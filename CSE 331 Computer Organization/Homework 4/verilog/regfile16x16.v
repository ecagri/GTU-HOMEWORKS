module regfile16x16(
	input[3:0] RA,
	input[3:0] RB, 
	input[3:0] RW,
	input[15:0] busW, 
	input[31:0] Multiplication,
	input writeEnable,
	input Mult,
	input clock, 
	output[15:0] busA, 
	output[15:0] busB
);
	reg[15:0] regfile[15:0];
	
	assign busA = regfile[RA];
	assign busB = regfile[RB];
	
	always @ (posedge clock) begin
		if(writeEnable) begin
			regfile[RW] <= busW;
		end
		if(Mult) begin
			regfile[15] <= Multiplication[31:16];
			regfile[14] <= Multiplication[15:0];
		end
		regfile[0] <= 16'b0;
	end
	
	initial begin
		regfile[0] = 16'b0;
	end
	
endmodule