module mips_tb();
	reg clock = 1'b0;
	reg clock2 = 1'b0;
	mips mips_for_test(clock, clock2);
	
	always begin	
		#25 
		clock2 = ~clock2;
		#25 
		clock = ~clock;
	end 

endmodule   