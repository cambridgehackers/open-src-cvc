//Author	David Wharton, DA Solutions Limited
//Date		2 June, 1994
//Version	1.0
//File		fp_unit.v
//		Converted from a functionally equivalent VHDL model




module fp_unit	(result_bus,
		fp_opcode,
		accumulator,
		ms_half, ls_half, clk,
		fp_unit_busy);

////////////////////////////////////////////////////////////////////
// Behavioural implementation of floating point unit
////////////////////////////////////////////////////////////////////

// Floating point format is sign and magnitude with 
// twos complement exponent
// Bit (0) is sign of number
// Bit (1 to 7) is hex exponent in two's complement format
// Bit (8 to 63) is mantissa value

input	[0:31]	result_bus;
input	[0:7]	fp_opcode;
output	[0:63]	accumulator;
input		ms_half, ls_half, clk;
output		fp_unit_busy;

reg	[0:63]	accumulator;
reg		fp_unit_busy;

reg	[0:2]	fp_state;

reg	[0:63]	op, zero;
reg		carry, ov;
reg	[0:7]	int_opcode;
reg	[0:7]	step_count, mult_count;
reg	[1:7]	exp_work;
reg	[0:63]	wop, wacc, work_reg;

reg	[8:63]	oper1, oper2;
wire	[8:63]	product;
reg		do_mult;

mult_56	component1 (oper1, oper2, product, do_mult);

////////////////////////////////////////////////////////////////////
//Floating Point Unit - Instruction decode
////////////////////////////////////////////////////////////////////

// Initialisation routines

initial
begin
	#0	accumulator = 0;
		fp_unit_busy = 0;
		step_count = 0; mult_count = 0;
		fp_state = 1;
end

`include	"tasks"	//include fp procedures

always
begin

	@ (posedge clk)
	case (fp_state)
	3'b001:
	begin
	do_mult = 0;
	if (ms_half == 1)
		begin
		op[0:31] = result_bus;
		int_opcode = fp_opcode;
		fp_state = 3'b010;
		end
	else
		fp_state = 3'b001;
	end
	3'b010:
	if (ls_half == 1)
		begin
		op[32:63] = result_bus;
		case (int_opcode)

		8'h18, 8'h19:		// FP load
		begin
		accumulator = op;
		fp_state = 3'b001;
		end

		8'h28, 8'h29:		// FP add
		begin
		fp_add(accumulator, op, 0, ov, step_count);
		fp_unit_busy = 1;
		fp_state = 3'b011;
		end

		8'h38, 8'h39:		// FP subtract
		begin
		fp_add(accumulator, op, 1, ov, step_count);
		fp_unit_busy = 1;
		fp_state = 3'b011;
		end

		8'h48, 8'h49:		//FP multiply
		begin
		fp_unit_busy = 1;
		step_count = step_count + 2;

		// Floating Point multiply

			normalise (accumulator, wacc, step_count);
			normalise (op, wop, step_count);
			add2 (wacc[1:7], wop[1:7], 0, 0, exp_work, carry);
			if (carry == 1)
				begin
				ov = 1;
				zero = 0;
				accumulator = 0;
				fp_state = 3'b011;
				end
			else
				begin
				wacc[0] = accumulator[0] != op[0];	
							//sign of result
				wacc[1:7] = exp_work;
				oper1 = wacc[8:63];
				oper2 = wop [8:63];
				do_mult = 1;
				mult_count = 4;
				fp_state = 3'b100;
				end 
		end

		default			// Illegal condition
		$display ("Illegal op code in fp unit");
		endcase
		end

	else
		fp_state = 3'b010;

// Each instruction takes a different time.
// The step count is counted up as the instruction is progressed,
// then counted down on 'clk', setting the unit not busy when zero

	3'b011:				// Count number of steps
	if (step_count == 0)
		begin
		fp_unit_busy = 0;
		fp_state = 3'b001;
		end
	else
		begin
		step_count = step_count - 1;
		fp_state = 3'b011;
		end

	3'b100:				// FP multiply
	if (mult_count === 0)
		begin
		wacc[8:63] = product;
		normalise (wacc, work_reg,step_count);
		accumulator = work_reg;
		fp_state = 3'b011;
		end
	else
		begin
		mult_count = mult_count - 1;
		fp_state = 3'b100;
		end

	default;
	endcase

end

endmodule


// Author	David Wharton, DA Solutions
// Date		27th, June, 1994
// Issue	1.0
// File		mult_56.v
// Origin	Converted from VHDL file of identical functionality

///////////////////////////////////////////////////////////////////
// Behavioral model of a 56 x 56 multiplier matrix
///////////////////////////////////////////////////////////////////

module	mult_56 (oper1, oper2, product, do_mult);

parameter	left = 8;
parameter	right = 63;

input	[left:right]	oper1, oper2;
output	[left:right]	product;
input		do_mult;

reg	[left:right]	product;
reg	[left:right]	part_sum, part_carry, gop;
reg		ovflow;

`include "tasks"

