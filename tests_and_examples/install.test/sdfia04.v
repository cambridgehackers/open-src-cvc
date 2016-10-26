module ffnand_test;
 wire [1:18] q, qbar;
 reg [18:1] preset, clear;

 parameter d = 10;

 ffnand #(.wide(17)) ff1[1:18](q, qbar, preset, clear);
 initial 
  begin
   #d preset[1] = 0; clear[1] = 1;
   #d preset[1] = 1;
   #d clear[1] = 0;
   #d clear[1] = 1;
  end
 initial $monitor($time,, "preset[1]=%b clear[1]=%b q[18]=%b qbar[18]=%b",
  preset[1], clear[1], q[18], qbar[18]);
endmodule

module ffnand(ffq, ffqbar, ffpreset, ffclear);
 output [1:wide + 1] ffq, ffqbar;
 input [wide + 1:1] ffpreset, ffclear;
 parameter wide = 1;
 
 nand #1 q1[1:wide + 1] (ffq, ffqbar, ffpreset),
  q2[1:wide + 1] (ffqbar, ffq, ffclear); 
endmodule
