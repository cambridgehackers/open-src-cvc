//////////////////////////////////////////////////////
// Function and Task package for CPU with fp_unit
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// Normalise task
//////////////////////////////////////////////////////

task	normalise;

parameter	fpleft = 0;
parameter	fpright = 63;

input	[fpleft:fpright]	fp_number;
output	[fpleft:fpright]	norm_result;
inout	[0:15]	scount;

reg	[fpleft:fpright]	work_reg;
reg		carry;

begin

	if (fp_number[8:fpright] == 0)	//zero mantissa can't be normalised
		begin
		norm_result = 0;
		scount = scount + 1;
		end
	else
		begin
		work_reg = fp_number;
		begin : normloop
		while ((work_reg[1:7] != 7'b1000000) && (work_reg[8:11] == 0))
			begin
			work_reg[8:(fpright - 4)] = work_reg[12:fpright];
			work_reg[(fpright-3):fpright] = 0;
			carry = 1;	// subtract one from the exponent

			begin : workloop
			integer i;
			for (i = 7; i > 0; i = i - 1)
				begin
				work_reg[i] = work_reg[i] != carry;
				carry = carry && work_reg[i];
					// Note work_reg has changed
			end
			end
			scount = scount + 1;
			end
		end
		norm_result = work_reg;
		scount = scount + 1;
		end
end
endtask

//////////////////////////////////////////////////////
// Align task
//////////////////////////////////////////////////////

task	align;

parameter	fpleft = 0;
parameter	fpright = 63;

input	[fpleft:fpright]	fp_number;
input	[0:31]	no_places;
output	[fpleft:fpright]	align_result;

reg	[fpleft:fpright]	work_reg;

begin

	work_reg = fp_number;
	begin : forloop
	integer i;
	for ( i = 1; i < (no_places + 1); i = i + 1 )
		begin
		work_reg[12:fpright] = work_reg[8:(fpright - 4)];
		work_reg[8:11] = 0;
		end
	end
	align_result = work_reg;
end
endtask

//////////////////////////////////////////////////////
// Add task
//////////////////////////////////////////////////////

task	add2;

parameter		aleft = 8;
parameter		aright = 63;

input	[aleft:aright]	a, b;
input			cin, subtract;

output	[aleft:aright]	sum;
output			cout;

reg	[aleft:aright]	vsum;
reg			carry;

begin

	carry = cin;
	begin : forloop
	integer i;
	for ( i = aright; i > (aleft - 1); i = i - 1 )	
		begin
		vsum[i] = (a[i] != carry) != (b[i] != subtract);
		carry = ((a[i] || carry) && (b[i] != subtract))
				|| (carry && a[i]);
		end
	end
	sum = vsum;
	cout = carry;
end
endtask

//////////////////////////////////////////////////////
// Task to add 1 to standard logic vector
//////////////////////////////////////////////////////

task	vect_add_one;

parameter	left = 1;
parameter	right = 7;

input	[left:right]	a;
output			overflow;
output	[left:right]	result;

reg			cin;

begin
	cin = 1;
	begin : forloop
	integer i;
	for (i = right; i > (left - 1); i = i - 1)
		begin
		result[i] = a[i] != cin;
		cin = a[i] && cin;
		end
	end
	overflow = cin != a[left];
end
endtask
	
//////////////////////////////////////////////////////
// Floating point add
//////////////////////////////////////////////////////

task	fp_add;

parameter	right = 63;

inout	[0:right]	acc;
input	[0:right]	op;
input			subtract;
output			overflow;
inout	[0:15]		scount;

integer			difference;
reg			carry;
reg	[0:right]	work_reg, wacc, wop;

begin

	normalise (acc, wacc, scount);
	normalise (op, wop, scount);
	difference = wacc[1:7] - wop[1:7];
	
		// one of the numbers may be zero or small compared to the
		// other

	if ( wop == 0 || difference > 13 )
		acc = wacc;		// Accumulator is unchanged
					// other than to be mormalised
	else if ( wacc == 0 || difference < -13 )
		begin
		if ( subtract == 0 )
			acc = wop;
		else
			begin
			acc[0] = !wop[0];
			acc[1:right] = wop[1:right];
			end
		end
	else 
		begin
		if ( difference > 0 ) 
			begin
			align (wop, difference, work_reg);
			wop = work_reg;
			scount = scount + difference;
			end
		else if ( difference < 0 )
			begin
			align (wacc, -difference, work_reg);
			wacc = work_reg;
			scount = scount - difference;
			end
		end

		// First handle the cases where the mantissas have
		// to be added

	if (((wacc[0] == wop[0]) && (subtract == 0)) || 
		((wacc[0] != wop[0]) && (subtract == 1)))
			begin
			add2 (wacc[8:right], wop[8:right], 0, 0,
				work_reg[8:right], carry);
			wacc[8:right] = work_reg[8:right];
			if ( carry == 1 ) // overflow, shift acc right,
						// add one to exponent
				begin
				align (wacc, 1, work_reg);
				scount = scount + 1;
				wacc = work_reg;
				wacc[11] = 1;
				vect_add_one ( wacc[1:7], overflow,
					work_reg[1:7]);
				wacc[1:7] = work_reg[1:7];
				end
			end
		// Mantissas have to be extracted
	else
			begin
			add2 (wacc[8:right], wop[8:right], 1, 1,
				work_reg[8:right], carry);
			if ( carry == 1 )
				wacc[8:right] = work_reg[8:right];
			else	// convert to sign and magnitude
				begin
				wacc[8:right] = work_reg[8:right];
				add2 (0, wacc[8:right], 1, 1,work_reg[8:right],
					carry);
				wacc[0] = ~acc[0];
				wacc[1:7] = work_reg[1:7];
				wacc[8:right] = work_reg[8:right];
				end
			normalise ( wacc, work_reg, scount );
			wacc = work_reg;
			end
	scount = scount + 2; // minumum time for an instruction
	acc = wacc;
end
endtask
