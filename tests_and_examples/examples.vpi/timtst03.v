`timescale 10 ns / 1 ns 
module test;
 reg set;
 wire a, b, c;
 parameter p = 1.55;

 and #p i1(a, b, c);

 initial
  begin
   $monitor($realtime,,"set=", set);
   #p set = 0;
   #p set = 1;
  end
endmodule
