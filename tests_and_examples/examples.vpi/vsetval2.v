//
// test of strdelputp - copy from input system task to output then
// compare results to make same
//

module top;
 xx i1();
endmodule

module xx;
 integer i;
 reg [31:0] rwa; 
 reg rw;
 reg [15:0] a, b;
 wire w;
 wire [31:0] wa; 
 parameter d = 500; 

 assign wa = rwa;
 assign w = rw;

 initial
  begin
   $monitor($stime,, "a=%b", a); 
   a = 0; rwa = 0;
   for (i = 0; i < 1000; i = i + 100) 
    begin
     $vsetval(a[5], rwa, i + 25, "vpiPureTransportDelay");
     rwa[0] = ~rwa[0];
    end
   #2000; 
  end
endmodule
