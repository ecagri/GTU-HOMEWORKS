module or8bit(input[7:0] a, input[7:0] b, output[7:0] result);
	or(result[0], a[0], b[0]);
	or(result[1], a[1], b[1]);
	or(result[2], a[2], b[2]);
	or(result[3], a[3], b[3]);
	or(result[4], a[4], b[4]);
	or(result[5], a[5], b[5]);
	or(result[6], a[6], b[6]);
	or(result[7], a[7], b[7]);	
endmodule
