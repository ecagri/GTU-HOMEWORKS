module datapath(input[63:0] prev, input[31:0] multiplicand, input write, input mult, input add, input sub, input slt, output[63:0] next);
	wire[63:0] product;
	wire[31:0] cout;
	wire[64:0] unshifted;
	wire[63:0] current;
	wire[63:0] temp;
	wire writeOrAdd;
	assign writeOrAdd = write | ~mult;
	mux32bit(prev[31:0], prev[63:32], ~mult, current[63:32]);
	mux32bit(prev[31:0], 32'b0, mult, product[31:0]);
	adder(current[63:32], multiplicand[31:0], sub, sub, cout[31:0], product[63:32]);
	mux64bit(product[63:0], prev[63:0], writeOrAdd, unshifted[63:0]);
	mux64bit(unshifted[64:1], unshifted[63:0], mult, next[63:0]);
endmodule
