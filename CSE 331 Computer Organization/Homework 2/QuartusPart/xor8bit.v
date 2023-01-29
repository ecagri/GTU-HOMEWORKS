module xor8bit(input[7:0] a, input[7:0] b, output[7:0] result);
	xor(result[0], a[0], b[0]);
	xor(result[1], a[1], b[1]);
	xor(result[2], a[2], b[2]);
	xor(result[3], a[3], b[3]);
	xor(result[4], a[4], b[4]);
	xor(result[5], a[5], b[5]);
	xor(result[6], a[6], b[6]);
	xor(result[7], a[7], b[7]);	
endmodule