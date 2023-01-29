module alu16_tb();
	reg[15:0] A;
	reg[15:0] B;
	reg[2:0] ALUOP;
	wire[15:0] Result;
	wire[31:0] Multiplication;
	
	alu16 alu(A, B, ALUOP, Result, Multiplication);
	
	initial begin
		A = 16'b10110; // 22
		B = 16'b00101; // 5
		ALUOP = 3'b000;
		
		#50
		
		ALUOP = 3'b001;
		
		#50
		
		ALUOP = 3'b001;
		
		#50
		
		ALUOP = 3'b010;
		
		#50
		
		ALUOP = 3'b011;
		
		#50
		
		ALUOP = 3'b100;
		
		#50
		
		ALUOP = 3'b101;
		
		#50
		
		ALUOP = 3'b110;
		
		#50
		
		ALUOP = 3'b111;
		
	end


endmodule