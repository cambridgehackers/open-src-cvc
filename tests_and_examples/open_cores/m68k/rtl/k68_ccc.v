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
// CC Condition Calc
//
module k68_ccc(/*AUTOARG*/
   // Outputs
   flag, 
   // Inputs
   cc, code
   );

   parameter XF = `k68_X_FLAG;
   parameter CF = `k68_C_FLAG;
   parameter NF = `k68_N_FLAG;
   parameter ZF = `k68_Z_FLAG;
   parameter VF = `k68_V_FLAG;
      
   input [7:0] cc;
   input [3:0] code;
   output      flag;
   reg 	       flag;

   always @(/*AUTOSENSE*/cc or code) begin
      case (code)
	4'h4: flag = ~cc[CF];
	4'h5: flag = cc[CF];
	4'h7: flag = cc[ZF];
	4'hC: flag = cc[NF] & cc[VF] | ~cc[NF] & ~cc[VF];
	4'hE: flag = cc[NF] & cc[VF] & ~cc[ZF] | ~cc[NF] & ~cc[VF] & ~cc[ZF];
	4'h2: flag = ~cc[CF] & ~cc[ZF];
	4'hF: flag = cc[ZF] | cc[NF] & ~cc[VF] | ~cc[NF] & cc[VF];
	4'h3: flag = cc[CF] | cc[ZF];
	4'hD: flag = cc[NF] & ~cc[VF] | ~cc[NF] & cc[VF];
	4'hB: flag = cc[NF];
	4'h6: flag = ~cc[ZF];
	4'hA: flag = ~cc[NF];
	4'h8: flag = ~cc[VF];
	4'h9: flag = cc[VF];
	4'h1: flag = 1'b0;
	4'h0: flag = 1'b1;
	//default: flag = 1'b0;
      endcase // case(code)
   end
   
endmodule // k68_ccc
