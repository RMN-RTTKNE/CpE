module IU 
(
	input clk, rst, 
	input [3:0]row,
	output [3:0]col,
	output [7:0] TS,
	output valid,
	output trig,
	output [2:0]op
);
	wire [15:0]BCD;
	wire [7:0]BSM;
	
	keypad_input kp
	(
		.clk(clk) ,	
		.reset(rst) ,	
		.row(row) ,	
		.col(col) ,	
		.out(BCD),
		.trig(trig),
		.op(op)
	);
	
	validity check (BCD, valid);
	
	BCD2BinarySM b0 (BCD, BSM); 
	
	twoSIGN (BSM, TS[6:0]);
	
	assign TS[7] = BSM[7];
	
endmodule