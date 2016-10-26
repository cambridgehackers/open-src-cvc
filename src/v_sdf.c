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
 * modules to read and back annotate from sdf file
 *
 * uses own itree context does not expect inst_ptr or inst mod to be set
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

/* this shares some vpi_ delay code */
#include "vpi_user.h"
#include "cv_vpi_user.h"

/* some max number of delay components */
#define SDF_MTMDNUM 3
#define SDF_PULDNUM 3
#define SDF_MAXDELS 12

/* rvalue types */
#define SDF_NOVAL 1
#define SDF_1VAL 2
#define SDF_MTMVAL 3

/* delay form keyword constants - must start above 99 (verilog op region) */
/* mostly overlapping Verilog directive range */
/* SJM 12/15/03 - added new 2001 LRM time checks and renumbered */
#define SDF_ABSOLUTE 100
#define SDF_ARRIVAL 101 
#define SDF_CCOND 102
#define SDF_CELL 103
#define SDF_CELLTYPE 104
#define SDF_COND 105
#define SDF_CONDELSE 106
#define SDF_DATE 107
#define SDF_DELAY 108
#define SDF_DELAYFILE 109
#define SDF_DEPARTURE 110
#define SDF_DESIGN 111
#define SDF_DEVICE 112
#define SDF_DIFF 113
#define SDF_DIVIDER 114
#define SDF_EXCEPTION 115
#define SDF_FULLSKEW 116
#define SDF_HOLD 117
#define SDF_INCREMENT 118
#define SDF_INSTANCE 119
#define SDF_INTERCONNECT 120
#define SDF_IOPATH 121
#define SDF_LABEL 122
#define SDF_NAME 123
#define SDF_NOCHANGE 124
#define SDF_PATHCONSTRAINT 125
#define SDF_PERIODCONSTRAINT 126
#define SDF_PATHPULSE 127
#define SDF_PATHPULSEPERCENT 128
#define SDF_PERIOD 129
#define SDF_PORT 130
#define SDF_PROCESS 131
#define SDF_PROGRAM 132
#define SDF_RECREM 133
#define SDF_RECOVERY 134
#define SDF_REMOVAL 135
#define SDF_RETAIN 136
#define SDF_SCOND 137
#define SDF_SKEWCONSTRAINT 138
#define SDF_SLACK 139
#define SDF_SETUP 140 
#define SDF_SETUPHOLD 141 
#define SDF_SKEW 142 
#define SDF_SUM 143
#define SDF_TEMPERATURE 144
#define SDF_TIMESCALE 145
#define SDF_TIMESKEW 146
#define SDF_TIMINGCHECK 147
#define SDF_TIMINGENV 148
#define SDF_VENDOR 149
#define SDF_VERSION 150
#define SDF_VOLTAGE 151
#define SDF_WAVEFORM 152
#define SDF_WIDTH 153
#define SDF_NEGEDGE 154
#define SDF_POSEDGE 155

#define SDF_BKEYS SDF_ABSOLUTE

/* sdf only records */
struct pthlst_t {
 struct spcpth_t *lpthp;
 struct pthlst_t *pthlnxt;
};

struct tclst_t {
 struct tchk_t *tcp;
 struct tclst_t *tclnxt;
};

struct tcterm_t {
 char *tnam;
 int32 ti1, ti2, eval;
 char *cndnam;
 int32 cndi1, cndi2;
 int32 cnd_op, cnd_const;
};

/* sdf only declares */
static char __pathsep; 
static char __sdf_none_str[20];
static char __sdf_work_str[IDLEN];
static char __sdf_varnam[IDLEN];
static char *__sdf_version;
static char *__sdf_design;
static char *__sdf_date; 
static char *__sdf_vendor;
static char *__sdf_program;
static char *__sdf_progversion;
static double __sdf_voltage;
static double __sdf_temp;
static char *__sdf_process;
static int32 __sdf_timescale;    /* this is internal pos. time unit exp */    
static char __sdf_star_val[4]; /* special " * " string for all inst. star */ 
static int32 __sdf_tokval;
static struct itree_t *__sdf_cntxt_itp;
static int32 __seen_ppulse;      /* per SDF file, 1 warn if path pulse used */
static int32 __seen_pc_ppulse;   /* same for path pulse percent */
static int32 __seen_rlim_delval; /* 1 warn if reject limit in delval */ 
static int32 __seen_xlim_delval; /* 1 warn if x (error) limit in delval */ 
static int32 __sdf_nd_tscale;    /* T => SDF file timescale different */
static int32 __sdf_ts_units;     /* unit difference for SDF TIMESCALE */
static struct t_vpi_delay *__sdf_delp;
static struct t_vpi_delay *__sdf_delp2;
static int32 __id_qualpath;
static int32 __id_select;
static int32 __id_partsel;
static int32 __rding_cond_expr;  /* reading cond form - scalars cons allowd */ 

/* SJM 07/08/01 - change so user can specify log file - then replaces here */
static char *__sdf_log_fnam;   /* name of SDF log file */
static FILE *__sdf_log_s;      /* and stream */ 
static FILE *__sdf_sav_log_s;  /* just need to save normal log file */  

/* local prototypes */
static void alloc_sdf_mdp(void);
static void sdf_annotate(char *, char *, int32, int32);
static void do_systsk_sdf_annotate(char *, struct itree_t *, int32, int32);
static void do_sdf_annotate(char *, int32, int32);
static void free_sdf_hdrvals(void);
static char *get_sdfcntxtnam(char *, struct itree_t *);
static void init_vpi_del(struct t_vpi_delay *, int32);
static void rd_sdf_file(FILE *);
static char *mtm_sel_tonam(char *, int32);
static int32 rd_sdf_sepchar(FILE *, char *);
static int32 rd_sdf_timescaleval(FILE *, int32 *);
static int32 rdset_sdf_cells(FILE *);
static struct itree_t *get_sdfdownrel_itp(struct expr_t *, struct itree_t *,
 struct sy_t **, char *);
static int32 rdset_prim_delay(FILE *, struct sy_t *, int32, char *, struct sy_t *);
static int32 prim_rdset_device_del(FILE *, struct itree_t *, struct sy_t *,
 struct gate_t *);
static void set_device_del(struct itree_t *, struct gate_t *, struct sy_t *);
static void set_logic_gdel_tox_val(struct gate_t *);
static void set_toz_gdel_tox_val(struct gate_t *);
static void prep_sdfdev_verbmsg(struct gate_t *, struct gate_t *,
 struct itree_t *, struct mod_t *);
static void emit_sdfdev_verbmsg(struct gate_t *, struct gate_t *, char *);
static int32 rdset_timing_spec(FILE *, struct itree_t *, struct mod_t *);
static char *get_sdfinam(char *, struct itree_t *, struct mod_t *);
static int32 rdset_deltyps(FILE *, struct itree_t *, struct mod_t *);
static int32 port_qual_nam(char *, char *);
static int32 rd_1_val(FILE *, char *);
static int32 rd2_1_val(FILE *);
static int32 rd_1or2_vals(FILE *, char *);
static int32 rd_4_vals(FILE *, char *);
static int32 rd_deldef(FILE *, struct itree_t *, struct mod_t *, char *);
static void dellst_err(char *, char *);
static void formend_err(char *);
static int32 rd_iopath(FILE *, struct itree_t *, struct mod_t *,
 struct expr_t *, int32, char *);
static void set_1pthdel(struct pthlst_t *, struct itree_t *, struct mod_t *);
static void prep_sdfiopath_verbmsg(struct spcpth_t *, struct gate_t *,
 struct itree_t *, struct mod_t *);
static void emit_sdfiopath_verbmsg(struct spcpth_t *, struct gate_t *, char *);
static int32 upd_sdf_perinst_del(struct gate_t *, p_vpi_delay, struct mod_t *,
 int32, int32, int32, char *);
static int32 itp_under_cntxt(struct itree_t *);
static int32 rd_port_spec(FILE *, char *, int32 *, int32 *, int32 *, int32);
static int32 rd_port(FILE *, char *, int32 *, int32 *);
static struct pthlst_t *bld_match_spcpth(struct mod_t *, char *, int32, int32,
 int32, char *, int32, int32, struct expr_t *, int32);
static void free_pthlst(struct pthlst_t *);
static char *msg_sdfpath_tostr(char *, char *, int32, int32, int32, char *, int32,
 int32, struct expr_t *, int32);
static int32 rd_del_def_cond(FILE *, struct itree_t *, struct mod_t *, char *);
static int32 col_cond_port_expr(FILE *);
static int32 sdf_bld_expnode(void);
static int32 rdset_tchk_defs(FILE *, struct itree_t *, struct mod_t *);
static void set_half_setuphold_tchk_defs(struct tclst_t *, int32,
 struct itree_t *, struct mod_t *);
static void set_half_recrem_tchk_defs(struct tclst_t *, int32,
 struct itree_t *, struct mod_t *);
static int32 rdset_2term_1v_tchk(struct tclst_t **, int32 *, FILE *,
 struct mod_t *, char *, int32, int32, int32 *);
static int32 rdset_1term_1v_tchk(struct tclst_t **, FILE *, struct mod_t *,
 char *, int32, int32, int32 *);
static int32 rdset_2term_2v_tchk(struct tclst_t **, FILE *, struct mod_t *,
 char *, int32, int32, int32 *);
static void prep_sdftchk_verbmsg(struct tchk_t *, char *, struct gate_t *,
 struct itree_t *, struct mod_t *, char *);
static void emit_sdftchk_verbmsg(struct tchk_t *, char *, struct gate_t *,
 char *, char *);
static int32 rd_port_tchk(FILE *, struct tcterm_t *);
static int32 rd_tchk_cond(FILE *, struct tcterm_t *);
static int32 rd_scalar_node(FILE *, char *, int32 *);
static int32 from_sdf_tctyp(int32);
static struct tclst_t *bld_match_tchk(struct mod_t *, struct tcterm_t *,
 struct tcterm_t *, int32, char *);
static int32 same_tchk_cond(struct tcterm_t *, struct expr_t *);
static void free_tclst(struct tclst_t *);
static void free_tct_insides(struct tcterm_t *);
static int32 rdset_port_mipd(FILE *, struct itree_t *, struct mod_t *, char *);
static void set_mipd_dels(struct itree_t *, char *, int32, int32);
static void try_find_set_intercon_prim_del(struct mod_pin_t *, int32,
 struct mod_t *, struct itree_t *, char *);
static struct net_pin_t *find_intercon_gate_drvr(struct itree_t **,
 struct mod_pin_t *, int32, struct mod_t *, char *);
static char *bld_interconn_drv_emsg(char *, struct mod_pin_t *, struct mod_t *);
static struct net_pin_t *fnd_xlflat_one_gate_drvr(struct net_t *,
 int32, struct itree_t **);
static struct net_pin_t *find_gate_drvr(struct net_pin_t *, struct net_t *,
 int32);
static char *msgpref_tostr(char *, struct mod_pin_t *);
static struct itree_t *find_1under_itp(struct mod_t *);
static int32 xtrct_portdev(struct itree_t **, char *, char *, struct itree_t *,
 char *, char *);
static struct mod_pin_t *get_inport_fr_nam(struct mod_t *, char *);
static int32 getsrch_portnam(struct mod_t *, char *);
static struct mod_pin_t *get_outport_fr_nam(struct mod_t *, char *);
static struct mod_pin_t *get_bidport_fr_nam(struct mod_t *, char *);
static int32 rdset_interconn_dels(FILE *, struct itree_t *, struct mod_t *,
 char *);
static void chkset_interconn_dels(struct itree_t *, char *, int32, int32, char *,
 int32, int32);
static char *bld_prefnam(char *, char *, int32, int32);
static void add_srcdst_impth(struct mipd_t *, struct mod_pin_t *, int32, int32,
 struct itree_t *, char *);
static int32 rdset_devpath_dels(FILE *, struct itree_t *, struct mod_t *,
 char *);
static void set_allpths_dels(struct itree_t *, struct mod_t *);
static void set_alloutpths_dels(char *, int32, int32, struct itree_t *,
 struct mod_t *);
static int32 not_a_port(char *, int32, struct mod_t *, char *);
static int32 rdskip_te_defs(FILE *);
static int32 rd_exception(FILE *);
static int32 rd_constraint_path(FILE *, char *, int32);
static int32 rd_edgepair_list(FILE *);
static int32 rdset_labels(FILE *, struct itree_t *, struct mod_t *);
static int32 xtrct_param(struct itree_t **, char *, struct itree_t *);
static struct xstk_t *sdf_push_rvalue(struct net_t *, double);
static void emit_sdflblverb_msg(struct net_t *, struct xstk_t *, char *);
static int32 sdf_adjust_incr(struct net_t *, struct xstk_t *, int32);
static int32 bld_sdfnewdu(struct gate_t *, struct gate_t *, p_vpi_delay,
 struct itree_t *, int32, int32, char *);
static int32 sdf_fillchk_tim(word64 *, int32 *, int32 *, int32 *,
 p_vpi_delay, char *);
static int32 vpi_delay_all0s(p_vpi_delay);
static int32 rd_sdf_dellst(FILE *, char *);
static int32 rd_rtriple(FILE *, struct t_vpi_time *);
static int32 rd_sdf_formtyp(FILE *);
static int32 rd2_sdf_formtyp(FILE *);
static int32 rd_sdf_strval(FILE *);
static void get_sdftok(FILE *);
static int32 sdf_rd_comment(FILE *);
static int32 sdf_collect_str(FILE *);
static int32 sdf_collect_num(FILE *, int32);
static int32 chkcnv_sdfpath(char *, int32 *, int32 *, char *, int32);
static char *fnd_pth_sep(char *);
static int32 chkcnv_sdfid(char *, int32 *, int32 *, char *, int32);
static int32 sdf_getsel_indices(int32 *, int32 *, char *);
static int32 sdf_skip_form(FILE *);
static int32 rd_edge_ident(FILE *);
static int32 rd_scalar_const(FILE *);
static char *prt_sdftok(void);
static int32 get_sdfkeywrd(char *);
static char *get_skeynam(char *, int32);

/* extern prototypes (maybe defined in this module) */
extern void __process_sdf_files(void);
extern void __process_sdf_tskenables(void);
extern void __chg_param_tois(struct net_t *, struct mod_t *);

extern FILE *__my_fopen(char *, char *);
extern FILE *__tilde_fopen(char *, char *);
extern void __my_fclose(FILE *);
extern void __my_free(void *, size_t);
extern char *__my_malloc(size_t);
extern char *__msg2_blditree(char *, struct itree_t *);
extern char *__msg2_ndx_blditree(char *, int32);
extern char *__pv_stralloc(char *);
extern char *__to_timunitnam(char *, word32);
extern char *__get_tmult(char *, word32 *);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct expr_t *__glbnam_to_expr(char *);
extern char *__to_glbcmp_nam(struct expr_t *);
extern char *__bld_glbcmp_ginam(char *, struct expr_t *);
extern int32 __ip_indsrch(char *);
extern int32 __add_gate_pnd0del(struct gate_t *, struct mod_t *, char *);
extern void __chg_1inst_del(struct gate_t *, struct itree_t *, struct gate_t *);
extern void __free_del(union del_u, word32, int32);
extern char *__bld_delay_str(char *, union del_u, word32);
extern char *__bld_lineloc(char *, word32, int32);
extern char *__to_edgenam(char *, word32);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern void __xtract_wirng(struct expr_t *, struct net_t **, int32 *, int32 *);
extern void __add_alloc_mipd_npp(struct net_t *, struct mod_t *);
extern void __re_prep_dels(struct net_t *, struct itree_t *, struct mod_t *,
 int32);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern int32 __real_to_v64tim(word64 *, double);
extern void __sizchgxs(struct xstk_t *, int32);
extern char *__regab_tostr(char *, word32 *, word32 *, int32, int32, int32);
extern void __ld_wire_val_xstk(struct xstk_t *, struct net_t *);
extern int32 __wide_vval_is0(word32 *, int32);
extern int32 __do_widecmp(int32 *, word32 *, word32 *, word32 *, word32 *,
 int32);
extern void __lsub(word32 *, word32 *, word32 *, int32);
extern void __ladd(word32 *, word32 *, word32 *, int32);
extern void __extract_delval_compile_time(word64 *, int32 *, union del_u, 
 word32, int32);
