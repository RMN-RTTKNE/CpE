module OU
(
	input [7:0] A,
	output [6:0] HEX0, HEX1, HEX2,
	output HEX3_g
);
	wire [7:0] C;
	wire [3:0] ones, tens;
	wire [1:0] hund;

	wire [6:0] tens_segments, hund_segments;
	wire [6:0] tens_final, hund_final;

	twoSIGN t0(A[7:0], C[7:0]);
	binary2bcd b0(C[7:0], ones[3:0], tens[3:0], hund[1:0]);

	bcd2seven s0(ones[3], ones[2], ones[1], ones[0], HEX0[0], HEX0[1], HEX0[2], HEX0[3], HEX0[4], HEX0[5], HEX0[6]);

	bcd2seven s1(tens[3], tens[2], tens[1], tens[0], tens_segments[0], tens_segments[1], tens_segments[2], tens_segments[3], tens_segments[4], tens_segments[5], tens_segments[6]);
	bcd2seven s2(0, 0, hund[1], hund[0], hund_segments[0], hund_segments[1], hund_segments[2], hund_segments[3], hund_segments[4], hund_segments[5], hund_segments[6]);

	assign tens_final = (tens[3] || tens[2] || tens[1] || tens[0] || hund[1] || hund[0]) ? tens_segments : 7'b1111111;
	assign hund_final = (hund[1] || hund[0]) ? hund_segments : 7'b1111111;

	assign HEX1 = tens_final;
	assign HEX2 = hund_final;

	assign HEX3_g = !A[7];
endmodule
