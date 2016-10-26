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

/* for x86 ebp spill variable stack must grown downward */
/* undef for machine with upward growing stack */
//AIVS
//#define STACK_GROWS_DOWN 1

/* types of flow graphs - mod elments linked into flow graph lists */
#define FLOWG_UNKN 0
#define FLOWG_PROC 1
#define FLOWG_TASK 2
#define FLOWG_FUNC 3
#define FLOWG_DCE 4           /* net dce processing flow graph */ 
#define FLOWG_NPP 5           /* net npp processing flow graph */
#define FLOWG_MULTFI 6
#define FLOWG_CONTA 7
#define FLOWG_ICONN 8
#define FLOWG_GATECA 9
#define FLOWG_GATEDA 10
#define FLOWG_NCHG 11
#define FLOWG_PROCESS_NCHG 12
#define FLOWG_MIPD 13
#define FLOWG_WIRE_EV 14
#define FLOWG_TRPTH 15
#define FLOWG_MDC 16

#define FLOWG_SIZE 17

/* type of basic block connecting edge */
#define BE_UNKN 0
#define BE_TRUE 1
#define BE_FALSE 2
#define BE_UNCOND 3

/* type of value tracking tn amount of infrrmation known states */
#define TRK_UNKN 0
#define TRK_TOP_UNDEF 1
#define TRK_CON 2
#define TRK_BOT_VARYING 3

#define FG_NONE 0
#define FG_ICONN 1
#define FG_GATECA 2
#define FG_CAP 3
#define FG_NCHG 4

/* insn operand input (addressing/type) modes - for input types in bbgen */
#define AM_UNKN 0
#define AM_NONE 1
#define AM_IMM 2
#define AM_REG 3
#define AM_NDXREG 4
#define AM_NDXREG_DISP 5
#define AM_NONREG_OFS 6
#define AM_IDP_ADR_OFS 7
#define AM_LABEL 8
#define AM_NLO_ARRNDX 9       /* special case for glb nlo array indexing */  
#define AM_BBLK 10
#define AM_NLO 11
#define AM_NDXREG_DBL 12      /* special double index used for opt leal */

/* tmp name type */
//AIV BEWARE if extending number of types need to add bits to tn_typ
//in tn_t
#define TN_UNKN 1
#define TN_VAL 2
#define TN_ADR 3

/* constant addr tns that become mem labels in assembly */
#define COMLAB_NONE 1

/* things that point to read/write NL object storage */
/* per inst asm insn adds and adr adds can be used - interp shares addr */ 
#define COMLAB_GATEBP 2       /* gate gstate.bp */
#define COMLAB_NETBP 3        /* net nva.bp */
#define COMLAB_DCEPREV 4      /* dce (dcevnt_t) prevval.bp */
#define COMLAB_CONTA_DRVBP 5  /* for conta - ca_drv_wp.bp */

/* things allocated in area only for compiler - like netbp but cvc only */
/* things that intepreter malloc but are run time static area for compiler */
#define COMLAB_NB_BP 6        /* NB statement pending rhs stmt value */ 
#define COMLAB_REP_BP 7       /* for repeat stmt - static area for count */
#define COMLAB_DCEEXPR_BP 8   /* for delay/event ctrl - state expr value */
#define COMLAB_DCESCH_TEVS 9  /* for dce's - pending schd tev storage */
#define COMLAB_DELREP_BP 10   /* for event ctrl repeat - area for count */

/* read only NL objects loaded into reg and addr passed to asl wrapper only */
/* can't be used with addr add */
#define COMLAB_STMT 11        /* stmt_t - addr of stmt for asl (sys task) */ 
#define COMLAB_XPR 12         /* expr_t - addr of xpr for asl never write */
#define COMLAB_GREF 13        /* asl wrapper ptr to gref */
#define COMLAB_GATE 14        /* asl wrapper ptr to gate (not state) */
#define COMLAB_NETADR 15      /* asl wrapper ptr to net (not value) */
#define COMLAB_CA 16          /* asl wrapper ptr to conta_t */
#define COMLAB_NPPADR 17      /* asl wrapper ptr to npp record */
#define COMLAB_DCEADR 18      /* asl wrapper ptr to dce evevnt record */

/* this is a 4 byte literal (immediate) in an insn - is therefore read only */
#define COMLAB_CINT 19        /* insn literal number */

/* things that point to read only NL object storage */ 
/* read only ptr that is local copy in mod .s file of contab value */
/* only for contab values where need a/b parts */
#define COMLAB_CONADR 20      /* area in mod's .s file - copy of contab val */ 

/* address of a procedural enter point into compiled code */
#define COMLAB_PROC_ENTER 21 /* procedual enter point */
#define COMLAB_PD_RHSBP 22   /* static memory for rhs proc blocking delay */

#define COMLAB_GATE_OUTBP 23  /* gate output value */
#define COMLAB_IDP 24         /* new idp storage area */
#define COMLAB_NCHGACTION 25  /* nchgaction storage area */
#define COMLAB_CONTA_ENTER 26 /* continuous assign enter point */
#define COMLAB_GATE_ENTER 27  /* gate backend assign enter point */
//AIV FIXME - temporary until cmos/udp/mos backend lowered
#define COMLAB_GATE_CHANGE_ENTER 28  /* address of __change_gate_outwire */
#define COMLAB_GATE_ACC_CHANGE_ENTER 29 /* address of acc_evchg_gate_outwire */
#define COMLAB_PNCHG 30       /* process nchg event */
#define COMLAB_MIPD_ENTER 31  /* mipd enter back end address */
#define COMLAB_PROCESS_WIRE_ENTER 32 /* process wire enter back end address */
#define COMLAB_TEVP 33        /* static event address */
#define COMLAB_IDPDAT 34      /* known offset from mdat_ linked in idp area */
#define COMLAB_PROC_NB_ENTER 35 /* procedual enter point for non-blocking */
#define COMLAB_TASK_ADR 36    /* task address only used for task ptr linking */
#define COMLAB_L_UDPADR 37    /* udp tab addr */
#define COMLAB_E_UDPADR 38    /* udp edge tab addr */
#define COMLAB_TCHK 39        /* timing check addr */
#define COMLAB_DEL 40         /* del base addr */

/* for debugging, object type of idp offset value (such as nva_ofs) */
#define IDPMAP_UNKN 0
#define IDPMAP_NVAOFS 1
#define IDPMAP_NCHGACTION 2
#define IDPMAP_NET_TEVP 3
#define IDPMAP_ST_TEVP 4
#define IDPMAP_CA_TEVP 5
#define IDPMAP_GP_TEVP 6
#define IDPMAP_REP_BP 7
#define IDPMAP_DCESCH_TEVS 8
#define IDPMAP_DELREP_BP 9
#define IDPMAP_PD_RHSBP 10
#define IDPMAP_NB_BP 11
#define IDPMAP_CA_DRVBP 12
#define IDPMAP_CA_SCHBP 13
#define IDPMAP_GATE_OUTBP 14
#define IDPMAP_GATEBP 15
#define IDPMAP_DCEPREV 16
#define IDPMAP_DCEEXPR_BP 17
#define IDPMAP_PNCHG 18
#define IDPMAP_ISNUM 19
/* area with both chg time and last value */
#define IDPMAP_TCHK_CHG 20
#define IDPMAP_DPFD 21

/* design wide (not in module) load net list objects */
#define NLO_NONE 0
#define NLO_NCHGED_I1 3 
#define NLO_NCHGED_I2 4
#define NLO_DELAYED_MIPD 6
#define NLO_OLDGVAL 7
#define NLO_NEWGVAL 8

#define NLO_NEWINPUTVAL 9
#define NLO_CURTHD 10
#define NLO_MASKTAB 11
#define NLO_EPAIR_TAB 12
#define NLO_EPAIR_POS_TAB 13
#define NLO_EPAIR_NEG_TAB 14
#define NLO_EPSILON 15
#define NLO_SLOTEND_ACTION 17
#define NLO_STMT_SUSPEND 18
#define NLO_THDJMP_RET_ADDR_TAB 19
#define NLO_STREN_MAP_TAB 20
#define NLO_DBGSTR 21
#define NLO_INST_INDX 22
#define NLO_IDP 23
#define NLO_CUR_TEVP 24
#define NLO_GBITREDAND 25
#define NLO_GNAND 26
#define NLO_GBITREDOR 27
#define NLO_GNOR 28
#define NLO_GBITREDXOR 29
#define NLO_GREDXNOR 30

#define NLO_ORM_2_0 32
#define NLO_ORM_2_1 33
#define NLO_ORM_2_2 34
#define NLO_ORM_2_3 35
#define NLO_ORM_3_0 36
#define NLO_ORM_3_1 37
#define NLO_ORM_3_2 38
#define NLO_ORM_3_3 39
#define NLO_ORM_4_0 40
#define NLO_ORM_4_1 41
#define NLO_ORM_4_2 42
#define NLO_ORM_4_3 43
#define NLO_GBUFVAL 44
#define NLO_GNOTVAL 45

#define NLO_BF0_STRVAL 46
#define NLO_BF0_STRONGX 47
#define NLO_BF0_HIZ 48
#define NLO_BF0_PULL0 49
#define NLO_BF0_PULL1 50
#define NLO_BF0_SUPPLY0 51
#define NLO_BF0_SUPPLY1 52
#define NLO_BF1_STRVAL 53
#define NLO_BF1_STRONGX 54
#define NLO_BF1_HIZ 55
#define NLO_BF1_PULL0 56
#define NLO_BF1_PULL1 57
#define NLO_BF1_SUPPLY0 58
#define NLO_BF1_SUPPLY1 59

