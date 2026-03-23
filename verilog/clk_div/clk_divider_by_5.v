`timescale 1ns/1ps

/*The counter counts from 0 to 4.
When the count reaches 4, the output clock toggles.
Since the output clock toggles every 5 input clock cycles, the output frequency is clk_in/10 (because toggling twice makes a full cycle).
To get clk_in/5 frequency, we toggle the output clock every 2.5 input clock cycles, which is not possible directly with a single edge.
The output clock toggles on both rising and falling edges of the input clock when the count is 2 or 4.
This creates an output clock with frequency clk_in/5 and approximately 50% duty cycle.
*/
module clk_div_by_5(
    input  wire clk_in,
    input  wire rst,   
    output reg  clk_out
);

    reg [2:0] cnt = 3'd0; //3 bit counter to cout 0-4

    always @(posedge clk_in or posedge rst) begin
        if (rst) begin
            cnt     <= 3'd0;
            clk_out <= 1'b0;
        end
        else begin
            if (cnt == 3'd4) begin
                cnt     <= 3'd0;
            end
            else begin
                cnt <= cnt + 1'b1;
            end
        end
    end

    always @(posedge clk_in or negedge clk_in or posedge rst) begin
        if (rst) begin
            clk_out <= 1'b0;
        end else begin
            if (cnt == 3'd2 || cnt == 3'd4)
                clk_out <= ~clk_out;
        end
    end

endmodule