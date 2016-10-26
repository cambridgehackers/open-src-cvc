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
 * third source module reads tasks/functions, udps and specify section
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>

#include <sys/dir.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

/* local prototypes */
static struct udp_t *alloc_udp(struct sy_t *);
static int32 rd_udp_hdr(struct udp_t *);
static int32 rd_udp_decls(void);
static int32 rd_udp_init(struct udp_t *);
static int32 chkcnt_uports(struct udp_t *);
static int32 rd_udp_table(struct udp_t *);
static void str_tolower(char *, char *);
static int32 cvrt_udpedges(char *, char *);
static int32 to_udp_levsym(char);
static int32 chk_comb_udpline(char *, struct udp_t *, int32 *);
static int32 chk_sequdpline(char *, struct udp_t *, int32 *);
static char to_edgech(int32);
static int32 is_edgesym(char);
static char *to_codedge_line(char *, char *);
static void extra_chk_edgeudp(struct udp_t *);
static char *to_udp_prtnam(struct udp_t *, int32);
static void dmp_udp_lines(FILE *, struct udp_t *);
static struct spfy_t *alloc_spfy(void);
static int32 rd_specparamdecl(void);
static int32 rd_delay_pth(void);
static struct exprlst_t *rd_pthtermlst(void);
static int32 col_pthexpr(void);
static int32 rd_pathdelaylist(struct paramlst_t **);
static void init_spcpth(struct spcpth_t *);
static int32 rd_setup_or_hold_tchk(word32);
static int32 rd_tchk_part(word32, struct tchk_t *, struct expr_t **);
static int32 rd_setuphold_tchk(void);
static int32 rd_optional_tc_cond(struct expr_t **, int32);
static int32 rd_optional_tc_delayed_net(struct expr_t **, int32);
static int32 rd_recrem_tchk(void);
static int32 rd_width_tchk(void);
static int32 rd_period_tchk(void);
static int32 rd_skew_recov_rem_tchk(word32);
static int32 rd_nochg_tchk(void);
static int32 rd_tchk_selector(int32 *, struct expr_t **, struct expr_t **);
static int32 rd_edges(int32 *);
static struct sy_t *rd_notifier(void);
static struct attr_t *chk_dup_attrs(struct attr_t *);
static int32 src_rd_chk_paramexpr(struct expr_t *, int32);

static int32 rd1_optcfg_fil(struct ocfil_lst_t *);
static int32 rd_optcfg_ver_el_list(struct oc_vtok_t **);
static int32 rd_optcfg_1ver_el(void);
static int32 rd_optcfg_prop_list(struct oc_vtok_t **);
static int32 rd_optcfg_1prop(void);
static void add_octok_toend(int32, int32, char *);
static int32 optcfg_skipto_semi(void);
static void dmp_dsgn_optcfgs(void);
static char *dbg_bld_ver_item_list_str(char *, struct oc_vtok_t *);
static void set_optcfg_bits_from_optcfgfils(void);
static void turn_on_design_wide_tgl_coverage(void);
static void alloc_init_m_itps_tgl_cover(struct mod_t *);
static void set_dsgn_tgl_cover_state(void); 
static struct sy_t *find_optcfg_xmr_object(struct oc_vtok_t *,
 struct itree_t **);
static struct itree_t *get_optcfg_down_itp(struct expr_t *, struct sy_t **,
 char *); 
static void set_tgl_1subtree_coverage(struct itree_t *, int32, int32, int32);
static void set_other_than_tgl_1subtree_coverage(struct mod_t *, int32,
  int32, int32);
static void turn_on_1mod_tgl_coverage(struct mod_t *);
static void turn_off_1mod_tgl_coverage(struct mod_t *);
static void turn_on_1inst_allnets_tgl_coverage(struct itree_t *);
static void turn_off_1inst_allnets_tgl_coverage(struct itree_t *, int32);
static void try_turn_on_1inst_net_tgl_coverage(struct itree_t *,
 struct net_t *, int32, int32);
static void turn_off_1inst_net_tgl_coverage(struct itree_t *, struct net_t *,
 int32, int32, int32);
static void alloc_init_1net_tgl(struct net_t *, struct mod_t *);
static void optcfg_free_1net_tgl_record(struct mod_t *, struct net_t *);
static void try_set_net_excl_bit(struct net_t *, int32);

static void set_stmt_cover_bits(struct mod_t *, struct inst_t *, int32);
static void set_event_cover_bits(struct mod_t *, struct inst_t *, int32);
#ifdef __XPROP__
static void set_xprop_bits(struct mod_t *, struct inst_t *, int32, int32);
#endif
static void set_plitab_acc(int32, struct mod_t *, struct inst_t *,
 struct net_t *, int32);
static void set_1mod_all_nets_acc(int32, struct mod_t *, int32);

static void rd1_cfg_file(FILE *);
static void rd_cfg_library(FILE *);
static struct libel_t *rd_cfg_fspec_list(FILE *, int32);
static void rd_cfg_cfg(FILE *);
static int32 chk_libid(char *);
static int32 chk_escid(char *);
static void init_rule(struct cfgrule_t *);
static int32 extract_design_nam(char *, char *, char *);
static int32 bld_inst_xmr_comptab(char *);
static void grow_bind_comps(void);
static int32 extract_libcell_nam(char *, char *, char *);
static int32 rd_use_clause(FILE *, char *, char *, int32 *);
static int32 extract_use_nam(char *, char *, int32 *, char *);
static struct cfgnamlst_t *rd_liblist(FILE *);

static void init_cfglib(struct cfglib_t *);
static void init_cfg(struct cfg_t *);
static int32 cfg_skipto_semi(int32, FILE *);
static int32 cfg_skipto_comma_semi(int32, FILE *);
static int32 cfg_skipto_semi_endconfig(int32, FILE *);
static int32 cfg_skipto_eof(int32, FILE *);

static void expand_dir_pats(struct cfglib_t *, struct libel_t *, char *);
static void expand_hier_files(struct cfglib_t *, struct libel_t *, 
 struct xpndfile_t *);
static void match_dir_pats(struct libel_t *, struct xpndfile_t *, char *, 
 char *, int32, int32);
static void movedir_match_dir_pats(struct libel_t *, struct xpndfile_t *); 
static void find_hier(struct libel_t *, struct xpndfile_t *, char *, char *);
static int32 match_hier_name(struct xpndfile_t *, char *);
static int32 match_wildcard_str(char *, struct xpndfile_t *);
static void expand_libel(struct libel_t *, char *);
static int32 expand_single_hier(struct cfglib_t *, struct libel_t *, char *);
static int32 has_wildcard(char *);
static void prep_cfg_vflist(void);
static void dump_config_info(void);
static void dump_lib_expand(void);
static int32 bind_cfg_design(struct cfg_t *, int32);
static struct cfglib_t *find_cfglib(char *);
static void free_undef_list(void);
static void bind_cells_in1mod(struct cfg_t *, struct cfglib_t *,
 struct mod_t *);
static int32 try_match_rule(struct cfglib_t *, struct cell_t *,
 struct cfgrule_t *);
static void build_rule_error(struct cfg_t *, struct cfglib_t *, 
struct cfgrule_t *);
static int32 bind_liblist_rule(struct cfg_t *, struct cell_t *,
 struct cfgrule_t *);
static int32 bind_use_rule(struct cfg_t *, struct cfglib_t *, struct cell_t *,
 struct cfgrule_t *);
static struct cfg_t *fnd_cfg_by_name(char *);
static void bind_cells_inside(struct cfg_t *, struct cell_t *,
 struct mod_t *, struct cfglib_t *);
static struct mod_t *find_cell_in_cfglib(char *, struct cfglib_t *);
static int32 open_cfg_lbfil(char *);
static void rd_cfg_srcfil(struct libel_t *);
static int32 init_chk_cfg_sytab(struct libel_t *, char *);
static void free_unused_cfgmods(void);
static void partially_free_mod(struct mod_t *);
static void add_cfg_libsyms(struct cfglib_t *);
static void add_cfgsym(char *, struct tnode_t *);

/* extern prototypes (maybe defined in this module) */
extern char *__pv_stralloc(char *);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern char *__prt_vtok(void);
extern char *__prt_kywrd_vtok(void);
extern char *__to_uvvnam(char *, word32);
extern char *__to_tcnam(char *, word32);
extern char *__to_sytyp(char *, word32);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct sy_t *__decl_sym(char *, struct symtab_t *);
extern struct sy_t *__bld_loc_symbol(int32, struct symtab_t *, char *, char *);

/* SJM 04-14-13 - added procs defined here prototypes plus xmr expr protos */
extern struct attr_t *__rd_parse_attribute(struct attr_t *);
extern void __rd_optcfg_files(void);
extern void __rd_setup_optcfg(void);
extern struct expr_t *__glbnam_to_expr(char *);
extern int32 __get_optcfg_prop_typ(struct ocfg_stmt_t *);

extern struct exprlst_t *__alloc_xprlst(void);
extern struct tnode_t *__vtfind(char *, struct symtab_t *);
extern struct symtab_t *__alloc_symtab(int32);
extern struct expr_t *__alloc_newxnd(void);
extern struct mod_pin_t *__alloc_modpin(void);
extern struct paramlst_t *__alloc_pval(void);
extern struct expr_t *__bld_rng_numxpr(word32, word32, int32);
extern int32 __vskipto_modend(int32);
extern void __add_sym(char *, struct tnode_t *);
extern int32 __chk_redef_err(char *, struct sy_t *, char *, word32);
extern void __remove_undef_mod(struct sy_t *);
extern void __get_vtok(void);
extern int32 __get1_vtok(FILE *);
extern void __unget_vtok(void);
extern void __dmp_udp(FILE *, struct udp_t *);
extern int32 __udp_vskipto_any(int32);
extern int32 __udp_vskipto2_any(int32, int32);
extern int32 __udp_vskipto3_any(int32, int32, int32);
extern int32 __wide_vval_is0(word32 *, int32);
extern int32 __vval_is1(word32 *, int32);
extern void __wrap_puts(char *, FILE *);
extern void __wrap_putc(int32, FILE *);
extern void __nl_wrap_puts(char *, FILE *);
extern int32 __fr_tcnam(char *);
extern int32 __spec_vskipto_any(int32);
extern int32 __spec_vskipto2_any(int32, int32);
extern int32 __spec_vskipto3_any(int32, int32, int32);
extern int32 __rd_opt_param_vec_rng(struct expr_t **, struct expr_t **, int32);
extern int32 __col_paramrhsexpr(void);
extern int32 __col_connexpr(int32);
extern int32 __col_comsemi(int32);
extern void __bld_xtree(int32);
extern void __set_numval(struct expr_t *, word32, word32, int32);
extern struct net_t *__add_param(char *, struct expr_t *, struct expr_t *,
 int32, int32);
