// Verilog Interface section

module NA310 (  A , B , C , Y );

// Verilog Port Declaration section

   input  A;
   input  B;
   input  C;
   output Y;


// Verilog Structure section (in terms of gate prims)


          nand  #1 ( Y , C , A , B ) ;

endmodule
