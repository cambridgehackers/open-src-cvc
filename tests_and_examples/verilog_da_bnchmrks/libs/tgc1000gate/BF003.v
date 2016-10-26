// Verilog Interface section

module BF003 (  A1 , A2 , B1 , B2 , Y );

// Verilog Port Declaration section

   input  A1;
   input  A2;
   input  B1;
   input  B2;
   output Y;


// Verilog Structure section (in terms of gate prims)


        aoiudp  #1 ( Y , B1 , B2 , A1 , A2 ) ;

endmodule
