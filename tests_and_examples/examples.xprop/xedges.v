//scalar (one-bit) change on 0->X 
module test_scalar;
 reg c, v;

 always @(c) v = 1'b0;

 initial begin
   v = 1'b1;
   c = 1'b0;
   #1 ;
   c = 1'bx;
   #1 ;
   $display("%m");
   $display("v=%b", v);
 end

endmodule

//one bit scalar with 'negedge'
module test_scalar_negedge;
 reg c,v;

 always @(negedge c) v = 1'b0;

 initial begin
   v = 1'b1;
   c = 1'b0;
   #1 ;
   c = 1'bx;
   #1 ;
   $display("%m");
   $display("v=%b", v);
 end

endmodule

//two bit vectored with no 'real' 1/0 bits changed 00->XX
module test_vector;
 reg [1:0] c,v;

 always @(c) v = 2'b00;

 initial begin
   v = 2'b11;
   c = 2'b00;
   #1 ;
   c = 2'bxx;
   #1 ;
   $display("%m");
   $display("v=%b", v);
 end

endmodule

//two bit vectored with 'real' 1/0 bits changed 00->1X 
//handle as a real bit change
module test_vector_nonx_change;
 reg [1:0] c,v;

 always @(c) v = 2'b00;

 initial begin
   v = 2'b11;
   c = 2'b00;
   #1 ;
   c = 2'b1x;
   #1 ;
   $display("%m");
   $display("v=%b", v);
 end
endmodule

//two bit vectored with 'negedge'
module test_vector_negedge;
 reg [1:0] c,v;

 always @(negedge c[0]) v = 2'b00;

 initial begin
   v = 2'b11;
   c = 2'b00;
   #1 ;
   c = 2'b1x;
   #1 ;
   $display("%m c[0]=%b", v[0]);
   $display("v=%b", v);
 end

endmodule
