// Verilog Interface section

module EX210 (  A , B , Y );

// Verilog Port Declaration section

   input  A;
   input  B;
   output Y;


// Verilog Structure section (in terms of gate prims)


           xor  #1 ( Y , B , A ) ;

endmodule

