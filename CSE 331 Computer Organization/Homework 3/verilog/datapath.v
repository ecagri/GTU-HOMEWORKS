module datapath(input [3:0] data, input add_sum, input rs_sum,  input rs_col, input clock, output collected, output[7:0] sum);

reg[7:0] reg_sum;
reg reg_collected;
wire[7: 0] w_sum;
wire w_collected;
wire[7:0] w_sumalpha;

assign sum = reg_sum;
assign collected = reg_collected;

assign w_sum = add_sum ? (sum + data) : sum;
assign w_sumalpha = rs_sum ? 8'b0 : w_sum;
assign w_collected = rs_col ? 1'b0 : 1'b1;


always @(posedge clock) begin
	reg_sum <= w_sumalpha;
	reg_collected <= w_collected;
end
endmodule