#define NLO_NF0_STRVAL 60
#define NLO_NF0_STRONGX 61
#define NLO_NF0_HIZ 62
#define NLO_NF0_PULL0 63
#define NLO_NF0_PULL1 64
#define NLO_NF0_SUPPLY0 65
#define NLO_NF0_SUPPLY1 66
#define NLO_NF1_STRVAL 67
#define NLO_NF1_STRONGX 68
#define NLO_NF1_HIZ 69
#define NLO_NF1_PULL0 70
#define NLO_NF1_PULL1 71
#define NLO_NF1_SUPPLY0 72
#define NLO_NF1_SUPPLY1 73

#define NLO_NCHG_FUTEND 74
#define NLO_NCHG_FUTHDR 75

#define NLO_NEXT_NCHGLP 76
#define NLO_UDP_UVALTAB 77
#define NLO_UDP_NOZTAB 78
#define NLO_SIMTIME 79
#ifdef __CVC32__
#define NLO_SIMTIME_HIGH 80
#endif
#define NLO_PDMINDEL_ADR 81
#define NLO_PDMINDEL 82
#ifdef __CVC32__
#define NLO_PDMINDEL_HIGH 83
#endif
#define NLO_P0_TE_HDRP 84
#define NLO_P0_TE_ENDP 85
#define NLO_SBO_P1 86
#define NLO_SBO_P2 87
#define NLO_SBO_P3 88
#define NLO_SBO_P4 89

#define NLO_SBO_TIMES 90
#define NLO_SBO_DIV 91
#define NLO_SBO_MOD 92
#define NLO_SBO_BITREDAND 93
#define NLO_SBO_RELGT 94
#define NLO_SBO_RELLE 95
#define NLO_SBO_RELLT 96
#define NLO_SBO_RELCEQ 97
#define NLO_SBO_RELCNEQ 98
#define NLO_SBO_SHIFT 100

#define NLO_UN_P1 101
#define NLO_UN_P2 102
#define NLO_QCOL_COMB 104

#define NLO_SBO_NAND 105
#define NLO_SBO_NOR 106

#define NLO_G3_BITREDAND 107
#define NLO_G3_NAND 108
#define NLO_G3_BITREDOR 109
#define NLO_G3_NOR 110
#define NLO_G3_BITREDXOR 111
#define NLO_G3_REDXNOR 112

#define NLO_G4_BITREDAND 113
#define NLO_G4_NAND 114
#define NLO_G4_BITREDOR 115
#define NLO_G4_NOR 116
#define NLO_G4_BITREDXOR 117
#define NLO_G4_REDXNOR 118

#define NLO_NB_TE_ENDP 119
#define NLO_SCP_TSKP 120
#define NLO_SAVE_SCP_TSKP 121
#define NLO_4STATE_TO2 122
#define NLO_EVENT_COVER 123
#define NLO_STMT_COVER 124

#ifdef __XPROP__
#define NLO_SBO_X_BITOR 125
#define NLO_POPCOUNT_BYTE 126
#define NLO_XEDGE_SET_POS_TAB 127
#define NLO_XEDGE_SET_NEG_TAB 128
#define NLO_XEDGE_SET_TAB 129
#define NLO_IS_XEDGE_TAB 130
#define NLO_HIGH_USED NLO_IS_XEDGE_TAB
#else
#define NLO_HIGH_USED NLO_STMT_COVER
#endif


/* case generation types */
#define ICASX_UNKN 0
#define ICASX_ENDMARK 1
#define ICASX_NONXZNUM 2
#define ICASX_XZNUM 3
#define ICASX_EXPR 4
#define ICASX_COMPLEX 5       /* for now only complex is fcall */

/* instruction operand pattern classes */
#define ICLASS_UNKN 0
#define ICLASS_MOV 1
#define ICLASS_STORE 2
#define ICLASS_BIN 4
#define ICLASS_UN 5
#define ICLASS_SHFT 6
#define ICLASS_CMP 7
#define ICLASS_JMP 8
#define ICLASS_NDXJMP 9
#define ICLASS_TFJMP 10
#define ICLASS_CALL 11
#define ICLASS_SUSPEND 12
#define ICLASS_PUSH 13
#define ICLASS_POP 14
#define ICLASS_REAL_1RD 15
#define ICLASS_REAL_NORD 16
#define ICLASS_REAL_WRAX 17
#define ICLASS_ASL 18
#define ICLASS_WREDX 19
#define ICLASS_SETE 20
#define ICLASS_LABEL 21
#define ICLASS_DIR 22
#define ICLASS_DIV 23
#define ICLASS_FUNC_BRK 24
#define ICLASS_ENTER 25
#define ICLASS_DEFLST 26

/* low level X86 style virtual machine insns */
#define I_UNKN 0

/* medium level bblk world insns (pre-lowered) lowered during asm gen */
/* insns here must be expandable (contractable) using peep hole techniques */

/* only one jump allowed at end of a bblk and point to a bblk not seq no */
#define I_BBLK_JMP 1
#define I_COND_JMP 2
#define I_REAL_COND_JMP 3

/* next 2 medium level but maps with addr modes - no insn changes */
#define I_TSKJMP 4
#define I_TSKRET_JMP 5

/* boiler plate expand enter insns */
#define I_BBLK_LABEL 6
#define I_ENTER_PROC 7
#define I_ENTER_THD_RET 8
#define I_ENTER_DECL 9
#define I_ENTER_NPP 10
#define I_ENTER_CAP 11
#define I_ENTER_ICONN 12
#define I_ENTER_GATECA 13
#define I_MULTFI_SUBR 14

/* boiler plate expand exit insns */
#define I_SUSPEND 15
#define I_COMPLETE 16

/* special cases of medium level expanded in asm gen */
#define I_COPY 17

/* this is high level call with arguments at tn's - nothing returned */
#define I_CALL_ASLPROC 18
/* same as asl call medium level insn except returns result in eax */
#define I_CALL_ASLFUNC 19

#define I_PROLOGUE 20
#define I_EPILOGUE 21
/* FUD (factored use-def list variant of SSA) use-def list pseudo insn */
#define I_DEFLST 22

/* X86 cpu insns start here */
/* move isnsn */
#define I_MOVL 23
#define I_MOVZBL 24
#define I_MOVSBL 25
#define I_MOVB 26
#define I_MOVW 27
#define I_MOVZWL 28
/* load addr */
#define I_LEAL 29

#define I_STOREL 30
#define I_STOREB 31
#define I_STOREW 32

/* add/sub */
#define I_ADDL 33
#define I_SUBL 34
/* mult/div */
#define I_IMUL 35
#define I_IMULL 36
#define I_DIVL 37
#define I_SGN_DIVL 38
#define I_MODL 39
#define I_SGN_MODL 40

/* binary logical */
#define I_ANDL 41
#define I_ORL 42
#define I_XORL 44

/* shift */
#define I_SHRU 45
#define I_SARU 46
#define I_SHLL 47
#define I_SHRL 48
#define I_SALL 49
#define I_SARL 50

/* unary logical */
#define I_NOTL 51
#define I_NEGL 52

/* store CC into ah (bits 8-15) */
#define I_SAHF 53

/* compare - testl is faster for checking for 0 */
#define I_CMPL 54
#define I_CMPW 55
#define I_CMPB 56
#define I_TESTB 57
#define I_TESTL 58

/* jumps */
#define I_JMP 59
#define I_IND_JMP 60
/* really simple end of bblk jump */
#define I_FUNC_JMP 61

/* asm proc calls */
#define I_CALL 62
#define I_RETURN 63
#define I_LEAVE 64
#define I_PUSHL 65
#define I_POPL 66

/* floating point uses floating point reg stack */
#define I_FADD 67
#define I_FLD 68
#define I_FSUB 69
#define I_FMUL 70
#define I_FDIV 71
#define I_FABS 72
#define I_FLDL 73
#define I_FSTPL 74
#define I_FADDL 75
#define I_FSUBL 76
#define I_FMULL 77
#define I_FDIVL 78
#define I_FUCOMPP 79
#define I_FNSTSW 80
#define I_FCHS 81
#define I_FXCH 82
#define I_FLDZ 83

/* new for directing asm ascii output format */
#define I_ASL_CALL 84
#define I_ASL_REST_STK 85

/* misc */
/* think this clear8 edx and clears conditions codes for div? */
#define I_CLTD 86
/* set reg to 1 if zf flag 1 - after compare? */ 
#define I_SETE 87

#define I_DIRECTIVE 88
#define I_LABEL 89
#define I_ENTER_LABEL 90
//AIV FIXME - put these in proper place and renumber
#define I_ENTER_PORT 91
#define I_PORT_IND_JMP 92
#define I_ENTER_GATEDA 93
#define I_NEXT_EVENT 94
#define I_NEVENT_JMP 95
#define I_ENTER_NCHG 96
#define I_ENTER_PROCESS_NCHG 97
#define I_ENTER_MIPD 98
#define I_ENTER_TRPTH_EV 99
#define I_ENTER_WIRE_EV 100
#define I_ENTER_NB_PROC 101
#define I_ENTER_NB_PROC_FREE 102
#define I_NEXT_NCHG_EVENT 103
#define I_CALL_FREE_EVENT 104
#define I_CALL_FREE_NBMEM_EVENT 105
#define I_ADCL 106
#define I_SETNE 107
#define I_SETGE 108
#define I_SETG 109
#define I_SETLE 110
#define I_SETL 111
#define I_SETA 113
#define I_SETAE 114
#define I_SETB 115
#define I_SETBE 116
#define I_FG_CALL 117
#define I_ENTER_MDC 118

#ifdef __CVC32__

#define LAST_INSN I_ENTER_MDC

#define I_MOVA I_MOVL
#define I_STOREA I_STOREL
#define I_SUBA I_SUBL
#define I_ADDA I_ADDL
#define I_PUSHA I_PUSHL
#define I_POPA I_POPL

