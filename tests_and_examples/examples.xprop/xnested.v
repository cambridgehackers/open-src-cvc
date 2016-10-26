module xnested;
 reg [3:0] a, b, c, d, e;


 initial begin

  /* TEST1 */
  a = 4'b000x;
  b = 0;
  c = 4'b1111;
  d = 4'b1111;
  e = 4'b1111;
  /* first two cases match and combine if statements */
  case(a)
   4'b0000: 
    begin
     if (c) b = 4'b1001;
     else b = 4'b0000;
    end
   4'b0001:
    begin
     if (d) b = 4'b1001;
     else b = 4'b0000;
    end
   4'b0111:
    begin
     if (e) b = 4'b1111;
     else b = 4'b0000;
    end
  endcase
  //b = 1001
  $display("test1 b = %b", b);


  /* TEST2 */
  a = 4'b000x;
  b = 0;
  c = 4'bxxxx;
  d = 4'bxxxx;
  e = 4'bxxxx;
  /* first two cases match and combine if statements */
  case(a)
   4'b0000: 
    begin
     if (c) b = 4'b1001;
     else b = 4'b0000;
    end
   4'b0001:
    begin
     if (d) b = 4'b1101;
     else b = 4'b0000;
    end
   4'b0111:
    begin
     if (e) b = 4'b1111;
     else b = 4'b0000;
    end
  endcase
  //b = xx0x
  $display("test2 b = %b", b);




  /* TEST3 */
  b = 4'b1000;
  a = 4'b000x;
  c = 4'b000x;
  case (a)
    4'b1100: b = 4'b1111; 
    4'b0001: b = 4'b0000;   //matches
    4'b0000: 
    case (a)
      4'b1100: b = 4'b1111; 
      4'b0001: b = 4'b0000; //matches
      4'b0000: b = 4'b0001; //matches
    endcase
  endcase
  //b = 000x
  $display("test3 b = %b", b);

  /* TEST4 */
  a = 4'b000x;
  if (a)
   begin
    case (a)
      4'b1100: b = 4'b1111; 
      4'b0001: b = 4'b0000;  
      4'b0000: b = 4'b1100;
    endcase
   end
   else
    begin
     case (a)
       4'b1100: b = 4'b1111; 
       4'b0001: b = 4'b0000; 
       4'b0000: b = 4'b0000; 
     endcase
   end 
  //b = xx00
  $display("test4 b = %b", b);

 end
endmodule

