// Verilog Interface section

module IV110 (  A , Y );

// Verilog Port Declaration section

   input  A;
   output Y;


// Verilog Structure section (in terms of gate prims)


           not  #1 ( Y , A ) ;

endmodule
