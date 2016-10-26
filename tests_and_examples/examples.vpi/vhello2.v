module xx;
 integer i;
 real r;

 initial
  begin
   $hello;
   r = $realfhello;
   i = $stime;
   $display("done with PLI 2.0 calls returned i=%0d and r=%0g", i, r);
  end
endmodule