#define REG_NONE 0 
#define EAX 1
#define EBX 2
#define ECX 3
#define EDX 4
#define ESI 5
#define EDI 6
#define EBP 7
#define ESP 8
#define ST1 9               /* special real stack reg */

/* byte regs */
#define AL 10
#define BL 11 
#define CL 12
#define DL 13
#define SI 14
#define DI 15
#define EBP_B 16
#define ESP_b 17
/* word regs */
#define AX 18
#define BX 19 
#define CX 20 
#define DX 21 
#define HIGH_X86_REG DX

#define HIGH_GEN_REG 7       /* number of general purpose regs */
#define HIGH_BHW_REG 4       /* only low 4 regs for byte/hwrd insns */
#define HIGH_MACH_REG 9      /* X86 has 8 usable general regs */
#define NUM_ALLOCABLE_REGS 5 /* size of the alloc order table */ 
#define OFLW_REG ECX         /* reg to handle overflow spilling */
#define IDP_REG  ESI         /* the idp dedicated register */

#define AR_AX EAX
#define AR_BX EBX
#define AR_CX ECX
#define AR_DX EDX
#define AR_DI EDI
#define AR_SI ESI
#define AR_BP EBP
#define AR_SP ESP

#define MOVA_STR "movl"
#define PUSHA_STR "pushl"
#define SUBA_STR "subl"
#define POPA_STR "popl"
#define ANDA_STR "andl"
#define XORA_STR "xorl"
#define ADDA_STR "addl"
#define TESTA_STR "testl"
#define AW_STR "long"
#define CMPA_STR "cmpl"
#define ASM_WORD_STR ".long"
#define GBL_OFS_STR ""

#else

#define I_MOVQ 119
#define I_STOREQ 120
#define I_SUBQ 121
#define I_ADDQ 122
#define I_PUSHQ 123
#define I_POPQ 124
/* AIV 11/12/08 - these are special case real insns */
#define I_LDR1 125
#define I_LDR2 126
#define I_LDR3 127
#define I_LDR4 128
#define I_LDR5 129
#define I_LDR6 130
#define I_LDR7 131
#define I_LDR8 132
#define I_LDR9 133
#define I_LDR10 134
#define I_LDR11 135
#define I_LDR12 136
#define I_LDR13 137
#define I_LDR14 138
#define I_LDR15 139
#define I_LDR16 140
#define I_STREAL 141
#define I_XORSREAL 142
#define I_XORNREAL 143
#define I_ANDAREAL 144
#define I_LDEPSILON 145
#define I_LDRABS 146
#define I_LDRNEG 147
#define I_MOVABSQ 148
/* AIV 08/03/10 - added special insn to do a 4 byte movl on 64-bit */
#define I_MOVSLQ 149
#define I_MOVQL 150
#define I_STOREQL 151

#define LAST_INSN I_STOREQL

#define I_MOVA I_MOVQ
#define I_STOREA I_STOREQ
#define I_SUBA I_SUBQ
#define I_ADDA I_ADDQ
#define I_POPA I_POPQ
#define I_PUSHA I_PUSHQ


#define REG_NONE 0 
#define EAX 1
#define EBX 2
#define ECX 3
#define EDX 4
#define ESI 5
#define EDI 6
#define RAX 7
#define RBX 8
#define RCX 9
#define RDX 10
#define RSI 11
#define RDI 12
#define R8 13
#define R9 14
#define R10 15
#define R11 16
#define R12 17
#define R13 18
#define R14 19
#define R15 20
#define RBP 21
#define RSP 22
#define ST1 23              /* special real stack reg */

/* byte regs */
#define AL 24
#define BL 25
#define CL 26
#define DL 27
#define SI 28
#define DI 29
#define R8B 30
#define R9B 31
#define R10B 32
#define R11B 33
#define R12B 34
#define R13B 35
#define R14B 36
#define R15B 37

#define EBP_B 38
#define ESP_b 39
/* word regs */
#define AX 40
#define BX 41
#define CX 42
#define DX 43
#define R8W 44
#define R9W 45
#define R10W 46
#define R11W 47
#define R12W 48
#define R13W 49
#define R14W 50
#define R15W 51

/* AIV64 - FIXME - not using movl insn so not using these regs for now */
#define R8D 52
#define R9D 53
#define R10D 54
#define R11D 55
#define R12D 56
#define R13D 57
#define R14D 58
#define R15D 59

#define HIGH_X86_REG R15D

#define HIGH_GEN_REG 21       /* number of general purpose regs */
#define HIGH_BHW_REG 4       /* only low 4 regs for byte/hwrd insns */
#define HIGH_MACH_REG 23     /* X86 has 8 usable general regs */
#define NUM_ALLOCABLE_REGS 5 /* size of the alloc order table */ 
#define OFLW_REG RCX         /* reg to handle overflow spilling */
#define IDP_REG  R15         /* the idp dedicated register */

#define AR_AX RAX
#define AR_BX RBX
#define AR_CX RCX
#define AR_DX RDX
#define AR_DI RDI
#define AR_SI RSI
#define AR_BP RBP
#define AR_SP RSP

#define PASS_REG1 RDI
#define PASS_REG2 RSI
#define PASS_REG3 RDX
#define PASS_REG4 RCX
#define PASS_REG5 R8
#define PASS_REG6 R9

#define MOVA_STR "movq"
#define PUSHA_STR "pushq"
#define SUBA_STR "subq"
#define POPA_STR "popq"
#define ANDA_STR "andq"
#define XORA_STR "xorq"
#define ADDA_STR "addq"
#define TESTA_STR "testq"
#define CMPA_STR "cmpq"

#define AW_STR "quad"
#define ASM_WORD_STR ".quad"

#define GBL_OFS_STR "(%rip)"

extern int32 __passed_regs_order[6];
#endif


/* types of illegal X86 two memory ref fixup patterns */
#define MR2_UNKN 0
#define MR2_SPILL_SPILL 1
#define MR2_SPILL_SPILLNDX 2
#define MR2_SPILL_X86NDX 3
#define MR2_SPILLNDX_SPILL 4
#define MR2_X86NDX_SPILL 5
#define MR2_SPILLNDX_SPILLNDX 6
#define MR2_SPILLNDX_X86NDX 7
#define MR2_X86NDX_SPILLNDX 8
#define MR2_X86NDX_X86NDX 9
#define MR2_SPILL_SPILL_NOMEM 10

/* insn sizes */
#define SIZ_NONE 0
#define SIZ_B 1
#define SIZ_BL 2
#define SIZ_W 3
#define SIZ_WL 4
#define SIZ_L 5
#define SIZ_D 6          
/* AIV 08/03/10 - added special sizes to do a 4 byte movls on 64-bit */
#define SIZ_QL 7
#define SIZ_LL 8

/* Jump CC types - now one jmp insn and pass cc to asm gen */
#define CC_UNKN 0
#define CC_NONE 1             /* for unconditional jump */
#define CC_JE 2
#define CC_JNE 3
#define CC_JZ 4
#define CC_JNZ 5
#define CC_JGE 6
#define CC_JGT 7
#define CC_JLE 8
#define CC_JLT 9
#define CC_JNS 10
#define CC_JP 11
#define CC_JRZ 12
#define CC_JA 13
#define CC_JB 14
#define CC_JAE 15
#define CC_JBE 16

#define IGEN_UNKN 0
#define IGEN_PROC 1
#define IGEN_DCE 2
#define IGEN_NPP 3       

/* defines for tracing flow graphs and basic blocks */
#define IGEN_UNKN 0
#define IGEN_PROC 1
#define IGEN_DCE 2
#define IGEN_NPP 3            /* for nets only npp igen since combined */

/* asm related defines */
 /* FIXME - must make tmp available for release ??? */
#define DEF_OBJ_DIR "/tmp"
#define DEF_EXE_NAME "cvcsim"
#define RUNTIME_MAKEFILE "makefile.modules"

/* return types for asm lib (asl) routines */
#define RE_UNKN 0
#define RE_VOID 1
#define RE_INT 2
#define RE_PTR 3
#define RE_BYTE 4
#define RE_DBLE 5

/* routine argument types for asm lib (asl) routines */
/* notice using default c initializer so unknown must be value 0 */ 
#define A_UNKN 0
#define A_INT 1
#define A_RPTR 2
#define A_WPTR 3
#define A_RWPTR 4
#define A_DBLE 5
#define A_NUM 6              /* arg is an literal num (usually a width) */ 

