module and32bit(input[31:0] a, input[31:0] b, output [31:0] result);
	and8bit(a[7:0], b[7:0], result[7:0]);
	and8bit(a[15:8], b[15:8], result[15:8]);
	and8bit(a[23:16], b[23:16], result[23:16]);
	and8bit(a[31:24], b[31:24], result[31:24]);
endmodule