extern void __fill_16vconst(word64 *, word64 *, int32);
extern void __fill_4vconst(word64 *, word64 *, word64 *, word64 *, int32, int32);
extern double __my_strtod(char *, char **, int32 *);
extern word32 __my_strtoul(char *, char **, int *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern void __free_xtree(struct expr_t *);
extern void __init_mod(struct mod_t *, struct sy_t *);
extern struct itree_t *__itp_xmrget_refgrp_to_targ(struct gref_t *, 
 struct itree_t *);
extern char * __get_eval_cstr(struct expr_t *, int32 *);
extern char *__to_timstr(char *, word64 *);
extern int32 __cmp_xpr(struct expr_t *, struct expr_t *, int32 *);
extern void __bld_xtree(int32);
extern void __set_xtab_errval(void);
extern int32 __alloc_shareable_cval(word32, word32, int32);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern struct expr_t *__alloc_exprnd(void);
extern struct expridtab_t *__alloc_expridnd(char *);
extern struct tenp_t *__bld_portbit_netbit_map(struct mod_pin_t *);
extern void __setup_mipd(struct mipd_t *, struct net_t *, int32);
extern void __exec_sdf_annotate_systsk(struct expr_t *);
extern char *__msg2_idp_blditree(char *, t_midat *);
extern int32 __bld_xl_drvld_vtxtab(struct net_t *, int32, struct itree_t *,
 int32);
extern void __get_bidnpp_sect(struct net_t *, struct net_pin_t *, int32 *,
 int32 *);

extern void __cv_msg(char *, ...);
extern void __pv_ferr(int32, char *, ...);
extern void __pv_fwarn(int32, char *, ...);
extern void __sgfwarn(int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __finform(int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);

extern const char __pv_ctab[];
extern const word32 __masktab[];
extern const double __dbl_toticks_tab[];
extern const struct opinfo_t __opinfo[];

/*
 * process all sdf annotate files (from options) just before init for sim
 */
extern void __process_sdf_files(void)
{
 struct sdfnamlst_t *sdfp;
 int32 sav_slin_cnt, sav_sfnam_ind;
 char *sav_fnam;

 if (__sdf_opt_log_fnam != NULL)
  {
   if ((__sdf_opt_log_s = __tilde_fopen(__sdf_opt_log_fnam, "w")) == NULL)
    {
     __sgfwarn(505,
      "cannot open SDF log file %s from +sdf_log_file option - using normal log file",
      __sdf_opt_log_fnam);
     __sdf_opt_log_s = NULL;
     __sdf_opt_log_fnam = NULL;
    }
   else
    { 
     __cv_msg(
      "  SDF: writing SDF annotation messages and errors to separate SDF log file %s\n",
      __sdf_opt_log_fnam); 
     __sdf_sav_log_s = __log_s;
     __log_s = __sdf_opt_log_s;
    }
  }

 /* since this is before simulation sdf mdp always nil here */
 if (__sdf_mdp == NULL) alloc_sdf_mdp();

 /* need to treat as interactive state call from first top level */
 __cur_thd = NULL;
 sav_fnam = __in_fils[0];
 /* need to save-restore sgf... type locations since used as work vars */
 sav_slin_cnt = __slin_cnt;
 sav_sfnam_ind = __sfnam_ind;
 for (sdfp = __sdflst; sdfp != NULL; sdfp = sdfp->sdfnamnxt)
  {
   /* need slincnt and sfnam ind for string path name processing here */
   __in_fils[0] = sdfp->optfnam;
   /* here - after annotation complete - cleans up and frees memory */
   sdf_annotate(sdfp->fnam, sdfp->scopnam, 0, sdfp->opt_slcnt);
  }

 /* SJM 07/08/01 - put back normal log file if changed */ 
 if (__sdf_opt_log_s != NULL) __log_s = __sdf_sav_log_s;

 __in_fils[0] = sav_fnam;
 __slin_cnt = sav_slin_cnt; 
 __sfnam_ind = sav_sfnam_ind;
 /* LOOKATME - could free sdf mdp here */
}

/*
 * routine to allocate sdf_mdp - need for converting instance names to path
 */
static void alloc_sdf_mdp(void)
{
 struct sy_t *syp;

 /* allocate work sdf module - needed glbndp con tab */
 __sdf_mdp = (struct mod_t *) __my_malloc(sizeof(struct mod_t)); 
 syp = (struct sy_t *) __my_malloc(sizeof(struct sy_t));
 syp->synam = __pv_stralloc("**SDF WORK**");
 syp->sydecl = TRUE;

 __init_mod(__sdf_mdp, syp);
 __sdf_mdp->flatinum = 1;
 syp->el.emdp = __sdf_mdp;
}

/*
 * routine to process all in source sdf annotate calls before compilation 
 * now the default unless +sdf_during_sim option selected
 *
 * SJM 08/28/05 - added for CVC
 */
extern void __process_sdf_tskenables(void)
{
 int32 sav_slin_cnt, sav_sfnam_ind;
 struct sdf_tskenlst_t *sdflp;
 struct st_t *stp;
 struct tskcall_t *tkcp;
 char *sav_fnam;

 /* need to treat as interactive state call from first top level */
 __cur_thd = NULL;
 sav_fnam = __in_fils[0];
 /* need to save-restore sgf... type locations since used as work vars */
 sav_slin_cnt = __slin_cnt;
 sav_sfnam_ind = __sfnam_ind;

 for (sdflp = __sdftskenlst; sdflp != NULL; sdflp = sdflp->sdf_tsken_nxt)
  {
   __sdf_mdp = sdflp->sdf_stp_mod;
   stp = sdflp->sdf_annotate_stp;
   __in_fils[0] = __in_fils[stp->stfnam_ind];
   __sfnam_ind = stp->stfnam_ind;
   __slin_cnt = stp->stlin_cnt;

   if (__sdf_mdp->flatinum > 1)
    {
     __sgfwarn(3143,
      "$sdf_annotate task called from module instantiated %d times - sdf file compiled only in first instance",
      __sdf_mdp->flatinum);
    }
   tkcp = &(stp->st.stkc);
   __push_itstk(__sdf_mdp->moditps[0]);
   __exec_sdf_annotate_systsk(tkcp->targs);
   __pop_itstk();
  }

 /* restore state */
 __in_fils[0] = sav_fnam;
 __slin_cnt = sav_slin_cnt; 
 __sfnam_ind = sav_sfnam_ind;
}

/*
 * open - read - close the sdf annotation file and annotate (set) values
 *
 * run at compile time because can set delays on non delay element
 * simulation not run if error here
 * runs in isolation - all trace gone when routine returns
 * knows slin cnt environment set 
 */
static void sdf_annotate(char *sdf_fnam, char *sdf_scopnam, int32 fnind,
 int32 slcnt)
{
 int32 sdfenum, sav_no_errs, sav_no_warns;
 struct expr_t *glbndp;
 char s1[RECLEN], s2[RECLEN];

 /* open sdf annotation file */
 if ((__sdf_s = __my_fopen(sdf_fnam, "r")) == NULL)
  {
   __gferr(1370, fnind, slcnt, 
    "cannot open +sdf_annotate SDF input file %s", sdf_fnam);
   return;
  }

 /* need to save error count for system task - will be 0 if from option */
 __sdf_sav_enum = __pv_err_cnt;

 /* if no scope use first top module */
 __cur_thd = NULL;
 if (sdf_scopnam == NULL || strcmp(sdf_scopnam, "") == 0)
   __sdf_cntxt_itp = NULL;
 else
  {
   /* scope context for sdf file must always be rooted and is Verilog path */
   /* need to use interactive global context here */
   __push_wrkitstk(__sdf_mdp, 0);
   /* this does not use itree context but uses expr routines that need */
   /* inst mod set */
   if ((glbndp = __glbnam_to_expr(sdf_scopnam)) != NULL) 
    {
     /* for null context, down rel is really rooted */
     __sdf_cntxt_itp = get_sdfdownrel_itp(glbndp, NULL, NULL, s2);
     /* now done with glb expr. */ 
     __free_xtree(glbndp);
     __pop_wrkitstk();
     if (__sdf_cntxt_itp == NULL)
      {
       __gferr(1350, fnind, slcnt, 
        "for +sdf_annotate SDF input file %s context %s illegal: %s", sdf_fnam,
        sdf_scopnam, s2);  
annot_fail:
       __my_fclose(__sdf_s);
       if (__verbose)
        {
        __cv_msg(
         "  SDF delay +sdf_annotate failed for \"%s\" in context scope %s\n",
         sdf_fnam, s1);
        }
       return;
      }
    }
   else
    {
     __pop_wrkitstk();
     __gferr(1350, fnind, slcnt, 
      "for +sdf_annotate SDF input file %s context %s illegal - rooted instance not found",
      sdf_fnam, sdf_scopnam);  
     goto annot_fail;
    }
  }
 /* here always use command option mintypmax delay selector */
 __sdf_mintypmax_sel = __mintypmax_sel;

 /* SJM 06/16/00 - must never stop no matter how many SDF errors */
 __sdf_sav_maxerrs = __max_errors;
 __max_errors = 0;
 __sdf_active = TRUE;

 /* SJM 07/08/01 - add new do not print sdf errors and warns option */
 sav_no_errs = __no_errs;
 sav_no_warns = __no_warns;
 if (__sdf_no_errs) __no_errs = TRUE;
 if (__sdf_no_warns) __no_warns = TRUE;

 do_sdf_annotate(sdf_fnam, fnind, slcnt);
 __max_errors = __sdf_sav_maxerrs;
 __sdf_active = FALSE;

 /* always replace saved no errs and no warns */
 __no_errs = sav_no_errs;
 __no_warns = sav_no_warns; 

 get_sdfcntxtnam(s1, __sdf_cntxt_itp);
 __sdf_cntxt_itp = NULL;

 /* SJM 06/06/00 - change so report but do not count SDF errors */
 if (__pv_err_cnt > __sdf_sav_enum)
  {
   sdfenum = __pv_err_cnt - __sdf_sav_enum;
   __pv_err_cnt = __sdf_sav_enum;

   __cv_msg(
    "  **%d SDF Errors** during +sdf_annotate of \"%s\" context scope %s.\n",
    sdfenum, sdf_fnam, s1);
  }
 if (__verbose) 
  {
   __cv_msg(
    "  SDF delay +sdf_annotate completed for \"%s\" context scope %s.\n",
    sdf_fnam, s1);
  }
}

/*
 * execute $sdf_annotate call
 *
 * SJM 07/08/01 - change to allow setting different log file during SDF read
 * AIV 10/04/07 - changed this back to use itree context need to add sdf
 * info to idp so must be done without using idp info
 */
extern void __exec_sdf_annotate_systsk(struct expr_t *axp)
{
 int32 argi;
 int32 slen, slen2;
 struct itree_t *cntxt_itp;
 char *fnchp, *mtmchp, *sdflogfn_chp;

 /* always need sdf mdp (so inst mod set) for decomping sdf qualified name */
 /* does not need instance context, just needs to be set */ 
 if (__sdf_mdp == NULL) alloc_sdf_mdp();

 fnchp = NULL;
 sdflogfn_chp = NULL;
 __sdf_log_fnam = NULL;
 
 cntxt_itp = NULL;
 mtmchp = NULL;
 slen = slen2 = 0;
 /* assume sdf annotate systf call does not override command line option */
 __sdf_mintypmax_sel = __mintypmax_sel;
 
 /* SJM 07/09/01 - must skip opempty non required arguments */
 for (argi = 0; axp != NULL; axp = axp->ru.x, argi++)
  {
   /* know there will always be at least one arg */
   if (argi == 0)
    {
     fnchp = __get_eval_cstr(axp->lu.x, &slen);
     continue;
    }
   if (argi == 1)
    {
     if (axp->lu.x->optyp == OPEMPTY) continue;

     /* module instance context */
     cntxt_itp = __itp_xmrget_refgrp_to_targ(axp->lu.x->ru.grp, __inst_ptr);
     continue;
    }
   if (argi == 3)
    {
     if (axp->lu.x->optyp == OPEMPTY) continue;

     /* name of different log file */
     sdflogfn_chp = __get_eval_cstr(axp->lu.x, &slen);
     continue;
    } 
   if (argi == 4)
    {
     if (axp->lu.x->optyp == OPEMPTY) continue;

     /* MTM selector */
     mtmchp = __get_eval_cstr(axp->lu.x, &slen2);
     if (strcmp(mtmchp, "MINIMUM") == 0) __sdf_mintypmax_sel = DEL_MIN;
     else if (strcmp(mtmchp, "TYPICAL") == 0) __sdf_mintypmax_sel = DEL_TYP; 
     else if (strcmp(mtmchp, "MAXIMUM") == 0) __sdf_mintypmax_sel = DEL_MAX; 
     else if (strcmp(mtmchp, "TOOL_CONTROL") == 0)
      __sdf_mintypmax_sel = __mintypmax_sel;
     else
      {
       __sgfwarn(627,
        "$sdf_annotate fifth mtm_spec argument %s illegal - using default TOOL_CONTROL",
        mtmchp);
      }
    }
  }
 /* if not 2nd arg, use current itree context */
 if (cntxt_itp == NULL) cntxt_itp = __inst_mod->moditps[0];

 /* change to sdf log file, if given in system task */ 
 if (fnchp != NULL && sdflogfn_chp != NULL)
  {
   if ((__sdf_log_s = __tilde_fopen(sdflogfn_chp, "w")) == NULL)
    {
     __sgfwarn(505,
      "cannot open fourth argument separate SDF log file %s - using normal log file",
      sdflogfn_chp);
     __sdf_log_s = NULL;
     __sdf_log_fnam = NULL;
     goto log_chg_done;
    }
   __sdf_log_fnam = __my_malloc(strlen(sdflogfn_chp) + 1);
   strcpy(__sdf_log_fnam, sdflogfn_chp);
   __sdf_sav_log_s = __log_s;
   if (__sdf_opt_log_fnam != NULL)
    {
     __sgfwarn(505,
      "use of fourth argument SDF log file %s over-rides SDF log file %s set on command line",
      sdflogfn_chp, __sdf_opt_log_fnam);
    }
   /* notice message about use of log file goes to normal log file */
   __cv_msg(
    "  SDF: writing SDF annotation messages and errors to separate SDF log file %s\n",
    __sdf_log_fnam); 
   __log_s = __sdf_log_s;
   goto log_chg_done;
  }
 /* SJM 07/08/01 - see if SDF log file set from command line */
 if (__sdf_opt_log_fnam != NULL)
  {
   if (__sdf_opt_log_s != NULL)
    {
     __sdf_log_s = __sdf_opt_log_s;
     __sdf_log_fnam = __sdf_opt_log_fnam;
     __sdf_sav_log_s = __log_s;
     __log_s = __sdf_log_s;
     goto log_chg_done;
    }

   if ((__sdf_opt_log_s = __tilde_fopen(__sdf_opt_log_fnam, "w")) == NULL)
    {
     __sgfwarn(505,
      "cannot open SDF log file %s from +sdf_log_file option - using normal log file",
      __sdf_opt_log_fnam);
     __sdf_log_s = NULL;
     __sdf_log_fnam = NULL;
     __sdf_opt_log_fnam = NULL;
     goto log_chg_done;
    }
   __cv_msg(
    "  SDF: writing SDF annotation messages and errors to separate SDF log file %s\n",
    __sdf_opt_log_fnam); 

   __sdf_log_s = __sdf_opt_log_s;
   __sdf_log_fnam = __sdf_opt_log_fnam;
   __sdf_sav_log_s = __log_s;
   __log_s = __sdf_log_s;
  }

log_chg_done:
 if (__sdf_verbose)
  {
   char s1[RECLEN], s2[RECLEN];

   __cv_msg(
    "  SDF: now %s executing $sdf_annotate task at %s in %s context %s\n",
    __to_timstr(s1, &__simtime), __bld_lineloc(__xs, __sfnam_ind,
    __slin_cnt), __msg2_blditree(s2, __inst_ptr), 
     __msg2_blditree(__xs2, cntxt_itp)); 

   if (__sdf_mintypmax_sel != __mintypmax_sel)
    {
     __cv_msg(
      "  SDF: selecting %s delays instead of %s from mtm_spec $sdf_annotate argument\n",
      mtm_sel_tonam(__xs, __sdf_mintypmax_sel), mtm_sel_tonam(__xs2,
      __mintypmax_sel));
    }
  } 

 /* LOOKATME - can fnchp be nil */
 if (fnchp != NULL)
  {
   do_systsk_sdf_annotate(fnchp, cntxt_itp, __sfnam_ind, __slin_cnt);
   __my_free(fnchp, slen + 1);
  }
 if (mtmchp != NULL) __my_free(mtmchp, slen2);

 /* SJM 07/08/01 - put back normal log file if changed */ 
 if (__sdf_log_s != NULL) 
  {
   __sdf_log_s = NULL;
   __sdf_log_fnam = NULL;
   __log_s = __sdf_sav_log_s;
  }
}

/*
 * open - read - close the sdf annotation file from $sdf_annotate system task
 * call routine to do annotation
 *
 * this runs in run time context $sdf_annotate task call
 */
static void do_systsk_sdf_annotate(char *sdf_fnam, struct itree_t *itp, 
 int32 fnind, int32 slcnt)
{
 int32 sdfenum, sav_no_errs, sav_no_warns;
 char s1[RECLEN];

 /* need to save error count for system task - will be 0 if from option */
 __sdf_sav_enum = __pv_err_cnt;

 /* open sdf annotation file */
 if ((__sdf_s = __my_fopen(sdf_fnam, "r")) == NULL)
  {
   __gferr(1370, fnind, slcnt, 
    "cannot open $sdf_annotate SDF input file %s", sdf_fnam);
   __pv_err_cnt = __sdf_sav_enum;
   return;
  }

 /* SJM 06/16/00 - must never stop no matter how many SDF errors */
 __sdf_active = TRUE;
 __sdf_sav_maxerrs = __max_errors;
 __max_errors = 0;

 /* SJM 07/08/01 - add new do not print sdf errors and warns option */
 sav_no_errs = __no_errs;
 sav_no_warns = __no_warns;
 if (__sdf_no_errs) __no_errs = TRUE;
 if (__sdf_no_warns) __no_warns = TRUE;

 __sdf_cntxt_itp = itp;
 do_sdf_annotate(sdf_fnam, fnind, slcnt);
 __max_errors = __sdf_sav_maxerrs;
 __sdf_active = FALSE;
 /* always replace saved no errs and no warns */
 __no_errs = sav_no_errs;
 __no_warns = sav_no_warns; 

 get_sdfcntxtnam(s1, __sdf_cntxt_itp);
 __sdf_cntxt_itp = NULL;

 /* SJM 06/06/00 - change so report but do not count SDF errors */
 if (__pv_err_cnt > __sdf_sav_enum)
  {
   sdfenum = __pv_err_cnt - __sdf_sav_enum;
   __pv_err_cnt = __sdf_sav_enum;
   __cv_msg(
    "  **%d SDF errors during $sdf_annotate of \"%s\" context scope %s\n",
    sdfenum, sdf_fnam, s1);
  }
 else if (__verbose) 
  {
   __cv_msg(
    "  SDF delay $sdf_annotate completed for \"%s\" context scope %s.\n",
    sdf_fnam, s1);
  }
}

/*
 * routine to read and annotate sdf file 
 *
 * called either by +sdf_annotate command line option processing routine
 * or $sdf_annotate system task 
 *
 * use global __sdf_s stream to read sdf file
 */
static void do_sdf_annotate(char *sdf_fnam, int32 fnind, int32 slcnt)
{
 int32 sav_lin_cnt, ndels;
 char *sav_fnam;

 /* assume none for these since form optional */
 strcpy(__sdf_none_str, "[none]");
 __sdf_version = __sdf_none_str; 
 __sdf_design = __sdf_none_str;
 __sdf_date = __sdf_none_str;
 __sdf_vendor = __sdf_none_str; 
 __sdf_program = __sdf_none_str; 
 __sdf_progversion = __sdf_none_str; 
 __sdf_process = __sdf_none_str; 

 /* allocate the global work vpi delay record */
 __sdf_delp = (struct t_vpi_delay *) __my_malloc(sizeof(struct t_vpi_delay));
 /* need extra delay need to read 13th for error detection */
 ndels = SDF_MTMDNUM*SDF_PULDNUM*(SDF_MAXDELS+1);
 __sdf_delp->da = (struct t_vpi_time *)
  __my_malloc(ndels*sizeof(struct t_vpi_time)); 
 init_vpi_del(__sdf_delp, ndels);
 /* 2nd needed for separating timing check limits */
 __sdf_delp2 = (struct t_vpi_delay *) __my_malloc(sizeof(struct t_vpi_delay));
 __sdf_delp2->da = (struct t_vpi_time *)
  __my_malloc(ndels*sizeof(struct t_vpi_time)); 
 init_vpi_del(__sdf_delp2, ndels);
 
 /* set flag so only one warning emitted if used */ 
 __seen_ppulse = FALSE;
 __seen_pc_ppulse = FALSE;
 __seen_rlim_delval = FALSE;
 __seen_xlim_delval = FALSE;

 sav_lin_cnt = __lin_cnt;
 sav_fnam = __cur_fnam;
 __cur_fnam = sdf_fnam; 
 __lin_cnt = 1;
 __pathsep = DFLT_SEP_CHAR;

 /* default is 1 ns - stored as negative so 9 is 10**-9 */
 __sdf_timescale = 9;
 /* need module to pass to real to ticks conversion routine */
 /* sdf is like dummy module with possibly different time scale */ 
 if (__des_timeprec == __sdf_timescale)
  { __sdf_nd_tscale = FALSE; __sdf_ts_units = 0; }
 else
  {
   __sdf_nd_tscale = TRUE;
   __sdf_ts_units = (int32) __des_timeprec - __sdf_timescale;
  }

 /* notice extra spaces insure no conflict with escaped ID */
 strcpy(__sdf_star_val, " * ");

 /* read the file and build internal sdf d.s. */
 rd_sdf_file(__sdf_s);
 __my_fclose(__sdf_s);
 __lin_cnt = sav_lin_cnt;
 __cur_fnam = sav_fnam;
 /* free all sdf values - no trace should be left after here except maybe */
 /* changed delays */ 
 free_sdf_hdrvals();
}

/*
 * free the sdf current values (free header strings)
 */
static void free_sdf_hdrvals(void)
{
 int32 slen;

 if (__sdf_delp != NULL)
  {
   /* number of delays is maximum possible */
   __my_free(__sdf_delp->da,
    SDF_MTMDNUM*SDF_PULDNUM*SDF_MAXDELS*sizeof(struct t_vpi_time)); 
   __my_free(__sdf_delp, sizeof(struct t_vpi_delay));
  }
 if (__sdf_delp2 != NULL)
  {
   /* number of delays is maximum possible */
   __my_free(__sdf_delp2->da,
    SDF_MTMDNUM*SDF_PULDNUM*SDF_MAXDELS*sizeof(struct t_vpi_time)); 
   __my_free(__sdf_delp2, sizeof(struct t_vpi_delay));
  }
 if (__sdf_version != __sdf_none_str) 
  {
   slen = strlen(__sdf_version) + 1;
   __my_free(__sdf_version, slen); 
   __sdf_version = NULL;
  }
 if (__sdf_design != __sdf_none_str) 
  {
   slen = strlen(__sdf_design) + 1;
   __my_free(__sdf_design, slen); 
   __sdf_design = NULL;
  }
 if (__sdf_date != __sdf_none_str) 
  {
   slen = strlen(__sdf_date) + 1;
   __my_free(__sdf_date, slen); 
   __sdf_date = NULL;
  }
 if (__sdf_vendor != __sdf_none_str) 
  {
   slen = strlen(__sdf_vendor) + 1;
   __my_free(__sdf_vendor, slen); 
   __sdf_vendor = NULL;
  }
 if (__sdf_program != __sdf_none_str) 
  {
   slen = strlen(__sdf_program) + 1;
   __my_free(__sdf_program, slen); 
   __sdf_program = NULL;
  }
 if (__sdf_progversion != __sdf_none_str) 
  {
   slen = strlen(__sdf_progversion) + 1;
   __my_free(__sdf_progversion, slen); 
   __sdf_progversion = NULL;
  }
 if (__sdf_process != __sdf_none_str) 
  {
   slen = strlen(__sdf_process) + 1;
   __my_free(__sdf_process, slen); 
   __sdf_process = NULL;
  }
}

/*
 * get the scope context name in which annotation takes place
 */
static char *get_sdfcntxtnam(char *cntxtnam, struct itree_t *cntxt_itp)
{
 if (cntxt_itp == NULL) strcpy(cntxtnam, "**design**");  
 else __msg2_blditree(cntxtnam, cntxt_itp);
 return(cntxtnam);
}

/*
 * initialize a vpi delay record
 */
static void init_vpi_del(struct t_vpi_delay *vdp, int32 ndels)
{
 int32 i;

 vdp->no_of_delays = 0;
 /* only type supported by SDF */
 vdp->time_type = vpiScaledRealTime;
 vdp->mtm_flag = FALSE; 
 vdp->pulsere_flag = FALSE;
 vdp->append_flag = FALSE;
 for (i = 0; i < ndels; i++)
  {
   vdp->da[i].type = vpiSimTime; 
   vdp->da[i].high = 0;
   vdp->da[i].low = 0;
  }
}

/*
 * SDF FORM INPUT ROUTINES
 */

/*
 * read and process (set delays) for an sdf standard file 
 *
 * although lower level routines attempt to resync - here give up on err 
 * at least one cell requered so do not need to catch errors here
 */
static void rd_sdf_file(FILE *f)
{
 struct t_vpi_time *vtp = &(__sdf_delp->da[0]);

 get_sdftok(f);
 if (__toktyp != LPAR)
  {
bad_file:
   __pv_ferr(1370,
    "initial (DELAYFILE missing (probably not SDF file) - %s read",
    prt_sdftok());
   return;
  }
 get_sdftok(f);
 if (__toktyp != SDF_DELAYFILE) goto bad_file;

 /* sdf version required rest optional - but must be inorder */
 get_sdftok(f);
 if (__toktyp != LPAR)
  {
bad_vershdr:
   __pv_ferr(1349, "required (SDFVERSION header missing - %s read",
    prt_sdftok());
   return;
  }
 get_sdftok(f);
 if (__toktyp != SDF_VERSION) goto bad_vershdr;
 /* mallocs string if nil not returned and reads ending ) */
 if (!rd_sdf_strval(f)) return;
 __sdf_version = __pv_stralloc(__sdf_work_str);
 if (strchr(__sdf_version, '3') == NULL)
  {
   __finform(460,
   "(SDFVERSION %s) unexpected - should be 3.x - but if no errors still works", 
    __sdf_version);
  }

 /* know there will be one - maybe just cell */ 
 /* also know if present will be in order */
 if (!rd2_sdf_formtyp(f)) return;

 if (__toktyp == SDF_DESIGN)
  {
   if (!rd_sdf_strval(f)) return;
   __sdf_design = __pv_stralloc(__sdf_work_str);
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp == SDF_DATE) 
  {
   if (!rd_sdf_strval(f)) return;
   __sdf_date = __pv_stralloc(__sdf_work_str);
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp == SDF_VENDOR) 
  {
   if (!rd_sdf_strval(f)) return;
   __sdf_vendor = __pv_stralloc(__sdf_work_str);
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp ==  SDF_PROGRAM)
  {
   if (!rd_sdf_strval(f)) return;
   __sdf_program = __pv_stralloc(__sdf_work_str);
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp == SDF_VERSION)
  {
   if (!rd_sdf_strval(f)) return;
   __sdf_progversion = __pv_stralloc(__sdf_work_str);
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp ==  SDF_DIVIDER)
  {
   if (!rd_sdf_sepchar(f, &__pathsep)) return;
   if (__pathsep == '/')
    {
     __pv_fwarn(675,
   "(DIVIDER '/' unexpected - Verilog uses '.' separator so SDF path matching uses '.'");
    }
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp == SDF_VOLTAGE)
  { 
   /* form is (VOLTAGE min:typ:max) - no () or list - one value ok */
   get_sdftok(f);

   /* on T, reads ending ) - reads value too */
   if (!rd_rtriple(f, vtp)) return;
   if (vtp->type == vpiSuppressTime)
    {
     __pv_fwarn(662, "(VOLTAGE value missing in rtriple field \"%s\"",
      mtm_sel_tonam(__xs, __sdf_mintypmax_sel));
    }
   else __sdf_voltage = vtp->real;
   /* ) read - this reads either form that must be present */
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp == SDF_PROCESS)
  { 
   get_sdftok(f);
   /* empty (PROCESS) now legal */
   if (__toktyp == RPAR) goto get_process_nxtform;
   /* SJM 03/20/00 - for SDF all tokens and strings limited to id len */
   if (__toktyp == LITSTR) strcpy(__sdf_work_str, __token);
   else
    { 
     __pv_ferr(1320,
      "(PROCESS right parenthesis or string value expected - %s read",
      prt_sdftok());
     return;
    }
   get_sdftok(f);
   if (__toktyp != RPAR)
    {
     __pv_ferr(1322, "(PROCESS string value not followed by ) - %s read",
      prt_sdftok());
     return;
    }
   __sdf_process = __pv_stralloc(__sdf_work_str);

get_process_nxtform:
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp == SDF_TEMPERATURE)
  { 
   /* form is (TEMPERATURE min:typ:max) - no () or list - one value ok */
   get_sdftok(f);
   /* on T, reads ending ) - reads value too */
   if (!rd_rtriple(f, vtp)) return;
   if (vtp->type == vpiSuppressTime)
    {
     __pv_fwarn(662, "(TEMPERATURE value missing in rtriple field \"%s\"",
      mtm_sel_tonam(__xs, __sdf_mintypmax_sel));
    }
   else __sdf_temp = vtp->real;
   if (!rd2_sdf_formtyp(f)) return;
  }
 if (__toktyp == SDF_TIMESCALE)
  {
   if (!rd_sdf_timescaleval(f, &__sdf_timescale)) return;

   if (__sdf_timescale > __des_timeprec)
    {
     __pv_fwarn(660,
      "SDF TIMESCALE unit %s less than minimum unit %s in design - round to 0 probable",
     __to_timunitnam(__xs, (word32) __sdf_timescale),
     __to_timunitnam(__xs2, __des_timeprec));
     return;
    }
   if (__sdf_timescale == __des_timeprec)
    { __sdf_nd_tscale = FALSE; __sdf_ts_units = 0; }
   else
    {
     __sdf_nd_tscale = TRUE;
     __sdf_ts_units = (int32) __des_timeprec - __sdf_timescale;
    }
   if (!rd2_sdf_formtyp(f)) return;
  }

 /* multiple cells possible at least one required */
 /* returns F on first file structure error - resync not possible */
 /* if annotation errors only, returns T but does nothing */
 if (!rdset_sdf_cells(f)) return;

 /* will not have read eof since end with ) of cells */ 
 get_sdftok(f);
 if (__toktyp != TEOF)
  __pv_fwarn(661,
   "tokens after end of SDF DELAYFILE ignored - %s first ignored",
   prt_sdftok());
}

/*
 * convert current runs mtm selector to a name
 */
static char *mtm_sel_tonam(char *s, int32 mtmtyp)
{
 if (mtmtyp == DEL_MIN) strcpy(s, "min");
 else if (mtmtyp == DEL_TYP) strcpy(s, "typ");
 else if (mtmtyp == DEL_MAX) strcpy(s, "max");
 else strcpy(s, "-unknown-");
 return(s);
}

/*
 * read the separator char form ending value
 * here always returns some char - if error sets to default
 * form and value can be missing
 */
static int32 rd_sdf_sepchar(FILE *f, char *sep)
{
 int32 c;

 /* this is tricky cannot use get sdf token - skips to any non white space */
 do { c = getc(f); } while(vis_white_(c)); 

 get_sdftok(f);
 if (__toktyp != RPAR) { formend_err("DIVIDER"); return(FALSE); }
 
 /* cannot be part of id or escape */
 if (c != '.' && c != '/')
  {
   __pv_ferr(1316, "DIVIDER form separator character %c illegal", c);
   c = DFLT_SEP_CHAR;
  }
 *sep = c;
 return(TRUE);
}

/*
 * read a timescale form ending value (TIMESCALE read
 * set tunits which is -1 to -15 normal timescale units value
 */
static int32 rd_sdf_timescaleval(FILE *f, int32 *tunits)
{
 int32 mult, mval;
 word32 t1;
 char *chp;

 get_sdftok(f);
 if (__toktyp == RPAR) { *tunits = 9; return(TRUE); }
 /* 1ns form - will still return just number */ 
 if (__toktyp == REALNUM) mval = (int32) __itok_realval;
 else if (__toktyp == NUMBER) mval = (int32) __sdf_tokval;
 else 
  {
   __pv_ferr(1318,
    "TIMESCALE form unit value or ) (omitted form) missing - %s read",
    prt_sdftok());
   return(FALSE);
  }
 if (mval == 1) mult = 0;
 else if (mval == 10) mult = 1;
 else if (mval == 100) mult = 2;
 else
  {
   __pv_ferr(1317, "(TIMESCALE form timescale units %d illegal",
    __sdf_tokval);
   mult = -1; 
  }
 get_sdftok(f);
 if (__toktyp != ID)
  { 
   __pv_ferr(1373, "(TIMESCALE form scale suffix expected - %s read",
    prt_sdftok());
   return(FALSE);
  } 
 if ((chp = __get_tmult(__token, &t1)) == NULL || *chp != '\0') 
  {
bad_timfmt:
   __pv_ferr(1319, "(TIMESCALE form scale suffix %s illegal", __token);
   mult = -1;
  }
 if (mult == -1) *tunits = 9; 
 else
  {
   if (t1 == 0 && mult != 0) goto bad_timfmt;
   /* 10 subtracts 1 and 100 subtracts 2 - i.e ns (9 - 2 (for 10) = 7 */
   *tunits = (int32) t1 - mult;
  }
 get_sdftok(f);
 if (__toktyp != RPAR) { formend_err("TIMESCALE"); return(FALSE); }
 return(TRUE);
}

/*
 * ROUTINES TO READ CELL FORMS 
 */

/*
 * read every sdf cell entry and set delays for it (at least one required)
 *
 * returns F on error 
 * upon entry will have read CELL keyword of form
 * on exit has read ending ) but not eof
 * instances qualified names - for paths must select exact instance
 */
static int32 rdset_sdf_cells(FILE *f)
{
 int32 all_insts, i1, i2;
 struct itree_t *itp, *top_itp;
 struct expr_t *glbndp;
 struct mod_t *ctmdp;
 struct sy_t *syp, *syp2;
 char ctnam[IDLEN], inam[IDLEN], ginam[IDLEN], s1[RECLEN];

 /* expects (CELL to have been read */
 for (;;)  
  {
   if (__toktyp != SDF_CELL)
    {
     __pv_ferr(1323, "(CELL form expected - (%s read", prt_sdftok());
     return(FALSE);
    }
   if (!rd2_sdf_formtyp(f)) return(FALSE);
   if (__toktyp != SDF_CELLTYPE)
    {
     __pv_ferr(1324, "(CELLTYPE form expected - (%s read", prt_sdftok());
     return(FALSE);
    }
   /* this reads ending ) */
   if (!rd_sdf_strval(f)) return(FALSE);
   /* this can not be qualified name or contain selects */
   if (!chkcnv_sdfid(ctnam, &i1, &i2, __sdf_work_str, FALSE) || i1 != -1)
    {
     __pv_ferr(1330, "(CELLTYPE Verilog type name %s illegal format",
      __sdf_work_str);
     return(FALSE);
    }

   /* read instance form - path can be concatenation of instance forms */  
   if (!rd2_sdf_formtyp(f)) return(FALSE); 
   if (__toktyp != SDF_INSTANCE)
    {
     __pv_ferr(1324, "(INSTANCE form expected - (%s read", prt_sdftok());
     return(FALSE);
    }
   get_sdftok(f);
   all_insts = FALSE;
   i1 = i2 = -1;
   itp = NULL;
   strcpy(inam, "");
   strcpy(ginam, ""); 
   if (__toktyp == ID)
    {
     if (__id_qualpath)
      {
       /* because this is inst. non variable name, last component select ok */
       if (!chkcnv_sdfpath(inam, &i1, &i2, __token, TRUE) || i1 != i2)
        {
         __pv_ferr(1325,
          "(INSTANCE hierarchical instance name %s illegal Verilog path name",
          __token);
         return(FALSE);
        }
      }
     else if (!chkcnv_sdfid(inam, &i1, &i2, __token, TRUE) || i1 != i2)
      {
       __pv_ferr(1325, "(INSTANCE form name of instance %s illegal",
        __token);
      }
    }
   else if (__toktyp == TIMES)
    {
     /* inam empty string here */
     all_insts = TRUE;
     get_sdftok(f);
     if (__toktyp != ID) goto chk_rpar;
     if (__id_qualpath)
      {
       __pv_ferr(1245,
        "(INSTANCE * [gate instance name]) qualified gate name path %s illegal",
        __token);
       return(FALSE);
      }
     /* gate instance name here can have index */
     if (!chkcnv_sdfid(ginam, &i1, &i2, __token, TRUE) || i1 != i2)
      {
       __pv_ferr(1245, "(INSTANCE * [gate name]) name of gate %s illegal",
        __token);
       return(FALSE);
      }
     /* for simple gate name with index - can not add index as suffix */
    }
   else if (__toktyp == RPAR)
    {
     /* empty cell name case - means in context (or first top if none) */
     /* leave inam as "" - also know ginam "" */
     goto chk_rpar;
    }
   else 
    {
     __pv_ferr(1328, "(INSTANCE form path, primitive or * expected - %s read", 
      prt_sdftok());
     return(FALSE);
    }
   get_sdftok(f);
chk_rpar:
   /* either gate instance name (non path) or instance path but not both set */
   if (__toktyp != RPAR) { formend_err("INSTANCE"); return(FALSE); }
   get_sdftok(f);
   /* this reads either timing spec keyword or ) */
   if (!rd_sdf_formtyp(f)) return(FALSE); 

   /* this can be gate type name or module type name for (* [gate inst]) */
   /* but never xmr or gate/instance select */
   if ((syp =__get_sym(ctnam, __modsyms)) == NULL)
    {
     __pv_ferr(1389,
      "(CELL form (CELLTYPE \"%s\" is not a module type or primitive name",
      ctnam);
     /* cell type unknown, unable to process instance */
skip_cell:
     if (!sdf_skip_form(f)) return(FALSE);
     goto nxt_cell;
    }  
   /* case 1: primitive gate or udp - must be (DEVICE delay */ 
   if (syp->sytyp == SYM_PRIM || syp->sytyp == SYM_UDP)
    {
     if (all_insts)
      { 
       __pv_ferr(1397,
        "SDF DEVICE primitive wildcard form illegal - setting delay for all meaningless");
       goto skip_cell;
      } 
     /* if non * [gate inst] form, syp is (CELLTYPE, inam is gate inst path */
     /* for array of gates i1 is gate index and inam is base name */
     if (!rdset_prim_delay(f, syp, i1, inam, (struct sy_t *) NULL))
      goto skip_cell;
     goto nxt_cell;
    }

   /* DBG remove -- */
   if (syp->sytyp != SYM_M) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* case 1a: all instances of primitive (gate) in type */ 
   if (strcmp(ginam, "") != 0)
    {
     /* ginam only set if all insts * form */
     /* DBG remove -- */
     if (!all_insts) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* look up gate instance name - must be gate in type */
     /* can be base name of gate instance array */
     if ((syp2 = __get_sym(ginam, syp->el.emdp->msymtab)) == NULL
      || (syp2->sytyp != SYM_PRIM && syp2->sytyp != SYM_UDP))
      {
       __pv_ferr(1360,
        "(CELLTYPE * [gate]) form primitive %s not defined in type %s", 
        ginam, syp->synam);
       goto skip_cell;
      }
     /* * [gate inst] form, syp is (CELLTYPE mod, inam nil, syp2 gate inst */
     /* for array of gates syp2 is base element and i1 is index */ 
     if (!rdset_prim_delay(f, syp, i1, inam, syp2)) goto skip_cell;
     goto nxt_cell;
    }
   ctmdp = syp->el.emdp;

   if (all_insts) goto rd_timspec;

   /* case 2 - one specific named (maybe "" for in context) instance */
   /* need to fixup instance name by adding index if any back on */
   if (i1 != -1)
    {
     char s2[IDLEN];

     sprintf(s2, "%s[%d]", inam, i1);
     strcpy(inam, s2);
    }
   /* empty iname form - use first top or context */
   /* case 2a - no instance - in context or first top level */
   if (strcmp(inam, "") == 0)
    {
     if (__sdf_cntxt_itp == NULL)
      { 
       itp = __it_roots[0];
       if (__numtopm != 1)
        {
         __pv_fwarn(648,
          "(INSTANCE ) form with no context ambiguous because more than one top level module - using first (%s)",
          itp->itip->imsym->synam);
        }
      }
     else itp = __sdf_cntxt_itp;
     goto rd_timspec;
    }
   /* case 2b - have instance path */
   /* need to use interactive global context here */
   __push_wrkitstk(__sdf_mdp, 0);
   if ((glbndp = __glbnam_to_expr(inam)) == NULL)
    {
     __pop_wrkitstk();
     goto skip_cell;
    }
   /* case 2b-1 - no context */
   if (__sdf_cntxt_itp == NULL)
    {
     /* no context first try rooted */
     if ((itp = get_sdfdownrel_itp(glbndp, NULL, NULL, s1)) != NULL)
      { 
       __free_xtree(glbndp);
       __pop_wrkitstk();
       goto rd_timspec;
      }

     /* then try in first top level */ 
     top_itp = __it_roots[0];
     if (__numtopm != 1)
      {
       __pv_fwarn(648,
        "(INSTANCE form non rooted instance path %s ambiguous because more than one top level module - using first (%s)",
        inam, top_itp->itip->imsym->synam);
      }
     itp = get_sdfdownrel_itp(glbndp, top_itp, NULL, s1);
     /* done with glb ndp thru this code path */
     __free_xtree(glbndp);
     __pop_wrkitstk();
  
     if (itp == NULL)
      { 
       __pv_ferr(1378, "(CELL instance %s not found as rooted path or in first top level module: %s",
        inam, s1);
       goto skip_cell;
      }
     goto rd_timspec; 
    }

   /* case 2b-2 - must be in context annotation context instance */ 
   itp = get_sdfdownrel_itp(glbndp, __sdf_cntxt_itp, NULL, s1);
   /* done with glb ndp thru this code path */

   /* if not in sdf context - see if name is rooted */
   if (itp == NULL)
    {
     /* SJM 01/14/00 - need to search for rooted cell instance */ 
     /* previously only worked if no context command option was used */
     /* not search first in context for cell (not device) then rooted always */
     if ((itp = get_sdfdownrel_itp(glbndp, NULL, NULL, s1)) != NULL)
      { 
       __free_xtree(glbndp);
       __pop_wrkitstk();
       goto rd_timspec;
      }
     __pv_ferr(1378, "(CELL instance %s undefined rooted or in context %s: %s",
      inam, get_sdfcntxtnam(__xs, __sdf_cntxt_itp), s1);
    }
   __free_xtree(glbndp);
   __pop_wrkitstk();

rd_timspec:
   /* read/set 1 or more timing specs - if design context, then '*' all */ 
   if (!rdset_timing_spec(f, itp, ctmdp)) return(FALSE);

nxt_cell:
   /* know cell ending ) read to get here */
   /* see if more cells */
   get_sdftok(f);
   if (!rd_sdf_formtyp(f)) return(FALSE); 
   if (__toktyp == RPAR) break;
  }
 return(TRUE);
}

/*
 * find sdf path instance (always downward relative) given global expr
 *
 * possibly no context so name must be rooted 
 * last component may be non scope variable end (found and ignored here)
 * only for use during SDF annotation - caller must emit error on nil return
 *
 * if tailsyp nil, calling from known instance xmr where last must be
 * instance or error, else last must be non instance and tail name copied
 * into passed string variable
 *
 * called after fixup so know m giap aux fields set
 */
static struct itree_t *get_sdfdownrel_itp(struct expr_t *glbndp,
 struct itree_t *cntxt_itp, struct sy_t **tailsyp, char *errmsg) 
{
 int32 ii;
 byte *bp1, *bp2;
 struct expr_t *gcmp_ndp;
 struct itree_t *itp;
 struct mod_t *mdp;
 struct sy_t *isyp, *arr_isyp;
 struct inst_t *ip;
 char *chp, s1[RECLEN];

 gcmp_ndp = glbndp->ru.x;
 /* here context is annotate scope not cell context */
 /* for down rel. path in cell context and '*' form, pass first of type */
 if (cntxt_itp == NULL)
  {
   /* know top level rooted first component never indexed */
   chp = __to_glbcmp_nam(gcmp_ndp);
   if ((ii = __ip_indsrch(chp)) == -1)
    {
     strcpy(errmsg, "root undefined");
     return(NULL);
    }
   itp = __it_roots[ii];
   gcmp_ndp = gcmp_ndp->ru.x;
  }
 else itp = cntxt_itp;

 /* this is for getting type, on inst '*' form */ 
 for (;gcmp_ndp != NULL; gcmp_ndp = gcmp_ndp->ru.x)
  {
   mdp = itp->itip->imsym->el.emdp;
   chp = __to_glbcmp_nam(gcmp_ndp);
   /* look up component in module symbol table */
   if ((isyp = __get_sym(chp, mdp->msymtab)) == NULL)
    {
     sprintf(errmsg, "component %s undefined in %s", chp, mdp->msym->synam);
     return(NULL);
    }

   if (isyp->sytyp != SYM_I)
    {
     if (tailsyp == NULL)
      {
       strcpy(errmsg, "no non-scope (probably gate) ending symbol");
       return(NULL);
      }
     if (gcmp_ndp->ru.x != NULL)
      {
       strcpy(errmsg, "non-scope symbol inside path");
       return(NULL);
      }
     *tailsyp = isyp;
     return(itp);
    }

   ip = isyp->el.eip; 
   if (ip->i_giap == NULL)
    {
     /* case 1: not array of insts */
     /* must be ID component */
     if (gcmp_ndp->lu.x->optyp != XMRID)
      {
       sprintf(errmsg, "select of non-instance array %s", ip->isym->synam);
       return(NULL);
      }
    }
   else
    {
     /* DBG remove -- */
     if (!isyp->sy_giabase) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* must be inst select component */
     if (gcmp_ndp->lu.x->optyp != LSB)
      {
       sprintf(errmsg, "select of instance array %s required", isyp->synam);
       return(NULL);
      }

     /* case 2: array of insts */
     /* notice passing the select xmr node, not the comma node */
     __bld_glbcmp_ginam(s1, gcmp_ndp->lu.x);
     
     if ((arr_isyp = __get_sym(s1, mdp->msymtab)) == NULL)
      {
       sprintf(errmsg, "array of instances component %s undefined in %s",
        s1, mdp->msym->synam);
       return(NULL);
      }
     /* both prongs of if set ip */
     ip = arr_isyp->el.eip;
     /* DBG remove -- */
     if (ip->i_giap == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
    }
   bp1 = (byte *) ip;
   bp2 = (byte *) mdp->minsts;
   ii = (bp1 - bp2)/sizeof(struct inst_t);
   itp = &(itp->in_its[ii]);
  } 
 /* instance path expected but has name (gate?) at end */
 if (tailsyp != NULL)
  {
   strcpy(errmsg, "path end must be instance"); 
   return(NULL);
  }
 return(itp);
}

/*
 * PRIMITIVE (GATE) DELAY FORM READING AND SETTING ROUTINES
 */

/*
 * read set a primitive delay - must be (DEVICE form or error
 *
 * itp = nil for all insts, where tsyp is mod type and gisyp is gate inst
 * when itp not nil tsyp set to module type symbol
 *
 * inam may end in gate instance where for array of gates it is base with
 * index i1 which must not be -1
 *
 * since there is always one in tsyp gate instance, ctgp always set to it
 * for (instance * [gate inst]) (CELLTYPE is tsyp, and gate inst is ctgp
 *
 * (DEVICE that is abbreviation for all paths handled elsewhere
 * know DEVICE keyword or ) read
 */
static int32 rdset_prim_delay(FILE *f, struct sy_t *tsyp, int32 i1, char *inam,
 struct sy_t *gisyp)
{
 int32 first_time, gi;
 char *chp;
 struct gia_aux_t *giap;
 struct sy_t *gsyp, *dumsyp;
 struct gate_t *ctgp;
 struct mod_t *mdp;
 struct expr_t *glbndp;
 struct itree_t *itp;
 char ctgnam[IDLEN], s1[RECLEN];
 
 /* * form requires instance name of gate in all instance of type */
 /* already have the instance symbol in gisyp */
 if (gisyp != NULL) { itp = NULL; ctgp = gisyp->el.egp; }
 else
  {
   /* DBG remove -- */
   if (strcmp(inam, "") == 0) __arg_terr(__FILE__, __LINE__);
   /* --- */
   /* need to use interactive global context here */
   __push_wrkitstk(__sdf_mdp, 0);
   if ((glbndp = __glbnam_to_expr(inam)) == NULL)
    {
     __pop_wrkitstk();
     return(FALSE);
    }

   /* case 1 - gate instance name has only one component */
   if (glbndp->ru.x->ru.x == NULL)
    {
     /* DBG remove --- */
     if (glbndp->ru.x->lu.x->optyp == LSB) __misc_terr(__FILE__, __LINE__);
     /* --- */
     chp = __to_glbcmp_nam(glbndp->ru.x);
     strcpy(ctgnam, chp);
     /* done with glb ndp thru this code path */
     __free_xtree(glbndp);
     __pop_itstk();

     /* for design scope (one above any top level module), path needed */ 
     if (__sdf_cntxt_itp == NULL)
      {
       __pv_ferr(1392,
        "primitive non hierarchical instance %s illegal because SDF context is entire design",  
        ctgnam);
       return(FALSE);
      }
     else itp = __sdf_cntxt_itp;
    }
   else
    { 
     /* remove the tail that is primitive (i.e. gate) inst and set itp */
     itp = get_sdfdownrel_itp(glbndp, __sdf_cntxt_itp, &dumsyp, s1);
     /* done with glb ndp thru this code path */
     __free_xtree(glbndp);
     __pop_itstk();

     if (itp == NULL)
      {
       __pv_ferr(1351, 
        "for primitive delay, (CELL instance %s undefined in context %s: %s",
        inam, get_sdfcntxtnam(__xs, __sdf_cntxt_itp), s1);
       return(FALSE);
      }

     /* DBG remove --- */
     if (dumsyp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* for array of gates this is base name with i1 (non -1) index */  
     strcpy(ctgnam, dumsyp->synam);
    }
   /* if type is primitive, look up inst name in module's symbol table */
   tsyp = itp->itip->imsym;
   mdp = tsyp->el.emdp;
   /* for non * qualified path the one gate gname in mdp */
   if ((gsyp =__get_sym(ctgnam, mdp->msymtab)) == NULL)
    {
     __pv_ferr(1351,
      "%s primitive instance %s not found in module %s (from instance path %s)",
      tsyp->synam, ctgnam, mdp->msym->synam, inam); 
     return(FALSE); 
    }
   ctgp = gsyp->el.egp;
   if (ctgp->g_giap != NULL)
    {
     /* DBG remove -- */
     if (!gsyp->sy_giabase) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* must be array of gates select component */
     if (i1 == -1)
      {
       __pv_ferr(1393,
        "%s primitive instance %s is array of gates - required select missing",
        tsyp->synam, gsyp->synam); 
       return(FALSE);
      }

     /* gsyp is the original array of gates name before expansion */
     sprintf(s1, "%s[%d]", gsyp->synam, i1);
     if ((gsyp =__get_sym(s1, mdp->msymtab)) == NULL)
      {
       __pv_ferr(1351,
        "%s primitive array of gates instance %s not found in module %s (from instance path %s)",
        tsyp->synam, s1, mdp->msym->synam, inam); 
       return(FALSE); 
      }
     ctgp = gsyp->el.egp;

//SJM 04-21-10 - REMOVEME - think can't happen any more     
     /* since each split gate points to a gia aux record, can use any */
     giap = ctgp->g_giap;
     if (giap->gia1 > giap->gia2)
      {
       if (i1 > giap->gia1 || i1 < giap->gia2)
        {
bad_sel:
         __pv_ferr(1501,
          "%s primitive array of gates instance %s index %d out of range [%d:%d]",
           tsyp->synam, gsyp->synam, i1, giap->gia1, giap->gia2);
         return(FALSE);
        }
       else gi = giap->gia_bi + (giap->gia1 - i1);
      }
     else
      {
       if (i1 < giap->gia1 || i1 > giap->gia2) goto bad_sel;
       gi = giap->gia_bi + (i1 - giap->gia1);
      }
    }
   else
    {
     if (i1 != -1)
      {
       __pv_ferr(1502,
        "%s primitive instance %s select of non arrayed gate illegal",
        tsyp->synam, gsyp->synam); 
       return(FALSE);
      }
    }
   /* know ctgp set to gate (maybe bit of array of gates here) */
  }
 /* read and set the device delay */
 /* cell can contain any number (at least one) but only (DEVICE */ 
 for (first_time = TRUE;;)
  {
   if (__toktyp == RPAR)
    {
     if (first_time)
      {
       __finform(477,
        "(CELL %s primitive instance del_spec empty - no delays annotated",
        tsyp->synam);
      }
     goto done;
    }
   if (__toktyp != SDF_DELAY)
    {
     __pv_ferr(1336, "only (DELAY form allowed for primitive delay - (%s read",
      prt_sdftok());
     return(FALSE);
    }
   if (!prim_rdset_device_del(f, itp, tsyp, ctgp)) return(FALSE);
   first_time = FALSE;
   get_sdftok(f);
   if (!rd_sdf_formtyp(f)) return(FALSE);
  }
done:
 return(TRUE);
}

/*
 * read absolute or increment primitive gate form
 *
 * for instance form ctgp is gate instance in itp
 * for (CELL (CELLTYPE "RSLATCH") (INSTANCE * bufa) (DEVICE 3 4))
 * itp=nil, 
 */
static int32 prim_rdset_device_del(FILE *f, struct itree_t *itp,
 struct sy_t *tsyp, struct gate_t *ctgp)
{
 int32 first_time, first2_time, ndels, lcnt, sav_lcnt;
 char formnam[RECLEN];

 for (first_time = TRUE;;) 
  {
   get_sdftok(f);
   if (!rd_sdf_formtyp(f)) return(FALSE);
   if (__toktyp == RPAR)
    {
     if (first_time)
      {
       __pv_ferr(1333,
        "primitive (DELAY form empty - at least one (ABOSLUTE or (INCREMENT required");
       return(FALSE);
      }
     break;
    }
   if (__toktyp != SDF_ABSOLUTE && __toktyp != SDF_INCREMENT)
    {
     __pv_ferr(1336,
      "primitive instance (ABSOLUTE or (INCREMENT expected - (%s read",
      prt_sdftok());
     return(FALSE);
    } 
   first_time = FALSE;
   strcpy(formnam, __token);
   for (first2_time = TRUE;;) 
    {
     get_sdftok(f);
     if (!rd_sdf_formtyp(f)) return(FALSE);
     if (__toktyp == RPAR)
      {
       if (first2_time)
        {
         __pv_ferr(1337,
          "(%s form empty - at least one primitive instance (DEVICE form required",
          formnam);
         return(FALSE);
        }
       break;
      } 
     lcnt = __lin_cnt;
     if (__toktyp != SDF_DEVICE)
      {
       __pv_ferr(1336,
        "for primitive instance only (DEVICE form allowed - (%s read",
        prt_sdftok());
       return(FALSE);
      }
     first2_time = FALSE;
     get_sdftok(f);
     if (__toktyp != LPAR) { dellst_err(formnam, "DEVICE"); return(FALSE); }
     get_sdftok(f);
     if ((ndels = rd_sdf_dellst(f, "DEVICE")) == -1) return(FALSE);
     /* except for next 2 fields all t_vpi_delay fields fixed in SDF */
     __sdf_delp->no_of_delays = ndels; 
     if (strcmp(formnam, "INCREMENT") == 0) __sdf_delp->append_flag = TRUE;
     else __sdf_delp->append_flag = FALSE;

     /* need to be able to emit f errors for first token in form */
     sav_lcnt = __lin_cnt; 
     __lin_cnt = lcnt;  
     set_device_del(itp, ctgp, tsyp);
     __lin_cnt = sav_lcnt;
    }
  }
 return(TRUE);
}

/*
 * set device primitive delays
 *
 * uses global sdf delp
 * wildcard form is extension (not in standard), (i * [gate inst]) 
 * normal * wild card form does not make sense because need all gate
 * instances in type
 *
 * for both forms tsyp is symbol of instance type - ctgp is gate inst.
 */
static void set_device_del(struct itree_t *itp, struct gate_t *ctgp,
 struct sy_t *tsyp)
{
 int32 ndels, dfix;
 struct gate_t ogat, ngat;
 struct mod_t *mdp;
 char s1[IDLEN];

 /* even for all instances of one gate instance, only check once */
 ndels = __sdf_delp->no_of_delays;
 mdp = tsyp->el.emdp;
 dfix = 4;
 if (ctgp->g_class == GC_UDP || ctgp->g_class == GC_LOGIC)
  {
   if (ndels > 2)
    {
     __pv_ferr(1398,
      "SDF (CELLTYPE %s (DEVICE primitive %s has %d delay values - must be 1 or 2",
      mdp->msym->synam, ctgp->gmsym->synam, ndels);
     return; 
    }
   dfix = 2;
  }
 else
  {
   /* 3 delay form is bufif or mos type gate that has to z delay */
   if (ndels > 3)
    {
     __pv_ferr(1398,
      "SDF (CELLTYPE %s (DEVICE primitive %s has %d delay values - must be 1, 2 or 3",
      mdp->msym->synam, ctgp->gmsym->synam, ndels);
     return;
    }  
   dfix = 3;
  }

 /* this is needed because if no insts in SDF scope context no #0 del add */ 
 if (itp == NULL)
  {
   if (find_1under_itp(mdp) == NULL)
    {
     __pv_fwarn(665,
      "delays not changed for (DEVICE gate %s because no instance of type %s in context", 
      ctgp->gmsym->synam, mdp->msym->synam);
     return;
    }
  }

 sprintf(s1, "(DEVICE %s %s in %s", ctgp->gmsym->synam, ctgp->gsym->synam,
  mdp->msym->synam);  
 /* already checked for adding delay in non load run state */
 if (ctgp->g_delrep == DT_NONE)
  { if (!__add_gate_pnd0del(ctgp, mdp, s1)) return; } 

 ogat.g_du = ctgp->g_du;
 ogat.g_delrep = ctgp->g_delrep;
 if (itp == NULL)
  {
   /* this handles any needed delay freeing */
   if (!upd_sdf_perinst_del(&ogat, __sdf_delp, mdp, FALSE, FALSE,
    dfix, s1)) return;
  }
 else
  {
   /* build the new value, maybe using old to append to if append flag */
   /* uses itree loc. from hp if needed for append access */
   /* only allocate delay that needs to be freed if returns T */ 
   if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp, itp, FALSE, FALSE, s1))
    return;

   /* this must always recomputer toz (logic) and tox all because never */
   /* explicitly given */
   if (ngat.g_delrep == DT_4V)
    {
     if (dfix == 2) set_logic_gdel_tox_val(&(ngat));
     else if (dfix == 3) set_toz_gdel_tox_val(&(ngat));
     else __case_terr(__FILE__, __LINE__);
    }
   /* this handles freeing and realloc of delay union if needed */
   __chg_1inst_del(&ogat, itp, &ngat);
   __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
  }
 ctgp->g_du = ogat.g_du;  
 ctgp->g_delrep = ogat.g_delrep;
 if (__sdf_verbose) prep_sdfdev_verbmsg(ctgp, &ogat, itp, mdp);
}

/*
 * routine to set the toz delay for a 2 delay form (Verilog logic gate) 
 */
static void set_logic_gdel_tox_val(struct gate_t *gp)
{
 if (gp->g_du.d4v[0] < gp->g_du.d4v[1])
  {
   gp->g_du.d4v[2] = gp->g_du.d4v[0];
   gp->g_du.d4v[3] = gp->g_du.d4v[0];
  }
 else
  {
   gp->g_du.d4v[2] = gp->g_du.d4v[1];
   gp->g_du.d4v[3] = gp->g_du.d4v[1];
  }
}

/*
 * routine to set the toz delay for a 3 del form (Verilog bufif with to-z del)
 *
 * SJM 04/16/08 - think needs to follow Verilog LRM here and  use to-z
 * (index 2) delay in finding min - was not including to-z 3rd (ndx 2) val
 */
static void set_toz_gdel_tox_val(struct gate_t *gp)
{
 if (gp->g_du.d4v[0] < gp->g_du.d4v[1])
  {
   if (gp->g_du.d4v[0] < gp->g_du.d4v[2])
    gp->g_du.d4v[3] = gp->g_du.d4v[0];
   else gp->g_du.d4v[3] = gp->g_du.d4v[2];
  }
 else
  {
   if (gp->g_du.d4v[1] < gp->g_du.d4v[2])
    gp->g_du.d4v[3] = gp->g_du.d4v[1];
   else gp->g_du.d4v[3] = gp->g_du.d4v[2];
  }
}

/*
 * wrapper to prepare and call device sdf verbose tracing message
 */
static void prep_sdfdev_verbmsg(struct gate_t *gp, struct gate_t *ogp,
 struct itree_t *itp, struct mod_t *mdp)
{
 int32 ii;
 struct itree_t *itp2;
 char s1[RECLEN], s2[RECLEN];

 if (itp == NULL)
  {
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp2 = mdp->moditps[ii];
     __push_itstk(itp2);
     sprintf(s1, "%s(%s) from '*'", __msg2_blditree(s2, itp2),
      mdp->msym->synam);
     emit_sdfdev_verbmsg(gp, ogp, s1);
     __pop_itstk();
    }
  } 
 else
  {
   __push_itstk(itp);
   sprintf(s1, "%s(%s)", __msg2_blditree(s2, itp), mdp->msym->synam);
   emit_sdfdev_verbmsg(gp, ogp, s1);
   __pop_itstk();
  }
}

/*
 * emit sdf device verbose tracing message 
 */
static void emit_sdfdev_verbmsg(struct gate_t *gp, struct gate_t *ogp,
 char *celloc)
{
 char s1[RECLEN], s2[RECLEN];

 __cv_msg("  SDF **%s(%d): (DEVICE %s %s delay set to (%s) in %s at %s\n",
  __cur_fnam, __lin_cnt, gp->gmsym->synam, gp->gsym->synam,
  __bld_delay_str(s1, ogp->g_du, ogp->g_delrep), celloc,
  __bld_lineloc(s2, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt));
}

/*
 * ROUTINES TO READ AND TIMING TIMING SPEC FORMS 
 */

/*
 * read and set delay for one or more timing spec forms
 *
 * know first token read ([timing spec name] or )) and reads cell ending ) 
 */
static int32 rdset_timing_spec(FILE *f, struct itree_t *itp, struct mod_t *ctmdp)
{
 int32 first_time;

 /* DBG remove -- */
 if (ctmdp == NULL) __arg_terr(__FILE__, __LINE__);
 /* --- */ 

 /* cell can contain any number (at least one) timing_specs */ 
 for (first_time = TRUE;;)
  {
   switch (__toktyp) {
    case RPAR:
     if (first_time)
      {
       __finform(477, "(CELL instance %s missing timing specifications",
        get_sdfinam(__xs, itp, ctmdp));
      }
     goto done;
    case SDF_DELAY:
     if (!rdset_deltyps(f, itp, ctmdp)) return(FALSE);
     break;
    case SDF_TIMINGCHECK:
     if (!rdset_tchk_defs(f, itp, ctmdp)) return(FALSE);
     break;
    case SDF_TIMINGENV:
     /* for simulator these are just skipped */
     if (!rdskip_te_defs(f)) return(FALSE);
     break;
    case SDF_LABEL:
     if (!rdset_labels(f, itp, ctmdp)) return(FALSE);
     break;
    default:
     __pv_ferr(1353, "timing_spec form name expected - %s read", 
      prt_sdftok());
     return(FALSE);
   }
   first_time = FALSE;  
   get_sdftok(f);
   if (!rd_sdf_formtyp(f)) return(FALSE); 
  }
done:
 return(TRUE);
}

/*
 * get sdf cell instance name (may be * for all under) 
 */
static char *get_sdfinam(char *s, struct itree_t *itp, struct mod_t *ctmdp)
{
 char s1[RECLEN];

 if (itp == NULL) sprintf(s, "* (all instances of type %s under %s",
  ctmdp->msym->synam, get_sdfcntxtnam(s1, __sdf_cntxt_itp));
 else sprintf(s, "%s (type %s)", itp->itip->isym->synam, ctmdp->msym->synam); 
 return(s);
}

/*
 * read a delay timing spec form
 * know (DELAY read - can be multiple deltyp records
 * reads ending )
 */
static int32 rdset_deltyps(FILE *f, struct itree_t *itp, struct mod_t *ctmdp)
{
 int32 first_time, i11, i12, i21, i22, pptyp;
 char formnam[RECLEN], pnam1[IDLEN], pnam2[IDLEN];

 for (first_time = TRUE;;) 
  {
   get_sdftok(f);
   if (!rd_sdf_formtyp(f)) return(FALSE);
   if (__toktyp == RPAR)
    {
     if (first_time)
      {
       __pv_ferr(1333,
        "(DELAY form empty - at least one deltype form required");
       return(FALSE);
      }
     break;
    }
   first_time = FALSE;
   switch (__toktyp) {
    case SDF_PATHPULSE:
    case SDF_PATHPULSEPERCENT:
     pptyp = __toktyp;
     strcpy(formnam, __token);
     get_sdftok(f); 
     if (__toktyp == ID)
      {
       /* qualified port names now alwayhs use . separator */
       if (!rd_port(f, pnam1, &i11, &i12)) return(FALSE);
       if (!rd_port(f, pnam2, &i21, &i22)) return(FALSE);

       /* AIV 11/20/03 only need to be checked if pnams set */
       /* need to check but since syntax good just continue */
       port_qual_nam(pnam1, "(PATHPULSE port"); 
       port_qual_nam(pnam2, "(PATHPULSE port");
      }
     /* this reads ) ending form */
     if (rd_1or2_vals(f, formnam) == -1) return(FALSE); 

     /* SJM 03/13/04 - move into ID case above by AIV - why? */ 

     if (pptyp == SDF_PATHPULSE)
      { 
       if (!__seen_ppulse)
        {
         __seen_ppulse = TRUE;
         __pv_fwarn(666,
          "all (PATHPULSE forms ignored - actual delay used for reject or x limits"); 
        }
      }
     else
      {
       if (!__seen_pc_ppulse)
        {
         __seen_pc_ppulse = TRUE;
         __pv_fwarn(656,
          "all (PATHPULSEPERCENT forms ignored - 100%% of delay for r or x limits used"); 
        }
      }
     if (ctmdp == NULL)
      {
       __pv_ferr(1395, "primitive (gate or UDP) CELLTYPE illegal for PATHPULSE");
      }
     break;
    case SDF_ABSOLUTE:
    case SDF_INCREMENT:
     strcpy(formnam, __token);
     rd_deldef(f, itp, ctmdp, formnam);
     break;
    default:
     __pv_ferr(1336, "expected deltype form - (%s read", prt_sdftok());
     return(FALSE);
   }
  }
 return(TRUE);
}

/*
 * return T and emit error if port is a qualified name
 *
 * for places where port must be top level port or node name
 * no error message if emsg nil, used for places where legal
 * to see if must find downward itree loc. 
 */
static int32 port_qual_nam(char *nam, char *emsg)
{
 char *chp, *chp2;

 chp = nam;
try_more:
 if ((chp = strchr(chp, '.')) == NULL) return(FALSE);
 if (chp == nam) goto emit_msg;
 chp2 = chp - 1;
 /* not escaped, has separator */ 
 if (*chp2 != '\\') goto emit_msg;
 chp++;
 goto try_more;

emit_msg:
 if (emsg != NULL)
  {
   __pv_ferr(1381,
    "hierarchical name %s illegal for %s - must be (CELL top level name",
    nam, emsg);
  }
 return(TRUE);
}

/*
 * fill 1 value list - returns no. of delays (-1 for error else 1)
 *
 * fill work value tables position 0 - no need to pre-initialize
 * ( read and reads one after ending )
 * fills pos. 1 of global sdf delp but does not set number of delays
 */
static int32 rd_1_val(FILE *f, char *formnam)
{
 struct t_vpi_time *vtp = &(__sdf_delp->da[0]);

 if (__toktyp != LPAR)
  {
   __pv_ferr(1334, "(%s required first rvalue bad - %s read", formnam,
    prt_sdftok());
   return(-1);
  }
 get_sdftok(f);
 /* this reads and checks ending ) */ 
 if (!rd_rtriple(f, vtp)) return(-1);
 get_sdftok(f); 
 return(1);
}

/*
 * fill 1 value list (2nd version where know first value token read)
 *
 * fill work value tables position 0 - no need to pre-initialize
 * ( read and reads one after ending )
 */
static int32 rd2_1_val(FILE *f)
{
 struct t_vpi_time *vtp = &(__sdf_delp->da[0]);

 /* this reads and checks ending ) */ 
 if (!rd_rtriple(f, vtp)) return(FALSE);
 get_sdftok(f); 
 return(TRUE);
}

/*
 * fill 1 or 2 value list - for path pulse and timing checks
 * caller determines if found number is right
 * returns number found (-1 on error)
 *
 * fill work value tables position 0 and maybe 1 - no need to pre-initialize
 * ( read and reads one after ending )
 */
static int32 rd_1or2_vals(FILE *f, char *formnam)
{
 int32 nvals;
 struct t_vpi_time *vtp = &(__sdf_delp->da[0]);

 if (__toktyp != LPAR)
  {
   __pv_ferr(1334, "(%s required first rvalue bad - %s read", formnam,
    prt_sdftok());
   return(-1);
  }
 get_sdftok(f);
 /* this reads and checks ending ) */ 
 if (!rd_rtriple(f, vtp)) return(-1);
 get_sdftok(f); 
 if (__toktyp == LPAR)
  {
   get_sdftok(f);
   /* this reads and checking ending ) */ 
   if (!rd_rtriple(f, &(vtp[1]))) return(-1);
   get_sdftok(f);
   nvals = 2;
  }
 else nvals = 1;
 return(nvals);
}

/*
 * fill exactly 4 value list (not for delays - for timing constraints) 
 *
 * fill work value tables position 0, 1, 2, and 3 - no need to pre-initialize
 * ( read and reads one after ending )
 */
static int32 rd_4_vals(FILE *f, char *formnam)
{
 int32 i;
 struct t_vpi_time *vtp = &(__sdf_delp->da[0]);

 for (i = 0; i < 4; i++)
  {
   if (__toktyp != LPAR)
    {
     __pv_ferr(1334, "(%s required rvalue (pos %d) bad - %s read", formnam,
      i, prt_sdftok());
     return(FALSE);
    }
   get_sdftok(f);
   /* this reads and checks ending ) */ 
   if (!rd_rtriple(f, &(vtp[i]))) return(FALSE);
   get_sdftok(f); 
  }
 return(TRUE);
}

/*
 * read an absolute or increment delay form 
 *
 * grammar type is del_def+
 * name of del_def form read - reads form ending )
 */
static int32 rd_deldef(FILE *f, struct itree_t *itp, struct mod_t *ctmdp,
 char *formnam)
{
 int32 first_time;

 /* at least one required */
 for (first_time = TRUE;;) 
  {
   get_sdftok(f);
   if (!rd_sdf_formtyp(f)) return(FALSE);
   if (__toktyp == RPAR)
    {
     if (first_time)
      {
       __pv_ferr(1337, "(%s form empty - at least one del_def form required",
         formnam);
       return(FALSE);
      }
     break;
    }
   if (ctmdp == NULL && __toktyp != SDF_DELAY)
    {
     __pv_ferr(1399,
      "primitive (gate or UDP) CELLTYPE illegal for %s form", prt_sdftok());
     if (!sdf_skip_form(f)) return(FALSE);
     continue; 
    }
   first_time = FALSE;
   switch (__toktyp) {
    case SDF_IOPATH:
     if (!rd_iopath(f, itp, ctmdp, NULL, FALSE, formnam))
      return(FALSE);
     break;
    case SDF_COND:
     /* this calls rd iopath to match and set path delay */
     if (!rd_del_def_cond(f, itp, ctmdp, formnam)) return(FALSE);
     break;
    case SDF_CONDELSE:
     get_sdftok(f); 
     if (__toktyp != LPAR)
      {
bad_condelse:
       __pv_ferr(1335, "(%s CONDELSE form bad - %s read", formnam,
        prt_sdftok());
       return(FALSE);
      }
     get_sdftok(f);
     if (__toktyp != SDF_IOPATH) goto bad_condelse;
     if (!rd_iopath(f, itp, ctmdp, NULL, TRUE, formnam))
      return(FALSE);
     get_sdftok(f);
     if (__toktyp != RPAR) goto bad_condelse;
     break;
    case SDF_PORT:
     if (!rdset_port_mipd(f, itp, ctmdp, formnam)) return(FALSE);             
     break;
    case SDF_INTERCONNECT:
     if (!rdset_interconn_dels(f, itp, ctmdp, formnam)) return(FALSE);
     break;
    case SDF_DEVICE:
     if (!rdset_devpath_dels(f, itp, ctmdp, formnam))
      return(FALSE);
     break;
    default:
     __pv_ferr(1353, "timing_spec form name expected - %s read", 
      prt_sdftok());
     return(FALSE);
   }
  }
 return(TRUE);
}

/*
 * emit a missing delay list starting ( error 
 */
static void dellst_err(char *formnam, char *formnam2)
{
 __pv_ferr(1352, "(%s (%s form delay list starting ( expected - %s read",
  formnam, formnam2, prt_sdftok());
}

/*
 * emit a missing form end ) error
 */
static void formend_err(char *formnam)
{
 __pv_ferr(1354, "(%s form ending ) expected - %s read",
  formnam, prt_sdftok());
}

/*
 * read and process an IOPATH form - Verilog specify path
 *
 * this returns F on syntax error but T if syntax good and annotate error
 * know (IOPATH read and reads ending )
 * qualified name illegal here
 */
static int32 rd_iopath(FILE *f, struct itree_t *itp, struct mod_t *ctmdp,
 struct expr_t *cndx, int32 is_condelse, char *formnam)
{
 struct pthlst_t *plp;
 int32 si1, si2, di1, di2, ndels, eval, sav_lcnt, lcnt;
 struct pthlst_t *plhd;
 char portsrc[IDLEN], portdst[IDLEN];

 get_sdftok(f);
 lcnt = __lin_cnt;
 if (__toktyp == ID || __toktyp == LPAR)
  {
   if (!rd_port_spec(f, portsrc, &si1, &si2, &eval, FALSE)) return(FALSE);
   if (!rd_port(f, portdst, &di1, &di2)) return(FALSE);
  }
 else
  {
   __pv_ferr(1339, "(IOPATH source portspec starting token expected - %s read",
    prt_sdftok()); 
   return(FALSE);
  }    
 if (__toktyp != LPAR) { dellst_err(formnam, "IOPATH"); return(FALSE); }
 get_sdftok(f);
 /* LOOKATME - grammar allows multiple but have no semantic meaning */
 if (__toktyp == SDF_RETAIN)
  {
   /* not supported by Cver - need warning for every one */ 
   __pv_fwarn(632,
    "SDF (RETAIN form (time value retained) skipped - not supported");
   get_sdftok(f);
   if (__toktyp != LPAR) { dellst_err(formnam, "RETAIN"); return(FALSE); }
   get_sdftok(f);
   /* need first after ( to have been read and reads ) one past end */
   if ((ndels = rd_sdf_dellst(f, "IOPATH RETAIN")) == -1) return(FALSE);
   get_sdftok(f);
   if (__toktyp != LPAR)
    { dellst_err(formnam, "delval aftere RETAIN"); return(FALSE); }
   get_sdftok(f);
  }
 /* this reads end of io path form */
 if ((ndels = rd_sdf_dellst(f, "IOPATH")) == -1) return(FALSE);

 /* syntax good but can not set delays */
 if (port_qual_nam(portsrc, "(IOPATH port")) return(TRUE); 
 if (port_qual_nam(portdst, "(IOPATH port")) return(TRUE); 

 /* now always return T since syntax good even if annotate fails */ 
 /* need to be able to emit f errors for first token in form from here on */
 sav_lcnt = __lin_cnt; 
 __lin_cnt = lcnt;  

 /* except for next 2 fields all t_vpi_delay fields fixed in SDF */
 __sdf_delp->no_of_delays = ndels; 
 if (strcmp(formnam, "INCREMENT") == 0) __sdf_delp->append_flag = TRUE;
 else __sdf_delp->append_flag = FALSE;

 /* build list of candidate path matches, nil if none */
 /* edge always included in filter of src-dsts */
 if ((plhd = bld_match_spcpth(ctmdp, portsrc, si1, si2, eval, portdst,
  di1, di2, cndx, is_condelse)) == NULL) goto done;

 for (plp = plhd; plp != NULL; plp = plp->pthlnxt)
  set_1pthdel(plp, itp, ctmdp);

done:
 __lin_cnt = sav_lcnt;  
 free_pthlst(plhd);
 return(TRUE);
}

/*
 * convert SDF path string components to path string for output
 */
static char *msg_sdfpath_tostr(char *s, char *psrcnam, int32 si1, int32 si2,
 int32 eval, char *pdstnam, int32 di1, int32 di2, struct expr_t *cndx,
 int32 is_condelse)
{
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 if (si1 == -1) strcpy(s1, "");
 else if (si1 == si2) sprintf(s1, "[%d]", si1);
 else sprintf(s1, "[%d:%d]", si1, si2);

 if (di1 == -1) strcpy(s2, "");
 else if (di1 == di2) sprintf(s2, "[%d]", di1);
 else sprintf(s2, "[%d:%d]", di1, di2);

 if (eval == NOEDGE) sprintf(s3, "%s%s", psrcnam, s1);
 else if (eval == E_POSEDGE) sprintf(s3, "(posedge %s%s)", psrcnam, s1);
 else if (eval == E_NEGEDGE) sprintf(s3, "(negedge %s%s)", psrcnam, s1);
 else __case_terr(__FILE__, __LINE__);

 if (cndx != NULL)
  sprintf(s, "(COND ... (IOPATH %s %s%s", s3, pdstnam, s2);
 else if (is_condelse)
  sprintf(s, "(CONDELSE ... (IOPATH %s %s%s", s3, pdstnam, s2);
 else sprintf(s, "(IOPATH %s %s%s", s3, pdstnam, s2);
 return(s);
}

/*
 * set one path delay - given a one element from list of selected paths
 *
 * this handles itp nil wildcard instance case too
 */
static void set_1pthdel(struct pthlst_t *plp, struct itree_t *itp,
 struct mod_t *ctmdp)
{
 struct spcpth_t *pthp;
 struct gate_t ogat, ngat;
 char s1[RECLEN];

 pthp = plp->lpthp;
 /* old path delay - maybe none */
 ogat.g_du = pthp->pth_du;
 ogat.g_delrep = pthp->pth_delrep;

 /* update the delays */
 sprintf(s1, "(IOPATH for path at %s", __bld_lineloc(__xs,
  pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt));
 if (itp == NULL)
  { 
   /* result starts in ogat moves to ngat then finally put back in ogat */
   if (!upd_sdf_perinst_del(&ogat, __sdf_delp, ctmdp, TRUE, FALSE,
    4, s1)) return;
  }
 else
  {
   /* SJM 04/16/08 - know path delay always 16v - no need for 4v correction */
   if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp, itp, TRUE, FALSE, s1))
    return;
   __chg_1inst_del(&ogat, itp, &ngat);
   __free_del(ngat.g_du, ngat.g_delrep, ctmdp->flatinum);
  }
 pthp->pth_du = ogat.g_du;  
 pthp->pth_delrep = ogat.g_delrep;
 if (__sdf_verbose) prep_sdfiopath_verbmsg(pthp, &ogat, itp, ctmdp);
}

