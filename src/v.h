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

#define VERS "OSS_CVC_7"

#include "fstapi.h"

#if defined(__RHEL6X__)
#ifdef __CVC32__
#define VERS2 ".00b-rhel6x"
#else
#define VERS2 ".00b-x86_64-rhel6x"
#endif
#elif defined(__RHEL5X__)
#ifdef __CVC32__
#define VERS2 ".00b-rhel5x"
#else
#define VERS2 ".00b-x86_64-rhel5x"
#endif
#elif defined(__RHEL4X__)
#ifdef __CVC32__
#define VERS2 ".00b-rhel4x-compat"
#else
#define VERS2 ".00b-x86_64-rhel4x"
#endif
#else
/* force syntax error if no RHEL defined */
bogus_call_to_die ++ 25;
#endif

#define OFDT "07/07/14"

// SJM 04-21-14 - option for x propagation synthesizable RTL compiled
// in - undef to remove which simplifies code use the #define to redo
// or remove from source
#define __XPROP__

#define OUTLINLEN 71          /* length of output file line */
#define DFLTIOWORDS 8         /* preallocated size for I/O and work values */
#define MUSTFREEWORDS 64      /* for stk values wider free when done */
/* ? for debugging */
/* #define DFLTIOWORDS 1 */   /* preallocated size for I/O and work values */
/* #define MUSTFREEWORDS 1 */ /* for stk values wider free when done */


#define MAXNUMBITS 1000000    /* allowing 1 million for now */
#define MAXNUMPORTS 1000000   /* index must fit in 20 bits so 1 million max */
#define MAXXNEST 256          /* initial exp. eval. stack depth - grows */
#define MAXFCNEST 256         /* initial fcall eval stack depth - grows */
#define XNESTFIXINC 0x4096    /* increase xpr stack by this */
#define IDCHARS 4090          /* max. ID length (need 7 for unique) */   
#define IDLEN 4097            /* size of string to hold ID */
#define RECLEN 4097           /* length for normal temp string (plus \0) */
#define MSGTRUNCLEN 1265      /* for msg len. to trunc to (... end) - id fit */
#define TRTRUNCLEN 66         /* for tracing truncate length (short) */
#define MAXFILS 500           /* start number of in and lib. files (grows) */
#define MAXFILNEST 1024       /* max. num. of `include macro nestings */
#define MAXLEVELS 800         /* max. num. nested param/task/block decls */
#define MAXGLBCOMPS 800       /* max. components in global name */
#define MAXLBEXTS 512         /* max. no. of -y library extensions */
#define MAXINCDIRS 2048       /* max. no. of +incidr search paths files */
#define MAXNOOPTMODS 2048     /* max. no of +optimize_off module names */
#define MAXUPRTS 11           /* max. no. of udp ports */
#define UALTREPIPNUM 7        /* lowest port number to use slower udp rep */
#define MAXVERIUSERTFS 4095   /* maximum number of pli veriusertfs tfs */
#define SYSTFDATSIZE 256      /* starting size of vpi_ systf table (grows) */
#define BASE_VERIUSERTFS 1000 /* base for pli (veriuser) system tf_s */
#define MAXITDPTH 800         /* dpth of itstk */
#define MAXCIRDPTH 4096       /* maximum depth of a circuit */ 
#define IAHISTSIZ 256         /* start history list line and command size */
#define INFLOOP_MAX 1000      /* stages with time move for loop checking */
#define DFLT_SNAP_EVS 5       /* default number futuren events to print */
#define GDVAL 0x400           /* good value */
#define BDVAL 1000            /* bad value */
#define TOPVPIVAL 1023        /* biggest vpi define const value (MUST EXTND) */
#define PVH_MAGIC 0x625       /* 11 bit vpi handle magic number */

#define MAXPRPSTNEST 800      /* maximum statement nesting */
#define MAXBTDPTH 40          /* maximum depth of timing q (3**40)/2 or so */
#define BTREEMAXWID 8         /* max. b tree node width (usually .5 full) */

#define BIG_ALLOC_SIZE 0x3ff8 /* size of block to allocate at once */
#define VPI_OBJALLOCNUM 2048  /* number of vpi object to allocate at once */
#define RDBUFSIZ 0x4000       /* source list buffer size */
/* AIV 05/04/10 - increased buffer size to 1M */
#define DVBUFSIZ 0x100000     /* buffer for dumpvars output */
#define MAX_DMPPRTS_FILES 26  /* maximum num different dump ports files */ 
#define MAX_ERRORS 32         /* error limit in one run */
#define MAXEMSGNUM 4000       /* highest possible any type error num */

#define MY_FOPEN_MAX 1024     /* guess at OS process max open stdio.h wrong */

#define TEVTAB_ALLOC_SIZE 4096 /* size to alloc __tevtab by */

/* RANDOM NUMBER GENERATION CONTANTS */
#define MY_LONG_MAX2 0xffffffff
/* SJM 11/19/03 - must use 32 bit range even for 64 bit systems */ 
/* because Verilog WBITS (for now?) must be set to 32 */
#define MY_LONG_MAX 2147483647L
#define MY_LONG_MIN (-MY_LONG_MAX - 1L)

#ifdef __CVC32__
typedef unsigned long word32;
typedef long sword32;
typedef int int32;
typedef unsigned long long word64;
typedef long long sword64;
typedef unsigned char byte;
typedef unsigned short hword;
typedef short hsword;
typedef int32 tmp_tev_ndx;
typedef word32 t_midat;
typedef int cmpsword;
#else
typedef unsigned long word32;
typedef long sword32;
typedef int int32;
typedef unsigned long word64;
typedef unsigned long long word128;
typedef long sword64;
typedef unsigned char byte;
typedef unsigned short hword;
typedef short hsword;
typedef int32 tmp_tev_ndx;
typedef word32 t_midat;
typedef long cmpsword;
#endif

/* needed to allow signals to use normal decls */
typedef int32 sighandler();

#ifndef __sparc
/* BEWARE - assuming all non sparc systems define BYTE_ORDER and endian.h */
/* to PORT change for your system */ 
# ifdef __APPLE__
#  include <sys/types.h>
# else
#  ifdef __CYGWIN32__
#   include <sys/param.h>
#  else
#   ifdef __FreeBSD__
#    include <sys/endian.h>
#   else
#    include <endian.h>
#   endif
#  endif
# endif

#ifndef __CVC32__
 /* AIV 04/13/08 - didn't implement div/mult using __uint128 in v_ex2.c */
 #if (BYTE_ORDER == BIG_ENDIAN)
   AIV DID NOT IMPLEMENT v_ex2.c mult/div for little endian
 #endif
#endif

typedef union {
 word64 w64v; 
#if (BYTE_ORDER == BIG_ENDIAN)
 struct { word32 high; word32 low; } w_u;
#else
 struct { word32 low; word32 high; } w_u;
#endif
} w64_u;
#else
#include <sys/isa_defs.h>

typedef union {
 word64 w64v; 
#if defined(_BIG_ENDIAN)
 struct { word32 high; word32 low; } w_u;
#else
 struct { word32 low; word32 high; } w_u;
#endif
} w64_u;
#endif

#define INTBITS 32
#define BYTEBITS 8
#define CINTBITS 32
#define SHORTCINTBITS 16
#define LONGCINTBITS 64

#define TRUE 1
#define FALSE 0
#define INTBYTES 4
#define TIMEBITS 64

/* AIV 01/13/12 - added max time used for path delays */
#define MAXTIME 0xffffffffffffffffULL

#ifdef __CVC32__
/* 32-bit defines */
#define WBITS 32
#define LWBITS 64
#define WRDBYTES 4
#define MAXWSWRDS ((MAXEMSGNUM + INTBITS)/INTBITS)
#define WORDMASK_ULL 0xffffffffULL
#define ALL1W 0xffffffff
#define ALL1HW 0xffff
#define SHORTBASE (1 << (WBITS/2))

/* these values are IEEE */
#define REALBITS 32           /* 64 bit double - but no no b part */
#define LG2_DIV_LG10 0.3010299956639812
#define EPSILON 2.2204460492503131E-16  /* float.h dbl == diff. amount */
#define _DEXPLEN 11           /* double exp. len (not incl. sign) */

#else
/* 64-bit defines */
#define WBITS 64
#define LWBITS 64
#define WRDBYTES 8
/* AIV 06/22/09 - make these all 32 not WBITS for 64 - always 32 */
#define MAXWSWRDS ((MAXEMSGNUM + INTBITS)/INTBITS)
#define WORDMASK_ULL 0xffffffffffffffffULL
#define ALL1W 0xffffffffffffffff
#define ALL1HW 0xffffffff
#define SHORTBASE 4294967296

/* these values are IEEE */
#define REALBITS 64          /* 64 bit double - but no no b part */
#define SHORTREALBITS 32     /* 32 bits for float */
#define LG2_DIV_LG10 0.3010299956639812
#define EPSILON 2.2204460492503131E-16  /* float.h dbl == diff. amount */
#define _DEXPLEN 11           /* double exp. len (not incl. sign) */
#endif

/* number base constants */
#define BHEX 0
#define BBIN 1
#define BOCT 2
#define BDEC 3
#define BDBLE 4               /* special base for printing */
#define BNONE 5               /* indicator for no base override */
/* debugger only bases */
#define BCHAR 6               /* force treatment as char */
#define BSTR 7                /* froce treatment as string */

/* net representation forms */
#define NX_CT 0
#define NX_ARR 1
#define NX_DWIR 2
#define NX_WIR 3
#define NX_SCALWIR 4          /* for scalar empty range field */

/* net storage representation forms */
#define SR_VEC 0
#define SR_SVEC 1
#define SR_SCAL 2
#define SR_SSCAL 3
#define SR_BIT2S 4            /* reg vec but 2 state */
#define SR_SCAL2S 5           /* 2 state scalar - for sv stored as byte */
#define SR_ARRAY 6
#define SR_PVEC 7             /* now only used for gates */
#define SR_PXPR 8             /* for parameter src. normal rhs expr */ 
#define SR_PISXPR 9           /* for # and defparams, per inst. array of x */
#define SR_PNUM 10            /* after fix up simple parameter const. */
#define SR_PISNUM 11          /* after fix up IS parameter const. */
#define SR_STRING 12          /* new SV string type */

/* new dpi sreps - inconsistent because sr array means arrays no srep val */
#define SR_DPI_SCAL2S 13
#define SR_DPI_BYTE 14
#define SR_DPI_CINT 15
#define SR_DPI_SHORTCINT 16
#define SR_DPI_LONGCINT 17
#define SR_DPI_REAL 18
#define SR_DPI_CHANDLE 19
#define SR_DPI_STRING 20
#define SR_DPI_UNKN 21

/* compiler only storage rep types */
#define SR_CINT 22
#define SR_BBLK 23
#define SR_MODADR 24
#define SR_DSGNADR 25
#define SR_UNKN 26

/* strength types */
#define LOW_STREN 1
#define HIGH_STREN 2
#define CAP_STREN 3

/* strength values - must fit in 3 bits */
/* notice semantics requires this exact strength assignment for 0 to 7 */
#define ST_HIGHZ 0
#define ST_SMALL 1
#define ST_MEDIUM 2
#define ST_WEAK 3
#define ST_LARGE 4
#define ST_PULL 5
#define ST_STRONG 6
#define ST_SUPPLY 7

/* capacitor sizes */
#define CAP_NONE 0
#define CAP_SMALL 1 
#define CAP_MED 2
#define CAP_LARGE 3

/* 6 bit stren only constants */
#define NO_STREN 8            /* never a strength - indicator only */
#define ST_STRVAL 0x36        /* (strong0,strong1) 110110 */

/* strength and value constants */
#define ST_STRONGX ((ST_STRVAL << 2) | 3)
#define ST_HIZ 0x02           /* <hiZ:hiZ>=z - 00000010 */
#define ST_PULL0 0xb4         /* <Pu:Pu>=0 - 10110100 */
#define ST_PULL1 0xb5         /* <Pu:Pu>=1 - 10110101 */
#define ST_SUPPLY0 0xfc       /* <Su:Su>=0 - 11111100 */ 
#define ST_SUPPLY1 0xfd       /* <Su:Su>=1 - 11111101 */ 

/* udp types */
#define U_COMB 0
#define U_LEVEL 1
#define U_EDGE 2
#define NO_VAL 0x7f           /* misc. empty for byte no edge, no val etc. */

/* udp edge values (? and b legal in edges) */
#define UV_0 0
#define UV_1 1
#define UV_X 3
#define UV_Q 4
#define UV_B 5

/* net pin connection types */
#define NP_GATE 0
#define NP_CONTA 1            /* connects to lhs or rhs of cont. assign */
#define NP_PB_ICONN 2         /* per bit form of iconn type - now ld/drv */
#define NP_ICONN 3            /* for load down assign, driver to up iconn */
#define NP_PB_MDPRT 4         /* per bit mdprt form both drv/ld now */
#define NP_MDPRT 5            /* for drvr down port assgn, load up to iconn */
/* notice last of in src npps must be mdprt */
#define NP_MIPD_NCHG 6        /* for MIPD/interconnect, conn net(s) nchg */
#define NP_TCHG 7             /* specify time chg record subtyp determines */
#define NP_TRANIF 8           /* third tranif port enable is normal rhs */
#define NP_PULL 9             /* constant strength pullup or pulldown drv. */
/* PLI only not seen by vpi_ routines */
#define NP_TFRWARG 10         /* driver is tf_ task/func is_rw driver */
#define NP_VPIPUTV 11         /* driver is vpi_ put value wire driver */
/* removed from net drvs after tran channels built - drivers only */
#define NP_TRAN 12            /* driver/load for special tran/tranif gate */ 
#define NP_BIDICONN 13 
#define NP_BIDMDPRT 14 

/* port direction change net driver states - pre added np list states */
#define DRVR_NONE 0           /* net not driven */
#define DRVR_NON_PORT 1       /* inout port or gate/conta */
#define DRVR_ICONN 2          /* one up iconn inst conn output driver */ 
#define DRVR_MDPRT 3          /* one down mod port input driver */ 

/* parmnplst net pin types - disjoint32 from sim time npps */
#define PNP_GATEDEL 0
#define PNP_CONTADEL 1
#define PNP_NETDEL 2
#define PNP_PROCDCTRL 3
#define PNP_PATHDEL 4
#define PNP_TCHKP1 5
#define PNP_TCHKP2 6

/* change record subtypes */
#define NPCHG_NONE 0
#define NPCHG_TCSTART 1
#define NPCHG_TCCHK 2
#define NPCHG_PTHSRC 3

/* kinds of net pin global processing - npgru interpretation */
#define XNP_LOC 0
#define XNP_DOWNXMR 1
#define XNP_RTXMR 2
#define XNP_UPXMR 3

/* kinds of net pin processing */
#define NP_PROC_INMOD 0
#define NP_PROC_GREF 1
#define NP_PROC_FILT 2

/* left hand expression types */
#define LHS_DECL 1
#define LHS_PROC 2

/* tokens types - must < 255 */
#define TOK_NONE 0
#define ID 1
#define BADOBJ 2
#define NUMBER 3
#define ISNUMBER 4            /* array of constants - cur_iti selects */
#define REALNUM 5
#define ISREALNUM 6
#define LITSTR 7              /* token returned for literal str by scanner */
#define OPEMPTY 8             /* unc. expr place holder in expr. list */ 
#define UNCONNPULL 9          /* unc. inst. input port `unconndrive val. */
#define RMADDR 10             /* special readmem address token */

/* punctuation */
#define SEMI 12
#define COMMA 13
#define COLON 14
#define SHARP 15
#define LPAR 16
#define RPAR 17
#define LSB 18                /* [ (also bit select operator) */
#define RSB 19
#define LCB 20                /* { */
#define RCB 21
#define DOT 22
#define AT 23

/* special unary */
#define CAUSE 24              /* -> not an expression operator */
#define EQ 25                 /* = (assignment but not an expr. lang.) */

/* unary only operators - real 0.0 is F for logical */
#define BITNOT 26             /* ~ */
#define NOT 27                /* ! (logical) */
/* real unary only (0.0 if F else T) */
#define REALNOT 28 

/* both unary and binary */
#define REDXNOR 29            /* must ^~ - ~^ is 2 unaries */
#define PLUS 30               /* + */
#define MINUS 31              /* - */
#define BITREDAND 32          /* bin & (bit) - un red. and */
#define BITREDOR 33           /* bin | (bit) - un red. or */
#define BITREDXOR 34          /* bin ^ (bit) - un red. xor */
/* both real - notice type must be in operator */
/* notice this should have at 5? number */
#define REALMINUS 35

/* binary operators */
#define TIMES 36              /* * */
#define POWER 37              /* ** */
#define DIV 38                /* / */
#define MOD 39                /* % */
#define RELGE 40              /* >= */
#define RELGT 41              /* > */
#define RELLE 42              /* <= (also non block cont. assign token) */
#define RELLT 43              /* < */
#define RELCEQ 44             /* === */
#define RELEQ 45              /* == */
#define RELCNEQ 46            /* !== */
#define RELNEQ 47             /* != */
#define BOOLAND 48            /* && */
#define BOOLOR 49             /* || */
#define SHIFTL 50             /* << */
#define ASHIFTL 51            /* <<< - differenet operator but same as << */
#define SHIFTR 52             /* >> */
#define ASHIFTR 53            /* >>> */
#define FPTHCON 54            /* *> (full path conn spfy. op.) */
#define PPTHCON 55            /* => (parallel path conn spfy. op.) */
#define TCHKEVAND 56          /* &&& (timing check conditional event op.) */
/* real binary */
#define REALPLUS 57
#define REALTIMES 58
#define REALPOWER 59
#define REALDIV 60
#define REALRELGT 61
#define REALRELGE 62
#define REALRELLT 63
#define REALRELLE 64
#define REALRELEQ 65
#define REALRELNEQ 66
#define REALBOOLAND 67
#define REALBOOLOR 68
/* notice logical non bit-wise and non-reduction 0.0 is F */

/* special ops */
/* special expression operators that do not correspond to read tokens */
#define QUEST 69              /* binary ? part of ?: */
#define QCOL 70               /* : part of ?: */
#define PARTSEL 71            /* part select [ */
#define PARTSEL_NDX_PLUS 72   /* an indexed part select [ +: */
#define PARTSEL_NDX_MINUS 73  /* an indexed part select [ -: */
#define CATCOM 74             /* concatenate comma (really list indicator) */
#define CATREP 75             /* concatenate repeat form */
#define FCALL 76              /* function call */
#define FCCOM 77              /* func/task call , (really list indicator) */
#define OPEVOR 78             /* event control or */
#define OPEVCOMMAOR 79        /* alternative to event ctrl or - sims same */
#define OPPOSEDGE 80          /* posedge in delay ctrl expr. */
#define OPNEGEDGE 81          /* negedge in delay ctrl expr. */
/* real specials */
#define REALREALQUEST 82      /* binary ?  part of ?: - all reals */ 
#define REALREGQUEST 83       /* bin ? part of ?: - real cond : part reg */ 
#define REGREALQUEST 84       /* binary : part of ?: - normal cond : real */

/* global expression componnents */ 
#define GLBREF 85             /* this is sort of ID and sort of expr. */    
#define GLBPTH 86             /* this is global path as XMRID expr (list) */
#define XMRID 87              /* ID node that is part of xmr (no sy) */
#define XMRCOM 88
#define INC 89                /* ++ */
#define DEC 90                /* -- */
#define PLUS_EQ 91            /* += */
#define MINUS_EQ 92           /* -= */
#define TIMES_EQ 93           /* *= */    
#define DIV_EQ 94             /* /= */
#define MOD_EQ 95             /* %= */
#define AND_EQ 96             /* &= */
#define OR_EQ 97              /* |= */
#define XOR_EQ 98             /* ^= */
#define SHIFTL_EQ 99          /* <<= */
#define ASHIFTL_EQ 100        /* <<<= */
#define SHIFTR_EQ 101         /* >>= */
#define ASHIFTR_EQ 102        /* >>>= */
/* AIV 10/06/10 - SV string comparison op types */
#define STRRELGT 103
#define STRRELGE 104
#define STRRELLT 105
#define STRRELLE 106
#define STRRELEQ 107
#define STRRELNEQ 108

/* special indicators */
#define UNDEF 109              /* toktyp for no pushed back token */
#define TEOF 110

/* sdf only constants */
#define DFLT_SEP_CHAR '.'
#define SDF_DOL 111
#define SDF_BACKQ 112
#define SDF_QUOTE 113
#define SDF_BACKSLASH 114
#define SDF_UNKN 0

/* notice unused token no. gap here for addition operators ? */

/* these can all appear outside modules - some can appear inside */
/* back quote is ascii 96 (0x60) just before lower case (after upper case) */
#define CDIR_ACCEL 130
#define CDIR_AEXPVECNETS 131
#define CDIR_CELLDEF 132
#define CDIR_DEFINE 133
#define CDIR_DFLNTYP 134
#define CDIR_ECELLDEF 135
#define CDIR_ELSE 136
#define CDIR_ELSIF 137
#define CDIR_ENDIF 138
#define CDIR_ENDPROTECT 139
#define CDIR_ENDPROTECTED 140
#define CDIR_XPNDVNETS 141
#define CDIR_IFDEF 142
#define CDIR_IFNDEF 143
#define CDIR_INCLUDE 144
#define CDIR_NOACCEL 145
#define CDIR_NOXPNDVNETS 146
#define CDIR_NOREMGATENAMES 147
#define CDIR_NOREMNETNAMES 148
#define CDIR_NOUNCONNDRIVE 149
#define CDIR_PROTECT 150
#define CDIR_PROTECTED 151
#define CDIR_REMGATESNAMES 152
#define CDIR_REMNETNAMES 153
#define CDIR_RESETALL 154
#define CDIR_TIMESCALE 155
#define CDIR_UNCONNDRIVE 156
#define CDIR_UNDEF 157
#define CDIR_DFLTDECAYTIME 158
#define CDIR_DFLTTRIREGSTREN 159
#define CDIR_DELMODEDIST 160
#define CDIR_DELMODEPATH 161
#define CDIR_DELMODEUNIT 162
#define CDIR_LANG 163 
#define CDIR_DELMODEZERO 164

#define CDIR_TOKEN_START CDIR_ACCEL
#define CDIR_TOKEN_END CDIR_DELMODEZERO

/* notice 19 unused token no. gap here ? */
#define ALWAYS 170
#define ALWAYS_COMB 171
#define ALWAYS_FF 172
#define ALWAYS_LATCH 173
#define ASSIGN 174
#define AUTOMATIC 175
#define Begin 176
#define BIT 177
#define BREAK 178
#define BYTE 179
#define CASE 180
#define CASEX 181
#define CASEZ 182
#define CHANDLE 183
#define CONTEXT 184
#define CONTINUE 185
#define DEASSIGN 186
#define DEFAULT 187
#define DEFPARAM 188
#define DISABLE 189
#define DO 190
#define EDGE 191
#define ELSE 192
#define END 193
#define ENDCASE 194
#define ENDFUNCTION 195
#define ENDGENERATE 196
#define ENDMODULE 197
#define ENDPRIMITIVE 198
#define ENDSPECIFY 199
#define ENDTABLE 200
#define ENDTASK 201
#define EXPORT 202
#define EVENT 203
#define FOR 204
#define FORCE 205
#define FOREACH 206
#define FOREVER 207
#define FORK 208
#define FUNCTION 209
#define GENERATE 210
#define GENVAR 211
#define HIGHZ0 212
#define HIGHZ1 213
#define IF 214
#define IFNONE 215
#define IMPORT 216
#define INITial 217
#define INOUT 218
#define INPUT 219
#define INT 220
#define INTEGER 221
#define JOIN 222
#define LARGE 223
#define LOGIC 224
#define LOCALPARAM 225
#define LONGINT 226
#define MACROMODULE 227
#define MEDIUM 228
#define MODULE 229
#define NEGEDGE 230
#define OUTPUT 231
#define PARAMETER 232
#define POSEDGE 233
#define PRIMITIVE 234
#define PULL0 235
#define PULL1 236
#define PURE 237
#define REAL 238
#define REALTIME 239
#define REG 240
#define RELEASE 241
#define REPEAT 242
#define RETURN 243
#define SCALARED 244
#define SHORTINT 245 
#define SHORTREAL 246
#define SIGNED 247
#define SPECIFY 248
#define SPECPARAM 249
#define SMALL 250
#define Strength 251
#define STRING 252
#define STRONG0 253
#define STRONG1 254
#define SUPPLY0 255
#define SUPPLY1 256
#define TABLE 257
#define TASK 258
#define TIME 259
#define TRI 260
#define TRI0 261
#define TRI1 262
#define TRIAND 263
#define TRIOR 264
#define TRIREG 265
#define UNSIGNED 266
#define VECTORED 267
#define VOID 268
#define WAIT 269
#define WAND 270
#define WEAK0 271
#define WEAK1 272
#define WHILE 273
#define WIRE 274
#define WOR 275

/* gate nums (not tokens) for sim - now separate gatid range */
/* now for debugging do not use low numbers */
#define G_ASSIGN 10 
#define G_BITREDAND 11
#define G_BUF 12
#define G_BUFIF0 13
#define G_BUFIF1 14
#define G_CMOS 15
#define G_NAND 16
#define G_NMOS 17
#define G_NOR 18
#define G_NOT 19
#define G_NOTIF0 20
#define G_NOTIF1 21
#define G_BITREDOR 22
#define G_PMOS 23
#define G_PULLDOWN 24
#define G_PULLUP 25
#define G_RCMOS 26
#define G_RNMOS 27
#define G_RPMOS 28
#define G_RTRAN 29
#define G_RTRANIF0 30
#define G_RTRANIF1 31
#define G_TRAN 32
#define G_TRANIF0 33
#define G_TRANIF1 34
#define G_BITREDXOR 35
#define G_REDXNOR 36

#define LAST_GSYM G_REDXNOR

/* gate classes */ 
#define GC_LOGIC 0
#define GC_BUFIF 1
#define GC_MOS 2
#define GC_CMOS 3
#define GC_TRAN 4
#define GC_TRANIF 5
#define GC_UDP 6
#define GC_PULL 7

/* region separation constants */
#define FIRSTKEY CDIR_ACCEL
#define BKEYS FIRSTKEY
/* this is last real op. part select's etc. come after */
#define LASTOP TEOF

/* unconnected pull directive OPEMPTY values */
#define NO_UNCPULL 0
#define UNCPULL0 1
#define UNCPULL1 2

/* net types (ntyp field) - meaningful when iotyp is NON_IO */
#define N_WIRE 0
#define N_TRI 1
#define N_TRI0 2
#define N_TRI1 3
#define N_TRIAND 4
#define N_TRIOR 5
#define N_TRIREG 6
#define N_WA 7
#define N_WO 8
#define N_SUPPLY0 9
#define N_SUPPLY1 10

#define N_REG 11
#define N_LOGIC 12
/* new SV 2 state var types */
#define N_BIT 13
#define N_INT 14
#define N_CINT 15

#define N_TIME 16
#define N_REAL 17
#define N_EVENT 18            /* needs to be event so -d decls in order */
#define N_BYTE 19
#define N_SHORTCINT 20
#define N_LONGCINT 21
#define N_CHANDLE 22
#define N_STRING 23

/* beware - number ranges used so all reg types must come after all wires */ 
#define NONWIRE_ST N_REG

/* the i/o net and port types - separate from net type */
#define IO_IN 0
#define IO_OUT 1
#define IO_BID 2
#define IO_UNKN 3
#define NON_IO 4

/* sync to location classes */
#define SYNC_FLEVEL 0
#define SYNC_MODLEVEL 1
#define SYNC_STMT 2
#define SYNC_SPECITEM 3
#define SYNC_UDPLEVEL 4
#define SYNC_TARG 5

/* scalared/vectored splitting states */
#define SPLT_DFLT 0
#define SPLT_SCAL 1
#define SPLT_VECT 2

/* min/typ/max delay selection values */
#define DEL_MIN 1
#define DEL_TYP 2
#define DEL_MAX 3

/* symbol types - determines net list element */
/* front end only symbols */
#define SYM_UNKN 0
#define SYM_M 1               /* module type name (not in pli) */
#define SYM_STSK 2            /* built in system task name */
#define SYM_SF 3              /* built in system function name */
#define SYM_DEF 4             /* preprocessor `define sym, separate table */

/* in module (real pli) objects */
#define SYM_I 5               /* inst. name in module */
#define SYM_TSK 6             /* task name */
#define SYM_F 7               /* function name */
#define SYM_LB 8              /* labeled block */
#define SYM_PRIM 9            /* built in primitive */
#define SYM_UDP 10            /* udp definition name */
#define SYM_N 11              /* wire, regs, events and I/O ports (nets) */
#define SYM_CA 12             /* symbol for conta */
#define SYM_TCHK 13           /* symbol for time check */
#define SYM_PTH 14            /* symbol for delay path */
#define SYM_LGB 15            /* labeled gen block symbol */

/* pli only object (handle) types - no front end symbol */
#define SYM_IMPATH 19         /* inter module (inst.) path not in ovi ? */
#define SYM_MPATH 20          /* any intra module path */
#define SYM_PRIMPATH 21       /* path between primitives - not in ovi ? */
#define SYM_WIREPATH 22       /* another kind of non ovi path ? */
#define SYM_TERM 23           /* primitive terminal dummy */
#define SYM_MPTERM 24         /* terminal of mod path - only acc handle */
#define SYM_PORT 25           /* module port dummy */
#define SYM_BIT 26            /* bit of expanded net dummy */
#define SYM_PBIT 27           /* bit of expanded port dummy */
/* dpi only objects - set from new dpi decl code */
#define SYM_DPIF 28           /* dpi function call symbol - find with dlopen */ 

/* new hierarchical reference elaboration time record types */
/* SJM 02-15-10 - new algorithm - fill complicated elab XMR record first */
#define XMP_UNKN 0
#define XMP_MOD 1
#define XMP_INST 2
#define XMP_INST_INGEN 3
#define XMP_GBLK 4
#define XMP_TSK 5
#define XMP_NET 7
#define XMP_NET_INGEN 8

/* tree balance constants */
#define BLEFT 0
#define BEVEN 1
#define BRIGHT 2

