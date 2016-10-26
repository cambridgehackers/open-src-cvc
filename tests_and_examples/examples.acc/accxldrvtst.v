// specify test for fd clear/set flip flop
module test;
 wire t_q;  
 reg t_clk, t_clk0, t_clk1, t_clk2, t_d, t_clr, t_set;

 fd3noqn i1(t_q0, t_clk2, t_clk2, t_d0, t_clr0, t_set0);
 fd3noqn i2(t_q1, t_clk2, t_clk2, t_d1, t_clr1, t_set1);
 fd3noqn i3(t_q, t_clk, t_clk1, t_d, t_clr, t_set);

 initial 
  begin
   $test;
   $monitor($stime,, "q=%b, clk=%b, data=%b, clr=%b, set=%b",
    t_q, t_clk, t_d, t_clr, t_set);
  end
endmodule

module fd3noqn(q, clk, clk1, d, clr, set);
 output q;
 input clk, clk1, d, clr, set;
 wire xxx;

 xl_fd3 #10 i0(xxx, d, clk, clr, set);
 buf i1(q, xxx);
 not i2(qn, xxx);
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