/*
 * wrapper to prepare and call iopath sdf verbose tracing message
 */
static void prep_sdfiopath_verbmsg(struct spcpth_t *pthp, struct gate_t *ogp, 
 struct itree_t *itp, struct mod_t *mdp)
{
 int32 ii;
 struct itree_t *itp2;
 char s1[RECLEN], s2[RECLEN];

 if (itp == NULL)
  {
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp2 = mdp->moditps[ii];
     __push_itstk(itp2);
     sprintf(s1, "%s(%s) from '*'", __msg2_blditree(s2, itp2),
      mdp->msym->synam);
     emit_sdfiopath_verbmsg(pthp, ogp, s1);
     __pop_itstk();
    }
  } 
 else
  {
   __push_itstk(itp);
   sprintf(s1, "%s(%s)", __msg2_blditree(s2, itp), mdp->msym->synam);
   emit_sdfiopath_verbmsg(pthp, ogp, s1);
   __pop_itstk();
  }
}

/*
 * emit sdf device verbose tracing message 
 */
static void emit_sdfiopath_verbmsg(struct spcpth_t *pthp, struct gate_t *ogp,
 char *celloc)
{
 char s1[RECLEN], s2[RECLEN];

 __cv_msg("  SDF **%s(%d): (IOPATH at %s delay set to (%s) in %s\n",
  __cur_fnam, __lin_cnt,
  __bld_lineloc(s1, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt),
 __bld_delay_str(s2, ogp->g_du, ogp->g_delrep), celloc);
}

/*
 * update sdf per instance (inst wildcard * form) delay 
 * when done ogp will have new probably per instance delay for object
 * this updates old (ogp) by copying to work then updating in ogp
 *
 * new gate is just work place to hold delay
 * first will change to correct instance form, then rest will usually 
 * just fill in the other instances
 * bld vpi new du need to have lin and fnam ind set for f errors
 * this handles any freeing of work delays it creates
 *
 * dfix is expected transitions for delay usually 4 (includes x/z) but
 * sometimes 2 or 3
 */
static int32 upd_sdf_perinst_del(struct gate_t *ogp, p_vpi_delay delay_p,  
 struct mod_t *ctmdp, int32 is_path, int32 has_toz, int32 dfix, char *sdfmsg)
{
 int32 ii;
 int32 has_err, none_chged;
 struct gate_t wgat;
 struct itree_t *itp;

 /* case 1: need loop for selected instances */
 if (delay_p->append_flag || __sdf_cntxt_itp != NULL)
  {
   has_err = FALSE;
   for (none_chged = TRUE, ii = 0; ii < ctmdp->flatinum; ii++)
    {
     itp = ctmdp->moditps[ii];
     if (__sdf_cntxt_itp != NULL && !itp_under_cntxt(itp)) continue;

     /* need error for every, if problem */
     if (!bld_sdfnewdu(&wgat, ogp, __sdf_delp, itp, is_path, has_toz,
      sdfmsg)) { has_err = TRUE; continue; }

     /* know if is path, never build 4v */
     if (wgat.g_delrep == DT_4V)
      {
       if (dfix == 2) set_logic_gdel_tox_val(&(wgat));
       else if (dfix == 3) set_toz_gdel_tox_val(&(wgat));
       else __case_terr(__FILE__, __LINE__);
      }

     none_chged = FALSE;
     __chg_1inst_del(ogp, itp, &wgat);
     __free_del(wgat.g_du, wgat.g_delrep, ctmdp->flatinum);
    }
   if (none_chged)
    {
     __pv_fwarn(665,
      "delays not changed for %s because no instance of type %s in context", 
      sdfmsg, ctmdp->msym->synam);
    }
   if (has_err) return(FALSE);
   return(TRUE);
  }
 /* case 2: change to per type delay (no context and not append) */
 /* since not append, just need itp for getting module for scaling */
 itp = ctmdp->moditps[0];
 if (!bld_sdfnewdu(&wgat, ogp, __sdf_delp, itp, is_path, has_toz, sdfmsg))
  return(FALSE); 

 /* know if is path, never build 4v */
 if (wgat.g_delrep == DT_4V)
  {
   if (dfix == 2) set_logic_gdel_tox_val(&(wgat));
   else if (dfix == 3) set_toz_gdel_tox_val(&(wgat));
   else __case_terr(__FILE__, __LINE__);
  }
 /* freeing old probably per inst. */
 __free_del(ogp->g_du, ogp->g_delrep, ctmdp->flatinum);

 /* replacing with known per type form */
 ogp->g_du = wgat.g_du;
 ogp->g_delrep = wgat.g_delrep;
 return(TRUE);
}

/*
 * return T if instance itp under context itp (work up)
 */
static int32 itp_under_cntxt(struct itree_t *itp)
{
 for (;;)
  {
   if (itp == __sdf_cntxt_itp) return(TRUE); 
   if (itp == NULL) break;
   itp = itp->up_it;
  }
 return(FALSE);
}

/*
 * read a port spec (path input or timing check terminal)
 * this expects first token read and reads one past end
 *
 * even though in Verilog only posedge and negedge for path sources - for
 * SDF can any edge but will just not match 
 */
static int32 rd_port_spec(FILE *f, char *pnam, int32 *i1, int32 *i2, int32 *eval,
 int32 is_tchk)
{
 int32 nd_rpar, ettyp;

 /* skip the edge form - form not currently readable because of [val][val] */
 *eval = NOEDGE;
 nd_rpar = FALSE;
 if (__toktyp == LPAR)
  {
   if ((ettyp = rd_edge_ident(f)) == -1) return(FALSE);
   *eval = ettyp; 
   /* for non timing checks (iopaths), only pos and neg edges allowed */
   /* error will inhibit simulation but does not effect sdf reading */
   if (!is_tchk && ettyp != E_POSEDGE && ettyp != E_NEGEDGE)
    { 
     __pv_ferr(1340,
      "(IOPATH portspec port_edge %s impossible in Verilog - only posedge or negedge legal",
      __to_edgenam(__xs, (word32) ettyp));
    } 
   nd_rpar = TRUE;
   get_sdftok(f);
  }
 if (!rd_port(f, pnam, i1, i2)) return(FALSE);
 if (nd_rpar)
  {
   /* know one past port spec read */
   if (__toktyp != RPAR)
    {
     __pv_ferr(1346, "portspec port_edge ending ) expected - %s read",
      prt_sdftok()); 
     return(FALSE);
    }
   get_sdftok(f);
  }
 return(TRUE);
}

/*
 * read a port specification 
 *
 * name (id) read and reads one past end
 * portnam is verilog name (escaped and path separator handled)
 * can be qualified name here - caller may allow or not
 * vector ports can appear with or without range - SDF side determines
 * for matching
 */
