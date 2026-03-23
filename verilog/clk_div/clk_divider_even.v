`timescale 1ns/1ps

module clk_div_n_even #(
    parameter DIV = 4   // Must be EVEN number
)(
    input  wire clk_in,
    input  wire rst,      
    output reg  clk_out
);

    // Counter width (enough bits to count till DIV/2)
    reg [$clog2(DIV/2)-1:0] cnt;

    always @(posedge clk_in or posedge rst) begin
        if (rst) begin
            cnt     <= 3'd0;
            clk_out <= 1'b0;
        end
        else begin
            if (cnt == (DIV/2 - 1)) begin
                cnt     <= 3'd0;
                clk_out <= ~clk_out; 
            end
            else begin
                cnt <= cnt + 1'b1;
            end
        end
    end

endmodule