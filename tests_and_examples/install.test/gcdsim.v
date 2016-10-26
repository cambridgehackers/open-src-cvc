////////////////////////////////////////////////////////////////////////////////
// GCD test vectors
// translated to Verilog from VHDL by Sari Coumeri 
// original VHDL obtained from the '92 High Level Synthesis Benchmarks
// January 1994
////////////////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps
module GCD_sim;
     reg [7:0] X;
     reg [7:0] Y;
     reg Reset;
     wire [7:0] gcd_output;

     GCD GCD_1 (X,Y,Reset,gcd_output);

initial
begin
//$dumpvars;
// repeat(10000)
repeat(10000)
begin
#10;

// ****************************************** 
// *                                        * 
// *           TEST VECTORS                 * 
// *                                        * 
// ****************************************** 

// X && Y are small && equal x == 1, y == 1, reset == 0

  X = 8'b00000001;
  Y = 8'b00000001;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000001) $display("gcd_output !== 8'b00000001");

// X && Y are small && divisible x == 2, y == 1, reset == 0

  X = 8'b00000010;
  Y = 8'b00000001;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000001) $display("gcd_output !== 8'b00000001");

// X && Y are small && divisible 2 times x == 6, y == 3, reset == 0

  X = 8'b00000110;
  Y = 8'b00000011;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000011) $display("gcd_output !== 8'b00000011");

// X && Y are small && divisible 4 times x == 12, y == 3, reset == 0

  X = 8'b00001100;
  Y = 8'b00000011;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000011) $display("gcd_output !== 8'b00000011");

// X && Y are small && divisible x == 1, y == 2, reset == 0

  X = 8'b00000001;
  Y = 8'b00000010;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000001) $display("gcd_output !== 8'b00000001");

// X && Y are small && divisible 2 times x == 3, y == 6, reset == 0

  X = 8'b00000011;
  Y = 8'b00000110;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000011) $display("gcd_output !== 8'b00000011");

// X && Y are small && divisible 4 times x == 3, y == 12, reset == 0

  X = 8'b00000011;
  Y = 8'b00001100;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000011) $display("gcd_output !== 8'b00000011");

// X && Y are small && divisible 4 times x == 12, y == 6, reset == 1

  X = 8'b00001100;
  Y = 8'b00000110;
  Reset = 1'b1;
#10;
if (gcd_output !== 8'b00000000) $display("gcd_output !== 8'b00000000");

// X && Y are not divisible x == 28, y == 5, reset == 0

  X = 8'b00011100;
  Y = 8'b00000101;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000001) $display("gcd_output !== 8'b00000001");

// X && Y are not divisible x == 5, y == 28, reset == 0

  X = 8'b00000101;
  Y = 8'b00011100;

  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000001) $display("gcd_output !== 8'b00000001");

// X && Y are not divisible x == 28, y == 5, reset == 1

  X = 8'b00011100;
  Y = 8'b00000111;
  Reset = 1'b1;
#10;
if (gcd_output !== 8'b00000000) $display("gcd_output !== 8'b00000000");

// X && Y are equal x == 28, y == 28, reset == 0

  X = 8'b00011100;
  Y = 8'b00011100;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00011100) $display("gcd_output !== 8'b00011100");

// X && Y are equal x == 28, y == 28, reset == 1

  X = 8'b00011100;
  Y = 8'b00011100;
  Reset = 1'b1;
#10;
if (gcd_output !== 8'b00000000) $display("gcd_output !== 8'b00000000");

// Y is large , x == 3, y == 192, reset == 0

  X = 8'b00000011;
  Y = 8'b11000000;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000011) $display("gcd_output !== 8'b00000011");


// X is large , x == 192, y == 3, reset == 0

  X = 8'b00000011;
  Y = 8'b11000000;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000011) $display("gcd_output !== 8'b00000011");


// X && Y are large, X > Y, && X is not divisible by Y, x == 208, y == 64, reset == 0

  X = 8'b01000000;
  Y = 8'b11010000;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00010000) $display("gcd_output !== 8'b00010000");


// X && Y are large, X < Y && Y is not divisible by X, x == 38, y == 158, reset == 0

  X = 8'b00100110;
  Y = 8'b10011110;
  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000010) $display("gcd_output !== 8'b00000010");



// X && Y are large, X > Y && X is not divisible by X, x == 158, y == 38, reset == 0

  X = 8'b10011110;
  Y = 8'b00100110;

  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000010) $display("gcd_output !== 8'b00000010");


// X && Y are large, almost equal && are not divisible, x == 158, y == 192, reset == 0

  X = 8'b10011110;
  Y = 8'b11000000;

  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000010) $display("gcd_output !== 8'b00000010");


// X && Y are large, almost equal && are not divisible, x == 158, y == 192, reset == 1

  X = 8'b10011110;
  Y = 8'b11000000;

  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000010) $display("gcd_output !== 8'b00000010");

// X == 0, Y is large, x == 0, y == 192, reset == 0

  X = 8'b00000000;
  Y = 8'b11000000;

  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000000) $display("gcd_output !== 8'b00000000");


// X is large, Y == 0, x == 192, y == 0, reset == 0

  X = 8'b11000000;
  Y = 8'b00000000;

  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000000) $display("gcd_output !== 8'b00000000");


// X == 0, Y == 0, x == 0, y == 0, reset == 0

  X = 8'b00000000;
  Y = 8'b00000000;

  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000000) $display("gcd_output !== 8'b00000000");


// X == 0, Y == 0, x == 0, y == 0, reset == 1

  X = 8'b00000000;
  Y = 8'b00000000;

  Reset = 1'b0;
#10;
if (gcd_output !== 8'b00000000) $display("gcd_output !== 8'b00000000");


end
$finish(3);
end
endmodule

// configuration cgcd of E is
//   for A
//   for all: gcd
////   end for;
//   end for;
//end cgcd;




