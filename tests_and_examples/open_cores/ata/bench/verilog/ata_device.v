/////////////////////////////////////////////////////////////////////
////                                                             ////
////  ATA (IDE) Device Model                                     ////
////  This Model Supports PIO cycles only !                      ////
////                                                             ////
////                                                             ////
////  Author: Rudolf Usselmann                                   ////
////          rudi@asics.ws                                      ////
////                                                             ////
////                                                             ////
////  Downloaded from: http://www.opencores.org/cores/ata/       ////
////                                                             ////
/////////////////////////////////////////////////////////////////////
////                                                             ////
//// Copyright (C) 2001 Rudolf Usselmann                         ////
////                    rudi@asics.ws                            ////
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

//  CVS Log
//
//  $Id: ata_device.v,v 1.2 2002-02-25 06:07:21 rherveille Exp $
//
//  $Date: 2002-02-25 06:07:21 $
//  $Revision: 1.2 $
//  $Author: rherveille $
//  $Locker:  $
//  $State: Exp $
//
// Change History:
//               $Log: not supported by cvs2svn $
//               Revision 1.1  2001/08/16 10:01:05  rudi
//
//               - Added Test Bench
//               - Added Synthesis scripts for Design Compiler
//               - Fixed minor bug in atahost_top
//
//
//
//
//                        

`timescale 1ns / 10ps

module ata_device(	ata_rst_, ata_data, ata_da, ata_cs0, ata_cs1,
			ata_dior_, ata_diow_, ata_iordy, ata_intrq );
input		ata_rst_;
inout	[15:0]	ata_data;
input	[2:0]	ata_da;
input		ata_cs0, ata_cs1;
input		ata_dior_, ata_diow_;
output		ata_iordy;
output		ata_intrq;

integer		mode;
integer		n;
reg		ata_iordy;
reg		iordy_enable;
integer		iordy_delay;

reg	[15:0]	mem[32:0];
reg	[15:0]	dout;
reg		dout_en;
wire		ata_rst_m0, ata_rst_m1, ata_rst_m2, ata_rst_m3, ata_rst_m4;
wire	[4:0]	addr;
wire		ata_dior, ata_diow;

initial
   begin
	dout_en = 0;
	mode = 0;
	iordy_enable = 0;
	iordy_delay  = 0;
	ata_iordy    = 1;
   end

assign ata_dior = !ata_dior_;
assign ata_diow = !ata_diow_;

assign ata_intrq = 0;

assign ata_data = dout_en ? dout : 16'hzzzz;

assign addr = {~ata_cs1, ~ata_cs0, ata_da};

always @(posedge ata_rst_)
	dout_en = 0;

always @(posedge ata_dior)
   begin
	dout = mem[ addr ];
	dout_en = 1;
   end

always @(posedge ata_dior)
   begin
	dout_en = 0;
   end

always @(posedge ata_diow)
   begin
	mem[ addr ] = ata_data;
   end

always @(posedge ata_dior or posedge ata_diow)
   begin
	ata_iordy = 1'b0;
	#(iordy_delay);
	ata_iordy = 1'b1;
   end

task init_mem;

begin

for(n=0;n<32;n=n+1)
	mem[n] = n;
end
endtask

assign ata_rst_m0 = ata_rst_ & (mode==0);
assign ata_rst_m1 = ata_rst_ & (mode==1);
assign ata_rst_m2 = ata_rst_ & (mode==2);
assign ata_rst_m3 = ata_rst_ & (mode==3);
assign ata_rst_m4 = ata_rst_ & (mode==4);



endmodule


