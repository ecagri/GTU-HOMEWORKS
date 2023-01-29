module control(input lastbit, input clock, output reg write);
	integer i = 0;
	always@(posedge clock) begin
		if(lastbit == 0) begin
			write <= 0;
		end else begin
			write <= 1;
		end
	end
endmodule