/* num for every asm lib (asl_) rt support routine - needed for reg assign */
#define ASL_GET_UPREL_IDP 3
#define ASL_GET_DOWNREL_IDP 4
#define ASL_SCHED_PROC_DELAY 8
#define ASL_ARM_ECTRL 9
#define ASL_SETSAV_ASSOC_TSK 14
#define ASL_ARM_NB_ECTRL 22
#define ASL_SCHED_NBRHS_DCTRL 30
#define ASL_SCHED_NAMBLK_THD 35
#define ASL_SCHED_FORK 36
#define ASL_EXEC_STSK 37
#define ASL_REG_QCAF_INHIBIT 38
#define ASL_SCALAR_WIRE_INHIBIT 40
#define ASL_BSEL_WIRFRC_INHIBIT 41
#define ASL_STREN_CORRECT_FRC 42
#define ASL_CORRECT_FRC 43
#define ASL_PSEL_CORRECT_FRC 44
#define ASL_STREN_PSEL_CORRECT_FRC 45
#define ASL_JMP_EQ_STMASK 48
#define ASL_TRIGGER_ECTRL 49
#define ASL_FMONIT_TRIGGER 50
#define ASL_ASSIGN_QCAF 51
#define ASL_MOVABW_FR_SVEC 54
#define ASL_MOVSB_FR_WSTAD 55
#define ASL_MOVSB_FR_WIDESTAD 56
#define ASL_MOVSB_FR_SCALSTAD 57
#define ASL_MOVR_FR_W 58
#define ASL_MOVR_FR_SGNW 59
#define ASL_MOVW_FR_R 60
#define ASL_EXEC_SYSFUNC 61
#define ASL_WIDCAS_EVAL 62
#define ASL_WIDCASX_EVAL 63
#define ASL_WIDCASZ_EVAL 64
#define ASL_WIDE_BITXOR 69
#define ASL_WIDE_NOTL 70
#define ASL_WIDE_BITAND 71
#define ASL_WIDE_REDXOR 72
#define ASL_WID_BIN_BITXNOR 73
#define ASL_WID_BIN_BITOR 74
#define ASL_WID_UN_REDOR 75
#define ASL_WID_UNBITNOT 76
#define ASL_WIDE_BITOR 77
#define ASL_WIDE_RSHIFT 78
#define ASL_WIDE_LSHIFT 79
#define ASL_WIDOMITXZ_NE 80
#define ASL_SGNMASK 82
#define ASL_SETUP_TASK_THD 85
#define ASL_TSKDONE_CLEANUP_RET 86
#define ASL_WIDE_CMP 88
#define ASL_SGN_WIDE_CMP 89
#define ASL_WIDE_WORD_CMP 90
#define ASL_WIDE_SGNWORD_CMP 91
#define ASL_WIDE_JMPOR_0 92
#define ASL_WIDE_JMP_EQ 93
#define ASL_EXEC_CAUSE 96
#define ASL_REPCNT_JMP 97
#define ASL_WIDE_ANY1 99
#define ASL_WIDE_QCOL_COMB_OPANDS 100
#define ASL_SGNBIT_ON 102
#define ASL_SET_BYTEVAL 107
#define ASL_EXEC_WIDE_LOGIC_GATE 112
#define ASL_SCHED_VEC_MIPD_BIT 114
#define ASL_SCHD_CAEV 120
#define ASL_CANCEL_EV 122
#define ASL_CALC_BUFIF_NEWSTATE 123
#define ASL_SET_RHS_NEW_GATEVAL 126
#define ASL_EVAL_CMOS_GATE 127
#define ASL_EVAL_RCMOS_GATE 128
#define ASL_STREN_SCHD_1GEV 131
#define ASL_SCHD_1GEV 132
#define ASL_CANCELE_PEND_NOCHG_1GEV 133
#define ASL_CHG_GATE_OUTWIRE 134
#define ASL_CANCELE_PEND_CHG_1GEV 135
#define ASL_PEND_NOCHG_1GEV 137
#define ASL_STREN_PEND_CHG_1GEV 138
#define ASL_PEND_CHG_1GEV 139
#define ASL_RESCHD_CAEV 141
#define ASL_EVAL_TRAN_DRVRS 144
#define ASL_ADJUST_TRIREG 145
#define ASL_LD_TFRWARG_DRVP 146
#define ASL_GET_PERINST_VAL 147
#define ASL_STREN_SCHED_UNKNOWN_BIT 150
#define ASL_SCHED_UNKNOWN_BIT 151
#define ASL_BYTECMP 152
#define ASL_EVAL_NMOS_GATE 155
#define ASL_EVAL_RNMOS_GATE 156
#define ASL_EVAL_PMOS_GATE 157
#define ASL_EVAL_RPMOS_GATE 158
#define ASL_CP_SOFS_WVAL 159
#define ASL_LHSPSEL 160
#define ASL_LSUB 161
#define ASL_LADD 162
#define ASL_LMULT 163
#define ASL_SGN_LMULT 164
#define ASL_SGN_LDIVMOD 165
#define ASL_LDIVMOD 166
#define ASL_WRD_REDXOR 167
#define ASL_WIDE_VVAL_IS0 168
#define ASL_VVAL_IS1 169
#define ASL_CVT_LNGBOOL 170
#define ASL_EXEC_QC_ASSIGN 171
#define ASL_EXEC_QC_FORCE 172
#define ASL_EXEC_QC_WIREFORCE 173
#define ASL_EXEC_QC_DEASSIGN 174
#define ASL_EXEC_QC_WIRERELEASE 175
#define ASL_EXEC_DISABLE 176
#define ASL_EVAL_TRANIF_LD 178
#define ASL_WDEL_SCHD_1WIREBIT 182
#define ASL_EVAL_STWIRE 183
#define ASL_EVAL_WIDE_WIRE 185
#define ASL_ADD_SELECT_NCHGLST_EL 188
#define ASL_ADD_DMPV_CHGLST_EL 189
#define ASL_MEMCPY 190
#define ASL_MY_MEMSET 191
#define ASL_COMB_1BITSTS 193
#define ASL_SGN_XTND_WIDEN 194

