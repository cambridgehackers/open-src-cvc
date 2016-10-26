// Verilog Interface section

module BF001 (  A1 , B1 , B2 , Y );

// Verilog Port Declaration section

   input  A1;
   input  B1;
   input  B2;
   output Y;


// Verilog Structure section (in terms of gate prims)

           and   ( E2EG_5923 , B1 , B2 ) ;

           nor  #1 ( Y , A1 , E2EG_5923 ) ;

endmodule
