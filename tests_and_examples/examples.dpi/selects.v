/*
 * test built in bit/part select routines
 */
module select_test;
 import "DPI-C" task bitsel_2state_test(inout bit [63:0] o, input int bi);
 import "DPI-C" task bitsel_4state_test(inout reg [63:0] o, input int bi);
 import "DPI-C" task partsel_2state_test(inout bit [63:0] o, input bit [63:0] in);
 import "DPI-C" task partsel_4state_test(inout reg [63:0] o, input reg [63:0] in);
 bit [63:0] bi, bi2;
 reg [63:0] ri, ri2;

 initial begin
  /* do 2-state bit selects */
  bi[12] = 1; 
  bitsel_2state_test(bi, 12);
  $display("bi=%b", bi);
  bi[55] = 1; 
  bitsel_2state_test(bi, 55);
  $display("bi=%b", bi);

  /* do 4-state bit selects */
  ri = 0;
  ri[12] = 1; 
  bitsel_4state_test(ri, 12);
  $display("ri=%b", ri);
  ri[55] = 1'bx; 
  bitsel_4state_test(ri, 55);
  $display("ri=%b", ri);

  /* do 2-state part selects */
  bi = 64'h0;
  bi2 = 64'hffffffff_ffffffff; 
  partsel_2state_test(bi, bi2);
  $display("bi=%b", bi);

  /* do 4-state part selects */
  ri = 64'h0;
  ri2 = 64'hffffffff_ffffffff; 
  partsel_4state_test(ri, ri2);
  $display("ri=%b", ri);
 end
endmodule