static int32 rd_port(FILE *f, char *portnam, int32 *i1, int32 *i2)
{
 *i1 = *i2 = -1;
 if (__toktyp != ID)
  {
   __pv_ferr(1343, "SDF port reference expected - %s read", prt_sdftok());
   return(FALSE);
  }
 if (__id_qualpath)
  {
   if (!chkcnv_sdfpath(portnam, i1, i2, __token, TRUE))
    {
     __pv_ferr(1366,
      "hierarchical port name reference %s illegal Verilog name",
      __token);
     return(FALSE);
    }
  }
 else if (!chkcnv_sdfid(portnam, i1, i2, __token, TRUE))
  {
   __pv_ferr(1366, "port name %s illegal SDF or Verilog identifier",
      __token);
   return(FALSE);
  }
 /* need to read one past */
 get_sdftok(f);
 return(TRUE);
}

/*
 * build a list of matching specify paths
 *
 * rule is that missing SDF is treated as wildcard (all match) but if
 * present in SDF must match exactly (including path has edge)
 * idea: only as much SDF constructs as needed must be code in SDF file 
 */
static struct pthlst_t *bld_match_spcpth(struct mod_t *ctmdp, char *psrcnam,
 int32 si1, int32 si2, int32 eval, char *pdstnam, int32 di1, int32 di2, 
 struct expr_t *cndx, int32 is_condelse)
{
 int32 rv, rv2, has_xmr;
 struct spcpth_t *pthp;
 struct pathel_t *pep1, *pep2;
 struct pthlst_t *plp, *plhd, *plend;

 if (ctmdp->mspfy == NULL)
  {
   not_a_port(psrcnam, IO_IN, ctmdp, "(IOPATH [source]");
   not_a_port(pdstnam, IO_OUT, ctmdp, "(IOPATH [dest.]");
   __pv_ferr(1387, "unable to match (IOPATH in type %s - no specify section", 
    ctmdp->msym->synam);
   return(NULL);
  }
 plhd = plend = NULL;
 /* build list of matching source-dest but ignore cond or condelse for now */ 
 for (pthp = ctmdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
  {
   /* step 1: match src and dest name and range - rule is to use first only */
   pep1 = &(pthp->peins[0]);
   pep2 = &(pthp->peouts[0]); 
   /* eliminate if net names do not match */
   if (strcmp(pep1->penp->nsym->synam, psrcnam) != 0 ||
    strcmp(pep2->penp->nsym->synam, pdstnam) != 0) continue;

   /* this is just matching to stuff delay into right path */
   /* therefore if Verilog source is vector without range SDF no range too */
   /* and vice versa */
   if (pep1->pthi1 != si1 || pep1->pthi2 != si2) continue;
   if (pep2->pthi1 != di1 || pep2->pthi2 != di2) continue;

   /* step 2: match edge, but no SDF edge means match all */ 
   /* i.e. if SDF has edge but path does not, no match */
   if (!__ignore_sdf_iopath_edges)
    {
     if (eval != NOEDGE)
      { if (pthp->pthedge != eval) continue; }
    }

   /* step 3: if SDF condition or SDF condelse (Verilog ifnone), */
   /* must match - know not both condx and condelse */
   /* if missing from SDF, then always matches even if path has cond */
   if (cndx != NULL)
    {
     if (pthp->pthcondx == NULL) continue;
     /* if expr's do not match, keep looking */
     if (!__cmp_xpr(pthp->pthcondx, cndx, &has_xmr)) continue; 
    }
   else if (is_condelse && !pthp->pth_ifnone) continue;

   /* have match */
   /* src-dst match emit warning even though cond or edge may eliminate */
   if (pthp->last_pein > 0 || pthp->last_peout > 0)
    {
     __finform(475,
      "(IOPATH matches first component only of Verilog component path list at %s in %s",
      __bld_lineloc(__xs, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt),
      ctmdp->msym->synam);
    }
   plp = (struct pthlst_t *) __my_malloc(sizeof(struct pthlst_t));
   plp->lpthp = pthp;
   plp->pthlnxt = NULL; 
   if (plend == NULL) plhd = plend = plp;
   else { plend->pthlnxt = plp; plend = plp; }
  }
 if (plhd == NULL)
  {
   rv = not_a_port(psrcnam, IO_IN, ctmdp, "(IOPATH [source]");
   rv2 = not_a_port(pdstnam, IO_OUT, ctmdp, "(IOPATH [dest.]");
   if (rv || rv2) return(NULL);

   __pv_ferr(1369,
    "no module %s specify path (first component used) matches %s",
    ctmdp->msym->synam, msg_sdfpath_tostr(__xs, psrcnam, si1, si2, eval,
    pdstnam, di1, di2, cndx, is_condelse));
  }
 return(plhd);
}

/* SJM 06/15/00 - removed old (COND as string compare - now compare exprs */

/*
 * free a path list
 */
static void free_pthlst(struct pthlst_t *pthlhd)
{
 struct pthlst_t *pthlp, *pthlp2;

 for (pthlp = pthlhd; pthlp != NULL;)
  {
   pthlp2 = pthlp->pthlnxt;
   __my_free(pthlp, sizeof(struct pthlst_t));
   pthlp = pthlp2;
  }
}
 
/*
 * read a del (COND form
 *
 * (COND read and reads ending )
 * LOOKATME - building token list as ascii string for matching
 */
static int32 rd_del_def_cond(FILE *f, struct itree_t *itp, struct mod_t *ctmdp,
 char *formnam)
{
 int32 sav_declobj;
 struct expr_t *cond_expr;
 char labnam[IDLEN];

 get_sdftok(f);   
 /* LOOKATME - ignoring label - think Verilog can not use labels? */
 if (__toktyp == LITSTR) { strcpy(labnam, __token); get_sdftok(f); }
 
 /* SJM - 06/15/00 - build expr. using src reading mechanism */
 if (__top_sti != 0) __misc_terr(__FILE__, __LINE__);
 /* need to save since will probably be interactive mode */
 sav_declobj = __cur_declobj;
 __cur_declobj = SPECIFY;
 __cur_spfy = ctmdp->mspfy;
 __venviron[0] = ctmdp->msymtab; 
 __venviron[1] = __cur_spfy->spfsyms;
 __top_sti = 1;

 __saverr_cnt = __pv_err_cnt;

 /* SJM 05/14/01 - only allow scalar constants in io path conds */ 
 /* scalars in timing check conditions in fixed place so no expr collect */
 __rding_cond_expr = TRUE;
 if (!col_cond_port_expr(f)) { __rding_cond_expr = FALSE; return(FALSE); }
 __rding_cond_expr = FALSE;

 __bld_xtree(0);
 cond_expr = __root_ndp;
 __top_sti = 0;
 __cur_declobj = sav_declobj;
 /* if already error, do not check expr. */ 
 if (__pv_err_cnt != __saverr_cnt)
  {
   __pv_ferr(1390, "invalid SDF (COND expression");
   return(FALSE);
  }

 if (!rd_iopath(f, itp, ctmdp, cond_expr, FALSE, formnam)) return(FALSE);
 get_sdftok(f);
 if (__toktyp != RPAR)
  {
   __pv_ferr(1335, "(%s (COND form ending ) expected - %s read",
    formnam, prt_sdftok());
   return(FALSE);
  }
 return(TRUE);
}

/*
 * collect and build expression to (IOPATH 
 *
 * expects 1st expr. token to have been read (after '(') 
 * and reads ending ( IOPATH sequence  
 *
 * LOOKATME - uses pass 1 expr mechanism - see if works
 */
static int32 col_cond_port_expr(FILE *f)
{
 int32 last_sdftok;

 /* this is illegal empty case */
 __last_xtk = -1;
 if (__toktyp == LPAR)
  {
   get_sdftok(f);
   if (__toktyp != SDF_IOPATH)
    {
     last_sdftok = __toktyp;
     __toktyp = LPAR;
     /* BEWARE - this works because for operator token name unchanged */
     if (!sdf_bld_expnode()) goto bad_end;
     __toktyp = last_sdftok;
     goto col_expr;
    } 

   __pv_ferr(1390, "empty SDF IOPATH (COND expression illegal");
bad_end:
   /* notice cannot free here since in __exprtab (links just overwritten) */
   /* also make look like empty expr. */
   __set_xtab_errval();
   return(FALSE);
  }

 /* notice SDF expressions can't be parenthesized */
col_expr:
 for (;;)
  {
   if (!sdf_bld_expnode()) goto bad_end;
   last_sdftok = __toktyp; 
   get_sdftok(f);
   /* SJM 08-11-09 - must read ( before the IOPATH and then adjust back one */
   if (__toktyp == SDF_IOPATH)
    {
     if (last_sdftok != LPAR)
      {
       __pv_ferr(1390, "expected (IOPATH missing - %s read", prt_sdftok());
       goto bad_end;
      }
     /* SJM 08-11-09 - LOOKATME? - this is minor memory leak */
     __last_xtk--;
     break;
    }
   if (__toktyp == TEOF || __toktyp == SEMI)
    {
     if (__pv_err_cnt <= __saverr_cnt)
      __pv_ferr(1390, "illegal token %s in SDF (COND expression",
       prt_sdftok());
     goto bad_end;
    }
   last_sdftok = SDF_UNKN;
  }
 return(TRUE);
}

/*
 * build sdf expression tree node from current token
 * always places it in next free place in __exprtab
 * reuses storage so bld_xtree must allocate nodes
 *
 * puts ID name in expr_idtab that is changed to symbol in
 * parse term routine (either ID or xmr component)
 */
static int32 sdf_bld_expnode(void)
{
 const struct opinfo_t *oip;
 struct expr_t *ndp;
 struct xstk_t *xsp;

 ndp = __alloc_exprnd();
 switch (__toktyp) {
  case ID:
   /* if can be inst. ref, assume global fix later */
   /* notice anthing in this case but id and glb wrong - caught later */
   ndp->optyp = ID;
   __alloc_expridnd(__token);
   break;
  case NUMBER:
   /* notice scanner only returns number */  
   ndp->optyp = NUMBER;
   ndp->szu.xclen = WBITS;
   ndp->unsiznum = FALSE;
   ndp->has_sign = FALSE;
   ndp->ibase = BDEC;
   ndp->sizdflt = TRUE;
   ndp->ru.xvi = __alloc_shareable_cval(__sdf_tokval, 0, WBITS);
   break;
  case REALNUM:
   /* num storage pted to by a part - usually (except xstk) no b part */ 
   ndp->optyp = REALNUM;
   ndp->szu.xclen = REALBITS;
   ndp->ibase = BDBLE;
   ndp->is_real = TRUE;
   ndp->has_sign = TRUE;
   /* LOOKATME - SIZE assuming size of real is 8 bytes here */
// ==========### SJM 02/17/05 - FIXME - WHY NOT PUT IN REAL CON TAB 
   push_xstk_(xsp, WBITS);
   memcpy(xsp->ap, &(__itok_realval), sizeof(double));
   ndp->ru.xvi = __allocfill_cval_new(xsp->ap, xsp->bp, 1);
   __pop_xstk();
/* ---
   wp = &(__contab[ndp->ru.xvi]);
   memcpy(wp, &__itok_realval, sizeof(double));
--- */
   break;
  case TEOF: case LITSTR:
   /* since no error recovery in interactive - this is finish path */
   /* caller sets to error expression */ 
   ndp->optyp = BADOBJ;
   return(FALSE);
  default:
   if (__toktyp > LASTOP)
    {
     /* keywords can not be in or end expressions */
     if (__pv_err_cnt <= __saverr_cnt)
      __pv_ferr(1104, "illegal token %s in SDF expression", prt_sdftok());
     return(FALSE);
    }
   /* build an operator node */
   oip = &(__opinfo[__toktyp]);
   if (oip->opclass == NOTANOP)
    {
     if (__pv_err_cnt <= __saverr_cnt)
      __pv_ferr(1105, "illegal punctuation %s in SDF expression",
       prt_sdftok());
     return(FALSE);
    }
   /* build an operator node */
   ndp->optyp = __toktyp;
  }
 return(TRUE);
}

/*
 * ROUTINES TO READ TIMING CHECKS
 */

/*
 * read a timing spec form
 * timing checks terminals can not be qualified names
 *
 * qualified (xmr) terminal name illegal here
 */
static int32 rdset_tchk_defs(FILE *f, struct itree_t *itp,
 struct mod_t *ctmdp)
{
 int32 first_time, sdf_tctyp, tchktyp, ndels, lcnt, sav_lcnt, match_tctyp;
 struct tclst_t *tclp;
 struct tchk_t *tcp; 
 struct tclst_t *tclhd;
 struct gate_t ogat, ngat;
 char sdf_tcnam[RECLEN], s1[RECLEN]; 

 for (first_time = TRUE;;) 
  {
   /* this returns T if ) */
   get_sdftok(f);
   lcnt = __lin_cnt; 
   if (!rd_sdf_formtyp(f)) return(FALSE);
   if (__toktyp == RPAR)
    {
     if (first_time)
      {
       __pv_ferr(1341,
        "(TIMINGCHECK form empty - at least one tc_def required");
       return(FALSE);
      }
     break;
    }
   first_time = FALSE;
   sdf_tctyp = __toktyp;
   /* must be tchk form - any other form error */
   if ((tchktyp = from_sdf_tctyp(sdf_tctyp)) == -1)
    {
     __pv_ferr(1342, "tc_def timing check form expected - (%s read",
      prt_sdftok());
     return(FALSE);
    }
   /* this is SDF side timing check name */
   strcpy(sdf_tcnam, prt_sdftok());
   ndels = 1;
   switch ((byte) tchktyp) {
    case TCHK_SETUP: case TCHK_HOLD: case TCHK_RECOVERY:
    case TCHK_REMOVAL: case TCHK_SKEW: case TCHK_FULLSKEW:
    case TCHK_TIMESKEW:
     /* 10/30/00 SJM - for setup and hold if no match tries to match */
     /* corresponding ports of setuphold */
     /* match tctyp can be setuphold if SDF hold or setup matches */
     /* Verilog setuphold */
     if (!rdset_2term_1v_tchk(&tclhd, &match_tctyp, f, ctmdp, sdf_tcnam,
      tchktyp, lcnt, &sav_lcnt)) return(FALSE);

     if (tclhd == NULL) continue;

     /* 10/27/00 SJM - setup or hold matches setuphold, annotate the half */
     /* this is needed to match XL behavior */
     if (match_tctyp == TCHK_SETUPHOLD)
      {
       /* 10/28/00 SJM - this is special case where SDF hold or setup */
       /* terminals do not match same setup/hold type but do match a */
       /* setuphold in Verilog source*/
       /* this uses loop to process every timing check as loop below */
       set_half_setuphold_tchk_defs(tclhd, tchktyp, itp, ctmdp);
       goto nxt_tchk;
      }
     else if (match_tctyp == TCHK_RECREM)
      {
       /* SJM 01/16/04 - same questionable algorithm for recrem */
       set_half_recrem_tchk_defs(tclhd, tchktyp, itp, ctmdp);
       goto nxt_tchk;
      }
     break;
    case TCHK_WIDTH: case TCHK_PERIOD:
     if (!rdset_1term_1v_tchk(&tclhd, f, ctmdp, sdf_tcnam, tchktyp, lcnt,
      &sav_lcnt)) return(FALSE);
     if (tclhd == NULL) continue;
     break;
    case TCHK_SETUPHOLD: case TCHK_RECREM:
     /* SJM 01/16/04 - recrem also same two terminals */
     if (!rdset_2term_2v_tchk(&tclhd, f, ctmdp, sdf_tcnam, tchktyp, lcnt,
      &sav_lcnt)) return(FALSE);
     if (tclhd == NULL) continue;

     /* normal annotate to both delays of setup hold at once */ 
     ndels = 2;
     break;
    case TCHK_NOCHANGE:
     /* 10/27/00 - SJM here ignore matched tc typ only used for setup hold */
     if (!rdset_2term_2v_tchk(&tclhd, f, ctmdp, sdf_tcnam, tchktyp, lcnt,
      &sav_lcnt)) return(FALSE);
     if (tclhd == NULL) continue;
     ndels = 2;
     break;
    default: __case_terr(__FILE__, __LINE__); return(FALSE);
   }
  /* know either one or two delays */
  for (tclp = tclhd; tclp != NULL; tclp = tclp->tclnxt)
   {
    tcp = tclp->tcp;

    /* know always at least one delay */
    ogat.g_du = tcp->tclim_du;
    ogat.g_delrep = tcp->tc_delrep;
    if (ogat.g_delrep == DT_NONE) __misc_terr(__FILE__, __LINE__);

    /* update the delays */
    sprintf(s1, "(TIMINGCHECK (%s at %s", sdf_tcnam,
     __bld_lineloc(__xs, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt));
    if (itp == NULL)
     {
      /* result starts in ogat and also ends up there */
      if (!upd_sdf_perinst_del(&ogat, __sdf_delp, ctmdp, FALSE, 4, FALSE, s1))
       goto none_chged;
     }
    else
     {
      /* timing checks can't have logic/bufix toz delays */
      if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp, itp, FALSE, FALSE, s1))
       goto none_chged;
      __chg_1inst_del(&ogat, itp, &ngat);
      __free_del(ngat.g_du, ngat.g_delrep, ctmdp->flatinum);
     }
    /* if found no delays to change, must not assign old gate */ 
    tcp->tclim_du = ogat.g_du;  
    tcp->tc_delrep = ogat.g_delrep;
    if (__sdf_verbose)
     prep_sdftchk_verbmsg(tcp, sdf_tcnam, &ogat, itp, ctmdp, "");
none_chged:
    if (ndels == 1) continue;

    sprintf(s1, "(TIMINGCHECK (%s at %s second limit", sdf_tcnam,
     __bld_lineloc(__xs, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt));
    ogat.g_du = tcp->tclim2_du;
    ogat.g_delrep = tcp->tc_delrep2;
    if (ogat.g_delrep == DT_NONE) __misc_terr(__FILE__, __LINE__);
    if (itp == NULL)
     {
      if (!upd_sdf_perinst_del(&ogat, __sdf_delp2, ctmdp, FALSE, 4, FALSE,
       s1)) continue;
     }
    else
     {
      /* timing checks can't have logic/bufix toz delays */
      if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp2, itp, FALSE, FALSE, s1))
       continue;
      __chg_1inst_del(&ogat, itp, &ngat);
      __free_del(ngat.g_du, ngat.g_delrep, ctmdp->flatinum);
     }
    tcp->tclim2_du = ogat.g_du;  
    tcp->tc_delrep2 = ogat.g_delrep;
    if (__sdf_verbose)
     prep_sdftchk_verbmsg(tcp, sdf_tcnam, &ogat, itp, ctmdp, "2nd ");
   }
nxt_tchk:
   /* must put back each time */
   __lin_cnt = sav_lcnt;  
   free_tclst(tclhd);
  }
 return(TRUE);
}

/*
 * set setup or hold half (only) of setuphold timing check 
 *
 * know all reading done and only called for special case where  
 * have found setup or hold form in SDF that matches $setuphold
 * in vrilog so need to update only one of the 2 timing delays 
 *
 * 10/27/00 SJM - this is special case routine for matching XL that allows
 * SDF that does not have setuphold's but has separate setup and hold forms
 */
static void set_half_setuphold_tchk_defs(struct tclst_t *tclhd,
 int32 sdf_tctyp, struct itree_t *itp, struct mod_t *ctmdp)
{
 struct tclst_t *tclp;
 struct tchk_t *tcp;
 struct gate_t ogat, ngat;
 char sdf_tcnam[RECLEN], s1[RECLEN], s2[RECLEN];

 if (sdf_tctyp == TCHK_SETUP)
  strcpy(sdf_tcnam, "SETUP matched to $setuphold");
 else strcpy(sdf_tcnam, "HOLD matched to $setuphold");

 /* LOOKATME - this is normal SDF algorithm where one SDF can match all ver */
 for (tclp = tclhd; tclp != NULL; tclp = tclp->tclnxt)
  {
   tcp = tclp->tcp;
 
   /* know always at least one delay */
   /* match type determines which limit set */  
   /* LOOKATME - algorithm implies it is legal to use SDF to set one half */
   /* of setuphold but not other - questionable algorithm but matching XL */
   if (sdf_tctyp == TCHK_SETUP)
    {
     ogat.g_du = tcp->tclim_du;
     ogat.g_delrep = tcp->tc_delrep;
     strcpy(s2, "setup");
    }
   else
    {
     ogat.g_du = tcp->tclim2_du;
     ogat.g_delrep = tcp->tc_delrep2;
     strcpy(s2, "hold");
    }
   /* DBG remove -- */
   if (ogat.g_delrep == DT_NONE) __misc_terr(__FILE__, __LINE__);
   /* --- */ 

   /* update the delays */
   sprintf(s1, "%s half of (TIMINGCHECK (%s at %s", sdf_tcnam, s2,
    __bld_lineloc(__xs, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt));

   /* this builds delay into work "gate" place holder */
   if (itp == NULL)
    {
     /* result starts in ogat and also ends up there */
     if (!upd_sdf_perinst_del(&ogat, __sdf_delp, ctmdp, FALSE, 4, FALSE, s1))
      continue;
    }
   else
    {
     /* timing checks can't have logic/bufix toz delays */
     if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp, itp, FALSE, FALSE, s1))
      continue;
     __chg_1inst_del(&ogat, itp, &ngat);
     __free_del(ngat.g_du, ngat.g_delrep, ctmdp->flatinum);
    }
   /* for Verilog $setuphold, first limit is setup and 2nd is hold */
   if (sdf_tctyp == TCHK_SETUP)
    {
     tcp->tclim_du = ogat.g_du;  
     tcp->tc_delrep = ogat.g_delrep;
    }
   else if (sdf_tctyp == TCHK_HOLD)
    {
     tcp->tclim2_du = ogat.g_du;  
     tcp->tc_delrep2 = ogat.g_delrep;
    }
   else __case_terr(__FILE__, __LINE__);
   if (__sdf_verbose)
    prep_sdftchk_verbmsg(tcp, sdf_tcnam, &ogat, itp, ctmdp, "");
  }
}

/*
 * set recovery or removal half (only) of recrem timing check 
 *
 * know all reading done and only called for special case where  
 * have found recovery or removal form in SDF that matches $recrem
 * in verilog so need to update only one of the 2 timing delays 
 *
 * 10/27/00 SJM - this is special case routine for matching XL that allows
 * SDF that does not have recrem's but has separate recovery and removal
 */
static void set_half_recrem_tchk_defs(struct tclst_t *tclhd,
 int32 sdf_tctyp, struct itree_t *itp, struct mod_t *ctmdp)
{
 struct tclst_t *tclp;
 struct tchk_t *tcp;
 struct gate_t ogat, ngat;
 char sdf_tcnam[RECLEN], s1[RECLEN], s2[RECLEN];

 if (sdf_tctyp == TCHK_RECOVERY)
  strcpy(sdf_tcnam, "RECOVERY matched to $recrem");
 else strcpy(sdf_tcnam, "REMOVAL matched to $recrem");

 /* LOOKATME - this is normal SDF algorithm where one SDF can match all ver */
 for (tclp = tclhd; tclp != NULL; tclp = tclp->tclnxt)
  {
   tcp = tclp->tcp;
 
   /* know always at least one delay */
   /* match type determines which limit set */  
   /* LOOKATME - algorithm implies it is legal to use SDF to set one half */
   /* of recrem but not other - questionable algorithm but matching XL */
   if (sdf_tctyp == TCHK_RECOVERY)
    {
     ogat.g_du = tcp->tclim_du;
     ogat.g_delrep = tcp->tc_delrep;
     strcpy(s2, "recovery");
    }
   else
    {
     ogat.g_du = tcp->tclim2_du;
     ogat.g_delrep = tcp->tc_delrep2;
     strcpy(s2, "removal");
    }
   /* DBG remove -- */
   if (ogat.g_delrep == DT_NONE) __misc_terr(__FILE__, __LINE__);
   /* --- */ 

   /* update the delays */
   sprintf(s1, "%s half of (TIMINGCHECK (%s at %s", sdf_tcnam, s2,
    __bld_lineloc(__xs, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt));

   /* this builds delay into work "gate" place holder */
   if (itp == NULL)
    {
     /* result starts in ogat and also ends up there */
     if (!upd_sdf_perinst_del(&ogat, __sdf_delp, ctmdp, FALSE, 4, FALSE, s1))
      continue;
    }
   else
    {
     /* timing checks can't have logic/bufix toz delays */
     if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp, itp, FALSE, FALSE, s1))
      continue;
     __chg_1inst_del(&ogat, itp, &ngat);
     __free_del(ngat.g_du, ngat.g_delrep, ctmdp->flatinum);
    }
   /* for Verilog $recrem, first limit is recovery and 2nd is removal */
   if (sdf_tctyp == TCHK_RECOVERY)
    {
     tcp->tclim_du = ogat.g_du;  
     tcp->tc_delrep = ogat.g_delrep;
    }
   else if (sdf_tctyp == TCHK_REMOVAL)
    {
     tcp->tclim2_du = ogat.g_du;  
     tcp->tc_delrep2 = ogat.g_delrep;
    }
   else __case_terr(__FILE__, __LINE__);
   if (__sdf_verbose)
    prep_sdftchk_verbmsg(tcp, sdf_tcnam, &ogat, itp, ctmdp, "");
  }
}

/*
 * read common 2 terminals and 1 delay value timing check
 *
 * for (SETUP, (HOLD, (RECOVERY, (REMOVAL, (SKEW 
 * delay put into sdf delp global work vpi delay record
 *
 * notice SDF HOLD terminal order reverse of Verilog so reverse terminals
 * here for matching
 *
 */
static int32 rdset_2term_1v_tchk(struct tclst_t **tclhd, int32 *match_tctyp,
 FILE *f, struct mod_t *ctmdp, char *sdf_tcnam, int32 tchktyp, int32 lcnt,
 int32 *sav_lcnt)
{
 struct tcterm_t reftct, dattct;
 
 *tclhd = NULL;
 /* assume SDF matches same type in Verilog */
 *match_tctyp = tchktyp;
 get_sdftok(f);
 /* this skips COND form, but just get port - source has cond or edge */
 if (!rd_port_tchk(f, &reftct)) return(FALSE);
 if (!rd_port_tchk(f, &dattct)) return(FALSE);

 if (__toktyp != LPAR)
  { dellst_err("TIMINGCHECK", sdf_tcnam); return(FALSE); }

 /* only one delay allowed for these common tchk types */
 if (rd_1_val(f, sdf_tcnam) == -1) return(FALSE);
 if (__toktyp != RPAR) { formend_err(sdf_tcnam); return(FALSE); }
 __sdf_delp->no_of_delays = 1; 

 /* need to be able to emit f errors for first token in form from here on */
 *sav_lcnt = __lin_cnt; 
 __lin_cnt = lcnt;  

 if (port_qual_nam(reftct.tnam, "(TIMINGCHECK first terminal")) return(TRUE);
 if (port_qual_nam(dattct.tnam, "(TIMINGCHECK second terminal")) return(TRUE);

 /* now always return T since syntax good even if annotate fails */ 
 if (reftct.cndnam != NULL)
  {
   if (port_qual_nam(reftct.cndnam, "(TIMINGCHECK reference condition signal"))
    return(TRUE);
  }
 if (dattct.cndnam != NULL)
  {
   if (port_qual_nam(dattct.cndnam, "(TIMINGCHECK data condition signal"))
    return(TRUE);
  }
 /* build list of candidate path matches, nil if none */
 /* edge always included in filter of src-dsts */
 /* SDF hold uses same order as setup but in Verilog reversed, so reverse */
 /* only hold for matching */ 
 if (tchktyp != TCHK_HOLD)
  *tclhd = bld_match_tchk(ctmdp, &reftct, &dattct, tchktyp, sdf_tcnam);
 else *tclhd = bld_match_tchk(ctmdp, &dattct, &reftct, tchktyp, sdf_tcnam);

 /* 10/27/00 SJM - if did not match same , see if can match ver setuphold */ 
 if (*tclhd == NULL && (tchktyp == TCHK_HOLD || tchktyp == TCHK_SETUP))
  {
   /* try to see if can match setuphold */
   /* Verilog setup reversed port order compared to SDF */

   /* AIV 11/11/03 - both Verilog and SDF setuphold have data first */
   /* previous separate hold condition was same */
   *tclhd = bld_match_tchk(ctmdp, &dattct, &reftct, TCHK_SETUPHOLD,
    sdf_tcnam);

   if (*tclhd != NULL) *match_tctyp = TCHK_SETUPHOLD; 
   else
    {
     /* SJM 06/04/01 - if no timinchg checks do not emit error */ 
     if (__no_tchks) goto fail_do_free;

     __pv_ferr(1391,
      "no module %s timing check matches SDF (TIMINGCHECK (%s) - also tried matching $setuphold in Verilog source", 
        ctmdp->msym->synam, sdf_tcnam);
     goto fail_do_free;  
    }
   /* fall thru since know match one or other half of setuphold */
   /* if SDF syntax ok, always return T even if no match */
  }
 /* 01/16/04 SJM - if did not match same , see if can match ver recrem */ 
 if (*tclhd == NULL && (tchktyp == TCHK_RECOVERY || tchktyp == TCHK_REMOVAL))
  {
   /* try to see if can match recrem */
   /* Verilog recovery reversed port order compared to SDF */
   /* AIV 11/11/03 - both Verilog and SDF recrem have data first */
   /* previous separate removal condition was same */
   *tclhd = bld_match_tchk(ctmdp, &dattct, &reftct, TCHK_RECREM,
    sdf_tcnam);
   if (*tclhd != NULL) *match_tctyp = TCHK_RECREM; 
   else
    {
     /* SJM 06/04/01 - if no timinchg checks do not emit error */ 
     if (__no_tchks) goto fail_do_free;

     __pv_ferr(1391,
      "no module %s timing check matches SDF (TIMINGCHECK (%s) - also tried matching $recrem in Verilog source", 
        ctmdp->msym->synam, sdf_tcnam);
     goto fail_do_free;  
    }
   /* fall thru since know match one or other half of setuphold */
   /* if SDF syntax ok, always return T even if no match */
  }

 /* free only the strings allocated inside a tchk term rec */ 
fail_do_free:
 free_tct_insides(&reftct);
 free_tct_insides(&dattct);
 return(TRUE);
}

/*
 * read 1 terminal and 1 delay value timing check
 *
 * for (WIDTH, and (PERIOD
 * delay put into sdf delp global work vpi delay record
 */
static int32 rdset_1term_1v_tchk(struct tclst_t **tclhd, FILE *f,
 struct mod_t *ctmdp, char *sdf_tcnam, int32 tchktyp, int32 lcnt, int32 *sav_lcnt)
{
 struct tcterm_t reftct;
 
 *tclhd = NULL;
 get_sdftok(f);
 /* this skips COND form, but just get port - source has cond or edge */
 if (!rd_port_tchk(f, &reftct)) return(FALSE);

 if (__toktyp != LPAR)
  { dellst_err("TIMINGCHECK", sdf_tcnam); return(FALSE); }

 /* only one delay allowed for these common tchk types */
 if (rd_1_val(f, sdf_tcnam) == -1) return(FALSE);
 if (__toktyp != RPAR) { formend_err(sdf_tcnam); return(FALSE); }
 __sdf_delp->no_of_delays = 1; 

 /* need to be able to emit f errors for first token in form from here on */
 *sav_lcnt = __lin_cnt; 
 __lin_cnt = lcnt;  

 if (port_qual_nam(reftct.tnam, "(TIMINGCHECK first terminal")) return(TRUE);

 /* now always return T since syntax good even if annotate fails */ 
 if (reftct.cndnam != NULL)
  {
   if (port_qual_nam(reftct.cndnam, "(TIMINGCHECK reference condition signal"))
    return(TRUE);
  }
 /* build list of candidate path matches, nil if none */
 /* edge always included in filter of src-dsts */
 *tclhd = bld_match_tchk(ctmdp, &reftct, NULL, tchktyp, sdf_tcnam);

 /* free only the strings allocated inside a tchk term rec */ 
 free_tct_insides(&reftct);
 return(TRUE);
}

/*
 * read 2 terminals, 2 delay values SDF tchk form with optional 2nd and ccond 
 *
 * for (SETUPHOLD, (RECREM, and (NOCHANGE (no scond and cond for this)
 */
static int32 rdset_2term_2v_tchk(struct tclst_t **tclhd, FILE *f,
 struct mod_t *ctmdp, char *sdf_tcnam, int32 tchktyp, int32 lcnt, int32 *sav_lcnt)
{
 int32 seen_scond, seen_ccond;
 struct t_vpi_time tmpda;
 struct tcterm_t reftct, dattct;

 seen_scond = seen_ccond = FALSE;
 /* 10/27/00 SJM - assumes for setup hold matches setuphold not a half */
 *tclhd = NULL;
 get_sdftok(f);
 /* this skips COND form, but just get port - source has cond or edge */
 if (!rd_port_tchk(f, &reftct)) return(FALSE);
 if (!rd_port_tchk(f, &dattct)) return(FALSE);

 if (__toktyp != LPAR)
  { dellst_err("TIMINGCHECK", sdf_tcnam); return(FALSE); }

 /* exactly two delay required */
 if (rd_1_val(f, sdf_tcnam) == -1) return(FALSE); 
 if (__toktyp != LPAR)
  {
   __pv_ferr(1239, "(TIMINGCHECK (%s two delays required", sdf_tcnam);
  }
 tmpda = __sdf_delp->da[0];
 if (rd_1_val(f, sdf_tcnam) == -1) return(FALSE); 
 /* now set first and 2nd delays t_vpi_delay records */
 __sdf_delp2->da[0] = __sdf_delp->da[0];
 __sdf_delp->da[0] = tmpda;
 __sdf_delp->no_of_delays = 1;
 __sdf_delp2->no_of_delays = 1;

 /* (SSCOND and (CCOND can appear but no meaning in Verilog */
 /* and not needed for matching */
 if (__toktyp == LPAR)
  {
read_cond:
   get_sdftok(f);
   if (__toktyp == SDF_SCOND)
    {
     if (seen_scond)
      {
       __pv_ferr(1362, "(TIMINGCHECK (%s only one (SCOND allowed", sdf_tcnam); 
      }
     else seen_scond = TRUE;
    }
   else if (__toktyp == SDF_CCOND)
    {
     if (seen_scond)
      {
       __pv_ferr(1362, "(TIMINGCHECK (%s only one (CCOND allowed", sdf_tcnam); 
      }
     else seen_ccond = TRUE;
    }
   /* this reads ending ')' */
   if (!sdf_skip_form(f)) return(FALSE);
   get_sdftok(f);
   if (__toktyp == LPAR) goto read_cond;
  }
 if (__toktyp != RPAR) { formend_err(sdf_tcnam); return(FALSE); }