/* statement types */
#define S_NULL 0              /* ; by itself */
#define S_PROCA 1
#define S_NBPROCA 2
#define S_RHSDEPROCA 3
#define S_IF 4
#define S_CASE 5
#define S_FOR 6
#define S_FOREVER 7
#define S_REPEAT 8
#define S_WHILE 9             /* execept forever only sim time loop */
#define S_WAIT 10
#define S_DELCTRL 11
#define S_NAMBLK 12
#define S_UNBLK 13
#define S_UNFJ 14             /* this is for unnamed block fork-join only */
#define S_TSKCALL 15
#define S_QCONTA 16
#define S_QCONTDEA 17
#define S_CAUSE 18            /* CAUSE (->) <event> */
#define S_DSABLE 19           /* disable <task or block> */
#define S_STNONE 20           /* thing inside empty block */
/* special invisible simulation control statements */
#define S_REPSETUP 21         /* set up repeat count - st_u empty */
#define S_REPDCSETUP 22       /* event repeat form dctrl setup */ 
#define S_GOTO 23             /* goto statement for loops */
#define S_FORASSGN 24         /* special added (before) for assign */
#define S_BRKPT 25            /* for setting break point at statement */
#define S_INC 26              /* increment id++; */
#define S_DEC 27              /* decrement id-- */
#define S_BREAK 28            /* loop break statement */
#define S_CONTINUE 29         /* loop continue statement */
#define S_DO_WHILE 30         /* do-while loop */
#define S_FUNCCALL 31         /* void function call */
#define S_RETURN 32           /* function return statement */

/* system function types */
#define SYSF_UNKNOWN 0
#define SYSF_BUILTIN 1
#define SYSF_TF 2
#define SYSF_VPI 3

/* break point types */
#define BP_UNKN 0
#define BP_INST 1 
#define BP_TYPE 2

/* interactive entry reasons */
#define IAER_UNKN 0
#define IAER_BRKPT 1
#define IAER_STEP 2
#define IAER_STOP 3
#define IAER_CTRLC 4

/* generate item types */
#define GI_UNKN 0
#define GI_GBLK 1
#define GI_GFOR 2
#define GI_GIF 3
#define GI_GCASE 4
#define GI_CONTA 5
#define GI_CELL 6            /* src read as cells - separate before xpnd */
#define GI_GATE 7
#define GI_INST 8
#define GI_VARDECL 9
#define GI_INITALW 10
#define GI_GREF 11
#define GI_DFPARM 12

/* event control types */
#define DC_NONE 0
#define DC_EVENT 1
#define DC_DELAY 2
#define DC_RHSEVENT 3
#define DC_RHSDELAY 4
#define DC_WAITEVENT 5

/* statement dump new line control constants */
#define NONL 1
#define NL 2

/* Verilog operator types */
#define NOTANOP 0
#define UNOP 1
#define BINOP 2
#define BOTHOP 3
#define SPECOP 4
#define RUNOP 5
#define RBINOP 6
#define RBOTHOP 7

/* indicator if operand legal for reals */
#define REALOP TRUE
#define NOTREALOP FALSE
#define PTHOP TRUE
#define NOTPTHOP FALSE

/* operater width result pattern */
#define WIDNONE 0             /* no width result */
#define WIDONE 1              /* result width 1 (for logicals) */
#define WIDENONE 2            /* result one, but widen opands to wides */
#define WIDLEFT 3             /* left operand width of binary */
#define WIDMAX 4              /* max. of 2 operands */
#define WIDSUM 5              /* sum of operand width for concats */
#define WIDSELF 6             /* width self determining (like [] or un ~/-) */

/* specify section constants */
#define PTH_PAR 0             /* => */
#define PTH_FULL 1            /* *> */
#define PTH_NONE 2

#define POLAR_NONE 0
#define POLAR_PLUS 1
#define POLAR_MINUS 2

#define TCHK_SETUP 0
#define TCHK_HOLD 1
#define TCHK_WIDTH 2
#define TCHK_PERIOD 3
#define TCHK_SKEW 4
#define TCHK_RECOVERY 5
#define TCHK_NOCHANGE 6
#define TCHK_SETUPHOLD 7
#define TCHK_FULLSKEW 8
#define TCHK_RECREM 9
#define TCHK_REMOVAL 10
#define TCHK_TIMESKEW 11

/* for [edge ...] form allows list so multiple bits possible */
/* values must match acc_ pli values */
#define NOEDGE 0
#define EDGE01 0x1
#define EDGE10 0x2
#define EDGE0X 0x4
#define EDGEX1 0x8
#define EDGE1X 0x10
#define EDGEX0 0x20
/* these are or of relevants */
#define E_POSEDGE 0xd
#define E_NEGEDGE 0x32

#ifdef __XPROP__
#define XPROP_XEDGE_TO_0 0
#define XPROP_XEDGE_TO_1 1
#define XPROP_XEDGE_NOT_SET 2
#endif

/* delay union form for all delays after simulation preparation */
/* notice for non IS form no byte and halfword packed forms */
#define DT_NONE 0
#define DT_1V 1
#define DT_IS1V  2            /* all is forms have 1,2 and 8 byte forms */
#define DT_IS1V1 3
#define DT_IS1V2 4
#define DT_4V 5               /* 4v forms only for primtives not paths */ 
#define DT_IS4V 6
#define DT_IS4V1 7
#define DT_IS4V2 8
#define DT_16V 9              /* except for 1v all spec. delays need 15v */
#define DT_IS16V 10
#define DT_IS16V1 11
#define DT_IS16V2 12
#define DT_1X 13
#define DT_4X 14
#define DT_PTHDST 15
#define DT_CMPLST 16

/* for checking 0 and path delays, kinds of bad delays */
#define DGOOD 1
#define DBAD_NONE 2
#define DBAD_EXPR 3
#define DBAD_0 4
#define DBAD_MAYBE0 5

/* timing event types - what tested by not starting at 0 ? */
#define TE_THRD 2
#define TE_G 3
#define TE_CA 4
#define TE_WIRE 5
#define TE_BIDPATH 6
#define TE_MIPD_NCHG 7
#define TE_NBPA 8
#define TE_TFSETDEL 9
#define TE_SYNC 10
#define TE_TFPUTPDEL 11
#define TE_VPIPUTVDEL 12
#define TE_VPIDRVDEL 13
#define TE_VPICBDEL 14

/* AIV 01/17/07 - if nb assigns are handled seperately in compiler */
/* no need to malloc memory storage everytime */
#define TE_NBPA_ND 15
#define TE_NBPA_SCALAR 16
#define TE_NBPA_VARNDX 17
#define TE_MIPD_SCALAR_NCHG 18
#define TE_NO_THRD 19
#define TE_UNKN 20

#define DFLT_LOGFNAM "verilog.log"
#define DFLTDVFNAM "verilog.dump"
#define DFLTDPFNAM "dumpports.evcd"
#define DFLFSTFNAM "verilog.fst"
#define DFLTKEYFNAM "verilog.key"
#ifdef __XPROP__
#define DFLT_XPROPFNAM "cvc.xprop"
#define DFLT_NOT_ELIGIBLE_XPROPFNAM "cvc.xprop.excluded"
#endif

/* default toggle and cover report file names */
#define DEFAULT_TOGGLE_FILE_NAME "cvc.toggle"
#define DEFAULT_TGLDAT_OUT_FILE_NAME "verilog.tgldat"
#define DEFAULT_EVENT_FILE_NAME "cvc.events"
#define DEFAULT_STMT_FILE_NAME "cvc.stmts"

/* dumpvars action state */
#define DVST_NOTSETUP 0
#define DVST_DUMPING 1
#define DVST_NOTDUMPING 2
#define DVST_OVERLIMIT 3

/* baseline dump types for dumpvars */
#define DMPV_CHGONLY 0
#define DMPV_DMPALL 1
#define DMPV_DUMPX 2

/* dumpports action state - here kept in per file dp fildesc records */
#define DPST_NOTSETUP 0
#define DPST_DUMPING 1
#define DPST_NOTDUMPING 2
#define DPST_OVERLIMIT 3

/* baseline dump types for dumpports */
#define DMPP_CHGONLY 0
#define DMPP_DMPALL 1
#define DMPP_DUMPX 2

/* dumpports evaluation types */ 
#define DP_DRV_UNKN 0
#define DP_IN_1DRVR 1
#define DP_IN_DRVRS 2
#define DP_OUT_1DRVR 3
#define DP_OUT_DRVRS 4
#define DP_INOUT_1DRVR 5       /* just get val - one driver hi or lo */
#define DP_INOUT_DRVRS 6

/* delay control event filter processing types */
#define DCE_RNG_INST 0
#define DCE_INST 1
#define DCE_RNG_MONIT 2
#define DCE_MONIT 3
#define DCE_NONE 4
#define DCE_QCAF 5
#define DCE_RNG_QCAF 6
#define DCE_CBF 7
#define DCE_RNG_CBF 8
#define DCE_CBR 9
#define DCE_RNG_CBR 10
/* BEWARE these always require prevval - must be higher number than above */
#define DCE_PVC 11
#define DCE_RNG_PVC 12
#define DCE_CBVC 13
#define DCE_RNG_CBVC 14

#define ST_ND_PREVVAL DCE_PVC

/* slotend action masks - multiple can be on at time */
#define SE_TCHK_VIOLATION 1
#define SE_MONIT_CHG 0x2      /* definite chg including first time */
#define SE_MONIT_TRIGGER 0x4  /* monit chg where val saved (chk at end) */
/* FIXME - why is this never referenced */ 
#define SE_FMONIT_TRIGGER 0x8
#define SE_STROBE 0x10
#define SE_DUMPVARS 0x20      /* ON => some dumpvars action required */ 
#define SE_DUMPALL 0x40       /* need slot end dump all */
#define SE_DUMPON  0x800      /* need to turn dumping on at slot end */
#define SE_DUMPOFF 0x100      /* need to turn dumping off at slot end */
#define SE_TFROSYNC 0x200     /* have list of rosync events to process */
#define SE_VPIROSYNC 0x400    /* have list of vpi rw sync to process */

/* dumpports slot end flags stored in per file descriptor records */
#define SE_DUMPPORTS 0x1000   /* ON => some dumpports action required */
#define SE_DUMPPORTSALL 0x2000 /* need slot end dump all ports */
#define SE_DUMPPORTSON 0x4000  /* need to turn dumping on ports at slot end */
#define SE_DUMPPORTSOFF 0x8000 /* need slot end dumping ports off at slot end */
#define SE_TOGGLE 0x10000      /* need toggle coverage at slot end */

/* selectors for type of tran channel routine to use (low 3 bits) */ 
#define TRPROC_UNKN 0
#define TRPROC_BID 1
#define TRPROC_STBID 2
#define TRPROC_STWTYPBID 3
#define TRPROC_TRAN 4

/* type of gate acceleration - for selecting routine */
#define ACC_NONE 0
#define ACC_STD 1
#define ACC_BUFNOT 2
#define ACC_STIBUFNOT 3
#define ACC_4IGATE 4
#define ACC_ST4IGATE 5

/* internal vpi_ call back type classes */
#define CB_NONE 0
#define CB_VALCHG 1 
#define CB_DELAY 2
#define CB_ACTION 3

/* simulation (run) progress states */
#define SS_COMP 1
#define SS_LOAD 2
#define SS_RESET 3
#define SS_SIM 4

/* Cver supported error severity levels */
#define INFORM 0
#define WARN 1
#define ERROR 2
#define FATAL 3

/* per inst. masks for net nchg action byte array */
#define NCHG_DMPVARNOW 0x1    /* dumpvaring of this var inst on/off */
#define NCHG_DMPVNOTCHGED 0x2 /* var inst. not chged during current time */
#define NCHG_DMPVARED 0x4     /* var inst. dumpvared (setup) */
#define NCHG_ALL_CHGED 0x08   /* all var inst. bits chged (also if no lds) */
#define NCHG_DMPP_VARNOW 0x10 /* dump porting of this port inst on/off */
#define NCHG_DMPP_NOTCHGED 0x20 /* var inst for dump port not chged cur time */

/* AIV 09/05/03 consts for new fileio OS file descriptor streams support */
#define FIO_MSB 0x80000000
#define FIO_FD 0x7fffffff
#define FIO_STREAM_ST 3       /* first usable ver fio fd open file number */
#define SE_VPIROSYNC 0x400    /* have list of vpi rw sync to process */

/* AIV 12/02/03 constants for cfg get token */
/* FIXME ??? - needed here because cfg get tok in v ms but used in cver? */
#define CFG_UNKNOWN 0
#define CFG_ID 1
#define CFG_COMMA 2
#define CFG_SEMI 3
#define CFG_EOF 4
#define CFG_LIBRARY 5
#define CFG_CFG 6
#define CFG_INCLUDE 7
#define CFG_DESIGN 8
#define CFG_LIBLIST 9
#define CFG_INSTANCE 10
#define CFG_CELL 11
#define CFG_USE 12
#define CFG_ENDCFG 13
#define CFG_DEFAULT 14

/* max number of instances for the compiler to not split/merge modules */
#define NO_SPLIT_INST_MAX 500

/* option cfg and PLI tab file record types */
#define OCFG_UNKN 0
#define OCFG_MOD 1
#define OCFG_TREE 2
#define OCFG_INST 3           /* also full heirarchical name of nets */
/* exclude mod/tree/inst */
#define OCFG_EXL_MOD 4
#define OCFG_EXL_TREE 5
#define OCFG_EXL_INST 6

/* option cfg file attribute (really property) masks */
#define OCPRP_TGL 0x01
#define OCPRP_EVENT 0x02
#define OCPRP_STMT 0x04
/* PLI +acc+ per net specific from opt cfg fil to store into nets */ 
#define OCPRP_ACC_RW 0x08     /* for mod/inst/net, set net as +acc+1 */
#define OCPRP_ACC_CBK 0x10    /* for mod/inst/net set net as +acc+2 */
#define OCPRP_ACC_ANNPD 0x20  /* same as +acc+3 - same as ACCCBK now */
#define OCPRP_ACC_ANNGD 0x40  /* same as +acc+4 - same as ACCCBK now */
#ifdef __XPROP__
/* +xprop option types - sets for inst/mod - not per net */
/* SJM 10-03-11 these need to be masks because many for 1 inst possible */
#define OCPRP_XPROP 0x80      /* for mod/inst, use +xprop option */ 
#define OCPRP_XPROP2 0x100    /* for mod/inst, use +xprop option */ 
#define OCPRP_XPROP_AND_OR_X 0x200  /* for mod &, |, &&, || bit x preserve */
#endif

/* start of per inst midata area fixed value offsets */
#define MD_INUM 0             /* old __inum and the itree index number */ 
#define MD_MDP 1              /* ptr to the mdp struct cast from word */
#define MD_ITP 2              /* ptr to itree struct cast from word */
#define MD_UPIDP 3            /* ptr to one up itp struct cast from word */
#define MD_DOWNITPS 4         /* ptr to in its field in itree record cast */
#define MD_DPIP 5             /* this points to the dpinst el for dmpports */  

/* AIV 10/12/09 - was wasting a word here - only 6 MD_ items */
#define IDP_HD_BYTOFS (sizeof(word32) + sizeof(struct mod_t *)\
  + sizeof(struct itree_t *) + sizeof(word32) + sizeof(struct itree_t *)\
  + sizeof(struct dpinstel_t *))
#define IDP_HD_WOFS (IDP_HD_BYTOFS/WRDBYTES)

/* interactive debugger may have to grow max size */
#define IDP_IA_GROW_MAX 10

/* string IDP area size for each string in words */
#define STR_IDP_WLEN 3
/* string pointer idp offset from np->nva_ofs */
#define STR_IDP_OFS 0
/* string current size idp ofs from np->nva_ofs */
#define STR_IDP_NDX_OFS 1
/* string current malloc size idp ofs from np->nva_ofs */
#define STR_IDP_SIZE_OFS 2

/* string init number of chars */
#define STR_INIT_CHARS 32

/* DPI types */
#define DPI_UNKN 0;
#define DPI_IMPORT 1
#define DPI_EXPORT 2
#define DPI_CVC_PTRS 3

/* DPI language types */
#define DPI_LANG_C 1

/* DPI import property */
#define DPI_IMPRT_UNKN 0;
#define DPI_IMPRT_CONTEXT 1
#define DPI_IMPRT_PURE 2

/* DPI task/funcion */
#define DPI_TF_UNKN 0;
#define DPI_TF_TASK 1
#define DPI_TF_FUNC 2

/* DPI interpreter wrapper call defines */
/* SV DPI Verilog side C types */
#define SV_UNKN 0
/* 2 value c/c++ types */
#define SV_BIT 1              /* this is svBit svdpi.h type (0 or 1) u char */
#define SV_BYTE 2
#define SV_SHORTCINT 3
#define SV_CINT 4
#define SV_LONGCINT 5
#define SV_SHORTREAL 6        /* currently unused */ 
#define SV_REAL 7
#define SV_BITVECVAL 8        /* ptr to 2 state area */
#define SV_CHANDLE 9          /* this is const void ptr */
#define SV_VOID 10            /* void? */
#define SV_VOID_PTR 11        /* void ptr? */
/* 4 state */
#define SV_LOGIC 12           /* 4 state scalar - this is not sreps */
#define SV_LOGICVECVAL 13     /* ptr to 4 state a/b area */
#define SV_CHAR_PTR 14        /* char * string */

/* SJM 07/31/01 - need system type def. include files for 64 bit types */
#include <time.h>

/* various forward references */
struct sy_t;
struct st_t;
struct mod_pin_t;
struct thread_t;
struct tchk_t;
struct tchg_t;
struct fmonlst_t;
struct flowg_t;

/* data structure for keywords and command line/file options */
struct namlst_t {
 int32 namid;
 char *lnam;
};

/* SJM 06/03/01 - to prepare for 64 bits union to avoid int32 to ptr cast */
/* SJM 10/12/04 - can't use p because need index into contab not addr */
union intptr_u {
 int32 i;
 int32 xvi;
};

/* SJM 08/22/01 - must be at top for new expr node union */
union pck_u {
 word32 *wp;
 hword *hwp;
 byte *bp;
 double *dp;
};

/* data struct for help message line tables - hnum is namlst_t namid */
struct hlplst_t {
 /* LOOKATME - why is this unused */
 int32 hnamid;
 char **hmsgtab;
};

/* list of sdf task enable stmts along with module stmt appears in */
struct sdf_tskenlst_t {
 struct st_t *sdf_annotate_stp;
 struct mod_t *sdf_stp_mod;
 struct sdf_tskenlst_t *sdf_tsken_nxt;
};

struct sdfnamlst_t { 
 char *fnam;
 char *scopnam;
 char *optfnam;
 int32 opt_slcnt;
 struct sdfnamlst_t *sdfnamnxt;
};

struct optlst_t {
 unsigned optfnam_ind : 16;
 unsigned is_bmark : 1;       /* special -f markers for vpi_ */         
 unsigned is_emark : 1;
 unsigned is_argv : 1;
 unsigned argv_done : 1;
 int32 optlin_cnt;
 int32 optnum;
 int32 optlev;
 char *opt;
 char **dargv;
 struct optlst_t *optlnxt;
};

/* data structure for input file/`define/`include stack */
/* could be union but not too many ? */
struct vinstk_t {
 int32 vilin_cnt;
 int32 vichplen;              /* if not -1, len + 1 must be freed */
 word32 vifnam_ind;
 FILE *vi_s;
 char *vichp_beg;             /* beginning of macro string */  
 char *vichp;                 /* macro string current char */
};

/* cfg option file stmt ver obj and it tok typ */
struct oc_vtok_t {
 unsigned ocs_toctyp : 8;
 int32 ebi1;                 /* exclude lsb */
 int32 ebi2;                 /* exclude rsb */
 int32 tok_lcnt;
 char *ocs_toknam;
 struct oc_vtok_t *ocvtnxt;
};

/* cfg attribute record */
struct ocfg_stmt_t {
 unsigned ocfgtyp : 8;
 int32 tree_level_val;
 struct oc_vtok_t *oc_ver_objs; /* list of insts, mods, etc tokens */
 struct oc_vtok_t *oc_props;/* list of opt cfg attribs/props as nam */
 struct ocfg_stmt_t *ocsnxt;
};

/* option cfg file and pli.tab file record */
struct ocfil_lst_t {
 char *ocfnam;
 struct ocfg_stmt_t *oc_stmts;/* this opt fil's attr stmts */  
 struct ocfil_lst_t *oclnxt;
};

/* init toggle recording values from .tgldat file record */
//SJM 04-18-13 LOOKATME? - think should also have path to field that gets
//added as prefix to every name in file
struct tgldat_in_lst_t { 
 char *in_tgldat_fnam;
 struct tgldat_in_lst_t *tgldat_in_nxt;
};

/* net toggle fields */
struct net_toggle_t {
 /* access per inst net's recorded tgl bits by using this ofset in idp area */
 size_t toggle_ofs;           /* toggle offset */
 int32 *n_peri_tgl_on_se_list;/* if T this inum on slot's end chged list */
 /* still need to track all insts - just not in report */
 byte *peri_tgl_on;           /* optconfig record tgl on per inst (byte) */
 /* if per inst bit tgl report nil, then all bits */
 word32 *peribits_tgl_rpt_exclude; /* per inst bit tgl report excl (bit) tab */
 word32 **peribits_drvn_const;/* per inst ptr to per bit driven const bit */
};

/* P1364 2001 cfg include structs */
/* list of map files - uses map.lib in CWD if none from options */
struct mapfiles_t {
 char *mapfnam;
 struct mapfiles_t *mapfnxt;
};

/* order list of config element names */
struct cfgnamlst_t {
 char *nam;
 struct cfgnamlst_t *cnlnxt;
};

/* describes component of path during wild card expansion */
struct xpndfile_t {
 unsigned wildcard: 2;        /* T=> if it contains a wild char, *, ? or ... */
 unsigned incall : 1;         /* include the entire dir, ends in '/' */
 int32 nmatch;                /* the number of matched files */
 int32 level;                 /* current directory level */
 char *fpat;                  /* the original pattern per dir, split by '/' */
 struct xpndfile_t *xpfnxt;   /* next part of original pattern */
};

/* record for library element (after expand, all wild cards removed) */
struct libel_t {
 unsigned lbelsrc_rd : 1;     /* T => expanded lib file name src all read */
 unsigned expanded : 1;       /* T => file has been expanded  */ 
 char *lbefnam; 
 struct libcellndx_t **lbcelndx; /* byte offset of cell names for seeking */
 struct symtab_t *lbel_sytab; /* symbol table of cells in file */
 struct libel_t *lbenxt;
};

/* cfg library record - sort of corresponds to -v/y data record */ 
struct cfglib_t {
 unsigned lbsrc_rd : 1;       /* T => lib src files already read */
 unsigned sym_added : 1;      /* T => sym table has been read */
 int32 cfglb_lno;
 char *lbname;                /* library name */ 
 struct libel_t *lbels;       /* list of library file path spec elements */
 struct cfglib_t *lbnxt;      /* pointer to the next library */
 char *cfglb_fnam;            /* location of library in src needed */
 struct cfg_t *cfgnxt;
};

/* config body rule record */
struct cfgrule_t {
 unsigned rultyp : 8;         /* type - cfg symbol number */
 unsigned use_rule_cfg : 1;   /* T => use clause config form */ 
 unsigned matched : 1;        /* T => rule was bound at least once */ 
 unsigned is_use : 1;         /* T => 'use' else 'liblist' */ 
 int32 inam_comp_lasti;       /* number of components in XMR inst path */
 int32 rul_lno;
 char *objnam;                /* inst clause: [XMR inst path] */ 
 char *libnam;                /* cell clause: <lib name>.[cell name] */
 char *rul_use_libnam;        /* use <lib name.>[cell name][:config] */
 char *rul_use_celnam;
 char **inam_comptab;         /* table of inst clause XMR components */

 struct cfgnamlst_t *rul_libs;/* liblist clause - just list of libraries */
 struct cfgrule_t *rulnxt;
};

/* record for list of config design cell identifiers */
struct cfgdes_t {
 char *deslbnam;          /* name of config design library */
 struct cfglib_t *deslbp; /* ptr to config design library */
 char *topmodnam;         /* name of top level cell (type) */
 struct cfgdes_t *desnxt;  
};

/* record for each cfg block */
struct cfg_t {
 char *cfgnam;                /* name of the cfg */
 struct cfgdes_t *cfgdeslist; /* list of config design [lib].[cell]s */

 /* SJM 12/11/03 - notice preserving exact order of rules critical */
 struct cfgrule_t *cfgrules;  /* ordered list of config rules */
 struct cfgrule_t *cfgdflt;   /* default lib list if rules find no matches */
 char *cfg_fnam;
 int32 cfg_lno;
 struct cfg_t *cfgnxt;
};

/* for debugger include file and last included place */
struct incloc_t {
 int32 inc_fnind;             /* in_fils index of included file */
 int32 incfrom_fnind;         /* in_fils index file included from */
 int32 incfrom_lcnt;          /* lin cnt where included */ 
 struct incloc_t *inclocnxt;
};

/* doubly linked list for undefined modules */
struct undef_t {
 struct sy_t *msyp;
 int32 dfi;
 char *modnam;
 struct undef_t *undefprev;
 struct undef_t *undefnxt;
};

/* struct for files in ylib - to avoid opening if not needed */
struct mydir_t {
 unsigned ydirfnam_ind : 16;
 unsigned ylbxi : 16;         /* ndx in lbexts (-1 if none), -2 no match */
 char *dirfnam;
};

/* -y and -v file list */
struct vylib_t {
 unsigned vyfnam_ind : 16;    /* for rescanning file ind or num dir files */
 unsigned vytyp : 8;          /* 'v' for -v andd 'y' for -y */
 union {
  char *vyfnam;               /* file name */ 
  char *vydirpth;             /* for -y directory, directory path */
 } vyu;
 struct mydir_t *yfiles;      /* for -y header of file list */
 struct vylib_t *vynxt;
};

/* struct for multi-channel descriptors - need to save file name */ 
struct mcchan_t { 
 FILE *mc_s; 
 char *mc_fnam;
};

/* ver fd number record for new 2001 P1364 file io package */
struct fiofd_t {
 unsigned fd_error : 1;      /* error indicator */
 char *fd_name;              /* name of stdio file */
 FILE *fd_s;                 /* corresponding OS FILE * descriptor */ 
};

/* debugger source file cache line start location rec */
struct filpos_t {
 int32 nlines;
 int32 *lpostab;
};

/* formal macro argument list */
struct macarg_t {
 char *macargnam;
 struct macarg_t *macargnxt;
};

/* macro expansion templace list */
struct macexp_t {
 char *leading_str;
 int32 leadlen;
 int32 ins_argno;
 struct macexp_t *macexpnxt;
};

/* arg macro record */ 
struct amac_t { 
 int32 num_formal_args;
 struct macexp_t *amxp;
};

/* operator info struct for predefined table (index by op. symbol number) */
/* Verilog ops always associate left */
struct opinfo_t {
 unsigned opclass : 8;
 unsigned realop : 8;
 unsigned stringop : 1;       /* T => op legal for SV strings */
 unsigned pthexpop: 8;        /* T => op legal in SDPD condional expr. */
 unsigned reswid : 8;
 char *opnam;
};

/* value in q for $q_ system tasks */
struct q_val_t {
 int32 job_id;
 int32 inform_id;
 word64 enter_tim;
};

/* q header record - linked list of all queues */
struct q_hdr_t {
 unsigned q_fifo : 1;       /* T => fifo, F => lifo */
 int32 q_id;                /* user passed ID */
 int32 q_hdr;               /* index of current head */
 int32 q_tail;              /* index of current tail */
 int32 q_maxlen;            /* maximum length of queue */
 int32 q_size;              /* need to store size for q_exam */
 int32 q_maxsize;           /* for entire run, max size of q */
 struct q_val_t *qarr;      /* table contain queue */
 word64 q_minwait;          /* shortest wait (min) of all els. ever in Q */
 struct q_hdr_t *qhdrnxt; 
};

/* history suspended statement control record */
struct hctrl_t {
 int32 hc_lini;           /* line loc. in history of statement */ 
 int32 hc_ifi; 
 int32 hc_numglbs;        /* size of table */
 struct st_t *hc_stp;     /* initial style statement list */
 t_midat *hc_idp;         /* itree loc. runs in if reenabled */
 struct thread_t *hc_thp; /* associated thread */ 
 struct hctrl_t *hc_nxt;  /* list next for non history traversing */
 struct hctrl_t *hc_prev; /* and previous */
 struct iahist_t *hc_iahp;/* ptr to history element if history on */
 struct dceauxlst_t *hc_dcelst; /* aux. list of per inst iact dces to free */ 
 struct gref_t *hc_grtab; /* table of any grefs used in this statement */ 
};

/* interactive history command record */
struct iahist_t { 
 char *iah_lp;            /* history line (may have embedded new lines) */
 struct hctrl_t *iah_hcp; /* parsed suspended stmt control record */
 struct itree_t *iah_iti; /* for non immed. save original itree loc. */
};

/* parallel to expr table during expr collect id name info struct */  
struct expridtab_t {
 char *idnam;
 int32 idfldwid;
 int32 idfnam_ind;
 int32 idlin_cnt;
};

/* structs for expressions */
union l_u {
 struct expr_t *x;
 int32 xi; /* for compile/save changed to indices */
 struct sy_t *sy;
 int32 si; /* for compile/save changed to indices */
};

union r_u {
 struct expr_t *x;
 int32 xvi;                   /* wrd index into constant tab */
 union pck_u iop_ptr;         /* for special malloc iopt node ptr to area */
 struct gref_t *grp;          /* during compile/exec - ptr to gref */
 int32 gri;                   /* for compile/save index */
 char *qnchp;                 /* for local qual. name, pointer to name */ 
};

/* expression size or tf rec union */
union sz_u {
 int32 xclen;
 struct tfrec_t *xfrec;
 void *vpi_sysf_datap;        /* for vpi_ sysf get/put data routine */
};