//AIV NEW CONSTANT DELAY WRAPPERS START HERE
#define ASL_SCHED_PROC_DELAY_CONST 195
#define ASL_SCHED_PROC_DELAY_PND0 197
#define ASL_SCHED_NBRHS_DCTRL_CONST 198
#define ASL_SCHD_CAEV_CONST 201
#define ASL_SCHD_CAEV_CONST0 203
#define ASL_RESCHD_CAEV_CONST 204
#define ASL_WORDCMP 207
//AIV NEW PLI WRAPPERS
#define ASL_CHK_DCE_CBVC 208 
#define ASL_CHK_LD_VPIPUTV_DRIVER 209
#define ASL_CHK_GATE_VPI_CHG 210
//AIV NEW 1 NONSTREN WIRE TYPE EVALS
#define ASL_EVAL_1W_NONSTREN_WIRE 211
#define ASL_EVAL_1W_NONSTREN_WIRE_AND 212
#define ASL_EVAL_1W_NONSTREN_WIRE_OR 213
#define ASL_EVAL_WIDE_WIRE_AND 214
#define ASL_EVAL_WIDE_WIRE_OR 215
#define ASL_BBLK_DBG_MSG 216
#define ASL_MOVABW_ONEW_FR_SVEC 217
#define ASL_WIDE_POWER 218
#define ASL_WIDE_SGN_POWER 219
#define ASL_REAL_POW_FUNC 220
#define ASL_BLD_NB_NODELAY_TEV 221
#define ASL_NB_TRIGGER_ECTRL 222
#define ASL_DOWNREL_TARG_TO_REF 227
#define ASL_UPREL_TARG_TO_REF 228
#define ASL_SCHD_NB_VARDEL_RHSCONST_DCTRL 229
#define ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST 230
#define ASL_SCHED_NBRHS_SCALAR_DCTRL 232
#define ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST 233
#define ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST 235
#define ASL_SCHED_NBRHS_VARNDX_DCTRL 237
#define ASL_ARM_NB_VARNDX_ECTRL 238
#define ASL_SCHED_NB_PND0_LHS_VARNDX 239
#define ASL_RHS_CONTA_STREN 241
#define ASL_SCHED_SCALAR_MIPD_PATH 243
#define ASL_SCHED_SCALAR_MIPD_16V 244
#define ASL_SCHED_SCALAR_MIPD_IS16V 245
#define ASL_SCHED_SCALAR_MIPD_IS16V1 246
#define ASL_SCHED_SCALAR_MIPD_IS16V2 247
#define ASL_SCHED_SCALAR_MIPD_IS1V 248
#define ASL_SCHED_SCALAR_MIPD_PND0 249
#define ASL_SCHED_SCALAR_MIPD_CONST 250
#define ASL_SCHD_SCALAR_1PTHWIREBIT 252
#define ASL_SCHD_ST_SCALAR_1PTHWIREBIT 253
#define ASL_SCHD_1PTHWIREBIT 254
#define ASL_SCHD_ST_1PTHWIREBIT 255
//AIV NEW NO THRD DELAY EVENTS
#define ASL_SCHED_PROC_DELAY_NT 265
#define ASL_SCHED_PROC_DELAY_CONST_NT 266
#define ASL_SCHED_PROC_DELAY_PND0_NT 268
#define ASL_LD_LOGIC_WIDE_DRIVER 273
#define ASL_ADD_STATIC_NCHG_SEL 282
#define ASL_PROCESS_MIPD_NCHG 283
#define ASL_PROCESS_SCAL_MIPD_NCHG 284
#define ASL_SCHD_1GEV_CONST 293
#define ASL_SCHD_1GEV_PND0 294
#define ASL_SCHED_PROC_DELAY_TASK_CONST 296
#define ASL_SCHED_PROC_DELAY_TASK_PND0 297
#define ASL_UPDATE_TRAN_HARDDRVS 298
#define ASL_EVAL_HTRAN_WIRE_1BIT 300
#define ASL_EVAL_HTRAN_WIRE_1BIT_NCHG 301
#define ASL_EVAL_HTRAN_STWIRE_1BIT 302
#define ASL_EVAL_HTRAN_STWIRE_1BIT_NCHG 303
#define ASL_EVAL_TRAN_SCALAR_BIDCHAN_1BIT 304
#define ASL_EVAL_TRAN_BIDCHAN_1BIT 305
#define ASL_EVAL_TRAN_STBIDCHAN_1BIT 306
#define ASL_QC_ACTIVE 307
#define ASL_EXEC_QC_TRAN_WIREFORCE 308
#define ASL_EXEC_QC_TRAN_WIRERELEASE 309
#define ASL_EXEC_QC_DEASSIGN_FORCE 310
#define ASL_ASSIGN_QCAF_REGFORM 311
#define ASL_ASSIGN_SCALAR_QCAF 312
#define ASL_TRAN_ADDR 313
#define ASL_STREN_SCHD_BIDPTHDRVRS 314
#define ASL_SCHD_BIDPTHDRVRS 315
#define ASL_SCHD_SCALAR_BIDPTHDRVRS 316
#define ASL_STORE_BIDPTHDRVRS 317
#define ASL_TRPATH_SCALAR_STORE 318
#define ASL_TRPATH_STORE 319
#define ASL_IMMED_EVAL_TRIFCHAN 320
#define ASL_WDEL_TRIREG_SCHED_HIZ 321
#define ASL_UDP_WIDE_ADJSTATE 322
#define ASL_FORCE_ACTIVE 323
#define ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_CONCAT 324
#define ASL_SCHED_NBRHS_VARNDX_DCTRL_CONCAT 325
#define ASL_SCHED_NB_PND0_LHS_VARNDX_CONCAT 326
#define ASL_SCHD_SCALAR_1WEV 329
#define ASL_RESCHD_1WEV 330
#define ASL_GET_DEL_1X 331
#define ASL_GET_DEL_4X 332
#define ASL_SCHD_1PTHWIREBIT_NOMSG 333
#define ASL_SCHD_1WEV 334
#define ASL_TIMING_CHECK_RECORD 335
#define ASL_RANDOM_WITH_SEED 336
#define ASL_RANDOM 337
#define ASL_RHS_PSEL 339
#define ASL_RHS_PSEL_WIDE 340
#define ASL_RHS_ST_PSEL 341
#define ASL_JMP_EQ_WIDE_VARMASK 342
#define ASL_ADD_DMPP_CHGLST_EL 343
#define ASL_WIDE_CMP_NEQ 344
#define ASL_WIDE_CMP_EQ 345
#define ASL_EXEC_DISPLAY 346
#define ASL_PEND_CHG_1GEV_CONST 347
#define ASL_ADD_DMPP_CHGLST_EL_MDPRT 349
#define ASL_ADD_DMPV_CHGLST_EL_MDPRT 350
#define ASL_MDPRT_BSEL 351
#define ASL_MDPRT_BSEL_NCHG 352
#define ASL_MDPRT_BSEL_1W 353
#define ASL_MDPRT_BSEL_NCHG_1W 354
#define ASL_MDPRT_BSEL_DMPP 355
#define ASL_MDPRT_BSEL_NCHG_DMPP 356
#define ASL_MDPRT_BSEL_1W_DMPP 357
#define ASL_MDPRT_BSEL_NCHG_1W_DMPP 358
#define ASL_MDPRT_BSEL_DMPV 359
#define ASL_MDPRT_BSEL_NCHG_DMPV 360
#define ASL_MDPRT_BSEL_1W_DMPV 361
#define ASL_MDPRT_BSEL_NCHG_1W_DMPV 362
#define ASL_SCHED_NBRHS_DCTRL_CONST_T 363
#define ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST_T 364
#define ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST_T 365
#define ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_T 366
#define ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_CONCAT_T 367
#define ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST_LAST 368
#define ASL_SCHED_NBRHS_DCTRL_CONST_LAST 369
#define ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST_LAST 370
#define ASL_NEW_AUTO_IDP_AREA 371
#define ASL_CP_AUTO_IDP_AREA_FUNC 372
#define ASL_SETUP_TASK_THD_AUTO 373
#define ASL_TSKDONE_CLEANUP_RET_AUTO 374
#define ASL_THREAD_AUTO_CLEANUP 375
#define ASL_ADD_DMPV_CHGLST_EL_ARRAY 376
#define ASL_4STATE_TO_2STATE_WIDE 377
#define ASL_SGN_XTND_WIDEN_2STATE 378
#define ASL_RHS_PSEL_2STATE 379
#define ASL_RHS_PSEL_WIDE_2STATE 380
#define ASL_MOVW_FR_R_2STATE 381
#define ASL_WIDE_SGN_POWER_2STATE 382
#define ASL_WID_BIN_BITXNOR_2STATE 383
#define ASL_WID_UNBITNOT_2STATE 384
#define ASL_COS 385
#define ASL_SIN 386
#define ASL_TAN 387
#define ASL_CEIL 389
#define ASL_FLOOR 390
#define ASL_ACOS 391
#define ASL_ASIN 392
#define ASL_ATAN 393
#define ASL_COSH 394
#define ASL_SINH 395
#define ASL_TANH 396
#define ASL_ACOSH 397
#define ASL_ASINH 398
#define ASL_ATANH 399
#define ASL_LN 400 
#define ASL_LOG10 401
#define ASL_ABS 402
#define ASL_SQRT 403
#define ASL_EXP 404
#define ASL_ADD_TOGGLELST_EL 406
#define ASL_ADD_TOGGLELST_EL_PORT 407
/* SV wrappers from here down */
#define ASL_ST_STRING_CONST 408
#define ASL_ST_STRING_VAR 409
#define ASL_ST_STRING_RHSX 410
#define ASL_STRING_BINOP 411
#define ASL_ST_STRING_BYTE 412
#define ASL_ST_STRING_ARRAY_CONST 413
#define ASL_ST_STRING_ARRAY_VAR 414
#define ASL_ST_STRING_ARRAY_RHSX 415
#define ASL_GET_STRING_BYTE 416
#define ASL_SV_DPI_STRING 417
#define ASL_SV_DPI_STRING_STORE 418
#define ASL_SCHED_NBRHS_VARNDX_DCTRL_SEL_CONST 419
#define ASL_SCHED_NBRHS_VARNDX_SEL_DCTRL 420
#define ASL_SCHED_NB_PND0_LHS_VARNDX_SEL 421
#define ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_SEL_T 422
#define ASL_ASSIGN_QCAF_REGFORM_CONCAT 423
#define ASL_ASSIGN_QCAF_CONCAT 424
#define ASL_REAL_DIV0_WARNING 425
#define ASL_EXEC_SYSFUNC_STMTLOC 426
#define ASL_REAL_QCOL_WARNING 427
#define ASL_EVAL_TRAN_BIDCHAN_1BIT_ASSIGN 428
#define ASL_EVAL_TRAN_STBIDCHAN_1BIT_ASSIGN 429
#define ASL_EVAL_TRAN_DRVRS_VECTOR 430
#define ASL_EVAL_TRAN_BIDCHAN_VECTORED_ASSIGN 431
#define ASL_EVAL_TRAN_STBIDCHAN_VECTORED_ASSIGN 432
#define ASL_POP_XSTK 433
#define ASL_EXEC_QC_WIREFORCE_CONCAT 434
#define ASL_EXEC_QC_TRAN_WIRERELEASE_CONCAT 435
#define ASL_EXEC_QC_WIRERELEASE_CONCAT 436
#define ASL_EXEC_QC_ASSIGN_CONCAT 437
#define ASL_EXEC_QC_FORCE_CONCAT 438
#define ASL_EXEC_QC_DEASSIGN_FORCE_CONCAT 439
#define ASL_EXEC_QC_DEASSIGN_CONCAT 440
#define ASL_EXEC_QC_TRAN_WIREFORCE_CONCAT 441

#ifdef __XPROP__
#define ASL_WID_BIN_BITOR_X 443
#define ASL_WID_UN_REDOR_X 444
#define ASL_GET_XPROP_ACCUM 445
#define ASL_SET_XPROP_ACCUM_INIT 446
#define ASL_SET_XPROP_ACCUM_INIT_WIDE 447
#define ASL_PER_BIT_XPROP_ACCUM 448
#define ASL_STMT_ASSIGN_TO_ACCUM_WIDE 449
#define ASL_STMT_ASSIGN_TO_ACCUM_1W 450
#define ASL_SET_XPROP_ACCUM_BLOCK_CASE 451
#define ASL_SET_RESTORE_XPROP_ACCUM_BLOCK 452
#define ASL_SET_RESTORE_XPROP_ACCUM_BLOCK_NODEFAULT 453
#define ASL_TRACE_XPROP_WRITE 454
#define ASL_TRACE_XPROP_WRITE_WIDE 455
#define ASL_POPCOUNT_1W 456
#define ASL_POPCOUNT_WIDE 457
#define ASL_XPROP_CHECK_CASE_NET_SET 458
#define ASL_TRIGGER_ECTRL_XPROP 459
#define ASL_HAS_XEDGE_WIDE 460
#define ASL_HAS_XEDGE_WIDE_ST 461
#define ASL_XPROP_ACCUM_TO_SELF 462
#define ASL_XPROP_ACCUM_TO_SELF_WIDE 463
#define ASL_XPROP_XEDGE_NET 464
#define ASL_XPROP_SET_XEDGE_NET 465
#define ASL_SET_RESTORE_XPROP_ACCUM_TOSELF 466
#define ASL_SET_XPROP_ACCUM_BLOCK_IF 467
#define ASL_STMT_ASSIGN_TO_ACCUM_1W_IF_ID 468
#define ASL_STMT_ASSIGN_TO_ACCUM_1W_CASE_ID 469
#define ASL_STMT_ASSIGN_TO_ACCUM_WIDE_IF_ID 470
#define ASL_STMT_ASSIGN_TO_ACCUM_WIDE_CASE_ID 471
#endif

#define ASL_MISC_TERR 472

/* AIV - new wrapper calls for tev_t events */
#define WRAPPER_NONE 0
#define WRAPPER_PROCESS_THRD_EV 1
#define WRAPPER_NPBA_VARNDX_CONCAT_EV 2

/* AIV 11/10/09 - this just needs to be > 1 - to tell gen_expr_val */
/* that want a vector not a scalar if possible */
/* only used for bsel eval expr */
#define WANT_A_VEC 2

/* struct for lists of basic blocks */
struct bblklst_t {
 struct bblk_t *bl_bbp;
 struct bblklst_t *bl_prev;
 struct bblklst_t *bl_nxt;
};

