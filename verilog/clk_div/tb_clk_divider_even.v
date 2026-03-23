`timescale 1ns/1ps

module tb;

    reg clk;
    reg rst;
    wire clk_out;

    clk_div_n_even #(.DIV(4)) uut (
        .clk_in(clk),
        .rst(rst),
        .clk_out(clk_out)
    );

    initial begin
        clk = 0;
        forever #10 clk = ~clk;   // 20ns period
    end

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb);

        rst = 1;
        #20;
        rst = 0;

        #200;
        $finish;
    end

endmodule