/* expression tree storage - eventually will fit in 12 bytes */
struct expr_t {
 /* operator token type - leaf node if var or number */
 /* AIV 09/30/10 - this needs to be size 9 for new SV types */
 /* SJM 05-15-14 - need 10 since VHDL keywords start at 512 */
 unsigned optyp : 10;         /* token type of node */
 unsigned has_sign : 1;       /* T => result must be signed */
 unsigned rel_ndssign : 1;    /* T => 1 bit result relational needs sign */
 unsigned is_string : 1;      /* T => constant in src as string (quoted) */
 unsigned is_sv_string : 1;   /* T => expr is a SystemVerilog 'string' */
 unsigned unsiznum : 1;       /* T => constant is unsized */
 unsigned ibase : 3;          /* for sized no., base char. */
 unsigned sizdflt : 1;        /* T => '[base] form but no width */
 unsigned is_real : 1;        /* T => expr. value is real number */
 unsigned cnvt_to_real : 1;   /* T => non real operand of real expr */
 unsigned cnvt_to_string : 1; /* T => convert to SV string */
 unsigned x_is2state : 1;     /* T => can be evaled as 2 state (no b part) */
 unsigned unsgn_widen : 1;    /* T => for cases unsigned widen if needed */
 unsigned consubxpr : 1;      /* T => node will evaluate to number */
 unsigned consub_is : 1;      /* T => node will eval to IS number */
 unsigned con_fcall : 1;      /* T => in const cntxt, call of const func */
 unsigned folded : 1;         /* T => const. folded (also empty cat rep rem) */
 unsigned getpatlhs : 1;      /* T => expressions is lhs of get pattern */
 unsigned ind_noth0 : 1;      /* T => constant index has been normalized */
 unsigned x_multfi : 1;       /* T => expr has multi fan-in or stren wire */
 unsigned tf_isrw : 1;        /* T => for user tf arg. - assignable (rw) */
 unsigned x_islhs : 1;        /* T => expr. is lhs */
 unsigned locqualnam : 1;     /* T => if printing name is local qualified */
 unsigned lhsx_ndel : 1;      /* T => wire in lhs expr. has net delay */
 unsigned x_stren : 1;        /* T => expr. is strength wire/bs/ps */
 unsigned unc_pull : 2;       /* unc. pull directive value for OPEMPTY */
 unsigned folded_ndx : 1;     /* constant value for multi dim array folded */
 unsigned arr_select : 1;     /* last dimension access of array is bsel/psel */
 unsigned post_inc_dec : 1;   /* T => is id++ not ++id */
 unsigned unbas_unsiz_num : 1;/* SV unsized /unbased '0 number */
 unsigned tgl_cant_be_const: 1;/* T => for tgl, know rhs can't be const */
 unsigned is_loaded : 1;      /* T => expr is loaded (passed) to wrapper */
 unsigned is_norm_ndx : 1;    /* T => expr is already normalize ndx */
 union sz_u szu;              /* size of func tf rec. union */ 
 union l_u lu;                /* left sub expr. or symbol union */
 union r_u ru;                /* right sub expr. or ptr. to value union */
 struct expr_t *next_ndx;     /* pointer to next mult-dim index (select) */
};

struct xstk_t {
 int32 xslen;                 /* number of bits required to store */
 int32 xsawlen;               /* word32 length of a/b half of alloced size */
 word32 *ap;                  /* a part of value but must be contigous */
 word32 *bp;                  /* b part of value */
};

struct exprlst_t {
#ifdef __XPROP__
 int32 num_xmatch;            /* number of x/zs in this case item */
#endif
 struct expr_t *xp;
 struct exprlst_t *xpnxt;
};

/* for new ver 2001 var (not wire) decl initialize assign list */
struct varinitlst_t {
 struct sy_t *init_syp;
 struct expr_t *init_xp;
 struct varinitlst_t *varinitnxt;
};

/* struct for storing # delays but not instance pound params */
struct paramlst_t {
 struct expr_t *plxndp;
 struct paramlst_t *pmlnxt;
};

/* struct for storing defparams - list is design wide */
struct dfparam_t {
 unsigned dfp_local : 1;      /* T => defparam is local or in top mod */
 unsigned dfp_rooted : 1;     /* T => rooted lhs gref */
 unsigned dfp_mustsplit : 1;  /* T = mst split rng cat lhs dest. param */
 unsigned dfp_done : 1;       /* during splitting, done with this one */
 unsigned dfp_has_idents : 1; /* T => identical to other rooted defparam */
 unsigned dfp_in_gen : 1;     /* T => defparam inside gen blk (always down) */
 unsigned dfp_was_in_gen : 1; /* T => for 2nd pass in gblk history */
 unsigned dfp_gblk_in_pth : 1;/* T => defparam has gen blk in pth (down) */
 unsigned dfpfnam_ind : 16;
 int32 dfplin_cnt;
 int32 last_dfpi;             /* last element of path */
 int32 *dfpiis;               /* array of in its indices for path of defp */

 struct expr_t *dfpxlhs;
 struct expr_t *dfpxrhs;
 struct gref_t *dfp_grp;      /* for non local defparams, assoc. lhs gref */
 struct mod_t *dfp_in_mdp;    /* module defparam stmt in */ 
 struct dfparam_t *dfpnxt;
 char *gdfpnam;               /* lhs name from gref */
 struct sy_t *targsyp;        /* target symbol from gref */
 struct dfparam_t *idntmastdfp;/* ptr to master if >1 with identical path */
 struct dfparam_t *idntnxt;   /* list from master of identicals path */
 struct dfparam_t *rooted_dfps;/* work for converting downward to rooted */
 struct itree_t *indfp_itp;   /* for rooted, itree place rhs evaled in */ 
 struct task_t *dfptskp;      /* if non NULL, task target declared in */
 struct genblk_t *dfp_gblk_in; /* for local def params, gblk in */ 
};

/* per type delay storage - 1 array acess during scheduling */
union del_u {
 word64 *d1v;                 /* 1 constant (non 0) delay value */
 word64 *dis1v;               /* 1 constant (IS form maybe some 0) delay */
 byte *dis1v1;                /* 1 constant IS fits in one byte */
 hword *dis1v2;               /* 1 constant IS fits in two byte */
 word64 *d4v;                 /* 4 value constant delay table */
 word64 *dis4v;               /* 4 constant (IS form maybe some 0) delay */
 byte *dis4v1;                /* 4 constant IS fits in one byte */
 hword *dis4v2;               /* 4 constant IS fits in two byte */
 word64 *d16v;                /* 16 constant IS form */
 word64 *dis16v;              /* 16 constant (IS form) delay */
 byte *dis16v1;               /* 16 constant IS fits in one byte */
 hword *dis16v2;              /* 16 constant IS fits in two bytes */
 struct expr_t *d1x;          /* 1 delay expr. */
 struct expr_t **d4x;         /* array of 4 expression ptrs */
 struct pthdst_t **pb_pthdst; /* per bit path dest. ptr to same dst. src */
 struct paramlst_t *pdels;    /* original compile time # delay form */
};

/* input instance structure before known whether gate or cell */
struct cell_pin_t {
 struct expr_t *cpxnd;        /* connecting expression root node */
 word32 cpfnam_ind;           /* file symbol defined in */
 int32 cplin_cnt;             /* def. line no. */
 char *pnam;                  /* probably no symbol table when read */
 struct cell_pin_t *cpnxt;
};

struct namparam_t {
 struct expr_t *pxndp;        /* parameter value as expr. */
 word32 prmfnam_ind;          /* file pound parameter appears in */
 int32 prmlin_cnt;            /* line pound parameter defined on */
 char *pnam;                  /* name as string - no sym table when read */
 struct namparam_t *nprmnxt;
};

/* record to store attributes - table of each from attribute inst */
struct attr_t {
 unsigned attr_tok : 8;       /* token attribute on */
 unsigned attr_seen : 1;      /* turn on when see attr of attr tok type */
 unsigned attr_fnind : 16;    /* file attribute instance defined at */

 int32 attrlin_cnt;           /* and line no. */
 char *attrnam;               /* name but before parsed entire attr inst str */ 
 struct expr_t *attr_xp;      /* expr - nil if no value expr */
 struct attr_t *attrnxt;
};

/* source location struct for saving cell port line numbers */
struct srcloc_t {
 word32 sl_fnam_ind;
 int32 sl_lin_cnt;
};

/* compile time cell or gate contents */
struct cell_t {
 unsigned c_hasst : 1;        /* T => strength appears in source */
 unsigned c_stval : 6;        /* (3 bit 0 st. and 3 bit 1 st. */
 unsigned cp_explicit : 1;    /* T => all explicit connection list */
 unsigned c_named : 1;        /* T => instance is named */
 unsigned c_iscell : 1;       /* T => this is a timing lib. cell */  
 struct sy_t *csym;
 struct sy_t *cmsym;          /* module type symbol */
 struct cell_t *cnxt;
 struct expr_t *cx1, *cx2;    /* for arrays of gates/insts, the range */
 struct namparam_t *c_nparms;
 struct attr_t *cattrs;       /* attrs for cell - moved later */
 struct cell_pin_t *cpins;
};

/* list for blocks of allocated cells for fast block freeing */
struct cpblk_t {
 struct cell_t *cpblks;
 struct cpblk_t *cpblknxt; 
};

/* list for blocks of allocated cell pins for fast block freeing */
struct cppblk_t {
 struct cell_pin_t *cppblks;
 struct cppblk_t *cppblknxt;
};

/* list of tree node blocks */
struct tnblk_t {
 struct tnode_t *tnblks;
 struct tnblk_t *tnblknxt;
};

struct cpnblk_t {
 char *cpnblks;
 char *cpn_start_sp, *cpn_end_sp;
 struct cpnblk_t *cpnblknxt;
}; 

/* aux record for mod gates or insts that are array form */
/* SJM 04-21-10 - now just pointed to from gates and insts */
struct gia_aux_t {
 unsigned gia_is_base_first : 1; /* first one in array order */
 unsigned gia_xpnd : 1;       /* T => inst/gate arr xpnded to per bit */
 unsigned gia_rng_has_pnd : 1;/* T => range has passed pound param */
 int32 gia1, gia2;            /* evaluated range - expr may chg */
 int32 gia_bi;                /* base mgates or minsts index */
 struct expr_t *giax1, *giax2;/* src constant rng exprs from cell */
 struct expr_t **giapins_ptr; /* ptr to tab of original g/i pin expressions */
 struct sy_t *gia_base_syp;   /* original src base sym (stays in symtab) */
};

/* run time module instance contents */
struct inst_t {
 unsigned ip_explicit : 1;
 unsigned pprm_explicit : 1;  /* has explicit form pound params */
 unsigned i_iscell : 1;       /* instance is a cell */
 unsigned i_pnddefsplit : 1;     /* T => must pound param split */
 struct sy_t *isym;
 struct sy_t *imsym;          /* module type symbol */
 struct gia_aux_t *i_giap;    /* arr of insts info gia aux record */
 struct expr_t **ipxprtab;    /* inst. pound param expr. table, nil for none */
 struct attr_t *iattrs;       /* attribute table for inst. */
 struct expr_t **ipins;       /* ptr to array of port expr ptrs */
 struct expr_t ***pb_ipins_tab; /* if non nil, ptr to pb sep pin expr tab */ 
};

/* SJM 11-09-08 records for new generate forms */
struct gen_for_t {
 int32 ngenblks;
 struct st_t *gforassgn;
 struct expr_t *gfortermx;
 struct st_t *gforinc;
 struct genblk_t **gentab;
 struct genblk_t *src_gforblkp;
};

struct gen_if_t {
 unsigned no_if_beg : 1;      /* T => really a begin-end (added if (1) */ 
 int ngenblks;                /* for if max 1 (none -1) but makes consistent */
 struct expr_t *condx;
 struct genblk_t *src_then_gblkp;
 struct genblk_t *src_else_gblkp;
 struct genblk_t **gentab;    /* tab for xmr indexing but if used size 1 */
};

struct gen_csitem_t {
 unsigned gdflt_i : 1;
 struct exprlst_t *csixlst;
 struct genblk_t *gen_csiblkp;
 struct gen_csitem_t *gcsinxt;
};

struct gen_case_t {
 int32 ngenblks;            /* for if max 1 (none -1) but makes consistent */
 struct expr_t *csx;
 struct gen_csitem_t *gcsitems;/* first item always default: place holder */ 
 struct genblk_t **gentab;    /* tab for xmr indexing but if used size 1 */
};

/* for gened insts need struct because also need the srcloc tab for mod */
struct inst_gen_t {
 struct inst_t *ip;
 struct srcloc_t *srclocp;
};

/* union of all generate forms and Verilog module (body) items */
union giu_u {
 struct genblk_t *gi_gblkp;   /* for gen form blks list of gen forms */
 struct gen_for_t *gi_gforp;  /* gen specific elab time for loop */
 struct gen_if_t *gi_gifp;    /* gen specific elab time if form */
 struct gen_case_t *gi_gcasp; /* gen specific elab time case form */
 struct net_t *gi_np;
 struct ialst_t *gi_ialp;
 struct conta_t *gi_cap;
 struct dfparam_t *gi_dfp;   /* union for dfparm decl in gen blk */
 struct gref_t *gi_grp;       /* XMRs used in gen blks are mved gen items */
 struct task_t *gi_tskp;      /* for task and func gen mod items */
 struct cell_t *gi_cp;        /* src read time inst/gate gen item */
 struct inst_gen_t *gi_igp;   /* fixup time inst struct */
 struct gate_t *gi_gp;        /* gen elab time gate */    
};

/* gen item (form) record - for lists inside of gen blks - also used in xpnd */
struct genitem_t { 
 unsigned gityp : 8; 
 unsigned gi_fnam_ind : 16;
 int32 gilin_cnt;
 union giu_u giu;             /* in src form, ptr to gen item */
 char *gi_nam;                /* in gen blk in src name of item */
 struct genitem_t *gened_nxt; /* by gen item type, mod to add to nl list */
 struct genitem_t *geninxt;
};

/* gen blk header record - has a symbol table and points to one gen item */
struct genblk_t { 
 unsigned genblk_fnam_ind : 16;
 unsigned unnamed_gblk : 1;
 unsigned gblk_has_grefs : 1;
 unsigned gblk_in_gfor : 1;
 int32 genblk_lin_cnt;
 int32 gen_id;
 int32 genv_ndx;               /* for genfor need gentab index for name too */
 char *gblknam;
 struct symtab_t *gblk_sytab;
 struct mod_t *gblk_mod_in;    /* mdp that this gblk in defined in */
 struct net_t *gvnp;           /* genblk's inner genvar if one exists */
 struct genitem_t *gitems;     /* normal gen items from LRM */
 struct genitem_t *last_gitem;
 struct task_t *gblk_tsks;  /* for tsks (now all t/f/lb need gblk tsk list) */
 struct task_t *end_gblk_tsk; 
 struct genitem_t *gref_gitems;/* gref globals used in gen block */
 struct genitem_t *last_gref_gitem;
 struct genitem_t *dfp_gitems; /* defparams appearing in gen blocks */
 struct genitem_t *last_dfp_gitem;
};

/* sensitivity list for generate parameters to check for changes */
struct gen_sens_t {
 struct net_t *gsen_prmnp;
 word32 *gsen_owp;
 struct gen_sens_t *gsenxt;
};
 
/* as if flattened instance structure - should use inum arrays instead ? */
/* think this can be smaller but per mod. inst. array better ? */
struct itree_t {
 int32 itinum;
 t_midat *it_idp;             /* RT (after v_prp) ptr to mod var peri data */
 struct itree_t *up_it;       /* containing itree inst. */
 struct itree_t *in_its;      /* array of low itree elements */
 struct inst_t *itip;         /* corresponding inst_t info */
};

/* event info struct used to make compiler runtime static events */
/* SJM 04/08/08 - now emit into design wide area - tn's not around */
struct ctev_t {
 unsigned has_wire_ev : 1;    /* is mipd wire event */
 unsigned wrapper_type : 3;   /* type of generic event wrapper handle type */
 unsigned ct_comlab_typ : 6;  /* comlab type (from original tn) */
 unsigned del_rep : 5;        /* type of delay */
 unsigned srep : 6;           /* srep type used for nb storage */
 unsigned in_list : 1;        /* T => already in mdp->ctev_list */
 struct mod_t *mdp;           /* module this event is in */
 int32 ct_el_ndx;             /* index of the element (from original tn) */ 
 int32 nb_fg_num;             /* if non-blocking - its fg number */
 int32 path_ndx;              /* path index */
 int32 ctev_ndx;              /* the number (indentifier) for this event */
 int32 ca_ndx;                /* conta ndx needed by asmlnk tev write proc */
 int32 wev_ndx;               /* wire evnt ndx need by asmlnk tev write proc */
 int32 dctrl_ndx;             /* delay control merged ndx (always @ blocks) */
 int32 nb_rhs_byt_size;       /* byte size of nb rhs storage (-1 if none) */
 size_t ctev_idp_ofs;         /* idp offset of this delay (tev) */
 union del_u du;              /* delay for this event */
 struct gate_t *ctev_gp;      /* (unused?) gate ptr in ctev */
 struct ctev_t *ctevnxt;      /* list used by asmlnk writing code */
};

/* gate contents after fixup separation */
struct gate_t {
 unsigned gpnum : 14;         /* number of gate ports (limit 16k) */
 unsigned g_class : 3;        /* gate class for processing case */
 unsigned g_hasst : 1;        /* T => stren in src or tran(if) cycle break */
 unsigned g_stval : 6;        /* (3 bit each 0 and 1 st.) <ST:ST> if none */
 unsigned g_delrep : 5;
 unsigned g_unam : 1;         /* primitive has no instance name */
 unsigned g_gone : 1;         /* gate removed, no state */ 
 unsigned g_pdst : 1;         /* T => gate drives del/pth */
 size_t gate_out_ofs;         /* gate output value index into idp */
 struct ctev_t *ctevp;
 union del_u g_du;            /* per type delay union */
 struct sy_t *gsym;
 struct sy_t *gmsym;          /* gate type symbol */
 struct gia_aux_t *g_giap;    /* arr of gates info gia aux record */
 size_t gstate_ofs;           /* idp index storage of state vector */
 size_t schd_tevs_ofs;        /* idp index storage of scheduled events ndxes */
 struct attr_t *gattrs;       /* optional gate attribute */
 struct expr_t **gpins;       /* ptr to table of input port expr ptrs */

 /* routine to eval gate on input change */
 void (*gchg_func)(register struct gate_t *, register word32);
};

union pbca_u {
 struct conta_t *pbcaps;      /* for rhs cat per bit conta tab for sim */
 struct conta_t *mast_cap;    /* for per bit element, ptr to master */
 struct conta_t *canxt;       /* canxt only need up to late fixup 2 tab bld */ 
};

/* notice 1 bit ca's are simulated as gates */
struct conta_t {
 struct sy_t *casym;
 unsigned ca_hasst : 1;
 unsigned ca_stval : 6;       /* (3 bit 0 st. and 3 bit 1 st. */
 unsigned ca_delrep : 5;
 unsigned ca_4vdel : 1;       /* T => delay 4v so need to eval new_gateval */
 unsigned ca_gone : 1;        /* continuous assign could be removed */
 unsigned ca_pb_sim : 1;      /* T => in src rhs concat simulates as PB */
 unsigned ca_pb_el : 1;       /* T => this is a per bit el pb fld is master */
 unsigned is_loaded : 1;      /* T => conta is loaded (passed) to wrapper */
 unsigned is_printed : 1;     /* T => compiled global is printed */
 int32 enter_cndx;            /* index for enter del assign place */
 struct flowg_t *flowg;       /* aux flow graph for conta */
 struct ctev_t *ctevp;
 union del_u ca_du;           /* per type delay table (only in master) */
 struct expr_t *lhsx;
 struct expr_t *rhsx;
 size_t caschd_tevs_ofs;       /* per inst. idp ofs scheduled event ndx array */
 size_t ca_drv_ofs;            /* idp ofs rhs drive a/b values if needed */
 size_t schd_drv_ofs;          /* idp scheduled value */
 union pbca_u pbcau;          /* up or down tab rhs cat decomposed PB val */ 
};

/* net storage */
/* compilation specific net auxiliary fields */
struct ncomp_t {
 /* compile time only flags */
 unsigned n_iotypknown : 1;
 unsigned n_wirtypknown : 1;
 unsigned n_rngknown : 1;     /* needed to separate range in i/o/wire decls */
 unsigned n_impldecl : 1;     /* declared implicitly */
 unsigned n_in_gia_rng : 1;   /* in array of g/i range expression */
 unsigned n_spltstate : 2;    /* scalared/vectored splitting of wire */
 unsigned n_onrhs : 1;        /* appears on some rhs (also declarative) */ 
 unsigned n_onlhs : 1;        /* appears on some lhs */
 unsigned n_2ndonlhs : 1;     /* T => more than 1 on lhs (for in to inout) */
 unsigned num_prtconns : 2;   /* count to 2 of no. of ports wire conns to */
 unsigned n_widthdet : 1;     /* T => parm is width determing - no IS form */
 unsigned n_indir_widthdet : 1; /* T => parm passed down to width det */
 unsigned p_setby_defprm : 1; /* T => can't recalc since set by def param*/
 unsigned p_canbe_setby_pndprm : 1; /* T => at least 1 inst set by pnd param */
 unsigned p_specparam : 1;    /* T => specify parameter */
 unsigned p_rhs_has_param : 1;/* T => param def rhs contains param */
 unsigned p_locparam : 1;     /* T => local parameter (never # or def) */
 unsigned p_genvar : 1;       /* T => local param is really a genvar */
 unsigned prngdecl : 1;       /* T => range declared in source */
 unsigned ptypdecl : 1;       /* T => type declared in source */
 unsigned psigndecl : 1;      /* T => signed keyword declared in source */
 unsigned parm_srep : 6;      /* for parameter n_dels_u original expr rep */ 
 unsigned pbase : 3;          /* base of original rhs */
 unsigned pstring : 1;        /* T => if string appeared on original rhs */
 unsigned frc_assgn_in_src : 1; /* T => force or assign appears in src */
 unsigned monit_in_src : 1;   /* T => has mon/fmon in source for var */
 unsigned dmpv_in_src : 1;    /* if not all dummpvar => has mon/fmon in src */
 unsigned n_iscompleted : 1;  /* type def completed in earlier source */ 
 byte n_drvtyp;               /* for scalar simple stat tab for dir chg */
 /* AIV 12/22/11 - added field as a work around for generate parameter issue */
 //AIV LOOKATME - this can be removed
 int32 isparam_ninsts;
 
 struct expr_t *nx1, *nx2;
 struct expr_t *ax1, *ax2;
 union del_u n_dels_u;
 byte *n_pb_drvtyp;           /* per bit drvr state tab for port dir chg */ 
};

/* list for blocks of allocated ncomp for fast block freeing */
struct ncablk_t {
 struct ncomp_t *ancmps;
 struct ncablk_t *ncablknxt; 
};

/* array - LOOKATME - one dimensional only so far */
struct rngarr_t {
 int32 ni1, ni2;
 int32 ai1, ai2;
};

/* normal wire with delay or path destination wire */
struct rngdwir_t {
 int32 ni1, ni2;
 unsigned n_delrep : 5;
 union del_u n_du;            /* every bit has same delay for nets */ 
 struct tev_t **wschd_pbtevs;  /* any schd. event ndxes - indexed nwid*inst */
};

struct rngwir_t {
 int32 ni1, ni2;
};


/* maximum number of dimensions allowed */
#define MAX_ARRAY_DIM 8

struct mda_t {
 int32 dimension;              /* number of dimensions */
 int32 ni1, ni2;               /* array element width */
 int32 *rng1;                  /* range array for lsb indexed by dimension */
 int32 *rng2;                  /* range array for lsb indexed by dimension */
 int32 *dim_mult;              /* multiplier indexed by dimension */
 struct expr_t **tab_ax1;      /* dim size table of first range exprs */
 struct expr_t **tab_ax2;      /* dim size table of first range exprs */
};

/* various extra storage information for various stages for nets */

union nx_u {
 struct ncomp_t *ct;          /* compile time value */
 struct rngarr_t *rngarr;
 struct rngdwir_t *rngdwir;
 struct rngwir_t *rngwir;
};

union np_u {
 struct gref_t *npgrp;        /* xmr glb that needs normal downward proc. */
 t_midat *filtidp;            /* for root or uprel xmr filt to 1 inst */
 struct h_t *vpihp;           /* for vpi_ added, the assoc. handle */
};

/* auxiliary list struct of lists of per inst dce lsts for qcaf lhs concats */
struct dceauxlstlst_t {
 /* SJM 06/23/02 - for wire dce list for 1 lhs bit but ndx is per inst/bit */
 struct dceauxlst_t **dcelsttab; /* peri(/bit) tab of ptrs to dce lsts */
 struct dceauxlstlst_t *dcelstlstnxt;
};

/* auxiliary list struct for removing dce's of various types */ 
struct dceauxlst_t {
 struct dcevnt_t *ldcep;
 struct dceauxlst_t *dclnxt;
};

/* AIV 05/17/10 - union to hold FST idcode or VCD char ptr */
union dvid_u {
 char *dvcodp;
 int32 idcode;
};

/* union to either old <= WBITS a part or malloc byte ptr */
union dv_storage_u {
 byte *buf; 
 word32 val;
 word32 mtime;
};

/* AIV 04/19/12 - storage for buffered dumping storage */
struct dmp_buf_t {
 int32 idcode;              /* idcode */
 int32 arr_flat_ndx;        /* array index for array dumping */
 union dv_storage_u dvsu;   /* storage for apart or alloc buf */
 word32 bval;               /* <= WBITS bpart value */
 struct net_t *np;          /* net it is dumping */
};
 
/* parallel version needs to take an extra arg */
union dmp_funcu {
 void (*single)(struct net_t *, t_midat *);     
 void (*parallel)(struct net_t *, t_midat *, struct dmp_buf_t *);
};

struct dvchgnets_t {
 unsigned on_list : 1;         /* array element is on list */ 
 union dvid_u idu;
 int32 dv_flat_ndx;            /* if not -1 - flat array (maybe mda) index */
 struct net_t *dvchg_np; 
 t_midat *dvchg_idp;
 struct dvchgnets_t *dvchgnxt;
};

union dce_u {
 struct gref_t *dcegrp;       /* xmr glb that needs normal downward proc. */
 int32 pnum;                  /* for pvc dce tf routine port number */     
 struct task_t *tskp;         /* for dmpv dce, task variable in */
 struct cbrec_t *dce_cbp;     /* cbrec for vpi_ val chg callback */
 struct expr_t *dcemon_src_xp;/* during fill when no idps, save expr here */ 
};

/* SJM 06/12/02 - need 2nd union to separate different types of data */
union dce2_u {
 struct fmonlst_t *dce_fmon;  /* nil if monit else fmon record for monitors */
 struct expr_t *dce_pvc_fcallx; /* pvc misctf fcall expr */
 struct st_t *dce_pvc_stp;    /* pvc misctf statment */
 struct qcval_t *dce_qcvalp;  /* for qcaf dce, stmts qcval record */ 
};

/* for edge where value expr., need general information for filtering */
/* all decomposed dce's from expr, pt. to one of these */
struct dce_expr_t {
 struct expr_t *edgxp;
 struct dcevnt_t *mast_dcep;  /* one master (first) for alloc and init */ 
 size_t expr_ofs;             /* dce expr idp offset */ 
};

/* union for itree ptrs later changd to idp ptrs when built */
union itd_u { 
 struct itree_t *itp; 
 t_midat *idp;
};

/* fixed (except $monitor chges) list off wire of things to trigger */
struct dcevnt_t {
 unsigned dce_typ : 8;        /* itree location and action match type */ 
 unsigned dce_xmrtyp : 2;     /* indicates if xmr and type */ 
 unsigned dce_1inst : 1;      /* one instance form must match match itp */
 unsigned dce_edge : 1;       /* T => need edge filtering  */
 unsigned dce_edgval : 8;     /* edge signature for filter (only pos/neg) */
 unsigned dce_nomonstren : 1; /* T => ignore stren for monit of stren */
 unsigned dce_tfunc : 1;      /* T => for pvc dce func. not task */
 unsigned is_fmon : 1;        /* monitor is fmon */
 unsigned nd_chg_to_idp : 1;  /* T => in src monit dce add, chg to idp later */
 /* AIV 09/08/08 - made dce_off a byte instead of bit - lowered code better */
 byte dce_off;                /* for byte code PLI/monitor need dce on/off */ 
 unsigned merged : 1;         /* T => dce has been merged */
 unsigned is_loaded : 1;      /* T => dce is loaded (passed) to wrapper */
 unsigned is_printed : 1;     /* T => compiled global is printed */
 int32 dci1;                  /* for range dci2 union for IS param */ 
 int32 dce_ndx;               /* dce ndx from the table for +load_solib */
 int32 merged_count;            /* number of merged dces */
 struct dcevnt_t **merged_dces; /* dces on list merged into this one */
 struct dce_idp_info_t *didp; /* idp offset information */
 size_t prevval_ofs;
 union pck_u pli_prevval;     /* storage for wire or range for PLI only */
 union intptr_u dci2;         /* for IS param union rng ptr (dci1 = -2) */
 struct net_t *dce_np;        /* net this dce is triggerd by */
 struct delctrl_t *st_dctrl;  /* statement's delay control record */
 union dce_u dceu;            /* for xmr - propagation gref info */
 union dce2_u dceu2;          /* nil if monit else fmon record */
 union itd_u dce_matchu;      /* for 1 inst. must match this itree target */
 union itd_u dce_refu;        /* itree/idp ref location */
 t_midat *iact_idp;           /* for per inst. iact need inst. to match */
 struct dce_expr_t *dce_expr; /* for edge where need expr old val and expr */
 struct dcevnt_t *dcenxt;     /* next on wire dcelst */
};

/* info for a xmr dce to hold idp linker information */
struct dce_idp_info_t {
 size_t match_idp_ofs;         /* idp offset for dce_matchu */
 struct mod_t *match_mdp;     /* matching mdp */
 size_t ref_idp_ofs;           /* idp offset for dce_refu */
 struct mod_t *ref_mdp;       /* ref mdp */
};

/* built in table for every built in primitive (gate) */
struct primtab_t {
 unsigned gateid : 8;
 unsigned gclass : 8;         /* class of gate */
 struct sy_t *gnsym;
 char *gatnam;
};

/* table for system task info */
struct systsk_t {
 word32 stsknum;              /* systask ind or 1000+index veriusertfs[] */
 char *stsknam;               /* name of system task or pli task */
};

/* list for +loadvpi or +loadpli1 dynamic lib and bootstrap function pairs */
union dynlb_u {
 void (*vpi_rout)(void);
 void *(*tf_rout)(void);
};

/* need list of boot strap routines because option allows more than one */
struct dynboot_t {
 char *bootrout_nam;
 union dynlb_u dynu;
 struct t_tfcell *ret_veriusertf;
 struct dynboot_t *dynbootnxt;
}; 

struct loadpli_t {
 unsigned pli1_option : 1;    /* T => +loadpli1= option */
 char *libnam;
 struct dynboot_t *dynblst;   /* list of boot routines (can be empty) */ 
 /* for pli1, if non nil ptr to veriusertf tab */
 struct loadpli_t *load_plinxt;
};

