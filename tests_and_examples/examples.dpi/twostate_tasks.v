/*
 * simple 2-state tasks input/outputs
 */
module test_2state_tasks;
 import "DPI-C" task byte_test(input byte i, output byte o);
 import "DPI-C" task shortint_test(input shortint i, output shortint o);
 import "DPI-C" task int_test(input int i, output int o);
 import "DPI-C" task real_test(input real i, output real o);
 import "DPI-C" task bit_test(input bit i, output bit o);
 import "DPI-C" task bit_vec_test(input bit [7:0] i, output bit [7:0] o);
 import "DPI-C" task bit_vec_wide_test(input bit [127:0] i, output bit [127:0] o);

 byte byte_i, byte_o;
 shortint short_i, short_o;
 int int_i, int_o;
 real real_i, real_o;
 bit bit_i, bit_o;
 bit [7:0] bitv_i, bitv_o;
 bit [127:0] bitvw_i, bitvw_o;

 initial begin
  byte_i = 10;
  byte_test(byte_i, byte_o);
  $display("byte_i=%0d byte_o=%0d", byte_i, byte_o);

  short_i = 11;
  shortint_test(short_i, short_o);
  $display("short_i=%0d short_o=%0d", short_i, short_o);

  int_i = 22;
  int_test(int_i, int_o);
  $display("int_i=%0d int_o=%0d", int_i, int_o);

  real_i = 123.5;
  real_test(real_i, real_o);
  $display("real_i=%g real_o=%g", real_i, real_o);

  bit_i = 1;
  bit_test(bit_i, bit_o);
  $display("bit_i=%g bit_o=%g", bit_i, bit_o);

  bitv_i = 30;
  bit_vec_test(bitv_i, bitv_o);
  $display("bitv_i=%0d bitv_o=%0d", bitv_i, bitv_o);

  bitvw_i = 128'h11111111_22222222_33333333_44444444;
  bit_vec_wide_test(bitvw_i, bitvw_o);
  $display("bitvw_i=%x bitv_o=%x", bitvw_i, bitvw_o);
 end
endmodule

