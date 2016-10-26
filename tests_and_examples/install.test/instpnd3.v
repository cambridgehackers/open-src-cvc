// instance identity test

module level1(i);
 input [h:0] i;
 parameter h = 31;
 parameter p1 = 0, p2 = 0;
 initial
  begin
   #1 $display("i=%0d,h=%0d,p1=%0d,p2=%0d", i, h, p1, p2);
  end
endmodule

module level2(i);
 input [h:0] i;
 parameter h = 31;
 parameter p1 = 0, p2 = 0;
 level1 #(h) x1(2*i);
 level1 #(h) x2(2*i + 1);
endmodule

module level3(i);
 input [h:0] i;
 parameter h = 31;
 parameter p1 = 0, p2 = 0;
 level2 #(h) x1(3*i);
 level2 #(h) x2(3*i + 1);
endmodule

module level4(i);
 input [h:0] i;
 parameter h = 31;
 parameter p1 = 0, p2 = 0;
 level3 #(h) x1(4*i);
 level3 #(h) x2(4*i + 1);
endmodule

module level5(i);
 input [h:0] i;
 parameter h = 31;
 parameter p1 = 0, p2 = 0;
 level4 #(h) x1(4*i);
 level4 #(h) x2(4*i + 1);
endmodule

module top;
 integer i;

 initial i = 0;
 level5 #(24) t1(i);
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

 defparam t1.x1.x1.x1.x1.h = 31;
 defparam t1.x1.x1.x1.x2.h = 2;
 defparam t1.x1.x1.x2.x1.h = 3;
 defparam t1.x1.x1.x2.x2.h = 4;

 defparam t1.x1.x2.x1.x1.h = 5;
 defparam t1.x1.x2.x1.x2.h = 6;
 defparam t1.x1.x2.x2.x1.h = 7;
 defparam t1.x1.x2.x2.x2.h = 8;

 defparam t1.x2.x1.x1.x1.h = 9;
 defparam t1.x2.x1.x1.x2.h = 10;
 defparam t1.x2.x1.x2.x1.h = 11;
 defparam t1.x2.x1.x2.x2.h = 12;

 defparam t1.x2.x2.x1.x1.h = 13;
 defparam t1.x2.x2.x1.x2.h = 14;
 defparam t1.x2.x2.x2.x1.h = 15;
 defparam t1.x2.x2.x2.x2.h = 16;
endmodule
