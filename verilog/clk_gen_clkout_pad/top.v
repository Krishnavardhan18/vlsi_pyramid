`timescale 1ns/1ps

module top (
    input  wire clk_in,
    input  wire rst,
    input  wire [1:0] cfg_sel,
    output wire clk_out_pad
);

    wire sclk;
    wire pll_main_clk;
    wire axi_clk;
    wire apb_clk;

    wire clk_selected;

    clk_gen u_clk_gen (
        .clk_in(clk_in),
        .rst(rst),
        .sclk(sclk),
        .pll_main_clk(pll_main_clk),
        .axi_clk(axi_clk),
        .apb_clk(apb_clk)
    );

    clk_mux u_clk_mux (
        .clk_in_1(sclk),
        .clk_in_2(pll_main_clk),
        .clk_in_3(axi_clk),
        .clk_in_4(apb_clk),
        .cfg_sel(cfg_sel),
        .clk_out(clk_selected)
    );

    clk_div #(.DIV(14)) u_clk_div (
        .clk_in(clk_selected),
        .rst(rst),
        .clk_out_pad(clk_out_pad)
    );

endmodule