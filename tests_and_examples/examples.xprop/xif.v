module xif;
 reg [3:0] a, b, c;

 initial begin
  /* TEST1 */
  //if selector contains no Xs just handle as normal if
  a = 4'b0001;
  if (a) b = 1;
  else b = 0;
  //b=0001
  $display("test1 b=%b", b);


  /* TEST2 */
  //if selector contains an X, combine the then/else sections using the ?:
  //rules, (0,0) = 0, (1,1) = 1, otherwise x
  a = 4'bxxxx;
  if (a) b = 4'bx010;
  else b = 4'bx011;
  //b=x01x
  $display("test2 b=%b", b);


  /* TEST3 */
  //no else so combined with value on entry
  a = 4'b00x1;
  b = 4'b1100;
  if (a) b = 4'b1111;
  //b=11xx
  $display("test3 b=%b", b);

  /* TEST4 */
  //X contains a select but 'c' is not set in else case will be assigned 'bx
  a = 4'b00x1;
  if (a) 
   begin
    b = 4'bx010;
    c = 4'b1111;  //c is assigned here not not is else case will be 4'bxxxx;
   end
  else b = 4'bx011;

  //b=x01x  c = xxxx
  $display("test4 b=%b c=%b", b, c);
 end
endmodule
