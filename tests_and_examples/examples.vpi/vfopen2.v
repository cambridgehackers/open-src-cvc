module test;

reg		clk;

integer         tmp_channel;
    initial
      begin
	clk = 0;

	#2000 $vpi_fopen_task("vpitout.fil", tmp_channel);
        $display("writing to vpitout.fil.");
	$fdisplay(tmp_channel | 5,"tmp_channel %d",tmp_channel);
	$fclose(tmp_channel);	

	#4000 $finish;

      end

  always
    begin
      #1000 clk = ~clk;
    end

endmodule

