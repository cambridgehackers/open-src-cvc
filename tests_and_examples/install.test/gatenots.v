module example_2b;
parameter
	in_width = 50,
	patterns = 10,
	out_width = 60,
	step = 200,
        // 0 no monitor, 1 - monitor, 2 - end of period strobe
	mon_flag = 1;

mod1 cct(o1, o2, o3, o4, o5, o6, o7, o8, o9, o10,
 o11, o12, o13, o14, o15, o16, o17, o18, o19, o20,
 o21, o22, o23, o24, o25, o26, o27, o28, o29, o30,
 o31, o32, o33, o34, o35, o36, o37, o38, o39, o40,
 o41, o42, o43, o44, o45, o46, o47, o48, o49, o50,
 o51, o52, o53, o54, o55, o56, o57, o58, o59, o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct1(m1_o1, m1_o2, m1_o3, m1_o4, m1_o5, m1_o6, m1_o7, m1_o8, m1_o9, m1_o10,
 m1_o11, m1_o12, m1_o13, m1_o14, m1_o15, m1_o16, m1_o17, m1_o18, m1_o19, m1_o20,
 m1_o21, m1_o22, m1_o23, m1_o24, m1_o25, m1_o26, m1_o27, m1_o28, m1_o29, m1_o30,
 m1_o31, m1_o32, m1_o33, m1_o34, m1_o35, m1_o36, m1_o37, m1_o38, m1_o39, m1_o40,
 m1_o41, m1_o42, m1_o43, m1_o44, m1_o45, m1_o46, m1_o47, m1_o48, m1_o49, m1_o50,
 m1_o51, m1_o52, m1_o53, m1_o54, m1_o55, m1_o56, m1_o57, m1_o58, m1_o59, m1_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct2(m2_o1, m2_o2, m2_o3, m2_o4, m2_o5, m2_o6, m2_o7, m2_o8, m2_o9, m2_o10,
 m2_o11, m2_o12, m2_o13, m2_o14, m2_o15, m2_o16, m2_o17, m2_o18, m2_o19, m2_o20,
 m2_o21, m2_o22, m2_o23, m2_o24, m2_o25, m2_o26, m2_o27, m2_o28, m2_o29, m2_o30,
 m2_o31, m2_o32, m2_o33, m2_o34, m2_o35, m2_o36, m2_o37, m2_o38, m2_o39, m2_o40,
 m2_o41, m2_o42, m2_o43, m2_o44, m2_o45, m2_o46, m2_o47, m2_o48, m2_o49, m2_o50,
 m2_o51, m2_o52, m2_o53, m2_o54, m2_o55, m2_o56, m2_o57, m2_o58, m2_o59, m2_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct3(m3_o1, m3_o2, m3_o3, m3_o4, m3_o5, m3_o6, m3_o7, m3_o8, m3_o9, m3_o10,
 m3_o11, m3_o12, m3_o13, m3_o14, m3_o15, m3_o16, m3_o17, m3_o18, m3_o19, m3_o20,
 m3_o21, m3_o22, m3_o23, m3_o24, m3_o25, m3_o26, m3_o27, m3_o28, m3_o29, m3_o30,
 m3_o31, m3_o32, m3_o33, m3_o34, m3_o35, m3_o36, m3_o37, m3_o38, m3_o39, m3_o40,
 m3_o41, m3_o42, m3_o43, m3_o44, m3_o45, m3_o46, m3_o47, m3_o48, m3_o49, m3_o50,
 m3_o51, m3_o52, m3_o53, m3_o54, m3_o55, m3_o56, m3_o57, m3_o58, m3_o59, m3_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct4(m4_o1, m4_o2, m4_o3, m4_o4, m4_o5, m4_o6, m4_o7, m4_o8, m4_o9, m4_o10,
 m4_o11, m4_o12, m4_o13, m4_o14, m4_o15, m4_o16, m4_o17, m4_o18, m4_o19, m4_o20,
 m4_o21, m4_o22, m4_o23, m4_o24, m4_o25, m4_o26, m4_o27, m4_o28, m4_o29, m4_o30,
 m4_o31, m4_o32, m4_o33, m4_o34, m4_o35, m4_o36, m4_o37, m4_o38, m4_o39, m4_o40,
 m4_o41, m4_o42, m4_o43, m4_o44, m4_o45, m4_o46, m4_o47, m4_o48, m4_o49, m4_o50,
 m4_o51, m4_o52, m4_o53, m4_o54, m4_o55, m4_o56, m4_o57, m4_o58, m4_o59, m4_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct5(m5_o1, m5_o2, m5_o3, m5_o4, m5_o5, m5_o6, m5_o7, m5_o8, m5_o9, m5_o10,
 m5_o11, m5_o12, m5_o13, m5_o14, m5_o15, m5_o16, m5_o17, m5_o18, m5_o19, m5_o20,
 m5_o21, m5_o22, m5_o23, m5_o24, m5_o25, m5_o26, m5_o27, m5_o28, m5_o29, m5_o30,
 m5_o31, m5_o32, m5_o33, m5_o34, m5_o35, m5_o36, m5_o37, m5_o38, m5_o39, m5_o40,
 m5_o41, m5_o42, m5_o43, m5_o44, m5_o45, m5_o46, m5_o47, m5_o48, m5_o49, m5_o50,
 m5_o51, m5_o52, m5_o53, m5_o54, m5_o55, m5_o56, m5_o57, m5_o58, m5_o59, m5_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct6(m6_o1, m6_o2, m6_o3, m6_o4, m6_o5, m6_o6, m6_o7, m6_o8, m6_o9, m6_o10,
 m6_o11, m6_o12, m6_o13, m6_o14, m6_o15, m6_o16, m6_o17, m6_o18, m6_o19, m6_o20,
 m6_o21, m6_o22, m6_o23, m6_o24, m6_o25, m6_o26, m6_o27, m6_o28, m6_o29, m6_o30,
 m6_o31, m6_o32, m6_o33, m6_o34, m6_o35, m6_o36, m6_o37, m6_o38, m6_o39, m6_o40,
 m6_o41, m6_o42, m6_o43, m6_o44, m6_o45, m6_o46, m6_o47, m6_o48, m6_o49, m6_o50,
 m6_o51, m6_o52, m6_o53, m6_o54, m6_o55, m6_o56, m6_o57, m6_o58, m6_o59, m6_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct7(m7_o1, m7_o2, m7_o3, m7_o4, m7_o5, m7_o6, m7_o7, m7_o8, m7_o9, m7_o10,
 m7_o11, m7_o12, m7_o13, m7_o14, m7_o15, m7_o16, m7_o17, m7_o18, m7_o19, m7_o20,
 m7_o21, m7_o22, m7_o23, m7_o24, m7_o25, m7_o26, m7_o27, m7_o28, m7_o29, m7_o30,
 m7_o31, m7_o32, m7_o33, m7_o34, m7_o35, m7_o36, m7_o37, m7_o38, m7_o39, m7_o40,
 m7_o41, m7_o42, m7_o43, m7_o44, m7_o45, m7_o46, m7_o47, m7_o48, m7_o49, m7_o50,
 m7_o51, m7_o52, m7_o53, m7_o54, m7_o55, m7_o56, m7_o57, m7_o58, m7_o59, m7_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct8(m8_o1, m8_o2, m8_o3, m8_o4, m8_o5, m8_o6, m8_o7, m8_o8, m8_o9, m8_o10,
 m8_o11, m8_o12, m8_o13, m8_o14, m8_o15, m8_o16, m8_o17, m8_o18, m8_o19, m8_o20,
 m8_o21, m8_o22, m8_o23, m8_o24, m8_o25, m8_o26, m8_o27, m8_o28, m8_o29, m8_o30,
 m8_o31, m8_o32, m8_o33, m8_o34, m8_o35, m8_o36, m8_o37, m8_o38, m8_o39, m8_o40,
 m8_o41, m8_o42, m8_o43, m8_o44, m8_o45, m8_o46, m8_o47, m8_o48, m8_o49, m8_o50,
 m8_o51, m8_o52, m8_o53, m8_o54, m8_o55, m8_o56, m8_o57, m8_o58, m8_o59, m8_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

mod1 cct9(m9_o1, m9_o2, m9_o3, m9_o4, m9_o5, m9_o6, m9_o7, m9_o8, m9_o9, m9_o10,
 m9_o11, m9_o12, m9_o13, m9_o14, m9_o15, m9_o16, m9_o17, m9_o18, m9_o19, m9_o20,
 m9_o21, m9_o22, m9_o23, m9_o24, m9_o25, m9_o26, m9_o27, m9_o28, m9_o29, m9_o30,
 m9_o31, m9_o32, m9_o33, m9_o34, m9_o35, m9_o36, m9_o37, m9_o38, m9_o39, m9_o40,
 m9_o41, m9_o42, m9_o43, m9_o44, m9_o45, m9_o46, m9_o47, m9_o48, m9_o49, m9_o50,
 m9_o51, m9_o52, m9_o53, m9_o54, m9_o55, m9_o56, m9_o57, m9_o58, m9_o59, m9_o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

 reg [1:in_width] in, in_mem[1:patterns];
 integer index;

 assign {
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50 }
  = $getpattern(in_mem[index]);

 // monitor control
 initial
  begin
   if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m0) %h", in_mem[index], 
     { o1, o2, o3, o4, o5, o6, o7, o8, o9, o10,
     o11, o12, o13, o14, o15, o16, o17, o18, o19, o20,
     o21, o22, o23, o24, o25, o26, o27, o28, o29, o30,
      o31, o32, o33, o34, o35, o36, o37, o38, o39, o40,
     o41, o42, o43, o44, o45, o46, o47, o48, o49, o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m1) %h", in_mem[index], 
    {m1_o1, m1_o2, m1_o3, m1_o4, m1_o5, m1_o6, m1_o7, m1_o8, m1_o9, m1_o10,
     m1_o11, m1_o12, m1_o13, m1_o14, m1_o15, m1_o16, m1_o17, m1_o18, m1_o19,
     m1_o20, m1_o21, m1_o22, m1_o23, m1_o24, m1_o25, m1_o26, m1_o27, m1_o28,
     m1_o29, m1_o30, m1_o31, m1_o32, m1_o33, m1_o34, m1_o35, m1_o36, m1_o37,
     m1_o38, m1_o39, m1_o40, m1_o41, m1_o42, m1_o43, m1_o44, m1_o45, m1_o46,
     m1_o47, m1_o48, m1_o49, m1_o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m2) %h", in_mem[index], 
    {m2_o1, m2_o2, m2_o3, m2_o4, m2_o5, m2_o6, m2_o7, m2_o8, m2_o9, m2_o10,
     m2_o11, m2_o12, m2_o13, m2_o14, m2_o15, m2_o16, m2_o17, m2_o18, m2_o19,
     m2_o20, m2_o21, m2_o22, m2_o23, m2_o24, m2_o25, m2_o26, m2_o27, m2_o28,
     m2_o29, m2_o30, m2_o31, m2_o32, m2_o33, m2_o34, m2_o35, m2_o36, m2_o37,
     m2_o38, m2_o39, m2_o40, m2_o41, m2_o42, m2_o43, m2_o44, m2_o45, m2_o46,
     m2_o47, m2_o48, m2_o49, m2_o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m3) %h", in_mem[index], 
    {m3_o1, m3_o2, m3_o3, m3_o4, m3_o5, m3_o6, m3_o7, m3_o8, m3_o9, m3_o10,
     m3_o11, m3_o12, m3_o13, m3_o14, m3_o15, m3_o16, m3_o17, m3_o18, m3_o19,
     m3_o20, m3_o21, m3_o22, m3_o23, m3_o24, m3_o25, m3_o26, m3_o27, m3_o28,
     m3_o29, m3_o30, m3_o31, m3_o32, m3_o33, m3_o34, m3_o35, m3_o36, m3_o37,
     m3_o38, m3_o39, m3_o40, m3_o41, m3_o42, m3_o43, m3_o44, m3_o45, m3_o46,
     m3_o47, m3_o48, m3_o49, m3_o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m4) %h", in_mem[index], 
    {m4_o1, m4_o2, m4_o3, m4_o4, m4_o5, m4_o6, m4_o7, m4_o8, m4_o9, m4_o10,
     m4_o11, m4_o12, m4_o13, m4_o14, m4_o15, m4_o16, m4_o17, m4_o18, m4_o19,
     m4_o20, m4_o21, m4_o22, m4_o23, m4_o24, m4_o25, m4_o26, m4_o27, m4_o28,
     m4_o29, m4_o30, m4_o31, m4_o32, m4_o33, m4_o34, m4_o35, m4_o36, m4_o37,
     m4_o38, m4_o39, m4_o40, m4_o41, m4_o42, m4_o43, m4_o44, m4_o45, m4_o46,
     m4_o47, m4_o48, m4_o49, m4_o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m5) %h", in_mem[index], 
    {m5_o1, m5_o2, m5_o3, m5_o4, m5_o5, m5_o6, m5_o7, m5_o8, m5_o9, m5_o10,
     m5_o11, m5_o12, m5_o13, m5_o14, m5_o15, m5_o16, m5_o17, m5_o18, m5_o19,
     m5_o20, m5_o21, m5_o22, m5_o23, m5_o24, m5_o25, m5_o26, m5_o27, m5_o28,
     m5_o29, m5_o30, m5_o31, m5_o32, m5_o33, m5_o34, m5_o35, m5_o36, m5_o37,
     m5_o38, m5_o39, m5_o40, m5_o41, m5_o42, m5_o43, m5_o44, m5_o45, m5_o46,
     m5_o47, m5_o48, m5_o49, m5_o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m6) %h", in_mem[index], 
    {m6_o1, m6_o2, m6_o3, m6_o4, m6_o5, m6_o6, m6_o7, m6_o8, m6_o9, m6_o10,
     m6_o11, m6_o12, m6_o13, m6_o14, m6_o15, m6_o16, m6_o17, m6_o18, m6_o19,
     m6_o20, m6_o21, m6_o22, m6_o23, m6_o24, m6_o25, m6_o26, m6_o27, m6_o28,
     m6_o29, m6_o30, m6_o31, m6_o32, m6_o33, m6_o34, m6_o35, m6_o36, m6_o37,
     m6_o38, m6_o39, m6_o40, m6_o41, m6_o42, m6_o43, m6_o44, m6_o45, m6_o46,
     m6_o47, m6_o48, m6_o49, m6_o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m7) %h", in_mem[index], 
    {m7_o1, m7_o2, m7_o3, m7_o4, m7_o5, m7_o6, m7_o7, m7_o8, m7_o9, m7_o10,
     m7_o11, m7_o12, m7_o13, m7_o14, m7_o15, m7_o16, m7_o17, m7_o18, m7_o19,
     m7_o20, m7_o21, m7_o22, m7_o23, m7_o24, m7_o25, m7_o26, m7_o27, m7_o28,
     m7_o29, m7_o30, m7_o31, m7_o32, m7_o33, m7_o34, m7_o35, m7_o36, m7_o37,
     m7_o38, m7_o39, m7_o40, m7_o41, m7_o42, m7_o43, m7_o44, m7_o45, m7_o46,
     m7_o47, m7_o48, m7_o49, m7_o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m8) %h", in_mem[index], 
    {m8_o1, m8_o2, m8_o3, m8_o4, m8_o5, m8_o6, m8_o7, m8_o8, m8_o9, m8_o10,
     m8_o11, m8_o12, m8_o13, m8_o14, m8_o15, m8_o16, m8_o17, m8_o18, m8_o19,
     m8_o20, m8_o21, m8_o22, m8_o23, m8_o24, m8_o25, m8_o26, m8_o27, m8_o28,
     m8_o29, m8_o30, m8_o31, m8_o32, m8_o33, m8_o34, m8_o35, m8_o36, m8_o37,
     m8_o38, m8_o39, m8_o40, m8_o41, m8_o42, m8_o43, m8_o44, m8_o45, m8_o46,
     m8_o47, m8_o48, m8_o49, m8_o50 });
   #((patterns*step)/10) if (mon_flag == 1)
    $monitor($stime,, "input %h outputs(m9) %h", in_mem[index], 
    {m9_o1, m9_o2, m9_o3, m9_o4, m9_o5, m9_o6, m9_o7, m9_o8, m9_o9, m9_o10,
     m9_o11, m9_o12, m9_o13, m9_o14, m9_o15, m9_o16, m9_o17, m9_o18, m9_o19,
     m9_o20, m9_o21, m9_o22, m9_o23, m9_o24, m9_o25, m9_o26, m9_o27, m9_o28,
     m9_o29, m9_o30, m9_o31, m9_o32, m9_o33, m9_o34, m9_o35, m9_o36, m9_o37,
     m9_o38, m9_o39, m9_o40, m9_o41, m9_o42, m9_o43, m9_o44, m9_o45, m9_o46,
     m9_o47, m9_o48, m9_o49, m9_o50 });
  end

 initial
  begin
   // $dumpvars;
   $readmemb("gn.mem", in_mem, 1, patterns);

   for (index = 1; index <= patterns; index = index + 1)
    begin
     fork
      #(step/2)
       if (mon_flag == 2) 
        case (10*$time/(patterns*step))
         0: $strobe($stime,, "in=%h out(m0)=%h", in_mem[index], 
          { o1, o2, o3, o4, o5, o6, o7, o8, o9, o10,
           o11, o12, o13, o14, o15, o16, o17, o18, o19, o20,
           o21, o22, o23, o24, o25, o26, o27, o28, o29, o30,
           o31, o32, o33, o34, o35, o36, o37, o38, o39, o40,
           o41, o42, o43, o44, o45, o46, o47, o48, o49, o50 });
         1: $strobe($stime,, "in=%h out(m2)=%h", in_mem[index], 
          {m1_o1, m1_o2, m1_o3, m1_o4, m1_o5, m1_o6, m1_o7, m1_o8, m1_o9, m1_o10,
          m1_o11, m1_o12, m1_o13, m1_o14, m1_o15, m1_o16, m1_o17, m1_o18, m1_o19,
          m1_o20, m1_o21, m1_o22, m1_o23, m1_o24, m1_o25, m1_o26, m1_o27, m1_o28,
          m1_o29, m1_o30, m1_o31, m1_o32, m1_o33, m1_o34, m1_o35, m1_o36, m1_o37,
          m1_o38, m1_o39, m1_o40, m1_o41, m1_o42, m1_o43, m1_o44, m1_o45, m1_o46,
          m1_o47, m1_o48, m1_o49, m1_o50 });
         2: $strobe($stime,, "in=%h out(m2)=%h", in_mem[index], 
          {m2_o1, m2_o2, m2_o3, m2_o4, m2_o5, m2_o6, m2_o7, m2_o8, m2_o9, m2_o10,
          m2_o11, m2_o12, m2_o13, m2_o14, m2_o15, m2_o16, m2_o17, m2_o18, m2_o19,
          m2_o20, m2_o21, m2_o22, m2_o23, m2_o24, m2_o25, m2_o26, m2_o27, m2_o28,
          m2_o29, m2_o30, m2_o31, m2_o32, m2_o33, m2_o34, m2_o35, m2_o36, m2_o37,
          m2_o38, m2_o39, m2_o40, m2_o41, m2_o42, m2_o43, m2_o44, m2_o45, m2_o46,
          m2_o47, m2_o48, m2_o49, m2_o50 });
         3: $strobe($stime,, "in=%h out(m3)=%h", in_mem[index], 
          {m3_o1, m3_o2, m3_o3, m3_o4, m3_o5, m3_o6, m3_o7, m3_o8, m3_o9, m3_o10,
          m3_o11, m3_o12, m3_o13, m3_o14, m3_o15, m3_o16, m3_o17, m3_o18, m3_o19,
          m3_o20, m3_o21, m3_o22, m3_o23, m3_o24, m3_o25, m3_o26, m3_o27, m3_o28,
          m3_o29, m3_o30, m3_o31, m3_o32, m3_o33, m3_o34, m3_o35, m3_o36, m3_o37,
          m3_o38, m3_o39, m3_o40, m3_o41, m3_o42, m3_o43, m3_o44, m3_o45, m3_o46,
          m3_o47, m3_o48, m3_o49, m3_o50 });
         4: $strobe($stime,, "in=%h out(m4)=%h", in_mem[index], 
          {m4_o1, m4_o2, m4_o3, m4_o4, m4_o5, m4_o6, m4_o7, m4_o8, m4_o9, m4_o10,
          m4_o11, m4_o12, m4_o13, m4_o14, m4_o15, m4_o16, m4_o17, m4_o18, m4_o19,
          m4_o20, m4_o21, m4_o22, m4_o23, m4_o24, m4_o25, m4_o26, m4_o27, m4_o28,
          m4_o29, m4_o30, m4_o31, m4_o32, m4_o33, m4_o34, m4_o35, m4_o36, m4_o37,
          m4_o38, m4_o39, m4_o40, m4_o41, m4_o42, m4_o43, m4_o44, m4_o45, m4_o46,
          m4_o47, m4_o48, m4_o49, m4_o50 });
         5: $strobe($stime,, "in=%h out(m5)=%h", in_mem[index], 
          {m5_o1, m5_o2, m5_o3, m5_o4, m5_o5, m5_o6, m5_o7, m5_o8, m5_o9, m5_o10,
          m5_o11, m5_o12, m5_o13, m5_o14, m5_o15, m5_o16, m5_o17, m5_o18, m5_o19,
          m5_o20, m5_o21, m5_o22, m5_o23, m5_o24, m5_o25, m5_o26, m5_o27, m5_o28,
          m5_o29, m5_o30, m5_o31, m5_o32, m5_o33, m5_o34, m5_o35, m5_o36, m5_o37,
          m5_o38, m5_o39, m5_o40, m5_o41, m5_o42, m5_o43, m5_o44, m5_o45, m5_o46,
          m5_o47, m5_o48, m5_o49, m5_o50 });
         6: $strobe($stime,, "in=%h out(m6)=%h", in_mem[index], 
          {m6_o1, m6_o2, m6_o3, m6_o4, m6_o5, m6_o6, m6_o7, m6_o8, m6_o9, m6_o10,
          m6_o11, m6_o12, m6_o13, m6_o14, m6_o15, m6_o16, m6_o17, m6_o18, m6_o19,
          m6_o20, m6_o21, m6_o22, m6_o23, m6_o24, m6_o25, m6_o26, m6_o27, m6_o28,
          m6_o29, m6_o30, m6_o31, m6_o32, m6_o33, m6_o34, m6_o35, m6_o36, m6_o37,
          m6_o38, m6_o39, m6_o40, m6_o41, m6_o42, m6_o43, m6_o44, m6_o45, m6_o46,
          m6_o47, m6_o48, m6_o49, m6_o50 });
         7: $strobe($stime,, "in=%h out(m7)=%h", in_mem[index], 
          {m7_o1, m7_o2, m7_o3, m7_o4, m7_o5, m7_o6, m7_o7, m7_o8, m7_o9, m7_o10,
          m7_o11, m7_o12, m7_o13, m7_o14, m7_o15, m7_o16, m7_o17, m7_o18, m7_o19,
          m7_o20, m7_o21, m7_o22, m7_o23, m7_o24, m7_o25, m7_o26, m7_o27, m7_o28,
          m7_o29, m7_o30, m7_o31, m7_o32, m7_o33, m7_o34, m7_o35, m7_o36, m7_o37,
          m7_o38, m7_o39, m7_o40, m7_o41, m7_o42, m7_o43, m7_o44, m7_o45, m7_o46,
          m7_o47, m7_o48, m7_o49, m7_o50 });
         8: $strobe($stime,, "in=%h out(m8)=%h", in_mem[index], 
          {m8_o1, m8_o2, m8_o3, m8_o4, m8_o5, m8_o6, m8_o7, m8_o8, m8_o9, m8_o10,
          m8_o11, m8_o12, m8_o13, m8_o14, m8_o15, m8_o16, m8_o17, m8_o18, m8_o19,
          m8_o20, m8_o21, m8_o22, m8_o23, m8_o24, m8_o25, m8_o26, m8_o27, m8_o28,
          m8_o29, m8_o30, m8_o31, m8_o32, m8_o33, m8_o34, m8_o35, m8_o36, m8_o37,
          m8_o38, m8_o39, m8_o40, m8_o41, m8_o42, m8_o43, m8_o44, m8_o45, m8_o46,
          m8_o47, m8_o48, m8_o49, m8_o50 });
         9: $strobe($stime,, "in=%h out(m9)=%h", in_mem[index], 
          {m9_o1, m9_o2, m9_o3, m9_o4, m9_o5, m9_o6, m9_o7, m9_o8, m9_o9, m9_o10,
          m9_o11, m9_o12, m9_o13, m9_o14, m9_o15, m9_o16, m9_o17, m9_o18, m9_o19,
          m9_o20, m9_o21, m9_o22, m9_o23, m9_o24, m9_o25, m9_o26, m9_o27, m9_o28,
          m9_o29, m9_o30, m9_o31, m9_o32, m9_o33, m9_o34, m9_o35, m9_o36, m9_o37,
          m9_o38, m9_o39, m9_o40, m9_o41, m9_o42, m9_o43, m9_o44, m9_o45, m9_o46,
          m9_o47, m9_o48, m9_o49, m9_o50 });
        endcase
      #step;
     join
    end 
  end
endmodule 

module mod1(o1, o2, o3, o4, o5, o6, o7, o8, o9, o10,
 o11, o12, o13, o14, o15, o16, o17, o18, o19, o20,
 o21, o22, o23, o24, o25, o26, o27, o28, o29, o30,
 o31, o32, o33, o34, o35, o36, o37, o38, o39, o40,
 o41, o42, o43, o44, o45, o46, o47, o48, o49, o50,
 o51, o52, o53, o54, o55, o56, o57, o58, o59, o60,
 i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50);

 output o1, o2, o3, o4, o5, o6, o7, o8, o9, o10,
 o11, o12, o13, o14, o15, o16, o17, o18, o19, o20,
 o21, o22, o23, o24, o25, o26, o27, o28, o29, o30,
 o31, o32, o33, o34, o35, o36, o37, o38, o39, o40,
 o41, o42, o43, o44, o45, o46, o47, o48, o49, o50,
 o51, o52, o53, o54, o55, o56, o57, o58, o59, o60;

 input i1, i2, i3, i4, i5, i6, i7, i8, i9, i10,
 i11, i12, i13, i14, i15, i16, i17, i18, i19, i20,
 i21, i22, i23, i24, i25, i26, i27, i28, i29, i30,
 i31, i32, i33, i34, i35, i36, i37, i38, i39, i40,
 i41, i42, i43, i44, i45, i46, i47, i48, i49, i50;

 dmod
  mi1(o1, i1), mi2(o2, i2), mi3(o3, i3), mi4(o4, i4),
  mi5(o5, i5),  mi6(o6, i6), mi7(o7, i7), mi8(o8, i8),
  mi9(o9, i9), mi10(o10, i10),  mi11(o11, i11), mi12(o12, i12),
  mi13(o13, i13), mi14(o14, i14), mi15(o15, i15), mi16(o16, i16),
  mi17(o17, i17), mi18(o18, i18), mi19(o19, i19), mi110(o20, i20),
  mi21(o21, i21), mi22(o22, i22), mi23(o23, i23), mi24(o24, i24),
  mi25(o25, i25),  mi26(o26, i26), mi27(o27, i27), mi28(o28, i28),
  mi29(o29, i29), mi30(o30, i30),  mi31(o31, i31), mi32(o32, i32),
  mi33(o33, i33), mi34(o34, i34),  mi35(o35, i35), mi36(o36, i36),
  mi37(o37, i37), mi38(o38, i38),  mi39(o39, i39), mi40(o40, i40),
  mi41(o41, i41), mi42(o42, i42),  mi43(o43, i43), mi44(o44, i44),
  mi45(o45, i45),  mi46(o46, i46), mi47(o47, i47), mi48(o48, i48),
  mi49(o49, i49), mi50(o50, i50),
  mi51(o51, i1), mi52(o52, i2), mi53(o53, i3), mi54(o54, i4),
  mi55(o55, i5), mi56(o56, i6), mi57(o57, i7), mi58(o58, i8),
  mi59(o59, i9), mi60(o60, i10);
endmodule

/* odd number of nots - input inverted to output */
module dmod(o, i);
 output o;
 input i;

 not #(5,3) g0(o, w1), g1(w1, w2), g2(w2, w3),
 g3(w3, w4), g4(w4, w5), g5(w5, w6), g6(w6, w7), g7(w7, w8),
 g8(w8, w9), g9(w9, w10), g10(w10, w11), g11(w11, w12), g12(w12, w13),
 // notice broken chain  
 g13(w13, i), g14(w14, w15), g15(w15, w16), g16(w16, w17), g17(w17, w18),
 g18(w18, w19), g19(w19, w20), g20(w20, w21), g21(w21, w22), g22(w22, i);
endmodule
