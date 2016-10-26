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
// 1 CLK 32bit ASX Shifter
//
module k68_asx (/*AUTOARG*/
   // Outputs
   res, 
   // Inputs
   in, step
   ) ;
   parameter dw = `k68_DATA_W;
   
   output [dw-1:0] res;
   input [dw-1:0] in;
   input [5:0] 	  step;
   reg [dw-1:0] 	  res;
  
   always @ ( /*AUTOSENSE*/in or step) begin
      if (step[5])
	if (in[31])
	  case (step[4:0])
	    5'd01: res <= {1'b1,in[31:1]};
	    5'd02: res <= {2'b11,in[31:2]};
	    5'd03: res <= {3'b111,in[31:3]};
	    5'd04: res <= {4'b1111,in[31:4]};
	    5'd05: res <= {5'b11111,in[31:5]};
	    5'd06: res <= {6'b111111,in[31:6]};
	    5'd07: res <= {7'b1111111,in[31:7]};
	    5'd08: res <= {8'b11111111,in[31:8]};
	    5'd09: res <= {9'b111111111,in[31:9]};
	    5'd10: res <= {10'b1111111111,in[31:10]};
	    5'd11: res <= {11'b11111111111,in[31:11]};
	    5'd12: res <= {12'b111111111111,in[31:12]};
	    5'd13: res <= {13'b1111111111111,in[31:13]};
	    5'd14: res <= {14'b11111111111111,in[31:14]};
	    5'd15: res <= {15'b111111111111111,in[31:15]};
	    5'd16: res <= {16'b1111111111111111,in[31:16]};
	    5'd17: res <= {17'b11111111111111111,in[31:17]};
	    5'd18: res <= {18'b111111111111111111,in[31:18]};
	    5'd19: res <= {19'b1111111111111111111,in[31:19]};
	    5'd20: res <= {20'b11111111111111111111,in[31:20]};
	    5'd21: res <= {21'b111111111111111111111,in[31:21]};
	    5'd22: res <= {22'b1111111111111111111111,in[31:22]};
	    5'd23: res <= {23'b11111111111111111111111,in[31:23]};
	    5'd24: res <= {24'b111111111111111111111111,in[31:24]};
	    5'd25: res <= {25'b1111111111111111111111111,in[31:25]};
	    5'd26: res <= {26'b11111111111111111111111111,in[31:26]};
	    5'd27: res <= {27'b111111111111111111111111111,in[31:27]};
	    5'd28: res <= {28'b1111111111111111111111111111,in[31:28]};
	    5'd29: res <= {29'b11111111111111111111111111111,in[31:29]};
	    5'd30: res <= {30'b111111111111111111111111111111,in[31:30]};
	    5'd31: res <= {31'b1111111111111111111111111111111,in[31]};
	    default: res <= in;
	  endcase // case(step[4:0])
	else
	  res <= in >> step[4:0];
      else
	res <= in << step[4:0];
   end
   

endmodule // k68_barrel
