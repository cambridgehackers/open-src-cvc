//use CVC -optconfigfile option to only turn on X-propagation for module
//named 'dut' not the testbench itself
module testbench;
 reg clk, rst, i; 
 wire o;

 dut i1(clk, rst, i, o);

 initial begin
  rst = 1'bx;
  i = 1'b0;
  clk = 1'b0;
  //xprop turned off for this module so it will not combine
  if (o) i = 1'b0;
  else i = 1'b1;

  clk = 1'b1;
  #1 ;
  clk = 1'b0;
  #1 ;
  $display("o=%b", o);
 end
endmodule

//include this module for x-propagation
module dut(clk, rst, ival, oval);
 input clk; 
 input rst; 
 input ival;
 output reg oval; 
 
 always @(clk)
  begin
   if (rst) oval = 1'b0;
   else oval = ival;
  end
endmodule
