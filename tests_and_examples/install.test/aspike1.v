module test;
reg in;
wire w1,w2,out;

buf #(1,2) (w1,in);
not #(3,4) (w2,w1);

bufif1 #(5,6) (out,w2,in);

initial begin
 $monitor($stime,, "out=%b,in=%b,w1=%b,w2=%b", out, in, w1, w2);
 #0 in=1'b0;	
 #100 in=1'b1;	
 #100 in=1'bx;	
 #100 in=1'bz;	
end
endmodule
