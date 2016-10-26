module FD2 (D, CP, CD, Q, QN);


input	D, CP, CD;
output	Q, QN;

reg	QI;

always @(posedge CP or negedge CD)

	if (!CD)
		QI = #1 0;
	else
		QI = #1 D;

assign QN = ~QI;
assign Q = QI;

endmodule
