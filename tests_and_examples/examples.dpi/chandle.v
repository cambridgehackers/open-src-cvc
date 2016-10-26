/*
 * simple chandle (C pointers) test
 */
module test_chandle;
 import "DPI-C" function chandle get_address(input int i);
 import "DPI-C" task print_str(input chandle c);
 chandle c1, c2;

 initial begin
  c1 = get_address(1);
  print_str(c1);
  c2 = get_address(2);
  print_str(c2);
 end
endmodule