always
begin

	@ (posedge do_mult)
	begin
	part_sum = 0;
	part_carry = 0;
	
	begin : multloop1
	integer j;
	for (j = right; j > (left - 1); j = j - 1)
		begin
		begin : multloop2
		integer i;
		for (i = right; i > (left); i = i - 1)
			begin
			gop[i] = oper2[i] && oper1[j];
			part_sum[i] = gop[i] != part_sum[i-1] != part_carry[i];
			part_carry[i] = ((gop[i] || part_sum[i-1]) && part_carry[i])
				|| (gop[i] && part_sum[i-1]);
			end
		end
		part_sum[left] = oper2[left] && oper1[j];
		part_carry[left] = 0;
		end
	end

// Now add partial results

	begin : multloop3
	integer i;
	for ( i = left; i < (right); i = i + 1)
		part_carry[i] = part_carry[i+1];
	end
	part_carry[63] = 0;
	add2 (part_sum, part_carry, 0, 0, gop, ovflow);
	product = gop;
	end 
end
endmodule


//Author	David Wharton, DA Solutions Limited
//Date		5 June, 1994
//Version	1.0	
//File 		cpu_tb.v

////////////////////////////////////////////////////////////////////////
//  Testbench 
////////////////////////////////////////////////////////////////////////

module testbench;

reg 		reset, load;
wire		ipl = load;

cpu		c1 (reset, ipl);

initial
begin
	begin : mainloop
	integer i;
	for ( i=0; i<100; i = i+1 )
		begin
		case (i)
		0:	begin load = 0; reset = 0; end
		1:	reset = 1;
		3:	reset = 0;
		4:	load = 1;
		12:	load = 0;
		default;
		endcase
		#10;
		end
	end
end

initial
begin

	begin : displayloop
	integer i;
	for ( i = 0; i < 1000; i = i + 1 )
		#1000000 $display($time,,,,"accumulator =",,testbench.c1.accumulator);
	end

end
// stop control

initial
begin
	 #8203100 $finish;
end

endmodule


//Author	David Wharton, DA Solutions Limited
//Date		27th. May, 1994
//Version	1.0	
//File 		cpu.v
//Origin	Converted from a functionally equivalent VHDL model

////////////////////////////////////////////////////////////////////////
//  Central processing unit 
///////////////////////////////////////////////////////////////////////

module	cpu (reset, ipl);

input		reset, ipl;

wire	[0:31]	data_out;
wire	[0:31]	result_bus;
wire	[0:15]	i_address;
wire	[0:15]	op_address;
wire	[0:31]	instruction;
wire	[0:15]	mem_address;
wire	[0:31]	mmux_wreg;
wire	[0:31]	wr_data;
wire	[0:63]	accumulator;
wire	[0:7]	fp_opcode;

wire		load = ipl;

reg		clk;

i_unit		i1(data_out,
		result_bus,
		fetch, jump, relative, mem_dv,
		clk, load,
		i_address,
		instruction,
		i_fetch, i_valid);