struct tfinst_t { 
 struct expr_t *callx;
 struct st_t *tfstp;
 t_midat *tfidp;
 struct task_t *tftskp;
};

/* table for system function info */
struct sysfunc_t {
 word32 syfnum;               /* sysfunc ind. or 1000+ind veriusertfs[] */
 unsigned retntyp : 8;
 unsigned retsigned : 1;      /* need for signed wire */
 unsigned pass_array : 1;     /* T => can pass unindexed array */
 unsigned tftyp : 8;          /* type */
 int32 retwid;                /* for veriuser and vpi systf sizetf call sets */
 char *syfnam;                /* name of system function */
};

union vsystf_u {
 struct expr_t *sysfcallx;    /* if systf fcall, vpi_ systf call expr. */
 struct st_t *syststp;        /* stmt vpi_ systf call or task enable in */
};

/* list element for each location vpi_ systf appears in source */
/* cross linked through sz_u from calling expr node */
struct vpisystf_t {
 unsigned is_sysfunc : 1;     /* t +> vpi_ systf func */
 unsigned vstffnam_ind : 16;
 int32 vstflin_cnt;
 struct mod_t *curmdp;        /* ptr. to current mod source line of call in */
 struct task_t *curtskp;      /* ptr. to current task source line of call in */
 union vsystf_u vsystfu;      /* ptr to callx or sys task stmt */ 
 struct vpisystf_t *vpistfnxt; 
};

/* union for dpi arg malloc - BEWARE need literal copy emitte in dpi wrapper */ 
union adpi_u {
 unsigned char sv_ch;
 int sv_i;
 short int sv_shrti;
 long long int sv_lngi;
 double sv_d; 
 void *sv_ptr;
};

/* struct (per arg) for interpreter storage of dpi wrapper val storage */
struct dpiarg_t {
 unsigned ver_side_svtyp : 8; /* Ver side SV type constant from imp/exp decl */
 unsigned arg_srep : 6;       /* extended storage reps (for passed arrays) */
 unsigned arg_iotyp : 3;      /* arg direction - using ver side vals */
 unsigned arg_arr : 1;        /* T => arg is verilog array name */
 unsigned nd_lval_ptr : 1;    /* T => arg is lval (array or out) use addr */
 int32 arg_nbytes;            /* if alloced size, else 0 */ 
};

struct dpi_t {
 unsigned dpi_type : 8;      /* DPI type - import/export */
 unsigned dpi_call_type : 8; /* DPI call type - function/task */
 unsigned dpi_language : 1;  /* DPI language - always 'C' for now */
 unsigned import_property : 2; /* context/pure */
 unsigned has_ret : 1;       /* T => has a return type */
 unsigned imp_fnd_in_lib : 1;/* T => during checking phase for comp, fnd */
 struct sy_t *dsym;          /* Verilog named symbol */
 char *cname;                /* name of actual C function */
 struct task_t *dpi_tskp;    /* back link from dpi to its t/f */ 
 int dpi_proc_ndx;           /* for interp C gen index of wrapper to call */
 int32 dpi_nargs;            /* number of dpi world t/f args */
 struct dpiarg_t *dpi_ainfo; /* arg info for each dpi task arg (port/pin) */
 struct dpi_t *dpinxt;       /* next dpi struct on list */
 union adpi_u *arg_u_tab;    /* array of union of dpi arg values */
};

struct sv_lib_t {
 unsigned does_not_exist : 1;
 char *path;
 struct sv_lib_t *svnxt;
};

union mpp_afunc_u {
 /* routine for input cross port assign */
 void (*mpp_downassgnfunc)(register struct expr_t *,
  register struct expr_t *, struct itree_t *);
 /* routine for output cross port assign */
 void (*mpp_upassgnfunc)(register struct expr_t *,
  register struct expr_t *, struct itree_t *);
};

/* work record for decomposed into per bit declarative assign */
struct pbexpr_t {
 unsigned ndx_outofrng : 1;
 unsigned rhs_const : 1;
 unsigned no_rhs_expr : 1;     /* lhs widers bits need 0/z assign */
 int32 bi;                     /* for bsel/psel offset in var object */
 struct expr_t *xp;
 word32 aval;                  /* aways 1 bit constant value (for rhs only) */
 word32 bval;
};

/* module port element */
struct mod_pin_t {
 unsigned mptyp : 3;          /* I/O type - maybe changed with warning */
 unsigned mp_explicit : 1;    /* T => source explicit port reference */
 unsigned mp_jmpered : 1;     /* T => port has net also in other port */
 unsigned inout_unc : 1;      /* T => this inout unc. somewhere */
 unsigned assgnfunc_set : 1;  /* T => know the port assign func */
 unsigned has_mipd : 1;       /* T => input port has mipd delay */
 unsigned has_scalar_mpps : 1;/* T => simulated per bit */
 unsigned mpfnam_ind : 16;    /* file symbol defined in */
 int32 mplin_cnt;             /* def. line no. */
 int32 mpwide;                /* width of port */
 
 char *mpsnam;                /* name not symbol of port (can be NULL) */
 struct expr_t *mpref;        /* expression form port list (const.) */
 struct attr_t *mpattrs;      /* all I/O decls attrs for conn nets */

 /* union of proc ptrs  for input/output cross port assign */
 union mpp_afunc_u mpaf;
 struct mod_pin_t *pbmpps;    /* for rhs hconn input port, per bit mpp */
 struct mod_pin_t *mpnxt;     /* elaborate time next link */
};

/* table build per line for wild card processing */
struct wcard_t {
 int32 wcinum;                /* in port (also state) numb for wild card */
 char wcchar;                 /* wild card ? or b */
};

/* udp table storage */
struct utline_t {
 /* these must be char pairs even for combinatorial */
 unsigned ulhas_wcard : 1;
 unsigned ullen : 8;          /* length of original tline in bytes */
 unsigned utabsel : 8;        /* first edge char table select (maybe wc) */
 unsigned uledinum : 8;       /* input position number of one allowed edge */
 unsigned utlfnam_ind : 16;   /* file no. of udp line */
 int32 utlin_cnt;             /* line no. of udp tble line */
 char *tline;                 /* table line - for edge 2nd char in line */
 struct utline_t *utlnxt;
};

/* special struct for udp tables */
struct udptab_t {
 word32 *ludptab;
 /* alloced according to required size (max 27 pointers to tabs of words */
 word32 **eudptabs;
};

struct udp_t {
 unsigned utyp : 4;
 unsigned numins : 8;         /* number of inputs */
 unsigned numstates : 8;      /* for combinatorial same else one more */
 unsigned ival : 8;           /* initial value (0,1,3 - none) */
 unsigned u_used : 1;         /* T => need table, instanciated in some mod */
 unsigned u_wide : 1;         /* T => uses alt. wide representation */
 int32 u_idnum;               /* id number for counting and cvc access */
 struct sy_t *usym;
 struct symtab_t *usymtab;    /* symbol table just for terminals */
 struct mod_pin_t *upins;     /* defined ports for order */
 struct utline_t *utlines;
 struct udp_t *udpnxt;
 struct udptab_t *utab;
};

/* task port (like procedural variable - all info in reg(wire)) */
struct task_pin_t {
 unsigned trtyp : 8;          /* i/o type (same as sym np iotyp) */
 struct sy_t *tpsy;           /* port name sym. points to wire/reg */
 struct task_pin_t *tpnxt;
};

/* procedureal assignment statement */
struct proca_t {
 struct expr_t *lhsx;         /* need to make sure this is an lvalue */
 struct expr_t *rhsx;
};

/* quasi continous assigns */
struct qconta_t {
 unsigned qcatyp : 8;
 unsigned regform : 8;
 struct expr_t *qclhsx;
 struct expr_t *qcrhsx;
 struct dceauxlstlst_t *rhs_qcdlstlst;
};

/* quasi cont. deassigns - no continuous deassign */
struct qcontdea_t {
 unsigned qcdatyp : 8;
 unsigned regform : 8;
 struct expr_t *qcdalhs;
};

#ifdef __XPROP__
struct xprop_t {
 int32 xblock;                   /* xblock 0 or 1 */
 int32 ncount;                   /* num nets on lhs */
 unsigned is_top_level : 1;      /* x-prop is top level */
 unsigned top_single_item : 1;   /* top-level item not part of nested */
 unsigned nested_if_case : 1;    /* nested if/case stmts */
 unsigned has_ids_only : 1;      /* only contains ids on lhs */
 unsigned has_one_id_only : 1;   /* only contains single id always set */
 unsigned x_entered : 1;         /* xprop has been entered */
 int32 *lhs_id_only;             /* lhs id only */
 word32 **accum_block1;          /* accum block 1 */
 word32 **accum_block2;          /* accum block 2 */
 word32 **bits_set;              /* net mask for the per set bits */
 word32 **xbitmask_block1_set;   /* net mask for the first block */
 word32 **xbitmask_block2_set;   /* net mask for the second block */
 int32 *net_block1_set;          /* net set flags for first block  */
 int32 *net_block2_set;          /* net set flags for second block */
 struct net_t **lhsnets;         /* table of nets on the lhs */
 struct st_t **astmts;           /* assign stmts - all know to be the same */
 int32 *parent_net_indices;      /* save net indices */
 struct xprop_t *parent_xprop;   /* parent of this xprop */
 struct net_t **xedge_nets;      /* xedge triggered event control - per inst */
 byte *xedge_to_vals;            /* set to xedge value 0, 1, 2 (not set) */
 struct tev_t **xevents;         /* store x triggered event controls */
};

/* struct for non-blocking compile time nb fixed struct xprop building */
union xprop_nbu {
 struct st_t *xprop_astp;     /* assign id xprop stmt */
 struct st_t *xprop_orig_astp; /* assign id xprop stmt */
};

struct st_list_t {
 struct st_t *stp;
 struct st_list_t *nxt_stp;
};
#endif

struct if_t {
#ifdef __XPROP__
 unsigned xedge_dce : 1;        /* T => is a dce xedge if stmt */
 struct xprop_t *xprop;
#endif
 struct expr_t *condx;
 struct st_t *thenst;
 struct st_t *elsest;
};

struct csitem_t {
 struct exprlst_t *csixlst;
 struct st_t *csist;          /* for unnamed block can be list */
 struct csitem_t *csinxt;
};

struct case_t {
 unsigned castyp : 8;
 unsigned maxselwid : 24;
#ifdef __XPROP__
 struct xprop_t *xprop;
 struct st_t *xprop_lstp;     /* x-prop statement list */
#endif
 struct expr_t *csx;
 struct csitem_t *csitems;    /* first item always default: place holder */  
};

struct wait_t { 
 struct expr_t *lpx;
 struct st_t *lpst;
 struct delctrl_t *wait_dctp;
};

/* for forever and while */
struct while_t {
 struct expr_t *lpx;
 struct st_t *lpst;
};

struct repeat_t {
 struct expr_t *repx;
 size_t reptmp_ofs;            /* now rep count is ofs from idp (%esi) area */
 struct st_t *repst;
};

struct for_t {
 unsigned has_continue : 1;    /* T => has continue statement */
 unsigned has_break : 1;       /* T => has break statement */
 unsigned is_expanded_foreach : 1;    /* T => is expanded foreach statement */
 struct sy_t *foreach_syp;     /* foreach expanded array symbol */
 int32 dim;                    /* foreach expanded array dimension */
 struct st_t *forassgn;
 struct expr_t *fortermx;
 struct st_t *forinc;
 struct st_t *forinc_tail;
 struct st_t *forbody;
};

/* normal separate delay control - but in case of rhs control contains st. */
/* event expression allow events edges of events and oring of ev. exprs */
struct delctrl_t {
 unsigned dctyp : 8;          /* event or delay */
 unsigned dc_iact : 1;        /* iact delay control */ 
 /* SJM 06/10/02 - distinguish non blocking from blocking event ctrls */  
 unsigned dc_nblking : 1;     /* T => delay control is non blocking form */
 /* AIV 07/12/12 - need to mark SV always_comb/always_ff */
 unsigned dc_is_always_comb_latch : 1; /* T => always_comb/always_latch */
 unsigned dc_is_always_ff : 1;         /* T => always_ff */
 unsigned implicit_evxlst : 1;/* special all rhs's @(*) ev var-ndx list */ 
 unsigned dc_delrep : 5;      /* normal gca delay type */
 unsigned is_merged : 1;        /* T => has been merged into head dctl */ 
 unsigned is_always : 1;        /* T => used as always block trigger */ 
 unsigned nested_dctrl : 1;     /* T => has nested dctrl */ 
 unsigned needs_thread : 1;     /* T => always block uses thread */ 
#ifdef __XPROP__
 unsigned d_has_xmr : 1;        /* T => xmr edge */ 
 unsigned d_has_edge : 1;       /* T => has posedge/negedge */
 unsigned d_only_edges : 2;     /* T => only pos/edge edges */
 unsigned d_only_scalars : 1;   /* T => only scalar nets */
 unsigned d_only_vectors : 1;   /* T => only vectored nets */
 unsigned d_gt_one : 2;         /* == 2 has greater than one trigger net */
 unsigned d_edgval : 8;         /* edge signature for filter (only pos/neg) */
 unsigned d_same_edge : 1;      /* edge (pos/neg) is the same */
 unsigned d_uses_nets_on_rhs : 1;  /* T => edge uses some nets on rhs body */
#endif
 union del_u dc_du;           /* normal delay union (also used for ev ctrl) */
 struct expr_t *repcntx;      /* for rhs ev ctrl repeat form, rep cnt expr */
 size_t dceschd_tev_ofs;       /* offset of the i tev ndx sched tev for dce */
 size_t dce_repcnt_ofs;        /* offset in per inst idp of counter now */   
 struct st_t *actionst;       /* delctrl stmt list */
#ifdef __XPROP__
 struct st_t *xprop_nb_actionst;    /* nb xprop copy action list */
 struct st_t *xprop_xedge_actionst; /* xedge action list */
#endif
//AIV LOOKATME - could make some of these own struct to save some space???
 struct delctrl_t *merged_dctp; /* list of merged dctp off of head */
 struct delctrl_t *head_dctp;   /* head dctp this is merged into */
 struct ctev_t *head_ctevp;     /* compile time info building static tev_t */
 int32 dc_id_ndx;               /* index (id)  */
};

/* header list for each initial always block */
struct ialst_t {
 unsigned iatyp : 8;
 unsigned needs_thread : 1;  /* T => needs thread control */
 int32 ia_first_lini;         /* line no. of initial/always */
 int32 ia_first_ifi;          /* and file index */
 int32 ia_last_lini;          /* line no. of end (mabye in next file) */
 int32 ia_last_ifi;           /* end file in case spans multiple files */
 struct st_t *iastp; 

 void *enterptr;             /* enter address for cvc enter */
 struct ialst_t *ialnxt;   
};

union tf_u {
 struct expr_t *callx;        /* for tf_ func ptr back to call expr else nil */
 struct st_t *tfstp;          /* for tf_ task ptr back to call stmt else nil */
};

union tfx_u {
 struct expr_t *axp;          /* for arg the expr. */
 word32 *awp;                 /* for 0th return value just the value */
};

/* per parameter tfrec record */
struct tfarg_t {
 union tfx_u arg;
 struct net_t *anp;           /* for is rw, the wire */
 byte *old_pvc_flgs;          /* old and sav pvc flags */
 byte *sav_pvc_flgs;
 struct dltevlst_t **dputp_tedlst;/* per inst ptr to list of delputps */
 char **sav_xinfos;           /* per inst evalp saved expr info rec */
 union pck_u tfdrv_wp;        /* for rw, pointer to param driver value */ 
};

/* extra task call side data for pli tasks/funcs (each call loc. differs) */
struct tfrec_t {
 unsigned tf_func : 1;        /* is record for tf_ func */
 unsigned fretreal : 1;       /* func. returns real */
 unsigned tffnam_ind : 16;
 int32 tflin_cnt;
 int32 tfanump1;              /* no. of args plus 1 (included 0th func ret) */
 int32 fretsiz;               /* for function return size (sizetf ret. val) */  
 union tf_u tfu;              /* ptr back to tf_ task or function */
 struct mod_t *tf_inmdp;      /* module in (for inst. number) */
 struct task_t *tf_intskp;    /* task call in (nil in in init/always */
 struct tfarg_t *tfargs;      /* per parameter param record table */
 char **savwrkarea;           /* per inst saved work areas */
 struct tev_t **sync_tevp;        /* per inst ndx to sync event */
 struct tev_t **rosync_tevp;      /* per inst ndx to ro sync event in list */ 
 byte *asynchon;              /* per inst. async on flag */
 struct tevlst_t **setd_telst; /* per inst ptr to list of set dels */  
 struct dceauxlst_t **pvcdcep;/* per inst dce list but all parameters */
 struct tfrec_t *tfrnxt;      /* linked list */
};

/* vpi handle union of internal d.s. elements */
union h_u {
 struct gate_t *hgp;
 struct net_t *hnp;
 struct task_t *htskp;        /* also named block and function */
 struct mod_t *hmdp;          /* for mods in modsyms table */
 struct ialst_t *hialstp;     /* process - init or always */
 struct mod_pin_t *hmpp;      /* udp port or net-pin list mod. I/O port */
 struct conta_t *hcap;        /* pointer to conta */
 struct spcpth_t *hpthp;      /* point back to path for special id symbol */    
 struct dfparam_t *hdfp;      /* for defparam source reconstruction handles */
 struct tchk_t *htcp;         /* and back to time check */      
 struct expr_t *hxp;          /* representation as ptr to expr. */
 struct st_t *hstp;           /* statement handle */
 struct csitem_t *hcsip;      /* case item */
 int32 hpi;                   /* for port bit handle the port index */
 /* this is only contents field that is freed */
 struct pviter_t *hiterp;     /* iterator indirect element with alloc list */
 struct cbrec_t *hcbp;        /* callback handle guts record */
 struct tev_t *htevp;         /* event ndx for sched. vpi put value only */
 struct net_pin_t *hnpp;      /* for driver the drvr net pin record */
 struct udp_t *hudpp;         /* udp handle object record */ 
 struct utline_t *hutlp;      /* udp line for table entry handle */
 struct schdev_t *hevrec;     /* pending vpi_ driver all net sched. evs tab */
 void *hanyp;                 /* any ptr so do not need to cast to it */
 struct hrec_t *hfreenxt;     /* ptr to next hrec on free list */
};

/* non-blocking event list */
struct nb_event_t { 
 struct tev_t *nb_tevp; 
 struct nb_event_t *nbnxt;
};

/* handle object event table record for scheduled vector events */ 
struct schdev_t {
 struct net_t *evnp;
 struct tev_t **evndxtab; 
};

/* actual handle */
struct h_t {
 struct hrec_t *hrec;         /* handle content record */
 t_midat *hin_idp;            /* itree inst object in (if relevant) */
};

/* handle contents */
struct hrec_t {
 unsigned htyp : 16;          /* vpi object type of handle */
 unsigned htyp2 : 16;         /* extra type */
 unsigned h_magic : 11;       /* magic number for internal checking */
 unsigned in_iter : 1;        /* part of iterr, free when iterator freed */
 unsigned free_with_iter : 1; /* for in iter, free when iter freed */
 unsigned free_xpr : 1;       /* free expr. when free handle */
 unsigned evnt_done : 1;      /* for vpi schd event, event happened */
 unsigned bith_ndx : 1;       /* bit handle index form (also any tab form) */ 
 int32 hi;                    /* for bit of object handle the index */
 union h_u hu;                /* ptr to object (could be void *) */ 
 struct task_t *hin_tskp;     /* task (scope) handle in (or ialst) */
};

struct pviter_t {
 struct h_t **scanhptab;      /* tab of ptr to handles built by vpi iterator */
 int32 nxthi;                 /* next handle to return */
 int32 numhs;                 /* total number of handles for iterator */
};

struct onamvpi_t {
 char *vpiobjnam;
 word32 vpiotyp;              /* redundant value same as obj constant ind */
};

struct pnamvpi_t { 
 char *vpipropnam;
 int32 vpiproptyp;            /* redundant value same as prop constant ind */
};

struct opnamvpi_t { 
 char *vpiopnam;
 int32 vpioptyp;              /* redundant value same as op constant ind */
 char *vpiopchar;             /* operator character (such as +) */
};

union systf_u { 
 struct systsk_t *stbp;
 struct sysfunc_t *sfbp;
};

struct systftab_t {
 unsigned systf_chk : 1;      /* T => already seen in source and checked */ 
 void *vpi_sytfdat;
 union systf_u sfu;
};

/* guts of callback handle - separate handle for each instance */
/* info from passed user cb_data record copied into here */
struct cbrec_t {
 unsigned cb_reason : 12;     /* reason field from passed cb_data rec. */
 unsigned cb_rettimtyp : 6;   /* time record field type to return */
 unsigned cb_retvalfmt : 7;   /* value record field format to return */
 unsigned cb_class : 3;       /* internal scheduling class */  
 unsigned cb_ndxobj : 1;      /* T => value chg handle is indexed */  
 unsigned cb_user_off : 1;    /* T => user turned off with sim control */
 unsigned cb_gateout : 1;     /* T => gate outut val chg type cb */ 
 struct h_t *cb_hp;           /* object */ 
 int32 (*cb_rtn)();           /* cb_data call back routine */
 char *cb_user_data;          /* user data field from passed cb_data rec. */
 struct dceauxlst_t *cbdcep;  /* list of dces for cb removal */ 
 struct tev_t *cbtevp;         /* ndx (ptr) back to event */
 struct h_t *cb_cbhp;         /* associated handle of call back */
 struct cbrec_t *cbnxt;       /* next in chain of all callbacks */
 struct cbrec_t *cbprev;      /* previous in chain of all callbacks */
};

/* list for release and force cb all forms - many cbs possible */
struct rfcblst_t {
 struct cbrec_t *rfcbp; 
 struct rfcblst_t *rfcbnxt;
};

/* SJM 06/20/02 - for monit now bld dces where can during prep, need dce ptr */
struct monaux_t {
 unsigned dces_blt : 1;       /* T => dces already built for this monit */
 byte *argisvtab;             /* tab of v format flags for monitor */
 struct dceauxlst_t **mon_dcehdr; /* lst of per inst dces bld during prep */ 
};

/* SJM 06/20/02 - change sys task aux field to union instead of casts */
/* sys task call union for PLI systf calls and monitor/fmonitor aux info */
union tkcaux_u {
 struct tfrec_t *trec;        /* ptr to aux pli tf_ data */
 struct monaux_t *mauxp;      /* ptr to mon aux v format flag and dce ptr */
 void *vpi_syst_datap;
};

struct tskcall_t {
 struct expr_t *tsksyx;       /* task symbol or global table entry */
 struct expr_t *targs;        /* FCCOM expr of args */
 union tkcaux_u tkcaux;       /* ptr to aux pli tf_ data or monit rec */
};

struct dsable_t {
 struct expr_t *dsablx;       /* expr. (ID/GLB) of disable task/func/blk */
 struct st_t *func_nxtstp;    /* for functions disable is goto */
};

struct fj_t {
 struct st_t **fjstps;        /* ptr to tab (nil ended) fork-join stmts */
 int32 *fjlabs;               /* ptr to tab of fj start lab nums */
};

/* slot end stmt list for strobes with itree where execed strobe appeared */
struct strblst_t {
 struct st_t *strbstp;
 t_midat *strb_idp;
 struct strblst_t *strbnxt;
};

/* slot end triggered fmonitor list */
struct fmselst_t {
 struct fmonlst_t *fmon;
 struct fmselst_t *fmsenxt;
};

/* acctivated fmonitor list with itree location */
struct fmonlst_t {
 word32 fmon_forcewrite;
 struct st_t *fmon_stp;
 t_midat *fmon_idp;
 struct fmselst_t *fmse_trig; /* set when monitor triggered 1st time */
 struct dceauxlst_t *fmon_dcehdr;
 struct fmonlst_t *fmonnxt;
}; 

/* union either 4 byte ptr or 12 byte union in statment */
/* save space since previously needed 4 byte ptr plus record */
union st_u {
 struct proca_t spra;
 struct if_t sif;
 struct case_t scs;
 struct while_t swh;
 struct wait_t swait;
 struct repeat_t srpt;
 struct for_t *sfor;
 struct delctrl_t *sdc;
 struct task_t *snbtsk;       /* named (like task) block */
 struct st_t *sbsts;          /* unnamed block statement list */
 struct fj_t fj;              /* fj 2 tabs (1 stps and 1 fj c code labs */
 struct tskcall_t stkc;
 struct qconta_t *sqca;       /* assign and force */
 struct qcontdea_t sqcdea;    /* deassign and release */
 struct expr_t *scausx;       /* cause expr. node symbor or global id. */
 struct dsable_t sdsable;     /* disable struct (also place for goto dest) */
 struct st_t *sgoto;          /* destination of added goto */
};

/* statement structure */
struct st_t {
 unsigned stmttyp : 6;
 unsigned rl_stmttyp : 6;     /* for break set at statment, real type */
 unsigned st_unbhead : 1;     /* if unnamed block removed, indicated here */  
 unsigned strb_seen_now : 1;  /* T => for checking strobe on list for now */
 unsigned lpend_goto : 1;     /* T => this is loopend goto */
 unsigned dctrl_goto : 1;     /* T => this is next after dctrl chain goto */ 
 unsigned lpend_goto_dest : 1; /* dest. of loop end back goto for compiler */
 unsigned dmp_stmt : 1;       /* T => statement has been printed for coverage */
 unsigned stfnam_ind : 16;
 unsigned enter_created : 1;  /* T => stmt already has an enter loc in asm */
 unsigned unreachable : 1;    /* T => stmt is unreachable from compiler */
 unsigned is_loaded : 1;      /* T => stmt is loaded (passed) to a wrapper */
 unsigned is_printed : 1;     /* T => compiled global is printed */
 unsigned is_nb_enter : 1;    /* T => stmt has a nb enter location */
 unsigned is_enter : 1;       /* T => stmt has a enter location */
#ifdef __XPROP__
 unsigned nb_xprop_in_list : 1; /* T => nb stmt has already in nb list */
 unsigned xprop_eligible : 1; /* T => if/case stmt can be xprop */
#endif
 int32 stlin_cnt;
 int32 task_thrd_jmpndx;        /* index of task return location */
 union st_u st;
 struct st_t *stnxt;

 void (*enterptr)(void);      /* enter address */ 
 size_t rhs_idp_ofs;          /* storag area index for rhs */
 struct ctev_t *ctevp;        /* compile time info for building static tev_t */
 int32 stmt_id_ndx;           /* stmt identifier */
 int32 st_ndx;                /* stmt index into mstmts */
#ifdef __XPROP__
//AIV XPROP - FIXME - should make a struct to save space
 int32 xprop_level;           /* T => stmt xprop level */
 union xprop_nbu xprop_nbu; /* compile time xprop nb info */
#endif
};

/* contents of break point table */
struct brkpt_t {
 unsigned bp_type : 4;        /* type of breakpoint */ 
 unsigned bp_can_halt : 1;    /* T => really break, F start and reset */
 unsigned bp_enable : 1;      /* T => break not disabled */
 unsigned bp_prttyp : 2;      /* type of printing when hit */
 unsigned bp_dup : 1;         /* T => multiple break points at statement */
 unsigned bp_rm_when_hit : 1; /* T => remove when hit */
 int32 bp_num;                /* identifying number */
 int32 bp_ignore_cnt;
 int32 bp_hit_cnt;            /* number of times hit */
 struct st_t *bp_stp;         /* statement this break point breaks at */
 t_midat *bp_idp;             /* itree loc. - any (first?) for all of type */ 
 struct task_t *bp_tskp;      /* task break point in else NULL if not */
 struct expr_t *bp_condx;     /* :cond cmd filter expr. */ 
 /* expressions and watch point values go here */
 struct brkpt_t *bpnxt;
};

struct dispx_t {
 unsigned dsp_enable : 1;
 unsigned dsp_frc_unsign : 1;
 int32 dsp_num;
 int32 dsp_prtfmt;
 int32 dsp_prtwidth;
 struct expr_t *dsp_xp;
 t_midat *dsp_idp;
 struct task_t *dsp_tskp;
 struct dispx_t *dsp_nxt;
};

/* horizontal doubly linked list of task threads */
struct tskthrd_t {
 struct tskthrd_t *tthd_l, *tthd_r;
 struct thread_t *tthrd;
};

/* aux record for const func info during pre fixup exec and elaboration */
struct conf_aux_t {
 word32 *conf_idata;             /* if alloced, the dummy var idp ara */
 int32 conf_idata_siz;           /* and its size - only one 0th inst */
};

/* either ptr to copied con func from src or con func aux info */
union conf_u {
 struct task_t *to_exec_confunc; /* copied/elabed to exec con func image */
 struct conf_aux_t *cf_auxp;     /* aux record for con func extra info */
};

/* task definition - type of task name symbol determines task type */
struct task_t {
 unsigned tsktyp : 9;         /* symbol number giving task type */
 unsigned t_used : 1;         /* T => task/func. invoked some where */
 unsigned thas_outs : 1;      /* T => task has outs that must be stored */ 
 unsigned thas_tskcall : 1;   /* T => task contains other task call */
 unsigned fhas_fcall : 1;     /* T => func contains non sys fcall */
 unsigned can_be_disabled : 1;/* T => disable somewhere in source */
 unsigned tf_lofp_decl : 1;   /* T => t/f hdr list of port decl form */ 
 unsigned tsk_ingen : 1;      /* T => task defined in gen block */
 unsigned unkn_if_con_func : 1;/* T => not check to see if con func yet */
 unsigned is_con_func : 1;    /* T => when const args, is a const func */
 unsigned is_cp_conf_image : 1; /* T => this is elaborate const copy */
 unsigned is_auto : 1;          /* T => is automatic task */
 unsigned is_inter_blk : 1;    /* T => is internal named block */
 unsigned is_void_func : 1;    /* T => is SV void func */
 unsigned has_return : 1;      /* T => has SV return stmt */
 unsigned no_delay : 1;       /* T => task has no reachable delay */ 
 unsigned uses_scope : 1;     /* T => task calls display uses %m */
 unsigned no_xmrcall : 1;     /* T => task has no reachable xmr task */
 unsigned is_loaded : 1;      /* T => task is loaded (passed) to a wrapper */
 unsigned is_printed : 1;     /* T => compiled global is printed */
 int32 dsa_brk_ndx;           /* index for glob func dsabl nb jmp */
 int32 tsk_last_lini;         /* line no. of end (mabye in next file) */
 int32 tsk_last_ifi;          /* end file in case spans multiple files */
 int32 tprmnum;               /* number of task parameters */
 int32 tlocprmnum;            /* number of task local parameters */
 int32 trnum;                 /* number of task regs */   
 int32 t_idnum;               /* id number for each task (design wide) */
 struct sy_t *tsksyp;         /* name symbol in module level table */
 struct symtab_t *tsksymtab;  /* symbol table for objects in task */
 struct st_t *st_namblkin;    /* stmt named block in in */
 struct task_pin_t *tskpins;  /* task ports - procedural not wires */
 struct net_t *tsk_prms;      /* parameters defined in task */
 struct net_t *tsk_locprms;   /* local parameters defined in task */
 struct net_t *tsk_regs;      /* list then array of nets in task */
 struct st_t *tskst;          /* one task statement (usually a block) */
 struct task_t *tsknxt;       /* next defined task in current module */
 struct tskthrd_t **tthrds;   /* per inst. list of active threads for task */
 union conf_u cfu;            /* con func and image aux info union */
 struct dpi_t *tf_dpip;       /* if DPI set to DPI struct */
 struct task_t **called_tasks; /* array of tasks this task calls */
 int32 end_of_stmtndx;         /* end of stmt index for this task */
};

