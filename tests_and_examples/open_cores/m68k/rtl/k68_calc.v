//                              -*- Mode: Verilog -*-
// Filename        : k68_load.v
// Description     : RISC @mode Calculator
// Author          : Shawn Tan
// Created On      : Sat Feb  8 09:58:04 2003
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
// General Address Mode Calculator (To Save Space)
//

module k68_calc (/*AUTOARG*/
   // Outputs
   ea_o, rs_add_o, rt_add_o, rd_add_o, rd_dat_o, r_we_o, dat_o, skip_o, 
   // Inputs
   rst_i, we_i, add_i, dst_i, imm_i, dat_i, rs_dat_i, rt_dat_i, siz_i, pc_i
   ) ;

   parameter kw=6;
   parameter aw = `k68_ADDR_W;
   parameter gw = `k68_GPR_W;
   parameter dw = `k68_DATA_W;
   parameter xxxx = `XXXX;
            
   input     rst_i, we_i;
   input [kw-1:0] add_i,dst_i;
   output [aw-1:0] ea_o;
   input [dw-1:0]  imm_i, dat_i;
   output [gw-1:0] rs_add_o, rt_add_o, rd_add_o;
   input [dw-1:0]  rs_dat_i, rt_dat_i;
   output [dw-1:0] rd_dat_o;
   output 	   r_we_o;
   output [dw-1:0] dat_o;
   input [1:0] 	   siz_i;
   output [1:0]    skip_o;
   input [aw-1:0]  pc_i;
   
   reg [aw-1:0]    ea_o;
   reg [gw-1:0]    rs_add_o, rt_add_o, rd_add_o;
   reg [dw-1:0]    rd_dat_o;
   reg 		   r_we_o;
   reg [1:0] 	   skip_o;
   reg [dw-1:0]    dat_o;
   
   always @ ( /*AUTOSENSE*/add_i or imm_i or rst_i or siz_i or we_i) begin
      if (rst_i) begin
	 /*AUTORESET*/
	 // Beginning of autoreset for uninitialized flops
	 r_we_o = 0;
	 rd_add_o = 0;
	 rs_add_o = 0;
	 rt_add_o = 0;
	 skip_o = 0;
	 // End of automatics
      end else begin // if (rst_i)

	 /*AUTORESET*/
	 // Beginning of autoreset for uninitialized flops
	 r_we_o = 0;
	 rd_add_o = 0;
	 rs_add_o = 0;
	 rt_add_o = 0;
	 skip_o = 0;
	 // End of automatics
	 
	 //ea_o = ea_o;
	 //dat_o = dat_o;
	 r_we_o = 1'b0;

	      case (add_i[5:3])
		3'h0,3'h1: begin // %d#, %a#
		   rt_add_o = add_i[3:0];
		   rd_add_o = add_i[3:0];
		   r_we_o = we_i;
		end
		3'h2: begin // %a#@
		   rt_add_o = {1'b1, add_i[2:0]};
		end
		3'h3: begin // %a#@+
		   rt_add_o = {1'b1, add_i[2:0]};
		   rd_add_o = {1'b1, add_i[2:0]};
		   r_we_o = ~we_i;
		end // case: 3'h3
		3'h4: begin // -%a#@
		   rt_add_o = {1'b1, add_i[2:0]};
		   rd_add_o = {1'b1, add_i[2:0]};
		   r_we_o = we_i;
		end // case: 3'h4
		3'h5: begin // %a#(+d16)
		   rt_add_o = {1'b1, add_i[2:0]};
		   skip_o = 2'd1;
		end
		3'h6: begin // %a#(+d8*scale)
		   rt_add_o = {1'b1, add_i[2:0]};
		   rs_add_o = {imm_i[31:28]};
		   skip_o = 2'd1;
		end
		default:
		  case (add_i[2:0])
		    3'h0: begin // (xxx:w)
		       skip_o = 2'd1;
		    end
		    3'h1: begin // (xxx:l)
		       skip_o = 2'd2;
		    end
		    3'h2: begin // %pc(+d16)
		       skip_o = 2'd1;
		    end
		    3'h3: begin // %pc(+d8*scale)
		       rs_add_o = {imm_i[31:28]};
		       skip_o = 2'd1;
		    end
		    3'h4: begin // ####
		       case (siz_i)
			 2'b10,2'b11: begin
			    skip_o = 2'b10;
			 end
			 
			 default: begin
			    skip_o = 2'b01;
			 end
			 
		       endcase // case(siz_i)
		    end // case: 3'h4
		    3'h5: begin
		       skip_o = 2'd0;
		    end
		    3'h7: begin
		       skip_o = 2'd0;
		    end
		    default: begin
		       skip_o = xxxx;
		    end
		    
		  endcase // case(add_i[2:0])
	      endcase // case(add_i[5:3])
	 
      end // else: !if(rst_i)
   end // always @ (...
     
   always @ ( /*AUTOSENSE*/add_i or dat_i or imm_i or pc_i or rs_dat_i or rst_i or rt_dat_i or siz_i) begin
      if (rst_i) begin
	 /*AUTORESET*/
	 // Beginning of autoreset for uninitialized flops
	 dat_o = 0;
	 ea_o = 0;
	 rd_dat_o = 0;
	 // End of automatics
      end else begin // if (rst_i)
	 /*AUTORESET*/
	 // Beginning of autoreset for uninitialized flops
	 dat_o = 0;
	 ea_o = 0;
	 rd_dat_o = 0;
	 // End of automatics
	      case (add_i[5:3])
		3'h0,3'h1: begin // %d#, %a#
		   dat_o = rt_dat_i;
		   rd_dat_o = dat_i;
		end
		3'h2: begin // %a#@
		   ea_o = rt_dat_i;
		   dat_o = dat_i;
		end
		3'h3: begin // %a#@+
		   ea_o = rt_dat_i;
		   dat_o = dat_i;
		   rd_dat_o = rt_dat_i + 3'd4;
		end // case: 3'h3
		3'h4: begin // -%a#@
		   ea_o = rt_dat_i - 3'd4;
		   rd_dat_o = rt_dat_i - 3'd4;
		   dat_o = dat_i;
		end // case: 3'h4
		3'h5: begin // %a#(+d16)
		   ea_o = rt_dat_i + {{16{imm_i[31]}},imm_i[31:16]};
		   dat_o = dat_i;
		end
		3'h6: begin // %a#(+d8*scale)
		   ea_o = rt_dat_i + {{24{imm_i[31]}},imm_i[23:16]} + (rs_dat_i << imm_i[26:25]);
		   dat_o = dat_i;
		end
		default:
		  case (add_i[2:0])
		    3'h0: begin // (xxx:w)
		       ea_o = {{16{imm_i[31]}},imm_i[31:16]};
		       dat_o = dat_i;
		    end
		    3'h1: begin // (xxx:l)
		       ea_o = imm_i;
		       dat_o = dat_i;
		    end
		    3'h2: begin // %pc(+d16)
		       ea_o = pc_i + {{16{imm_i[31]}},imm_i[31:16]};
		       dat_o = dat_i;
		    end
		    3'h3: begin // %pc(+d8*scale)
		       ea_o = pc_i + {{24{imm_i[31]}},imm_i[23:16]} + (rs_dat_i << imm_i[26:25]);
		       dat_o = dat_i;
		    end
		    3'h4: begin // ####
		       case (siz_i)
			 2'b10,2'b11: begin
			    dat_o = imm_i;
			 end
			 
			 default: begin
			    dat_o = {16'd0,imm_i[31:16]};
			 end
			 
		       endcase // case(siz_i)
		    end // case: 3'h4
		    3'h5: begin
		       dat_o = pc_i;
		       ea_o = xxxx;
		    end
		    3'h7: begin
		       dat_o = 32'd0;
		       ea_o = xxxx;
		    end
		    default: begin
		       ea_o = xxxx;
		       dat_o = xxxx;
		    end
		  endcase // case(add_i[2:0])
	      endcase // case(add_i[5:3])
      end // else: !if(rst_i)
   end // always @ (...
     
endmodule // k68_calc
