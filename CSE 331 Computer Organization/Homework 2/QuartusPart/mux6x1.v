module mux6x1(input[31:0] result0, input[31:0] result1, input[31:0] result2, input[31:0] result3, input[31:0] result4, input[31:0] result5, input[31:0] result6, input[31:0] result7, input[2:0] op, output[31:0] finalResult);
	wire[31:0] temp1;
	wire[31:0] temp2;
	wire[31:0] temp3;
	wire[31:0] temp4;
	wire[31:0] temp5;
	wire[31:0] temp6;
	mux32bit(result1, result0, op[0], temp1);
	mux32bit(result3, result2, op[0], temp2);
	mux32bit(result5, result4, op[0], temp3);
	mux32bit(result7, result6, op[0], temp4);
	mux32bit(temp2, temp1, op[1], temp5);
	mux32bit(temp4, temp3, op[1], temp6);
	mux32bit(temp6, temp5, op[2], finalResult);
endmodule