extern int32 __col_parenexpr(int32, int32, int32);
extern int32 __bld_expnode(void);
extern void __set_xtab_errval(void);
extern int32 __col_delexpr(int32);
extern int32 __vskipto3_modend(int32, int32, int32);
extern void __init_tchk(struct tchk_t *, word32);
extern void __set_0tab_errval(void);
extern void __free_xtree(struct expr_t *);
extern void __free2_xtree(struct expr_t *);
extern char *__bld_lineloc(char *, word32, int32);
extern void __push_vinfil(void);
extern char *__to_glbcmp_nam(struct expr_t *);
extern char *__bld_glbcmp_ginam(char *, struct expr_t *);
extern int32 __ip_indsrch(char *);
extern int32 __expr_has_glb(struct expr_t *);
extern int32 __xpr_hasfcall(struct expr_t *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern void __sizchgxs(struct xstk_t *, int32);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern char *__msg2_blditree(char *, struct itree_t *);
extern void __cnv_stk_fromreal_toreg32(struct xstk_t *);
extern void __eval_param_rhs_tonum(struct expr_t *, int32, int32);
extern int32 __cmp_xpr(struct expr_t *, struct expr_t *, int32 *);
extern FILE *__tilde_fopen(char *, char *);
extern int32 __get_cfgtok(FILE *);
extern int32 __vskipto_modend(int32);
extern void __grow_infils(int32);
extern int32 __rd_cfg(void);
extern char *__to_cfgtoknam(char *, int32);
extern void __my_fclose(FILE *);
extern void __expand_lib_wildcards(void);
extern void __process_cdir(void);
extern int32 __rd_moddef(struct symtab_t *, int32);
extern int32 __vskipto2_modend(int32, int32);
extern char *__cfg_lineloc(char *s, char *, int32);
extern char *__schop(char *, char *);
extern void __sym_addprims(void);
extern int32 __chk_paramexpr(struct expr_t *, int32);
extern int32 __isleaf(struct expr_t *);
extern int32 __is_const_expr(struct expr_t *);
extern void __lhsbsel(word32 *, int32, word32);
extern void __to_dhboval(int32, int32);
extern void __getwir_range(struct net_t *, int32 *, int32 *);

extern void __cv_msg(char *s, ...);
extern void __finform(int32, char *, ...);
extern void __pv_ferr(int32, char *, ...);
extern void __pv_fwarn(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __dbg_msg(char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __fterr(int32, char *, ...);
extern void __misc_terr(char *, int32);
extern void __misc_fterr(char *, int32);
extern void __pv_err(int32, char *, ...);
extern void __pv_warn(int32, char *, ...);

extern const char __pv_ctab[];

/*
 * UDP PROCESSING ROUTINES
 */

/*
 * process a udp definition
 * added to end of list of udps with header __udphead
 * name of udp has already been read
 * notice there is a separate design wide list of udps
 *
 * primitive keyword read and reads endprimitive
 */
extern int32 __rd_udpdef(struct symtab_t *cfg_sytab)
{
 int32 retval, initlcnt, initsfnind;
 struct udp_t *udpp;
 struct tnode_t *tnp;
 struct sy_t *syp;
 char *cp;

 initlcnt = 0;
 initsfnind = 0;
 /* notice that Verilog keywords are reserved words */
 retval = TRUE;
 /* for now must be able to declare to continue syntax checking */
 if (__toktyp != ID)
  {
   __pv_ferr(1155, "udp name expected - %s read", __prt_kywrd_vtok());
skip_end:
   retval = __vskipto_modend(ENDPRIMITIVE);
   return(retval);
  }
 cp = __token;

 if (cfg_sytab != NULL)
  {
   tnp = __vtfind(__token, cfg_sytab);
   /* dups already checked for */
   /* DBG remove -- */
   if (!__sym_is_new) __misc_terr(__FILE__, __LINE__);
   /* --- */
   __add_sym(__token, tnp);
   (cfg_sytab->numsyms)++;
   syp = tnp->ndp;
  }
 else
  {
   tnp = __vtfind(cp, __modsyms);
   if (__sym_is_new)
    {
     __add_sym(__token, tnp);
     (__modsyms->numsyms)++;
     syp = tnp->ndp;
    }
   else
    {
     syp = tnp->ndp;
     /* if previously guessed as module, will just change */
     if (!__chk_redef_err(__token, syp, "udp", SYM_UDP)) goto skip_end;
     /* chk fail means never in module undef list */
     __remove_undef_mod(syp);
    }
  } 
 syp->sytyp = SYM_UDP;
 udpp = alloc_udp(syp);
 syp->el.eudpp = udpp;
 syp->sydecl = TRUE;
 /* need place where udp declared */
 syp->syfnam_ind = __cur_fnam_ind;
 syp->sylin_cnt = __lin_cnt;

 /* must also allocate the new symbol table */
 /* udps have no internal structure, sym table discarded when done */
 udpp->usymtab = __alloc_symtab(FALSE);
 __cur_udp = udpp;
 /* link symbol table back to module symbol */
 udpp->usymtab->sypofsyt = syp;

 /* do not need to build type until entire module read */
 /* any return here means skipped to endprimitive or next file level */
 if (!rd_udp_hdr(udpp)) return(FALSE);
 if (!rd_udp_decls()) return(FALSE);
 if (__toktyp == INITial)
  {
   initlcnt = __lin_cnt;
   initsfnind = __cur_fnam_ind;
   if (!rd_udp_init(udpp)) return(FALSE);
   __get_vtok();
   if (__toktyp != TABLE)
    {
     __pv_ferr(1156, "udp table section missing - %s read", __prt_vtok());
     goto skip_end;
    }
  }
 /* sets type to U_LEVEL if not combinatorial - edge type detected later */
 if (!chkcnt_uports(udpp)) retval = FALSE;
 if ((int32) udpp->numstates >= __ualtrepipnum) udpp->u_wide = TRUE;
 else udpp->u_wide = FALSE;

 /* this reads the endprimitive */
 if (!rd_udp_table(udpp)) return(FALSE);
 if (udpp->utyp == U_COMB && udpp->ival != NO_VAL)
  {
   __gferr(1157, initsfnind, initlcnt,
    "combinatorial udp %s cannot have initial value", syp->synam);
   udpp->ival = NO_VAL;
  }

 __get_vtok();
 if (__toktyp != ENDPRIMITIVE)
  {
   __pv_ferr(1158,
    "udp endprimitive keyword expected - %s read", __prt_vtok());
   goto skip_end;
  }
 if (!retval) return(TRUE);

 /* catch common extra ; error here */
 __get_vtok();
 if (__toktyp == SEMI)
  __pv_ferr(1152, "semicolon following endprimitive illegal"); 
 else __unget_vtok();

 extra_chk_edgeudp(udpp);

 /* notice if error before here not added to list */ 
 if (__udp_last == NULL) __udphead = udpp; else __udp_last->udpnxt = udpp;
 __udp_last = udpp;
 if (__debug_flg) __dmp_udp(stdout, udpp);
 return(TRUE);
}

/*
 * allocate a udp
 */
static struct udp_t *alloc_udp(struct sy_t *syp)
{
 struct udp_t *udpp;

 udpp = (struct udp_t *) __my_malloc(sizeof(struct udp_t));
 udpp->usym = syp;
 udpp->usymtab = NULL;
 udpp->upins = NULL;
 udpp->utyp = U_COMB;
 udpp->numins = 0;
 udpp->numstates = 0;
 udpp->u_used = FALSE;
 udpp->u_wide = FALSE;
 /* initial value - assume none that becomes 1'bx for level */
 udpp->ival = NO_VAL;
 udpp->utlines = NULL;
 udpp->udpnxt = NULL;
 udpp->utab = NULL;
 udpp->u_idnum = 0;
 return(udpp);
}

/*
 * read the udp header
 * only simple variable names allowed in this header
 * reads ending ;
 * handles skipping - 
 */
static int32 rd_udp_hdr(struct udp_t *udpp)
{
 struct mod_pin_t *upp, *last_upp;
 struct sy_t *syp;

 /* empty I/O list illegal */
 __get_vtok();
 if (__toktyp == SEMI)
  {
   __pv_ferr(1162, "required udp header list of ports missing");
   return(TRUE);
  }

 if (__toktyp != LPAR)
  {
   __pv_ferr(1164,
    "udp header list of ports initial left parenthesis expected - %s read",
    __prt_vtok());
   if (__udp_vskipto2_any(RPAR, SEMI)) 
    {
     if (__toktyp == RPAR) __get_vtok();
     /* if not semi, assume semi left out - if bad, next rout. will catch */
     if (__toktyp != SEMI) __unget_vtok();
     return(TRUE);
    }
ret_end:
   if (__syncto_class == SYNC_FLEVEL) return(FALSE);
   else return(TRUE);
  }
 __get_vtok();
 if (__toktyp == RPAR)
  {
   __pv_ferr(1165, "empty udp header list of ports () form illegal");
do_end:
   __get_vtok();
   if (__toktyp == SEMI) return(TRUE);
   __pv_ferr(980,
    "module header list of ports end semicolon expected - %s read",
    __prt_vtok());
   __unget_vtok();
   return(TRUE);
  }
 for (last_upp = NULL;;)
  {
   /* this declares the symbols in the header */
   if (__toktyp != ID)
    {
     __pv_ferr(1166, "udp port variable name expected - %s read",
      __prt_kywrd_vtok());
do_resync:
     if (__udp_vskipto3_any(COMMA, SEMI, RPAR)) 
      {
       /* port effectively not seen - error emitted already */
       if (__toktyp == COMMA) goto nxt_port;
       if (__toktyp == RPAR) goto do_end;
       return(TRUE);
      }
     goto ret_end;
    }
   syp = __decl_sym(__token, __cur_udp->usymtab);
   /* must fill in connection to port still */
   if (__sym_is_new) syp->sytyp = SYM_N;
   else
    {
     __pv_ferr(1167,
      "udp port %s repeated in header list of ports", syp->synam);
     goto nxt_port;
    }
   upp = __alloc_modpin();
   upp->mptyp = IO_UNKN;
   upp->mpsnam = syp->synam;
   upp->mpref = NULL;
   syp->el.empp = upp;

   if (last_upp == NULL) udpp->upins = upp; else last_upp->mpnxt = upp;
   last_upp = upp;

nxt_port:
   __get_vtok();
   if (__toktyp == RPAR)
    {
     __get_vtok();
     if (__toktyp == SEMI) break;
     __pv_ferr(1168,
      "udp header list of ports ending semicolon expected - %s read",
      __prt_vtok());
     goto do_end;
    }
   if (__toktyp != COMMA)
    {
     __pv_ferr(1169,
      "udp header comma or semicolon separator expected - %s read",
      __prt_vtok());
     goto do_resync;
    }
   __get_vtok();
  }
 return(TRUE);
}

/*
 * read the udp declarations
 * must read first port type and reads following initial or table
 * eliminates illegal vector ports by not parsing
 */
static int32 rd_udp_decls(void)
{
 struct mod_pin_t *mpp;
 struct sy_t *syp;
 int32 outdecl_seen, regdecl_seen;

 regdecl_seen = outdecl_seen = FALSE;
 for (;;)
  {
again:
   __get_vtok();
   if (__toktyp == INITial || __toktyp == TABLE) break;
   switch (__toktyp) {
    case INPUT:
     for (;;)
      {
       __get_vtok();
       if (__toktyp != ID)
        {
         __pv_ferr(1170, "udp input port name expected - %s read",
          __prt_kywrd_vtok());
sync_in:
         if (__udp_vskipto2_any(COMMA, SEMI)) 
          {
           /* port effectively not seen - error emitted already */
           if (__toktyp == COMMA) continue;
           goto again;
          }
         if (__syncto_class == SYNC_FLEVEL) return(FALSE);
         else goto again;
        }
       if ((syp = __get_sym(__token, __cur_udp->usymtab)) == NULL)
        {
not_in_port:
          __pv_ferr(1173,
           "udp input declaration of \"%s\" - non header input port", __token);
         goto nxt_port;
        }
       if (syp->sytyp != SYM_N)
        {
bad_sytab:
         /* udp symbol table inconsistent */
         __misc_fterr(__FILE__, __LINE__);
        }
       mpp = syp->el.empp;
       if (syp->sydecl || mpp->mptyp != IO_UNKN) goto not_in_port;
       mpp->mptyp = IO_IN;
       syp->sydecl = TRUE;

nxt_port:
       __get_vtok();
       if (__toktyp == SEMI) break;
       if (__toktyp == COMMA) continue;
       __pv_ferr(1174,
        "udp port declaration comma or semicolon separator expected - %s read",
        __prt_vtok());
       goto sync_in;
      }
     break;
    case OUTPUT:
     if (outdecl_seen)
      {
       __pv_ferr(1178, "only one udp output port declaration permitted");
       __get_vtok();
       goto end_out_port;
      }
     outdecl_seen = TRUE;

      __get_vtok();
     if (__toktyp != ID)
      {
       __pv_ferr(1179, "udp output port name expected - %s read",
        __prt_kywrd_vtok());
sync_out:
       if (__udp_vskipto_any(SEMI)) return(TRUE); 
       if (__syncto_class == SYNC_FLEVEL) return(FALSE);
       else goto again;
      }
     if ((syp = __get_sym(__token, __cur_udp->usymtab)) == NULL)
      {
not_out_port:
       __pv_ferr(1180,
        "udp output port declaration of \"%s\" that is not in header port list",
        __token);
       goto end_out_port;
      }
     if (syp->sytyp != SYM_N) goto bad_sytab;
     mpp = syp->el.empp;
     /* NON_IO means already declared as reg so nothing to do */
     if (mpp->mptyp != NON_IO)
      {
       if (syp->sydecl || mpp->mptyp != IO_UNKN) goto not_out_port;
       mpp->mptyp = IO_OUT;
       syp->sydecl = TRUE;
      }
end_out_port:
     __get_vtok();
     if (__toktyp != SEMI)
      {
       __pv_ferr(1181,
        "udp output declaration not followed by semicolon - %s read",
        __prt_vtok());
       goto sync_out;
      }
     break;
    case REG:
     /* SJM 07-31-10 - for SV, udp still uses reg not logic */
     if (regdecl_seen)
      {
       __pv_ferr(1182, "only one udp reg declaration permitted");
       __get_vtok();
       goto end_reg;
      }
     regdecl_seen = TRUE;
     __get_vtok();
     if (__toktyp != ID)
      {
       __pv_ferr(1183,
        "udp reg declaration output port name expected - %s read",
        __prt_kywrd_vtok());
sync_reg:
       if (__udp_vskipto_any(SEMI)) return(TRUE); 
       if (__syncto_class == SYNC_FLEVEL) return(FALSE);
       else goto again;
      }
     if ((syp = __get_sym(__token, __cur_udp->usymtab)) == NULL)
      {
not_reg_port:
       __pv_ferr(1184,
        "udp reg declaration of \"%s\" that is not in header port list",
        __token);
       goto end_reg;
      }
     if (syp->sytyp != SYM_N) goto bad_sytab;
     mpp = syp->el.empp;
     if (mpp->mptyp == IO_OUT) mpp->mptyp = NON_IO;
     else
      {
       /* if not output must be undeclared */
       if (syp->sydecl || mpp->mptyp != IO_UNKN) goto not_reg_port;
       mpp->mptyp = NON_IO;
      }
end_reg:
     __get_vtok();
     if (__toktyp != SEMI)
      {
       __pv_ferr(1187,
        "udp output reg declaration ending semicolon expected - %s read",
        __prt_vtok());
       goto sync_reg;
      }
     break;
    default:
     __pv_ferr(1188,
      "udp declaration I/O declaration keyword expected - %s read",
      __prt_vtok());
    return(FALSE);
   }
  }
 return(TRUE);
}

/*
 * read the one optional initial statement for the one udp output
 * know initial read - format is intial [output term] = [1 bit const]
 * complicated because no mechanism for conversion from 32 1 bit vals
 */
static int32 rd_udp_init(struct udp_t *udpp)
{
 int32 blen;

 __get_vtok();
 if (__toktyp != ID) goto bad_init;
 __get_vtok();
 if (__toktyp != EQ) goto bad_init;
 __get_vtok();
 if (__toktyp != NUMBER) goto bad_init;
 __get_vtok();
 if (__toktyp != SEMI) goto bad_init;
 if (__itoklen > WBITS)
  {
   blen = __itoklen - WBITS;
   if (!vval_is0_(&(__acwrk[1]), blen)) goto bad_val; 
   if (!vval_is0_(&(__bcwrk[1]), blen)) goto bad_val; 
  }
 /* this must be a 1 bit value but wider with all zero's ok */
 if (__acwrk[0] == 0L && __bcwrk[0] == 0L) udpp->ival = 0;
 else if (__acwrk[0] == 1L && __bcwrk[0] == 0L)
  udpp->ival = 1;
 else if (__acwrk[0] == 0L && __bcwrk[0] == 1L)
  {
   __pv_fwarn(576, "udp initial value 1'bz illegal - changed to 1'bx");
   udpp->ival = 3;
  }
 else if (__acwrk[0] == 1L && __bcwrk[0] == 1L) udpp->ival = 3;
 else
  {
bad_val:
   __pv_ferr(1191, "udp initial value must be one of: 0, 1, 1'bx - %s read",
    __prt_vtok());
   udpp->ival = NO_VAL;
  }
 return(TRUE);

bad_init:
 __pv_ferr(1192, "udp initial statement syntax error");
 if (__udp_vskipto_any(SEMI)) return(TRUE);
 if (__syncto_class == SYNC_FLEVEL) return(FALSE);
 return(TRUE);
}

/*
 * check and count number of ports and set to default sequential if needed
 * number of ports in number of inputs (+ 1 if level or edge)
 * udp type number udp inputs and type set here
 * error if header port not declared
 * return FALSE on error
 */
static int32 chkcnt_uports(struct udp_t *udpp)
{
 int32 retval, unumins, unumstates;
 struct mod_pin_t *mpp;

 mpp = udpp->upins;
 retval = TRUE;
 if (mpp->mptyp == IO_IN)
  {
   __gferr(1193, udpp->usym->syfnam_ind, udpp->usym->sylin_cnt,
    "first udp header port %s not the output", mpp->mpsnam);
   retval = FALSE;
  }
 unumins = unumstates = 0;
 if (mpp->mptyp == NON_IO) { udpp->utyp = U_LEVEL; unumstates++; }

 mpp = mpp->mpnxt;
 for (; mpp != NULL; mpp = mpp->mpnxt)
  {
   if (mpp->mptyp != IO_IN)
    {
     __gferr(1194, udpp->usym->syfnam_ind, udpp->usym->sylin_cnt,
      "after first udp port %s must be an input", mpp->mpsnam);
     retval = FALSE;
    }
   unumins++;
  }
 udpp->numins = unumins;
 udpp->numstates = unumins + unumstates;
 if (udpp->numins > MAXUPRTS)
  {
   __gferr(1195, udpp->usym->syfnam_ind, udpp->usym->sylin_cnt,
    "udp definition has %d ports - maximum allowed is %d",
    udpp->numins, MAXUPRTS);
   retval = FALSE;
  }
 return(retval);
}

/*
 * read the udp table
 * know table keyword read and reads endtable
 * when done udp lines are array of chars of length numins + 1 (for out)
 * numins includes state for non combinatorial
 *
 * if edge, 1 allowed edge, char in line is 2nd plus uledinum index of edge
 * and ultabsel is 1st (maybe wildcard) - need to convert back to r/f abbrev.
 */
static int32 rd_udp_table(struct udp_t *udpp)
{
 int32 ulcnt, has_wcard, ulfnam_ind;
 struct utline_t *utlp, *last_utlp;
 char uline[RECLEN], coduline[RECLEN], s1[RECLEN];

 __letendnum_state = TRUE;
 /* initialized for malformed ; only line - error caught later */
 ulfnam_ind = __cur_fnam_ind;
 ulcnt = __lin_cnt;

 for (last_utlp = NULL;;)
  {
   __get_vtok();
   if (__toktyp == ENDTABLE) break;
   strcpy(uline, "");
   for (;;)
    {
     if (__toktyp == SEMI) goto end_line;

     /* need beginning of udp entry line no. */
     ulfnam_ind = __cur_fnam_ind;
     ulcnt = __lin_cnt;
     switch (__toktyp) {
      case LPAR: strcat(uline, "("); break;
      case RPAR: strcat(uline, ")"); break;
      case QUEST: strcat(uline, "?"); break;
      case MINUS: strcat(uline, "-"); break;
      case TIMES: strcat(uline, "*"); break;
      case COLON: strcat(uline, ":"); break;
      /* this requires that even non sized numbers stored in token */
      /* works because ' not legal in udp table line */
      case ID: strcat(uline, __token); break;
      /* SJM 03/20/00 - must assemble from num token for numbers */
      case NUMBER: strcat(uline, __numtoken); break;
      default:
       __pv_ferr(1198, "invalid udp table line symbol %s", __prt_vtok());
       if (__udp_vskipto_any(SEMI)) continue;
       if (__toktyp == ENDTABLE) goto done;
       if (__syncto_class == SYNC_FLEVEL) goto bad_end;
       __vskipto_modend(ENDPRIMITIVE);
bad_end:
       __letendnum_state = FALSE;
       return(FALSE);
     }
     __get_vtok();
    }
end_line:
   /* at this point line collected and contains only 1 char values and punct */
   /* utyp only U_COMB if does not have reg declaration */
   if (udpp->utyp == U_COMB)
    {
     __cur_utabsel = NO_VAL;
     __cur_ueipnum = NO_VAL;
     str_tolower(coduline, uline);
     if (!chk_comb_udpline(coduline, udpp, &has_wcard)) goto bad_end;
    }
   else
    {
     str_tolower(s1, uline);
     /* edge temporarily converted to 0x80 form */
     if (!cvrt_udpedges(coduline, s1)) return(FALSE);
     /* edge converted to 1st char __cur_utabsel plus 2nd char here in uline */
     __cur_utabsel = NO_VAL;
     if (!chk_sequdpline(coduline, udpp, &has_wcard)) continue;
    }
   utlp = (struct utline_t *) __my_malloc(sizeof(struct utline_t));
   utlp->tline = __pv_stralloc(coduline);
   utlp->ullen = (word32) strlen(coduline);
   utlp->ulhas_wcard = (has_wcard) ? TRUE : FALSE;
   utlp->uledinum = __cur_ueipnum;
   utlp->utabsel = __cur_utabsel;
   utlp->utlfnam_ind = ulfnam_ind;
   utlp->utlin_cnt = ulcnt;
   utlp->utlnxt = NULL;
   if (last_utlp == NULL) udpp->utlines = utlp; else last_utlp->utlnxt = utlp;
   last_utlp = utlp;
  }
done:
 __letendnum_state = FALSE;
 return(TRUE);
}

static void str_tolower(char *to, char *from)
{
 while (*from)
  {
   if (isupper(*from)) *to++ = (char) tolower(*from); else *to++ = *from;
   from++;
  }
 *to = '\0';
}

/*
 * convert (..) form edges to one coded char - real edge processing
 * in check seqential udp line routine
 * edge has high bit on and then bits 5-3 is e1 and 2-0 is e2
 *
 * know all legal upper case edges converted to lower case before called
 * first step in udp table line checking - edge abbreviation not seen here
 */
static int32 cvrt_udpedges(char *culine, char *uline)
{
 int32 ie1, ie2, no_err;
 char *culp, *ulp, *chp, ech1, ech2;
 char s1[RECLEN];

 no_err = FALSE;
 for (no_err = TRUE, ulp = uline, culp = culine;;)
  {
   switch (*ulp) {
    case '\0': *culp = '\0'; goto done;
    case '(':
     ech1 = *(++ulp);
     if ((ie1 = to_udp_levsym(ech1)) == -1)
      {
       __pv_ferr(1202,
        "udp table line edge first symbol '%c' not a level symbol", ech1);
edge_err:
       no_err = FALSE;
       /* making error into (? ?) edge */
       *culp++ = (char) (0x80 + (UV_Q << 3) + UV_Q);
       if ((chp = strchr(ulp, ')')) == NULL) { *culp = '\0'; return(no_err); }
       ulp = ++chp;
       continue;
      }
     ech2 = *(++ulp);
     if ((ie2 = to_udp_levsym(ech2)) == -1)
      {
       __pv_ferr(1203,
        "udp table line edge second symbol '%c' not a level symbol", ech2);
       goto edge_err;
      }
     if (*(++ulp) != ')')
      {
       __pv_ferr(1204,
        "udp table line edge symbol closing ')' expected - %c read", *ulp);
       goto edge_err;
      }
     /* edge has high bit on and bits 5-3 is e1 and 2-0 is e2 */
     *culp++ = (char) (0x80 | (ie1 << 3) | ie2);
     ulp++;
     break;
    default:
     *culp++ = *ulp++;
    }
  }
done:
 if (__debug_flg)
  __dbg_msg("&&& converted from %s to %s\n", uline, to_codedge_line(s1,
   culine));
 return(no_err);
}

/*
 * return value of level symbol (-1 if not level symbol)
 */
static int32 to_udp_levsym(char ch)
{
 switch (ch) {
  case '0': return(UV_0);
  case '1': return(UV_1);
  case 'x': return(UV_X);
  case '?': return(UV_Q);
  case 'b': return(UV_B);
 }
 return(-1);
}

/*
 * check coded combinatorial udp uline
 */
static int32 chk_comb_udpline(char *uline, struct udp_t *udpp,
 int32 *has_wcard)
{
 int32 ins;
 char *chp;
 char ch;

 *has_wcard = FALSE;
 /* separate off ending :[output] */
 if ((chp = strrchr(uline, ':')) == NULL)
  {
   __pv_ferr(1205,
    "combinatorial udp line expected ':' output separator missing");
   return(FALSE);
  }
 *chp++ = '\0';
 ch = *chp++;
 if (ch == '-')
  {
   __pv_ferr(1206,
    "combinatorial udp line '-' output symbol illegal - has no state");
   return(FALSE);
  }
 if (ch != '0' && ch != '1' && ch != 'x')
  {
   __pv_ferr(1207,
    "combinatorial udp line output symbol (%x) '%c' illegal", ch, ch);
   return(FALSE);
  }
 if (*chp != '\0')
  {
   __pv_ferr(1208,
    "combinatorial udp line has second output symbol '%c' - only one allowed",
    *chp);
   return(FALSE);
  }
 /* check inputs - up to rightmost : */
 for (chp = uline, ins = 0; *chp != '\0'; chp++, ins++)
  {
   switch (*chp) {
    case '(': case 'r': case 'f': case 'p': case 'n': case '*':
     __pv_ferr(1209, "edge symbol %c illegal in combinatorial udp line", *chp); 
     return(FALSE);
   }
   if (to_udp_levsym(*chp) == -1)
    {
     __pv_ferr(1213,
      "combinatorial udp line input symbol '%c' (position %d) not a level symbol",
      *chp, ins + 1);
     return(FALSE);
    }
   if (ins >= 254)
    {
     __pv_ferr(1214,
      "udp has so many inputs (%d) - it cannot be checked", 254); 
     return(FALSE);
    }
   if (*chp == 'b' || *chp == '?') *has_wcard = TRUE;
  }
 if (ins != udpp->numins)
  {
   __pv_ferr(1215,
    "combinatorial udp line wrong number of input symbols (%d) - should be %d",
    ins, udpp->numins);
   return(FALSE);
  }
 /* finally add output as last symbol */
 *chp++ = ch;
 *chp = '\0';
 return(TRUE);
}

/*
 * check coded sequential upd uline
 * know all (..) edge convert to 1 char by here (0x80 on)
 * if no edge __cur_ueipnum has value NO_VAL
 * old 0x80 bit on form edge converted to 1st as __cur_utabsel, 2nd as char 
 * unless edge wildcard (i.e. r,f,n, etc.) in which case has edge wildcard
 */
static int32 chk_sequdpline(char *uline, struct udp_t *udpp,
 int32 *has_wcard)
{
 int32 ins, t1;
 char *chp;
 char ch1, ch2;

 *has_wcard = FALSE;
 /* separate off : before previous state :[prev. state]:[output] */
 if ((chp = strchr(uline, ':')) == NULL)
  {
   __pv_ferr(1216,
    "sequential udp line expected colon before old state symbol missing");
   return(FALSE);
  }
 /* end uline */
 *chp = '\0';
 chp++;
 /* ch1 is state symbol and -1 means not 1 of legasl 0,1,x,?,b */
 ch1 = *chp++;
 if (to_udp_levsym(ch1) == -1)
  {
   __pv_ferr(1218,
    "sequential udp line state level symbol '%c' illegal", ch1);
   return(FALSE);
  }
 /* state can be wildcard but not edge */
 if (ch1 == 'b' || ch1 == '?') *has_wcard = TRUE;
 if (*chp++ != ':')
  {
   __pv_ferr(1219,
    "sequential udp line expected colon before output symbol missing");
   return(FALSE);
  }
 /* ch2 is output symbol */
 ch2 = *chp++;
 if (ch2 != '0' && ch2 != '1' && ch2 != 'x' && ch2 != '-')
  {
   __pv_ferr(1221, "sequential udp line output symbol '%c' illegal", ch2);
   return(FALSE);
  }
 if (*chp != '\0')
  {
   __pv_ferr(1222,
    "sequential udp line has extra output symbol '%c' - only one allowed",
    *chp);
   return(FALSE);
  }
 /* previous state and output done, finally check inputs */
 __cur_utabsel = NO_VAL;
 __cur_ueipnum = NO_VAL;
 for (chp = uline, ins = 0; *chp != '\0'; chp++, ins++)
  {
   /* know if edge, already checked - wild card only for level sensitive */
   if (is_edgesym(*chp))
    {
     if (__cur_ueipnum != NO_VAL)
      {
       __pv_ferr(1223,
       "sequential udp line has more than one edge symbol (second input %d)",
        ins + 1);
       return(FALSE);
      }
     __cur_ueipnum = ins;
     if ((*chp & 0x80) != 0)
      {
       /* know if (..) edge then both letters are edge symbols */
       /* edge has high bit on and then bits 5-3 is ie1 and 2-0 is ie2 */
       t1 = *chp & 0x7f;
       *chp = to_edgech(t1 & 0x7);
       __cur_utabsel = to_edgech((t1 >> 3) & 0x7);
       if ((__cur_utabsel == '0' && *chp == '0')
        || (__cur_utabsel == '1' && *chp == '1')
        || (__cur_utabsel == 'x' && *chp == 'x'))
        {
         __pv_ferr(1224,
          "sequential udp line edge (%c%c) (input %d) illegal - no transition",
          __cur_utabsel, *chp, __cur_ueipnum + 1);
         return(FALSE);
        }
      }
     else if (*chp == 'r') { __cur_utabsel = '0'; *chp = '1'; }
     else if (*chp == 'f') { __cur_utabsel = '1'; *chp = '0'; }
     /* if special edge abbrev. but not r or f make both edges have abbrev. */
     else __cur_utabsel = *chp;
     continue;
    }
   if (to_udp_levsym(*chp) == -1)
    {
     __pv_ferr(1225,
      "sequential udp line symbol '%c' (input %d) not edge or level", *chp,
      ins + 1);
     return(FALSE);
    }
   if (*chp == 'b' || *chp == '?') *has_wcard = TRUE;
  }
 if (ins != udpp->numstates - 1 || ins != udpp->numins)
  {
   __pv_ferr(1226,
    "sequential udp line wrong number of input symbols (%d) - should be %d",
    ins, udpp->numins - 1);
   return(FALSE);
  }
 /* finally add previous state input and next state output as last 2 */
 *chp++ = ch1;
 *chp++ = ch2;
 *chp = '\0';
 if (__cur_ueipnum != NO_VAL) udpp->utyp = U_EDGE;
 return(TRUE);
}

/*
 * convert edge 4 bit encoding to normal level edge symbol
 */
static char to_edgech(int32 encodee)
{
 switch ((byte) encodee) {
  case UV_0: return('0');
  case UV_1: return('1');
  case UV_X: break;
  case UV_Q: return('?');
  case UV_B: return('b');
  default: __case_terr(__FILE__, __LINE__);
 }
 return('x');
}

/*
 * return T if symbol is an edge symbol (code 0x80 or edge letter)
 */
static int32 is_edgesym(char ch)
{
 if ((ch & 0x80) != 0) return(TRUE);
 switch (ch) {
  case 'r': case 'f': case 'p': case 'n': case '*': return(TRUE);
 }
 return(FALSE);
}

/*
 * convert a coded edge line to a string 
 * in form during input before converted to line separate edge char and 
 * edge destination in line char position 
 */
static char *to_codedge_line(char *s, char *culine)
{
 int32 uch;
 char *cpi, *cpo;

 for (cpi = culine, cpo = s; *cpi != '\0'; cpi++)
  {
   if ((*cpi & 0x80) != 0)
    {
     *cpo++ = '(';
     /* notice 5-3 are e1 and 2-0 are e2 */
     uch = (int32) *cpi;
     *cpo++ = to_edgech((uch >> 3) & 0x7);
     *cpo++ = to_edgech(uch & 0x7);
     *cpo++ = ')'; 
    }
   else *cpo++ = *cpi;
  }
 *cpo = '\0';
 return(s);
}

/*
 * perform some consistency checks on edge udps
 * - input column probably needs edge in some row
 * - output column probably needs - somewhere
 */
static void extra_chk_edgeudp(struct udp_t *udpp)
{
 int32 i, out_hasbar;
 struct utline_t *utlp;

 for (i = 0; i < (int32) udpp->numins; i++)
  {
   for (utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt)
    {
     if (utlp->uledinum == i) goto next;
    }
   __gfinform(421, udpp->usym->syfnam_ind, udpp->usym->sylin_cnt,
    "sequential udp \"%s\" column for input %s lacks any edge(s)",
     udpp->usym->synam, to_udp_prtnam(udpp, i + 1));
next:;
  }
 /* inputs are 0 to num ins - 1 then previous state, then next state */
 i = udpp->numins + 1;
 out_hasbar = FALSE;
 for (utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt)
  {
   if (utlp->tline[i] == '-') out_hasbar = TRUE;
  }
 if (!out_hasbar)
  {
   __gfinform(422, udpp->usym->syfnam_ind, udpp->usym->sylin_cnt,
    "sequential udp %s output column lacks any no change (-) symbols",
    udpp->usym->synam);
  }
}

/*
 * find input position %d (first is output)
 * know position number legal and starts at 1
 */
static char *to_udp_prtnam(struct udp_t *udpp, int32 inum)
{
 int32 nins;
 struct mod_pin_t *mpp;

 nins = 1;
 mpp = udpp->upins->mpnxt;
 for (; mpp != NULL; mpp = mpp->mpnxt, nins++)
  {
   if (nins == inum) goto done;
  }
 __misc_terr(__FILE__, __LINE__);
done:
 return(mpp->mpsnam);
}

/*
 * UDP DUMP ROUTINES - FOR DEBUGGING
 */

/*
 * dump a udp for debugging
 * f cannot be nil to put in string
 */
extern void __dmp_udp(FILE *f, struct udp_t *udpp)
{
 int32 first_time;
 struct mod_pin_t *mpp;
 char s1[RECLEN], s2[RECLEN];

 if (f == NULL) __arg_terr(__FILE__, __LINE__);
 __cv_msg("\n");
 __cur_sofs = 0;
 __outlinpos = 0;
 __pv_stlevel = 0;

 __wrap_puts("primitive ", f);
 __wrap_puts(udpp->usym->synam, f);
 first_time = TRUE;
 /* notice udp module pin lists continue to use next pointer */
 for (mpp = udpp->upins; mpp != NULL; mpp = mpp->mpnxt)
  {
   if (first_time) { __wrap_putc('(', f); first_time = FALSE; }
   else __wrap_puts(", ", f);
   /* know udp pins must be named */
   __wrap_puts(mpp->mpsnam, f);
  }
 __nl_wrap_puts(");", f);

 /* notice here mpsnam must exist or earlier syntax error */
 __pv_stlevel = 1;
 mpp = udpp->upins;
 __wrap_puts("output ", f);
 __wrap_puts(mpp->mpsnam, f);
 __wrap_putc(';', f);
 if (udpp->utyp != U_COMB)
  {
   __wrap_puts("  reg ", f);
   __wrap_puts(mpp->mpsnam, f);
   __wrap_putc(';', f); 
  }
 __nl_wrap_puts("", f);
 
 __wrap_puts("input ", f);
 first_time = TRUE;
 for (mpp = mpp->mpnxt; mpp != NULL; mpp = mpp->mpnxt)
  {
   if (first_time) first_time = FALSE; else __wrap_puts(", ", f);
   __wrap_puts(mpp->mpsnam, f);
  }
 __nl_wrap_puts(";", f);

 if (udpp->ival != NO_VAL)
  {
   __wrap_puts("initial ", f);
   __wrap_puts(udpp->upins->mpsnam, f);
   sprintf(s1, " = 1'b%s", __to_uvvnam(s2, (word32) udpp->ival));
   __wrap_puts(s1, f);
   __nl_wrap_puts(";", f);
  }
 __nl_wrap_puts("", f);
 __nl_wrap_puts("table", f);
 dmp_udp_lines(f, udpp);
 __nl_wrap_puts("endtable", f);
 __pv_stlevel--;
 __nl_wrap_puts("endprimitive", f);
}

/*
 * dump udp lines
 * need to also dump initial value
 */
static void dmp_udp_lines(FILE *f, struct udp_t *udpp)
{
 int32 i, numins, sav_stlevel;
 struct utline_t *utlp;
 char *chp, s1[RECLEN];

 sav_stlevel = __pv_stlevel;
 __pv_stlevel = 4;
 __outlinpos = 0;
 numins = udpp->numins;
 for (utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt)
  {
   for (chp = utlp->tline, i = 0; i < numins; i++, chp++)
    {    
     /* the one possible edge */
     if (utlp->uledinum == i)
      {
       /* special wild card types edges are kept as original char */
       /* 01 and 10 are converted from rise-fall - convert back */
       if (utlp->utabsel == '0' && *chp == '1') __wrap_puts("    r", f);
       else if (utlp->utabsel == '1' && *chp == '0') __wrap_puts("    f", f);
       else if (utlp->utabsel == '*') __wrap_puts("    *", f);
       else if (utlp->utabsel == 'p') __wrap_puts("    p", f);
       else if (utlp->utabsel == 'n') __wrap_puts("    n", f);
       else
        {
         sprintf(s1, " (%c%c)", (char) utlp->utabsel, *chp);
         __wrap_puts(s1, f);
        }
      }
     /* various wild cards and states left as input char */
     else { sprintf(s1, "%5c", *chp); __wrap_puts(s1, f); }
    }
   if (udpp->utyp != U_COMB)
    { sprintf(s1, " : %c ", *chp); __wrap_puts(s1, f); chp++; }
   sprintf(s1, " : %c ;", *chp);
   __nl_wrap_puts(s1, f);
  }
 __pv_stlevel = sav_stlevel;
}

/*
 * READ SPECIFY SECTION ROUTINES
 */

/*
 * read and build d.s for specify section items
 * expects specify to have been read and reads endspecify
 * current approach concatenates all specify sections in one mod.
 */
extern int32 __rd_spfy(struct mod_t *mdp)
{
 int32 tmpi, sav_decl_obj;
 word32 tchktyp;
 char s1[RECLEN];
 
 __path_num = __tchk_num = 1;
 sav_decl_obj = __cur_declobj;
 __cur_declobj = SPECIFY;
 /* all specify sections concatenated together */
 if (mdp->mspfy == NULL) mdp->mspfy = alloc_spfy();
 __cur_spfy = mdp->mspfy;
 /* at this point only module symbol tabl on scope stack since specify */
 /* is module item */
 if (__top_sti != 0) __misc_terr(__FILE__, __LINE__);
 /* place special symbol table for specparams on scope stack */
 __venviron[++__top_sti] = __cur_spfy->spfsyms;

 for (;;)
  {
   __get_vtok();
   switch (__toktyp)
    {
     case SPECPARAM: 
      if (!rd_specparamdecl())
       {
        /* notice unless T (found ;) will not sync to normal ( path */
specitem_resync:
        switch ((byte) __syncto_class) {
         case SYNC_FLEVEL: case SYNC_MODLEVEL: case SYNC_STMT:
          __top_sti--;
          return(FALSE);
         case SYNC_SPECITEM:
          break;
         /* if sync. to statement assume initial left out */
         default: __case_terr(__FILE__, __LINE__);
        }
       }
      continue;
     case IF: case LPAR: case IFNONE:
      if (!rd_delay_pth()) goto specitem_resync;
      break;
     case ENDSPECIFY: goto done;
     case ID:
      /* this must be timing check */
      if (*__token == '$')
       {
        if ((tmpi = __fr_tcnam(__token)) == -1)
         {
          __pv_ferr(1228,
           "system task %s illegal in specify section", __token);
          goto err_skip;
         }
        tchktyp = tmpi;
        __get_vtok();
        if (__toktyp != LPAR)
         {
          __pv_ferr(1231,
          "timing check %s argument list left parenthesis expected - %s read",
          __to_tcnam(s1, tchktyp) , __prt_vtok());
          goto err_skip;
         } 
        /* specify system timing check tasks */
        /* the routines fill cur tchk */
        switch ((byte) tchktyp) {
         case TCHK_SETUP: case TCHK_HOLD:
          if (!rd_setup_or_hold_tchk(tchktyp)) goto specitem_resync;
          break;
         case TCHK_SETUPHOLD:
          if (!rd_setuphold_tchk()) goto specitem_resync;
          break;
         case TCHK_WIDTH:
          if (!rd_width_tchk()) goto specitem_resync;
          break;
         case TCHK_PERIOD:
          if (!rd_period_tchk()) goto specitem_resync;
          break;
         case TCHK_SKEW: case TCHK_RECOVERY: case TCHK_REMOVAL:
          if (!rd_skew_recov_rem_tchk(tchktyp)) goto specitem_resync;
          break;
         case TCHK_RECREM:
          if (!rd_recrem_tchk()) goto specitem_resync;
          break;
         case TCHK_NOCHANGE:
          if (!rd_nochg_tchk()) goto specitem_resync;
          /* SJM 04-10-14 - nochange does nothing in simulator world */
          /* do not add to list here */
          goto no_add;
         case TCHK_FULLSKEW:
         case TCHK_TIMESKEW:
          /* SJM 11/21/03 - this and other new 2001 tchks not supported */
          /* for now just skip and later add support for this and others */
          __pv_fwarn(3124,"%s timing check not yet supported - ignored",
           __to_tcnam(__xs, tchktyp)); 
          goto err_skip;
         default: __case_terr(__FILE__, __LINE__);
        }
        /* add to timing check list */
        if (__end_tchks == NULL) __cur_spfy->tchks = __cur_tchk;
        else __end_tchks->tchknxt = __cur_tchk;
        __end_tchks = __cur_tchk;
no_add:
        break;
       }
      /* fall through to error since ID not specify item */
      /*FALLTHRU*/
     default:
      __pv_ferr(1229, "specify section item expected - %s read",
       __prt_vtok());
err_skip:
     if (!__spec_vskipto_any(SEMI)) goto specitem_resync;
     /* just fall through if seme to next */
    }
  }
done:
 __top_sti = 0;
 __cur_declobj = sav_decl_obj;
 /* notice freezing at module end for specparam symbol table too */
 return(TRUE);
}

/*
 * allocate a specify block - called when first specify block seen
 */
static struct spfy_t *alloc_spfy(void)
{
 struct spfy_t *spcp;

 spcp = (struct spfy_t *) __my_malloc(sizeof(struct spfy_t));
 /* notice this symbol table links to mod through this special specify */
 /* block but otherwise no symbol table links */
 spcp->spfsyms = __alloc_symtab(TRUE);
 spcp->spcpths = NULL; 
 spcp->tchks = NULL;
 spcp->msprms = NULL; 
 spcp->sprmnum = 0;
 __end_spcpths = NULL;
 __end_tchks = NULL;
 __end_msprms = NULL;
 return(spcp);
}

/*
 * read the specparam declaration statement 
 * form: specparam [name] = [constant?], ...
 * no  # and () around delay is optional in parameter decl.
 * reads parameter name through ending ;
 *
 * here width actual bit width - later converted to int32 or real
 * and then usually to 64 bit delay
 *
 * SJM 01-28-09 - can't eval optional spec param range expr or rhs value
 * until processing of const functions completed - now just save and
 * same assigns done just before net list fixup
 */
static int32 rd_specparamdecl(void)
{
 int32 good, prng_decl, pwid;
 struct net_t *np;
 struct expr_t *x1, *x2;
 char paramnam[IDLEN];

 pwid = 0;
 x1 = x2 = NULL;
 prng_decl = FALSE;
 __get_vtok();
 if (__toktyp == LSB)
  {
   /* SJM 02-11-09 - now only way for x1 not nil is rng present */
   /* also check to make sure ranges are non x/z 32 bit values */
   if (!__rd_opt_param_vec_rng(&x1, &x2, FALSE)) return(FALSE);
   prng_decl = TRUE;
  }

 for (;;)
  {
   if (__toktyp != ID)
    {
     __pv_ferr(1230, "specparam name expected - %s read", __prt_kywrd_vtok());
bad_end:
     /* part of delay expression may have been built */
     if (!__spec_vskipto2_any(COMMA, SEMI)) return(FALSE);
     if (__toktyp == COMMA) { __get_vtok(); continue; }
     return(TRUE);
    }
   strcpy(paramnam, __token);

   /* notice the initial value is required */
   __get_vtok();
   if (__toktyp != EQ)
    {
     __pv_ferr(1232,
      "specparam declaration equal expected - %s read", __prt_vtok());
     goto bad_end;
    }
   /* 06/22/00 - SJM - special path pulse form, for now ignore with warn */
   if (strncmp(paramnam, "PATHPULSE$", 10) == 0)
    {
     __pv_fwarn(3102,
      "%s special path pulse specparam ignored - use +show_canceled_e option instead",
      paramnam);
     /* 06/22/00 - SJM - FIXME - need to really parse this */ 
     if (!__spec_vskipto_any(SEMI)) 
      {
       __pv_ferr(3408,
        "PATHPULSE$ specparam %s right hand side value illegal format",
        paramnam);
       return(FALSE);
      }
     goto nxt_sparam;
    }

   /* know symbol table env. in specify specparam rhs specparam local */
   __get_vtok();
   __sav_spsytp = __venviron[0];
   __venviron[0] = __venviron[1];
   __top_sti = 0;
   good = __col_paramrhsexpr();
   __venviron[0] = __sav_spsytp;
   __top_sti = 1; 
   /* on error, does not add spec param */
   if (!good) goto bad_end;
   __bld_xtree(0);

   /* SJM 06/17/99 - illegal to assign string literal to specparam */
   /* SJM 02/04/00 - must allow since needed for models where PLI used */
   /* to read parameter value - and should be this is just wide reg */
   /* --- REMOVED --- 
   if (__root_ndp->is_string)
    {
     __pv_fwarn(659,
      "specparam %s right hand side string not a delay value - converted to 0 delay",
      paramnam);
     -* need to still add value of x to prevent further errors *-
     __free2_xtree(__root_ndp);
     __root_ndp->szu.xclen = WBITS;
     __set_numval(__root_ndp, 0L, 0L, WBITS);  
     -* notice x1, x2 range expressions always WBITS-1 to 0 for specparams *-  
    }
   --- */

   /* SJM 01-25-09 - due to const funcs can't eval parameter ranges to */
   /* numbers until all src read - so just leave spec param range expr */ 
   /* and eval before work space copy for gen and fixup nl */

   /* SJM 02-11-09 - always need range expr in nu.ct even if from number */
   /* if prng decl - set bit and calculate width later - for now assume WBITS */
   if (prng_decl) pwid = WBITS; 
   else 
    {
     /* SJM 02-12-09 - assume normal integer/WBITS size here - will fix late */
     x1 = __bld_rng_numxpr(WBITS - 1, 0, WBITS);
     x2 = __bld_rng_numxpr(0, 0, WBITS);
    }

   /* check and links on modules parameter list */
   /* when rhs expr. evaluated, if real will change */
   /* LOOKATME - problem with all params in list sharing range xprs? */ 
   np = __add_param(paramnam, x1, x2, FALSE, FALSE);
   /* set provisional fields */
   np->ntyp = N_REG;
   np->nwid = pwid; 
   np->nu.ct->prngdecl = prng_decl;
 
   /* using ncomp delay union to store original expresssion - set first */
   /* need this separate copy even after parameter value assigned */
   np->nu.ct->n_dels_u.d1x = __root_ndp;
   np->nu.ct->parm_srep = SR_PXPR;

   /* SJM 01-28-09 - can't eval spec param rhs until const funcs found */
   /* and prepared - done just nl fixup now */

   /* specparams can never be strings or IS forms */ 
   __mod_specparams++;

nxt_sparam:
   if (__toktyp == SEMI) break;
   if (__toktyp != COMMA)
    {
     __pv_ferr(1236,
      "specparam ; or , separator expected - %s read", __prt_vtok());
     if (!__spec_vskipto2_any(COMMA, SEMI)) return(FALSE); 
     if (__toktyp == SEMI) break;
    }
   __get_vtok();
  }
 return(TRUE);
}

/*
 * assign values to specparams - like defparams but can never be IS form
 *
 * 02/04/00 - SJM change to move toward v2k LRM and match XL better
 * type determined from RHS - range allowed and used for width
 *
 * SJM 10/06/03 - signed keyword illegal and specparams never signed
 * unless real
 */
extern void __assign_1specparam(struct net_t *np)
{
 int32 wlen;
 word32 *wp;
 struct expr_t *ndp;
 struct xstk_t *xsp;

 /* need dummy itree place on itree stack for eval */
 ndp = np->nu.ct->n_dels_u.d1x;
 xsp = __eval_xpr(ndp);

 /* case 1: range declaration - may need to convert value */
 if (np->nu.ct->prngdecl)
  {
   /* convert declared param type real rhs to int/reg */
   if (ndp->is_real)
    {
     __cnv_stk_fromreal_toreg32(xsp);
     np->nu.ct->pbase = BDEC;
     np->nu.ct->prngdecl = TRUE;
     np->nwid = xsp->xslen;
     np->ntyp = N_REG;
     np->n_signed = TRUE;
    }
   else
    {
     if (xsp->xslen != np->nwid) __sizchgxs(xsp, np->nwid);

     np->nu.ct->prngdecl = TRUE;
     np->nwid = xsp->xslen;
     np->ntyp = N_REG;
     if (np->nwid > 1) { np->n_isavec = TRUE; np->vec_scalared = TRUE; } 
     np->nu.ct->pbase = ndp->ibase;
    }

   wlen = wlen_(np->nwid);
   wp = (word32 *) __my_malloc(2*WRDBYTES*wlen); 
   memcpy(wp, xsp->ap, 2*WRDBYTES*wlen);
   __pop_xstk();
   np->prm_nva.wp = wp;
   np->srep = SR_PNUM;
   return;
  }

 /* SJM 10/06/03 - since specparams never signed, interpret as word32 */
 /* even if rhs signed with sign bit on */

 /* case 2: type determined from constant expr */
 /* spec params either reg or real - by here if range decl ndp fixed */
 if (ndp->is_real)
  {
   np->nwid = REALBITS;
   np->ntyp = N_REAL;
   np->n_signed = TRUE;
   np->n_isavec = TRUE;
   np->nu.ct->pbase = BDBLE;
   wp = (word32 *) __my_malloc(2*WRDBYTES); 
   memcpy(wp, xsp->ap, 2*WRDBYTES);
  }
 else
  {
   np->nwid = xsp->xslen;
   np->ntyp = N_REG;
   if (np->nwid > 1) { np->n_isavec = TRUE; np->vec_scalared = TRUE; } 
   if (ndp->is_string) np->nu.ct->pstring = TRUE;

   np->nu.ct->pbase = ndp->ibase;
   wlen = wlen_(np->nwid);
   wp = (word32 *) __my_malloc(2*WRDBYTES*wlen); 
   memcpy(wp, xsp->ap, 2*WRDBYTES*wlen);
  }
 __pop_xstk();
 /* build wire value - this is assign to wire so wire flags unchged */
 np->prm_nva.wp = wp;
 np->srep = SR_PNUM;
}

/*
 * DELAY PATH ROUTINES
 */

/*
 * read the ([path desc. list?] [=*]> [path desc. list?]) = [path val.]
 * know initial ( read and if conditional present in condx
 * notice no path if any error but may still return T
 *
 * here when collecting expressions both specparams and top module symbol
 * table accessible for wires but only local specparams for delay
 */
static int32 rd_delay_pth(void)
{
 int32 good;
 int32 pdtyp, pth_edge, pthpolar, datasrcpolar, is_ifnone;
 struct sy_t *pthsyp;
 struct exprlst_t *ilstx, *olstx;
 struct paramlst_t *pmphdr;
 struct expr_t *condx, *datsrcx, *lop, *last_dsx;
 struct spcpth_t *pthp;

 is_ifnone = FALSE;
 condx = datsrcx = NULL;
 /* needed since gcc sees as unset - do not think so */
 olstx = NULL;
 pdtyp = PTH_NONE;
 datasrcpolar = POLAR_NONE;
 pthpolar = POLAR_NONE;
 if (__toktyp == IFNONE)
  { 
   __get_vtok();
   if (__toktyp != LPAR)
    {
     __pv_ferr(1197,
      "sdpd ifnone token not followed by path beginning ( - %s read",
      __prt_vtok());
     /* here skipping to ) will skip path - no start tok - can not correct */
     if (!__spec_vskipto_any(SEMI)) return(FALSE);
     return(TRUE);
    }
   is_ifnone = TRUE;
   goto no_pthcond;
  }
 if (__toktyp == LPAR) goto no_pthcond;
 /* must be if token to get here, read optional condition expr. 1st */
 __get_vtok();
 if (__toktyp != LPAR)
  {
   __pv_ferr(1251,
    "sdpd conditional expression if token not followed by ( - %s read",
     __prt_vtok());
bad_sdp:
   if (!__spec_vskipto2_any(SEMI, RPAR)) return(FALSE);
   if (__toktyp == SEMI) return(TRUE);
   /* have ) make cond x NULL - this is not delay this is if actual expr */
   __set_numval(__exprtab[0], 1L, 1L, 1);
   __last_xtk = 0;
   goto bad_sdpx;
  }
 __get_vtok();
 if (!__col_parenexpr(-1, FALSE, FALSE)) goto bad_sdp;
bad_sdpx:
 __bld_xtree(0);
 condx = __root_ndp;
 if (__expr_has_glb(condx))
  {
   __pv_ferr(1022,
    "global hierarchical reference illegal in state dependent path condition %s",
    __msgexpr_tostr(__xs, condx));
  }
 __get_vtok();
 if (__toktyp != LPAR)
  {
   __pv_ferr(1252,
    "sdpd conditional expression not followed by path start ( - %s read",
    __prt_vtok());
   /* here skipping to ) will skip path */
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
   return(TRUE);
  }

no_pthcond:
 /* for edge sensitive path can have edge before input */
 /* but only pos and neg edges */
 __get_vtok();
 if (__toktyp == NEGEDGE || __toktyp == POSEDGE) 
  {
   pth_edge = (__toktyp == NEGEDGE) ? E_NEGEDGE : E_POSEDGE;
   __get_vtok();
  }
 else pth_edge = NOEDGE;

 /* this requires read 1st token of path */ 
 if ((ilstx = rd_pthtermlst()) == NULL)
  {
bad_pth:
   if (!__spec_vskipto3_any(SEMI, RPAR, EQ)) return(FALSE);
   if (__toktyp == RPAR) goto get_eq; 
   if (__toktyp == EQ) goto got_eq;
   return(TRUE);
  }
 /* this just attempts to catch some common errors */
 if (__toktyp == RPAR || __toktyp == TCHKEVAND)
  {
   __pv_ferr(1253,
    "input path description connector operator or semicolon expected - %s read",
    __prt_vtok());
   goto bad_pth;
  }
 /* path polarity is option stored for pli but not used */
 /* AIV 08/05/08 - these now parse as one token +: */
 /* may still need to parse +*> as seperate tokens */
 if (__toktyp == PARTSEL_NDX_PLUS || __toktyp == PARTSEL_NDX_MINUS
  || __toktyp == PLUS || __toktyp == MINUS)
  {
   pthpolar = ((__toktyp == PLUS || __toktyp == PARTSEL_NDX_PLUS) 
    ? POLAR_PLUS : POLAR_MINUS);
   __get_vtok();
  }
 else pthpolar = POLAR_NONE;

 /* path type required */
 if (__toktyp == FPTHCON) pdtyp = PTH_FULL; 
 else if (__toktyp == PPTHCON) pdtyp = PTH_PAR;
 else
  {
   __pv_ferr(1258,
    "either full => or parallel *> path operator expected - %s read",
    __prt_vtok());
   goto bad_pth;
  }
 /* if ( here then form is ([dst. term list] [polarity?]:[data src. expr.]) */
 __get_vtok();
 if (__toktyp == LPAR)
  { 
   /* this requires read 1st token of path */ 
   __get_vtok();
   if ((olstx = rd_pthtermlst()) == NULL) goto bad_end;
   /* data source polarity determines delay selection */
   /* AIV 08/05/08 - these now parse as one token +: */
   if (__toktyp == PARTSEL_NDX_PLUS || __toktyp == PARTSEL_NDX_MINUS)
    {
     datasrcpolar = (__toktyp == PARTSEL_NDX_PLUS) ? POLAR_PLUS : POLAR_MINUS;
     __get_vtok();
    }
   /* may still need to parse +*> as seperate tokens */
   else 
    {
     if (__toktyp == PLUS || __toktyp == MINUS)
      {
       datasrcpolar = (__toktyp == PLUS) ? POLAR_PLUS : POLAR_MINUS;
       __get_vtok();
      }
     else datasrcpolar = POLAR_NONE;
     if (__toktyp != COLON)  
      {
       __pv_ferr(1254,
        "data source path destination colon terminator expected - %s read",
        __prt_vtok());
      goto bad_pth;
     }
     __get_vtok();
    }
   /* comma separated list allowed here - width must match dest. width */
   if (!__col_parenexpr(-1, FALSE, FALSE)) goto bad_pth;
   __bld_xtree(0);
   /* common edge path trigger as 1 expression not list case */
   if (__toktyp != COMMA)
    { datsrcx = __root_ndp; __get_vtok(); goto chk_endrpar; }

   /* this is complicated data source expression list case */
   lop = __alloc_newxnd();
   lop->optyp = FCCOM;
   lop->ru.x = NULL;
   lop->lu.x = __root_ndp;
   datsrcx = lop;
   for (last_dsx = lop;;) 
    {
     /* if good this reads trailing delimiter */
     if (!__col_connexpr(-1)) goto bad_end;
     __bld_xtree(0);
     lop = __alloc_newxnd();
     lop->optyp = FCCOM;
     lop->ru.x = NULL;
     lop->lu.x = __root_ndp;
     last_dsx->ru.x = lop;
     if (__toktyp == RPAR) { __get_vtok(); break; }
     if (__toktyp != COMMA) 
      {
       __pv_ferr(1255,
        "edge sensitive path data source expression list separator expected - %s read",
        __prt_vtok());
       goto bad_end;
      }
     __get_vtok();
     if (__toktyp == COMMA || __toktyp == RPAR) 
      {
        __pv_ferr(1259,
         "edge sensitive path data source expression ,, or ,) forms illegal");
        goto bad_end;
      }
    }
  }
 else if ((olstx = rd_pthtermlst()) == NULL) goto bad_pth;

chk_endrpar:
 if (__toktyp != RPAR)
  {
   __pv_ferr(1256,
    "path output terminal list right parenthesis expected - %s read",
    __prt_vtok());
   goto bad_pth;
  }
get_eq:
 __get_vtok();
 if (__toktyp != EQ) 
  {
   __pv_ferr(1257, "path delay equal sign expected - %s read",
    __prt_vtok());
bad_end:
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
   return(TRUE);
  }
got_eq:
 /* know symbol table env. in specify always specparam local on mod. lev. */
 __sav_spsytp = __venviron[0];
 __venviron[0] = __venviron[1];
 __top_sti = 0;
 /* notice = read but not ( - unusual case of no 1st token read before call */ 
 good = rd_pathdelaylist(&pmphdr);
 __venviron[0] = __sav_spsytp;
 __top_sti++; 
 if (!good) goto bad_end;

 /* build the path delay element */
 pthp = (struct spcpth_t *) __my_malloc(sizeof(struct spcpth_t));
 init_spcpth(pthp);
 pthp->pthtyp = pdtyp; 
 pthp->pthpolar = pthpolar; 
 pthp->peins = (struct pathel_t *) ilstx;
 pthp->peouts = (struct pathel_t *) olstx;

 /* add the location identifying symbol */
 pthsyp = __bld_loc_symbol(__path_num, __venviron[0], "path", "delay path");
 pthsyp->sytyp = SYM_PTH;
 pthsyp->syfnam_ind = __cur_fnam_ind;
 pthsyp->sylin_cnt = __lin_cnt;
 pthp->pthsym = pthsyp;
 pthsyp->el.epthp = pthp;
 pthsyp->sydecl = TRUE;
 __path_num++;

 /* set delay part */
 pthp->pth_delrep = DT_CMPLST;
 pthp->pth_du.pdels = pmphdr;

 /* set sdpd and conditional path values */ 
 pthp->pthedge = pth_edge;  
 pthp->dsrc_polar = datasrcpolar;
 pthp->datasrcx = datsrcx;
 pthp->pth_ifnone = is_ifnone;
 pthp->pthcondx = condx;

 if (__end_spcpths == NULL) __cur_spfy->spcpths = pthp;
 else __end_spcpths->spcpthnxt = pthp;
 __end_spcpths = pthp;
 return(TRUE);
}

/*
 * read a path terminal list
 * know 1st token read and reads ending )
 */
static struct exprlst_t *rd_pthtermlst(void)
{
 struct exprlst_t *xpmphdr, *xpmp, *last_xpmp;

 /* build specify terminal list - semantics that requires subset of mod. */
 /* I/O port terminals checked later */
 /* no ,, and at least one required */
 for (xpmphdr = NULL, last_xpmp = NULL;;)
  {
   /* this will have skipped to end of statement on error */
   if (!col_pthexpr()) return(NULL);
   __bld_xtree(0);
   xpmp = __alloc_xprlst();
   xpmp->xp = __root_ndp;
   if (last_xpmp == NULL) xpmphdr = xpmp; else last_xpmp->xpnxt = xpmp;
   last_xpmp = xpmp;
   if (__toktyp == RPAR || __toktyp == FPTHCON || __toktyp == PPTHCON
    || __toktyp == PLUS || __toktyp == MINUS 
    || __toktyp == PARTSEL_NDX_PLUS || __toktyp == PARTSEL_NDX_MINUS 
    || __toktyp == TCHKEVAND || __toktyp == COLON) break;
   __get_vtok();
  }
 return(xpmphdr);
}

/*
 * collect a delay path terminal expression
 * expects 1st token to be read and read ending token
 * ends with ) or ',' or => or *> or - or + or : preceding connection op.
 * for timing checks can end with TCHKEVAND &&&
 * allows full expressions because port bit select can be full const. expr.
 *
 * notice ending thing not included in expr. but left in token
 *
 * this collects a specify expr. - caller must eliminate wrong tokens for
 * either tchk or path 
 *
 * notice this is lhs element not delay constants
 * maybe should be empty on error
 */
static int32 col_pthexpr(void)
{
 int32 parlevel, sqblevel;

 for (__last_xtk = -1, parlevel = 0, sqblevel = 0;;)
  {
   switch (__toktyp) {
    case LPAR: parlevel++; break;
    /* any expression (must later be constant) legal in selects */
    case LSB: sqblevel++; break;
    case RPAR: 
     if (parlevel <= 0 && sqblevel <= 0) return(TRUE); else parlevel--;
     break;
   case RSB:
    sqblevel--;
    break;
   case COMMA:
    /* illegal here but parse and check later */
    if (parlevel <= 0 && sqblevel <= 0) return(TRUE);
    break;
   /* AIV 08/05/08 - these now parse as one token +: */
   case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   case PLUS: case MINUS:
    if (parlevel <= 0 && sqblevel <= 0) return(TRUE);
    break;
   case COLON:
    if (parlevel <= 0 && sqblevel <= 0) return(TRUE);
    break;
   /* notice these are never nested */
   case FPTHCON: case PPTHCON: case TCHKEVAND:
    return(TRUE);
   case TEOF:
   case SEMI:
    goto bad_end;
   }
   if (!__bld_expnode()) goto bad_end;
   __get_vtok();
  }

bad_end:
 __set_xtab_errval();
 return(FALSE);
}

/*
 * read delay path list 
 * almost same as read oparams del but surrounding () always optional
 *
 * reads and checks for ending ; 
 * builds a parameter/delay list and returns pointer to header
 * returns F on sync error - caller must resync
 * but in places with known delimiter attempt to resync to delim 
 */
static int32 rd_pathdelaylist(struct paramlst_t **pmphdr)
{
 int32 rv;
 struct paramlst_t *pmp, *last_pmp;

 *pmphdr = NULL;

 /* this is #[number] or #id - not (..) form - min:typ:max requires () */
 /* for path delay will never see this form */
 __get_vtok();
 /* case 1: has optional () surround list */
 if (__toktyp == LPAR) 
  {
   for (last_pmp = NULL;;)
    {
     __get_vtok();
     if (!__col_delexpr(FALSE))
      {
       /* need to look to skip to any possible end ( may be unmatched */
       if (!__vskipto3_modend(COMMA, RPAR, SEMI)) return(FALSE);
       if (__toktyp == SEMI) return(FALSE);
       if (__toktyp == RPAR) { __get_vtok(); rv = FALSE; goto chk_semi; }
       /* if comman do not add but continue checking */
       continue;
      }       
     __bld_xtree(0);
     pmp = __alloc_pval();
     pmp->plxndp = __root_ndp;

     /* link on front */
     if (last_pmp == NULL) *pmphdr = pmp; else last_pmp->pmlnxt = pmp;
     last_pmp = pmp;

     if (__toktyp == COMMA) continue;
     if (__toktyp == RPAR) break;
     /* should never happen - sync on err above, if does give up */
     __pv_ferr(1050,
      "path delay delay list comma or right parenthesis expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   rv = TRUE;
   __get_vtok();
chk_semi:
   if (__toktyp != SEMI)
    {
     __pv_ferr(1279, "path delay final ; expected - %s read", __prt_vtok());
     return(FALSE);
    }
   return(rv);
  }
 /* case 2: optional surrounding omitted */ 
 for (last_pmp = NULL;;)
  {
   /* this reads the end , or ; */
   if (!__col_paramrhsexpr())
    {
     /* need to look to skip to any possible end ( may be unmatched */
     if (!__vskipto3_modend(COMMA, RPAR, SEMI)) return(FALSE);
     if (__toktyp == SEMI) return(FALSE);
     if (__toktyp == RPAR) { __get_vtok(); rv = FALSE; goto chk_semi; }
     __get_vtok();
     continue;
    }       
   __bld_xtree(0);
   pmp = __alloc_pval();
   pmp->plxndp = __root_ndp;
   if (last_pmp == NULL) *pmphdr = pmp; else last_pmp->pmlnxt = pmp;
   last_pmp = pmp;

   if (__toktyp == COMMA) { __get_vtok(); continue; }
   if (__toktyp == SEMI) break;
   /* should never happen - sync on err above, if does give up */
   __pv_ferr(1050,
    "path delay delay list comma or semicolon expected - %s read",
     __prt_vtok());
   return(FALSE);
  }
 return(TRUE);
}

/*
 * return T if expression has any global reference
 */
extern int32 __expr_has_glb(struct expr_t *xp)
{
 struct expr_t *xp2;

 if (__isleaf(xp))
  {
   if (xp->optyp == GLBREF) return(TRUE);
   return(FALSE);
  }

 for (xp2 = xp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   if (__expr_has_glb(xp2)) return(TRUE);  
  }

 if (xp->lu.x != NULL) { if (__expr_has_glb(xp->lu.x)) return(TRUE); }  
 if (xp->ru.x != NULL) { if (__expr_has_glb(xp->ru.x)) return(TRUE); }
 return(FALSE);
}
 
/*
 * initialize a specify section delay path
 */
static void init_spcpth(struct spcpth_t *pthp)
{
 pthp->pthtyp = PTH_NONE;
 pthp->pth_gone = FALSE;
 pthp->pth_as_xprs = TRUE;
 pthp->pth_delrep = DT_NONE;
 pthp->pthpolar = FALSE;
 pthp->pthedge = NOEDGE;
 pthp->dsrc_polar = POLAR_NONE; 
 pthp->pth_ifnone = FALSE;
 pthp->pth_0del_rem = FALSE;
 pthp->pthsym = NULL;
 pthp->last_pein = -1;
 pthp->last_peout = -1;
 pthp->peins = NULL;
 pthp->peouts = NULL;
 pthp->pth_du.d1v = NULL;
 pthp->datasrcx = NULL;
 pthp->pthcondx = NULL;
 pthp->spcpthnxt = NULL;
 pthp->spcpth_id = -1;
}

/*
 * TIMING CHECK READ ROUTINES
 */

/*
 * read setup or hold timing check
 * know system task keyword and ( read and reads ending ; if possible
 *
 * read and parse timing checks as is - during prep changed to needed form
 */
static int32 rd_setup_or_hold_tchk(word32 ttyp)
{
 int32 fnum, lnum;
 struct sy_t *syp, *tcsyp;
 struct paramlst_t *pmp;
 struct tchk_t tmptchk;
 struct expr_t *limx;

 __init_tchk(&tmptchk, ttyp);
 /* must save location since, need system task line as tchk loc. */
 fnum = __cur_fnam_ind;
 lnum = __lin_cnt;
 if (!rd_tchk_part(ttyp, &tmptchk, &limx)) return(FALSE);

 /* SJM 06-16-09 - now allowing missing notifier form to be ",)" */ 
 /* notice can only be ID if present */
 syp = NULL;
 if (__toktyp == COMMA)
  {
   /* SJM 06-16-09 - notifier now requires ID to have been read */
   __get_vtok();
   /* now allowing ,); omitted notifer form */
   if (__toktyp == RPAR) goto got_rpar;
   syp = rd_notifier();
  __get_vtok();
  }

 /* even even error end, still add since good */
 if (__toktyp != RPAR) goto noparsemi;
got_rpar:
 __get_vtok();
 if (__toktyp != SEMI)
  {
noparsemi:
   __pv_ferr(1261, "%s timing check does not end with ); - %s read",
    __to_tcnam(__xs, ttyp), __prt_vtok());
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
  }
 __cur_tchk = (struct tchk_t *) __my_malloc(sizeof(struct tchk_t));
 *__cur_tchk = tmptchk; 
 /* add the location idnentifying symbol */
 tcsyp = __bld_loc_symbol(__tchk_num, __venviron[0], "tchk", "timing check");
 tcsyp->sytyp = SYM_TCHK;
 tcsyp->syfnam_ind = fnum;
 tcsyp->sylin_cnt = lnum;
 tcsyp->el.etcp = __cur_tchk;
 tcsyp->sydecl = TRUE;
 __cur_tchk->tcsym = tcsyp;
 tcsyp->el.etcp = __cur_tchk;
 __tchk_num++;

 __cur_tchk->ntfy_np = (struct net_t *) syp;
 /* setup and hold identical - users changes order of args - ref. event */
 /* always first so $setup(data, clk, ...), $hold(clk, data, ...) */
 pmp = __alloc_pval(); pmp->plxndp = limx; pmp->pmlnxt = NULL;
 __cur_tchk->tclim_du.pdels = pmp;
 return(TRUE);
} 

/*
 * build a local symbol - for timing check and continuous assign etc.
 *
 * even if already declared, change to delay object
 * if used previously, change to delay object - error if previously declared
 * if used in previous expr. but later declared, error emitted at declaration
 * common case first used in $set[it]delay expr. and added to symbol table
 * as wire then here changed to delay object
 */
extern struct sy_t *__bld_loc_symbol(int32 num, struct symtab_t *sytp,
 char *pref, char *emsgnam)
{
 char s1[RECLEN];
 struct sy_t *syp;

 sprintf(s1, "__%s$$%d", pref, num);
 syp = __decl_sym(s1, sytp);
 if (!__sym_is_new)
  {
   if (syp->sydecl)
    {
     __pv_ferr(1160,
      "%s constructed internal name %s conflicts with declared %s",
      emsgnam, s1, __to_sytyp(__xs, syp->sytyp));
    }
   else
    {
     __pv_ferr(1160, "%s constructed internal name %s conflicts with wire",
      emsgnam, s1);
    }
  }
 return(syp);
}

/*
 * read the event and first limit part of all timing checks
 * common code for all timing checks, limits differ
 * this must read 1st token before reading tchk events
 * if returns F, parameters not set
 * this syncs to ; or item location and returns F 
 * on T reads ) or , after first (maybe only) limit
 * notice 1 limit always required
 */
static int32 rd_tchk_part(word32 ttyp, struct tchk_t *tcp,
 struct expr_t **limx)
{
 struct expr_t *xp, *condx;
 int32 edgval;

 /* notice ref. always first */
 __get_vtok();
 if (!rd_tchk_selector(&edgval, &xp, &condx))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
got_semi:
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
  }
 tcp->startedge = edgval;  
 tcp->startxp = xp;
 tcp->startcondx = condx;

 /* tcp initialized to empty fields */
 if (ttyp != TCHK_WIDTH && ttyp != TCHK_PERIOD) 
  {
   __get_vtok();
   if (!rd_tchk_selector(&edgval, &xp, &condx))
    {
     if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
     if (__toktyp == SEMI) goto got_semi;
    }  
   tcp->chkedge = edgval;  
   tcp->chkxp = xp;
   tcp->chkcondx = condx;
  }
 __get_vtok();
 __sav_spsytp = __venviron[0];
 __venviron[0] = __cur_spfy->spfsyms;
 /* limit is one number but can be d:d:d form - but know ends with , or ) */
 if (!__col_delexpr(FALSE))
  { 
   if (!__spec_vskipto2_any(SEMI, COMMA))
    { __venviron[0] = __sav_spsytp; return(FALSE); }
   if (__toktyp == SEMI)
    { __venviron[0] = __sav_spsytp; goto got_semi; }
   /* set error, if ,, form will not get here */
   /* make it look like ,, form */
   __set_0tab_errval();
  }
 __bld_xtree(0);
 if (__has_top_mtm)
  {
   __pv_fwarn(653,
    "%s timing check min:typ:max limit expression needs parentheses under 1364 - unportable",
    __to_tcnam(__xs, ttyp));
  }
 *limx = __root_ndp;
 __venviron[0] = __sav_spsytp;
 return(TRUE);
}

/*
 * initialize a timing check record
 */
extern void __init_tchk(struct tchk_t *tcp, word32 ttyp)
{
 tcp->tchktyp = ttyp; 
 /* notice del rep applies to both limits if present */
 tcp->tc_delrep = DT_CMPLST; 
 tcp->tc_delrep2 = DT_CMPLST; 
 tcp->tc_gone = FALSE;
 tcp->tc_supofsuphld = FALSE;
 tcp->tc_recofrecrem = FALSE;
 tcp->tc_haslim2 = FALSE;
 tcp->startedge = NOEDGE;
 tcp->startxp = NULL;
 tcp->tcsym = NULL;
 tcp->startcondx = NULL;
 tcp->chkedge = NOEDGE;
 tcp->chkxp = NULL;
 tcp->chkcondx = NULL;
 tcp->stamptim_condx = NULL;
 tcp->chktim_condx = NULL;
 tcp->delayed_refx = NULL;
 tcp->delayed_datx = NULL;
 /* notice this may be nil */
 tcp->ntfy_np = NULL;
 tcp->tclim_du.pdels = NULL;
 tcp->tclim2_du.pdels = NULL;
 tcp->tchknxt = NULL;
}

/*
 * read setuphold timing check (both with 2 limits)
 * know system task keyword read
 */
static int32 rd_setuphold_tchk(void)
{
 word32 ttyp;
 int32 fnum, lnum;
 struct tchk_t tmptchk;
 struct expr_t *limx, *lim2x, *stamptim_condx, *chktim_condx;
 struct expr_t *delayed_ref_vrefx, *delayed_data_vrefx;
 struct sy_t *syp, *tcsyp;
 struct paramlst_t *pmp;

 ttyp = TCHK_SETUPHOLD;
 __init_tchk(&tmptchk, ttyp);
 stamptim_condx = chktim_condx = delayed_ref_vrefx = delayed_data_vrefx = NULL;
 fnum = __cur_fnam_ind;
 lnum = __lin_cnt;

 if (!rd_tchk_part(ttyp, &tmptchk, &limx)) return(FALSE);
 if (__toktyp != COMMA)
  {
   __pv_ferr(1267,
    "$setuphold hold limit expression , terminator expected - %s read",
    __prt_vtok());
   __spec_vskipto_any(SEMI);
   return(FALSE);
  }
 __get_vtok();
 __sav_spsytp = __venviron[0];
 __venviron[0] = __cur_spfy->spfsyms;
 /* can be ,, or ,) empty but required */
 if (!__col_delexpr(FALSE))
  { 
   if (!__spec_vskipto2_any(SEMI, COMMA))
    { __venviron[0] = __sav_spsytp; return(FALSE); }
   if (__toktyp == SEMI)
    {
     __venviron[0] = __sav_spsytp;
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   /* set rhs error expr. */
   __set_0tab_errval();
  }
 __bld_xtree(0);
 if (__has_top_mtm)
  {
   __pv_fwarn(653,
    "%s timing check min:typ:max 2nd limit expression needs parentheses under 1364 - unportable",
    __to_tcnam(__xs, ttyp));
  }
 lim2x = __root_ndp;
 __venviron[0] = __sav_spsytp;

 /* SJM 06-16-09 - now allowing missing notifier form to be ",)" */ 
 /* notice can only be ID if present */
 syp = NULL;
 if (__toktyp == COMMA)
  { 
   /* SJM 06-16-09 - notifier now requires ID to have been read */
   __get_vtok();
   /* SJM 06-18-09 - allowing ",);" empty notifier form now */
   if (__toktyp == RPAR) goto got_rpar;
   /* SJM 05-21-09 for setuphold and recrem ,, possible for others only ,) */
   if (__toktyp != COMMA) syp = rd_notifier();
   __get_vtok();
  } 
 /* SJM 06-16-09 - , or ) after notifier read - notifier now optional */
 if (__toktyp == RPAR) goto got_rpar;
 if (__toktyp != COMMA) goto noparsemi; 

 /* first optional arg is the time stamp condition delay expr */
 if (!rd_optional_tc_cond(&(stamptim_condx), ttyp))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   stamptim_condx = NULL;
  }
 /* SJM 06-21-09 - need warning if unsupported timing check field */
 if (stamptim_condx != NULL)
  {
   __pv_fwarn(3153,
    "%s optional time stamp condition expression %s unsupported - ignored",
    __to_tcnam(__xs, ttyp), __msgexpr_tostr(__xs2, stamptim_condx));
  }

 /* now need either , or ) */
 if (__toktyp == RPAR) goto got_rpar;
 if (__toktyp != COMMA) goto noparsemi; 

 /* 2nd optional arg is the time check condition delay expr */
 if (!rd_optional_tc_cond(&(chktim_condx), ttyp))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   chktim_condx = NULL;
  }
 /* SJM 06-21-09 - need warning if unsupported timing check field */
 if (chktim_condx != NULL)
  {
   __pv_fwarn(3154,
    "%s optional time check condition expression %s unsupported - ignored",
    __to_tcnam(__xs, ttyp), __msgexpr_tostr(__xs2, chktim_condx));
  }

 /* now need either , or ) */
 if (__toktyp == RPAR) goto got_rpar;
 if (__toktyp != COMMA) goto noparsemi; 

 /* 3rd optional arg is the time check condition delay expr */
 if (!rd_optional_tc_delayed_net(&(delayed_ref_vrefx), ttyp))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   delayed_ref_vrefx = NULL;
  }
 /* SJM 06-21-09 - need warning if unsupported timing check field */
 if (delayed_ref_vrefx != NULL)
  {
   __pv_fwarn(3155,
    "%s optional delayed reference variable %s unsupported - ignored",
    __to_tcnam(__xs, ttyp), __msgexpr_tostr(__xs2, delayed_ref_vrefx));
  }

 /* now need either , or ) */
 if (__toktyp == RPAR) goto got_rpar;
 if (__toktyp != COMMA) goto noparsemi; 

 /* 3rd optional arg is the time check condition delay expr */
 if (!rd_optional_tc_delayed_net(&(delayed_data_vrefx), ttyp))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   delayed_data_vrefx = NULL;
  }
 /* SJM 06-21-09 - need warning if unsupported timing check field */
 if (delayed_data_vrefx != NULL)
  {
   __pv_fwarn(3155,
    "%s optional delayed data variable %s unsupported - ignored",
    __to_tcnam(__xs, ttyp), __msgexpr_tostr(__xs2, delayed_data_vrefx));
  }

 if (__toktyp != RPAR) goto noparsemi;

got_rpar:
 __get_vtok();
 if (__toktyp != SEMI)
  {
noparsemi:
   __pv_ferr(1262, "$setuphold timing check does not end with ); - %s read",
    __prt_vtok());
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
  }
 __cur_tchk = (struct tchk_t *) __my_malloc(sizeof(struct tchk_t));
 *__cur_tchk = tmptchk; 

 /* add the location idnentifying symbol */
 tcsyp = __bld_loc_symbol(__tchk_num, __venviron[0], "tchk", "timing check");
 tcsyp->sytyp = SYM_TCHK;
 tcsyp->syfnam_ind = fnum;
 tcsyp->sylin_cnt = lnum;
 __cur_tchk->tcsym = tcsyp;
 tcsyp->el.etcp = __cur_tchk;
 __tchk_num++;
 __cur_tchk->ntfy_np = (struct net_t *) syp;
 pmp = __alloc_pval();
 pmp->plxndp = limx;
 pmp->pmlnxt = NULL;
 __cur_tchk->tclim_du.pdels = pmp;
 pmp = __alloc_pval();
 pmp->plxndp = lim2x;
 pmp->pmlnxt = NULL;
 __cur_tchk->tclim2_du.pdels = pmp;
 __cur_tchk->tc_haslim2 = TRUE;

 /* SJM 06-18-09 - new optional negative limit and delayed var access flds */
 __cur_tchk->stamptim_condx = stamptim_condx;
 __cur_tchk->chktim_condx = chktim_condx;
 __cur_tchk->delayed_refx = delayed_ref_vrefx;
 __cur_tchk->delayed_datx = delayed_data_vrefx;
 return(TRUE);
}

/*
 * read a optional setuphold or recrem stamp time condition
 *
 * leading , read and reads ending , or ) 
 * SJM 06-16-09 routine for new
 */
static int32 rd_optional_tc_cond(struct expr_t **timcondx, int32 ttyp)
{
 struct symtab_t *sav_loc_spsytp;

 /* AIV 10/11/10 - this was wrong need to look for D_delayed as module */
 /* level defined wire - not local to specify block */
 /* these are currently ignored - but gets undefined net error */
 /* $setuphold(CP, D, SETUP_D_CP_R, HOLD_D_CP_R,,,,CP_delayed,D_delayed); */
 sav_loc_spsytp = __venviron[0];
 __venviron[0] = __sav_spsytp;

 *timcondx = NULL;
 __get_vtok();
 if (!__col_delexpr(TRUE))
  { 
   if (!__spec_vskipto2_any(SEMI, COMMA))
    { __venviron[0] = sav_loc_spsytp; return(FALSE); }
   if (__toktyp == SEMI)
    {
     __venviron[0] = sav_loc_spsytp;
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   /* set rhs error expr. */
   __set_xtab_errval();
  }
 __bld_xtree(0);
 if (__root_ndp != NULL && __root_ndp->optyp == OPEMPTY)
  {
   __venviron[0] = sav_loc_spsytp;
   return(TRUE);
  }

 if (__has_top_mtm)
  {
   __pv_fwarn(653,
    "%s timing check min:typ:max optional time condition needs parentheses under 1364 - unportable",
    __to_tcnam(__xs, ttyp));
  }
 __venviron[0] = sav_loc_spsytp;
 *timcondx = __root_ndp;
 return(TRUE);
}

/*
 * read a optional setuphold or recrem delayed_expr (var or const bsel)
 *
 * SJM 06-18-09 new routine for 1364-2005 timing checks that allow access
 * to reference (stamp) and data (check) recorded event net values
 *
 * notice this must find net in module level symbol table not specify
 */
static int32 rd_optional_tc_delayed_net(struct expr_t **delayedx, int32 ttyp)
{
 struct expr_t *vrefx;
 struct net_t *np;

 *delayedx = NULL;
 __get_vtok();
 /* returns F on error */
 if (!__col_connexpr(-1))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   /* set rhs error expr. */
   __set_xtab_errval();
  }
 __bld_xtree(0);
 if (__root_ndp != NULL && __root_ndp->optyp == OPEMPTY) return(TRUE);

 vrefx = __root_ndp;
 if (vrefx->optyp == ID)
  {
   if (vrefx->lu.sy->sytyp != SYM_N)
    {
bad_vref:
     __pv_ferr(3515,
      "%s timing delayed ref or data expression %s illegal - must be variable or constant bit select",  
      __to_tcnam(__xs, ttyp), __msgexpr_tostr(__xs2, vrefx));
     return(TRUE);
    }
   np = vrefx->lu.sy->el.enp;
   if (np->n_isaparam) goto bad_vref;
  }
 else if (vrefx->optyp == LSB)
  {
   if (vrefx->lu.x->lu.sy->sytyp != SYM_N) goto bad_vref;
   np = vrefx->lu.x->lu.sy->el.enp;
   if (np->n_isaparam) goto bad_vref;
   if (!__is_const_expr(vrefx->ru.x)) goto bad_vref;
  }
 else goto bad_vref;

 *delayedx = vrefx;
 return(TRUE);
}

/*
 * read recrem timing check (both with 2 limits)
 * know system task keyword read
 *
 * SJM 01/16/04 - almost same as setup hold but 2001 LRM has extra stuff
 * that is not yet added
 */
static int32 rd_recrem_tchk(void)
{
 word32 ttyp;
 int32 fnum, lnum;
 struct tchk_t tmptchk;
 struct expr_t *limx, *lim2x, *stamptim_condx, *chktim_condx;
 struct expr_t *delayed_ref_vrefx, *delayed_data_vrefx;
 struct sy_t *syp, *tcsyp;
 struct paramlst_t *pmp;
 char s1[RECLEN];

 ttyp = TCHK_RECREM;
 __init_tchk(&tmptchk, ttyp);
 stamptim_condx = chktim_condx = delayed_ref_vrefx = delayed_data_vrefx = NULL;
 fnum = __cur_fnam_ind;
 lnum = __lin_cnt;

 if (!rd_tchk_part(ttyp, &tmptchk, &limx)) return(FALSE);

 /* for recrem both terminals must be edges */ 
 if (tmptchk.startedge == NOEDGE)
  {
   __pv_ferr(1260,
   "%s timing check first recovery reference event missing required edge",
   __to_tcnam(s1, ttyp));
  }
 if (tmptchk.chkedge == NOEDGE)
  {
   __pv_ferr(1260,
    "%s timing 2nd removal reference event missing required edge",
   __to_tcnam(s1, ttyp));
  }

 if (__toktyp != COMMA)
  {
   __pv_ferr(1267,
    "$recrem removal limit expression , terminator expected - %s read",
    __prt_vtok());
   __spec_vskipto_any(SEMI);
   return(FALSE);
  }
 __get_vtok();
 __sav_spsytp = __venviron[0];
 __venviron[0] = __cur_spfy->spfsyms;
 /* can be ,, or ,) empty but required */
 if (!__col_delexpr(FALSE))
  { 
   if (!__spec_vskipto2_any(SEMI, COMMA))
    { __venviron[0] = __sav_spsytp; return(FALSE); }
   if (__toktyp == SEMI)
    {
     __venviron[0] = __sav_spsytp;
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   /* set rhs error expr. */
   __set_0tab_errval();
  }
 __bld_xtree(0);
 if (__has_top_mtm)
  {
   __pv_fwarn(653,
    "%s timing check min:typ:max 2nd limit expression needs parentheses under 1364 - unportable",
    __to_tcnam(__xs, ttyp));
  }
 lim2x = __root_ndp;
 __venviron[0] = __sav_spsytp;

 /* SJM 06-16-09 - now allowing missing notifier form to be ",)" */ 
 /* notice can only be ID if present */
 syp = NULL;
 if (__toktyp == COMMA)
  {
   /* SJM 06-16-09 - notifier now requires ID to have been read */
   __get_vtok();
   if (__toktyp == RPAR) goto got_rpar;
   /* SJM 05-21-09 for setuphold and recrem ,, possible for others only ,) */
   if (__toktyp != COMMA) syp = rd_notifier();
   __get_vtok();
  } 

 /* SJM 06-16-09 - , or ) after notifier read - notifier now optional */
 if (__toktyp == RPAR) goto got_rpar;
 if (__toktyp != COMMA) goto noparsemi; 

 /* first optional arg is the time stamp condition delay expr */
 if (!rd_optional_tc_cond(&(stamptim_condx), ttyp))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   stamptim_condx = NULL;
  }

 /* now need either , or ) */
 if (__toktyp == RPAR) goto got_rpar;
 if (__toktyp != COMMA) goto noparsemi; 

 /* 2nd optional arg is the time check condition delay expr */
 if (!rd_optional_tc_cond(&(chktim_condx), ttyp))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   chktim_condx = NULL;
  }

 /* now need either , or ) */
 if (__toktyp == RPAR) goto got_rpar;
 if (__toktyp != COMMA) goto noparsemi; 

 /* 3rd optional arg is the time check condition delay expr */
 if (!rd_optional_tc_delayed_net(&(delayed_ref_vrefx), ttyp))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   delayed_ref_vrefx = NULL;
  }

 /* now need either , or ) */
 if (__toktyp == RPAR) goto got_rpar;
 if (__toktyp != COMMA) goto noparsemi; 

 /* 3rd optional arg is the time check condition delay expr */
 if (!rd_optional_tc_delayed_net(&(delayed_data_vrefx), ttyp))
  {
   if (!__spec_vskipto2_any(SEMI, COMMA)) return(FALSE);
   if (__toktyp == SEMI)
    {
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   delayed_data_vrefx = NULL;
  }

 if (__toktyp != RPAR) goto noparsemi;
got_rpar:
 __get_vtok();
 if (__toktyp != SEMI)
  {
noparsemi:
   __pv_ferr(1262, "$recrem timing check does not end with ); - %s read",
    __prt_vtok());
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
  }
 __cur_tchk = (struct tchk_t *) __my_malloc(sizeof(struct tchk_t));
 *__cur_tchk = tmptchk; 

 /* add the location idnentifying symbol */
 tcsyp = __bld_loc_symbol(__tchk_num, __venviron[0], "tchk", "timing check");
 tcsyp->sytyp = SYM_TCHK;
 tcsyp->syfnam_ind = fnum;
 tcsyp->sylin_cnt = lnum;
 __cur_tchk->tcsym = tcsyp;
 tcsyp->el.etcp = __cur_tchk;
 __tchk_num++;
 __cur_tchk->ntfy_np = (struct net_t *) syp;
 pmp = __alloc_pval();
 pmp->plxndp = limx;
 pmp->pmlnxt = NULL;
 __cur_tchk->tclim_du.pdels = pmp;
 pmp = __alloc_pval();
 pmp->plxndp = lim2x;
 pmp->pmlnxt = NULL;
 __cur_tchk->tclim2_du.pdels = pmp;
 __cur_tchk->tc_haslim2 = TRUE;

 /* SJM 06-18-09 - new optional negative limit and delayed var access flds */
 __cur_tchk->stamptim_condx = stamptim_condx;
 __cur_tchk->chktim_condx = chktim_condx;
 __cur_tchk->delayed_refx = delayed_ref_vrefx;
 __cur_tchk->delayed_datx = delayed_data_vrefx;

 return(TRUE);
}

