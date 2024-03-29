module regfile16x16_tb();
	reg[3:0] RA, RB, RW;
	reg[15:0] busW;
	reg writeEnable;
 	wire[15:0] busA, busB;
	reg clock = 1'b1;
	
	regfile16x16 regfile(RA, RB, RW, busW, writeEnable, clock, busA, busB);
	
	always begin	
		#10
		clock = ~clock;
	end
	
	
	initial begin
		RW = 3'b1;
		writeEnable = 1'b1;
		busW = 16'b11001;
		
		#50
		
		RA = 3'b01;
		writeEnable = 1'b0;
		
		#50
		
		RB = 3'b000;
		writeEnable = 1'b0;
		
	end

endmodule