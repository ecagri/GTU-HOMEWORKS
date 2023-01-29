module mult32(input[31:0] multiplier, input[31:0] multiplicand, input clock, input mult, input add, input sub, input slt, output [63:0] product, output [31:0] sum);
	wire write;
	reg[63:0] tempProduct;
	reg[63:0] temp;
	wire[63:0] tempResult;
	reg[63:0] tempSum;
	integer i = 0;
	always@(posedge clock) begin
		if(i == 0) begin
			temp[63:32] <= 32'b0;
			temp[31:0] <= multiplier;
		end else if(i < 35 && mult == 1) begin
			temp <= tempResult;
			tempProduct <= temp;
		end else if(i < 2 && mult == 0) begin
			temp <= 64'b0;
			tempSum <= tempResult;
		end
		i = i + 1;
	end
	control(temp[0], clock, write);
	datapath(temp[63:0], multiplicand[31:0], write, mult, add, sub, slt, tempResult[63:0]);
	assign product = (tempProduct);
	assign sum = (tempSum[63:32]);
endmodule