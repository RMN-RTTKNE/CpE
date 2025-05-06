module keypad_input #(parameter DIGITS = 4)
(
	input clk,
	input reset,
	input [3:0] row,
	output [3:0] col,
	output [(DIGITS*4)-1:0] out,
	output [3:0] value,
	output trig,
	output [2:0]op
);

	keypad_base keypad_base(
			.clk(clk),
			.row(row),
			.col(col),
			.value(value),
			.valid(trig),
			.op(op)
	);
	
	shift_reg #(.COUNT(DIGITS)) shift_reg(
		.trig(trig),
		.in(value),
		.out(out),
		.reset(reset)
	);
	
endmodule 