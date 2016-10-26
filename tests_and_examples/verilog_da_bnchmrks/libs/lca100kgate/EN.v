module	EN (a, b, z);

input	a, b;
output	z;

xnor #1 g1(z, a, b);

endmodule
