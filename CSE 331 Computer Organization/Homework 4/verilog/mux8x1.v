module mux8x1(
	input[15:0] A, 
	input[15:0] B,
	input[15:0] C,
	input[15:0] D,
	input[15:0] E,
	input[15:0] F,
	input[15:0] G,
	input[15:0] H,
	input[2:0] Select,
	output[15:0] out
);
	wire[15:0] w0;
	wire[15:0] w1;
	wire[15:0] w2;
	wire[15:0] w3;
	wire[15:0] w4;
	wire[15:0] w5;
	
	assign w0 = ~Select[0] ? A : B;
	assign w1 = ~Select[0] ? C : D;
	assign w2 = ~Select[0] ? E : F;
	assign w3 = ~Select[0] ? G : H;
	
	assign w4 = ~Select[1] ? w0 : w1;
	assign w5 = ~Select[1] ? w2 : w3;
	
	assign out = ~Select[2] ? w4 : w5;
	
endmodule

