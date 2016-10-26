module xx;
 wire [31:0] w;
 wire [15:0] a, b, c;
 reg [31:0] w_r;

 assign {a[7:2], b, c[9:3]} = w;
 assign w = w_r;
 assign w = 32'hzzzzzzzz;
 assign b[1] = w[9]; 

 initial
  begin
   $monitor($stime,, "a=%b, b=%b, c=%b, w=%h", a, b, c, w);
   #10 w_r = 0;
   #10 w_r = 32'hffffffff;
   #10 w_r = 32'haaaaaaaa;
   #10 w_r = 32'h55555555;
   #10 w_r = 32'hffffffff;
   #10 w_r = 0;
  end
endmodule