/*
 * read width timing check
 * know system task keyword read
 * width has 2 limits (but 2nd can be omitted), period has 1
 */
static int32 rd_width_tchk(void)
{
 word32 ttyp;
 int32 fnum, lnum;
 struct tchk_t tmptchk;
 struct expr_t *limx, *lim2x;
 struct sy_t *syp, *tcsyp;
 struct paramlst_t *pmp;

 ttyp = TCHK_WIDTH;
 __init_tchk(&tmptchk, ttyp);

 fnum = __cur_fnam_ind;
 lnum = __lin_cnt;

 if (!rd_tchk_part(ttyp, &tmptchk, &limx)) return(FALSE);
 if (tmptchk.startedge != E_NEGEDGE && tmptchk.startedge != E_POSEDGE)
  __pv_ferr(1266,
   "$width timing check event missing required negedge or posedge"); 
 /* 2nd limit optional and becomes NULL */
 if (__toktyp == RPAR) { syp = NULL; lim2x = NULL; goto done; }
 if (__toktyp != COMMA)
  {
   __pv_ferr(1268,
    "$width first limit expression , terminator expected - %s read",
    __prt_vtok());
   __spec_vskipto_any(SEMI);
   return(FALSE);
  }
 __get_vtok();
 __sav_spsytp = __venviron[0];
 __venviron[0] = __cur_spfy->spfsyms;
 /* lrm says no ,, or ,) forms for width */
 /* since ignored by sim value of 0 ok place holder and just ignored */
 if (!__col_delexpr(FALSE))
  { 
   if (!__spec_vskipto2_any(SEMI, COMMA))
    { __venviron[0] = __sav_spsytp; return(FALSE); }
   if (__toktyp == SEMI)
    {
     __venviron[0] = __sav_spsytp;
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   /* make it look like ,, form */
   __set_0tab_errval();
  }
 __bld_xtree(0);
 lim2x = __root_ndp;
 __venviron[0] = __sav_spsytp;

 /* notice can only be ID and may be omited */
 /* notice can only be ID if present */
 /* SJM 06-16-09 - now allowing missing notifier form to be ",)" */ 
 syp = NULL;
 if (__toktyp == COMMA)
  {
   /* SJM 06-16-09 - notifier now requires ID to have been read */
   __get_vtok();
   if (__toktyp == RPAR) goto done;
   syp = rd_notifier();
   __get_vtok();
  } 

 /* even even error end, still add since good */
 if (__toktyp != RPAR) goto noparsemi;
done:
 __get_vtok();
 if (__toktyp != SEMI)
  {
noparsemi:
   __pv_ferr(1263, "$width timing check does not end with ); - %s read",
    __prt_vtok());
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
  }

 /* notice no data even here */
 __cur_tchk = (struct tchk_t *) __my_malloc(sizeof(struct tchk_t));
 *__cur_tchk = tmptchk; 

 /* add the location idnentifying symbol */
 tcsyp = __bld_loc_symbol(__tchk_num, __venviron[0], "tchk", "timing check");
 tcsyp->sytyp = SYM_TCHK;
 tcsyp->syfnam_ind = fnum;
 tcsyp->sylin_cnt = lnum;
 tcsyp->sydecl = TRUE;
 __cur_tchk->tcsym = tcsyp;
 tcsyp->el.etcp = __cur_tchk;
 __tchk_num++;

 __cur_tchk->ntfy_np = (struct net_t *) syp;
 pmp = __alloc_pval();
 pmp->plxndp = limx;
 pmp->pmlnxt = NULL;
 __cur_tchk->tclim_du.pdels = pmp;
 /* always build 2nd limit as 0 if missing (during fix) so present */
 __cur_tchk->tc_haslim2 = TRUE;
 /* notice missing 2nd limit ok since only timing verifier threshold */
 /* that stops errors if pulse less than threshold */ 
 if (lim2x == NULL) lim2x = __bld_rng_numxpr(0L, 0L, WBITS);
 pmp = __alloc_pval();
 pmp->plxndp = lim2x;
 pmp->pmlnxt = NULL;
 __cur_tchk->tclim2_du.pdels = pmp;
 return(TRUE);
}

/*
 * read period timing check
 * know system task keyword read
 * period has 1 limit (required), width has 2
 */
static int32 rd_period_tchk(void)
{
 word32 ttyp;
 int32 fnum, lnum;
 struct tchk_t tmptchk;
 struct expr_t *limx;
 struct sy_t *syp, *tcsyp;
 struct paramlst_t *pmp;

 ttyp = TCHK_PERIOD;
 __init_tchk(&tmptchk, ttyp);

 fnum = __cur_fnam_ind;
 lnum = __lin_cnt;

 if (!rd_tchk_part(ttyp, &tmptchk, &limx)) return(FALSE);
 if (tmptchk.startedge == NOEDGE)
  __pv_ferr(1269, "$period timing check event missing required edge"); 

 /* SJM 06-16-09 - now allowing missing notifier form to be ",)" */ 
 /* notice can only be ID if present */
 syp = NULL;
 if (__toktyp == COMMA)
  {
   /* SJM 06-16-09 - notifier now requires ID to have been read */
   __get_vtok();
   if (__toktyp == RPAR) goto got_rpar;
   syp = rd_notifier();
   __get_vtok();
  } 

 /* even even error end, still add since good */
 if (__toktyp != RPAR) goto noparsemi;

got_rpar:
 __get_vtok();
 if (__toktyp != SEMI)
  {
noparsemi:
   __pv_ferr(1264, "$period timing check does not end with ); - %s read",
    __prt_vtok());
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
  }
 __cur_tchk = (struct tchk_t *) __my_malloc(sizeof(struct tchk_t));
 *__cur_tchk = tmptchk; 

 /* add the location idnentifying symbol */
 tcsyp = __bld_loc_symbol(__tchk_num, __venviron[0], "tchk", "timing check");
 tcsyp->sytyp = SYM_TCHK;
 tcsyp->syfnam_ind = fnum;
 tcsyp->sylin_cnt = lnum;
 tcsyp->sydecl = TRUE;
 __cur_tchk->tcsym = tcsyp;
 tcsyp->el.etcp = __cur_tchk;
 __tchk_num++;

 __cur_tchk->ntfy_np = (struct net_t *) syp;
 pmp = __alloc_pval();
 pmp->plxndp = limx;
 pmp->pmlnxt = NULL;
 __cur_tchk->tclim_du.pdels = pmp;
 return(TRUE);
}

/*
 * read skew or recovery timing check
 * know system task keyword read
 * different timing checks have identical arguments
 *
 * SJM 01/16/04 - added removal first terminal is the ref events that
 * needs to be an edge for both
 */
static int32 rd_skew_recov_rem_tchk(word32 ttyp)
{
 int32 fnum, lnum;
 struct tchk_t tmptchk;
 struct expr_t *limx;
 struct sy_t *syp, *tcsyp;
 struct paramlst_t *pmp;
 char s1[RECLEN];

 __init_tchk(&tmptchk, ttyp);
 /* must save location since, need system task line as tchk loc. */
 fnum = __cur_fnam_ind;
 lnum = __lin_cnt;
 if (!rd_tchk_part(ttyp, &tmptchk, &limx)) return(FALSE);
 if (ttyp == TCHK_RECOVERY || ttyp == TCHK_REMOVAL)
  {
   if (tmptchk.startedge == NOEDGE)
    __pv_ferr(1260,
     "%s timing check first reference event missing required edge",
     __to_tcnam(s1, ttyp));
  }

 /* SJM 06-16-09 - now allowing missing notifier form to be ",)" */ 
 /* notice can only be ID if present */
 syp = NULL;
 if (__toktyp == COMMA)
  {
   /* SJM 06-16-09 - notifier now requires ID to have been read */
   __get_vtok();
   if (__toktyp == RPAR) goto got_rpar;
   syp = rd_notifier();
   __get_vtok();
  } 

 /* even even error end, still add since good */
 if (__toktyp != RPAR) goto noparsemi;
got_rpar:
 __get_vtok();
 if (__toktyp != SEMI)
  {
noparsemi:
   __pv_ferr(1265, "%s timing check does not end with ); - %s read",
    __to_tcnam(s1, ttyp), __prt_vtok());
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
  }
 __cur_tchk = (struct tchk_t *) __my_malloc(sizeof(struct tchk_t));
 *__cur_tchk = tmptchk; 

 /* add the location identifying symbol */
 tcsyp = __bld_loc_symbol(__tchk_num, __venviron[0], "tchk", "timing check");
 tcsyp->sytyp = SYM_TCHK;
 tcsyp->syfnam_ind = fnum;
 tcsyp->sylin_cnt = lnum;
 tcsyp->sydecl = TRUE;
 __cur_tchk->tcsym = tcsyp;
 tcsyp->el.etcp = __cur_tchk;
 __tchk_num++;

 __cur_tchk->ntfy_np = (struct net_t *) syp;
 pmp = __alloc_pval(); pmp->plxndp = limx; pmp->pmlnxt = NULL;
 __cur_tchk->tclim_du.pdels = pmp;
 return(TRUE);
}

/*
 * must correctly parse $nochange but ignore with warning
 * this does not build and data structure
 */
static int32 rd_nochg_tchk(void)
{
 word32 ttyp;
 struct tchk_t tmptchk;
 struct expr_t *limx;
 char s1[RECLEN];

 ttyp = TCHK_NOCHANGE;
 __init_tchk(&tmptchk, ttyp);
 /* this reads the first limit but not second */
 if (!rd_tchk_part(ttyp, &tmptchk, &limx)) return(FALSE);
 if (tmptchk.startedge != E_NEGEDGE && tmptchk.startedge != E_POSEDGE)
  __pv_ferr(1271,
   "$nochange timing check first reference event missing negedge or posedge"); 
 __free_xtree(limx);
 __free_xtree(tmptchk.startxp);
 __free_xtree(tmptchk.startcondx);
 __free_xtree(tmptchk.chkxp);
 __free_xtree(tmptchk.chkcondx);

 if (__toktyp != COMMA)
  {
   __pv_ferr(1272,
    "$nochange second event - comma expected - %s read", __prt_vtok());
   __spec_vskipto_any(SEMI);
   return(FALSE);
  }
 __get_vtok();
 __sav_spsytp = __venviron[0];
 __venviron[0] = __cur_spfy->spfsyms;
 /* lrm says no ,, or ,) forms for nochange */
 if (!__col_delexpr(FALSE))
  { 
   if (!__spec_vskipto2_any(SEMI, COMMA))
    { __venviron[0] = __sav_spsytp; return(FALSE); }
   if (__toktyp == SEMI)
    {
     __venviron[0] = __sav_spsytp;
     __syncto_class = SYNC_SPECITEM;
     return(FALSE);
    }
   /* make it look like ,, form */
   __set_0tab_errval();
  }
 /* this is needed for checking */
 __bld_xtree(0);
 __free_xtree(__root_ndp);
 __venviron[0] = __sav_spsytp;
 /* even even error end, still add since good */
 if (__toktyp != RPAR) goto noparsemi;

 __get_vtok();
 if (__toktyp != SEMI)
  {
noparsemi:
   __pv_ferr(1273, "%s timing check does not end with ); - %s read",
    __to_tcnam(s1, ttyp), __prt_vtok());
   if (!__spec_vskipto_any(SEMI)) return(FALSE);
  }
 __pv_fwarn(599, "$nochange timing check has no effect in simulation");
 return(TRUE);
}

/*
 * read a timing check event - know always followed by , 
 * know 1st token read and reads ending ,
 * returns NULL on error, caller must skip to ;
 * caller syncs - returns NULL if syntax error (will need syncing)
 */
static int32 rd_tchk_selector(int32 *edgval, struct expr_t **xp,
 struct expr_t **condx)
{
 *edgval = NOEDGE;
 switch (__toktyp) {  
  case NEGEDGE: *edgval = E_NEGEDGE; break; 
  case POSEDGE: *edgval = E_POSEDGE; break; 
  case EDGE:
   __get_vtok();
   if (__toktyp != LSB) 
    {
     __pv_ferr(1281, "timing check event edge list [ expected - %s read",
      __prt_vtok());
edge_sync:
     /* caller must synchronize - except try for enclosing ] */
     if (!__spec_vskipto_any(RSB)) return(FALSE);
     goto get_pthx;
    }
   if (!rd_edges(edgval)) goto edge_sync;
   break;
  default: goto no_edge;
 }

get_pthx:
 __get_vtok();
no_edge:
 if (!col_pthexpr()) return(FALSE);
 __bld_xtree(0);
 *xp = __root_ndp;
 if (__toktyp != COMMA)
  {
   if (__toktyp != TCHKEVAND)
    {
     __pv_ferr(1282,
      "timing check data or reference event, comma or &&& expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   /* read &&& expr. */
   __get_vtok();
   if (!__col_connexpr(-1)) return(FALSE);
   if (__toktyp != COMMA)
    {
     __pv_ferr(1283,
      "timing check event &&& expression comma expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   __bld_xtree(0);
   *condx = __root_ndp;
  }
 else *condx = NULL;
 return(TRUE);
}

/*
 * read an edge list
 * know [ read and reads trailing ]
 * if error tries to sync to , ], ), ;
 */
static int32 rd_edges(int32 *edge)
{
 char s1[RECLEN];
 byte etmp, e1;

 *edge = etmp = NOEDGE;
 __letendnum_state = TRUE;
 for (;;)
  {
   strcpy(s1, "");
   for (;;)
    {
     __get_vtok();
     switch (__toktyp) {
      case COMMA: case RSB: goto got_pair;
      case ID: strcat(s1, __token); break;
      case NUMBER: strcat(s1, __numtoken); break;
      default:
       __pv_ferr(1284, "edge list edge value pair expected - %s read",
        __prt_vtok());
       __letendnum_state = FALSE;
       return(FALSE);
      }
    }
got_pair:
   if (strlen(s1) > 2)
    {
bad_edge:
     __pv_ferr(1286, "edge list element %s illegal", s1);
     continue;
    }
   switch (s1[0]) {
    case '0':
     if (s1[1] == '1') e1 = EDGE01;
     else if (s1[1] == 'x') e1 = EDGE0X;
     else goto bad_edge;
     break;
    case '1':
     if (s1[1] == '0') e1 = EDGE10;
     else if (s1[1] == 'x') e1 = EDGE1X;
     else goto bad_edge;
     break;
    case 'x':
     if (s1[1] == '0') e1 = EDGEX0;
     else if (s1[1] == '1') e1 = EDGEX1;
     else goto bad_edge;
     break;
    default: goto bad_edge;
   }
   if ((etmp & e1) != 0)
    __pv_fwarn(577, "edge %s repeated in edge list", s1);
   else etmp |= e1;
   /* notice last edge will be vv with __toktyp of ] - must proces last */
   if (__toktyp == RSB) break;
  }
 __letendnum_state = FALSE;
 *edge = etmp;
 return(TRUE);
}

/*
 * read an notifier 
 * know leading , read and reads just the notifier reg
 * SJM 06-16-09 - noifier now can be missing with ,, so caller must
 * read the possible notifier ID
 */
static struct sy_t *rd_notifier(void) 
{ 
 struct sy_t *syp;

 if (__toktyp != ID)
  {
bad_notfy:
   __pv_ferr(1285, "notifier register name expected - %s read",
    __prt_kywrd_vtok());
   return(NULL);
  } 
 /* this declares thing as a net - fixed later and checked even later */
 __last_xtk = -1;
 /* FIXME - since can never fail should change to arg terr */
 if (!__bld_expnode()) goto bad_notfy;
 __bld_xtree(0);
 syp = __root_ndp->lu.sy;
 /* type will be checked later */
 return(syp);
}

/*
 * VERILOG 2001 ATTRIBUTE READING ROUTINES
 */

/*
 * read, parse and build attribute list from attribute string
 * builds list and returns header of list or nil on error
 *
 * new verilog 2000 feature
 * know string between (* and *) stored on entry in attr name field
 * trick is to push string onto file stack as if it is no arg macro 
 *
 * expression value converted to constant number here because
 * attributes need to be used by tools that do not know pound param vals
 * i.e. can be fed, post generate source
 */
extern struct attr_t *__rd_parse_attribute(struct attr_t *rd_attrp)
{
 int32 sav_ecnt, sav_tot_lines, sav_fnam_ind, attllen;
 struct attr_t *attrp, *attr_hd, *last_attrp;
 char *chp; 
 char *attlin, attnam[IDLEN];

 attrp = attr_hd = last_attrp = NULL;
 attlin = rd_attrp->attrnam;
 /* SJM 07/30/01 - need to read chars and parse out of global */
 /* needed so can free work attrnam after rec built */ 
 if ((attllen = strlen(attlin)) >= __attrparsestrlen - 1)
  {
   __attrparsestr = __my_realloc(__attrparsestr, __attrparsestrlen,
    attllen + 1);
   __attrparsestrlen = attllen + 1;
  }
 strcpy(__attrparsestr, attlin); 

 /* need to save total lines read since counted in attr when collected */
 /* parsing here counts lines because new lines not escaped */
 sav_tot_lines = __total_rd_lines;
 sav_fnam_ind = __cur_fnam_ind;
 sav_ecnt = __pv_err_cnt;

 /* if currently reading file, must preserve line count */
 if (__visp->vi_s != NULL) __visp->vilin_cnt = __lin_cnt;
 /* push string on top of read stack */
 __push_vinfil();
 __visp->vichp = __visp->vichp_beg = __attrparsestr;

 /* make sure not freeing line even if somehow hit eof - never should */
 __visp->vichplen = -1;
 __in_s = NULL;
 /* DBG remove --- */
 if (__debug_flg) __dbg_msg("parsing attribute string %s\n", attlin);
 /* --- */

 __cur_fnam_ind = rd_attrp->attr_fnind;
 __lin_cnt = rd_attrp->attrlin_cnt;

 __get_vtok();
 /* ; added to end of saved attribute string if not there */
 if (__toktyp == SEMI) 
  {
   __pv_ferr(3405,
    "attribute_instance illegal - at least one attr_spec required");
chk_eol: 
   for (chp = __visp->vichp; *chp != '\0'; chp++)
    {
     if (!vis_white_(*chp))
      {
       __pv_ferr(3407,
        "attribute_instance comma separator expected - semicolon read");
       /* on error always skip to end of string - need EOF next read */
       while (*chp != '\0') chp++;
       goto done;
      }
    }
   goto done;
  }
 for (;;)
  {
   if (__toktyp != ID)
    {
     __pv_ferr(3404, "attribute name expected - %s read", __prt_vtok());
err_skip_eol:
     /* on error always skip to end of string - need EOF next read */
     for (chp = __visp->vichp; *chp != '\0'; chp++) ;
     goto done;
    }
   strcpy(attnam, __token);
   __get_vtok();
   __root_ndp = NULL; 
   if (__toktyp == EQ)
    {
     __get_vtok();
     /* LOOKATME - should try to resync on errors */
     __last_xtk = -1;
     /* on success (T), this reads either , or ; */
     if (!__col_comsemi(-1)) goto err_skip_eol;
     __bld_xtree(0);

     /* SJM 01-28-09 - attributes are not in structural param world */
     /* so to allow immediate eval, if constant func used it is error */
     /* should never see since attributes not used any more */
     if (__expr_has_glb(__root_ndp) || !src_rd_chk_paramexpr(__root_ndp, 0)
      || __xpr_hasfcall(__root_ndp))
      {
       __pv_ferr(3404,
        "attr_spec for attribute %s expression error - defined parameters and constants only - constant functions also illegal here", 
        attnam); 
       /* need to still add value of x to prevent further errors */
       __free2_xtree(__root_ndp);
       __root_ndp->szu.xclen = WBITS;
       /* default value is on 1 (non zero) */
       __set_numval(__root_ndp, 1, 0, WBITS);  
      }
     else
      {
       /* because of previous check, this can not fail */
       __eval_param_rhs_tonum(__root_ndp, __cur_fnam_ind, __lin_cnt);
      }
    }
   else __root_ndp = NULL;

   /* allocate in link in attribute */
   attrp = (struct attr_t *) __my_malloc(sizeof(struct attr_t));
   attrp->attr_tok = rd_attrp->attr_tok;
   attrp->attrnam = __pv_stralloc(attnam); 
   /* must eval. after all param setting is done */
   attrp->attr_xp = __root_ndp; 
   /* LOOKATME - think should just use attr inst loc */
   attrp->attr_fnind = __cur_fnam_ind;
   attrp->attrlin_cnt = __lin_cnt;
   attrp->attrnxt = NULL;
   if (last_attrp == NULL) attr_hd = attrp; else last_attrp->attrnxt = attrp;
   last_attrp = attrp;

   if (__toktyp == SEMI) goto chk_eol;
   if (__toktyp != COMMA)
    {
     __pv_ferr(3406, "attr_spec separator or end \"*)\" expected - %s read",
      __prt_vtok());
     goto err_skip_eol;
    }
   __get_vtok();
   continue;
  }

done:
 /* caller must free attribute string when pased for all instances */

 /* restore total lines read */
 __total_rd_lines = sav_tot_lines;
 __cur_fnam_ind = sav_fnam_ind;
 /* SJM 07/30/01 - was using visp but that was not set or index */
 __cur_fnam = __in_fils[__cur_fnam_ind];
 /* small memory leak if syntax error */
 if (__pv_err_cnt > sav_ecnt) return(NULL);
 /* emit warnings if attr duplicated with different value - inform if same */
 if (attr_hd != NULL) attr_hd = chk_dup_attrs(attr_hd);
 return(attr_hd);
}

/*
 * check attribute list for duplicates
 * if duplicate remove - if different value warn if same value inform
 * 
 * LOOKATME - if lots of attributes need to sort and match
 */
static struct attr_t *chk_dup_attrs(struct attr_t *attr_hd)
{
 int32 has_xmr;
 struct attr_t *attrp1, *attrp2, *last_attrp1;
 struct attr_t *new_attrhd, *attrp3;
 char s1[RECLEN], s2[RECLEN]; 

 new_attrhd = attr_hd;
 last_attrp1 = NULL;
 for (attrp1 = attr_hd; attrp1 != NULL;)
  {
   for (attrp2 = attrp1->attrnxt; attrp2 != NULL; attrp2 = attrp2->attrnxt)
    {
     if (strcmp(attrp1->attrnam, attrp2->attrnam) == 0) 
      {
       /* know both numbers but still use xpr cmp */ 
       if (__cmp_xpr(attrp1->attr_xp, attrp2->attr_xp, &has_xmr) == 0)
        {
         __gfinform(3001, attrp2->attr_fnind, attrp2->attrlin_cnt,
          "attribute %s duplicated with same value (first at %s) - first discared",
         attrp1->attrnam, __bld_lineloc(s1, attrp1->attr_fnind,
         attrp1->attrlin_cnt));  
        }
       else
        {
         __gfwarn(3101, attrp2->attr_fnind, attrp2->attrlin_cnt,
          "attribute %s value %s duplicated with different values - first at %s value %s discarded",
         attrp1->attrnam, __msgexpr_tostr(s1, attrp2->attr_xp),
         __bld_lineloc(__xs, attrp1->attr_fnind, attrp1->attrlin_cnt), 
         __msgexpr_tostr(s2, attrp1->attr_xp));
        }
       /* SJM 10/16/00 - must set next before freeing and splicing */
       attrp3 = attrp1->attrnxt;

       /* splice out first - if more duplicates will catch later */
       if (last_attrp1 == NULL) new_attrhd = attrp1->attrnxt; 
       else last_attrp1->attrnxt = attrp1->attrnxt;
       __free_xtree(attrp1->attr_xp);

       __my_free(attrp1, sizeof(struct attr_t));
       /* must not advance last attr */
       attrp1 = attrp3;
       goto chk_nxt_attr;
      }
    }
   attrp1 = attrp1->attrnxt;
   last_attrp1 = attrp1;     
chk_nxt_attr:;
  }
 return(new_attrhd);
}

/*
 * version of chk paramexpr that is called for parameters during
 * source input 
 */
static int32 src_rd_chk_paramexpr(struct expr_t *ndp, int32 xwid)
{
 int32 rv, sav_sfnam_ind, sav_slin_cnt;

 /* SJM 10/01/99 - improve error location for param checking */
 /* chk param expr needs sim locations set - set temporary guess here */
 sav_sfnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt;
 __sfnam_ind = __cur_fnam_ind;
 __slin_cnt = __lin_cnt;

 rv = __chk_paramexpr(ndp, xwid);

 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;

 return(rv);
}

/*
 * ROUTINES TO READ THE OPT CONFIG FILES AND SAVE TOKENS
 */

/*
 * read the opt config arg files and build lists with tokens and names
 *
 * this routine uses get 1vtok since no includes or macros allowed
 *
 * SJM 12-11-10 - look at me - for ` in numbers this calls get vtok
 * (i.e. 10'd`<some macro>) should fix - leaving for now
 */
extern void __rd_optcfg_files(void)
{
 struct ocfil_lst_t *ocfnp;

 /* SJM 12-11-10 - trick is to use file one up from last inf from options */
 /* that is called last lib fil and at end remove it - not in infils list */
 __last_lbf = __last_inf + 1;

 for (ocfnp = __optcfg_fils; ocfnp != NULL; ocfnp = ocfnp->oclnxt)
  {
   __in_fils[__last_lbf] = __pv_stralloc(ocfnp->ocfnam);
   __cur_fnam = __in_fils[__last_lbf];

   /* AIV PUTBACK print directory for now - for debugging */
   if ((__in_s = __tilde_fopen(__cur_fnam, "r")) == NULL)
    {
     __pv_err(4849,
      "cannot open -optconfigfile %s - skipped", __cur_fnam);
      continue;
     }
   if (feof(__in_s))
    {
     __pv_warn(4307, "-optconfigfile %s empty", __cur_fnam);
     continue;
    }
   /* whenever open new file must discard pushed back */
   __lasttoktyp = UNDEF;
   __cur_fnam_ind = __last_lbf;
   __cur_fnam = __in_fils[__cur_fnam_ind];
   __lin_cnt = 1;
   __file_just_op = TRUE;

   /* read the stmts with toggle (for now) attr for one fil */ 
   rd1_optcfg_fil(ocfnp);

   if (__in_s != NULL) fclose(__in_s);
   /* rest always get set in next loop - or visp record freed on exit */
   __my_free(__in_fils[__last_lbf], strlen(__in_fils[__last_lbf] + 1));
   __in_fils[__last_lbf] = NULL; 
  }
 __last_lbf = -1;
 /* DBG remove --- */ 
 if (__debug_flg) dmp_dsgn_optcfgs();
 /* --- */
}

/*
 * read cfg source file to find and elaborate current module
 *
 * SJM 12-12-10 - for now not adding new keywords - treating instance
 * as ID and compare name
 *
 * read one -optconfigfile (for now toggle attr file) and link read
 * statements onto opt cfg fil's opt cfg stmts list 
 */
static int32 rd1_optcfg_fil(struct ocfil_lst_t *ocfnp)
{
 int32 oc_sttyp, tree_dpth_cnt, blen, is_negative;
 struct ocfg_stmt_t *ocstmtp, *last_ocstmtp;

 /* SJM 12-12-10 - here no macro/include etc. expansion - not a src file */ 
 __toktyp = __get1_vtok(__in_s);
 if (__toktyp == TEOF)
  {
   __pv_fwarn(4840, "-optconfigfile option file %s contains no tokens",
    ocfnp->ocfnam);
   return(FALSE);
  }

 for (last_ocstmtp = NULL;;)
  {
//SJM 12-17-10 - LOOKATME - using 0 as current one, -1 all below */
//this is different from VCS - think about it
   tree_dpth_cnt = -1;
   switch (__toktyp) {
    case MODULE:
     oc_sttyp = OCFG_MOD;
     break;
    case ID:
     oc_sttyp = OCFG_TREE;
     if (strcmp(__token, "tree") == 0 || strcmp(__token, "tree_exclude") == 0) 
      {
       __toktyp = __get1_vtok(__in_s);
       if (__toktyp == LPAR) 
        {
         __toktyp = __get1_vtok(__in_s);
         is_negative = FALSE;
         if (__toktyp == MINUS)
          {
           is_negative = TRUE;
           __toktyp = __get1_vtok(__in_s);
          }
         if (__toktyp != NUMBER)
          {
           __pv_ferr(4841,
            "-optconfigfile tree statement found '(' but [number] missing - %s read",
            __prt_vtok());
           if (optcfg_skipto_semi()) break;
           return(FALSE);
          }
         blen = __itoklen - WBITS;
         if (!vval_is0_(&(__acwrk[1]), blen)
          || !vval_is0_(&(__bcwrk[0]), __itoklen))
          {
           __pv_ferr(4842,
            "-optconfigfile tree ([number]) %s non 32 bit non x/z value",
            __prt_vtok());
           if (optcfg_skipto_semi()) 
            { __toktyp = __get1_vtok(__in_s); continue; } 
           return(FALSE);
          }
         else tree_dpth_cnt = (int32) __acwrk[0];

         /* if negative value - check only -1 supported for now */
         if (is_negative)
          {
           tree_dpth_cnt = -tree_dpth_cnt;
           if (tree_dpth_cnt != -1)
            {
             __pv_ferr(4850,
              "-optconfigfile tree ([number]) %d -1 is the only negative value supported",
              tree_dpth_cnt);
             if (optcfg_skipto_semi()) 
              { __toktyp = __get1_vtok(__in_s); continue; } 
             return(FALSE);
            }
          }
         __toktyp = __get1_vtok(__in_s); 
         if (__toktyp != RPAR) 
          {
           __pv_ferr(4843,
            "-optconfigfile tree ([number]) ending ')' missing - %s read",
            __prt_vtok());
           if (optcfg_skipto_semi()) 
            { __toktyp = __get1_vtok(__in_s); continue; } 
           return(FALSE);
          }
         /* since for no (lev) form, read the '('', this needs to rd 1 past */  
         __toktyp = __get1_vtok(__in_s);
        }
       if (strcmp(__token, "tree") == 0) 
        {
         oc_sttyp = OCFG_TREE;
        }
       else oc_sttyp = OCFG_EXL_TREE;

       /* SJM 12-17-10 - here reading one ahead so need the goto */
       goto lset_brak_rd; 
      }
     /* AIV 12/23/10 - added support for exclude options */
     if (strcmp(__token, "instance") == 0)
      { 
       oc_sttyp = OCFG_INST;
      } 
     else if (strcmp(__token, "instance_exclude") == 0)
      { 
       oc_sttyp = OCFG_EXL_INST;
      } 
     else if (strcmp(__token, "module_exclude") == 0)
      {
       oc_sttyp = OCFG_EXL_MOD;
      }
     else goto unrec_oc_stmt; 
     break;
    default:
unrec_oc_stmt:
     __pv_ferr(4844, "-optconfigfile statement type name expected - %s read",
      __prt_vtok());
     if (optcfg_skipto_semi()) 
      { __toktyp = __get1_vtok(__in_s); continue; } 
     return(FALSE);     
    }
   /* have statement type keywords, look for list of verilog objects */
   __toktyp = __get1_vtok(__in_s); 
lset_brak_rd:
   if (__toktyp != LCB) 
    {
     __pv_ferr(4863,
      "-optconfigfile list of modules, instances or XMRs begin left set bracket expected - %s read",
      __prt_vtok());
     if (optcfg_skipto_semi()) 
      { __toktyp = __get1_vtok(__in_s); continue; } 
     return(FALSE);
    }
   /* alloc one opt config stmt record */
   ocstmtp = (struct ocfg_stmt_t *) __my_malloc(sizeof(struct ocfg_stmt_t));
   ocstmtp->ocfgtyp = oc_sttyp;
   ocstmtp->tree_level_val = tree_dpth_cnt; 
   ocstmtp->oc_ver_objs = NULL;
   ocstmtp->oc_props = NULL; 
   ocstmtp->ocsnxt = NULL;
   if (!rd_optcfg_ver_el_list(&(ocstmtp->oc_ver_objs)))
    {
     if (optcfg_skipto_semi()) 
      { __toktyp = __get1_vtok(__in_s); continue; } 
     return(FALSE);
    }
   /* have statement type keywords, look for list of opt cfg properties */
   __toktyp = __get1_vtok(__in_s); 
   if (__toktyp != LCB) 
    {
     __pv_ferr(4858,
      "-optconfigfile list of config properties expected - %s read",
      __prt_vtok());
     if (optcfg_skipto_semi()) 
      { __toktyp = __get1_vtok(__in_s); continue; } 
     return(FALSE);
    }
   if (!rd_optcfg_prop_list(&(ocstmtp->oc_props)))
    {
     if (optcfg_skipto_semi()) 
      { __toktyp = __get1_vtok(__in_s); continue; } 
     return(FALSE);
    }
   __toktyp = __get1_vtok(__in_s); 
   if (__toktyp == SEMI) 
    {
     if (last_ocstmtp == NULL) ocfnp->oc_stmts = last_ocstmtp = ocstmtp;
     else 
      {
       last_ocstmtp->ocsnxt = ocstmtp;
       last_ocstmtp = ocstmtp;
      } 
     __toktyp = __get1_vtok(__in_s);
     if (__toktyp == TEOF) return(TRUE);
     continue;
    }
   /* missing required semicolon that ends a opt config file statement */
   __pv_ferr(4859,
    "-optconfigfile statement missing ending semicolon - %s read",
    __prt_vtok());
   if (optcfg_skipto_semi()) 
    { __toktyp = __get1_vtok(__in_s); continue; } 
   return(FALSE);
  }
 return(TRUE);
}

/*
 * routine to read an opt config element (may be dot separated)
 *
 * know the first ID has been read and reads ending }
 * builds (adds to) a work opt cfg list - caller handling linking it in
 */  
static int32 rd_optcfg_ver_el_list(struct oc_vtok_t **ocvtok_hdr)
{
 __wrk_ocvtok_hd = __wrk_ocvtok_end = NULL;
 if (__toktyp != LCB) 
  {
   __pv_ferr(4861,
     "-optconfigfile list of modules, instances or XMRs left set bracket expected - %s read",
    __prt_vtok());
   return(FALSE);
  }

 for (;;) 
  {
   __toktyp = __get1_vtok(__in_s);
   if (__toktyp != ID)
    {
     __pv_ferr(4854,
      "-optconfigfile list of modules, instances or XMRs component expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   if (!rd_optcfg_1ver_el()) return(FALSE);
   if (__toktyp == RCB) break;
   /* DBG remove -- */ 
   if (__toktyp != COMMA) __misc_terr(__FILE__, __LINE__);
   /* --- */
  }
 *ocvtok_hdr = __wrk_ocvtok_hd;
 __wrk_ocvtok_hd = __wrk_ocvtok_end = NULL;
 return(TRUE);
}

/*
 * routine to read one verilog mod, inst or XMR element and add to work list
 *
 * know the first ID has been read and reads ending , or }
 * builds (adds to) a work opt cfg list - caller handling linking it in
 */  
static int32 rd_optcfg_1ver_el(void)
{
 int32 el_ttyp, el_lcnt;
 char namstr[IDLEN];

 /* DBG remove -- */
 if (__toktyp != ID) __misc_terr(__FILE__, __LINE__);
 /* --- */
 strcpy(namstr, __token);
 el_ttyp = ID;
 el_lcnt = __lin_cnt;
 __toktyp = __get1_vtok(__in_s);
 if (__toktyp == RCB || __toktyp == COMMA)
  {
   add_octok_toend(el_ttyp,  el_lcnt, namstr);
   return(TRUE);
  }
 if (__toktyp != DOT)
  {
   __pv_ferr(4857,
    "-optconfigfile list of items hierarchical reference contains illegal token %s",
    __prt_vtok());
   return(FALSE);
  }

 /* assemble rest of XMR */
 __toktyp = __get1_vtok(__in_s);
 for (;;)
  {
   if (__toktyp != ID)
    {
     __pv_ferr(4854,
      "-optconfigfile list of modules, instances or XMRs component expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   /* know it is an ID */
   strcat(namstr, ".");
   strcat(namstr, __token);
   __toktyp = __get1_vtok(__in_s);
   if (__toktyp == RCB) 
    {
     add_octok_toend(XMRID, el_lcnt, namstr);
     break;
    }
   if (__toktyp == COMMA) 
    {
     add_octok_toend(XMRID, el_lcnt, namstr);
     break;
    }

   /* AIV 03/05/11 - now allowing exlcude of bits so either can read a */
   /* bit select or part select here */
   if (__toktyp == LSB)
    {
     add_octok_toend(__toktyp, el_lcnt, namstr);
     __toktyp = __get1_vtok(__in_s);
     if (__toktyp != NUMBER)
      {
       __pv_ferr(4857,
        "-optconfigfile list of Verilog items hierarchical reference contains '[' constant number for range expected not - %s",
        __prt_vtok());
       return(FALSE);
      }
     /* convert to int and get value */
     /* SJM 06-13-13 - can't normalize to h:0 yet because do have net */
     __to_dhboval(__itokbase, TRUE);
     __wrk_ocvtok_end->ebi1 = (int32) __acwrk[0];

     __toktyp = __get1_vtok(__in_s);
     /* only bit case  - break */
     if (__toktyp == RSB)
      {
       /* 06-02-13 - bsel include/exclude must ebi 2 to be same as ebi 1 */
       __wrk_ocvtok_end->ebi2 = __wrk_ocvtok_end->ebi1;
       __toktyp = __get1_vtok(__in_s);
       break;
      }

     /* better be the part select pattern [lsb:rsb] */
     if (__toktyp != COLON)
      {
       __pv_ferr(4857,
        "-optconfigfile list of Verilog items hierarchical reference bit selection - ']' expected not - %s",
        __prt_vtok());
       return(FALSE);
      }
     __toktyp = __get1_vtok(__in_s);
     if (__toktyp != NUMBER)
      {
       __pv_ferr(4857,
        "-optconfigfile list of Verilog items hierarchical reference contains '[lsb:' constant number for range expected not - %s",
        __prt_vtok());
       return(FALSE);
      }
     __to_dhboval(__itokbase, TRUE);
     /* SJM 06-13-13 - can't normalize to h:0 yet because do have net */
     __wrk_ocvtok_end->ebi2 = (int32) __acwrk[0]; 

     __toktyp = __get1_vtok(__in_s);
     if (__toktyp == RSB)
      {
       __toktyp = __get1_vtok(__in_s);
       break;
      }
     __pv_ferr(4857,
       "-optconfigfile list of Verilog items hierarchical reference bit selection - ']' expected not - %s",
       __prt_vtok());
     return(FALSE);
    }
   if (__toktyp != DOT)
    {
     __pv_ferr(4857,
      "-optconfigfile list of Verilog items hierarchical reference contains illegal token %s",
      __prt_vtok());
     return(FALSE);
    }
   __toktyp = __get1_vtok(__in_s); 
  }
 return(TRUE);
}

/*
 * routine to read an opt config list of properties (ID and string only)
 *
 * know the first token has been read and reads ending }
 * builds (adds to) a work opt cfg list - caller handling linking it in
 */  
static int32 rd_optcfg_prop_list(struct oc_vtok_t **ocvtok_hdr)
{
 __wrk_ocvtok_hd = __wrk_ocvtok_end = NULL;
 if (__toktyp != LCB) 
  {
   __pv_ferr(4847,
    "-optconfigfile properties list begin set bracket expected - %s read",
    __prt_vtok());
   return(FALSE);
  }
 for (;;) 
  {
   __toktyp = __get1_vtok(__in_s);
   if (__toktyp != ID && __toktyp != LITSTR)
    {
     __pv_ferr(4866,
      "-optconfigfile attribute (property) list element expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   if (!rd_optcfg_1prop()) return(FALSE);
   if (__toktyp == RCB) break;
   /* DBG remove -- */ 
   if (__toktyp != COMMA) __misc_terr(__FILE__, __LINE__);
   /* --- */
  }
 *ocvtok_hdr = __wrk_ocvtok_hd;
 __wrk_ocvtok_hd = __wrk_ocvtok_end = NULL;
 return(TRUE);
}

/*
 * routine to read one verilog property token - either ID or string
 *
 * know the first ID has been read and reads ending , or }
 * builds (adds to) a work opt cfg list - caller handling linking it in
 */  
static int32 rd_optcfg_1prop(void)
{
 int32 el_ttyp, el_lcnt;
 char namstr[IDLEN];

 /* DBG remove -- */
 if (__toktyp != ID && __toktyp != LITSTR) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (__toktyp == ID) strcpy(namstr, __token);
 else strcpy(namstr, __strtoken);
 el_ttyp = ID;
 el_lcnt = __lin_cnt;
 __toktyp = __get1_vtok(__in_s);
 if (__toktyp == RCB || __toktyp == COMMA)
  {
   /* SJM 04-14-13 - need to see if toggle property {toggle_cover} used */
   /* may actually not have any toggles but if possible set for warn */
   if (strcmp(namstr, "cover_toggle") == 0) __has_tgl_optcfg_stmt = TRUE;

   add_octok_toend(el_ttyp,  el_lcnt, namstr);
   return(TRUE);
  }
 __pv_ferr(4866,
  "-optconfigfile attribute (property) %s followed by illegal token %s",
  namstr,  __prt_vtok());
 return(FALSE);
}

/*
 * add one token to end of global work opt cfg list 
 */
static void add_octok_toend(int32 ttyp, int32 lcnt, char *toknam)
{
 struct oc_vtok_t *ocvtokp;
 
 ocvtokp = (struct oc_vtok_t *) __my_malloc(sizeof(struct oc_vtok_t)); 
 ocvtokp->ocs_toctyp = ttyp;
 ocvtokp->ebi1 = -1;
 ocvtokp->ebi2 = -1;
 ocvtokp->tok_lcnt = lcnt;
 ocvtokp->ocs_toknam = __pv_stralloc(toknam);
 ocvtokp->ocvtnxt = NULL;
 if (__wrk_ocvtok_end == NULL) __wrk_ocvtok_hd = __wrk_ocvtok_end = ocvtokp;
 else
  {
   __wrk_ocvtok_end->ocvtnxt = ocvtokp;
   __wrk_ocvtok_end = ocvtokp;
  }
}

/*
 * simple skip to semi for reading opt config file (no ver src stuff)
 */
static int32 optcfg_skipto_semi(void)
{

 for (;;)
  {
   if (__toktyp == SEMI) return(TRUE);
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to opt config file semicolon");
   __toktyp = __get1_vtok(__in_s);
  }
 return(FALSE);
}

/*
 * DBG routine to dump design's optconfig file statements lists
 */
static void dmp_dsgn_optcfgs(void)
{
 struct ocfil_lst_t *ocfnp;
 struct ocfg_stmt_t *ocstmtp;
 char s1[RECLEN], s2[RECLEN];

 for (ocfnp = __optcfg_fils; ocfnp != NULL; ocfnp = ocfnp->oclnxt)
  {
   __dbg_msg(".. dumping -optconfigfile %s\n", ocfnp->ocfnam);
   for (ocstmtp = ocfnp->oc_stmts; ocstmtp != NULL; ocstmtp = ocstmtp->ocsnxt) 
    {
     switch (ocstmtp->ocfgtyp) {
      case OCFG_MOD:
        dbg_bld_ver_item_list_str(s1, ocstmtp->oc_ver_objs);
        dbg_bld_ver_item_list_str(s2, ocstmtp->oc_props);
       __dbg_msg("module {%s} {%s};\n", s1, s2); 
       break;
      case OCFG_EXL_MOD:
        dbg_bld_ver_item_list_str(s1, ocstmtp->oc_ver_objs);
        dbg_bld_ver_item_list_str(s2, ocstmtp->oc_props);
       __dbg_msg("module_exclude {%s} {%s};\n", s1, s2); 
       break;
      case OCFG_INST:
        dbg_bld_ver_item_list_str(s1, ocstmtp->oc_ver_objs);
        dbg_bld_ver_item_list_str(s2, ocstmtp->oc_props);
       __dbg_msg("instance {%s} {%s};\n", s1, s2); 
       break;
      case OCFG_EXL_INST:
        dbg_bld_ver_item_list_str(s1, ocstmtp->oc_ver_objs);
        dbg_bld_ver_item_list_str(s2, ocstmtp->oc_props);
       __dbg_msg("instance_exclude {%s} {%s};\n", s1, s2); 
       break;
      case OCFG_TREE:
       dbg_bld_ver_item_list_str(s1, ocstmtp->oc_ver_objs);
       dbg_bld_ver_item_list_str(s2, ocstmtp->oc_props);
       __dbg_msg("tree (%d) {%s} {%s};\n", ocstmtp->tree_level_val, s1, s2); 
       break;
      case OCFG_EXL_TREE:
       dbg_bld_ver_item_list_str(s1, ocstmtp->oc_ver_objs);
       dbg_bld_ver_item_list_str(s2, ocstmtp->oc_props);
       __dbg_msg("tree_exclude (%d) {%s} {%s};\n", ocstmtp->tree_level_val, 
         s1, s2); 
       break;
      default: __case_terr(__FILE__, __LINE__);
      }
     __dbg_msg("\n");
    }
  }
}

/*
 * dbg proc to build a mod ver items list (module, inst, or XMR) into a string
 * caller emits the surring {}
 */
static char *dbg_bld_ver_item_list_str(char *s, struct oc_vtok_t *ocvtp_hd)
{
 int32 first_time;
 struct oc_vtok_t *ocvtp;
 char s1[RECLEN];

 first_time = TRUE;
 strcpy(s, "");
 for (ocvtp = ocvtp_hd; ocvtp != NULL; ocvtp = ocvtp->ocvtnxt)
  {
   if (first_time) first_time = FALSE;
   else strcat(s, ", ");
   sprintf(s1, "%s<%d>", ocvtp->ocs_toknam, ocvtp->ocs_toctyp);
   strcat(s, s1);
  }
 return(s);
}

/*
 * ROUTINES TO SET TOGGLE BITS FROM OPTCFGFIL STATEMENTS
 */

/*
 * wrapper that handles all set up both from options and optcfg file
 * stmts and properties
 *
 * this is called near end of v prp
 * need this even if no opt cfg files but toggle options used 
 */
extern void __rd_setup_optcfg(void)
{
 /* SJM 05-01-13 - need to initialize toggle state if -toggle flat used */
 /* new algorithm allows 2 approaches - use -toggle to turn on all then turn */
 /* or only turn on/off with optconfig {cover_toggle} stmts */
 if (__toggle_coverage)
  {
   turn_on_design_wide_tgl_coverage();
  }

 /* process the saved opt cfg fil statements with properties */
 set_optcfg_bits_from_optcfgfils();

 /* done processing optconfig and set up from program options, if has */
 /* toggle need to set per itree loc bits - this checks and may turn */
 /* off toggle recording if no nets have any tgl recording bits */

 /* SJM 05-01-13 - after setting tgl coverage recording/reporting d.s */
 /* need to go through analyze and update/check final cover recording state */ 
 /* lots of turning on and off possible */
 if (__has_tgl_optcfg_stmt)
  {
   set_dsgn_tgl_cover_state(); 
  }
}


/*
 * set toggle bits in nearly finished prep net list
 *
 * can only call this during late prep stage because need to fill in
 * built n.l. d.s. 
 *
 * here syntax must be good or error that stop simulation
 *
 * NOTICE - always called even if no toggle option or optcfg tgl stmts so
 * may do nothing 
 *
 * NOTICE - if multiple properties in list, may have multiple bits set
 */
static void set_optcfg_bits_from_optcfgfils(void)
{
 int32 ii, sav_lcnt, oc_mask, lev, is_exclude, ri1, ri2, biti;
 struct ocfil_lst_t *ocfnp;
 struct ocfg_stmt_t *ocstmtp;
 struct oc_vtok_t *ocvtp;
 struct sy_t *syp, *tailsyp;
 struct mod_t *mdp;
 struct itree_t *itp;
 struct inst_t *ip;
 struct net_t *np;
 struct expr_t *glbndp, *gcmp_ndp;
 char *chp, sav_curfnam[RECLEN], errstr[RECLEN];

 /* may have to reinit the pli module bit set */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   mdp->m_opt_pli_bits_set = FALSE;
  }
 strcpy(sav_curfnam, __cur_fnam);
 sav_lcnt = __lin_cnt;
 for (ocfnp = __optcfg_fils; ocfnp != NULL; ocfnp = ocfnp->oclnxt)
  {
   /* AIV 10/24/11 - this needs point to not copy */
   __cur_fnam = ocfnp->ocfnam;
   for (ocstmtp = ocfnp->oc_stmts; ocstmtp != NULL; ocstmtp = ocstmtp->ocsnxt) 
    {
     if ((oc_mask = __get_optcfg_prop_typ(ocstmtp)) == 0) continue;

     for (ocvtp = ocstmtp->oc_ver_objs; ocvtp != NULL; ocvtp = ocvtp->ocvtnxt) 
      {
       __lin_cnt = ocvtp->tok_lcnt;
       /* each stmt may or may not be exclude */
       is_exclude = FALSE;
       switch (ocstmtp->ocfgtyp) {
        case OCFG_EXL_MOD:
         is_exclude = TRUE;
        /*FALLTHRU */
        case OCFG_MOD:
         syp = __get_sym(ocvtp->ocs_toknam, __modsyms);
         if (syp == NULL || syp->sytyp != SYM_M)
          {
           __pv_ferr(4868,
            "-optconfigfile module statement - %s not a design module",
            ocvtp->ocs_toknam);
           continue;
          }
really_mod_form:
         strcpy(__cur_optcfg_cntxt_str, "module statement");
         mdp = syp->el.emdp;
/* DBG remove -- */
         if (__debug_flg)
          {
           __dbg_msg("<<<+++ setting properties in module %s at %s)\n",
            mdp->msym->synam, __bld_lineloc(__xs, mdp->msym->syfnam_ind,
            mdp->msym->sylin_cnt));
          }
/* --- */
         if ((oc_mask & OCPRP_TGL) != 0) 
          {
           if (ocvtp->ebi1 != -1) __misc_terr(__FILE__, __LINE__);
           if (is_exclude) turn_off_1mod_tgl_coverage(mdp);
           else turn_on_1mod_tgl_coverage(mdp);
          }
         if ((oc_mask & OCPRP_EVENT) != 0) 
          {
           set_event_cover_bits(mdp, NULL, is_exclude);    
          }
         if ((oc_mask & OCPRP_STMT) != 0) 
          {
           set_stmt_cover_bits(mdp, NULL, is_exclude);
          }
         if ((oc_mask & OCPRP_ACC_RW) != 0) 
          {
           set_plitab_acc(1, mdp, NULL, NULL, is_exclude);
          }
//AIV? 10-17-10 - LOOKATME - why have +acc+3+ and +acc+4?
         if ((oc_mask & OCPRP_ACC_CBK) != 0
          || (oc_mask & OCPRP_ACC_ANNPD) != 0
          || (oc_mask & OCPRP_ACC_ANNGD) != 0)
           {
            set_plitab_acc(2, mdp, NULL, NULL, is_exclude);
           }
#ifdef __XPROP__
         /* SJM 11-03-11 - for now only xprop and xprop2 - will have more */
         /* AIV 02/27/12 - this was supposed to be xprop2 - had two xprops */
         if ((oc_mask & OCPRP_XPROP) != 0 || (oc_mask & OCPRP_XPROP2) != 0 ||
          (oc_mask & OCPRP_XPROP_AND_OR_X) != 0)
          {
           set_xprop_bits(mdp, NULL, is_exclude, oc_mask);
          }
#endif
         break;
        case OCFG_EXL_TREE:
         is_exclude = TRUE;
         /*FALLTHRU */
        case OCFG_TREE:
         strcpy(__cur_optcfg_cntxt_str, "tree statement");

         /* SJM 06-12-13 - need to use same values as dumpvars but here */
         /* -1 is all underneath while for dumpvars it is 0, always use */
         /* 0 for both internally here */
         if (ocstmtp->tree_level_val == -1) lev = 0;
         else if (ocstmtp->tree_level_val == 0)
          {
           __pv_ferr(4869,
            "-optconfigfile tree statement %s number of subtree levels 0 illegal - means no levels - nothing to do",
            ocvtp->ocs_toknam);
           continue;
          }
         else lev = ocstmtp->tree_level_val;

         /* SJM 04-30-13 - NOTICE can not use find optcfg xmr object here */ 
         /* because arg may be simple not root module name */

         /* tree here can be module name which means all itree under */
         /* every inst of mod or XMR path */
         if ((glbndp = __glbnam_to_expr(ocvtp->ocs_toknam)) == NULL)
          {
           __pv_ferr(4868,
             "-optconfigfile tree statement llegal hierarchical path %s",
            ocvtp->ocs_toknam);
           continue;
          }
         /* if only one component since rooted will be module but does */
         /* not need to be top level */
         gcmp_ndp = glbndp->ru.x;
         /* know top level rooted first component never indexed */
         chp = __to_glbcmp_nam(gcmp_ndp);
         /* each element lu of comma element */
         if (glbndp->ru.x->ru.x == NULL)
          {
           /* case 1: module name - need to turn on/off toggle coverager */ 
           /* for each tree under every inst of mod */
           syp = __get_sym(chp, __modsyms);
           __free_xtree(glbndp);
           
           if (syp == NULL || syp->sytyp != SYM_M)
            {
             __pv_ferr(4868,
              "-optconfigfile tree statement module name form - %s not a design module",
              chp);
             continue;
            } 
           mdp = syp->el.emdp;
           if (ocstmtp->tree_level_val == 0) goto really_mod_form;

           /* DBG remove -- */
           if (__debug_flg)
            {
             __dbg_msg(
             ">>>--- setting properties from tree mod %s (%s) form %d levels\n",
              mdp->msym->synam, __bld_lineloc(__xs, mdp->msym->syfnam_ind,
              mdp->msym->sylin_cnt), lev);
            }
           /* --- */

           if ((oc_mask & OCPRP_TGL) != 0) 
            {
             /* for net tgl module form, need all itrees under still */
             /* but once process all insts of mod revert to only itree form */
             for (ii = 0; ii <  mdp->flatinum; ii++)
              {
               itp = mdp->moditps[ii];
               set_tgl_1subtree_coverage(itp, lev, oc_mask, is_exclude);
              }
            }
           else
            {
             set_other_than_tgl_1subtree_coverage(mdp, lev, oc_mask,
              is_exclude);
            }  
           break;
          }
         /* case 2: XMR to one itree loc (inst) */ 
         /* SJM 04-30-13 - LOOKATME? notice tail syp here can be gate or */
         /* maybe other sym type - must check */ 
         itp = get_optcfg_down_itp(glbndp, &(tailsyp), errstr);
         __free_xtree(glbndp);
         if (itp == NULL)
          { 
           __pv_ferr(4909,
            "-optconfigfile tree statement hierarchical ref %s illegal because %s",
            ocvtp->ocs_toknam, errstr);
           continue;
          }
         /* tree can not end with net */
         if (tailsyp->sytyp != SYM_I)
          { 
           __pv_ferr(4903,
            "-optconfigfile tree statement hierarchical ref %s instance form ends with %s symbol - instance required",
            ocvtp->ocs_toknam, __to_sytyp(__xs, tailsyp->sytyp));
           continue;     
          }
         /* DBG remove -- */
         if (__debug_flg)
          {
           mdp = itp->itip->imsym->el.emdp;
            __dbg_msg(
             ">>>--- setting properties from tree inst %s form mod typ %s %d levels\n",
            __msg2_blditree(__xs, itp), __to_sytyp(__xs, tailsyp->sytyp), lev);
          }
         /* --- */
         if ((oc_mask & OCPRP_TGL) != 0) 
          {
           set_tgl_1subtree_coverage(itp, lev, oc_mask, is_exclude);
          }
         else
          {
           mdp = itp->itip->imsym->el.emdp;
           set_other_than_tgl_1subtree_coverage(mdp, lev, oc_mask, is_exclude);
          }  
         break;
        case OCFG_EXL_INST:
         is_exclude = TRUE;
         /*FALLTHRU */
        case OCFG_INST:
         ip = NULL;
         /* SJM 04-26-13 - for opt config inst form either itree loc */
         /* or net in itree */
         if ((glbndp = __glbnam_to_expr(ocvtp->ocs_toknam)) == NULL)
          {
           __pv_ferr(4907,
            "-optconfigfile instance statement heirarchical path %s illegal",
            ocvtp->ocs_toknam);
           continue;
          }
         /* SJM 04-27-13 - LOOKATME - is this the right proc? */
         /* should it be find optcfg xmr object? */
         /* if error returns nil, this proc emits the error message */
         tailsyp = find_optcfg_xmr_object(ocvtp, &(itp));
         if (tailsyp == NULL) continue;

         mdp = itp->itip->imsym->el.emdp;
         if (tailsyp->sytyp == SYM_N)
          {
           strcpy(__cur_optcfg_cntxt_str, "instance net statement");

           /* handle 1 net inst form optconfig file stmt as special */
           /* because really one net in on inst */
           np = tailsyp->el.enp;
           if ((oc_mask & OCPRP_TGL) != 0) 
            {  
             /* SJM 06-13-13 - cvrt to normalized h:0 - if already no chg */ 
             /* can't do it until here when know net */ 
             if (ocvtp->ebi1 != -1)
              {
               /* DBG remove -- */
               if (ocvtp->ebi2 == -1) __misc_terr(__FILE__, __LINE__);
               /* -- */
               /* can do both - still works for bsel where equal */ 
               __getwir_range(np, &ri1, &ri2);
               biti = normalize_ndx_(ocvtp->ebi1, ri1, ri2);
               ocvtp->ebi1 = biti;
               biti = normalize_ndx_(ocvtp->ebi2, ri1, ri2);
               ocvtp->ebi2 = biti;
              }
             else
              {
               /* DBG remove -- */
               if (ocvtp->ebi2 != -1) __misc_terr(__FILE__, __LINE__);
               /* -- */
              }

             /* set toggle property for the one net */
             /* SJM 05-03-13 - handle tgl cover as special case net and inst */
             if (is_exclude)
              { 
               if (!np->n_has_toggle)
                {
#ifndef __CVC_RT__
                 __pv_fwarn(4354,
                  "-optconfigfile net %s instance %s form - can not turn toggle off - no inst of net has toggle on",
                  np->nsym->synam, __msg2_blditree(__xs, itp));
#endif
                 continue;
                }
               turn_off_1inst_net_tgl_coverage(itp, np, ocvtp->ebi1,
                ocvtp->ebi2, TRUE);
              }
             else
              {
               if (np->n_isarr || np->ntyp == N_REAL || np->ntyp == N_EVENT)
                {
#ifndef __CVC_RT__
                 __pv_fwarn(4356,
                   "-optconfigfile net %s instance %s form - can not turn toggle on - no toogle coverage for arrays or reals",
                  np->nsym->synam, __msg2_blditree(__xs, itp));
#endif
                 continue;
                }

               try_turn_on_1inst_net_tgl_coverage(itp, np, ocvtp->ebi1,
                ocvtp->ebi2);
               /* SJM 05-01-13 - if inst include for net that can not */
               /* have toggle coverage - emit warning */
               /* SJM 06-13-13 - notice msg only for one net form */
               if (!np->n_has_toggle)
                {
                 if (np->n_isarr) strcpy(errstr, "is an array");
                 else if (np->ntyp == N_REAL) strcpy(errstr, "is a real");
                 else if (np->ntyp == N_EVENT)
                  {
                   strcpy(errstr, "is an event - use event coverage");
                  }
                 else __case_terr(__FILE__, __LINE__);

#ifndef __CVC_RT__
                 __pv_fwarn(4359, "-optconfigfile net %s instance %s form - can not turn toggle on because %s",
                  np->nsym->synam, __msg2_blditree(__xs, itp), errstr);
#endif
                }
              }
            }
           /* ip needed below other properties take insts not itree locs */
           ip = itp->itip;
          }
         else if (tailsyp->sytyp == SYM_I)
          { 
           strcpy(__cur_optcfg_cntxt_str, "instance statement");
           /* tgl cover is special case - still need others below */
           if (is_exclude) turn_off_1inst_allnets_tgl_coverage(itp, TRUE);
           else turn_on_1inst_allnets_tgl_coverage(itp);
           ip = tailsyp->el.eip; 
           np  = NULL; 
          }
         else
          {
           /* this can be wrong other symbol types such as gate */
           __pv_ferr(4904,
            "-optconfigfile statement instance form heirarchical path %s ends with illegal symbol %s type %s - only instance or net allowed",
            ocvtp->ocs_toknam, tailsyp->synam,
             __to_sytyp(__xs, tailsyp->sytyp));
           /* just needed for lint */
           ip = NULL;
           continue;
          }
         /* SJM 05-04-13 - notice that one statement can have many cfg */
         /* properties - separated and processed tgl above - others possible */
         if ((oc_mask & OCPRP_EVENT) != 0) 
          set_event_cover_bits(mdp, ip, is_exclude);    
         if ((oc_mask & OCPRP_STMT) != 0) 
           set_stmt_cover_bits(mdp, ip, is_exclude);
         /* SJM 12-17-10 - pli.tab not right - just using opt cfg prop */ 
         if ((oc_mask & OCPRP_ACC_RW) != 0) 
          set_plitab_acc(1, mdp, ip, np, is_exclude);
         if ((oc_mask & OCPRP_ACC_CBK) != 0
          || (oc_mask & OCPRP_ACC_ANNPD) != 0
          || (oc_mask & OCPRP_ACC_ANNGD) != 0)
          {
           set_plitab_acc(2, mdp, ip, np, is_exclude);
          }
#ifdef __XPROP__
         /* AIV 02/27/12 - need to set xprop bits here as well */
         if ((oc_mask & OCPRP_XPROP) != 0 || (oc_mask & OCPRP_XPROP2) != 0 ||
          (oc_mask & OCPRP_XPROP_AND_OR_X) != 0)
          {
           set_xprop_bits(mdp, ip, is_exclude, oc_mask);
          }
#endif
       }
      } 
    }
  }
 /* AIV 11/29/11 - if strcpy back is larger this has memory issue */
 /* just alloc new string */
 __cur_fnam = __pv_stralloc(sav_curfnam);
 __lin_cnt = sav_lcnt;
}

/*
 * find tail of XMR reference string and return last path component symbol
 * this will find either an inst sym or a net sym
 *
 * SJM 04-30-13 - on error returns nil, if returns non nil sym then know
 * itp set
 * SJM 04-30-13 - removed any inst ref from here - know uses real itree
 *
 * SJM 12-16-10 - if object is net (end of path) also returns inst in
 *
 * know opt cfg token is from either instance or tree stmt type 
 *
 * SJM 12-14-10 - do not need context since symbol finds inst - all
 * hierarichal reference are rooted
 */
static struct sy_t *find_optcfg_xmr_object(struct oc_vtok_t *ocvtp,
 struct itree_t **ret_itp)
{
 struct expr_t *glbndp;
 struct itree_t *itp;
 struct sy_t *tailsyp;
 char s1[RECLEN]; 

 *ret_itp = NULL;
 /* this will not alloc an expr if nil returned */
 if ((glbndp = __glbnam_to_expr(ocvtp->ocs_toknam)) == NULL)
  {
   __pv_ferr(4868,
     "-optconfigfile statement hierarchical path name %s illegal",
    ocvtp->ocs_toknam);
   return(NULL);
  }

 /* SJM 03-22-13 - using proc originally from SDF that uses build inst tree */
 /* during v prp processing to set -optconfigfile properties */
 /* really another kind of annotation, but here only rooted allowed */

 /* parse -optconfigfile inst or tree name into itree context then */
 /* depending on -optconfigfile stmt type construct itree or inst or net */
 /* SJM 03-22-13 - proc emits error for non inst path end */
 /* SJM 04-14-13 - context itp nil means require rooted, if ret nil err */
 /* sets s1 with error string */ 
 itp = get_optcfg_down_itp(glbndp, &(tailsyp), s1);
 __free_xtree(glbndp);
 if (itp == NULL)
  {
   __pv_ferr(4871,
     "-optconfigfile statement hierarchical path %s illegal because %s",
    ocvtp->ocs_toknam, s1);
   return(NULL);
  }
 /* case 1: -optconfigfile stmt path ends with inst */
 if (tailsyp == NULL)
  {
   tailsyp = itp->itip->isym;
   /* DBG remove -- */
   if (tailsyp->sytyp != SYM_I) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* here tailsyp is inst same as ret ip, if path ends with inst */

   *ret_itp = itp;
   return(tailsyp);
  }
 /* case 2: -optconfigfile stmt path ends with net */
 if (tailsyp->sytyp != SYM_N)
  {
   __pv_ferr(4873,
    "-optconfigfile statement rooted hierarchical path end %s type %s - must be either instance or net", 
    tailsyp->synam, __to_sytyp(__xs, tailsyp->sytyp));
   return(NULL);
  }
 *ret_itp = itp;
 return(tailsyp);
}

/*
 * get a known rooted down itp and return it - if ends with inst.
 * if path ends with inst sets tail syp to nil else to ptr to ending
 *
 * if end sym is inst, sets tailsyp to point to nil
 * if end sym is net or gate (caller must check for expected) sets
 * tail syp to point to the ending symbol
 *
 * SJM 04-30-13 - this proc does not emit error messages but returns nil
 * and sets passed errmsg string - caller much emit the error message
 *
 * end sym can be gate, caller must check for handle (emit err?)
 * since opt cfg does not have any gate config statements (yet?)
 */
static struct itree_t *get_optcfg_down_itp(struct expr_t *glbndp,
 struct sy_t **tailsyp, char *errmsg) 
{
 int32 ii;
 byte *bp1, *bp2;
 struct expr_t *gcmp_ndp;
 struct itree_t *itp;
 struct mod_t *mdp;
 struct sy_t *isyp, *arr_isyp;
 struct inst_t *ip;
 char *chp, s1[RECLEN];

 /* DBG remove -- */
 if (tailsyp == NULL) __misc_terr(__FILE__, __LINE__); 
 /* -- */
 strcpy(errmsg, "");
 *tailsyp = NULL;

 gcmp_ndp = glbndp->ru.x;
 /* know top level rooted first component never indexed */
 chp = __to_glbcmp_nam(gcmp_ndp);
 if ((ii = __ip_indsrch(chp)) == -1)
  {
   strcpy(errmsg, "root undefined");
   return(NULL);
  }
 itp = __it_roots[ii];
 gcmp_ndp = gcmp_ndp->ru.x;

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
     if (gcmp_ndp->ru.x != NULL)
      {
       strcpy(errmsg, "non-scope symbol inside path");
       return(NULL);
      }
     /* here tailsyp - an in mod sym, for -optconfigfile must be net */
     /* caller checks */
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
 /* path ends with instance */
 return(itp);
}

/*
 * set one subtree coverage for toggle which is per inst - namely only
 *
 * insts underneath set - other insts of mods underneath not effected
 *
 * SJM 06-13-13 - now internal level 0 is all level 1 is just current
 * and do not descend
 */
static void set_tgl_1subtree_coverage(struct itree_t *itp, int32 level,
 int32 oc_mask, int32 is_excld)
{
 int32 ii;
 struct mod_t *mdp;
 struct itree_t *down_itp; 

 if (is_excld) turn_off_1inst_allnets_tgl_coverage(itp, TRUE);
 else turn_on_1inst_allnets_tgl_coverage(itp);

 if (level == 1) return; 

 /* descend for every inst in current inst */ 
 mdp = itp->itip->imsym->el.emdp;
 for (ii = 0; ii < mdp->minum; ii++)
  { 
   down_itp = &(itp->in_its[ii]);
/* DBG remove -- */
   if (__debug_flg)
    {
     __dbg_msg(">>>--- tree level %d adding inst %s\n",
      level, __msg2_blditree(__xs, down_itp));
    }
/* --- */
   set_tgl_1subtree_coverage(down_itp, (level != 0) ? level - 1 : 0,
    oc_mask, is_excld);
  }
}

/*
 * set optconfig file proprties for subtree of modules, i.e. all module
 * instance for any inst of modules and all insts underneath - that
 * is current semantics for everything optcfg property except tgl coverage
 *
 * SJM 04-27-13 - other state changes don't need this algorithm, but
 * plitab does
 */
static void set_other_than_tgl_1subtree_coverage(struct mod_t *mdp,
 int32 level, int32 oc_mask, int32 is_excld)
{
 int32 ii;
 struct itree_t *down_itp, *itp; 
 struct mod_t *down_mdp; 

 /* DBG remove -- */
 if ((oc_mask & OCPRP_TGL) != 0) __misc_terr(__FILE__, __LINE__);
 /* -- */

 if ((oc_mask & OCPRP_EVENT) != 0) set_event_cover_bits(mdp, NULL, is_excld);   
 if ((oc_mask & OCPRP_STMT) != 0) set_stmt_cover_bits(mdp, NULL, is_excld);
 /* SJM 12-17-10 - pli.tab not right - just using opt cfg prop */ 
 if ((oc_mask & OCPRP_ACC_RW) != 0) 
  {
   set_plitab_acc(1, mdp, NULL, NULL, is_excld);
  }
 /* AIV? 10-17-10 - LOOKATME - why have +acc+3+ and +acc+4? */
 if ((oc_mask & OCPRP_ACC_CBK) != 0 || (oc_mask & OCPRP_ACC_ANNPD) != 0
  || (oc_mask & OCPRP_ACC_ANNGD) != 0) 
  {
   set_plitab_acc(2, mdp, NULL, NULL, is_excld);
  }
#ifdef __XPROP__
  /* AIV 02/27/12 - need to set xprop bits here as well */
 if ((oc_mask & OCPRP_XPROP) != 0 || (oc_mask & OCPRP_XPROP2) != 0 ||
  (oc_mask & OCPRP_XPROP_AND_OR_X) != 0)
  {
   set_xprop_bits(mdp, NULL, is_excld, oc_mask);
  }
#endif

 /* SJM 06-13-13 - internally lev 0 all insts below, level 1 no descend */
 if (level == 1) return; 

 itp = mdp->moditps[0];
 for (ii = 0; ii < mdp->minum; ii++)
  { 
   down_itp = &(itp->in_its[ii]);
   down_mdp = down_itp->itip->imsym->el.emdp;
/* DBG remove -- */
   if (__debug_flg)
    {
      __dbg_msg(">>>--- tree level %d adding module %s\n",
        level, down_mdp->msym->synam);
    }
/* --- */
   set_other_than_tgl_1subtree_coverage(down_mdp, (level != 0) ? level - 1 : 0,
    oc_mask, is_excld);
  }
}

/*
 * NEXT 3 ROUTINES ONLY WAY TO TURN ON AND TURN OFF TOGGLE COVERAGE
 */

/*
 *
 * turn on toggle coverage for every net in every module
 *
 * possible to have this from -toggle then later optconfigfil excludes
 * and even followed by includes etc.
 */
static void turn_on_design_wide_tgl_coverage(void)
{
 int32 ni, ii, wlen;
 struct net_t *np;
 struct mod_t *mdp;
 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* SJM 05-01-13 - when turning on toggle for entire design */
   /* also turn on for every mod */
   if (mdp->m_itps_tgl_cover == NULL) alloc_init_m_itps_tgl_cover(mdp);
   /* need to turn on even if alloc since may be excluded to off */
   mdp->m_has_toggle_cover = TRUE;
   for (ii = 0; ii < mdp->flatinum; ii++) 
    {
     mdp->m_itps_tgl_cover[ii] = 1;
    }

   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
    {
     /* SJM 04-26-13 - this must match per inst turn on exclusion */
     /* skip arrays */
     if (np->n_isarr) continue;
     //SJM 10-31-12 - LOOKATME - maybe should support real toggle coverage
     /* skip reals */
     if (np->ntyp == N_REAL) continue;
     /* skip events */
     if (np->ntyp == N_EVENT) continue;

     np->n_has_toggle = TRUE;
     if (np->ntgp == NULL)
      {
       alloc_init_1net_tgl(np, mdp);
      }
     for (ii = 0; ii < mdp->flatinum; ii++) 
      {
       np->ntgp->peri_tgl_on[ii] = 1;
      }
     /* zero (mark not excluded) all peribits tgl rpt exclude bits */
     /* when bits are excluded, value is 1 */
     wlen = wlen_(mdp->flatinum*np->nwid);
     memset(np->ntgp->peribits_tgl_rpt_exclude, 0x00, WRDBYTES*wlen);
    }
  } 
}

/*
 * alloc and initialize mod's itp cover per inst byte tab if not already
 * alloc and
 *
 * SJM 05-04-13 - need to initialize to 0 non for all then set to 1 if
 * included and set to 0 if excluded
 */
static void alloc_init_m_itps_tgl_cover(struct mod_t *mdp)
{
  {
   mdp->m_itps_tgl_cover = (byte *) __my_malloc(mdp->flatinum);
   memset(mdp->m_itps_tgl_cover, 0, mdp->flatinum);
  }
}

/*
 * turn on toggle coverage for one mod all insts
 *
 * SJM 04-27-13 - notice turn on entire design separate since faster to do
 * all at once
 *
 * SJM 05-02-13 - can turn on multiple times because maybe partially on 
 */
static void turn_on_1mod_tgl_coverage(struct mod_t *mdp)
{
 int ii;
 struct itree_t *itp;

 if (mdp->m_itps_tgl_cover == NULL) alloc_init_m_itps_tgl_cover(mdp);
 /* SJM 05-03-13 - turn on inst turn on per inst mod itps */ 
 /* the m itps flags turned on when inst all nets turned on */
 mdp->m_has_toggle_cover = TRUE;

 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   itp = mdp->moditps[ii];
   turn_on_1inst_allnets_tgl_coverage(itp);
  }
}

/*
 * turn off toggle coverage for one mod all insts always entire nets
 */
static void turn_off_1mod_tgl_coverage(struct mod_t *mdp)
{
 int ii;
 struct itree_t *itp;

 if (!mdp->m_has_toggle_cover)
  {
#ifndef __CVC_RT__
   __pv_fwarn(4359,
    "-optconfigfile %s exclude all instance of module %s impossible - no module toggle coverage on", 
    __cur_optcfg_cntxt_str, mdp->msym->synam);
#endif
   return;
  } 

 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   itp = mdp->moditps[ii];
   /* this turns off mod's itp per inst coverage bytes */
   turn_off_1inst_allnets_tgl_coverage(itp, FALSE);
  }
 /* SJM 05-04-13 - do not free mod itps tgl cover on - only final */
 /* set state can free */
 mdp->m_has_toggle_cover = FALSE;
}

/*
 * turn on toggle coverage for one inst all nets
 *
 * SJM 06-13-13 - for now always need loop since no all on bit in net record
 * since mostly just turn on with selective off can leave
 */
static void turn_on_1inst_allnets_tgl_coverage(struct itree_t *itp)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;

 mdp = itp->itip->imsym->el.emdp;
 /* DBG rmeove -- */
 if (mdp->m_has_toggle_cover && mdp->m_itps_tgl_cover == NULL) 
  {
   __misc_terr(__FILE__, __LINE__);
  }
 /* --- */

 if (mdp->m_itps_tgl_cover == NULL) alloc_init_m_itps_tgl_cover(mdp);
 /* this is mod has some tgl coverage */
 mdp->m_has_toggle_cover = TRUE;
 mdp->m_itps_tgl_cover[itp->itinum] = 1;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   try_turn_on_1inst_net_tgl_coverage(itp, np, -1, -1);
  }
}

/*
 * turn off toggle coverage for one inst all nets
 */
static void turn_off_1inst_allnets_tgl_coverage(struct itree_t *itp,
 int32 emit_warn)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;

 mdp = itp->itip->imsym->el.emdp;
 if (!mdp->m_has_toggle_cover && mdp->m_itps_tgl_cover != NULL)
  {
   __misc_terr(__FILE__, __LINE__);
  }
 /* --- */
 if (emit_warn && !mdp->m_has_toggle_cover)
  {
#ifndef __CVC_RT__
   __pv_fwarn(4359,
    "-optconfigfile %s exclude all nets of inst %s (mod %s) impossible - no module toggle coverage to turn off",
    __cur_optcfg_cntxt_str, __msg2_blditree(__xs, itp), mdp->msym->synam);
#endif
   return;
  }
 if (emit_warn && mdp->m_itps_tgl_cover[itp->itinum] == 0)
  {
#ifndef __CVC_RT__
   __pv_fwarn(4359,
    "-optconfigfile %s exclude all nets of inst %s (mod %s) impossible - toggle coverage not on for inst", 
    __cur_optcfg_cntxt_str, __msg2_blditree(__xs, itp), mdp->msym->synam);
#endif
   return;
  }

 /* DBG remove -- */
 if (mdp->m_itps_tgl_cover == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */

 mdp = itp->itip->imsym->el.emdp;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   /* SJM 11-12-13 - if net does not have tgl (type of var?) can't turn off */
   if (!np->n_has_toggle) continue;

   turn_off_1inst_net_tgl_coverage(itp, np, -1, -1, FALSE);
  }
 /* SJM 05-03-13 - this inst no more tgl coverage - off mod byte tab val */
 mdp->m_itps_tgl_cover[itp->itinum] = 0;
}

/*
 * turn on toggle coverage for all bits of one net for one inst
 * range is already normalized to h:0 stored form not declared rng
 *
 * SJM 02-16-13 - may be already on 
 *
 * SJM 01-22-13 - array vectors (n isarr_vector) are still wires and
 * need toggle coverage - name prints write for the wire in the agregated
 * wire bits
 */
static void try_turn_on_1inst_net_tgl_coverage(struct itree_t *itp,
 struct net_t *np, int32 r1, int32 r2)
{
 int32 bi, base;
 struct mod_t *mdp;

 /* skip arrays */
 if (np->n_isarr) return;
//SJM 10-31-12 - LOOKATME - maybe should support real toggle coverage
 /* skip reals */
 if (np->ntyp == N_REAL) return;
 /* skip events */
 if (np->ntyp == N_EVENT) return;

 mdp = itp->itip->imsym->el.emdp;

 /* turn on mod's inst of net in tgl cover - if not alloc, alloc init */ 
 if (mdp->m_itps_tgl_cover == NULL) alloc_init_m_itps_tgl_cover(mdp);
 /* SJM 06-02-13 - some bits may already be on so this will be on (1) */
 /* does not hurt to turn on again */
 mdp->m_itps_tgl_cover[itp->itinum] = 1;

 /* if first time any bits of any insts of this net, alloc init the tgl rec */
 if (np->ntgp == NULL)
  {
   alloc_init_1net_tgl(np, itp->itip->imsym->el.emdp);
  }

 /* SJM 06-02-13 - some bits may already be on so this will be on (1) */
 /* does not hurt to turn on again */
 np->ntgp->peri_tgl_on[itp->itinum] = 1;
 np->n_has_toggle = TRUE;

 if (r1 == -1) { r1 = np->nwid - 1; r2 = 0; }
 base = itp->itinum*np->nwid;
 for (bi = r1; bi >= r2; bi--)
  {
   /* 1 is off (excluded) bit so set to 0 */
   /* SJM 06-13-13 need lhs bsel because packed to the bit */
   __lhsbsel(np->ntgp->peribits_tgl_rpt_exclude, base + bi, 0);
  }
}

/*
 * turn off tgl coverage for one inst net some range (maybe entire net)
 */
static void turn_off_1inst_net_tgl_coverage(struct itree_t *itp,
 struct net_t *np, int32 r1, int32 r2, int32 emit_warn)
{
 int32 bi, base, bval, off_all_bits;
 struct mod_t *mdp;

 /* DBG remove -- */
 if (!np->n_has_toggle) __misc_terr(__FILE__, __LINE__);
 if (np->ntgp == NULL) __misc_terr(__FILE__, __LINE__);
 if (np->ntgp->peribits_tgl_rpt_exclude == NULL)
  __misc_terr(__FILE__, __LINE__);
 /* -- */

 off_all_bits = FALSE;
 mdp = itp->itip->imsym->el.emdp;
 if (emit_warn && (!np->n_has_toggle
  || np->ntgp->peri_tgl_on[itp->itinum] == 0))
  {
#ifndef __CVC_RT__
   __pv_fwarn(4359,
    "-optconfigfile %s exclude net %s inst %s (mod %s) impossible - toggle coverage not on for this inst of net",
    __cur_optcfg_cntxt_str, np->nsym->synam, __msg2_blditree(__xs, itp),
    mdp->msym->synam);
#endif
   return;
  }

 /* SJM 05-03-13 - since only 1 net, can not chg mod's per itp */
 if (r1 == -1) off_all_bits = TRUE;
 base = itp->itinum*np->nwid;
 if (r1 == -1) { r1 = np->nwid - 1; r2 = 0; }
 /* turn off bits by setting to 1 */
 for (bi = r1; bi >= r2; bi--)
  {
   /* off is 1 */
   __lhsbsel(np->ntgp->peribits_tgl_rpt_exclude, base + bi, 1);
  }
 /* SJM 06-02-13 - was wrong - was always turning off this net/inst record */
 /* only turn off this net, this inst recording if all bits excluded */
 if (off_all_bits)
  {
   /* case 1: all bits excluded - turn of recording for this net/inst */
   np->ntgp->peri_tgl_on[itp->itinum] = 0;
   return;
  }
 /* case 2: excluded some bits - see if now all excluded */ 
 for (bi = 0; bi < np->nwid; bi++)
  {
   bval = rhsbsel_(np->ntgp->peribits_tgl_rpt_exclude, base + bi);
   /* off is 1 so if on (0), can't turn off net/inst toggle record */
   if (bval != 1) return;
  }
 /* SJM 06-12-13 - if all bits 1 (all off), then mark this inst of net off */
 /* i.e. no need to record this net inst, if any bits on record entire */
 /* net and mask when concise report is written */
 np->ntgp->peri_tgl_on[itp->itinum] = 0;
}

/*
 * alloc and init net's toggle record
 *
 * SJM 05-02-13 - notice these are not freed except maybe in finall
 * set design tgl state proc
 */
static void alloc_init_1net_tgl(struct net_t *np, struct mod_t *mdp)
{
 int32 wlen;
 struct net_toggle_t *ntglp;

 ntglp = (struct net_toggle_t *) __my_malloc(sizeof(struct net_toggle_t));
 np->ntgp = ntglp;
 ntglp->toggle_ofs = 0;

 /* these are set during prep and drvn const only used in cvr report gen */
 ntglp->n_peri_tgl_on_se_list = NULL;
 ntglp->peribits_drvn_const = NULL;

 /* SJM 04-26-13 - these need to be alloc and set/unset even if all tgl */
 /* when allocated assume none excluded */
 wlen = wlen_(mdp->flatinum*np->nwid);
 ntglp->peribits_tgl_rpt_exclude = (word32 *) __my_malloc(WRDBYTES*wlen);
 /* 1 is excluded, 0 is included */
 memset(ntglp->peribits_tgl_rpt_exclude, 0x00, WRDBYTES*wlen); 

 /* peri tgl off needs to be turned on */
 ntglp->peri_tgl_on = (byte *) __my_malloc(mdp->flatinum);
 memset(ntglp->peri_tgl_on, 0x00, mdp->flatinum);
}

/*
 * free net toggle record for one net
 *
 * SJM 05-02-13 - only used in final update tgl state
 */
static void optcfg_free_1net_tgl_record(struct mod_t *mdp, struct net_t *np)
{
 int32 wlen;

 wlen = wlen_(mdp->flatinum*np->nwid);
 __my_free(np->ntgp->peribits_tgl_rpt_exclude, wlen*WRDBYTES);
 __my_free(np->ntgp->peri_tgl_on, mdp->flatinum);
 __my_free(np->ntgp, sizeof(struct net_toggle_t));
 np->ntgp = NULL;
}


/*
 * alloc and set per inst (tree loc) in mod inst has some tgl coverage
 * bits - if no toggle cover
 */
static void set_dsgn_tgl_cover_state(void) 
{
 int32 ii, ni, bi, base, bval;
 struct mod_t *mdp;
 struct net_t *np;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* step 1: try to turn off net coverage for every net if all instances */ 
   /* ordered transaction processing - see if can simplify */
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     if (!np->n_has_toggle)
      {
       if (np->ntgp != NULL) __misc_terr(__FILE__, __LINE__);
       continue;
      } 

     /* DBG remove -- */
     if (np->ntgp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       if (np->ntgp->peri_tgl_on[ii] == 1)
        { 
         if (!np->n_has_tglbits_excl) try_set_net_excl_bit(np, ii);
         goto tgl_cover_on_1inst_of_net;
        }

       /* also possible for all bits of this inst turned off, if so */
       /* adjust and count as no tgl coverage for inst */
       base = ii*np->nwid;
       for (bi = np->nwid - 1; bi >= 0; bi--)
        {
         /* bit excluded (off) i bit val 1 */
         bval = rhsbsel_(np->ntgp->peribits_tgl_rpt_exclude, base + bi);
         if (bval == 0)
          {
           if (!np->n_has_tglbits_excl) try_set_net_excl_bit(np, ii);
           goto tgl_cover_on_1inst_of_net;
          }
        }
       /* all bits off sonce this inst of net tgl recording off */
       np->ntgp->peri_tgl_on[ii] = 0; 
      } 
     /* this net no longer has any toggle coverage */
/* ==== TOO MANY WARNS SO REMOVED =====
#ifndef __CVC_RT__
     __pv_warn(4359,
      "toggle coverage turned off for net %s (in mod %s) - all insts excluded",
      np->nsym->synam, mdp->msym->synam);  
#endif
==== */
     /* SJM 05-05-13 - turn off net toggle if not need and free d.s. */
     /* will not alloc nchg which is right */
     optcfg_free_1net_tgl_record(mdp, np);
     np->n_has_toggle = FALSE;
     continue;

tgl_cover_on_1inst_of_net:;
    }
  }

 /* know have final net n tgp structure - if net off flag off and no n tgp */
 /* try to set per net has tgl - only set here needed by report gen */

 /* step 2: try to turn off all coverage for a module */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  { 
   /* tgl coverage already off for this mod, nothing to do */
   if (!mdp->m_has_toggle_cover) continue;

   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     if (mdp->m_itps_tgl_cover[ii] == 1) goto mod_has_some_tgl_cover;
    }
   __my_free(mdp->m_itps_tgl_cover, mdp->flatinum); 
   /* SJM 05-04-13 - LOOKATME - using tab nil for no tgl in mod flag */
   mdp->m_itps_tgl_cover = NULL;
   mdp->m_has_toggle_cover = FALSE;

mod_has_some_tgl_cover:;
  } 

 /* step 3: no toggle turned on after exclude and includes */
 /* now need toggle coverage on - because optcfg tgl set up by now */

 /* SJM 05-05-13 - FIXME toggle coverage var should not be used both */
 /* for turning on all tgl for design and then later for causing toggle */
 /* recording code gen  - works because no more toggle set up after here */
 __toggle_coverage = TRUE;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->m_has_toggle_cover) return;
  }
