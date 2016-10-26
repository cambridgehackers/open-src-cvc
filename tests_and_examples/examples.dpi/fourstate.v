/*
 * simple 4-state input/output test
 */
module test_fourstate;
 import "DPI-C" task reg_test(input reg [31:0] i);
 import "DPI-C" task reg_assign(inout reg [31:0] io);
 import "DPI-C" task reg_wide(inout reg [63:0] i);

 reg [31:0] ri, rio;
 reg [63:0] w;


 initial begin
   ri = 13;
   reg_test(ri);
   $display("ri=%d", ri);
   rio = 11;
   $display("rio=%d", rio);
   reg_assign(rio);
   $display("after rio=%d", rio);

   w = 64'hffffffff_aaaaaaaa;
   $display("w=%x", w);
   reg_wide(w);
   $display("after w=%x", w);
 end
endmodule
