//                              -*- Mode: Verilog -*-
// Filename        : k68_cpu.v
// Description     : RISC 68K
// Author          : Shawn Tan
// Created On      : Sat Feb  8 02:23:38 2003
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

`include "k68_defines.v"

//
// CLOCK DIVIDER TO GENERATE CLK and CLK/4
//

module k68_clkgen (/*AUTOARG*/
   // Outputs
   clk4_o, clk_o, rst_o, 
   // Inputs
   clk_i, rst_i
   ) ;

   input clk_i,rst_i;
   output clk4_o;
   output clk_o;
   output rst_o;
   reg 	  rst_o;
   
   reg [1:0] 	    cnt;

   assign    clk4_o = cnt[1];
   assign    clk_o = ~clk_i;
   
   initial cnt = 0;	// Power up state doesn't matter, but can't be X

   always @(posedge clk_i) begin
	cnt <= cnt + 1'b1;
   end

   always @(posedge clk4_o) rst_o <= rst_i;
      
endmodule // k68_clkgen

