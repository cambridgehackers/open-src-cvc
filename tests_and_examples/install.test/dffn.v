// pipeline model from LRM section 7.1.6 
module DFF(q, d, clk);
 output q;
 input d, clk;
 reg q;
 
 always @(posedge clk)
  begin
   $display($stime,, "-- %m: positive clock edge old q=%b d=%b", q, d);
   q = d;
  end
endmodule

module dffn(q, d, clk); 
 parameter bits = 1;

 input [bits-1:0] d;
 output [bits-1:0] q;
 input clk;

 DFF dff[bits-1:0] (q, d, clk);
endmodule

module MxN_pipeline(in, out, clk);
 parameter M = 3, N = 4;

 input [M-1:0] in;
 output [M-1:0] out;
 input clk;

 wire [M*(N-1):1] t;

 dffn #(M) p[1:N] ({out, t}, {t, in}, clk);
endmodule

module top;
 reg [M-1:0] in;
 reg clk;
 wire [M-1:0] out;
 parameter M = 3, N = 4;

 MxN_pipeline #(M, N) pipe1(in, out, clk);

 initial
  begin
   $monitor($stime,, "in=%b, out=%b, clk=%b", in, out, clk);
   #10 in = 3'b0;
   #10 clk = 0;
   #10 clk = 1;
   #10 clk = 1'bx;
   #10 clk = 0;

   #10 in = 3'b111;
   #10 clk = 0;
   #10 clk = 1;
   #10 clk = 1'bx;
   #10 clk = 0;

   #10 in = 3'b0;
   #10 clk = 0;
   #10 clk = 111;
   #10 clk = 1'bx;
   #10 clk = 0;

   // notice values do not propagate through pipeline until here 
   #10 in = 3'b111;
   #10 clk = 0;
   #10 clk = 1;
   #10 clk = 1'bx;
   #10 clk = 0;
  end
endmodule
