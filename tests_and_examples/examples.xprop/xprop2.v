module xprop2;
 reg [3:0] a, b, c;

 initial begin
  //for +xprop2 - if value has an X does no combining will just set to x
  a = 4'b00x1;
  if (a) b = 4'bx010;
  else b = 4'bx011;
  //b=xxxx
  $display("b=%b", b);

  //same for +xprop2 case if selector contains an X no combining just set to X
  a = 4'b01xx;
  b = 0;
  case(a)
   4'b0000: b = 4'b0000;
   4'b1100: b = 4'b1100; 
   4'b0101: b = 4'b0010;  
   4'b0111: b = 4'b0100;  
  endcase
  //just assigne b=xxxx
  $display("case1 b = %b", b);
 end
endmodule
