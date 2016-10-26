/* Copyright (c) 1991-2014 Tachyon Design Automation Corp. */

/* === INSERT LICENSE ===

OSS CVC dual licensing modified Artistic Open Source Software License

Copyright © 1991-2014 Tachyon Design Automation Corp.
All Rights reserved.  Licensed software subject to prohibitions and
restrictions.

PLEASE READ THIS SOFTWARE LICENSE AGREEMENT CAREFULLY BEFORE USING THE
SOFTWARE. BY USING THE SOFTWARE, YOU ARE AGREEING TO BE BOUND BY THE
TERMS OF THIS LICENSE. IF YOU ARE ACCESSING THE SOFTWARE ELECTRONICALLY,
SIGNIFY YOUR AGREEMENT TO BE BOUND BY THE TERMS OF THIS LICENSE BY
CLICKING THE "AGREE/ACCEPT" BUTTON. IF YOU DO NOT AGREE TO THE TERMS OF
THIS LICENSE, DO NOT USE THE SOFTWARE AND (IF APPLICABLE) RETURN OR DELETE
THE SOFTWARE OR, IF THE SOFTWARE WAS ACCESSED ELECTRONICALLY, CLICK
"DISAGREE/DECLINE".

Preamble

  The intent of this document is to state the conditions under which a
Package may be copied, such that the Copyright Holder maintains artistic
control over the development of the Package as granted by Copyright law.
The intent is also to give the users of the Package the
right to use and distribute the Package using the free software model
as long as the Package and all modified, linked or accompanying software
is redistributed also using the open source model with included or
available source.  The Modifications must meet some conditions to
retain the artistic integrity of the Package and to preserve the
Package Copyright Holder's commercial rights.

  OSS CVC is dual licensed so that to commercially distribute the Package,
with or without linked in or modified source code, or as a forked project
with closed commercial software, a commercial license or other distribution
arrangements must be purchased from the Copyright Holder.

Definitions:

  "Package" refers to the collection of files distributed by the Copyright
Holder, and derivatives of that collection of files created through textual
modification.

  "Standard Version" refers to such a Package if it has not been modified,
or has been modified in accordance with the wishes of the Copyright Holder.

  "Copyright Holder" is whoever is named in the copyright notice or
copyright registrations for the Package.

  "You" and “your” means any person who would like to copy, distribute or
modify the Package.

  "Reasonable Copying Fee" is whatever you can justify on the basis of media
cost, duplication charges, time of people involved, and so on.

  "Freely Available" means that no fee is charged for the item itself,
though there may be a Reasonable Copying Fee involved in handling the
item. It also means that recipients of the item may redistribute it under
the same conditions they received it.

1. You may use, make and give away verbatim copies of the source form of
the Standard Version without any linking in or modifications of this
Package provided that you duplicate this License and all of the original
copyright notices and associated disclaimers.

2. You may apply bug fixes, portability fixes and other modifications
made available from the Copyright Holder. A Package modified in such a
way shall still be considered the Standard Version, and Copyright holder
retains copyright to all such changes.

3. You may otherwise modify your copy of this Package in any way, provided
that you insert a prominent notice in each changed file stating how and
when you changed that file, and provided that you do at least ONE of
the following:

    a) place your modifications into the Public Domain or otherwise make them
Freely Available, or by allowing the Copyright Holder to include your
modifications in the Standard Version of the Package.

    b) use the modified Package only individually or within your corporation
or organization.

    c) rename any non-standard Package (forked project usually) so the names
do not conflict with standard executables, which must also be provided, and
provide documentation for each non-standard Package that clearly documents
how it differs from the Standard Version.  The non-standard version must
retain this license so all redistributions of the non-standard version
must be distributed with all modified, linked, and accompanying code
available in source form.

    d) make other distribution arrangements with the Copyright Holder.


All versions must retain and include this License and disclaimers, and all
redistributions of a non-standard version must be distributed with all
modified, linked, and accompanying code available in source form.

In particular OSS CVC is intended to use the dual licensing model so any
commercial redistribution of a modified version, a forked project, a
standard OSS CVC as a commercial product (sold for more than a reasonable
redistribution fee), or a version linked with commercial closed source
software will require other distribution arrangements and license with
the Copyright Holder. 

4. You may distribute the programs of this Package in object code or
executable form provided that such versions include this License and
disclaimers and that all of the Package, including any modifications or
other bundled elements, are distributed as open source made Freely
Available and provided you also do at least ONE of the following:

    a) distribute a Standard Version of the executables and library files,
together with instructions (in the manual page or equivalent) on where to
get the Standard Version.

    b) accompany the distribution with the machine-readable source of the
Package with your modifications, if any.

    c) accompany any non-standard executables with their corresponding
Standard Version executables, giving the non-standard executables
different names, and clearly documenting the differences, together
with instructions on where to get the Standard Version.

    d) make other distribution arrangements with the Copyright Holder.

5. You may charge a Reasonable Copying Fee for any distribution of this
Package. You may charge any fee you choose for support of this Package.

6. Any Verilog standard API PLI interface source or binary code supplied by
you and linked into this Package shall not be considered part of this
Package. You may license your PLI libraries as you wish.

7. Any use, modification, and distribution of the Standard Version or
non-standard versions is governed by this Artistic License. By using,
modifying or distributing the Package, you accept this License.
Do not use, modify, or distribute the Package, if you do not accept
this license.

8. If your non-standard version has been derived from a non-standard
version made by someone other than you, you are nevertheless required
to ensure that your non-standard version complies with the requirements
of this license.

9. The name of the Copyright Holder may not be used to endorse or promote
products derived from this software without specific prior written
permission.  This license does not grant you the right to use any
trademark, service mark, trade name, or logo of the Copyright Holder.

10. This license includes the non-exclusive, worldwide, free-of-charge
patent license to make, have made, use, offer to sell, sell, import and
otherwise transfer the Package with respect to any patent claims
licensable by the Copyright Holder that are necessarily infringed by
the Package.  If you institute patent litigation (including a cross-claim
or counterclaim) against any party alleging that the Package constitutes
direct or contributory patent infringement, then this Artistic License
to you shall terminate on the date that such litigation is filed.

11. DISCLAIMER OF WARRANTIES: THIS PACKAGE IS PROVIDED "AS IS" AND
WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION,
THE IMPLIED WARRANTIES OF MERCHANTIBILITY, FITNESS FOR A PARTICULAR PURPOSE,
OR NON-INFRINGEMENT.  THE COPYRIGHT HOLDER SHALL NOT BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING IN ANY WAY
OUT OF THE USE OF THE PACKAGE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.

=== END INSERT === */