/* symbol table tree nodes */
struct tnode_t {
 unsigned bal : 8;
 unsigned via_dir : 8;
 struct sy_t *ndp;
 struct tnode_t *lp, *rp;
};

/* symbol table element (type) pointer union */
union el_u {
 struct cell_t *ecp;
 struct inst_t *eip;
 struct gate_t *egp;
 struct net_t *enp;
 struct st_t *estp;
 struct delctrl_t *edctp;     /* delay ctrl for re prep pnps */
 struct task_t *etskp;        /* also named block and function */
 struct systsk_t *esytbp;     /* pointer to system task table entry */
 struct sysfunc_t *esyftbp;   /* pointer to system func. table entry */
 struct mod_t *emdp;          /* for mods in modsyms table */
 struct primtab_t *eprimp;    /* for prims (gates) in modsyms table */
 struct udp_t *eudpp;         /* for udps in modsysm table */
 struct mod_pin_t *empp;      /* udp port or net-pin list mod. I/O port */
 char *edfchp;                /* value of `define macros in defsyms table */
 struct amac_t *eamacp;       /* value for macro with arguments */
 struct conta_t *ecap;        /* pointer to conta */
 struct spcpth_t *epthp;      /* point back to path for special id symbol */    
 struct tchk_t *etcp;         /* and back to time check */      
 int32 eii;                   /* index of inst. in mod inst list or ni */
 struct tchg_t *etchgp;       /* time change record */ 
 struct chktchg_t *echktchgp; /* check time change record */
 struct undef_t *eundefp;     /* for undefined temp. link to list el. */
 struct tfrec_t *etfrp;       /* ptr to tf_ func/task record */
 void *eanyp;                 /* castable void * for special cases */
 struct mipd_t *emipdbits;    /* ptr to per bit mipd record for MIPD npp */
 /* SJM 02-18-10 - new any type for linking syms to gblks */ 
 struct genblk_t *egblkp;     /* link from sym to gblk for LGB type */
};

/* record in table for rem/del of repeated npp's on nets */
struct npopt_t {
 unsigned cant_opt : 1;       /* npp must not be deleted or changed */
 unsigned npp_processed : 1;  /* T => its group has been processed */
 unsigned opt_in_grp : 1;     /* this npp is a maybe del duplicated group */ 
 unsigned npp_del : 1;        /* remove this npp when rebuild npp list */
 int32 nxt_dup_nppi;          /* ptr to nxt in duped possible del list group */
 int32 new_i1;                /* possibly updated new npp range */ 
 int32 new_i2;
 struct net_pin_t *npp;       /* corresponding npp */
};

/* net pin aux struct for special cases */
struct npaux_t {
 size_t idp_ofs;              /* idp offset for filtidp location */
 struct mod_t *mdp;           /* module for filter npp */
 int32 nbi1;                  /* range of connection (-1 for all) */
 int32 lcbi1, lcbi2;          /* if fi is lhs concat, the rhs val subrange */
 /* convention if nbi1 is -2, nbi2 is word32 * union ptr to 2 ISNUM tables */
 union intptr_u nbi2;         /* for IS param union rng ptr (dci1 = -2) */
 union np_u npu;
 /* for src down itree loc tab for root, must match targ. itree */
 /* SJM 05/14/03 - since only for rooted XMR npp, this is addr not peri tab */
 struct itree_t *npdownitp;
};

/* AIV 07/07 - changed chgsubtyp to only be two bits - bits now fit in 32 */
/* its range is only 0-3 so should be 2 bits */
struct net_pin_t {
 unsigned npntyp : 4;         /* type of net pin connection */
 unsigned npproctyp : 2;      /* type of npp processing needed */ 
 unsigned chgsubtyp : 2;      /* for change the change subtype */
 unsigned np_xmrtyp : 2;      /* xmr type */
 unsigned pullval : 1;        /* for pull driver 0 or 1 */
 unsigned obnum : 20;         /* port index number */
 unsigned is_loaded : 1;      /* T => net_pin is loaded (passed) to a wrapper */
 unsigned is_printed : 1;     /* T => compiled global is printed */
 int32 pbi;                   /* for per bit bit index */
 int32 npp_idnum;             /* per mod unique npp id num */

 union el_u elnpp;            /* net pin connecting objects */
 struct npaux_t *npaux;       /* aux. for net pins needing special fields */
 struct net_pin_t *npnxt;
 struct flowg_t *npp_fgp;     /* backend mipd flow graph */
 size_t scalar_mdprt_ofs;     /* idp offset to this net chg */
};

/* parm nplist for delay update on param change delay anotation */
struct parmnet_pin_t {
 unsigned pnptyp : 8;         /* delay expr (or list) type param ref. in */
 unsigned pnp_free : 1;       /* T => master ptr to delay need to free */
 union el_u elpnp;            /* in mod element with delay */
 struct paramlst_t *pnplp;    /* param list (all dels) - copy or orig */
 struct parmnet_pin_t *pnpnxt;
};

/* PLI list of mod port or iconn npp's not yet process for XL style iters */
struct xldlnpp_t {
 struct net_pin_t *xlnpp;
 /* SJM 02/28/08 - now need itree loc since called from SDF where no idp */
 struct itree_t *xlitp;
 struct xldlnpp_t *xlnxt;
};

/* record accessed through sorted index of net/bits with xl style drv/lds */
struct xldlvtx_t {
 struct net_t *dlnp;
 int32 dlbi;
 struct itree_t *dlitp;
};

/* edge list - since both vertices point to this */
struct edge_t { 
 struct vtx_t *ev2;           /* other side edge, this side is cur vtx */
 struct itree_t *edgoside_itp; /* edge other side itree loc (nil if same) */
 /* npnxt has value for traux list for vpi - tran chan must not touch */ 
 struct net_pin_t *enpp;      /* npp of connecting edge (npp) */
 struct edge_t *enxt;
};

/* vertex of tran graph - only traversed thru edges - need npp itp chg */ 
struct vtx_t {
 unsigned new_vtxval : 8;     /* for tran chan, new value */
 unsigned old_vtxval : 8;     /* value at start of tran relax */
 unsigned vtx_chged : 1;      /* T => vertex changes - when done store */
 unsigned vtx_in_vicinity : 1;/* T => vertex already in vincinity */
 unsigned vtx_forced : 1;     /* T => vertex is forced */
 unsigned vtx_supply : 1;     /* T => vertex hard drivers/decl supply */ 
 unsigned vtx_mark : 1;       /* mark bit used for cutting cycles */
 unsigned vtx_mark2 : 1;      /* mark bit used for turning off marks */
 int32 vi1;                   /* bit index for vector wire */
 struct nchglst_t *nchgp;     /* static net change for this vertex */
 struct net_t *vnp;           /* net in channel */
 struct edge_t *vedges;       /* ptr to adjacency list for this node */
};

/* per bit vtx and chan. id table for this static inst. loc. */
struct vbinfo_t {
 int32 chan_id;               /* ID for channel */
 struct vtx_t *vivxp;         /* vertex */
};

/* net tran aux record on - exists if net on some bid or tran channel */
struct traux_t {
 union pck_u trnva;           /* per inst hard driver values for all of net */
 struct vbinfo_t **vbitchans; /* (chan_id, vtx) per bit or bit-inst */
 /* notice this uses npp npnxt field because unused by edges */
 struct net_pin_t *tran_npps; /* ptr to linked tran chan npps */
 int32 *tran_ids;                /* indent for loaded compiler values */
};

/* list element for tran channel relaxation */
struct vtxlst_t { 
 struct vtx_t *vtxp;
 struct itree_t *vtx_itp;
 struct vtxlst_t *vtxnxt;
};

/* list of net/bits in switch channel for init and change processing */
struct bidvtx_t {
 struct net_t *vnp;           /* net in channel */
 int32 vi1;                   /* bit index for vec wire (-1 for all of vec) */ 
 struct itree_t *bidvtx_itp;
};

struct chanrec_t {
 unsigned chtyp : 3;          /* channel processing type */
 unsigned chan_diffwtyps : 1; /* T => different wire types in channel */
 unsigned chan_no_vtxs : 1;   /* T => for pure bid after cnvt to list */
 unsigned chan_replaced : 1;  /* T => when cnvrt to vec bid chan, this gone */
 unsigned chan_vectored : 1;  /* T => replacement vector for inout per bit */
 struct vtx_t *chvxp;         /* for now one random vertex */ 
 struct itree_t *chvitp;      /* and its itree loc. */
 struct bidvtx_t *bid_vtxtab; /* for bid only, rec tab with itree loc */
 word32 numvtxs;              /* number of vertices (net-bits) in channel */
};

/* master dumpvar header record for module argument */
struct mdvmast_t { 
 t_midat *mdv_itprt_idp;      /* itree root of subtree or var itree loc */
 struct task_t *mdv_tskp;     /* task variable or scope in */
 struct net_t *mdv_np;        /* for var. form, pointer to wire */
 struct mdvmast_t *mdvnxt; 
 int32 mdv_levels;            /* level down from $dumpvars call */
 int32 mdv_flat_ndx;          /* array flattened index */
 int32 *mdv_mda_indices;      /* array multi-dim frozen indices */
};

/* table element describing each dump ports file state and output fd num */
struct dp_fildesc_t {
 char *dp_fnam;               /* name of dumpports output file */
 int32 dp_func;               /* global set with type of dumpports dumping */
 int32 dp_state;              /* processing state of dumpports for this file */
 int32 dp_dumplimit_size;     /* user set limit of dv file size (0 none) */
 int32 dp_file_size;          /* current size of dumpports file */
 int32 dp_time_emitted;       /* flag to stop repeated same #[time] */
 int32 dp_fd;                 /* file number of dmpports fd */
 int32 dp_nxti;               /* next free location */
 int32 dp_outlinpos;          /* line postion in dump ports file */ 
 char *dp_buffer;             /* buffer to speed up dumpports output */
 word32 dp_slotend_action;    /* slotend actions - per file */ 

 struct dpinstel_t *dpi_hdr; /* hdr of mast dmpports rec. list for this file */
 struct dpinstel_t *dpi_end; /* end of dumpports rec. list for this file */
 struct dvchgnets_t *dp_chgnethdr;  /* curr. time var chg list hdr for file */
};

/* master dumpports header record for each module (inst) argument */
/* each of these pointed to by fixed field in idp area */
struct dpinstel_t {
 t_midat *dpinst_idp;       /* itree location from which all ports dumped */
 struct dp_fildesc_t *dpi_fdescp; /* ptr to file rec for I/O and state info */
 struct dpctrl_t **net_dpctrl_tab;/* ptr to pb tab of dp ctrl for each i/o net*/
 struct dpinstel_t *dpinxt;     
};

/* structs for d.s. build to handle dump ports separation of in and out */
/* list of drivers of the one bit */
struct dpdrvr_t {
 word32 drv_val;              /* value of driver with stren (added if need) */ 
 int32 drv_biti;              /* if vec drvr bit to select */
 struct net_pin_t *dpd_npp;
 struct itree_t *dpd_itp;     /* since drvs all over design - itree loc */
 struct dpdrvr_t *dpdrvnxt; 
};

/* record that defines dumpports eval algorithm for one bit of one net */
struct dpctrl_t {
 unsigned dp_eval_typ : 8;    /* type of eval needed for this port net/bit */
 struct dpdrvr_t *dp_indrvs;  /* for hiconn (input) drivers */
 struct dpdrvr_t *dp_outdrvs; /* for loconn (output) drivers */

 /* SJM 10/10/08 - back links for debugging */
 struct net_t *dpc_np;
 int32 dpc_bi;
};

struct qcval_t {
 unsigned qc_active : 1;      /* T => this net(/bit) force or assign active */
 unsigned qc_overridden : 1;  /* T => reg assgn active but force overrides */
 int32 qcrhsbi;               /* if concat, rhs low bit index else -1 */
 int32 qclhsbi;               /* for wire, select lhs low bit index */
 struct st_t *qcstp;
 t_midat *lhsidp;
 struct dceauxlst_t *qcdcep;  /* rhs dce tab of lists */
};

/* qcval union during prep and exec but other uses earlier and for params */
union nqc_u {
 word32 *wp;                  /* for params work saved param val ptr */ 
 int32 npi;                   /* for params fixup sorting/matching val */
 struct net_t *nnxt;          /* during src rd and fixup, nets not yet tab */ 
 struct qcval_t *qcval;       /* per inst. (maybe per bit) qc aux records */
};

/* table of driver and scheduled values for each added vpi_ net driver */
/* know if any at least two, last has both fields nil */
struct vpi_drv_t {
 union pck_u vpi_hasdrv;      /* per inst. net wide driver added table */
 union pck_u vpi_drvwp;       /* per inst. net wide driver values */
 struct dltevlst_t **putv_drv_tedlst;/* per inst per bit pending ev. lists */
 struct dltevlst_t **softforce_putv_tedlst; /* per inst/bit pend ev lists */
};

/* compile time net change info used for building static net changes */
struct net_chg_t {
 unsigned is_lowered : 1;   /* T => this net change used in compiled code */
 unsigned is_wire_ev: 1;    /* T => is wire event */
 unsigned is_const: 1;      /* T => is constant */
 unsigned is_tran_force_vec : 1; /* T => is from a tran force vector */
 unsigned is_printed : 1;   /* T => has been printed to asm file */
 int32 ndx;              /* index identifier */
 int32 i1;               /* range one */
 int32 i2;               /* range two */
 size_t nchg_idp_ofs;    /* idp offset to this net chg */
 struct flowg_t *wire_fgp; /* the process wire flow graph */
 struct flowg_t *nchg_fgp; /* the record nchg flow graph */
 struct flowg_t *process_nchg_fgp;    /* the process nchg flow graph */
 struct net_chg_t *nxt;
};

struct net_t {
 unsigned ntyp : 5;
 unsigned iotyp : 3;          /* I/O direction */
 unsigned n_isaparam : 1;     /* T => net is a parameter */
 unsigned srep : 6;           /* storage representation of value - nva fld */
 unsigned nrngrep : 3;        /* representation for net ranges - nx_u fld */
 unsigned n_isavec : 1;       /* this is a vector */
 unsigned vec_scalared : 1;   /* wire is scalared (bit by bit, T if scalar) */
 unsigned n_isarr : 1;
 unsigned n_isarr_vector : 1; /* T=> is a wire array vector net */
 unsigned n_signed : 1;
 unsigned n_stren : 1;        /* T => needs strength model */
 unsigned n_2state : 1;       /* var decl as one of 2 state reg types */
 unsigned n_capsiz : 2;       /* special capacitor size constant */
 unsigned n_mark : 1;         /* misc. marking flag for var. uses */ 
 unsigned n_multfi : 1;       /* at least one bit fi > 1 */
 unsigned n_isapthsrc : 1;    /* T => port net a pth src (or tc ref ev.) */
 unsigned n_isapthdst : 1;    /* T => port net is a path dest */
 unsigned n_hasdvars : 1;     /* T => at least one inst. dumpvared */
 unsigned n_onprocrhs : 1;    /* appears on some procedural rhs */
 unsigned n_gone : 1;         /* T => net deleted by gate eater */
 /* 03/21/01 - these are fields from removed separate optim table */ 
 unsigned nchg_nd_chgstore : 1;/* need chg store for var */
 unsigned nchg_has_dces : 1;  /* T => var currently has delay ctrls */
 unsigned nchg_has_lds : 1;   /* var has lds (structural from src */
 unsigned frc_assgn_allocated : 1; /* T => force/assign in src or PLI added */
 unsigned dmpv_in_src : 1;    /* T => dumpvars for net in src */
 unsigned dmpp_in_src : 1;    /* T => dumpports for net in src */
 unsigned monit_in_src : 1;   /* monit for var somewhere in src */
 unsigned n_onrhs : 1;        /* appears on some rhs (also declarative) */ 
 unsigned n_onlhs : 1;        /* appears on some lhs */
 unsigned n_drvtyp : 3;       /* for scalar, pre elab p type chg drvr state */
 unsigned n_is_auto : 1;      /* T => is an automatic var  */
 unsigned n_is_auto_var : 1;  /* T => is task automatic var  */
 unsigned n_has_toggle : 1;   /* T => has toggle coverage */
 unsigned n_has_tglbits_excl : 1;/* T => tgl cover some net bits excluded */
#ifdef __XPROP__
 unsigned n_xprop_accum_set : 1;    /* T => xprop accum value is set */
 unsigned n_xprop_accum_set_block1: 1;   /* T => folding for loop inc */
 unsigned n_xprop_accum_set_block2: 1;   /* T => folding for loop inc */
#endif
 unsigned n_cause : 1;        /* net has net change used for gen cancel */
 unsigned n_mipd : 1;         /* net has mipd usage */
 unsigned n_on_nblhs_varndx : 1; /* T -> net is on lhs of varndx <= */
 unsigned cc_need_multfi : 1;
 unsigned has_xmr : 1;        /* T -> has a xmr ref to it */
 unsigned is_loaded : 1;      /* T => net is loaded (passed) to a wrapper */
 unsigned is_printed : 1;     /* T => compiled global is printed */
 unsigned is_iconn_port_scalar_opt : 1; /* T => optim scalar iconn port op */
 unsigned fold_for_inc : 1;   /* T => folding for loop inc */
 int32 nwid;                  /* net width */
 int32 pli_access;            /* pli access level */
 int32 mfi_id;                /* mfi indent if is mfi */
 struct mda_t *mda;
 size_t nva_ofs;              /* offset in mod's variable area for each inst */ 
 union pck_u prm_nva;        /* still need during elab per inst params mem */
 struct sy_t *nsym;
 union nx_u nu;               /* ptr to auxiliary range and delay values */
 struct dcevnt_t *dcelst;     /* fixed list of dce/monit events */
 struct net_pin_t *ndrvs;     /* list of net drivers */
 struct net_pin_t *nlds;      /* list of loads driven by net */
 struct traux_t *ntraux;      /* aux tran channel record */  
 size_t nchgaction_ofs;       /* idp area nchg (or 0 only) assign action bits */
 /* SJM 07/24/00 - need both add driver and soft force for wires */
 struct dltevlst_t **regwir_putv_tedlst; /*  per inst (all bits) ev list */
 struct vpi_drv_t **vpi_ndrvs;/* ptr to table of ptrs to drivers */
 union nqc_u nu2;             /* union - comp. nnxt, and qcval */  
 struct attr_t *nattrs;       /* table of net's attributes */
 struct symtab_t *syt_of_net; /* symbol table net is in */
 struct net_chg_t *nchdp;     /* net changes info header */
 struct flowg_t *nflowg;      /* aux flow for decl processing by net */
 void (*enter_dce)(void);     /* enter address */ 
 void (*enter_npp)(void);     /* enter address */ 
 struct ctev_t **ndel_ctevtab; /* lhsx w/del must have static tevs */
 struct dce_info_t *dcetable; /* dce table for linked dces */
 union dmp_funcu dmpv_funcu; /* dmpv function */
 struct dvchgnets_t *dvns;    /* dump var nets */
 int32 *n_arr_hasdvars;       /* np->n_hasdvars for each array element */
 int32 arr_num_els;           /* number of flattened array elements */
 int32 param_tndx;            /* index into param table */
 struct net_toggle_t *ntgp;   /* toggle fields */
#ifdef __XPROP__
 word32 *xprop_accum;         /* accumulator for xprop values */
 int32 n_xprop_ndx;           /* xprop block net ndx */
#endif
};

struct rt_tgl_t {
 unsigned is_2state : 1;      /* T => toggled net is 2-state */
 struct net_t *np;            /* net this toggle is for */
 word32 *last_valp;           /* last value time value */
 word32 *seen10p;             /* 1->0 bit mask */
 word32 *seen01p;             /* 0->1 bit mask */
 //AIV TOGGLE - skipping toggle count for now
 //int32 *countp;             /* number of times toggled */
 t_midat *idp;                /* idp of this toggle */
 struct rt_tgl_t *tognxt;     /* next on the list */
};

/* make a table info for dces which are linked (fmonitor & qca) */
/* AIV LOOKATME - this can go when fmonitor & qca lowered */
struct dce_info_t {
 struct dcevnt_t **dtable;  /* dce table for linking */
 int32 size;                /* dce table size */
 int32 ndx;                 /* dce table current index */
};

/* symbol table contents and avl tree link info */
struct sy_t {
 unsigned sytyp : 5;
 unsigned sydecl : 1;         /* symbol has been declared */
 unsigned syundefmod : 1;     /* undefined mod or udp */ 
 unsigned cfg_needed : 1;     /* T => symbol is used in config */
 unsigned sy_impldecl : 1;    /* for wire, declared implicitly */
 unsigned sy_argsmac : 1;     /* macro symbol with arguments */
 unsigned sy_giabase : 1;     /* T => symbol is g/i array base */
 unsigned sy_gia_added : 1;   /* this is g/i vector el added symbol */
 unsigned sy_in_genblk : 1;   /* this is local (net?/lb) in gen blk sy tab */
 unsigned gen_add_mstab : 1;  /* T => qualified gen nam moves to mod sym tab */
 unsigned gen_net_impldecl : 1;/* net's sym implicitly decled in xpnd gen blk */
 unsigned syfnam_ind : 16;    /* file symbol defined in */
 int32 sylin_cnt;             /* def. line no. */
 char *synam;
 union el_u el;
 struct sy_t *spltsy;
};

/* elaboration time hierarchical reference record, at end use to fill gr cmps */
/* SJM 02-15-10 - new algorithm - fill complicated elab XMR record first */
struct xmrcmp_t {
 unsigned xmp_petyp : 4;    
 unsigned xmp_is_rooted : 1;  /* T component that is head is rooted */
 unsigned xmp_upwards_rel : 1;  /* T => up rel form path - starts with mod */
 unsigned xmp_err : 1;        /* xmr cmp in tab, but had error grp removed */
 char *xmp_cmpnam;
 char *xmp_alt_cmpnam;        /* after gen, original name (mabye in gen blk) */
 struct expr_t *gcmp_ndp;     /* from XMR parse expr, the XMR expr */
 struct expr_t *xmp_sel_ndp;  /* if constant select, the select expr */
 struct sy_t *xmp_syp;
// ??? - don't need can get from _syp?
 struct symtab_t *xmp_in_sytab;/* sym tab this component in (modsyms for rt) */
 struct symtab_t *xmp_nxtcmp_sytab;/* sym tab if exists down ncmp in */
 struct genblk_t *xmp_in_gblkp;
 struct sy_t *xmp_uprel_msym;  /* uprel module symbol */
};

/* separate work array storage of global component names */
struct glbncmp_t {
 int32 gncsiz;                /* size of largest alloc component (reused) */
 char *gncmp;
};

union targ_u {
 struct itree_t *targitp;     /* only for rooted - one target itree place */
 struct itree_t **uprel_itps; /* parallel to mod itps dest itree table */
}; 

/* global ref. info - master global rec. also used during simulation */
struct gref_t {
 unsigned upwards_rel : 1;    /* T => up rel form path starts with mod */
 unsigned is_rooted : 1;      /* T => path starts at top module root */
 unsigned path_has_isel : 1;  /* T => down or root path has inst arr select */
 unsigned gr_inst_ok : 1;     /* T => can be inst flg for chk, set in src 2 */
 unsigned gr_defparam : 1;    /* T => allow parameter as net tail */
 unsigned gr_has_genitem : 1; /* T => has a gen item in xmr cmp path */
 unsigned gr_gone : 1;        /* T => for defparam processing - now gone */
 unsigned gr_err : 1;         /* T => global is incorrect */
 unsigned is_loaded : 1;      /* T => grp is loaded */
 unsigned is_printed : 1;     /* T => compiled global is printed */
 unsigned grfnam_ind : 16;    /* file location of ref. */
 int32 grflin_cnt;            /* line location of ref. */
 int32 last_gri;              /* last - 1 (1 before target) symbol in path */

 char *gnam;                  /* name */
 struct expr_t *gxndp;        /* back link to expr. node containing xmr */
 struct expr_t *glbref;       /* original gref expr for inst. array eval. */
 struct symtab_t *grsytp;     /* symtab where ref. appears */
 struct mod_t *targmdp;       /* module target declared in */
 struct task_t *targtskp;     /* if non NULL, task target declared in */
 struct mod_t *gin_mdp;       /* place where gref used, for netchg prop. */
 struct sy_t **grcmps;        /* table of path symbols (prep fixes ia sels) */
 struct expr_t **grxcmps;     /* table of arr of inst path symbol sel exprs */
 union targ_u targu;          /* up rel. itp list or rooted 1 target itp */
 struct sy_t *targsyp;        /* actual end path symbol in target module */
 struct xmrcmp_t **gr_xmptab; /* for hierchical name resolving, wrk d.s */
 int32 gr_num_xmps;           /* XMR hierarchical path len */
 struct gref_t *new_to_old_grp; /* ptr from orig to new split of grp */
 struct genblk_t *gr_gblk_in; /* for xmr gen blk in, smallest containing */
};

/* symbol table - separate for each module */
/* needs union here ? */
struct symtab_t {
 unsigned freezes : 1;
 unsigned numsyms : 31;
 struct tnode_t *n_head;
 struct sy_t **stsyms;        /* non null means frozed form */
 struct symtab_t *sytpar;     /* parent is enclosing scope */
 struct symtab_t *sytsib;     /* sibling is disjoint32 same level scope */
 struct symtab_t *sytofs;     /* offspring is list hdr of enclosed scopes */
 struct symtab_t *linkto_cp_osytp; /* for sym tab copy in old pt to new */
 struct sy_t *sypofsyt;       /* symbol this table is symbol table of */
 struct genblk_t *gblkofsyt;  /* for gen blk symtabs, gen blk symtab in */
};

/* list for saving timing check chk event changes for end of time slot */
struct tc_pendlst_t {
 struct chktchg_t *tc_chkchgp;
 t_midat *tc_idp;
 struct tc_pendlst_t *tc_plnxt;
};

union tchg_u {
 struct tchk_t *chgtcp;
 struct spcpth_t *chgpthp;
};

/* time of last chg net pin record - np from context, bit from npp rec. */
struct tchg_t {
 union tchg_u chgu;           /* union pointer to associated master */
 size_t oldval_ofs;           /* idp ofs of value of source bit */
 size_t lastchg_ofs;          /* last chg idp ofs time for 1 bit */
};

/* time check change record - access tchk record thru start change */
struct chktchg_t {
 struct tchg_t *startchgp;    /* corresponding start wire time change */
 size_t chkoldval_ofs;
 size_t chkactive_ofs;        /* T => check is active flag */
};

/* simulation per bit path delay element */
struct pthdst_t {
 struct tchg_t *pstchgp;      /* path src time change and indir. to path */ 
 struct pthdst_t *pdnxt;      /* destination bit can have >1 sources */
};

/* one path elment */
struct pathel_t {
 int32 pthi1, pthi2;          /* specparam then index number value */
 struct net_t *penp;          /* path input/out wire - NULL if removed */
}; 

/* work data struct for checking multiple same sdpds */
struct xpnd_pthel_t {
 unsigned in_equiv_set : 1;
 struct spcpth_t *pthp;
 int32 peii, peoi; 
 struct xpnd_pthel_t *xpthnxt;
};

struct spcpth_t {
 unsigned pthtyp : 2;         /* type of path (full or *>) */ 
 unsigned pth_gone : 1;       /* must ignore because of serious error */
 unsigned pth_as_xprs : 1;    /* T => fixup not done path els still exprs */
 unsigned pth_delrep : 5;     /* delay representation for path */
 unsigned pthpolar : 2;       /* simple path polarity (no sim meaning) */
 unsigned pthedge : 8;        /* if edge, edge sensitive path */
 unsigned dsrc_polar : 2;     /* if edge sensitive polarity */
 unsigned pth_ifnone : 1;     /* T => condition is ifnone and other sdpds */
 unsigned pth_0del_rem : 1;   /* T => removed from 0 delay */ 
 int32 last_pein;
 int32 last_peout;
 int32 spcpth_id;             /* generate a number (unique id) */
 struct sy_t *pthsym;         /* built symbol for identifying path */
 struct pathel_t *peins;      /* array of path input elements */
 struct pathel_t *peouts;     /* array of path output elements */
 union del_u pth_du;          /* delay value */
 struct expr_t *datasrcx;     /* non sim polarity expr, can be FCCOM list */
 struct expr_t *pthcondx;     /* for if (cond) sdpd, the cond expr. */
 struct spcpth_t *spcpthnxt;
};

/* timing check system task master record */
struct tchk_t {
 unsigned tchktyp : 8;        /* timing check type */
 unsigned tc_delrep : 5;      /* limit delay type (will be same for both) */
 unsigned tc_delrep2 : 5;     /* type of 2nd limit if present */ 
 unsigned tc_gone : 1;        /* must ignore because of error */
 unsigned tc_supofsuphld : 1; /* setup (added) part of setup hold */
 unsigned tc_recofrecrem : 1; /* recovery (added) part of recrem */
 unsigned tc_haslim2 : 1;     /* lim2 value present */
 unsigned startedge : 8;      /* edge byte (pli 1 bit per rf coding) */
 unsigned chkedge : 8;        /* edge byte (pli 1 bit per rf coding) */
 struct sy_t *tcsym;          /* symbol with constructed name for del set */
 struct expr_t *startxp;      /* event (reference) expr */
 struct expr_t *startcondx;   /* &&& ref. event or edge path delay sel. */
 struct expr_t *chkxp;        /* event (data - check) expr */
 struct expr_t *chkcondx;     /* &&& data event or edge path delay sel. */
 /* SJM 06-18-09 - new negative del/delayed var flds for setuphold and recrem */
 struct expr_t *stamptim_condx; /* optional setuphld/recrem stamp del expr */
 struct expr_t *chktim_condx; /* optional setuphld/recrem chk del expr */
 struct expr_t *delayed_refx; /* optional setuphld/recrem delayed ref var x */
 struct expr_t *delayed_datx; /* optional setuphld/recrem delayed data var x */

