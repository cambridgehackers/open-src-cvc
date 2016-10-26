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

//
// Bench Interface to Soft ROM
//

module k68_testrom (/*AUTOARG*/
   // Outputs
   dat_o, 
   // Inputs
   add_i
   );
   
   input [31:0] add_i;
   output [31:0] dat_o;

   //reg [31:0] 	 dat_o;
   reg [31:0] 	 mem [0:10240];

   wire [9:0] 	 add;

   assign 	 add = add_i[11:2];
 	 
   
   initial begin
`include "test.rom.vh"
   end
      
   assign  dat_o = mem[add];

   //always @(dat_o) $write("[%0t] Read %x -> %x\n", $time, add, dat_o);
      
endmodule // k68_testrom

