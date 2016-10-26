// Verilog Interface section

module BF002 (  A1 , B1 , B2 , B3 , Y );

// Verilog Port Declaration section

   input  A1;
   input  B1;
   input  B2;
   input  B3;
   output Y;


// Verilog Structure section (in terms of gate prims)

           and   ( E2EG_5924 , B3 , B1 , B2 ) ;

           nor  #1 ( Y , A1 , E2EG_5924 ) ;

endmodule
