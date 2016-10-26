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

/* local prototypes */
static void set_lhs_expr_drvrtyp(struct expr_t *, int32, int32, int32);
static int32 comp_pre_elab_norm_con_ndx(struct net_t *, struct expr_t *, int32,
 int32);
static int32 comp_pre_elab_wire_ndx(struct net_t *, struct expr_t *,
 int32, int32);
static int32 is_nonis_const_expr(struct expr_t *);
static void set_scalar_drvr_type(struct net_t *, int32);
static void set_vec_drvr_type(struct net_t *, int32, int32, int32);
static int32 port_expr_has_wrong_dir_drvr(struct expr_t *, int32, int32,
 int32, int32, int32);
static int32 find_max_rng_drvr_state(struct net_t *, int32, int32);
static int32 expr_decl_lvalue(struct expr_t *);
static void chg_mpx_to_bid(struct expr_t *);
static void free_design_ndrvrs(void);

static void bld_timstr_vals(void);
static void from_gen_mark_all_parm_widthdet(struct mod_t *);
static void inrnges_mark_params(struct symtab_t *);
static void psel_set_allexprs(struct mod_t *);
static void stmt_do_inpsel_set(struct st_t *);
static void lstofsts_do_inpsel_set(struct st_t *);
static void csitemlst_do_inpsel_set(struct csitem_t *);
static void inpsel_xpr_markparam(struct expr_t *);
static void chk_undef_syms(struct symtab_t *, word32);
static void chkset_1mwire_rnges(void);
static void chk_1wire_delay(struct net_t *);
static void fill_wire_arr_wrkstab(struct net_t *);
static void fill_mda_wire_wrkstab(struct net_t *, struct mda_t *, char *, 
 int32);
static void tmp_fill_mda_rnges(struct net_t *);
static void chk_modsym(struct sy_t *);
static void chk_1wire(struct net_t *);
static void chk_1reg(struct net_t *);
static void mark_sttypewires(void);
static void mark_stdr_wires(void);
static void mark_stdr_inout_wired_logic(void);
static int32 has_non_stren_wired_net(struct expr_t *);
static int32 net_type_tri(word32);
static int32 chk_hasst_wires(struct mod_t *, struct expr_t *);
static void mark_stwires(struct mod_t *, struct expr_t *);
static void prop_stsdown(void);
static void prop_stsup(void);
static int32 chkdel_expr(struct expr_t *, char *, int32);
static int32 nd_delnum(struct expr_t *, char *);
static int32 nd_delisnum(struct expr_t *, char *);
static void freeset_is0del(struct expr_t *, int32);
static void wr_ndisdel_err(struct expr_t *, int32, char *);
static void chk_wire_rng(struct net_t *);
static int32 chk_wire_dma_rng(struct net_t *);
static void chg_rng_isnum_to_num(struct net_t *, struct expr_t *, char *);
static int32 chk_prtwidth(struct expr_t *, struct mod_pin_t *);
static void emit_shorted_informs(int32);
static void emit_1net_shorted_informs(struct mod_pin_t *, int32,
 struct net_t *, int32);
static int32 net_in_expr(struct net_t *, struct expr_t *);
static int32 xhas_multconn_wire(struct expr_t *);
static void emit_nonbid_shortwarn(struct mod_pin_t *, struct expr_t *);
static void reconn_1mod_gateterms(struct mod_t *);
static struct expr_t *bld_bsel_expr(struct net_t *, int32);

static int32 legal_gia_conn_concat(struct expr_t *);
static void reconn_1mod_instports(struct mod_t *);
static struct expr_t *bld_psel_expr(struct net_t *, int32, int32);
static void conn_1gateterm_concat(struct mod_t *, int32, struct expr_t *, int32);
static void conn_1instport_concat(struct mod_t *, int32, struct gia_aux_t *,
 struct expr_t *, int32, int32);
static struct exprlst_t *splt_icat_align_xlist(struct expr_t *, int32);
static struct expr_t *bld_num_expr(struct xstk_t *);
static void set_1mpx_stren(struct expr_t *);
static void chk_1tsk(struct task_t *);
static void chk_inst_conns(void);
static void chk_iconn_downxmr(struct inst_t *, struct expr_t *);
static void chk_iconn_mixeddirrng(struct inst_t *, struct mod_pin_t *,
 struct expr_t *);
static void chk_gates(void);
static int32 chk_1bltingate(struct gate_t *);
static void gate_errifn(struct gate_t *, int32);
static void chk_gate_nostren(struct gate_t *);
static void chk_tran_gate(struct gate_t *);
static int32 chk_tran_terms_same(struct gate_t *);
static void set_unc_gateterm(struct gate_t *, int32);
static void chk_1bit_tran(struct gate_t *, struct expr_t *, struct net_t *,
 int32);
static void chk_tranif_gate(struct gate_t *);
static void chk_pull_gate(struct gate_t *);
static int32 chk_1udp(struct gate_t *);
static int32 chk_gate_source(struct gate_t *, struct expr_t *, int32, int32,
 struct net_t **);
static void chk_contas(void);
static void cnv_1bcas_into_garr(int32, struct conta_t *); 
static struct gate_t *convert_1bca_togate(struct gate_t *,
 struct conta_t *);
static void nd_1bit_concat(struct expr_t *);
static void chk_getpat_nonscal(struct expr_t *);
static void chk_nodel_stmt(struct st_t *);
static void chk_nodel_dsable(struct st_t *);
static int32 lhsexpr_hassym(struct expr_t *, struct sy_t *);
static void chk_varinits(void);
static void chk_stmts(void);
static void chk_1stmt(struct st_t *);
static void chk_case(struct st_t *);
static void chk_dctrl(struct delctrl_t *);
static void bld_stlst_evxlst(struct st_t *, int32);
static void bld_stmt_evxlst(struct st_t *, int32);
static void bld_case_evxlst(struct st_t *, int32);
static void bld_tskenable_evxlst(struct st_t *, int32);
static void bld_rhs_impl_evxlst(struct expr_t *, int32);
static void bld_lhs_impl_evxlst(struct expr_t *, int32);
static int32 xp_in_evxlst(struct expr_t *); 
static struct expr_t *bld_evlst_comma_expr(void);
static void chk_qclvalue(struct expr_t *, word32, int32 *);
static void set_qc_frcassgn_net(struct expr_t *);
static int32 nd_qcreg(struct expr_t *);
static void chk_circular_qc_stmt(struct st_t *);
static int32 rhs_expr_has_net(struct expr_t *, struct net_t *);
static void chk_disable(struct st_t *);
extern void __add_isnum_to_tree(void *, int32, int32);
static void add_task_to_task_call(struct task_t *, struct task_t *);
static void check_task_has_delay(struct task_t *);
static void check_task_has_xmrcall(struct task_t *);
static void check_task_has_disable(struct task_t *);

/* extern prototypes (maybe defined in this module) */
extern void __free_icptab(void);
extern void __chk_funcdef(struct task_t *);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern char *__pv_stralloc(char *);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_ptnam(char *, word32);
extern char *__to_sytyp(char *, word32);
extern char *__to_sttyp(char *, word32);
extern char *__to_qctyp(char *, word32);
extern char *__to_idnam(struct expr_t *);
extern char *__to_mpnam(char *, char *);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern char *__msgnumexpr_tostr(char *, struct expr_t *, int32);
extern struct expr_t *__copy_expr(struct expr_t *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern char *__pregab_tostr(char *, word32 *, word32 *, struct net_t *);
extern char *__bld_lineloc(char *, word32, int32);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct expr_t *__alloc_newxnd(void);
extern struct expr_t *__bld_rng_numxpr(word32, word32, int32);
extern struct paramlst_t *__copy_dellst(struct paramlst_t *);
extern void __my_free(void *, size_t);
extern void __mark_widdet_params(struct mod_t *);
extern void __sgn_xtnd_widen(struct xstk_t *, int32);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern int32 __wide_vval_is0(word32 *, int32);
extern void __in_xpr_markparam(struct expr_t *);
extern int32 __chk_delparams(struct paramlst_t *, char *, int32);
extern void __free_dellst(struct paramlst_t *);
extern void __bld_mlevel_lists(void);
extern int32 __get_netwide(struct net_t *);
extern int32 __chk_rhsexpr(struct expr_t *, int32);
extern int32 __chk_numdelay(struct expr_t *, char *);
extern void __free_xtree(struct expr_t *);
extern void __free2_xtree(struct expr_t *);
extern void __init_xnd(struct expr_t *);
extern int32 __get_arrwide(struct net_t *);
extern void __getarr_range(struct net_t *, int32 *, int32 *, int32 *);
extern void __getarr_range_mda(struct net_t *, int32 *, int32 *mr2, int32 *, 
 int32);
extern int32 __mda_multiplier(struct net_t *, int32);
extern int32 __compute_mda_index(struct mda_t *, struct net_t *, 
 struct expr_t *, int32, struct expr_t **);
extern int32 __nd_ndxnum(struct expr_t *, char *, int32);
extern int32 __chk_lhsexpr(struct expr_t *, int32);
extern void __set_expr_onrhs(struct expr_t *);  
extern void __chk_lstofsts(struct st_t *);
extern struct expr_t *__widen_unsiz_rhs_assign(struct expr_t *, int);
extern struct expr_t *__widen_sv_unbas_unsiz_rhs(struct expr_t *, int32);
extern struct expr_t *__get_lvalue_idndp(struct expr_t *);
extern void __chk_nodel_lstofsts(struct st_t *);
extern int32 __isleaf(struct expr_t *);
extern void __getwir_range(struct net_t *, int32 *, int32 *);
extern int32 __unnormalize_ndx(struct net_t *, int32);
extern int32 __unnormalize2_ndx(int32, int32, int32);
extern int32 __chk_lhsdecl_scalared(struct expr_t *);
extern void __push_nbstk(struct st_t *);
extern void __pop_nbstk(void);
extern int32 __is_upward_dsable_syp(struct sy_t *, struct symtab_t *, int32 *);
extern void __chk_tskenable(struct st_t *);
extern void __set_lhswidth(struct expr_t *);
extern void __set_rhswidth(struct expr_t *, int32);
extern int32 __get_rhswidth(struct expr_t *);
extern void __chk_evxpr(struct expr_t *);
extern int32 __xhas_reg(struct expr_t *);
extern int32 __get_gia_wide(struct gia_aux_t *);
extern void __rhspsel(word32 *, word32 *, int32, int32);
extern int32 __chkndx_expr(struct expr_t *, char *);
extern int32 __expr_has_glb(struct expr_t *);
extern void __bld_unc_expr(void);
extern struct exprlst_t *__alloc_xprlst(void);
extern void __chk_1mdecls(void);
extern void __chk_taskvars(struct task_t *, int32);
extern void __set_drvr_bits(void);
extern void __chk_chg_port_dir(int32);
extern int32 __cvt_lngbool(word32 *, word32 *, int32);
extern struct st_t *__alloc_stmt(int32);

extern int32 __alloc_is_cval(int32);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern int32 __alloc_shareable_cval(word32, word32, int32);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern int32 __is_const_expr(struct expr_t *);
extern int32 __cmp_xpr(struct expr_t *, struct expr_t *, int32 *);
extern int32 __chk_paramexpr(struct expr_t *, int32);
extern void __set_numval(struct expr_t *, word32, word32, int32);
extern int32 __gia_sym_cmp(const void *, const void *);
extern void __copy_wire_from_wire_array(struct net_t *, struct net_t *);
extern void __chk_repl_wire_arr_selects(struct expr_t *, int32);
extern void __chk_task_thread_needed(struct mod_t *);
extern void __chk_1tsk_dpi(struct task_t *);
extern void __chk_funcdef_dpi(struct task_t *);
extern void __chk_funcdef_dpi(struct task_t *);
extern void __chk_fdef_args(struct task_t *);

extern void __cv_msg(char *, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __sgfwarn(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __dbg_msg(char *, ...);
extern void __sgfinform(int32, char *, ...);
extern void __sgfterr(int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __misc_sgfterr(char *, int32);
extern void __misc_gfterr(char *, int32, word32, int32);

extern const word32 __masktab[];

/*
 * ROUTINES TO FIND PORT CONNECTED AS INOUTS AND CHG DIR OR EMIT WARN
 */

/*
 * routine to set driver bits for nets
 * if driven by internal instance output port up drvr, set iconn driver bit
 * if driven by module input port down drvr, set mdprt driver bit 
 * for all other drivers set inmod driver bit
 *
 * SJM 05/23/01 - now using per bit algorithm because otherwise can't
 * detect shorted ports or 2nd iconn that is wrong direction driver
 *
 * AIV 08/07/09 - may have to convert wire array check each expr here
 */
extern void __set_drvr_bits(void)
{
 int32 pi, ii, gi, ptyp, pnum;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct mod_t *mdp, *imdp;
 struct gate_t *gp;
 struct conta_t *cap;
 struct expr_t *xp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* DBG remove -- */
   if (__debug_flg)
    {
     extern void __dmp_mod(FILE *, struct mod_t *, int32);
     extern void __chk_dsgn_ipins(struct mod_t *);

     __dbg_msg(" =======  DUMPING MOD SRC AFTER GEN AND AFTER SPLITTING %s\n",
      mdp->msym->synam);
     __dmp_mod(stdout, mdp, FALSE);
     __dbg_msg(" =======  END OF SRC DMP\n");
     __chk_dsgn_ipins(__modhdr);
    }
   /* --- */

   __push_wrkitstk(mdp, 0);
   /* first process all instances in module to set the high conn iconns */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((pnum = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < pnum; pi++)
      {
       mpp = &(imdp->mpins[pi]);
       xp = ip->ipins[pi];
       /* AIV 08/07/09 - may have to convert wire array here */
       __chk_repl_wire_arr_selects(xp, TRUE);
       ptyp = mpp->mptyp;

       /* for inout always marks high conn tran drvr */
       if (ptyp == IO_BID) set_lhs_expr_drvrtyp(xp, DRVR_NON_PORT,
        ip->isym->syfnam_ind, ip->isym->sylin_cnt);
       else if (ptyp == IO_OUT) set_lhs_expr_drvrtyp(xp, DRVR_ICONN,
        ip->isym->syfnam_ind, ip->isym->sylin_cnt);
      }
    }

   /* next gates including udps */
   for (gi = 0; gi < mdp->mgnum; gi++)
    {
     /* if this is array of gates, will cause direction chg to inout */
     /* SJM 05/23/01 - FIXME - should unwind these and not change */
     gp = &(mdp->mgates[gi]);
     switch ((byte) gp->g_class) {
      case GC_PULL:
       /* one gate all drivers can have multiple pins */
       for (pi = 0; pi < (int32) gp->gpnum; pi++)
        {
         xp = gp->gpins[pi];
         __chk_repl_wire_arr_selects(xp, TRUE);
         /* pull will force change to inoutk so tran type */
         set_lhs_expr_drvrtyp(xp, DRVR_NON_PORT, gp->gsym->syfnam_ind,
          gp->gsym->sylin_cnt);
        }
       break;
      case GC_TRAN: 
       __chk_repl_wire_arr_selects(gp->gpins[0], TRUE);
       __chk_repl_wire_arr_selects(gp->gpins[1], TRUE);
       /* both terminals of tran, need drvr field set */
       set_lhs_expr_drvrtyp(gp->gpins[0], DRVR_NON_PORT, gp->gsym->syfnam_ind,
        gp->gsym->sylin_cnt);
       set_lhs_expr_drvrtyp(gp->gpins[1], DRVR_NON_PORT, gp->gsym->syfnam_ind,
        gp->gsym->sylin_cnt);
       break;
      case GC_TRANIF:
       /* first two  terminals of tranif, need drvr field set */
       __chk_repl_wire_arr_selects(gp->gpins[0], TRUE);
       __chk_repl_wire_arr_selects(gp->gpins[1], TRUE);
       set_lhs_expr_drvrtyp(gp->gpins[0], DRVR_NON_PORT, gp->gsym->syfnam_ind,
        gp->gsym->sylin_cnt);
       set_lhs_expr_drvrtyp(gp->gpins[1], DRVR_NON_PORT, gp->gsym->syfnam_ind,
        gp->gsym->sylin_cnt);
       break;
      default:
       /* for gate/udp, unless output unc. set drv type field in conn net */
       /* if output unc. (OPEMPTY), chges are not seen (do not propagate) */
       if (gp->gpins[0]->optyp == OPEMPTY) continue;
       __chk_repl_wire_arr_selects(gp->gpins[0], TRUE);
       set_lhs_expr_drvrtyp(gp->gpins[0], DRVR_NON_PORT, gp->gsym->syfnam_ind,
        gp->gsym->sylin_cnt);
     }
    }
   for (cap = mdp->mcas; cap != NULL; cap = cap->pbcau.canxt)
    {
     __chk_repl_wire_arr_selects(cap->lhsx, TRUE);
     set_lhs_expr_drvrtyp(cap->lhsx, DRVR_NON_PORT, cap->casym->syfnam_ind,
      cap->casym->sylin_cnt);
    }

   /* LOOKATME - for top level module ports, still setting */
   /* module ports (low conns) */
   pnum = mdp->mpnum;
   for (pi = 0; pi < pnum; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     xp = mpp->mpref;
     __chk_repl_wire_arr_selects(xp, TRUE);
     ptyp = mpp->mptyp;
     /* for inout always marks low conn tran drvr */
     if (ptyp == IO_BID) set_lhs_expr_drvrtyp(xp, DRVR_NON_PORT,
      mpp->mpfnam_ind, mpp->mplin_cnt);
     else if (ptyp == IO_IN) set_lhs_expr_drvrtyp(xp, DRVR_MDPRT,
      mpp->mpfnam_ind, mpp->mplin_cnt);
    }
   __pop_wrkitstk();
  }
 /* FIXME - not using tf_ drivers to change module port direction */
 /* think this is right since not really structural drivers" */ 
}

/*
 * set lhs lvalue expr driver bits (i.e. know will be lvalue expr)
 */
static void set_lhs_expr_drvrtyp(struct expr_t *xp, int32 drvr_typ, int32 fnind,
 int32 flcnt)
{
 int32 ri1, ri2;
 struct net_t *np;
 struct expr_t *idndp, *catxp;

 ri1 = ri2 = -1;
 switch (xp->optyp) {
  case ID: case GLBREF:
   if (xp->lu.sy->sytyp != SYM_N)
    {
     /* SJM 11/12/01 - must catch syntax error of using non net as port */
     /* iconn connection */
     /* actual error will be found during pass 2 - needed for port coerce */
     __gferr(3415, fnind, flcnt,
      "illegal declarative lvalue %s - see detailed pass 2 error",
      __msgexpr_tostr(__xs, xp)); 
     __pv_err_cnt--;
     return;
    }
   np = xp->lu.sy->el.enp;
   break;
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM: case OPEMPTY:
   return;
  case LSB:
   idndp = xp->lu.x;
   np = idndp->lu.sy->el.enp;
   /* SJM 09/24/01 - if syntax err where selecting from non vector emit */
   /* error and do not set drive type */ 
   if (np->nsym->sytyp != SYM_N || !np->n_isavec)
    {
     __gferr(3412, fnind, flcnt,
      "attempt to bit select from non vector %s", np->nsym->synam);
     return;
    }
   ri1 = ri2 = comp_pre_elab_norm_con_ndx(np, xp->ru.x, fnind, flcnt);
   /* SJM 07/07/03 - for illegal negative index, can't set bit drvr types */
   if (ri1 == -2) return;
   break;
  case PARTSEL:
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   idndp = xp->lu.x;
   np = idndp->lu.sy->el.enp;
   if (np->nsym->sytyp != SYM_N || !np->n_isavec)
    {
     __gferr(3412, fnind, flcnt,
      "attempt to part select from non vector %s", np->nsym->synam);
     return;
    }
   /* notice need to eval these const exprs since not folded yet */
   ri1 = comp_pre_elab_norm_con_ndx(np, xp->ru.x->lu.x, fnind, flcnt);
   ri2 = comp_pre_elab_norm_con_ndx(np, xp->ru.x->ru.x, fnind, flcnt);
   /* SJM 07/07/03 - for illegal negative index, can't set bit drvr types */
   if (ri1 == -2 || ri2 == -2) return;
   break;
  case LCB:
   for (catxp = xp->ru.x; catxp != NULL; catxp = catxp->ru.x)
    { set_lhs_expr_drvrtyp(catxp->lu.x, drvr_typ, fnind, flcnt); }
   return;
  default: 
   /* SJM 10/22/01 - need to flag problem but not count as error since */
   /* actual error will be found during pass 2 - needed for port coerce */
   __gferr(3415, fnind, flcnt, "illegal declarative lvalue %s - see detailed pass 2 error",
    __msgexpr_tostr(__xs, xp)); 
   __pv_err_cnt--;
   return;
 }
 if (np->n_isavec) set_vec_drvr_type(np, ri1, ri2, drvr_typ);
 else set_scalar_drvr_type(np, drvr_typ);
}

/*
 * compute a known constant expr numeric index before elaboration and folding
 * notice since constants not yet folded, must normalize constants too
 */
static int32 comp_pre_elab_norm_con_ndx(struct net_t *np, struct expr_t *xp,
 int32 fnind, int32 flcnt)
{
 int32 nni1, nni2, biti, biti2, prtxpr_rng_bad;
 struct xstk_t *xsp;

 if (!is_nonis_const_expr(xp)) return(-1);
   
 /* AIV 02/24/09 - now need to handle wire array ranges here */
 if (np->n_isarr && np->ntyp < NONWIRE_ST)
  {
   return(comp_pre_elab_wire_ndx(np, xp, fnind, flcnt));
  }

 xsp = __eval_xpr(xp);
 /* if wide or x/z, be pessimistic and assume all of range (i.e. out of rng) */
 if (xsp->xslen > WBITS || xsp->bp[0] != 0)
  { __pop_xstk(); return(-1); }
 biti2 = (int32) xsp->ap[0];
 __pop_xstk();

 /* SJM 04/07/23 - nx1 may not be set for nets decl from implicit connect */
 if (np->nu.ct->nx1 == NULL || np->nu.ct->nx2 == NULL)
  {
   biti = -1;
  }
 else
  {
   nni1 = (int32) __contab[np->nu.ct->nx1->ru.xvi];
   nni2 = (int32) __contab[np->nu.ct->nx2->ru.xvi];
   /* SJM 07/31/03 - because port drivers are needed before ranges set */
   /* must make sure that mod port expr constant selects are in range */
   /* notice - not yet normalized to h:0 */
   prtxpr_rng_bad = FALSE;
   if (nni1 >= nni2)
    { if (biti2 > nni1 || biti2 < nni2) prtxpr_rng_bad  = TRUE; }
   else { if (biti2 < nni1 || biti2 > nni2) prtxpr_rng_bad = TRUE; }
   /* AIV 05/25/11 - added net name so error message is more informative */
   if (prtxpr_rng_bad) 
    {
     __gferr(3415, fnind, flcnt,
      "module port expression select range index %d outside net %s range [%d:%d] - can't fix",
      biti2, np->nsym->synam, nni1, nni2); 
     return(-2); 
    }

   if (nni1 < 0 || nni2 < 0 || biti2 < 0)
    {
     __gferr(3415, fnind, flcnt, "illegal negative port declaration range on net%s ", np->nsym->synam);
     return(-2); 
    } 
   biti = normalize_ndx_(biti2, nni1, nni2);
  }
 return(biti);
}

/*
 * compute array index for wire array
 * almost the same as comp_pre_elab_norm_con_ndx - except known to be array 
 * so need to check array range
 */
static int32 comp_pre_elab_wire_ndx(struct net_t *np, struct expr_t *xp,
 int32 fnind, int32 flcnt)
{
 int32 nni1, nni2, biti, biti2, prtxpr_rng_bad, arrwid, err;
 struct expr_t *sel_ndx, *ndx;
 struct xstk_t *xsp;
 struct mda_t *mdap;

 mdap = np->mda;
 /* mda - check for range and constant indices */
 if (mdap != NULL)
  {
   /* this is check array range */
   err = chk_wire_dma_rng(np);
   if (err) return(-1);
   xsp = __eval_xpr(xp);
   if (xsp->xslen > WBITS || xsp->bp[0] != 0) { __pop_xstk(); return(-1); }

   biti2 = (int32) xsp->ap[0];
   __pop_xstk();
  
   ndx = xp->next_ndx;
   /* DBG remove -- */
   if (ndx == NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */

   /* all indices must be constant */
   while (ndx != NULL) 
    {
     if (!is_nonis_const_expr(ndx)) return(-1);
     ndx = ndx->next_ndx;
    }
   biti = __compute_mda_index(mdap, np, xp, biti2, &sel_ndx);
   //AIV LOOKATME - selects off mda - are these allowed?????
   if (sel_ndx != NULL)
    {
     __gferr(3441, fnind, flcnt,
      "module port expression not allowing selects of wire arrays (%s)",
      np->nsym->synam); 
    }
   return(biti);
  //AIV LOOKATME - this should be folded later????
  // xp->folded_ndx = TRUE;
  }

 xsp = __eval_xpr(xp);
 /* if wide or x/z, be pessimistic and assume all of range (i.e. out of rng) */
 if (xsp->xslen > WBITS || xsp->bp[0] != 0)
  { __pop_xstk(); return(-1); }
 biti2 = (int32) xsp->ap[0];
 __pop_xstk();

/*
 if (xp->next_ndx != NULL) xp = xp->next_ndx;
  {
   __gferr(3441, fnind, flcnt,
    "module port expression not allowing selects of wire arrays (%s)",
    np->nsym->synam); 
   biti = -1;
  }
*/
 /* SJM 04/07/23 - nx1 may not be set for nets decl from implicit connect */
 if (np->nu.ct->nx1 == NULL || np->nu.ct->nx2 == NULL)
  {
   biti = -1;
  }
 else
  {
   __getarr_range(np, &nni1, &nni2, &arrwid);
   /* SJM 07/31/03 - because port drivers are needed before ranges set */
   /* must make sure that mod port expr constant selects are in range */
   /* notice - not yet normalized to h:0 */
   prtxpr_rng_bad = FALSE;
   if (nni1 >= nni2)
    { if (biti2 > nni1 || biti2 < nni2) prtxpr_rng_bad  = TRUE; }
   else { if (biti2 < nni1 || biti2 > nni2) prtxpr_rng_bad = TRUE; }
   if (prtxpr_rng_bad) 
    {
     __gferr(3415, fnind, flcnt,
      "module port expression select range index %d outside net range [%d:%d] - can't fix",
      biti2, nni1, nni2); 
     return(-2); 
    }

   if (nni1 < 0 || nni2 < 0 || biti2 < 0)
    {
     __gferr(3415, fnind, flcnt, "illegal negative port declaration range");
     return(-2); 
    } 
   biti = normalize_ndx_(biti2, nni1, nni2);
  }
 return(biti);
}

/*
 * check to see if an expressions is pre elaboration non IS constant
 * no folding before here and selects legal providing no variables appear
 *
 * SJM 01-18-09 - if have array select, know can't be non is const expr
 */
static int32 is_nonis_const_expr(struct expr_t *ndp)
{
 struct net_t *np;

 np = NULL;
 if (__isleaf(ndp))
  {
   if (ndp->optyp == ID)
    {
     if (ndp->lu.sy->sytyp != SYM_N) return(FALSE);
     np = ndp->lu.sy->el.enp;
     if (!np->n_isaparam) return(FALSE);
    }
   if (ndp->optyp == GLBREF) return(FALSE);
   /* here IS number is non constant */
   if (ndp->optyp == ISNUMBER) return(FALSE); 

   /* SJM 05/19/04 - because of driver bit setting needed to do later */
   /* expr checking - only for parameters expr size not yet set */
   /* therefore set it to parameter width here as kludge - value will be */
   /* right but will be set again later */
   if (ndp->optyp == ID && ndp->szu.xclen == 0)
    {
     ndp->szu.xclen = np->nwid;
    }

   return(TRUE);
  }

 /* AIV 03/10/11 - this doesn't necessarily have the width set yet here */
 /* rare issue for shift << which checks the expr width this is needed */
 /* width will be set later (see above comment) - just set width to WBITS */
 if (ndp->szu.xclen == 0) 
   ndp->szu.xclen = WBITS;

 if (ndp->lu.x != NULL)
  { if (!is_nonis_const_expr(ndp->lu.x)) return(FALSE); }
 if (ndp->ru.x != NULL)
  { if (!is_nonis_const_expr(ndp->ru.x)) return(FALSE); }
 return(TRUE);
}

/*
 * set scalar driver type - know never passed drvr none
 */
static void set_scalar_drvr_type(struct net_t *np, int32 drvr_typ)
{
 /* if current state drvr none, set to passed new state */
 if (np->n_drvtyp == DRVR_NONE) { np->n_drvtyp = drvr_typ; return; }

 /* otherwide set to real driver - any 2nd driver becomes non port where */
 /* always need to change to inout if possible */
 np->n_drvtyp = DRVR_NON_PORT;
}

/*
 * set driver type - know never passed drvr none
 * if ri1 -1, then entire range - know ranges normalized before here
 */
static void set_vec_drvr_type(struct net_t *np, int32 ri1, int32 ri2,
 int32 drvr_typ)
{
 int32 ri, bi;
 int32 nni1, nni2, wid;

 /* range convert to constants but not normalized by here */
 nni1 = (int32) __contab[np->nu.ct->nx1->ru.xvi];
 nni2 = (int32) __contab[np->nu.ct->nx2->ru.xvi];
 wid = ((nni1 >= nni2) ? (nni1 - nni2 + 1) : (nni2 - nni1 + 1));
 /* allocate per bit drv state if needed */
 if (np->nu.ct->n_pb_drvtyp == NULL)
  {
   np->nu.ct->n_pb_drvtyp = (byte *) __my_malloc(wid);
   for (bi = 0; bi < wid; bi++) np->nu.ct->n_pb_drvtyp[bi] = DRVR_NONE; 
  }

 /* AIV 04/09/09 - if is a wire array it is really just a vector of an */
 /* entire net - these are flatten to each element - so do entire range */
 /* was causing memory issue by accessing out or range ri1/ri2 */
 if (np->n_isarr && np->ntyp < NONWIRE_ST)
  {
   ri1 = -1;
  }
 
 if (ri1 == -1) { ri1 = wid - 1; ri2 = 0; }
 for (ri = ri1; ri >= ri2; ri--)
  {
   /* if current state drvr none, set to passed new state */
   if (np->nu.ct->n_pb_drvtyp[ri] == DRVR_NONE)
    { np->nu.ct->n_pb_drvtyp[ri] = drvr_typ; continue; }
   /* otherwide set to real driver - any 2nd driver becomes non port where */
   /* always need to change to inout if possible */
   np->nu.ct->n_pb_drvtyp[ri] = DRVR_NON_PORT;
  }
}

/*
 * check connection pattern for all input and output ports and change if 
 * nd_chg T and return num_chged if any changed (0 if none changed)
 *
 * if input has lowconn driver and highconn is wire lvalue chg to inout
 * if output has highconn driver and lowconn is wire lvalue chg to inout
 *
 * if option not used, emit warning else emit inform if option used
 */
extern void __chk_chg_port_dir(int32 nd_chg)
{
 int32 pi, ii, pnum, num_chged, sav_num_chged;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct mod_t *mdp, *imdp;
 struct expr_t *xp;
#ifndef __CVC_RT__
 char s1[RECLEN];
#endif

 for (num_chged = 0;;)
  {
   sav_num_chged = num_chged;
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     /* process for every instance in module */ 
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

         /* SJM 06/01/01 SJM - never change if either hiconn or loconn */
         /* concatenate - idea is that concat is expr so must be declared */
         /* with right direction or assume no backwards driving */
         if (mpp->mpref->optyp == LCB || xp->optyp == LCB) continue;

         /* SJM 11/15/00 - need to emit warnings for connections where */
         /* XL port collapsing may produce wrong result */
         /* case 1: instance input port where down lowconn has drivers */
         if (mpp->mptyp == IO_IN)
          {
           /* SJM 05/23/01 - changeable if both hiconn and loconn decl lval */
           /* and has wrong direction driver(s) */
           /* for port, even if subrange, if any bits in vec, change */
           if (expr_decl_lvalue(mpp->mpref) && expr_decl_lvalue(xp)
            && port_expr_has_wrong_dir_drvr(mpp->mpref, IO_IN, -1, -1,
             mpp->mpfnam_ind, mpp->mplin_cnt))
            {
             if (nd_chg)
              {
#ifndef __CVC_RT__
               __gfinform(3005, mpp->mpfnam_ind, mpp->mplin_cnt,
                "input port %s (pos. %d) of instance at %s has lowconn driver(s) - changed to inout from +change_port_type option - otherwise value of %s in %s could differ",
                __to_mpnam(__xs, mpp->mpsnam), pi + 1, 
                __bld_lineloc(__xs2, ip->isym->syfnam_ind, ip->isym->sylin_cnt),
                __msgexpr_tostr(s1, xp), mdp->msym->synam); 
#endif

               mpp->mptyp = IO_BID;
               chg_mpx_to_bid(mpp->mpref);
               set_lhs_expr_drvrtyp(mpp->mpref, DRVR_NON_PORT,
                mpp->mpfnam_ind, mpp->mplin_cnt);
               set_lhs_expr_drvrtyp(xp, DRVR_NON_PORT, ip->isym->syfnam_ind,
                ip->isym->sylin_cnt);
               num_chged++;
               continue;
              }
             if (mdp->m_has_garrs)
              {
#ifndef __CVC_RT__
               /* SJM 05/23/01 - if mod has arrays of gates just inform but */
               /* still would change if change port types on */
               __gfinform(3005, mpp->mpfnam_ind, mpp->mplin_cnt,
                "input port %s (pos. %d) of instance at %s has lowconn driver(s), value of %s in %s may differ from simulators using port collapsing - use +change_port_type for compatibility",
                __to_mpnam(__xs, mpp->mpsnam), pi + 1, 
                __bld_lineloc(__xs2, ip->isym->syfnam_ind, ip->isym->sylin_cnt),
                __msgexpr_tostr(s1, xp), mdp->msym->synam); 
#endif
               continue;
              }
#ifndef __CVC_RT__
 
             __gfwarn(3107, mpp->mpfnam_ind, mpp->mplin_cnt,
              "input port %s (pos. %d) of instance at %s has lowconn driver(s), value of %s in %s may differ from simulators using port collapsing - use +change_port_type for compatibility",
              __to_mpnam(__xs, mpp->mpsnam), pi + 1, 
              __bld_lineloc(__xs2, ip->isym->syfnam_ind, ip->isym->sylin_cnt),
              __msgexpr_tostr(s1, xp), mdp->msym->synam); 
#endif
            }
           continue;
          }
         if (mpp->mptyp == IO_OUT) 
          {
           /* SJM 05/23/01 - changeable if both hiconn and loconn decl lval */
           /* and has wrong direction driver(s) */
           /* for output if bsel or psel, need range but decomposed here */
           if (expr_decl_lvalue(mpp->mpref) && expr_decl_lvalue(xp)
            && port_expr_has_wrong_dir_drvr(xp, IO_OUT, -1, -1,
            mpp->mpfnam_ind, mpp->mplin_cnt))
            {
             if (nd_chg)
              {
#ifndef __CVC_RT__
               __gfinform(3004, mpp->mpfnam_ind, mpp->mplin_cnt,
                "output port %s (pos. %d) of instance at %s has highconn driver(s) - changed to inout from +change_port_type option - otherwise value of %s in %s could differ",
               __to_mpnam(__xs, mpp->mpsnam), pi + 1, 
               __bld_lineloc(__xs2, ip->isym->syfnam_ind, ip->isym->sylin_cnt),
               __msgexpr_tostr(s1, mpp->mpref), imdp->msym->synam); 
#endif

               mpp->mptyp = IO_BID;
               chg_mpx_to_bid(mpp->mpref);
               set_lhs_expr_drvrtyp(mpp->mpref, DRVR_NON_PORT,
                mpp->mpfnam_ind, mpp->mplin_cnt);
               set_lhs_expr_drvrtyp(xp, DRVR_NON_PORT, ip->isym->syfnam_ind,
                ip->isym->sylin_cnt);
               num_chged++;
               continue;
              }
             if (mdp->m_has_garrs)
              {
               /* SJM 05/23/01 - if mod has arrays of gates just inform but */
               /* still would change if change port types on */
#ifndef __CVC_RT__
               __gfinform(3005, mpp->mpfnam_ind, mpp->mplin_cnt,
              "output port %s (pos. %d) of instance at %s has highconn driver(s), value of %s in %s may differ from simulators using port collapsing - use +change_port_type for compatibility",
              __to_mpnam(__xs, mpp->mpsnam), pi + 1, 
              __bld_lineloc(__xs2, ip->isym->syfnam_ind, ip->isym->sylin_cnt),
              __msgexpr_tostr(s1, mpp->mpref), imdp->msym->synam); 
#endif
               continue;
              }
#ifndef __CVC_RT__
             __gfwarn(3108, mpp->mpfnam_ind, mpp->mplin_cnt,
              "output port %s (pos. %d) of instance at %s has highconn driver(s), value of %s in %s may differ from simulators using port collapsing - use +change_port_type for compatibility",
              __to_mpnam(__xs, mpp->mpsnam), pi + 1, 
              __bld_lineloc(__xs2, ip->isym->syfnam_ind, ip->isym->sylin_cnt),
              __msgexpr_tostr(s1, mpp->mpref), imdp->msym->synam); 
#endif
            }
          }
        }
      }
    }
   /* if none changed, done - else try to find more */
   if (sav_num_chged == num_chged) break;
  }
#ifndef __CVC_RT__
 if (nd_chg && __verbose)
  {
   __cv_msg(
    "  %d input and/or output ports that are connected as inout changed to inout.\n", 
    num_chged);
  }
#endif
 free_design_ndrvrs();
}

/*
 * return T if expression has (can have) wrong direction drivers
 * for input port, expect down mod port expr to have only MD PRT driver
 * for output port, expect up iconn expr to have only up iconn driver
 *
 * this is run before tran channels built
 * never called for ports already inouts or that can't be changed to inout 
 */
static int32 port_expr_has_wrong_dir_drvr(struct expr_t *xp, int32 pdir, int32 ri1,
 int32 ri2, int32 fnind, int32 flcnt)
{
 int32 elem_lval, has_drvrs, max_drv_state;
 struct expr_t *catndp;
 struct net_t *np;

 /* SJM 07/07/03 - if neg range error - can't check dir - error later */
 /* SJM 07/16/03 - for non vector expect ri2 to be -1 - can't check for */  
 /* negative range */
 if (ri1 < -1 || ri2 < -1) return(FALSE);

 if (__isleaf(xp))
  {
   if (xp->optyp == ID || xp->optyp == GLBREF)
    {
     np = xp->lu.sy->el.enp;
     /* if not wire, does not have wrong dir driver */
     if (np->ntyp >= NONWIRE_ST) return(FALSE);

     if (np->n_isavec) max_drv_state = find_max_rng_drvr_state(np, ri1, ri2);
     else max_drv_state = np->n_drvtyp;

     /* if no drivers, can't be wrong direction */
     if (max_drv_state == DRVR_NONE) return(FALSE);

     /* if has non port (inout non port here), always has wrog dir */
     if (max_drv_state == DRVR_NON_PORT) return(TRUE);
    
     if (pdir == IO_IN)
      {
       /* if input port, wrong direction is non port or 1 up iconn driver */
       if (max_drv_state != DRVR_MDPRT) return(TRUE);
      }
     else if (pdir == IO_OUT)
      {
       /* if output port, wrong direction is non port or 1 down mdprt drvr */
       if (max_drv_state != DRVR_ICONN) return(TRUE);
      }
     else __case_terr(__FILE__, __LINE__);
     return(FALSE);
    }
   /* if leaf, non id or global, can't have drivers */
   return(FALSE);
  }
 /* arithmetic/logic operators exprs or fcalls can't have drivers */
 switch (xp->optyp) {
  /* for selects, ignore select expr. */
  case LSB:
   /* if not lvalue, never need to change */
   if (!__is_const_expr(xp->ru.x)) return(FALSE);
   /* if port is input, any driver (even outside bsel) still need dir chg */  
   if (pdir == IO_IN) ri1 = -1;
   else
    {
     np = xp->lu.x->lu.sy->el.enp;
     ri1 = comp_pre_elab_norm_con_ndx(np, xp->ru.x, fnind, flcnt);
     /* SJM 07/07/03 - if illegal neg rng - treat as right dir */
     if (ri1 == -2) return(FALSE);
    }
   if (port_expr_has_wrong_dir_drvr(xp->lu.x, pdir, ri1, ri1, fnind,
    flcnt)) return(TRUE);
   return(FALSE);
  case PARTSEL:
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   /* if port is input, any driver (even outside sel) still need dir chg */  
   if (pdir == IO_IN) ri1 = ri2 = -1;
   else
    {
     np = xp->lu.x->lu.sy->el.enp;
     ri1 = comp_pre_elab_norm_con_ndx(np, xp->ru.x->lu.x, fnind, flcnt);
     ri2 = comp_pre_elab_norm_con_ndx(np, xp->ru.x->ru.x, fnind, flcnt);
     /* SJM 07/07/03 - if illegal neg rng - treat as right dir */
     if (ri1 == -2 || ri2 == -2) return(FALSE);
    }
   if (port_expr_has_wrong_dir_drvr(xp->lu.x, pdir, ri1, ri2, fnind, flcnt))
    return(TRUE);
   return(FALSE);
  case LCB:
   /* if any component has drivers and all are decl lvals, then T */
   has_drvrs = FALSE;
   elem_lval = TRUE;
   for (catndp = xp->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     /* if any expr has drivers and no regs, then concat can have drvrs */
     if (port_expr_has_wrong_dir_drvr(catndp->lu.x, pdir, -1, -1, fnind,
      flcnt)) has_drvrs = TRUE;
     /* if not decl lvalue, concat can't be decl lvalue either */
     if (!expr_decl_lvalue(catndp->lu.x)) elem_lval = FALSE;
    }
   if (has_drvrs && elem_lval) return(TRUE);
   break;
  default: break;
 }
 /* if not an lvalue, can't be changed to inout */
 return(FALSE);
}

/*
 * compute maximum driver state of expr 
 * for module will always be entire expr, for up iconn may be for subrange
 *
 * if entire range -1, else normalized range
 * only called for vectors
 */
static int32 find_max_rng_drvr_state(struct net_t *np, int32 ri1, int32 ri2)
{
 int32 bi;
 int32 max_drvr_state, nni1, nni2, wid;

 nni1 = (int32) __contab[np->nu.ct->nx1->ru.xvi];
 nni2 = (int32) __contab[np->nu.ct->nx2->ru.xvi];
 wid = ((nni1 >= nni2) ? (nni1 - nni2 + 1) : (nni2 - nni1 + 1));
 max_drvr_state = DRVR_NONE;

 /* AIV 04/09/09 - if is a wire array it is really just a vector of an */
 /* entire net - these are flatten to each element - so do entire range */
 /* was causing memory issue by accessing out or range ri1/ri2 */
 if (np->n_isarr && np->ntyp < NONWIRE_ST)
  {
   ri1 = -1;
  }

 if (ri1 == -1) { ri1 = wid - 1; ri2 = 0; }
 for (bi = ri1; bi >= ri2; bi--)
  {
   /* if current driver state, max. hard non port (maybe inout), found max */
   if (np->nu.ct->n_pb_drvtyp[bi] == DRVR_NON_PORT) 
    { max_drvr_state = DRVR_NON_PORT; break; }

   /* if this one is driver none, nothing to do */
   if (max_drvr_state == DRVR_NONE) continue;

   /* if max same as this one, nothing to do */
   if (np->nu.ct->n_pb_drvtyp[bi] == max_drvr_state) continue;
     
   /* if this one, non inout port, know will be different so set to max */  
   max_drvr_state = DRVR_NON_PORT;
   break;
  }
 return(max_drvr_state);
}

/*
 * check to see if an expressions is constant 
 *
 * no folding and selects legal providing no variables appear
 */
extern int32 __is_const_expr(struct expr_t *ndp)
{
 struct net_t *np;

 if (__isleaf(ndp))
  {
   if (ndp->optyp == ID)
    {
     if (ndp->lu.sy->sytyp != SYM_N) return(FALSE);
     np = ndp->lu.sy->el.enp;
     if (!np->n_isaparam) return(FALSE);
    }
   if (ndp->optyp == GLBREF) return(FALSE);
   return(TRUE);
  }
 if (ndp->lu.x != NULL) { if (!__is_const_expr(ndp->lu.x)) return(FALSE); }
 if (ndp->ru.x != NULL) { if (!__is_const_expr(ndp->ru.x)) return(FALSE); }
 return(TRUE);
}

/*
 * return T if expr is decl lvalue
 * only if decl lvalue high conn and low conn can be changed to inout port
 */
static int32 expr_decl_lvalue(struct expr_t *xp)
{
 struct expr_t *catndp;
 struct net_t *np;

 switch (xp->optyp) {
  case ID: case GLBREF:
   np = xp->lu.sy->el.enp;
   /* reg is not decl lvalue */
   if (np->ntyp < NONWIRE_ST) return(TRUE);
   break;
  case LSB:
   /* declarative lvalue only if constant expr */
   /* SJM 05/23/01 - at this point const exprs not folded */
   if (!__is_const_expr(xp->ru.x)) return(FALSE);
   np = xp->lu.x->lu.sy->el.enp;
   /* only wire is decl lvalue */
   if (np->ntyp < NONWIRE_ST) return(TRUE);
   break;
  case PARTSEL:
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   np = xp->lu.x->lu.sy->el.enp;
   /* only wire is decl lvalue */
   if (np->ntyp < NONWIRE_ST) return(TRUE);
   break;
  case LCB:
   /* if any element of concat not decl lvalue, concat can't be changed */
   for (catndp = xp->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     if (!expr_decl_lvalue(catndp->lu.x)) return(FALSE);
    }
   return(TRUE);
  default: break;
 }
 /* if not an lvalue, can't be changed to inout */
 return(FALSE);
}

/*
 * routine to change IO type of all port expr contaned nets 
 * know will be lvalue or will not be called
 */
static void chg_mpx_to_bid(struct expr_t *mpx)
{
 struct expr_t *catndp; 
 struct net_t *np;

 switch (mpx->optyp) {
   case ID: case GLBREF:
    np = mpx->lu.sy->el.enp;
    np->iotyp = IO_BID;
    break;
   case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
    chg_mpx_to_bid(mpx->lu.x);
    break;
   case LCB:
    for (catndp = mpx->ru.x; catndp != NULL; catndp = catndp->ru.x)
     { chg_mpx_to_bid(catndp->lu.x); }
    break; 
   default: __case_terr(__FILE__, __LINE__);
  }
}

/*
 * free all vector rng reps in design - never attached for task vars
 */
static void free_design_ndrvrs(void)
{
 int32 ni, nni1, nni2, wid;
 struct mod_t *mdp;
 struct net_t *np;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* only free for wires, regs and task vars never pb drv fields */ 
   for (np = &(mdp->mnets[0]), ni = 0; ni < mdp->mnnum; ni++, np++)
    {
     if (!np->n_isavec) continue;

     if (np->nu.ct->n_pb_drvtyp != NULL)
      {
       nni1 = (int32) __contab[np->nu.ct->nx1->ru.xvi];
       nni2 = (int32) __contab[np->nu.ct->nx2->ru.xvi];
       wid = ((nni1 >= nni2) ? (nni1 - nni2 + 1) : (nni2 - nni1 + 1));
       __my_free(np->nu.ct->n_pb_drvtyp, wid);
       np->nu.ct->n_pb_drvtyp = NULL;
      }
    }
  }
}