 /* need to be able to emit f errors for first token in form from here on */
 *sav_lcnt = __lin_cnt; 
 __lin_cnt = lcnt;  

 if (port_qual_nam(reftct.tnam, "(TIMINGCHECK first terminal")) return(TRUE);
 if (port_qual_nam(dattct.tnam, "(TIMINGCHECK second terminal")) return(TRUE);

 /* now always return T since syntax good even if annotate fails */ 
 if (reftct.cndnam != NULL)
  {
   if (port_qual_nam(reftct.cndnam, "(TIMINGCHECK reference condition signal"))
    return(TRUE);
  }
 if (dattct.cndnam != NULL)
  {
   if (port_qual_nam(dattct.cndnam, "(TIMINGCHECK data condition signal"))
    return(TRUE);
  }
 /* build list of candidate path matches, nil if none */
 /* edge always included in filter of src-dsts */
 if (tchktyp == TCHK_SETUPHOLD)
  {
   /* AIV 11/11/03 - setuphold SDF has data terminal first but it */
   /* much match Verilog where ref terminal is first */
   /* i.e. the SDF ref terminal is really the 2nd one in SDF file */
   *tclhd = bld_match_tchk(ctmdp, &dattct, &reftct, tchktyp, sdf_tcnam);
  }
 else if (tchktyp == TCHK_RECREM)
  {
   /* AIV 11/11/03 - recrem SDF has data terminal first but it */
   /* much match Verilog where ref terminal is first */
   /* i.e. the SDF ref terminal is really the 2nd one in SDF file */
   *tclhd = bld_match_tchk(ctmdp, &dattct, &reftct, tchktyp, sdf_tcnam);
  }
 else *tclhd = bld_match_tchk(ctmdp, &reftct, &dattct, tchktyp, sdf_tcnam);

 /* free only the strings allocated inside a tchk term rec */ 
 free_tct_insides(&reftct);
 free_tct_insides(&dattct);
 return(TRUE);
}

/*
 * wrapper to prepare and call tchk sdf verbose tracing message
 */
static void prep_sdftchk_verbmsg(struct tchk_t *tcp, char *tcnam,
 struct gate_t *ogp, struct itree_t *itp, struct mod_t *mdp, char *limnam)
{
 int32 ii;
 struct itree_t *itp2;
 char s1[RECLEN], s2[RECLEN];

 if (itp == NULL)
  {
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp2 = mdp->moditps[ii];
     __push_itstk(itp2);
     sprintf(s1, "%s(%s) from '*'", __msg2_blditree(s2, itp2),
      mdp->msym->synam);
     emit_sdftchk_verbmsg(tcp, tcnam, ogp, s1, limnam);
     __pop_itstk();
    }
  } 
 else
  {
   __push_itstk(itp);
   sprintf(s1, "%s(%s)", __msg2_blditree(s2, itp), mdp->msym->synam);
   emit_sdftchk_verbmsg(tcp, tcnam, ogp, s1, limnam);
   __pop_itstk();
  }
}

/*
 * emit sdf timing check limit verbose tracing message 
 */
static void emit_sdftchk_verbmsg(struct tchk_t *tcp, char *tcnam,
 struct gate_t *ogp, char *celloc, char *lim)
{
 char s1[RECLEN], s2[RECLEN];

 __cv_msg("  SDF **%s(%d): (TIMINGCHECK %s %slimit set to %s in %s at %s\n",
  __cur_fnam, __lin_cnt, tcnam, lim, __bld_delay_str(s2, ogp->g_du,
  ogp->g_delrep), celloc, __bld_lineloc(s1, tcp->tcsym->syfnam_ind,
  tcp->tcsym->sylin_cnt));
}

/*
 * read a time check port reference
 * assume first token read and reads one past last 
 *
 * tricky because (COND [tchk cond. expr] [port spec]) possible
 * nnam only for cond 
 * other possibility just [port spec]
 * where [port spec] can be (edge [port ref.]) or [port ref.]
 */
static int32 rd_port_tchk(FILE *f, struct tcterm_t *tctp)
{
 char pnam[IDLEN];
 int32 i1, i2, eval, ettyp;

 tctp->ti1 = tctp->ti2 = -1;
 tctp->cndnam = NULL;
 tctp->cndi1 = tctp->cndi2 = -1;
 tctp->cnd_op = UNDEF;
 tctp->cnd_const = -1;
 tctp->eval = NOEDGE;

 if (__toktyp == LPAR) 
  {
   /* collects ID (maybe strange edge) into __token */
   ettyp = rd_edge_ident(f);
   /* if (COND form contains port tchk */
   if (ettyp == -1 && __toktyp == SDF_COND)
    return(rd_tchk_cond(f, tctp));
   /* port_edge */
   if (ettyp == -1)
    {
     __pv_ferr(1386, "port_edge edge expected - %s read", prt_sdftok());
     return(FALSE);
    }
   tctp->eval = ettyp;
   get_sdftok(f);
   if (!rd_port_spec(f, pnam, &i1, &i2, &eval, TRUE)) return(FALSE);
   tctp->tnam = __pv_stralloc(pnam); 
   tctp->ti1 = i1;
   tctp->ti2 = i2;
   tctp->eval = eval;
   if (__toktyp != RPAR)
    {
     __pv_ferr(1363, "port_edge ending ) expected - %s read", prt_sdftok());
     return(FALSE);
    }
   get_sdftok(f);
   return(TRUE);
  }
 /* port_instance */
 if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
 tctp->tnam = __pv_stralloc(pnam);
 tctp->ti1 = i1;
 tctp->ti2 = i2;
 return(TRUE);
}

/*
 * read a timing_check_condition into tcterm record
 *
 * sets sdf globals
 * know (COND read and reads final port spec and ending ) 
 * record good only if returns T
 */
static int32 rd_tchk_cond(FILE *f, struct tcterm_t *tctp)
{
 char labnam[IDLEN], nam[IDLEN];
 int32 ni1, i1, i2, eval;

 get_sdftok(f);
 /* save literal string "label" but for now not used */
 if (__toktyp == LITSTR) { strcpy(labnam, __token); get_sdftok(f); }
 /* expression can have up to 3 term of certain simple form only */  
 tctp->cnd_op = UNDEF;
 tctp->cnd_const = -1;
 if (__toktyp == BITNOT || __toktyp == NOT) 
  {
   tctp->cnd_op = __toktyp;
   get_sdftok(f);
   if (__toktyp != ID)
    {
     __pv_ferr(1394,
      "timing_check_condition unary operator following identifier expected - %s read",
      prt_sdftok());
     return(FALSE);
    }
   if (!rd_scalar_node(f, nam, &ni1)) return(FALSE); 
   tctp->cndnam = __pv_stralloc(nam);
   tctp->cndi1 = tctp->cndi2 = ni1;
  }
 else if (__toktyp == ID)
  {
   if (!rd_scalar_node(f, nam, &ni1)) return(FALSE); 
   tctp->cndnam = __pv_stralloc(nam);
   
   if (__toktyp == RELEQ || __toktyp == RELCEQ || __toktyp == RELNEQ
    || __toktyp == RELCNEQ) 
    {
     tctp->cnd_op = __toktyp;
     if ((tctp->cnd_const = rd_scalar_const(f)) == -1) return(FALSE);
     get_sdftok(f);
    }
  }
 else
  {
   __pv_ferr(1356, "timing_check_condition expression expected - %s read",
    prt_sdftok());
   return(FALSE);
  }
 if (!rd_port_spec(f, nam, &i1, &i2, &eval, TRUE)) return(FALSE);
 tctp->tnam = __pv_stralloc(nam);
 tctp->ti1 = i1;
 tctp->ti2 = i2;
 tctp->eval = eval; 
 if (__toktyp != RPAR)
  {
   __pv_ferr(1367, "timing_check_cond ending ) expected - %s read",
    prt_sdftok());
   return(FALSE);
  }
 get_sdftok(f);
 return(TRUE);
}

/*
 * read a scalar node
 *
 * read and set global for a scalar (ID or bit select node)
 * this can not be qualified path and emits its own error message
 *
 * know scalar ID read and reads one past end
 */
static int32 rd_scalar_node(FILE *f, char *nnam, int32 *i1)
{
 int32 i2;

 *i1 = -1;
 if (__id_qualpath)
  {
   __pv_ferr(1245, "scalar node qualified path %s illegal", __token);
   return(FALSE);
  }
 /* part select illegal */
 if (!chkcnv_sdfid(nnam, i1, &i2, __token, TRUE) || *i1 != i2)
  {
   __pv_ferr(1227,
    "scalar node %s illegal Verilog identifier or illegal part select",
    __token);
   return(FALSE);
  }
 get_sdftok(f);
 return(TRUE);
}

/*
 * convert from SDF timing check token type to internal tchk number
 * returns -1 on error
 */
static int32 from_sdf_tctyp(int32 sdf_tctyp)
{
 switch ((byte) sdf_tctyp) {
  case SDF_SETUP: return(TCHK_SETUP);
  case SDF_HOLD: return(TCHK_HOLD);
  case SDF_RECOVERY: return(TCHK_RECOVERY);
  case SDF_SKEW: return(TCHK_SKEW);
  case SDF_SETUPHOLD: return(TCHK_SETUPHOLD);
  case SDF_NOCHANGE: return(TCHK_NOCHANGE);
  case SDF_WIDTH: return(TCHK_WIDTH); 
  case SDF_PERIOD: return(TCHK_PERIOD);
  /* SJM 12/15/03 - added new 2001 LRM time checks */
  case SDF_FULLSKEW: return(TCHK_FULLSKEW);
  case SDF_REMOVAL: return(TCHK_REMOVAL);
  case SDF_RECREM: return(TCHK_RECREM);
  case SDF_TIMESKEW: return(TCHK_TIMESKEW);
 }
 return(-1);
}

/*
 * build a list of matching timing checks
 *
 * rule is that missing SDF is treated as wildcard (all match) but if
 * present in SDF must match exactly (including path has edge)
 * idea: only as much SDF constructs as needed must be code in SDF file 
 *
 * sdf tc nam is SDF name for timing check, tc typ is internal tchk const
 * know line count is beginning of this ([tchk name] form
 *
 * know reftctp always set but dattctp may be nil
 */
static struct tclst_t *bld_match_tchk(struct mod_t *ctmdp,
 struct tcterm_t *reftctp, struct tcterm_t *dattctp, int32 tctyp,
 char *sdf_tcnam)
{
 int32 tci1, tci2;
 int32 rv, rv2;
 struct tchk_t *tcp;
 struct tclst_t *tclp, *tclhd, *tclend;
 struct net_t *np;
 char s1[RECLEN]; 

 /* SJM 09/26/99 - allow no matching of timing checks if +notimingchecks */
 /* option selected */ 
 if (__no_tchks) return(NULL);

 if (ctmdp->mspfy == NULL)
  {
   /* ports can be any type */
   sprintf(s1, "(TIMINGCHECK (%s [ref.]", sdf_tcnam); 
   not_a_port(reftctp->tnam, IO_BID, ctmdp, s1);
   if (dattctp != NULL)
    {
     sprintf(s1, "(TIMINGCHECK (%s [data]", sdf_tcnam); 
     not_a_port(dattctp->tnam, IO_BID, ctmdp, s1);
    }

   __pv_ferr(1396, "unable to match (TIMINGCHECK (%s in type %s - no specify section", 
    sdf_tcnam, ctmdp->msym->synam);
   return(NULL);
  }

 /* build list of matching source-dest but ignore cond or condelse for now */ 
 tclhd = tclend = NULL;
 for (tcp = ctmdp->mspfy->tchks; tcp != NULL; tcp = tcp->tchknxt)
  {
   /* always ignore gone (can they happen?) and added setup hold half */
   /* and added rec rem half */
   if (tcp->tc_gone || tcp->tc_supofsuphld || tcp->tc_recofrecrem) continue;

   /* step 1: obviously must match timing check type */
   if (tcp->tchktyp != tctyp) continue;

   /* step 2: match ref and dat name and range */
   /* since know constant select or wire can never fail */
   __xtract_wirng(tcp->startxp, &np, &tci1, &tci2);

   /* ??? RELEASE REMOVEME --
   __cv_msg("... trying to match Verilog ref %s[%d:%d] to SDF %s[%d:%d]\n",
    np->nsym->synam, tci1, tci2, reftctp->tnam, reftctp->ti1, reftctp->ti2);
   --- */

   if (strcmp(np->nsym->synam, reftctp->tnam) != 0) continue;
   if (tci1 != reftctp->ti1 || tci2 != reftctp->ti2) continue;

   if (dattctp != NULL)
    {
     __xtract_wirng(tcp->chkxp, &np, &tci1, &tci2);
     /* ??? RELEASE REMOVEME ---
     __cv_msg("... trying to match Verilog data %s[%d:%d] to SDF %s[%d:%d]\n",
      np->nsym->synam, tci1, tci2, dattctp->tnam, dattctp->ti1, dattctp->ti2);
     --- */
     if (strcmp(np->nsym->synam, dattctp->tnam) != 0) continue;
     if (tci1 != dattctp->ti1 || tci2 != dattctp->ti2) continue;
    }

   /* step 3: match 2 edge, but no SDF edge (either) means match all */ 
   /* i.e. if SDF has edge but tchk does not have corresonding, no match */
   if (reftctp->eval != NOEDGE)
    { if (reftctp->eval != tcp->startedge) continue; } 
   if (dattctp != NULL && dattctp->eval != NOEDGE)
    { if (dattctp->eval != tcp->chkedge) continue; } 

   /* step 4: if SDF condition (either terminal), must match */
   /* if no SDF condition matches all including cond's */  
   if (reftctp->cndnam != NULL)
    { if (!same_tchk_cond(reftctp, tcp->startcondx)) continue; }
   if (dattctp != NULL && dattctp->cndnam != NULL)
    { if (!same_tchk_cond(dattctp, tcp->chkcondx)) continue; }

   /* have match */
   tclp = (struct tclst_t *) __my_malloc(sizeof(struct tclst_t));
   tclp->tcp = tcp;
   tclp->tclnxt = NULL; 
   if (tclend == NULL) tclhd = tclend = tclp;
   else { tclend->tclnxt = tclp; tclend = tclp; }
  }
 if (tclhd == NULL)
  {
   /* ports can be any */
   sprintf(s1, "(TIMINGCHECK (%s [ref.]", sdf_tcnam); 
   rv = not_a_port(reftctp->tnam, IO_BID, ctmdp, s1);
   
   if (dattctp != NULL)
    {
     sprintf(s1, "(TIMINGCHECK (%s [data]", sdf_tcnam); 
     rv2 = not_a_port(dattctp->tnam, IO_BID, ctmdp, s1);
    }
   else rv2 = FALSE;
   if (rv || rv2) return(NULL); 

   /* 10/27/00 SJM - no error if setup or hold, error only if after also */
   /* trying to match setuphold, not found */
   if (tctyp == TCHK_SETUP || tctyp == TCHK_HOLD) return(NULL);
   /* 01/16/04 SJM - also not error if recovery or removal */
   if (tctyp == TCHK_RECOVERY || tctyp == TCHK_REMOVAL) return(NULL);

   __pv_ferr(1391, "no module %s timing check matches SDF (TIMINGCHECK (%s)", 
    ctmdp->msym->synam, sdf_tcnam);
   /* falls thru and correctly return nil */
  }
 return(tclhd);
}

/*
 * compare a tc term condition (know exists) against tchk condx (expr.)
 * returns T on match else F
 */
static int32 same_tchk_cond(struct tcterm_t *tctp, struct expr_t *condxp)
{
 int32 i1, i2, cval; 
 word32 *wp;
 struct net_t *np;
 struct expr_t *xp;

 if ((xp = condxp) == NULL) return(FALSE);
 switch (xp->optyp) {
  case ID:
   if (tctp->cnd_op != UNDEF || tctp->cnd_const != -1) return(FALSE);

chk_id:
   if (tctp->cndi1 != -1 || tctp->cndi2 != -1) return(FALSE);
   np = xp->lu.sy->el.enp;
   if (strcmp(tctp->cndnam, np->nsym->synam) != 0) return(FALSE);
   break; 
  case LSB:
   if (tctp->cnd_op != UNDEF || tctp->cnd_const != -1) return(FALSE);

chk_bsel:
   if (xp->ru.x->optyp != NUMBER) __case_terr(__FILE__, __LINE__);
   __xtract_wirng(xp, &np, &i1, &i2);
   if (strcmp(tctp->cndnam, np->nsym->synam) != 0) return(FALSE);
   if (i1 != tctp->cndi1 || i2 != tctp->cndi2) return(FALSE);
   break; 
  case BITNOT:
   if (tctp->cnd_op != BITNOT || tctp->cnd_const != -1) return(FALSE);
   xp = condxp->lu.x; 
do_scalar_var:
   if (xp->optyp == ID) goto chk_id;
   if (xp->optyp == LSB) goto chk_bsel;
   /* not sure if legal, but can never match SDF in any case */
   return(FALSE);
  case NOT: 
   if (tctp->cnd_op != NOT || tctp->cnd_const != -1) return(FALSE);
   xp = condxp->lu.x; 
   goto do_scalar_var;
  case RELCEQ: case RELEQ: case RELCNEQ: case RELNEQ:
   if (tctp->cnd_op != (int32) xp->optyp) return(FALSE); 
   if (xp->ru.x->szu.xclen != 1) __misc_terr(__FILE__, __LINE__);
   wp = &(__contab[xp->ru.x->ru.xvi]);
   if (wp[1] != 0L) __misc_terr(__FILE__, __LINE__);
   cval = (int32) wp[0];

   if (cval != 0 && cval != 1) __misc_terr(__FILE__, __LINE__);
   if (cval != tctp->cnd_const) return(FALSE);
   xp = condxp->lu.x; 
   goto do_scalar_var;
  /* according to LRM, wider expr where just low bit used legal */
  /* can never match an SDF condition expr. */
  default: return(FALSE);
 } 
 return(TRUE);
}

/*
 * free a tchk list
 */
static void free_tclst(struct tclst_t *tclhd)
{
 struct tclst_t *tclp, *tclp2;

 for (tclp = tclhd; tclp != NULL;)
  {
   tclp2 = tclp->tclnxt;
   __my_free(tclp, sizeof(struct tclst_t));
   tclp = tclp2;
  }
}

/*
 * free insides only (strings) from a tchk terminal record
 */
static void free_tct_insides(struct tcterm_t *tctp)
{
 if (tctp->tnam != NULL) __my_free(tctp->tnam, strlen(tctp->tnam) + 1);
 if (tctp->cndnam != NULL) __my_free(tctp->cndnam, strlen(tctp->cndnam) + 1);
}

/*
 * MIPD PORT ROUTINES
 */

/*
 * read and set MIPD delays for (PORT form
 *
 * here port can and will usually be qualified name
 */
static int32 rdset_port_mipd(FILE *f, struct itree_t *itp, struct mod_t *ctmdp,
 char *formnam)
{
 int32 ii, sav_lcnt, lcnt, si1, si2, ndels, none_set;
 struct itree_t *itp2;
 char qualport[IDLEN];

 get_sdftok(f);
 lcnt = __lin_cnt;
 /* this can and usually will be qualified name */
 if (!rd_port(f, qualport, &si1, &si2)) return(FALSE);
 if (__toktyp != LPAR) { dellst_err(formnam, "PORT"); return(FALSE); }
 get_sdftok(f);
 /* know at least one read or returns -1 and emits error */
 /* this reads (PORT form ending ) */
 if ((ndels = rd_sdf_dellst(f, "PORT"))== -1) return(FALSE);

 /* need to be able to emit f errors for first token in form from here on */
 sav_lcnt = __lin_cnt; 
 __lin_cnt = lcnt;  

 /* except for next 2 fields all t_vpi_delay fields fixed in SDF */
 __sdf_delp->no_of_delays = ndels; 
 if (strcmp(formnam, "INCREMENT") == 0) __sdf_delp->append_flag = TRUE;
 else __sdf_delp->append_flag = FALSE;

 if (itp == NULL)
  {
   for (none_set = TRUE, ii = 0; ii < ctmdp->flatinum; ii++)
    {
     itp2 = ctmdp->moditps[ii];
     if (__sdf_cntxt_itp != NULL && !itp_under_cntxt(itp2)) continue;

     none_set = FALSE;
     set_mipd_dels(itp2, qualport, si1, si2);
    }
   if (none_set)
    {
     __pv_fwarn(670,
      "no MIPD delays changed because no instance of type %s in context", 
      ctmdp->msym->synam); 
    }
  }
 else set_mipd_dels(itp, qualport, si1, si2);

 __lin_cnt = sav_lcnt;  
 return(TRUE);
}


/*
 * set/update MIPD delays - used by (PORT 
 *
 * uses already set global sdf_del table
 * here port can be xmr path if range already extracted
 *
 * range here optional - if not present uses port width 
 * MIPD delays are 16 value (both old and new used in get del)
 * know this called just before sim, i.e. n lds lists built
 *
 * SJM 02/15/08 - FIXME??? - think no longer possible for itp to be nil
 * (all insts wild card form)
 */
static void set_mipd_dels(struct itree_t *itp, char *qualport, int32 si1,
 int32 si2)
{
 int32 ndx, fr, to, bi;
 struct tenp_t *prtnetmap;
 struct mipd_t *mipdp;
 struct net_t *np;
 struct itree_t *itp2;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 struct gate_t ogat, ngat;
 char port[IDLEN], s1[RECLEN];

 /* setting to one instance case - this get instance only */
 if (!xtrct_portdev(&itp2, port, qualport, itp, "PORT", "PORT")) return;
 mdp = itp2->itip->imsym->el.emdp;

 /* SJM 07/10/01 - now allowing MIPD delays on input and inout ports */
 if ((mpp = get_inport_fr_nam(mdp, port)) == NULL
  && (mpp = get_bidport_fr_nam(mdp, port)) == NULL)
  { 
   if (vpi_delay_all0s(__sdf_delp))
    {
     /* SJM 07/10/01 - ignore cases with 0 delay - it is what XL does */
     __finform(3002,
      "SDF (PORT form port %s is not an input or inout port of module %s but ignored because delays all 0",
      port, mdp->msym->synam);
    }
   else if ((mpp = get_outport_fr_nam(mdp, port)) != NULL)
    {
     /* SJM 02/15/08 - new use gate driver (DEVICE delay for interconnect */
     /* destination as out port wild card all instance form impossible */
     /* (has no meaning) */
     if (itp == NULL)
      {
       __pv_ferr(1504,
        "SDF (PORT output port %s in %s (DEVICE delay annotate wild card (*) form illegal\n",
        port, mdp->msym->synam);
       return; 
      }
     /* SJM 02/15/08 - following other simulators (PORT or (INTERCONNECT */
     /* delay dest can now also be output port providing output port has one */
     /* drvr algorithm searches down through mod out ports finding real drvr */
     /* SJM 02/18/08 - for now only allow 1 bit - bit select ok */
     if (mpp->mpref->optyp != ID)
      {
       __pv_ferr(1505,
        "SDF (PORT output port %s in %s (DEVICE delay annotate must be identfier\n",
        port, mdp->msym->synam);
      }
     np = mpp->mpref->lu.sy->el.enp;
     /* SJM 02/18/08 - also must be 1 bit - scalar or si1 equal to si2 */ 
     /* for scalar si1 = si2 = -1 */
     if (np->n_isavec && (si1 == -1 || si1 != si2))  
      { 
       __pv_ferr(1506,
        "SDF (PORT output port %s in %s (DEVICE delay annotate must be 1 bit wide\n",
        port, mdp->msym->synam);
       return;
      }
    
     try_find_set_intercon_prim_del(mpp, si1, mdp, itp2, "(PORT");
    }
   else 
    {
     __pv_ferr(1384,
      "SDF (PORT form port %s is not an input or inout port of module %s",
      port, mdp->msym->synam);
    }
   return;
  }

 /* LOOKATME - assuming vector ports require ranges */
 if (si1 == -1)
  {
   if (mpp->mpwide != 1) { fr = mpp->mpwide - 1; to = 0; } else fr = to = 0;
  }
 else { fr = si1; to = si2; } 

 prtnetmap = NULL;
 /* build the MIPD d.s. if needed */
 if (!mpp->has_mipd) 
  {
   /* if setting 0 del (always only 1 inst.) and none before no need to add */ 
   /* if later other inst. needs will be set then */
   if (vpi_delay_all0s(__sdf_delp))
    {
     __num_rem_mipds += (fr - to) + 1; 
     return;
    }
   /* must allocate for all nets that connect to port - not just rng */
   prtnetmap = __bld_portbit_netbit_map(mpp);
   for (ndx = 0; ndx < mpp->mpwide; ndx++)
    {
     np = prtnetmap[ndx].tenu.np;
     /* LOOKATME - think unc not possible here */
     if (np == NULL || (np->nlds != NULL && np->nlds->npntyp == NP_MIPD_NCHG))
      continue;

     /* allocate path for every connected net */ 
     __add_alloc_mipd_npp(np, mdp);
    }

   /* add the per bit mipd npp and set all bits to no IMPD */
   mdp->mod_has_mipds = TRUE;
   mpp->has_mipd = TRUE; 
  }

 if (prtnetmap == NULL) prtnetmap = __bld_portbit_netbit_map(mpp);
 sprintf(s1, "(PORT %s in %s", port, mdp->msym->synam);
 for (ndx = fr; ndx >= to; ndx--)
  {
   np = prtnetmap[ndx].tenu.np;
   bi = prtnetmap[ndx].nbi;

   /* DBG remove -- */
   if (np->nlds == NULL || np->nlds->npntyp != NP_MIPD_NCHG)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   mipdp = &(np->nlds->elnpp.emipdbits[bi]);

   /* if no active mipd for this net/bit, must enable with 0 delay */
   if (mipdp->no_mipd) __setup_mipd(mipdp, np, mdp->flatinum);

   ogat.g_du = mipdp->pb_mipd_du;
   ogat.g_delrep = mipdp->pb_mipd_delrep;

   /* change bit in every instance if all insts * form */
   if (itp == NULL)
    { 
     /* result starts in ogat moves to ngat then finally put back in ogat */
     if (!upd_sdf_perinst_del(&ogat, __sdf_delp, mdp, TRUE, FALSE, 4, s1))
      continue;
    }
   else
    {
     /* mipd delays can't have logic/bufix toz delays */
     if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp, itp2, TRUE, FALSE, s1))
      continue;
     if (ngat.g_delrep == DT_4V)
      {
       if (ngat.g_du.d4v[0] < ngat.g_du.d4v[1])
        ngat.g_du.d4v[3] = ngat.g_du.d4v[0];
       else ngat.g_du.d4v[3] = ngat.g_du.d4v[1];
      }
     __chg_1inst_del(&ogat, itp2, &ngat);
     __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
    }
   mipdp->pb_mipd_du = ogat.g_du; 
   mipdp->pb_mipd_delrep = ogat.g_delrep; 
   if (__sdf_verbose)
    {
     char s2[RECLEN], s3[RECLEN];

     if (mpp->mpwide > 1) sprintf(s1, " bit %d", ndx); else strcpy(s1, "");
     __push_itstk(itp2);
     __cv_msg("  SDF **%s(%d): (PORT %s%s MIPD set to %s (in %s type %s)\n", 
      __cur_fnam, __lin_cnt,
      msgpref_tostr(__xs, mpp), s1, __bld_delay_str(s2, ogat.g_du,
      ogat.g_delrep), __msg2_blditree(s3, itp2), mdp->msym->synam);
     __pop_itstk();
    }
  }
 __my_free(prtnetmap, mpp->mpwide*sizeof(struct tenp_t));
}

/*
 * routine to set SDF device delay for an SDF interconnect or port delay on
 * one bit gate (or udp) (1 bit conta is a gate) driving the output port
 *
 * know mpp is an output port
 *
 * SJM 02/18/08 - NEW ALGORTHM since SDF (INTERCONNECT form does not exactly
 * fit any one Verilog construct, usually mapped to MIPD delay but if
 * (INTERCONNECT destination not input or inout now maps to (DEVICE delay 
 * on gate driving the output path (similar to normal Verilog path delay
 * but ignores the input since not intra-module
 *
 * for (PORT delays if source not an input but dest an output/inout uses
 * normal MIDP delay - since Cver interconnect delays are always MIPD (no
 * src-dst delays for (INTERCONNECT (inter-module) delays, either (DEVICE
 * or MIPD same effect
 */
static void try_find_set_intercon_prim_del(struct mod_pin_t *mpp, int32 i1,
 struct mod_t *mdp, struct itree_t *itp, char *sdfkw)
{
 struct net_pin_t *npp;
 struct gate_t *gp;
 struct itree_t *in_itp;

 in_itp = itp;
 npp = find_intercon_gate_drvr(&(in_itp), mpp, i1, mdp, sdfkw);
 if (npp == NULL) return;

 gp = npp->elnpp.egp;
 set_device_del(in_itp, gp, mdp->msym);
}

/*
 * routine to find gate/udp driving a net 
 *
 * if first down hard driver (not an output port) is not a gate/udp/conta
 * emits error 
 */
static struct net_pin_t *find_intercon_gate_drvr(struct itree_t **in_itp,
 struct mod_pin_t *mpp, int32 i1, struct mod_t *mdp, char *sdfkw)
{
 struct net_t *np;
 struct net_pin_t *npp;
 char s1[RECLEN];

 if (mpp->mpref->optyp != ID)
  {
   bld_interconn_drv_emsg(s1, mpp, mdp);
   __pv_ferr(1505,
    "SDF %s destination out port %s annotated as device illegal non scalar\n",
     sdfkw, s1);
   return(NULL);
  }
 np = mpp->mpref->lu.sy->el.enp;
 if (np->n_multfi)
  {
   bld_interconn_drv_emsg(s1, mpp, mdp);
   __pv_ferr(1507,
    "SDF %s destination out port %s annotated as (DEVICE delay multiple drivers illegal\n",
    sdfkw, s1);
   return(NULL); 
  }
 npp = fnd_xlflat_one_gate_drvr(np, i1, in_itp); 
 if (npp == NULL)
  {
   bld_interconn_drv_emsg(s1, mpp, mdp);
   __pv_ferr(1509,
    "SDF %s destination out port %s annotated as (DEVICE delay does not have flattened gate driver\n",
    sdfkw, s1);
   return(NULL);
  }
 return(npp);
}

/*
 * build a interconnect driver descend error message
 */
static char *bld_interconn_drv_emsg(char *s, struct mod_pin_t *mpp,
 struct mod_t *mdp)
{
 char s1[RECLEN];

 sprintf(s, "port %s in %s", msgpref_tostr(s1, mpp), mdp->msym->synam);
 return(s);
}

/*
 * routine to find the one gate driver given a one bit output port
 * (maybe net[bit] type)
 */
