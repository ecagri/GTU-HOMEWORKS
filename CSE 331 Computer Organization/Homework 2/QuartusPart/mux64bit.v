module mux64bit(input[63:0] a, input[63:0] b, input select, output[63:0] result);
	mux16bit(a[15:0], b[15:0], select, result[15:0]);
	mux16bit(a[31:16], b[31:16], select, result[31:16]);
	mux16bit(a[47:32], b[47:32], select, result[47:32]);
	mux16bit(a[63:48], b[63:48], select, result[63:48]);
endmodule