#ifndef __CVC_RT__
 __pv_warn(4338,
   "All design toggle coverage turned off either no nets toggle coverage on or all nets toggle coverage off from exclude - still need to run with toggle recording"); 
#endif
 /* SJM 05-05-13 - know if get here design has all tgl cover turned off */
 /* but still need to compile for tgl since idp stuff set */
}

/*
 * try to set net has excluded bits flag for later use by report gen
 *
 * only set here - no during cfg file processing
 * only called if know not already on 
 */
static void try_set_net_excl_bit(struct net_t *np, int32 ii)
{
 int32 bi, base, bval;

 base = ii*np->nwid;
 for (bi = np->nwid; bi >= 0; bi--)
  {
   bval = rhsbsel_(np->ntgp->peribits_tgl_rpt_exclude, base + bi);
   if (bval != 0) { np->n_has_tglbits_excl = TRUE; return; } 
  }
}

/*
 * routine to set stmt coverage bits for include/exclude for a module
 *
 * SJM 04-26-13 - this is only per mod
 */
static void set_stmt_cover_bits(struct mod_t *mdp, struct inst_t *ip,
 int32 is_excld)
{
 if (mdp != NULL)
  {
   if (is_excld) mdp->m_has_stmt_cover = FALSE;
   else mdp->m_has_stmt_cover = TRUE;
   return;
  }
 /* DBG remove -- */
 if (ip == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (is_excld) ip->imsym->el.emdp->m_has_stmt_cover = FALSE;
 else ip->imsym->el.emdp->m_has_stmt_cover = TRUE;
}

/*
 * to set event control coverage bits per mod
 *
 * SJM 04-26-13 - event cover only per mod
 */
static void set_event_cover_bits(struct mod_t *mdp, struct inst_t *ip,
 int32 is_excld)
{
 if (mdp != NULL)
  {
   if (is_excld) mdp->m_has_event_cover = FALSE; 
   else mdp->m_has_event_cover = TRUE; 
   return;
  }
 /* DBG remove -- */
 if (ip == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (is_excld) ip->imsym->el.emdp->m_has_event_cover = FALSE;
 else ip->imsym->el.emdp->m_has_event_cover = TRUE;
}

#ifdef __XPROP__
/*
 * set xprop option bits per module only
 *
 * SJM 04-26-13 - xprop is always per module since compiled into code
 */  
static void set_xprop_bits(struct mod_t *mdp, struct inst_t *ip,
 int32 is_exclude, int32 xprop_typ_mask)
{
 int32 xprop, xprop2, xprop_and_or; 

 xprop = xprop2 = xprop_and_or = FALSE;
 /* set the flags from mode mask */
 if ((xprop_typ_mask & OCPRP_XPROP) != 0) 
  {
   __xprop = TRUE;
   xprop = TRUE;
  }
 if ((xprop_typ_mask & OCPRP_XPROP2) != 0) 
  {
   __xprop2 = TRUE;
   xprop2 = TRUE;
  }
 if ((xprop_typ_mask & OCPRP_XPROP_AND_OR_X) != 0) 
  {
   __xprop_and_or_xs = TRUE;
   xprop_and_or = TRUE;
  }

 /* cannot inter mix any combo of __xprop and __xprop2 */
 if (__xprop && __xprop2)
  {
   __pv_ferr(1990,
     "+xprop cannot be used with +xprop2 - only one may be used from opt config file");
  }

 if (mdp == NULL)
  {
   /* DBG remove -- */
   if (ip == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   mdp = ip->imsym->el.emdp;
  }

 /* if exclude turn off else on */
 if (is_exclude)
  {
   mdp->m_use_xprop = !xprop; 
   mdp->m_use_xprop2 = !xprop2;
   mdp->m_use_xprop_and_or_x = !xprop_and_or;
  }
 else
  {
   mdp->m_use_xprop = xprop; 
   mdp->m_use_xprop2 = xprop2;
   mdp->m_use_xprop_and_or_x = xprop_and_or;
  }
}
#endif

/*
 * routine to set the PLI acc+<num> net field - similar to pli.tab and
 * unlike the +acc+ option uses a name not a number
 *
 * SJM 04-26-13 - setting here is per module obviously
 */
static void set_plitab_acc(int32 acc_lev, struct mod_t *mdp,
 struct inst_t *ip, struct net_t *np, int32 is_excld)
{
 struct mod_t *mdp2;

 /* notice no mod or inst pli access acc lev on net and design */
 if (np != NULL)
  {
   if (is_excld)
    {
     np->pli_access = 0;
     return;
    }
   if (acc_lev >= np->pli_access) np->pli_access = acc_lev;
   /* access lev > 1 for change record */
   if (acc_lev >= 1) np->nchg_nd_chgstore = TRUE;
   return;
  }

 if (mdp != NULL)
  {
   /* need to turn all instances of this modules to toggle true */
   /* AIV 02/19/12 - there is no reason to do this for each instance */
   /* just the module - removed the for loop */
   set_1mod_all_nets_acc(acc_lev, mdp, is_excld);

   /* AIV 02/15/12 - this needs to also mark all instances that are split */
   /* so for module {ddr} {acc_rw}; - if this is split into ddr$$2 */
   /* must also set bits of the split module */
   /* AIV 03/30/12 - had a bug there on increment - mdp2 not mdp */
   /* AIV 04/04/12 - if already set do not need to process again */
   //AIV LOOKATME - maybe xprop/coverage should inlcude these split marking as
   //well - leaving for now - but pli needs it or design may silently not work
   if (!mdp->m_opt_pli_bits_set && !is_excld)
    {
     for (mdp2 = mdp->split_hd; mdp2 != NULL; mdp2 = mdp2->split_nxt) 
      {
      //AIV LOOKATME - split list copied to itself?????
       if (mdp2 == mdp) continue;
       set_1mod_all_nets_acc(acc_lev, mdp2, is_excld);
      }
    }
   return;
  }
 /* DBG remove -- */
 if (ip == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 mdp = ip->imsym->el.emdp;
 set_1mod_all_nets_acc(acc_lev, mdp, is_excld);
}

/*
 * routine to set acc level for all nets in one module
 */
static void set_1mod_all_nets_acc(int32 acc_lev, struct mod_t *mdp,
 int32 is_excld)
{
 int32 ni;
 struct net_t *np;
 struct task_t *tskp; 

 mdp->m_opt_pli_bits_set = TRUE;
 /* add to each variable */
 if (mdp->mnnum != 0)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     if (is_excld)
      {
       np->pli_access = 0;
       continue;
      }
     if (acc_lev >= np->pli_access) np->pli_access = acc_lev;
     if (acc_lev >= 1) np->nchg_nd_chgstore = TRUE;
    }
  }
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt) 
  {
   if (tskp->trnum != 0)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       if (is_excld)
        {
         np->pli_access = 0;
         continue;
        }
       if (acc_lev >= np->pli_access) np->pli_access = acc_lev;
       if (acc_lev >= 1) np->nchg_nd_chgstore = TRUE;
      }
    } 
  }
}

