module CU
(
	input ClearAll, CLK, trig, ClearEntry,
	input [2:0]value,
	output reg Reset, LoadA, LoadB, LoadR, AS, IUAU
);

reg [2:0] state;
reg [2:0]invalue = 3'b000;

parameter S0 = 3'b000;
parameter S1 = 3'b001;
parameter S2 = 3'b010;
parameter S3 = 3'b011;
parameter S4 = 3'b100;
parameter S5 = 3'b101;
parameter S6 = 3'b110;

always @(posedge trig, negedge ClearAll)
begin 
	if(ClearAll == 0) begin
		state <= S0;
		invalue <= 0;
		end  
		else
	begin 
		invalue <= value;
		case(state)
			S0: begin state <= S1; end 
			S1: begin if(invalue == 2 || invalue == 3) begin state <= S2; end else state <= S1; end
			S2: begin state <= S3; end
			S3: begin state <= S4; end
			S4: begin if(invalue == 4) begin state <= S5; end else state <= S4; end
			S5: begin state <= S6; end
			S6: begin state <= S6 ; end
		endcase
	end
end

always @(state)
begin
	case(state)
	
		S0: begin Reset = 0 & ClearEntry; LoadA = 1; LoadB = 1; LoadR = 1; IUAU = 0; AS = 0; end //clear iu
		
		S1: begin Reset = 1 & ClearEntry; LoadA = 1; LoadB = 1; LoadR = 1; IUAU = 0; AS = invalue[0]; end	//enter a
		
		S2: begin Reset = 1 & ClearEntry; LoadA = 0; LoadB = 1; LoadR = 1; IUAU = 0; AS = AS; end //load a
		
		S3: begin Reset = 0 & ClearEntry; LoadA = 1; LoadB = 1; LoadR = 1; IUAU = 0; AS = AS; end //clear iu
		
		S4: begin Reset = 1 & ClearEntry; LoadA = 1; LoadB = 1; LoadR = 1; IUAU = 0; AS = AS; end //enter b
		
		S5: begin Reset = 1 & ClearEntry; LoadA = 1; LoadB = 0; LoadR = 1; IUAU = 0; AS = AS; end //load b
		 
		S6: begin Reset = 1 & ClearEntry; LoadA = 1; LoadB = 1; LoadR = 0; IUAU = 1; AS = AS; end //load r
		
	endcase
end

endmodule