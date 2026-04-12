`timescale 1ns/1ps

module clk_gen (
    input  wire clk_in,
    input  wire rst,

    output wire sclk,
    output wire pll_main_clk,
    output wire axi_clk,
    output wire apb_clk
);

    // Divide by 2
    clk_div #(.DIV(2)) u_sclk (
        .clk_in(clk_in),
        .rst(rst),
        .clk_out_pad(sclk)
    );

    // Divide by 4
    clk_div #(.DIV(4)) u_pll_main_clk (
        .clk_in(clk_in),
        .rst(rst),
        .clk_out_pad(pll_main_clk)
    );

    // Divide by 8
    clk_div #(.DIV(8)) u_axi_clk (
        .clk_in(clk_in),
        .rst(rst),
        .clk_out_pad(axi_clk)
    );

    // Divide by 16
    clk_div #(.DIV(16)) u_apb_clk (
        .clk_in(clk_in),
        .rst(rst),
        .clk_out_pad(apb_clk)
    );

endmodule