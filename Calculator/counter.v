module counter 
	(
	input clock, reset, StartStop,
	output [6:0] HEX0, HEX1, HEX2,
	output HEX3_g
	);

	wire ten;
	wire sec0;
	wire [7:0] count;
	
	tenHz s0 (clock, reset, StartStop, ten);

	divideXN #(8'd255, 4'd8) d0 (ten, reset, count[7:0], sec0);
	
	OU o0(count[7:0], HEX0[6:0], HEX1[6:0], HEX2[6:0], HEX3_g);
endmodule
	