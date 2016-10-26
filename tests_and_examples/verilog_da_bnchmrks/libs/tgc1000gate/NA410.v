// Verilog Interface section

module NA410 (  A , B , C , D , Y );

// Verilog Port Declaration section

   input  A;
   input  B;
   input  C;
   input  D;
   output Y;


// Verilog Structure section (in terms of gate prims)


          nand  #1 ( Y , A , B , C , D ) ;

endmodule
