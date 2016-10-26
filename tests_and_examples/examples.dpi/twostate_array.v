/*
 * 2-state array tests
 */
`define SIZE 10
module twostate_array;
 import "DPI-C" task mult_array(inout int i[`SIZE-1:0], input int size);

 int array[`SIZE-1:0];
 int i;

 initial begin

  for (i = 0; i < `SIZE; i = i + 1) 
   begin
    array[i] = i;
   end

  mult_array(array, `SIZE);
  for (i = 0; i < `SIZE; i = i + 1) 
   begin
    $display("array[%0d] = %0d", i, array[i]);
   end
  
 end
endmodule


module wide_twostate_array;
 import "DPI-C" task wide_array_test(inout bit [63:0] a [1:0]);

 bit [63:0] array [1:0];

 initial begin
   array[0] = 64'hffffffff_aaaaaaaa;
   array[1] = 64'hbbbbbbbb_cccccccc;
   wide_array_test(array);
   $display("array[0] = %x array[1] = %x", array[0], array[1]); 
 end
endmodule
