////////////////////////////////////////////////////////////////////////////////
// a2901 test vectors
// translated to Verilog from VHDL by Sari Coumeri 
// original VHDL obtained from the '92 High Level Synthesis Benchmarks
// January 1994
////////////////////////////////////////////////////////////////////////////////

`timescale 1 ns / 100 ps
module a2901_sim;
        reg [8:0] I;
        reg [3:0] Aadd, Badd;
        reg [3:0] D;
        wire [3:0] Y;
        reg t_RAM0, t_RAM3, t_Q0, t_Q3;
        reg CLK;
        reg C0;
        reg OEbar;
        wire C4, Gbar, Pbar, OVR, F3, F30;

        wor RAM0 = t_RAM0;
        wor RAM3 = t_RAM3;
        wor Q0 = t_Q0;
        wor Q3 = t_Q3;


        a2901 a2901_1 (I,Aadd,Badd,D,Y,RAM0,RAM3,Q0,Q3,CLK,C0,OEbar,C4,Gbar,Pbar
,OVR,F3,F30);


initial
begin
// $dumpvars;
repeat(1000)
// repeat(10)
// repeat(1)
begin

// ************************
// *                      *
// * TEST VECTORS FOR ALU *
// *                      *
// ************************
// ******** ADDITION  R + S ********
//////////////////////////

CLK = 1'b1; //	 Cycle No: 0

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 1

#1;

I = 9'b001000110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 2

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 3

#1;

I = 9'b001000110;
D = 4'b0000;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0001) $display($time,,,"Y !== 4'b0001");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 4

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 5

#1;

I = 9'b001000110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 6

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 7

#1;

I = 9'b001000110;
D = 4'b0000;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 8

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 9

#1;

I = 9'b001000110;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1110) $display($time,,,"Y !== 4'b1110");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 10

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 11

#1;

I = 9'b001000110;
D = 4'b1111;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 12

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 13

#1;

I = 9'b001000110;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 14

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 15

#1;

I = 9'b001000110;
D = 4'b1111;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 16

#1;

I = 9'b000000111;
D = 4'b0001;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 17

#1;

I = 9'b000000110;
D = 4'b0001;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0010) $display($time,,,"Y !== 4'b0010");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 18

#1;

I = 9'b000000111;
D = 4'b0010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 19

#1;

I = 9'b001000110;
D = 4'b0010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0100) $display($time,,,"Y !== 4'b0100");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 20

#1;

I = 9'b000000111;
D = 4'b0100;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 21

#1;

I = 9'b001000110;
D = 4'b0100;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1000) $display($time,,,"Y !== 4'b1000");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b1) $display($time,,,"OVR !== 1'b1");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 22

#1;

I = 9'b000000111;
D = 4'b1000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 23

#1;

I = 9'b001000110;
D = 4'b1000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b1) $display($time,,,"OVR !== 1'b1");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
// ******** SUBTRACTION S - R ********
//////////////////////////

CLK = 1'b1; //	 Cycle No: 24

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 25

#1;

I = 9'b001001110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 26

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 27

#1;

I = 9'b001001110;
D = 4'b0000;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 28

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 29

#1;

I = 9'b001001110;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 30

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 31

#1;

I = 9'b001001110;
D = 4'b1111;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0001) $display($time,,,"Y !== 4'b0001");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 32

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 33

#1;

I = 9'b001001110;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 34

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 35

#1;

I = 9'b001001110;
D = 4'b1111;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 36

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 37

#1;

I = 9'b001001110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1110) $display($time,,,"Y !== 4'b1110");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 38

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 39

#1;

I = 9'b001001110;
D = 4'b0000;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 40

#1;

I = 9'b000000111;
D = 4'b0001;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 41

#1;

I = 9'b001001110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 42

#1;

I = 9'b000000111;
D = 4'b0010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 43

#1;

I = 9'b001001110;
D = 4'b0001;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0001) $display($time,,,"Y !== 4'b0001");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 44

#1;

I = 9'b000000111;
D = 4'b0100;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 45

#1;

I = 9'b001001110;
D = 4'b0010;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0010) $display($time,,,"Y !== 4'b0010");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 46

#1;

I = 9'b000000111;
D = 4'b1000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 47

#1;

I = 9'b001001110;
D = 4'b0100;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0100) $display($time,,,"Y !== 4'b0100");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b1) $display($time,,,"OVR !== 1'b1");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
// ******** SUBTRACTION R - S ********
//////////////////////////

CLK = 1'b1; //	 Cycle No: 48

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 49

#1;

I = 9'b001010110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 50

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 51

#1;

I = 9'b001010110;
D = 4'b0000;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 52

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 53

#1;

I = 9'b001010110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 54

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 55

#1;

I = 9'b001010110;
D = 4'b0000;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0001) $display($time,,,"Y !== 4'b0001");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 56

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 57

#1;

I = 9'b001010110;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 58

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 59

#1;

I = 9'b001010110;
D = 4'b1111;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b1) $display($time,,,"Gbar !== 1'b1");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 60

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 61

#1;

I = 9'b001010110;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1110) $display($time,,,"Y !== 4'b1110");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 62

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 63

#1;

I = 9'b001010110;
D = 4'b1111;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 64

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 65

#1;

I = 9'b001010110;
D = 4'b0001;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b0) $display($time,,,"Pbar !== 1'b0");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 66

#1;

I = 9'b000000111;
D = 4'b0001;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 67

#1;

I = 9'b001010110;
D = 4'b0010;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0001) $display($time,,,"Y !== 4'b0001");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 68

#1;

I = 9'b000000111;
D = 4'b0010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 69

#1;

I = 9'b001010110;
D = 4'b0100;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0010) $display($time,,,"Y !== 4'b0010");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b0) $display($time,,,"OVR !== 1'b0");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 70

#1;

I = 9'b000000111;
D = 4'b0100;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 71

#1;

I = 9'b001010110;
D = 4'b1000;
C0 = 1'b1;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0100) $display($time,,,"Y !== 4'b0100");

if (C4 !== 1'b1) $display($time,,,"C4 !== 1'b1");

if (Gbar !== 1'b0) $display($time,,,"Gbar !== 1'b0");

if (Pbar !== 1'b1) $display($time,,,"Pbar !== 1'b1");

if (OVR !== 1'b1) $display($time,,,"OVR !== 1'b1");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
// ******** || (R || S) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 72

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 73

#1;

I = 9'b001011110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 74

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 75

#1;

I = 9'b001011110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 76

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 77

#1;

I = 9'b001011110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 78

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 79

#1;

I = 9'b001011110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
// ******** && (R && S) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 80

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 81

#1;

I = 9'b001100110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 82

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 83

#1;

I = 9'b001100110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 84

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 85

#1;

I = 9'b001100110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 86

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 87

#1;

I = 9'b001100110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
// ******** && (not(R) && S) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 88

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 89

#1;

I = 9'b001101110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 90

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 91

#1;

I = 9'b001101110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 92

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 93

#1;

I = 9'b001101110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 94

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 95

#1;

I = 9'b001101110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
// ******** XOR (R xor S) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 96

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 97

#1;

I = 9'b001110110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 98

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 99

#1;

I = 9'b001110110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 100

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 101

#1;

I = 9'b001110110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 102

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 103

#1;

I = 9'b001110110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
// ******** XNOR (R xnor S) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 104

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 105

#1;

I = 9'b001111110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 106

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 107

#1;

I = 9'b001111110;
D = 4'b0000;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (F3 !== 1'b0) $display($time,,,"F3 !== 1'b0");

if (F30 !== 1'b1) $display($time,,,"F30 !== 1'b1");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 108

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 109

#1;

I = 9'b001111110;
D = 4'b1111;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (F3 !== 1'b1) $display($time,,,"F3 !== 1'b1");

if (F30 !== 1'b0) $display($time,,,"F30 !== 1'b0");

#1;

// ************************
// ************************
// *                      *		
// * TEST VECTORS FOR t_RAM *
// *                      *
// ************************
// ******** WRITING 0's && 1's IN t_RAM LOCATIONS ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 110

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 111

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 112

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 113

#1;

I = 9'b001000100;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 114

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 115

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 116

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 117

#1;

I = 9'b001000100;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 118

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 119

#1;

I = 9'b001000100;
Aadd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 120

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 121

#1;

I = 9'b001000100;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 122

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 123

#1;

I = 9'b001000100;
Aadd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 124

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 125

#1;

I = 9'b001000100;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************	
//////////////////////////

CLK = 1'b1; //	 Cycle No: 126

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 2 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 127

#1;

I = 9'b001000100;
Aadd = 2 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 128

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 2 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 129

#1;

I = 9'b001000100;
Badd = 2 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 130

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 2 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 131

#1;

I = 9'b001000100;
Aadd = 2 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 132

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 2 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 133

#1;

I = 9'b001000100;
Badd = 2 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************	
//////////////////////////

CLK = 1'b1; //	 Cycle No: 134

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 3 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 135

#1;

I = 9'b001000100;
Aadd = 3 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 136

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 3 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 137

#1;

I = 9'b001000100;
Badd = 3 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 138

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 3 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 139

#1;

I = 9'b001000100;
Aadd = 3 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 140

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 3 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 141

#1;

I = 9'b001000100;
Badd = 3 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************	
//////////////////////////

CLK = 1'b1; //	 Cycle No: 142

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 4 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 143

#1;

I = 9'b001000100;
Aadd = 4 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 144

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 4 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 145

#1;

I = 9'b001000100;
Badd = 4 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 146

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 4 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 147

#1;

I = 9'b001000100;
Aadd = 4 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 148

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 4 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 149

#1;

I = 9'b001000100;
Badd = 4 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************					
//////////////////////////

CLK = 1'b1; //	 Cycle No: 150

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 5 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 151

#1;

I = 9'b001000100;
Aadd = 5 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 152

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 5 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 153

#1;

I = 9'b001000100;
Badd = 5 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 154

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 5 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 155

#1;

I = 9'b001000100;
Aadd = 5 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 156

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 5 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 157

#1;

I = 9'b001000100;
Badd = 5 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************	
//////////////////////////

CLK = 1'b1; //	 Cycle No: 158

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 6 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 159

#1;

I = 9'b001000100;
Aadd = 6 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 160

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 6 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 161

#1;

I = 9'b001000100;
Badd = 6 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 162

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 6 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 163

#1;

I = 9'b001000100;
Aadd = 6 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 164

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 6 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 165

#1;

I = 9'b001000100;
Badd = 6 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************			
//////////////////////////

CLK = 1'b1; //	 Cycle No: 166

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 7 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 167

#1;

I = 9'b001000100;
Aadd = 7 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 168

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 7 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 169

#1;

I = 9'b001000100;
Badd = 7 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 170

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 7 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 171

#1;

I = 9'b001000100;
Aadd = 7 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 172

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 7 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 173

#1;

I = 9'b001000100;
Badd = 7 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 174

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 8 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 175

#1;

I = 9'b001000100;
Aadd = 8 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 176

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 8 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 177

#1;

I = 9'b001000100;
Badd = 8 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 178

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 8 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 179

#1;

I = 9'b001000100;
Aadd = 8 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 180

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 8 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 181

#1;

I = 9'b001000100;
Badd = 8 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 182

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 9 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 183

#1;

I = 9'b001000100;
Aadd = 9 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 184

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 9 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 185

#1;

I = 9'b001000100;
Badd = 9 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 186

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 9 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 187

#1;

I = 9'b001000100;
Aadd = 9 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 188

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 9 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 189

#1;

I = 9'b001000100;
Badd = 9 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 190

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 10 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 191

#1;

I = 9'b001000100;
Aadd = 10 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 192

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 10 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 193

#1;

I = 9'b001000100;
Badd = 10 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 194

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 10 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 195

#1;

I = 9'b001000100;
Aadd = 10 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 196

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 10 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 197

#1;

I = 9'b001000100;
Badd = 10 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 198

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 11 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 199

#1;

I = 9'b001000100;
Aadd = 11 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 200

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 11 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 201

#1;

I = 9'b001000100;
Badd = 11 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 202

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 11 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 203

#1;

I = 9'b001000100;
Aadd = 11 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 204

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 11 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 205

#1;

I = 9'b001000100;
Badd = 11 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 206

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 12 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 207

#1;

I = 9'b001000100;
Aadd = 12 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 208

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 12 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 209

#1;

I = 9'b001000100;
Badd = 12 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 210

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 12 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 211

#1;

I = 9'b001000100;
Aadd = 12 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 212

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 12 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 213

#1;

I = 9'b001000100;
Badd = 12 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 214

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 13 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 215

#1;

I = 9'b001000100;
Aadd = 13 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 216

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 13 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 217

#1;

I = 9'b001000100;
Badd = 13 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 218

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 13 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 219

#1;

I = 9'b001000100;
Aadd = 13 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 220

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 13 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 221

#1;

I = 9'b001000100;
Badd = 13 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 222

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 14 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 223

#1;

I = 9'b001000100;
Aadd = 14 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 224

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 14 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 225

#1;

I = 9'b001000100;
Badd = 14 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 226

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 14 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 227

#1;

I = 9'b001000100;
Aadd = 14 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 228

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 14 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 229

#1;

I = 9'b001000100;
Badd = 14 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 230

#1;

I = 9'b010000111;
D = 4'b0000;
Badd = 15 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 231

#1;

I = 9'b001000100;
Aadd = 15 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 232

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 15 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 233

#1;

I = 9'b001000100;
Badd = 15 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 234

#1;

I = 9'b010000111;
D = 4'b1111;
Badd = 15 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 235

#1;

I = 9'b001000100;
Aadd = 15 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 236

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 15 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 237

#1;

I = 9'b001000100;
Badd = 15 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
// ******** TESTING t_RAM SHIFTERS ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 238

#1;

I = 9'b100000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;
t_RAM0 = 1'bz;
t_RAM3 = 1'b1;

#4;

CLK = 1'b0;

#4;

if (RAM0 !== 1'b0) $display($time,,,"RAM0 !== 1'b0");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 239

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1000) $display($time,,,"Y !== 4'b1000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 240

#1;

I = 9'b100000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;
t_RAM0 = 1'bz;
t_RAM3 = 1'b0;

#4;

CLK = 1'b0;

#4;

if (RAM0 !== 1'b1) $display($time,,,"RAM0 !== 1'b1");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 241

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0111) $display($time,,,"Y !== 4'b0111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 242

#1;

I = 9'b101000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;
t_RAM0 = 1'bz;
t_RAM3 = 1'b1;

#4;

CLK = 1'b0;

#4;

if (RAM0 !== 1'b0) $display($time,,,"RAM0 !== 1'b0");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 243

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1000) $display($time,,,"Y !== 4'b1000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 244

#1;

I = 9'b101000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;
t_RAM0 = 1'bz;
t_RAM3 = 1'b0;

#4;

CLK = 1'b0;

#4;

if (RAM0 !== 1'b1) $display($time,,,"RAM0 !== 1'b1");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 245

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0111) $display($time,,,"Y !== 4'b0111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 246

#1;

I = 9'b110000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;
t_RAM0 = 1'b1;
t_RAM3 = 1'bz;

#4;

CLK = 1'b0;

#4;

if (RAM3 !== 1'b0) $display($time,,,"RAM3 !== 1'b0");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 247

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0001) $display($time,,,"Y !== 4'b0001");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 248

#1;

I = 9'b110000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;
t_RAM0 = 1'b0;
t_RAM3 = 1'bz;

#4;

CLK = 1'b0;

#4;

if (RAM3 !== 1'b1) $display($time,,,"RAM3 !== 1'b1");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 249

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1110) $display($time,,,"Y !== 4'b1110");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 250

#1;

I = 9'b111000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;
t_RAM0 = 1'b1;
t_RAM3 = 1'bz;

#4;

CLK = 1'b0;

#4;

if (RAM3 !== 1'b0) $display($time,,,"RAM3 !== 1'b0");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 251

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0001) $display($time,,,"Y !== 4'b0001");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 252

#1;

I = 9'b111000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;
t_RAM0 = 1'b0;
t_RAM3 = 1'bz;

#4;

CLK = 1'b0;

#4;

if (RAM3 !== 1'b1) $display($time,,,"RAM3 !== 1'b1");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 253

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1110) $display($time,,,"Y !== 4'b1110");

#1;

// ************************
// *******************************		
// *                             *
// * TEST VECTORS FOR Q-REGISTER *
// *                             *
// *******************************		
// ******** WRITING 0's && 1's ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 254

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 255

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 256

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 257

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************		
// ******** TESTING Q-REGISTER SHIFTERS ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 258

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 259

#1;

I = 9'b100000111;
C0 = 1'b0;
OEbar = 1'b0;
t_Q0 = 1'bz;
t_Q3 = 1'b1;

#4;

CLK = 1'b0;

#4;

if (Q0 !== 1'b0) $display($time,,,"Q0 !== 1'b0");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 260

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1000) $display($time,,,"Y !== 4'b1000");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 261

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 262

#1;

I = 9'b100000111;
C0 = 1'b0;
OEbar = 1'b0;
t_Q0 = 1'bz;
t_Q3 = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Q0 !== 1'b1) $display($time,,,"Q0 !== 1'b1");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 263

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0111) $display($time,,,"Y !== 4'b0111");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 264

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 265

#1;

I = 9'b110000111;
C0 = 1'b0;
OEbar = 1'b0;
t_Q0 = 1'b1;
t_Q3 = 1'bz;

#4;

CLK = 1'b0;

#4;

if (Q3 !== 1'b0) $display($time,,,"Q3 !== 1'b0");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 266

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0001) $display($time,,,"Y !== 4'b0001");

#1;

// ************************		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 267

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 268

#1;

I = 9'b110000111;
C0 = 1'b0;
OEbar = 1'b0;
t_Q0 = 1'b0;
t_Q3 = 1'bz;

#4;

CLK = 1'b0;

#4;

if (Q3 !== 1'b1) $display($time,,,"Q3 !== 1'b1");

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 269

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1110) $display($time,,,"Y !== 4'b1110");

#1;

// ************************		
// ****************************************
// *                                      *
// * TEST VECTORS FOR ALU SOURCE-SELECTOR *
// *                                      *
// ****************************************
// ******** TESTING FOR ALU SOURCE-SELECT ( R == A, S == Q) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 270

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 271

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 272

#1;

I = 9'b001000000;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 273

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 274

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 275

#1;

I = 9'b001000000;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
// ******** TESTING FOR ALU SOURCE-SELECT ( R == A, S == B) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 276

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 277

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 278

#1;

I = 9'b001000001;
Aadd = 0 ;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 279

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 280

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 281

#1;

I = 9'b001000001;
Aadd = 0 ;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
// ******** TESTING FOR ALU SOURCE-SELECT ( R == 0, S == Q) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 282

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 283

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 284

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 285

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
// ******** TESTING FOR ALU SOURCE-SELECT ( R == 0, S == B) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 286

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 287

#1;

I = 9'b001000011;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 288

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 289

#1;

I = 9'b001000011;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
// ******** TESTING FOR ALU SOURCE-SELECT ( R == 0, S == A) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 290

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 291

#1;

I = 9'b001000100;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 292

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 293

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
// ******** TESTING FOR ALU SOURCE-SELECT ( R == D, S == A) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 294

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 295

#1;

I = 9'b001000101;
D = 4'b1111;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 296

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 297

#1;

I = 9'b001000101;
D = 4'b0000;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
// ******** TESTING FOR ALU SOURCE-SELECT ( R == D, S == Q) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 298

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 299

#1;

I = 9'b001000110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 300

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 301

#1;

I = 9'b001000110;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

if (C4 !== 1'b0) $display($time,,,"C4 !== 1'b0");

#1;

// ************************
// ******** TESTING FOR ALU SOURCE-SELECT ( R == D, S == 0) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 302

#1;

I = 9'b001000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 303

#1;

I = 9'b001000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// ************************************
// *                                  *
// * TEST VECTORS FOR OUTPUT-SELECTOR *
// *                                  *
// ************************************
// ******** TESTING OUTPUT FOR (I8 I7 I6 == 000) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 304

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 305

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 306

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b1;

#4;

CLK = 1'b0;

#4;


#1;

// ************************
// ******** TESTING OUTPUT FOR (I8 I7 I6 == 001) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 307

#1;

I = 9'b001000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 308

#1;

I = 9'b001000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 309

#1;

I = 9'b001000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b1;

#4;

CLK = 1'b0;

#4;


#1;

// ************************
// ******** TESTING OUTPUT FOR (I8 I7 I6 == 010) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 310

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 311

#1;

I = 9'b010000111;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 312

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 313

#1;

I = 9'b010000111;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 314

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 315

#1;

I = 9'b010000111;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b1;

#4;

CLK = 1'b0;

#4;


#1;

// ************************
// ******** TESTING OUTPUT FOR (I8 I7 I6 == 011) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 316

#1;

I = 9'b011000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 317

#1;

I = 9'b011000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 318

#1;

I = 9'b011000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b1;

#4;

CLK = 1'b0;

#4;


#1;

// ************************
// ******** TESTING OUTPUT FOR (I8 I7 I6 == 100) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 319

#1;

I = 9'b100000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 320

#1;

I = 9'b100000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 321

#1;

I = 9'b100000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b1;

#4;

CLK = 1'b0;

#4;


#1;

// ************************
// ******** TESTING OUTPUT FOR (I8 I7 I6 == 101) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 322

#1;

I = 9'b101000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 323

#1;

I = 9'b101000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 324

#1;

I = 9'b101000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b1;

#4;

CLK = 1'b0;

#4;


#1;

// ************************
// ******** TESTING OUTPUT FOR (I8 I7 I6 == 110) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 325

#1;

I = 9'b110000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 326

#1;

I = 9'b110000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 327

#1;

I = 9'b110000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b1;

#4;

CLK = 1'b0;

#4;


#1;

// ************************
// ******** TESTING OUTPUT FOR (I8 I7 I6 == 111) ********		
//////////////////////////

CLK = 1'b1; //	 Cycle No: 328

#1;

I = 9'b111000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 329

#1;

I = 9'b111000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 330

#1;

I = 9'b111000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b1;

#4;

CLK = 1'b0;

#4;


#1;

// ************************
// **************************
// *                        *
// * TEST VECTORS FOR PATHS *
// *                        *
// **************************
// ******** TESTING PATHS ( "ALU-SOURCES" //> F //> Q ) ********
// * * * * PATH TEST WITH ALU-SOURCE ( R == A , S == Q ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 331

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 332

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 333

#1;

I = 9'b000011000;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 334

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 335

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 336

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 337

#1;

I = 9'b000100000;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 338

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == A , S == B ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 339

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 340

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 341

#1;

I = 9'b000011001;
Aadd = 0 ;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 342

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 343

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 344

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 345

#1;

I = 9'b000100001;
Aadd = 0 ;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 346

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == 0 , S == Q ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 347

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 348

#1;

I = 9'b000011010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 349

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 350

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 351

#1;

I = 9'b000011010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 352

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == 0 , S == B ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 353

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 354

#1;

I = 9'b000011011;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 355

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 356

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 357

#1;

I = 9'b000011011;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 358

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == 0 , S == A ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 359

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 360

#1;

I = 9'b000011100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 361

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 362

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 363

#1;

I = 9'b000011100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 364

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == D , S == A ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 365

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 366

#1;

I = 9'b000011101;
D = 4'b0000;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 367

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 368

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 369

#1;

I = 9'b000100101;
D = 4'b1111;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 370

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == D , S == Q ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 371

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 372

#1;

I = 9'b000011110;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 373

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 374

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 375

#1;

I = 9'b000100110;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 376

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == D , S == 0 ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 377

#1;

I = 9'b000011111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 378

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == D , S == 0 ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 379

#1;

I = 9'b000011111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 380

#1;

I = 9'b001000010;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// ******** TESTING PATHS ( "ALU-SOURCES" //> F //> B ) ********
// * * * * PATH TEST WITH ALU-SOURCE ( R == A , S == Q ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 381

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 382

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 383

#1;

I = 9'b011011000;
Aadd = 0 ;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 384

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 385

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 386

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 387

#1;

I = 9'b011100000;
Aadd = 0 ;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 388

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == A , S == B ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 389

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 390

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 391

#1;

I = 9'b011011001;
Aadd = 1 ;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 392

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 393

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 394

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 1 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 395

#1;

I = 9'b011100001;
Aadd = 1 ;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 396

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == 0 , S == Q ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 397

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 398

#1;

I = 9'b011011010;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 399

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 400

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 401

#1;

I = 9'b011011010;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 402

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == 0 , S == B ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 403

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 404

#1;

I = 9'b011011011;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 405

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 406

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 407

#1;

I = 9'b011011011;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 408

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == 0 , S == A ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 409

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 410

#1;

I = 9'b011011100;
Aadd = 0 ;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 411

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 412

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 413

#1;

I = 9'b011011100;
Aadd = 0 ;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 414

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == D , S == A ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 415

#1;

I = 9'b011000111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 416

#1;

I = 9'b011011101;
D = 4'b0000;
Aadd = 0 ;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 417

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 418

#1;

I = 9'b011000111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 419

#1;

I = 9'b011100101;
D = 4'b1111;
Aadd = 0 ;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 420

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == D , S == Q ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 421

#1;

I = 9'b000000111;
D = 4'b0000;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 422

#1;

I = 9'b011011110;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 423

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 424

#1;

I = 9'b000000111;
D = 4'b1111;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 425

#1;

I = 9'b011100110;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 426

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
// * * * * PATH TEST WITH ALU-SOURCE ( R == D , S == 0 ) * * * *
//////////////////////////

CLK = 1'b1; //	 Cycle No: 427

#1;

I = 9'b011011111;
D = 4'b0000;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 428

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b0000) $display($time,,,"Y !== 4'b0000");

#1;

// ************************
//////////////////////////

CLK = 1'b1; //	 Cycle No: 429

#1;

I = 9'b011011111;
D = 4'b1111;
Badd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

#1;

//////////////////////////

CLK = 1'b1; //	 Cycle No: 430

#1;

I = 9'b001000100;
Aadd = 0 ;
C0 = 1'b0;
OEbar = 1'b0;

#4;

CLK = 1'b0;

#4;

if (Y !== 4'b1111) $display($time,,,"Y !== 4'b1111");

#1;

// ************************
//////////////////////////

end
$finish(2);
end
endmodule

