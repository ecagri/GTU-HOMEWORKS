module mips(input clock, clock2);
	
	wire RegDst, Branch, BranchNotEqual, Jump, JumpRegister, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, zero, Mult;
	wire[2:0] ALUOP;
	wire[6:0] OPCode;
	wire[15:0] datapath_result;
	wire[31:0] Instruction;
	wire[9:0] PC;
	reg[9:0] PC_reg;
	
	instruction_mem instruction_memory(PC, Instruction);
	datapath datapath16(RegDst, Branch, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, clock2, Mult, ALUOP, Instruction, zero, datapath_result);
	control control16(Instruction[31:26], Instruction[9:4], RegDst, Branch, BranchNotEqual, Jump, JumpRegister, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, Mult, ALUOP);	
	
	assign PC = PC_reg;
	
	initial begin
		PC_reg = 10'b0;
	end
	
	always @ (posedge clock) begin
		if(Branch & zero) begin
			PC_reg = PC + 1 + Instruction[17:2];
		end else if (BranchNotEqual & ~zero) begin
			PC_reg = PC + 1 + Instruction[17:2]; 
		end else if(Jump) begin
			PC_reg = Instruction[25:16];
		end else if (JumpRegister) begin
			PC_reg = datapath_result[9:0];
		end else begin
			PC_reg <= PC + 1;
		end
	end
	
	
endmodule