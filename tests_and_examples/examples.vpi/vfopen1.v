module test;

reg		clk;

integer         tmp_channel;
    initial
      begin
	clk = 0;

	#2000 tmp_channel = $vpi_fopen("vpifout.fil");
        $display("... writing to file vpifout.fil.");
	$fdisplay(tmp_channel | 5,"tmp_channel %d",tmp_channel);
	$fclose(tmp_channel);	

	#4000 $finish;

      end

  always
    begin
      #1000 clk = ~clk;
    end

endmodule

