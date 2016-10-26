module task10;
    reg [31:0] aa, x;
    reg bb, y, nochg;
    integer count;
    initial count = 0;

    event e1;

    task t1;
	input [31:0] a;
	input b;
	output [31:0] c;
	output  d;
	reg d;
	reg [31:0] c;
	begin
	    $display($stime, " t1 started"); 

	    d = b;
	    #10 c = a;
	    #10 count = count + 1;
	    $display($stime, " t1 finished"); 

	    end
	endtask

    initial begin
        x = 31'hxxxxxxxx;
        #10;    
        aa = 0;
	bb = 0;
	x = -1;
	y = 1;
	$display($stime," start   x: %x  y: %x  count: %0d", x, y, count);
        t1(aa, bb, x, y);
	$display($stime," return  x: %x  y: %x  count: %0d", x, y, count);

	aa = aa + 1;
	bb = ~bb;
	->e1;
        t1(aa, bb, x, y);
	$display($stime," return  x: %x  y: %x  count: %0d", x, y, count);

	aa = aa + 1;
	bb = ~bb;
        t1(aa, bb, x, y);
	$display($stime," return  x: %x  y: %x  count: %0d", x, y, count);

	end

    initial begin
	@e1 ;
	#5  disable t1;
	end
    
    always begin @nochg ; end

    endmodule
