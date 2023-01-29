module nor8bit(input[7:0] a, input[7:0] b, output[7:0] result);
	nor(result[0], a[0], b[0]);
	nor(result[1], a[1], b[1]);
	nor(result[2], a[2], b[2]);
	nor(result[3], a[3], b[3]);
	nor(result[4], a[4], b[4]);
	nor(result[5], a[5], b[5]);
	nor(result[6], a[6], b[6]);
	nor(result[7], a[7], b[7]);	
endmodule