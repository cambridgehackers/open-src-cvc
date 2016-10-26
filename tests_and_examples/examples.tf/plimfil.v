module xx; 
 reg [66:0] mem1[1:10];

initial
  begin
   fillmem;  
   $display("writing filled memory values:"); 
   writemem;
  end

 task fillmem;
  integer i; 
  begin
   if ($pli_setupmemfill(10, 67) == 0) $finish;
   for (i = 1; i <= 10; i = i + 1) 
    begin  
     if ($pli_memfill(mem1[i], i) == 0) $finish;
     // notice must delay after call because value of i cannot change 
     // but if mem fill used extension tf_strputp routine not needed
     // if you do not need portability, tf_strputp is better
     #10; 
    end
  end
 endtask

 task writemem; 
  integer i;
  begin
   for (i = 1; i <= 10; i = i + 1) $display("%0d: %b", i, mem1[i]);
   $write("\n");
  end
 endtask
endmodule
