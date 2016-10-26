//                              -*- Mode: Verilog -*-
// Filename        : k68_prims.v
// Description     : RISC ALU blocks
// Author          : Shawn Tan
// Created On      : Sun Feb  9 00:06:41 2003
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
// BCD CONVERTER
//
module k68_b2d(/*AUTOARG*/
   // Outputs
   d, 
   // Inputs
   b
   );
   parameter dw = `k68_DATA_W;
   input [7:0] b;
   output [7:0] d;
   reg [7:0] 	d;

   always @ ( /*AUTOSENSE*/b) begin

      if (b[7:4] >= 4'd5)
	d[7:4] = b[7:4] - 2'd3;
      else
	d[7:4] = b[7:4];

      if (b[3:0] >= 4'd5)
	d[3:0] = b[3:0] - 2'd3;
      else
	d[3:0] = b[3:0];
            
   end
   
      
endmodule // k68_b2d
 