mem_mux		mm1(i_address, result_bus[16:31],
		wr_data,
		clk, i_fetch, op_read, op_write,
		mem_address,
		mem_busy, mem_dv,
		mem_read, mem_write, i_dv, op_dv, write_busy,
		mmux_wreg);

op_unit		o1(accumulator, 
		instruction, data_out,
		result_bus,
		wr_data,
		fp_opcode,
		ms_half, ls_half,
		clk, i_valid, mem_dv, reset,
		fp_unit_busy, write_busy, 
		fetch, jump, relative, idle ,op_read, op_write);

memory32	m1(mmux_wreg,
		mem_address,
		clk, mem_write, mem_read, idle,
		mem_busy, mem_dv,
		data_out);

fp_unit		f1(result_bus,
		fp_opcode,
		accumulator,
		ms_half, ls_half, clk,
		fp_unit_busy);

// CPU Clock

initial
begin
	clk = 1;
end

always
	begin
		# 25 clk = ~clk;
	end

endmodule


//Author	David Wharton DA Solutions Limited
//Date		02 June, 1994
//Version	1.0	
//File 		i_fetch.v
//		Converted from VHDL model of equivalent functionality

/////////////////////////////////////////////////////////////////////
//  Instruction fetch unit 
/////////////////////////////////////////////////////////////////////

module i_unit	(data_out,
		result_bus,
		fetchin, jumpin, relativein, mem_dvin,
		clk, load,
		i_address,
		instruction,
		i_fetch, i_valid);

// behavioural implementation of instruction fetch unit

input	[0:31]	data_out, result_bus;
input		fetchin, jumpin, relativein, mem_dvin, clk, load;
output	[0:31]	instruction;
output	[0:15]	i_address;
output		i_fetch, i_valid;

reg		is1, is2, is3;
reg	[0:15]	pc_a, pc_b, psum, pc;
reg		carry;

reg		i_valid, i_fetch, fetch, mem_dv, jump, relative;
reg	[0:15]	i_address;
reg	[0:31]	instruction;


initial
begin
	#0	is1 = 1; is2 = 0; is3 = 0;
		pc_a = 0; pc_b = 0; pc = 0; carry = 0; psum = 0;

end

always
begin
	@ (mem_dvin or fetchin or jumpin or relativein)
	#1 mem_dv = mem_dvin;
	fetch = fetchin;
	jump = jumpin;
	relative = relativein;
end

always
begin					// PC adder and store address
	@ (posedge clk)
	begin
	case ({is1, is2, is3})
	3'b100 :
		begin
		i_valid = 0;
		begin
		if (jump == 1)
			begin
			if (relative == 1)
				pc_a = pc;
			else
				begin : pcainit
				integer i;
				for (i = 0; i < 16; i = i + 1)
				pc_a[i] = 0; 
				end
			pc_b = result_bus[16:31];
			is1 = 0; is2 = 1; is3 = 0;
			end
		else if (fetch == 1)
			begin
			pc_a = pc;
			begin : pcbinit
			integer i;
			for (i = 0; i < 15; i= i + 1)
			pc_b[i] = 0;
			end
			pc_b[15] = 1;
			is1 = 0; is2 = 1; is3 = 0;
			end
		else if (load == 1)
			begin
			begin : pcabinit
			integer i;
			for (i = 0; i < 16; i = i + 1)
			begin
			pc_a[i] = 0;
			pc_b[i] = 0;
			end
			end
			is1 = 0; is2 = 1; is3 = 0;
			end
		else
			begin
			is1 = 1; is2 = 0; is3 = 0;
			end
		end
		carry = 0;
		begin : addsum
		integer i;
		for (i = 15; i > -1; i = i - 1)
		begin
		psum[i] = (pc_a[i] != pc_b[i]) != carry;
		carry = (pc_a[i] && pc_b[i]) || (carry && (pc_a[i]
				|| pc_b[i]));
		end
		end
		pc = psum;
		end
	3'b010:
		begin
		i_address = pc;
		i_fetch = 1;
		is1 = 0; is2 = 0; is3 = 1;
		end
	3'b001:
		begin
		i_fetch = 0;
		if (mem_dv == 1)
			begin
			i_valid = 1;
			instruction = data_out;
			is1 = 1; is2 = 0; is3 = 0;
			end
		else
			begin
			is1 = 0; is2 = 0; is3 = 1;
			end
		end
	endcase
	end