/*
 * ROUTINES TO SET TIME SCALE VALUES 
 */

/*
 * process module and design timescales
 * this is needed before any conversion of delay constant expressions
 * to ticks 
 * notice storing inverse so higher value is smaller time
 */
extern void __process_timescales(void)
{
 struct mod_t *mdp;
 
 /* notice implied - so 0 is max 1 sec. (10**-0 secs.) */
 /* larger units is shorter tick */
 __des_timeprec = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mtime_units + mdp->mtime_prec > __des_timeprec)
    __des_timeprec = mdp->mtime_units + mdp->mtime_prec;
  } 
 /* unless set %t time format defaults to ticks */
 __tfmt_units = __des_timeprec;

 /* next mark all modules with des time units - no scaling needed */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mtime_units == __des_timeprec) mdp->mno_unitcnv = TRUE;
  }
 bld_timstr_vals();
}

/*
 * routine to build "absolute time" multiplier and suffix for to_timstr
 * message times
 */
static void bld_timstr_vals(void)
{
 struct mod_t *mdp;

 strcpy(__timstr_unitsuf, "");
 __timstr_mult = 1ULL;
 __nd_timstr_suf = FALSE;
 /* if module has scaled time timstr values need suffix and multiplier */ 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* if not no unit conversion need absolute times */
   if (!mdp->mno_unitcnv) { __nd_timstr_suf = TRUE; break; } 
  }
 /* if all modules have same time unit (no matter what), timstr no units */
 if (!__nd_timstr_suf) return;
 
 /* if any differ, need absolute units but still not scaled to module */
 /* i.e. value will be absolute time of tick */
 switch (__des_timeprec) {
  case 0:
   __timstr_mult = 1ULL;
   strcpy(__timstr_unitsuf, " s");
   break;
  case 1:
   __timstr_mult = 100ULL;
   strcpy(__timstr_unitsuf, " ms");
   break;
  case 2:
   __timstr_mult = 10ULL;
   strcpy(__timstr_unitsuf, " ms");
   break;
  case 3:
   __timstr_mult = 1ULL;
   strcpy(__timstr_unitsuf, " ms");
   break;
  case 4:
   __timstr_mult = 100ULL;
   strcpy(__timstr_unitsuf, " us");
   break;
  case 5:
   __timstr_mult = 10ULL;
   strcpy(__timstr_unitsuf, " us");
   break;
  case 6:
   __timstr_mult = 1ULL;
   strcpy(__timstr_unitsuf, " us");
   break;
  case 7:
   __timstr_mult = 100ULL;
   strcpy(__timstr_unitsuf, " ns");
   break;
  case 8:
   __timstr_mult = 10ULL;
   strcpy(__timstr_unitsuf, " ns");
   break;
  case 9:
   __timstr_mult = 1ULL;
   strcpy(__timstr_unitsuf, " ns");
   break;
  case 10:
   __timstr_mult = 100ULL;
   strcpy(__timstr_unitsuf, " ps");
   break;
  case 11:
   __timstr_mult = 10ULL;
   strcpy(__timstr_unitsuf, " ps");
   break;
  case 12:
   __timstr_mult = 1ULL;
   strcpy(__timstr_unitsuf, " ps");
   break;
  case 13:
   __timstr_mult = 100ULL;
   strcpy(__timstr_unitsuf, " fs");
   break;
  case 14:
   __timstr_mult = 10ULL;
   strcpy(__timstr_unitsuf, " fs");
   break;
  case 15:
   __timstr_mult = 1ULL;
   strcpy(__timstr_unitsuf, " fs");
   break;
 default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * ROUTINES TO MARK PARAMS THAT EFFECT EXPRESSION WIDTHS
 */

/*
 * mark all parameters that are in ranges or cats (or port def. psels)
 *
 * called first time when module is target of xmr defparam that needs to
 * be split
 *
 * this marks all param net_t's that can effect width so that splitting is
 * needed but unless actual xmr defparam marked, does not cause splitting
 */
extern void __mark_widdet_params(struct mod_t *pmdp)
{
 struct task_t *tskp;

 /* SJM - 02-22-09 all parameters are width determing if there is a generate */
 /* in the module - must always force splitting since gen does nothing if */
 /* params are not accessed */
 if (pmdp->mgenitems != NULL)
  {
   from_gen_mark_all_parm_widthdet(pmdp);
   /* since all marked nothing more to do */
   return;
  }
 
 /* check all wire and array declaration ranges - mark any param there */
 inrnges_mark_params(pmdp->msymtab);

 /* task list contains all symbols in task but if has named blocks */
 /* symbols declared there will be checked in its task on list */
 for (tskp = pmdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  inrnges_mark_params(tskp->tsksymtab);

 /* for all modules since checked before splitting port header range */
 /* params already marked */

 /* finally find all psel params in any expressions */
 /* insts, contas, task/functions, statements */
 /* also any bit select expression connecting to output or inout port */ 
 psel_set_allexprs(pmdp);
}

/*
 * from generate mark all parameters as width determing
 *
 * SJM 02-22-09 - this is slightly too pessimistic but rare extra splitting
 * spec or local params never width determining
 * if width determing can't be indir width determing - set elsewhere
 */
static void from_gen_mark_all_parm_widthdet(struct mod_t *mdp)
{
 int32 pi;
 struct net_t *np;

 if (mdp->mprmnum == 0) return;

 __inst_mod->mhas_widthdet = TRUE;
 for (pi = 0; pi < mdp->mprmnum; pi++)
  {
   np = &(mdp->mprms[pi]);
   /* DBG remove -- */
   if (!np->n_isaparam) __misc_terr(__FILE__, __LINE__);
   /* -- */
   if (np->nu.ct->p_genvar) continue;

   np->nu.ct->n_widthdet = TRUE;
  }
}

/*
 * mark all parameters in declaration ranges for one symbol table 
 *
 * by here know symbol table format frozen form 
 * must use symbol table because may not have nets list built when called
 */
static void inrnges_mark_params(struct symtab_t *sytp)
{
 int32 syi, i;
 struct sy_t **syms;
 struct sy_t *syp;
 struct net_t *np;
 struct mda_t *mdap;

 for (syi = 0, syms = sytp->stsyms; syi < (int32) sytp->numsyms; syi++)
  {
   syp = syms[syi];
   if (syp->sytyp != SYM_N) continue;
   np = syp->el.enp;

   /* set in cat or range bit for wire range params */
   if (np->n_isavec)
    {
     __in_xpr_markparam(np->nu.ct->nx1);
     __in_xpr_markparam(np->nu.ct->nx2);
    }
   /* set in cat or range bit for array range params */
   if (np->n_isarr)
    {
     /* AIV 01/18/11 - if multi dim need to check each dimension */
     if ((mdap = np->mda) != NULL)
      {
       for (i = 0; i < mdap->dimension; i++)
        {
         __in_xpr_markparam(mdap->tab_ax1[i]);
         __in_xpr_markparam(mdap->tab_ax2[i]);
        }
       continue;
      }
     __in_xpr_markparam(np->nu.ct->ax1);
     __in_xpr_markparam(np->nu.ct->ax2);
    }
  }
}

/*
 * set the width determining bit for any wire in expressions
 * caller determined is expression used in width determing place
 *
 * expression not yet checked but just marks IDs that are there
 * may mark wrong internal select params but selects here will cause
 * error later since must be constant expr.
 * any parameter including in "from param" select marked here
 */
extern void __in_xpr_markparam(struct expr_t *xp)
{
 struct net_t *np;
 struct expr_t *xp2;

 if (__isleaf(xp))
  {
   if (xp->optyp == ID && xp->lu.sy->sytyp == SYM_N)
    {
     np = xp->lu.sy->el.enp; 
     if (np->n_isaparam)
      {
       np->nu.ct->n_widthdet = TRUE;
       __inst_mod->mhas_widthdet = TRUE;
      }
    }
   return;
  }
 for (xp2 = xp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   __in_xpr_markparam(xp->lu.x);
  }
 if (xp->lu.x != NULL) __in_xpr_markparam(xp->lu.x);
 if (xp->ru.x != NULL) __in_xpr_markparam(xp->ru.x);
}

/*
 * mark params in all part selects and CATREP lhs repeat expressions
 * and tran out bit select ranges anywhere in module
 *
 * width determining marked for params used in array of gate or inst
 * ranges - only cause split if marked param a def or pound param and
 * really needs to cause containing module to be split
 */
static void psel_set_allexprs(struct mod_t *pmdp)
{
 int32 pi, j, pnum;
 struct inst_t *ip;
 struct gate_t *gp;
 struct task_t *tskp;
 struct conta_t *cap;
 struct ialst_t *ialp;
 struct expr_t *xp, *lhsx;
 struct mod_pin_t *mpp;
 struct mod_t *down_mdp;
 struct net_t *np;

 /* any part select in module except specify where no defparams possible */ 
 if ((pnum = pmdp->mpnum) != 0)
  {
   /* mark for module ports */
   for (pi = 0; pi < pnum; pi++)
    { mpp = &(pmdp->mpins[pi]); inpsel_xpr_markparam(mpp->mpref); }
  }
 for (j = 0; j < pmdp->minum; j++)
  {
   ip = &(pmdp->minsts[j]);

   down_mdp = ip->imsym->el.emdp;
   for (pi = 0; pi < (int32) down_mdp->mpnum; pi++)
    {
     xp = ip->ipins[pi];
     /* DBG remove --- */
     if (xp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* this will mark any part select even those that for arrays of insts */
     /* become bit selects */
     inpsel_xpr_markparam(xp);

     /* instance connection bit selects to inout or output ports must be */
     /* width det because effects tran channels */
     mpp = &(down_mdp->mpins[pi]);
     if (xp->optyp == LSB)
      {
       /* 05/19/01 SJM - for input and output that are param bsel from net */
       /* must mark as splittable if relevant param passed down */
       if (mpp->mptyp == IO_IN)
        {
         /* 06/01/01 SJM - if XMR, must always mark */
         if (xp->lu.x->optyp != ID) __in_xpr_markparam(xp->ru.x);
         else
          {
           np = xp->lu.x->lu.sy->el.enp;
           if (np->ntyp < NONWIRE_ST) __in_xpr_markparam(xp->ru.x);
          }
         continue;
        }
       if (mpp->mptyp == IO_BID || mpp->mptyp == IO_OUT)
        __in_xpr_markparam(xp->ru.x);
      }
    }
   /* SJM 04-21-10 - does not hurt to repeat for each - just sets again */
  }

 for (cap = pmdp->mcas; cap != NULL; cap = cap->pbcau.canxt)
  {
   lhsx = cap->lhsx;
   inpsel_xpr_markparam(lhsx);
   /* AIV 03/04/11 - was getting SEGV for XMR case - can have GLBREF here */
   /* just skip XMR case - notice in_xpr_markparm does't handle XMR either */
   /* XMR ly.sy resolution is not done yet */
   if (lhsx->optyp == LSB)
    {
     /* if conta output could drive path dest. cannot be IS form */
     if (lhsx->lu.x->optyp == ID)
      {
       np = lhsx->lu.x->lu.sy->el.enp;
       if (np->iotyp == IO_OUT || np->iotyp == IO_BID)
        { __in_xpr_markparam(cap->lhsx->ru.x); continue; }
      }
    }
   inpsel_xpr_markparam(cap->rhsx);
  }
 
 /* bit selects not width determining, except determines tran channel */
 /* for trans */
 /* now gates outputs that are IS form bit selects are ok just not acc. */
 for (j = 0; j < pmdp->mgnum; j++)
  {
   gp = &(pmdp->mgates[j]);
   if (gp->g_giap != NULL)
    {
     /* array of gates is only place part select allowed */
     /* any parameter used in part select is potentially width determing */
     /* reason is that for width 1 will be replicated and for other widths */
     /* will be apportioned so must split containing module */
     /* SJM 04-21-10 - could only do for first - leaving now for debugging */
     for (pi = 0; pi < (int32) gp->gpnum; pi++)
      {
       xp = gp->gpins[pi];
       inpsel_xpr_markparam(xp);
      }
//SJM - LOOKATME?? - maybe only should do for first
    }

   if (gp->g_class != GC_TRAN || gp->g_class == GC_TRANIF)
    {
     if (gp->gpins[0]->optyp == LSB)
      {
       /* 06/01/01 - if connection is xmr can never be port */
       if (gp->gpins[0]->lu.x->optyp != ID) goto nxt_gate;

       /* if gate output could drive path dest. cannot be IS form */
       np = gp->gpins[0]->lu.x->lu.sy->el.enp;

       if (np->iotyp == IO_OUT || np->iotyp == IO_BID)
        { __in_xpr_markparam(gp->gpins[0]->ru.x); goto nxt_gate; }
      }
     goto nxt_gate;
    }
   /* for trans any bit select in either inout port is width determining */
   xp = gp->gpins[0];
   if (xp->optyp == LSB) __in_xpr_markparam(xp->ru.x);
   /* mark the output bit select range - if present */ 
   xp = gp->gpins[1];
   if (xp->optyp == LSB) __in_xpr_markparam(xp->ru.x);

   /* routine always called after gate arrays expanded into per bit but */
   /* before connections apportioned to each expanded inst. - just do first */
nxt_gate:;
  }
 /* notice processing name blocks here not inline */
 for (tskp = pmdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  lstofsts_do_inpsel_set(tskp->tskst);
 /* initial/always can only be stmt here - maybe extra added at prep. */
 for (ialp = pmdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  lstofsts_do_inpsel_set(ialp->iastp);
 /* notice defparams cannot effect specify section */
}

/*
 * mark all psels in concatenates in any statement expr.
 */
static void stmt_do_inpsel_set(struct st_t *stp)
{
 struct csitem_t *dflt_csip;

 switch ((byte) stp->stmttyp) {
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA:
   inpsel_xpr_markparam(stp->st.spra.lhsx);
   inpsel_xpr_markparam(stp->st.spra.rhsx);
   break;
  case S_IF:
   inpsel_xpr_markparam(stp->st.sif.condx);
   lstofsts_do_inpsel_set(stp->st.sif.thenst);
   lstofsts_do_inpsel_set(stp->st.sif.elsest);
   break;
  case S_CASE:
   inpsel_xpr_markparam(stp->st.scs.csx);
   /* first is always default - st nil if no default */
   dflt_csip = stp->st.scs.csitems;
   csitemlst_do_inpsel_set(dflt_csip->csinxt);
   if (dflt_csip->csist != NULL) lstofsts_do_inpsel_set(dflt_csip->csist);
#ifdef __XPROP__
   /* AIV 08/02/11 - now might have xprop list to process as well */
   if (stp->st.scs.xprop_lstp != NULL)
    {
     lstofsts_do_inpsel_set(stp->st.scs.xprop_lstp);
    }
#endif
   break;
  case S_FOREVER:
  case S_WHILE:
  case S_DO_WHILE:
   inpsel_xpr_markparam(stp->st.swh.lpx);
   lstofsts_do_inpsel_set(stp->st.swh.lpst);
   break; 
  case S_WAIT:
   inpsel_xpr_markparam(stp->st.swait.lpx);
   lstofsts_do_inpsel_set(stp->st.swait.lpst);
   break; 
  case S_REPEAT:
   inpsel_xpr_markparam(stp->st.srpt.repx);
   lstofsts_do_inpsel_set(stp->st.srpt.repst);
   break;
  case S_FOR:
   {
    struct for_t *frs;
    struct st_t *stp2;

    frs = stp->st.sfor;
    /* AIV 10/01/10 - for assign can now have multiple - cannot use */
    /* list because is linked onto forbody */
    for (stp2 = frs->forassgn; stp2 != NULL; stp2 = stp2->stnxt)
     {
      if (stp2->stmttyp != S_FORASSGN) break;
      stmt_do_inpsel_set(stp2);
     }
    inpsel_xpr_markparam(frs->fortermx);
    lstofsts_do_inpsel_set(frs->forinc);
    lstofsts_do_inpsel_set(frs->forbody);
   }
   break;
  case S_DELCTRL:
   /* do not need to check delay expression - width will resolve to WBITS */
   lstofsts_do_inpsel_set(stp->st.sdc->actionst);
   break;
  case S_NAMBLK:
   /* do not need to process here - done when set bits for tasks defs */
   break;
  case S_UNBLK:
   lstofsts_do_inpsel_set(stp->st.sbsts);
   break;
  case S_UNFJ:
   { 
    int32 fji;
    struct st_t *fjstp;

    for (fji = 0;; fji++)
     {
      if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
      /* SJM 09/24/01 - this can be 2 stmts for for (for assgn then for) */
      lstofsts_do_inpsel_set(fjstp);
     }
   }
   break;
  case S_FUNCCALL:
  case S_TSKCALL:
   {
    struct expr_t *xp;

    for (xp = stp->st.stkc.targs; xp != NULL; xp = xp->ru.x)
     inpsel_xpr_markparam(xp->lu.x);
   }
   break;
  case S_QCONTA:
   inpsel_xpr_markparam(stp->st.sqca->qclhsx);
   inpsel_xpr_markparam(stp->st.sqca->qcrhsx);
   break;
  case S_CAUSE: case S_DSABLE: case S_NULL: case S_STNONE: case S_QCONTDEA:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * process each statements of statement list for in psel exprs
 */
static void lstofsts_do_inpsel_set(struct st_t *stp)
{
 for (; stp != NULL; stp = stp->stnxt) stmt_do_inpsel_set(stp);
}

static void csitemlst_do_inpsel_set(struct csitem_t *csip)
{
 struct exprlst_t *xplp;

 for (; csip != NULL; csip = csip->csinxt)
  {
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    inpsel_xpr_markparam(xplp->xp);
   lstofsts_do_inpsel_set(csip->csist);
  }
}

/*
 * mark any param that is appears inside any part select range
 * as sell as any CATREP repeat count expressions
 *
 * must process every module expr. through here if module target of
 * xmr defparam and multiply instantiated
 * since nested concatenates not yet expanded must handle nesting
 */
static void inpsel_xpr_markparam(struct expr_t *xp)
{
 /* loop statements expr. can be nil */
 if (xp == NULL) return;
  
 switch (xp->optyp) {
  case ID: case GLBREF: case NUMBER: case ISNUMBER:
  case REALNUM: case ISREALNUM:
   return;
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   __in_xpr_markparam(xp->ru.x->lu.x);
   __in_xpr_markparam(xp->ru.x->ru.x);
   return;
  case CATREP:
   inpsel_xpr_markparam(xp->lu.x);
   if (xp->ru.x != NULL) inpsel_xpr_markparam(xp->ru.x);
   return;
  }
 /* for here can have expr. like a + {...} inside concat - so descend */
 if (xp->lu.x != NULL) inpsel_xpr_markparam(xp->lu.x);
 if (xp->ru.x != NULL) inpsel_xpr_markparam(xp->ru.x);
}

/*
 * MODULE LEVEL DECLARATION CHECKING ROUTINES
 */

/*
 * check undefined symbol and freeze ranges (eval. defparam rhs exprs)
 * must stop if any pass 1 errors before calling this
 */
extern void __chk_1mdecls(void)
{
 struct task_t *tskp;
 int32 tregbasi;

 chk_undef_syms(__inst_mod->msymtab, MODULE);

 /* this also counts number of regs in tasks and set all nnum fields */
 chkset_1mwire_rnges();

 /* must check task variables before any statement checking because of */
 /* xmrs - notice named blocked included here */
 tregbasi = __inst_mod->mnnum;
 for (tskp = __inst_mod->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  { 
   __chk_taskvars(tskp, tregbasi);
   tregbasi += tskp->trnum;
  }
}

/*
 * check all symbols in given table (module/task/func/lab. block)
 * notice this cannot be used to check decl. of specify specparams 
 */
static void chk_undef_syms(struct symtab_t *sytp, word32 objttyp)
{
 int32 syi, save_obj;
 struct sy_t *syp;

 __wrkstab = sytp->stsyms;
 save_obj = __cur_declobj;
 __cur_declobj = objttyp;
 for (syi = 0; syi < (int32) sytp->numsyms; syi++)
  {
   syp = __wrkstab[syi];
   chk_modsym(syp);
  }
 __cur_declobj = save_obj;
}

/*
 * check one symbol
 */
static void chk_modsym(struct sy_t *syp)
{
 switch ((byte) syp->sytyp) {
  /* params still in symbol table but cannot be undeclared so works */
  case SYM_N:
   if (__cur_declobj == MODULE) chk_1wire(syp->el.enp);
   else chk_1reg(syp->el.enp);
   break;
  case SYM_TSK: case SYM_F: case SYM_STSK: case SYM_SF:
   if (!syp->sydecl)
    __gferr(770, syp->syfnam_ind, syp->sylin_cnt,
     "%s %s not declared", __to_sytyp(__xs, syp->sytyp), syp->synam);
   break;
  /* since non legal in expr. symbol error caught elsewhere */  
  case SYM_CA: case SYM_TCHK: case SYM_PTH: break;  
  /* things checked elsewhere that can be in mod. sym. table */
  /* and are declared by usage */
  case SYM_I: case SYM_LB: case SYM_UDP: case SYM_PRIM:
  break;
 default:
  /* symbol decl. lost */
  __misc_gfterr(__FILE__, __LINE__, syp->syfnam_ind, syp->sylin_cnt);
 }
}

/*
 * check 1 wire - just makes sure declared - must check attributes later
 * wire here just means not in task/func.
 */
static void chk_1wire(struct net_t *np)
{
 struct sy_t *syp;

 syp = np->nsym;
 if (!syp->sydecl)
  {
   if (syp->sytyp == SYM_CA || syp->sytyp == SYM_PTH
   || syp->sytyp == SYM_TCHK)
    {
     __gferr(1147, syp->syfnam_ind, syp->sylin_cnt,
      "constructed internal %s %s may not appear in source - only as run time string",
      __to_sytyp(__xs, syp->sytyp), syp->synam);
     return;
    }
   /* AIV 10/01/10 - changed this to generic 'variable' instead of */
   /* wire/reg/event - many more types */
   if (np->iotyp == NON_IO)
    {
     __gferr(771, syp->syfnam_ind, syp->sylin_cnt,
      "variable %s not declared", syp->synam);
    }
   else
    __gferr(772, syp->syfnam_ind, syp->sylin_cnt,
     "module definition port %s not declared", syp->synam);
   return;
  }
 /* LOOKATME - what trireg checking needed */
}

/*
 * check 1 task/function/named block wire
 * this can check everything because task declarations all at top
 *
 * this rotine is called through sybmol table checking for tasks
 */
static void chk_1reg(struct net_t *np)
{
 struct sy_t *syp;

 syp = np->nsym;
 if (!syp->sydecl)
  {
   __gferr(773, syp->syfnam_ind, syp->sylin_cnt,
    "task/function/named block reg %s not declared", syp->synam);
   return;
  }
}

/*
 * check and set the module's wire ranges
 *
 * also preprocesses wire delays to simulation form and builds wire tab by
 * copying list elements to table and freeing list 
 * notice key is that nothing before here points directly to net
 * always through symbol table which is also updated here
 *
 * routine is passed total number of vars in modules so all vars
 * including task regs are contigous and can be accessed as offset
 * from mod base
 *
 */
static void chkset_1mwire_rnges(void)
{
 int32 syi, ni, ai, ai2, new_stsiz;
 int32 nnum, mvarnum, arrwid, wirarr_el_num, sav_last_sy2;
 struct sy_t *syp;
 struct net_t *np;
 struct sy_t **syms;
 struct symtab_t *sytp;
 struct net_t *ntab, *np2;
 struct task_t *tskp;

 sytp = __inst_mod->msymtab;
 /* count number of nets and store in mod field */
 nnum = wirarr_el_num = 0;
 for (syi = 0, syms = sytp->stsyms; syi < (int32) sytp->numsyms; syi++)
  {
   syp = syms[syi];

   if (syp->sytyp != SYM_N) continue;
   np = syp->el.enp;
   /* count wire arrays as one non array wire for each element */
   if (np->n_isarr && np->ntyp < NONWIRE_ST)
    {
     /* AIV 07/15/09 - need to set wire ranges prior to calling get_arrwide */
     /* this was not converting ranges set by parameters */
     chk_wire_rng(np);
     arrwid = __get_arrwide(np);
     nnum += arrwid;
     wirarr_el_num += arrwid;
    }
   if (!np->n_isaparam) nnum++;
  }

 __inst_mod->mnnum = nnum; 
 mvarnum = nnum;

 /* then count number of regs in each task - set and keep running total */
 for (tskp = __inst_mod->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   sytp = tskp->tsksymtab;
   nnum = 0;
   for (syi = 0, syms = sytp->stsyms; syi < (int32) sytp->numsyms; syi++)
    {
     syp = syms[syi];
     if (syp->sytyp != SYM_N) continue;
     np = syp->el.enp;
     if (np->n_isaparam) continue;
     nnum++;
    }
   tskp->trnum = nnum;
   mvarnum += nnum;
  }

 /* set total nnumber of vars in module for possible use by dmpv */
 __inst_mod->mtotvarnum = mvarnum;

 ntab = NULL;
 if (mvarnum != 0)
  {   
   ntab = (struct net_t *) __my_malloc(mvarnum*sizeof(struct net_t)); 
  }

 /* SJM 08/30/00 must include task nets here in case only task's have */
 /* declared variables */
 if (__inst_mod->mtotvarnum == 0) return;
 __inst_mod->mnets = ntab; 

 if (wirarr_el_num != 0)
  {
   __wrkstab2 = (struct sy_t **)
    __my_malloc(wirarr_el_num*sizeof(struct sy_t *));
  }
 __last_sy2 = -1;

 /* fixing task vars in ntab later */
 /* point sytp back to mod not task symbol table */
 sytp = __inst_mod->msymtab;
 /* not sure if saved needed here */
 for (ni = 0, syi = 0, syms = sytp->stsyms; syi < (int32) sytp->numsyms; syi++)
  {
   syp = syms[syi];
   if (syp->sytyp != SYM_N) continue;

   np = syp->el.enp;
   /* parameters checked elsewhere */
   if (np->n_isaparam) continue;

   /* do not include wire arrays yet - */
   if (np->n_isarr && np->ntyp < NONWIRE_ST)
    {
     /* SJM 02-22-09 chk wire rng sets ranges for wire array so can add */
     /* one array for each array element */
     chk_wire_rng(np);
     chk_1wire_delay(np);

     sav_last_sy2 = __last_sy2 + 1;
     fill_wire_arr_wrkstab(np);
     for (ai = sav_last_sy2; ai <= __last_sy2; ai++)
      {
       np2 = &(ntab[ni]);
       __copy_wire_from_wire_array(np2, np);
       np2->nsym = __wrkstab2[ai];
       np2->nsym->el.enp = np2;
       /* mark this net as coming from a wire array */
       np2->n_isarr_vector = TRUE;
       ni++;
      }
     //AIV FIXME - AIV WA - need to still process regular net 
     //should remove wire array net??????
     //continue;
    }

   np2 = &(ntab[ni]);
   *np2 = *np;
   __my_free(np, sizeof(struct net_t));
   syp->el.enp = np2;
   ni++;
   np = np2;

   /* do not need to save these, never called with previous location */
   __sfnam_ind = np->nsym->syfnam_ind;
   __slin_cnt = np->nsym->sylin_cnt;

   chk_wire_rng(np);
   chk_1wire_delay(np);
  }

 /* AIV 01/04/12 - if error count not zero could be result of bad formed */
 /* array which later causes a SEGV */
 if (__pv_err_cnt != 0) return; 

 /* final step is building new frozen (array form) mod symbol table */
 sytp = __inst_mod->msymtab;
 new_stsiz = wirarr_el_num + sytp->numsyms;
 __wrkstab = (struct sy_t **) __my_malloc(new_stsiz*sizeof(struct sy_t *));
 for (ai = 0; ai < sytp->numsyms; ai++)
  {
   __wrkstab[ai] = sytp->stsyms[ai];
  }
 ai2 = 0;
 for (ai = sytp->numsyms; ai < new_stsiz; ai++)
  {
   __wrkstab[ai] = __wrkstab2[ai2++];
  }
 /* re-sort symbol table */
 qsort((char *) __wrkstab, (word32) new_stsiz, sizeof(struct sy_t *),
  __gia_sym_cmp);
 __my_free(sytp->stsyms, sytp->numsyms*sizeof(struct sy_t *)); 
 sytp->numsyms = new_stsiz;
 sytp->stsyms = __wrkstab;
 
 if (wirarr_el_num != 0)
  {
   __my_free(__wrkstab2, wirarr_el_num*sizeof(struct sy_t *)); 
  }
}

/*
 * routine to check wire delays
 *
 * LOOKATME - maybe should allow expressions here but lrm says no 
 * can process expression at this early point since final value 
 * of all parameters know by here 
 */
static void chk_1wire_delay(struct net_t *np)
{
 int32 dnum;
 struct paramlst_t *pmp, *dhdr;

 if ((pmp = np->nu.ct->n_dels_u.pdels) == NULL) return;

 dhdr = __copy_dellst(pmp);
 if ((dnum = __chk_delparams(dhdr, "wire delay", TRUE)) == -1)
  np->nu.ct->n_dels_u.pdels = NULL;
 else
  {
   if (dnum > 3)
    {
     __sgferr(792,
      "wire delay for %s has more then 3 delays (%d)", np->nsym->synam, dnum);
      np->nu.ct->n_dels_u.pdels = NULL;
    }
  }
 __free_dellst(dhdr);
}

/*
 * build a wire array name for each element of wire array
 *  
 * fills tab ax1 and tab ax2 but then frees since all arrays set in prep
 * uses dim_mult as running place holder 
 *
 * SJM 02-22-09 - new code to convert (split) wire arrays to one wire for
 * each array element
 */
static void fill_wire_arr_wrkstab(struct net_t *np)
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
     syp = (struct sy_t *) __my_malloc(sizeof(struct sy_t));
     /* need net sym as basic pattern then modify where needed */
     *syp = *(np->nsym);
     syp->synam = __pv_stralloc(s1);
     __wrkstab2[++__last_sy2] = syp;
    }
   return;
  }

 tmp_fill_mda_rnges(np);
  
 /* set the mda element nets */
 fill_mda_wire_wrkstab(np, mdap, s1, 0);
}

/*
 * recursive call to create a vector net for every element in a mda
 */
static void fill_mda_wire_wrkstab(struct net_t *np, struct mda_t *mdap,
 char *s1, int32 dim)
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
     syp = (struct sy_t *) __my_malloc(sizeof(struct sy_t));
     *syp = *(np->nsym);
     sprintf(s3, "%s%s", np->nsym->synam, s2);
     syp->synam = __pv_stralloc(s3);
     __wrkstab2[++__last_sy2] = syp;
    }
   fill_mda_wire_wrkstab(np, mdap, s2, dim+1);
  }
}

/*
 * alloc and fill mda rng high and low values (not dim mult since not needed)
 */
static void tmp_fill_mda_rnges(struct net_t *np)
{
 int32 dim, i, nai1, nai2;
 struct mda_t *mdap;

 mdap = np->mda;
 /* DBG remove -- */
 if (mdap == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---*/
 /* allocate space for the ranges and the dimension multiplier */
 dim = mdap->dimension;
 mdap->rng1 = (int32 *) __my_malloc(sizeof(int32)*dim);
 mdap->rng2 = (int32 *) __my_malloc(sizeof(int32)*dim);
 mdap->dim_mult = (int32 *) __my_malloc(sizeof(int32)*dim);
 for (i = 0; i < dim; i++)
  {
   nai1 = (int32) __contab[mdap->tab_ax1[i]->ru.xvi];
   mdap->rng1[i] = nai1;
   nai2 = (int32) __contab[mdap->tab_ax2[i]->ru.xvi];
   mdap->rng2[i] = nai2;
   mdap->dim_mult[i] = __mda_multiplier(np, i);
  }
}

/*
 * debugging routine to dump net names of all nets in all modules
 */
extern void __dbg_dmpall_nets(void)
{
 int32 ni;
 struct mod_t *mdp;
 struct net_t *np;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __dbg_msg("--- dumping nets for module %s\n", mdp->msym->synam);
   if (mdp->mnnum == 0) continue;
   for (np = &(mdp->mnets[0]), ni = 0; ni < mdp->mnnum; ni++, np++)
    {
     __dbg_msg("  setting symbol %s to point to net %s\n",
      np->nsym->synam, np->nsym->el.enp->nsym->synam);
    }
  }
}

/*
 * STRENGTH PROPOGATION TO WIRES ROUTINES
 */

/*
 * mark wires that need strength storage and all strength expressions
 * notice this is before splitting since strengths structural
 */
extern void __mark_st_wires(void)
{
 /* mark all wires that are strength from type (no wire strength decls) */
 mark_sttypewires();
 /* mark all wires immediately driven by strengths */
 mark_stdr_wires();
 mark_stdr_inout_wired_logic();
 if (__design_no_strens) return;

 /* must build module type levelized table after all splitting */
 /* only used here but not freed since only 4 byte ptr per level */
 /* field in mod_t needed anyway */  
 __bld_mlevel_lists();

 /* SJM 10/16/99 - need to keep propagating until no progress */
 /* not sure why this is needed but missing strenght from 4 */
 /* know need 4 for shorted inout ports - why more? */
 for (;;)
  {
   __strenprop_chg = FALSE;
   prop_stsdown();
   /* prop strengths up through mod outs and inouts */
   prop_stsup();
   /* DBG remove -- */
   if (__debug_flg) __dbg_msg("  >>> Complete one strength marking pass.\n");
   /* --- */
   if (!__strenprop_chg) break;
  }
}

/*
 * mark all wires that are strength from decl. type
 * know if module in list - will be in output
 */
static void mark_sttypewires(void)
{
 int32 syi;
 struct mod_t *mdp;
 struct net_t *np;
 struct sy_t *syp;
 struct sy_t **syms;
 struct symtab_t *sytp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   sytp = mdp->msymtab;
   /* table (array) of nets still not built at this point */
   for (syi = 0, syms = sytp->stsyms; syi < (int32) sytp->numsyms; syi++)
    {
     syp = syms[syi];
     if (syp->sytyp != SYM_N) continue;
     np = syp->el.enp;

     /* notice N_TRI is just N_WIRE */

     switch ((byte) np->ntyp) {
      /* these are always marked strength */
      case N_TRIREG: case N_TRI0: case N_TRI1: case N_SUPPLY0:
      case N_SUPPLY1:
       np->n_stren = TRUE;
       mdp->mhassts = TRUE;
       __design_no_strens = FALSE;

       /* --- DBG remove
       if (__debug_flg)
        __dbg_msg("++marking direct decl. type wire %s in %s\n", np->nsym->synam,
         mdp->msym->synam);
       --- */

       break;
     }
    }
  }
}

/*
 * for every module mark wire that are driven by strengths
 * notice explicit conta output driving strength is treated as no strength
 * think that may be wrong.
 */
static void mark_stdr_wires(void)
{
 int32 gi, i;
 struct mod_t *mdp;
 struct conta_t *cap;
 struct gate_t *gp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (gi = 0; gi < mdp->mgnum; gi++)
    {
     gp = &(mdp->mgates[gi]);

     switch ((byte) gp->g_class) {
      case GC_PULL:
       /* pull all connections */
       for (i = 0; i < (int32) gp->gpnum; i++)
        { mark_stwires(mdp, gp->gpins[i]); }
       break;
      case GC_MOS: case GC_TRAN: case GC_TRANIF: case GC_CMOS:
       /* mos or tran gates first 2 ports only - rest are controls */
       mark_stwires(mdp, gp->gpins[0]);
       mark_stwires(mdp, gp->gpins[1]);
       break;
      case GC_BUFIF:
       /* buffer only output is strength */
       mark_stwires(mdp, gp->gpins[0]);
       break;
      case GC_LOGIC: case GC_UDP:
       /* logic only mark output if has strength */
       if (gp->g_hasst && gp->g_stval != ST_STRVAL)
        mark_stwires(mdp, gp->gpins[0]);
       break;
      }
    }
   for (cap = mdp->mcas; cap != NULL; cap = cap->pbcau.canxt)
    {
     if (!cap->ca_hasst || cap->ca_stval == ST_STRVAL) continue;
     /* 1 bit continuous assign not converted to gate at this point */
     mark_stwires(mdp, cap->lhsx);
    }
  }
}

