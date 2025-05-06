module validity 
(	
	input [15:0]BCD,
	output reg valid
);
	
	always @ (BCD) begin
	
	if(BCD[11:0] <= 12'b000100100111)
		valid = 1;
	else
		valid = 0;
	
	end
endmodule