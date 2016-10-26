/*
 * simple real and real array test
 */
`define SIZE 10
module real_test;
 import "DPI-C" task set_array_vals(inout real a [`SIZE-1:0], input int s);
 import "DPI-C" function real mult_real(input real i);

 real array [`SIZE:0];
 real twox;
 int i;

 initial begin
   set_array_vals(array, `SIZE);
   for (i = 0; i < `SIZE; i = i+1)
    begin
     twox = mult_real(array[i]);
     $display("array[%0d]=%g", i, twox);
    end
 end
endmodule

