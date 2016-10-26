module ffnand_test;
 wire q, qbar;
 reg preset, clear;

 parameter d = 10;

 ffnand ff1(q, qbar, preset, clear);
 initial 
  begin
   #d preset = 0; clear = 1;
   #d preset = 1;
   #d clear = 0;
   #d clear = 1;
  end
 initial $monitor($time,, "preset=%b clear=%b q=%b qbar=%b",
  preset, clear,q, qbar);
endmodule

module ffnand(ffq, ffqbar, ffpreset, ffclear);
 output ffq, ffqbar;
 input ffpreset, ffclear;
  
 nand #(1, 1) q1(ffq, ffqbar, ffpreset), q2(ffqbar, ffq, ffclear); 
 specify
  specparam pr = 5;
  specparam pf = 5;
  // notice error because no path delay to ffqbar
  (ffpreset => ffq) = (pr, pf);
  (ffclear => ffq) = (pr, pf);
 endspecify
endmodule