static struct net_pin_t *fnd_xlflat_one_gate_drvr(struct net_t *np,
 int32 bi, struct itree_t **in_itp)
{
 int32 vti, vtxnum, bi2;
 struct xldlvtx_t *xldlvp;
 struct net_pin_t *npp, *gate_npp;
 struct itree_t *itp;

 /* this build the list of (net,bit,itree loc) of all drivers of this net */
 /* know non multi-fan-in output port so can just find the one gate driver */
 itp = *in_itp;
 vtxnum = __bld_xl_drvld_vtxtab(np, bi, itp, FALSE);
 if (vtxnum == 0) return(NULL);

 gate_npp = NULL;
 /* SJM 06-25-13 - idea here is that matches bits so there can be only */
 /* one overlapping rng - multiple drvrs on net for vector net possible */
 /* but for each bit only one */
 
 for (vti = 0; vti < vtxnum; vti++)
  {
   xldlvp = __xldlvtxind[vti];
   /* DBG remove -- */
   if (xldlvp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
  
   np = xldlvp->dlnp;
   bi2 = xldlvp->dlbi;

   npp = find_gate_drvr(np->ndrvs, np, bi2); 
   if (npp == NULL) continue;
   if (gate_npp != NULL) __misc_terr(__FILE__, __LINE__); 
   gate_npp = npp;
   *in_itp = xldlvp->dlitp;
   
   npp = find_gate_drvr(npp->npnxt, np, bi2); 
   if (npp != NULL) __misc_terr(__FILE__, __LINE__);

   __my_free(xldlvp, sizeof(struct xldlvtx_t));
   __xldlvtxind[vti] = NULL;
  }
 __num_xldlvtxs = 0;
 /* SJM - 06-25-13 misc terr was wrong since it is possible for some bits */
 /* no not have drivers, but if so SDF is wrong but just ignore */
 if (gate_npp == NULL)
  {
   __pv_fwarn(678,
    "(DEVICE or (INTERCONNECT flattened gate driver of %s does not have a driverfor bit %d",
    np->nsym->synam, bi);
  }
 return(gate_npp);
}

/*
 * given a net bit - find a gate driver if present
 */
static struct net_pin_t *find_gate_drvr(struct net_pin_t *nxt_npp,
 struct net_t *np, int32 bi)
{
 int32 bi1, bi2;
 struct net_pin_t *npp;

 for (npp = nxt_npp; npp != NULL; npp = npp->npnxt)
  {
   __get_bidnpp_sect(np, npp, &(bi1), &(bi2));
   if (bi == -1 || (bi <= bi1 && bi >= bi2))
    {
     /* range matches - see if gate driver */
     if (npp->npntyp == NP_GATE) return(npp);
    }
  }
 return(NULL);
}

/*
 * build a port expr. for tracing
 */
static char *msgpref_tostr(char *s, struct mod_pin_t *mpp)
{
 char s1[RECLEN];

 if (mpp->mp_explicit)
  {
   if (mpp->mpref->optyp == ID
    && strcmp(mpp->mpsnam, mpp->mpref->lu.sy->synam) == 0)
    strcpy(s, mpp->mpsnam);
   /* un-named but explicit module port stored wrong */
   else sprintf(s, ".%s(%s)", mpp->mpsnam, __msgexpr_tostr(s1, mpp->mpref));
  }
 else __msgexpr_tostr(s, mpp->mpref); 
 return(s); 
}

/*
 * find one "underneath" instance of given type
 * return nil if none
 */
static struct itree_t *find_1under_itp(struct mod_t *ctmdp)
{
 int32 ii;
 struct itree_t *itp;

 /* if top level context, any will do, know at least one */
 if (__sdf_cntxt_itp == NULL) return(ctmdp->moditps[0]);
 else
  {
   for (ii = 0; ii < ctmdp->flatinum; ii++)
    {
     itp = ctmdp->moditps[ii];
     if (itp_under_cntxt(itp)) return(itp);
    }
  } 
 /* no types in this context */
 return(NULL);
}

/*
 * extract a (possibly qualified) port or device name
 * and set instance object in
 *
 * inst '*' form and xmr port reference do not make sense - so an
 * error is emitted
 * select of last component allowed
 */
static int32 xtrct_portdev(struct itree_t **itp2, char *nam, char *qualport,
 struct itree_t *itp, char *formnam, char *onam)
{
 struct expr_t *glbndp;
 struct sy_t *tailsyp;
 char s1[RECLEN];

 if (itp == NULL)
  {
   __pv_ferr(1201,
    "(%s hierarchical %s name %s illegal with (INSTANCE *) form - type unknown",
    formnam, onam, qualport);
   return(FALSE);
  }

 /* case 1, simple name (no path), just check and copy - this can have range */
 if (!port_qual_nam(qualport, (char *) NULL))
  {
   *itp2 = itp;
   strcpy(nam, qualport);
   return(TRUE);
  }

 /* case 2: qualified name */
 /* need to use interactive global context here */
 __push_wrkitstk(__sdf_mdp, 0);
 if ((glbndp = __glbnam_to_expr(qualport)) == NULL)
  {
   __pop_wrkitstk();
   return(FALSE);
  }

 /* find downward itree loc */
 *itp2 = get_sdfdownrel_itp(glbndp, itp, &tailsyp, s1);
 /* done with glb ndp thru this code path */
 __free_xtree(glbndp);
 __pop_itstk();

 if (*itp2 == NULL)
  {
   __pv_ferr(1388, "(%s form %s qualified name %s illegal in context %s: %s",
    formnam, onam, qualport, get_sdfcntxtnam(__xs, itp), s1);
   return(FALSE);
  }
 strcpy(nam, tailsyp->synam);
 return(TRUE);
}

/*
 * given a module and an input port name, find the port 
 *
 * tricky because port name space may be different
 * first try for net that is IO_IN then search for drivers since
 * input port only possibility 
 * then sequentially search port list if not found
 *
 * this should be efficient since rare with lots of ports and
 * connecting nets have different name but there can be designs
 * where lots of sequential searching needed
 *
 * LOOKATME - could build symbol tables for large ones only (>10)
 */
static struct mod_pin_t *get_inport_fr_nam(struct mod_t *mdp, char *pnam)
{
 int32 pi;
 struct net_pin_t *npp;
 struct sy_t *syp;
 struct net_t *np; 
 struct mod_pin_t *mpp;

 if ((syp = __get_sym(pnam, mdp->msymtab)) != NULL)
  {
   if (syp->sytyp != SYM_N) goto nd_srch;
   np = syp->el.enp;
   if (np->iotyp != IO_IN) goto nd_srch;
   for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
    {
     /* can be multiple, but assume this is input port down driver */
     /* SJM 12/15/03 - match both md port and new separated per bit md prt */
     if (npp->npntyp != NP_MDPRT && npp->npntyp != NP_PB_MDPRT) continue;

     mpp = &(mdp->mpins[npp->obnum]);    
     /* could be separate port and net name space conflict, must search */ 
     if (mpp->mp_explicit) goto nd_srch;
     return(mpp);
    }
   __misc_terr(__FILE__, __LINE__);
  }
nd_srch:
 if ((pi = getsrch_portnam(mdp, pnam)) == -1) return(NULL);
 mpp = &(mdp->mpins[pi]);
 if (mpp->mptyp != IO_IN) return(NULL);
 return(mpp);
}

/*
 * since port names in different name space must search here
 * 
 * slow sequential but only needed if not found in normal name space
 * maybe fix this - can be SDF problem if lots of sarching needed
 */
static int32 getsrch_portnam(struct mod_t *mdp, char *nam)
{
 int32 pi;
 struct mod_pin_t *mpp;

 for (pi = 0; pi < mdp->mpnum; pi++)
  {
   mpp = &(mdp->mpins[pi]);
   if (mpp->mpsnam == NULL) continue;
   if (strcmp(mpp->mpsnam, nam) == 0) return(pi);
  }
 return(-1);
}

/*
 * given a module and an output port name, find the port 
 *
 * tricky because port name space may be different
 */
static struct mod_pin_t *get_outport_fr_nam(struct mod_t *mdp, char *pnam)
{
 int32 pi;
 struct net_pin_t *npp;
 struct sy_t *syp;
 struct net_t *np; 
 struct mod_pin_t *mpp;

 if ((syp = __get_sym(pnam, mdp->msymtab)) != NULL)
  {
   if (syp->sytyp != SYM_N) goto nd_srch;
   np = syp->el.enp;
   if (np->iotyp != IO_OUT) goto nd_srch;
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
     /* can be multiple, but assume this is output port down load */
     /* SJM 12/15/03 - match both md port and new separated per bit md prt */
     if (npp->npntyp != NP_MDPRT && npp->npntyp != NP_PB_MDPRT) continue;

     mpp = &(mdp->mpins[npp->obnum]);    
     /* could be separate port and net name space conflict, must search */ 
     if (mpp->mp_explicit) goto nd_srch;
     return(mpp);
    }
   __misc_terr(__FILE__, __LINE__);
  }
nd_srch:
 if ((pi = getsrch_portnam(mdp, pnam)) == -1) return(NULL);
 mpp = &(mdp->mpins[pi]);
 if (mpp->mptyp != IO_OUT) return(NULL);
 return(mpp);
}

/*
 * given a module and an inout port name, find the port 
 *
 * FIXME - because of no npps, must explicitly search
 */
static struct mod_pin_t *get_bidport_fr_nam(struct mod_t *mdp, char *pnam)
{
 int32 pi;
 struct mod_pin_t *mpp;

 if ((pi = getsrch_portnam(mdp, pnam)) == -1) return(NULL);
 mpp = &(mdp->mpins[pi]);
 if (mpp->mptyp != IO_BID) return(NULL);
 return(mpp);
}

/*
 * ROUTINES TO PROCESS INTERCONNECT DELAYS - IGNORED
 */

/*
 * read and set all interconnect delays
 *
 * Verilog does not module real inter module paths (MIPD selected) 
 * just ignoring these delay since not supported by Verilog
 *
 * need to support single source (same as (PORT for path dest.)
 * because design compiler emits (INTERCONNECT delays
 */
static int32 rdset_interconn_dels(FILE *f, struct itree_t *itp,
 struct mod_t *ctmdp, char *formnam)
{
 int32 ii;
 int32 ndels, none_set, si1, si2, di1, di2, sav_lcnt, lcnt;
 struct itree_t *itp2;
 char portsrc[IDLEN], portdst[IDLEN]; 

 get_sdftok(f);
 lcnt = __lin_cnt;
 /* these can and usually will be qualified name */
 if (!rd_port(f, portsrc, &si1, &si2)) return(FALSE);
 if (!rd_port(f, portdst, &di1, &di2)) return(FALSE);
 if (__toktyp != LPAR)
  { dellst_err(formnam, "INTERCONNECT"); return(FALSE); }
 get_sdftok(f);
 if ((ndels = rd_sdf_dellst(f, "INTERCONNECT")) == -1) return(FALSE);

 /* need to be able to emit f errors for first token in form from here on */
 sav_lcnt = __lin_cnt; 
 __lin_cnt = lcnt;  

 /* except for next 2 fields all t_vpi_delay fields fixed in SDF */
 __sdf_delp->no_of_delays = ndels; 
 if (strcmp(formnam, "INCREMENT") == 0) __sdf_delp->append_flag = TRUE;
 else __sdf_delp->append_flag = FALSE;

 if (itp == NULL)
  {
   for (none_set = TRUE, ii = 0; ii < ctmdp->flatinum; ii++)
    {
     itp2 = ctmdp->moditps[ii];
     if (__sdf_cntxt_itp != NULL && !itp_under_cntxt(itp2)) continue;

     none_set = FALSE;
     chkset_interconn_dels(itp2, portsrc, si1, si2, portdst, di1, di2);
    }
   if (none_set)
    {
     __pv_fwarn(670,
      "no (INTERCONNECT delays changed because no instance of type %s in context", 
      ctmdp->msym->synam); 
    }
  }
 else chkset_interconn_dels(itp, portsrc, si1, si2, portdst, di1, di2);

 __lin_cnt = sav_lcnt;  
 return(TRUE);
}

/*
 * update MIPD delays - used by (INTERCONNECT 
 *
 * uses already set global sdf_del table
 * here port can be xmr path if range already extracted
 *
 * for all instances case - decomposed above so this called for each inst
 */
static void chkset_interconn_dels(struct itree_t *itp, char *portsrc,
 int32 si1, int32 si2, char *portdst, int32 di1, int32 di2)
{
 int32 ndx, fr, to, swid, dwid, bi;
 struct tenp_t *prtnetmap;
 struct mipd_t *mipdp;
 struct itree_t *sitp2, *ditp2;
 struct mod_t *smdp, *dmdp;
 struct mod_pin_t *smpp, *dmpp;
 struct gate_t ogat, ngat;
 struct net_t *np;
 char sport[IDLEN], dport[RECLEN], s1[RECLEN];

 /* first need to know instances (probably down xmrs) of ports */
 if (!xtrct_portdev(&sitp2, sport, portsrc, itp, "INTERCONNECT", "PORT"))
  return;
 if (!xtrct_portdev(&ditp2, dport, portdst, itp, "INTERCONNECT", "PORT"))
  return;

 /* next access and check the source port */
 smdp = sitp2->itip->imsym->el.emdp;
 if ((smpp = get_outport_fr_nam(smdp, sport)) == NULL &&
  (smpp = get_bidport_fr_nam(smdp, sport)) == NULL) 
  { 
   /* 11/06/00 SJM - change to warn, because no multi-driver path inter- */
   /* module paths, this is just MIPD - (PORT form and work fine */
   __pv_fwarn(3106,
    "SDF (INTERCONNECT form source port %s is not an output or inout port of module %s - works because annotated as (PORT form MIPD delay",
    sport, smdp->msym->synam);
  }

 /* then the destination input port */
 dmdp = ditp2->itip->imsym->el.emdp;
 /* SJM 08/14/01 - was checking src not dest for input port */
 if ((dmpp = get_inport_fr_nam(dmdp, dport)) == NULL 
  && (dmpp = get_bidport_fr_nam(dmdp, dport)) == NULL) 
  { 
   if ((dmpp = get_outport_fr_nam(dmdp, dport)) == NULL)
    {
     __pv_ferr(1384,
      "SDF (INTERCONNECT form destination port %s is not a port of module %s",
      dport, dmdp->msym->synam);
     return;
    }

   /* SJM 02/15/08 - new use gate driver (DEVICE delay for interconnect */
   /* destination as output port wild card all instance form impossible */
   /* (has no meaning) */
   if (itp == NULL)
    {
     __pv_ferr(1509,
      "SDF (INTERCONNECT output port %s in %s (DEVICE annotate wild card (*) form illegal\n",
      dport, dmdp->msym->synam);
     return; 
    }
   /* SJM 02/15/08 - following other simulators (INTERCONNECT delay dest */
   /* can now also be output port providing output port has one driver */
   /* algorithm searches down through mod out ports finding real driver */
   /* SJM 02/18/08 - for now only allow scalar ports */
   if (dmpp->mpref->optyp != ID)
    {
     __pv_ferr(1505,
      "SDF (INTERCONNECT output port %s in %s (DEVICE annotate must be net identifier\n",
      dport, dmdp->msym->synam);
    }
   np = dmpp->mpref->lu.sy->el.enp;
   /* SJM 02/18/08 - also must be 1 bit - scalar or one bit: i1 equal to i2 */ 
   if (np->n_isavec && (di1 == -1 || di1 != di2))  
    { 
     __pv_ferr(1506,
      "SDF (INTERCONNECT output port %s in %s (DEVICE delay annotate must be 1 bit wide\n",
      dport, dmdp->msym->synam);
     return;
    }

   try_find_set_intercon_prim_del(dmpp, di2, dmdp, ditp2, "(INTERCONNECT");
   return;
  }

 /* 11/06/00 SJM - only check for same width if input/inout port set */
 /* since same as (PORT works fine */ 
 if (smpp != NULL)
  {
   if (si1 == -1) swid = smpp->mpwide; else swid = si1 - si2 + 1;
   if (di1 == -1) dwid = dmpp->mpwide; else dwid = di1 - di2 + 1;
   if (swid != dwid)
    {
     __pv_fwarn(3105,
      "SDF (INTERCONNECT form source %s width %d not same as destination %s width %d",
      bld_prefnam(__xs, sport, si1, si2), swid, bld_prefnam(__xs2, dport, di1,
      di2), dwid);
    } 
  }

 /* LOOKATME - assuming vector ports require ranges */
 if (di1 == -1)
  {
   if (dmpp->mpwide != 1) { fr = dmpp->mpwide - 1; to = 0; } else fr = to = 0;
  }
 else { fr = di1; to = di2; } 

 prtnetmap = NULL;
 /* always build the MIPD d.s. on dest if not built yet */
 if (!dmpp->has_mipd) 
  {
   /* if setting 0 del (always only 1 inst.) and none before no need to add */ 
   /* if later other inst. needs will be set then and no src path */
   if (smpp == NULL && vpi_delay_all0s(__sdf_delp))
    {
     __num_rem_mipds += (fr - to) + 1; 
     return;
    }

   /* must allocate for all nets that connect to port - not just rng */
   prtnetmap = __bld_portbit_netbit_map(dmpp);
   for (ndx = 0; ndx < dmpp->mpwide; ndx++)
    {
     np = prtnetmap[ndx].tenu.np;
     /* LOOKATME - think unc not possible here */
     if (np == NULL || (np->nlds != NULL && np->nlds->npntyp == NP_MIPD_NCHG))
      continue;

     /* allocate path for ever net connected to port */
     __add_alloc_mipd_npp(np, dmdp);
    }

   /* add the per bit mipd npp and set all bits to no IMPD */
   dmdp->mod_has_mipds = TRUE;
   dmpp->has_mipd = TRUE; 
  }

 if (prtnetmap == NULL) prtnetmap = __bld_portbit_netbit_map(dmpp);
 if (smpp == NULL)
  {
   sprintf(s1,
    "(INTERCONNECT (but invalid source port %s) destination port %s in %s",
    portsrc, dport, dmdp->msym->synam);
  }
 else
  {
   sprintf(s1, "(INTERCONNECT destination port %s in %s", dport,
    dmdp->msym->synam);
  }
 for (ndx = fr; ndx >= to; ndx--)
  {
   np = prtnetmap[ndx].tenu.np;
   bi = prtnetmap[ndx].nbi;

   /* DBG remove -- */
   if (np->nlds == NULL || np->nlds->npntyp != NP_MIPD_NCHG)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   mipdp = &(np->nlds->elnpp.emipdbits[bi]);

   /* if no active mipd for this net/bit, must enable (PORT FORM with 0 del */
   if (mipdp->no_mipd) __setup_mipd(mipdp, np, dmdp->flatinum);

   /* FIXME - for now still not simulating src-dst path delays */
   /* if use impth delays add the source path but set non src-dst too */
   if (smpp != NULL && __use_impthdels && mipdp->pth_mipd)
    add_srcdst_impth(mipdp, smpp, si1, si2, sitp2, s1);

   /* even if setting, interconnect src-dst impth src, still set (PORT form */
   ogat.g_du = mipdp->pb_mipd_du;
   ogat.g_delrep = mipdp->pb_mipd_delrep;

   /* mipd delays can't have logic/bufix toz delays */
   if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp, ditp2, TRUE, FALSE, s1))
    continue;

   if (ngat.g_delrep == DT_4V)
    {
     if (ngat.g_du.d4v[0] < ngat.g_du.d4v[1])
      ngat.g_du.d4v[3] = ngat.g_du.d4v[0];
     else ngat.g_du.d4v[3] = ngat.g_du.d4v[1];
    }

   /* always set dest (PORT delay - either add or replace depending on SDF */
   __chg_1inst_del(&ogat, ditp2, &ngat);
   __free_del(ngat.g_du, ngat.g_delrep, dmdp->flatinum);

   mipdp->pb_mipd_du = ogat.g_du; 
   mipdp->pb_mipd_delrep = ogat.g_delrep; 
   if (__sdf_verbose)
    {
     char s2[RECLEN], s3[RECLEN];

     if (dmpp->mpwide > 1) sprintf(s1, " bit %d", ndx); else strcpy(s1, "");
     __push_itstk(ditp2);
     __cv_msg(
      "  SDF **%s(%d): (INTERCONNECT (non src-dst port) %s%s MIPD set to %s (in %s type %s)\n", 
      __cur_fnam, __lin_cnt,
      msgpref_tostr(__xs, dmpp), s1, __bld_delay_str(s2, ogat.g_du,
      ogat.g_delrep), __msg2_blditree(s3, ditp2), dmdp->msym->synam);
     __pop_itstk();
    }
  }
 __my_free(prtnetmap, dmpp->mpwide*sizeof(struct tenp_t));
}

/*
 * build a port reference name
 */
static char *bld_prefnam(char *s, char *pnam, int32 i1, int32 i2)
{
 if (i1 == -1) strcpy(s, pnam);
 else if (i1 == i2) sprintf(s, "%s[%d]", pnam, i1); 
 else sprintf(s, "%s[%d:%d]", pnam, i1, i2); 
 return(s);
} 

/*
 * routine to compute delay and fill interconnect src-dst source impth element
 *
 * this is called from inside dest range loop so same as full path
 */
static void add_srcdst_impth(struct mipd_t *mipdp, struct mod_pin_t *smpp,
 int32 si1, int32 si2, struct itree_t *sitp, char *s1)
{
 int32 fr, to, bi, save_append_flg, ndx, inum;
 word64 tmpdval; 
 struct tenp_t *prtnetmap;
 struct gate_t ngat, ogat;
 struct net_t *np;
 struct impth_t *impthp; 

 if (si1 == -1)
  {
   if (smpp->mpwide != 1) { fr = smpp->mpwide - 1; to = 0; } else fr = to = 0;
  }
 else { fr = si1; to = si2; } 

 prtnetmap = __bld_portbit_netbit_map(smpp);
 for (ndx = fr; ndx >= to; ndx--)
  {
   np = prtnetmap[ndx].tenu.np;
   bi = prtnetmap[ndx].nbi;

   impthp = (struct impth_t *) __my_malloc(sizeof(struct impth_t));
   impthp->snp = np; 
   impthp->sbi = bi;
   impthp->sitp = sitp;
   /* notice just one for each full path bit */
   impthp->lastchg = 0ULL;

   /* need to convert SDF delay_p (just using vpi because convenient) to del */
   /* pass as non append and ogat as 0 and makes right non IS */
   ogat.g_delrep = DT_1V;
   ogat.g_du.d1v = &tmpdval;
   tmpdval = 0ULL;

   save_append_flg = __sdf_delp->append_flag;
   /* LOOKATME - does this emit warns on delay problems? */
   /* path delays can't have logic/bufix toz delays */
   if (!bld_sdfnewdu(&ngat, &ogat, __sdf_delp, sitp, TRUE, FALSE, s1))
    {
     __sdf_delp->append_flag = save_append_flg;
     /* ??? FIXME - HOW HANDLE THIS */
     __misc_terr(__FILE__, __LINE__);
     continue;
    }
   __sdf_delp->append_flag = save_append_flg;

   /* notice must not free but bld sdfnewdu allocates new for each call */
   impthp->impth_delrep = ngat.g_delrep;
   impthp->impth_du = ngat.g_du;

   /* LOOKATME - think linking on front works */
   inum = get_inum_();
   impthp->impthnxt = mipdp->impthtab[inum];
   mipdp->impthtab[inum] = impthp;
  }
 __my_free(prtnetmap, smpp->mpwide*sizeof(struct tenp_t));
}

/*
 * ROUTINES TO PROCESS DEVICE DELAYS
 */

/*
 * read and set delays for a device delay form that is cell all paths
 *
 * primitive delays handled elsewhere
 * also can set IOPATH delays for all paths to output or in cell
 * this can be qualified name (all outputs of the xmr path dest in xmr dest
 * cell) but iopath because have both source and dest. can not be qualified
 */
static int32 rdset_devpath_dels(FILE *f, struct itree_t *itp,
 struct mod_t *ctmdp, char *formnam)
{
 int32 si1, si2, ndels, sav_lcnt, lcnt;
 char portdst[IDLEN];

 /* DBG remove -- */
 if (ctmdp == NULL) __arg_terr(__FILE__, __LINE__);
 /* --- */

 get_sdftok(f);
 lcnt = __lin_cnt;
 /* ( is start of delval_list so portinst missing */
 if (__toktyp != LPAR)
  {
   /* this can be qualified name */
   if (!rd_port(f, portdst, &si1, &si2)) return(FALSE);
   if (__toktyp != LPAR)
    { dellst_err(formnam, "DEVICE"); return(FALSE); }
  }
 else { strcpy(portdst, ""); si1 = si2 = -1; }
 get_sdftok(f);
 if ((ndels = rd_sdf_dellst(f, "DEVICE")) == -1) return(FALSE);

 /* except for next 2 fields all t_vpi_delay fields fixed in SDF */
 __sdf_delp->no_of_delays = ndels; 
 if (strcmp(formnam, "INCREMENT") == 0) __sdf_delp->append_flag = TRUE;
 else __sdf_delp->append_flag = FALSE;

 /* need to be able to emit f errors for first token in form from here on */
 sav_lcnt = __lin_cnt; 
 __lin_cnt = lcnt;  

 if (strcmp(portdst, "") == 0)  
  {
   /* build list of all paths in ctmdp and update delays */
   set_allpths_dels(itp, ctmdp);
  }
 /* all paths to one output */
 else set_alloutpths_dels(portdst, si1, si2, itp, ctmdp);
 __lin_cnt = sav_lcnt;
 return(TRUE);
}

/*
 * for (DEVICE no port instance form set delay for all paths in module
 */