end
endmodule


//Author	David Wharton, DA Solutions Limited
//Date		2 June, 1994
//Version	1.0	
//File 		mem_mux.v
//		Converted from VHDL description of equivalent function

///////////////////////////////////////////////////////////////////
// Memory address multiplexor
///////////////////////////////////////////////////////////////////
 
module mem_mux	(i_address, op_address,
		wr_data,
		clk, i_fetch, op_read, op_write,
		mem_address,
		mem_busy, mem_dv,
		mem_read, mem_write, i_dv, op_dv, write_busy,
		mmux_wreg);

// behavioural implementation of memory multiplexor
// mem mux operates on the opposite phase clock

input	[0:15]	i_address, op_address;
input	[0:31]	wr_data;
input		clk, i_fetch, op_read, op_write;
output	[0:15]	mem_address;
input		mem_busy, mem_dv;
output		mem_read, mem_write, i_dv, op_dv, write_busy;
output	[0:31]	mmux_wreg;

reg		i_req, or_req, ow_req;
reg	[0:15]	mmux_iadd, mmux_oradd, mmux_owadd;
reg		mxs1, mxs2, mxs3, mxs4;

reg	[0:31]	mmux_wreg;
reg		write_busy, op_dv, i_dv, mem_read, mem_write;
reg	[0:15]	mem_address;

initial
begin

	#0 i_req = 0; or_req = 0; ow_req = 0;
	mxs1 = 1; mxs2 = 0; mxs3 = 0; mxs4 = 0; 
end

always
begin
	@ (negedge clk)

// Clock request information into mem mux registers
	begin
	if (i_req == 0)
		mmux_iadd = i_address;
	if (or_req == 0)
		mmux_oradd = op_address;
	if (ow_req == 0)
		begin
		mmux_owadd = op_address;
		mmux_wreg = wr_data;
		end

// Record which requests are in the queue

	if (i_fetch == 1)
		i_req = 1;
	if (op_read == 1)
		or_req = 1;
	if (op_write == 1)
		begin
		ow_req = 1;
		write_busy = 1;
		end

// State machine

	case ({mxs1, mxs2, mxs3, mxs4})
	4'b1000 :
	begin
		op_dv = 0;
		i_dv = 0;
		if (ow_req == 1)
			begin
			mem_address = mmux_owadd;
			mem_write = 1;
			if (mem_busy == 0)
				begin 
				mxs1 = 0; mxs2 = 1; mxs3 = 0; mxs4 = 0;
				end
			else
				begin
				mxs1 = 1; mxs2 = 0; mxs3 = 0; mxs4 = 0;
				write_busy = 0;
				end
			end
		else if (or_req == 1)
			begin
			mem_address = mmux_oradd;
			mem_read = 1;
			if (mem_busy == 0)
				begin
				mxs1 = 0; mxs2 = 0; mxs3 = 1; mxs4 = 0;
				end
			else
				begin
				mxs1 = 1; mxs2 = 0; mxs3 = 0; mxs4 = 0;
				end
			end
		else if (i_req == 1)
			begin
			mem_address = mmux_iadd;
			mem_read = 1;
			if (mem_busy == 0)
				begin
				mxs1 = 0; mxs2 = 0; mxs3 = 0; mxs4 = 1;
				end
			else
				begin
				mxs1 = 1; mxs2 = 0; mxs3 = 0; mxs4 = 0;
				end
			end
	end
	4'b0100 :
	begin
		if (mem_busy == 1)
			begin
			mxs1 = 0; mxs2 = 1; mxs3 = 0; mxs4 = 0;
			end
		else
			begin
			ow_req = 0;
			mem_write = 0;
			write_busy = 0;
			mxs1 = 1; mxs2 = 0; mxs3 = 0; mxs4 = 0;
			end
	end
	4'b0010 :
	begin
		or_req = 0;
		mem_read = 0;
		if (mem_dv == 0)
			begin
			mxs1 = 0; mxs2 = 0; mxs3 = 1; mxs4 = 0;
			end
		else
			begin
			op_dv = 1;
			mxs1 = 1; mxs2 = 0; mxs3 = 0; mxs4 = 0;
			end
	end
	4'b0001 :
	begin
		i_req = 0;
		mem_read = 0;
		if (mem_dv == 0)
			begin
			mxs1 = 0; mxs2 = 0; mxs3 = 0; mxs4 = 1;
			end
		else
			begin
			mxs1 = 1; mxs2 = 0; mxs3 = 0; mxs4 = 0;
			end
	end
	endcase
	end