/*
 * routine to check for legal opt cfg file statement attribute (property)
 * and return the property type
 *
 * return -1 on unrecognized property
 * SJM 12-16-10- FIXME - need warning for unrecognized property
 */
extern int32 __get_optcfg_prop_typ(struct ocfg_stmt_t *ocstmtp)
{
 int32 ret_mask;
 struct oc_vtok_t *ocvtokp;

 ret_mask = 0;
 for (ocvtokp = ocstmtp->oc_props; ocvtokp != NULL; ocvtokp = ocvtokp->ocvtnxt) 
  {
   /* DBG remove -- */
   if (ocvtokp->ocs_toctyp != ID) __misc_terr(__FILE__, __LINE__);
   /* --- */

   if (strcmp(ocvtokp->ocs_toknam, "cover_toggle") == 0)
    {
     /* need to turn on toggle coverage */
     ret_mask |= OCPRP_TGL;
    }
   else if (strcmp(ocvtokp->ocs_toknam, "cover_stmt") == 0)
    {
     /* need to turn on event control coverage */
     __stmt_coverage = TRUE;
     ret_mask |= OCPRP_STMT;
    }
   else if (strcmp(ocvtokp->ocs_toknam, "cover_event") == 0)
    {
     /* need to turn on statement coverage */
     __event_coverage = TRUE;
     ret_mask |= OCPRP_EVENT;
    }
   else if (strcmp(ocvtokp->ocs_toknam, "acc_rw") == 0)
    {
     ret_mask |= OCPRP_ACC_RW;
     __pli_access_level = 1;
    }
   else if (strcmp(ocvtokp->ocs_toknam, "acc_cbk") == 0)
    {
     ret_mask |= OCPRP_ACC_CBK;
     __pli_access_level = 2;
    }
   else if (strcmp(ocvtokp->ocs_toknam, "acc_ann_path_del") == 0)
    {
     ret_mask |= OCPRP_ACC_ANNPD;
     __pli_access_level = 3;
    }
   else if (strcmp(ocvtokp->ocs_toknam, "acc_ann_gate_del") == 0)
    {
     ret_mask |= OCPRP_ACC_ANNGD;
     __pli_access_level = 4;
    }
#ifdef __XPROP__
   /* xprop control flags */
   else if (strcmp(ocvtokp->ocs_toknam, "xprop") == 0)
    {
     ret_mask |= OCPRP_XPROP;
     __xprop = TRUE;
    }
   else if (strcmp(ocvtokp->ocs_toknam, "xprop2") == 0)
    {
     ret_mask |= OCPRP_XPROP2;
     __xprop2 = TRUE;
    }
   else if (strcmp(ocvtokp->ocs_toknam, "xprop_eval") == 0)
    {
     ret_mask |= OCPRP_XPROP_AND_OR_X;
     __xprop_and_or_xs = TRUE;
    }
#endif
   else
    {
     __pv_fwarn(4309,
      "-optconfigfile attribute or PLI access property name %s unrecognized - ignored",
      ocvtokp->ocs_toknam);
    }
  }
 return(ret_mask);
}

