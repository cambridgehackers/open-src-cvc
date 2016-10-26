primitive aoiudp 
(out, in1, in2, in3, in4);
input in1, in2, in3, in4;
output out;
   table    
//     in1  in2  in3  in4  : out ;
        0    ?    0    ?   :  1  ;
        0    ?    ?    0   :  1  ;
        ?    0    0    ?   :  1  ;
        ?    0    ?    0   :  1  ;
        1    1    ?    ?   :  0  ;
        ?    ?    1    1   :  0  ;
   endtable
endprimitive
