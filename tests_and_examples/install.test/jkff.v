/******************************************************************************/

module jkff (t, tbar, j, k, ck, s, r);  

  parameter rise = 0, fall = 0;

  input  j, k, ck, s, r;    	// J, K, clock, s, clear
  output t, tbar;               // data outputs

  JK_Q    #(rise, fall) (t, j, k, ck, s, r);
  JK_QBAR #(rise, fall) (tbar, j, k, ck, s, r);

endmodule    // jkff

