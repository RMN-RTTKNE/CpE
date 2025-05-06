module ArithmeticUnit
(
input [7:0] X, 
input InA, InB, Out, Clear, Add_Subtract,
output [7:0] Result, 
output [3:0] Flags,
output [0:6] HEX2, HEX1, HEX0 
);
wire [7:0] Aout, Bout, Rout;
wire [3:0] Fout; 


NBitRegister #(8) s0 (X[7:0] , InA, Clear, Aout[7:0]);

NBitRegister #(8) s1 (X[7:0] , InB, Clear, Bout[7:0]);


RCAS s2 (Aout[7:0], Bout[7:0], Add_Subtract, Result[7:0], Flags[3:0]);


NBitRegister #(4) s3 (Flags[3:0], Out, Clear, Fout[3:0]);


NBitRegister #(8) s4 (Result[7:0], Out, Clear, Rout[7:0]);


binary2seven s5 (Rout[3:0], HEX0[0:6]);

binary2seven s6 (Rout[7:4], HEX1[0:6]);


binary2seven s7 (Fout[3:0], HEX2[0:6]);

endmodule