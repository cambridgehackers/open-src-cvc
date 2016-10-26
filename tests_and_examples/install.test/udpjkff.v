module top;

reg r_clock,j,k,s,r;
assign clock = r_clock;

jkff inst1 (t, tbar, j, k, clock, s, r);  

initial begin
$monitor ($time,,"t=%b,tbar=%b,j=%b,k=%b,clock= %b,s=%b,r=%b",
 t, tbar, j, k, clock, s, r); 
j = 0;
k = 0;
s = 1;
r = 1;
end

initial begin

#10 s = 0;
#10 r = 1;
#10 r  = 0;
#10 r = 1;
#10 j = 0; k = 0;
#10 r_clock = 0;
#10 r_clock = 1;
#10 j = 0; k = 1;
#10 r_clock = 0;
#10 r_clock = 1;
#10 j = 1; k = 0;
#10 r_clock = 0;
#10 r_clock = 1;
#10 j = 1; k = 1;
#10 r_clock = 0;
#10 r_clock = 1;
#10 j = 0; k = 1;
#10 r_clock = 0;
#10 r_clock = 1;
#10 j = 0; k = 0;
#10 r_clock = 0;
#10 r_clock = 1;
#10 r = 0;
#10 r_clock = 0;
#10 r_clock = 1;
#10 r = 0;
#10 s = 1;
#10 r_clock = 0;
#10 r_clock = 1;
#10 r = 1;
#10 s = 0; r = 1;
#10 s = 1; r = 0;
#10 s = 1; r = 1;
#10 s = 0; r = 0;
#10 s = 1; r = 0;
#10 s = 0; r = 1;
end
endmodule

// jk flip flop from valid SIM library
module jkff (t, tbar, j, k, ck, s, r);  

  parameter rise = 0, fall = 0;

  input  j, k, ck, s, r;    	// J, K, clock, s, clear
  output t, tbar;               // data outputs

  JK_Q    #(rise, fall) (t, j, k, ck, s, r);
  JK_QBAR #(rise, fall) (tbar, j, k, ck, s, r);

endmodule    // jkff