end
endmodule

//Author	David Wharton, DA Solutions Limited
//Date		3 June, 1994
//Version	1.0	
//File 		memory32.v
//		Converted from equivalent functionality in VHDL

////////////////////////////////////////////////////////////////////////
// 32-bit wide memory, 256 deep
////////////////////////////////////////////////////////////////////////

module memory32 (wr_data,
		mem_address,
		clk, mem_write, mem_read, idle,
		mem_busy, mem_dv,
		data_out);

// behavioural implementation OF the 32-bit wide memory
// using a state machine

input	[0:31]	wr_data;
input	[0:15]	mem_address;
input		clk, mem_write, mem_read, idle;
output		mem_busy, mem_dv;
output	[0:31]	data_out;

reg	[0:31]	main_mem[0:1023];
reg	[0:15]	mem_add_reg;
reg	[0:31]	mem_write_reg;
reg	[0:31]	load_line;
reg		mem_init, dump_done;	//VHDL booleans
reg	[0:2]	mem_state;

reg		mem_busy, mem_dv;
reg	[0:31]	data_out;

initial
begin
	#0	mem_init = 0; dump_done = 0;
		mem_state = 3'b001;
end

initial
begin

// If this is the first time through load the memory from a file.

	#10 if ( mem_init == 0)
		begin
		$readmemb ("prog", main_mem);
		mem_init = 1;
		dump_done = 0;
		end

end

always
begin

	@ (posedge clk)
	begin
	case ( mem_state )
	3'b001:
	begin
		mem_busy = 0;
		mem_dv = 0;
		if (mem_read == 1)
			begin
			mem_state = 3'b010;
			mem_add_reg = mem_address;
			end
		if (mem_write == 1)
			begin
			mem_state = 3'b101;
			mem_add_reg = mem_address;
			mem_write_reg = wr_data;
			end
	end
	3'b010:
	begin
		mem_busy = 1;
		mem_state = 3'b011;
	end
	3'b011:
	begin
		mem_state = 3'b100;
	end
	3'b100:
	begin
		data_out = main_mem[mem_add_reg];
		mem_dv = 1;
		mem_state = 3'b001;
	end
	3'b101:
	begin
		mem_busy = 1;
		mem_state = 3'b110;
	end
	3'b110:
	begin
		main_mem[mem_add_reg] = mem_write_reg;
		mem_state = 3'b001;
	end
	endcase
	if (idle == 1)
		if (dump_done == 0)
			begin
// uncommented SJM
//			$writememb (main_mem, "result");
			dump_done = 1;
			end
	end
end


endmodule

//Author	David Wharton, DA Solutions Limited
//Date		2 June, 1994
//Version	1.0	
//File 		op_unit.v
//		Converted from VHDL model of equivalent functionality

////////////////////////////////////////////////////////////////
// Operand unit (true behavioural)
////////////////////////////////////////////////////////////////

