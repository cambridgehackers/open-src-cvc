// Verilog Interface section

module BF006 (  A1 , A2 , B1 , B2 , Y );

// Verilog Port Declaration section

   input  A1;
   input  A2;
   input  B1;
   input  B2;
   output Y;


// Verilog Structure section (in terms of gate prims)

           and   ( E2EG_5924 , B1 , B2 ) ;

           nor  #1 ( Y , E2EG_5924 , A1 , A2 ) ;

endmodule

