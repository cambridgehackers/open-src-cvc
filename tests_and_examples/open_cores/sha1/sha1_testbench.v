/////////////////////////////////////////////////////////////////
// sha1_testbench.v  version 0.1
// 
// Generic verilog test bench that tests the SHA-1 implementation
//
// Paul Hartke, phartke@stanford.edu,  Copyright (c)2002
//
// The information and description contained herein is the
// property of Paul Hartke.
//
// Permission is granted for any reuse of this information
// and description as long as this copyright notice is
// preserved.  Modifications may be made as long as this
// notice is preserved.
// This code is made available "as is".  There is no warranty,
// so use it at your own risk.
// Documentation? "Use the source, Luke!"
/////////////////////////////////////////////////////////////////

module test;

   reg     clk;
   reg     start;
   reg [511:0] y;
   reg [31:0] data_in;
   reg load_in;
   reg [159:0] cv;
   reg use_prev_cv;
   wire        busy;
   wire        out_valid;
   wire [159:0] cv_next;
   reg          reset;

   sha1_exec sha1_exec (.clk(clk), .reset(reset), .start(start),
                        .data_in(data_in), .load_in(load_in),
                        .cv(cv), .use_prev_cv(use_prev_cv), .busy(busy), 
                        .out_valid(out_valid), .cv_next(cv_next));
   integer i;
   reg [159:0] expected_result;
   
   initial
   begin
      i = 0;
      
      clk = 0;
      start = 0;
      // Bits of input 
      y = 512'b0;
      cv = 160'h0;
      data_in = 32'b0;
      load_in = 1'b0;
      use_prev_cv = 1'b0;
      reset = 1;
      expected_result = 160'h0;
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      reset = 0;
      @(posedge clk);
      @(negedge clk);

      $display("Test Begun ...");
      @(posedge clk);
      y = {"abc", 8'h80, 416'd0, 61'd3, 3'd0};
      $display("  input is \"abc\"");
      expected_result = 160'ha9993e364706816aba3e25717850c26c9cd0d89d;
      inputdata(y);
      cv = 160'h67452301EFCDAB8998BADCFE10325476C3D2E1F0;
      start = 1;
      @(posedge clk);
      start = 0;
      while (busy == 1'd1)
        begin
           @(posedge clk);
        end
      $display("  result is %8h %8h %8h %8h %8h", cv_next[159:128], 
                  cv_next[127:96], cv_next[95:64], cv_next[63:32], 
                  cv_next[31:0]);
      if (cv_next == expected_result) 
        $display ("Passed...");
      else
        $display ("*** FAILED ***");
      $display("Test Done ...");       

      @(posedge clk);
    
      $display("");

      $display("Test Begun ...");
      @(posedge clk);
      y = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 8'h80, 56'd0};
      $display("  input is \"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq\"");
      expected_result = 160'h84983e441c3bd26ebaae4aa1f95129e5e54670f1;
      inputdata(y);
      cv = 160'h67452301EFCDAB8998BADCFE10325476C3D2E1F0;
      start = 1;
      @(posedge clk);
      start = 0;
      while (busy == 1'd1)
        begin
           @(posedge clk);
        end
      @(posedge clk);
      /*
      $display("  intermediate result is %8h %8h %8h %8h %8h", cv_next[159:128], 
                  cv_next[127:96], cv_next[95:64], cv_next[63:32], 
                  cv_next[31:0]);
      */
      y = {448'h0, 61'd56, 3'd0};
      inputdata(y);
      start = 1;
      use_prev_cv = 1;
      @(posedge clk);
      start = 0;
      use_prev_cv = 0;
      while (busy == 1'd1)
        begin
           @(posedge clk);
        end
      $display("  result is %8h %8h %8h %8h %8h", cv_next[159:128], 
                  cv_next[127:96], cv_next[95:64], cv_next[63:32], 
                  cv_next[31:0]);
      if (cv_next == expected_result) 
        $display ("Passed...");
      else 
        $display ("*** FAILED ***");
      $display("Test Done ..."); 

      $display("");
      @(posedge clk);

      //$finish;

      ///////////////////////////////////////////////////////////////////////
      // Warning!!!  The following test takes ~50 minutes on my machine!!
      ///////////////////////////////////////////////////////////////////////
      $display("Test Begun ...");
      @(posedge clk);
      y = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
      $display("  input is one million \"a\"s");
      expected_result = 160'h34aa973cd4c4daa4f61eeb2bdbad27316534016f;      
      inputdata(y);
      cv = 160'h67452301EFCDAB8998BADCFE10325476C3D2E1F0;
      start = 1;
      @(posedge clk);
      start = 0;
      while (busy == 1'd1)
        begin
           @(posedge clk);
        end
      @(posedge clk);
      
      /* $display("  ** %8h %8h %8h %8h %8h **", cv_next[159:128], 
                  cv_next[127:96], cv_next[95:64], cv_next[63:32], 
                  cv_next[31:0]); */
      for (i=1; i<15625 ; i=i+1)
        begin
          inputdata(y);
          start = 1;
          use_prev_cv = 1;
          @(posedge clk);
          start = 0;
          use_prev_cv = 0;
          while (busy == 1'd1)
          begin
            @(posedge clk);
          end
          if (i%10 == 0) $display("  %d of 15625 iterations completed", i);
        end
      y = {8'h80, 440'd0, 61'd1000000, 3'd0};
      inputdata(y);
      start = 1;
      use_prev_cv = 1;
      @(posedge clk);
      start = 0;
      while (busy == 1'd1)
        begin
           @(posedge clk);
        end
     
      $display("  result is %8h %8h %8h %8h %8h", cv_next[159:128], 
                  cv_next[127:96], cv_next[95:64], cv_next[63:32], 
                  cv_next[31:0]);
      if (cv_next == expected_result) 
        $display ("Passed...");
      else 
        $display ("*** FAILED ***");
      $display("Test Done ..."); 

      @(posedge clk);
      @(posedge clk);
      @(posedge clk);
      @(posedge clk);

      $finish;

   end // end of initial


  /////////////////////////////////////////////////////////
  // Create System Clock
  always #5 clk = ~clk;

  /////////////////////////////////////////////////////////
  // Debugging printouts of all pertinent state...
  /*
  always@(posedge clk)
  begin
    if (sha1_exec.state == 2'b01)
      $display("%8h %8h %8h %8h %8h -- %8h %8h %8h-- round: %d", 
        sha1_exec.sha1_round.a, sha1_exec.sha1_round.b, 
        sha1_exec.sha1_round.c, sha1_exec.sha1_round.d,
        sha1_exec.sha1_round.e, sha1_exec.sha1_round.w, 
        sha1_exec.sha1_round.f, sha1_exec.sha1_round.k, 
        sha1_exec.rnd_cnt_q);
  end
  */

  ////////////////////////////////////////////////////////////////////////
  // Dump VCD file
  ///////////////////////////////////////////////////////////////////////
  /*
  initial
    begin
       $vcdpluson(0,test);
    end
  */


task inputdata;
  input [511:0] y;
  integer i;

  begin
    for (i=0; i<=15; i=i+1) 
      begin
        data_in <= (y >> 512-((i+1)*32));
        load_in <= 1'b1;
        // $display("%8x", data_in);
        @(posedge clk) ; 
      end
    load_in = 1'b0;
  end
endtask

endmodule // test



