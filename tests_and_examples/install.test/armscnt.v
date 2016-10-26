////////////////////////////////////////////////////////////////////////////////
// ARMS_COUNTER
// translated to Verilog from VHDL by Sari Coumeri 
// original VHDL obtained from the '92 High Level Synthesis Benchmarks
// January 1994
////////////////////////////////////////////////////////////////////////////////

// `timescale 1ns / 100ps
module ARMS_COUNTER(CLK,STRB,CON,DATA,COUT);
   input CLK;
   input STRB;
   input [1:0] CON;
   input [3:0] DATA;
   output [3:0] COUT;

//VSS: design_style behavioural

   reg ENIT, RENIT;
   reg EN;
   reg [3:0] CONSIG;
   reg [3:0] LIM;
   reg [3:0] CNT;

   reg [1:0] CONREG;

   reg CNTE;

   assign COUT=CNT;
////////////////  The decoder ////////////////////////////////////-
initial
begin
   CONREG = 2'b00;
   CNTE = 1'b0;
   
end

always @(posedge STRB)
begin

    CONREG = CON;

    case (CONREG)
         2'b00:
begin
 CONSIG = 4'b0001;
end
         2'b01:
begin
 CONSIG = 4'b0010;
end
         2'b10:
begin
 CONSIG = 4'b0100; ENIT = 1'b1;
end
         2'b11:
begin
 CONSIG = 4'b1000; ENIT = 1'b1;
end
         default: ;
    endcase

end // Rising edge of STRB

always @(posedge RENIT)
begin

    ENIT = 1'b0;
  end


////////////////  The limit loader ////////////////////////////////////-

always @(negedge STRB)
begin

  if( (CONSIG[1] == 1'b1)  )
begin

    LIM = DATA;
  end

end


////////////////  The counter ////////////////////////////////////-


always @(posedge CONSIG[0])
begin

    CNT = 4'b0000;
  end

always @(posedge EN)
begin

      CNTE = 1'b1;
    end
always @(negedge EN)
begin

      CNTE = 1'b0;
    end

always @(posedge CLK)
begin
  if( (CNTE == 1'b1) )
begin

    if( (CONSIG[2] == 1'b1) )

      CNT = CNT + 4'b0001;
    else if (CONSIG[3] == 1'b1) 
          CNT = CNT - 4'b0001;
  end
end


////////////////  The comparator ////////////////////////////////////-

always  @(ENIT)
begin
if (ENIT == 1'b1) 
begin
  EN = 1'b1; RENIT = 1'b1;
  if( (EN == 1'b1) && (CNT == LIM) )
begin

    EN = 1'b0;
  end
end
else
begin

  RENIT = 1'b0;
  if( (EN == 1'b1) && (CNT == LIM) )
begin

    EN = 1'b0;
  end
end
end


always @(CNT)
begin
  if( (EN == 1'b1) && (CNT == LIM) )
begin

    EN = 1'b0;
  end

end



endmodule