module op_unit	(accumulator, instruction, data_out,
		result_bus,
		wr_data,
		fp_opcode,
		ms_half, ls_half,
		clk, i_valid, mem_dvin, reset, fp_unit_busyin, write_busy,
		fetch, jump, relative, idle ,op_read, op_write);

// behavioral implementation of operand unit

input	[0:31]	instruction, data_out;
input	[0:63]	accumulator;
output	[0:31]	result_bus;
output	[0:31]	wr_data;
output	[0:7]	fp_opcode;
output		ms_half, ls_half;
input		clk, i_valid, mem_dvin, reset, fp_unit_busyin, write_busy;
output		fetch, jump, relative, idle, op_read, op_write;

wire	[0:7]	opcode = instruction [0:7];
wire	[0:3]	R1 = instruction[8:11];
wire	[0:3]	R2 = instruction[12:15];
wire	[0:15]	D2 = instruction[16:31];
wire	[0:31]	ms_half_acc = accumulator[0:31];
wire	[0:31]	ls_half_acc = accumulator[32:63];

reg	[0:31]	x_reg[0:15];
reg	[0:31]	a, b, result;
reg	[0:3]	ccode;
reg		carryout, overflow, fp_unit_busy;
reg	[0:4]	op_step;

reg	[8*16:1]	message;
reg	[8*1:1]		newbit;

reg		op_write, jump, idle, fetch, relative, ms_half, ls_half;
reg		op_read, mem_dv;
reg	[0:7]	fp_opcode;
reg	[0:31]	wr_data;
reg	[0:31]	result_bus;

reg	[0:7]	i;


integer		hex_op;	

initial
begin
	#0	op_step = 5'b00001;
end

always
begin
	@ (mem_dvin or fp_unit_busyin)
	#1 mem_dv = mem_dvin;
	fp_unit_busy = fp_unit_busyin;
end

////////////////////////////////////////////////////////////////
//   Task to add or subtract two 32 bit vectors, a and b,
//	and return the result as a 32 bit vector sum
////////////////////////////////////////////////////////////////

task		add;

input	[0:31]	a, b;
input		subtract;
output	[0:31]	result;
output		cout, ov;

reg	[0:31]	sum;
reg		carry, carry0;

begin

	carry = subtract;
	begin : addsum
	integer i;
	for ( i = 31; i > 0; i = i - 1)
	begin
	sum[i] = (a[i] != carry) != (b[i] != subtract);
	carry = ((a[i] || carry) && (b[i] != subtract))
			|| (carry && a[i]);
	end
	end

	sum[0] = (a[0] != carry) != (b[0] != subtract);
	carry0 = ((a[0] || carry) && (b[0] != subtract))
			|| (carry && a[0]);
	ov = carry0 != carry;
	cout = carry0;

	result = sum;
end
endtask

////////////////////////////////////////////////////////////////
//   Function to sign extend a 16 bit vector to 32 bits by
//	replicating bit 0 16 times.
////////////////////////////////////////////////////////////////

function [0:31]	sign_extend;

input	[0:15]	D2;
reg	[0:31]	result;

begin
	begin : sextend
	integer i;
	for (i = 0; i < 16; i = i+1)
	begin
	result[i] = D2[0];
	result[i+16] = D2[i];
	end
	end
	sign_extend = result;
end
endfunction