/*
 * system function id numbers
 * notice no patters other than pli tf_ start above these (at 1000 for now)
 */

/* functions for converting reals */
#define STN_BITSTOREAL 1
#define STN_ITOR 2
#define STN_REALTOBITS 3
#define STN_RTOI 4
#define STN_CEIL 5
#define STN_FLOOR 6

/* time related system functions */
#define STN_REALTIME 7
#define STN_STIME 8
#define STN_TIME 9
#define STN_SCALE 10

/* random number generators */
#define STN_RANDOM 11
#define STN_DIST_UNIFORM 12
#define STN_DIST_NORMAL 13
#define STN_DIST_EXPONENTIAL 14
#define STN_DIST_POISSON 15
#define STN_DIST_CHI_SQUARE 16
#define STN_DIST_T 17
#define STN_DIST_ERLANG 18

/* misc. system functions */
#define STN_TESTPLUSARGS 19
#define STN_FOPEN 20
#define STN_COUNT_DRIVERS 21
#define STN_RESET_COUNT 22
#define STN_RESET_VALUE 23
#define STN_GETPATTERN 24
#define STN_Q_FULL 25
#define STN_CLOG2 26

/* AIV 09/08/03 - new P1364 2001 fileio sys funcs */
#define STN_FGETC 27
#define STN_UNGETC 28
#define STN_FGETS 29
#define STN_FTELL 30
#define STN_REWIND 31
#define STN_FSEEK 32
#define STN_FERROR 33 
#define STN_FREAD 34
#define STN_FSCANF 35 
#define STN_SSCANF 36
/* AIV 03/23/09 - 2005 LRM has an $feof */
#define STN_FEOF 37

