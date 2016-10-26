////////////////////////////////////////////////////////////////////////////////
// single process a2901
// translated to Verilog from VHDL by Sari Coumeri 
// original VHDL obtained from the '92 High Level Synthesis Benchmarks
// January 1994
////////////////////////////////////////////////////////////////////////////////


`timescale 1 ns / 100 ps
module a2901(I,Aadd,Badd,D,Y,RAM0,RAM3,Q0,Q3,CLK,C0,OEbar,C4,Gbar,Pbar,OVR,F3,F30);

        input [8:0] I;
        input [3:0] Aadd, Badd;
        input [3:0] D;
        output [3:0] Y;
        reg [3:0] Y;
        inout RAM0, RAM3, Q0, Q3;
        reg t_RAM0, t_RAM3, t_Q0, t_Q3;
        input CLK, C0, OEbar;
        output C4, Gbar, Pbar, OVR, F3, F30;
        reg C4, Gbar, Pbar, OVR, F3, F30;

        reg [3:0] RAM [15:0];
        reg [3:0] RE, S, A, B, Q, F, dout;

        reg [4:0] R_ext,S_ext,result,temp_p,temp_g;
        wire RAM0 = t_RAM0;
        wire RAM3 = t_RAM3;
        wire Q0 = t_Q0;
        wire Q3 = t_Q3;
		

always @(negedge CLK)
begin

      A = RAM[Aadd];  // RAM OUTPUTS ( ADDRESSED BY Aadd & Badd ) ARE 
      B = RAM[Badd];  //  MADE AVAILABLE TO ALU SOURCE SELECTOR

// SELECT THE SOURCE OPERANDS FOR ALU. SELECTED OPERANDS ARE "RE" & "S".

      case (I[2:0])
           3'b000:
begin

			RE = A;
			S = Q;
end
           3'b001:
begin

			RE = A;
			S = B;
end
           3'b010:
begin

			RE = 4'b0000;
			S = Q;
end
           3'b011:
begin
 
			RE = 4'b0000;
			S = B;
end
           3'b100:
begin

			RE = 4'b0000;
			S = A;
end
           3'b101:
begin

			RE = D;
			S = A;
end
           3'b110:
begin

			RE = D;
			S = Q;
end
      	   3'b111:
begin
 
			RE = D;
			S = 4'b0000;
end
           default: ;
     endcase

// SELECT THE FUNCTION FOR ALU.

//   TO FACILITATE COMPUTATION OF CARRY-OUT "C4", WE EXTEND THE CHOSEN 
//   ALU OPERANDS "RE" & "S" (4 BIT OPERANDS) BY 1 BIT IN THE MSB POSITION. 

//   THUS THE EXTENDED OPERANDS "R_EXT" & "S_EXT" (5 BIT OPERANDS) ARE
//   FORMED & ARE//   INITIALLY. THE ALU'S EXTENDED OUTPUT ( 5 BITS LONG) IS "result".

//   IN THE ADD/SUBTRACT OPERATIONS, THE CARRY-INPUT "C0" (1 BIT) IS EXTENDED
//   BY 4 BITS ( ALL 1'b0) IN THE MORE SIGNIFICANT BITS TO MATCH ITS LENGTH TO
//   THAT OF "R_ext" & "S_ext". THEN, THESE THREE OPERANDS ARE ADDED.

//   ADD/SUBTRACT OPERATIONS ARE DONE ON 2'S COMPLEMENT OPERANDS.

	case (I[5:3]) 
	   3'b000:
begin

                        R_ext = {1'b0,RE};
                        S_ext = {1'b0,S};
                        result = R_ext + S_ext + {4'b0000,C0};
end
       	   3'b001:
begin

                        R_ext = {1'b0,~(RE)};
                        S_ext = {1'b0,S};                  
                        result = R_ext + S_ext + {4'b0000,C0};
end
           3'b010:
begin

                        R_ext = {1'b0,RE};
                        S_ext = {1'b0,~(S)};
                        result = R_ext + S_ext + {4'b0000,C0};
end
	   3'b011:
begin
            
                        R_ext = {1'b0,RE};
                        S_ext = {1'b0,S};
			result = R_ext | S_ext;
end
           3'b100:
begin
 
                        R_ext = {1'b0,RE};
                        S_ext = {1'b0,S};
			result = R_ext & S_ext;
end
     	   3'b101:
begin
 
                        R_ext = {1'b0,RE};
                        S_ext = {1'b0,S};
			result = ~(R_ext) & S_ext;
end
	   3'b110:
begin

                        R_ext = {1'b0,RE};
                        S_ext = {1'b0,S};
			result = R_ext ^ S_ext;
end
           3'b111:
begin
 
                        R_ext = {1'b0,RE};
                        S_ext = {1'b0,S};
                        result = ~(R_ext ^ S_ext);
end
           default: ;
	endcase


// EVALUATE OTHER ALU OUTPUTS.

//  FROM EXTENDED OUTPUT "result" ( 5 BITS), WE OBTAIN THE NORMAL ALU OUTPUT,
//  "F" (4 BITS) BY LEAVING OUT THE MSB ( WHICH CORRESPONDS TO CARRY-OUT
//  "C4"). 

//  TO FACILITATE COMPUTATION OF CARRY LOOKAHEAD TERMS "Pbar" & "Gbar", WE
//  COMPUTE INTERMEDIATE TERMS "temp_p" & "temp_g".

        C4 = result[4] ;                                            
        OVR = ~ (R_ext[3] ^ S_ext[3]) &
                              (R_ext[3] ^ result[3]) ;
        F = result[3:0] ;
       temp_p = R_ext[3:0] | S_ext[3:0];
        temp_g = R_ext[3:0] & S_ext[3:0];
        Pbar = ~( temp_p[0] & temp_p[1] & temp_p[2] & temp_p[3] ) ;
        Gbar = ~(  temp_g[3] | 
                     ( temp_p[3] & temp_g[2] ) | 
                     (temp_p[3] & temp_p[2] & temp_g[1] ) |
	             (temp_p[3] & temp_p[2] & temp_p[1] & temp_g[0] ) 
                   );
        F3 = result[3] ;
        F30 = ~( result[3] | result[2] | result[1] | result[0] ) ;


// GENERATE INTERMEDIATE OUTPUT "dout" & BIDIRECTIONAL SHIFTER SIGNALS.

// WRITE TO DESTINATION(S) WITH/WITHOUT SHIFTING. RAM DESTINATIONS ARE 
// ADDRESSED BY "Badd".

 	case (I[8:6]) 
           3'b000:
begin

                        dout = F;           // INTERMEDIATE OUTPUT

			Q = F;              // WRITE TO DESTINATION

                        t_Q0 = 1'bz;
                        t_Q3 = 1'bz;
                        t_RAM0 = 1'bz;
                        t_RAM3 = 1'bz;

end
           3'b001:
begin

                        dout = F;

                        t_Q0 = 1'bz;
                        t_Q3 = 1'bz;
                        t_RAM0 = 1'bz;
                        t_RAM3 = 1'bz;

end
	   3'b010:
begin

                        dout = A;

			RAM[Badd] = F;

                        t_Q0 = 1'bz;
                        t_Q3 = 1'bz;
                        t_RAM0 = 1'bz;
                        t_RAM3 = 1'bz;

end
	   3'b011:
begin

                        dout = F;

			RAM[Badd] = F;

                        t_Q0 = 1'bz;
                        t_Q3 = 1'bz;
                        t_RAM0 = 1'bz;
                        t_RAM3 = 1'bz;

end
	   3'b100:
begin

                        dout = F;

			RAM[Badd] = {RAM3,F[3:1]};
			Q = {Q3,Q[3:1]};

                        t_Q3 = 1'bz;
                        t_RAM3 = 1'bz;
			t_RAM0 = F[0] ;       // SHIFTER SIGNALS
			t_Q0 = Q[0] ;

end
	   3'b101:
begin
 
                        dout = F;

			RAM[Badd] = {RAM3,F[3:1]};
                        t_Q0 = 1'bz;
                        t_Q3 = 1'bz;
                        t_RAM3 = 1'bz;
			t_RAM0 = F[0] ;

end
 	   3'b110:
begin
 
                        dout = F;

			RAM[Badd] = {F[2:0],RAM0};
			Q = {Q[2:0],Q0};

                        t_Q0 = 1'bz;
                        t_RAM0 = 1'bz;
			t_RAM3 = F[3] ;
			t_Q3 = Q[3] ;

end
           3'b111:
begin
 
                        dout = F;

			RAM[Badd] = {F[2:0],RAM0};

                        t_Q0 = 1'bz;
                        t_Q3 = 1'bz;
                        t_RAM0 = 1'bz;
			t_RAM3 = F[3] ;

end
           default: ;

 	endcase

// GENERATE DATA OUTPUT "Y" FROM INTERMEDIATE OUTPUT "dout".

        if( (OEbar == 1'b0) )
begin

           Y = dout;
        end
else
begin
 
           Y = 4'bzzzz;
       	end

  end

endmodule






