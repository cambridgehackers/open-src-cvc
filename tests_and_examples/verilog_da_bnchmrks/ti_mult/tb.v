// DA Solutions Ltd., Testbench to drive Texas Instruments provided
// Multiplier circuit
// Creeated 1-Sep-94, D. J. Wharton
// Circuit also available in VHDL
// Library used Texas Instruments TGC1000_2.1 5v CMOS

`timescale 1ns / 10ps
module testbench;

reg	[0:98]	patternreg[0:201];
reg	[0:98]	patternregbuf;
reg	[30:0]	errorbit;

reg A15port;
reg A14port;
reg A13port;
reg A12port;
reg A11port;
reg A10port;
reg A9port;
reg A8port;
reg A7port;
reg A6port;
reg A5port;
reg A4port;
reg A3port;
reg A2port;
reg A1port;
reg A0port;
reg B15port;
reg B14port;
reg B13port;
reg B12port;
reg B11port;
reg B10port;
reg B9port;
reg B8port;
reg B7port;
reg B6port;
reg B5port;
reg B4port;
reg B3port;
reg B2port;
reg B1port;
reg B0port;
reg C15port;
reg C14port;
reg C13port;
reg C12port;
reg C11port;
reg C10port;
reg C9port;
reg C8port;
reg C7port;
reg C6port;
reg C5port;
reg C4port;
reg C3port;
reg C2port;
reg C1port;
reg C0port;
reg D15port;
reg D14port;
reg D13port;
reg D12port;
reg D11port;
reg D10port;
reg D9port;
reg D8port;
reg D7port;
reg D6port;
reg D5port;
reg D4port;
reg D3port;
reg D2port;
reg D1port;
reg D0port;
reg SEL3port;
reg SEL2port;
reg SEL1port;
reg SEL0port;

wire Y_30_port;
wire Y_29_port;
wire Y_28_port;
wire Y_27_port;
wire Y_26_port;
wire Y_25_port;
wire Y_24_port;
wire Y_23_port;
wire Y_22_port;
wire Y_21_port;
wire Y_20_port;
wire Y_19_port;
wire Y_18_port;
wire Y_17_port;
wire Y_16_port;
wire Y_15_port;
wire Y_14_port;
wire Y_13_port;
wire Y_12_port;
wire Y_11_port;
wire Y_10_port;
wire Y_9_port;
wire Y_8_port;
wire Y_7_port;
wire Y_6_port;
wire Y_5_port;
wire Y_4_port;
wire Y_3_port;
wire Y_2_port;
wire Y_1_port;
wire Y_0_port;

`define inputs  {A15port, A14port, A13port, A12port, A11port, A10port, A9port, A8port, A7port, A6port, A5port, A4port, A3port, A2port, A1port, A0port, B15port, B14port, B13port, B12port, B11port, B10port, B9port, B8port, B7port, B6port, B5port, B4port, B3port, B2port, B1port, B0port, C15port, C14port, C13port, C12port, C11port, C10port, C9port, C8port, C7port, C6port, C5port, C4port, C3port, C2port, C1port, C0port, D15port, D14port, D13port, D12port, D11port, D10port, D9port, D8port, D7port, D6port, D5port, D4port, D3port, D2port, D1port, D0port, SEL3port, SEL2port, SEL1port, SEL0port}


initial
begin
//	$readmemb ("/home/vecircs/ti/archive/patterns", patternreg);
	$readmemb ("patterns", patternreg);
	begin : readloop
	integer i;
	for (i=0; i < 202; i=i+1)
	begin
		patternregbuf = patternreg[i];

