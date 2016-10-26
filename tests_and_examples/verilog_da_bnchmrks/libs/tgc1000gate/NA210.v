// Verilog Interface section

module NA210 (  A , B , Y );

// Verilog Port Declaration section

   input  A;
   input  B;
   output Y;


// Verilog Structure section (in terms of gate prims)


          nand  #1 ( Y , A , B ) ;

endmodule