/*
 * ROUTINES TO READ CFG LIB.MAP INPUT FILE LIST
 */

/*
 * read a cfg file - returns F on error else T
 * reads both library mapping file and the config blocks
 *
 * may have list of config map library files (if none given using map.lib)
 *
 * if passed the command line, insrc = FALSE, and mapfile is the file name
 * otherwise TRUE, NULL if in source
 *
 * SJM 11/29/03 - contrary to LRM but following NC, cfg can't appear in src
 * but allowing list of lib.map files
 */
extern int32 __rd_cfg(void)
{
 int32 i, sav_ecnt, sav_lin_cnt;
 FILE *fp;
 struct mapfiles_t *mapfp;
 char *sav_cur_fnam;

 /* DBG remove -- */
 if (__map_files_hd == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* initialize the instance clause rule binding XMR path component glb tab */
 __siz_bind_comps = 50;
 __bind_inam_comptab = (char **) __my_malloc(__siz_bind_comps*sizeof(char *)); 
 __last_bind_comp_ndx = -1;
 for (i = 0; i < __siz_bind_comps; i++) __bind_inam_comptab[i] = NULL;

 /* SJM 01/15/04 - reading cfg does not use in fils buts must save as cntxt */
 sav_lin_cnt = __lin_cnt;
 sav_cur_fnam = __cur_fnam;

 sav_ecnt = __pv_err_cnt; 
 for (mapfp = __map_files_hd; mapfp != NULL; mapfp = mapfp->mapfnxt) 
  {
   /* must set cur file and line count for error messages */
   __cur_fnam = __pv_stralloc(mapfp->mapfnam);
   __lin_cnt = 1;
   if ((fp = __tilde_fopen(__cur_fnam, "r")) == NULL)
    {
     __pv_err(3500, "cannot open config map library file %s - skipped",
      __cur_fnam);
     continue;
    }
   if (feof(fp))
    {
     __pv_warn(3121, "config map library file %s empty", __cur_fnam);
     continue; 
    }
   rd1_cfg_file(fp);
  }
 /* and then put back */
 __lin_cnt = sav_lin_cnt;
 __cur_fnam = sav_cur_fnam;
 
 if (__pv_err_cnt != sav_ecnt) return(FALSE);
 return(TRUE);
}

/*
 * read contents of one config file
 */
static void rd1_cfg_file(FILE *fp)
{ 
 int32 ttyp, ttyp2, sav_lin_cnt;
 FILE *incfp;
 char *sav_cur_fnam;

 for (;;)
  {
   ttyp = __get_cfgtok(fp);
   if (ttyp == CFG_INCLUDE)
    {
     if ((ttyp2 = __get_cfgtok(fp)) != CFG_ID)
      {
       __pv_ferr(3501,
        "config map library include statement non wildcard file path name expected - %s read",
        __to_cfgtoknam(__xs, ttyp2));
       if (cfg_skipto_semi(ttyp2, fp) == CFG_EOF) return;  
       continue;
      }
     if ((incfp = __tilde_fopen(__token, "r")) == NULL)
      {
       __pv_ferr(3502,
        "cannot open config map library include file %s - skipped",
        __token);
       if (cfg_skipto_semi(ttyp2, fp) == CFG_EOF) return;  
       continue;
      }
     if (feof(incfp))
      {
       __pv_warn(3121, "config map library file %s empty", __token);
       goto skipto_semi;
      }

     /* SJM 01/15/04 - save ptr and malloc name for later err msgs */
     sav_lin_cnt = __lin_cnt;
     sav_cur_fnam = __cur_fnam;
     __cur_fnam = __pv_stralloc(__token);
     __lin_cnt = 1;

     rd1_cfg_file(incfp); 

     __cur_fnam = sav_cur_fnam;
     __lin_cnt = sav_lin_cnt;

skipto_semi:
     ttyp = __get_cfgtok(fp);
     if (ttyp != CFG_SEMI)
      {
       if (cfg_skipto_semi(ttyp2, fp) == CFG_EOF) return;  
      }
     continue;
    }
   if (ttyp == CFG_LIBRARY)
    {
     rd_cfg_library(fp);
     continue;
    }
   if (ttyp == CFG_CFG) 
    {
     rd_cfg_cfg(fp);
     continue;
    }
   if (ttyp == CFG_EOF) return;
  }
 /* -- DBG remove ---
 dump_mod_info();
 --- */ 
}

/*
 * read a library map file library list
 * expects library keyword to have been read and reads ending ; (or CFG_EOF)
 *
 * if no libraries specified and unresolved references after reading
 * source files (either from config or from list of source files)
 * elaboration will fail with unresolved lib refs
 */
static void rd_cfg_library(FILE *fp)
{
 int32 ttyp;
 struct cfglib_t *lbp;
 struct libel_t *lbep;

 /* get the library name */
 if ((ttyp =__get_cfgtok(fp)) != CFG_ID)
  {
   __pv_ferr(3503,
    "library map file library description library name expected - %s read", 
    __to_cfgtoknam(__xs, ttyp));
   cfg_skipto_semi(ttyp, fp);
   return;
  }
 lbp = (struct cfglib_t *) __my_malloc(sizeof(struct cfglib_t));
 init_cfglib(lbp);
 /* needed for expand error messages */
 lbp->cfglb_fnam = __cur_fnam;
 lbp->cfglb_lno = __lin_cnt;
 lbp->sym_added = FALSE;

 if (!chk_libid(__token))
  { 
   __pv_ferr(3504, "library name %s illegal simple Verilog identifier",
    __token);
  }
 lbp->lbname = __pv_stralloc(__token);
 lbep = rd_cfg_fspec_list(fp, FALSE);
 lbp->lbels = lbep; 
 if (__cfglib_tail == NULL) __cfglib_hd = __cfglib_tail = lbp; 
 else
  {
   __cfglib_tail->lbnxt = lbp;
   __cfglib_tail = lbp;
  }
}

/*
 * read a list of library file spec (wildcard) paths build and return list
 * reads first element and reads ending EOF (for --incdir) or semi 
 *
 * SJM 12/11/03 - notice old config dir code was wrong - comma separated list
 *
 * LOOKATME - maybe should return nil on error
 */
static struct libel_t *rd_cfg_fspec_list(FILE *fp, int32 in_incdir)
{
 int32 ttyp, ttyp2, sav_lin_cnt;
 struct libel_t *lbep, *lbep2, *lbep_hd, *last_lbep;
 FILE *incfp;
 char *sav_cur_fnam;

 for (lbep_hd = last_lbep = NULL;;)
  {
   ttyp = __get_cfgtok(fp);
   if (ttyp == CFG_SEMI || ttyp == CFG_EOF)
    {
     if (in_incdir)
      {
       if (ttyp == CFG_SEMI)
        {
         __pv_ferr(3507,
          "config library description file path spec in -incdir ';' illegal");
         cfg_skipto_eof(ttyp, fp);
        }
       break; 
      }
     if (ttyp == CFG_EOF)
      {
       __pv_ferr(3507,
        "config library description file path spec in -incdir ';' illegal");
         cfg_skipto_eof(ttyp, fp);
       /* even if hit wrong early EOF return list build so far */
      }
     /* know correct sem read or error emitted */
     break;
    }

   if (ttyp != CFG_ID)
    {
     __pv_ferr(3506,
      "config library description file path spec expected - %s read",
      __to_cfgtoknam(__xs, ttyp)); 

     if ((ttyp2 = cfg_skipto_comma_semi(ttyp, fp)) == CFG_COMMA) continue;
     if (in_incdir && ttyp2 == CFG_SEMI)
      {
       __pv_ferr(3507,
        "config library description file path spec in -incdir ';' illegal");
       cfg_skipto_eof(ttyp, fp);
      }
     return(NULL);
    }
   
   /* -incdir [name of file contains comma separated lib list] */
   /* can be nested */
   /* case 1: -incdir file containg comma separated list but end with EOF */ 
   if (strcmp(__token, "-incdir") == 0) 
    {
     /* read the config list from a file (comma separated) */
     if ((ttyp2 = __get_cfgtok(fp)) != CFG_ID)
      {
       __pv_ferr(3501,
        "config library description -incdir non wildcard file path name expected - %s read",
        __to_cfgtoknam(__xs, ttyp2));
inc_err_skip:
       if (cfg_skipto_comma_semi(ttyp, fp) == CFG_COMMA) continue;
       return(NULL);
      }
     if ((incfp = __tilde_fopen(__token, "r")) == NULL)
      {
       __pv_ferr(3502,
        "cannot open config library description -incdir file %s - skipped",
        __token);
       goto inc_err_skip; 
      }
     if (feof(incfp))
      {
       __pv_fwarn(3121,
        "config library description -incdir file %s empty", __token);
       goto inc_err_skip;
      }

     /* SJM 01/15/04 - save ptr and malloc name for later err msgs */
     sav_cur_fnam = __cur_fnam;
     sav_lin_cnt = __lin_cnt;
     __cur_fnam = __pv_stralloc(__token);
     __lin_cnt = 1;

     lbep = rd_cfg_fspec_list(incfp, TRUE);
     if (lbep != NULL) 
      {
       /* link onto end and update last to end of new add (maybe long) list */
       if (last_lbep == NULL) lbep_hd = lbep;
       else last_lbep->lbenxt = lbep;

       /* SJM 12/08/03 - think this is wrong ??? - need a last */
       for (lbep2 = lbep; lbep2->lbenxt != NULL; lbep2 = lbep2->lbenxt) ; 
       last_lbep = lbep2;
      } 
     __my_fclose(incfp); 

     __cur_fnam = sav_cur_fnam;
     __lin_cnt = sav_lin_cnt;
    }
   /* case 2: file spec - only other possibility */
   lbep = (struct libel_t *) __my_malloc(sizeof(struct libel_t));
   lbep->lbelsrc_rd = FALSE;
   lbep->lbefnam = __pv_stralloc(__token);
   lbep->lbcelndx = NULL;
   lbep->lbel_sytab = NULL;
   lbep->lbenxt = NULL;
   lbep->expanded = FALSE;

   if (last_lbep == NULL) lbep_hd = lbep; else last_lbep->lbenxt = lbep;
   last_lbep = lbep;
  }
 return(lbep_hd);
}

/*
 * read map library config block 
 * know config keyword read and reads the endconfig keyword 
 *
 * idea is that the library lists are separate from the config blocks
 */
static void rd_cfg_cfg(FILE *fp)
{
 int32 ttyp, len, cfg_beg_lno, nbytes, expl_config;
 struct cfgdes_t *desp, *des_hd, *des_tail;
 struct cfg_t *cfgp;
 struct cfgrule_t *rulp, *rule_beg, *rule_end;
 struct cfgnamlst_t *lblp;
 char objnam[IDLEN], libnam[IDLEN], celnam[IDLEN];
 char cfgnam[IDLEN], s1[IDLEN], s2[IDLEN];

 cfg_beg_lno = __lin_cnt;
 /* get the config name */
 if ((ttyp =__get_cfgtok(fp)) != CFG_ID)
  {
   __pv_ferr(3503, "config declaration config name expected - %s read", 
    __to_cfgtoknam(__xs, ttyp));
   if (cfg_skipto_semi(ttyp, fp) == CFG_EOF) return;
   strcpy(cfgnam, "**none**");
  }
 else
  { 
   strcpy(cfgnam, __token);
   ttyp = __get_cfgtok(fp);
  }
 if (ttyp != CFG_SEMI)
  {
   __pv_ferr(3531,
    "config declaration config name not followed by semicolon - %s read",
    __to_cfgtoknam(__xs, ttyp));
   if (cfg_skipto_semi(ttyp, fp) == CFG_EOF) return;
  }
 /* config names may need to match cell type names so can be escaped */
 if (!chk_libid(cfgnam))
  {
   if (chk_escid(cfgnam))
    {
     /* remove the leading escaping back slash and ending ' ' */
     strcpy(s1, &(cfgnam[1]));
     len = strlen(s1);
     s1[len - 1] = '\0';
     strcpy(cfgnam, s1);
    }
   else
    {
     __pv_ferr(3534,
      "illegal config name %s - must be legal Verlog identifier", cfgnam);
    }
  }

 cfgp = (struct cfg_t *) __my_malloc(sizeof(struct cfg_t));
 init_cfg(cfgp);
 cfgp->cfgnam = __pv_stralloc(cfgnam);
 /* config location info for tracing and error msgs */
 cfgp->cfg_fnam = __pv_stralloc(__cur_fnam); 
 cfgp->cfg_lno = cfg_beg_lno;

 ttyp = __get_cfgtok(fp);
 /* config design statement must come first if used */
 if (ttyp == CFG_DESIGN)
  {
   /* SJM 12/08/03 - as I read LRM, every top module needs separate config */ 
   /* therefore only one design mod allowed - FIXME- text of LRM contradicts */

   des_hd = des_tail = NULL;
   for (;;)
    {
     ttyp =__get_cfgtok(fp);
     if (ttyp == CFG_SEMI)
      {
       if (des_hd == NULL)
        {
         __pv_ferr(3532,
          "config design statement requires at least one [lib name].[cell name]");
        }
       break;
      }
     /* get the design specifier [library].[mod name] */
     if (ttyp != CFG_ID)
      {
       __pv_ferr(3533,
        "config design statement design specifier expected - %s read", 
        __to_cfgtoknam(__xs, ttyp));
       if (cfg_skipto_semi(ttyp, fp) == CFG_EOF) return;
       /* here just leave objnam nil for none */
      }
     else
      { 
       /* library name required design cell name */ 
       /* notice cell nam can be escaped and if so escapes removed */
       if (!extract_design_nam(libnam, celnam, __token))
        {
         __pv_ferr(3535,
          "config design statement [library identifier].[cell identifier] expected - %s illegal",
          __to_cfgtoknam(__xs, ttyp));
         /* skip on error */
         continue;
        }
      desp = (struct cfgdes_t *) __my_malloc(sizeof(struct cfgdes_t)); 
      desp->deslbnam = __pv_stralloc(libnam);
      desp->deslbp = NULL;
      desp->topmodnam = __pv_stralloc(celnam);
      desp->desnxt = NULL;

      if (des_hd == NULL) des_hd = des_tail = desp;
      else
       {
        des_tail->desnxt = desp;
        des_tail = desp;
       }
     }
    }
   cfgp->cfgdeslist = des_hd;

   /* know ';' read to get here */
   ttyp =__get_cfgtok(fp);
  }
 rule_beg = rule_end = NULL;
 for (;;)
  {
   /* liblist or use clauses never start a config rule */
   switch(ttyp) { 
    case CFG_DEFAULT:
     if (cfgp->cfgdflt != NULL)
      {
       __pv_ferr(3538, "config %s default clause repeated - new one replaces",
       cfgp->cfgnam);
      }
   
     /* format: default liblist [space sep list of library names]; */ 
     /* may return nil */
     if ((ttyp = __get_cfgtok(fp)) != CFG_LIBLIST) 
      {
       __pv_ferr(3537,
        "config declaration default clause not followed by liblist keyword - %s read",
        __to_cfgtoknam(__xs, ttyp));
       if (cfg_skipto_semi_endconfig(ttyp, fp) != CFG_SEMI)
        return;
       continue;
      }
     if ((lblp = rd_liblist(fp)) != NULL)
      {
       if (cfgp->cfgdflt != NULL) 
        {
         /* SJM 12/19/03 - LOOKATME - what if repated */
         __pv_ferr(3539, "config declaration default clause repeated - 2nd ignord"); 
        }
      }
     else
      {
       __pv_fwarn(3127, "config declaration default clause liblist empty");
      }
     rulp = (struct cfgrule_t *) __my_malloc(sizeof(struct cfgrule_t));
     init_rule(rulp);
     rulp->rul_libs = lblp;
     rulp->rultyp = CFG_DEFAULT;
     cfgp->cfgdflt = rulp;
     break;
    case CFG_ENDCFG:
     /* no semi after end config */
     goto endcfg_read;
    case CFG_INSTANCE:
     /* format: instance [inst name] liblist [space sep lib name list]; */ 
     /* format: instance [inst name] use [qualified mod type name]; */
 
     /* instance name can be XMR but take apart later */
     if ((ttyp = __get_cfgtok(fp)) != CFG_ID) 
      {
       __pv_ferr(3540,
        "config instance clause instance named expected - %s read",
          __to_cfgtoknam(__xs, ttyp));
        if (cfg_skipto_semi_endconfig(ttyp, fp) != CFG_SEMI)
         return;
       continue;
      }
     /* save the instance name */
     strcpy(objnam, __token);
     /* check config XMR path and build malloced cfg nam list of components */
     /* if return F, table not built */
     if (!bld_inst_xmr_comptab(__token))
      {
       __pv_ferr(3540,
        "config instance clause instance name %s illegal Verilog hierarchical name",
       __token);
       continue;
      }  

     lblp = NULL;
     if ((ttyp = __get_cfgtok(fp)) == CFG_LIBLIST) 
      {
       /* case 1: liblist form - always reads ending ; */
       if ((lblp = rd_liblist(fp)) == NULL)
        {
         __pv_fwarn(3129, "config instance clause liblist empty - ignored");
         goto rd_nxt_tok;
        }
       rulp = (struct cfgrule_t *) __my_malloc(sizeof(struct cfgrule_t));
       init_rule(rulp);
       rulp->rultyp = CFG_INSTANCE;
       /* just set the instance name and lib names are in lblp */
       rulp->objnam = __pv_stralloc(objnam);
       rulp->rul_libs = lblp;
      }
     else if (ttyp == CFG_USE) 
      {
       if (rd_use_clause(fp, s1, s2, &expl_config) == CFG_ENDCFG)
        return;
       /* on error s1 not set */
       if (strcmp(s1, "") == 0 && strcmp(s2, "") == 0) goto rd_nxt_tok;

       rulp = (struct cfgrule_t *) __my_malloc(sizeof(struct cfgrule_t));
       init_rule(rulp);
       rulp->rultyp = CFG_INSTANCE;
       /* instance objnam use s1.s2 */
       rulp->rul_use_libnam = __pv_stralloc(s1);
       rulp->rul_use_celnam = __pv_stralloc(s2);
       rulp->objnam = __pv_stralloc(objnam);
       rulp->use_rule_cfg = expl_config;
       rulp->is_use = TRUE; 
      }
     else
      {
       __pv_ferr(3548,
        "config inst clause not followed by liblist or use clause - %s read",
        __to_cfgtoknam(__xs, ttyp));
       if (cfg_skipto_semi(ttyp, fp) == CFG_EOF) return;
       goto rd_nxt_tok;
      }

     /* SJM 01/14/03 - can't bld the inst XMR components tab until here */
     nbytes = (__last_bind_comp_ndx + 1)*sizeof(char *);
     rulp->inam_comptab = (char **) __my_malloc(nbytes);
     memcpy(rulp->inam_comptab, __bind_inam_comptab, nbytes);
     rulp->inam_comp_lasti = __last_bind_comp_ndx;
     /* head of instance name must match config name a design cell name */
     for (desp = cfgp->cfgdeslist; desp != NULL; desp = desp->desnxt)
      {
       if (strcmp(desp->topmodnam, rulp->inam_comptab[0]) == 0)
        goto fnd_match;
      }
     __pv_ferr(3541,
      "config instance clause hierachical path %s head does not match any design statement top rooted module name",
      s1);

fnd_match: 
     /* add to end of list since must search in order of appearance */
     if (rule_beg == NULL) cfgp->cfgrules = rule_beg = rule_end = rulp;
     else
      {
       rule_end->rulnxt = rulp;
       rule_end = rulp;
      }
     
     break;
    case CFG_CELL:
     /* format: cell [<lib:>cell] liblist [space sep lib name list]; */ 
     /* format: cell [<lib>:cell] use [qualified mod type name]; */
     if ((ttyp = __get_cfgtok(fp)) != CFG_ID) 
      {
       __pv_ferr(3551,
        "config cell clause [library].cell name expected - %s read",
        __to_cfgtoknam(__xs, ttyp));
       if (cfg_skipto_semi_endconfig(ttyp, fp) != CFG_SEMI) return;
       continue;
      }
     if (!extract_libcell_nam(libnam, objnam, __token))
      {
       goto rd_nxt_tok;
      }
     lblp = NULL;
     if ((ttyp = __get_cfgtok(fp)) == CFG_LIBLIST) 
      {
       /* AIV - LRM (pg 217) states lib.cell with liblist is an error */
       /* if stmt will work because libnam init in extract_libcell  */
       if (libnam[0] != '\0') 
       {
         __pv_ferr(3552,
          "config cell clause library.cell (%s.%s) cannot be used with 'liblist' clause", libnam, objnam);
        if (cfg_skipto_semi_endconfig(ttyp, fp) != CFG_SEMI) return;
        goto rd_nxt_tok;
       }

       /* case 1: liblist form - always reads ending ; */
       if ((lblp = rd_liblist(fp)) == NULL)
        {
         __pv_fwarn(3131, "config cell clause liblist empty - ignored");
         goto rd_nxt_tok;
        }
       rulp = (struct cfgrule_t *) __my_malloc(sizeof(struct cfgrule_t));
       init_rule(rulp);
       rulp->rultyp = CFG_CELL;
       /* libnam optional    libnam.objnam */
       rulp->libnam = __pv_stralloc(libnam);
       rulp->objnam = __pv_stralloc(objnam);
       rulp->rul_libs = lblp;
      }
     else if (ttyp == CFG_USE) 
      {
       if (rd_use_clause(fp, s1, s2, &expl_config) == CFG_ENDCFG) return;
       /* on error s1 not set */
       if (strcmp(s1, "") == 0 && strcmp(s2, "") == 0) goto rd_nxt_tok;

       rulp = (struct cfgrule_t *) __my_malloc(sizeof(struct cfgrule_t));
       init_rule(rulp);
       /* cell objnam use s1.s2 */
       rulp->rul_use_libnam = __pv_stralloc(s1);
       rulp->rul_use_celnam = __pv_stralloc(s2);
       rulp->use_rule_cfg = expl_config;
       /* objnam is the cell type to match */
       rulp->objnam = __pv_stralloc(objnam);
       rulp->libnam = __pv_stralloc(libnam);
       rulp->rultyp = CFG_CELL;
       rulp->is_use = TRUE; 
      }
     else
      {
       __pv_ferr(3559,
        "config cell clause not followed by liblist or use keywords - %s read",
        __to_cfgtoknam(__xs, ttyp));
       if (cfg_skipto_semi(ttyp, fp) == CFG_EOF) return;
       goto rd_nxt_tok;
      }

     /* add to end of list since must search in order of appearance */
     if (rule_beg == NULL) cfgp->cfgrules = rule_beg = rule_end = rulp;
     else
      {
       rule_end->rulnxt = rulp;
       rule_end = rulp;
      }
     break;
    default:
     __pv_ferr(3561,
      "config declaration rule statement or endconfig expected - %s read",
      __to_cfgtoknam(__xs, ttyp));
     if (cfg_skipto_semi(ttyp, fp) == CFG_EOF) return;
   }
rd_nxt_tok:
   ttyp =__get_cfgtok(fp);
  }
endcfg_read:
   /* AIV add the config to the list */
   if (__cfg_hd == NULL) __cfg_hd = __cur_cfg = cfgp;
   else { __cur_cfg->cfgnxt = cfgp;  __cur_cfg = cfgp; }
 return;
}

/*
 * initialize a rule record
 */
static void init_rule(struct cfgrule_t *rulp)
{
 rulp->rultyp = CFG_UNKNOWN;
 rulp->use_rule_cfg = FALSE;
 rulp->objnam = NULL;
 rulp->libnam = NULL;
 rulp->rul_use_libnam = NULL; 
 rulp->rul_use_celnam = NULL; 
 rulp->inam_comptab = NULL;
 rulp->inam_comp_lasti = -1;
 rulp->rul_libs = NULL;
 rulp->rulnxt = NULL;
 /* AIV just set the line to current line  */
 rulp->rul_lno =  __lin_cnt;
 rulp->matched =  FALSE;
 rulp->is_use =  FALSE;
}

/*
 * extract a [lib].[cell] design name - format [lib].[cell] 
 * lib ID lexical pattern is: [let or _]{let | num | $ | _}
 *
 * SJM 12/19/03 - LRM wrong since config can't be in Verilog source lib
 * and cell names both required
 *
 * SJM 01/12/04 - library identifiers (names) can't be escaped
 */
static int32 extract_design_nam(char *libnam, char *celnam, char *desnam)
{
 int32 len;
 char *chp;
 char s1[IDLEN], s2[IDLEN];

 strcpy(libnam, "");
 strcpy(celnam, "");

 if ((chp = strchr(desnam, '.')) == NULL) return(FALSE);
 strncpy(s1, desnam, chp - desnam);
 s1[chp - desnam] = '\0';
 if (!chk_libid(s1)) return(-1);
 strcpy(libnam, s1);

 chp++;
 strcpy(s2, chp);
 if (!chk_libid(s2))
  {
   if (chk_escid(s2))
    {
     /* remove the leading escaping back slash and ending ' ' */
     strcpy(s1, &(s2[1]));
     len = strlen(s1);
     s1[len - 1] = '\0';
    }
   else
    {
     __pv_ferr(3534,
      "illegal cell name %s - must be legal Verlog identifier", s2);
    }
   strcpy(celnam, s1);
   return(TRUE);
  }
 strcpy(celnam, s2);
 return(TRUE);
}

/*
 * check and return T if library name is legal unescaped ID
 */
static int32 chk_libid(char *lbnam)
{
 char *chp;

 chp = lbnam;
 if (!isalpha(*chp) && *chp != '_') return(FALSE);
 for (++chp; *chp != '\0'; chp++)
  {
   if (!isalnum(*chp) && *chp!= '$' && *chp != '_') return(FALSE);
  }
 return(TRUE);
}

/*
 * check and return T if path component or cell type name is legal escaped ID
 */
static int32 chk_escid(char *nam)
{
 int32 len;
 char *chp;

 chp = nam;
 if (*chp != '\\') return(FALSE); 
 len = strlen(nam);
 if (nam[len - 1] != ' ') return(FALSE);
 return(TRUE);
}

/*
 * build table of ptrs to strings in global cfg bind table of instance comps
 * return F on error
 *
 * grows bind inam comp tab - caller will copy to malloced memory
 */
static int32 bld_inst_xmr_comptab(char *inam)
{
 int32 ci, len;
 char *chp, *chp2;
 char s1[IDLEN], s2[IDLEN];

 /* AIV need to reset the global, after it is copied */
 __last_bind_comp_ndx = -1;
 
 for (chp = inam;;)
  {
   if (*chp == '\\')
    {
     if ((chp2 = strchr(chp, ' ')) == NULL)
      {
bad_end:
       for (ci = 0; ci <= __last_bind_comp_ndx; ci++)
        {
         __my_free(__bind_inam_comptab[ci],
          strlen(__bind_inam_comptab[ci]) + 1);
         __bind_inam_comptab[ci] = NULL;
        }
       return(TRUE);
      }

     strncpy(s1, chp, chp2 - chp);
     s1[chp2 - chp] = '\0';
     if (!chk_escid(s1)) goto bad_end;
     strcpy(s2, &(s1[1]));
     s2[chp2 - chp - 2] = '\0';
     chp++;
    }
   else
    {
     if ((chp2 = strchr(chp, '.')) == NULL)
      {
       strcpy(s2, chp);
       len = strlen(chp);
       chp = &(chp[len]);
      }
     else
      {
       /* non escaped and non tail component */
       strncpy(s2, chp, chp2 - chp);
       s2[chp2 - chp] = '\0';
       chp = chp2;
      }
    }
   /* add malloced comp name to table - table copied so do not need to free */ 
   if (++__last_bind_comp_ndx >= __siz_bind_comps) grow_bind_comps();
   __bind_inam_comptab[__last_bind_comp_ndx] = __pv_stralloc(s2); 

   if (*chp == '\0') break;
   if (*chp != '.') goto bad_end;
   chp++;
  }
 return(TRUE);
}

/*
 * routine to grow global bind comp table
 */
static void grow_bind_comps(void)
{
 size_t osize, nsize;
     
 osize = __siz_bind_comps*sizeof(char *);
 /* SJM 01/13/04 - maybe growing too fast */
 __siz_bind_comps *= 2;
 nsize = __siz_bind_comps*sizeof(char *);
 __bind_inam_comptab = (char **) __my_realloc(__bind_inam_comptab,
  osize, nsize);
}


/*
 * extract a <lib>.[cell] name where [lib] optional
 *
 * almost same as extracting design [lib].[cell] but there lib name required
 */
static int32 extract_libcell_nam(char *libnam, char *celnam, char *nam)
{
 char *chp;
 char s1[IDLEN], s2[IDLEN];

 strcpy(libnam, "");
 strcpy(celnam, "");

 /* case 1: library omitted and escaped cell name */
 if (*nam == '\\')
  {
   strcpy(s2, nam); 

do_cell_tail:
   if ((chp = strchr(nam, ' ')) == NULL) return(FALSE);
   strncpy(celnam, nam, chp - nam);
   celnam[chp - nam] = '\0';
   /* checking esc ID but for now will never fail */
   if (!chk_escid(s2)) return(FALSE); 
   strncpy(s1, &(nam[1]), chp - nam - 2);
   s1[chp - nam - 2] = '\0';
   strcpy(celnam, s1);
   chp++;
   if (*chp != '\0') return(FALSE);
   return(TRUE);
  }
 /* if lib name before '.' present, check and fill */
 if ((chp = strchr(nam, '.')) != NULL)
  { 
   strncpy(s1, nam, chp - nam);
   s1[chp - nam] = '\0';
   if (!chk_libid(s1)) return(FALSE);
   strcpy(libnam, s1);
   chp++;
   strcpy(s1, chp);
  }
 else strcpy(s1, nam);
 
 /* case 3: lib name present and escaped ID */
 if (*s1 == '\\') goto do_cell_tail;
 
 /* case 4: lib name non escaped ID */
 if (!chk_libid(s1)) { strcpy(libnam, ""); return(FALSE); }
 strcpy(celnam, s1);
 return(TRUE);
}

/*
 * read a use clause and ending SEMI
 *
 * know use keyword read and reads ending SEMI unless error where resync 
 * on error return F and set libnam and cell name to empty
 */
static int32 rd_use_clause(FILE *fp, char *libnam, char *celnam,
 int32 *expl_config)
{
 int32 ttyp, ttyp2, has_cfg_suffix;

 strcpy(libnam, "");
 strcpy(celnam, "");

 if ((ttyp = __get_cfgtok(fp)) != CFG_ID)
  {
   __pv_ferr(3542,
    "config use clause not followed by use specifier - %s read",
    __to_cfgtoknam(__xs, ttyp));
   ttyp2 = cfg_skipto_semi_endconfig(ttyp, fp);
   return(ttyp2);
  }
 /* this always sets has cfg suffix */  
 if (!extract_use_nam(libnam, celnam, &has_cfg_suffix, __token))
  {
   __pv_ferr(3546,
    "config use clause %s illegal - [lib].[cell] or [cell]:config allowed - P1364 disallows configs in library source files",
    __token);
  }
 *expl_config = has_cfg_suffix;

 if ((ttyp = __get_cfgtok(fp)) != CFG_SEMI)
  {
   __pv_ferr(3544,
    "config use clause not followed by semicolon - %s read",
    __to_cfgtoknam(__xs, ttyp));
   ttyp = cfg_skipto_semi_endconfig(ttyp, fp);
   return(ttyp);
  }
 return(SEMI);
}

/*
 * extract a use clause cell identifier
 * format: <lib name>[cell type name]<:config>
 * 
 * if lib name is omitted parent (current) cell's lib used
 * if :config used, the use config matching [cell type name] for binding
 */
static int32 extract_use_nam(char *libnam, char *celnam, int32 *has_config,
 char *use_spec)
{
 char *chp;
 char s1[IDLEN], s2[IDLEN];

 strcpy(libnam, "");
 strcpy(celnam, "");
 *has_config = FALSE;

 /* case 1: library omitted and escaped cell name */
 if (*use_spec == '\\')
  {
   strcpy(s2, use_spec); 

do_cell_tail:
   if ((chp = strchr(use_spec, ' ')) == NULL) return(FALSE);
   strncpy(celnam, use_spec, chp - use_spec);
   celnam[chp - use_spec] = '\0';
   /* checking esc ID but for now will never fail */
   if (!chk_escid(s2)) return(FALSE); 
   strncpy(s1, &(use_spec[1]), chp - use_spec - 2);
   s1[chp - use_spec - 2] = '\0';
   strcpy(celnam, s1);
   chp++;
   if (*chp == ':') 
    {
     if (strcmp(chp, ":config") != 0) return(FALSE);
     /* SJM 05/18/04 - :config hierarchical config indirection indicator */ 
     /* can't be used with library name since library are for Verilog src */
     if (strcmp(libnam, "") != 0) return(FALSE);
     *has_config = TRUE;
    }
   else 
    {
     if (*chp != '\0') return(FALSE);
    }
   return(TRUE);
  }
 /* if lib name before '.' present, check and fill */
 if ((chp = strchr(use_spec, '.')) != NULL)
  { 
   strncpy(s1, use_spec, chp - use_spec);
   s1[chp - use_spec] = '\0';
   if (!chk_libid(s1)) return(FALSE);
   strcpy(libnam, s1);
   chp++;
   strcpy(s1, chp);
  }
 else strcpy(s1, use_spec);
 
 /* case 3: lib name present and escaped ID */
 if (*s1 == '\\') goto do_cell_tail;
 
 /* case 4: lib name non escaped ID */
 if ((chp = strchr(s1, ':')) == NULL)
  {
   if (!chk_libid(s1)) { strcpy(libnam, ""); return(FALSE); }
   strcpy(celnam, s1);
   return(TRUE);
  }
 /* :config suffix present */
 if (strcmp(chp, ":config") != 0) return(FALSE);

 strncpy(s2, s1, chp - s1);
 s2[chp - s1] = '\0';
 if (!chk_libid(s2)) return(FALSE);
 strcpy(celnam, s2);

 /* SJM 05/18/04 - :config hierarchical config indirection indicator */ 
 /* can't be used with library name since library are for Verilog src */
 if (strcmp(libnam, "") != 0) return(FALSE);

 *has_config = TRUE;
 return(TRUE);
}

/*
 * read a liblist non comma separated list of libraries
 *
 * know liblist keyword read and reads first libr and keeps reading lib
 * names (no wildcards) until ending semicolon read (i.e. list ends with ;
 * and no commas)
 *
 * library names are simple IDs
 * even if error continues reading to ; or EOF
 */
static struct cfgnamlst_t *rd_liblist(FILE *fp)
{
 int32 ttyp;
 struct cfgnamlst_t *lbp, *lbp_hd, *lbp_tail;

 lbp_hd = lbp_tail = NULL;
 for (;;)
  {
   ttyp = __get_cfgtok(fp);
   if (ttyp == CFG_SEMI) break; 

   if (ttyp != CFG_ID)
    {
     __pv_ferr(3562, "config liblist library name expected - %s read",
      __to_cfgtoknam(__xs, ttyp));
     cfg_skipto_semi(ttyp, fp);
     return(NULL);
    }
   if (!chk_libid(__token))
    {
     __pv_ferr(3563,
      "config liblist library name %s illegal - must be simple Verilog ID",
      __token);
    }
   lbp = (struct cfgnamlst_t *) __my_malloc(sizeof(struct cfgnamlst_t)); 
   lbp->nam = __pv_stralloc(__token);
   lbp->cnlnxt = NULL; 
   if (lbp_hd == NULL) lbp_hd = lbp_tail = lbp;
   else { lbp_tail->cnlnxt = lbp;  lbp_tail = lbp; }
  }
 return(lbp_hd);
}

/*
 * LOW LEVEL ROUTINES FOR CFG INITIALIZATION AND ERROR RECOVERY  
 */

/*
 * initialize a cfg lib record
 */
static void init_cfglib(struct cfglib_t *lbp)
{
 lbp->lbsrc_rd = FALSE;
 lbp->lbname = NULL;
 lbp->lbels = NULL;
 lbp->lbnxt = NULL;
}

/*
 * initialize a cfg block record
 */
static void init_cfg(struct cfg_t *cfgp)
{
 cfgp->cfgnam = NULL;
 cfgp->cfgdeslist = NULL;
 cfgp->cfgrules = NULL;
 cfgp->cfgdflt = NULL;
 cfgp->cfg_fnam = NULL;
 cfgp->cfg_lno = -1;
 cfgp->cfgnxt = NULL;
}

/*
 * cfg get token error recovery skip to semi
 *
 * notice config token number not related to source reading numbers
 * but using __token global for names still
 */
static int32 cfg_skipto_semi(int32 ttyp, FILE *fp)
{
 for (;;) 
  {
   if (ttyp == CFG_SEMI || ttyp == CFG_EOF) break;
   ttyp = __get_cfgtok(fp);
  }
 return(ttyp);
}

/*
 * cfg get token error recovery skip to semi or comma
 *
 * notice config token number not related to source reading numbers
 * but using __token global for names still
 */
static int32 cfg_skipto_comma_semi(int32 ttyp, FILE *fp)
{
 for (;;) 
  {
   if (ttyp == CFG_SEMI || ttyp == CFG_EOF) break;
   ttyp = __get_cfgtok(fp);
  }
 return(ttyp);
}

/*
 * cfg get token error recovery skip to semi or endconfig
 *
 * notice config token number not related to source reading numbers
 * but using __token global for names still
 */
static int32 cfg_skipto_semi_endconfig(int32 ttyp, FILE *fp)
{
 for (;;) 
  {
   if (ttyp == CFG_SEMI || ttyp == CFG_ENDCFG || ttyp == CFG_EOF) break;
   ttyp = __get_cfgtok(fp);
  }
 return(ttyp);
}


/*
 * cfg get token error recovery skip 
 *
 * notice config token number not related to source reading numbers
 */
static int32 cfg_skipto_eof(int32 ttyp, FILE *fp)
{
 for (;;) 
  {
   if (ttyp == CFG_EOF) break;
   ttyp = __get_cfgtok(fp);
  }
 return(ttyp);
}

/*
 * ROUTINES TO EXPAND AND REPLACE LIBRARY WILDCARD FILE LISTS
 */

/* names for the special wildcard characters - see LRM */
#define STAR 1
#define QMARK 2
#define HIER 3

/*
 * return TRUE if the string contains a wildcard
 * '*', '?', '...', or ending in a / => TRUE
 */
static int32 has_wildcard(char *cp)
{
 int32 i, slen;

 slen = strlen(cp);
 /* if it ends in a slash return TRUE - include all case */
 if (cp[slen -1] == '/') return(TRUE);
 for (i = 0; i <= slen - 1; i++, cp++)
  {
   if (*cp == '*') return(TRUE);
   if (*cp == '?') return(TRUE);
   if (i < slen + 2 && strncmp(cp, "...", 3) == 0) return(TRUE);
  }
 return(FALSE);
}

/*
 * expand all wild cards in library file name lists
 *
 * first step in cfg elaboration after all map and cfg files read
 */
extern void __expand_lib_wildcards(void)
{
 int32 sav_lin_cnt;
 struct cfglib_t *lbp;
 struct libel_t *lbep;
 char *sav_cur_fnam, *cp;
 FILE *fp;

 /* expand for library */
 for (lbp = __cfglib_hd; lbp != NULL; lbp = lbp->lbnxt)
  {
   sav_lin_cnt = __lin_cnt;
   sav_cur_fnam = __cur_fnam;
   __cur_fnam = lbp->cfglb_fnam;
   __lin_cnt = lbp->cfglb_lno;

   /* for each fspec in one library's fspec list, expand any wildcards */
   for (lbep = lbp->lbels; lbep != NULL; lbep = lbep->lbenxt)
    {
     /* AIV mark the expanded so the pattern string is replaced */
     lbep->expanded = FALSE;
     cp = lbep->lbefnam;
     /* if it doesn't contain a wildcard char must be a file so simple open */
     if (!has_wildcard(cp))
      {
       /* if it returns NULL file no such file */
       if ((fp = __tilde_fopen(cp, "r")) == NULL)
        {
         __pv_ferr(3564, "config library %s unable to match pattern %s\n",
          lbp->lbname, cp); 
        }
       else 
        {
         /* no need to change the file name, just mark the flag as expanded */
         lbep->expanded = TRUE;
         /* close the open file */
         __my_fclose(fp); 
        }
      }
     else if (strcmp(cp, "...") == 0)
      {
       /* include all files below the current directory */
       if (!expand_single_hier(lbp, lbep, NULL))
        {
         __pv_ferr(3564, "config library %s unable to match pattern %s\n",
          lbp->lbname, cp); 
        }
      }
     else 
      {
        /* match the pattern case */
        expand_dir_pats(lbp, lbep, cp);
      }
   }
   /* put back for further reading */
   __lin_cnt = sav_lin_cnt;
   __cur_fnam = sav_cur_fnam;
  }
}

/*
 * match a hier name with the given pattern name
 */
static int32 match_hier_name(struct xpndfile_t *xfp_hd, char *name) 
{
 char *cp, *last;
 char str[RECLEN]; 
 struct xpndfile_t *xfp;
 
 /* skip past ./ meaningless */
 if (name[0] == '.' && name[1] == '/') name += 2;
 last = name;
 xfp = xfp_hd; 
 cp = strchr(name, '/');
 if (cp == NULL)
  {
   /* Special case ../../\*.v  - last pattern and matches wildcard */
   if (xfp->xpfnxt == NULL && match_wildcard_str(name, xfp)) return(TRUE);
   /* Special case .../\*.v  */
   else if (xfp->wildcard == HIER && xfp->xpfnxt->xpfnxt == NULL 
    && match_wildcard_str(name, xfp->xpfnxt)) return(TRUE);
  }
 else
  {
   for (; xfp != NULL && cp != NULL; cp = strchr(cp, '/'))
    {
     /* check the string to the next '/' to match the pattern */
     /* copy /string/ into str to check with pattern */
     strncpy(str, last, cp - last); 
     str[cp-last] ='\0';
     /* if doesn't match pattern return */
     if (!match_wildcard_str(str, xfp)) return(FALSE);
     /* handle special ... case */
     if (xfp->wildcard == HIER)
      { 
       /* no more patterns it is a match */
       if (xfp->xpfnxt == NULL) return(TRUE);

       /* match all the remaining patterns after .../ */
       /* move pattern up one and get the next /string/ */
hier:
       xfp = xfp->xpfnxt;
       for (; cp != NULL;  )
        {
         /* special case it is the last one */
         if ((cp - last) == 0) strcpy(str, cp);
         else
          {
           strncpy(str, last, cp - last); 
           str[cp-last] ='\0';
          }
         /* if matches continue */
         if (match_wildcard_str(str, xfp))
          {
           xfp = xfp->xpfnxt; 
           if (xfp == NULL) return(TRUE);
          }
         last = ++cp;
         /* last pattern in the string dir/dir2/lastpattern */
         if ((cp = strchr(cp, '/')) == NULL)
          {
           /* if more patterns continue */
           if (xfp->xpfnxt != NULL) return(FALSE); strcpy(str, last); 
           /* match the lastpattern and gets here it is a match */
           if (match_wildcard_str(str, xfp)) return(TRUE);
          }
        }
      }
     last = ++cp;

     /* include all in the directory and the last in the char name */ 
     if (xfp->incall && strchr(cp, '/') == NULL) return(TRUE);

     /* if the last pattern and didn't match FALSE  */ 
     xfp = xfp->xpfnxt; 
     if (xfp == NULL)  return(FALSE);
     if (xfp->wildcard == HIER && xfp->xpfnxt != NULL) goto hier;
     /* try to match the last of the string */ 
     if (*cp != '\0' && strchr(cp, '/') == NULL)
      {
       if (xfp->xpfnxt == NULL && match_wildcard_str(cp, xfp)) return(TRUE);
       else return(FALSE);
      }
    }
  }
 return(FALSE);
}

/*
 * match the special hierarchical wildcard in the pattern
 * is recursive call which takes the parameters -
 *
 * xfp_hd - the start of the split pattern to match 
 * bpath - the beginning part of the path (the non-wildcard start of the path) 
 * path - the current path
 *
 * builds the strings to match according to attempt to match to the xfp list 
 */
static void find_hier(struct libel_t *lbep, struct xpndfile_t *xfp_hd, 
 char *bpath, char *path)
{
 char str[RECLEN];
 char str2[RECLEN];
 char dirstr[RECLEN];
 char *cp;
 DIR *dp;
 struct dirent *dir;
  
 /* start from the current directory */
 if (path == NULL) { strcpy(str, "."); cp = str; }
 else cp = path;

 if ((dp = opendir(cp)) == NULL)
  {
   __pv_ferr(1368, "during config library expansion cannot open dir %s : %s\n",
    cp, strerror(errno)); 
  }
 
 while ((dir = readdir(dp)) != NULL)
  {
   if (dir->d_ino == 0) continue;
   if (strcmp(dir->d_name, ".") == 0) continue;
   if (strcmp(dir->d_name, "..") == 0) continue;
   if (dir->d_type == DT_DIR)
    {
     /* directory concat name and call recursively */
     if (path == NULL) sprintf(dirstr, "./%s", dir->d_name);
     else sprintf(dirstr, "%s/%s", path, dir->d_name);
     find_hier(lbep, xfp_hd, bpath, dirstr);
    }
   else if (dir->d_type == DT_REG)
    {
     str[0] ='\0';
     /* concat the file name to the directory */
     if (path == NULL) strcpy(str, dir->d_name);
     else sprintf(str, "%s/%s", cp, dir->d_name);
     /* check if the name matches the xfp list */
     if (match_hier_name(xfp_hd, str))
      {
       if (bpath != NULL)
        {
         sprintf(str2, "%s/%s", bpath, str);
         expand_libel(lbep, str2);
        }
       else expand_libel(lbep, str);
      }
    }
  }
 if (dp != NULL) closedir(dp);
}

/*
 * routine to actually do the hierarchical search 
 * moves to the first wildcard xfp and does search 
 */
static void expand_hier_files(struct cfglib_t *lbp, struct libel_t *lbep,
 struct xpndfile_t *xfp_hd)
{
 char dirstr[RECLEN];
 char bpath[RECLEN];
 char tmp[RECLEN];
 int32 first;
 
 /* if the first xfp has a wildcard do the search do search with current xfp */ 
 if (xfp_hd->wildcard) 
  {
   find_hier(lbep, xfp_hd, NULL, NULL);
   return;
  }
 first = TRUE;
 /* save current dir */
 getcwd(dirstr, RECLEN); 
 strcpy(bpath, "");
 while (!xfp_hd->wildcard && xfp_hd->incall != TRUE) 
  {
   if (chdir(xfp_hd->fpat) < 0)
    {
     if (first)
      {
       __pv_ferr(3564, "config library %s no such directory %s\n",
       lbp->lbname, xfp_hd->fpat); 
      }
     else
      {
       __pv_ferr(3564, "config library %s no such directory %s/%s\n",
        lbp->lbname, bpath, xfp_hd->fpat);
       chdir(dirstr);
       return;
      }
    }
   /* move to non-wildcard dir and buld beginning path name */
   if (first)
    {
     strcpy(bpath, xfp_hd->fpat);
     first = FALSE;
    }
   else
    {
     strcpy(tmp, bpath);
     sprintf(bpath, "%s/%s", tmp, xfp_hd->fpat);
    }
   xfp_hd = xfp_hd->xpfnxt;
  }
 /* do the search */
 find_hier(lbep, xfp_hd, bpath, NULL);
 /* go back to the original dir  */
 chdir(dirstr);
}

/*
 * routine to break up the original user pattern by '/' - xfp1/xfp2/xfpn
 */
static void expand_dir_pats(struct cfglib_t *lbp, struct libel_t *lbep,
 char *pat)
{
 int32 slen, i, ndx, clevel, last_star;
 int32  wildcard, hier, cur_hier, last_hier, back_dir;
 char str[RECLEN]; 
 char *last, *cp;
 struct xpndfile_t *xfp, *xfp2, *xfp_hd, *xfp_tail;

 str[0] = '\0';
 clevel = -1;
 xfp_hd = xfp_tail = NULL;
 slen = strlen(pat);
 cp = last = pat;
 last_star = last_hier = wildcard = FALSE;
 back_dir = cur_hier = hier = FALSE;
 /* ndx if current index of the string */
 ndx = 0;
 for (i = 0; i < slen; i++, ndx++, cp++)
  {
   /* split add a xfp to the list */
   if (*cp == '/')
    {
     cur_hier = FALSE;
     /* special verilog escape char */
     if (i + 1 < slen && *(cp+1) == '/') 
      {
       /* LOOKATME FIXME - check if this works */
       /* special espcaped char // read until next ' ' or end of str */
       i++;
       cp++;
       for (; i < slen && *cp != ' '; i++, cp++) ;
      }
     /* skip a /./ since it doesn't do anything */
     if (ndx == 1 &&  str[0] == '.') { last = (cp + 1); continue; }
     str[ndx] = '\0'; 
     if (ndx == 3 && strcmp(str, "...") == 0) 
      {
       /* if ... and so was the last skip this one */
       if (last_hier)
        {
         __pv_warn(3124, "config can't have .../... - treating as only one\n");
         ndx = -1;
         continue;
        }
       cur_hier = hier = TRUE;
      }
     else if (ndx == 2 && back_dir && strcmp(str, "..") == 0)
      {
       __pv_warn(3125,
        "Back directory '..' can only be used at the beginning of pattern string\n");
      }
      /* AIV 05/25/04 - on the first non '..' set back_dir to true */
      /* there can be multilple ../.. prior to the pattern */
     else if(ndx != 2 || strcmp(str, "..") != 0)
            back_dir = TRUE;

     xfp = (struct xpndfile_t *) __my_malloc(sizeof(struct xpndfile_t)); 
     xfp->fpat = __pv_stralloc(str);
     if (cur_hier) 
      {
       /* set the wildcar to hierarch */
       xfp->wildcard = HIER;
       last_hier = TRUE;
      }
     else
      {
       /* set the wildcar STAR or QMARK */
       xfp->wildcard = wildcard;
       last_hier = FALSE;
      }
     xfp->nmatch = 0; 
     /* special case that ends in '/' inc all the files */
     if (i + 1 == slen) xfp->incall = TRUE; 
     else xfp->incall = FALSE; 
     xfp->xpfnxt = NULL; 

     /* set the current depth level */
     xfp->level = ++clevel;
     if (xfp_hd == NULL) xfp_hd = xfp_tail = xfp;
     else { xfp_tail->xpfnxt = xfp;  xfp_tail = xfp; }

     /* set the last char to one past the / */
     if (i < slen) last = (cp + 1);
     /* reset wildcard and last_star and string index */
     wildcard = FALSE;
     last_star = FALSE;
     ndx = -1;
    }
   else if (*cp == '*')
    {
     /* previous chars was star as well so just set ndx back one to skip */
     if (last_star) ndx--;
     last_star = TRUE;
     wildcard = STAR;
     /* AIV 05/18/04 - can never be negative since last_star is a flag */
     /* that can only be set when ndx > 0 */
//AIV? 02-09-09 ???? LINT IS COMPLAINING about negative index here
     str[ndx] = *cp;
    }
   else
    {
     /* star takes wildcard precedence over qmark - needed for pat matching */
     if (*cp == '?' && wildcard != STAR) wildcard = QMARK;
     last_star = FALSE;
     str[ndx] = *cp;
    }
  } 
 /* LOOKATME will /a still work */
 /* add the last one this has to be a file or file pattern */
 cur_hier = FALSE;
 if (cp != last)
  {
   if (ndx == 1 && *(cp - 1) == '.') goto done;
   str[ndx] = '\0'; 
   if (strcmp(str, "...") == 0) 
    {
     /* just skip the last ... if there is two in a row */
     if (last_hier) goto done; cur_hier = hier = TRUE;
    }
   xfp = (struct xpndfile_t *) __my_malloc(sizeof(struct xpndfile_t)); 
   xfp->fpat = __pv_stralloc(str);
   if (cur_hier) xfp->wildcard = HIER;
   else xfp->wildcard = wildcard;
   xfp->nmatch = 0; 
   xfp->xpfnxt = NULL; 
   xfp->level = ++clevel;
   if (xfp_hd == NULL) xfp_hd = xfp_tail = xfp;
   else { xfp_tail->xpfnxt = xfp;  xfp_tail = xfp; }
  }

 /* DGB REMOVE */
 if (xfp_hd == NULL) __misc_terr(__FILE__, __LINE__);

done:
 /* doesn't contain a hieracrh ... */
 if (!hier)
  {
   /* if the first xfp contains a wildcard just call match overwise */
   /* move to on wildcard dir and then match */ 
   if (xfp_hd->wildcard) match_dir_pats(lbep, xfp_hd, NULL, NULL, FALSE, 0); 
   else movedir_match_dir_pats(lbep, xfp_hd); 
  }
 else
  {
   /* match the hier case */
   expand_hier_files(lbp, lbep, xfp_hd); 
  }
 /* free xfp list */
 /* SJM 11/05/04 - need 2nd pointer since xpfnxt can't be accessed */
 /* after freed */
 for (xfp = xfp_hd ; xfp != NULL;)
  {
   xfp2 = xfp->xpfnxt;
   __my_free(xfp, sizeof(struct xpndfile_t ));
   xfp = xfp2; 
  }
}

/*
 * move xfp_hd to the first wildcard to start the search
 */
static void movedir_match_dir_pats(struct libel_t *lbep, 
 struct xpndfile_t *xfp_hd) 
{
 int32 level;
 char dirstr[RECLEN]; 
 char bpath[RECLEN]; 

 level = 0;
 /* save current directory */
 getcwd(dirstr, RECLEN); 
 while (!xfp_hd->wildcard && xfp_hd->incall != TRUE) 
  {
   if (chdir(xfp_hd->fpat) < 0)
    {
     /* SJM 05/11/04 - FIXME ### ??? - need way to locate these */
     /* AIV 05/18/04 if the currect level print current pattern name */
     if (level == 0)
      { 
       __pv_warn(3132, "no such directory %s\n", xfp_hd->fpat);
      }
     else
      {
      /* if lower level print all previous path and current pattern name */
       __pv_warn(3132, "Error - no such directory path %s/%s\n",
        bpath, xfp_hd->fpat);
      }
     chdir(dirstr);
     return;
    }
   /* goto the next directory and inc the depth level */
   if (level == 0) strcpy(bpath, xfp_hd->fpat);
   else sprintf(bpath, "%s/%s", bpath, xfp_hd->fpat);
   level++;
   xfp_hd = xfp_hd->xpfnxt;
  }
 /* search directories */
 match_dir_pats(lbep, xfp_hd, NULL, bpath, FALSE, level); 
 /* do back to the current directory */
 chdir(dirstr);
}

/*
 * match the patterns for each xfp->fpat per directory
 *
 * xfp_hd - points to the first wildcard name1/ 
 * bpath - start of path not containing a wildcard 
 * path - points to all current path 
 * incall - is the flag to include all the files in the dir, end in '/'
 */
static void match_dir_pats(struct libel_t *lbep, struct xpndfile_t *xfp_hd,
char *path, char *bpath, int32 incall, int32 level) 
{
 char dirstr[RECLEN]; 
 char str[RECLEN]; 
 char str2[RECLEN]; 
 char *cp; 
 struct xpndfile_t *xfp;
 struct dirent *dir;
 DIR *dp;
     
 /* if it's null just add the ./ */
 if (path == NULL) { strcpy(str, "./"); cp = str; }
 else cp = path;

 xfp = xfp_hd; 
 dp = NULL;
 for (; xfp != NULL; xfp = xfp->xpfnxt)
  {
   /* if the xfp->level is greater than the current level return */
   if (xfp->level > level) return;
   if ((dp = opendir(cp)) == NULL)
    {
     __pv_ferr(3569, "in config libary file %s cannot open dir %s : %s\n",
      lbep->lbefnam, cp, strerror(errno)); 
     return;
    }
   while ((dir = readdir(dp)) != NULL)
    {
     if (dir->d_ino == 0) continue;
     if (strcmp(dir->d_name, ".") == 0) continue;
     /* handle directories */
     if (dir->d_type == DT_DIR)
      {
       /* if not include all and it matches the wildcard go to next dir */
       if (!incall && match_wildcard_str(dir->d_name, xfp))
        {
         /* path is null copy else concat dir name */
         if (path == NULL) sprintf(dirstr, "%s", dir->d_name);
         else sprintf(dirstr, "%s/%s", path, dir->d_name);
         /* if include all (end's in /) include all files of dir */
         if (xfp->incall)
          {
           match_dir_pats(lbep, xfp, dirstr, bpath, TRUE, level + 1);
          }
         else
          {
           match_dir_pats(lbep, xfp->xpfnxt, dirstr, bpath, incall,
            level + 1);
          }
         /* if no wildcard and doesn't end in / return */
         if (!xfp->wildcard && !xfp->incall) return;
        }
      }
     else if (dir->d_type == DT_REG)
      {
       /* handle files */
       /* if not include all in current directory */ 
       if (!incall)
        {
         /* if another pattern to macth or pattern ends in / continue */ 
         if (xfp->xpfnxt != NULL || xfp->incall) continue;
 
         /* if doesn't match the wildcard continue */ 
         if (!match_wildcard_str(dir->d_name, xfp)) continue;
        }
       /* if it gets here include the file */
       if (path == NULL) sprintf(str, "%s", dir->d_name);
       else sprintf(str, "%s/%s", cp, dir->d_name);
       if (bpath != NULL)
        {
         sprintf(str2, "%s/%s", bpath, str);
         expand_libel(lbep, str2);
        }
       else expand_libel(lbep, str);
      }
    }
  }
 if (dp != NULL) closedir(dp);
}

/*
 * routine to return T if a wildcard pattern matches a file name 
 * matches '...', '*', '?'
 * or file name with any of the wild chars
 */
static int32 match_wildcard_str(char *file, struct xpndfile_t *xfp) 
{
 int32 fndx, pndx, flen, plen; 
 int32 ondx, wildcard;
 char *opat, *patp, *filep;

 patp = xfp->fpat;
 wildcard = xfp->wildcard;
 /* if hier include all patterns */
 if (wildcard == HIER || strcmp(patp, "*") == 0) return(TRUE);
 
 /* if string is an exact match return true */
 if (strcmp(file, patp) == 0) return(TRUE);
 /* if it doesn't have a wildcard return */
 if (!xfp->wildcard) return(FALSE);

 flen = strlen(file);
 plen = strlen(patp); 
 
 /* special case if it has a star at the end match exact file - start */
 if (wildcard == STAR && flen == plen - 1 && xfp->fpat[plen-1] == '*')
  {
   if (strncmp(file, xfp->fpat, flen) == 0) return(TRUE);
  }
 filep = file;
 fndx = ondx = 0;
 /* skip the regular characters */
 while (*patp != '?' && *patp != '*') 
  {
   if (*filep != *patp) return(FALSE);
   filep++;
   patp++;
   fndx++;
   ondx++; 
  }
 
 /* reset used for * can to reset to location of last special char */
 opat = patp;

reset:
 patp = opat;
 pndx = ondx;
 for (; fndx < flen && pndx < plen; fndx++, pndx++, filep++, patp++)
  {
   /* if strings are equal or '?' goto the next char */
   if (*filep == *patp || *patp == '?') continue;
   else if (*patp == '*')
    {
     /* special case the \*\*\?\?  */
     if (*(patp + 1) == '?')
      {
       opat = (patp + 1);
       ondx = pndx + 1;
       patp++;
       pndx++;
       while (*patp == '?' && pndx < plen && fndx < flen)
        { fndx++, pndx++, filep++, patp++; }
       /* matching chars return */
       if (pndx == plen) return(TRUE);
       goto reset;
      }
     opat = patp; ondx = pndx;
     /* if a star case just move pattern to next char */
     while (*patp == '*' && pndx < plen)
      { 
       patp++; pndx++; 
      }
     if (pndx == plen) return(TRUE);

     /* if a qmark just continue and match the next char */
     if (*patp == '?') continue;

     /* while not equal move file forward */
     while (fndx < flen && *filep != *patp)
      { filep++; fndx++; }
     
     /* reached the end without finding an equal char */
     if (fndx == flen &&  *filep != *patp) return(FALSE);
     if (*filep != *patp && fndx < flen){filep++; fndx++; goto reset; }
    }
   /* if not eq, '?', or '*' doesn't match*/
   else if (fndx < flen && wildcard == STAR) goto reset;
   else return(FALSE);
  }
 if (fndx < flen && wildcard == STAR) goto reset;
 /* if string reaches the end it is a match */
 if (flen == fndx)
  {
   if (pndx == plen) return(TRUE);
   /* special case patp ends in the '*' */ 
   else if (pndx == plen - 1 && *patp == '*') return(TRUE);
  }
 return(FALSE);
} 

/*
 * expand the lib element
 */
static void expand_libel(struct libel_t *lbep, char *file)
{
 struct libel_t *newlbp;

 /* if F replace the pattern name with the expanded file name */
 if (!lbep->expanded)
  {
   /* only rename/free if it isn't the orginal string */
   /* there is no wildcard so the same stays the same */
   if (lbep->lbefnam != NULL)
    {
     __my_free(lbep->lbefnam, strlen(lbep->lbefnam) + 1);
     lbep->lbefnam = (char *) __pv_stralloc(file);
    }
   lbep->expanded = TRUE;
  }
 else
  {
   /* link on a new expanded file name  */
   newlbp = (struct libel_t *) __my_malloc(sizeof(struct libel_t));
   memcpy(newlbp, lbep, sizeof(struct libel_t));
   newlbp->lbefnam = (char *) __pv_stralloc(file);
   lbep->lbenxt = newlbp;
   lbep = newlbp;
   lbep->expanded = TRUE;
  }
}

/*
 * return to expand all patterns underneath hierarchy
 *
 * if pattern is only '...' return all files below the current path
 * recursively calls itself returning all files
 */
static int32 expand_single_hier(struct cfglib_t *lbp, struct libel_t *lbep,
 char *path)
{
 int32 count;
 char str[RECLEN];
 char dirstr[RECLEN];
 char *cp;
 DIR *dp;
 struct dirent *dir;

 if (path == NULL) { strcpy(str, "."); cp = str; }
 else cp = path;

 count = 0;
 if ((dp = opendir(cp)) == NULL)
  {
   __pv_ferr(3569, "in config libary %s cannot open dir %s : %s\n",
    lbp->lbname, cp, strerror(errno)); 
   return(0);
  }
 while ((dir = readdir(dp)) != NULL)
  {
   if (dir->d_ino == 0) continue;
   if (strcmp(dir->d_name, ".") == 0) continue;
   if (strcmp(dir->d_name, "..") == 0) continue;
   if (dir->d_type == DT_DIR)
    {
     if (path == NULL) sprintf(dirstr, "./%s", dir->d_name);
     else sprintf(dirstr, "%s/%s", path, dir->d_name);
     expand_single_hier(lbp, lbep, dirstr);
    }
   else if (dir->d_type == DT_REG)
    {
     str[0] ='\0';
     if (path == NULL) sprintf(str, "%s", dir->d_name);
     else sprintf(str, "%s/%s", cp, dir->d_name);
     count++;
     expand_libel(lbep, str);
    }
  }
 if (dp != NULL) closedir(dp);
 return(count);
}

/*
 * ROUTINES TO READ CFG LIBRARY SPECIFIED VERILOG SOURCE
 */

/*
 * read and bind cells as directed by previously read  config block
 *
 * reads cfg design statement and then read libraries according to cfg rules
 * user must not give and .v files on command line
 */
extern void __rd_ver_cfg_src(void)
{
 struct cfg_t *cfgp;
 
 /* SJM 05/18/04 - LOOKATME - why doesn't this test work? */
 /* ### if (__last_inf != __cmd_ifi) __misc_terr(__FILE__, __LINE__); */

 prep_cfg_vflist();

 if (__cfg_verbose) dump_config_info();

 for (cfgp = __cfg_hd; cfgp != NULL; cfgp = cfgp->cfgnxt)
  {
   if (__cfg_verbose)
    {
     __cv_msg("BINDING RULES IN CONFIG %s \n",  cfgp->cfgnam);
    }
   bind_cfg_design(cfgp, FALSE);
  }

 /* AIV 05/24/04 - free and link out of mod list all cfg lib modules */
 /* that are in scanned files but never instantiated */
 free_unused_cfgmods();
}

/*
 * cfg verbose routine to dump names of expanded library files
 */
static void dump_lib_expand(void)
{
 struct cfglib_t *lbp;
 struct libel_t *lbep;

 __cv_msg("  Library expasion file names:\n");
 for (lbp = __cfglib_hd; lbp != NULL; lbp = lbp->lbnxt)
  {
   __cv_msg("  Libname %s\n", lbp->lbname);
   for (lbep = lbp->lbels; lbep != NULL; lbep = lbep->lbenxt)
    {
     __cv_msg("    %s\n", lbep->lbefnam);
    }
  }
}

static void dump_config_info(void)
{
 char typ[RECLEN];
 struct cfg_t *cfgp;
 struct cfgdes_t *desp;
 struct cfgrule_t *rulp;
 struct cfgnamlst_t *cnlp;

 __cv_msg("\n  DUMPING CONFIG INFORMAION:\n");
 dump_lib_expand();
 for (cfgp = __cfg_hd; cfgp != NULL; cfgp = cfgp->cfgnxt)
  {
   __cv_msg("    Config %s in %s lineno %d \n", cfgp->cfgnam, cfgp->cfg_fnam, 
    cfgp->cfg_lno);

   /* dump design info */
   for (desp = cfgp->cfgdeslist; desp != NULL; desp = desp->desnxt)
    {
     __cv_msg("      Design %s \n", desp->deslbnam); 
    }

   /* dump rule default info */
   if (cfgp->cfgdflt != NULL) __cv_msg("    Default rule:\n"); 
   rulp = cfgp->cfgdflt;
   for (cnlp = rulp->rul_libs; cnlp != NULL; cnlp = cnlp->cnlnxt)
    {
     __cv_msg("      %s \n", cnlp->nam); 
    }

   /* dump rule info */
   for (rulp = cfgp->cfgrules; rulp != NULL; rulp = rulp->rulnxt)
    {
     __cv_msg("    Rule \n"); 
     if (rulp->rultyp == CFG_INSTANCE)
        strcpy(typ, "Instance");
     else
        strcpy(typ, "Cell");
     if (rulp->use_rule_cfg)
       __cv_msg("      %s %s using hierarchical config : %s\n", 
         typ, rulp->objnam, rulp->rul_use_celnam); 
     else if (rulp->is_use)
        __cv_msg("      %s %s use %s.%s\n", rulp->objnam, 
          typ, rulp->rul_use_libnam, rulp->rul_use_celnam); 
     else
      {
       __cv_msg("      %s %s liblist:\n", typ, rulp->objnam); 
       for (cnlp = rulp->rul_libs; cnlp != NULL; cnlp = cnlp->cnlnxt)
        {
         __cv_msg("       %s \n", cnlp->nam); 
        }
      }
    }
  }
 __cv_msg("  END CONFIG DUMP\n\n");
}

/*
 * prepare the cfg input file stack - never more than one cfg lib file 
 *
 * but macro expansions and `include put on top of stack so still needed
 * this puts one open file struct on tos and inits vinstk  
 */
static void prep_cfg_vflist(void)
{
 int32 fi;

 __last_lbf = __last_inf;
 /* set open file/macro exp./include stack to empty */
 for (fi = 0; fi < MAXFILNEST; fi++) __vinstk[fi] = NULL;
 __vin_top = -1;
 __lasttoktyp = UNDEF;
 __last_attr_prefix = FALSE;
 /* this builds the empty top of stack entry */
 __push_vinfil();
 __cur_infi = __last_inf;
}

/*
 * build error message if the module didn't match any in the
 * given library
 */ 
static void build_rule_error(struct cfg_t *cfgp, struct cfglib_t *cntxt_lbp, 
 struct cfgrule_t *rulp)
{
     
 /* if this didn't match there is no such instance */
 if (rulp->rultyp == CFG_INSTANCE)
  {
   __pv_err(3576, "config %s at %s: unable to bind rule - no such module %s",
    cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, rulp->rul_lno), 
    rulp->objnam);
  }
 else if (rulp->rultyp == CFG_CELL)
  {
   if (rulp->libnam != NULL)
    {
     /* no such library cell */ 
     __pv_err(3576,
      "config %s at %s: unable to bind rule - no such cell %s",
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, rulp->rul_lno), 
      rulp->objnam);
    } 
  }
}

