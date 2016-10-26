// Verilog Interface section

module NA311 (  A , B , C , Y );

// Verilog Port Declaration section

   input  A;
   input  B;
   input  C;
   output Y;


// Verilog Structure section (in terms of gate prims)

           not   ( IINVnet1 , A ) ;

          nand  #1 ( Y , C , IINVnet1 , B ) ;

endmodule