always
begin
	@ (posedge clk)
	begin
	case (op_step)
	5'b00001:	// idle or starting next instruction
	begin
		op_write = 0; jump = 0; relative = 0;
		ls_half = 0; ms_half = 0;
		fetch = 0;
			// reset conditions from previous instructions
		if (i_valid == 1)
			begin
			hex_op = opcode;
			fp_opcode = opcode;
			case (hex_op)
			8'h10:				// RR Load
			begin
				a = 0;
				b = x_reg[R2];	//conversions
				add (a, b, 0,result, carryout, overflow);
				op_step = 5'b00010;
			end
			8'h20:				// RR Add
			begin
				a = x_reg[R1];
				b = x_reg[R2];
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b00010;
			end
			8'h30:				// RR Sub
			begin
				a = x_reg[R1];
				b = x_reg[R2];
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b00010;
			end
			8'h40:				// RR Mult
			begin
			end
			8'h11, 8'h21, 8'h31, 8'h41:	// RX Instruction
			begin
				a = x_reg[R2];
				b = sign_extend(D2);
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b00011;
			end
			8'h51:				// RX store
			begin
				a = x_reg[R1];
				b = 0;
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b00101;
			end
			8'h12:				//RLIT Load
			begin
				b = sign_extend(D2);
				result = b;
				op_step = 5'b00010;
			end
			8'h22:				// RLIT Add
			begin
				a = x_reg[R1];
				b = sign_extend(D2);
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b00010;
			end
			8'h32:				// RLIT Sub
			begin
				a = x_reg[R1];
				b = sign_extend(D2);
				add (a, b, 1, result, carryout, overflow);
				op_step = 5'b00010;
			end
			8'h42:				// RLITT Mult
			begin
			end
			8'h18, 8'h28, 8'h38, 8'h48, 8'h68:
					// RRD Laod, Add, Sub, Mult, Div
			begin
				a = 0;
				b = sign_extend(D2);
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b01000;
			end
			8'h58:				// RRD Store
			begin
				op_step = 5'b01010;
			end
			8'h19, 8'h29, 8'h39, 8'h49, 8'h69:
					// RXD Load, Add, Sub, Mult, Div
			begin
				a = x_reg[R2];
				b = sign_extend(D2);
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b01101;
			end
			8'h59:				// RXD Store
			begin
				op_step = 5'b10100;
			end 
			8'h80:				// Jump
			begin
				b = sign_extend(D2);
				result = b;
				op_step = 5'b00110;
			end
			8'h90:				// JCC
			begin
				b = sign_extend(D2);
				result = b;
				op_step = 5'b00111;
			end
			8'h81:				// J (Abs)
			begin
				result = x_reg[R2];
				op_step = 5'b00110;
			end
			8'h91:				// JCC (Abs)
			begin
				result = x_reg[R2];
				op_step = 5'b00111;
			end
			8'hF0:				// IDLE
			begin
				$display ("IDLE operand", D2);
			end
			default
			begin
				$display ("Illegal op code");
			end
			
			endcase
			end



	end
	5'b00010:		// Write result of instruction back to R1
	begin
		x_reg[R1] = result;
		if ( overflow == 1 )	// Set condition code
			ccode = 4'b0001;
		else if (result == 0)
			ccode = 4'b1000;
		else if (result[0] == 1)
			ccode = 4'b0010;
		else
			ccode = 4'b0100;
		fetch = 1;
		op_step = 5'b00001;
	end
	5'b00011:			// Start read from main store
	begin
		op_read = 1;
		op_step = 5'b00100;
	end
	5'b00100:			// Waiting for data from main store
	begin
		op_read = 0;
		if (mem_dv == 1)
			begin
			b = data_out;
			case (hex_op)
			8'h11:			// RX Load
			begin
				a = 0;
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b00010;
			end
			8'h21:			// R Add
			begin
				a = x_reg[R1];
				add (a, b, 0, result, carryout, overflow);
				op_step = 5'b00010;
			end
			8'h31:			// RX Sub
			begin
				a = x_reg[R1];
				add (a, b, 1, result, carryout, overflow);
				op_step = 5'b00010;
			end
			8'h40:			// RR Mult
			begin
			end
			default;
			endcase
			end
		else
			op_step = 5'b00100;	// possibly redundant
	end
	5'b00101:				// RX Store - Write
	begin
		wr_data = result;
		a = x_reg[R2];
		b = sign_extend(D2);
		add (a, b, 0, result, carryout, overflow);
		op_write = 1;
		fetch = 1;
		op_step = 5'b00001;
	end
	5'b00110:			// J
	begin
		jump = 1;
		if (opcode[7] == 1)	// Distinguish bwteen J and J (Abs)
			relative = 1;
		op_step = 5'b00001;
	end
	5'b00111:				// JCC
	begin
		if ( ((ccode[0] && R1[0]) || (ccode[1] && R1[1])
			|| (ccode[2] && R1[2]) || (ccode[3] && R1[3])) == 1 )
			begin
			jump = 1;
			if ( opcode[7] == 0 )	// Distinguish beetween J and J (Abs)
				relative = 1;
			end
		else
			fetch = 1;
		op_step = 5'b00001;
	end
	5'b01000:			// RRD data from R1, R1+1 to fp unit
	begin
		ms_half = 1;
		if ( fp_unit_busy == 1)
			op_step = 5'b01000;
		else
			begin
			a = 0;
			b = x_reg[{R2[0:2],1'b1}];
			add (a, b, 0, result, carryout, overflow);
			op_step = 5'b01001;
			end
	end
	5'b01001:
	begin
		ls_half = 1;
		fetch = 1;
		op_step = 5'b00001;
	end
	5'b01010:			// RRD Store
	begin
		if ( fp_unit_busy == 1 )
			op_step = 5'b01010;
		else
			begin
			a = accumulator[0:31];
			b = 0;
			add (a, b, 0, result, carryout, overflow);
			op_step = 5'b01011;
			end
	end
	5'b01011:
	begin
		x_reg[R1] = result;
		a = accumulator[32:63];
		b = 0;
		add (a, b, 0, result, carryout, overflow);
		op_step = 5'b01100;
	end
	5'b01100:
	begin
		x_reg[{R1[0:2],1'b1}] = result;
		fetch = 1;
		op_step = 5'b00001;
	end
	5'b01101:		// Start double read from main store
	begin
		op_read = 1;
		op_step = 5'b01110;
	end
	5'b01110:		// Waiting for data from main store
	begin
		op_read = 0;
		if ( mem_dv == 1)
			begin
			a = 0;
			b = data_out;
			add (a, b, 0, result, carryout, overflow);
			ms_half = 1;
			op_step = 5'b01111;
			end
		else
			op_step = 5'b01110;
	end
	5'b01111:
	begin
		if ( fp_unit_busy == 1)
			op_step = 5'b01111;
		else
			begin
			a = x_reg[R2];
			b = sign_extend({D2[0:14],1'b1});
			add (a, b, 0, result, overflow, carryout);
			ms_half = 0;
			op_step = 5'b10000;
			end
	end
	5'b10000:		// Second half of read
	begin
		op_read = 1;
		op_step = 5'b10001;
	end
	5'b10001:		// Waiting for data from main store
	begin
		op_read = 0;
		if ( mem_dv == 1 )
			begin
			a = 0;
			b = data_out;
			add (a, b, 0, result, carryout, overflow);
			ls_half = 1;
			fetch = 1;
			op_step = 5'b0001;
			end
		else
			op_step = 5'b10001;
	end
	5'b10100:		// RXD Store
	begin
		if ( fp_unit_busy == 1)
			op_step = 5'b10100;
		else
			begin
			a = accumulator[0:31];
			b = 0;
			add (a, b, 0, result, carryout, overflow);
			op_step = 5'b10101;
			end
	end
	5'b10101:		// RRD Store - Write ms half
	begin
		wr_data = result;
		a = x_reg[R2];
		b = sign_extend(D2);
		add (a, b, 0, result, carryout, overflow);
		op_write = 1;
		op_step = 5'b10110;
	end
	5'b10110:
	begin
		op_write = 0;
		a = accumulator[32:63];
		b = 0;
		add (a, b, 0, result, carryout, overflow);
		if ( write_busy == 1)
			op_step = 5'b10110;
		else
			op_step = 5'b10111;
	end
	5'b10111:		// Write ls half to store
	begin
		wr_data = result;
		a = x_reg[R2];
		b = sign_extend({D2[0:14],1'b1});
		add (a, b, 0, result, carryout, overflow);
		op_write = 1;
		fetch = 1;
		op_step = 5'b00001;
	end
	default;
	endcase
	result_bus = result;
	end
end
endmodule
