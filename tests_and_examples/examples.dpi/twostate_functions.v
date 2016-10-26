/*
 * simple 2-state function assigns
 */
module test_2state_functions;
 //'void function' not yet supported - use tasks instead
 import "DPI-C" function byte byte_test(input byte i);
 import "DPI-C" function shortint shortint_test(input shortint i);
 import "DPI-C" function int int_test(input int i);
 import "DPI-C" function real real_test(input real i);
 import "DPI-C" function bit bit_test(input bit i);
 import "DPI-C" function longint longint_test(input longint i);

 byte byte_i, byte_o;
 shortint short_i, short_o;
 int int_i, int_o;
 real real_i, real_o;
 bit bit_i, bit_o;
 longint long_i, long_o;

 initial begin
  byte_i = 10;
  byte_o = byte_test(byte_i);
  $display("byte_i=%0d byte_o=%0d", byte_i, byte_o);

  short_i = 11;
  short_o = shortint_test(short_i);
  $display("short_i=%0d short_o=%0d", short_i, short_o);

  int_i = 22;
  int_o = int_test(int_i);
  $display("int_i=%0d int_o=%0d", int_i, int_o);

  real_i = 123.5;
  real_o = real_test(real_i);
  $display("real_i=%g real_o=%g", real_i, real_o);

  bit_i = 1;
  bit_o = bit_test(bit_i);
  $display("bit_i=%g bit_o=%g", bit_i, bit_o);

  long_i = 64'haaaaaaaa_bbbbbbbb;
  long_o = longint_test(long_i);
  $display("long_i=%0x long_o=%0x", long_i, long_o);
 end
endmodule

