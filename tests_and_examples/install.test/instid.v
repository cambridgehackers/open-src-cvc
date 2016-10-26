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
 level1 x1(2*i);
 level1 x2(2*i + 1);
endmodule

module level3(i);
 input [31:0] i;
 parameter p1 = 0, p2 = 0;
 level2 x1(3*i);
 level2 x2(3*i + 1);
endmodule

module level4(i);
 input [31:0] i;
 parameter p1 = 0, p2 = 0;
 level3 x1(4*i);
 level3 x2(4*i + 1);
endmodule

module level5(i);
 input [31:0] i;
 parameter p1 = 0, p2 = 0;
 level4 x1(4*i);
 level4 x2(4*i + 1);
endmodule

module top;
 integer i;

 initial i = 0;
 level5 t1(i);
 defparam t1.x1.x1.x1.x1.p1 = 1;
 defparam t1.x1.x1.x1.x2.p1 = 2;
 defparam t1.x1.x1.x2.x1.p1 = 3;
 defparam t1.x1.x1.x2.x2.p1 = 4;

 defparam t1.x1.x2.x1.x1.p1 = 5;
 defparam t1.x1.x2.x1.x2.p1 = 6;
 defparam t1.x1.x2.x2.x1.p1 = 7;
 defparam t1.x1.x2.x2.x2.p1 = 8;

 defparam t1.x2.x1.x1.x1.p1 = 9;
 defparam t1.x2.x1.x1.x2.p1 = 10;
 defparam t1.x2.x1.x2.x1.p1 = 11;
 defparam t1.x2.x1.x2.x2.p1 = 12;

 defparam t1.x2.x2.x1.x1.p1 = 13;
 defparam t1.x2.x2.x1.x2.p1 = 14;
 defparam t1.x2.x2.x2.x1.p1 = 15;
 defparam t1.x2.x2.x2.x2.p1 = 16;
endmodule
