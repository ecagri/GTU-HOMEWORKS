module and8bit(input[7:0] a, input[7:0] b, output[7:0] result);
	and(result[0], a[0], b[0]);
	and(result[1], a[1], b[1]);
	and(result[2], a[2], b[2]);
	and(result[3], a[3], b[3]);
	and(result[4], a[4], b[4]);
	and(result[5], a[5], b[5]);
	and(result[6], a[6], b[6]);
	and(result[7], a[7], b[7]);	
endmodule
