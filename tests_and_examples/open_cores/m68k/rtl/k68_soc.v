//                              -*- Mode: Verilog -*-
// Filename        : k68_soc.v
// Description     : k68 SOC Top Level
// Author          : Shawn Tan
// Created On      : Sat Feb  8 20:58:34 2003
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

module k68_soc (/*AUTOARG*/
   // Outputs
   add_o, dat_o, we_o, tx_o, rts_o, clk_o, rst_o, 
   // Inputs
   dat_i, rst_i, clk_i, arbclk_i, rx_i, cts_i, int_i
   ) ;
   parameter aw = `k68_ADDR_W;
   parameter dw = `k68_DATA_W;

   output [aw-1:0] add_o;
   input [dw-1:0]  dat_i;
   output [dw-1:0] dat_o;
   output 	   we_o;
   
   input 	   rst_i, clk_i;
   input	   arbclk_i;
   input [1:0] 	   rx_i,cts_i;
   output [1:0]    tx_o,rts_o;
   input [2:0] 	   int_i;
   output 	   clk_o;
   output 	   rst_o;
        
   wire 	   cs;
   wire [aw-1:0]   m_add_o;
   wire [dw-1:0]   m_dat_o;
   wire [dw-1:0]   m_dat_i;
   wire 	   m_we_o;
   wire 	   m_cs_o;
   
 	    
   wire [9:0] 	   a_dat_i, b_dat_i;
   wire 	   r_cs_o, r_we_o, a_cs_o, b_cs_o, a_we_o, b_we_o; 	    

   wire		   rst;
   wire [31:0] 	   d_dat_o,d_dat_i;
         
   wire		   arbclk = clk_i;

   assign 	   add_o = m_add_o;
   assign 	   dat_o = m_dat_o;
   assign 	   we_o = r_we_o;
 
   wire 	   unused_g_we_o;
   wire 	   unused_g_cs_o;

   //
   // Arbiter
   //
   k68_arb arb0 (
		 .m_we_o(r_we_o),
		 .m_cs_o(r_cs_o),
		 .m_dat_i(dat_i),
		 
		 .a_dat_i(a_dat_i),

		 .b_dat_i(b_dat_i),
		 
		 .m_add_i(m_add_o),
		 .m_we_i(m_we_o),
		 .m_dat_o(m_dat_i),

		 .g_we_o(unused_g_we_o),
		 .g_cs_o(unused_g_cs_o),
		 .g_dat_i(16'h0),

		 .rst_i(rst_o),
		 /*AUTOINST*/
		 // Outputs
		 .a_we_o		(a_we_o),
		 .a_cs_o		(a_cs_o),
		 .b_we_o		(b_we_o),
		 .b_cs_o		(b_cs_o),
		 // Inputs
		 .arbclk		(arbclk));

   //
   // Instantiate CPU
   //
   k68_cpu cpu0(
		.add_o(m_add_o),
		.dat_o(m_dat_o),
		.dat_i(m_dat_i),
		.we_o(m_we_o),
		
		.int_i(int_i),
		.cs_o(cs),
		.clk_o(clk_o), .rst_o(rst_o),
		.clk_i(clk_i), .rst_i(rst_i)
		);


   
`ifdef k68_UART
   //
   // k68_sasc
   //

   wire [7:0] 	   brg0,brg1;
   assign 	   brg0 = `k68_div0;
   assign 	   brg1 = `k68_div1;
      
   k68_sasc uart0(
		  .tx_o(tx_o[0]),
		  .rts_o(rts_o[0]),
		  .dat_i({brg1,brg0,m_dat_o[7:0]}),
		  .dat_o(a_dat_i),
		  .cts_i(cts_i[0]),
		  .rx_i(rx_i[0]),
		  .cs_i(a_cs_o),
		  .we_i(a_we_o),
		  .clk_i(clk_o),.rst_i(rst_o)
		  );
   
   k68_sasc uart1(
		  .tx_o(tx_o[1]),
		  .rts_o(rts_o[1]),
		  .dat_i({brg1,brg0,m_dat_o[7:0]}),
		  .dat_o(b_dat_i),
		  .cts_i(cts_i[1]),
		  .rx_i(rx_i[1]),
		  .cs_i(b_cs_o),
		  .we_i(b_we_o),
		  .clk_i(clk_o),.rst_i(rst_o)
		  );
`endif
  
 
endmodule // k68_soc
