module adder(input [31:0] a, input [31:0] b, input cin, input sub, output[31:0] cout, output[31:0] sum);
	fullAdder16bit(a[15:0], b[15:0], cin, sub, cout[15:0], sum[15:0]);
	fullAdder16bit(a[31:16], b[31:16], cout[15], sub, cout[31:16], sum[31:16]);	
endmodule

module fullAdder16bit(input[15:0] a, input [15:0] b, input cin, input sub, output[15:0] cout, output[15:0] sum);
	fullAdder4bit(a[3:0], b[3:0], cin, sub, cout[3:0], sum[3:0]);
	fullAdder4bit(a[7:4], b[7:4], cout[3], sub, cout[7:4], sum[7:4]);
	fullAdder4bit(a[11:8], b[11:8], cout[7], sub, cout[11:8], sum[11:8]);
	fullAdder4bit(a[15:12], b[15:12], cout[11], sub, cout[15:12], sum[15:12]);
endmodule

module fullAdder4bit(input[3:0] a, input [3:0] b, input cin, input sub, output[3:0] cout, output[3:0]sum);
	fullAdder1bit(a[0], b[0], cin, sub, cout[0], sum[0]);
	fullAdder1bit(a[1], b[1], cout[0], sub, cout[1], sum[1]);
	fullAdder1bit(a[2], b[2], cout[1], sub, cout[2], sum[2]);
	fullAdder1bit(a[3], b[3], cout[2], sub, cout[3], sum[3]);
endmodule

module fullAdder1bit(input a, b, cin, sub, output cout, sum);
	wire wire1, wire2, wire3, wire4, bbnot;
	mux1bit(~b, b, sub, bbnot);
	xor(wire1, a, bbnot);
	xor(sum, wire1, cin);
	and(wire2, cin, wire1);
	and(wire3, a, bbnot);
	or(cout, wire2, wire3);
endmodule