static void set_allpths_dels(struct itree_t *itp, struct mod_t *ctmdp)
{
 struct spcpth_t *pthp;
 struct pthlst_t *plp;
 struct pthlst_t *plhd, *plend;

 if (ctmdp->mspfy == NULL || ctmdp->mspfy->spcpths == NULL)
  {
   __pv_fwarn(668,
    "SDF DEVICE module CELLTYPE %s has no paths - nothing to do",
    ctmdp->msym->synam);
   return;
  }
 plhd = plend = NULL;
 for (pthp = ctmdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
  {
   plp = (struct pthlst_t *) __my_malloc(sizeof(struct pthlst_t));
   plp->lpthp = pthp;
   plp->pthlnxt = NULL; 
   if (plend == NULL) plhd = plend = plp;
   else { plend->pthlnxt = plp; plend = plp; }
  }
 for (plp = plhd; plp != NULL; plp = plp->pthlnxt)
  set_1pthdel(plp, itp, ctmdp);
 free_pthlst(plhd);
} 

/*
 * for (DEVICE port instance (maybe xmr) set delay for all paths to output
 *
 * this differs from all paths by matching output and range 
 * if any path component (, list in Verilog) matches delay is set for all 
 */
static void set_alloutpths_dels(char *qualport, int32 pi1, int32 pi2,
 struct itree_t *itp, struct mod_t *ctmdp)
{
 struct spcpth_t *pthp;
 struct pthlst_t *plp;
 int32 pei;
 struct pthlst_t *plhd, *plend;
 struct itree_t *cor_itp, *itp2;
 struct mod_t *mdp;
 struct pathel_t *pep;
 char portnam[IDLEN];

 /* if wildcard all insts of type under form have same module type */
 /* therefore need to find a "corrected" itp */
 /* type will be same */
 if (itp == NULL)
  {
   if ((cor_itp = find_1under_itp(ctmdp)) == NULL)
    {
     __pv_fwarn(669,
      "delays not changed for (DEVICE portinst %s because no instance of type %s in context", 
      qualport, ctmdp->msym->synam);
     return;
    }
  }
 else cor_itp = itp;

 /* setting to one instance case */
 if (!xtrct_portdev(&itp2, portnam, qualport, cor_itp, "DEVICE", "PORT"))
  return;
 mdp = itp2->itip->imsym->el.emdp;

 if (ctmdp->mspfy == NULL || ctmdp->mspfy->spcpths == NULL)
  {
   not_a_port(portnam, IO_OUT, mdp, "(DEVICE");
   __pv_fwarn(668,
    "SDF DEVICE module CELLTYPE %s has no paths - nothing to do",
    ctmdp->msym->synam);
   return;
  }
 plhd = plend = NULL;
 for (pthp = ctmdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
  {
   /* only match outputs */
   for (pei = 0; pei <= pthp->last_peout; pei++)
    {
     pep = &(pthp->peouts[pei]);
     if (strcmp(pep->penp->nsym->synam, portnam) != 0) continue;
     /* if any bit overlaps matches */
     if (pi1 != -1 && pep->pthi1 != -1)
      { if (pi1 > pep->pthi1 && pi2 < pep->pthi2) continue; }

     /*if either whole range or pi1:pi2 range at least one bit inside */
     if (pi1 == -1 || pep->pthi1 == -1
      || (pi1 <= pep->pthi1 && pi1 >= pep->pthi2)
      || (pi2 <= pep->pthi1 && pi2 >= pep->pthi2))
      {
       plp = (struct pthlst_t *) __my_malloc(sizeof(struct pthlst_t));
       plp->lpthp = pthp;
       plp->pthlnxt = NULL; 
       if (plend == NULL) plhd = plend = plp;
       else { plend->pthlnxt = plp; plend = plp; }

       /* once path in list, other matches irrelevant */
       goto nxt_pth;
      }
    }
nxt_pth:;
  }
 if (plhd == NULL)
  {
   if (not_a_port(portnam, IO_OUT, mdp, "(DEVICE")) return;

   __pv_ferr(1329, 
    "for (DEVICE no module %s specify path ends on output/inout port %s", 
    mdp->msym->synam, portnam); 
   return;
  }
 for (plp = plhd; plp != NULL; plp = plp->pthlnxt)
  set_1pthdel(plp, itp, ctmdp);
 free_pthlst(plhd);
} 

/*
 * return T and emit error if name in (DEVICE or (TIMINGCHECK port name slot
 * not a port
 *
 * here always check inout and passed port type
 */
static int32 not_a_port(char *pnam, int32 ptyp, struct mod_t *mdp, char *formnam)
{
 if (ptyp == IO_BID)
  {
   if (get_inport_fr_nam(mdp, pnam) != NULL) return(FALSE); 
   if (get_outport_fr_nam(mdp, pnam) != NULL) return(FALSE); 
   if (get_bidport_fr_nam(mdp, pnam) != NULL) return(FALSE); 
  }
 else
  {
   if (ptyp == IO_IN)
    { if (get_inport_fr_nam(mdp, pnam) != NULL) return(FALSE); }
   else
    { if (get_outport_fr_nam(mdp, pnam) != NULL) return(FALSE); }

   if (get_bidport_fr_nam(mdp, pnam) != NULL) return(FALSE); 
  }

 /* know port slot is not a port of given type for this module */
 __pv_ferr(1385, "%s form port %s not a port of %s",
  formnam, pnam, mdp->msym->synam); 
 return(TRUE);
}

/*
 * FORWARD TIMING EVIRONMENT ROUTINES - NOT USED BUT CHECKED
 */

/*
 * read but skip one or more te_defs
 *
 * know (TIMINGENV read and reads one token after last
 * think timing environment constraints do not make sense in a simulator 
 * maybe user would code timing checks for simulation checking?
 *
 */
static int32 rdskip_te_defs(FILE *f)
{
 int32 first_time, i1, i2, eval;
 char tenam[RECLEN], constraint_name[IDLEN], pnam[IDLEN];

 if (__sdf_verbose)
  {
   __cv_msg(
    "  SDF: (TIMINGENV form skipped - constraints no effect in simulator\n");
  }
 for (first_time = FALSE;;)
  {
   /* this returns T if ) */
   get_sdftok(f);
   if (!rd_sdf_formtyp(f)) return(FALSE);
   if (__toktyp == RPAR)
    {
     if (first_time)
      {
       __pv_ferr(1357,
        "(TIMINGENV form empty - at least one te_def required");
       return(FALSE);
      }
     break;
    }
   first_time = FALSE;
   switch (__toktyp) {
    case SDF_PATHCONSTRAINT:
     get_sdftok(f);
     if (__toktyp == LPAR)
      {
       get_sdftok(f);
       if (__toktyp != SDF_NAME)
        {
bad_name:
         __pv_ferr(1359, "(NAME [string]) of PATHCONSTRAINT bad - %s read",
          prt_sdftok());  
        }
       get_sdftok(f);
       if (__toktyp != LITSTR) goto bad_name;
       strcpy(constraint_name, __token);
       get_sdftok(f);   
       if (__toktyp != RPAR) goto bad_name;
       get_sdftok(f);
      }
     /* do not need to save since just skipping */
     if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
     if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
     for (;;)
      {
       if (__toktyp == LPAR) break; 
       if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
      }
     if (rd_1or2_vals(f, tenam) != 2)
      {
       __pv_ferr(1239, "(PATHCONSTRAINT two values required");
       return(FALSE); 
      }
     if (__toktyp != RPAR) formend_err(tenam);
     /* would process constaint32 here */
     break;
    case SDF_PERIODCONSTRAINT:
     get_sdftok(f);
     if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
     if (rd_1_val(f, tenam) == -1) return(FALSE); 
     if (__toktyp == LPAR) { if (!rd_exception(f)) return(FALSE); }
     get_sdftok(f);
     if (__toktyp != RPAR) formend_err(tenam);
     /* process here */
     break;
    case SDF_SUM:
     get_sdftok(f);
     if (!rd_constraint_path(f, tenam, TRUE)) return(FALSE);
     get_sdftok(f);
     if (!rd_constraint_path(f, tenam, TRUE)) return(FALSE);
     for (;;)
      {
       get_sdftok(f);   
       if (!rd_constraint_path(f, tenam, FALSE)) return(FALSE);
       if (__toktyp == NUMBER || __toktyp == REALNUM || __toktyp == COLON)
        break;
       if (__toktyp == TEOF)
        {
         __pv_ferr(1297, "(SUM constraint path list bad syntax - EOF read");
         return(FALSE); 
        }
      }
     if (!rd2_1_val(f)) return(FALSE);
     if (__toktyp == RPAR) break;
     /* would need to copy and save if need actual value */
     if (rd_1_val(f, tenam) == -1) return(FALSE);
     if (__toktyp != RPAR) { formend_err(tenam); return(FALSE); }
     break;
    case SDF_DIFF:
     get_sdftok(f);
     if (!rd_constraint_path(f, tenam, TRUE)) return(FALSE);
     get_sdftok(f);
     if (!rd_constraint_path(f, tenam, TRUE)) return(FALSE);
     get_sdftok(f);  
     if (rd_1or2_vals(f, tenam) == -1) return(FALSE); 
     if (__toktyp != RPAR) formend_err(tenam);
     break;
    case SDF_SKEWCONSTRAINT:
     get_sdftok(f);
     /* since does nothing allowing full edge pair syntax */
     if (!rd_port_spec(f, pnam, &i1, &i2, &eval, TRUE)) return(FALSE);
     if (rd_1_val(f, tenam) == -1) return(FALSE);
     if (__toktyp != RPAR) { formend_err(tenam); return(FALSE); }
     break;
    case SDF_ARRIVAL: case SDF_DEPARTURE:
     get_sdftok(f);
     if (__toktyp == LPAR)
      {
       if ((eval = rd_edge_ident(f)) == -1) return(FALSE);
       get_sdftok(f);
       if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
       if (__toktyp != RPAR) { formend_err(tenam); return(FALSE); }
       get_sdftok(f);
      }
     if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
     if (!rd_4_vals(f, tenam)) return(FALSE);
     if (__toktyp != RPAR) { formend_err(tenam); return(FALSE); }
     break;
    case SDF_SLACK:
     get_sdftok(f);
     if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
     if (!rd_4_vals(f, tenam)) return(FALSE);
     if (__toktyp == NUMBER || __toktyp == REALNUM)
      {
       /* save number to process */
       get_sdftok(f);
      }
     if (__toktyp != RPAR) { formend_err(tenam); return(FALSE); }
     break;
    case SDF_WAVEFORM:
     get_sdftok(f);
     if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
     if (__toktyp != NUMBER && __toktyp != REALNUM)
      {
       __pv_ferr(1361, "(WAVEFORM NUMBER expected - %s read", prt_sdftok());
       return(FALSE);
      }
     if (!rd_edgepair_list(f)) return(FALSE);
     break;
    default:
     __pv_ferr(1358, "te_def timing check form expected - (%s read",
      prt_sdftok());
     return(FALSE);
   }
  }
 return(TRUE);
}

/*
 * read an exception form
 *
 * know ( read and reads ending )
 */
static int32 rd_exception(FILE *f)
{
 int32 first_time;

 get_sdftok(f);
 if (__toktyp != SDF_EXCEPTION)
  { 
bad_except:
   __pv_ferr(1200, "bad cns_def (PERIODCONSTRAINT (EXCEPTION form - %s read",
    prt_sdftok());
   return(FALSE);
  }
 /* read the cell_instance+ */
 for (first_time = TRUE;;)
  {
   get_sdftok(f);
   if (__toktyp == RPAR)
    {
     if (first_time) goto bad_except;
     break;
    }
   if (__toktyp != LPAR) goto bad_except;
   first_time = FALSE;
   get_sdftok(f);
   if (__toktyp != SDF_INSTANCE) goto bad_except;
   get_sdftok(f);
   if (__toktyp != RPAR)
    {
     if (__toktyp != ID && __toktyp != TIMES) goto bad_except;
     get_sdftok(f);
    }
   if (__toktyp != RPAR) { formend_err("INSTANCE"); return(FALSE); }
  }
 return(TRUE);
}

/*
 * read a constraint path
 *
 * know ( read and reads ending )
 */
static int32 rd_constraint_path(FILE *f, char *formnam, int32 required)
{
 int32 i1, i2;
 char pnam[IDLEN];
 
 get_sdftok(f);
 /* if not required next will be ([num or :] */
 if (!required) { if (__toktyp != ID) return(TRUE); }
 if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
 if (!rd_port(f, pnam, &i1, &i2)) return(FALSE);
 if (__toktyp != RPAR) { formend_err(formnam); return(FALSE); }
 return(TRUE);
}

/*
 * read either a start with neg edge or start with pos edge list (1 or more)
 *
 * reads first ( and last ) - this reads NUMBER not triple
 *
 * LOOKATME - should always be (negedge (num))(posedge (num)) or opposite but  
 * not checked for now
 */
static int32 rd_edgepair_list(FILE *f)
{
 int32 first_time;

 for (first_time = TRUE;;)
  {
   get_sdftok(f);
   if (__toktyp == RPAR)
    {
     if (first_time) goto bad_edgepair;
     break;
    }
   if (__toktyp != LPAR) 
    {
bad_edgepair:
     __pv_ferr(1358, "bad tenv_def (WAVEFORM edgelist - %s read",
      prt_sdftok());
     return(FALSE);
    }
   first_time = FALSE;
   get_sdftok(f);
   if (__toktyp != SDF_NEGEDGE && __toktyp != SDF_POSEDGE) goto bad_edgepair;
   /* first number required */
   get_sdftok(f);
   if (__toktyp != REALNUM && __toktyp != NUMBER) goto bad_edgepair;
   /* 2nd optionsal */
   get_sdftok(f);
   if (__toktyp == RPAR) continue;
   if (__toktyp != REALNUM && __toktyp != NUMBER) 
    {
bad_elend:
     formend_err("edgelist");
     return(FALSE);
    }
   get_sdftok(f);
   if (__toktyp != RPAR) goto bad_elend; 
  } 
 return(TRUE);
}

/*
 * LABEL PROCESSING AND PARAM SETTING ROUTINES
 *
 * grammar:
 * lbl_spec    := (LABEL lbltype)
 * lbltype     := (ABSOLUTE lbl_def+)
 *             := (INCREMENT lbl_def+)
 * lbl_def     := (IDENTIFIER-maybe-xmr rvalue)
 *
 * (LABEL read - reads ending ) 
 *
 * notice labels must be in units of ctmdp time scale because other
 * parts of expression will be in those units - not SDF timescale
 *
 * qualified names illegal here - (INSTANCE must select exact instance
 */
static int32 rdset_labels(FILE *f, struct itree_t *itp, struct mod_t *ctmdp)
{
 int32 ii;
 int32 first_time, is_incr, is_minus, wlen, sav_lcnt, lcnt;
 double d1;
 word32 *wp;
 struct t_vpi_time *vtp = &(__sdf_delp->da[0]);
 struct sy_t *syp;
 struct net_t *np;
 struct xstk_t *xsp;
 struct itree_t *itp2;
 struct mod_t *mdp;
 char labnam[IDLEN], s1[RECLEN], s2[RECLEN];

 get_sdftok(f);
 lcnt = __lin_cnt;
 if (!rd_sdf_formtyp(f)) return(FALSE);
 if (__toktyp == SDF_ABSOLUTE) is_incr = FALSE;
 else if (__toktyp == SDF_INCREMENT) is_incr = TRUE;
 else
  {
   __pv_ferr(1310,
    "expected lbltype ABSOLUTE or INCREMENT expected - (%s read",
    prt_sdftok());
   return(FALSE);
  }
 for (first_time = TRUE;;)
  {
   get_sdftok(f);
   if (__toktyp == RPAR)
    {
     if (first_time)
      {
       if (is_incr) strcpy(s1, "INCREMENT"); else strcpy(s1, "ABSOLUTE");
       __pv_ferr(1380,
        "(LABEL (%s lbl_def section empty - at least one lbl_def required",
        s1);
      }
     break;
    }
   if (__toktyp != LPAR)
    {
     __pv_ferr(1307, "SDF lbldef ( expected - %s read", prt_sdftok());
     return(FALSE);
    }
   first_time = FALSE;
   get_sdftok(f);
   if (__toktyp != ID)
    {
     __pv_ferr(1306,
      "SDF label expected - Verilog defparam or specparam reference - %s read",
      prt_sdftok());
     return(FALSE);
    }
   if (!xtrct_param(&itp2, labnam, itp)) return(FALSE);
   get_sdftok(f);
   /* this reads triple ending ) */
   if (!rd_rtriple(f, vtp)) return(FALSE);
   if (__toktyp != RPAR)
    {
     __pv_ferr(1308,
      "SDF (LABEL form ending ) expected - %s read", prt_sdftok());
     return(FALSE);
    }
   sav_lcnt = __lin_cnt; 
   __lin_cnt = lcnt;  
   if (itp2 != NULL) mdp = itp2->itip->imsym->el.emdp;
   else mdp = ctmdp;
   /* first look up symbol in specify symbol table if exists */
   if (mdp->mspfy != NULL && mdp->mspfy->spfsyms != NULL) 
    {
     /* SJM 09/28/06 - notice only specparams in specify symbol table */
     if ((syp =__get_sym(labnam, mdp->mspfy->spfsyms)) != NULL)
      goto got_lab_param;
    }
   if ((syp =__get_sym(labnam, mdp->msymtab)) == NULL)
    {
     __pv_ferr(1309,
      "(LABEL form label (spec or def param) %s not found in cell type %s",
      labnam, mdp->msym->synam);
     goto done;
    }
   /* AIV 09/27/06 - Cver non standard SDF label form checking was not right */
   if (syp->sytyp != SYM_N || !syp->el.enp->n_isaparam)
    {
     __pv_ferr(1309,
      "(LABEL form label (spec or def param) %s not a parameter", syp->synam);
     goto done;
    }
   /* AIV 09/27/06 - Cver non standard SDF label form can't be local param */
   if (syp->el.enp->nu.ct->p_locparam)
    {
     __pv_ferr(1309,
      "(LABEL form label %s is localparam - must be specparam or parameter",
      syp->synam);
     goto done;
    }

   __pv_fwarn(2304,
    "(LABEL form back annotation to parameter %s non standard - will need to change to module scope specparam for Verilog 2000",
     syp->synam);

got_lab_param:
   np = syp->el.enp;
   if (vtp->type == vpiSuppressTime)
    {
     __pv_fwarn(671,
      "(LABEL form %s parameter %s value missing - parameter not changed",
      (is_incr ? "INCREMENT" : "ABSOLUTE"), syp->synam);
     goto done;
    }
   d1 = vtp->real;
   if (d1 < 0.0) { is_minus = TRUE; d1 = -d1; } else is_minus = FALSE;
   if ((xsp = sdf_push_rvalue(np, d1)) == NULL) goto done;
 
   /* now know correct value to store in xsp of width n wid */
   wlen = wlen_(np->nwid);
   /* case 1: specific instance maybe downward xmr reference */
   if (itp2 != NULL)
    {
     /* load value and combine (add/subtract) if increment form */
     if (is_incr)
      {
       __push_itstk(itp2);
       if (!sdf_adjust_incr(np, xsp, is_minus))
        { __pop_itstk(); goto done2; }
       __pop_itstk();
      }

     /* change range rep to IS if needed */
     if (np->srep == SR_PNUM)
      __chg_param_tois(np, itp2->itip->imsym->el.emdp);
     wp = &(np->prm_nva.wp[2*wlen*itp2->itinum]);
     memcpy(wp, xsp->ap, 2*WRDBYTES*wlen);

     /* leave original parameter rhs expr. if case user codes wants */
     /* different parameter algorithm - only paramter value changed */
     /* but original param assign RHS left as is */ 

     if (__sdf_verbose)
      {
       sprintf(s1, "%s(%s)", __msg2_blditree(s2, itp2), 
        mdp->msym->synam);
       emit_sdflblverb_msg(np, xsp, s1);
      }
     goto done2;
    }
   /* case 2: itp nil, all of design, never xmr port ref. */
   if (!is_incr && itp2 == NULL && __sdf_cntxt_itp == NULL)
    {
     /* change back from IS form since all instances */
     if (np->srep == SR_PISNUM) 
      {
       wp = np->prm_nva.wp;
       np->prm_nva.wp = (word32 *) __my_malloc(2*wlen*WRDBYTES);
       __my_free(wp, mdp->flatinum*2*wlen*WRDBYTES); 
       np->srep = SR_PNUM; 
      }
     wp = np->prm_nva.wp;
     memcpy(wp, xsp->ap, 2*WRDBYTES*wlen);
     if (__sdf_verbose)
      {
       sprintf(s1, "all instances of %s", mdp->msym->synam);
       emit_sdflblverb_msg(np, xsp, s1);
      }
     goto done2;
    }
   /* case 3: itp nil and under not all of design or incr */
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp2 = mdp->moditps[ii];
     if (__sdf_cntxt_itp != NULL && !itp_under_cntxt(itp2)) continue;
     
     if (is_incr)
      {
       __push_itstk(itp2);
       if (!sdf_adjust_incr(np, xsp, is_minus)) { __pop_itstk(); continue; }
       __pop_itstk();
      }
     /* change range rep to IS if needed */
     if (np->srep == SR_PNUM)
      __chg_param_tois(np, itp2->itip->imsym->el.emdp);
     wp = &(np->prm_nva.wp[2*wlen*itp2->itinum]);
     memcpy(wp, xsp->ap, 2*WRDBYTES*wlen);

     /* leave original parameter rhs expr. if case user codes wants */
     /* different parameter algorithm - only paramter value changed */
     /* but original param assign RHS left as is */ 

     if (__sdf_verbose)
      {
       sprintf(s1, "instance %s under %s)", __msg2_blditree(s2, itp2),
        mdp->msym->synam);
       emit_sdflblverb_msg(np, xsp, s1);
      }
    }

done2:
   __pop_xstk(); 
   /* SJM = 07/05/00 - even during simulation recomputing params/delays */
   /* from labels works */
   /* final step is to re-compute (and prep) all delays param effects */
   __re_prep_dels(np, itp2, mdp, FALSE);
done:
   __lin_cnt = sav_lcnt;
  }
 /* lbltype ) read - now read lbl_spec ) - checked by caller */
 get_sdftok(f);
 return(TRUE);
}

/*
 * extract a (possibly qualified) parameter name
 * and set instance object in
 *
 * know ID (maybe qual. path) read 
 * range illegal
 * itp and *itp2 can both be nil 
 */
static int32 xtrct_param(struct itree_t **itp2, char *pnam, struct itree_t *itp)
{
 int32 i1, i2;
 struct expr_t *glbndp;
 struct sy_t *tailsyp;
 char s1[IDLEN], s2[RECLEN];

 if (itp == NULL)
  {
   __pv_ferr(1201,
    "SDF (LABEL hierarchical parameter reference %s illegal with (INSTANCE *) form - type unknown",
    __token);
   return(FALSE);
  }

 /* case 1, simple name (no path), just check and copy */
 if (!__id_qualpath)
  {
   /* if illegal verilog identifier convert to escaped */
   if (!chkcnv_sdfid(pnam, &i1, &i2, __token, FALSE))
    {
     __pv_ferr(1344, "(LABEL %s illegal Verilog parameter name", __token);
     return(FALSE);
    }
   *itp2 = itp;
   return(TRUE);
  }
 /* case 2: qualified name */
 /* convert to Verilog name and check */
 /* LOOKATME - maybe should allow select from param here */
 if (!chkcnv_sdfpath(s1, &i1, &i2, __token, FALSE))
  {
   __pv_ferr(1348,
    "(LABEL hierarchical parameter name %s illegal Verilog global reference",
    __token);
   return(FALSE);
  }
 /* this emits its own error and returns nil on error */
 /* need to use interactive global context here */
 __push_wrkitstk(__sdf_mdp, 0);
 if ((glbndp = __glbnam_to_expr(s1)) == NULL)
  {
   __pop_wrkitstk();
   return(FALSE); 
  }

 /* find downward itree loc */
 *itp2 = get_sdfdownrel_itp(glbndp, itp, &tailsyp, s2);
 /* done with glb ndp */
 __free_xtree(glbndp);
 __pop_itstk();
 if (*itp2 == NULL)
  {
   __pv_ferr(1388,
    "(LABEL form qualified path %s.%s name illegal in context %s: %s",
    s1, pnam, get_sdfcntxtnam(__xs, itp), s2);
   return(FALSE);
  }
 if (tailsyp->sytyp != SYM_N || !tailsyp->el.enp->n_isaparam) 
  {
   __pv_ferr(1201,
    "SDF (LABEL hierarchical parameter reference %s illegal - %s not a parameter",
    __token, tailsyp->synam);
   return(FALSE);
  }
 strcpy(pnam, tailsyp->synam);
 return(TRUE);
}

/*
 * push rtriple value onto stack with param matching type and width
 *
 * since SDF rtriple real (if present), convert to match param if needed
 * after here know stack contains param width new value 
 */
static struct xstk_t *sdf_push_rvalue(struct net_t *np, double d1)
{
 int32 i1;
 word64 timval;
 struct xstk_t *xsp;

 if (np->ntyp != N_REAL)
  {
   if (np->ntyp == N_INT) 
    {
     i1 = (int32) d1;
     push_xstk_(xsp, np->nwid);
     xsp->ap[0] = (word32) i1;
     xsp->bp[0] = 0L;
    }
   else
    {
     if (!__real_to_v64tim(&timval, d1))
      {
       __pv_ferr(1327,
        "precision lost in converting (LABEL rvalue %g to 64 bit", d1);
       __pop_xstk();
       return(NULL);
      }
     push_xstk_(xsp, 64);
     xsp->ap[0] = (word32) (timval & WORDMASK_ULL);
     xsp->ap[1] = (word32) ((timval >> 32) & WORDMASK_ULL);
     xsp->bp[0] = xsp->bp[1] = 0L;
     if (np->nwid != 64) __sizchgxs(xsp, np->nwid);
    }
  }
 else
  {
   push_xstk_(xsp, WBITS);
   /* value real and pushing real */
   memcpy(xsp->ap, &d1, sizeof(double)); 
  }
 return(xsp);
}

/*
 * emit a label sdf verbose message for param assign
 */
static void emit_sdflblverb_msg(struct net_t *np, struct xstk_t *xsp,
 char *celloc)
{
 char s1[RECLEN], s2[RECLEN];

 /* DBG remove -- */ 
 if (!np->n_isaparam) __arg_terr(__FILE__, __LINE__);
 /* --- */
 if (np->nu.ct->p_specparam) strcpy(s1, "specparam"); 
 else strcpy(s1, "defparam");

 __cv_msg("  SDF **%s(%d): (LABEL %s %s set to %s in %s\n",
  __cur_fnam, __lin_cnt, s1, np->nsym->synam,
  __regab_tostr(s2, xsp->ap, xsp->bp, xsp->xslen, BDEC, FALSE), celloc);
}

/*
 * for SDF label adjust increment parameter 
 *
 * leaves expr. stack same as entry
 */
static int32 sdf_adjust_incr(struct net_t *np, struct xstk_t *xsp, int32 is_minus)
{
 int32 i1, i2, isxz, cmp;
 double d1, d2;
 struct xstk_t *xsp2, *xsp3;

 push_xstk_(xsp2, np->nwid);
 __ld_wire_val_xstk(xsp2, np);
 if (np->ntyp == N_REAL)
  {
   memcpy(&d1, xsp->ap, sizeof(double));
   memcpy(&d2, xsp2->ap, sizeof(double));
   if (is_minus) d2 -= d1; else d2 += d1;
   memcpy(xsp->ap, &d2, sizeof(double));
   return(TRUE);
  }
 if (!vval_is0_(xsp2->bp, xsp2->xslen))
  {
   __pv_ferr(1250,
    "(LABEL INCREMENT form impossible - parameter %s value %s x/z",
    np->nsym->synam, __regab_tostr(__xs, xsp2->ap, xsp2->bp, xsp->xslen,
    BDEC, FALSE));
   __pop_xstk();
   return(FALSE);
  }
 /* int32 - result can be negative */
 /* know neiher value can have x/z bits on */
 if (np->ntyp == N_INT)
  {
   i1 = (int32) xsp2->ap[0]; 
   i2 = (int32) xsp->ap[0];
   if (is_minus) i2 -= i1; else i2 += i1;
   xsp->ap[0] = i2;
   __pop_xstk();
   return(TRUE);
  }
 /* word32 case fits in word32 case */
 if (np->nwid <= WBITS)
  {
   if (is_minus)
    {
     if (xsp2->ap[0] < xsp->ap[0])
      {
incr_neg:
       __pv_ferr(1250,
        "(LABEL INCREMENT form impossible - word32 parameter %s incremented value negative",
        np->nsym->synam);
       __pop_xstk();
       return(FALSE);
      }
     xsp2->ap[0] -= xsp->ap[0]; 
     xsp->ap[0] = xsp2->ap[0];
    }
   else xsp->ap[0] += xsp2->ap[0];
   __pop_xstk();
   return(TRUE);
  }
 /* word32 wider than one word32 */
 push_xstk_(xsp3, np->nwid);
 if (is_minus)
  {
   /* SJM 05/10/04 LOOKATME SIGNED - think do not need signed wide comp here */
   cmp = __do_widecmp(&isxz, xsp->ap, xsp->bp, xsp2->ap, xsp2->bp, np->nwid);
   /* DBG remove --- */
   if (isxz) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (cmp < 0) { __pop_xstk(); goto incr_neg; }
   __lsub(xsp3->ap, xsp2->ap, xsp->ap, np->nwid);
  }
 else __ladd(xsp3->ap, xsp2->ap, xsp->ap, np->nwid);
 cp_walign_(xsp->ap, xsp3->ap, np->nwid);
 __pop_xstk();
 __pop_xstk();
 return(TRUE);
}

/*
 * change parameter from SR_PNUM to SR_PISNUM range all values same
 * no error possible here
 *
 * LOOKATME - does this still work with v2k param override scheme?
 */
extern void __chg_param_tois(struct net_t *np, struct mod_t *imdp)
{
 int32 ii;
 int32 wlen2x;
 word32 *wp, *wp2;

 /* AIV 12/22/11 - need to save the number of instances that this */
 /* is split into due to later passes of generate expansion */
 /* DBG remove --- */
 if (np->nrngrep != NX_CT) __misc_terr(__FILE__, __LINE__);
 /* --- */
 np->nu.ct->isparam_ninsts = imdp->flatinum;
 wlen2x = 2*wlen_(np->nwid);
 wp = np->prm_nva.wp;
 wp2 = (word32 *) __my_malloc(wlen2x*WRDBYTES*imdp->flatinum); 
 for (ii = 0; ii < imdp->flatinum; ii++)
  { memcpy(&(wp2[ii*wlen2x]), wp, WRDBYTES*wlen2x); }
 __my_free(wp, WRDBYTES*wlen2x);
 np->srep = SR_PISNUM;
 np->prm_nva.wp = wp2;
 imdp->mhasisform = TRUE;
}

/*
 * DELAY CHANGING MECHANISM ROUTINES (USES VPI) 
 */

/*
 * given an SDF vpi delay_p filled by user, build the _du for it
 *
 * know delay number correct
 * vpi delay_p filled 
 * if no source delay caller changes to #0 before calling
 * any time scaling uses SDF timescale (can be smaller than design prec)
 *
 * this always builds non IS form, so never a need for packed but does
 * try to reduce
 *
 * this can be called multiple times provided append flg turned off
 * also if append flg turned off, itp can be passed as il
 */
static int32 bld_sdfnewdu(struct gate_t *ngp, struct gate_t *ogp,
 p_vpi_delay delay_p, struct itree_t *itp, int32 is_path, int32 has_toz,
 char *sdfmsg)
{
 int32 di, ndels, ondels, negdel[16], empty_fld[16], has_emp;
 word64 tim[16], otim[16], ntim[16], *dtab;

 /* if empty place holders in delay p, set to old delay or 0 if append */ 
 /* this trims all tail empty place holders */
 if ((ndels = sdf_fillchk_tim(tim, negdel, empty_fld, &has_emp,
  delay_p, sdfmsg)) == -1) return(FALSE); 

 /* if no dels, no change for both append (change 0) or absolute (ignore) */
 if (ndels == 0) return(FALSE);

 /* handle appending - must be on delay_p array */ 
 if (delay_p->append_flag)
  { 
   __extract_delval_compile_time(otim, &ondels, ogp->g_du, ogp->g_delrep, 
    itp->itinum);
   /* if either 1, widen with inform by replicating the 1 to width of other */
   if ((ondels == 1 || ndels == 1) && (ondels != ndels)) 
    {
     __finform(479,
      "%s INCREMENT old (%d) and new (%d) number of delays differ - one delay replicated",
      sdfmsg, ondels, ndels);   

     if (ondels != 1)
      {
       for (di = 1; di < ondels; di++) tim[di] = tim[0];
       ndels = ondels;
      }
     else
      { 
       for (di = 1; di < ndels; di++) otim[di] = otim[0];
       ondels = ndels;
      }
    }
   /* SJM 04/16/08 - attempt to simplify toz 3 delays to 2 when could */
   /* was wrong since delays here are t vpi delay 3 values not 4 val Verilog */
   /* tables, caller will correct if needed */

   /* if too few new delays, use 0 for those (i.e. unchanged) */
   /* since increment, increment of 0 does nothing */
   if (ndels < ondels)
    {
     __finform(478,
      "%s INCREMENT more old delays (%d) than new (%d) - 0 used for missing",
      sdfmsg, ondels, ndels);   
     for (di = ndels; di < ondels; di++) tim[di] = 0ULL;
     ndels = ondels;
    }
   /* too many - ignore with warning */
   else if (ndels > ondels)
    {
     __pv_fwarn(674,
      "%s INCREMENT more new delays (%d) than old (%d) - extra ignored",
      sdfmsg, ndels, ondels);   
     ndels = ondels;
    }
   /* do the update - know ndels and odels same */
   for (di = 0; di < ndels; di++) ntim[di] = tim[di];
   for (di = 0; di < ndels; di++)
    {
     if (negdel[di])
      {
       if (ntim[di] > otim[di])
        {
         __pv_fwarn(667,
          "%s INCREMENT append result (pos %d) negative (0 used)", sdfmsg,
          di + 1);
         tim[di] = 0ULL;
        }
       else tim[di] = otim[di] - ntim[di];
      } 
     else tim[di] = otim[di] + ntim[di];
    }
  }
 /* easy 1 delay case */
 if (ndels == 1)
  {
del1form:
   ngp->g_du.d1v = (word64 *) __my_malloc(sizeof(word64));
   *(ngp->g_du.d1v) = tim[0];
   ngp->g_delrep = DT_1V;
   return(TRUE);
  }

 /* if absolute and has empty place holders, must fill empty */
 /* problem is that for empty, time value 0 but should be old value */
 if (has_emp && !delay_p->append_flag)
  {
   __extract_delval_compile_time(otim, &ondels, ogp->g_du, ogp->g_delrep,
     itp->itinum);
   for (di = 0; di < ndels; di++)
    {
     if (!empty_fld[di]) continue;
      
     /* if ondels shorter than new and empty field, warning with 0 */
     if (di >= ondels)
      {
       __pv_fwarn(673,
        "%s ABSOLUTE empty delay place holder but no original delay (pos. %d) - 0 used",
       sdfmsg, di);
      }  
     else tim[di] = otim[di];
    }
  }
 /* see if can reduce to 1 - know at least 2 */
 for (di = 1; di < ndels; di++) { if (tim[0] != tim[di]) goto no_reduce1; }
 goto del1form;

no_reduce1:
 /* know tim has right new delay value - fill dtab (always 1 or 16 for path) */
 if (is_path)
  {
   dtab = (word64 *) __my_malloc(16*sizeof(word64));
   __fill_16vconst(dtab, tim, ndels);
   ngp->g_delrep = DT_16V;
   ngp->g_du.d16v = dtab;
  }
 else
  {
   dtab = (word64 *) __my_malloc(4*sizeof(word64));
   __fill_4vconst(dtab, &(tim[0]), &(tim[1]), &(tim[2]), ndels, has_toz);
   ngp->g_delrep = DT_4V;
   ngp->g_du.d4v = dtab;
  }
 return(TRUE);
}

/*
 * fill and check internal tim[] value from delay p for SDF
 * return -1 on error else number of delays after tail place holder removed
 *
 * know all delays vpiScaledRealTime
 * for SDF any mtm or pulsere already removed
 * for empty () place holders, set empty_fld for pos. and time to 0
 * but also removed all end since have no effect
 */
static int32 sdf_fillchk_tim(word64 *tim, int32 *negdel, int32 *empty_fld,
 int32 *has_emp, p_vpi_delay delay_p,  char *sdfmsg)
{
 int32 di, nndels;
 int32 ndels, has_empty;
 double d1;
 struct t_vpi_time *vpitimp;

 has_empty = FALSE;
 *has_emp = FALSE;
 ndels = delay_p->no_of_delays;
 for (di = 0; di < ndels; di++) negdel[di] = empty_fld[di] = FALSE;
 /* step 1: convert to internal ticks and set neg - maybe needed for inc */
 for (di = 0; di < ndels; di++)
  {
   /* always ignore any pulse limits (2 and 3 or 3 through 8 if mtm) */
   vpitimp = &(delay_p->da[di]);

   /* if delay field empty (SDF place holder), set pos. flag */
   if (vpitimp->type == vpiSuppressTime)
    {
     empty_fld[di] = TRUE;
     /* SJM 02/25/08 - wrongly was assigning to 0 not di so when after 1st */
     /* was missing was over-writing the 0th so wrong valued annotated */
     tim[di] = 0ULL;   
     has_empty = TRUE;
     continue;
    }

   /* DBG remove --- */
   if (vpitimp->type == vpiSimTime) __arg_terr(__FILE__, __LINE__);
   /* --- */
   d1 = vpitimp->real;
   if (d1 < 0.0)
    {
     if (!delay_p->append_flag)
      {
       __pv_fwarn(667, "%s ABSOLUTE value %g (pos %d) negative (0 used)",
        sdfmsg, d1, di + 1);
        tim[di] = 0ULL;
       continue;
      }  
     d1 = -d1;
     negdel[di] = TRUE;
    }
   /* first scale to real but in design time prec (min. ticks) */
   if (__sdf_nd_tscale)
    {
     if (__sdf_ts_units < 0) d1 /= __dbl_toticks_tab[-__sdf_ts_units];
     else d1 *= __dbl_toticks_tab[__sdf_ts_units];
    }
   /* once know in design time prec. units, convert to ticks (from real) */ 
   if (!__real_to_v64tim(&(tim[di]), d1))
    {
     __pv_ferr(1365, "%s delay value %g (pos. %d) too large for 64 bit time",
      sdfmsg, d1, di + 1);
     return(-1);
    }
  }
 /* remove place holders - if all empty emit warning */
 if (has_empty)
  {
   for (nndels = ndels, di = ndels - 1; di >= 0; di--)
    {
     if (!empty_fld[di]) break;
     nndels--;
    }
   if (nndels == 0)
    {
     __pv_fwarn(650,
     "%s all delay list values (size %d) empty place holders - no delay change",
      sdfmsg, ndels);
    }
   ndels = nndels;
  }
 if (has_empty) *has_emp = TRUE;
 return(ndels);
}

/*
 * return T if vpi_delay records all 0 (or missing) 
 *
 * used for MIPDs to not set 0 delays
 */
static int32 vpi_delay_all0s(p_vpi_delay delay_p)
{
 int32 di;
 struct t_vpi_time *vpitimp;
 double d1;

 for (di = 0; di < delay_p->no_of_delays; di++)
  {
   /* always ignore any pulse limits (2 and 3 or 3 through 8 if mtm) */
   vpitimp = &(delay_p->da[di]);
   /* missing for append mode same as 0 */
   if (vpitimp->type == vpiSuppressTime) continue;

   /* DBG remove --- */
   if (vpitimp->type != vpiScaledRealTime) __arg_terr(__FILE__, __LINE__);
   /* --- */
   d1 = vpitimp->real;
   /* for non append mode, <0 converted to 0.0 so same as 0 */
   if (delay_p->append_flag) { if (d1 != 0.0) return(FALSE); }
   else { if (d1 > 0.0) return(FALSE); }
  }
 return(TRUE);
}

/*
 * SDF FILE OBJECT LOW LEVEL READ ROUTINES
 */

/*
 * read a delay list - fills extern 12 value maximum value and in use tables
 * returns no. of delays (some may be missing) or -1 on error
 *
 * ( and first value read and reads one past list end - must be )
 * at least one required but can be ()
 *
 * syntax for delay lists:
 *  rvalue ::= ([some kind of real number - maybe mtm])
 *  delval ::= ([rnumber]) | (([delay rnumber]) ([rlim rnumber]))
 *           | ((delay rnumber]) ([rlim rnumber]) ([xlim rnumber]))   
 * -- notice no parentheses around this - context has parens
 * delval_list ::= [from 1 to 12 delvals] 
 *
 * examples of delval: (mtm), (), ((mtm) (mtm)), ((mtm), (mtm), (mtm))
 * list: () ((mtm) ()) (mtm) ((mtm) (mtm) (mtm)) ()
 * notice some members of list can have rlim, xlim and other not
 * also missing needed for delay setting - no change
 *
 * SJM 10/23/00 - () not at end was not working - i.e. it was not being added
 * to delay list as empty form - now do not just skip when seeing ()
 */
static int32 rd_sdf_dellst(FILE *f, char *formnam)
{
 int32 nvals;
 struct t_vpi_time *vtp = &(__sdf_delp->da[0]);
 struct t_vpi_time tmpvtim;

 for (nvals = 0;;)
  {
   /* case 1: position "nval" empty () form */
   if (__toktyp == RPAR)
    {
     vtp[nvals].type = vpiSuppressTime;
     nvals++;  
     if (nvals > 12) goto too_many;
     goto nxt_del;
    }

   /* case 2: r limit 2-tuple or r and x 3-tuple form - starts with (( */
   if (__toktyp == LPAR)
    {
     get_sdftok(f);
     /* know triple always reads required ending ) - room for illegal 13th */
     if (!rd_rtriple(f, &(vtp[nvals]))) return(-1);
     nvals++;  
     if (nvals > 12)
      {
too_many:
       __pv_ferr(1332, "(%s form delval_list illegal - more than 12 delvals",
        formnam);
       if (!sdf_skip_form(f)) return(-1);
       return(nvals);
      }
     get_sdftok(f); 
     if (__toktyp != LPAR)
      {
bad_list:
       __pv_ferr(1331, "(%s form delval_list illegal - error at delay pos. %d",
        formnam, nvals + 1);
       return(-1);
      }
     if (!rd_rtriple(f, &(tmpvtim))) return(-1);
     if (tmpvtim.type != vpiSuppressTime)
      {
       if (!__seen_rlim_delval)
        {
         __seen_rlim_delval = TRUE;
         __pv_fwarn(657,
          "some delval(s) contain reject limits - ignored (this is first)");
        }
      } 
     get_sdftok(f); 
     /* 2-tuple without x limit legal */
     if (__toktyp == RPAR) goto nxt_del;
     if (__toktyp != LPAR) goto bad_list; 
     if (!rd_rtriple(f, &(tmpvtim))) return(-1);
     if (tmpvtim.type != vpiSuppressTime)
      {
       if (!__seen_xlim_delval)
        {
         __seen_xlim_delval = TRUE;
         __pv_fwarn(658,
          "some delval(s) contain error (x) limits - ignored (this is first)");
        }
      } 
    }
   else
    { 
     /* case 3: non r/e lim value - normal delay from list */
     if (!rd_rtriple(f, &(vtp[nvals]))) return(-1);
     nvals++;  
     if (nvals > 12) goto too_many;
    }

nxt_del:
   get_sdftok(f);
   if (__toktyp == RPAR) break;
   if (__toktyp != LPAR) goto bad_list; 
   get_sdftok(f);
  }
 /* starts from 0 but nvals set at unfilled next to fill so same as number */
 return(nvals);
}

/*
 * read one real (including negative) numeric expression as vpi time
 *
 * fills dap and returns T - if error returns F dap may or may not be set
 *
 * <value> or <min>:<typ>:<max> where all but one can be omitted 
 * for <min>:<typ>:<max> at least one value and two : required
 * RNUMBER form also read 
 *
 * assumes rtriple (or degenerate one value) always followed by )
 * mintypmax selector from command line option or sdf syst override
 * used to select value - sets vpiSuppressTime if missing 
 *
 * this does not scale, delay preparation does that
 *
 * first token read (probably after '(') and reads ending )
 * LOOKATME - possibly faster if not always convert to double but
 * think SDF standard requires
 */
static int32 rd_rtriple(FILE *f, struct t_vpi_time *dap)
{
 double d1, d2, d3;
 int32 has_min, has_typ, has_max;

 d1 = d2 = d3 = 0.0;
 dap->type = vpiScaledRealTime;
 has_min = has_typ = has_max = TRUE;
 if (__toktyp == COLON) { has_min = FALSE; goto get_typ; }

 if (__toktyp == REALNUM) d1 = __itok_realval; 
 else if (__toktyp == NUMBER) d1 = (double) __sdf_tokval;
 else 
  {  
bad_rexp:
   __pv_ferr(1372, "SDF rtriple value or : expected - %s read",
    prt_sdftok());
   return(FALSE);
  }  

 get_sdftok(f);
 /* ([rnumber]) case */  
 if (__toktyp == RPAR) { dap->real = d1; return(TRUE); }
 if (__toktyp != COLON) goto bad_rexp; 

get_typ:
 get_sdftok(f);
 if (__toktyp == COLON) { has_typ = FALSE; goto get_max; }
 if (__toktyp == REALNUM) d2 = __itok_realval;
 else if (__toktyp == NUMBER) d2 = (double) __sdf_tokval;
 else goto bad_rexp; 
 get_sdftok(f);
 if (__toktyp != COLON) goto bad_rexp;

get_max:
 get_sdftok(f);
 if (__toktyp == RPAR) { has_max = FALSE; goto set_val; }
 if (__toktyp == REALNUM) d3 = __itok_realval;
 else if (__toktyp == NUMBER) d3 = (double) __sdf_tokval;
 else goto bad_rexp; 

 get_sdftok(f);
 if (__toktyp != RPAR) goto bad_rexp;
 
set_val:
 if (__sdf_mintypmax_sel == DEL_TYP)
  {
   if (!has_typ) dap->type = vpiSuppressTime; else dap->real = d2;
  }
 else if (__sdf_mintypmax_sel == DEL_MIN)
  {
   if (!has_min) dap->type = vpiSuppressTime; else dap->real = d1;
  }
 else if (__sdf_mintypmax_sel == DEL_MAX)
  {
   if (!has_max) dap->type = vpiSuppressTime; else dap->real = d3;
  }
 else __case_terr(__FILE__, __LINE__);
 return(TRUE);
}

/*
 * get a form ([name] (name in token) or )
 * return F on error
 */
static int32 rd_sdf_formtyp(FILE *f)
{
 if (__toktyp != LPAR)
  {
   if (__toktyp == RPAR) return(TRUE);
   __pv_ferr(1371, "SDF form starting '(' expected - %s read",
    prt_sdftok());
   return(FALSE);
  }
 get_sdftok(f);
 if (__toktyp < SDF_BKEYS)
  {
   __pv_ferr(1321, "SDF form name expected - %s read", prt_sdftok());
   return(FALSE);
  }
 return(TRUE);
}

/*
 * get a form ([name] (name in token) - error if not present
 * return F on error
 */
static int32 rd2_sdf_formtyp(FILE *f)
{
 get_sdftok(f);
 if (__toktyp != LPAR)
  {
   __pv_ferr(1371, "SDF form starting '(' expected - %s read",
    prt_sdftok());
   return(FALSE);
  }
 get_sdftok(f);
 if (__toktyp < SDF_BKEYS)
  {
   __pv_ferr(1321, "SDF form name expected - %s read", prt_sdftok());
   return(FALSE);
  }
 return(TRUE);
}

/*
 * read a string value (name of something) also reads terminating )
 * puts string into sdf work string - caller must allocate
 * in SDF 3.0, value can not be missing
 */
static int32 rd_sdf_strval(FILE *f)
{
 get_sdftok(f);
 if (__toktyp != LITSTR)
  {
   __pv_ferr(1320, "string value expected - %s read", prt_sdftok());
   return(FALSE);
  }
 strcpy(__sdf_work_str, __token);
 get_sdftok(f);
 if (__toktyp != RPAR)
  {
   __pv_ferr(1322, "string value not followed by ) - %s read", prt_sdftok());
   return(FALSE);
  }
 return(TRUE);
}


/*
 *  SDF TOKEN INPUT ROUTINES
 */

/*
 * ascii character table for processing end of ID tokens
 * 0: continue - legal ID char (letter, digit, _) 
 * 1: end and don't back up (white space)
 * 2: end and back up (operators)
 * 3: inc lin_cnt and end - only new line
 * 4: illegal ID char
 * 5: \\ escape - include next char unless white space
 * 6: [] - bit select part of ID - need to set flag
 * 7: :  - part select part of ID - in expr. (not embedded in ID) normal op
 *
 * . can start number only except for catching separator path prefix error
 * table allows [], ., and : in IDs because that is SDF semantics
 * ID where [ is possible must be parsed by caller 
 *
 * 0x5f is _ and $ are legal starting and in IDs (value 0)
 */
static char sdf_ctab[128] = {
 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 4, 1, 1, 4, 4, /* ^i,\n,\f,\r */
 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
 /* need to handle " */
 1, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* sp,!,%,#,(,),*,',+,-,.,/ */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 2, 2, 2, 2, /* digits, :,;,<,-,>,? */
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* @, cap letters */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 5, 6, 2, 0, /* letters, [, \\,], ^, */
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* `, letters */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2  /* lettes, {, |, },~,EOF */
};

/* DBG remove and fix ---
static void get_sdftok(FILE *f)
{
 static void get2_sdftok(FILE *);

 get2_sdftok(f);
 __cvsim_msg("-- line %d: token [%s]\n", __lin_cnt, prt_sdftok());
}
--- */

/*
 * get a -f file option token - only white space separation
 * (modified from yylex in "The Unix Programming Environment" p. 337)
 * notice no push back token here
 *
 * this collects selects (including part select) and xmrs because that
 * is SDF semantics - part of ID - caller must parse because selects
 * and non escaped path separator must appear as selects and XMRs in Verilog 
 *
 * LOOKATME - algorithm is to allow any [], . or : in ID, only checked when
 * ID mapped to Verilog - where [] becomes selects
 */
static void get_sdftok(FILE *f)
{
 /* the char must be an int32 for machine independence */
 int32 c, ctval;
 int32 len, c1, t1typ;
 char *cp;
 int32 toolong;
 
 len = 0;
 /* these must be turned off because possibly set by last call */
 __id_qualpath = FALSE;
 __id_select = FALSE;
 __id_partsel = FALSE;

again:
 do { ctval = sdf_ctab[(c = getc(f)) & 0x7f]; } while (ctval == 1);
 if (c == '\n')
  {
again2:
   __lin_cnt++;
   do { ctval = sdf_ctab[(c = getc(f)) & 0x7f]; } while (ctval == 1);
   if (c == '\n') goto again2; 
  }
 switch (c) {
  case EOF: __toktyp = TEOF; return;
  /* notice as first char - token for ?: expr. operator or mtm value */
  /* but in ID since selector part, part of token */
  case ':':__toktyp = COLON; return;
  case '#': __toktyp = SHARP; return;
  /* CHECKME - where can $ appear, ` in number? */
  case '$': __toktyp = SDF_DOL; return;
  case ',': __toktyp = COMMA; return;
  case '[': __toktyp = LSB; return; 
  case ']': __toktyp = RSB; return; 
  case '{': __toktyp = LCB; return;
  case '}': __toktyp = RCB; return;
  case '?': __toktyp = QUEST; return;
  case '(': __toktyp = LPAR; return;
  case ')': __toktyp = RPAR; return;
  /* special for ' in 1'b[val] form */ 
  case '\'':
   /* SJM 05/14/01 - need to collect 4 cases of `[bB][01] form scalars */
   /* if scalar not allowed in context just return quote, error later */
   if (!__rding_cond_expr) { __toktyp = SDF_QUOTE; return; }

   c = getc(f) & 0x7f;
   if (c != 'b' && c != 'B') 
    { ungetc(c, f); __toktyp = SDF_QUOTE; return; }
rd_scalar_const:
   c1 = getc(f) & 0x7f;
   if (c1 == '0') { __sdf_tokval = 0; __toktyp = NUMBER; return; }
   if (c1 == '1') { __sdf_tokval = 1; __toktyp = NUMBER; return; }
bad_scalar:
   __pv_ferr(1382,
    "SDF path delay condition scalar constant %c illegal value - only 0 or 1 allowed",
    c1);
   __token[0] = '\''; __token[1] = c; __token[2] = c1; __token[3] = '\0';
   __toktyp = BADOBJ;
   return;
  case '`': __toktyp = SDF_BACKQ; return;
  case '*': __toktyp = TIMES; return;
  case '/': 
   if ((t1typ = sdf_rd_comment(f)) == UNDEF) goto again;
   /* know path sep '/' or ID not returned */
   if (t1typ == ID)
    {
     __id_qualpath = TRUE;
     ctval = sdf_ctab[(c = getc(f)) & 0x7f];
     cp = __token;
     *cp++ = '/';  
     len = 1;
     goto collect_id;
    }
   if (t1typ == TEOF) __toktyp = t1typ; else __toktyp = DIV;
   return;
  case '%': __toktyp = MOD; return;
  case '~':
   if ((c1 = getc(f)) == '^') { __toktyp = REDXNOR; return; }
   ungetc(c1, f);
   __toktyp = BITNOT;
   return;
  case '&':
   if ((c1 = getc(f)) == '&') { __toktyp = BOOLAND; return; }
   ungetc(c1, f);
   __toktyp = BITREDAND;
   return;
  case '|':
   if ((c1 = getc(f)) == '|') { __toktyp = BOOLOR; return; }
   ungetc(c1, f);
   __toktyp = BITREDOR;
   return;
  case '^':
   if ((c1 = getc(f)) == '~') { __toktyp = REDXNOR; return; }
   ungetc(c1, f);
   __toktyp = BITREDXOR;
   return;
  /* notice no C assignment op operators */
  case '=':
   if ((c1 = getc(f)) != '=')
    {
     __pv_ferr(1374, "SDF operator '=' illegal");
     __token[0] = '?';
     __token[1] = '\0';
     __toktyp = BADOBJ;
     return;
    }
   if ((c1 = getc(f)) != '=') { ungetc(c1, f); __toktyp = RELEQ; return; }
   __toktyp = RELCEQ;
   return;
  case '!':
   if ((c1 = getc(f)) != '=') { ungetc(c1, f); __toktyp = NOT; return; }
   if ((c1 = getc(f)) != '=') { ungetc(c1, f); __toktyp = RELNEQ; return; }
   __toktyp = RELCNEQ;
   return;
  case '>':
   if ((c1 = getc(f)) == '=') { __toktyp = RELGE; return; }
   else if (c1 == '>')
    {
     /* SJM 10/01/03 - add parsing of arithmetic right shift >>> */  
     if ((c1 = getc(f)) == '>') { __toktyp = ASHIFTR; return; }
     ungetc(c1, f);
     __toktyp = SHIFTR;
     return;
    }
   ungetc(c1, f);
   __toktyp = RELGT;
   return;
  case '<':
   if ((c1 = getc(f)) == '=') { __toktyp = RELLE; return; }
   else if (c1 == '<') 
    {
     /* SJM 10/01/03 - add parsing of arithmetic right shift >>> */  
     if ((c1 = getc(f)) == '<') { __toktyp = ASHIFTL; return; }
     ungetc(c1, f);
     __toktyp = SHIFTL;
     return;
    }
   ungetc(c1, f);
   __toktyp = RELLT;
   return;   
  case '\\':
   /* IDs can start with escaped characters */
   c = getc(f);
   ctval = sdf_ctab[c & 0x7f];
   if (ctval == 1 || ctval == 3)  
    {
     __pv_ferr(1377,
      "escaped white space illegal in SDF file (illegal in IDs)");
     __toktyp = BADOBJ;
     __token[0] = '?';
     __token[1] = '\0';  
     return;
    }
   cp = __token;
   *cp++ = '\\';  
   len = 1;
   goto collect_id;
  case '"': __toktyp = sdf_collect_str(f); return;

  case '1':
   /* SJM 05/14/01 - 1 special case if reading IOPATH cond expr */
   /* if scalar not allowed in context, treat as normal number */
   if (!__rding_cond_expr) goto get_num;
   c1 = getc(f) & 0x7f;
   /* if not scalar constant, collect as normal number */
   if (c1 != '\'') { ungetc(c1, f); goto get_num; }
   c = getc(f) & 0x7f;
   if (c != 'b' && c != 'B') goto bad_scalar;
   goto rd_scalar_const;

  case '+': case '-': case '.': case '0':
  case '2': case '3':
  case '4': case '5': case '6': case '7': case '8': case '9':
get_num: 
   __toktyp = sdf_collect_num(f, c);
   /* if path separator . and starts with ".[letter]", the ID returned */
   if (__toktyp == ID)
    {
     /* ID first char, un-getted in collect number, must reread */
     __id_qualpath = TRUE;
     ctval = sdf_ctab[(c = getc(f)) & 0x7f];
     cp = __token;
     *cp++ = '.';  
     len = 1;
     goto collect_id;
    }
   return;
 }
 /* here know digits eliminated so only letters, $, and _ have ct val 0 */
 /* i.e. ID must start with _, $, or letter */ 
 if (ctval != 0)
  {
   __token[0] = '?';
   __token[1] = '\0';
   __pv_ferr(1375, "SDF file contains illegal character %c (%x)", c, c);
   /* just some impossible token */
   __toktyp = BADOBJ;  
   return;
  }
 /* try to recognize some kind of id - only - know c and ctval */
 /* obviously in spite of SDF LRM, ID can not start with number */
 cp = __token;
collect_id:
 for (toolong = FALSE;;)
  {
   /* loop backward - know good character to add here - check and fix below */
   if (++len >= IDCHARS)
    {
     if (!toolong)
      {
       __pv_ferr(1376, "SDF identifier too long (%d) - truncated",
        IDCHARS - 1);
       toolong = TRUE;
      }
    }
   else *cp++ = c;

   c = getc(f);
   if ((ctval = sdf_ctab[c & 0x7f]) == 0) continue;

   /* if entire escaped - will not see any of these */
   /* if component escaped - may need to fixup later */
   if (c == __pathsep) { __id_qualpath = TRUE; continue; }
   if (ctval == 6) { __id_select = TRUE; continue; }
   if (ctval == 7) { __id_partsel = TRUE; continue; }
/* ---
   if (c == __pathsep)
    { *cp++ = c; len++, c = getc(f); __id_qualpath = TRUE; continue; }
   if (ctval == 6) 
    { *cp++ = c; len++; c = getc(f); __id_select = TRUE; continue; }
   if (ctval == 7) 
    { *cp++ = c; len++; c = getc(f); __id_partsel = TRUE; continue; }
--- */

   /* any escaped part of SDF ID - escape remains and next not special */ 
   if (ctval == 5) 
    {
     c = getc(f);
     ctval = sdf_ctab[c & 0x7f];
     if (ctval == 1 || ctval == 3)  
      {
       __pv_ferr(1377, "SDF identifier cannot escape white space - ended");
       *cp = '\0';
       goto end_id;
      }
     /* must leave escape character in ID */
     *cp++ = '\\';
     len++;
     /* c is character after ID, always added above then get next above */
     /* i.e. no special checking for current c */
     continue;
    }
   ungetc(c, f);
   goto end_id;
  }
end_id:
 *cp = '\0';
 /* no reason to lookup if has select or path separator - know can't match */
 if (__id_qualpath || __id_select || __id_partsel) __toktyp = ID;
 else __toktyp = get_sdfkeywrd(__token);
}

