module datapath_tb();
	reg RegDst;
	reg Branch;
	reg MemRead;
	reg MemtoReg;
	reg	MemWrite;
	reg ALUSrc;
   reg	RegWrite;
	reg clock = 1'b1;
	reg [1:0] ALUOP;
	reg [31:0] Instruction;
	wire [15:0] datapath_result;
	
	datapath datapath16(RegDst, Branch, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, clock, ALUOP, Instruction, datapath_result);
	
	always begin	
		#10
		clock = ~clock;
	end
	
	initial begin
		Instruction = 32'b00000000000000000100001000000000;
		RegDst = 1'b1;
		ALUSrc = 1'b0;
		MemtoReg = 1'b0;
		RegWrite = 1'b1;
		MemRead = 1'b0;
		MemWrite = 1'b0;
		Branch = 1'b0;
		ALUOP = 2'b10;
		
		#50
		
		Instruction = 32'b00000000000010000100001000000000;
		RegDst = 1'b0;
		ALUSrc = 1'b1;
		MemtoReg = 1'b0;
		RegWrite = 1'b1;
		MemRead = 1'b0;
		MemWrite = 1'b0;
		Branch = 1'b0;
		ALUOP = 2'b10;
		
		
		#50
		Instruction = 32'b00000000000010000100001000000000;
		RegDst = 1'b1;
		ALUSrc = 1'b0;
		MemtoReg = 1'b0;
		RegWrite = 1'b1;
		MemRead = 1'b0;
		MemWrite = 1'b0;
		Branch = 1'b0;
		ALUOP = 2'b10;
		
	end


endmodule