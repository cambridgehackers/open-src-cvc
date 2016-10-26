
`define CLK_PER 100

module top;
 setdel i1();
endmodule

module setdel;
 reg clk;
 reg [31:0] clk2;
 time t;
 initial 
  begin
   $monitor($time,, "%b %b", clk, clk2);
   #20 $tfclk(clk);
   #1000 t = $tfclkoff;
   $display("clock turned off at %t", t); 
   #200 $tfclk(clk2[2]);
   #1000 $finish;
  end
endmodule