 union del_u tclim_du;        /* 1st limit as delay */
 union del_u tclim2_du;       /* 2nd optional limit as delay */
 struct net_t *ntfy_np;       /* notify wire (known during fix up) */
 struct tchk_t *tchknxt;      /* next in current specify block */
};

/* concatenation of all module specify items */
struct spfy_t {
 struct symtab_t *spfsyms;    /* specify symbol table for specparams */
 struct spcpth_t *spcpths;    /* delay paths */
 struct tchk_t *tchks;        /* timing checks */
 struct net_t *msprms;        /* module's specify parameters */
 int32 sprmnum;               /* number of specify parameters in table */
};

/* SJM 07/10/01 - d.s. for new delay net load propagation algorithm */
/* for inter module paths, each src-dest pair has one of these */
struct impth_t {
 unsigned impth_delrep : 8;   /* delrep */
 int32 sbi;                   /* and bit */
 union del_u impth_du;        /* for inter mod non IS del for src/dst pair */
 struct net_t *snp;           /* source net */
 struct itree_t *sitp;        /* and itree loc */
 word64 lastchg;              /* last chg time for this 1 pth bit of inst */
 struct impth_t *impthnxt;    /* for || paths dst has >1 src with diff del */
};

/* mipd npp elnpp field points to per bit array mipd records */
struct mipd_t {
 unsigned no_mipd : 1;        /* T => no mipd delay for this bit */
 unsigned pth_mipd : 1;       /* T => do not treat as src-dest inter mod pth */
 unsigned pb_mipd_delrep : 5; /* bit's delay type */ 
 union del_u pb_mipd_du;      /* bit's delay - max if src-dst impth */
 byte *oldvals;               /* per inst array of old values */
 struct tev_t **mipdschd_tevs;/* per inst sched. event ndxes (-1 if none) */
 struct impth_t **impthtab;   /* per inst inter mod src-dst pth ptr list */
};

struct srtmp_t {
 int32 mppos;
 struct mod_pin_t *smp;
};

/* top level n.l. entry points - this is a real user defined module */
struct mod_t {
 unsigned minstnum : 2;       /* static inst no. 0, 1, 2 (more than once) */
 unsigned mhassts : 1;        /* T => module has strength wire(s) */
 unsigned msplit : 1;         /* T => module created from defparam splitting */
 unsigned mpndsplit : 1;      /* T => split off from # params */
 unsigned mhassplit : 1;      /* T => modules split off from this one */
 unsigned mgone : 1;          /* T => split from defparam but same params */
 unsigned msplitpth : 1;      /* T => module comp. of split off chain */
 unsigned mwiddetdone : 1;    /* T => mod width determing param marking done */
 unsigned mhas_widthdet : 1;  /* T => module has width determin param */
 unsigned mhas_indir_widdet : 1; /* T => module has indr width det param */
 unsigned dfp_allmodinsts_split : 1; /* T => defparam to mod - must splt all */
 unsigned mgia_rngdone : 1;   /* T => mod in array of g/i rng marking done */
 unsigned m_has_garrs : 1;    /* T => mod has at one arrays of gates */ 
 unsigned m_has_iarrs : 1;    /* T => mod has at one arrays of insts */ 
 unsigned mpndprm_ingirng : 1;/* T => module has pound param in gi range */ 
 unsigned mhasisform : 1;     /* T => at least oe IS form constant in mod */
 unsigned mtime_units : 4;    /* no. of significant units of time rounded */
 unsigned mtime_prec : 4;     /* prec. - exp. 0 (1 sec.) - 15 (1 fs) */
 unsigned mno_unitcnv : 1;    /* F => need for delay unit conv. */
 unsigned m_iscell : 1;       /* T => module is asic style cell */
 unsigned m_hascells : 1;     /* T => module contains asic style cells */
 unsigned mod_hasdvars : 1;   /* T => for at least 1 inst. all vars dumped */
 unsigned mod_dvars_in_src : 1;/* T => all vars dumpved in src */
 unsigned mod_dumpports_in_src : 1;/* T => dump ports in src */
 unsigned mod_dumiact : 1;    /* T => dummy iact. info mod. */
 unsigned mod_rhs_param : 1;  /* T => mod has param def with rhs param */ 
 unsigned mod_hasbidtran : 1; /* T => has inout mod. port - tran chan */
 unsigned mod_hastran : 1;    /* T => has tran gate - tran chan */
 unsigned mod_gatetran : 1;   /* T => module has tran gate in it */
 unsigned mod_has_mipds : 1;  /* T => mod has SDF or vpi_ only set mipds */  
 unsigned mod_parms_gd : 1;   /* T => all dependent and pound params right */
 unsigned mod_1bcas : 1;      /* T => contains 1 bit ca - special for vpi */
 unsigned mod_lofp_decl : 1;  /* T => port decl uses list of ports form */ 
 unsigned mod_dfltntyp : 4;   /* T => for vpi, from directive net dflt type */
 unsigned mod_uncdrv : 8;     /* for vpi, mod val of unc drive directive */ 
 unsigned m_inconfig : 1;     /* T => module is from a config file */
 unsigned cfg_scanned : 1;    /* T => module has been scanned by config */
 unsigned mhas_frcassgn : 1;  /* T => mod contains force/assign(s) */
 unsigned m_gia_in_gblks : 1; /* T => mod has arrays of g/i in gen blks */
 unsigned m_tfs_in_gblks : 1; /* T => mod contains tsks/funcs in gen blks */ 
 unsigned m_xmrs_in_gblks : 1;/* T => at least 1 xmr/dfp in mod in a gen blk */
 unsigned m_dfps_in_gblks : 1;/* T => at least 1 dfp in mod in a gen blk */
 unsigned m_gen_xpnded : 1;   /* T => gens in this mod expended */
 unsigned m_gened_remove : 1; /* T => in never used generate mark remove */
 unsigned m_maybe_gened : 1;  /* T => use in gen src - may be gened top */
 unsigned m_no_param_match : 1; /* T => turn off # param matching */
 unsigned m_has_toggle_cover : 1;/* T => module contains net toggle cover */
 unsigned m_has_stmt_cover : 1;  /* T => module contains stmt cover */
 unsigned m_has_event_cover : 1; /* T => module contains event cover */
 unsigned m_combined_into : 1;   /* T => module has been combined into */
 unsigned m_using_init_file : 1; /* T => uses this modules asm init file */
 unsigned m_opt_pli_bits_set : 1; /* T => opt config pli bits set */
#ifdef __XPROP__
 unsigned m_use_xprop : 1;    /* this module has xprop on */  
 unsigned m_use_xprop2 : 1;   /* this module has xprop2 (x flooding) on */
 unsigned m_use_xprop_and_or_x : 1; /* this mod &, |, &&, || bit x preserve */
#endif
 unsigned m_gened_fstvars : 1; /* T => fst vars generated */

 int32 flatinum;              /* num. of flattened instances of module */
 int32 mpnum;                 /* number of module ports */
 int32 minum;                 /* number of instances in module */
 int32 mgnum;                 /* number of gates in module */
 int32 mcanum;                /* number of non 1 bit cas in module */ 
 int32 mnnum;                 /* number of nets in module */  
 int32 mtotvarnum;            /* total number of variables mod+task */
 int32 mprmnum;               /* number of pound params defined */ 
 int32 mlocprmnum;            /* number of local params defined */ 
 int32 mlpcnt;                /* mod. inst. loop count (static level) */
 int32 m_idnum;               /* index (id) no. for mod - for .comm */
 int32 mod_last_lini;         /* line no. of end (mabye in next file) */
 int32 mod_last_ifi;          /* and file in case spans multiple */
 int32 mversno;               /* version number for split modules */
 int32 lastinum;              /* while assigning inums - last used */
 int32 mstnum;                /* size of mod's stmt tab */
 int32 mstnum_no_task;        /* size of mod's stmt tab not including tasks */
 int32 prov_mstnum;           /* provisional mod stmt ndx size for storage */
 int32 mgrnum;                /* number of grefs in module */
 int32 mdfp_grnum;            /* SJM 08-26-11 - now sep defparam grefs */
 int32 mdfp_sav_grnum;        /* num. of to put back pre gen defp assoc xmrs */
 int32 mpthnum;
 int32 mnppnum;               /* num of npps (size of index) */
 int32 dctrl_size;            /* size of dctrl events array */
 int32 mod_ndx_seq_no;        /* need separate counter per mod for XMRs */
 int32 asm_partition_cnt;     /* asm files partitioned into N files */    
 struct sy_t *msym;           /* symbol from separate module name space */
 struct symtab_t *msymtab;    /* symbol table for objects in module */
 struct cfglib_t *mod_cfglbp; /* config lib this mod's cells bound using */
 struct mod_pin_t *mpins;     /* defined ports first list then arr. */
 struct gate_t *mgates;       /* array of gates, udps and assigns */
 struct conta_t *mcas;        /* module cont. assigns */
 struct inst_t *minsts;       /* array of module instance records */
 struct net_t *mprms;         /* param definitions - list then tab */
 struct net_t *mlocprms;      /* local param definitions - list then tab */
 struct net_t *mnets;         /* list then array of nets in module */
 /* SJM 12/19/04 - only fixed ones from conn npin - vpi added malloced */
 struct net_pin_t *mnpins;    /* table of all npins in module */
 struct itree_t **moditps;    /* itnum to itree struct mapping table */
 byte *m_itps_tgl_cover;      /* per inst (flat inum) of mod has some tgl */
 struct mod_t *mnxt;          /* next defined module */

 /* new Verilog 2000 fields */
 struct attr_t *mattrs;       /* mod attrs - used only if inst has no attr */
 struct varinitlst_t *mvarinits; /* list of var (not net) init decls */
 struct tev_t ***mgateout_cbs;/* per gate ptr to per inst list of vc cbs */
 struct genitem_t *mgenitems; /* list of generate items in this mod */ 
 struct symtab_t *mgen_symtab;/* mod's gen symbol table */

 /* LOOKATME - these are compile only and can maybe be freed after fixup */
 struct mod_t *mlevnxt;       /* link to next same level module */
 struct mod_t *mspltmst;      /* pointer to defparam master if split off */
 struct mod_t *mpndspltmst;   /* pointer to pound master if split off */

 /* AIV 10/16/10 - new values to catch multiple #para split values */
 struct mod_t *split_hd;      /* module split list head */
 struct mod_t *split_tail;    /* module split list tail */
 struct mod_t *split_nxt;     /* next split mod */
 struct inst_t *inst_split;   /* instance split from */
 struct mod_t *recomb_to_mdp; /* for recombining - recombs to this one */

 int32 mlevel;                /* current mlevel for the splitting */
 struct cell_t *mcells;       /* unordered list of module objects */
 struct srtmp_t *smpins;      /* sorted table of module pins */
 struct srcloc_t **iploctab;  /* || to insts ptr tab to tab of port locs */

 struct dfparam_t *mdfps;     /* modules defparams */
 struct dfparam_t *sav_mdfps; /* place to copy dfps to put back pre gen */
 struct task_t *mtasks;       /* tasks declared in module */
 struct ialst_t *ialst;       /* initial/always list */
 struct spfy_t *mspfy;        /* module's specify elements */

 word32 *mod_idata;            /* RT ptr to base of mod's all inst data */ 
 size_t mod_idata_siz;         /* wrd size of this mod's each inst data area */
 size_t mod_idata_siz_presim;  /* original size of mod sim prior to sim */
 size_t task_start_ofs;        /* offset where task vars start */

 /* per module record tables - for optimized code and save/restart */
 struct idp_map_t **mod_idp_map;/* idp data struct map of 1 instidp area */
 struct expr_tab_t *expr_tab; /* table info of all sys calls in mod */
 struct avlhd_t *isnum_tree;  /* holds isnum objects to place into idp */
 struct delctrl_t **dctrl_array; /* array of dctrl events */
 struct flowg_t *mod_flowg;   /* list of ia and tf flow graphs for mod */
 struct ctev_t *ctev_list_hd; /* hd of this mods CT (static) ctevs structs */
#ifdef __XPROP__
 struct task_t *xprop_nb_taskp; /* dummy xprop non-blocking stmt holder */
#endif
 struct st_t **mstmts;        /* per mod array of stmts */
 struct st_t **prov_mstndx;   /* provisional index (ptr to stmt) */ 
 struct gref_t *mgrtab;       /* list of xmr's appearing in this mod. */
 struct spcpth_t **m_pth_ndx; /* per mod index of all specify delay paths */
 struct net_pin_t **m_npp_ndx;/* per mod index of all (lds & drvs) npps */
 struct dceauxlst_t *dcep_lst_xmrp;  /* dcep with dce_xprs xmr to this mod */
};

/* AIV 03/26/07 - no more expression table for all expression */
/* this holds the expression for sys funcs which are currently linked in */
/* if syscalls were lowered could remove this */
/* AIV 12/10/07 - also holds expression for qc force wrapper calls */
struct expr_tab_t {
 struct expr_t **table;  /* per mod table of sys func call records */    
 int32 num;              /* size of sys call tab */
 size_t size;            /* mod sys call expr size */
};

/* prep time record for expr tabs */
struct prep_obj_t {
 int32 id;                  /* value added to the isnum tree */
 int32 xvi;                 /* index into contab */
 int32 blen;                /* bit blen */
 void *obj;                 /* system function call */
 size_t isnum_idp_ofs;      /* idp offset if expr is an IS num in idp area */
};
 
/*
 * run time only structures
 */
/* doubly linked list of events for cancelling some */ 
struct dltevlst_t {
 struct tev_t *tevp;
 struct dltevlst_t *telp, *terp;
};

/* singly linked list of events for cancel (short search from front) */ 
struct tevlst_t {
 struct tev_t *tevp;
 struct tevlst_t *telnxt;
};

/* threads - because associated with an event, inst. specific */
struct thread_t {
 unsigned tsk_stouts : 1;     /* T => when task returns has outs to store */
 unsigned th_dsable : 1;      /* thread done because disabled */
 unsigned th_rhsform : 1;     /* T => rhs form so value in thread record */
 unsigned th_fj : 1;          /* T => thread is fj - assoc. task is upward */
 unsigned th_postamble : 1;   /* T => pending task needs end store/trace */
 unsigned th_ialw : 1;        /* T => thread in initial/always list */
 unsigned thofscnt : 24;      /* num of still active fork-join offspring */
 int32 thenbl_slin_cnt;       /* and line number */
 int32 th_rhswlen;            /* word32 length of rhs value for disable */
 int32 thd_ret_lab_ndx;       /* task return jump to label index */  
 word32 thenbl_sfnam_ind;     /* file index of place thread enabled from */

 struct st_t *thnxtstp;       /* next st. in thread to execute (resume pc) */
 /* tree of 2 way linked sibling subthread lists */
 struct thread_t *thpar;      /* thread that invoked this one */
 struct thread_t *thright;    /* double linked same level right ptr */
 struct thread_t *thleft;     /* double linked same level right ptr */
 struct thread_t *thofs;      /* list of threads, enabled by this one */
 struct tskthrd_t *tthlst;    /* ptr to this task assoc. thrd list el. */
 struct tev_t *thdtevp;       /* if thread has scheduled event, ptr of it */
 struct task_t *assoc_tsk;    /* if created from task, connection to it */

 /* AIV 10/19/07 - changed to int only needed for dctp_tev_ofs */
 size_t th_dctp_tev_ofs;       /* if armed but not trig. ev ctrl, ptr to it */
 word32 *th_rhswp;            /* for rhs delay/event controls, rhs value */  
 t_midat *th_idp;             /* itree loc. (index) thread runs in */
 t_midat *th_save_idp;        /* saved idp area for auto tasks threads */
 struct hctrl_t *th_hctrl;    /* for iact, pointer to control rec. */
};

union ten_u {
 struct net_t *np;
 struct mod_pin_t *mpp;
};

/* net bit or MIPD event storage - must be alloced and freed as used */
struct tenp_t {
 int32 nbi;
 union ten_u tenu;
};

/* AIV 11/21/07 - need lhs for nb var ndx can be either lhsx (interp) or */
/* net np for the compiler */
union nblhs_u {
 struct expr_t *nblhsxp;      /* if var ndx expr (maybe cat) const ndx copy */
 struct net_t *nblhsnp;
};

/* storage for scheduled but not matured non blocking assign event */ 
struct tenbpa_t {
 word32 *nbawp;
 int32 nbytes;                /* store the num bytes of the stored area */
 int32 bi;                    /* AIV 11/21/07 - the bit/arr ndx into the lhs */
 struct st_t *nbastp;
 union nblhs_u nblhsu; 
 struct expr_t *nblhsxp;      /* if var ndx expr (maybe cat) const ndx copy */
 struct delctrl_t *nbdctp;
 struct nchglst_t *nchglp;    /* static (maybe alloced) net change */
};

/* tf strdelputp event storage - one schedule change (tev has instance) */
struct tedputp_t {
 struct tfrec_t *tedtfrp;
 int32 tedpnum;
 word32 *tedwp;               /* point to both half - know exact lhs word32 len */
};

/* vpi put value event storage (for both reg net driver assign */
struct teputv_t { 
 int32 nbi;
 int32 di;                    /* for mult. drivers the ndx no. in table */
 struct net_t *np;
 word32 *putv_wp;
 struct h_t *evnt_hp;         /* ptr back to event for cancelling */
};

union te_u {
 struct st_t *stp;
 struct thread_t *tethrd;
 struct gate_t *tegp;
 struct conta_t *tecap;
 struct tenp_t *tenp;
 struct tenbpa_t *tenbpa;
 struct tfrec_t *tetfrec;
 struct tedputp_t *tedputp;
 struct teputv_t *teputvp; 
 word32 bi;                      /* mipd index value */
 word32 *rhs_wp;                 /* rhs nb value pointer */
 struct h_t *tehp;
};

/* extra word value for events for the compiler */
/* these must be word for 64-bit */
union te2_u {
 word32 nb_rhs_size;           /* size of nb rhs to free */
 word32 bi;                    /* lhs bit index */
};

struct tev_t {
 unsigned free_it : 1;        /* this event needs to be freed at rt */
 unsigned nb_evctrl : 1;      /* for non blocking event is event control */
 unsigned te_trdecay : 1;     /* event is trireg decay */
 unsigned gev_acc : 1;        /* accelerated gate value assign */
 unsigned vpi_reschd : 1;     /* T => vpi_ time cb moves to other slot part */
 unsigned vpi_onfront : 1;    /* T => cb sim time start, add on fut. front */
 unsigned vpi_regwir_putv : 1;/* T => putv to reg/wire soft force */
 /* AIV LOOKATME - could use this field for something alloc in te_u ???? */
 unsigned align_filler : 9;   /* empty space to align on word boundary */
// AIV LOOKATME - don't really need both of these could just use outv??????
 byte outv;                   /* for gate output value */
 byte scalar_nb_val;          /* scalar non-blocking value */
 union te_u tu;
 word32 trigger; 
 void (*enterptr)(void);      /* enter address for this event */ 
 void (*next_enterptr)(void); /* next enter event may have to free it */ 
#ifdef __STREE__
 struct tqnode_t *nodep;     /* AIV timing tree node so no search is needed */
#else
 struct heap_t *time_hp;      /* last event at given heap time */
#endif
 word64 etime;                /* absolute time not delay */
 t_midat *te_idp;             /* idp area */
 word64 delay;                /* constant delay value -1 for variable */
 struct tev_t *tenxtp;
 struct tev_t *teprevp;
 union te2_u t2u;     /* extra word storage for the compiler to avoid malloc */
 //AIV LOOKATME - if going to waste this space could use for other storage
 //and make this a union????
 word32 sel_ndx;      /* used to hold array select index for <= saving */
};

struct telhdr_t {
 struct tev_t *te_hdrp, *te_endp;
 int32 num_events;
};

/* list element for pending net changes to process after event done */
struct nchglst_t {
//AIV64 - AIV FIXME - trigged/delayed_mipd are flags and should be
//int32 aligned on 4 bytes getting to work via movq no movl
 word32 triggered;             /* T => event has been triggered */
 void (*process_enterptr)(void);/* process nchg enter address */ 
 word32 delayed_mipd;          /* T - 2nd after schedule from ev process */
 int32 bi1, bi2;
 struct net_t *chgnp;
 t_midat *nchg_idp;
 struct nchglst_t *nchglnxt;
};

struct contab_info_t {
 int32 cwid;
 int32 xvi;
 struct contab_info_t *cnxt;
};

/* extern defined in cvc.c */
/* various simulation counting variables */
extern char *__vers;          /* actual product info */
extern char *__vers2;
extern char *__ofdt;
extern char *__platform;
extern char *__start_sp, *__end_sp;/* pointer for "big" memory allocator */
extern char *__pvdate;        /* date in unix form */
extern char *__pv_timestamp;  /* timestamp for design */
extern time_t __start_time;   /* start wall clock times in secs. */
extern time_t __start_mstime; /* start millisecond part */
extern time_t __end_comp_time;/* end of compilation time */
extern time_t __end_comp_mstime;
extern time_t __end_prep_time;/* end of preparation time */
extern time_t __end_prep_mstime;
extern time_t __end_time;     /* start and end wall clock times */
extern time_t __end_mstime;   /* start and end wall clock times */

/* various file variables and global data base flags (i/o vars) */
extern char **__in_fils;      /* malloced input file list from args */
extern int32 __siz_in_fils;   /* current size of input files */
extern int32 __last_inf;      /* last input file in list */
extern int32 __last_optf;     /* last option file */
extern int32 __last_lbf;      /* last lib/inc file (starts last_inf + 1) */
extern int32 __last_srcf;     /* last src containing file for debugger */
extern struct incloc_t *__inclst_hdr; /* header of included files list */
extern struct incloc_t *__inclst_end; /* end of included files list */
extern struct filpos_t *__filpostab; /* in fils size tab of file line pos. */
extern FILE *__save_log_s;    /* if $nolog executed, value to use if log */
extern int32 __echo_iactcmds_tolog; /* T => echo interactive cmds to log file */
extern FILE *__save_key_s;    /* if $nolog executed, value to use if log */
extern int32 __nokey_seen;    /* $nokey executed and no key */
extern FILE *__in_s;
extern FILE *__log_s;
extern FILE *__cmd_s;         /* command file source or null for tty */ 
extern FILE *__key_s;         /* if key_s nil but key_fnam not, must open */
extern struct optlst_t *__opt_hdr;   /* header of expanded option list */
extern struct optlst_t *__opt_end;   /* wrk end of expanded option list */
//AIV 06-31-09 - FIXME??? this can be right since setting bit numbers up to 64 
extern word32 *__wsupptab;    /* tab (1 bit/msg) for warn and iact suppress */
extern char *__blnkline;      /* work blank line */
extern char __pv_homedir[RECLEN]; /* home dir - . if HOME env. not set */
extern struct mcchan_t __mulchan_tab[32];/* mc desc. tab (32 built in Ver) */ 
extern struct fiofd_t **__fio_fdtab; /* array of ptrs to file io stream */
extern char *__fiolp;         /* fio file input work string ptr */
extern char *__fiofp;         /* fio file input work fmt string ptr */
extern long __scanf_pos;      /* byte offset position of scanf in file */
extern sighandler *__old_int_sig;  /* value of quit (^c) signal on entry */
extern int32 __force_base;    /* for output force base if not BASENONE */
extern struct vinstk_t **__vinstk;/* open file/macro list in stack form */
extern struct vinstk_t *__visp;/* pointer to top of open input stack */
extern int32 __vin_top;       /* index of top of current file stack */
extern char *__log_fnam;      /* log file for all terminal output */
extern char *__sdf_opt_log_fnam; /* sdf log file if set by cmd arg */
extern FILE *__sdf_opt_log_s; /* and open file ptr */
extern int32 __sdf_no_warns;  /* T => don't print any SDF warning msgs */
extern int32 __sdf_no_errs;   /* T => don't print any SDF error msgs */
extern char *__cmd_fnam;      /* command interact. input file name */
extern char *__cmd_start_fnam;/* -i startup interactive input file name */
extern char *__key_fnam;      /* key file name and stream */
extern FILE *__tr_s;          /* trace output file - can be stdout */
extern char *__tr_fnam;
extern int32 __cmd_ifi;       /* constant command in_fils index */
extern char *__lic_path;      /* +licpath [path] if option used */
extern FILE *__sdf_s;         /* current SDF back annotate file/stream */
extern struct sdfnamlst_t *__sdflst; /* list of sdf annotate option files */
extern struct sdf_tskenlst_t *__sdftskenlst; /* sdf annotate tsks in src lst */
extern struct sdf_tskenlst_t *__sdftelst_end;/* end of list for src order */
extern int32 __sdf_sav_enum;  /* saved error num. for annotate inhibit */
extern int32 __sdf_sav_maxerrs; /* saved max errors so won't stop */
extern int32 __has_sdfann_calls;/* T => no sdf annotate systsk calls in src */ 
extern int32 __sdf_active;    /* T => annotating SDF - for PLI erro code  */
extern int32 __sdf_during_sim;/* T => can't compile SDF file before sim */
extern struct mod_t *__sdf_mdp; /* special sdf context mod */

/* cfg variables */
extern char *__cmdl_library;  /* library name to file off the command line */
extern struct mapfiles_t *__map_files_hd; /* hdr of map files from cmd args */
extern struct mapfiles_t *__map_files_tail; /* end of map file list */
extern struct cfglib_t *__cfglib_hd; /* head of list of libs for cfg */
extern struct cfglib_t *__cfglib_tail; /* and tail */
extern struct cfg_t *__cfg_hd;/* head of list of cfgs */
extern struct cfg_t *__cur_cfg;/* current cfg */
extern struct mod_t *__cfg_mdp;/* SJM - remove me - why global */
extern char **__bind_inam_comptab;/* during cfg binding, comp descent comps */ 
extern int32 __siz_bind_comps;/* current malloc size of table */
extern int32 __last_bind_comp_ndx;/* last currently used comp end index */ 
extern int32 __cfg_verbose;   /* T => emit cfg reading verbose messages */ 

/* option config and plitab processing variables */
extern struct ocfil_lst_t *__optcfg_fils; /* optconfig file names */
extern struct ocfil_lst_t *__last_optcfg_fil; /* and tail */
extern struct ocfg_stmt_t *__ocfg_stmts; /* o cfg stmts from all opts lst */ 
extern struct oc_vtok_t *__wrk_ocvtok_hd; /* opt cfg wrd token list hd */
extern struct oc_vtok_t *__wrk_ocvtok_end;/* and current end */
extern char __cur_optcfg_cntxt_str[RECLEN]; /* cntxt name for optcfg warns */ 

/* file variables */
extern int32 __cur_infi;      /* index in in_fils of current file */
extern struct optlst_t *__new_opt_hdr;/* header of expanded option list */
extern struct optlst_t *__new_opt_end;/* wrk end of expanded option list */
extern struct optlst_t *__log_olp;   /* log option, nil if none */
extern struct optlst_t *__help_olp;  /* help option, nil if none */
extern struct optlst_t *__quiet_olp; /* quiet option, nil if none */
extern struct optlst_t *__verb_olp;  /* verbose option, nil if none */  
extern struct optlst_t *__verb_mem_olp;  /* verbose mem option, nil if none */  
extern int32 __vpi_argc;      /* global arg count for vpi */
extern char **__vpi_argv;     /* global arg array for vpi */
extern char *__vpi_argv0;     /* argv execed program name */
extern char *__cur_fnam;      /* being read file name for errors */
extern int32 __cur_fnam_ind;  /* index in in_fils of cur_fnam */
extern int32 __sfnam_ind;     /* global file index for current stmt. */
extern int32 __slin_cnt;      /* global line no. for currently check stmt */
extern int32 __vpifnam_ind;   /* vpi_ global current file index */
extern int32 __vpilin_cnt;    /* vpi_ global current line no. */
extern struct expr_t *__srm_xp; /* current string 'file' for sreadmem */
extern char *__srm_strp;      /* char. pos. in sreadmem string */
extern char *__srm_strp_beg;  /* work alloced location for sreadmem string */
extern int32 __srm_strp_len;  /* alloced length */
extern int32 __srm_stargi;    /* current string position number */
extern int32 __in_ifdef_level;/* current processing `ifdef level */ 
extern int32 __have_t_ignore_elsif[MAXLEVELS]; /* T in else(if), seen a T */
extern int32 __ifdef_skipping;/* T = skipping not included ifdef section */
extern int32 __rding_top_level; /* T => reading outside top level construct */

/* variables for batch tracing */
extern word64 __last_trtime;  /* last trace statement time */
extern word64 __last_evtrtime;/* last event trace time */
extern t_midat *__last_tridp; /* last event traced inst. itree index */ 

/* command processing variables and temps */
extern int32 __pv_err_cnt, __pv_warn_cnt; /* error counts */
extern int32 __inform_cnt;    /* number of informs */
extern int32 __outlinpos;     /* current trunc. output line pos. */
extern long __mem_use;        /* counts allocated mem for debugging */
extern long __mem_allocated;  /* bytes allocated */
extern long __mem_freed;      /* bytes freed */
extern long __memstr_use;     /* counts allocated string mem for debugging */
extern long __arrvmem_use;    /* allocated bytes for Verilog arrays */
extern long __mem_udpuse;     /* number of bytes used by udp tables */
extern word64 __tim_zero;     /* place for time of constant 0 */
extern int32 __num_glbs;      /* total no. of globals in design */
extern int32 __num_inmodglbs; /* glbs thar resolve to intra module refs. */
extern int32 __num_uprel_glbs;/* number of upward relative globals */
extern int32 __nets_removable;/* flat no. of deletable nets */
extern int32 __flnets_removable;/* removable static nets */
extern int32 __gates_removable; /* removable static gates */
extern int32 __flgates_removable; /* flat no. of deletable gates */
extern int32 __contas_removable; /* removabale static cont. assigns */
extern int32 __flcontas_removable; /* flat no. of deletable cont. assigns */

