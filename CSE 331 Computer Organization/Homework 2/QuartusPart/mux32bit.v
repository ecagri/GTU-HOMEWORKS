module mux32bit(input[31:0] a, input[31:0] b, input select, output[31:0] result);
	mux16bit(a[15:0], b[15:0], select, result[15:0]);
	mux16bit(a[31:16], b[31:16], select, result[31:16]);
endmodule