/* separate flow graph for every init/always, task and func in mod */
struct flowg_t {
 unsigned flowgtyp : 8;
 unsigned fg_remove : 1;      /* T => mark for linking out */
 unsigned uses_idp : 1;       /* T => uses accesses __idp storage area */
 unsigned do_not_load_idp : 1;/* T => do not use dedicated reg for idp */
 unsigned has_overflow : 1;   /* T => has overflow tmps */
 unsigned uses_ebx : 1;       /* T => uses %ebx in xjmp region */
 unsigned uses_ebp : 1;       /* T => uses %ebp in xjmp region */
#ifdef __CVC32__
 unsigned uses_edi : 1;       /* T => uses %edi in xjmp region */
 unsigned uses_esi : 1;       /* T => uses %esi in xjmp region */
#else
 unsigned uses_r12 : 1;       /* T => uses r12 in fg */
 unsigned uses_r13 : 1;       /* T => uses r12 in fg */
 unsigned uses_r14 : 1;       /* T => uses r12 in fg */
 unsigned uses_r15 : 1;       /* T => uses r12 in fg */
 unsigned has_real_ops : 1;   /* T => flowgraph uses special xmm regs */
#endif
 unsigned has_nb_pnd0s : 1;   /* T => fg is nb which checks if pnd0 */
 unsigned is_nb : 1;          /* T => fg is nb */
 unsigned is_nb_free : 1;     /* T => nb has free version */
 unsigned is_nb_rhs_mem : 1;  /* T => fg is nb with possible malloc mem */
 unsigned has_thread_ctrl : 1; /* T => has thread entered from stp->enterptr */
 unsigned optim_scalar_port : 1; /* T => has optimized scalar port */
 int32 max_call_args;         /* max num args passed to call */
 int32 max_dpi_wrds;          /* max num args (wrds) passed to dpi call */
 int32 fg_num_bblks;          /* number of bblks in flow graph */ 
 int32 ebp_wrd_area_siz;      /* size of flow graph stk spill area in wrds */ 
 word32 fg_seqno;             /* number to identify flowg */
 struct bblk_t *fg_bblks;     /* list of bblks in fg in alloc order */
 struct bblk_t *fg_bblkend;   /* end of fg alloc order bblk list */
 struct bblklst_t *enter_bblks;/* list of entry (jump to and AFS) bblks */
 struct avlhd_t *fg_tn_ref_tree;/* tree of tmps refed (use or def) in flowg */
 struct net_t *optim_port_np; /* optimize port net for fixed style fg */
#ifdef __VALTRK__
 int32 *predoms;              /* predominator tree stored as array */
#endif
 struct insn_t *fg_ihd;       /* machine insn list head for this fg */
 struct insn_t *fg_itail;     /* and machine list tail */
 struct flowg_t *flowgnxt;
};

struct bbedge_t {
 struct bblk_t *eblkp;
 struct bbedge_t *bbenxt;
};

/* basic block always ends with jump so v insn contains up to 2 nxt links */
struct bblk_t {
 unsigned after_suspend : 1;  /* T => entry bblk after suspend */
 unsigned afs_reachable : 1;  /* T => reachable from some AFS bblk if fg */
 unsigned deflst_processed : 1;/* T => already processed for current tn */
 unsigned deflst_added : 1;   /* T => phi already added for current tn */
 unsigned is_xz : 1;          /* T => block is x/z block */
 unsigned is_enter_loop : 1;  /* T => block is loop enter  */
 unsigned mark_for_rm : 1;    /* T => block is marked for rm  */
 unsigned in_list : 1;        /* T => block is in list  */
 unsigned is_casejmp_item : 1;   /* T => block is jmp case item  */

 int32 mark;                  /* work number for marking */
 int32 revpostordno;          /* this bblks reverse post order num in flowg */
 int32 bblk_seqno;

 struct bbedge_t *bbe_prev;   /* list of basic blk predecesor edges */
#ifdef __VALTRK__
 struct bblklst_t *predom_frontiers;/* predom frontier's list */
 struct bblklst_t *bblk_pdoms;/* list of bblks predominated by this bblk */
#endif

 struct insn_t *ihd;          /* one bblks' machine insn list head */
 struct insn_t *itail;        /* and its tail */
 struct bblk_t *bbnxt;        /* alloc order list of bblk in flowg */
 struct bblk_t *bbprev;       /* alloc order list of bblk in flowg */
};

union ifrom_u {
 struct st_t *from_stp;     /* statement insn from */ 
 struct net_t *from_np;     /* net insn from */
 struct conta_t *from_cap;  /* conta insn from */
 int32 from_iconn;          /* from iconn ndx */
 int32 from_mdprt;          /* from mdprt */
 int32 from_gateca;         /* from gate scalar conta ndx */
 int32 from_gateda;         /* from gate back end delay assign */
};

/* AIV 06/02/09 - made this a union to save space */
union am_ptr_u {
 char *labnam;
 struct bblk_t *bbp;
};

/* src and dst insn operand description - adrmode determines which used */
struct amode_t {
 unsigned amode : 8;
 unsigned scale : 3;          /* scale - 0 for none, 1=2x, 2= 4x, 3=8x */ 
 unsigned x86_regno : 6;      /* x86 reg num if used */
 unsigned arr_base_nlo: 8;    /* for glb nlo array indexing the NLO number */
 unsigned is_labnam : 1;      /* union apu is a label string */ 
#ifndef __CVC32__
 unsigned is_large_label : 1; /* is large model label */ 
#endif
 int32 am_tni;                /* reg tmp name index */
 size_t disp;                   /* byte offset (above) within tmp name area */
 union am_ptr_u apu;          /* union for either labnam or bbp */
};

/* info for a special case index jump insn */
struct ndxjmp_t {
 int32 has_duplicates;         /* T => if jump table can have duplicates */
 int32 jtabstart;              /* start of first block */
 int32 jtabsiz;                /* number of blocks in table */
 struct bblk_t **bbtab;        /* jump to blocks */
};

/* record for each asl routine arg the defining insn (nil if none) */ 
struct asl_def_t {
 struct amode_t am_arg;
 struct insn_t **arg_src_defips;
 struct insn_t **arg_savchain_ips;
};

/* union for indexed jump and medium leval asl call insn extra info */
union i_extrainfo_u {
 struct ndxjmp_t *ndxjp;      /* ndx jmp pointer info if is a ndx jmp */
 struct defilst_t *defilst;   /* lst of live defs that can reach deflst insn */
 struct asl_def_t *asl_ausedefs; /* tab of asl opand usedef and tn records */
 int32 prologue_bblkno;       /* for prologue pseudo insn, entry bblk num */
};

/* per insn record for build and tracing factored use-def (FUD) lists */
struct iusedef_t {
 int32 trk_nbytes;            /* number of bytes in tracked area */
 word32 *ip_trk_valp;         /* insn tracked out (result) value */
 struct insn_t *isrc_defip;   /* if src is a tn ref, insn that defines it */
 struct insn_t *idst_defip;   /* if dst is a tn ref, insn that defines it */
 struct insn_t *savchain_ip;  /* for tn define or deflst insn, previous def */
};

/* list of tmps stored as an array - index by insn number */
/* used for register assign tn conflict graphs */
struct tn_list_t {
 int32 size;         /* size of values */
 int32 ndx;          /* current index into values */
 int32 *values;      /* actual values */
};

struct reg_alloc_t {
 struct tn_list_t *tn_use_lst;/* regs used in this insn */ 
 struct tn_list_t *tn_def_lst;/* regs def in this insn */ 
 struct tn_list_t *tn_in_lst; /* regs used coming into this insn */ 
 struct tn_list_t *tn_out_lst;/* regs used leaving this insn */ 
};

/* saved register allocation information for multiple pass assignment */
struct reg_alloc_info_t {
 unsigned tn_spilled : 1;     /* T => this tmp name is spilled - wide always */
 unsigned tn_assigned : 1;    /* T => tn assigned to reg for this flowg */
 unsigned t_used_cross_call : 1; /* T => used across a call */
 unsigned t_used_in_bw_insn : 1; /* T => used in a byte or half word insn */
 unsigned x86_regno : 6;      /* the x86 regno this tmp lowers to */
 int32 spill_ebp_byt_ofs;     /* for spill wrd and all wid, ebp ofs in bytes */
 int32 tn_coalesce_into;      /* for colalescing - tni that replaces */
 struct tn_list_t *tn_adj_lst; /* tmps adjacent to this one */ 
};

struct reg_prty_t {
 int32 priority;
 int32 tni;
};

/* union for optmization records free while insn needs to stay around still */
union optim_u {
 struct iusedef_t *fudp;      /* ptrs to use <bblk, insn> or deflst insn */
 struct reg_alloc_t *rap;     /* record for reg allocator live in/outs */  
};

/* virtual machine insn - later lowered so easily maps to cpu insn */
struct insn_t { 
 unsigned opcod : 16;         /* high level vm insn op code */
 unsigned is_store : 1;       /* is a store insn */
 unsigned jmptyp : 6;         /* this is just the condition code (cc) */
 unsigned callasl_argnum : 4; /* for unlowered asl calls, number of args */
 unsigned sgn_jmp : 1;        /* T if jump is signed (chks SF flag) */
 unsigned is_coal_out : 1;    /* linkout coal move for 1st reg pass */ 
 unsigned is_coal_out2 : 1;   /* linkout coal move for 2nd reg pass */ 
 unsigned is_dpi_enter : 1;   /* T => is dpi enter insn */
 unsigned is_export_stack : 1; /* export DPI task arg on stack */
#ifndef __CVC32__
 unsigned is_large_ofs : 1;   /* is large model idp ofs insn */ 
#endif
#ifdef __VALTRK__
 unsigned trk_later_del : 1;  /* T => in trk removal, must mark before del */
 unsigned symb_res_val : 2;   /* symbolic result value - including unkn */
#endif
 int32 res_tni;               /* original risc vm insns can be 3 addr */
 int32 ndx;                   /* insn index (identifier) */

