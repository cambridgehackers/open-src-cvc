// Verilog Interface section

module BF051 (  A1 , B1 , B2 , Y );

// Verilog Port Declaration section

   input  A1;
   input  B1;
   input  B2;
   output Y;


// Verilog Structure section (in terms of gate prims)

            or   ( E2EG_5937 , B1 , B2 ) ;

          nand  #1 ( Y , E2EG_5937 , A1 ) ;

endmodule