/* system task id numbers */

/* display type tasks */
#define STN_FCLOSE 100
/* formated procedural display - implied cr */
#define STN_DISPLAY 101
#define STN_DISPLAYB 102
#define STN_DISPLAYH 103
#define STN_DISPLAYO 104
#define STN_FDISPLAY 105
#define STN_FDISPLAYH 106
#define STN_FDISPLAYB 107
#define STN_FDISPLAYO 108

/* formated procedural display - no implied cr */
#define STN_WRITE 109
#define STN_WRITEH 110
#define STN_WRITEB 111
#define STN_WRITEO 112
#define STN_FWRITE 113
#define STN_FWRITEH 114
#define STN_FWRITEB 115
#define STN_FWRITEO 116

/* like display except write at end of current time */
#define STN_STROBE 117
#define STN_STROBEH 118
#define STN_STROBEB 119
#define STN_STROBEO 120
#define STN_FSTROBE 121
#define STN_FSTROBEH 122
#define STN_FSTROBEB 123
#define STN_FSTROBEO 124

#define STN_MONITOR 125
#define STN_MONITOROFF 126
#define STN_MONITORON 127
#define STN_FMONITOR 128
#define STN_MONITORH 129
#define STN_MONITORB 130
#define STN_MONITORO 131
#define STN_FMONITORH 132
#define STN_FMONITORB 133
#define STN_FMONITORO 134

/* time releated system tasks */
#define STN_PRINTTIMESCALE 135
#define STN_TIMEFORMAT 136

/* notice specify section timing checks not here - no exec - built in tevs */
#define STN_READMEMB 137
#define STN_READMEMH 138
#define STN_SREADMEMB 139
#define STN_SREADMEMH 140
#define STN_WRITEMEMB 141
#define STN_WRITEMEMH 142

/* dump variables tasks */
#define STN_DUMPVARS 145
#define STN_DUMPALL 146
#define STN_DUMPFILE 147
#define STN_DUMPFLUSH 148
#define STN_DUMPLIMIT 149
#define STN_DUMPOFF 150
#define STN_DUMPON 151

/* mainly interactive system tasks */
#define STN_KEY 152
#define STN_NOKEY 153
#define STN_LIST 154
#define STN_LOG 155
#define STN_NOLOG 156
#define STN_HISTORY 157
#define STN_SAVE 158
#define STN_INCSAVE 159
#define STN_INPUT 160
#define STN_RESTART 161
#define STN_SETTRACE 162
#define STN_CLEARTRACE 163
#define STN_RESET 164
#define STN_FINISH 165
#define STN_STOP 166
#define STN_KEEPCMDS 167
#define STN_NOKEEPCMDS 168

/* internal simulation state printng tasks */
#define STN_SCOPE 169
#define STN_SHOWALLINSTANCES 170
#define STN_SHOWEXPANDEDNETS 171
#define STN_SHOWSCOPES 172
#define STN_SHOWVARIABLES 173
#define STN_SHOWVARS 174

/* q manipulation tasks - also q_full function */
#define STN_Q_INITIALIZE 175
#define STN_Q_ADD 176
#define STN_Q_REMOVE 177
#define STN_Q_EXAM 178

/* sdf annotate system task */
#define STN_SDF_ANNOTATE 179

/* new P1364 2001 special signed/word32 conversion system functions */
#define STN_SIGNED 180
#define STN_UNSIGNED 181

/* graphical output tasks */
#define STN_GRREMOTE 182
#define STN_PSWAVES 183
#define STN_GRSYNCHON 184
#define STN_GRREGS 185
#define STN_GRWAVES 186
#define STN_FREEZEWAVES 187
#define STN_DEFINEGROUPWAVES 188

