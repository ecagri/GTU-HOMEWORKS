module cypherDetector(input[15:0] cypher, input[3:0] data, input read, input reset, input clock, output collected, output[7:0] sum);
	wire add_sum, rs_sum, rs_col;
	datapath dp(data, add_sum, rs_sum, rs_col, clock, collected, sum);
	control ctrl(cypher, data, reset, read, rs_col, rs_sum, add_sum);
endmodule