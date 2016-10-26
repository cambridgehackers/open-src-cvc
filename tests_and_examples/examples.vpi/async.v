/*
 * async driven not gate cpu PLI model .v file
 */
module top;
    wire z;
    reg a;
    initial
        begin
            $monitor($stime,, "z=%b, a=%b", z, a);   
            $pli_not(z, a);
        end
    initial
        begin
           #10 a = 1'bz;
           #10 a = 1;
           #10 a = 0;
           #10 a = 1;
           // notice glitch that PLI model maybe should catch 
            #1 a = 0;
        end
endmodule