/* Cver extension (system tasks or functions) */
#define STN_SETDEBUG 190 
#define STN_CLEARDEBUG 191
#define STN_SETEVTRACE 192
#define STN_CLEAREVTRACE 193
#define STN_TRACEFILE 194
#define STN_STICKSTIME 195
#define STN_TICKSTIME 196
#define STN_SNAPSHOT 197
#define STN_SYSTEM 198
#define STN_SUPWARNS 199
#define STN_ALLOWWARNS 200
#define STN_MEMUSE 201
#define STN_FLUSHLOG 202
#define STN_SCANPLUSARGS 203
#define STN_VALUEPLUSARGS 204

/* new ams transcendental function extension but works in digital */
/* SJM 10/01/03 - leaving in for now */
#define STN_COS 217
#define STN_SIN 218
#define STN_TAN 219
#define STN_ACOS 220
#define STN_ASIN 221
#define STN_ATAN 222
#define STN_ATAN2 223
#define STN_COSH 224
#define STN_SINH 225
#define STN_TANH 226
#define STN_ACOSH 227
#define STN_ASINH 228
#define STN_ATANH 229

#define STN_INT 230
#define STN_SGN 231
#define STN_LN 232
#define STN_LOG10 233
#define STN_ABS 234
#define STN_POW 235
#define STN_SQRT 236
#define STN_EXP 237
#define STN_MIN 238
#define STN_MAX 239

#define STN_HSQRT 240
#define STN_HPOW 241
#define STN_HPWR 242
#define STN_HLOG 243
#define STN_HLOG10 244
#define STN_HDB 245
#define STN_HSIGN 246
#define STN_HYPOT 247

/* AIV 09/08/03 - new P1364 2001 fileio sys tasks */
#define STN_FFLUSH 248
#define STN_SWRITE 249
#define STN_SWRITEB 250
#define STN_SWRITEH 251
#define STN_SWRITEO 252
#define STN_SFORMAT 253

/* AIV 09/02/08 - new dumpvars sys tasks */
#define STN_DUMPPORTS 261
#define STN_DUMPPORTSALL 262
#define STN_DUMPPORTSFLUSH 263
#define STN_DUMPPORTSLIMIT 264
#define STN_DUMPPORTSOFF 265
#define STN_DUMPPORTSON 266

#define STN_FST_DUMPALL 267
#define STN_FST_DUMPFILE 268
#define STN_FST_DUMPFLUSH 269
#define STN_FST_DUMPLIMIT 270
#define STN_FST_DUMPOFF 271
#define STN_FST_DUMPON 272
#define STN_FST_DUMPREPACK 273
#define STN_FST_DUMPVARS 274
#define STN_FST_PARALLELOFF 275
#define STN_FST_PARALLELON 276

/* AIV 10/07/10 - new SV string tasks */
#define STN_PSPRINTF 277

/* AIV 10/12/10 - new array size functions */
#define STN_DIMENSION 278
#define STN_UNPACKED_DIMENSION 279
#define STN_LEFT 280
#define STN_RIGHT 281
#define STN_LOW 282
#define STN_HIGH 283
#define STN_INCREMENT 284
#define STN_SIZE 285

/* AIV 11/17/10 - new SV assert functions */
#define STN_ONEHOT 286
#define STN_ONEHOT0 287
#define STN_ISUNKNOWN 288
#define STN_COUNTONES 290

/* AIV 11/17/10 - new SV severity system tasks */
#define STN_FATAL 291
#define STN_ERROR 292
#define STN_WARNING 293
#define STN_INFO 294

#ifdef __XPROP__
#define STN_XTRACE_ON 295
#define STN_XTRACE_OFF 296
#endif

/* SJM 06-27-13 - new toggle on/off reset to untoggled state systems tasks */
#define STN_TGL_STATE_RESET 297
#define STN_TGL_RECORD_ON 298
#define STN_TGL_RECORD_OFF 299
#define STN_TGL_RECORD_OFF_SET_OLD_VAL_X 300
