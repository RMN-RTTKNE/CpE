module oneHz (
input clk, rst,
output one);
wire TenM, OneM, Onek;
wire [1:0]c;
divideXN # (1000, 4'd10) div1000a (clk, rst, c[0], Onek);
divideXN # (1000, 4'd10) div1000b (Onek, rst, c[1], one);

endmodule 