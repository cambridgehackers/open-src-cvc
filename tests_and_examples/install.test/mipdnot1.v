module xx;
 wire w1, w2; 
 reg r1, r2;

 modnot i1(w1, r1);
 modnot i2(w2, r2);

 initial 
  begin
   $monitor($stime,, "w1=%b, r1=%b, w2=%b, r2=%b", w1, r1, w2, r2);
   #100 r1 = 0;
   #100 r2 = 0;

   #100 r1 = 1;
   #100 r2 = 1;

   #100 r1 = 0;
   #100 r2 = 0;

   #100 r1 = 1'bx;
   #100 r2 = 1'bx;

   #100 r1 = 0;
   #100 r2 = 0;

   #100 r1 = 1'bz;
   #100 r2 = 1'bz;

   #100 r1 = 1;
   #100 r2 = 1;
  end
endmodule

module modnot(out, a);
 output out;
 input a;

 not (out, a); 
endmodule