/*
 * read a comment (either / * or //)
 */
static int32 sdf_rd_comment(FILE *f)
{
 int32 c, c2;

 c2 = getc(f);
 /* /[ID] possible as path - return with indicator */  
 if (__pathsep == '/' && (isalpha(c2) || c2 == '_'))
  { ungetc(c2, f); return(ID); }

 /* // to EOL comment */
 if (c2 == '/')
  {
   while ((c = getc(f)) != '\n') if (c == EOF) return(TEOF);
   ungetc(c, f);
   return(UNDEF);
  }
 /* slash-star comments don't nest */
 if (c2 == '*')
  {
more_comment:
   while ((c = getc(f)) != '*')
    {
     /* error if / * comments nested */
     if (c == '/')
      {
       if ((c2 = getc(f)) == '*')
        {
         __pv_fwarn(663, "SDF delay file nested /* in /* style comment");
         continue;
        }
       c = c2;
      }
     if (c == EOF) return(TEOF);
     if (c == '\n') __lin_cnt++;
    }
got_star:
   if ((c = getc(f)) == '/') return(UNDEF);
   if (c == '*') goto got_star;
   if (c == '\n') __lin_cnt++;
   goto more_comment;
  }
 /* not a comment so treat as name token */
 /* notice c2 here must be most recent because above if never falls through */
 ungetc(c2, f);
 return(DIV);
}

/*
 * collect an sdf file form string
 */
static int32 sdf_collect_str(FILE *f)
{
 char *cp, c;
 int32 namlen;

 for (cp = __token, namlen = 0;;)
  {
   /* SJM 03/20/00 - for SDF all tokens and strings limited to id len */
   if (++namlen >= IDLEN - 1)
    {
     __pv_ferr(1311, "SDF quoted string too long (%d) - truncated", IDLEN);
     *cp = '\0';
     for (;;)
      {
       if ((c = getc(f)) == '"') return(LITSTR);
       if (c == '\n') __lin_cnt++;
       if (c == EOF) goto unterm_str;
      }
    }
   if ((c = getc(f)) == '"') break;
   if (c == '\n')
    {
     __pv_fwarn(672, "new line embedded in SDF quoted string");
     __lin_cnt++;
    }
   if (c == EOF)
    {
unterm_str:
     __pv_ferr(1312, "unterminated SDF string");
     return(TEOF);
    }
   *cp++ = c; 
  }
 *cp = '\0';
 return(LITSTR);
}

/*
 * collect a number and convert to value
 * if has . becomes real - this uses c scanf to read
 */
static int32 sdf_collect_num(FILE *f, int32 c)
{
 char *cp;
 int32 c1, fill, namlen, is_real, errnum, signv, t1;
 double d1;
 char *endp;
 
 /* for .[letter] form and path separator dot handle rooted path */
 if (c == '.' &&__pathsep == '.')
  {
   c1 = getc(f);
   ungetc(c1, f);
   if (isalpha(c1) || c1 == '_') return(ID);
  }

 signv = FALSE;
 if (c == '+' || c == '-')  
  {
   if (c == '-') signv = TRUE;
   c1 = getc(f);
   if (!isdigit(c1) && c1 != '.') 
    {
     if (c == '-') return(MINUS);
     return(PLUS);
    }
   c = c1;
  }
 fill = TRUE;
 is_real = FALSE;
 for (namlen = 0, cp = __token;;)
  {
   if (++namlen >= IDLEN - 1)
    {
     __pv_ferr(1313, "SDF number too long (%d) - truncated", IDLEN);
     *cp = '\0';
     fill = FALSE;
    }
   switch (c) {
    case '+': case '-': case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7': case '8': case '9': 
     if (fill) *cp++ = c; break;
    case '.': case 'e': case 'E':
     is_real = TRUE;
     if (fill) *cp++ = c; break;
    default: *cp = '\0'; goto got_num;
   }
   c = getc(f);
  }
got_num: 
  ungetc(c, f);
  if (is_real)
   {
    d1 = __my_strtod(__token, &endp, &errnum);   
    if (errnum != 0 || *endp != '\0')
     {
      __pv_ferr(1314, "SDF real number %s illegal", __token);
      d1 = 1.0;
     }
    __itok_realval = d1;
    return(REALNUM);
   }
 /* integer number */
 t1 = __my_strtoul(__token, &endp, &errnum);
 if (errnum != 0 || *endp != '\0')
  {
   __pv_ferr(1315, "SDF integer number %s illegal", __token);
   t1 = 1;
  }
 if (signv) t1 = -t1;
 __sdf_tokval = t1;
 return(NUMBER);
}

/*
 * check and convert SDF path name (always . separator) to Verilog ID 
 * returns F on error - caller must emit any error
 *
 * this builds the Verilog path ID that is converted to xmr expr later
 * indices here extracted according to SDF format and convert to Verilog fmt
 */
static int32 chkcnv_sdfpath(char *verid, int32 *i1, int32 *i2, char *sdfid,
 int32 allow_select)
{
 char *chp, *chp2;
 int32 ind1, ind2;
 char s1[IDLEN], s2[RECLEN];

 /* step 1: convert from rooted if needed */
 if (*sdfid == __pathsep) 
  {
   __pv_fwarn(676,
    "SDF leading %c removed from %s - SDF paths downward relative from context",
    __pathsep, sdfid); 
   sdfid++;  
   if (*sdfid == __pathsep) return(FALSE);
  }
 /* check all but ending component of path */
 strcpy(verid, "");
 for (chp = sdfid; *chp != '\0';)
  {
   if ((chp2 = fnd_pth_sep(chp)) == NULL) break;

   /* if path component starts with separator, illegal empty */
   if (chp == chp2) return(FALSE);
   strncpy(s1, chp, chp2 - chp);
   s1[chp2 - chp] = '\0';
   /* even in non select variable path, internal insts can have selects */
   if (!chkcnv_sdfid(s2, &ind1, &ind2, s1, TRUE)) return(FALSE);

   /* part select of instance array never allowed */
   if (ind1 != ind2) return(FALSE);

   /* add select back onto end as suffix if needed */
   if (ind1 != -1) { sprintf(s1, "%s[%d]", s2, ind1); strcpy(s2, s1); }

   if (strlen(verid) + strlen(s2) >= IDLEN - 2)
    {
toolong:
     __pv_ferr(1368, "Verilog path name too long (%d)", IDLEN); 
     return(FALSE);
    }
   if (*verid != '\0') strcat(verid, ".");
   strcat(verid, s2);
   chp = ++chp2;
  }
 /* s1 is path tail */
 /* part select of tail may be legal */
 /* add select back onto end as suffix if needed */
 if (!chkcnv_sdfid(s1, i1, i2, chp, allow_select)) return(FALSE);

 if (strlen(verid) + strlen(s1) >= IDLEN - 2) goto toolong;
 if (*verid != '\0') strcat(verid, ".");
 strcat(verid, s1);
 return(TRUE);
}

/*
 * find path separator - must skip over escaped
 */
static char *fnd_pth_sep(char *chp)
{
 char *chp2;

again:
 if ((chp2 = strchr(chp, __pathsep)) == NULL) return(NULL);
 if (chp2 == chp) return(chp2);
 if (chp2[-1] == '\\') { chp = ++chp2; goto again; } 
 return(chp2);
}

/*
 * check and convert SDF ID to Verilog ID (may need to be escaped)
 * because of possible select this can fail - return F and caller emits error
 *
 * notice path separators here '.' or '/' are part of Verilog escaped IDs
 * because if escaped as char will be embedded in sdfid
 *
 * know simple id (not a path)
 * if called with path (non escaped separator(s)) in non path context
 * becomes escaped ID and will probably not match Verilog 
 */
static int32 chkcnv_sdfid(char *verid, int32 *i1, int32 *i2, char *sdfid,
 int32 allow_select)
{
 char *chp, *chp2;
 int32 nd_escver_id;
 char s1[IDLEN], s2[IDLEN];

 *i1 = *i2 = -1;
 if (__id_select || __id_partsel)
  {
   /* here have qualified path where some component has select */
   /* if not this one tread as non select */
   if ((chp = strrchr(sdfid, '[')) == NULL)
    {
     strcpy(s1, sdfid);
     goto comp_non_sel;
    }
   strcpy(s1, ++chp);
   if (!sdf_getsel_indices(i1, i2, s1)) return(FALSE);
   chp--;
   strncpy(s1, sdfid, chp - sdfid);
   s1[chp - sdfid] = '\0';
   if (!allow_select) return(FALSE);
  }
 else strcpy(s1, sdfid);

comp_non_sel:
 nd_escver_id = FALSE;
 if (isdigit(s1[0])) nd_escver_id = TRUE; 
 for (chp = s1, chp2 = verid; *chp != '\0'; chp++) 
  {
   if (sdf_ctab[*chp & 0x7f] != 0) nd_escver_id = TRUE;
   *chp2++ = *chp;
   if (chp2 - verid >= IDLEN - 1)
    {
toolong:
     __pv_ferr(1368, "Verilog identifier name too long (%d) - truncated",
      IDLEN); 
     break;
    }
  }
 *chp2 = '\0';
 if (nd_escver_id)
  {
   if (strlen(verid) + 2 >= IDLEN + 1)
    { verid[IDLEN - 3] = '\0'; goto toolong; }
   chp = s2;
   *chp++ = '\\';
   for (chp2 = verid; *chp2 != '\0';) 
    {
     if (*chp2 == '\\') { chp2++; continue; }
     *chp++ = *chp2++;
    }
   *chp++ = ' ';
   *chp = '\0';
   strcpy(verid, s2);
  }
 return(TRUE);
}

/*
 * extract range(s) from select part of sdf id - s starts with one past [
 *
 * because passed with real (non escaped) [ at start no escape checking needed
 * escaped digit or escaped ] is error
 */
static int32 sdf_getsel_indices(int32 *i1, int32 *i2, char *s)
{
 char *chp, *chp2;
 char s1[RECLEN], s2[RECLEN];

 *i1 = *i2 = -1;
 /* check for illegal chars after ending ] */ 
 if ((chp = strrchr(s, ']')) == NULL) __arg_terr(__FILE__, __LINE__);
 chp++;
 if (*chp != '\0' || chp[-1] == '\\') return(FALSE);
 chp--;
 strncpy(s1, s, chp - s);
 s1[chp - s] = '\0';

 /* extract 2nd range if present */
 if (__id_partsel)
  {
   if ((chp = strchr(s1, ':')) == NULL) __arg_terr(__FILE__, __LINE__);
   chp++;
   strcpy(s2, chp);
   chp--;
   chp--;
   *chp = '\0';
   /* 2nd index in s2 */
   for (chp2 = s2; *chp2 != '\0'; chp2++)
    {
     if (!isdigit(*chp2)) return(FALSE);
    }
   if (sscanf(s2, "%d", i2) != 1) return(FALSE);
  }
 /* extract first range - know it is in s1 */
 /* first index in s1 */
 for (chp2 = s1; *chp2 != '\0'; chp2++)
  {
   if (!isdigit(*chp2)) return(FALSE);
  }
 if (sscanf(s1, "%d", i1) != 1) return(FALSE);
 if (!__id_partsel) *i2 = *i1;
 return(TRUE);
}

/*
 * after reading ([name] form - skip to matching )
 * returns F on no match before eof
 */
static int32 sdf_skip_form(FILE *f)
{
 int32 par_cnt = 0;

 for (;;)
  {
   get_sdftok(f);
   if (__toktyp == RPAR) { if (--par_cnt < 0) break; }
   if (__toktyp == LPAR) par_cnt++;
   if (__toktyp == TEOF) return(FALSE);
  }
 return(TRUE);
}

/*
 * read an SDF edge - if edge returns edge number else -1
 * if returns -1 sets __toktyp and __token as if normal ID read
 * 
 * this must read chars since not normal tokens
 * timing checks allow edge expressions but not paths
 * only called in places where operators illegal
 */
static int32 rd_edge_ident(FILE *f)
{
 char *cp;
 int32 c, ctval, len;

 /* skip white space */
 do { ctval = sdf_ctab[(c = getc(f)) & 0x7f]; } while (ctval == 1);
 if (ctval != 0)
  {
   __pv_ferr(1345,
    "possible EDGE_IDENTIFIER starting character %c (%x) illegal",
    c, c);
   return(-1);
  }
 /* collect non white space chars */
 for (cp = __token, len = 0;;)  
  {
   *cp++ = c;
   if (++len >= IDLEN)
    {
     __pv_ferr(1347, "EDGE_IDENTIFIER too many characters (%d)", IDLEN);
     return(-1);
    }
   ctval = sdf_ctab[(c = getc(f)) & 0x7f];
   if (ctval != 0) { ungetc(c, f); break; }  
  }
 *cp = '\0';
 if (strcmp(__token, "posedge") == 0) return(E_POSEDGE);
 if (strcmp(__token, "negedge") == 0) return(E_NEGEDGE);
 if (strcmp(__token, "01") == 0) return(EDGE01);
 if (strcmp(__token, "10") == 0) return(EDGE10);
 if (strcmp(__token, "0x") == 0) return(EDGE0X);
 if (strcmp(__token, "x1") == 0) return(EDGEX1);
 if (strcmp(__token, "1x") == 0) return(EDGE1X);
 if (strcmp(__token, "x0") == 0) return(EDGEX0);
 __toktyp = get_sdfkeywrd(__token);
 return(-1);
}

/*
 * read an SDF cond scalar constant - returns val (-1 on error)
 * 
 * needed because ' in constants not defined in SDF
 * this must read chars since not normal tokens
 * this expect nothing read and reads just to end of constant
 */
static int32 rd_scalar_const(FILE *f)
{
 int32 c, ctval;

 /* skip white space */
 do { ctval = sdf_ctab[(c = getc(f)) & 0x7f]; } while (ctval == 1);
 if (c == '1')
  {
   /* SJM 01/24/02 - was not reading next c so only 1'b0 and 1'b1 wrong err */ 
   c = getc(f) & 0x7f;
   if (c == '\'')
    {
do_base:
     c = getc(f);
     if (c != 'b' && c != 'B') goto bad_scalar;
     c = getc(f);
     /* wrong following char caught by next get token call */
     if (c == '0') return(0);
     if (c == '1') return(1);
     goto bad_scalar;
    }
   if (c == '0') return(0);
   if (c == '1') return(1);
   goto bad_scalar;
  }
 if (c == '\'') goto do_base;  

bad_scalar:
 __pv_ferr(1355, "SCALAR_CONSTANT illegal - %c (%x) bad", c, c);
 return(-1);
}

/*
 * print a sdf token
 *
 * uses prt vtok since value in __token value except for number or real num.
 */
static char *prt_sdftok(void)
{
 /* notice this must not change current val. of token */
 if (__toktyp >= SDF_BKEYS)
  { get_skeynam(__sdf_varnam, __toktyp); return(__sdf_varnam); }

 switch (__toktyp) {
  case TEOF: strcpy(__token, "**EOF**"); break;
  case ID: return(__token);
  /* must recreate because sign may be missing */
  case NUMBER: sprintf(__token, "%d", __sdf_tokval); break;
  case REALNUM: sprintf(__token, "%#g", __itok_realval); break;
  case LITSTR: return(__token);
  case COLON: strcpy(__token, ":"); break;
  case SHARP: strcpy(__token, "#"); break;
  case SDF_DOL: strcpy(__token, "$"); break; 

  /* SJM - 05/14/01 - next 2 illegal but needed for error msg */
  case SDF_BACKQ: strcpy(__token, "`"); break; 
  case SDF_QUOTE: strcpy(__token, "'"); break; 

  case COMMA: strcpy(__token, ","); break;
  case LCB: strcpy(__token, "{"); break; 
  case RCB: strcpy(__token, "}"); break;
  case QUEST: strcpy(__token, "?"); break;
  case LSB: strcpy(__token, "["); break;
  case RSB: strcpy(__token, "]"); break;
  case LPAR: strcpy(__token, "("); break;
  case RPAR: strcpy(__token, ")"); break; 
  case PLUS: strcpy(__token, "+"); break; 
  case MINUS: strcpy(__token, "-"); break;
  case TIMES: strcpy(__token, "*"); break;
  case DIV: strcpy(__token, "/"); break; 
  case MOD: strcpy(__token, "%"); break; 
  case BITNOT: strcpy(__token, "~"); break; 
  case REDXNOR: strcpy(__token, "^~"); break;
  case BOOLAND: strcpy(__token, "&&"); break;
  case BITREDAND: strcpy(__token, "&"); break;
  case BOOLOR: strcpy(__token, "||"); break; 
  case BITREDOR: strcpy(__token, "|"); break;
  case BITREDXOR: strcpy(__token, "^"); break; 
  case RELEQ: strcpy(__token, "=="); break;
  case RELCEQ: strcpy(__token, "==="); break; 
  case NOT: strcpy(__token, "!"); break;
  case RELNEQ: strcpy(__token, "!="); break;  
  case RELCNEQ: strcpy(__token, "!=="); break;
  case RELGE: strcpy(__token, ">="); break;
  case SHIFTR: strcpy(__token, ">>"); break;
  case ASHIFTR: strcpy(__token, ">>>"); break;
  case RELGT:  strcpy(__token, ">"); break;
  case RELLE: strcpy(__token, "<="); break;
  case SHIFTL: strcpy(__token, "<<"); break;
  case ASHIFTL: strcpy(__token, "<<<"); break;
  case RELLT: strcpy(__token, "<"); break;
  case UNDEF: strcpy(__token, "**NONE**"); break; 
  case BADOBJ: strcpy(__token, "**ILLEGAL**"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(__token);
}

/* keyword types (already know token is a name) */
struct sdfkeywds_t {
 char *sknam;
 int32 sknum;
};

/* since sharing operators for expr. processing with Verilog, first > 99 */
/* BEWARE - must be kept in alphabetical order */
static struct sdfkeywds_t skeywds[] = {
 { "ABSOLUTE", SDF_ABSOLUTE },
 { "ARRIVAL", SDF_ARRIVAL },
 { "CCOND", SDF_CCOND },
 { "CELL", SDF_CELL },
 { "CELLTYPE", SDF_CELLTYPE },
 { "COND", SDF_COND },
 { "CONDELSE", SDF_CONDELSE },
 { "DATE", SDF_DATE },
 { "DELAY", SDF_DELAY },
 { "DELAYFILE", SDF_DELAYFILE },
 { "DEPARTURE", SDF_DEPARTURE },
 { "DESIGN", SDF_DESIGN },
 { "DEVICE", SDF_DEVICE },
 { "DIFF", SDF_DIFF },
 { "DIVIDER", SDF_DIVIDER },
 { "EXCEPTION", SDF_EXCEPTION },
 { "FULLSKEW", SDF_FULLSKEW },
 { "HOLD", SDF_HOLD },
 { "INCREMENT", SDF_INCREMENT },
 { "INSTANCE", SDF_INSTANCE },
 { "INTERCONNECT", SDF_INTERCONNECT },
 { "IOPATH", SDF_IOPATH },
 { "LABEL", SDF_LABEL },
 { "NAME", SDF_NAME },
 { "NOCHANGE", SDF_NOCHANGE },
 { "PATHCONSTRAINT", SDF_PATHCONSTRAINT },
 { "PATHPULSE", SDF_PATHPULSE },
 { "PATHPULSEPERCENT", SDF_PATHPULSEPERCENT },
 { "PERIOD", SDF_PERIOD },
 { "PERIODCONSTRAINT", SDF_PERIODCONSTRAINT },
 { "PORT", SDF_PORT },
 { "PROCESS", SDF_PROCESS },
 { "PROGRAM", SDF_PROGRAM },
 { "RECOVERY", SDF_RECOVERY },
 { "RECREM", SDF_RECREM },
 { "REMOVAL", SDF_REMOVAL },
 { "RETAIN", SDF_RETAIN },
 { "SCOND", SDF_SCOND },
 { "SDFVERSION", SDF_VERSION }, 
 { "SETUP", SDF_SETUP }, 
 { "SETUPHOLD", SDF_SETUPHOLD }, 
 { "SKEWCONSTRAINT", SDF_SKEWCONSTRAINT },
 { "SLACK", SDF_SLACK },
 { "SKEW", SDF_SKEW }, 
 { "SUM", SDF_SUM }, 
 { "TEMPERATURE", SDF_TEMPERATURE },
 { "TIMESCALE", SDF_TIMESCALE },
 { "TIMESKEW", SDF_TIMESKEW },
 { "TIMINGCHECK", SDF_TIMINGCHECK },
 { "TIMINGENV", SDF_TIMINGENV },
 { "VENDOR", SDF_VENDOR },
 { "VERSION", SDF_VERSION },
 { "VOLTAGE", SDF_VOLTAGE },
 { "WAVEFORM", SDF_WAVEFORM },
 { "WIDTH", SDF_WIDTH },
 { "negedge", SDF_NEGEDGE },
 { "posedge", SDF_POSEDGE }
};
#define NSKEYWDS (sizeof(skeywds) / sizeof(struct sdfkeywds_t))

/*
 * determine type of keyword or ident
 * binary search because the table is so big
 */
static int32 get_sdfkeywrd(char *tstr)
{
 int32 l, h;
 int32 m, cv;

 l = 0; h = NSKEYWDS - 1;
 for (;;)
  {
   m = (l + h)/2;
   if ((cv = strcmp(skeywds[m].sknam, tstr)) == 0) return(skeywds[m].sknum);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) break;
  }
 return(ID);
}

/*
 * determine keyword name from number
 * must use linear search since not sorted
 */
static char *get_skeynam(char *s, int32 knum)
{
 int32 vi;

 for (vi = 0; vi < NSKEYWDS; vi++)
  {
   if (skeywds[vi].sknum == knum)
   {
    strcpy(s, skeywds[vi].sknam);
    return(s);
   }
  }
 strcpy(s, "--none--");
 return(s);
}
