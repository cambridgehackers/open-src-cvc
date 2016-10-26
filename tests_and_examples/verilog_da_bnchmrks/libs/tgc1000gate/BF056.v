// Verilog Interface section

module BF056 (  A1 , A2 , B1 , B2 , Y );

// Verilog Port Declaration section

   input  A1;
   input  A2;
   input  B1;
   input  B2;
   output Y;


// Verilog Structure section (in terms of gate prims)

            or   ( E2EG_5944 , B1 , B2 ) ;

          nand  #1 ( Y , A1 , E2EG_5944 , A2 ) ;

endmodule
