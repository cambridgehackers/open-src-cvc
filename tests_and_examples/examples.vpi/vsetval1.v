//
// test of strdelputp - copy from input system task to output then
// compare results to make same
//

module top;
 xx i1();
 xx i2();
 xx i3();
 xx i4();
 initial
  begin  
   $monitor($stime,, "a=%h, w=%b (rw=%b), wa=%b (rwa=%b)", 
     i2.a, i2.w, i2.rw, i2.wa, i2.rwa); 
  end
endmodule

module xx;
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
   a = 0; rw = 0;
   // blocks changes a 15 reg and w (1 bit wire) only */
   $vsetval(a[5], 1'b1, 25, "vpiInertialDelay");
   /* schedule put value to register - just assigns */
   #100 $vsetval(a, 16'h55aa, 90);  
   /* notice minor bug here since w is a scalar vector is 16 bits, it */
   /* happens that at least in CVC narrowing width change assigns work, */
   /* but widening especially into a higher word probably core dumps */
   /* also this will schedule transition to x at 290 since other driver 0 */
   #100 $vsetval(w, 16'haa55, 90);  
   /* remove vpi_set_value driver conflict, so schedule back to 0 at 340 */ 
   #100 $vsetval(w, 16'hzzzz, 40);
   /* cancel schedule of one bit to z, uses last event, w just place holder */
   #20 $vsetval(w, 0, 0, "vpiCancelEvent");  
   #100 rw = 1'bz; $vsetval(w, 1, 63); 
   /* this is inertial reschedule (remove early, save late) */ 
   #30 $vsetval(w, 0, 50);
  end

 initial
  begin
   // blocks changes wire wa only */
   rwa = 32'b0;
   #1000 
   #100 $vsetval(wa[5], 1'b1, 25, "vpiInertialDelay");
   #100 $vsetval(wa[5], 1'b0, 25, "vpiInertialDelay");
   #100 $vsetval(wa, 20'h5aa55, 90); rwa = 32'bz;  
   #10 $vsetval(wa, 32'hffffffff, 0, "vpiForceFlag");
   #10 $vsetval(wa, 0, 0, "vpiReleaseFlag");
   #80 $vsetval(wa, 20'ha55aa, 80);  
  end
endmodule
