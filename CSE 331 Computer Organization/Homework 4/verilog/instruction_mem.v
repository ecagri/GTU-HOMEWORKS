module instruction_mem(
	input[9:0] PC,
	output[31:0] Instruction
);		
	reg[1023:0] Instructions[31:0];
	
	assign Instruction = Instructions[PC];
	
	initial begin
		Instructions[0] = 32'b00000100000001000000000000100100; // addi $1 $0 9
		Instructions[1] = 32'b00000100000010000000000000110000; // addi $2 $0 12
		Instructions[2] = 32'b00000000010010001100001000000000; // add $3 $1 $2
		Instructions[3] = 32'b00011000010100000000000000110000; // slti $4 $1 12
		Instructions[4] = 32'b00011000010101000000000000011000; // slti $5 $1 6
		Instructions[5] = 32'b00000000010010011000001010100000; // slt $6 $1 $2  
		Instructions[6] = 32'b00000000010000011100001010100000; // slt $7 $1 $0
		Instructions[7] = 32'b00000000100001100000001000100000; // sub $8 $2 $1
		Instructions[8] = 32'b00000100001001000000000000111100; // addi $9 $0 15 (binary 1111)
		Instructions[9] = 32'b00000100001010000000000001101000; // addi $10 $0 26 (binary 111010)
		Instructions[10] = 32'b00000010011010101100001001000000; // and $11 $9 $10
		Instructions[11] = 32'b00000010011010110000001001010000; // or $12 $9 $10
		Instructions[12] = 32'b00001010011011000000000001101000; // andi $11 $9 26
		Instructions[13] = 32'b00001110011100000000000001101000; // ori $12 $9 26
		Instructions[14] = 32'b00010100000010000000000001000100; // li $2 17
		Instructions[15] = 32'b10101100000010000000000001100000; // sw $2 24($0)
		Instructions[16] = 32'b10001100001000000000000001100000; // lw $12 24($0)
		Instructions[17] = 32'b11111100010010000000000000000000; // mult $1 $2
		Instructions[18] = 32'b10101100001110000000000011001000; // sw $14 50($0) (hi register)
		Instructions[19] = 32'b10101100001111000000000010100000; // sw $15 40($0) (lo register) 
		Instructions[20] = 32'b00010000000001000000000000001000; // beq $0 $1 2
		Instructions[21] = 32'b00110000000000000000000000001000; // bne $0 $0 2 
		Instructions[22] = 32'b00010000000000000000000000001000; // beq $0 $0 2
		Instructions[23] = 32'b00010100000010000000000001000100; // li $2 17 (test purposes) 
		Instructions[24] = 32'b00010100000010000000000001000100; // li $2 17 (test porposes)
		Instructions[25] = 32'b00110000000001000000000000001000; // bne $0 $1 2
		Instructions[26] = 32'b00010100000010000000000001000100; // li $2 17 (test purposes) 
		Instructions[27] = 32'b00010100000010000000000001000100; // li $2 17 (test purposes) 
		Instructions[28] = 32'b11111000000111100000000000000000; // j 30
		Instructions[29] = 32'b00010100000010000000000001000100; // li $2 17 (test purposes)  
		Instructions[30] = 32'b11110100000010000000000000000000; // jr $2
	end

endmodule