/*
 * test calling Verilog task from C using DPI export
 */
module test_export;
 import "DPI-C" task ctask;

 export "DPI-C" task verilogtask;


 initial begin
   ctask;
 end

 task verilogtask(input reg r, input reg r2, input reg r3);
  $display("Verilog Task r=%d r2=%d r3=%d", r, r2, r3);
 endtask
endmodule

