module tenHzClk
(
	input clock, reset,
	output TenHz
);
		wire TenMHz, TenkHz;
		wire [2:0] count;
		
		divideXN #(5, 4) 			 div5 		 (clock, 	reset, count[0] ,TenMHz);
		divideXN #(1000, 4'd10)  div1000a    (TenMHz, 	reset, count[1], TenkHz);
		divideXN #(1000, 4'd10)  div1000b    (TenkHz, 	reset, count[2], TenHz);
		
endmodule