 struct amode_t isrc;         /* src addressing mode */
 struct amode_t idst;         /* dest. addressing mode */
 union i_extrainfo_u extrau;  /* for special case insns ptr to extra info */
#ifdef __CVC_DEBUG__
 /* AIV 06/17/09 - only need this for debug messages */
 union ifrom_u ifru;          /* nl object .v file insn gened from */
 struct mod_t *inmdp;         /* module then isns was generated */
#endif
 struct insn_t *inxt;
 struct insn_t *iprev;

 union optim_u optu;          /* short lived optimization fields */
};
 
/* record in avl tree (set) for inst mod net list gen tn duplicate reuse */ 
struct tn_dup_t {
 word32 nlo_ndx;               /* net list object in mod index */
 int32 tni;
};

/* adr add struct to hold duplicate adr add values */ 
struct adradd_dup_t {
 struct mod_t *mdp;        /* module tmp is in */
 int32 srep;               /* srep of this tmp */
 int32 blen;               /* blen of tmp */
 int32 par_ti;             /* parent tmp */
 size_t offset;             /* offset from the parent */
 int32 res_ti;             /* result of adr add */
};

/* avl tree node for flow graph non repeated element list building  */
struct avlnode_t {
 unsigned bal : 8;
 unsigned via_dir : 8;
 void *valp;                  /* probably ptr to record of compare values */
 struct avlnode_t *lp, *rp;
};

/* avl search tree tmp name root record - simplifies chaning root */
struct avlhd_t {
 int32 num_nodes;
 struct avlnode_t *avl_root;
 cmpsword (*avl_cmp)(const void *, const struct avlnode_t *);
 struct avlnode_t *(*avl_alloc)(void *);
};

/* union for comm area (and NLO and cint) labels and values */
union tn_const_u {
 word32 tn_cint;             /* for cint (immediate) word bit val */
 int32 modadr_nlo; 
 int32 el_ndx;                /* addr field depending on type of of com lab */ 
 int32 ctab_ndx;              /* base index for label of per mod contab */
};

/* union for the comm area labels that need the mod/task symbol */
//SJM FIXME - this should be malloced
struct tn_syadr_t {
 int32 el2_ndx;
 struct sy_t *tfm_syp;
 struct mod_t *in_mdp;
};

/* tmp name record */
struct tn_t {
 unsigned srtyp : 6;          /* srep type of tmp name */  
 unsigned tn_typ : 2;         /* register type of tmp name */  
 unsigned comlab_typ : 6;     /* per mod comm area data object label type */  
 unsigned t_signed : 1;       /* T => tn signed - any can be */
 unsigned t_real : 1;         /* stored as SR VEC but actually double */
 unsigned t_used_in_bw_insn : 1; /* T => used in a byte or half word insn */
 unsigned t_used_cross_call : 1; /* T => used across a call */
 unsigned conadr_is_is : 1;   /* T => per mod comm area const is IS form */
 unsigned tn_used_wide : 1;   /* T => tmp is used in a wide context */
 unsigned tn_spilled : 1;     /* T => this tmp name is spilled - wide always */
 unsigned tn_assigned : 1;    /* T => tn assigned to reg for this flowg */
 unsigned used_in_asm : 1;    /* T => tn used in lowered asm */
 unsigned x86_regno : 6;      /* the x86 regno this tmp lowers to */
 unsigned svec_adr_add : 1;   /* T => tn is adr add of svec */ 
 unsigned idp_typ : 6;        /* __idp type (eventually replace comlab) */
 unsigned tn_used_var_shift : 1; /* tmp used as variable shift amount */
 unsigned tn_cnvt_from_2state : 1; /* tmp used 4-state from 2-state */
 unsigned tn_bpart_zero : 1;  /* tmp used 2to4 state b part (0) */
 unsigned tn_spill_fold: 1;   /* tmp spill is folded */
#ifndef __CVC32__
 unsigned passed_args: 3;     /* arg num passed to a asl wrapper */
#endif
#ifdef __VALTRK__
 unsigned res_tn_useistays : 1;/* T => insn res or uses this tn must stay */
 unsigned nd_valtrk_idp_siz : 1; /* T => idp (%esi?) reg tn - mod idp size */
#endif
 //AIV 07/02/09 - these are only used for debuging
 //unsigned is_reg_use : 1;     /* reg tmp is used */
 //unsigned is_reg_def : 1;     /* reg tmp is def */
 /* AIV 02/13/09 - this is currently only needed for debug */
 //int32 def_ndx;             /* tmp def index (identifier) */
 
 int32 tnwid;                 /* width of pointed to tmp name object */      
 int32 spill_ebp_byt_ofs;     /* for spill wrd and all wid, ebp ofs in bytes */
 int32 valnum;                /* current value number for this tn */ 
 int32 tn_coalesce_into;      /* for colalescing - tni that replaces */
 int32 tag_parent_tni;        /* if result of adr add containing parent tni */
 size_t child_tag_offset;      /* for tn in parent, offset in area in bytes */
 union tn_const_u tncu;       /* union for common lab and cint tn vals */ 
 struct tn_syadr_t *tnsyrecp; /* rt mem area that needs ndx/sym */
 struct insn_t *st_into_ip;   /* insn ptr for checking stored intos */
 struct avlhd_t *tn_conflct_tree;/* avl tree of tn's this tn comflicts with */
 struct tn_list_t *tn_adj_lst; /* tmps adjacent to this one */ 
 struct reg_alloc_info_t *ralloci; /* reg alloc save info for 2nd pass */
#ifdef __VALTRK__
 struct insn_t **curdef_ip;   /* per word insn most recent definer of tn */ 
 word32 *trk_valp;            /* malloc tracked current val - only parents */
 word32 *trk_known;           /* only child part may be known, per bit mask */  
 struct avlhd_t *bb_def_tree; /* avl tree of bblk this tn defined in */ 
 struct avlhd_t *bb_use_tree; /* avl tree of bblk this tn used (refed) in */ 
#endif
};

/* formal tmp tab same operands and result type search information record */
struct ftval_t {
 /* AIV 02/18/11 - this needs to be 6 bits not 4 - more srtyps now */
 unsigned srtyp : 6;
 unsigned tn_typ : 4;           /* type of tmp name */  
 unsigned res_tnwid : 24;
 int32 res_tni;
//SJM? - can't this just get the amodes from some insn? 
 struct amode_t am1;
 struct amode_t am2;
};

/* case component stmt list record */
struct icas_t {
 unsigned end_mark : 1;       /* T => end fence of table */
 struct bblk_t *cstmt_bbp;    /* basic blk that starts case stmt list */
 struct csitem_t *csitem;     /* item - contains stmt list ptr */
};

/* case item record - sorted compare select expr to values */
struct icasx_t {
 unsigned cxtyp : 4;          /* complexity of item expr */
 int32 cas_tabi;
 word32 aval;                 /* for constant expr, value, a part */
 word32 bval;                 /* and b part */
 struct expr_t *casx;         /* item expression */
};

/* MACHINE INSN RECORDS */
/* x86 machine insn record for printing insns and checking addr modes */
//AIV? - how handle these?
struct insn_info_t {
 int32 inum;
 char *inam;
 unsigned iclass : 8;
 unsigned rdwr_siz : 8;
};

/* deflst insn list of ptrs to insns */
struct defilst_t {
 struct insn_t *defip;
 struct defilst_t *defilstnxt;
};

/* list of non-blocking stmts */
struct nb_stmt_lst_t {
 unsigned processing_pnd0s : 1;  /* T => known to be processing pnd0s */
 unsigned has_static_mem : 1;    /* T => if this nba has static mem */
 unsigned has_rhs_const : 1;     /* T => if rhs is constant */
 unsigned is_scalar : 1;         /* T => true is scalar */
 unsigned need_free_fg : 1;      /* T => need free fg to free alloc nb ev */
 struct st_t *stp;               /* current nb stmt */
 struct nb_stmt_lst_t *stnxt;    /* next nb stmt */
};

/* iconn storage info to only create one flow graph per xpr */
struct np_iconn_t {
 int32 iconn_ndx;               /* this flow graph identifier number */
 struct flowg_t *fgp;           /* the flowg generated for this iconn */
 struct expr_t *up_rhsx;        /* up rhsx expr */
 struct net_pin_t *npp;         /* npp this is from */
};

/* iconn storage info to only create one flow graph per xpr */
struct gate_conta_t {
 struct flowg_t *fgp;           /* the flowg generated for this gate */
 struct net_pin_t *npp;         /* net pin from which this is gened */
 struct mod_t *mdp;             /* instance to move to during fg gen */
 int32 gc_ndx;                  /* enter index for generate flow graph */
 struct expr_t *xp;             /* gate expression */
};

/* gate list of flow graphs with back end delay assigns */
struct gate_da_list_t {
 struct flowg_t *fgp;             /* flow graph */
 struct gate_da_list_t *nxt;      /* nxt delay assign fg */
};


/* dce expr info to create one byte storage area for each expr */
struct dce_expr_info_t {
 struct dcevnt_t *dcep;      /* the dcep that created this info */
 int32 tni;                  /* the tmp for the storage area */
};

/* for debugging, idp area map table - for CVC in mod_t record */
struct idp_map_t {
 unsigned idpmaptyp : 8;     /* type of object for this idp offset */
 union el_u idpobju;         /* the obj (netbp net?) for this idp offset */
 struct task_t *idp_tskp;    /* ptr to tsk if in task for unique name */
};

