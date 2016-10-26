//                              -*- Mode: Verilog -*-
// Filename        : k68_soc_test.v
// Description     : k68 SOC Test Bench
// Author          : Shawn Tan
// Created On      : Sat Feb 15 18:08:50 2003
// Last Modified By: .
// Last Modified On: .
// Update Count    : 0
// Status          : Unknown, Use with caution!
/////////////////////////////////////////////////////////////////////
////                                                             ////
//// Copyright (C) 2002 to Shawn Tan Ser Ngiap.                  ////
////                       shawn.tan@aeste.net                   ////
////                                                             ////
//// This source file may be used and distributed without        ////
//// restriction provided that this copyright statement is not   ////
//// removed from the file and that any derivative work contains ////
//// the original copyright notice and the associated disclaimer.////
////                                                             ////
////     THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY     ////
//// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   ////
//// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS   ////
//// FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL THE AUTHOR      ////
//// OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,         ////
//// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    ////
//// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE   ////
//// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR        ////
//// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF  ////
//// LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT  ////
//// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  ////
//// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE         ////
//// POSSIBILITY OF SUCH DAMAGE.                                 ////
////                                                             ////
/////////////////////////////////////////////////////////////////////

`timescale 1ns / 10ps

module bench;

   reg 	       clk,arbclk_i,rst;
   
   k68_soc_test k68_soc_test
     (/*AUTOINST*/
      // Inputs
      .clk				(clk),
      .rst				(rst),
      .arbclk_i				(arbclk_i)); 
   

   initial begin
      //$dumpfile("foo.vcd");
      //$dumpvars(99,bench);
      clk = 1;
      arbclk_i = 1;
      rst = 0;
      #40 rst = 1;
      #100000000;
      $finish;
   end
   
   initial forever begin
      #5 clk = ~clk;
   end

   initial forever begin
      #1 arbclk_i = ~arbclk_i;
   end

endmodule
