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
// 1 CLK 32bit ROX Shifter
//
module k68_roxx (/*AUTOARG*/
   // Outputs
   res, 
   // Inputs
   in, xin, step
   ) ;
   parameter dw = `k68_DATA_W;
   
   output [dw:0] res;
   input [dw-1:0] in;
   input 	xin;
   input [6:0] 	step;
   reg [dw:0] res;
   reg [5:0] 	move;
   
   always @ ( /*AUTOSENSE*/step) begin
      if (step[6]) 
	move <= 6'd33 - step[5:0];
      else
	move <= step[5:0];
   end
   	     
   always @ ( /*AUTOSENSE*/in or move or xin) begin
      //
      // Barrel Shift
      //
      case (move)
	6'd01: res <= {in[30:0],xin,in[31]};
	6'd02: res <= {in[29:0],xin,in[31:30]};
	6'd03: res <= {in[28:0],xin,in[31:29]};
	6'd04: res <= {in[27:0],xin,in[31:28]};
	6'd05: res <= {in[26:0],xin,in[31:27]};
	6'd06: res <= {in[25:0],xin,in[31:26]};
	6'd07: res <= {in[24:0],xin,in[31:25]};
	6'd08: res <= {in[23:0],xin,in[31:24]};
	6'd09: res <= {in[22:0],xin,in[31:23]};
	6'd10: res <= {in[21:0],xin,in[31:22]};
	6'd11: res <= {in[20:0],xin,in[31:21]};
	6'd12: res <= {in[19:0],xin,in[31:20]};
	6'd13: res <= {in[18:0],xin,in[31:19]};
	6'd14: res <= {in[17:0],xin,in[31:18]};
	6'd15: res <= {in[16:0],xin,in[31:17]};
	6'd16: res <= {in[15:0],xin,in[31:16]};
	6'd17: res <= {in[14:0],xin,in[31:15]};
	6'd18: res <= {in[13:0],xin,in[31:14]};
	6'd19: res <= {in[12:0],xin,in[31:13]};
	6'd20: res <= {in[11:0],xin,in[31:12]};
	6'd21: res <= {in[10:0],xin,in[31:11]};
	6'd22: res <= {in[9:0],xin,in[31:10]};
	6'd23: res <= {in[8:0],xin,in[31:9]};
	6'd24: res <= {in[7:0],xin,in[31:8]};
	6'd25: res <= {in[6:0],xin,in[31:7]};
	6'd26: res <= {in[5:0],xin,in[31:6]};
	6'd27: res <= {in[4:0],xin,in[31:5]};
	6'd28: res <= {in[3:0],xin,in[31:4]};
	6'd29: res <= {in[2:0],xin,in[31:3]};
	6'd30: res <= {in[1:0],xin,in[31:2]};
	6'd31: res <= {in[0],xin,in[31:1]};
	6'd32: res <= {xin,in[31:0]};
	default: res <= {in[31:0],xin};
	
      endcase // case(step)
   end

endmodule // k68_barrel
