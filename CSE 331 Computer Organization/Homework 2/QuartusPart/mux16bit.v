module mux16bit(input[15:0] a, input[15:0] b, input select, output[15:0] result);
	mux4bit(a[3:0], b[3:0], select, result[3:0]);
	mux4bit(a[7:4], b[7:4], select, result[7:4]);
	mux4bit(a[11:8], b[11:8], select, result[11:8]);
	mux4bit(a[15:12], b[15:12], select, result[15:12]);
endmodule