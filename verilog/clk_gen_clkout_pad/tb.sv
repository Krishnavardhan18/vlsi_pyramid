`timescale 1ns/1ps

// ============================================================
// Testbench for top.v  (clk_gen + clk_mux + clk_div /14)
//
// clk_in = 100 MHz (period = 10 ns)
//
// Expected clk_out_pad periods
//   cfg_sel = 0 : sclk        = clk_in/2  -> /14 total = /28  -> 280 ns
//   cfg_sel = 1 : pll_main_clk= clk_in/4  -> /14 total = /56  -> 560 ns
//   cfg_sel = 2 : axi_clk     = clk_in/8  -> /14 total = /112 -> 1120 ns
//   cfg_sel = 3 : apb_clk     = clk_in/16 -> /14 total = /224 -> 2240 ns
// ============================================================

module tb;

    logic        clk_in;
    logic        rst;
    logic [1:0]  cfg_sel;
    wire         clk_out_pad;

    top u_top (
        .clk_in      (clk_in),
        .rst         (rst),
        .cfg_sel     (cfg_sel),
        .clk_out_pad (clk_out_pad)
    );

    // --------------------------------------------------------
    // 100 MHz clock generation  (period = 10 ns)
    // --------------------------------------------------------
    localparam real CLK_PERIOD = 10.0; // ns

    initial clk_in = 1'b0;
    always #(CLK_PERIOD / 2.0) clk_in = ~clk_in;

    // --------------------------------------------------------
    // Period measurement helper
    //   Measures the period of clk_out_pad over N_CYCLES
    //   rising edges and prints result vs expected.
    // --------------------------------------------------------
    localparam int MEAS_CYCLES = 6;

    task automatic measure_period(
        input real    expected_ns,
        input string  label
    );
        real t_start, t_end, measured_ns;
        int  i;

        // Wait for first rising edge (synchronise)
        @(posedge clk_out_pad);
        t_start = $realtime;

        for (i = 0; i < MEAS_CYCLES; i++)
            @(posedge clk_out_pad);

        t_end       = $realtime;
        measured_ns = (t_end - t_start) / MEAS_CYCLES;

        $display("[%0t ns]  cfg_sel=%0b (%s)  measured period = %0.1f ns  (expected %0.1f ns)  %s",
                 $realtime, cfg_sel, label, measured_ns, expected_ns,
                 (measured_ns == expected_ns) ? "PASS" : "FAIL");
    endtask

    // --------------------------------------------------------
    // Stimulus
    // --------------------------------------------------------
    // How many clk_out_pad cycles to observe per cfg_sel value
    // before switching (gives waveform visibility in viewer)
    localparam int OBSERVE_CYCLES = 20;

    // Worst-case period at cfg_sel=3 is 2240 ns → 20 cycles = 44800 ns
    // Use per-phase waits so earlier phases don't over-wait.

    initial begin
        // --- initialise ---
        rst     = 1'b1;
        cfg_sel = 2'b00;

        // hold reset for 10 clk_in cycles
        repeat (10) @(posedge clk_in);
        rst = 1'b0;
        $display("[%0t ns]  Reset de-asserted", $realtime);

        // ---- cfg_sel = 0 : sclk -> clk_out_pad = clk_in/28 = 280 ns ----
        cfg_sel = 2'b00;
        $display("[%0t ns]  cfg_sel -> 2'b00  (sclk, expect /28 = 280 ns)", $realtime);
        measure_period(280.0, "sclk /28");
        // Stay for extra OBSERVE_CYCLES after measurement
        repeat (OBSERVE_CYCLES) @(posedge clk_out_pad);

        // ---- cfg_sel = 1 : pll_main_clk -> clk_out_pad = clk_in/56 = 560 ns ----
        cfg_sel = 2'b01;
        $display("[%0t ns]  cfg_sel -> 2'b01  (pll_main_clk, expect /56 = 560 ns)", $realtime);
        measure_period(560.0, "pll_main /56");
        repeat (OBSERVE_CYCLES) @(posedge clk_out_pad);

        // ---- cfg_sel = 2 : axi_clk -> clk_out_pad = clk_in/112 = 1120 ns ----
        cfg_sel = 2'b10;
        $display("[%0t ns]  cfg_sel -> 2'b10  (axi_clk, expect /112 = 1120 ns)", $realtime);
        measure_period(1120.0, "axi_clk /112");
        repeat (OBSERVE_CYCLES) @(posedge clk_out_pad);

        // ---- cfg_sel = 3 : apb_clk -> clk_out_pad = clk_in/224 = 2240 ns ----
        cfg_sel = 2'b11;
        $display("[%0t ns]  cfg_sel -> 2'b11  (apb_clk, expect /224 = 2240 ns)", $realtime);
        measure_period(2240.0, "apb_clk /224");
        repeat (OBSERVE_CYCLES) @(posedge clk_out_pad);

        $display("[%0t ns]  Simulation complete", $realtime);
        $finish;
    end

    // --------------------------------------------------------
    // Optional: assert reset briefly mid-sim to test recovery
    // --------------------------------------------------------
    // Uncomment the block below to verify reset clears dividers
    // at any cfg_sel value.
    //
    // initial begin
    //     #50000;
    //     $display("[%0t ns]  Asserting mid-sim reset", $realtime);
    //     rst = 1'b1;
    //     repeat (5) @(posedge clk_in);
    //     rst = 1'b0;
    //     $display("[%0t ns]  Mid-sim reset released", $realtime);
    // end

    // --------------------------------------------------------
    // Waveform dump (works with xsim / iverilog / vcs)
    // --------------------------------------------------------
    initial begin
        $dumpfile("tb_clk_div.vcd");
        $dumpvars(0, tb);
    end

endmodule