/*
 * read source of and parse all cells in a design 
 *
 * SJM 01/09/04 FIXME ??? - must allow more than one top level design mod 
 */
static int32 bind_cfg_design(struct cfg_t *cfgp, int32 is_hier)
{
 struct cfgdes_t *desp;
 struct cfgrule_t *rulp;
 struct cfglib_t *lbp;
 struct mod_t *mdp;

 if (is_hier)
  {
   if (cfgp->cfgdeslist == NULL || cfgp->cfgdeslist->desnxt != NULL)
    {
     __pv_err(3571,
      "hierarchical config %s at %s - only one design statement allowed", 
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno));
     return(FALSE);
    }
  }

 for (desp = cfgp->cfgdeslist; desp != NULL; desp = desp->desnxt)
  {
   if (desp->deslbnam == NULL)
    {
     /* SJM 01/09/04 - FIXME - need to use default rule */
     __pv_err(3571, "config %s at %s: design library name missing",
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno));

     /* --- DBG remove -- */
     __misc_terr(__FILE__, __LINE__);
     /* --- */
    }

   if ((lbp = find_cfglib(desp->deslbnam)) == NULL)
    {
     __pv_err(3572, "config %s at %s: unable to find design library %s", 
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno),
      desp->deslbnam);
     continue;
    }
   desp->deslbp = lbp;
 
   /* find the top level module in library lbp and parse source of file it */ 
   /* is in - normally will be in file by itself */

   /* SJM 01/13/04 - may not be top mod but from config view work down */
   /* design modules can be non top mods (instantiated somewhere) but */   
   /* that just works because sub tree just gets bound */
   /* SJM 01/13/04 - FIXME - but that means inst and type names must be same */
   if (desp->topmodnam == NULL)
    {
     __pv_err(3573,
      "config %s at %s: top level design module name missing - for design lib %s", 
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno),
      desp->deslbnam);
     continue;
    }

   if ((mdp = find_cell_in_cfglib(desp->topmodnam, lbp)) == NULL)
    {
     __pv_err(3574,
      "config %s at %s: unable to find design top level module %s in library %s", 
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno),
      desp->topmodnam, desp->deslbnam);
     continue;
    }

   /* can't use undef hd list because only undef inst mod types from */
   /* the one design top mod added - rest of the mods must be read and */
   /* parsed but there cells can't be added to undef list */
 
   /* free undef list added from reading one config top level module */
   free_undef_list();
 
   __last_bind_comp_ndx = 0;
   __bind_inam_comptab[0] = __pv_stralloc(mdp->msym->synam);

   /* SJM 05/18/04 - binding of mdp uses current cfg library */
   mdp->mod_cfglbp = lbp;
   
   /* AIV rare case with instance/cell rules but no undefined mods */
   /* that means rules are not matched */
   if (mdp->mcells == NULL)
    {
     for (rulp = cfgp->cfgrules; rulp != NULL; rulp = rulp->rulnxt)
      {
       /* just warn because no cells need mapping */
       /* AIV LOOKATME message can msym be NULL here ?? */
       __pv_warn(3122,
        "config %s at %s: unable to bind rule - no modules to map in design %s module %s",
        cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, rulp->rul_lno),
        desp->deslbnam, mdp->msym != NULL ? mdp->msym->synam : "undefined");
      }
    }
   else
    {
     bind_cells_in1mod(cfgp, desp->deslbp, mdp);
     /* emit errors for hierarchical paths in rules that do not exist */
     for (rulp = cfgp->cfgrules; rulp != NULL; rulp = rulp->rulnxt)
      {
       if (!rulp->matched)
        {
         build_rule_error(cfgp, desp->deslbp, rulp);
        }
      }
    } 
   /* DBG remove -- */
   if (__last_bind_comp_ndx > 0) __misc_terr(__FILE__, __LINE__);
   /* -- */
   __my_free(__bind_inam_comptab[0], strlen(__bind_inam_comptab[0]) + 1);
   __last_bind_comp_ndx = -1;
  }
 return(TRUE);
}

