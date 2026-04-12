`timescale 1ns/1ps

module clk_mux(
    input wire clk_in_1, clk_in_2, clk_in_3, clk_in_4,
    input wire [1:0] cfg_sel,
    output reg clk_out
);
    always @(*) begin
        case (cfg_sel)
            2'b00 : clk_out = clk_in_1;
            2'b01 : clk_out = clk_in_2;
            2'b10 : clk_out = clk_in_3;
            2'b11 : clk_out = clk_in_4;
            default : clk_out = 1'b0;
        endcase
    end

endmodule