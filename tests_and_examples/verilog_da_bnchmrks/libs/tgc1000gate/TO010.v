// Verilog Interface section

module TO010 (  HI , LO );

// Verilog Port Declaration section

   output HI;
   output LO;
   supply0	GROUND;
   supply1	POWER;

// Verilog Structure section (in terms of gate prims)


           buf  #1 ( HI , POWER ) ;
           buf  #1 ( LO , GROUND ) ;

endmodule