/* special allocate free variables */
extern struct ncablk_t *__hdr_ncablks; /* blocks used for ncomp recs */
extern int32 __ncablk_nxti;   /* index of next free pos. */
extern struct cpblk_t *__hdr_cpblks; /* blocks used for cell recs*/
extern int32 __cpblk_nxti;    /* index of next free pos. */
extern struct cppblk_t *__hdr_cppblks; /* blocks used for cell pin recs*/
extern int32 __cppblk_nxti;   /* index of next free pos. */
extern struct tnblk_t *__hdr_tnblks;  /* blocks of symb table tree nodes */
extern int32 __tnblk_nxti;    /* index of next free pos. */ 
extern struct cpnblk_t *__hdr_cpnblks;  /* blocks of explicit cell pnames */

/* source processing variables */
extern int32 __lin_cnt;       /* line number while reading a file */
extern int32 __saverr_cnt;    /* counter to inhibit more than a err in xpr */
extern int32 __max_errors;    /* maximum errors before stopping */
extern int32 __rding_comment; /* flag so comment non printable chars ok */
extern int32 __total_rd_lines;/* total number of lines read */

/* SV source reading and fixup variables */

/* new P1364-2005 generate processing variables */ 
extern int32 __dsgn_uses_generate; /* T => some use of generate in design */
extern int32 __in_gen_region; /* T => processing generate mod item */
extern int32 __gen_fnam_ind;  /* location of most recent generate */
extern int32 __gen_lin_cnt;   /* location of most recent generate */
extern int32 __in_gen_for;    /* T => no task/func decl in gen for */
extern int32 __mod_gen_id;    /* need unique per mod id num for each gen */
extern struct genitem_t *__last_gip;/* end of cur mod gen item list */
extern void *__save_last_mitem; /* ptr for remove mod items end of list */
extern struct genblk_t *__cur_cntxt_gblk;/* if rd src in gen blk, the cur blk */
extern struct gen_sens_t *__gen_sens_hd; /* hd of gen param sensivity list */
extern struct gen_sens_t *__gen_sens_tail; /* and tail of same list */
extern struct genitem_t *__gitems_hd; /* list of non meta gen items in mod */
extern struct genitem_t *__gitems_tail; 
extern struct genitem_t *__gref_gitems_hd; /* lst of xmr gen items (sep list) */
extern struct genitem_t *__gref_gitems_tail; 
extern struct genitem_t *__dfp_gitems_hd; /* lst of dfp gen items (sep list) */
extern struct genitem_t *__dfp_gitems_tail; 
extern char __wrk_gi_nam[RECLEN]; /* gbl wrk string for saving gen item nam */
extern int32 __fixup_round;   /* counter for fixup nl repeat for generates */ 
extern int32 __all_topm_gen_xpnd; /* T - all top modules gen expanded */
extern int32 __forblk_index; /* foreach/for(int local block index counter */

/* booleans for program options (flags) */
extern int32 __verbose;       /* T => emit various extra messages */
extern int32 __quiet_msgs;    /* T => do not emit msgs just errors */
extern int32 __no_warns;      /* T => don't print warning msgs */
extern int32 __no_errs;       /* T => don't print error msgs */
extern int32 __no_informs;    /* T => don't print inform msgs (dflt) */
extern int32 __debug_flg;     /* T => turn on debugging output */
extern int32 __opt_debug_flg; /* T => turn on vm compiler debugging output */
extern int32 __missing_nchg_trace; /* undocumented tracing of late nchg add */
extern int32 __opt_prt_stats; /* T => print cvc bblk and m insn stats */
extern int32 __st_tracing;    /* T => trace statement execution */
extern int32 __ev_tracing;    /* T => trace event schedules and processes */
extern int32 __pth_tracing;   /* T => trace path delays in detail */
extern int32 __dump_arrays;   /* T => dump array values (vcd,fst,fsdb) */
extern int32 __dump_array_cells; /* T => dump array values per element */
extern int32 __verbose_mem;     /* T => verbose memory cvc usage */ 
extern int32 __opt_block_trace; /* T => block tracing for compiler */
extern int32 __opt_valtrk;      /* T => turn on value tracking optimizing */
extern int32 __opt_trk_verbose; /* T => value tracking verbose msgs printed */
extern int32 __opt_emit_var_names;/* T => for debug, emit var name if short */
extern int32 __use_pwd_as_tmp;   /* T => use pwd as the work space directory */ 
extern char * __usedir_cp;        /* use named dir as the work space dir */ 
extern int32 __real_warns;            /* turn on sim time NaN real warns */
extern int32 __prt_stats;     /* T => print design statics tables */
extern int32 __prt_allstats;  /* T => print design and mod content tabs */
extern int32 __show_cancel_e; /* T => chg val to x on pulse cancelled event */
extern int32 __showe_onevent; /* T => if showing cancel e, drive x on event */
extern int32 __warn_cancel_e; /* T => emit warn cancel_e (indep. of cancel) */
extern int32 __mipd_cycle_pnd0_schd; /* T => MIPD del chg on nchg - pnd0 sched */
extern int32 __rm_gate_pnd0s; /* T => remove #0 from all gates */
extern int32 __rm_path_pnd0s; /* T => (default) remove all 0 delay paths */
extern int32 __dmpvars_all;   /* T => dumpvars all variables */
extern int32 __has_dmpv_sys_calls; /* T => design as dumpvar sys calls */

/* dumpport globals */
extern int32 __has_dumpports_sys_calls; /* T => design as dumpport sys calls */
extern word64 __dp_calltime;  /* time dump ports first (and only) called */
extern int32 __dp_seen;       /* glb flag to insure dp all at same tick */
extern struct dp_fildesc_t *__dp_fildesc_tab; /* table of dumpports open files */
extern int32 __dp_fildesc_nxti; /* next free open file slot */

extern int32 __is_fst;   /* T => is FST dumping on */
extern int32 __fst_repack; /* T => do FST repacking on close */
extern int32 __fst_parallel; /* T => do FST using multiple threads */
extern int32 __fst_parallel2; /* T => do FST multiple threads with buffering */
extern void *__fst_ctx;  /* FST format handle */
extern int32 __fst_max_work_area; /* max number of bytes for work area */
extern byte *__fst_work_area; /* work area to do the conversions */
extern int32 __fst_convert_dump2fst; /* T => convert $dump calls to $fst */
extern byte *__fst_work_svec; /* work area to do stren conversions */
extern int32 __fst_next_idcode; /* count the number of nets dumping */

/* command option booleans */
extern int32 __lib_verbose;   /* T => emit src.file/lib source messages */
extern int32 __sdf_verbose;   /* T => emit msgs for SDF annotated delays */
extern int32 __tgl_verbose;   /* T => emit tgldat non match warning msgs */
extern int32 __ignore_sdf_iopath_edges; /* T => ignore io path edges match MS */
extern int32 __switch_verbose;/* T => emit msgs for switch/tran chan build */
extern int32 __no_vec_bid_tran_channels; /* T=>leave bid switch chans scalar */ 
extern int32 __chg_portdir;   /* T => chg port dir to bid. for XL compat */
extern int32 __sched_always_blocks_first; /* T init all alw before init */
extern int32 __decompile;     /* T => decompile and print Verilog source */
extern int32 __repl_gen_dot_uline;/* T => decompile with gen dots as '_' */ 
extern int32 __repl_gen_dot_esc;/* T => decompile with gen dots escaped */ 
extern int32 __compile_only;  /* T => check syntax (inc. lib.) no quads */
extern int32 __parse_only;    /* T => first pass parse only to chk sep mod */
extern int32 __dflt_ntyp;     /* Verilog wire type for normal nets */
extern int32 __dflt_ntyp_is_none;  /* '`defaul_nettype none' - no implicit */
extern int32 __mintypmax_sel; /* for (e:e:e) expressions value to use */
extern int32 __sdf_mintypmax_sel; /* min:nom_max over-ride for $sdf_annotate */
extern int32 __gateeater_on;  /* T => attempt to remove (disconnect) gates */ 
extern int32 __no_expand;     /* T => make all wire vectors vectored */
extern int32 __in_cell_region;/* T => turn on cell bit for every module */
extern int32 __unconn_drive;  /* if none TOK_NONE else PULL 0 or PULL 1 */
extern int32 __no_specify;    /* T => check but no simulate with specify */
extern int32 __no_tchks;      /* T => check but no simulate with tim chks */
extern int32 __lib_are_cells; /* T => if in lib, the mark as cell (dflt.) */
extern int32 __design_has_cells;/* T => cells somewhere in design */
extern int32 __accelerate;    /* T => use short circuits g/prt code if can */
extern int32 __pli_keep_src;  /* T => keep more source stmt info for pli */
extern int32 __use_impthdels; /* T => use src-dst im path dels */
extern int32 __old_vpi_obj_after_iter_free_only; /* old vpi in iter free */

/* source input variables and temps */
extern char __lasttoken[IDLEN];/* current last pushed back symbol name */
extern char __token[IDLEN];   /* current symbol (in canonical (lc) form) */
extern int32 __toktyp;        /* place for current toktyp value */
extern int32 __lasttoktyp;    /* push back token type (= UNDEF if none) */
extern int32 __last_attr_prefix;/* push back pending attr prefix state */
extern int32 __itoklen;       /* current number token bit length */
extern int32 __itoksized;     /* T => token is sized */
extern int32 __itokbase;      /* base constant for number token */
extern int32 __itoksizdflt;   /* '[base] form with width (uses dflt.) */
extern int32 __itok_signed;   /* T => token is signed number */
extern int32 __itok_sv_unbas_unsiz;   /* T => token is SV '0 number */
extern double __itok_realval; /* actual scannoer double val */
extern char *__strtoken;      /* growable token to hold string */
extern int32 __strtok_wid;    /* current size of string token */    
extern char *__numtoken;      /* growable token to hold numbers */
extern int32 __numtok_wid;    /* current size of number token */    
extern int32 __letendnum_state; /* T => letter can end unsized num. */
extern int32 __macro_sep_width; /* T => possible beginning of macro 2 tok num */
extern int32 __maybe_2tok_sized_num; /* T => seeing number after macro num */
extern int32 __macro_sav_nwid;/* value of saved first tok width */
extern int32 __first_linetok; /* T => token first on line */
extern int32 __file_just_op;  /* T => new file and no token yet returned */
extern int32 __first_num_eol; /* T => first tok because number ended line */
extern char *__macwrkstr;     /* work string for macros */ 
extern int32 __mac_line_len;  /* actual length of macro line in wrk str */   
extern int32 __macwrklen;     /* allocated len of mac. work string */
extern struct macarg_t *__macarg_hdr; /* hdr of list of format mac. args */
extern int32 __macbs_flag;    /* T=> 8'h`DEFINE catch multiple bases errors */
extern char *__attrwrkstr;    /* work string for attributes */
extern int32 __attr_line_len; /* actual length of attribute string */ 
extern int32 __attrwrklen;    /* alloced len of attr work string - grows */
extern char *__attrparsestr;  /* string to parse attr out of */
extern int32 __attrparsestrlen; /* string to parse attr out of */
extern int32 __attr_prefix;   /* T => token has attribute prefix */
extern int32 __attr_fnam_ind; /* location of attr inst. */
extern int32 __attr_lin_cnt;  /* location of attr inst. */
extern struct attr_t __wrk_attr; /* latest read attribute */
extern char *__xs, *__xs2;    /* places to put expr to str trunc messages */
extern int32 __pv_ctv;        /* tmp for white space skipping macros */
extern int32 __syncto_class;  /* token class sync skipping halted at */
extern char *__exprline;      /* expr. output line work string */
extern int32 __exprlinelen;   /* expr. line length */
extern int32 __cur_sofs;      /* ndx of next ofs (position) in expr line */
extern word32 *__acwrk;       /* a value work string for scanning number */
extern word32 *__bcwrk;       /* b value work string for scanning number */
extern word32 __addrtmp[2];   /* up to 32 bit temp with addr. */
extern word32 *__addr_2state_zero; /* 2-state empty bpart */
extern int32  __max_net_blen; /* maximum declared net size */
extern int32 __abwrkwlen;     /* current acwrk a half length in words */
extern char __portnam[IDLEN];
extern char __pv_varnam[IDLEN]; /* variable name */
extern int32 __expr_is_lval;  /* T => parsing proc. assign lhs */
extern int32 __allow_scope_var; /* T => process systask arg can be scope */
extern int32 __allow_scope_lsb; /* T => process systask arg be XMR lsb */
extern int32 __rd_auto_task;    /* T => is reading automatic task */
extern int32 __rd_loop;         /* T => is reading a loop */
extern int32 __rd_continue;     /* T => read 'continue' */
extern int32 __rd_break;        /* T => read 'break' */
extern int32 __rd_always_ff;    /* T => read always_ff */
extern struct st_t *__st_loop_continue; /* prep loop continue statement */
extern struct st_t *__st_loop_break;    /* prep loop break statement */

/* toggle processing work variables */
extern char *__tglbits01;       /* for init from .tgldat file 01 list */
extern char *__tglbits10;       /* 10 list */
extern int32 __siz_tgl_lst;     /* current alloc size of list */
extern char *__tgl_modnam;      /* name of module for tgl net line */
extern char *__tgl_rtpthnam;    /* for init from .tgldat line rooted path */ 
extern int32 __siz_tgl_rtpthnam;/* and alloc size */
extern int32 *__tgl01tab;       /* int (0/1 for now) tab of 0->1 toggle cnt */
extern int32 *__tgl10tab;       /* and 1->0 tab */ 
extern int32 __siz_tgltabs;     /* alloc size of tgl cnt tabs */
extern int32 __tgl_r1;          /* first tgldat line range */
extern int32 __tgl_r2;          /* 2nd tgldat line range */
extern int32 __se_reset_to_untgled; /* T => slot end set recorded nets untgl */

#ifdef __XPROP__
extern int32 __xprop_copying;   /* T => copying x propagation stmt block */
extern struct net_t **__xprop_lhs_nets; /* lhs net prep building */
extern int32 *__xprop_lhs_other_than_id;  /* lhs net id only */
extern struct st_t **__xprop_stmts;        /* lhs stmt prep building */
extern int32 __xprop_net_ndx;              /* lhs net ndx */
extern struct net_t **__xprop_lhs_nets_top; /* top lhs net prep building */
extern int32 *__xprop_lhs_other_than_id_top;      /* top lhs net id only */
extern struct st_t **__xprop_stmts_top;     /* top lhs stmt prep building */
extern int32 __xprop_net_ndx_top;         /* top lhs net ndx */
extern struct xprop_t *__current_xprop;   /* last xprop struct */
extern word32 *__xprop_max_net_1_wp;        /* max width 1 wp */
extern int32 __xprop_max_net_width;         /* max xprop net width */
extern struct st_list_t *__added_xprop_stlst_hdr; /* alloc xprop stmt hdr */
extern struct st_list_t *__added_xprop_stlst_tail; /* alloc xprop stmt tail */
extern int32 __xprop_xedge;             /* T => xedge global */
extern int32 __xprop_expr_has_cneq; /* expr mark has === or !=== */
extern FILE *__xprop_trace_fp;          /* xprop trace info file */
extern int32 __xprop_trace_on;          /* xprop tracing on */
extern int32 __xprop_xtrace_suppress;   /* T => do not emit trace message */
extern FILE *__xprop_not_eligible_fp;   /* xprop not eligible stmt file */
extern int32 __xprop_not_eligible;      /* xprop not eligible stmts on */
extern int32 __xprop_cond_hit;          /* x conditions hit */
extern int32 __xprop_cond_max;          /* max hit before stopping log */
#endif

/* vars needed for pushing back numbers (see var. comment) */
extern int32 __lastitokbase;
extern int32 __lastitoksized;
extern int32 __lastitoksizdflt;
extern int32 __lastitok_signed;
extern int32 __lastitok_sv_unbas_unsiz;  
extern int32 __lastitoklen;
extern word32 *__lastacwrk;   /* special malloced push back num value */
extern word32 *__lastbcwrk; 
extern double __lastitok_realval;

/* the module and module subtask specific work variables */
extern struct mod_t *__oinst_mod;/* ptr. to old current module for copying */
extern struct mod_t *__end_mdp; /* end of module def. list */
extern struct cell_t *__end_cp; /* end of module inst. list */
extern int32 __cp_num;          /* counter for unnamed gate/inst pos. */ 
extern struct conta_t *__end_ca; /* end of module conta list */
extern int32 __conta_num;     /* counter for building symbol for conta */
extern struct varinitlst_t *__end_mod_varinitlst; /* end of mod var inits */
extern struct symtab_t *__tfcall_wrksytp;/* wrk tf tab for undecl xmr uprel */  

extern struct dfparam_t *__end_dfp;/* module current end of defparam list */
extern struct task_pin_t *__end_tpp; /* end of task port list */
extern struct task_t *__end_tbp;/* end of top level task/functions/blocks */
extern struct task_t *__cur_tsk;/* ptr. to current task */
extern struct net_t *__end_loc_paramnp; /* end of ordered parm loc decl. list */
extern struct net_t *__end_paramnp; /* end of ordered parm decl. list */
extern struct net_t *__end_impparamnp; /* end of ordered imprt parm decl lst */
extern struct net_t *__end_glbparamnp; /* end of ordered glb parm decl. lst */
extern struct net_t *__end_tskparamnp; /* end of task param decl. list */
extern struct net_t *__end_tsk_loc_paramnp; /* end of task param decl. list */
extern struct ialst_t *__end_ialst; /* end of module initial/always list */
extern struct gref_t *__grwrktab;  /* work table for building mod glbs */
extern int32 __grwrktabsiz;        /* its size */
extern int32 __grwrknum;      /* current number of glbs in work table */ 
extern struct gref_t *__dfp_grwrktab;  /* wrk tab for building mod dfp glbs */
extern int32 __dfp_grwrktabsiz;        /* its size */
extern int32 __dfp_grwrknum;           /* current num of glbs in table */ 

extern int32 __cur_declobj;   /* token type of declared mod or task */
extern int32 __pv_stlevel;    /* tmp. for current stmt nesting level */
extern int32 __design_no_strens;/* T => no strengths used in design */
extern int32 __strenprop_chg; /* during propagate pass at least one chged */
extern int32 __splitting;     /* T => in process of splitting module */
extern int32 __confunc_copying; /* T => expr copy is conf func copy */
extern int32 __genblk_copying; /* T => expr copy is gen blk copy */
extern int32 __gentsk_copying; /* T => copying gen tsk, complex special case */
extern int32 __processing_pnd0s;/* T => in time unit, in end #0 region */
extern struct dce_expr_t *__cur_dce_expr; /* glb for edge events eval expr */
extern int32 __lofp_port_decls; /* T => exclusive hdr port decls appeared */ 
extern struct exprlst_t *__impl_evlst_hd; /* hdr of impl @(*) ev expr list */
extern struct exprlst_t *__impl_evlst_tail; /* and its tail */
extern int32 __canbe_impl_evctrl; /* glb switch to allow @(*) as ev ctrl */

/* variables for dumpvars */
extern int32 __dv_seen;       /* dumpvars seen but not yet setup */
extern int32 __dv_state;      /* processing state of dumpvars */
extern word64 __dv_calltime;  /* time dump var. first (and only) called */
extern int32 __dv_dumplimit_size; /* user set limit of dv file size (0 none) */
extern int32 __dv_file_size;  /* current size of dumpvars file */
extern int32 __dv_time_emitted; /* flag to stop repeated same #[time] */
extern char *__dv_fnam;       /* name of dumpvars output file */
extern int32 __dv_func;       /* global set with type of dumpvar dumping */
extern struct mdvmast_t *__dv_hdr; /* hdr of mast dumpvar rec. list */
extern struct mdvmast_t *__dv_end; /* end of dumpvar rec. list */
extern int32 __dv_fd;         /* file number of dmpvars fd */
extern char *__dv_buffer;     /* buffer to speed up dumpvars output */
extern int32 __dv_nxti;       /* next free location */
extern int32 __dv_outlinpos;  /* line postion in dump vars file */ 
extern int32 __next_dvnum;    /* highest so far used dumpvars number */
extern struct dvchgnets_t *__dv_chgnethdr;  /* curr. time var chg list hdr */
extern int32 __dv_isall_form; /* T doing all of design dumpvar setup */
extern int32 __dv_allform_insrc;/* T dumpvars all form in source */
/* AIV 04/19/12 - variables for parallel dumping */
extern pthread_mutex_t __dump_mutex;    /* dump mutex */
extern pthread_cond_t __buffer_empty;   /* buffer is empty */
extern pthread_attr_t __thread_attr; /* thread attributes */
extern pthread_t __dump_thread;      /* dumping thread */
extern struct dmp_buf_t *__dump_buffer; /* dump buffer */
extern int32 __dump_buffer_size;        /* size of dump buffer */
extern int32 __write_ndx;               /* current write of dump buffer */
extern int32 __dump_next_ndx;           /* next index */

extern struct rt_tgl_t *__toggle_chghdr;  /* rt toggle change header list */
extern int32 __tgl_record_on;             /* tgl record (add to lst) now on */
extern char *__toggle_coverage_file_name; /* name of coverage file */
extern int32 __toggle_coverage;           /* T => turn on tgl cover record */

/* old style toggle coverage variables */
extern int32 __old_toggle_rpt_instance;   /* T => old report per instance */
extern int32 __old_toggle_rpt_bits;       /* T => old style report per bit */
extern int32 __old_toggle_rpt_uncovered;  /* T => old style rpt uncoverd bits */
extern int32 __old_toggle_rpt_covered;    /* T => old style rpt covered bits */

extern int32 __wr_tgldat_on;              /* at end, write .tgldat file */
extern char *__wr_tgldat_file;            /* name of .tgldat output file */
extern struct tgldat_in_lst_t *__tgldat_infils_lst_hd; /* init tgldat hd */
extern struct tgldat_in_lst_t *__tgldat_infils_lst_end; /* and tail */
extern char __tgldat_writer_vers[RECLEN]; /* id info from input .tgldat file */
extern char __tgldat_writer_date[RECLEN]; /* id info from input .tgldat file */

/* new concise style toggle coverage variables - if used ignore old style */
extern int32 __drvn_const_as_tgled;       /* T => driven const made tgled */
extern int32 __drvn_const_rpt_concise;    /* T => output rpt drvn const bits */
extern int32 __untgled_rpt_concise;       /* T => concise untgl rpt only */
extern int32 __has_tgl_optcfg_stmt;       /* T => optconfigfil tgl stmts used */

extern char *__event_coverage_file_name; /* name event coverage file */
extern word32 *__event_covered;          /* marked events array */
extern int32 __event_coverage;           /* T => report event coverage */

extern char *__stmt_coverage_file_name; /* name event coverage file */
extern word32 *__stmt_covered;          /* marked stmts array */
extern int32 __stmt_coverage;           /* T => report stmt coverage */
extern int32 __stmt_coverage_tasks;     /* T => report tasks stmt coverage */
extern FILE *__force_dmp_fp;            /* when set for dmp_stmt to file */

/* time scale - precision variables */
extern word32 __cur_units;    /* current units (0 (1s) - 15 (1ft) */ 
extern word32 __cur_prec;     /* current digits of precision (0-15) */
extern word32 __des_timeprec; /* assume -, 0-15 design sim. tick prec. */
extern word32 __tfmt_units;   /* %t output units (also interact. units) */
extern word32 __tfmt_precunits;/* %t number of prec. digits */
extern int32 __des_has_timescales;/* T => design has at least one timescale */
extern char *__tfmt_suf;      /* suffix for %t */
extern int32 __tfmt_minfwid;  /* minimum field width for %t */
extern word64 __itoticks_tab[16];/* table of scales amount from prec. */
extern char __timstr_unitsuf[4];/* to_timstr units suffix if needed */
extern word64 __timstr_mult;  /* multiplier if needed */
extern int32  __nd_timstr_suf;/* T => need to_timstr units */

/* veriusertfs pli user function and task work variables */ 
/* SJM 07/16/02 - need internal veriuser tfs for new +loadpli1 option */
extern struct t_tfcell *__shadow_veriusertfs; /* internal copy of table */
extern int32 __last_veriusertf; /* last user veriusertfs tf number */
extern struct tfinst_t *__tfinst;/* current tf_ inst loc. */
extern struct tfrec_t *__tfrec;/* current tf_ record */ 
extern struct dceauxlst_t *__pvc_dcehdr; /* header of current pvc dces */
extern struct tfrec_t *__tfrec_hdr; /* header of design wide tfrec list */ 
extern struct tfrec_t *__tfrec_end; /* last el of design wide tfrec list */ 
extern struct tev_t *__tehdr_rosyncp; /* hdr ndx of slot end ro sync ev lst */ 
extern struct tev_t *__teend_rosyncp; /* end of slot end ro sync ev lst */ 
extern int32 __now_resetting; /* reset in progress - for cbs and misctf */  
extern int32 __rosync_slot;   /* T => processing tf or vpi  ro synch events */
extern struct loadpli_t *__pli1_dynlib_hd; /* hd of ld pli1 dynamic lb list */
extern struct loadpli_t *__pli1_dynlib_end; /* and its end */

/* vpi_ work variables */
extern int32 __last_systf;    /* last vpi_ registered sytfs number */
extern int32 __num_vpi_force_cbs; /* number of registered vpi force cbs */
extern int32 __vpi_force_cb_always; /* T => always call back on force */
extern int32 __num_vpi_rel_cbs; /* number of registered vpi rel cbs */
extern int32 __vpi_rel_cb_always; /* T => always call back on release */
extern int32 __allforce_cbs_off; /* T => can't reenter any of all force cbs */
extern int32 __allrel_cbs_off;/* T => can't reenter any of all release cbs */
extern char *__wrks1;         /* work string - can not use xs if func */
extern char *__wrks2;
extern char __wrk_vpiemsg[IDLEN];/* error msg. work string */
extern char __wrk_vpiget_str[IDLEN];/* standard required vpi get str string */
extern char __wrk_vpi_product[256];/* product version */
extern char __wrk_vpi_errcode[256];/* error codes are Cver err num as str */
extern double __wrk_vpi_timedbl;/* time double for vpi error rec */
extern char *__wrkvalbufp;    /* buf for vpi get value value_p contents */ 
extern int32 __wrkval_buflen; /* and current length */
extern int32 __vpi_vlog_start_done;/* T => startup done, no systf registering */
extern struct systftab_t *__systftab; /* table of vpi_ systf records */
extern int32 __size_systftab; /* current size of systf data rec. table */
extern struct xstk_t *__cur_sysf_xsp; /* tmp stk_t for vpi sysf ret val */
extern struct expr_t *__cur_sysf_expr;/* tmp calling expr. for vpi sysf*/
extern struct st_t *__cur_syst_stp; /* tmp stmt for vpi syst*/
extern struct dceauxlst_t *__cbvc_dcehdr; /* header of current vc cb dces */
extern struct rfcblst_t *__rel_allcb_hdr;
extern struct rfcblst_t *__rel_allcb_end;
extern struct rfcblst_t *__force_allcb_hdr;
extern struct rfcblst_t *__force_allcb_end;
extern struct tev_t **__vpicb_tehdri; /* hdr of fixed cb tev list-1 per class */
extern struct tev_t **__vpicb_teendi; /* end of fixed cb tev list-1 per class */
extern int32 __have_vpi_actions;/* some use of __vpi actions */
extern int32 __have_vpi_gateout_cbs;/* some use of gate out term cbs */
extern struct h_t *__vpi_hfree_hdr;  /* handle free list hdr */ 
extern struct hrec_t *__vpi_hrecfree_hdr;  /* handle record free list hdr */ 
extern struct cbrec_t *__vpi_cbrec_hdr; /* all cbs list header */
extern int32 __ithtsiz;       /* size of global work ld/drv handle table */
extern struct h_t **__ithptab; /* and the work ld/drv handle ptr table */
extern int32 __ithtsiz2;      /* size of global work ld/drv handle table */
extern struct h_t **__ithptab2; /* 2nd work for ptrs to in subtree handles */
extern struct vpisystf_t *__vpi_sysf_hdr; /* hdr sys func call src locs */
extern struct vpisystf_t *__vpi_syst_hdr; /* hdr sys task enable src locs */
extern int32 __in_vpi_errorcb;/* T => if sim ctrl, suppress error msg error */
extern int32 __vpierr_cb_active; /* T => at least one cbError reged */
extern int32 __acc_vpi_erroff;/* acc_ flag to stop internal acc_ error cbs */
extern int32 __errorcb_suppress_msg; /* T => sim control suppress error msg */
extern struct h_t *__cur_vpi_inst;
extern struct hrec_t *__cur_vpi_obj;
extern struct loadpli_t *__vpi_dynlib_hd; /* hd of ld vpi dynamic lib list */
extern struct loadpli_t *__vpi_dynlib_end; /* and its end */
extern struct dcevnt_t *__cbvc_causing_dcep; /* glb for vc cb if it is remed */

/* specify work variables */
extern struct spfy_t *__cur_spfy;/* current specify block */
extern struct spcpth_t *__end_spcpths; /* end of specify path st. list */
extern int32 __path_num;      /* counter for unnamed paths */
extern struct tchk_t *__end_tchks;/* end of specify time check st. list */
extern struct net_t *__end_msprms;/* end of specify specparam net list */
extern struct tchk_t *__cur_tchk;
extern int32 __tchk_num;      /* counter for unnamed paths */
extern struct symtab_t *__sav_spsytp;/* save loc. of sym tab in spfy sect. */