/*
 * build a **<file>(<line. no.) reference for config where in fils not used
 * this chops file name so know will fit
 * s must be at least RECLEN wide
 */
extern char *__cfg_lineloc(char *s, char *fnam, int32 fnlcnt)
{
 char s1[RECLEN];

 sprintf(s, "**%s(%d)", __schop(s1, fnam), fnlcnt);
 return(s);
}

/*
 * find a library by name
 */
static struct cfglib_t *find_cfglib(char *lbnam)
{
 struct cfglib_t *lbp;

 for (lbp = __cfglib_hd; lbp != NULL; lbp = lbp->lbnxt) 
  {
   if (strcmp(lbp->lbname, lbnam) == 0) return(lbp);
  }
 return(NULL);
}

/*
 * free (empty) undef list
 *
 * because config file reading requires parsing all modules in any file
 * read, can't use undef hd list - must scan cells and resolve
 * from mcells whose mod type symbol is syundefmod
 */
static void free_undef_list(void)
{
 struct undef_t *undefp, *undefp2;

 /* final step is to free temp undef list */
 for (undefp = __undefhd; undefp != NULL;) 
  {
   undefp2 = undefp->undefnxt;
   __my_free(undefp, sizeof(struct undef_t)); 
   undefp = undefp2;
  }
 /* SJM 02/24/05 - must set tail to nil too */
 __undefhd = __undeftail = NULL;
}

/*
 * ROUTINES TO BIND CELLS
 */

/*
 * bind all cells inside one already bound module
 */
static void bind_cells_in1mod(struct cfg_t *cfgp, struct cfglib_t *cntxt_lbp,
 struct mod_t *mdp)
{
 struct cfgrule_t *rulp;
 struct libel_t *lbep;
 int32 cell_matched;
 struct cell_t *cp;
 struct sy_t *lbsyp;
 char *mnp;
 
 mdp->cfg_scanned = TRUE;
 for (cp = mdp->mcells; cp != NULL; cp = cp->cnxt)
  {
   if (!cp->cmsym->syundefmod) continue;
   cell_matched = FALSE;
   for (rulp = cfgp->cfgrules; rulp != NULL; rulp = rulp->rulnxt)  
    {
     if (!try_match_rule(cntxt_lbp, cp, rulp)) continue; 
  
     if (__cfg_verbose)
      {
       __cv_msg("  ** Rule matched for instance: %s (%s:%s) for rule config file: %s at line %d.\n\n",   
        cp->csym->synam, __in_fils[cp->cmsym->syfnam_ind], 
        mdp->msym->synam, cfgp->cfg_fnam, rulp->rul_lno);
      }
    
     if (cell_matched)
      {
       __pv_warn(3123, "config %s at %s: overriding previous defined matching rule(s)", 
        cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, rulp->rul_lno));
      }

     /* SJM 05/18/04 - cells inside bound to this lib (for %l) */
     mdp->mod_cfglbp = cntxt_lbp;
    
     cell_matched = TRUE;
     /* if it gets here the module exists so mark as TRUE */
     rulp->matched = TRUE; 
     if (!rulp->is_use)
      {
       if (!bind_liblist_rule(cfgp, cp, rulp))
        {
         /* AIV 06/01/04 - FIXME should print out the entire liblist */ 
         /* unable to match type of the ins mod in the specified library */
         __pv_err(3577,
          "config %s at %s: unable to bind instance rule - module type (%s) never found in liblist (line number %d)",
          cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, rulp->rul_lno),
          cp->cmsym->synam, rulp->rul_lno);
        }
      }
     else if (!bind_use_rule(cfgp, cntxt_lbp, cp, rulp))
      {
       /* Unable to match the use type of the mod in the specified lib */
       __pv_err(3578, "config %s at %s: unable to bind use rule - module type (%s) never found in library (%s)",
        cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, rulp->rul_lno),
        cp->cmsym->synam, rulp->objnam);
      }
     goto nxt_cell;
    }
 
   /* AIV if a file read via a rule, and in the file it contains mod 'foo' */
   /* it must also bind the 'foo' in the file without a rule */
   /* AIV LOOKATME ### ??? - is there a better way to do this */
   /* get the current file name */
   if (mdp->mod_last_ifi == - 1) goto nxt_cell; 
   mnp = __in_fils[mdp->mod_last_ifi]; 
   for (lbep = cntxt_lbp->lbels; lbep != NULL; lbep = lbep->lbenxt)
    {
     /* match the name of the expanded library file name */
     if (strcmp(lbep->lbefnam, mnp) == 0)
      {
       /* find the symbol to be bound in the library symbol table */
       if ((lbsyp = __get_sym(cp->cmsym->synam, lbep->lbel_sytab)) != NULL) 
        {
         /* bind the cell symbols */
         cp->cmsym = lbsyp;
         cp->cmsym->cfg_needed = TRUE;

         if (__cfg_verbose)
          {
           __cv_msg("  ++ Bound in config: %s\n      instance: %s (%s:%s) bound to cell: %s in module: %s from file: %s in library: %s (SCANNED).\n\n",  
            cfgp->cfgnam, cp->csym->synam, __in_fils[cp->csym->syfnam_ind], 
            cp->cmsym->synam, lbsyp->synam, mdp->msym->synam,
            mnp, cntxt_lbp->lbname);
          }
         /* cells inside bound to this lib (for %l) */
         cp->cmsym->el.emdp->mod_cfglbp = cntxt_lbp;

         /* if a module the unconnected module could have mods */
         /* that need to be connected as well  */
         /* if the connecting cell hasn't been sanned and is mod check it */
         if (!cp->cmsym->el.emdp->cfg_scanned && cp->cmsym->sytyp == SYM_M
          && mdp->mcells != NULL)
          {
           if (__cfg_verbose)
            {
             __cv_msg("Binding cells in module: %s in file: %s.\n",
              mdp->msym->synam, mnp);
            }
           if (++__last_bind_comp_ndx >= __siz_bind_comps) grow_bind_comps();
           __bind_inam_comptab[__last_bind_comp_ndx] = 
           __pv_stralloc(cp->csym->synam);

           /* bind cells in this one passing lib used to bind this one */
           bind_cells_in1mod(cfgp, cntxt_lbp, cp->cmsym->el.emdp);
           
           __my_free(__bind_inam_comptab[__last_bind_comp_ndx],
           strlen(__bind_inam_comptab[__last_bind_comp_ndx]) + 1);
           __last_bind_comp_ndx--;
          }
         goto nxt_cell;
        }
      }
    }

   /* must match rules in order */
   if ((rulp = cfgp->cfgdflt) != NULL)
    {
     /* notice default is always liblist form rule - never use form */
     if (bind_liblist_rule(cfgp, cp, rulp)) goto nxt_cell;
    }
   /* error message if cound not bind cell */
   __pv_err(3575,
    "config %s at %s: unable to bind cell %s (instance %s) (current lib %s in file %s:%d) - no rule matches",
    cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno),
    cp->cmsym->synam, cp->csym->synam, cntxt_lbp->lbname,
     __in_fils[cp->csym->syfnam_ind], cp->csym->sylin_cnt); 

   nxt_cell:;
  } 
}

/*
 * routine to attempt to match one rule and return T if matches
 * does not bind
 */
static int32 try_match_rule(struct cfglib_t *cntxt_lbp, struct cell_t *cp,
 struct cfgrule_t *rulp)
{
 int32 ci;
     
 if (rulp->rultyp == CFG_INSTANCE)
  {
   /* match inst */
   if (!cp->c_named) return(FALSE);

   if (strcmp(cp->csym->synam, rulp->inam_comptab[rulp->inam_comp_lasti])
    != 0) return(FALSE);

   /* if instance path length from config design root different */
   /* then can't match */
   if (__last_bind_comp_ndx + 1 != rulp->inam_comp_lasti) return(FALSE);

   for (ci = __last_bind_comp_ndx; ci >= 0; ci--)
    {
     if (strcmp(__bind_inam_comptab[ci], rulp->inam_comptab[ci]) != 0)
      return(FALSE);
    }
   return(TRUE);
  }
 else if (rulp->rultyp == CFG_CELL)
  {
   if (rulp->libnam != NULL && rulp->libnam[0] != '\0')
    {
     if (strcmp(rulp->libnam, cntxt_lbp->lbname) != 0) return(FALSE);
    }
   if (strcmp(cp->cmsym->synam, rulp->objnam) == 0) return(TRUE);
  }
 return(FALSE);
}

/*
 * bind instance rule with liblist clause - return T if succeeds else F
 */
static int32 bind_liblist_rule(struct cfg_t *cfgp, struct cell_t *cp,
 struct cfgrule_t *rulp)
{
 struct cfgnamlst_t *cnlp;
 struct cfglib_t *lbp;
 struct mod_t *bind_mdp;
 char s1[RECLEN];

 /* match every lib in lib list in order until find match or fail */
 for (cnlp = rulp->rul_libs; cnlp != NULL; cnlp = cnlp->cnlnxt)
  {
   /* find the current lib */
   if ((lbp = find_cfglib(cnlp->nam)) == NULL)
    {
     if (rulp->rultyp == CFG_DEFAULT)
       strcpy(s1, "default");
     else
       strcpy(s1, rulp->objnam);

     __pv_err(3571,
      "config %s at %s: binding object %s lib list clause library %s not found",
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno),
      s1, cnlp->nam);
     continue;
    }

   /* attempt to bind - cp is cell containing */
   if ((bind_mdp = find_cell_in_cfglib(cp->cmsym->synam, lbp)) == NULL)
    continue;
   
   /* AIV 05/18/04 - binding of mdp uses current cfg library */
   bind_mdp->mod_cfglbp = lbp;

   /* this does the binding */
   cp->cmsym = bind_mdp->msym;
   cp->cmsym->cfg_needed = TRUE;

   if (__cfg_verbose)
    {
     if (rulp->rultyp == CFG_DEFAULT) strcpy(s1, "default");
     else strcpy(s1, rulp->objnam);

     __cv_msg("  ++ Bound in config: %s\n      instance: %s (%s:%s) bound to cell: %s in library: %s (%s) (LIBLIST %s).\n\n",  
      cfgp->cfgnam, cp->csym->synam, __in_fils[cp->cmsym->syfnam_ind], 
      cp->cmsym->synam, bind_mdp->msym->synam,  lbp->lbname, 
      __in_fils[bind_mdp->msym->syfnam_ind], s1);
    }

   /* bind cells inside */
   bind_cells_inside(cfgp, cp, bind_mdp, lbp);
   return(TRUE);
  } 
 return(FALSE);
}

/*
 * bind use rule
 *
 * use clause - easy because [lib].cell explicitly given
 * SJM 01/14/03 - WRITEME - handle different cfg (:config)
 */
static int32 bind_use_rule(struct cfg_t *cfgp, struct cfglib_t *cntxt_lbp,
 struct cell_t *cp, struct cfgrule_t *rulp)
{
 struct cfg_t *use_replace_cfgp;
 struct cfglib_t *lbp;
 struct mod_t *bind_mdp;
 struct sy_t *msyp;

 /* if use clause hierarchical config form find the config to use */ 
 if (rulp->use_rule_cfg)
  {
   if ((use_replace_cfgp = fnd_cfg_by_name(rulp->rul_use_celnam)) == NULL)
    {
     __pv_err(3579,
      "config %s at %s: hierichical use clause config name %s undefined - config not changed",
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno),
      rulp->rul_use_celnam);
    }

   if (bind_cfg_design(use_replace_cfgp, TRUE))
    {
     /* SJM 05/18/04 - BEWARE - assuming (and must check) only one */
     /* design statement for hierarchical sub configs */
     if ((msyp = __get_sym(use_replace_cfgp->cfgdeslist->topmodnam,
      __modsyms)) != NULL) 
      cp->cmsym = msyp;
     cp->cmsym->cfg_needed = TRUE;
     if (__cfg_verbose)
      {
       __cv_msg("  ++ Bound in config: %s using hierarchical config: %s\n      binding instance: %s (%s:%s) bound to cell: %s (%s) (USE CLAUSE).\n\n",  
       cfgp->cfgnam, use_replace_cfgp->cfgnam, cp->csym->synam, 
       __in_fils[cp->cmsym->syfnam_ind], cp->cmsym->synam, msyp->synam,
        __in_fils[msyp->syfnam_ind]);
      }
    }
   return(TRUE);
  }

 if (rulp->rul_use_libnam == NULL || rulp->rul_use_libnam[0] == '\0') 
  {
   lbp = cntxt_lbp;
  }
 else
  { 
   if ((lbp = find_cfglib(rulp->rul_use_libnam)) == NULL)
    {
     __pv_err(3571,
      "config %s at %s: object %s use clause %s:%s library %s not found",
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno),
      rulp->objnam, rulp->rul_use_libnam, rulp->rul_use_celnam,
      rulp->rul_use_libnam);
     return(FALSE);
    }
  }

 /* use the rul_use ins name 'use lib.rul_use_celnam' */
 if ((bind_mdp = find_cell_in_cfglib(rulp->rul_use_celnam, lbp)) == NULL)
  {
    __pv_err(3573, "config %s at %s: object %s use clause %s.%s cell %s not found",
     cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, cfgp->cfg_lno),
     rulp->objnam, lbp->lbname, rulp->rul_use_celnam,
     rulp->rul_use_celnam);
    return(FALSE);
   }

 /* bind the library name (%l) */
 bind_mdp->mod_cfglbp = lbp;

 /* found cell */
 cp->cmsym = bind_mdp->msym;
 cp->cmsym->cfg_needed = TRUE;
 if (__cfg_verbose)
  {
   __cv_msg("  ++ Bound in config: %s \n       binding instance: %s (%s:%s) bound to cell: %s in library: %s (%s) (USE CLAUSE).\n\n",  
   cfgp->cfgnam, cp->csym->synam, __in_fils[cp->cmsym->syfnam_ind], 
   cp->csym->synam, bind_mdp->msym->synam, lbp->lbname, 
   __in_fils[bind_mdp->msym->syfnam_ind]);
  }

 /* bind cells inside */
 bind_cells_inside(cfgp, cp, bind_mdp, lbp);
 return(TRUE);
}

/*
 * find a config given a cfg name
 */
static struct cfg_t *fnd_cfg_by_name(char *confnam)
{
 struct cfg_t *cfgp;

 for (cfgp = __cfg_hd; cfgp != NULL; cfgp = cfgp->cfgnxt)
  {
   if (strcmp(cfgp->cfgnam, confnam) == 0)
    {
     return(cfgp);
    }
  }
 return(NULL);
}

/*
 * after binding one cell bind cells depth first inside it
 */
static void bind_cells_inside(struct cfg_t *cfgp, struct cell_t *cp,
 struct mod_t *bind_mdp, struct cfglib_t *lbp)
{
 if (++__last_bind_comp_ndx >= __siz_bind_comps) grow_bind_comps();
 __bind_inam_comptab[__last_bind_comp_ndx] = __pv_stralloc(cp->csym->synam);

 /* bind cells in this one passing library used to bind this one */
 bind_cells_in1mod(cfgp, lbp, bind_mdp);
           
 __my_free(__bind_inam_comptab[__last_bind_comp_ndx],
   strlen(__bind_inam_comptab[__last_bind_comp_ndx]) + 1);
 __last_bind_comp_ndx--;
}

/*
 * ROUTINE TO FIND A CFG CELL IN A LIBRARY AND FIRST PASS READ SRC 
 */

/*
 * find a cell in a config library list of cells
 *
 * if config library file compiled, find pre-fixup d.s module (cell)
 * else read all source in file and search for cell
 *
 * keeps reading until finding cell or reaching end of library file list
 * if any part of file is read all cells in file are read and put in
 * lib el's symbol table with ptr to mod pre-fixup d.s. 
 */
static struct mod_t *find_cell_in_cfglib(char *celnam, struct cfglib_t *lbp)
{
 struct libel_t *lbep;
 struct sy_t *msyp;

 for (lbep = lbp->lbels; lbep != NULL; lbep = lbep->lbenxt)
  {
   if (!lbep->lbelsrc_rd)
    {
     /* move keep adding files read into in fils for error locations */
     if (++__last_lbf >= __siz_in_fils) __grow_infils(__last_lbf);
     __in_fils[__last_lbf] = __pv_stralloc(lbep->lbefnam);

     /* returns F and emits error if can't open llb file */
     if (!open_cfg_lbfil(lbp->lbname)) continue;

     rd_cfg_srcfil(lbep);
     lbep->lbelsrc_rd = TRUE;
    }

   /* AIV - 05/24/04 - the rare case there is no symbol table */
   /* if the source only contains `define, `tiemscale, etc, continue */
   if (lbep->lbel_sytab == NULL) continue;
   if ((msyp = __get_sym(celnam, lbep->lbel_sytab)) != NULL) 
   {
    return(msyp->el.emdp); 
   }
  }
 return(NULL);
}

/*
 * try to open the config library file and repl. top of stack with its info
 *
 * except for includes and macros size of vinstk will always be 1
 * file must be openable and have contents
 * return F on fail
 * in fils of last lbf must be filled with file name
 * since know last_lbf > last_inf - on EOF get_vtok will resturn to caller
 */
static int32 open_cfg_lbfil(char *lbnam)
{
 char dirstr[RECLEN]; 

 /* know called with last_lbf index of file to process */
 __cur_fnam = __in_fils[__last_lbf];
 /* AIV PUTBACK print directory for now - for debugging */
 if ((__in_s = __tilde_fopen(__cur_fnam, "r")) == NULL)
  {
   __pv_err(710, "cannot open config library %s file %s in dir : %s - skipped",
    lbnam, __cur_fnam,  getcwd(dirstr, RECLEN)); 
   return(FALSE);
  }
 if (feof(__in_s))
  {
   __pv_warn(512, "config library %s file %s empty", lbnam, __cur_fnam);
   return(FALSE);
  }
 /* whenever open new file must discard pushed back */
 __lasttoktyp = UNDEF;
 __visp->vi_s = __in_s;
 __visp->vifnam_ind = __last_lbf;
 __cur_fnam_ind = __last_lbf;
 __cur_fnam = __in_fils[__cur_fnam_ind];
 __lin_cnt = 1;
 __file_just_op = TRUE;
 if (__cfg_verbose)
  {
   __cv_msg("  Parsing config library %s file \"%s\".\n", lbnam, __cur_fnam);
  }
 return(TRUE);
}

/*
 * read cfg source file to find and elaborate current module
 *
 * read src and to lbel symbol table for every module in library
 */
static void rd_cfg_srcfil(struct libel_t *lbep)
{
 __get_vtok();
 if (__toktyp == TEOF)
  {
   __pv_fwarn(609, "config library file %s contains no tokens",
    lbep->lbefnam);
   /* since empty, mark so not re-read */
   lbep->lbelsrc_rd = TRUE;
   return;
  }

 for (;;)
  {
   /* may be a compiler directive */
   if (__toktyp >= CDIR_TOKEN_START && __toktyp <= CDIR_TOKEN_END)
    {
     __process_cdir();
     goto nxt_tok;
    }
   switch (__toktyp) {
    case TEOF: return;
    case MACROMODULE:
     __get_vtok();
     __finform(423,
      "macromodules in config library not expanded - %s translated as module",
      __token);
     goto chk_name;
    case MODULE:
     __get_vtok();
chk_name:
     if (__toktyp != ID)
      {
       __pv_ferr(707, "config library file module name expected - %s read",
        __prt_vtok());
       /* since error, just try to resynchronize */
       __vskipto_modend(ENDMODULE);
       goto nxt_tok;
      }
     if (!init_chk_cfg_sytab(lbep, "module"))
      {
       __vskipto_modend(ENDMODULE);
       goto nxt_tok;
      }

     /* know error here will cause skipping to file level thing */
     /* this adds mod name to lbel one file's symbol table */
     if (!__rd_moddef(lbep->lbel_sytab, TRUE)) goto nxt_tok;

     /* when reading source this was set only if in cell define region */
     /* now turn on (maybe again) if all library modules are cells */
     /* dummy itstk empty here but if good module read mark as cell */
     if (__lib_are_cells && __last_libmdp != NULL)
      {
       __last_libmdp->m_iscell = TRUE;
       __design_has_cells = TRUE;
      }
     __last_libmdp = NULL;
     /* know to get here 1 more resolved */
     break;

    case PRIMITIVE:
     __get_vtok();
     if (__toktyp != ID)
      {
       __pv_ferr(708,
        "config library file udp primitive name expected - %s read",
        __prt_vtok());
       /* since err, just try to skip to end primitive */
       __vskipto_modend(ENDPRIMITIVE);
       goto nxt_tok;
      }
     if (!init_chk_cfg_sytab(lbep, "udp primitive"))
      {
       __vskipto_modend(ENDPRIMITIVE);
       goto nxt_tok;
      }

     if (!__rd_udpdef(lbep->lbel_sytab)) goto nxt_tok;
     break;
    default:
     __pv_ferr(709,
     "config library file module, primitive or directive expected - %s read",
      __prt_vtok());
     /* here just ignores extra semicolons */
     if (__toktyp != SEMI) __vskipto2_modend(ENDMODULE, ENDPRIMITIVE);
   }
nxt_tok:
   /* why checking this twice */
   if (__toktyp == TEOF)
    {
chk_ifdef:
     if (__in_ifdef_level != 0)
      {
       __pv_err(924, "last `ifdef unterminated in config libary file %s",
        __cur_fnam);
      }
     break;
    }
   __get_vtok();
   if (__toktyp == TEOF) goto chk_ifdef;
  }
}

/*
 * check module/udp name and alloc lib el symbol table if needed
 * returns F on error
 */
static int32 init_chk_cfg_sytab(struct libel_t *lbep, char *celtyp)
{
 struct sy_t *syp;

 /* if first mod in file, build the lbel's symbol table */ 
 if (lbep->lbel_sytab == NULL) lbep->lbel_sytab = __alloc_symtab(FALSE);

 /* check to see if name repeated in this library file */
 if ((syp = __get_sym(__token, lbep->lbel_sytab)) != NULL) 
  {
   __pv_ferr(3474,
    "%s %s repeated in config library file %s - previous at %s",
    celtyp, syp->synam, lbep->lbefnam,
    __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
   return(FALSE);
  }

 if (__lib_verbose)
  {
   __cv_msg("  Scanning config library %s %s (%s).\n",
    lbep->lbefnam, celtyp, __token);
  } 
 return(TRUE);
}

/*
 * ROUTINES TO FREE COMPILED LIBRARY MODULE NEVER INSTANTIATED
 */
static void add_cfgsym(char *libnam, struct tnode_t *tnp)
{
 struct tnode_t *ntnp;
 char s1[RECLEN];

  if (tnp == NULL) return;
  add_cfgsym(libnam, tnp->lp);

  // AIV FIXME ??? sprintf(s1, "%s.%s", libnam, tnp->ndp->synam);
  if (tnp->ndp->cfg_needed)
   {
    strcpy(s1, tnp->ndp->synam);
    ntnp = __vtfind(s1, __modsyms);
   //AIV FIXME ###
    if (!__sym_is_new)
     {
      __fterr(305,
       "Sorry - config code to rename module with same name from different libraries not implemented yet.");
     }
    __add_sym(s1, ntnp);
    ntnp->ndp = tnp->ndp;
    strcpy(ntnp->ndp->synam, s1);
    ntnp->ndp->sydecl = TRUE;
    (__modsyms->numsyms)++;
   }
  add_cfgsym(libnam, tnp->rp);
}


/* 
 * add all the used symbols from a config to __modsyms
 */
static void add_cfg_libsyms(struct cfglib_t *cfgp)
{
 struct libel_t *lbp;
 struct symtab_t *symt;
 struct tnode_t *tnp;
 char *cp;
 int32 i;

 for (lbp = cfgp->lbels; lbp != NULL; lbp = lbp->lbenxt)
  {
   if ((symt = lbp->lbel_sytab) == NULL) continue;
   if (symt->stsyms != NULL)
    {
     for (i = 0; i < symt->numsyms; i++)
      {
       if (!symt->stsyms[i]->cfg_needed) continue;
       cp = symt->stsyms[i]->synam;
       tnp = __vtfind(cp, __modsyms);
      //AIV FIXME ###
       if (!__sym_is_new)
        {
         __fterr(305,
          "Sorry - config code to rename module with same name from different libraries not implemented yet.");
        }
       __add_sym(cp, tnp);
       (__modsyms->numsyms)++;
       tnp->ndp = symt->stsyms[i];
      }
    }
   else
    {
     add_cfgsym(cfgp->lbname, symt->n_head);
    }
  }
}


/* 
 * removes all modules that were scanned in from config libraries 
 * but are never needed remove from the __modhdr list
 */
static void free_unused_cfgmods(void)
{
 struct mod_t *mdp, *mdp2, *last_mdp; 
 long sav_mem_use;

//AIV FIXME ### need to free
 __modsyms = NULL;
 __modsyms = __alloc_symtab(FALSE);
 __sym_addprims();
 sav_mem_use = __mem_use;
 last_mdp = NULL;
 for (mdp = __modhdr; mdp != NULL;)
  {
   mdp2 = mdp->mnxt;

   /* if module is from a config and hasn't been linked to a library rm */
   if (mdp->m_inconfig && mdp->mod_cfglbp == NULL)
    {
     /* SJM 05/28/04 FIXME ### ??? - need to do some freeing of libs */
     /* partially_free_mod(mdp); */

     if (last_mdp != NULL) last_mdp->mnxt = mdp2;
     mdp = mdp2;
     continue;
    }
   if (!mdp->mod_cfglbp->sym_added)
   {
     add_cfg_libsyms(mdp->mod_cfglbp);
     mdp->mod_cfglbp->sym_added = TRUE;
   }
   last_mdp = mdp;
   mdp = mdp2;
  }
 /* AIV 05/31/05 - FIXME ### if not freeing no need to print message */
 /*
 if (__cfg_verbose)
  {
   __cv_msg(
   "  Config freeing most memory in unused library modules - %ld bytes freed\n",
    sav_mem_use - __mem_use);
  }
  */
}

/* 
 * partially free a module (just the larger parts such as stmts and cells)
 *
 * for now freeing most of the inisdes of modules that were parsed during
 * config library loading - eventually will moved to precompiled lib scheme
 * so this will be removed
 *
 * not free mdp but now nothing points to it
 *
 * SJM 05/26/04 - LOOKATME - since only free large d.s. in modules there is
 * quite a bit of memory leakage here
 */
static void partially_free_mod(struct mod_t *mdp)
{
 struct cell_t *cp, *cp2;

 for (cp = mdp->mcells; cp != NULL; )
  {
   cp2 = cp->cnxt;
   __my_free(cp, sizeof(struct cell_t));
   cp = cp2;
  }

 /* SJM 05/26/04 - LOOKATME ??? ### can't free stmt until fixup ---
 struct ialst_t *ialp;
 struct task_t *tskp;
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt) 
  {
   __free_stlst(ialp->iastp);
  }

 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   __free_stlst(tskp->tskst);
  }
 --- */

}