/*
 * routine to mark wires in port highconn or lowconn that have wired logic
 * stren model - needed so will use wire type incremental switch relax proc
 *
 * 04/22/01 SJM - changed so wand/wor in inout port hi/low conn always stren
 */
static void mark_stdr_inout_wired_logic(void)
{
 int32 ii, pi, pnum;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct mod_t *imdp;
 struct expr_t *xp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* if inout port and lowconn wor/wand, mark port expr as stren */ 
   for (pi = 0; pi < mdp->mpnum; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     if (mpp->mptyp != IO_BID) continue;

     if (has_non_stren_wired_net(mpp->mpref))
      mark_stwires(mdp, mpp->mpref);
    }

   /* if iconn highconn wor/wand, mark expr as stren */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((pnum = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < pnum; pi++)
      {
       mpp = &(imdp->mpins[pi]);
       if (mpp->mptyp != IO_BID) continue;

       xp = ip->ipins[pi];
       if (has_non_stren_wired_net(xp)) mark_stwires(imdp, xp);
      }
    }
  } 
}

/*
 * return T if inout (lhs) expr, has wand or wor port
 */
static int32 has_non_stren_wired_net(struct expr_t *lhsx)
{
 struct expr_t *catndp;
 struct net_t *np;

 switch (lhsx->optyp) {
  /* SJM 07/10/01 - if later syntax error non lvalues possible here */
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM: case OPEMPTY:
   break;
  case ID: case GLBREF:
   np = lhsx->lu.sy->el.enp;
   if (net_type_tri(np->ntyp)) return(TRUE);
   break;
  case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   np = lhsx->lu.x->lu.sy->el.enp;
   if (net_type_tri(np->ntyp)) return(TRUE);
   break;
  case LCB:
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x) 
    {
     if (has_non_stren_wired_net(catndp->lu.x)) return(TRUE);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE); 
}

/*
 * return T if net type is wand or wor (wired logic) 
 */
static int32 net_type_tri(word32 ntyp)
{
 switch ((byte) ntyp) {
  case N_TRIOR: case N_WO: case N_TRIAND: case N_WA: return(TRUE);
  default: break;
 }
 return(FALSE);
}

/*
 * check to see if expr has any stren wires, if yes return T else F 
 *
 * SJM 06/01/01 - need separate check routine because must return
 * T if any concat el has stren but must always set all elements
 * logic for combined routine was wrong
 */
static int32 chk_hasst_wires(struct mod_t *mdp, struct expr_t *lhsx)
{
 struct net_t *np;

 switch (lhsx->optyp) {
   /* if global has driven strength - all instances of wire must be */
   /* strength */
  case GLBREF: case ID:
   np = lhsx->lu.sy->el.enp;
   break;
  case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   /* this is bit select or array index */
   np = lhsx->lu.x->lu.sy->el.enp;
   break;
  case LCB:
   {
    struct expr_t *ndp2;

    /* know lhs concatenates never nested */
    for (ndp2 = lhsx->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
     {
      /* if any strength, must other must be marked */
      if (chk_hasst_wires(mdp, ndp2->lu.x)) return(TRUE);
     }
    return(FALSE);
   }
  default: return(FALSE);
 }
 /* know if non wire, n stren never true */
 if (np->n_stren) return(TRUE);
 return(FALSE);
}

/*
 * for lhs expression driven with strength mark all wires
 * if not good lhs, ignore error caught later
 *
 * SJM 06/01/15 - change so separate mark routine
 */
static void mark_stwires(struct mod_t *mdp, struct expr_t *lhsx)
{
 struct net_t *np;

 switch (lhsx->optyp) {
   /* if global has driven strength - all instances of wire must be */
   /* strength */
  case GLBREF: case ID:
   np = lhsx->lu.sy->el.enp;
   break;
  case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   /* this is bit select or array index */
   np = lhsx->lu.x->lu.sy->el.enp;
   break;
  case LCB:
   {
    struct expr_t *ndp2;

    /* know lhs concatenates never nested */
    /* mark all - if some els already marked, does nothing */
    for (ndp2 = lhsx->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
     { mark_stwires(mdp, ndp2->lu.x); }
    return;
   }
  default: return;
 }
 /* must be wire to have strength */
 if (np->ntyp >= NONWIRE_ST) return;

 /* SJM 10/15/99 - if mark and already marked, just return T */  
 if (!np->n_stren)
  {
   /* --- DBG remove */
   if (__debug_flg)
    __dbg_msg("++marking wire %s in %s\n", np->nsym->synam,
     mdp->msym->synam);
   /* --- */
   np->n_stren = TRUE;
   __strenprop_chg = TRUE;
   mdp->mhassts = TRUE;
   __design_no_strens = FALSE;
  }
}

/*
 * build the levelized module type list 
 *
 * this is sometimes called before minsts exists (part of d.s. built)
 */
extern void __bld_mlevel_lists(void)
{
 int32 mlevel;
 struct mod_t *mdp, *last_mdp;

 /* then build the by level header table and link same level modules on it */
 if (__mdlevhdr == NULL)
  {
   __mdlevhdr = (struct mod_t **)
    __my_malloc((__dagmaxdist + 1)*sizeof(struct mod_t *)); 
  }
 /* need to initialize this to nil since may be rebuilt */
 for (mlevel = 0; mlevel <= __dagmaxdist; mlevel++) __mdlevhdr[mlevel] = NULL;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt) mdp->mlevnxt = NULL;

 for (mlevel = 0; mlevel <= __dagmaxdist; mlevel++)
  {
   last_mdp = NULL;
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     if (mdp->mlpcnt != mlevel) continue;
     if (last_mdp == NULL) __mdlevhdr[mlevel] = mdp;
     else last_mdp->mlevnxt = mdp;
     last_mdp = mdp;
    }
  }
}

/*
 * propagate strengths down
 *
 * 04/22/01 - changed so inout port either highconn or lowonn wired and or or
 * now both marked as strength
 */
static void prop_stsdown(void)
{
 int32 pi, ii, mlevel, pnum;
 struct mod_t *smdp;
 /* do all max. dag dist. modules first - level 1 has no insts. */
 struct inst_t *ip;
 struct mod_pin_t *mpp;
 struct mod_t *imdp;
 struct expr_t *xp;

 /* could stop one up (level 2 (1 from bottom)) here */
 for (mlevel = __dagmaxdist; mlevel >= 0; mlevel--)
  {
   for (smdp = __mdlevhdr[mlevel]; smdp != NULL; smdp = smdp->mlevnxt)
    {
     /* even if no strength must still try to propagate down for */
     /* possible unconndrive */
     for (ii = 0; ii < smdp->minum; ii++)
      {
       ip = &(smdp->minsts[ii]);

       imdp = ip->imsym->el.emdp;
       if ((pnum = imdp->mpnum) == 0) goto nxt_inst;

       for (pi = 0; pi < pnum; pi++)
        {
	 mpp = &(imdp->mpins[pi]);
	 if (mpp->mptyp == IO_OUT) continue;

         xp = ip->ipins[pi];
         /* --- DBG remove
         if (__debug_flg)
          __dbg_msg(
           "++trying to prop stren down from %s (in %s) to %s (in %s)\n",
           __msgexpr_tostr(__xs, xp), smdp->msym->synam,
           __msgexpr_tostr(__xs2, mpp->mpref), imdp->msym->synam);  
         --- */

         /* if op empty `unconndrive, must propagate st. down */
         if (xp->optyp == OPEMPTY && xp->unc_pull != NO_UNCPULL) 
          { mark_stwires(imdp, mpp->mpref); continue; }

	 /* if port inst. port has strength, propagate down */
         if (chk_hasst_wires(smdp, xp))
	  { mark_stwires(imdp, mpp->mpref); continue; }
	}
nxt_inst:;
      }
    }
  }
}

/*
 * propagate strengths up
 */
static void prop_stsup(void)
{
 int32 pi, ii, mlevel, pnum;
 struct mod_t *smdp;
 struct inst_t *ip;
 struct mod_pin_t *mpp;
 struct mod_t *imdp;
 struct expr_t *xp;

 /* start up 1 since propagating from one down to current */
 for (mlevel = 1; mlevel <= __dagmaxdist; mlevel++)
  {
   for (smdp = __mdlevhdr[mlevel]; smdp != NULL; smdp = smdp->mlevnxt)
    {
     /* go through module instances marking down port wires */
     for (ii = 0; ii < smdp->minum; ii++)
      {
       ip = &(smdp->minsts[ii]);
        
       imdp = ip->imsym->el.emdp;
       if ((pnum = imdp->mpnum) == 0) goto nxt_inst;
       for (pi = 0; pi < pnum; pi++)
        {
         mpp = &(imdp->mpins[pi]);
         xp = ip->ipins[pi];
	 if (mpp->mptyp == IO_IN) continue;

         /* --- DBG remove
         if (__debug_flg)
          __dbg_msg(
           "++trying to prop stren up from %s (in %s) to %s (in %s)\n",
           __msgexpr_tostr(__xs, mpp->mpref), imdp->msym->synam,  
           __msgexpr_tostr(__xs2, xp), smdp->msym->synam);
         --- */

	 /* if down port has strength, need to propagate up */
         if (chk_hasst_wires(imdp, mpp->mpref))
          mark_stwires(smdp, xp);
	}
nxt_inst:;
      }
    }
  }
}

/*
 * ROUTINES TO CHECK CONSTANT DELAYS (IGNORES DELAY EXPRS)
 */

/*
 * check a list of constant delays and convert to scaled non real ticks
 * return number of delays - -1 on error
 */
extern int32 __chk_delparams(struct paramlst_t *pmp2, char *emsg,
 int32 mustbeconst)
{
 struct paramlst_t *pmp;
 int32 pmnum, err;

 err = FALSE;
 for (pmnum = 0, pmp = pmp2; pmp != NULL; pmp = pmp->pmlnxt, pmnum++)
  {
   if (!chkdel_expr(pmp->plxndp, emsg, mustbeconst)) err = TRUE;
   /* make sure actual delay expressions output as dec. */
   pmp->plxndp->ibase = BDEC;
   /* param expression evaluted to number during delay prep */  
  }
 if (err) return(-1);
 return(pmnum);
}

/*
 * check a delay expression but cannot convert until prep. time
 * uses flag mustbeconst to cause error if expr. 
 * returns F on error
 */
static int32 chkdel_expr(struct expr_t *dxp, char *emsg,
 int32 mustbeconst)
{
 int32 sav_ecnt;

 sav_ecnt = __pv_err_cnt;
 __chk_rhsexpr(dxp, 0);
 if (mustbeconst) return(__chk_numdelay(dxp, emsg));
 /* case (procedural for now) where delay can be expression */
 if (sav_ecnt != __pv_err_cnt) return(FALSE); 
 /* delay expr. always output as decimal */
 dxp->ibase = BDEC;
 return(TRUE);
}

/*
 * check to make sure a delay is a number
 * returns F on error 
 */
extern int32 __chk_numdelay(struct expr_t *ndp, char *emsg)
{
 switch (ndp->optyp) {
  case NUMBER: 
   if (!nd_delnum(ndp, emsg)) return(FALSE);
   break;
  case ISNUMBER:
   if (!nd_delisnum(ndp, emsg)) return(FALSE);
   break;
  case REALNUM: case ISREALNUM: return(TRUE);
  default: 
   __sgferr(845, "non constant %s delay illegal", emsg); 
   __free2_xtree(ndp);
   __init_xnd(ndp);

   /* bad delay must be 0 */
   ndp->ru.xvi = __alloc_shareable_cval(0, 0, WBITS);
   ndp->szu.xclen = WBITS;
   ndp->optyp = NUMBER;
   return(FALSE);
 }
 return(TRUE);
}

/*
 * check NUMBER delay to make sure convert in prep. section will succeed
 * catches too wide (non 0) and x/z forms - if expr. converts to 0 const.
 */
static int32 nd_delnum(struct expr_t *ndp, char *emsg)
{
 int32 err, wlen;
 word32 *ap, *bp;
 struct xstk_t *xsp;

 err = FALSE;
 ap = &(__contab[ndp->ru.xvi]);
 wlen = wlen_(ndp->szu.xclen);
 bp = &(ap[wlen]);
 if (ndp->szu.xclen > TIMEBITS)
  {
   if (!vval_is0_(&(ap[2]), ndp->szu.xclen - TIMEBITS) 
    || !vval_is0_(bp, ndp->szu.xclen))
    {
     __force_base = BDEC;
     __msgexpr_tostr(__xs, ndp);
     __force_base = BNONE;
     err = TRUE;
    }
   /* always free-alloc */
   __free2_xtree(ndp);
   __init_xnd(ndp);
   /* notice if not a number make into 32 bit x */
   ndp->optyp = NUMBER;
   if (err) 
    {
     ndp->szu.xclen = WBITS;
     /* bad delay must be zero */
     ndp->ru.xvi = __alloc_shareable_cval(0, 0, WBITS);
     goto wr_msg;
    }

   /* LOOKATME - time width dependent */
   ndp->szu.xclen = TIMEBITS;
   ndp->ru.xvi = __allocfill_cval_new(ap, bp, 2);
   return(TRUE);
  }
 if (ndp->szu.xclen > WBITS)
  {
   if (bp[0] != 0L || bp[1] != 0L) 
    {
     /* notice on error here just leave as 8 bytes - since non IS form */
     ndp->szu.xclen = TIMEBITS;

     push_xstk_(xsp, 2*WBITS);
     memset(xsp->ap, 0, 4*WRDBYTES);
     ndp->ru.xvi = __allocfill_cval_new(xsp->ap, xsp->bp, 2);
     __pop_xstk();
     goto fill_xs;
    }
   return(TRUE);
  }
 ndp->szu.xclen = WBITS;
 if (bp[0] == 0L) return(TRUE); 
 ndp->ru.xvi = __alloc_shareable_cval(0, 0, WBITS);

fill_xs:
 __force_base = BDEC;
 __msgexpr_tostr(__xs, ndp);
 __force_base = BNONE;

wr_msg:
 __sgferr(848,
  "%s value %s not required up to %d bit non x/z delay number - set to 0",
  emsg, __xs, TIMEBITS);
 return(FALSE);
}

/*
 * need an delay up to 64 bit number - same as nd_ndxisnum except 64 bits  
 * changed in prep - this just checks but if error converts to 0
 * LOOKATME - should change from TIMEBITS 8 bytes to 4 bytes if all high 0
 * SIZEDEPENDENT notice this routine has built in 32 bit word32 and 64 bit time
 *
 * FIXME - this routine looks wrong or can be improved
 */
static int32 nd_delisnum(struct expr_t *ndp, char *emsg)
{
 int32 iti, err, wlen, wsiz;
 word32 *wp, *wp2, *ap, *bp;
 
 err = FALSE;
 wlen = wlen_(ndp->szu.xclen);
 wp = &(__contab[ndp->ru.xvi]);
 /* case 1: wider than TIMEBITS (64) */
 if (ndp->szu.xclen > 64)
  {
   /* check all high bits if 0 and not z just extract low 8 byte sections */
   for (iti = 0; iti < __inst_mod->flatinum; iti++)
    {
     ap = &(wp[2*wlen*iti]);
     bp = &(ap[wlen]);
     if (!vval_is0_(&(ap[2]), ndp->szu.xclen - 64) 
      || !vval_is0_(bp, ndp->szu.xclen))
      { wr_ndisdel_err(ndp, iti, emsg); err = TRUE; }
    }
   if (err) { freeset_is0del(ndp, __inst_mod->flatinum); return(FALSE); }

   /* convert to TIMEBITS by extracting low 64 a/b bits of each */ 
   /* this frees subtree under ndp but xva constant field can not be freed */
   __free2_xtree(ndp);
   __init_xnd(ndp);
   ndp->optyp = ISNUMBER;
   ndp->szu.xclen = TIMEBITS;
   wsiz = 2*__inst_mod->flatinum; 
   ndp->ru.xvi = __alloc_is_cval(wsiz);
   wp2 = &(__contab[ndp->ru.xvi]);
   if (__compiled_sim)
    {
     __add_isnum_to_tree((void *) ndp, ndp->ru.xvi, ndp->szu.xclen);
    }
   for (iti = 0; iti < __inst_mod->flatinum; iti++)
    {
     ap = &(wp[2*wlen*iti]);
     bp = &(ap[wlen]);
     wp2[4*iti] = ap[0]; wp2[4*iti + 1] = ap[1];
     wp2[4*iti + 2] = bp[0]; wp2[4*iti + 3] = bp[1];
    }
   return(TRUE);
  }
 /* case 2 between WBITS and TIMEBITS */
 if (ndp->szu.xclen > WBITS)
  {
   for (iti = 0; iti < __inst_mod->flatinum; iti++)
    {
     ap = &(wp[4*iti]);
     bp = &(ap[2]);
     if (bp[0] != 0L || bp[1] != 0L)
      { wr_ndisdel_err(ndp, iti, emsg); err = TRUE; }
    }
   /* notice on error here even good instances set to 0 */  
   if (err) { freeset_is0del(ndp, __inst_mod->flatinum); return(FALSE); }
   /* this uses fact that constants are always stored as 8 byte chunks */
   ndp->szu.xclen = 64;
   return(TRUE);
  }
 /* finally case is all WBITS */
 for (iti = 0; iti < __inst_mod->flatinum; iti++)
  {
   ap = &(wp[2*iti]); bp = &(ap[1]);
   if (bp[0] != 0L)
    {
     wr_ndisdel_err(ndp, iti, emsg);
     ap[0] = bp[0] = 0L; 
     err = TRUE;
    }
  }
 /* here value left unless x/z in which case converted to 0 */ 
 ndp->szu.xclen = WBITS;
 return(!err);
}

/*
 * upon error free and set delay expr. to WBITS IS delay 0's
 *
 * LOOKATME - this does not free previous constant entry
 */
static void freeset_is0del(struct expr_t *ndp, int32 insts)
{
 int32 iti;
 word32 *wp;

 __free2_xtree(ndp);
 __init_xnd(ndp);
 ndp->optyp = ISNUMBER;
 ndp->szu.xclen = WBITS;
 ndp->ru.xvi = __alloc_is_cval(1*insts);
 wp = &(__contab[ndp->ru.xvi]);
 for (iti = 0; iti < insts; iti++) wp[2*iti] = wp[2*iti + 1] = 0L;
 if (__compiled_sim)
  {
   __add_isnum_to_tree((void *) ndp, ndp->ru.xvi, ndp->szu.xclen);
  }
}

/*
 * write an is need delay form error message
 */
static void wr_ndisdel_err(struct expr_t *ndp, int32 iti, char *emsg)
{
 char s1[RECLEN];

 __force_base = BDEC;
 __sgferr(838,
  "%s value %s not required up to %d bit non x/z delay number (inst. %d)",
   emsg, __msgnumexpr_tostr(s1, ndp, iti), TIMEBITS, iti);
 __force_base = BNONE;
}

/*
 * check a wires range and array range
 */
static void chk_wire_rng(struct net_t *np)
{
 int32 vwid, mwid, ival;
 word32 *wp;
 struct expr_t *ndp, *ndp2;
 char s1[RECLEN]; 

 if (np->n_isavec)
  {
   /* this must be a non x/z constant that can be a wire range */
   /* changes to WBIT vectored form */
   /* never IS form */ 
   sprintf(s1, "wire or reg first range of %s", np->nsym->synam);
   if (!__chkndx_expr(np->nu.ct->nx1, s1))
    {
bad_wire:
     np->n_isavec = FALSE;
     np->nu.ct->nx1 = np->nu.ct->nx2 = NULL;
     goto chk_arr;
    }
   wp = &(__contab[np->nu.ct->nx1->ru.xvi]);
   ival = (int32) wp[0];
   /* AIV 02/24/10 - LRM allows negative indices */
   /*
   if (ival < 0)
    {
     __sgferr(902, "%s value %d illegal negative number", s1, ival);
     goto bad_wire;
    }
   */
   
   sprintf(s1, "wire or reg second range of %s", np->nsym->synam);
   if (np->nu.ct->nx2 == NULL || !__chkndx_expr(np->nu.ct->nx2, s1))
    goto bad_wire;

   wp = &(__contab[np->nu.ct->nx2->ru.xvi]);
   ival = (int32) wp[0];
   /* AIV 02/24/10 - LRM allows negative indices */
   /*
   if (ival < 0)
    {
     __sgferr(902, "%s value %d illegal negative number", s1, ival);
     goto bad_wire;
    }
   */

   /* know net ranges fit in 32 bits or will not get here */
   vwid = __get_netwide(np);
   if (vwid > MAXNUMBITS)
    {
     __sgferr(774,
      "wire or reg %s range width %d too wide (%d)", np->nsym->synam, vwid,
      MAXNUMBITS);
     np->n_isavec = FALSE;
     np->nu.ct->nx1 = np->nu.ct->nx2 = NULL;
     goto chk_arr;
    }
   /* DBG remove */
   if (np->nu.ct->nx1 == NULL || np->nu.ct->nx2 == NULL) 
    __misc_terr(__FILE__, __LINE__);  
   /* -- */

   /* for one pound param case, IS form possible but know all same */
   /* know only one place in source and only pound params used */
   /* all of what is seen as IS form same so check and fix here */
   ndp = np->nu.ct->nx1;
   ndp2 = np->nu.ct->nx2;
   if (ndp->optyp == ISNUMBER)
    {
     chg_rng_isnum_to_num(np, ndp, "first vector range");
    }
   if (ndp2->optyp == ISNUMBER)
    {
     chg_rng_isnum_to_num(np, ndp2, "second vector range");
    }
   if (ndp->optyp != NUMBER)
    {
     __sgfterr(329,
      "wire or reg %s in module %s impossible first vector range expression %s",
      np->nsym->synam, __inst_mod->msym->synam, __msgexpr_tostr(__xs, ndp));
    }
   if (ndp2->optyp != NUMBER)
    {
     __sgfterr(329,
      "wire or reg %s in module %s impossible second vector range expression %s",
      np->nsym->synam, __inst_mod->msym->synam, __msgexpr_tostr(__xs, ndp2));
    }
  }
 /* inconsistent scalar range */
 else if (np->nu.ct->nx1 != NULL || np->nu.ct->nx2 != NULL)
  __misc_terr(__FILE__, __LINE__);

 /* check array */
chk_arr:
 if (np->mda != NULL) 
  {
   chk_wire_dma_rng(np);
   return;
  }
 if (np->n_isarr)
  {
   sprintf(s1, "array first range of %s", np->nsym->synam);
   if (!__chkndx_expr(np->nu.ct->ax1, s1))
    {
bad_arr:
     np->n_isarr = FALSE;
     /* AIV 01/04/12 - cannot NULL here causes SEGV - no need to NULL anyway */
     /* np->nu.ct->ax1 = np->nu.ct->ax2 = NULL; */
     return;
    }
   wp = &(__contab[np->nu.ct->ax1->ru.xvi]);
   ival = (int32) wp[0];
   /* AIV 02/24/10 - LRM allows negative indices */
   /*
   if (ival < 0)
    {
     __sgferr(902, "%s value %d illegal negative number", s1, ival);
     goto bad_arr;
    }
   */
   sprintf(s1, "array second range of %s", np->nsym->synam);
   if (np->nu.ct->ax2 == NULL || !__chkndx_expr(np->nu.ct->ax2, s1))
    goto bad_arr;

   wp = &(__contab[np->nu.ct->ax2->ru.xvi]);
   ival = (int32) wp[0];
   /* AIV 02/24/10 - LRM allows negative indices */
   /*
   if (ival < 0)
    {
     __sgferr(902, "%s value %d illegal negative number", s1, ival);
     goto bad_arr;
    }
   */

   /* allowing up to 2*24 cells (SJM 11/13/00 - comment was wrong) */
   mwid = __get_arrwide(np);
#ifndef __CVC_RT__
   if (mwid < 0 || mwid > 0x00ffffff)
    {
     __sgfwarn(620,
      "array %s has %d cells - standard only requires maximum of %d",
      np->nsym->synam, mwid, 0x00ffffff);
    }
#endif
   /* DBG remove */
   if (np->nu.ct->ax1 == NULL || np->nu.ct->ax2 == NULL) 
    __misc_terr(__FILE__, __LINE__);  

   ndp = np->nu.ct->ax1;
   ndp2 = np->nu.ct->ax2;
   if (ndp->optyp == ISNUMBER)
    {
     chg_rng_isnum_to_num(np, ndp, "first array range");
    }
   if (ndp2->optyp == ISNUMBER)
    {
     chg_rng_isnum_to_num(np, ndp2, "second array range");
    }
   if (ndp->optyp != NUMBER)
    {
     __sgfterr(329,
      "wire or reg %s in module %s impossible first array range expression %s", 
      np->nsym->synam, __inst_mod->msym->synam, __msgexpr_tostr(__xs, ndp));
    }
   if (ndp2->optyp != NUMBER)
    {
     __sgfterr(329,
      "wire or reg %s in module %s impossible second array range expression %s", 
      np->nsym->synam, __inst_mod->msym->synam, __msgexpr_tostr(__xs, ndp2));
    }
   /* --- */
  }
}

