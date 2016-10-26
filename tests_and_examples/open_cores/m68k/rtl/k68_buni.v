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
// BUS Unifier
//
module k68_buni (/*AUTOARG*/
   // Outputs
   cs_o, we_o, add_o, dat_o, p_dat_o, m_dat_o, 
   // Inputs
   clk_i, rst_i, p_add_i, m_add_i, dat_i, m_dat_i, m_we_i
   ) ;
   parameter aw = `k68_ADDR_W;
   parameter dw = `k68_DATA_W;
   parameter ow = `k68_OP_W;
   parameter xxxx = `XXXX;
   parameter zero = `ZERO;
   
   input     clk_i, rst_i;
   output    cs_o, we_o;
   
   input [aw-1:0] p_add_i, m_add_i;
   output [aw-1:0] add_o;

   input [dw-1:0]  dat_i;
   output [dw-1:0] dat_o;
       
   input [dw-1:0]  m_dat_i;
   output [ow-1:0]  p_dat_o;
   output [dw-1:0]  m_dat_o;

   input 	    m_we_i;
   reg [1:0] 	    uni_cnt;
 

   // Chip select always ON becuase it's either Program or Data Access
   assign 	    cs_o = 1'b1;
   
   assign 	    m_dat_o = (uni_cnt == 2'b00) ? xxxx : dat_i;
   assign 	    p_dat_o = (uni_cnt == 2'b00) ? dat_i : xxxx;
   assign 	    add_o = (uni_cnt == 2'b00) ? p_add_i : m_add_i;
   assign 	    dat_o = m_dat_i;
   assign 	    we_o = (uni_cnt == 2'b00) ? 1'b0 : m_we_i;
   
   //
   // Synchronouse Count
   always @(posedge clk_i) begin
      if (rst_i)
	uni_cnt <= 2'b00;
      else
	uni_cnt <= uni_cnt + 2'b01;
   end
      
endmodule // k68_sba
