module cypherDetector_tb();
	reg[15:0] cypher;
	reg[3:0] data;
	reg clock = 1'b0, reset, read = 1'b0;
	wire[7:0] sum;
	wire collected;
	
	cypherDetector detector(cypher, data, read, reset, clock, collected, sum);
	
	always begin	
		#1
		clock = ~clock;
		read = ~read;
	end
	
	initial begin
		reset = 1'b1;
		cypher = 16'b0010011000010001;
		#6 
		reset = 1'b0;
		#2
		data = 4'b0001;
		#2
		data = 4'b0001;
		#2
		data = 4'b0110;
		#2
		data = 4'b0010;	
		
		#200
		reset = 1'b1;
		cypher = 16'b1000010000100001;
		#6 
		reset = 1'b0;
		#2
		data = 4'b1110;
		#2
		data = 4'b0010;
		#2
		data = 4'b0001;
		#2
		data = 4'b0010;
		#2
		data = 4'b0100;
		#2
		data = 4'b1000;
		#2
		data = 4'b1010;
		
		#200
		reset = 1'b1;
		cypher = 16'b0001001000110100;
		#6 
		reset = 1'b0;
		#2
		data = 4'b0100;
		#2
		data = 4'b0011;
		#2
		data = 4'b0010;
		#2
		data = 4'b0011;
		#2
		data = 4'b0100;
		#2
		data = 4'b0011;
		#2
		data = 4'b0010;
		#2
		data = 4'b0001;
		
	end




endmodule