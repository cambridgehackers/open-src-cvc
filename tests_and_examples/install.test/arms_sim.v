////////////////////////////////////////////////////////////////////////////////
// ARMS_COUNTER test vectors
// translated to Verilog from VHDL by Sari Coumeri 
// original VHDL obtained from the '92 High Level Synthesis Benchmarks
// January 1994
////////////////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps
module ARMS_COUNTER_sim;

   reg CLK;
   reg STRB;
   reg [1:0] CON;
   reg [3:0] DATA;
   wire [3:0] COUT;

   integer i;
   ARMS_COUNTER ARMS_COUNTER_1 (CLK,STRB,CON,DATA,COUT);

    // SJM add for debugging
    // initial $monitor($stime,, "CLK=%b, STRB=%b, CON=%b, DATA=%b, COUT=%b",
    //  CLK, STRB, CON, DATA, COUT);

//////- The Clock always

   always
   begin
#1;
      CLK =  1'b0;
#49;
      CLK =  1'b1;
   end

//////- The Counter always

   initial
   begin
 //  $dumpvars;
 //  CLK = 1'b0;
 //  STRB = 1'b0;
 //  CON = 2'b00;
 //  DATA = 4'b0000;
   // repeat(10000)
   repeat(20)
   begin
#30;

// TEST 1 start off with simple test of reset, count up, && count down, && limit

      // reset the counter
      CON = 2'b00;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;

#50;
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0000");
      
      // load the LIMIT to 2
      DATA = 4'b0010;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;

      // count up
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0001) $display($time,,,"COUT !== 4'b0001");
      
      // count up again
