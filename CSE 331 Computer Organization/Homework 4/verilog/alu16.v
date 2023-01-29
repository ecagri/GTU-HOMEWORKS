module alu16(
	input[15:0] A,
	input[15:0] B,
	input[2:0] ALUOP,
	output[15:0] Result,
	output[31:0] Multiplication,
	output zero
);

	wire[15:0] ADD;
	wire[15:0] SUB;
	wire[31:0] MULT;
	wire[15:0] XOR;
	wire[15:0] AND;
	wire[15:0] OR;
	wire[15:0] SLT; 
	wire[15:0] NOR;

	assign ADD = A + B;
	assign SUB = A - B;
	assign MULT = A * B;
	assign XOR = A ^ B;
	assign AND = A & B;
	assign OR = A | B;
	assign SLT = SUB[15] ? 16'b1 : 16'b0;
	assign NOR = ~(A | B);
	
	mux8x1 mux(AND, OR, ADD, MULT, XOR, NOR, SUB, SLT, ALUOP, Result);
	
	assign zero = (Result == 15'b0) ? 1'b1 : 1'b0;
	
	assign Multiplication = A * B;
	
endmodule