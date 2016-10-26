module xtrace;
 reg [3:0] a, b, c;

 initial begin
  // the +xtrace feature along with +xprop or +xprop2 will record all times
  // and places during simulation where x-propagation occurs, run this
  // example with +xtrace and see the 'cvc.xprop' file it creates
  a = 4'b00x1;
  if (a) b = 4'bx010;
  else b = 4'bx011;
  $display("b = %b", b);

  a = 4'b01xx;
  b = 0;
  case(a)
   4'b0000: b = 4'b0000;
   4'b1100: b = 4'b1100; 
   4'b0101: b = 4'b0010; 
   4'b0111: b = 4'b0100;
   4'b0100: b = 4'b0100;  
   4'b0110: b = 4'b0100;  
  endcase
  $display("b = %b", b);
 end
endmodule
