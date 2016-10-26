///////////////////////////////////////////////////////////////////////////
// GCD
// translated to Verilog from VHDL by Sari Coumeri 
// original VHDL obtained from the '92 High Level Synthesis Benchmarks
// January 1994
///////////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps
module GCD(X,Y,Reset,gcd_output);
	input [7:0] X;
	input [7:0] Y;
        input Reset;
        output [7:0] gcd_output;
     
	reg [7:0] gcd_output;

	reg [7:0] xvar;
	reg [7:0] yvar;
       	reg resetvar;
	reg [1:0] compare_var;

function [1:0] COMPARE;

   input [7:0] x1;
   input [7:0] x2;

   integer i;

// 11 implies x1 and x2 are equal.
// 01 implies x1 less than x2.
// 10 implies x1 greater than x2.
begin : flag

     i = 7;
     while(i>=0)
      begin
       if ((x1[i] == 1'b1) && (x2[i] == 1'b0))
	begin
         COMPARE = 2'b10;
	 disable flag;
	end
       else if ((x1[i] == 1'b0) && (x2[i] == 1'b1))
	begin
           COMPARE = 2'b01;
	   // disable stupid;
           disable flag;
	end
       	i = i - 1;
     end

     COMPARE = 2'b11;
end
endfunction

always @(X or Y or Reset)
begin

  xvar = X;
  yvar = Y;
  resetvar = Reset;

  if (xvar == 8'b00000000) 
    gcd_output = 8'b00000000;

  if (yvar == 8'b00000000)
    gcd_output = 8'b00000000;

// The GCD factorization takes place only if Reset = 0

  if ((resetvar == 1'b0) && (xvar !== 8'b00000000) && (yvar !== 8'b00000000)) 
    begin
    compare_var = COMPARE(xvar, yvar);

// If compare returns 11 then inputs are equal
// If compare returns 10 then xvar > yvar
// If compare returns 01 then xvar < yvar

    while (compare_var !== 2'b11) 
     begin
// Loop till the numbers are equal
  
      if (compare_var == 2'b01)  
        yvar = yvar - xvar;
      else 
        xvar = xvar - yvar;
     

      compare_var = COMPARE(xvar, yvar);
    end
    
    gcd_output = xvar;
    end
  else
   begin
    gcd_output = 8'b00000000;
   end

end 

endmodule









