
module complex_mul;
  defparam UMLP.N=12;
  defparam UMLP.M=13;
  Mult0 UMLP (); //end of Mult0 UMLP

  defparam UMLR.N=12;
  defparam UMLR.M=13;
  Mult0 UMLR (); //end of Mult0 UMLR

endmodule

module Mult0 ;
  parameter N=12;
  parameter M=12;
  parameter Q=N+M;
  reg  [M:0] datab;

  defparam U_MULT00.MULT_N=N-1;
  defparam U_MULT00.MULT_M=M-1;
  mult U_MULT00 (
    .b(datab[M-1:0]),
    .r(aXb)
  );

endmodule

module mult (
    b,
    r
  );
  parameter MULT_N =8;
  parameter MULT_M =8;
  parameter MULT_NM=MULT_M + MULT_N + 2;
  input  [MULT_M :0] b;
  output [MULT_NM:0] r;

endmodule
