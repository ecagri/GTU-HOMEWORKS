module mux8x1_tb();
	reg[15:0] A;
	reg[15:0] B;
	reg[15:0] C;
	reg[15:0] D;
	reg[15:0] E;
	reg[15:0] F;
	reg[15:0] G;
	reg[15:0] H;
	reg[2:0] Select;
	wire[15:0] out;
	
	mux8x1 mux(A, B, C, D, E, F, G, H, Select, out);

	initial begin
	
		A = 16'b0;
		B = 16'b1;
		C = 16'b10;
		D = 16'b11;
		E = 16'b100;
		F = 16'b101;
		G = 16'b110;
		H = 16'b111;
		Select = 3'b11;
		
		#100
		
		Select = 3'b110;
		
		#100
		
		Select = 3'b101;
	
	end


endmodule