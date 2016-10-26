/*
 * test to use different name in Verilog than the C lib
 */
module diffname_test;
 import "DPI-C" ctest = task scalar_value(input reg b, input reg b2);

 reg s, s2;

 initial begin
   s = 0;
   s2 = 1;
   scalar_value(s, s2);
 end
endmodule

