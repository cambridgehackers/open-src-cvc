 
primitive JK_Q (q, j, k, clk, pre, clr);
 
// FUNCTION : POSITIVE EDGE TRIGGERED JK FLIP FLOP, WITH ACTIVE LOW 
//            ASYNCHRONOUS CLEAR AND  SET  ( Q OUTPUT UDP ). 


    output q;
    reg    q;  
    input  j,k,
            clk,                                  // Clock.
            clr,                                  // Clear input.
            pre;                                  // Set input.
                                  

    table
      // j   k   clk  pre  clr   : Qtn : Qtn+1

         0   0  (01)  1    1     :  ?  :   - ;    // Output retains the 

         0   1  (01)  1    1     :  ?  :   0 ;    // Clocked J and K.
         0   1  (01)  1    x     :  ?  :   0 ;    // pessimism
         ?   ?   ?    1    x     :  0  :   0 ;    // pessimism

         1   0  (01)  1    1     :  ?  :   1 ;    
         1   0  (01)  x    1     :  ?  :   1 ;    // pessimism
         ?   ?   ?    x    1     :  1  :   1 ;    // pessimism

         1   1  (01)  1    1     :  0  :   1 ;    // Clocked toggle.
         1   1  (01)  1    1     :  1  :   0 ;
                                                     
         ?   1  (01)  1    x     :  1  :   0 ;     //pessimism
         1   ?  (01)  x    1     :  0  :   1 ;
  
         0   0  (x1)  1    1     :  ?  :   - ;   //possible clocked JK
         0   1  (x1)  1    1     :  0  :   0 ;   
         1   0  (x1)  1    1     :  1  :   1 ;
         0   0  (0x)  1    1     :  ?  :   - ;
         0   1  (0x)  1    1     :  0  :   0 ;
         1   0  (0x)  1    1     :  1  :   1 ;

                                 
         *   ?   ?    1    1     :  ?  :   - ;    // Insensitive to 
         ?   *   ?    1    1     :  ?  :   - ;    // transitions on J and K
                                                 // with steady clock.

         ?   ?   ?    0    1     :  ?  :  1  ;    // Set.
         ?   ?   ?    ?    0     :  ?  :  0  ;    // clear and  clear override.

         ?   ? (?0)   1    1     :   ? :  -  ;    //ignore falling clock.
         ?   ? (1x)   1    1     :   ? :  -  ;
    
         x   0   r    1    1     :   1  :   1 ;         // reducing pessimism for unknown J 
         x   1   r    1    1     :   1  :   0 ;         // reducing pessimism for unknown J 
         0   x   r    1    1     :   0  :   0 ;         // reducing pessimism for unknown K 
         1   x   r    1    1     :   0  :   1 ;         // reducing pessimism for unknown K 

         x   0  (x1)  1    1     :   1  :   1 ;        //possible clocked with
         0   x  (x1)  1    1     :   0  :   0 ;        //possible J & K                                 
         x   0  (0x)  1    1     :   1  :   1 ;
         0   x  (0x)  1    1     :   0  :   0 ;

         ?   ?   ?    1  (?1)    :  ?   :  -  ;    //ignore changes on set and
         ?   ?   ?   (?1)  1     :  ?   :  -  ;    //reset.


    endtable

endprimitive