/* work compile global variables accessed by routines */
extern int32 __v1stren;       /* wire/inst. Ver. 1 strength */
extern int32 __v0stren;       /* wire/inst. Ver. 0 strength */
extern word32 __pr_iodir;     /* glb. for port ref. expr. I/O direction */
extern int32 __pr_wid;        /* global for total port ref. expr. width */
extern int32 __mpref_explicit;/* T => mod def header port ref explicit */
extern int32 __sym_is_new;    /* set when new symbol added */
extern struct sy_t **__wrkstab;/* malloced work symbol table area */
extern int32 __last_sy;       /* last symbol in work area */
extern struct sy_t **__wrkstab2;/* malloced 2nd work symbol table area */
extern int32 __last_sy2;      /* last symbol in work area */
extern int32 __mod_specparams;/* number of declared specparams in mod */
extern int32 __name_assigned_to;/* glb set if func. def. name assigned to */
extern struct sy_t *__locfnamsyp; /* place for func. def. chk func. symbol */
extern int32 __processing_func; /* T => prep or exec of function occuring */
extern struct st_t **__nbstk; /* func. nest nblock stack (nxt for exec) */
extern int32 __nbsti;      
extern struct sy_t *__ca1bit_syp; /* gmsym for 1 bit conta converted gate */
extern int32 __chking_conta;  /* T => checking a continuous assignment */
extern int32 __rhs_isgetpat;  /* T => flag for checking stylized getpat */
extern int32 __lhs_changed;   /* T => assignment changed lhs */
extern word32 __badind_a;     /* place for a part of in error index value */
extern word32 __badind_b;     /* and for b part */
extern int32 __badind_wid;    /* width for bad ind (<32 expr can eval to x) */
extern int32 __expr_has_real; /* T => know some real in expr. */
extern int32 __expr_has_sv_string; /* T => know some SV string in expr. */
extern int32 __isform_bi_xvi; /* glbl for IS net pin bit index in contab */
extern int32 __lhsxpr_has_ndel; /* T => component wire of lhs has wire del */
extern int32 __checking_only; /* T => no error msg, looking for something */ 
extern int32 __task_has_tskcall;/* T => task calls other task (not name blk) */
extern int32 __task_has_xmrcall;/* T => task has no reachable xmr task */
extern int32 __task_has_disable;/* T => task call has disable needs thread */
extern int32 __task_has_delay;/* T => task call has del. needs thread */
extern int32 __disp_uses_scope;/* T => $display fam of functions uses %m */
extern int32 __ia_has_vpicall;/* init/alwasy has a vpi call - needs thread */
extern int32 __func_has_fcall;/* T => func contains has non sys fcall */
extern int32 __iact_must_sched; /* T => iact stmt(s) have $stop or loop */
extern int32 __expr_rhs_decl; /* T current expr. is decl. not proc. rhs */ 
extern int32 __chg_rng_direct;/* T => change rng dir. for implicitly decl */
extern int32 __has_top_mtm;   /* T => for parameter rhs non () m:t:m */
extern int32 __nd_0width_catel_remove; /* fx3 file 0 width concat glb */
extern struct gref_t * __wire_array_grp; /* gref use to convert wire arrays */

/* current Verilog module/task/block symbol environment */
extern struct symtab_t **__venviron;
extern int32 __top_sti;
extern struct symtab_t *__modsyms;/* separate symbol table for type names */
extern struct symtab_t *__pv_defsyms;/* global table for `defines */
extern struct symtab_t *__syssyms;/* global tab for system tasks and funcs */
extern struct sy_t **__glbsycmps; /* work global name symbols */
extern struct expr_t **__glbxcmps;/* work glbal exprs */
extern int32 __last_gsc;

/* n.l. access headers and tables */
extern struct mod_t *__modhdr;/* header of top level module list */
extern struct udp_t *__udphead; /* header udps */
extern struct udp_t *__udp_last;/* end udp list */
extern struct inst_t **__top_itab; /* tab of virt inst ptrs of top mods */
extern int32 *__top_ipind;    /* binary searchable top insts index */
extern int32 __numtopm;       /* number of uninstanciated top modules */

extern struct mod_t **__dsgn_mod_ndx; /* dsgn per mod ndx number index array */
extern int32 __dsgn_num_mods; /* num of module in modhdr list for ndxing */
extern struct udp_t **__dsgn_udp_ndx; /* dsgn all udp tab index array */
extern int32 __dsgn_num_udps; /* num of upds in udp list */ 

extern struct itree_t **__it_roots; /* table of root itree entries */
extern int32 __ualtrepipnum;  /* udp rep. change threshold */
extern struct thread_t *__initalw_thrd_hdr; /* list hd of per inst in/al thds */
extern struct tev_t *__tevtab;/* reallocable tab of events and free evs */
extern int32 __numused_tevtab;/* num used at least once in tev tab */
extern int32 __size_tevtab;   /* num tev's allocated in tev tab */ 
extern word32 *__contab;      /* design wide constant table */
extern int32 __contabwsiz;    /* currrent size of const tab in words */
extern int32 __contabwi;      /* next free word32 slot in const tab */
extern int32 __opempty_contabi; /* special contab ndx for opempty expr leaf */
extern struct contab_info_t **__contab_hash; /* contab hash information */

/* n.l. access routines */  
extern struct dfparam_t *__dfphdr; /* design wide defparam list header */
extern int32 __num_dfps;      /* number of defparams in source */
extern int32 __num_glbdfps;   /* number of defparams in design */
extern int32 __num_locdfps;   /* number of local defparams */
extern int32 __num_inst_pndparams;/* static number of inst. pound params */
extern int32 __design_gia_pndparams;/* T => at least one gia range pnd params */
extern int32 __design_gi_arrays;  /* T => design has arrays of g/i */ 
extern int32 __pndparam_splits; /* T => at least one split from pound params */
extern int32 __defparam_splits; /* T => at least one split from def params */
extern int32 __dagmaxdist;    /* max. nested mod. inst. level */
extern struct mod_t **__mdlevhdr; /* array of ptrs to ith lev linked mods */ 
extern struct cell_pin_t *__cphdr;   /* header of temp. cell pin list */
extern struct cell_pin_t *__cpp_last;/* current last cell pin*/
extern struct tnode_t *__tmp_head;

extern struct xldlnpp_t *__xldl_hdr; /* other side unproc. xl drv/ld npps */
extern struct xldlnpp_t *__last_xldl;/* end of list - place to add after */
extern struct xldlvtx_t **__xldlvtxind; /* table of xl drv/ld net/bit vtx */
extern int32 __num_xldlvtxs;  /* number of lements in table */
extern int32 __siz_xldlvtxtab;/* current size of table */

/* udp table building variables */
extern struct wcard_t *__wcardtab; /* level wildcard table */
extern int32 __last_wci;      /* last wild card index for line */
extern word32 *__cur_utab;    /* current udp table */
extern struct utline_t *__cur_utlp; /* current line info struct */
extern word32 __cur_uoval;    /* current udp line output value */
extern int32 __cur_unochange; /* T => cur line has '-' no change output */
extern struct udp_t *__cur_udp; /* current udp struct */
extern word32 __cur_upstate;  /* current last input (state) for wide */
extern int32 __cur_ueipnum;   /* cur. input pos. num of edge (NO_VAL none) */
extern int32 __cur_utabsel;   /* current edge 1st char - 2nd in state line */

/* expression and function processing variables */
extern int32 __xndi;          /* next place in collected expression list */
extern struct expr_t **__exprtab;/* table to collect expressions into */
extern struct expridtab_t **__expr_idtab; /* expr parse id name info */ 
extern int32 __exprtabsiz;    /* current operator precedence expr tab siz */
extern int32 __last_xtk;
extern struct expr_t *__root_ndp;/* root of built and alloced expression */
extern struct xstk_t **__xstk;/* expr work vals */
extern int32 __xspi;          /* expr. pointer */
extern int32 __maxxnest;      /* current size of expr. stack - must grow */ 
extern int32 __maxfcnest;     /* size of func. call task stk - must grow */
extern struct task_t **__fcstk; /* function call nesting stack */
extern int32 __fcspi;           /* fcall tos index */
extern int32 __lhs_has_4state;  /* T=> lhs has 4-state values */ 
extern int32 __rhs_has_4state;  /* T=> rhs has 4-state values */ 
extern int32 __rding_defparam;  /* T=> parsing dfp stmt - for dfp gref tab */

/* -y and -v library variables */
extern struct vylib_t *__vyhdr; /* header of lib. file list */
extern struct vylib_t *__end_vy;/* last entry on vy lib. list */
extern int32 __num_ylibs;     /* number of ylibs in options */
extern int32 __num_vlibs;     /* number of vlibs in options */

extern struct undef_t *__undefhd;/* head of undefined mod/udp list */   
extern struct undef_t *__undeftail; /* tail of undefined mod/udp list */
extern int32 __undef_mods;    /* count of undefined modules */

extern int32 __lib_rescan;    /* T => rescan from start after each */
extern int32 __cur_passres;   /* num mods resolved in current pass */
extern int32 __rescanning_lib;/* T => for `language exclude after 1st pass */ 
extern int32 __num_ys;        /* number of -y options in lib. */
extern char **__lbexts;       /* tab of -y library extension suffixes */
extern int32 __last_lbx;
extern char **__incdirs;      /* tab of +incdir paths (always / end) */
extern int32 __last_incdir;
extern int32 __leaf_modules_already_merged; /* leaf modules already merged */

/* simulation preparation variables */
extern int32 __cur_npii;      /* current index of inst. in cur. mod */
extern struct gate_t *__cur_npgp;/* current net-pin processing gate */
extern struct mod_t *__cur_npmdp;/* current net-pin processing module */
extern struct conta_t *__cur_npcap; /* current net pin proc. conta */
extern struct tfrec_t *__cur_nptfrp; /* current net pin tf arg drvr rec */
extern struct net_t *__cur_npnp; /* current net pin net for vpi putv driver */
extern int32 __cur_npnum;     /* current port number (from 0) */
extern int32 __cur_pbi;       /* current bit number for PB ICONN npp */
extern int32 num_optim_cats;  /* number of optimized concats */
extern int32 num_optim_catels;/* number of all elements in optim concats */
extern int32 __cur_lhscati1;  /* if lhs concat, high rhs psel index */
extern int32 __cur_lhscati2;  /* if lhs concat, low rhs psel index */
extern struct st_t **__prpstk;/* during prep., continue stp */
extern int32 __prpsti;        /* top of nested stmt. stack */
extern int32 __nd_parmpnp_free; /* T => after 1st parmnpp need copy not orig */
extern int32 __num_rem_gate_pnd0s; /* number of removed source #0 gates */
extern int32 __num_flat_rem_gate_pnd0s; /* and flat number */
extern int32 __num_rem_mipds; /* number of per bit flat MIPDs 0 delays rmed */
extern int32 __last_modsti;   /* and counter for statements */
extern int32 __compiled_sim;  /* generate asm, compile and dl link */
#ifndef __CVC32__
extern int32 __cvc_use_large_model;   /* large model needs to be used */
#endif
extern struct st_t **__prp_mstmt_ndx;/* during prep tmp stmt tab for idp add */
extern int32 __last_mstndx;   /* last used prep tmp stmt tab index */
extern int32 __size_prp_mstmts;/* alloc size of tmp prp mstmt tab */
extern int32 __dump_flowg;    /* dump flow graph for debugging */
extern int32 __optimize_level;/* for cvc, optimize leve (now only 2?) */
extern char  *__exe_name;   /* name of already compiled .so library */
extern int32  __show_asm;     /* show assmebly files */     
extern int32 __use_interp_dpi_mk; /* T => for dbg, interp dpi use mk file */
extern char  *__objdir_path;  /* path to object dir to get compiled .so */
extern int32 __asm_emit_loc;  /* val controls asm out printed location info */
extern int32 __pli_access_level;    /* hold pli access value */
extern int32 __inline_code;   /* inline generated code */
extern int32 __opt_reg_alloc; /* optimize reg allocation */
extern int32 __opt_two_state; /* use two state optimization */
extern int32 __opt_two_state_no_wires; /* 2-state does not include wires */
extern int32 __my_popen;      /* use special faster piping */
#ifdef __XPROP__
extern int32 __xprop;           /* T => x propagation  */
extern int32 __xprop2;          /* T => x2 propagation  */
extern int32 __xprop_and_or_xs; /* T => preserve xs for |,&, ||, &&  */
extern int32 __no_xprop_edges;  /* T => do not include always @ edges */
extern int32 __no_xprop_vectors;  /* T => do not include always @veced vars */
extern int32 __xprop_pos_neg_only;  /* T => only include pos/neg edge */
extern int32 __do_xprop_xedge_vectors;/* T => need to calc xprop vectors */
#endif
extern int32 __random_init;     /* T => random initialize is on */
extern int32 __random_init_2state; /* T => random 2state initialize is on */
extern int32 __sv_parse; /* T => parse system verilog keywords */
/* SJM 02-11-13 - need to trace dl open sb lib finding */ 
extern int32 __dpi_verbose;  /* T => trace dpi -sv_lib finding checking */
extern int32 __wr_dpi_c_hdrs; /* T => write DPI c prototype hdrs to file */
extern int32 __override_change; /* T => do not check for cvcsim changes */
extern int32 __same_param_must_split;/* T => off inhibit splt same parms */
extern int32 __opt_nbaopt;    /* ignore the time delay for nb <= # */
extern int32 __opt_unroll_loops;   /* T => turn on loop unrolling */
extern int32 __cap_seq_no;    /* counter for conta enter points */
extern int32 __dctrl_seq_no;  /* counter for merged dlctrl */
extern int32 __dctrl_depth;   /* design delay ctrl depth - for marking */
extern int32 __nested_dctrl;  /* has nested delay dctrl */
extern struct npopt_t *__opt_npptab; /* global array for rm/del of npps */
extern int32 __siz_opt_npptab;/* current allocated size - just grows */
extern int32 __total_lds_removed; /* count of total lds merged away */
extern int32 __total_lds_from_nets; /* count of number of nets with lds del */
extern long __mem_cvc_use;    /* counts allocated cvc mem after argmnts read */
extern long *__dsnmemp;       /* ptr for load lib option size validation */
extern struct avlhd_t *__xpr_dup_tree; /* tree to hold all sysf calls */
extern struct avlhd_t *__xpr_isnum_tree; /* tree to hold all IS num exprs */
extern void *__process_wire_ev_enterp; /* enter pointer for wire events */
extern void *__process_compiled_thrd_ev_enterp; /* enter pointer for thrd ev */
extern void *__process_trpthdst_ev_enterp; /* enter pointer for tran ev */
extern void *__process_gatechg_ev_enterp;  /* enter process for gate ev */
extern void *__process_cancel_ev_enterp;   /* cancel event addresss ptr  */
extern void *__process_free_ev_enterp; /* done with tev list enterp */
extern void *__process_free_ev_pnd0_enterp; /* done with tev list ent pnd0 */
extern void *__process_next_ev_enterp; /* done with cur tev - get next event */
extern void *__delay_callback_enterp;  /* delay call back event */
extern void *__process_putpdel_enterp;      /* vpi putdel event */
extern void *__setdel_call_misctf_enterp;  /* set del pli event */
extern void *__sync_call_misctf_enterp;    /* sync del pli event */
extern void *__process_vpi_varputv_enterp; /* vpi putv event */
extern void *__process_vpidrv_enterp;      /* vpi drv event */
extern struct tev_t *__free_event_tevp;    /* free event index */
extern struct tev_t *__free_event_pnd0_tevp;   /* free event pnd0 index */
extern int32 __nchg_ndx; /* nchg index counter (identifier) */
extern int32 __ctev_ndx; /* tev index counter (identifier) */
extern struct nchglst_t **__nchg_freed; /* nchgs freed - available for reuse */
extern int32 __nchg_free_ndx; /* nchgs freed ndx */
extern int32 __nchg_free_size;/* nchgs freed array size */
extern int32 __const_expr_has_isnums; /* flag to control is IS nums constant */
extern int32 __ludptab_ndx;  /* design wide l udp index (identifier) */
extern int32 __eudptab_ndx;  /* design wide e udp index (identifier) */
extern int32 __dc_id_ndx;    /* design wide delay control index */
extern int32 __stmt_id_ndx;    /* design wide statement index */
extern int32 __fold_for_value; /* folded for loop index */
extern int32 __folding_for_loop; /* T => folding for loop */

/* timing queue scheduling variables */
extern word64 __simtime;      /* current simulaton time (make 64 bits ?) */
extern word32 __num_execstmts;/* total number of executed statements */
extern word32 __num_addedexec;/* number of executed added statements */
extern word32 __num_proc_tevents;/* total num simulation events processed */
extern word32 __nxtstmt_freq_update; /* next ev count for xbig freq upd. */ 
extern word32 __num_cancel_tevents; /* total num sim events processed */
extern int32 __num_init_events; /* num of initial events */
extern word32 __inertial_cancels; /* num resched form later inertial del */
extern word32 __newval_rescheds; /* num rescheduled for same time */
extern word32 __num_netchges; /* num of processed net change records */
extern word32 __immed_assigns;/* num immed assign (not scheduled) */ 
extern word32 __proc_thrd_tevents;/* number of processed thread events */
extern struct q_hdr_t *__qlist_hdr; /* for $q_ system task q list header */
extern int32 __num_switch_vtxs_processed; /* total num tranif chan vtx done */
extern int32 __num_switch_chans; /* total num tranif channels in design */ 
extern int32 __num_inout_chans; /* total num inout switch chans design */ 

/* storage tables variables */
size_t __nxt_ofs;       /* next module all nets offset */

/* simulation control and state values */
/* AIV 04/11/12 - this should be word32 - override for 64-bit movq */
extern word32 __stmt_suspend;  /* set when behavioral code suspends */
extern int32 __run_state;     /* state of current simulation run */
extern int32 __can_exec;      /* T => for vpi sim ctrl - can now exec */
extern int32 __wire_init;     /* T => initializing wires */
extern int32 __no_tmove_levels; /* T => infinite 0 delay loop warn path dist */
extern struct thread_t *__cur_thd;  /* currently executing thread addr. */
extern struct thread_t *__suspended_thd; /* cur thread before suspend */
extern struct thread_t *__thd_freelst; /* free list of threads */
extern t_midat *__suspended_idp; /* cur inst ptr before suspend */
extern struct itree_t *__inst_ptr; /* current if flattened itree place */ 
extern struct mod_t *__inst_mod;   /* module of current itree inst */
extern int32 __inum;          /* iti num  of current inst (always set) */
extern t_midat *__idp;        /* current inst net (for now) data area ptr */
extern struct itree_t **__itstk; /* stack of saved itrees */
extern int32 __itspi;         /* top of itree stack */
extern struct tev_t *__fsusp_tevp;/* in func. step, event to undo(cancel) */
extern struct itree_t *__tmpitp_freelst; /* free list of wrk itps */
extern struct inst_t *__tmpip_freelst; /* free list of wrk ips */
extern struct mod_t *__last_libmdp; /* libary module just read */
extern int32 __seed;          /* SJM 01/27/04 - glb seed needed if no arg */
extern int32 __init_seed;     /* init random seed for +random option */

/* execution state variables */
extern word32 __new_gateval;  /* new gate out val (st. possible) */
extern word32 __old_gateval;  /* before gate change (st. possible) */
extern word32 __new_inputval; /* new input value for tracing message */
extern word32 __old_inputval; /* prev. value of input for wide udp eval */
extern word64 __pdlatechgtim; /* for path tracing latest path chg time */
extern word64 __pdmindel;     /* for path minimum path delay */
extern int32 __nd_neg_del_warn; /* T => must emit warn (or err) for <0 del */ 
extern int32 __force_active;  /* T => for trace deassign while force */ 
extern int32 __assign_active; /* T => for trace release activates assgn */
extern struct dceauxlst_t *__qcaf_dcehdr; /* header of current qcaf dces */
extern int32 __nxt_chan_id;   /* cnter and size for assigning chan ids */
extern int32 __num_repl_scal_chans;/* number of replaced scalar channels */
extern size_t __chanallocsize; /* size of allocated chan tables */
extern struct chanrec_t *__chantab;/* tab of channel records (one per id) */
extern int32 *__sort_chan_ndx;/* for bid comb, selected/sorted chantab ndx */
extern int32 __nxt_maybe_vec; /* and ndx of next to fill */
extern struct vtxlst_t *__stvtxtab[8]; /* per stren value vertex list */ 
extern struct vtxlst_t *__stvtxtabend[8]; /* and ptr to last el on each */
extern struct vtxlst_t *__chg_vtxlst_hdr; /* list of chged vertices to store */
extern struct vtxlst_t *__chg_vtxlst_end; /* and ptr to end */
extern struct vtxlst_t *__off_vtxlst_hdr; /* bid chan vtx list for marks off */
extern struct vtxlst_t *__off_vtxlst_end; /* and ptr to end */
extern struct vtxlst_t *__vtxlst_freelst; /* free list for vtx lists */
extern struct vtx_t *__vtx_freelst;  /* free list for re-using vtxs */   
struct edge_t *__edge_freelst; /* free list for re-using edges */
extern int32 __nxt_bidvtx;    /* glb for next bid vtx index tab pos to fill */

extern word32 __acum_sb;      /* accumulator for stren tran chan combined */
extern word32 __acum_a;       /* accumulator for tran chan non stren */
extern word32 __acum_b;
extern byte *__acum_sbp;      /* ptr to stacked strength byte */
extern struct xstk_t *__acum_xsp; /* ptr to stacked strength byte */

/* end of time slot variables, strobe, monitor, time check */
extern struct strblst_t *__strobe_hdr; /* list strobe display at slot end */
extern struct strblst_t *__strobe_end; /* end of strobe display list */
extern struct strblst_t *__strb_freelst; /* head of free strobe elements */
extern struct st_t *__monit_stp;/* monit if chg display at slot end stmt */
extern t_midat *__monit_idp;    /* current monitor itree element */
extern word32 __slotend_action; /* word32 of 1 bit switches set for action */
extern int32 __monit_active;  /* T => monitor can trigger (default) */
extern struct dceauxlst_t *__monit_dcehdr; /* header of current dces */
extern struct fmonlst_t *__fmon_hdr; /* list of execed (enabled) fmonitors */
extern struct fmonlst_t *__fmon_end;
extern struct fmonlst_t *__cur_fmon; /* current fmon list entry */
extern struct fmselst_t *__fmonse_hdr; /* this slot end fmon eval list */
extern struct fmselst_t *__fmonse_end;
extern struct fmselst_t *__fmse_freelst; /* fmon slot end free list head */

/* interactive execution variables */
extern t_midat *__scope_idp;     /* from $scope itree place */
extern struct task_t *__scope_tskp; /* from $scope task if present */ 
extern struct symtab_t *__last_iasytp; /* last found symbol symbol table */
extern struct iahist_t *__iahtab;/* table of history commands */
extern int32 __iahsiz;        /* current size of history cmd table */
extern int32 __iah_lasti;     /* current (latest) command */
extern struct hctrl_t *__hctrl_hd; /* head of active iact stmts */
extern struct hctrl_t *__hctrl_end;/* and end */
extern int32 __history_on;    /* collecting and saving history is on */
extern int32 __hist_cur_listnum;/* number to list for :history command */
extern int32 __iasetup;       /* F until interactive entered */
extern int32 __ia_entered;    /* F (also for reset) until iact entered */
extern int32 __iact_state;    /* T => in interactive processing */
extern int32 __iact_can_free; /* T => non monitor/strobe, can free */
extern int32 __no_iact;       /* T => no interactive processing for run */
extern int32 __intsig_prt_snapshot; /* T => on no iact end, print shapshot */
extern int32 __reset_count;   /* count of the number of rests ($reset) */
extern int32 __reset_value;   /* 2nd $reset value preserved after reset */ 
extern int32 __list_cur_ifi;  /* index in in fils of current source file */
extern int32 __list_cur_fd;   /* current opened file no. (-1 if none) */
extern int32 __list_cur_lini; /* current line no. in current dbg file */
extern int32 __list_cur_listnum;/* number of lines to list at once */
extern int32 __list_arg_lini; /* for :b (:ib), user list argument */
extern int32 __iact_scope_chg;/* T => always move scope to cur on iact st. */
extern struct brkpt_t *__bphdr;/* header of breakpoint list */ 
extern int32 __nxt_bpnum;     /* next breakpoint number to use */
extern struct dispx_t *__dispxhdr;/* header of display list */ 
extern int32 __nxt_dispxnum;  /* next display number to use */
extern t_midat *__last_stepidp;  /* last step inst. itree loc. */ 
extern struct task_t *__last_steptskp;/* last step task */
extern int32 __last_stepifi;  /* last step in fils index */
extern word64 __last_brktime; /* last break or step time */
extern int32 __dbg_dflt_base; /* :print debugger default base */ 
extern int32 __iact_stmt_err; /* T => syntax error for iact stmt */
extern struct mod_t *__iact_mdp; /* current iact dummy module */
extern int32 __sav_mtime_units; /* prep of iact statements needs tfmt units */

/* interactive variables */
extern char *__iahwrkline;    /* interactive command line work area */
extern int32 __iahwrklen;     /* allocated len of iah work string */
extern int32 __pending_enter_iact;/* T => enter iact as soon as can */
extern int32 __iact_reason;   /* reason for entering interactive state */
extern int32 __single_step;   /* T => need to single step */
extern int32 __step_rep_cnt;  /* number of times to repeat step */
extern int32 __step_from_thread;/* T step from non thread loc. (^c?) */
extern t_midat *__step_match_idp; /* for istep, exec itp must match */
extern int32 __step_lini;     /* line stepping from (must step to next) */  
extern int32 __step_ifi;      /* and file */ 
extern int32 __verbose_step;  /* T => emit location each step */
extern int32 __stop_before_sim; /* T => enter interactive before sim */
extern int32 __dbg_stop_before; /* if >100, T (-100) stop before sim */ 
extern struct st_t *__blklast_stp; /* stmt loc. saved last stmt in block */
extern struct dceauxlst_t *__iact_dcehdr; /* header of current iact dces */

/* event list variables */
extern struct telhdr_t *__cur_timehdr;
extern struct tev_t *__p0_te_hdrp;/* pound 0 event list header */
extern struct tev_t *__p0_te_endp;/* pound 0 event list end */
extern struct tev_t *__cur_te_hdrp;
extern struct tev_t *__cur_tevp; /* ptr to event list for adding to front */
extern struct tev_t *__cur_te_endp;
extern struct tev_t *__tefreelstp;/* free list for events */
extern struct tev_t *__nb_te_hdrp; /* non-blocking new end queue hd */ 
extern struct tev_t *__nb_te_endp; /* and tail */

extern struct tedputp_t *__tedpfreelst; /* tf_ putp rec free list header */
extern struct teputv_t *__teputvfreelst; /* vpi_ put value free list hdr */ 
extern struct nchglst_t *__nchgfreelst; /* change element free list */
extern struct tc_pendlst_t *__tcpendfreelst; /* free slot end changed tchks */
extern struct dltevlst_t *__dltevfreelst; /* pend double event free list */
extern struct tevlst_t *__ltevfreelst; /* pend event free list */

extern struct dpi_t *__dpi_hdrp;     /* DPI hdr structs */
extern struct dpi_t *__dpi_endp;     /* DPI end structs */
extern struct dpi_t *__cur_dpip;     /* currently scanning dpi */
extern int32 __can_have_array_on_rhs; /* DPI can pass array to DPI calls */
extern struct sv_lib_t *__sv_lib_hdrp; /* hdr of sv DPI lib paths */
extern struct sv_lib_t *__sv_lib_endp; /* hdr of sv DPI lib paths */
extern int32 __dpi_file_writing; /* T => wrap puts with only fp wr */
extern char *__dpi_interp_wrapper_fnam; /* file name of interp wrapper */

/* net change list variables */
extern struct nchglst_t *__nchg_futhdr; /* header of future net chg list */
extern struct nchglst_t *__nchg_futend; /* end (for add) of future net chgs */
extern struct tc_pendlst_t *__tcpendlst_hdr; /* header of pending */ 
extern struct tc_pendlst_t *__tcpendlst_end; /* end of pending */
extern struct tev_t **__wrkevtab; /* for exit, trace of pending events */
extern int32 __last_wevti;    /* last filled */
extern int32 __size_wrkevtab; /* and current allocated size */ 

#ifdef __STREE__

#define SENTINEL &(__sentinel)

/* colors red/black */
#define RED 0
#define BLACK 1

/* a tree node for the new red/black tree timing queue */
struct tqnode_t {
 word64 time;             /* the time node (sorted by) */
 int32 color;             /* color of node (red/black) */
 struct tqnode_t *parent; /* node's parent */
 struct tqnode_t *left;   /* node's left child */
 struct tqnode_t *right;  /* node's right child */
 struct tev_t *te_hdrp, *te_endp;
 struct tev_t *nb_hdrp, *nb_endp;
};

/* sentinel point to empty node (NULL) */
extern struct tqnode_t __sentinel;     /* empty node holder */
extern struct tqnode_t *__tree_root;   /* root of tree */
extern struct tqnode_t *__min_time_node; /* current minimum node */
extern struct tqnode_t *__max_time_node; /* current maximum node */

extern struct tqnode_t **__free_nodes; /* nodes freed - available for reuse */
extern int32 __free_node_size;         /* size of freed node array */
extern int32 __free_node_ndx;          /* current freed node index */

#else

struct heap_t {
 int32 hash;              /* time hash index */
 word64 time;             /* the time node (sorted by) */
 struct tev_t *te_hdrp, *te_endp;
 struct tev_t *nb_hdrp, *nb_endp;
 struct heap_t *next;
};

extern struct heap_t **__heap;
extern int32 __heap_size;
extern int32 __heap_maxsize;
extern struct heap_t **__free_heap;
extern int32 __free_heap_ndx;        

#define PARENT(i) i >> 1
#define LEFT(i) 2*i
#define RIGHT(i) 2*i+1
/* AIV 01/21/10 - should align on 2^ changed to 4096 */
#define HEAP_INIT_SIZE 4096

/* AIV 06/06/08 - size of hash should be aligned on 2^ for better code */
#define THASH_SIZE 4096
extern struct heap_t *__time_hash[THASH_SIZE];
extern int32 __collision_count;
#endif

extern struct tev_t **__free_tevs;    /* tevs freed - available for reuse */
extern int32 __free_tev_size;         /* size of freed tev array */
extern int32 __free_tev_ndx;          /* current freed tev index */

extern int32 __insn_count;            /* total insn count */
extern int32 __insn_print_count;      /* actually printed insn count */
extern int32 __coalesce_count;        /* coalesce insn count */
extern int32 __spill_count;           /* spill insn count */
extern int32 __spill_nonw_count;      /* spill non-wide insn count */
extern int32 __design_has_ld_pli_libs;  /* design has +pli/+vpi on cmmnd ln*/
extern int32 __cvc_nd_old_gate_store; /* nd to store gate_out_ofs value */
extern int32 __design_has_auto_task;  /* T => design has auto task/func */
/* end of externs defined in cvc.c */


extern int32 __running_cvc_exe;  /* T => running compiled executable */

/* SJM 05/03/08 - this is the pointer to the design wide init .s func gened */
/* during comm storage alloc, make or pipe must compile the dsgn init */
/* function this pointer is set to it during the compile */
/* SJM 07/10/08 - gnu cc too slow - now gen as asm aslib wrapper calls */ 
extern void (*__dsgn_initp)(void);

extern t_midat **__idpdat_areasp;  /* mod idp area pointers */

extern int32 __gbl_argc;       /* global to hold orig argc num */
extern char **__gbl_argv;      /* global to hold orig argv addr */
extern int32 __execute_compiled; /* execute compiled executable */

#include "systsks.h"
