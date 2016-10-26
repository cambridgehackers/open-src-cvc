module probe;
 reg [31:0] a, b, c;

 initial 
  begin
   $setup_values(a, b, c); 
   #10 a = 3; c = 1;
   #10 b = 3; c = 2;
   #10 c = 3;
   #10 a = 33; c = 9;
   #10 b = 44; c = 22;
   #10 a = 30;
   #10 a = 50; b = 200; c = 0;
   #10 a = 50; c = 99;
   #10 b = 90; c = 99;
   #10 b = 11; c = 19;
  end
 // do the flash
 always @(c) $flash_values($stime/2);
endmodule