/*
 * check multi-dimensional array ranges 
 * AIV 02/24/09 - this now returns TRUE if there is an error
 */
static int32 chk_wire_dma_rng(struct net_t *np)
{
 int32 i, mwid, ival, w1, w2;
 word32 *wp;
 struct mda_t *mdap;
 struct expr_t *ndp, *ndp2;
 char s1[RECLEN];
 
 mdap = np->mda;
 for (i = 0; i < mdap->dimension; i++)
  {
   sprintf(s1, "array first range of %s", np->nsym->synam);
   if (!__chkndx_expr(mdap->tab_ax1[i], s1))
    {
bad_arr:
     np->n_isarr = FALSE;
     mdap->tab_ax1[i] = NULL; 
     mdap->tab_ax2[i] = NULL; 
     return(TRUE);
    }
   wp = &(__contab[mdap->tab_ax1[i]->ru.xvi]);
   ival = (int32) wp[0];
   /* AIV 02/24/10 - LOOKATME - negative indices are allowed by LRM */
   /* but not allowing for mda wire array for now */
   if (ival < 0)
    {
     __sgferr(902, "%s value %d illegal negative number", s1, ival);
     goto bad_arr;
    }
   sprintf(s1, "array second range of %s", np->nsym->synam);
   if (mdap->tab_ax2[i] == NULL || !__chkndx_expr(mdap->tab_ax2[i], s1))
    goto bad_arr;

   wp = &(__contab[mdap->tab_ax2[i]->ru.xvi]);
   ival = (int32) wp[0];
   if (ival < 0)
    {
     __sgferr(902, "%s value %d illegal negative number", s1, ival);
     goto bad_arr;
    }

   /* allowing up to 2*24 cells (SJM 11/13/00 - comment was wrong) */
   w1 = (int32) __contab[mdap->tab_ax1[i]->ru.xvi];
   w2 = (int32) __contab[mdap->tab_ax2[i]->ru.xvi];
   mwid = ((w1 >= w2) ? (w1 - w2 + 1) : (w2 - w1 + 1));
#ifndef __CVC_RT__
   if (mwid < 0 || mwid > 0x00ffffff)
    {
     __sgfwarn(620,
      "array %s has %d cells - standard only requires maximum of %d",
      np->nsym->synam, mwid, 0x00ffffff);
    }
#endif
   /* DBG remove */
   if (mdap->tab_ax1[i] == NULL || mdap->tab_ax2[i] == NULL) 
    __misc_terr(__FILE__, __LINE__);  
   /* --- */

   ndp = mdap->tab_ax1[i];
   ndp2 = mdap->tab_ax2[i];
   if (ndp->optyp == ISNUMBER)
    {
     chg_rng_isnum_to_num(np, ndp, "first array range");
    }
   if (ndp2->optyp == ISNUMBER)
    {
     chg_rng_isnum_to_num(np, ndp2, "second array range");
    }
   if (ndp->optyp != NUMBER)
    {
     __sgfterr(329,
      "wire or reg %s in module %s impossible first array range expression %s", 
      np->nsym->synam, __inst_mod->msym->synam, __msgexpr_tostr(__xs, ndp));
     return(TRUE);
    }
   if (ndp2->optyp != NUMBER)
    {
     __sgfterr(329,
      "wire or reg %s in module %s impossible second array range expression %s", 
      np->nsym->synam, __inst_mod->msym->synam, __msgexpr_tostr(__xs, ndp2));
     return(TRUE);
    }
   /* --- */
  }
 return(FALSE);
}

/*
 * convert all same value range that is ISNUMBER to simple NUMBER
 * i.e. change expr type and check
 *
 * know first range element checked and good or will not be called
 */
static void chg_rng_isnum_to_num(struct net_t *np, struct expr_t *ndp,
 char *rngstr)
{
 int32 iti, wlen;
 word32 *wp, *wp0, *wp1;

 wlen = wlen_(ndp->szu.xclen);
 wp = &(__contab[ndp->ru.xvi]);
 wp0 = &(wp[0]);
 for (iti = 1; iti < __inst_mod->flatinum; iti++)
  {
   wp1 = &(wp[2*wlen*iti]);
   if (memcmp(wp0, wp1, 2*wlen*WRDBYTES) != 0)
    {
     __sgferr(902,
      "wire or reg %s in %s (inst. %d) %s value %s wrong - should be %s - one source instance pound param problem", 
      np->nsym->synam, __inst_mod->msym->synam, iti, rngstr,
      __msgnumexpr_tostr(__xs, ndp, 0), __msgnumexpr_tostr(__xs2, ndp, iti));
    }
  }
 /* even if error change to num - i.e. just use first */
 /* change to number easy, just use first one for all - first xvi right */
 /* and all other fields right */
 ndp->optyp = NUMBER;
 /* DBG remove --- */
 if (__debug_flg)
  {
   __dbg_msg(
    "++ %s in %s %s set by pound param to %d converted to number - all insts same\n",
    np->nsym->synam, __inst_mod->msym->synam, rngstr, wp0[0]);
  } 
 /* --- */
}

/*
 * routine to check a index style 32 bit non x/z expression
 * for declaration ranges - other routines for now for other things
 * caller must pass string for error message describing range type
 */
extern int32 __chkndx_expr(struct expr_t *ndp, char *emsg)
{
 /* must be 0 context - even though result is always 32 bits */
 __chk_rhsexpr(ndp, 0);
 /* even if errors, if number at end good returns T else F */
 if (!__nd_ndxnum(ndp, emsg, TRUE)) return(FALSE);  
 return(TRUE);
}

/*
 * check task regs
 * must be done before any statement checking
 */
extern void __chk_taskvars(struct task_t *tskp, int32 tregbasi)
{
 int32 syi, ri;
 struct sy_t *syp;
 struct net_t *rp;
 struct sy_t **syms;
 struct symtab_t *sytp;
 struct net_t *rtab;

 /* if undefined must emit error */
 syp = tskp->tsksyp;
 if (!syp->sydecl)
  {
   __gferr(776, syp->syfnam_ind, syp->sylin_cnt,
    "task or function %s not declared", syp->synam);
   return;
  }
 sytp = tskp->tsksymtab;
 /* this will also set reg ranges */
 chk_undef_syms(sytp, tskp->tsktyp);
 /* parameters (including local) checked before defparam processing */

 if (tskp->trnum == 0) return;

 /* SJM 02-09-09 - for const funcs, tab must be mallocated */
 if (tregbasi == -1)
  {
   rtab = (struct net_t *) __my_malloc(tskp->trnum*sizeof(struct net_t));
  }
 else
  {
   /* then point to right offset in module wide var table */
   rtab = &(__inst_mod->mnets[tregbasi]);
  }

 /* must now convert all task regs with ranges to constants */
 /* possible return range of function will be here */
 for (ri = 0, syi = 0, syms = sytp->stsyms; syi < (int32) sytp->numsyms; syi++)
  {
   syp = syms[syi];
   if (syp->sytyp != SYM_N) continue;
   rp = syp->el.enp;
   /* build list of task variables */
   if (rp->n_isaparam) continue;

   rtab[ri] = *rp;
   __my_free(rp, sizeof(struct net_t));
   rp = &(rtab[ri]);
   syp->el.enp = rp;
   ri++;

   /* --- DBG
   if (__debug_flg)
    {
     char s1[ECLEN], s2[RECLEN];

     __dbg_msg("--- module %s task %s linking net %s onto list\n",
      __inst_mod->msym->synam, tskp->tsksyp->synam, rp->nsym->synam); 
    }
   --- */

   /* do not need to save these, never called with previous location */
   __sfnam_ind = rp->nsym->syfnam_ind;
   __slin_cnt = rp->nsym->sylin_cnt;
   chk_wire_rng(rp);
  }
 /* still need to point to address of task's reg region in mod table */
 tskp->tsk_regs = rtab; 
}

/*
 * PORT WIDTH SETTING AND CHECKING ROUTINES
 */

/*
 * set and check module port widths
 *
 * will not get here unless all ports good
 * requires that all I/O port net widths known - param subst. and const.
 * evaluation completed.
 */
extern void __setchk_mpwidths(void)
{
 int32 pi, pnum;
 struct mod_pin_t *mpp;
 struct expr_t *mpx;

 if ((pnum = __inst_mod->mpnum) == 0) return;
 __expr_rhs_decl = TRUE;
 for (pi = 0; pi < pnum; pi++)
  {
   mpp = &(__inst_mod->mpins[pi]);
   /* location here must be port header */
   __sfnam_ind = __inst_mod->msym->syfnam_ind;
   __slin_cnt = __inst_mod->msym->sylin_cnt;

   /* as a minimum port must be legal expr. */
   mpx = mpp->mpref;

   if (mpp->mptyp == IO_OUT) __chk_rhsexpr(mpx, mpp->mpwide);
   else
    {
     __chk_lhsexpr(mpx, LHS_DECL);
     if (mpp->mptyp == IO_BID) __set_expr_onrhs(mpx);
    }

   /* updates __pr_wid to right width - on error section width assumed 1 */
   __pr_wid = 0;
   /* this does more port expr. checking and sets __pr_wid */
   chk_prtwidth(mpp->mpref, mpp);
   mpp->mpwide = __pr_wid;
  }
 __expr_rhs_decl = FALSE;
}

/*
 * set a port width - previously checked before param values known
 * pr_wid must be set to 0 before this is called
 * on error uses a subcomponent port width of 1
 */
