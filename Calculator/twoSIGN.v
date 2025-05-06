module twoSIGN #(parameter N = 8)
(
	input [N-1:0] A,
	output [N-1:0] B
);
	wire [N:0] ha;
	assign ha[0] = A[N-1];
	genvar i;
	generate
	for(i=0; i<N; i=i+1)
		begin: twosFor
		
		halfADDER a0(B[i], ha[i+1], (A[i])^(A[N-1]), ha[i]);
		
		end
	endgenerate
endmodule