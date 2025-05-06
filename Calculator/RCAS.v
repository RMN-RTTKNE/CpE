module RCAS 
(
input [7:0] A, B, 
input Add_Subtract, 
output [7:0] S, 
output [3:0] Flags
);
wire [8:0] C; 
wire cout, ovr, neg, zero; 
assign C[0] = Add_Subtract; 
assign Flags = {cout, ovr, neg, zero}; 
FAbehav s0 (A[0], B[0]^C[0], C[0], S[0], C[1]); 
FAbehav s1 (A[1], B[1]^C[0], C[1], S[1], C[2]); 
FAbehav s2 (A[2], B[2]^C[0], C[2], S[2], C[3]); 
FAbehav s3 (A[3], B[3]^C[0], C[3], S[3], C[4]); 

FAbehav s4 (A[4], B[4]^C[0], C[4], S[4], C[5]); 
FAbehav s5 (A[5], B[5]^C[0], C[5], S[5], C[6]); 
FAbehav s6 (A[6], B[6]^C[0], C[6], S[6], C[7]);
FAbehav s7 (A[7], B[7]^C[0], C[7], S[7], C[8]);

assign cout = C[8]; 
assign ovr = C[8] ^ C[7];
assign neg = S[7];
assign zero = ~(S[7]|S[6]|S[5]|S[4]|S[3]|S[2]|S[1]|S[0]);

endmodule

