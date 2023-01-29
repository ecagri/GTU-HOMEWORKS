module alu_control_unit(
	input[1:0] ALUOP,
	input [5:0] functionField,
	output [2:0] ALUControl
);
	assign ALUControl[0] = ALUOP[0] + (ALUOP[1] & functionField[1]);
	assign ALUControl[1] = ~ALUOP[1] + ~functionField[2];
	assign ALUControl[2] = ALUOP[1] & (functionField[0] + functionField[3]);
endmodule