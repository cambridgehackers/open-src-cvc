// Verilog Interface section

module BF052 (  A1 , B1 , B2 , B3 , Y );

// Verilog Port Declaration section

   input  A1;
   input  B1;
   input  B2;
   input  B3;
   output Y;


// Verilog Structure section (in terms of gate prims)

            or   ( E2EG_5942 , B3 , B1 , B2 ) ;

          nand  #1 ( Y , E2EG_5942 , A1 ) ;

endmodule
