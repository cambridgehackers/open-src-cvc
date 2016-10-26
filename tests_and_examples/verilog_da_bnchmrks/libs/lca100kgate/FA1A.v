module	FA1A( ci, a, b, s, co );

input	ci, a, b;
output	s, co;

xor	#1 l1(s, ci, a, b);
and	l2(x1, ci, a );
and	l3(x2, ci, b );
and	l4(x3, a, b );
or	#1 l5(co, x1, x2, x3);

endmodule