//		assign `inputs = patternregbuf[0:67];
		`inputs = patternregbuf[0:67];
		# 90000;
		errorbit[30] = Y_30_port != patternregbuf[68];
		errorbit[29] = Y_29_port != patternregbuf[69];  
		errorbit[28] = Y_28_port != patternregbuf[70];  
		errorbit[27] = Y_27_port != patternregbuf[71];  
		errorbit[26] = Y_26_port != patternregbuf[72];  
		errorbit[25] = Y_25_port != patternregbuf[73];  
		errorbit[24] = Y_24_port != patternregbuf[74];  
		errorbit[23] = Y_23_port != patternregbuf[75];  
		errorbit[22] = Y_22_port != patternregbuf[76];  
		errorbit[21] = Y_21_port != patternregbuf[77];  
		errorbit[20] = Y_20_port != patternregbuf[78];  
		errorbit[19] = Y_19_port != patternregbuf[79];  
		errorbit[18] = Y_18_port != patternregbuf[80];  
		errorbit[17] = Y_17_port != patternregbuf[81];  
		errorbit[16] = Y_16_port != patternregbuf[82];  
		errorbit[15] = Y_15_port != patternregbuf[83];  
		errorbit[14] = Y_14_port != patternregbuf[84];  
		errorbit[13] = Y_13_port != patternregbuf[85];  
		errorbit[12] = Y_12_port != patternregbuf[86];  
		errorbit[11] = Y_11_port != patternregbuf[87];  
		errorbit[10] = Y_10_port != patternregbuf[88];  
		errorbit[9] = Y_9_port != patternregbuf[89];
		errorbit[8] = Y_8_port != patternregbuf[90];
		errorbit[7] = Y_7_port != patternregbuf[91];
		errorbit[6] = Y_6_port != patternregbuf[92];
		errorbit[5] = Y_5_port != patternregbuf[93];
		errorbit[4] = Y_4_port != patternregbuf[94];
		errorbit[3] = Y_3_port != patternregbuf[95];
		errorbit[2] = Y_2_port != patternregbuf[96];
		errorbit[1] = Y_1_port != patternregbuf[97];
		errorbit[0] = Y_0_port != patternregbuf[98];
		if (errorbit != 0)
			begin
			$display ($time,,,,"error register",,errorbit);
			end
	end
	end
end

multx16 g1(
         .a_15_port(A15port),
         .a_14_port(A14port),
         .a_13_port(A13port),
         .a_12_port(A12port),
         .a_11_port(A11port),
         .a_10_port(A10port),
         .a_9_port(A9port),
         .a_8_port(A8port),
         .a_7_port(A7port),
         .a_6_port(A6port),
         .a_5_port(A5port),
         .a_4_port(A4port),
         .a_3_port(A3port),
         .a_2_port(A2port),
         .a_1_port(A1port),
         .a_0_port(A0port),
         .b_15_port(B15port),
         .b_14_port(B14port),
         .b_13_port(B13port),
         .b_12_port(B12port),
         .b_11_port(B11port),
         .b_10_port(B10port),
         .b_9_port(B9port),
         .b_8_port(B8port),
         .b_7_port(B7port),
         .b_6_port(B6port),
         .b_5_port(B5port),
         .b_4_port(B4port),
         .b_3_port(B3port),
         .b_2_port(B2port),
         .b_1_port(B1port),
         .b_0_port(B0port),
         .c_15_port(C15port),
         .c_14_port(C14port),
         .c_13_port(C13port),
         .c_12_port(C12port),
         .c_11_port(C11port),
         .c_10_port(C10port),
         .c_9_port(C9port),
         .c_8_port(C8port),
         .c_7_port(C7port),
         .c_6_port(C6port),
         .c_5_port(C5port),
         .c_4_port(C4port),
         .c_3_port(C3port),
         .c_2_port(C2port),
         .c_1_port(C1port),
         .c_0_port(C0port),
         .d_15_port(D15port),
         .d_14_port(D14port),
         .d_13_port(D13port),
         .d_12_port(D12port),
         .d_11_port(D11port),
         .d_10_port(D10port),
         .d_9_port(D9port),
         .d_8_port(D8port),
         .d_7_port(D7port),
         .d_6_port(D6port),
         .d_5_port(D5port),
         .d_4_port(D4port),
         .d_3_port(D3port),
         .d_2_port(D2port),
         .d_1_port(D1port),
         .d_0_port(D0port),
         .sel_3_port(SEL3port),
         .sel_2_port(SEL2port),
         .sel_1_port(SEL1port),
         .sel_0_port(SEL0port),
         .y_30_port(Y_30_port),
         .y_29_port(Y_29_port),
         .y_28_port(Y_28_port),
         .y_27_port(Y_27_port),
         .y_26_port(Y_26_port),
         .y_25_port(Y_25_port),
         .y_24_port(Y_24_port),
         .y_23_port(Y_23_port),
         .y_22_port(Y_22_port),
         .y_21_port(Y_21_port),
         .y_20_port(Y_20_port),
         .y_19_port(Y_19_port),
         .y_18_port(Y_18_port),
         .y_17_port(Y_17_port),
         .y_16_port(Y_16_port),
         .y_15_port(Y_15_port),
         .y_14_port(Y_14_port),
         .y_13_port(Y_13_port),
         .y_12_port(Y_12_port),
         .y_11_port(Y_11_port),
         .y_10_port(Y_10_port),
         .y_9_port(Y_9_port),
         .y_8_port(Y_8_port),
         .y_7_port(Y_7_port),
         .y_6_port(Y_6_port),
         .y_5_port(Y_5_port),
         .y_4_port(Y_4_port),
         .y_3_port(Y_3_port),
         .y_2_port(Y_2_port),
         .y_1_port(Y_1_port),
         .y_0_port(Y_0_port));
endmodule

// End of testbench code
