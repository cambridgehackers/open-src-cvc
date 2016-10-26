/*
 * simple 4-state array test
 */
module test_fourstate_array;
 import "DPI-C" task array_test(input reg [31:0] a [1:0]);
 import "DPI-C" task wide_array_test(inout reg [63:0] a [1:0]);

 reg [31:0] array [1:0];
 reg [63:0] wide_array [1:0];

 initial begin
   array[0] = 12;
   array[1] = 13;
   array_test(array);

   /* now wide array */
   wide_array[0] = 64'hffffffff_aaaaaaaa;
   wide_array[1] = 64'hbbbbbbbb_cccccccc;
   wide_array_test(wide_array);
   $display("array[0] = %x array[1] = %x", array[0], array[1]); 
 end
endmodule


