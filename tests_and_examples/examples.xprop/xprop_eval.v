module xprop_eval;
 reg [3:0] a, b, c;

 initial begin
  a = 4'b1011;
  b = 4'b1x1x;
  c = a & b;
  //normal Verilog c = 101x, with +xprop_eval c = 4'b1x1x
  $display("and c = %b", c);

  a = 4'b1011;
  b = 4'b1x1x;
  c = a | b;
  //normal Verilog c = 1x11, with +xprop_eval c = 4'b1x1x
  $display("or c = %b", c);
 end
endmodule
