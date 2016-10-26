module xx;
 integer i;
 real r;

 initial
  begin
   $hello;
   i = $stime;
   $hello(i);
   $display("done with PLI 2.0 calls returned i=%0d and r=%0g", i, r);
  end
endmodule
