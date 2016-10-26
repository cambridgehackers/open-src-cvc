module xx;
 integer i;
 real r;

 initial
  begin
   $hello(3);
   i = $stime;
   /* r = $realfhello; */
   $display("done with PLI 2.0 calls returned i=%0d and r=%0g", i, r);
  end
endmodule
