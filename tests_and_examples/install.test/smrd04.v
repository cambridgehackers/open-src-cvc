module top;
 parameter idprom_width = 10, idprom_depth = 2, step = 20;
 reg [8*idprom_width:1] s1, s2;
 integer index;

 reg [idprom_width:1] idprom[1:idprom_depth];

 initial
  begin
   // probably should do some checking here
   if ($scan$plusargs("idprom1=", s1) == 0
    || $scan$plusargs("idprom2=", s2) == 0) 
    begin
     $display("missing or bad idprom option(s)"); 
     $finish;
    end
   $sreadmemb(idprom,,, s1, s2);
   for (index = 0; index < idprom_depth; index = index + 1) #step;
   for (index = 1; index <= idprom_depth; index = index + 1)   
    $display("idprom[%0d]=%b", index, idprom[index]); 
  end
endmodule
