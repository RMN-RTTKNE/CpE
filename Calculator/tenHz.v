module tenHz
(
	input clock, reset, switch,
	output tenHz
);
	wire freq;
	OnOffToggle t0 (switch, clock, freq);
	tenHzClk c0 (freq, reset, tenHz);
endmodule 