static int32 chk_prtwidth(struct expr_t *ndp, struct mod_pin_t *mpp)
{
 struct sy_t *syp;
 struct net_t *np;

 switch (ndp->optyp) {
  case ID:
   np = ndp->lu.sy->el.enp;
   __pr_wid += ndp->szu.xclen;
   break;
  case LSB:
   syp = ndp->lu.x->lu.sy;
   np = syp->el.enp;
   if (ndp->ru.x->optyp != NUMBER && ndp->ru.x->optyp != ISNUMBER)
    {
     __gferr(778, mpp->mpfnam_ind, mpp->mplin_cnt,
      "module declaration port %s bit select index must be constant",
      np->nsym->synam);
    }
   __pr_wid++;
   break;
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   syp = ndp->lu.x->lu.sy;
   np = syp->el.enp;
   __pr_wid += ndp->szu.xclen;
   break;
  case LCB:
   /* notice legal port ref. expr. are always width self determined */
   {
    struct expr_t *ndp2;

    /* notice concatenate syntax already checked */
    for (ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
     {
      if (!chk_prtwidth(ndp2->lu.x, mpp)) return(FALSE);
     }
   }
   return(TRUE);
  case OPEMPTY:
   __pr_wid += 1;
   return(TRUE);
  default:
   __gferr(779, mpp->mpfnam_ind, mpp->mplin_cnt,
    "%s illegal in module header list of ports", __msgexpr_tostr(__xs, ndp));
   __pr_wid++;
   return(FALSE);
 }
 /* because of P1364 tran channel channel inout algorithm */ 
 /* inout ports can not be delayed wires */
 if (np->iotyp == IO_BID && np->nu.ct->n_dels_u.pdels != NULL)
  {
   __sgferr(728,
    "illegal for inout port %s to have wire delay - incompatible with P1364 tran model",
    np->nsym->synam);
  }
 return(TRUE);
}

/*
 * check shorted inouts for current module
 * notice this must be called only after port widths known
 */
extern void __chk_shorted_bids(void)
{
 int32 pi;
 int32 pnum, has_shorted;
 struct mod_pin_t *mpp;

 if ((pnum = __inst_mod->mpnum) == 0) return;
 for (has_shorted = FALSE, pi = 0; pi < pnum; pi++)
  {
   mpp = &(__inst_mod->mpins[pi]);
   /* this uses previously counted number of connected ports */
   if (!xhas_multconn_wire(mpp->mpref)) continue;

   /* emit inform for shorted that are not inouts */
   if (mpp->mptyp != IO_BID) emit_nonbid_shortwarn(mpp, mpp->mpref);
   mpp->mp_jmpered = TRUE;
   has_shorted = TRUE;
  }
 /* also emit informs for inouts */
 if (has_shorted) emit_shorted_informs(pnum);
}

/*
 * emit informs for all shorted ports - ok but good to know about
 */
static void emit_shorted_informs(int32 pnum)
{
 int32 pi;
 struct expr_t *xp2;
 struct mod_pin_t *mpp;
 struct expr_t *xp, *xp3; 
 struct net_t *np;

 for (pi = 0; pi < pnum; pi++)
  {
   mpp = &(__inst_mod->mpins[pi]);
   /* if previous error will not appear as jumpered */
   if (!mpp->mp_jmpered) continue;
   xp = mpp->mpref;
   switch (xp->optyp) { 
    case ID: np = xp->lu.sy->el.enp; break;
    case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
     np = xp->lu.x->lu.sy->el.enp; 
     break;
    case LCB:
     for (xp2 = xp->ru.x; xp2 != NULL; xp2 = xp2->ru.x)
      { 
       xp3 = xp2->lu.x;
       switch(xp3->optyp) {  
        case ID: np = xp3->lu.sy->el.enp; break;
        case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
          np = xp3->lu.x->lu.sy->el.enp; 
         break;
        default: continue;
       }
       emit_1net_shorted_informs(mpp, pi, np, pnum);
      }
     continue;
    default: continue;
   }
   emit_1net_shorted_informs(mpp, pi, np, pnum);
  }
}

/*
 * emit the shorted port informs for 1 net 
 */
static void emit_1net_shorted_informs(struct mod_pin_t *mpp,
 int32 pi, struct net_t *np, int32 pnum)
{
 int32 pi2;
 struct mod_pin_t *mpp2;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 /* have jumpered into not in any equiv. class - it is master */
 for (pi2 = pi + 1; pi2 < pnum; pi2++) 
  {
   mpp2 = &(__inst_mod->mpins[pi2]);
   /* if not jumpered to anything no need to check */
   if (!mpp2->mp_jmpered) continue;
   if (!net_in_expr(np, mpp2->mpref)) continue;

   __gfinform(454, mpp2->mpfnam_ind, mpp2->mplin_cnt,
    "%s %s in %s port %s also referenced in port %s at %s (shorted together)",
    __to_wtnam(s1, np), np->nsym->synam, __to_ptnam(s2, mpp2->mptyp),
    __to_mpnam(s3, mpp2->mpsnam), __to_mpnam(__xs2, mpp->mpsnam),
    __bld_lineloc(__xs, mpp->mpfnam_ind, mpp->mplin_cnt));
   }
}

/*
 * return T if net np is expr xp
 * return F for non lhs expr.
 */
static int32 net_in_expr(struct net_t *np, struct expr_t *xp)
{
 struct expr_t *xp2;
 struct net_t *np2;

 switch (xp->optyp) { 
  case ID:
   np2 = xp->lu.sy->el.enp;
   break;
  case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   np2 = xp->lu.x->lu.sy->el.enp;
   break;
  case LCB:
   for (xp2 = xp->ru.x; xp2 != NULL; xp2 = xp2->ru.x)
    { if (net_in_expr(np, xp2->lu.x)) return(TRUE); }
   return(FALSE);
  /* if non lhs expr (error elsewhere , just return F */
  default: return(FALSE);
 }
 return(np == np2);
}

/*
 * return T if port contains wire that connects to other port
 * notice only called for ports and not called from interactive
 * also even though not checked here if inotu shorted must be wire name
 */
static int32 xhas_multconn_wire(struct expr_t *ndp)
{
 struct expr_t *ndp2;
 struct net_t *np;

 switch (ndp->optyp) {
  case ID:
   np = ndp->lu.sy->el.enp;
chk_mult:
   if (np->nu.ct->num_prtconns == 2) return(TRUE);
   break;
  case PARTSEL: case LSB: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   np = ndp->lu.x->lu.sy->el.enp;
   goto chk_mult; 
  case LCB:
   for (ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
    { if (xhas_multconn_wire(ndp2->lu.x)) return(TRUE); }
   break;
  case OPEMPTY: break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}

/*
 * emit warn for shorted together feed thru ports that are not inouts
 */
static void emit_nonbid_shortwarn(struct mod_pin_t *mpp,
 struct expr_t *ndp)
{
 struct expr_t *ndp2;
 struct net_t *np;
 char s1[RECLEN], s2[RECLEN];

 switch (ndp->optyp) {
  case ID:
   np = ndp->lu.sy->el.enp;
chk_mult:
   if (np->iotyp != IO_BID)
    {  
     __gfinform(476, mpp->mpfnam_ind, mpp->mplin_cnt,
      "%s port %s %s %s used in merged or shorted ports - if ranges overlap probably wrong",
      __to_ptnam(s2, np->iotyp), __to_mpnam(s1, mpp->mpsnam),
      __to_wtnam(__xs, np), np->nsym->synam);
    }
   break;
  case PARTSEL: case LSB: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   np = ndp->lu.x->lu.sy->el.enp;
   goto chk_mult; 
  case LCB:
   for (ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
    emit_nonbid_shortwarn(mpp, ndp2->lu.x);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * ROUTINES TO RECONNECT SCALAR GATES/INSTS PIN LISTS
 */

/*
 * reconnect and check gates and instances according to LRM rules 
 */
extern void __reconn_gia_pins(void)
{
 struct mod_t *mdp;
 extern void __dmp_dsgn_minst(char *);

 /* DBG remove --- */
 if (__debug_flg)
  {
   __dmp_dsgn_minst("before reconnecting iarr terms");
  }
 /* ---- */

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   
   if (mdp->m_has_garrs) reconn_1mod_gateterms(mdp);
   if (mdp->m_has_iarrs) reconn_1mod_instports(mdp);
   __pop_wrkitstk();
  }
}

/*
 * reconnect array of gates ports for one module  
 * new expression put in each expanded bit of gate original free for each term
 * 
 * know module has at least one arrayed gates or not called
 *
 * SJM 04-10-21 - at this point arrays of gates expaned into multiple gates
 * but not connected - this connects
 */
static void reconn_1mod_gateterms(struct mod_t *mdp)
{
 int32 gi, gi2, pi;
 int32 giawid, bi, wid, r0;
 word32 av, bv, *wp;
 struct gia_aux_t *giap;
 struct gate_t *gp, *gp2;
 struct expr_t *xp;
 struct net_t *np;
 struct xstk_t *xsp;

 for (gi = 0; gi < mdp->mgnum;)
  {
   /* only sets for first */
   gp = &(mdp->mgates[gi]);
   /* if not array of gates, nothing to do */ 
   if ((giap = gp->g_giap) == NULL) { gi++; continue; }

   giawid = __get_gia_wide(giap);
   /* DBG remove -- */
   if (!giap->gia_is_base_first) __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* for checking each gate has original entire array terms */
   /* allocate new tab of expr ptrs for each independent of how connected */
   for (gi2 = gi; gi2 < gi + giawid; gi2++)
    {
     gp2 = &(mdp->mgates[gi2]);          
     gp2->gpins = (struct expr_t **)
      __my_malloc(gp->gpnum*sizeof(struct expr_t *));
    }

   /* handle each pin (terminal) in turn */ 
   for (pi = 0; pi < gp->gpnum; pi++)
    {
     xp = giap->giapins_ptr[pi];
     /* notice 0 context in case need to apportion */
     __chk_rhsexpr(xp, 0);

     /* FIXME - should allow global here? */
     if (__expr_has_glb(xp)) goto bad_conn_expr;

     if (xp->szu.xclen == 1)
      {
       /* exact copy expressions, this can be any expr. */
       for (gi2 = gi; gi2 < gi + giawid; gi2++)
        {
         gp2 = &(mdp->mgates[gi2]);          
         gp2->gpins[pi] = __copy_expr(xp);
        }
      }
     else if (xp->szu.xclen == giawid)
      {
       /* hard apportioning case - know now width 1 and matches */
       /* only variable, part select, concat, or constant possible */
       switch (xp->optyp) {
        case ID:
         np = xp->lu.sy->el.enp;
         if (np->n_isarr)
          {
           __gferr(699, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
           "arrayed %s gate %s terminal %d array %s illegal - not selectable",
            gp->gmsym->synam, giap->gia_base_syp->synam, pi + 1,
            __msgexpr_tostr(__xs, xp));
           goto make_unc;
          } 
         /* build bsel expression - apportion bits h to l from wire */
         /* array of gates may be stored either way but first (h) from wire */
         /* always gets first of array */
         wid = __get_netwide(np);
         for (gi2 = gi, bi = wid - 1; gi2 < gi + giawid; gi2++, bi--)
          {
           gp2 = &(mdp->mgates[gi2]);          
           gp2->gpins[pi] = bld_bsel_expr(np, bi);
          }
         break;
        case PARTSEL:
         /* for part select know internal wire h:l - generating bit selects */
         /* normalized to it and h bit connects to first, etc */ 
         wp = &(__contab[xp->ru.x->lu.x->ru.xvi]);
         r0 = (int32) wp[0];
         /* AIV 06/08/06 - was getting the net from the wrong part of xpr */
         np = xp->lu.x->lu.sy->el.enp;
         for (gi2 = gi, bi = r0; gi2 < gi + giawid; gi2++, bi--)
          {
           gp2 = &(mdp->mgates[gi2]);          
           gp2->gpins[pi] = bld_bsel_expr(np, bi);
          }
         break;
        case LCB:
         /* easy gate case - peels off 1 bit things from concat */
         /* concats always h:0 */
         if (!legal_gia_conn_concat(xp))
          {
           __gferr(699, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
            "arrayed %s gate %s terminal %d concatenate %s illegal - contains non selectable lvalue",
            gp->gmsym->synam, giap->gia_base_syp->synam, pi + 1,
            __msgexpr_tostr(__xs, xp));
           goto make_unc;
          }
         conn_1gateterm_concat(mdp, gi, xp, pi);
         break;
        case NUMBER:
         xsp = __eval_xpr(xp);

         /* DBG remove -- */
         if (xsp->xslen != giawid) __misc_terr(__FILE__, __LINE__);
         /* --- */
         /* numbers always h:0 with low bit numbered 0 */
         bi = xsp->xslen - 1;
         for (gi2 = gi; gi2 < gi + giawid; gi2++, bi--)
          {
           av = rhsbsel_(xsp->ap, bi);
           bv = rhsbsel_(xsp->bp, bi);
           gp2 = &(mdp->mgates[gi2]);          
           gp2->gpins[pi] = __bld_rng_numxpr(av, bv, 1);
           gp2->gpins[pi]->ibase = BDEC;
          }
         __pop_xstk();
         break;
        case ISNUMBER:
         /* must never see this means incorrect splitting somewhere */
         __misc_terr(__FILE__, __LINE__);
         break;
        default:
          __gferr(699, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
           "arrayed %s gate %s terminal %d expression %s illegal - not var, select, concat or number", 
          gp->gmsym->synam, giap->gia_base_syp->synam, pi + 1,
          __msgexpr_tostr(__xs, xp));
          goto make_unc;
        } 
      }
     else
      {
bad_conn_expr:
       /* error width mis-match */
       __gferr(698, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
        "arrayed %s gate %s terminal %d connection width %d illegal - must be 1 or %d",
        gp->gmsym->synam, giap->gia_base_syp->synam, pi + 1, xp->szu.xclen,
        giawid);
       /* make each unc. */
make_unc:
       /* SJM 05-07-10 - index must be gi2 */
       for (gi2 = gi; gi2 < gi + giawid; gi2++)
        {
         gp2 = &(mdp->mgates[gi2]);          
         __bld_unc_expr();
         gp2->gpins[pi] = __root_ndp;
        }
      } 
    }
   gi += giawid;
  }
}

/*
 * routine to build a constant bit select expression
 *
 * passed ndx is h:0 normalized form because later expr. checking will assume
 * value is what appeared in source, must unnormalize to what is in
 * source so will get normalized later during expr. check then output 
 * will reconvert to source - neede so caller can work only with internal h:0 
 */
static struct expr_t *bld_bsel_expr(struct net_t *np, int32 ndx)
{
 int32 ndx2;
 struct expr_t *xp, *xpid, *xpndx;

 xpid = __alloc_newxnd();
 xpid->optyp = ID; 
 xpid->lu.sy = np->nsym;
 xpid->szu.xclen = __get_netwide(np);

 ndx2 = __unnormalize_ndx(np, ndx); 
 xpndx = __bld_rng_numxpr((word32) ndx2, 0L, WBITS);
 xpndx->ibase = BDEC;
 if (ndx != ndx2) xpndx->ind_noth0 = TRUE;

 /* root of part select */
 xp = __alloc_newxnd();
 xp->optyp = LSB;
 xp->szu.xclen = 1;

 xp->lu.x = xpid;
 xp->ru.x = xpndx;
 return(xp);
}

/*
 * connect arrayed gate terms from a concat for one gate term (know 1 bit)
 *
 * notice here loop is through gate concat expression - peels off bits 1 by 1
 * and moved through instances
 */
static void conn_1gateterm_concat(struct mod_t *mdp, int32 gi,
 struct expr_t *catxp, int32 pi)
{
 int32 gi2, bi, r0, r1, nwid;
 struct expr_t *xp2, *xp3;
 word32 av, bv;
 struct gate_t *gp;
 struct net_t *np;
 struct xstk_t *xsp;

 gi2 = gi;
 for (xp2 = catxp->ru.x; xp2 != NULL; xp2 = xp2->ru.x)
  {
   xp3 = xp2->lu.x;
   switch (xp3->optyp) {
    case ID:
     np = xp3->lu.sy->el.enp;
     nwid = __get_netwide(np);
     if (np->n_isavec)
      {
       for (bi = nwid - 1; bi >= 0; gi2++, bi--)
        {
         gp = &(mdp->mgates[gi2]);          
         gp->gpins[pi] = bld_bsel_expr(np, bi);
        }
      }
     /* SJM 07/08/00 - if scalar in concatenate can't convert ot bsel */
     else
      {
       gp = &(mdp->mgates[gi2]);          
       gp->gpins[pi] = __copy_expr(xp3);
       gi2++;
      }
     break;
    case LSB:
     gp = &(mdp->mgates[gi2]);
     gp->gpins[pi] = __copy_expr(xp3);
     gi2++;
     break;
    case PARTSEL:
     /* constants here normalized h:0 and need to apportion in that order */ 
     r0 = __contab[xp3->ru.x->lu.x->ru.xvi];
     r1 = __contab[xp3->ru.x->ru.x->ru.xvi];
     /* SJM 04/13/04 - since psel must get net from left ID of psel */
     np = xp3->lu.x->lu.sy->el.enp;
     for (bi = r0; bi >= r1; gi2++, bi--)
      {
       gp = &(mdp->mgates[gi2]);          
       gp->gpins[pi] = bld_bsel_expr(np, bi);
      }
     break;
    case NUMBER:
     xsp = __eval_xpr(xp3);

     /* numbers always h:0 with low bit numbered 0 */
     bi = xsp->xslen - 1;
     for (bi = xsp->xslen - 1; bi >= 0; gi2++, bi--)
      {
       av = rhsbsel_(xsp->ap, bi);
       bv = rhsbsel_(xsp->bp, bi);
       gp = &(mdp->mgates[gi2]);          
       gp->gpins[pi] = __bld_rng_numxpr(av, bv, 1);
       gp->gpins[pi]->ibase = BDEC;
      }
     __pop_xstk(); 
     break;
    default: __case_terr(__FILE__, __LINE__);  
   }
  }
} 

/*
 * check concat connected to gate/inst - only IDs, selects, and num 
 *
 * nested concatenate illegal (maybe never can see by here)
 */
static int32 legal_gia_conn_concat(struct expr_t *xp)
{
 struct expr_t *xp2;
 struct net_t *np;

 for (xp2 = xp->ru.x; xp2 != NULL; xp2 = xp2->ru.x)
  {
   switch (xp2->lu.x->optyp) {
    case ID:
     np = xp2->lu.x->lu.sy->el.enp;
     /* array illegal if apportioning because can not be selected from */
     if (np->n_isarr) return(FALSE);
     break;
    case LSB: case PARTSEL: case NUMBER: 
    case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
     break;
    default: return(FALSE);
   }
  } 
 return(TRUE);
}

/*
 * reconnect array of instances ports for one module  
 * new expression put in each expanded bit of gate original free for each term
 * 
 * know module has at least arrayed instances or not called
 *
 * SJM 04-10-21 - at this point arrays of gates expaned into multiple gates
 * but not connected - this connects
 */
static void reconn_1mod_instports(struct mod_t *mdp)
{
 int32 ii, pi, ii2;
 int32 giawid, bi, nwlen, wid, r0;
 struct mod_pin_t *mpp;
 struct gia_aux_t *giap;
 struct mod_t *imdp;
 struct inst_t *ip, *ip2;
 struct expr_t *xp, *xp2;
 struct xstk_t *xsp, *xsp2;
 struct net_t *np;

 for (ii = 0; ii < mdp->minum;)
  {
   ip = &(mdp->minsts[ii]);
   if ((giap = ip->i_giap) == NULL) { ii++; continue; }

   giawid = __get_gia_wide(giap);
   imdp = ip->imsym->el.emdp;

   /* DBG remove -- */
   if (!giap->gia_is_base_first) __misc_terr(__FILE__, __LINE__);
   /* --- */
   for (ii2 = ii; ii2 < ii + giawid; ii2++)
    {
     ip2 = &(mdp->minsts[ii2]);          
     /* SJM 10/17/99 - empty pin list possible */
     if (imdp->mpnum == 0) ip2->ipins = NULL;
     else
      {
       ip2->ipins = (struct expr_t **)
        __my_malloc(imdp->mpnum*sizeof(struct expr_t *));
      }
    }

   /* handle each pin (terminal) in turn */ 
   for (pi = 0; pi < imdp->mpnum; pi++)
    {
     xp = giap->giapins_ptr[pi];
     mpp = &(imdp->mpins[pi]);
     /* notice 0 context in case need to apportion */
     __chk_rhsexpr(xp, 0);

     /* FIXME - should allow global here? */
     if (__expr_has_glb(xp)) goto bad_conn_expr;
     if (xp->szu.xclen == mpp->mpwide)
      {
       /* exact match copy expression, any expr. allowed */
       for (ii2 = ii; ii2 < ii + giawid; ii2++)
        {
         ip2 = &(mdp->minsts[ii2]);          
         ip2->ipins[pi] = __copy_expr(xp);
        }
      }
     /* port width times array of insts size exactly matches expr size */
     else if (xp->szu.xclen == giawid*mpp->mpwide)
      {
       /* hard apportioning case */
       /* only variable, part select, or constant possible */
       switch (xp->optyp) {
        case ID:
         np = xp->lu.sy->el.enp;
         if (np->n_isarr)
          {
           __gferr(699, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
            "arrayed %s instance %s port %d array %s illegal - not selectable",
            ip->imsym->synam, giap->gia_base_syp->synam, pi + 1,
            __msgexpr_tostr(__xs, xp));
           goto make_unc;
          } 
         wid = __get_netwide(np);
 
         /* build bsel (for scalar ports) or psel expression */
         /* 2 cases - port width 1 bit or port width >1 bits */
         if (mpp->mpwide == 1)
          {
           /* build bsel expression - apportion bits h to l from wire */
           for (ii2 = ii, bi = wid - 1; ii2 < ii + giawid; ii2++, bi--)
            {
             ip2 = &(mdp->minsts[ii2]);          
             ip2->ipins[pi] = bld_bsel_expr(np, bi);
            }
          }
         else
          {
           bi = wid - 1;
           for (ii2 = ii; ii2 < ii + giawid; ii2++, bi -= mpp->mpwide)
            {
             ip2 = &(mdp->minsts[ii2]);          
             /* build internal h:0 - on output would get unnormalized */
             ip2->ipins[pi] = bld_psel_expr(np, bi, bi - mpp->mpwide + 1);
            }
          } 
         break; 
        case PARTSEL:
         /* values normalized to h:0 wire during expr check */
         r0 = __contab[xp->ru.x->lu.x->ru.xvi];
         np = xp->lu.x->lu.sy->el.enp;
         if (mpp->mpwide == 1)
          {
           /* SJM 04/13/04 - core dumped because for loop one too many */
           /* scalar port */
           for (ii2 = ii, bi = r0; ii2 < ii + giawid; ii2++, bi--)
            {
             ip2 = &(mdp->minsts[ii2]);          
             ip2->ipins[pi] = bld_bsel_expr(np, bi);
            }
          }
         else
          {
           /* vector port */
           for (ii2 = ii, bi = r0; ii2 < ii + giawid; ii2++, bi -= mpp->mpwide)
            {
             ip2 = &(mdp->minsts[ii2]);          
             ip2->ipins[pi] = bld_psel_expr(np, bi, bi - mpp->mpwide + 1);
            }
          }
         break;
        case LCB:
         /* easy gate case - peels off 1 bit things from concat */
         /* concats always h:0 */
         if (!legal_gia_conn_concat(xp))
          {
           __gferr(699, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
            "arrayed %s instance %s port %d concatenate %s illegal - contains non selectable lvalue",
            ip->imsym->synam, giap->gia_base_syp->synam, pi + 1,
            __msgexpr_tostr(__xs, xp));
           goto make_unc;
          }
         conn_1instport_concat(mdp, ii, giap, xp, pi, mpp->mpwide);
         break;
        case NUMBER:
         __push_wrkitstk(mdp, 0);
         xsp = __eval_xpr(xp);
         __pop_wrkitstk();
         push_xstk_(xsp2, mpp->mpwide); 

         bi = xsp->xslen - 1;
         for (ii2 = ii; ii2 < ii + giawid; ii2++, bi -= mpp->mpwide)
          {
           /* could improve scalar case by using rhs bsel but this works */
           __rhspsel(xsp2->ap, xsp->ap, bi, mpp->mpwide);
           __rhspsel(xsp2->bp, xsp->bp, bi, mpp->mpwide);

           /* must allocate and fill because may be wider than WBITS */
           xp2 = __alloc_newxnd();
           xp2->optyp = NUMBER;
           nwlen = wlen_(mpp->mpwide); 
           if (mpp->mpwide <= WBITS)
            {
             xp2->ru.xvi = __alloc_shareable_cval(xsp2->ap[0], xsp2->ap[1],
              mpp->mpwide);
            }
           else
            {
             /* each a and b part of constants fits in integral no. words */
             xp2->ru.xvi = __allocfill_cval_new(xsp->ap, xsp->bp, nwlen);
            }
           xp2->szu.xclen = mpp->mpwide;

           ip2 = &(mdp->minsts[ii2]);          
           ip2->ipins[pi] = xp2;
          }
         __pop_xstk(); 
         __pop_xstk();
         break;
        case ISNUMBER:
         /* if this is seen bad splitting somewhere */ 
         __misc_terr(__FILE__, __LINE__);
         break;
        default:
         __gferr(699, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
          "arrayed %s instance %s port %d expression %s illegal - must be var, select, concat, or number", 
          ip->imsym->synam, giap->gia_base_syp->synam, pi + 1,
          __msgexpr_tostr(__xs, xp));
         goto make_unc;
        } 
      }
     else
      {
bad_conn_expr:
       /* error width mis-match */
       __gferr(698, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
        "arrayed %s instance %s port %d connection width %d illegal - must be %d or %d",
        ip->imsym->synam, giap->gia_base_syp->synam, pi + 1, xp->szu.xclen,
        mpp->mpwide, mpp->mpwide*giawid);
 
       /* make each unc. */
make_unc:
       for (ii2 = ii; ii2 < ii + giawid; ii2++)
        {
         ip2 = &(mdp->minsts[ii2]);          
         __bld_unc_expr();
         ip2->ipins[pi] = __root_ndp;
        }
      } 
    }
   ii += giawid;
  }
}

/*
 * routine to build a constant part select expression
 *
 * passed i1/i2 are h:0 normalized form because later expr. check will assume
 * value is what appeared in source, must actually normalize to what is in
 * source so will get unnormalized later during expr. check then output 
 * will reconvert to source - neede so caller can work only with internal h:0 
 */
static struct expr_t *bld_psel_expr(struct net_t *np, int32 i1, int32 i2)
{
 int32 ndx1, ndx2;
 struct expr_t *xp, *xpid, *xp1, *xp2, *xpcol;

 xpid = __alloc_newxnd();
 xpid->optyp = ID; 
 xpid->szu.xclen = __get_netwide(np);
 xpid->lu.sy = np->nsym;

 ndx1 = __unnormalize_ndx(np, i1); 
 xp1 = __bld_rng_numxpr((word32) ndx1, 0L, WBITS);
 xp1->ibase = BDEC;
 if (i1 != ndx1) xp1->ind_noth0 = TRUE;

 ndx2 = __unnormalize_ndx(np, i2); 
 xp2 = __bld_rng_numxpr((word32) ndx2, 0L, WBITS);
 xp2->ibase = BDEC;
 if (i2 != ndx2) xp1->ind_noth0 = TRUE;

 /* root of part select */
 xp = __alloc_newxnd();
 xp->optyp = PARTSEL;
 xp->szu.xclen = i1 - i2 + 1;
 xp->lu.x = xpid;
 xpcol = __alloc_newxnd();
 xpcol->optyp = COLON;
 xp->ru.x = xpcol;
 xpcol->lu.x = xp1;
 xpcol->ru.x = xp2;
 return(xp);
}

/*
 * connect arrayed inst port highconns from a concat for one non scalar port
 *
 * know width of concat is mpwid*(num insts)
 * tricky because may need to build new concats when concat exprs overlap
 * by here know all concatenates converted to one level
 *
 * concat width exactly matches width times inst array size (can't fail)
 * concat components already checked 
 */
static void conn_1instport_concat(struct mod_t *mdp, int32 ii,
 struct gia_aux_t *giap, struct expr_t *catxp, int32 pi, int32 mpwid)
{
 int32 ii2, giawid, cwidmore;
 struct exprlst_t *xplp;
 struct exprlst_t *xplphd, *last_xplp;
 struct expr_t *xp2, *catxp2, *last_catxp;
 struct inst_t *ip;

 giawid = __get_gia_wide(giap);
 /* this copies elements into list - need to leave concat since part of */
 /* original expr that stays in giap */
 xplphd = splt_icat_align_xlist(catxp, mpwid);
 xplp = xplphd;
 for (ii2 = ii; ii2 < ii + giawid; ii2++)
  {
   ip = &(mdp->minsts[ii2]);          
   /* cat element can never be too wide */
   /* DBG remove --- */
   if (xplp->xp->szu.xclen > mpwid) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* case 1: element of concat exactly matches one inst port width */ 
   if (xplp->xp->szu.xclen == mpwid) 
    {
     ip->ipins[pi] = xplp->xp;
     xplp = xplp->xpnxt;
     continue;
    }
   /* case 2: concatenate combined from elements of array concat needed */
   catxp2 = __alloc_newxnd();
   catxp2->optyp = LCB; 
   catxp2->szu.xclen = mpwid;
   cwidmore = mpwid;
   for (last_catxp = NULL;;)
    {
     xp2 = __alloc_newxnd();
     xp2->optyp = CATCOM;
     if (last_catxp == NULL) catxp2->ru.x = xp2; else last_catxp->ru.x = xp2;
     last_catxp = xp2;

     /* CAT COM len is distant from high bit to low bit (right end) */ 
     xp2->szu.xclen = cwidmore;
     xp2->lu.x = xplp->xp;
     cwidmore -= xp2->lu.x->szu.xclen;
     if (cwidmore == 0) break;
     xplp = xplp->xpnxt;
     /* DBG remove --- */
     if (xplp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
    }
   ip->ipins[pi] = catxp2;
   xplp = xplp->xpnxt;
  }
 /* DBG remove --- */
 if (xplp != NULL) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 /* need to free concat expr list (but not expressions that are used) */
 for (xplp = xplphd; xplp != NULL;)
  {
   last_xplp = xplp->xpnxt;
   __my_free(xplp, sizeof(struct exprlst_t));
   xplp = last_xplp;
  }
}
   
/*
 * build expression list with any overlaps eliminated
 *
 * when done all expressions copied (so can just conn to insts) and
 * never overlaps (may need to build concats but never a need to split)
 */
static struct exprlst_t *splt_icat_align_xlist(struct expr_t *catxp,
 int32 mpwid)
{
 int32 prtbi, cxlen, r1, endlen, overlaplen;
 word32 *wp;
 struct expr_t *xp2, *xp3;
 struct exprlst_t *xplphd, *xplp, *xplp_last;
 struct net_t *np;
 struct xstk_t *xsp, *xsp2;

 xsp = NULL;
 xplphd = xplp_last = NULL;
 /* work one by one thru elements of concatenate */
 for (prtbi = 0, xp2 = catxp->ru.x; xp2 != NULL; xp2 = xp2->ru.x)
  {
   xp3 = xp2->lu.x;
   cxlen = xp3->szu.xclen;
   /* case 1: entire expr connects to current instance */
   if (prtbi + cxlen <= mpwid)   
    {
     xplp = __alloc_xprlst();
     xplp->xp = __copy_expr(xp3);
     if (xplphd == NULL) xplphd = xplp; else xplp_last->xpnxt = xplp;
     xplp_last = xplp; 
     prtbi += cxlen;
     if (prtbi == mpwid) prtbi = 0;
     continue;
    }
   /* case 2: hard need to split expr because element crosses inst. */
   /* prtbi + cxlen wider than mpwid */
   endlen = mpwid - prtbi;
   overlaplen = cxlen - endlen;
   /* if number, must compute value for use below */
   if (xp3->optyp == NUMBER)
    {
     xsp = __eval_xpr(xp3);
    }
   /* build expr. list element for high bits of expr overlapping inst */
   xplp = __alloc_xprlst();
   if (xplphd == NULL) xplphd = xplp; else xplp_last->xpnxt = xplp;
   xplp_last = xplp; 
   switch (xp3->optyp) {
    case ID:
     np = xp3->lu.sy->el.enp;
     r1 = cxlen - 1;
     /* SJM 07/08/00 - if scalar in concatenate can't convert ot bsel */
     if (!np->n_isavec) 
      {
       xplp->xp = __copy_expr(xp3);
       break;
      }
     goto bld_select; 
    case PARTSEL:
     np = xp3->lu.x->lu.sy->el.enp;
     wp = &(__contab[xp3->ru.x->lu.x->ru.xvi]);
     r1 = (int32) wp[0];

bld_select:
     /* split off first part that will then fill to end */
     if (endlen == 1) xplp->xp = bld_bsel_expr(np, r1);
     else xplp->xp = bld_psel_expr(np, r1, r1 - endlen + 1);
     break;
    case NUMBER:
     /* make work xsp big enough for both */
     push_xstk_(xsp2, endlen); 
     /* split off high part of number for first, new part for overlap */
     /* 3rd argument is length not low end */
     __rhspsel(xsp2->ap, xsp->ap, cxlen - 1, endlen);
     __rhspsel(xsp2->bp, xsp->bp, cxlen - 1, endlen); 
     xplp->xp = bld_num_expr(xsp2);
     __pop_xstk();
     break;
     /* bit select impossible because always fits */
    default: __case_terr(__FILE__, __LINE__);
   }
   if (overlaplen > mpwid)
    {
     /* case 2a: overlap continues for more than one inst */
     for (;;) 
      {
       xplp = __alloc_xprlst();
       if (xplphd == NULL) xplphd = xplp; else xplp_last->xpnxt = xplp;
       xplp_last = xplp; 
       switch (xp3->optyp) {
        case ID:
         np = xp3->lu.sy->el.enp;
         /* SJM 07/08/00 - if scalar in concatenate can't convert ot bsel */
         if (!np->n_isavec) 
          {
           xplp->xp = __copy_expr(xp3);
           break;
          }
         r1 = overlaplen - 1;
         goto bld2_selects;
        case PARTSEL:
         np = xp3->lu.x->lu.sy->el.enp;
         /* here need right range end */
         wp = &(__contab[xp3->ru.x->ru.x->ru.xvi]);
         r1 = (int32) wp[0] + overlaplen - 1;
bld2_selects:
         if (mpwid == 1) xplp->xp = bld_bsel_expr(np, r1);
         else xplp->xp = bld_psel_expr(np, r1, r1 - mpwid + 1);
         break;
        case NUMBER:
         /* make work xsp big enough for both */
         push_xstk_(xsp2, mpwid); 
         __rhspsel(xsp2->ap, xsp->ap, overlaplen - 1, mpwid);
         __rhspsel(xsp2->bp, xsp->bp, overlaplen - 1, mpwid);
         /* must allocate and fill because may be wider than WBITS */
         xplp->xp = bld_num_expr(xsp2);
         __pop_xstk();
         break;
        /* bit select impossible because always fits */
        default: __case_terr(__FILE__, __LINE__);
       }
       overlaplen -= mpwid;
       /* DBG remove --- */
       if (overlaplen < 0) __misc_terr(__FILE__, __LINE__);  
       /* ---*/
       if (overlaplen == 0) goto nxt_catel;
       if (overlaplen < mpwid) break;   
       /* if corrected overlap length equal to or wider than port continue */
      }
    }
   /* final or only end part (if narrower than mpwid) */
   xplp = __alloc_xprlst();
   if (xplphd == NULL) xplphd = xplp; else xplp_last->xpnxt = xplp;
   xplp_last = xplp; 
   switch (xp3->optyp) {
    case ID:
     np = xp3->lu.sy->el.enp;
     /* SJM 07/08/00 - if scalar in concatenate can't convert ot bsel */
     if (!np->n_isavec) 
      {
       xplp->xp = __copy_expr(xp3);
       break;
      }
     r1 = overlaplen - 1; 
     goto bld3_selects; 
    case PARTSEL:
     np = xp3->lu.x->lu.sy->el.enp;
     /* here need right range end */
     wp = &(__contab[xp3->ru.x->ru.x->ru.xvi]);
     r1 = (int32) wp[0] + overlaplen - 1;
bld3_selects:
     /* split off first part that will then fill to end */
     if (overlaplen == 1) xplp->xp = bld_bsel_expr(np, r1);
     else xplp->xp = bld_psel_expr(np, r1, r1 - overlaplen + 1);
     break;
    case NUMBER:
     /* make work xsp big enough for both */
     push_xstk_(xsp2, overlaplen); 
     __rhspsel(xsp2->ap, xsp->ap, overlaplen - 1, overlaplen);
     __rhspsel(xsp2->bp, xsp->bp, overlaplen - 1, overlaplen);
     xplp->xp = bld_num_expr(xsp2);
     __pop_xstk();
     break;
    /* bit select impossible because always fits */
    default: __case_terr(__FILE__, __LINE__);
   }
nxt_catel:
   if (xp3->optyp == NUMBER) __pop_xstk();
  }
 return(xplphd);
}

/*
 * build a new number expression from a expression stack element
 */
static struct expr_t *bld_num_expr(struct xstk_t *xsp)
{
 int32 nwlen;
 struct expr_t *xp;

 xp = __alloc_newxnd();
 xp->optyp = NUMBER;
 xp->szu.xclen = xsp->xslen;
 /* AIV 08/11/10 - need to mark as constant expresion for new compiler */ 
 /* 2state code handling */
 xp->consubxpr = TRUE;
 nwlen = wlen_(xsp->xslen); 
 if (xsp->xslen <= WBITS)
  {
   xp->ru.xvi = __alloc_shareable_cval(xsp->ap[0], xsp->ap[1], xsp->xslen);
  }
 else
  {
   xp->ru.xvi = __allocfill_cval_new(xsp->ap, xsp->bp, nwlen);
  }
 return(xp);
}

/*
 * ROUTINES TO RESET AS FIXUP MODULE PORT STRENGTHS AFTER PORT EXPANDING 
 */

/*
 * set module port strength expression bits
 *
 * needed because must check expressions to set widths before apportioning
 * I/O ports to iconns, but can not propagate strengths until apportioning
 * done, so now must go back and set expr x_stren bit if module port
 * exprs contains stren wires, all other expressions checked after stren
 * propagation so only need to fix up for module ports
 */
extern void __reset_modport_strens(void)
{
 int32 pi, pnum;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* SJM 12/26/02 - this was wrong - not marking all port strens so */
   /* iop gen wasn't working */
   if ((pnum = mdp->mpnum) == 0) continue;

   for (pi = 0; pi < pnum; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     set_1mpx_stren(mpp->mpref);
    }
  }
}

/*
 * set expr. strength bits for module port exprs with strength wires
 *
 * used recursively on subexprs of ports exprs (not iconn exprs)
 */
static void set_1mpx_stren(struct expr_t *mpx)
{
 int32 cat_stren;
 struct net_t *np;
 struct sy_t *syp;

 switch (mpx->optyp) {
  case ID: case GLBREF:
   np = mpx->lu.sy->el.enp;
   if (np->n_stren) mpx->x_stren = TRUE;
   break;
  case NUMBER: case ISNUMBER: case OPEMPTY: case REALNUM: case ISREALNUM:
   break;
  case LSB:
   syp = mpx->lu.x->lu.sy;
   np = syp->el.enp;
   if (np->n_stren) mpx->x_stren = TRUE;
   set_1mpx_stren(mpx->ru.x);
   break;
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   syp = mpx->lu.x->lu.sy;
   np = syp->el.enp;
   if (np->n_stren) mpx->x_stren = TRUE;
   set_1mpx_stren(mpx->ru.x->lu.x);
   set_1mpx_stren(mpx->ru.x->ru.x);
   break;
  case QUEST:
   set_1mpx_stren(mpx->lu.x);
   set_1mpx_stren(mpx->ru.x->ru.x);
   set_1mpx_stren(mpx->ru.x->lu.x);
   break;
  case FCALL: return;
  case LCB:
   {
    struct expr_t *ndp2;
    struct expr_t *catxp;

    /* know concatenates never nested by here */
    for (cat_stren = FALSE, ndp2 = mpx->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
     {
      catxp = ndp2->lu.x;
      set_1mpx_stren(catxp);
      if (catxp->x_stren) { ndp2->x_stren = TRUE; cat_stren = TRUE; }
     }
    if (cat_stren) mpx->x_stren = TRUE;
   }
   break;
  default:
   if (mpx->lu.x != NULL) set_1mpx_stren(mpx->lu.x);
   if (mpx->ru.x != NULL) set_1mpx_stren(mpx->ru.x);
 }
}

/*
 * MODULE COMPONENT SEMANTIC CHECKING ROUTINES
 */

/*
 * check module - also call procedure checking routines
 * does the following:
 *  1) global refs. hanged to ids
 *  2) constant expr. folded and node widths set
 *
 * notice all code called from here requires __inst_mod to be set for
 * finding size of IS form parmeters that are converted to constants here
 */
extern void __chk_mod(void)
{
 struct task_t *tskp;

 /* check inst. conns. and gates */
 chk_inst_conns();
 chk_gates();
 chk_contas();

 /* SJM 09/30/04 - although variable assign initialize decls require */
 /* constant rhs expr, not checking the expression until here */ 
 /* because semantics is same as decl followed by initial [var] = [expr]; */
 chk_varinits();
 
 /* finally check user tasks and function statements */
 for (tskp = __inst_mod->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   switch (tskp->tsktyp) { 
    case FUNCTION:
     /* named blocks checked in context */
     __chk_funcdef(tskp);
     tskp->thas_tskcall = FALSE;
     break;
    case TASK:
     chk_1tsk(tskp);
     break;
    /* named block task checked when statement seen */
    case Begin: case FORK: break;
    default: __case_terr(__FILE__, __LINE__); 
   }
  }
 /* AIV 02/19/09 - these must now be done after setting tskp->uses_scope */
 /* check init/always statements */
 chk_stmts();
}
    
extern void __chk_task_thread_needed(struct mod_t *mdp)
{
 struct task_t *tskp;

 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   /* AIV 05/17/10 - these need to be reset upon every setting */
   __task_has_delay = FALSE;
   __task_has_xmrcall = FALSE;
   /* AIV 09/07/11 - need to also mark if any of the tasks called tasks */
   /* can be disabled this needs to also be marked as a disabled task */
   __task_has_disable = FALSE;
   if (tskp->no_delay)
    {
     check_task_has_delay(tskp);
     tskp->no_delay = !__task_has_delay;
    }
   if (tskp->no_xmrcall)
    {
     check_task_has_xmrcall(tskp);
     tskp->no_xmrcall = !__task_has_xmrcall;
    }
   if (!tskp->can_be_disabled)
    {
     check_task_has_disable(tskp);
     tskp->can_be_disabled = __task_has_disable;
    }
  }
 __task_has_delay = FALSE;
 __task_has_xmrcall = FALSE;
 __task_has_disable = FALSE;
}


static void check_task_has_delay(struct task_t *tskp)
{
 struct task_t *called_tskp;
 int32 i;

 for (i = 0; ; i++)
  {
   called_tskp = tskp->called_tasks[i];
   if (called_tskp == NULL) return;
   if (!called_tskp->no_delay) 
    {
     __task_has_delay = TRUE;
     return;
    }
   else check_task_has_delay(called_tskp);
  }
}

static void check_task_has_xmrcall(struct task_t *tskp)
{
 struct task_t *called_tskp;
 int32 i;

 for (i = 0; ; i++)
  {
   called_tskp = tskp->called_tasks[i];
   if (called_tskp == NULL) return;
   if (!called_tskp->no_xmrcall) 
    {
     __task_has_xmrcall = TRUE;
     return;
    }
   else check_task_has_xmrcall(called_tskp);
  }
}

static void check_task_has_disable(struct task_t *tskp)
{
 struct task_t *called_tskp;
 int32 i;

 for (i = 0; ; i++)
  {
   called_tskp = tskp->called_tasks[i];
   if (called_tskp == NULL) return;
   if (called_tskp->can_be_disabled) 
    {
     __task_has_disable = TRUE;
     return;
    }
   else check_task_has_disable(called_tskp);
  }
}

/*
 * check 1 task
 * notice this is task definition so cannot be called from iact
 */
static void chk_1tsk(struct task_t *tskp)
{
 struct task_pin_t *tpp;
 int32 ai;
 struct net_t *np;
 struct sy_t *syp;

 /* if DPI task - use new separate checking routine */
 if (tskp->tf_dpip != NULL)
  {
   __chk_1tsk_dpi(tskp);
   return;
  }

 __cur_tsk = tskp;
 /* variables checked, chk statements & look for non thread optimizations */
 for (ai = 1, tpp = tskp->tskpins; tpp != NULL; tpp = tpp->tpnxt, ai++)
  {
   np = tpp->tpsy->el.enp;
   /* SJM 01/14/1999 - arrays illegal formal function arguments */
   /* now allowing passing entire array to DPI routine */
   if (np->n_isarr)
    {
     syp = tpp->tpsy;
     __gferr(869, syp->syfnam_ind, syp->sylin_cnt,
      "task %s definition entire array formal argument %s (pos. %d) illegal - must be simple variable",
      tskp->tsksyp->synam, syp->synam, ai);
     continue;
    }

   /* notice task ports must be regs so no need to set 2nd on lhs */
   if (tpp->trtyp != IO_IN)
    {
     if (np->nrngrep == NX_CT)
      {
       if (tpp->trtyp == IO_BID) np->nu.ct->n_onlhs = TRUE;
       np->nu.ct->n_onrhs = TRUE;
      }
     tskp->thas_outs = TRUE;
    }
   else if (np->nrngrep == NX_CT) np->nu.ct->n_onlhs = TRUE;
  }
 __disp_uses_scope = FALSE;
 /* notice that task can take any legal variables no argument */
 /* requirements - this finds any named block no delay cases */
 __chk_lstofsts(tskp->tskst);

 /* finally do checking to determine if 0 delay or has task call */ 
 __task_has_delay = FALSE;
 __task_has_tskcall = FALSE;
 __task_has_xmrcall = FALSE;
 __nbsti = -1;
 __chk_nodel_lstofsts(tskp->tskst);
 /* AIV 05/28/07 - set task delay bit */
 tskp->no_delay = !__task_has_delay;
 /* AIV 04/12/10 - if task does not contain a delay there is no reason */
 /* for it to be automatic - turn off flag */
 /* AIV LOOKATME - pretty sure this is correct ???? */
 if (tskp->no_delay && !__task_has_tskcall) tskp->is_auto = FALSE;
 tskp->uses_scope = __disp_uses_scope;
 tskp->no_xmrcall = !__task_has_xmrcall;
 __disp_uses_scope = FALSE;
 __cur_tsk = NULL;
}

/*
 * check module instance connections
 * expression here can be numbers with IS form so need to check
 * all instances in that case
 * this frees cell_pin_t since not used after here
 */
static void chk_inst_conns(void)
{
 int32 pi, ii, iotyp, sav_enum, pnum, pwid;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct mod_t *imdp;
 struct expr_t *pxp;
 struct srcloc_t *slocp;
 struct net_t *np;

 __expr_rhs_decl = TRUE;
 for (ii = 0; ii < __inst_mod->minum; ii++)
  {
   ip = &(__inst_mod->minsts[ii]);
   imdp = ip->imsym->el.emdp;
   if ((pnum = imdp->mpnum) == 0) continue;
   slocp = __inst_mod->iploctab[ii];

   for (pi = 0; pi < pnum; pi++)
    {
     mpp = &(imdp->mpins[pi]);
     pxp = ip->ipins[pi];
     __sfnam_ind = slocp[pi].sl_fnam_ind;
     __slin_cnt = slocp[pi].sl_lin_cnt;

     /* this should always be at least OPEMPTY by here */
     /* change to special unc. indicator and check/fix here */
     /* instance one port missing 'bx for unconnect */
     /* DBG remove --- */
     if (pxp == NULL) __misc_sgfterr(__FILE__, __LINE__);
     /* --- */

     /* module port iconn cannot have real connection */
     if (pxp->is_real)
      __sgferr(780,
       "instance %s port %s (pos. %d) illegally connects to real number",
       ip->isym->synam, __msgexpr_tostr(__xs, pxp), pi + 1);

     /* cannot be xmr that references down into same inst. */
     sav_enum = __pv_err_cnt;
     chk_iconn_downxmr(ip, pxp);
     if (sav_enum < __pv_err_cnt) continue;

     pwid = mpp->mpwide;
     /* if first time implicitly declared wire used change to port width */
     /* if first use if as scalar and later other must still fix here */
     if (pxp->optyp == ID)
      {
       /* SJM 03/15/00 - must catch passing non wire ID as error */
       if (pxp->lu.sy->sytyp != SYM_N)
        {
         __sgferr(789, "instance %s port pos. %d illegally connects to %s %s",
          ip->isym->synam, pi + 1, __to_sytyp(__xs, pxp->lu.sy->sytyp),
          __msgexpr_tostr(__xs2, pxp));
         continue;
        }
       np = pxp->lu.sy->el.enp;
       if (np->nu.ct->n_impldecl && !np->nu.ct->n_rngknown)
        {
         /* change to vectored wire with same direction range as port */ 
         if (pwid > 1)
          {
           np->nu.ct->nx1 = __bld_rng_numxpr((word32) (pwid - 1), 0L, WBITS);
           np->nu.ct->nx2 = __bld_rng_numxpr(0L, 0L, WBITS);
           np->n_isavec = TRUE;
           np->nwid = pwid;
           /* vectored/scalared set to default scalared state at prep time */
           __sgfinform(472, 
            "implicitly declared %s %s width changed to %d to match port width",
            __to_wtnam(__xs, np), np->nsym->synam, pwid);
          }
         np->nu.ct->n_rngknown = TRUE;  
         __chg_rng_direct = TRUE;
        }
      }

     iotyp = mpp->mptyp;
     if (iotyp == IO_IN)
      {
       /* fix unc. drive to special type of constant */
       if (pxp->optyp == OPEMPTY)
        {
         pxp->szu.xclen = pwid;
         /* change node type so will eval. to right value */
         if (pxp->unc_pull != NO_UNCPULL) pxp->optyp = UNCONNPULL; 

         __sgfinform(473,
          "instance %s input port %s (pos. %d) width %d unconnected",
          ip->isym->synam, __to_mpnam(__xs, mpp->mpsnam), pi + 1, pwid);

         continue;
        }
       /* notice for IS forms checks each */
       __chk_rhsexpr(pxp, pwid);
      }
     else
      {
       /* either output or inout */
       /* make OPEMPTY not unconn. drive strength form */
       if (pxp->optyp == OPEMPTY)
        {
         pxp->szu.xclen = pwid;
         if (pxp->x_stren) { pxp->x_stren = FALSE; pxp->ru.xvi = -1; }
         if (mpp->mptyp == IO_BID && !mpp->mp_jmpered)
          {
           __sgfinform(473,
            "instance %s inout port %s (pos. %d) width %d unconnected",
            ip->isym->synam, __to_mpnam(__xs, mpp->mpsnam), pi + 1, pwid);
          }
         /* already emitted special case inout unc. - not jumpered, etc. */
         /* 11/06/00 SJM - to match XL emit inform for every unc. port */ 
         if (mpp->mptyp != IO_BID)
          {
           __sgfinform(473,
            "instance %s output port %s (pos. %d) width %d unconnected",
            ip->isym->synam, __to_mpnam(__xs, mpp->mpsnam), pi + 1, pwid);
          }
         continue;
        }
       pxp->szu.xclen = pwid;
       __chk_lhsexpr(pxp, LHS_DECL);
       /* inout is also rhs expression */
       if (iotyp == IO_BID) __set_expr_onrhs(pxp);
      }
     /* if error in expr., do not emit size warning */
     if (sav_enum < __pv_err_cnt) continue;

     /* check port width mismatch */
     if (pxp->szu.xclen != pwid)
      {
#ifndef __CVC_RT__
       char s2[20], s3[RECLEN];
       __sgfwarn(602,
        "%s(%s) %s port %s (line %s) width %d mismatch with %s width %d", 
        ip->isym->synam, ip->imsym->synam, __to_ptnam(s2, mpp->mptyp),  
        __to_mpnam(s3, mpp->mpsnam), __bld_lineloc(__xs, mpp->mpfnam_ind,
        mpp->mplin_cnt), pwid, __msgexpr_tostr(__xs2, pxp), pxp->szu.xclen);
#endif
      }

     /* check same wire directions - if either concat do not check */
     /* know now both mod and inst port exprs checked */
     chk_iconn_mixeddirrng(ip, mpp, pxp);
     /* SJM - 10/08/99 - always turn off impl decl change dir since */ 
     /* if implicit scalar will not go through reverse code */
     __chg_rng_direct = FALSE;
    }
  }
 __expr_rhs_decl = FALSE;
}

/*
 * for inout I/O port expr. must set both rhs bits
 */
extern void __set_expr_onrhs(struct expr_t *ndp)  
{
 struct net_t *np;
 struct expr_t *xp2;

 if (__isleaf(ndp))
  {
   if (ndp->optyp == ID || ndp->optyp == GLBREF)
    {
     np = ndp->lu.sy->el.enp;
     if (np->nrngrep == NX_CT)
      {
       if (np->iotyp == NON_IO) np->nu.ct->n_onrhs = TRUE;
      }
     if (!__expr_rhs_decl) np->n_onprocrhs = TRUE;
    }
   return;
  }
 for (xp2 = ndp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   __set_expr_onrhs(xp2);
  }

 if (ndp->lu.x != NULL) __set_expr_onrhs(ndp->lu.x);
 if (ndp->ru.x != NULL) __set_expr_onrhs(ndp->ru.x);
}

/*
 * check for all xmrs in expr. and emit error if xmr into instance
 * know expr. is instance connection
 */
static void chk_iconn_downxmr(struct inst_t *ip, struct expr_t *ndp)
{
 int32 pthi;
 struct sy_t *syp;
 struct expr_t *xp2;

 if (__isleaf(ndp))
  {
   if (ndp->optyp == GLBREF)
    {
     struct gref_t *grp;

     grp = ndp->ru.grp;
     if (grp->upwards_rel || grp->gr_gone || grp->gr_err) return;
     for (pthi = 0; pthi <= grp->last_gri; pthi++)
      {
       syp = grp->grcmps[pthi];
       if (syp == ip->isym)
        {
         __sgferr(788,
          "in module %s: instance %s port list contains hierarchical reference %s into same instance",
          __inst_mod->msym->synam, ip->isym->synam, grp->gnam);
        }
      }
    }
   return;
  }
 for (xp2 = ndp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   chk_iconn_downxmr(ip, xp2);
  }

 if (ndp->lu.x != NULL) chk_iconn_downxmr(ip, ndp->lu.x);
 if (ndp->ru.x != NULL) chk_iconn_downxmr(ip, ndp->ru.x);
}

/*
 * check for mixed direction range instance 
 */
static void chk_iconn_mixeddirrng(struct inst_t *ip,
 struct mod_pin_t *mpp, struct expr_t *ipxp)
{
 int32 one_is_bsel, porthl, iphl, tmp;
 int32 portr1, portr2, ipr1, ipr2;
 struct net_t *portnp, *ipnp;
 char porthls[20], iphls[20];

 /* only check for both psel, id or global, if either bsel, 1 inform */
 one_is_bsel = FALSE;
 switch (mpp->mpref->optyp) { 
  case ID: case GLBREF: portnp = mpp->mpref->lu.sy->el.enp; break;
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
get_portsel_np:
   portnp = mpp->mpref->lu.x->lu.sy->el.enp;
   break;
  case LSB:
   one_is_bsel = TRUE;
   goto get_portsel_np;
  default: return;
 }
 if (!portnp->n_isavec) return;
 switch (ipxp->optyp) { 
  case ID: case GLBREF: ipnp = ipxp->lu.sy->el.enp; break;
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
get_ipsel_np:
   ipnp = ipxp->lu.x->lu.sy->el.enp;
   break;
  case LSB:
   one_is_bsel = TRUE;
   goto get_ipsel_np;
  default: return;
 }
 if (!ipnp->n_isavec) return;
 __getwir_range(portnp, &portr1, &portr2);
 __getwir_range(ipnp, &ipr1, &ipr2);

 /* if either is 1 bit range, no warn/inform */ 
 if (portr1 == portr2 || ipr1 == ipr2) return;

 /* here if this is implicitly declared from inst. conn. wire, just fix */
 if (__chg_rng_direct)
  {
   /* if port really low high, reverse range */
   if (portr1 < portr2)
    {
     /* only need to reverse con tab pointers */
     tmp = ipnp->nu.ct->nx1->ru.xvi;
     ipnp->nu.ct->nx1->ru.xvi = ipnp->nu.ct->nx2->ru.xvi;
     ipnp->nu.ct->nx2->ru.xvi = tmp;
    }
   __chg_rng_direct = FALSE;
   return;  
  }

 if (portr1 >= portr2)
  { porthl = TRUE; strcpy(porthls, "high to low"); }
 else { porthl = FALSE; strcpy(porthls, "low to high"); }
 if (ipr1 >= ipr2)
  { iphl = TRUE; strcpy(iphls, "high to low"); }
 else { iphl = FALSE; strcpy(iphls, "low to high"); }
 
 if (porthl != iphl)
  {
   char s1[2*IDLEN], s2[20];

   sprintf(s1, "%s [%d:%d] %s at %s",
    __to_ptnam(s2, mpp->mptyp), portr1, portr2, portnp->nsym->synam,
    __bld_lineloc(__xs, mpp->mpfnam_ind, mpp->mplin_cnt));
#ifndef __CVC_RT__
   if (one_is_bsel)
    {
     __sgfinform(412,
      "type %s instance %s range [%d:%d] direction mismatch with %s",
      ip->imsym->synam, ip->isym->synam, ipr1, ipr2, s1);
    }
   else
    {
     __sgfwarn(556,
      "type %s instance %s range [%d:%d] direction mismatch with %s",
      ip->imsym->synam, ip->isym->synam, ipr1, ipr2, s1);
    }
#endif
  }
}

/*
 * free module port line no.s for one module if not already freed
 * for split all will share so only one needs to be freed
 *
 * SJM 07-14-07 - need to copy iploc tabs when splitting (copying) mods
 * therefore must always free an iploc tab
 * SJM 04-21-10 - for expanded arrays of insts, all shared only first freed
 */
extern void __free_icptab(void)
{
 int32 ii, pnum;
 struct srcloc_t *iplocs;
 struct inst_t *ip;
 struct mod_t *imdp;

 /* DBG remove -- */
 if (__inst_mod->minum > 0 && __inst_mod->iploctab == NULL)
  __misc_terr(__FILE__, __LINE__);
 if (__debug_flg)
  {
   __dbg_msg("))) freeing iploctab for module %s\n", __inst_mod->msym->synam);
  }
 /* --- */

 for (ii = 0; ii < __inst_mod->minum; ii++)
  {
   ip = &(__inst_mod->minsts[ii]);
   imdp = ip->imsym->el.emdp;
   if ((pnum = imdp->mpnum) == 0)
    {
     /* DBG remove -- */
     if (__inst_mod->iploctab[ii] != NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     continue;
    }

   /* ptr to table of actual src loc records */
   iplocs = __inst_mod->iploctab[ii];
   /* DBG remove -- */
   if (iplocs == NULL) __misc_terr(__FILE__, __LINE__);

   ip = &(__inst_mod->minsts[ii]);
   if (ip->i_giap != NULL)
    {
     if (ip->i_giap->gia_is_base_first) 
      {
       __my_free(iplocs, pnum*sizeof(struct srcloc_t)); 
      }
    }
   else __my_free(iplocs, pnum*sizeof(struct srcloc_t)); 
   __inst_mod->iploctab[ii] = NULL;
   /* number of ports if number for contained inst */
  }
 if (__inst_mod->minum != 0)
  {
   __my_free(__inst_mod->iploctab,
    __inst_mod->minum*sizeof(struct srcloc_t **));
  }
 __inst_mod->iploctab = NULL;
}

/*
 * check gate and continuous assigns
 * notice at this point continuous assignments still not split off
 */
static void chk_gates(void)
{
 int32 gi, pi, dnum, nins;
 struct gate_t *gp;
 struct expr_t *xp;
 struct net_t *np;
 struct paramlst_t *dhdr;

 /* check gates first */
 __expr_rhs_decl = TRUE;
 for (gi = 0; gi < __inst_mod->mgnum; gi++)
  {
   gp = &(__inst_mod->mgates[gi]);

   __sfnam_ind = gp->gsym->syfnam_ind;
   __slin_cnt = gp->gsym->sylin_cnt;
   if (gp->g_class != GC_UDP)
    {
     /* returns FALSE if special gate (pull?), will then not check ports */
     /* know output port checked later */
     if (!chk_1bltingate(gp)) continue;
     nins = gp->gpnum - 1;
    }
   else
    {
     /* SJM 07/02/03 - if error here will core dump if keeps checking */ 
     if (!chk_1udp(gp)) continue;
     nins = gp->gmsym->el.eudpp->numins;
    }

   /* returns F on fail, must convert to unc. OPEMPTY */ 
   if (!chk_gate_source(gp, gp->gpins[0], TRUE, FALSE, &np))
    { __free_xtree(gp->gpins[0]); set_unc_gateterm(gp, 0); }
   for (pi = 0; pi < nins; pi++)
    {
     /* can tell i/o type from gate order */
     xp = gp->gpins[pi + 1];
     __chk_rhsexpr(xp, 1);
     if (xp->is_real)
      __sgferr(781, 
       "gate or udp %s input terminal %s (pos. %d) cannot have real value",
       gp->gmsym->synam, __msgexpr_tostr(__xs2, xp), pi + 1);
     /* for implicitly declared must mark as scalar if first use */
     if (xp->optyp == ID)
      { 
       np = xp->lu.sy->el.enp;
       if (np->nu.ct->n_impldecl && !np->nu.ct->n_rngknown)
        np->nu.ct->n_rngknown = TRUE;  
      }
    }
   if (gp->g_du.pdels == NULL) continue;

   /* check delay params, sim array built later */
   if (gp->g_class == GC_UDP)
    {
     dhdr = __copy_dellst(gp->g_du.pdels);
     if ((dnum = __chk_delparams(dhdr, "udp delay", FALSE)) == -1)
      gp->g_du.pdels = NULL;
     else if (dnum > 2)
      {
       __sgferr(782, "udp has more than 2 delays (%d)", dnum);
       gp->g_du.pdels = NULL;
      }
     __free_dellst(dhdr);
    }
   else
    {
     dhdr = __copy_dellst(gp->g_du.pdels);
     if ((dnum = __chk_delparams(dhdr, "built-in gate delay", FALSE)) == -1)
      gp->g_du.pdels = NULL;
     else if (gp->g_class == GC_LOGIC)
      { 
       if (dnum > 2)
        {
         __sgferr(783, "%s logic gate has more than 2 delays (%d)",
          gp->gmsym->synam, dnum);
          gp->g_du.pdels = NULL;
        }
      }
     else if (dnum > 3)
      {
       __sgferr(775, "%s gate has more than 3 delays (%d)",
        gp->gmsym->synam, dnum);
       gp->g_du.pdels = NULL;
      }
     __free_dellst(dhdr);
    }
  }
 /* unless looking for declarative, must leave in off state */
 __expr_rhs_decl = FALSE;
}

/*
 * check 1 built in gate (not udps and 1 bit contas still not gates)
 * notice normal gate just falls through and only terminal list checked
 * return F to prevent normal 1st only output gate expression checking
 * if returns F must call expression checking for each port itself
 *
 */
static int32 chk_1bltingate(struct gate_t *gp)
{
 int32 pnum;
 struct primtab_t *ptp;

 pnum = gp->gpnum;
 ptp = gp->gmsym->el.eprimp;
 switch ((byte) ptp->gateid) {
  case G_BUF: case G_NOT:
   if (pnum == 1) __sgferr(784,
    "%s gate requires at least 2 terminals", ptp->gatnam);
   else if (pnum != 2)
    __sgferr(785, "%s gate with multiple outputs unsupported", ptp->gatnam);
   break;
  case G_BUFIF0: case G_BUFIF1: case G_NOTIF0: case G_NOTIF1:
   if (pnum != 3) gate_errifn(gp, 3);
   break;
  case G_RPMOS: case G_RNMOS:
   /*FALLTHRU */
  case G_NMOS: case G_PMOS:
   chk_gate_nostren(gp);
   if (pnum != 3) gate_errifn(gp, 3);
   break;
  case G_RCMOS:
   /*FALLTHRU */
  case G_CMOS:
   chk_gate_nostren(gp);
   if (pnum != 4) gate_errifn(gp, 4);
   break;
  case G_PULLDOWN: case G_PULLUP:
   chk_pull_gate(gp);
   /* this inhibits normal checking of ports */
   return(FALSE);
  case G_TRAN: case G_RTRAN:
   chk_tran_gate(gp);
   return(FALSE);
  case G_TRANIF0: case G_TRANIF1: case G_RTRANIF0: case G_RTRANIF1:
   chk_tranif_gate(gp);
   return(FALSE);
  default:
   if (pnum < 2)
    {
     __sgferr(786, "%s gate requires at least 2 terminals", gp->gmsym->synam);
    }
   else if (pnum < 3)
    {
#ifndef __CVC_RT__
     __sgfwarn(573, "%s gate has only %d terminals - should have at least 3",
      gp->gmsym->synam, pnum);
#endif
    }
  }
 return(TRUE);
}

/*
 * write a message for a if type gate that needs 3 terminals
 */
static void gate_errifn(struct gate_t *gp, int32 n)
{
 __sgferr(787, "%s gate does not have required %d terminals",
  gp->gmsym->synam, n);
}

/*
 * emit warning and remove strength on gate that should not have it
 */
static void chk_gate_nostren(struct gate_t *gp)
{
#ifndef __CVC_RT__
 if (gp->g_hasst)
  {
   __sgfwarn(537, "%s gate cannot have strength", gp->gmsym->synam);
   gp->g_hasst = FALSE;
   gp->g_stval = ST_STRVAL; 
  }
#endif
}

/*
 * check a tran style gate
 */
static void chk_tran_gate(struct gate_t *gp)
{ 
 int32 pnum;
 struct expr_t *px1, *px2;
 struct net_t *np1, *np2;

 np1 = np2 = NULL;
 /* first cannot have delay */
 if (gp->g_du.pdels != NULL)
  {
   __sgferr(816, "%s cannot have delay", gp->gmsym->synam);
   __free_dellst(gp->g_du.pdels);
   gp->g_du.pdels = NULL;
  }
 /* must mark as no del since later expression checking expects no delay */
 gp->g_delrep = DT_NONE;

 /* any tran can't have strength - signal strength is preserved according */
 /* to resistive or not mos table */
 chk_gate_nostren(gp);
 px1 = px2 = NULL;
 pnum = gp->gpnum;
 if (pnum != 2) gate_errifn(gp, 2);
 if (pnum >= 1) px1 = gp->gpins[0];
 if (pnum >= 2) px2 = gp->gpins[1];
 /* for these both terminals must be lhs */ 
 if (px1 != NULL)
  {
   if (!chk_gate_source(gp, px1, TRUE, TRUE, &np1))
    {
    __free_xtree(px1);
     /* this cannot build unc expr since cannot set pull only for inst */
     set_unc_gateterm(gp, 0);
    }
   else chk_1bit_tran(gp, px1, np1, 1);
  }
  
 if (px2 != NULL)
  {
   if (!chk_gate_source(gp, px2, TRUE, TRUE, &np2))
    { __free_xtree(px2); set_unc_gateterm(gp, 1); }
   else chk_1bit_tran(gp, px2, np2, 2);
  }
 __inst_mod->mod_gatetran = TRUE;
 /* SJM 04/26/01 - if both terminals same, emit warning and mark as gone */
 chk_tran_terms_same(gp);
}

/*
 * check for tran or tranif with both inout terminals same expr
 * if so emit warning and mark deleted from net list 
 * return T if deleted
 */
static int32 chk_tran_terms_same(struct gate_t *gp)
{
 struct expr_t *xp1, *xp2;
 struct net_t *np1, *np2;
 int32 i1, i2;

 xp1 = gp->gpins[0]; 
 xp2 = gp->gpins[1];
 if (xp1->optyp == ID && xp2->optyp == ID)
  {
   np1 = xp1->lu.sy->el.enp;
   np2 = xp2->lu.sy->el.enp;
   /* since not xmr, can compare net addrs */
#ifndef __CVC_RT__
   if (np1 == np2)
    {
     __gfwarn(3117, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
      "%s %s inout terminals (%s) identical - removed because has no effect", 
      gp->gmsym->synam, gp->gsym->synam, np1->nsym->synam);
     gp->g_gone = TRUE;
    }
#endif
   return(TRUE);
  }
 if (xp1->optyp == LSB && xp2->optyp == LSB)
  {
   np1 = xp1->lu.x->lu.sy->el.enp;
   np2 = xp2->lu.x->lu.sy->el.enp;
   /* know same net */
   if (np1 != np2) return(FALSE);

   if (xp1->ru.x->optyp != NUMBER || xp2->ru.x->optyp != NUMBER)
    return(FALSE);
   i1 = __contab[xp1->ru.x->ru.xvi];
   i2 = __contab[xp2->ru.x->ru.xvi];
#ifndef __CVC_RT__
   if (i1 == i2) 
    {
     __gfwarn(3117, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
      "%s %s inout terminals (%s[%d]) identical - gate removed because has not effect", 
      gp->gmsym->synam, gp->gsym->synam, np1->nsym->synam, i1);
     gp->g_gone = TRUE;
    }
#endif
  }
 return(FALSE);
}

/*
 * set unc (OPEMPTY) for gate terminal
 */
static void set_unc_gateterm(struct gate_t *gp, int32 pi)
{
 /* cannot use bld unc expr here since sets pull but that only for */
 /* for instances */
 __root_ndp = __alloc_newxnd();
 __root_ndp->optyp = OPEMPTY;
 __root_ndp->folded = TRUE;
 __root_ndp->szu.xclen = 1;
 gp->gpins[pi] = __root_ndp;
}

/*
 * check to make sure tran bidirectional terminal only connect to scalar
 * nets or bit selects
 */
static void chk_1bit_tran(struct gate_t *gp, struct expr_t *px,
 struct net_t *np, int32 termno)
{
#ifndef __CVC_RT__
 if (px->optyp == OPEMPTY)
  {
   __sgfwarn(581, "%s terminal %d unconnected - switch has no effect",
    gp->gmsym->synam, termno);
   return;
  }
#endif
 /* 07/08/00 SJM - because of complexity with switch channal also can't be */
 /* ID must be select of ID */
 if ((px->optyp == PARTSEL || px->optyp == PARTSEL_NDX_PLUS 
      || px->optyp == PARTSEL_NDX_MINUS) || (px->optyp != LSB && np->n_isavec)
      || ((px->optyp == GLBREF || px->optyp == ID)
  && px->lu.sy->el.enp->nwid > 1))
  { 
   __sgferr(1237, "%s terminal %d - %s not scalar or scalared bit select",
    gp->gmsym->synam, termno, __msgexpr_tostr(__xs, px));
   return;
  }
 /* by here any constant converted to empty and caught above */
 if (np->nu.ct->n_dels_u.pdels != NULL)
  {
   __sgferr(1238,
    "%s terminal %d (%s) - wire %s in tran channel illegally has wire delay",
    gp->gmsym->synam, termno, __msgexpr_tostr(__xs, px), np->nsym->synam);
  }
}

/*
 * check a tranif style gate 
 */
static void chk_tranif_gate(struct gate_t *gp)
{ 
 int32 dnum, pnum;
 struct paramlst_t *dhdr;
 struct net_t *np1, *np2;
 struct expr_t *px1, *px2, *px3;
 
 np1 = np2 = NULL;
 if (gp->g_du.pdels != NULL)
  {
   /* can have 0,1 or 2 delays */ 
   dhdr = __copy_dellst(gp->g_du.pdels);
   if ((dnum = __chk_delparams(dhdr, "tranif enable delay", TRUE)) == -1)
    gp->g_du.pdels = NULL; 
   else if (dnum > 2)
    {
     __sgferr(799, "%s gate has more than 2 delays (%d)", gp->gmsym->synam,
      dnum);
     gp->g_du.pdels = NULL;
    }
   __free_dellst(dhdr);
  }

 /* any tran can't have strength - signal strength is preserved according */
 /* to resistive or not mos table */
 chk_gate_nostren(gp);
 px1 = px2 = NULL;
 pnum = gp->gpnum;
 if (pnum != 3) gate_errifn(gp, 3);
 if (pnum >= 1) px1 = gp->gpins[0];
 if (pnum >= 2) px2 = gp->gpins[1];
 /* for these both terminal must be lhs */ 
 if (px1 != NULL)
  {
   if (!chk_gate_source(gp, px1, TRUE, TRUE, &np1))
    { __free_xtree(px1); set_unc_gateterm(gp, 0); }
   else chk_1bit_tran(gp, px1, np1, 1);
  }
 if (px2 != NULL)
  {
   if (!chk_gate_source(gp, px2, TRUE, TRUE, &np2))
    { __free_xtree(px2); set_unc_gateterm(gp, 1); }
   else chk_1bit_tran(gp, px2, np2, 2);
  }
 if (pnum < 3) return;

 /* check 3rd control normal input terminal */
 px3 = gp->gpins[2];
 __chk_rhsexpr(px3, 1);
 if (px3->is_real)
  __sgferr(781, "%s gate input terminal value %s cannot be real",
   gp->gmsym->synam, __msgexpr_tostr(__xs2, px3));
 __inst_mod->mod_gatetran = TRUE;

 /* SJM 04/26/01 - if both terminals same, emit warning and mark as gone */
 chk_tran_terms_same(gp);
}

/*
 * check a pull gate - can any any length list of lhs sources
 * all pull pins are outputs 
 */
static void chk_pull_gate(struct gate_t *gp)
{
 int32 i;
 struct expr_t *xp;
 struct net_t *np;

 /* first cannot have delay */
 if (gp->g_du.pdels != NULL)
  {
   __sgferr(816, "%s source cannot have delay", gp->gmsym->synam);
   __free_dellst(gp->g_du.pdels);
   gp->g_du.pdels = NULL;
  }
 /* must mark as no del since later expression checking expects no delay */
 gp->g_delrep = DT_NONE;

 /* for pull sources, stength defaults to pull not strong */
 /* LOOKATME - pull gate always has strength so g_hasst not checked */
 if (!gp->g_hasst) gp->g_stval = 0x2d;
 else if (gp->g_stval == 0x00)
  {
   __sgferr(1151, "%s source highz[01] strength illegal",
    gp->gmsym->synam);
  }
#ifndef __CVC_RT__
 else if (gp->g_stval == 0x3f)
  {
   __sgfwarn(546, "%s source supply[01] strength same as supply declaration",
    gp->gmsym->synam);
  }
#endif

 /* all ports must be legal lhs expressions except no concat and xmr */
 /* notice constant bit and part selects ok */
 for (i = 0; i < (int32) gp->gpnum; i++) 
  {
   xp = gp->gpins[i];
   __chk_lhsexpr(xp, LHS_DECL);
   if (xp->optyp == LCB)
    {
     __sgferr(951, "%s source %s (pos. %d) cannot drive concatenate",
      gp->gmsym->synam, __msgexpr_tostr(__xs, xp), i + 1);
     continue;
    }
   if (xp->optyp == GLBREF)
    {
     __sgferr(959,
      "%s source cannot drive cross module reference %s (pos. %d)",
      gp->gmsym->synam, __msgexpr_tostr(__xs, xp), i + 1);
     continue;
    }
   else if (xp->optyp == OPEMPTY)
    {
     __sgferr(965,
      "%s source empty (,,) terminal list element (pos. %d) illegal",
      gp->gmsym->synam, i + 1); 
     continue;
    }
   /* source must be wire */
   if (xp->optyp == LSB || xp->optyp == PARTSEL 
    ||  xp->optyp == PARTSEL_NDX_PLUS || xp->optyp == PARTSEL_NDX_MINUS)
     {
      np = xp->lu.x->lu.sy->el.enp;
     }
   else np = xp->lu.sy->el.enp;  
   if (np->ntyp >= NONWIRE_ST)
    {
     __sgferr(969,
      "%s source net %s (pos. %d) type %s illegal - must be wire type",
      gp->gmsym->synam, np->nsym->synam, i + 1, __to_wtnam(__xs, np));
     continue;
    }
   if (np->ntyp == N_TRIREG)
    {
     __sgfinform(443, "%s source on trireg wire %s (pos. %d)",
      gp->gmsym->synam, np->nsym->synam, i+ 1);
     continue;
    }
#ifndef __CVC_RT__
   if (np->ntyp == N_SUPPLY0 || np->ntyp == N_SUPPLY1 || np->ntyp == N_TRI0
    || np->ntyp == N_TRI1)
    {
     __sgfwarn(536, "%s source on %s wire %s (pos. %d) has no effect",
      gp->gmsym->synam, np->nsym->synam, __to_wtnam(__xs, np), i+ 1);
     continue;
    }
#endif
  }
}

/*
 * check a udp
 * notice nins here includes output state if non comb.
 */
static int32 chk_1udp(struct gate_t *gp)
{
 struct udp_t *udpp;

 udpp = gp->gmsym->el.eudpp;
 udpp->u_used = TRUE;
 /* numins includes state that does not appear in udp instantiation */
 if (gp->gpnum - 1 != udpp->numins)
  {
   __sgferr(790, "udp %s has wrong number of terminals (%d) should be %d",
    gp->gmsym->synam, gp->gpnum, udpp->numins + 1);
   return(FALSE);
  }
 /* more checking */
 return(TRUE);
}

/*
 * check a gate output (source) driving terminal more than one
 */
static int32 chk_gate_source(struct gate_t *gp, struct expr_t *xp,
 int32 nd_lhs_chk, int32 nd_1bit, struct net_t **ret_np)
{
 int32 rv;
 struct net_t *np;
 char s1[RECLEN];

 if (gp->g_class == GC_UDP) strcpy(s1, "udp"); else strcpy(s1, "gate");
 np = NULL; 
 *ret_np = NULL;
 /* real driven by gate output caught also bit select from vectored wire */
 if (nd_lhs_chk)
  {
   rv = __chk_lhsexpr(xp, LHS_DECL);
   if (!rv) return(FALSE);
  }
 switch (xp->optyp) {
  case ID: case GLBREF:
   np = xp->lu.sy->el.enp;
   if (__get_netwide(np) > 1 && !nd_1bit)
    {
#ifndef __CVC_RT__
     __sgfwarn(538,
      "%s %s output %s wider than 1 bit - assuming select of low bit", 
      gp->gmsym->synam, s1, __to_idnam(xp));
     /* cannot be vectored vector since implied select */
#endif
     __chk_lhsdecl_scalared(xp);
    }
   break;
  case OPEMPTY: break;
  case ISNUMBER:
   if (xp->is_real) goto is_real; 
   /*FALLTHRU */
  case NUMBER:
#ifndef __CVC_RT__
   __sgfwarn(539,
    "%s %s output drives constant - made unconnected",
    gp->gmsym->synam, s1);
#endif
   return(FALSE);
  case REALNUM:
  case ISREALNUM:
is_real:
   __sgferr(793,
    "%s %s output cannot connect to real number", gp->gmsym->synam, s1); 
   return(FALSE);
  case LSB:
   np = xp->lu.x->lu.sy->el.enp;
   break;
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   /* if part select, must change to bit select with warning */
   /* done after check psel called - needs normalized indices */
#ifndef __CVC_RT__
   if (!nd_1bit)
    {
     __sgfwarn(540, "%s %s output drives part select - assign to low bit",
      gp->gmsym->synam, s1);
    }
#endif
   np = xp->lu.x->lu.sy->el.enp;
   break;
  case LCB:
   __sgferr(794, "%s %s output terminal cannot be connected to concatenate",
    gp->gmsym->synam, s1);
   return(FALSE);
  default:
   __sgferr(795, "%s %s output expression %s illegal",
    gp->gmsym->synam, s1,  __msgexpr_tostr(__xs, xp));
   return(FALSE);
  }
 *ret_np = np;
 return(TRUE);
}

/*
 * check declarative type continuous assignments from one module
 * know cmsym NULL to get here
 *
 * this is point where 1 bit continuous assignments removed and added
 * as gates of type (token ASSIGN)
 *
 * quasi cont. assign checked in statement checking code
 */
static void chk_contas(void)
{
 int32 lhs_gd, dnum, sav_ecnt, cwid, num_gd1bca, cai, num_cas;
 struct conta_t *cap;
 struct conta_t *last_cap, *cap2, *ca1bit_hd, *last_1bcap, *catab;
 struct expr_t *lhsx, *rhsx;
 struct paramlst_t *dhdr;

 last_cap = NULL;
 ca1bit_hd = NULL;
 last_1bcap = NULL;
 __expr_rhs_decl = TRUE;
 num_cas = 0;
 for (cap = __inst_mod->mcas, num_gd1bca = 0; cap != NULL;)
  {
   __sfnam_ind = cap->casym->syfnam_ind;
   __slin_cnt = cap->casym->sylin_cnt;

   num_cas++;
   /* error if cont. assign lhs not a wire */
   lhsx = cap->lhsx;
   rhsx = cap->rhsx;

   sav_ecnt = __pv_err_cnt;
   lhs_gd = __chk_lhsexpr(lhsx, LHS_DECL);
   /* index error still allow return of T from chk lhs expr */
   if (__pv_err_cnt > sav_ecnt) lhs_gd = FALSE;

   cwid = lhsx->szu.xclen;
   __chking_conta = TRUE;
   __rhs_isgetpat = FALSE;
   /* notice rhs here may be left as the $getpattern function call */
   __chk_rhsexpr(rhsx, cwid);

   if (rhsx->is_real || lhsx->is_real)
    __sgferr(796,
     "real expression illegal on either side of continuous assign");
   __chking_conta = FALSE;
   if (__rhs_isgetpat)
    {
     nd_1bit_concat(lhsx);
     if (cap->ca_du.pdels != NULL)
      __sgferr(797,
       "continuous assign with $getpattern on right cannot have delay"); 
     lhsx->getpatlhs = TRUE;
     __rhs_isgetpat = FALSE;
     goto nxt_ca;
    }
   if (cap->ca_du.pdels != NULL)
    {
     dhdr = __copy_dellst(cap->ca_du.pdels);
     if ((dnum = __chk_delparams(dhdr, "continuous assignment delay",
      FALSE)) == -1) cap->ca_du.pdels = NULL;
     else if (dnum > 3)
      {
       __sgferr(798, "continuous assign has more than 3 delays (%d)", dnum);
       cap->ca_du.pdels = NULL;
      }
     /* SJM 09/28/02 - anything but 1v need 4v table so conta del all bits */ 
     __free_dellst(dhdr);
    }

   /* SJM 06-25-09 lhs part of continuous assign can be 1 bit but a concat */
   /* in that case just leave as a conta - slowerly but should work since */ 
   /* 1 bit concats are legal so they will just work right */

   /* must convert to 1 bit form if needed */
   if (lhs_gd && lhsx->szu.xclen == 1 && lhsx->optyp != LCB)
    {
     /* link out 1 bit ca onto tmp list */ 
     cap2 = cap->pbcau.canxt;

     num_gd1bca++;
     if (last_1bcap == NULL) ca1bit_hd = cap;
     else last_1bcap->pbcau.canxt = cap;
     cap->pbcau.canxt = NULL;
     last_1bcap = cap;

     if (last_cap == NULL) __inst_mod->mcas = cap2;
     else last_cap->pbcau.canxt = cap2;
     /* notice last_cap stays same when splicing out */
     cap = cap2;
     continue;
    }

nxt_ca:
   /* only get here is lhs wider than 1 bit */
   if (cap->ca_hasst)
    {
     if ((cap->ca_stval & 7) == 0 || (cap->ca_stval & 0x38) == 0)
      __sgferr(1276,
       "wider than one bit vector continuous assign highz[01] strength unsupported");
    }
   last_cap = cap;
   cap = cap->pbcau.canxt;
  }
 __expr_rhs_decl = FALSE;
 /* next re-allocate 1bit cas on end of mgates array */ 
 /* since conta already checked can convert and not apply gaet checks */
 if (num_gd1bca > 0)
  {
   cnv_1bcas_into_garr(num_gd1bca, ca1bit_hd); 
   num_cas -= num_gd1bca;
  }

 /* final step is to convert conta to array same as m nets conversion */
 /* from now on (same as with nets) - must index through array to traverse */
 /* contas */
 catab = NULL;
 __inst_mod->mcanum = num_cas;
 if (__inst_mod->mcanum != 0)
  {   
   catab = (struct conta_t *)
    __my_malloc(__inst_mod->mcanum*sizeof(struct conta_t)); 
  }
 for (cai = 0, cap = __inst_mod->mcas; cai < __inst_mod->mcanum; cai++)
  {
   cap2 = cap->pbcau.canxt;

   catab[cai] = *cap; 
   __my_free(cap, sizeof(struct conta_t));
   catab[cai].pbcau.canxt = NULL;

   cap = cap2;
  }
 __inst_mod->mcas = catab; 
}

/*
 * convert the separated out 1 bit cas to gates and free cas
 *
 * tricky step required to point all symbols for name back to gate which
 * may (probably will) be moved by re-alloc
 */
static void cnv_1bcas_into_garr(int32 n1bcas, struct conta_t *ca1bit_hd) 
{
 int32 gi;
 struct conta_t *cap, *cap2;
 size_t osize, nsize;
 struct gate_t *gp;
 struct net_t *dum_np;

 dum_np = NULL;
 /* mark needed because must change back to conta for vpi_ */ 
 __inst_mod->mod_1bcas  = TRUE;

 /* reallocate mgates to add room at end */
 osize = __inst_mod->mgnum*sizeof(struct gate_t);
 nsize = osize + n1bcas*sizeof(struct gate_t);
 /* common for no gates in design - only 1 bit contas */
 /* know nsize at least one or will not get here */
 if (osize == 0) { gp = (struct gate_t *) __my_malloc(nsize); }
 else 
  {
   gp = (struct gate_t *) __my_realloc(__inst_mod->mgates, osize, nsize);
  }
 __inst_mod->mgates = gp;
 /* reset each el egp field */
 for (gi = 0; gi < __inst_mod->mgnum; gi++)
  {
   gp = &(__inst_mod->mgates[gi]);
   gp->gsym->el.egp = gp;
  }

 /* notice number is index of one after */
 gi = __inst_mod->mgnum;
 __inst_mod->mgnum += n1bcas; 
 for (cap = ca1bit_hd; cap != NULL; gi++)
  {
   gp = &(__inst_mod->mgates[gi]);
   convert_1bca_togate(gp, cap);
   
   /* just move the conta built inst. */ 
   gp->gsym = cap->casym;
   gp->gsym->el.egp = gp;
   gp->gsym->sytyp = SYM_PRIM;
   if (!chk_gate_source(gp, gp->gpins[0], FALSE, FALSE, &dum_np))
    {
     __free_xtree(gp->gpins[0]);
     set_unc_gateterm(gp, 0);
    }
   /* free and link out conta */
   cap2 = cap->pbcau.canxt;
   /* ca scheduled event array not yet allocated */
   __my_free(cap, sizeof(struct conta_t));
   cap = cap2;
  }
}

/*
 * convert a 1 bit continuous assign to a gate and link on end
 * of module's gate list - returns F if not converted
 *
 * this fills passed gate struct from within mgates
 * notice this can not return nil
 * other fields initialized later
 */
static struct gate_t *convert_1bca_togate(struct gate_t *gp, 
 struct conta_t *cap)
{
 /* caller sets gsym */
 gp->gsym = NULL;
 gp->gmsym = __ca1bit_syp;

 gp->gpnum = 2;
 gp->g_hasst = cap->ca_hasst;
 gp->g_stval = cap->ca_stval;
 gp->g_delrep = cap->ca_delrep;
 /* assign delay union */
 gp->g_du = cap->ca_du;
 gp->schd_tevs_ofs = 0;
 gp->g_class = GC_LOGIC;
 gp->g_pdst = FALSE;
 gp->g_unam = FALSE;
 gp->g_gone = FALSE;
 gp->gate_out_ofs = 0;
 gp->ctevp = NULL;
 gp->gstate_ofs = 0;
 gp->gattrs = NULL;
 /* AIV 05/21/10 - need to init new g_giap to NULL */
 gp->g_giap = NULL;

 /* build the special output, temp form */
 gp->gpins = (struct expr_t **) __my_malloc(2*sizeof(struct expr_t *));
 gp->gpins[0] = cap->lhsx;
 gp->gpins[1] = cap->rhsx;
 /* caller must free and unlink continuous assign */
 return(gp);
}

/*
 * for get pattern continuous assigment must be scalar wire or concat of
 * scalar wires (lhs of conta assign non wire already caught)
 */
static void nd_1bit_concat(struct expr_t *lhsx)
{
 struct expr_t *catndp;

 if (lhsx->optyp == LCB)
  {
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    chk_getpat_nonscal(catndp->lu.x);
   return;
  }
 __sgferr(800,
  "$getpattern continous assign lvalue must be concatenate of scalar wires");
}

/*
 * error if non scalar net
 * know this is wire
 */
static void chk_getpat_nonscal(struct expr_t *lhsx)
{
 struct net_t *np;

 if (lhsx->optyp == GLBREF)
  { 
   __sgferr(801,
    "$getpattern assign lvalue hierarchical path reference %s illegal",
    __to_idnam(lhsx));
   return;
  }
 if (lhsx->optyp != ID)
  {
   __sgferr(802, "$getpattern assign lvalue element %s not a simple wire",
     __msgexpr_tostr(__xs, lhsx));
   return;
  }
 np = lhsx->lu.sy->el.enp;
 if (np->n_isavec)
  __sgferr(966,
   "$getpattern continous assign lvalue element %s not a scalar",
   __to_idnam(lhsx));
 if (np->n_stren)
  __sgferr(967,
   "$getpattern continous assign lvalue element %s has strength",
   __to_idnam(lhsx));
}

/*
 * check a user function definition
 * this must undeclare if error because cannot check call
 * know function defined at top level of __inst_mod
 */
extern void __chk_funcdef(struct task_t *tskp)
{
 int32 saverr_cnt;
 
 /* special DPI function checking */
 if (tskp->tf_dpip != NULL)
  {
   __chk_funcdef_dpi(tskp);
   return;
  }

 __cur_tsk = tskp;
 saverr_cnt = __pv_err_cnt;
 /* check definition args */
 __chk_fdef_args(tskp);

 /* SJM 09/28/01 - see if func call other non sys func */
 __func_has_fcall = FALSE;

 /* first check all statements normally */ 
 __disp_uses_scope = FALSE;
 __chk_lstofsts(tskp->tskst);
 if (__func_has_fcall) tskp->fhas_fcall = TRUE;
 tskp->uses_scope = __disp_uses_scope;

 /* check all sub statements for illegal delay controls */
 /* also sets name_assigned_to if name somewhere on assign lhs */
 __task_has_delay = FALSE;
 __task_has_xmrcall = FALSE;
 __task_has_tskcall = FALSE;
 __name_assigned_to = FALSE;
 __locfnamsyp = tskp->tskpins->tpsy;
 __nbsti = -1;
 __checking_only = FALSE;
 __chk_nodel_lstofsts(tskp->tskst);
 __checking_only = TRUE;
#ifndef __CVC_RT__
 /* AIV 11/08/10 - cannot assign return value to a void function */
 /* and if a void function - do not omit warn */
 if (!__name_assigned_to && !tskp->is_void_func)
  __gfwarn(647, tskp->tsksyp->syfnam_ind, tskp->tsksyp->sylin_cnt,
   "no assignment to function name %s in body", tskp->tsksyp->synam);
 else if (tskp->is_void_func && __name_assigned_to)
  {
   __gferr(4870, tskp->tsksyp->syfnam_ind, tskp->tsksyp->sylin_cnt,
    "function %s declared void cannot set return value",
    tskp->tsksyp->synam);
  }
#endif
 /* must leave name assigned to off, unless checking func. def body */
 __name_assigned_to = FALSE;
 if (__pv_err_cnt != saverr_cnt) tskp->tsksyp->sydecl = FALSE;
 __cur_tsk = NULL;
 __disp_uses_scope = FALSE;
}

/*
 * check a function def arguments
 * all ports inputs and 1 required
 */
extern void __chk_fdef_args(struct task_t *tskp)
{
 int32 ai;
 struct task_pin_t *tpp;
 struct sy_t *syp;
 struct net_t *np;
 char s1[RECLEN];

 /* function definition return value missing */
 if ((tpp = tskp->tskpins) == NULL)
  __misc_gfterr(__FILE__, __LINE__, tskp->tsksyp->syfnam_ind,
   tskp->tsksyp->sylin_cnt);
 if (tpp->tpsy->sytyp != SYM_N) __arg_terr(__FILE__, __LINE__);  
 /* assign err replaces unused err, this rhs of func. return value assign */
 np = tpp->tpsy->el.enp;
 /* notice not set n_onprocrhs since only needed for wires */ 
 if (np->nrngrep == NX_CT) np->nu.ct->n_onrhs = TRUE;
 
 if ((tpp = tpp->tpnxt) == NULL)
  {
   __gferr(867, tskp->tsksyp->syfnam_ind, tskp->tsksyp->sylin_cnt,
    "function %s definition requires at least one input argument",
    tskp->tsksyp->synam);
   return;
  }
 for (ai = 1; tpp != NULL; tpp = tpp->tpnxt, ai++)
  {
   np = tpp->tpsy->el.enp;
   if (tpp->tpsy->sytyp != SYM_N) __arg_terr(__FILE__, __LINE__);  
   /* AIV 11/16/10 - SV now allows functions with outputs */
   if (!__sv_parse)
    {
     if (tpp->trtyp != IO_IN)
      {
       syp = tpp->tpsy;
       __gferr(868, syp->syfnam_ind, syp->sylin_cnt,
        "function %s argument %s illegal - must be input",
        __to_ptnam(s1, tpp->trtyp), syp->synam);
      }
     if (np->nrngrep == NX_CT) np->nu.ct->n_onlhs = TRUE;
    }
   else
    {
     /* notice task ports must be regs so no need to set 2nd on lhs */
     if (tpp->trtyp != IO_IN)
      {
       if (np->nrngrep == NX_CT)
        {
         if (tpp->trtyp == IO_BID) np->nu.ct->n_onlhs = TRUE;
         np->nu.ct->n_onrhs = TRUE;
        }
       tskp->thas_outs = TRUE;
      }
     else if (np->nrngrep == NX_CT) np->nu.ct->n_onlhs = TRUE;
    }




   /* SJM 01/14/1999 - arrays illegal formal function arguments */
   /* DPI can now pass an entire array */
   if (tskp->tf_dpip == NULL)
    {
     if (np->n_isarr)
      {
       syp = tpp->tpsy;
       __gferr(869, syp->syfnam_ind, syp->sylin_cnt,
        "function %s definition entire array formal argument %s (pos. %d) illegal - must be simple variable",
        tskp->tsksyp->synam, syp->synam, ai);
      }
    }
   else
    {
     /* AIV 08/02/10 - MDA not yet supported for DPI */
     if (np->n_isarr)
      {
       syp = tpp->tpsy;
       __gferr(869, syp->syfnam_ind, syp->sylin_cnt,
        "DPI task %s definition argument %s (pos. %d) illegal - CVC DPI support currently does not support multi-dimensional array passing",
        tskp->tsksyp->synam, syp->synam, ai);
      }
    }
  }
}

/*
 * check func. def. and task statement list
 * if func. def. and delay error, else just set flag for optimization
 */
extern void __chk_nodel_lstofsts(struct st_t *fhdstp)
{
 struct st_t *stp;

 /* then check for illegal in func def. statements */
 for (stp = fhdstp; stp != NULL; stp = stp->stnxt) chk_nodel_stmt(stp);
}

/*
 * check task body statement list for time movement constructs
 * for functions emits errors, for rest sets flags
 * for every named block sets time movement task bits for optimization
 *
 * think could allow distant disables and causes and still could optimize
 * but for now using function rules
 * assumes normal statement checking already finished
 * notice always called after statement checking so disables fixed up
 */
static void chk_nodel_stmt(struct st_t *stp)
{
 char s1[RECLEN];
 struct task_t *tskp;

 switch ((byte) stp->stmttyp) {
  case S_NULL: case S_STNONE: break;
  /* legal statements */
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA:
   /* notice for rhs delay control - wrong delay control caught at dctrl */
   if (!__checking_only || !__name_assigned_to)
    {
     if (lhsexpr_hassym(stp->st.spra.lhsx, __locfnamsyp))
      __name_assigned_to = TRUE;
    }
   break;
  /* these do not count as assignment to name */ 
  case S_QCONTA: case S_QCONTDEA:
   break;
  case S_IF:
   __chk_nodel_lstofsts(stp->st.sif.thenst);
   if (stp->st.sif.elsest != NULL) __chk_nodel_lstofsts(stp->st.sif.elsest);
   break;
  case S_CASE:
   {
    struct csitem_t *csip;
    struct csitem_t *dflt_csip;
   
    /* first always default or place holder for default in no st */
    dflt_csip = stp->st.scs.csitems;
    for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
     {
      __chk_nodel_lstofsts(csip->csist);
     }
    if (dflt_csip->csist != NULL) __chk_nodel_lstofsts(dflt_csip->csist);
#ifdef __XPROP__
    /* AIV 08/02/11 - now might have xprop list to process as well */
    if (stp->st.scs.xprop_lstp != NULL)
     {
      __chk_nodel_lstofsts(stp->st.scs.xprop_lstp);
     }
#endif
   }
   break;
  case S_FOREVER:
  case S_WHILE:
  case S_DO_WHILE:
   __chk_nodel_lstofsts(stp->st.swh.lpst);
   break;
  case S_REPEAT:
   __chk_nodel_lstofsts(stp->st.srpt.repst);
   break;
  case S_FOR:
   {
    struct for_t *frs;
    struct st_t *stp2;

    frs = stp->st.sfor;
    /* AIV 10/01/10 - for assign can now have multiple - cannot use */
    /* list because is linked onto forbody */
    for (stp2 = frs->forassgn; stp2 != NULL; stp2 = stp2->stnxt)
     {
      if (stp2->stmttyp != S_FORASSGN) break;
      chk_nodel_stmt(stp2);
     }
    __chk_nodel_lstofsts(frs->forinc);
    __chk_nodel_lstofsts(frs->forbody);
   }
   break;
  /* illegal statements */
  case S_FUNCCALL:
  case S_TSKCALL:
   {
    struct expr_t *tkxp;

    tkxp = stp->st.stkc.tsksyx;
    /* $stop system tasks requires iact schedule */
    if (strcmp(tkxp->lu.sy->synam, "$stop") == 0) __iact_must_sched = TRUE;
    
    if ((tkxp->optyp == ID || tkxp->optyp == GLBREF)
     && *(tkxp->lu.sy->synam) != '$')
     {
      /* AIV 05/29/07 - the task that a task calls must be marked as */
      /* calling of a task */
      if (__compiled_sim)
       {
        if (tkxp->optyp == GLBREF) __task_has_xmrcall = TRUE;
        tskp = tkxp->lu.sy->el.etskp;
        if (__cur_tsk != NULL)
         {
          add_task_to_task_call(__cur_tsk, tskp);
         }
       }
      if (__checking_only) __task_has_tskcall = TRUE;
      else
       {
        __gferr(870, stp->stfnam_ind, stp->stlin_cnt,
         "user task %s enable illegal in function body", __to_idnam(tkxp));
       }
     }
   }
   break;
  /* for these check sub statement even though must have delay */
  case S_DELCTRL:
   if (stp->st.sdc->actionst != NULL)
    __chk_nodel_lstofsts(stp->st.sdc->actionst);
   goto bad_fdstmt;
  case S_WAIT:
   __chk_nodel_lstofsts(stp->st.swait.lpst);
   goto bad_fdstmt;
  case S_UNFJ: 
   { 
    int32 fji;
    struct st_t *fjstp;
    int32 sav_has_tskcall, has_timemove;

    has_timemove = FALSE;
    sav_has_tskcall = __task_has_tskcall;
    __task_has_delay = TRUE;
    __task_has_tskcall = FALSE;
    for (fji = 0;; fji++)
     {
      if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
      __chk_nodel_lstofsts(fjstp);
      if (__task_has_delay || __task_has_tskcall) has_timemove = TRUE;
     }
#ifndef __CVC_RT__
    if (!has_timemove)
     {
      __gfwarn(606, stp->stfnam_ind, stp->stlin_cnt,
        "unnamed fork-join components probably have no time movement");
     }
#endif
    if (!__task_has_tskcall) __task_has_tskcall = sav_has_tskcall;
    /* always has time fork-join always has time move since needs threads */ 
   }
   goto bad_fdstmt;
  /* non blocking procedural assign implies time movement so can not */
  /* be in function that is execed outside of time */ 
  case S_NBPROCA:
  /* these are simple delay statements */
  case S_CAUSE:
bad_fdstmt:
   if (__checking_only) __task_has_delay = TRUE;
   else
    {
     __gferr(870, stp->stfnam_ind, stp->stlin_cnt,
      "%s illegal in function body", __to_sttyp(s1, stp->stmttyp));
    }
   break;
  /* possibly illegal statements */
  case S_NAMBLK:
   /* legal except for fork */
   {
    struct task_t *nbtskp;
    int32 sav_has_delay, sav_has_tskcall;

    sav_has_delay = __task_has_delay;
    sav_has_tskcall = __task_has_tskcall;
    __task_has_delay = FALSE;
    __task_has_tskcall = FALSE;
    nbtskp = stp->st.snbtsk;
    __push_nbstk(stp);
    if (nbtskp->tsktyp == FORK)
     {
      int32 fji;
      int32 has_timemove;
      struct st_t *stp2;
      struct st_t *fjstp;

      stp2 = nbtskp->tskst;
      has_timemove = FALSE;
      /* named fork-join is task with 1 UNFJ statement */
      for (fji = 0;; fji++)
       {
        if ((fjstp = stp2->st.fj.fjstps[fji]) == NULL) break;
        __chk_nodel_lstofsts(fjstp);
        if (__task_has_delay || __task_has_tskcall) has_timemove = TRUE;
       }
#ifndef __CVC_RT__
      if (!has_timemove)
       {
        __gfwarn(606, stp->stfnam_ind, stp->stlin_cnt,
         "named fork-join components probably have no time movement");
       }
#endif
      if (!__task_has_tskcall) __task_has_tskcall = sav_has_tskcall;
      goto bad_fdstmt;
     }
    __chk_nodel_lstofsts(nbtskp->tskst);
    /* AIV 03/10/09 - need to set if task as delay or not */
    nbtskp->no_delay = !__task_has_delay;
    if (!__task_has_delay) __task_has_delay = sav_has_delay;
    /* AIV 12/12/07 - need to set the uses scope flag for name blocks */
    nbtskp->uses_scope = __disp_uses_scope;
    if (__task_has_tskcall) nbtskp->thas_tskcall = TRUE;
    else __task_has_tskcall = sav_has_tskcall;
    __pop_nbstk();
   }
   break;
  case S_UNBLK:
   /* must check statements below */
   {
    struct st_t *stp2;

    for (stp2 = stp->st.sbsts; stp2 != NULL; stp2 = stp2->stnxt) 
     chk_nodel_stmt(stp2);
   }
   break;
  case S_DSABLE:
   /* this may or may not be a delay */
   chk_nodel_dsable(stp);
   break;
   case S_INC: case S_DEC: break;
   case S_BREAK: case S_CONTINUE: case S_RETURN: break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

static void add_task_to_task_call(struct task_t *from_tskp, 
 struct task_t *called_tskp)
{
 struct task_t *tskp, *tskp2;
 int32 i, j;

 /* AIV 05/29/07 - a task can disable itself */
 if (from_tskp == called_tskp) return;
 
//AIV 08/21/07 AIV FIXME
//task can disable the task that called it so need to check for
//notice this could be a performance problems and there are still bugs
//in the disable code in cvc
 for (i = 0; ; i++)
  {
   tskp = called_tskp->called_tasks[i];
   if (tskp == NULL) break;
   if (tskp == from_tskp) return;
   for (j = 0; ; j++)
    {
     tskp2 = tskp->called_tasks[j];
     if (tskp2 == NULL) break;
     if (tskp2 == from_tskp) return;
     if (tskp == tskp2) return;
    }
  }

 for (i = 0; ; i++)
  {
   tskp = from_tskp->called_tasks[i];
   if (tskp == called_tskp) return;
   if (tskp == NULL)
    {
     from_tskp->called_tasks[i] = called_tskp;
     return;
    }
  }
}

/*
 * check a function definition (body) disable 
 * think possibly here, can still optimize and avoid thread for tasks even
 * if they disable other tasks - but for now forcing thread.
 */
static void chk_nodel_dsable(struct st_t *stp)
{
 struct expr_t *dsxp;
 struct sy_t *syp;
 int32 dummy;

 /* task disable illegal - named block ok if above in func. body */
 dsxp = stp->st.sdsable.dsablx;
 /* assume above */
 syp = dsxp->lu.sy;
 if (syp->sytyp == SYM_TSK)
  {
   if (__checking_only)
    {
     /* if disabling current task still above */
     if (syp->el.etskp != __cur_tsk) goto set_has_del;
     return;
    }
   __gferr(873, stp->stfnam_ind, stp->stlin_cnt,
    "task %s disable illegal in function body", __to_idnam(dsxp));
   return;
  }
 /* cannot disable anything outside of function also - qualified name */
 /* ok if within function */
 /* cannot disable anything not upward for function */
 if (dsxp->optyp == GLBREF)
  { 
   if (__checking_only) goto set_has_del;
   __gferr(874, stp->stfnam_ind, stp->stlin_cnt,
    "disable of cross module reference %s illegal in function", 
    __to_idnam(dsxp));
   return;
  }   
 /* if called from func., ok to disable function name */
 if (syp->sytyp == SYM_F)
  {
   if (syp->el.etskp != __cur_tsk)
    {
     if (__checking_only) goto set_has_del;

     __gferr(866, stp->stfnam_ind, stp->stlin_cnt,
      "disable of function %s illegal inside other function %s", 
      __to_idnam(dsxp), __cur_tsk->tsksyp->synam);
    }
   return;
  }
 /* OK to disable function from within body */
 if (__nbsti >= 0 && __is_upward_dsable_syp(syp,
  __nbstk[__nbsti]->st.snbtsk->tsksymtab, &dummy)) return;
 if (__checking_only) goto set_has_del;

 __gferr(875, stp->stfnam_ind, stp->stlin_cnt,
  "disable of non enclosing named block %s inside function %s illegal",
  __msgexpr_tostr(__xs, dsxp), __locfnamsyp->synam);
 return;

set_has_del:
 __task_has_delay = TRUE;
}

/*
 * return T if lhs expression contains lhs symbol
 */
static int32 lhsexpr_hassym(struct expr_t *ndp, struct sy_t *syp)
{
 struct expr_t *ndp2;

 switch (ndp->optyp) {
   case ID:
    if (ndp->lu.sy == syp) return(TRUE);
    break;
   case GLBREF: case NUMBER: case REALNUM: break;
   case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
    if (ndp->lu.x->lu.sy == syp) return(TRUE);
    break;
   case LCB:
    /* know only 1 level of lhs concatenates (at least by here) */
    for (ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
     {
      /* widths get set after checking */
      if (ndp2->lu.x->lu.sy == syp) return(TRUE);
     }
    break;
   default: __case_terr(__FILE__, __LINE__);
  }
 return(FALSE);
}

/*
 * RANGE MANIPULATION ROUTINES
 */

/*
 * get width of net - cannot be called unless n_isavec is TRUE 
 * used when know vector width needed even if array 
 *
 * notice always know range is no inst. specific - if defparam in
 * in range assigned to must really split.
 */
extern int32 __get_netwide(struct net_t *np)
{
 int32 i1, i2, wid;

 if (!np->n_isavec) return(1);  

 i1 = i2 = 0;
 if (np->nrngrep == NX_CT)
  {
   i1 = (int32) __contab[np->nu.ct->nx1->ru.xvi];
   i2 = (int32) __contab[np->nu.ct->nx2->ru.xvi];

   /* AIV 02/24/10 - LRM allows negative indices */
   /* if (i1 == -1 || i2 == -2) __arg_terr(__FILE__, __LINE__); */
   wid = (i1 >= i2) ? (i1 - i2 + 1) : (i2 - i1 + 1);
   return(wid);
  }
 return(np->nwid);
}

/*
 * get array width (i.e. width of range or number of elements in memory) 
 * this is number of elements
 */
extern int32 __get_arrwide(struct net_t *np)
{
 int32 w1, w2, twid, dawid, i;
 struct mda_t *mdap;

 /* if mdat compute the size of all the dimensions of the array */
 if ((mdap = np->mda) != NULL)
  {
   __getarr_range_mda(np, &w1, &w2, &twid, 0);
   for (i = 1; i < mdap->dimension; i++)
    {
     __getarr_range_mda(np, &w1, &w2, &dawid, i);
     twid *= dawid;
    }
   return(twid);
  }

 w1 = w2 = 0;
 switch ((byte) np->nrngrep) {
  case NX_CT:
   w1 = (int32) __contab[np->nu.ct->ax1->ru.xvi];
   w2 = (int32) __contab[np->nu.ct->ax2->ru.xvi];
   break;
  case NX_ARR:
   w1 = np->nu.rngarr->ai1;
   w2 = np->nu.rngarr->ai2;
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return((w1 >= w2) ? (w1 - w2 + 1) : (w2 - w1 + 1));
}

/*
 * get vector range extremes independent of representation 
 * (for both compile and run times)  
 * this can only be called for known vector not scalar
 *
 * returns false if cannot determine range (unfolded still)
 * this will return vector width of array
 * must use bit to determine if vector or not 
 */
extern void __getwir_range(struct net_t *np, int32 *xr1, int32 *xr2)
{
 int32 r1, r2;

 r1 = r2 = 0;
 switch ((byte) np->nrngrep) {
  case NX_CT:
   r1 = (int32) __contab[np->nu.ct->nx1->ru.xvi];
   r2 = (int32) __contab[np->nu.ct->nx2->ru.xvi];
   break;
  case NX_ARR: r1 = np->nu.rngarr->ni1; r2 = np->nu.rngarr->ni2; break;
  case NX_DWIR: r1 = np->nu.rngdwir->ni1; r2 = np->nu.rngdwir->ni2; break;
  case NX_WIR: r1 = np->nu.rngwir->ni1; r2 = np->nu.rngwir->ni2; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 *xr1 = r1;
 *xr2 = r2;
}

/*
 * run time get array range extremes independent of representation 
 * must use bit to determine if array or not
 *
 * returns false if cannot determine range (unfolded still)
 * this will return array width of array
 */
extern void __getarr_range(struct net_t *np, int32 *mr1, int32 *mr2, 
 int32 *arrwid)
{
 int32 r1, r2;

 r1 = r2 = 0;
 /* notice fall thru on things with no array range */
 switch ((byte) np->nrngrep) {
  case NX_CT:
   if (np->n_isarr)
    {
     r1 = (int32) __contab[np->nu.ct->ax1->ru.xvi];
     r2 = (int32) __contab[np->nu.ct->ax2->ru.xvi];
    }
   break;
  case NX_ARR: r1 = np->nu.rngarr->ai1; r2 = np->nu.rngarr->ai2; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 *arrwid = (r1 > r2) ? r1 - r2 + 1 : r2 - r1 + 1;
 *mr1 = r1;
 *mr2 = r2;
}

/*
 * get the range of the multi-dim array for one dimension
 * passed dimension is dim
 */
extern void __getarr_range_mda(struct net_t *np, int32 *mr1, int32 *mr2, 
 int32 *arrwid, int32 dim)
{
 int32 r1, r2;
 struct mda_t *mdap;

 r1 = r2 = 0;
 mdap = np->mda; 
 /* notice fall thru on things with no array range */
 switch ((byte) np->nrngrep) {
  case NX_CT:
   r1 = (int32) __contab[mdap->tab_ax1[dim]->ru.xvi];
   r2 = (int32) __contab[mdap->tab_ax2[dim]->ru.xvi];
   break;
  case NX_ARR: 
   r1 = mdap->rng1[dim];
   r2 = mdap->rng2[dim];
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 *arrwid = (r1 > r2) ? r1 - r2 + 1 : r2 - r1 + 1;
 *mr1 = r1;
 *mr2 = r2;
}

/*
 * routine to map normalized h:0 form index back to input value
 * know indi in range and wire type determines if array or wire select
 */
extern int32 __unnormalize_ndx(struct net_t *np, int32 indi)
{
 int32 r1, r2, obwid;

 if (np->n_isarr) __getarr_range(np, &r1, &r2, &obwid);
 else if (np->n_isavec) __getwir_range(np, &r1, &r2);
 else return(indi); 
 if (r1 >= r2) return(r2 + indi); else return(r2 - indi);
}

/*
 * routine to map normalized h:0 form index back to input value
 * 2nd variant for multi-dim arrays where must pass the range
 */
extern int32 __unnormalize2_ndx(int32 indi, int32 mr1, int32 mr2)
{
 if (mr1 >= mr2) return(mr2 + indi);
 else return(mr2 - indi);
}

/*
 * map normalized h:0 constant index to value in source world
 * already processed to word32 and know in range 
 *
 * just like C implied truncating assign to 32 bit value
 * constants are already normalized during compilation
 */
extern int32 __unmap_ndx(int32 biti, int32 ri1, int32 ri2)
{
 if (ri1 >= ri2) { if (ri1 != 0) biti -= ri2; }
 else { if (ri2 != 0) biti = ri2 - biti; }
 return(biti);
}

/*
 * VARIABLE INITIALIZE ASSIGNMENT CHECKING ROUTINES
 */

/*
 * check a module's var init rhs exprs
 */
static void chk_varinits(void)
{
 struct varinitlst_t *initp;

 initp = __inst_mod->mvarinits;
 for (; initp != NULL; initp = initp->varinitnxt)
  {
   __sfnam_ind = initp->init_syp->syfnam_ind;
   __slin_cnt = initp->init_syp->sylin_cnt;

   if (!__chk_paramexpr(initp->init_xp, initp->init_syp->el.enp->nwid))
    {
     __sgferr(3431,
      "variable assign to %s initializing expression %s illegal - numbers and parameters only",
      initp->init_syp->synam, __msgexpr_tostr(__xs, initp->init_xp));

     /* need to still add value of x to prevent further errors */
     __free2_xtree(initp->init_xp);
     /* SJM 09/30/04 - LOOKATME - maybe needs to be right width x's */
     initp->init_xp->szu.xclen = 1;
     __set_numval(initp->init_xp, ALL1W, ALL1W, 1);
    }
  }
}

/* 
 * STATEMENT CHECKING ROUTINES
 */


/*
 * routines to check fix up statements
 */
static void chk_stmts(void)
{
 struct ialst_t *ialp;

 for (ialp = __inst_mod->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   __ia_has_vpicall = FALSE;
   __cur_tsk = NULL;
   __chk_lstofsts(ialp->iastp);
   /* also check no del statement lists to set various task/block bits */
   __task_has_delay = FALSE;
   __task_has_tskcall = FALSE;
   __nbsti = -1;
   __chk_nodel_lstofsts(ialp->iastp);
   /* AIV 03/24/09 - for now all PLI calls must use thread */
   if (__pli_access_level && !ialp->needs_thread)
    {
     ialp->needs_thread =  __ia_has_vpicall;
    }
   __ia_has_vpicall = FALSE;
  } 
}

/*
 * check a statement list
 */
extern void __chk_lstofsts(struct st_t *hdstp)
{
 struct st_t *stp;

 /* notice legal empty statement list just does nothing here */
 for (stp = hdstp; stp != NULL; stp = stp->stnxt) chk_1stmt(stp);
}

/*
 * check 1 statement
 */
static void chk_1stmt(struct st_t *stp)
{
 int32 save_lno, save_fni, cwid, is_regform, tmp, save_no_warns;
 struct xstk_t *xsp;
 struct expr_t *rhsx, *condx, *lhsx;
 struct net_t *np;
 struct st_t *snull;
 int32 inc;
 struct st_t *nxtstp;
 struct delctrl_t *dctp;

 /* save callers values */
 save_fni = __sfnam_ind;
 save_lno = __slin_cnt;
 __sfnam_ind = stp->stfnam_ind;
 __slin_cnt = stp->stlin_cnt;

 switch ((byte) stp->stmttyp) {
  case S_NULL: case S_STNONE: break;
  /* if delay prefix action part of delay control */
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA:
   __chk_lhsexpr(stp->st.spra.lhsx, LHS_PROC);
#ifndef __CVC_RT__
   if (stp->st.spra.lhsx->optyp == LCB && stp->st.spra.lhsx->szu.xclen == 1)
    __sgfwarn(542, "procedural assign lvalue 1 bit concatenate unusual");
#endif
   /* AIV 05/12/09 - special case must check for part select of one dim */
   /* array access of +: or -: this parses but cannot use +: for array */
   /* multiple dimension checks correctly */
   rhsx = stp->st.spra.rhsx;
   if (rhsx->optyp == PARTSEL_NDX_MINUS || rhsx->optyp == PARTSEL_NDX_PLUS)
    {
     np = rhsx->lu.x->lu.sy->el.enp;
     /* one dimension array must be bsel or psel */
     if (np->n_isarr)
      {
       __sgferr(3508, "array access of one dimension cannot be access with an indexed part select on array %s", np->nsym->synam);
      }
    }
   cwid = stp->st.spra.lhsx->szu.xclen;
   __chk_rhsexpr(rhsx, cwid);

   /* SJM 10/08/04 - for Ver 2001 because WBITS can be 64 - must widen */
   /* unsized constant (unsiznum bit in expr rec on) to lhs width */
   /* AIV 01/04/10 - this also needs to handle new SV '1 case */ 
   lhsx = stp->st.spra.lhsx;
   if (rhsx->optyp == NUMBER && rhsx->szu.xclen < lhsx->szu.xclen)
    {
     if (rhsx->unbas_unsiz_num)
      {
       stp->st.spra.rhsx = __widen_sv_unbas_unsiz_rhs(rhsx, lhsx->szu.xclen);
      }
     else if (rhsx->unsiznum)
      {
       stp->st.spra.rhsx = __widen_unsiz_rhs_assign(rhsx, lhsx->szu.xclen);
      }
    }
   break;
  case S_IF:
   condx = stp->st.sif.condx;
   __chk_rhsexpr(condx, 0);
   /* AIV 06/01/11 - if condition code is constant try to fold the else */
   /* statement list or suppress warns for if */
   /* this was getting warnings for unreachable generate code of things */
   /* being out of range but are really folded due to gen values */
   /* if (gi < PARAM) reg[i-1] = 1; */
#ifdef __XPROP__
   /* this ruins xprop2 which assumes the else x case is always there */
   if (__is_const_expr(condx) && !__xprop2)
#else
   if (__is_const_expr(condx))
#endif
    {
     save_no_warns = __no_warns;
     xsp = __eval_xpr(condx);
     if (xsp->xslen <= WBITS)
      {
       if (stp->st.sif.condx->is_real)
        {
         double d1;
         memcpy(&d1, xsp->ap, sizeof(double));
         tmp = (d1 != 0.0);
        }
       else tmp = ((xsp->ap[0] & ~xsp->bp[0]) != 0L);
      }
     else tmp = (__cvt_lngbool(xsp->ap, xsp->bp, wlen_(xsp->xslen)) == 1);

     /* if using interpreter just do not emit the warning messages */
     /* for the part of the if which is never reached */
     if (!__compiled_sim)
      {
       if (tmp) 
        {
         __chk_lstofsts(stp->st.sif.thenst);
         __no_warns = TRUE;
         if (stp->st.sif.elsest != NULL) __chk_lstofsts(stp->st.sif.elsest);
        }
       else
        {
         __no_warns = TRUE;
         __chk_lstofsts(stp->st.sif.thenst);
         __no_warns = save_no_warns;
         if (stp->st.sif.elsest != NULL) __chk_lstofsts(stp->st.sif.elsest);
        }
      }
     else
      {
       /* for compiler remove the statements - this helps because all */
       /* stmts for memory/code gen are never needed */

       /* if true - just make else case NULL */
       if (tmp) 
        {
         __chk_lstofsts(stp->st.sif.thenst);
         stp->st.sif.elsest = NULL;
        }
       else
        {
         /* if else case switch blocks and make condition always true */
         if (stp->st.sif.elsest != NULL)
          {
           __init_xnd(condx);
           condx->ru.xvi = __alloc_shareable_cval(1, 0, WBITS);
           condx->szu.xclen = WBITS;
           condx->optyp = NUMBER;
           stp->st.sif.thenst = stp->st.sif.elsest;
           stp->st.sif.elsest = NULL;
          }
         else
          {
           /* no else just empty block which is never reached - make NULL */
           snull = __alloc_stmt(S_NULL);
           stp->st.sif.thenst = snull;
          }
         __chk_lstofsts(stp->st.sif.thenst);
        }
      }
     __pop_xstk();
     __no_warns = save_no_warns;
    }
   else
    {
     /* not constant just do normal fixup */
     __chk_lstofsts(stp->st.sif.thenst);
     if (stp->st.sif.elsest != NULL) __chk_lstofsts(stp->st.sif.elsest);
    }
   break;
  case S_CASE:
   chk_case(stp);
   break;
  case S_WAIT:
   /* notice this is level sensitive condition cannot be event expr */
   /* DBG remove -- */
   if (stp->st.swait.lpx == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   __chk_rhsexpr(stp->st.swait.lpx, 0);
   if (__isleaf(stp->st.swait.lpx) && stp->st.swait.lpx->optyp != ID
    && stp->st.swait.lpx->optyp != GLBREF)
    __sgfinform(413, "wait expression constant - use loop");

   __chk_lstofsts(stp->st.swait.lpst);
   break;
  case S_FOREVER:
   __chk_lstofsts(stp->st.swh.lpst);
   break;
  case S_REPEAT:
   if (stp->st.srpt.repx != NULL)
    {
     __chk_rhsexpr(stp->st.srpt.repx, 0);
#ifndef __CVC_RT__
     if (stp->st.srpt.repx->szu.xclen > WBITS)
      __sgfwarn(543,
       "truncation of repeat count from %d to 32 bits - high bits ignored",
       stp->st.srpt.repx->szu.xclen);
#endif
    }
   else __sgferr(803, "required repeat statement repeat count missing");
   __chk_lstofsts(stp->st.srpt.repst);
   break;
  case S_WHILE:
  case S_DO_WHILE:
   if (stp->st.swh.lpx != NULL)
    {
     __chk_rhsexpr(stp->st.swh.lpx, 0);
     /* SJM 04/05/02 - this warning is wrong - while not truncated - REMOVED */
     /* --- 
     if (stp->st.swh.lpx->szu.xclen > WBITS)
      __sgfwarn(544,
       "truncation of while expression from %d to 32 bits - high bits ignored",
       stp->st.swh.lpx->szu.xclen);
     --- */
    }
   else __sgferr(804, "while statement required while expression missing");
   __chk_lstofsts(stp->st.swh.lpst);
   break;
  case S_FOR:
   {
    struct for_t *frs;
    struct st_t *stp2;
    struct mda_t *mdap;
    int32 ri1, ri2, arrwid, dim;

    /* notice for statement must use temporaries of right width */
    frs = stp->st.sfor;
    /* AIV 10/13/10 - if expanded from a foreach stmt - need extra checking */
    if (frs->is_expanded_foreach)
     {
      /* passed net better be an array */
      if (frs->foreach_syp->sytyp != SYM_N)
       {
        __sgferr(4860, "foreach statement variable (%s) is not an array", 
         frs->foreach_syp->synam);
        break;
       }
      np = frs->foreach_syp->el.enp;
      if (!np->n_isarr)
       {
        __sgferr(4860, "foreach statement variable (%s) is not an array", 
         np->nsym->synam);
        break;
       }

      /* if mda - get dimension */
      if ((mdap = np->mda) != NULL) 
       {
        __getarr_range_mda(np, &ri1, &ri2, &arrwid, frs->dim);
        dim = mdap->dimension;
       }
      else 
       {
        dim = 1;
        __getarr_range(np, &ri1, &ri2, &arrwid);
       }

      /* make sure not too many dimensions */
      if (frs->dim > dim)
       {
        __sgferr(4862, "foreach statement access too many dimesions %d for array (%s) of %d dimension ", frs->dim, dim, np->nsym->synam);
       }
      /* DBG remove -- */
      if (frs->fortermx->optyp != RELGE) __misc_terr(__FILE__, __LINE__);
      /* ---- */
      /* if ri2 > ri1 need to swap the compare stop loop optyp to <= */
      if (ri2 > ri1) frs->fortermx->optyp = RELLE;
     }
    /* AIV 10/01/10 - for assign can now have multiple - cannot use */
    /* list because is linked onto forbody */
    for (stp2 = frs->forassgn; stp2 != NULL; stp2 = stp2->stnxt)
     {
      if (stp2->stmttyp != S_FORASSGN) break;
      chk_1stmt(stp2);
     }
    if (frs->fortermx != NULL) __chk_rhsexpr(frs->fortermx, 0);
    __chk_lstofsts(frs->forinc);
    __chk_lstofsts(frs->forbody);
   }
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   nxtstp = dctp->actionst;
   inc = 0;
   /* AIV 03/03/09 - must mark dctrl if it has a nested blocking delctrl */
   /* when attempting to merge always @(egde) blocks cannot merge those */
   /* which contain a blocking delay (can merge '<= #' but not '= #' ) */
   /* inc only those which are blocking */
   switch (dctp->dctyp) {
    case DC_DELAY: case DC_EVENT:
      inc = TRUE;
      break;
    case DC_RHSDELAY:
     if (nxtstp->stmttyp == S_NBPROCA) inc = FALSE;
     else inc = TRUE;
     break;
    case DC_RHSEVENT:
     if (nxtstp->stmttyp == S_NBPROCA) inc = FALSE;
     else inc = TRUE;
     break;
   }
   __dctrl_depth += inc; 

   chk_dctrl(dctp);

   __dctrl_depth -= inc;
   /* back to top level delctrl mark the bit */
   if (__dctrl_depth == 0)
    {
     if (__nested_dctrl) 
      {
       dctp->nested_dctrl = TRUE;
       __nested_dctrl = FALSE; 
      }
    }
   else if (inc) __nested_dctrl = TRUE; 
   break;
  case S_NAMBLK:
   __chk_lstofsts(stp->st.snbtsk->tskst);
   break;
  case S_UNBLK:
   __chk_lstofsts(stp->st.sbsts);
   break;
  case S_UNFJ:
   {
    int32 fji;
    struct st_t *fjstp;

    /* 1 sub stmt only, for unnamed begin-end will be unnamed block */ 
    for (fji = 0;; fji++)
     {
      if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
      /* SJM 09/24/01 - this can be 2 stmts for for (for assgn then for) */
      __chk_lstofsts(fjstp);
     }
   }
   break;
  case S_FUNCCALL:
  case S_TSKCALL:
   __chk_tskenable(stp);
   break;
  case S_QCONTA:
   /* quasi-continuous assign is either proc. assign or force */
   chk_qclvalue(stp->st.sqca->qclhsx, stp->st.sqca->qcatyp, &is_regform);
   __set_lhswidth(stp->st.sqca->qclhsx);
   cwid = stp->st.sqca->qclhsx->szu.xclen;
   __chk_rhsexpr(stp->st.sqca->qcrhsx, cwid);
   stp->st.sqca->regform = is_regform;

   rhsx = stp->st.sqca->qcrhsx;
   lhsx = stp->st.sqca->qclhsx;
   /* SJM 10/08/04 - for Ver 2001 because WBITS can be 64 - must widen */
   /* unsized constant (unsiznum bit in expr rec on) to lhs width */
   /* AIV 01/04/10 - this also needs to handle new SV '1 case */ 
   if (rhsx->optyp == NUMBER && rhsx->szu.xclen < lhsx->szu.xclen)
    {
     if (rhsx->unbas_unsiz_num)
      {
       stp->st.sqca->qcrhsx = __widen_sv_unbas_unsiz_rhs(rhsx, lhsx->szu.xclen);
      }
     else if (rhsx->unsiznum)
      {
       stp->st.sqca->qcrhsx = __widen_unsiz_rhs_assign(rhsx, lhsx->szu.xclen);
      }
    }

   /* SJM 07/16/03 - illegal if rhs expr. contains lhs being forced lvalue */ 
   chk_circular_qc_stmt(stp);
   break;
  case S_QCONTDEA:
   /* quasi-continuous deassign is either proc. deassign or release */
   chk_qclvalue(stp->st.sqcdea.qcdalhs, stp->st.sqcdea.qcdatyp, &is_regform);
   __set_lhswidth(stp->st.sqcdea.qcdalhs);
   stp->st.sqcdea.regform = is_regform;
   break;
  case S_DSABLE:
   chk_disable(stp);
   break;
  case S_CAUSE:
   {
    struct expr_t *ndp;
    struct sy_t *syp;
    struct net_t *np2;

    ndp = stp->st.scausx;
    if (ndp->optyp != GLBREF && ndp->optyp != ID)
     {
      __sgferr(806, "cause argument %s must be simple event name",
       __msgexpr_tostr(__xs, ndp));
      break;
     }
    syp = ndp->lu.sy;
    if (syp->sytyp == SYM_N) np2 = syp->el.enp; else np2 = NULL;
    if (syp->sytyp != SYM_N || np2->ntyp != N_EVENT)
     {
      if (np2 == NULL) __to_sytyp(__xs, syp->sytyp);
      else __to_wtnam(__xs, np2);
      __sgferr(807,
       "cause right hand side symbol \"%s\" type %s is not an event",
       __to_idnam(ndp), __xs);
     }
    /* cause is lhs assign for event */
    if (np2->nrngrep == NX_CT) np2->nu.ct->n_onlhs = TRUE;
   }
   break;
   case S_INC: case S_DEC:
    __chk_lhsexpr(stp->st.spra.lhsx, LHS_PROC);
    break;
   case S_BREAK: case S_CONTINUE: case S_RETURN:
    break;
   default: __case_terr(__FILE__, __LINE__);
  }
 /* restore callers values */
 __sfnam_ind = save_fni;
 __slin_cnt = save_lno;
}

/*
 * routine to widen unsized number to lhs context
 *
 * know only called for literal numbers - maybe literal from folding
 * and think folded bit will be on for all but fcalls but not using
 *
 * this is special widen with x/z extend in addition to sign extend
 * but if word32, does not extend the high 1 
 *
 * needed from Ver 2001 change because WBITS can now be 64 so for
 * any of the assigns (proc, cont, func/task input and force/assign)
 * need to use lhs context to widen unsized number to that size
 * with sign and x/z extend
 */
extern struct expr_t *__widen_unsiz_rhs_assign(struct expr_t *rhsx,
 int32 lhswid)
{
 int32 owlen, bi;
 word32 *owp;
 struct xstk_t *xsp;

 owlen = wlen_(rhsx->szu.xclen);
 push_xstk_(xsp, rhsx->szu.xclen);
 owp = &(__contab[rhsx->ru.xvi]);
 memcpy(xsp->ap, owp, 2*owlen*WRDBYTES);

 /* notice not lhs signed because signed does not corss = */
 if (rhsx->has_sign) __sgn_xtnd_widen(xsp, lhswid);
 else
  {
   /* if x/z - b part high bit on, then widen both a and b parts */
   bi = get_bofs_(rhsx->szu.xclen - 1);
   if ((xsp->bp[owlen - 1] & (1UL << bi)) != 0) 
    {
     /* notice since x/z bit on - can treat as sign extend widen since */
     /* reduces to x/z widen case */
     __sgn_xtnd_widen(xsp, lhswid);
    }
  }
 rhsx = bld_num_expr(xsp);
 __pop_xstk();
 return(rhsx);
}

/*
 * widen a new SV '1/'0/'x/'z expression
 */
extern struct expr_t *__widen_sv_unbas_unsiz_rhs(struct expr_t *rhsx, 
 int32 lhswid)
{
 int32 owlen, sval, wlen;
 word32 *owp, *obwp;
 struct xstk_t *xsp;

 owlen = wlen_(rhsx->szu.xclen);
 owp = &(__contab[rhsx->ru.xvi]);
 obwp = &(owp[owlen]);

 sval = (owp[0] | (obwp[0] << 1));
 push_xstk_(xsp, lhswid);
 wlen = wlen_(lhswid);
 switch (sval) {
  case 0:
   memset(xsp->ap, 0, 2*wlen*WRDBYTES);
   break;
  case 1:
   memset(xsp->ap, 0xff, wlen*WRDBYTES);
   memset(xsp->bp, 0, wlen*WRDBYTES);
   break;
  case 2:
   memset(xsp->ap, 0, wlen*WRDBYTES);
   memset(xsp->bp, 0xff, wlen*WRDBYTES);
   break;
  case 3:
   memset(xsp->ap, 0xff, wlen*WRDBYTES);
   memset(xsp->bp, 0xff, wlen*WRDBYTES);
   break;
  default : __case_terr(__FILE__, __LINE__); break;
 }

 /* create new number expr */
 rhsx = bld_num_expr(xsp);
 rhsx->unbas_unsiz_num = TRUE;
 __pop_xstk();
 return(rhsx);
}

/*
 * check a case statement
 *
 * SJM 05/10/04 - new algorithm turns off sign bit for widening if needed
 * for * every expression if select expr word32, if select expr signed
 * then compares are signed if match signed else unsigned
 */
static void chk_case(struct st_t *stp)
{
 int32 xwid, maxselwid, nd_realcnv, nd_unsgn_widen;
 struct csitem_t *csip;
 struct exprlst_t *xplp;
 struct csitem_t *dflt_csip;

 dflt_csip = stp->st.scs.csitems;
 /* first find maximum selection expression width */
 csip = dflt_csip->csinxt;
 for (maxselwid = 0; csip != NULL; csip = csip->csinxt)
  {
   /* check each expression in possible list */
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     xwid = __get_rhswidth(xplp->xp);
     if (xwid > maxselwid) maxselwid = xwid;
    }
  }
 /* including selector itself */
 xwid = __get_rhswidth(stp->st.scs.csx);

 if (xwid > maxselwid) maxselwid = xwid;
 stp->st.scs.maxselwid = (word32) maxselwid;

 /* now check expression using max. width context */
 for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
  {
   /* check each expression in possible list */
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     __chk_rhsexpr(xplp->xp, maxselwid);
    }
   /* this must be a statement (at least null) */
   __chk_lstofsts(csip->csist);
  }
 __chk_rhsexpr(stp->st.scs.csx, maxselwid);

 if (dflt_csip->csist != NULL) __chk_lstofsts(dflt_csip->csist);

#ifdef __XPROP__
 /* AIV 08/02/11 - now might have xprop list to process as well */
 if (stp->st.scs.xprop_lstp != NULL)
  {
   __chk_lstofsts(stp->st.scs.xprop_lstp);
  }
#endif

 /* SJM 12/12/03 - because real bit only turned on when rhs expr chk called */ 
 /* must set the real bits after do all other checking */
 /* one pass sets the flag if any expr real (select or case item) */
 csip = dflt_csip->csinxt;
 nd_unsgn_widen = FALSE;
 for (nd_realcnv = FALSE; csip != NULL; csip = csip->csinxt)
  {
   /* check each expression in possible list */
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     if (xplp->xp->is_real) nd_realcnv = TRUE;
     if (!xplp->xp->has_sign) nd_unsgn_widen = TRUE;
    }
  }
 if (stp->st.scs.csx->is_real) nd_realcnv = TRUE;
 if (stp->st.scs.csx->has_sign) nd_unsgn_widen = TRUE;

 if (!nd_realcnv && !nd_unsgn_widen) return;

 for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
  {
   /* check each expression in possible list */
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     if (nd_realcnv)
      {
       if (!xplp->xp->is_real)
        {
         xplp->xp->cnvt_to_real = TRUE;
         /* SJM 12-02-12 - if converting expr to real (not real itself) must */
         /* set widths underneath shielding (no) context if present */
         __set_rhswidth(xplp->xp, 0);
       } 
      }
     if (nd_unsgn_widen)
      {
       if (xplp->xp->has_sign) xplp->xp->unsgn_widen = TRUE;
      }
    }
  }
 if (nd_realcnv)
  {
   if (!stp->st.scs.csx->is_real)
    {
     stp->st.scs.csx->cnvt_to_real = TRUE;
     /* SJM 12-02-12 - if converting expr to real (not real itself) must */
     /* set widths underneath shielding (no) context if present */
     __set_rhswidth(stp->st.scs.csx, 0);
    }
  } 
 if (nd_unsgn_widen)
  {
   if (stp->st.scs.csx->has_sign) stp->st.scs.csx->unsgn_widen = TRUE;
  } 
}

/*
 * check a delay control statement
 */
static void chk_dctrl(struct delctrl_t *dctp)
{
 int32 sav_ecnt;
 struct paramlst_t *dhdr;

 /* even if error keeep checking - also know list has exactly 1 element */
 if (dctp->dctyp == DC_EVENT || dctp->dctyp == DC_RHSEVENT)
  {
   /* SJM 06/01/04 - if implicit list form "@(*)" no expr to check */
   if (!dctp->implicit_evxlst)
    {
     __chk_evxpr(dctp->dc_du.pdels->plxndp);
    }
  }
 /* pound form normal rhs expression checked here */
 /* notice delay controls even if numbers scaled at execution time */
 /* always only and at least 1 value */  
 else 
  {
   dhdr = __copy_dellst(dctp->dc_du.pdels);
   __chk_delparams(dhdr, "procedural delay control", FALSE);
   __free_dellst(dhdr);
  }

 if (dctp->repcntx != NULL)
  {
   __chk_rhsexpr(dctp->repcntx, 0);

#ifndef __CVC_RT__
   if (dctp->repcntx->szu.xclen > WBITS)
    {
     __sgfwarn(543,
      "truncation of right hand side event control repeat count from %d to 32 bits - high bits ignored",
      dctp->repcntx->szu.xclen);
    }
#endif
  }

 sav_ecnt = __pv_err_cnt;
 /* for RHS delay control know is assign, else can be spliced up list */
 /* algorithm here is bottom up because this may process implicit @* forms */
 if (dctp->actionst != NULL) __chk_lstofsts(dctp->actionst);

 /* final step (must be done after statement checking) build the */ 
 /* all rhs form evxpr list */ 
 if (dctp->implicit_evxlst)
  {
   /* if errors in stmts can't build this list - make it empty */
   if (sav_ecnt > __pv_err_cnt)
    {
#ifndef __CVC_RT__
     __sgfwarn(3134, "implicit @(*) event control action statement has syntax errors - can't build implicit change list");
     __bld_unc_expr();
     dctp->dc_du.pdels->plxndp = __root_ndp;
#endif
     return;
    }
   if (dctp->actionst == NULL) 
    {
#ifndef __CVC_RT__
     __sgfwarn(3135, "implicit @(*) event control no action statement - no implicit change list");
     __bld_unc_expr();
     dctp->dc_du.pdels->plxndp = __root_ndp;
#endif
     return;
    }

   /* if nothing in list - expr become op empty and no triggers */
   __impl_evlst_hd = __impl_evlst_tail = NULL; 
   /* AIV 07/16/12 - if always_comb/always_latch - must include */
   /* function values as well */
   bld_stlst_evxlst(dctp->actionst, dctp->dc_is_always_comb_latch);
   if (__impl_evlst_hd != NULL)
    {
     dctp->dc_du.pdels->plxndp = bld_evlst_comma_expr();
     __impl_evlst_hd = __impl_evlst_tail = NULL; 

     /* SJM 08/03/04 - can't call check here because building normalized */
     /* to h:0 expressions but check uses actual src read decl ranges */ 
    }
  }
}

/*
 * bld the list of change ev xpr lists - check for duplicates
 */
static void bld_stlst_evxlst(struct st_t *hdstp, int32 include_func)
{
 struct st_t *stp;

 /* notice legal empty statement list just does nothing here */
 for (stp = hdstp; stp != NULL; stp = stp->stnxt)
  {
   bld_stmt_evxlst(stp, include_func);
  }
}

/*
 * build the evxprlist for the action stmt for one @(*) implicit ev ctrl
 *
 * this must be run after the action stmt is checked for syntax errors
 * this must be run before pass 3 v prp because of for loops
 */
static void bld_stmt_evxlst(struct st_t *stp, int32 include_func)
{
 switch ((byte) stp->stmttyp) {
  case S_NULL: case S_STNONE: break;
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA:
   /* know if lhs IS form bit or array select - will be split */
   bld_lhs_impl_evxlst(stp->st.spra.lhsx, include_func);
   bld_rhs_impl_evxlst(stp->st.spra.rhsx, include_func);
   break;
  case S_IF:
   bld_rhs_impl_evxlst(stp->st.sif.condx, include_func);
   bld_stlst_evxlst(stp->st.sif.thenst, include_func);
   /* AIV 04/09/08 - was only checking the first stmt here need to check */
   /* all the statements on the else list */
   if (stp->st.sif.elsest != NULL) 
    bld_stlst_evxlst(stp->st.sif.elsest, include_func);
   break;
  case S_CASE:
   /* case is special case because selection and case item expressions */ 
   /* need to be added to list */
   bld_case_evxlst(stp, include_func);
   break;
  case S_WAIT:
   bld_stlst_evxlst(stp->st.swait.lpst, include_func);
   break;
  case S_FOREVER:
   bld_stlst_evxlst(stp->st.swh.lpst, include_func);
   break;
  case S_REPEAT:
   if (stp->st.srpt.repx != NULL)
    {
     bld_rhs_impl_evxlst(stp->st.srpt.repx, include_func);
    }
   bld_stlst_evxlst(stp->st.srpt.repst, include_func);
   break;
  case S_WHILE:
  case S_DO_WHILE:
   if (stp->st.swh.lpx != NULL)
    {
     bld_rhs_impl_evxlst(stp->st.swh.lpx, include_func);
    }
   bld_stlst_evxlst(stp->st.swh.lpst, include_func);
   break;
  case S_FOR:
   {
    struct for_t *frs;
    struct st_t *stp2;

    /* notice for statement must use temporaries of right width */
    frs = stp->st.sfor;
    /* AIV 10/01/10 - for assign can now have multiple - cannot use */
    /* list because is linked onto forbody */
    for (stp2 = frs->forassgn; stp2 != NULL; stp2 = stp2->stnxt)
     {
      if (stp2->stmttyp != S_FORASSGN) break;
      bld_stmt_evxlst(stp2, include_func);
     }
    if (frs->fortermx != NULL) bld_rhs_impl_evxlst(frs->fortermx, include_func);
    bld_stlst_evxlst(frs->forinc, include_func);
    bld_stlst_evxlst(frs->forbody, include_func);
   }
   break;
  case S_DELCTRL:
   /* notice if implicit @(*) form event ctrl - implicit expr list */
   /* already built - but this needs to also add to any containing */
   /* list is union of all contained implicit dctrl lists */
   if (stp->st.sdc->actionst != NULL)
    {
     bld_stlst_evxlst(stp->st.sdc->actionst, include_func);
    }
   break;
  case S_NAMBLK:
   bld_stlst_evxlst(stp->st.snbtsk->tskst, include_func);
   break;
  case S_UNBLK:
   bld_stlst_evxlst(stp->st.sbsts, include_func);
   break;
  case S_UNFJ:
   {
    int32 fji;
    struct st_t *fjstp;

    /* 1 sub stmt only, for unnamed begin-end will be unnamed block */ 
    for (fji = 0;; fji++)
     {
      if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
      /* SJM 09/24/01 - this can be 2 stmts for for (for assgn then for) */
      bld_stlst_evxlst(fjstp, include_func);
     }
   }
   break;
  case S_FUNCCALL:
   /* this is func call side */
   /* AIV 07/16/12 - SV always_comb includes function body as well */ 
   if (include_func)
    {
     struct tskcall_t *tkcp;
     struct expr_t *tkxp;
     struct sy_t *fsyp;
     struct task_t *tskp;

     tkcp = &(stp->st.stkc);
     tkxp = tkcp->tsksyx;
     fsyp = tkxp->lu.sy;
     tskp = fsyp->el.etskp;
     bld_stmt_evxlst(tskp->tskst, TRUE);
    }
   /*FALLTHRU */
  case S_TSKCALL:
   /* task enable out ports are lhs exprs (but sel ndx needs to go in list) */
   /* does nothing for system tasks */
   bld_tskenable_evxlst(stp, include_func);
   break;
  case S_QCONTA: case S_QCONTDEA:
   /* SJM 06/01/04 - LOOKATME - think quasi-cont stmts can't cause triggers */
   /* because rhs changes outside of proc time */
   break;
  case S_DSABLE: case S_CAUSE:
   /* SJM 06/01/04 - LOOKATME - think cause is lhs expr here */
   break;
  case S_INC: case S_DEC:
   bld_lhs_impl_evxlst(stp->st.spra.lhsx, include_func);
   break;
  case S_BREAK: case S_CONTINUE: case S_RETURN:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * build case stmt evx lst - tricky because both select and case item 
 * expr must be added
 */
static void bld_case_evxlst(struct st_t *stp, int32 include_func)
{
 struct csitem_t *csip;
 struct exprlst_t *xplp;
 struct csitem_t *dflt_csip;

 /* first build expr list element for case select */
 bld_rhs_impl_evxlst(stp->st.scs.csx, include_func);

 dflt_csip = stp->st.scs.csitems;
 csip = dflt_csip->csinxt;
 for (;csip != NULL; csip = csip->csinxt)
  {
   /* then expr list element for each case item expr */
   /* usually will be constants so none will be added */
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     bld_rhs_impl_evxlst(xplp->xp, include_func);
    }
  }

 /* now check expression using max. width context */
 for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
  {
   /* check each expression in possible list */
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     bld_rhs_impl_evxlst(xplp->xp, include_func);
    }
   bld_stlst_evxlst(csip->csist, include_func);
   /* this must be a statement (at least null) */
  }
 if (dflt_csip->csist != NULL) bld_stlst_evxlst(dflt_csip->csist, include_func);
}

/*
 * build task enable stmt evx lst - output ports are lhs exprs here
 */
static void bld_tskenable_evxlst(struct st_t *stp, int32 include_func)
{
 struct expr_t *xp;
 struct tskcall_t *tkcp;
 struct sy_t *syp;
 struct task_t *tskp;
 struct task_pin_t *tpp;

 tkcp = &(stp->st.stkc);
 syp = tkcp->tsksyx->lu.sy;
 /* SJM 06/01/04 - think system task rhs should not go in sensitivity list */
 if (syp->sytyp == SYM_STSK) return;

 tskp = tkcp->tsksyx->lu.sy->el.etskp;
 tpp = tskp->tskpins;
 for (xp = tkcp->targs; xp != NULL; xp = xp->ru.x, tpp = tpp->tpnxt)
  {
   /* output port connections are lvalues but must trigger on any indices */
   if (tpp->trtyp == IO_OUT) bld_lhs_impl_evxlst(xp->lu.x, include_func);
   else bld_rhs_impl_evxlst(xp->lu.x, include_func);
  }
}

/*
 * build rhs impl event expr list - all vars, bsel and psels go in list
 *
 * SJM 06/01/04 ### ??? FIXME - right to assume not including XMRs
 */
static void bld_rhs_impl_evxlst(struct expr_t *rhsx, int32 include_func)
{
 struct expr_t *evxp;
 struct exprlst_t *xplp;
 struct expr_t *ndp2;
 struct sy_t *fsyp;
 struct task_t *tskp;

 switch (rhsx->optyp) {
  case ID:
  /* AIV 06/25/09 - was ignoring xmr here but need to add to list */
  case GLBREF:
   /* DBG remove -- */
   if (rhsx->lu.sy->el.enp->n_isaparam) __misc_terr(__FILE__, __LINE__);
   /* --- */
   goto add_expr;
  case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   bld_rhs_impl_evxlst(rhsx->ru.x->lu.x, include_func);
   goto add_expr;
  case LSB: case PARTSEL: 
add_expr:
   evxp = __copy_expr(rhsx);
   if (!xp_in_evxlst(evxp)) 
    {
     xplp = (struct exprlst_t *) __my_malloc(sizeof(struct exprlst_t));
     xplp->xp = evxp;
     xplp->xpnxt = NULL; 
     if (__impl_evlst_hd == NULL) __impl_evlst_hd = __impl_evlst_tail = xplp;
     else { __impl_evlst_tail->xpnxt = xplp; __impl_evlst_tail = xplp; }
    }
   break;
  case NUMBER: case ISNUMBER: case OPEMPTY:
  case REALNUM: case ISREALNUM:
   break;
  case QUEST:
   bld_rhs_impl_evxlst(rhsx->lu.x, include_func);
   bld_rhs_impl_evxlst(rhsx->ru.x->ru.x, include_func);
   bld_rhs_impl_evxlst(rhsx->ru.x->lu.x, include_func);
   break;
  case FCALL:
   /* this is func call side */
   /* AIV 07/16/12 - SV always_comb includes function body as well */ 
   if (include_func)
    {
     fsyp = rhsx->lu.x->lu.sy; 
     tskp = fsyp->el.etskp;
     bld_stmt_evxlst(tskp->tskst, TRUE);
    }
   for (ndp2 = rhsx->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
    {
     bld_rhs_impl_evxlst(ndp2->lu.x, include_func);
    }
   break; 
  case LCB:
   /* know by here concatenates only one level */
   for (ndp2 = rhsx->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
    {
     bld_rhs_impl_evxlst(ndp2->lu.x, include_func);
    }
   break; 
  default:
   /* handle unary or binary operators */
   /* DBG remove -- */
   if (rhsx->lu.x == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   bld_rhs_impl_evxlst(rhsx->lu.x, include_func);
   if (rhsx->ru.x != NULL) bld_rhs_impl_evxlst(rhsx->ru.x, include_func);
 }
}

/*
 * build lhs impl event expr list
 *
 * only variable bit select are rhs expr that need to go in list
 * must handle concats - otherwise only needs to look at bsel/arrsel 
 *
 * know all expr checking and folding completed before here
 */
static void bld_lhs_impl_evxlst(struct expr_t *lhsx, int32 include_func)
{
 struct expr_t *ndp2;

 switch (lhsx->optyp) {
  case ID: case GLBREF: case OPEMPTY: break;
  case LSB:
   /* only need to add variable selects of bit select or array select */
   if (lhsx->ru.x->optyp == NUMBER || lhsx->ru.x->optyp == ISNUMBER)
    break;
   /* DBG remove -- */
   if (__is_const_expr(lhsx->ru.x)) __misc_terr(__FILE__, __LINE__);
   /* --- */
   bld_rhs_impl_evxlst(lhsx->ru.x, include_func);
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   bld_rhs_impl_evxlst(lhsx->ru.x->lu.x, include_func);
   break;
  case PARTSEL:
   /* know ranges are constant */
   break;
  case LCB:
   /* know lhs concatenates never nested */
   for (ndp2 = lhsx->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
    {
     bld_lhs_impl_evxlst(ndp2->lu.x, include_func);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * return T if expr already in the ev xpr list  
 */
static int32 xp_in_evxlst(struct expr_t *evxp) 
{
 int32 has_xmr;
 struct exprlst_t *xplp;

 for (xplp = __impl_evlst_hd; xplp != NULL; xplp = xplp->xpnxt)
  {
   /* SJM 06/01/04 - ### ??? LOOKATME - is this expr compare right */ 
   if (__cmp_xpr(evxp, xplp->xp, &has_xmr)) return(TRUE);
  }
 return(FALSE);
}

/*
 * build implicit ev list comma expr from expr list
 *
 * notice needs to left associate and edges never appear
 */
static struct expr_t *bld_evlst_comma_expr(void)
{
 int32 first_time;
 struct exprlst_t *xplp;
 struct expr_t *rootndp, *ndp;
 struct exprlst_t *xplp2;

 first_time = TRUE;
 ndp = NULL;
 rootndp = NULL;
 for (xplp = __impl_evlst_hd; xplp != NULL; xplp = xplp->xpnxt)
  {
   if (first_time)
    {
     rootndp = xplp->xp;
     first_time = FALSE;
     continue;
    }
   ndp = __alloc_newxnd();
   ndp->optyp = OPEVCOMMAOR;
   ndp->lu.x = rootndp; 
   ndp->ru.x = xplp->xp;
   rootndp = ndp; 
  }
 /* DBG remove -- */
 if (__debug_flg) __dbg_msg("%s", __msgexpr_tostr(__xs, rootndp));
 /* -- */
 /* free the expr list but not the contained exprs */
 for (xplp = __impl_evlst_hd; xplp != NULL;)
  {
   xplp2 = xplp->xpnxt;
   __my_free(xplp, sizeof(struct exprlst_t));
   xplp = xplp2;
  }
 return(rootndp);
}

/*
 * STMT CHECKING ROUTINES FOR QC STMTS
 */

/*
 * check a quasi continous assign/deassign reg. or force wire or reg
 * most checks special qc reg concatenate form
 *
 * assuming here there are 2 disjoint32 forms - force [normal decl. lhs] or
 * force [assign style register form] - concatentates cannot mix the 2
 */
static void chk_qclvalue(struct expr_t *ndp, word32 qctyp,
 int32 *is_rgform)
{
 struct expr_t *ndp2;
 int32 cnt;
 char s1[RECLEN];

 *is_rgform = TRUE;
 /* one level concatenates for either reg or wire forms ok */
 /* for legal concatenate can not mix reg and wire elements */
 if (ndp->optyp == LCB)
  {
   for (cnt = 1, ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x,
    cnt++)
    {
     /* if this is normal declarative (wire only) lhs - must be force */
     if (!__xhas_reg(ndp2->lu.x))
      {
       if (qctyp != FORCE && qctyp != RELEASE)
        {
         __sgferr(808,
           "%s concatenate lvalue (pos. %d) contains wires - use force/release",
          __to_qctyp(s1, qctyp), cnt);
         return;
        }
       if (cnt == 1) *is_rgform = FALSE;
       else if (*is_rgform)
        {
         __sgferr(1150,
          "%s concatenate lvalue (pos %d) wire conflicts with reg form",  
          __to_qctyp(s1, qctyp), cnt);
         return;
        }
       continue;
      }
     /* must be reg form */
     if (!nd_qcreg(ndp2->lu.x))
      {
       __sgferr(810,
        "%s concatenate lvalue (pos %d) not a scalared wire or simple reg",
        __to_qctyp(s1, qctyp), cnt);
       return;
      }
     if (!*is_rgform)
      {
       __sgferr(1150,
        "%s concatenate lvalue (pos %d) reg conflicts with wire form",
        __to_qctyp(s1, qctyp), cnt);
       return;
      }
    }
  }
 else
  {
   /* if this is normal declarative (wire only) lhs - must be force */
   if (!__xhas_reg(ndp))
    {
     if (qctyp != FORCE && qctyp != RELEASE)
      {
       __sgferr(808, "%s lvalue contains wires - use force/release",
        __to_qctyp(s1, qctyp));
       return;
      }
     *is_rgform = FALSE;
    }
   else
    {
     if (!nd_qcreg(ndp))
      {
       __sgferr(810, "%s lvalue not a scalared wire or simple reg",
        __to_qctyp(s1, qctyp));
       return; 
      } 
    }
  }
 /* final step is checking lhs expression */
 /* know for procedural required simple format already checked for */
 if (*is_rgform) __chk_lhsexpr(ndp, LHS_PROC);
 else __chk_lhsexpr(ndp, LHS_DECL);

 /* set used in qc force assign nets - set even if no code gen */
 set_qc_frcassgn_net(ndp); 
}

/*
 * set used in QC stmt bit for all nets on LHS 
 * always called but does nothing for interactive fixup (pass 2) 
 */
static void set_qc_frcassgn_net(struct expr_t *ndp)
{
 struct net_t *np;

 if (__isleaf(ndp))
  {
   if (ndp->optyp == ID || ndp->optyp == GLBREF)
    {
     np = ndp->lu.sy->el.enp;
     if (np->nrngrep != NX_CT) return;

     np->nu.ct->frc_assgn_in_src = TRUE;
     /* setting mod flag for task to - i.e. no task qc assign/force flag */
     /* SJM 12/23/02 - only needs to be set during elaboration - if */
     /* added from PLI not needed */
     __inst_mod->mhas_frcassgn = TRUE;
    }
   return;
  }
 /* SJM 01-18-09 - can't do variable lhs part select for frc/assign */
 /* so do not need to check mda next ndx list */

 if (ndp->lu.x != NULL) set_qc_frcassgn_net(ndp->lu.x);
 if (ndp->ru.x != NULL) set_qc_frcassgn_net(ndp->ru.x);
}

/*
 * return T if expr. is a register
 * nd reg for id's - this is where node type is unknown
 * this reg cannot be a real
 */
static int32 nd_qcreg(struct expr_t *ndp)
{
 struct net_t *np;

 if ((ndp->optyp != ID && ndp->optyp != GLBREF) || ndp->lu.sy->sytyp != SYM_N)
  return(FALSE);
 np = ndp->lu.sy->el.enp;
 if (np->n_isaparam) return(FALSE);
 if (np->ntyp >= NONWIRE_ST && np->ntyp != N_EVENT) return(TRUE);
 return(FALSE);
}

/*
 * must check qc assign/force (not deassign/release) for cirular use
 * of lhs component on rhs 
 * error if lhs net used on rhs of assign/force
 *
 * SJM 07/16/03 new check added since code core dumps with stack overflow
 * otherwise
 * LOOKATME - currently pessimistic - different XMR inst or bit still error
 */
static void chk_circular_qc_stmt(struct st_t *stp)
{
 int32 qctyp;
 struct expr_t *lhsx, *rhsx;
 struct expr_t *catndp, *catelx, *lhsx2;
 struct net_t *np;
 char s1[RECLEN];

 lhsx = stp->st.sqca->qclhsx;
 rhsx = stp->st.sqca->qcrhsx;
 qctyp =   stp->st.sqca->qcatyp;
 if (lhsx->optyp == LCB)
  {
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     catelx = __get_lvalue_idndp(catndp->lu.x);
     /* DBG remove -- */
     if (catelx->optyp != ID && catelx->optyp != GLBREF) 
      __misc_terr(__FILE__, __LINE__);
     /* -- */
     np = catelx->lu.sy->el.enp;

     if (rhs_expr_has_net(rhsx, np))
      {
       if (qctyp != FORCE && qctyp != RELEASE)
        {
         __sgferr(3409,
           "net %s in concatenate on both left and right hand sides of QC %s - illegal infinite loop",
           np->nsym->synam, __to_qctyp(s1, qctyp));
         return;
        }
      }
    }
   return;
  }
 lhsx2 = __get_lvalue_idndp(lhsx);
 /* DBG remove -- */
 if (lhsx2->optyp != ID && lhsx2->optyp != GLBREF) 
  __misc_terr(__FILE__, __LINE__);
 /* -- */
 np = lhsx2->lu.sy->el.enp;
 if (rhs_expr_has_net(rhsx, np))
  {
   __sgferr(3409,
    "net %s on both left and right hand sides of QC %s - illegal infinite loop",
    np->nsym->synam, __to_qctyp(s1, qctyp));
  }
}

/*
 * get lvalue (lhs expr that is decomposed form concat) expr
 * for ID/XMR return expr else return left offspring
 */
extern struct expr_t *__get_lvalue_idndp(struct expr_t *lhsx)
{
 if (lhsx->optyp == GLBREF || lhsx->optyp == ID) return(lhsx);
 if (lhsx->optyp == LSB || lhsx->optyp == PARTSEL 
  || lhsx->optyp == PARTSEL_NDX_PLUS || lhsx->optyp == PARTSEL_NDX_MINUS) 
  {
   return(lhsx->lu.x);
  }
 __misc_terr(__FILE__, __LINE__);
 return(NULL);
}

/*
 * routine to return T if net contained in rhs expr
 */
static int32 rhs_expr_has_net(struct expr_t *rhsx, struct net_t *np)
{
 struct expr_t *xp2;

 if (__isleaf(rhsx))
  {
   if (rhsx->optyp == ID || rhsx->optyp == GLBREF) 
    {
     if (rhsx->lu.sy->el.enp == np) return(TRUE);
    }
   return(FALSE);
  }

 for (xp2 = rhsx->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   if (rhs_expr_has_net(xp2, np)) return(TRUE);
  }

 if (rhsx->lu.x != NULL) 
  { if (rhs_expr_has_net(rhsx->lu.x, np)) return(TRUE); }
 if (rhsx->ru.x != NULL) 
  { if (rhs_expr_has_net(rhsx->ru.x, np)) return(TRUE); }
 return(FALSE); 
}

/*
 * check a disable statement
 * tricky because if non global may need to replace with labl/task sym.
 */
static void chk_disable(struct st_t *stp)
{
 struct expr_t *dsxp;
 struct sy_t *syp, *syp2;
 struct symtab_t *sytp;
 struct sy_t *upsyp;
 struct gref_t *grp;

 dsxp = stp->st.sdsable.dsablx;
 /* case 1: global cannot replace if cannot be disabled */
 if (dsxp->optyp == GLBREF) syp = dsxp->lu.sy;
 else if (dsxp->optyp == ID)
  { 
   /* case 2: ID - make sure can be disabled and look upward */
   syp = dsxp->lu.sy;
   /* if not declared, or not disable try to find above */ 
   if (!syp->sydecl) goto use_syp;

   if (syp->sytyp != SYM_TSK && syp->sytyp != SYM_F
    && syp->sytyp != SYM_LB)
    {
     /* if ID disable and no current task, error */
     if (__cur_tsk == NULL) goto use_syp;

     /* work upward to task/func or named block that can be disabled */
     /* know parent of task is module and of module is nil */
     /* but only look starting one up since syp already set */
     sytp = __cur_tsk->tsksymtab->sytpar;
     for (; sytp != NULL; sytp = sytp->sytpar)
      {
       if ((syp2 = __get_sym(syp->synam, sytp)) != NULL)
        {
         /* if can be disabled, must change ID expr. symbol */
         /* but statement still points to same expr. */
         if (syp2->sytyp == SYM_TSK || syp2->sytyp != SYM_F
          || syp2->sytyp != SYM_LB)
          { syp = syp2; dsxp->lu.sy = syp; goto use_syp; }
        }
      }
     /* fall thru and use known wrong syp since no alternative */
    }
  }
 else { syp = NULL; __misc_sgfterr(__FILE__, __LINE__); }

 /* disable object not simple name */
use_syp:
 if (!syp->sydecl) return;

 /* SJM 10/18/05 - always marking tasks/funcs/named blocks that can be */
 /* disabled but only used in cver-cc */
 syp->el.etskp->can_be_disabled = TRUE;

 /* AIV 05/29/07 - if named block in task need to add to called from */
 /* task list to check for delays/named blocks */
 if (__compiled_sim)
  {
  if (__cur_tsk != NULL)
   {
    add_task_to_task_call(__cur_tsk, syp->el.etskp);
   }
 }
 
 /* if ID and function know ok, if different func. error catch in nodel chk */ 
 if (dsxp->optyp == ID && syp->sytyp == SYM_F && __cur_tsk != NULL
  && __cur_tsk->tsktyp == FUNCTION) return;

 /* if error will still be global ID - else from now on normal symbol */
 if (syp->sytyp != SYM_TSK && syp->sytyp != SYM_LB)
  {
   __sgferr(968, "object \"%s\" type %s cannot be disabled",
    __to_idnam(dsxp), __to_sytyp(__xs, syp->sytyp));
  }
 /* know if local, good since accessible local means not in function */
 /* or checked in special inside function checking code */
 if (dsxp->optyp == GLBREF)
  {
   grp = dsxp->ru.grp; 
   /* see if symbol table that target is in */
   /* think gref target symbol table should be set */
   if (grp->grsytp == NULL) __misc_sgfterr(__FILE__, __LINE__);

   for (sytp = grp->grsytp; sytp != NULL; sytp = sytp->sytpar)
    {
     upsyp = sytp->sypofsyt;
     if (upsyp->sytyp == SYM_TSK && upsyp->el.etskp->tsktyp == FUNCTION)
      {
       __sgferr(805,
        "disable target \"%s\" type %s cannot be inside function",
        __to_idnam(dsxp), __to_sytyp(__xs, upsyp->sytyp));
       return;
      }
    }  	
  }
} 
