module datapath(
	input RegDst,
	input Branch,
	input MemRead,
	input MemtoReg,
	input	MemWrite,
	input ALUSrc,
   input	RegWrite,
	input clock,
	input Mult,
	input [2:0] ALUControl,
	input [31:0] Instruction,
	output zero,
	output [15:0] datapath_result
);
	wire[15:0] busA, busB, B;
	wire[15:0] ALUResult;
	wire[15:0] data_mem_result;
	wire[3:0] RW;
	wire[31:0] Multiplication;
	
	assign RW = RegDst ? Instruction[17:14] : Instruction[21:18];	
	assign B = ALUSrc ? Instruction[17:2] : busB;	
	assign datapath_result = MemtoReg ? data_mem_result : ALUResult;
	
	regfile16x16 registers(Instruction[25:22], Instruction[21:18], RW, datapath_result, Multiplication, RegWrite, Mult, clock, busA, busB);
	alu16 alu(busA, B, ALUControl, ALUResult, Multiplication, zero);
	data_memory data_mem(ALUResult, clock, busB, MemWrite, data_mem_result);

endmodule 