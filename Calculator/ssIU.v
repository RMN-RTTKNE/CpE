module ssIU (

	input CLK, CLR,
	input [3:0]row,
	output [3:0]col,
	output sReset, sLA, sLB, sLR, sIUAU, sAS
);

wire [7:0]TS;
wire Reset, LA, LB, LR, IUAU, AS, trig;
wire [1:0]op;
assign sReset = Reset; assign  sLA = LA; assign sLB = LB; assign sLR = LR; assign sIUAU = IUAU; assign sAS = AS;


CU CU_inst
(
	.ClearAll(CLR) ,	// input  ClearAll_sig
	.CLK(CLK) ,	// input  CLK_sig
	.trig(CLK) ,	// input  trig_sig
	.value(op) ,	// input [3:0] value_sig
	.Reset(Reset) ,	// output  Reset_sig
	.LoadA(LA) ,	// output  LoadA_sig
	.LoadB(LB) ,	// output  LoadB_sig
	.LoadR(LR) ,	// output  LoadR_sig
	.AS(AS) ,	// output  AS_sig
	.IUAU(IUAU) 	// output  IUAU_sig
);
IU IU_inst
(
	.clk(CLK) ,	// input  clk_sig
	.rst(Reset) ,	// input  rst_sig
	.row(row) ,	// input [3:0] row_sig
	.col(col) ,	// output [3:0] col_sig
	.TS(TS) ,	// output [7:0] TS_sig
	.trig(trig), 	// output  trig_sig
	.op(op)
);



endmodule