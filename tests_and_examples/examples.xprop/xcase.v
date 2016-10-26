module xcase;
 reg [3:0] a, b, c;

 initial begin

  /* TEST1 */
  //case matches all possible values for xs (1 or 0) in the case items
  a = 4'b01xx;
  b = 0;
  case(a)
   4'b0000: b = 4'b0000;
   4'b1100: b = 4'b1100; 
   4'b0101: b = 4'b0010;  //first match
   4'b0111: b = 4'b0100;  //second match
   4'b0100: b = 4'b0100;  //third match
   4'b0110: b = 4'b0100;  //fourth match
  endcase
  //the four matches are combined to assign b = 4'b0xx0
  $display("case1 b = %b", b);


  /* TEST2 */
  //case is missing possible values for xs (1 or 0) in the case items 
  a = 4'b01xx;
  b = 0;
  case(a)
   4'b0000: b = 4'b0000;
   4'b1100: b = 4'b1100; 
   4'b0101: b = 4'b0010;  //first match
   4'b0111: b = 4'b0100;  //second match
  endcase
  //missing possible values 4'b0100 and 4'b0100, so value is combined
  //to its value on entry
  $display("case2 b = %b", b);


  /* TEST3 */
  //if case selector has X value and default, the default is also combined
  a = 4'b01xx;
  b = 0;
  case(a)
   4'b0000: b = 4'b0000;
   4'b1100: b = 4'b1100; 
   4'b0101: b = 4'b0010;  //first match
   4'b0111: b = 4'b0100;  //second match
   default: b = 4'b1100;  //also inlcude the default
  endcase
  //b = xxx0
  $display("case3 b = %b", b);

  /* TEST4 */
  //combine both a & c values on the lhs
  a = 4'b01xx;
  b = 0;
  c = 0;
  case(a)
   4'b0000: 
    begin
     b = 4'b0000;
     c = 4'b0000;
    end
   4'b1100: 
    begin
     b = 4'b1100; 
     c = 4'b1100;
    end
   4'b0101: 
    begin
     b = 4'b0010;  //first match
     c = 4'b1100;  
    end
   4'b0111: 
    begin
     b = 4'b0100;  //second match
     c = 4'b1100;
    end
   4'b0100: 
    begin
     b = 4'b0100;  //third match
     c = 4'b1100;
    end
   4'b0110: 
    begin
     b = 4'b0100;  //fourth match
     c = 4'b1100;
    end
  endcase
  //b = xxx0 c = 1100
  $display("case4 b = %b c = %b", b, c);


  /* TEST5 */
  //combine both a & c values on the lhs - but 'c' not always assigned to 
  //in second matched block will be assigned X
  a = 4'b01xx;
  b = 0;
  c = 0;
  case(a)
   4'b0000: 
    begin
     b = 4'b0000;
     c = 4'b0000;
    end
   4'b1100: 
    begin
     b = 4'b1100; 
     c = 4'b1100;
    end
   4'b0101: 
    begin
     b = 4'b0010;  //first match
     c = 4'b1100;  
    end
   4'b0111: 
    begin
     b = 4'b0010;  //second match
                   //notice no c assign - will set to x
    end
   4'b0100: 
    begin
     b = 4'b0100;  //third match
     c = 4'b1100;
    end
   4'b0110: 
    begin
     b = 4'b0100;  //fourth match
     c = 4'b1100;
    end
  endcase
  //b = 0010 c = xxxx
  $display("case5 b = %b c = %b", b, c);

 end
endmodule
