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
 * module that fixes and checks net list after all source read
 * all defparam and global processing in v_grf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include <sys/types.h>

#include <sys/dir.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

/* local prototypes */
static struct mod_t *choose_nxt_allup_inst_gened_mod(void);
static int32 fixup_one_generate_mod(struct mod_t *);
static int32 fixup_nl(void);
static void fixup_nl_linkout_gencells(void);
static void undo_free_pre_fixup_nl(void);
static void empty_dfp_flds(struct dfparam_t *);
static int32 fix_modcell_nl(void);
static int32 count_static_instances(struct mod_t *);
static int32 chk_dag(void);
static void count_flat_insts(void);
static void count2_flat_insts(struct mod_t *);
static void do_iarr_splitting(void);
static void mark_gia_rng_params(struct mod_t *);
static int32 in_giarng_markparam(struct gia_aux_t *, struct expr_t *);
static int32 down_hasgiarngdet_param(struct mod_t *);
static void bld_top_virtinsts(void);
static int32 topip_cmp(const void *, const void *);
static void rebld_dsgn_giars_from_split(int32);
static void unbld_iarrs_and_garrs(void);
static void save_all_param_vals(void);
static void free_all_param_vals(void);
static void set_gia_ranges(void);
static void eval1_arr_of_gates_rng(struct gate_t *, struct itree_t *);
static int32 gi_ndxexpr_chk(struct expr_t *, int32, int32, char *); 
static int32 gi_ndxval_chk(struct xstk_t *, int32, int32, char *);
static void eval1_arr_of_insts_rng(struct inst_t *, struct itree_t *);
static void set_pnd_gi_rnges(void);
static void set2_pnd_gi_rnges(struct mod_t *, struct itree_t *);
static void set_gia_expr_pndparms(struct expr_t *, struct itree_t *);
static void set1_garr_pndparm(struct net_t *, struct itree_t *); 
static void unsave_gia_expr_pndparms(struct expr_t *, struct itree_t *);
static void rebld_mod_g_and_i_arrs(void);
static void rebld_1mod_g_and_i_arr(struct mod_t *);
static void cmp_new_mgnum_minum_and_stsiz(struct mod_t *, int32 *, int32 *,
 int32 *);
static void rebld_mgtab(struct mod_t *, int32);
static void rebld_mitab(struct mod_t *, int32);
static void add_new_gsym(struct gate_t *, int32);  
static void add_new_isym(struct inst_t *, int32); 
static void chk_defparams(void);
static int32 chk1_defparam(struct dfparam_t *);
static int32 lhs_chk1dfparam(struct dfparam_t *);
static int32 gref_has_giarr_ndxes(struct gref_t *);
static int32 xmp_contains_genblk(struct xmrcmp_t **, int32);
static int32 cnt_new_xmp_siz(struct gref_t *);

static void set_1defparam_iis(struct dfparam_t *, struct gref_t *);
static int32 do_dfp_resolve(struct gref_t *);
static int32 bld_dfp_xmrcmps(struct gref_t *);
static int32 bld_dfp_hd_xmrcmp(struct xmrcmp_t *, struct gref_t *);
static int32 cvrt_local_dfp_back_to_xpr(struct gref_t *);
static int32 bld_rest_dfpcmps(struct xmrcmp_t **, int32, struct gref_t *,
 struct expr_t *);

static void fill_gref_from_xmrcmps(struct gref_t *);
static int32 cvrt_local_xmr_back_to_xpr(struct gref_t *);
static int32 cnt_xmr_cmp_num(struct gref_t *);
static void fill_glbcmps_from_xmrcmp(struct gref_t *);
static int32 bld_rest_xmrcmps(struct xmrcmp_t **, int32, struct gref_t *,
 struct expr_t *);
static int32 bld_glb_xmrcmps(struct gref_t *);
static int32 bld_glb_hd_xmrcmp(struct xmrcmp_t *, struct gref_t *);

static int32 chk_xmr_tail_wire(struct gref_t *, struct sy_t *, int32);
static int32 chk_all_uprels_same(struct gref_t *, struct sy_t *, char *,
 struct expr_t *);
static struct itree_t *fnd_uprel_inst(char *, struct itree_t *);
static struct itree_t *fnd_uprel_mod(struct sy_t *, struct itree_t *);
static struct mod_t *fnd_uprel_tskfunc(struct sy_t **, char *,
 struct itree_t *);
static struct sy_t *fnd_tskfunc_inscope(char *, struct symtab_t *);
static struct sy_t *try_fnd_nxtcmp_gblk(char *, struct mod_t *);
static struct sy_t *try_fnd_in_gblk_tsk(char *, struct genblk_t *,
 struct symtab_t **);
static void dbg_dmp_grcmps(struct gref_t *);
static void dbg_dmp_xmrcmptab(struct gref_t *, struct xmrcmp_t **, int32); 
static void emit_downrel_nam_collision_informs(char *, struct gref_t *);
static void init_xmrcmp(struct xmrcmp_t *);
static struct sy_t *find_dfp_inmod_sym(struct gref_t *, struct expr_t *,
 struct sy_t *, struct symtab_t *);
static struct sy_t *find_xmr_inmod_sym(struct gref_t *, int32, struct sy_t *,
 struct symtab_t *);
static int32 chk_glb_inst_sels(struct gref_t *);
static void free_gone_glbs(void);
static void free_xmrcmptab(struct gref_t *);
static void free_1xmrcmp(struct xmrcmp_t *);
static void mark_poundparam_splitinsts(void);
static int32 indir_widthdet_markparam(struct expr_t *);
static void do_poundparam_splitting(void);
static void split_upd_mod(struct mod_t *, struct inst_t *, int32, int32); 
static struct mod_t *find_split_mod(struct mod_t *, struct inst_t *, int32);

static void bld2_flat_itree(struct itree_t *);
static int32 dmp_down_itree(struct itree_t *, int32, int32);
static void do_dmp(struct itree_t *, int32);
static void free2_flat_itree(struct itree_t *);
static void reassign_itnums(void);
static void bld2_itnum_to_itp(struct itree_t *);

static void travfreeze1_genitem(struct genitem_t *);
static void travfreeze1_genblk(struct genblk_t *);
static void travfreeze1_genitem(struct genitem_t *);

static void gather_add_1mod_gened_items(struct mod_t *);
static void bld_1mod_gitem_list(void);
static void add_genitems_from1_genitem(struct genitem_t *);
static void add_genitems_from1_genblk(struct genblk_t *);
static void mv_gblk_nsym_to_mod_mgen_sytab(struct sy_t *, struct genblk_t *);
static void mv_gblk_tsks_to_mod(struct genblk_t *);
static int32 gblk_under_genfor(struct genblk_t *);
static void mv_genitems_into_mod(void);
static void turn_off_pndsplitting_reuse(struct mod_t *);
static int32 count_genitems(int32);
static int32 count_gref_genitems(void);
static void free_mv_gitem_lst(struct genitem_t *);
static int32 chk_1gblk_dfp(struct dfparam_t *);
static void chk_1mod_genblk_defparams(void);
static void mv_gened_symbols_to_modsymtab(struct mod_t *);
static void mv_gblk_dfps_to_mod(void);
static void fixup_1dfp_xmrcmps(struct gref_t *);
static int32 cnt_new_xmp_siz(struct gref_t *);
static void mv_gblk_grefs_to_mods_grtab(void);
static void bld_glbref_xpr_from_xmrcmptab(struct gref_t *);
static char *xmrcmptab_to_gnam(char *, struct gref_t *);

static void xpnd_1mod_gen_items(struct mod_t *);
static void xpnd1_gen_item(struct genitem_t *, struct genblk_t *);
static void chk_xpnd1_dfparam(struct genitem_t *, struct genblk_t *);
static void xpnd1_genblk(struct genblk_t *);
static void xpnd1_gen_for(struct genitem_t *, struct genblk_t *);
static int32 fnd_genfor_genvar_rng(struct genitem_t *, int32 *, int32 *);
static void bld_genfor_gentab(struct gen_for_t *, struct genblk_t *);
static int32 genfor_not_done(struct expr_t *);

static int32 gen_chk_expr(struct expr_t *, int32, int32, char *);
static void xpnd1_gen_if(struct genitem_t *, struct genblk_t *);
static void xpnd1_gen_case(struct genitem_t *, struct genblk_t *);
static struct genblk_t *find_gen_case_gblk(struct genitem_t *);
static struct genblk_t *get_real_case_sel_genblk(struct genitem_t *,
 struct gen_csitem_t *);
static void xpnd1_gen_conta(struct genitem_t *, struct genblk_t *);
static void xpnd1_gen_inst(struct genitem_t *, struct genblk_t *);
static void xpnd1_gen_gate(struct genitem_t *, struct genblk_t *);

static void xpnd1_gen_vardecl(struct genitem_t *, struct genblk_t *);
static void xpnd1_gen_initalways(struct genitem_t *);
static void copy_avl_sytab_to_wrkstab(struct symtab_t *);

static void prefixup_sav_not_yet_sav_defparams(void);
static void prefixup_restor_defparams(void);
static struct dfparam_t *prefixup_copy_1mod_dfparms(struct dfparam_t *, int32);
static struct dfparam_t *prefixup_cp1_dfp(struct dfparam_t *, int32);
static void prefix_free_dfplist(struct dfparam_t *);

static void genp_dellst_do(struct paramlst_t *,
 void (*gprm_proc)(struct expr_t *));
static void genp_1stmt_do(struct st_t *, void (*gprm_proc)(struct expr_t *));
static void genp_dctrl_do(struct delctrl_t *, int32,
 void (*gprm_proc)(struct expr_t *));
static void genp_delexpr_do(union del_u, word32,
 void (*gprm_proc)(struct expr_t *));
static void genp_csitemlst_do(struct csitem_t *,
 void (*gprm_proc)(struct expr_t *));
static void genp_stlst_do(struct st_t *, void (*gprm_proc)(struct expr_t *));
static void genp_xprlst_do(struct exprlst_t *,
 void (*gprm_proc)(struct expr_t *));
static void genp_expr_do(struct expr_t *, void (*gprm_proc)(struct expr_t *));
static void do_repl_id_genvar(struct expr_t *);
static void do_repl_id_forincvar(struct expr_t *);
static void do_addto_gsens_lst(struct expr_t *);
static void mark_declnet_expr_syms(struct expr_t *, struct genblk_t *);
static void try_fix_genblk_nam_conflict(struct genblk_t *, struct mod_t *);
static void fix_gen_msytab_conflict(char *, struct mod_t *);

static void bld_root_dfpglbs(void);
static int32 dfploc_cmp(const void *, const void *);
static void dmp_dfps(int32, int32);
static void bld_root2_dfpglbs(struct itree_t *, int32);
static void bld_identdfparams(int32);
static int32 ipth_cmp(const void *, const void *);
static int32 ipth2_cmp(struct dfparam_t *, struct dfparam_t *);
static void find_mustsplit_dfps(void);
static struct mod_t *find_dfpbot_mod(struct dfparam_t *);
static void dbg_dmp_dfpiis(struct dfparam_t *, char *);
static void do_dfp_fnd_needto_split(void);
static void mark_all_insts_of_mod_split(void);
static void do_defparam_splitting(void);
static void reset_dfp_targsyps(void);
static void reset_1dfp_targsyp(struct dfparam_t *);
static void reassign2_itnums(struct itree_t *);
static void set2_poundparams(struct itree_t *);
static void __cnvt_decl_param_stkval(struct xstk_t *, struct expr_t *,
 struct net_t *);
static void rebld_undecl_parm_net(struct xstk_t *, struct expr_t *,
 struct net_t *);
static void assgn_2005_is_param(struct net_t *, struct xstk_t *,
 struct expr_t *, int32, int32);
static void maybe_rebld_undecl_isparm_net(struct net_t *,
 struct xstk_t *, int32);
static void replace_param_rhs_expr(struct net_t *, word32 *, struct mod_t *);
static void set_1defparam(struct dfparam_t *);
static void recalc_1mod_params(struct mod_t *, struct net_t *, int32);
static void recalc_1mod_pndparams(struct mod_t *);
static int32 xpr_has_is_param(struct expr_t *);
static void set_parmval_from_isxpr(struct net_t *, struct expr_t *,
 struct mod_t *);
static int32 all_parent_mods_recalced(struct mod_t *);


/* extern prototypes (maybe defined in this module) */
extern int32 __fixup_and_gen_nl(void);
extern int32 __dsgn_has_generate(void);
extern void __init_inst(struct inst_t *);
extern struct expr_t **__copy_pndxtab(struct inst_t *);
extern char *__my_malloc(size_t);
extern char *__pv_stralloc(char *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern int32 __isleaf(struct expr_t *);
extern struct sy_t *__zget_sym(char *, struct sy_t **, word32);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_sytyp(char *, word32);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern struct expr_t *__copy_expr(struct expr_t *);
extern void __bld_flat_itree(void);
extern void __free_flat_itree(void);
extern int32 __xpr_has_param(struct expr_t *);
/* DBG */
extern void __dmp_itree(struct itree_t *); 
/* --- */
extern void __bld_moditps(void);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct expr_t *__alloc_newxnd(void);
extern struct symtab_t *__alloc_symtab(int32);
extern struct paramlst_t *__copy_dellst(struct paramlst_t *);
extern char *__regab_tostr(char *, word32 *, word32 *, int32, int32, int32);
extern char *__pregab_tostr(char *, word32 *, word32 *, struct net_t *);
extern int32 __wide_vval_is0(word32 *, int32);
extern char *__bld_lineloc(char *, word32, int32);
extern struct expr_t *__bld_rng_numxpr(word32, word32, int32);
extern void __sizchgxs(struct xstk_t *, int32);  
extern void __process_defparams(void);
extern void __dbg_dmp_1mod_defparams(struct mod_t *, int32);
extern void __set_poundparams(void);
extern void __set_1inst_pound_params(struct itree_t *, int32);
extern void __recalc_param_vals(void);
extern void __my_free(void *, size_t);
extern void __free_xtree(struct expr_t *);
extern void __free2_xtree(struct expr_t *);
extern int32 __chk_paramexpr(struct expr_t *, int32);
extern void __set_numval(struct expr_t *, word32, word32, int32);
extern struct dfparam_t *__copy1_defparam(struct dfparam_t *);
extern void __free_1dfparam(struct dfparam_t *);
extern struct itree_t *__find_dfpbot_itp(struct dfparam_t *);
extern struct gref_t *__alloc_grtab(struct gref_t *, int32);
extern int32 __ip_indsrch(char *);
extern void __free_1glb_flds(struct gref_t *);
extern void __bld_mlevel_lists(void);
extern void __mark_widdet_params(struct mod_t *);
extern void __do_mdsplit(struct mod_t *);
extern struct genblk_t *__xpnd_copy1_genblk(struct genblk_t *, struct net_t *,
 int32); 
extern void __init_itree_node(struct itree_t *);
static void __dbg_dmp_mod_gia_recs(struct mod_t *);
extern void __dbg_dmp_gia_rec(struct gia_aux_t *, int32);
extern int32 __get_gia_wide(struct gia_aux_t *);
extern int32 __gia_sym_cmp(const void *, const void *);
extern void __dmp_dsgn_minst(char *);
extern void __dmp_1minst(struct inst_t *);
extern void __dmp_modhdr_list(struct mod_t *, char *);
extern void __resolve_xmrs_fr_xmrcmps(void);
extern void __dbg_dmp_gref(struct gref_t *);
extern void __dmp_1defparam(FILE *, struct dfparam_t *, int32);
extern int32 __expr_has_glb(struct expr_t *);
extern int32 __chkndx_expr(struct expr_t *, char *);
extern void __assgn_2005_nonis_param(struct net_t *, struct expr_t *,
 struct xstk_t *);
extern char *__msg2_blditree(char *, struct itree_t *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern void __chg_param_tois(struct net_t *, struct mod_t *);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern int32 __alloc_shareable_cval(word32, word32, int32);
extern int32 __alloc_shareable_rlcval(double);
extern struct mod_t *__get_mast_mdp(struct mod_t *);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct sy_t *__decl_sym(char *, struct symtab_t *);
extern int32 __cvt_lngbool(word32 *, word32 *, int32);
extern void __cnv_stk_fromreg_toreal(struct xstk_t *, int32);
extern void __narrow_sizchg(struct xstk_t *, int32);
extern void __sgn_xtnd_widen(struct xstk_t *, int32);
extern void __sizchg_widen(struct xstk_t *, int32);
extern void __cnv_stk_fromreal_toreg32(struct xstk_t *);
extern void __init_xnd(struct expr_t *);
extern void __travfreeze_syms(struct tnode_t *);
extern void __freeze_mod_syms(struct symtab_t *, struct symtab_t *);
extern int32 __chk_rhsexpr(struct expr_t *, int32);
extern void __set_rhswidth(struct expr_t *, int32);
extern void __travfreeze_genitem_sytabs(struct genitem_t *);
extern void __copy1_gate_gia_rec(struct gate_t *, struct gia_aux_t *);
extern void __copy1_inst_gia_rec(struct inst_t *, struct gia_aux_t *);

extern void __dmp_mod(FILE *, struct mod_t *, int32);
extern void __dbg_dmp_avl_sytab(struct symtab_t *);
extern struct tnode_t *__vtfind(char *, struct symtab_t *);
extern char *__bld_gen_scope_nam(char *, struct genblk_t *);
extern int32 __is_const_expr(struct expr_t *);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern void __rhspsel(word32 *, word32 *, int32, int32);
extern void __merge_same_pval_leaf_splitmods(void);

extern void __pv_err(int32, char *, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __sgfwarn(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __pv_ferr(int32, char *, ...);
extern void __dbg_msg(char *, ...);
extern void __sgfinform(int32, char *, ...);
extern void __pv_terr(int32, char *, ...);
extern void __gfterr(int32, word32, int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);

extern const word32 __masktab[];

/*
 * GENERATE AND PARAM FIXUP ROUTINES 
 */

/*
 * generate fixup loop
 *
 * SJM 03-13-10 - this rouutine called one for fixup, gen, fixup <more...?>
 * loop so can init global fixup loop count here
 *
 * SJM 03-09-09 ADDME? - eventually need fixup and gen expand look with
 * parameter sensitivity change lists to determine convergence (unchangedness)
 *
 * SJM 05-31-10 - now performing all generate steps for one mod and then move
 * on to next mod - needed to rebld inst tree and recalc all params each time
 */
extern int32 __fixup_and_gen_nl(void)
{
 struct mod_t *mdp, *mdp2;
 struct inst_t *ip;
 int32 rv, i;

 __fixup_round = 1;
 __all_topm_gen_xpnd = FALSE;
 if (!fixup_nl()) return(FALSE);

 /* SJM 05-31-10 - even with new per mod gen scheme if no gens in dsgn, done */ 
 if (!__dsgn_has_generate()) return(TRUE);

 /* SJM 03-11-11 - mark all mod's with gen's inside as gen expanded */
 /* this is initial guess - if gen caused splitting will need to mark */
 /* dynamically when choosing next module */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  { 
   if (mdp->mgenitems == NULL) mdp->m_gen_xpnded = TRUE;
  } 

 /* AIV 05-20-10 - now per module generating with all the post gen gather */
 /* add fixup done each time one mod is generated - this makes sure inst */
 /* tree and param values rebld and recalc after each module is gened */
 rv = TRUE;
 for (;;)
  {
   if ((mdp = choose_nxt_allup_inst_gened_mod()) == NULL) break; 

   rv = fixup_one_generate_mod(mdp);
   if (!rv) return(FALSE); 

   /* AIV 05/26/11 - just find a module which hasn't been expanded but must */
   /* do the top modules first and then expand all instance modules */
   /* think this is now correct to go down generated instance modules */
   for (i = 0; i < mdp->minum; i++)
    {
     ip = &(mdp->minsts[i]);
     mdp2 = ip->imsym->el.emdp;
     if (!mdp2->m_gen_xpnded) 
      {
       mdp2->m_gen_xpnded = TRUE;
       rv = fixup_one_generate_mod(mdp2);
       if (!rv) return(FALSE); 
      }
    }
  }
 /* AIV 08/24/11 - may need to linkout top level -y/-v libs which are */
 /* never instantiated via generate blocks */
 fixup_nl_linkout_gencells();
 return(rv);
}
   
/*
 * expand one modules generate and do fixup
 */
static int32 fixup_one_generate_mod(struct mod_t *mdp)
{
 int32 rv;

 /* SJM 12-27-08 - need to initialize the mod gen work sym tab */
 /* first used here - until here all gen sym go into gen blk sym tabs */
 mdp->mgen_symtab = __alloc_symtab(FALSE);

 /* SJM 05-31-10 - expand but still keep in gen d.s. */
 xpnd_1mod_gen_items(mdp);
 gather_add_1mod_gened_items(mdp);
 if (__pv_err_cnt != 0) return(FALSE);
 
 /* SJM 04-11-10 - increment after move so know if bugs in 2nd fixup */
 __fixup_round++;

 /* SJM 03-23-10 - LOOKATME? - current algorithm works only when first */
 /* time gen items are moved into mod's top level, design contents does */
 /* not change - need removal mechanism and special handling 3rd time */
 /* and after of defparams, plus need way to determine convergence */

 /* SJM 03-11-11 - NOTICE - key to algorithm is that every time a module */
 /* has its gen's expanded, the instance tree is rebuilt and all pound */
 /* params are re-evaluated  - then know chosen mod will use final from */
 /* up param values so number of gened items and sizes and indices will */
 /* will all be the final value */

 rv = fixup_nl();

 /* DBG remove -- */
 if (__debug_flg)
  {
   struct mod_t *mdp2;

   for (mdp2 = __modhdr; mdp2 != NULL; mdp2 = mdp2->mnxt)
    {
     __dbg_msg(">>> after call of fixup nl for mod %s dmp %s fixup=%d\n",
      mdp->msym->synam, mdp2->msym->synam, __fixup_round);

     __dmp_mod(stdout, mdp2, FALSE);
    }
  }
 /* --- */
 return(rv);
}

/*
 * return T if design uses any generates
 */
extern int32 __dsgn_has_generate(void)
{
 struct mod_t *mdp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mgenitems != NULL) return(TRUE);
  }
 return(FALSE);
}

/*
 * choose next module to generate - must choose mod where all modules
 * that instantiate any inst of this module either top or has already
 * been gened
 *
 * returns nil if can't find mod to expand
 *
 * SJM 03-11-11 - the relaxation algorithm in the LRM in this case
 * should have been taken almost literally since we do not flatten,  
 * must find modules where all modules that instantiate this module
 * have their gens expanded
 *
 * key is that itree is dynamically updated after any mod has its gens
 * expanded - can't use mdlevhdr here since changed dynamically each
 * time a mod's gen's expanded
 *
 * AIV 05/26/11 - just find a module which hasn't been expanded but must
 * do the top modules first and then expand all instance modules
 */
static struct mod_t *choose_nxt_allup_inst_gened_mod(void)
{
 int32 ii;
 struct itree_t *itp;
 struct mod_t *mdp;

 /* first try to choose top mod and choose these until all chosen */
 /* SJM 03-11-11 - all topm first works because gen expand can never */
 /* create a new top module */
 if (!__all_topm_gen_xpnd)
  {
   for (ii = 0; ii < __numtopm; ii++)
    {
     itp = __it_roots[ii];
     mdp = itp->itip->imsym->el.emdp;

     /* if no gen in mod, xpnded will be already set */
     if (mdp->m_gen_xpnded) continue;
     if (mdp->m_maybe_gened) continue;

     mdp->m_gen_xpnded = TRUE;
     return(mdp);
    }
   __all_topm_gen_xpnd = TRUE;
  }
 
 /* after all top mod's that can't be later gened, done - try the rest */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->m_gen_xpnded) continue;
   mdp->m_gen_xpnded = TRUE;
   return(mdp);
  }
 return(NULL);
}

/*
 * fixup the net list after all modules read
 *
 * this is second pass routine for determine params, inst tree and XMRs
 * returns F to get cannot continue message
 * if return T caller still stops if there were any syntax errors
 */  
static int32 fixup_nl(void)
{
 /* SJM 03-13-10 - free d.s from last fixup run if need to repeat for gen */
 if (__fixup_round > 1)
  {
   undo_free_pre_fixup_nl();
   prefixup_sav_not_yet_sav_defparams();
   prefixup_restor_defparams();
  }
 else
  {
   prefixup_sav_not_yet_sav_defparams();
//SJM REMOVEME - just for debugging - since this is same first time as sav 
   prefixup_restor_defparams();
  } 

 /* build static instance information */ 
 /* AIV 03/13/11 - these should have been returning FALSE */
 if (!fix_modcell_nl()) return(FALSE);

 count_flat_insts();

 /* need well formed static instance tree to continue */
 if (__pv_err_cnt != 0) return(FALSE);

 /* build the levelized module table - rebuilt later again after splitting */
 __bld_mlevel_lists();

 /* do split - needed because pound param used in array of gate/inst ranges */
 if (__design_gi_arrays && __num_inst_pndparams != 0) do_iarr_splitting();

 /* build top of itree table now so can search tops when build dfpii */
 bld_top_virtinsts();

 /* after here, all g/i array ranges known */
 /* current value of pound params used then value thrown away because */
 /* defparam setting and splitting may change again */
 if (__design_gi_arrays)
  {
   rebld_dsgn_giars_from_split(FALSE);
  }

 /* find and check all normal defparams - defps in gen blks */
 /* not seen until moved into normal defparam list for next pass */
 chk_defparams();
 /* AIV 03/13/11 - if has bad defparams no need to continue */
 if (__pv_err_cnt != 0) return(FALSE);

 /* do all splitting for all pound params */
 /* must set pound params after all splitting since need itree inst num. */
 if (__num_inst_pndparams != 0 || __num_dfps != 0)
  {
   mark_poundparam_splitinsts();

   /* SJM 06-20-11 - split off every downward defparam into a width */
   /* determing defparam - split here so pound params set right and then */
   /* defparam setting later just overrights */ 

   /* SJM 09-21-11 - for defparam for any target inst, all insts of that */
   /* module type, need to be split following the pound param splitting */
   /* rules - this marks all insts as need to split - so pound param */
   /* splitting will handle */
   do_dfp_fnd_needto_split();

   do_poundparam_splitting();
  }

 /* SJM 07-06-07 if any splitting of modules with array of gate or inst */
 /* pound params, need to rebuild the gate and inst arrays and itree again */ 
 if (__pndparam_splits && __design_gia_pndparams)
  {
   rebld_dsgn_giars_from_split(TRUE);
  }

 /* build the as if flattened instance tree and assign instance numbers */
 __bld_flat_itree();

 /* -- v_fx2.c routines start here -- */

 /* handle defparam setting and associated splitting and param expr array */
 /* building - finally reassigns itree place numbers */
 /* after here all parameters have a numeric value (but maybe IS form) */
 /* therefore can fold and evaluate constant expressions */
 
 /* notice if have defparams must process pound params at same time */
 /* else do just pound params separately */
 /* SJM 03-23-10 - can't process downward only dfps in gen blks here */
 /* because won't be seen */
 if (__num_dfps != 0) __process_defparams();
 else if (__num_inst_pndparams != 0) __set_poundparams();

 /* final itree instance numbers now assigned, build mod by num to inst tab */
 __bld_moditps();

 /* must stop here if errors since will not have value for xmrs */
 if (__pv_err_cnt != 0) return(TRUE);

 /* re-calculate parameter values, for params with other rhs params */
 /* may have been changed by pound or defparam setting */ 
 /* SJM 02/28/02 - need so parameter values use post pound/def val */
 __recalc_param_vals();
 
 //AIV cannot free here yet put need to do this
 //for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt) mdp->lastinum = 0;
 
 /* SJM 03-11-11 - knew algorithm will core dump if n.l. is mashed so */ 
 /* there are no top modules or no modules */
 if (__numtopm == 0 || __modhdr == NULL) __misc_terr(__FILE__, __LINE__);

 /* fixup - 1st pass done - connectivity now known and no errors */
 /* SJM 03-11-11 - know inst tree rebuilt and correct for the one mod */
 /* (after first fixup) that has just been gened */ 
 return(TRUE);
}

/* 
 * AIV 08/24/11 - may need to linkout top level -y/-v libs which are 
 *
 * basically the same as fixup_nl except no param calcs routines
 *
 * AIV 05/30/12 - this is now working correctly, just need to remove the
 * the top-level never gened mods, build the top-level mods again, count the
 * instances and remove the modules with 0 instances
 */
static void fixup_nl_linkout_gencells(void)
{
 struct mod_t *mdp, *last_mdp;


 /* AIV 02/06/12 - now have to merge leaf modules prior to running the */
 /* generate top-level never used modules link out */
 /* AIV LOOKATME - if this modules is fixed this can be removed */
 __merge_same_pval_leaf_splitmods();

 undo_free_pre_fixup_nl();

 /* build static instance information */ 
 /* AIV 03/13/11 - these should have been returning FALSE */
 if (!fix_modcell_nl()) __misc_terr(__FILE__, __LINE__);

 count_flat_insts();

 /* need well formed static instance tree to continue */
 if (__pv_err_cnt != 0) __misc_terr(__FILE__, __LINE__);

 /* build the levelized module table - rebuilt later again after splitting */
 __bld_mlevel_lists();
 
 /* do split - needed because pound param used in array of gate/inst ranges */
 if (__design_gi_arrays && __num_inst_pndparams != 0) do_iarr_splitting();

 /* link out the never generated modules from the __modhdr list */
 last_mdp = NULL;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* descend to count only from top level modules */
   if (mdp->minstnum != 0) 
    {
     last_mdp = mdp;
     continue;
    }

   /* mark module as top level never instantiated module */
   if (mdp->m_iscell && __map_files_hd == NULL)
    {
     if (mdp->m_maybe_gened)
      {
       mdp->m_gened_remove = TRUE;
       /* should not be header - something needs to gen this */
       /* DBG remove --- */
       if (last_mdp == NULL) __misc_terr(__FILE__, __LINE__);
       /* ----- */
       last_mdp->mnxt = mdp->mnxt;
       continue;
      }
    }
   last_mdp = mdp;
  }

 /* build top of itree table now so can search tops when build dfpii */
 bld_top_virtinsts();
 /* now recount number of instances */
 count_flat_insts();
 
 /* now linkout all never instantiated modules */
 last_mdp = NULL;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->flatinum == 0)
    {
     /* should not be header - something needs to gen this */
     /* DBG remove --- */
     if (last_mdp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ----- */
     last_mdp->mnxt = mdp->mnxt;
     continue;
    }
   last_mdp = mdp;
  }

 /* after here, all g/i array ranges known */
 /* current value of pound params used then value thrown away because */
 /* defparam setting and splitting may change again */
 if (__design_gi_arrays)
  {
   rebld_dsgn_giars_from_split(FALSE);
  }

 /* build the as if flattened instance tree and assign instance numbers */
 __bld_flat_itree();
 /* final itree instance numbers now assigned, build mod by num to inst tab */
 __bld_moditps();

 /* DBG remove --- */
 if (__pv_err_cnt != 0) __misc_terr(__FILE__, __LINE__);
 /* ----- */
}

/*
 * ROUTINES TO GO THROUGH GEN ITEMS FREEING IF NEEDED BEFORE >1 PASS
 */

/*
 * routine to initialize globals set by fixup nl so can run again
 *
 * called just before 2nd (and if changed to loop) fixup nl call
 *
 * AIV? - 01-17-09 for 2nd time through fixup nl should free these
 * FIXME? - LOTS OF MEMORY LEAKED HERE
 */
static void undo_free_pre_fixup_nl(void)
{
 int32 gri;
 struct mod_t *mdp;
 struct gref_t *grp;
 struct dfparam_t *dfpp;

 /* DBG remove --- */
 if (__fixup_round <= 1) __misc_terr(__FILE__, __LINE__); 
 /* --- */

 __numtopm = 0;
 __top_itab = NULL;
 __it_roots = NULL;
 __top_ipind = NULL;
 __mdlevhdr = NULL;
 __dfphdr = NULL;
 __design_no_strens = TRUE;

/* AIV - params don't work because first pass it sets/frees defparams 
 * in v_fx2.c 
 * bld_root_dfpglbs
 * dfpmdp->mdfps = NULL;
 */
//SJM 08-23-11 - exactly so now saving and putting back
//
 __free_flat_itree();
 if (__design_gi_arrays) unbld_iarrs_and_garrs();
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt) 
  {
   /* SJM - 05-29-10 - some split tests are failing because now after */
   /* maybe need more re-init here */
// SJM 05-29-10 - need to re-init here
   mdp->mwiddetdone = FALSE;
   mdp->mlpcnt = -1;

   /* SJM 09-10-11 - need to reset split state so next round splitting */
   /* recorded right - i.e. must start each round with nothing split */
   mdp->msplit = FALSE;
   mdp->mpndsplit = FALSE;
   mdp->mhassplit = FALSE;
   mdp->mspltmst = NULL;
   mdp->mpndspltmst = NULL;

   /* SJM 09-09-11 - must empty each defparam in mod */
   for (dfpp = mdp->mdfps; dfpp != NULL; dfpp = dfpp->dfpnxt) 
    {
     empty_dfp_flds(dfpp);
    }

   /* AIV 02/14/11 - need to re-init param recalc here - was not */ 
   /* propagating pound parameter changes - turn off marker */ 
   mdp->mod_parms_gd = FALSE;
   for (gri = 0; gri < mdp->mgrnum; gri++)
    {
     grp = &(mdp->mgrtab[gri]);
     if (grp->gr_xmptab != NULL) free_xmrcmptab(grp);
    }
   /* SJM 09-03-11 - no more dfp gref tab */
  }
 /* SJM 03-31-11 - can't free */
//SJM 03-31-11 - this is memory leak because can't free because need the
//final gen d.s. for xmr (and vpi_) processing but do not know if done
// SJM 04-07-11 - IF FREEING GEN BLKS COULD GO HERE
}

/*
 * free defparam guts during pre fixup nl stop
 *
 * SJM 09-09-11 - trying new defparam algorithm for fixup nl list
 * whatever defparams are added are left - no freeing and restoring
 * but must empty so can be filled again with possibly quite different
 * inst tree from generates
 */
static void empty_dfp_flds(struct dfparam_t *dfpp)
{
 /* should have been freed during defparam resolution on last pass */
 /* DBG remove -- */
 if (dfpp->dfpiis != NULL || dfpp->last_dfpi != -1)
  __misc_terr(__FILE__, __LINE__);
 /* -- */
 if (dfpp->gdfpnam != NULL)
  {
   __my_free(dfpp->gdfpnam, strlen(dfpp->gdfpnam) + 1);
   dfpp->gdfpnam = NULL;
  }
 if (dfpp->targsyp != NULL) dfpp->targsyp = NULL;
 /* can just set to nil, actual rooted dfps already moved to dsgn wide list */
 if (dfpp->rooted_dfps != NULL) dfpp->rooted_dfps = NULL;
 if (dfpp->dfptskp != NULL) dfpp->dfptskp = NULL;
}

/*
 * INTERMEDIATE LEVEL NL FIXUP ROUTINES
 */

/*
 * rearrange and build module and inst. connections for further processing
 * also set dag levels and connect inst. pins to module ports
 *
 * parameter values still unknown but this builds global strength anal. and
 * splitting info
 */
static int32 fix_modcell_nl(void)
{
 struct mod_t *mdp;

 /* first need to know static instantiations */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* F for self instantiation and cannot continue */
   count_static_instances(mdp);

   __pop_wrkitstk();
  }

 /* set dag levels */
 if (!chk_dag()) return(FALSE);
 return(TRUE);
}

/*
 * distinguish number of times module statically instantiated
 * 0 means top, 1 exactly once, 2 more than once
 * value here is static unflattened number of instantiations
 */
static int32 count_static_instances(struct mod_t *mdp)
{
 int32 ii; 
 struct inst_t *ip;
 struct sy_t *syp;
 struct mod_t *imdp;

 for (ii = 0; ii < mdp->minum; ii++)
  {
   ip = &(mdp->minsts[ii]);
   syp = ip->imsym;
   imdp = syp->el.emdp;
   if (mdp == imdp)
    __gfterr(312, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
     "INTERNAL - module instantiates itself");
   /* only need counts of 0 (never), 1 (exactly once), 2 (more than once) */
   if (imdp->minstnum == 0) imdp->minstnum = 1;
   else if (imdp->minstnum == 1) imdp->minstnum = 2;
  }
 return(TRUE);
}

/*
 * check to see if any instantiation loops and set levelized level
 * for multiple instantiations level is level of lowest one
 */
static int32 chk_dag(void)
{
 int32 ii, i, change, allmark;
 struct mod_t *mdp;
 struct inst_t *ip;
 struct mod_t *imdp;

 __dagmaxdist = 0;
 /* previously initialized to -1 (unmarked) */
 for (allmark = TRUE, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->minsts == NULL) mdp->mlpcnt = 0;
   else allmark = FALSE;
  }
 if (allmark) return(TRUE);
 /* level 0 means no contained instances, mark all level i modules */
 for (i = 1; i < MAXCIRDPTH; i++)
  {
   change = FALSE;
   /* assume all marked */
   allmark = TRUE;
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     /* if marked nothing to do */
     if (mdp->mlpcnt != -1) continue;

     for (ii = 0; ii < mdp->minum; ii++)
      {
       ip = &(mdp->minsts[ii]);
       imdp = ip->imsym->el.emdp;
       /* cannot mark if unmarked or mark this time == i */
       if (imdp->mlpcnt == -1 || imdp->mlpcnt == i)
        {
         /* ---
         if (__debug_flg)
          {
           __dbg_msg("++at level %d cannot mark %s because of %s\n", i,
            mdp->msym->synam, imdp->msym->synam);
          }
         ---- */
         goto cannot_mark;
       }
      }
     mdp->mlpcnt = i;
     /* ---
     if (__debug_flg)
      __dbg_msg("++at level %d marking %s\n", i, mdp->msym->synam);
     --- */
     change = TRUE;
     continue;

cannot_mark:
     allmark = FALSE;
    }
   if (allmark) { __dagmaxdist = i; return(TRUE); }
   if (!change) break;
  }
 __pv_err(735,
  "design contains indirect (length > 1) self instantiation loop");
 return(FALSE);
}

/*
 * ROUTINES TO SPLIT INSTS, REBUILD AND EXPAND FOR GATE/INST ARRAYS 
 */

/*
 * split (copy) module types for which pound params used in arrays of
 * gates or instances declaration width ranges
 */
static void do_iarr_splitting(void)
{
 int32 ii, mlevel;
 struct mod_t *mdp; 
 struct inst_t *ip;
 struct mod_t *imdp;

 /* start will all modules that contain instances only of modules */
 /* which themselves contain no instances and work upward */ 
 for (mlevel = 1; mlevel <= __dagmaxdist; mlevel++) 
  {
   /* SJM 03/16/04 - notice processing one up and splitting (if needed) */
   /* contained instances - therefore mlevel of md lev hdr list not chged */
   /* inside this loop */
   for (mdp = __mdlevhdr[mlevel]; mdp != NULL; mdp = mdp->mlevnxt)
    {
     __push_wrkitstk(mdp, 0);
     
     /* go through instances in current module */
     for (ii = 0; ii < __inst_mod->minum; ii++)
      {
       ip = &(__inst_mod->minsts[ii]);
       if (ip->ipxprtab == NULL) continue;

       /* imdp is module type of instance that has pound params */
       imdp = ip->imsym->el.emdp;
       __sfnam_ind = ip->isym->syfnam_ind;
       __slin_cnt = ip->isym->sylin_cnt;

//AIV? ===> one of these doesn't do anything - see below
       /* because static src inst loc. has pnd params, if any gate must */
       /* try to set any gate range params */
       /* AIV 07/12/04 - old checking and was wrong nad mark gia rng checks */
       if (!imdp->mgia_rngdone)
        {
         mark_gia_rng_params(imdp);
         imdp->mgia_rngdone = TRUE;
        }

       /* eliminate if instance does not an array of insts */
       if (ip->i_giap == NULL) continue;

       /* SJM 07-06-07 - removed repeated gia rng param marking - redundant */

       if (!down_hasgiarngdet_param(imdp)) continue;

       /* even if no split (one place in source instantiated) need to eval */ 
       /* mark that some modules have width determining pnd params and mark */
       /* that this one does */
       ip->imsym->el.emdp->mpndprm_ingirng = TRUE;

       /* if only one place in source instantiated, must not split */
       /* because would create never instantiated instance */
       if (imdp->flatinum == 1 || imdp->flatinum == __inst_mod->flatinum)
        continue; 

       /* this does not need to update miarr since parallel minsts updated */
       split_upd_mod(imdp, ip, mlevel, FALSE); 
       /* AIV 07/26/11 - this needs to be set again after split not before */
       /* AIV 10/16/10 - set the level for searching for duplicate module */
       /* paramter spliting */
       mdp->mlevel = mlevel;
      }
     __pop_wrkitstk();
    }
  }
}

/*
 * mark all parameters that are used in arrays of gate/inst ranges
 * inside module pmdp
 *
 * splitting later only if these parameters are passed as pound params
 * caller will mark module 
 */
static void mark_gia_rng_params(struct mod_t *pmdp)
{
 int32 gi, ii;
 struct gate_t *gp;
 struct inst_t *ip;
 struct gia_aux_t *giap;

 if (pmdp->m_has_garrs)
  {
   for (gi = 0; gi < pmdp->mgnum; gi++)
    {
     gp = &(pmdp->mgates[gi]);
     if ((giap = gp->g_giap) == NULL) continue;

     if (in_giarng_markparam(giap, giap->giax1)) pmdp->mpndprm_ingirng = TRUE;
     if (in_giarng_markparam(giap, giap->giax2)) pmdp->mpndprm_ingirng = TRUE;
    }
  }
  
 if (pmdp->m_has_iarrs)
  {
   for (ii = 0; ii < pmdp->minum; ii++)
    {
     ip = &(pmdp->minsts[ii]);
     if ((giap = ip->i_giap) == NULL) continue;

     if (in_giarng_markparam(giap, giap->giax1)) pmdp->mpndprm_ingirng = TRUE;
     if (in_giarng_markparam(giap, giap->giax2)) pmdp->mpndprm_ingirng = TRUE;
    }
  }
}

/*
 * mark parmeters (nets) in arrays of gate/inst range parameters
 *
 * only called for expressions in gate/inst range indices
 */
static int32 in_giarng_markparam(struct gia_aux_t *giap, struct expr_t *xp)
{
 int32 rv1, rv2;
 struct net_t *np;

 rv1 = rv2 = FALSE;
 if (__isleaf(xp))
  {
   if (xp->optyp == ID && xp->lu.sy->sytyp == SYM_N)
    {
     np = xp->lu.sy->el.enp; 
     if (np->n_isaparam)
      {
       np->nu.ct->n_in_gia_rng = TRUE;
       giap->gia_rng_has_pnd = TRUE;
       __design_gia_pndparams = TRUE;
       rv1 = TRUE; 
      }
    }
   return(rv1);
  }
 if (xp->lu.x != NULL) rv1 = in_giarng_markparam(giap, xp->lu.x);
 if (xp->ru.x != NULL) rv2 = in_giarng_markparam(giap, xp->ru.x);
 return(rv1 || rv2);
}

/*
 * return T if any down instance (module type ipmdp) pound parameter
 * determines array of gates or instances range
 */
static int32 down_hasgiarngdet_param(struct mod_t *ipmdp)
{
 int32 pi;
 struct net_t *parm_np;
 
 /* if # param list short ok, do not bother changing missing at end */
 /* only check params actually set if short list */
 for (pi = 0; pi < ipmdp->mprmnum; pi++)
  {
   parm_np = &(ipmdp->mprms[pi]);

   if (parm_np->nu.ct->n_in_gia_rng)
    {
     if (__debug_flg)
      {
       __dbg_msg(
        "+++ split module %s, # param %s in array of inst/gate range expr.\n",
        ipmdp->msym->synam, parm_np->nsym->synam);
      }
     return(TRUE);
    }
   /* move to next target module pound param */
  }
 if (__debug_flg)
  __dbg_msg(
   "+++ no need to split module %s because of pound param in gate/inst range",
   ipmdp->msym->synam);
 return(FALSE);
} 

/*
 * ROUTINES TO BUILD TOP VIRTUAL INSTANCES
 */

/*
 * build the list of instances for uninstantiated top level modules
 * this builds inst_t (static inst) for each top level modules
 * and makes top itab of index point to it
 *
 * notice top module may be split, so this new elements can be added later
 *
 * top_iptab points to created instances since for top module and instance
 * have same name - top_iptab and it_roots are parallel arrays, top_ipind 
 * ins sorted index into both top_iptab and it_roots since they are ||
 */
static void bld_top_virtinsts(void)
{
 int32 tpii, ii;
 struct mod_t *mdp;
 struct inst_t *ip;
 struct sy_t *syp;
 struct itree_t *itp;

 /* count number of top level modules */ 
 __numtopm = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* descend to count only from top level modules */
   if (mdp->minstnum != 0) continue;

   /* AIV 08/24/11 - if generated do not print warning message */
   /* these are later linked out - see fixup_nl_linkout_gencells */
   if (!mdp->m_maybe_gened)
    {
     /* top modules will have is cell bit on if configs used */
     if (mdp->m_iscell && __map_files_hd == NULL)
      {
#ifndef __CVC_RT__
       __gfwarn(597, mdp->msym->syfnam_ind, mdp->msym->sylin_cnt,
        "top level module %s in `celldefine region but cannot be a cell",
         mdp->msym->synam);
#endif
       mdp->m_iscell = FALSE;
      }
    }
   __numtopm++;
  }
 if (__numtopm == 0) return;
 __top_itab = (struct inst_t **)
  __my_malloc(__numtopm*sizeof(struct inst_t *));
 for (tpii = -1, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->minstnum != 0) continue;
   /* need 1 itree inst for each top level module because itp->itip */
   /* accessed during simulation */
   ip = (struct inst_t *) __my_malloc(sizeof(struct inst_t));
   __top_itab[++tpii] = ip;
   /* initialize for unused by top fields */
   __init_inst(ip);

   /* need to allocate symbol here - because may need name */
   /* but this symbol is in no symbol table - cannot be looked up */
   /* because there is no virtual top level module */
   syp = (struct sy_t *) __my_malloc(sizeof(struct sy_t));
   /* copying here in case implementing name removal comp. directives */
   syp->synam = __pv_stralloc(mdp->msym->synam);
   syp->sytyp = SYM_I;
   /* notice all symbols add during input phase */
   syp->sydecl = TRUE;
   syp->el.eip = ip;
   syp->syfnam_ind = mdp->msym->syfnam_ind;
   syp->sylin_cnt = mdp->msym->sylin_cnt;
   syp->spltsy = NULL;

   ip->isym = syp; 
   ip->imsym = mdp->msym;
   /* top level modules have exactly 1 instance */
   mdp->flatinum = 1;
   ip->ipxprtab = NULL;
   ip->pprm_explicit = FALSE;
   ip->ip_explicit = FALSE;
   ip->ipins = NULL;
  }
 __top_ipind = (int32 *) __my_malloc(__numtopm*sizeof(int32)); 
 for (ii = 0; ii < __numtopm; ii++) __top_ipind[ii] = ii;
 qsort(__top_ipind, (size_t) __numtopm, sizeof(int32), topip_cmp);

 /* table of pointers to root entries */
 __it_roots = (struct itree_t **)
  __my_malloc(__numtopm*sizeof(struct itree_t *));

 /* allocate root itp entries for each top level module */
 for (ii = 0; ii < __numtopm; ii++)
  {
   /* alloc sets itree value */
   itp = (struct itree_t *) __my_malloc(sizeof(struct itree_t));
   __it_roots[ii] = itp;
   __init_itree_node(itp);
   itp->itip = __top_itab[ii];
   itp->up_it = NULL;
   /* since top instance number must be 0 */
   itp->itinum = 0;
  }
}

/*
 * comparison routines for sorting top modules index
 */
static int32 topip_cmp(const void *ii1, const void *ii2)
{
 struct inst_t *ip1, *ip2;

 ip1 = __top_itab[*((int32 *) ii1)];
 ip2 = __top_itab[*((int32 *) ii2)];
 return(strcmp(ip1->imsym->synam, ip2->imsym->synam));
}

extern void __init_itree_node(struct itree_t *itp)
{
 itp->up_it = NULL;
 itp->in_its = NULL;
 itp->itip = NULL;
 itp->itinum = 0;
 itp->it_idp = NULL;
}

/*
 * routine to reset gate/inst array ranges and rebuild gia aux records
 *
 * this also builds a provisional itree and then free its - final itree 
 * built later
 *
 * SJM 07-06-07 now may need to rebuild a second time if there is any
 * splitting because of the use of pound params in gi ranges
 */
static void rebld_dsgn_giars_from_split(int32 second_call)
{
 /* SJM 07-07-07 - if second call must start with pre-gi elements built */
 /* gate/inst/itree net list data structures - this shrinks back */
 /* but must map from well formed itree structure to itree structure */
 /* AIV 06/05/09 - passing flag to unbld_ was wrong it is always not FALSE */
 if (second_call) unbld_iarrs_and_garrs();

 /* save all module (not task/func) parameter values */
 save_all_param_vals();

 set_gia_ranges();
 /* rebuild array and gate tables in module with g/i arrays */
 rebld_mod_g_and_i_arrs();

 /* final step free saved param value records */
 free_all_param_vals();
}

/*
 * routine to unbld (restore) all gate and g/i arr structures to pre-bld
 *
 * SJM 07-07-07 - new algorithm requires freeing all the gate and inst
 * and symbol table added g/i vector elements
 *
 * algorithm: after pound param splitting - original build needed since need
 * expanded itree for defparam processing, after defparam processing need
 * to do pound param splitting, after pound param splitting now may have new
 * iarr and * or giarr parameter values that can be in the array ranges
 * - old algorithm fixed the pound param ranges before defparam processing
 * but now have examples (from generate?) that require rebuilding a 2nd time
 *
 * routine free and then allocated new giarr and miarr if needed with
 * no entries for expanded arrays of gates or instances - then normal
 * rebld routine works
 *
 * SJM 07-07-07 - new algorithm seems to be relaxation by resolving
 * g/i instances and then undoing when know more and resolving again
 * but seems to be order dependent so stupid
 *
 * SJM 07-07-07 - this is one routine since during this routine, itree
 * not well formed
 *
 * AIV 06/05/09 - removed chk_param flag it is always FALSE
 *
 * SJM 05-04-10 - this must turn off expanded
 */
static void unbld_iarrs_and_garrs(void)
{
 int32 gi, mi, syi, syi2, newgnum, newinum, new_stsiz;
 struct mod_t *mdp;
 struct gate_t *gptab, *gp, *new_gp;
 struct inst_t *iptab, *ip, *new_ip; 
 struct srcloc_t **sloctabp;
 struct symtab_t *sytp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->m_has_garrs && !mdp->m_has_iarrs) continue;

   /* DBG remove -- */
   if (__debug_flg)
    {
     __dbg_msg(" ## mod's symbol table for %s size %d:\n", mdp->msym->synam,
      mdp->msymtab->numsyms); 
     for (syi = 0; syi < mdp->msymtab->numsyms; syi++) 
      {
       __dbg_msg("  ndx %d mdp symbol %s\n", syi,
        mdp->msymtab->stsyms[syi]->synam);
      }
    }
   /* --- */

   if (mdp->m_has_garrs)
    {
     /* rebld mod's gate table */
     /* first count */
     for (newgnum = 0, gi = 0; gi < mdp->mgnum; gi++)
      {
       gp = &(mdp->mgates[gi]);
       /* case one - not array of gates */
       if (!gp->gsym->sy_gia_added)
        {
         /* DBG remove -- */
         if (gp->g_giap != NULL) __misc_terr(__FILE__, __LINE__);
         /* --- */
         newgnum++;
         continue;
        }
       /* DBG remove -- */
       if (gp->g_giap == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */

       /* only keep and count if this is the first */
       if (gp->g_giap->gia_is_base_first) newgnum++;
      }

     /* now alloc and copy */
     gptab = (struct gate_t *) __my_malloc(newgnum*sizeof(struct gate_t));
     for (newgnum = 0, gi = 0; gi < mdp->mgnum; gi++)
      {
       gp = &(mdp->mgates[gi]);

       if (!gp->gsym->sy_gia_added)
        {
         /* simple copy non array gates gate */
         new_gp = &(gptab[newgnum]);
         *new_gp = *gp;
         new_gp->gsym->el.egp = new_gp;
         newgnum++;
         continue;
        }
       /* DBG remove -- */
       if (gp->g_giap == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */

       /* SJM 04-21-10 - undoing xpnd works here since pins still all vec */
       if (gp->g_giap->gia_is_base_first)
        {
         /* this is the base (1st) - gate has wrong symbol but giap has right */
         /* base symbol that becomes put back symbol for the gate which */
         /* is the first of a gi range */
         /* 07-12-07 - only fill gptab for un-built if first */
         new_gp = &(gptab[newgnum]);
         *new_gp = *gp;
         new_gp->gsym = gp->g_giap->gia_base_syp;
         new_gp->gsym->el.egp = new_gp;
         /* turn off expanded */
         new_gp->g_giap->gia_xpnd = FALSE;
         newgnum++;
        }
       else
        {
         /* SJM 04-25-10 - now have gia aux rec for every replicate gate-free */
         __free_xtree(gp->g_giap->giax1);
         __free_xtree(gp->g_giap->giax2);
         __my_free(gp->g_giap, sizeof(struct gia_aux_t));
         gp->g_giap = NULL;
        }
      }
     /* now free and replace */
     __my_free(mdp->mgates, mdp->mgnum*sizeof(struct gate_t));
     mdp->mgates = gptab;
     mdp->mgnum = newgnum;
    }

   if (mdp->m_has_iarrs)
    {
     /* rebld mod's minsts */
     /* first count */
     for (newinum = 0, mi = 0; mi < mdp->minum; mi++)
      {
       ip = &(mdp->minsts[mi]);
       if (!ip->isym->sy_gia_added)
        {
         /* DBG remove -- */
         if (ip->i_giap != NULL) __misc_terr(__FILE__, __LINE__);
         /* --- */
         newinum++;
         continue;
        }
       /* DBG remove -- */
       if (ip->i_giap == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */

       /* only keep and count if this is the first */
       if (ip->i_giap->gia_is_base_first) newinum++;
      }
     /* now alloc and copy inst array and parallel src loc tab */
     iptab = (struct inst_t *) __my_malloc(newinum*sizeof(struct inst_t));
     sloctabp = (struct srcloc_t **)
      __my_malloc(newinum*sizeof(struct srcloc_t *));

     for (newinum = 0, mi = 0; mi < mdp->minum; mi++)
      {
       ip = &(mdp->minsts[mi]);

       if (!ip->isym->sy_gia_added)
        {
         /* case 1: non inst array */
         /* DBG remove -- */
         if (ip->i_giap != NULL) __misc_terr(__FILE__, __LINE__);
         /* --- */

         /* simple copy non array gates gate */
         new_ip = &(iptab[newinum]);
         *new_ip = *ip;
         new_ip->isym->el.eip = new_ip;
         /* SJM 07-13-07 - new algorithm all iploctab's for array of inst */
         /* shared - i.e. really only one but many may point to it */
         sloctabp[newinum] = mdp->iploctab[mi];

         newinum++;
         continue;
        }
       /* DBG remove -- */
       if (ip->i_giap == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */

       /* 07-11-07 - only copy giatab for first one - this is the unbld */
       if (ip->i_giap->gia_is_base_first)
        { 
         /* this is the base - isym wrong symbol but giap has right */
         /* base symbol that becomes put back symbol for the inst which */
         /* is the first of a mi range */
         /* 07-12-07 - only fill gptab for un-built if first */
         new_ip = &(iptab[newinum]);
         *new_ip = *ip;
         new_ip->isym = ip->i_giap->gia_base_syp;
         new_ip->isym->el.eip = new_ip;
         /* turn off expaned */
         new_ip->i_giap->gia_xpnd = FALSE;

         /* SJM 07/13-07 - selects out src locs - know just ptrs for expanded */
         sloctabp[newinum] = mdp->iploctab[mi];
         newinum++;
        }
       else
        {
//SJM 05-04-10 - LOOKATME???? - think this is wrong !!!!
         /* SJM 04-25-10 - now have gia aux rec for every replicate inst-free */
         __free_xtree(ip->i_giap->giax1);
         __free_xtree(ip->i_giap->giax2);
         __my_free(ip->i_giap, sizeof(struct gia_aux_t));
         ip->i_giap = NULL;
        }
      }

     /* SJM 07-07-07 - do not need to change minstnum since fixed in rebld */  
     /* now free and replace */
     __my_free(mdp->minsts, mdp->minum*sizeof(struct inst_t));

     /* SJM 07-13-07 free tab of ptrs to per inst per port src loc */
     /* records, since shrinking back sloctab now has rigtt ptrs */
     /* DBG remove -- */
     if (mdp->iploctab == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     __my_free(mdp->iploctab, mdp->minum*sizeof(struct srcloc_t *));

     mdp->minsts = iptab;
     mdp->iploctab = sloctabp; 
     mdp->minum = newinum;

     /* count only non added symbols, since all added gone */
     sytp = mdp->msymtab;
     new_stsiz = 0;
     for (syi = 0; syi < (int32) sytp->numsyms; syi++) 
      {
       /* count only not added */
       if (!sytp->stsyms[syi]->sy_gia_added) new_stsiz++;
      }
     __wrkstab = (struct sy_t **) __my_malloc(new_stsiz*sizeof(struct sy_t *));
     for (syi = 0,syi2 = 0; syi < (int32) sytp->numsyms; syi++)
      {
       if (sytp->stsyms[syi]->sy_gia_added) continue; 
       /* DBG remove -- */
       if (__debug_flg)
        {
         __dbg_msg(" ## adding symbol %s wrkstab position %d\n",
          sytp->stsyms[syi]->synam, syi2);
        }
       /* --- */
       __wrkstab[syi2++] = sytp->stsyms[syi];
      }
     /* --- */
     if (new_stsiz != syi2) __misc_terr(__FILE__, __LINE__);
     /* DBG remove -- */
     qsort(__wrkstab, (word32) new_stsiz, sizeof(struct sy_t *),
      __gia_sym_cmp);
     __my_free(mdp->msymtab->stsyms, sytp->numsyms*sizeof(struct sy_t *)); 
     mdp->msymtab->stsyms = __wrkstab;
     mdp->msymtab->numsyms = new_stsiz;
    }
  }
}

/*
 *
 * save all design instance (not task/func) parameters values
 *
 * only callsd if need to set gia ranges from params 
 *
 * this is point where gia ranges set so parameters evaluated but must
 * be put back because later defparams may change final values
 *
 * AIV 09/27/06 - since can't be changed do not need to save local params
 */
static void save_all_param_vals(void)
{
 int32 pi, nbytes;
 struct mod_t *mdp;
 struct net_t *parm_np;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mprmnum == 0) continue;

   for (pi = 0, parm_np = &(mdp->mprms[0]); pi < mdp->mprmnum; pi++, parm_np++)
    {
     nbytes = 2*WRDBYTES*wlen_(parm_np->nwid);
     parm_np->nu2.wp = (word32 *) __my_malloc(nbytes);
     memcpy(parm_np->nu2.wp, parm_np->prm_nva.wp, nbytes);
    }
  }
}

/*
 * free all param values - must do this so can reuse nu2 field 
 */
static void free_all_param_vals(void)
{
 int32 pi;
 struct mod_t *mdp;
 struct net_t *parm_np;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mprmnum == 0) continue;

   for (pi = 0, parm_np = &(mdp->mprms[0]); pi < mdp->mprmnum; pi++, parm_np++)
    {
     /* DBG remove --- */
     if (parm_np->nu2.wp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     __my_free(parm_np->nu2.wp, 2*WRDBYTES*wlen_(parm_np->nwid));
     parm_np->nu2.wp = NULL;
    }
  }
}

/*
 * evaluate arrays of gates and instances ranges to number
 *
 * depends on convention that arrays of gate/inst range indices can use
 * pound params (parmeter values changed by # parameters) but evaluation
 * happens before defparams set (and splitting occurs) so values converted
 * to number because component parameters may ultimately have different value
 *
 * here because no defparams values are static instance tree dependent, i.e. 
 * do not need to build and use itree
 *
 * trick is that because by here all modules with array of gate or instance
 * ranges determined by pound params, can set range as number
 */
static void set_gia_ranges(void)
{
 int32 gi, ii2;
 struct mod_t *mdp;
 struct gate_t *gp;
 struct inst_t *ip;
 struct gia_aux_t *giap;

 /* assume some ranges do not have pound params because not much work */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* if module has arrays of gates expand first */
   if (mdp->m_has_garrs)
    {
     for (gi = 0; gi < mdp->mgnum; gi++)
      {
       gp = &(mdp->mgates[gi]);

       /* skip non array style gates */ 
       if ((giap = gp->g_giap) == NULL) continue;
       /* if has pound param need to handle in special code below */
       if (giap->gia_rng_has_pnd) continue;

       eval1_arr_of_gates_rng(gp, NULL);
      }
    }
   if (mdp->m_has_iarrs)
    {
     for (ii2 = 0; ii2 < mdp->minum; ii2++)
      {
       ip = &(mdp->minsts[ii2]);
       /* skip non array style instances */ 
       if ((giap = ip->i_giap) == NULL) continue;
       /* if has pound param need to handle in special code below */
       if (giap->gia_rng_has_pnd) continue;

       eval1_arr_of_insts_rng(ip, NULL);
      }
    }
   __pop_wrkitstk();
  }

 /* if design has no pound params in arrays of g/i ranges, nothing to do */
 if (__design_gia_pndparams) set_pnd_gi_rnges();
}

/*
 * evaluate array of gates ranges in module mdp 
 *
 * for non pound param case just works on raw expr
 * for pound param case, code called to save and set elaborated (fixed)
 * param values from propagating pound params down then afterwards unsaving
 * elaborated values because defparams may change
 */
static void eval1_arr_of_gates_rng(struct gate_t *gp, struct itree_t *itp)
{
 int32 bad_rng;
 struct gia_aux_t *giap;
 struct xstk_t *xsp1, *xsp2;

 giap = gp->g_giap;
 /* if error, since do not know range, convert to non array of gates */
 bad_rng = FALSE;

 if (!gi_ndxexpr_chk(giap->giax1, gp->gsym->syfnam_ind,
  gp->gsym->sylin_cnt, "of gates first")) bad_rng = TRUE;

 /* save and set pound params by propagating up initial vals down */
 if (!bad_rng && itp != NULL) set_gia_expr_pndparms(giap->giax1, itp);

 /* although impossible to have any inst. specific values here */
 /* need something on it stk */
 if (itp == NULL)
  {
   /* if no passed itp - use wrk dummy inst (right mod) */
   xsp1 = __eval_xpr(giap->giax1);
  }
 else
  {
   __push_itstk(itp);
   xsp1 = __eval_xpr(giap->giax1);
   __pop_itstk();
  }

 /* unsave if pound case */
 if (!bad_rng && itp != NULL) unsave_gia_expr_pndparms(giap->giax1, itp);

 if (!gi_ndxval_chk(xsp1, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
  "of gates first")) bad_rng = TRUE;

 if (!gi_ndxexpr_chk(giap->giax2, gp->gsym->syfnam_ind,
  gp->gsym->sylin_cnt, "of gates second")) bad_rng = TRUE;

 /* save and set pound params by propagating up initial vals down */
 if (!bad_rng && itp != NULL) set_gia_expr_pndparms(giap->giax2, itp);

 if (itp == NULL)
  {
   /* if no passed itp - use wrk dummy inst (right mod) */
   xsp2 = __eval_xpr(giap->giax2);
  }
 else
  {
   __push_itstk(itp);
   xsp2 = __eval_xpr(giap->giax2);
   __pop_itstk();
  }

 if (!bad_rng && itp != NULL) unsave_gia_expr_pndparms(giap->giax2, itp);

 if (!gi_ndxval_chk(xsp2, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
  "of gates second")) bad_rng = TRUE;
 /* if error do not know range - convert back to one gate */
 if (!bad_rng) 
  {
   giap->gia1 = (int32) xsp1->ap[0];
   giap->gia2 = (int32) xsp2->ap[0];
  }
 __pop_xstk();
 __pop_xstk();
}

/*
 * check a gate or instance array index constant expression 
 * returns F on error 
 */
static int32 gi_ndxexpr_chk(struct expr_t *xp, int32 lfnind, int32 lcnt,
 char *emsg) 
{
 int32 rv, sav_slin_cnt, sav_sfnam_ind;
 
 /* SJM 01-22-09 - checking can now emit errors, so need to save and set */
 sav_slin_cnt = __slin_cnt;
 sav_sfnam_ind = __sfnam_ind;
 __slin_cnt = lcnt;
 __sfnam_ind = lfnind;

 if (__expr_has_glb(xp) || !__chk_paramexpr(xp, 0))
  {
   __sgferr(1161, 
    "array %s declaration index expression %s error - pound parameters and constants only",
    emsg, __msgexpr_tostr(__xs, xp));
   rv = FALSE;
  }
 else rv = TRUE;

 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
 return(rv);
}

/*
 * check a gate or instance array value for 32 bits non x/z
 * emits error and returns F on error
 *
 * LOOKATME - maybe need warn or inform if >32 bits but higher 0's
 */
static int32 gi_ndxval_chk(struct xstk_t *xsp, int32 lfnind, int32 lcnt, char *emsg)
{
 if (xsp->xslen > WBITS)
  {
   if (!vval_is0_(&(xsp->ap[1]), xsp->xslen - 64)
    || !vval_is0_(xsp->bp, xsp->xslen))
    {
     __gferr(1189, lfnind, lcnt,
      "array %s declaration index value %s not required %d bit non x/z number",
      emsg, __regab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE),
      WBITS);
     return(FALSE);
    }
  }
 return(TRUE);
}

/*
 * evaluate array of instances ranges for one inst
 *
 * for non pound param case just works on raw expr
 * for pound param case, code called to save and set elaborated (fixed)
 * param values from propagating pound params down then afterwards unsaving
 * elaborated values because defparams may change
 */
static void eval1_arr_of_insts_rng(struct inst_t *ip, struct itree_t *itp)
{
 int32 bad_rng;
 struct gia_aux_t *giap;
 struct xstk_t *xsp1, *xsp2;

 giap = ip->i_giap;
 /* know only first (master) auxiliary extra array non nil */
 /* if error, since do not know range, convert to non array of gates */
 bad_rng = FALSE;

 if (!gi_ndxexpr_chk(giap->giax1, ip->isym->syfnam_ind,
  ip->isym->sylin_cnt, "of instances first")) bad_rng = TRUE;

 /* save and set pound params by propagating up initial vals down */
 if (!bad_rng && itp != NULL) set_gia_expr_pndparms(giap->giax1, itp);

 /* although impossible to have any inst. specific values here */
 /* need something on it stk */
 if (itp == NULL)
  {
   /* if no passed itp - use wrk dummy inst (right mod) */
   xsp1 = __eval_xpr(giap->giax1);
  }
 else
  {
   __push_itstk(itp);
   xsp1 = __eval_xpr(giap->giax1);
   __pop_itstk();
  }

 /* unsave if pound case */
 if (!bad_rng && itp != NULL) unsave_gia_expr_pndparms(giap->giax1, itp);

 if (!gi_ndxval_chk(xsp1, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
  "of instances first")) bad_rng = TRUE;

 if (!gi_ndxexpr_chk(giap->giax2, ip->isym->syfnam_ind,
  ip->isym->sylin_cnt, "of gates second")) bad_rng = TRUE;

 /* save and set pound params by propagating up initial vals down */
 if (!bad_rng && itp != NULL) set_gia_expr_pndparms(giap->giax2, itp);

 if (itp == NULL)
  {
   /* if no passed itp - use wrk dummy inst (right mod) */
   xsp2 = __eval_xpr(giap->giax2);
  }
 else
  {
   __push_itstk(itp);
   xsp2 = __eval_xpr(giap->giax2);
   __pop_itstk();
  }

 /* unsave if pound case */
 if (!bad_rng && itp != NULL) unsave_gia_expr_pndparms(giap->giax2, itp);

 if (!gi_ndxval_chk(xsp2, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
  "of instances second")) bad_rng = TRUE;
 /* if error do not know range - convert back to one gate */
 if (!bad_rng)
  {
   giap->gia1 = (int32) xsp1->ap[0];
   giap->gia2 = (int32) xsp2->ap[0];
  }
 __pop_xstk();
 __pop_xstk();
}

/*
 * set all module instance gi ranges with pound params
 *
 * only need to do once per module because modules with pound params
 * in gi ranges always split off to one instance
 *
 * final hard case where need itree that is discarded after this step
 */
static void set_pnd_gi_rnges(void)
{
 int32 ii;
 struct itree_t *itp;
 struct mod_t *mdp;

 __bld_flat_itree();

 /* know top modules never have pound params */
 for (ii = 0; ii < __numtopm; ii++)
  {
   itp = __it_roots[ii];
   mdp = itp->itip->imsym->el.emdp;
   set2_pnd_gi_rnges(mdp, itp);
  }

 /* last step free itree - need to rebuild after defparam splitting */
 __free_flat_itree();
}

/*
 * descend down in itree setting pound param gia ranges
 * 
 * when see first instance of module set ranges for all instances
 * and mark - after that just ignore instances of module
 */

static void set2_pnd_gi_rnges(struct mod_t *up_mdp, struct itree_t *up_itp)
{
 int32 gi, ii, ii2;
 struct mod_t *imdp;
 struct gate_t *gp;
 struct inst_t *ip;
 struct itree_t *itp;
 struct gia_aux_t *giap;

 /* first descend */
 for (ii = 0; ii < up_mdp->minum; ii++)
  {
   itp = &(up_itp->in_its[ii]);
   /* once module done, know all under also done - no need to descend */
   imdp = itp->itip->imsym->el.emdp;

   /* need to descend even if does not have any in gia range pnd params */
   set2_pnd_gi_rnges(imdp, itp);
  }
 /* when this returns will be done even if none in range */
 if (!up_mdp->mpndprm_ingirng) return;

 /* eval arrays of g/i ranges containing pnd params - others already done */
 if (up_mdp->m_has_garrs)
  {
   for (gi = 0; gi < up_mdp->mgnum; gi++)
    {
     gp = &(up_mdp->mgates[gi]);
     /* skip non array style gates */ 
     if ((giap = gp->g_giap) == NULL) continue;

     /* if does not contain pound param already done */
     if (!giap->gia_rng_has_pnd) continue;

     __push_wrkitstk(up_mdp, 0);
     eval1_arr_of_gates_rng(gp, up_itp);
     __pop_wrkitstk();
    }
  }
 if (up_mdp->m_has_iarrs)
  {
   for (ii2 = 0; ii2 < up_mdp->minum; ii2++)
    {
     ip = &(up_mdp->minsts[ii2]);

     /* skip non array style instances */ 
     if ((giap = ip->i_giap) == NULL) continue;
     /* if does not contain pound param already done */
     if (!giap->gia_rng_has_pnd) continue;

     __push_wrkitstk(up_mdp, 0);
     eval1_arr_of_insts_rng(ip, up_itp);
     __pop_wrkitstk();
    }
  }
}
    
/*
 * set all pound params in one g/i array range expression
 *
 * when done know all params in g/i array range expr. values elaborated (fixed)
 */
static void set_gia_expr_pndparms(struct expr_t *xp, struct itree_t *itp)
{
 struct net_t *np;

 if (__isleaf(xp))
  {
   if (xp->optyp == ID && xp->lu.sy->sytyp == SYM_N)
    {
     np = xp->lu.sy->el.enp; 
     if (np->n_isaparam) set1_garr_pndparm(np, itp); 
    }
   return;
  }
 if (xp->lu.x != NULL) set_gia_expr_pndparms(xp->lu.x, itp);
 if (xp->ru.x != NULL) set_gia_expr_pndparms(xp->ru.x, itp);
}

/*
 * for parameter determine if pound and if so set value by setting
 * values in up instance pound expr and evaluating it
 * new up value is then set as value of down parameter 
 * may need to work up to top of itree
 */
static void set1_garr_pndparm(struct net_t *np, struct itree_t *itp) 
{
 int32 pndpi;
 struct itree_t *up_itp;
 struct mod_t *up_mdp;
 struct inst_t *up_ip;
 struct expr_t *up_pndxp;
 struct xstk_t *xsp;

 /* may need to access parameter (not pound) in top level module */
 up_itp = itp->up_it;
 /* if top or no pound params or no pound expr. passed down for this, done */
 up_ip = itp->itip;
 if (up_ip->ipxprtab == NULL) return;
 up_mdp = up_ip->imsym->el.emdp;
 pndpi = ((byte *) np - (byte *) up_mdp->mprms)/sizeof(struct net_t);
 if (up_ip->ipxprtab[pndpi] == NULL) return;

 /* know this is pound param */
 up_pndxp = up_ip->ipxprtab[pndpi];

 /* work up evaluating parmeters changing pound params to passed down val */
 /* this sets values in pound passed (up) expr - if it contains pound */
 /* params recursively repeats up as far as needed (maybe to top) */
 set_gia_expr_pndparms(up_pndxp, up_itp);
 /* now all pound param in expr. replaced by passed down pound value */
   
 /* although pound params never instance specific must access constants */
 /* from up module con tab */
 __push_itstk(up_itp);
 xsp = __eval_xpr(up_pndxp);
 __pop_itstk();
 __assgn_2005_nonis_param(np, up_pndxp, xsp);
 __pop_xstk();

 /* free and put back temporary "as of now" parameter values of params */
 /* in up pound expr */
 unsave_gia_expr_pndparms(up_pndxp, up_itp);
}

/*
 * free and unsave pound params in expression 
 *
 * non up pound params just ignored initial in source value was not changed
 * only needed for this expr. because if pnds worked up, evaled and unsaved
 */
static void unsave_gia_expr_pndparms(struct expr_t *xp, struct itree_t *itp)
{
 int32 pndpi;
 struct net_t *np;
 struct itree_t *up_itp;
 struct inst_t *ip;
 struct mod_t *mdp;

 if (__isleaf(xp))
  {
   if (xp->optyp == ID && xp->lu.sy->sytyp == SYM_N)
    {
     np = xp->lu.sy->el.enp; 
     if (np->n_isaparam)
      {
       if ((up_itp = itp->up_it) == NULL) return;
       ip = up_itp->itip;
       if (ip->ipxprtab == NULL) return;
       mdp = itp->itip->imsym->el.emdp;
       pndpi = ((byte *) np - (byte *) mdp->mprms)/sizeof(struct net_t);
       if (ip->ipxprtab[pndpi] == NULL) return;
 
       /* DBG remove --- */
       if (np->srep != SR_PNUM) __misc_terr(__FILE__, __LINE__);
       if (np->nu2.wp == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */

       /* need to unsave param value by copying back */
       /* this puts back intial value that is always SR_PNUM */
       memcpy(np->prm_nva.wp, np->nu2.wp, 2*WRDBYTES*wlen_(np->nwid));
      }
    }
   return;
  }
 if (xp->lu.x != NULL) unsave_gia_expr_pndparms(xp->lu.x, itp);
 if (xp->ru.x != NULL) unsave_gia_expr_pndparms(xp->ru.x, itp);
}

/*
 * ROUTINES TO SPLIT AND BUILD ARRAYS OF GATES AND INSTANCES  
 */

/*
 * rebuild mgates and miarr tables for each module with arrays of g/i
 *
 * for g/i arrays original symbol and pins store in giap
 * SJM 04-25-10 - notice this does not use copy 1gate or copy 1inst but
 *                copies for gi arr expand with special case code in here 
 * BEWARE - can not access symbol table in here until sorted and reconnected
 *          at end of gate and inst expansion
 */
static void rebld_mod_g_and_i_arrs(void)
{
 struct mod_t *mdp;
 int32 has_iarrs;

 has_iarrs = FALSE;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* if has either arrays of gates or insts must re-bld both for sym tab */
   if (!mdp->m_has_garrs && !mdp->m_has_iarrs) continue;

   __push_wrkitstk(mdp, 0);
   rebld_1mod_g_and_i_arr(mdp);
   if (mdp->m_has_iarrs) has_iarrs = TRUE;
   __pop_wrkitstk();
  }
 /* if any any arrays of instances, must recount */  
 if (has_iarrs) count_flat_insts();
 /* mod level table remains same since more instance but no more types */
}

/*
 * routine to re-build m gates and m insts tabs by expanding all arrays of
 * g/i that have not already been expanded
 *
 * SJM 05-04-10 - now for arrays of g/i in gen blks, after moving all gen
 * items into a module, if the mod has arrays of g/i in gens this is called
 */
static void rebld_1mod_g_and_i_arr(struct mod_t *mdp)
{
 int32 newgnum, newinum, new_stsiz, nbytes;

 /* count new mod gates, insts and sym tab size */
 cmp_new_mgnum_minum_and_stsiz(mdp, &(newgnum), &(newinum), &(new_stsiz));

 /* alloc new work symtab - will replace mod's sym tab st syms */
 __wrkstab = (struct sy_t **) __my_malloc(new_stsiz*sizeof(struct sy_t *));
 nbytes = mdp->msymtab->numsyms*sizeof(struct sy_t *);
 /* first copy in old syms - add new gsym and isym will add to wrk stab */
 memcpy(__wrkstab, mdp->msymtab->stsyms, nbytes);

 __last_sy = mdp->msymtab->numsyms - 1;
 /* DBG remove --- */
 if (!mdp->msymtab->freezes) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* rebuild m gate tab by expanding g arr - adds to wrk sym tab new syms */ 
 if (mdp->m_has_garrs) rebld_mgtab(mdp, newgnum);

 /* rebuild m inst tab by expanding i arr - adds to wrk sym tab new syms */ 
 if (mdp->m_has_iarrs)
  {
   rebld_mitab(mdp, newinum);
  } 

 /* must re-sort symbol table - because table of ptr el union right */
 qsort(__wrkstab, (word32) new_stsiz, sizeof(struct sy_t *), __gia_sym_cmp);
 /* SJM 07/02/05 - free the mod's symbtab stsyms to fix memory leak */
 /* symtab is ptr to syms - for non i/g array's sym record still used */
 __my_free(mdp->msymtab->stsyms, mdp->msymtab->numsyms*sizeof(struct sy_t *)); 
 mdp->msymtab->numsyms = new_stsiz;
 mdp->msymtab->stsyms = __wrkstab;

 if (__debug_flg)
  {
   __dbg_dmp_mod_gia_recs(mdp);
  }
}

/*
 * compute size of new mgnum, new ninum and and mod sy tab size
 *
 * SJM 05-04-10 - now if expanded do not count since for arrays of g/i
 * in generates need to rebld just those - rest will be marked expanded
 * -- works because unbld turns of xpnd flag
 */
static void cmp_new_mgnum_minum_and_stsiz(struct mod_t *mdp, int32 *newgnum,
 int32 *newinum, int32 *new_stsiz)
{
 int32 i, arrsynum, ngnum, ninum;
 struct gate_t *ogp;
 struct inst_t *oip;
 struct gia_aux_t *giap;

 arrsynum = 0;
 /* first count number of new - non g/i array as 1 and g/i array width */
 if (mdp->m_has_garrs)
  {
   /* compute new size of mgates table */
   for (i = 0, ngnum = 0; i < mdp->mgnum; i++) 
    {
     ogp = &(mdp->mgates[i]);
     if ((giap = ogp->g_giap) == NULL) { ngnum++; continue; }
     if (giap->gia_xpnd) { ngnum++; continue; }
     ngnum += __get_gia_wide(giap);
     /* one extra symbol for every element of array but original gate */
     /* counted as one */
     arrsynum++;
    } 
  }
 else ngnum = mdp->mgnum;
 *newgnum = ngnum;

 if (mdp->m_has_iarrs)
  {
   /* compute new size of minsts table */
   for (i = 0, ninum = 0; i < mdp->minum; i++) 
    {
     oip = &(mdp->minsts[i]);
     if ((giap = oip->i_giap) == NULL) { ninum++; continue; }
     if (giap->gia_xpnd) { ninum++; continue; }
     ninum += __get_gia_wide(giap);
     arrsynum++;
    }
  } 
 else ninum = mdp->minum;
 *newinum = ninum; 

 *new_stsiz = mdp->msymtab->numsyms + (*newgnum - mdp->mgnum)
  + (*newinum - mdp->minum) + arrsynum;
}

/*
 * routine to rebld new m gates tab and replace
 */
static void rebld_mgtab(struct mod_t *mdp, int32 newgnum)
{
 int gi, gi2, gi3, giawid, gia_dir, bi;
 struct gate_t *gptab, *ogp, *ngp;
 struct gia_aux_t *giap, tmpl_gia;

 gptab = (struct gate_t *) __my_malloc(newgnum*sizeof(struct gate_t));

 /* copy from old to new gia and gate tables */
 /* gi moves through old mgates, gi2 through new */ 
 for (gi = 0, gi2 = 0; gi < mdp->mgnum; gi++) 
  {
   ogp = &(mdp->mgates[gi]);

   if ((giap = ogp->g_giap) == NULL || giap->gia_xpnd)
    {
     /* copy body (insides) */
     ngp = &(gptab[gi2]);
     *ngp = *ogp;
     /* SJM 07/02/05 - for non arrayed insts in mod with inst arrays, */ 
     /* need to connect the sym to new gptab entry - needed because */
     /* gp tab is array of gate_t records not array of ptrs */
     ngp->gsym->el.egp = ngp;
     gi2++;
     continue;
    }

   /* fill a template giap before copying and building - start with base */
   tmpl_gia = *giap;
   /* move original gpins to template giap - all will point so same pins */
   tmpl_gia.giapins_ptr = ogp->gpins;

   /* for now all gpins lists same and >1 ptrs to it */
   tmpl_gia.gia_base_syp = ogp->gsym;
   tmpl_gia.gia_base_syp->sy_giabase = TRUE;

   /* set cross link between gate array in src base sy and new gptab gate */
   tmpl_gia.gia_base_syp->el.egp = &(gptab[gi2]);
   tmpl_gia.gia_xpnd = TRUE; 

   /* fill gptab (new m gates) tab */
   giawid = __get_gia_wide(giap);
   gia_dir = (giap->gia1 > giap->gia2) ? -1 : 1;
   bi = tmpl_gia.gia1;
   for (gi3 = gi2; gi3 < gi2 + giawid; gi3++, bi += gia_dir)
    {
     ngp = &(gptab[gi3]);
     /* for expanded first copy gate contents */
     *ngp = *ogp;
     ngp->g_du.pdels = __copy_dellst(ogp->g_du.pdels);
     /* proc to give new gate right array index symbol and cross link */
     /* add to wrk symtab */
     add_new_gsym(ngp, bi);  

     /* this allocs and fills new g giap, but does not set base union */
     __copy1_gate_gia_rec(ngp, &(tmpl_gia));
     ngp->g_giap->gia_bi = bi;
     /* if first one set base, else non base */
     if (gi3 == gi2) ngp->g_giap->gia_is_base_first = TRUE;
     else ngp->g_giap->gia_is_base_first = FALSE;
    }
   gi2 += giawid;
  }
 /* finally free old gate tables and allocate new */
 __my_free(mdp->mgates, mdp->mgnum*sizeof(struct gate_t));
 mdp->mgates = gptab;
 mdp->mgnum = newgnum;
}

/*
 * routine to rebld new m insts tab and replace
 * also need to deal with src loc tab
 */
static void rebld_mitab(struct mod_t *mdp, int32 newinum)
{
 int ii, ii2, ii3, giawid, gia_dir, bi;
 struct inst_t *iptab, *oip, *nip;
 struct gia_aux_t *giap, tmpl_gia;
 struct srcloc_t **sloctabp;

 iptab = (struct inst_t *) __my_malloc(newinum*sizeof(struct inst_t));
 sloctabp = (struct srcloc_t **)
 __my_malloc(newinum*sizeof(struct srcloc_t *));

 /* ii moves through old minsts, ii2 through new */ 
 for (ii = 0, ii2 = 0; ii < mdp->minum; ii++) 
  {
   oip = &(mdp->minsts[ii]);

   if ((giap = oip->i_giap) == NULL || giap->gia_xpnd)
    {
     /* copy body (insides) */
     nip = &(iptab[ii2]);
     *nip = *oip;
     /* SJM 07/02/05 - for non arrayed insts in mod with inst arrays, */ 
     /* need to connect the sym to new iptab entry - needed because */
     /* ip tab is array of inst_t records not array of ptrs */
     sloctabp[ii2] = mdp->iploctab[ii];
     nip->isym->el.eip = nip;
     ii2++;
     continue;
    }

   /* fill a template giap before copying and building - start with base */
   tmpl_gia = *giap;
   /* move original gpins to template giap - all will point so same pins */
   tmpl_gia.giapins_ptr = oip->ipins;

   /* for now all gpins lists same and >1 ptrs to it */
   tmpl_gia.gia_base_syp = oip->isym;
   tmpl_gia.gia_base_syp->sy_giabase = TRUE;
   /* set cross link between gate array in src base sy and new gptab gate */
   tmpl_gia.gia_base_syp->el.eip = &(iptab[ii2]);
   tmpl_gia.gia_xpnd = TRUE; 

   /* fill gptab (new m gates) tab */
   giawid = __get_gia_wide(giap);
   gia_dir = (giap->gia1 > giap->gia2) ? -1 : 1;
   bi = tmpl_gia.gia1;
   for (ii3 = ii2; ii3 < ii2 + giawid; ii3++, bi += gia_dir)
    {
     nip = &(iptab[ii3]);
     /* for expanded first copy gate contents */
     *nip = *oip;
     /* build the expanded base (first) inst of array of insts */
     nip->ipxprtab = __copy_pndxtab(oip);
     add_new_isym(nip, bi);  
     /* SJM 07-14-07 - same algorithm - all expanded point to same one */
     sloctabp[ii3] = mdp->iploctab[ii];

     /* this allocs and fills new g giap, but does not set base union */
     __copy1_inst_gia_rec(nip, &(tmpl_gia));
     nip->i_giap->gia_bi = bi;
     /* if first one set base, else non base */
     if (ii3 == ii2) nip->i_giap->gia_is_base_first = TRUE;
     else nip->i_giap->gia_is_base_first = FALSE;
    }
   ii2 += giawid;
   if (mdp->minstnum == 1 && giawid > 1) mdp->minstnum = 2;
  }
 /* finally free old insts tables and allocate new */
 __my_free(mdp->minsts, mdp->minum*sizeof(struct inst_t));
 /* SJM 07-13-07 - this is freeing ptr table not per pin sloc arrays */
 __my_free(mdp->iploctab, mdp->minum*sizeof(struct srcloc_t *));
 mdp->minsts = iptab;
 mdp->iploctab = sloctabp; 
 mdp->minum = newinum;
}

/*
 * routine to dump one mod's inst and gate
 */
static void __dbg_dmp_mod_gia_recs(struct mod_t *mdp)
{
 int32 gi, ii;
 struct gate_t *gp;
 struct inst_t *ip;

 if (!mdp->m_has_garrs)
  {
   __dbg_msg("... mod %s has no arrays of gates\n", mdp->msym->synam);
  }
 else
  {
   __dbg_msg("... mod %s has arrays of gates:\n", mdp->msym->synam);
   for (gi = 0; gi < mdp->mgnum; gi++)
    {
     gp = &(mdp->mgates[gi]);
     if (gp->g_giap == NULL) continue;
     __dbg_dmp_gia_rec(gp->g_giap, TRUE);
    }
  } 
 if (!mdp->m_has_iarrs)
  {
   __dbg_msg("... mod %s has no arrays of insts\n", mdp->msym->synam);
  }
 else
  {
   __dbg_msg("... mod %s has arrays of insts:\n", mdp->msym->synam);
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     if (ip->i_giap == NULL) continue;
     __dbg_dmp_gia_rec(ip->i_giap, FALSE);
    }
  } 
}

/*
 * routine to dump array of inst/gate aux records
 *
 * SJM 05-03-10 - 
 */
extern void __dbg_dmp_gia_rec(struct gia_aux_t *giap, int32 is_gate)
{
 char s1[RECLEN];

 if (is_gate) strcpy(s1, "gate"); else strcpy(s1, "inst");
 __dbg_msg("+++ dumping g/i array aux for %s base syp %s[%d] - [%d:%d]\n",
  s1, giap->gia_base_syp->synam, giap->gia_bi, giap->gia1, giap->gia2); 
 __dbg_msg("    first=%d, xpnd=%d, pnd-rng=%d, rng expr [%s:%s] ptr = %lx\n",
  giap->gia_is_base_first, giap->gia_xpnd, giap->gia_rng_has_pnd,
  __msgexpr_tostr(__xs, giap->giax1), __msgexpr_tostr(__xs2, giap->giax2),
  giap->giapins_ptr);
}

/*
 * ROUTINES TO CALCULATE FLATTEND INST NUMBERS
 */

/*
 * set the as if flattended instance counts for all modules
 * know flat insts initialized to 0 and m insts already counted
 * this also links every module inst. upward (parent) instance
 *
 * count here counts only 1 for each cell array - fixed up later
 */
static void count_flat_insts(void)
{
 int32 ii;
 struct mod_t *mdp;
 struct inst_t *ip;
 struct mod_t *imdp;

 /* must always reinitialize flat count because maybe called multiple times */ 
 /* i.e. after arrays of instances expanded */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  mdp->flatinum = 0;

 /* inc. count of all instances in each top level module */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* descend to count only from top level modulss */
   if (mdp->minstnum != 0) continue;
   mdp->flatinum = 1;

   /* count depth first */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     imdp->flatinum++;

     /* DBG remove --
     if (__debug_flg)
      {
       __dbg_msg(
        "+++ incing count (%d) of inst. %s type %s in top level module %s\n",
        imdp->flatinum, ip->isym->synam, imdp->msym->synam,
        mdp->msym->synam);
      }
     ---- */ 
     count2_flat_insts(imdp);
    }
  }
}

/*
 * traverse 1 down flattened inst. count
 */
static void count2_flat_insts(struct mod_t *mdp)
{
 int32 ii;
 struct inst_t *ip;
 struct mod_t *imdp;

 for (ii = 0; ii < mdp->minum; ii++)
  {
   ip = &(mdp->minsts[ii]); 
   imdp = ip->imsym->el.emdp;
   imdp->flatinum++;
   /* DBG remove ---
   if (__debug_flg)
    { 
     __dbg_msg("+++ traverse inc count (%d) inst %s type %s in mod %s\n",
      imdp->flatinum, ip->isym->synam, imdp->msym->synam, mdp->msym->synam);
    }
   --- */
   if (imdp->mlpcnt > 0) count2_flat_insts(imdp);
  }
}


/*
 * comparison routine for sorting symbol table after expand g/i added 
 */
extern int32 __gia_sym_cmp(const void *sy1, const void *sy2)
{
 return(strcmp((*((struct sy_t **) sy1))->synam,
  (*(struct sy_t **) sy2)->synam));
}

/*
 * get width of array of inst/gate
 */
extern int32 __get_gia_wide(struct gia_aux_t *giap)
{
 int32 r1, r2;

 r1 = giap->gia1;
 r2 = giap->gia2;
 /* DBG remove -- */
 if (r1 == -1 || r2 == -1) __arg_terr(__FILE__, __LINE__); 
 /* --- */
 return((r1 >= r2) ? (r1 - r2 + 1) : (r2 - r1 + 1));
}

/*
 * routine to add new (still unusuable and unsorted) symbol table
 * because stored in range order never need to normalize here
 */
static void add_new_gsym(struct gate_t *gp, int32 bi)  
{
 struct sy_t *gsyp;
 char nsynam[2*IDLEN];

 gsyp = (struct sy_t *) __my_malloc(sizeof(struct sy_t)); 
 *gsyp = *(gp->gsym);
 sprintf(nsynam, "%s[%d]", gp->gsym->synam, bi); 
 gsyp->synam = __pv_stralloc(nsynam);
 /* SJM 07-07-07 - T only for gia added, will be F for the original base */ 
 gsyp->sy_gia_added = TRUE;
 __wrkstab[++__last_sy] = gsyp;
 gp->gsym = gsyp;
 gsyp->el.egp = gp;
}

/*
 * routine to update new (still unusable and unsorted) symbol table
 * because stored in range order never need to normalize here
 */
static void add_new_isym(struct inst_t *ip, int32 bi)  
{
 struct sy_t *isyp;
 char nsynam[2*IDLEN];

 isyp = (struct sy_t *) __my_malloc(sizeof(struct sy_t)); 
 *isyp = *(ip->isym);
 sprintf(nsynam, "%s[%d]", ip->isym->synam, bi); 
 isyp->synam = __pv_stralloc(nsynam);
 /* SJM 07-07-07 - T only for gia added, will be F for the original base */ 
 isyp->sy_gia_added = TRUE;
 __wrkstab[++__last_sy] = isyp;
 ip->isym = isyp;
 isyp->el.eip = ip;
}

/*
 * routine to dump minsts for every module in the design
 */
extern void __dmp_dsgn_minst(char *hdr_s)
{
 struct mod_t *mdp;
 int32 ii;
 struct inst_t *ip;

 __dbg_msg("%s ===>\n", hdr_s);
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __dbg_msg("+++ dumping instances in module %s:\n", mdp->msym->synam);
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     __dmp_1minst(ip);
    }
  }
}

/*
 * dmp one minst element 
 */
extern void __dmp_1minst(struct inst_t *ip)
{
 char s1[RECLEN];

 if (ip->ipxprtab != NULL)
  {
   sprintf(s1, "ipxprtab[0]=%s", __msgexpr_tostr(__xs, ip->ipxprtab[0]));
  }
 else strcpy(s1, "[no ipxprtab]");
 __dbg_msg("     inst %s type %s %s\n", ip->isym->synam, ip->imsym->synam,
  s1);
 if (ip->isym->el.eip != ip)
  {
   __dbg_msg("inst %s type %s - other inst %s type %s\n",
     ip->isym->el.eip->isym->synam, ip->isym->el.eip->imsym->synam, 
     ip->isym->synam, ip->imsym->synam); 
   __misc_terr(__FILE__, __LINE__);
  }
}

/*
 * debug routine to dump entire mod header list
 */
extern void __dmp_modhdr_list(struct mod_t *mhdrp, char *label)
{
 struct mod_t *mdp;

 /* SJM 02-26-09 - was always dumping wrong mod hdr glb */
 __dbg_msg("\n+++ %s modhdr list:\n", label);
 for (mdp = mhdrp; mdp != NULL; mdp = mdp->mnxt)
  {
   __dbg_msg("\n+++ module %s minstnum=%d flatinum=%d\n", mdp->msym->synam,
    mdp->minstnum, mdp->flatinum);
   __dmp_mod(stdout, mdp, FALSE);
  }
 __dbg_msg("+++ END +++\n");
}

/*
 * ROUTINES TO CHECK DEFPARAMS
 */

/*
 * check defparam format parameter statements 
 *
 * must be done before pound splitting because pound splitting copy
 * of defparam grefs must copy glb ref components
 *
 * if error, undef symbol - must ignore undef. symbols later
 * SJM 04-08-10 - this is routine for normal dfps only not dfps in gen blks
 */
static void chk_defparams(void)
{
 struct dfparam_t *dfpp, *dfpp2, *last_dfpp;
 struct mod_t *mdp;

 /* must do as first step in converting to rooted */
 __num_dfps = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   for (last_dfpp = NULL, dfpp = __inst_mod->mdfps; dfpp != NULL;)
    {
     dfpp2 = dfpp->dfpnxt;

     __sfnam_ind = dfpp->dfpfnam_ind;
     __slin_cnt = dfpp->dfplin_cnt;

     if (!chk1_defparam(dfpp))
      {
       /* if error, remove from list */
       if (last_dfpp == NULL) __inst_mod->mdfps = dfpp2;
       else last_dfpp->dfpnxt = dfpp2;
       /* on error free the defparam - compeletly removed from circuit */
       __free_1dfparam(dfpp);
      }
     else { last_dfpp = dfpp; __num_dfps++; }
     dfpp = dfpp2;
    }
   __pop_wrkitstk();
  }

 /* final step is freeing all defparams in gref table, no longer needed */
 free_gone_glbs();
}

/*
 * check one defparam - if error return F - caller links out of mod's list
 *
 * SJM 09-03-11 - for gen, after defparam moved into src, will check next
 * here next time through
 */
static int32 chk1_defparam(struct dfparam_t *dfpp)
{
 /* first check and set widths here since can contain parameters defined */ 
 /* later in source according to LRM */
 if (!__chk_paramexpr(dfpp->dfpxrhs, 0))
  {
   __sgferr(1035,
    "defparam %s right hand side error - parameters and constants only",
    __msgexpr_tostr(__xs, dfpp->dfpxlhs));
    __free2_xtree(dfpp->dfpxrhs);
    __set_numval(dfpp->dfpxrhs, ALL1W, ALL1W, WBITS);
  }
 /* check and set value during src read since only previously defined */
 /* params on rhs and must use initial values */

 /* SJM 01/27/04 - old code was wrongly evaling defparam rhs to number */
 /* must be left as expr since dfps may need changed dependend param */
 if (!lhs_chk1dfparam(dfpp)) return(FALSE);

 if (dfpp->dfp_local) return(TRUE);
 
 /* DBG remove -- */
 if (dfpp->dfpxlhs->optyp != GLBREF) __misc_terr(__FILE__, __LINE__);
 /* -- */
//SJM 04-23-10 - what is missing here?

 return(TRUE);
}

/*
 * check parameter lhs expression and return
 * resolution of defparam lhs global in here
 *
 * array of instance selects illegal in defparams  
 * SJM 04-09-10 - this is only for normal defparams not those in gen blks
 */
static int32 lhs_chk1dfparam(struct dfparam_t *dfpp)
{
 struct gref_t *grp;
 struct expr_t *lhsndp;
 struct sy_t *syp;
 struct net_t *np;

 lhsndp = dfpp->dfpxlhs;
 grp = NULL;
 if (lhsndp->optyp == GLBREF)
  { 
   grp = lhsndp->ru.grp;
   /* DBG remove -- */
   if (grp != dfpp->dfp_grp) __misc_terr(__FILE__, __LINE__);
   if (strcmp(grp->gin_mdp->msym->synam, dfpp->dfp_in_mdp->msym->synam) != 0)
    __misc_terr(__FILE__, __LINE__);
   /* -- */
   grp->gr_defparam = TRUE;

   /* SJM 03-26-10 - for defparam's moved into mod dfp list, need to fix */
   /* gref's back ptr to dfp lhsx because it moved during copy from */
   /* expand */
   if (grp->gxndp != lhsndp) 
    {
     if (dfpp->dfp_in_gen)
      {
       grp->gxndp = lhsndp;
      }
     /* DBG remove -- */
     else __misc_terr(__FILE__, __LINE__);
     /* --- */ 
    }

   /* 04-05-10 - now only called for dfp's at resolve pt. for the 2 types */
   if (!do_dfp_resolve(grp)) return(FALSE);

   if (lhsndp->optyp == ID) goto is_local;
   __num_glbdfps++;
   /* if error in resolving global cannot check here - syp not set */
   if (grp->gr_err) return(FALSE);
   /* upward relative defparams illegal to match Cadence */
   /* SJM 04-10-10 - notice rooted defparams are legal */
   if (grp->upwards_rel)
    {
     __sgferr(760,
      "upward relative defparam lvalue %s illegal - must be rooted or downward relative",
      grp->gnam);
     grp->upwards_rel = FALSE;      
     grp->gr_err = TRUE;
     return(FALSE);
    }
   /* DBG remove -- */
   if (grp->gr_xmptab == NULL || grp->gr_num_xmps <= 0)
    __misc_terr(__FILE__, __LINE__);
   /* -- */
   if (xmp_contains_genblk(grp->gr_xmptab, grp->gr_num_xmps))
    {
     __sgferr(3615,
      "defparam lvalue %s with generate block in path can not be defined outside of any generate block",
      grp->gnam);
     grp->gr_err = TRUE;
     return(FALSE);
    }

   syp = lhsndp->lu.sy;
   np = syp->el.enp;
   if (syp->sytyp != SYM_N || !np->n_isaparam)
    {
     __sgferr(755, "defparam hierarchical name lvalue %s is not a parameter",
      grp->gnam);
     grp->gr_err = TRUE;
     return(FALSE);
    }
  
   /* AIV 09/27/06 - lhs of a defparam cannot be a localparam */
   if (np->nu.ct->p_locparam)
    {
     __sgferr(3430, "defparam hierarchical name lvalue %s cannot be a localparam",
      grp->gnam);
     grp->gr_err = TRUE;
     return(FALSE);
    }

   /* for any array of inst selects in defparams are illegal */ 
   if (gref_has_giarr_ndxes(grp))
    {
     __sgferr(691, 
      "defparam lvalue %s instance array select illegal - use pound param",
      grp->gnam);
     grp->gr_err = TRUE;
     return(FALSE);
    }

   /* now have defparam global lhs path - so done with global move to defp */
   /* move guts of gref to defparam nil fields and mark global as gone */
   set_1defparam_iis(dfpp, grp);
   dfpp->gdfpnam = __pv_stralloc(grp->gnam);
   /* SJM 08-28-11 - must be able to exec again for gen */
   // grp->gnam = NULL;

   grp->last_gri = -1;
   dfpp->targsyp = grp->targsyp;
   dfpp->dfptskp = grp->targtskp;
   grp->targsyp = NULL;

   /* SJM 08-30-11 - now removing gref at top of fixup nl which is way */
   /* gen implemented by multiple elaboration until relaxation */
   /* gref need to be removed in fixup nl because next gen fixup loop */
   /* may select other defps */

   return(TRUE); 
  }

is_local:
 /* this is local - if in module gref - converted to simple by here */
 syp = lhsndp->lu.sy;
 np = syp->el.enp;
 if (syp->sytyp != SYM_N || !np->n_isaparam)
  {
   __sgferr(756, "defparam local lvalue variable %s not a parameter",
    syp->synam);
   if (grp != NULL) grp->gr_err = TRUE;
   return(FALSE);
  }
 /* AIV 09/27/06 - lhs of a defparam cannot be a localparam */
 if (np->nu.ct->p_locparam)
  {
   __sgferr(3430, "defparam local lvalue variable %s cannot be a localparam",
    syp->synam);
   if (grp != NULL) grp->gr_err = TRUE;
   return(FALSE);
  }
 dfpp->dfp_local = TRUE;
 dfpp->gdfpnam = __pv_stralloc(syp->synam);
 dfpp->dfp_in_mdp = __inst_mod;
 dfpp->targsyp = syp;
 __num_locdfps++;
 return(TRUE);
}

/*
 * return T if resolved global name has instance array index component
 */
static int32 gref_has_giarr_ndxes(struct gref_t *grp)
{
 int32 gri;

 for (gri = 0; gri <= grp->last_gri; gri++) 
  {
   if (grp->grxcmps[gri] != NULL) return(TRUE);
  }
 return(FALSE);
}

/*
 * return T if gref a gen blk component
 *
 * path can't end in genblk but may end in non net
 */
static int32 xmp_contains_genblk(struct xmrcmp_t **xmrcmptab, int32 nxcmps)
{
 int32 xmri;
 struct xmrcmp_t *xmp;

 for (xmri = 0; xmri < nxcmps; xmri++)
  {
   xmp = xmrcmptab[xmri];
   if (xmp->xmp_in_gblkp != NULL)
    {
     /* DBG remove -- */
     if (xmp->xmp_petyp != XMP_GBLK && xmp->xmp_petyp != XMP_INST_INGEN
      && xmp->xmp_petyp != XMP_NET_INGEN) __misc_terr(__FILE__, __LINE__);
     /* --- */
     return(TRUE);
    }
  }
 return(FALSE);
}

/*
 * set defparam itree ii paths 
 *
 * needed now because copying changes instance symbols
 * later will convert downward relative dfpiis to rooted and 1 design list
 */
static void set_1defparam_iis(struct dfparam_t *dfpp,
 struct gref_t *grp)
{
 int32 gi, ii;
 byte *bp1, *bp2;
 struct sy_t *syp;
 struct inst_t *ip;
 struct mod_t *up_mdp;

 dfpp->last_dfpi = grp->last_gri;
 dfpp->dfpiis = (int32 *) __my_malloc((dfpp->last_dfpi + 1)*sizeof(int32));
 dfpp->dfp_rooted = (grp->is_rooted) ? TRUE : FALSE;
 if (dfpp->dfp_rooted)
  {
   /* defparam path root wrong */
   syp = grp->grcmps[0];
   if ((ii = __ip_indsrch(syp->synam)) == -1) __misc_terr(__FILE__, __LINE__);
   dfpp->dfpiis[0] = ii;
   gi = 1;
   up_mdp = __top_itab[ii]->imsym->el.emdp;
  }
 else { gi = 0; up_mdp = __inst_mod; }  

 for (; gi <= grp->last_gri; gi++)
  {
   /* grcmps components parallel here */
   syp = grp->grcmps[gi];
   ip = syp->el.eip;
   /* making use of c pointer subtraction correction object size here */
   /* changing to byte ptr because not sure of c ptr size object rules */
   bp1 = (byte *) ip;
   bp2 = (byte *) up_mdp->minsts;
   ii = (bp1 - bp2)/sizeof(struct inst_t);
//   if (ii > 10) __misc_terr(__FILE__, __LINE__);
//REMOVEME

// SJM 03-24-10 - should not get here for defparams in gen blks
//AIV - think this should be 0 for b.v - addrs off - REMOVEME
//   if (ii != 0) __misc_terr(__FILE__, __LINE__);
// ----

   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg(
      "^^ defparam %s component %s index %d instance %s type %s in module %s\n",
      grp->gnam, syp->synam, ii, ip->isym->synam, ip->imsym->synam,
      up_mdp->msym->synam);
    }
   --- */
   dfpp->dfpiis[gi] = ii;
   up_mdp = syp->el.eip->imsym->el.emdp;
  }
 /* DBG remove --
 if (__debug_flg) dbg_dmp_dfpiis(dfpp, "in set dfparam iis");
 --- */
}

/*
 * ROUTINES TO FILL HEAD AND REST FOR DEFPARAMS
 */

/*
 * routine to implement old gref resolve code - blds xmr cmps and then uses
 * to set gref fields exactly as in old algorithm for dfps only
 *
 * SJM 04-03-11 - BEWARE - now only usable for gen/fixup time defps
 *
 * SJM 04-08-10 - now leaving the xmr cmp tab for later use
 * SJM 04-03-11 - this proc now only used for defparms 
 */
static int32 do_dfp_resolve(struct gref_t *grp)
{
 /* DBG remove -- */
 if (!grp->gr_defparam) __misc_terr(__FILE__, __LINE__);
 /* --- */ 
 if (!bld_dfp_xmrcmps(grp)) return(FALSE);

 if (!grp->gr_err)
  {
   if (cvrt_local_dfp_back_to_xpr(grp)) return(TRUE);
  }
 if (!grp->gr_err && !grp->gr_gone)
  {
   /* SJM 04-03-11 - this is common routine for dfps and grefs to just */
   /* map the built xmr cmp tab to the gref d.s. */
   fill_gref_from_xmrcmps(grp);
  }

 /* DBG remove --
 if (__debug_flg)
  {
   dbg_dmp_xmrcmptab(grp, grp->gr_xmptab, grp->gr_num_xmps);
  }
 --- */
 if (grp->gr_err) return(FALSE);
 return(TRUE);
}

/*
 * build the global path name component symbol list (xmp tab) for 1 global
 *
 * SJM 03/14/10 
 * this requires that inst mod be set usually by push wrk itstk routine
 * it just decomposes xmr into path components so does not need itree context
 */
static int32 bld_dfp_xmrcmps(struct gref_t *grp)
{
 int32 nxcmps, xmri;
 struct xmrcmp_t **xmrcmptab;

 /* DBG remove -- */
 if (!grp->gr_defparam) __misc_terr(__FILE__, __LINE__);
 /* --- */

 __sfnam_ind = grp->grfnam_ind;
 __slin_cnt = grp->grflin_cnt;

 /* some consistency checking */
 /* DBG remove --- */
 if (grp->gxndp->optyp != GLBREF) __arg_terr(__FILE__, __LINE__);
 if (grp->glbref->optyp != GLBPTH) __arg_terr(__FILE__, __LINE__);
 if (grp->glbref->ru.x == NULL || grp->glbref->ru.x->optyp != XMRCOM)
  __arg_terr(__FILE__, __LINE__);
 /* --- */

 /* SJM 02-26-10 -  d.s is table of ptr to malloc xmrcmp records so can */
 /* modify and re-arrange later - not sure if needed */
 nxcmps = cnt_xmr_cmp_num(grp);
 xmrcmptab = (struct xmrcmp_t **)
  __my_malloc(nxcmps*sizeof(struct xmrcmp_t *));
 for (xmri = 0; xmri < nxcmps; xmri++)
  {
   xmrcmptab[xmri] = (struct xmrcmp_t *) __my_malloc(sizeof(struct xmrcmp_t));
   /* think do not really need to init here */
   init_xmrcmp(xmrcmptab[xmri]);
  }
 grp->gr_xmptab = xmrcmptab;
 grp->gr_num_xmps = nxcmps;

 /* SJM 09/15/00 - because of inst tree dependent upward rel forms */
 /* reauired by LRM must use old routine for defparams to fill head */

 /* fill the defparam lhs head - notice after first component found */
 /* and filled rest is same as normal XMR */
 /* different needed because itree needed for full XMR processing */
 if (!bld_dfp_hd_xmrcmp(xmrcmptab[0], grp))
  {
   grp->gr_err = TRUE;
   return(FALSE);
  }
 /* if only one component done */
 if (grp->glbref->ru.x->ru.x == NULL) return(TRUE);

 /* this is a normal xmr - fill rest of xmr path */
 /* this removes the intra-module path (except last) from glb sy cmps */
 /* SJM 03-28-10 - gcmp ndp 4 arg must be 2nd comp (not hd) */
 if (!bld_rest_dfpcmps(xmrcmptab, nxcmps, grp, grp->glbref->ru.x->ru.x))
  {
   grp->gr_err = TRUE;
   return(FALSE);
  }
 return(TRUE);
}

/*
 * fill defparam xmr cmp head (first element) 
 * this forces symbol location of all remaining xmr cmps
 *
 * only legal possibilites are 1) instance in current module 2) top level
 * module, and 3) upward module type reference (this is error caught by
 * caller)
 *
 * return F on error else T - error message emitted here
 * this routine is only slight different (few cases) from fill xmr hd
 *
 * SJM 02-22-10 - notice first component for defparams can only be inst
 * the various down task and up task forms are not legal here
 *
 * SJM 03-12-10 FIXME? - what about defparam that is local such as 
 * defparam var = c + d; - is this legal still
 *
 * SJM 04-03-11 - now using separate code for defp filling xmr filling
 */
static int32 bld_dfp_hd_xmrcmp(struct xmrcmp_t *xmp, struct gref_t *grp)
{
 struct sy_t *syphd, *modsyp;
 struct symtab_t *sytp;
 struct expr_t *dfphd_ndp, *sel_ndp, *ndp;
 struct genblk_t *in_gblkp;
 char *ncmp;

 dfphd_ndp = grp->glbref->ru.x;
 sel_ndp = NULL;
 if (dfphd_ndp->lu.x->optyp == XMRID) ndp = dfphd_ndp->lu.x;
 else if (dfphd_ndp->lu.x->optyp == LSB)
   { ndp = dfphd_ndp->lu.x->lu.x; sel_ndp = dfphd_ndp->lu.x->ru.x; }
 else { __case_terr(__FILE__, __LINE__); return(FALSE); }

 ncmp = ndp->ru.qnchp;
 /* if can possibly be rooted from top module or above module, save symbol */
 modsyp = __get_sym(ncmp, __modsyms);

 if (grp->gr_gblk_in != NULL)
  {
   in_gblkp = grp->gr_gblk_in;
   sytp = in_gblkp->gblk_sytab;
  }
 else
  {
   in_gblkp = NULL;

   /* DBG remove --- */
   if (grp->grsytp->sypofsyt->sytyp != SYM_M) __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* 1st priority is instance (must exist) in mod where glb ref. appeared */
   /* but maybe accessed from contained task or named block scope */
   /* try mod defparam reference in first then work up ward toward root */
   /* this works up through mod sym tables */ 
   for (sytp = grp->grsytp; sytp != NULL; sytp = sytp->sytpar)
    { if (sytp->sypofsyt->sytyp == SYM_M) goto got_inst; } 
   __misc_terr(__FILE__, __LINE__);
  }
  
 /* look up in inst. symbol table only */
got_inst:
 if ((syphd = __zget_sym(ncmp, sytp->stsyms, sytp->numsyms)) != NULL)
  {
   /* SJM 03-15-10 - if mod inst, illegal if in gen blk, but error later */
   if (syphd->sytyp != SYM_I && syphd->sytyp != SYM_LGB)
    {
#ifndef __CVC_RT__
     __sgfwarn(533,
      "defparam left hand side %s head %s %s in %s not instance - assuming rooted",
      grp->gnam, __to_sytyp(__xs, syphd->sytyp), ncmp, sytp->sypofsyt->synam);
#endif
     syphd = NULL;
     goto try_mod1st;
    }
   /* emit warning if also could be rooted but use inst. */
   /* case 1: dfparam is downward relative starting with inst */
   if (modsyp != NULL)
    {
#ifndef __CVC_RT__
    __sgfwarn(534,
      "defparam left hand side %s head %s both upward module and downward instance - instance used",
      grp->gnam, ncmp);
#endif
    }
   /* have defparam head inst, fill xmr cmp element */
   init_xmrcmp(xmp);
   xmp->xmp_cmpnam = __pv_stralloc(ncmp);
   xmp->gcmp_ndp = dfphd_ndp;
   xmp->xmp_sel_ndp = sel_ndp;
   /* SJM 03-09-10 - must set dfp's path sel if any xmr cmp has isel */
   if (xmp->xmp_sel_ndp != NULL) grp->path_has_isel = TRUE;
   xmp->xmp_syp = syphd;
   xmp->xmp_in_sytab = sytp;

   /* PRIORTY 1: downward rel inst */
   if (syphd->sytyp == SYM_I)
    {
     /* case 1: no nested gen blks to traverse */
     if (in_gblkp != NULL)
      {
       xmp->xmp_petyp = XMP_INST_INGEN;
       xmp->xmp_in_gblkp = in_gblkp;
      }
     else xmp->xmp_petyp = XMP_INST;

     /* next looking in downward inst sym tab - no effect if in a gen blk */
     xmp->xmp_nxtcmp_sytab = syphd->el.eip->imsym->el.emdp->msymtab;
    }
   else
    { 
     /* case 2: head is a genblk name - will descend until find real object */
     xmp->xmp_petyp = XMP_GBLK;
     grp->gr_has_genitem = TRUE;
//AIV 03-15-10 FIXME? - genblk egblkp not connected right?
     xmp->xmp_nxtcmp_sytab = syphd->el.egblkp->gblk_sytab;
     xmp->xmp_in_gblkp = in_gblkp;
    }

   return(TRUE);
  }

 /* did not find instance name - see if matches module name */
try_mod1st:
 if (modsyp == NULL)
  {
   __sgferr(757,
    "rooted or upward relative defparam left hand side %s first component %s illegal or undeclared",
    grp->gnam, ncmp);
   return(FALSE);
  }
 /* SJM 03-12-10 - according to LRM only rooted inst and downward rel inst */
 /* allowed as first component of defparam */

 /* since upward module not instance, error if select */
 if (sel_ndp != NULL) 
  {
   __sgferr(692,
    "rooted or upward relative path %s head %s not instance array - select illegal",
    grp->gnam, ncmp);
   xmp->xmp_err = TRUE;
   grp->gr_err = TRUE;
   return(FALSE);
  }

 /* SJM 03-12-10 - normally modsyp will be top mod but can be any mod name */
 /* can't be upward inst since when defparam elaborated inst tree not known */
 /* checking for illegal cases later - LOOKATME? - what are they? */
 init_xmrcmp(xmp);
 xmp->xmp_petyp = XMP_MOD; 

 /* notice cannot check if upward really above in itree until prep. time */
 if (modsyp->el.emdp->minstnum != 0) xmp->xmp_upwards_rel = TRUE; 
 else xmp->xmp_is_rooted = TRUE;

 xmp->xmp_cmpnam = __pv_stralloc(ncmp);
 xmp->xmp_syp = modsyp;
 xmp->gcmp_ndp = dfphd_ndp;
 xmp->xmp_sel_ndp = sel_ndp;

 /* SJM 03-09-10 - must set gref's path sel if any xmr (dfp) cmp has isel */
 if (xmp->xmp_sel_ndp != NULL) grp->path_has_isel = TRUE;

 xmp->xmp_in_sytab = __modsyms;
 /* SJM 03-01-10 - think for mod, nxt el symtab to look in is mod's sym tab */
 xmp->xmp_nxtcmp_sytab = modsyp->el.emdp->msymtab;

 /* notice mod name defparam cmp hd, can never be in a gen gblk */

 return(TRUE);
}

/*
 * resolve a local name that is a qualified path name by converting
 * back to normal var 
 * if really local path, converted back to simple expr and checked as id later
 *
 * here caller handled instance arrays - know in module scope symbols
 * are never arrayed (error emitted if select appears)
 * SJM 03-10-10 - FIXME???? - this is not true for genblks 
 *
 * SJM 04-03-11 - need separate routine for defparam convert back to
 * local defparam - difference is defparam names do not have final
 * gen blk prefixes yet and very limited downward path rules
 */
static int32 cvrt_local_dfp_back_to_xpr(struct gref_t *grp)
{
 struct xmrcmp_t *xmp;
 struct sy_t *syphd, *syptail;
 struct expr_t *ghd_ndp, *locndp;

 /* DBG remove -- */
 if (grp->gr_xmptab == NULL || grp->gr_num_xmps <= 0)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 xmp = grp->gr_xmptab[0];

 ghd_ndp = grp->glbref->ru.x;
 /* DBG remove -- */
 if (ghd_ndp != xmp->gcmp_ndp) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* CASE 1: handle xmr's that were guessed to be xmrs but are really either */
 /* errors or guessed wrong and just simple wires - if this is place wire */
 /* cannot go, error will be caught in item (such as task enable) checking */
 /* simple nets in dumpvars argument lists will be seen as XMRs - fixed here */
 syphd = xmp->xmp_syp;
 if (syphd->sytyp == SYM_N)
  {
   /* if this is hierarchical global whose head is wire - error */
   /* i.e. if only 1 component ok */
   if (grp->gr_num_xmps > 1 || !grp->gr_inst_ok)
    {
     __sgferr(754, "hierarchical reference %s first component %s %s illegal",
      grp->gnam, __to_wtnam(__xs, syphd->el.enp), syphd->synam);
     grp->gr_err = TRUE;
     return(TRUE);
    }
   /* must be wire not parameter here at end - param use xmr's illegal */
   if (!chk_xmr_tail_wire(grp, syphd, TRUE))
    { grp->gr_err = TRUE; return(TRUE); }

local_1cmp:
   /* if this is xmr that is 1 component - change back to simple wire */
   /* LOOKATME - why is this needed since removing glb */
   if (syphd->sytyp == SYM_TSK || syphd->sytyp == SYM_F ||
    syphd->sytyp == SYM_LB) grp->targtskp = syphd->el.etskp;
   /* this can be local task call too - not just wire */
   /* AIV 01/20/11 - cannot remove if uprel */
   if (xmp->xmp_upwards_rel)
    {
     return(FALSE);
    }
   grp->gr_gone = TRUE;
   if (ghd_ndp->lu.x->optyp == XMRID)
    {
     /* first free the XMRCOM grp expr. part */  
     locndp = grp->gxndp;
     __free2_xtree(locndp);
     locndp->optyp = ID;
     locndp->ru.grp = NULL;
     locndp->lu.sy = syphd;
    }
   else 
    {
     /* here gxndp is GLB REF with ru ptr to XMR COM (list) */     
     /* here rearranging so can not free */
     /* SJM 03-10-10 - for multi-dim expr's always have first index so */
     /* works because still have next_ndx expr */
     locndp = grp->gxndp;
     locndp->optyp = LSB;
     locndp->ru.grp = NULL;
     locndp->lu.x = ghd_ndp->lu.x->lu.x;
     locndp->lu.x->optyp = ID;
     locndp->lu.x->lu.sy = syphd;
     locndp->ru.x = ghd_ndp->lu.x->ru.x; 
    }
   /* global is now removed and do not need to save name since only one comp */
   return(TRUE);
  }
 /* know only way for this to happen is gr loc is scope object */  
 /* if this is 1 component task enable or function call will never be */
 /* seen as global in source reading */
 /* handle in normal global code since it cannot be local */

 /* not a wire - handle case of 1 component scope object */
 /* this is global caused by appearing in scope legal place */
 if (grp->gr_num_xmps == 1) 
  {
   /* can be task/func/named block in which case convert back to local */
   /* also can be udp or gate primitive */
   /* and no need to check for possibility of wrong param will check in */
   /* sys task enable code */
   if (syphd->sytyp == SYM_TSK || syphd->sytyp == SYM_F ||
    syphd->sytyp == SYM_LB)
    {
     /* any scope array that is not array of insts is illegal */
     if (ghd_ndp->lu.x->optyp == LSB)
      {
local_sel_err:
       __sgferr(690, "hierarchical reference %s illegal - array of %s illegal",
        grp->gnam, __to_sytyp(__xs, syphd->sytyp));
       grp->gr_err = TRUE;
       return(TRUE);
      }
     goto local_1cmp; 
    }

   /* normal 1 component inst. or top mod. global - handled elsewhere */
   return(FALSE);
  }
 /* if in module symbol head instance, then not local */
 if (syphd->sytyp != SYM_TSK && syphd->sytyp != SYM_F &&
  syphd->sytyp != SYM_LB) return(FALSE); 

 /* know this local name expressed with qualified path */
 /* 1st check head to see if also a module name */
 if (__get_sym(xmp->xmp_cmpnam, __modsyms) != NULL)
  {
#ifndef __CVC_RT__
   __sgfwarn(532,
    "local hierarchical name %s path head is also module name - local used",  
    grp->gnam);
#endif
  }
 /* NULL means undecl - error but getting here still means local */
 /* checks for parameter at end of path in here */
 /* getting here means first symbol is is declared in module */  
 /* SJM 03-14-10 - notice since ghd ndp is head must start with in mod */
 /* not next down sym tab */
 /* SJM 03-14-10 - if error this routine emits the message */
 if ((syptail = find_dfp_inmod_sym(grp, ghd_ndp, syphd, xmp->xmp_in_sytab))
  == NULL)
  {
   grp->gr_err = TRUE;
   return(TRUE);
  }
 /* after end of instances, local scope object can not be array ref. */
 if (ghd_ndp->lu.x->optyp == LSB) goto local_sel_err;

 /* know task/func/mod */
 /* notice ...lb.lb as scope is ok - just like local - and >2 elements */
 if (syphd->sytyp == SYM_LB && grp->gr_num_xmps > 2)
  {
   __sgfinform(401, 
    "local hierarchical path %s first component is named block", grp->gnam);
  }
 /* finally convert to ID but save name for printing */
 grp->gr_gone = TRUE;
 /* SJM 03-14-10 - task is tail not head */ 
 grp->targtskp = syptail->el.etskp;

 locndp = grp->gxndp;
 __free2_xtree(locndp);
 /* must set non xmr node tail */
 locndp->lu.sy = syptail;
 locndp->optyp = ID;
 /* re-allocate this so can eventually if needed free global */
 /* notice must not free gnam field in case free globals (shouldn't) */  
 /* FIXME - should for inst. array references need to convert to numbers */
 locndp->ru.qnchp = grp->gnam;
 grp->gnam = NULL;
 locndp->locqualnam = TRUE;
 /* global is now removed */
 return(TRUE);
}

/*
 * fill xmrcmp tab for rest of path after head set
 *
 * fills xmrcmptab (assumes allocated to right size already) if no error
 * know head - index 0 of xmrcmptab set to head of XMR
 *
 * head filling routines differ but this proc used to fill the rest of
 * the path xmrcmps for both XMRs and defparams
 *
 * SJM 04-03-11 - this is old routine now only for defparams
 */
static int32 bld_rest_dfpcmps(struct xmrcmp_t **xmrcmptab, int32 xmrtsiz,
 struct gref_t *grp, struct expr_t *gcmp_ndp)
{
 int32 xmri;
 struct xmrcmp_t *xmp, *last_xmp;
 struct sy_t *syp;
 struct symtab_t *sytp;
 struct expr_t *ndp, *sel_ndp;
 struct genblk_t *in_gblkp;
 char *ncmp;

 for (xmri = 1;; xmri++)
  {
   sel_ndp = NULL;
   if (gcmp_ndp->lu.x->optyp == XMRID) ndp = gcmp_ndp->lu.x;
   else if (gcmp_ndp->lu.x->optyp == LSB)
    { ndp = gcmp_ndp->lu.x->lu.x; sel_ndp = gcmp_ndp->lu.x->ru.x; }
   /* SJM 02/02/05 - part select legal but same as ID here */
   else if (gcmp_ndp->lu.x->optyp == PARTSEL 
    || gcmp_ndp->lu.x->optyp == PARTSEL_NDX_PLUS
    || gcmp_ndp->lu.x->optyp == PARTSEL_NDX_PLUS) 
    {
     ndp = gcmp_ndp->lu.x->lu.x;
    }
   else { __case_terr(__FILE__, __LINE__); return(FALSE); }

   last_xmp = xmrcmptab[xmri - 1]; 

   /* for each pass thru loop, see in gblkp if inside a gblk */
   if (last_xmp->xmp_petyp == XMP_GBLK) in_gblkp = last_xmp->xmp_in_gblkp;
   else in_gblkp = NULL;

   /* SJM 03-01-10 - need to look in symbol tab of the previous xmr cmp */
   /* object - not the sym tab prev in but its sym tab */
   /* DBG remove --- */
   if (last_xmp->xmp_nxtcmp_sytab == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */

   sytp = last_xmp->xmp_nxtcmp_sytab;

   xmp = xmrcmptab[xmri];
   init_xmrcmp(xmp);
   ncmp = ndp->ru.qnchp;

   /* SJM 02-22-10 - key here is that once head is found, must find every */
   /* component in each downward scope (include gen blk) sym tab */
   if ((syp = __zget_sym(ncmp, sytp->stsyms, sytp->numsyms)) == NULL)
    {
     __sgferr(758, "hierarchical path %s component %s undeclared in %s",
      grp->gnam, ncmp, sytp->sypofsyt->synam);
     xmp->xmp_err = TRUE;
     grp->gr_err = TRUE;
     return(FALSE);
    }

   /* counted so one xmr cmp for each part of XMR although in gr cmps */
   /* may have disappeared */
   if (xmri + 1 >= MAXGLBCOMPS - 1 || xmri + 1 > xmrtsiz)
    {
     __pv_terr(310, "hierarchical path %s has too many components (%d)",
      grp->gnam, MAXGLBCOMPS);
    }
   xmp->xmp_cmpnam = __pv_stralloc(ncmp);
   xmp->xmp_syp = syp;
   xmp->gcmp_ndp = gcmp_ndp;
   /* code below determines if array of scope legal */
   xmp->xmp_sel_ndp = sel_ndp;

   /* SJM 03-09-10 - must set gref's path sel if any xmr or dfp cmp has isel */
   if (xmp->xmp_sel_ndp != NULL) grp->path_has_isel = TRUE;

   /* virtual case 0: descending through gen blks */
   /* SJM 03-15-10 - if found a genblk in symtab search, add virtual xmp, */
   /* update ptrs and keep looping - this xmr cmp will be removed later */
   if (syp->sytyp == SYM_LGB)
    {
     /* DBG remove -- */
     if (in_gblkp == NULL) __misc_terr(__FILE__, __LINE__); 
     /* --- */
     /* SJM 03-01-10 - in sym tab is this gen blk */
     xmp->xmp_in_sytab = sytp;
  
     /* SJM 03-01-10 - when moving downward and find inst, sytp is the next */
     /* down symtab to look in */
     xmp->xmp_nxtcmp_sytab = in_gblkp->gblk_sytab;
     xmp->xmp_in_gblkp = in_gblkp;

     /* next down gen blk */
     sytp = in_gblkp->gblk_sytab;
//SJM 03-15-10 - FIXME? need checking here */
     // if (gcmp_ndp->ru.x == NULL) - need error if wrongly end of path
     continue;
    }

//SJM 03-15-10 - FIXME? not setting in_gblkp right here?
   /* case 1: in downward relative inst - can end path */
   if (syp->sytyp == SYM_I)
    {
     if (last_xmp->xmp_in_gblkp != NULL) xmp->xmp_petyp = XMP_INST_INGEN;
     else xmp->xmp_petyp = XMP_INST;

//SJM 02-22-10 - FIXME??? - think this sym tab not glb blk as of now
     sytp = syp->el.eip->imsym->el.emdp->msymtab;

     /* SJM 03-01-10 - in sym tab is nxt symtab for previous */   
     xmp->xmp_in_sytab = last_xmp->xmp_nxtcmp_sytab;

     /* SJM 03-01-10 - when moving downward and find inst, sytp is the next */
     /* down symtab to look in */
     xmp->xmp_nxtcmp_sytab = sytp;
     /* SJM 03-09-10 - for rooted, this 2nd xmr component's next symbol */
     /* tab to look in will be a top module with no parent, i.e. hd found */
     /* in mod syms for rooted, next component looked at in the top lev mod */
     /* DBG remove -- */
     if (sytp->sytpar != NULL && sytp->sytpar->sypofsyt->sytyp != SYM_M)
      __misc_terr(__FILE__, __LINE__);
     /* ---*/
     if ((gcmp_ndp = gcmp_ndp->ru.x) == NULL)
      {
       /* DBG remove -- */
       if (xmri != xmrtsiz - 1) __misc_terr(__FILE__, __LINE__);
       /* DBG remove -- */
       return(TRUE);
      }      
     continue;
    }
   /* case 2: in downward relative net - must end path */
   if (syp->sytyp == SYM_N)
    {
     if (gcmp_ndp->ru.x != NULL)
      {
       __sgferr(761, "hierarchical path %s net %s not rightmost path element",
        grp->gnam, ncmp); 
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }
     if (sel_ndp != NULL) 
      {
       __sgferr(762, "hierarchical path %s ending net component %s select illegal - only generate or instance array select allowed",
        grp->gnam, ncmp); 
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }

     /* SJM 05/02/00 - hierarchical params legal following XL - add if not */
     /* ========
     if (syp->el.enp->n_isaparam)
      {
       __sgferr(762, "path %s component %s illegal hierachical reference to parameter",
        grp->gnam, ncmp, __to_sytyp(__xs, syp->sytyp)); 
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }
     ===== */

     /* DBG remove -- */
     if (xmri != xmrtsiz - 1) __misc_terr(__FILE__, __LINE__);
     /* DBG remove -- */

     /* cmp in scope sym tab net is in */ 
     if (last_xmp->xmp_petyp == XMP_GBLK) xmp->xmp_petyp = XMP_NET_INGEN;
     else xmp->xmp_petyp = XMP_NET;
     xmp->xmp_in_sytab = sytp;
     xmp->xmp_nxtcmp_sytab = NULL;
     /* in net and in gblk for net's same as one previous xmr cmp */ 
     if (last_xmp->xmp_petyp == XMP_GBLK)
      {
       xmp->xmp_in_gblkp = last_xmp->xmp_in_gblkp;
      }
     break;
    }
   /* case 3: task (t/f/l) - may or may not end path */
   if (syp->sytyp != SYM_TSK && syp->sytyp != SYM_F && syp->sytyp != SYM_LB)
    {
     __sgferr(762, "hierarchical path %s component %s illegal %s symbol type",
      grp->gnam, ncmp, __to_sytyp(__xs, syp->sytyp)); 
     xmp->xmp_err = TRUE;
     grp->gr_err = TRUE;
     return(FALSE);
    }
   xmp->xmp_petyp = XMP_TSK;

   /* XMR tasks are always in scopes */
   /* SJM 02-22-10 - LOOKATME? maybe also need to support tasks in gen blks */ 
   /* know that task in prev component mod sym tab, so can just use prev val */

   /* here previous sym tab's next can be t/f/lb or mod */

   /* xmr cmp syp already set */
   xmp->xmp_in_sytab = last_xmp->xmp_nxtcmp_sytab;
   xmp->xmp_nxtcmp_sytab = syp->el.etskp->tsksymtab;

   /* SJM 03-09-10 - XMR is a task call */
   if (gcmp_ndp->ru.x == NULL)
    {
     /* DBG remove -- */
     if (xmri != xmrtsiz - 1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     break; 
    }
   /* SJM 03-14-10 - need to move to variable in task */
   /* if labeled blocks in tasks can have many more components */
   gcmp_ndp = gcmp_ndp->ru.x;

   /* if found match but rest is not an in mod global - keep looking */
   /* and will later emit error */
  }
 return(TRUE);
}

/*
 * ROUTINES TO REOLVE XMRS - NOW SEPARATED FROM DFP RESOLVE
 */

/*
 * first step of fix up 2 after generate finished is to fill grefs from
 * xmrcmps build during generate expansion
 *
 * since this is done after all splitting and fix up of itree and static
 * inst tree - all grefs will have correct syms
 * all defparams set by here 
 *
 * SJM 08-27-11 - only need to do this is m gr tab not m dfp gr tab 
 * called only from fixup 2 after all params and defparams resolved
 */
extern void __resolve_xmrs_fr_xmrcmps(void)
{
 int32 gri;
 struct gref_t *grp; 
 struct mod_t *mdp;

 /* notice must include any newly split off modules here */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* SJM - 04-03-10 - if no grefs, mgrtab will not exist */
   if (mdp->mgrnum == 0) continue;

   __push_wrkitstk(mdp, 0);
   grp = &(mdp->mgrtab[0]);
   for (gri = 0; gri < mdp->mgrnum; gri++, grp++)
    {
     /* DBG remove --- */
     if (grp->gr_defparam) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* FIXME - for now leaving defparams but marked as gone here */
     /* why not remove? */
     if (grp->gr_err || grp->gr_gone) continue;

     /* SJM 04-11-10 - if error building xmr cmp tab, can't do anything */
     if (!bld_glb_xmrcmps(grp)) continue;
     /* DBG remove --
     if (__debug_flg)
      {
       __dbg_dmp_gref(grp);
      }
     --- */

     if (!grp->gr_err)
      {
       if (cvrt_local_xmr_back_to_xpr(grp)) continue;
      }

     /* must count here because must resolve globals from pli and debugger */
     if (!grp->gr_err && !grp->gr_gone) __num_glbs++;

     /* this can find errors */
     fill_gref_from_xmrcmps(grp);

     /* must count here because must resolve globals from pli and debugger */
     if (!grp->gr_err && !grp->gr_gone) __num_glbs++;
    }
   __pop_wrkitstk();
  }
 /* must free because can be many PLI systf args that are converted back */  
 free_gone_glbs();
}

/*
 * wrapper around global XMR resolve code for interactive mode use only
 *
 * SJM 04-03-11 - BEWARE - interactive XMR sepecially with gen blks probably
 * does notwork
 *
 * SJM 04-08-10 - now leaving the xmr cmp tab for later use
 */
extern int32 __do_xmr_resolve(struct gref_t *grp)
{
 /* DBG remove -- */
 if (grp->gr_defparam) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 if (!bld_glb_xmrcmps(grp)) return(FALSE);

 if (!grp->gr_err)
  {
   if (cvrt_local_xmr_back_to_xpr(grp)) return(TRUE);
  }
 if (!grp->gr_err && !grp->gr_gone)
  {
   /* SJM 04-03-11 - this is common routine for dfps and grefs to just */
   /* map the built xmr cmp tab to the gref d.s. */
   fill_gref_from_xmrcmps(grp);
  }

 /* DBG remove --
 if (__debug_flg)
  {
   dbg_dmp_xmrcmptab(grp, grp->gr_xmptab, grp->gr_num_xmps);
  }
 --- */
 if (grp->gr_err) return(FALSE);
 return(TRUE);
}

/*
 * build the global path name component symbol list (xmp tab) for 1 global
 *
 * SJM 03/14/10 
 * this requires that inst mod be set usually by push wrk itstk routine
 * it just decomposes xmr into path components so does not need itree context
 */
static int32 bld_glb_xmrcmps(struct gref_t *grp)
{
 int32 nxcmps, xmri;
 struct xmrcmp_t **xmrcmptab;

 /* DBG remove -- */
 if (grp->gr_defparam) __misc_terr(__FILE__, __LINE__);
 /* --- */

 __sfnam_ind = grp->grfnam_ind;
 __slin_cnt = grp->grflin_cnt;

 /* some consistency checking */
 /* DBG remove --- */
 if (grp->gxndp->optyp != GLBREF) __arg_terr(__FILE__, __LINE__);
 if (grp->glbref->optyp != GLBPTH) __arg_terr(__FILE__, __LINE__);
 if (grp->glbref->ru.x == NULL || grp->glbref->ru.x->optyp != XMRCOM)
  __arg_terr(__FILE__, __LINE__);
 /* --- */

 /* SJM 02-26-10 -  d.s is table of ptr to malloc xmrcmp records so can */
 /* modify and re-arrange later - not sure if needed */
 nxcmps = cnt_xmr_cmp_num(grp);
 xmrcmptab = (struct xmrcmp_t **)
  __my_malloc(nxcmps*sizeof(struct xmrcmp_t *));
 for (xmri = 0; xmri < nxcmps; xmri++)
  {
   xmrcmptab[xmri] = (struct xmrcmp_t *) __my_malloc(sizeof(struct xmrcmp_t));
   /* think do not really need to init here */
   init_xmrcmp(xmrcmptab[xmri]);
  }
 grp->gr_xmptab = xmrcmptab;
 grp->gr_num_xmps = nxcmps;

 /* SJM 09/15/00 - because of inst tree dependent upward rel forms */
 /* reauired by LRM must use old routine for defparams to fill head */

 /* fill root of non defparam xmr path */
 if (!bld_glb_hd_xmrcmp(xmrcmptab[0], grp))
  {
   grp->gr_err = TRUE;
   return(FALSE);
  }
 /* if only one component done */
 if (grp->glbref->ru.x->ru.x == NULL) return(TRUE);

 /* this is a normal xmr - fill rest of xmr path */
 /* this removes the intra-module path (except last) from glb sy cmps */
 /* SJM 03-28-10 - gcmp ndp 4 arg must be 2nd comp (not hd) */
 if (!bld_rest_xmrcmps(xmrcmptab, nxcmps, grp, grp->glbref->ru.x->ru.x))
  {
   grp->gr_err = TRUE;
   return(FALSE);
  }
 return(TRUE);
}

/*
 * count num of XMR hierarchical path components in an XMR
 *
 * SJM 02-26-10 - new alorithm stores every . separated component in
 * xmrcmp tab - needed because gen blks and in mod scopes do not appear
 * in grcmp tab
 */
static int32 cnt_xmr_cmp_num(struct gref_t *grp)
{
 int32 nxcmps;
 struct expr_t *gcmp_ndp;

 gcmp_ndp = grp->glbref->ru.x;
 /* know always at least one xmr path cmp */
 for (nxcmps = 0; gcmp_ndp != NULL; gcmp_ndp = gcmp_ndp->ru.x)
  {
   nxcmps++;
  }
 return(nxcmps);
}

/*
 * build the head xmrcmp record - minimal checking here 
 * returns F on error
 * rules for priority are: 
 * 1: in a scope that the XMR is in or is contained by higher scope including
 *    mod top level scope
 * 2: a top level generate block (not in mod top level sym tab so separate)
 * 3: the name of a module that is a top level module - therefore root
 * 4: mod name that matches that is not rooted, search up itree
 * 5: task/labeled block (but not gen block) in inst up in itree
 */
static int32 bld_glb_hd_xmrcmp(struct xmrcmp_t *xmp, struct gref_t *grp)
{
 int32 ndx;
 struct expr_t *ghd_ndp, *ndp, *sel_ndp;
 struct sy_t *modsyp, *syphd;
 struct symtab_t *sytp, *sytp2;
 struct mod_t *imdp;
 struct itree_t *in_itp, *itp2;
 struct xstk_t *xsp;
 char *ncmp, ncmpstr[RECLEN], s1[RECLEN];

 ghd_ndp = grp->glbref->ru.x;
 sel_ndp = NULL;
 if (ghd_ndp->lu.x->optyp == XMRID) ndp = ghd_ndp->lu.x;
 else if (ghd_ndp->lu.x->optyp == LSB)
   { ndp = ghd_ndp->lu.x->lu.x; sel_ndp = ghd_ndp->lu.x->ru.x; }
 else { __case_terr(__FILE__, __LINE__); return(FALSE); }

 strcpy(ncmpstr, ndp->ru.qnchp);
 /* SJM 03-31-11 - if select, needs to be part of ncmp */
 if (sel_ndp != NULL)
  {
   /* will not get here if not an index const expr */
   /* DBG remove -- */
   if (!__is_const_expr(sel_ndp)) __misc_terr(__FILE__, __LINE__);
   /* --- */
   __push_wrkitstk(grp->gin_mdp, 0);
   xsp = __eval_xpr(sel_ndp);
   __pop_wrkitstk();

   ndx = (int32) xsp->ap[0];
   __pop_xstk(); 
   sprintf(s1, "%s[%d]", ncmpstr, ndx);
   strcpy(ncmpstr, s1);
  }
 ncmp = ncmpstr;

 /* PRIORITY 0: gen block head - either within gref's gen blk or top gen blk */
 /* SJM 03-31-11 - new algorithm - first see if path head is downward */
 /* relative gen blk can be in or not in a gen blk */
 /* SJM 03-31-11 - notice that upward relative are only modules, not */
 /* gen blks */
 /* this searches for gen blks in mgen symtab */
 /* if a downward gen blk is found know syphd set with type SYM LGB */
 if ((syphd = try_fnd_nxtcmp_gblk(ncmp, grp->gin_mdp)) != NULL)
  {
   sytp = syphd->el.egblkp->gblk_sytab->sytpar;
   goto found_syphd;
  }

 /* SJM 04-01-11 - gref in sym tab will be post gen mod sym tab, but */
 /* if gref in gen blk, must work up through gen blk sym tabs */
 if (grp->gr_gblk_in != NULL) sytp = grp->gr_gblk_in->gblk_sytab;
 else sytp = grp->grsytp; 

 /* PRIORITY 1: in current sym tab or up including symbol in mod top level */
 /* work up all symbol tables starting with one defined so if downward */
 /* relative or really local, always finds first */
 for (syphd = NULL; sytp != NULL; sytp = sytp->sytpar)
  {
   if ((syphd = __zget_sym(ncmp, sytp->stsyms, sytp->numsyms)) != NULL) break;
  }

 /* PRIORITY 1a: special case because for tassk gblk sy tab needs name */
 /* with scope prefix */ 
 if (syphd == NULL && grp->gr_gblk_in != NULL)
  {
   syphd = try_fnd_in_gblk_tsk(ncmp, grp->gr_gblk_in, &sytp2);
   if (syphd != NULL) sytp = sytp2;
  }

 /* SJM 04-01-11 - if syphd found in gen blk sym table - need to get sym */
 /* mod not gen blk - elu ptr post gen will point to in mod symbol */
 /* with correct name */
 if (syphd != NULL && sytp->gblkofsyt != NULL)
  {
   if (syphd->sytyp == SYM_I) syphd = syphd->el.eip->isym;
   else if (syphd->sytyp == SYM_N) syphd = syphd->el.enp->nsym;
   else if (syphd->sytyp == SYM_F || syphd->sytyp == SYM_TSK
    || syphd->sytyp == SYM_LB)
    {
     syphd = syphd->el.etskp->tsksyp;
    }
   else __case_terr(__FILE__, __LINE__);

   /* SJM 04-01-11 - LOOKATME? - since not using ncmp, think do not need */
   /* to change to name in mod top level */
  }

found_syphd:
 if (syphd != NULL)
  {
   init_xmrcmp(xmp);
   xmp->xmp_cmpnam = __pv_stralloc(ncmp);
   xmp->gcmp_ndp = ghd_ndp;
   xmp->xmp_syp = syphd;
   xmp->xmp_in_sytab = sytp;
   if (syphd->sytyp == SYM_LGB || sytp->gblkofsyt != NULL)
    xmp->xmp_in_gblkp = sytp->gblkofsyt;
   else xmp->xmp_in_gblkp = NULL;

   /* case 1-a: net */
   if (syphd->sytyp == SYM_N)
    {
     /* SJM 03-01-10 - for net no next xmr cmp symtab */
     xmp->xmp_nxtcmp_sytab = NULL;

     /* this is one component guessed wrong as XMR, later changed to non XMR */
     if (xmp->xmp_in_gblkp != NULL)
      {
       xmp->xmp_petyp = XMP_NET_INGEN;
       grp->gr_has_genitem = TRUE;
      }
     else xmp->xmp_petyp = XMP_NET;

     /* if this is hierarchical global whose head is wire - error */
     /* but if only 1 component ok - because may find elsewhere */
     if (ghd_ndp->ru.x != NULL || !grp->gr_inst_ok)
      {
       __sgferr(754, "hierarchical reference %s first component %s %s illegal",
        grp->gnam, __to_wtnam(__xs, syphd->el.enp), syphd->synam);
       
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }
     /* must be wire not parameter here at end - param use xmr's illegal */
     if (!chk_xmr_tail_wire(grp, syphd, TRUE))
      {
       grp->gr_err = TRUE;
       xmp->xmp_err = TRUE;
       return(FALSE);
      }
     return(TRUE);
    }
   /* case 1-b: inst - most common downward relative path */
   if (syphd->sytyp == SYM_I)
    {
     /* AIV 03-29-10 - was using xmp in gblkp before set */
     if (xmp->xmp_in_gblkp != NULL)
      { 
       xmp->xmp_petyp = XMP_INST_INGEN;
       grp->gr_has_genitem = TRUE;
      } 
     else
      {
       xmp->xmp_petyp = XMP_INST;
       /* DBG remove -- */
       if (xmp->xmp_in_sytab->sypofsyt->sytyp != SYM_M) 
        __misc_terr(__FILE__, __LINE__);
       /* --- */
      }

     xmp->xmp_sel_ndp = sel_ndp;
     /* SJM 05-09-10 - set gref's path sel,was checking in wrong order */
     if (xmp->xmp_sel_ndp != NULL) grp->path_has_isel = TRUE;

     /* SJM 03-01-10 - for downward rel inst nxt cmp symtab to search in */
     /* is the downward inst's mod sym tab */
     xmp->xmp_nxtcmp_sytab = syphd->el.eip->imsym->el.emdp->msymtab;
     emit_downrel_nam_collision_informs(ncmp, grp);
     return(TRUE);
    }

   /* case 1-c: component is head of downward rel gen blk */
   if (syphd->sytyp == SYM_LGB)
    {
     xmp->xmp_petyp = XMP_GBLK;
     grp->gr_has_genitem = TRUE;
     /* SJM 03-01-10 - for gen blks, next search in gen blk sym tab */
     xmp->xmp_nxtcmp_sytab = syphd->el.egblkp->gblk_sytab;
     /* if gen blk in gen blk, containing gen blk already set */  
     return(TRUE);
    }

   /* case 1-d some kind of task/func or labeled block - know downard rel */
   if (syphd->sytyp == SYM_TSK || syphd->sytyp == SYM_F ||
    syphd->sytyp == SYM_LB)
    {
     /* also labeled blocks here */
     xmp->xmp_petyp = XMP_TSK;
     if (sel_ndp != NULL)
      {
       __sgferr(690, "hierarchical reference %s illegal - array of %s illegal",
        grp->gnam, __to_sytyp(__xs, syphd->sytyp));
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }
     /* SJM 03-01-10 - for t/f/lb - search for next cmp in t/f/l sym tab */
     xmp->xmp_nxtcmp_sytab = syphd->el.etskp->tsksymtab;
     return(TRUE);
    }   
//SJM 02-18-10 - can anything else go here ???
   __case_terr(__FILE__, __LINE__);
  }

 /* PRIORITY 2: rooted XMR - top level module */
 modsyp = __get_sym(ncmp, __modsyms);
 if (modsyp != NULL && modsyp->el.emdp->minstnum == 0)
  {
   init_xmrcmp(xmp);

   /* rooted is really inst since for rooted inst and mod names the same */
   xmp->xmp_petyp = XMP_MOD;
   xmp->xmp_is_rooted = TRUE;
   xmp->xmp_cmpnam = __pv_stralloc(ncmp);
   xmp->xmp_syp = modsyp;
   xmp->gcmp_ndp = ghd_ndp;
   xmp->xmp_in_sytab = __modsyms;
   /* SJM 03-01-10 - for rooted search for next cmp in mod's sym tab */
   xmp->xmp_nxtcmp_sytab = modsyp->el.emdp->msymtab;

   if (sel_ndp != NULL)
    {
     __sgferr(690, "select of rooted hierarchical reference %s illegal - top level module %s can not be an instance array",
      grp->gnam, ncmp);
     xmp->xmp_err = TRUE;
     grp->gr_err = TRUE;
     return(FALSE);
    }

   /* inform if also can be upward instance but not top - rooted used */
   /* itp is the itree inst element that matches */
   if ((itp2 = fnd_uprel_inst(ncmp, grp->gin_mdp->moditps[0])) != NULL
    && itp2->itip->imsym->el.emdp->minstnum != 0)
    {
     __sgfinform(464,
      "hierarchical path %s rooted but head %s also lower upward instance - rooted path used",
      grp->gnam, ncmp);
    }
   return(TRUE);
  }  
 /* SJM 03-12-10 - if not rooted, modsyp for uprelmod may still be set */
 /* if if also name of uprel inst, inst has priority so use first */

 /* PRIORITY 3: upward inst that is not rooted, search up itree */

 /* see if upward inst that is not rooted - use 0th instance for find */
 /* works because all upward relative paths must find same module type */
 /* SJM 03-12-11 - works up inst tree - if top found as priority 4 */
 in_itp = grp->gin_mdp->moditps[0];
 if ((itp2 = fnd_uprel_inst(ncmp, in_itp)) != NULL)
  {
   init_xmrcmp(xmp);

   /* SJM 03-12-10 - the gref grcmp here needs to be a mod since inst */
   /* tree may be rebuilt later - actual path set in v prp */
   /* SJM 03-12-10 - LOOKATME - this implies do not really know inst here */
   xmp->xmp_petyp = XMP_MOD;
   xmp->xmp_upwards_rel = TRUE;
   xmp->xmp_cmpnam = __pv_stralloc(ncmp);
   /* array of instances legal here */
   xmp->xmp_sel_ndp = sel_ndp;
   /* SJM 03-09-10 - must set gref's path sel if any xmr cmp has isel */
   if (xmp->xmp_sel_ndp != NULL) grp->path_has_isel = TRUE;
   xmp->gcmp_ndp = ghd_ndp;
   xmp->xmp_syp = itp2->itip->imsym;

//SJM? 02-20-10 - ??? FIXME will not see instances in gens not moved in yet
   /* DBG remove -- */
   if (itp2->up_it == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* itp2 is itree loc for the upward inst that match ncmp */
   xmp->xmp_in_sytab = itp2->up_it->itip->imsym->el.emdp->msymtab;
   /* SJM 03-01-10 - for upward rel know inst nxt cmp symtab to search in */
   /* is the up rel inst's mod sym tab */
   xmp->xmp_nxtcmp_sytab = xmp->xmp_syp->el.emdp->msymtab;

   /* found an upward relative inst, if more than one in src, error */
   /* if do not find same module for all */
   if (grp->gin_mdp->minstnum > 1) 
    {
     /* if instantiated in many places must always find exactly same */
     /* uprel module type */
     if (!chk_all_uprels_same(grp, modsyp, ncmp, ghd_ndp))
      {
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }      
    }

   /* inform if found inst and head also upward mod name - know not rooted */
   if (modsyp != NULL && fnd_uprel_mod(modsyp, in_itp) != NULL)
    {
     __sgfinform(464,
      "hierarchical path %s head %s upward relative instance but %s also upward module - instance used",
      grp->gnam, ncmp, ncmp);
    }
   return(TRUE);
  }

 /* priority 4: uprel mod that is not top level rooted */
 /* know in itp set from 4: */
 if (modsyp != NULL && (itp2 = fnd_uprel_mod(modsyp, in_itp)) != NULL)
  {
   xmp->xmp_petyp = XMP_MOD;
   xmp->xmp_upwards_rel = TRUE;
   xmp->xmp_cmpnam = __pv_stralloc(ncmp);
   if (sel_ndp != NULL)
    {
     __sgferr(690,
      "hierarchical reference %s select of upward relative module %s illegal",
      grp->gnam, ncmp);
     xmp->xmp_err = TRUE;
     grp->gr_err = TRUE;
     return(FALSE);
    }
   xmp->gcmp_ndp = ghd_ndp;
   xmp->xmp_syp = modsyp;
   /* itp2 is itree loc for the upward inst that has matching mod (from sy) */
   xmp->xmp_in_sytab = itp2->up_it->itip->imsym->el.emdp->msymtab;
   /* next down sym tab is just sym tab of matching mod */
   xmp->xmp_nxtcmp_sytab = xmp->xmp_syp->el.emdp->msymtab;

   /* SJM 03-12-10 - need to check all uprel mods from the gref in mod same */
   /* here too */
   /* found an upward relative inst, if more than one in src, error */
   /* if do not find same module for all */
   if (grp->gin_mdp->minstnum > 1) 
    {
     /* if instantiated in many places must always find exactly same */
     /* uprel module type */
     if (!chk_all_uprels_same(grp, modsyp, ncmp, ghd_ndp))
      {
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }      
    }
   return(TRUE);
  }

 /* PRIORITY 5: task/labeled block (but not gen block) in inst up in itree */
 /* SJM 02-20-10 - SJM ??? - LOOKATME - LRM says upward t/f/l names in */
 /* enclosing modules illegal, but allowed in current code */

 /* FIXME - will this be seen as XMR? - think not and test */
 /* finally try to find name as task/func/named block (other scope) */
 /* anywhere in upward module - must be one component non select form */
 if (ghd_ndp->ru.x == NULL)
  {
   if ((imdp = fnd_uprel_tskfunc(&(syphd), ncmp, in_itp)) == NULL)
    goto ref_err;

   init_xmrcmp(xmp);

   xmp->xmp_upwards_rel = TRUE;
   xmp->xmp_cmpnam = __pv_stralloc(ncmp);
   xmp->gcmp_ndp = ghd_ndp;
   xmp->xmp_syp = syphd;
   xmp->xmp_in_sytab = imdp->msymtab;
   /* SJM 03-01-10 - for t/f/lb - search for next cmp in t/f/l sym tab */
   xmp->xmp_nxtcmp_sytab = syphd->el.etskp->tsksymtab;
   /* AIV 01/20/11 - need to mark as task and save module symbol */
   xmp->xmp_petyp = XMP_TSK;
   xmp->xmp_uprel_msym = imdp->msym;

   if (sel_ndp != NULL)
    {
     __sgferr(690, "select of rooted hierarchical reference %s illegal - top level module %s can not be an instance array",
      grp->gnam, ncmp);
     xmp->xmp_err = TRUE;
     grp->gr_err = TRUE;
     return(FALSE);
    }
   return(TRUE);
  }

 /* finally illegal reference - head not found */ 
 /* finally, not found */
ref_err:
 /* SJM 03/29/02 - for 1 component - assume undeclared */
 if (ghd_ndp->ru.x == NULL)
  {
   /* DBG remove */
   if (strcmp(ncmp, grp->gnam) != 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   __sgferr(757,
    "%s undeclared - possibly undeclared one component cross module reference",
    grp->gnam);
  }
 else
  {
   __sgferr(757,
    "rooted, downward relative or upward relative hierarchical reference %s first component %s not found - illegal path head or undeclared",
    grp->gnam, ncmp);
  }
 init_xmrcmp(xmp);
 xmp->xmp_err = TRUE;
 grp->gr_err = TRUE;
 return(FALSE);
}


/*
 * fill xmrcmp tab for rest of path after head set
 *
 * fills xmrcmptab (assumes allocated to right size already) if no error
 * know head - index 0 of xmrcmptab set to head of XMR
 *
 * head filling routines differ but this proc used to fill the rest of
 * the path xmrcmps for both XMRs and defparams
 *
 * SJM 03-27-11 this uses e gblkp - works because set as first step after gen
 */
static int32 bld_rest_xmrcmps(struct xmrcmp_t **xmrcmptab, int32 xmrtsiz,
 struct gref_t *grp, struct expr_t *gcmp_ndp)
{
 int32 xmri, ndx;
 struct xmrcmp_t *xmp, *last_xmp;
 struct sy_t *syp;
 struct symtab_t *sytp;
 struct expr_t *ndp, *sel_ndp;
 struct genblk_t *in_gblkp, *this_gblkp;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct xstk_t *xsp;
 char *ncmp, ncmpstr[RECLEN], s1[RECLEN], s2[RECLEN];

 for (xmri = 1;; xmri++)
  {
   sel_ndp = NULL;
   if (gcmp_ndp->lu.x->optyp == XMRID) ndp = gcmp_ndp->lu.x;
   else if (gcmp_ndp->lu.x->optyp == LSB)
    { ndp = gcmp_ndp->lu.x->lu.x; sel_ndp = gcmp_ndp->lu.x->ru.x; }
   /* SJM 02/02/05 - part select legal but same as ID here */
   else if (gcmp_ndp->lu.x->optyp == PARTSEL 
    || gcmp_ndp->lu.x->optyp == PARTSEL_NDX_PLUS
    || gcmp_ndp->lu.x->optyp == PARTSEL_NDX_PLUS) 
    {
     ndp = gcmp_ndp->lu.x->lu.x;
    }
   else { __case_terr(__FILE__, __LINE__); return(FALSE); }

   /* SJM 03-31-11 - if select, needs to be part of ncmp */
   /* can use local var ncmpstr because when put in xmp, malloced */
   strcpy(ncmpstr, ndp->ru.qnchp);
   if (sel_ndp != NULL)
    {
     /* will not get here if not an index const expr */
     /* DBG remove -- */
     if (!__is_const_expr(sel_ndp)) __misc_terr(__FILE__, __LINE__);
     /* --- */

     __push_wrkitstk(grp->gin_mdp, 0);
     xsp = __eval_xpr(sel_ndp);
     __pop_wrkitstk();

     /* DBG remove -- */
     if (xsp->bp[0] != 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
     ndx = (int32) xsp->ap[0];
     __pop_xstk(); 
     /* s1 and s2 are tmp strings but ncmpstr is not */
     sprintf(s1, "%s[%d]", ncmpstr, ndx);
     strcpy(ncmpstr, s1);
    }
   ncmp = ncmpstr;

   xmp = xmrcmptab[xmri];
   last_xmp = xmrcmptab[xmri - 1]; 
   in_gblkp = NULL;

   /* case 1: last component is a gen blk */
   /* for each pass thru loop, see in gblkp if inside a gblk */
   if (last_xmp->xmp_petyp == XMP_GBLK)
    {
     in_gblkp = last_xmp->xmp_syp->el.egblkp;
     mdp = in_gblkp->gblk_mod_in;

     if ((syp = try_fnd_nxtcmp_gblk(ncmp, mdp)) != NULL)
      goto found_xmr_sym;
     /* may be net or inst or task */
     __bld_gen_scope_nam(s1, in_gblkp);
     sprintf(s2, "%s.%s", s1, ncmp);
     if ((syp = __zget_sym(s2, mdp->msymtab->stsyms, mdp->msymtab->numsyms)) 
      != NULL) goto found_xmr_sym;
    }
   /* case 2: last component is a module */
   if (last_xmp->xmp_petyp == XMP_MOD)
    {
     /* DBG remove -- */
     if (last_xmp->xmp_syp->sytyp != SYM_M) __misc_terr(__FILE__, __LINE__);
     /* --- */
     mdp = last_xmp->xmp_syp->el.emdp;
     /* case 1a: see if in gref */
     if ((syp = try_fnd_nxtcmp_gblk(ncmp, mdp)) != NULL)
      goto found_xmr_sym;
     /* case 2a: see if in mod */
     if ((syp = __zget_sym(ncmp, mdp->msymtab->stsyms, mdp->msymtab->numsyms)) 
      != NULL) goto found_xmr_sym;
    }
   /* case 3: last component an inst */ 
   if (last_xmp->xmp_petyp == XMP_INST
    || last_xmp->xmp_petyp == XMP_INST_INGEN)
    {
     /* DBG remove -- */
     if (last_xmp->xmp_syp->sytyp != SYM_I) __misc_terr(__FILE__, __LINE__);
     /* --- */
     mdp = last_xmp->xmp_syp->el.eip->imsym->el.emdp;

     /* case 1a: see if in gref */
     if ((syp = try_fnd_nxtcmp_gblk(ncmp, mdp)) != NULL)
      goto found_xmr_sym;
     /* case 2a: see if in mod */
     if ((syp = __zget_sym(ncmp, mdp->msymtab->stsyms, mdp->msymtab->numsyms)) 
      != NULL) goto found_xmr_sym;
    }
   /* case 4: last component a task/func/labeled block */
   if (last_xmp->xmp_petyp == XMP_TSK)
    {
     /* DBG remove -- */
     if (last_xmp->xmp_syp->sytyp != SYM_F
      && last_xmp->xmp_syp->sytyp != SYM_TSK
      && last_xmp->xmp_syp->sytyp != SYM_LB) __misc_terr(__FILE__, __LINE__);
     /* --- */
     tskp = last_xmp->xmp_syp->el.etskp;
     if ((syp = __zget_sym(ncmp, tskp->tsksymtab->stsyms,
      tskp->tsksymtab->numsyms)) != NULL) goto found_xmr_sym;
    }

   sytp = last_xmp->xmp_nxtcmp_sytab;
   if (sytp->sypofsyt != NULL) strcpy(s1, sytp->sypofsyt->synam);
   else
    {
     /* DBG remove -- */
     if (sytp->gblkofsyt == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     sprintf(s1, "generate block %s", sytp->gblkofsyt->gblknam);
    }
//SJM 04-02-11 - PUTMEBACK - after working change to better err msg 
/* ====
   __sgferr(758, "hierarchical path %s (in %s) component %s undeclared in %s",
    grp->gnam, grp->gin_mdp->msym->synam, ncmp, s1);
==== */
   __sgferr(758, "hierarchical path %s component %s undeclared in %s",
    grp->gnam, ncmp, s1);

   xmp->xmp_err = TRUE;
   grp->gr_err = TRUE;
   return(FALSE);

found_xmr_sym:
   /* SJM 03-29-11 - this code has found the next symbol from last_xmp */
   /* info now fills the next one*/
   /* counted so one xmr cmp for each part of XMR although in gr cmps */
   /* may have disappeared */
   if (xmri + 1 >= MAXGLBCOMPS - 1 || xmri + 1 > xmrtsiz)
    {
     __pv_terr(310, "hierarchical path %s has too many components (%d)",
      grp->gnam, MAXGLBCOMPS);
    }
   xmp->xmp_cmpnam = __pv_stralloc(ncmp);
   xmp->xmp_syp = syp;
   xmp->gcmp_ndp = gcmp_ndp;
   /* code below determines if array of scope legal */
   xmp->xmp_sel_ndp = sel_ndp;

   /* SJM 03-09-10 - must set gref's path sel if any xmr cmp has isel */
   if (xmp->xmp_sel_ndp != NULL) grp->path_has_isel = TRUE;

   /* virtual case 0: descending through gen blks */
   /* SJM 03-15-10 - if found a genblk in symtab search, add virtual xmp, */
   /* update ptrs and keep looping - this xmr cmp will be removed later */
   if (syp->sytyp == SYM_LGB)
    {
     this_gblkp = syp->el.egblkp;
     /* SJM 03-01-10 - in sym tab is this gen blk */
     xmp->xmp_in_sytab = this_gblkp->gblk_sytab->sytpar;
  
     /* SJM 03-01-10 - when moving downward and find inst, sytp is the next */
     /* down symtab to look in */
     xmp->xmp_nxtcmp_sytab = this_gblkp->gblk_sytab;
   
     /* SJM 03-31-11 - if non nested gblk - no in any gblk */
     if (this_gblkp->gblk_sytab->sytpar->gblkofsyt != NULL) 
      xmp->xmp_in_gblkp = this_gblkp->gblk_sytab->sytpar->gblkofsyt;
     else xmp->xmp_in_gblkp = NULL;

     xmp->xmp_petyp = XMP_GBLK;

     /* next down gen blk */
     /* DBG remove --- */
     if (gcmp_ndp->ru.x == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     gcmp_ndp = gcmp_ndp->ru.x;
     continue;
    }

   /* case 1: in downward relative inst - can end path */
   if (syp->sytyp == SYM_I)
    {
     if (last_xmp->xmp_in_gblkp != NULL)
      {
       xmp->xmp_petyp = XMP_INST_INGEN;
       xmp->xmp_in_gblkp = last_xmp->xmp_in_gblkp; 
      }
     else xmp->xmp_petyp = XMP_INST;


     /* SJM 03-31-11 - for inst in gen blk, saying in gen blk sym tab */
     /* but really in mod sym tab with gen blk prefix added to name */
     xmp->xmp_in_sytab = last_xmp->xmp_nxtcmp_sytab;

     /* SJM 03-01-10 - when moving downward and find inst, sytp is the next */
     /* down symtab to look in */
     sytp = syp->el.eip->imsym->el.emdp->msymtab;
     xmp->xmp_nxtcmp_sytab = sytp;
     if ((gcmp_ndp = gcmp_ndp->ru.x) == NULL)
      {
       /* DBG remove -- */
       if (xmri != xmrtsiz - 1) __misc_terr(__FILE__, __LINE__);
       /* DBG remove -- */
       return(TRUE);
      }      
     continue;
    }
   /* case 2: in downward relative net - must end path */
   if (syp->sytyp == SYM_N)
    {
     if (gcmp_ndp->ru.x != NULL)
      {
       __sgferr(761, "hierarchical path %s net %s not rightmost path element",
        grp->gnam, ncmp); 
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }
     if (sel_ndp != NULL) 
      {
       __sgferr(762, "hierarchical path %s ending net component %s select illegal - only generate or instance array select allowed",
        grp->gnam, ncmp); 
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }

     /* SJM 05/02/00 - hierarchical params legal following XL - add if not */
     /* ========
     if (syp->el.enp->n_isaparam)
      {
       __sgferr(762, "path %s component %s illegal hierachical reference to parameter",
        grp->gnam, ncmp, __to_sytyp(__xs, syp->sytyp)); 
       xmp->xmp_err = TRUE;
       grp->gr_err = TRUE;
       return(FALSE);
      }
     ===== */

     /* DBG remove -- */
     if (xmri != xmrtsiz - 1) __misc_terr(__FILE__, __LINE__);
     /* DBG remove -- */

     /* cmp in scope sym tab net is in */ 
     if (last_xmp->xmp_petyp == XMP_GBLK) xmp->xmp_petyp = XMP_NET_INGEN;
     else xmp->xmp_petyp = XMP_NET;
     /* DBG remove -- */ 
     if (last_xmp->xmp_nxtcmp_sytab == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     xmp->xmp_in_sytab = last_xmp->xmp_nxtcmp_sytab;
     xmp->xmp_nxtcmp_sytab = NULL;
     /* in net and in gblk for net's same as one previous xmr cmp */ 
     if (last_xmp->xmp_petyp == XMP_GBLK)
      {
       xmp->xmp_in_gblkp = last_xmp->xmp_in_gblkp;
      }
     break;
    }
   /* case 3: task (t/f/l) - may or may not end path */
   if (syp->sytyp != SYM_TSK && syp->sytyp != SYM_F && syp->sytyp != SYM_LB)
    {
     __sgferr(762, "hierarchical path %s component %s illegal %s symbol type",
      grp->gnam, ncmp, __to_sytyp(__xs, syp->sytyp)); 
     xmp->xmp_err = TRUE;
     grp->gr_err = TRUE;
     return(FALSE);
    }
   xmp->xmp_petyp = XMP_TSK;

   /* XMR tasks are always in scopes */
   /* SJM 02-22-10 - LOOKATME? maybe also need to support tasks in gen blks */ 
   /* know that task in prev component mod sym tab, so can just use prev val */

   /* here previous sym tab's next can be t/f/lb or mod */

   /* xmr cmp syp already set */
   xmp->xmp_in_sytab = last_xmp->xmp_nxtcmp_sytab;
   xmp->xmp_nxtcmp_sytab = syp->el.etskp->tsksymtab;

   /* SJM 03-09-10 - XMR is a task call */
   if (gcmp_ndp->ru.x == NULL)
    {
     /* DBG remove -- */
     if (xmri != xmrtsiz - 1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     break; 
    }
   /* SJM 03-14-10 - need to move to variable in task */
   /* if labeled blocks in tasks can have many more components */
   gcmp_ndp = gcmp_ndp->ru.x;

   /* if found match but rest is not an in mod global - keep looking */
   /* and will later emit error */
  }
 return(TRUE);
}

/*
 * try to find a gen blk - can be in mod or inst or other gen blk only
 *
 * SJM 03-31-11 - mgen sym tab is not frozen (no stsyms) and has all
 * insts and gen blks,  gen blk sytab is frozen and has normal parent
 * and offspring struct within a mod's gen blks
 */
static struct sy_t *try_fnd_nxtcmp_gblk(char *ncmp, struct mod_t *in_mdp)
{
 struct sy_t *syp;
 struct genblk_t *gblkp;

 if (in_mdp->mgen_symtab == NULL) return(NULL);
 if ((syp = __get_sym(ncmp, in_mdp->mgen_symtab)) == NULL) return(NULL);
 if (syp->sytyp != SYM_LGB) return(NULL);
 gblkp = syp->el.egblkp;
 /* gblk sytab always must have a parent (mod for non nested gblks */
 /* SJM 03-31-11 - if previous err e gblkp may not be set */ 
 if (gblkp == NULL) return(NULL);

 /* DBG remove -- */
 if (gblkp->gblk_sytab == NULL || gblkp->gblk_sytab->sytpar == NULL)
   __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* AIV 04/13/11 - removed code which was incorrect for new XMR generate */
 return(syp);
}

/*
 * routine to try to find tasks or functions defined in gen blks
 *
 * SJM 04-04-11 - needed because even in gen blk gblk sytab, need to
 * store t/f with full gen blk scope name
 */
static struct sy_t *try_fnd_in_gblk_tsk(char *ncmp, struct genblk_t *cur_gblkp,
 struct symtab_t **sytp2)
{
 struct symtab_t *sytp;
 struct genblk_t *gblkp;
 struct sy_t *syp;
 char s1[RECLEN], s2[RECLEN];

 gblkp = cur_gblkp;
 for (;;)
  {
   sytp = gblkp->gblk_sytab;
   __bld_gen_scope_nam(s1, gblkp);
   sprintf(s2, "%s.%s", s1, ncmp);
   if ((syp = __zget_sym(s2, sytp->stsyms, sytp->numsyms)) != NULL)
    {
     *sytp2 = sytp;
     return(syp);
    }
   sytp = sytp->sytpar;
   if (sytp->gblkofsyt == NULL) break;
   gblkp = sytp->gblkofsyt;
  }
 return(NULL);
}

/*
 * SOME DBG DMP ROUTINES
 */

/*
 * routine to dump a gen blk
 */
static void dbg_dmp_gblk_body(struct genblk_t *gblkp)
{
 int32 t1, t2, t3;
 struct symtab_t *sytp, *sytp2;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 if (gblkp->gitems != NULL) t1 = 1; else t1 = 0;
 if (gblkp->gblk_tsks != NULL) t2 = 1; else t2 = 0;
 if (gblkp->dfp_gitems != NULL) t3 = 1; else t3 = 0;

 __dbg_msg(
  ")-> dumping genblk %s (id=%d) at %s <grefs=%d,in_gfor=%d,items=%d,tfs=%d,dfps=%d\n",
  gblkp->gblknam, gblkp->gen_id, __bld_lineloc(__xs, gblkp->genblk_fnam_ind,
  gblkp->genblk_lin_cnt),  gblkp->gblk_has_grefs, gblkp->gblk_in_gfor,
  t1, t2, t3);

 if (gblkp->gblk_mod_in == NULL) strcpy(s1, "?NONE?");
 else sprintf(s1, "%s", gblkp->gblk_mod_in->msym->synam);
 if (gblkp->gvnp == NULL) strcpy(s2, "?NONE?");
 else strcpy(s2, gblkp->gvnp->nsym->synam);
 __dbg_msg("    mod_in=%s, genvar net %s\n", s1, s2);

 if ((sytp = gblkp->gblk_sytab) == NULL) __dbg_msg("    sytab=?NONE?\n");
 else
  {
   if (sytp->gblkofsyt != NULL)
    {
     sprintf(s1, "gblk_of=%s", sytp->gblkofsyt->gblknam);
    }
   else sprintf(s1, "scope_of=%s", sytp->sypofsyt->synam);
   if ((sytp2 = sytp->sytpar) == NULL) strcpy(s2, "par sytab=?NONE?");
   else
    {
     if (sytp2->gblkofsyt != NULL)
      {
       sprintf(s2, "par gblk_of=%s", sytp2->gblkofsyt->gblknam);
      }
     else sprintf(s2, "par scope_of=%s", sytp2->sypofsyt->synam);
    }
   if (sytp->stsyms != NULL) strcpy(s3, "has stsyms");
   else strcpy(s3, "unfrozen");
   __dbg_msg("    %s %s nsyms=%d freezes=%d %s\n", s1, s2, sytp->numsyms,
    sytp->freezes, s3);
  }  
 __dbg_msg(")-> END GBLK )->\n");
}


/*
 * routine to dump a gref record
 */
extern void __dbg_dmp_gref(struct gref_t *grp)
{
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN];

 __dbg_msg(
  "$$ dumping gref %s at %s <uprel=%d,rt=%d,isel=%d,dfp=%d,genitem=%d\n",
  grp->gnam, __bld_lineloc(__xs, grp->grfnam_ind, grp->grflin_cnt),
  grp->upwards_rel, grp->is_rooted, grp->path_has_isel, grp->gr_defparam,
  grp->gr_has_genitem);

  if (grp->gxndp == NULL) strcpy(s1, "?NONE?");
  else __msgexpr_tostr(s1, grp->gxndp);
  if (grp->glbref != NULL) strcpy(s2, "?NONE?");
  else __msgexpr_tostr(s2, grp->glbref);
  if (grp->grsytp == NULL) strcpy(s3, "?NONE?");
  else
   {
    if (grp->grsytp->sypofsyt != NULL)
     {
      sprintf(s3, "%s symtab for %s",
       __to_sytyp(__xs, grp->grsytp->sypofsyt->sytyp),
       grp->grsytp->sypofsyt->synam);
     }
    else sprintf(s3, "genblk %s symtab", grp->grsytp->gblkofsyt->gblknam);
   }
  if (grp->gr_gblk_in == NULL) strcpy(s4, "?NONE?");
  else strcpy(s4, grp->gr_gblk_in->gblknam);
  __dbg_msg("  gxndp=%s glbref=%s %s in genblk=%s\n", s1, s2, s3, s4);

  if (grp->targmdp == NULL) strcpy(s1, "?NONE?");
  else strcpy(s1, grp->targmdp->msym->synam);
  if (grp->targtskp == NULL) strcpy(s2, "?NONE?");
  else strcpy(s2, grp->targtskp->tsksyp->synam);
  if (grp->gin_mdp == NULL) strcpy(s3, "?NONE?");
  else strcpy(s3, grp->gin_mdp->msym->synam);
  if (grp->targsyp == NULL) strcpy(s4, "?NONE?");
  else
   {
    sprintf(s4, "%s(symtyp=%s)", grp->targsyp->synam,
     __to_sytyp(__xs, grp->targsyp->sytyp));
   }
  __dbg_msg("  targmdp=%s targtsk=%s gin_mdp=%s targsyp=%s\n",
    s1, s2, s3, s4);

  dbg_dmp_grcmps(grp);
  dbg_dmp_xmrcmptab(grp, grp->gr_xmptab, grp->gr_num_xmps);

 __dbg_msg("$$ END GREF $$\n");
}

/*
 * debug routine to dump grcmps symbols
 *
 * not dumping grxcmps for arrays of inst select for now
 */
static void dbg_dmp_grcmps(struct gref_t *grp)
{
 int32 gri;
 struct sy_t *syp;

 __dbg_msg("=== for gref %s GRCMPS size %d\n", grp->gnam, grp->last_gri + 1);
 for (gri = 0; gri <= grp->last_gri; gri++)
  {
   syp = grp->grcmps[gri];
   __dbg_msg("    grcmp %d sym %s type %s\n", gri, syp->synam,
    __to_sytyp(__xs, syp->sytyp));
  }
 __dbg_msg("=== END GRCMPS ===\n");
}

/*
 * debug routine to dump xmrcmp tab
 */
static void dbg_dmp_xmrcmptab(struct gref_t *grp, struct xmrcmp_t **xmrcmptab,
 int32 nxcmps) 
{
 int32 xmri;
 struct xmrcmp_t *xmp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];
 extern char *__to_xmrcmp_nam(char *, int32);

 __dbg_msg("+++ dumping gref %s xmrcmp tab path len %d\n", grp->gnam,
  nxcmps);
 for (xmri = 0; xmri < nxcmps; xmri++)
  {
   xmp = xmrcmptab[xmri];
   if (xmp->xmp_alt_cmpnam == NULL) strcpy(s2, "");
   else strcpy(s2, xmp->xmp_alt_cmpnam);

   __dbg_msg("    %s cmp: nam=%s alt nam=%s sy=%s rt=%d uprel=%d\n",     
    __to_xmrcmp_nam(__xs, xmp->xmp_petyp), xmp->xmp_cmpnam, s2,
    xmp->xmp_syp->synam, xmp->xmp_is_rooted, xmp->xmp_upwards_rel);

   if (xmp->xmp_in_gblkp == NULL) strcpy(s1, "");
   else strcpy(s1, xmp->xmp_in_gblkp->gblknam); 

   /* SJM 03-30-11 - for xmp net components, no in sytab */
   if (xmp->xmp_in_sytab == NULL) strcpy(s2, "?NO XMP SYTAB?");
   else
    {
     if (xmp->xmp_in_sytab->sypofsyt == NULL)
      {
       if (xmp->xmp_in_sytab->gblkofsyt != NULL)
        {
         sprintf(s2, "GBLK=%s", xmp->xmp_in_sytab->gblkofsyt->gblknam);
         }
       else strcpy(s2, "**MODS**");
      }
     else strcpy(s2, xmp->xmp_in_sytab->sypofsyt->synam);
    }

   if (xmp->xmp_nxtcmp_sytab == NULL) strcpy(s3, "**NONE**");
   else if (xmp->xmp_nxtcmp_sytab->sypofsyt == NULL) strcpy(s3, "**MODS**");
   else strcpy(s3, xmp->xmp_nxtcmp_sytab->sypofsyt->synam);

   __dbg_msg("    in sytab=%s nxt cmp sytab=%s gblkp=%s\n", s2,
    s3, s1);
  }
 __dbg_msg("+++ END XMRCMPS +++\n");
}

/*
 * ROUTINES TO MOVE FROM XMR CMPS TO GREFS  
 */

/*
 * routine to fill global xcmps table var and expr and then build the gref's
 * grcmps structure and set the various final gref fields and bits
 *
 * SJM 02-28-10 - new separated routine because can't do this step - must leave
 * and rebuild the xmrcmps fields during generate - loops for multiple
 * relaxation tries of generate free and then rebuild xmrcmps only
 * for defparams this is used immediately then the extra checking happens 
 */
static void fill_gref_from_xmrcmps(struct gref_t *grp)
{
 int32 gi;
 struct sy_t *scop_syp, **syarr;
 struct expr_t **syxarr;

 /* SJM 02-28-10 - ??? wonder if removal of grefs can be done ealier - during */
 /* gen for XMRs - think not */
//SJM 04-08-10 - WRITEME?? - still need routine which find XMR patterns that
// are not really XMR so converted back to normal expr and remove gref

 /* SJM 03-09-10 - was not filling all the needed gref fields */
 /* first set a number of gref fields form the xmrcmp head */
 grp->upwards_rel = grp->gr_xmptab[0]->xmp_upwards_rel;
 grp->is_rooted = grp->gr_xmptab[0]->xmp_is_rooted;

 /* fill global glb sy cmps and glb x cmps and set size */
 /* SJM 02-26-10 - this is step to create the grcmps tab that is not 1-to-1 */
 /* with gref name hierarchical path components expected by code from here on */
 /* notice this sets global c var, last gsc */ 
 fill_glbcmps_from_xmrcmp(grp);

 /* now fill various gref fields - target symbol always last even if inst. */
 grp->targsyp = __glbsycmps[__last_gsc];

 /* SJM 04-08-10 - do not need to set targ tskp for gref, now set in fill */

 /* need to set syp as ending inst. not var for setting targmdp */
 if (grp->targsyp->sytyp == SYM_I || grp->targsyp->sytyp == SYM_M)
  scop_syp = grp->targsyp;
 /* syp is 1 before target end - usually will be inst. */
 else 
  {
   /* for task before final net, know will be caught by routine that */
   /* cvrts local xmr back to simple expr */
   /* SJM 04-03-11 - fixed so local xmr in gen blk(s), now caught */ 
   /* DBG remove -- */ 
   if (__last_gsc <= 0) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   scop_syp = __glbsycmps[__last_gsc - 1]; 
  }


 /* may be dumpvars or scope style instance reference */
 if (scop_syp->sytyp == SYM_I)
  {
   grp->targmdp = scop_syp->el.eip->imsym->el.emdp;
  }
 else if (scop_syp->sytyp == SYM_M) grp->targmdp = scop_syp->el.emdp;
 else 
  {
   __sgferr(1107,
    "hierarchical path reference %s target symbol %s type %s illegal",  
    grp->gnam, scop_syp->synam, __to_sytyp(__xs, scop_syp->sytyp)); 
   grp->gr_err = TRUE;
   return;
  }

 /* handle special scope globals */
 /* can be module for top only or upward relative one component */
 if (grp->targsyp->sytyp == SYM_I || grp->targsyp->sytyp == SYM_M) 
  {
   /* task scope form looks like normal here and checked elsewhere */
   if (!grp->gr_inst_ok)
    {
     __sgferr(1030,
      "special system task instance form argument %s not allowed here",
      grp->gnam);
     grp->gr_err = TRUE;
     return;
    }
   /* adjust last component so it stays as part of path here */
   /* targsyp and last are same symbol */
   /* SJM 02-28-10 - this was once a short int, but no more */
   /* SJM 03-14-10 - for scope XMRs last is really last since no net */   
   /* for for normal last is last scope object */
   grp->last_gri = __last_gsc;
  }
 else grp->last_gri = __last_gsc - 1;

 if (!chk_glb_inst_sels(grp))
  {
   grp->gr_err = TRUE;
   return;
  }

 /* allocate the array of symbols in malloced storage */
 syarr = (struct sy_t **)
   __my_malloc((__last_gsc + 1)*sizeof(struct sy_t *));
 grp->grcmps = syarr;

 syxarr = (struct expr_t **)
   __my_malloc((__last_gsc + 1)*sizeof(struct expr_t *));
 grp->grxcmps = syxarr;

 /* tail pointed to by targsyp end of syarr is last instance symbol */
 /* for scope object targsyp and last syarr same */ 
 for (gi = 0; gi <= __last_gsc; gi++)
  {
   grp->grcmps[gi] = __glbsycmps[gi];
   /* will be nil for non inst. select */
   grp->grxcmps[gi] = __glbxcmps[gi];
  }

 /* check and fold gref instance array select constant select expressions */
 if (grp->path_has_isel)
  {
   char s1[RECLEN];

   for (gi = 0; gi <= grp->last_gri; gi++) 
    {
     if (grp->grxcmps[gi] == NULL) continue;

     sprintf(s1, "hierarchical reference instance array index (pos. %d)",
      gi + 1);
     if (!__chkndx_expr(grp->grxcmps[gi], s1))
      {
       grp->gr_err = TRUE;
       return;
      }
    }
  }

 /* even though downward really rooted, must not treat as rooted */
 /* until variable xmr converted to location - for defparam need to */
 /* add module name (1 level) prefix */

 /* fill symbol grp expr and grp ru expr field already cross linked */
 /* for disable will point to disable expr. */
 /* LOOKATME - although XMRCOM expr contents no longer accessible */
 /* can not free because grp points to grcmps - slight memory leak here */
 grp->gxndp->ru.grp = grp;
 grp->gxndp->lu.sy = grp->targsyp;
}

/*
 * routine to fill glb sy cmps and glb xcms arrays from xrmcmps tab
 *
 * SJM 03-28-10 - new simpler algorithm because xmrcmp tab fixed up when
 * XMRs (and defparam lhs XMR) moved into mod tab
 *
 * SJM 03-28-10 - assuming XMR checking before here
 * **BEWARE** - SJM 04-07-10 - glbsycmps is not actual path since for tasks
 * one before end is the task sym and end is the net with any labeled
 * blocks removed (its for finding target)
 */
static void fill_glbcmps_from_xmrcmp(struct gref_t *grp)
{
 int32 xmri, xmri2, nxcmps;
 struct xmrcmp_t *xmp, *xmp2, *xmp3;
 struct xmrcmp_t **xmrcmptab;
 struct sy_t *syp;
 
 xmrcmptab = grp->gr_xmptab;
 nxcmps = grp->gr_num_xmps;
 __last_gsc = -1;
 for (xmri = 0; xmri < nxcmps; xmri++) 
  {
//SJM 03-28-10 - LOOAKTME? - not sure of some of these cases - sketching in
   xmp = xmrcmptab[xmri];
   switch (xmp->xmp_petyp) {
    case XMP_INST: case XMP_INST_INGEN:
     /* SJM 03-31-11 - even for insts in gen blks, xmp syp is the mod's inst */
     /* symbol here - only indication is name is qualified with gen scope */
     __glbsycmps[++__last_gsc] = xmp->xmp_syp;
     /* will be nil for non inst. select */
     __glbxcmps[__last_gsc] = xmp->xmp_sel_ndp;
     break;
    case XMP_MOD:
     __glbsycmps[++__last_gsc] = xmp->xmp_syp;
     /* will be nil for non inst. select */
     __glbxcmps[__last_gsc] = xmp->xmp_sel_ndp;
     break;
    case XMP_TSK:
//SJM 03-29-11 - think right because except for upwards rel, tskp sy right
     /* SJM 04-07-10 - code for tasks must duplicate old scheme where */
     /* routine find inmod sym used - not using similar routine because */
     /* xmr cmp tab already built */

     /* know xmr cmp tab is ether <some insts> <a task> with targ tskp set */
     /* or <some insts><a net> with targ tskp set to final (if label blks) */
     /* task the ending net is in */  
     /* SJM 04-08-10 - this matches old algorithm where only need sym */
     /* since all variables really stored at top mod level anyway */

     /* SJM - 04-07-10 - glb sy cmps does not have the tasks because */
     /* indicated by targ tskp - NOTICE no tsk/f/lb in glb cmp sys */

     /* check up to one before end that each xmr cmp tab value is a t/f/lb */
     /* once hit a task - can't see any gen blks for in gen blk XMRs */
     /* terrs since already checked */
     /* DBG remove -- */
     for (xmri2 = xmri + 1; xmri2 < nxcmps - 1; xmri2++)
      {
       xmp2 = xmrcmptab[xmri2];
       if (xmp2->xmp_petyp != XMP_TSK) __misc_terr(__FILE__, __LINE__);
       if (xmp2->xmp_sel_ndp != NULL) __misc_terr(__FILE__, __LINE__);   
       syp = xmp2->xmp_syp;
       if (syp->sytyp != SYM_TSK && syp->sytyp != SYM_F
        && syp->sytyp != SYM_LB) __misc_terr(__FILE__, __LINE__);
      }
     /* --- */
     /* end can either be task or func or net here */
     xmp2 = xmrcmptab[nxcmps - 1];
     if (xmp2->xmp_petyp == XMP_NET) 
      {
       /* case 1: net at end - do not store any tasks in glb sy cmps tab */
       __glbsycmps[++__last_gsc] = xmp2->xmp_syp;
       xmp3 = xmrcmptab[nxcmps - 2]; 
       grp->targtskp = xmp3->xmp_syp->el.etskp;
      }
     else if (xmp2->xmp_petyp == XMP_TSK)
      {
       /* AIV 01/20/11 - if uprel need to get the module symbol as well */
       /* this was wrong in the new code - following previous model */
       if (xmp->xmp_upwards_rel)
        {
         /* DBG remove -- */
         if (xmp2->xmp_uprel_msym == NULL) __misc_terr(__FILE__, __LINE__);   
         /* --- */ 
         __glbsycmps[++__last_gsc] = xmp->xmp_uprel_msym;
        }
       /* case 2: xmr is task/func (for call?) */
       __glbsycmps[++__last_gsc] = xmp2->xmp_syp;
       /* DBG remove -- */
       if (xmp2->xmp_sel_ndp != NULL) __misc_terr(__FILE__, __LINE__);   
       /* --- */ 
       grp->targtskp = xmp2->xmp_syp->el.etskp;
      }
     else __case_terr(__FILE__, __LINE__);
     return;
    case XMP_NET: case XMP_NET_INGEN:
     /* net must always be tail - if see task in xmr cmp will not get here */
     /* DBG remove -- */
     if (xmri != nxcmps -1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* put in net as last component */
     /* know never get here if net in t/f/lb */

     /* SJM 03-31-11 - again net sym is in mod with scope prefix */
     __glbsycmps[++__last_gsc] = xmp->xmp_syp;
     /* net end select not seen here - no select expr allowed */
     if (xmp->xmp_sel_ndp != NULL) __misc_terr(__FILE__, __LINE__);
     /* expr component will be nil for non inst. select */
     __glbxcmps[__last_gsc] = NULL;
     /* SJM 04-07-10 - all the checking done when bld the xmr cmp tab */
     /* net must be end */
     return;
    case XMP_GBLK:
     /* SJM 03-31-11 - just skip since actual sym in mod even if gened */
     /* gen blks just used for getting right scope prefixes */
     break;  
    default:
     __case_terr(__FILE__, __LINE__);
   }
  }
}


/*
 * resolve a local XMR name that is a qualified post gen and post fixup
 * name back to normal var
 *
 * if really local path, converted back to simple expr and checked as id later
 *
 * here caller handled instance arrays - know in module scope symbols
 * are never arrayed (error emitted if select appears)
 *
 * SJM 04-03-11 - now separate routine for xmr's since name are post
 * gen genblk qualified in symbol tables
 *
 * cannot use gblref expr components here - must use xmr cmp tab
 */
static int32 cvrt_local_xmr_back_to_xpr(struct gref_t *grp)
{
 int32 cur_xmri;
 struct xmrcmp_t *xmp;
 struct sy_t *syphd, *syptail;
 struct expr_t *locndp;

 /* DBG remove -- */
 if (grp->gr_xmptab == NULL || grp->gr_num_xmps <= 0)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 cur_xmri = 0;
 xmp = grp->gr_xmptab[cur_xmri];

 /* SJM 04-03-11 - now downward local XMR through gen blocks possible */
 /* to look must move past all gen blocks */
 if (xmp->xmp_petyp == XMP_GBLK)
  {
   for (cur_xmri = 1; cur_xmri < grp->gr_num_xmps; cur_xmri++) 
    {
     xmp = grp->gr_xmptab[cur_xmri];
     if (xmp->xmp_petyp != XMP_GBLK) goto end_of_gblk_chain;
    }
   /* must be one xmr cmp after end of gblk chain */
   __misc_terr(__FILE__, __LINE__);
  }

end_of_gblk_chain:
 /* CASE 1: handle xmr's that were guessed to be xmrs but are really either */
 /* errors or guessed wrong and just simple wires - if this is place wire */
 /* cannot go, error will be caught in item (such as task enable) checking */
 /* simple nets in dumpvars argument lists will be seen as XMRs - fixed here */
 syphd = xmp->xmp_syp;
 if (syphd->sytyp == SYM_N)
  {
   /* if this is hierarchical global whose head is wire - error */
   /* i.e. if only 1 component ok */
   if (grp->gr_num_xmps > 1 || !grp->gr_inst_ok)
    {
     __sgferr(754, "hierarchical reference %s first component %s %s illegal",
      grp->gnam, __to_wtnam(__xs, syphd->el.enp), syphd->synam);
     grp->gr_err = TRUE;
     return(TRUE);
    }
   /* must be wire not parameter here at end - param use xmr's illegal */
   if (!chk_xmr_tail_wire(grp, syphd, TRUE))
    { grp->gr_err = TRUE; return(TRUE); }

local_1cmp:
   /* if this is xmr that is 1 component - change back to simple wire */
   /* LOOKATME - why is this needed since removing glb */
   if (syphd->sytyp == SYM_TSK || syphd->sytyp == SYM_F ||
    syphd->sytyp == SYM_LB) grp->targtskp = syphd->el.etskp;
   /* this can be local task call too - not just wire */
   /* AIV 01/20/11 - cannot remove if uprel */
   if (xmp->xmp_upwards_rel)
    {
     return(FALSE);
    }
   grp->gr_gone = TRUE;
   if (xmp->xmp_sel_ndp == NULL)
    {
     /* this frees entire sub expr starting at XMRCOM grp expr. part */  
     locndp = grp->gxndp;
     __free2_xtree(locndp);
     locndp->optyp = ID;
     locndp->ru.grp = NULL;
     locndp->lu.sy = syphd;
    }
   else 
    {
     /* here gxndp is GLB REF with ru ptr to XMR COM (list) */     
     /* here rearranging so can not free */
     /* SJM 03-10-10 - for multi-dim expr's always have first index so */
     /* works because still have next_ndx expr */
     locndp = grp->gxndp;

     locndp->optyp = LSB;
     locndp->ru.grp = NULL;
     locndp->lu.x = grp->glbref->ru.x->lu.x->lu.x;
     locndp->lu.x->optyp = ID;
     locndp->lu.x->lu.sy = syphd;
     locndp->ru.x = grp->glbref->ru.x->lu.x->ru.x; 
    }
   /* global is now removed and do not need to save name since only one comp */
   return(TRUE);
  }
 /* know only way for this to happen is gr loc is scope object */  
 /* if this is 1 component task enable or function call will never be */
 /* seen as global in source reading */
 /* handle in normal global code since it cannot be local */

 /* not a wire - handle case of 1 component scope object */
 /* this is global caused by appearing in scope legal place */
 if (grp->gr_num_xmps == 1) 
  {
   /* can be task/func/named block in which case convert back to local */
   /* also can be udp or gate primitive */
   /* and no need to check for possibility of wrong param will check in */
   /* sys task enable code */
   if (syphd->sytyp == SYM_TSK || syphd->sytyp == SYM_F ||
    syphd->sytyp == SYM_LB)
    {
     /* any scope array that is not array of insts is illegal */
     if (xmp->xmp_sel_ndp != NULL)
      {
local_sel_err:
       __sgferr(690, "hierarchical reference %s illegal - array of %s illegal",
        grp->gnam, __to_sytyp(__xs, syphd->sytyp));
       grp->gr_err = TRUE;
       return(TRUE);
      }
     goto local_1cmp; 
    }

   /* normal 1 component inst. or top mod. global - handled elsewhere */
   return(FALSE);
  }
 /* if in module symbol head instance, then not local */
 if (syphd->sytyp != SYM_TSK && syphd->sytyp != SYM_F &&
  syphd->sytyp != SYM_LB) return(FALSE); 

 /* know this local name expressed with qualified path */
 /* 1st check head to see if also a module name */
 if (__get_sym(xmp->xmp_cmpnam, __modsyms) != NULL)
  {
#ifndef __CVC_RT__
   __sgfwarn(532,
    "local hierarchical name %s path head is also module name - local used",  
    grp->gnam);
#endif
  }
 /* NULL means undecl - error but getting here still means local */
 /* checks for parameter at end of path in here */
 /* getting here means first symbol is is declared in module */  

 /* SJM 03-14-10 - notice since ghd ndp is head must start with in mod */
 /* not next down sym tab */
 /* SJM 03-14-10 - if error this routine emits the message */
 /* SJM 04-03-11 - have a task/func/lb - need to find in containing sym tab */
 /* down sytab */ 
 if ((syptail = find_xmr_inmod_sym(grp, cur_xmri, syphd,
  xmp->xmp_in_sytab)) == NULL)
  {
   grp->gr_err = TRUE;
   return(TRUE);
  }
 
 /* xmp here is start of in mod t/f/lb chain */
 /* after end of instances, local scope object can not be array ref. */
 if (xmp->xmp_sel_ndp != NULL) goto local_sel_err;

 /* know task/func/mod */
 /* notice ...lb.lb as scope is ok - just like local - and >2 elements */
 if (syphd->sytyp == SYM_LB && grp->gr_num_xmps > 2)
  {
   __sgfinform(401, 
    "local hierarchical path %s first component is named block", grp->gnam);
  }
 /* finally convert to ID but save name for printing */
 grp->gr_gone = TRUE;
 /* SJM 03-14-10 - task is tail not head */ 
 grp->targtskp = syptail->el.etskp;

 locndp = grp->gxndp;
 __free2_xtree(locndp);
 /* must set non xmr node tail */
 locndp->lu.sy = syptail;
 locndp->optyp = ID;
 /* re-allocate this so can eventually if needed free global */
 /* notice must not free gnam field in case free globals (shouldn't) */  
 /* FIXME - should for inst. array references need to convert to numbers */
 locndp->ru.qnchp = grp->gnam;
 grp->gnam = NULL;
 locndp->locqualnam = TRUE;
 /* global is now removed */
 return(TRUE);
}

/*
 * MISC MID LEVEL ROUTINES USED IN BUILDING XMR CMP TABS
 */

/*
 * routine to emit informs when found down rel (either inst or t/f/l) in
 * case name also matches something rooted or upward relative
 *
 * SJM 02-20-10 - new routine because not removing local early any more
 */
static void emit_downrel_nam_collision_informs(char *ncmp, struct gref_t *grp)
{
 struct sy_t *modsyp;

 /* search for component in mod syms - needed for rooted and other checking */
 modsyp = __get_sym(ncmp, __modsyms);
 /* need some consistency warning for duplicates - use downward rel inst */
 /* emit inform if can also be rooted */
 if (modsyp != NULL && modsyp->el.emdp->minstnum == 0)
  {
   __sgfinform(464,
    "hierarchical path %s head %s downward relative but also top level module - could be rooted path",
    grp->gnam, ncmp);
  }
 /* emit inform if can be upward rel inst - just check one 0th inst */
 if (fnd_uprel_inst(ncmp, grp->gin_mdp->moditps[0]) != NULL)
  {
   __sgfinform(464,
    "hierarchical path %s head %s downward relative but also upward instance - could be upward relative path",
    grp->gnam, ncmp);
  }
 /* emit inform if can be upward relative instance - just check 0th inst */
 if (modsyp != NULL && fnd_uprel_mod(modsyp, grp->gin_mdp->moditps[0]) != NULL)
  {
   __sgfinform(464,
    "hierarchical path %s head %s downward relative but also upward module type name - could be upward relative path",
    grp->gnam, ncmp);
  }
}

/*
 * routine to initialize an xmr compoent record
 */
static void init_xmrcmp(struct xmrcmp_t *xmp)
{
 xmp->xmp_petyp = XMP_UNKN;
 xmp->xmp_is_rooted = FALSE;
 xmp->xmp_upwards_rel = FALSE;
 xmp->xmp_uprel_msym = NULL;
 xmp->xmp_err = FALSE;
 xmp->xmp_cmpnam = NULL;
 xmp->xmp_alt_cmpnam = NULL;
 xmp->gcmp_ndp = NULL;
 xmp->xmp_sel_ndp = NULL;
 xmp->xmp_syp = NULL;
 xmp->xmp_in_sytab = NULL;
 xmp->xmp_nxtcmp_sytab = NULL;
 xmp->xmp_in_gblkp = NULL;
}

/*
 * check a wire tail to make sure not illegal parameter wire form
 * know symbol is wire to be called 
 */
static int32 chk_xmr_tail_wire(struct gref_t *grp, struct sy_t *tailsyp,
 int32 is_loc1cmp)
{
 struct net_t *np;

 switch ((byte) tailsyp->sytyp) {
  /* these are legal in some places - various kinds of xmrs checked for in */
  /* place of use */
  case SYM_I: case SYM_M: case SYM_LB: case SYM_F: case SYM_TSK: break;
  case SYM_N:
   /* this if fixup of guessed wrong because sys. task special arg xmr */
   /* that is really net */
   np = tailsyp->el.enp;
   /* if resolving defparam lhs xmr, parameter ok and required but */
   /* if not error caught later */
   if (grp->gr_defparam) break;

   if (!is_loc1cmp && np->n_isaparam)
    {
     __sgferr(3451,
      "hierarchical reference %s tail variable %s cannot be a parameter",
      grp->gnam, np->nsym->synam);
     return(FALSE);
    }
   break;
  default:
   __sgferr(3453, "hierarchical reference %s tail %s cannot be a %s",
    grp->gnam, tailsyp->synam, __to_sytyp(__xs, tailsyp->sytyp));
  }
 return(TRUE);
}

/*
 * for every instance of gin module type, find uprel dest and check to
 * make sure destination the same
 *
 * also checks each instance's uprel
 */
static int32 chk_all_uprels_same(struct gref_t *grp, struct sy_t *modsyp,
 char *ncmp, struct expr_t *ghd_ndp)
{
 int32 ii;
 struct itree_t *in_itp, *itp2;
 int32 uprel_typ, got_one, fnd_ii, sav_ecnt; 
 struct sy_t *uprel_syp, *scope_syp, *syp;
 struct mod_t *imdp;

 uprel_typ = -1;
 uprel_syp = NULL;
 fnd_ii = -1;
 got_one = FALSE;
 sav_ecnt = __pv_err_cnt;
 for (ii = 0; ii < grp->gin_mdp->flatinum; ii++)
  {
   in_itp = grp->gin_mdp->moditps[ii];
   /* upward relative instance name - symbol is module not inst */
   if ((itp2 = fnd_uprel_inst(ncmp, in_itp)) != NULL)
    {
     syp = itp2->itip->isym;
     if (!got_one)
      { uprel_typ = SYM_I; uprel_syp = syp; got_one = TRUE; fnd_ii = ii; }
     else
      {
       if (uprel_typ != SYM_I || syp != uprel_syp) 
        {
        __sgferr(939,
         "rooted or upward relative instance reference %s for instance %s differs from upward reference for instance %s",
         grp->gnam, __msg2_blditree(__xs, in_itp),
         __msg2_blditree(__xs2, grp->gin_mdp->moditps[fnd_ii]));
        }
      }
     continue; 
    }

   /* upward relative type name */
   if (modsyp != NULL)
    { 
     /* this returns T on success */
     if (fnd_uprel_mod(modsyp, in_itp) != NULL)
      {
       if (!got_one)
        { uprel_typ = SYM_M; uprel_syp = modsyp; got_one = TRUE; fnd_ii = ii; }
       else
        {
         if (uprel_typ != SYM_M || modsyp != uprel_syp) 
          {
           __sgferr(3402,
           "upward relative module type reference %s for instance %s differs from upward reference for instance %s",
           grp->gnam, __msg2_blditree(__xs, in_itp),
           __msg2_blditree(__xs2, grp->gin_mdp->moditps[fnd_ii]));
          }
        }
       continue; 
      }
    }

   /* if only one component, look for upward somwhere task/func */
   if (ghd_ndp->ru.x == NULL)
    {
     if ((imdp = fnd_uprel_tskfunc(&scope_syp, ncmp, in_itp)) != NULL)
      { 
       if (!got_one)
        {
         uprel_typ = SYM_TSK;
         uprel_syp = scope_syp;
         got_one = TRUE;
         fnd_ii = ii;
        }
       else
        {
         if (uprel_typ != SYM_TSK || scope_syp != uprel_syp) 
          {
           __sgferr(3402,
           "upward relative task/func/named block reference %s for instance %s differs from upward reference for instance %s",
           grp->gnam, __msg2_blditree(__xs, in_itp),
           __msg2_blditree(__xs2, grp->gin_mdp->moditps[fnd_ii]));
          }
        }
       continue; 
      }
    } 
   __sgferr(757,
    "rooted or upward relative hierarchical reference %s first component %s not found for instance %s - illegal symbol or undeclared",
    grp->gnam, ncmp, __msg2_blditree(__xs, in_itp));
  }
 if (__pv_err_cnt > sav_ecnt) return(FALSE);
 return(TRUE);
}

/*
 * match upward relative instance - if found returns itree loc of inst
 */
static struct itree_t *fnd_uprel_inst(char *ncmp, struct itree_t *in_itp)
{
 struct itree_t *up_itp;
 struct inst_t *ip;

 for (up_itp = in_itp; up_itp != NULL;)
  { 
   ip = up_itp->itip;
   /* know insts in split off module types have unchanged inst name */
   /* FIXME - should compare inst exprs not just iarr element name */
   if (strcmp(ncmp, ip->isym->synam) == 0) return(up_itp);
   up_itp = up_itp->up_it;
  }
 return(NULL);
}

/*
 * match upward relative instance from mod name - if found returns itree
 * loc of inst with match mod name (from mod sym here)
 */
static struct itree_t *fnd_uprel_mod(struct sy_t *modsyp,
 struct itree_t *in_itp)
{
 struct itree_t *up_itp;
 struct mod_t *up_mdp, *up_mast_mdp, *imdp, *mast_imdp;
 struct inst_t *ip;

 up_mdp = modsyp->el.emdp;
 up_mast_mdp = __get_mast_mdp(up_mdp);
 for (up_itp = in_itp; up_itp != NULL;)
  {
   /* must match master mod type */
   ip = up_itp->itip;
   imdp = ip->imsym->el.emdp;
   mast_imdp = __get_mast_mdp(imdp);
   if (mast_imdp == up_mast_mdp) return(up_itp);
   up_itp = up_itp->up_it;
  }
 return(FALSE);
}

/*
 * find an upward relative task/func/named block anywhere in uprel inst
 * if found return module type and set scope syp 
 */
static struct mod_t *fnd_uprel_tskfunc(struct sy_t **scope_syp, char *ncmp,
 struct itree_t *in_itp)
{
 struct itree_t *up_itp;
 struct sy_t *tskfunc_syp; 
 struct mod_t *imdp;

 for (up_itp = in_itp; up_itp != NULL;)
  { 
   imdp = up_itp->itip->imsym->el.emdp;
   if ((tskfunc_syp = fnd_tskfunc_inscope(ncmp, imdp->msymtab)) != NULL)
    {
     *scope_syp = tskfunc_syp;
     return(imdp);
    }
   up_itp = up_itp->up_it;
  }
 return(NULL);
}

/*
 * find a scope symbol inside one symbol table scope level    
 */
static struct sy_t *fnd_tskfunc_inscope(char *ncmp, struct symtab_t *scope_sytp)
{
 struct symtab_t *sytp;
 struct sy_t *match_syp;

 for (sytp = scope_sytp->sytofs; sytp != NULL; sytp = sytp->sytsib)  
  {
   if (strcmp(sytp->sypofsyt->synam, ncmp) == 0) return(sytp->sypofsyt);
   if ((match_syp = fnd_tskfunc_inscope(ncmp, sytp)) != NULL)
    return(match_syp);
  }
 return(NULL);
}

/*
 * find in module symbol - know previous symbol selected module  
 * or local task/block/function hierarchical name root
 *
 * end of path here can be scope named block/func/task/mod/inst etc.
 * this must also return (set) symbol table where last symbol declared
 *
 * SJM 03-14-10 - pass current sym tab, but no longer need to return since
 * this is local gref - just need end symbol to convert back
 */
static struct sy_t *find_dfp_inmod_sym(struct gref_t *grp,
 struct expr_t *gcmp_ndp, struct sy_t *syp, struct symtab_t *cur_sytp)
{
 struct expr_t *ndp;
 struct symtab_t *sytp;

 sytp = cur_sytp;
 for (;;)
  {
   if (gcmp_ndp->lu.x->optyp == XMRID) ndp = gcmp_ndp->lu.x;
   else if (gcmp_ndp->lu.x->optyp == LSB)
    {
     __sgferr(694,
     "hierarchical path %s select of %s component illegal - not instance array",
      grp->gnam, __to_sytyp(__xs, syp->sytyp));
     return(NULL);
    }
   else { __case_terr(__FILE__, __LINE__); return(FALSE); }

   syp = __zget_sym(ndp->ru.qnchp, sytp->stsyms, sytp->numsyms);
   if (gcmp_ndp->ru.x == NULL) break;

   if (syp == NULL)
    {
     /* did not find next path component */
     __sgferr(763, "hierarchical path %s component %s undeclared", grp->gnam,
      ndp->ru.qnchp);
     return(NULL);
    } 
   /* SJM 10/07/06 - also legal for local XMR reference nets in tasks and */
   /* functions declared within the current module (i.e. t.r) */
   if (syp->sytyp != SYM_LB && syp->sytyp != SYM_TSK && syp->sytyp != SYM_F)
    {
     __sgferr(764, 
      "hierarchical path %s internal component %s type %s instead of expected named block",
      grp->gnam, ndp->ru.qnchp, __to_sytyp(__xs, syp->sytyp));
     return(NULL);
    }
   sytp = syp->el.etskp->tsksymtab; 
   gcmp_ndp = gcmp_ndp->ru.x;
  }
 /* syp is tail (actual variable), if declared replace - checking later */
 if (syp == NULL)
  {
   __sgferr(765,
    "internal hierarchical path %s part last component %s undeclared",
    grp->gnam, ndp->ru.qnchp);
   return(NULL);
  }
 if (!chk_xmr_tail_wire(grp, syp, FALSE)) return(NULL);
 return(syp);
}

/*
 * find in module symbol - know previous symbol selected module  
 * or local task/block/function hierarchical name root
 *
 * SJM 04-03-11 - version for xmr's with post gen names and must use
 * xmrcmps only
 *
 * end of path here can be scope named block/func/task/mod/inst etc.
 * this must also return (set) symbol table where last symbol declared
 *
 * SJM 03-14-10 - pass current sym tab, but no longer need to return since
 * this is local gref - just need end symbol to convert back
 */
static struct sy_t *find_xmr_inmod_sym(struct gref_t *grp, int32 cur_xmri,
 struct sy_t *syp, struct symtab_t *cur_sytp)
{
 int32 in_gblk;
 struct expr_t *ndp;
 struct xmrcmp_t *xmp;
 struct symtab_t *sytp;

 sytp = cur_sytp;
 /* SJM 04-03-11- if containing block (scope) is a gen blk need to use */
 /* passed symbol to to find */ 
 if (cur_xmri > 0 && grp->gr_xmptab[cur_xmri - 1]->xmp_petyp == XMP_GBLK)
  in_gblk = TRUE;
 else in_gblk = FALSE; 

 /* SJM 04-03-11 - was wrongly not moving sytp down and loop was wrong */
 for (;;)
  {
   xmp = grp->gr_xmptab[cur_xmri];

   /* will never see gblk from xmr cmp here, because only can be prefixes */
   /* that are skipped by here */
   /* DBG remove */ 
   if (xmp->xmp_petyp == XMP_GBLK) __misc_terr(__FILE__, __LINE__);
   /* --- */

   if (xmp->xmp_sel_ndp != NULL)
    {
     __sgferr(3444,
     "hierarchical path %s select of %s component illegal - not instance array",
      grp->gnam, __to_sytyp(__xs, syp->sytyp));
     return(NULL);
    }
   ndp = xmp->gcmp_ndp;
   /* first time if in genblk look up using passed symbol name from then on */
   /* or if not in gen blk, use the xmr cmp tab nam */
   if (in_gblk)
    {
     syp = __zget_sym(syp->synam, sytp->stsyms, sytp->numsyms);
     in_gblk = FALSE;
    }
   else syp = __zget_sym(xmp->xmp_cmpnam, sytp->stsyms, sytp->numsyms);

   if (cur_xmri + 1 >= grp->gr_num_xmps) break; 

   if (syp == NULL)
    {
     /* did not find next path component */
     __sgferr(3446, "hierarchical path %s component %s undeclared", grp->gnam,
      xmp->xmp_cmpnam);
     return(NULL);
    } 
   /* SJM 10/07/06 - also legal for local XMR reference nets in tasks and */
   /* functions declared within the current module (i.e. t.r) */
   if (syp->sytyp != SYM_LB && syp->sytyp != SYM_TSK && syp->sytyp != SYM_F)
    {
     __sgferr(3448, 
      "hierarchical path %s internal component %s type %s instead of expected named block",
      grp->gnam, xmp->xmp_cmpnam, __to_sytyp(__xs, syp->sytyp));
     return(NULL);
    }
   sytp = syp->el.etskp->tsksymtab; 
   cur_xmri++;
  }

 /* syp is tail (actual variable), if declared replace - checking later */
 if (syp == NULL)
  {
   __sgferr(3449,
    "internal hierarchical path %s part last component %s undeclared",
    grp->gnam, xmp->xmp_cmpnam);
   return(NULL);
  }
 if (!chk_xmr_tail_wire(grp, syp, FALSE)) return(NULL);
 return(syp);
}

/*
 * check global selects 
 *
 * error if select of non inst array and non select of inst. array
 * this is called during global input, can not check select exprs
 */
static int32 chk_glb_inst_sels(struct gref_t *grp)
{
 int32 gi, good;
 struct sy_t *syp, *up_syp;
 struct inst_t *ip;
 struct mod_t *mdp, *up_mdp;

 for (good = TRUE, up_syp = NULL, gi = 0; gi <= __last_gsc; gi++)
  {
   syp = __glbsycmps[gi];
   if (syp->sytyp != SYM_I)
    {
     if (__glbxcmps[gi] != NULL)
      {
       __sgferr(695,
        "hierarchical path %s illegal select of %s symbol - never arrayed",
        grp->gnam, __to_sytyp(__xs, syp->sytyp));
       good = FALSE;
      }
     continue;
    }
   /* know symbol is instance */
   /* if inst select but not array of instances, select illegal */
   ip = syp->el.eip;
   mdp = ip->imsym->el.emdp;
   /* know this component inst, need to access up module */
   if (gi == 0)
    {
     /* first component instance mean down relative */
     /* DBG remove -- */
     if (grp->is_rooted) __misc_terr(__FILE__, __LINE__);
     /* --- */
     up_mdp = grp->gin_mdp;
    }
   else
    {
     up_syp = __glbsycmps[gi - 1];
     if (up_syp->sytyp == SYM_I) up_mdp = up_syp->el.eip->imsym->el.emdp;
     else if (up_syp->sytyp == SYM_M) up_mdp = up_syp->el.emdp;
     else { up_mdp = NULL;__case_terr(__FILE__, __LINE__); }
    }
   if (ip->i_giap == NULL)
    {
     if (__glbxcmps[gi] == NULL) continue;

     __sgferr(696,
      "hierarchical path %s select illegal for non vectored instance %s (type %s)",
      grp->gnam, ip->isym->synam, mdp->msym->synam);
     good = FALSE;
     continue;
    }
   /* final case vectored instance - select required */ 
   if (__glbxcmps[gi] != NULL) continue;
   __sgferr(697,
    "hierarchical path %s missing required select of vectored instance %s (type %s)",
    grp->gnam, ip->isym->synam, mdp->msym->synam);
   good = FALSE;
  }
 return(good);
}

/*
 * ROUTINES TO FREE GLOBAL DATA STRUCTURES
 */

/*
 * free a defparam
 * may want to keep defparams and global for debugging
 * but latest value of parameter is what is needed not defparam
 *
 * global marked as gone so will be freed later
 *
 * SJM 09-03-11 - fixed so free all fields 
 */
extern void __free_1dfparam(struct dfparam_t *dfpp)
{
 if (dfpp->last_dfpi > -1 && dfpp->dfpiis != NULL)
  {
   /* DBG remove --
   if (__debug_flg) dbg_dmp_dfpiis(dfpp, "in free 1 defparam");
   --- */

   __my_free(dfpp->dfpiis, (dfpp->last_dfpi + 1)*sizeof(int32));
  }

 if (dfpp->dfpxrhs != NULL)
  {
   __free_xtree(dfpp->dfpxrhs);
  }
 if (dfpp->dfpxlhs != NULL)
  {
   __free_xtree(dfpp->dfpxlhs);
  }

 /* SJM 09-03-11 - free the one associated gref with the defp - not in tab */
 if (dfpp->dfp_grp != NULL)
  {
   __free_1glb_flds(dfpp->dfp_grp);
   __my_free(dfpp->dfp_grp, sizeof(struct gref_t)); 
   dfpp->dfp_grp = NULL;
  }
 if (dfpp->gdfpnam != NULL)
  {
   __my_free(dfpp->gdfpnam, strlen(dfpp->gdfpnam) + 1);
  }

 /* notice cannot free rhs since moved to parameter value rhs */
 /* if error, will stop so no need to free */
 __my_free(dfpp, sizeof(struct dfparam_t));
}

/*
 * free globals marked to be freed - mostly for defparam tmp globals
 *
 * must remove gone and err from grtab and fix up gxndp ptrs or
 * will process with empty guts and can't skip steps if only defparams
 *
 * SJM 08-29-11 - now only rem local and errors from main (not defp) gref tab
 */
static void free_gone_glbs(void)
{ 
 int32 gri, ngri;
 struct gref_t *grp;
 struct mod_t *mdp;
 struct gref_t *ngrtab;
 int32 ngrnum;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mgrnum == 0) continue;

   __push_wrkitstk(mdp, 0);

   /* first rebuild the normal xmr gr tab remoing gones and rebuilding */
   grp = &(__inst_mod->mgrtab[0]);
   /* first count remaining */
   for (ngrnum = gri = 0; gri < __inst_mod->mgrnum; grp++, gri++) 
    {
     /* if global gone or error will not get counted at all */
     if (grp->gr_err || grp->gr_gone) continue; 
     ngrnum++;
    }
   /* nothing to remove */
   if (ngrnum == __inst_mod->mgrnum) goto nxt_mod;
   /* all removed */
   if (ngrnum == 0)
    {
     __my_free(__inst_mod->mgrtab, __inst_mod->mgrnum*sizeof(struct gref_t));
     __inst_mod->mgrtab = NULL;
     __inst_mod->mgrnum = 0;
     goto nxt_mod;
    }

   ngrtab = (struct gref_t *) __my_malloc(ngrnum*sizeof(struct gref_t));
   grp = &(__inst_mod->mgrtab[0]);
   for (ngri = gri = 0; gri < __inst_mod->mgrnum; grp++, gri++) 
    {
     /* this frees contents of global but left in table */
     if (grp->gr_err || grp->gr_gone) { __free_1glb_flds(grp); continue; }

     ngrtab[ngri] = *grp; 
     ngrtab[ngri].gxndp->ru.grp = &(ngrtab[ngri]);
     ngri++;
    }
   __my_free(__inst_mod->mgrtab, __inst_mod->mgrnum*sizeof(struct gref_t));
   __inst_mod->mgrtab = ngrtab;
   __inst_mod->mgrnum = ngrnum;

nxt_mod:
   /* then repeat rebuild for mod defparam gref tab */
   __pop_wrkitstk();
  }
}

/*
 * allocate and fill new gref table 
 *
 * also always fixes up r_u ptrs from expr. to to newly alloced global
 */
extern struct gref_t *__alloc_grtab(struct gref_t *oldgrtab, int32 grnum)
{
 int32 gri;
 struct gref_t *grp; 
 struct gref_t *ngrtab;

 /* DBG remove -- */
 if (grnum <= 0) __arg_terr(__FILE__, __LINE__);
 /* --- */
 ngrtab = (struct gref_t *) __my_malloc(grnum*sizeof(struct gref_t));
 memcpy(ngrtab, oldgrtab, grnum*sizeof(struct gref_t));

 /* pointer from expr nodes need to be fixed to point to new addr */
 grp = &(ngrtab[0]);
 for (gri = 0; gri < grnum; grp++, gri++) grp->gxndp->ru.grp = grp; 
 return(ngrtab);
}

/*
 * free 1 global's fields 
 *
 * caller must free table containing this global if needed
 * LOOKATME - what if gnam in name table (think never calling this then)? 
 *
 * SJM 09-04-11 - added freeing of glbrf expr - it is the GLBREF list
 */
extern void __free_1glb_flds(struct gref_t *grp)
{
 /* if using this for local qualifed name will be set to nil */
 if (grp->gnam != NULL) __my_free(grp->gnam, strlen(grp->gnam + 1));
 grp->gnam = NULL;
 /* gxndp is ptr to src expr - must not free */
 /* also free glb ref expr - always in malloced memory here */
 __free_xtree(grp->glbref);

 /* SJM 03-10-10 - now also free xmr cmp table if built before freeing */
 /* if have xmr cmp record also free those */
 if (grp->gr_xmptab != NULL) free_xmrcmptab(grp);

 /* only sized targu is upwards rel list - may not have been alloced yet */
 if (grp->upwards_rel && grp->targu.uprel_itps != NULL)
  {
   __my_free(grp->targu.uprel_itps,
    grp->gin_mdp->flatinum*sizeof(struct itree_t *));
  } 
 if (grp->grcmps != NULL)
  {
   __my_free(grp->grcmps, (grp->last_gri + 1)*sizeof(struct sy_t *));
   grp->grcmps = NULL;
  }
 if (grp->grxcmps != NULL)
  {
   __my_free(grp->grxcmps, (grp->last_gri + 1)*sizeof(struct expr_t *));
   grp->grxcmps = NULL;
  }
}

/*
 * routine to free an xmrcmp tab - needed also for fixup nl gen loop
 * only called if grefs xmrcmptab non nil
 *
 * SJM 03-13-10 - xmrcmptab is new algorithm for handling gen blks in XMRs
 */
static void free_xmrcmptab(struct gref_t *grp)
{
 int32 xmri;
 struct xmrcmp_t *xmp;

 /* DBG remove -- */
 if (grp->gr_num_xmps <= 0) __misc_terr(__FILE__, __LINE__);
 /* -- */
 for (xmri = 0; xmri < grp->gr_num_xmps; xmri++)
  {
   /* xmr cmp tab is table of ptr to xmr cmp elements */
   xmp = grp->gr_xmptab[xmri];
   free_1xmrcmp(xmp);
   grp->gr_xmptab[xmri] = NULL;
  }
 __my_free(grp->gr_xmptab, grp->gr_num_xmps*sizeof(struct xmrcmp_t *));
 grp->gr_xmptab = NULL;
 grp->gr_num_xmps = 0;
}

/*
 * routine to free one xmrcmp elment
 */
static void free_1xmrcmp(struct xmrcmp_t *xmp)
{
 if (xmp->xmp_cmpnam != NULL)
  {
   __my_free(xmp->xmp_cmpnam, strlen(xmp->xmp_cmpnam) + 1);
   xmp->xmp_cmpnam = NULL;
  }
 if (xmp->xmp_cmpnam != NULL)
  {
   __my_free(xmp->xmp_alt_cmpnam, strlen(xmp->xmp_alt_cmpnam) + 1);
   xmp->xmp_alt_cmpnam = NULL;
  }
 /* expr's subtree pointed to here, freed when free gref expr */
 xmp->gcmp_ndp = NULL;
 xmp->xmp_sel_ndp = NULL;
 /* sym is not freed */
 xmp->xmp_syp = NULL;
 xmp->xmp_in_sytab = NULL;
 xmp->xmp_nxtcmp_sytab = NULL;
 xmp->xmp_in_gblkp = NULL;
 __my_free(xmp, sizeof(struct xmrcmp_t));
}

/*
 * ROUTINES TO DO POUND PARAM SPLITTING
 */

/*
 * work form bottom up marking all instances that need to be split
 * and all params that are width determining or indirect width determining 
 */
static void mark_poundparam_splitinsts(void)
{
 int32 ii, mlevel, pi;
 int32 split_inst;
 struct mod_t *mdp;
 int32 giawid;
 struct inst_t *ip;
 struct mod_t *imdp;
 struct expr_t *pxp;
 struct net_t *modnp;

 /* bottom modules which do not instantiate anything special case */
 for (mdp = __mdlevhdr[0]; mdp != NULL; mdp = mdp->mlevnxt)
  {
   /* for bottom pound params, if only one flat instance - nothing to do */
   /* because if only one flat instance then know anything instantiating */
   /* also only one flat inst */
   if (mdp->flatinum == 1) continue;

   __push_wrkitstk(mdp, 0);
   /* this also set mod has width determining bit */
   if (!mdp->mwiddetdone)
    { __mark_widdet_params(mdp); mdp->mwiddetdone = TRUE; }
   __pop_wrkitstk();
  }

 /* work upward in levelized dag marking width determining params and */ 
 /* instance that need to be split */
 __pndparam_splits = FALSE;
 for (mlevel = 1; mlevel <= __dagmaxdist; mlevel++)
  {
   for (mdp = __mdlevhdr[mlevel]; mdp != NULL; mdp = mdp->mlevnxt)
    {
     __push_wrkitstk(mdp, 0);

     /* width determining needs module context - always set here */
     /* if has width determining, becomes probable if ever instantiated */
     /* if only 1 inst in design no need to mark width determining */
     if (mdp->flatinum > 1)
      {
       if (!mdp->mwiddetdone)
        { __mark_widdet_params(mdp); mdp->mwiddetdone = TRUE; }
      }

     /* even if only one inst of mod, must still try to split insts of mod in*/ 

     /* for every instance in module, see if need to split */
     for (ii = 0; ii < __inst_mod->minum; ii++)
      {
       /* if instance in mod is inst array (first) never split and do not */
       /* even check other expanded from in source instance array */
       /* pound param splitting in inst arrays illegal */
       /* LOOKATME - is error emitted somewhere? */
       /* for contained insts that came from mi arrays, no pnd param split */
       ip = &(__inst_mod->minsts[ii]);
       if (ip->i_giap != NULL)
        {
         giawid = __get_gia_wide(ip->i_giap);
         /* always inc by one in for loop above */
         ii += (giawid - 1);
         continue;
        }

       ip = &(__inst_mod->minsts[ii]);
       if (ip->ipxprtab == NULL) continue;

       /* LOOKATME - think these not used */
       __sfnam_ind = ip->isym->syfnam_ind;
       __slin_cnt = ip->isym->sylin_cnt;

       /* imdp is module type of instance that has pound param */
       imdp = ip->imsym->el.emdp;

       /* if one inst never split - even if in later splitting by here */
       /* spliting would result in 0 insts, mark here but stop when split */
       if (imdp->flatinum == 1)
        {
         if (__debug_flg)
          {
           __dbg_msg("++ # form inst. %s(%s) not split - only one instance\n",
           ip->isym->synam, imdp->msym->synam);
          } 
         continue;
        }
       /* know contained module has all width determining params set */
       /* if no width determining and no indir width determining, done */
       if (!imdp->mhas_widthdet && !imdp->mhas_indir_widdet)
        {
         if (__debug_flg)
          {
           __dbg_msg(
            "++ # form inst. %s(%s) not split - no params in ranges\n",
            ip->isym->synam, imdp->msym->synam);
          } 
         continue;
        }

       split_inst = FALSE;
       /* go through defined params in one down mod */
       for (pi = 0; pi < imdp->mprmnum; pi++)
        {
         pxp = ip->ipxprtab[pi];
         /* explicit form this one unused or short list */
         if (pxp == NULL) continue;

         modnp = &(imdp->mprms[pi]);
         /* if down mod has width determining, but none of the width */
         /* determining passed down to this inst. as pound param, no split */
         if (modnp->nu.ct->n_widthdet || modnp->nu.ct->n_indir_widthdet)
          {
           /* set indirect width determining */

           /* if no up expr params set as indirect width determining, do not */
           /* need to split, but other source locs insts of type may split */
           /* returns T if any set */
           if (indir_widthdet_markparam(pxp)) split_inst = TRUE;
          }

        }
       /* if no width determining and no indir width determining, done */
       if (!split_inst)
        {
         if (__debug_flg)
          {
           __dbg_msg(
            "++ # form inst. %s(%s) not split - no range # params\n",
            ip->isym->synam, imdp->msym->synam);
          } 
        }
       ip->i_pnddefsplit = TRUE; 
      }
     __pop_wrkitstk();
    }
  }
}

/*
 * set the indirect width determining bit for any wire up pound param expr
 * return T if any params in this up expr else F
 */
static int32 indir_widthdet_markparam(struct expr_t *xp)
{
 int32 rv, rv2, rv3;
 struct net_t *np;
 struct expr_t *xp2;

 rv = rv2 = FALSE;
 if (__isleaf(xp))
  {
   if (xp->optyp == ID && xp->lu.sy->sytyp == SYM_N)
    {
     np = xp->lu.sy->el.enp; 
     if (np->n_isaparam)
      {
       /* if already width determining, can't be indir width determining */
       if (!np->nu.ct->n_widthdet)
        {
         np->nu.ct->n_indir_widthdet = TRUE;
         __inst_mod->mhas_indir_widdet = TRUE;
         rv = TRUE;
        }
      }
    }
   return(rv);
  }

 for (rv3 = FALSE, xp2 = xp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   if (indir_widthdet_markparam(xp2)) rv3 = TRUE;
  }

 if (xp->lu.x != NULL) rv = indir_widthdet_markparam(xp->lu.x);
 if (xp->ru.x != NULL) rv2 = indir_widthdet_markparam(xp->ru.x);
 if (rv || rv2 || rv3) return(TRUE);
 return(FALSE);
}

/*
 * work from top down splitting off static instance locations for
 * pound parameters that are width determining or indirect width determining
 * such instances are already marked
 *
 * splitting here may produce modules with more than 1 flat instance
 */
static void do_poundparam_splitting(void)
{
 int32 ii, mlevel;
 struct mod_t *mdp;
 int32 giawid;
 struct inst_t *ip;
 struct mod_t *imdp;

 __pndparam_splits = FALSE;
 /* work from top (mod) down - since need fixed no pound param start */
 /* LOOKATME - wonder if bottom up works - think not */
 for (mlevel = __dagmaxdist; mlevel >= 1; mlevel--)
  {
   /* SJM 03/16/04 - notice processing from one up and splitting (if needed) */
   /* contained insts - therefore mlevel of md lev hdr list not chged */
   /* inside this loop - mlevel one less may use update list */
   for (mdp = __mdlevhdr[mlevel]; mdp != NULL; mdp = mdp->mlevnxt)
    {
     __push_wrkitstk(mdp, 0);
 
     /* do all splitting from pound params - also check but cannot set */
     /* for every instance in module */
     for (ii = 0; ii < __inst_mod->minum; ii++)
      {
       /* if instance in mod is inst array (first) never split and do not */
       /* even check other expanded from in source instance array */
       /* for contained insts that came from mi arrays, no pnd param split */
       ip = &(__inst_mod->minsts[ii]);
       if (ip->i_giap != NULL)
        {
         giawid = __get_gia_wide(ip->i_giap);
         /* always inc by one in for loop above */
         ii += (giawid - 1);
         continue;
        }

       ip = &(__inst_mod->minsts[ii]);
       if (!ip->i_pnddefsplit) continue;
       
       /* when splitting marked, marked for all but do not split last */
       /* when splitting would result in nonsense 0 insts */

       imdp = ip->imsym->el.emdp;
       if (imdp->flatinum == 1 || imdp->flatinum == __inst_mod->flatinum)
        {
         if (__debug_flg)
          {
           __dbg_msg(
            "++ # form inst. %s(%s) not split - last %d splittable insts\n",
            ip->isym->synam, ip->imsym->synam, __inst_mod->flatinum);
          } 
         continue;
        }

       /* DBG remove -- */
       if (__inst_mod->flatinum == 0) __misc_terr(__FILE__, __LINE__);
       /* --- */

       if (__debug_flg)
        {
         __dbg_msg(
          "++ # form inst. %s(%s) split (%d new instances)\n",
          ip->isym->synam, imdp->msym->synam, __inst_mod->flatinum);
        } 

       __sfnam_ind = ip->isym->syfnam_ind;
       __slin_cnt = ip->isym->sylin_cnt;

       /* imdp is module type of instance that has pound param */
       /* SJM 03/16/04 - notice mlevel is one above imdp being split off */
       split_upd_mod(imdp, ip, mlevel, TRUE); 
       /* AIV 07/26/11 - this needs to be set again after split not before */
       /* AIV 10/16/10 - set the level for searching for duplicate module */
       /* paramter spliting */
       mdp->mlevel = mlevel;
      }
     __pop_wrkitstk();
    }
  }
}

/*
 * split (copy) module from pound params or arrays of gate/insts where
 * assumes tmp itree loc set and sets/uses various other globals
 * 
 * called after conditions for split determined to be true
 * does copy and update the static (in source text) instance d.s.
 */
static void split_upd_mod(struct mod_t *imdp, struct inst_t *ip, int32 mlevel,
 int32 is_param_split) 
{
 struct mod_t *ipmdp, *sav_inst_mod;

 /* this is one up module containing instance for which new module split off */
 sav_inst_mod = __inst_mod; 
 /* if not parameter splitting (array of inst) do not search for duplicate */
 /* #param values */

 if (!is_param_split)
  {
   __do_mdsplit(imdp);
  }
 /* AIV 10/16/10 - search for duplicate pound param values - only split */
 /* to one module if possible */
 else if (find_split_mod(imdp, ip, mlevel) == NULL) 
  {
   __do_mdsplit(imdp);
   /* save the split instance */
   __inst_mod->inst_split = ip;
   /* if split had to split module list */
   if (imdp->split_hd == NULL)
    {
     imdp->split_hd = __inst_mod;
     imdp->split_tail = __inst_mod;
    }
   else
    {
     imdp->split_tail->split_nxt = __inst_mod;
     imdp->split_tail = __inst_mod;
    }
  }
 else 
  {
   /* if module with the same #(const, ) values are passed use the */
   /* first module it was split into - adjustments similar to below */
   ipmdp = __inst_mod;
   ip->imsym = ipmdp->msym;
   ipmdp->flatinum += sav_inst_mod->flatinum; 
   ipmdp->mpndspltmst = imdp;
   imdp->flatinum -= sav_inst_mod->flatinum;
   if (imdp->flatinum > 1) imdp->minstnum = 2;

   __inst_mod = sav_inst_mod;
   return;
  }
 __pndparam_splits = TRUE;

 /* after here new (in __inst_mod) set to new, and old set to old - 1 */ 
 /* ipmdp is newly split off, sav cur mod if old split from */
 ipmdp = __inst_mod;
 /* adjust type of this instance */
 ip->imsym = ipmdp->msym;
 /* adjust inst numbers (spilt set new number to 1 and old to old - 1) */
 ipmdp->flatinum = sav_inst_mod->flatinum; 
 if (ipmdp->flatinum > 1) ipmdp->minstnum = 2;

 /* imdp is old, reduce by number of times containing module instantiated */
 imdp->flatinum -= sav_inst_mod->flatinum;
 /* during splitting reduced count by one too many - adjust back */
 imdp->flatinum++;
 /* SJM 02/17/00 - must adjust new split off module to have right inst */
 /* num */
 if (imdp->flatinum > 1) imdp->minstnum = 2;

 /* now adjust so both are masters that can be split from */
 /* this may cause lots of $$[num] prefixes */
 /* DBG remove --- */
 if (imdp->msplit) __misc_terr(__FILE__, __LINE__);
 /* --- */
 ipmdp->msplit = FALSE;
 /* if split off others from new, add new prefix starting at 1 */
 ipmdp->mversno = 0;
 imdp->mhassplit = FALSE;
 /* this must remain a defparm master since master applies only to */
 /* pealing off 1 instance paths from defparams */
 ipmdp->mspltmst = NULL;
 ipmdp->mpndsplit = TRUE;
 /* but need to record master of pound split off */
 ipmdp->mpndspltmst = imdp;

 /* SJM 03/16/04 - passed mlevel is one higher than imdp being split */  
 /* must add new split to dag list but for one down that is processed later */
 /* but must incrementally update the md lev hdr list during splitting */
 ipmdp->mlevnxt = __mdlevhdr[mlevel - 1];
 __mdlevhdr[mlevel - 1] = ipmdp;
 /* put back current module to up module instances in */
 __inst_mod = sav_inst_mod;
 return;
}

/*
 * AIV 10/16/10 - now searching for splitting of modules which have been
 * split.  There is no reason to split duplicate modules with constant
 * #(values).  The key is that the values are constant so no need to 
 * adjust down parameter values and that mlevel is <=.
 * search for these - which are common and previously split into two mods
 * m1 #2 i1();
 * m1 #2 i2();
 */
static struct mod_t *find_split_mod(struct mod_t *imdp, struct inst_t *new_ip,
 int32 mlevel) 
{
 struct mod_t *mdp;
 struct expr_t *split_pxp, *new_pxp;
 struct xstk_t *xsp, *xsp2;
 struct inst_t *split_ip;
 int32 wlen, pi, is_match;

 /* SJM 03-22-11 - adding new (will be undocumented) option to turn off */
 /* no splitting for params with identical params - maybe not needed */
 if (__same_param_must_split) return(NULL);

 /* AIV 03/14/11 - if generated instance skip these code */
 /* was running into problems - just split all generated instances */
 if (imdp->m_maybe_gened) return(NULL);

 /* AIV 08/24/11 - added another flag which checks for defparam and */
 /* modules which are instantiated below gened modules */
 if (imdp->m_no_param_match) return(NULL);

 /* AIV 02/27/12 - if the number of instances is large - just split it */
 /* this keeps the compile time/memory down */
 if (imdp->flatinum > NO_SPLIT_INST_MAX) return(NULL);
 
 /* search already split modules */
 for (mdp = imdp->split_hd; mdp != NULL; mdp = mdp->split_nxt)
  {
   split_ip = mdp->inst_split;
   /* assume it is a match */
   is_match = TRUE;
   /* the value for  __dagmaxdist cannot be passed already */
   if (mlevel <= mdp->mlevel) continue;
   for (pi = 0; pi < mdp->mprmnum; pi++)
    {
     /* if one value isn't set must split to a new value */
     if (split_ip->ipxprtab == NULL || new_ip->ipxprtab == NULL) 
      { 
       is_match = FALSE; 
       break; 
      }
     split_pxp = split_ip->ipxprtab[pi];
     new_pxp = new_ip->ipxprtab[pi];
     /* explicit form this one unused or short list */
     /* if both values aren't set this is fine - will use default */
     if (split_pxp == NULL)
      {
       if (new_pxp == NULL) continue;
       else { is_match = FALSE; break; }
      }
     /* cannot have one set and not the other */
     if (new_pxp == NULL) { is_match = FALSE; break; }
     /* both values must be a number */
     if (split_pxp->optyp != NUMBER || new_pxp->optyp != NUMBER)
      { 
       is_match = FALSE; 
       break; 
      }
     /* these are known numbers - just using eval expr */
     xsp = __eval_xpr(split_pxp);
     xsp2 = __eval_xpr(new_pxp);
     wlen = wlen_(xsp->xslen);
     /* the expr consant sizes and values must match */
     if (xsp->xslen != xsp2->xslen) is_match = FALSE;
     else if (memcmp(xsp->ap, xsp2->ap, 2*wlen) != 0) is_match = FALSE;
     __pop_xstk(); 
     __pop_xstk(); 
     /* known not to match break */
     if (!is_match) break;
    }

   if (is_match)
    {
     /* DBG remove --- */
     if (mdp != mdp->inst_split->imsym->el.emdp)
      __misc_terr(__FILE__, __LINE__);
     /* ----- */
     __inst_mod = mdp;
     return(mdp);
    }
  }
 return(NULL);
}



/*
 * ROUTINES TO BUILD AS IF FLATTENED INSTANCE TREE
 */

/*
 * build a linked tree as if flattened instance structure
 * needed in simulation and for tracing xmrs
 * try to set fields at as high a place in tree as possible
 */
extern void __bld_flat_itree(void)
{
 int32 ii;

 for (ii = 0; ii < __numtopm; ii++)
  {
   bld2_flat_itree(__it_roots[ii]);
  }
 /* DBG remove --- */
 if (__debug_flg)
  { for (ii = 0; ii < __numtopm; ii++) __dmp_itree(__it_roots[ii]); }
 /* --- */
}

/*
 * non top level built itree for inst. of one module
 *
 * know up instance pointers point to allocated but not set itree nodes
 * for each inst. in module one up
 * try to make as breadth first as possible
 */
static void bld2_flat_itree(struct itree_t *new_itp)
{
 int32 ii;
 struct inst_t *ip;
 struct itree_t *itp;
 struct mod_t *up_imdp, *imdp;

 up_imdp = new_itp->itip->imsym->el.emdp;
 /* if mod has no insts empty minsts ptr tab and empty up_itp ptr table */
 if (up_imdp->minum == 0) return;

 /* allocate pointer to contained itree instances */
 new_itp->in_its = (struct itree_t *)
  __my_malloc(up_imdp->minum*sizeof(struct itree_t));

 /* fill contained itree instance contents */ 
 for (ii = 0; ii < up_imdp->minum; ii++)
  {
   /* alloc sets inst_t value */
   itp = &(new_itp->in_its[ii]);
   __init_itree_node(itp);
   ip = &(up_imdp->minsts[ii]);
   imdp = ip->imsym->el.emdp;
   itp->itip = ip;
   itp->up_it = new_itp;
   /* assign instance number */
   itp->itinum = imdp->lastinum;
   imdp->lastinum += 1;
   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg("==> building flat itree for instance %s of type %s\n",
      ip->isym->synam, ip->imsym->synam);
    }
   --- */
  }
 /* finally down 1 level */
 for (ii = 0; ii < up_imdp->minum; ii++)
  bld2_flat_itree(&(new_itp->in_its[ii]));
}

/*
 * dump a instance tree
 */
extern void __dmp_itree(struct itree_t *itp) 
{
 int32 i;

 __dbg_msg("--- dumping instance tree ---.\n");
 /* dump top */
 do_dmp(itp, 0);
 for (i = 1;; i++) { if (!dmp_down_itree(itp, i, i)) return; }
}

/*
 * dump a down level of a tree
 */
static int32 dmp_down_itree(struct itree_t *itp, int32 lev, int32 more_down)
{
 int32 i, ofsnum, retval;

 if (more_down == 0) { do_dmp(itp, lev); return(TRUE); }
 if ((ofsnum = itp->itip->imsym->el.emdp->minum) == 0) return(FALSE);
 for (retval= FALSE, i = 0; i < ofsnum; i++)
  {
   if (dmp_down_itree(&(itp->in_its[i]), lev, more_down - 1))
    retval = TRUE;
  }
 return(retval);
}

/*
 * do actual dump for level of 1 itp at level lev
 */
static void do_dmp(struct itree_t *itp, int32 lev)
{
 int32 ofsnum;
 char *chp, s1[RECLEN];

 /* DBG remove --- */
 if (itp->itip == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (itp->up_it == NULL) { strcpy(s1, "(top module)"); chp = s1; }
 else chp = itp->up_it->itip->isym->synam;
 ofsnum = itp->itip->imsym->el.emdp->minum;
 __dbg_msg("-- level %d: inst. %s(%s) itinum %d, up %s %d offspring\n",
  __dagmaxdist - lev, itp->itip->isym->synam, itp->itip->imsym->synam,
  itp->itinum, chp, ofsnum);
}

/*
 * free under root (top level) itree
 */
extern void __free_flat_itree(void)
{
 int32 ii;
 struct mod_t *mdp;

 for (ii = 0; ii < __numtopm; ii++) free2_flat_itree(__it_roots[ii]);

 /* final step requires resetting last inum field in every module */ 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt) mdp->lastinum = 0;
}

/*
 * free itree in_its tables bottom up
 */
static void free2_flat_itree(struct itree_t *cur_itp)
{
 int32 ii;
 struct mod_t *cur_imdp;

 cur_imdp = cur_itp->itip->imsym->el.emdp;

 /* if mod has no insts, nothing to do, if not top up frees */ 
 if (cur_imdp->minum == 0) return;

 /* otherwise free all under first */
 for (ii = 0; ii < cur_imdp->minum; ii++)
  free2_flat_itree(&(cur_itp->in_its[ii]));

 /* all under freed but in its table not yet freed */
 __my_free (cur_itp->in_its, cur_imdp->minum*sizeof(struct itree_t)); 
 cur_itp->in_its = NULL;
}

/*
 * ROUTINES TO BUILD INSTANCE NUMBER TO ITREE TABLES
 */

/*
 * build mod itp tabs for all modules
 *
 * look to improve this - either build only when needed or remove unneeded
 * before run time
 */
extern void __bld_moditps(void)
{
 int32 ii;
 struct mod_t *mdp;
 struct itree_t *itp, *itp2;

 /* first allocate the inst num to itree location tables */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   mdp->moditps = (struct itree_t **)
   __my_malloc(mdp->flatinum*sizeof(struct itree_t *));
   memset(mdp->moditps, 0, mdp->flatinum*sizeof(struct itree_t *));
  }

 for (ii = 0; ii < __numtopm; ii++)
  {
   itp = __it_roots[ii];
   mdp = itp->itip->imsym->el.emdp;
   mdp->moditps[itp->itinum] = itp;
   bld2_itnum_to_itp(itp);
  }

 if (__debug_flg)
  {
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     __dbg_msg("\n--- module %s instances:\n", mdp->msym->synam);
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       itp2 = mdp->moditps[ii];
       __dbg_msg("  instance %s type %s\n", 
        __msg2_blditree(__xs, itp2), itp2->itip->imsym->synam);
      }
    }
   __dbg_msg("\n");
  }
}

/*
 * recusively build the table
 */
static void bld2_itnum_to_itp(struct itree_t *itp)
{
 int32 ii;
 struct mod_t *mdp;
 
 mdp = itp->itip->imsym->el.emdp;
 if (mdp->moditps != NULL) mdp->moditps[itp->itinum] = itp;
 for (ii = 0; ii < mdp->minum; ii++) bld2_itnum_to_itp(&(itp->in_its[ii]));
}

/*
 * GENERATE ROUTINES - NOW SEPARATED AND SELF CONTAINED UNTIL ADD TO NL
 */

/*
 * ROUTINES TO FREEZE GEN BLK SYMBOLS TABLES (CONVERT TO BINARY SEARCH ARRAY)
 * CALLED IN SRC READ AS END PART OF ONE MOD SRC READ
 */

/*
 * copy a list of gen items
 */  
extern void __travfreeze_genitem_sytabs(struct genitem_t *gip_hd)
{
 struct genitem_t *gip;

 for (gip = gip_hd; gip != NULL; gip = gip->geninxt)
  {
   travfreeze1_genitem(gip);
  }
}

/*
 * routine to copy one generate item
 */  
static void travfreeze1_genitem(struct genitem_t *gip)
{
 struct gen_csitem_t *gcsip;

 switch (gip->gityp) {
  case GI_GFOR:
   travfreeze1_genblk(gip->giu.gi_gforp->src_gforblkp);
   break;
  case GI_GIF:
   travfreeze1_genblk(gip->giu.gi_gifp->src_then_gblkp);
   if (gip->giu.gi_gifp->src_else_gblkp != NULL)
    {
     travfreeze1_genblk(gip->giu.gi_gifp->src_else_gblkp);
    }
   break;
  case GI_GCASE:
   gcsip = gip->giu.gi_gcasp->gcsitems;
   for (; gcsip != NULL; gcsip = gcsip->gcsinxt)
    {
     travfreeze1_genblk(gcsip->gen_csiblkp);
    }
   break;
  case GI_GBLK:
   travfreeze1_genblk(gip->giu.gi_gblkp);
   break;
  default: break;
 }
}

/*
 * trav freeze the symbol table in one gen block and process items
 *
 */
static void travfreeze1_genblk(struct genblk_t *gblkp)
{
 /* SJM 01-17-09 - if symbol table empty - nothing to freeze */
 if (gblkp->gblk_sytab->numsyms != 0)
  {
   /* SJM 05-04-10 - in chg to gblk as mod algorithm, tasks, funcs, and */
   /* lbs now may have lb and task/func sym tabs inside so freeze those too */
   __freeze_mod_syms(gblkp->gblk_sytab, NULL);
  }
 __travfreeze_genitem_sytabs(gblkp->gitems);
}

/*
 * ROUTINES TO EXPAND GENERATE RECORDS
 */

/*
 * expand generates in one mod to change the contents just the currently
 * being generated module (after here still not moved into dsgn)
 *
 * SJM 12-04-08/05-30-10 - all generate can do is add new module top level
 * items * and cannot change parameter values. ports or create IS form params
 * or create anything that can effect modules splitting - except downward
 * new items may pass different param values down
 *
 * but new instances can be created so the instance tree needs to be
 * rebuilt and new symbols can be added to the mod's symbol table
 *
 * SJM 04-04-10 - this routine works totally in the world of gen items and
 * blocks - the mv gen items into mod done all at once after 
 *
 * SJM 05-31-10 - only called if mod has generates, still need to separate
 * expand from move to mod top level items (never need 2nd expand?) 
 */
static void xpnd_1mod_gen_items(struct mod_t *mdp)
{
 struct genitem_t *gip;
 int32 sav_slin_cnt, sav_sfnam_ind;

 /* SJM 01-14-09 - mod's may not be parallel or 1-to-1 because of splitting */
 /* key: if any splitting may change original mod params but gen can only */
 /* see non split off modules (types) */ 

 /* SJM 12-27-08 - need to initialize the mod gen work sym tab */
 /* first used here - until here all gen sym go into gen blk sym tabs */
 mdp->mgen_symtab = __alloc_symtab(FALSE);

 /* SJM 01-16-09 - this must run with inst mod set */ 
 __push_wrkitstk(mdp, 0);
 // AJB 06-28-14 generate instantiation need location context 
 sav_slin_cnt = __lin_cnt;
 sav_sfnam_ind = __cur_fnam_ind;
 for (gip = mdp->mgenitems; gip != NULL; gip = gip->geninxt)
  {
   // AJB 06-28-14 - sym add would take last elaborated file otherwise.
   __cur_fnam_ind = gip->gi_fnam_ind;
   __lin_cnt = gip->gilin_cnt + 1;
   // AJB 06-28-14 this gives vicinity of the generate
   // all line numbers seem to be off by one so adjusting here
   // SJM 07-07-14 - LOOKATME - line nums one before this changes slightly
   xpnd1_gen_item(gip, NULL);
  }
 __lin_cnt = sav_slin_cnt;
 __cur_fnam_ind = sav_sfnam_ind;

 __pop_wrkitstk();
}

/*
 * expand one generate item - can be nested
 */ 
static void xpnd1_gen_item(struct genitem_t *gip,
 struct genblk_t *cntxt_gblkp)
{
 switch (gip->gityp) {
  case GI_GBLK:
   xpnd1_genblk(gip->giu.gi_gblkp);
   break;
  case GI_GFOR:
   xpnd1_gen_for(gip, cntxt_gblkp);
   break;
  case GI_GIF:
   xpnd1_gen_if(gip, cntxt_gblkp);
   break;
  case GI_GCASE:
   xpnd1_gen_case(gip, cntxt_gblkp);
   break;
  case GI_CONTA:
   xpnd1_gen_conta(gip, cntxt_gblkp);
   break;
  case GI_INST:
   xpnd1_gen_inst(gip, cntxt_gblkp);
   break;
  case GI_GATE:
   xpnd1_gen_gate(gip, cntxt_gblkp);
   break;
  case GI_VARDECL:
   xpnd1_gen_vardecl(gip, cntxt_gblkp);
   break;
  case GI_INITALW:
   xpnd1_gen_initalways(gip);
   break;
  case GI_DFPARM:
   /* SJM 04-11-10 - should never see these in this gen item list */
   /* SJM 04-11-10 - nothing do do for gen blk XMRs here but process dfps */
   /* when expanding each gen blk */
   __misc_terr(__FILE__, __LINE__);   
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * routine to expand one gen blk - just set gen blk struct context and
 * expands list of gen items
 */
static void xpnd1_genblk(struct genblk_t *gblkp)
{
 struct genitem_t *gip;

 /* check/fix to insure all gen blk (even nested) names unique in mod */
 /* symbol table */
 /* SJM 10-02-09 - since adding index to gen for, always need check */
 try_fix_genblk_nam_conflict(gblkp, __inst_mod);

 /* go thru every gen item in gen blk and expand and add to mod el list */ 
 for (gip = gblkp->gitems; gip != NULL; gip = gip->geninxt)
  { 
   xpnd1_gen_item(gip, gblkp);
  } 
 /* need to xpnd (copy) the defparam in each gen blk (many if gen for) */
 for (gip = gblkp->dfp_gitems; gip != NULL; gip = gip->geninxt)
  {
   chk_xpnd1_dfparam(gip, gblkp);
  }
}

/*
 * routine to expand a gen for - new algorith blds an array of
 * contained gen block
 *
 * SJM 12-16-08 - must not substitute genvars here - eval will find as
 * local params as it should
 *
 * SJM 03-01-09 - new algorithm build the possibly sparse array:
 * SJM 03-03-09 - notice in gen blks no genvar substituion - gen fors
 *                are meta constructs
 * sjm 10-02-09 - now passing and setting xpnd from gen blk for gen fors
 */  
static void xpnd1_gen_for(struct genitem_t *gip, struct genblk_t *cntxt_gblkp)
{
 int32 h_rng, l_rng, gti;
 struct gen_for_t *gforp;

 gforp =  gip->giu.gi_gforp;

 h_rng = l_rng = -1;
 /* SJM 09-30 - if error i.e. genvar not declared on not genvar returns F */
 if (!fnd_genfor_genvar_rng(gip, &(h_rng), &(l_rng))) return;
 
 if (h_rng == -1)
  {
   __gfinform(3012, gip->gi_fnam_ind, gip->gilin_cnt,
    "generate for loop - empty range - nother generated");
   return;
  }
 /* gen for gen var ndx numbers can occur in any order - but have high/low */
 /* since gen vars are only positive non x/z ints know high same */ 
 /* as size - if low range not 0 - those bits just unused */
 gforp->ngenblks = h_rng + 1;
 gforp->gentab = (struct genblk_t **)
  __my_malloc(gforp->ngenblks*sizeof(struct genblk_t *)); 
 for (gti = 0; gti < gforp->ngenblks; gti++) gforp->gentab[gti] = NULL;

 /* run gen for loop again fill gentab indices - calcs gen ndx and genvar */
 bld_genfor_gentab(gforp, cntxt_gblkp);
}

/*
 * routine to exec a gen for to determine max index
 * execs gen for loop to find max - need because can be h:l and sparse
 *
 * routine also handles checking - for expand to fill for's gen blk tab 
 * does not check
 *
 * SJM 12-16-08 - must not substitute genvars here - eval will find as 
 * local params as it should
 *
 * SJM 03-02-09 - FIXME? - where handle LRM rule that genvars can not have
 * x parts
 */  
static int32 fnd_genfor_genvar_rng(struct genitem_t *gip, int32 *h_rng,
 int32 *l_rng)
{
 int32 ndx;
 word32 *wp;
 struct gen_for_t *gforp;
 struct st_t *stp;
 struct xstk_t *xsp;
 struct net_t *genv_np;
 struct expr_t *init_lhsxp, *init_rhsxp, *inc_rhsxp, *lhsxp;

 gforp = gip->giu.gi_gforp;

 /* check terminating and inc rhs exprs - sets width */ 
 /* mark exprs in gen for's as folded since the */
 /* gen is a local param that changes values, obviously can't fold */
 gforp->gfortermx->folded = TRUE;
 if (!gen_chk_expr(gforp->gfortermx, gip->gi_fnam_ind, gip->gilin_cnt,
  "gen for terminating expression")) return(FALSE);

 inc_rhsxp = gforp->gforinc->st.spra.rhsx;

 /* AIV 09/29/10 - can now have ++/-- with no rhsx */
 if (inc_rhsxp != NULL)
  {
   gforp->gforinc->st.spra.rhsx->folded = TRUE;
   if (!gen_chk_expr(gforp->gforinc->st.spra.rhsx, gip->gi_fnam_ind,
    gip->gilin_cnt, "gen for inc rhs expression")) return(FALSE);
  }
  
 stp = gforp->gforassgn;
 init_lhsxp = stp->st.spra.lhsx; 
 init_rhsxp = stp->st.spra.rhsx; 
 /* AIV 08/04/09 - this rhs needs to be converted as well */
 if (!gen_chk_expr(init_rhsxp, gip->gi_fnam_ind, gip->gilin_cnt,
  "gen for init rhs expression")) return(FALSE);

 /* SJM 09-30-09 - if genvar undeclared it will look like net so must catch */
 if (init_lhsxp->optyp != ID || init_lhsxp->lu.sy->sytyp != SYM_N)
  {
   __sgferr(3612,
    "gen for gen var index expression %s illegal - not a parameter",
    __msgexpr_tostr(__xs, init_lhsxp));
   return(FALSE);
  }

 genv_np = init_lhsxp->lu.sy->el.enp;

 if (!genv_np->n_isaparam || !genv_np->nu.ct->p_genvar)
  {
   __sgferr(3612,
    "gen for gen var index expression %s illegal - not a genvar",
    __msgexpr_tostr(__xs, init_lhsxp));
   return(FALSE);
  }

 xsp = __eval_xpr(init_rhsxp);

 /* SJM 12-06-08 - each gen blk needs a ptr to its at most 1 gen var */
 gforp->src_gforblkp->gvnp = genv_np;

 /* set gen for's gen var's value for initial value */
 wp = genv_np->prm_nva.wp;
 /* AIV 08/04/09 - need the * WRDBYTES */
 memcpy(wp, xsp->ap, 2*wlen_(genv_np->nwid)*WRDBYTES);
 __pop_xstk();

 /* range can be empty then just ranges -1 */
 *h_rng = *l_rng = -1;
next_for:
 if (!genfor_not_done(gforp->gfortermx)) return(TRUE);

 stp = gforp->gforinc;
 /* SJM 09-30-09 - these t errors are right if inconsistency in looping */
 /* DBG remove -- */
 /* AIV 09/28/10 - can now have ++/-- here - no rhs expr */
 if (stp->stmttyp == S_INC || stp->stmttyp == S_DEC)
  {
   lhsxp = stp->st.spra.lhsx;
   lhsxp = lhsxp->lu.x;
  }
 else lhsxp = stp->st.spra.lhsx;

 if (lhsxp->optyp != ID || lhsxp->lu.sy->sytyp != SYM_N) 
    __misc_terr(__FILE__, __LINE__);
 if (lhsxp->lu.sy->el.enp != genv_np)
  __misc_terr(__FILE__, __LINE__);
 /* ---*/

 ndx = (int32) wp[0];
 if (*h_rng == -1) *h_rng = ndx; else if (ndx > *h_rng) *h_rng = ndx;
 if (*l_rng == -1) *l_rng = ndx; else if (ndx < *l_rng) *l_rng = ndx;

 /* still always need to update gen for's genvar control index */
 wp = genv_np->prm_nva.wp;
 /* AIV 08/04/09 - need the * WRDBYTES */
 if (inc_rhsxp != NULL)
  {
   xsp = __eval_xpr(stp->st.spra.rhsx);
   memcpy(wp, xsp->ap, 2*wlen_(genv_np->nwid)*WRDBYTES);
   __pop_xstk();
  }
 else 
  {
   /* AIV 09/28/10 - can now have ++/--, just inc/dec */
   if (stp->stmttyp == S_INC) wp[0] = wp[0] + 1;
   else if (stp->stmttyp == S_DEC) wp[0] = wp[0] - 1;
   else __case_terr(__FILE__, __LINE__);
  }
 goto next_for;
}

/*
 * routine to expand a gen for
 * must be called after find gen for genvar range since does not do checking
 *
 * sjm 10-02-09 - now passing and setting xpnd from gen blk for gen fors
 */  
static void bld_genfor_gentab(struct gen_for_t *gforp,
 struct genblk_t *cntxt_gblkp)
{
 int32 ndx;
 word32 *wp;
 struct net_t *genv_np;
 struct st_t *stp;
 struct xstk_t *xsp;
 struct expr_t *init_rhsxp;
 struct genblk_t *ngblkp;

 stp = gforp->gforassgn;
 init_rhsxp = stp->st.spra.rhsx; 

 xsp = __eval_xpr(init_rhsxp);

 /* gen for src genblk filled when calculating gen blk array range */ 
 genv_np = gforp->src_gforblkp->gvnp;

 wp =  genv_np->prm_nva.wp;
 /* AIV 08/04/09 - need the * WRDBYTES */
 memcpy(wp, xsp->ap, 2*wlen_(genv_np->nwid)*WRDBYTES);
 __pop_xstk();

next_for:
 if (!genfor_not_done(gforp->gfortermx)) return;

 ndx = (int32) genv_np->prm_nva.wp[0];

//SJM 03-14-09 - NOTICE only copy needed during expand is this one - do not
// need to copy an gen items since the gentab copies make gen items unique
 /* SJM 03-14-09 - need to copy every gen for loop gen block - once copied */
 /* do not need to copy gen items before expand of each gentab gen blk */
 ngblkp = __xpnd_copy1_genblk(gforp->src_gforblkp, genv_np, ndx);  

 /* SJM 10-02-09 - parent of this genblk must be passed so inside gen fors */ 
 /* including nest gen fors each name will have gen for blk with its index */
 /* SJM 02-16-10 - but now parents linked through a genblk's sym tab par */
 if (cntxt_gblkp != NULL)
  {
   /* DBG remove -- */
   if (cntxt_gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   ngblkp->gblk_sytab->sytpar = cntxt_gblkp->gblk_sytab;
  }
 /* SJM 03-31-11 - gen blks in mods (items), parent sym tab is mod's sym tab */
 else ngblkp->gblk_sytab->sytpar = __inst_mod->msymtab;

 /* SJM 03-14-09 can expand gen blk since each gentab gen blk independent */ 
 xpnd1_genblk(ngblkp);
 gforp->gentab[ndx] = ngblkp; 

 stp = gforp->gforinc;
 wp = genv_np->prm_nva.wp;
 /* AIV 09/28/10 - can now have ++/--, just inc/dec */
 if (stp->st.spra.rhsx == NULL)
  {
   if (stp->stmttyp == S_INC) wp[0]++;
   else if (stp->stmttyp == S_DEC) wp[0]--;
   else __case_terr(__FILE__, __LINE__);
  }
 else
  {
   xsp = __eval_xpr(stp->st.spra.rhsx);
   /* AIV 08/04/09 - need the * WRDBYTES */
   memcpy(wp, xsp->ap, 2*wlen_(genv_np->nwid)*WRDBYTES);
   __pop_xstk();
  }
 goto next_for;
}

/*
 * routine to mimic for not done but for gen fors
 */
static int32 genfor_not_done(struct expr_t *termx)
{
 int32 tmp, has_xzs;
 word32 val;
 struct xstk_t *xsp;

 /* must move and execute for inc. at end not beginning of loop */
 has_xzs = FALSE;
 xsp = __eval_xpr(termx);
 if (xsp->xslen <= WBITS)
  {
//SJM? 12-08-08 FIXME - think can still have real exprs here?
   /* SJM 07/20/00 - must convert to real if real */
   val = xsp->bp[0];
   tmp = ((xsp->ap[0] & ~val) != 0L);
   if (val != 0) { if (tmp == 0) tmp = 3; else has_xzs = TRUE; }
  }
 else
  {
   tmp = __cvt_lngbool(xsp->ap, xsp->bp, wlen_(xsp->xslen));
   if (tmp == 1) { if (!vval_is0_(xsp->bp, xsp->xslen)) has_xzs = TRUE; }
  }
 __pop_xstk();
 if (tmp == 1)
  {
   if (has_xzs)
    {
     __sgfinform(3012, "generate for condition true but has some x/z bits");
    }
   return(TRUE);
  }
 /* notice any 1 implies true so will not get here */
 if (tmp == 3)
  {
   __sgfinform(3013,
    "generate for loop terminated by FALSE expressions containing x/z bits");
  }
 /* done with loop */
 return(FALSE);
}

/*
 * routine to prep/chk a gen expr (v fx2 size setting/checking)
 */
static int32 gen_chk_expr(struct expr_t *ndp, int32 gxfnam_ind,
 int32 gxlin_cnt, char *genonam)
{
 int32 rv, sav_slin_cnt, sav_sfnam_ind, sav_err_cnt;

 sav_sfnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt;
 __slin_cnt = gxlin_cnt;
 __sfnam_ind = gxfnam_ind;
 
 rv = TRUE;
 sav_err_cnt = __pv_err_cnt;
 __chk_rhsexpr(ndp, 0);
 if (__pv_err_cnt != sav_err_cnt)
  {
   __sgferr(3604, "%s expression illegal - nothing generated", genonam); 
   rv = FALSE;
  }

 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
 return(rv);
}

/*
 * routine to expand a gen if
 *
 * SJM 03-03-09 - think need to rechck meta type gen exprs because
 * changed param values may change checking results
 */  
static void xpnd1_gen_if(struct genitem_t *gip, struct genblk_t *cntxt_gblkp)
{
 int32 tmp;
 struct gen_if_t *gifp;
 struct xstk_t *xsp;
 struct genblk_t *ngblkp, *ogblkp;

 gifp = gip->giu.gi_gifp;

 /* SJM 02-20-09 - algorithm was wrong - must leave gen vars in if condx */
 /* SJM 02-20-09 - set already folded bit to prevent folding */  
 gifp->condx->folded = TRUE;

 /* SJM 12-30-08 - must check if cond expr */
//SJM? 02-20-09 - LOOKATME - what if syntax error here?
 if (!gen_chk_expr(gifp->condx, gip->gi_fnam_ind, gip->gilin_cnt,
  "gen if conditional expression")) return;

 xsp = __eval_xpr(gifp->condx);
 /* condition T (non zero) only if at least 1, 1 */
 if (xsp->xslen <= WBITS)
  {
   if (gifp->condx->is_real)
    {
     double d1;
 
     memcpy(&d1, xsp->ap, sizeof(double));
     tmp = (d1 != 0.0);
    }
   else tmp = ((xsp->ap[0] & ~xsp->bp[0]) != 0L);
  }
 else tmp = (__cvt_lngbool(xsp->ap, xsp->bp, wlen_(xsp->xslen)) == 1);
 __pop_xstk();

   
 if (tmp) ogblkp = gifp->src_then_gblkp;
 else if (gifp->src_else_gblkp != NULL)
  {
   ogblkp = gifp->src_else_gblkp;
  }
 else ogblkp = NULL; 

 if (ogblkp == NULL)
  { 
   __gfinform(3012, gip->gi_fnam_ind, gip->gilin_cnt,
    "generate conditional if - nother generated");
   gifp->ngenblks = -1;
   return;
  }
 /* SJM 03-14-09 this meta gen blk must be copied in case need to gen */ 
 /* again because of changed params from prevous gen expand pass */
 /* SJM 03-20-09 - except in gen for unset gen var np and ndx correct */
 ngblkp = __xpnd_copy1_genblk(ogblkp, NULL, -1);

 /* SJM 10-02-09 - parent of this genblk must be passed so inside gen fors */ 
 /* each name will have the gen for blk with its index */
 if (cntxt_gblkp != NULL)
  {
   /* DBG remove -- */
   if (cntxt_gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   ngblkp->gblk_sytab->sytpar = cntxt_gblkp->gblk_sytab;
  }
 /* SJM 03-31-11 - gen blks in mods (items), parent sym tab is mod's sym tab */
 else ngblkp->gblk_sytab->sytpar = __inst_mod->msymtab;
 
 gifp->ngenblks = 1;
 gifp->gentab = (struct genblk_t **) __my_malloc(sizeof(struct genblk_t *));
 xpnd1_genblk(ngblkp);
 gifp->gentab[0] = ngblkp;
}

/*
 * expand one gen case - another gen conditional meta form
 */
static void xpnd1_gen_case(struct genitem_t *gip, struct genblk_t *cntxt_gblkp)
{
 struct gen_case_t *gcasp;
 struct genblk_t *ogblkp, *ngblkp;

 ogblkp = find_gen_case_gblk(gip);
 gcasp = gip->giu.gi_gcasp;
 if (ogblkp == NULL)
  { 
   __gfinform(3012, gip->gi_fnam_ind, gip->gilin_cnt,
    "generate case - nothing generated");
   gcasp->ngenblks = -1;
   return;
  }
 /* SJM 03-14-09 this meta gen blk must be copied in case need to gen */ 
 /* again because of changed params from prevous gen expand pass */
 /* SJM 03-20-09 - except in gen for unset gen var np and ndx correct */
 ngblkp = __xpnd_copy1_genblk(ogblkp, NULL, -1);

 /* SJM 10-02-09 - parent of this genblk must be passed so inside gen fors */ 
 /* each name will have the gen for blk with its index */

 /* SJM 02-16-10 - but now parents linked through a genblk's sym tab par */
 /* AIV 03-14-10 - only set gblk sytab par, if cntxt gblk set */
 if (cntxt_gblkp != NULL)
  {
   /* DBG remove -- */
   if (cntxt_gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   ngblkp->gblk_sytab->sytpar = cntxt_gblkp->gblk_sytab;
  }
 /* SJM 03-31-11 - gen blks in mods (items), parent sym tab is mod's sym tab */
 else ngblkp->gblk_sytab->sytpar = __inst_mod->msymtab;


 gcasp->ngenblks = 1;

 /* using tab although only 1 so can access same always and for xmrs */
 gcasp->gentab = (struct genblk_t **) __my_malloc(sizeof(struct genblk_t *));
 xpnd1_genblk(ngblkp);
 gcasp->gentab[0] = ngblkp;
}

/*
 * routine to find the gen case element to expand - returns gen blk to expand
 *
 * setting expr folded bit here prevents folding of genvars
 */  
static struct genblk_t *find_gen_case_gblk(struct genitem_t *gip)
{
 int32 selwlen, i; 
 struct xstk_t *itemxsp;
 struct exprlst_t *xplp;
 struct xstk_t *selxsp;
 struct gen_case_t *gcasp;
 struct gen_csitem_t *gcsip, *dflt_gcsip;
 struct genblk_t *gblkp;

 gcasp = gip->giu.gi_gcasp;

 /* SJM 02-20-09 - gen case meta construct select expr need to access latest */
 /* values of genvars - do not replace and do not fold */
 gcasp->csx->folded = TRUE;
 if (!gen_chk_expr(gcasp->csx, gip->gi_fnam_ind, gip->gilin_cnt,
  "gen case select expression")) return(NULL);

 /* check all exprs and find the default if thee is one */
 dflt_gcsip = NULL;
 for (gcsip = gcasp->gcsitems; gcsip != NULL; gcsip = gcsip->gcsinxt)
  {
   if (gcsip->gdflt_i) dflt_gcsip = gcsip; 

   /* SJM 02-09-09 - fixed bug gscip needs to be set since used as for ndx */
   for (xplp = gcsip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     xplp->xp->folded = TRUE;
     if (!gen_chk_expr(xplp->xp, gcsip->gen_csiblkp->genblk_fnam_ind,
      gcsip->gen_csiblkp->genblk_lin_cnt, "gen case item match expression"))
      {
       return(NULL);
      } 
    }
  }

 /* SJM 12/12/03 - must treat all 3 case types as special case if any */
 /* of select or case item exprs real */
 if (gcasp->csx->is_real || gcasp->csx->cnvt_to_real)
  {
   gblkp = get_real_case_sel_genblk(gip, dflt_gcsip);
   return(gblkp);
  }

 /* compute the case type - determines operator to use */
 selxsp = __eval_xpr(gcasp->csx);

 /* if expression real, convert to 32 bit reg */
 if (gcasp->csx->is_real) __cnv_stk_fromreal_toreg32(selxsp);

 for (gcsip = gcasp->gcsitems; gcsip != NULL; gcsip = gcsip->gcsinxt)
  {
   if (gcsip == dflt_gcsip) continue;

   for (xplp = gcsip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     itemxsp = __eval_xpr(xplp->xp);

     if (itemxsp->xslen > selxsp->xslen)
       __narrow_sizchg(itemxsp, selxsp->xslen);
     else if (itemxsp->xslen < selxsp->xslen)
      {
       if (xplp->xp->has_sign) __sgn_xtnd_widen(itemxsp, selxsp->xslen);
       else __sizchg_widen(itemxsp, selxsp->xslen);
      }
     selwlen = wlen_(selxsp->xslen);
     for (i = 0; i < selwlen; i++)
      {
       if (((selxsp->ap[i] ^ itemxsp->ap[i])
        | (selxsp->bp[i] ^ itemxsp->bp[i])) != 0) goto nxt_x;
      }
     __pop_xstk();
     __pop_xstk();
     return(gcsip->gen_csiblkp);

nxt_x:
     __pop_xstk();
    }
  }  
 __pop_xstk();
 if (dflt_gcsip != NULL) return(dflt_gcsip->gen_csiblkp);
 return(NULL);
}

/*
 * exec a gen case - returns the gen block to expand
 */
static struct genblk_t *get_real_case_sel_genblk(struct genitem_t *gip,
 struct gen_csitem_t *dflt_gcsip)
{
 double d1, d2;
 struct xstk_t *itemxsp;
 struct exprlst_t *xplp;
 struct xstk_t *selxsp;
 struct gen_case_t *gcasp;
 struct gen_csitem_t *gcsip;

 gcasp = gip->giu.gi_gcasp;

 /* compute the case type - determines operator to use */
 selxsp = __eval_xpr(gcasp->csx);

 /* if select expr not real convert it */
 if (gcasp->csx->cnvt_to_real)
  {
   __cnv_stk_fromreg_toreal(selxsp, gcasp->csx->has_sign);
  }
 memcpy(&d1, selxsp->ap, sizeof(double));

 for (gcsip = gcasp->gcsitems; gcsip != NULL; gcsip = gcsip->gcsinxt)
  {
   if (gcsip == dflt_gcsip) continue;

   for (xplp = gcsip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     itemxsp = __eval2_xpr(xplp->xp);

     /* if case item expr not real convert it */
     if (xplp->xp->cnvt_to_real)
      {
       __cnv_stk_fromreg_toreal(itemxsp, xplp->xp->has_sign);
      } 
     memcpy(&d2, itemxsp->ap, sizeof(double));

     /* real == (near 0.0) */
     if ((d2 - d1) > -EPSILON && (d2 - d1) < EPSILON)
      { __pop_xstk(); __pop_xstk(); return(gcsip->gen_csiblkp); }
     __pop_xstk();
    }
  }
 __pop_xstk();
 if (dflt_gcsip != NULL) return(dflt_gcsip->gen_csiblkp);
 return(NULL);
}

/*
 * ROUTINES TO EXPAND GEN ITEMS TO INSERT IN MOD NL STORED IN GEN ITEMS
 */

/*
 * expand continuous assignment generate item
 * simple so just inline copy - do not need separate routine
 *
 * now easy since can replace all genvars in expressions with numbers and
 * use the module splitting copy mechanism to add a new conta to bottom
 * of table
 *
 * SJM 03-14-09 - notice conta already copied when the gen blk containing
 * it is copied as first part of gen expand operation
 */
static void xpnd1_gen_conta(struct genitem_t *gip,
 struct genblk_t *cntxt_gblkp)
{
 struct conta_t *cap;
 struct sy_t *syp;
 char s1[RECLEN], s2[RECLEN];

 cap = gip->giu.gi_cap;

 /* DBG remove -- */
 if (cntxt_gblkp == NULL) __misc_terr(__FILE__, __LINE__);
 if (cap->pbcau.canxt != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* SJM 03-07-09 - item name is going to be copied into mod level sym tab */
 /* so needs the full hierarchical name, dots allow later XMR finding */
 __bld_gen_scope_nam(s1, cntxt_gblkp);
 sprintf(s2, "%s.__frgassign$%d", s1, __conta_num++);

 syp = __decl_sym(s2, __inst_mod->mgen_symtab);
 /* DBG remove -- */ 
 if (!__sym_is_new) __misc_terr(__FILE__, __LINE__);

 if (__get_sym(s2, __inst_mod->msymtab) != NULL)  
  __misc_terr(__FILE__, __LINE__);
 /* --- */ 
 
 syp->sytyp = SYM_CA;
 syp->gen_add_mstab = TRUE;
 syp->sydecl = TRUE;
 cap->casym = syp;
 syp->el.ecap = cap;

 /* copy the still elaborate time list of delays not del_t */
 genp_dellst_do(cap->ca_du.pdels, do_repl_id_genvar);

 genp_expr_do(cap->lhsx, do_repl_id_genvar);
 genp_expr_do(cap->rhsx, do_repl_id_genvar);
}

/*
 * 
 * know at copy point delay is DT_CMPLST list
 */
static void genp_dellst_do(struct paramlst_t *plp,
 void (*gprm_proc)(struct expr_t *))
{
 for (; plp != NULL; plp = plp->pmlnxt)
  {
   genp_expr_do(plp->plxndp, gprm_proc);
  }
}

/*
 * expand 1 gen instance
 *
 * SJM 03-20-09 - know it has already been copied
 */
static void xpnd1_gen_inst(struct genitem_t *gip, struct genblk_t *cntxt_gblkp)
{
 int32 prmi, pi;
 struct inst_t *ip;
 struct sy_t *syp;
 struct mod_t *imdp;
 struct expr_t *pxp;
 struct gia_aux_t *giap;
 char genscop_prefix[RECLEN], s1[RECLEN];

 ip = gip->giu.gi_igp->ip;
 /* DBG remove -- */
 if (cntxt_gblkp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* know gen blk name already guarenteed to be unique */
 __bld_gen_scope_nam(genscop_prefix, cntxt_gblkp);
 /* DBG remove -- */
 if (strcmp(genscop_prefix, "") == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 sprintf(s1, "%s.%s", genscop_prefix, ip->isym->synam);

 /* then decl in mod gen symbol table */
 /* SJM 02-22-09 - decl sym initializes symbol and set only name field */
 /* also inserts in avl tree */
 syp = __decl_sym(s1, __inst_mod->mgen_symtab);
 if (!__sym_is_new)
  {
   __gferr(3603, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
    "qualified generated instance name %s conflicts with another generated %s symbol at %s",
    s1, __to_sytyp(__xs, syp->sytyp), __bld_lineloc(__xs2, syp->syfnam_ind,
    syp->sylin_cnt));
   /* return without moving to gen item move to design ptr */
   return;
  }
 /* SJM 03-04-09 - sym is new so need to fill various fields */
 syp->gen_add_mstab = TRUE;
 syp->sydecl = TRUE;
 syp->sytyp = SYM_I;

 /* need to set the cross links for new inst sym */
 syp->el.eip = ip;
 ip->isym = syp;

 /* SJM 03-14-09 - no longer need to copy non meta gen items since when meta */
 /* (for, case, if) copied, do not need to copy mod item - already have copy */

 /* SJM 03-20-09 - if no pound params specified for this inst - just skip */
 imdp = ip->imsym->el.emdp;
 if (ip->ipxprtab != NULL)
  {
   /* substitute inst's pnd param expressions */
   for (prmi = 0; prmi < imdp->mprmnum; prmi++)
    {
     pxp = ip->ipxprtab[prmi];
     /* AIV 07/15/09 - this can be NULL here - if not setting all */
     /* parameters - look at inst_nparms_to_xtab - if setting less params */
     /* with # then just skip the NULL */
     if (pxp == NULL) continue;
     genp_expr_do(pxp, do_repl_id_genvar);
    }
  } 
 /* also subsitute in port high conn connections */
 for (pi = 0; pi < imdp->mpnum; pi++)
  {
   genp_expr_do(ip->ipins[pi], do_repl_id_genvar);
  }
  /* SJM 03-11-09 - implicit declarations in mod's mgen symbol table */ 
 for (pi = 0; pi < imdp->mpnum; pi++)
  {
   mark_declnet_expr_syms(ip->ipins[pi], cntxt_gblkp);
  } 
 
 /* SJM 03-14-09 - src loc already set from genblk inst genitem copy */

 /* SJM 05-04-10 - with new gen blk scope as pseudo mod algorithm - now */
 /* just substitute and eval the ranges here - after move new g/i arrays */
 /* from gen blocks will be expanded using normal code */
 if ((giap = ip->i_giap) != NULL) 
  {
   __inst_mod->m_gia_in_gblks = TRUE;
   __inst_mod->m_has_iarrs = TRUE;
   __design_gi_arrays = TRUE;

   genp_expr_do(giap->giax1, do_repl_id_genvar);
   genp_expr_do(giap->giax2, do_repl_id_genvar);
   eval1_arr_of_insts_rng(ip, NULL);
  }
}

/*
 * expand 1 gen gate
 */
static void xpnd1_gen_gate(struct genitem_t *gip, struct genblk_t *cntxt_gblkp)
{
 int32 pi;
 struct sy_t *syp;
 struct gate_t *gp;
 struct gia_aux_t *giap;
 char genscop_prefix[RECLEN], s1[RECLEN];

 gp = gip->giu.gi_gp;
 /* if unnamed - no gate inst name - gening into mgate that way works */
 /* DBG remove -- */
 if (cntxt_gblkp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* know gen blk name already guarenteed to be unique */
 __bld_gen_scope_nam(genscop_prefix, cntxt_gblkp);
 /* DBG remove -- */
 if (strcmp(genscop_prefix, "") == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 sprintf(s1, "%s.%s", genscop_prefix, gp->gsym->synam);

 /* then decl in mod gen symbol table */
 /* SJM 02-22-09 - decl sym initializes symbol and set only name field */
 /* also inserts in avl tree */
 syp = __decl_sym(s1, __inst_mod->mgen_symtab);
 if (!__sym_is_new)
  {
   __gferr(3603, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
    "qualified generated gate (prim) name %s conflicts with another generated %s symbol at %s",
    s1, __to_sytyp(__xs, syp->sytyp), __bld_lineloc(__xs2,
    syp->syfnam_ind, syp->sylin_cnt));
    /* return without moving to gen item move to design ptr */
   return;
  }

 /* DBG remove -- */
 if (__debug_flg)
  {
   if (gp->gsym != NULL)
    {
     __dbg_msg(" == while expanding gate old gate sym was %s\n",
      gp->gsym->synam);
    }
   else __dbg_msg(" == while expanding gate old gate sym was NULL\n");
  }
 /* --- */ 

 /* need to set the cross links for new inst sym */
 syp->el.egp = gp;
 gp->gsym = syp;

 /* SJM 03-04-09 - sym is new so need to fill various fields */
 syp->gen_add_mstab = TRUE;
 syp->sydecl = TRUE;
 if (gp->gmsym->sytyp == SYM_UDP) syp->sytyp = SYM_UDP;
 else syp->sytyp = SYM_PRIM;

 /* substitute gen vars for delays in expr list form still */
 genp_dellst_do(gp->g_du.pdels, do_repl_id_genvar);

 /* substitute gen var in gate/udp terminals */
 for (pi = 0; pi < gp->gpnum; pi++)
  {
   genp_expr_do(gp->gpins[pi], do_repl_id_genvar);
  }

 /* SJM 03-11-09 - implicit declarations in mod's mgen symbol table */ 
 for (pi = 0; pi < gp->gpnum; pi++)
  {
   mark_declnet_expr_syms(gp->gpins[pi], cntxt_gblkp);
  } 

 /* SJM 05-04-10 - with new gen blk scope as pseudo mod algorithm - now */
 /* just substitute and eval the ranges here - after move new g/i arrays */
 /* from gen blocks will be expanded using normal code */
 if ((giap = gp->g_giap) != NULL) 
  {
   __inst_mod->m_gia_in_gblks = TRUE;
   __inst_mod->m_has_garrs = TRUE;
   __design_gi_arrays = TRUE;

   genp_expr_do(giap->giax1, do_repl_id_genvar);
   genp_expr_do(giap->giax2, do_repl_id_genvar);
   eval1_arr_of_gates_rng(gp, NULL);
  }
}

/*
 * routine to expand a var decl
 *
 * SJM 03-15-09 - net declared during src read and added to gen blks gblk
 * sytab - net sym in gen blk sytab cross linked with net from src read
 * will have declared and net type wide set
 */
static void xpnd1_gen_vardecl(struct genitem_t *gip,
 struct genblk_t *cntxt_gblkp)
{
 struct net_t *np;
 struct sy_t *syp;

 /* DBG remove -- */
 if (cntxt_gblkp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 np = gip->giu.gi_np;
 syp = np->nsym;
 /* net has been declared in src and copied along with gen blk sym tab */
 /* SJM 03-15-09 - this set indicates this gen var decl expanded so need */
 /* to copy first to mod mod's mgen symtab with the gen blk's scope path */
 /* and then will be copied to mod's */
 syp->gen_add_mstab = TRUE;
 /* SJM 03-16-09 expand means declared */
 syp->sydecl = TRUE;

 /* SJM 03-14-09 - no longer need to copy gen net since already copied */
 /* when containing gen blk copied */
}

/*
 * expand initial or always generate item
 */  
static void xpnd1_gen_initalways(struct genitem_t *gip)
{
 struct ialst_t *ialp;
 
 ialp = gip->giu.gi_ialp;
 /* AIV 05/07/09 - had an malloc here which cannot be right */
 /* DBG remove -- */
 if (ialp->ialnxt != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* AIV 07/08/10 - this needs to do the stmt list was only expanded the */
 /* first stmt - need to call the stlst version */
 genp_stlst_do(ialp->iastp, do_repl_id_genvar);
}

/*
 * substitute in gen defp index genvars and check for downward relative
 * into gen blk here
 */
static void chk_xpnd1_dfparam(struct genitem_t *gip,
 struct genblk_t *cntxt_gblkp)
{
 struct dfparam_t *dfpp;
 struct expr_t *lhsx, *ndp, *dfphd_ndp;
 struct gref_t *grp;
 struct sy_t *syp;

 dfpp = gip->giu.gi_dfp;
 lhsx = dfpp->dfpxlhs;

 if (lhsx->optyp != GLBREF)
  {
   __gferr(3613, dfpp->dfpfnam_ind, dfpp->dfplin_cnt,
    "local defparam %s=%s in generate block %s illegal in generate blocks",
    __msgexpr_tostr(__xs, lhsx), __msgexpr_tostr(__xs2, dfpp->dfpxrhs),
    cntxt_gblkp->gblknam);
   return;
  }

 /* get glb ref comma expr from gref */
 grp = lhsx->ru.grp;
 dfphd_ndp = grp->glbref->ru.x;
 if (dfphd_ndp->lu.x->optyp == XMRID) ndp = dfphd_ndp->lu.x;
 else if (dfphd_ndp->lu.x->optyp == LSB) ndp = dfphd_ndp->lu.x->lu.x;
 else { __case_terr(__FILE__, __LINE__); return; }

 if ((syp = __get_sym(ndp->ru.qnchp, cntxt_gblkp->gblk_sytab)) == NULL)
  {
   __gferr(3614, dfpp->dfpfnam_ind, dfpp->dfplin_cnt,
    "defparam %s=%s head %s must be defined in this genblk %s",
    __msgexpr_tostr(__xs, lhsx), __msgexpr_tostr(__xs2, dfpp->dfpxrhs),
   cntxt_gblkp->gblknam, ndp->ru.qnchp);
  }
 /* SJM 04-06-10 - need to substitute in the lhs dfp XMR comma expr selects */ 
 genp_expr_do(dfphd_ndp, do_repl_id_genvar);

//SJM 03-23-10 - LOOKATME? - is it legal to substitute genvars here?
 genp_expr_do(dfpp->dfpxrhs, do_repl_id_genvar);
}

/*
 * ROUTINES TO REPLACE GENVARS IN STATEMENTS AND EXPRESSIONS
 */

/*
 * generate param action (do) routine to process params in one stmt
 * this requires set __inst_mod  
 */
static void genp_1stmt_do(struct st_t *stp, void (*gprm_proc)(struct expr_t *))
{
 int32 fji;
 struct for_t *frp;
 struct qconta_t *qcafs;
 struct st_t *fjstp;

 if (stp == NULL) return;

 switch ((byte) stp->stmttyp) {
  case S_NULL: case S_STNONE: break;
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA:
   genp_expr_do(stp->st.spra.lhsx, gprm_proc);
   genp_expr_do(stp->st.spra.rhsx, gprm_proc);
   break;
  case S_IF:
   genp_expr_do(stp->st.sif.condx, gprm_proc);
   /* AIV 07/15/09 - these need to do the stmt list not one stmt */
   genp_stlst_do(stp->st.sif.thenst, gprm_proc);
   genp_stlst_do(stp->st.sif.elsest, gprm_proc);
   break;
  case S_CASE:
   genp_expr_do(stp->st.scs.csx, gprm_proc);
   /* this also frees default: (maybe just place holder) and list els */
   genp_csitemlst_do(stp->st.scs.csitems, gprm_proc);
   break;
  case S_REPEAT:
   genp_expr_do(stp->st.srpt.repx, gprm_proc);
   /* if after preparation need to free temp. repeat count array */
   /* LOOKATME - why is this only per. inst. stor. place in stmts? */ 
   genp_stlst_do(stp->st.srpt.repst, gprm_proc);
   break;
  case S_FOREVER:
  case S_WHILE:
  case S_DO_WHILE:
   genp_expr_do(stp->st.swh.lpx, gprm_proc);
   genp_stlst_do(stp->st.swh.lpst, gprm_proc);
   break;
  case S_WAIT:
   genp_expr_do(stp->st.swait.lpx, gprm_proc);
   /* free statement list since del. ctrl. points to wait itself */
   genp_stlst_do(stp->st.swait.lpst, gprm_proc);
   /* do not free action statement which is wait itself */
   genp_dctrl_do(stp->st.swait.wait_dctp, FALSE, gprm_proc);
   break;
  case S_FOR:
   frp = stp->st.sfor;
   /* notice for assign already freed */
   genp_expr_do(frp->fortermx, gprm_proc);
   genp_1stmt_do(frp->forinc, gprm_proc);
   genp_stlst_do(frp->forbody, gprm_proc);
   break;
  case S_DELCTRL: genp_dctrl_do(stp->st.sdc, TRUE, gprm_proc); break;
  case S_UNBLK:
   genp_stlst_do(stp->st.sbsts, gprm_proc);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     genp_stlst_do(fjstp, gprm_proc); 
    }
   break;
  case S_FUNCCALL:
  case S_TSKCALL:
   /* AIV 07/20/09 - this can be NULL here task with no args - $finish; */
   if (stp->st.stkc.targs != NULL)
    {
     genp_expr_do(stp->st.stkc.targs, gprm_proc);
    }
   break;
  case S_QCONTA:
   qcafs = stp->st.sqca;
   /* notice for assign already freed */
   genp_expr_do(qcafs->qclhsx, gprm_proc);
   genp_expr_do(qcafs->qcrhsx, gprm_proc);
   break;
  case S_QCONTDEA:
   genp_expr_do(stp->st.sqcdea.qcdalhs, gprm_proc);
   break;
  case S_CAUSE: break;
  case S_DSABLE:
   genp_expr_do(stp->st.sdsable.dsablx, gprm_proc);
   break;
  /* statement added for execution */
  case S_REPSETUP:
   /* union field unused */
//SJM 12-03-08 - can event variables (cause) be genvars - think not
   genp_expr_do(stp->st.scausx, gprm_proc);
   break;
  case S_REPDCSETUP:
   /* SJM 02-28-09 - this really use the causx expr field */
   /* union field unused */
   genp_expr_do(stp->st.scausx, gprm_proc);
   break;
//AIV 05/08/09 - SJM added this name block is this right?????
  case S_NAMBLK: 
   /* DBG remove -- */
   if (stp->st.snbtsk == NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */
   
   /* SJM 05-01-10 - must substitute statement in name blk in line here */
   /* previously was not substituting right */
   /* AIV 07/09/10 - this needs to do the stmt list was only expanded the */
   /* first stmt - need to call the stlst version */
   genp_stlst_do(stp->st.snbtsk->tskst, gprm_proc);
   break;
  case S_INC: case S_DEC:
   genp_expr_do(stp->st.spra.lhsx, gprm_proc);
   break;
//AIV LOOP
  /* AIV 04/08/11 - this should have been S_BREAK */
  case S_BREAK: case S_CONTINUE: case S_RETURN:
   __case_terr(__FILE__, __LINE__);
   break;
  case S_GOTO: break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * generate param action (do) routine to process one delay ctrl record
 */
static void genp_dctrl_do(struct delctrl_t *dctp, int32 stmtlst_to,
 void (*gprm_proc)(struct expr_t *))
{
 /* SJM 05-25-09 for implicit @(*) form, no del expr */
 if (!dctp->implicit_evxlst)
  {
   genp_delexpr_do(dctp->dc_du, dctp->dc_delrep, gprm_proc);
  }
 if (dctp->repcntx != NULL) genp_expr_do(dctp->repcntx, gprm_proc);
 if (stmtlst_to) genp_stlst_do(dctp->actionst, gprm_proc);
}

/*
 * generate param action (do) routine to process one delay expr (list)
 */
static void genp_delexpr_do(union del_u du, word32 drep,
 void (*gprm_proc)(struct expr_t *))
{
 struct paramlst_t *pmp;

 /* DBG remove --*/
 if (drep != DT_CMPLST) __misc_terr(__FILE__, __LINE__);
 /* --- */
 for (pmp = du.pdels; pmp != NULL; pmp = pmp->pmlnxt) 
  {
   genp_expr_do(pmp->plxndp, gprm_proc);
  }
}

/*
 * generate param action (do) routine to process one case item
 * SJM 12-07-08 - this is for case statement not gen case
 */
static void genp_csitemlst_do(struct csitem_t *csip,
 void (*gprm_proc)(struct expr_t *))
{
 for (;csip != NULL; csip = csip->csinxt)
  {
   /* nil expr list always nil for default */
   if (csip->csixlst != NULL) genp_xprlst_do(csip->csixlst, gprm_proc);
   /* if no default, stmt of first nil */
   if (csip->csist != NULL) genp_stlst_do(csip->csist, gprm_proc);
  }
}

/*
 * generate param action (do) routine to process a list of stmts
 */
static void genp_stlst_do(struct st_t *stp, void (*gprm_proc)(struct expr_t *))
{
 for (; stp != NULL; stp = stp->stnxt)
  {
   genp_1stmt_do(stp, gprm_proc);
  }
}

/*
 * generate param action (do) routine to process expr in expr list
 */
static void genp_xprlst_do(struct exprlst_t *xplp,
 void (*gprm_proc)(struct expr_t *))
{
 for (; xplp != NULL; xplp = xplp->xpnxt)
  {
   genp_expr_do(xplp->xp, gprm_proc);
  }
}

/*
 * generate param action (do) routine to process an expression
 *
 * since params only at leaves any tree order works
 * only way multiple different genvars can exist if nested gen fors
 */
static void genp_expr_do(struct expr_t *xp, void (*gprm_proc)(struct expr_t *))
{
 struct expr_t *xp2, *ndx1, *ndx2, *lhsx;
 struct net_t *np;
 int32 bitl, bith, numbits, biti;
 word32 aval, pval;

 /* AIV 04/01/11 - now need to mark as not folded since for loop inline */
 /* may need to fold subexprs which are now constant */
 xp->folded = FALSE;
 /* AIV 09/30/09 - this must be done prior to leave exit */
 /* was never converting these */
 for (xp2 = xp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   genp_expr_do(xp2, gprm_proc);
  }

// SJM 04-11-01 - LOOKATME?? - think XMR or defparam's can never need 
// substitute but for now allow and fix if run into it - not know how to write
 /* SJM 04-11-10 - need to prevent descent since XMRID is a leaf that can */
 /* never be substituted here */
 if (xp->optyp == XMRID) return;

 if (__isleaf(xp))
  {
   /* AIV 04/01/11 - do not fold genvar or for inc on lhs */
   /* if lhs gi = gi + 1 cannot be folded to 1 = 1 +1 */
   if (xp->optyp == ID && xp->lu.sy->sytyp == SYM_N && !xp->x_islhs)
    {
     gprm_proc(xp);
    }
   return;
  }

 /* AIV 04/01/11 - need to handle special expression which can occur on the */
 /* lhs these expression on expecting xp->lu.x->lu.sy to be set latter on */
 /* so must fold these constant cases here on as just a number leaf expr */
 switch ((byte) xp->optyp) {
  case LSB:
   lhsx = xp->lu.x;
   if (lhsx->optyp == ID)
    {
     np = xp->lu.x->lu.sy->el.enp;
     if (np->fold_for_inc || np->nu.ct->p_genvar) 
      {
       biti = __comp_ndx(np, xp->ru.x);
       if (np->nu.ct->p_genvar) aval = np->prm_nva.wp[0]; 
       else aval = (word32) __fold_for_value;
       aval =  rhsbsel_(&(aval), biti);
       __init_xnd(xp);
       __set_numval(xp, aval, 0, 1);
       break;
      }
    }
   if (xp->lu.x != NULL) genp_expr_do(xp->lu.x, gprm_proc);
   if (xp->ru.x != NULL) genp_expr_do(xp->ru.x, gprm_proc);
   break;
  case PARTSEL:
   lhsx = xp->lu.x;
   if (lhsx->optyp == ID)
    {
     np = xp->lu.x->lu.sy->el.enp;
     if (np->fold_for_inc || np->nu.ct->p_genvar) 
      {
       if (np->nu.ct->p_genvar) aval = np->prm_nva.wp[0]; 
       else
        {
         /* DBG remove -- */
         if (!__folding_for_loop) __misc_terr(__FILE__, __LINE__);
         /* ---*/
         aval = (word32) __fold_for_value;
        }
       ndx1 = xp->ru.x->lu.x;
       bitl = __contab[ndx1->ru.xvi];
       ndx2 = xp->ru.x->ru.x;
       bith = __contab[ndx2->ru.xvi];
       numbits = bitl - bith + 1;
       pval = 0;
       __rhspsel(&pval, &aval, bith, numbits);
       __init_xnd(xp);
       __set_numval(xp, pval, 0, numbits);
       break;
     }
    }
   if (xp->lu.x != NULL) genp_expr_do(xp->lu.x, gprm_proc);
   if (xp->ru.x != NULL) genp_expr_do(xp->ru.x, gprm_proc);
   break;
  default:
   if (xp->lu.x != NULL) genp_expr_do(xp->lu.x, gprm_proc);
   if (xp->ru.x != NULL) genp_expr_do(xp->ru.x, gprm_proc);
 }
}

/*
 * action routine (called do) to replace genvar in leaf expre with its value
 * know expr is ID param or will not be called
 */
static void do_repl_id_genvar(struct expr_t *xp)
{
 word32 genv_val;
 struct net_t *np;
 struct expr_t *save_ndx;

 np = xp->lu.sy->el.enp;
 if (!np->nu.ct->p_genvar) return;

 /* SJM 01-14-09 - genvars have value in module with gen src added */
 /* replace net (of parameter type) body with number body */
 /* SJM 12-03-08 - works because leaves only point to d.s. fields */

 /* DBG remove -- */
 if (np->ntyp != N_INT) __misc_terr(__FILE__, __LINE__);
 /* ---*/
    
 /* first initialize to empty */
 /* AIV 07/12/10 - for mulit-dim arrays need to save ndx which is copied */
 /* from expr copy into this xp cannot init to NULL - need to save ndx */
 /* and restore  */
 /* AIV LOOKATME - this may need to not re-init other fields as well */
 save_ndx = xp->next_ndx;
 __init_xnd(xp);
 xp->next_ndx = save_ndx;

 genv_val = np->prm_nva.wp[0]; 
 /* DBG remove -- */
 if (np->prm_nva.wp[1] != 0) __misc_terr(__FILE__, __LINE__);
 /* ---*/
 /* this adds genv val to shared con table if needed */
 __set_numval(xp, genv_val, 0, WBITS);
}

/*
 * fold a given net value in the expression
 * currently just used for for loop inlining
 */
extern void __set_expr_fold_value_stlst(struct st_t *stp)
{
 genp_stlst_do(stp, do_repl_id_forincvar);
}

/*
 * substitute constant for loop value in the expression similiar to 
 * generate substitute
 */
static void do_repl_id_forincvar(struct expr_t *xp)
{
 struct net_t *np;
 struct expr_t *save_ndx;

 np = xp->lu.sy->el.enp;
 if (!np->fold_for_inc) return;

 /* DBG remove -- */
 if (np->ntyp != N_INT && np->ntyp != N_CINT) __misc_terr(__FILE__, __LINE__);
 /* ---*/
    
 /* first initialize to empty */
 save_ndx = xp->next_ndx;
 __init_xnd(xp);
 xp->next_ndx = save_ndx;

 /* DBG remove -- */
 if (!__folding_for_loop) __misc_terr(__FILE__, __LINE__);
 /* ---*/
 /* this adds genv val to shared con table if needed */
 __set_numval(xp, (word32) __fold_for_value, 0, INTBITS);
 /* ints always signed */
 xp->has_sign = TRUE;
}

/*
 * action proc (do) to add a gen param use (sensitivity) element to global list
 * know expr is ID param or will not be called
 */
static void do_addto_gsens_lst(struct expr_t *xp)
{
 struct gen_sens_t *gsp;
 struct net_t *np;

 np = xp->lu.sy->el.enp;
 /* genvars not in sensivity list - since only internally to gen blk changed */
 if (np->nu.ct->p_genvar) return; 
 /* local params never change so do not add */
 if (np->nu.ct->p_locparam) return; 

 /* if param already in list, do not add */
 for (gsp = __gen_sens_hd; gsp != NULL; gsp = gsp->gsenxt)
  {
   if (gsp->gsen_prmnp == np) return;
  }
 /* alloc new record */
 gsp = (struct gen_sens_t *) __my_malloc(sizeof(struct gen_sens_t));
 gsp->gsen_prmnp = np;
 gsp->gsen_owp = NULL;
 gsp->gsenxt = NULL;

 /* add to list */
 if (__gen_sens_hd == NULL) __gen_sens_hd = __gen_sens_tail = gsp;
 else
  {
   __gen_sens_tail->gsenxt = gsp;
   __gen_sens_tail = gsp;
  }
}


/*
 * PARAMETERIZED ROUTINRES TO PROCESS GEN NETS
 */

/*
 * routine to mark symbols that need to be moved from gen blk local
 * symbol table to mgen sym table with gen blk qualified path scope prefix
 *
 * SJM 07-21-09 - this routine had a number of problems - the is leaf code
 * was wrong now using pattern of dcl 1cell hiconn undecl that also had
 * a minor bug involving not declaring undeclared indices in multi-dimensional
 * selects - most serious problem here was always declaring as gen local - was
 * wrongly not checking the decl bit
 */
static void mark_declnet_expr_syms(struct expr_t *ndp, struct genblk_t *gblkp)
{
 struct net_t *np;
 struct sy_t *syp;
 struct expr_t *ndp2;

 switch ((byte) ndp->optyp) {
  case NUMBER: case REALNUM: case OPEMPTY: break;
  /* ignore globals */
  case GLBREF: break;
  case ID:
   syp = ndp->lu.sy;
   if (syp->sydecl || syp->sytyp != SYM_N) break;

   np = syp->el.enp;
   /* must not implicitly declare I/O port */
   if (np->iotyp != NON_IO) break;
   if (np->n_isaparam) break;

   /* SJM 03-15-09 for multiple uses can just re-mark */
   np->nsym->gen_add_mstab = TRUE;
   np->nsym->gen_net_impldecl = TRUE;
   break;
  default:
   /* SJM 07-21-09 - was not decl implict undecl wire in multi-dim sels */
   for (ndp2 = ndp->next_ndx; ndp2 != NULL; ndp2 = ndp2->next_ndx) 
    {
     mark_declnet_expr_syms(ndp2, gblkp);
    }
   if (ndp->lu.x != NULL) mark_declnet_expr_syms(ndp->lu.x, gblkp);
   if (ndp->ru.x != NULL) mark_declnet_expr_syms(ndp->ru.x, gblkp);
 }
}

/*
 * ROUTINES TO BUILD GENERATE SCOPE NAMES
 */

/*
 * build a qualified generate scope name (prefix) 
 */
extern char *__bld_gen_scope_nam(char *s, struct genblk_t *gblkp)
{
 struct genblk_t *gblkp2;
 struct symtab_t *sytp;
 char snam[RECLEN], s1[RECLEN], s2[RECLEN];

 /* for generate items in generate regions, top item has no gen scope name */
 if (gblkp == NULL)
  {
   strcpy(s, ""); 
   return(s);
  }

 /* build from last component to first */
 /* SJM 03-07-09 - old naming algorithm was wrong - gen blocks need the */
 /* gen for indices but module items just have gen src named appended */
 /* xpnd copy1 gen blk handled adding the range if inside a gen for */
 strcpy(snam, gblkp->gblknam);

 /* SJM 03-07-09 - if the path name has gen var indices now already part */
 /* of block name */ 
 /* SJM 02-16-10 - must trace up through gblk symtabs now to bld scope nam */
 for (sytp = gblkp->gblk_sytab->sytpar; sytp != NULL; sytp = sytp->sytpar)
  {
   if (sytp->gblkofsyt == NULL) break;

   gblkp2 = sytp->gblkofsyt;
   /* put on front */
   strcpy(s1, gblkp2->gblknam);
   strcpy(s2, s1);
   strcat(s2, ".");
   strcat(s2, snam);  
   strcpy(snam, s2);
  }
 strcpy(s, snam);
 return(s);
}

/*
 * ROUTINES TO CREATE UNIQUE GLOBAL GEN BLK NAME WHEN ACTUALLY ADDED TO SRC  
 */

/*
 * routine to add 0's to front of (if present) numeric suffix
 *
 * gen blk label names are implicitly in mod level symbol tab 
 * if conflict with non gen mod sym's or other gen labels, this
 * routine makes unique
 *
 * needed because with gen constructs (but not from outside) gen labels
 * produce a sort of xmr
 */
static void try_fix_genblk_nam_conflict(struct genblk_t *gblkp,
 struct mod_t *mdp)
{
 struct sy_t *syp;
 char s1[RECLEN];
 
 /* look in both mod sym tab for conflict */
 if (__get_sym(gblkp->gblknam, mdp->msymtab) == NULL
  && __get_sym(gblkp->gblknam, mdp->mgen_symtab) == NULL)
  {
   /* no conflict - just add to mod gen item sym tab for future checking */
do_blk_decl:
   /* SJM 03-26-11 - only way for gen blk to be in mgen symtab */
   syp = __decl_sym(gblkp->gblknam, mdp->mgen_symtab);
   syp->sytyp = SYM_LGB;

   /* SJM 03-27-11 - can't set e gblkp here because does not get copied */
   syp->syfnam_ind = gblkp->genblk_fnam_ind;
   syp->sylin_cnt = gblkp->genblk_lin_cnt;
   return;
  }
 /* have conflict must add leading 0s to name until no conflict */
 /* DBG remove --- */
 if (gblkp->gblknam == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 strcpy(s1, gblkp->gblknam);
 fix_gen_msytab_conflict(s1, mdp);
 __my_free(gblkp->gblknam, strlen(gblkp->gblknam) + 1);
 gblkp->gblknam = __pv_stralloc(s1);
 goto do_blk_decl;
}

/*
 * add leading 0s until have unique module level symbol table label name
 */
static void fix_gen_msytab_conflict(char *s1, struct mod_t *mdp)
{
 char *chp;
 char s2[RECLEN], suffix[RECLEN];

 chp = &(s1[strlen(s1) - 1]);
 while (isdigit(*chp))
  {
   chp--;
   /* DBG remove --- */ 
   if (chp == s1) __misc_terr(__FILE__, __LINE__);
   /* --- */
  }
 /* chp points to start of digit suffix, if there is one */
 chp++;
 if (*chp == '\0')
  {
   /* case 1: no digits suffix at end */
   strcpy(s2, s1); 
   for (;;)
    {
     strcat(s2, "0");
     if (__get_sym(s2, mdp->msymtab) == NULL
      && __get_sym(s2, mdp->mgen_symtab) == NULL) break;
    }
   strcpy(s1, s2);
   return;
  }
 /* either chp points to first blk char before ending digit string or */
 /* malformed (error) all digits in name */
 strcpy(suffix, &(chp[1]));
 strncpy(s2, s1, chp - s1 + 1); 
}

/*
 * ROUTINE TO COLLECT ALL GENS AND ADD TO MODS VARIOUS NET LIST ELEMENTS
 */

/*
 * gather and link in all gen items for
 *
 * SJM 05-31-10 - with new algorithm only called if mod has gen items 
 */
static void gather_add_1mod_gened_items(struct mod_t *mdp)
{
 __push_wrkitstk(mdp, 0);

 __gitems_hd = __gitems_tail = NULL;
 __gref_gitems_hd = __gref_gitems_tail = NULL;
 __dfp_gitems_hd = __dfp_gitems_tail = NULL;
 bld_1mod_gitem_list();
 mv_genitems_into_mod();
 /* SJM 05-04-10 - if any arrays of g/i moved in, must xpnd and rebld */
 if (mdp->m_gia_in_gblks) rebld_1mod_g_and_i_arr(mdp);

 __pop_wrkitstk();

 /* DBG remove -- */
 if (__debug_flg)
  {
   __dbg_msg(
    " =======  DUMPING MOD SRC AFTER GEN GATHER FOR %s (fixup round %d)\n",
    mdp->msym->synam, __fixup_round);
   __dmp_mod(stdout, mdp, FALSE);
   __dbg_msg(" =======  END OF SRC DMP\n");
  }
}

/*
 * routine to gather all genitems that will be added to mod into a list
 */
static void bld_1mod_gitem_list(void)
{
 struct genitem_t *gip;

 for (gip = __inst_mod->mgenitems; gip != NULL; gip = gip->geninxt)
  {
   add_genitems_from1_genitem(gip);
  }
}

/*
 * add one gen item to one modules non meta gen item list
 *
 * this routine gathers non meta gen items - gen items that are moved
 * into mod net list
 */ 
static void add_genitems_from1_genitem(struct genitem_t *gip)
{
 int32 gti;
 struct gen_for_t *gforp;
 struct gen_if_t *gifp;
 struct gen_case_t *gcasp;

 switch (gip->gityp) {
  case GI_GBLK:
   add_genitems_from1_genblk(gip->giu.gi_gblkp);
   break;
  case GI_GFOR:
   gforp = gip->giu.gi_gforp;
   for (gti = 0; gti < gforp->ngenblks; gti++)
    {
     /* SJM 03-04-09 - gen table may be sparse */ 
     if (gforp->gentab[gti] == NULL) continue;

     add_genitems_from1_genblk(gforp->gentab[gti]);
    }
   break;
  case GI_GIF:
   gifp = gip->giu.gi_gifp;
   /* SJM 03-07-09 - if empty gen if, i.e. nothing gened, nothing to do */
   if (gifp->ngenblks == -1) break;

   /* generate anything - exactly one gen blk (list of gen items) gened */
   if (gifp->ngenblks != 1) __misc_terr(__FILE__, __LINE__); 
   add_genitems_from1_genblk(gifp->gentab[0]);
   break;
  case GI_GCASE:
   gcasp = gip->giu.gi_gcasp;
   /* SJM 03-07-09 - if empty gen case, i.e. nothing gened, nothing to do */
   if (gcasp->ngenblks == -1) break;

   /* DGB remove -- */
   if (gcasp->ngenblks != 1) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   add_genitems_from1_genblk(gcasp->gentab[0]);
   break;
  case GI_GREF: case GI_DFPARM:
   /* SJM 04-07-10 - already moved */
   break;
  default:
   /* SJM 04-03-10 - gref genitems must be in separate list */ 
   if (__gitems_hd == NULL) __gitems_hd = gip;
   else __gitems_tail->gened_nxt = gip;
   __gitems_tail = gip;
   gip->gened_nxt = NULL;
 }
}

/*
 * add gen items inside one genblk to gen item list
 *
 * also adds nets (in gen blk declared or implicitly declared from use)
 * nets to mod's mgen sytab
 */
static void add_genitems_from1_genblk(struct genblk_t *gblkp)
{
 int32 syi;
 struct symtab_t *sytp;
 struct sy_t *syp;
 struct genitem_t *gip;

 /* SJM 03-15-09 - add nets (from their syms) for this gen blk */
 sytp = gblkp->gblk_sytab;
 for (syi = 0; syi < sytp->numsyms; syi++)
  {
   syp = sytp->stsyms[syi];
   if (syp->sytyp != SYM_N) continue;
   /* for nets not implicitly used or declared in expanded gen blk, no move */ 
   if (!syp->gen_add_mstab) continue;

   mv_gblk_nsym_to_mod_mgen_sytab(syp, gblkp);
  }

 if (gblkp->gblk_tsks != NULL)
  {
   mv_gblk_tsks_to_mod(gblkp);
  }

 /* SJM 04-07-10 - changed to add top down - is there are problem? */

 /* SJM 04-03-10 - gref genitems are on separate list */ 
 /* gref gen items only in gen blks */
 for (gip = gblkp->gref_gitems; gip != NULL; gip = gip->geninxt)
  {
   /* SJM 09-06-11 - MAYBE FIXME? - if syntax err defparam grefs here */
   /* must omit */
   if (gip->giu.gi_grp->gr_defparam) continue;

   if (__gref_gitems_hd == NULL) __gref_gitems_hd = gip;
   else __gref_gitems_tail->gened_nxt = gip;
   __gref_gitems_tail = gip;
   gip->gened_nxt = NULL;
  }

 /* SJM 04-07-10 - defparam genitems are on separate list */ 
 /* defparam gen items only in gen blks */
 for (gip = gblkp->dfp_gitems; gip != NULL; gip = gip->geninxt)
  {
   if (__dfp_gitems_hd == NULL) __dfp_gitems_hd = gip;
   else __dfp_gitems_tail->gened_nxt = gip;
   __dfp_gitems_tail = gip;
   gip->gened_nxt = NULL;
  }

 for (gip = gblkp->gitems; gip != NULL; gip = gip->geninxt)
  {
   add_genitems_from1_genitem(gip);
  }
}

/*
 * routine to add one gen blk expanded var decl or implicitly decl by use
 * net to mod's mgen sytab 
 * 
 * only get here if 
 */  
static void mv_gblk_nsym_to_mod_mgen_sytab(struct sy_t *nsyp,
 struct genblk_t *gblkp)
{
 struct net_t *np;
 struct sy_t *syp2;
 struct tnode_t *tnp;
 char genscop_prefix[RECLEN], s1[RECLEN], s2[RECLEN];

 np = nsyp->el.enp;
 /* DBG remove -- */
 if (np->iotyp != NON_IO) __misc_terr(__FILE__, __LINE__);
 /* --- */

 __bld_gen_scope_nam(genscop_prefix, gblkp);
 /* DBG remove -- */
 if (strcmp(genscop_prefix, "") == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 sprintf(s1, "%s.%s", genscop_prefix, np->nsym->synam);

 /* if already moved to mgen sym tab, nothing to do - providing it is a net */
 /* can only by declared when expanding or from gen blk var decl */ 
 /* also implicit decl here no new info */
 if ((syp2 = __get_sym(s1, __inst_mod->mgen_symtab)) != NULL)  
  {
   if (syp2->sytyp != SYM_N)
    {
     if (np->nu.ct->n_impldecl) strcpy(s2, "implicitly ");
     else strcpy(s2, "");

     __gferr(3608, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
      "net %s %sdeclared in generate block %s conflicts with %s symbol declared at %s",
      s1, s2, gblkp->gblknam, __to_sytyp(__xs, syp2->sytyp),
      __bld_lineloc(__xs2, syp2->syfnam_ind, syp2->sylin_cnt));
     return;
    }
   /* DBG remove -- */
   if (!syp2->sydecl) __misc_terr(__FILE__, __LINE__);
   /* --- */
   return;
  }

 /* SJM 03-12-09 - code for moving symbol to mod's mgen symbol table */
 /* trick is that all the expr's in the pre expanded gen point to syp */
 /* in local sym tab (needed because may not never be gened) */
 /* so need to add an avl tnode and point the node to the gen blk sy tab */

 /* net now copied into nnp - symbol for now goes into mod mgen sym tab */
 tnp = __vtfind(s1, __inst_mod->mgen_symtab);
 /* DBG remove */
 if (!__sym_is_new) __misc_terr(__FILE__, __LINE__);
 /* --- */
 __inst_mod->mgen_symtab->numsyms++;

 /* algorithm here is to add new avl form sym tab tree node but keep same */
 /* symbol so expr nodes continue to point to the sym - name is changed*/

 /* SJM 03-16-09 - BEWARE must not alloc new sym but add already declared */
 tnp->ndp = nsyp;
 //AIV - cannot free this because is inside of malloc chunk in nfbig_alloc???
 // __my_free(syp->synam, strlen(syp->synam) + 1);
 nsyp->synam = __pv_stralloc(s1);

 if (nsyp->gen_net_impldecl)
  {
   nsyp->sydecl = TRUE;
   nsyp->sy_impldecl = TRUE;
   np->iotyp = NON_IO;
   /* type for undeclared is default net types */
   np->ntyp = __dflt_ntyp;
   np->nu.ct->n_iotypknown = TRUE;
   np->nu.ct->n_rngknown = FALSE;
   np->nu.ct->n_impldecl = TRUE;
   /* AIV 05/17/11 - LRM states that `default_nettype none */
   /* means that all wires must be defined no implicit */
   if (__dflt_ntyp_is_none)
    {
     __pv_ferr(3006, "wire '%s' %s cannot be implicitly defined with use of '`default_nettype none' - must explicity define wire",
     nsyp, __bld_lineloc(__xs2, nsyp->syfnam_ind, nsyp->sylin_cnt));
    }
   np->nu.ct->n_wirtypknown = TRUE;

   __gfinform(3013, nsyp->syfnam_ind, nsyp->sylin_cnt,
    "%s %s implicitly declared from inst/gate expand of generate block %s\n",
    __to_wtnam(__xs, np), np->nsym->synam, gblkp->gblknam);
  }

 /* SJM 03-13-09 impl decl flag causes width to be set later */

 /* fix cross linking */
 np->nsym = nsyp;
 /* SJM 03-18-09 - change net's syt of net to mgen symtab */
 np->syt_of_net = __inst_mod->mgen_symtab;
 nsyp->el.enp = np;
}

/*
 * routine to add one gen blk expanded task sym to * mods mgen sytab with
 * right fully qualified name
 */  
static void mv_gblk_tsks_to_mod(struct genblk_t *gblkp)
{
 struct task_t *tskp, *last_tskp;
 struct sy_t *syp2;
 struct symtab_t *par_sytp;
 struct tnode_t *tnp;
 char genscop_prefix[RECLEN], s1[RECLEN];

 /* move gen blk tasks since known gened (selected) onto end of mod tsk list */
 last_tskp = NULL;
 for (tskp = __inst_mod->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   last_tskp = tskp;
  }
 if (last_tskp == NULL) __inst_mod->mtasks = gblkp->gblk_tsks;
 else last_tskp->tsknxt = gblkp->gblk_tsks;

 /* now move the labeled block task names into mod's mgen for later move */
 last_tskp = NULL;
 for (tskp = gblkp->gblk_tsks; tskp != NULL; tskp = tskp->tsknxt)
  {
   /* now can check to make sure task no under a gen for */
   if (tskp->tsksyp->sytyp == SYM_TSK || tskp->tsksyp->sytyp == SYM_F)
    {
     /* SJM 02-07-11 - for tasks and functions need the gen blk prefix */
     __bld_gen_scope_nam(genscop_prefix, gblkp);
     sprintf(s1, "%s.%s", genscop_prefix, tskp->tsksyp->synam);
     /* DBG remove -- */
     if (strcmp(genscop_prefix, "") == 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
     if (gblk_under_genfor(gblkp))
      { 
       __gferr(3619, gblkp->genblk_fnam_ind, gblkp->genblk_lin_cnt,
        "task %s in generate block %s illegal - tasks can not be generated under generate for loops",
        s1, gblkp->gblknam);
       /* remove the task from inst's task list */

       /* SJM 04-09-11 - if errors last tskp can be nil */
       if (last_tskp == NULL) gblkp->gblk_tsks = tskp->tsknxt;
       else last_tskp->tsknxt = tskp->tsknxt;

//SJM 05-04-10 - FIXME? - should free task storage here
       continue;
      }
    }
   else if (tskp->tsksyp->sytyp == SYM_LB)
    {
     /* DBG remove -- */ 
     if (tskp->tsksymtab->sytpar == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* SJM 02-07-11 - only need the gen blk prefix for labeled blocks that */
     /* get moved to top modules top level - contained labeled blocks */
     /* still have their local name */
     if (tskp->tsksymtab->sytpar->gblkofsyt == NULL) continue;

     __bld_gen_scope_nam(genscop_prefix, gblkp);
     sprintf(s1, "%s.%s", genscop_prefix, tskp->tsksyp->synam);
     /* DBG remove -- */
     if (strcmp(genscop_prefix, "") == 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
    }
   else __case_terr(__FILE__, __LINE__);
   
   /* SJM 05-01-10 - task definitions can't be in gen for loops so do not */
   /* need to substite genvars - for labeled blocks substituted with stmt */
   
   /* know name can't conflict - just checking */
   syp2 = __get_sym(s1, __inst_mod->mgen_symtab);
   /* DBG remove -- */
   if (syp2 != NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */

   tnp = __vtfind(s1, __inst_mod->mgen_symtab);
   /* DBG remove */
   if (!__sym_is_new) __misc_terr(__FILE__, __LINE__);
   /* --- */
   __inst_mod->mgen_symtab->numsyms++;

   /* SJM 03-16-09 - BEWARE must not alloc new sym but add already declared */
   tnp->ndp = tskp->tsksyp;

   //AIV - cannot free this because is inside of malloc chunk in nfbig_alloc???
   // __my_free(syp->synam, strlen(syp->synam) + 1);
   /* SJM 04-04-11 - task name must be gen blk qualified name even in */
   /* gblk sytab */
   tskp->tsksyp->synam = __pv_stralloc(s1);
   tskp->tsksyp->gen_add_mstab = TRUE;

   /* SJM 02-07-11 - only need to link in t/f or lb directly in gen blk*/
   /* DBG remove -- */   
   par_sytp = tskp->tsksymtab->sytpar;
   if (par_sytp->sypofsyt != NULL || par_sytp->gblkofsyt == NULL)
    __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* SJM 05-11-10 - when move task into module, task sytab par is now mod */
   /* for labeled blks, only change if parent is genblk */
   /* SJM 02-07-11 - need to link task (either gened t/f not in genfor or */
   /* generated top mod level labeled block */
   tskp->tsksymtab->sytpar = __inst_mod->msymtab;
   /* link on front - order does not matter */
   if (__inst_mod->msymtab->sytofs != NULL)
    {
     tskp->tsksymtab->sytsib = __inst_mod->msymtab->sytofs;
    }
   __inst_mod->msymtab->sytofs = tskp->tsksymtab;

   /* need to cross link tsk syms in mgen so can be linked in mod */ 
   /* SJM 02-07-11 - task sym is temporarily into mgen sytab until merged */
   tskp->tsksyp->el.etskp = tskp;

   last_tskp = tskp;
  }
}

/*
 * return T if a gen blk is in a genb for loop directly or an above gen blk is
 */
static int32 gblk_under_genfor(struct genblk_t *gblkp)
{
 struct genblk_t *gblkp2;
 struct symtab_t *sytp;

 if (gblkp->gblk_in_gfor) return(TRUE);
 for (gblkp2 = gblkp;;)
  {
   if ((sytp = gblkp2->gblk_sytab->sytpar) == NULL) break;

   /* gen blk that is mod gen item's parent is mod sym tab */
//SJM 05-05-10 - LOOKATME - is this right - maybe should be nil if gen blks
//are really mod's 
   if ((gblkp2 = sytp->gblkofsyt) == NULL) break;

   if (gblkp2->gblk_in_gfor) return(TRUE);
  }
 return(FALSE);
}

/*
 * add a gen module item to end of its module item type list
 */
static void mv_genitems_into_mod(void)
{
 int32 add_numgis, numis, numgs, ii, gi;
 struct genitem_t *gip;
 struct conta_t *cap, *last_cap;
 struct ialst_t *ialp, *last_ialp;
 struct inst_t *newitab, *ip;
 struct srcloc_t **newsrcloctab;
 struct gate_t *newgtab, *gp;

 /* add contas */
 /* v fixup2 sets mod's number of contas - do not need to set here */
 last_cap = NULL;
 for (cap = __inst_mod->mcas; cap != NULL; cap = cap->pbcau.canxt)
  last_cap = cap;
 for (gip = __gitems_hd; gip != NULL; gip = gip->gened_nxt) 
  {
   if (gip->gityp != GI_CONTA) continue;

   cap = gip->giu.gi_cap;
//SJM 03-14-09 - LOOKATME? - how free genitems (genblk) when all realized? 
   if (last_cap == NULL) __inst_mod->mcas = cap;
   else last_cap->pbcau.canxt = cap;
   last_cap = cap;
  }

 /* add nets */
 /* SJM 03-14-09 - nets already added to gen blk's sym tab - nothing to do */

 /* add initial/always */
 last_ialp = NULL;
 for (ialp = __inst_mod->ialst; ialp != NULL; ialp = ialp->ialnxt)
  last_ialp = ialp;
 for (gip = __gitems_hd; gip != NULL; gip = gip->gened_nxt) 
  {
   if (gip->gityp != GI_INITALW) continue;

   ialp = gip->giu.gi_ialp;
   if (last_ialp == NULL) __inst_mod->ialst = ialp;
   else last_ialp->ialnxt = ialp;
   last_ialp = ialp;
  }

 /* add gen item insts to bottom of minsts */
 add_numgis = count_genitems(GI_INST);
 numis = __inst_mod->minum + add_numgis;
 if (numis > 0)
  {
   newitab = (struct inst_t *) __my_malloc(numis*sizeof(struct inst_t));

   /* SJM 03-12-09 - table of ptrs to tab of per inst mods hiconn locs */
   /* port connecting exprs in src - for where each hiconn on different line */
   /* alloc the pointers */
   newsrcloctab = (struct srcloc_t **)
    __my_malloc(numis*sizeof(struct srcloc_t *));

   /* fill from old minsts tab and per contained inst hiconn pin locs */ 
   for (ii = 0; ii < __inst_mod->minum; ii++)
    {
     newitab[ii] = __inst_mod->minsts[ii];
     /* AIV 05/25/11 - must shut off tracking of split modules - that is */
     /* cannot reuse already split modules due to generate, was freeing */
     /* below which was getting into trouble when latter checking for */
     /* splitting with the same parameter values */
     __inst_mod->minsts[ii].imsym->el.emdp->m_maybe_gened = TRUE;
     /* this is a ptr to hiconn pin connect records for each port of inst */
     /* since just growing just point to old */
     newsrcloctab[ii] = __inst_mod->iploctab[ii];
    }
   /* AIV 08/24/11 - must just off entire sub tree's pnd splitting as well */
   turn_off_pndsplitting_reuse(__inst_mod);

   /* fill bottom with new insts */
   ii = __inst_mod->minum;
   for (gip = __gitems_hd; gip != NULL; gip = gip->gened_nxt) 
    {
     if (gip->gityp != GI_INST) continue;

     /* get instance and set src loc - internal gen saves */
     ip = gip->giu.gi_igp->ip;

     /* SJM 06-01-10 - must always split mod of gened instances because */
     /* if gen more than one may need to change IS parameter rng but do not */
     /* know old range so must split - 06-26-10 - NOT QUITE RIGHT */
     /* SJM 06-09-10 - was splitting too often - now only split if passing */
     /* down params has mod has params - YES */

//    SJM 06-26-10 - this test was totally wrong - usually split but in some
//    case did not split when needed to
//     if (ip->ip_explicit || ip->pprm_explicit) ip->i_pndsplit = TRUE;    
//     SJM 06-26-10 - if inst has any pound params to first approximation splt
//     reason is that parameter expr may have genvar that is substituted by
//     here - would need mechanism to know if ipxprtab had genvar substituted
//     but no where to store - for now conservation always if mod has params
//     best
     if (ip->ipxprtab != NULL)
      {
       struct mod_t *imdp;

       /* DBG remove -- */
       imdp = ip->imsym->el.emdp;
       if (imdp->mprmnum == 0) __misc_terr(__FILE__, __LINE__);
       /* --- */
       ip->i_pnddefsplit = TRUE;
      }
//     SJM 06-27-10 - altera mf model has one level downward defps in place
//     of pound params - that also requires splitting 
//     many other possible defparam cases into the module - but not sure how
//     to find so only handle altera case for now
//     can't check if this inst has params here - just mark all because 
//     it is possible to have say 10 insts gened with defparams into only some
     if (__dfp_gitems_hd != NULL) ip->i_pnddefsplit = TRUE;
      
     /* SJM 04-06-09 - need to inc after both assigns */
     newitab[ii] = *ip;
     /* SJM 03-14-09 - this is moving the ptr to imod port num src loc recs */
     newsrcloctab[ii] = gip->giu.gi_igp->srclocp;
     ii++;
    }
   
   /* SJM 05-29-09 - need to also fix the inst cross linked symbols */
   for (ii = 0; ii < numis; ii++)
    {
     newitab[ii].isym->el.eip = &(newitab[ii]);
    }

   __my_free(__inst_mod->minsts, __inst_mod->minum*sizeof(struct inst_t));
   /* SJM 03-12-09 - this is freeing the ptrs - pointed to moved */
   __my_free(__inst_mod->iploctab, __inst_mod->minum*sizeof(struct srcloc_t *));
   __inst_mod->minsts = newitab;
   __inst_mod->iploctab = newsrcloctab;
   __inst_mod->minum = numis; 
  }

 /* add gen item gates to bottom of mgates */
 add_numgis = count_genitems(GI_GATE);
 numgs = __inst_mod->mgnum + add_numgis;
 if (numgs > 0)
  {
   newgtab = (struct gate_t *) __my_malloc(numgs*sizeof(struct gate_t));
   /* fill from old mgates tab */ 
   for (gi = 0; gi < __inst_mod->mgnum; gi++)
    {
     newgtab[gi] = __inst_mod->mgates[gi];
    }
   /* fill bottom with new */
   gi = __inst_mod->mgnum;
   for (gip = __gitems_hd; gip != NULL; gip = gip->gened_nxt) 
    {
     if (gip->gityp != GI_GATE) continue;

     gp = gip->giu.gi_gp;
     newgtab[gi++] = *gp;
    }

   /* SJM 05-29-09 - need to also fix the gates cross linked symbols */
   for (gi = 0; gi < numgs; gi++)
    {
     newgtab[gi].gsym->el.egp = &(newgtab[gi]);
    }

   __my_free(__inst_mod->mgates, __inst_mod->mgnum*sizeof(struct gate_t));
   __inst_mod->mgates = newgtab;
   __inst_mod->mgnum = numgs; 
  }


 /* finally move mod gen syms used in new src into mod symbol table */
 /* SJM 01-16-09 - if nothing gened, then empty symbol tab - nothing to do */
 if (__inst_mod->mgen_symtab->numsyms != 0)
  {
   mv_gened_symbols_to_modsymtab(__inst_mod);
  }

 /* SJM 03-25-10 - can't move and rebld defparam lhs gref's until sym added */
 chk_1mod_genblk_defparams();
 mv_gblk_dfps_to_mod();

 /* SJM 03-30-10 - since now dfps work - can move in grefs after since */
 /* not resolved until after gen processing done - gen blk structure */
 /* will still be around to fix up names */ 
 /* SJM 08-30-11 - first move gref on lhs of defparams in gen, then normal */
 /* grefs */ 
 mv_gblk_grefs_to_mods_grtab();
}

/* AIV 08/22/11 - this needs to turn on the flag for the entire instance */
/* tree - all instances below this generated module cannot reuse */
/* the module parameter not splitting code */
static void turn_off_pndsplitting_reuse(struct mod_t *mdp)
{
 int32 ii;
 struct inst_t *ip;
 struct mod_t *imdp;

 /* just mark m_maybe_gened for each instance below this mod */
 mdp->m_no_param_match = TRUE;
 for (ii = 0; ii < mdp->minum; ii++)
  {
   ip = &(mdp->minsts[ii]); 
   imdp = ip->imsym->el.emdp;
   imdp->m_no_param_match = TRUE;
   turn_off_pndsplitting_reuse(imdp);
  }
}

/*
 * count gen items of a given non meta gen item type 
 */  
static int32 count_genitems(int32 match_gityp)
{
 int32 numgis;
 struct genitem_t *gip;

 for (numgis = 0, gip = __gitems_hd; gip != NULL; gip = gip->gened_nxt)
  {
   if (gip->gityp == match_gityp) numgis++;
  }
 return(numgis);
}

/*
 * routine to move gen
 */  
static void mv_gblk_grefs_to_mods_grtab(void)
{
 int32 n_gblk_grefs, n_omd_grefs, gri;
 struct genitem_t *gip;
 struct gref_t *ogrp, *ngrp, *ngrtab, *ogrtab;

 n_gblk_grefs = count_gref_genitems();
 /* if no gen blk grefs in mod, nothing to do */
 if (n_gblk_grefs == 0) return;

 n_omd_grefs = __inst_mod->mgrnum;

//SJM 03-30-10??? - could use realloc here - but this better for debugging
 ngrtab = (struct gref_t *)
  __my_malloc((n_omd_grefs + n_gblk_grefs)*sizeof(struct gref_t));

 ogrtab = __inst_mod->mgrtab;
 if (n_omd_grefs > 0)
  {
   memcpy(ngrtab, ogrtab, n_omd_grefs*sizeof(struct gref_t));
  } 

 /* for all the old grefs since grtab moved, point expr to new - xpr has */
 /* not moved */
 for (gri = 0; gri < n_omd_grefs; gri++)
  {
   ngrp = &(ngrtab[gri]);
   ngrp->gxndp->ru.grp = ngrp;
  }

 gri = n_omd_grefs;
 /* SJM 04-04-10 - routine only see gen items on separate list */
 for (gip = __gref_gitems_hd; gip != NULL; gip = gip->gened_nxt) 
  {
   /* DBG remove -- */
   if (gip->gityp != GI_GREF) __misc_terr(__FILE__, __LINE__);
   /* -- */
   
   ogrp = gip->giu.gi_grp;
   ngrp = &(ngrtab[gri]);
   /* notice this is image copy since no longer using gen item grefs */
   /* exprs just are pointed to by gen items but were always in mod */
   /* expr area */
   *ngrp = *ogrp;
   /* SJM 04-06-10 - copy is a just a storage location move here - but */
   /* still need to make gref's pointing to expr point to new addr */
//REMOVEME?
   if (ngrp->gxndp == NULL) __misc_terr(__FILE__, __LINE__); 
   ngrp->gxndp->ru.grp = ngrp;
   /* SJM 04-11-10 - change gref so gr sy tab in is now correct mod level */
   ngrp->grsytp = __inst_mod->msymtab;
   gri++;
  }
 /* free the old grtab - but not the contents (i.e. just spliced exprs) */
 if (n_omd_grefs > 0)
  {
   __my_free(ogrtab, n_omd_grefs*(sizeof(struct gref_t)));
  }
 __inst_mod->mgrtab = ngrtab;
 __inst_mod->mgrnum = n_omd_grefs + n_gblk_grefs;
 free_mv_gitem_lst(__gref_gitems_hd);
 __gref_gitems_hd = __gref_gitems_tail = NULL;
}

/*
 * count gref gen items of a given non meta gen item type 
 *
 * SJM 09-03-11 - now only for non defparam gref tab
 */  
static int32 count_gref_genitems(void)
{
 int32 numgis;
 struct genitem_t *gip;

 for (numgis = 0, gip = __gref_gitems_hd; gip != NULL; gip = gip->gened_nxt)
  {
   /* DBG remove --- */
   if (gip->gityp != GI_GREF) __misc_terr(__FILE__, __LINE__);
   /* --- */
   numgis++;
  }
 return(numgis);
}

/*
 * free a mv to mod simple gened nxt gen item list
 *
 * only free the gen item records because used after the contents moved
 */
static void free_mv_gitem_lst(struct genitem_t *gip)
{
 struct genitem_t *gip2;

 for (; gip != NULL;)
  {
   gip2 = gip->gened_nxt;
   __my_free(gip, sizeof(struct genitem_t));
   gip = gip2;
  }
}

/*
 * routine to check defparam in gen blk just before transform and mv into mod
 * know all defparams defined in gen blks or won't be seen here
 */
static void chk_1mod_genblk_defparams(void)
{
 struct genitem_t *gip, *gip2, *last_gip;
 struct dfparam_t *dfpp;

 last_gip = NULL;
 for (gip = __dfp_gitems_hd; gip != NULL; gip = gip2)
  {
   gip2 = gip->gened_nxt;
   dfpp = gip->giu.gi_dfp;

   __sfnam_ind = dfpp->dfpfnam_ind;
   __slin_cnt = dfpp->dfplin_cnt;

   if (!chk_1gblk_dfp(dfpp))
    {
     /* if error, remove from list */
     if (last_gip == NULL) __dfp_gitems_hd = gip2;
     else last_gip->gened_nxt = gip2;

     /* on error free the defparam - compeletly removed from circuit */
     __free_1dfparam(dfpp);
     __my_free(gip, sizeof(struct genitem_t));
    }
   else last_gip = gip;
  }
}

/*
 * preliminary checking of one defp that appeared in a gen blk
 *
 * real checking after move into mod in next pass
 */
static int32 chk_1gblk_dfp(struct dfparam_t *dfpp)
{
 struct gref_t *grp;
 struct xmrcmp_t *xmp;

 /* if 1 component gref, think gref but error caught in normal defp code */
 if (dfpp->dfpxlhs->optyp != GLBREF)
  {
   __sgferr(3618,
    "defparam LHS %s define in gen blk %s is a local defparam - illegal generate block defparam",
    __msgexpr_tostr(__xs, dfpp->dfpxlhs), dfpp->dfp_gblk_in->gblknam);
   return(FALSE);
  }

 grp = dfpp->dfpxlhs->ru.grp;
 /* now checking very early so need to mark the gref as a defparam to start */ 
 grp->gr_defparam = TRUE;

 if (!bld_dfp_xmrcmps(grp)) return(FALSE);
 /* DBG remove --
 if (__debug_flg)
  {
   dbg_dmp_xmrcmptab(grp, grp->gr_xmptab, grp->gr_num_xmps);
  }
 --- */

 /* SJM 04-05-10 - very specific rules for XMR in generate blocks */
 /* checking here may be too stringent */ 
 /* checking for in gen blk downward relative into underneath cone only */
 /* DBG remove -- */
 if (grp->gr_num_xmps <= 0) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 xmp = grp->gr_xmptab[0];
 switch (xmp->xmp_petyp) {
  case XMP_MOD: case XMP_INST:
   __sgferr(3616,
   "defparam LHS %s in generate block %s first component not item defined in generate block - strictly downward only",
      grp->gnam, dfpp->dfp_gblk_in->gblknam);
   grp->gr_err = TRUE;
   return(FALSE);
  case XMP_GBLK:
   if (xmp->xmp_in_sytab->gblkofsyt != dfpp->dfp_gblk_in)
    {
     __sgferr(3617,
      "defparam LHS %s in generate block %s first component generate block %s not defined in it - strictly downward only",
      grp->gnam, dfpp->dfp_gblk_in->gblknam,
      xmp->xmp_in_sytab->gblkofsyt->gblknam);
     grp->gr_err = TRUE;
     return(FALSE);
    }
   break;
    case XMP_INST_INGEN: case XMP_TSK: case XMP_NET_INGEN: case XMP_NET:
//SJM 04-04-10 - not sure if XMR that is just net is possible here - locals 
// not yet found
     break;
    default: __case_terr(__FILE__, __LINE__);
 }
 /* SJM 04-05-10 - if error gr xmp tab free later, only free here if good */
 /* DBG remove -- */
 if (grp->gr_xmptab == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */
 return(TRUE);
}

/*
 * routine to move defparams from one mod that appears in a gen blk 
 * onto end of mod's defp list changed so it looks like after gen it
 * appeared as a normal defparam statement in a mod top level item
 *
 * adds onto end of mod's dfp list after changing to post gen inst 
 * tree - processed as normal defparam then on next pass thru fixup nl
 *
 * defparam will be processed on next fixup nl pass, so no fields set
 *
 * SJM 03-25-10 - must be called after all gen symbols moved to mod's
 * top level sym tab
 *
 * SJM 03-16-10 - new algorithm move defparams in gen blks into dfp list
 * but only for next pass since from now on never seeing defparams in
 * this pass of fixup nl - dfps will be checked and treatd as if in mod
 * so do not need chk lhs defp xpr call here
 *
 * SJM 03-23-10 - move defparams with proper contents (exprs) onto end
 * of defp list for each module - does not work in general - not sure
 * what happens with local defparams when fixup nl is run
 *
 * convert defparam to after gen items moved into designs form and
 * add to mod's normal defparam list - unsets in gen blk fields
 *
 * SJM 04-06-10 - notice this routine just transforms internals of
 * defp struct, it does not change connectivity to rest of net list
 */
// ??? key is that defparams can only be down ward relative - but can go
//    through contained insts - how handle
static void mv_gblk_dfps_to_mod(void)
{
 struct gref_t *grp;
 struct genitem_t *gip;
 struct dfparam_t *dfpp, *last_dfpp;
 char s1[RECLEN];

 last_dfpp = NULL;
 for (dfpp = __inst_mod->mdfps; dfpp != NULL; dfpp = dfpp->dfpnxt)
  { 
   last_dfpp = dfpp;
  } 
 /* all gen related local defps removed before here */
 /* mv all dfps in gen blks in current module to end of mod's defp list */ 
 for (gip = __dfp_gitems_hd; gip != NULL; gip = gip->gened_nxt)
  {
   dfpp = gip->giu.gi_dfp;

   /* def params in gen blks can't be local for now - error else where */
   /* DBG remove -- */
   if (dfpp->dfpxlhs->optyp != GLBREF) __misc_terr(__FILE__, __LINE__);
   /* --- */ 

   /* SJM 03-14-09 - now when expand of gen blk def param setting bit */
   /* and setting path prefix */
   grp = dfpp->dfpxlhs->ru.grp;

   /* SJM 09-03-11 - notice gref no only associated with defp so already */ 
   /* cross linked */
   /* DG remove */
   if (grp != dfpp->dfp_grp) __misc_terr(__FILE__, __LINE__);
   if (grp->gxndp->ru.grp != grp) __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* DBG remove --- */
   if (grp->gxndp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* build the xmr cmps using pre gen fixup inst tree */
   /* SJM 09-07-11 - this is critical must be done in gen world because */
   /* gen's needed for building the initial xmr cmps */
   if (!bld_dfp_xmrcmps(grp))
    {
     grp->gr_err = TRUE;
     continue;
    }

   /* DBG remove --
   if (__debug_flg)
    {
     dbg_dmp_xmrcmptab(grp, grp->gr_xmptab, grp->gr_num_xmps);
    }
   --- */

   /* this fixes gref so next time fixup nl, dfp gets resolved as normal */
   fixup_1dfp_xmrcmps(grp);

   /* DBG remove --
   if (__debug_flg)
    {
     dbg_dmp_xmrcmptab(grp, grp->gr_xmptab, grp->gr_num_xmps);
    }
   --- */

   /* need to fixup defparam lhs expr from fixed gref */
   /* SJM 03-26-10 - key is that know dfp lhs expr and gref are 1-to-1 */
   bld_glbref_xpr_from_xmrcmptab(grp);

   /* SJM 03-26-10 also need to fill gref name and cross linked exprs */
   __my_free(grp->gnam, strlen(grp->gnam) + 1);
   xmrcmptab_to_gnam(s1, grp);
   grp->gnam = __pv_stralloc(s1);

   /* rhs checked when module level def param checked - any gen var */
   /* substitute done before here */
   /* SJM 04-04-10 - now that have normal gref with no gblk components */
   /* - gblk world gone must change flags to indicate normal */
   dfpp->dfp_in_gen = FALSE;
   dfpp->dfp_was_in_gen = TRUE;
   /* SJM 09-07-11 - this was misleading FALSE that came up as nil */
   /* nil is right because defparams no longer in gen blks when moved in */
   grp->gr_gblk_in = NULL;
   grp->gr_has_genitem = FALSE;
    
   /* SJM 09-07-11 - all gen world defparam processing done - now need to do */
   /* old gref copy into non gen world defparam grefs */
   /* this is crucial step from old code in moving into gen src mod world */
   grp->grsytp = __inst_mod->msymtab;

   /* add to end */
   if (last_dfpp == NULL) __inst_mod->mdfps = dfpp;
   else last_dfpp->dfpnxt = dfpp;
   last_dfpp = dfpp;
  }
 free_mv_gitem_lst(__dfp_gitems_hd);
 __dfp_gitems_hd = __dfp_gitems_tail = NULL;
}

/*
 * fixup one gref's xmr component tab to post generate path so filling
 * of gref uses right post mv gens into mod values
 *
 * SJM 03-17-10 - convert xmrcmp tab to post gen (moved in) xmr cmp path
 * that just converts to normal post gen XMR
 *
 * copy xmrcmp tab to new xmrcmp tab with fixed values, then free old
 *
 * SJM 03-25-10 - this routine must run after all gen done, syms moved
 * to mod's top level sym tab - can't look in gblk sym tabs anymore
 * except gen blks
 */
static void fixup_1dfp_xmrcmps(struct gref_t *grp)
{
 int32 xmri, nxmri, new_nxcmps;
 struct xmrcmp_t **new_xmrcmptab, *nxmp, *oxmp;
 struct sy_t *syp;
 struct symtab_t *cur_sytp;
 char s1[RECLEN], s2[RECLEN];

 /* SJM 03-25-10 - cur sym tab is now always mod's top level because */
 /* all gen items moved into mod by here */
 cur_sytp = __inst_mod->msymtab;

 /* bld fill and init new xmrn cmps, final step will be to free old */
 new_nxcmps = cnt_new_xmp_siz(grp);
 new_xmrcmptab = (struct xmrcmp_t **)
  __my_malloc(new_nxcmps*sizeof(struct xmrcmp_t *));
 for (xmri = 0; xmri < new_nxcmps; xmri++)
  {
   new_xmrcmptab[xmri] = (struct xmrcmp_t *)
    __my_malloc(sizeof(struct xmrcmp_t));
   /* think do not really need to init here */
   init_xmrcmp(new_xmrcmptab[xmri]);
  }
  
 for (xmri = 0, nxmri = 0; xmri < grp->gr_num_xmps; xmri++) 
  {
   oxmp = grp->gr_xmptab[xmri];
    
   /* case 1: omit any gen blks */
   if (oxmp->xmp_petyp == XMP_GBLK)
    {
     /* SJM 03-26-10 - now freeing old xmr cmp tab when done */
     continue;
    }
   /* case 2: inst in gen blk */
   if (oxmp->xmp_petyp == XMP_INST_INGEN)
    {
     /* SJM 03-26-10 - since already know new num, set new to be filled */
     /* to next free xmp pointed to by new table */
     nxmp = new_xmrcmptab[nxmri];
     nxmp->xmp_petyp = XMP_INST;
     /* copying original gen blk cmp name to save it */
     nxmp->xmp_alt_cmpnam = oxmp->xmp_cmpnam;

     /* SJM 03-17-10 - LOOKATME? - think expr. right - pts to new */
     /* node that is right syp for ID? */
     /* DBG remove -- */
     if (oxmp->xmp_in_gblkp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     __bld_gen_scope_nam(s1, oxmp->xmp_in_gblkp);
     sprintf(s2, "%s.%s", s1, nxmp->xmp_alt_cmpnam);
     if ((syp = __zget_sym(s2, cur_sytp->stsyms, cur_sytp->numsyms)) == NULL)
      {
//SJM? 03-17-10 - LOOKATME - should never get here if this happens??
       __misc_terr(__FILE__, __LINE__);
      }
     /* DBG remove -- */
     if (syp->sytyp != SYM_I) __misc_terr(__FILE__, __LINE__);
     /* --- */
     nxmp->xmp_cmpnam  = __pv_stralloc(s2);
     nxmp->xmp_syp = syp;
     nxmp->xmp_in_sytab = cur_sytp;
     nxmp->xmp_nxtcmp_sytab = syp->el.eip->imsym->el.emdp->msymtab;
     cur_sytp = nxmp->xmp_nxtcmp_sytab;
     nxmri++;
     continue;
    }

   /* case 3: net in gen blk */
   if (oxmp->xmp_petyp == XMP_NET_INGEN)
    {
     nxmp = new_xmrcmptab[nxmri];
     nxmp->xmp_petyp = XMP_NET;
     nxmp->xmp_alt_cmpnam = oxmp->xmp_cmpnam;
     /* SJM 03-17-10 - LOOKATME? - think expr. right - pts to new */
     /* node that is right syp for ID? */
     /* DBG remove -- */
     if (nxmp->xmp_in_gblkp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     __bld_gen_scope_nam(s1, nxmp->xmp_in_gblkp);
     sprintf(s2, "%s.%s", s1, nxmp->xmp_alt_cmpnam);
     if ((syp = __zget_sym(s2, cur_sytp->stsyms, cur_sytp->numsyms)) == NULL)
      {
//SJM? 03-17-10 - LOOKATME - should never get here if this happens??
       __misc_terr(__FILE__, __LINE__);
      }
     nxmp->xmp_cmpnam =  __pv_stralloc(s2);
     /* DBG remove -- */
     if (syp->sytyp != SYM_I) __misc_terr(__FILE__, __LINE__);
     /* --- */
     nxmp->xmp_syp = syp;
     nxmp->xmp_in_sytab = cur_sytp;
     /* SJM 03-26-10 - since net, no next sytab */ 
     nxmp->xmp_nxtcmp_sytab = NULL;
     cur_sytp = NULL;
     nxmri++;
     continue;
    }
   /* SJM 03-28-10 - NOTICE net (param) at end can be net declared in gen */
   /* where will be XMP NET INGEN or just nned in downwardn instn where will */
   /* just be simple net */

   /* normal component (no in gen) */ 
   /* SJM - 03-26-10 - can just copy guts providing cmp nam's set to nil */
   /* SJM - 03-28-10 - can have normal xmr comps after downward inst */
   nxmp = new_xmrcmptab[nxmri];
   *nxmp = *oxmp;
   /* need to set old to nil so get freed right */
   oxmp->xmp_cmpnam = NULL;
   oxmp->xmp_alt_cmpnam = NULL;
   /* think still need to ajdust sytabs down - old might be wrong - fixes */
   nxmp->xmp_in_sytab = cur_sytp;
   cur_sytp = nxmp->xmp_nxtcmp_sytab;
   nxmri++;
  }
 /* free old and move new into gref */ 
 free_xmrcmptab(grp);
 grp->gr_xmptab = new_xmrcmptab;
 grp->gr_num_xmps = new_nxcmps;
}

/*
 * routine to count new length of xmrcmp tab because gen blks omitted
 * since after mv of genitems into mod's top level, no long exit 
 */
static int32 cnt_new_xmp_siz(struct gref_t *grp)
{
 int32 xmri, new_nxcmps;
 struct xmrcmp_t *xmp;

 for (new_nxcmps = 0, xmri = 0; xmri < grp->gr_num_xmps; xmri++) 
  {
   xmp = grp->gr_xmptab[xmri];
   /* everything in path stays except for gen blks */
   if (xmp->xmp_petyp != XMP_GBLK) new_nxcmps++;
  }
 return(new_nxcmps);
}


/*
 * routine to build (alloc) a gref's glbref GLBPTH expr from fixed xmpcmrtab
 * 
 * when rebuilding code different than in v src2 because there needed to
 * splice the comma XMR component expr list onto the gref
 */
static void bld_glbref_xpr_from_xmrcmptab(struct gref_t *grp)
{
 int32 xmri;
 struct expr_t *com_xp, *last_com_xp;
 struct xmrcmp_t *xmp;

 last_com_xp = NULL;
 for (xmri = 0; xmri < grp->gr_num_xmps; xmri++)
  {
   xmp = grp->gr_xmptab[xmri];

   com_xp = __alloc_newxnd();
   com_xp->optyp = XMRCOM;

   /* SJM 03-26-10 - glbref in grp's ru points to head of comma list */
//SJM 03-28-10 - LOOKATME?? - there is a memory leak here
   if (last_com_xp == NULL) grp->glbref->ru.x = com_xp;
   else last_com_xp->ru.x = com_xp;

   /* alloc and connect the lhs XMRID */
   com_xp->lu.x = __alloc_newxnd();
   com_xp->lu.x->optyp = XMRID;
//SJM 03-24-10 - LOOKATME? - think var at end not on glbref expr - check?
   com_xp->lu.x->ru.qnchp = __pv_stralloc(xmp->xmp_cmpnam);

   last_com_xp = com_xp;
  }
 if (last_com_xp != NULL) last_com_xp->ru.x = NULL;
}

/*
 * routine to build glb name from xmrcmp tab
 *
 * notice works becuause xmrcmptab always linked off gref
 * SJM 03-26-10 - LOOKATME - could build gnam from glbref expr 
 */
static char *xmrcmptab_to_gnam(char *s, struct gref_t *grp)
{
 int32 xmri;
 struct xmrcmp_t *xmp;
 
 strcpy(s, "");
 for (xmri = 0; xmri < grp->gr_num_xmps; xmri++)
  {
   if (xmri > 0) strcat(s, ".");
   xmp = grp->gr_xmptab[xmri];
   strcat(s, xmp->xmp_cmpnam);
  }
 return(s);
}

/*
 * move gened symbols to mod sym table for fx2 elaborate
 *
 * know no name conflict problems since earlier error message - no expand
 */
static void mv_gened_symbols_to_modsymtab(struct mod_t *mdp)
{
 int32 syi, syi2, new_stsiz;
 struct sy_t *syp;

// ??? SJM 03-01-09
// ??? move now final step after gen converged - do not need to do each time

 /* copy mod gen symbol table symbols (avl form) into wrk stab */
 copy_avl_sytab_to_wrkstab(mdp->mgen_symtab);
 /* then copy marked symbols to wrk stab 2 */
 /* allocate wrk stab2 where know enough room (probably to big) */
 __wrkstab2 = (struct sy_t **)
  __my_malloc(mdp->mgen_symtab->numsyms*sizeof(struct sy_t *));
 /* SJM 02-21-09 - fixed bug - size of wrk stab here is mgen symtab size */
 for (__last_sy2 = -1, syi = 0; syi <  mdp->mgen_symtab->numsyms; syi++)
  {
   syp = __wrkstab[syi];  

   if (__debug_flg)
    {
     __dbg_msg(
      "--> processing mod %s mgen symtab sym %s type %s (decl=%d add=%d)\n",  
      mdp->msym->synam, syp->synam,  __to_sytyp(__xs, syp->sytyp),
      syp->sydecl, syp->gen_add_mstab);
    }

   if (!syp->gen_add_mstab) continue;

   /* SJM 03-18-09 - if add sym from mgen sy tab net - fix up net's syt fld */
   if (syp->sytyp == SYM_N)
    {
     syp->el.enp->syt_of_net = __inst_mod->msymtab;
    }
   __wrkstab2[++__last_sy2] = syp;
  }
 __my_free(__wrkstab, mdp->mgen_symtab->numsyms*sizeof(struct sy_t *)); 

 new_stsiz = mdp->msymtab->numsyms + __last_sy2 + 1; 
 __wrkstab = (struct sy_t **) __my_malloc(new_stsiz*sizeof(struct sy_t *));
 /* copy all mod syms into new sym tab - before sorting */
 for (syi = 0, syi2 = 0; syi < mdp->msymtab->numsyms; syi++)
  {
   __wrkstab[syi2++] = mdp->msymtab->stsyms[syi];
  }
 for (syi = 0; syi <= __last_sy2; syi++)
  {
   __wrkstab[syi2++] = __wrkstab2[syi];
  }
 /* DBG remove -- */
 if (syi2 != new_stsiz) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 __my_free(__wrkstab2, (__last_sy2 + 1)*sizeof(struct sy_t *));

 qsort(__wrkstab, (word32) new_stsiz, sizeof(struct sy_t *),
  __gia_sym_cmp);
 __my_free(mdp->msymtab->stsyms, mdp->msymtab->numsyms*sizeof(struct sy_t *)); 
 mdp->msymtab->stsyms = __wrkstab;
 mdp->msymtab->numsyms = new_stsiz;
}

/*
 * debug routine to dump a symbol table in avl tree format
 */ 
extern void __dbg_dmp_avl_sytab(struct symtab_t *sytp)
{
 int32 si;
 char s1[RECLEN];

 /* DBG remove -- */
 if (sytp->freezes && sytp->n_head == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (sytp->sypofsyt == NULL) strcpy(s1, "**NO ASSOC**");
 else strcpy(s1, sytp->sypofsyt->synam);
 __dbg_msg("&&& dumping avl format sym tab assoc sym %s size %d\n", s1,
  sytp->numsyms);
 
 copy_avl_sytab_to_wrkstab(sytp);
 
 for (si = 0; si < sytp->numsyms; si++) 
  {
  __dbg_msg("    symbol %s type %s\n", __wrkstab[si]->synam,
   __to_sytyp(__xs, __wrkstab[si]->sytyp)); 
  }
 __my_free(__wrkstab, sytp->numsyms*sizeof(struct sy_t *));
 __wrkstab = NULL;
 __last_sy = -1;
}

/*
 * routine to copy 1 symbol tab into wrk stab malloced global
 */
static void copy_avl_sytab_to_wrkstab(struct symtab_t *sytp)
{
 int32 bytes;

 /* SJM 12-23-08 - this just copies from avl symbol tab form to wrkstab */
 /* can now use on any symbol table */
 bytes = sytp->numsyms*sizeof(struct sy_t *);
 __wrkstab = (struct sy_t **) __my_malloc(bytes);
 __last_sy = -1;
 __travfreeze_syms(sytp->n_head);

 /* non mod symbol table size wrong */
 /* DBG remove --*/
 if (__last_sy + 1 != sytp->numsyms) __misc_terr(__FILE__, __LINE__);
 /* --- */
}

/*
 * ROUTINES TO COPY TO SAVE AND RESTORE DEFPARAMS AND ASSOCIATED DEFP XMRS
 */

/*
 * pre fixup copy to save all mod's defparams (before any from gen moved in)
 * and all mod's grefs (same before)
 *
 * SJM 09-08-11 - saving is complicated because need to be able to
 * save newly copied mods, but copied to mod's dfps will be already filled
 * but need non filled version as sav stem for next pass if needed
 *
 * SJM 09-08-11 copied from mod and therefore copied to mod's dfps can
 * include defps from generate, but those must not be saved since next
 * round of fixup nl may get a new set of generated defparams - the old
 * set will not work
 */
static void prefixup_sav_not_yet_sav_defparams(void)
{
 struct mod_t *mdp;
 struct dfparam_t *dfpp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt) 
  {
   /* during gen fixup nl passes may add more modules to list - so may need */
   /* to run the save code in later gen fixup nl passes */
   if (mdp->sav_mdfps == NULL)   
    {
     if (mdp->mdfps != NULL)
      {
       dfpp = prefixup_copy_1mod_dfparms(mdp->mdfps, TRUE);
       mdp->sav_mdfps = dfpp;
      }
    }
  }
}

/*
 * pre fixup copy to restore all mod's defparams and grefs from copy
 * saved before any fixup nl elaboration started
 *
 * SJM 08-29-11 - this is needed because each gen pass may add new
 * and possibly different 
 */
static void prefixup_restor_defparams(void)
{
 struct mod_t *mdp;
 struct dfparam_t *dfpp;

 /* SJM 09-07-11 - dfp hdr is per design not per mod */
 if (__dfphdr != NULL)
  {
   prefix_free_dfplist(__dfphdr);
   __dfphdr = NULL; 
  }

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt) 
  {
   if (mdp->mdfps != NULL)
    {
     prefix_free_dfplist(mdp->mdfps);
     mdp->mdfps = NULL;
    }
   /* SJM 09-02-11 - removed mdfp grtab - can just malloc grefs for defps */
   if (mdp->sav_mdfps != NULL)
    {
     dfpp = prefixup_copy_1mod_dfparms(mdp->sav_mdfps, FALSE);
     mdp->mdfps = dfpp;
    }
  }
}

/*
 * pre fixup copy defparams in one mod (for both direction copies)
 *
 * SJM 08-29-11 - must copy all pre fix copy defparams before dfp grtab
 * for the mod
 */
static struct dfparam_t *prefixup_copy_1mod_dfparms(struct dfparam_t *fr_dfpp,
 int32 empty_flds)
{
 struct dfparam_t *dfpp, *to_dfpp, *last_dfpp, *ndfp_hd, *dfpp2;

 last_dfpp = ndfp_hd = NULL;
 for (dfpp = fr_dfpp; dfpp != NULL;)
  { 
   dfpp2 = dfpp->dfpnxt;   

   /* SJM 09-08-11 - must not copied for saving or adding to mod for */
   /* next round any defparam from generate */
/* ====
//SJM 08-09-11 - PUTMEBACK MAYBE????
   if (dfpp->dfp_was_in_gen)
    {
     dfpp = dfpp2;
     /- do not change copied to last here -/
     continue;
    }
=== */
   to_dfpp = prefixup_cp1_dfp(dfpp, empty_flds);
   if (last_dfpp == NULL) ndfp_hd = to_dfpp; else last_dfpp->dfpnxt = to_dfpp;
   last_dfpp = to_dfpp;

   dfpp = dfpp2;
  }
 return(ndfp_hd);
}

/*
 * copy one defparam during pre fixup and defparam elab (each pass) 
 *
 * used both for save/restore and for to rooted list conversion copy
 * SJM 08-29-11 - can set df nxt to nil, because leaving mod dfpp list
 *
 * SJM 09-08-11 - cleaning works because the copied from dfps are going
 * to be freed anyway in next step since only called for saving
 */
static struct dfparam_t *prefixup_cp1_dfp(struct dfparam_t *fr_dfpp,
 int32 empty_flds)
{
 struct dfparam_t *ndfpp;
 struct gref_t *ngrp;

 /* DBG remove -- */
 if (fr_dfpp->dfpiis != NULL || fr_dfpp->last_dfpi != -1)
  __misc_terr(__FILE__, __LINE__);
 /* -- */
 if (empty_flds)
  {
   if (fr_dfpp->gdfpnam != NULL)
    {
     __my_free(fr_dfpp->gdfpnam, strlen(fr_dfpp->gdfpnam) + 1);
     fr_dfpp->gdfpnam = NULL;
    }
   if (fr_dfpp->targsyp != NULL) fr_dfpp->targsyp = NULL;
   /* can just set to nil, actual rooted dfps already moved to dsgn wide list */
   if (fr_dfpp->rooted_dfps != NULL) fr_dfpp->rooted_dfps = NULL;
   if (fr_dfpp->dfptskp != NULL) fr_dfpp->dfptskp = NULL;
  }
 else
  {
   /* DBG remove -- */
   if (fr_dfpp->gdfpnam != NULL) __misc_terr(__FILE__, __LINE__);
   if (fr_dfpp->dfptskp != NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */
  }

 /* always copy local defparams */
 ndfpp = (struct dfparam_t *) __my_malloc(sizeof(struct dfparam_t));
 *ndfpp = *fr_dfpp;
 /* SJM 09-03-11 - this does not change grp ptr in expr node */
 ndfpp->dfpxlhs = __copy_expr(fr_dfpp->dfpxlhs);
 /* know rhs expr can not contain grefs */
 ndfpp->dfpxrhs = __copy_expr(fr_dfpp->dfpxrhs);

 if (fr_dfpp->dfpxlhs->optyp == GLBREF)
  { 
   ngrp = (struct gref_t *) __my_malloc(sizeof(struct gref_t));
   ndfpp->dfp_grp = ngrp;
   /* copy flags, exprs and indices and name only */
   *ngrp = *(fr_dfpp->dfp_grp);
   /* alloc the gref nam */
   ngrp->gnam = __pv_stralloc(fr_dfpp->dfp_grp->gnam);

   /* gref's dfp lhs index same as one copied from because defp copied first */
   /* copy the glbref expr since gets changed in elab */
   ngrp->glbref = __copy_expr(fr_dfpp->dfp_grp->glbref);
   ndfpp->dfpxlhs->ru.grp = ngrp;
   ngrp->gxndp = ndfpp->dfpxlhs;
  }
 else ndfpp->dfp_grp = NULL;

 /* since leaving dfp nxt list caller must link on right */
 ndfpp->dfpnxt = NULL;
 return(ndfpp);
}

/*
 * free a defparam list 
 */
static void prefix_free_dfplist(struct dfparam_t *dfpp)
{
 struct dfparam_t *dfpp2;

 for (; dfpp != NULL;)
  {
   dfpp2 = dfpp->dfpnxt; 
   __free_1dfparam(dfpp);
   dfpp = dfpp2;
  } 
}

/*
 * ROUTINES TO PROCESS XMR TYPE DEFPARAMS 
 */

/*
 * use all defparams in current module to change local param init values
 * in other modules
 * notice all defparams used to set module init values before values
 * used in code
 *
 * notice defparams are not module items but parameters can be used on
 * lvalues and defparams allowed in tasks where they can only
 * be set with global ref. defparams
 */
extern void __process_defparams(void)
{
 struct dfparam_t *dfpp;

 /* convert all downward relative defparams to rooted */
 /* linked on by root nxt - even if 1 will be on root nxt */
 bld_root_dfpglbs();

 /* handle splitting of all defparams - those not split from gen */
 do_defparam_splitting();
 /* by here arrays of instances have been converted into normal instances */
 if (__pndparam_splits || __defparam_splits) reset_dfp_targsyps();

 /* go through flat itree and reset all instance numbers */
 reassign_itnums();

 /* SJM 03/16/04 - rebuild the levelized static (src contents) if any */
 /* defparam spliting - if only pound param splitting still good */
 /* this is not strictly needed now but will be for future generate */
 if (__defparam_splits) __bld_mlevel_lists();

 /* set pound params if needed */
 /* SJM 11-30-09 if design has defparams, splitting may change pound params */
 if (__num_inst_pndparams > 0) __set_poundparams();

 /* SJM 11-30-09 but defparam values over ride are not propagated down */
 /* fixup new target syps and mdps if needed and set defparams */
 /* this must be in exact source order including in root or local */
 for (dfpp = __dfphdr; dfpp != NULL; dfpp = dfpp->dfpnxt)
  set_1defparam(dfpp);
}

/*
 * ROUTINES TO CONVERT ALL DOWNWARD DEFPARAMS TO ROOTED
 */

/*
 * convert defparam lhs non rooted globals to right number of rooted 
 * links off non rooted and build 1 design wide list
 *
 * know will be at least one defparam or will not be called
 * after here all design wide defparams in one list
 * module mdfps unused after here
 *
 * SJM 08-29-11 - new algorithm - root are separated and linked on to
 * rooted dfps list that is copy even for one inst, mod's dfps are
 * left around for vpi_, next fixup pass will free
 */
static void bld_root_dfpglbs(void)
{
 int32 ii, num_defparams, num_locdefparams;
 struct dfparam_t *dfpp, *dfpp2;
 struct dfparam_t *last_dfpp2, *dfpp3, **dfpptab;
 struct mod_t *dfpmdp;

 /* go through list of 1 inst. corresponding to each top level module */
 /* this also sets itree place to eval. rhs in */
 /* SJM 09-07-11 - bld dfpiis for all but already rooted and locals */
 /* and locals */
 for (ii = 0; ii < __numtopm; ii++)
  { 
   bld_root2_dfpglbs(__it_roots[ii], 1);
  }

 /* convert to design wide linear defparam list */
 last_dfpp2 = NULL;
 num_defparams = num_locdefparams = 0;
 for (dfpmdp = __modhdr; dfpmdp != NULL; dfpmdp = dfpmdp->mnxt)
  {
   /* DBG remove -- */
   if (__debug_flg)
    {
     __dbg_msg("++++++ trying to bld root defparams in module %s\n",
       dfpmdp->msym->synam);
    }
   /* --- */
   for (dfpp = dfpmdp->mdfps; dfpp != NULL;)
    {
     /* DBG remove -- */
     if (__debug_flg)
      {
       __dbg_msg("<<< module %s has defparam %s\n", dfpmdp->msym->synam,
        dfpp->gdfpnam);
      }
     /* --- */
     if (dfpp->dfp_local) num_locdefparams++;

     /* for non rooted/local, add to end of rooted_dfps list */
     for (dfpp2 = dfpp->rooted_dfps; dfpp2 != NULL; dfpp2 = dfpp2->rooted_dfps)
      {
       /* DBG remove --
       if (__debug_flg) dbg_dmp_dfpiis(dfpp2, "rooted defp list");
       --- */

       if (last_dfpp2 == NULL) __dfphdr = dfpp2;
       else last_dfpp2->dfpnxt = dfpp2;
       last_dfpp2 = dfpp2;
       num_defparams++;
      }
     /* SJM 08-07-11 - rm dfpiis for original defparams since always copied */
     __my_free(dfpp->dfpiis, (dfpp->last_dfpi + 1)*sizeof(int32));
     dfpp->dfpiis = NULL;
     dfpp->last_dfpi = -1;

     /* SJM 08-29-11 - leave original (non rooted) dfps around for freeing */ 
     /* just before next fixup pass */
     dfpp = dfpp->dfpnxt;
    }

   /* SJM 08-29-11 - now want mod's dfp list to be copied too */
   /* SJM 08-29-11 - the saving and restoring of defparams and assoc dfp */
   /* grefs now done a start if fixup nl and left around - when last */ 
   /* fixup pass done will have good m dfps list and copied and separated */
   /* rooted list */

//SJM 09-07-11 - itree wrong here - bld dfp list should not change itree */
   /* DBG remove --
   if (__debug_flg)
    {
     __dbg_dmp_1mod_defparams(dfpmdp, TRUE);
    }
   --- */
  }
 if (last_dfpp2 != NULL) last_dfpp2->dfpnxt = NULL;

 /* sort global defparams by location since last must override */
 /* know there will always be a least one defparam here */
 dfpptab = (struct dfparam_t **)
  __my_malloc(num_defparams*sizeof(struct dfparam_t *));
 for (ii = 0, dfpp = __dfphdr; ii < num_defparams; ii++, dfpp = dfpp->dfpnxt) 
  dfpptab[ii] = dfpp;
 qsort(dfpptab, num_defparams, sizeof(struct dfparam_t *),
  dfploc_cmp);
 __dfphdr = dfpptab[0];
 dfpp3 = __dfphdr;
 for (ii = 1; ii < num_defparams; ii++)
  {
   dfpp3->dfpnxt = dfpptab[ii];
   dfpp3 = dfpp3->dfpnxt;
  }
 dfpp3->dfpnxt = NULL;
 /* design wide rooted (or local) def param list now ordered */
 __my_free(dfpptab, num_defparams*sizeof(struct dfparam_t *));

 /* SJM 06/04/05 - nil the rooted dfps field since no longer needed */
 /* could leave but nil makes debugging easier */
 for (dfpp = __dfphdr; dfpp != NULL; dfpp = dfpp->dfpnxt)
  dfpp->rooted_dfps = NULL;

 /* only find identicals if at least one non local */
 if (num_defparams - num_locdefparams != 0)
  {
   bld_identdfparams(num_defparams - num_locdefparams);
   find_mustsplit_dfps();
  } 
 /* DBG remove ---
 if (__debug_flg) dmp_dfps(TRUE, TRUE);
 --- */
}

static int32 dfploc_cmp(const void *dfpp1, const void *dfpp2)
{
 int32 cv;

 cv = (*((struct dfparam_t **) dfpp1))->dfpfnam_ind
  - (*((struct dfparam_t **) dfpp2))->dfpfnam_ind;
 if (cv != 0) return(cv);
 return((*((struct dfparam_t **) dfpp1))->dfplin_cnt
  - (*((struct dfparam_t **) dfpp2))->dfplin_cnt);
}

/*
 * debug dmp one mod (not moved to rooted) defparams
 */
extern void __dbg_dmp_1mod_defparams(struct mod_t *mdp, int32 itree_built)
{
 struct dfparam_t *dfpp;

 __dbg_msg("## dumping defparams for %s round %d ##\n", mdp->msym->synam,
  __fixup_round);
 for (dfpp = mdp->mdfps; dfpp != NULL; dfpp = dfpp->dfpnxt) 
  {
   __dmp_1defparam(stdout, dfpp, itree_built);
  }
 __dbg_msg("## end of %s defparams ##\n", mdp->msym->synam);
}

/*
 * dump defparam list
 * only called if debugging on
 *
 * SJM 05/25/05 - rewrote to work with converted to rooted dfps
 */
static void dmp_dfps(int32 emit_pth, int32 now_rted)
{
 int32 dfi, ii; 
 struct dfparam_t *dfpp;
 char identtyp;
 struct inst_t *ip;

 __dbg_msg("$$$ Dumping all design defparams $$$\n");
 for (dfpp = __dfphdr; dfpp != NULL; dfpp = dfpp->dfpnxt)
  {
   if (dfpp->dfp_has_idents) 
    { if (dfpp->idntmastdfp == NULL) identtyp = 'M'; else identtyp = 'Y'; }
   else identtyp = 'N';
   __dbg_msg("==> rt defparam %s in %s at %s loc.=%u rooted=%u identical=%c\n",
    dfpp->gdfpnam, dfpp->dfp_in_mdp->msym->synam,
   __bld_lineloc(__xs, dfpp->dfpfnam_ind, dfpp->dfplin_cnt),
    dfpp->dfp_local, dfpp->dfp_rooted, identtyp);

   /* will not have component since accessed from master */
   if (dfpp->idntmastdfp != NULL || !emit_pth || dfpp->dfp_local) continue;

   /* here must still allocate dfpiis */
   /* if root in module that is multiply instantiated must see table */
   /* only once and rule is last source order is right instance to eval in */
   ii = dfpp->dfpiis[0];
   if (dfpp->dfp_rooted || now_rted) ip = __top_itab[ii];
   else ip = &(dfpp->dfp_in_mdp->minsts[ii]);  
   for (dfi = 0; dfi <= dfpp->last_dfpi; dfi++) 
    {
     sprintf(__xs, " (inst type %s)", ip->imsym->synam);
     __dbg_msg("   component %s%s index %d\n", __xs, ip->isym->synam, ii);

     ii = dfpp->dfpiis[dfi + 1];
     if (dfi < dfpp->last_dfpi) ip = &(ip->imsym->el.emdp->minsts[ii]); 
    }
   __dbg_msg("\n");
  }
 __dbg_msg("$$$ end of defparms $$$\n");
}

/*
 * dump all param expressions 
 *
 * AIV 09/27/06 - this is never called but also doesn't work for local params
 */
extern void __dmp_all_param_exprs(void)
{
 int32 pi, ii;
 struct mod_t *mdp;
 struct net_t *np;
 int32 wlen;
 word32 *wp;

 __dbg_msg("*** dumping all params ***\n");
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (pi = 0; pi < mdp->mprmnum; pi++)
    {
     np = &(mdp->mprms[pi]);
     wlen = wlen_(np->nwid);

     /* parameter has IS form, eval rhs from itree place and set num */
     if (np->srep == SR_PISNUM)
      {
       for (ii = 0; ii < mdp->flatinum; ii++)
        {
         wp = &(np->prm_nva.wp[2*ii*wlen]);
         __dbg_msg("module %s param %s value %s\n", mdp->msym->synam,
          np->nsym->synam, __pregab_tostr(__xs, wp, &(wp[wlen]), np));
        } 
      }
     else if (np->srep == SR_PNUM)
      {
       wp = np->prm_nva.wp;
       __dbg_msg("module %s param %s rhs expr. %s\n", mdp->msym->synam,
        np->nsym->synam, __pregab_tostr(__xs, wp, &(wp[wlen]), np));
      }
     else __case_terr(__FILE__, __LINE__);
     if (np->nrngrep != NX_CT) __misc_terr(__FILE__, __LINE__);
     if (np->n_isarr)
      {
       __dbg_msg("  array range [%s:%s]", __msgexpr_tostr(__xs,
        np->nu.ct->nx1), __msgexpr_tostr(__xs2, np->nu.ct->nx2));
      }
     else __dbg_msg(" ");
     if (np->n_isavec)
      {
       __dbg_msg(" range [%s:%s]\n", __msgexpr_tostr(__xs, np->nu.ct->nx1),
        __msgexpr_tostr(__xs2, np->nu.ct->nx2));
      }
     else __dbg_msg("\n");
    }
  }
 __dbg_msg("*** end of dump ***\n");
}

/*
 * under each top module's convert defparam lhs global to rooted form
 * uses extra storage but reclaimed after defparams substituted
 *
 * this just updates dfpiis for downward relative
 * downward relative symbols in top module are not rooted but can never
 * be in list
 *
 * SJM 09-07-11 - after here ever dfp rooted list built for all now 
 */
static void bld_root2_dfpglbs(struct itree_t *itp, int32 level)
{
 int32 i, ii, rtlen, *newiis;
 struct dfparam_t *dfpp;
 struct dfparam_t *new_dfpp;
 byte *bp1, *bp2;
 struct mod_t *imdp;
 struct itree_t *tmpitp, *upitp;

 if (level >= MAXGLBCOMPS)
  {
too_deep:
   __pv_terr(310,
    "downward defparam hierarchical path has too many components (%d)",
    MAXGLBCOMPS); 
  } 
 imdp = itp->itip->imsym->el.emdp;
 /* ---
 if (__debug_flg)
  {
   __dbg_msg("==> building defparam globals in inst. %s type %s level %d\n",
    itp->itip->isym->synam, imdp->msym->synam, level);
  }
 --- */ 

 /* convert unrooted to defparam rooted by changing dfpiis when downward */
 /* even if only one inst. of this need rooted form */ 
 for (dfpp = imdp->mdfps; dfpp != NULL; dfpp = dfpp->dfpnxt)
  {
   /* SJM 05/26/05 - can't use indfp itp for dfps because splitting changes */

   /* if root in module that is multiply instantiated must see table */
   /* only once and rule is last source order is right instance to eval in */

   /* if rooted appears in multiply instantiated, possible that rhs */
   /* expr. can contain IS form so that same target rooted defparam lhs */ 
   /* gets assigned to once for each - using last one since arbitrary */

   /* local defparams - NULL means in all instances - for dependent */
   /* if rhs defparam is IS form will convert local value to IS form later */

   /* SJM 09-07-11 - new algorithm just copies dfpiis and defparam for */
   /* simple ones here */
   if (dfpp->dfp_rooted  || dfpp->dfp_local)
    {
     /* just copy */ 
     __push_wrkitstk(imdp, 0);
     new_dfpp = __copy1_defparam(dfpp);
     __pop_wrkitstk();
     /* only one on front */
     dfpp->rooted_dfps = new_dfpp;
     /* DBG remove -- */
     if (new_dfpp->rooted_dfps != NULL) __misc_terr(__FILE__, __LINE__);
     /* -- */
     continue;
    }

   rtlen = level + dfpp->last_dfpi + 1;  
   if (rtlen >= MAXGLBCOMPS) goto too_deep;
   newiis = (int32 *) __my_malloc(rtlen*sizeof(int32));
   /* fill the new prefix - need instance symbol except module at top */ 
   /* this is downward relative in top level */
   tmpitp = itp;
   for (i = level; i > 0; i--)
    {
     if (tmpitp->up_it == NULL)
      {
       ii = __ip_indsrch(tmpitp->itip->imsym->synam);
       /* DBG remove -- */
       if (ii == -1) __misc_terr(__FILE__, __LINE__);
       if (i != 1) __misc_terr(__FILE__, __LINE__);
       /* --- */
       newiis[i - 1] = ii;
       continue;
      }
     upitp = tmpitp->up_it;
     bp1 = (byte *) tmpitp->itip;
     bp2 = (byte *) upitp->itip->imsym->el.emdp->minsts;
     ii = (bp1 - bp2)/sizeof(struct inst_t);
     newiis[i - 1] = ii;
     tmpitp = upitp;
    }
   /* finish by copying rest of path */
   __last_gsc = level;
   for (i = 0; i <= dfpp->last_dfpi; __last_gsc++, i++)
    newiis[__last_gsc] = dfpp->dfpiis[i];

   /* SJM 08-27-11 - in fixing gen multiple fixup defparam processing (can */
   /* change) - get rid of 1 flat inst special case - list some more original */

   /* SJM 09-07-11 - need real defparam copy because if inst in many places */
   /* in itree, when convert to rooted will need new defparam gref */
   /* because now each defparam has its own malloced gref */

   /* SJM 09-07-11 - even new rooted can have in mod (place were was) */
   __push_wrkitstk(imdp, 0);
   new_dfpp = __copy1_defparam(dfpp);
   __pop_wrkitstk();

   /* add the newly computed for rooted dfp iis index with right len */
   /* notice tail is pointed to by targsyp (not in cmps) */
   new_dfpp->dfpiis = newiis;
   new_dfpp->last_dfpi = __last_gsc - 1;
   /* DBG remove --
   if (__debug_flg) dbg_dmp_dfpiis(dfpp, "in bld root2 dfps");
   --- */

   /* put on front */
   new_dfpp->rooted_dfps = dfpp->rooted_dfps;
   dfpp->rooted_dfps = new_dfpp;
   /* downward relative stem freed when new rooted copied to design list */
   /* know rooted flag off */
  }
 /* process 1 down depth first */
 for (ii = 0; ii < imdp->minum; ii++)
  bld_root2_dfpglbs(&(itp->in_its[ii]), level + 1);
}

/*
 * build the list of defparams independent of source module that have
 * identical target module - goes through all defparams and connect
 * those with identical target module
 *
 * this order identical path maybe same or maybe different defparams
 * in source order so same will always use last source order
 */
static void bld_identdfparams(int32 nrtdfps)
{
 int32 dfi, dfi2;
 struct dfparam_t *dfpp1, *dfpp2;
 struct dfparam_t *mastdfp, *dfpend, **dfppndx;

 /* build and sort index - ordered so all same rooted paths contingous */ 
 /* within same paths ordered by source order */ 
 dfppndx = (struct dfparam_t **)
  __my_malloc(nrtdfps*sizeof(struct dfparam_t *));
 for (dfi = -1, dfpp1 = __dfphdr; dfpp1 != NULL; dfpp1 = dfpp1->dfpnxt)
  {
   if (!dfpp1->dfp_local) dfppndx[++dfi] = dfpp1;
  }
 qsort(dfppndx, nrtdfps, sizeof(struct dfparam_t *), ipth_cmp);

 for (dfi = 0; dfi < nrtdfps;)
  {
   dfpp1 = dfppndx[dfi];
   /* because of sorting - never see one already in equivalence class */ 
   /* DBG remove -- */
   if (dfpp1->dfp_has_idents) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if ((dfi2 = dfi + 1) >= nrtdfps) break;
   dfpp2 = dfppndx[dfi2];
   /* DBG remove -- */
   if (dfpp2->dfp_has_idents) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (ipth2_cmp(dfpp1, dfpp2) != 0) { dfi++; continue; }

   /* know at least 2 equivalent - first is master */
   mastdfp = dfpend = dfpp1;
   dfpp1->idntmastdfp = NULL;
   dfpp1->dfp_has_idents = TRUE;
   for (;;)
    {
     /* DBG remove -- */
     if (dfpp2->dfp_has_idents) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* mark has ident and link on front of current work list */  
     dfpp2->dfp_has_idents = TRUE;
     dfpp2->idntmastdfp = mastdfp;
     dfpend->idntnxt = dfpp2;
     dfpend = dfpp2;
     /* DBG remove --- */
     if (__debug_flg)
      {
       __dbg_msg("defparam %s in %s at %s same target inst. as %s at %s\n",  
        dfpp2->gdfpnam, dfpp2->dfp_in_mdp->msym->synam,     
        __bld_lineloc(__xs, dfpp2->dfpfnam_ind, dfpp2->dfplin_cnt),
        mastdfp->gdfpnam, __bld_lineloc(__xs2, mastdfp->dfpfnam_ind,
        mastdfp->dfplin_cnt));
      }
     /* --- */
     if (++dfi2 >= nrtdfps) break; 
     dfpp2 = dfppndx[dfi2];
     /* if not in current equiv. class, may start next one */ 
     if (ipth2_cmp(dfpp1, dfpp2) != 0) break;
    }
   dfpend->idntnxt = NULL;
   dfi = dfi2;
  } 
 __my_free(dfppndx, nrtdfps*sizeof(struct dfparam_t *));
}

/*
 * wrapper for sorting defparams - if same order by source loc.
 */
static int32 ipth_cmp(const void *dfpp1p, const void *dfpp2p)
{
 int32 cv;
 struct dfparam_t *dfpp1, *dfpp2;

 dfpp1 = *((struct dfparam_t **) dfpp1p);
 dfpp2 = *((struct dfparam_t **) dfpp2p);
  
 if ((cv = ipth2_cmp(dfpp1, dfpp2)) != 0) return(cv);

 /* if same, need source location order */ 
 cv = dfpp1->dfpfnam_ind - dfpp2->dfpfnam_ind;
 if (cv != 0) return(cv);
 cv = (dfpp1->dfplin_cnt - dfpp2->dfplin_cnt);
 if (cv != 0) return(cv);
 return(0);
}

/*
 * compare 2 defparam records (use address for order)
 */
static int32 ipth2_cmp(struct dfparam_t *dfpp1, struct dfparam_t *dfpp2)
{
 int32 ii, atend1, atend2;
 struct sy_t *sy1, *sy2;
 struct itree_t *itp1, *itp2;

 /* DBG remove --
 if (__debug_flg) dbg_dmp_dfpiis(dfpp1, "ipth2 cmp 1st");
 if (__debug_flg) dbg_dmp_dfpiis(dfpp2, "ipth2 cmp 2nd");
 --- */

 itp1 = __it_roots[dfpp1->dfpiis[0]];
 itp2 = __it_roots[dfpp2->dfpiis[0]];
 for (ii = 0;;)
  {
   /* DBG remove --
   if (itp1->itip == NULL || itp2->itip == NULL)
    __misc_terr(__FILE__, __LINE__);
   --- */
   sy1 = itp1->itip->isym;
   sy2 = itp2->itip->isym;
   /* SJM 06/03/02 - cast to int32 and minus not 64 bit portable */
   if (sy1 != sy2)
    {
     if (sy1 > sy2) return(1);
     return(-1);
    }
   ii++;
   atend1 = (ii > dfpp1->last_dfpi);
   atend2 = (ii > dfpp2->last_dfpi);
   if (!atend1 && !atend2)
    {
     itp1 = &(itp1->in_its[dfpp1->dfpiis[ii]]);
     itp2 = &(itp2->in_its[dfpp2->dfpiis[ii]]);
     continue;
    }
   /* if both past end - done (know same length) */
   if (atend1 && atend2) break;
   /* know one but not other past end - done with shortest first */
   if (atend1) return(-1); 
   return(1);
  }
 return(0);
}

/*
 * mark wires that can effect target module expression widths in
 * target module and if defparam contains mark as must split
 * if not marked, then can use IS form 
 */
static void find_mustsplit_dfps(void)
{
 struct dfparam_t *dfpp, *dfpp2;
 struct mod_t *imdp;
 struct net_t *np;
 struct itree_t *bot_itp; 

 for (dfpp = __dfphdr; dfpp != NULL; dfpp = dfpp->dfpnxt)
  {
   /* only look at non local master's from identicals here */ 
   if (dfpp->dfp_local || dfpp->idntmastdfp != NULL) continue;

   bot_itp = __find_dfpbot_itp(dfpp);
   imdp = bot_itp->itip->imsym->el.emdp;
   /* if only 1 inst. no need to split */
   if (imdp->flatinum == 1) continue;

   /* if target module does not have expr. width params set, do it now */
   if (!imdp->mwiddetdone)
    {
     /* width marking must be done with module context */
     __push_wrkitstk(imdp, 0);
     __mark_widdet_params(imdp);
     __pop_wrkitstk();
     imdp->mwiddetdone = TRUE;
    }

   /* if any of list with identical target width determining must split */
   /* identical target means identical module type */
   /* dfpp included in ident list */
   if (dfpp->dfp_has_idents)
    {
     for (dfpp2 = dfpp; dfpp2 != NULL; dfpp2 = dfpp2->idntnxt)
      {
       np = dfpp2->targsyp->el.enp;
       if (np->nu.ct->n_widthdet)
        {
         /* DBG remove --- */
         if (__debug_flg)
          {
           __dbg_msg(
            "+++ mark module %s to split defparam %s (mast of equiv class) width determining.\n",
            imdp->msym->synam, np->nsym->synam);
          }
         /* --- */
         /* SJM 03/21/04 - because all are in same destination inst */
         /* equivalence class, once know that the master split can stop */
         dfpp->dfp_mustsplit = TRUE;
        }
      }
    }
   else
    {
     np = dfpp->targsyp->el.enp;
     if (np->nu.ct->n_widthdet)
      {
       /* DBG remove --- */
       if (__debug_flg)
        {
         __dbg_msg(
          "+++ mark module %s to split since defparam %s width determining.\n",
          imdp->msym->synam, np->nsym->synam);
        }
       /* --- */
       dfpp->dfp_mustsplit = TRUE;
       /* AIV 02/04/04 - was wrongly breaking so did not process all defps */
      }
    }
  }
}

/*
 * find a defp bottom module type
 *
 * SJM 09-21-11 - needed before pound (and now also def) param splitting
 * when there is no inst tree, but there is dfpiis built and top virtual
 * instances for rooted defparams
 *
 * new much more pessimistic splitting algoirthm for defparams needed
 * because next pass of generate can change defparam widths or types
 * even inst into from different gen for?
 *
 * this finds bottom module type without needing a good inst tree
 */
static struct mod_t *find_dfpbot_mod(struct dfparam_t *dfpp)
{
 int32 dfi, ii;
 struct mod_t *imdp;
 struct inst_t *ip;

 if (dfpp->dfp_rooted)
  {
   ii = dfpp->dfpiis[0];
   ip = __top_itab[ii];
   imdp = ip->imsym->el.emdp;
   dfi = 1;
  }
 else
  { 
   imdp = dfpp->dfp_in_mdp;
   dfi = 0;
  }
 for (; dfi <= dfpp->last_dfpi; dfi++)
  {
   ii = dfpp->dfpiis[dfi];
//REMOVEME
//   if (ii > 8) __misc_terr(__FILE__, __LINE__);
   ip = &(imdp->minsts[ii]);
   imdp = ip->imsym->el.emdp;
  }
 return(imdp);
}

/*
 * find bottom defparam itree loc.
 */
extern struct itree_t *__find_dfpbot_itp(struct dfparam_t *dfpp)
{
 int32 dfi, ii;
 struct itree_t *bot_itp, *itp;
 
 /* DBG remove --
 if (__debug_flg) dbg_dmp_dfpiis(dfpp, "in find dfpbot");
 --- */
 ii = dfpp->dfpiis[0];
 bot_itp = __it_roots[ii];
 /* may not go through this loop if in top */
 for (dfi = 1; dfi <= dfpp->last_dfpi; dfi++)
  {
   ii = dfpp->dfpiis[dfi];
//REMOVEME
//   if (ii > 8) __misc_terr(__FILE__, __LINE__);
   /* --- */
   itp = &(bot_itp->in_its[ii]);
   bot_itp = itp;
  }
 return(bot_itp);
}

/*
 * DBG routine to dump defparam dfpiis
 */
static void dbg_dmp_dfpiis(struct dfparam_t *dfpp, char *s1)
{
 /* DBG remove -- */
 if (__debug_flg)
  {
   int32 dfi2;

   __dbg_msg("+++ dump (round %d) of defpiis for %s in %s (%s)\n",
    __fixup_round, dfpp->gdfpnam, dfpp->dfp_in_mdp->msym->synam, s1);
   __dbg_msg("    dfpii=0th=%d", dfpp->dfpiis[0]);  
   for (dfi2 = 1; dfi2 <= dfpp->last_dfpi; dfi2++)
    {
//REMOVEME
//     if (dfpp->dfpiis[dfi2] > 10) __misc_terr(__FILE__, __LINE__);
     __dbg_msg("    ,%dth=%d", dfi2, dfpp->dfpiis[dfi2]);  
    }
   __dbg_msg("\n");
  }
}

/*
 * ROUTINES TO SPLIT MODULES AND UNWIND DEFPARAMS
 */

/*
 * separate routine for downward defparams - must split off before bld rooted 
 *
 * routine only for downward defparams that are really like pound params
 * where in each mod split the ones underneath
 *
 * SJM 06-13-11 - still must handle defparams that are rooted or
 * upward relative somewhere else (collected in one place) in design
 *
 * SJM 06-21-11 - not inst tree and no mod itps here so need to chg 
 * flatinum counts and update inst_t in m insts mod sym ptr
 *
 * SJM 06-22-11 - think do not need any type of levelized processing
 * just process downward relative defparams in every module, also need
 * to process defparams in the new split off modules (know always 1 flat inst
 * for these)
 *
 * SJM 09-21-11 - because multiple defparams to different instance may have
 * different sizes or even types (semantics is to totally replace) for
 * any depfaram inst targs must split every inst of mod type (also needed
 * for rooted because there may be more than one rooted to different insts
 * of the module type).
 */
static void do_dfp_fnd_needto_split(void)
{
 struct dfparam_t *dfpp;
 struct mod_t *mdp, *imdp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* DBG remove --
   if (__debug_flg) __dbg_dmp_1mod_defparams(mdp, FALSE);
   --- */
   for (dfpp = mdp->mdfps; dfpp != NULL; dfpp = dfpp->dfpnxt)
    {
     /* SJM 06-13-11 - defparams can't be upward relative */
     /* only downward or rooted for real XMR type defparams possible */
     if (dfpp->dfp_local) continue;

     /* DBG remove --
     if (__debug_flg) dbg_dmp_dfpiis(dfpp, "in do dfp widthdet split");
     --- */
////=====>
     /* SJM 09-21-11 - LOOKATME??? - maybe better to find through syt_of_net */ 
     /* then if not mod sym tab, work up sym tab parents to mod */
     imdp = find_dfpbot_mod(dfpp);
     imdp->dfp_allmodinsts_split = TRUE;
    }
  }
 mark_all_insts_of_mod_split();
}

/*
 * special more splitting for defparams from gen 
 *
 * SJM 09-21-11 - because of generate interaction with defparams, now
 * can change width/type of any inst of a parameter from a defparam from
 * additional rounds, solution is that any defparam target module's must
 * have all insts split
 */
static void mark_all_insts_of_mod_split(void)
{
 int32 ii;
 struct mod_t *mdp;
 struct inst_t *ip;
 struct mod_t *imdp;

 /* for every mod in design */ 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* for every inst of mod */ 
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp; 
     if (imdp->dfp_allmodinsts_split) ip->i_pnddefsplit = TRUE;
    }
  }
}

/*
 * do all defparam splitting off
 * since all rooted just descend from root in itree change itree imsym
 * types and copy modules where needed
 */
static void do_defparam_splitting(void)
{
 int32 ii2, dfi, ii, last_split;
 struct dfparam_t *dfpp;
 struct inst_t *ip;
 struct itree_t *itp, *up_itp;
 struct mod_t *orig_imdp, *imdp, *down_inst_mod;

 __defparam_splits = FALSE;
 last_split = FALSE;
 for (dfpp = __dfphdr; dfpp != NULL; dfpp = dfpp->dfpnxt)
  {
   /* if has identical (i.e. more than one param in same inst set), */
   /* then build path for 1 and at end copy same path for all idents */
   if (dfpp->dfp_local || dfpp->idntmastdfp != NULL) continue;

   /* SJM 03/23/04 - if needed to split must rebuild itree because */
   /* need to renumber the split off ones and the ones split from */ 
   if (last_split)
    {
     __free_flat_itree();
     __bld_flat_itree();
     last_split = FALSE;
    }
   /* DBG remove --
   if (__debug_flg) dbg_dmp_dfpiis(dfpp, "in defparam splitting");
   --- */

   /* first split module containing defparam target if needed */
   dfi = dfpp->last_dfpi;
   itp = __find_dfpbot_itp(dfpp);
   ip = itp->itip;
   imdp = ip->imsym->el.emdp;

   if (imdp->flatinum == 1)
    {
     /* DBG remove --- */
     if (__debug_flg)
      {
       __dbg_msg("-- defparam %s mod %s not split - only 1 instance\n",
        dfpp->gdfpnam, imdp->msym->synam);
      }
     /* --- */
     continue;
    }

   /* if can just change to IS expr. form, do not split */
   if (!dfpp->dfp_mustsplit)
    {
     /* DBG remove --- */
     if (__debug_flg)
      {
       __dbg_msg(
        "-- defparam %s mod %s not split - can change param to inst. form\n",
        dfpp->gdfpnam, imdp->msym->synam);
      }
     /* --- */
     continue;
    }

   /* always split off master (original) if needed */ 
   if (imdp->mspltmst != NULL)
    {
     __gfwarn(535, dfpp->dfpfnam_ind, dfpp->dfplin_cnt,
      "INTERNAL - bottom of tree module of type \"%s\" should not have master %s",
      imdp->msym->synam, imdp->mspltmst->msym->synam);
     orig_imdp = imdp->mspltmst;
    }
   else orig_imdp = imdp;

   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg("==> before split of bottom mod %s and before split up\n",
      orig_imdp->msym->synam);
     __dmp_itree(__it_roots[0]);
    }
   --- */

   /* notice this set __inst_mod to new split off - each defaparam has */
   /* own in module so this use of __inst_mod does not require saving */
   /* LOOKATME - should not set __inst_mod inside but return value here */
   __do_mdsplit(orig_imdp);
   /* AIV 08/24/11 - need to turn off all defparam instance from */
   /* using # param splitting reuse */
   turn_off_pndsplitting_reuse(__inst_mod);
   __defparam_splits = TRUE;
   last_split = TRUE;

   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg("==> after split but before split up without adjust to %s\n",
      __inst_mod->msym->synam);
     __dmp_itree(__it_roots[0]);
    }
   --- */
    
   /* DBG remove --- */
   if (__debug_flg)
    {
     __dbg_msg("-- split defparam(s) %s type %s to %s target symbol %s.\n",
      dfpp->gdfpnam, orig_imdp->msym->synam, __inst_mod->msym->synam,
      dfpp->targsyp->synam);
    }
   /* --- */
   /* do not need to update non master defparam since will never see */ 

   up_itp = itp->up_it;
try_split_up:
   /* notice that level i, ii is index in one up itree in_its */
   ii = dfpp->dfpiis[dfi];
   /* move 1 level up tree */
   dfi--;
   itp = up_itp;
   imdp = itp->itip->imsym->el.emdp;
   up_itp = up_itp->up_it;
   /* previous copied module */
   down_inst_mod = __inst_mod;

    /* DBG remove --- 
    if (__debug_flg)
     {
      __dbg_msg("==> at beginning of try split up\n");
      __dmp_itree(__it_roots[0]);
     }
    --- */

   /* either fix 1 itree level above module type or split if needed */

   /* rule 1: if 1 up itree place inst_t module type has 1 flat inst, */
   /* just change imsym */
   /* top modules will always cause rule 1 termination */
   /* if already split off (common), know exactly one inst., do not split */
   if (imdp->flatinum == 1)
    {
     (imdp->minsts[ii]).imsym = down_inst_mod->msym;

     /* DBG remove --- */
     if (__debug_flg)
      {
       __dbg_msg("-- defparam %s module %s needs split but has 1 inst.\n",
        dfpp->gdfpnam, imdp->msym->synam);
      }
     /* --- */
     continue;
    }
   
   /* rule 2: if module flatinum > 1, has contained inst_t split off */
   /* must copy module and work up tree */
   if (imdp->mspltmst != NULL) orig_imdp = imdp->mspltmst;
   else orig_imdp = imdp;
   /* notice here __inst_mod changed to newly split off, so works */
   /* but use of __inst mod makes code hard to follow */
   __do_mdsplit(orig_imdp);
   /* AIV 08/24/11 - need to turn off all defparam instance from */
   /* using # param splitting reuse */
   turn_off_pndsplitting_reuse(__inst_mod);

   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg("==> after split - before itree fix up\n");
     __dmp_itree(__it_roots[0]);
    }
   --- */

   /* inside split off mod always change instances down module type */
   (__inst_mod->minsts[ii]).imsym = down_inst_mod->msym;

   /* since entire insts list in __inst_mod copy of list in original mod */
   /* each itip inside non leaf top module must be changed to address of */
   /* inst in split of __inst_mod */
   /* notice must update because other defparams may descend through here */
   for (ii2 = 0; ii2 < __inst_mod->minum; ii2++)
    (itp->in_its[ii2]).itip = &(__inst_mod->minsts[ii2]);

   /* --- DBG remove
   if (__debug_flg)
    {
     __dbg_msg("==> after split - after itree fix up\n");
     __dmp_itree(__it_roots[0]);
    }
   --- */

   /* DBG remove --- */
   if (__debug_flg)
    {
     __dbg_msg("-- defparam %s needing split mod %s split to %s\n",
      dfpp->gdfpnam, orig_imdp->msym->synam, __inst_mod->msym->synam);
    }
   /* --- */
   goto try_split_up;
  }

 /* SJM 03/23/04 - if last one needed to split must rebuild itree here */
 if (last_split)
  {
   __free_flat_itree();
   __bld_flat_itree();
  }
 /* DBG remove --- */
 if (__debug_flg)
  { for (ii2 = 0; ii2 < __numtopm; ii2++) __dmp_itree(__it_roots[ii2]); }
 /* --- */
}

/*
 * if any splitting must reset all target symbols 
 * problem is that end instance of path may be split from other defparam
 */
static void reset_dfp_targsyps(void)
{
 struct dfparam_t *dfpp, *dfpp2;

 for (dfpp = __dfphdr; dfpp != NULL; dfpp = dfpp->dfpnxt)
  {
   /* since local always copied and no xmr path no reset needed */
   if (dfpp->dfp_local || dfpp->idntmastdfp != NULL) continue;

   if (!dfpp->dfp_has_idents)
    {
     reset_1dfp_targsyp(dfpp);
     continue;
    }

   /* SJM 03/16/04 - LOOKATME - could just go through lists ignoring */
   /* idntmastdfp */
   /* master included on this list */
   for (dfpp2 = dfpp; dfpp2 != NULL; dfpp2 = dfpp2->idntnxt)
    reset_1dfp_targsyp(dfpp2);
  }  
}

/*
 * in case splitting of target module (maybe from elsewhere)
 * reset target symbol
 */
static void reset_1dfp_targsyp(struct dfparam_t *dfpp)
{
 struct task_t *tskp;
 struct itree_t *itp;
 struct mod_t *mdp;
 struct sy_t *syp;
 char *chp;

 itp = __find_dfpbot_itp(dfpp);
 mdp = itp->itip->imsym->el.emdp;
 chp = dfpp->targsyp->synam;
 if (dfpp->dfptskp != NULL)
  {
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (strcmp(tskp->tsksyp->synam, dfpp->dfptskp->tsksyp->synam) == 0)
      goto have_task;
    }
   __arg_terr(__FILE__, __LINE__);
   
have_task:
   if ((syp = __get_sym(chp, tskp->tsksymtab)) == NULL)
    __arg_terr(__FILE__, __LINE__);
   if (dfpp->targsyp != syp) 
    {
     /* DBG remove -- */
     if (__debug_flg)  
      {
       __dbg_msg(
        "++ for task defparam %s new bottom %s replacing %s with %s\n",
        dfpp->gdfpnam, __msg2_blditree(__xs, itp),
        dfpp->targsyp->synam, syp->synam);
      }
     /* ---*/
     dfpp->targsyp = syp;
     /* DBG remove --- */
     if (__debug_flg)
      {
       struct net_t *np;

       np = syp->el.enp; 
       /* using first instance of original expression */
       __dbg_msg("-+- assigning params for %s in %s at %p - expr:%s\n",
        np->nsym->synam, mdp->msym->synam, np, __msgexpr_tostr(__xs,
        np->nu.ct->n_dels_u.d1x));
      }
     /* --- */
    }
   return;
  }
 /* DBG remove -- */
 if ((syp = __get_sym(chp, mdp->msymtab)) == NULL)
  __arg_terr(__FILE__, __LINE__);
 if (dfpp->targsyp != syp)
  {
   /* DBG remove -- */
   if (__debug_flg)
    {
     __dbg_msg("++ for defparam %s new bottom %s replacing %s with %s\n",
      dfpp->gdfpnam, __msg2_blditree(__xs, itp),
      dfpp->targsyp->synam, syp->synam);
    }
   /* ---*/
   dfpp->targsyp = syp;
  }
}

/*
 * ROUTINES TO BUILD AS IF FLATTENED INSTANCE TREE
 */

/*
 * go through itree setting all inst fields to possible new split off value 
 * split off module has same inst pointer (type different) but underneath
 * instances can be completeley different no. (structure unchanged though)
 */
static void reassign_itnums(void)
{
 int32 ii;
 struct mod_t *flmdp;
 struct itree_t *itp; 

 for (flmdp = __modhdr; flmdp != NULL; flmdp = flmdp->mnxt)
  flmdp->lastinum = 0;
 /* notice types of top level modules cannot change */
 for (ii = 0; ii < __numtopm; ii++)
  {
   itp = __it_roots[ii];
   flmdp = itp->itip->imsym->el.emdp;
   itp->itinum = (flmdp->lastinum)++;
   reassign2_itnums(itp);
  }
 /* ---
 if (__debug_flg)
  {
   __dbg_msg("==> dumping itree with reset inst numbers\n"); 
   for (ii = 0; ii < __numtopm; ii++) __dmp_itree(__it_roots[ii]);
  }
 --- */
}

/*
 * non top level built itree for inst. of one module
 *
 * know up instance pointers point to allocated but not set itree nodes
 * for each inst. in module one up
 * try to make as breadth first as possible
 */
static void reassign2_itnums(struct itree_t *new_itp)
{
 int32 ii;
 struct itree_t *itp;
 struct mod_t *imdp, *mdp;

 imdp = new_itp->itip->imsym->el.emdp;
 /* fill contained itree instance contents */ 
 for (ii = 0; ii < imdp->minum; ii++)
  {
   /* alloc sets inst_t value */
   itp = &(new_itp->in_its[ii]);
   mdp = itp->itip->imsym->el.emdp;
   itp->itinum = (mdp->lastinum)++;
  }
 /* finally down 1 level */
 for (ii = 0; ii < imdp->minum; ii++)
  reassign2_itnums(&(new_itp->in_its[ii]));
}

/*
 * ROUTINES TO SET POUND AND DEFPARAMS 
 */

/*
 * must set pound params by top down scan of itree
 * rule is first set all pound params
 */
extern void __set_poundparams(void)
{
 int32 ii;
 struct itree_t *itp; 

 for (ii = 0; ii < __numtopm; ii++)
  {
   /* since pound params change params one level down - none at top */
   itp = __it_roots[ii];
   set2_poundparams(itp);
  }
}

/*
 * set pound params
 * try to make as breadth first as possible
 */
static void set2_poundparams(struct itree_t *up_itp)
{
 int32 ii, ii2;
 int32 giawid, is_giarr;
 struct itree_t *itp;
 struct inst_t *ip, *ip2;
 struct mod_t *up_mdp;
 struct gia_aux_t *giap;

 up_mdp = up_itp->itip->imsym->el.emdp;
 giap = NULL;
 giawid = 0;
 for (ii = 0; ii < up_mdp->minum; ii++)
  {
   ip2 = &(up_mdp->minsts[ii]);
   if ((giap = ip2->i_giap) != NULL)
    {
     giawid = __get_gia_wide(giap);
     is_giarr = TRUE;
    }
   else is_giarr = FALSE;

   /* if module no params or none set nil, if some set non nil but some */
   /* locations will be nil instead of pointing to up pound param expr. */
   itp = &(up_itp->in_its[ii]);
   ip = itp->itip;

   /* for giarr's in each expanded instance although since no generate */
   /* all are the same */
   if (is_giarr)
    {
     if (ip->ipxprtab != NULL)
      {
       for (ii2 = ii; ii2 < ii + giawid; ii2++)
        {
         itp = &(up_itp->in_its[ii2]);
         __set_1inst_pound_params(itp, TRUE);
        }
      } 
    }
   else { if (ip->ipxprtab != NULL) __set_1inst_pound_params(itp, FALSE); }

   /* skip all but first instance of instance array expanded */
   /* works because know all must have same type */
   /* for array of instances, need master ip in giarr */ 
   if (is_giarr) { giawid = __get_gia_wide(giap); ii += (giawid - 1); }
  }
 /* finally down 1 level */
 for (ii = 0; ii < up_mdp->minum; ii++)
  {
   set2_poundparams(&(up_itp->in_its[ii]));

   /* skip all but first instance of instance array expanded */
   /* works because know all must have same type */
   /* for array of instances, need master ip in giarr */ 
   ip2 = &(up_mdp->minsts[ii]); 
   if (ip2->i_giap != NULL)
    {
     /* SJM 05-17-10 - was possibly using wrong or nil giap here */ 
     giawid = __get_gia_wide(ip2->i_giap);
     ii += (giawid - 1);
    }
  }
}

/*
 * set the pound parameters for all of 1 instance down
 *
 * only called if instance has at least one pound param
 * 
 * for anything set here must evaluate to number because this is the next
 * place in sort order but must leave as expr. because some other
 * instances of IS form parameter may need to use default
 */
extern void __set_1inst_pound_params(struct itree_t *itp, int32 is_giarr) 
{
 int32 pi;
 struct expr_t *pxp;
 struct mod_t *imdp;
 struct inst_t *ip;
 struct xstk_t *xsp;
 struct net_t *modnp;
 
 /* top module can not be destination of pound params */
 /* DBG remove --- */
 if (itp->up_it == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 ip = itp->itip;
 /* SJM 11-30-09 - imdp is down module */
 imdp = itp->itip->imsym->el.emdp; 
 /* pound parameters are nets (param var typ) defined in module */
 /* if # param list short ok, do not change last */
 for (pi = 0; pi < imdp->mprmnum; pi++)
  {
   /* SJM 11-30-09 - pxp is in up module above imdp instance */ 
   /* ipxprtab is per instance in up mdp */
   pxp = ip->ipxprtab[pi];
   /* explicit form with this one unused or short list */
   if (pxp == NULL) continue;

   /* SJM 11-30-09 - in down mod np may be used on rhs of lots of prm defs */ 
   modnp = &(imdp->mprms[pi]);

   /* SJM 06-17-09 - this was wrong - when recalcing each pound param inst */
   /* must look to see if the pound param is set in that inst */
   /* can't use a per downconn mod param bit - must be per inst */

   /* SJM 06-17-08 - canbe means at least in one inst this param set by */
   /* pound param - if non IS form, then can just use this bit to avoid */
   /* recalculating a parameters value from possibly changed rhs params */ 
   modnp->nu.ct->p_canbe_setby_pndprm = TRUE;

   /* use whatever parm values in rhs are current to freeze rhs to num */
   /* here is the source order point for pound param */
   /* must evaluate in instantiating module but set in lower */ 
   __push_itstk(itp->up_it);

   /* AIV 11-30-01 - eval xpr reqires correct size setting, but if */
   /* declare from rhs param changed by pound or def or other previous rhs */
   /* change, sizes will not be set right - must reset here */
   __set_rhswidth(pxp, 0);

   xsp = __eval_xpr(pxp);
   __pop_itstk();
   
   /* know this is parameter */
   /* if not already in IS form convert and make each inst. old expr. */
   /* providing more than one inst. - 1st inst. set from # parm if >1 insts */
   /* causes change to IS form */
   if (modnp->srep == SR_PNUM)
    {
     /* special case, if part of inst array, never convert to IS form */
     /* because each inst array its own type and all params must be same */
     if (is_giarr)
      {
       __assgn_2005_nonis_param(modnp, pxp, xsp);
       goto chk_dbg; 
      }

     /* this will replicate initial value and change srep */
     if (imdp->flatinum > 1 && !modnp->nu.ct->n_widthdet)
      {
       __chg_param_tois(modnp, imdp);
      }
     else
      {
       __assgn_2005_nonis_param(modnp, pxp, xsp);
       goto chk_dbg; 
      }
    }
   assgn_2005_is_param(modnp, xsp, pxp, itp->itip->imsym->el.emdp->flatinum,
    itp->itinum);

   /* update paramter value but leave original expr. - needed if user */
   /* wants different parameter assign algorithm */

   /* should dump parameter size info here */
chk_dbg:
   if (__debug_flg)
    {
     __push_itstk(itp);
     __dbg_msg(
      "+++ setting # param %s to %s in module %s (%d insts) from inst. %s\n",
      modnp->nsym->synam, __pregab_tostr(__xs, xsp->ap, xsp->bp, modnp),
      imdp->msym->synam, imdp->flatinum, ip->isym->synam);
     __pop_itstk();
    }
   __pop_xstk();
  }
}

/*
 * assign new val to non IS parameter - new algorithm assign always the same
 *
 * SJM 11-24-09 - new 2005 LRM requires exactly the same parameter assignment
 * from a rhs expr (maybe defparam rhs, maybe pound param, maybe re-eval of
 * decl expr) the 3 ncomp_t bits determine if rng declared, type declared
 * or signed declared (actual declaration in src used to set the 3 bits), if
 * not declared the rhs every time of a param assign is used to change the
 * declaration - can happen multiple times
 *
 * SJM 11-24-09 - notice that range with no type implies unsigned reg, if a
 * type keyword (such as integer or time) is give that is same as an explicit
 * declaration, according 2.12, if just signed appears, the range comes
 * from the rhs
 *
 * must pass xsp since for def params eval of rhs itree context complex even
 * for non IS case
 */
extern void __assgn_2005_nonis_param(struct net_t *np, struct expr_t *xrhs,
 struct xstk_t *xsp)
{
 int32 owlen, nwlen;

 /* AIV 12/06/11 - if #(12'd2048) this is not signed - rare bug if was */
 /* the exact size and signed.  May need to now turn it off if not declared */
 /* with keyword 'signed' */
 //AIV LOOKATME - genvar exprs should be signed??
 if (!np->nu.ct->psigndecl && (np->n_signed && !xrhs->has_sign) &&
     !np->nu.ct->p_genvar)
  {
   np->n_signed = FALSE;
  }

 /* case 1: rng and probably type and maybe signed - true parm net type decl */
 if (np->nu.ct->prngdecl || np->nu.ct->ptypdecl)
  {
   __cnvt_decl_param_stkval(xsp, xrhs, np);
   nwlen = wlen_(np->nwid);
   memcpy(np->prm_nva.wp, xsp->ap, 2*nwlen*WRDBYTES); 
  }
 else
  {
   /* case 2: signed keyword but no rng or type - width from rhs but */
   /* signed keyword may appear */
   owlen = wlen_(np->nwid);
   nwlen = wlen_(xsp->xslen);
   if (owlen != nwlen)
    {
     __my_free(np->prm_nva.wp, 2*WRDBYTES*owlen);
     np->prm_nva.wp = (word32 *) __my_malloc(2*WRDBYTES*nwlen);
    }
   memcpy(np->prm_nva.wp, xsp->ap, 2*nwlen*WRDBYTES); 
   /* can rebuild the net after the value copy */
   rebld_undecl_parm_net(xsp, xrhs, np);
  }

 /* also use rhs constant value if string/non string */
 if (xrhs->is_string) np->nu.ct->pstring = TRUE;
 else { np->nu.ct->pstring = FALSE; np->nu.ct->pbase = BDEC; } 
}

/*
 * routine to possibly change the stack xsp result of a declared parameter rhs
 * expr to the right xsp value (width, signedness, type etc.)
 */
static void __cnvt_decl_param_stkval(struct xstk_t *xsp, struct expr_t *xrhs,
 struct net_t *np)
{
 /* DBG remove -- */
 if (!np->n_isaparam) __arg_terr(__FILE__, __LINE__);
 /* --- */

 /* case 1: declared to be real - convert if needed */
 if (np->ntyp == N_REAL)
  { 
   if (!xrhs->is_real) __cnv_stk_fromreg_toreal(xsp, (xrhs->has_sign == 1));
  }
 else 
  { 
   /* know declaration of param is non real */ 
   if (xrhs->is_real) __cnv_stk_fromreal_toreg32(xsp);

   /* but it may have wrong width or signedness */
   if (xsp->xslen < np->nwid)
    {
     if (np->n_signed) __sgn_xtnd_widen(xsp, np->nwid);
     else __sizchg_widen(xsp, np->nwid);
    }
   else if (xsp->xslen > np->nwid) __narrow_sizchg(xsp, np->nwid);
  }
}

/*
 * for undeclared width param that is changed according to rhs expr properties
 * rebuild the parameter
 *  
 * SJM 11-30-09 - think there may be a problem here - now when vpi_ (say) gets
 * pound param source properties it looks like passed down pound param was in
 * src - is this right?
 */
static void rebld_undecl_parm_net(struct xstk_t *xsp, 
 struct expr_t *xrhs, struct net_t *np)
{
 /* case 1: rhs real but so is current net type, nothing to do */
 if (xrhs->is_real && np->ntyp == N_REAL) return;

 /* case 2: rhs real, but param not yet real - fix it */
 if (xrhs->is_real && np->ntyp != N_REAL)
  {
   if (np->nwid != REALBITS)
    {
     np->nwid = REALBITS;
     if (np->nu.ct->nx1 != NULL) __free_xtree(np->nu.ct->nx1);
     if (np->nu.ct->nx2 != NULL) __free_xtree(np->nu.ct->nx2);
     np->nu.ct->nx1 = __bld_rng_numxpr((word32) REALBITS - 1, 0L, WBITS);
     np->nu.ct->nx2 = __bld_rng_numxpr(0L, 0L, WBITS);
     np->n_isavec = TRUE;
     np->n_signed = TRUE;
     np->nu.ct->pbase = BDBLE;
    }
   /* AIV 11/30/09 - need to set to type to real */
   np->ntyp = N_REAL;
   return;
  }

 /* case 3: reg that may need range change */
 /* if net already same width and non real nothing to do */
 if (xsp->xslen != np->nwid)
  {
   np->nwid = xsp->xslen;
   if (np->nu.ct->nx1 != NULL) __free_xtree(np->nu.ct->nx1);
   if (np->nu.ct->nx2 != NULL) __free_xtree(np->nu.ct->nx2);
   if (np->nwid == 1)
    {
     np->n_isavec = FALSE;
     np->nu.ct->nx1 = np->nu.ct->nx2 = NULL;
    }
   else
    {
     np->nu.ct->nx1 = __bld_rng_numxpr((word32) (np->nwid - 1), 0L, WBITS);
     np->nu.ct->nx2 = __bld_rng_numxpr(0L, 0L, WBITS);
     np->n_isavec = TRUE;
    }
  }
 /* for reg, signed keyword by itself force a signed reg */
 if (np->nu.ct->psigndecl) np->n_signed = TRUE;
}

/*
 * assign one new value at inst iti to IS parameter
 */
static void assgn_2005_is_param(struct net_t *np, struct xstk_t *xsp,
 struct expr_t *xrhs, int32 ninsts, int32 iti)
{
 int32 wlen, old_ninsts;
 word32 *wp;

 /* AIV 12/22/11 - the number of instances may have changed due to */
 /* generate expansion since chg_param_tois has first called */
 /* thus must be freed and resized to match the instances */
//AIV LOOKATME - better method???
 old_ninsts = np->nu.ct->isparam_ninsts; 
 /* free the old, alloc and copy the old */ 
 if (old_ninsts != -1 && ninsts > np->nu.ct->isparam_ninsts)
  {
   wlen = wlen_(np->nwid);
   wp = (word32 *) __my_malloc(2*wlen*WRDBYTES*ninsts); 
   memcpy(wp, np->prm_nva.wp, 2*wlen*WRDBYTES*old_ninsts); 
   __my_free(np->prm_nva.wp, 2*wlen*WRDBYTES*old_ninsts); 
   np->prm_nva.wp = wp;
   np->nu.ct->isparam_ninsts = ninsts;
  }

 /* case 1: rng and probably type and maybe signed - param net type declare */
 if (np->nu.ct->prngdecl || np->nu.ct->ptypdecl)
  {
   __cnvt_decl_param_stkval(xsp, xrhs, np);
  }
 else if (np->ntyp == N_REAL)
  {
   /* case 2: net type from previous rhs real, all must be real */
   /* and will be converted even if makes illegal or nonsense value */
//SJM 11-24-09 - LOOKATME??? - can only some be reals - think not
   if (!xrhs->is_real) __cnv_stk_fromreg_toreal(xsp, (xrhs->has_sign == 1));
  } 
 else
  {
   /* case 3: use rhs value - if wider may need to widen all */
   maybe_rebld_undecl_isparm_net(np, xsp, ninsts);
  }
 /* change this one inst */
//b.v SJM 05-30-10 - fails here
 wlen = wlen_(np->nwid);
 wp = &(np->prm_nva.wp[2*wlen*iti]);
 memcpy(wp, xsp->ap, 2*wlen*WRDBYTES); 
}

/*
 * routine to rebld a
 * if new value wider must free and realloc so all wider
 * also change new width - this is tricky case 
 */
static void maybe_rebld_undecl_isparm_net(struct net_t *np,
 struct xstk_t *xsp, int32 ninsts)
{
 int32 ii, owlen, nwlen;
 word32 *wp, *wp2, *wp3, *wp4; 

 owlen = wlen_(np->nwid);
 nwlen = wlen_(xsp->xslen);
 if (xsp->xslen > np->nwid)
  {
   /* save old area */ 
   wp2 = np->prm_nva.wp;
   /* allocate new area of new wider size */
   np->prm_nva.wp = (word32 *) __my_malloc(2*ninsts*WRDBYTES*nwlen);
   /* point to new area */
   wp = np->prm_nva.wp;
   for (ii = 0; ii < ninsts; ii++)
    {
     /* right inst. area of old value */
     wp3 = &(wp2[2*owlen*ii]);
     /* right inst of new area */
     wp4 = &(wp[2*nwlen*ii]);
     /* since widening must zero first */
     zero_allbits_(wp4, xsp->xslen);
     zero_allbits_(&(wp4[nwlen]), xsp->xslen);
     /* copy in to first arg - high bits 0 */
     cp_walign_(wp4, wp3, np->nwid);
     cp_walign_(&(wp4[nwlen]), &(wp3[owlen]), np->nwid);
    }

   /* finally free old */
   __my_free(wp2, 2*ninsts*WRDBYTES*owlen);
   /* only widening case */
   np->nwid = xsp->xslen;

   /* need to change range */
   if (np->nu.ct->nx1 != NULL) __free_xtree(np->nu.ct->nx1);
   if (np->nu.ct->nx2 != NULL) __free_xtree(np->nu.ct->nx2);
   np->nu.ct->nx1 = __bld_rng_numxpr((word32) (np->nwid - 1), 0L, WBITS);
   np->nu.ct->nx2 = __bld_rng_numxpr(0L, 0L, WBITS);
   np->n_isavec = TRUE;
  }
 else
  {
   /* if new narrower, widen */
   /* use net's signedness since if param declared sign will be on in net */
   if (xsp->xslen < np->nwid)
    {
     /* SJM 11-24-09 - can only sign extend if explicit signed but no rng */
     /* in declaration - if totally implicit, always unsigned */
     if (np->nu.ct->psigndecl) __sgn_xtnd_widen(xsp, np->nwid);
     else __sizchgxs(xsp, np->nwid);
    }
  }
}

/*
 * routine to replace all instances of original expression from
 * local defparam
 *
 * needed so vpi_ access of rhs expr gets right one from pound/defparam
 * not original source
 */
static void replace_param_rhs_expr(struct net_t *np, word32 *wp,
 struct mod_t *imdp)
{
 int32 wlen;
 double d1;
 struct expr_t *xp;

 /* free expr table and convert back if already IS form */
 if (np->nu.ct->parm_srep == SR_PISXPR)
  {
   __my_free(np->nu.ct->n_dels_u.d4x,
    imdp->flatinum*sizeof(struct expr_t *));
   np->nu.ct->parm_srep = SR_PXPR;
  }
 xp = __alloc_newxnd();
 wlen = wlen_(np->nwid);

 if (np->ntyp == N_REAL)
  {
   xp->optyp = REALNUM;
   xp->is_real = TRUE;
   /* SJM 03/25/02 - still need width - since no x part WBITS */
   xp->szu.xclen = WBITS;
   xp->ibase = np->nu.ct->pbase;

   memcpy(&d1, wp, sizeof(double)); 
   xp->ru.xvi = __alloc_shareable_rlcval(d1);
   np->nu.ct->n_dels_u.d1x = xp;
   return;
  }

 if (np->nwid <= WBITS)
  {
   xp->ru.xvi = __alloc_shareable_cval(wp[0], wp[1], np->nwid);
  }
 else
  {
   xp->ru.xvi = __allocfill_cval_new(wp, &(wp[2*wlen]), wlen);
  }

 xp->optyp = NUMBER;
 xp->ibase = np->nu.ct->pbase;
 if (np->nu.ct->pstring) xp->is_string = TRUE;
 if (np->n_signed) xp->has_sign = TRUE;

 np->nu.ct->n_dels_u.d1x = xp;
}

/*
 * set 1 defparam - know all splitting done 
 *
 * notice there be a slight memory leak here since old expression
 * value of parameter is not freed but no longer accessible from here
 * do not know if accessible form other place because no copy when
 * convert to IS form just have each point to the one expr.
 * 
 * know all defparams converted to rooted by here - never specparams here
 */
static void set_1defparam(struct dfparam_t *dfpp)
{
 int32 wlen;
 struct dfparam_t *mast_dfpp; 
 struct expr_t *lhsndp;
 struct net_t *np;
 struct xstk_t *xsp;
 struct mod_t *imdp;
 struct itree_t *itp;

 __sfnam_ind = dfpp->dfpfnam_ind;
 __slin_cnt = dfpp->dfplin_cnt;

 if (dfpp->idntmastdfp != NULL) mast_dfpp = dfpp->idntmastdfp; 
 else mast_dfpp = dfpp;

 /* first step evaluate to make sure rhs is constant needs to be done */
 /* here since source order and if leave param on rhs further defparam */
 /* may change which invalidates source order */
 if (dfpp->dfp_local)
  {
   imdp = dfpp->dfp_in_mdp;
   __push_wrkitstk(imdp, 0);

   /* AIV 11-30-01 - eval xpr reqires correct size setting, but if */
   /* declare from rhs param changed by pound or def or other previous rhs */
   /* change, sizes will not be set right - must reset here */
   __set_rhswidth(dfpp->dfpxrhs, 0);

   xsp = __eval_xpr(dfpp->dfpxrhs);
   __pop_wrkitstk();
  }
 else
  {
   /* SJM 04/24/05 - fix minor bug this must eval in actual defined in itree */
   /* loc not the master's - LOOKATME - is master needed here? */
   itp = __find_dfpbot_itp(dfpp);
   imdp = itp->itip->imsym->el.emdp;
   __push_itstk(itp);

   /* AIV 11-30-01 - eval xpr reqires correct size setting, but if */
   /* declare from rhs param changed by pound or def or other previous rhs */
   /* change, sizes will not be set right - must reset here */
   __set_rhswidth(dfpp->dfpxrhs, 0);

   xsp = __eval_xpr(dfpp->dfpxrhs);
   __pop_itstk();
  }

 /* now know rhs evaluated into xsp */
 /* only possibilities here are ident or global ident */
 lhsndp = dfpp->dfpxlhs;

 /* key is that this np must be np in target split off module */
 /* and know will be SYM N */
 if (lhsndp->optyp == ID) np = lhsndp->lu.sy->el.enp;
 else np = dfpp->targsyp->el.enp;
 /* SJM 02/28/04 - added flag since must know set by defparam for recalc */
 np->nu.ct->p_setby_defprm = TRUE;
 wlen = wlen_(np->nwid);

 /* DBG remove -- */
 if (!np->n_isaparam || np->nu.ct->p_specparam)
  __arg_terr(__FILE__, __LINE__);
 /* -- */

 /* if local applies to all instances and mast dfpp same */
 if (dfpp->dfp_local)
  {
   imdp = dfpp->dfp_in_mdp;
   /* since must be source order, change back from instance specific */
   if (np->srep == SR_PISNUM)
    {
     __my_free(np->prm_nva.wp, imdp->flatinum*2*WRDBYTES*wlen);
     np->srep = SR_PNUM;
     np->prm_nva.wp = (word32 *) __my_malloc(2*WRDBYTES*wlen);
    }
   memcpy(np->prm_nva.wp, xsp->ap, 2*WRDBYTES*wlen);

   /* change so original expression for all instances using new local */
   /* defparam evaluated rhs numeric expr. */
   /* makes vpi get value form parameter in vpi_ work */
   /* this may allocate expr nodes so need mod - although expr not needed */
   /* at run time */
   __push_wrkitstk(imdp, 0);
   replace_param_rhs_expr(np, xsp->ap, imdp);
   __pop_wrkitstk();
  }  
 else 
  {
   /* set the target itree place - use master if part of identical group */
   itp = __find_dfpbot_itp(mast_dfpp);
   imdp = itp->itip->imsym->el.emdp;
   /* change to IS NUM form only if more than 1 inst. of module */
   if (np->srep == SR_PNUM && imdp->flatinum > 1) __chg_param_tois(np, imdp);

   /* 06/06/00 - SJM - can't copy must use param assign routines */
   /* can be either IS or non IS form - but assign all insts*/ 
   if (np->srep == SR_PISNUM)
    { 
     assgn_2005_is_param(np, xsp, dfpp->dfpxrhs, imdp->flatinum, itp->itinum);
    }
   else __assgn_2005_nonis_param(np, dfpp->dfpxrhs, xsp);

   /* leave original expr. - only value of lhs parameter changes */
   /* allows using algorithm for assigning defparams */
  }
 /* DBG remove --- */
 if (__debug_flg)
  {
   __dbg_msg("+++ setting defparam %s path %s to %s (wid=%d) in module %s\n",
    np->nsym->synam, dfpp->gdfpnam, __pregab_tostr(__xs, xsp->ap, xsp->bp, np),
    np->nwid, imdp->msym->synam);
  }
 /* --- */
 __pop_xstk();
}

/*
 * recalculate all parameters with other params on rhs 
 * needed in case rhs params, changed from def or pound setting
 * 
 * SJM 02/28/04 - fixes bug not match LRM when pound/def set rhs expr param
 * LOOKATME - handling all cases although think some impossible
 *
 * LOOKATME - algorithm uses whatever net type is although strictly
 * speaking conversion when no explicit width/type given in param decl
 * could be needed - if change - then previous syntax checking invalidated
 */
extern void __recalc_param_vals(void)
{
 struct mod_t *mdp;
 int32 mlevel, chged, all_done;
 struct task_t *tskp;

 for (;;)
  {
   all_done = TRUE;
   chged = FALSE;

   /* SJM 03/16/04 - if static (source content) mod level d.s. changed */ 
   /* from splitting of pound params levelized lists updated dynamically */
   /* and if from def params will have been rebuilt */ 
   /* SJM 11-24-09 - start at root (top with max dagmaxdist) down to leafs */
   for (mlevel = __dagmaxdist; mlevel >= 0; mlevel--)
    {
     for (mdp = __mdlevhdr[mlevel]; mdp != NULL; mdp = mdp->mlevnxt)
      {
       /* DBG remove -- */
       if (__debug_flg)
        {
         __dbg_msg("++ recalc: level=%d mod=%s gd=%d pnum=%d minstnum=%d\n",
          mlevel, mdp->msym->synam, mdp->mod_parms_gd, mdp->mprmnum,
          mdp->minstnum);
        }
       /* --- */
       if (mdp->mod_parms_gd)
        {
         if (__debug_flg)
          {
           __dbg_msg(
            "### mlevel %d mod %s all parms mark good - no more down pnd parm setting\n",
            mlevel, mdp->msym->synam);
          }
         continue;
        }

       all_done = FALSE;
       /* if some other parent of this not recalced so know param val - look */
       /* for one that has all recalced - know will make progress in loop */
       if (!all_parent_mods_recalced(mdp)) continue;
       chged = TRUE;

       /* if no params mark as done */ 
       /* AIV 10/18/10 - need to check for no locparams as well */
       if (mdp->mprmnum == 0 && mdp->mlocprmnum == 0)
        {
         mdp->mod_parms_gd = TRUE;
         continue;
        }
       /* LOOKATME - always recalculate since can't detect if recalced */
       /* if no instance have pound params, does no extra checking */
       /* but can't call if top mod */  
       /* AIV 09/27/06 - no need to recalc local params here */
       if (mdp->minstnum != 0) recalc_1mod_pndparams(mdp);

       /* AIV 09/27/06 - must recalc all params/local parms/task local parm */
       /* after any pound param recalc done, can set params to final vals */
       recalc_1mod_params(mdp, mdp->mprms, mdp->mprmnum);
       /* recalc all the localparams */
       /* SJM 11-23-09 - local or tsk parms always good not set by pnd parms */
       recalc_1mod_params(mdp, mdp->mlocprms, mdp->mlocprmnum);
       /* recalc all the task localparams */
       for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
        {
         recalc_1mod_params(mdp, tskp->tsk_locprms, tskp->tlocprmnum);
        }

       /* now all parameters in this module set to good final value */
       mdp->mod_parms_gd = TRUE;
      }
    }
   if (all_done) break;
   /* if pass with no progress, internal error */
   if (!chged) __misc_terr(__FILE__, __LINE__);
  }
}

/*
 * recalc all params for one module
 *
 * know all parameters set by pound and/or def params have right value
 *
 * SJM 11-23-09 - if set by pound param inhibits val assign, return F
 * to indicate params possibly not all go0d
 */
static void recalc_1mod_params(struct mod_t *mdp, struct net_t *mprms, 
 int32 num)
{
 int32 pi, ii, wlen;
 struct net_t *np;
 struct xstk_t *xsp;
 struct expr_t *xp, **xtab;
 struct itree_t *itp, *up_itp;
 struct inst_t *ip;

 for (pi = 0; pi < num; pi++)
  {
   np = &(mprms[pi]);

   /* if rhs does not contain any parameter, or parameter set by defparam */
   /* that removes the rhs expr, no need to recalculate */      

   /* if a param is ever set by a defparam do not recalculate */  
//SJM 06-17-09 LOOKATME - what if only some insts set by defparams 
   if (np->nu.ct->p_setby_defprm) continue;

   /* SJM 06-17-09 - if a given inst's parameter is set by a pound param */
   /* the recalc for that inst eliminated below */
   /* can't set a bit that would wrongly apply to all instances */
   /* LRM pound params now use the as if flattended model */

   wlen = wlen_(np->nwid);
   /* case 1: param representation IS expr form */
   if (np->nu.ct->parm_srep == SR_PISXPR)
    {
     if (np->srep == SR_PNUM)
      {
       /* change to is num - not sure if can happen */
       __my_free(np->prm_nva.wp, 2*WRDBYTES*wlen);
       np->srep = SR_PISNUM;
       np->prm_nva.wp = (word32 *) __my_malloc(2*WRDBYTES*wlen*mdp->flatinum);
      }
     else if (np->srep != SR_PISNUM) __case_terr(__FILE__, __LINE__);
     /* eval expr for every inst */
     xtab = np->nu.ct->n_dels_u.d4x;
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       itp = mdp->moditps[ii];

       /* SJM 06-17-09 - if per inst params (differen insts set different) */
       /* pnd param values or some not set - only do not eval from rhs if */
       /* not set for this inst */
       up_itp = itp->up_it;
       if (up_itp != NULL)
        { 
         ip = up_itp->itip;
         if (ip->ipxprtab != NULL && ip->ipxprtab[pi] != NULL) continue;
        }

       __push_itstk(itp);
       xp = xtab[ii];

       /* AIV 11-30-01 - eval xpr reqires correct size setting, but if */
       /* decl from rhs param changed by pound or def or other previous rhs */
       /* change, sizes will not be set right - must reset here */
       __set_rhswidth(xp, 0);

       xsp = __eval_xpr(xp);
       assgn_2005_is_param(np, xsp, xp, mdp->flatinum, ii);
       __pop_xstk();

       __pop_itstk();
      }
     continue;
    }

   /* SJM 11-23-09 - only get here if not SR IS xpr - i.e. non IS */ 
   /* SJM 06-17-09 if param set by pnd param non per inst - if any inst */
   /* set all will be */
   if (np->nu.ct->p_canbe_setby_pndprm)
    { 
     if (__debug_flg)
      {
        __dbg_msg("### mod %s param %s srep=%d width %d can be set by pound param\n",
         mdp->msym->synam, np->nsym->synam, np->nu.ct->parm_srep, np->nwid);
      }
     continue;
    }
   
   if (np->nu.ct->parm_srep == SR_PXPR)
    {
     /* case 2: rhs expr non IS */
     if (np->srep == SR_PNUM)
      { 
       xp = np->nu.ct->n_dels_u.d1x;
       /* if any IS PNUM params on rhs, must also chg this to IS */
       if (xpr_has_is_param(xp))
        {
         __my_free(np->prm_nva.wp, 2*WRDBYTES*wlen);
         np->srep = SR_PISNUM;
         np->prm_nva.wp = (word32 *)
         __my_malloc(2*WRDBYTES*wlen*mdp->flatinum);
         set_parmval_from_isxpr(np, xp, mdp);
         continue;
        }
       /* case 2a: both non IS - any inst context works */
       __push_itstk(mdp->moditps[0]);

       /* AIV 11-30-01 - eval xpr reqires correct size setting, but if */
       /* decl from rhs param changed by pound or def or other previous rhs */
       /* change, sizes will not be set right - must reset here */
       __set_rhswidth(xp, 0);

       xsp = __eval_xpr(xp);
       __assgn_2005_nonis_param(np, xp, xsp);
       __pop_xstk(); 
       __pop_itstk();
       continue;
      }
     if (np->srep == SR_PISNUM)
      {
       /* SJM 04/09/02 - LOOKATME - can this case ever happen? */
       /* case 2b: param value IS but only one expr non IS) */
       /* only one value - can use any itree loc to eval */
       xp = np->nu.ct->n_dels_u.d1x;

       /* case 2a: both non IS - any inst context works */
       __push_itstk(mdp->moditps[0]);

       /* AIV 11-30-01 - eval xpr reqires correct size setting, but if */
       /* decl from rhs param changed by pound or def or other previous rhs */
       /* change, sizes will not be set right - must reset here */
       __set_rhswidth(xp, 0);

       xsp = __eval_xpr(xp);

       /* set same value for each */
       for (ii = 0; ii < mdp->flatinum; ii++)
        {
         assgn_2005_is_param(np, xsp, xp, mdp->flatinum, ii);
        }
       /* AIV 05/04/11 - need to pop stack here */
       __pop_itstk();
       __pop_xstk();
       continue;
      }
     __case_terr(__FILE__, __LINE__);
    }
   /* if this param changed by pound/def, bit may be on but now number */
  }
}

/*
 * recalculate all pound that are set by instances instantiating this mod
 *
 * new pound params calculation never requires to IS or size/type change
 */
static void recalc_1mod_pndparams(struct mod_t *mdp)
{
 int32 ii, pi;
 struct itree_t *itp, *up_itp;
 struct inst_t *ip;
 struct net_t *np; 
 struct expr_t *pxp;
 struct xstk_t *xsp;

 /* for every inst of the mod */
 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   itp = mdp->moditps[ii];
   ip = itp->itip;
   if (ip->ipxprtab == NULL) continue;

   if (itp->up_it == NULL) __misc_terr(__FILE__, __LINE__);
   up_itp = itp->up_it;
   /* if not pound params for this containing inst, nothing to do */

   /* must push since converts need down mod itree loc */
   __push_itstk(itp);
   /* for every non local param of mod */
   for (pi = 0; pi < mdp->mprmnum; pi++)
    {
     np = &(mdp->mprms[pi]);

     /* SJM 11-24-09 pxp is the high conn of the inst of mdp with pnd params */
     /* set again */
     pxp = ip->ipxprtab[pi];
     /* explicit form with this one unused or short list */
     if (pxp == NULL) continue;

     /* if pound param high conn expr does not contain param, nothing to do */ 
     /* SJM 03/01/04 - if rhs set by defparam can't recalc */  

     /* SJM 06-17-09 - if any inst set by def param, can't recalc */
//SJM 06-17-09 - maybe need to look to see if per inst set by def param?
     if (!__xpr_has_param(pxp) || np->nu.ct->p_setby_defprm)
      {
       if (__debug_flg)
        {
          __dbg_msg("### mod %s pnd param %s srep=%d width %d no params up\n",
           mdp->msym->synam, np->nsym->synam, np->nu.ct->parm_srep, np->nwid);
        }
       continue;
      }

     /* eval in up and know then any parameters used in expr */
     /* SJM 11-24-09 - need to eval pxp without any context - whatever on rhs */
     __push_itstk(up_itp);

     /* AIV 11-30-01 - eval xpr reqires correct size setting, but if */
     /* decl from rhs param changed by pound or def or other previous rhs */
     /* change, sizes will not be set right - must reset here */
     __set_rhswidth(pxp, 0);

     xsp = __eval_xpr(pxp);
     __pop_itstk();

     /* AIV 11/19/09 - width may have changed may need to adjust */
     /* to new width and assign new value */
     if (np->srep == SR_PNUM)
      {
       __assgn_2005_nonis_param(np, pxp, xsp);
      }
     else if (np->srep == SR_PISNUM)
      {
       assgn_2005_is_param(np, xsp, pxp, mdp->flatinum, ii);
      }
     else __case_terr(__FILE__, __LINE__);
     __pop_xstk();
    }
   __pop_itstk();
  }
}

/*
 * return T if parameter rhs expr contains IS rep param
 */
static int32 xpr_has_is_param(struct expr_t *ndp)
{
 struct sy_t *syp;
 struct net_t *np;
 struct expr_t *fandp;

 switch ((byte) ndp->optyp) { 
  case NUMBER: case REALNUM: case ISNUMBER: case ISREALNUM: return(FALSE);
  case ID:
   syp = ndp->lu.sy;
   if (!syp->sydecl || syp->sytyp != SYM_N) return(FALSE);
   np = syp->el.enp; 
   if (np->n_isaparam && np->srep == SR_PISNUM) return(TRUE);
   return(FALSE);
  case GLBREF: return(FALSE);
  case FCALL:
   for (fandp = ndp->ru.x; fandp != NULL; fandp = fandp->ru.x)
    {
     /* LOOKATME - even if real param not allowed arg to const systf */
     /* can be real */
     if (xpr_has_is_param(fandp->lu.x)) return(TRUE);
    }
   return(FALSE);
 } 
 if (ndp->lu.x != NULL) if (xpr_has_is_param(ndp->lu.x)) return(TRUE);
 if (ndp->ru.x != NULL) if (xpr_has_is_param(ndp->ru.x)) return(TRUE);
 return(FALSE);
}

/*
 * return T all paramters known in modules that use pound params to set
 * params in this module 
 *
 */
static int32 all_parent_mods_recalced(struct mod_t *mdp)
{
 int32 ii;
 struct itree_t *itp;

 /* if mod has no params trivially true */
 /* AIV 10/18/10 - need to check for locparams as well */
 if (mdp->mprmnum == 0 && mdp->mlocprmnum == 0) return(TRUE);
 /* if top mod, obviously T */ 
 if (mdp->minstnum == 0) return(TRUE);

 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   itp = mdp->moditps[ii];
   /* DBG remove -- */
   if (itp->up_it == NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */
   if (!itp->up_it->itip->imsym->el.emdp->mod_parms_gd) return(FALSE);
  }
 return(TRUE);
}

/*
 * set param value (nva) for P IS NUM net from one expr 
 */
static void set_parmval_from_isxpr(struct net_t *np, struct expr_t *xp,
 struct mod_t *mdp)
{
 int32 ii, wlen;
 word32 *wp;
 struct xstk_t *xsp;

 wlen = wlen_(np->nwid);
 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   __push_itstk(mdp->moditps[ii]);
   /* need to re-eval for every inst */

   /* AIV 11-30-01 - eval xpr reqires correct size setting, but if */
   /* decl from rhs param changed by pound or def or other previous rhs */
   /* change, sizes will not be set right - must reset here */
   __set_rhswidth(xp, 0);

   xsp = __eval_xpr(xp);
   /* SJM 09/29/03 - change to handle sign extension and separate types */
   if (xsp->xslen > np->nwid) __narrow_sizchg(xsp, np->nwid);
   else if (xsp->xslen < np->nwid)
    {
     if (xp->has_sign) __sgn_xtnd_widen(xsp, np->nwid);
     else __sizchg_widen(xsp, np->nwid);
    }

   wp = &(np->prm_nva.wp[ii*2*wlen]);
   memcpy(wp, xsp->ap, 2*wlen*WRDBYTES);
   __pop_xstk();
   __pop_itstk();
  }
}
