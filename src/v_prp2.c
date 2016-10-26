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
 * Verilog simulation preparation routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

#include "igen.h"

/* local prototypes */
/* --- SJM REMOVED static void setchk_trchan_wire(struct net_t *); */
static void setchk_1w_fifo(struct net_t *);
static int32 cnt_scalar_fo(struct net_t *);
static int32 has_npp_isform(struct net_pin_t *);
static void chkset_vec_fifo(struct net_t *, int32 *, int32 *, int32, int32,
 int32);
static int32 has_rng_npp(struct net_t *);
static struct itree_t *cnvt_to_itp(struct mod_t *, int32);
static struct itree_t *cnvt_todown_itp(struct itree_t *, struct mod_t *,
 int32);
static void chk_trifctrl_insame_chan(struct gate_t *, struct expr_t *);
static void chk_samechan_trifctrl_simple(struct mod_t *, struct gate_t *,
 int32, struct expr_t *, struct expr_t *);
static int32 net_in_expr(struct expr_t *, struct net_t *);
static void prep_tf_rwexprs(void);
static int32 lhs_has_figt1(struct expr_t *);
static void getpat_lhs_figt1(struct mod_t *, struct expr_t *,
struct conta_t *);
static void chk_decl_siderep(struct expr_t *, struct expr_t *, char *,
int32, word32, int32);
static int32 find_var_in_xpr(struct expr_t *, struct net_t *, int32 *);
static void add_portbit_map(struct tenp_t *, struct expr_t *, int32);
static void init_contas_idp_area(struct mod_t *);
static void init_gate_idp_area(struct mod_t *);
static void init_one_inst_conta_drv(word32 *, int32);
static void init_net_npp_tchk_idpvals(struct net_t *);
static word32 cmp_udpind(word32, word32);
static void init_one_inst_udp_state(struct gate_t *);
static void init_one_inst_gate_state(struct gate_t *);
static void init_real_var(struct net_t *);
static void init_string_var(struct net_t *);
static void init_arr_var(struct net_t *);
static void init_2state_arr_var(struct net_t *, int32);
static void init_scal_var(struct net_t *);
static void init_sscal_var(struct net_t *);
static void init_vec_var(struct net_t *);
static void init_vec2s_var(struct net_t *);
static void init_svec_var(struct net_t *);
static void init_var_random(struct net_t *);
static void init_random(word32 *, int32);
static void init_real_var_random(struct net_t *);
static void init_2state_arr_var_random(struct net_t *, int32);
static void init_arr_var_random(struct net_t *);
static void init_scal_var_random(struct net_t *);
static void init_vec2s_var_random(struct net_t *);
static void init_vec_var_random(struct net_t *);
static void set_net_dce_expr_ofs(struct net_t *, struct mod_t *);
static void set_net_npp_tchk_ofs(struct net_t *);
static int32 all_drvrs_bidirect(struct net_t *);
static void reinit_1wirereg(struct net_t *, struct mod_t *);
static void init_dce_exprval(struct dcevnt_t *);
static struct mod_t *dcep_ref_mod(struct dcevnt_t *);
static void init_dce_prevval(struct dcevnt_t *, struct mod_t *);
static void reorder_all_mods_ialst_always_first(void);
static void prep_stskcalls(struct st_t *, struct mod_t *);
static struct st_t *add_loopend_goto(struct st_t *, struct st_t *);
static void prep_case(struct st_t *);
static void prep_dctrl(struct st_t *);
static void cnv_cmpdctl_todu(struct st_t *, struct delctrl_t *);
static void prep_event_dctrl(struct delctrl_t *);
static void bld_ev_dces(struct expr_t *, struct delctrl_t *);
static void bld_evxpr_dces(struct expr_t *, struct delctrl_t *, int32);
static void linkon_dce(struct net_t *, int32, int32, struct delctrl_t *,
 int32, struct gref_t *);
static void fill_mda_wire_sym_wrkstab(struct net_t *, struct mda_t *,
 char *, int32, struct mod_t *);
static void init_iact_dce(struct dcevnt_t *, struct delctrl_t *,
 struct gref_t *);
static void prep_func_dsable(struct st_t *);
static void add_xmr_dcep_edge_list(struct mod_t *, struct dcevnt_t *);
static void xmr_linkon_dce(struct net_t *, int32, int32, struct delctrl_t *,
 int32, struct gref_t *);
static struct dcevnt_t *linkon2_dce(struct net_t *, int32, int32,
 struct delctrl_t *, int32, int32, struct mod_t *, struct mod_t *);
static struct dcevnt_t *linkon3_dce(struct net_t *, int32, int32,
 struct delctrl_t *, int32, int32, struct mod_t *, struct mod_t *, int32, 
 struct gref_t *, struct itree_t *, struct itree_t *);
static void bld_init_qcaf_dce_lstlst(struct st_t *);
static void prep_qc_assign(struct st_t *, int32);
static void prep_qc_deassign(struct st_t *);
static struct dceauxlst_t *prep_noncat_qc_assign(struct st_t *,
 struct expr_t *);
static struct dceauxlst_t *prep_noncat_qc_regforce(struct st_t *,
 struct expr_t *);
static void init_qcval(struct qcval_t *);
static void prep_qc_wireforce(struct st_t *);
static void prep_qc_wirerelease(struct st_t *);
static void prep_noncat_qc_wireforce(struct st_t *, struct expr_t *,
 struct dceauxlstlst_t *);
static void prep_noncat_qc_wirerelease(struct expr_t *);
static void bld_qcaf_dces(struct expr_t *, struct qcval_t *);
static void linkon_qcaf_dce(struct net_t *, int32, int32, struct gref_t *,
 struct qcval_t *);
static void process_upwards_grp(struct gref_t *);
static void chk_downrel_inst_sels(struct gref_t *);
static void prep_tchks(void);
static struct tchg_t *bld_start_tchk_npp(struct tchk_t *, struct net_t *,
 int32);
static struct chktchg_t *bld_check_tchk_npp(struct net_t *, int32);
static void prep_pths(void);
static int32 chk_pthels(struct spcpth_t *);
static int32 bldchk_pb_pthdsts(struct spcpth_t *);
static struct tchg_t *try_add_npp_dpthsrc(struct spcpth_t *, struct net_t *,
 int32);
static struct net_pin_t *find_1timchg_psnpp(struct net_t *, int32, int32);
static int32 bldchk_1bit_pthdst(struct spcpth_t *, struct net_t *, int32,
 struct net_t *, int32, int32, struct tchg_t *);
static void get_pthbitwidths(struct spcpth_t *, int32 *, int32 *);
static char *bld_bitref(char *, struct net_t *, int32);
static int32 chk_biti_pthdst_driver(struct spcpth_t *, struct net_t *, int32);
static void emit_pthdst_bit_informs(struct mod_t *);
static void free_dctrl(struct delctrl_t *, int32);
static void free_csitemlst(struct csitem_t *);
static void prep_get_qc_wirrng(struct expr_t *, struct net_t **, int32 *,
 int32 *, struct itree_t **);
static int32 net_needs_change(struct net_t *);
static struct net_t *get_low_wire_array_net(struct net_t *, struct mod_t *mdp);

static void add_stlst_mstmts_ndx(struct st_t *);
static struct st_t *add_1stmt_mstmts_ndx(struct st_t *);
static void add_csitemlst_mstmts_ndx(struct csitem_t *);
static void set_mstmt_stp(struct st_t *);
static void grow_prp_mstmt_ndx(void);
static void cmp_xform_ialst(struct mod_t *mdp);
static struct st_t *cmp_xform_lstofsts(struct mod_t *, struct st_t *);
static struct st_t *cmp_xform1_stmt(struct mod_t *, struct st_t *, 
 struct st_t *);
static void xform_tf_syst_enable(struct st_t *);
static void cmp_xform_csitemlst(struct mod_t *, struct csitem_t *);
static struct st_t *cxf_fixup_loopend_goto(struct st_t *, struct st_t *);
static void cxf_fixup_case_gotos(struct st_t *);
static void cxf_fixup_func_dsabl_gotos(struct st_t *);
static void cmp_xform_tasks(struct mod_t *);
static void init_1net_dces(struct net_t *, struct mod_t *);
static void init_net_toggle_ofs(struct mod_t *);
static void set_net_toggle_ofs(struct net_t *);

/* extern prototypes defined elsewhere */
extern void __setchk_all_fifo(void);
extern void __bld_pb_fifo(struct net_t *, int32 *, int32 *, int32 *, int32);
extern void __prep_exprs_and_ports(void);
extern void __alloc_tfdrv_wp(struct tfarg_t *, struct expr_t *,
 struct mod_t *);
extern void __init_tfdrv(struct tfarg_t *, struct expr_t *, struct mod_t *);
extern void __prep_contas(void);
extern void __allocinit_perival(union pck_u *, int32, int32, int32);
extern void __allocinit_stperival(union pck_u *, int32, struct net_t *,
 int32);
extern void __set_net_srep_types(void);
extern void __set_1net_srep(struct net_t *);
extern void __init_idp_nchgaction(void);
extern void __set_pre_idp_nchgaction_bits(void);
extern void __set_optimtab_bits(void);
extern void __set_all_mods_1inst_storage_offsets(void);
extern void __expand_1mod_idp_area(struct mod_t *, int32);
extern void __set_1var_net_ofs(struct net_t *, struct mod_t *);
extern void __alloc_sim_storage(void);
extern void __init_sim_storage(void);
extern void __init_var(struct net_t *);
extern int32 __get_array_srep_type(struct net_t *);
extern void __init_peri_vec_var(word32 *, int32, int32, int32, word32, word32);
extern int32 __get_initval(struct net_t *, int32 *);
extern void __reinitialize_vars(struct mod_t *);
extern int32 __get_dce_prevval_wsiz(struct dcevnt_t *, struct net_t *);
extern void __initialize_dces(struct mod_t *);
extern void __prep_stmts(void);
extern struct st_t *__prep_lstofsts(struct st_t *, int32, int32);
extern void __push_prpstmt(struct st_t *);
extern void __pop_prpstmt(void);
extern void __push_nbstk(struct st_t *);
extern void __pop_nbstk(void);
extern void __dce_turn_chg_store_on(struct mod_t *, struct dcevnt_t *, int32);  
extern struct dcevnt_t *__alloc_dcevnt(struct net_t *);
extern int32 __is_upward_dsable_syp(struct sy_t *, struct symtab_t *,
 int32 *);
extern void __prep_xmrs(void);
extern void __fill_grp_targu_fld(struct gref_t *);
extern void __prep_specify(void);
extern void __xtract_wirng(struct expr_t *, struct net_t **, int32 *,
 int32 *);
extern void __free_1stmt(struct st_t *);
extern void __free_xprlst(struct exprlst_t *);
extern struct expr_t *__get_lvalue_idndp(struct expr_t *);
extern void __getarr_range(struct net_t *, int32 *, int32 *, int32 *);
extern struct sy_t *__get_sym(char *, struct symtab_t *);

extern void __my_free(void *, size_t);
extern char *__msg2_blditree(char *, struct itree_t *);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_tsktyp(char *, word32);
extern char *__my_malloc(size_t);
extern struct st_t *__alloc2_stmt(int32, int32, int32);
extern void __getwir_range(struct net_t *, int32 *, int32 *);
extern void __set_gchg_func(struct gate_t *);
extern int32 __isleaf(struct expr_t *);
extern struct net_t *__find_tran_conn_np(struct expr_t *);
extern int32 __get_pcku_chars(int32, int32);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern void __st_perinst_val(union pck_u, int32, word32 *, word32 *);
extern void __st_idp_val(word32 *, int32, word32 *, word32 *);
extern char *__to_idnam(struct expr_t *);
extern int32 __get_arrwide(struct net_t *);
extern void __reinit_regwir_putvrec(struct net_t *, int32);
extern void __reinit_netdrvr_putvrec(struct net_t *, struct mod_t *);
extern int32 __dce_needs_prevval(struct dcevnt_t *, struct mod_t *);
extern void __init_1instdce_prevval(struct dcevnt_t *);
extern void __alloc_plidce_prevval(struct dcevnt_t *);
extern int32 __get_dcewid(struct dcevnt_t *, struct net_t *);
extern void __ld_wire_sect(struct xstk_t *, struct net_t *, int32, int32);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern char *__to_sttyp(char *, word32);
extern char *__bld_lineloc(char *, word32, int32);
extern void __add_dctldel_pnp(struct st_t *);
extern void __prep_delay(struct gate_t *, struct paramlst_t *, int32, int32,
 char *, int32, struct sy_t *, int32);
extern struct itree_t *__itp_xmrget_refgrp_to_targ(struct gref_t *, 
 struct itree_t *);
extern int32 __ip_indsrch(char *);
extern struct itree_t *__find_unrt_targitp(struct gref_t *, struct itree_t *,
 int32);
extern void __add_tchkdel_pnp(struct tchk_t *, int32);
extern void __conn_npin(struct net_t *, int32, int32, int32, int32,
 struct gref_t *, int32, char *);
extern void __add_pathdel_pnp(struct spcpth_t *);
extern char *__to_deltypnam(char *, word32);
extern void __free_xtree(struct expr_t *);
extern void __free_del(union del_u, word32, int32);
extern int32 __chk_0del(word32, union del_u, struct mod_t *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern void __dmp_msttab(struct mod_t *, int32);
extern void __dmp_stmt(FILE *, struct st_t *, int32);
extern struct expr_t *__copy_expr(struct expr_t *);
extern struct mod_t *__get_mast_mdp(struct mod_t *);
extern struct net_t *__tranx_to_netbit(struct expr_t *, int32, int32 *,
 struct itree_t *);
extern struct mipd_t *__get_mipd_from_port(struct mod_pin_t *, int32);
extern struct tenp_t *__bld_portbit_netbit_map(struct mod_pin_t *);
extern struct net_pin_t *__alloc_npin(int32, int32, int32);
extern void __alloc_qcval(struct net_t *);
extern void __prep_insrc_monit(struct st_t *, int32, struct mod_t *);
extern int32 __cnt_dcelstels(struct dcevnt_t *);
extern void __dcelst_off(struct dceauxlst_t *);
extern void __xform_nl_stmts(void);
extern void __cxf_fixup_lstofsts_gotos(struct st_t *, int32);
extern void __bld_provisional_mstabs(void);
extern int32 __get_itp_const_bselndx(struct expr_t *);
extern void __reinit_all_contas_in_mod(struct mod_t *);
extern void __init_all_inst_conta_drv(int32, int32, struct mod_t *);
extern struct net_t *__get_prep_indexed_psel_range(struct expr_t *, int32 *, 
 int32 *);
extern int32 __is_int_atom_typ(int32);
extern int32 __is_2state_typ(int32);
extern int32 __is_net_dumped(struct net_t *);
extern void __fill_wire_arr_sym_wrkstab(struct net_t *, struct mod_t *);
extern void __fill_wire_arr_wrkstab(struct net_t *);
extern void __try_to_fold_for_loops(void);
extern void __set_expr_fold_value_stlst(struct st_t *);
extern struct st_t *__copy_lstofsts(struct st_t *);
extern void __chk_lstofsts(struct st_t *);
extern struct expr_t *__alloc_newxnd(void);
extern void __set_numval(struct expr_t *, word32, word32, int32);
extern struct st_t *__alloc_stmt(int32);
extern int32 __rtl_dist_uniform(int32 *, int32, int32);
extern char *__msgexpr_tostr(char *, struct expr_t *);
#ifdef __XPROP__
extern void __eligible_xprop_stofsts(struct st_t *, int32 *);
extern struct st_t *__copy_stmt(struct st_t *);
extern void __prep_xprop_stmts(int32);
extern void __free_xprop(struct xprop_t *);
#endif

extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __sgfwarn(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern void __pv_ferr(int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __dbg_msg(char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __misc_sgfterr(char *, int32);
extern void __misc_gfterr(char *, int32, word32, int32);
extern void __sgfterr(int32, char *, ...);
extern void __my_fprintf(FILE *, char *, ...);
extern void __free_stlst(struct st_t *);

static void link_qc_to_dces(struct mod_t *, struct st_t *);
static void link_stmt_to_dce_list(struct dceauxlst_t *, struct st_t *);

static void bld_1mod_idp_map(struct mod_t *);
static void set_net_dce_idp_map(struct net_t *, struct mod_t *);
static void set_net_tchk_chg_val_idp_map(struct net_t *, struct mod_t *);
static void alloc_fill_ctevtab_idp_map_els(struct mod_t *, struct ctev_t **,
 int32, int32, void *);
static void alloc_fill_ctevp_idp_map_el(struct mod_t *, struct ctev_t *,
 int32, void *);
static void alloc_fill_idp_map_el(struct mod_t *, int32, int32, int32, void *);

static void set_conta_idp_ofs(struct mod_t *);
static void set_gate_idp_ofs(struct mod_t *);
static void set_nchg_idp_ofs(struct mod_t *);
static void set_tevs_idp_ofs(struct mod_t *);
static void set_isnum_idp_ofs(struct mod_t *);
static int32 mark_if_scalar_port_optim_mdprt(struct net_t *, struct mod_t *);
static void mark_scalar_port_optim_ofs(struct net_t *, struct mod_t *);
static int32 isnum_cmp(const void *, const void *);
static int32 get_1net_idp_wlen(struct net_t *);
static int32 get_rhs_del_storage_wlen(struct st_t *);
static void grow_dce_table(struct dce_info_t *);
static struct st_t *try_fold_for_loop_stmt(struct st_t *);
static void try_fold_for_loop_lstofstmts(struct st_t *);
static struct net_t *is_for_foldable(struct st_t *, int32 *, int32 *, int32 *);
static struct st_t *fold_for_loop(struct st_t *, int32, int32, struct net_t *, 
 int32);

extern char *__my_realloc(void *, size_t, size_t);
extern void __alloc_compiled_sim_storage(void);
extern void __init_compiled_sim_storage(void);
extern void __set_all_toggles_off(void);
extern void __set_all_tgl_lastvals_tox(void);
extern void __init_var(struct net_t *);
extern int32 __is_const_expr(struct expr_t *);
extern int32 __gate_needs_output_word(int32);
extern void __add_dcep_to_table(struct net_t *, struct dcevnt_t *);
extern void __add_expr_totable(struct expr_t *);
extern struct avlnode_t **__linearize_avl_tree(struct avlhd_t *, int32 *);
extern void __add_isnum_to_tree(void *, int32, int32);
extern int32 __net_chg_nd_store(struct net_t *, int32, int32);
extern struct net_chg_t *__find_nchg_range(struct net_t *, int32, int32);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern int32 __needs_netchg_record(struct net_t *);
extern int32 __get_lhs_srep(struct expr_t *, int32 *);

extern const word32 __masktab[];

int32 __prep_numsts;

/*
 * FAN OUT AND PORT COLLAPSING ROUTINES
 */

/*
 * set and check all wire fi and fo
 * here must ignore any added for unc. bid. wires
 * cannot check fifo for wires in tran channels 
 *
 * LOOKATME - maybe allocate different formats depending on fi/fo
 * to keep lists short 
 * 
 * SJM - 06/25/00 - difference from 2018c since change chg state algorithm
 */
extern void __setchk_all_fifo(void)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum == 0) continue;

   __push_wrkitstk(mdp, 0);
   for (ni = 0, np = &(__inst_mod->mnets[0]); ni < __inst_mod->mnnum;
    ni++, np++)
    {
     /* --- SJM 11/20/01 - removed since useless and slow 
     if (np->ntraux != NULL) { setchk_trchan_wire(np); continue; }
     --- */
     if (np->ntyp >= NONWIRE_ST) continue;
     setchk_1w_fifo(np);
    }
   __pop_wrkitstk();
  }
} 

/*
 * check for tran channels with some bits in and some not
 * for non tran channel wires (no edges) remove vibp
 * notice all tran connected nets have fi>1 set 
 */
/* --- SJM 11/20/01 - removed since warning useless and this takes too
      long to make freeing rare small amount of memory worth it 
 
static void setchk_trchan_wire(struct net_t *np) 
{
 int32 bi, ii;
 struct traux_t *trap;
 struct itree_t *itp;
 struct vbinfo_t *vbip;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 trap = np->ntraux;
 for (bi = 0; bi < np->nwid; bi++)
  {
   for (ii = 0; ii < __inst_mod->flatinum; ii++)
    {
     vbip = trap->vbitchans[ii*np->nwid + bi];
     if (vbip != NULL) 
      {
       if (vbip->vivxp->vedges != NULL) continue;
       __my_free(vbip, sizeof(struct vbinfo_t));
       trap->vbitchans[ii*np->nwid + bi] = NULL; 
      } 
     -* SJM 01/26/99 - new connect modules not in tran channels *- 
     if ((itp = cnvt_to_itp(__inst_mod, ii)) == NULL) continue;

     sprintf(s1, "in %s(%s):", __inst_mod->msym->synam,
      __msg2_blditree(__xs, itp));
     if (np->n_isavec) sprintf(s3, "%s[%d]", np->nsym->synam, bi);
     else strcpy(s3, np->nsym->synam); 
     __gfinform(450, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
      "%s %s %s not in any transistor channel but other bits are",
       s1, __to_wtnam(s2, np), s3);
    }
  }
}
--- */

/*
 * set and check for 1 wire
 * but no warns or informs
 *
 * sets n_multfi bit, but not set for tran channel's which need fi>1 eval
 * because instead x_multfi is set, n_multfi used for other checking
 */
static void setchk_1w_fifo(struct net_t *np)
{
 int32 ii;
 int32 scalfo, nd_fi_chk;
 int32 *pbfi, *pbfo, *pbtcfo;
 char s1[RECLEN];
 
 /* no matter what tri0/tri1 and supply0/supply1 must be multi-fi */
 switch ((byte) np->ntyp) {
  case N_TRI0: case N_TRI1: case N_TRIREG: case N_SUPPLY0: case N_SUPPLY1:
   np->n_multfi = TRUE;
 }

 /* special case 1: pullup - must be constant - no fi */
 nd_fi_chk = TRUE;
 /* special case 1: supply should not have fan-in - no effect */
 if (np->ntyp == N_SUPPLY0 || np->ntyp == N_SUPPLY1)
  {
#ifndef __CVC_RT__
   if (np->ndrvs != NULL)
    {
     __gfwarn(607, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
      "in %s: %s %s has driver(s) that have no effect",
      __inst_mod->msym->synam, __to_wtnam(s1, np), np->nsym->synam);
    }
#endif
   /* pwr/gnd should not have drivers */
   nd_fi_chk = FALSE;
  }
 /* case 2: scalar */
 if (!np->n_isavec)
  {
   if (nd_fi_chk)
    {
     if (np->ndrvs == NULL)
      {
       if (np->nsym->sy_impldecl) 
        __gfinform(420, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
         "in %s: implicitly declared scalar wire %s has no drivers",
         __inst_mod->msym->synam, np->nsym->synam);
       else __gfinform(427, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
        "in %s: scalar wire %s has no drivers", __inst_mod->msym->synam,
        np->nsym->synam);
      } 
     else if (np->ndrvs->npnxt != NULL) np->n_multfi = TRUE;
    }
   /* scalar case multi fo set */  
   scalfo = cnt_scalar_fo(np);
   if (scalfo == 0)
    {
     if (np->nsym->sy_impldecl) 
      __gfinform(429, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
      "in %s: implicitly declared scalar wire %s drives no declarative fan-out",
       __inst_mod->msym->synam, np->nsym->synam);
     else __gfinform(426, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
      "in %s: scalar wire %s drives no declarative fan-out",
      __inst_mod->msym->synam, np->nsym->synam);
    }
   return;
  }
 /* case 4: wire that is not scalar */
 pbfi = (int32 *) __my_malloc(sizeof(int32)*np->nwid);
 pbfo = (int32 *) __my_malloc(sizeof(int32)*np->nwid);
 pbtcfo = (int32 *) __my_malloc(sizeof(int32)*np->nwid);
 if (!has_npp_isform(np->ndrvs))
  {
   /* notice not using t chg counts for now */
   __bld_pb_fifo(np, pbfi, pbfo, pbtcfo, 0);
   chkset_vec_fifo(np, pbfi, pbfo, 0, FALSE, nd_fi_chk);
  }
 else
  {
   /* tricky has IS form case - must do for every inst */
   /* if any inst. has fi > 1, then wire must be all multi fan in */
   for (ii = 0; ii < __inst_mod->flatinum; ii++)
    chkset_vec_fifo(np, pbfi, pbfo, ii, TRUE, nd_fi_chk);
  }
  /* notice task/func/lb variables always regs - never fi > 1 */
  /* done free the tables */
 __my_free(pbfi, sizeof(int32)*np->nwid);
 __my_free(pbfo, sizeof(int32)*np->nwid);
 __my_free(pbtcfo, sizeof(int32)*np->nwid);
}

/*
 * return number of non TCHG fan out for scalar
 * MIPD never seen here - only added by PLI or SDF after elaboration
 */
static int32 cnt_scalar_fo(struct net_t *np)
{
 int32 nfi;
 struct net_pin_t *npp;

 for (nfi = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_TCHG) nfi++; 
  }
 return(nfi);
}

/*
 * return T if has IS (-2) form net pin list entry  
 */
static int32 has_npp_isform(struct net_pin_t *npp)
{
 struct npaux_t *npauxp;

 for (; npp != NULL; npp = npp->npnxt)
  { if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 == -2) return(TRUE); }
 return(FALSE);
}

/*
 * build per bit fi and fo tables - caller must pass wide enough tables
 */
extern void __bld_pb_fifo(struct net_t *np, int32 *pbfi, int32 *pbfo,
 int32 *pbtcfo, int32 ii)
{
 int32 bi;
 struct net_pin_t *npp;
 struct npaux_t *npauxp;
 word32 *wp;

 memset(pbfi, 0, sizeof(int32)*np->nwid);
 memset(pbfo, 0, sizeof(int32)*np->nwid);
 memset(pbtcfo, 0, sizeof(int32)*np->nwid);

 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   /* AIV 07/28/09 - now need to handle wire array ranges here */
   /* these are transformed to regular scalar - was causing segv */
   /* issues by accessing out of range arrays below */
   /* these should be free no longer have a range - may as well do here ??? */
   if (npp->npaux != NULL && np->n_isarr && np->ntyp < NONWIRE_ST)
    {
     __my_free(npp->npaux, sizeof(struct npaux_t));
     npp->npaux = NULL;
    }

   if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1) 
    {
     for (bi = 0; bi < np->nwid; bi++) (pbfi[bi])++;
     continue;
    }
   if (npauxp->nbi1 == -2)
    { 
     /* SJM 10/12/04 - because contab realloced, must be ndx base of IS */
     wp = &(__contab[npauxp->nbi2.xvi]);
     /* DBG remove - here should never has x in index */
     if (wp[2*ii + 1] != 0L) __arg_terr(__FILE__, __LINE__);
     bi = (int32) wp[2*ii];
     (pbfi[bi])++;
     continue;
    }
   for (bi = npauxp->nbi1; bi >= npauxp->nbi2.i; bi--) (pbfi[bi])++;
  }
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* AIV 07/28/09 - now need to handle wire array ranges here */
   /* these are transformed to regular scalar - was causing segv */
   /* issues by accessing out of range arrays below */
   /* these should be free no longer have a range */
   /* these should be free no longer have a range - may as well do here ??? */
   if (npp->npaux != NULL && np->n_isarr && np->ntyp < NONWIRE_ST)
    {
     __my_free(npp->npaux, sizeof(struct npaux_t));
     npp->npaux = NULL;
    }
   if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1) 
    {
     for (bi = 0; bi < np->nwid; bi++)
      {
       /* MIPD never seen here - only added by PLI or SDF after elaboration */
       if (npp->npntyp == NP_TCHG) (pbtcfo[bi])++; else (pbfo[bi])++; 
      }
     continue;
    }
   if (npauxp->nbi1 == -2)
    { 
     /* SJM 10/12/04 - because contab realloced, must be ndx base of IS */
     wp = &(__contab[npauxp->nbi2.xvi]);
    
     /* DBG remove - here should never has x in index */
     if (wp[2*ii + 1] != 0L) __arg_terr(__FILE__, __LINE__);
     bi = (int32) wp[2*ii];
     if (npp->npntyp == NP_TCHG) (pbtcfo[bi])++; else (pbfo[bi])++; 
     continue;
    }
   for (bi = npauxp->nbi1; bi >= npauxp->nbi2.i; bi--)
    { if (npp->npntyp == NP_TCHG) (pbtcfo[bi])++; else (pbfo[bi])++; } 
  }
}

/*
 * check fan-in and fan-out and set multiple driver net bit for vector
 * know vector or will not be called
 * could call lds and drivers reorganization routine from in here
 */
static void chkset_vec_fifo(struct net_t *np, int32 *pbfi, int32 *pbfo,
 int32 ii, int32 isform, int32 nd_fi_chk)
{
 int32 bi;
 int32 r1, r2;
 int32 someno_fanin, someno_fanout, allno_fanin, allno_fanout;
 struct itree_t *itp;
 char s1[IDLEN], s2[RECLEN], s3[RECLEN];

 /* DBG remove */
 if (!np->vec_scalared && (has_rng_npp(np) || np->nsym->sy_impldecl))
  __misc_terr(__FILE__, __LINE__);

 someno_fanin = someno_fanout = FALSE;
 allno_fanin = allno_fanout = TRUE;
 /* first check to see if all of wire has no fan-in */ 
 for (bi = 0; bi < np->nwid; bi++)
  {
   if (pbfi[bi] == 0) someno_fanin = TRUE;
   /* notice for is form, any > 1 will set for entire wire */ 
   else { allno_fanin = FALSE; if (pbfi[bi] >= 2) np->n_multfi = TRUE; }
   if (pbfo[bi] == 0) someno_fanout = TRUE; else allno_fanout = FALSE;
  }
 if (!allno_fanin && !someno_fanin && !allno_fanout && !someno_fanout)
  return;
 /* if added net, no messages multi-fo set */ 
 /* mark for cases where cannot determine fi/fo from load and driver list */
 if (isform)
  {
   if ((itp = cnvt_to_itp(__inst_mod, ii)) != NULL)
    {
     sprintf(s1, "in %s(%s):", __inst_mod->msym->synam, __msg2_blditree(__xs,
      itp));
    }
   else sprintf(s1, "in %s(CONNECT?):", __inst_mod->msym->synam);
  }
 else sprintf(s1, "in %s:", __inst_mod->msym->synam);
 if (np->vec_scalared) strcpy(s2, ""); else strcpy(s2, " vectored");
 __getwir_range(np, &r1, &r2);
 if (allno_fanin && nd_fi_chk)
  {
   __gfinform(418, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
    "%s %s%s [%d:%d] %s has no drivers (no bit has fan-in)", s1,
    __to_wtnam(s3, np), s2, r1, r2, np->nsym->synam);
  }
 if (allno_fanout)
  {
   __gfinform(428, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
    "%s %s%s [%d:%d] %s drives nothing (no bit has fan-out)", s1,
    __to_wtnam(s3, np), s2, r1, r2, np->nsym->synam);
  }
 /* next emit bit by bit errors - know at least one error */ 
 if (nd_fi_chk)
  {
   if (someno_fanin && !allno_fanin)    
    {
     for (bi = 0; bi < np->nwid; bi++)
      {
       if (pbfi[bi] == 0)
        {
         __gfinform(418, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
          "%s %s%s [%d:%d] %s bit %d has no declarative drivers (no fan-in)",
          s1, __to_wtnam(s3, np), s2, r1, r2, np->nsym->synam, bi);
        }
     }
    } 
  }
 if (someno_fanout && !allno_fanout)
  {
   for (bi = 0; bi < np->nwid; bi++)
    {
     if (pbfo[bi] == 0)
      {
       __gfinform(428, np->nsym->syfnam_ind, np->nsym->sylin_cnt, 
        "%s %s%s [%d:%d] %s bit %d drives nothing (no declartive fan-out)",
        s1, __to_wtnam(s3, np), s2, r1, r2, np->nsym->synam, bi);
      }
    }
  }
}

/*
 * return T if any net pin is non -1 form
 */
static int32 has_rng_npp(struct net_t *np)
{
 struct net_pin_t *npp;
 struct npaux_t *npauxp;

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 != -1) return(TRUE);
  }
 return(FALSE);
}

/*
 * convert a module and an itinum to the corresponding itp location
 * this searches 
 */
static struct itree_t *cnvt_to_itp(struct mod_t *mdp, int32 itino)
{
 int32 ii;
 struct itree_t *itp;

 for (ii = 0; ii < __numtopm; ii++)
  {
   if ((itp = cnvt_todown_itp(__it_roots[ii], mdp, itino)) != NULL)
    return(itp);
  }
 __arg_terr(__FILE__, __LINE__);
 return(NULL);
}

/*
 * dump a down level of a tree
 */
static struct itree_t *cnvt_todown_itp(struct itree_t *itp,
 struct mod_t *mdp, int32 itino)
{
 int32 ii; 
 int32 ofsnum;
 struct itree_t *itp2;

 if (itp->itip->imsym->el.emdp == mdp && itp->itinum == itino) return(itp);
 ofsnum = itp->itip->imsym->el.emdp->minum;
 for (ii = 0; ii < ofsnum; ii++)
  {
   if ((itp2 = cnvt_todown_itp(&(itp->in_its[ii]), mdp, itino)) != NULL)
    return(itp2);
  } 
 return(NULL);
}

/* 
 * ROUTINE TO PREPARE EXPRESSIONS 
 */

/*
 * check all expr. things that cannot be checked until most of prep done
 * 1) set expr. >1 fi bit
 * check for port and inst psel direction mismatch (warning)  
 * inout ports multi-fi and set here
 */
extern void __prep_exprs_and_ports(void)
{
 int32 pi, ii, gi, cai, pnum, derrtyp;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct mod_t *mdp, *imdp;
 struct gate_t *gp;
 struct conta_t *cap;
 struct expr_t *xp;
 struct conta_t *pbcap;
 char s1[RECLEN];

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* port lhs expr. that drive fi > 1 must be set for each inst. in mod */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((pnum = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < pnum; pi++)
      {
       mpp = &(imdp->mpins[pi]);
       /* any up iconn connection to inout is fi>1 here */
       xp = ip->ipins[pi];

       /* input port never lhs */
       if (mpp->mptyp == IO_IN) continue;

       /* will never see inouts, if in tran chan. no drivers */
       if (lhs_has_figt1(xp)) xp->x_multfi = TRUE;
      }
    }
   /* gate outputs may drive fi > 1 and be not strength */
   for (gi = 0; gi < mdp->mgnum; gi++)
    {
     gp = &(mdp->mgates[gi]);

     switch ((byte) gp->g_class) {
      case GC_LOGIC: case GC_UDP: case GC_BUFIF: case GC_MOS: case GC_CMOS:
       if (lhs_has_figt1(gp->gpins[0])) gp->gpins[0]->x_multfi = TRUE;
       for (pi = 1; pi < (int32) gp->gpnum; pi++)
        {
         if (gp->g_class != GC_UDP)
          sprintf(s1, "%s gate input %d", gp->gmsym->synam, pi + 1);
         else sprintf(s1, "udp \"%s\" input %d", gp->gmsym->synam, pi + 1);
         xp = gp->gpins[pi];

         /* check for lhs and rhs same wire, delay type determines error */
         derrtyp =  __chk_0del(gp->g_delrep, gp->g_du, mdp);
         chk_decl_siderep(gp->gpins[0], xp, s1, derrtyp,
          gp->gsym->syfnam_ind, gp->gsym->sylin_cnt);
        }
       /* set the input change eval routine for the gate */ 
       __set_gchg_func(gp);
       break;
      /* no processing for trans - in separate tran switch channel */
      /* tran. channel expressions never seen */
      /* hard (channel input) driver expressions will be marked as fi>1 */
      case GC_TRAN:
       break;
      case GC_TRANIF:
       chk_trifctrl_insame_chan(gp, gp->gpins[2]);
       /* if tranif ctrl expr non leaf, warn if in same channel as term */
       if (!__isleaf(gp->gpins[2]))
        {
         chk_samechan_trifctrl_simple(mdp, gp, 0, gp->gpins[0], gp->gpins[2]);
         chk_samechan_trifctrl_simple(mdp, gp, 1, gp->gpins[1], gp->gpins[2]);
        }
       break;
      /* pull really source on wire not lhs */
      case GC_PULL: break;
      default: __case_terr(__FILE__, __LINE__); 
     }
    }

   for (cap = &(mdp->mcas[0]), cai = 0; cai < mdp->mcanum; cai++, cap++)
    {
     if (lhs_has_figt1(cap->lhsx))
      {
       cap->lhsx->x_multfi = TRUE;
       if (cap->ca_pb_sim)
        {
         for (pi = 0; pi < cap->lhsx->szu.xclen; pi++)
          {
           pbcap = &(cap->pbcau.pbcaps[pi]);
           pbcap->lhsx->x_multfi = TRUE;
          }
        }
      }
    }

   /* module in or inout ports can be non strength but drive fi > 1 */
   pnum = mdp->mpnum;
   for (pi = 0; pi < pnum; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     if (mpp->mptyp == IO_OUT) continue;
     xp = mpp->mpref;
     if (mpp->mptyp == IO_BID) { xp->x_multfi = TRUE; continue; }
     if (lhs_has_figt1(xp)) xp->x_multfi = TRUE;
    }
  }
 prep_tf_rwexprs();
}

/*
 * check tranif 3rd ctrl input in same channel 
 * LOOKATME - possible for xmr to cause this to be ok
 */
static void chk_trifctrl_insame_chan(struct gate_t *gp, struct expr_t *ndp)
{
 int32 pi;
 struct net_t *np0, *np1, *np2;
 struct expr_t *xp2;

 if (__isleaf(ndp))
  {
   if (ndp->optyp == ID || ndp->optyp == GLBREF)
    {
     np2 = ndp->lu.sy->el.enp;
     if (np2->ntraux == NULL) return;
     np0 = __find_tran_conn_np(gp->gpins[0]);
     np1 = __find_tran_conn_np(gp->gpins[1]);
     pi = -1;
     if (np2 == np0) pi = 0;
     if (pi != -1 && (np2->ntyp != N_SUPPLY0 && np2->ntyp != N_SUPPLY1))
      {
       __gfinform(3011, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
        "%s %s non supply net %s (port %d) appears in tran channel and control input - possible infinite loop oscillation",
        gp->gmsym->synam, gp->gsym->synam, np2->nsym->synam, pi);
      }   
     pi = -1;
     if (np2 == np1) pi = 1;
     if (pi != -1 && (np2->ntyp != N_SUPPLY0 && np2->ntyp != N_SUPPLY1))
      {
       __gfinform(3011, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
        "%s %s non supply net %s (port %d) appears in tran channel and control input - possible infinite loop oscillation",
        gp->gmsym->synam, gp->gsym->synam, np2->nsym->synam, pi);
      }   
    }
   return;
  }

 for (xp2 = ndp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   chk_trifctrl_insame_chan(gp, xp2);
  }

 if (ndp->lu.x != NULL) chk_trifctrl_insame_chan(gp, ndp->lu.x);
 if (ndp->ru.x != NULL) chk_trifctrl_insame_chan(gp, ndp->ru.x);
}

/*
 * check to see if tranif enable in same channel as the bidirect terminals
 * and expr non simple (if simple will use tranif node vertex value)
 * if complex will not update the enable during tran switch channel relax 
 */
static void chk_samechan_trifctrl_simple(struct mod_t *mdp, struct gate_t *gp,
 int32 pi, struct expr_t *termxp, struct expr_t *ctrlxp)
{
 int32 ii, bi, bi2, chanid0, chanid2, inum2;
 struct net_t *np0, *np2;
 struct vbinfo_t *vbip;
 struct gref_t *grp;

 np0 = __find_tran_conn_np(termxp);
 /* if terminal net is not in enable expr no problem possible */
 if (!net_in_expr(ctrlxp, np0)) return;

 /* DBG remove */
 if (np0->ntraux == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 __push_itstk(mdp->moditps[0]);
 /* SJM 08/02/01 - only called for tranif so other side itp same */
 /* get terminal net/bit */
 /* AIV 10-16-11 - must pass the itree here - tran channel does not */
 /* use idp's since extra access step and compiler uses wrappers */
 np0 = __tranx_to_netbit(termxp, 0, &bi, get_itp_());
 /* DBG remove */
 if (np0->ntraux == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 bi2 = (bi == -1) ? 0 : bi;
 vbip = np0->ntraux->vbitchans[np0->nwid*__inum + bi2];
 /* SJM 08/07/01 - bit may not be in channel */
 if (vbip == NULL) goto done;
 chanid0 = vbip->chan_id;

 if (ctrlxp->optyp == LSB)
  {
   /* BEWARE - this assumes all constant folded */
#ifndef __CVC_RT__
   if (termxp->ru.x->optyp != NUMBER)
    {
     __gfwarn(3112, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
      "%s %s third enable input net %s probably in same switch channel as terminal %d but bit select index non constant - updated node value not used when solving channel",
      gp->gmsym->synam, gp->gsym->synam, np0->nsym->synam, pi);
    }
#endif
   goto done;
  }
 if (termxp->optyp == PARTSEL)
  {
   chanid2 = vbip->chan_id;
   np2 = ctrlxp->lu.x->lu.sy->el.enp;
   if (ctrlxp->lu.x->optyp == GLBREF)
    {
     grp = ctrlxp->lu.x->ru.grp;
     for (ii = 0; ii < grp->targmdp->flatinum; ii++)
      {
       /* part select here uses low bit */

       inum2 = grp->targmdp->moditps[ii]->itinum;
       vbip = np0->ntraux->vbitchans[np0->nwid*inum2];
       /* SJM 08/07/01 - low bit may not be in channel */
       if (vbip == NULL) goto done;
       chanid2 = vbip->chan_id;
       if (chanid0 == chanid2)
        {
#ifndef __CVC_RT__
         __gfwarn(3115, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
          "%s %s third enable input heirarchical reference part select of net %s in same switch channel as terminal %d - updated node value not used when solving channel",
          gp->gmsym->synam, gp->gsym->synam, np0->nsym->synam, pi);
#endif
         goto done;
        }
      }
     goto done;
    }
   /* non xmr part select case */  
   bi = __contab[ctrlxp->ru.x->ru.xvi];
   /* DBG remove */
   if (np2->ntraux == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   vbip = np2->ntraux->vbitchans[np0->nwid*__inum + bi];
   /* SJM 08/07/01 - low bit may not be in channel */
   if (vbip == NULL) goto done;
   chanid2 = vbip->chan_id;
#ifndef __CVC_RT__
   if (chanid0 == chanid2)
    {
     __gfwarn(3116, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
      "%s %s third enable input part select of net %s in same switch channel as terminal %d - updated node value not used when solving channel",
      gp->gmsym->synam, gp->gsym->synam, np0->nsym->synam, pi);
    }
#endif
   goto done; 
  }
 /* AIV 07/30/08 - don't think this can happen */
 /* DBG remove -- */
 if (termxp->optyp == PARTSEL_NDX_PLUS || termxp->optyp == PARTSEL_NDX_MINUS)
   __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* complex expression - can't tell if really in */
#ifndef __CVC_RT__
 __gfwarn(3118, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
  "%s %s third enable input complex expression contains net %s possibly in same switch channel as terminal %d - updated node value not used when solving channel",
  gp->gmsym->synam, gp->gsym->synam, np0->nsym->synam, pi);
#endif

done:
 __pop_itstk();
}

/*
 * return T if net in expr
 */
static int32 net_in_expr(struct expr_t *ndp, struct net_t *np)
{
 struct net_t *np1;
 struct expr_t *xp2;

 if (__isleaf(ndp))
  {
   if (ndp->optyp == ID || ndp->optyp == GLBREF)
    {
     /* T even if different instances */
     np1 = ndp->lu.sy->el.enp;
     if (np == np1) return(TRUE);
    }
   return(FALSE);
 }

 for (xp2 = ndp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   if (net_in_expr(xp2, np)) return(TRUE);
  }

 if (ndp->lu.x != NULL)
  { if (net_in_expr(ndp->lu.x, np)) return(TRUE); }
 if (ndp->ru.x != NULL)
  { if (net_in_expr(ndp->ru.x, np)) return(TRUE); }
 return(FALSE);
}

/*
 * prepare tf rw expressions 
 * set multfi bits for tf_ rw expressions involving wires 
 * concat never tf_ rw 
 */
static void prep_tf_rwexprs(void)
{
 int32 pi;
 struct tfrec_t *tfrp; 
 struct tfarg_t *tfap;
 struct expr_t *xp;

 for (tfrp = __tfrec_hdr; tfrp != NULL; tfrp = tfrp->tfrnxt)
  {
   for (pi = 1; pi < tfrp->tfanump1; pi++)
    {
     tfap = &(tfrp->tfargs[pi]);
     xp = tfap->arg.axp; 
     if (!xp->tf_isrw) continue;
     /* only wires have multiple fan in */
     if (tfap->anp->ntyp >= NONWIRE_ST) continue;

     /* no context module or inst neede in here */
     if (lhs_has_figt1(xp))
      { xp->x_multfi = TRUE; __alloc_tfdrv_wp(tfap, xp, tfrp->tf_inmdp); }
    }
  }
}

/*
 * allocate the tfdrv wp
 * notice this can never be array 
 */ 
extern void __alloc_tfdrv_wp(struct tfarg_t *tfap, struct expr_t *xp,
 struct mod_t *mdp)
{
 int32 totchars;
 
 if (xp->x_stren)
  tfap->tfdrv_wp.bp = (byte *) __my_malloc(xp->szu.xclen*mdp->flatinum);
 else
  {
   totchars = __get_pcku_chars(xp->szu.xclen, mdp->flatinum);
   tfap->tfdrv_wp.wp = (word32 *) __my_malloc(totchars);
  }
 __init_tfdrv(tfap, xp, mdp);
}

/*
 * initialize tf arg value to z 
 * may be strength
 */
extern void __init_tfdrv(struct tfarg_t *tfap, struct expr_t *xp,
 struct mod_t *mdp)
{
 int32 i;
 byte *sbp;
 struct xstk_t *xsp;
 word32 dummy_idp;

 if (xp->x_stren)
  {
   sbp = (byte *) tfap->tfdrv_wp.bp;
   set_byteval_(sbp, mdp->flatinum*xp->szu.xclen, ST_HIZ);
  }
 else 
  {
   push_xstk_(xsp, xp->szu.xclen);
   zero_allbits_(xsp->ap, xp->szu.xclen); 
   one_allbits_(xsp->bp, xp->szu.xclen); 
   /* this does not access mod con tab */

   /* AIV 01/09/07 - need a dummy idp to get the idp[MD_INUM] from */
   __idp = &(dummy_idp);
   for (i = 0; i < mdp->flatinum; i++) 
    {
     /* set the dummy inum */
     dummy_idp = i;
     __inum = i;
     /* no need to access mod con table here */
     __st_perinst_val(tfap->tfdrv_wp, xp->szu.xclen, xsp->ap, xsp->bp);
    }
   __idp = NULL;
   __pop_xstk();
  }
}

/*
 * return T if lhs has at least 1 fi > 1 net  
 * this is needed because expr. bit also set for any strength but for
 * fi == 1 strength do not need 
 * any wire in a tran/inout channel must be fi>1  
 */
static int32 lhs_has_figt1(struct expr_t *lhsx)
{
 int32 multfi;
 struct expr_t *xp;
 struct net_t *np;

 switch (lhsx->optyp ) {
  case OPEMPTY: break;
  case ID:
  case GLBREF:
   np = lhsx->lu.sy->el.enp;
chk_net_bit:
   /* any wire in tran channel is fi>1 */ 
   if (np->ntraux != NULL) return(TRUE);
   if (np->n_multfi) return(TRUE);
   break;
  case LSB:
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   np = lhsx->lu.x->lu.sy->el.enp;
   goto chk_net_bit;
  case LCB:
   /* know for lhs at most 1 level of concatenate */
   /* if any element fi > 1 then entire expr */
   /* for cvc - need to handle non fi>1 parts of concatenates as fi>1 */
   multfi = FALSE;
   for (xp = lhsx->ru.x; xp != NULL; xp = xp->ru.x)
    {
     if (lhs_has_figt1(xp->lu.x)) { multfi = TRUE; break; }
    }
   if (multfi)
    {
     struct expr_t *idndp;

     for (xp = lhsx->ru.x; xp != NULL; xp = xp->ru.x)
      {
       if (!lhs_has_figt1(xp->lu.x))
        {
         idndp = __get_lvalue_idndp(xp->lu.x);
         np = idndp->lu.sy->el.enp;
         np->cc_need_multfi = TRUE;
        }
      }
    }
   return(multfi);
   break;
  default: __case_terr(__FILE__, __LINE__); 
 }
 return(FALSE);
}

/*
 * additional prep and checking of wide continuous assigns after fi known
 *
 * rules for delay and fi combinations of drivers and rhs save expr.:
 * fi==1, delay =0 => driver access by loading net, do not need rhs val wp
 *                    because no sched. value to re-eval  
 *                    (eval and store)
 * fi==1, delay >0 => driver access by loading net, has rhs val wp
 *                    because need to re-eval expr. after delay for assign
 *                    and so expr. no changes can be killed off early
 * fi>1,  delay =0 => driver access just by loading rhs, may need to save
 *                    rhs val save 
 * fi>1,  delay >0 => need to save driver wp and need rhs val wp for sched.
 *
 * notice delays prepared before here
 */
extern void __prep_contas(void)
{
 int32 bi, cai, insts, derrtyp;
 struct conta_t *cap, *pbcap;
 struct mod_t *mdp; 
 char s1[RECLEN];

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (cap = &(mdp->mcas[0]), cai = 0; cai < mdp->mcanum; cai++, cap++)
    {
     insts = mdp->flatinum;

     /* first check and eliminate getpat conta form */
     /* has neither rhsval wp or driver wp and no delay or error */
     /* SJM 09/28/02 - get pat lhs never PB decomposed rhs concat form */
     if (cap->lhsx->getpatlhs)
      { getpat_lhs_figt1(mdp, cap->lhsx, cap); continue; }

     /* need to eval rhs because of delay bit */
     /* know 6 and 12 not possible here but is 4x possible here ? */
     switch ((byte) cap->ca_delrep) {
      case DT_4V: case DT_IS4V: case DT_IS4V1: case DT_IS4V2: case DT_4X:
       cap->ca_4vdel = TRUE;
       break;
      default: cap->ca_4vdel = FALSE;
     }

     if (!cap->ca_pb_sim)
      {
       /* need to check for variable on both sides, even if 0 delay */ 
       derrtyp =  __chk_0del(cap->ca_delrep, cap->ca_du, mdp);
       chk_decl_siderep(cap->lhsx, cap->rhsx, "continuous assign", derrtyp,
        cap->casym->syfnam_ind, cap->casym->sylin_cnt);
      }
     else
      {
       derrtyp =  __chk_0del(cap->ca_delrep, cap->ca_du, mdp);
       for (bi = 0; bi < cap->lhsx->szu.xclen; bi++)
        {
         pbcap = &(cap->pbcau.pbcaps[bi]);
         /* DBG remove -- */
         if (pbcap->lhsx->szu.xclen != 1) __misc_terr(__FILE__, __LINE__);
         /* --- */
         /* if conta lhs expr fi>1, then all bit must be and need drv wp */
         /* need to check for variable on both sides, even if 0 delay */ 
         sprintf(s1, "per bit %d continuous assign", bi);
         chk_decl_siderep(pbcap->lhsx, pbcap->rhsx, s1, derrtyp,
          cap->casym->syfnam_ind, cap->casym->sylin_cnt);
        }
      }
    }
  }
}

/*
 * initialize and maybe allocate the continuous assign sched. and drive tabs
 *
 * this is always used for mod port input and output half drivers using
 * dummy conta for union place holder 
 *
 * initial value is z since needed for inout port in and out drivers 
 * think also better for conta but for conta's always overwritten?
 * this is only for non strength case - stren must be initialized
 * to strength wire type init value
 */
extern void __allocinit_perival(union pck_u *nvap, int32 insts, int32 blen,
 int32 nd_alloc)
{
 int32 totchars, wlen;

 if (blen == 1)
  {
   totchars = insts;
   if (nd_alloc) nvap->bp = (byte *) __my_malloc(totchars);
   set_byteval_(nvap->bp, insts, 2);
  }
 else
  {
   wlen = wlen_(blen); 
   totchars = 2*insts*wlen*WRDBYTES;
   if (nd_alloc) nvap->wp = (word32 *) __my_malloc(totchars);
   /* initialize to z - do not know driver - sim init will set */
   __init_peri_vec_var(nvap->wp, insts, wlen, blen, 0L, ALL1W); 
  }
}

/*
 * initialize a non strength vector (non packed) to z 
 * SJM 06-18-07 - no longer for var storage that is no longer all insts
 * together
 */
extern void __init_peri_vec_var(word32 *wp, int32 insts, int32 wlen,
 int32 vecw, word32 maska, word32 maskb)
{ 
 int32 ii, wi;
 word32 *iwp;
 int32 ubits;

 /* insts number of <= 1 word32 vectors that each occuppy part of 1 word32 */
 /* use normal full word32 initialization masks but make sure high bits 0 */
 if (vecw <= WBITS)
  {
   maska &= __masktab[vecw];
   maskb &= __masktab[vecw];
   /* for vectors <= WBITS, alternate high 0 masked init values per inst. */
   for (ii = 0; ii < insts; ii++) { *wp++ = maska; *wp++ = maskb; }
   return;
  }
 ubits = ubits_(vecw);
 iwp = wp;
 /* insts number of multiword per vector elements */
 for (ii = 0; ii < insts; ii++) 
  {
   /* for 1 insts's vector value, initial a part */
   for (wi = 0; wi < wlen; wi++) iwp[wi] = maska;
   iwp[wlen - 1] &= __masktab[ubits]; 

   /* then b part */
   for (wi = wlen; wi < 2*wlen; wi++) iwp[wi] = maskb;
   iwp[2*wlen - 1] &= __masktab[ubits]; 
   /* finally move iwp to vector location for next inst. */
   iwp = &(iwp[2*wlen]);
  }
}

/*
 * allocate (if flag T) and initialize strength perinst value
 * this is for tran channels
 */
extern void __allocinit_stperival(union pck_u *nvap, int32 insts,
 struct net_t *np, int32 nd_alloc)
{
 int32 totbits, stval;
 byte sval;

 totbits = insts*np->nwid;
 if (nd_alloc) nvap->bp = (byte *) __my_malloc(totbits);
 /* for trireg in tran channel, hard driver must be z - it will set value */
 if (np->ntraux != NULL && np->ntyp == N_TRIREG) stval = ST_HIZ;
 else __get_initval(np, &stval);
 sval = (byte) stval;
 set_byteval_(nvap->bp, totbits, sval);
}

/*
 * check a lhs expr. and emit error for every wire that has fi > 1
 * message for getpat only
 * LOOKATME - should bit select of scalared wire be legal for getpattern
 */
static void getpat_lhs_figt1(struct mod_t *mdp, struct expr_t *lhsx,
 struct conta_t *cap)
{
 struct net_t *np;

 switch (lhsx->optyp) {
  case OPEMPTY: break;
  case ID:
  case GLBREF:
   np = lhsx->lu.sy->el.enp;
   if (np->n_multfi)
    {
     /* wire for getpat will be scalar or will not get this far */
     __gferr(858, cap->casym->syfnam_ind, cap->casym->sylin_cnt,
     "$getpattern lvalue wire %s more than one driver illegal - no way to removebus contention",
     __to_idnam(lhsx)); 
    }
   if (np->ntraux != NULL)
    {
     __gferr(858, cap->casym->syfnam_ind, cap->casym->sylin_cnt,
      "$getpattern lvalue wire %s inout port or tran connection illegal",
      __to_idnam(lhsx)); 
    }
   if (np->nrngrep == NX_DWIR)
    {
     __gferr(938, cap->casym->syfnam_ind, cap->casym->sylin_cnt,
      "$getpattern lvalue wire %s delay or path destination illegal",
      __to_idnam(lhsx)); 
    }
   break;
  case LCB:
   /* know for lhs at most 1 level of concatenate */
   {
    struct expr_t *xp2;
    for (xp2 = lhsx->ru.x; xp2 != NULL; xp2 = xp2->ru.x)
     getpat_lhs_figt1(mdp, xp2->lu.x, cap);
   }
   break;
  default: __case_terr(__FILE__, __LINE__); 
 }
}

/*
 * check continous assign or gate for same variable on both sides
 * if delay then inform, if no delay warn - probable inf. loop
 *
 * possible for 2 same wire globals to be on both sides but not caught here
 */
static void chk_decl_siderep(struct expr_t *lhsx, struct expr_t *rhsx,
 char *objnam, int32 deltyp, word32 fnind, int32 lcnt)
{
 int32 nd_inform, wire_issel;
 struct expr_t *ndp;
 struct net_t *np;
 char s1[RECLEN];

 /* expect rhs to be wider */
 nd_inform = TRUE;
 switch (rhsx->optyp) {
  case ID: 
   nd_inform = FALSE;
   np = rhsx->lu.sy->el.enp; 
cmp_wire:
   if (!find_var_in_xpr(lhsx, np, &wire_issel)) break;

   if (deltyp == DBAD_NONE) { strcpy(s1, "no delay"); nd_inform = FALSE; }
   else if (deltyp == DBAD_EXPR || deltyp == DBAD_MAYBE0) 
    { strcpy(s1, "possible 0 delay"); nd_inform = FALSE; }
   else if (deltyp == DBAD_0)
    { strcpy(s1, "all 0 delay"); nd_inform = FALSE; }
   else strcpy(s1, "delay");

   if (nd_inform || wire_issel)
    __gfinform(444, fnind, lcnt,
     "wire %s repeated on both sides of %s - has %s", np->nsym->synam,
     objnam, s1);
#ifndef __CVC_RT__
   else __gfwarn(624, fnind, lcnt,
    "wire %s repeated on both sides of %s - has %s", np->nsym->synam, objnam,
    s1);
#endif
   break;
  case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   np = rhsx->lu.x->lu.sy->el.enp;
   goto cmp_wire;
  case LCB:
   for (ndp = rhsx->ru.x; ndp != NULL; ndp = ndp->ru.x)
    chk_decl_siderep(lhsx, ndp->lu.x, objnam, deltyp, fnind, lcnt);
   break;
  case FCALL: 
   for (ndp = rhsx->ru.x; ndp != NULL; ndp = ndp->ru.x)
    chk_decl_siderep(lhsx, ndp->lu.x, objnam, deltyp, fnind, lcnt);
 }
}

/*
 * find a variable in an expr.
 * if same variable but global xmr, not a match
 */
static int32 find_var_in_xpr(struct expr_t *xp, struct net_t *np, 
 int32 *wire_sel)
{
 struct expr_t *ndp;
 struct net_t *npx;

 if (np->ntyp >= NONWIRE_ST) return(FALSE);

 *wire_sel = TRUE;
 switch (xp->optyp) {
  case ID: 
   *wire_sel = FALSE;
   npx = xp->lu.sy->el.enp;
comp_net:
   return(np == npx);
  case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   npx = xp->lu.x->lu.sy->el.enp;
   goto comp_net;
  case LCB:
   for (ndp = xp->ru.x; ndp != NULL; ndp = ndp->ru.x)
    { if (find_var_in_xpr(ndp->lu.x, np, wire_sel)) return(TRUE); } 
   break;
  case FCALL: 
   for (ndp = xp->ru.x; ndp != NULL; ndp = ndp->ru.x)
    { if (find_var_in_xpr(ndp->lu.x, np, wire_sel)) return(TRUE); } 
 }
 return(FALSE);
}

/*
 * ROUTINES TO DYNAMICALLY SET UP MIPDS
 */
   
/*
 * allocate, initialize, and link in NP MIPD load delay npp for a net 
 *
 * reinit does not turn off SDF annotated delays - if task called
 * with replace form works, increment adds
 */
extern void __add_alloc_mipd_npp(struct net_t *np, struct mod_t *mdp)
{
 int32 bi;
 struct net_pin_t *npp;
 struct mipd_t *mipdp;

 /* DBG remove --- */
 if (np->nlds != NULL && np->nlds->npntyp == NP_MIPD_NCHG)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 __cur_npnp = np;
 __cur_npnum = 0;
 /* always for entire net - table nil if no MIPD on bit for any inst */
 /* this also inserts on front of list */
 npp = __alloc_npin(NP_MIPD_NCHG, -1, -1);

 if (np->nlds == NULL)
  {
   /* LOOKATME - think since input port will always have load */
   /* add the one new mipd net pin - know np never a reg becaus in/inout */
   np->nlds = npp;

   /* SJM 07/25/01 - was not setting all needed bits right */
   /* need to set the various bits to indicate has load so net changes */
   /* put on nchg list */ 
   np->nchg_has_lds = TRUE;

   /* when add mipd load, must turn off all chged */
   /* even if dce list was not empty, if match itp dces some action bits */
   /* will be wrongly off */
   /* SJM 01/06/03 - is is possible to only turn on current inst? */
   /* AIV REMOVEME - no longer set this here - set during idp alloc/init
   for (ii = 0; ii < mdp->flatinum; ii++)
    { 
     idp = mdp->moditps[ii]->it_idp;
     idp[np->nchgaction_ofs] &= ~(NCHG_ALL_CHGED); 
    }
   */
  }
 else { npp->npnxt = np->nlds; np->nlds = npp; }

 /* SJM 07/26/01 - alloc was wrong size - needs to be one per bit */
 npp->elnpp.emipdbits = (struct mipd_t *)
  __my_malloc(np->nwid*sizeof(struct mipd_t));

 /* AIV 12/31/07 - mipd flag must be set to TRUE */
 np->n_mipd = TRUE;

 /* need basic setup especially turning on no mipd bit for each */
 for (bi = 0; bi < np->nwid; bi++)
  {
   mipdp = &(npp->elnpp.emipdbits[bi]);
   /* BEWARE - this is crucial T bit indicating no path for this bit */
   mipdp->no_mipd = TRUE;
   mipdp->pth_mipd = FALSE;
   mipdp->impthtab = NULL;
   /* rest of fields set if path ends on bit */
  } 
 /* SJM 02/06/03 - may have npps but not dces so must turn this on */
 /* SJM 06/23/04 - ### ??? LOOKATME - is this needed without regen? */
 /* since nchg nd chgstore on, know nchg action right */
 if (np->ntyp >= NONWIRE_ST) np->nchg_has_dces = TRUE;

}

/*
 * initialize a (PORT form path - first step in annotating either path delay
 * value is the (PORT form destination for one bit
 */
extern void __setup_mipd(struct mipd_t *mipdp, struct net_t *np, int32 ninsts)
{
 int32 ii;
 int32 stval;
 byte bv;

 mipdp->no_mipd = FALSE;
 mipdp->pb_mipd_delrep = DT_1V;
 mipdp->pb_mipd_du.d1v = (word64 *) __my_malloc(sizeof(word64));
 /* SJM 07/22/01 - nee to start value at 0 so unset stay as 0 */
 mipdp->pb_mipd_du.d1v[0] = 0ULL;

 mipdp->oldvals = (byte *) __my_malloc(ninsts); 

 if (!np->n_stren) bv = (byte) __get_initval(np, &stval);
 else { __get_initval(np, &stval); bv = (byte) stval; }
 for (ii = 0; ii < ninsts; ii++) mipdp->oldvals[ii] = bv;
 
 mipdp->mipdschd_tevs = 
  (struct tev_t **) __my_malloc(ninsts*sizeof(struct tev_t *));
 for (ii = 0; ii < ninsts; ii++) mipdp->mipdschd_tevs[ii] = NULL;
 if (mipdp->pth_mipd)
  {
   mipdp->impthtab = (struct impth_t **)
    __my_malloc(ninsts*sizeof(struct impth_t *));
   for (ii = 0; ii < ninsts; ii++) mipdp->impthtab[ii] = NULL;
  }
}

/*
 * re-init all mipds for a port - only called if port has mipds
 * this just reset old value
 */
extern void __reinit_mipd(struct mod_pin_t *mpp, struct mod_t *mdp)
{
 int32 ndx, bi, ii;
 int32 stval;
 byte bv;
 struct impth_t *impthp;
 struct tenp_t *prtnetmap;
 struct mipd_t *mipdp;
 struct net_t *np;

 prtnetmap = __bld_portbit_netbit_map(mpp);
 /* for every port bit - just reinit connected bits */
 /* other ports will reinit other bits if used */ 
 for (ndx = 0; ndx < mpp->mpwide; ndx++)
  { 
   np = prtnetmap[ndx].tenu.np;
   /* notice ndx is port bit index but bi is connecting net bit index */
   bi = prtnetmap[ndx].nbi;
   /* DBG remove -- */
   if (np->nlds == NULL || np->nlds->npntyp != NP_MIPD_NCHG)
    __misc_terr(__FILE__, __LINE__);
   /* -- */
   mipdp = &(np->nlds->elnpp.emipdbits[bi]);

   if (!np->n_stren) bv = (byte) __get_initval(np, &stval);
   else { __get_initval(np, &stval); bv = (byte) stval; }
   for (ii = 0; ii < mdp->flatinum; ii++) mipdp->oldvals[ii] = bv;
 
   for (ii = 0; ii < mdp->flatinum; ii++) mipdp->mipdschd_tevs[ii] = NULL;

   if (mipdp->pth_mipd)
    {
     /* only need to re-init change times */ 
     for (ii = 0; ii < mdp->flatinum; ii++) 
      {
       impthp = mipdp->impthtab[ii];
       for (; impthp != NULL; impthp = impthp->impthnxt)
        { impthp->lastchg = 0ULL; }
      }
    }
  } 
 __my_free(prtnetmap, mpp->mpwide*sizeof(struct tenp_t));
}

/*
 * access mipd from port and port index
 *
 * for scalar ndx passed as 0 not -1 here
 * only called if port has mipd
 */
extern struct mipd_t *__get_mipd_from_port(struct mod_pin_t *mpp, int32 ndx)
{
 int32 bi;
 struct mipd_t *mipdp;
 struct tenp_t *prtnetmap;
 struct net_t *np;

 prtnetmap = __bld_portbit_netbit_map(mpp);
 np = prtnetmap[ndx].tenu.np;
 bi = prtnetmap[ndx].nbi;
 mipdp = &(np->nlds->elnpp.emipdbits[bi]);
 __my_free(prtnetmap, mpp->mpwide*sizeof(struct tenp_t));
 return(mipdp);
}

/*
 * for a lhs port, malloc and build tenp map from port bit to net bit 
 * know port always lhs here
 */
extern struct tenp_t *__bld_portbit_netbit_map(struct mod_pin_t *mpp)
{
 int32 pi;
 struct expr_t *catxp;
 struct tenp_t *prtnetmap;

 prtnetmap = (struct tenp_t *) __my_malloc(mpp->mpwide*sizeof(struct tenp_t));

 /* concatenate - add each component */
 if (mpp->mpref->optyp == LCB)
  {
   pi = mpp->mpwide - 1;
   for (catxp = mpp->mpref->ru.x; catxp != NULL; catxp = catxp->ru.x)
    {
     pi -= catxp->lu.x->szu.xclen; 
     add_portbit_map(prtnetmap, catxp->lu.x, pi);
    }
   return(prtnetmap);
  } 
 /* add simple port to map */
 add_portbit_map(prtnetmap, mpp->mpref, 0);
 return(prtnetmap);
}

/*
 * for a lhs port, add non concat lhs port to port to bit map
 * notice nbi index is 0 for scalar
 */
static void add_portbit_map(struct tenp_t *prtnetmap, struct expr_t *xp,
 int32 base_pi)
{
 int32 pi, bi; 
 int32 psi1, psi2;
 word32 *wp;
 struct net_t *np;
 struct expr_t *ndx;
 
 switch (xp->optyp) {
  case ID:
   np = xp->lu.sy->el.enp;
   if (!np->n_isavec)
    {
     prtnetmap[base_pi].tenu.np = np;
     prtnetmap[base_pi].nbi = 0;
    }
   else 
    {
     for (pi = base_pi; pi < base_pi + xp->szu.xclen; pi++)
      { prtnetmap[pi].tenu.np = np; prtnetmap[pi].nbi = pi - base_pi; }
    }
   break;
  case OPEMPTY:
   for (pi = base_pi; pi < base_pi + xp->szu.xclen; pi++)
    {
     /* LOOKATME - index illegal -1 here since think won't occur */
     prtnetmap[pi].tenu.np = NULL;
     prtnetmap[pi].nbi = -1;
    }
   break;
  case PARTSEL:
   np = xp->lu.x->lu.sy->el.enp;
   ndx = xp->ru.x;
   wp = &(__contab[ndx->lu.x->ru.xvi]);
   psi1 = (int32) wp[0];
   wp = &(__contab[ndx->ru.x->ru.xvi]);
   psi2 = (int32) wp[0];
   /* part select always constant */
   for (pi = base_pi, bi = psi2; pi < base_pi + xp->szu.xclen; pi++, bi++)
    {
     prtnetmap[pi].tenu.np = np;
     prtnetmap[pi].nbi = bi;
    }
   break;
  case LSB:
   /* LOOKATME - think IS bit selects always split before here */
   /* DBG remove */
   if (xp->ru.x->optyp != NUMBER) __misc_terr(__FILE__, __LINE__);
   /* --- */
   np = xp->lu.x->lu.sy->el.enp;
   ndx = xp->ru.x;
   wp = &(__contab[ndx->ru.xvi]);
   psi1 = (int32) wp[0];
   prtnetmap[base_pi].tenu.np = np;
   prtnetmap[base_pi].nbi = psi1;
   break;
  /* since know only 1 level, removed before here */
  case LCB: __case_terr(__FILE__, __LINE__);
  /* xmr can't connect to port */
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * ROUTINES TO ALLOCATE NCHG ACTION STORAGE
 */

/*
 * compute size of needed nchg byte table in bytes
 * also sets srep since always called
 */
extern void __set_net_srep_types(void)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum != 0)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       __set_1net_srep(np);
      } 
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       __set_1net_srep(np);
      }
    }
  }
}

/*
 * set the storage rep type for one net
 *
 * SJM 05/04/05 - since not calling alloc storage routine for CVC, 
 * must set sreps in separate routine called from nchg routines that
 * are always called
 *
 * SJM 08-02-10 - new routine to handle the various SV 2 state var cases
 */
extern void __set_1net_srep(struct net_t *np)
{
 if (np->ntyp == N_EVENT) return;

 if (np->n_isarr) { np->srep = SR_ARRAY; return; }
 if (np->ntyp == N_REAL) { np->srep = SR_VEC; return; } 
 if (np->ntyp == N_STRING) { np->srep = SR_STRING; return; }
 /* set srep for scalar cases */
 if (!np->n_isavec)
  {
   if (np->ntyp == N_BIT) np->srep = SR_SCAL2S;
   else if (np->n_stren) np->srep = SR_SSCAL;
   /* AIV 08/25/10 - this routine now checks for +2state options */
   else if (__is_2state_typ(np->ntyp)) 
    {
     np->srep = SR_SCAL2S;
    }
   else np->srep = SR_SCAL;
   return;
  }
 /* set sreps for the vector cases */
 if (!np->n_stren)
  {
   /* AIV 08/25/10 - this routine now checks for +2state options */
   if (__is_2state_typ(np->ntyp)) 
    {
     np->srep = SR_BIT2S;
     return;
    }
   if (np->ntyp == N_BIT)
    {
     np->srep = SR_BIT2S;
    }
   else np->srep = SR_VEC;
  }
 else np->srep = SR_SVEC;
}

/*
 * initialize nchg action byte table for all modules
 *
 * this needs the idp area since nchg actions bits from idp area used for
 * both interpreted and compiled sim
 *
 * always assume dumpvars off also after reset (re-initialize)
 * this must be called after dces reinited
 * init net changtion action in idp area
 */
extern void __init_idp_nchgaction(void)
{
 int32 ii, ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;
 t_midat *idp;
 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
    {
     /* AIV 10/23/07 - if net doesn't need change don't init the nchgaction */
     if (!net_needs_change(np)) continue;

     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       idp = mdp->moditps[ii]->it_idp;
       /* start with all dumpvars off - now independent of var chg */
       /* all all other fields 0 off */
       idp[np->nchgaction_ofs] = NCHG_DMPVNOTCHGED; 
       /* AIV 01/08/08 - if compiled sim only need for dumpvars */ 
       /* AIV 10/13/08 - ncgaction needed for dump ports as well */
       if (__compiled_sim && !np->dmpv_in_src && !np->dmpp_in_src)
        {
         continue;
        }

       if (np->ntyp >= NONWIRE_ST)
        {
         /* SJM - 07/01/00 - for regs, if no lds, all var insts stay */
         /* all chged and never record */
         if (np->nlds == NULL) 
          {
           idp[np->nchgaction_ofs] |= NCHG_ALL_CHGED;
          }
        }
       else
        { 
         /* SJM 07/24/00 - for wires, if has dces not all changed */
         if (np->nlds == NULL && (np->dcelst == NULL
          || __cnt_dcelstels(np->dcelst) == 0))
          idp[np->nchgaction_ofs] |= NCHG_ALL_CHGED;
        }
      }
    }
  
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       /* AIV 10/23/07 - if net doesn't need change don't init the nchgaction */
       if (!net_needs_change(np)) continue;

       for (ii = 0; ii < mdp->flatinum; ii++)
        { 
         idp = mdp->moditps[ii]->it_idp;
         /* start with all dumpvars off - now independent of var chg */
         /* all all other fields 0 off */
         idp[np->nchgaction_ofs] = NCHG_DMPVNOTCHGED; 
         /* AIV 01/08/08 - if compiled sim only need for dumpvars */ 
         /* AIV 10/13/08 - ncgaction needed for dump ports as well */
         if (__compiled_sim && !np->dmpv_in_src && !np->dmpp_in_src)
          {
           continue;
          }

         /* SJM - 07/01/00 - if no lds, all var insts stay all chged */
         /* now all chged only for loads */
         /* SJM 07/24/00 - here since know reg, all chged if no lds */
         if (np->nlds == NULL) 
          {
           idp[np->nchgaction_ofs] |= NCHG_ALL_CHGED;
          }
        }
      }
    }
  }
}

/*
 * init net action bits - this sets bits in net_t records and does not
 * need the idp area
 *
 * during sim bits moved from routine called later into the idp area
 * are used instead - this is the first prep step
 */
extern void __set_pre_idp_nchgaction_bits(void)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;
 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
    {
     /* SJM - 07/01/00 - set various per variable bits in 0th element */
     /* SJM - 03/15/01 - change to fields in net record */
     if (np->nlds != NULL) np->nchg_has_lds = TRUE;

     /* SJM 07/24/00 - only nchg has dces on for regs immediate prop/wakeup */
     if (np->ntyp >= NONWIRE_ST && np->dcelst != NULL)
      np->nchg_has_dces = TRUE;

     /* SJM REMOVEME */
     /* --- 
     if (np->nlds == NULL && np->dcelst == NULL && np->dmpv_in_src)
      __misc_terr(__FILE__, __LINE__); 
     -- */

     /* if any lds, dces or dmpvs, need chg store  */
     if (np->nlds != NULL || np->dcelst != NULL || np->dmpv_in_src || 
       np->n_has_toggle) np->nchg_nd_chgstore = TRUE;

     /* SJM 09-27-08 - all ports of dumpports instances must be chg store */
     if (mdp->mod_dumpports_in_src && np->iotyp != NON_IO)
      np->nchg_nd_chgstore = TRUE;
    }
  
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       /* SJM - 07/01/00 - set various per var bits in 0th element */
       /* SJM 03/15/01 - change to fields in net record */
       if (np->nlds != NULL) np->nchg_has_lds = TRUE;

       /* SJM 07/24/00 - only nchg has dces on for regs but task vars regs */
       if (np->dcelst != NULL) np->nchg_has_dces = TRUE;

       /* if any lds, dces or dmpvs, need chg store  */
       if (np->nlds != NULL || np->dcelst != NULL || np->dmpv_in_src
        || np->n_has_toggle) np->nchg_nd_chgstore = TRUE;
      }
    }
  }
}

/*
 * set computed optimtab bits for all vars in entire design
 */
extern void __set_optimtab_bits(void)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;
 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
    {
     /* AIV 07/21/10 - this should have never turned these bits on for */
     /* arrays - now allowing dumping of arrays */
     if (np->n_isarr && !__dump_arrays) continue;


     /* assume need chg store */
     if (__is_net_dumped(np) && (__dv_allform_insrc || mdp->mod_dvars_in_src))
      {
       np->dmpv_in_src = TRUE;
       np->nchg_nd_chgstore = TRUE;
      }
    }
  
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       /* AIV 07/21/10 - this should have never turned these bits on for */
       /* arrays - now allowing dumping of arrays */
       if (np->n_isarr && !__dump_arrays) continue;

       /* AIV 01/26/11 - if automatic array do not dump value */
       if (np->n_is_auto_var) continue;

       if (__is_net_dumped(np) && (__dv_allform_insrc || mdp->mod_dvars_in_src))
        {
         np->dmpv_in_src = TRUE;
         np->nchg_nd_chgstore = TRUE;
        }
      }
    }
  }
}

/*
 * NEW ROUTINES TO ALLOC SIM VARIABLE STORAGE PER INST TOGETHER
 */

/*
 * routine sets the offsets in the one inst contiguous area 
 * for nets and driving/recording malloc memory
 *
 * used for both interpreter and CVC but CVC allocates elsewhere
 *
 * SJM 06-26-07 - new algorithm assume __idp points to current instances
 * data area including fast way using to get current mod and inst number
 *
 * for now only variable storage in per inst all of module __idp data area
 * accessed by offsets
 *
 * SJM 08-07-08 - now also adds stmt idp variables so builds a tmp table
 * of statement for each mod before setting idp values for statements
 */
extern void __set_all_mods_1inst_storage_offsets(void)
{
 int32 ni, sti, wlen, net_nchg_dummy_word;
 struct mod_t *mdp;
 struct net_t *np;
 struct task_t *tskp;
 struct st_t *stp;
 struct delctrl_t *dctp;
 struct expr_t *rhsx;

 net_nchg_dummy_word = -1;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* SJM 06-27-07 each peri mod data area starts with the 3 itree fields for */
   /* faster access */
   __nxt_ofs = IDP_HD_WOFS;
   /* AIV 01/08/08 - this is the dummy word for net change word */
   /* there are a couple places in the init code which call the __add_nchg_* */
   /* routines so they need to have a value and instead of having a if */
   /* statement in the interpreted code just fill a dummy value */
   if (__compiled_sim)
    {
     net_nchg_dummy_word = __nxt_ofs;
     __nxt_ofs++;
    }

   /* mod net offset */
   if (mdp->mnnum != 0)
    {
     /* AIV 02/23/09 - need to assign all value area first */
     /* wire arrays are assuming contiguous - values */
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       if (np->ntyp == N_EVENT) continue;

       __set_1var_net_ofs(np, mdp);
      } 
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       /* also none for events (if dce will be allocated when used) */
       /* AIV 08/14/07 - every net now contain an nchgaction in the idp area */
       //AIV FIXME - nchgaction shouldn't be needed for event/param
       //put was alloc anyway for the old code so wasting a little space
       /* AIV 10/23/07 - if net doesn't need change don't init the nchgaction */
       /* AIV 01/08/08 - nchgaction array is only used for dumpvars */
       if (__compiled_sim)
        {
         /* AIV 10/13/08 - ncgaction needed for dump ports as well */
         if (np->dmpv_in_src || np->dmpp_in_src)
          {
           np->nchgaction_ofs = __nxt_ofs;
           __nxt_ofs++;
          }
         else np->nchgaction_ofs = net_nchg_dummy_word;
        }
       else if (net_needs_change(np)) 
        {
         np->nchgaction_ofs = __nxt_ofs;
         __nxt_ofs++;
        }
      }
    }
   
   /* AIV 08/06/07 - parms are now store per idp instance as well */
   if (mdp->mprmnum != 0)
    {
     for (ni = 0, np = &(mdp->mprms[0]); ni < mdp->mprmnum; ni++, np++) 
      {
       np->nva_ofs = __nxt_ofs;
       wlen = get_1net_idp_wlen(np);
       __nxt_ofs += wlen;
      }
    }

   /* next the statement per inst values now in idp area */
   for (sti = 0; sti < mdp->prov_mstnum; sti++)
    {
     stp = mdp->prov_mstndx[sti];
     
     if (stp->stmttyp == S_REPEAT)
      {
       stp->st.srpt.reptmp_ofs = __nxt_ofs;
       __nxt_ofs++;
      }
     else if (stp->stmttyp == S_DELCTRL)
      {
       dctp = stp->st.sdc;
       if (dctp->repcntx != NULL)
        {
         dctp->dce_repcnt_ofs = __nxt_ofs;
         __nxt_ofs++;
        }
       dctp->dceschd_tev_ofs = __nxt_ofs;
       __nxt_ofs++;
      }
     /* need to get the wait statements delctrl as well */
     else if (stp->stmttyp == S_WAIT)
      {
       dctp = stp->st.swait.wait_dctp;
       if (dctp->repcntx != NULL)
        {
         dctp->dce_repcnt_ofs = __nxt_ofs;
         __nxt_ofs++;
        }
       dctp->dceschd_tev_ofs = __nxt_ofs;
       __nxt_ofs++;
      }
//AIV FIXME - could do this in the interpreter as well no need to alloc mem
     if (__compiled_sim)
      {
       if (stp->stmttyp == S_NBPROCA)
        {
         stp->rhs_idp_ofs = __nxt_ofs;
         wlen = get_rhs_del_storage_wlen(stp);
         __nxt_ofs += wlen;
        }
       else if (stp->stmttyp == S_RHSDEPROCA)
        {
         rhsx = stp->st.spra.rhsx;
         /* don't need storage area if rhs is constant */
         if (!__is_const_expr(rhsx)) 
          {
           stp->rhs_idp_ofs = __nxt_ofs;
           wlen = get_rhs_del_storage_wlen(stp);
           __nxt_ofs += wlen;
          }
        }
      }
    }
   /* SJM 08-08-07 - idp area for dce run time values */
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
    {
     set_net_dce_expr_ofs(np, mdp);
    }
   /* AIV 08/13/07 - idp area for continuous assign storage area */
   set_conta_idp_ofs(mdp);
   /* AIV 08/14/07 - idp area for gate storage area */
   set_gate_idp_ofs(mdp); 
   /* AIV 09/25/07 - idp area for static net changes */
   if (__compiled_sim) 
    {
     /* AIV 03/06/08 - set isnum uses linearize_avl_tree - init globals */
     /* AIV 06/16/09 - need to free here - this is in a for loop */ 
     /* probably could just use the same tree and rest values - but reseting */
     if (__avltab != NULL)
      {
       __my_free(__avltab, __avltabsiz*sizeof(struct avlnode_t *));
      }
     __avltabsiz = 200;
     __avltab = (struct avlnode_t **)
     __my_malloc(__avltabsiz*sizeof(struct avlnode_t *));
     __avl_lasti = -1;
     set_nchg_idp_ofs(mdp);
     set_tevs_idp_ofs(mdp);
     set_isnum_idp_ofs(mdp);
    }
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
    {
     /* AIV 05/13/08 - timing checks now use idp area must alloc */
     set_net_npp_tchk_ofs(np);
     /* AIV 12/06/10 - need to set the offset to hold toggle structs */
     set_net_toggle_ofs(np);
    }

   /* task net offsets */

   /* AIV 04/13/10 - need to save the start of the tasks idp offset for */
   /* automatic tasks - when copying back the idp area */
   /* these also need to go to the top of the idp area - for copying */
   /* back all non-task idp area */
   mdp->task_start_ofs = __nxt_ofs;
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
    
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       /* AIV 08/14/07 - every net now contain an nchgaction in the idp area */
       //AIV FIXME - nchgaction shouldn't be needed for event/param
       //put was alloc anyway for the old code so wasting a little space
       /* AIV 01/08/08 - nchgaction array is only used for dumpvars */
       if (__compiled_sim)
        {
         if (np->dmpv_in_src || np->dmpp_in_src)
          {
           np->nchgaction_ofs = __nxt_ofs;
           __nxt_ofs++;
          }
         else np->nchgaction_ofs = net_nchg_dummy_word;
        }
       else if (net_needs_change(np)) 
        {
         np->nchgaction_ofs = __nxt_ofs;
         __nxt_ofs++;
        }
       if (np->ntyp == N_EVENT) continue;

       /* for now always zeroing variables - when x/z */
       __set_1var_net_ofs(np, mdp);
      }
    }

   mdp->mod_idata_siz = __nxt_ofs;
   /* AIV 03/31/09 - prior to simulation - must record the size of the idp */
   /* this may be expanded for interactive dbg with +interp */
   mdp->mod_idata_siz_presim = __nxt_ofs;
  }
}

/*
 * AIV 10/23/07 - don't alloc net change in idp if never used
 * AIV PLI?????????
 */
static int32 net_needs_change(struct net_t *np)
{
//AIV FIXME - due to wrapper routines this doesn't quite work
//working on removing tev saved events first
//////////////////////////////////
 return(TRUE);
//////////////////////////////////
//AIV FIXME - interpreter always needs to have net change set - this must be
//a recording not needed net changes - or always need because of ports
 if (!__compiled_sim) return(TRUE);

//AIV FIXME - if multfi or np->ntraux return true - explain why????
 if (np->n_multfi || np->ntraux != NULL) return(TRUE);

 if (np->nlds != NULL || np->dcelst != NULL || np->dmpv_in_src ||
     np->dmpp_in_src || np->monit_in_src || np->n_has_toggle)
  {
   return(TRUE);
  }
 return(FALSE); 
}

/*
 * set the continous assign offset storage area
 */
static void set_conta_idp_ofs(struct mod_t *mdp)
{
 int32 cai, bi;
 int32 wlen;
 struct conta_t *cap, *pbcap;

 for (cai = 0, cap = &(mdp->mcas[0]); cai < mdp->mcanum; cai++, cap++)
  {
   if (!cap->ca_pb_sim)
    {
     if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
      { 
       cap->ca_drv_ofs = __nxt_ofs;
       wlen = (2*wlen_(cap->lhsx->szu.xclen));
       __nxt_ofs += wlen;
      }
     if (cap->ca_delrep != DT_NONE)
      {
       cap->schd_drv_ofs = __nxt_ofs;
       wlen = (2*wlen_(cap->lhsx->szu.xclen));
       __nxt_ofs += wlen;
       /* AIV 10/24/07 - compiler no longer storing tevp - using fixed events */
       if (!__compiled_sim)
        {
         cap->caschd_tevs_ofs = __nxt_ofs;
         __nxt_ofs++;
        }
      }
    }
   else
    { 
     /* AIV 08/15/07 - must do the original cap itself as well */
//AIV FIXME - don't think this pbit is needed?????
     if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
      {
       cap->ca_drv_ofs = __nxt_ofs;
       wlen = (2*wlen_(cap->lhsx->szu.xclen));
       __nxt_ofs += wlen;
      }
     if (cap->ca_delrep != DT_NONE)
      {
       cap->schd_drv_ofs = __nxt_ofs;
       wlen = (2*wlen_(cap->lhsx->szu.xclen));
       __nxt_ofs += wlen;
       /* AIV 10/24/07 - compiler no longer storing tevp - using fixed events */
       if (!__compiled_sim)
        {
         cap->caschd_tevs_ofs = __nxt_ofs;
         __nxt_ofs++;
        }
      }

     for (bi = 0; bi < cap->lhsx->szu.xclen; bi++) 
      {
       pbcap = &(cap->pbcau.pbcaps[bi]);
       /* DBG remove */
       if (pbcap->lhsx->szu.xclen != 1) __misc_terr(__FILE__, __LINE__);
       /* -- */
       if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
        {
         pbcap->ca_drv_ofs = __nxt_ofs;
         __nxt_ofs += 2;
        }
       if (cap->ca_delrep != DT_NONE)
        {
         pbcap->schd_drv_ofs = __nxt_ofs;
         __nxt_ofs += 2;
         /* AIV 10/24/07 - compiler no longer storing tevp - using fixed evs */
         if (!__compiled_sim)
          {
           pbcap->caschd_tevs_ofs = __nxt_ofs;
           __nxt_ofs++;
          }
        }
      }
    }
  }
}

/*
 * return the non-blocking storage size
 */
static int32 get_rhs_del_storage_wlen(struct st_t *stp)
{
 int32 wlen, nbytes;
 struct expr_t *lhsx;

 /* AIV 04/13/07 - now can be scal as well not always convert vec*/
 lhsx = stp->st.spra.lhsx;
 __get_lhs_srep(lhsx, &nbytes);
 wlen = nbytes/WRDBYTES;
 return(wlen);
}

/*
 * set the idp storage area for gates
 */
static void set_gate_idp_ofs(struct mod_t *mdp)
{
 int32 gi, wlen;
 struct gate_t *gp;
 struct udp_t *udpp;

 for (gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);
   if (gp->g_class == GC_UDP)
    {
     udpp = gp->gmsym->el.eudpp;
     gp->gstate_ofs = __nxt_ofs;
     if (udpp->u_wide) __nxt_ofs += 2;
     else __nxt_ofs += 1;
    }
   else if (gp->g_class == GC_LOGIC && gp->gpnum > 16)
    {
     wlen = 2*wlen_(gp->gpnum);
     gp->gstate_ofs = __nxt_ofs;
     __nxt_ofs += wlen;
    }
   else
    {
     /* pull gate (really source) has no state or scheduled events */
     /* no state for trans */ 
     /* SJM 12/12/07 - this was wrongly reserving a place but uneeded */
     if (gp->g_class != GC_PULL && gp->g_class != GC_TRAN)
      {
       gp->gstate_ofs = __nxt_ofs;
       __nxt_ofs += 1;
      }
    }
   /* AIV 08/13/07 - gate output area */
   if (__compiled_sim)
    {
     /* AIV 08/13/07 - only certain gates have output value stored in idp */
     if (__gate_needs_output_word(gp->g_class))
      {
       gp->gate_out_ofs = __nxt_ofs;
       __nxt_ofs++;
      }
    }
   /* AIV 10/22/07 - compiler now uses static events no need to save event */
   /* wide and tran channels still use wrappers */
   if (__compiled_sim && gp->g_class != GC_TRAN && gp->g_class != GC_TRANIF) 
     {
      continue;
     }
   /* event tevpi storage area */
   if (gp->g_delrep != DT_NONE || (__sdflst != NULL || __has_sdfann_calls))
    {
     gp->schd_tevs_ofs = __nxt_ofs;
     __nxt_ofs++;
    }
  }
}
   
/*
 * set the idp ofs area for static net change structs
 */
static void set_nchg_idp_ofs(struct mod_t *mdp)
{
 struct net_chg_t *ncp;
 struct net_t *np;
 int32 ni;

 /* AIV 09/26/07 - if only one instance no reason to put them into idp */
 /* can access via $nchgdat no need to acess via inum better to use */
 /* literal address */
 /* SJM 08/04/08 - need to store the nchg idp ofs which points to */
//BEWARE - now always storing the nchg_idp area even if only one inst
 /* the __nchgdat_ area otherwise need separate alnk asl lib wrappers */
 /* for every net in tr chan for one inst modules */
  
 /* ??? if (mdp->flatinum == 1) return; */

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
    {
     ncp->nchg_idp_ofs = __nxt_ofs;
     __nxt_ofs++;
    }
  }
}

/*
 * set the idp ofs area for static timing events
 */
static void set_tevs_idp_ofs(struct mod_t *mdp)
{
 struct ctev_t *ctevp;
 struct st_t *stp;
 int32 sti, i, gi, ni;
 struct conta_t *cap;
 struct net_t *np;
 struct gate_t *gp;
 struct delctrl_t **da;
 struct delctrl_t *dctp;

 /* AIV 09/26/07 - if only one instance no reason to put them into idp */
 /* can access via $tevdat no need to acess via inum better to use */
 /* literal address */
 if (mdp->flatinum == 1) return;

 for (sti = 0; sti < mdp->prov_mstnum; sti++)
  {
   stp = mdp->prov_mstndx[sti];
   if ((ctevp = stp->ctevp) == NULL) continue;
   ctevp->ctev_idp_ofs = __nxt_ofs;
   __nxt_ofs++;
  }

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   if (np->ndel_ctevtab == NULL) continue;

   for (i = 0; i < np->nwid; i++)
    {
     ctevp = np->ndel_ctevtab[i];
     ctevp->ctev_idp_ofs = __nxt_ofs;
     __nxt_ofs++;
    }
  }

 for (gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);

   /* pull gate (really source) has no state or scheduled events */
   /* no state for trans */ 
   if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN) continue;

   /* if output unc. (OPEMPTY), changes are not seen (do not propagate) */
   if (gp->g_class != GC_TRANIF && gp->gpins[0]->optyp == OPEMPTY)
      continue;

   if (gp->g_delrep == DT_NONE) continue;

   ctevp = gp->ctevp;
   /* DBG remove -- */ 
   if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */ 
   ctevp->ctev_idp_ofs = __nxt_ofs;
   __nxt_ofs++;
  }

 for (i = 0; i < mdp->mcanum; i++)
  {
   cap = &(mdp->mcas[i]);
   if (cap->lhsx->getpatlhs) continue;

   if (cap->ca_delrep != DT_NONE) 
    {
     ctevp = cap->ctevp;
     /* DBG remove -- */ 
     if (cap->ca_pb_sim) __misc_terr(__FILE__, __LINE__);
     if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     ctevp->ctev_idp_ofs = __nxt_ofs;
     __nxt_ofs++;
    }
  }
 
 /* AIV 03/03/09 - for merged always blocks need a ctev for the header */
 /* block which the others are merged into */
 da = mdp->dctrl_array;
 for (i = 0; i < mdp->dctrl_size; i++)
  {
   dctp = da[i];
   /* only need space for the header block */
   if (!dctp->is_merged && dctp->merged_dctp != NULL) 
    {
     ctevp = dctp->head_ctevp;
     if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
     ctevp->ctev_idp_ofs = __nxt_ofs;
     __nxt_ofs++;
    }
  }
}
     
/*
 * set idp offsets for mdp
 */
static void set_isnum_idp_ofs(struct mod_t *mdp)
{
 struct prep_obj_t *pop;
 struct avlnode_t **isnums_avltab;
 int32 i, size, wlen, num_isnums;

 if (mdp->isnum_tree == NULL) return;
 
 isnums_avltab = __linearize_avl_tree(mdp->isnum_tree, &(num_isnums));
 /* AIV 12/1/08 - sort the ISNUM tree according to the node number */
 /* (order added) before this was ordering according to obj adr */
 /* which resulted in diff offsets at runtime due to diff adr */
 qsort((char *) isnums_avltab, num_isnums, sizeof(struct avlnode_t *), 
  isnum_cmp); 
 for (i = 0; i < num_isnums; i++)
  {
   pop = (struct prep_obj_t *) isnums_avltab[i]->valp;
   wlen = wlen_(pop->blen);
   pop->isnum_idp_ofs = __nxt_ofs;
   size = 2*wlen;
   __nxt_ofs += size;
  }
 __my_free(isnums_avltab, num_isnums*sizeof(struct avlnode_t *));
}

/*
 * sort the ISNUM tree according to the node number (order added)
 */
static int32 isnum_cmp(const void *np1, const void *np2)
{
 struct prep_obj_t *pop1, *pop2;
 struct avlnode_t *avp1, *avp2;

 avp1 = (*((struct avlnode_t **) np1));
 avp2 = (*((struct avlnode_t **) np2));
 pop1 = (struct prep_obj_t *) avp1->valp;
 pop2 = (struct prep_obj_t *) avp2->valp;
 return(pop1->id - pop2->id);
}

/*
 * Routine now just expands to a max number of pre-allocated idp extra 
 * space.  Cannot realloc due to idp adddress are set in many places.
 *
 * AIV 03/27/09 - these need idp size_t for 64-bit sizes
 */
extern void __expand_1mod_idp_area(struct mod_t *mdp, int32 add_wrds)
{
 size_t newsize;

 /* only need for interactive debugger */
 /* DBG remove -- */
 if (__compiled_sim) __misc_terr(__FILE__, __LINE__);
 /* --- */

 newsize = mdp->mod_idata_siz+add_wrds;
 if (newsize >= (mdp->mod_idata_siz_presim+IDP_IA_GROW_MAX))
  {
   __pv_ferr(314, "INTERNAL FATAL - module is expanded more than data area of size (%d) - contact Tachyon DA", IDP_IA_GROW_MAX);
  }
 mdp->mod_idata_siz = newsize; 
}

/*
 * compute size for one variable and set the offset
 * passed next offset to use and returns next to use after setting offset 
 *
 * SJM 06-17-07 - now also called for memories
 * PORTABILITY FIXME - maybe need 8 byte alignment for ptr too?
 */
extern void __set_1var_net_ofs(struct net_t *np, struct mod_t *mdp)
{
 struct net_t *np2;
 int32 wlen, srtyp;
 word32 arrw;

 /* AIV 07/20/09 - mark if scalar npp list is a scalar NP_MDPRT - which */
 /* can later be optimized during compilation - need to do this */
 /* here because if require idp space */
 if (__compiled_sim) 
  {
   if (mark_if_scalar_port_optim_mdprt(np, mdp))
    {
     /* if it is optimizable allocate the idp offest area */
     mark_scalar_port_optim_ofs(np, mdp);
    }
  }

 np->nva_ofs = __nxt_ofs;
 if (np->n_isarr)
  {
   /* AIV 02/23/09 - if wire get the first element of the net */
   if (np->ntyp < NONWIRE_ST)
    {
     np2 = get_low_wire_array_net(np, mdp);
     /* DBG remove -- */
     if (np2->nva_ofs == 0) __misc_terr(__FILE__, __LINE__);
     /* --- */ 
     np->nva_ofs = np2->nva_ofs;
     return;
    }

   arrw = __get_arrwide(np);
   /* AIV 09/01/10 - if 2-state now just alloc smaller space */
   srtyp = __get_array_srep_type(np);
   /* string array current holds 3 words per element */
   wlen = 0;
   if (srtyp == SR_STRING) wlen = arrw*STR_IDP_WLEN;
   /* 2-state scal is now just a vector */
   else if (srtyp == SR_SCAL2S) wlen = wlen_(arrw);
   /* 2-state now doesn't do any packing */
   else if (srtyp == SR_BIT2S) wlen = arrw*wlen_(np->nwid);
//AIV64 FIXME - these values are now wrong - shouldn't be packing anyway???
   else if (!np->n_isavec) wlen = wlen_(2*arrw);
   else if (np->nwid > WBITS/2) wlen = 2*arrw*wlen_(np->nwid);
   else if (np->nwid <= 4) wlen = (arrw + WRDBYTES)/WRDBYTES;
   else if (np->nwid <= 8) wlen = (2*arrw + WRDBYTES)/WRDBYTES;
   else if (np->nwid <= WBITS/2) wlen = WRDBYTES*arrw;
   else __case_terr(__FILE__, __LINE__); 
   __nxt_ofs += wlen;
   return;
  }

 if (np->ntyp == N_REAL) { __nxt_ofs += 2; return; }
 if (np->ntyp == N_STRING) { __nxt_ofs += STR_IDP_WLEN; return; } 

 /* scalar */
 /* SJM 07-17-07 - could pack scalars as bytes in one area? */ 
 /* SJM 08-09-10 - even for 2 state scalars need one word */ 
 if (!np->n_isavec) __nxt_ofs += 1;
 else
  {
   wlen = wlen_(np->nwid); 
   if (!np->n_stren)
    {
     if (np->srep == SR_BIT2S) __nxt_ofs += wlen;
     else __nxt_ofs += 2*wlen;
    }
   else
    { 
     __nxt_ofs += (np->nwid + WRDBYTES - 1)/WRDBYTES;
    }
  }
}

/*
 * return TRUE if all nlds for passed net can be an optimized NP_MDPRT
 *
 * check for scalar to scalar/bsel/opempty with no delay
 */
static int32 mark_if_scalar_port_optim_mdprt(struct net_t *np, 
 struct mod_t *upmdp)
{
 struct expr_t *up_lhsx;
 struct itree_t *itp, *up_itp;
 struct inst_t *ip;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 struct net_pin_t *npp;
 struct net_t *up_np;
 int32 ii, nchg_val, has_mixed_nchg, only_id;

 /* if has PLI cannot assume simple assign */
 if (__pli_access_level >= 2) return(FALSE);
 /* must be scalar */
 /* AIV 08/29/10 - need SR_SCAL2S here now as well */
 if (np->srep != SR_SCAL && np->srep != SR_SCAL2S) return(FALSE);
 if (np->nlds == NULL) return(FALSE);
 /* if has dces cannot do simple assign - need to also do dce list */
 if (np->dcelst != NULL) return(FALSE);
 /* skip if it has a force */
 if (np->frc_assgn_allocated) return(FALSE);

 /* only id to id */
 only_id = TRUE;
 up_itp = upmdp->moditps[0];
  
 /* AIV 07/13/10 - this needs to be init to false here - read below */
 has_mixed_nchg = FALSE;
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* AIV 08/14/09 - now allowing additionaly npp types */
   if (npp->npntyp != NP_MDPRT) continue;
   /* skip xmrs */
   if (npp->npproctyp != NP_PROC_INMOD) return(FALSE);

   downmdp = npp->elnpp.emdp;
   mpp = &(downmdp->mpins[npp->obnum]);
   if (npp->npntyp == NP_PB_MDPRT) mpp = &(mpp->pbmpps[npp->pbi]);
 
   if (downmdp->flatinum == 1) return(FALSE);

   nchg_val = -1;
   has_mixed_nchg = FALSE;
   for (ii = 0; ii < downmdp->flatinum; ii++) 
    {
     itp = downmdp->moditps[ii];
     /* this is an instance of mod containing rhs output port load */
     ip = itp->itip;
     if (npp->npntyp == NP_PB_MDPRT)
      { up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi]; }
     else up_lhsx = ip->ipins[npp->obnum];

     /* down better be simple scalar ID/ regular LSB/ OPEMPTY */
     if (up_lhsx->optyp != ID && up_lhsx->optyp != LSB && 
      up_lhsx->optyp != OPEMPTY) 
      {
       return(FALSE);
      }
          
     if (up_lhsx->optyp == OPEMPTY) 
      {
       only_id = FALSE;
       continue;
      }

     if (up_lhsx->optyp == LSB) 
      {
       only_id = FALSE;
       /* not handling XMR here */
       if (up_lhsx->lu.x->optyp != ID) return(FALSE);
       up_np = up_lhsx->lu.x->lu.sy->el.enp;
       if (up_np->srep != SR_VEC) return(FALSE);
       /* DBG remove -- */
       if (up_lhsx->ru.x->optyp != NUMBER) __misc_terr(__FILE__, __LINE__);
       /* ---- */
      }
     else 
      {
       up_np = up_lhsx->lu.sy->el.enp;
       /* AIV 08/29/10 - need SR_SCAL2S here now as well */
       if (up_np->srep != SR_SCAL && up_np->srep != SR_SCAL2S) return(FALSE);
      }

     /* skip if it has a force */
     if (up_np->frc_assgn_allocated) return(FALSE);
     if (up_lhsx->x_multfi) return(FALSE); 
     if (up_lhsx->lhsx_ndel) return(FALSE);
     /* check if any lhsx nets have some that need to record chg */
     /* and some that do not */
     if (nchg_val != -1)
      {
       if (nchg_val != __needs_netchg_record(up_np))
        {
         has_mixed_nchg = TRUE;
        }
      }
     else nchg_val = __needs_netchg_record(up_np);
    }
  }

 /* AIV 08/21/09 - if bsel/uncon/id combo - do not produce worse code */
 /* should just produce regular index jump flatten code */
 if (__inline_code && !only_id)
  {
   return(FALSE);
  }

 /* if this is optimized -O (inline) and it contains a mixed nchg */
 /* do not to the nchg - this produces extra condition (if) of port assign */
 if (__inline_code && has_mixed_nchg)
  {
   return(FALSE);
  }
 return(TRUE);
}
     
/*
 * known to be optimized scalar NP_MDPRT - allocate the idp space to 
 * hold the net offset, expr offset, net nchg offset, and the np address if 
 * it has dumpvars
 */
static void mark_scalar_port_optim_ofs(struct net_t *np, struct mod_t *upmdp)
{
 struct expr_t *up_lhsx;
 struct itree_t *itp, *up_itp;
 struct inst_t *ip;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 struct net_pin_t *npp;
 struct net_t *up_np;
 struct net_chg_t *ncp;
 int32 ii, has_nchg, has_dmpv, biti, has_mixed_expr, has_toggle;

 up_itp = upmdp->moditps[0];
 has_mixed_expr = -1;
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* AIV 08/14/09 - now allowing additionaly npp types */
   if (npp->npntyp != NP_MDPRT) continue;

   has_nchg = has_dmpv = has_toggle = FALSE;
   downmdp = npp->elnpp.emdp;
   mpp = &(downmdp->mpins[npp->obnum]);
   if (npp->npntyp == NP_PB_MDPRT) mpp = &(mpp->pbmpps[npp->pbi]);

   for (ii = 0; ii < downmdp->flatinum; ii++) 
    {
     itp = downmdp->moditps[ii];
     /* this is an instance of mod containing rhs output port load */
     ip = itp->itip;
     if (npp->npntyp == NP_PB_MDPRT)
      { up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi]; }
     else up_lhsx = ip->ipins[npp->obnum];

     /* check for mixed expression -2 indicates mixed expressions */
     if (has_mixed_expr == -1)
      {
       has_mixed_expr = up_lhsx->optyp;
      }
     else if (has_mixed_expr != up_lhsx->optyp) has_mixed_expr = -2;

     /* if opempty mark as mixed */
     if (up_lhsx->optyp == OPEMPTY) 
      {
       has_mixed_expr = -2;
       continue;
      }

     /* if lsb mark as mixed - if all lsb will lower correctly in v_bbgen2 */
     if (up_lhsx->optyp == LSB)
      {
       has_mixed_expr = -2;
       /* DBG remove -- */
       if (up_lhsx->lu.x->optyp != ID) __misc_terr(__FILE__, __LINE__);
       /* --- */ 
       up_np = up_lhsx->lu.x->lu.sy->el.enp;
       biti = __comp_ndx(up_np, up_lhsx->ru.x);
      }
     else 
      {
       biti = -1;
       up_np = up_lhsx->lu.sy->el.enp;
      }

     /* need to mark flag for later lower fixed data */
     if (__needs_netchg_record(up_np) && __net_chg_nd_store(up_np, biti, biti)) 
      {
       has_nchg = TRUE;
       ncp = __find_nchg_range(up_np, biti, biti);
       ncp->is_lowered  = TRUE;
      }
     if (up_np->dmpv_in_src || up_np->dmpp_in_src) 
      {
       has_dmpv = TRUE;
      }
     /* AIV 12/06/10 - toggle needs to record changes */
     if (up_np->n_has_toggle) 
      {
       has_toggle = TRUE;
      }
    }
   npp->scalar_mdprt_ofs = __nxt_ofs;
   /* if has an nchg need to allocate space for nchg address */
   __nxt_ofs++;
   /* AIV BEWARE - these orders are assumed here - must remain in order */
   if (has_mixed_expr == -2) __nxt_ofs++;
   if (has_nchg) __nxt_ofs++;
   /* if dmpv one for np address */
   if (has_dmpv || has_toggle) __nxt_ofs++;
  }
}

/*
 * return the net of the low wire array - for a single dimension
 */
static struct net_t *get_low_wire_array_net(struct net_t *np, 
 struct mod_t *mdp)
{
 struct mda_t *mdap;
 int32 ai, ri1, ri2, arrwid, dim;
 struct sy_t *syp;
 struct net_t *np2;
 char s1[RECLEN], s2[RECLEN];

 /* one dimension */
 mdap = np->mda;
 if (mdap == NULL)
  {
   __getarr_range(np, &ri1, &ri2, &arrwid);
   ai = ri2;
   sprintf(s1, "%s[%d]", np->nsym->synam, ai);
   syp = __get_sym(s1, mdp->msymtab);
  }
 else
  {
   /* mda just get the lowest range for every dimension */
   strcpy(s1, np->nsym->synam);
   for (dim = 0; dim < mdap->dimension; dim++)
    {
     ri1 = mdap->rng1[dim];
     ri2 = mdap->rng2[dim];
//AIV FIXME - ????????
     if (ri1 < ri2) ai = ri1;
     else ai = ri2;
     sprintf(s2, "%s[%d]", s1, ai);
     strcpy(s1, s2);
    }
   syp = __get_sym(s2, mdp->msymtab);
  }
 /* DBG remove -- */
 if (syp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */ 
 np2 = syp->el.enp;
 return(np2);
}

/*
 * allocate all module variable (net) storage for one inst and then memcpy 
 * that template for every instance
 *
 * need region big enough for all instance but only fills lowest (1st inst)
 * version only for the interpreter  
 */
extern void __alloc_sim_storage(void)
{
 int32 ii;
 t_midat *new_idp;
 struct mod_t *mdp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* DBG remove -- */
   if (mdp->mod_idata_siz == 0) __misc_terr(__FILE__, __LINE__);
   /* --- */ 
   
   /* AIV 03/31/09 - add space for interactive debugger events idp grow */
   /* AIV 08/04/09 - if compiled sim no need to alloc IDP_IA_GROW_MAX */
   /* this is only needed for debugger - can waste space for small */
   /* gate modules where ther are many instances */
   if (__compiled_sim)
    {
     mdp->mod_idata = (t_midat *)
       __my_malloc(mdp->flatinum*(mdp->mod_idata_siz)*WRDBYTES);
    }
   else
    {
     mdp->mod_idata = (t_midat *)
       __my_malloc(mdp->flatinum*(mdp->mod_idata_siz+IDP_IA_GROW_MAX)*WRDBYTES);
    }
   __idp = mdp->mod_idata;

   mdp->moditps[0]->it_idp = __idp;

   for (ii = 1; ii < mdp->flatinum; ii++)
    {
     new_idp = (t_midat *) &(mdp->mod_idata[ii*mdp->mod_idata_siz]);
     mdp->moditps[ii]->it_idp = new_idp;
    }
  }
 __idp = NULL;
}

/*
 * AIV 07/12/07 
 * initialize nets now need to be separated from the allocation of the storage
 * the init values for the nets now depends on drivers and npps are now
 * filtered by the matching idp so these need to be separated out 
 */
extern void __init_sim_storage(void)
{
 int32 ni, ii, sti;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct itree_t *up_itp;
 struct st_t *stp;
 struct delctrl_t *dctp;
 t_midat *new_idp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   __idp = mdp->mod_idata;
   
   if (mdp->mnnum != 0)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       /* no allocated storage here for parameters - in different list */
       /* also none for events (if dce will be allocated when used) */
       if (np->ntyp == N_EVENT) continue;

       /* for now always zeroing variables - when x/z */
       /* could free later if no fan-in and no fan-out */
       __init_var(np);
       init_net_npp_tchk_idpvals(np);
      } 
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       if (np->ntyp == N_EVENT) continue;

       /* for now always zeroing variables - when x/z */
       __init_var(np);
       init_net_npp_tchk_idpvals(np);
      }
    }

   for (sti = 0; sti < mdp->prov_mstnum; sti++)
    {
     stp = mdp->prov_mstndx[sti];
     
     if (stp->stmttyp == S_REPEAT) __idp[stp->st.srpt.reptmp_ofs] = 0;
     else if (stp->stmttyp == S_DELCTRL)
      {
       dctp = stp->st.sdc;
       /* SJM 08-07-07 - no sched event init is NULL */
       __idp[dctp->dceschd_tev_ofs] = (t_midat) NULL;
       if (dctp->repcntx != NULL) __idp[dctp->dce_repcnt_ofs] = 0;
      }
     /* need to get the wait statements delctrl as well */
     else if (stp->stmttyp == S_WAIT)
      {
       dctp = stp->st.swait.wait_dctp;
       __idp[dctp->dceschd_tev_ofs] = (t_midat) NULL;
       if (dctp->repcntx != NULL) __idp[dctp->dce_repcnt_ofs] = 0;
      }
    }
   /* init the continous assign area for one instance */
   init_contas_idp_area(mdp);
   /* init the gate storage area for one instance */
   init_gate_idp_area(mdp);

   /* SJM 06-18-07 now only first inst vars reinitialized - must copy */
   /* template into all other instances */
   __idp[MD_INUM] = (t_midat) mdp->moditps[0]->itinum;
   // ((struct mod_t *) &(__idp[MD_MDP]))[0] = mdp; 
   __idp[MD_MDP] = (t_midat) mdp; 
   // ((struct itree_t *) &(__idp[MD_ITP]))[0] = mdp->moditps[0];
   __idp[MD_ITP] = (t_midat) mdp->moditps[0]; 
   up_itp = mdp->moditps[0]->up_it;
   if (up_itp != NULL) __idp[MD_UPIDP] = (t_midat) up_itp->it_idp;
   else __idp[MD_UPIDP] = (t_midat) NULL;

   __idp[MD_DOWNITPS] = (t_midat) mdp->moditps[0]->in_its;
   __idp[MD_DPIP] = 0;

   /* need link from itree to mod idata areas - this is 0th */
   mdp->moditps[0]->it_idp = __idp;

   for (ii = 1; ii < mdp->flatinum; ii++)
    {
     new_idp = (t_midat *) &(mdp->mod_idata[ii*mdp->mod_idata_siz]);
     memcpy(new_idp, __idp, WRDBYTES*mdp->mod_idata_siz);

     new_idp[MD_INUM] = (t_midat) mdp->moditps[ii]->itinum;
     // *((struct mod_t *) &(new_idp[MD_MDP])) = mdp; 
     new_idp[MD_MDP] = (t_midat) mdp;
     // *((struct itree_t *) &(new_idp[MD_ITP])) = mdp->moditps[ii];
     new_idp[MD_ITP] = (t_midat) mdp->moditps[ii];

     up_itp = mdp->moditps[ii]->up_it;
     if (up_itp != NULL) new_idp[MD_UPIDP] = (t_midat) up_itp->it_idp;
     else new_idp[MD_UPIDP] = (t_midat) NULL;

     new_idp[MD_DOWNITPS] = (t_midat) mdp->moditps[ii]->in_its;
     new_idp[MD_DPIP] = 0;
     mdp->moditps[ii]->it_idp = new_idp;
    }
   __pop_wrkitstk();
   /* AIV 12/06/10 - set toggle structs */
   if (__toggle_coverage) init_net_toggle_ofs(mdp);
  }

 __idp = NULL;
}

/*
 * alloc compiled sim storage for CVC
 *
 * SJM 07-25-07 - almost same as interp version except for mod idp creation
 * another routine intializes and this routine build the 0th instance only
 * mod idp info table for mapping from storage disps to the object in
 */
extern void __alloc_compiled_sim_storage(void)
{
 int32 ii, nmods;
 struct mod_t *mdp;
 t_midat *new_idp;

 nmods = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt, nmods++)
  {
   __push_wrkitstk(mdp, 0);

   /* AIV 07/25/09 - if running the executable cvcsim - just get the */
   /* fixed __idpdat address - previously was allocing and then */
   /* freeing later - this is much better because there isn't a need */
   /* for two copies of the idp area and a need to memcpy/free the other */
   if (__running_cvc_exe)
    {
     mdp->mod_idata = __idpdat_areasp[nmods];
     /* DBG remove -- */ 
     if (mdp->mod_idata == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
    }
   else
    {
     mdp->mod_idata = (t_midat *) 
      __my_malloc(mdp->flatinum*mdp->mod_idata_siz*WRDBYTES);
    }

   /* AIV 07/30/07 - need to set these here because these are needed */
   /* to set filt idp so must be set here */
   /* AIV FIXME ???? can remove if there is some index scheme for compiler */
   /* since compiled code cannot compare addresses */
   mdp->moditps[0]->it_idp = mdp->mod_idata;
   for (ii = 1; ii < mdp->flatinum; ii++)
    {
     new_idp = (t_midat *) &(mdp->mod_idata[ii*mdp->mod_idata_siz]);
     mdp->moditps[ii]->it_idp = new_idp;
    }
   __pop_wrkitstk();
  }
 if (__opt_debug_flg || __opt_valtrk)
  {
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     __push_wrkitstk(mdp, 0);
     bld_1mod_idp_map(mdp);
     __pop_wrkitstk();
    }
  }
}

//############################################################################

/*
 * ROUTINES TO FILL IDP AREA MAP FOR DEBUGGING AND LATER VALUE TRACKING
 */

/*
 * alloc and fill the idp map one idp area map for one module
 *
 * SJM 12/06/07 - notice idp area sized and accessed as word (wrd index) but
 * instruction offsets are in bytes
 *
 * compiler needs to know what index of __idp point to what for debug
 *
 * SJM 12/06/07 - only build the mod idp info table if dbg on
 * mod idp info table allows map from disp's in idp area bak to ofs of
 */
static void bld_1mod_idp_map(struct mod_t *mdp)
{
 int32 idi, ni, sti, wlen, ca_ctev_set;
 int32 bi, cai, gi, nins, i, num_isnums;
 struct net_t *np;
 struct task_t *tskp;
 struct st_t *stp;
 struct delctrl_t *dctp;
 struct conta_t *cap, *pbcap;
 struct expr_t *rhsx;
 struct udp_t *udpp;
 struct gate_t *gp;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;
 struct avlnode_t **isnums_avltab;
 struct prep_obj_t *pop;

 /* SJM 12/07/07 - idp map is array of ptrs to idp map records */
 mdp->mod_idp_map = (struct idp_map_t **)
  __my_malloc(mdp->mod_idata_siz*sizeof(struct idp_map_t *));
 for (idi = 0; idi < mdp->mod_idata_siz; idi++)
  {
   mdp->mod_idp_map[idi] = NULL;
  }

 /* fill the 0th instance (only) idp map for mapping idp disp to net */
 if (mdp->mnnum != 0)
  {
   /* fill idp map parallel table entries for module nets */  
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
    {
     /* AIV 01/11/08 - this can now be shared across nets */
     /* AIV 03/26/08 - should be == NULL */
     if (mdp->mod_idp_map[np->nchgaction_ofs] == NULL) 
      {
       alloc_fill_idp_map_el(mdp, np->nchgaction_ofs, 1, IDPMAP_NCHGACTION,
        (void *) np);
      }

     if (np->ntyp == N_EVENT) continue;

     /* add the idp map struct to get the net from the ndx */
     wlen = get_1net_idp_wlen(np);
     alloc_fill_idp_map_el(mdp, np->nva_ofs, wlen, IDPMAP_NVAOFS, (void *) np);

     set_net_dce_idp_map(np, mdp);

     if (np->ndel_ctevtab != NULL && np->ndel_ctevtab[0]->ctev_idp_ofs != 0) 
      {
       /* SJM 12/06/07 - here the indices are in the CT tev data struct */
       /* but they still must be contiguous - this checks */
       alloc_fill_ctevtab_idp_map_els(mdp, np->ndel_ctevtab, np->nwid,
        IDPMAP_NET_TEVP, (void *) np);   
      }
    }
  }

 /* fill idp map parallel table entries for task in module nets */  
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   if (tskp->trnum == 0) continue;

   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     /* AIV 01/11/08 - this can now be shared across nets */
     /* AIV 03/26/08 - should be == NULL */
     if (mdp->mod_idp_map[np->nchgaction_ofs] == NULL) 
      {
       alloc_fill_idp_map_el(mdp, np->nchgaction_ofs, 1, IDPMAP_NCHGACTION,
        (void *) np);
      }

     if (np->ntyp == N_EVENT) continue;

     /* add the idp map struct to get the net from the ndx */
     wlen = get_1net_idp_wlen(np);
     alloc_fill_idp_map_el(mdp, np->nva_ofs, wlen, IDPMAP_NVAOFS,
      (void *) np);

     set_net_dce_idp_map(np, mdp);

     if (np->ndel_ctevtab != NULL) 
      {
       /* SJM 12/06/07 - here the indices are in the CT tev data struct */
       /* but they still must be contiguous - this checks */
       alloc_fill_ctevtab_idp_map_els(mdp, np->ndel_ctevtab, np->nwid,
        IDPMAP_NET_TEVP, (void *) np);   
      }
    }
  }

 /* SJM 12/12/07 - need to map params too */
 if (mdp->mprmnum != 0)
  {
   for (ni = 0, np = &(mdp->mprms[0]); ni < mdp->mprmnum; ni++, np++) 
    {
     wlen = get_1net_idp_wlen(np);
     alloc_fill_idp_map_el(mdp, np->nva_ofs, wlen, IDPMAP_NVAOFS,
      (void *) np);
    }
  }

 /* fill idp map parallel table entries for task in module statements */  
 for (sti = 0; sti < mdp->prov_mstnum; sti++)
  {
   stp = mdp->prov_mstndx[sti];
   if (stp->stmttyp == S_REPEAT)
    {
     alloc_fill_idp_map_el(mdp, stp->st.srpt.reptmp_ofs, 1, IDPMAP_REP_BP,
      (void *) stp);
    } 
   else if (stp->stmttyp == S_DELCTRL)
    {
     dctp = stp->st.sdc;

     alloc_fill_idp_map_el(mdp, dctp->dceschd_tev_ofs, 1, IDPMAP_DCESCH_TEVS,
      (void *) dctp);

     if (dctp->repcntx != NULL)
      {
       alloc_fill_idp_map_el(mdp, dctp->dce_repcnt_ofs, 1, IDPMAP_DELREP_BP,
        (void *) dctp);
      }
    }
   else if (stp->stmttyp == S_WAIT)
    {
     /* need to get the wait statements del ctrl as well */
     dctp = stp->st.swait.wait_dctp;

     alloc_fill_idp_map_el(mdp, dctp->dceschd_tev_ofs, 1, IDPMAP_DCESCH_TEVS,
      (void *) dctp);

     if (dctp->repcntx != NULL)
      {
       alloc_fill_idp_map_el(mdp, dctp->dce_repcnt_ofs, 1, IDPMAP_DELREP_BP,
        (void *) dctp);
      }
    } 
   else if (stp->stmttyp == S_NBPROCA)
    {
     /* non-blocking storage area */
     wlen = get_rhs_del_storage_wlen(stp);
     alloc_fill_idp_map_el(mdp, stp->rhs_idp_ofs, wlen, IDPMAP_NB_BP,
      (void *) stp);
    }
   else if (stp->stmttyp == S_RHSDEPROCA)
    {
     rhsx = stp->st.spra.rhsx;
     /* don't need storage area if rhs is constant */
     if (!__is_const_expr(rhsx)) 
      {
       wlen = get_rhs_del_storage_wlen(stp);
       alloc_fill_idp_map_el(mdp, stp->rhs_idp_ofs, wlen, IDPMAP_PD_RHSBP,
        (void *) stp);
      }
    }
   if ((ctevp = stp->ctevp) != NULL) 
    {
     if (ctevp->ctev_idp_ofs != 0)
      {
       alloc_fill_ctevp_idp_map_el(mdp, ctevp, IDPMAP_ST_TEVP, (void *) stp);
      }
    }
  }

 /* add the conta storage dbg info */
 for (cai = 0, cap = &(mdp->mcas[0]); cai < mdp->mcanum; cai++, cap++)
  {
   ca_ctev_set = FALSE;
   if (!cap->ca_pb_sim)
    {
     ca_ctev_set = FALSE;
     wlen = wlen_(cap->lhsx->szu.xclen);
     if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
      { 
       alloc_fill_idp_map_el(mdp, cap->ca_drv_ofs, 2*wlen, IDPMAP_CA_DRVBP,
        (void *) cap);

//AIV? 12/12/07 - logic doesn't make any sense - can't do this twice ????
       if (cap->ctevp != NULL && cap->ctevp->ctev_idp_ofs != 0)
        {
         alloc_fill_ctevp_idp_map_el(mdp, cap->ctevp, IDPMAP_CA_TEVP,
          (void *) cap);   
         ca_ctev_set = TRUE;
        }
      }
     if (cap->ca_delrep != DT_NONE)
      {
       alloc_fill_idp_map_el(mdp, cap->schd_drv_ofs, 2*wlen,
        IDPMAP_CA_SCHBP, (void *) cap);

       if (!ca_ctev_set && cap->ctevp != NULL
        && cap->ctevp->ctev_idp_ofs != 0)
        {
         alloc_fill_ctevp_idp_map_el(mdp, cap->ctevp, IDPMAP_CA_TEVP,
          (void *) cap);   
        }
      }
    }
   else
    {
     /* AIV 08/15/07 - must do the original cap itself as well */
//AIV FIXME - don't think this pbit is needed?????
     wlen = wlen_(cap->lhsx->szu.xclen);
//AIV? FIXME 12/12/07 - again this logic makes no sense ????? see above
     if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
      {
       alloc_fill_idp_map_el(mdp, cap->ca_drv_ofs, 2*wlen, IDPMAP_CA_DRVBP,
        (void *) cap);
      }
     if (cap->ca_delrep != DT_NONE)
      { 
       alloc_fill_idp_map_el(mdp, cap->schd_drv_ofs, 2*wlen,
       IDPMAP_CA_SCHBP, (void *) cap);
      }
     for (bi = 0; bi < cap->lhsx->szu.xclen; bi++) 
      {
       pbcap = &(cap->pbcau.pbcaps[bi]);
       wlen = wlen_(cap->lhsx->szu.xclen);
       if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
        { 
         alloc_fill_idp_map_el(mdp, pbcap->ca_drv_ofs, 2*wlen,
          IDPMAP_CA_DRVBP, (void *) cap);
        }
      }
    }
  }
 /* gate storage info */
 for (gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);
   nins = gp->gpnum - 1;
   /* AIV 08/16/07 - if have any sdf must alloc in event because */
   /* sdf could need events from rt eval for sdf file */
   if (gp->g_delrep != DT_NONE || (__sdflst != NULL || __has_sdfann_calls))
    {
     if (gp->ctevp != NULL && gp->ctevp->ctev_idp_ofs != 0)
      {
       alloc_fill_ctevp_idp_map_el(mdp, gp->ctevp, IDPMAP_GP_TEVP,
        (void *) gp);   
      }
     }
   /* AIV 08/13/07 - only certain gates have output value stored in idp */
   /* SJM 12/12/07 - gate out mapping must be outside gate type ifs */
   if (__gate_needs_output_word(gp->g_class))
    {
     alloc_fill_idp_map_el(mdp, gp->gate_out_ofs, 1, IDPMAP_GATE_OUTBP,
      (void *) gp);
    }

   /* SJM 12/12/07 - no state for pull or tran */
   if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN) continue;

   /* wide logic case */
   if (gp->g_class == GC_LOGIC && gp->gpnum > 16)
    {
     if (nins < 16)
      {
       /* SJM - this should be gstate ofs not gate out ofs */ 
       alloc_fill_idp_map_el(mdp, gp->gstate_ofs, 1, IDPMAP_GATE_OUTBP,
        (void *) gp);
      }
     else
      {
       /* AIV 08/13/07 - currently only type of gate that doesn't pack */
       /* the output value is narrow logic gates */
       wlen = 2*wlen_(gp->gpnum);
       alloc_fill_idp_map_el(mdp, gp->gstate_ofs, wlen, IDPMAP_GATEBP,
        (void *) gp);
      }
     continue;
    }
   else if (gp->g_class == GC_UDP) 
    {
     udpp = gp->gmsym->el.eudpp;
     if (udpp->u_wide) wlen = 2; else wlen = 1;
     alloc_fill_idp_map_el(mdp, gp->gstate_ofs, wlen, IDPMAP_GATEBP,
      (void *) gp);
    }
   else
    {
     alloc_fill_idp_map_el(mdp, gp->gstate_ofs, 1, IDPMAP_GATEBP,
      (void *) gp);
    }
  }
 /* the net change idp info */
 /* SJM 08/04/08 - need to store the nchg idp ofs even for 1 inst */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
    {
     alloc_fill_idp_map_el(mdp, ncp->nchg_idp_ofs, 1, IDPMAP_PNCHG,
      (void *) ncp);
    }
  }

 /* SJM 08/03/08 - need to fill tchk old value and last chg time idp maps */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   set_net_tchk_chg_val_idp_map(np, mdp);
//AIV TOGGLE - need IDP MAP - here
  }

 /* AIV 04/06/08 - need to fill idp map for ISNUMBERS */
 if (mdp->isnum_tree != NULL) 
  {
   isnums_avltab = __linearize_avl_tree(mdp->isnum_tree, &(num_isnums));
   /* AIV 12/1/08 - sort the ISNUM tree according to the node number */
   /* (order added) before this was ordering according to obj adr */
   /* which resulted in diff offsets at runtime due to diff adr */
   qsort((char *) isnums_avltab, num_isnums, sizeof(struct avlnode_t *), 
     isnum_cmp); 
   for (i = 0; i < num_isnums; i++)
    {
     pop = (struct prep_obj_t *) isnums_avltab[i]->valp;
     alloc_fill_idp_map_el(mdp, pop->isnum_idp_ofs, 2*wlen_(pop->blen), 
      IDPMAP_ISNUM, (void *) pop);
    }
   __my_free(isnums_avltab, num_isnums*sizeof(struct avlnode_t *));
  }


 /* final step - check to make sure all idp locations mapped */
 /* SJM 12/07/07 - FIXME? should probably put MAP elemets in low 6 words */
 /* AIV 01/11/08 - the offset + 1 is always dummy net change word - so skip */
 /* may never be set if never used but is always alloc */
 for (idi = IDP_HD_WOFS + 1; idi < mdp->mod_idata_siz; idi++)
  {
   if (mdp->mod_idp_map[idi] == NULL) __misc_terr(__FILE__, __LINE__);
  }
}

/*
 * set idp map elements for net dce fields
 */
static void set_net_dce_idp_map(struct net_t *np, struct mod_t *mdp)
{
 int32 wlen;
 struct dcevnt_t *dcep; 

 for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
  {
   if (__dce_needs_prevval(dcep, mdp))
    {
     wlen = __get_dce_prevval_wsiz(dcep, np);
     alloc_fill_idp_map_el(mdp, dcep->prevval_ofs, wlen, IDPMAP_DCEPREV,
      (void *) dcep);
    }
   if (dcep->dce_expr != NULL)
    {
//AIV? 12/12/07 - FIXME ??? - expr shared by two dce's should copy
     if (mdp->mod_idp_map[dcep->dce_expr->expr_ofs] == NULL)
      {
       alloc_fill_idp_map_el(mdp, dcep->dce_expr->expr_ofs, 1,
        IDPMAP_DCEEXPR_BP, (void *) dcep);
      }
    }
  }
}

/*
 * fill idp map for the time check old value and change time fields 
 */
static void set_net_tchk_chg_val_idp_map(struct net_t *np, struct mod_t *mdp)
{
 struct net_pin_t *npp;
 struct tchg_t *tchgp;
 struct chktchg_t *chktcp;

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_TCHG) continue; 

   switch ((byte) npp->chgsubtyp) {
    case NPCHG_TCSTART: case NPCHG_PTHSRC:

     tchgp = npp->elnpp.etchgp;
     alloc_fill_idp_map_el(mdp, tchgp->lastchg_ofs, 3, IDPMAP_TCHK_CHG,
      (void *) npp);
     break;
    case NPCHG_TCCHK:
     chktcp = npp->elnpp.echktchgp;
     alloc_fill_idp_map_el(mdp, chktcp->chkactive_ofs, 6, IDPMAP_TCHK_CHG,
     (void *) npp);
     break;
   }
  }
}

/*
 * wrapper to alloc idp map el for an event ctev table (comp time event record) 
 * this is for ndel array (table) of ctevs
 *
 * differs from normal alloc (fill) idp map because the ctev array contains
 * one idp offset in each of the table of ctev elements
 *
 * routine also checks to make sure the ctev contained ofs are contiguous
 */
static void alloc_fill_ctevtab_idp_map_els(struct mod_t *mdp,
 struct ctev_t **ctevtab, int32 siz_idp_area, int32 t, void *vp)
{
 int idi, ctev_1st_ofs;
 
 ctev_1st_ofs = ctevtab[0]->ctev_idp_ofs;
 /* DBG remove -- */ 
 if (ctev_1st_ofs == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 for (idi = 1; idi < siz_idp_area; idi++)
  {
   if (ctevtab[idi]->ctev_idp_ofs != ctev_1st_ofs + idi)
    __misc_terr(__FILE__, __LINE__);
  }
 alloc_fill_idp_map_el(mdp, ctev_1st_ofs, siz_idp_area, t, vp);
}

/*
 * wrapper to alloc idp map el for an event ctevp (compile time event record) 
 *
 * differs from normal alloc (fill) idp map because the ctevp element
 * know always exactly one element (i.e. non per bit case)
 * contains other fieldds that can be checked here
 */
static void alloc_fill_ctevp_idp_map_el(struct mod_t *mdp,
 struct ctev_t *ctevp, int32 t, void *vp)
{
 /* DBG remove -- */ 
 if (ctevp->ctev_idp_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 alloc_fill_idp_map_el(mdp, ctevp->ctev_idp_ofs, 1, t, vp);
}

/*
 * alloc an element for a module's idp map malloced table
 *
 * exactly one element per word of mod idp info array and all elements within
 * the area for one object (currently netbp or netadr) point to the same
 * ojbect - i.e. any idp offset such as the bpart word can be used to 
 * get the object - the low area few words have idp object types
 */
static void alloc_fill_idp_map_el(struct mod_t *mdp, int32 base_idp_ofs,
 int32 siz_idp_area, int32 t, void *vp)
{
 int idi;
 struct idp_map_t *idp_mapp;

 /* DBG remove -- */
 if (base_idp_ofs == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */

 idp_mapp = (struct idp_map_t *) __my_malloc(sizeof(struct idp_map_t));
 for (idi = base_idp_ofs; idi < base_idp_ofs + siz_idp_area; idi++)
  {
   /* DBG remove -- */
   if (mdp->mod_idp_map[idi] != NULL) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   mdp->mod_idp_map[idi] = idp_mapp;
   idp_mapp->idpmaptyp = t;
   idp_mapp->idpobju.eanyp = vp;
  }
}

//###########################################################################

/*
 * version of net value storage allocator for CVC
 *
 * new algorithm requires __idp to be set to 0th instance
 */
extern void __init_compiled_sim_storage(void)
{
 int32 ni, ii, sti, wlen, i, ndx, idp_ofs, size, num_isnums;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct itree_t *up_itp;
 struct st_t *stp;
 struct delctrl_t *dctp;
 struct expr_t *rhsx;
 struct prep_obj_t *pop;
 struct avlnode_t **isnums_avltab;
 word32 *wp;
 t_midat *new_idp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   __idp = mdp->mod_idata;
   
   /* initialize variables for first (0th) inst */ 
   if (mdp->mnnum != 0)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       /* no allocated storage here for parameters - in different list */
       /* also none for events (if dce will be allocated when used) */
       if (np->ntyp == N_EVENT) continue;

       /* for now always zeroing variables - when x/z */
       /* could free later if no fan-in and no fan-out */
       __init_var(np);
       init_net_npp_tchk_idpvals(np);
      } 
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       if (np->ntyp == N_EVENT) continue;

       /* for now always zeroing variables - when x/z */
       __init_var(np);
       init_net_npp_tchk_idpvals(np);
      }
    }

   for (sti = 0; sti < mdp->prov_mstnum; sti++)
    {
     stp = mdp->prov_mstndx[sti];
     
     if (stp->stmttyp == S_REPEAT) __idp[stp->st.srpt.reptmp_ofs] = 0;
     else if (stp->stmttyp == S_DELCTRL)
      {
       dctp = stp->st.sdc;

       /* SJM 08-07-07 - no sched event init is NULL */
       __idp[dctp->dceschd_tev_ofs] = (t_midat) NULL;
       if (dctp->repcntx != NULL) __idp[dctp->dce_repcnt_ofs] = 0;
      }
     /* need to get the wait statements delctrl as well */
     if (stp->stmttyp == S_WAIT)
      {
       dctp = stp->st.swait.wait_dctp;
       __idp[dctp->dceschd_tev_ofs] = (t_midat) NULL;
       if (dctp->repcntx != NULL) __idp[dctp->dce_repcnt_ofs] = 0;
      }
//AIV LOOKATME - don't really need to init this area but should do so 
//to remain consistent
     else if (stp->stmttyp == S_RHSDEPROCA)
      {
       rhsx = stp->st.spra.rhsx;
       /* don't need storage area if rhs is constant */
       if (!__is_const_expr(rhsx)) 
        {
         wlen = get_rhs_del_storage_wlen(stp);
         /* initialize to 0 maybe -1 better ????? */
         memset(&(__idp[stp->rhs_idp_ofs]), 0, wlen*WRDBYTES);
        }
      }
    }

   /* init the continous assign area for one instance */
   init_contas_idp_area(mdp);
   /* init the gate storage area for one instance */
   init_gate_idp_area(mdp);
   
   /* SJM 06-18-07 now only first inst vars reinitialized - must copy */
   /* template into all other instances */
   __idp[MD_INUM] = (t_midat) mdp->moditps[0]->itinum;
   __idp[MD_MDP] = (t_midat) mdp; 
   __idp[MD_ITP] = (t_midat) mdp->moditps[0]; 
   up_itp = mdp->moditps[0]->up_it;
   mdp->moditps[0]->it_idp = __idp;

   if (up_itp != NULL) __idp[MD_UPIDP] = (t_midat) up_itp->it_idp;
   else __idp[MD_UPIDP] = (t_midat) NULL;

   __idp[MD_DOWNITPS] = (t_midat) mdp->moditps[0]->in_its;
   __idp[MD_DPIP] = 0;

   for (ii = 1; ii < mdp->flatinum; ii++)
    {
     new_idp = (t_midat *) &(mdp->mod_idata[ii*mdp->mod_idata_siz]);
     memcpy(new_idp, __idp, WRDBYTES*mdp->mod_idata_siz);

     new_idp[MD_INUM] = (t_midat) mdp->moditps[ii]->itinum;
     new_idp[MD_MDP] = (t_midat) mdp;
     new_idp[MD_ITP] = (t_midat) mdp->moditps[ii];

     up_itp = mdp->moditps[ii]->up_it;
     if (up_itp != NULL) new_idp[MD_UPIDP] = (t_midat) up_itp->it_idp;
     else new_idp[MD_UPIDP] = (t_midat) NULL;
   
     new_idp[MD_DOWNITPS] = (t_midat) mdp->moditps[ii]->in_its;
     new_idp[MD_DPIP] = 0;
     mdp->moditps[ii]->it_idp = new_idp;
    }

   /* AIV 08/06/07 - parms are now store per idp instance as well */
   if (mdp->mprmnum != 0)
    {
     for (ni = 0, np = &(mdp->mprms[0]); ni < mdp->mprmnum; ni++, np++) 
      {
       wlen = wlen_(np->nwid);
       if (np->srep == SR_PNUM)
        {
         for (ii = 0; ii < mdp->flatinum; ii++)
          {
           new_idp = (t_midat *) &(mdp->mod_idata[ii*mdp->mod_idata_siz]);
           memcpy(&(new_idp[np->nva_ofs]), &(np->prm_nva.wp[0]), 
            2*WRDBYTES*wlen);
          }

        }
       else if (np->srep == SR_PISNUM)
        {
         for (ii = 0; ii < mdp->flatinum; ii++)
          {
           new_idp = (t_midat *) &(mdp->mod_idata[ii*mdp->mod_idata_siz]);
           memcpy(&(new_idp[np->nva_ofs]), &(np->prm_nva.wp[2*wlen*ii]), 
            2*WRDBYTES*wlen);
          }
        }
       else __case_terr(__FILE__, __LINE__);
      }
    }

   /* AIV 12/06/10 - set toggle structs */
   if (__toggle_coverage) init_net_toggle_ofs(mdp);

   __pop_wrkitstk();
  }
 
 /* AIV 04/06/08 - need to copy the ISNUMBERS into the idp area */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->isnum_tree == NULL) continue;
   __idp = mdp->mod_idata;
   isnums_avltab = __linearize_avl_tree(mdp->isnum_tree, &(num_isnums));
   for (i = 0; i < num_isnums; i++)
    {
     pop = (struct prep_obj_t *) isnums_avltab[i]->valp;
     wp = &(__contab[pop->xvi]);
     idp_ofs = pop->isnum_idp_ofs;
     for (ii = 0; ii < mdp->flatinum; ii++)
       {
        new_idp = (t_midat *) &(mdp->mod_idata[ii*mdp->mod_idata_siz]);
        size = 2*wlen_(pop->blen);
        ndx = ii*size;
        memcpy(&(new_idp[idp_ofs]), &(wp[ndx]), size*WRDBYTES);
       }
    }
   __my_free(isnums_avltab, num_isnums*sizeof(struct avlnode_t *));
  }
 __idp = NULL;
}

/*
 * get the idp length in words for a nets storage area
 */
static int32 get_1net_idp_wlen(struct net_t *np)
{
 int32 wlen, srtyp;
 word32 arrw;

 wlen = -1;
 if (np->n_isarr)
  {
   arrw = __get_arrwide(np);
   /* AIV 09/01/10 - if 2-state now just alloc smaller space */
   srtyp = __get_array_srep_type(np);
   /* string array current holds 3 words per element */
   if (srtyp == SR_STRING) wlen = arrw*STR_IDP_WLEN;
   else if (srtyp == SR_SCAL2S) wlen = wlen_(arrw)*WRDBYTES;
   else if (srtyp == SR_BIT2S) wlen = arrw*wlen_(np->nwid)*WRDBYTES;
   else if (!np->n_isavec) wlen = wlen_(2*arrw);
   else if (np->nwid > WBITS/2) wlen = 2*arrw*wlen_(np->nwid);
   else if (np->nwid <= 4) wlen = (arrw + WRDBYTES)/WRDBYTES;
   else if (np->nwid <= 8) wlen = (2*arrw + WRDBYTES)/WRDBYTES;
   else if (np->nwid <= 16) wlen = WRDBYTES*arrw;
   else __case_terr(__FILE__, __LINE__); 
   return(wlen);
  }

 if (np->ntyp == N_REAL) return(2); 
 if (np->ntyp == N_STRING) return(STR_IDP_WLEN); 

 /* scalar */
 /* SJM 07-17-07 - could pack scalars as bytes in one area? */ 
 /* SJM 08-03-10 - notice for new 2 state scalar still needs an idp word */
 else if (!np->n_isavec) wlen = 1;
 else
  {
   /* SJM 08-03-10 - SV - this is crucial new code that allocates only half */
   /* size for a part for new 2 state variables */
   if (!np->n_stren)
    {
     if (np->srep == SR_BIT2S) wlen = wlen_(np->nwid);
     else wlen = 2*wlen_(np->nwid);
    }
   else
    { 
     wlen = (np->nwid + WRDBYTES - 1)/WRDBYTES;
    }
  }
 return(wlen);
}

/*
 * init timing check last time to 0 and last values
 */
static void init_net_npp_tchk_idpvals(struct net_t *np)
{
 struct net_pin_t *npp;
 struct tchg_t *tchgp;
 struct chktchg_t *chktcp;
 int32 ival, stval;
 word64 *w64p;

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_TCHG) continue; 

   if (np->n_stren) __get_initval(np, &ival);
   else ival = __get_initval(np, &stval);

   switch ((byte) npp->chgsubtyp) {
    case NPCHG_TCSTART: case NPCHG_PTHSRC:
     tchgp = npp->elnpp.etchgp;
     w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
     *w64p = 0ULL;
     __idp[tchgp->oldval_ofs] = ival;
     break;
    case NPCHG_TCCHK:
     chktcp = npp->elnpp.echktchgp;
     /* AIV 10/15/09 - now just check if on list with the flag T/F */
     __idp[chktcp->chkactive_ofs] = FALSE;
     __idp[chktcp->chkoldval_ofs] = ival;
 
     tchgp = chktcp->startchgp;
     w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
     *w64p = 0ULL;
     __idp[tchgp->oldval_ofs] = ival;
     break;
   }
  }
}

/*
 * initialize rt tgl struct which go into idp area - one for each instance
 */
static void init_net_toggle_ofs(struct mod_t *mdp)
{
 int32 wlen, ii, ni, ubits;
 word32 *wp, *seen10wp, *seen01wp;
 word32 mask;
 t_midat *idp;
 struct net_t *np;
 struct rt_tgl_t *togp;
 //int32 *ip;

 /* if module does not have toggle coverage - no offsets to set */
 if (!mdp->m_has_toggle_cover) return; 
     
 /* initialize on for each net/instance */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   if (!np->n_has_toggle) continue;

   /* DBG remove -- */
   if (np->ntgp == NULL || np->ntgp->toggle_ofs == 0) 
     __misc_terr(__FILE__, __LINE__);
   /* --- */ 
 
   /* need to alloc one for each instance */
   wlen = wlen_(np->nwid);
   np->ntgp->n_peri_tgl_on_se_list = (int32 *)
    __my_malloc(sizeof(int32)*mdp->flatinum);
   memset(np->ntgp->n_peri_tgl_on_se_list, 0, sizeof(int32)*mdp->flatinum);
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     /* DBG remove -- */
     if (np->ntgp == NULL) __misc_terr(__FILE__, __LINE__);
     if (np->ntgp->peri_tgl_on == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* add to the toggle list */
     /* if itree loc does not have toggle coverage on - just set to never */
// SJM 08-30-13 - REMOVED AND REMOVE CODE
/* ==== NEED TO RMEOV
     if (np->ntgp->peri_tgl_on[ii] == 0)
      {
       np->ntgp->n_peri_tgl_on_se_list[ii] = TRUE;
       continue; 
      }
==== */
     
     idp = mdp->moditps[ii]->it_idp;
     togp = (struct rt_tgl_t *) __my_malloc(sizeof(struct rt_tgl_t));
     togp->idp = idp;
     togp->tognxt = NULL;
     togp->np = np;
     togp->is_2state = __is_2state_typ(np->ntyp);

     /* SJM 03-26-13 WRITME??? - toggle counts not cover go here */
     //AIV TOGGLE - skipping toggle count for now
     //ip = (int32 *) __my_malloc(np->nwid*INTBYTES);
     //memset(ip, 0, np->nwid*INTBYTES);

     /* vectors to hold the toggle values */
     seen10wp = (word32 *) __my_malloc(wlen*WRDBYTES);
     seen01wp = (word32 *) __my_malloc(wlen*WRDBYTES);
     memset(seen01wp, 0, wlen*WRDBYTES);
     memset(seen10wp, 0, wlen*WRDBYTES);
     if (!np->n_isavec)
      {
       wp = (word32 *) __my_malloc(WRDBYTES);
       /* init scalar values to x and set count to 0 */
       if (togp->is_2state) wp[0] = 0;
       else wp[0] = 3;
      }
     else
      {
       if (togp->is_2state)
        {
         /* 2-state init to 0 so will not count */
         wp = (word32 *) __my_malloc(wlen*WRDBYTES);
         memset(wp, 0, wlen*WRDBYTES);
        }
       else 
        {
         /* 4-state init to x so will not count */
         wp = (word32 *) __my_malloc(2*wlen*WRDBYTES);
         memset(wp, 0xff, 2*wlen*WRDBYTES);
         ubits = ubits_(np->nwid);
         /* need to mask the high part to 0 if not word aligned */
         if (ubits != 0)
          {
           mask = __masktab[ubits];
           wp[wlen-1] &= mask;
           wp[(2*wlen)-1] &= mask;
          }
        }
      }
     //SJM 04-26-13 - AIV TOGGLE - skipping toggle count for now - what ???
     //togp->countp = ip;
     
     togp->last_valp = wp;
     togp->seen10p = seen10wp;
     togp->seen01p = seen01wp;
     idp[np->ntgp->toggle_ofs] = (word32) togp;

     /* SJM 08-30-13 - must still build entire toggle (togp) data structure */
     /* add to the toggle list */
     /* if itree loc does not have toggle coverage on - just set to never */
/* ==== WHY CAN"T PUT BACK???
     if (np->ntgp->peri_tgl_on[ii] == 0)
      {
       np->ntgp->n_peri_tgl_on_se_list[ii] = TRUE;
      }
==== */
    }
  }
}

/*
 * reset all toggle to unknown from $toggle_reset sys task call
 *
 * SJM 06-27-13 - there is a problem with this - reset is to x state
 * (untoggled) so next transition (toggle will be from x and not counted)
 * on second toggle will be counted
 */
extern void __set_all_toggles_off(void)
{
 int32 wlen, ii, ni, ubits;
 word32 mask;
 t_midat *idp;
 struct mod_t *mdp;
 struct net_t *np;
 struct rt_tgl_t *togp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  { 
   /* if module does not have toggle coverage - no offsets to set */
   if (!mdp->m_has_toggle_cover) continue;
     
   /* initialize on for each net/instance */
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
    {
     if (!np->n_has_toggle) continue;

     /* DBG remove -- */
     if (np->ntgp == NULL || np->ntgp->toggle_ofs == 0) 
      __misc_terr(__FILE__, __LINE__);
     /* --- */ 
 
     wlen = wlen_(np->nwid);
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       /* DBG remove -- */
       if (np->ntgp == NULL) __misc_terr(__FILE__, __LINE__);
       if (np->ntgp->peri_tgl_on == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       idp = mdp->moditps[ii]->it_idp;
       togp =  (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];
     
       /* if itree loc does not have toggle coverage on - nothing to reset */
       if (np->ntgp->peri_tgl_on[ii] == 0) continue;

       /* if this inst tgl recorded since setting back to untoggled need */
       /* to undo any permanent toggled on from */ 
       np->ntgp->n_peri_tgl_on_se_list[ii] =  0;

       memset(togp->seen10p, 0, wlen*WRDBYTES);
       memset(togp->seen01p, 0, wlen*WRDBYTES);

       if (!np->n_isavec)
        {
         /* init scalar values to x and set count to 0 */
         if (togp->is_2state) togp->last_valp[0] = 0;
         else togp->last_valp[0] = 3;
        }
       else
        {
         if (togp->is_2state)
          {
           /* 2-state init to 0 so will not count */
           memset(togp->last_valp, 0, wlen*WRDBYTES);
          }
         else 
          {
           /* 4-state init to x so will not count */
           memset(togp->last_valp, 0xff, 2*wlen*WRDBYTES);
           ubits = ubits_(np->nwid);
           /* need to mask the high part to 0 if not word aligned */
           if (ubits != 0)
            {
             mask = __masktab[ubits];
             togp->last_valp[wlen-1] &= mask;
             togp->last_valp[(2*wlen)-1] &= mask;
            }
          }
        }
      }
    }
  }
}

/*
 * set all last valp's to x (0 for 2 state)
 *
 * SJM 07-01-13 - idea is that when tgl recording turned off, must reset
 * all ol values to x, but this has a minor problem still.  Namely, it
 * takes 2 transitions before a toggle is seen.  First one from x then
 * the next one is the 0->1 or 1->0 toggle - maybe will be many more
 * one direction only toggles 
 */
extern void __set_all_tgl_lastvals_tox(void)
{
 int32 wlen, ii, ni, ubits;
 word32 mask;
 t_midat *idp;
 struct mod_t *mdp;
 struct net_t *np;
 struct rt_tgl_t *togp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  { 
   /* if module does not have toggle coverage - no offsets to set */
   if (!mdp->m_has_toggle_cover) continue;
     
   /* initialize on for each net/instance */
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
    {
     if (!np->n_has_toggle) continue;

     /* DBG remove -- */
     if (np->ntgp == NULL || np->ntgp->toggle_ofs == 0) 
      __misc_terr(__FILE__, __LINE__);
     /* --- */ 
 
     wlen = wlen_(np->nwid);
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       /* DBG remove -- */
       if (np->ntgp == NULL) __misc_terr(__FILE__, __LINE__);
       if (np->ntgp->peri_tgl_on == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       idp = mdp->moditps[ii]->it_idp;
       togp =  (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];
     
       /* if itree loc does not have toggle coverage on - nothing to reset */
       if (np->ntgp->peri_tgl_on[ii] == 0) continue;

       /* SJM 07-01-13 - if both already tgled no need to chanl last val */

       /* set the last vals */
       if (!np->n_isavec)
        {
         /* init scalar values to x and set count to 0 */
         if (togp->is_2state) togp->last_valp[0] = 0;
         else togp->last_valp[0] = 3;
        }
       else
        {
         if (togp->is_2state)
          {
           /* 2-state init to 0 so will not count */
           memset(togp->last_valp, 0, wlen*WRDBYTES);
          }
         else 
          {
           /* 4-state init to x so will not count */
           memset(togp->last_valp, 0xff, 2*wlen*WRDBYTES);
           ubits = ubits_(np->nwid);
           /* need to mask the high part to 0 if not word aligned */
           if (ubits != 0)
            {
             mask = __masktab[ubits];
             togp->last_valp[wlen-1] &= mask;
             togp->last_valp[(2*wlen)-1] &= mask;
            }
          }
        }
      }
    }
  }
}

/*
 * initialize storage for a variable in one module
 *
 * BEWARE - this routine needs current (0th inst) __idp to be set
 */
extern void __init_var(struct net_t *np)
{
 int32 srtyp;
 
 /* AIV 11/16/11 - if random init +random use seperate routine */ 
 if (__random_init)
  {
   init_var_random(np);
   return;
  }

 /* need to handle REAL as special case - has special representation */
 /* and now real can be array */
 if (np->ntyp == N_REAL) { init_real_var(np); return; }
 if (np->ntyp == N_STRING) { init_string_var(np); return; }

 if (np->n_isarr)
  {
   /* AIV 08/11/10 - this is SR_ARRAY - so need routine to check for type */
   /* AIV LOOKATME maybe should remove SR_ARRAY can use n_isarr????? */
   srtyp = __get_array_srep_type(np);
   if (srtyp == SR_BIT2S || srtyp == SR_SCAL2S) init_2state_arr_var(np, srtyp);
   else init_arr_var(np);
  }
 else if (!np->n_isavec)
  {
   if (!np->n_stren) init_scal_var(np);
   else init_sscal_var(np);
  }
 else
  {
   if (!np->n_stren)
    {
     if (np->srep == SR_BIT2S) init_vec2s_var(np);
     else init_vec_var(np);
    }
   else init_svec_var(np);
  }
}

/*
 * random initialize storage for a variable in one module
 *
 * just like above except inits to random not x or 0
 * strengths are init the same
 */
static void init_var_random(struct net_t *np)
{
 int32 srtyp;

 if (np->ntyp == N_REAL) { init_real_var_random(np); return; }
 /* AIV 05/09/12 - to init string here as well */
 if (np->ntyp == N_STRING) { init_string_var(np); return; }

 if (np->n_isarr)
  {
   srtyp = __get_array_srep_type(np);
   if (srtyp == SR_BIT2S || srtyp == SR_SCAL2S) 
    {
     init_2state_arr_var_random(np, srtyp);
    }
   else init_arr_var_random(np);
  }
 else if (!np->n_isavec)
  {
   if (!np->n_stren) init_scal_var_random(np);
   else init_sscal_var(np);
  }
 else
  {
   if (!np->n_stren)
    {
     if (np->srep == SR_BIT2S) init_vec2s_var_random(np);
     else init_vec_var_random(np);
    }
   else init_svec_var(np);
  }
}

/*
 * init real random
 */
static void init_real_var_random(struct net_t *np)
{
 int32 arrw;
 double *dp;

 /* case 1: real array */
 if (np->n_isarr)
  {
   arrw = __get_arrwide(np);
   /* reals arrays contiguous a/b 8 bytes with no x/z */
   dp = (double *) &(__idp[np->nva_ofs]);
   init_random((word32 *) dp, 2*arrw*wlen_(np->nwid)*WRDBYTES);
  }
 else
  {
   /* case 2 non array */
   dp = (double *) &(__idp[np->nva_ofs]);
   init_random((word32 *) dp, wlen_(REALBITS)*WRDBYTES);
  }
}
   
/*
 * set a vector to random nbytes
 */
static void init_random(word32 *base_wp, int32 nbytes)
{
 int32 i;
 unsigned int ranv;
 unsigned int *ip;

 ip = (unsigned int *) base_wp;
 for (i = 0; i < nbytes/4; i++)
  {
   ranv = __rtl_dist_uniform(&__init_seed, MY_LONG_MIN, MY_LONG_MAX);
   *ip = ranv;
   ip++;
  }
}

/*
 * random init of array
 */
static void init_arr_var_random(struct net_t *np)
{
 int32 i;
 unsigned int ranv;
 int32 arrw, wlen, blen;
 word32 *wp;
 byte *bp;
 hword *hwp;

 if (np->ntyp < NONWIRE_ST && np->n_isarr) return;

 /* arrw is number of cells in memory */
 arrw = __get_arrwide(np);
 wp = &(__idp[np->nva_ofs]);
 /* case 1, each cell is a scalar */
 if (!np->n_isavec)
  {
   wlen = wlen_(2*arrw);
   /* notice packed densely, index by cell array of 2 bit cells */
   for (i = 0; i < wlen; i++) 
    {
     init_random(&(wp[i]), WRDBYTES);
     /* AIV 05/09/12 - new +random_2state init 4-state to 2-state values */
     /* just turn off x/z bit of the 2-state bit */
     if (__random_init_2state) 
      {
#ifdef __CVC32__
       wp[i] &= 0x55555555;
#else
       wp[i] &= 0x5555555555555555;
#endif
      }
    }
   /* must mask off unused bits in last word32 */
   wp [wlen - 1] &= __masktab[ubits_(2*arrw)];
   return;
  }

 /* case 2: each cell cannot be packed */
 if (np->nwid > WBITS/2)
  {
   /* array is linear array of arrw*insts elements */
   /* each element has 2 elwlen x (1w) regions */
   wlen = wlen_(np->nwid);
   blen = np->nwid; 
   for (i = 0;;) 
    {
     init_random(wp, wlen*WRDBYTES);
     wp[wlen - 1] &= __masktab[ubits_(blen)];
     wp = &(wp[wlen]);
     /* AIV 05/09/12 - new +random_2state init 4-state to 2-state values */
     if (__random_init_2state) 
      {
       memset(wp, 0, wlen*WRDBYTES);
      }
     else
      {
       init_random(wp, wlen*WRDBYTES);
       wp[wlen - 1] &= __masktab[ubits_(blen)];
      }

     if (++i >= arrw) break; 
     wp = &(wp[wlen]);
    }
   return;
  }
 /* case 3a: packs into byte */
 if (np->nwid <= 4)
  {
   /* each cell has 1 byte */
   /* pack into 2 contiguous low bit side sections of byte */
   bp = (byte *) wp;
   for (i = 0; i < arrw; i++) 
    {
     ranv = __rtl_dist_uniform(&__init_seed, MY_LONG_MIN, MY_LONG_MAX);
     /* AIV 05/09/12 - new +random_2state init 4-state to 2-state values */
     if (__random_init_2state) 
      {
       ranv &= 0x0f;
      }
     bp[i] = (byte) ranv;
    }
   return;
  }
 /* case 3b: packs into half word32 */
 if (np->nwid <= 8)
  {
   hwp = (hword *) wp;
   for (i = 0; i < arrw; i++) 
    { 
     ranv = __rtl_dist_uniform(&__init_seed, MY_LONG_MIN, MY_LONG_MAX);
     /* AIV 05/09/12 - new +random_2state init 4-state to 2-state values */
     if (__random_init_2state) 
      {
       ranv &= 0x00ff;
      }
     hwp[i] = (hword) ranv;
    }
   return;
  }
 /* case 3c: pcks in word32 */
 for (i = 0; i < arrw; i++) 
  {
   init_random(&(wp[i]), WRDBYTES);
   /* AIV 05/09/12 - new +random_2state init 4-state to 2-state values */
   if (__random_init_2state) 
    {
     /* AIV 05/09/12 - new +random_2state init 4-state to 2-state values */
     /* just turn off x/z bit of the 2-state bit */
     wp[i] &= 0x0000ffff;
    }
  }
}

/*
 * random init of 2 state array
 */
static void init_2state_arr_var_random(struct net_t *np, int32 srtyp)
{
 int32 i;
 int32 arrw, wlen;
 word32 *wp;

 /* AIV 09/30/09 - wire arrays are converted into regular wire vectors */
 /* however the initial array is still around - no need to init */
 /* AIV LOOKATME - maybe these should be linked out ???? */
 if (np->ntyp < NONWIRE_ST && np->n_isarr) return;

 /* arrw is number of cells in memory */
 arrw = __get_arrwide(np);
 wp = &(__idp[np->nva_ofs]);

 if (srtyp == SR_SCAL2S)
  {
   wlen = wlen_(arrw);
   /* notice packed densely, index by cell array of 2 bit cells */
   /* for 2 state, just all 0's - since b parts really unused */
   for (i = 0; i < wlen; i++) 
    {
     init_random(&(wp[i]), WRDBYTES);
    }
   return;
  }

 wlen = wlen_(np->nwid)*arrw;
 for (i = 0; i < arrw; i++)
  {
   init_random(&(wp[i]), WRDBYTES);
  }
}

/*
 * scalar random init
 */
static void init_scal_var_random(struct net_t *np)
{
 unsigned int ranv;
 word32 *wp;

 /* variables accessed as section of design wide storage table */
 ranv = __rtl_dist_uniform(&__init_seed, MY_LONG_MIN, MY_LONG_MAX);
 wp = &(__idp[np->nva_ofs]);
 /* AIV 05/08/12 - need the mask here was causing core dumps */
 /* AIV 05/09/12 - new +random_2state init 4-state to 2-state values */
 if (__random_init_2state) wp[0] = ranv & 1;
 else wp[0] = ranv & 3;
}

/*
 * init random vector value
 */
static void init_vec_var_random(struct net_t *np)
{
 int32 wlen, nbytes, ubits;
 word32 *wp;

 wlen = wlen_(np->nwid);
 nbytes = 2*WRDBYTES*wlen;
 wp = &(__idp[np->nva_ofs]); 
 /* AIV 05/09/12 - new +random_2state init 4-state to 2-state values */
 if (__random_init_2state)
  {
   init_random(wp, nbytes/2);
   memset(&(wp[wlen]), 0, nbytes/2);
  }
 else init_random(wp, nbytes);
 ubits = ubits_(np->nwid);
 /* 1 insts's vector value, initial a part */
 wp[wlen - 1] &= __masktab[ubits]; 
 wp[2*wlen - 1] &= __masktab[ubits]; 
}

/*
 * init random 2-state vector value
 */
static void init_vec2s_var_random(struct net_t *np)
{
 int32 wlen, nbytes, ubits;
 word32 *wp;

 wlen = wlen_(np->nwid);
 nbytes = WRDBYTES*wlen;
 wp = &(__idp[np->nva_ofs]); 
 init_random(wp, nbytes);
 ubits = ubits_(np->nwid);
 /* 1 insts's vector value, initial a part */
 wp[wlen - 1] &= __masktab[ubits]; 
}

/*
 * return array type since srep type is SR_ARRAY must check ntype for 2state
 * AIV LOOKATME maybe should remove SR_ARRAY can use n_isarr????? 
 */
extern int32 __get_array_srep_type(struct net_t *np)
{
 int32 srtyp;

 /* DBG remove -- */
 if (!np->n_isarr) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 if (np->ntyp == N_STRING) srtyp = SR_STRING;
 else if (np->nwid == 1)
  {
   if (__is_2state_typ(np->ntyp)) srtyp = SR_SCAL2S;
   else srtyp = SR_SCAL;
  }
 else
  {
   if (__is_2state_typ(np->ntyp)) srtyp = SR_BIT2S;
   else srtyp = SR_VEC;
  }
 return(srtyp);
}

/*
 * initialize a real variable
 */
static void init_real_var(struct net_t *np)
{
 int32 arrw;
 double *dp;

 /* case 1: real array */
 if (np->n_isarr)
  {
   arrw = __get_arrwide(np);
   /* reals arrays contiguous a/b 8 bytes with no x/z */
   dp = (double *) &(__idp[np->nva_ofs]);
   /* AIV 09/15/10 - this was wrong for 64-bit need to zero 2* just use */
   /* memset  - LOOKATME - 64-bit only needs one word but 32 is 2x */
   /* so it expects 2x when dealing with reals */ 
   /* wlen = 2*arrw*wlen_(np->nwid); */
   memset(dp, 0, 2*arrw*wlen_(np->nwid)*WRDBYTES);
  }
 else
  {
   /* case 2 non array */
   dp = (double *) &(__idp[np->nva_ofs]);
   *dp = 0.0;
  }
}
 
/*
 * initialize a SV string variable
 *
 * these are stored as follows:
 * __idp[np->nva_ofs] =   cp //the string pointer
 * __idp[np->nva_ofs+1] = cursize //size of currently store string
 * __idp[np->nva_ofs+2] = sizeofcp //size of alloc string
 */
static void init_string_var(struct net_t *np)
{
 int32 arrw, i;
 char *cp;
 t_midat *idp;

 /* if array each elment contains 3 - idp words */
 if (np->n_isarr) 
  {
   arrw = __get_arrwide(np);
   for (i = 0; i < arrw; i++)
    {
     cp = __my_malloc(STR_INIT_CHARS);
     memset(cp, 0, STR_INIT_CHARS);
     idp = &(__idp[np->nva_ofs+(i*STR_IDP_WLEN)]);
     idp[STR_IDP_OFS] = (t_midat) cp; 
     idp[STR_IDP_NDX_OFS] = 0; 
     idp[STR_IDP_SIZE_OFS] = STR_INIT_CHARS; 
    }
   return;
  }

 cp = __my_malloc(STR_INIT_CHARS);
 memset(cp, 0, STR_INIT_CHARS);
 idp = &(__idp[np->nva_ofs]);
 idp[STR_IDP_OFS] = (t_midat) cp; 
 idp[STR_IDP_NDX_OFS] = 0; 
 idp[STR_IDP_SIZE_OFS] = STR_INIT_CHARS; 
}

/*
 * initialize one instance of an array
 *
 * notice for now to access must call get packbits - store somewhere
 * never need to access nva through stu strength union because array cannot
 * have strength 
 *
 * initialization easy since know arrays are registers that are always
 * initialized to x's
 * notice this routine is somewhat dependent on 32 bit words
 */
static void init_arr_var(struct net_t *np)
{
 int32 i;
 int32 arrw, wlen;
 word32 *wp, mask;
 byte *bp;
 hword *hwp;

 /* AIV 09/30/09 - wire arrays are converted into regular wire vectors */
 /* however the initial array is still around - no need to init */
 /* AIV LOOKATME - maybe these should be linked out ???? */
 if (np->ntyp < NONWIRE_ST && np->n_isarr) return;

 /* arrw is number of cells in memory */
 arrw = __get_arrwide(np);
 wp = &(__idp[np->nva_ofs]);
 /* case 1, each cell is a scalar */
 if (!np->n_isavec)
  {
   wlen = wlen_(2*arrw);
   /* notice packed densely, index by cell array of 2 bit cells */
   for (i = 0; i < wlen; i++) wp[i] = ALL1W;
   /* must mask off unused bits in last word32 */
   wp [wlen - 1] &= __masktab[ubits_(2*arrw)];
   return;
  }

 /* case 2: each cell cannot be packed */
 if (np->nwid > WBITS/2)
  {
   /* array is linear array of arrw*insts elements */
   /* each element has 2 elwlen x (1w) regions */
   wlen = wlen_(np->nwid);
   for (i = 0;;) 
    {
     one_allbits_(wp, np->nwid);
     wp = &(wp[wlen]);
     one_allbits_(wp, np->nwid); 
     if (++i >= arrw) break; 
     wp = &(wp[wlen]);
    }
   return;
  }
 /* case 3a: packs into byte */
 if (np->nwid <= 4)
  {
   /* each cell has 1 byte */
   /* pack into 2 contiguous low bit side sections of byte */
   mask = __masktab[2*np->nwid];
   bp = (byte *) wp;
   for (i = 0; i < arrw; i++) bp[i] = (byte) mask;
   return;
  }
 /* case 3b: packs into half word32 */
 if (np->nwid <= 8)
  {
   mask = __masktab[2*np->nwid];
   hwp = (hword *) wp;
   for (i = 0; i < arrw; i++) hwp[i] = (hword) mask;
   return;
  }
 /* case 3c: pcks in word32 */
 mask = __masktab[2*np->nwid];
 for (i = 0; i < arrw; i++) wp[i] = mask;
}

/*
 * initialize one instance of a 2 state array
 */
static void init_2state_arr_var(struct net_t *np, int32 srtyp)
{
 int32 i;
 int32 arrw, wlen;
 word32 *wp;

 /* AIV 09/30/09 - wire arrays are converted into regular wire vectors */
 /* however the initial array is still around - no need to init */
 /* AIV LOOKATME - maybe these should be linked out ???? */
 if (np->ntyp < NONWIRE_ST && np->n_isarr) return;

 /* arrw is number of cells in memory */
 arrw = __get_arrwide(np);
 wp = &(__idp[np->nva_ofs]);

 if (srtyp == SR_SCAL2S)
  {
   wlen = wlen_(arrw);
   /* notice packed densely, index by cell array of 2 bit cells */
   /* for 2 state, just all 0's - since b parts really unused */
   for (i = 0; i < wlen; i++) wp[i] = 0;
   return;
  }

 wlen = wlen_(np->nwid)*arrw;
 for (i = 0; i < arrw; i++) wp[i] = 0;
}

/*
 * initialize one scalar var
 *
 * since aligned on word boundary make high bits 0x55 (or 0xaa) to debug
 * if needed
 */
static void init_scal_var(struct net_t *np)
{
 word32 *wp;
 int32 ival, stval;

 /* variables accessed as section of design wide storage table */
 ival = __get_initval(np, &stval);
 wp = &(__idp[np->nva_ofs]);
 wp[0] = ival;
}

/*
 * determine the initial value and strength for any wire type
 * stval is entire 8 bit value - ival returned is low 2 bits only
 * strength format is (st0 (7-5), st1 (4-2), val (1-0) 
 */
extern int32 __get_initval(struct net_t *np, int32 *stval)
{
 int32 ival, sval;


 switch ((byte) np->ntyp) { 
  case N_TRI: case N_TRIAND: case N_WA: case N_TRIOR: case N_WO:
  case N_WIRE: 
   /* normal wires are z (hiz(0),hiz(0), z) */
   /* SJM 02/16/07 - initialize to x if net has drivers otherwise z */

   /* SJM 03/16/07 - if wire is an inout special case - may have npp bid */
   /* mod port drvrs here, but since inout are in tran channels removed */
   /* later - if all drivers are bid ports, really has no drivers */
   if (np->ndrvs == NULL || all_drvrs_bidirect(np))
    {
     ival = 2; 
     sval = ST_HIZ;
    }
   else
    {
     ival = 3; 
     sval = 0xdb;
    }
   break;
  /* these are normal wires, that have pull0 or pull driver added */  
  case N_TRI0: ival = 0; sval = ST_PULL0; break; /* <5:5>=0 Pu0 10110100 */
  case N_TRI1: ival = 1; sval = ST_PULL1; break; /* <5:5>=1 pu1 10110101 */
  case N_TRIREG:
   /* even if delay do not schedule decay to z at initialize */
   ival = 3; 
   if (np->n_capsiz == CAP_LARGE) sval = 0x93; /* <4:4>=x LaX 10010011 */
   else if (np->n_capsiz == CAP_SMALL) sval = 0x27; /* <1:1>=x SmX 00100111 */
   else sval = 0x4b; /* <2:2>=x MeX 01001011 */
   break;
  /* <7:7>=1 Su1 ll111101 */
  case N_SUPPLY1: ival = 1; sval = ST_SUPPLY1; break;
 /* <7:7>=0 Su0 11111100 */
  case N_SUPPLY0: ival = 0; sval = ST_SUPPLY0; break;
  case N_REG: case N_LOGIC: 
   ival = 3; sval = 0xdb; /* strength meaningless but <6:6>=X Stx 11011011 */
   break;
  case N_BIT:
   ival = 0; sval = 0xdb; /* strength meaningless but <6:6>=X Stx 11011011 */
   break;
  case N_INT:
   ival = 3; sval = 0xdb; /* strength meaningless but <6:6>=X Stx 11011011 */
   break;
  case N_TIME:
   ival = 3; sval = 0xdb; /* strength meaningless but <6:6>=X Stx 11011011 */
   break;
 case N_CINT:
   ival = 0; sval = 0xdb; /* strength meaningless but <6:6>=X Stx 11011011 */
   break;
  case N_EVENT:
   ival = 3; sval = 0xdb; /* strength meaningless but <6:6>=X Stx 11011011 */
   break;
  /* SV the 2 state cases */
  case N_BYTE: case N_SHORTCINT: case N_LONGCINT: case N_CHANDLE:
   ival = 0; sval = 0xdb; /* strength meaningless but <6:6>=X Stx 11011011 */
   break;
  default: __case_terr(__FILE__, __LINE__); return(0);
 } 
 /* AIV 08/25/10 - if running two state with wires init to zero */
 if (__is_2state_typ(np->ntyp))
  {
   ival = 0;
  }
 *stval = sval;
 return(ival); 
}

/*
 * return T if all drivers are bid mdprt drivers because they are all 
 * removed later when inout are converted to switch channels
 */
static int32 all_drvrs_bidirect(struct net_t *np)
{
 struct net_pin_t *npp;  

 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_BIDMDPRT && npp->npntyp != NP_BIDICONN)
    return(FALSE);
  }
 return(TRUE);
}

/*
 * allocate all instances for a strength scalar var
 * 1 byte per value (low 2 bits value), next 3 bits 1 stren, high 3 0 stren 
 */
static void init_sscal_var(struct net_t *np)
{
 word32 *wp;
 int32 stval;

 __get_initval(np, &stval);
 wp = &(__idp[np->nva_ofs]);
 /* stval is the 8 bit combination of stren and value (low 2 bits) */
 wp[0] = stval;
}

/*
 * initialize one instance of vector variable (net)
 */
static void init_vec_var(struct net_t *np)
{
 int32 ival, stval, wlen, totchars, ubits, wi;
 word32 *wp, *iwp;
 word32 maska, maskb;

 /* calculate sizes and initial mask patterns */
 ival = __get_initval(np, &stval);
 maska = maskb = 0L;
 /* SJM 07/15/00 - no longer pack <16 bit vecs - still pack scalar in byte */ 
 wlen = wlen_(np->nwid);
 totchars = 2*WRDBYTES*wlen;
 wp = &(__idp[np->nva_ofs]); 
 switch ((byte) ival) {
  case 0: memset(wp, 0, totchars); return;
  case 1: maska = ALL1W; break;
  case 2: maskb = ALL1W; break;
  case 3: maska = ALL1W; maskb = ALL1W; break;
  default: __case_terr(__FILE__, __LINE__);
 }

 if (np->nwid <= WBITS)
  {
   maska &= __masktab[np->nwid];
   maskb &= __masktab[np->nwid];
   wp[0] = maska;
   wp[1] = maskb;
   return;
  }
 ubits = ubits_(np->nwid);
 iwp = wp;
 /* 1 insts's vector value, initial a part */
 for (wi = 0; wi < wlen; wi++) iwp[wi] = maska;
 iwp[wlen - 1] &= __masktab[ubits]; 

 /* then b part */
 for (wi = wlen; wi < 2*wlen; wi++) iwp[wi] = maskb;
 iwp[2*wlen - 1] &= __masktab[ubits]; 
}

/*
 * initialize one instance of a 2 state vector variable (net)
 *
 * SJM 08-09-10 - simple just no b part
 */
static void init_vec2s_var(struct net_t *np)
{
 int32 ival, stval, wlen, totchars, ubits, wi;
 word32 *wp, *iwp;
 word32 maska;

 /* calculate sizes and initial mask patterns */
 ival = __get_initval(np, &stval);
 maska = 0L;
 /* SJM 07/15/00 - no longer pack <16 bit vecs - still pack scalar in byte */ 
 wlen = wlen_(np->nwid);

 totchars = WRDBYTES*wlen;
 wp = &(__idp[np->nva_ofs]); 
 switch ((byte) ival) {
  case 0: memset(wp, 0, totchars); return;
  case 1: maska = ALL1W; break;
  default: __case_terr(__FILE__, __LINE__);
 }

 if (np->nwid <= WBITS)
  {
   maska &= __masktab[np->nwid];
   wp[0] = maska;
   return;
  }
 ubits = ubits_(np->nwid);
 iwp = wp;
 /* 1 insts's vector value, initial a part */
 for (wi = 0; wi < wlen; wi++) iwp[wi] = maska;
 iwp[wlen - 1] &= __masktab[ubits]; 
}

/*
 * initialize one insts svec - know aligned on word boundary
 */
static void init_svec_var(struct net_t *np)
{
 byte *bp;
 int32 stval;
 byte sval;

 bp = (byte *) &(__idp[np->nva_ofs]);
 __get_initval(np, &stval);
 sval = (byte) stval;
 set_byteval_((char *) bp, np->nwid, sval);
}

/*
 * set all dce expr offsets for one net 
 * AIV 01/26/12 - this was sometimes wrong for XMR dce_exprs
 * it would even just silently work - and mash idp areas which is the worst
 * sine they are difficult to debug.  The dce_expr MUST use the idp area
 * for module it is in, which may not be the one the net is in.  Now building
 * a list for XMR dce's with exprs mdp->dcep_lst_xmrp to work off of.
 */
static void set_net_dce_expr_ofs(struct net_t *np, struct mod_t *mdp)
{
 struct dcevnt_t *dcep; 
 struct dceauxlst_t *dlp, *dlp2;
 struct mod_t *ref_mdp;
 struct itree_t *itp;
 struct gref_t *grp;

 for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
  {
   if (__dce_needs_prevval(dcep, mdp))
    {
     dcep->prevval_ofs = __nxt_ofs;
     __nxt_ofs += __get_dce_prevval_wsiz(dcep, np);
    }
   if (dcep->dce_expr != NULL)
    {
     /* AIV 01/26/12 - now if XMR will set below */
     if (dcep->dce_xmrtyp != XNP_LOC)
      {
       if (dcep->dce_xmrtyp == XNP_RTXMR)
        {
         itp = dcep->dce_refu.itp;
         ref_mdp = itp->itip->imsym->el.emdp;
        }
       else
        {
         grp = dcep->dceu.dcegrp;
         ref_mdp = grp->gin_mdp;
        }
      }
     else ref_mdp = mdp;


     /* AIV 12/13/07 - dce_expr can share expression - so this can already */
     /* be set */
     if (ref_mdp == mdp && dcep->dce_expr->expr_ofs == 0) 
      {
       dcep->dce_expr->expr_ofs = __nxt_ofs;
       __nxt_ofs++;
      }
    }
  }

 /* now might have dce_expr built XMR list */
 if (mdp->dcep_lst_xmrp != NULL)
  {
   for (dlp = mdp->dcep_lst_xmrp; dlp != NULL; dlp = dlp2)
    {
     dlp2 = dlp->dclnxt;
     dcep = dlp->ldcep;
     /* must be expr and double check that is in this mod */
     /* DBG remove */
     if (dcep->dce_expr == NULL) __misc_terr(__FILE__, __LINE__);
     if (dcep->dce_xmrtyp != XNP_LOC)
      {
       if (dcep->dce_xmrtyp == XNP_RTXMR)
        {
         itp = dcep->dce_refu.itp;
         ref_mdp = itp->itip->imsym->el.emdp;
        }
       else
        {
         grp = dcep->dceu.dcegrp;
         ref_mdp = grp->gin_mdp;
        }
      }
     else ref_mdp = mdp;
     if (ref_mdp != mdp)__misc_terr(__FILE__, __LINE__);
     /* -------------------------------------------- */

 
     /* AIV 12/13/07 - dce_expr can share expression - so this can already */
     /* be set */
     if (dcep->dce_expr->expr_ofs == 0)
      {
       dcep->dce_expr->expr_ofs = __nxt_ofs;
       __nxt_ofs++;
      }
     /* no longer need it - free it */
     __my_free(dlp, sizeof(struct dceauxlst_t));
    }
   mdp->dcep_lst_xmrp = NULL;
  }
}

/*
 * set offset for net's timing checks
 */
static void set_net_npp_tchk_ofs(struct net_t *np)
{
 int32 nwrds;
 struct net_pin_t *npp;
 struct tchg_t *tchgp;
 struct chktchg_t *chktcp;

 /* AIV 08/04/09 - num words for adding to store time - is only one for */
 /* 64 - bits */
#ifdef __CVC32__
 nwrds = 2;
#else
 nwrds = 1;
#endif

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_TCHG) continue; 

   switch ((byte) npp->chgsubtyp) {
    case NPCHG_TCSTART: case NPCHG_PTHSRC:
     tchgp = npp->elnpp.etchgp;
     
     tchgp->lastchg_ofs = __nxt_ofs;
     /* need to add two words for 64-bit time */
     __nxt_ofs += nwrds;
     /* one word for old value */
     tchgp->oldval_ofs = __nxt_ofs;
     __nxt_ofs++;
     break;
    case NPCHG_TCCHK:
     chktcp = npp->elnpp.echktchgp;
     /* AIV 10/15/09 - now just check if on list with the flag T/F */
     /* always one word */
     chktcp->chkactive_ofs = __nxt_ofs;
     __nxt_ofs += 1;
     /* one word for old value */
     chktcp->chkoldval_ofs = __nxt_ofs;
     __nxt_ofs++;
 
     tchgp = chktcp->startchgp;
     tchgp->lastchg_ofs = __nxt_ofs;
     /* need to add two words for 64-bit time */
     __nxt_ofs += nwrds;
     /* one word for old value */
     tchgp->oldval_ofs = __nxt_ofs;
     __nxt_ofs++;
     break;
   }
  }
}

/*
 * set idp offset for toggle struct
 */
static void set_net_toggle_ofs(struct net_t *np)
{

 /* if net does not toggle - do not set offset */
 if (!np->n_has_toggle) return;

 /* SJM 02-16-13 - must make sure if tgl cover bit on has d.s */ 
 /* DBG remove -- */
 if (np->ntgp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */

 /* need to turn chg store bit on */
 np->ntgp->toggle_ofs = __nxt_ofs;
 __nxt_ofs++;
}

/*
 * get size of dce prev val fields in words
 */
extern int32 __get_dce_prevval_wsiz(struct dcevnt_t *dcep, struct net_t *np)
{ 
 int32 add_wrds, dcewid;

 dcewid = __get_dcewid(dcep, np);
 if (np->n_stren) add_wrds = (dcewid + 3)/4; 
 else
  {
   if (dcewid == 1) add_wrds = 1; else add_wrds = 2*wlen_(dcewid);
  }
 return(add_wrds);
}

/*
 * initialize all continous assigns for one instance
 */
static void init_contas_idp_area(struct mod_t *mdp)
{
 int32 cai, bi;
 word32 *wp;
 struct conta_t *cap, *pbcap;

 for (cai = 0, cap = &(mdp->mcas[0]); cai < mdp->mcanum; cai++, cap++)
  {
   if (!cap->ca_pb_sim)
    {
     if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
      { 
       wp = &(__idp[cap->ca_drv_ofs]); 
       init_one_inst_conta_drv(wp, cap->lhsx->szu.xclen);
      }
     if (cap->ca_delrep != DT_NONE)
      {
       wp = &(__idp[cap->schd_drv_ofs]); 
       init_one_inst_conta_drv(wp, cap->lhsx->szu.xclen);
       /* AIV 10/24/07 - compiler no longer storing tevp - using fixed events */
       if (!__compiled_sim) __idp[cap->caschd_tevs_ofs] = (t_midat) NULL;
      }
    }
   else
    { 
     /* AIV 08/15/07 - must do the original cap itself as well */
//AIV FIXME - don't think this pbit is needed?????
     if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
      { 
       wp = &(__idp[cap->ca_drv_ofs]); 
       init_one_inst_conta_drv(wp, cap->lhsx->szu.xclen);
      }
     if (cap->ca_delrep != DT_NONE)
      {
       wp = &(__idp[cap->schd_drv_ofs]); 
       init_one_inst_conta_drv(wp, cap->lhsx->szu.xclen);
       /* AIV 10/24/07 - compiler no longer storing tevp - using fixed events */
       if (!__compiled_sim) __idp[cap->caschd_tevs_ofs] = (t_midat) NULL;
      }
     for (bi = 0; bi < cap->lhsx->szu.xclen; bi++) 
      {
       pbcap = &(cap->pbcau.pbcaps[bi]);
       if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
        {
         wp = &(__idp[pbcap->ca_drv_ofs]); 
         init_one_inst_conta_drv(wp, pbcap->lhsx->szu.xclen);
        }
       if (cap->ca_delrep != DT_NONE)
        {
         wp = &(__idp[pbcap->schd_drv_ofs]); 
         init_one_inst_conta_drv(wp, pbcap->lhsx->szu.xclen);
         /* AIV 10/24/07 - compiler no longer storing tevp - use fixed events */
         if (!__compiled_sim) __idp[pbcap->caschd_tevs_ofs] = (t_midat) NULL;
        }
      }
    }
  }
}

   
/*
 * intialize all a modules conta driver values
 */
extern void __reinit_all_contas_in_mod(struct mod_t *mdp)
{
 int32 cai, bi;
 struct conta_t *cap, *pbcap;

 for (cai = 0, cap = &(mdp->mcas[0]); cai < mdp->mcanum; cai++, cap++)
  {
   if (!cap->ca_pb_sim)
    {
     if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
      { 
       __init_all_inst_conta_drv(cap->ca_drv_ofs, cap->lhsx->szu.xclen, mdp);
      }
     if (cap->ca_delrep != DT_NONE)
      {
       __init_all_inst_conta_drv(cap->schd_drv_ofs, cap->lhsx->szu.xclen, mdp);
      }
    }
   else
    { 
     for (bi = 0; bi < cap->lhsx->szu.xclen; bi++) 
      {
       pbcap = &(cap->pbcau.pbcaps[bi]);
       if (cap->lhsx->x_multfi || cap->ca_delrep != DT_NONE)
        __init_all_inst_conta_drv(pbcap->ca_drv_ofs, 1, mdp);
       if (cap->ca_delrep != DT_NONE)
        {
         __init_all_inst_conta_drv(cap->schd_drv_ofs, 1, mdp);
        }
      }
    }
  }
}

/*
 * initialize one conta driver value for all instances in the module
 */
extern void __init_all_inst_conta_drv(int32 cap_ofs, int32 blen, 
 struct mod_t *mdp)
{
 int32 ii;
 word32 *wp;
 t_midat *idp;
 
 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   idp = mdp->moditps[ii]->it_idp;
   wp = &(idp[cap_ofs]);
   init_one_inst_conta_drv(wp, blen);
  }
}

/*
 * init one conta driver
 */
static void init_one_inst_conta_drv(word32 *wp, int32 blen)
{
 int32 nbytes;

 /* AIV LOOKATME - old init code was using init of 2 for this case */
 /* think this isn't needed any more at least not for the compiler */
 /*
 if (blen == 1)
  {
   wp[0] = 2;
  }
 */
 nbytes = 2*WRDBYTES*wlen_(blen); 
 memset(wp, 0xff, nbytes);
}
   
/* SJM 12/16/99 - notices packing only into words does not change this */
/* mask table for <= 16 bit wide pck elements (1,z,x) - 0 just all 0's */
/* 0 width impossible and never used for scalar */ 
/* SJM 07/15/00- only for gates since variables no longer packed */
word32 __pack_imaskx[17] = {
 0L, 0x3L, 0xfL, 0x3fL, 0xffL, 0x03ff, 0x0fffL, 0x3fffL, 0xffffL,
 0x3ffffL, 0xfffffL, 0x3fffffL, 0xffffffL, 0x3ffffffL, 0xfffffffL,
 0x3fffffffL, ALL1W
};

/* what is this value of 16 bit should 1 not 8 1's ? */
word32 __pack_imask1[17] = {
 0L, 0x1L, 0x3L, 0x07L, 0x0fL, 0x001fL, 0x003fL, 0x007fL, 0x00ffL,
 0x01ffL, 0x03ffL, 0x07ffL, 0x0fffL, 0x1fffL, 0x03fffL, 0x7fffL, 0xffffL
};

word32 __pack_imaskz[17] = {
 0L, 0x2L, 0xcL, 0x38L, 0xf0L, 0x03e0L, 0x0fc0L ,0x3f80L, 0xff00L,
 0x3fe00L, 0xffc00L, 0x3ff800L, 0xfff000L, 0x3ffe000L, 0xfffc000L,
 0x3fff8000L, 0xffff0000L
};

/*
 * initialize gate idp area for first inst
 */
static void init_gate_idp_area(struct mod_t *mdp)
{
 int32 gi;
 struct gate_t *gp;

 for (gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);
   if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN) continue;
   if (gp->g_class == GC_UDP) init_one_inst_udp_state(gp);
   else init_one_inst_gate_state(gp);
   /* event tevpi storage area */
//AIV FIXME - memory leak for sdf????????
   /* AIV 08/16/07 - if have any sdf must alloc in event because */
   /* AIV 10/22/07 - compiler now uses static events no need to save event */
   /* wide and tran channels still use wrappers */
   if (__compiled_sim && gp->g_class != GC_TRAN && gp->g_class != GC_TRANIF) 
     {
      continue;
     }
   /* AIV LOOKATME - don't think sdf checking is still needed here */
   /* sdf could need events from rt eval for sdf file */
   if (gp->g_delrep != DT_NONE || (__sdflst != NULL || __has_sdfann_calls))
    {
     __idp[gp->schd_tevs_ofs] = (t_midat) NULL;
    }
  }
}

/*
 * init one instance gate value
 * set one and the rest are set from memcpy of idp
 */
static void init_one_inst_gate_state(struct gate_t *gp)
{
 int32 pnum, wlen;
 word32 maska;

 switch ((byte) gp->g_class) {
  case GC_LOGIC:
   pnum = gp->gpnum;
   if (pnum > 16)
    {
     wlen = 2*wlen_(pnum);
     memset(&(__idp[gp->gstate_ofs]), 0xff, wlen*WRDBYTES); 
     break;
    }
   else 
    {
     /* must init output gate value to x */
//AIV FIXME - currently only for compiled sim
     if (__compiled_sim) __idp[gp->gate_out_ofs] = 3;
    }
   /* case 1, fits in 8 bits */
   maska = __pack_imaskx[pnum];
   __idp[gp->gstate_ofs] = maska;
   break;
  case GC_BUFIF:
   /* this starts by driving given strength x (if no expl. <st1:st0>= x) */
   __idp[gp->gstate_ofs] = (t_midat) (0x3f | (gp->g_stval << 6));
    /* must init output gate value to x */
//AIV FIXME - currently only for compiled sim
   if (__compiled_sim) __idp[gp->gate_out_ofs] = 3;
   break;
  case GC_MOS:
   /* pattern here in highz in, control x, and high z out */
   __idp[gp->gstate_ofs] = 0x00020302L;
//AIV FIXME - currently only for compiled sim
   if (__compiled_sim) __idp[gp->gate_out_ofs] = 3;
   break;
  case GC_CMOS:
   /* pattern here in highz in, controls both x, and high z out */
   __idp[gp->gstate_ofs] = 0x02030302L;
//AIV FIXME - currently only for compiled sim
   if (__compiled_sim) __idp[gp->gate_out_ofs] = 3;
   return;
  case GC_TRANIF:
   __idp[gp->gstate_ofs] = ALL1W;
   return;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * init one instance udp
 */
static void init_one_inst_udp_state(struct gate_t *gp)
{
 word32 *wp;
 int32 nins;
 word32 iwval, indval;
 struct udp_t *udpp;

 udpp = gp->gmsym->el.eudpp;
 /* notice nins is total number of input pins: (state not included) */
 nins = udpp->numins;
 /* assume initial value x - notice inputs plus 1 output no pending  */
 iwval = __masktab[2*nins + 2];
 /* initialize to x here - if initial value assign instead of normal eval */ 
 if (udpp->u_wide)
  {
   /* 2 words for each superposition form udp */
   wp = &(__idp[gp->gstate_ofs]);
   wp[0] = iwval;
   indval = cmp_udpind(iwval, udpp->numstates);
   wp[1] = indval;
   /* --- RELEASE remove 
   if (__debug_flg)
    __dbg_msg("++ wide udp init (inst %d): w0=%lx, w1=%lx\n",
     gsi, wp[0], wp[1]);
   --- */
  }
 else
  {
   /* also store signature form udp in half word32 - 2 bit udp pointless */
   __idp[gp->gstate_ofs] = iwval;
   /* -- RELEASE remove
   if (__debug_flg)
    __dbg_msg("-- narrow udp init: initial state h=%x\n", (hword) iwval); 
   -- */
  }
 if (__compiled_sim) __idp[gp->gate_out_ofs] = 3;
}


/*
 * set initial state for builtin gate
 * 
 * LOOKATME - SJM 12/19/99 maybe should also only pck into word32 here but
 * wastes lotsof storage for 4 state gates
 */
extern void __init_all_inst_gate_state(struct gate_t *gp, struct mod_t *mdp)
{
 int32 i;
 int32 pnum, wlen;
 word32 maska;
 t_midat *idp;

 switch ((byte) gp->g_class) {
  case GC_LOGIC:
   pnum = gp->gpnum;
   if (pnum > 16)
    {
     wlen = 2*wlen_(pnum);
     for (i = 0; i < mdp->flatinum; i++)
      {
       idp = mdp->moditps[i]->it_idp;
       memset(&(idp[gp->gstate_ofs]), 0xff, wlen*WRDBYTES); 
      }
     break;
    }
   
   /* case 1, fits in 8 bits */
   maska = __pack_imaskx[pnum];
   for (i = 0; i < mdp->flatinum; i++)
    {
     idp = mdp->moditps[i]->it_idp;
     idp[gp->gstate_ofs] = maska;
     /* must init output gate value to x */
//AIV FIXME - currently only for compiled sim
     if (__compiled_sim) idp[gp->gate_out_ofs] = 3;
    }
   break;
  case GC_BUFIF:
   /* this starts by driving given strength x (if no expl. <st1:st0>= x) */
   for (i = 0; i < mdp->flatinum; i++)
    {
     idp = mdp->moditps[i]->it_idp;
     idp[gp->gstate_ofs] = (t_midat) (0x3f | (gp->g_stval << 6));
     if (__compiled_sim) idp[gp->gate_out_ofs] = 3;
    }
   break;
  case GC_MOS:
   /* pattern here in highz in, control x, and high z out */
   for (i = 0; i < mdp->flatinum; i++)
    {
     idp = mdp->moditps[i]->it_idp;
     idp[gp->gstate_ofs] = 0x00020302L;
//AIV FIXME - currently only for compiled sim
     if (__compiled_sim) __idp[gp->gate_out_ofs] = 3;
    }
   break;
  case GC_CMOS:
   /* pattern here in highz in, controls both x, and high z out */
   for (i = 0; i < mdp->flatinum; i++)
    {
     idp = mdp->moditps[i]->it_idp;
     idp[gp->gstate_ofs] = 0x02030302L;
//AIV FIXME - currently only for compiled sim
     if (__compiled_sim) idp[gp->gate_out_ofs] = 3;
    }
   return;
  case GC_TRANIF:
   for (i = 0; i < mdp->flatinum; i++)
    {
     idp = mdp->moditps[i]->it_idp;
     idp[gp->gstate_ofs] = ALL1W;
    }
   return;
  default: __case_terr(__FILE__, __LINE__);
 }
}

extern const word32 __pow3tab[];

/*
 * set initial state for udp
 * for udps >6 also need 1 word32 per inst. for current table index value
 *
 * notice value is stored as x (3) - but indexing uses 2 for nins > 6
 * conversions from normal 4 value to 3 value made when indexing
 *
 * ustate values are stored as n 2 bit scalars not separate a and b parts
 * since no need for reduction word32 evaluation operations
 */
extern void __init_all_inst_udp_state(struct gate_t *gp, struct mod_t *mdp)
{
 word32 *wp;
 int32 nins, i;
 word32 iwval, indval;
 struct udp_t *udpp;
 t_midat *idp;

 udpp = gp->gmsym->el.eudpp;
 /* notice nins is total number of input pins: (state not included) */
 nins = udpp->numins;
 /* assume initial value x - notice inputs plus 1 output no pending  */
 iwval = __masktab[2*nins + 2];
 /* initialize to x here - if initial value assign instead of normal eval */ 
 if (udpp->u_wide)
  {
   /* 2 words for each superposition form udp */
   for (i = 0; i < mdp->flatinum; i++)
    {
     idp = mdp->moditps[i]->it_idp;
     if (__compiled_sim) idp[gp->gate_out_ofs] = 3;
     wp = &(idp[gp->gstate_ofs]);
     wp[0] = iwval;
     indval = cmp_udpind(iwval, udpp->numstates);
     wp[1] = indval;
     /* --- RELEASE remove 
     if (__debug_flg)
      __dbg_msg("++ wide udp init (inst %d): w0=%lx, w1=%lx\n",
       gsi, wp[0], wp[1]);
     --- */
    }
  }
 else
  {
   /* also store signature form udp in half word32 - 2 bit udp pointless */
   for (i = 0; i < mdp->flatinum; i++)
    {
     idp = mdp->moditps[i]->it_idp;
     idp[gp->gstate_ofs] = iwval;
     if (__compiled_sim) idp[gp->gate_out_ofs] = 3;
    }
   /* -- RELEASE remove
   if (__debug_flg)
    __dbg_msg("-- narrow udp init: initial state h=%x\n", (hword) iwval); 
   -- */
  }
}

/*
 * eval input state (including possible previous state) to get table index
 * for initialization only since normally must use transition to select tab
 *
 * assuming here that 30 bit and 2 bit shifts take same time
 */
static word32 cmp_udpind(word32 ustate, word32 nstates)
{
 word32 ui;

 word32 ind;
 word32 ival;

 /* know ustate has proper initialized state */
 /* notice here need to use state that may have been initialized */ 
 for (ind = 0, ui = 0; ui < nstates; ui++)
  {
   ival = (ustate >> ui) & 3L; 
   /* input x converted to udp x (2) to index - z is x and left as is */
   if (ival == 3) ival = 2;
   ind += ival*__pow3tab[ui];
  } 
 return(ind);
}


/*
 * VARIOUS INITIALIZATION ROUTINES
 */

/*
 * routine to re-initialize variables for 1 module
 *
 * this just reinits wire/reg value - after dces reinited sets chg action bits
 */
extern void __reinitialize_vars(struct mod_t *mdp)
{
 int32 ni, ii;
 struct net_t *np;
 struct task_t *tskp;
 word32 *new_idp;

 __idp = mdp->mod_idata;
 if (mdp->mnnum == 0) goto do_tasks; 
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   /* if any instances any bits in tran channel, need to re-init */
   /* all hard drivers */ 
   if (np->ntraux != NULL)
    {
     if (np->n_stren)
      __allocinit_stperival(&np->ntraux->trnva, mdp->flatinum, np, FALSE);
     else
      __allocinit_perival(&np->ntraux->trnva, mdp->flatinum, np->nwid, FALSE);
    }
   /* need all changed even for event */
   if (np->ntyp == N_EVENT) continue;
   reinit_1wirereg(np, mdp);
  }

do_tasks:
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt) 
  {
   if (tskp->trnum == 0) continue;
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     if (np->ntyp == N_EVENT) continue;
     reinit_1wirereg(np, mdp);
    }
  }
 /* SJM 06-18-07 now only first inst vars reinitialized - must copy */
 /* template into all other instances */
 for (ii = 1; ii < mdp->flatinum; ii++)
  {
   new_idp = &(mdp->mod_idata[ii*mdp->mod_idata_siz]);
   memcpy(new_idp, __idp, WRDBYTES*mdp->mod_idata_siz);
  }
}

/*
 * reinitialize 1 wire or reg
 */
static void reinit_1wirereg(struct net_t *np, struct mod_t *mdp)
{
 int32 i;
 struct qcval_t *qcvalp;
 struct tev_t **itevp;

 /* initialize per bit per inst scheduled event tab if needed */
 if (np->nrngrep == NX_DWIR)
  {
   itevp = np->nu.rngdwir->wschd_pbtevs;
   for (i = 0; i < mdp->flatinum*np->nwid; i++) itevp[i] = NULL;
  }
 if (np->frc_assgn_allocated)
  {
   if (np->ntyp >= NONWIRE_ST)
    {
     qcvalp = np->nu2.qcval;
     /* reset all force/assigns to off and turn off any dces for active */
     for (i = 0; i < 2*mdp->flatinum; i++, qcvalp++)
      {
       qcvalp = &(np->nu2.qcval[i]);
       if (qcvalp->qc_active)
        { 
         /* turn off dces then empty fields by re-initializing record */
         if (qcvalp->qcdcep != NULL) __dcelst_off(qcvalp->qcdcep); 
         init_qcval(qcvalp); 
        }
       else if (qcvalp->qc_overridden)
        {
         /* here fields filled so need to re-init but dces off */
         init_qcval(qcvalp); 
        }
      }
    }
   else
    {
     /* reset all force/assigns on to off and reinit - no assign of wire */
     /* forces per bit */
     for (i = 0; i < np->nwid*mdp->flatinum; i++, qcvalp++)
      {
       qcvalp = &(np->nu2.qcval[i]);
       if (qcvalp->qc_active)
        { 
         if (qcvalp->qcdcep != NULL) __dcelst_off(qcvalp->qcdcep); 
         init_qcval(qcvalp); 
        }
      }
    }
  }
 /* reinitialize any pending vpi_put_value records */
 /* leave the record but change driver to nil and cancel any scheduled tevs */ 
 if (np->ntyp < NONWIRE_ST)
  { 
   if (np->vpi_ndrvs != NULL) __reinit_netdrvr_putvrec(np, mdp);
   if (np->regwir_putv_tedlst != NULL)
    __reinit_regwir_putvrec(np, mdp->flatinum);
  }
 else 
  {
   if (np->regwir_putv_tedlst != NULL)
    __reinit_regwir_putvrec(np, mdp->flatinum);
  }

 /* 06-18-07 since now allocating and initializing seperately, can just */
 /* use the before sim start init var (net) routine */
 __init_var(np);
}

/*
 * initialize all dces (and tchk old vals) in design
 */
extern void __initialize_dsgn_dces(void)
{
 struct mod_t *mdp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   __initialize_dces(__inst_mod);
   __pop_wrkitstk();
  }
}

/*
 * routine to re-initialize dces (and tchk npp old vals) for 1 module
 *
 * do not need to (re)initialize npps except path and timing check which have
 * internal state - normal npp's need processing on any kind of change
 */
extern void __initialize_dces(struct mod_t *mdp)
{
 int32 i, ni;
 struct net_t *np;
 struct net_pin_t *npp;
 int32 insts, ival, stval;
 word64 tim0;
 word64 *w64p;
 struct tchg_t *tchgp;
 struct chktchg_t *chktcp;
 struct task_t *tskp;
 t_midat *idp;

 insts = mdp->flatinum;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   if (np->ntyp == N_EVENT) goto skip_spec;

   /* reinitialize timing check state values - only accessible thru npps */
   /* if no specify section do not need to go through npp loads list */
   if (mdp->mspfy != NULL)
    {
     tim0 = 0ULL;
     for (npp = np->nlds; npp != NULL; npp = npp->npnxt) 
      {
       if (npp->npntyp != NP_TCHG) continue; 

       if (np->n_stren) __get_initval(np, &ival);
       else ival = __get_initval(np, &stval);

       switch ((byte) npp->chgsubtyp) {
        case NPCHG_TCSTART: case NPCHG_PTHSRC:
         tchgp = npp->elnpp.etchgp;
         for (i = 0; i < insts; i++) 
          {
           idp = mdp->moditps[i]->it_idp;
           /* DBG remove */
           if (idp == NULL || tchgp->lastchg_ofs == 0) 
            __misc_terr(__FILE__, __LINE__);
           /* -- */
           w64p = (word64 *) &(idp[tchgp->lastchg_ofs]);
           *w64p = tim0;
           idp[tchgp->oldval_ofs] = ival;
          }
         break;
        case NPCHG_TCCHK:
         chktcp = npp->elnpp.echktchgp;
         for (i = 0; i < insts; i++) 
          {
           idp = mdp->moditps[i]->it_idp;
           /* DBG remove */
           if (idp == NULL || chktcp->chkactive_ofs == 0)
               __misc_terr(__FILE__, __LINE__);
           /* -- */

           /* AIV 12/30/11 - this not init correctly - this is the correct */
           /* init code */
           idp[chktcp->chkactive_ofs] = FALSE;
           idp[chktcp->chkoldval_ofs] = ival;
 
           tchgp = chktcp->startchgp;
           w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
           *w64p = tim0;
           idp[tchgp->oldval_ofs] = ival;
          }
         break;
        default: __case_terr(__FILE__, __LINE__);
       }
      }
    }
skip_spec:
   init_1net_dces(np, mdp);
  }
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt) 
  {
   if (tskp->trnum == 0) continue;
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     /* LOOKATME - think need to do this for events too */
     init_1net_dces(np, mdp);
    }
  }
}

/*
 * initialize one net's dces (called by faster cver-cc compile and $reset)
 *
 * for XMR mdp is the define (target) itree loc since dce on define var
 * FIXME (OR FINDOUT) - why is algorithm to remove PLI 1.0 vcls
 * but leave PLI 2.0 val chg cbs
 */
//AIV? 05-20-07 why is mdp not referenced
static void init_1net_dces(struct net_t *np, struct mod_t *mdp)
{
 struct dcevnt_t *dcep; 
 struct mod_t *ref_mdp;
 decl_idp_locals_;

 /* must go through setting all dce schedule per inst tables to nil */
 for (dcep = np->dcelst; dcep != NULL;)
  {
   switch (dcep->dce_typ) {
    case DCE_RNG_INST: case DCE_INST:
     /* set per inst. schedule table to nil but leave this type of dce */
     /* not per bit since filter applied to range */
     /* also for dce forms accessed from ref. not target itree loc. */

     /* DBG remove --- */
     if (dcep->st_dctrl->dceschd_tev_ofs == -1)
       __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* SJM 10/07/06 - NOTICE that dce previous values are indexed by */ 
     /* declare in (target) instance number and have that size but */
     /* because dce scheduled tevs are accessed while arming from ref */
     /* point, the dce schd tev table is the size of and index by ref mod */

     /* SJM 10/07/06 - since init called from declared in (targ) itree loc */
     /* need to use the defined in mdp number of insts for XMRs */
     /* AIV 03/03/07 - made a routine to get the ref mod */

     /* SJM 10/07/06 - for XMR dces (@(i1.reg) say), the schd tev table */
     /* has the size of the referenced in (in mdp) module and is accessed */
     /* by the referencing (used in) inum - XMR dce prevals are accessed */
     /* and have the size of the declare in (target) module */
     /* AIV 03/03/07 - these are init when alloced for the intep  */
     /* they are init when linked in for the compiler as well */
     /*
     for (i = 0; i < ref_mdp->flatinum; i++)
      {
       dcep->st_dctrl->dceschd_tev_ofs[i] = -1;
      }
     */

     /* AIV 01/04/07 - init dce expr was using the wrong inst for */
     /* dce with more than one inst and was also skipping init for the */
     /* dce_expr for the one instance case */
     /* set dce previous values to initial wire value */
     if (dcep->dce_expr != NULL) init_dce_exprval(dcep);
     else
      {
       if (dcep->prevval_ofs != 0)
        {
         ref_mdp = dcep_ref_mod(dcep);
         /* 05/18/03 - for XMR there is one for each decl in inst */
         init_dce_prevval(dcep, ref_mdp);
        }
      }
     break;
    case DCE_RNG_MONIT: case DCE_MONIT:
     /* DBG remove -- */
     if (!dcep->dce_1inst) __misc_terr(__FILE__, __LINE__);
     /* --- */
   
     /* SJM 12/30/02 - since monits can't be removed - only turned off */
     /* on reset must turn off and initialize to start value */
     /* previous fix was wrong */
     dcep->dce_off = TRUE;
     /* initialize old value as if this was first time - can never be XMR */
     set_save_idp_(dcep->dce_matchu.idp);
     __init_1instdce_prevval(dcep);
     restore_idp_();
     break;
    case DCE_RNG_QCAF: case DCE_QCAF:
     /* always 1 qca dce load per statement exec */
     /* never a previous value since better to repeat assign of forced */
     /* DBG remove --- */
     if (dcep->prevval_ofs != 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* 11/22/02 AIV - no longer freeing QCAF dces - turned off instead */
     /* also no previous value to re-initialize */
     dcep->dce_off = TRUE;
     break;
    case DCE_RNG_PVC: case DCE_PVC:
     /* DBG remove -- */
     if (!dcep->dce_1inst) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* SJM 01/02/03 - for the dce - always inst specific - just reinit in */
     /* case has previous value */
     set_save_idp_(dcep->dce_matchu.idp);
     __init_1instdce_prevval(dcep);
     restore_idp_();
     break;
    case DCE_CBVC: case DCE_RNG_CBVC:
    case DCE_CBF: case DCE_RNG_CBF: case DCE_CBR: case DCE_RNG_CBR:
     /* DBG remove -- */
     if (!dcep->dce_1inst) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* this handles re-init of PLI 2.0 dce that must be left on */
     /* know will always exist */  
     /* LOOKATME - why left on? or why not consistent with PLI 1 */
     set_save_idp_(dcep->dce_matchu.idp);
//SJM? - this contradicts the comment
     __alloc_plidce_prevval(dcep);
     restore_idp_();
     break;
    /* notice iact never seen here since only enabled from iact stmt */
    default: __case_terr(__FILE__, __LINE__);
   }
   dcep = dcep->dcenxt;
  }
}

/*
 * initialize by setting to current value of wire the dce preval
 * need value for every instance (itree loc. not used)
 *
 * SJM 05/07/03 - now separate alloc and initialize
 * only called if dce prev val non nil
 */
static void init_dce_prevval(struct dcevnt_t *dcep, struct mod_t *decl_mdp)
{
 int32 ii;
 int32 i1;
 word32 *wp;
 byte *sbp, *sbp2, *bp;
 int32 dcewid;
 struct net_t *np;
 struct xstk_t *xsp;
 t_midat *wrk_idp;
 decl_idp_locals_;

 np = dcep->dce_np;
 /* build old value for wire range change detection */ 
 dcewid = __get_dcewid(dcep, np);
 if (np->n_stren)
  {
   /* notice this can never be array */
   if (dcep->dci1 == -2)
    {
     /* SJM 10/12/04 - because contab realloced, must be ndx base of IS */
     wp = &(__contab[dcep->dci2.xvi]);
     for (ii = 0; ii < decl_mdp->flatinum; ii++)
      {
       wrk_idp = decl_mdp->moditps[ii]->it_idp;
       /* know i1 not -1 since must be 1 bit */
       i1 =  (int32) wp[2*ii];
       bp = (byte *) &(wrk_idp[np->nva_ofs]);
       sbp2 = &(bp[i1]);

       /* SJM 08-10-07 copy into idp area - know net ofs and dce same idp */
       sbp = (byte *) &(wrk_idp[dcep->prevval_ofs]);
       memcpy(sbp, sbp2, dcewid); 
      }
    }
   else
    {
     /* here set every instance */
     for (ii = 0; ii < decl_mdp->flatinum; ii++)
      {
       wrk_idp = decl_mdp->moditps[ii]->it_idp;
       /* notice start addr. must be low (2nd) index */
       i1 = (dcep->dci1 == -1) ? 0 : dcep->dci2.i;
       bp = (byte *) &(wrk_idp[np->nva_ofs]);
       sbp2 = &(bp[i1]);
       /* SJM 08-10-07 copy into idp area - know net ofs and dce same idp */
       sbp = (byte *) &(wrk_idp[dcep->prevval_ofs]);
       memcpy(sbp, sbp2, dcewid); 
      }
    }
   return;
  }
 push_xstk_(xsp, dcewid);
 /* dummy itree loc needed so can change inum */
 save_idp_();
 /* this is impossible for monit form */ 
 if (dcep->dci1 == -2)
  {
   /* SJM 10/12/04 - because contab realloced, must be ndx base of IS */
   wp = &(__contab[dcep->dci2.xvi]);
   /* know this is all inst. since monit/iact cannot be -2 form */
   for (ii = 0; ii < decl_mdp->flatinum; ii++)
    {
     i1 =  (int32) wp[2*ii];
     wrk_idp = decl_mdp->moditps[ii]->it_idp;
     /* SJM 08-10-07 need set idp because used by ld wire sect */
     set_idp_(wrk_idp);

     __ld_wire_sect(xsp, np, i1, i1);
     /* minus 2 form only possible for bit select */
     st_scalval_(&(wrk_idp[dcep->prevval_ofs]), xsp->ap[0], xsp->bp[0]);
    }
  }
 else
  {
   for (ii = 0; ii < decl_mdp->flatinum; ii++)
    {
     /* no need to access mod con table here */
     wrk_idp = decl_mdp->moditps[ii]->it_idp;
     set_idp_(wrk_idp);
 /* AIV 03/02/07 - compiled code now treats all dce_edge prevval as scalar */
 /* no need to save more than the low bit - probably true for interp */
 /* as well but leaving for compiler only for now */
 /* just get the low bit regardless of the size */

     /* SJM 08-10-07 need set idp because used by ld wire sect */
     if (dcep->dce_edge && __compiled_sim)
      {
       /* AIV 12/18/07 - this can now be an array need to mask bit */
       /* prior to packing to scalar value - needs to be 0 element not 1 */
       __ld_wire_sect(xsp, np, 0, 0);
       xsp->ap[0] &= 1;
       xsp->bp[0] &= 1;
       st_scalval_(&(wrk_idp[dcep->prevval_ofs]), xsp->ap[0], xsp->bp[0]);
      }
     else 
      {
       __ld_wire_sect(xsp, np, dcep->dci1, dcep->dci2.i);
       __st_idp_val(&(wrk_idp[dcep->prevval_ofs]), dcewid, xsp->ap, xsp->bp);
      }
    }  
  }
 restore_idp_();
 __pop_xstk();
}

/*
 * initialize dce expr old (expr. not variable) value 
 *
 * only called if dce has expr. and this is master (1st) for XMR 
 *
 * since expr evaluated in ref XMR loc, module context is referenced module
 * or XMR case which is set by caller
 *
 * SJM 05/06/03 - need to eval and save in ref mod loc XMR dce case
 * SJM 05/04/05 - notice this 
 */
static void init_dce_exprval(struct dcevnt_t *dcep)
{
 int32 ii;
 struct xstk_t *xsp;
 struct mod_t *ref_mdp;
 struct gref_t *grp;
 struct itree_t *itp;
 t_midat *idp;
 decl_idp_locals_;

 /* AIV 04/04/07 - this was incorrect put old code back */
 if (dcep->dce_xmrtyp != XNP_LOC)
  {
   if (dcep->dce_xmrtyp == XNP_RTXMR)
    {
     itp = (struct itree_t *) dcep->dce_refu.idp[MD_ITP];
     ref_mdp = itp->itip->imsym->el.emdp;
    }
   else
    {
     grp = dcep->dceu.dcegrp;
     ref_mdp = grp->gin_mdp;
    }
  }
 else ref_mdp = __inst_mod;

 /* AIV 01/26/12 - make sure this is set */
 /* DBG remove -- */
 if (dcep->dce_expr->expr_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* edges always 1 bit (maybe low of vector) */
 /* LOOKATME - can expr. be evaluated here? probably since can load wire */ 
 /* need to eval. from initialized wires */
 /* SJM 05/06/03 - must eval expr in ref loc itree context not define */
 save_idp_();
 for (ii = 0; ii < ref_mdp->flatinum; ii++)
  {
   idp = ref_mdp->moditps[ii]->it_idp;
   set_idp_(idp);
   xsp = __eval_xpr(dcep->dce_expr->edgxp);
//AIV FIXME
   /* DBG remove -- */
   if (dcep->dce_expr->expr_ofs > ((struct mod_t *) idp[MD_MDP])->mod_idata_siz)
    __misc_terr(__FILE__, __LINE__);
   /* ----- */
   st_scalval_(&(idp[dcep->dce_expr->expr_ofs]), (xsp->ap[0] & 1L), 
    (xsp->bp[0] & 1L));
   __pop_xstk();
  }
 restore_idp_();
}

/*
 * return the reference dcep mod 
 */
static struct mod_t *dcep_ref_mod(struct dcevnt_t *dcep)
{
 struct mod_t *ref_mdp;
 struct itree_t *itp;

 if (dcep->dce_xmrtyp == XNP_UPXMR || dcep->dce_xmrtyp == XNP_DOWNXMR)
  {
   ref_mdp = dcep->dceu.dcegrp->targmdp;
  }
 /* AIV 03/01/07 - rooted must be linked with its containing mod */
 else if (dcep->dce_xmrtyp == XNP_RTXMR)
  {
   /* AIV 03/03/07 - should be match itp not ref */
   itp = (struct itree_t *) dcep->dce_matchu.idp[MD_ITP];
   ref_mdp = itp->itip->imsym->el.emdp;
  }
 else ref_mdp = __inst_mod;
 return(ref_mdp);
}

/*
 * return T if dce needs a previous value
 */
extern int32 __dce_needs_prevval(struct dcevnt_t *dcep, struct mod_t *mdp)
{
 struct net_t *np;

 np = dcep->dce_np;
#ifdef __XPROP__
//AIV EXPROP - merged @  - don't include????
 //if (dcep->merged) return(FALSE);
 /* if xprop xedges always need to save the previous value */
 //AIV PUTMEBACK __xprop2 - not doing edges for now
 /* skipping events for now */
 if (__xprop && np->ntyp != N_EVENT)
  {
   struct delctrl_t *dctp;
   int32 not_eligible;

   /* AIV 02/28/12 - only alloc this if mod uses xprop */
   if (mdp != NULL && mdp->m_use_xprop)
    {
     if (np->n_isarr && dcep->dci2.i == -1)
      {
       /* cannot handle variable arrays for now */
       //AIV LOOKATME
      }
     else
      {
       dctp = dcep->st_dctrl;
       /* AIV 02/28/12 - if no xprop stmt list do no need prevval set */
       if (!__no_xprop_edges && dctp != NULL)
        {
         if (dctp->dctyp == DC_EVENT && dctp->is_always)
          {
           not_eligible = FALSE;
           __eligible_xprop_stofsts(dctp->actionst, &not_eligible);
           if (!not_eligible)
            {
             return(TRUE);
            }
          }
        }
      }
    }
  }
#endif

 /* always need prevval for PLI, multiple change at same time possible */ 
 if (dcep->dce_typ < ST_ND_PREVVAL)
  { 
   /* no previous value for arrays or non edge entire wire regs */
   /* but needed for all others and always build if nd prev val T */ 
   if (dcep->dce_typ == DCE_RNG_QCAF || dcep->dce_typ == DCE_QCAF)
    {
     return(FALSE);
    }
   /* AIV 02/24/09 - can have wire arrays now */
   /* AIV 03/23/09 - can have variable index arrays only - if constant */
   /* better be constant array value */
   if (np->ntyp < NONWIRE_ST && np->n_isarr) return(FALSE);

   /* AIV 12/11/07 - if an array need to prevval_ofs for edge filter also */
   if ((np->ntyp >= NONWIRE_ST && dcep->dci1 == -1 && !dcep->dce_edge) 
       || dcep->dce_expr != NULL) return (FALSE);
  }
 /* AIV 01/21/08 - compiler only needs prevval now if has range */
 /* AIV 02/28/08 - if dce has been merged do not need prevval */
 if (dcep->merged) return(FALSE);

 /* AIV 02/21/08 - leaving this commented out for now running some designs 
  slower - pci - why??????????? */
/* ----------------------------------------------------
 if (__compiled_sim) 
  {
   //AIV FIXME - if strength and mfi init code isn't handled correctly
   //goes through the interp for init and records the change
   if (np->n_stren) 
    {
     return(TRUE);
    }
   // if no range and no edge don't need the previous value - known to change 
   // IO_BID - still needs the prevval due to wrapper 
   if (dcep->dci1 == -1 && !dcep->dce_edge && np->iotyp != IO_BID)
    {
     return(FALSE);
    }
  }
---------------------------------------------------- */
 return(TRUE);
}

/*
 * initialize and set to current value into dce preval idp area
 * variant for one inst forms (taken from current idp) - monit and XMR
 * SJM 05/07/03 - now only can be called after all of dce filled 
 *
 * this routine must be passed declare (target) itree context on top of
 * inst stack and ref loc 1 under
 */
extern void __init_1instdce_prevval(struct dcevnt_t *dcep)
{
 byte *sbp, *sbp2;
 int32 dcewid;
 struct net_t *np;
 struct xstk_t *xsp;
 decl_idp_locals_;

 np = dcep->dce_np;
 /* DBG remove -- */
 if (dcep->dce_expr != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (dcep->prevval_ofs == 0) return;

 dcewid = __get_dcewid(dcep, np);
 /* SJM 05/08/03 - eval in match context but store as 0 since only 1 inst */
 set_save_idp_(dcep->dce_matchu.idp); 
 if (np->n_stren)
  {
   /* notice this can never be array */
   sbp = (byte *) &(__idp[dcep->prevval_ofs]);
   /* must load for initialize from right inst. */
   sbp2 = (byte *) &(__idp[np->nva_ofs]);
   if (dcep->dci1 != -1) sbp2 = &(sbp2[dcep->dci2.i]);
   memcpy(sbp, sbp2, dcewid);
  }
 else
  {
   push_xstk_(xsp, dcewid);
   /* must load value from correct (match_itp instance) on it stack */
   __ld_wire_sect(xsp, np, dcep->dci1, dcep->dci2.i);

   /* need dummy place for itree inst num since know only 1 inst. */
   /* this is match loc but only 1 inst - so any would work */
   __st_idp_val(&(__idp[dcep->prevval_ofs]), dcewid, xsp->ap, xsp->bp);
   __pop_xstk();
  }
 restore_idp_();
}

/*
 * STATEMENT PREPARATION ROUTINES
 */

/*
 * for every always, add surrounding forever statement
 *
 * all variable storage must have been allocated by here
 * all id (and glbid) expression nodes made to point to variable
 */
extern void __prep_stmts(void)
{
 int32 i; 
 struct ialst_t *ialp; 
 struct task_t *tskp;
 struct mod_t *mdp;
 int32 sav_declobj, iatyp;

 /* SJM 05-13-13 - need to change order of init always list so all */
 /* always blocks (but not always comb or always ff) come before */
 /* initial blocks - LRM says any order but FPGA libraries (Altera) */
 /* depend on always being armed before any initial to start up */

 /* always comb can be used to force always to run after all init/always */
 /* SJM 05-13-13 - made an option for now because lots of old bug fixes */
 /* changed to old order - need to see what people want */
 if (__sched_always_blocks_first)
  {
   reorder_all_mods_ialst_always_first();
  }

#ifdef __XPROP__
 /* AIV 10/20/11 - if xprop2 must prep stmts here since it alloc and changes */
 /* stmts while checking for xs */
 if (__xprop2)
  {
   __prep_xprop_stmts(TRUE);
  }
#endif
 /* bottom of if/case/delay control continuation stack must be null */
 /* for cases where continuation is really NULL - no goto */
 __prpsti = 0;
 __nbsti = -1;
 __prpstk[0] = NULL;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   __prep_numsts = 0;
   __processing_func = FALSE;
   for (ialp = __inst_mod->ialst; ialp != NULL; ialp = ialp->ialnxt)
    {
     /* for always, must be first - tails of last must point to 1st stmt */
     /* here may be list and will be put on end */
     iatyp = ialp->iatyp;
     /* AIV 07/12/12 - now supporting new SV always_* types */
     if (iatyp == ALWAYS || iatyp == ALWAYS_COMB || iatyp == ALWAYS_FF || 
      iatyp == ALWAYS_LATCH)
      {
       add_loopend_goto(ialp->iastp, ialp->iastp);
       /* AIV 03/03/09 - need to mark always @ blocks for later attempt */
       /* to merge on edge exprs */
       if (ialp->iastp->stmttyp == S_DELCTRL)
        {
         struct delctrl_t *dctp;
         dctp = ialp->iastp->st.sdc;
         if (dctp != NULL && dctp->dctyp == DC_EVENT)
          dctp->is_always = TRUE;
        }
      }
     ialp->iastp = __prep_lstofsts(ialp->iastp, TRUE, FALSE);
     /* DBG remove --- */
     if (__prpsti != 0) __misc_terr(__FILE__, __LINE__); 
     /* --- */
    }
   /* notice, there is one set of task variables per instance */
   /* but a task in one itree inst. can be enabled multiple times */
   /* tthrds for tasks (not functions) is per inst. list of active thrds */
   /* so if disable can disable all below */
   for (tskp = __inst_mod->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     /* never need task threads for function */ 
     if (tskp->tsktyp == FUNCTION) continue; 
     tskp->tthrds = (struct tskthrd_t **)
      __my_malloc(__inst_mod->flatinum*sizeof(struct tskthrd_t *));
     for (i = 0; i < __inst_mod->flatinum; i++) tskp->tthrds[i] = NULL;
    }
  
   sav_declobj = __cur_declobj;
   __cur_declobj = TASK;
   for (tskp = __inst_mod->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     /* named blocks handled as statement where they occur */
     if (tskp->tsktyp == FUNCTION) __processing_func = TRUE;
     else if (tskp->tsktyp == TASK) __processing_func = FALSE; 
     else continue;

     tskp->tskst = __prep_lstofsts(tskp->tskst, FALSE, FALSE);
     /* no branch continue here because must schedule/disable thread */
     /* need inform if function never enable */
     if (!tskp->t_used)
      {
       char s1[RECLEN], s2[RECLEN];

       if (__processing_func) strcpy(s2, "called");
       else strcpy(s2, "enabled"); 
       __gfinform(439, tskp->tsksyp->syfnam_ind, tskp->tsksyp->sylin_cnt, 
        "%s %s never %s", __to_tsktyp(s1, tskp->tsktyp), tskp->tsksyp->synam,
        s2);
      }
     /* DBG remove --- */ 
     if (__prpsti != 0) __misc_terr(__FILE__, __LINE__); 
     /* --- */
    }
   __processing_func = FALSE;
   __cur_declobj = sav_declobj;

   /* DBG remove --
   {
    extern void __dmp_mod(FILE *, struct mod_t *, int32);

    if (__debug_flg) __dmp_mod(stdout, mdp, FALSE);
   }
   --- */   
   /* DBG remove ---
   if (__prep_numsts != __inst_mod->mstnum) __misc_terr(__FILE__, __LINE__);
   --- */

   __pop_wrkitstk();
  }
}

/*
 * re-order a init always list so all always first then all init - move
 * always ff and always comb with always, but still done after all always
 * and init armed
 *
 * SJM 05-13-13 - new order consistent with LRM but needed to match FPGA
 * library results - any order legal - but now think all simulators
 * need initial before always
 */
static void reorder_all_mods_ialst_always_first(void)
{
 int32 num_ialst_els, ai, alwi, initi;
 struct mod_t *mdp;
 struct ialst_t *ialp, *ialp2, *last_ialp; 
 struct ialst_t **init_ptr_tab, **always_ptr_tab;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  { 
   /* count number of ia elements in mod */ 
   num_ialst_els = 0;
   for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt) num_ialst_els++;

   init_ptr_tab = (struct ialst_t **)
    __my_malloc(num_ialst_els*sizeof(struct ialst_t *));
   always_ptr_tab = (struct ialst_t **)
    __my_malloc(num_ialst_els*sizeof(struct ialst_t *));
   alwi = initi = -1;

   for (ialp = mdp->ialst; ialp != NULL;)
    {
     ialp2 = ialp->ialnxt;

     if (ialp->iatyp == INITial) init_ptr_tab[++initi] = ialp;
     else always_ptr_tab[++alwi] = ialp;
     ialp->ialnxt = NULL;
  
     ialp = ialp2;
    }
   mdp->ialst = NULL;
   last_ialp = NULL;
   /* DBG remove -- */
   if (alwi + initi + 2 != num_ialst_els) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* rebuild the mod's ialst for always (all 3 types) first */ 
   for (ai = 0; ai <= alwi; ai++)
    {
     if (last_ialp == NULL) mdp->ialst = always_ptr_tab[ai];
     else last_ialp->ialnxt = always_ptr_tab[ai];
     last_ialp = always_ptr_tab[ai];
    }
   /* rebuild the mod's ialst for init */
   for (ai = 0; ai <= initi; ai++)
    {
     if (last_ialp == NULL) mdp->ialst = init_ptr_tab[ai];
     else last_ialp->ialnxt = init_ptr_tab[ai];
     last_ialp = init_ptr_tab[ai];
    }
  }
}

/*
 * routine to prepare (optimize) list of statements for simulation
 * returns front (may be new statement for for)
 *
 * know begin ends already turned into statements list wherever possible
 * know if containing statement is loop, goto added at end before here
 */
extern struct st_t *__prep_lstofsts(struct st_t *hdrstp, int32 nd_endgoto,
 int32 is_dctrl_chain)
{
 struct st_t *stp;
 int32 fji, ii;
 struct for_t *forp;
 struct st_t *astp, *astp2, *last_stp, *fjstp;
 struct st_t *save_continue_stp, *save_break_stp;
 struct delctrl_t *dctp;
 struct mod_t *cur_mdp;

 /* AIV 04/25/07 - since can get here from interactive debugger need get mod */
 if (__idp == NULL) cur_mdp =  __inst_mod;
 else cur_mdp = get_inst_mod_();

 for (stp = hdrstp, last_stp = NULL; stp != NULL; stp = stp->stnxt)
  {
   __sfnam_ind = stp->stfnam_ind;
   __slin_cnt = stp->stlin_cnt;

   /* --- DBG remove --- 
   __dbg_msg("AT %s %s - STMT PREP %04d (%s)\n",
    __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt),
    cur_mdp->msym->synam, __prep_numsts - 1,
    __to_sttyp(__xs2, stp->stmttyp));
   --- */ 

   switch ((byte) stp->stmttyp) {
    case S_INC: case S_DEC:
    case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA: break;
    case S_IF:
     if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
     stp->st.sif.thenst = __prep_lstofsts(stp->st.sif.thenst, TRUE, FALSE);
     if (stp->st.sif.elsest != NULL)
      stp->st.sif.elsest = __prep_lstofsts(stp->st.sif.elsest, TRUE, FALSE);
     if (stp->stnxt != NULL) __pop_prpstmt();
     break;
    case S_CASE:
     prep_case(stp);
     break;
    case S_FOR:
     /* must link so old for assign is replaced by for inc. that points */
     /* to for body (added) - key is that for inc next is not used */ 
     /* first add goto to for statement itself at end of body */
     /* notice initial assign already precedes for */
     forp = stp->st.sfor;
     astp2 = add_loopend_goto(forp->forbody, forp->forbody);
     /* change to point to for itself */
     astp2->stnxt->st.sgoto = stp;
     astp2->stnxt->st.sgoto->lpend_goto_dest = TRUE;

     /* insert inc stmt before goto */
     forp->forinc_tail->stnxt = astp2->stnxt;
     astp2->stnxt = forp->forinc;
     /* inc will be fixed up in body of loop */
     /* AIV 09/28/10 - save/restore/set loop continue/break statements */ 
     save_continue_stp = __st_loop_continue; 
     save_break_stp = __st_loop_break;
     __st_loop_continue = forp->forinc; 
     __st_loop_break = astp2->stnxt->stnxt; 
     forp->forbody = __prep_lstofsts(forp->forbody, FALSE, FALSE);
     __st_loop_continue = save_continue_stp; 
     __st_loop_break = save_break_stp; 
     break;
    case S_FOREVER:
    case S_WHILE:
    case S_DO_WHILE:
     /* scheme here if evaluation of while means if non NULL xpr see if T */
     /* if not do not exec statement else exec - loops to same statement */
     /* something like while (x) begin : y ... end becomes: */
     /* L: while () begin ... end; goto L; */
     /* AIV 09/28/10 - save/restore/set loop continue/break statements */ 
     save_continue_stp = __st_loop_continue; 
     save_break_stp = __st_loop_break;
     astp2 = add_loopend_goto(stp->st.swh.lpst, stp);
     __st_loop_continue = astp2; 
     __st_loop_break = astp2->stnxt; 
     stp->st.swh.lpst = __prep_lstofsts(stp->st.swh.lpst, FALSE, FALSE);
     __st_loop_continue = save_continue_stp; 
     __st_loop_break = save_break_stp; 
     break;
    case S_REPEAT:
     /* AIV 09/28/10 - save/restore/set loop continue/break statements */ 
     save_continue_stp = __st_loop_continue; 
     save_break_stp = __st_loop_break;
     /* first allocate special repeat setup statement and link on front */
     astp = __alloc2_stmt(S_REPSETUP, stp->stfnam_ind, stp->stlin_cnt);
     /* fill guts of new statement with repeat guts - astp2 pnts to nxt st */
     *astp = *stp;       
     if (__iact_state) 
      {
       /* AIV 03/31/09 - if interactive debugger added wait statemtent */
       /* must set idp offset area */
       __expand_1mod_idp_area(cur_mdp, 1);
       astp->st.srpt.reptmp_ofs = cur_mdp->mod_idata_siz - 1;
       __idp[astp->st.srpt.reptmp_ofs] = 0;
      }

     stp->stmttyp = S_REPSETUP;
     stp->rl_stmttyp = stp->stmttyp;
     stp->st_unbhead = FALSE;
     stp->st.scausx = NULL;

     /* then exchange stp and astp pointers (since prev nxt is stp) */
     astp2 = astp;
     astp = stp;
     stp = astp2;
     astp->stnxt = stp;

     /* stp now points to rep setup */
     /* DBG remove --
     if (__debug_flg)
      {
       __dbg_msg("AT %s %s - STMT PREP (%s)\n",
        __bld_lineloc(__xs, astp->stfnam_ind, astp->stlin_cnt),
        cur_mdp->msym->synam, __to_sttyp(__xs2, astp->stmttyp));
      }
     --- */
     /* DBG remove --
     __prep_numsts++;
     if (__debug_flg)
      {
       __dbg_msg("%04d: AT %s %s - STMT PREP (%s)\n", astp->stalloc_ndx,
        __bld_lineloc(__xs, astp->stfnam_ind, astp->stlin_cnt),
        cur_mdp->msym->synam, __to_sttyp(__xs2, astp->stmttyp));
      }
     --- */
     /* ALTERNATE DBG remove ---
     __prep_numsts++;
     if (__debug_flg)
      {
       __dbg_msg("AT %s %s - STMT PREP %04d (%s)\n",
        __bld_lineloc(__xs, astp->stfnam_ind, astp->stlin_cnt),
        cur_mdp->msym->synam, __prep_numsts - 1,
        __to_sttyp(__xs2, astp->stmttyp));
      }
     --- */
     /* allocate per inst. count storage */ 
     /* add loop back to repeat header */
     astp2 = add_loopend_goto(stp->st.srpt.repst, stp);
     /* 32 bit word32 width built in here */
     /* end must loop back to actual repeat not setup */
     __st_loop_continue = astp2; 
     __st_loop_break = astp2->stnxt; 
     stp->st.srpt.repst = __prep_lstofsts(stp->st.srpt.repst, FALSE, FALSE);
     __st_loop_continue = save_continue_stp; 
     __st_loop_break = save_break_stp; 
     break;
    case S_WAIT:
     /* build and adding dc events is just change expr. case here */
     dctp = stp->st.swait.wait_dctp;
     /* must turn on iact bit so linkon dce adds to free list when done */ 
     if (__iact_state) 
      {
       dctp->dc_iact = TRUE;
       /* AIV 03/31/09 - if interactive debugger added wait statemtent */
       /* must set idp offset area */
       __expand_1mod_idp_area(cur_mdp, 1);
       dctp->dceschd_tev_ofs = cur_mdp->mod_idata_siz - 1;
       __idp[dctp->dceschd_tev_ofs] = 0;
      }
     /* wait is simple expression - EV OR illegal - edge illegal state dep. */
     bld_evxpr_dces(stp->st.swait.lpx, dctp, FALSE);
     /* wait @ event triggers on loop exp and executes wait to evaluate */
     /* the loop expression */
     dctp->actionst = stp;
     /* fill the delay/event scheduled action rec that is needed by wait */
     /* for arming and triggering */
     dctp->dctyp = DC_WAITEVENT;

     /* prepare the statements */ 
     /* wait needs end link to next statement after wait not beginning */
     if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
     /* last statement (normally only 1, will have goto to continuation */
     stp->st.swait.lpst = __prep_lstofsts(stp->st.swait.lpst, TRUE, FALSE);
     if (stp->stnxt != NULL) __pop_prpstmt();
     break;
    case S_DELCTRL:
     dctp = stp->st.sdc;
     /* 10/28/00 - if repeat form, insert repeat dc setup in front */
     if (dctp->repcntx != NULL)
      {
       /* first allocate special repeat setup statement and link on front */
       /* this is needed so can insert after to get lists nexts right */
       /* but still have setup first */
       astp = __alloc2_stmt(S_REPDCSETUP, stp->stfnam_ind, stp->stlin_cnt);
       /* fill guts of new statement with  delctrl statment guts */
       /* astp2 points to next stmt */
       *astp = *stp;       

       stp->stmttyp = S_REPDCSETUP;
       stp->rl_stmttyp = stp->stmttyp;
       stp->st_unbhead = FALSE;
       stp->st.scausx = NULL;

       /* then exchange stp and astp pointers (since prev nxt is stp) */
       /* so stp will be at original (after inserted setup) so next works */
       /* right in loop */
       astp2 = astp;
       astp = stp;
       stp = astp2;
       astp->stnxt = stp;
       /* DBG remove */
       if (stp->st.sdc != dctp) __misc_terr(__FILE__, __LINE__);
       /* --- */
      }
     /* 10/28/00 SJM - always still prepare dctrl as usual */
     prep_dctrl(stp);
     break;
    case S_NAMBLK:
     /* for named block, no continuation - must be subthread except in func */
     __push_nbstk(stp);
     if (__processing_func)
      { 
       if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
       stp->st.snbtsk->tskst = __prep_lstofsts(stp->st.snbtsk->tskst,
        TRUE, FALSE);
       if (stp->stnxt != NULL) __pop_prpstmt();
      }
     else
      {
       __push_prpstmt((struct st_t *) NULL);
       stp->st.snbtsk->tskst = __prep_lstofsts(stp->st.snbtsk->tskst, FALSE,
        FALSE);
       __pop_prpstmt();
      }
     __pop_nbstk();
     break;
    case S_UNBLK:
     if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
     /* need continuation for simple block */
     stp->st.sbsts = __prep_lstofsts(stp->st.sbsts, TRUE, FALSE);
     if (stp->stnxt != NULL) __pop_prpstmt();
     break;
    case S_UNFJ:
     __push_prpstmt((struct st_t *) NULL);
     /* continuation inside these must be NULL, not stacked val */
     for (fji = 0;; fji++)
      {
       if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
       stp->st.fj.fjstps[fji] = __prep_lstofsts(fjstp, FALSE, FALSE);
      }
     __pop_prpstmt();
     /* SJM 12/03/05 - for now since need stmt to reenter from scheduler */ 
     /* during cvc compiled sim, need nil stmt always after if no stmt */
     /* follows a fork-join */
     if (__compiled_sim) 
      {
       struct st_t *nilstp;

       if (stp->stnxt == NULL)
        {
         nilstp = __alloc2_stmt(S_NULL, stp->stfnam_ind, stp->stlin_cnt);
         stp->stnxt = nilstp;
        }
      }
     break;
    case S_QCONTA:
     /* first build the one for each lhs cat element list of per inst */
     /* qcaf dce lists and initialize - then during build just fill */
     bld_init_qcaf_dce_lstlst(stp);

     /* separate prepare because different qcval record for each inst */
     /* qcaf dces per inst because only one active on a reg at a time */
     for (ii = 0; ii < cur_mdp->flatinum; ii++)
      {
       __push_itstk(cur_mdp->moditps[ii]);

       if (stp->st.sqca->qcatyp == ASSIGN) prep_qc_assign(stp, FALSE);
       else
        {
         /* force of reg, is like assign except overrides assign */
         if (stp->st.sqca->regform) prep_qc_assign(stp, TRUE);
         else prep_qc_wireforce(stp);
        }
       __pop_itstk();
      }
     break;
    case S_QCONTDEA:
     for (ii = 0; ii < cur_mdp->flatinum; ii++)
      {
       __push_itstk(cur_mdp->moditps[ii]);

       if (stp->st.sqcdea.qcdatyp == DEASSIGN) prep_qc_deassign(stp);
       else
        {
         /* SJM 06/21/02 - since deassign/release just allocs qcvals */
         /* no diff between release/deassign */
         if (stp->st.sqcdea.regform) prep_qc_deassign(stp);
         else prep_qc_wirerelease(stp);
        } 
       __pop_itstk();
      } 
     break;
    case S_DSABLE:
     /* inside function disables are gotos to next statement in up block */
     if (__processing_func) prep_func_dsable(stp);

     /* since for any other name block or task cannot optimize since can */
     /* be disabled from interactive command */ 
     break;
    case S_FUNCCALL:
    case S_TSKCALL:
     /* identify and build dces only for monit/fmonit here */
     prep_stskcalls(stp, cur_mdp);
     break;
    case S_BREAK: 
     /* DBG remove ---*/
     if (__st_loop_break == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     stp->st.sgoto = __st_loop_break;
     break;
    case S_CONTINUE:
     /* DBG remove ---*/
     if (__st_loop_continue == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     stp->st.sgoto = __st_loop_continue;
     break;
    case S_RETURN: break;
   }
   last_stp = stp;
  }
 /* now at end of list */
 /* fix up by working up stack to point where statement has next */
 if (nd_endgoto && __prpstk[__prpsti] != NULL) 
  {
   /* DBG remove ---*/
   if (last_stp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* need to save cur location so allocate get right stmt loc */ 
   astp = __alloc2_stmt(S_GOTO, last_stp->stfnam_ind, last_stp->stlin_cnt);
   astp->st.sgoto = __prpstk[__prpsti];

   if (is_dctrl_chain) astp->dctrl_goto = TRUE;

   /* in this rare case will not have line number - can it happen */
   /* LOOKATME - can this happen */ 
   if (last_stp == NULL) hdrstp = astp;
   else
    {
     last_stp->stnxt = astp;
    }
   /* DBG remove --
   __prep_numsts++;
   if (__debug_flg)
    {
     __dbg_msg("AT %s %s - STMT PREP %04d (%s)\n",
      __bld_lineloc(__xs, astp->stfnam_ind, astp->stlin_cnt),
      cur_mdp->msym->synam, __prep_numsts - 1,
      __to_sttyp(__xs2, astp->stmttyp));
    }
   --- */
  }
 return(hdrstp);
}

/*
 * prepare sys task enable - only for monit/fmonit and builds dces for those
 *
 * SJM 06/21/02 - new algorithm builds monit/fmonit dces during prep
 */
static void prep_stskcalls(struct st_t *stp, struct mod_t *mdp)
{
 struct expr_t *tkxp;
 struct tskcall_t *tkcp;
 struct sy_t *syp;
 struct systsk_t *stbp;

 tkcp = &(stp->st.stkc);
 tkxp = tkcp->tsksyx;

 /* nothing to do for non system task calls */
 if (tkxp->optyp == ID && *(tkxp->lu.sy->synam) == '$')
  {
   syp = tkxp->lu.sy;
   stbp = syp->el.esytbp;

   switch (stbp->stsknum) {
    /* system task args do not have type or width - take what is there */
    case STN_MONITOR: case STN_MONITORB: case STN_MONITORH: case STN_MONITORO:
     __prep_insrc_monit(stp, FALSE, mdp);
     break;
    /* tasks that take a multichannel descriptor followed by anything */
    case STN_FMONITOR: case STN_FMONITORB: case STN_FMONITORH:
    case STN_FMONITORO:
     __prep_insrc_monit(stp, TRUE, mdp);
     break;
    default: break;
   }
  }
}

/*
 * for list of statements that is loop body, add goto that links
 * back to front of loop
 * returns previous last statement - error to be called withh begstp nul
 */
static struct st_t *add_loopend_goto(struct st_t *begstp,
 struct st_t *targstp)
{
 struct st_t *stp; 
 struct st_t *last_stp, *gtstp;

 /* DBG remove --- */
 if (begstp == NULL) __arg_terr(__FILE__, __LINE__);
 /* --- */

 /* find last statement in loop - know has at least one */
 for (stp = begstp, last_stp = NULL; stp != NULL; stp = stp->stnxt)
  last_stp = stp;
 if (last_stp == NULL) __arg_terr(__FILE__, __LINE__);
 gtstp = __alloc2_stmt(S_GOTO, last_stp->stfnam_ind, last_stp->stlin_cnt);
 gtstp->lpend_goto = TRUE;
 gtstp->st.sgoto = targstp;
 targstp->lpend_goto_dest = TRUE;

 gtstp->stfnam_ind = last_stp->stfnam_ind;
 gtstp->stlin_cnt = last_stp->stlin_cnt;
 last_stp->stnxt = gtstp;
 if (__debug_flg)
  {
   char s1[RECLEN], s2[RECLEN], s3[RECLEN];

   __dbg_msg("++ loop: adding goto after %s at %s back to stmt %s at %s\n",
    __to_sttyp(s1, last_stp->stmttyp), __bld_lineloc(__xs, 
    last_stp->stfnam_ind, last_stp->stlin_cnt), __to_sttyp(s2,
    begstp->stmttyp), __bld_lineloc(s3, targstp->stfnam_ind,
    targstp->stlin_cnt));
  }
 /* --- */
 return(last_stp);
}

/*
 * push a nested preparation statement
 * this is for control flow so many not pushed
 */
extern void __push_prpstmt(struct st_t *stp)
{
 if (++__prpsti >= MAXPRPSTNEST)
  __sgfterr(317, "statements nested too deeply (%d)", MAXPRPSTNEST);
 __prpstk[__prpsti] = stp;
 /* DBG remove --
 if (__debug_flg)
  {
   if (stp != NULL)
    {
     __dbg_msg(".. push nested stmt stack to %d at %s\n", __prpsti,
      __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt));
    }
   else
    {  
     __dbg_msg(".. push NULL nested stmt stack to %d\n", __prpsti);
    }
  }
 --- */
}

/*
 * pop a nested preparation statement
 */
extern void __pop_prpstmt(void)
{ 
 /* should never undeflow */
 if (__prpsti < 0) __misc_sgfterr(__FILE__, __LINE__);
 __prpsti--;
 /* DBG remove --
 if (__debug_flg)
  {
   struct st_t *stp;

    stp = __prpstk[__prpsti];
    if (stp != NULL)
     {
      __dbg_msg(".. pop nested stmt stack to %d at %s\n", __prpsti,
       __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt));
     }
    else
     {  
      __dbg_msg(".. pop NULL nested stmt stack to %d\n", __prpsti);
     }
  }
 --- */
}

/*
 * push a nested named block statement - this is for disable processing
 * and only used during preparation
 */
extern void __push_nbstk(struct st_t *stp)
{
 if (++__nbsti >= MAXPRPSTNEST)
  __sgfterr(318, "named blocks nested too deeply (%d)", MAXPRPSTNEST);
 __nbstk[__nbsti] = stp;
}

/*
 * pop a nested named block statement
 */
extern void __pop_nbstk(void)
{ 
 /* named blocks during prep. also should not undeflow */
 if (__nbsti < 0) __misc_sgfterr(__FILE__, __LINE__);
 __nbsti--;
}

/*
 * prepare case statement for simulation
 */
static void prep_case(struct st_t *stp)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;

 if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);

 dflt_csip = stp->st.scs.csitems;
 /* this will move up stack to add goto after ending stp */
 for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
  csip->csist = __prep_lstofsts(csip->csist, TRUE, FALSE);

#ifdef __XPROP__
 /* AIV 08/02/11 - now might have xprop list to process as well */
 if (stp->st.scs.xprop_lstp != NULL)
  stp->st.scs.xprop_lstp = __prep_lstofsts(stp->st.scs.xprop_lstp, TRUE, FALSE);
#endif

 /* this will move up stack to connect ending stnxt to next exec. place */
 if (dflt_csip->csist != NULL)
  dflt_csip->csist = __prep_lstofsts(dflt_csip->csist, TRUE, FALSE);
 if (stp->stnxt != NULL) __pop_prpstmt();
}

/*
 * prepare a declare control
 * tricky because #<> #<> #<> etc [stmt] legal
 */
static void prep_dctrl(struct st_t *stp)
{
 struct st_t *stp2;
 struct delctrl_t *dctp;
 struct st_t *last_stp;
 struct mod_t *cur_mdp;

 dctp = stp->st.sdc;
 /* AIV 03/31/09 - if interactive debugger added need to setup */
 /* idp offset area */
 if (__iact_state) 
  {
   if (__idp == NULL) cur_mdp =  __inst_mod;
   else cur_mdp = get_inst_mod_();

   if (stp->stmttyp == S_REPDCSETUP)
    {
     __expand_1mod_idp_area(cur_mdp, 1);
     dctp->dce_repcnt_ofs = cur_mdp->mod_idata_siz - 1;
     __idp[dctp->dce_repcnt_ofs] = 0;
    }
   __expand_1mod_idp_area(cur_mdp, 1);
   dctp->dceschd_tev_ofs = cur_mdp->mod_idata_siz - 1;
   __idp[dctp->dceschd_tev_ofs] = 0;
  }
 cnv_cmpdctl_todu(stp, dctp);
 /* if no statement just prepare expr. - stnxt correct */
 if (dctp->actionst == NULL) return;

 /* for #[d1] #[d2] #[d3] ... <stmt> chain, add goto to end only */ 
 last_stp = NULL;
 for (stp2 = dctp->actionst;; stp2 = stp2->st.sdc->actionst)
  {
   /* keep going until delay control has no action statement or */
   /* a non delay control action statement */
   /* case "#10 begin #20 ..." - is not delay control chain */
   if (stp2 == NULL || stp2->stmttyp != S_DELCTRL || stp2->st_unbhead)
    break;

   /* SJM 10/07/06 - need the goto before any (will be the last) rhs */
   /* delay or event control because it really is an action stmt */ 
   if (stp2->st.sdc->dctyp != DC_EVENT && stp2->st.sdc->dctyp != DC_DELAY)
    break;

   dctp = stp2->st.sdc;
   cnv_cmpdctl_todu(stp2, dctp);

   /* DBG remove --
   if (__debug_flg)
    {
     __dbg_msg("AT %s %s - STMT PREP (%s)\n",
      __bld_lineloc(__xs, stp2->stfnam_ind, stp2->stlin_cnt),
      __inst_mod->msym->synam, __to_sttyp(__xs2, stp2->stmttyp));
    }
    --- */

   last_stp = stp2;
  }
 if (stp2 == NULL)
  {
   __sgfwarn(562, "INTERNAL - delay control chain does not end with stmt.");
   /* unrecognized delay control chain */
   if (last_stp == NULL) __misc_terr(__FILE__, __LINE__);
   stp2 = last_stp;
  }
 /* finally, just add goto from stp2 to original statement next */
 if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
 stp2 = __prep_lstofsts(stp2, TRUE, TRUE);
 if (stp->stnxt != NULL) __pop_prpstmt();
}

/*
 * convert a delay control CMP LST form to run tim delay 
 */
static void cnv_cmpdctl_todu(struct st_t *stp, struct delctrl_t *dctp)
{
 struct gate_t gwrk;
 struct sy_t tmpsym;

 /* notice for delay controls schd event tevs field not used */
 if (dctp->dctyp == DC_DELAY || dctp->dctyp == DC_RHSDELAY)
  {
   __add_dctldel_pnp(stp); 
   tmpsym.syfnam_ind = (word32) __sfnam_ind;
   tmpsym.sylin_cnt = __slin_cnt;
   __prep_delay(&gwrk, dctp->dc_du.pdels, FALSE, FALSE,
    "procedural delay control", FALSE, &tmpsym, FALSE);
   if (__nd_neg_del_warn)
    {
     __sgferr(974, "delay control negative delay illegal (0 used)");
     __nd_neg_del_warn = FALSE;
    } 
   dctp->dc_delrep = gwrk.g_delrep;
   dctp->dc_du = gwrk.g_du;
  }
 else prep_event_dctrl(dctp);
}

/*
 * for every value in expr. add the dc list to appropriate wire 
 */
static void prep_event_dctrl(struct delctrl_t *dctp)
{
 struct expr_t *xp;
 struct expr_t *evx;
 struct paramlst_t *pmp;

 /* must change delay representation to DT_1X */
 pmp = dctp->dc_du.pdels;
 evx = pmp->plxndp;
 /* first free param list form */
 __my_free(pmp, sizeof(struct paramlst_t));
 dctp->dc_du.d1x = evx;
 dctp->dc_delrep = DT_1X;

 /* SJM 06/28/05 - for degenerate form no dces to build but must catch */  
 /* nil event expr */
 if (evx == NULL)
  {
#ifndef __CVC_RT__
   __sgfwarn(3139,
    "implicit event control - no events in statement - will never trigger");
#endif
   return;
  }

 if (evx->optyp != OPEVOR && evx->optyp != OPEVCOMMAOR)
  { bld_ev_dces(evx, dctp); return; }
 /* notice evor tree must associate left to right - i.e. evor chain */
 /* extends down left links */
 for (xp = evx;;) 
  {
   bld_ev_dces(xp->ru.x, dctp);
   if (xp->lu.x->optyp != OPEVOR && xp->lu.x->optyp != OPEVCOMMAOR)
    {
     /* left is bottom of tree */
     bld_ev_dces(xp->lu.x, dctp);
     break;
    }
   xp = xp->lu.x;
  }
}

/*
 * build the event control dcevnt list element(s) for one event control 
 *
 * know xp is not evor - main expr of operand of evor or wait simple expr
 * this cannot assume any itree loc. 
 *
 * for constant bit select, ID, or global do not need expr.
 * otherwise use normal variable in expr. change mechanism but before 
 * triggering armed evaluate expression and see if correct edge
 * aux dce_expr record contains previous entire expr. value
 */
static void bld_ev_dces(struct expr_t *xp, struct delctrl_t *dctp)
{
 int32 biti, bitj, e_val;
 word32 *wp;
 struct net_t *np;
 struct expr_t *endp, *ndx, *idndp;
 struct gref_t *grp;

 __cur_dce_expr = NULL;
 /* know evor must be at top and associates right (right tree) */
 e_val = NOEDGE; 
 if (xp->optyp == OPNEGEDGE || xp->optyp == OPPOSEDGE)
  {
   if (xp->optyp == OPNEGEDGE) e_val = E_NEGEDGE;
   else if (xp->optyp == OPPOSEDGE) e_val = E_POSEDGE;
   else __case_terr(__FILE__, __LINE__);

   endp = xp->lu.x;
   biti = bitj = -1;
   if (endp->optyp == LSB)
    {
     idndp = endp->lu.x;
     np = idndp->lu.sy->el.enp; 
     /* array never scalared and if not scalared need dce expr eval */
     /* this will force expr eval for array index (not bsel) */
     if (!np->vec_scalared) goto expr_edge;

     ndx = endp->ru.x;
     if (ndx->optyp == NUMBER)
      {
       /* this can be reg constant out of range of x */
       /* becomes entire range */
       wp = &(__contab[ndx->ru.xvi]);
       if (wp[1] == 0L) biti = bitj = (int32) wp[0];
      }
     else if (ndx->optyp == ISNUMBER)
      {
       __isform_bi_xvi = ndx->ru.xvi;
       biti = -2;
       bitj = 0;
      }
     else goto expr_edge;
    }
   else if (endp->optyp == ID || endp->optyp == GLBREF)
    {
     idndp = endp;
     np = idndp->lu.sy->el.enp;
     /* since using low bit only vectored wire do not need expr. */
     /* unindexed array illegal in rhs expr. */
    }
   else goto expr_edge;

   grp = (idndp->optyp == GLBREF) ? idndp->ru.grp : NULL; 
   linkon_dce(np, biti, bitj, dctp, e_val, grp);
   return;

expr_edge:
   __cur_dce_expr = (struct dce_expr_t *)
    __my_malloc(sizeof(struct dce_expr_t));
   __cur_dce_expr->edgxp = endp; 
   __cur_dce_expr->mast_dcep = NULL; 
   __cur_dce_expr->expr_ofs = 0;
   /* this will set global dce expr for each allocated in bld routine */
   bld_evxpr_dces(xp, dctp, e_val);
   __cur_dce_expr = NULL;
   return;
  }

 /* AIV 07/16/12 - always_ff must have posedge/negedge */
 if (dctp->dc_is_always_ff)
  {
   struct st_t *stp;

   stp = dctp->actionst;
   __pv_ferr(3443, "always_ff must include @(posedge/negedge) in sensitivity list - at %s:%d on %s ", __in_fils[stp->stfnam_ind], stp->stlin_cnt,
    __msgexpr_tostr(__xs, xp));
  }

 /* LOOKATME - slight bug here - trigger on variable change */
 /* instead of expression change - rare (eval. to 1 bit logical mostly) */
 /* cases where there is a difference (sending question to P1364 committee */
 /* allocate for every variable including indices in expr. */

 bld_evxpr_dces(xp, dctp, FALSE);
}

/*
 * build and link on dce vents for 1 normal not evor expression but can be
 * many dces since 1 per variable for non edge expr. that is handled here
 * need itree place since called while running
 */
static void bld_evxpr_dces(struct expr_t *xp, struct delctrl_t *dctp,
 int32 eval)
{
 struct net_t *np;
 int32 biti, bitj;
 word32 *wp;
 struct expr_t *idndp, *ndx;
 struct mda_t *mdap;
 struct gref_t *grp;

 switch (xp->optyp) {
  case GLBREF:
   idndp = xp; 
   np = xp->lu.sy->el.enp;
   linkon_dce(np, -1, -1, dctp, eval, idndp->ru.grp);
   break;
  case ID:
   idndp = xp; 
   np = xp->lu.sy->el.enp;
   linkon_dce(np, -1, -1, dctp, eval, (struct gref_t *) NULL);
   break;
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM: case OPEMPTY:
   break;
  case LSB:
   /* SJM - 07/02/00 - arrays also here if constant index makes range form */
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   ndx = xp->ru.x;
   biti = bitj = -1;
   if ((mdap = np->mda) != NULL)
    {
     /* if folded mda just make the value the fixed index */
     if (ndx->folded_ndx)
      {
       wp = &(__contab[ndx->ru.xvi]);
       if (wp[1] == 0L) biti = bitj = (int32) wp[0];
      }
    }
   else if (ndx->optyp == NUMBER)
    {
     /* know if out of range or x/z - will be all x value */
     wp = &(__contab[ndx->ru.xvi]);
     if (wp[1] == 0L) biti = bitj = (int32) wp[0];
    }
   else if (ndx->optyp == ISNUMBER)
    {
     __isform_bi_xvi = ndx->ru.xvi;
     biti = -2;
     bitj = 0;
    }
   else
    {
     /* notice for monitor and dctrl event change, variable here is legal */
     /* and implies change for index and trigger on all bits of variable */
     bld_evxpr_dces(ndx, dctp, eval);
    }
   /* SJM - 07/03/00 - for arrays need index, i.e. value but not array */
   /* index scalared - works since no way to refer to both bit and index */
   if (biti != -1 && !np->n_isarr && !np->vec_scalared) biti = bitj = -1;
   grp = (idndp->optyp == GLBREF) ? idndp->ru.grp : NULL; 
   linkon_dce(np, biti, bitj, dctp, eval, grp);
   break;
  case PARTSEL:
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   ndx = xp->ru.x;
   /* know part select never IS, will not get here if x/z or out of rng */
   biti = __contab[ndx->lu.x->ru.xvi];
   bitj = __contab[ndx->ru.x->ru.xvi];
   if (!np->vec_scalared) biti = bitj = -1;
   grp = (idndp->optyp == GLBREF) ? idndp->ru.grp : NULL; 
   linkon_dce(np, biti, bitj, dctp, eval, grp);
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   /* these must always be -1 variable must be checked at runtime */
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   grp = (idndp->optyp == GLBREF) ? idndp->ru.grp : NULL; 
   linkon_dce(np, -1, -1, dctp, eval, grp);
   break;
  case FCALL:
   {
    struct expr_t *fax;

    /* if any args of system or user functions chg, monitor triggers */
    /* notice $time function do not have arguments */
    for (fax = xp->ru.x; fax != NULL; fax = fax->ru.x)
     bld_evxpr_dces(fax->lu.x, dctp, eval);
   }
   break;
  case LCB:
   {
    struct expr_t *fax;

    for (fax = xp->ru.x; fax != NULL; fax = fax->ru.x)
     bld_evxpr_dces(fax->lu.x, dctp, eval);
   }
   break;
  default:
   if (xp->lu.x != NULL) bld_evxpr_dces(xp->lu.x, dctp, eval);
   if (xp->ru.x != NULL) bld_evxpr_dces(xp->ru.x, dctp, eval);
   break;
 } 
}

/*
 * for dces: to move from expr. reference to target where var. stored 
 *  -- if xmr, xmr ref. to target by calling xmrpush refgrp to targ(grp)
 *     [notice np is right but itree loc. wrong]
 * to move from target variable location back to expr. ref.
 *  -- if xmr, xmr target to ref cal xmrpush targ to ref(xmrtyp, npu1)
 */

/*
 * link the delay event control element for wire np
 * this builds the dcelst on np that is never removed  
 *
 * when called __inst_mod is module ref. in, (not declare in target)
 * and np is wire possibly xmr target but not itree context only mod here
 * if ref. expr is xmr, grp non nil 
 */
static void linkon_dce(struct net_t *np, int32 biti, int32 bitj,
 struct delctrl_t *dctp, int32 e_val, struct gref_t *grp)
{
 struct dcevnt_t *dcep;

 /* case 1: all xmr cases including xmr target */
 /* notice because of preprocessing never need 2 steps from target to ref */
 if (grp != NULL)
  {
   xmr_linkon_dce(np, biti, bitj, dctp, e_val, grp);
   return;
  }
 /* case 2: simple in module */
 dcep = linkon3_dce(np, biti, bitj, dctp, e_val, FALSE, __inst_mod,
  __inst_mod, TRUE, grp, NULL, NULL);
 if (dctp->dc_iact) init_iact_dce(dcep, dctp, NULL);
}

/*
 * AIV 01/25/10 - this needs a wrapper to check for wire arrays.  Wire arrays
 * are turned into vectors as seperate nets.  So it has a wire array has
 * a variable index value IE, biti == -1 it must turn on all dces for
 * all wire array net vector values
 */
static struct dcevnt_t *linkon3_dce(struct net_t *np, int32 biti, int32 bitj,
 struct delctrl_t *dctp, int32 e_val, int32 oneinst, struct mod_t *ref_mdp,
 struct mod_t *decl_mdp, int32 is_local, struct gref_t *grp, 
 struct itree_t *match_itp, struct itree_t *ref_itp)
{
 struct sy_t *syp;
 struct net_t *el_np;
 struct dcevnt_t *dcep;
 int32 i, wirarr_el_num;
   
#ifdef __XPROP__
 /* AIV 02/21/12 - need to mark these as xmr - turning off for now for xedges */
 if (!is_local) dctp->d_has_xmr = TRUE;
#endif

 /* AIV 01/25/11 - if variable wire array and biti == -1 variable index */
 if (np->n_isarr && np->ntyp < NONWIRE_ST && biti == -1) 
  {
   __last_sy2 = -1;
   wirarr_el_num = np->arr_num_els;
   /* DBG remove -- */
   if (wirarr_el_num <= 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
  
   /* alloc a work array to hold the symbols */
   if (wirarr_el_num != 0)
    {
     __wrkstab2 = (struct sy_t **)
      __my_malloc(wirarr_el_num*sizeof(struct sy_t *));
    }
   /* fill the symbols of the split wire elements */
   __fill_wire_arr_sym_wrkstab(np, decl_mdp);
  
   for (i = 0; i <= __last_sy2; i++)
    {
     syp = __wrkstab2[i];
     el_np = syp->el.enp;
     /* DBG remove -- */
     if (syp->sytyp != SYM_N) __misc_terr(__FILE__, __LINE__);
     if (!el_np->n_isarr_vector) __misc_terr(__FILE__, __LINE__);
     /* --- */
     dcep = linkon2_dce(el_np, biti, bitj, dctp, e_val, oneinst, ref_mdp,
      decl_mdp);
     /* AIV 02/08/11 - this wasn't right for the XMR case - need to setup all */
     /* XMR flags and pointers.  */
     /* AIV LOOKATME - could probably just get rid of xmr_linkon routine */
     /* since this stuff is passed down */
     /* this basically duplicates xmr_linkon_dce setting for each array element net */
     if (grp != NULL)
      {
       if (!grp->is_rooted)
        {
         if (grp->upwards_rel)
          { dcep->dceu.dcegrp = grp; dcep->dce_xmrtyp = XNP_UPXMR; }
          /* downward case */
         else { dcep->dceu.dcegrp = grp; dcep->dce_xmrtyp = XNP_DOWNXMR; }
        }
       else
        {
         dcep->dce_1inst = TRUE; 
         dcep->dce_matchu.itp = match_itp;
         dcep->dce_refu.itp = ref_itp;
         dcep->nd_chg_to_idp = TRUE;
         dcep->dce_xmrtyp = XNP_RTXMR;
        }
       /* AIV 01/26/12 - need to record XMR dcep into mod it is called in */
       add_xmr_dcep_edge_list(decl_mdp, dcep);
      }
     if (is_local) dcep->dce_xmrtyp = XNP_LOC;
    }
   if (wirarr_el_num != 0)
    {
     __my_free(__wrkstab2, wirarr_el_num*sizeof(struct sy_t *)); 
    }
  }
 dcep = linkon2_dce(np, biti, bitj, dctp, e_val, oneinst, ref_mdp,
   decl_mdp);
  if (is_local) dcep->dce_xmrtyp = XNP_LOC;
 return(dcep);
}
       
/*
 * AIV 01/26/12 - need to build a list of dce XMRs which saves the dceps which
 * might be used in a seperate module, this is need to later set
 * dce_expr->expr_ofs
 *
 * always @ (posedge (tb_top.r[2] & enable))
 */
static void add_xmr_dcep_edge_list(struct mod_t *decl_mdp, 
 struct dcevnt_t *dcep)
{
 struct dceauxlst_t *dcxlstp, *cur_hdrp;

 
 /* only add those with edges */
 if (dcep->dce_expr == NULL) return;

 dcxlstp = (struct dceauxlst_t *) __my_malloc(sizeof(struct dceauxlst_t));
 dcxlstp->ldcep = dcep;
 dcxlstp->dclnxt = NULL;
 if (decl_mdp->dcep_lst_xmrp == NULL)
  {
   decl_mdp->dcep_lst_xmrp = dcxlstp;
  }
 else
  {
   /* link on front */
   cur_hdrp =  decl_mdp->dcep_lst_xmrp;
   dcxlstp->dclnxt = cur_hdrp;  
   decl_mdp->dcep_lst_xmrp = dcxlstp;
  }
}


/*
 * fill __wrkstab2 with wire array net symbols
 * - this is just like fill_wire_arr_wrkstab in v_fx2.c but does not
 *   change net values just fills the symbols
 */
extern void __fill_wire_arr_sym_wrkstab(struct net_t *np, 
 struct mod_t *decl_mdp)
{
 int32 dim, arrwid, ri1, ri2, ndx;
 struct mda_t *mdap;
 struct sy_t *syp;
 char s1[RECLEN];

 mdap = np->mda;
 /* single dimension */
 if (mdap == NULL) 
  {
   __getarr_range(np, &ri1, &ri2, &arrwid);
   for (dim = 0; dim < arrwid; dim++)
    {
     if (ri1 < ri2) ndx = ri2 - dim;
     else ndx = ri2 + dim;

     sprintf(s1, "%s[%d]", np->nsym->synam, ndx);
     syp = __get_sym(s1, decl_mdp->msymtab);
     /* DBG remove -- */
     if (syp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---*/
     __wrkstab2[++__last_sy2] = syp;
    }
   return;
  }

 /* set the mda element nets */
 fill_mda_wire_sym_wrkstab(np, mdap, s1, 0, decl_mdp);
}

/*
 * recursive call to create a vector net for every element in a mda
 */
static void fill_mda_wire_sym_wrkstab(struct net_t *np, struct mda_t *mdap,
 char *s1, int32 dim, struct mod_t *decl_mdp)
{
 int32 ri1, ri2, tmp;
 char s2[RECLEN], s3[RECLEN];
 struct sy_t *syp;

 if (dim >= mdap->dimension) return;
   
 ri1 = mdap->rng1[dim];
 ri2 = mdap->rng2[dim];
 /* swap the ranges for the loop below */
 if (ri1 > ri2) 
  {
   tmp = ri1;
   ri1 = ri2;
   ri2 = tmp;
  }

 for (; ri1 <= ri2; ri1++)
  {
   if (dim == 0) sprintf(s2, "[%d]", ri1);
   else sprintf(s2, "%s[%d]", s1, ri1);

   /* add the lowest level dimension */
   if (dim == mdap->dimension-1)
    {
     sprintf(s3, "%s%s", np->nsym->synam, s2);
     syp = __get_sym(s1, decl_mdp->msymtab);
     /* DBG remove -- */
     if (syp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---*/
     __wrkstab2[++__last_sy2] = syp;
    }
   fill_mda_wire_sym_wrkstab(np, mdap, s2, dim+1, decl_mdp);
  }
}

/*
 * initialize interactive only dces 
 * 
 * expects inst mod to be set to module where net declared in
 * SJM 01/14/03 - LOOKATME - think there is reason need to pass grp
 *
 * SJM 05/04/05 - because putting var storage (np.nva) in .bss section
 * for cver-cc, this is only for interactive init using interpreter
 * after linking in .bss .so lib var values, now initializing by net in mod
 */
//AIV? 05-20-07 why is grp not referenced
static void init_iact_dce(struct dcevnt_t *dcep, struct delctrl_t *dctp,
 struct gref_t *grp)
{
 struct net_t *np;
 struct dceauxlst_t *dclp;
 struct mod_t *ref_mdp;

 np = dcep->dce_np;
 /* AIV 01/04/07 - init dce expr was using the wrong inst for */
 /* dce with more than one inst and was also skipping init for the */
 /* dce_expr for the one instance case */
 if (dcep->dce_expr != NULL) init_dce_exprval(dcep);
 else
  {
   if (dcep->prevval_ofs != 0)
    {
     ref_mdp = dcep_ref_mod(dcep);
     init_dce_prevval(dcep, ref_mdp);
    }
   }

 if (dctp->dc_iact)
  {
   /* add to iact list for this statement - will be linked to hctrl */  
   dclp = (struct dceauxlst_t *) __my_malloc(sizeof(struct dceauxlst_t));
   dclp->ldcep = dcep; 
   dclp->dclnxt = __iact_dcehdr;
   __iact_dcehdr = dclp;
   /* SJM 05/03/03 - LOOKATME - think iact XMR event controls converted */
   /* to per inst.  is that true? */
   dcep->iact_idp = __idp;

   /* since no dce, no loads, and no dmpvars must always turn chg store on */
   if (!np->nchg_nd_chgstore)
    {
     /* this also turn regen of net's decl iops from dce if -O on */
     __dce_turn_chg_store_on(__inst_mod, dcep, TRUE);  
    }
   /* SJM 04/14/04 - even if need chg store if dumpvars in future but that */
   /* can happen if need only has dce added from iact code and dumpvars */
   np->nchg_has_dces = TRUE;
  }
}

/*
 * routine to handle all cases where dce expr. is xmr (global ref. expr)
 * ref. in module __inst_mod - these all always one instance forms
 * notice all rooted dce xmrs are 1inst forms also npps
 */
static void xmr_linkon_dce(struct net_t *np, int32 biti, int32 bitj,
 struct delctrl_t *dctp, int32 e_val, struct gref_t *grp)
{
 int32 ii;
 struct dcevnt_t *dcep;
 struct itree_t *itp, *xmr_itp;
 struct mod_t *ref_mdp;

 /* handle xmr */
 if (!grp->is_rooted)
  {
   /* SJM 05/04/03 - for non rooted where need prev. val, must set */
   /* module instance context for any instance such as inst 0 */
   /* (many instance and do not need to know here) */
   dcep = linkon3_dce(np, biti, bitj, dctp, e_val, FALSE, grp->gin_mdp,
    grp->targmdp, FALSE, grp, NULL, NULL);

   if (grp->upwards_rel)
    { dcep->dceu.dcegrp = grp; dcep->dce_xmrtyp = XNP_UPXMR; }
   /* downward case */
   else { dcep->dceu.dcegrp = grp; dcep->dce_xmrtyp = XNP_DOWNXMR; }
   /* SJM 05/08/03 - now initialize only after complete dce built */
   if (dctp->dc_iact) init_iact_dce(dcep, dctp, grp);
   return;
  }

 /* rooted xmr handled here */
 for (ii = 0; ii < __inst_mod->flatinum; ii++)
  {
   /* itp is itree loc. of xmr reference */
   itp = __inst_mod->moditps[ii]; 
   /* reference itree loc. */
   __push_itstk(itp);
   ref_mdp = __inst_ptr->itip->imsym->el.emdp;
   /* xmr target (declared in) */
   xmr_itp = __itp_xmrget_refgrp_to_targ(grp, itp);
   __push_itstk(xmr_itp);
   /* SJM 05/06/03 - BEWARE - TOS must be def (targ) and TOS-1 must be ref */ 

   dcep = linkon3_dce(np, biti, bitj, dctp, e_val, TRUE, ref_mdp, __inst_mod,
    FALSE, grp, xmr_itp, itp);

   /* if one inst form needs xmr target (where wire decled) itree loc */
   dcep->dce_1inst = TRUE; 
   /* match is target itree loc */
   dcep->dce_matchu.itp = __inst_ptr;

   __pop_itstk();
   dcep->dce_refu.itp = __inst_ptr;
   dcep->nd_chg_to_idp = TRUE;
   /* SJM 05/07/03 - must set as rooted dce XMR */ 
   __pop_itstk();
   /* AIV 01/26/12 - need to record XMR dcep into mod it is called in */
   add_xmr_dcep_edge_list(__inst_mod, dcep);
   dcep->dce_xmrtyp = XNP_RTXMR;

   /* SJM 05/08/03 - now initialize only after complete dce built */
   if (dctp->dc_iact) init_iact_dce(dcep, dctp, grp);
  }
}

/*
 * actually link on event dce - other routines for monitor and dumpvars 
 * created dce is returned
 *
 * assumes inst mod set to declared in module context 
 *
 * if oninst, know the itree context of the one inst targed (declared in) set
 * this allocates any old value storage but does not initialize it 
 *
 * SJM 05/07/03 - now since caller for XMR sets some dce fields must only 
 * set fields here, can't call routines that use dce fields
 * this was cause of most of the XMR event control dce bugs
 */
static struct dcevnt_t *linkon2_dce(struct net_t *np, int32 biti, int32 bitj,
 struct delctrl_t *dctp, int32 e_val, int32 oneinst, struct mod_t *ref_mdp,
 struct mod_t *decl_mdp)
{
 struct dcevnt_t *dcep;
 struct dceauxlst_t *dclp;

 /* allocate, init, and fill the fields */
 dcep = __alloc_dcevnt(np);

 /* if unused for non complicated edge expression will be nil */ 
 if (__cur_dce_expr != NULL)
  {
   dcep->dce_expr = __cur_dce_expr;
   /* DBG remove -- */
   if (dcep->dce_1inst) __misc_terr(__FILE__, __LINE__);
   /* --- */
   
   /* notice for dce expr, old value only for each ref inst since */
   /* must eval expr in ref inst */
   if (__cur_dce_expr->mast_dcep == NULL)
    {
     __cur_dce_expr->mast_dcep = dcep; 
     dcep->dce_expr->expr_ofs = 0;
    }
  }

 if (biti == -1) dcep->dce_typ = DCE_INST;
 else
  {
   dcep->dce_typ = DCE_RNG_INST;
   dcep->dci1 = biti;
   if (biti == -2)
    {
     /* for one inst. form must access -2 form to actual index */
     /* because know itree context pushed for one inst - from now on not IS */
     if (oneinst)
      {
       /* SJM 10/12/04 - because contab is realloc must be index */
       dcep->dci1 = dcep->dci2.i = __contab[__isform_bi_xvi + 2*__inum];
      }
     /* since correct for direction here will be right bits */
     /* has normal user error of connecting opposite direction bus problem */
     else 
      {
       dcep->dci2.xvi = __isform_bi_xvi;
       /* AIV 03/06/08 - add IS form to tree so it can be added to idp */
       if (__compiled_sim)
        {
         __add_isnum_to_tree((void *) dcep, __isform_bi_xvi, WBITS);
        }
       }
    }  
   else dcep->dci2.i = bitj;
  }
 /* 07/01/00 - just added a dce - also need change store */
 /* 07/24/00 - has dces only on if reg for immediate propagate/wakeup */
 /* but recording bits set after here */
 if (!dctp->dc_iact)
  {
   if (np->ntyp >= NONWIRE_ST) np->nchg_has_dces = TRUE;
   np->nchg_nd_chgstore = TRUE;
  }  

 /* link onto front of d ctrl list for np */
 dcep->dcenxt = np->dcelst;
 np->dcelst = dcep;
 dcep->st_dctrl = dctp;
 if (e_val != NOEDGE)
  {
   dcep->dce_edge = TRUE;
   dcep->dce_edgval = (word32) e_val;
  }
 /* if has edge needs per inst. old value table for last value */

 /* DBG remove ---
 if (__debug_flg)
  {
   if (dctp->dc_iact) strcpy(__xs, " (interactive)");
   else strcpy(__xs, ""); 
   if (oneinst) strcat(__xs, " (xmr)");
   __dbg_msg(
    ".. ref. mod %s decl. %s adding net %s delay ctrl type %d%s ([%d:%d])\n",
    ref_mdp->msym->synam, decl_mod->msym->synam, np->nsym->synam,
    dcep->dce_typ, __xs, dcep->dci1, dcep->dci2.i);
  }
 --- */
 if (dctp->dc_iact)
  {
   /* add to iact list for this statement - will be linked to hctrl */  
   dclp = (struct dceauxlst_t *) __my_malloc(sizeof(struct dceauxlst_t));
   dclp->ldcep = dcep; 
   dclp->dclnxt = __iact_dcehdr;
   __iact_dcehdr = dclp;
   /* for after sim start iact dctrl add, know the iact itree loc set */  
   dcep->iact_idp = __idp;
  }
 return(dcep);
}

/*
 * routine to turn chg store on when new dce added but previously chg store
 * off because no dces, and no loads, and not dumpvars 
 *
 * SJM 02/08/03 - for -O this only regens any needed proc insns but
 * caller must regen the net with the new dces added - proc regen
 * is only for case where net was not compiled in proc code
 * case where
 */
extern void __dce_turn_chg_store_on(struct mod_t *in_mdp,
 struct dcevnt_t *dcep, int32 all_insts)  
{
 int32 ii;
 struct mod_t *mdp;
 struct net_t *np;
 struct itree_t *itp;
 t_midat *idp;

 if (dcep->dce_1inst)
  {
//AIV INUM FIXME
   itp = (struct itree_t *) dcep->dce_matchu.idp[MD_ITP];
   mdp = itp->itip->imsym->el.emdp;
   /* DBG remove -- */
   if (in_mdp != mdp) __misc_terr(__FILE__, __LINE__); 
   /* --- */
  }
 else if (dcep->dce_xmrtyp != XNP_LOC) mdp = dcep->dceu.dcegrp->targmdp;
 else mdp = in_mdp;
 np = dcep->dce_np;

 /* SJM 01/06/03 - fix interpreter bug since need chg store on if */
 /* net had no dces, no nlds, and dumpvars was off */
 np->nchg_nd_chgstore = TRUE;

 /* SJM 04/14/04 - for iact added dce if dumpvars and unc. need this on */
 np->nchg_has_dces = TRUE;

 if (all_insts)
  {
   /* SJM 01/06/03 - LOOKATME - is is possible to only turn on this inst? */
   for (ii = 0; ii < mdp->flatinum; ii++)
    { 
     idp = mdp->moditps[ii]->it_idp;
     idp[np->nchgaction_ofs] &= ~(NCHG_ALL_CHGED); 
    }
  }
 else 
  {
   __idp[np->nchgaction_ofs] &= ~(NCHG_ALL_CHGED);
  }
}

/*
 * allocate a delay control event record
 *
 * this assumes non XMR and non 1inst - if not caller must set
 * SJM 05/07/03 - must set net at beginning since needed by following code
 */
extern struct dcevnt_t *__alloc_dcevnt(struct net_t *np)
{ 
 struct dcevnt_t *dcep;

 dcep = (struct dcevnt_t *) __my_malloc(sizeof(struct dcevnt_t));
 dcep->dce_np = NULL;

 dcep->dce_typ = DCE_NONE;
 dcep->dce_np = np;

 dcep->dce_xmrtyp = XNP_LOC; 
 dcep->dce_1inst = FALSE;
 dcep->dce_tfunc = FALSE;
 /* SJM 07/22/00 - for re-entrant problem and vpi control off - never off */
 /* unless set by vpi (sim) control or call back entry */
 /* SJM 06/13/02 - now also interpreter always filters dce for on/off */
 /* because (f)monitor and qcaf now added during design load (prep) */
 /* for these builder must explicitlyturn off */
 dcep->dce_off = FALSE;
 dcep->is_fmon = FALSE;
 dcep->nd_chg_to_idp = FALSE;
 dcep->dce_nomonstren = TRUE; 
 dcep->dci1 = -1;
 dcep->dci2.i = -1;
 dcep->prevval_ofs = 0;
 dcep->pli_prevval.wp = NULL;
 dcep->dce_edge = FALSE;
 dcep->dce_edgval = NOEDGE;
 dcep->st_dctrl = NULL;
 dcep->dceu.dcegrp = NULL;
 dcep->dceu2.dce_fmon = NULL;
 dcep->dce_matchu.idp = NULL;
 dcep->dce_refu.idp = NULL; 
 dcep->iact_idp = NULL;
 dcep->dcenxt = NULL;
 dcep->dce_expr = NULL;
 dcep->dce_ndx = -1;
 dcep->didp = NULL;
 dcep->merged_dces = NULL;
 dcep->merged_count = -1;
 dcep->merged = FALSE;
 dcep->is_loaded = FALSE;
 dcep->is_printed = FALSE;
 return(dcep);
}

/*
 * prepare a disable inside a function by setting to next statement to goto
 * inside function disable are like c continue and are just gotos
 */
static void prep_func_dsable(struct st_t *stp)
{
 int32 i;
 struct expr_t *dsxp;
 struct sy_t *syp;
 struct task_t *dsatskp;

 dsxp = stp->st.sdsable.dsablx;
 syp = dsxp->lu.sy; 
 /* disable of func. indicated by nil next statmenet - use fcall stack */
 if (syp->sytyp == SYM_F)
  {
   stp->st.sdsable.func_nxtstp = NULL;
   return;
  }

 /* must be disabling named block */
 if (syp->sytyp != SYM_LB || syp->el.etskp->tsktyp == FORK
  || dsxp->optyp == GLBREF) __misc_sgfterr(__FILE__, __LINE__);
 dsatskp = syp->el.etskp;
 /* know every named block when entered in function name block is stacked */
 for (i = __nbsti; i >= 0; i--)
  {
   if (__nbstk[i]->st.snbtsk == dsatskp)
    {
     /* this can be nil */
     stp->st.sdsable.func_nxtstp = __nbstk[i]->stnxt;
     return;
    }
  }
 /* know always enclosing, or will not get here - earlier error */
 __case_terr(__FILE__, __LINE__);
}

/*
 * return T if disable targsyp above cursytp 
 * i.e. is upward break type disable
 * if any named block on path sets nbonpath to T
 *
 * because of xmr disabling of named begin-end blocks need thread so cannot
 * use goto except inside function
 */
extern int32 __is_upward_dsable_syp(struct sy_t *targsyp,
 struct symtab_t *cursytp, int32 *nbonpath)
{
 struct symtab_t *sytp;
 struct sy_t *syp;

 *nbonpath = FALSE;
 if (targsyp->sytyp != SYM_LB) return(FALSE); 
 /* notice top of upward chain will be module, but disable of module */
 /* illegal so will return match top of chain module */
 for (sytp = cursytp; sytp != NULL; sytp = sytp->sytpar) 
  {
   syp = sytp->sypofsyt;
   if (targsyp == syp) return(TRUE);
   if (syp->sytyp == SYM_LB) *nbonpath = TRUE;
  }
 return(FALSE);
}

/*
 * FORCE/ASSIGN/MONITOR PREPARATION ADD DCE ROUTINES
 */

/*
 * for qcaf stmts, build the per lhs cat element 
 * for reg per cat component dce lists are per inst and for wire
 * they are per bit of cat expr per inst
 */
static void bld_init_qcaf_dce_lstlst(struct st_t *stp)
{
 int32 ii;
 int32 ibase;
 struct expr_t *lhsx;
 struct expr_t *catndp, *catlhsx;
 struct dceauxlstlst_t *dcllp, *end_dcllp;
 struct mod_t *cur_mdp;
 
 lhsx = stp->st.sqca->qclhsx;
 /* AIV 04/02/09 - since can get here from interactive debugger need get mod */
 if (__idp == NULL) cur_mdp =  __inst_mod;
 else cur_mdp = get_inst_mod_();

 if (lhsx->optyp != LCB)
  {
   /* one list of peri lists */
   dcllp = (struct dceauxlstlst_t *)
    __my_malloc(sizeof(struct dceauxlstlst_t)); 
   stp->st.sqca->rhs_qcdlstlst = dcllp;
   if (stp->st.sqca->regform)
    {
     /* for reg list field is peri table of dce lists - starting at empty */
     dcllp->dcelsttab = (struct dceauxlst_t **)
      __my_malloc(cur_mdp->flatinum*sizeof(struct dceauxlst_t *));
     
     for (ii = 0; ii < cur_mdp->flatinum; ii++) 
      dcllp->dcelsttab[ii] = NULL; 
    }
   else
    {
     /* for wire list field is peri/bit tab of dce lists - starts at empty */
     ibase = cur_mdp->flatinum*lhsx->szu.xclen;
     dcllp->dcelsttab = (struct dceauxlst_t **)
      __my_malloc(ibase*sizeof(struct dceauxlst_t *));
     for (ii = 0; ii < ibase; ii++) dcllp->dcelsttab[ii] = NULL; 
    }
   /* since non concat, only one element */
   dcllp->dcelstlstnxt = NULL;
  } 
 else
  {
   end_dcllp = NULL;
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     catlhsx = catndp->lu.x;

     /* allocate list of peri lists element */
     dcllp = (struct dceauxlstlst_t *)
      __my_malloc(sizeof(struct dceauxlstlst_t)); 
     if (end_dcllp == NULL) stp->st.sqca->rhs_qcdlstlst = dcllp;
     else end_dcllp->dcelstlstnxt = dcllp;
     end_dcllp = dcllp;

     if (stp->st.sqca->regform)
      {
       /* reg list field is peri table of dce lists - starting at empty */
       dcllp->dcelsttab = (struct dceauxlst_t **)
        __my_malloc(cur_mdp->flatinum*sizeof(struct dceauxlst_t *));
       for (ii = 0; ii < cur_mdp->flatinum; ii++) 
        dcllp->dcelsttab[ii] = NULL; 
      }
     else
      {
       ibase = cur_mdp->flatinum*catlhsx->szu.xclen;
       /* if not list end, next pass will set */
       dcllp->dcelsttab = (struct dceauxlst_t **)
        __my_malloc(ibase*sizeof(struct dceauxlst_t *));
       for (ii = 0; ii < ibase; ii++) dcllp->dcelsttab[ii] = NULL; 
      }
     dcllp->dcelstlstnxt = NULL;
    }
  }
}

/*
 * prepare a quasi-continuous assign or force of reg (same as qc assign)
 * this is for both reg force and reg assign
 *
 * SJM 06/14/02 - same as old exec qc assign for each inst but at prep time
 * to build and fill d.s
 */
static void prep_qc_assign(struct st_t *stp, int32 is_force)
{
 struct expr_t *catndp;
 struct dceauxlstlst_t *dcllp;
 struct expr_t *lhsx, *catlhsx;
 struct dceauxlst_t *qcdep;

 /* first evaluate rhs */
 lhsx = stp->st.sqca->qclhsx;
 /* only possibilities are concat and ID */
 /* this builds and initializes the reg assign/frc qcval records */ 
 if (lhsx->optyp != LCB)
  {
   if (is_force) qcdep = prep_noncat_qc_regforce(stp, lhsx);
   else qcdep = prep_noncat_qc_assign(stp, lhsx);
   /* only one list of lists element since not lhs concat */
   stp->st.sqca->rhs_qcdlstlst->dcelsttab[__inum] = qcdep;
  }
 else
  {
   /* concatenate case know lhs entire var */
   dcllp = stp->st.sqca->rhs_qcdlstlst;
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x,
    dcllp = dcllp->dcelstlstnxt)
    {
     catlhsx = catndp->lu.x;
     if (is_force) qcdep = prep_noncat_qc_regforce(stp, catlhsx);
     else qcdep = prep_noncat_qc_assign(stp, catlhsx);
     dcllp->dcelsttab[__inum] = qcdep;
     /* AIV 08/13/08 - need to add this expr because these are passed to asl */
     /* wasn't handling the concat case */
     if (__compiled_sim)
      {
       __add_expr_totable(catlhsx);
      }
    }
  }
}

/*
 * prepare a quasi-continuous deassign (same as old exec but at per/inst now)
 * inverse of assign and reg only defined for regs
 */
static void prep_qc_deassign(struct st_t *stp)
{
 int32 nd_itpop;
 struct expr_t *catndp;
 struct expr_t *lhsx, *catlhsx;
 struct net_t *np;
 struct gref_t *grp;
 struct itree_t *targ_itp;

 /* SJM 07/19/02 - was wrongly accessing qconta not qcontdea record */
 lhsx = stp->st.sqcdea.qcdalhs;
 /* only possibilities are concat and ID */
 if (lhsx->optyp != LCB)
  {
   /* just need to alloc qcval records here - dce list built from assgn */
   np = lhsx->lu.sy->el.enp;
   /* SJM 05/23/03 - must alloc in context of XMR */
   if (lhsx->optyp == GLBREF)
    {
     grp = lhsx->ru.grp;
     targ_itp = __itp_xmrget_refgrp_to_targ(grp, __inst_ptr);
     __push_itstk(targ_itp);
     nd_itpop = TRUE;
    }
   else nd_itpop = FALSE;

   if (np->nu2.qcval == NULL) __alloc_qcval(np);

   if (nd_itpop) __pop_itstk();
  }
 else
  {
   /* concatenate case know lhs full wire - tricky extractions of rhs */
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     catlhsx = catndp->lu.x;
     np = catlhsx->lu.sy->el.enp;
     /* SJM 05/23/03 - must alloc in context of XMR */
     if (lhsx->optyp == GLBREF)
      {
       grp = lhsx->ru.grp;
       targ_itp = __itp_xmrget_refgrp_to_targ(grp, __inst_ptr);
       __push_itstk(targ_itp);
       nd_itpop = TRUE;
      }
     else nd_itpop = FALSE;

     /* AIV 12/06/07 - need to add this expr because these are passed to asl */
     /* wrappers and must be linked for +load_solib */
     if (__compiled_sim)
      {
       __add_expr_totable(catlhsx);
      }
     if (np->nu2.qcval == NULL) __alloc_qcval(np);

     if (nd_itpop) __pop_itstk();
    }
  }
}

/*
 * prep quasi continuous assign for one expr in one inst.
 *
 * know lhs always entire register - no assign for wires - lhs can be xmr 
 * this is called for every inst of module tha contains stmt
 * LOOKATME - do not need stmt since can get from qcval already built
 */
static struct dceauxlst_t *prep_noncat_qc_assign(struct st_t *qcstp,
 struct expr_t *lhsx)
{
 int32 nd_itpop;
 struct net_t *np;
 struct qcval_t *assgn_qcp;
 struct gref_t *grp;
 struct itree_t *targ_itp;

 /* SJM 05/29/03 - must allocate and find qcval rec from lhs itree loc */
 nd_itpop = FALSE;
 if (lhsx->optyp == GLBREF)
  {
   grp = lhsx->ru.grp;
   targ_itp = __itp_xmrget_refgrp_to_targ(grp, __inst_ptr);
   __push_itstk(targ_itp);
   nd_itpop = TRUE;
  }
 else if (lhsx->optyp != ID) __case_terr(__FILE__, __LINE__);

 np = lhsx->lu.sy->el.enp;
 if (np->nu2.qcval == NULL) __alloc_qcval(np);
 assgn_qcp = &(np->nu2.qcval[2*__inum + 1]);

 /* add qcaf from soruce location of statment */
 if (nd_itpop) __pop_itstk();

 /* SJM 05/29/03 - must build the qcaf dce in reference not declare context */ 
 __qcaf_dcehdr = NULL;
 /* for constant rhs this can be nil */
 bld_qcaf_dces(qcstp->st.sqca->qcrhsx, assgn_qcp);

 return(__qcaf_dcehdr);
}


/*
 * prepare the quasi continuous force for reg variables - just alloc qcval rec
 *
 * know lhs always entire register
 * lhs here can be xmr 
 * force of entire reg only overrides possible active reg assign
 */
static struct dceauxlst_t *prep_noncat_qc_regforce(struct st_t *qcastp,
 struct expr_t *lhsx)
{
 int32 nd_itpop;
 struct net_t *np;
 struct qcval_t *frc_qcp; 
 struct gref_t *grp;
 struct itree_t *targ_itp;

 nd_itpop = FALSE;
 /* 05/28/03 - must get fource qc record ptr from lhs decl itree loc */
 if (lhsx->optyp == GLBREF)
  {
   grp = lhsx->ru.grp;
   targ_itp = __itp_xmrget_refgrp_to_targ(grp, __inst_ptr);
   __push_itstk(targ_itp);
   nd_itpop = TRUE;
  }
 else if (lhsx->optyp != ID) __case_terr(__FILE__, __LINE__);

 np = lhsx->lu.sy->el.enp;
 /* DBG remove -- */
 if (!np->frc_assgn_allocated) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (np->nu2.qcval == NULL) __alloc_qcval(np);
 frc_qcp = &(np->nu2.qcval[2*__inum]);

 /* 05/28/03 - but must bld qcaf dces in ref itree context */
 if (nd_itpop) __pop_itstk();

 __qcaf_dcehdr = NULL;
 /* for constant rhs thsi can be nil */
 bld_qcaf_dces(qcastp->st.sqca->qcrhsx, frc_qcp);

 return(__qcaf_dcehdr);
}

/*
 * allocate a new qc assign value aux. record
 * itree location must be set before calling here since needs to know mod in
 *
 * SJM 12/21/02 - this is per inst of mod net declared in when called as XMR
 */
extern void __alloc_qcval(struct net_t *np)
{
 int32 i;
 struct qcval_t *qcvalp;
 struct mod_t *mdp;

 /* AIV 04/18/07 - need to use __idp here can be accessed at run time */
 /* SJM 08-10-07 - can be called during prep before any idp area and */
 /* for PLI from run time */
 if (__inst_mod == NULL) mdp = get_inst_mod_();
 else mdp = __inst_mod;

 /* AIV 03/09/05 - if force from vpi bit needs to be set */
 np->frc_assgn_allocated = TRUE;
 if (np->ntyp >= NONWIRE_ST)
  {
   /* here need 1 qcval per inst. but need 1 for assign and 1 for force */
   np->nu2.qcval = (struct qcval_t *)
    __my_malloc(2*mdp->flatinum*sizeof(struct qcval_t));
  
   qcvalp = np->nu2.qcval;
   for (i = 0; i < 2*mdp->flatinum; i++, qcvalp++) init_qcval(qcvalp);
  }
 else
  {
   /* here need 1 per inst bit product */
   /* LOOKATME - could have 1 bit per inst. for vectored wires */ 
   np->nu2.qcval = (struct qcval_t *)
    __my_malloc(mdp->flatinum*np->nwid*sizeof(struct qcval_t));
   qcvalp = np->nu2.qcval;
   for (i = 0; i < mdp->flatinum*np->nwid; i++, qcvalp++)
    init_qcval(qcvalp);
  }
}

/*
 * allocate a qcval record
 */
static void init_qcval(struct qcval_t *qcvalp) 
{
 qcvalp->qc_active = FALSE;
 qcvalp->qc_overridden = FALSE;
 qcvalp->qcstp = NULL;
 qcvalp->qcrhsbi = -1;
 qcvalp->qclhsbi = -1;
 qcvalp->lhsidp = NULL;
 qcvalp->qcdcep = NULL;
}

/*
 * QUASI CONTINUOUS WIRE FORCE/RELEASE PREP ROUTINES 
 */

/*
 * prepare quasi-continuous force on a wire
 * possibilities here are wire, constant bit select, part select
 * also concat of above
 * wire must be scalared and everything decomposed to bits
 */
static void prep_qc_wireforce(struct st_t *stp)
{
 struct expr_t *catndp;
 struct dceauxlstlst_t *dcllp;
 struct expr_t *lhsx, *catlhsx;

 /* first evaluate rhs */
 lhsx = stp->st.sqca->qclhsx;
 /* only possibilities are concat and ID */
 /* this builds and initializes the reg assign/frc qcval records */ 
 if (lhsx->optyp != LCB)
  {
   prep_noncat_qc_wireforce(stp, lhsx, stp->st.sqca->rhs_qcdlstlst);
  }
 else
  {
   /* concatenate case know lhs full wire - tricky extractions of rhs */
   dcllp = stp->st.sqca->rhs_qcdlstlst;
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x,
    dcllp = dcllp->dcelstlstnxt)
    {
     catlhsx = catndp->lu.x;
     prep_noncat_qc_wireforce(stp, catlhsx, dcllp);
     /* AIV 03/02/12 - the compiler is only loading the exprs for concats now */
     /* AIV 12/06/07 - need to add this expr because these are passed to asl */
     /* wrappers and must be linked for +load_solib */
     if (__compiled_sim)
      {
       __add_expr_totable(catlhsx);
      }
    }
  }
}

/*
 * prepare a quasi-continuous release - only decomposes into lhs exprs
 * only scalared wires or selects or cats not regs
 * wire force/release is one level only
 * called in itree context of release stmt 
 * 
 * 06/24/02 - wire release just alloc qcvals for all nets so it must
 * decompose into cat elements to get net - for wire all bits need
 * qcval even if only some can be forced/released 
 */
static void prep_qc_wirerelease(struct st_t *stp)
{
 struct expr_t *catndp;
 struct expr_t *lhsx, *catlhsx;

 lhsx = stp->st.sqcdea.qcdalhs; 
 /* only possibilities are concat and ID */
 if (lhsx->optyp != LCB) prep_noncat_qc_wirerelease(lhsx);
 else
  {
   /* concatenate case know lhs full wire - tricky extractions of rhs */
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    { 
     catlhsx = catndp->lu.x; 
     prep_noncat_qc_wirerelease(catlhsx); 
     /* AIV 12/06/07 - need to add this expr because these are passed to asl */
     /* wrappers and must be linked for +load_solib */
     if (__compiled_sim)
      {
       __add_expr_totable(catlhsx);
      }
    }
  }
}
/*
 * after possible concat unwinding, prepare wire force
 *
 * wire force is bit by bit unless vectored wire (when only entire wire)
 *
 * force which is for debugging overrides any wire delay assign
 * when wire change happens (wire event process) if force active, no assign
 * rhsbi is low bit of possible rhs section select (0 for not concat)
 * this is called with stmt itree loc even if lhs xmr and handled push/pop
 *
 * SJM 11/14/00 - tran channel (inout port) force now is separate routine
 * LOOKATME - think could simplify since for wire force always one bit
 *
 * sjm 12/21/02 - attached to statement so dcllp element must use stmt
 * itree inst loc even for XMR lhs expr
 */
static void prep_noncat_qc_wireforce(struct st_t *qcfstp, struct expr_t *lhsx,
 struct dceauxlstlst_t *dcllp)
{
 int32 bi, xbi, ibase;
 int32 biti, bitj;
 struct qcval_t *frc_qcp;
 struct net_t *np;
 struct itree_t *itp;

 /* step 1: get the wire range */
 /* for psel or vector, range is biti down to bitj - for scalar 0,0 */
 /* this computes any xmr new itp but does not push it - nil if not XMR */
 prep_get_qc_wirrng(lhsx, &np, &biti, &bitj, &itp); 

 /* for tran channel wire, no dces - forcing wire forces channel */
 /* LOOKATME - think no need also no need for qcvals */

 /* SJM 07/19/02 - for lhs xmr need target itree loc */
 /* rest needs possible lhs xmr itree context including qcval alloc */
 if (itp != NULL) __push_itstk(itp);

 /* allocate the qcval record for wire if not yet alloced */
 /* also needed for tran channel force */
 /* for XMR attached net per inst values are from pushed defined in mod */
 if (np->nu2.qcval == NULL) __alloc_qcval(np);

 /* 05/28/03 - need to get per bit frc qc record from lhs decl itree cntxt */ 
 ibase = __inum*np->nwid;
 if (itp != NULL) __pop_itstk();

 if (np->ntraux != NULL) return;

 for (bi = bitj, xbi = 0; bi <= biti; bi++, xbi++)
  {
   /* for normal add dces for every bit */
   frc_qcp = &(np->nu2.qcval[ibase + bi]);

   __qcaf_dcehdr = NULL;
   /* for constant rhs thsi can be nil */
   /* LOOKATME-could decompose lhs-rhs bit but rare and speed non-critical */
   bld_qcaf_dces(qcfstp->st.sqca->qcrhsx, frc_qcp);

   /* SJM 12/22/02 - per inst here is stmt when lhs XMR */ 
   dcllp->dcelsttab[__inum*lhsx->szu.xclen + xbi] = __qcaf_dcehdr;
  }
}

/*
 * after possible concat unwinding, prepare lhs expr release
 * just allocs qcval if needed in case seen before force
 */
static void prep_noncat_qc_wirerelease(struct expr_t *lhsx)
{
 int32 biti, bitj;
 struct net_t *np;
 struct itree_t *itp;
 
 /* get the wire range - using common routine but only need net here */
 prep_get_qc_wirrng(lhsx, &np, &biti, &bitj, &itp); 

 /* SJM 07/19/02 - for lhs xmr need target itree loc */
 /* rest needs possible lhs xmr itree context including qcval alloc */
 if (itp != NULL) __push_itstk(itp);

 /* allocate the qcval record for wire in case see release before force */
 if (np->nu2.qcval == NULL) __alloc_qcval(np);

 if (itp != NULL) __pop_itstk();
}

/*
 * prep time version of get qc wire element (after lhs concat separation) 
 * this sets needed itree loc. to itpp, also sets wire, and range 
 *
 * for prep where there is not yet any dce but itree stack available
 */
static void prep_get_qc_wirrng(struct expr_t *lhsx, struct net_t **nnp,
 int32 *biti, int32 *bitj, struct itree_t **itpp)
{
 int32 nd_itpop;
 word32 *wp;
 struct gref_t *grp;
 struct net_t *np;
 struct expr_t *idndp, *ndx;
 struct itree_t *targ_itp;

 *itpp = NULL; 
 nd_itpop = FALSE;
 np = NULL;
 switch (lhsx->optyp) {
  case GLBREF:
   grp = lhsx->ru.grp;
   targ_itp = __itp_xmrget_refgrp_to_targ(grp, __inst_ptr);
   __push_itstk(targ_itp);
   nd_itpop = TRUE;
   /* FALLTHRU */
  case ID:
   np = lhsx->lu.sy->el.enp;
   *biti = np->nwid - 1;
   *bitj = 0;
   break;
  case LSB: case PARTSEL:
   idndp = lhsx->lu.x;
   if (idndp->optyp == GLBREF)
    {
     grp = idndp->ru.grp;
     targ_itp = __itp_xmrget_refgrp_to_targ(grp, __inst_ptr);
     __push_itstk(targ_itp);
     nd_itpop = TRUE;
    }
   np = idndp->lu.sy->el.enp;
   /* know error before here if non in range constant value */ 
   if (lhsx->optyp == LSB) *bitj = *biti = __get_itp_const_bselndx(lhsx);
   else
    {
     ndx = lhsx->ru.x->lu.x;
     wp = &(__contab[ndx->ru.xvi]);
     *biti = wp[0];
     ndx = lhsx->ru.x->ru.x;
     wp = &(__contab[ndx->ru.xvi]);
     *bitj = wp[0];
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (nd_itpop) { *itpp = __inst_ptr;  __pop_itstk(); }
 *nnp = np;
}

/*
 * ROUTINES TO SETUP QUASI-CONTINOUS ASSIGN STORE AND DCE LIST
 */

/*
 * build and link on special qc assign/force rhs simple dce
 * xp is rhs expr and called from itree loc. where exec qc assign
 */
static void bld_qcaf_dces(struct expr_t *xp, struct qcval_t *qcvalp)
{
 word32 *wp;
 struct net_t *np;
 int32 biti, bitj;
 struct expr_t *idndp, *ndx;
 struct expr_t *fax;
 
 switch (xp->optyp) {
  case GLBREF:
   idndp = xp; 
   /* for global - do not need ref. point - just link on 1 (because only 1 */
   /* monit call from 1 inst.) target wire */
   biti = bitj = -1;
glb_dce:
   np = idndp->lu.sy->el.enp;
   linkon_qcaf_dce(np, biti, bitj, idndp->ru.grp, qcvalp);
   break;
  case ID:
   idndp = xp; 
   np = xp->lu.sy->el.enp;
   linkon_qcaf_dce(np, -1, -1, (struct gref_t *) NULL, qcvalp);
   break;
  /* SJM 05/18/00 - must do nothing for reals */ 
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM: case OPEMPTY:
   return;
  case LSB:
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   ndx = xp->ru.x;
   /* for monits, any reg or non scalaraed wire must trigger on any chg */
   if (ndx->optyp == NUMBER)
    {
     wp = &(__contab[ndx->ru.xvi]);
     if (wp[1] != 0L) biti = -1; else biti = (int32) wp[0];
    }
   else if (ndx->optyp == ISNUMBER)
    {
     wp = &(__contab[ndx->ru.xvi]);
     wp = &(wp[2*__inum]);
     /* need length for IS number because can be wider - but get low */
     if (wp[1] != 0L) biti = -1; else biti = (int32) wp[0];
    }
   else
    {
     /* notice for monitor and dctrl event change, variable here is legal */
     /* and implies change for index and trigger on all bits of variable */
     bld_qcaf_dces(ndx, qcvalp);
     biti = -1;
    }
   bitj = biti;
   if (biti != -1 && !np->vec_scalared) biti = bitj = -1;
   if (idndp->optyp == GLBREF) goto glb_dce;
   linkon_qcaf_dce(np, biti, biti, (struct gref_t *) NULL, qcvalp);
   break;
  case PARTSEL:
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   ndx = xp->ru.x;
   /* know part select never IS */
   biti = __contab[ndx->lu.x->ru.xvi];
   bitj = __contab[ndx->ru.x->ru.xvi];
   if (!np->vec_scalared) biti = bitj = -1;
   if (idndp->optyp == GLBREF) goto glb_dce;
   linkon_qcaf_dce(np, biti, bitj, (struct gref_t *) NULL, qcvalp);
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   ndx = xp->ru.x;
   /* these must always be -1 variable must be checked at runtime */
   linkon_qcaf_dce(np, -1, -1, (struct gref_t *) NULL, qcvalp);
   break;
  case FCALL:
   /* if any arguments of system or user functions change, monitor triggers */
   /* notice $time function do not have arguments */
   for (fax = xp->ru.x; fax != NULL; fax = fax->ru.x)
    bld_qcaf_dces(fax->lu.x, qcvalp);
   break;
  case LCB:
   for (fax = xp->ru.x; fax != NULL; fax = fax->ru.x)
    bld_qcaf_dces(fax->lu.x, qcvalp);
   break;
  default:
   if (xp->lu.x != NULL) bld_qcaf_dces(xp->lu.x, qcvalp);
   if (xp->ru.x != NULL) bld_qcaf_dces(xp->ru.x, qcvalp);
   break;
 } 
}

/*
 * link on a special (simplified) qc assign/force dce rhs load
 * caller must decompose any scalared wire part selects into bit selects
 * before here
 * -2 IS form impossible since any one inst. IS form converted to constant
 * before here
 *
 * this must be called from source reference location of the qc stmt 
 *
 * notice never a need for an old value since better to just re-eval assign
 * this goes on front but after any DMPV 
 */
static void linkon_qcaf_dce(struct net_t *np, int32 biti, int32 bitj,
 struct gref_t *grp, struct qcval_t *qcvalp)
{
 int32 nd_itpop;
 struct itree_t *ref_itp;
 struct dcevnt_t *dcep;
 struct dceauxlst_t *dclp;
 struct itree_t *targ_itp;

 ref_itp = __inst_ptr;
 nd_itpop = FALSE;
 if (grp != NULL) 
  { 
   targ_itp = __itp_xmrget_refgrp_to_targ(grp, __inst_ptr);
   __push_itstk(targ_itp);
   nd_itpop = TRUE; 
  }
 /* allocate, init, and fill the fields */
 dcep = __alloc_dcevnt(np);
 /* AIV 02/19/07 - need to link dcep for qcaf for now until lowered */
 if (__compiled_sim) __add_dcep_to_table(np, dcep);
 if (biti == -1) dcep->dce_typ = DCE_QCAF;
 else
  {
   dcep->dce_typ = DCE_RNG_QCAF;
   dcep->dci1 = biti;
   dcep->dci2.i = bitj;
  }
 dcep->dce_np = np;
 /* dce's start out on so must explicitly turn prep time built qc off here */
 dcep->dce_off = TRUE;

 /* link this on front */
 dcep->dcenxt = np->dcelst;
 np->dcelst = dcep;

 /* set ref. itree location - since dcep on target */
 dcep->dce_1inst = TRUE;
 dcep->dce_matchu.itp = __inst_ptr;
 dcep->dce_refu.itp = ref_itp;
 dcep->nd_chg_to_idp = TRUE;
 /* SJM 07/19/02 needed to make sure chg form iops get gened */ 
 np->nchg_nd_chgstore = TRUE;

 /* also set unused fmon field to qcval for bit or wire if reg */
 dcep->dceu2.dce_qcvalp = qcvalp;

 /* then link on undo/chg list */
 dclp = (struct dceauxlst_t *) __my_malloc(sizeof(struct dceauxlst_t));
 dclp->ldcep = dcep; 
 dclp->dclnxt = __qcaf_dcehdr;
 __qcaf_dcehdr = dclp;

 /* SJM 06/23/04 ### ??? - without regen is this needed? */
 /* SJM 02/06/03 - may have npps but not dces so must turn this on */
 /* since nchg nd chgstore on, know nchg action right */
 if (np->ntyp >= NONWIRE_ST) np->nchg_has_dces = TRUE;

 if (nd_itpop) __pop_itstk();
}

/*
 * add a npp to the compile load list
 */
extern void __add_dcep_to_table(struct net_t *np, struct dcevnt_t *dcep)
{
 struct dce_info_t *dceip;

 dceip = np->dcetable;
 if (dceip == NULL)
  {
   dceip = (struct dce_info_t *) __my_malloc(sizeof(struct dce_info_t));
   dceip->size = 10;
   dceip->dtable = (struct dcevnt_t **) 
    __my_malloc(dceip->size*sizeof(struct dcevnt_t *));
   dceip->ndx = -1;
   np->dcetable = dceip; 
  }
 if (++dceip->ndx == dceip->size)
  {
   grow_dce_table(dceip);
  }
 dceip->dtable[dceip->ndx] = dcep;
 dcep->dce_ndx = dceip->ndx;
}

/*
 * grow the dce table
 */
static void grow_dce_table(struct dce_info_t *dceip)
{
 size_t osize, nsize;

 osize = dceip->size*sizeof(struct dcevnt_t *);
 dceip->size = (3*dceip->size)/2; 
 nsize = dceip->size*sizeof(struct dcevnt_t *);
 dceip->dtable = (struct dcevnt_t **) __my_realloc(dceip->dtable, osize, nsize);
}

/*
 * XMR VARIABLE PREPARATION ROUTINES
 */

/*
 * prepare xmrs - allocate per inst. storage and set itree pointers
 *
 * no itree context here - must use explicit itree locs
 */
extern void __prep_xmrs(void)
{
 int32 gri, ii;
 struct mod_t *mdp;
 struct gref_t *grp;
 struct itree_t *itp;

 /* first process rooted and count upward rel. in static tree */
 __num_uprel_glbs = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (gri = 0, grp = &(mdp->mgrtab[0]); gri < mdp->mgrnum; gri++, grp++)
    {
     /* DBG remove - if any gr_err should not get here */
     if (grp->gr_err) __misc_terr(__FILE__, __LINE__);
     if (grp->gr_gone) continue;

     /* if guessed wrong xmr from used in instance argument loc., undo */
     /* if rooted set root target itp */ 
     if (grp->is_rooted)
      {
       /* find itree root corresponding to root path staring module name */
       /* never constant inst array select */
       if ((ii = __ip_indsrch(grp->grcmps[0]->synam)) == -1)
	__misc_gfterr(__FILE__, __LINE__, grp->grfnam_ind, grp->grflin_cnt);
       itp = __it_roots[ii];

       if (grp->last_gri != 0)
        grp->targu.targitp = __find_unrt_targitp(grp, itp, 1);
       /* one component rooted, so already have itp */
       else grp->targu.targitp = itp;

       /* must mark module as containing rooted gref */
       /* and first rooted gref - allocate flatinum style itree table */
       continue;
      }
     /* notice one uprel xmr has flatinum number in itree */
     if (grp->upwards_rel)
      {
       /* setting of inst. selects in upward rels, handled elsewhere */
       __num_uprel_glbs += mdp->flatinum; 
       process_upwards_grp(grp);
       continue;
      }
     /* for downward relative with array of inst. selects must check ranges */
     if (grp->path_has_isel) chk_downrel_inst_sels(grp);
    }
  }
} 

/*
 * fill grp targ field for rooted grp and uprel itps tabl for upward rel
 * called for interactive and delay setting run time xmr eval only
 */
extern void __fill_grp_targu_fld(struct gref_t *grp)
{
 int32 ii;
 struct itree_t *itp2;

 if (grp->gr_err || grp->gr_gone) return;

 /* if rooted set root target itp */ 
 if (grp->is_rooted)
  {
   /* find itree root corresponding to root path staring module name */
   if ((ii = __ip_indsrch(grp->grcmps[0]->synam)) == -1)
    __misc_gfterr(__FILE__, __LINE__, grp->grfnam_ind, grp->grflin_cnt);
   itp2 = __it_roots[ii];
   /* may be rooted and in top module */
   if (grp->last_gri != 0)
     grp->targu.targitp = __find_unrt_targitp(grp, itp2, 1);
   else grp->targu.targitp = itp2;
   return;
  }
 /* since never more than 1 inst. of interactive scope, up from current */
 /* scope - this implies must always reparse interactive statements */
 /* SJM 09/15/00 - this fills the per ref. indexed targ itps table */
 if (grp->upwards_rel) process_upwards_grp(grp);
}

/*
 * process upward relative gref by building downward reverse of upward
 * path to first above module of matching type
 *
 * rule is go upward until find matching 0th component type, then down
 * this is needed because for inst. upward distance may be different
 * because inst array pound param range types copied before defparam
 * splitting, first upward rel. first component symbol will be right split off
 */
static void process_upwards_grp(struct gref_t *grp)
{
 int32 ii;
 struct mod_t *imdp, *up_mdp, *mast_imdp, *up_mast_mdp;
 struct itree_t *in_itp, *up_itp, *titp;
 struct inst_t *ip;
 struct sy_t *syp;
 struct itree_t **uprelitps;

 /* notice for upward relative, first component is module type not inst */  
 syp = grp->grcmps[0];
 /* DBG remove - upward relative xmr head not module type */
 if (syp->sytyp != SYM_M)
  __misc_gfterr(__FILE__, __LINE__, grp->grfnam_ind, grp->grflin_cnt);
 /* -- */

 uprelitps = (struct itree_t **)
  __my_malloc(grp->gin_mdp->flatinum*sizeof(struct itree_t *));
 grp->targu.uprel_itps = uprelitps;

 /* for upward distance is per inst. variable - up to find target mod */
 up_mdp = syp->el.emdp;
 up_mast_mdp = __get_mast_mdp(up_mdp);
 for (ii = 0; ii < grp->gin_mdp->flatinum; ii++)
  {
   in_itp = grp->gin_mdp->moditps[ii];

   for (up_itp = in_itp;;)
    {
     if (up_itp == NULL)
      {
       __gferr(981, grp->grfnam_ind, grp->grflin_cnt,
        "unqualified use of upward relative task/func %s illegal - matched upward relative task/func undefined above instance %s",
        grp->gnam, __msg2_blditree(__xs, in_itp)); 
       return;
      }

     /* upward xmr reference no matching type above */
     ip = up_itp->itip;
     imdp = ip->imsym->el.emdp;
     mast_imdp = __get_mast_mdp(imdp);
     /* DBG remove --
     __dbg_msg("upwards rel: %s: first comp=%s, current mdp: %s(%s)=%d\n",
      grp->gnam, up_mast_mdp->msym->synam, mast_imdp->msym->synam,
      ip->isym->synam, up_itp->itinum);
     -- */
     if (mast_imdp == up_mast_mdp) break;
     up_itp = up_itp->up_it;
    }
   /* next trace down from upward module type match (using it inst) */
   /* 0th is module that determines upward distance */
   if (grp->last_gri != 0) titp = __find_unrt_targitp(grp, up_itp, 1);
   /* one component upward relative module name */
   else titp = up_itp;

   uprelitps[ii] = titp;
  }
}     

/*
 * given possible split off module type get the mast type
 *
 * pound params may be 1 level split off and defparams one more
 * i.e. all pound parameters split off from one master (maybe >1 inst)
 * then defparam split off from either normal or pound split off
 */
extern struct mod_t *__get_mast_mdp(struct mod_t *mdp)
{
 struct mod_t *mast_mdp;

 if (mdp->msplit) 
  {
   mast_mdp = mdp->mspltmst;
   if (mast_mdp->mpndsplit) mast_mdp = mast_mdp->mpndspltmst;
  }
 else if (mdp->mpndsplit) mast_mdp = mdp->mpndspltmst;
 else mast_mdp = mdp;
 return(mast_mdp);
}

/*
 * check all instances of downward relative instance selects
 *
 * only called for downward relative that have inst array selects
 */
static void chk_downrel_inst_sels(struct gref_t *grp)
{
 int32 ii; 
 int32 sav_ecnt;
 struct mod_t *mdp; 
 struct itree_t *itp;

 sav_ecnt = __pv_err_cnt;
 mdp = grp->gin_mdp;
 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   itp = mdp->moditps[ii];
   /* DBG remove --- */
   if (itp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* this does checking for each and emits error */  
   __find_unrt_targitp(grp, itp, 0);
   /* once error is found stop */
   if (__pv_err_cnt > sav_ecnt) break;
  }
}

/*
 * SPECIFY SECTION PREPARATION ROUTINES
 */

extern void __prep_specify(void)
{
 prep_tchks();
 prep_pths();
}

/*
 * TIMING CHECK REPRESENTATION CHANGE ROUTINES
 */

/*
 * routine to prepare timing checks 
 * for vectors in timing check event slots must split into 1 bit wide
 * checks since each bit timing reference and data events separate
 *
 * notice timing checks cannot be xmrs (must be I/O ports) so no xmr
 * processing net pin elements
 */
static void prep_tchks(void)
{
 int32 i1, i2;
 int32 starti1, starti2, chki1, chki2;
 struct tchk_t *tcp;
 struct mod_t *mdp;
 struct net_t *startnp, *chknp;
 struct tchg_t *start_tchgp;
 struct chktchg_t *chk_tchgp;
 struct gate_t gwrk;
 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* multiple blocks each with different symbol table legal */
   /* if option to ignore, specify will be remove before here */
   if (mdp->mspfy == NULL) continue;

   __push_wrkitstk(mdp, 0);
   for (tcp = mdp->mspfy->tchks; tcp != NULL; tcp = tcp->tchknxt)
    {
     /* do not convert since always will not get initialized - invisible */
     if (tcp->tc_gone) continue;

     /* convert ref. and data events to wire and range */
     /* know events is non concatente lhs (wire, const. bit/part select) */
     __xtract_wirng(tcp->startxp, &startnp, &starti1, &starti2);
     if (tcp->tchktyp == TCHK_PERIOD || tcp->tchktyp == TCHK_WIDTH) 
      {
       chknp = startnp; chki1 = starti1; chki2 = starti2;
       /* need to copy to make timing check violation check code work */
       tcp->chkxp = __copy_expr(tcp->startxp);
       tcp->chkcondx = __copy_expr(tcp->startcondx);
       if (tcp->tchktyp == TCHK_WIDTH)
        {
         /* opposite edge */
         if (tcp->startedge == E_NEGEDGE) tcp->chkedge = E_POSEDGE;
         else if (tcp->startedge == E_POSEDGE) tcp->chkedge = E_NEGEDGE;
         else __case_terr(__FILE__, __LINE__);
        }
       /* same edge */
       else tcp->chkedge = tcp->startedge;
      }
     else __xtract_wirng(tcp->chkxp, &chknp, &chki1, &chki2);

     switch ((byte) tcp->tchktyp) {
      /* SJM 01/16/04 - added $removal - reversed terms of $recovery */
      case TCHK_SETUP: case TCHK_HOLD: case TCHK_SKEW: case TCHK_RECOVERY:
      case TCHK_SETUPHOLD: case TCHK_REMOVAL: case TCHK_RECREM:
       /* timing check range all full - every bit time checked against */
       for (i1 = starti1; i1 >= starti2; i1--)
        {
         start_tchgp = bld_start_tchk_npp(tcp, startnp, i1); 
         for (i2 = chki1; i2 >= chki1; i2--)
         {
          chk_tchgp = bld_check_tchk_npp(chknp, i2); 
          /* check event needs access to start - also path to tchk master */
          chk_tchgp->startchgp = start_tchgp;
         }
        } 
       break;
      case TCHK_WIDTH: case TCHK_PERIOD:
       /* after above fixup, like normal except ==> not *> form */  
       /* maybe wrong and should be ? */
       for (i1 = starti1; i1 >= starti2; i1--)
        {
         /* for $period no reference event, data and reference the same */
         /* so this build ref. but no npp */
         start_tchgp = bld_start_tchk_npp(tcp, startnp, i1); 
         chk_tchgp = bld_check_tchk_npp(chknp, i1); 
         /* check event needs access to start - also path to tchk master */
         chk_tchgp->startchgp = start_tchgp;
        } 
       break;
      default: __case_terr(__FILE__, __LINE__);
     }
    /* no delay preparation for added hold of setuphold */
    if (tcp->tc_supofsuphld || tcp->tc_recofrecrem) continue;

    /* first set &&& conditional fields net still acessed from t event */
    /* width irrelevant know will always only be 1 delay */
    /* know every timing check has 1 limit field */
    __add_tchkdel_pnp(tcp, TRUE);
    __prep_delay(&gwrk, tcp->tclim_du.pdels, FALSE, FALSE,
     "first timing check limit", TRUE, tcp->tcsym, TRUE);
#ifndef __CVC_RT__
    if (__nd_neg_del_warn)
     {
      __gfwarn(601, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt,
       "timing check negative delay changed to 0 (ok for timing verifier)");
       __nd_neg_del_warn = FALSE;
     }
#endif
    tcp->tc_delrep = gwrk.g_delrep;
    tcp->tclim_du = gwrk.g_du;

    /* notice for setuphold (actually hold part) this always on */
    if (tcp->tc_haslim2)
     {
      /* width irrelevant know will always only be 1 delay */
      __add_tchkdel_pnp(tcp, FALSE);
      __prep_delay(&gwrk, tcp->tclim2_du.pdels, FALSE, FALSE,
       "2nd timing check limit", TRUE, tcp->tcsym, TRUE);
#ifndef __CVC_RT__
      if (__nd_neg_del_warn)
       {
        __gfwarn(601, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt,
         "timing check negative delay changed to 0 (ok for timing verifier)");
        __nd_neg_del_warn = FALSE;
       } 
#endif
      tcp->tc_delrep2 = gwrk.g_delrep;
      tcp->tclim2_du = gwrk.g_du;
     }
    }
   __pop_wrkitstk();
  }
}

/*
 * extract wire and range
 * know ranges always constants
 */
extern void __xtract_wirng(struct expr_t *xp, struct net_t **np,
 int32 *i1, int32 *i2)
{
 word32 *wp;

 switch (xp->optyp) {
  case ID:
   *np = xp->lu.sy->el.enp;
   *i1 = *i2 = -1;
   break;
  case LSB:
   *np = xp->lu.x->lu.sy->el.enp;
   wp = &(__contab[xp->ru.x->ru.xvi]);
   *i1 = *i2 = (int32) wp[0]; 
   break;
  case PARTSEL:
   *np = xp->lu.x->lu.sy->el.enp;
   *i1 = (int32) __contab[xp->ru.x->lu.x->ru.xvi];
   *i2 = (int32) __contab[xp->ru.x->ru.x->ru.xvi];
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   *np = __get_prep_indexed_psel_range(xp, i1, i2);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * build the start (earliest reference) event
 * for period need the start change (ref.) event but no npp
 */
static struct tchg_t *bld_start_tchk_npp(struct tchk_t *tcp,
 struct net_t *startnp, int32 bi1)
{
 struct tchg_t *start_tchgp;

 start_tchgp = (struct tchg_t *) __my_malloc(sizeof(struct tchg_t));
 start_tchgp->chgu.chgtcp = tcp;
 start_tchgp->oldval_ofs = 0;
 start_tchgp->lastchg_ofs = 0;
 /* FIXME - why are 2nd later change time and t chg rec unused here */

 /* for $period, no npp just placer holder set when data event occurs */ 
 if (tcp->tchktyp != TCHK_PERIOD)
  {
   __cur_npnum = 0;
   if (!startnp->n_isavec) bi1 = -1;
   __conn_npin(startnp, bi1, bi1, FALSE, NP_TCHG, (struct gref_t *) NULL,
     NPCHG_TCSTART, (char *) start_tchgp);
  }
 return(start_tchgp);
}

/*
 * build the check net pin event (later data event)
 */
static struct chktchg_t *bld_check_tchk_npp(struct net_t *chknp, int32 bi1)
{
 struct chktchg_t *chk_tchgp;

 chk_tchgp = (struct chktchg_t *) __my_malloc(sizeof(struct chktchg_t));
 /* link to start and tchk master accessed through start but caller sets */
 /* tchk master accessed through union in start tim chg */
 /* FIXME - why are 2nd later change time and t chg rec unused here */
 chk_tchgp->chkactive_ofs = 0;
 chk_tchgp->chkoldval_ofs = 0;
 __cur_npnum = 0;
 if (!chknp->n_isavec) bi1 = -1;
 __conn_npin(chknp, bi1, bi1, FALSE, NP_TCHG, (struct gref_t *) NULL,
  NPCHG_TCCHK, (char *) chk_tchgp);

 /* SJM - 04/04/02 need to turn on chg processing if only load */
 /* DBG remove -- */
 if (chknp->nlds == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 return(chk_tchgp);
}

/*
 * prepare path elements and delays
 * 1) convert path expr. lists to path elements
 * 2) convert delays - know delay expression is 1, 2, 3, or 6 numbers
 *    here delay expr. must still be scaled
 * 3) check inout ports that are path srcs to be sure has input driver
 *    pattern and path and path dest. has output driver pattern only
 *
 * LOOKATME - also somewhere back annotation can create IS forms ?
 */
static void prep_pths(void)
{
 int32 rv, mod_has_path;
 struct spcpth_t *pthp;
 struct mod_t *mdp;
 struct gate_t gwrk;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mspfy == NULL) continue;

   __push_wrkitstk(mdp, 0);

   mod_has_path = FALSE;
   /* know each delay is NUMBER or REALNUM */ 
   for (pthp = __inst_mod->mspfy->spcpths; pthp != NULL;
    pthp = pthp->spcpthnxt)
    {
     /* do not convert since always will not get initialized - invisible */
     if (pthp->pth_gone) continue;

     if (!chk_pthels(pthp)) { pthp->pth_gone = TRUE; continue; }
     if (!bldchk_pb_pthdsts(pthp)) { pthp->pth_gone = TRUE; continue; }

     /* prepare the delay - notice this uses __inst_mod */
     __add_pathdel_pnp(pthp);
     __prep_delay(&gwrk, pthp->pth_du.pdels, TRUE, FALSE, "path delay",
      TRUE, pthp->pthsym, TRUE);
     if (__nd_neg_del_warn)
      {
       __gferr(981, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt, 
        "path delay negative (used 0)");
       __nd_neg_del_warn = FALSE;
      } 
     pthp->pth_delrep = gwrk.g_delrep;
     pthp->pth_du = gwrk.g_du;
     if (pthp->datasrcx != NULL)
      {
       __gfinform(481, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt, 
        "path polarity operator ignored meaningless in simulator"); 
      } 
     /* and check for any illegal 0 delays */
     if ((rv = __chk_0del(pthp->pth_delrep, pthp->pth_du, __inst_mod))
      != DGOOD)
      {
       if (rv != DBAD_MAYBE0 && rv != DBAD_0)
        {
         __gferr(964, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
          "path delay illegal (%s delay form)", __to_deltypnam(__xs,
          pthp->pth_delrep));
        }
       else
        {
         /* for IO PAD cells some 0 delays common */
         if (rv == DBAD_MAYBE0)
          {
           __gfinform(483, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
           "path delay (%s form) contains some zero delays - primitive delay may be better",
           __to_deltypnam(__xs, pthp->pth_delrep));
          }
         else
          {
           __gfinform(484, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
            "path delay (%s form) all zeros - no effect unless annotated to",
            __to_deltypnam(__xs, pthp->pth_delrep));
          }
        }
      }
     mod_has_path = TRUE;
    }
   if (mod_has_path) emit_pthdst_bit_informs(__inst_mod);
   __pop_wrkitstk();
  }
}

/*
 * check all path components - check things that apply to path elements
 * check for bit by bit things when building sim path d.s.
 */
static int32 chk_pthels(struct spcpth_t *pthp)
{
 int32 pei;
 int32 gd_path;
 struct pathel_t *pep;
 struct net_t *np;

 gd_path = TRUE;
 for (pei = 0; pei <= pthp->last_pein; pei++)
  {
   pep = &(pthp->peins[pei]);
   np = pep->penp; 
   /* DBG remove */
   if (!np->n_isapthsrc) __misc_terr(__FILE__, __LINE__);
   /* --- */ 
   /* path source can be vectored or scalared (can be reg) */
   /* since source just timing check ref. event - record time of any chg */
  }
 for (pei = 0; pei <= pthp->last_peout; pei++)
  {
   pep = &(pthp->peouts[pei]);
   np = pep->penp; 
   if (np->n_isavec && !np->vec_scalared)
    {
     __gferr(825, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "vectored path destination wire %s illegal - must be scalared",
      np->nsym->synam);
     gd_path = FALSE;
    }
   /* if both has wire delay and dest., pth dst bit was turned off */
   /* LOOKATME - not sure what to check here */
   if (np->ntyp == N_TRIREG)
    {
     __gferr(826, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "path destination wire %s illegal trireg type", np->nsym->synam);
     gd_path = FALSE;
    }
   else if (!np->n_isapthdst
    || (np->nrngrep == NX_DWIR && np->nu.rngdwir->n_delrep != DT_PTHDST))
    {
     __gferr(826, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "path destination wire %s illegal - has wire delay", np->nsym->synam);
     gd_path = FALSE;
    }
  }
 return(gd_path);
}

/*
 * build and check the per bit but not per inst path dest table lists
 * all non bit specific path properties already checked
 */
static int32 bldchk_pb_pthdsts(struct spcpth_t *pthp)
{
 int32 spi, dpi;
 int32 pbiwid, pbowid;
 int32 sbi, sbi2, dbi, dbi2, pb_gd, nxt_spep, nxt_dpep;
 struct pathel_t *spep, *dpep;
 struct net_t *snp, *dnp;
 struct tchg_t *src_tchg;

 pb_gd = TRUE; 
 /* needed since loop initialization indirect and lint cannot detect */
 sbi = sbi2 = dbi = dbi2 = -1;
 snp = dnp = NULL;
 src_tchg = NULL;
 if (pthp->pthtyp == PTH_PAR)
  { 
   get_pthbitwidths(pthp, &pbiwid, &pbowid);
   if (pbiwid != pbowid)
    {
     __gferr(839, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "parallel path input bit length %d and output %d differ",
      pbiwid, pbowid);
     return(FALSE);
    }
   /* know bit lengths the same and if vectors or selects scalared */
   for (spi = dpi = -1, nxt_spep = nxt_dpep = TRUE;;)   
    {
     if (nxt_spep)
      {
       /* before moving to next bit always add net pin element */
       if (++spi > pthp->last_pein)
        {
         if (!nxt_dpep || (dpi + 1) <= pthp->last_peout)
          __misc_terr(__FILE__, __LINE__);
         break;
        }
       spep = &(pthp->peins[spi]);
       snp = spep->penp;
       if (!snp->n_isavec) sbi = sbi2 = 0; 
       else
        {
         if (spep->pthi1 == -1) { sbi = snp->nwid - 1; sbi2 = 0; }  
         else { sbi = spep->pthi1; sbi2 = spep->pthi2; }
        }
       /* build and add (if non already added) path dest. NP_DPTHSRC */
       src_tchg = try_add_npp_dpthsrc(pthp, snp, sbi);
       nxt_spep = FALSE; 
      }
     if (nxt_dpep)
      {
       /* if done, will always exit on src over run of end */ 
       if (++dpi > pthp->last_peout) __misc_terr(__FILE__, __LINE__);
       dpep = &(pthp->peouts[dpi]);
       dnp = dpep->penp;
       if (!dnp->n_isavec) dbi = dbi2 = 0; 
       else
        {
         if (dpep->pthi1 == -1) { dbi = dnp->nwid - 1; dbi2 = 0; }  
         else { dbi = dpep->pthi1; dbi2 = dpep->pthi2; }
        }
       nxt_dpep = FALSE; 
      }
     if (!bldchk_1bit_pthdst(pthp, snp, sbi, dnp, dbi, dnp->nwid, src_tchg))
      pb_gd = FALSE;
     if (--sbi < sbi2) nxt_spep = TRUE;
     if (--dbi < dbi2) nxt_dpep = TRUE;
    }
   return(pb_gd);
  }
 /* handle full path case - for every source bit */
 for (spi = 0; spi <= pthp->last_pein; spi++)
  {
   spep = &(pthp->peins[spi]);
   snp = spep->penp;
   if (!snp->n_isavec) sbi = sbi2 = 0; 
   else
    {
     if (spep->pthi1 == -1) { sbi = snp->nwid - 1; sbi2 = 0; }  
     else { sbi = spep->pthi1; sbi2 = spep->pthi2; }
    }
   for (; sbi >= sbi2; sbi--)
    {
     src_tchg = try_add_npp_dpthsrc(pthp, snp, sbi);
     /* for given bit of input path - for every output path */ 
     for (dpi = 0; dpi <= pthp->last_peout; dpi++)
      {
       dpep = &(pthp->peouts[dpi]);
       dnp = dpep->penp;
       if (!dnp->n_isavec) dbi = dbi2 = 0; 
       else
        {
         if (dpep->pthi1 == -1) { dbi = dnp->nwid - 1; dbi2 = 0; }  
         else { dbi = dpep->pthi1; dbi2 = dpep->pthi2; }
        }
       /* for every bit of destination path element */
       for (; dbi >= dbi2; dbi--)
        {
         /* notice here, must check every sbits by dbits combination */
         if (!bldchk_1bit_pthdst(pthp, snp, sbi, dnp, dbi, dnp->nwid,
          src_tchg)) pb_gd = FALSE;
        }
      }
    }
  }
 return(pb_gd);
}

/*
 * build and add the path source net pin entry - like tc ref. event
 * just records latest change
 *
 * for cases with mulitple source for 1 path only add first time
 * here special indirect npp that allows indexing by bit and comparison
 *
 * if non empty or separate bit lists make sense
 * best is to put in pass that checks to see if needed and adds after here
 */
static struct tchg_t *try_add_npp_dpthsrc(struct spcpth_t *pthp,
 struct net_t *snp, int32 sbi)
{
 struct net_pin_t *npp;
 struct tchg_t *start_tchgp;

 if ((npp = find_1timchg_psnpp(snp, sbi, NPCHG_PTHSRC)) != NULL)
  return(npp->elnpp.etchgp);

 start_tchgp = (struct tchg_t *) __my_malloc(sizeof(struct tchg_t));
 start_tchgp->chgu.chgpthp = pthp;
 start_tchgp->oldval_ofs = 0;
 start_tchgp->lastchg_ofs = 0;
 
 __cur_npnum = 0;
 /* sbi access inst. table so must be 0 but must be -1 for npp */
 if (!snp->n_isavec) sbi = -1;

 /* with table for moving down to col. from inst. */
 __conn_npin(snp, sbi, sbi, FALSE, NP_TCHG, (struct gref_t *) NULL,
  NPCHG_PTHSRC, (char *) start_tchgp);
 return(start_tchgp);
}

/*
 * find a path source time change npp 
 * know __inst_mod set 
 */
static struct net_pin_t *find_1timchg_psnpp(struct net_t *snp, int32 bi,
 int32 subtyp)
{
 struct net_pin_t *npp;
 struct npaux_t *npauxp;

 for (npp = snp->nlds; npp != NULL; npp = npp->npnxt) 
  {
   if (npp->npntyp == NP_TCHG && npp->chgsubtyp == subtyp
    && ((npauxp = npp->npaux) != NULL && npauxp->nbi1 == bi)) return(npp);
  }
 return(NULL);
}

/*
 * build 1 bit path dest. pair simulation path and do 1 bit path checking
 * if error path dest. not built
 *
 * for scalar dbi will be 0
 */
static int32 bldchk_1bit_pthdst(struct spcpth_t *pthp, struct net_t *s_np,
 int32 sbi, struct net_t *d_np, int32 dbi, int32 dnwid,
 struct tchg_t *src_tchg)
{
 int32 i;
 int32 pb_gd;
 struct pthdst_t *pdp;
 char s1[RECLEN], s2[RECLEN];

 /* for inouts - source and dest. cannot be the same */
 pb_gd = TRUE;
 if (d_np->nsym == s_np->nsym && dbi == sbi)
  {
#ifndef __CVC_RT__
   __gfwarn(617, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
    "ignoring path from %s%s to %s%s because source and destination same wire - simulators that split inout ports results may differ",
    s_np->nsym->synam, bld_bitref(s1, s_np, sbi), d_np->nsym->synam,
    bld_bitref(s2, d_np, dbi));
#endif
   return(FALSE);
  }
 /* if previous error, net marked as gone here */
 if (d_np->n_gone || s_np->n_gone) return(FALSE);

 /* check for no more than one driver per bit */ 
 /* LOOKATME - now driver for 1364 can be anything and */ 
 /* tran or inouts are not drivers (not hard), does this work? */
 if (!chk_biti_pthdst_driver(pthp, d_np, dbi)) return(FALSE);

 /* know for dest. rng dwir already allocated */
 /* if first bit of this wire, allocate table and mark all unused */
 if (d_np->nu.rngdwir->n_du.pb_pthdst == NULL)
  {
   d_np->nu.rngdwir->n_du.pb_pthdst = (struct pthdst_t **)
    __my_malloc(dnwid*sizeof(struct pthdst_t *));
   for (i = 0; i < dnwid; i++) d_np->nu.rngdwir->n_du.pb_pthdst[i] = NULL;
  }
 /* if this is path with different source but same destination, allocate */
 pdp = (struct pthdst_t *) __my_malloc(sizeof(struct pthdst_t));
 pdp->pstchgp = src_tchg;
 pdp->pdnxt = d_np->nu.rngdwir->n_du.pb_pthdst[dbi];
 d_np->nu.rngdwir->n_du.pb_pthdst[dbi] = pdp;
 return(pb_gd);
}

/*
 * compute a path's input and output bit widths
 */
static void get_pthbitwidths(struct spcpth_t *pthp, int32 *pinwid,
 int32 *poutwid)
{
 int32 pei, pbwid;
 struct pathel_t *pep;

 for (pei = 0, pbwid = 0; pei <= pthp->last_pein; pei++)
  {
   pep = &(pthp->peins[pei]);
   /* notice all ranges normalized to h:l here */
   if (pep->pthi1 == -1) pbwid += pep->penp->nwid; 
   else pbwid += (pep->pthi1 - pep->pthi2 + 1); 
  }
 *pinwid = pbwid;
  for (pei = 0, pbwid = 0; pei <= pthp->last_peout; pei++)
   {
    pep = &(pthp->peouts[pei]);
    if (pep->pthi1 == -1) pbwid += pep->penp->nwid;
    else pbwid += (pep->pthi1 - pep->pthi2 + 1); 
   }
 *poutwid = pbwid;
} 

/*
 * build a bit reference of form [<bit>] or ""
 */
static char *bld_bitref(char *s, struct net_t *np, int32 bi)
{
 if (!np->n_isavec || bi == -1) strcpy(s, "");
 else sprintf(s, "[%d]", bi);
 return(s);
}

/*
 * check driver of bit to make sure bit has exactly one driver
 */
static int32 chk_biti_pthdst_driver(struct spcpth_t *pthp, struct net_t *np,
 int32 biti)
{
 int32 num_drvs;
 struct net_pin_t *npp;
 struct npaux_t *npauxp;
 char s1[RECLEN];

 if (!np->n_isavec)
  {
   if (np->ndrvs == NULL) goto no_drv;
   for (num_drvs = 0, npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
    {
     if (npp->npntyp > NP_MDPRT) continue;
     if (npp->npntyp <= NP_MDPRT && npp->np_xmrtyp != XNP_LOC)
      goto pthdst_xmr;
     if (++num_drvs > 1)
      {
       __gferr(827, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
        "path destination %s illegal - scalar wire has more than one driver",
        np->nsym->synam);
       return(FALSE);
      }  
    }
   if (num_drvs == 0) goto no_drv;
  }

 /* here only check drivers of this bit */
 for (num_drvs = 0, npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1) goto got_match;
   /* must never see IS form driver here - must cause copying earlier */ 
   /* DBG remove --- */
   if (npauxp->nbi1 == -2) __misc_terr(__FILE__, __LINE__);   
   /* --- */

   if (biti > npauxp->nbi1 || biti < npauxp->nbi2.i) continue;

got_match:
   /* found driver of bit - know only 1 */
   if (npp->npntyp <= NP_MDPRT && npp->np_xmrtyp != XNP_LOC)
    {
pthdst_xmr:
     __gferr(961, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "path destination %s%s cross module reference driver illegal",
      np->nsym->synam, bld_bitref(s1, np, biti));
     return(FALSE);
    }
   if (++num_drvs > 1)
    {
     __gferr(827, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "path destination %s%s illegal - more than one driver",
      np->nsym->synam, bld_bitref(s1, np, biti));
    }  
  }
 if (num_drvs != 0) return(TRUE);

no_drv:
#ifndef __CVC_RT__
 __gfwarn(616, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
  "path destination %s%s does not have a driver - path delay no effect",
  np->nsym->synam, bld_bitref(s1, np, biti));
#endif
 return(TRUE);
}

/*
 * emit path dest bit informs where bits not in any path for vectors
 * processes path dests in current module.
 * know module has specify section and at least one path
 *
 * SJM 06/06/00 - also emitting inform for inout as both path src/dest
 */
static void emit_pthdst_bit_informs(struct mod_t *mdp)
{
 int32 ni, bi;
 struct net_t *np;
 
 if (mdp->mnnum == 0) return;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   /* SJM 06/06/00 - emit inform if inout used as path src and dst */   
   /* SJM 07/16/01 - removed warning, it was wrong - inout paths now work */

   if (!np->n_isapthdst || !np->n_isavec) continue;
   /* DBG remove --- */
   if (np->nu.rngdwir->n_delrep != DT_PTHDST)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   
   for (bi = 0; bi < np->nwid; bi++)   
    {
     if (np->nu.rngdwir->n_du.pb_pthdst[bi] == NULL)
      {
       __gfinform(474, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
        "for delay path destination %s, bit %d is not destionation of any path",
        np->nsym->synam, bi); 
      }
    }
  }
}

/*
 * check path delay non zero and non expression
 */
extern int32 __chk_0del(word32 drep, union del_u du, struct mod_t *mdp)
{
 int32 i;
 int32 some_0, all_0;

 some_0 = FALSE;
 all_0 = TRUE;
 switch ((byte) drep) {
  /* think ,, form will work right here for timing checks */
  case DT_NONE: return(DBAD_NONE);
  case DT_1X: case DT_4X: return(DBAD_EXPR);
  case DT_1V:
   if (*du.d1v == 0ULL) return(DBAD_0);
   return(DGOOD);
  case DT_IS1V:
   for (i = 0; i < mdp->flatinum; i++)
    { if (du.dis1v[i] == 0ULL) some_0 = TRUE; else all_0 = FALSE; }
   break;
  case DT_IS1V1:
   for (i = 0; i < mdp->flatinum; i++)
    { if (du.dis1v1[i] == 0) some_0 = TRUE; else all_0 = FALSE; }
   break;
  case DT_IS1V2:
   for (i = 0; i < mdp->flatinum; i++)
    { if (du.dis1v2[i] == 0) some_0 = TRUE; else all_0 = FALSE; }
   break;
  case DT_4V:
   for (i = 0; i < 4; i++)
    { if (du.d4v[i] == 0ULL) some_0 = TRUE; else all_0 = FALSE; }
   break;
  case DT_IS4V:
   for (i = 0; i < 4*mdp->flatinum; i++)
    { if (du.dis4v[i] == 0ULL) some_0 = TRUE; else all_0 = FALSE; }
   break; 
  case DT_IS4V1:
   some_0 = FALSE;
   all_0 = TRUE;
   for (i = 0; i < 4*mdp->flatinum; i++)
    { if (du.dis4v1[i] == 0) some_0 = TRUE; else all_0 = FALSE; }
   break;
  case DT_IS4V2:
   some_0 = FALSE;
   all_0 = TRUE;
   for (i = 0; i < 4*mdp->flatinum; i++)
    { if (du.dis4v2[i] == 0) some_0 = TRUE; else all_0 = FALSE; }
   break;
  case DT_16V:
   for (i = 1; i < 16; i++)
    {
     /* must skip unused that will be 0 */
     if (i == 5 || i == 10 || i == 15) continue;
     if (du.d16v[i] == 0ULL) some_0 = TRUE; else all_0 = FALSE;
    }
   break;
  case DT_IS16V:
   for (i = 1; i < 16*mdp->flatinum; i++)
    { 
     if ((i % 16) == 5 || (i % 16) == 10 || (i % 16) == 15) continue; 
     if (du.dis16v[i] == 0ULL) some_0 = TRUE; else all_0 = FALSE;
    }
   break;
  case DT_IS16V1:
   for (i = 1; i < 16*mdp->flatinum; i++)
    {
     if ((i % 16) == 5 || (i % 16) == 10 || (i % 16) == 15) continue; 
     if (du.dis16v1[i] == 0) some_0 = TRUE; else all_0 = FALSE;
    }
   break;
  case DT_IS16V2:
   for (i = 0; i < 16*mdp->flatinum; i++)
    {
     if ((i % 16) == 5 || (i % 16) == 10 || (i % 16) == 15) continue; 
     if (du.dis16v2[i] == 0) some_0 = TRUE; else all_0 = FALSE;
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (all_0) return(DBAD_0); 
 if (some_0) return(DBAD_MAYBE0);
 return(DGOOD);
}

/*
 * DESIGN PART FREE ROUTINES 
 */

/*
 * free one statement
 * this requires set __inst_mod  
 * LOOKATME - how come only called from interactive and always 1 flat inst?
 */
extern void __free_1stmt(struct st_t *stp)
{
 int32 fji;
 struct for_t *frp;
 struct qconta_t *qcafs;
 struct st_t *fjstp;

 if (stp == NULL) return;

 switch ((byte) stp->stmttyp) {
  case S_NULL: case S_STNONE: break;
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA:
   __free_xtree(stp->st.spra.lhsx);
   __free_xtree(stp->st.spra.rhsx);
   break;
  case S_IF:
   __free_xtree(stp->st.sif.condx);
   __free_stlst(stp->st.sif.thenst);
   __free_stlst(stp->st.sif.elsest);
#ifdef __XPROP__
   if (stp->st.sif.xprop != NULL) 
    {
     __free_xprop(stp->st.sif.xprop);     
     stp->st.sif.xprop = NULL;     
    } 
#endif
   break;
  case S_CASE:
   __free_xtree(stp->st.scs.csx);
   /* this also frees default: (maybe just place holder) and list els */
   free_csitemlst(stp->st.scs.csitems);
#ifdef __XPROP__
   __free_stlst(stp->st.scs.xprop_lstp);
   if (stp->st.scs.xprop != NULL) 
    {
     __free_xprop(stp->st.scs.xprop);     
     stp->st.scs.xprop = NULL;     
    } 
#endif
   break;
  case S_REPEAT:
   __free_xtree(stp->st.srpt.repx);
   /* if after preparation need to free temp. repeat count array */
   /* LOOKATME - why is this only per. inst. stor. place in stmts? */ 
   __free_stlst(stp->st.srpt.repst);
   break;
  case S_FOREVER:
  case S_WHILE:
  case S_DO_WHILE:
   __free_xtree(stp->st.swh.lpx);
   __free_stlst(stp->st.swh.lpst);
   break;
  case S_WAIT:
   __free_xtree(stp->st.swait.lpx);
   /* free statement list since del. ctrl. points to wait itself */
   __free_stlst(stp->st.swait.lpst);
   /* do not free action statement which is wait itself */
   free_dctrl(stp->st.swait.wait_dctp, FALSE);
   break;
  case S_FOR:
   frp = stp->st.sfor;
   /* notice for assign already freed */
   __free_xtree(frp->fortermx);
   __free_stlst(frp->forinc);
   __free_stlst(frp->forbody);
   __my_free(frp, sizeof(struct for_t));
   break;
  case S_DELCTRL: free_dctrl(stp->st.sdc, TRUE); break;
  case S_UNBLK:
   __free_stlst(stp->st.sbsts);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     __free_stlst(fjstp); 
    }
   __my_free(stp->st.fj.fjstps, (fji + 1)*sizeof(struct st_t *)); 
   __my_free(stp->st.fj.fjlabs, (fji + 1)*sizeof(int32)); 
   break;
  case S_FUNCCALL:
  case S_TSKCALL:
   __free_xtree(stp->st.stkc.targs);
   /* cannot free symbol */
   /* only interactive can be freed so cannot have tfrec */
   if (stp->st.stkc.tkcaux.trec != NULL) __misc_terr(__FILE__, __LINE__);
   break;
  case S_QCONTA:
   qcafs = stp->st.sqca;
   /* notice for assign already freed */
   __free_xtree(qcafs->qclhsx);
   __free_xtree(qcafs->qcrhsx);
   __my_free(qcafs, sizeof(struct qconta_t));
   break;
  case S_QCONTDEA:
   __free_xtree(stp->st.sqcdea.qcdalhs);
   break;
  case S_CAUSE: break;
  case S_DSABLE:
   __free_xtree(stp->st.sdsable.dsablx);
   break;
  /* statement added for execution */
  case S_REPSETUP:
   /* union field unused */
   stp->st.scausx = NULL;
   break;
  case S_REPDCSETUP:
   /* union field unused */
   stp->st.scausx = NULL;
   break;
  case S_INC: case S_DEC:
   __free_xtree(stp->st.spra.lhsx);
   break;
  case S_BREAK: case S_CONTINUE: case S_RETURN: break;
  case S_GOTO: break;
  /* notice named block non freeable (at least for now) */
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * free a delay control record
 */
static void free_dctrl(struct delctrl_t *dctp, int32 free_action)
{
 struct mod_t *cur_mdp;

 /* AIV 04/25/07 - since can get here from interactive debugger need get mod */
 if (__idp == NULL) cur_mdp =  __inst_mod;
 else cur_mdp = get_inst_mod_();

 /* free the delay value or expr. for event controls */
 __free_del(dctp->dc_du, dctp->dc_delrep, cur_mdp->flatinum);

 /* SJM - 08/03/01 - also free repeat cout expr if present */
 if (dctp->repcntx != NULL) __free_xtree(dctp->repcntx);

 /* for delay not event control, will not have scheduled tevs */
 dctp->dceschd_tev_ofs = -1;
 if (free_action) __free_stlst(dctp->actionst);
 __my_free(dctp, sizeof(struct delctrl_t));
}

/*
 * free case item list
 */
static void free_csitemlst(struct csitem_t *csip)
{
 struct csitem_t *csip2;

 for (;csip != NULL;)
  {
   csip2 = csip->csinxt;
   /* nil expr list always nil for default */
   if (csip->csixlst != NULL) __free_xprlst(csip->csixlst);
   /* if no default, stmt of first nil */
   if (csip->csist != NULL) __free_stlst(csip->csist);
   __my_free(csip, sizeof(struct csitem_t));
   csip = csip2;
  }
}

/*
 * free a list of statements - i.e. next fields connect to make block list
 */
extern void __free_stlst(struct st_t *stp)
{
 struct st_t *stp2;

 for (; stp != NULL;) { stp2 = stp->stnxt; __free_1stmt(stp); stp = stp2; }
}

/*
 * free an expression list
 */
extern void __free_xprlst(struct exprlst_t *xplp)
{
 struct exprlst_t *xplp2;

 for (; xplp != NULL;)
  {
   xplp2 = xplp->xpnxt;
   __free_xtree(xplp->xp);
   __my_free(xplp, sizeof(struct exprlst_t));
   xplp = xplp2;
  }
}

/* 
 * ROUTINES FOR BUILDING TMP MOD STMT INDEX (TAB)
 */

/*
 * routine to build tmp stmt index (tab) for adding stmt fields to idp area
 *
 * builds one global index for each module then sets mst tab and mstnum to
 * tmporarily point to it.  At xform point, frees all these first and
 * build the final msmts table
 *
 * SJM 08-07-07 - new routine to build early provisional mstmt index
 */
extern void __bld_provisional_mstabs(void)
{
 struct mod_t *mdp;
 struct ialst_t *ialp;
 struct task_t *tskp;
 struct st_t *stp;

 __size_prp_mstmts = 100;
 __prp_mstmt_ndx = (struct st_t **)
  __my_malloc(__size_prp_mstmts*sizeof(struct st_t *));
 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0); 
   __last_mstndx = -1;

   for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)  
    {
     /* first stmt always entry point */
     stp = ialp->iastp;
     add_stlst_mstmts_ndx(stp);
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     /* labeled blocks and forks are gened inline */
     if (tskp->tsktyp == Begin || tskp->tsktyp == FORK) continue;
  
     stp = tskp->tskst;
     add_stlst_mstmts_ndx(stp);
    }
   mdp->prov_mstnum = __last_mstndx + 1;
   if (mdp->prov_mstnum > 0)
    {
     mdp->prov_mstndx = (struct st_t **)
      __my_malloc(mdp->prov_mstnum*sizeof(struct st_t *));
     memcpy(mdp->prov_mstndx, __prp_mstmt_ndx,
      mdp->prov_mstnum*sizeof(struct st_t *));
    }
   __pop_wrkitstk();
  }
 /* finally, free the work prp mstmt index since done with it */
 __my_free(__prp_mstmt_ndx, __size_prp_mstmts*sizeof(struct st_t *));
}

/*
 * add stmts in a stlst to prp tmp mstmt ndx tab
 */
static void add_stlst_mstmts_ndx(struct st_t *hdstp)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = add_1stmt_mstmts_ndx(stp);
  }
}

/*
 * add one stmt to prp tmp mstmt ndx tab and figure out where to continue
 */
static struct st_t *add_1stmt_mstmts_ndx(struct st_t *stp)
{
 int32 fji;
 struct st_t *fjstp;
 struct st_t *astp;
 struct delctrl_t *dctp;

 if (stp == NULL) return(NULL);

 /* SJM 08-07-08 - always add current stmt */
 set_mstmt_stp(stp);
 switch ((byte) stp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_INC: case S_DEC:
  case S_NULL: case S_STNONE:
  case S_PROCA: case S_RHSDEPROCA: case S_FORASSGN:
  case S_REPSETUP: case S_REPDCSETUP: case S_TSKCALL: case S_FUNCCALL:
  case S_QCONTA: case S_QCONTDEA: case S_CAUSE: case S_DSABLE:
   break;
  case S_NBPROCA: 
#ifdef __XPROP__
   /* if xprop and compiled code need to alloc a new stmt which will be */
   /* used as the lhs assign at the end of xprop accumulation */
   /* the new stmt must be done here so normal set up works correctly */
   if (__xprop && __compiled_sim)
    {
     struct st_t *xstp;
     struct net_t *np;
     struct expr_t *lhsx, *idndp;
     struct task_t *tskp;

     /* if not yet copied alloc a new nb stmt and put in dummy task holder */
     if (stp->xprop_nbu.xprop_astp == NULL)
      {
       __xprop_copying = TRUE;
       xstp = __copy_stmt(stp);
       __xprop_copying = FALSE;
       stp->xprop_nbu.xprop_astp = xstp;
       xstp->xprop_nbu.xprop_orig_astp = stp;
       /* place stmt into dummy task holder */
       tskp = __inst_mod->xprop_nb_taskp;
       /* DBG remove -- */
       if (tskp == NULL) __misc_terr(__FILE__, __LINE__);
       /* ---- */
       xstp->stnxt = tskp->tskst;
       tskp->tskst = xstp;
       lhsx = xstp->st.spra.lhsx;
       /* lhs concats still used as wrapper */
       if (lhsx->optyp != ID && lhsx->optyp != LCB)
        {
         idndp = __get_lvalue_idndp(lhsx);
         np = idndp->lu.sy->el.enp;
         lhsx->optyp = ID;
         lhsx->lu.sy = np->nsym;
         lhsx->szu.xclen = np->nwid;
        }
   
       set_mstmt_stp(xstp);
      }
    }
#endif
   break;
  case S_IF:
   add_stlst_mstmts_ndx(stp->st.sif.thenst);
   add_stlst_mstmts_ndx(stp->st.sif.elsest);
   break;
  case S_CASE:
   add_csitemlst_mstmts_ndx(stp->st.scs.csitems);
#ifdef __XPROP__
   /* AIV 08/02/11 - now might have xprop list to process as well */
   if (stp->st.scs.xprop_lstp != NULL)
     add_stlst_mstmts_ndx(stp->st.scs.xprop_lstp);
#endif
   break;
  case S_REPEAT:
   add_stlst_mstmts_ndx(stp->st.srpt.repst);
   break;
  case S_FOREVER: case S_WHILE: case S_DO_WHILE:
   add_stlst_mstmts_ndx(stp->st.swh.lpst);
   break;
  case S_WAIT:
   add_stlst_mstmts_ndx(stp->st.swait.lpst);
   break;
  case S_FOR:
   add_stlst_mstmts_ndx(stp->st.sfor->forinc);
   add_stlst_mstmts_ndx(stp->st.sfor->forbody);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;
#ifdef __XPROP__
   /* basically the same code as above for <= # as regular <= */
   if (astp->stmttyp == S_NBPROCA) 
    {
     if (__xprop && __compiled_sim)
      {
       struct st_t *xstp;
       struct net_t *np;
       struct expr_t *lhsx, *idndp;
       struct task_t *tskp;
  
       if (astp->xprop_nbu.xprop_astp == NULL)
        {
         __xprop_copying = TRUE;
         xstp = __copy_stmt(astp);
         __xprop_copying = FALSE;
         /* AIV 01/31/12 - this has to be stp-> here not astp */
         stp->xprop_nbu.xprop_astp = xstp;
         xstp->xprop_nbu.xprop_orig_astp = stp;
         tskp = __inst_mod->xprop_nb_taskp;
         /* DBG remove -- */
         if (tskp == NULL) __misc_terr(__FILE__, __LINE__);
         /* ---- */
         xstp->stnxt = tskp->tskst;
         tskp->tskst = xstp;
         lhsx = xstp->st.spra.lhsx;
         /* lhs concats still used as wrapper */
         if (lhsx->optyp != ID && lhsx->optyp != LCB)
          {
           idndp = __get_lvalue_idndp(lhsx);
           np = idndp->lu.sy->el.enp;
           lhsx->optyp = ID;
           lhsx->lu.sy = np->nsym;
           lhsx->szu.xclen = np->nwid;
          }
         dctp->xprop_nb_actionst = xstp;
         set_mstmt_stp(xstp);
        }
      }
    }
#endif
   if (astp != NULL) add_stlst_mstmts_ndx(astp);
   break;
  case S_NAMBLK:
   /* SJM 02-05-09 - now using traversal to build stmt list for special case */
   /* checkng */
   add_stlst_mstmts_ndx(stp->st.snbtsk->tskst);
   break;
  case S_UNBLK:
   add_stlst_mstmts_ndx(stp->st.sbsts);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     add_stlst_mstmts_ndx(fjstp);
    }
   break;
  case S_GOTO:
   break;
  case S_BREAK: case S_CONTINUE: case S_RETURN: break;
  /* LOOKATME - need name resolving statement type no? */
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}

/*
 * add the case item stmts to the tmp idp add point mstmt tab (ndx)
 */
static void add_csitemlst_mstmts_ndx(struct csitem_t *csip)
{
 for (; csip != NULL; csip = csip->csinxt)
  {
   if (csip->csist != NULL) add_stlst_mstmts_ndx(csip->csist);
  }
}


/*
 * set 1 stmt to current prp tmp stmt ndx tab
 */
static void set_mstmt_stp(struct st_t *stp)
{
 if (stp == NULL) return;

 if ((++__last_mstndx) >= __size_prp_mstmts) grow_prp_mstmt_ndx();
 __prp_mstmt_ndx[__last_mstndx] = stp; 
}

/*
 * grow global gref work table
 */
static void grow_prp_mstmt_ndx(void)
{
 size_t old_mstsiz, osize, nsize;

 old_mstsiz = __size_prp_mstmts;
 osize = old_mstsiz*sizeof(struct st_t *);
 __size_prp_mstmts = (3*__size_prp_mstmts)/2; 
 nsize = __size_prp_mstmts*sizeof(struct st_t *);
 __prp_mstmt_ndx = (struct st_t **) __my_realloc(__prp_mstmt_ndx,
  osize, nsize);
}

/*
 * ROUTINES TO TRANFORM INTERNAL NET LIST FOR COMPILATION 
 */

/*
 * process all net list data structures tranforming for compilation
 *
 * AIV 03/26/07 - removed table of expressions only doing statments now
 *
 * SJM 08-07-07 - must be able to use provisional mst tab up to here, 
 * free provisional and build final in this routine
 */
extern void __xform_nl_stmts(void)
{
 struct mod_t *mdp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->prov_mstnum == 0) continue;

   __my_free(mdp->prov_mstndx, mdp->prov_mstnum*sizeof(struct st_t *));
   mdp->prov_mstndx = NULL;
   mdp->prov_mstnum = 0;
  }

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mstnum == 0) mdp->mstmts = NULL;
   else
    {
     /* AIV 02/20/12 - changed this to use an array of stmts - this way */
     /* statements can be alloc and added at anytime */
     mdp->mstmts = (struct st_t **) 
      __my_malloc(mdp->mstnum*sizeof(struct st_t *));
    }
   __last_modsti = -1;
   /* AIV 12/15/10 - need to know where the end of the non-task stmts end */
   mdp->mstnum_no_task = __last_modsti + 1;
   cmp_xform_tasks(mdp);
 
   cmp_xform_ialst(mdp);
   
   mdp->mstnum = __last_modsti + 1;
   /* LOOKATME - do analog block statement need to be */
   /* xformed since not accessed in digital sim, think not */

   /* AIV 07/13/09 - copy_stmt wasn't inc mstnum for generated items */
   /* but now it is - should pass this check */
   /* DBG remove -- */
   if (__last_modsti + 1 != mdp->mstnum)
    __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* DBG remove ---
   if (__debug_flg)
    {
     __dmp_msttab(mdp, mdp->mstnum);
    }
   --- */
  }
}

/*
 * copy a statement list (linked list of statements)
 */
static struct st_t *cmp_xform_lstofsts(struct mod_t *mdp, struct st_t *ostp)
{
 struct st_t *nstp_hdr, *nstp, *last_nstp, *ostp2;

 nstp_hdr = NULL;
 for (last_nstp = NULL; ostp != NULL;)
  {
   nstp = cmp_xform1_stmt(mdp, ostp, last_nstp);
   /* must not free internal parts of old statement */

   if (last_nstp == NULL) nstp_hdr = nstp; else last_nstp->stnxt = nstp;
   nstp->stnxt = NULL;
   last_nstp = nstp;
   ostp2 = ostp->stnxt;
#ifdef __XPROP__
   /* if xprop duplicate non-blocking stmt must point to alloc stmt */
   /* AIV 10/26/11 - only do this if xprop is turned on */
   if (__xprop)
    {
     struct st_t *orig_stp;

     orig_stp = ostp->xprop_nbu.xprop_orig_astp;
     if (orig_stp != NULL)
      {
       orig_stp->xprop_nbu.xprop_astp = nstp;
      }
    }
#endif
   __my_free(ostp, sizeof(struct st_t));
   ostp = ostp2;
  }
 return(nstp_hdr);
}

/*
 * compile transform one statement
 */
static struct st_t *cmp_xform1_stmt(struct mod_t *mdp, struct st_t *ostp,
 struct st_t *last_stp)
{
 struct st_t *nstp;
 int32 fji;
 struct sy_t *syp; 
 struct systsk_t *stbp;
 struct st_t *fjstp;

/* DBG remove --
 if (__debug_flg)
  {
-* --
   __dbg_msg("%04d: AT %s %s - STMT XFORM (%s)\n", ostp->stalloc_ndx,
    __bld_lineloc(__xs, ostp->stfnam_ind, ostp->stlin_cnt),
    mdp->msym->synam, __to_sttyp(__xs2, ostp->stmttyp));
-- *-
-* -- *-
   __dbg_msg("AT %s %s - STMT XFORM %04d (%s)\n",
    __bld_lineloc(__xs, ostp->stfnam_ind, ostp->stlin_cnt),
    mdp->msym->synam, __last_modsti + 1,
    __to_sttyp(__xs2, ostp->stmttyp));
-* -- *-
  }
--- */

 if (ostp == NULL) return(NULL);

 /* DBG remove -- */
 if (__last_modsti + 2 > mdp->mstnum) __misc_terr(__FILE__, __LINE__);
 /* ---*/

 nstp = (struct st_t *) __my_malloc(sizeof(struct st_t)); 

 mdp->mstmts[++__last_modsti] = nstp;

 /* because union for common case now in statement, gets copied here */
 *nstp = *ostp;
 nstp->stnxt = NULL;
 nstp->st_ndx = __last_modsti;

 switch ((byte) ostp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_NULL: case S_STNONE: break;
  /* SJM 09/24/01 - for fj, must not make for assign separate stmt */
  case S_INC: case S_DEC:
  case S_PROCA: case S_RHSDEPROCA: case S_NBPROCA: case S_FORASSGN:
#ifdef __AMS__
  case S_BRNCH_CNTRB: case S_IND_BRNCH_CNTRB:
#endif
   break;
  case S_IF:
   nstp->st.sif.thenst = cmp_xform_lstofsts(mdp, ostp->st.sif.thenst);
   nstp->st.sif.elsest = cmp_xform_lstofsts(mdp, ostp->st.sif.elsest);
#ifdef __XPROP__
   nstp->st.sif.xprop = ostp->st.sif.xprop;
#endif
   break;
  case S_CASE:
   nstp->st.scs.castyp = ostp->st.scs.castyp;
   nstp->st.scs.maxselwid = ostp->st.scs.maxselwid;

   /* if case has no default, st and expr list fields nil */ 
   /* no copy but must transform st lists and expr inside */
   nstp->st.scs.csitems = ostp->st.scs.csitems;
   cmp_xform_csitemlst(mdp, nstp->st.scs.csitems);
#ifdef __XPROP__
   nstp->st.scs.xprop = ostp->st.scs.xprop;
   /* AIV 08/02/11 - now might have xprop list to process as well */
   if (nstp->st.scs.xprop_lstp != NULL)
     nstp->st.scs.xprop_lstp = cmp_xform_lstofsts(mdp, ostp->st.scs.xprop_lstp);
#endif
   break;
  case S_REPEAT:
   /* move ptr to new, old freed so no wrong cross links */
   nstp->st.srpt.reptmp_ofs = ostp->st.srpt.reptmp_ofs;
   nstp->st.srpt.repst = cmp_xform_lstofsts(mdp, ostp->st.srpt.repst);
   break;
  case S_REPSETUP:
   /* no contents just indicator for setting up next actual rep stmt */
   break;
 
  case S_FOREVER: case S_WHILE: case S_DO_WHILE:
   nstp->st.swh.lpst = cmp_xform_lstofsts(mdp, ostp->st.swh.lpst);
   break;
  case S_WAIT:
   nstp->st.swait.lpst = cmp_xform_lstofsts(mdp, ostp->st.swait.lpst);
   /* here just move pointer since needed by new statement in table */
   /* LOOKATME - is this already copied */
   nstp->st.swait.wait_dctp = ostp->st.swait.wait_dctp;
   /* also point dctp statement to new one */
   nstp->st.swait.wait_dctp->actionst = nstp->st.swait.lpst;
   break;
  case S_FOR:
   /* DBG remove --- */
   if (last_stp == NULL) __misc_terr(__FILE__, __LINE__);
   if (last_stp->stmttyp != S_FORASSGN) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* notice using already allocated storage - assumes dynamic dlopen so */
   /* no need to save and copy storage to runtime */
   nstp->st.sfor = ostp->st.sfor;
   nstp->st.sfor->forassgn = last_stp;
   /* for inc xformed in here */
   {
    struct st_t *stp2, *last_stp2, *tail_stp, *head_stp;
    int32 i, count;

    /* AIV 10/01/10 - need to now get the head of the list */
    /* before the copy get a count of stmts to the start of inc list */
    stp2 = ostp->st.sfor->forbody;
    for (count = 0; stp2 != NULL; stp2 = stp2->stnxt, count++)
     {
      if (stp2 == ostp->st.sfor->forinc) break;
     }

    /* DBG remove --- */
    if (stp2 == NULL) __misc_terr(__FILE__, __LINE__);
    /* ---- */

    nstp->st.sfor->forbody = cmp_xform_lstofsts(mdp, ostp->st.sfor->forbody);
   

    stp2 = nstp->st.sfor->forbody;
    for (i = 0; stp2 != NULL; stp2 = stp2->stnxt, i++)
     {
      /* if count is the inc head */
      if (i == count)
       {
        head_stp = stp2;
       }
      tail_stp = last_stp2;
      last_stp2 = stp2;
     }
    /* DBG remove --- */
    if (tail_stp->stmttyp != S_PROCA && tail_stp->stmttyp != S_INC &&
        tail_stp->stmttyp != S_DEC) 
       __misc_terr(__FILE__, __LINE__);
    /* --- */
    nstp->st.sfor->forinc = head_stp;
    nstp->st.sfor->forinc_tail = tail_stp;
   }
   break;
  case S_REPDCSETUP:
   /* no contents just indicator for setting up next actual rep stmt */
   break;
  case S_DELCTRL:
   /* stmt contents do not fit in record so link old ptr to new */ 
   nstp->st.sdc = ostp->st.sdc;
   /* here fix but no need to copy dellst */
   nstp->st.sdc->actionst = cmp_xform_lstofsts(mdp, ostp->st.sdc->actionst);
   break;
  case S_NAMBLK:
   nstp->st.snbtsk->tsksyp->el.etskp->st_namblkin = nstp;
   /* for named block, no continuation - must be subthread except in func */
   nstp->st.snbtsk->tskst = cmp_xform_lstofsts(mdp, ostp->st.snbtsk->tskst);
   break;
  case S_UNBLK:
   nstp->st.sbsts = cmp_xform_lstofsts(mdp, ostp->st.sbsts);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = ostp->st.fj.fjstps[fji]) == NULL) break;
     nstp->st.fj.fjstps[fji] = cmp_xform_lstofsts(mdp, fjstp);
    }
   break;
  case S_FUNCCALL:
  case S_TSKCALL:
#ifdef __AMS__
  case S_ABOUND_STEP: case S_ADISCONTINUITY:
#endif
   /* find new task through old to new symbol */
   /* for system tasks since points to itself gets same (right) sym */
   /* task itself xforms in xform task routine */

   /* need to fixup PLI tf systf cross linked tf recs only - not vpi */
   syp = nstp->st.stkc.tsksyx->lu.sy;
   if (syp->sytyp == SYM_STSK)
    {
     stbp = syp->el.esytbp;
     /* only way to tell if tf_ is by range of tsk veriusertf index */
     if (stbp->stsknum >= BASE_VERIUSERTFS
      && (int32) stbp->stsknum <= __last_veriusertf)
      {
       xform_tf_syst_enable(nstp);
      }
    }
   /* for vpi registered and built-in system tasks nothing to do */  
   /* for vpi systasks accessing vpi_ systf has index and values */
   /* needed in vpi_ t vpi systf data record */
   break;
  case S_QCONTA:
   /* SJM 02/23/02 - now malloc aux info, but can still use - no new malloc */
   nstp->st.sqca->qcatyp = ostp->st.sqca->qcatyp;
   nstp->st.sqca->regform = ostp->st.sqca->regform;
   nstp->st.sqca->rhs_qcdlstlst = ostp->st.sqca->rhs_qcdlstlst;
   /* AIV 11/15/07 - link on all qvalp->qcstp - this is needed at compile */
   /* time no need to do at runtime */
   if (__compiled_sim) link_qc_to_dces(mdp, nstp);
   break;
  case S_QCONTDEA:
   nstp->st.sqcdea.qcdatyp = ostp->st.sqcdea.qcdatyp;
   nstp->st.sqcdea.regform = ostp->st.sqcdea.regform;
   break;
  case S_CAUSE:
   /* must copy expr. even though know just event name */
   break;
  case S_DSABLE:
   break;
  case S_CONTINUE: case S_BREAK: case S_RETURN:  
   break;
  case S_GOTO:
   /* must 0 out dest. since fixed later with right target */
   nstp->st.sgoto = NULL;
   break;
  /* LOOKATME - need name resolving statement type no? */
  default: __case_terr(__FILE__, __LINE__);
 }
 return(nstp);
}
   
/*
 * link on all dcep->dceu2.dce_qcvalp->qcstp = newstp
 */
static void link_qc_to_dces(struct mod_t *mdp, struct st_t *stp)
{
 int32 ii, ibase;
 struct expr_t *lhsx;
 struct expr_t *catndp, *catlhsx;
 struct dceauxlstlst_t *dcllp;
 
 lhsx = stp->st.sqca->qclhsx;
 dcllp = stp->st.sqca->rhs_qcdlstlst;
 if (lhsx->optyp != LCB)
  {
   /* one list of peri lists */
   if (stp->st.sqca->regform)
    {
     for (ii = 0; ii < mdp->flatinum; ii++) 
      link_stmt_to_dce_list(dcllp->dcelsttab[ii], stp); 
    }
   else
    {
     ibase = mdp->flatinum*lhsx->szu.xclen;
     for (ii = 0; ii < ibase; ii++) 
      link_stmt_to_dce_list(dcllp->dcelsttab[ii], stp); 
    }
  } 
 else
  {
   /* AIV 05/09/11 - need to go to next dcellst here for concat version */
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x,
        dcllp = dcllp->dcelstlstnxt)
    {
     catlhsx = catndp->lu.x;

     if (stp->st.sqca->regform)
      {
       for (ii = 0; ii < mdp->flatinum; ii++) 
         link_stmt_to_dce_list(dcllp->dcelsttab[ii], stp); 
      }
     else
      {
       ibase = mdp->flatinum*catlhsx->szu.xclen;
       /* if not list end, next pass will set */
       for (ii = 0; ii < ibase; ii++)
         link_stmt_to_dce_list(dcllp->dcelsttab[ii], stp); 
      }
    }
  }
}
         
/*
 * link on all dces on a list to the new stmt
 */
static void link_stmt_to_dce_list(struct dceauxlst_t *dclp, struct st_t *stp)
{
 struct dcevnt_t *dcep;
 struct qcval_t *qcvalp;

 for (; dclp != NULL; dclp = dclp->dclnxt)
  {
   dcep = dclp->ldcep; 
   qcvalp =  dcep->dceu2.dce_qcvalp;
   /* DBG remove --- */
   if (qcvalp == NULL) __misc_terr(__FILE__, __LINE__);
   qcvalp->qcstp = stp;
  }
}

/*
 * xform tf_ style sys task enable by updating tf rec 
 *
 * not needed for vpi style syst enables because compiletf already called
 *
 * LOOKATME - could pass systf ptrs since already computed
 */
static void xform_tf_syst_enable(struct st_t *nstp)
{
 int32 ai;
 struct tskcall_t *tkcp;
 struct tfrec_t *tfrp;
 struct expr_t *argxp;
 struct tfarg_t *tfap;

 tkcp = &(nstp->st.stkc);
 /* DBG remove --- */
 if (tkcp->tkcaux.trec == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* tsk call record contains tfrec for PLI 1.0 registered */
 tfrp = tkcp->tkcaux.trec;

 /* back link tfrec for systask enable to new moved stmt */
 tfrp->tfu.tfstp = nstp;
 /* notice for tsk, targs 1st left has actual argument - no need for next */
 argxp = tkcp->targs;
 /* update all the tfarg expr ptrs to moved expr */
 for (ai = 1; ai < tfrp->tfanump1; ai++, argxp = argxp->ru.x)
  {
   /* DBG remove -- */
   if (argxp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */

   tfap = &(tfrp->tfargs[ai]);
   tfap->arg.axp = argxp->lu.x;
  }
}

/*
 * ROUTINES TO XFORM (MOVE TO INDEXABLE TABLE) EXPRESSIONS
 */

/*
 * compile transform list of case items
 *
 * no need to copy but must replace statement lists and exprs inside
 */
static void cmp_xform_csitemlst(struct mod_t *mdp, struct csitem_t *csip)
{
 for (; csip != NULL; csip = csip->csinxt)
  {
   if (csip->csist != NULL) csip->csist = cmp_xform_lstofsts(mdp, csip->csist);
  }
}

/*
 * GOTO FIXUP ROUTINES
 */

/*
 * compile transform all initial/always statement lists
 */
static void cmp_xform_ialst(struct mod_t *mdp)
{
 struct ialst_t *ialp;
 int32 iatyp;

 __processing_func = FALSE;
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   ialp->iastp = cmp_xform_lstofsts(mdp, ialp->iastp);
  } 
 __prpsti = 0;
 __nbsti = -1;
 __prpstk[0] = NULL;
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   iatyp = ialp->iatyp;
   /* AIV 07/12/12 - now supporting new SV always_* types */
   if (iatyp == ALWAYS || iatyp == ALWAYS_COMB || iatyp == ALWAYS_FF || 
       iatyp == ALWAYS_LATCH)
    {
     cxf_fixup_loopend_goto(ialp->iastp, ialp->iastp);
    }
   __cxf_fixup_lstofsts_gotos(ialp->iastp, TRUE);

   /* DBG remove --- */ 
   if (__prpsti != 0) __misc_terr(__FILE__, __LINE__); 
   /* --- */
  } 
}

/*
 * fixup loop end gotos
 */
static struct st_t *cxf_fixup_loopend_goto(struct st_t *begstp, 
 struct st_t *targstp)
{
 struct st_t *stp; 
 struct st_t *last_stp;

 /* DBG remove --- */
 if (begstp == NULL) __arg_terr(__FILE__, __LINE__);
 /* --- */

 /* find last statement in loop - know has at least one */
 for (stp = begstp, last_stp = NULL; stp != NULL; stp = stp->stnxt)
  {
   last_stp = stp;
  }
 /* DBG remove --- */
 if (last_stp == NULL) __arg_terr(__FILE__, __LINE__);
 if (last_stp->stmttyp != S_GOTO) __arg_terr(__FILE__, __LINE__);
 if (!last_stp->lpend_goto) __arg_terr(__FILE__, __LINE__);
 if (targstp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 last_stp->st.sgoto = targstp;

 if (__debug_flg)
  {
   char s1[RECLEN], s2[RECLEN], s3[RECLEN];

   __dbg_msg("++ loop: xform goto after %s at %s back to stmt %s at %s\n",
    __to_sttyp(s1, last_stp->stmttyp), __bld_lineloc(__xs, 
    last_stp->stfnam_ind, last_stp->stlin_cnt), __to_sttyp(s2,
    begstp->stmttyp), __bld_lineloc(s3, targstp->stfnam_ind,
    targstp->stlin_cnt));
  }
 return(last_stp);
}

/*
 * fixup all gotos in list of stmts
 *
 * know all statement transformed - sets correct new goto dest.
 */
extern void __cxf_fixup_lstofsts_gotos(struct st_t *hdrstp, int32 has_endgoto)
{
 struct st_t *stp;
 int32 fji;
 struct for_t *forp;
 struct st_t *stp2, *fjstp;
 struct st_t *save_continue_stp, *save_break_stp, *last_stp;

 for (stp = hdrstp; stp != NULL; stp = stp->stnxt)
  {
   __sfnam_ind = stp->stfnam_ind;
   __slin_cnt = stp->stlin_cnt;

   switch ((byte) stp->stmttyp) {
    case S_INC: case S_DEC:
    case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA: break;
    case S_IF:
     if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
     __cxf_fixup_lstofsts_gotos(stp->st.sif.thenst, TRUE);
     if (stp->st.sif.elsest != NULL)
      __cxf_fixup_lstofsts_gotos(stp->st.sif.elsest, TRUE);
     if (stp->stnxt != NULL) __pop_prpstmt();
     break;
    case S_CASE:
     cxf_fixup_case_gotos(stp);
     break;
    case S_FOR:
     forp = stp->st.sfor;
     /* LOOKATME - is prep change needed */
     /* goto to for itself */
     /* AIV 09/28/10 - save/restore/set loop continue/break statements */ 
     save_continue_stp = __st_loop_continue; 
     save_break_stp = __st_loop_break;
     last_stp = cxf_fixup_loopend_goto(forp->forbody, stp);
     __st_loop_continue = forp->forinc; 
     __st_loop_break = last_stp->st.sgoto->stnxt;
     __cxf_fixup_lstofsts_gotos(forp->forbody, FALSE);
     __st_loop_continue = save_continue_stp; 
     __st_loop_break = save_break_stp; 
     break;
    case S_FOREVER: case S_WHILE: case S_DO_WHILE:
     /* AIV 09/28/10 - save/restore/set loop continue/break statements */ 
     save_continue_stp = __st_loop_continue; 
     save_break_stp = __st_loop_break;
     last_stp = cxf_fixup_loopend_goto(stp->st.swh.lpst, stp);
     __st_loop_continue = last_stp; 
     __st_loop_break = last_stp->st.sgoto->stnxt;
     __cxf_fixup_lstofsts_gotos(stp->st.swh.lpst, FALSE);
     __st_loop_continue = save_continue_stp; 
     __st_loop_break = save_break_stp; 
     break;
    case S_REPEAT:
     /* allocate per inst. count storage */ 
     /* add loop back to repeat header */
     /* AIV 09/28/10 - save/restore/set loop continue/break statements */ 
     save_continue_stp = __st_loop_continue; 
     save_break_stp = __st_loop_break;
     last_stp = cxf_fixup_loopend_goto(stp->st.srpt.repst, stp);
     __st_loop_continue = last_stp; 
     __st_loop_break = last_stp->st.sgoto->stnxt;
     __cxf_fixup_lstofsts_gotos(stp->st.srpt.repst, FALSE);
     __st_loop_continue = save_continue_stp; 
     __st_loop_break = save_break_stp; 
     break;
    case S_WAIT:
     if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
     __cxf_fixup_lstofsts_gotos(stp->st.swait.lpst, TRUE);
     if (stp->stnxt != NULL) __pop_prpstmt();
     break;
    case S_DELCTRL:
     /* first find end of decltrl chain */
     /* if no actoin statement - nothing to do */
     if (stp->st.sdc->actionst == NULL) break; 
     for (stp2 = stp->st.sdc->actionst;; stp2 = stp2->st.sdc->actionst)
      {
       /* keep going until delay control has no action statement or */
       /* a non delay control action statement */
       /* case "#10 begin #20 ..." - is not delay control chain */
       if (stp2 == NULL || stp2->stmttyp != S_DELCTRL || stp2->st_unbhead)
        break;
      }
     /* ??? 11/10/99 -  if (stp2 == NULL || stp2->stmttyp != S_GOTO) break; */
     if (stp2 == NULL) break;
     /* do the goto fix up */
     if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
     __cxf_fixup_lstofsts_gotos(stp2, TRUE);
     /* only end of chain can have "real" statement */
     if (stp->stnxt != NULL) __pop_prpstmt();
     break;
    case S_NAMBLK:
     /* for named block, no continuation - must be subthread except in func */
     __push_nbstk(stp);
     if (__processing_func)
      { 
       /* for function no task scheduled - run inline to need goto to cont */
       /* at end */
       if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
       __cxf_fixup_lstofsts_gotos(stp->st.snbtsk->tskst, TRUE);
       if (stp->stnxt != NULL) __pop_prpstmt();
      }
     else
      {
       __push_prpstmt((struct st_t *) NULL);
       __cxf_fixup_lstofsts_gotos(stp->st.snbtsk->tskst, FALSE);
       __pop_prpstmt();
      }
     __pop_nbstk();
     break;
    case S_UNBLK:
     if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);
     /* need continuation for simple block */
     __cxf_fixup_lstofsts_gotos(stp->st.sbsts, TRUE);
     if (stp->stnxt != NULL) __pop_prpstmt();
     break;
    case S_UNFJ:
     __push_prpstmt((struct st_t *) NULL);
     /* continuation inside these must be NULL, not stacked val */
     for (fji = 0;; fji++)
      {
       if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
       __cxf_fixup_lstofsts_gotos(fjstp, FALSE);
      }
     __pop_prpstmt();
     break;
    case S_DSABLE:
     /* inside function disables are gotos to next statement in up block */
     if (__processing_func) cxf_fixup_func_dsabl_gotos(stp);
     /* any other disable is task scheduled */
     break;
#ifdef __AMS__
    /* these are all simply like assigns */
    case S_BRNCH_CNTRB: case S_IND_BRNCH_CNTRB:
    case S_ABOUND_STEP: case S_ADISCONTINUITY:
     break;
#endif
    case S_GOTO:
     /* goto can only be last */
     /* DBG remove --- */
     if (stp->stnxt != NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* if loopend dest. set and nothing to do here */
     if (stp->lpend_goto) return;
     if (has_endgoto && __prpstk[__prpsti] != NULL) 
      {
       stp->st.sgoto = __prpstk[__prpsti];
       /* in this rare case will not have line number - can it happen */
      }
     /* DBG remove -- */
     else __case_terr(__FILE__, __LINE__); 
     /* -- */
     return;
    case S_BREAK: 
     /* AIV 10/13/10 - this can be NULL for break stmt with no following stmt */
     /* DBG remove ---
     if (__st_loop_break == NULL) __misc_terr(__FILE__, __LINE__);
     --- */
     stp->st.sgoto = __st_loop_break;
     break;
    case S_CONTINUE:
     /* DBG remove ---*/
     if (__st_loop_continue == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     stp->st.sgoto = __st_loop_continue;
     break;
    case S_RETURN: break;
    default:
     /* statements with no processing ignored thru here */
     break;
   }
  }
 /* block with no loop end goto returns thru here */ 
}

/*
 * fixup all gotos in case stmt
 */
static void cxf_fixup_case_gotos(struct st_t *stp)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;

 if (stp->stnxt != NULL) __push_prpstmt(stp->stnxt);

 dflt_csip = stp->st.scs.csitems;
 /* this will move up stack to add goto after ending stp */
 for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
  {
   __cxf_fixup_lstofsts_gotos(csip->csist, TRUE);
  }

 /* this will move up stack to connect ending stnxt to next exec. place */
 if (dflt_csip->csist != NULL)
  __cxf_fixup_lstofsts_gotos(dflt_csip->csist, TRUE);

#ifdef __XPROP__
 /* AIV 08/02/11 - now might have xprop list to process as well */
 if (stp->st.scs.xprop_lstp != NULL)
  __cxf_fixup_lstofsts_gotos(stp->st.scs.xprop_lstp, TRUE);
#endif

 if (stp->stnxt != NULL) __pop_prpstmt();
}

/*
 *
 * inside function disable are like c continue and are just gotos
 */
static void cxf_fixup_func_dsabl_gotos(struct st_t *stp)
{
 int32 i;
 struct expr_t *dsxp;
 struct sy_t *syp;
 struct task_t *dsatskp;

 dsxp = stp->st.sdsable.dsablx;
 syp = dsxp->lu.sy; 
 /* disable of func. indicated by nil next statmenet - use fcall stack */
 /* system function disable no next */
 if (syp->sytyp == SYM_F) return;

 dsatskp = syp->el.etskp;
 /* know every named block when entered in function name block is stacked */
 for (i = __nbsti; i >= 0; i--)
  {
   if (__nbstk[i]->st.snbtsk == dsatskp)
    {
     /* this can be nil */
     stp->st.sdsable.func_nxtstp = __nbstk[i]->stnxt;
     return;
    }
  }
 /* know always enclosing, or will not get here - earlier error */
 __case_terr(__FILE__, __LINE__);
}

/*
 * compile transform tasks
 *
 * this also handle tasks - task specific task field (one for now)
 * set when statemetns tranformed
 *
 * task args do not have expr. forms
 */
static void cmp_xform_tasks(struct mod_t *mdp)
{
 struct task_t *tskp;

 /* finally check user tasks and function statements */
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   /* named blocks handled as statement where they occur */
   if (tskp->tsktyp == FUNCTION) __processing_func = TRUE;
   else if (tskp->tsktyp == TASK) __processing_func = FALSE; 
   else continue;
   /* DBG remove -- */
   if (__debug_flg)
    {
     __dbg_msg("+++ xforming task %s\n", tskp->tsksyp->synam); 
    }
   /* --- */

   tskp->tskst = cmp_xform_lstofsts(mdp, tskp->tskst);
  }
 __prpsti = 0;
 __nbsti = -1;
 __prpstk[0] = NULL;
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   /* named blocks handled as statement where they occur */
   if (tskp->tsktyp == FUNCTION) __processing_func = TRUE;
   else if (tskp->tsktyp == TASK) __processing_func = FALSE; 
   else continue;

   __cxf_fixup_lstofsts_gotos(tskp->tskst, FALSE);
   /* AIV 12/15/10 - need to know where the end of the non-task stmts end */
   tskp->end_of_stmtndx = __last_modsti + 1;
  } 
 /* DBG remove --- */ 
 if (__prpsti != 0) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 /* AIV 10/20/05 - must reset __processing_func to FALSE */
 __processing_func = FALSE;
}

/*
 * dump a module's statement table
 *
 * number to dump is arg so can use on partially built table
 */
extern void __dmp_msttab(struct mod_t *mdp, int32 snum)
{
 int32 si, si2;
 struct st_t *stp;

 if (mdp->mstnum == 0) 
  {
   /* DBG remove ---
   __dbg_msg("+++ module %s has no statements +++\n", mdp->msym->synam);
   --- */
   return;
  }
 /* DBG remove --- */
 if (mdp->mstmts == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 __dbg_msg("+++ module %s has %d statements +++\n", mdp->msym->synam,
  mdp->mstnum);
 __push_wrkitstk(mdp, 0); 
 for (si = 0; si < snum; si++)
  {
   stp = mdp->mstmts[si];
   if (stp->stmttyp == S_GOTO)
    {
     si2 = stp->st_ndx;
     __dbg_msg("GOTO STMT %d (goto %d):\n", si, si2);
    }
   else __dbg_msg("STMT %d:\n", si);
   __dmp_stmt(stdout, stp, FALSE);
   __dbg_msg("\n");
  }
 __pop_wrkitstk();
}

/*
 * ROUTINES TO INLINE FOR LOOPS
 */

/*
 * try to inline all for loops for each module/tasks
 */
extern void __try_to_fold_for_loops(void)
{
 struct mod_t *mdp;
 struct ialst_t *ialp;
 struct task_t *tskp;
 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   /* do ever init/always list */
   for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)  
     try_fold_for_loop_lstofstmts(ialp->iastp);
   
   /* now each task */
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
     try_fold_for_loop_lstofstmts(tskp->tskst);
   __pop_wrkitstk();
  }
}

/*
 * try to fold all for loops in stmt list
 */
static void try_fold_for_loop_lstofstmts(struct st_t *hdstp)
{
 struct st_t *stp; 

 for (stp = hdstp; stp != NULL;)
  {
   stp = try_fold_for_loop_stmt(stp);
  }
}

/*
 * handle each stmt type and attempt to fold for loops
 */
static struct st_t *try_fold_for_loop_stmt(struct st_t *stp)
{
 int32 fji;
 struct st_t *astp, *fjstp, *cont_stp, *nstp;
 struct csitem_t *csip, *dflt_csip;
 struct delctrl_t *dctp;
 struct net_t *np;
 struct task_t *tskp;
 int32 from_val, to_val, is_inc;
 
 cont_stp = NULL;
 switch ((byte) stp->stmttyp) {
  case S_RHSDEPROCA:
   break;
  case S_NBPROCA:
   break;
  case S_IF:
   try_fold_for_loop_lstofstmts(stp->st.sif.thenst);
   if (stp->st.sif.elsest != NULL)
    {
     try_fold_for_loop_lstofstmts(stp->st.sif.elsest);
    }
   break;
  case S_CASE:
   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
    {
     try_fold_for_loop_lstofstmts(csip->csist);
    } 
   if (dflt_csip->csist != NULL && dflt_csip->csist->stmttyp != S_NULL)
    {
     try_fold_for_loop_lstofstmts(dflt_csip->csist);
    }
#ifdef __XPROP__
   /* AIV 08/02/11 - now might have xprop list to process as well */
   if (stp->st.scs.xprop_lstp != NULL)
     try_fold_for_loop_lstofstmts(stp->st.scs.xprop_lstp);
#endif
   break; 
  case S_FOREVER:
   try_fold_for_loop_lstofstmts(stp->st.swh.lpst);
   break;
  case S_REPEAT: 
   try_fold_for_loop_lstofstmts(stp->st.srpt.repst);
   break;
  case S_WHILE:
   try_fold_for_loop_lstofstmts(stp->st.swh.lpst);
   break;
  case S_FOR:
   /* see if for loop is foldable */
   np = is_for_foldable(stp, &from_val, &to_val, &is_inc);
   /* if net returned inline it */
   if (np != NULL)
    {
     nstp = fold_for_loop(stp, from_val, to_val, np, is_inc);
     /* may still not be able to fold loop in inc variable on lhs */
     if (nstp != NULL)
      {
       *stp = *nstp;
      }
    }
   break;
  case S_WAIT:
   try_fold_for_loop_lstofstmts(stp->st.swh.lpst);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   if (dctp->dctyp == DC_DELAY || dctp->dctyp == DC_EVENT)
    {
     astp = dctp->actionst;
     cont_stp = astp;
    }
   else
    {
     /* handle rhs forms */
     astp = stp->st.sdc->actionst;
     /* DBG remove -- */
     if (astp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     if (astp->stmttyp == S_RHSDEPROCA)
      {
       cont_stp = astp;
      }
     /* if non blocking no entry bit to set but must cont at right stmt */
     else if (astp->stmttyp == S_NBPROCA)
      {
       try_fold_for_loop_stmt(astp);
       cont_stp = astp->stnxt;
      }
     else __case_terr(__FILE__, __LINE__);
    }
   return(cont_stp);
  case S_NAMBLK:
   /* was doing this for all named blocks */
   tskp = stp->st.snbtsk;
   try_fold_for_loop_lstofstmts(tskp->tskst);
   break;
  case S_UNBLK:
   try_fold_for_loop_lstofstmts(stp->st.sbsts);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     /* first stmt of fork-join prong always entered from scheduler */
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;

     /* if this is named blocked adjust in next routine */
     if (fjstp->stmttyp == S_UNBLK)
      {
       try_fold_for_loop_lstofstmts(fjstp->st.sbsts);
      }
     else 
      {
       try_fold_for_loop_lstofstmts(fjstp);
      }
    }
   break;
  case S_TSKCALL:
   break;
  case S_GOTO: 
   if (stp->dctrl_goto) return(stp->st.sgoto);
   break;
  case S_REPDCSETUP:
   break;
  default: break;
 }
 return(stp->stnxt);
}

/*
 * check to see if a for loop is foldable
 * look for the common for loop structures if it is foldable returns 
 * the net which is the loop counter and the start and end loops values
 * is_inc - TRUE-> is for ++ else --
 *
 * for (i = 0; i <= 2; i = i+1)
 * for (i = 2; i != 0; i = i-1)
 */
static struct net_t *is_for_foldable(struct st_t *stp, int32 *from_val,
 int32 *to_val, int32 *is_inc)
{
 struct for_t *forp;
 struct st_t *assgn_stp, *inc_stp, *stp2;
 struct expr_t *termx, *lhsx, *rhsx;
 struct xstk_t *xsp;
 struct net_t *np;
 int32 num_stmts, tval, niters;

 forp = stp->st.sfor;

 /* AIV 04/08/11 - skipping SV loops which have a continue/break */
 if (forp->has_continue || forp->has_break) return(NULL);

 *from_val = 0;
 *to_val = 0;
 *is_inc = TRUE;
 num_stmts = 0;
 for (stp2 = forp->forbody; stp2 != NULL; stp2 = stp2->stnxt)
  {
   /* if has delay the loop index might have change - so cannot just inline */
   /* this is rare but can occur */
   if (stp2->stmttyp == S_DELCTRL) return(NULL);
   if (stp2->stmttyp == S_UNFJ) return(NULL);
   /* don't really have mechanism to split name blocks - just skip */
   if (stp2->stmttyp == S_NAMBLK) return(NULL);
   /* if nested loops do not inline */
   if (stp2->stmttyp == S_FOR) return(NULL);
   if (stp2->stmttyp == S_WHILE) return(NULL);
   if (stp2->stmttyp == S_REPEAT) return(NULL);
   num_stmts++;
  }
 assgn_stp = forp->forassgn;
 lhsx = assgn_stp->st.spra.lhsx; 
 rhsx = assgn_stp->st.spra.rhsx;
 /* better be basic i = const */
 if (lhsx->optyp != ID) return(NULL);
 np = lhsx->lu.sy->el.enp;
 /* counter must be an integer or int */ 
 if (np->ntyp != N_INT && np->ntyp != N_CINT) return(NULL);
 if (np->nwid > INTBITS) return(NULL);
 if (!__is_const_expr(rhsx)) return(NULL);
 
 /* SV can have for (i = 0, j = 0 - just skip this case */
 if (assgn_stp->stnxt != NULL)
  {
   if (assgn_stp->stnxt->stmttyp != S_FOR) return(NULL);
  }

 xsp = __eval_xpr(rhsx);
 /* if bpart not zero skip it */
 if (xsp->bp[0] != 0) 
  {
   __pop_xstk();
   return(NULL);
  }
 *from_val = (int32) xsp->ap[0];
 __pop_xstk();
 
 /* terminate uses the same variable */
 termx = forp->fortermx;
 lhsx = termx->lu.x;
 if (lhsx->optyp != ID) return(NULL);
 if (lhsx->lu.sy->el.enp != np) return(NULL);
 rhsx = termx->ru.x;
 if (!__is_const_expr(rhsx)) return(NULL);

 xsp = __eval_xpr(rhsx);
 if (xsp->bp[0] != 0) 
  {
   __pop_xstk();
   return(NULL);
  }
 tval = (int32) xsp->ap[0];
 __pop_xstk();
 /* inc better be i = i + 1 or i = i -1 */
 inc_stp = forp->forinc;
 if (inc_stp->stmttyp != S_PROCA) 
  {
   /* SV can now has ++/-- */
   if (inc_stp->stmttyp != S_INC && inc_stp->stmttyp != S_DEC)
    {
     return(NULL);
    }
  }

 /* SV can have for (i = 0; i < 4; i++, j++)  - just skip this case */
 if (inc_stp->stnxt != NULL) return(NULL);

 lhsx = rhsx = NULL;
 if (inc_stp->stmttyp == S_INC) 
  {
   lhsx = inc_stp->st.spra.lhsx->lu.x; 
   *is_inc = TRUE;
  }
 else if (inc_stp->stmttyp == S_DEC) 
  {
   lhsx = inc_stp->st.spra.lhsx->lu.x; 
   *is_inc = FALSE;
  }
 else
  {
   lhsx = inc_stp->st.spra.lhsx; 
   rhsx = inc_stp->st.spra.rhsx;
   if (rhsx->optyp != PLUS) 
    {
     if (rhsx->optyp == MINUS)
      {
       *is_inc = FALSE;
      }
     else return(NULL);
    }
  }
 if (lhsx->optyp != ID) return(NULL);
 if (lhsx->lu.sy->el.enp != np) return(NULL);


 /* if SV ++/-- do not need to check +1 or -1 */
 if (rhsx != NULL)
  {
   lhsx = termx->lu.x;
   if (lhsx->optyp != ID) return(NULL);
   if (lhsx->lu.sy->el.enp != np) return(NULL);
   rhsx = rhsx->ru.x;

   if (!__is_const_expr(rhsx)) return(NULL);
   xsp = __eval_xpr(rhsx);
   /* only handling inc/dec by one */
   if (xsp->ap[0] != 1 || xsp->bp[0] != 0) 
    {
     __pop_xstk();
     return(NULL);
    }
   __pop_xstk();
  }

 if (*is_inc)
  {
   //case /* <= */ RELLE:
   if (termx->optyp == RELLE)
    {
     *to_val = tval + 1;
    }
   //case /* < */ RELLT: 
   else if (termx->optyp == RELLT || termx->optyp == RELNEQ)
    {
     *to_val = tval;
    }
   else return(NULL);
   /* nothing to loop - just leave the stmt as is */ 
   if (*from_val >= *to_val) return(NULL);
   niters = *to_val - *from_val;
  }
 else
  {
   //case /* >= */ RELGE:
   if (termx->optyp == RELGE)
    {
     *to_val = tval - 1;
    }
   //case /* > */ RELGT: 
   else if (termx->optyp == RELGT || termx->optyp == RELNEQ)
    {
     *to_val = tval;
    }
   else return(NULL);
   if (*to_val >= *from_val) return(NULL);
   niters = *from_val - *to_val;
  }
 /* cap at size of the statements which can be inlined */
 /* currently - number of (loop interations* num stmts in loop) <= WBITS*10 */
 if (niters*num_stmts > WBITS*10) return(NULL);
 return(np);
}

/*
 * Fold a for loop with values from_value => to_value
 * the folded variable (counter) is inc_np 
 * is_inc => TRUE then ++ else --
 * if variable is on lhs anywhere in loop cannot fold loop return NULL
 *
 */
static struct st_t *fold_for_loop(struct st_t *for_stp, int32 from_val, 
 int32 to_val, struct net_t *inc_np, int32 is_inc)
{
 struct for_t *forp;
 struct st_t *stp, *new_list_hd, *last_stp, *nstp, *assgn_stp;
 struct expr_t *lhsx, *rhsx;
 int32 i, save_onlhs, save_ct_n_onlhs;

 forp = for_stp->st.sfor;
 save_ct_n_onlhs = FALSE;
 /* save and turn on net on lhs */
 save_onlhs = inc_np->n_onlhs;
 inc_np->n_onlhs = FALSE;
 if (inc_np->nrngrep == NX_CT)
  {
   save_ct_n_onlhs = inc_np->nu.ct->n_onlhs;
   inc_np->nu.ct->n_onlhs = FALSE;
  }
 /* now check if net is on lhs - if TRUE cannot fold this loop */
 for (stp = forp->forbody; stp != NULL; stp = stp->stnxt)
  {
   __chk_lstofsts(stp);
  }
 /* net is assigned inside of loop cannot fold loop */
 if (inc_np->n_onlhs)
  {
   /* restore saved flag */
   inc_np->n_onlhs = save_onlhs;
   return(NULL);
  }
 inc_np->n_onlhs = save_onlhs;
 /* net is assigned inside of loop cannot fold loop */
 if (inc_np->nrngrep == NX_CT)
  {
   if (inc_np->nu.ct->n_onlhs)
    {
     /* restore saved flag */
     inc_np->nu.ct->n_onlhs = save_ct_n_onlhs;
     return(NULL);
    }
   inc_np->nu.ct->n_onlhs = save_ct_n_onlhs;
  }

 new_list_hd = NULL;
 /* turn on flag to fold loop inc value */
 inc_np->fold_for_inc = TRUE;
 last_stp = NULL;
 /* set global folding flag */
 __folding_for_loop = TRUE;
 /* go through the loop folding values */
 for (i = from_val; ; )
  {
   __fold_for_value = i;
   /* copy and fold all stmts in the loop */
   for (stp = forp->forbody; stp != NULL; stp = stp->stnxt)
    {
     nstp = __copy_lstofsts(stp);
     __set_expr_fold_value_stlst(nstp);
     __chk_lstofsts(nstp);
     if (last_stp == NULL) new_list_hd = nstp;
     else last_stp->stnxt = nstp;
     last_stp = nstp;
    }

   /* add the i = const expression */
   assgn_stp = __alloc_stmt(S_PROCA);
   lhsx = __alloc_newxnd();
   lhsx->optyp = ID;
   lhsx->lu.sy = inc_np->nsym;
   lhsx->has_sign = inc_np->n_signed;
   /* make the constant */
   rhsx = __alloc_newxnd();
   if (is_inc) i++;
   else i--;
   __fold_for_value = i;
   __set_numval(rhsx, (word32) i, 0, INTBITS);

   assgn_stp->st.spra.lhsx = lhsx;
   assgn_stp->st.spra.rhsx = rhsx;
   assgn_stp->stlin_cnt = for_stp->stlin_cnt;
   assgn_stp->stfnam_ind = for_stp->stfnam_ind;
   __chk_lstofsts(assgn_stp);
   if (last_stp == NULL) new_list_hd = assgn_stp;
   else last_stp->stnxt = assgn_stp;
   last_stp = assgn_stp;
   if (i == to_val) break;
  }
 __fold_for_value = -1;
 __folding_for_loop = FALSE;
 last_stp->stnxt = for_stp->stnxt;
 inc_np->fold_for_inc = FALSE;
 return(new_list_hd);
}
