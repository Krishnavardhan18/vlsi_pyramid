`timescale 1ns/1ps

module clk_div #(
    parameter DIV = 14
)(
    input wire clk_in,
    input wire rst,
    output reg clk_out_pad
);

    reg[3:0] counter = 0;

    always @(posedge clk_in or posedge rst) begin
        if(rst) begin
            counter <= 4'd0;
            clk_out_pad <= 1'b0;
        end
        else begin
            if(counter == (DIV/2 -1)) begin
                counter <= 4'd0;
                clk_out_pad <= ~clk_out_pad;
            end
            else begin
                counter <= counter + 1'b1;
            end
        end
    end

endmodule