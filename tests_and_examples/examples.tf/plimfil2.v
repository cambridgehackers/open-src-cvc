module xx; 
 reg [31:0] mem2[1:5];

initial
  begin
   fillmem;  
   $display("writing filled memory values:"); 
   writemem;
  end

 task fillmem;
  integer i; 
  begin
   if ($pli_setupmemfil2(5, 32) == 0) $finish;
   // since propagatep assignment immediate evaluate of drivers
   // do not need delay here
   for (i = 1; i <= 5; i = i + 1) 
    begin  
     // only need 2nd index argument for checking */
     if ($pli_memfil2(mem2[i], i) == 0) $finish;
    end
  end
 endtask

 task writemem; 
  integer i;
  begin
   for (i = 1; i <= 5; i = i + 1) $display("%0d: %0d", i, mem2[i]);
   $write("\n");
  end
 endtask
endmodule
