module control(input [15:0] cypher, input[3:0] data, input reset, input read, output reg rs_col, output reg rs_sum, output reg add_sum);

reg[2:0] current, next;

localparam RESET = 3'b000,
			  START = 3'b001,
			  FIRSTMATCH = 3'b010,
			  SECONDMATCH = 3'b011,
			  THIRDMATCH = 3'b100,
			  LASTMATCH = 3'b101;
always @ (posedge read) begin	
	if(reset) /* If the reset input is 1, set the current state as RESET state. */
		current <= RESET;
	else /* Otherwise, go to next state. */
		current <= next;
end

always @ (*) begin
	case(current)
		RESET: begin /* If the current state is RESET, set the next state as START. */ 
			next = START;
		end
		START: begin /* If the current state is START, continue. */
			if(cypher[3:0] == data) begin /* If first four bits of the cypher are matched with data, set the next state as FIRSTMATCH. */
				next = FIRSTMATCH;
			end else begin /* Otherwise next state is START. */
				next = START;
			end
		end
		FIRSTMATCH: begin /* If the current state is FIRSTMATCH, continue. */
			if(cypher[7:4] == data) begin /* If second four bits of the cypher are matched with data, set the next state as SECONDMATCH. */
				next = SECONDMATCH;
			end else if(cypher[3:0] == data) begin
				next = FIRSTMATCH;
			end else begin /* Otherwise next state is START. */
				next = START;
			end
		end
		SECONDMATCH: begin
			if(cypher[11:8] == data) begin /* If second third bits of the cypher are matched with data, set the next state as THIRDMATCH. */
				next = THIRDMATCH;
			end else if(cypher[3:0] == data) begin
				next = FIRSTMATCH;
			end else begin
				next = START; /* Otherwise next state is START. */
			end
		end
		THIRDMATCH: begin
			if(cypher[15:12] == data) begin /* If last four bits of the cypher are matched with data, set the next state as LASTMATCH. */
				next = LASTMATCH;
			end else if(cypher[3:0] == data) begin
				next = FIRSTMATCH;
			end else begin
				next = START; /* Otherwise next state is START. */
			end
		end
		LASTMATCH: begin /* If the current state is LASTMATCH, set the next state as RESET. */
			next = RESET; 
		end
	endcase
end

always @ (*) begin /* Sets the signal according to current state. */
	add_sum = 1'b0;
	case(current)
		RESET: begin
			rs_sum = 1'b1;
			rs_col = 1'b1;
		end
		START: begin
			rs_sum = 1'b0;
			rs_col = 1'b1;
			add_sum = 1'b1;
		end
		FIRSTMATCH: begin
			rs_sum = 1'b0;
			rs_col = 1'b1;
			add_sum = 1'b1;
		end
		SECONDMATCH: begin
			rs_sum = 1'b0;
			rs_col = 1'b1;
			add_sum = 1'b1;
		end
		THIRDMATCH: begin
			rs_sum = 1'b0;
			rs_col = 1'b1;
			add_sum = 1'b1;
		end
		LASTMATCH: begin
			rs_sum = 1'b0;
			rs_col = 1'b0;
			add_sum = 1'b0;
		end
	endcase
end




endmodule