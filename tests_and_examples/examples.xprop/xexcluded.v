module xexcluded;
 reg [3:0] a, b;


 initial begin

  //only blocks containing if/case/lhs assings (=/<=/<= #const) are eligible
  //this if statement will be treated like regular Verilog since it
  //contains a delay the +xprop_exlude option will create a file called
  //'cvc.xprop.excluded' which are not eligible along with the reason
  a = 4'b000x;
  if (a) 
   begin
    b = 4'b0000;
    #1;  //contains delay - cannot be used in xprop
   end
  else
   begin
    b = 4'b0011;
   end
  $display("b=%b", b);
 end
endmodule

