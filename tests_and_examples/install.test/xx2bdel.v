module yy;
parameter
	in_width = 10,
	patterns = 8,
	out_width = 20,
	step = 200,
	mon_flag = 1;
 parameter d1=3, d2=5, d3=7;

med1 intop(to1, to2, to3, to4, to5, to6, to7, to8, to9, to10,
 to11, to12, to13, to14, to15, to16, to17, to18, to19, to20,
 ti1, ti2, ti3, ti4, ti5, ti6, ti7, ti8, ti9, ti10);

 reg [15:0] gnam;
 reg [1:in_width] in, in_mem[1:patterns];
 integer index, i;

 assign { ti1, ti2, ti3, ti4, ti5, ti6, ti7, ti8, ti9, ti10 }
  = $getpattern(in_mem[index]);

   /* --- */ 
 initial
  begin
   $readmemb("mem.dat", in_mem, 1, patterns);
   $monitor($stime,, "input %b output %b and %b", in_mem[index], 
    { to1, to2, to3, to4, to5, to6, to7, to8, to9, to10 }, 
    { to11, to12, to13, to14, to15, to16, to17, to18, to19, to20 });
   // $showvars;
   // $setevtrace;
   // $monitoroff;
   // $list(yy);
  for (index = 1; index <= patterns; index = index + 1) 
    fork
     #(step/2)
      if (mon_flag)
       $strobe($stime,, "-->read: %h same: %h invert: %h",
       in_mem[index],
        { to1, to2, to3, to4, to5, to6, to7, to8, to9, to10 },
	{ to11, to12, to13, to14, to15, to16, to17, to18, to19, to20});
     #step;
    join
  end
endmodule 

module med1(mo1, mo2, mo3, mo4, mo5, mo6, mo7, mo8, mo9, mo10,
 mo11, mo12, mo13, mo14, mo15, mo16, mo17, mo18, mo19, mo20,
 mi1, mi2, mi3, mi4, mi5, mi6, mi7, mi8, mi9, mi10);

 output mo1, mo2, mo3, mo4, mo5, mo6, mo7, mo8, mo9, mo10,
  mo11, mo12, mo13, mo14, mo15, mo16, mo17, mo18, mo19, mo20;
 input mi1, mi2, mi3, mi4, mi5, mi6, mi7, mi8, mi9, mi10;

 bot
  inmedi1(mo1, mi1), inmedi2(mo2, mi2), inmedi3(mo3, mi3), inmedi4(mo4, mi4),
  inmedi5(mo5, mi5),  inmedi6(mo6, mi6), inmedi7(mo7, mi7), inmedi8(mo8, mi8),
  inmedi9(mo9, mi9), inmedi10(mo10, mi10);
 bot2
  inmed11(mo11, mi1), inmed12(mo12, mi2),
  inmed13(mo13, mi3), inmed14(mo14, mi4), inmed15(mo15, mi5),
  inmed16(mo16, mi6), inmed17(mo17, mi7), inmed18(mo18, mi8),
  inmed19(mo19, mi9), inmed20(mo20, mi10);
endmodule

// identity through some nots
module bot(o, i);
 output o;
 input i;
 not #1 g0(o, w1), g1(w1, i), g2(w2, w3), g3(w3, i);
endmodule

// inverter through some nots
module bot2(o, i);
 output o;
 input i;

 not #1 g0(o, w1), g1(w1, w2), g2(w2, i);
endmodule
