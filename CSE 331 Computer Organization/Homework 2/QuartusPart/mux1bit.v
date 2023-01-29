module mux1bit(input a, input b, input select, output result);

	wire temp1, temp2, temp3;
	and(temp1, a, select);
	not(temp2, select);
	and(temp3, b, temp2);
	or(result, temp3, temp1);
	
endmodule
