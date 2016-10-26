module test;
 reg a, // = 1'hx, x 
     b, // = 1'hx, x 
     c, // = 1'hx, x 
     d; // = 1'hx, x 
 wire e; // = StX
 and and1(e, a, b, c); 

 initial
  begin
   // $list;
   $monitor("d=%b,e=%b", d, e);
   a = 1;
   b = 0;
   c = 1;
   assign d = a & b & c;
   #10 ;
   $stop;
 end
endmodule
