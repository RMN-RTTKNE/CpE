module Calculator (
	input [3:0]row,
	output [3:0]col,
	output [6:0]H0,
	output [6:0]H1,
	output [6:0]H2,
	output H3,
	input CLK, RST, CE,
	output [3:0]F,
	output valid, sReset, sLA, sLB, sLR, sIUAU, sAS //for state debugging
);

wire [7:0]TS; 
wire [7:0]R;
reg [7:0]num;
wire trig, LA, LB, LR, AS, IUAU, RS;
assign sReset = RS; assign  sLA = LA; assign sLB = LB; assign sLR = LR; assign sIUAU = IUAU; assign sAS = AS;
wire [2:0]op;

CU CU_inst
(
	.ClearAll(RST) ,			// input  ClearAll_sig
	.CLK(CLK) ,					// input  CLK_sig
	.trig(CLK) ,				// input  trig_sig
	.ClearEntry(CE),			// input  ClearEntry_sig
	.value(op) ,				// input [1:0] value_sig
	.Reset(RS) ,				// output  Reset_sig
	.LoadA(LA) ,				// output  LoadA_sig
	.LoadB(LB) ,				// output  LoadB_sigs
	.LoadR(LR) ,				// output  LoadR_sig
	.AS(AS) ,					// output  AS_sig
	.IUAU(IUAU) 				// output  IUAU_sig
);
IU IU_inst
(
	.clk(CLK) ,		// input  clk_sig
	.rst(RS) ,		// input  rst_sig
	.row(row) ,		// input [3:0] row_sig
	.col(col) ,		// output [3:0] col_sig
	.TS(TS) ,		// output [7:0] TS_sig
	.trig(trig), 	// output  trig_sig
	.op(op),			//output op_sig
	.valid(valid)	//output valid_sig
);

ArithmeticUnit ArithmeticUnit_inst
(
	.X(TS) ,					// input [7:0] X_sig
	.InA(LA) ,				// input  InA_sig
	.InB(LB) ,				// input  InB_sig
	.Out(LR) ,				// input  Out_sig
	.Clear(RST) ,			// input  Clear_sig
	.Add_Subtract(AS) ,	// input  Add_Subtract_sig
	.Result(R) ,			// output [7:0] Result_sig
	.Flags(F) 				// output [3:0] Flags_sig 0 is zero and 1 is ovr
);

OU OU_inst
(
	.A(num) ,		// input [7:0] A_sig
	.HEX0(H0) ,		// output [6:0] HEX0_sig
	.HEX1(H1) ,		// output [6:0] HE X1_sig
	.HEX2(H2) ,		// output [6:0] HEX2_sig
	.HEX3_g(H3) 	// output  HEX3_g_sig
);

always @(IUAU) begin
if(IUAU) num = R; else num = TS;
end
endmodule


