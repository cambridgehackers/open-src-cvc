// Verilog Interface section

module BF053 (  A1 , A2 , B1 , B2 , Y );

// Verilog Port Declaration section

   input  A1;
   input  A2;
   input  B1;
   input  B2;
   output Y;


// Verilog Structure section (in terms of gate prims)

            or   ( E2EG_5940 , B1 , B2 ) ;
            or   ( E2EG_5942 , A1 , A2 ) ;

          nand  #1 ( Y , E2EG_5940 , E2EG_5942 ) ;

endmodule
