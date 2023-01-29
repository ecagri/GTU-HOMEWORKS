module control(
	input[5:0] OPCode,
	input[5:0] functionField,
	output RegDst,
	output Branch,
	output BranchNotEqual,
	output Jump,
	output JumpRegister,
	output MemRead,
	output MemtoReg,
	output	MemWrite,
	output ALUSrc,
   output	RegWrite,
	output Mult, 
	output [2:0] ALUOP
);
	wire R_type, lw, sw, beq, addi, li, andi, ori, slti;
	wire[2:0] aluop;
	assign R_type = (OPCode === 6'b0) ? 1'b1: 1'b0;
	assign lw = (OPCode === 6'b100011) ? 1'b1: 1'b0;
	assign sw = (OPCode === 6'b101011) ? 1'b1: 1'b0;
	assign beq = (OPCode === 6'b000100) ? 1'b1: 1'b0;
	assign bne = (OPCode === 6'b001100) ? 1'b1: 1'b0;
	assign addi = (OPCode === 6'b000001) ? 1'b1: 1'b0;
	assign andi = (OPCode === 6'b000010) ? 1'b1: 1'b0;
	assign ori = (OPCode === 6'b0000011) ? 1'b1: 1'b0;
	assign slti = (OPCode === 6'b000110) ? 1'b1: 1'b0;
	assign li = (OPCode === 6'b000101) ? 1'b1: 1'b0;
	assign Mult = (OPCode === 6'b111111) ? 1'b1: 1'b0;
	assign Jump = (OPCode === 6'b111110) ? 1'b1: 1'b0;
	assign JumpRegister = (OPCode === 6'b111101) ? 1'b1: 1'b0;
	assign RegWrite = ~Mult & (R_type | lw | addi | andi | ori | slti | li);
	assign ALUSrc = lw | sw | addi | andi | ori | slti | li;
	assign RegDst = R_type;
	assign MemtoReg = lw;
	assign MemRead = lw;
	assign MemWrite = sw;
	assign Branch = beq;
	assign BranchNotEqual = bne;
	assign aluop[2] = beq + (R_type & functionField[1]) + bne;
	assign aluop[1] = ~R_type + ~functionField[2];
	assign aluop[0] = R_type & (functionField[0] + functionField[3]);		
	assign ALUOP = (addi + li + sw + lw + JumpRegister) ? 3'b010: ((andi) ? 3'b000: ((ori) ? 3'b001: ((slti) ? 3'b111: aluop)));
		

endmodule