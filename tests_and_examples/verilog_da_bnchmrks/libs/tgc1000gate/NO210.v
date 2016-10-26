// Verilog Interface section

module NO210 (  A , B , Y );

// Verilog Port Declaration section

   input  A;
   input  B;
   output Y;


// Verilog Structure section (in terms of gate prims)


           nor  #1 ( Y , A , B ) ;

endmodule