#50;
if (COUT !== 4'b0010) $display($time,,,"COUT !== 4'b0010");

      // count up, should not increment since hit limit
#50;
if (COUT !== 4'b0010) $display($time,,,"COUT !== 4'b0010");
      
      // count up, should not increment since limit is hit eventhough countup signal is enabled
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0011) $display($time,,,"COUT !== 4'b0011");
      
      // count down, cannot decrement since limit is hit && we do not know from which
      // direction the limit is hit
      CON = 2'b11;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0010) $display($time,,,"COUT !== 4'b0010");
      
      // load the LIMIT to 0
      DATA = 4'b0000;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
      
      // count down
      CON = 2'b11;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0001) $display($time,,,"COUT !== 4'b0001");

// TEST2 Perform some extensive testing of the counter's limit handling

      // set limit to 13
      DATA = 4'b1101;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;

      // reset the counter
      CON = 2'b00;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0000");
      
      // count up to 13
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
      for (i = 1; i <= 13; i = i + 1)
begin

#50;
      end
if (COUT !== 4'b1101) $display($time,,,"COUT !== 4'b1101");
 
      // count up, should not increment since hit limit
#50;
if (COUT !== 4'b1101) $display($time,,,"COUT !== 4'b1101");
      
      // count up, should not increment since hit limit
      CON = 2'b10;
#50;
if (COUT !== 4'b1101) $display($time,,,"COUT !== 4'b1101");
      
      // change limit to 15
      DATA = 4'b1111;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;

      // count up
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b1110) $display($time,,,"COUT !== 4'b1110");

      // count up
#50;
if (COUT !== 4'b1111) $display($time,,,"COUT !== 4'b1111");

      // count up, should not increment since hit limit
#50;
if (COUT !== 4'b1111) $display($time,,,"COUT !== 4'b1111");
      
      // change limit to 7 
      DATA = 4'b0111;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;

      // count down, try counting below 7
      CON = 2'b11;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
      for (i = 1; i <= 10; i = i + 1)
begin

#50;
      end
if (COUT !== 4'b0111) $display($time,,,"COUT !== 4'b0111");
         
      // change limit to 0 
      DATA = 4'b0000;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
 
      // count down, try counting below 8
      CON = 2'b11;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
      for (i = 1; i <= 8; i = i + 1)
begin

#50;
      end
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0000");
         
      // count up, should not increment since hit limit
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0000");
      
// TEST3 Try counting beyond the range, i.e. above 15 && below 0

      // reset the counter
      CON = 2'b00;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0000");

      // change limit to 7 
      DATA = 4'b0111;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;

      // count up 1 
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0001) $display($time,,,"COUT !== 4'b0001");
      
      // count down  
      CON = 2'b11;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0000");
    
      // count down  
#50;
if (COUT !== 4'b1111) $display($time,,,"COUT !== 4'b1111");
      
      // count down  
#50;
if (COUT !== 4'b1110) $display($time,,,"COUT !== 4'b1110");
      
      // count up 
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b1111) $display($time,,,"COUT !== 4'b1111");
      
      // count up 
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0000");

// TEST4 Checking for counting sequence from 0 to 15 && from 15 to 0

      // reset the counter
      CON = 2'b00;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0000");

      // change limit to 15
      DATA = 4'b1111;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;

      // count up 15 times
      CON = 2'b10;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;

#50;
if (COUT !== 4'b0001) $display($time,,,"COUT !== 4'b0001");

#50;
if (COUT !== 4'b0010) $display($time,,,"COUT !== 4'b0010");

#50;
if (COUT !== 4'b0011) $display($time,,,"COUT !== 4'b0011");

#50;
if (COUT !== 4'b0100) $display($time,,,"COUT !== 4'b0100");

#50;
if (COUT !== 4'b0101) $display($time,,,"COUT !== 4'b0101");

#50;
if (COUT !== 4'b0110) $display($time,,,"COUT !== 4'b0110");

#50;
if (COUT !== 4'b0111) $display($time,,,"COUT !== 4'b0111");

#50;
if (COUT !== 4'b1000) $display($time,,,"COUT !== 4'b1000");

#50;
if (COUT !== 4'b1001) $display($time,,,"COUT !== 4'b1001");

#50;
if (COUT !== 4'b1010) $display($time,,,"COUT !== 4'b1010");

#50;
if (COUT !== 4'b1011) $display($time,,,"COUT !== 4'b1011");

#50;
if (COUT !== 4'b1100) $display($time,,,"COUT !== 4'b1100");

#50;
if (COUT !== 4'b1101) $display($time,,,"COUT !== 4'b1101");

#50;
if (COUT !== 4'b1110) $display($time,,,"COUT !== 4'b1110");

#50;
if (COUT !== 4'b1111) $display($time,,,"COUT !== 4'b1111");
      
      // change limit to 0
      DATA = 4'b0000;
      CON = 2'b01;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;
#50;

      // count down 15 times 
      CON = 2'b11;
	STRB <= #10 1'b1;
	STRB <= #20 1'b0;

#50;
if (COUT !== 4'b1110) $display($time,,,"COUT !== 4'b1110");

#50;
if (COUT !== 4'b1101) $display($time,,,"COUT !== 4'b1101");

#50;
if (COUT !== 4'b1100) $display($time,,,"COUT !== 4'b1100");

#50;
if (COUT !== 4'b1011) $display($time,,,"COUT !== 4'b1011");

#50;
if (COUT !== 4'b1010) $display($time,,,"COUT !== 4'b1010");

#50;
if (COUT !== 4'b1001) $display($time,,,"COUT !== 4'b1001");

#50;
if (COUT !== 4'b1000) $display($time,,,"COUT !== 4'b1000");

#50;
if (COUT !== 4'b0111) $display($time,,,"COUT !== 4'b0111");

#50;
if (COUT !== 4'b0110) $display($time,,,"COUT !== 4'b0110");

#50;
if (COUT !== 4'b0101) $display($time,,,"COUT !== 4'b0101");

#50;
if (COUT !== 4'b0100) $display($time,,,"COUT !== 4'b0100");

#50;
if (COUT !== 4'b0011) $display($time,,,"COUT !== 4'b0011");

#50;
if (COUT !== 4'b0010) $display($time,,,"COUT !== 4'b0010");

#50;
if (COUT !== 4'b0001) $display($time,,,"COUT !== 4'b0001");

#50;
if (COUT !== 4'b0000) $display($time,,,"COUT !== 4'b0001");
#20;    
end
   $finish(2);
   end
endmodule







