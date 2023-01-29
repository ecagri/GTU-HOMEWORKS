module mux4bit(input[3:0] a, input[3:0] b, input select, output[3:0] result);
	mux1bit(a[0], b[0], select, result[0]);
	mux1bit(a[1], b[1], select, result[1]);
	mux1bit(a[2], b[2], select, result[2]);
	mux1bit(a[3], b[3], select, result[3]);
endmodule