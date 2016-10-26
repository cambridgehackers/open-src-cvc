// specify test for fd clear/set flip flop
module test;
 wire t_q;  
 reg t_clk, t_clk0, t_clk1, t_clk2, t_d, t_clr, t_set;

 fd3noqn i1(t_q0, t_clk2, t_clk2, t_d0, t_clr0, t_set0);
 fd3noqn i2(t_q1, t_clk2, t_clk2, t_d1, t_clr1, t_set1);
 fd3noqn i3(t_q, t_clk, t_clk1, t_d, t_clr, t_set);

 initial 
  begin
   $monitor($stime,, "q=%b, clk=%b, data=%b, clr=%b, set=%b",
    t_q, t_clk, t_d, t_clr, t_set);
   $dump_contents;
   // test set/clear logic and delays - set overrides - low assertion 
   #1000 $display("testing set/clear logic"); t_set = 1'bx;
   #1000 t_set = 0;
   #1000 t_clr = 0;
   #1000 t_set = 1;
   #1000 t_set = 0; 
   #1000 t_set = 1; 
   #1000 t_clr = 1'bx;
   // test normal logic (set clear must be high)
   #1000 $display("testing normal logic"); t_clr = 1; t_set = 1; t_d = 0;
   #1000 t_clk = 1; 
   #1000 t_clk = 0; 
   #1000 t_clk = 1; 
   #1000 t_clk = 0; 
   #1000 t_clk = 1; 
   #1000 t_clk = 0; 
   #1000 t_clk = 1'bx;
   #1000 t_clk = 0;
   #1000 t_clk = 1'bz;
   #1000 t_clk = 0;
   #1000 t_clk = 1'bx;
   #1000 t_clk = 1;
   #1000 t_d = 1; t_clk = 1; 
   #1000 t_clk = 0; 
   #1000 t_clk = 1; 
   #1000 t_clk = 0; 
   #1000 t_clk = 1; 
   #1000 t_clk = 0; 
   #100 t_clk = 1'bx;
   #1000 t_clk = 0;
   #1000 t_clk = 1'bz;
   #1000 t_clk = 0;
   #1000 t_clk = 1'bx;
   #1000 t_clk = 1;
   // test setup
   #30 t_clk = 0;
   #30 t_d = 1;
   #30 t_clk = 1;
   #30 t_d = 0;
   #30 t_clk = 0;
   #30 t_d = 1;
   #30 t_clk = 1; t_d = 0; t_clk = 0; t_d = 1; t_clk = 1;
   #100 t_clk = 0; t_clk1 = 0;
   #100 t_clk1 = 1;
   #2000 t_clk = 1;

   /* ---
   #100 t_d = 1; t_clk = 1;
   #100 t_d = 1;
   #450 t_clk = 1;
   #550 t_clk = 0;
   #200 t_d = 0;

   #350 t_clk = 1;
   #550 t_clk = 0;

   #550 t_clk = 1;
   #550 t_clk = 0;
  --- */
  end
endmodule

module fd3noqn(q, clk, clk1, d, clr, set);
 output q;
 input clk, clk1, d, clr, set;
 // wire xxx;

 specify
  specparam tRise_clk_q = 140, tFall_clk_q = 250;
  specparam tRise_control = 40, tFall_control= 50;
  specparam tSetup=70, tHold=50;
  specparam tWpos=600, tWneg=500;

  // paths
  (clk => q) = (tRise_clk_q, tFall_clk_q);
  (clr,set *> q) = (tRise_control, tFall_control);

  // timing checks
  // setup time: d is reference, clk is data - setup > posedge clk - last data
  // data must be stable > setup when clock triggers (pos. edge) 
  // setup(ref, data, >setup);
  // $setup(d, posedge clk, tSetup);

  // hold time:  clk is reference, d is data - hold > d change after last clk
  // hold(ref, data, >hold);
  // $hold(posedge clk, d, tHold);

  $setuphold(posedge clk, d, tSetup, tHold);

  $width(posedge clk, tWpos);
  $width(negedge clk, tWneg);
  $period(posedge clk, 1000:1200:1400);
  $skew(posedge clk1, posedge clk, 50);
  $recovery(posedge d, clk, 200);
 endspecify

 xl_fd3 /* #10 */ i0(q, d, clk, clr, set);
 // buf i1(q, xxx);
 // not i2(qn, xxx);
endmodule

primitive xl_fd3(q, d, clk, clr, set);
 output q; reg q;
 input d, clk, clr, set;

 table
  // d  clk  clr  set  :  q  :  q
  // -  ---  ---  ---  -  -  -  -
  // set/clear low assertion 
     ?   ?    ?    0   :  ?  :  1 ;
     ?   ?    ?    x   :  ?  :  x ;
     ?   ?    0    1   :  ?  :  0 ;
     ?   ?    x    1   :  ?  :  x ;

     0   r    1    1   :  ?  :  0 ;
     1   r    1    1   :  ?  :  1 ;
     x   r    1    1   :  ?  :  x ;

     ?   f    1    1   :  ?  :  - ;
     ?  (x?)  1    1   :  ?  :  - ;
     ?  (?x)  1    1   :  ?  :  - ;
     *   ?    1    1   :  ?  :  - ;
     ?   ?    r    1   :  ?  :  - ;
     ?   ?    1    r   :  ?  :  - ;
 endtable
endprimitive
