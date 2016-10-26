////////////////////////////////////////////////////////////////////////////////
// Partitioned a2901
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
        reg [3:0] RE, S, A, B, Q, F;

	reg [4:0] R_ext,S_ext,result,temp_p,temp_g;
	wire RAM0 = t_RAM0;
	wire RAM3 = t_RAM3;
	wire Q0 = t_Q0;
	wire Q3 = t_Q3;


always @(RAM[Aadd] or RAM[Badd] or I[2:0] or Aadd or D or Badd or Q) 
begin : alu_inputs 

A = RAM[Aadd];
B = RAM[Badd];

// SELECT THE SOURCE OPERANDS FOR ALU. SELECTED OPERANDS ARE "RE" && "S".

case (I[2:0])
  3'b000,3'b001: RE = A;
  3'b010,3'b011,3'b100: RE = 4'b0000;
  default: RE = D;
endcase

case (I[2:0])
  3'b100, 3'b101: S = A;
  3'b001, 3'b011: S = B; 
  3'b111: S = 4'b0000;
  default: S = Q;
endcase

end


always @(I[5:3] or RE or S or C0)
begin : alu

//   TO FACILITATE COMPUTATION OF CARRY-OUT "C4", WE EXTEND THE CHOSEN 
//   ALU OPERANDS "RE" && "S" (4 BIT OPERANDS) BY 1 BIT IN THE MSB POSITION. 

//   THUS THE EXTENDED OPERANDS "R_EXT" && "S_EXT" (5 BIT OPERANDS) ARE
//   FORMED && ARE//   INITIALLY. THE ALU'S EXTENDED OUTPUT ( 5 BITS LONG) IS "result".

R_ext = (I[5:3] == 3'b001) ? {1'b0,~(RE)} : {1'b0,RE};
S_ext = (I[5:3] == 3'b010) ? {1'b0,~(S)} :  {1'b0,S};

// SELECT THE FUNCTION FOR ALU.

//   IN THE ADD/SUBTRACT OPERATIONS, THE CARRY-INPUT "C0" (1 BIT) IS EXTENDED
//   BY 4 BITS ( ALL 1'b0) IN THE MORE SIGNIFICANT BITS TO MATCH ITS LENGTH TO
//   THAT OF "R_ext" && "S_ext". THEN, THESE THREE OPERANDS ARE ADDED.

//   ADD/SUBTRACT OPERATIONS ARE DONE ON 2'S COMPLEMENT OPERANDS.

case (I[5:3])
  3'b000, 3'b001, 3'b010: result = R_ext + S_ext + {4'b0000,C0};
  3'b011: result = R_ext | S_ext; 
  3'b100: result = R_ext & S_ext;
  3'b101: result = ~(R_ext) & S_ext;
  3'b110: result = R_ext ^ S_ext;
  default: result = ~( R_ext ^ S_ext);
endcase

// EVALUATE OTHER ALU OUTPUTS.

//  FROM EXTENDED OUTPUT "result" ( 5 BITS), WE OBTAIN THE NORMAL ALU OUTPUT,
//  "F" (4 BITS) BY LEAVING OUT THE MSB ( WHICH CORRESPONDS TO CARRY-OUT
//  "C4"). 

//  TO FACILITATE COMPUTATION OF CARRY LOOKAHEAD TERMS "Pbar" && "Gbar", WE
//  COMPUTE INTERMEDIATE TERMS "temp_p" && "temp_g".

F = result[3:0];
OVR = !(R_ext[3] ^ S_ext[3]) &&
                           ( R_ext[3] ^ result[3] );
C4 = result[4];
temp_p = R_ext | S_ext;          // R || S may get
temp_g = R_ext & S_ext;         // inverted (sub)
Pbar = !(temp_p[0] && temp_p[1] && temp_p[2] && temp_p[3]);
Gbar = !( temp_g[3] ||
             (temp_p[3] && temp_g[2]) || 
             (temp_p[3] && temp_p[2] && temp_g[1]) ||
             (temp_p[3] && temp_p[2] && temp_p[1] && temp_g[0])
           );
F3 = result[3];
F30 = !(result[3] || result[2] || result[1] || result[0]);

end 


always @(posedge CLK)
begin : mem

// WRITE TO RAM WITH/WITHOUT SHIFTING. RAM DESTINATIONS ARE 
// ADDRESSED BY "Badd".
        
RAM[Badd] = ((!(I[8]) & I[7]) == 1'b1) ? F :
            ((I[8] & !(I[7])) == 1'b1) ? {RAM3,F[3:1]} :
            ((I[8] & I[7]) == 1'b1) ? {F[2:0],RAM0} : 
	    RAM[Badd];
end 


always @(posedge CLK)
begin : Q_reg

// WRITE TO Q REGISTER WITH/WITHOUT SHIFTING. 
        
Q = (I[8:6] == 3'b000) ? F :
    (I[8:6] == 3'b100) ? {Q3,Q[3:1]} :
    (I[8:6] == 3'b110) ? {Q[2:0],Q0} :
     Q;

end 


always @(I[8:6] or OEbar or A or F or Q)
begin : output_and_shifter

// GENERATE DATA OUTPUT "Y" 
   
Y = (( I[8:6] == 3'b010) && ( OEbar == 1'b0)) ? A :
     (!(I[8:6] == 3'b010) && ( OEbar == 1'b0)) ? F :
     4'bzzzz;

// GENERATE BIDIRECTIONAL SHIFTER SIGNALS.

t_RAM0 = (( I[8] == 1'b1) && ( I[7] == 1'b0 )) ? F[0] : 
       1'bz;             
t_RAM3 = (( I[8] == 1'b1) && ( I[7] == 1'b1 )) ? F[3] :
       1'bz;           
t_Q3 = (( I[8] == 1'b1) && ( I[7] == 1'b1)) ? Q[3] :
       1'bz;         
t_Q0 = (( I[8] == 1'b1) && ( I[7] == 1'b0)) ? Q[0] :
       1'bz;         

end 


endmodule