/* table describing asm lib (asl_) routines for x86 reg optimization */
struct asl_info_t {
 int32 asl_rout_num;
 char *asl_rout_nam;
 unsigned uses_idp : 1;      /* T => needs __idp to be set upon entering */
 unsigned asl_ret_typ : 4;
 unsigned asl_op_typ[7];
};

extern int32 *__asl_info_map;    /* map of routine number to table index */
extern int32 __max_asl_rout_num; /* max asl routine number */

extern int32 __needs_thread_ctrl; /* T => block needs thread control */

/* variables tmp name locations (vars and consts also tmps) */
extern struct tn_t *__tntab; /* design wide (?) tmp name table */
extern size_t __tntabsiz;    /* current size */         
extern int32 __tntab_nxti; /* next location to use */
extern struct avlhd_t **__formal_tmptab;/* array index by vinsn of tmps */
extern int32 __avl_node_is_new; /* T avl tree find added the node */
extern struct avlnode_t *__tmp_avl_hd;  /* tmp for balance avl tree */
extern int32 *__nlo_tn_used; /* table so use same NLO tn if num same */
extern struct avlhd_t *__adradd_child_tree;/* adradd child tree */

/* avl tree (set) hdr tress to make sure only one tn per/mod NL object */
extern struct avlhd_t *__cint_dup_tn_tree;
extern struct avlhd_t *__contab_dup_tn_tree;
extern struct avlhd_t *__np_iconn_dup_tn_tree;
extern struct avlhd_t *__gate_conta_dup_tn_tree;

extern int32 __rev_po_ndx; /* for reverse post order nums - current ndx */
extern int32 __enter_bblk_valnum; /* value number at start of cur bblk */
extern int32 __cur_valnum; /* current highest used value number */
extern struct bblk_t *__dum_fg_ent_bbp;/* dummy bblk for fg enter back edges */
extern struct bblk_t *__loop_continue_bbp; /* loop continue block */
extern struct bblk_t *__loop_break_bbp;    /* loop break block */

extern struct bblklst_t *__cur_dom_fron_todos; /* dom frontier wrd list hd */
extern struct bblklst_t *__cur_dom_fron_tail; /* and tail for add to end */
extern int32 *__insn_order_ndx; /* bblk rpo index sort tab for ip to bblk map */

/* mod flow graph variables */
extern struct flowg_t *__proc_flowg_hd; /* hd of cur gen list of flow graphs */
extern struct flowg_t *__proc_flowg_tail; /* and its tail */
extern struct flowg_t *__cur_flowg;  /* current being gened flow graph */
extern struct flowg_t **__flowgtab; /* work array of ptrs to flowgs in mod */
extern size_t __flowgtabsiz;  /* current size */ 
extern int32 __flowg_lasti;   /* next use location */       
extern struct bblk_t **__ndxjmp_bbtab; /* tab of bblk ptrs for ndx jumps */
extern size_t __ndxjmp_bbtab_siz;/* current table size */
extern int32 __jmplab_nxti;   /* current jmp label number */
extern int32 *__jmpbase;      /* tab of jump bases for per inst ndx jumps */
extern size_t __jmpbas_tabsiz; /* current allocated size of jmp base tab */
extern struct bblk_t **__bblktab; /* work array of ptrs to bblks */
extern size_t __bblktabsiz;    /* current size */
extern int32 __bblk_lasti;    /* last used bblk index */ 
extern int32 __gening_tsk;    /* T => generating insn inside task body */
extern int32 __gening_mdc;    /* gening merged always blocks */
extern int32 **__decomposed_tn_nums; /* wide tmps into word tmps wrk area */
extern struct nb_stmt_lst_t *__nb_stmt_hd; /* non-blocking stmt head */
extern struct nb_stmt_lst_t *__nb_stmt_cur;/* last non-blocking stmt */
extern int32 __need_reg_tns;  /* T => use x86 reg for tn sets and fuds */

/* variables for storing bblk information (property trees?) */
extern int32 __cur_mark;      /* for keeping track of current marking step */

extern struct avlnode_t **__avltab; /* array for linearized avl tree */
extern int32 __avltabsiz;     /* current malloced work tab size */ 
extern int32 __avl_lasti;     /* last allocated */

/* basic block variables */
extern struct bblk_t *__cur_bbp; /* cur being filled basic block ptr */  
extern struct bblk_t *__enter_bbp;/* entry (1st) bblk in flow graph */
extern struct bblklst_t *__last_alloc_bblst; /* last allocated bblk list el */
extern union ifrom_u __cur_ifrom_u; /* statement or net v insn from */ 
extern struct insn_t *__cur_ip;   /* cur being lowered to insn ip */
extern int32 __push_count;        /* number of variables push to wrap call */

extern int32 __nxt_lab;       /* counter for creating local insn lab nums */
extern int32 __enter_seq_no;  /* counter for creating lab numbers */
extern int32 __enter_dce_seq_no; /* counter for creating enter dce numbers */
extern int32 __dce_no;        /* counter for creating dce numbers */
extern int32 __bblk_seq_no;   /* counter for creating basic block nums */ 
extern word32 __flowg_seq_no;  /* counter for creating flow graph nums */ 
extern int32 __iconn_seq_no;  /* counter for creating iconn ident nums */ 
extern int32 __gate_conta_seq_no; /* counter for creating scalar conta nums */ 

extern struct insn_t *__copy_ip; /* the current copy insn to xpnd from */
extern struct bblk_t *__func_complete_bbp; /* func comp bbp n case of disable */
extern int32 __need_net_addr;       /* need to generate net address flag */

/* internal run time work variables (regs) */
//AIV64 __nchged_i1 - int32/word32????????
#ifdef __CVC32__
extern int32 __nchged_i1;     /* RT - access to rng form nchg lp */
extern int32 __nchged_i2;     /* and low end of range */
#else
extern word32 __nchged_i1;     /* RT - access to rng form nchg lp */
extern word32 __nchged_i2;     /* and low end of range */
#endif
/* AIV 02/21/09 - this needs to be word32/ 64-bit */
extern word32 __nchged_delayed_mipd; /* and 2nd time thru mipd flag */
extern struct net_pin_t *__cur_npp; /* cur runtime net pin */
extern int32 __delay_mipd;    /* chg process MIPD state glb */
extern int32 __nchg_tevpi;
extern char **__thdjmp_ret_tab;  /* jump thru current thd dynamic lnk labels */
extern int32 __thdjmp_siz;    /* growing tab size and next to use */
extern int32 __thdjmp_nxti;
extern int32 __loop_depth;       /* loop depth during compilation */

extern struct gate_da_list_t *__hd_gdap; /* head date del assgn struct list */
extern struct gate_da_list_t *__tail_gdap; /* tail date del assgn struct list */

extern int32 __removed_bblks; /* number of removed basic blocks */ 
extern int32 __num_asm_insn;  /* num of asm insn */
extern int32 __removed_asm_insns;  /* removed num of asm insn */
extern int32 __trk_num_insn_removed; /* tracking - per bblk no. insn removed */
extern int32 __trk_num_insn_changed; /* and changed */

/* maximum number of printed assembly lines prior to splitting files */
#define PARTITION_MAX_INSN_COUNT 1000000
extern int32 __num_print_asm_insn;  /* number of asm insn printed */

/* /tmp/ distinct file names */
extern char **__mod_file_names;   /* module tmp file names */
extern char **__comm_nt_file_names; /* comm init file names - one per module */
extern char *__comm_file_name;    /* comm file name */
extern char *__comm_nt_file_name; /* comm init file name */
extern char *__exe_file_name;     /* exe main file name */
extern char *__cvclib_file_name;  /* cvclib file name */

extern int32 __idp_ti;        /* per module idp storage area tmp */
extern word32 *__ebp;         /* dummy asm stack base for gdb debugging */
extern void *__process_nbpa_varndx_ev_enterp;
extern void *__process_cancel_gate_rescheduled_ev_enterp;
extern void *__process_next_event_free_enterp;

extern struct nchglst_t *__next_nchglp; /* next processing nchglp */
extern void *__process_next_nchg_enterp; /* process next nchg enter ptr */
extern void *__first_enterp; /* the first sim process entered */

extern struct heap_t *__last_nb_hp; /* last non-blocking heap inserted time */

extern struct nchglst_t __nchg_dummy_hd; /* dummy header for nchgs */
extern struct tev_t __pnd0_dummy_hd; /* dummy header for pnd0 events */
extern struct tev_t __nb_dummy_hd; /* dummy header for nb events */
extern struct task_t *__save_scope_tskp; /* save from $scope task if present */ 
extern struct st_t *__generating_stp; /* current genned stp */

extern word32 __cvc_slotend_action; /* switches for possbile slot end action */
extern int32 __known_inum; /* for ports to indicate known inum value */
extern int32 __design_has_nb_events; /* design has nb events */
extern int32 __design_has_nb_del_events; /* design has nb with delay events */
extern struct mod_t *__init_mdp;  /* module glbl for init code */

/* NOTE - these are strings stored as long binary values */
extern word32 __cvclib_str[]; /* cvclib.o stored as a string */
extern size_t __cvclib_size; /* size of cvclib string */
extern word32 __exe_main_str[]; /* main_exe.o stored as a string */
extern size_t __exe_main_size; /* size of main_exe.o string */

extern word64 __nb_const_last_time;  /* last nb assign time */
extern word64 __nb_const_last_time; /* last nb assign time */
extern int32  __all_nb_same_time;   /* nb assign const all same time */

#ifdef __CVC32__
extern va_list  __advance_seta_va; /* global to reset advance of varargs */
#endif

extern char __asm_file_name[RECLEN];/* assembly file name */
extern int32 __asm_pipefd[2];       /* assembly pipe fds */
extern pid_t __asm_pid;             /* assembly pipe pid */
extern void  *__asm_stack;          /* assembly clone pipe stack */
