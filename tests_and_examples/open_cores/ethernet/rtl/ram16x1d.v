// $Header: /devl/xcs/repo/env/Databases/CAEInterfaces/verunilibs/s/RAM16X1D.v,v 1.7.18.1 2002/11/04 23:31:33 patrickp Exp $

/*

FUNCTION	: 16x1 Dual Port Static RAM with synchronous write capability

*/

`timescale  100 ps / 10 ps


module RAM16X1D (DPO, SPO, A0, A1, A2, A3, D, DPRA0, DPRA1, DPRA2, DPRA3, WCLK, WE);

    parameter INIT = 16'h0000;

    output DPO, SPO;

    input  A0, A1, A2, A3, D, DPRA0, DPRA1, DPRA2, DPRA3, WCLK, WE;

    reg  mem [15:0];
    reg  [4:0] count;
    wire [3:0] adr;
    wire [3:0] dpr_adr;
    wire d_in, wclk_in, we_in;

    buf b_d    (d_in, D);
    buf b_wclk (wclk_in, WCLK);
    buf b_we   (we_in, WE);

    buf b_a3 (adr[3], A3);
    buf b_a2 (adr[2], A2);
    buf b_a1 (adr[1], A1);
    buf b_a0 (adr[0], A0);

    buf b_d3 (dpr_adr[3], DPRA3);
    buf b_d2 (dpr_adr[2], DPRA2);
    buf b_d1 (dpr_adr[1], DPRA1);
    buf b_d0 (dpr_adr[0], DPRA0);

    buf b_spo (SPO, spo_int);
    buf b_dpo (DPO, dpo_int);

    buf b_spo_int (spo_int, mem[adr]);
    buf b_dpo_int (dpo_int, mem[dpr_adr]);

    initial
    begin
	for (count = 0; count < 16; count = count + 1)
	    mem[count] <= INIT[count];

    end

    always @(posedge wclk_in)
    begin
	if (we_in == 1'b1)
	    mem[adr] <= d_in;
    end

    specify
	if (WE)
	    (WCLK => SPO) = (1, 1);
	if (WE)
	    (WCLK => DPO) = (1, 1);

	(A3 => SPO) = (1, 1);
	(A2 => SPO) = (1, 1);
	(A1 => SPO) = (1, 1);
	(A0 => SPO) = (1, 1);

	(DPRA3 => DPO) = (1, 1);
	(DPRA2 => DPO) = (1, 1);
	(DPRA1 => DPO) = (1, 1);
	(DPRA0 => DPO) = (1, 1);
    endspecify

endmodule

