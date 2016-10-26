// instance identity test

module level1(i);
 input [31:0] i;
 parameter p1 = 0, p2 = 0;
 initial
  begin
   #1 $display("i=%0d,p1=%0d,p2=%0d", i, p1, p2);
  end
endmodule

module level2(i);
 input [31:0] i;
 parameter p1 = 0, p2 = 0;
 level1 #(.p1(500), .p2(501)) x1(2*i);
 level1 #(.p1(502), .p2(503)) x2(2*i + 1);
endmodule

module level3(i);
 input [31:0] i;
 parameter p1 = 0, p2 = 0;
 level2 #(.p1(400), .p2(401)) x1(3*i);
 level2 #(.p2(403), .p1(402)) x2(3*i + 1);
endmodule

module level4(i);
 input [31:0] i;
 parameter p1 = 0, p2 = 0;
 level3 #(.p1(300), .p2(301)) x1(4*i);
 level3 #(.p1(302), .p2(303)) x2(4*i + 1);
endmodule

module level5(i);
 input [31:0] i;
 parameter p1 = 0, p2 = 0;
 level4 #(.p1(200), .p2(201)) x1(4*i);
 level4 #(.p1(202), .p2(203)) x2(4*i + 1);
endmodule

module top;
 integer i;

 initial i = 0;
 level5 #(100,101) t1(i);
 /* --
 defparam t1.x1.x1.x1.x1.p1 = 1'h1;
 defparam t1.x1.x1.x1.x2.p1 = 2'h2;
 defparam t1.x1.x1.x2.x1.p1 = 3'h3;
 defparam t1.x1.x1.x2.x2.p1 = 4'h4;

 defparam t1.x1.x2.x1.x1.p1 = 5'h5;
 defparam t1.x1.x2.x1.x2.p1 = 6'h6;
 defparam t1.x1.x2.x2.x1.p1 = 7'h7;
 defparam t1.x1.x2.x2.x2.p1 = 8'h8;

 defparam t1.x2.x1.x1.x1.p1 = 9'h9;
 defparam t1.x2.x1.x1.x2.p1 = 10'ha;
 defparam t1.x2.x1.x2.x1.p1 = 11'hb;
 defparam t1.x2.x1.x2.x2.p1 = 12'hc;

 defparam t1.x2.x2.x1.x1.p1 = 13'hd;
 defparam t1.x2.x2.x1.x2.p1 = 14'he;
 defparam t1.x2.x2.x2.x1.p1 = 15'hf;
 defparam t1.x2.x2.x2.x2.p1 = 16'h10;
 defparam t1.x2.x2.x2.x2.p2 = 93'h3f01;
 -- */
endmodule
