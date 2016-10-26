// Verilog Interface section

module OR210 (  A , B , Y );

// Verilog Port Declaration section

   input  A;
   input  B;
   output Y;


// Verilog Structure section (in terms of gate prims)


            or  #1 ( Y , A , B ) ;

endmodule
