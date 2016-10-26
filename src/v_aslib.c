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
 * byte code interpreter virtual machine instructions here 
 * all bit/array/part select routines both lhs and rhs here
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

/* local prototypes */
static void link_1mod_filter_idata_area(struct mod_t *);
static void set_trchan_1vtx_nchg_fld(struct net_t *, int32, struct vbinfo_t *,
 t_midat *);
static word32 widegate_ld_bit(word32 *, int32, int32);
#ifdef __CVC_DEBUG__
static void check_for_active_event(struct tev_t *);
#endif

/* SJM 07/11/08 - hdrs for new after link init d.s wrappers */
extern void __alnk_init_mdp(int32);
extern void __alnk_fixup_allmods_comm_idp_areas(void);
extern void __alnk_init_tev_dat(void *, int32, void *, size_t, word64);
extern void __alnk_init_tev_dat_nodelay(void *, int32, void *, size_t);
extern void __alnk_init_nchglst_el(void *, void *, int32, size_t);
extern void __alnk_init_nchglst_el_npp(void *, void *, int32, size_t, void *);
extern void __alnk_init_nchglst_el_rng(void *, void *, int32, size_t, int32, 
 int32);
extern void __alnk_init_nchglst_el_rng_npp(void *, void *, int32, size_t, 
 int32, int32, void *);
extern void __alnk_set_tev_gp_u(void *, int32, int32);
extern void __alnk_set_tev_nxtptr(void *);
extern void __alnk_set_tev_nb_free_nextevptr(void *, void *, int32);
extern void __alnk_set_tev_del(void *, word64, int32);
extern void __alnk_cp_is1v_32b_tev_dels(void *, void *, int32);
extern void __alnk_cp_is1v_64b_tev_dels(void *, word32 *, int32);
extern void __alnk_set_trchan_vtx_nchgs(void); 
extern void __alnk_set_udptab_adrs(void *, void *, int32);
extern void __alnk_set_pth_del_adr(void *, int32);
extern void __alnk_set_tchk_tchg_adr(void *, int32);
extern void __alnk_set_stmt_entptr(void *, int32);
extern void __alnk_ialst_enters(void **, int32);
extern void __alnk_set_npp_entptr(void *, int32);
extern void __alnk_set_dcevnt(void *, int32, int32);
extern void __alnk_set_gref(void *, int32);
extern void __alnk_set_gate(void *, int32);
extern void __alnk_set_conta(void *, int32);
extern void __alnk_set_net_addr(void *, int32);
extern void __alnk_set_task_addr(void *, int32);
extern void __alnk_set_npp_addr(void *, int32);
extern void __alnk_set_xpr_addr(void *, int32);

/* extern prototypes (maybe defined in this module) */
extern void __asl_eval_wide_wire(word32 *, word32 *, word32 *, int32);
extern void __asl_eval_wide_wire_and(word32 *, word32 *, word32 *, int32);
extern void __asl_eval_wide_wire_or(word32 *, word32 *, word32 *, int32);
extern void __asl_eval_1w_nonstren_wire(word32 *, word32, word32);
extern void __asl_eval_1w_nonstren_wire_and(word32 *, word32, word32);
extern void __asl_eval_1w_nonstren_wire_or(word32 *, word32, word32);
extern void __asl_process_alloced_nchg(void);
extern void __asl_wdel_schd_1wirebit(struct net_t *, int32, word32, word32,
 struct tev_t *);
extern void __asl_schd_st_1pthwirebit(struct net_t *, 
 int32, word32, word32, struct nchglst_t *, struct tev_t *); 
extern void __asl_chk_dce_cbvc(struct net_t *);
extern void __asl_trigger_ectrl(struct tev_t *);
extern void __asl_add_dmpv_chglst_el(struct net_t *);
extern void __asl_add_dmpv_chglst_el_array(struct net_t *, int32);
extern void __asl_add_dmpp_chglst_el(struct net_t *);
extern void __asl_add_dmpv_chglst_el_mdprt(struct net_t *);
extern void __asl_add_dmpp_chglst_el_mdprt(struct net_t *);
extern int32 __net_chg_nd_store(struct net_t *, int32, int32);

extern struct itree_t *__find_unrt_targitp(struct gref_t *,
 struct itree_t *, int32);
extern int32 __wide_vval_is0(word32 *, int32);
extern word64 __get_del(union del_u, word32);
extern struct thread_t *__setup_tsk_thread(struct task_t *);
extern void __thrd_done_cleanup(struct thread_t *);
extern void __thrd_done_cleanup_auto(struct thread_t *);
extern void __exec_sysfunc(struct expr_t *);
extern struct st_t *__exec_stsk(struct st_t *, struct sy_t *,
 struct tskcall_t *);
extern void __do_disp(struct expr_t *, int32);
extern char *__vval_to_vstr(word32 *, int32, int32 *);
extern void __cvsim_msg(char *, ...);
extern void __pvc_call_misctf(struct dcevnt_t *);
extern void __cbvc_callback(struct dcevnt_t *, struct cbrec_t *, struct h_t *);
extern struct xstk_t *__ld_sttfrwarg_driver(struct net_pin_t *);
extern void __add_select_nchglst_el(struct net_t *, int32, int32);
extern void __cvc_eval_update_1w_tranchan(struct vtx_t *);
extern t_midat *__xmrget_refgrp_to_targ(struct gref_t *);
extern void __mwrshift(word32 *, word32, int32);
extern void __case_terr(char *, int32);
extern void __grow_xstk(void);
extern void __rhspsel(word32 *, word32 *, int32, int32);
extern void __eval_wire(word32 *, word32 *, struct net_t *, 
 struct net_pin_t *); 
extern void __chg_xstk_width(struct xstk_t *, int32);
extern int32 __vval_is1(word32 *, int32);
extern void __ld_wire_val_wrds(word32 *, word32 *, struct net_t *);
extern void __ld_wire_val_xstk(struct xstk_t *, struct net_t *);
extern void __bld_forcedbits_mask(word32 *, struct net_t *);
extern void __ld_perinst_val(word32 *, word32 *, union pck_u, int32);
extern void __ld_psel(word32 *, word32 *, struct net_t *, int32, int32);
extern word32 __wrd_redxor(word32);

extern void __schedorassign_unknown_bit(struct net_t *, word32,
 word32, int32);
extern word32 __get_showcancele_val(struct gate_t *);
extern word64 __hizstrengate_getdel(struct gate_t *);
extern void __emit_pulsewarn(struct gate_t *, struct tev_t *, word64 *,
 word64 *, char *);
extern int32 __em_suppr(int32);
extern void __acc_evchg_gate_outwire(struct gate_t *);
extern void __change_gate_outwire(struct gate_t *);
extern void __eval_nmos_gate(word32);
extern void __eval_rnmos_gate(word32);
extern void __eval_pmos_gate(word32);
extern void __eval_rpmos_gate(word32);
extern word32 __comb_1bitsts(word32, word32, word32);
extern t_midat *__get_qc_wirrng(struct expr_t *, struct net_t **, int32 *,
 int32 *);
extern void __dcelst_on(struct dceauxlst_t *);
extern void __dcelst_off(struct dceauxlst_t *);
extern void __eval_1w_nonstren(word32 *, word32 *, word32, word32, word32);
extern void __cvc_immed_eval_trifchan(struct gate_t *);
extern struct net_chg_t *__find_nchg_range(struct net_t *, int32, int32);

extern int32 __stfilter_dce_chg(struct net_t *, struct dcevnt_t *, byte *,
 word32 *, word32 *);
extern int32 __vccb_vec_standval_filter(struct net_t *, struct dcevnt_t *,
 byte *, word32 *, word32 *);
extern int32 __vccb_scal_standval_filter(struct net_t *, byte *, word32 *,
 word32 *, int32);
extern int32 __filter_dce_chg(struct net_t *, struct dcevnt_t *, word32 *,
 word32 *, word32 *);
extern int32 __scal_stfilter_dce_chg(struct net_t *, byte *, word32 *,
 word32 *);

extern void __st_perinst_val(union pck_u, int32, word32 *, word32 *);
extern void __lhsbsel(word32 *, int32, word32);
extern int32 __v64_to_real(double *, word64 *);
extern struct itree_t *__get_npprefloc(struct net_pin_t *);
extern struct xstk_t *__ld_vpiputv_driver(struct net_pin_t *);
extern void __exec_vpi_gateoutcbs(struct tev_t *);
extern void __ld_bit(word32 *, word32 *, struct net_t *, int32);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern int32 __exec_disable(struct expr_t *);
extern struct inst_t *__get_gref_giarr_ip(struct gref_t *, int32,
 struct itree_t *); 
extern void __emit_path_pulsewarn(struct pthdst_t *, struct tev_t *,
 word64 *, word64 *, char *, word32);
extern void __emit_path_distinform(struct net_t *, struct pthdst_t *,
 word64 *);
extern void __emit_path_samewarn(struct net_t *, int32, struct tev_t *,
 word64 *, char *, word32);
extern void __st_bit(struct net_t *, int32, word32, word32);
extern struct xstk_t *__eval_assign_rhsexpr(struct expr_t *, struct expr_t *);
extern int32 __real_to_v64tim(word64 *, double);
extern char *__to_timstr(char *, word64 *);
extern int32 __needs_netchg_record(struct net_t *);
extern void __add_dp_chglst_el(struct net_t *);
extern void __add_togglelst_el(struct net_t *);
extern void __lmult(word32 *, word32 *, word32 *, int32);
extern int32 __is_lnegative(word32 *, int32); 
extern word32 __cp_lnegate(word32 *, word32 *, int32);
extern word32 __inplace_lnegate(word32 *, int32);
extern int32 __eval_1wide_gate(struct gate_t *, int32);
extern void __exec_qc_assign(struct st_t *, int32);
extern void __exec_qc_wireforce(struct st_t *);
extern void __eval_wide_wire(word32 *, word32 *, word32 *, word32 *, int32,
 word32);
extern void __eval_stwire(byte *, word32, int32, int32, byte *);

static void asl_loc_add_pnd0_event(struct tev_t *);
static void asl_loc_add_pnd0_event_dl(struct tev_t *);
static struct tev_t *asl_loc_get_new_event(struct tev_t *);
static struct tev_t *asl_loc_get_new_event_nb(struct tev_t *);
static struct tev_t *asl_loc_get_new_nbmem_event(struct tev_t *, int32);
static struct tev_t *asl_loc_get_new_thread_event(void);
static void asl_loc_eval_1w_nonstren_wire(word32 *, word32 *, word32, word32);
static void asl_loc_eval_1w_nonstren_wire_and(word32 *, word32 *, word32,
 word32);
static void asl_loc_eval_1w_nonstren_wire_or(word32 *, word32 *, word32,
 word32);
static void asl_loc_get_impth_del(word64 *, struct net_t *, struct mipd_t *);
static void asl_loc_cancel_1mipdev(struct tev_t *);
static void asl_loc_sched_mipd_nchg(struct net_t *, int32, struct mipd_t *, 
 struct tev_t *);
static void asl_loc_reschedule_1mipd(int32, struct tev_t *, word64);
static void linkout_tevp(struct tev_t *);
static void linkout_cur_time(struct tev_t *);
static void linkout_pnd0_event(struct tev_t *);
static void asl_loc_reschedule_scalar_1mipd(struct tev_t *, word64);
static struct pthdst_t *asl_loc_get_path_del_scalar(struct net_t *, word64 *);
static struct pthdst_t *asl_loc_get_path_del(struct rngdwir_t *, int32, 
 word64 *);
static void asl_loc_record_nchg(struct net_t *, struct nchglst_t *);
static void asl_loc_chg_st_bit(struct net_t *, int32, word32, word32, 
 struct nchglst_t *);
static void asl_loc_record_sel_nchg(struct net_t *, struct nchglst_t *, int32);
static int32 asl_loc_chg_vec_lhsbsel(word32 *, int32, word32, word32, int32);
static int32 asl_loc_chg_vec_lhsbsel_2state(word32 *, int32, word32);
static void asl_loc_schedule_1wev(int32, struct tev_t *, word64, word64, 
 word32);
static void asl_loc_reschedule_1wev(struct tev_t *, word32, word64);
static struct thread_t *asl_loc_sched_fj_subthread(struct st_t *);

static word32 asl_loc_eval_combine_stbid_chan(struct chanrec_t *);
static word32 asl_loc_eval_combine_bid_chan(struct chanrec_t *); 
static void asl_loc_assign_1tranbit(struct net_t *, int32, word32, word32);
static void asl_loc_stassign_1tranbit(struct net_t *, int32, 
 word32);
static void asl_loc_stassign_1tranbit(struct net_t *, int32, word32);
static void asl_loc_eval_assign_stbid_chan(struct chanrec_t *);
static void asl_loc_eval_assign_bid_chan(struct chanrec_t *); 
static void asl_loc_ld_vtx_netbit(word32 *, word32 *, struct net_t *, int32);
static void asl_loc_vec_eval_assign_bid_chan(struct chanrec_t *);
static void asl_loc_vec_eval_assign_stbid_chan(struct chanrec_t *);

/* local force code handling */
static void asl_loc_do_qc2_wirestore(struct net_t *, struct qcval_t *,
 struct xstk_t *, struct nchglst_t *);
static void asl_loc_do_qc2_regstore(struct net_t *, struct qcval_t *,
 struct xstk_t *, struct nchglst_t *);
static int32 asl_loc_chg_st_vecval(word32 *, int32, word32 *, word32 *);
static int32 asl_loc_chg_st_vecval_2state(word32 *, int32, word32 *);
static void asl_loc_do_qc_store(struct net_t *, struct qcval_t *,
 struct expr_t *, struct expr_t *, struct nchglst_t *);
static void asl_loc_do_1bit_wireforce(struct st_t *, struct net_t *,
 int32, int32, int32, t_midat *, struct dceauxlst_t *, t_midat *, 
 struct nchglst_t *);
static void asl_loc_do_qc_wireforce(struct st_t *, struct expr_t *,
 int32, struct nchglst_t *, size_t);
static void asl_loc_do_qc_wirerelease(struct expr_t *, struct nchglst_t *, 
 size_t);
static void asl_loc_do_qc_tran_wirerelease(struct expr_t *, 
 struct nchglst_t *, size_t);
static void asl_loc_qc_tran_wirerelease(struct net_t *, int32, int32, 
 t_midat *, struct expr_t *, struct nchglst_t *);
static void asl_loc_do_qc_wire_intran_release(struct net_t *, int32, 
 struct expr_t *, t_midat *, struct nchglst_t *);
static void asl_loc_assign_1mdrwire(struct net_t *, struct nchglst_t *);
static void asl_loc_do_qc_assign(struct st_t *, struct expr_t *,
 int32, struct dceauxlstlst_t *, struct nchglst_t *, size_t);
static void asl_loc_do_qc_regforce(struct st_t *, struct expr_t *,
  int32, struct dceauxlstlst_t *, struct nchglst_t *, size_t);
static void asl_loc_do_qc_tran_wireforce(struct st_t *, 
 struct expr_t *, int32, struct nchglst_t *, size_t);
static void asl_loc_qc_tran_wireforce(struct net_t *, int32, int32, int32, 
 t_midat *, struct st_t *, struct nchglst_t *);
static void asl_loc_do_qc_wire_intran_force(struct net_t *, int32, word32, 
 word32, t_midat *, struct nchglst_t *);
extern void asl_loc_bit1_vpi_or_tran_wireforce(struct net_t *, 
 word32 *, word32 *, int32, int32, int32, struct nchglst_t *);
static void asl_loc_do_qc_deassign(struct expr_t *);
static void asl_loc_do_qc_regrelease(struct expr_t *, struct nchglst_t *, 
 size_t);
static void asl_loc_gate_chg_lhsbsel(word32 *, int32, word32);
static int32 asl_loc_schd_1bitpthdrvr(struct net_t *, int32, struct tev_t *);
static void asl_loc_assign_chged_vtxs(void);
static void asl_loc_eval_tranif_onoff(struct gate_t *);
static void asl_loc_add_static_nchglst(struct nchglst_t *);
static word64 asl_loc_real_to_ticks(double, struct mod_t *);
static word64 asl_loc_delx_to_deltim(struct expr_t *, struct xstk_t *);
static double asl_loc_uniform(int32 *, int32, int32);
static int32 asl_loc_rtl_dist_uniform(int32 *, int32, int32);
static void asl_loc_add_dmpv_chglst_el_mdprt(struct net_t *);
static int32 asl_loc_cmp_str_vals(word32 *, word32 *, int32);
#ifdef __XPROP__
static void asl_loc_set_restore_xprop_accum_block(struct xprop_t *, int32);
static void asl_loc_set_restore_xprop_accum_block_selfv(struct xprop_t *, 
 int32);
static void asl_loc_combine_xprop_accum(word32 *, word32 *, word32 *, int32);
static void asl_loc_combine_xprop_accum_1w(word32 *, word32, word32);
static void asl_loc_stmt_assign_to_accum_1w_id(struct net_t *, 
  struct xprop_t *, word32, word32);
static void asl_loc_stmt_assign_to_accum_wide_id(struct net_t *, 
 struct xprop_t *, word32 *, word32 *);
#endif

#ifdef __STREE__
extern struct tev_t *__move_compiled_time(void);
extern void __insert_event(struct tev_t *tevp);
extern void __insert_event_nb(struct tev_t *tevp);
#define asl_loc_insert_event_(tevp) __insert_event(tevp)
#define asl_loc_insert_event_nb_(tevp) __insert_event_nb(tevp)

#else
/* AIV 12/30/08 - use keyword 'inline' here this will inline these */
/* routines even with -O2 normally this is a -O3 optimization */
/* these common routines should be inlined - produces better code */
static inline void asl_loc_insert_event(struct tev_t *);
static inline void asl_loc_insert_event_nb(struct tev_t *);
static inline void asl_loc_insert_event_nb_t(struct tev_t *);
static void asl_loc_nb_conflict_list(struct tev_t *, struct heap_t *);
static void asl_loc_conflict_list(struct tev_t *, struct heap_t *);
#define asl_loc_insert_event_(tevp) asl_loc_insert_event(tevp)
#define asl_loc_insert_event_nb_(tevp) asl_loc_insert_event_nb(tevp)
#define asl_loc_insert_event_nb_t_(tevp) asl_loc_insert_event_nb_t(tevp)
static struct heap_t *asl_loc_add_new_heap_time(struct tev_t *, int32);
static void asl_loc_grow_event_heap(void);
#endif

extern struct thread_t *__alloc_thrd(void);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern char *__msg2_cur_blditree(char *);
extern void __sgfwarn(int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __misc_terr(char *, int32);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern void __find_call_force_cbs(struct net_t *, int32);
extern void __cb_all_rfs(struct net_t *, int32, int32);
extern char *__to_idnam(struct expr_t *);
extern void __ld_addr(word32 **, word32 **, struct net_t *);
extern struct xstk_t *__stload_mdrwire(struct net_t *);
extern struct xstk_t *__load_mdrwire(struct net_t *);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern int32 __correct_forced_newwireval(struct net_t *, word32 *, word32 *);
extern void __st_val(struct net_t *, word32 *, word32 *, int32);
extern void __find_call_rel_cbs(struct net_t *, int32);
extern void __sgfinform(int32, char *, ...);
extern void __st_standval(byte *, struct xstk_t *, byte);
extern void __cnvt_xzs_to_2state(word32 *, word32 *, int32);
extern void __eval_wide_gate(struct gate_t *, struct xstk_t *);
extern void __chg_st_val(struct net_t *, word32 *, word32 *);
extern void __wakeup_delay_ctrls(struct net_t *, int32, int32);
extern void __add_dmpv_chglst_el_sel(struct net_t *, int32);
extern void __chg_st_bit(struct net_t *, int32, word32, word32);
#ifdef __XPROP__
extern void __assign_lhsx_to_accum(struct expr_t *, word32 *, word32 *,
 struct xprop_t *);
extern void __trace_xprop_stmt_write(struct st_t *, word32 *, word32 *, int32);
#endif

extern const word32 __masktab[];
extern const byte __stren_map_tab[];
extern const word32 __cap_to_stren[];
extern const byte __hizstren_del_tab[];
extern const byte __bufif_and_tab[];
extern const byte __bufif_or_tab[];
extern const word32 __pow3tab[];
extern const double __dbl_toticks_tab[];

//##########################################################################

/*
 * RUN TIME ROUTINES USED BY THE DESIGN WIDE RUN AT ALNK TIME C INIT 
 */

/* AIV 09/02/08 - fixed the warnings for union init */
struct tev_t __tevdat_template = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {stp:NULL}, 0, NULL, NULL, NULL, 0ULL, NULL,
 0ULL, NULL, NULL, {bi:0}};

struct nchglst_t __nchglst_template = { 0, NULL, 0, -1, -1, NULL, NULL, NULL };

/*
 * AGGREGATED ALNK WRAPPER ROUTINES
 */


/* 
 * just set global __init_mdp
 */
extern void __alnk_init_mdp(int32 mi)
{
 __init_mdp = __dsgn_mod_ndx[mi];
}

/*
 * one routine to fixup the copied idp areas for all modules
 *
 * since have the right idp ptrs (made from linking the per mod idp symbols)
 * can do entire design fix up in one routine
 */  
extern void __alnk_fixup_allmods_comm_idp_areas(void)
{
 int32 mi, ii;
 t_midat *idp, *new_idp;
 struct mod_t *mdp;
 struct itree_t *itp;

 /* SJM 08/28/08 - notice must do after all per mod idata areas set to */
 /* the comm file since uses match imdps which may be forward or xmrs */
 for (mi = 0; mi < __dsgn_num_mods; mi++)
  {
   mdp = __dsgn_mod_ndx[mi];

   link_1mod_filter_idata_area(mdp);
   new_idp = mdp->mod_idata;
   /* link every instance */
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     mdp->moditps[ii]->it_idp = &(new_idp[ii*mdp->mod_idata_siz]);
    }
  }
 /* AIV 12/31/08 - for inline of toupdprt_inst must set MD_UPIDP */
 /* to the new idp value address */
 for (mi = 0; mi < __dsgn_num_mods; mi++)
  {
   mdp = __dsgn_mod_ndx[mi];

   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp = mdp->moditps[ii];
     if (itp->up_it == NULL) continue;
     idp = itp->it_idp;
     idp[MD_UPIDP] = (t_midat) itp->up_it->it_idp;
    }
  }
}

/*
 * cross connect mod_idata area after copying into .s file's idp area
 *  - connect filtidp for npp's 
 *  - connect dcep's match/ref idps
 */
static void link_1mod_filter_idata_area(struct mod_t *mdp)
{
 int32 ni; 
 size_t offset;
 struct net_t *np;
 struct net_pin_t *npp;
 struct mod_t *imdp;
 struct dcevnt_t *dcep;
 struct dce_idp_info_t *didp;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
  {
   for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
    {
     if (npp->np_xmrtyp != XNP_RTXMR) continue;
     if (npp->npproctyp != NP_PROC_FILT) continue;
 
     imdp = npp->npaux->mdp;
     offset = npp->npaux->idp_ofs;
     npp->npaux->npu.filtidp = &(imdp->mod_idata[offset]);
    }
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
     if (npp->np_xmrtyp != XNP_RTXMR) continue;
     if (npp->npproctyp != NP_PROC_FILT) continue;
 
     imdp = npp->npaux->mdp;
     offset = npp->npaux->idp_ofs;
     npp->npaux->npu.filtidp = &(imdp->mod_idata[offset]);
    }
   for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
    {
     if (dcep->nd_chg_to_idp)
      {
       didp = dcep->didp;
       /* DBG remove -- */
       if (didp == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       imdp = didp->match_mdp;
       offset = didp->match_idp_ofs;
       dcep->dce_matchu.idp = &(imdp->mod_idata[offset]);

       imdp = didp->ref_mdp;
       offset = didp->ref_idp_ofs;
       dcep->dce_refu.idp = &(imdp->mod_idata[offset]);
       /* no longer need didp free it */
       __my_free(dcep->didp, sizeof(struct dce_idp_info_t));
       dcep->didp = NULL;
      }
    }
  }
}


/*
 * init a tev to the dummy default values 
 * AIV 03/12/12 - combined a bunch of routines to init tev_'s into this one
 * this makes the code smaller and faster there is no reason to 
 * have seperate routines - these are all perinst to so better to 
 * to do just one pass 
 */
extern void __alnk_init_tev_dat(void *dst, int32 ninsts, void *enterp,
 size_t ctev_idp_ofs, word64 del)
{
 int32 i;
 struct tev_t *tevp;
 struct mod_t *mdp;
 t_midat *mod_idp_base;
 byte *dst_cp;

 mdp = __init_mdp;
 dst_cp = dst;
 memcpy(dst_cp, &__tevdat_template, sizeof(struct tev_t)); 

 /* set the delay and the enter pointer */
 tevp = (struct tev_t *) dst_cp;
 tevp->enterptr = (void (*)) enterp;
 tevp->delay = del;
 
 mod_idp_base = mdp->mod_idata;
 tevp->te_idp = mod_idp_base;
 /* only need link in idp area if more than one inst */ 
 if (mdp->flatinum > 1)
  {
   mod_idp_base[ctev_idp_ofs] = (word32) tevp;
  }

 /* do the same for each instance */
 for (i = 1; i < ninsts; i++)
  {
   dst_cp += sizeof(struct tev_t);
   memcpy(dst_cp, &__tevdat_template, sizeof(struct tev_t)); 
   tevp = (struct tev_t *) dst_cp;
   tevp->enterptr = (void (*)) enterp;
   tevp->delay = del;
   tevp->te_idp = &(mod_idp_base[i*mdp->mod_idata_siz]);
   /* only need link in idp area if more than one inst */ 
   if (mdp->flatinum > 1)
    {
     mod_idp_base[i*mdp->mod_idata_siz + ctev_idp_ofs] = (word32) tevp;
    }
  }
}

/*
 * same as above - but not setting a delay value
 */
extern void __alnk_init_tev_dat_nodelay(void *dst, int32 ninsts, void *enterp,
 size_t ctev_idp_ofs)
{
 int32 i;
 struct tev_t *tevp;
 struct mod_t *mdp;
 t_midat *mod_idp_base;
 byte *dst_cp;

 mdp = __init_mdp;
 dst_cp = dst;
 memcpy(dst_cp, &__tevdat_template, sizeof(struct tev_t)); 

 /* set the delay and the enter pointer */
 tevp = (struct tev_t *) dst_cp;
 tevp->enterptr = (void (*)) enterp;
 
 mod_idp_base = mdp->mod_idata;
 tevp->te_idp = mod_idp_base;
 /* only need link in idp area if more than one inst */ 
 if (mdp->flatinum > 1)
  {
   mod_idp_base[ctev_idp_ofs] = (word32) tevp;
  }

 /* do the same for each instance */
 for (i = 1; i < ninsts; i++)
  {
   dst_cp += sizeof(struct tev_t);
   memcpy(dst_cp, &__tevdat_template, sizeof(struct tev_t)); 
   tevp = (struct tev_t *) dst_cp;
   tevp->enterptr = (void (*)) enterp;
   tevp->te_idp = &(mod_idp_base[i*mdp->mod_idata_siz]);
   /* only need link in idp area if more than one inst */ 
   if (mdp->flatinum > 1)
    {
     mod_idp_base[i*mdp->mod_idata_siz + ctev_idp_ofs] = (word32) tevp;
    }
  }
}

/*
 * routine to init one nchg record all instances - no range
 *
 * AIV 07/22/09 - made this code smaller by making two cases one range 
 * and one no range - produces less code 
 *
 * AIV 07/25/09 - no reason for all the extern routines with the casting
 */
extern void __alnk_init_nchglst_el(void *nchg_vp, void *proc_nchg_vp, 
 int32 ni, size_t nchg_idp_ofs)
{
 struct nchglst_t *nchglp, *nchglp2;
 int32 ii;
 struct mod_t *mdp;
 struct net_t *np;
 t_midat *base_idp;

 mdp = __init_mdp;
 nchglp = (struct nchglst_t *) nchg_vp;
 memcpy(nchglp, &(__nchglst_template), sizeof(struct nchglst_t)); 

 nchglp = (struct nchglst_t *) nchg_vp;
 nchglp->process_enterptr = (void (*)) proc_nchg_vp;
 np = &(mdp->mnets[ni]);
 nchglp->chgnp = np;
 
 base_idp = mdp->mod_idata;
 nchglp->nchg_idp = base_idp;

 /* only need link in idp area if more than one inst */ 
 if (nchg_idp_ofs != -1)
  {
   base_idp[nchg_idp_ofs] = (word32) nchglp; 
  }

 for (ii = 1; ii < mdp->flatinum; ii++)
  {
   nchglp2 = &(nchglp[ii]);
   memcpy(nchglp2, nchglp, sizeof(struct nchglst_t));
   nchglp2->nchg_idp = &(base_idp[ii*mdp->mod_idata_siz]);
   if (nchg_idp_ofs != -1)
    {
     base_idp[ii*mdp->mod_idata_siz + nchg_idp_ofs] = (word32) nchglp2; 
    }
  }
}

/*
 * routine same as above except sets  _npp version
 * np->enter_npp 
 */
extern void __alnk_init_nchglst_el_npp(void *nchg_vp, void *proc_nchg_vp, 
 int32 ni, size_t nchg_idp_ofs, void *proc_nppe_vp)
{
 struct nchglst_t *nchglp, *nchglp2;
 int32 ii;
 struct mod_t *mdp;
 struct net_t *np;
 t_midat *base_idp;

 mdp = __init_mdp;
 nchglp = (struct nchglst_t *) nchg_vp;
 memcpy(nchglp, &(__nchglst_template), sizeof(struct nchglst_t)); 

 nchglp = (struct nchglst_t *) nchg_vp;
 nchglp->process_enterptr = (void (*)) proc_nchg_vp;
 np = &(mdp->mnets[ni]);
 nchglp->chgnp = np;
 np->enter_npp = (void (*)) proc_nppe_vp;
 
 base_idp = mdp->mod_idata;
 nchglp->nchg_idp = base_idp;

 /* only need link in idp area if more than one inst */ 
 if (nchg_idp_ofs != -1)
  {
   base_idp[nchg_idp_ofs] = (word32) nchglp; 
  }

 for (ii = 1; ii < mdp->flatinum; ii++)
  {
   nchglp2 = &(nchglp[ii]);
   memcpy(nchglp2, nchglp, sizeof(struct nchglst_t));
   nchglp2->nchg_idp = &(base_idp[ii*mdp->mod_idata_siz]);
   if (nchg_idp_ofs != -1)
    {
     base_idp[ii*mdp->mod_idata_siz + nchg_idp_ofs] = (word32) nchglp2; 
    }
  }
}

/*
 * routine to init one nchg record all instances - passed ranges
 */
extern void __alnk_init_nchglst_el_rng(void *nchg_vp, void *proc_nchg_vp, 
 int32 ni, size_t nchg_idp_ofs, int32 ncpi1, int32 ncpi2)
{
 struct nchglst_t *nchglp, *nchglp2;
 int32 ii;
 struct mod_t *mdp;
 struct net_t *np;
 t_midat *base_idp;

 mdp = __init_mdp;
 nchglp = (struct nchglst_t *) nchg_vp;
 memcpy(nchglp, &(__nchglst_template), sizeof(struct nchglst_t)); 

 nchglp = (struct nchglst_t *) nchg_vp;
 nchglp->process_enterptr = (void (*)) proc_nchg_vp;
 nchglp->bi1 = ncpi1;
 nchglp->bi2 = ncpi2;
 np = &(mdp->mnets[ni]);
 nchglp->chgnp = np;
 
 base_idp = mdp->mod_idata;
 nchglp->nchg_idp = base_idp;

 /* only need link in idp area if more than one inst */ 
 if (nchg_idp_ofs != -1)
  {
   base_idp[nchg_idp_ofs] = (word32) nchglp; 
  }

 for (ii = 1; ii < mdp->flatinum; ii++)
  {
   nchglp2 = &(nchglp[ii]);
   memcpy(nchglp2, nchglp, sizeof(struct nchglst_t));
   nchglp2->nchg_idp = &(base_idp[ii*mdp->mod_idata_siz]);
   if (nchg_idp_ofs != -1)
    {
     base_idp[ii*mdp->mod_idata_siz + nchg_idp_ofs] = (word32) nchglp2; 
    }
  }
}


/*
 * routine same as above except sets  _npp version
 * np->enter_npp 
 */
extern void __alnk_init_nchglst_el_rng_npp(void *nchg_vp, void *proc_nchg_vp, 
 int32 ni, size_t nchg_idp_ofs, int32 ncpi1, int32 ncpi2, void *proc_nppe_vp)
{
 struct nchglst_t *nchglp, *nchglp2;
 int32 ii;
 struct mod_t *mdp;
 struct net_t *np;
 t_midat *base_idp;

 mdp = __init_mdp;
 nchglp = (struct nchglst_t *) nchg_vp;
 memcpy(nchglp, &(__nchglst_template), sizeof(struct nchglst_t)); 

 nchglp = (struct nchglst_t *) nchg_vp;
 nchglp->process_enterptr = (void (*)) proc_nchg_vp;
 nchglp->bi1 = ncpi1;
 nchglp->bi2 = ncpi2;
 np = &(mdp->mnets[ni]);
 nchglp->chgnp = np;
 np->enter_npp = (void (*)) proc_nppe_vp;
 
 base_idp = mdp->mod_idata;
 nchglp->nchg_idp = base_idp;

 /* only need link in idp area if more than one inst */ 
 if (nchg_idp_ofs != -1)
  {
   base_idp[nchg_idp_ofs] = (word32) nchglp; 
  }

 for (ii = 1; ii < mdp->flatinum; ii++)
  {
   nchglp2 = &(nchglp[ii]);
   memcpy(nchglp2, nchglp, sizeof(struct nchglst_t));
   nchglp2->nchg_idp = &(base_idp[ii*mdp->mod_idata_siz]);
   if (nchg_idp_ofs != -1)
    {
     base_idp[ii*mdp->mod_idata_siz + nchg_idp_ofs] = (word32) nchglp2; 
    }
  }
}



/*
 * set tev (gate? only for now) to tu field 
 * after link (alnk) time routine gened in dsgn wide c init file
 */
extern void __alnk_set_tev_gp_u(void *tev_vp, int32 gi, int32 ninsts)
{
 int32 ii;
 struct tev_t *tevp;
 struct gate_t *gp;
 
 tevp = (struct tev_t *) tev_vp;
 for (ii = 0; ii < ninsts; ii++)
  {
   gp = &(__init_mdp->mgates[gi]);
   tevp[ii].tu.tegp = gp;
  }
}

/*
 * set tev next enter ptr field (for now just sets one template)
 * after link (alnk) time routine gened in dsgn wide c init file
 */
extern void __alnk_set_tev_nxtptr(void *tev_vp)
{
 struct tev_t *tevp;

 /* AIV 08/05/09 - this should just use the global next ev pointer */ 
 tevp = (struct tev_t *) tev_vp;
 tevp->next_enterptr = (void (*)) __process_next_ev_enterp;
}

/*
 * set tev next ev field for non blocking event for freeing
 * after link (alnk) time routine gened in dsgn wide c init file
 */
extern void __alnk_set_tev_nb_free_nextevptr(void *tev_vp,
 void *next_nb_free_vp, int32 ninsts)
{
 struct tev_t *tevp;
 int32 ii;

 tevp = (struct tev_t *) tev_vp;
 for (ii = 0; ii < ninsts; ii++)
  {
   tevp[ii].next_enterptr = (void (*)) next_nb_free_vp;
  }
}

/*
 * set the tev tu rhswp field with ptr to fixed rhswp area for nb tevs only
 */
extern void __alnk_tev_set_tu_nbrhs(void *tev_vp, void *nbrhs_vp,
 int32 nb_rhs_bytsiz, int32 ninsts)
{
 int32 ii;
 int32 wlen;
 struct tev_t *tevp;
 word32 *rhswp;
 
 tevp = (struct tev_t *) tev_vp;
 rhswp = (word32 *) nbrhs_vp; 
 
 /* SJM 07/22/08 - for scalar need to convert to 4 - otherwise know word */
 /* aligned since checked for in asm lnk file */
 /* AIV 10/31/08 - this was wrong - and should be changed */
 //AIV FIXME - change nb_rhs_bytsiz to nb_rhs_blen and pass wlen to this 
 //wrapper
 //AIV64
 wlen = wlen_((nb_rhs_bytsiz/(2*WRDBYTES))*WBITS);

 for (ii = 0; ii < ninsts; ii++)
  {
   /* SJM 08/27/08 - need 2 times here for rhs since both a and b parts */
   tevp[ii].tu.rhs_wp = &(rhswp[2*ii*wlen]);
  }
}

/*
 * same as above 2-state version
 */
extern void __alnk_tev_set_tu_nbrhs_2s(void *tev_vp, void *nbrhs_vp,
 int32 nb_rhs_bytsiz, int32 ninsts)
{
 int32 ii, wlen;
 struct tev_t *tevp;
 word32 *rhswp;
 
 tevp = (struct tev_t *) tev_vp;
 rhswp = (word32 *) nbrhs_vp; 
 
 /* SJM 07/22/08 - for scalar need to convert to 4 - otherwise know word */
 /* aligned since checked for in asm lnk file */
 /* AIV 10/31/08 - this was wrong - and should be changed */
 //AIV FIXME - change nb_rhs_bytsiz to nb_rhs_blen and pass wlen to this 
 //wrapper
 //AIV64
 wlen = wlen_((nb_rhs_bytsiz/WRDBYTES)*WBITS);

 for (ii = 0; ii < ninsts; ii++)
  {
   /* SJM 08/27/08 - need 2 times here for rhs since both a and b parts */
   tevp[ii].tu.rhs_wp = &(rhswp[ii*wlen]);
  }
}

/*
 * set tev delay word64 field - know always passed constant
 * after link (alnk) time routine gened in dsgn wide c init file
 *
 * SJM 05/11/08 - BEWARE - since taking apart for assembler this may not
 * work on big endian machines - or maybe asm combining wrong
 */

extern void __alnk_set_tev_del(void *tev_vp, word64 gdel, int32 ninsts)
{
 int32 ii;
 struct tev_t *tevp;

 tevp = (struct tev_t *) tev_vp;
 for (ii = 0; ii < ninsts; ii++)
  {
   tevp[ii].delay = gdel;
  }
}

/*
 * copy tev delay word64 field - fits in 32 bits case
 * after link (alnk) time routine gened in dsgn wide c init file
 */
extern void __alnk_cp_is1v_32b_tev_dels(void *tev_vp, void *vp, int32 ninsts)
{
 int32 ii;
 struct tev_t *tevp;
 word32 *wp;

 tevp = (struct tev_t *) tev_vp;
 wp = (word32 *) vp;
 for (ii = 1; ii < ninsts; ii++)
  {
   tevp[ii].delay = (word64) wp[ii];
  }
}


#ifndef __CVC32__
/*
 * copy tev delay word64 field - needs all 64 bits case
 * after link (alnk) time routine gened in dsgn wide c init file
 */
//AIV64????
extern void __alnk_cp_is1v_64b_tev_dels(void *tev_vp, word32 *wp, int32 ninsts)
{
 int32 ii;
 struct tev_t *tevp;
 word64 w64;

 tevp = (struct tev_t *) tev_vp;
 for (ii = 2; ii < 2*ninsts; ii += 2)
  {
   w64 = (word64) wp[ii] | (((word64) wp[ii + 1]) << 32);
   tevp[ii].delay = w64;
  }
}
#endif


/*
 * ALNK ROUTINES TO SET NCHGLST ELS
 */

/*
 * per mod ASL time routine that traverses every net in tran channels
 * setting every vtx nchgp when needed
 * 
 * for nchges ranges that can never lead to propagations do not record
 */
//AIV TRAN
extern void __alnk_set_trchan_vtx_nchgs(void) 
{
 int32 vi, ni, bi, bi2, ii;
 struct mod_t *mdp;
 struct vbinfo_t *vbip;
 struct chanrec_t *chanp;
 struct traux_t *trap;
 struct bidvtx_t *bidvtxp; 
 struct net_t *np, *np2;
 t_midat *tidp;

 mdp = __init_mdp;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   if (np->ntraux == NULL) continue;

   trap = np->ntraux;
   /* AIV 02/19/12 - if chan vectored can just alloc the one whole net */
   /* fixed change no reason for per bit */
   vbip = trap->vbitchans[0];
   chanp = &(__chantab[vbip->chan_id]);
   if (chanp->chan_vectored) continue;

   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     /* notice first step of alnk processing is updating (possibly post */
     /* load lib) in link solib the moditp idp addresses */
     tidp = mdp->moditps[ii]->it_idp;
     for (bi = np->nwid - 1; bi >= 0; bi--) 
      {
       vbip = trap->vbitchans[ii*np->nwid + bi];
       if (vbip == NULL) continue;

       chanp = &(__chantab[vbip->chan_id]);
       if (np->n_isavec)
        {
         if (__net_chg_nd_store(np, bi, bi))
          {
           set_trchan_1vtx_nchg_fld(np, bi, vbip, tidp);
          }
        }
       else
        {
         if (__net_chg_nd_store(np, -1, -1))
          {
           set_trchan_1vtx_nchg_fld(np, -1, vbip, tidp);
          }
        }

       /* then traverse the channel's inout vertex list */
       bidvtxp = &(chanp->bid_vtxtab[0]);
       if (bidvtxp != NULL)
        {
         for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
          {
           np2 = bidvtxp->vnp;
           if (np != np2)
            {
             bi2 = bidvtxp->vi1;
             if (np2->n_isavec)
              {
               if (__net_chg_nd_store(np2, bi2, bi2))
                {
                 set_trchan_1vtx_nchg_fld(np2, bi2, vbip, tidp);
                }
              }
             else
              {
               if (__net_chg_nd_store(np2, -1, -1))
                {
                 set_trchan_1vtx_nchg_fld(np2, -1, vbip, tidp);
                }
              }
            }
          }
        }
      }
    }
  }
}

/*
 * link a tran channel vertex to the compile time know nchgdat record
 * in the design wide comm .s file
 *
 * linking happens during the alnk processing that will eventually go into
 * a.out file of the model
 */
static void set_trchan_1vtx_nchg_fld(struct net_t *np, int32 bi, 
 struct vbinfo_t *vbip, t_midat *tidp)
{
 struct vtx_t *vtxp;
 struct chanrec_t *chanp;
 struct net_chg_t *ncp;
 struct nchglst_t *nchglp;

 chanp = &(__chantab[vbip->chan_id]);
 if (chanp->chan_no_vtxs) return;

 /* AIV 12/12/07 - if no need to record net change no need to link */
 if (!__needs_netchg_record(np)) return;

 vtxp = vbip->vivxp;
 ncp = __find_nchg_range(np, bi, bi);
 /* DBG remove -- */ 
 if (np != vtxp->vnp) __misc_terr(__FILE__, __LINE__);
 if (ncp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---- */ 
 nchglp = (struct nchglst_t *) tidp[ncp->nchg_idp_ofs];
 vtxp->nchgp = nchglp;
}

/*
 * set a udp tab ptr address passed the literal label of the udp tab ptr
 * in the comm .s file
 *
 * linking happens during the alnk processing that will eventually go into
 * a.out file of the model
 *
 * SJM 07/28/08 - LOOKATME - could move udp area to comm .s file to save
 * some indirections - but requires complicated interpreter change
 */
extern void __alnk_set_udptab_adrs(void *udptab_l_adr, void *udptab_e_adr,
 int32 udp_idnum)
{
 struct udp_t *udpp;
 word32 *wp_tab_l, *wp_tab_e;

 udpp = __dsgn_udp_ndx[udp_idnum];
 wp_tab_l = (word32 *) udptab_l_adr;
 wp_tab_e = (word32 *) udptab_e_adr;

 *wp_tab_l = (word32) udpp->utab->ludptab;
 if (wp_tab_e != NULL) *wp_tab_e = (word32) udpp->utab->eudptabs;
}

/*
 * set a pth del addr (ptr) in a specify path 
 *
 * linking happens during the alnk processing that will eventually go into
 * a.out file of the model
 */
extern void __alnk_set_pth_del_adr(void *pthdel_adr, int32 pth_id)
{
 word32 *wp;
 struct spcpth_t *pthp; 
 
 pthp = __init_mdp->m_pth_ndx[pth_id];
 wp = (word32 *) pthdel_adr;
 *wp = (word32) pthp->pth_du.d4v;
}
          
/*
 * set a tchk tchg addr (ptr) in a specify path 
 *
 * linking happens during the alnk processing that will eventually go into
 * a.out file of the model
 */
extern void __alnk_set_tchk_tchg_adr(void *tchk_tchg_adr, int32 npp_id)
{
 struct net_pin_t *npp;
 word32 *wp;

 // chktcp = (struct chktchg_t *) tchk_tchg_adr; 
 wp = (word32 *) tchk_tchg_adr; 
 npp =  __init_mdp->m_npp_ndx[npp_id];
 /* DBG remove -- */
 if (npp->chgsubtyp != NPCHG_TCCHK) __misc_terr(__FILE__, __LINE__);
 /* -- */
 *wp = (word32) npp->elnpp.echktchgp;
}

/*
 * set a stmt record's enter ptr label addr
 */
extern void __alnk_set_stmt_entptr(void *stmt_entp, int32 sti)
{
 struct st_t *stp;

 /* AIV 03/02/12 - this can just use __init_mdp here no reason to pass mod ndx */
 stp = __init_mdp->mstmts[sti];
 stp->enterptr = stmt_entp;
}
     
/*
 * set a nets npp enter pointer label addr
 */
extern void __alnk_set_npp_entptr(void *npp_entp, int32 ni)
{
 struct net_t *np;

 np = &(__init_mdp->mnets[ni]);
 np->enter_npp = npp_entp;
}

/*
 * set DCEA_modid_netndx_dcendx to point to a loaded dce 
 */
extern void __alnk_set_dcevnt(void *dcep_vp, int32 ni, int32 di)
{
 struct dce_info_t *dceip;
 struct net_t *np;
 struct dcevnt_t *dcep, **dcep_ptr;

 np = &(__init_mdp->mnets[ni]);
 dcep_ptr = (struct dcevnt_t **) dcep_vp;
 dceip = np->dcetable;
 dcep = dceip->dtable[di];
 *dcep_ptr = dcep;
}

/*
 * link GRP_modndx_grpndx to the malloc gref
 */
extern void __alnk_set_gref(void *grp_vp, int32 gi)
{
 struct gref_t *grp, **grp_ptr;

 grp = &(__init_mdp->mgrtab[gi]);
 grp_ptr = (struct gref_t **) grp_vp;
 *grp_ptr = grp;
}

/*
 * link GRP_modndx_grpndx to the malloc gref
 */
extern void __alnk_set_gate(void *gate_vp, int32 gi)
{
 struct gate_t *gp, **gp_ptr;

 gp = &(__init_mdp->mgates[gi]);
 gp_ptr = (struct gate_t **) gate_vp;
 *gp_ptr = gp;
}

/*
 * link CA_modndx_cndx to the malloc conta addr
 */
extern void __alnk_set_conta(void *conta_vp, int32 ci)
{
 struct conta_t *cap, **conta_ptr;

 cap = &(__init_mdp->mcas[ci]);
 conta_ptr = (struct conta_t **) conta_vp;
 *conta_ptr = cap;
}

/*
 * set _np_ to point to the malloc net address
 */
extern void __alnk_set_net_addr(void *net_vp, int32 ni)
{
 struct net_t *np, **net_ptr;

 np = &(__init_mdp->mnets[ni]);
 net_ptr = (struct net_t **) net_vp;
 *net_ptr = np;
}

/*
 * set TSKP_modid_taskndx to point to the loaded task
 */
extern void __alnk_set_task_addr(void *task_vp, int32 ti)
{
 int32 i;
 struct task_t *tskp, **task_ptr;

//AIV LOOKATME AIV FIXME - cannot use index
//there should be too many of these and they are used at setup so this
//shouldn't be a big deal - but this should be a table
 tskp = __init_mdp->mtasks;
 for (i = 0; i < ti; i++)
  {
   tskp = tskp->tsknxt; 
  }
 task_ptr = (struct task_t **) task_vp;
 *task_ptr = tskp;
}

/*
 * set one npp NPPA address to the malloc net_pin_t address
 */
extern void __alnk_set_npp_addr(void *npp_vp, int32 nppi)
{
 struct net_pin_t *npp, **npp_ptr;

 npp = __init_mdp->m_npp_ndx[nppi];
 npp_ptr = (struct net_pin_t **) npp_vp;
 *npp_ptr = npp;
}

/*
 * set one expr XPR address to the malloc expr address
 */
extern void __alnk_set_xpr_addr(void *xpr_vp, int32 xi)
{
 struct expr_t *xp, **xpr_ptr;
 struct expr_tab_t *etp;

 etp = __init_mdp->expr_tab;
 xp = etp->table[xi];
 xpr_ptr = (struct expr_t **) xpr_vp;
 *xpr_ptr = xp;
}

/*
 * set ialst enter ptr label addr
 */
extern void __alnk_ialst_enters(void **ialst_arrp, int32 mod_id)
{
 struct ialst_t *ialp;
 struct mod_t *mdp;
 int32 ndx;

 mdp = __dsgn_mod_ndx[mod_id];
 ndx = 0;
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt, ndx++)
  {
   if (ialp->needs_thread) continue;
   ialp->enterptr = ialst_arrp[ndx];
  }
}

//############################################################################

/* AIV 07/09/08 - gcc only inlines for -O3 - made this a macro */
#ifdef __CVC_DEBUG__
/* debug version checks for null misc terr */
#define asl_loc_add_nb_event_(tevp)\
{\
 if (__nb_te_endp == NULL) __misc_terr(__FILE__, __LINE__);\
 __nb_te_endp->tenxtp = tevp;\
 __nb_te_endp = tevp;\
}
#else
/* just add to non-blocking list */
#define asl_loc_add_nb_event_(tevp)\
{\
 __nb_te_endp->tenxtp = tevp;\
 __nb_te_endp = tevp;\
}
#endif

/*
 * ASM LIB ROUTINES USED FOR RUN TIME SCHEDULER SERVICES
 */

/* 
 * gen asm code lib routine to access upward relative XMR from gref
 */
extern void *__asl_get_uprel_idp(struct gref_t *grp)
{
 int32 inum;

 inum = get_inum_();
 return(grp->targu.uprel_itps[inum]->it_idp);
}

/* 
 * gen asm code lib routine to access downward relative XMR from gref
 *
 * LOOKATME could pass 
 */
extern void *__asl_get_downrel_idp(struct gref_t *grp)
{
 struct itree_t *itp;

 itp = get_itp_();
 itp = __find_unrt_targitp(grp, itp, 0);
 return(itp->it_idp);
}

extern void __asl_sched_proc_delay(struct st_t *stp, struct tev_t *tevp)
{
 struct delctrl_t *dctp;
 word64 t;

 /* AIV 03/25/09 - this is variable maybe triggered multiple times depending */
 /* the the variable delay value */
 /* pretty rare but if this is in task can trigger by calling tasks */
 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 dctp = stp->st.sdc;
 t = __get_del(dctp->dc_du, dctp->dc_delrep);  
 tevp->etime = __simtime + t;
 __cur_thd->thdtevp = tevp;
 tevp->tu.tethrd = __cur_thd;

 if (t == 0ULL)
  {
   asl_loc_add_pnd0_event(tevp);
  }
 else asl_loc_insert_event_(tevp);
}

/*
 * add a pound 0 event
 * AIV LOOKATME - make sure gcc inlines these or could be macros?????
 */
static void asl_loc_add_pnd0_event(struct tev_t *tevp)
{
 /* AIV 01/03/08 - notice only need to set the end to next event end fence */
 /* if  (__p0_te_hdrp == __cur_tevp) - better to set everytime and not do */
 /* if stmt */
 if (__p0_te_hdrp == NULL) __p0_te_hdrp = __p0_te_endp = tevp;
 else 
  { 
   __p0_te_endp->tenxtp = tevp; __p0_te_endp = tevp; 
   tevp->tenxtp = __free_event_pnd0_tevp;
  }
}

/*
 * add a event to the pnd0 event list doubly linked
 */
static void asl_loc_add_pnd0_event_dl(struct tev_t *tevp)
{
 if (__p0_te_hdrp == NULL) 
  {
   __p0_te_hdrp = __p0_te_endp = tevp;
   tevp->teprevp = NULL;
  }
 else 
  { 
   tevp->teprevp = __p0_te_endp; 
   __p0_te_endp->tenxtp = tevp; 
   __p0_te_endp = tevp; 
  }
}
 
/*
 * constant time version of  __asl_sched_proc_delay
 */
extern void __asl_sched_proc_delay_const(struct tev_t *tevp)
{
 /* AIV 09/01/09 - this is thread version may need a new one per thread */
 /* was not linking out because trigger flag not set */
 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 tevp->etime = __simtime + tevp->delay;
 __cur_thd->thdtevp = tevp;
 tevp->tu.tethrd = __cur_thd;
 asl_loc_insert_event_(tevp);
}

/*
 * constant time version of  __asl_sched_proc_delay used in task
 */
extern void __asl_sched_proc_delay_task_const(struct tev_t *tevp)
{
 word64 schtim;

 /* AIV 11/03/07 - these are needed for thread (task) calls */
 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 schtim = __simtime + tevp->delay;
 tevp->etime = schtim;
 __cur_thd->thdtevp = tevp;
 tevp->tu.tethrd = __cur_thd;
 asl_loc_insert_event_(tevp);
}

/*
 * constant time 0 of __asl_sched_proc_delay used in thread code
 */
extern void __asl_sched_proc_delay_pnd0(struct tev_t *tevp)
{
 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 __cur_thd->thdtevp = tevp;
 tevp->tu.tethrd = __cur_thd;

 /* maybe should remove option ????? */
 asl_loc_add_pnd0_event(tevp);
}

/*
 * constant time 0 of __asl_sched_proc_delay used in task
 */
extern void __asl_sched_proc_delay_task_pnd0(struct tev_t *tevp)
{
 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 __cur_thd->thdtevp = tevp;
 tevp->tu.tethrd = __cur_thd;

 /* maybe should remove option ????? */
 asl_loc_add_pnd0_event(tevp);
}

/*
 * no thread overhead variable delay schedule
 */
extern void __asl_sched_proc_delay_nt(struct st_t *stp, struct tev_t *tevp)
{
 struct delctrl_t *dctp;
 word64 t;

 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 check_for_active_event(tevp);
#endif
 tevp->trigger = TRUE;
 /* -- */

 dctp = stp->st.sdc;
 t = __get_del(dctp->dc_du, dctp->dc_delrep);  
 
 tevp->etime = __simtime + t;
 if (t == 0ULL)
  {
   asl_loc_add_pnd0_event(tevp);
  }
 else asl_loc_insert_event_(tevp);
}

/*
 * no thread overhead constant delay schedule
 */
extern void __asl_sched_proc_delay_const_nt(struct tev_t *tevp)
{
 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 check_for_active_event(tevp);
#endif
 tevp->trigger = TRUE;
 /* -- */

 tevp->etime = __simtime + tevp->delay;
 asl_loc_insert_event_(tevp);
}

/*
 * no thread overhead constant pound 0 delay schedule
 */
extern void __asl_sched_proc_delay_pnd0_nt(struct tev_t *tevp)
{
 /* AIV 12/17/07 - rare case may need to alloc an event, #0 in a loop */
 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 tevp->etime = __simtime;
 asl_loc_add_pnd0_event(tevp);
}

/*
 * asm lib routine to exec (arm) proc event ctrl timing control thread
 *
 * unlike interpreter - this does not set current thread continuation stmt or
 * current thread rhs delay value if present
 */
extern void __asl_arm_ectrl(struct tev_t *tevp, size_t ndx)
{
 /* DBG remove --- */
#ifdef __CVC_DEBUG__
 check_for_active_event(tevp);
#endif
 /* --- */

 /* build after trigger fires, startup event */
 /* notice this event record is not linked onto any event list for now */
 /* link event back to thread */
 __cur_thd->thdtevp = tevp;
 tevp->tu.tethrd = __cur_thd;

 /* maybe need rexec warning here */
 /* AIV 10/19/07 - really need to save now just dctp->dceschd_tev_ofs */
 /* need this for free_thd_stuff disable code */
 __cur_thd->th_dctp_tev_ofs = ndx;
}


/*
 * asmlib routine to save old (return tn that goes on stack) and
 * set new assoc tsk in current thread record 
 */
extern void *__asl_setsav_assoc_tsk(struct st_t *stp)
{
 struct task_t *tskp;

 tskp = __cur_thd->assoc_tsk;
 __cur_thd->assoc_tsk = stp->st.snbtsk;
 return(tskp);
}

/*
 * asm lib routine to replace top of itstk and set cur thd itree context
 */
//AIV FIXME - just inline this
extern void __asl_repl_curth_itp(void)
{
 /* AIV 02/03/06 - need to save the current inst_ptr before pop */
 __cur_thd->th_idp = __idp;
}

/*
 * asm lib routine to replace top of itstk from cur thd saved itree cntxt
 */
extern void *__asl_repl_itstk_top(void)
{
 t_midat *idp;

 idp = __cur_thd->th_idp;
 return(idp);
}

/*
 * ROUTINES FOR NON-BLOCKING ASSIGN HANDLING
 *
 * AIV 11/30/09 - new routines have the following struct for new changes for
 * non-blocking constant values
 * 
 * routines with _t are when __all_nb_same_time flag is true that is
 * all <= #del have the same value for #del (usually 1) 
 *
 * routines with _last are for multiple calls to non-blocking constants
 * where the second call is know to be the same as the last set time
 * so can just put event on to end to last nb list
 *
 * __asl_sched_nbrhs_scalar_dctrl_const //regulare constant scalar nb
 * __asl_sched_nbrhs_scalar_dctrl_const_t //all known to be <= #same
 * __asl_sched_nbrhs_scalar_dctrl_const_last //just put on end of list
 */

/*
 * asm lib routine to build and return index of a non blocking event with
 * no delay - regular r <= b statement
 */
extern void __asl_bld_nb_nodelay_tev(struct tev_t *tevp)
{
 /* alloc new non-blocking no delay event and set stmt for enter point */
 /* AIV 07/25/08 - these don't need to alloc new nb events */
 if (tevp->trigger) return;
 tevp->trigger = TRUE;

 asl_loc_add_nb_event_(tevp);
}

extern void __asl_sched_nbrhs_scalar_dctrl(struct tev_t *tevp, 
 struct st_t *del_stp, word32 rhsval)
{
 struct delctrl_t *dctp;
 word64 t, schtime;

 if (tevp->trigger) tevp = asl_loc_get_new_event_nb(tevp);
 else tevp->trigger = TRUE;

 dctp = del_stp->st.sdc;
 /* t may be explicit #0 */
 t = __get_del(dctp->dc_du, dctp->dc_delrep);  

 schtime = __simtime + t;
 tevp->etime = schtime;
 /* alloc new non-blocking no delay event and set stmt for enter point */
 tevp->scalar_nb_val = (byte) rhsval;
 /* AIV 02/15/08 - variable time delay might be 0 or x/z eval to 0 */ 
 /* should just be adding to current nb time list */
 /* if not doing this it ruins new minimum time movement */
 /* AIV 06/17/08 - this was suppose to check t == 0 */
 if (t == 0) 
  {
   asl_loc_add_nb_event_(tevp);
   return;
  }
 asl_loc_insert_event_nb_(tevp);
}

extern void __asl_sched_nbrhs_scalar_dctrl_const(struct tev_t *tevp, 
  word32 rhsval)
{
 word64 schtim;
 
 /* AIV 07/25/08 - produces better code to have the new version copy */
 /* the tevp->delay otherwise this need to use two regs to store 64-bit */
 /* time value the rare case is that it allocs a new event */
 if (tevp->trigger) tevp = asl_loc_get_new_event_nb(tevp);
 else tevp->trigger = TRUE;

 schtim = __simtime + tevp->delay;
 tevp->etime = schtim;
 /* alloc new non-blocking no delay event and set stmt for enter point */
 tevp->scalar_nb_val = (byte) rhsval;
 asl_loc_insert_event_nb_(tevp);
}

/*
 * all same #del version
 */
extern void __asl_sched_nbrhs_scalar_dctrl_const_t(struct tev_t *tevp, 
  word32 rhsval)
{
 
 /* AIV 07/25/08 - produces better code to have the new version copy */
 /* the tevp->delay otherwise this need to use two regs to store 64-bit */
 /* time value the rare case is that it allocs a new event */
 if (tevp->trigger) tevp = asl_loc_get_new_event_nb(tevp);
 else tevp->trigger = TRUE;

 /* alloc new non-blocking no delay event and set stmt for enter point */
 tevp->scalar_nb_val = (byte) rhsval;
 
 /* just check for NULL if already set otherwise just add to end of list */
 if (__last_nb_hp == NULL)
  {
   tevp->etime = __simtime + tevp->delay;
   asl_loc_insert_event_nb_t_(tevp);
   return;
  }

 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
}

/*
 * known to have same time as __last_nb_hp - just add to end of list
 */
extern void __asl_sched_nbrhs_scalar_dctrl_const_last(struct tev_t *tevp, 
  word32 rhsval)
{
 /* AIV 07/25/08 - produces better code to have the new version copy */
 /* the tevp->delay otherwise this need to use two regs to store 64-bit */
 /* time value the rare case is that it allocs a new event */
 if (tevp->trigger) tevp = asl_loc_get_new_event_nb(tevp);
 else tevp->trigger = TRUE;

 /* just set value and add to end of list */
 tevp->scalar_nb_val = (byte) rhsval;
 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
}


extern void __asl_sched_nbrhs_nomem_dctrl_const(struct tev_t *tevp)
{
 word64 schtim;
 
 if (tevp->trigger) tevp = asl_loc_get_new_event_nb(tevp);
 else tevp->trigger = TRUE;

 schtim = __simtime + tevp->delay;
 tevp->etime = schtim;
 /* alloc new non-blocking no delay event and set stmt for enter point */
 asl_loc_insert_event_nb_(tevp);
}

/*
 * all same #del version
 */
extern void __asl_sched_nbrhs_nomem_dctrl_const_t(struct tev_t *tevp)
{
 
 /* alloc new non-blocking no delay event and set stmt for enter point */
 if (tevp->trigger) tevp = asl_loc_get_new_event_nb(tevp);
 else tevp->trigger = TRUE;

 /* just check for NULL if already set otherwise just add to end of list */
 if (__last_nb_hp == NULL)
  {
   tevp->etime = __simtime + tevp->delay;
   asl_loc_insert_event_nb_t_(tevp);
   return;
  }

 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
}

/*
 * known to have same time as __last_nb_hp - just add to end of list
 */
extern void __asl_sched_nbrhs_nomem_dctrl_const_last(struct tev_t *tevp)
{
 
 if (tevp->trigger) tevp = asl_loc_get_new_event_nb(tevp);
 else tevp->trigger = TRUE;

 /* just set value and add to end of list */
 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
}


/*
 * asm lib routine to build and return index of a non blocking event with
 * delay 
 */
extern void __asl_schd_nb_vardel_rhsconst_dctrl(struct st_t *del_stp, 
 struct tev_t *tevp)
{
 word64 t, schtime;
 struct delctrl_t *dctp;

 if (tevp->trigger) tevp = asl_loc_get_new_event_nb(tevp);
 else tevp->trigger = TRUE;

 dctp = del_stp->st.sdc;
 /* t may be explicit #0 */
 t = __get_del(dctp->dc_du, dctp->dc_delrep);  

 schtime = __simtime + t;
 /* alloc new non-blocking no delay event and set stmt for enter point */
 tevp->etime = schtime;

 /* AIV 12/08/05 - wasn't using the nb #0 list */
 /* final step is inserting event in list */
 /* will never see non delay form here, #0 is like non delay form though */ 
 if (t == 0ULL)
  {
   /* if non blocking procedural assign, insert in normal moved to #0 later */
   /* AIV 07/05/05 - to match XL need nb te list that only processed */
   /* when all pnd 0s done */  
   /* effectively adds another section to current time event queue */
   asl_loc_add_nb_event_(tevp);
  }
 else asl_loc_insert_event_nb_(tevp);
}

/*
 * asm lib routine to sch proc non blocking dctrl delay assign 
 * this is nb proca with #(delay) after <=
 * this arms or schedules something but caller continues without suspend
 *
 */
extern word32 *__asl_sched_nbrhs_dctrl(struct st_t *stp, struct tev_t *tevp,
 int32 nbytes)
{
 struct delctrl_t *dctp;
 word32 *wp;
 word64 schtime, t;

 /* notice asm lib routine alloc rhs value but does not fill it */
 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 dctp = stp->st.sdc;
 /* t may be explicit #0 */
 t = __get_del(dctp->dc_du, dctp->dc_delrep);  
 schtime = __simtime + t;

 /* assume time is current time (as needed for arming ectrl) */
 tevp->etime = schtime;
 /* AIV 12/08/05 - wasn't using the nb #0 list */
 /* final step is inserting event in list */
 /* will never see non delay form here, #0 is like non delay form though */ 
 if (t == 0ULL)
  {
   /* if non blocking procedural assign, insert in normal moved to #0 later */
   /* AIV 07/05/05 - to match XL need nb te list that only processed */
   /* when all pnd 0s done */  
   /* effectively adds another section to current time event queue */
   asl_loc_add_nb_event_(tevp);
  }
 else asl_loc_insert_event_nb_(tevp);
 wp = tevp->tu.rhs_wp;
 return(wp);
}

extern word32 *__asl_sched_nbrhs_dctrl_const(struct tev_t *tevp, int32 nbytes)
{
 word32 *wp;
 word64 schtime;
 
 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 schtime = __simtime + tevp->delay;
 tevp->etime = schtime;

 /* notice asm lib routine alloc rhs value but does not fill it */
 asl_loc_insert_event_nb_(tevp);
 wp = tevp->tu.rhs_wp;
 return(wp);
}

/*
 * all same #del version
 */
extern word32 *__asl_sched_nbrhs_dctrl_const_t(struct tev_t *tevp, int32 nbytes)
{
 word32 *wp;
 
 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */

 /* notice asm lib routine alloc rhs value but does not fill it */
 wp = tevp->tu.rhs_wp;
 /* just check for NULL if already set otherwise just add to end of list */
 if (__last_nb_hp == NULL)
  {
   tevp->etime = __simtime + tevp->delay;
   asl_loc_insert_event_nb_t_(tevp);
   return(wp);
  }

 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
 return(wp);
}

/*
 * known to have same time as __last_nb_hp - just add to end of list
 */
extern word32 *__asl_sched_nbrhs_dctrl_const_last(struct tev_t *tevp, 
 int32 nbytes)
{
 word32 *wp;
 
 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else tevp->trigger = TRUE;

 /* just set value and add to end of list */
 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
 /* notice asm lib routine alloc rhs value but does not fill it */
 wp = tevp->tu.rhs_wp;
 return(wp);
}

extern word32 *__asl_sched_nbrhs_varndx_dctrl(struct st_t *stp, 
 int32 bi, int32 nbytes, struct tev_t *tevp)
{
 struct delctrl_t *dctp;
 word32 *wp;
 word64 schtime, t;

 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else tevp->trigger = TRUE;

 dctp = stp->st.sdc;
 /* t may be explicit #0 */
 t = __get_del(dctp->dc_du, dctp->dc_delrep);  
 schtime = __simtime + t;
 /* assume time is current time (as needed for arming ectrl) */
 tevp->etime = schtime;
 tevp->t2u.bi = bi;

 /* AIV 12/08/05 - wasn't using the nb #0 list */
 /* final step is inserting event in list */
 /* will never see non delay form here, #0 is like non delay form though */ 
 if (t == 0ULL)
  {
   /* if non blocking procedural assign, insert in normal moved to #0 later */
   /* AIV 07/05/05 - to match XL need nb te list that only processed */
   /* when all pnd 0s done */  
   /* effectively adds another section to current time event queue */
   asl_loc_add_nb_event_(tevp);
  }
 else asl_loc_insert_event_nb_(tevp);
 wp = tevp->tu.rhs_wp;
 return(wp);
}


extern word32 *__asl_sched_nbrhs_varndx_dctrl_const(int32 bi, int32 nbytes, 
 struct tev_t *tevp)
{
 word32 *wp;
 word64 schtime;

 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 schtime = __simtime + tevp->delay;
 tevp->etime = schtime;
 tevp->t2u.bi = bi;
 asl_loc_insert_event_nb_(tevp);
 wp = tevp->tu.rhs_wp;
 return(wp);
}

/*
 * all same #del version
 */
extern word32 *__asl_sched_nbrhs_varndx_dctrl_const_t(int32 bi, int32 nbytes, 
 struct tev_t *tevp)
{
 word32 *wp;

 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 tevp->t2u.bi = bi;
 wp = tevp->tu.rhs_wp;
 /* just check for NULL if already set otherwise just add to end of list */
 if (__last_nb_hp == NULL)
  {
   tevp->etime = __simtime + tevp->delay;
   asl_loc_insert_event_nb_t_(tevp);
   return(wp);
  }

 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
 return(wp);
}

extern word32 *__asl_sched_nb_pnd0_lhs_varndx(int32 bi, int32 nbytes, 
 struct tev_t *tevp) 
{
 word32 *wp;
 
 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 tevp->etime = __simtime;
 tevp->t2u.bi = bi;
 asl_loc_add_nb_event_(tevp);
 wp = tevp->tu.rhs_wp;
 return(wp);
}

/*
 * ROUTINES TO DO THE NB VARNDX WITH A SELECT ON THE END
 */

/*
 * select version same as non - 'sel' version but sets tevp->sel_ndx
 */
extern word32 *__asl_sched_nbrhs_varndx_sel_dctrl(struct st_t *stp, 
 int32 bi, int32 nbytes, struct tev_t *tevp, int32 sel_ndx)
{
 struct delctrl_t *dctp;
 word32 *wp;
 word64 schtime, t;

 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else tevp->trigger = TRUE;

 dctp = stp->st.sdc;
 t = __get_del(dctp->dc_du, dctp->dc_delrep);  
 schtime = __simtime + t;
 tevp->etime = schtime;
 tevp->t2u.bi = bi;
 tevp->sel_ndx = sel_ndx;

 if (t == 0ULL)
  {
   asl_loc_add_nb_event_(tevp);
  }
 else asl_loc_insert_event_nb_(tevp);
 wp = tevp->tu.rhs_wp;
 return(wp);
}


/*
 * select version same as non - 'sel' version but sets tevp->sel_ndx
 */
extern word32 *__asl_sched_nbrhs_varndx_dctrl_sel_const(int32 bi, int32 nbytes, 
 struct tev_t *tevp, int32 sel_ndx)
{
 word32 *wp;
 word64 schtime;

 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 schtime = __simtime + tevp->delay;
 tevp->etime = schtime;
 tevp->t2u.bi = bi;
 tevp->sel_ndx = sel_ndx;
 asl_loc_insert_event_nb_(tevp);
 wp = tevp->tu.rhs_wp;
 return(wp);
}

/*
 * select version same as non - 'sel' version but sets tevp->sel_ndx
 */
extern word32 *__asl_sched_nbrhs_varndx_dctrl_const_sel_t(int32 bi, 
 int32 nbytes, struct tev_t *tevp, int32 sel_ndx)
{
 word32 *wp;

 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 tevp->t2u.bi = bi;
 tevp->sel_ndx = sel_ndx;
 wp = tevp->tu.rhs_wp;
 /* just check for NULL if already set otherwise just add to end of list */
 if (__last_nb_hp == NULL)
  {
   tevp->etime = __simtime + tevp->delay;
   asl_loc_insert_event_nb_t_(tevp);
   return(wp);
  }

 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
 return(wp);
}

/*
 * select version same as non - 'sel' version but sets tevp->sel_ndx
 */
extern word32 *__asl_sched_nb_pnd0_lhs_varndx_sel(int32 bi, int32 nbytes, 
 struct tev_t *tevp, int32 sel_ndx) 
{
 word32 *wp;
 
 if (tevp->trigger) tevp = asl_loc_get_new_nbmem_event(tevp, nbytes);
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 tevp->etime = __simtime;
 tevp->t2u.bi = bi;
 tevp->sel_ndx = sel_ndx;
 asl_loc_add_nb_event_(tevp);
 wp = tevp->tu.rhs_wp;
 return(wp);
}

extern word32 *__asl_sched_nbrhs_varndx_dctrl_concat(struct st_t *stp, 
 struct net_t *np, int32 bi, int32 nbytes, struct tev_t *tevp, 
 struct nchglst_t *nchglp)
{
 struct delctrl_t *dctp;
 struct tenbpa_t *nbpap;
 word32 *wp;
 word64 schtime, t;

 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 dctp = stp->st.sdc;
 /* t may be explicit #0 */
 t = __get_del(dctp->dc_du, dctp->dc_delrep);  
 schtime = __simtime + t;
 tevp->etime = schtime;

 /* assume time is current time (as needed for arming ectrl) */
 nbpap = (struct tenbpa_t *) __my_malloc(sizeof(struct tenbpa_t)); 
 tevp->tu.tenbpa = nbpap;
 /* notice asm lib routine alloc rhs value but does not fill it */
 wp = (word32 *) __my_malloc(nbytes);
 nbpap->nbawp = wp; 
 nbpap->nbytes = nbytes;
 nbpap->nblhsu.nblhsnp = np; 
 nbpap->nchglp = nchglp;
 nbpap->bi = bi; 

 /* AIV 12/08/05 - wasn't using the nb #0 list */
 /* final step is inserting event in list */
 /* will never see non delay form here, #0 is like non delay form though */ 
 if (t == 0ULL)
  {
   /* if non blocking procedural assign, insert in normal moved to #0 later */
   /* AIV 07/05/05 - to match XL need nb te list that only processed */
   /* when all pnd 0s done */  
   /* effectively adds another section to current time event queue */
   asl_loc_add_nb_event_(tevp);
  }
 else asl_loc_insert_event_nb_(tevp);
 return(wp);
}


extern word32 *__asl_sched_nbrhs_varndx_dctrl_const_concat(struct net_t *np,
 int32 bi, int32 nbytes, struct tev_t *tevp, struct nchglst_t *nchglp)
{
 struct tenbpa_t *nbpap;
 word32 *wp;
 word64 schtime;

 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 schtime = __simtime + tevp->delay;
 tevp->etime = schtime;
 nbpap = (struct tenbpa_t *) __my_malloc(sizeof(struct tenbpa_t)); 
 tevp->tu.tenbpa = nbpap;
 /* notice asm lib routine alloc rhs value but does not fill it */
 wp = (word32 *) __my_malloc(nbytes);
 nbpap->nbawp = wp; 
 nbpap->nbytes = nbytes;
 nbpap->nblhsu.nblhsnp = np; 
 nbpap->bi = bi; 
 nbpap->nchglp = nchglp;

 asl_loc_insert_event_nb_(tevp);
 return(wp);
}

/*
 * all same #del version
 */
extern word32 *__asl_sched_nbrhs_varndx_dctrl_const_concat_t(struct net_t *np,
 int32 bi, int32 nbytes, struct tev_t *tevp, struct nchglst_t *nchglp)
{
 struct tenbpa_t *nbpap;
 word32 *wp;

 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 nbpap = (struct tenbpa_t *) __my_malloc(sizeof(struct tenbpa_t)); 
 tevp->tu.tenbpa = nbpap;
 /* notice asm lib routine alloc rhs value but does not fill it */
 wp = (word32 *) __my_malloc(nbytes);
 nbpap->nbawp = wp; 
 nbpap->nbytes = nbytes;
 nbpap->nblhsu.nblhsnp = np; 
 nbpap->bi = bi; 
 nbpap->nchglp = nchglp;

 /* just check for NULL if already set otherwise just add to end of list */
 if (__last_nb_hp == NULL)
  {
   tevp->etime = __simtime + tevp->delay;
   asl_loc_insert_event_nb_t_(tevp);
   return(wp);
  }

 __last_nb_hp->nb_endp->tenxtp = tevp;
 __last_nb_hp->nb_endp = tevp;
 return(wp);
}

extern word32 *__asl_sched_nb_pnd0_lhs_varndx_concat(struct net_t *np, int32 bi,
 int32 nbytes, struct tev_t *tevp, struct nchglst_t *nchglp) 
{
 struct tenbpa_t *nbpap;
 word32 *wp;
 
 if (tevp->trigger) tevp = asl_loc_get_new_event(tevp);
 else tevp->trigger = TRUE;

 tevp->etime = __simtime;
 /* assume time is current time (as needed for arming ectrl) */
 nbpap = (struct tenbpa_t *) __my_malloc(sizeof(struct tenbpa_t)); 
 tevp->tu.tenbpa = nbpap;
 /* notice asm lib routine alloc rhs value but does not fill it */
//AIV FIXME - if static event this could be static as well?????
 wp = (word32 *) __my_malloc(nbytes);
 nbpap->nbawp = wp; 
 nbpap->nbytes = nbytes;
 nbpap->nblhsu.nblhsnp = np; 
 nbpap->nchglp = nchglp;
 nbpap->bi = bi; 

 asl_loc_add_nb_event_(tevp);
 return(wp);
}

/*
 * asm lib routine to arm procedural non blocking rhs ectrl assign 
 * this is nb proca with @(ectrl) after <=
 *
 * know wrapper asm routine leaves tev ndx in %eax (returns) 
 * this arms event but caller continues without thread suspend
 */
extern word32 *__asl_arm_nb_ectrl(struct st_t *stp, struct tev_t *tevp)
{
 struct tev_t *tevp2;
 struct delctrl_t *dctp;
 word32 *wp;
 
 /* AIV 05/01/08 - the rare case these are schedule due to the count */
 /* being zero - need to just fill the value since it is already schd */
 /* at the current time */
 if (tevp->trigger) 
  {
   wp = tevp->tu.rhs_wp;
   return(wp);
  }
 else  tevp->trigger = TRUE;

 /* assume time is current time (as needed for arming ectrl) */
 tevp->nb_evctrl = TRUE;
 dctp = stp->st.sdc;
 /* for event control form need to set dctp field */
 if ((tevp2 = (struct tev_t *) __idp[dctp->dceschd_tev_ofs]) != NULL)
  {
   /* move to end element of list */
   /* could save end pointer if too slow ? */
   for (; tevp2->tenxtp != NULL; tevp2 = tevp2->tenxtp) ;

   /* add tev to the end */
   tevp2->tenxtp = tevp;
   tevp->teprevp = tevp2;

   /* make sure tevp seen as end */
   tevp->tenxtp = NULL;
  }
// ===> why not set?
 else __idp[dctp->dceschd_tev_ofs] = (t_midat) tevp;

 /* notice asm lib routine alloc rhs value but does not fill it */
 wp = tevp->tu.rhs_wp;
 return(wp);
}

extern word32 *__asl_arm_nb_varndx_ectrl(struct st_t *stp, struct tev_t *tevp, 
 int32 bi)
{
 struct tev_t *tevp2;
 struct delctrl_t *dctp;
 word32 *wp;

 /* assume time is current time (as needed for arming ectrl) */
 tevp->etime = __simtime;
 tevp->t2u.bi = bi;

 /* AIV 05/01/08 - the rare case these are schedule due to the count */
 /* being zero - need to just fill the value since it is already schd */
 /* at the current time */
 if (tevp->trigger) 
  {
   wp = tevp->tu.rhs_wp;
   return(wp);
  }
 else tevp->trigger = TRUE;

 dctp = stp->st.sdc;
 if ((tevp2 = (struct tev_t *) __idp[dctp->dceschd_tev_ofs]) != NULL)
  {
   /* could save end pointer if too slow ? */
   /* SJM 08/26/08- notice this is moving to end */
   for (; tevp2->tenxtp != NULL; tevp2 = tevp2->tenxtp) ;
   tevp2->tenxtp = tevp;
   tevp->teprevp = tevp2;
   tevp->tenxtp = NULL;
  }
 else __idp[dctp->dceschd_tev_ofs] = (t_midat) tevp;

 wp = tevp->tu.rhs_wp;
 return(wp);
}

/*
 * allocate a new event since the other one is active
 */
static struct tev_t *asl_loc_get_new_event(struct tev_t *tevp)
{
 struct tev_t *new_tevp;

 if (__free_tev_ndx > 1)
  {
   new_tevp = __free_tevs[--__free_tev_ndx];
  }
 else
  {
   new_tevp = (struct tev_t *) __my_malloc(sizeof(struct tev_t));
  }

 new_tevp->enterptr  = tevp->enterptr;
 new_tevp->te_idp = tevp->te_idp;
 /* LOOKATME - maybe zeroing to init bit fields unportable */
 /* AIV 09/28/07 - only need to zero the first two words of the struct */
 /* since the rest are set here no need to zero all fields */
 memset(new_tevp, 0, 8);
 /* AIV 07/25/08 - need to copy the delay for the constant values */
 /* an actually alloc of a new one is rare this way time doesn't need to */
 /* be save across calls to this routine */
 new_tevp->delay = tevp->delay;
 new_tevp->trigger = TRUE;
 new_tevp->next_enterptr = __process_next_event_free_enterp;
 return(new_tevp);
}

/*
 * allocate a new nb event since the other one is active
 * same as above except sets enter pointer to the nb 'free' flow graph pointer
 * which is in next_enterptr
 */
static struct tev_t *asl_loc_get_new_event_nb(struct tev_t *tevp)
{
 struct tev_t *new_tevp;

 if (__free_tev_ndx > 1)
  {
   new_tevp = __free_tevs[--__free_tev_ndx];
  }
 else
  {
   new_tevp = (struct tev_t *) __my_malloc(sizeof(struct tev_t));
  }

 /* set to 'free' fg enter location */
 new_tevp->enterptr  = tevp->next_enterptr;
 new_tevp->te_idp = tevp->te_idp;
 /* LOOKATME - maybe zeroing to init bit fields unportable */
 /* AIV 09/28/07 - only need to zero the first two words of the struct */
 /* since the rest are set here no need to zero all fields */
 /* AIV 07/25/08 - need to copy the delay for the constant values */
 /* an actually alloc of a new one is rare this way time doesn't need to */
 /* be save across calls to this routine */
 new_tevp->delay = tevp->delay;
 memset(new_tevp, 0, 8);
 new_tevp->trigger = TRUE;
 return(new_tevp);
}

/*
 * same as above except the ->next_enterptr is pointer else where
 * it must free the non blocking storage area as well
 */
static struct tev_t *asl_loc_get_new_nbmem_event(struct tev_t *tevp, 
 int32 nbytes)
{
 word32 *wp;
 struct tev_t *new_tevp;

 if (__free_tev_ndx > 1)
  {
   new_tevp = __free_tevs[--__free_tev_ndx];
  }
 else
  {
   new_tevp = (struct tev_t *) __my_malloc(sizeof(struct tev_t));
  }

 new_tevp->enterptr  = tevp->next_enterptr;
 new_tevp->te_idp = tevp->te_idp;
 memset(new_tevp, 0, 8);
 wp = (word32 *) __my_malloc(nbytes);
 new_tevp->tu.rhs_wp = wp;
 new_tevp->trigger = TRUE;
 new_tevp->t2u.nb_rhs_size = nbytes;
 /* AIV 07/25/08 - need to copy the delay for the constant values */
 /* an actually alloc of a new one is rare this way time doesn't need to */
 /* be save across calls to this routine */
 /* AIV 05/10/10 - removed duplicate line */
 new_tevp->delay = tevp->delay;
 return(new_tevp);
}

static struct tev_t *asl_loc_get_new_thread_event(void)
{
 struct tev_t *new_tevp;

 if (__free_tev_ndx > 1)
  {
   new_tevp = __free_tevs[--__free_tev_ndx];
  }
 else
  {
   new_tevp = (struct tev_t *) __my_malloc(sizeof(struct tev_t));
  }

 new_tevp->enterptr  = __process_compiled_thrd_ev_enterp;
 new_tevp->etime = __simtime;
 new_tevp->te_idp = __idp;
 /* LOOKATME - maybe zeroing to init bit fields unportable */
 /* AIV 09/28/07 - only need to zero the first two words of the struct */
 /* since the rest are set here no need to zero all fields */
 memset(new_tevp, 0, 8);
 new_tevp->trigger = TRUE;
 new_tevp->next_enterptr = __process_next_event_free_enterp;
 return(new_tevp);
}

/* AIV extern just calls the local routine */
/* this is needed so all the local asl_loc_get_new_events will be inlined */
/* by gcc */
extern struct tev_t *__asl_loc_get_new_thread_event(void)
{
 return(asl_loc_get_new_thread_event());
}

/* AIV extern just calls the local routine */
/* this is needed so all the local asl_loc_get_new_events will be inlined */
/* by gcc */
extern struct tev_t *__asl_loc_get_new_event(struct tev_t *tevp)
{
 return(asl_loc_get_new_event(tevp));
}

/*
 * exec a name block - same as interpreter
 *
 * task added to thread tree as if going to be scheduled but then execed
 * immediately
 */
extern void __asl_sched_namblk_thd(struct st_t *stp)
{
 struct task_t *tskp;
 struct thread_t *thp;
 int32 sav_ndx;

 tskp = stp->st.snbtsk;
 __cur_thd->thofscnt = 1;
 __cur_thd->thnxtstp = stp->stnxt;
 /* AIV 1/11/06 - must save the return label index  because might be in */
 /* a task - think ndx is needed here right ??? */
 sav_ndx = __cur_thd->thd_ret_lab_ndx;

 thp = __setup_tsk_thread(tskp);

 thp->thpar = __cur_thd;
 __cur_thd->thofs = thp;
 __cur_thd = thp;
 /* for named blocks, know never xmr */
 __cur_thd->th_idp = __idp; 
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 if (__cur_thd->thnxtstp == NULL) __misc_terr(__FILE__, __LINE__);
#endif
 __cur_thd->thd_ret_lab_ndx = sav_ndx;
}

/* 
 * asm lib routine to sched all prongs of fork join - sched fork wrapper
 * next insns must be suspend seq., so exec all scheduled threads happens
 */
extern void __asl_sched_fork(struct st_t *stp, struct st_t *nxtstp)
{
 int32 fji;
 struct thread_t *thp;
 int32 sav_slin_cnt, sav_sfnam_ind;
 struct thread_t *last_thp;
 struct st_t *fjstp;

#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 /* DBG remove */
 if (__cur_thd->thofscnt != 0) __misc_terr(__FILE__, __LINE__); 
 /* --- */ 
#endif
 /* convert current thread (one-up) to fork joint32 header */
 /* and build (link in) list of per statement threads */  
 last_thp = NULL;
 for (fji = 0;; fji++)
  {
   if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
   
   /* SJM 03/07/02 - for optimizer must always schedule 1st stmt of unblk */
   /* instead of unnamed blk as now */
   if (fjstp->stmttyp == S_UNBLK) fjstp = fjstp->st.sbsts;
   
   /* using location of fork-join statement as enable loc. not fork loc. */
   sav_sfnam_ind = __sfnam_ind;
   sav_slin_cnt = __slin_cnt;
   __sfnam_ind = fjstp->stfnam_ind;
   __slin_cnt = fjstp->stlin_cnt;
   /* schedule each subthread after building it */
   thp = asl_loc_sched_fj_subthread(fjstp);

   __sfnam_ind = sav_sfnam_ind;
   __slin_cnt = sav_slin_cnt;

   __cur_thd->thofscnt += 1;
   if (last_thp == NULL) __cur_thd->thofs = thp;
   else { thp->thleft = last_thp; last_thp->thright = thp; }
   thp->thpar = __cur_thd;
   thp->th_idp = __idp;
   /* flag on fork-join component to indicate must look for assoc tsk up */
   thp->th_fj = TRUE;
   last_thp = thp;
  }
 __cur_thd->thnxtstp = (struct st_t *) nxtstp;
}

static struct thread_t *asl_loc_sched_fj_subthread(struct st_t *stp)
{
 struct thread_t *thp;
 struct tev_t *tevp;

 /* allocate a new thread */
 thp = __alloc_thrd();
 thp->thenbl_sfnam_ind = __sfnam_ind;
 thp->thenbl_slin_cnt = __slin_cnt;

 /* set the one fj statement (or list) as next stmt of subthread */
 thp->thnxtstp = stp;
 
 /* allocate an event for this fork-join component statement */
 /* at end of current time slot */
//AIV FIXME - compiler still uses this as a wrapper so need to use enterp adr
 tevp = asl_loc_get_new_thread_event();

 /* link thread back to event */
 thp->thdtevp = tevp;
 tevp->tu.tethrd = thp;

 /* this must go on front because interactive statement must complete */
 /* AIV 09/05/07 - compiler must do special case handling for free events */
 __asl_trigger_ectrl(tevp);
 return(thp);
}

/* 
 * asm to exec system task - just wrapper to normal exec stsk routine
 * op1 is addr of task enable stmt 
 * LOOKATME - except for errors now setting line cnt to base block begin?
 * so need to save restore here
 *
 * SJM 07/22/02 - ??? maybe need context save here since this can 
 * call PLI that can then reenter interpreter
 * SJM 03/10/04 - for now just ignore PLI
 * AIV 10/20/08 - no reason to return stmt value
 */
extern void __asl_exec_stsk(struct st_t *stp)
{
 struct tskcall_t *tkcp;
 struct expr_t *tkxp;
 int32 sav_slin_cnt, sav_sfnam_ind;

 tkcp = &(stp->st.stkc);
 tkxp = tkcp->tsksyx;

 sav_slin_cnt = __slin_cnt;
 sav_sfnam_ind = __sfnam_ind;
 __slin_cnt = stp->stlin_cnt;
 __sfnam_ind = stp->stfnam_ind;

 __exec_stsk(stp, tkxp->lu.sy, tkcp);
  
 __slin_cnt = sav_slin_cnt;
 __sfnam_ind = sav_sfnam_ind;
}

/*
 * create and copy automatic local storage idp area
 */
extern t_midat *__asl_new_auto_idp_area(t_midat *idp)
{
 t_midat *new_idp;
 struct mod_t *mdp;
 size_t nbytes;

 /* allocate and copy idp area for one new instance */
 mdp = (struct mod_t *) idp[MD_MDP];
 nbytes = mdp->mod_idata_siz*WRDBYTES;
 new_idp = (t_midat *) __my_malloc(nbytes);
 memcpy(new_idp, idp, nbytes);
 return(new_idp);
}

/*
 * copy tmp idp area back and free it
 * this routine is only used for functions since automatic tasks are handled
 * with thread wrappers
 */
extern void __asl_cp_auto_idp_area_func(t_midat *dst_idp, t_midat *src_idp)
{
 struct mod_t *mdp;
 size_t nbytes;

 mdp = (struct mod_t *) src_idp[MD_MDP];
 /* only copy lower than the tasks idp area - for the static var values */
 nbytes = mdp->task_start_ofs*WRDBYTES;
 memcpy(dst_idp, src_idp, nbytes);
 __my_free(src_idp, mdp->mod_idata_siz);
}

/*
 * wrapper to execute a $display call
 */
extern void __asl_exec_display(struct st_t *stp)
{
 struct tskcall_t *tkcp;

 tkcp = &(stp->st.stkc);
 __do_disp(tkcp->targs, BDEC);
 __cvsim_msg("\n");
}

/*
 * return T (1) if a register is either forced or assigned
 *
 * notice register force/assign can't be constant bit select
 * but wire force can be
 */
extern int32 __asl_reg_qcaf_inhibit(struct net_t *np)
{
 int32 inum;

 inum = get_inum_();
 /* AIV 02/02/12 - changed T/F order */
 if (np->nu2.qcval[2*inum].qc_active
  || np->nu2.qcval[2*inum + 1].qc_active) return(FALSE);
 return(TRUE);
}

/*
 * return T (1) if a scalar wire is forced or assigned
 */
extern int32 __asl_scalar_wire_inhibit(struct net_t *np)
{
 int32 inum;

 inum = get_inum_();
 /* AIV - note truth value swapped because using testl */
 if (np->nu2.qcval[inum].qc_active) return(FALSE);
 return(TRUE);
}

/*
 * return T(1) if a constant bit bit is forced
 */
extern int32 __asl_bsel_wirfrc_inhibit(struct net_t *np, int32 biti)
{
 int32 inum;

 inum = get_inum_();
 /* AIV - note truth value swapped because using testl */
 if (np->nu2.qcval[np->nwid*inum + biti].qc_active) return(FALSE);
 return(TRUE);
}

/*
 * correct stren vector wire forced new rhs
 * returns T if all bits forced - know rhs width exactly same as np size
 *
 * this is both an eval insn routine and an in place routine so must
 * gen a new tmp for sbp
 */
extern int32 __asl_stren_correct_frc(byte *sbp, struct net_t *np)
{
 int32 bi, ibase, nd_assign, inum;
 byte *sbp2;
  
 inum = get_inum_();
 ibase = inum*np->nwid;
 sbp2 = (byte *) &(__idp[np->nva_ofs]);
 /* trick is to replace forced bits so new assign is same as forced val */
 for (nd_assign = FALSE, bi = 0; bi < np->nwid; bi++)
  {
   /* some bits not forced - so need assign */
   if (np->nu2.qcval[ibase + bi].qc_active) sbp[bi] = sbp2[bi];
   else nd_assign = TRUE;
  }
 return(nd_assign);
}

/*
 * correct a/b sr vec wire forced new rhs
 * returns T if all bits forced - know rhs width exactly same as np size
 *
 * this is both an eval insn routine and an in place routine so must
 * gen a new tmp for sbp
 */
extern int32 __asl_correct_frc(word32 *ap, struct net_t *np)
{
 int32 wi;
 word32 *bp;
 int32 wlen;
 struct xstk_t *xsp, *xsp2;
 
 push_xstk_(xsp, np->nwid);
 __bld_forcedbits_mask(xsp->ap, np);
 zero_allbits_(xsp->bp, np->nwid); 
 
 /* if all bits forced nothing to do */
 if (__vval_is1(xsp->ap, np->nwid)) { __pop_xstk(); return(FALSE); }
 /* if no bits forced, just assign ap */
 if (vval_is0_(xsp->ap, np->nwid)) { __pop_xstk(); return(TRUE); }

 /* only load wire if some bits forced */
 push_xstk_(xsp2, np->nwid);
 __ld_wire_val_xstk(xsp2, np);

 /* take new value and merge in some forced bits */
 wlen = wlen_(np->nwid);    
 bp = &(ap[wlen]);
 for (wi = 0; wi < wlen; wi++)
  {
   /* remove forced bits from new value */
   ap[wi] &= ~(xsp->ap[wi]);
   bp[wi] &= ~(xsp->ap[wi]);
   /* remove non forced bits from new wire */
   xsp2->ap[wi] &= (xsp->ap[wi]);
   xsp2->bp[wi] &= (xsp->ap[wi]);
   /* combine old maybe forced bits into new value - so will be same */  
   ap[wi] |= (xsp2->ap[wi]);
   /* AIV 02/02/12 - this was always wrong - should be xsp2->bp here */
   /* was oring in a part */
   bp[wi] |= (xsp2->bp[wi]);
  }
 __pop_xstk();
 __pop_xstk();
 return(TRUE);
}

/*
 * correct non stren wire part select wire forced new rhs
 * returns T if all bits in psel range forced 
 *
 * this is both an eval insn routine and an in place routine so must
 * gen a new tmp for sbp
 */
extern int32 __asl_psel_correct_frc(word32 *ap, struct net_t *np, int32 ri1,
 int32 ri2)
{
 int32 wi, wlen, pswid;
 word32 *bp;
 struct xstk_t *xsp, *xsp2;

 pswid = ri1 - ri2 + 1; 
 wlen = wlen_(np->nwid);
 bp = &(ap[2*wlen]);

 push_xstk_(xsp, pswid);
 push_xstk_(xsp2, np->nwid);
 __bld_forcedbits_mask(xsp2->ap, np);
 
 /* xsp has part select range forced bits */
 __rhspsel(xsp->ap, xsp2->ap, ri2, pswid);
 __pop_xstk();

 /* if all bits forced nothing to do */
 if (__vval_is1(xsp->ap, pswid)) { __pop_xstk(); return(FALSE); }
 /* if no bits in range forced, just do lhs part select */
 if (vval_is0_(xsp->ap, pswid)) { __pop_xstk(); return(TRUE); }

 push_xstk_(xsp2, pswid);
 /* xsp2 has value of old wire part selected range */
 __ld_psel(xsp2->ap, xsp2->bp, np, ri1, ri2); 
 wlen = wlen_(pswid);

 /* this changes new value so lhs part select will set right value */
 for (wi = 0; wi < wlen; wi++) 
  {
   /* remove forced bits from new value */
   ap[wi] &= ~(xsp->ap[wi]);   
   bp[wi] &= ~(xsp->ap[wi]);
   /* remove non forced bits from old (current value) */
   xsp2->ap[wi] &= xsp->ap[wi];
   xsp2->bp[wi] &= xsp->ap[wi];
   /* or old value forced into new value */
   ap[wi] |= xsp2->ap[wi]; 
   /* AIV 02/02/12 - this was always wrong - should be xsp2->bp here */
   /* was oring in a part */
   bp[wi] |= (xsp2->bp[wi]);
  }
 __pop_xstk();
 __pop_xstk();
 return(TRUE);
}

/*
 * correct stren wire part select wire forced new rhs
 * returns T if all bits in psel range forced 
 *
 * this is both an eval insn routine and an in place routine so must
 * gen a new tmp for sbp
 */
extern int32 __asl_stren_psel_correct_frc(byte *sbp, struct net_t *np,
 int32 ri1, int32 ri2)
{
 int32 bi, bi2;
 int32 pswid, nd_assign, ibase, inum;
 byte *sbp2;

 pswid = ri1 - ri2 + 1; 
 sbp2 = (byte *) &(__idp[np->nva_ofs]);

 /* trick is to replace forced bits so new assign is same as forced val */
 /* if all bits forced, do not need assign */
 inum = get_inum_();
 ibase = inum*np->nwid;
 for (nd_assign = FALSE, bi = ri2, bi2 = 0; bi2 < pswid; bi++, bi2++)
  {
   /* some bits not forced - so need assign */
   if (np->nu2.qcval[ibase + bi].qc_active) sbp[bi] = sbp2[bi];
   else nd_assign = TRUE;
  }
 return(nd_assign);
}

/************************************************************************/
/*************** ASL ROUTINE FOR FORCE HANDLING   ***********************/
/************************************************************************/
extern void __asl_exec_qc_wireforce(struct st_t *stp, int32 bi, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct expr_t *lhsx;

 lhsx = stp->st.sqca->qclhsx;
 asl_loc_do_qc_wireforce(stp, lhsx, bi, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_tran_wireforce(struct st_t *stp, int32 bi, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct expr_t *lhsx;

 lhsx = stp->st.sqca->qclhsx;
 asl_loc_do_qc_tran_wireforce(stp, lhsx, bi, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_wireforce_concat(struct st_t *stp, 
 struct expr_t *lhsx, int32 bi, struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 asl_loc_do_qc_wireforce(stp, lhsx, bi, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_tran_wireforce_concat(struct st_t *stp, 
 struct expr_t *lhsx, int32 bi, struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 asl_loc_do_qc_tran_wireforce(stp, lhsx, bi, nchglp, nchg_idp_ofs);
}

static void asl_loc_do_qc_wireforce(struct st_t *qcfstp, struct expr_t *lhsx,
 int32 rhsbi, struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 int32 bi, ibase;
 int32 biti, bitj, rhsbi2, lhsbi2, ndx, inum;
 struct net_t *np;
 t_midat *xmr_idp;
 struct dceauxlstlst_t *dcllp;
 struct dceauxlst_t *qcdcep;
 struct mod_t *mdp;
 decl_idp_locals_;

 /* step 1: get the wire range */
 /* for psel or vector, range is biti down to bitj - for scalar 0,0 */
 /* this computes any xmr new itp but does not push it */
 save_idp = NULL;
 xmr_idp = __get_qc_wirrng(lhsx, &np, &biti, &bitj); 

 /* SJM 07/22/02 - need to access dce list form stmt inum not lhs if xmr */
 /* access dce list from stmt not lhs itree context */
 inum = get_inum_();
 dcllp = qcfstp->st.sqca->rhs_qcdlstlst;
 qcdcep = dcllp->dcelsttab[inum];
 /* wire force must run in lhs itree context */ 
 if (xmr_idp != NULL)
  {
   set_save_idp_(xmr_idp); 
   /* AIV 07/13/07 - need to reload the inum value in case of xmr */
   inum = get_inum_();
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }
 /* ibase is lhs xmr qcval base */ 
 ibase = inum*np->nwid;
 if (!np->n_isavec)
  {
   /* this pops itstk if needed */
   /* AIV INUM FIXME - maybe better way to do this than passing save values */
   asl_loc_do_1bit_wireforce(qcfstp, np, ibase, -1, rhsbi, xmr_idp, qcdcep, 
     save_idp, nchglp);
   ndx = -1;    
   goto done;
  }

 /* force every bit in range using same rhs dce list for each */
 for (bi = bitj; bi <= biti; bi++)
  {
   /* rhsbi is low bit of possible lhs concat caused rhs select */
   if (rhsbi == -1) rhsbi2 = bi - bitj;
   else rhsbi2 = rhsbi + (bi - bitj);
   lhsbi2 = bi;

   asl_loc_do_1bit_wireforce(qcfstp, np, ibase, lhsbi2, rhsbi2, xmr_idp, 
    qcdcep, save_idp, nchglp);
  }

 if (biti != bitj) ndx = -1; else ndx = biti;

done:
 /* these need to run in itree context of possible lhs xmr */
 /* notice can have both many wire specific and many all cbs */
 if (__num_vpi_force_cbs > 0) __find_call_force_cbs(np, ndx);
 if (__vpi_force_cb_always) __cb_all_rfs(np, ndx, TRUE);

 /* on return, itree context of force stmt needed */ 
 if (xmr_idp != NULL)
  {
   restore_idp_();
  }
}

static void asl_loc_do_qc_tran_wireforce(struct st_t *qcfstp, 
 struct expr_t *lhsx, int32 rhsbi, struct nchglst_t *nchglp_base, 
 size_t nchg_idp_ofs)
{
 int32 biti, bitj;
 struct net_t *np;
 t_midat *xmr_idp;
 struct mod_t *mdp;
 decl_idp_locals_;
 
 /* step 1: get the wire range */
 /* for psel or vector, range is biti down to bitj - for scalar 0,0 */
 /* this computes any xmr new itp but does not push it */
 xmr_idp = __get_qc_wirrng(lhsx, &np, &biti, &bitj); 

 save_idp = NULL;
 if (xmr_idp != NULL)
  {
   /* AIV 02/01/12 - need to set the xmr_idp here and restore below */
   set_save_idp_(xmr_idp); 
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (nchglp_base != NULL && mdp->flatinum > 1)
    {
     nchglp_base = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }

 /* this pushes and pops lhs xmr itree context itp if needed */ 
 /* routine also handles any PLI force callbacks */
 /* SJM 02/26/02 - no dces so new pre-build qcaf dces does not chg this */
 asl_loc_qc_tran_wireforce(np, biti, bitj, rhsbi, xmr_idp, qcfstp, 
  nchglp_base);

 /* AIV 02/01/12 - this also may need to handle VPI cbs here */
 /* notice can have both many wire specific and many all cbs */
 /* call backs also need to match itree loc for lhs xmr */
 if (__num_vpi_force_cbs > 0) __find_call_force_cbs(np, biti);
 if (__vpi_force_cb_always) __cb_all_rfs(np, biti, TRUE);

 /* on return, itree context of force stmt needed */ 
 if (xmr_idp != NULL)
  {
   restore_idp_();
  }
}

static void asl_loc_qc_tran_wireforce(struct net_t *np, int32 biti, int32 bitj,
 int32 rhsbi, t_midat *idp, struct st_t *qcfstp, struct nchglst_t *nchglp_base)
{
 int32 bi;
 word32 aval, bval;
 struct xstk_t *xsp;
 struct expr_t *rhsx;
 struct nchglst_t *nchglp;
 int32 ninsts;
 struct mod_t *mdp;

 rhsx = qcfstp->st.sqca->qcrhsx; 
 /* this converts rhs if needed and makes lhs right width */
 /* must eval rhs in itree context of rhs (i.e. statement) */
 xsp = __eval_assign_rhsexpr(rhsx, qcfstp->st.sqca->qclhsx);
 /* do rhs bsel here so pass a/b words with low bit asign bit */ 
 if (rhsbi == -1) rhsbi = 0;

 if (!np->n_isavec)
  {
   aval = rhsbsel_(xsp->ap, rhsbi);
   bval = rhsbsel_(xsp->bp, rhsbi);
   /* SJM 03/15/01 - now just forcing the one wire - caller re-evals channel */
   /* SJM 04/15/01 - must pass any xmr itree context */
   asl_loc_do_qc_wire_intran_force(np, -1, aval, bval, idp, nchglp_base);
  }
 else
  {
   nchglp = nchglp_base;
   mdp = get_inst_mod_();
   ninsts = mdp->flatinum;
   for (bi = biti; bi >= bitj; bi--)
    {
     aval = rhsbsel_(xsp->ap, rhsbi + (bi - bitj));
     bval = rhsbsel_(xsp->bp, rhsbi + (bi - bitj));
     /* SJM 04/15/01 - must pass any xmr itree context */
     asl_loc_do_qc_wire_intran_force(np, bi, aval, bval, idp, nchglp);
//AIV PTR FIXME - don't think this is portable or good
//take the original netchg address and get the bi's from theis address
     /* AIV 02/03/12 - this was wrong - nchglp is already is from idp offs */
     /* added misc_terr check as well - this code is still bad and it */
     /* put think this now works */
     if (nchglp != NULL)
      {
//AIV PUTMEBACK - DEBUG
//#ifdef __CVC_DEBUG__
       if (bi != nchglp->bi1) __misc_terr(__FILE__, __LINE__);
//#endif
       nchglp = (struct nchglst_t *) ((word32) nchglp + 
         ((word32) sizeof(struct nchglst_t) * (ninsts)));
      }
    }
  }
 __pop_xstk();
}

/*
 * do force for one net-bit or scalar in tran channel 
 */
static void asl_loc_do_qc_wire_intran_force(struct net_t *np, int32 biti, 
 word32 aval, word32 bval, t_midat *lhs_idp, struct nchglst_t *nchglp)
{
 int32 ibase, inum;
 decl_idp_locals_;

 save_idp = NULL;
 if (lhs_idp != NULL) 
  { 
   set_save_idp_(lhs_idp); 
  }

 /* this must run in itree context of lhs (maybe an xmr) */
 inum = get_inum_();
 ibase = inum*np->nwid;
 if (!np->n_isavec)
  {
   asl_loc_bit1_vpi_or_tran_wireforce(np, &aval, &bval, ibase, 0, 0,
    nchglp);
  }
 else
  {
   /* because right bit value already selected into a/b low bit, rhsbi is 0 */  
   asl_loc_bit1_vpi_or_tran_wireforce(np, &aval, &bval, ibase, biti, 0,
    nchglp);
  }

 /* notice can have both many wire specific and many all cbs */
 /* call backs also need to match itree loc for lhs xmr */
 if (__num_vpi_force_cbs > 0) __find_call_force_cbs(np, biti);
 if (__vpi_force_cb_always) __cb_all_rfs(np, biti, TRUE);
 
 if (lhs_idp != NULL) 
  {
   restore_idp_();
  }
}

extern void asl_loc_bit1_vpi_or_tran_wireforce(struct net_t *np, 
 word32 *ap, word32 *bp, int32 ibase, int32 lhsbi, int32 rhsbi, 
 struct nchglst_t *nchglp)
{
 struct qcval_t *frc_qcp;
 struct xstk_t *xsp, *xsp2;
 word32 *rap;
 word32 uwrd;
 int32 bi, lhs_changed;
 byte *sbp, *netsbp;

 /* even if currently forced indicate force active */
 bi = (lhsbi == -1) ? 0 : lhsbi; 
 frc_qcp = &(np->nu2.qcval[ibase + bi]);
 frc_qcp->qc_active = TRUE;

 /* get the 1 bit onto stack */
 push_xstk_(xsp, 1);
 if (rhsbi != 0) 
  {
   xsp->ap[0] = rhsbsel_(ap, rhsbi);
   xsp->bp[0] = rhsbsel_(bp, rhsbi);
  }
 else { xsp->ap[0] = ap[0] & 1L; xsp->bp[0] = bp[0] & 1L; }
 /* AIV 08/23/10 - need to convert x/z prior to assign */
 if (np->n_2state)
  {
   __cnvt_xzs_to_2state(xsp->ap, xsp->bp, xsp->xslen);
  }

 /* quasi-continuous assign to strength wire always strong */
 if (np->n_stren)
  {
   push_xstk_(xsp2, WRDBYTES);
   sbp = (byte *) xsp2->ap;
   __st_standval(sbp, xsp, ST_STRVAL);
   netsbp = (byte *) &(__idp[np->nva_ofs]);
   if (np->n_isavec) 
    {
     /* SR_SVEC bsel */
     if (nchglp != NULL)
      {
       if (netsbp[lhsbi] != sbp[0])
        { 
         netsbp[lhsbi] = sbp[0]; 
         asl_loc_record_nchg(np, nchglp);
        }
      }
     else netsbp[lhsbi] = sbp[0]; 
    }
   else 
    {
     /* SR_SSCAL */
     if (nchglp != NULL)
      {
       if (*netsbp != *sbp)
        {
         *netsbp = *sbp;
         asl_loc_record_nchg(np, nchglp);
        }
      }
     else *netsbp = *sbp;
    }
   __pop_xstk();
  }
 else 
  {
   if (np->n_isavec)
    {
     /* SR_VEC bsel */
     if (nchglp != NULL)
      {
       rap = &(__idp[np->nva_ofs]);
       if (np->n_2state)
        {
         lhs_changed = asl_loc_chg_vec_lhsbsel_2state(rap, lhsbi, xsp->ap[0]);
        }
       else
        {
         lhs_changed = asl_loc_chg_vec_lhsbsel(rap, lhsbi, xsp->ap[0], 
          xsp->bp[0], np->nwid);
        }
       if (lhs_changed) asl_loc_record_nchg(np, nchglp);
      }
     else __st_bit(np, lhsbi, xsp->ap[0], xsp->bp[0]);
    }
   else 
    {
     /* SR_SCAL */
     uwrd = xsp->ap[0] | (xsp->bp[0] << 1);
     if (nchglp != NULL)
      {
       if (__idp[np->nva_ofs] != uwrd)
        {
         __idp[np->nva_ofs] = uwrd;
         asl_loc_record_nchg(np, nchglp);
        }
      }
     else __idp[np->nva_ofs] = uwrd;
    }
  }
 __pop_xstk();
}

static void asl_loc_do_1bit_wireforce(struct st_t *qcstp, struct net_t *np,
 int32 ibase, int32 lhsbi, int32 rhsbi, t_midat *xmr_idp,
 struct dceauxlst_t *qcdcep, t_midat *save_idp, struct nchglst_t *nchglp)
{
 struct xstk_t *xsp;
 struct expr_t *rhsx;
 int32 biti;
 struct qcval_t *frc_qcp;

 if (lhsbi == -1) biti = 0; else biti = lhsbi;

 /* for reg var 2 records always allocated, first is force and 2nd assign */
 frc_qcp = &(np->nu2.qcval[ibase + biti]);
 /* forcing to different expr */
 if (frc_qcp->qc_active)
  {
   if (frc_qcp->qcdcep != NULL) __dcelst_off(frc_qcp->qcdcep);
   frc_qcp->qcdcep = NULL;
  }

 /* setup the new force */
 frc_qcp->qcstp = qcstp; 
 /* rhsbi is low bit of rhs range in case lhs concatenate */ 
 frc_qcp->qcrhsbi = rhsbi;
 frc_qcp->qclhsbi = lhsbi;
 /* store and build dces in lhs ref. itree location */ 
 frc_qcp->lhsidp = __idp;
 frc_qcp->qcdcep = qcdcep;
 
 /* AIV INUM FIXME - maybe better way to do this */
 if (xmr_idp != NULL)
  {
   restore_idp_();
  }

 /* start force by storing rhs of force - dces will cause dce chges */
 rhsx = frc_qcp->qcstp->st.sqca->qcrhsx; 
 xsp = __eval_assign_rhsexpr(rhsx, frc_qcp->qcstp->st.sqca->qclhsx);
 asl_loc_do_qc2_wirestore(np, frc_qcp, xsp, nchglp);
 __pop_xstk();
 frc_qcp->qc_active = TRUE;

 /* turn on dces after doing store */
 if (frc_qcp->qcdcep != NULL) __dcelst_on(frc_qcp->qcdcep);

 if (xmr_idp != NULL)
  {
   set_idp_(xmr_idp); 
  }
}

static void asl_loc_do_qc_store(struct net_t *np, struct qcval_t *qcvalp,
 struct expr_t *lhsx, struct expr_t *rhsx, struct nchglst_t *nchglp)
{ 
 struct xstk_t *xsp;

 /* this converts rhs if needed and makes lhs right width */
 xsp = __eval_assign_rhsexpr(rhsx, lhsx);
 asl_loc_do_qc2_regstore(np, qcvalp, xsp, nchglp);
 __pop_xstk();
}

static void asl_loc_do_qc2_regstore(struct net_t *np, struct qcval_t *qcvalp,
 struct xstk_t *xsp, struct nchglst_t *nchglp)
{
 word32 uwrd;
 word32 *dwp;
 int32 nd_xpop;
 struct xstk_t *xsp2;
 decl_idp_locals_;

 /* know lhs always entire reg but rhs may need select out */ 
 /* rhsbi field is low bit of section from lhs concatenate if needed */
 if (qcvalp->qcrhsbi != -1)
  {
   push_xstk_(xsp2, np->nwid);
   __rhspsel(xsp2->ap, xsp->ap, qcvalp->qcrhsbi, np->nwid);
   __rhspsel(xsp2->bp, xsp->bp, qcvalp->qcrhsbi, np->nwid);
   nd_xpop = TRUE;
  }
 else { xsp2 = xsp; nd_xpop = FALSE; }

 save_idp = NULL;
 if (qcvalp->lhsidp != NULL)
  { 
   set_save_idp_(qcvalp->lhsidp); 
  }

 if (np->srep == SR_SCAL)
  {
   uwrd = xsp2->ap[0] | (xsp2->bp[0] << 1);
   if (nchglp != NULL)
    {
     if (__idp[np->nva_ofs] != uwrd)
      {
       __idp[np->nva_ofs] = uwrd;
       asl_loc_record_nchg(np, nchglp);
      }
    }
   else __idp[np->nva_ofs] = uwrd;
  }
 else if (np->srep == SR_VEC) 
  {
   /* SR_VEC bsel */
   if (nchglp != NULL)
    {
     dwp = &(__idp[np->nva_ofs]);
     if (asl_loc_chg_st_vecval(dwp, np->nwid, xsp2->ap, xsp2->bp))
      {
       asl_loc_record_nchg(np, nchglp);
      }
    }
   else __st_val(np, xsp2->ap, xsp2->bp, xsp2->xslen); 
  }
 else if (np->srep == SR_BIT2S) 
  {
   /* SR_VEC bsel */
   if (nchglp != NULL)
    {
//AIV 2STATE - need conversion of x/z here??
     dwp = &(__idp[np->nva_ofs]);
     if (asl_loc_chg_st_vecval_2state(dwp, np->nwid, xsp2->ap))
      {
       asl_loc_record_nchg(np, nchglp);
      }
    }
   else __st_val(np, xsp2->ap, xsp2->bp, xsp2->xslen); 
  }
 else if (np->srep == SR_SCAL2S)
  {
   uwrd = xsp2->ap[0];
   if (nchglp != NULL)
    {
     if (__idp[np->nva_ofs] != uwrd)
      {
       __idp[np->nva_ofs] = uwrd;
       asl_loc_record_nchg(np, nchglp);
      }
    }
   else __idp[np->nva_ofs] = uwrd;
  }
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 else __misc_terr(__FILE__, __LINE__);
#endif

 if (nd_xpop) __pop_xstk();
 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

static int32 asl_loc_chg_st_vecval(word32 *dwp, int32 blen, word32 *ap, 
 word32 *bp)
{
 int32 wlen, lhs_changed;
 word32 *dwp2;

 if (blen <= WBITS)
  { 
   if (dwp[0] != ap[0])
    {
     dwp[0] = ap[0];
     /* AIV 09/19/06 - if a part is not the same assign bpart regardless */
     /* this is better than doing another compare */
     dwp[1] = bp[0];
     return(TRUE);
    }
   /* AIV 09/19/06 - was assuming contiguous words (using ap[1] for bpart) */
   /* which isn't always true local words av, bv can be passed */
   if (dwp[1] != bp[0])
    {
     dwp[1] = bp[0];
     return(TRUE);
    }
   return(TRUE);
  }
 wlen = wlen_(blen);
 lhs_changed = FALSE;
 if (cmp_wvval_(dwp, ap, wlen) != 0)
  { cp_walign_(dwp, ap, blen); lhs_changed = TRUE; }
 dwp2 = &(dwp[wlen]); 
 if (cmp_wvval_(dwp2, bp, wlen) != 0)
  { cp_walign_(dwp2, bp, blen); lhs_changed = TRUE; }
 return(lhs_changed);
}

/*
 * 2-state version
 */
static int32 asl_loc_chg_st_vecval_2state(word32 *dwp, int32 blen, word32 *ap)
{
 int32 wlen, lhs_changed;

 if (blen <= WBITS)
  { 
   if (dwp[0] != ap[0])
    {
     dwp[0] = ap[0];
     return(TRUE);
    }
   return(TRUE);
  }
 wlen = wlen_(blen);
 lhs_changed = FALSE;
 if (cmp_wvval_(dwp, ap, wlen) != 0)
  { cp_walign_(dwp, ap, blen); lhs_changed = TRUE; }
 return(lhs_changed);
}

/*
 * store qc value with rhs in xsp for wire either scalar or 1 bit select only
 */
static void asl_loc_do_qc2_wirestore(struct net_t *np, struct qcval_t *qcvalp,
 struct xstk_t *xsp, struct nchglst_t *nchglp)
{
 int32 ind, nd_xpop, lhs_changed, biti;
 word32 uwrd;
 word32 *rap;
 byte *sbp, *netsbp;
 struct xstk_t *xsp2, *xsp3;
 decl_idp_locals_;

 /* AIV 08/23/10 - need to convert x/z prior to assign */
 if (np->n_2state)
  {
   __cnvt_xzs_to_2state(xsp->ap, xsp->bp, xsp->xslen);
  }
 /* 2 cases that require selecting a bit from evaled rhs xsp */
 /* rhs bi or lhs bi not -1 because lhs concatenate */
 if (qcvalp->qcrhsbi != -1 || qcvalp->qclhsbi != -1)
  {
   ind = ((qcvalp->qcrhsbi == -1) ? 0 : qcvalp->qcrhsbi);
   push_xstk_(xsp2, 1);
   xsp2->ap[0] = rhsbsel_(xsp->ap, ind);
   xsp2->bp[0] = rhsbsel_(xsp->bp, ind);
   nd_xpop = TRUE;
  }
 else { xsp2 = xsp; nd_xpop = FALSE; }

 save_idp = NULL;
 if (qcvalp->lhsidp != NULL)
  { 
   set_save_idp_(qcvalp->lhsidp); 
  }

 /* quasi-continuous assign to strength wire always strong */
 if (np->n_stren)
  {
   push_xstk_(xsp3, WRDBYTES);
   sbp = (byte *) xsp3->ap;
   /* LOOKATME could simpify since know only 1 bit */
   __st_standval(sbp, xsp2, ST_STRVAL);
   /* notice if vector for wire know lhs bi always non zero */

   /* SJM 11/14/00 slightly better to just pass a part as sbp */
   /* notice if vector for wire know lhs bi always non zero */
   netsbp = (byte *) &(__idp[np->nva_ofs]);
   if (np->n_isavec) 
    {
     /* SR_SVEC bsel */
     biti = qcvalp->qclhsbi;
     if (nchglp != NULL)
      {
       if (netsbp[biti] != sbp[0])
        { 
         netsbp[biti] = sbp[0]; 
         asl_loc_record_nchg(np, nchglp);
        }
      }
     else netsbp[biti] = sbp[0]; 
    }
   else 
    {
     /* SR_SSCAL */
     if (nchglp != NULL)
      {
       if (*netsbp != *sbp)
        {
         *netsbp = *sbp;
         asl_loc_record_nchg(np, nchglp);
        }
      }
     else *netsbp = *sbp;
    }
   __pop_xstk();
  }
 else 
  {
   if (np->n_isavec)
    {
     /* SR_VEC bsel */
     if (nchglp != NULL)
      {
       rap = &(__idp[np->nva_ofs]);
       if (np->n_2state)
        {
         lhs_changed = asl_loc_chg_vec_lhsbsel_2state(rap, qcvalp->qclhsbi, 
           xsp2->ap[0]);
        }
       else
        {
         lhs_changed = asl_loc_chg_vec_lhsbsel(rap, qcvalp->qclhsbi, 
           xsp2->ap[0], xsp2->bp[0], np->nwid);
        }
       if (lhs_changed) asl_loc_record_nchg(np, nchglp);
      }
     else __st_bit(np, qcvalp->qclhsbi, xsp2->ap[0], xsp2->bp[0]);
    }
   else 
    {
     /* SR_SCAL */
     uwrd = xsp2->ap[0] | (xsp2->bp[0] << 1);
     if (nchglp != NULL)
      {
       if (__idp[np->nva_ofs] != uwrd)
        {
         __idp[np->nva_ofs] = uwrd;
         asl_loc_record_nchg(np, nchglp);
        }
      }
     else __idp[np->nva_ofs] = uwrd;
    }
  }
 if (nd_xpop) __pop_xstk();
 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

extern void __asl_exec_qc_wirerelease(struct st_t *stp, struct nchglst_t *nchglp, 
 size_t nchg_idp_ofs)
{
 struct expr_t *lhsx;

 lhsx = stp->st.sqcdea.qcdalhs;
 asl_loc_do_qc_wirerelease(lhsx, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_tran_wirerelease(struct st_t *stp, 
  struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct expr_t *lhsx;

 lhsx = stp->st.sqcdea.qcdalhs;
 /* only possibilities are concat and ID */
 asl_loc_do_qc_tran_wirerelease(lhsx, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_wirerelease_concat(struct expr_t *lhsx,
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 /* only possibilities are concat and ID */
 asl_loc_do_qc_wirerelease(lhsx, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_tran_wirerelease_concat(struct expr_t *lhsx,
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 /* only possibilities are concat and ID */
 asl_loc_do_qc_tran_wirerelease(lhsx, nchglp, nchg_idp_ofs);
}

static void asl_loc_do_qc_wirerelease(struct expr_t *lhsx, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 int32 bi, ibase;
 int32 biti, bitj, all_forced, inum, ndx;
 struct net_t *np;
 t_midat *xmr_idp;
 struct qcval_t *frc_qcp;
 struct mod_t *mdp;
 char s1[RECLEN];
 decl_idp_locals_;
 
 /* step 1: get the wire range */
 /* for psel or vector, range is biti down to bitj - for scalar 0,0 */
 save_idp = NULL;
 xmr_idp = __get_qc_wirrng(lhsx, &np, &biti, &bitj); 

 /* SJM 07/23/02 - this needs lhs expr context */
 if (xmr_idp != NULL) 
  {
   set_save_idp_(xmr_idp); 
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }

 inum = get_inum_();
 ibase = inum*np->nwid;
 for (bi = 0; bi < np->nwid; bi++)
  {
   frc_qcp = &(np->nu2.qcval[ibase + bi]);
   if (frc_qcp->qc_active) goto some_bit_forced;
  }
 strcpy(s1, " - no bits forced");
 __sgfinform(465,
  "attempted release of %s in instance %s failed%s",
  __msgexpr_tostr(__xs2, lhsx), __msg2_cur_blditree(__xs), s1);
 /* SJM 04/15/01 - if no bits forced, do not try to exec call backs */
 if (xmr_idp != NULL) 
  {
   restore_idp_();
  }
 return;

some_bit_forced:
 /* know some forced or will not get here - release all in range */
 /* notice wire force is per bit but no second qc assigns for wires */  
 all_forced = TRUE;
 for (bi = biti; bi >= bitj; bi--)
  {
   frc_qcp = &(np->nu2.qcval[ibase + bi]);
   if (!frc_qcp->qc_active) { all_forced = FALSE; continue; }
   frc_qcp->qc_active = FALSE;

   /* turn off dces after doing store if rhs non constant */ 
   if (frc_qcp->qcdcep != NULL) __dcelst_off(frc_qcp->qcdcep);
   frc_qcp->qcdcep = NULL;
  }

 /* assign expected value now that force removed by evaling all drivers */
 /* must re-eval entire wire since other drivers may overlap forced range */
 /* notice this must be called from target of xmr and/or col. to */
 /* it handles moving back to references */
 asl_loc_assign_1mdrwire(np, nchglp);

 if (!all_forced)
  {
   strcpy(s1, " - some bits forced");
   __sgfinform(465, "attempted release of %s in instance %s failed%s",
    __msgexpr_tostr(__xs2, lhsx), __msg2_cur_blditree(__xs), s1);
   if (xmr_idp != NULL) 
    {
     set_save_idp_(xmr_idp); 
    }

   /* here still need to try to exec PLI callbacks */
  } 

 /* must exec call backs in possible lhs xmr itree context */ 
 /* FIXME - why not calling for every bit in range - only 1 bit possible? */
 if (biti != bitj) ndx = -1; else ndx = biti;
 /* notice can have both many wire specific and many all cbs */
 if (__num_vpi_rel_cbs > 0) __find_call_rel_cbs(np, ndx);
 if (__vpi_rel_cb_always) __cb_all_rfs(np, ndx, FALSE);

 if (xmr_idp != NULL)
  {
   restore_idp_();
  }
}

static void asl_loc_do_qc_tran_wirerelease(struct expr_t *lhsx, 
 struct nchglst_t *nchglp_base, size_t nchg_idp_ofs)
{
 int32 biti, bitj;
 struct net_t *np;
 t_midat *xmr_idp;
 struct mod_t *mdp;
 decl_idp_locals_;
 
 /* step 1: get the wire range */
 /* for psel or vector, range is biti down to bitj - for scalar 0,0 */
 xmr_idp = __get_qc_wirrng(lhsx, &np, &biti, &bitj); 
 /* AIV 02/02/12 - may need to push XMR idp here */
 save_idp = NULL;
 if (xmr_idp != NULL) 
  {
   set_save_idp_(xmr_idp); 
  }

 if (nchglp_base != NULL)
  {
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (mdp->flatinum > 1)
    {
     nchglp_base = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }

 asl_loc_qc_tran_wirerelease(np, biti, bitj, xmr_idp, lhsx, nchglp_base);

 if (xmr_idp != NULL)
  {
   restore_idp_();
  }
}

static void asl_loc_qc_tran_wirerelease(struct net_t *np, int32 biti, 
 int32 bitj, t_midat *idp, struct expr_t *lhsx, struct nchglst_t *nchglp_base)
{
 int32 bi, ninsts;
 struct mod_t *mdp;
 struct nchglst_t *nchglp;

 if (!np->n_isavec)
  {
   asl_loc_do_qc_wire_intran_release(np, -1, lhsx, idp, nchglp_base);
  }
 else
  {
   nchglp = nchglp_base;
   mdp = get_inst_mod_();
   ninsts = mdp->flatinum;
   for (bi = biti; bi >= bitj; bi--)
    {
     /* SJM 04/15/01 - must pass any xmr itree context */
     /* AIV 02/03/12 - this should be passed nchglp here not base */
     asl_loc_do_qc_wire_intran_release(np, bi, lhsx, idp, nchglp); 
//AIV PTR FIXME - don't think this is portable or good
//take the original netchg address and get the bi's from theis address
     /* AIV 02/03/12 - this was wrong - nchglp is already is from idp offs */
     /* added misc_terr check as well - this code is still bad and it */
     /* put think this now works */
     if (nchglp != NULL)
      {
//AIV PUTMEBACK - DEBUG
//#ifdef __CVC_DEBUG__
       if (bi != nchglp->bi1) __misc_terr(__FILE__, __LINE__);
//#endif
       nchglp = (struct nchglst_t *) ((word32) nchglp + 
         ((word32) sizeof(struct nchglst_t) * (ninsts)));
      }
    }
  }
}

/*
 * do release for one net-bit or scalar in tran channel 
 *
 * this must push lhs xmr itree loc that it is passed if needed 
 * this handles release PLI callbacks if needed
 */
static void asl_loc_do_qc_wire_intran_release(struct net_t *np, int32 biti,
 struct expr_t *lhsx, t_midat *idp, struct nchglst_t *nchglp)
{
 int32 bi, ibase;
 int32 bit_forced, inum;
 struct qcval_t *frc_qcp;
 char s1[RECLEN];
 decl_idp_locals_;

 inum = get_inum_();
 ibase = inum*np->nwid;
 /* messages must use stmt itree loc */
 for (bi = 0; bi < np->nwid; bi++)
  {
   if (np->nu2.qcval[ibase + bi].qc_active) goto some_bit_forced;
  }
 strcpy(s1, " - no bits forced");
 __sgfinform(465, "attempted release of %s in instance %s failed%s",
  __msgexpr_tostr(__xs2, lhsx), __msg2_cur_blditree(__xs), s1);
 /* SJM - 04/15/01 - if nothing forced must not exec any call backs */ 
 return;

some_bit_forced:

 save_idp = NULL;
 if (idp != NULL) 
  { 
   set_save_idp_(idp); 
  }

 /* know some forced or will not get here */
 bit_forced = TRUE;
 bi = (biti == -1) ? 0 : biti;
 frc_qcp = &(np->nu2.qcval[ibase + bi]);
 if (!frc_qcp->qc_active) bit_forced = FALSE;
 else frc_qcp->qc_active = FALSE;

 /* now that released, assign value from current drivers */ 
 asl_loc_assign_1mdrwire(np, nchglp);

 if (!bit_forced)
  {
   if (save_idp != NULL)
    {
     restore_idp_();
    }

   strcpy(s1, " - some bits forced");
   __sgfinform(465, "attempted release of %s in instance %s failed%s",
    __msgexpr_tostr(__xs2, lhsx), __msg2_cur_blditree(__xs), s1);

   if (save_idp != NULL)
    {
     set_save_idp_(idp); 
    }
  } 

 /* FIXME - why not calling for every bit in range - only 1 bit possible? */
 /* notice can have both many wire specific and many all cbs */
 if (__num_vpi_rel_cbs > 0) __find_call_rel_cbs(np, biti);
 if (__vpi_rel_cb_always) __cb_all_rfs(np, biti, FALSE);

 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

extern void __asl_exec_qc_assign(struct st_t *stp, int32 rhsbi, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct dceauxlstlst_t *dcllp;
 struct expr_t *lhsx;

 lhsx = stp->st.sqca->qclhsx;
 dcllp = stp->st.sqca->rhs_qcdlstlst;
 asl_loc_do_qc_assign(stp, lhsx, rhsbi, dcllp, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_force(struct st_t *stp, int32 rhsbi, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct dceauxlstlst_t *dcllp;
 struct expr_t *lhsx;

 lhsx = stp->st.sqca->qclhsx;
 dcllp = stp->st.sqca->rhs_qcdlstlst;
 asl_loc_do_qc_regforce(stp, lhsx, rhsbi, dcllp, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_assign_concat(struct st_t *stp, int32 rhsbi, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs, struct expr_t *lhsx)
{
 struct dceauxlstlst_t *dcllp;

 dcllp = stp->st.sqca->rhs_qcdlstlst;
 asl_loc_do_qc_assign(stp, lhsx, rhsbi, dcllp, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_force_concat(struct st_t *stp, int32 rhsbi, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs, struct expr_t *lhsx)
{
 struct dceauxlstlst_t *dcllp;

 dcllp = stp->st.sqca->rhs_qcdlstlst;
 asl_loc_do_qc_regforce(stp, lhsx, rhsbi, dcllp, nchglp, nchg_idp_ofs);
}

static void asl_loc_do_qc_regforce(struct st_t *qcastp, 
 struct expr_t *lhsx, int32 rhsbi, struct dceauxlstlst_t *dcllp,
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 int32 stmt_inum, inum;
 struct net_t *np;
 struct gref_t *grp;
 struct qcval_t *assgn_qcp, *frc_qcp; 
 t_midat *xmr_idp;
 struct expr_t *rhsx;
 struct mod_t *mdp;
 decl_idp_locals_;

 /* if lhs xmr, change to target since forcing in target instance */
 save_idp = NULL;
 /* for XMR need stmt context inum for getting dcellst linked on stmt */
 stmt_inum = get_inum_();
 xmr_idp = NULL;
 if (lhsx->optyp == GLBREF)
  {
   grp = lhsx->ru.grp;
   xmr_idp = __xmrget_refgrp_to_targ(grp);
   set_save_idp_(xmr_idp); 
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 else if (lhsx->optyp != ID) __case_terr(__FILE__, __LINE__);
#endif
 np = lhsx->lu.sy->el.enp;

 /* for reg var 2 records always allocated, first is force and 2nd assign */
 inum = get_inum_();
 frc_qcp = &(np->nu2.qcval[2*inum]);
 assgn_qcp = &(np->nu2.qcval[2*inum + 1]);

 /* case 1, force pending */
 if (frc_qcp->qc_active) 
  { 
   /* turn off current (if lhs concat many) list of rhs dces */
   if (frc_qcp->qcdcep != NULL) __dcelst_off(frc_qcp->qcdcep);
   frc_qcp->qcdcep = NULL;
   frc_qcp->qc_active = FALSE;
   goto setup_force;
  }

 /* if qc assign pending, inactivate but leave ptrs and set bit */
 if (assgn_qcp->qc_active)
  {
   /* turn off the assign list - will be turned on if reg force released */
   if (assgn_qcp->qcdcep != NULL) __dcelst_off(assgn_qcp->qcdcep);
   assgn_qcp->qc_active = FALSE;
   assgn_qcp->qc_overridden = TRUE;
  }
setup_force:
 /* setup the new force */
 frc_qcp->qc_active = TRUE;
 frc_qcp->qcstp = qcastp; 
 frc_qcp->qcrhsbi = rhsbi; 
 frc_qcp->qclhsbi = -1;
 frc_qcp->lhsidp = __idp;
 /* SJM 06/23/02 - add qc dcep list (right one if lhs cat) to qcval rec */
 /* one needed for each lhs element because reg release can do separately */
 frc_qcp->qcdcep = dcllp->dcelsttab[stmt_inum];

 if (save_idp != NULL)
  { 
   xmr_idp = __idp; 
   restore_idp_();
  }

 /* start force by storing rhs of force - dces will cause dce chges */
 /* these routines need ref itree loc not lhs xmr */
 rhsx = qcastp->st.sqca->qcrhsx; 
 asl_loc_do_qc_store(np, frc_qcp, qcastp->st.sqca->qclhsx, rhsx, nchglp);

 /* SJM 07/19/02 - must not turn on any rhs dces until store done */
 /* turn on reg force for this set of dces if non constant rhs */ 
 if (frc_qcp->qcdcep != NULL) __dcelst_on(frc_qcp->qcdcep);

 /* but these need to run in itree context of lhs */
 if (save_idp != NULL)
  {
   set_save_idp_(xmr_idp); 
  }

 /* notice can have both many wire specific and many all cbs */
 if (__num_vpi_force_cbs > 0) __find_call_force_cbs(np, -1);
 if (__vpi_force_cb_always) __cb_all_rfs(np, -1, TRUE);

 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

static void asl_loc_do_qc_assign(struct st_t *qcastp, struct expr_t *lhsx,
 int32 rhsbi, struct dceauxlstlst_t *dcllp, struct nchglst_t *nchglp, 
 size_t nchg_idp_ofs)
{
 int32 stmt_inum, inum; 
 t_midat *xmr_idp;
 struct net_t *np;
 struct gref_t *grp;
 struct qcval_t *frc_qcp, *assgn_qcp; 
 struct expr_t *rhsx;
 struct mod_t *mdp;
 decl_idp_locals_;

 /* assign to lhs itree loc. */
 save_idp = NULL;
 /* SJM 05/23/03 - need to access stmt info from original inum if XMR */
 stmt_inum = get_inum_();
 if (lhsx->optyp == GLBREF)
  { 
   grp = lhsx->ru.grp; 
   xmr_idp = __xmrget_refgrp_to_targ(grp); 
   set_save_idp_(xmr_idp); 
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 else if (lhsx->optyp != ID) __case_terr(__FILE__, __LINE__);
#endif
 np = lhsx->lu.sy->el.enp;

 /* for reg var 2 records always allocated, first is force and 2nd assign */
 inum = get_inum_();
 frc_qcp = &(np->nu2.qcval[2*inum]);
 assgn_qcp = &(np->nu2.qcval[2*inum + 1]);
 /* if active force of wire just fill assign qcval so when force removed */
 /* assign becomes active - but do not make qc assign active */
 if (frc_qcp->qc_active)
  {
   /* notice this can replace other over-ridden */
   assgn_qcp->qc_overridden = TRUE;
   assgn_qcp->qcstp = qcastp;
   assgn_qcp->qcrhsbi = rhsbi; 
   assgn_qcp->qclhsbi = -1; 
   /* need lhs target inst. loc including non xmr same for change assign */
   assgn_qcp->lhsidp = __idp;
   /* assign group of dces (usually 1) - if lhs concat this lhs expr's one */
   /* but don't turn on yet */
   /* SJM 05/23/03 - dcllp is linked off stmt and has stmt instances */
   assgn_qcp->qcdcep = dcllp->dcelsttab[stmt_inum];

   if (save_idp != NULL)
    {
     restore_idp_();
    }

   return;
  }
 /* if active assign, deactivate before setting new - know fields replaced */
 if (assgn_qcp->qc_active)
  {
   assgn_qcp->qc_active = FALSE;
   /* turn on dces after doing store if rhs dces */
   /* SJM 08/18/02 - bug - this was turning on but must turn off */
   if (assgn_qcp->qcdcep != NULL) __dcelst_off(assgn_qcp->qcdcep);
  }

 /* SJM 07/19/02 - was not making assign active */
 assgn_qcp->qc_active = TRUE;
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 /* DBG remove - can't be over-ridden by force if get here */
 if (assgn_qcp->qc_overridden) __misc_terr(__FILE__, __LINE__);
 /* --- */
#endif
 /* but still save in case reg var force removed */
 assgn_qcp->qcstp = qcastp;
 assgn_qcp->qcrhsbi = rhsbi; 
 assgn_qcp->qclhsbi = -1;
 /* do store and build dces in ref. itree loc. */ 
 assgn_qcp->lhsidp = __idp;
 /* assign group of dces (usually 1) - if lhs concat this lhs expr's one */
 assgn_qcp->qcdcep = dcllp->dcelsttab[stmt_inum];

 if (save_idp != NULL)
  {
   restore_idp_();
  }

 /* these routines need ref. itree loc - they set right context for xmr */
 rhsx = qcastp->st.sqca->qcrhsx; 
 asl_loc_do_qc_store(np, assgn_qcp, qcastp->st.sqca->qclhsx, rhsx, nchglp);

 /* turn on dces after doing store if rhs dces */
 if (assgn_qcp->qcdcep != NULL) __dcelst_on(assgn_qcp->qcdcep);

 /* FIXME ??? - assign callbacks go here */
}

/*
 * AIV 05/09/11 - just make these a wrapper for now.  This is bad to use
 * interp but since it is rarely used it really doen't matter.
 */
extern void __asl_assign_qcaf_regform_concat(struct st_t *stp)
{
 __exec_qc_assign(stp, FALSE);
}
       
/*
 * AIV 05/09/11 - just make these a wrapper for now.  This is bad to use
 * interp but since it is rarely used it really doen't matter.
 */
extern void __asl_assign_qcaf_concat(struct st_t *stp)
{
 __exec_qc_wireforce(stp);
}



static void asl_loc_assign_1mdrwire(struct net_t *np, struct nchglst_t *nchglp)
{
 struct xstk_t *xsp;
 byte *sbp;
 int32 sbi, lhs_changed;
 byte *abp;
 word32 *app, *bpp;

 /* separate routines for rare multi-fi wires with delay */
 /* here since schedule lhs changed always off */
 lhs_changed = FALSE;
 sbp = NULL;
 /* first most common strength case since know muliple drive */
 if (np->n_stren)
  {
   /* get new value of wire from combination of all drivers */
   xsp = __stload_mdrwire(np);
   sbp = (byte *) xsp->ap;

   /* notice any force overrides even tri reg */
   if (np->frc_assgn_allocated
    && !__correct_forced_newwireval(np, xsp->ap, xsp->bp))
    { __pop_xstk(); return; }

   /* short circuit chg store into strength wire */
   abp = (byte *) &(__idp[np->nva_ofs]);

   /* no delay form trireg wire, correct for same value cap. strength */
   if (np->ntyp == N_TRIREG)
    {
     for (sbi = 0; sbi < np->nwid; sbi++)
      {
       if (sbp[sbi] == ST_HIZ)
        sbp[sbi] = (byte) ((abp[sbi] & 3) | __cap_to_stren[np->n_capsiz]);
      }
    }
   if (nchglp != NULL)
    {
     if (memcmp(abp, sbp, np->nwid) != 0)
      {
       memcpy(abp, sbp, np->nwid);
       lhs_changed = TRUE;
      }
    }
   else memcpy(abp, sbp, np->nwid);
  }
 else
  {
   /* multiple driver non strength no delay case */
   /* xsp is new wire value */
   /* load address and store value use current (np lhs) itree place */
   xsp = __load_mdrwire(np);

   if (np->frc_assgn_allocated
    && !__correct_forced_newwireval(np, xsp->ap, xsp->bp))
    { __pop_xstk(); return; }

   /* notice this address because of packing cannot be stored into */
   __ld_addr(&app, &bpp, np);
   if (nchglp != NULL)
    {
     if (np->nwid <= WBITS)
      { if (app[0] == xsp->ap[0] && bpp[0] == xsp->bp[0]) goto done; }
     else
      {
       if (cmp_vval_(app, xsp->ap, np->nwid) == 0
        && cmp_vval_(bpp, xsp->bp, np->nwid) == 0) goto done;
      }
     lhs_changed = TRUE;
    }
   __st_val(np, xsp->ap, xsp->bp, xsp->xslen); 
  }

done:
 if (lhs_changed) asl_loc_record_nchg(np, nchglp);
 __pop_xstk();
}

extern void __asl_assign_qcaf(struct dcevnt_t *dcep, struct nchglst_t *nchglp,
 size_t nchg_idp_ofs)
{
 struct expr_t *lhsx, *rhsx; 
 struct qcval_t *qcvalp;
 struct xstk_t *xsp;
 struct net_t *np;
 struct qcval_t *frc_qcp; 
 struct mod_t *mdp;
 struct st_t *stp;
 t_midat *lhs_idp;
 int32 inum, bi, ibase, bitj, biti;
 decl_idp_locals_;

 save_idp = NULL;
 /* first must move itree loc. back to ref. (where lhs and rhs are) */ 
 if (dcep->dce_1inst) 
  { 
   set_save_idp_(dcep->dce_refu.idp); 
   /* AIV 04/11/12 - this also needs to set nchglp here for xmr version */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }  

 /* know some bit in rhs changed, get one qcval */
 /* here using fmon field really as union since unused in qca case */

 /* get the qc statement */
 /* evaluate the rhs */
 /* AIV 12/18/07 - this needs to get qcstp because can change at rt cannot */
 /* be passed as a fixed stmt to this wrapper */
 qcvalp = dcep->dceu2.dce_qcvalp;
 stp = qcvalp->qcstp;
 rhsx = stp->st.sqca->qcrhsx; 
 lhsx = stp->st.sqca->qclhsx;
 /* this converts rhs if needed and makes right lhs width */
 xsp = __eval_assign_rhsexpr(rhsx, lhsx);

 np = lhsx->lu.sy->el.enp;
 /* AIV 11/15/07 - inline version of assign_alllhs_bits() */
 /* notice lhs context is already saved here above */
 lhs_idp = __get_qc_wirrng(lhsx, &np, &biti, &bitj); 

 if (lhs_idp != NULL)
  {
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   if (save_idp == NULL)
    {
     set_save_idp_(lhs_idp); 
    }
   else
    {
     set_idp_(lhs_idp); 
    }
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }
 
 inum = get_inum_();
 ibase = np->nwid*inum;
 /* AIV 12/14/07 - these all always recorded as the whole net changing */
 /* AIV LOOKATME - could be per bit - would be better code?????? */
 for (bi = biti; bi >= bitj; bi--, frc_qcp--)
  {
   frc_qcp = &(np->nu2.qcval[ibase + bi]);
   asl_loc_do_qc2_wirestore(np, frc_qcp, xsp, nchglp);
  }

 __pop_xstk();
 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

extern void __asl_assign_scalar_qcaf(struct dcevnt_t *dcep, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct expr_t *lhsx, *rhsx; 
 struct qcval_t *qcvalp;
 struct xstk_t *xsp;
 struct net_t *np;
 struct qcval_t *frc_qcp; 
 struct mod_t *mdp;
 struct st_t *stp;
 t_midat *lhs_idp;
 int32 inum, ibase, bitj, biti;
 decl_idp_locals_;

 save_idp = NULL;
 /* first must move itree loc. back to ref. (where lhs and rhs are) */ 
 if (dcep->dce_1inst) 
  { 
   set_save_idp_(dcep->dce_refu.idp); 
   /* AIV 04/11/12 - this also needs to set nchglp here for xmr version */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }  

 /* know some bit in rhs changed, get one qcval */
 /* here using fmon field really as union since unused in qca case */

 /* get the qc statement */
 /* evaluate the rhs */
 /* AIV 12/18/07 - this needs to get qcstp because can change at rt cannot */
 /* be passed as a fixed stmt to this wrapper */
 qcvalp = dcep->dceu2.dce_qcvalp;
 stp = qcvalp->qcstp;
 rhsx = stp->st.sqca->qcrhsx; 
 lhsx = stp->st.sqca->qclhsx;
 /* this converts rhs if needed and makes right lhs width */
 xsp = __eval_assign_rhsexpr(rhsx, lhsx);

 np = lhsx->lu.sy->el.enp;
 /* AIV 11/15/07 - inline version of assign_alllhs_bits() */
 /* notice lhs context is already saved here above */
 lhs_idp = __get_qc_wirrng(lhsx, &np, &biti, &bitj); 

 if (lhs_idp != NULL)
  {
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   if (save_idp == NULL)
    {
     set_save_idp_(lhs_idp); 
    }
   else
    {
     set_idp_(lhs_idp); 
    }
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }
 
 inum = get_inum_();
 ibase = np->nwid*inum;
 frc_qcp = &(np->nu2.qcval[ibase]);
 asl_loc_do_qc2_wirestore(np, frc_qcp, xsp, nchglp);

 __pop_xstk();
 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

extern void __asl_assign_qcaf_regform(struct dcevnt_t *dcep, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct qcval_t *qcvalp;
 struct expr_t *lhsx, *rhsx; 
 struct xstk_t *xsp;
 int32 biti, bitj;
 t_midat *lhs_idp;
 struct net_t *np;
 struct st_t *stp;
 struct mod_t *mdp;
 decl_idp_locals_;

 save_idp = NULL;
 /* first must move itree loc. back to ref. (where lhs and rhs are) */ 
 if (dcep->dce_1inst) 
  { 
   set_save_idp_(dcep->dce_refu.idp); 
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }  

 /* know some bit in rhs changed, get one qcval */
 /* here using fmon field really as union since unused in qca case */

 /* get the qc statement */
 /* evaluate the rhs */
 /* AIV 12/18/07 - this needs to get qcstp because can change at rt cannot */
 /* be passed as a fixed stmt to this wrapper */
 qcvalp = dcep->dceu2.dce_qcvalp;
 stp = qcvalp->qcstp;
 rhsx = stp->st.sqca->qcrhsx; 
 lhsx = stp->st.sqca->qclhsx;
 /* this converts rhs if needed and makes right lhs width */
 xsp = __eval_assign_rhsexpr(rhsx, lhsx);

 /* if reg form and not concatenate, easy just use changed qcval */
 np = lhsx->lu.sy->el.enp;

 /* AIV 11/15/07 - need to get lhs idp to adjust nchg if xmr */
 lhs_idp = __get_qc_wirrng(lhsx, &np, &biti, &bitj); 
 if (lhs_idp != NULL)
  {
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) lhs_idp[nchg_idp_ofs];
    }
  }

 asl_loc_do_qc2_regstore(np, qcvalp, xsp, nchglp);
 __pop_xstk();

 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

extern void __asl_exec_qc_deassign_force(struct st_t *stp, 
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct expr_t *lhsx;

 lhsx = stp->st.sqcdea.qcdalhs;
 asl_loc_do_qc_regrelease(lhsx, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_deassign(struct st_t *stp)
{
 struct expr_t *lhsx;

 lhsx = stp->st.sqcdea.qcdalhs;
 asl_loc_do_qc_deassign(lhsx);
}

extern void __asl_exec_qc_deassign_force_concat(struct expr_t *lhsx,
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 asl_loc_do_qc_regrelease(lhsx, nchglp, nchg_idp_ofs);
}

extern void __asl_exec_qc_deassign_concat(struct expr_t *lhsx)
{
 asl_loc_do_qc_deassign(lhsx);
}

static void asl_loc_do_qc_regrelease(struct expr_t *lhsx,
 struct nchglst_t *nchglp, size_t nchg_idp_ofs)
{
 struct net_t *np;
 struct gref_t *grp;
 struct qcval_t *assgn_qcp, *frc_qcp; 
 t_midat *xmr_idp;
 int32 inum;
 struct expr_t *rhsx;
 struct mod_t *mdp;
 decl_idp_locals_;

 /* must release reg in itree loc. of lhs if xmr */
 save_idp = NULL;
 xmr_idp = NULL;
 if (lhsx->optyp == GLBREF)
  { 
   grp = lhsx->ru.grp; 
   xmr_idp = __xmrget_refgrp_to_targ(grp); 
   set_save_idp_(xmr_idp); 
   /* AIV 11/15/07 - for the xmr case the passed nchg is wrong if */
   /* only if ninsts > 1 becuase all nchgs > 1 are placed into the idp */
   mdp = get_inst_mod_();
   if (nchglp != NULL && mdp->flatinum > 1)
    {
     nchglp = (struct nchglst_t *) __idp[nchg_idp_ofs];
    }
  }
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 else if (lhsx->optyp != ID) __case_terr(__FILE__, __LINE__);
#endif
 np = lhsx->lu.sy->el.enp;

 /* for reg var 2 records always allocated, first is force and 2nd assign */
 inum = get_inum_();
 frc_qcp = &(np->nu2.qcval[2*inum]);
 assgn_qcp = &(np->nu2.qcval[2*inum + 1]);

 /* if no force, nothing to do */
 if (!frc_qcp->qc_active)
  {
   /* message here needs lhs xmr context */
   __sgfinform(465,
    "attempted release of reg %s in instance %s failed - never forced",
    __to_idnam(lhsx), __msg2_cur_blditree(__xs));
    if (save_idp != NULL)
     {
      restore_idp_();
     }
   return;
  }
 frc_qcp->qc_active = FALSE;
 /* turn off active force dces */
 if (frc_qcp->qcdcep != NULL) __dcelst_off(frc_qcp->qcdcep);
 frc_qcp->qcdcep = NULL;
 __force_active = FALSE;

 /* if pending but inactive assign - must reactivate it */
 if (assgn_qcp->qc_overridden)
  {
   /* these need to run in itree context of stmt not lhs if xmr */
   if (save_idp != NULL)
    { 
     xmr_idp = __idp; 
     restore_idp_();
    }

   /* AIV 11/16/07 - notice do need to get the rhsx from qcstp which */
   /* can varies at runtime so need to set qcstp */
   rhsx = assgn_qcp->qcstp->st.sqca->qcrhsx; 
   asl_loc_do_qc_store(np, assgn_qcp, assgn_qcp->qcstp->st.sqca->qclhsx, 
     rhsx, nchglp);
   /* build the QCAF dcelst - this must be build in rhs ref. itree loc. */

   assgn_qcp->qc_active = TRUE; 
   assgn_qcp->qc_overridden = FALSE;
   /* turn stored last dce list on */
   /* FIXME - this is never first time */
   if (assgn_qcp->qcdcep != NULL) __dcelst_on(assgn_qcp->qcdcep);
   __assign_active = TRUE;
  }
 else 
  { 
   if (save_idp != NULL)
    {
     xmr_idp = __idp;
     /* AIV 07/16/07 - suppose to restore here was wrong in 296f as well */
     restore_idp_();
    } 
   }

 /* these must run in lhs itree context for xmr */ 
 if (save_idp != NULL)
  {
   set_save_idp_(xmr_idp); 
  }

 /* notice can have both many wire specific and many all cbs */
 if (__num_vpi_rel_cbs > 0) __find_call_rel_cbs(np, -1);
 if (__vpi_rel_cb_always) __cb_all_rfs(np, -1, FALSE);

 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

static void asl_loc_do_qc_deassign(struct expr_t *lhsx) 
{
 t_midat *xmr_idp;
 struct net_t *np;
 struct gref_t *grp;
 struct qcval_t *frc_qcp, *assgn_qcp;
 int32 inum;
 decl_idp_locals_;

 /* must work in itree loc. of lhs if xmr */
 save_idp = NULL;
 if (lhsx->optyp == GLBREF)
  { 
   grp = lhsx->ru.grp; 
   xmr_idp = __xmrget_refgrp_to_targ(grp); 
   set_save_idp_(xmr_idp); 
  }
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 else if (lhsx->optyp != ID) __case_terr(__FILE__, __LINE__);
#endif
 np = lhsx->lu.sy->el.enp;
 
 /* for reg var 2 records always allocated, first is force and 2nd assign */
 inum = get_inum_();
 frc_qcp = &(np->nu2.qcval[2*inum]);
 assgn_qcp = &(np->nu2.qcval[2*inum + 1]);
 if (!assgn_qcp->qc_active && !assgn_qcp->qc_overridden)
  {
   __sgfinform(462,
    "attempted deassign of reg %s in instance %s failed - not assigned",
    __to_idnam(lhsx), __msg2_cur_blditree(__xs));
   goto done;
  }
 assgn_qcp->qc_active = FALSE; 
 /* turn off dces but do not empty qcval rec - will get refilled if needed */
 /* if over-ridden were not turned so do not need to turn off */
 if (!assgn_qcp->qc_overridden)
  {
   if (assgn_qcp->qcdcep != NULL) __dcelst_off(assgn_qcp->qcdcep);
  }
 assgn_qcp->qcdcep = NULL; 
 assgn_qcp->qc_overridden = FALSE;
 __assign_active = FALSE; 
 /* LOOKATME - extra work to set force flag only used for tracing */
 if (frc_qcp->qc_active)
  {
   /* dce list can be empty if forced to constant */
   __force_active = TRUE;
  }
done:
 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

/*
 * lower strength mask compare
 */
/* AIV 10/18/06 - was passing word32 * not bytes */
/* was indexing incorrectly on words running out of memory */
extern int32 __asl_jmp_eq_stmask(byte *sbp1, byte *sbp2, int32 blen)
{
 int32 bi;

 for (bi = 0; bi < blen; bi++)
  { 
   /* return one - oposite to use with testl false */
   if ((sbp1[bi] & 3) != (sbp2[bi] & 3)) 
    return(1); 
  }
 return(0); 
}

/*
 * asm trigger (schedule) event control both blocking
 */
extern void __asl_trigger_ectrl(struct tev_t *tevp)
{
 /* local version of __add_ev_to_front */
//AIV HERE2
 tevp->trigger = TRUE;
//AIV FIXME - only need to record time because of disable code
 tevp->etime = __simtime;
///////////////////
 /* AIV 01/19/09 - removed need to set __processing_pnd0s flag */
 if (__cur_te_endp == NULL)
  {
   /* also in pnd 0's front is just after current if set */
   if (__cur_tevp == NULL)
    {
     /* notice during add net chg elements cur tevp nil, so common to add */
     /* to end */ 
     if (__p0_te_hdrp == NULL) 
      {
       __p0_te_hdrp = __p0_te_endp = tevp; 
       /* AIV 01/03/08 - no need to set here */
       /* tevp->tenxtp = __free_event_pnd0_tevp; */
      }
     else 
      { 
       tevp->tenxtp = __p0_te_hdrp; 
       __p0_te_hdrp = tevp; 
      }
    }
   else
    {
     if (__cur_tevp != __p0_te_endp)
      {
       tevp->tenxtp = __cur_tevp->tenxtp;
       __cur_tevp->tenxtp->teprevp = tevp;
      }
     else 
      {
       __p0_te_endp = tevp;
       tevp->tenxtp = __free_event_pnd0_tevp;
      }
     __cur_tevp->tenxtp = tevp;
     tevp->teprevp = __cur_tevp;
    }
   /* this does not go on timing wheel or get counted */
  }
 else
  {
   /* adding to front is just after current since now processing current */
   /* AIV 06/06/08 - this can no longer happen here */
#ifdef __CVC_DEBUG__
   if (__cur_tevp == NULL) __misc_terr(__FILE__, __LINE__);
#endif
   if (__cur_tevp != __cur_te_endp)
    {
     tevp->tenxtp = __cur_tevp->tenxtp;
     __cur_tevp->tenxtp->teprevp = tevp;
    }
   else 
    {
     __cur_te_endp = tevp;
     tevp->tenxtp = __free_event_tevp;
    }
   __cur_tevp->tenxtp = tevp;
   tevp->teprevp = __cur_tevp;
  }
 /* in case disable, indicate suspended on ev thrd no suspend to disable */
 /* AIV 05/14/07 - no need to set th_dctp - in compiled code */
 /* tevp->tu.tethrd->th_dctp = NULL; */
}

#ifdef __XPROP__
//AIV EXPROP
extern void __asl_trigger_ectrl_xprop(struct tev_t *tevp, void *ep)
{
 /* local version of __add_ev_to_front */
 tevp->enterptr = ep;
//AIV HERE2
 tevp->trigger = TRUE;
//AIV FIXME - only need to record time because of disable code
 tevp->etime = __simtime;
///////////////////
 /* AIV 01/19/09 - removed need to set __processing_pnd0s flag */
 if (__cur_te_endp == NULL)
  {
   /* also in pnd 0's front is just after current if set */
   if (__cur_tevp == NULL)
    {
     /* notice during add net chg elements cur tevp nil, so common to add */
     /* to end */ 
     if (__p0_te_hdrp == NULL) 
      {
       __p0_te_hdrp = __p0_te_endp = tevp; 
       /* AIV 01/03/08 - no need to set here */
       /* tevp->tenxtp = __free_event_pnd0_tevp; */
      }
     else 
      { 
       tevp->tenxtp = __p0_te_hdrp; 
       __p0_te_hdrp = tevp; 
      }
    }
   else
    {
     if (__cur_tevp != __p0_te_endp)
      {
       tevp->tenxtp = __cur_tevp->tenxtp;
       __cur_tevp->tenxtp->teprevp = tevp;
      }
     else 
      {
       __p0_te_endp = tevp;
       tevp->tenxtp = __free_event_pnd0_tevp;
      }
     __cur_tevp->tenxtp = tevp;
     tevp->teprevp = __cur_tevp;
    }
   /* this does not go on timing wheel or get counted */
  }
 else
  {
   /* adding to front is just after current since now processing current */
   /* AIV 06/06/08 - this can no longer happen here */
#ifdef __CVC_DEBUG__
   if (__cur_tevp == NULL) __misc_terr(__FILE__, __LINE__);
#endif
   if (__cur_tevp != __cur_te_endp)
    {
     tevp->tenxtp = __cur_tevp->tenxtp;
     __cur_tevp->tenxtp->teprevp = tevp;
    }
   else 
    {
     __cur_te_endp = tevp;
     tevp->tenxtp = __free_event_tevp;
    }
   __cur_tevp->tenxtp = tevp;
   tevp->teprevp = __cur_tevp;
  }
 /* in case disable, indicate suspended on ev thrd no suspend to disable */
 /* AIV 05/14/07 - no need to set th_dctp - in compiled code */
 /* tevp->tu.tethrd->th_dctp = NULL; */
}
#endif

extern void __asl_compiled_ev_to_front(struct tev_t *tevp)
{
 __asl_trigger_ectrl(tevp);
}


/*
 * non blocking 
 */
extern void __asl_nb_trigger_ectrl(struct tev_t *tevp)
{
 /* local version of __add_ev_to_front */
 /* LOOKATME - is this right */
 /* here ok to have list of events (non inertial) */
 /* know at least 1 event, remove head schedule for now after trigger */
 asl_loc_add_pnd0_event(tevp);
 /* works because no new tevs that could cause realloc called */
 /* AIV 01/03/08 - notice no reason to set here will always be net for nb */
 /* tevp->tenxtp = __free_event_pnd0_tevp; */
 /* this now looks like normal delay control nb */ 
 /* AIV 11/31/07 - no need to null the tu.tenbpa anymore */
 /* tevp->tu.tenbpa->nbdctp = NULL; */
}

/*
 * asm trigger monitor (not fmon) 
 *
 * no ops
 */

/*
 * asm trigger fmon
 */
extern void __asl_fmonit_trigger(struct dcevnt_t *dcep)
{
 struct fmonlst_t *fmonp;
 struct fmselst_t *fmsep;

 fmonp = dcep->dceu2.dce_fmon;
 /* if already activated, nothing to do - activation happens at run time */
 /* after 1st exec this does nothing */
 /* LOOKATME - maybe should turn off after first - simple checking but rare */
 if (fmonp->fmse_trig != NULL) return;

 /* allocate new se fmon */
 if (__fmse_freelst == NULL) 
  fmsep = (struct fmselst_t *) __my_malloc(sizeof(struct fmselst_t));
 else
  {
   fmsep = __fmse_freelst;
   __fmse_freelst = __fmse_freelst->fmsenxt;
  }
 fmsep->fmsenxt = NULL;
 fmsep->fmon = fmonp;

 /* link it on list */
 if (__fmonse_hdr == NULL) __fmonse_hdr = fmsep;
 else __fmonse_end->fmsenxt = fmsep;
 __fmonse_end = fmsep;
 /* mark triggered */
 fmonp->fmse_trig = fmsep;
 __slotend_action |= SE_FMONIT_TRIGGER;     
}

/*
 * copied from __ld_stval in v_ex2.c
 */
extern void __asl_movabw_fr_svec(word32 *resap, byte *sbp, int32 blen)
{
 int32 bi, wlen;
 word32 tmpw;
 word32 *resbp;
 
 /* zero unused high bits in high word32 only - rest will be selected into */
 wlen = wlen_(blen);
 resbp = &(resap[wlen]);
 resap[wlen - 1] = 0L;
 resbp[wlen - 1] = 0L;

 for (bi = 0; bi < blen; bi++)
  {
   tmpw = (word32) sbp[bi];
   /* AIV FIXME - could inline these slightly better code - see onew case */
   __lhsbsel(resap, bi, tmpw & 1L);
   __lhsbsel(resbp, bi, (tmpw >> 1) & 1L);
  }
}

/*
 * one word version returns the new value
 * copied from __ld_stval in v_ex2.c
 * AIV 12/29/06 - added this insn because cannot pass a pointer to a tmp
 * which is <= wbits (no leal) because this makes it a tmp which
 * cannot be put into a register
 */
//AIV64 - this must return word32 not an int32
//AIV LOOKATME - think move of these if not all should be word32
//maybe move to scheme for 64-bit to use 32-bit regs therefore can still
//return int32 - such as TRUE/FALSE return values
extern word32 __asl_movabw_onew_fr_svec(byte *sbp, int32 blen)
{
 int32 bi;
 word32 tmpw, res, resb;
 
 /* zero unused high bits in high word32 only - rest will be selected into */
 res = resb = 0;
 for (bi = 0; bi < blen; bi++)
  {
   tmpw = (word32) sbp[bi];
   /* AIV 12/21/07 - don't use __lhsbsel here know it is low word */
   res |= ((tmpw & 1L) << bi);
   resb |= (((tmpw >> 1) & 1L) << bi);
  }
 /* AIV 12/29/06 - the b part (resb) always goes into ECX */
 /* AIV LOOKATME BEWARE - machine dependent - but most of bbgen3 is as well */
#ifdef __CVC32__
 __asm__ ("movl %0, %%ecx" : : "g" (resb));
#else
 __asm__ ("movq %0, %%rcx" : : "g" (resb));
#endif
 return(res);
}

/*
 * convert all x/z four state values to 0s
 */
extern void __asl_4state_to_2state_wide(t_midat *dstp, t_midat *srcp, 
 int32 wlen)
{
 int32 wi;
 word32 t1;
 word32 *bp;

 bp = &(srcp[wlen]); 
 for (wi = 0; wi < wlen; wi++)
  {
   t1 = ~bp[wi];
   dstp[wi] = srcp[wi] & t1;
  }
}

/*
 * routine for wrd a/b vec store add stren into svec
 */
extern void __asl_movsb_fr_wstad(byte *sbp, word32 *ap, int32 blen,
 word32 stval) 
{
 int32 bi;
 word32 aw, bw;

 for (bi = 0; bi < blen; bi++)
  {
   aw = (ap[0] >> bi) & 1;
   bw = (ap[1] >> bi) & 1;
   aw |= (bw << 1);
   /* if z no strength */
   if (aw == 2) sbp[bi] = (byte) aw;
   else
    {
     aw |= (stval << 2);
     /* SJM 08/15/01 - this is vector - from typo was only set 0 */
     sbp[bi] = __stren_map_tab[aw];
    }
  }
}

/*
 * routine for wide a/b vec store add stren into svec
 */
extern void __asl_movsb_fr_widestad(byte *sbp, word32 *ap, int32 blen,
 word32 stval) 
{
 int32 bi;
 word32 *bp, aw, bw;

 bp = &(ap[wlen_(blen)]); 
 for (bi = 0; bi < blen; bi++)
  {
   aw = rhsbsel_(ap, bi);
   bw = rhsbsel_(bp, bi);
   aw |= (bw << 1);
   /* if z no strength */
   if (aw == 2) sbp[bi] = (byte) aw;
   else
    {
     aw |= (stval << 2);
     /* SJM 08/15/01 - this is vector - from typo was only set 0 */
     sbp[bi] = __stren_map_tab[aw];
    }
  }
}

/*
 * routine to for 1 bit store st and val
 */
extern byte __asl_movsb_fr_scalstad(word32 aw, word32 stval) 
{
 word32 sw, bw;

 /* AIV 10/24/05 - was shifting in the wrong direction for the bpart */
 bw = (aw >> 1) & 1;
 aw = (aw & 1L) | ((bw << 1) & 2L);
 /* if z, no strength */
 if (aw == 2) return(aw);

 aw |= (stval << 2);
 sw = __stren_map_tab[aw];
 return(sw); 
} 

/*
 * add the conta assign strength for a rhs that already has strength
 */
extern void __asl_rhs_conta_stren(byte *sbp, int32 new_st, int32 bytlen)
{
 int32 bi, aw;

 for (bi = 0; bi < bytlen; bi++)
  {
   aw = (int32) sbp[bi];
   aw = aw & 3;
   if (aw != 2)
    {
     aw |= (new_st << 2);
     sbp[bi] = __stren_map_tab[aw];
    }
  }
}

/*
 * convert a word into a real
 * from __cnvt_stk_to_real
 */
extern double __asl_movr_fr_w(word32 *wp, int32 blen)
{
 word32 u;
 word64 tim;
 double d1;
 
 if (blen > WBITS)
  {
   tim = ((word64) wp[0]) | (((word64) wp[1]) << 32);
   __v64_to_real(&d1, &tim);
  }
 else
  {
   u = (word32) wp[0];
   d1 = (double) u; 
  }
 return(d1);
}

/*
 * convert a signed word into a real
 * from __cnvt_stk_to_real
 * AIV 01/10/07 FIXME - make a narrow case passing narrow as pointer
 * currently hinders it being placed into a register
 */
extern double __asl_movr_fr_sgnw(word32 *wp, int32 blen)
{
 int32 i;
 word32 mask_val;
 word64 tim;
 double d1;
 
 if (blen > WBITS)
  {
   tim = ((word64) wp[0]) | (((word64) wp[1]) << 32);
   __v64_to_real(&d1, &tim);
  }
 else
  {
   /* AIV 09/29/06 - if sign bit on and < WBITS need mask prior to cast */
   /* AIV 01/10/07 - changed in interp needed here as well */
   mask_val = wp[0]; 
   if (blen != WBITS)
    {
     if ((mask_val & (1UL << (blen - 1))) != 0)
      {
       mask_val |= ~(__masktab[blen]);
      }
    }
   i = (int32) mask_val; 
   d1 = (double) i; 
  }
 return(d1);
}

/*
 * convert a real into a reg 
 */
extern void __asl_movw_fr_r(word32 *resap, double d)
{
 int32 i;
 
 i = ver_rint_(d);
 resap[0] = (word32) i;
 resap[1] = 0L;
}

/*
 * 2-state contains no b-part
 */
extern word32 __asl_movw_fr_r_2state(double d)
{
 int32 i;
 
 i = ver_rint_(d);
 return((word32) i);
}

/*
 * ASM LIB ROUTINES FOR TO EVAL FUNCTIONS - HANDLES XSTK INTERACTION
 */

/*
 * wrapper to sys function call 
 */
extern void *__asl_exec_sysfunc(struct expr_t *ndp)
{
 word32 *ap;

 __exec_sysfunc(ndp);
 /* lowered to x86 copies this address to tmp name (reg in ebp tab) */ 
 /* must always emit pop xstk vinsn after call */
 /* AIV 02/09/12 - this should just save the pointer and do the dec here */
 /* was lowering the __xspi-- which was wrong for 64-bit since this is */
 /* an int32 was overwritting memory - should just do the -- here */
 ap = __xstk[__xspi]->ap;
 __xspi--;
 return(ap);
}

/*
 * same as regular sysfunc wrapper but sets stmt location
 */
extern void *__asl_exec_sysfunc_stmtloc(struct expr_t *ndp, struct st_t *stp)
{
 word32 *ap;
 int32 save_fndx, save_lineno;

 /* set the stmt file and line numbers */
 save_fndx = __sfnam_ind;
 save_lineno = __slin_cnt;
 __sfnam_ind = stp->stfnam_ind;
 __slin_cnt = stp->stlin_cnt;

 __exec_sysfunc(ndp);

 __sfnam_ind = save_fndx;
 __slin_cnt = save_lineno;
 /* lowered to x86 copies this address to tmp name (reg in ebp tab) */ 
 /* must always emit pop xstk vinsn after call */
 /* AIV 02/09/12 - this should just save the pointer and do the dec here */
 /* was lowering the __xspi-- which was wrong for 64-bit since this is */
 /* an int32 was overwritting memory - should just do the -- here */
 ap = __xstk[__xspi]->ap;
 __xspi--;
 return(ap);
}

/*
 * adjust xstk wrapper - now just used for DPI for SV strings
 */
extern void __asl_pop_xstk(int32 num)
{
 __xspi -= num;
} 

/*
 * ASM LIB ROUTINES FOR WIDE CASE SELECT EVAL
 */

/*
 * asm lib routine for wide case select versus label match compare
 * return 0 if match (same) else 1
 */
extern int32 __asl_widcas_eval(word32 *awp1, word32 *awp2, int32 wlen)
{
 int32 wi;
 word32 *bwp1, *bwp2;

 bwp1 = &(awp1[wlen]);
 bwp2 = &(awp2[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   if (((awp1[wi] ^ awp2[wi]) | (bwp1[wi] ^ bwp2[wi])) != 0)
    return(1);
  }
 return(0);
}

/*
 * asm lib routine for wide casex select versus label match compare
 * return 0 if match (same) else 1
 */
extern int32 __asl_widcasx_eval(word32 *awp1, word32 *awp2, int32 wlen)
{
 int32 wi;
 word32 *bwp1, *bwp2;

 bwp1 = &(awp1[wlen]);
 bwp2 = &(awp2[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   /* if any one bit matches - match */
   if ((((awp1[wi] ^ awp2[wi]) | (bwp1[wi] ^ bwp2[wi]))
    & ~(bwp1[wi] | bwp2[wi])) != 0) return(1);
  }
 return(0);
}

/*
 * asm lib routine for wide casez select versus label match compare
 * return 0 if match (same) else 1
 */
extern int32 __asl_widcasz_eval(word32 *awp1, word32 *awp2, int32 wlen)
{
 int32 wi;
 word32 mask;
 word32 *bwp1, *bwp2;

 bwp1 = &(awp1[wlen]);
 bwp2 = &(awp2[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   mask = ((awp1[wi] | ~bwp1[wi]) & (awp2[wi] | ~bwp2[wi]));
   if ((((awp1[wi] ^ awp2[wi]) | (bwp1[wi] ^ bwp2[wi])) & mask) != 0)
    return(1);
  }
 return(0);
}

/*
 * ASM LIB ROUTINES FOR WIDE EXPRESSION EVAL
 */

/*
 * wide bitxor wrapper
 */
extern void __asl_wide_bitxor(word32 *res, word32 *op1, word32 *op2,
 int32 wlen)
{
 int32 i;

 for (i = 0; i < wlen; i++)
  {
   res[i] = op1[i] ^ op2[i];
  }
}

/*
 * wide bit and  wrapper
 */
extern void __asl_wide_notl(word32 *res, word32 *op1, int32 wlen)
{
 int32 i;

 for (i = 0; i < wlen; i++)
  {
   res[i] = ~op1[i];
  }
}

/*
 * wide bit and  wrapper
 */
extern void __asl_wide_bitand(word32 *res, word32 *op1, word32 *op2,
 int32 wlen)
{
 int32 i;

 for (i = 0; i < wlen; i++)
  {
   res[i] = op1[i] & op2[i];
  }
}

/*
 * wide redxor wrapper
 */
extern word32 __asl_wide_redxor(word32 *op1ap, int32 wlen)
{
 int32 wi;
 word32 rtmp, rtmp2;

 /* any unused 0's can be ignored - just produce 0 */
 for (rtmp = 0, wi = 0; wi < wlen; wi++)
  {
   /* this returns 1 bit result */ 
   rtmp2 = __wrd_redxor(op1ap[wi]);
   rtmp ^= rtmp2;
  }
 return(rtmp);
}

#ifdef __XPROP__
/*
 * WRAPPER ROUTINES FOR XPROP 
 */

/* 
 * AIV 08/02/11 - new xprop wrapper
 * long binary bit or  - xprop version
 */
extern void __asl_wid_bin_bitor_x(word32 *resap, word32 *op1ap, word32 *op2ap,
 int32 blen)
{
 int32 wlen;
 int32 wi;
 word32 *op1bp, *op2bp, *resbp;

 wlen = wlen_(blen);
 op1bp = &(op1ap[wlen]);
 op2bp = &(op2ap[wlen]);
 resbp = &(resap[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   if ((op1bp[wi] | op2bp[wi]) == 0L)
    { resbp[wi] = 0L; resap[wi] = op1ap[wi] | op2ap[wi]; }
   else
    {
     resap[wi] = (op1ap[wi] | op2ap[wi]) | (op1bp[wi] | op2bp[wi]);
     resbp[wi] = (op1bp[wi] | op2bp[wi]);
    }
  }
 /* AIV 11/08/06 - need the mask here */
 resap[wlen - 1] &= __masktab[ubits_(blen)];
 resbp[wlen - 1] &= __masktab[ubits_(blen)];
}

/*
 * wide xprop version - may now return X
 */
extern int32 __asl_wid_un_redor_x(word32 *op1ap, int32 blen)
{
 int32 wlen;
 word32 *op1bp;

 wlen = wlen_(blen);
 op1bp = &(op1ap[wlen]);

 /* if even 1 1 and no x/z bits, reduction and will turn to 1 */
 if (vval_is0_(op1bp, blen))
  {
   if (!vval_is0_(op1ap, blen)) return(1);
   else return(0);
  }
 /* if any x now must return x */
 return(3);
}

/*
 * same as has_x_only_edge in v_sim
 * except T/F turn values are inverted
 */
extern int32 __asl_has_xedge_wide(word32 *wp1, word32 *wp2, int32 wlen)
{
 int32 i, has_xs;
 word32 *wbp1, *wbp2;
 word32 aval1, aval2, bval1, bval2, has_xval;

 wbp1 = &(wp1[wlen]);
 wbp2 = &(wp2[wlen]);
 has_xs = FALSE;
 for (i = 0; i < wlen; i++)
  {
   /* only include the x edges - not zs */
   aval1 = wp1[i];
   aval2 = wp2[i];
   bval1 = wbp1[i] & aval1;
   bval2 = wbp2[i] & aval2;
   /* if has xs */
   has_xval = (bval1 | bval2);
   if (has_xval)
    {
     has_xs = TRUE;
     /* mask out b bits */
     if ((aval1 | has_xval) ^ (aval2 | has_xval))
        return(TRUE);
    }
  }
 return(!has_xs);
}

/*
 * same as has_x_only_edge_stren in v_sim
 * except T/F turn values are inverted
 */
extern int32 __asl_has_xedge_wide_st(byte *bp1, byte *bp2, int32 blen)
{
 int32 i, has_xs;
 byte aval1, aval2, bval1, bval2, has_xval;

 has_xs = FALSE;
 for (i = 0; i < blen; i++)
  {
   /* only include the x edges - not zs */
   aval1 = bp1[i] & 1;
   aval2 = bp2[i] & 1;
   bval1 = (((bp1[i] & 3) >> 1) & 1L) & aval1;
   bval2 = (((bp2[i] & 3) >> 1) & 1L) & aval2;
   /* if has xs */
   has_xval = (bval1 | bval2);
   if (has_xval)
    {
     has_xs = TRUE;
     /* mask out b bits */
     if ((aval1 | has_xval) ^ (aval2 | has_xval))
        return(TRUE);
    }
  }
 return(!has_xs);
}

/*
 * same as xprop_check_case_net_assigned from v_xprop
 */
extern void __asl_xprop_check_case_net_set(struct st_t *stp, int32 matched)
{
 int32 i, wlen;
 struct net_t *np;
 word32 *setbits_wp, *accum_wp;
 struct xprop_t *xprop;

 /* if hasn't matched yet nothing to do */
 if (matched <= 1) return;

 xprop = stp->st.scs.xprop;
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];
   /* if set in the first block and not the second - set accumulator to X */ 
   /* and set */
   // AIV LOOKATME - could just optimize this as for now on known to be X
   // with a known_x - this way does no more combining
   // AIV LOOKATME - not doing per bit saving here - intentions unknown so
   // setting values to X
   if (xprop->net_block1_set[i] && !xprop->net_block2_set[i]) 
    {
     xprop->net_block2_set[i] = TRUE;
     
     wlen = wlen_(np->nwid);
     /* all bits set marking */
     setbits_wp = xprop->bits_set[i];
     memset(setbits_wp, 0xff, wlen*WRDBYTES);

     /* set to x */
     accum_wp = xprop->accum_block2[i];
     set_regtox_(accum_wp, &(accum_wp[wlen]), np->nwid);
    }
  }
}

/*
 * accum rhs value for each lhsx - wide
 */
extern void __asl_stmt_assign_to_accum_wide(struct st_t *astp, 
 struct st_t *xstp, word32 *ap, word32 *bp)
{
 struct expr_t *lhsx;
 struct xprop_t *xprop;

 if (xstp->stmttyp == S_CASE) xprop = xstp->st.scs.xprop;
 else xprop = xstp->st.sif.xprop;

 lhsx = astp->st.spra.lhsx;
 __assign_lhsx_to_accum(lhsx, ap, bp, xprop);
}

/*
 * accum rhs value for each lhsx - one word
 */
extern void __asl_stmt_assign_to_accum_1w(struct st_t *astp, 
 struct st_t *xstp, word32 aval, word32 bval)
{
 struct expr_t *lhsx;
 struct xprop_t *xprop;

 if (xstp->stmttyp == S_CASE) xprop = xstp->st.scs.xprop;
 else xprop = xstp->st.sif.xprop;

 lhsx = astp->st.spra.lhsx;
 __assign_lhsx_to_accum(lhsx, &aval, &bval, xprop);
}

/*
 *
 */
extern void __asl_stmt_assign_to_accum_1w_if_id(struct net_t *np, 
 struct st_t *xstp, word32 aval, word32 bval)
{
 struct xprop_t *xprop;

 xprop = xstp->st.sif.xprop;
 asl_loc_stmt_assign_to_accum_1w_id(np, xprop, aval, bval);
}

/*
 *
 */
extern void __asl_stmt_assign_to_accum_wide_if_id(struct net_t *np, 
 struct st_t *xstp, word32 *ap, word32 *bp)
{
 struct xprop_t *xprop;

 xprop = xstp->st.sif.xprop;
 asl_loc_stmt_assign_to_accum_wide_id(np, xprop, ap, bp);
}

/*
 *
 */
extern void __asl_stmt_assign_to_accum_wide_case_id(struct net_t *np, 
 struct st_t *xstp, word32 *ap, word32 *bp)
{
 struct xprop_t *xprop;

 xprop = xstp->st.scs.xprop;
 asl_loc_stmt_assign_to_accum_wide_id(np, xprop, ap, bp);
}

/*
 *
 */
extern void __asl_stmt_assign_to_accum_1w_case_id(struct net_t *np, 
 struct st_t *xstp, word32 aval, word32 bval)
{
 struct xprop_t *xprop;

 xprop = xstp->st.scs.xprop;
 asl_loc_stmt_assign_to_accum_1w_id(np, xprop, aval, bval);
}


/*
 *
 */
static void asl_loc_stmt_assign_to_accum_1w_id(struct net_t *np, 
 struct xprop_t *xprop, word32 aval, word32 bval)
{
 int32 xprop_ndx, xblock, blen;
 int32 *accum_set_ip;
 word32 *accum_wp, *setbits_wp, *setblock_mask_wp;

 xprop_ndx = np->n_xprop_ndx;
 xblock = xprop->xblock;
#ifdef __CVC_DEBUG__
 /* DBG remove --- */
 if (xprop_ndx < 0) __misc_terr(__FILE__, __LINE__);
 if (xprop_ndx >= xprop->ncount) __misc_terr(__FILE__, __LINE__);
 /* ----- */
#endif

 if (xblock == 0)
  {
   accum_wp = xprop->accum_block1[xprop_ndx];
   accum_set_ip = &(xprop->net_block1_set[xprop_ndx]);
  }
 else 
  {
   accum_wp = xprop->accum_block2[xprop_ndx];
   accum_set_ip = &(xprop->net_block2_set[xprop_ndx]);
  }
 
#ifdef __CVC_DEBUG__
 /* DBG remove --- */
 if (accum_wp == NULL) __misc_terr(__FILE__, __LINE__);
 if (xprop->net_block1_set == NULL) __misc_terr(__FILE__, __LINE__);
 /* ----- */
#endif


 /* all bits set marking */
 if (!xprop->lhs_id_only[xprop_ndx])
  {
   if (xblock == 0) setblock_mask_wp = xprop->xbitmask_block1_set[xprop_ndx];
   else setblock_mask_wp = xprop->xbitmask_block2_set[xprop_ndx];

   blen = np->nwid;
   setbits_wp = xprop->bits_set[xprop_ndx];
   setbits_wp[0] &= __masktab[ubits_(blen)];
   setblock_mask_wp[0] &= __masktab[ubits_(blen)];
  }

 /* if xblock is zero - nothing yet to combine */
 if (!(*accum_set_ip))
  {
   accum_wp[0] = aval;
   accum_wp[1] = bval;
  }
 else asl_loc_combine_xprop_accum_1w(accum_wp, aval, bval);
 np->n_xprop_accum_set = TRUE;
 *accum_set_ip = TRUE;
}

/*
 * combine the xprop accumulation value using the ?:
 * 1 word narrow version
 */
static void asl_loc_combine_xprop_accum_1w(word32 *accum_wp, word32 aval, 
 word32 bval)
{
 word32 *accum_bwp;

 accum_bwp = &(accum_wp[1]);
 /* truth table is 0-0 = 0, 1-1 = 1, else x */
 *accum_bwp = *accum_bwp | bval | (*accum_wp ^ aval);
 *accum_wp = *accum_bwp | aval;
}

/*
 *
 */
static void asl_loc_stmt_assign_to_accum_wide_id(struct net_t *np, 
 struct xprop_t *xprop, word32 *ap, word32 *bp)
{
 int32 xprop_ndx, xblock, wlen; 
 int32 *accum_set_ip;
 word32 *accum_wp, *setbits_wp, *setblock_mask_wp;

 xprop_ndx = np->n_xprop_ndx;
 xblock = xprop->xblock;
#ifdef __CVC_DEBUG__
 /* DBG remove --- */
 if (xprop_ndx < 0) __misc_terr(__FILE__, __LINE__);
 if (xprop_ndx >= xprop->ncount) __misc_terr(__FILE__, __LINE__);
 /* ----- */
#endif

 if (xblock == 0)
  {
   accum_wp = xprop->accum_block1[xprop_ndx];
   accum_set_ip = &(xprop->net_block1_set[xprop_ndx]);
  }
 else 
  {
   accum_wp = xprop->accum_block2[xprop_ndx];
   accum_set_ip = &(xprop->net_block2_set[xprop_ndx]);
  }
 
#ifdef __CVC_DEBUG__
 /* DBG remove --- */
 if (accum_wp == NULL) __misc_terr(__FILE__, __LINE__);
 if (xprop->net_block1_set == NULL) __misc_terr(__FILE__, __LINE__);
 /* ----- */
#endif


 /* all bits set marking */
 wlen = wlen_(np->nwid);
 if (!xprop->lhs_id_only[xprop_ndx])
  {
   if (xblock == 0) setblock_mask_wp = xprop->xbitmask_block1_set[xprop_ndx];
   else setblock_mask_wp = xprop->xbitmask_block2_set[xprop_ndx];

   setbits_wp = xprop->bits_set[xprop_ndx];
   memset(setbits_wp, 0xff, wlen*WRDBYTES);
   memset(setblock_mask_wp, 0xff, wlen*WRDBYTES);
  }

 /* if xblock is zero - nothing yet to combine */
 if (!(*accum_set_ip))
  {
   memcpy(accum_wp, ap, wlen*WRDBYTES);
   memcpy(&(accum_wp[wlen]), bp, wlen*WRDBYTES);
  }
 else
  {
   asl_loc_combine_xprop_accum(accum_wp, ap, bp, np->nwid);
  }
 /* set accum init flags */
 np->n_xprop_accum_set = TRUE;
 *accum_set_ip = TRUE;
}

/*
 * enter an xprop block - init xprop storage
 */
extern void __asl_set_xprop_accum_block_case(struct st_t *stp)
{
 struct xprop_t *xprop;
 int32 i, wlen;
 struct net_t *np;

 xprop = stp->st.scs.xprop;
 xprop->xblock = 0;
 /* go through each on net on the lhs init flags */ 
 xprop->x_entered = TRUE;
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];
   /* save the parent xprop net index */
   xprop->parent_net_indices[i] = np->n_xprop_ndx;
   np->n_xprop_ndx = i;
   /* init the across block setting flags */
   xprop->net_block1_set[i] = 0;
   xprop->net_block2_set[i] = 0;
   /* init the across block setting flags - per bit */
   if (!xprop->lhs_id_only[i])
    {
     wlen = wlen_(np->nwid);
     memset(xprop->bits_set[i], 0, wlen*WRDBYTES);
     memset(xprop->xbitmask_block1_set[i], 0, wlen*WRDBYTES);
     memset(xprop->xbitmask_block2_set[i], 0, wlen*WRDBYTES);
    }
  }
}

/*
 *
 */
extern void __asl_set_xprop_accum_block_if(struct st_t *stp)
{
 struct xprop_t *xprop;
 int32 i, wlen;
 struct net_t *np;

 xprop = stp->st.sif.xprop;
 xprop->xblock = 0;
 /* go through each on net on the lhs init flags */ 
 xprop->x_entered = TRUE;
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];
   /* save the parent xprop net index */
   xprop->parent_net_indices[i] = np->n_xprop_ndx;
   np->n_xprop_ndx = i;
   /* init the across block setting flags */
   xprop->net_block1_set[i] = 0;
   xprop->net_block2_set[i] = 0;
   /* init the across block setting flags - per bit */
   if (!xprop->lhs_id_only[i])
    {
     wlen = wlen_(np->nwid);
     memset(xprop->bits_set[i], 0, wlen*WRDBYTES);
     memset(xprop->xbitmask_block1_set[i], 0, wlen*WRDBYTES);
     memset(xprop->xbitmask_block2_set[i], 0, wlen*WRDBYTES);
    }
  }
}

/*
 * exit xblock - setting accum values etc
 */
extern void __asl_set_restore_xprop_accum_block(struct st_t *stp,
 int32 xblocks)
{
 struct xprop_t *xprop;

 if (stp->stmttyp == S_CASE) xprop = stp->st.scs.xprop;
 else xprop = stp->st.sif.xprop;

 asl_loc_set_restore_xprop_accum_block(xprop, xblocks);
}


/*
 * accum to self
 */
extern void __asl_set_restore_xprop_accum_toself(struct st_t *stp)
{
 struct xprop_t *xprop;

 xprop = stp->st.sif.xprop;
 asl_loc_set_restore_xprop_accum_block_selfv(xprop, FALSE);
}

/*
 * no default case wrapper
 */
extern void __asl_set_restore_xprop_accum_block_nodefault(struct st_t *stp,
 int32 num_matched, int32 xcount)
{
 int32 combine_to_self;
 struct xprop_t *xprop;

 xprop = stp->st.scs.xprop;
 xprop->xblock = (num_matched > 1);
 /* if no default and all the possible Xs are not matched just X out */
 combine_to_self = (num_matched < (1 << xcount));
 if (combine_to_self)
  {
   asl_loc_set_restore_xprop_accum_block_selfv(xprop, (num_matched > 1));
  }
 else asl_loc_set_restore_xprop_accum_block(xprop, (num_matched > 1));
}

/*
 * asl local version of set_restore_xprop_accum_block - this is known to 
 * never have to combine with self
 */
static void asl_loc_set_restore_xprop_accum_block(struct xprop_t *xprop, 
 int32 combine_blocks)
{
 int32 i, wlen, last_ndx, bi, block1_set, block2_set, wi, set_block;
 struct xprop_t *parent_xprop;
 word32 *b1wp, *b2wp, *parent_wp, *combine_wp;
 word32 *net_accum_wp, *parent_accum1_wp, *parent_accum2_wp, *accum_wp;
 word32 *setbits_wp, *parent_setbits_wp, *other_wp;
 word32 aval, bval;
 struct net_t *np;

 xprop->x_entered = FALSE;
 /* if X out no need to combine blocks */
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];

   wlen = wlen_(np->nwid);
   net_accum_wp = np->xprop_accum;
   /* case 1: lhs known to be ID set entire net */
 
   if (xprop->xblock == 0)
    {
     accum_wp = xprop->accum_block1[i];
     other_wp = xprop->accum_block2[i];
    }
   else 
    {
     accum_wp = xprop->accum_block2[i];
     other_wp = xprop->accum_block1[i];
    }

   if (combine_blocks)
    {
     asl_loc_combine_xprop_accum(accum_wp, other_wp, &(other_wp[wlen]), 
      np->nwid);
    }
   memcpy(net_accum_wp, accum_wp, 2*wlen*WRDBYTES);

   if (xprop->lhs_id_only[i])
    {
     block1_set = xprop->net_block1_set[i];
     block2_set = xprop->net_block2_set[i];

#ifdef __CVC_DEBUG__
     /* DBG remove -- */
     if (block1_set == -1) __misc_terr(__FILE__, __LINE__);
     if (block2_set == -1) __misc_terr(__FILE__, __LINE__);
     /* ---- */
#endif
     if (combine_blocks) 
      {
       if (block1_set != block2_set)
        {
         set_regtox_(net_accum_wp, &(net_accum_wp[wlen]), np->nwid);
        }
      }


     parent_xprop = xprop->parent_xprop;
     /* can have empty if block with no nets nothing to combine */
     /* if parent has not been entered there is no reason to combine it */
     if (parent_xprop != NULL && parent_xprop->x_entered)
      {
       last_ndx = xprop->parent_net_indices[i];
#ifdef __CVC_DEBUG__
       /* DBG remove -- */
       if (last_ndx > parent_xprop->ncount) __misc_terr(__FILE__, __LINE__);
       /* ---- */
#endif
       if (xprop->xblock == 0) set_block = block1_set;
       else set_block = block2_set;

       /* if never set do not set accum values */
       if (set_block)
        {
         if (parent_xprop->xblock == 0)
          {
           parent_xprop->net_block1_set[last_ndx] |= set_block;
           parent_accum1_wp = parent_xprop->accum_block1[last_ndx]; 
           memcpy(parent_accum1_wp, accum_wp, 2*wlen*WRDBYTES);
          }
         else
          {
           parent_xprop->net_block2_set[last_ndx] |= set_block;
           parent_accum2_wp = parent_xprop->accum_block2[last_ndx]; 
           memcpy(parent_accum2_wp, accum_wp, 2*wlen*WRDBYTES);
          }
        }
      }
     xprop->net_block1_set[i] = -1;
     xprop->net_block2_set[i] = -1;
    }
   /* case 2: lhs contains some selects part/bsel - need to handle per bit */
   else
    {
     b1wp = xprop->xbitmask_block1_set[i];
     b2wp = xprop->xbitmask_block2_set[i];
#ifdef __CVC_DEBUG__
     /* DBG remove -- */
     if (b1wp == NULL) __misc_terr(__FILE__, __LINE__);
     if (b2wp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
#endif
     if (combine_blocks)
      {
       /* need to set per bit values */
       for (bi = 0; bi < np->nwid; bi++)
        {
         block1_set = rhsbsel_(b1wp, bi);
         block2_set = rhsbsel_(b2wp, bi);

         if (block1_set != block2_set)
          {
           /* set just this one bit to x */
           __lhsbsel(net_accum_wp, bi, 1);
           __lhsbsel(&(net_accum_wp[wlen]), bi, 1);
          }
        }
      }

     parent_xprop = xprop->parent_xprop;
     /* can have empty if block with no nets nothing to combine */
     /* AIV 10/25/11 - this should only enter if x_entered bit set */
     if (parent_xprop != NULL && parent_xprop->x_entered)
      {
       last_ndx = xprop->parent_net_indices[i];
#ifdef __CVC_DEBUG__
       /* DBG remove -- */
       if (last_ndx > parent_xprop->ncount) __misc_terr(__FILE__, __LINE__);
       /* ---- */
#endif
  
       if (xprop->xblock == 0) combine_wp = b1wp;
       else combine_wp = b2wp;

       setbits_wp = xprop->bits_set[i];
       parent_setbits_wp = parent_xprop->bits_set[last_ndx];
       if (parent_xprop->xblock == 0)
        {
         parent_wp = parent_xprop->xbitmask_block1_set[last_ndx];
         parent_accum1_wp = parent_xprop->accum_block1[last_ndx]; 
         /* need to set per bit values */
         for (bi = 0; bi < np->nwid; bi++)
          {
           block1_set = rhsbsel_(setbits_wp, bi);
           if (block1_set)
            {
             aval = rhsbsel_(accum_wp, bi);
             bval = rhsbsel_(&(accum_wp[wlen]), bi);
             __lhsbsel(parent_accum1_wp, bi, aval);
             __lhsbsel(&(parent_accum1_wp[wlen]), bi, bval);
            }
          }
        }
       else
        {
         parent_wp = parent_xprop->xbitmask_block2_set[last_ndx];
         parent_accum2_wp = parent_xprop->accum_block2[last_ndx]; 
         for (bi = 0; bi < np->nwid; bi++)
          {
           block2_set = rhsbsel_(setbits_wp, bi);
           if (block2_set)
            {
             aval = rhsbsel_(accum_wp, bi);
             bval = rhsbsel_(&(accum_wp[wlen]), bi);
             __lhsbsel(parent_accum2_wp, bi, aval);
             __lhsbsel(&(parent_accum2_wp[wlen]), bi, bval);
            }
          }
        }
       /* combine the accumulator and the set bits */
       for (wi = 0; wi < wlen; wi++)
        {
         parent_wp[wi] |= combine_wp[wi];
         parent_setbits_wp[wi] |= setbits_wp[wi];
        }
      }
    }
   /* restore the parent net xprop index */
   np->n_xprop_ndx = xprop->parent_net_indices[i];
  }
}

/*
 * asl local version of set_restore_xprop_accum_block - this is known to 
 * have to combine with self
 */
static void asl_loc_set_restore_xprop_accum_block_selfv(struct xprop_t *xprop, 
 int32 combine_blocks)
{
 int32 i, wlen, last_ndx, bi, block1_set, block2_set, wi, set_block;
 struct xprop_t *parent_xprop;
 word32 *b1wp, *b2wp, *parent_wp, *combine_wp;
 word32 *net_accum_wp, *parent_accum1_wp, *parent_accum2_wp, *accum_wp;
 word32 *setbits_wp, *parent_setbits_wp, *other_wp, *net_wp;
 word32 aval, bval, sval;
 struct net_t *np;
 struct xstk_t *xsp;

 xprop->x_entered = FALSE;
 /* if X out no need to combine blocks */
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];

   wlen = wlen_(np->nwid);
   net_accum_wp = np->xprop_accum;
   /* case 1: lhs known to be ID set entire net */
 
   if (xprop->xblock == 0)
    {
     accum_wp = xprop->accum_block1[i];
     other_wp = xprop->accum_block2[i];
    }
   else 
    {
     accum_wp = xprop->accum_block2[i];
     other_wp = xprop->accum_block1[i];
    }

   /* AIV 02/23/12 - this must combine to its current value not set to X */
   //if (combine_to_self)
   //seperated routine known to have to combine
    {
     /* need to mark accum flag set so this will later X out */
     //AIV LOOKATME - not sure about this but if case doesn't match set to X
     /* could 'X' out all values just not setting for now */
     /*
     if (!np->n_xprop_accum_set)
      {
       np->n_xprop_accum_set = TRUE;
       xprop->net_block1_set[i] = TRUE;
       set_regtox_(accum_wp, &(accum_wp[wlen]), np->nwid); 
       goto combine;
      }
      */
     if (!np->n_xprop_accum_set) goto combine;

     np->n_xprop_accum_set = TRUE;
     xprop->net_block1_set[i] = TRUE;
     net_wp = &(__idp[np->nva_ofs]);
     /* if vector just combine into its current value */
     if (np->srep == SR_VEC)
      {
       asl_loc_combine_xprop_accum(accum_wp, net_wp, &(net_wp[wlen]), np->nwid);
      }
     /* if scalar just create word and combine */
     else if (np->srep == SR_SCAL || np->srep == SR_SSCAL)
      {
       sval = *net_wp; 
       aval = sval & 1;
       bval = (sval >> 1) & 1;
       asl_loc_combine_xprop_accum(accum_wp, &aval, &bval, 1);
      }
     else 
      {
       /* all others create a/b parts */
       push_xstk_(xsp, np->nwid);
       __ld_wire_val_wrds(xsp->ap, xsp->bp, np);
       asl_loc_combine_xprop_accum(accum_wp, xsp->ap, xsp->bp, 1);
       __pop_xstk();
      }
    }
combine:

   if (combine_blocks)
    {
     asl_loc_combine_xprop_accum(accum_wp, other_wp, &(other_wp[wlen]), np->nwid);
    }
   memcpy(net_accum_wp, accum_wp, 2*wlen*WRDBYTES);

   if (xprop->lhs_id_only[i])
    {
     block1_set = xprop->net_block1_set[i];
     block2_set = xprop->net_block2_set[i];

#ifdef __CVC_DEBUG__
     /* DBG remove -- */
     if (block1_set == -1) __misc_terr(__FILE__, __LINE__);
     if (block2_set == -1) __misc_terr(__FILE__, __LINE__);
     /* ---- */
#endif
     if (combine_blocks) 
      {
       if (block1_set != block2_set)
        {
         set_regtox_(net_accum_wp, &(net_accum_wp[wlen]), np->nwid);
        }
      }


     parent_xprop = xprop->parent_xprop;
     /* can have empty if block with no nets nothing to combine */
     /* if parent has not been entered there is no reason to combine it */
     if (parent_xprop != NULL && parent_xprop->x_entered)
      {
       last_ndx = xprop->parent_net_indices[i];
#ifdef __CVC_DEBUG__
       /* DBG remove -- */
       if (last_ndx > parent_xprop->ncount) __misc_terr(__FILE__, __LINE__);
       /* ---- */
#endif
       if (xprop->xblock == 0) set_block = block1_set;
       else set_block = block2_set;

       /* if never set do not set accum values */
       if (set_block)
        {
         if (parent_xprop->xblock == 0)
          {
           parent_xprop->net_block1_set[last_ndx] |= set_block;
           parent_accum1_wp = parent_xprop->accum_block1[last_ndx]; 
           memcpy(parent_accum1_wp, accum_wp, 2*wlen*WRDBYTES);
          }
         else
          {
           parent_xprop->net_block2_set[last_ndx] |= set_block;
           parent_accum2_wp = parent_xprop->accum_block2[last_ndx]; 
           memcpy(parent_accum2_wp, accum_wp, 2*wlen*WRDBYTES);
          }
        }
      }
     xprop->net_block1_set[i] = -1;
     xprop->net_block2_set[i] = -1;
    }
   /* case 2: lhs contains some selects part/bsel - need to handle per bit */
   else
    {
     b1wp = xprop->xbitmask_block1_set[i];
     b2wp = xprop->xbitmask_block2_set[i];
#ifdef __CVC_DEBUG__
     /* DBG remove -- */
     if (b1wp == NULL) __misc_terr(__FILE__, __LINE__);
     if (b2wp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
#endif
     if (combine_blocks)
      {
       /* need to set per bit values */
       for (bi = 0; bi < np->nwid; bi++)
        {
         block1_set = rhsbsel_(b1wp, bi);
         block2_set = rhsbsel_(b2wp, bi);

         if (block1_set != block2_set)
          {
           /* set just this one bit to x */
           __lhsbsel(net_accum_wp, bi, 1);
           __lhsbsel(&(net_accum_wp[wlen]), bi, 1);
          }
        }
      }

     parent_xprop = xprop->parent_xprop;
     /* can have empty if block with no nets nothing to combine */
     /* AIV 10/25/11 - this should only enter if x_entered bit set */
     if (parent_xprop != NULL && parent_xprop->x_entered)
      {
       last_ndx = xprop->parent_net_indices[i];
#ifdef __CVC_DEBUG__
       /* DBG remove -- */
       if (last_ndx > parent_xprop->ncount) __misc_terr(__FILE__, __LINE__);
       /* ---- */
#endif
  
       if (xprop->xblock == 0) combine_wp = b1wp;
       else combine_wp = b2wp;

       setbits_wp = xprop->bits_set[i];
       parent_setbits_wp = parent_xprop->bits_set[last_ndx];
       if (parent_xprop->xblock == 0)
        {
         parent_wp = parent_xprop->xbitmask_block1_set[last_ndx];
         parent_accum1_wp = parent_xprop->accum_block1[last_ndx]; 
         /* need to set per bit values */
         for (bi = 0; bi < np->nwid; bi++)
          {
           block1_set = rhsbsel_(setbits_wp, bi);
           if (block1_set)
            {
             aval = rhsbsel_(accum_wp, bi);
             bval = rhsbsel_(&(accum_wp[wlen]), bi);
             __lhsbsel(parent_accum1_wp, bi, aval);
             __lhsbsel(&(parent_accum1_wp[wlen]), bi, bval);
            }
          }
        }
       else
        {
         parent_wp = parent_xprop->xbitmask_block2_set[last_ndx];
         parent_accum2_wp = parent_xprop->accum_block2[last_ndx]; 
         for (bi = 0; bi < np->nwid; bi++)
          {
           block2_set = rhsbsel_(setbits_wp, bi);
           if (block2_set)
            {
             aval = rhsbsel_(accum_wp, bi);
             bval = rhsbsel_(&(accum_wp[wlen]), bi);
             __lhsbsel(parent_accum2_wp, bi, aval);
             __lhsbsel(&(parent_accum2_wp[wlen]), bi, bval);
            }
          }
        }
       /* combine the accumulator and the set bits */
       for (wi = 0; wi < wlen; wi++)
        {
         parent_wp[wi] |= combine_wp[wi];
         parent_setbits_wp[wi] |= setbits_wp[wi];
        }
      }
    }
   /* restore the parent net xprop index */
   np->n_xprop_ndx = xprop->parent_net_indices[i];
  }
}

/*
 *
 */
static void asl_loc_combine_xprop_accum(word32 *accum_wp, word32 *ap, 
 word32 *bp, int32 nwid)
{
 int32 wi, wlen, ubits;
 word32 *accum_bwp;

 wlen = wlen_(nwid);
 accum_bwp = &(accum_wp[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   /* truth table is 0-0 = 0, 1-1 = 1, else x */
   accum_bwp[wi] = accum_bwp[wi] | bp[wi] | (accum_wp[wi] ^ ap[wi]);
   accum_wp[wi] = accum_bwp[wi] | ap[wi];
  }
 ubits = ubits_(nwid);
 accum_wp[wlen - 1] &= __masktab[ubits];
 accum_bwp[wlen - 1] &= __masktab[ubits];
}

/*
 * set for or accumulate rhs - one word case
 */
extern void __asl_set_xprop_accum_init(struct net_t *np, word32 aw, word32 bw)
{
 word32 accum_aw, accum_bw;

 if (!np->n_xprop_accum_set)
  {
   np->n_xprop_accum_set = TRUE;
   np->xprop_accum[0] = aw;
   np->xprop_accum[1] = bw;
  }
 else
  {
   accum_aw = np->xprop_accum[0];
   accum_bw = np->xprop_accum[1];
   accum_bw = accum_bw | bw | (accum_aw ^ aw);
   accum_aw = accum_bw | aw;
   np->xprop_accum[0] = accum_aw;
   np->xprop_accum[1] = accum_bw;
  }
}

/*
 * set for or accumulate rhs - wide
 */
extern void __asl_set_xprop_accum_init_wide(struct net_t *np, word32 *rhswp)
{
 int32 wlen, wi, ubits;
 word32 *accum_wp, *accum_bwp, *rhs_bwp;

 wlen = wlen_(np->nwid);
 if (!np->n_xprop_accum_set)
  {
   np->n_xprop_accum_set = TRUE;
   memcpy(np->xprop_accum, rhswp, 2*wlen*WRDBYTES);
  }
 else
  {
   accum_wp = np->xprop_accum;
   accum_bwp = &(accum_wp[wlen]);
   rhs_bwp = &(rhswp[wlen]);

   for (wi = 0; wi < wlen; wi++)
    {
     /* truth table is 0-0 = 0, 1-1 = 1, else x */
     accum_bwp[wi] = accum_bwp[wi] | rhs_bwp[wi] | (accum_wp[wi] ^ rhswp[wi]);
     accum_wp[wi] = accum_bwp[wi] | rhswp[wi];
    }
   ubits = ubits_(np->nwid);
   accum_wp[wlen - 1] &= __masktab[ubits];
   accum_bwp[wlen - 1] &= __masktab[ubits];
  }
}

/*
 * combine - but if not inti must make x
 */
extern void __asl_xprop_accum_to_self(struct net_t *np, word32 aw, word32 bw)
{
 word32 accum_aw, accum_bw;

 //AIV LOOKATME - not sure about this but if case doesn't match set to X
 /* could 'X' out all values just not setting for now */
 /*
 if (!np->n_xprop_accum_set)
  {
   np->n_xprop_accum_set = TRUE;
   accum_wp = np->xprop_accum;
   set_regtox_(accum_wp, &(accum_wp[1]), np->nwid);
   return;
  }
 */
 if (np->n_xprop_accum_set)
  {
   accum_aw = np->xprop_accum[0];
   accum_bw = np->xprop_accum[1];
   accum_bw = accum_bw | bw | (accum_aw ^ aw);
   accum_aw = accum_bw | aw;
   np->xprop_accum[0] = accum_aw;
   np->xprop_accum[1] = accum_bw;
  }
}

/*
 * combine - but if not init must make x
 */
extern void __asl_xprop_accum_to_self_wide(struct net_t *np, word32 *rhswp)
{
 int32 wlen, wi, ubits;
 word32 *accum_wp, *accum_bwp, *rhs_bwp;

 wlen = wlen_(np->nwid);
 accum_wp = np->xprop_accum;
 //AIV LOOKATME - not sure about this but if case doesn't match set to X
 /* could 'X' out all values just not setting for now */
/*
 if (!np->n_xprop_accum_set)
  {
   np->n_xprop_accum_set = TRUE;
   set_regtox_(accum_wp, &(accum_wp[wlen]), np->nwid);
  }
 else
*/
 if (np->n_xprop_accum_set)
  {
   accum_bwp = &(accum_wp[wlen]);
   rhs_bwp = &(rhswp[wlen]);

   for (wi = 0; wi < wlen; wi++)
    {
     /* truth table is 0-0 = 0, 1-1 = 1, else x */
     accum_bwp[wi] = accum_bwp[wi] | rhs_bwp[wi] | (accum_wp[wi] ^ rhswp[wi]);
     accum_wp[wi] = accum_bwp[wi] | rhswp[wi];
    }
   ubits = ubits_(np->nwid);
   accum_wp[wlen - 1] &= __masktab[ubits];
   accum_bwp[wlen - 1] &= __masktab[ubits];
  }
}

/*
 *
 */
extern word32 *__asl_xprop_xedge_net(struct st_t *stp)
{
 word32 save_val, setval;
 word32 *net_wp;
 int32 inum;
 struct xprop_t *xprop;
 struct net_t *np;

 xprop = stp->st.sif.xprop;
 inum = get_inum_();
 np = xprop->xedge_nets[inum];
 if (np == NULL) return(NULL);
   
 xprop->xedge_nets[inum] = NULL;
 setval = xprop->xedge_to_vals[inum];
#ifdef __CVC_DEBUG__
 /* DBG remove --- */
 if (np->srep != SR_SCAL && np->srep != SR_SSCAL) 
    __misc_terr(__FILE__, __LINE__);
 if (setval == XPROP_XEDGE_NOT_SET) __misc_terr(__FILE__, __LINE__);
 /* ----- */
#endif

 net_wp = &(__idp[np->nva_ofs]);
 save_val = *net_wp;
 *net_wp = setval;

 /* AIV LOOKATME BEWARE - machine dependent - but most of bbgen3 is as well */
#ifdef __CVC32__
 __asm__ ("movl %0, %%ecx" : : "g" (save_val));
#else
 __asm__ ("movq %0, %%rcx" : : "g" (save_val));
#endif
 return(net_wp);
}

/*
 *
 */
extern void __asl_xprop_set_xedge_net(struct st_t *stp, struct net_t *np, 
 word32 e_val)
{
 struct xprop_t *xprop;
 int32 inum;

 inum = get_inum_();
 xprop = stp->st.sif.xprop;
 xprop->xedge_nets[inum] = np;
 xprop->xedge_to_vals[inum] = e_val;
}




//AIV XPROP - could inline this as well
/*
 * get xprop accum pointer NULL if not set
 */
extern word32 *__asl_get_xprop_accum(struct net_t *np)
{
 if (np->n_xprop_accum_set) 
  {
   np->n_xprop_accum_set = FALSE;
   return(np->xprop_accum);
  }
 return(NULL);
}

/*
 * do the per bit accumulation
 */
extern int32 __asl_per_bit_xprop_accum(struct st_t *stp, int32 ndx, word32 *wp)
{
 struct net_t *np;
 word32 *accum_wp, *setbits_wp, *accum_bwp, *wbp;
 int32 wlen, bi, accum_aval, accum_bval, bitset;
 struct xprop_t *xprop;

 if (stp->stmttyp == S_CASE) xprop = stp->st.scs.xprop;
 else xprop = stp->st.sif.xprop;

 np = xprop->lhsnets[ndx];
 /* if none set just return FALSE */
 if (!np->n_xprop_accum_set) return(FALSE);

 np->n_xprop_accum_set = FALSE;
 /* per bit needs to check if each bit is set */
 accum_wp = np->xprop_accum;
 /* copy in current net value */
//AIV XPROP - have the compiler do this - prior to passing in
 wlen = wlen_(np->nwid);
 wbp = &(wp[wlen]);
 __ld_wire_val_wrds(wp, wbp, np);

 accum_bwp = &(accum_wp[wlen]);
 setbits_wp = xprop->bits_set[ndx];

 bitset = FALSE;
 /* for each bit set place into xsp value */
 for (bi = 0; bi < np->nwid; bi++)
  {
   if (rhsbsel_(setbits_wp, bi))
    {
     bitset = TRUE;
     accum_aval = rhsbsel_(accum_wp, bi);
     __lhsbsel(wp, bi, accum_aval);
     accum_bval = rhsbsel_(accum_bwp, bi);
     __lhsbsel(wbp, bi, accum_bval);
    }
  }
 return(bitset);
}

/*
 * emit trace one word
 */
extern void __asl_trace_xprop_write(struct st_t *stp, word32 aval,
 word32 bval, int32 blen)
{
 __trace_xprop_stmt_write(stp, &aval, &bval, blen);
}


/*
 * emit trace wide
 */
extern void __asl_trace_xprop_write_wide(struct st_t *stp, word32 *ap,
 word32 *bp, int32 blen)
{
 __trace_xprop_stmt_write(stp, ap, bp, blen);
}

/*
 * wide pop (bit) count
 */
extern int32 __asl_popcount_wide(word32 *wp, int32 wlen)
{
 int32 i, count;

 count = 0;
 for (i = 0; i < wlen; i++)
  {
   count += __builtin_popcountl(wp[i]);
  }
 return(count);
}

#endif

/* 
 * long binary bit xnor 
 */
extern void __asl_wid_bin_bitxnor(word32 *resap, word32 *op1ap, word32 *op2ap,
 int32 blen)
{
 int32 wlen;
 int32 wi;
 word32 *op1bp, *op2bp, *resbp;

 wlen = wlen_(blen);
 op1bp = &(op1ap[wlen]);
 op2bp = &(op2ap[wlen]);
 resbp = &(resap[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   if ((op1bp[wi] | op2bp[wi]) == 0L)
    { resbp[wi] = 0L; resap[wi] = ~(op1ap[wi] ^ op2ap[wi]); }
   else
    {
     resbp[wi] = op1bp[wi] | op2bp[wi];
     /* AIV 11/27/06 - wasn't using correct logic */
     resap[wi] = resbp[wi] | ~(op1ap[wi] ^ op2ap[wi]);
    }
  }
 resap[wlen - 1] &= __masktab[ubits_(blen)];
}

/* 
 * long binary bit xnor 
 */
extern void __asl_wid_bin_bitxnor_2state(word32 *resap, word32 *op1ap, 
 word32 *op2ap, int32 blen)
{
 int32 wlen, wi;

 wlen = wlen_(blen);
 for (wi = 0; wi < wlen; wi++)
  {
   resap[wi] = ~(op1ap[wi] ^ op2ap[wi]);
  }
 resap[wlen - 1] &= __masktab[ubits_(blen)];
}

/* 
 * long binary bit or 
 */
extern void __asl_wid_bin_bitor(word32 *resap, word32 *op1ap, word32 *op2ap,
 int32 blen)
{
 int32 wlen, wi;
 word32 *op1bp, *op2bp, *resbp;

 wlen = wlen_(blen);
 op1bp = &(op1ap[wlen]);
 op2bp = &(op2ap[wlen]);
 resbp = &(resap[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   if ((op1bp[wi] | op2bp[wi]) == 0L)
    { resbp[wi] = 0L; resap[wi] = op1ap[wi] | op2ap[wi]; }
   else
    {
     resbp[wi] = op2bp[wi] ^ op1bp[wi] ^ ((op1ap[wi] | op1bp[wi])
      & (op2bp[wi] | (op2ap[wi] & op1bp[wi])));
     resap[wi] = resbp[wi] | op2ap[wi] | op1ap[wi];
    }
  }
 /* AIV 11/08/06 - need the mask here */
 resap[wlen - 1] &= __masktab[ubits_(blen)];
 resbp[wlen - 1] &= __masktab[ubits_(blen)];
}

/* 
 * long unary bit or 
 */
extern int32 __asl_wid_un_redor(word32 *op1ap, int32 blen)
{
 int32 wlen, wi;
 word32 *op1bp;

 wlen = wlen_(blen);
 op1bp = &(op1ap[wlen]);

 /* if even 1 1 and no x/z bits, reduction and will turn to 1 */
 if (vval_is0_(op1bp, blen))
  {
   if (!vval_is0_(op1ap, blen)) return(1);
   else return(0);
  }

 for (wi = 0; wi < wlen; wi++)
  {
   /* if a bit is 1 and b bit is 0, have the one needed 1 */
   if ((op1ap[wi] & ~op1bp[wi]) != 0L)
    { 
     return(1); 
    }
  }
 /* did not find a 1, must be x */
 return(3);
}

/*
 * wide bit and wrapper
 */
extern void __asl_wid_unbitnot(word32 *res, word32 *op1ap, int32 blen)
{
 int32 wi, wlen;
 word32 *op1bp;

 wlen = wlen_(blen);
 op1bp = &(op1ap[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   res[wi] = (~op1ap[wi] | op1bp[wi]);
   /* b value remains unchanged */
  }
 res[wlen - 1] &= __masktab[ubits_(blen)];
}

/*
 * 2-state version
 */
extern void __asl_wid_unbitnot_2state(word32 *res, word32 *op1ap, int32 blen)
{
 int32 wi, wlen;

 wlen = wlen_(blen);
 for (wi = 0; wi < wlen; wi++)
  {
   res[wi] = ~op1ap[wi];
   /* b value remains unchanged */
  }
 res[wlen - 1] &= __masktab[ubits_(blen)];
}

/*
 * wide bit or wrapper
 */
extern void __asl_wide_bitor(word32 *res, word32 *op1, word32 *op2,
 int32 wlen)
{
 int32 i;

 for (i = 0; i < wlen; i++)
  {
   res[i] = op1[i] | op2[i];
  }
}

/*
 * asm lib routine for wide casez select where neither operand has a b part
 * return 0 if match (same) else 1
 */
extern int32 __asl_widomitxz_ne(word32 *op1ap, word32 *op2ap, int32 wlen)
{
 int32 i; 
 word32 xzmask;
 word32 *op1bp, *op2bp;
 
 /* AIV - better to get bpart this way as long as this is a wrapper */
 op1bp = &(op1ap[wlen]);
 op2bp = &(op2ap[wlen]);
 for (i = wlen - 1; i >= 0; i--)
  {
   xzmask = op1bp[i] | op2bp[i];
   /* return opposite T/F values so assem can use testl jump on 0 */
   if ((op1ap[i] | xzmask) != (op2ap[i] | xzmask)) return(0);
  }
 return(1);
}

/*
 * divide by zero error message - only used with __real_warns is on
 */
extern void __asl_real_div0_warning(struct st_t *stp)
{
 int32 save_fndx, save_lineno;

 /* set the stmt file and line numbers */
 save_fndx = __sfnam_ind;
 save_lineno = __slin_cnt;
 __sfnam_ind = stp->stfnam_ind;
 __slin_cnt = stp->stlin_cnt;
 __sgfwarn(641, "real divide by zero results in NaN"); 
 __sfnam_ind = save_fndx;
 __slin_cnt = save_lineno;
}

/*
 * xz ? 1.0 : 2.0 - only used with __real_warns is on
 */
extern void __asl_real_qcol_warning(struct st_t *stp)
{
 int32 save_fndx, save_lineno;

 /* set the stmt file and line numbers */
 save_fndx = __sfnam_ind;
 save_lineno = __slin_cnt;
 __sfnam_ind = stp->stfnam_ind;
 __slin_cnt = stp->stlin_cnt;
 __sgferr(730,
     "?: operator select condition x/z but values are real - 0.0 returned");
 __sfnam_ind = save_fndx;
 __slin_cnt = save_lineno;
}

/*
 * 2-state pow signed function - same as __sgn_lpow with b part removed
 */
extern int32 __asl_sgn_lpow_2state(word32 *res, word32 *op1, word32 *op2, 
 int32 blen)
{
 int32 wlen, is_odd, nbytes;
 int32 op1_is_neg, op2_is_neg, has_sign;
 word32 *twp, *twp2, *twp3, *posop1, *posop2;
 struct xstk_t *xsp_twp, *xsp_twp2, *xsp_twp3, *xsp_posop1, *xsp_posop2;

 wlen = wlen_(blen);
 /* set result to 1 */
 memset(res, 0, wlen*WRDBYTES);
 res[0] = 1;

 nbytes = wlen*WRDBYTES;
 /* check if negative values if so make positive */
 op1_is_neg = __is_lnegative(op1, blen);
 if (op1_is_neg) 
  {
   push_xstk_(xsp_posop1, blen);
   posop1 = xsp_posop1->ap;
   __cp_lnegate(posop1, op1, blen);
  }
 else posop1 = op1;

 op2_is_neg = __is_lnegative(op2, blen);
 if (op2_is_neg) 
  {
   push_xstk_(xsp_posop2, blen);
   posop2 = xsp_posop2->ap;
   __cp_lnegate(posop2, op2, blen);
  }
 else posop2 = op2;

 has_sign = FALSE;
 /* case 1: op2 is negative */
 if (op2_is_neg)
  {
   /* both negative op2 < 0 && op < 0 */
   if (op1_is_neg)
    {
     /* if op1 is -1 result is -1 if op2 is odd 1 if even */
     /* -1 must have all bits 1 since it is extended then cast so == 1 */
     /* low word is 1 and rest of words must be zero to be one */
     if (posop1[0] == 1 && __wide_vval_is0(&(posop1[1]), blen-WBITS)) 
      {
       /* if odd -1 */
       if (posop2[0] & 1) one_allbits_(res, blen);
       /* if even result is one (already set to 1 here) */
       __pop_xstk();
       __pop_xstk();
       return(FALSE);
      }
     /* both negative op2 < 0 && op < 0 && op != -1*/
     res[0] = 0; 
     __pop_xstk();
     __pop_xstk();
     return(FALSE);
    }
   /* if op2 neg and op1 == 0 result is 'bx */  
   else if (__wide_vval_is0(posop1, blen)) 
    {
//AIV 2STATE - change result 'x to be 0
     res[0] = 0;
     /* only place returns true because result is x */
     __pop_xstk();
     return(TRUE);
    }
   /* if op2 neg and op1 positive result is 0 */  
   else res[0] = 0;
   __pop_xstk();
   return(FALSE);
  }
 /* case 2: op1 is negative */
 else if (op1_is_neg)
  {
   /* if op1 is -1 result is -1 if op2 is odd 1 if even */
   /* -1 must have all bits 1 since it is extended then cast so == 1 */
   if (posop1[0] == 1 && __wide_vval_is0(&(posop1[1]), blen-WBITS)) 
    {
     /* if odd -1 */
     if (posop2[0] & 1) one_allbits_(res, blen);
     /* if even result is one (already set to 1 here) */
     __pop_xstk();
     return(FALSE);
    }
   /* op1 is neg may need to change sign if op2 is odd */
   else 
    {
     /* if odd must negate the result */
     if (posop2[0] & 1) has_sign = TRUE;
     else has_sign = FALSE; 
    }
  }
 /* if both not signed will fall though and do regular power */
 /* since posop1 and posop2 values are still their original values */
 push_xstk_(xsp_twp, blen);
 push_xstk_(xsp_twp2, blen);
 push_xstk_(xsp_twp3, blen);
 /* AIV 04/25/07 - was mallocing wrong that caused memory leak */
 twp = xsp_twp->ap;
 twp2 = xsp_twp2->ap;
 twp3 = xsp_twp3->ap;
 /* twp2 = posop2 */
 memcpy(twp2, posop2, nbytes);
 /* twp3 = op1 */
 memcpy(twp3, posop1, nbytes);
 for (;;)
  {
   /* check if odd */
   is_odd = twp2[0] & 1;
   /* divide twp2 by 2 */
   __mwrshift(twp2, 1, blen);
   if (is_odd)
    {
     /* multiply twp3 with the result */
     __lmult(twp, res, twp3, blen);
     /* copy since mult result cannot be the same as operands */
     memcpy(res, twp, nbytes);
     /* if (eventually) zero free and return - result is in res */
     if (__wide_vval_is0(twp2, blen)) 
      {
       /* if has sign must make value negative */
       if (has_sign) __inplace_lnegate(res, blen);
       /* if malloc regions (op1/op2 has sign) must free */
       if (op1_is_neg) __pop_xstk();
       if (op2_is_neg) __pop_xstk();
       __pop_xstk();
       __pop_xstk();
       __pop_xstk();
       return(FALSE);
      }
    }
   /* twp3 = twp3*twp3 */
   __lmult(twp, twp3, twp3, blen);
  /* copy since mult result cannot be the same as operands */
   memcpy(twp3, twp, nbytes);
  }
 __misc_terr(__FILE__, __LINE__);
}

/* 
 * make high bits all 1 (aka negative)
 * needed for >>>
 * AIV FIXME - lower this
 */
extern void __asl_sgnmask(word32 *valwp, word32 shiftval, int32 blen)
{
 int32 nblen, bi, wi, mask_blen;

 nblen = blen - shiftval;
 /* set 1 bits for wi+1 to end and high bits in wi word32 */
 bi = get_bofs_(nblen);
 wi = get_wofs_(nblen); 
 if (bi != 0)
  {
   valwp[wi] |= (__masktab[WBITS - bi] << bi);
   mask_blen = shiftval - (WBITS - bi);
   /* AIV 08/04/06 - if mask blen is 0 don't mask */
   if (mask_blen != 0)
     one_allbits_(&(valwp[wi + 1]), shiftval - (WBITS - bi));
  }
 else one_allbits_(&(valwp[wi]), shiftval);
}

extern void __asl_mdprt_bsel(struct expr_t *up_lhsx, word32 *lhs_ap,
 word32 new_val)
{
 struct net_t *up_np;
 word32 mask;
 word32 *lhs_bp;
 int32 bi, wi, biti;

 up_np = up_lhsx->lu.x->lu.sy->el.enp;
 lhs_bp = &(lhs_ap[wlen_(up_np->nwid)]);
 biti = __contab[up_lhsx->ru.x->ru.xvi];

 wi = get_wofs_(biti);
 bi = get_bofs_(biti);

 mask = ~(1UL << bi);
 lhs_ap[wi] &= mask;
 lhs_ap[wi] |= ((new_val & 1L) << bi);

 lhs_bp[wi] &= mask;
 lhs_bp[wi] |= (((new_val >> 1) & 1L) << bi);
}

extern void __asl_mdprt_bsel_1w(int32 bi, word32 *lhs_ap, word32 new_val)
{
 word32 mask;
 word32 *lhs_bp;

 mask = ~(1UL << bi);
 *lhs_ap &= mask;
 *lhs_ap |= ((new_val & 1L) << bi);

 lhs_bp = &(lhs_ap[1]);
 *lhs_bp &= mask;
 *lhs_bp |= (((new_val >> 1) & 1L) << bi);
}

extern void __asl_mdprt_bsel_nchg(struct expr_t *up_lhsx, word32 *lhs_ap,
 word32 new_val, struct nchglst_t *nchglp)
{
 struct net_t *up_np;
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;
 int32 bi, wi, biti;

 up_np = up_lhsx->lu.x->lu.sy->el.enp;
 lhs_bp = &(lhs_ap[wlen_(up_np->nwid)]);
 biti = __contab[up_lhsx->ru.x->ru.xvi];

 wi = get_wofs_(biti);
 bi = get_bofs_(biti);
#ifdef __CVC_DEBUG__
 if (nchglp == NULL) __misc_terr(__FILE__, __LINE__);
#endif

 owrd = lhs_ap[wi];
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_ap[wi] = nwrd;
   lhs_bp[wi] &= mask;
   lhs_bp[wi] |= (((new_val >> 1) & 1L) << bi);
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }

 owrd = lhs_bp[wi];
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_bp[wi] = nwrd;
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }
}

extern void __asl_mdprt_bsel_nchg_1w(int32 bi, word32 *lhs_ap, word32 new_val,
  struct nchglst_t *nchglp)
{
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;

#ifdef __CVC_DEBUG__
 if (nchglp == NULL) __misc_terr(__FILE__, __LINE__);
#endif

 owrd = *lhs_ap;
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 lhs_bp = &(lhs_ap[1]);
 if (nwrd != owrd)
  {
   *lhs_ap = nwrd;
   *lhs_bp &= mask;
   *lhs_bp |= (((new_val >> 1) & 1L) << bi);
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }

 owrd = *lhs_bp;
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   *lhs_bp = nwrd;
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }
}

extern void __asl_mdprt_bsel_dmpv(struct expr_t *up_lhsx, word32 *lhs_ap,
 word32 new_val)
{
 struct net_t *up_np;
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;
 int32 bi, wi, biti;

 up_np = up_lhsx->lu.x->lu.sy->el.enp;
 lhs_bp = &(lhs_ap[wlen_(up_np->nwid)]);
 biti = __contab[up_lhsx->ru.x->ru.xvi];

 wi = get_wofs_(biti);
 bi = get_bofs_(biti);

 owrd = lhs_ap[wi];
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_ap[wi] = nwrd;
   lhs_bp[wi] &= mask;
   lhs_bp[wi] |= (((new_val >> 1) & 1L) << bi);
   asl_loc_add_dmpv_chglst_el_mdprt(up_np);
   return;
  }

 owrd = lhs_bp[wi];
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_bp[wi] = nwrd;
   asl_loc_add_dmpv_chglst_el_mdprt(up_np);
   return;
  }
}

extern void __asl_mdprt_bsel_1w_dmpv(int32 bi, word32 *lhs_ap, word32 new_val,
 struct net_t *up_np)
{
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;

 owrd = *lhs_ap;
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 lhs_bp = &(lhs_ap[1]);
 if (nwrd != owrd)
  {
   *lhs_ap = nwrd;
   *lhs_bp &= mask;
   *lhs_bp |= (((new_val >> 1) & 1L) << bi);
   asl_loc_add_dmpv_chglst_el_mdprt(up_np);
   return;
  }

 owrd = *lhs_bp;
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   *lhs_bp = nwrd;
   asl_loc_add_dmpv_chglst_el_mdprt(up_np);
   return;
  }
}

extern void __asl_mdprt_bsel_nchg_dmpv(struct expr_t *up_lhsx, word32 *lhs_ap,
 word32 new_val, struct nchglst_t *nchglp)
{
 struct net_t *up_np;
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;
 int32 bi, wi, biti;

 up_np = up_lhsx->lu.x->lu.sy->el.enp;
 lhs_bp = &(lhs_ap[wlen_(up_np->nwid)]);
 biti = __contab[up_lhsx->ru.x->ru.xvi];

 wi = get_wofs_(biti);
 bi = get_bofs_(biti);
#ifdef __CVC_DEBUG__
 if (nchglp == NULL) __misc_terr(__FILE__, __LINE__);
#endif

 owrd = lhs_ap[wi];
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_ap[wi] = nwrd;
   lhs_bp[wi] &= mask;
   lhs_bp[wi] |= (((new_val >> 1) & 1L) << bi);
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   asl_loc_add_dmpv_chglst_el_mdprt(up_np);
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }

 owrd = lhs_bp[wi];
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_bp[wi] = nwrd;
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   asl_loc_add_dmpv_chglst_el_mdprt(up_np);
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }
}

extern void __asl_mdprt_bsel_nchg_1w_dmpv(int32 bi, word32 *lhs_ap, 
 word32 new_val, struct nchglst_t *nchglp, struct net_t *up_np)
{
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;

#ifdef __CVC_DEBUG__
 if (nchglp == NULL) __misc_terr(__FILE__, __LINE__);
#endif

 owrd = *lhs_ap;
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 lhs_bp = &(lhs_ap[1]);
 if (nwrd != owrd)
  {
   *lhs_ap = nwrd;
   *lhs_bp &= mask;
   *lhs_bp |= (((new_val >> 1) & 1L) << bi);
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   asl_loc_add_dmpv_chglst_el_mdprt(up_np);
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }

 owrd = *lhs_bp;
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   *lhs_bp = nwrd;
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   asl_loc_add_dmpv_chglst_el_mdprt(up_np);
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }
}


/*
 * 
 *  AIV 08/18/09 - these next four same as previous four _dmpv version
 *  except are for dumpports - just call to 
 *   __asl_add_dmpp_chglst_el_mdprt(up_np);
 */

extern void __asl_mdprt_bsel_dmpp(struct expr_t *up_lhsx, word32 *lhs_ap,
 word32 new_val)
{
 struct net_t *up_np;
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;
 int32 bi, wi, biti;

 up_np = up_lhsx->lu.x->lu.sy->el.enp;
 lhs_bp = &(lhs_ap[wlen_(up_np->nwid)]);
 biti = __contab[up_lhsx->ru.x->ru.xvi];

 wi = get_wofs_(biti);
 bi = get_bofs_(biti);

 owrd = lhs_ap[wi];
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_ap[wi] = nwrd;
   lhs_bp[wi] &= mask;
   lhs_bp[wi] |= (((new_val >> 1) & 1L) << bi);
    __asl_add_dmpp_chglst_el_mdprt(up_np);
   return;
  }

 owrd = lhs_bp[wi];
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_bp[wi] = nwrd;
   __asl_add_dmpp_chglst_el_mdprt(up_np);
   return;
  }
}

extern void __asl_mdprt_bsel_1w_dmpp(int32 bi, word32 *lhs_ap, word32 new_val,
 struct net_t *up_np)
{
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;

 owrd = *lhs_ap;
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 lhs_bp = &(lhs_ap[1]);
 if (nwrd != owrd)
  {
   *lhs_ap = nwrd;
   *lhs_bp &= mask;
   *lhs_bp |= (((new_val >> 1) & 1L) << bi);
   __asl_add_dmpp_chglst_el_mdprt(up_np);
   return;
  }

 owrd = *lhs_bp;
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   *lhs_bp = nwrd;
   __asl_add_dmpp_chglst_el_mdprt(up_np);
   return;
  }
}

extern void __asl_mdprt_bsel_nchg_dmpp(struct expr_t *up_lhsx, word32 *lhs_ap,
 word32 new_val, struct nchglst_t *nchglp)
{
 struct net_t *up_np;
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;
 int32 bi, wi, biti;

 up_np = up_lhsx->lu.x->lu.sy->el.enp;
 lhs_bp = &(lhs_ap[wlen_(up_np->nwid)]);
 biti = __contab[up_lhsx->ru.x->ru.xvi];

 wi = get_wofs_(biti);
 bi = get_bofs_(biti);
#ifdef __CVC_DEBUG__
 if (nchglp == NULL) __misc_terr(__FILE__, __LINE__);
#endif

 owrd = lhs_ap[wi];
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_ap[wi] = nwrd;
   lhs_bp[wi] &= mask;
   lhs_bp[wi] |= (((new_val >> 1) & 1L) << bi);
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   __asl_add_dmpp_chglst_el_mdprt(up_np);
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }

 owrd = lhs_bp[wi];
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   lhs_bp[wi] = nwrd;
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   __asl_add_dmpp_chglst_el_mdprt(up_np);
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }
}

extern void __asl_mdprt_bsel_nchg_1w_dmpp(int32 bi, word32 *lhs_ap, 
 word32 new_val, struct nchglst_t *nchglp, struct net_t *up_np)
{
 word32 owrd, nwrd, mask;
 word32 *lhs_bp;

#ifdef __CVC_DEBUG__
 if (nchglp == NULL) __misc_terr(__FILE__, __LINE__);
#endif

 owrd = *lhs_ap;
 nwrd = owrd;
 mask = ~(1UL << bi);
 nwrd &= mask;
 nwrd |= ((new_val & 1L) << bi);
 lhs_bp = &(lhs_ap[1]);
 if (nwrd != owrd)
  {
   *lhs_ap = nwrd;
   *lhs_bp &= mask;
   *lhs_bp |= (((new_val >> 1) & 1L) << bi);
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   __asl_add_dmpp_chglst_el_mdprt(up_np);
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }

 owrd = *lhs_bp;
 nwrd = owrd;
 nwrd &= mask;
 nwrd |= (((new_val >> 1) & 1L) << bi);
 if (nwrd != owrd)
  {
   *lhs_bp = nwrd;
   /* no there is no mipd here so just inline asl_loc_add_static_nchglst */
   __asl_add_dmpp_chglst_el_mdprt(up_np);
   nchglp->triggered = TRUE;
   nchglp->nchglnxt = NULL;
   __nchg_futend->nchglnxt = nchglp; 
   __nchg_futend = nchglp; 
   return;
  }
}

/*
 * setup a task thread for a task that does not have outputs
 *
 * same as interpreter and same as namblk except for how task accessed
 *
 * task added to thread tree as if going to be scheduled but then execed
 * immediately
 */
extern void __asl_setup_task_thd(struct st_t *stp, struct st_t *nxtstp)
{
 struct task_t *tskp;
 struct tskcall_t *tkcp;
 struct expr_t *tkxp;
 struct thread_t *thp;

 tkcp = &(stp->st.stkc);
 tkxp = tkcp->tsksyx;
 tskp = tkxp->lu.sy->el.etskp;

 __cur_thd->thofscnt = 1;
 __cur_thd->thnxtstp = nxtstp;

 thp = __setup_tsk_thread(tskp);

 thp->thpar = __cur_thd;
 __cur_thd->thofs = thp;
 __cur_thd = thp;
 /* for XMR thread, vinsn to set XMR definition i.e. already executed */
 __cur_thd->th_idp = __idp;
}

/*
 * automatic version - same as above except it saves idp area
 * in th_save_idp - to be restores later
 */
extern void __asl_setup_task_thd_auto(struct st_t *stp, struct st_t *nxtstp,
 t_midat *saved_idp)
{
 struct task_t *tskp;
 struct tskcall_t *tkcp;
 struct expr_t *tkxp;
 struct thread_t *thp;

 tkcp = &(stp->st.stkc);
 tkxp = tkcp->tsksyx;
 tskp = tkxp->lu.sy->el.etskp;

 __cur_thd->thofscnt = 1;
 __cur_thd->thnxtstp = nxtstp;

 thp = __setup_tsk_thread(tskp);

 thp->thpar = __cur_thd;
 __cur_thd->thofs = thp;
 __cur_thd = thp;
 /* save non-automatic (tmp) idp area */
 thp->th_save_idp = saved_idp;
 /* for XMR thread, vinsn to set XMR definition i.e. already executed */
 thp->th_idp = __idp;
}

/*
 * code to clean up new thread tree leaf to run task in
 *
 * must setup in case task disabled, this code only runs if not
 * disabled
 */
extern int32 __asl_tskdone_cleanup_ret(void)
{
 int32 sav_ndx;
 struct thread_t *parthp;

 sav_ndx = __cur_thd->thd_ret_lab_ndx;
 parthp = __cur_thd->thpar;
 __thrd_done_cleanup(parthp);
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 /* DBG remove -- */
 if (parthp->thofscnt > 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
#endif
 parthp->thofs = NULL;
 __cur_thd = parthp;
 return(sav_ndx);
}

/*
 * automatic task must return cannot free automatic malloc area
 * until after task outputs have been assigned  - so separated out routines
 * AIV LOOKATME - inline
 */
extern int32 __asl_tskdone_cleanup_ret_auto(void)
{
 int32 sav_ndx;
 sav_ndx = __cur_thd->thd_ret_lab_ndx;
 return(sav_ndx);
}

/*
 * do the thread free and possible auto area and return save idp area
 */
extern t_midat *__asl_thread_auto_cleanup(void)
{
 t_midat *save_idp;
 struct thread_t *parthp;

 parthp = __cur_thd->thpar;
 save_idp =__cur_thd->th_save_idp;
 __thrd_done_cleanup_auto(parthp);
 __idp = save_idp;
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 /* DBG remove -- */
 if (parthp->thofscnt > 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
#endif
 parthp->thofs = NULL;
 __cur_thd = parthp;
 return(save_idp);
}

/*
 * ASM LIB ROUTINES FOR COMPARE OPERATIONS 
 */

/*
 * regular compare return value and caller sets jmp types in v_x86gen 
 */
extern int32 __asl_wide_cmp(word32 *op1p, word32 *op2p, int32 wlen, int32 cc)
{
 int32 wi, cmp, rval;

 cmp = 0;
 /* know unused parts of high words will both be zero */
 for (wi = wlen; wi >= 0; wi--)
  {
   if (op1p[wi] != op2p[wi])
    { 
     if (op1p[wi] < op2p[wi]) cmp = -1; 
     else cmp = 1; 
     break;  
    }
  }

  /* get truth value base on conditon code */
 rval = 0;
 switch (cc) {
  case CC_JGE: rval = (cmp >= 0); break;
  case CC_JGT: rval = (cmp > 0); break;
  case CC_JLE: rval = (cmp <= 0); break;
  case CC_JLT: rval = (cmp < 0); break;
  case CC_JNE: rval = (cmp != 0); break;
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
  default: rval = 0; __case_terr(__FILE__, __LINE__);
#endif
 }
 
 /* swap value for testl case in asm */
 /* AIV LOOKATME - maybe just swap logic above  */
 rval = !rval;
 return(rval);
}

/*
 * sgn compare return value  
 * taken from __do_sgn_widecmp in v_ex2.c
 */
extern int32 __asl_sgn_wide_cmp(word32 *op1ap, word32 *op2ap, int32 opwid, 
 int32 cc)
{
 int32 i;
 int32 cmp, rval, wlen, i1, i2;

 cmp = 0;
 wlen = wlen_(opwid);
 if ((op1ap[wlen - 1] & (1UL << ubits_(opwid - 1))) != 0)
  {
   /* if op1 is negative and op2 is positive */
   if ((op2ap[wlen - 1] & (1UL << ubits_(opwid - 1))) == 0) cmp = -1;
  }
 /* op1 is positive and op2 is negative */
 else if ((op2ap[wlen - 1] & (1UL << ubits_(opwid - 1))) != 0) cmp = 1;

 /* same sign */
 if (cmp == 0)
  {
   for (i = wlen_(opwid) - 1; i >= 0; i--)
    {
     if (op1ap[i] != op2ap[i])
      {
       i1 = (sword32) op1ap[i];    
       i2 = (sword32) op2ap[i];
       if (i1 < i2) cmp = -1;
       else cmp = 1;
       /* AIV 12/22/06 - need a break interp has a return so need break here */
       break;
      }
    }
  }

 /* get truth value base on conditon code */
 rval = 0;
 switch (cc) {
  case CC_JGE: rval = (cmp >= 0); break;
  case CC_JGT: rval = (cmp > 0); break;
  case CC_JLE: rval = (cmp <= 0); break;
  case CC_JLT: rval = (cmp < 0); break;
  case CC_JNE: rval = (cmp != 0); break;
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
  default: rval = 0; __case_terr(__FILE__, __LINE__);
#endif
 }
 
 /* swap value for testl case in asm */
 /* AIV LOOKATME - maybe just swap logic above  */
 rval = !rval;
 return(rval);
}

/* 
 * compare a wide with an int
 * check for 1s in the high words after comparing the first
 */
extern int32 __asl_wide_word_cmp(word32 *op1p, word32 op2w, int32 wlen, 
 int32 cc)
{
 int32 wi;
 int32 cmp, rval;

 cmp = rval = 0;
 /* compare first word value */
 if (op1p[0] != op2w)
  {
   if (op1p[0] < op2w) cmp = -1; 
   else cmp = 1; 
  }
 /* check for bits in the remaing part of the word */
 for (wi = wlen; wi > 0; wi--)
  {
   /* op2w has to be greater than */
   if (op1p[wi] != 0)
    {
     cmp = 1;
     break;
    }
  }

 /* get truth value base on conditon code */
 switch (cc) {
  case CC_JGE: rval = (cmp >= 0); break;
  case CC_JGT: rval = (cmp > 0); break;
  case CC_JLE: rval = (cmp <= 0); break;
  case CC_JLT: rval = (cmp < 0); break;
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
  default: __case_terr(__FILE__, __LINE__);
#endif
 }
 
 /* swap value for testl case in asm */
 /* AIV LOOKATME - maybe just swap logic above  */
 rval = !rval;
 return(rval);
}

/* 
 * compare a signed wide with an int
 *
 */
extern int32 __asl_wide_sgnword_cmp(int32 op1, word32 *op2ap, int32 opwid, 
 int32 cc)
{
 int32 wi;
 int32 cmp, rval, op2sgn, i2, wlen;

 cmp = rval = op2sgn = 0;
 wlen = wlen_(opwid);
 if (op1 < 0)
  {
   /* if op1 is negative and op2 is positive */
   if ((op2ap[wlen - 1] & (1UL << ubits_(opwid - 1))) == 0)
    {
     cmp = -1;
    }
   else op2sgn = -1;
  }
 /* op1 is positive and op2 is negative */
 else if ((op2ap[wlen - 1] & (1UL << ubits_(opwid - 1))) != 0) cmp = 1;
 else op2sgn = 1;

 /* same sign */
 if (cmp == 0)
  {
   /* compare first word value */
   i2 = (sword32) op2ap[0];
   if (op1 != i2) 
    {
     if (op1 < i2) cmp = -1;
     else cmp = 1;
    }
   /* both are positive */
   if (op2sgn == 1)
    {
     for (wi = wlen_(opwid) - 1; wi > 0; wi--)
      {
       /* op2p has to be greater than */
       if (op2ap[wi] != 0)
        {
         cmp = -1;
         break;
        }
      }
    }
   /* both are negative */
   else 
    {
     for (wi = wlen_(opwid) - 1; wi > 0; wi--)
      {
       /* op2p has to be less than */
       if (op2ap[wi] != 0)
        {
         cmp = 1;
         break;
        }
      }

    }
  }

 /* get truth value base on conditon code */
 switch (cc) {
  case CC_JGE: rval = (cmp >= 0); break;
  case CC_JGT: rval = (cmp > 0); break;
  case CC_JLE: rval = (cmp <= 0); break;
  case CC_JLT: rval = (cmp < 0); break;
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
  default: __case_terr(__FILE__, __LINE__);
#endif
 }
 
 /* swap value for testl case in asm */
 /* AIV LOOKATME - maybe just swap logic above  */
 rval = !rval;
 return(rval);
}

/*
 * do wide jmpor_0 
 */
extern int32 __asl_wide_jmpor_0(word32 *op1p, word32 *op2p, int32 wlen)
{
 int32 wi;

 for (wi = wlen; wi >= 0; wi--)
  {
   /* reverse T/F return to match < WBITS case */
   if ((op1p[wi] | op2p[wi]) != 0) return(1);
  }
 return(0);
}

/*
 * do wide jmp eq 
 */
extern int32 __asl_wide_jmp_eq(word32 *op1p, word32 *op2p, int32 wlen)
{
 int32 wi;

 for (wi = wlen; wi >= 0; wi--)
  {
   /* reverse T/F return to use testl compare in v_x86gen */
   if (op1p[wi] != op2p[wi]) return(1);
  }
 return(0);
}

/*
 * do wide jmp neq 
 */
extern int32 __asl_wide_cmp_eq(word32 *op1p, word32 *op2p, int32 wlen)
{
 int32 wi;

 for (wi = wlen; wi >= 0; wi--)
  {
   if (op1p[wi] != op2p[wi]) return(0);
  }
 return(1);
}

/*
 * do wide jmp neq 
 * really the same as __asl_wide_jmp_eq - but have diff name for clarity
 */
extern int32 __asl_wide_cmp_neq(word32 *op1p, word32 *op2p, int32 wlen)
{
 int32 wi;

 for (wi = wlen; wi >= 0; wi--)
  {
   if (op1p[wi] != op2p[wi]) return(1);
  }
 return(0);
}

/*
 * AIV 09/11/08 - need a variable version for wide index psel
 * has variable width which may trim to < width at run time depending
 * on variable index value
 */
extern int32 __asl_jmp_eq_wide_var(word32 *op1p, word32 *op2p, int32 blen)
{
 int32 wlen;

 wlen = wlen_(blen);
 return(__asl_wide_jmp_eq(op1p, op2p, wlen));
}

/*
 * ASM LIB ROUTINES TO DO WIDE CONVERSIONS 
 */

/*
 * wide extend
 */
extern void __asl_sgn_xtnd_widen(word32 *dst_ap, word32 *src_ap,
 int32 oblen, int32 nblen)
{
 word32 mask, osgn_bofs;
 word32 *src_bp, *dst_bp;
 int32 nwlen, owlen, widen_amt, xtra_wbits, ival;

 nwlen = wlen_(nblen);
 /* case 2: multiword but into same number of words */
 owlen = wlen_(oblen);
 dst_bp = &(dst_ap[nwlen]);
 src_bp = &(src_ap[owlen]);

 memcpy(dst_ap, src_ap, owlen*WRDBYTES); 
 memcpy(dst_bp, src_bp, owlen*WRDBYTES); 

 /* widen amount is number of bits to set to 1 (sign extend into) */
 widen_amt = nblen - oblen; 
 /* this is position in old narrower value */
 osgn_bofs = get_bofs_(oblen - 1);
 /* xtra bits is bit num bits with high bits of sign words subtracted */
 xtra_wbits = widen_amt - (WBITS - osgn_bofs - 1);

 /* AIV 06/23/05 - special case don't check for sign if 32 bits */
 /* just cast to int and copy high part */
 if (oblen == WBITS)
  {
   ival = (int32) dst_ap[0];
   if (ival < 0) one_allbits_(&(dst_ap[owlen]), xtra_wbits);
   else zero_allbits_(&(dst_ap[owlen]), xtra_wbits);
   ival = (int32) dst_bp[0];
   if (ival < 0) one_allbits_(&(dst_bp[owlen]), xtra_wbits);
   else zero_allbits_(&(dst_bp[owlen]), xtra_wbits);
   return;
  }

 /* sign extend if sign bit on, x/z extend if sign bit x/z, else 0 extend */
 if ((dst_ap[owlen - 1] & (1UL << osgn_bofs)) != 0)
  {
   mask = __masktab[WBITS - osgn_bofs - 1] << (osgn_bofs + 1);
   /* one high bits of this word32 */
   dst_ap[owlen - 1] |= mask;
   /* then all bits of rest */
   one_allbits_(&(dst_ap[owlen]), xtra_wbits);

   /* if x/z x/z extend */
   if ((dst_bp[owlen - 1] & (1UL << osgn_bofs)) != 0)
    {
     dst_bp[owlen - 1] |= mask;
     one_allbits_(&(dst_bp[owlen]), xtra_wbits);
    } 
   /* know high bits of high old size word32 0, but 0 all new words */
   else zero_allbits_(&(dst_bp[owlen]), xtra_wbits);
   return;
  }
 /* a part sign bit off, 0 all high a part words */
 zero_allbits_(&(dst_ap[owlen]), xtra_wbits);
 if ((dst_bp[owlen - 1] & (1UL << osgn_bofs)) != 0)
  {
   mask = __masktab[WBITS - osgn_bofs - 1] << (osgn_bofs + 1);
   dst_bp[owlen - 1] |= mask;
   one_allbits_(&(dst_bp[owlen]), xtra_wbits);
   return;
  }
 /* 0 wide new high bits */
 zero_allbits_(&(dst_bp[owlen]), xtra_wbits);
}

/*
 * wide extend for 2-state same as above without bpart
 */
extern void __asl_sgn_xtnd_widen_2state(word32 *dst_ap, word32 *src_ap,
 int32 oblen, int32 nblen)
{
 word32 mask, osgn_bofs;
 int32 owlen, widen_amt, xtra_wbits, ival;

 /* case 2: multiword but into same number of words */
 owlen = wlen_(oblen);

 memcpy(dst_ap, src_ap, owlen*WRDBYTES); 

 /* widen amount is number of bits to set to 1 (sign extend into) */
 widen_amt = nblen - oblen; 
 /* this is position in old narrower value */
 osgn_bofs = get_bofs_(oblen - 1);
 /* xtra bits is bit num bits with high bits of sign words subtracted */
 xtra_wbits = widen_amt - (WBITS - osgn_bofs - 1);

 /* AIV 06/23/05 - special case don't check for sign if 32 bits */
 /* just cast to int and copy high part */
 if (oblen == WBITS)
  {
   ival = (int32) dst_ap[0];
   if (ival < 0) one_allbits_(&(dst_ap[owlen]), xtra_wbits);
   else zero_allbits_(&(dst_ap[owlen]), xtra_wbits);
   return;
  }

 /* sign extend if sign bit on, x/z extend if sign bit x/z, else 0 extend */
 if ((dst_ap[owlen - 1] & (1UL << osgn_bofs)) != 0)
  {
   mask = __masktab[WBITS - osgn_bofs - 1] << (osgn_bofs + 1);
   /* one high bits of this word32 */
   dst_ap[owlen - 1] |= mask;
   /* then all bits of rest */
   one_allbits_(&(dst_ap[owlen]), xtra_wbits);
   return;
  }
 /* a part sign bit off, 0 all high a part words */
 zero_allbits_(&(dst_ap[owlen]), xtra_wbits);
}

/*
 * copied from v_ex.c
 */
extern void __asl_exec_cause(struct st_t *stp, struct nchglst_t *nchglp)
{
 t_midat *xmr_idp;
 struct expr_t *xp;
 struct net_t *np;
 struct gref_t *grp;
 decl_idp_locals_;

 xp = stp->st.scausx;
 save_idp = NULL;
 if (xp->optyp == GLBREF)
  {
   /* idea for xmr cause is to cause an event in some other part of the */
   /* itree - by changine current itree place will match waits only in */
   /* target of cause instance */ 
   grp = xp->ru.grp;    
   xmr_idp = __xmrget_refgrp_to_targ(grp);
   set_save_idp_(xmr_idp); 
  }
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
 else if (xp->optyp != ID) __case_terr(__FILE__, __LINE__);
#endif

 /* notice even if global ref. can still get net from symbol */ 
 np = xp->lu.sy->el.enp;
 /* notice cause does nothing - just schedules trigger for each waiting */
 /* armed ectrl - so any waiting event control blocks will be activated */

 /* record cause event var change as usual, if no pending do not record */
 /* must not record or will be worse event ordering dependency */
 /* know change see if need to record - also maybe dmpvars */
 if (np->enter_dce != NULL)
  {
   __nchged_i1 = __nchged_i2 = -1;
   /* AIV 09/14/06 - if has pli access must check for dce cb */
   /* linked on to the front to the dcelst */
   /* AIV 05/13/09 - access level > 2 for call backs */
   if (np->pli_access >= 2) __asl_chk_dce_cbvc(np);
   /* AIV 01/04/07 - need to tell gcc that %esi cannot be used here */
  /* AIV 02/12/10 - OSX always adds an '_' to symbol names */
  #ifdef __CVC32__
   __asm__ ("movl __idp, %%esi" :: :"%esi");
  #else
   __asm__ ("movq __idp, %%r15" :: :"%r15");
  #endif
   (np->enter_dce)();
  }

//AIV SAME AS - if (__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0) 
 if (nchglp != NULL && !nchglp->triggered)
  {
   asl_loc_add_static_nchglst(nchglp);
  }

 /* AIV 12/06/10 - may need to add change to toggle list */
 if (np->n_has_toggle) __add_togglelst_el(np);
//AIV DUMP - AIV FIXME - should just check this bit first np->dmpv_in_src
//first the code would be better??????
//if (np->dmpv_in_src)
 if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
   == (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
  {
   __idp[np->nchgaction_ofs] &= ~(NCHG_DMPVNOTCHGED);
   __asl_add_dmpv_chglst_el(np);
  } 
 if (np->dmpp_in_src)
  {
   if ((__idp[np->nchgaction_ofs] & (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED))
     == (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED))
    {
     __idp[np->nchgaction_ofs] &= ~(NCHG_DMPP_NOTCHGED);
     __asl_add_dmpp_chglst_el(np);
    } 
  }

 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

/*
 * check for repcnt jmp 
 */
extern int32 __asl_repcnt_jmp(word32 *wp, int32 has_sign)
{
 word32 val;

 if (has_sign && (int32) wp[0] <= 0) val = 0;
 else val = wp[0];
 return(val);
}

/*
 * check if any bit 1 - used for qcol 
 */
extern int32 __asl_wide_any1(word32 *opap, word32 *opbp, int32 wlen)
{
 int32 wi;

 for (wi = wlen; wi >= 0; wi--)
  {
   /* reverse T/F return to use testl compare in v_x86gen */
   if ((opap[wi] & ~opbp[wi]) != 0) return(0);
  }
 return(1);
}

/*
 * taken from v_ex2.c:lxqcol
 */
extern void __asl_wide_qcol_comb_opands(word32 *resap, word32 *op1ap, 
 word32 *op2ap, int32 wlen)
{
 int32 wi;
 word32 *resbp, *op1bp, *op2bp;

 op1bp = &(op1ap[wlen]);
 op2bp = &(op2ap[wlen]);
 resbp = &(resap[wlen]);
 for (wi = 0; wi < wlen; wi++)
  {
   resbp[wi] = op2bp[wi] | op1bp[wi] | (op2ap[wi] ^ op1ap[wi]);
   resap[wi] = resbp[wi] | op1ap[wi];
  }
}

/*
 * check if sign bit is on
 * return 0 if T, 1 if F 
 */
extern int32 __asl_sgnbit_on(word32 *wp, int32 blen)
{
 int32 wlen, sbit, bi;

 // AIV FIXME - can just inline this all this is fixed at compile time
 wlen = wlen_(blen);
 bi = get_bofs_(blen) - 1;
 sbit = (wp[wlen - 1] & (1UL << bi));
 return(sbit);
}

/* ========================= DECL WRAPPERS FROM HERE DOWN =============== */

/*
 * ASM LIB ROUTINES FOR DECLARATIVE NPP AND MULTI-DRIVER PROCESSING
 */

/*
 * __eval_wide_wire for wire type N_WIRE, N_TRI
 */
extern void __asl_eval_wide_wire(word32 *acc_ap, word32 *drv_ap,
 word32 *drv_bp, int32 wlen)
{
 int32 wi;
 word32 *acc_bp;

 acc_bp = &(acc_ap[wlen]);
 for (wi = 0; wi < wlen; wi++)
  {
   asl_loc_eval_1w_nonstren_wire(&(acc_ap[wi]), &(acc_bp[wi]), drv_ap[wi],
    drv_bp[wi]);
  }
}

/*
 * __eval_wide_wire for wire type N_TRIAND, N_WA
 */
extern void __asl_eval_wide_wire_and(word32 *acc_ap, word32 *drv_ap,
 word32 *drv_bp, int32 wlen)
{
 int32 wi;
 word32 *acc_bp;

 acc_bp = &(acc_ap[wlen]);
 for (wi = 0; wi < wlen; wi++)
  {
   asl_loc_eval_1w_nonstren_wire_and(&(acc_ap[wi]), &(acc_bp[wi]), drv_ap[wi],
    drv_bp[wi]);
  }
}

/*
 * __eval_wide_wire for wire type N_TRIOR, N_W0
 */
extern void __asl_eval_wide_wire_or(word32 *acc_ap, word32 *drv_ap, 
 word32 *drv_bp, int32 wlen)
{
 int32 wi;
 word32 *acc_bp;

 acc_bp = &(acc_ap[wlen]);
 for (wi = 0; wi < wlen; wi++)
  {
   asl_loc_eval_1w_nonstren_wire_or(&(acc_ap[wi]), &(acc_bp[wi]), drv_ap[wi],
    drv_bp[wi]);
  }
}

/*
 * __eval_1w_nonstren for wire type N_WIRE, N_TRI
 * AIV FIXME - one word case should never pass address - this causes
 * a narrow word never to be placed in a register
 */
extern void __asl_eval_1w_nonstren_wire(word32 *resa, word32 op2a, word32 op2b)
{
 word32 zmask, donemask;
 word32 op1a, op1b;

 /* AIV 12/29/06 - NOTE bpart is resa[1] */
 op1a = resa[0];
 op1b = resa[1];
 zmask = ~((op1a ^ op2a) | (op1b ^ op2b));
 resa[0] = op1a & zmask;
 resa[1] = op1b & zmask;
 donemask = zmask;
 /* AIV 07/08/08 - better to use constant value here than __masktab[0] */
 if (donemask == ALL1W) return;

 /* next op1 z bits, use op2 bits */
 zmask = (op1a ^ op1b) & op1b; 
 /* if z in op1, value is op2 */
 resa[0] |= (op2a & zmask);
 resa[1] |= (op2b & zmask);
 donemask |= zmask;
 if (donemask == ALL1W) return;

 /* next op2 zbits, use op1 bits */
 zmask = (op2a ^ op2b) & op2b; 
 /* if z in op2, value is op2 */
 resa[0] |= op1a & zmask;
 resa[1] |= op1b & zmask;
 donemask |= zmask; 
 if (donemask == ALL1W) return;

 zmask = ~donemask;
 resa[0] |= zmask; resa[1] |= zmask;
}

/*
 * __eval_1w_nonstren for wire type N_TRIAND, N_WA
 * AIV FIXME - one word case should never pass address - this causes
 * a narrow word never to be placed in a register
 */
extern void __asl_eval_1w_nonstren_wire_and(word32 *resa, word32 op2a, 
 word32 op2b)
{
 word32 zmask, donemask;
 word32 op1a, op1b;

 /* AIV 12/29/06 - NOTE b part is resa[1] */
 op1a = resa[0];
 op1b = resa[1];
 zmask = ~((op1a ^ op2a) | (op1b ^ op2b));
 resa[0] = op1a & zmask;
 resa[1] = op1b & zmask;
 donemask = zmask;
 if (donemask == ALL1W) return;

 /* next op1 z bits, use op2 bits */
 zmask = (op1a ^ op1b) & op1b; 
 /* if z in op1, value is op2 */
 resa[0] |= (op2a & zmask);
 resa[1] |= (op2b & zmask);
 donemask |= zmask;
 if (donemask == ALL1W) return;

 /* next op2 zbits, use op1 bits */
 zmask = (op2a ^ op2b) & op2b; 
 /* if z in op2, value is op2 */
 resa[0] |= op1a & zmask;
 resa[1] |= op1b & zmask;
 donemask |= zmask; 
 if (donemask == ALL1W) return;

 zmask = ~donemask;
 resa[0] |= ((op1a | op1b) & (op2a | op2b)) & zmask;
 resa[1] |= (resa[0] & (op1b | op2b)) & zmask;
}

/*
 * __eval_1w_nonstren for wire type N_TRIOR, N_WO
 * AIV FIXME - one word case should never pass address - this causes
 * a narrow word never to be placed in a register
 */
extern void __asl_eval_1w_nonstren_wire_or(word32 *resa, word32 op2a, 
 word32 op2b)
{
 word32 zmask, donemask;
 word32 op1a, op1b;

 /* AIV 12/29/06 - NOTE b part is resa[1] */
 op1a = resa[0];
 op1b = resa[1];
 zmask = ~((op1a ^ op2a) | (op1b ^ op2b));
 resa[0] = op1a & zmask;
 resa[1] = op1b & zmask;
 donemask = zmask;
 if (donemask == ALL1W) return;

 /* next op1 z bits, use op2 bits */
 zmask = (op1a ^ op1b) & op1b; 
 /* if z in op1, value is op2 */
 resa[0] |= (op2a & zmask);
 resa[1] |= (op2b & zmask);
 donemask |= zmask;
 if (donemask == ALL1W) return;

 /* next op2 zbits, use op1 bits */
 zmask = (op2a ^ op2b) & op2b; 
 /* if z in op2, value is op2 */
 resa[0] |= op1a & zmask;
 resa[1] |= op1b & zmask;
 donemask |= zmask; 
 if (donemask == ALL1W) return;

 zmask = ~donemask;
 resa[1] |= ((op2b ^ op1b ^ ((op1a | op1b) & (op2b | (op2a & op1b)))) & zmask);
 resa[0] |= ((resa[1] | op2a | op1a) & zmask);
}

static void asl_loc_eval_1w_nonstren_wire(word32 *resa, word32 *resb,
 word32 op2a, word32 op2b)
{
 word32 zmask, donemask;
 word32 op1a, op1b;

 op1a = resa[0];
 op1b = resb[0];
 zmask = ~((op1a ^ op2a) | (op1b ^ op2b));
 resa[0] = op1a & zmask;
 resb[0] = op1b & zmask;
 donemask = zmask;
 if (donemask == ALL1W) return;

 /* next op1 z bits, use op2 bits */
 zmask = (op1a ^ op1b) & op1b; 
 /* if z in op1, value is op2 */
 resa[0] |= (op2a & zmask);
 resb[0] |= (op2b & zmask);
 donemask |= zmask;
 if (donemask == ALL1W) return;

 /* next op2 zbits, use op1 bits */
 zmask = (op2a ^ op2b) & op2b; 
 /* if z in op2, value is op2 */
 resa[0] |= op1a & zmask;
 resb[0] |= op1b & zmask;
 donemask |= zmask; 
 if (donemask == ALL1W) return;

 zmask = ~donemask;
 resa[0] |= zmask; resb[0] |= zmask;
}

/*
 * __eval_1w_nonstren for wire type N_TRIAND, N_WA
 */
static void asl_loc_eval_1w_nonstren_wire_and(word32 *resa, word32 *resb,
 word32 op2a, word32 op2b)
{
 word32 zmask, donemask;
 word32 op1a, op1b;

 op1a = resa[0];
 op1b = resb[0];
 zmask = ~((op1a ^ op2a) | (op1b ^ op2b));
 resa[0] = op1a & zmask;
 resb[0] = op1b & zmask;
 donemask = zmask;
 if (donemask == ALL1W) return;

 /* next op1 z bits, use op2 bits */
 zmask = (op1a ^ op1b) & op1b; 
 /* if z in op1, value is op2 */
 resa[0] |= (op2a & zmask);
 resb[0] |= (op2b & zmask);
 donemask |= zmask;
 if (donemask == ALL1W) return;

 /* next op2 zbits, use op1 bits */
 zmask = (op2a ^ op2b) & op2b; 
 /* if z in op2, value is op2 */
 resa[0] |= op1a & zmask;
 resb[0] |= op1b & zmask;
 donemask |= zmask; 
 if (donemask == ALL1W) return;

 zmask = ~donemask;
 resa[0] |= ((op1a | op1b) & (op2a | op2b)) & zmask;
 resb[0] |= (resa[0] & (op1b | op2b)) & zmask;
}

/*
 * __eval_1w_nonstren for wire type N_TRIOR, N_WO
 */
static void asl_loc_eval_1w_nonstren_wire_or(word32 *resa, word32 *resb,
 word32 op2a, word32 op2b)
{
 word32 zmask, donemask;
 word32 op1a, op1b;

 op1a = resa[0];
 op1b = resb[0];
 zmask = ~((op1a ^ op2a) | (op1b ^ op2b));
 resa[0] = op1a & zmask;
 resb[0] = op1b & zmask;
 donemask = zmask;
 if (donemask == ALL1W) return;

 /* next op1 z bits, use op2 bits */
 zmask = (op1a ^ op1b) & op1b; 
 /* if z in op1, value is op2 */
 resa[0] |= (op2a & zmask);
 resb[0] |= (op2b & zmask);
 donemask |= zmask;
 if (donemask == ALL1W) return;

 /* next op2 zbits, use op1 bits */
 zmask = (op2a ^ op2b) & op2b; 
 /* if z in op2, value is op2 */
 resa[0] |= op1a & zmask;
 resb[0] |= op1b & zmask;
 donemask |= zmask; 
 if (donemask == ALL1W) return;

 zmask = ~donemask;
 resb[0] |= ((op2b ^ op1b ^ ((op1a | op1b) & (op2b | (op2a & op1b)))) & zmask);
 resa[0] |= ((resb[0] | op2a | op1a) & zmask);
}

/* 
 * wrapper of set_byteval_ macro
 * AIV FIXME - lower this with rep insn
 */
extern void __asl_set_byteval(byte *sbp, byte stval, int32 blen)
{
 set_byteval_(sbp, blen, stval);
}

/*
 * ld wide logic gate driver - from __ld_gate_out v_ex4.c  
 */
extern word32 __asl_ld_logic_wide_driver(struct gate_t *gp, int32 nins)
{
 word32 wrd;

 wrd = widegate_ld_bit(&(__idp[gp->gstate_ofs]), nins + 1, nins);
 return(wrd);
}

/* 
 * copied from v_ex4.c
 * WRITEM - lower ????
 * make extern in v_ex4.c ???
 */
static word32 widegate_ld_bit(word32 *gsp, int32 gwid, int32 biti)
{
 int32 wlen, inum;
 word32 av, bv, *rap;

 /* rap is start of instance coded vector a b groups */
 wlen = wlen_(gwid);
 inum = get_inum_();
 rap = &(gsp[2*wlen*inum]);
 av = rhsbsel_(rap, biti);
 bv = rhsbsel_(&(rap[wlen]), biti);
 return(av | (bv << 1));
}

/*
 * asm to exec gate eval on input change
 * FIXME - should inline 
 */
extern word32 __asl_exec_wide_logic_gate(struct gate_t *gp, int32 i)
{
 word32 *rap, ngav, ngbv;
 int32 gwid, wlen, bi; 
 word32 out_chg;
 struct xstk_t *xsp;

 xsp = __eval_xpr(gp->gpins[i]);
 bi = i - 1; 
 ngav = xsp->ap[0] & 1L;
 ngbv = xsp->bp[0] & 1L;
 __new_inputval = ngav | (ngbv << 1);
 __pop_xstk();

 /* always set strength even if not needed - always constant here */
 /* rap is base of vector for current inst */
 rap = &(__idp[gp->gstate_ofs]);
 __lhs_changed = FALSE;
 asl_loc_gate_chg_lhsbsel(rap, bi, ngav);
 gwid = gp->gpnum;
 wlen = wlen_(gwid);
 asl_loc_gate_chg_lhsbsel(&(rap[wlen]), bi, ngbv);
 if (!__lhs_changed) return(FALSE);
 /* AIV 08/23/10 - need to reset __lhs_changed here to FALSE */
 /* was doing to many not needed evals */
 __lhs_changed = FALSE;
 /* this set global new and old gate values */
 out_chg = __eval_1wide_gate(gp, gwid);
 /* AIV LOOKATME BEWARE - machine dependent - but most of bbgen3 is as well */
#ifdef __CVC32__
 __asm__ ("movl %0, %%ecx" : : "g" (out_chg));
#else
 __asm__ ("movq %0, %%rcx" : : "g" (out_chg));
#endif
 return(TRUE);
}

static void asl_loc_gate_chg_lhsbsel(word32 *dwp, int32 dbit, word32 sw)
{
 word32 mask, sw2;
 int32 bi, wi;

 wi = get_wofs_(dbit);
 bi = get_bofs_(dbit);
 mask = 1UL << bi;
 sw2 = (sw & 1L) << bi;
 if (((dwp[wi] & mask) ^ sw2) != 0L)
  { __lhs_changed = TRUE; dwp[wi] &= ~mask; dwp[wi] |= sw2; }
}

extern void __asl_sched_scalar_mipd_16v(struct net_t *np, struct tev_t *ptevp)
{
 struct mipd_t *mipdp;
 int32 ndx;
 word32 nval, oval;
 word64 ndel, schtim;

 mipdp = &(np->nlds->elnpp.emipdbits[0]);
 oval = mipdp->oldvals[0];

 nval = __idp[np->nva_ofs];
 /* AIV 05/01/07 - bit known to have changed otherwise will never get here */
 mipdp->oldvals[0] = nval;
 ndx = ((nval & 3) << 2 | (oval & 3)) & 0xf;
 ndel = mipdp->pb_mipd_du.d16v[ndx];
 /* non src-dst path delay for this simple MIPD case */
 schtim = __simtime + ndel;

 if (ptevp->trigger)
  {
   /* pending event - no spike analysis but inertial reschedule */
   /* case 1a: pending event earlier than newly scheduled */
   /* AIV 06/30/09 - this should just be <, not <= == just returns in this */
   /* rountine - saves an if stmt */
   if (ptevp->etime < schtim)
    {
     /* reschedule - cancel and sched new or replace if pound 0 */
     asl_loc_reschedule_scalar_1mipd(ptevp, schtim);
     /* fall through since next case does nothing */
    }
   /* case 1b: pending event later (rare modeling anomally?) */ 
   /* since inertial just ignore new change */
   return;
  }

 /* if nothing pending can just schedule */
 ptevp->etime = schtim;
 ptevp->trigger = TRUE;
 if (ndel == 0ULL)
  {
   /* this is #0, but must still build tev */
   asl_loc_add_pnd0_event(ptevp);
  }
 else asl_loc_insert_event_(ptevp);
}

extern void __asl_sched_scalar_mipd_is16v(struct net_t *np, struct tev_t *ptevp)
{
 struct mipd_t *mipdp;
 int32 ndx, inum;
 word32 nval, oval;
 word64 ndel, schtim;

 mipdp = &(np->nlds->elnpp.emipdbits[0]);
 inum = get_inum_();
 oval = mipdp->oldvals[inum];

 /* AIV 05/01/07 - bit known to have changed otherwise will never get here */
 nval = __idp[np->nva_ofs];
 mipdp->oldvals[inum] = nval;
 ndx = 16*inum + ((((nval & 3) << 2) | (oval & 3)) & 0xf);
 ndel = mipdp->pb_mipd_du.d16v[ndx];
 schtim = __simtime + ndel;
 if (ptevp->trigger)
  {
   /* pending event - no spike analysis but inertial reschedule */
   /* case 1a: pending event earlier than newly scheduled */
   /* AIV 06/30/09 - this should just be <, not <= == just returns in this */
   /* rountine - saves an if stmt */
   if (ptevp->etime < schtim)
    {
     /* reschedule - cancel and sched new or replace if pound 0 */
     asl_loc_reschedule_scalar_1mipd(ptevp, schtim);
     /* fall through since next case does nothing */
    }
   /* case 1b: pending event later (rare modeling anomally?) */ 
   /* since inertial just ignore new change */
   return;
  }

 /* if nothing pending can just schedule */
 ptevp->etime = schtim;
 ptevp->trigger = TRUE;
 if (ndel == 0ULL)
  {
   /* this is #0, but must still build tev */
   asl_loc_add_pnd0_event(ptevp);
  }
 else asl_loc_insert_event_(ptevp);
}

extern void __asl_sched_scalar_mipd_is16v1(struct net_t *np, 
 struct tev_t *ptevp)
{
 struct mipd_t *mipdp;
 int32 ndx, inum;
 word32 nval, oval;
 word64 ndel, schtim;

 inum = get_inum_();
 mipdp = &(np->nlds->elnpp.emipdbits[0]);
 oval = mipdp->oldvals[inum];

 /* AIV 05/01/07 - bit known to have changed otherwise will never get here */
 nval = __idp[np->nva_ofs];
 mipdp->oldvals[inum] = nval;

 ndx = 16*inum + ((((nval & 3) << 2) | (oval & 3)) & 0xf);
 ndel = (word64) mipdp->pb_mipd_du.dis16v1[ndx];
 schtim = __simtime + ndel;
 if (ptevp->trigger)
  {
   /* pending event - no spike analysis but inertial reschedule */
   /* case 1a: pending event earlier than newly scheduled */
   /* AIV 06/30/09 - this should just be <, not <= == just returns in this */
   /* rountine - saves an if stmt */
   if (ptevp->etime < schtim)
    {
     /* reschedule - cancel and sched new or replace if pound 0 */
     asl_loc_reschedule_scalar_1mipd(ptevp, schtim);
     /* fall through since next case does nothing */
    }
   /* case 1b: pending event later (rare modeling anomally?) */ 
   /* since inertial just ignore new change */
   return;
  }

 /* if nothing pending can just schedule */
 ptevp->etime = schtim;
 ptevp->trigger = TRUE;
 if (ndel == 0ULL)
  {
   /* this is #0, but must still build tev */
   asl_loc_add_pnd0_event(ptevp);
  }
 else asl_loc_insert_event_(ptevp);
}

extern void __asl_sched_scalar_mipd_is16v2(struct net_t *np, 
 struct tev_t *ptevp)
{
 struct mipd_t *mipdp;
 int32 ndx, inum;
 word32 nval, oval;
 word64 ndel, schtim;

 inum = get_inum_();
 mipdp = &(np->nlds->elnpp.emipdbits[0]);
 oval = mipdp->oldvals[inum];

 /* AIV 05/01/07 - bit known to have changed otherwise will never get here */
 nval = __idp[np->nva_ofs];
 mipdp->oldvals[inum] = nval;
 ndx = 16*inum + ((((nval & 3) << 2) | (oval & 3)) & 0xf);
 ndel = (word64) mipdp->pb_mipd_du.dis16v2[ndx];
 schtim = __simtime + ndel;
 if (ptevp->trigger)
  {
   /* pending event - no spike analysis but inertial reschedule */
   /* case 1a: pending event earlier than newly scheduled */
   /* AIV 06/30/09 - this should just be <, not <= == just returns in this */
   /* rountine - saves an if stmt */
   if (ptevp->etime < schtim)
    {
     /* reschedule - cancel and sched new or replace if pound 0 */
     asl_loc_reschedule_scalar_1mipd(ptevp, schtim);
     /* fall through since next case does nothing */
    }
   /* case 1b: pending event later (rare modeling anomally?) */ 
   /* since inertial just ignore new change */
   return;
  }

 /* if nothing pending can just schedule */
 ptevp->etime = schtim;
 ptevp->trigger = TRUE;
 if (ndel == 0ULL)
  {
   /* this is #0, but must still build tev */
   asl_loc_add_pnd0_event(ptevp);
  }
 else asl_loc_insert_event_(ptevp);
}

extern void __asl_sched_scalar_mipd_is1v(struct tev_t *ptevp)
{
 word64 ndel, schtim;

 ndel = ptevp->delay;
 schtim = __simtime + ndel;
 if (ptevp->trigger)
  {
   /* pending event - no spike analysis but inertial reschedule */
   /* case 1a: pending event earlier than newly scheduled */
   /* AIV 06/30/09 - this should just be <, not <= == just returns in this */
   /* rountine - saves an if stmt */
   if (ptevp->etime < schtim)
    {
     /* reschedule - cancel and sched new or replace if pound 0 */
     asl_loc_reschedule_scalar_1mipd(ptevp, schtim);
     /* fall through since next case does nothing */
    }
   /* case 1b: pending event later (rare modeling anomally?) */ 
   /* since inertial just ignore new change */
   return;
  }

 /* if nothing pending can just schedule */
 ptevp->etime = schtim;
 ptevp->trigger = TRUE;
 if (ndel == 0ULL)
  {
   /* this is #0, but must still build tev */
   asl_loc_add_pnd0_event(ptevp);
  }
 else asl_loc_insert_event_(ptevp);
}

extern void __asl_sched_scalar_mipd_path(struct net_t *np, struct tev_t *ptevp)
{
 struct mipd_t *mipdp;
 word32 nval, oval;
 int32 inum;
 word64 ndel, schtim;

 mipdp = &(np->nlds->elnpp.emipdbits[0]);
 inum = get_inum_();
 oval = mipdp->oldvals[inum];

 /* AIV 05/01/07 - bit known to have changed otherwise will never get here */
 nval = __idp[np->nva_ofs];
 mipdp->oldvals[inum] = nval;
 __new_gateval = nval;
 __old_gateval = oval;

 /* notice old and new gate values must be set before here */
 if (mipdp->impthtab[inum] == NULL)
  {
   /* non src-dst path delay for this simple MIPD case */
   ndel = __get_del(mipdp->pb_mipd_du, mipdp->pb_mipd_delrep);
   schtim = __simtime + ndel;
  }
 else
  {
   /* use same algorithm as specify path delay algorithm to get last chged */
   asl_loc_get_impth_del(&schtim, np, mipdp); 
   ndel = schtim - __simtime;
  }

 if (ptevp->trigger)
  {
   /* pending event - no spike analysis but inertial reschedule */
   /* case 1a: pending event earlier than newly scheduled */
   /* AIV 06/30/09 - this should just be <, not <= == just returns in this */
   /* rountine - saves an if stmt */
   if (ptevp->etime < schtim)
    {
     asl_loc_reschedule_scalar_1mipd(ptevp, schtim);
    }
   /* case 1b: pending event later (rare modeling anomally?) */ 
   /* since inertial just ignore new change */
   return;
  }

 /* if nothing pending can just schedule */
 ptevp->etime = schtim;
 ptevp->trigger = TRUE;
 if (ndel == 0ULL)
  {
   /* this is #0, but must still build tev */
   asl_loc_add_pnd0_event(ptevp);
  }
 else asl_loc_insert_event_(ptevp);
}

extern void __asl_sched_scalar_mipd_pnd0(struct tev_t *ptevp)
{
 word64 schtim;

 /* AIV 05/01/07 - bit known to have changed otherwise will never get here */
 schtim = __simtime;
 if (ptevp->trigger)
  {
   /* pending event - no spike analysis but inertial reschedule */
   /* case 1a: pending event earlier than newly scheduled */
   //AIV LOOKATME - can this every happen?????
   if (ptevp->etime <= schtim)
    {
     /* reschedule - cancel and replace if pound 0 */
     ptevp->etime = schtim;
     /* new scheduled value replaces old - same pending event */
    }
   /* fall through since next case does nothing */
   /* case 1b: pending event later (rare modeling anomally?) */ 
   /* since inertial just ignore new change */
   return;
  }
   
 /* if nothing pending can just schedule */
 ptevp->etime = schtim;
 ptevp->trigger = TRUE;
 /* this is #0, but must still build tev */
 asl_loc_add_pnd0_event(ptevp);
}

extern void __asl_sched_scalar_mipd_const(struct tev_t *ptevp)
{
 word64 schtim;


 /* AIV 05/01/07 - bit known to have changed otherwise will never get here */
 schtim = __simtime + ptevp->delay;
 if (ptevp->trigger)
  {
   /* pending event - no spike analysis but inertial reschedule */
   /* case 1a: pending event earlier than newly scheduled */
   /* AIV 06/30/09 - this should just be <, not <= == just returns in this */
   /* rountine - saves an if stmt */
   if (ptevp->etime < schtim)
    {
     /* reschedule - cancel and sched new or replace if pound 0 */
     asl_loc_reschedule_scalar_1mipd(ptevp, schtim);
     /* fall through since next case does nothing */
    }
   /* case 1b: pending event later (rare modeling anomally?) */ 
   /* since inertial just ignore new change */
   return;
  }

 /* if nothing pending can just schedule */
 ptevp->etime = schtim;
 ptevp->trigger = TRUE;
 asl_loc_insert_event_(ptevp);
}

/*
 * asm wrapper routine to schedule vector mipd  - for entire net
 *
 * AIV 12/28/11 - this needs to pass per bit since the ptevp is different
 * for each bit 
 * AIV LOOKATME - this can be optimized to not call for each bit?
 *
 * this one does entire net _rng is passed the fixed range
 */
extern void __asl_sched_vec_mipd_bit(struct net_t *np, struct tev_t *ptevp,
 int32 bi)
{
 struct mipd_t *mipdp;

 mipdp = &(np->nlds->elnpp.emipdbits[bi]);
 if (mipdp->no_mipd) return;
 asl_loc_sched_mipd_nchg(np, bi, mipdp, ptevp);
}

/*
 * currently same as __sched_mipd_nchg from v_ex3.c
 */
static void asl_loc_sched_mipd_nchg(struct net_t *np, int32 bi,
 struct mipd_t *mipdp, struct tev_t *ptevp)
{
 word32 nval, oval;
 word32 nav, nbv;
 word64 ndel, schtim;
 byte *bp;
 int32 inum;

 /* load new wire value - need this call in case packed */
 /* AIV 12/28/11 - these are known to be vector here no reason to check */
 if (np->srep == SR_SVEC)
  {
   /* BEWARE - this depends on stren vec stored as byte array */
   bp = (byte *) &(__idp[np->nva_ofs]);
   nval = bp[bi];
  }
 else
  {
   __ld_bit(&nav, &nbv, np, bi); 
   nval = (nav & 1) | ((nbv & 1) << 1);
  }

 inum = get_inum_();
 oval = mipdp->oldvals[inum];

 /* if no pending event and this bit unchanged nothing to schedule */
 /* know at least one bit chged or will not get here but maybe not this one */
 if (!ptevp->trigger && nval == oval) return;

 mipdp->oldvals[inum] = nval;
 /* delay only uses logic not stren part of value */
 __new_gateval = nval & 3;
 __old_gateval = oval & 3;

 /* notice old and new gate values must be set before here */
 if (!mipdp->pth_mipd || mipdp->impthtab == NULL
  || mipdp->impthtab[inum] == NULL)
  {
   /* non src-dst path delay for this simple MIPD case */
   ndel = __get_del(mipdp->pb_mipd_du, mipdp->pb_mipd_delrep);
   schtim = __simtime + ndel;
  }
 else
  {
   /* use same algorithm as specify path delay algorithm to get last chged */
   asl_loc_get_impth_del(&schtim, np, mipdp); 
   ndel = schtim - __simtime;
  }

 if (!ptevp->trigger)
  {
   /* if nothing pending can just schedule */
   ptevp->etime = schtim;
   ptevp->trigger = TRUE;
   if (ndel == 0ULL)
    {
     asl_loc_add_pnd0_event(ptevp);
    }
   else asl_loc_insert_event_(ptevp);
   mipdp->mipdschd_tevs[inum] = ptevp;
   ptevp->tu.bi = bi;
   return;
  }

 /* pending event - no spike analysis but inertial reschedule */
 /* case 1a: pending event earlier than newly scheduled */
 if (ptevp->etime <= schtim)
  {
   /* current driving and schedule same, new later inertial value just */
   /* causes scheduled to be removed since output at right value */
   if (nval == oval)
    {
     /* cancel */
     asl_loc_cancel_1mipdev(ptevp);
    }
   else
    {
     /* reschedule - cancel and sched new or replace if pound 0 */
     asl_loc_reschedule_1mipd(bi, ptevp, schtim);
    }
   /* fall through since next case does nothing */
  }
 /* case 1b: pending event later (rare modeling anomally?) */ 
 /* since inertial just ignore new change */
}

/*
 * 
 */
static void asl_loc_reschedule_1mipd(int32 bi, struct tev_t *tevp, 
 word64 newtim)
{

 /* if del == 0 (pnd0), will always be same time reschedule */
 /* AIV 02/03/09 - better to just check time to see if it is the same */
 /* this is the same as checking 0 and no cancel/schd is needed */
 if (tevp->etime == newtim)
  {
   /* new scheduled value replaces old - same pending event */
   return;
  }

 linkout_tevp(tevp);
 tevp->etime = newtim;
 asl_loc_insert_event_(tevp);
 tevp->trigger = TRUE;
 tevp->tu.bi = bi;
 return;
}

static void asl_loc_reschedule_scalar_1mipd(struct tev_t *tevp, word64 newtim)
{
 /* AIV 02/03/09 - better to just check time to see if it is the same */
 /* this is the same as checking 0 and no cancel/schd is needed */
 /* AIV 06/30/09 - no need for this if stmt changed places everywhere this */
 /* is called had <= should just be < equal does nothing */
 //if (tevp->etime == newtim) return;

 linkout_tevp(tevp);
 tevp->etime = newtim;
 /* AIV 06/30/09 - this flag was commented out needs to be set here */
 tevp->trigger = TRUE;
 asl_loc_insert_event_(tevp);
}


#ifdef __STREE__
static void linkout_tevp(struct tev_t *tevp)
{
 struct tqnode_t *nodep;

 /* -- DBG remove -- */
// if (tevp->etime < __simtime) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 if (tevp->etime == __simtime)
  {
   linkout_cur_time(tevp);
   return;
  }

 tevp->trigger = FALSE;
 /* AIV LOOKATME - could either store nodep in tevp or search storing for now */
 /* -- DBG remove -- 
 nodep = find_time_telp(tevp->etime);
 if (tevp->nodep != nodep) __misc_terr(__FILE__, __LINE__);
 ---- */
 nodep = tevp->nodep;
 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 if (nodep == NULL) __misc_terr(__FILE__, __LINE__);
#endif
 /* -- */
 tevp->nodep = NULL;

 if (nodep->te_hdrp == tevp && nodep->te_endp == tevp) 
  {
   /* emptying block */
   nodep->te_hdrp = nodep->te_endp = NULL;
//AIV FIXME - should remove node from tree - makes tree smaller for inserts
//   __remove_timing_node(nodep);
  }
 else if (tevp->teprevp == NULL) 
  { 
   /* link out at front */
   nodep->te_hdrp = tevp->tenxtp; 
   nodep->te_hdrp->teprevp = NULL;
  }
 else if (tevp->tenxtp == NULL)
  {
   /* link out at end (but not emptying) */
   nodep->te_endp = tevp->teprevp;
   nodep->te_endp->tenxtp = NULL;
  }
 else
  {
   /* inside */
   tevp->teprevp->tenxtp = tevp->tenxtp;
   tevp->tenxtp->teprevp = tevp->teprevp;
  } 
 /* finally put on free list since linked out */
 /* -- DBG remove -- */
// if (tevp->free_it) __misc_terr(__FILE__, __LINE__);
 /* -- */
}

#else
static void linkout_tevp(struct tev_t *tevp)
{
 struct tev_t *new_tevp;
 struct heap_t *time_hp;

 /* -- DBG remove -- */
// if (tevp->etime < __simtime) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 if (tevp->etime == __simtime)
  {
   linkout_cur_time(tevp);
   return;
  }

 tevp->trigger = FALSE;
 time_hp = tevp->time_hp;
 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 if (time_hp == NULL) __misc_terr(__FILE__, __LINE__);
#endif
 /* -- */
 tevp->time_hp = NULL;

 if (time_hp->te_hdrp == tevp && time_hp->te_endp == tevp) 
  {
   /* emptying block */
   /* AIV 07/21/08 - empty block now should just alloc a new one */
   /* and set it's event to cancel this is better because otherwise */
   /* every time move time must check for empty time events */
   new_tevp = asl_loc_get_new_event(tevp);
   new_tevp->enterptr = __process_cancel_ev_enterp;
   time_hp->te_hdrp = time_hp->te_endp = new_tevp;
  }
 else if (tevp->teprevp == NULL) 
  { 
   /* link out at front */
   time_hp->te_hdrp = tevp->tenxtp; 
   time_hp->te_hdrp->teprevp = NULL;
  }
 else if (tevp->tenxtp == NULL)
  {
   /* link out at end (but not emptying) */
   time_hp->te_endp = tevp->teprevp;
   time_hp->te_endp->tenxtp = NULL;
  }
 else
  {
   /* inside */
   tevp->teprevp->tenxtp = tevp->tenxtp;
   tevp->tenxtp->teprevp = tevp->teprevp;
  } 
 /* finally put on free list since linked out */
 /* -- DBG remove -- */
// if (tevp->free_it) __misc_terr(__FILE__, __LINE__);
 /* -- */
}
#endif

 
static void linkout_cur_time(struct tev_t *tevp)
{
 struct tev_t *nxt_tevp;

 tevp->trigger = FALSE;
 /* -- DBG remove -- 
 if (tevp->etime != __simtime) __misc_terr(__FILE__, __LINE__);
 ---- */
 /* AIV 12/18/07 - rare case it is processing pnd0 (gate 0 reschedule) */
 /* need to linkout to the pnd0 list */
 /* AIV 01/19/09 - removed need to set __processing_pnd0s flag */
 if (__cur_te_endp == NULL)
  {
   linkout_pnd0_event(tevp);
   return;
  }

 /* AIV 02/13/09 - removed the need to use/set __cur_te_hdrp */
 if (tevp->teprevp == NULL) 
  { 
   if (__cur_te_endp == tevp) 
    {
     /* emptying block */
     __cur_te_endp = NULL;
    }
   else
    {
     /* link out at front */
     nxt_tevp = tevp->tenxtp; 
//AIV HERE2
     if (nxt_tevp != NULL) nxt_tevp->teprevp = NULL;
    }
  }
 else if (tevp->tenxtp == NULL)
  {
   /* link out at end (but not emptying) */
   __cur_te_endp = tevp->teprevp;
   __cur_te_endp->tenxtp = NULL;
  }
 else
  {
   /* inside */
   tevp->teprevp->tenxtp = tevp->tenxtp;
   tevp->tenxtp->teprevp = tevp->teprevp;
   /* AIV 12/19/07 - may still be the last event but due to the fact */
   /* that it sets __cur_te_end->tenxtp = NEXT_EV it is really end event */
   if (__cur_te_endp == tevp) __cur_te_endp = tevp->teprevp;
  } 
}

/*
 * same as linkout_cur_time except using __p0 list header/tail
 *
 * AIV LOOKATME - could use one routine and pass as pointer but think 
 * produces better to inline the globals
 */
static void linkout_pnd0_event(struct tev_t *tevp)
{
 if (__p0_te_hdrp == tevp && __p0_te_endp == tevp) 
  {
   /* emptying block */
   __p0_te_hdrp = __p0_te_endp = NULL;
  }
 else if (tevp->teprevp == NULL) 
  { 
   /* link out at front */
   __p0_te_hdrp = tevp->tenxtp; 
   if (__p0_te_hdrp != NULL) __p0_te_hdrp->teprevp = NULL;
  }
 else if (tevp->tenxtp == NULL)
  {
   /* link out at end (but not emptying) */
   __p0_te_endp = tevp->teprevp;
   __p0_te_endp->tenxtp = NULL;
  }
 else
  {
   /* inside */
   tevp->teprevp->tenxtp = tevp->tenxtp;
   tevp->tenxtp->teprevp = tevp->teprevp;
   /* AIV 12/19/07 - may still be the last event but due to the fact */
   /* that it sets __p0_te_end->tenxtp = NEXT_EV it is really end event */
   if (__p0_te_endp == tevp) __p0_te_endp = tevp->teprevp;
  } 
}

/* AIV 10/16/07 - need to keep the routine local for gcc inlining */
extern void __asl_linkout_tevp(struct tev_t *tevp)
{
//AIV FIXME - what about malloc tevps memory leak need to free here
 /* trigger bit may be off here if the simtime is equal to the scheduled time */
 if (tevp->etime == __simtime)
  {
   linkout_cur_time(tevp);
   return;
  }
 /* trigger may not be set for arming so don't need to linkout */
 if (!tevp->trigger) return;
 linkout_tevp(tevp);
}

/*
 * same as above except dont' check for trigger called from wrapper code
 * AIV LOOKATME - maybe asl_loc_insert_event should just set trigger flag?????
 */
extern void __asl_linkout_tevp_no_trigger(struct tev_t *tevp)
{
//AIV FIXME - what about malloc tevps memory leak need to free here
 /* trigger bit may be off here if the simtime is equal to the scheduled time */
 if (tevp->etime == __simtime)
  {
   linkout_cur_time(tevp);
   return;
  }
 linkout_tevp(tevp);
}


/*
 * same as cancel_1midev from v_ex3
 */
static void asl_loc_cancel_1mipdev(struct tev_t *tevp)
{
 linkout_tevp(tevp);
}


/*
 * same as get_impth_del from v_ex3
 * AIV 01/13/12 - changed __pdlatechgtim to local pdlatechgtim
 * this is only global in interpreter for tracing
 */
static void asl_loc_get_impth_del(word64 *pschtim, struct net_t *np, 
 struct mipd_t *mipdp)
{
 struct impth_t *impdp;
 word64 chgtim, newdel, pdlatechgtim;
 int32 inum;
  
 inum = get_inum_();
 impdp = mipdp->impthtab[inum];
 pdlatechgtim = impdp->lastchg;
 /* know delay is non IS since src-dst delays outside inst tree */
 __pdmindel = __get_del(impdp->impth_du, impdp->impth_delrep);

 /* common only 1 path ends on net/bit case */ 
 if ((impdp = impdp->impthnxt) == NULL)
  {
   *pschtim = pdlatechgtim + __pdmindel;
   return;
  }

 /* complicated case where more than one path end on this dest. wire np */
 for (;impdp != NULL; impdp = impdp->impthnxt)
  {
   /* get source change time */
   chgtim = impdp->lastchg;

   /* case 1: change time earlier, always select latest */
   if (chgtim < pdlatechgtim) continue;
    
   /* know this will be non IS delay */
   newdel = __get_del(impdp->impth_du, impdp->impth_delrep);

   /* if change times are the same, use the shortest path */
   if (chgtim == pdlatechgtim)
    {
     /* newdel larger implies not shorter path, do not change */
     /* if same try to replace */
     if (newdel > __pdmindel) continue;
    }
   /* this path's change time later(< handled above), just use */
   else pdlatechgtim = chgtim;

   __pdmindel = newdel;
  }
 *pschtim = pdlatechgtim + __pdmindel;
}

/*
 * WRAPPER ROUTINES FOR CONTA SCHEDULING
 */

/*
 * wrapper to scheduling conta - also call get dely to get delay
 * non separated into per bit form
 */
extern void __asl_schd_caev(struct conta_t *cap, struct tev_t *tevp)
{
 word64 cadel;


 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 check_for_active_event(tevp);
#endif
 tevp->trigger = TRUE;
 /* -- */

 cadel = __get_del(cap->ca_du, cap->ca_delrep);
 tevp->etime =  __simtime + cadel;
 if (cadel == 0ULL)
  {
   /* AIV 12/26/07 - must be doubly linked since may have to be linked out */
   asl_loc_add_pnd0_event_dl(tevp);
  }
 else asl_loc_insert_event_(tevp);
}

/*
 *  conta with constant bit time
 */
extern void __asl_schd_caev_const(struct tev_t *tevp)
{
 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 check_for_active_event(tevp);
#endif
 /* -- */
 /* AIV 11/14/07 - need to turn on trigger flag here */
 tevp->trigger = TRUE;
 tevp->etime = __simtime + tevp->delay;
 asl_loc_insert_event_(tevp);
}

/*
 *  conta with constant delay 0 
 */
extern void __asl_schd_caev_const0(struct tev_t *tevp)
{
 tevp->etime = __simtime;
 /* AIV 12/14/07 - need to turn on trigger flag here */
 tevp->trigger = TRUE;
 /* this is #0, but must still build tev */
 /* AIV 12/26/07 - must be doubly linked since may have to be linked out */
 asl_loc_add_pnd0_event_dl(tevp);
}

/*
 * wrapper for canceling a scheduled conta event
 */
extern void __asl_cancel_ev(struct tev_t *tevp) 
{
 linkout_tevp(tevp);
}

/*
 * GATE ASL LIB ROUTINES
 */

/*
 * wrapper to make the table look up to calculation bufif new state
 * know bufif always drives stren
 */
/*
 * wrapper to make the table look up to calculation bufif new state
 * know bufif always drives stren
 */
extern word32 __asl_calc_bufif_newstate(word32 gwrd, int32 base, int32 g_stval)
{
 word32 ngv;

 /* use input 4 bits as case access - output not just simple 8 bit value */
 gwrd &= 0xf;

 /* assume 0 value with driven strength (strong if none) */
 ngv = g_stval;
 ngv &= __bufif_and_tab[gwrd + base];
 ngv |= __bufif_or_tab[gwrd + base];
 ngv = __stren_map_tab[ngv];
 __new_gateval = ngv;
 return(ngv);
}

/*
 * asm wrapper to calculate table value for combinatorial part of udp
 */
extern word32 __asl_calc_comb_udp(struct gate_t *gp, int32 wi, int32 bi)
{
 int32 ngval;

 ngval = (gp->gmsym->el.eudpp->utab->ludptab[wi] >> bi) & 3;
 return(ngval);
}

/*
 * handle special wide udp gate adjust case for udp with delay
 * see __change_gate_outwire with wide GC_UDP != U_COMB
 */
extern word32 __asl_udp_wide_adjstate(word32 *gwp, int32 nins)
{
 word32 w1;
 __old_gateval = (gwp[0] >> (2*nins)) & 3L;
 w1 = gwp[1];
 w1 -= ((__old_gateval == 3) ? 2 : __old_gateval)*__pow3tab[nins];
 w1 += ((__new_gateval == 3) ? 2 : __new_gateval)*__pow3tab[nins];
 return(w1);
}

/*
 * asm wrapper to adjust (calculate) table value for edge part of udp
 * only called if comb value is 3 (unknown)
 */
extern word32 __asl_adjust_edge_udp(int32 pi, int32 ndx, int32 old_ival, 
 struct gate_t *gp)
{
 int32 tabi, ngval, wi, bi;
 word32 *wp;
 struct udp_t *udpp;

 udpp = gp->gmsym->el.eudpp;
 /* AIV FIXME - lower this - add eudptabs to comm_* file */
 wi = get_wofs_(ndx);
 bi = get_bofs_(ndx);
 tabi = 3*pi + ((old_ival == 3) ? 2 : old_ival);
 wp = udpp->utab->eudptabs[tabi];
 ngval = (wp[wi] >> bi) & 3L;
 return(ngval);
}

/*
 * asm wrapper to evaluate, combine strens and return out chged for jmp 0
 * for cmos
 */
extern int32 __asl_eval_cmos_gate(int32 nmos_gwrd, int32 pmos_gwrd,
 int32 old_gateval, int32 wtyp)
{
 word32 new_nval, new_pval;

 __eval_nmos_gate(nmos_gwrd); 
 new_nval = __new_gateval;

 __eval_pmos_gate(pmos_gwrd);
 new_pval = __new_gateval;
 if (new_nval == new_pval && new_nval == old_gateval) return(FALSE);

 /* even if different after stren competition may be unchanged */
 __new_gateval = __comb_1bitsts(wtyp, new_nval, new_pval); 
 return(!(__new_gateval == old_gateval));
}

/*
 * asm wrapper to evaluate, combine strens and return out chged for jmp 0
 * for rcmos
 */
extern int32 __asl_eval_rcmos_gate(int32 nmos_gwrd, int32 pmos_gwrd,
 int32 old_gateval, int32 wtyp)
{
 word32 new_nval, new_pval;

 /* controls: 1st nmos 8-15, 2nd pmos 16-23 */
 __eval_rnmos_gate(nmos_gwrd); 
 new_nval = __new_gateval;

 __eval_rpmos_gate(pmos_gwrd);
 new_pval = __new_gateval;
 if (new_nval == new_pval && new_nval == old_gateval) return(FALSE);

 __new_gateval = __comb_1bitsts(wtyp, new_nval, new_pval); 
 return(TRUE);
}

/*
 * wrapper to set new gateval from rhs expr - used internally by scheduler
 *
 * for ca 4vdel and per bit, this is master cap, otherwide just cap
 */
extern void __asl_set_rhs_new_gateval(word32 *rhs_wp, int32 rhswid)
{
 int32 wlen;

 wlen = wlen_(rhswid);
 if (vval_is0_(rhs_wp, rhswid))
  {
   if (vval_is0_(&(rhs_wp[wlen]), rhswid)) __new_gateval = 0;
   else if (__vval_is1(&(rhs_wp[wlen]), rhswid)) __new_gateval = 2;
  }
 else if (__vval_is1(rhs_wp, rhswid) && __vval_is1(&(rhs_wp[wlen]), rhswid))
  { __new_gateval = 3; }
 else __new_gateval = 1;
}

extern void __asl_stren_schd_1gev(struct gate_t *gp, struct tev_t *tevp)
{
 word64 gdel;
 
 if ((__new_gateval & 2) == 0 && __hizstren_del_tab[gp->g_stval] == 1)
  gdel = __hizstrengate_getdel(gp);
 else gdel = __get_del(gp->g_du, gp->g_delrep);

 tevp->etime = __simtime + gdel;
 tevp->trigger = TRUE;
 tevp->outv = (byte) __new_gateval;

 if (gdel == 0ULL)
  {
   /* AIV 12/18/07 - need doubly-linked because p0 may have to reschedule */
   asl_loc_add_pnd0_event_dl(tevp);
  }
 else asl_loc_insert_event_(tevp);
}

/*
 * asl wrapper to schedule a non stren driving gate
 * 
 */
extern void __asl_schd_1gev(struct gate_t *gp, struct tev_t *tevp)
{
 word64 gdel;

 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 check_for_active_event(tevp);
#endif
 tevp->trigger = TRUE;
 /* -- */

 gdel = __get_del(gp->g_du, gp->g_delrep);
 tevp->etime = __simtime + gdel;
 if (gdel == 0ULL)
  {
   /* this is #0, but must still build tev */
   /* AIV 12/18/07 - need doubly-linked because p0 may have to reschedule */
   asl_loc_add_pnd0_event_dl(tevp);
  }
 else asl_loc_insert_event_(tevp);
}

extern void __asl_schd_1gev_const(struct tev_t *tevp)
{
 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 check_for_active_event(tevp);
#endif
 tevp->trigger = TRUE;
 /* -- */

 tevp->etime = __simtime + tevp->delay;
 asl_loc_insert_event_(tevp);
}

extern void __asl_schd_1gev_pnd0(struct tev_t *tevp)
{
 /* -- DBG remove -- */
#ifdef __CVC_DEBUG__
 check_for_active_event(tevp);
#endif
 tevp->trigger = TRUE;
 /* -- */

 tevp->etime = __simtime;
 /* AIV 12/18/07 - need doubly-linked because p0 may have to reschedule */
 asl_loc_add_pnd0_event_dl(tevp);
}

/* -- DBG remove -- */
static void check_for_active_event(struct tev_t *tevp)
{
// if (tevp->te_idp != __idp) __misc_terr(__FILE__, __LINE__);
 if (__cur_tevp != tevp && tevp->trigger) __misc_terr(__FILE__, __LINE__);
}

/* ---- */

/*
 * asl wrapper for complex cancele pending with new and old same (unchg)
 * for both stren and non stren driving cases
 */
extern int32 __asl_cancele_pend_nochg_1gev(struct gate_t *gp, 
 struct tev_t *tevp)
{
 word64 gdel, schtim;

 /* need time of new value scheduled change for this analysis */
 if (gp->g_hasst && (__new_gateval & 2) == 0
  && __hizstren_del_tab[gp->g_stval] == 1) 
   {
    gdel = __hizstrengate_getdel(gp);
   }
 else gdel = __get_del(gp->g_du, gp->g_delrep);

 schtim = __simtime + gdel;
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_pulsewarn(gp, tevp, &(tevp->etime), &schtim, "drives glitch");

 /* if spike, suppress future but schedule to x at currently scheduled */
 if (__show_cancel_e)
  {
   if (__showe_onevent)
    { tevp->outv = __get_showcancele_val(gp); return(FALSE); }

   /* immediate assign then cancel */
   __new_gateval = __get_showcancele_val(gp);
   /* newly scheduled to same so no event */
   linkout_tevp(tevp);
   return(TRUE);
  }
 /* needed for the non cancele case when warn cancele on */ 
 /* newly scheduled to same so no event */
 linkout_tevp(tevp);
 return(FALSE); 
}

/*
 * wrapper to store gate out
 *
 * SJM LOOKATME - think always accellerated
//SJM LOWERME 
 */
extern void __asl_chg_gate_outwire(struct tev_t *tevp)
{
 struct gate_t *gp;
//AIV FIXME - temporary until cmos/udp/mos backend lowered
 
//AIV FIXME - this has a fixed gate????????????????????
//could just pass the gate instead
 gp = tevp->tu.tegp;
 if (!gp->g_pdst) __acc_evchg_gate_outwire(gp);
 else __change_gate_outwire(gp);
}

/*
 * asl wrapper for cancele case of pending scheduled change gate
 */
extern int32 __asl_cancele_pend_chg_1gev(struct gate_t *gp, struct tev_t *tevp) 
{
 word64 gdel, schtim;

 if (tevp->outv == (byte) __new_gateval) return(TRUE);

 /* need time of new value scheduled change for this analysis */
 if (gp->g_hasst && (__new_gateval & 2) == 0
  && __hizstren_del_tab[gp->g_stval] == 1) 
   {
    gdel = __hizstrengate_getdel(gp);
   }
 else gdel = __get_del(gp->g_du, gp->g_delrep);

 schtim = __simtime + gdel;

 /* normal inertial reschedule */
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_pulsewarn(gp, tevp, &(tevp->etime), &schtim, "unstable");

 if (__show_cancel_e)
  {
   if (__showe_onevent)
    { tevp->outv = __get_showcancele_val(gp); return(TRUE); }

   __new_gateval = __get_showcancele_val(gp);
   /* newly scheduled to same so no event */
   linkout_tevp(tevp);
   return(FALSE);
  }
 /* reschedule - handles cancel */
 tevp->outv = (byte) __new_gateval;
 /* reschedule */
 /* if del == 0 (pnd0), will always be same time reschedule */
 if (gdel == 0ULL) return(TRUE);

 linkout_tevp(tevp);
 tevp->etime = schtim;
 asl_loc_insert_event_(tevp);
 tevp->trigger = TRUE; 
 return(TRUE);
}

/*
 * asl wrapper stren simple (no cancele) pending scheduled no chg
 */
extern void __asl_stren_pend_nochg_1gev(struct tev_t *tevp)
{
 linkout_tevp(tevp);
}

/*
 * asl wrapper non stren simple (no cancele) pending scheduled no chg
 * AIV 10/22/07 - this wrapper is actually just a cancel event
 */
extern void __asl_pend_nochg_1gev(struct tev_t *tevp)
{
 linkout_tevp(tevp);
}

/*
 * asl wrapper for non stren simple (no cancele) pending scheduled - chg
 */
extern void __asl_pend_chg_1gev(struct gate_t *gp, struct tev_t *tevp)
{
 word64 gdel;

 gdel = __get_del(gp->g_du, gp->g_delrep);
 /* reschedule */
 /* if del == 0 (pnd0), will always be same time reschedule */
 if (gdel == 0ULL) return;

 linkout_tevp(tevp);
 tevp->trigger = TRUE; 
 tevp->etime = __simtime + gdel;
 asl_loc_insert_event_(tevp);
}

/*
 * AIV 02/25/09 - added constant version - known to not be delay 0
 */
extern void __asl_pend_chg_1gev_const(struct tev_t *tevp)
{
 /* reschedule - handles cancel */
 linkout_tevp(tevp);
 tevp->etime = __simtime + tevp->delay;
 tevp->trigger = TRUE; 
 asl_loc_insert_event_(tevp);
}

/*
 * asl wrapper stren simple (no cancele) pending scheduled - chg
 */
extern void __asl_stren_pend_chg_1gev(struct gate_t *gp, struct tev_t *tevp)
{
 word64 gdel;

 if (tevp->outv == (byte) __new_gateval) return;

 /* if 0 or 1 and hiz strength gate need to use to hiz delay */
 if ((__new_gateval & 2) == 0 && __hizstren_del_tab[gp->g_stval] == 1)
  gdel = __hizstrengate_getdel(gp);
 else gdel = __get_del(gp->g_du, gp->g_delrep);

 tevp->outv = (byte) __new_gateval;
 /* reschedule */
 /* if del == 0 (pnd0), will always be same time reschedule */
 if (gdel == 0ULL) return;

 linkout_tevp(tevp);
 tevp->etime = __simtime + gdel;
 tevp->trigger = TRUE; 
 asl_loc_insert_event_(tevp);
}


/*
 * CONTA ASL LIB ROUTINES
 */

/*
 * wrapper to scheduling conta - also call get dely to get delay
 * non separated into per bit form
 */
extern void __asl_reschd_caev(struct conta_t *cap, struct tev_t *tevp)
{
 word64 cadel, newtime;

 cadel = __get_del(cap->ca_du, cap->ca_delrep);

 newtime = __simtime+cadel;
 /* AIV 02/03/09 - better to just check time to see if it is the same */
 /* this is the same as checking 0 and no cancel/schd is needed */
 /* if del == 0 (pnd0), will always be same time reschedule */
 if (tevp->etime == newtime)
  {
   /* new scheduled value replaces old */
   /* AIV 12/22/07 - need to return here */
   return;
  }

 /* cancel */
 linkout_tevp(tevp);
 /* this will change the scheduled field so no need to set to nil */
 tevp->etime = newtime;
 /* AIV 06/30/09 - should be setting flag here */
 tevp->trigger = TRUE;
 asl_loc_insert_event_(tevp);
}

/*
 * resched conta with constant time
 */
extern void __asl_reschd_caev_const(struct tev_t *tevp)
{
 word64 newtime;
 /* cancel */
 /* AIV 11/14/07 - wasn't marking correctly and doing the linkout for reschd */
 /* -- DBG remove -- */
 /* check_for_active_event(tevp); */
#ifdef __CVC_DEBUG__
 if (!tevp->trigger) __misc_terr(__FILE__, __LINE__);
#endif
 /* -- */

 /* AIV 02/03/09 - better to just check time to see if it is the same */
 /* this is the same as checking 0 and no cancel/schd is needed */
 newtime = __simtime+tevp->delay;
 if (tevp->etime == newtime) return;

 linkout_tevp(tevp);
 tevp->trigger = TRUE;
 tevp->etime = newtime;
 asl_loc_insert_event_(tevp);
}

/************************************************************************/
/*************** ASL ROUTINE FOR TRAN CHAN HANDLING  ********************/
/************************************************************************/

extern int32 __asl_eval_tranif_ld(struct gate_t *gp)
{
 int32 out_chg;

 /* third in chged - schedule (if needed) conducting state chg */
 /* must always go through scheduling code for spike analysis */
 asl_loc_eval_tranif_onoff(gp);
 /* out_chg T if conducting state changed */
 out_chg = (__new_gateval != __old_gateval);
 /* must evaluate both sides */
 return(out_chg);
}

/*
 *
 */
static void asl_loc_eval_tranif_onoff(struct gate_t *gp)
{
 int32 bi;
 word32 cval;
 struct xstk_t *xsp;
 int32 gateid, inum;

 inum = get_inum_();
 bi = get_bofs_(2*inum);
 /* step 1: access old value */
 cval = __idp[gp->gstate_ofs];
 /* this is conducting state independent of if0 or if1 */
 __old_gateval = (cval >> bi) & 3L;
 /* step 2: compute new conducting value */
 xsp = __eval_xpr(gp->gpins[2]);
 __new_inputval = (xsp->ap[0] & 1L) | ((xsp->bp[0] & 1L) << 1);
 if (__new_inputval == 2) __new_inputval = 3;
 __pop_xstk();
 gateid = gp->gmsym->el.eprimp->gateid;
 /* exactly 4 types of tranif gates */
 if (gateid == G_TRANIF1 || gateid == G_RTRANIF1)
  __new_gateval = __new_inputval;
 else
  { __new_gateval = (__new_inputval == 0) ? 1
   : ((__new_inputval == 1) ? 0 : __new_inputval);
  }
}

extern void __asl_immed_eval_trifchan(struct gate_t *gp)
{
 __cvc_immed_eval_trifchan(gp);
 if (__chg_vtxlst_hdr != NULL) asl_loc_assign_chged_vtxs();
}


extern int32 __asl_update_tran_harddrvs(struct net_t *np)
{
 byte *sbp, *sbp2;
 struct xstk_t *xsp, *xsp2;
 int32 inum;

 sbp = NULL;
 if (np->n_stren)
  {
   /* this will make chan wire section of input drivers have wire type */
   /* i.e. supply will probably override its drivers */
   xsp = __stload_mdrwire(np);
   sbp = (byte *) xsp->ap;
   /* SJM - 03/15/01 - even if forced wtill need to update hard drvrs */
   /* in case ever released - just do not use them when force in effect */
   inum = get_inum_();
   sbp2 = &(np->ntraux->trnva.bp[inum*np->nwid]);

   /* SJM 11/24/00 - for path destinations can't eliminate schedule using */ 
   /* current switch channel state because there may be pending event that */
   /* requires inertial rescheduling */

   /* SJM 12/13/00 malloc lib fails when bcmp of 1 byte scalar */
   if (np->nwid == 1)
    {
     if (sbp[0] != sbp2[0]) sbp2[0] = sbp[0]; 
     goto chg;
   }

   /* if all changed drivers (tran channel input) same, nothing to do */
   if (memcmp(sbp, sbp2, np->nwid) == 0) goto no_chg;

   /* update this wire drvrs (chan in sect), copy 2nd arg is dest. */
   memcpy(sbp2, sbp, np->nwid);
   /* now done with sbp and xsp */ 
   goto chg; 
  }

 xsp = __load_mdrwire(np);
 /* but must update driving value fron tran channel of xmr from inst */
 push_xstk_(xsp2, np->nwid);
 __ld_perinst_val(xsp2->ap, xsp2->bp, np->ntraux->trnva, np->nwid);

 /* SJM 11/24/00 - also for non stren case, must always use inertial */ 
 /* rescheduling on inout paths */
 if (np->nwid <= WBITS)
  {
   if (xsp->ap[0] == xsp2->ap[0] && xsp->bp[0] == xsp2->bp[0]) goto no_chg;
  }
 else
  {
   if (cmp_vval_(xsp->ap, xsp2->ap, np->nwid) == 0
    && cmp_vval_(xsp->bp, xsp2->bp, np->nwid) == 0) goto no_chg;
  }

 /* update ins (drvs) for this tran chan wire section */ 
 __st_perinst_val(np->ntraux->trnva, np->nwid, xsp->ap, xsp->bp);
chg:
 __pop_xstk();
 if (!np->n_stren) __pop_xstk();
 return(TRUE);

no_chg:
 __pop_xstk();
 if (!np->n_stren) __pop_xstk();
 return(FALSE);
}
   
/*
 *
 */
extern byte *__asl_tran_addr(struct net_t *np)
{
 byte *sbp;
 int32 inum;

 inum = get_inum_();
 sbp = &(np->ntraux->trnva.bp[inum*np->nwid]);
 return(sbp);
}

extern int32 __asl_stren_schd_bidpthdrvrs(struct net_t *np, byte *drv_sbp, 
 byte *trnva_sbp, int32 bi, struct tev_t *tevp)
{
 int32 nd_chan_upd;

 __new_gateval = (word32) *drv_sbp;
 __old_gateval = (word32) *trnva_sbp;

 nd_chan_upd = asl_loc_schd_1bitpthdrvr(np, bi, tevp);
 return(nd_chan_upd);
}

extern int32 __asl_schd_scalar_bidpthdrvrs(struct net_t *np, byte *drv_wp,
 byte *trnva_wp, int32 bi, struct tev_t *tevp)
{
 int32 nd_chan_upd;

 __new_gateval = (word32) drv_wp[bi];
 __old_gateval = (word32) trnva_wp[bi];
 nd_chan_upd = asl_loc_schd_1bitpthdrvr(np, bi, tevp);
 return(nd_chan_upd);
}

extern int32 __asl_schd_bidpthdrvrs(struct net_t *np, word32 *drv_wp,
 word32 *trnva_wp, int32 bi, struct tev_t *tevp)
{
 word32 tmp;
 word32 *drv_bp_wp, *trnva_bp_wp;
 int32 nd_chan_upd, wlen;

 wlen = wlen_(np->nwid);
 drv_bp_wp = &(drv_wp[wlen]);
 trnva_bp_wp = &(trnva_wp[wlen]);
 tmp = rhsbsel_(drv_bp_wp, bi);
 __new_gateval = (tmp << 1) | (rhsbsel_(drv_wp, bi));
 tmp = rhsbsel_(trnva_bp_wp, bi);
 __old_gateval = (tmp << 1) | (rhsbsel_(trnva_wp, bi));
 nd_chan_upd = asl_loc_schd_1bitpthdrvr(np, bi, tevp);
 return(nd_chan_upd);
}

extern void __asl_store_bidpthdrvrs(struct net_t *np, word32 *trnva_wp, 
 int32 bi)
{
 word32 *trnva_bp_wp;
 int32 wlen;

 wlen = wlen_(np->nwid);
 trnva_bp_wp = &(trnva_wp[wlen]);
 __lhsbsel(trnva_wp, bi, (__new_gateval & 1L));
 __lhsbsel(trnva_bp_wp, bi, ((__new_gateval >> 1) & 1L));
//AIV FIXME - this is per instance - should go into idp area - leaving
//as a wrapper for now 
 __st_perinst_val(np->ntraux->trnva, np->nwid, trnva_wp, trnva_bp_wp);
}

/*
 *
 */
extern int32 __asl_trpath_scalar_store(struct net_t *np, word32 nval)
{
 struct traux_t *trap;
 word32 av, bv;
 int32 inum;

 trap = np->ntraux;
   
 /* AIV 07/12/07 - BEWARE local inum now is used in reg_fr_inhibit_ macro */
 inum = get_inum_();
 ld_peri_scalval_(&av, &bv, trap->trnva.bp);
 if (nval == (av | (bv << 1))) return(FALSE);
 /* SJM 07/16/01 - typo was storing old val so tr chan value never chgs */
 /* need to store new non stren value not old */
 /* ??? wrong - st_scalval_(trap->trnva.bp, av, bv); */
 st2_peri_scalval_(trap->trnva.bp, nval);
 return(TRUE);
}

/*
 *
 */
extern int32 __asl_trpath_store(struct net_t *np, word32 nval, int32 bi)
{
 struct traux_t *trap;
 struct xstk_t *xsp;
 word32 av, bv;


 trap = np->ntraux;
 push_xstk_(xsp, np->nwid);
 __ld_perinst_val(xsp->ap, xsp->bp, trap->trnva, np->nwid);
 av = rhsbsel_(xsp->ap, bi);
 bv = rhsbsel_(xsp->bp, bi);
 if (nval == (av | (bv << 1))) { __pop_xstk(); return(FALSE); }
 __lhsbsel(xsp->ap, bi, (nval & 1L));
 __lhsbsel(xsp->bp, bi, ((nval >> 1) & 1L));
 __st_perinst_val(trap->trnva, np->nwid, xsp->ap, xsp->bp);
 __pop_xstk();
 return(TRUE);
}

/*
 * schedule 1 bit path bidirect driver
 *
 * show cancel e analysis including non inout path distributed delay
 *
 * this works for both strength 8 bit nval and oval and non strength
 * if scalar bi must be 0 (i.e. biti can not be -1)
 * nval is new value to schedule change to, old value is current wire value
 *
 * old and new gate values in globals - maybe changed since caller saves
 */
static int32 asl_loc_schd_1bitpthdrvr(struct net_t *np, int32 biti,
 struct tev_t *ptevp)
{
 word32 nval, oval;
 word32 is_stren;
 word64 schtim;
 struct rngdwir_t *dwirp; 
 struct pthdst_t *pdp;

 dwirp = np->nu.rngdwir;

 /* DBG remove ---
 if (tevp != -1 && tevp->enterptr != __process_trpthdsdt_ev)
  __misc_terr(__FILE__, __LINE__);
 --- */

 nval = __new_gateval;
 oval = __old_gateval; 

 /* since always use last changed value, if last same as current */
 /* because gate style glitch nothing to do since already right value */   
 if (!ptevp->trigger && nval == oval)
  return(FALSE);

 is_stren = np->n_stren;

 /* possible for some bits to not be path destinations */
 if (oval != nval)
  {
   if ((pdp = asl_loc_get_path_del(dwirp, biti, &schtim)) == NULL)
    return(TRUE);   
  }
 else { pdp = NULL; schtim = 0ULL; }

 /* special case 0 - distributed delay longer - immediate assign */
 /* normal cause is path (probably from multiple input final driving gate) */
 /* that has not path delay on it - this may be ok */
 if (pdp != NULL && schtim <= __simtime)
  {
   /* problem with modeling - distributed delay longer than path */
   if (!__no_informs) __emit_path_distinform(np, pdp, &__pdmindel);

   /* modeling anomally style spike possible - know immed. assign earlier */ 
   if (ptevp->trigger)
    {
     /* calls here take ptr not index */
     if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
      {
       __emit_path_pulsewarn(pdp, ptevp, &__simtime, &(ptevp->etime),
        "distributed longer or no path delay", is_stren);
      }
     /* always cancel pending */
     linkout_tevp(ptevp);

     /* this is same for on detect and on event */
     if (__show_cancel_e)
      {
       /* this is special case where immediate assign must be to x */ 
       /* and cancel future event that can be scheduled for now */
set_on_detect_x:
       /* set global causes use in tran channel re-eval */
       if (is_stren) __new_gateval = (word32) ST_STRONGX;
       else __new_gateval = (word32) 3;
       return(TRUE);
      }
     /* if no show canceled e, just assign later */  
    }
   /* no schedule, distributed longer - global new gateval right and used */
   return(TRUE);
  }

 /* no pending event */
 /* SJM 11/24/00 - know if no pending event will have path */
 if (!ptevp->trigger)
  {
   /* because no pending event must be different */
   asl_loc_schedule_1wev(biti, ptevp, __pdmindel, schtim, nval);
   return(FALSE);
  }    
 /* pending event */
 /* new and old same but know scheduled different - classic pulse/glitch */
 if (nval == oval)
  {
   /* have delay to use to select pa0th */  
   if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
    {
     __emit_path_samewarn(np, biti, ptevp, &(ptevp->etime), "pulse",
      is_stren);
    }
   
   /* if spike, suppress future but schedule to x at currently scheduled */
   if (__show_cancel_e)
    {
     if (__showe_onevent)
      { ptevp->outv = (is_stren) ? ST_STRONGX : 3; return(FALSE); }

     linkout_tevp(ptevp);
     goto set_on_detect_x;
    }
   /* remove pulse */
   linkout_tevp(ptevp);
   return(FALSE);
  }

 /* now know pdp set */

 /* new schedule to same value case */
 /* here delay can be different because different path selected */
 /* and maybe other reasons */
 /* done silently here - trace message only below */
 if (ptevp->outv == (byte) nval) return(FALSE);

 /* inertial reschedule */
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), &schtim,
   "inout unstable", is_stren);   

 /* easy show cancel (set to x case) - no new event may or may not switch */
 if (__show_cancel_e)
  {
   /* LOOKATME - maybe need to check old tevp and new schd time and if 2nd */
   /* input change results in earlier edge cancel and schedule earlier */
   if (__showe_onevent)
    { ptevp->outv = (is_stren) ? ST_STRONGX : 3; return(FALSE); }

   linkout_tevp(ptevp);
   goto set_on_detect_x;
  }
 /* inertial reschedule, this handles cancel if needed */
 asl_loc_reschedule_1wev(ptevp, nval, schtim);
 return(FALSE);
}

/*
 * AIV 11/06/07 - local version of __eval_tran_1bit - compiler needs to 
 * pass down compiled nchg action pointer
 */
/* LOOKATME - is it known that drivers always change here? */
extern void __asl_eval_tran_1bit(struct net_t *np, int32 bi)
{
 int32 base;
 struct traux_t *trap;
 struct vbinfo_t *vbip;
 int32 inum;

 trap = np->ntraux;
 /* SJM 04/23/01 - all channels now per inst, no extra cost for 1 inst mod */
 inum = get_inum_();
 base = inum*np->nwid;

 /* all others are per bit */
 /* bit of wire is not really in any tran channel - treated as 1 wire */
 /* tran channel - just access stored internal hard trnva value */
 vbip = trap->vbitchans[base + bi];
 /* real tran switch chan - use change vertex to perturb and relax chan */
 __cvc_eval_update_1w_tranchan(vbip->vivxp);
 /* AIV 11/20/07 - this list changes at runtime so vtx_t contain net change */
 if (__chg_vtxlst_hdr != NULL) asl_loc_assign_chged_vtxs();
}

/*
 * AIV 01/30/12 - there is no reason to pass each bit - added vector version
 */
extern void __asl_eval_tran_vector(struct net_t *np)
{
 int32 base, bi;
 struct traux_t *trap;
 struct vbinfo_t *vbip;
 int32 inum;

 trap = np->ntraux;
 inum = get_inum_();
 base = inum*np->nwid;
 for (bi = np->nwid - 1; bi >= 0; bi--) 
  {
   /* SJM 04/23/01 - all channels now per inst, no extra cost for 1 inst mod */

   /* all others are per bit */
   /* bit of wire is not really in any tran channel - treated as 1 wire */
   /* tran channel - just access stored internal hard trnva value */
   vbip = trap->vbitchans[base + bi];
   /* real tran switch chan - use change vertex to perturb and relax chan */
   __cvc_eval_update_1w_tranchan(vbip->vivxp);
   /* AIV 11/20/07 - this list changes at runtime so vtx_t contain net change */
   if (__chg_vtxlst_hdr != NULL) asl_loc_assign_chged_vtxs();
  }
}

/*
 *
 */
static void asl_loc_assign_chged_vtxs(void)
{
 int32 bi, bi2;
 word32 sbv;
 byte *sbp2;
 struct vtxlst_t *vtxlp;
 struct vtx_t *vtxp;
 struct nchglst_t *nchglp;
 struct net_t *np;
 decl_idp_locals_;

 save_idp_();
 for (vtxlp = __chg_vtxlst_hdr; vtxlp != NULL; vtxlp = vtxlp->vtxnxt)
  {
   set_idp_(vtxlp->vtx_itp->it_idp);

   vtxp = vtxlp->vtxp;
   np = vtxp->vnp;
   bi = vtxp->vi1;
   bi2 = (bi == -1) ? 0 : bi;
   /* sbp2 of index is addr to store new net value into */
   sbp2 = (byte *) &(__idp[np->nva_ofs]);
   /* sbv is new value to store */
   sbv = (word32) vtxp->new_vtxval;
   /* for next relax old value is current node val, old val no longer need */
   vtxp->old_vtxval = vtxp->new_vtxval;

   /* know if vertex forced will never be on change list */

   /* this may change sbv from tran channel new value to trireg value */ 
   /* SJM 10/16/00 - this was commented out but that caused Samsung trireg */
   /* tests to fail - must have had a reason to comment out but why? */
   if (np->ntyp == N_TRIREG)
    {
     if (sbv == ST_HIZ)
      sbv = (byte) ((sbp2[bi2] & 3) | __cap_to_stren[np->n_capsiz]);
    }
   if (sbv != (word32) sbp2[bi2])
    {
     sbp2[bi2] = (byte) sbv;

     /* notice needs to be bi since need -1 if scalar */
     /* always record since this assign does not set lhs changed */ 
     if ((nchglp = vtxp->nchgp) != NULL)
      {
       asl_loc_record_nchg(np, nchglp);
      }
    } 
   vtxlp->vtxp->vtx_chged = FALSE;
  }
 restore_idp_();
 /* add entire list to end of free list */
 if (__chg_vtxlst_hdr != NULL)
  {
   __chg_vtxlst_end->vtxnxt =  __vtxlst_freelst; 
   __vtxlst_freelst = __chg_vtxlst_hdr;
  }
 __chg_vtxlst_hdr = __chg_vtxlst_end = NULL;
}

extern word32 __asl_eval_tran_bidchan_1bit(int32 chan_id)
{
 word32 av;
 struct chanrec_t *chanp;

 chanp = &(__chantab[chan_id]);
 av = asl_loc_eval_combine_bid_chan(chanp);
 /* AIV 11/08/07 - the b part (resb) always goes into ECX */
 /* AIV LOOKATME BEWARE - machine dependent - but most of bbgen3 is as well */
 /* but bval into ecx */
#ifdef __CVC32__
 __asm__ ("movl %0, %%ecx" : : "g" (__acum_b));
#else
 __asm__ ("movq %0, %%rcx" : : "g" (__acum_b));
#endif
 return(av);
}

/*
 * same as above except know it is assigning to a scalar so pack it here
 */
extern word32 __asl_eval_tran_scalar_bidchan_1bit(int32 chan_id)
{
 word32 av, bv, sval;
 struct chanrec_t *chanp;

 chanp = &(__chantab[chan_id]);
 av = asl_loc_eval_combine_bid_chan(chanp);
 bv = (word32) __acum_b;
 sval = av | (bv << 1);
 return(sval);
}

extern word32 __asl_eval_tran_stbidchan_1bit(int32 chan_id)
{
 struct chanrec_t *chanp;

 chanp = &(__chantab[chan_id]);
 return(asl_loc_eval_combine_stbid_chan(chanp));
}

/*
 *  AIV 01/30/12 - wrapper which does the tran channel assigning as well 
 *  was producing too much code
 */
extern void __asl_eval_tran_bidchan_1bit_assign(int32 chan_id)
{
 struct chanrec_t *chanp;

 chanp = &(__chantab[chan_id]);
 asl_loc_eval_assign_bid_chan(chanp);
}

/*
 *  AIV 01/30/12 - wrapper which does the tran channel assigning as well 
 *  was producing too much code
 */
extern void __asl_eval_tran_stbidchan_1bit_assign(int32 chan_id)
{
 struct chanrec_t *chanp;

 chanp = &(__chantab[chan_id]);
 asl_loc_eval_assign_stbid_chan(chanp);
}

/*
 *  AIV 02/19/12 - new vectored wrapper inout assigned 
 */
extern void __asl_eval_tran_bidchan_vectored_assign(struct net_t *np)
{
 int32 inum, base;
 struct vbinfo_t *vbip;
 struct traux_t *trap;
 struct chanrec_t *chanp;

 trap = np->ntraux;
 inum = get_inum_();
 base = inum*np->nwid;
 vbip = trap->vbitchans[base];
 chanp = &(__chantab[vbip->chan_id]);
 asl_loc_vec_eval_assign_bid_chan(chanp);
}

/*
 *
 */
extern void __asl_eval_tran_stbidchan_vectored_assign(struct net_t *np)
{
 int32 inum, base;
 struct vbinfo_t *vbip;
 struct traux_t *trap;
 struct chanrec_t *chanp;

 trap = np->ntraux;
 inum = get_inum_();
 base = inum*np->nwid;
 vbip = trap->vbitchans[base];
 chanp = &(__chantab[vbip->chan_id]);
 asl_loc_vec_eval_assign_stbid_chan(chanp);
}


static void asl_loc_vec_eval_assign_bid_chan(struct chanrec_t *chanp) 
{
 int32 vi;
 struct bidvtx_t *bidvtxp; 
 struct net_t *np;
 struct xstk_t *xsp, *acc_xsp;
 decl_idp_locals_;
 
 save_idp_();

 bidvtxp = &(chanp->bid_vtxtab[0]);
 np = bidvtxp->vnp;
 push_xstk_(acc_xsp, np->nwid);
 /* initialize accumulator to all z's */ 
 zero_allbits_(acc_xsp->ap, np->nwid);
 one_allbits_(acc_xsp->bp, np->nwid);

 push_xstk_(xsp, np->nwid);
 /* first eval all contributors to the one new value */
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);
   np = bidvtxp->vnp;

#ifdef __CVC_DEBUG__
   /* DBG remove -- */
   if (bidvtxp->vi1 != -1) __misc_terr(__FILE__, __LINE__);
   if (np->frc_assgn_allocated) __misc_terr(__FILE__, __LINE__);
   if (!np->n_isavec) __misc_terr(__FILE__, __LINE__);
   /* -- */
#endif

   __ld_perinst_val(xsp->ap, xsp->bp, np->ntraux->trnva, np->nwid);
   __eval_wide_wire(acc_xsp->ap, acc_xsp->bp, xsp->ap, xsp->bp,
    np->nwid, np->ntyp);
  }
 __pop_xstk();
 /* then assign it to every vertex */
 bidvtxp = &(chanp->bid_vtxtab[0]);
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);
   np = bidvtxp->vnp;
   if (np->nchg_nd_chgstore) __chg_st_val(np, acc_xsp->ap, acc_xsp->bp);
   else __st_val(np, acc_xsp->ap, acc_xsp->bp, acc_xsp->xslen);
  }
 __pop_xstk();
 restore_idp_();
}

static void asl_loc_vec_eval_assign_stbid_chan(struct chanrec_t *chanp)
{
 int32 vi, inum;
 byte *sbp, *acc_sbp;
 struct net_t *np;
 struct bidvtx_t *bidvtxp; 
 struct xstk_t *xsp;
 decl_idp_locals_;

 save_idp_(); 
 bidvtxp = &(chanp->bid_vtxtab[0]);
 /* need to build a first bid vertex width accumulator */
 push_xstk_(xsp, 4*bidvtxp->vnp->nwid);
 acc_sbp = (byte *) xsp->ap;
 set_byteval_(acc_sbp, bidvtxp->vnp->nwid, ST_HIZ); 

 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);

   np = bidvtxp->vnp;
#ifdef __CVC_DEBUG__
   /* DBG remove -- */
   if (bidvtxp->vi1 != -1) __misc_terr(__FILE__, __LINE__);
   if (np->frc_assgn_allocated) __misc_terr(__FILE__, __LINE__);
   if (!np->n_isavec) __misc_terr(__FILE__, __LINE__);
   /* -- */
#endif
   inum = get_inum_();
   sbp = &(np->ntraux->trnva.bp[inum*np->nwid]);
   __eval_stwire(acc_sbp, np->ntyp, np->nwid - 1, 0, sbp);
  }

 /* then assign it to every vertex */
 bidvtxp = &(chanp->bid_vtxtab[0]);
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);
   np = bidvtxp->vnp;
   if (np->nchg_nd_chgstore) __chg_st_val(np, (word32 *) acc_sbp, 0L);
   /* SJM 02-12-13 - know rhs width is net width here */   
   else __st_val(np, (word32 *) acc_sbp, 0L, np->nwid);
  }
 __pop_xstk();
 restore_idp_();
}



/*
 * local do tran channel assign
 */
static void asl_loc_eval_assign_bid_chan(struct chanrec_t *chanp) 
{
 int32 vi, bi, bi2, inum;
 word32 nav, nbv; 
 struct bidvtx_t *bidvtxp; 
 struct net_t *np;
 decl_idp_locals_;
 
 /* initialize to 2 (hiz) */
 __acum_a = 0;
 __acum_b = 1;

 /* first eval all contributors to the one universal new value */
 /* uses global accum - in gcc global access faster */
 save_idp_();
 bidvtxp = &(chanp->bid_vtxtab[0]);
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);
   np = bidvtxp->vnp;
   bi = bidvtxp->vi1;
   bi2 = (bi == -1) ? 0 : bi;
   inum = get_inum_();
   if (np->frc_assgn_allocated
    && np->nu2.qcval[inum*np->nwid + bi2].qc_active)
    {
     if (bi == -1) ld_scalval_(&nav, &nbv, __idp[np->nva_ofs]);
     else __ld_bit(&nav, &nbv, np, bi);
    }
   else asl_loc_ld_vtx_netbit(&nav, &nbv, np, bi);
   //AIV 2-STATE think this just needs to orin the value here
   __eval_1w_nonstren(&__acum_a, &__acum_b, nav, nbv, np->ntyp);
   /* AIV 08/24/10 - if storing 2-state skip the b value here */
   if (np->n_2state) __acum_b = 0;
  }
 
 bidvtxp = &(chanp->bid_vtxtab[0]);
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);
   np = bidvtxp->vnp;
   bi = bidvtxp->vi1;
   asl_loc_assign_1tranbit(np, bi, __acum_a, __acum_b);
  }

 restore_idp_();
}

static void asl_loc_eval_assign_stbid_chan(struct chanrec_t *chanp)
{
 int32 vi, bi, inum;
 word32 sb2;
 struct bidvtx_t *bidvtxp; 
 struct net_t *np;
 byte *bp;
 decl_idp_locals_;

 /* first eval all contributors to the one universal new value */
 __acum_sb = ST_HIZ;
 save_idp_(); 
 bidvtxp = &(chanp->bid_vtxtab[0]);
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);

   np = bidvtxp->vnp;
   bi = bidvtxp->vi1;
   bi = (bi == -1) ? 0 : bi;
   /* SJM - 03/15/00 - if wire is forced, use its values as "driving" val */
   inum = get_inum_();
   if (np->frc_assgn_allocated && np->nu2.qcval[inum*np->nwid + bi].qc_active)
    {
     bp = (byte *) &(__idp[np->nva_ofs]);
     sb2 = bp[bi];
    }
   else sb2 = np->ntraux->trnva.bp[inum*np->nwid + bi];
   __acum_sb = (word32) __comb_1bitsts(np->ntyp, __acum_sb, sb2);
  }


 bidvtxp = &(chanp->bid_vtxtab[0]);
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);

   np = bidvtxp->vnp;
   bi = bidvtxp->vi1;
   asl_loc_stassign_1tranbit(np, bi, __acum_sb);
  }

 restore_idp_();
}


/*
 * AIV 01/30/12 - this is bad since it uses wrappers for the net changes
 * but need for modules with a large number of instances since this produces
 * a lot of code
 */
static void asl_loc_assign_1tranbit(struct net_t *np, int32 bi, word32 nav, 
 word32 nbv)
{
 int32 inum;
 word32 t1;

 /* non stren case */ 
 if (bi == -1) bi = 0;
 /* tran channel elements in P1364 can not have wire delays */
 /* no meaning since drivers of all in channel and wires must be same */

 /* SJM 06/02/99 - will have DWIR and no path if all 0 paths removed */
 /* to optimize invalidating internal consistency check */

 /* for path dest., need immediate assign - internal hard driver value */
 /* change is delayed */
 /* AIV 08/24/10 - if storing 2-state skip the b value here */
 if (np->n_2state) 
  {
   t1 = ~nbv;
   nav = nav & t1;
   nbv = 0;
  }

 /* if wire bit forced (qcval inst non nil), must not assign to wire */
 inum = get_inum_();
 if (np->frc_assgn_allocated
  && np->nu2.qcval[inum*np->nwid + bi].qc_active)
  {
   return;
  }

 /* AIV 11/06/07 - only record the net change if needed */
 if (!np->n_isavec) 
  {
   if (np->nchg_nd_chgstore) __chg_st_val(np, &nav, &nbv);
   else __st_val(np, &nav, &nbv, np->nwid);
  }
 else
  {
   if (np->nchg_nd_chgstore) __chg_st_bit(np, bi, nav, nbv);
   else __chg_st_bit(np, bi, nav, nbv);
  }
}

/*
 * AIV 01/30/12 - this is bad since it uses wrappers for the net changes
 * but need for modules with a large number of instances since this produces
 * a lot of code
 */
static void asl_loc_stassign_1tranbit(struct net_t *np, int32 bi, word32 sbv)
{
 int32 bind, inum;
 byte *sbp2;

 bind = (bi == -1) ? 0 : bi;

 /* get strength wire address */
 sbp2 = (byte *) &(__idp[np->nva_ofs]);

 /* tran channel elements in P1364 can not have wire delays */
 /* no meaning since drivers of all in channel and wires must be same */
 /* SJM 06/02/99 - will have DWIR and no path if all 0 paths removed */
 /* to optimize invalidating internal consistency check */

 /* stren non delay wire */ 
 /* if bit forced, must not assign */
 inum = get_inum_();
 if (np->frc_assgn_allocated
  && np->nu2.qcval[inum*np->nwid + bind].qc_active)
   { 
    return;
   }

 /* this may change sbv from tran channel new value to trireg value */ 
 /* SJM 10/16/00 - this was commented out but that caused Samsung trireg */
 /* tests to fail - must have had a reason to comment out but why? */
 /* --- */
 if (np->ntyp == N_TRIREG)
  {
   if (__wire_init) sbv = (byte) (3 | __cap_to_stren[np->n_capsiz]);
   else 
    {  
     if (sbv == ST_HIZ)
      sbv = (byte) ((sbp2[bind] & 3) | __cap_to_stren[np->n_capsiz]);
    }
  }

 if (sbv != (word32) sbp2[bind])
  {
   sbp2[bind] = (byte) sbv;
   /* notice needs to be bi since need -1 if scalar */
   /* always record since immediate assign - no setting of lhs changed */ 
   /* SJM 08/24/03 - and no need to now since this resets anyway */
   /* AIV 11/06/07 - only record the net change if needed */
   if (np->nchg_nd_chgstore) record_sel_nchg_(np, bi, bi);
  }  
}


extern void __asl_eval_htran_wire_1bit(struct net_t *np, int32 bi)
{
 word32 nav, nbv, uwrd;
 int32 inum;
 
 asl_loc_ld_vtx_netbit(&nav, &nbv, np, bi);

 inum = get_inum_();
 if (np->frc_assgn_allocated
  && np->nu2.qcval[inum*np->nwid + bi].qc_active)
  {
   /* need not pass bi -1 since checks separately for scalar net */
   return;
  }

 /* known not to contain strength here */
 if (!np->n_isavec) 
  {
   /* this is SR_SCAL case */
   uwrd = nav | (nbv << 1);
   __idp[np->nva_ofs] = uwrd;
  }
 else 
  {
   /* SR_VEC case */
   __st_bit(np, bi, nav, nbv);
  }
}

extern void __asl_eval_htran_wire_1bit_nchg(struct net_t *np, 
 struct nchglst_t *nchglp, int32 bi)
{
 word32 nav, nbv, uwrd;
 int32 inum, lhs_changed;
 word32 *rap;


 asl_loc_ld_vtx_netbit(&nav, &nbv, np, bi);

 inum = get_inum_();
 if (np->frc_assgn_allocated
  && np->nu2.qcval[inum*np->nwid + bi].qc_active)
  {
   /* need not pass bi -1 since checks separately for scalar net */
   return;
  }

 /* known not to contain strength here */
 if (!np->n_isavec) 
  {
   /* this is SR_SCAL case */
   uwrd = nav | (nbv << 1);
   if (__idp[np->nva_ofs] != uwrd)
    {
     __idp[np->nva_ofs] = uwrd;
     asl_loc_record_nchg(np, nchglp);
    }
  }
 else 
  {
   /* SR_VEC case */
   rap = &(__idp[np->nva_ofs]);
   lhs_changed = asl_loc_chg_vec_lhsbsel(rap, bi, nav, nbv, np->nwid);
   if (lhs_changed) asl_loc_record_nchg(np, nchglp);
  }
}

extern void __asl_eval_htran_stwire_1bit(struct net_t *np, int32 bi)
{
 word32 sbv;
 struct traux_t *trap;
 int32 inum;
 byte *sbp2;

 trap = np->ntraux;
 /* SJM 04/23/01 - all channels now per inst, no extra cost for 1 inst mod */
 inum = get_inum_();
 sbv = (word32) trap->trnva.bp[inum*np->nwid + bi];
 /* really unused but passing it */
 /* notice if strength, nbv not used */

 inum = get_inum_();
 if (np->frc_assgn_allocated
  && np->nu2.qcval[inum*np->nwid + bi].qc_active)
   { 
    return;
   }

 sbp2 = (byte *) &(__idp[np->nva_ofs]);
 if (np->ntyp == N_TRIREG)
  {
   if (sbv == ST_HIZ)
      sbv = (byte) ((sbp2[bi] & 3) | __cap_to_stren[np->n_capsiz]);
  }

 sbp2[bi] = (byte) sbv;
}

extern void __asl_eval_htran_stwire_1bit_nchg(struct net_t *np, 
 struct nchglst_t *nchglp, int32 bi)
{
 word32 sbv;
 struct traux_t *trap;
 int32 inum;
 byte *sbp2;

 trap = np->ntraux;
 /* SJM 04/23/01 - all channels now per inst, no extra cost for 1 inst mod */
 inum = get_inum_();
 sbv = (word32) trap->trnva.bp[inum*np->nwid + bi];
 /* really unused but passing it */
 /* notice if strength, nbv not used */

 if (np->frc_assgn_allocated
  && np->nu2.qcval[inum*np->nwid + bi].qc_active)
   { 
    return;
   }

 sbp2 = (byte *) &(__idp[np->nva_ofs]);
 if (np->ntyp == N_TRIREG)
  {
   if (sbv == ST_HIZ)
      sbv = (byte) ((sbp2[bi] & 3) | __cap_to_stren[np->n_capsiz]);
  }

 if (sbv != (word32) sbp2[bi])
  {
   sbp2[bi] = (byte) sbv;
   asl_loc_record_nchg(np, nchglp);
  }  
}


static void asl_loc_ld_vtx_netbit(word32 *ap, word32 *bp, struct net_t *np,
 int32 bi)
{
 int32 inum;
 struct xstk_t *xsp;

 if (!np->n_isavec)
  {
   inum = get_inum_();
   ld_peri_scalval_(ap, bp, np->ntraux->trnva.bp); 
  }
 else
  {
   /* know bi not -1 since vector */ 
   push_xstk_(xsp, np->nwid);
   __ld_perinst_val(xsp->ap, xsp->bp, np->ntraux->trnva, np->nwid);
   ap[0] = rhsbsel_(xsp->ap, bi);
   bp[0] = rhsbsel_(xsp->bp, bi);
   __pop_xstk();
  }
}

/*
 * return qc_active value
 */
extern int32 __asl_qc_active(struct net_t *np, int32 bi)
{
 int32 inum;

 inum = get_inum_();
 return(np->nu2.qcval[inum*np->nwid + bi].qc_active);
}

static word32 asl_loc_eval_combine_bid_chan(struct chanrec_t *chanp) 
{
 int32 vi, bi, bi2, inum;
 word32 nav, nbv; 
 struct bidvtx_t *bidvtxp; 
 struct net_t *np;
 decl_idp_locals_;
 
 /* initialize to 2 (hiz) */
 __acum_a = 0;
 __acum_b = 1;

 /* first eval all contributors to the one universal new value */
 /* uses global accum - in gcc global access faster */
 save_idp_();
 bidvtxp = &(chanp->bid_vtxtab[0]);
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);
   np = bidvtxp->vnp;
   bi = bidvtxp->vi1;
   bi2 = (bi == -1) ? 0 : bi;
   inum = get_inum_();
   if (np->frc_assgn_allocated
    && np->nu2.qcval[inum*np->nwid + bi2].qc_active)
    {
     if (bi == -1) ld_scalval_(&nav, &nbv, __idp[np->nva_ofs]);
     else __ld_bit(&nav, &nbv, np, bi);
    }
   else asl_loc_ld_vtx_netbit(&nav, &nbv, np, bi);
   //AIV 2-STATE think this just needs to orin the value here
   __eval_1w_nonstren(&__acum_a, &__acum_b, nav, nbv, np->ntyp);
   /* AIV 08/24/10 - if storing 2-state skip the b value here */
   if (np->n_2state) __acum_b = 0;
  }

 restore_idp_();
 return(__acum_a);
}

static word32 asl_loc_eval_combine_stbid_chan(struct chanrec_t *chanp)
{
 int32 bi, vi, inum;
 word32 sb2;
 byte *bp;
 struct bidvtx_t *bidvtxp; 
 struct net_t *np;
 decl_idp_locals_;

 /* first eval all contributors to the one universal new value */
 __acum_sb = ST_HIZ;
 save_idp_(); 
 bidvtxp = &(chanp->bid_vtxtab[0]);
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   set_idp_(bidvtxp->bidvtx_itp->it_idp);

   np = bidvtxp->vnp;
   bi = bidvtxp->vi1;
   bi = (bi == -1) ? 0 : bi;
   /* SJM - 03/15/00 - if wire is forced, use its values as "driving" val */
   inum = get_inum_();
   if (np->frc_assgn_allocated && np->nu2.qcval[inum*np->nwid + bi].qc_active)
    {
     bp = (byte *) &(__idp[np->nva_ofs]);
     sb2 = bp[bi];
    }
   else sb2 = np->ntraux->trnva.bp[inum*np->nwid + bi];
   __acum_sb = (word32) __comb_1bitsts(np->ntyp, __acum_sb, sb2);
  }

 restore_idp_();
 return((word32) __acum_sb);
}

/* 
 * trireg adjust wrapper
 * code from v_ex4.c:__assign_1mdrwire
 */
extern void __asl_adjust_trireg(byte *sbp, byte *abp, int32 nwid, word32 cstren)
{ 
 int32 sbi;

 for (sbi = 0; sbi < nwid; sbi++)
  {
   if (sbp[sbi] == ST_HIZ)
     sbp[sbi] = (byte) ((abp[sbi] & 3) | cstren);
  }
}

/*
 * asm routine to load non stren PLI 1.0 tf rw arg driver
 *
 * SJM 06/20/05 - needed because npp not fixed adr - could use RT __cur npp? 
 */
extern void *__asl_ld_tfrwarg_drvp(struct net_pin_t *npp)
{
 struct tfrec_t *tfrp;
 struct tfarg_t *tfap;

 tfrp = npp->elnpp.etfrp;
 tfap = &(tfrp->tfargs[npp->obnum]);
 return((void *) tfap->tfdrv_wp.bp);
}

/*
 * wrapper to call ld perinst val routine - just separates result a/b ptrs
 */
//AIV FIXME - need to lower this code in v_bbgen
extern void __asl_get_perinst_val(word32 *wp, union pck_u drv_wp, int32 blen) 
{
 word32 *wpb;

 wpb = &(wp[wlen_(blen)]);
 __ld_perinst_val(wp, wpb, drv_wp, blen);
}

/* SJM 04/20/07 removed asl st sttfrwarg driver wrapper - never needed */

/*
 * ASM LIB ROUTINES FOR WIRE DELAY SCHEDULING
 */

/*
 *
 */
extern void __asl_wdel_trireg_sched_hiz(struct net_t *np, byte *nsbp, 
 word32 oval, int32 biti, struct tev_t *ptevp)
{
 word64 ndel, schtim;
 word32 nval;

 /* need to get the byte value of the byte passed as word */
 oval = oval & 0xff;
 /* schedule decay to cap. size x value change if z delay not 0 */
 /* trireg charge decay time is third to-z delay - 0 means never */
 /* decays to z */
 __new_gateval = 2;
 __old_gateval = oval;
 /* index in get_del removes any indexing */
 ndel = __get_del(np->nu.rngdwir->n_du, np->nu.rngdwir->n_delrep);
 if (ndel == 0ULL) return;
 *nsbp = (3 | __cap_to_stren[np->n_capsiz]);
 
 nval = (word32) *nsbp;
 /* AIV 11/27/07 - inline the __asl_wdel_schd_1wirebit with decay T */
 /* since always use last changed value, if last same as current */
 /* because gate style spike nothing to do since already right value */   
 if (!ptevp->trigger && nval == oval) return;

 /* normal wire delay */
 /* notice old and new gate values always set before here */
 schtim = __simtime + ndel;

 if (!ptevp->trigger)
  {
   /* if nothing pending can just schedule */
   /* decay flag passed as TRUE */
   asl_loc_schedule_1wev(biti, ptevp, ndel, schtim, nval);
   return;
  }

 /* there is a pending unmatured event */
 /* case 1: real pulse (aka spike or glitch) just cancel */ 
 if (nval == oval)
  {
   /* cancel */
   linkout_tevp(ptevp);
  }
 /* this handles cancel too */
 else asl_loc_reschedule_1wev(ptevp, nval, schtim);
}


/*
 * asm routine wrapper to schedule unkown stren bit to vector (or scalar)
 * wrapper than schedules to x eval different bit since do not know index
 */
extern void __asl_stren_sched_unknown_bit(struct net_t *np, word32 nscal,
 byte *osbp, struct nchglst_t *nchglp, struct tev_t *tevp)
{
 int32 i;
 word32 newval;

//AIV HERE - AIV FIXME - cannot be right need to unroll loop - diff nchglps
__misc_terr(__FILE__, __LINE__);
///////////

 /* SJM 07/21/05 - for compiler, this global not always set */
 __lhs_changed = FALSE;
 for (i = 0; i < np->nwid; i++)
  {
   if (osbp[i] != (byte) nscal) newval = (word32) ST_STRONGX;
   else newval = nscal;

   if (newval != (word32) osbp[i])
    {
     if (np->nu.rngdwir->n_delrep == DT_PTHDST)
      {
       __asl_schd_st_1pthwirebit(np, i, newval, (word32) osbp[i], nchglp,
        tevp);
      }
     else 
      {
       __asl_wdel_schd_1wirebit(np, i, newval, (word32) osbp[i], tevp);
      }
    }
  }
 if (__lhs_changed) asl_loc_record_nchg(np, nchglp);
}

/*
 * AIV 08/29/06 - almost same as __wdel_schd_1wirebit in v_ex3.c
 * need to use different enter addresses for asl process calls
 */
extern void __asl_wdel_schd_1wirebit(struct net_t *np, int32 biti, 
 word32 nval, word32 oval, struct tev_t *ptevp)
{
 word64 ndel, schtim;
 struct rngdwir_t *dwirp; 

 /* since always use last changed value, if last same as current */
 /* because gate style spike nothing to do since already right value */   
 if (!ptevp->trigger && nval == oval) return;

 /* get delay and if path delay immediate (distributed longer) store */
 /* globals must be set for get del routine */
 __old_gateval = oval;
 /* notice new gateval is not value set but to-z needed for get del */
 __new_gateval = nval;

 /* normal wire delay */
 /* notice old and new gate values always set before here */
 dwirp = np->nu.rngdwir;
 ndel = __get_del(dwirp->n_du, dwirp->n_delrep);
 schtim = __simtime + ndel;

 if (!ptevp->trigger)
  {
   /* if nothing pending can just schedule */
   asl_loc_schedule_1wev(biti, ptevp, ndel, schtim, nval);
   return;
  }

 /* there is a pending unmatured event */
 /* case 1: real pulse (aka spike or glitch) just cancel */ 
 if (nval == oval)
  {
   /* cancel */
   linkout_tevp(ptevp);
  }
 /* this handles cancel too */
 else asl_loc_reschedule_1wev(ptevp, nval, schtim);
} 


/*
 *
 */
static void asl_loc_schedule_1wev(int32 bi, struct tev_t *tevp,
 word64 ndel, word64 schtim, word32 newval)
{

 tevp->etime = schtim;
 if (ndel == 0ULL)
  {
   /* this is #0, but must still build tev */
   asl_loc_add_pnd0_event(tevp);
  }
 else asl_loc_insert_event_(tevp);
 tevp->outv = (byte) newval;
 tevp->tu.bi = bi;
 tevp->trigger = TRUE;
}

/*
 *
 */
extern void __asl_schd_scalar_1wev(struct tev_t *tevp)
{
 /* AIV 01/16/12 - this can never happen here for path delay */
 /* __get_path_delay takes last change time plus delay which is zero */
 /* will just do the assign if (pdp != NULL && schtim <= __simtime) */
 /*
 if (__pdmindel == 0ULL)
  {
   asl_loc_add_pnd0_event(tevp);
  }
 else asl_loc_insert_event_(tevp);
 */
 asl_loc_insert_event_(tevp);
 tevp->trigger = TRUE;
 tevp->outv = (byte) __new_gateval;
}

/*
 *
 */
extern void __asl_schd_1wev(struct tev_t *tevp, int32 bi)
{
 /* AIV 01/16/12 - this can never happen here for path delay */
 /* __get_path_delay takes last change time plus delay which is zero */
 /* will just do the assign if (pdp != NULL && schtim <= __simtime) */
 /*
 if (__pdmindel == 0ULL)
  {
   asl_loc_add_pnd0_event(tevp);
  }
 else asl_loc_insert_event_(tevp);
 */
 asl_loc_insert_event_(tevp);
 tevp->trigger = TRUE;
//AIV FIXME - these should be init in fixed events no reason to set here
//could then just use one wrapper 
 tevp->tu.bi = bi;
 tevp->outv = (byte) __new_gateval;
}

/*
 *
 */
static void asl_loc_reschedule_1wev(struct tev_t *tevp, word32 newval, 
 word64 newtim)
{
 /* if del == 0 (pnd0), will always be same time reschedule */
 /* AIV 02/03/09 - better to just check time to see if it is the same */
 /* this is the same as checking 0 and no cancel/schd is needed */
 tevp->outv = (byte) newval;
 if (tevp->etime == newtim) return;

 linkout_tevp(tevp);
 tevp->etime = newtim;
 asl_loc_insert_event_(tevp);
 tevp->trigger = TRUE;
}

/*
 *
 */
extern void __asl_reschd_1wev(struct tev_t *tevp, word64 newtim)
{
 /* if del == 0 (pnd0), will always be same time reschedule */
 /* AIV 02/03/09 - better to just check time to see if it is the same */
 /* this is the same as checking 0 and no cancel/schd is needed */
 if (tevp->etime == newtim) 
  {
   tevp->outv = (byte) __new_gateval;
   return;
  }

 if (tevp->outv == __new_gateval) return;

 linkout_tevp(tevp);
 tevp->etime = newtim;
 asl_loc_insert_event_(tevp);
 tevp->trigger = TRUE;
 tevp->outv = (byte) __new_gateval;
}


/*
 * asm routine wrapper to schedule unkown bit to vector (or scalar)
 * (non stren version)
 *
 * wrapper than schedules to x eval different bit since do not know index
 * know rhsap the 1 bit rhs new value but in ptr to a/b form
 */
extern void __asl_sched_unknown_bit(struct net_t *np, word32 *rhsap)
{
 /* SJM 07/21/05 - is there a need to set lhs change to F here? */ 
 __schedorassign_unknown_bit(np, rhsap[0], rhsap[1], TRUE);
}

/*
 * simple byte cmp wrapper
 */
extern int32 __asl_bytecmp(byte *b1, byte *b2, int32 bsize) 
{
 int32 rval; 

 rval = memcmp(b1, b2, bsize);
 return(rval);
}

/*
 * simple word cmp wrapper
 */
extern int32 __asl_wordcmp(word32 *w1, word32 *w2, int32 wlen) 
{
 int32 i; 

 for (i = 0; i < wlen; i++)
  {
   if (w1[i] != w2[i]) return(TRUE);
  }
 return(FALSE);
}

/* SJM 04/20/07 - removed wrapper for asl rhspsel */

//////////////////////AIV NEW PLI INSNS
/*
 * process all vpi put values off front of the np->ndrvs list
 * uses the same code from v_sim
 *
 * SJM 04/20/07 - A WPTR now must be first arg and only one allowed
 */
extern void __asl_chk_ld_vpiputv_driver(word32 *accum_ap, struct net_t *np)
{
 struct net_pin_t *npp;
 struct xstk_t *xsp, *tmpxsp;
 int32 lhswid, nd_itpop;
 struct npaux_t *npauxp;
 struct itree_t *itp;
 decl_idp_locals_;

 save_idp = NULL;
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_VPIPUTV) return;
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - if XMR does not match - do not combine in */
     if ((itp = __get_npprefloc(npp)) == NULL) return;
     set_save_idp_itp_(itp); 
     nd_itpop = TRUE;
    }
   else nd_itpop = FALSE;
   
   xsp = __ld_vpiputv_driver(npp);
   if (nd_itpop) 
    {
     restore_idp_();
    }

   /* if lhs of concatenate, must select section out of rhs value */
   if ((npauxp = npp->npaux) != NULL && npauxp->lcbi1 != -1)
    {
     /* loaded value always matches lhs width exactly with z extension */
     /* if too wide just will not rhs psel from section */
     lhswid = npauxp->lcbi1 - npauxp->lcbi2 + 1;
     push_xstk_(tmpxsp, lhswid);
     __rhspsel(tmpxsp->ap, xsp->ap, npauxp->lcbi2, lhswid); 
     __rhspsel(tmpxsp->bp, xsp->bp, npauxp->lcbi2, lhswid); 

     __eval_wire(accum_ap, tmpxsp->ap, np, npp);
     __pop_xstk();
//AIV LOOKTEME - need to set these??????????
     __nchged_i1 = npauxp->lcbi2;
     __nchged_i2 = lhswid;
    }
   else __eval_wire(accum_ap, xsp->ap, np, npp);
   __pop_xstk();
  }
}


/*
 * process all dce added to the front of the list from PLI cbs
 * uses the same code from v_sim.c
 */
extern void __asl_chk_dce_cbvc(struct net_t *np)
{
 struct dcevnt_t *dcep;
 word32 oval, nval;
 int32 npi1, npi2;

 for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
  {
   if (dcep->dce_typ == DCE_RNG_PVC || dcep->dce_typ == DCE_PVC)
    {
     if (dcep->dce_typ == DCE_RNG_PVC)
      {
       __misc_terr(__FILE__, __LINE__);
       //AIV LINT - should this be handled????
       npi1 = __nchged_i1;
       npi2 = __nchged_i2;
       if (npi1 != -1 && (npi1 < dcep->dci2.i || npi2 > dcep->dci1)) continue;
      }
     if (dcep->dce_off) continue;

     /* notice tf PV change always per instance */
     if (dcep->dce_matchu.idp != __idp) continue;

     /* must check to make sure psel assign changed bits in actual range */
     oval = nval = 3;
     /* if no chg record, then array or reg entire wire so know changed */
     /* one dce for each different inst and location of _tf call */
     if (dcep->pli_prevval.wp != NULL)
      {
       if (np->n_stren)
        {
         if (!__stfilter_dce_chg(np, dcep, dcep->pli_prevval.bp, &oval,
          &nval)) continue;
        }
       else
        {
         if (!__filter_dce_chg(np, dcep, dcep->pli_prevval.wp, &oval, &nval))
          continue;
        }
      }
     /* do not care which rhs wire changed must eval and assign all */
     __pvc_call_misctf(dcep);
    }
   else if (dcep->dce_typ == DCE_RNG_CBVC)
    {
     __misc_terr(__FILE__, __LINE__);
     npi1 = __nchged_i1;
     npi2 = __nchged_i2;
     /* callback value change but dce contents differ */
     /* no -2 IS form since 1 active from 1 itree place only */
     /* if enire wire changed, always match */
     if (npi1 != -1 && (npi1 < dcep->dci2.i || npi2 > dcep->dci1)) continue;
    }
   else if (dcep->dce_typ != DCE_CBVC) return; 
     
   /* SJM 07/24/00 - must turn off PLI 1.0 PV dces from inside self */
   if (dcep->dce_off) continue;

   if (dcep->dce_matchu.idp != __idp) continue;

   oval = nval = 3;
   /* if no chg record, then array or reg entire wire so know changed */
   /* one dce for each different inst and location of _tf call */
   if (dcep->pli_prevval.wp != NULL)
    {
     if (!np->n_isavec)
      {
       /* 05/20/00 - SJM - following LRM vi vpi stren report st chg */
       /* user passed non stren val request to vpi_ cb call back */
       if (!np->n_stren || dcep->dce_nomonstren)
        {
         /* SJM 06/29/04 - simplified - always use stren version for scal */
         if (!__scal_stfilter_dce_chg(np, dcep->pli_prevval.bp, &oval, &nval)) 
           continue;
        }
       else
        {
         /* need strength changes too */
         if (!__vccb_scal_standval_filter(np, dcep->pli_prevval.bp,
          &oval, &nval, dcep->dce_edge)) continue;
        }
      }
     else
      {
       if (!np->n_stren)
        {
         if (!__filter_dce_chg(np, dcep, dcep->pli_prevval.wp, &oval, &nval))
          continue;
        }
       else
        {
         /* 05/20/00 - SJM - following LRM vi vpi stren report st chg */
         /* user passed non stren val request to vpi_ cb call back */
         if (dcep->dce_nomonstren)
          {
           if (!__stfilter_dce_chg(np, dcep, dcep->pli_prevval.bp, &oval,
            &nval)) continue;
          }
         else
          {
           /* need strength changes too */
           if (!__vccb_vec_standval_filter(np, dcep, dcep->pli_prevval.bp,
            &oval, &nval)) continue;
          }
        }
      }
    }

   /* SJM 07/24/00 - must run with this call back turned off in case */
   /* call back c code does put value to reg because change propagation */
   /* for regs must be immediate */
   /* notice will never get here unless dce on */
   dcep->dce_off = TRUE;

   /* AIV 03/06/07 - was passing the wrong arguments */
   __cbvc_callback(dcep, dcep->dceu.dce_cbp, dcep->dceu.dce_cbp->cb_hp);

   /* SJM 07/24/00 - unless user turned off with vpi control turn back on */
   /* user may turn off in value change call back routine */
   if (!dcep->dceu.dce_cbp->cb_user_off) dcep->dce_off = FALSE;
  }
}

/*
 * wrapper to check for PLI gate changes
 */
extern void __asl_chk_gate_vpi_chg(int32 gi)
{
 int32 inum;
 struct tev_t *tevp;
 struct mod_t *cur_mdp;

 if (__have_vpi_gateout_cbs)
  {
   cur_mdp = get_inst_mod_();
   inum = get_inum_();
   if (cur_mdp->mgateout_cbs != NULL && cur_mdp->mgateout_cbs[gi] != NULL
    && (tevp = cur_mdp->mgateout_cbs[gi][inum]) != NULL)
    {
     __exec_vpi_gateoutcbs(tevp);
    }
  }
}

extern void __asl_timing_check_record(struct chktchg_t *chkchgp)
{
 struct tc_pendlst_t *tcpendp;
 
 /* get a list element from somewhere */
 if (__tcpendfreelst == NULL)
  tcpendp = (struct tc_pendlst_t *) __my_malloc(sizeof(struct tc_pendlst_t));
 else
  {
   tcpendp = __tcpendfreelst;
   __tcpendfreelst = __tcpendfreelst->tc_plnxt;
  }
 tcpendp->tc_chkchgp = chkchgp;
 tcpendp->tc_idp = __idp;
 tcpendp->tc_plnxt = NULL;

 /* link on end since need batch movement of all to free list */
 if (__tcpendlst_end != NULL)
  { __tcpendlst_end->tc_plnxt = tcpendp; __tcpendlst_end = tcpendp; }
 else
  {
   __tcpendlst_hdr = __tcpendlst_end = tcpendp;
   __slotend_action |= SE_TCHK_VIOLATION;
  }
}

/*
 * wrapper to disable call - no longer loading expressions need to use stmt
 */
extern int32 __asl_exec_disable(struct st_t *stp)
{
 return(__exec_disable(stp->st.sdsable.dsablx));
}

extern void *__asl_downrel_targ_to_ref(struct gref_t *grp)
{
 int32 gri;
 struct itree_t *itp;
 struct inst_t *ip;

 /* since current itp is target - back up to reference itp */
 itp = get_itp_();
 /* SJM 04/17/03 - must move up and check that each one on way up */
 /* matches inst above since down can be multiply instanciated */
 for (gri = grp->last_gri; gri >= 0; gri--)
  {
   /* need to use inst array select expr which is itree loc. specific */
   if (grp->grxcmps[gri] != NULL) ip = __get_gref_giarr_ip(grp, gri, itp); 
   else ip = grp->grcmps[gri]->el.eip;

   if (ip != itp->itip)
    {
     //AIV BEWARE - not sure casting it for compare is good idea
     return((void *) -1);
    }
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
   /* DBG remove --- */
   if (itp->up_it == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
#endif
   itp = itp->up_it;
  }
 return(itp->it_idp);
}

extern void *__asl_uprel_targ_to_ref(struct gref_t *grp)
{
 int32 i;
 struct itree_t *itp;

 itp = get_itp_();
 for (i = 0; i < grp->gin_mdp->flatinum; i++)
  {
   if (itp == grp->targu.uprel_itps[i])
    {
     itp = grp->gin_mdp->moditps[i];
     return(itp->it_idp);
    }
  } 
 //AIV BEWARE - not sure casting it for compare is good idea
 return((void *) -1);
}

static void asl_loc_add_static_nchglst(struct nchglst_t *nchglp)
{
 nchglp->triggered = TRUE;
//AIV FIXME - if no midp don't need to reset this flag
 nchglp->delayed_mipd = FALSE;
 nchglp->nchglnxt = NULL;
#ifdef __CVC_DEBUG__
 if (__nchg_futend == NULL) __misc_terr(__FILE__, __LINE__);
#endif
 __nchg_futend->nchglnxt = nchglp; 
 __nchg_futend = nchglp; 
}

extern void __asl_add_static_nchglst_sel(struct nchglst_t *nchglp,
 int32 i1, int32 i2)
{
 struct nchglst_t *new_nchglp;

 if (nchglp->triggered) 
  {
   /* if variable select changes must alloc a new one */
   /* notice no need to check i2 because variable index in one value here */
   if (nchglp->bi1 != i1) 
    {
/* AIV LOOKATME - which is better??????
     if (__nchg_free_ndx > 1) new_nchglp = __nchg_freed[--__nchg_free_ndx];
     else 
      {
       new_nchglp = (struct nchglst_t *) __my_malloc(sizeof(struct nchglst_t));
      }
*/
     new_nchglp = (struct nchglst_t *) __my_malloc(sizeof(struct nchglst_t));
     new_nchglp->chgnp = nchglp->chgnp;
     new_nchglp->process_enterptr = __asl_process_alloced_nchg;
     nchglp = new_nchglp;
    }
   else return;
  }
 nchglp->triggered = TRUE;

 nchglp->bi1 = i1;
 nchglp->bi2 = i2;

//AIV FIXME - if no midp don't need to reset this flag
 nchglp->delayed_mipd = FALSE;
 nchglp->nchglnxt = NULL;
#ifdef __CVC_DEBUG__
 if (__nchg_futend == NULL) __misc_terr(__FILE__, __LINE__);
#endif
 __nchg_futend->nchglnxt = nchglp; 
 __nchg_futend = nchglp; 
 nchglp->nchg_idp = __idp;
}


/*
 * same as __schd_1pthwirebit from v_ex3.c - non-strength
 */
extern void __asl_schd_1pthwirebit(struct net_t *np, int32 biti, word32 nval,
 word32 oval, struct nchglst_t *nchglp, struct tev_t *ptevp) 
{
 word64 schtim;
 struct rngdwir_t *dwirp; 
 struct pthdst_t *pdp;

 /* since always use last changed value, if last same as current */
 /* because gate style glitch nothing to do since already right value */   
 if (!ptevp->trigger && nval == oval)
  return;

 /* these globals must be set for get del routine */
 __new_gateval = nval;
 __old_gateval = oval;
 /* possible for some bits to not be path destinations - just immed assign */
 /* SJM 11/24/00 - if values same won't find path or delay since need */
 /* transition */
 if (nval != oval) 
  {
   dwirp = np->nu.rngdwir;
   if ((pdp = asl_loc_get_path_del(dwirp, biti, &schtim)) == NULL)   
    {
     asl_loc_chg_st_bit(np, biti, nval & 1, (nval >> 1) & 1, nchglp);
     return;
    }
  }
 else { pdp = NULL; schtim = 0ULL; }

 /* special case 0 - distributed delay longer - immediate assign */
 /* normal cause is path (probably from multiple input final driving gate) */
 /* that has not path delay on it - this may be ok */
 if (pdp != NULL && schtim <= __simtime)
  {
   /* problem with modeling - distributed delay longer than path */
   if (!__no_informs) __emit_path_distinform(np, pdp, &__pdmindel);

   /* modeling anomally style spike possible - know immed. assign earlier */ 
   if (ptevp->trigger)
    {
     if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
      __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), NULL,
       "distributed longer or path destination driver unstable", FALSE);
     /* always cancel pending */
     linkout_tevp(ptevp);

     /* this is same for on detect and on event */
     if (__show_cancel_e)
      {
       /* this is special case where immediate assign must be to x */ 
       /* and cancel future event that can be scheduled for now */
set_on_detect_x:
       asl_loc_chg_st_bit(np, biti, 1, 1, nchglp);
       return;
      }
     /* if no show canceled e, just assign */  
    }
   /* AIV 12/17/07 - has doing the strength case here - need b part */
   asl_loc_chg_st_bit(np, biti, nval, (nval >> 1) & 1, nchglp);
   return;
  }

 /* no pending event - know nval not = oval or will not get here */
 if (!ptevp->trigger)
  {
   /* because no pending event must be different */
   asl_loc_schedule_1wev(biti, ptevp, __pdmindel, schtim, nval);
   return;
  }    

 /* pending event */
 /* new and old same but know scheduled different - classic pulse/glitch */
 if (nval == oval)
  {
   /* spike analysis, know scheduled different - tell user */
   /* this is classical spike analysis */
   /* do not have delay to use to select pa0th */  
   if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
    {
     __emit_path_samewarn(np, biti, ptevp, &(ptevp->etime), "pulse", FALSE);
    }

   /* if spike, suppress future but schedule to x at currently scheduled */
   if (__show_cancel_e)
    {
     if (__showe_onevent)
      { ptevp->outv = 3; return; }
     linkout_tevp(ptevp);
     goto set_on_detect_x;
    }
   /* remove pulse */
   linkout_tevp(ptevp);
   return;
  }
 /* SJM 11/24/00 - now know has pdp delay since old and new not same */

 /* new schedule to same value case */
 /* here delay can be different because different path selected */
 /* and maybe other reasons */
 /* done silently here - trace message only below */
 if (ptevp->outv == (byte) nval) return;

 /* inertial reschedule */
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), &schtim, "unstable", FALSE);   

 /* easy show cancel (set to x case) - no new event may or may not switch */
 if (__show_cancel_e)
  {
   /* LOOKATME - maybe need to check old tevp and new schd time and if 2nd */
   /* input change results in earlier edge cancel and schedule earlier */
   if (__showe_onevent)
    { ptevp->outv = 3; return; }

   /* remove pulse */
   linkout_tevp(ptevp);
   goto set_on_detect_x;
  }
 /* inertial reschedule, this handles cancel if needed */
 asl_loc_reschedule_1wev(ptevp, nval, schtim);
}

/*
 * no message version
 */
extern void __asl_schd_1pthwirebit_nomsg(struct net_t *np, int32 biti, 
 word32 nval, word32 oval, struct nchglst_t *nchglp, struct tev_t *ptevp) 
{
 word64 schtim;
 struct rngdwir_t *dwirp; 
 struct pthdst_t *pdp;

 /* since always use last changed value, if last same as current */
 /* because gate style glitch nothing to do since already right value */   
 if (!ptevp->trigger && nval == oval)
  return;

 /* these globals must be set for get del routine */
 __new_gateval = nval;
 __old_gateval = oval;
 /* possible for some bits to not be path destinations - just immed assign */
 /* SJM 11/24/00 - if values same won't find path or delay since need */
 /* transition */
 if (nval != oval) 
  {
   dwirp = np->nu.rngdwir;
   if ((pdp = asl_loc_get_path_del(dwirp, biti, &schtim)) == NULL)   
    {
     asl_loc_chg_st_bit(np, biti, nval & 1, (nval >> 1) & 1, nchglp);
     return;
    }
  }
 else { pdp = NULL; schtim = 0ULL; }

 /* special case 0 - distributed delay longer - immediate assign */
 /* normal cause is path (probably from multiple input final driving gate) */
 /* that has not path delay on it - this may be ok */
 if (pdp != NULL && schtim <= __simtime)
  {
   /* modeling anomally style spike possible - know immed. assign earlier */ 
   if (ptevp->trigger)
    {
     linkout_tevp(ptevp);
    }
   /* AIV 12/17/07 - has doing the strength case here - need b part */
   asl_loc_chg_st_bit(np, biti, nval, (nval >> 1) & 1, nchglp);
   return;
  }

 /* no pending event - know nval not = oval or will not get here */
 if (!ptevp->trigger)
  {
   /* because no pending event must be different */
   asl_loc_schedule_1wev(biti, ptevp, __pdmindel, schtim, nval);
   return;
  }    

 /* pending event */
 /* new and old same but know scheduled different - classic pulse/glitch */
 if (nval == oval)
  {
   /* remove pulse */
   linkout_tevp(ptevp);
   return;
  }

 /* new schedule to same value case */
 /* here delay can be different because different path selected */
 /* and maybe other reasons */
 /* done silently here - trace message only below */
 if (ptevp->outv == (byte) nval) return;

 /* inertial reschedule, this handles cancel if needed */
 asl_loc_reschedule_1wev(ptevp, nval, schtim);
}

/*
 * same as __schd_1pthwirebit from v_ex3.c - strength 
 */
extern void __asl_schd_st_1pthwirebit(struct net_t *np, 
 int32 biti, word32 nval, word32 oval, struct nchglst_t *nchglp, 
 struct tev_t *ptevp) 
{
 struct rngdwir_t *dwirp; 
 word64 schtim;
 struct pthdst_t *pdp;
 
 /* since always use last changed value, if last same as current */
 /* because gate style glitch nothing to do since already right value */   
 if (!ptevp->trigger && nval == oval)
  return;

 /* these globals must be set for get del routine */
 __new_gateval = nval;
 __old_gateval = oval;
 /* possible for some bits to not be path destinations - just immed assign */
 /* SJM 11/24/00 - if values same won't find path or delay since need */
 /* transition */
 if (nval != oval) 
  {
   dwirp = np->nu.rngdwir;
   if ((pdp = asl_loc_get_path_del(dwirp, biti, &schtim)) == NULL)   
    {
     asl_loc_chg_st_bit(np, biti, nval, 0L, nchglp);
     return;
    }
  }
 else { pdp = NULL; schtim = 0ULL; }

 /* special case 0 - distributed delay longer - immediate assign */
 /* normal cause is path (probably from multiple input final driving gate) */
 /* that has not path delay on it - this may be ok */
 if (pdp != NULL && schtim <= __simtime)
  {
   /* problem with modeling - distributed delay longer than path */
   if (!__no_informs) __emit_path_distinform(np, pdp, &__pdmindel);

   /* modeling anomally style spike possible - know immed. assign earlier */ 
   if (ptevp->trigger)
    {
     if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
      __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), NULL,
       "distributed longer or path destination driver unstable", TRUE);
     /* always cancel pending */
     linkout_tevp(ptevp);

     /* this is same for on detect and on event */
     if (__show_cancel_e)
      {
       /* this is special case where immediate assign must be to x */ 
       /* and cancel future event that can be scheduled for now */
set_on_detect_x:
       asl_loc_chg_st_bit(np, biti, (word32) ST_STRONGX, 0L, nchglp);
       return;
      }
     /* if no show canceled e, just assign */  
    }

   asl_loc_chg_st_bit(np, biti, nval, 0L, nchglp);
   return;
  }

 /* no pending event - know nval not = oval or will not get here */
 if (!ptevp->trigger)
  {
   /* because no pending event must be different */
   asl_loc_schedule_1wev(biti, ptevp, __pdmindel, schtim, nval);
   return;
  }    

 /* pending event */
 /* new and old same but know scheduled different - classic pulse/glitch */
 if (nval == oval)
  {
   /* spike analysis, know scheduled different - tell user */
   /* this is classical spike analysis */
   /* do not have delay to use to select pa0th */  
   if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
    {
     __emit_path_samewarn(np, biti, ptevp, &(ptevp->etime), "pulse", TRUE);
    }

   /* if spike, suppress future but schedule to x at currently scheduled */
   if (__show_cancel_e)
    {
     if (__showe_onevent)
      { ptevp->outv = ST_STRONGX; return; }
     linkout_tevp(ptevp);
     goto set_on_detect_x;
    }
   /* remove pulse */
   linkout_tevp(ptevp);
   return;
  }
 /* SJM 11/24/00 - now know has pdp delay since old and new not same */

 /* new schedule to same value case */
 /* here delay can be different because different path selected */
 /* and maybe other reasons */
 /* done silently here - trace message only below */
 if (ptevp->outv == (byte) nval) return;

 /* inertial reschedule */
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), &schtim, "unstable", TRUE);   

 /* easy show cancel (set to x case) - no new event may or may not switch */
 if (__show_cancel_e)
  {
   /* LOOKATME - maybe need to check old tevp and new schd time and if 2nd */
   /* input change results in earlier edge cancel and schedule earlier */
   if (__showe_onevent)
    { ptevp->outv = ST_STRONGX; return; }

   /* remove pulse */
   linkout_tevp(ptevp);
   goto set_on_detect_x;
  }
 /* inertial reschedule, this handles cancel if needed */
 asl_loc_reschedule_1wev(ptevp, nval, schtim);
}

/*
 * scalar version of schd_1pthwirebit - known biti is 0
 */
extern void __asl_schd_scalar_1pthwirebit(struct net_t *np, word32 nval, 
 word32 oval, struct nchglst_t *nchglp, struct tev_t *ptevp) 
{
 word64 schtim;
 byte *bp;
 struct pthdst_t *pdp;
 

 /* since always use last changed value, if last same as current */
 /* because gate style glitch nothing to do since already right value */   
 if (!ptevp->trigger && nval == oval)
  return;

 /* possible for some bits to not be path destinations - just immed assign */
 /* SJM 11/24/00 - if values same won't find path or delay since need */
 /* transition */
 __new_gateval = nval;
 __old_gateval = oval;
 if (nval != oval) 
  {
   /* these globals must be set for get del routine */
   /* AIV 01/11/12 - cond if(D) paths can now result in NULL paths */
   /* just return assing and return */
   if (asl_loc_get_path_del_scalar(np, &schtim) == NULL) 
    {
     asl_loc_chg_st_bit(np, -1, nval & 1, (nval >> 1) & 1, nchglp);
     return;
    }
  //AIV FIXME
   pdp = (struct pthdst_t *) 0xffffffff;
  }
 else { pdp = NULL; schtim = 0ULL; }

 /* special case 0 - distributed delay longer - immediate assign */
 /* normal cause is path (probably from multiple input final driving gate) */
 /* that has not path delay on it - this may be ok */
 if (pdp != NULL && schtim <= __simtime)
  {
   /* problem with modeling - distributed delay longer than path */
   if (!__no_informs) __emit_path_distinform(np, pdp, &__pdmindel);

   /* modeling anomally style spike possible - know immed. assign earlier */ 
   if (ptevp->trigger)
    {
     if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
      __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), NULL,
       "distributed longer or path destination driver unstable", FALSE);
     /* always cancel pending */
     linkout_tevp(ptevp);

     /* this is same for on detect and on event */
     if (__show_cancel_e)
      {
       /* this is special case where immediate assign must be to x */ 
       /* and cancel future event that can be scheduled for now */
set_on_detect_x:
       bp = (byte *) &(__idp[np->nva_ofs]);
       if (bp[0] != 3) 
        {
         bp[0] = 3; 
         asl_loc_record_nchg(np, nchglp);
        }
       return;
      }
     /* if no show canceled e, just assign */  
    }

   bp = (byte *) &(__idp[np->nva_ofs]);
   if (bp[0] != nval) 
    {
     bp[0] = nval; 
     asl_loc_record_nchg(np, nchglp);
    }
   return;
  }

 /* no pending event - know nval not = oval or will not get here */
 if (!ptevp->trigger)
  {
   /* because no pending event must be different */
   asl_loc_schedule_1wev(0, ptevp, __pdmindel, schtim, nval);
   return;
  }    

 /* pending event */
 /* new and old same but know scheduled different - classic pulse/glitch */
 if (nval == oval)
  {
   /* spike analysis, know scheduled different - tell user */
   /* this is classical spike analysis */
   /* do not have delay to use to select pa0th */  
   if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
    {
     __emit_path_samewarn(np, 0, ptevp, &(ptevp->etime), "pulse", FALSE);
    }

   /* if spike, suppress future but schedule to x at currently scheduled */
   if (__show_cancel_e)
    {
     if (__showe_onevent)
      { ptevp->outv = 3; return; }
     linkout_tevp(ptevp);
     goto set_on_detect_x;
    }
   /* remove pulse */
   linkout_tevp(ptevp);
   return;
  }
 /* SJM 11/24/00 - now know has pdp delay since old and new not same */
 /* new schedule to same value case */
 /* here delay can be different because different path selected */
 /* and maybe other reasons */
 /* done silently here - trace message only below */
 if (ptevp->outv == (byte) nval) return;

 /* inertial reschedule */
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), &schtim, "unstable", FALSE);   

 /* easy show cancel (set to x case) - no new event may or may not switch */
 if (__show_cancel_e)
  {
   /* LOOKATME - maybe need to check old tevp and new schd time and if 2nd */
   /* input change results in earlier edge cancel and schedule earlier */
   if (__showe_onevent) { ptevp->outv = 3; return; }

   /* remove pulse */
   linkout_tevp(ptevp);
   goto set_on_detect_x;
  }
 /* inertial reschedule, this handles cancel if needed */
 asl_loc_reschedule_1wev(ptevp, nval, schtim);
}

extern void __asl_schd_st_scalar_1pthwirebit(struct net_t *np, 
 word32 nval, word32 oval, struct nchglst_t *nchglp, struct tev_t *ptevp) 
{
 word64 schtim;
 struct pthdst_t *pdp;
 byte *netsbp;
 
 /* since always use last changed value, if last same as current */
 /* because gate style glitch nothing to do since already right value */   
 if (!ptevp->trigger && nval == oval)
  return;

 /* these globals must be set for get del routine */
 __new_gateval = nval;
 __old_gateval = oval;
 /* possible for some bits to not be path destinations - just immed assign */
 /* SJM 11/24/00 - if values same won't find path or delay since need */
 /* transition */
 if (nval != oval) 
  {
   /* AIV 01/11/12 - cond if(D) paths can now result in NULL paths */
   /* just return assing and return */
   if (asl_loc_get_path_del_scalar(np, &schtim) == NULL) 
    {
     asl_loc_chg_st_bit(np, -1, nval & 1, (nval >> 1) & 1, nchglp);
     return;
    }
  //AIV FIXME
   pdp = (struct pthdst_t *) 0xffffffff;
  }
 else { pdp = NULL; schtim = 0ULL; }

 /* special case 0 - distributed delay longer - immediate assign */
 /* normal cause is path (probably from multiple input final driving gate) */
 /* that has not path delay on it - this may be ok */
 if (pdp != NULL && schtim <= __simtime)
  {
   /* problem with modeling - distributed delay longer than path */
   if (!__no_informs) __emit_path_distinform(np, pdp, &__pdmindel);

   /* modeling anomally style spike possible - know immed. assign earlier */ 
   if (ptevp->trigger)
    {
     if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
      __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), NULL,
       "distributed longer or path destination driver unstable", TRUE);
     /* always cancel pending */
     linkout_tevp(ptevp);

     /* this is same for on detect and on event */
     if (__show_cancel_e)
      {
       /* this is special case where immediate assign must be to x */ 
       /* and cancel future event that can be scheduled for now */
set_on_detect_x:
       netsbp = (byte *) &(__idp[np->nva_ofs]);
       if (netsbp[0] != ST_STRONGX)
        { 
         *netsbp = (byte) ST_STRONGX; 
         asl_loc_record_nchg(np, nchglp);
        }
       return;
      }
     /* if no show canceled e, just assign */  
    }
   netsbp = (byte *) &(__idp[np->nva_ofs]);
   if (netsbp[0] != (byte) nval)
    { 
     *netsbp = (byte) nval; 
     asl_loc_record_nchg(np, nchglp);
    }
   return;
  }

 /* no pending event - know nval not = oval or will not get here */
 if (!ptevp->trigger)
  {
   /* because no pending event must be different */
   asl_loc_schedule_1wev(0, ptevp, __pdmindel, schtim, nval);
   return;
  }    

 /* pending event */
 /* new and old same but know scheduled different - classic pulse/glitch */
 if (nval == oval)
  {
   /* spike analysis, know scheduled different - tell user */
   /* this is classical spike analysis */
   /* do not have delay to use to select pa0th */  
   if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
    {
     __emit_path_samewarn(np, 0, ptevp, &(ptevp->etime), "pulse", TRUE);
    }

   /* if spike, suppress future but schedule to x at currently scheduled */
   if (__show_cancel_e)
    {
     if (__showe_onevent)
      { ptevp->outv = ST_STRONGX; return; }
     linkout_tevp(ptevp);
     goto set_on_detect_x;
    }
   /* remove pulse */
   linkout_tevp(ptevp);
   return;
  }
 /* SJM 11/24/00 - now know has pdp delay since old and new not same */

 /* new schedule to same value case */
 /* here delay can be different because different path selected */
 /* and maybe other reasons */
 /* done silently here - trace message only below */
 if (ptevp->outv == (byte) nval) return;

 /* inertial reschedule */
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_path_pulsewarn(pdp, ptevp, &(ptevp->etime), &schtim, "unstable", TRUE);   

 /* easy show cancel (set to x case) - no new event may or may not switch */
 if (__show_cancel_e)
  {
   /* LOOKATME - maybe need to check old tevp and new schd time and if 2nd */
   /* input change results in earlier edge cancel and schedule earlier */
   if (__showe_onevent)
    { ptevp->outv = ST_STRONGX; return; }

   /* remove pulse */
   linkout_tevp(ptevp);
   goto set_on_detect_x;
  }
 /* inertial reschedule, this handles cancel if needed */
 asl_loc_reschedule_1wev(ptevp, nval, schtim);
}

/*
 * AIV 01/13/12 - changed this to match new interp changes which need to 
 * check the condition code when determing the correct path
 *
 * changed __pdlatechgtim to local pdlatechgtim
 * this is only global in interpreter for tracing
 */
static struct pthdst_t *asl_loc_get_path_del_scalar(struct net_t *np, 
 word64 *pschtim) 
{
 struct pthdst_t *pdp, *latepdp;
 struct spcpth_t *newpthp, *pthp;
 struct expr_t *condx;
 struct xstk_t *xsp;
 word64 chgtim, newdel, pdlatechgtim;
 word64 *w64p;
 struct rngdwir_t *dwirp; 

 dwirp = np->nu.rngdwir;
 pdp = dwirp->n_du.pb_pthdst[0];

 /* AIV 01/11/12 - this was always wrong for paths which have a if(expr) */
 /* condition.  Need to eval condition code here to check for 0/1 */
 /* flag to keep track it any set */
 latepdp = NULL;
 /* AIV 01/13/12 - just init this to largest and smallest - this saves */
 /* an additional if stmt inside the loop */
 /* MAXTIME = 0xffffffffffffffffULL; */
 __pdmindel = MAXTIME;
 pdlatechgtim = 0;
 /* complicated case where more than one path end on this dest. wire np */
 for (;pdp != NULL; pdp = pdp->pdnxt)
  {
   pthp = pdp->pstchgp->chgu.chgpthp;
   condx = pthp->pthcondx;
   /* only include possible paths if cond does not eval to 0 */
   if (condx != NULL)
    {
     xsp = __eval2_xpr(condx);

      /* LRM requires anything but explicit false (0) is T */
     if ((xsp->ap[0] & 1L) == 0L && (xsp->bp[0] & 1L) == 0L)
      { 
       __pop_xstk();
       continue;
      }
     __pop_xstk();
    }

   /* get source change time */
   w64p = (word64 *) &(__idp[pdp->pstchgp->lastchg_ofs]);
   chgtim =  *w64p;
  
   /* case 1: change time earlier, always select latest */
   if (chgtim < pdlatechgtim) continue;
    
   newpthp = pdp->pstchgp->chgu.chgpthp;
   newdel = __get_del(newpthp->pth_du, newpthp->pth_delrep);
  
   /* if change times are the same, use the shortest path */
   if (chgtim == pdlatechgtim)
    {
     if (newpthp->pth_ifnone && newdel == __pdmindel) continue;

     /* newdel larger implies not shorter path, do not change */
     /* if same try to replace since for ties must replace ifnone */ 
     if (newdel > __pdmindel) continue;
    }
   /* this path's change time later(< handled above), just use */
   else pdlatechgtim = chgtim;

   __pdmindel = newdel;
   latepdp = pdp;
  }
 /* if none set __pdmindel will be max */
 /* return NULL - no path will do assign without delay */
 if (__pdmindel == MAXTIME) return(NULL);

 *pschtim = pdlatechgtim + __pdmindel;
 return(latepdp);
}


/*
 * same as __get_path_del from v_ex3.c
 * AIV 01/13/12 - changed this to match new interp changes which need to 
 * check the condition code when determing the correct path
 *
 * changed __pdlatechgtim to local pdlatechgtim
 * this is only global in interpreter for tracing
 */
static struct pthdst_t *asl_loc_get_path_del(struct rngdwir_t *dwirp, 
 int32 biti, word64 *pschtim) 
{
 struct pthdst_t *pdp, *latepdp;
 struct spcpth_t *newpthp, *pthp;
 struct expr_t *condx;
 struct xstk_t *xsp;
 word64 chgtim, newdel, pdlatechgtim;
 word64 *w64p;

 if ((pdp = dwirp->n_du.pb_pthdst[biti]) == NULL) return(NULL);

 /* AIV 01/11/12 - this was always wrong for paths which have a if(expr) */
 /* condition.  Need to eval condition code here to check for 0/1 */
 /* flag to keep track it any set */
 latepdp = NULL;
 /* AIV 01/13/12 - just init this to largest and smallest - this saves */
 /* an additional if stmt inside the loop */
 /* MAXTIME = 0xffffffffffffffffULL; */
 __pdmindel = MAXTIME;
 pdlatechgtim = 0;
 /* complicated case where more than one path end on this dest. wire np */
 for (;pdp != NULL; pdp = pdp->pdnxt)
  {
   pthp = pdp->pstchgp->chgu.chgpthp;
   condx = pthp->pthcondx;
   /* only include possible paths if cond does not eval to 0 */
   if (condx != NULL)
    {
     xsp = __eval2_xpr(condx);

      /* LRM requires anything but explicit false (0) is T */
     if ((xsp->ap[0] & 1L) == 0L && (xsp->bp[0] & 1L) == 0L)
      { 
       __pop_xstk();
       continue;
      }
     __pop_xstk();
    }

   /* get source change time */
   w64p = (word64 *) &(__idp[pdp->pstchgp->lastchg_ofs]);
   chgtim =  *w64p;
  
   /* case 1: change time earlier, always select latest */
   if (chgtim < pdlatechgtim) continue;
    
   newpthp = pdp->pstchgp->chgu.chgpthp;
   newdel = __get_del(newpthp->pth_du, newpthp->pth_delrep);
  
   /* if change times are the same, use the shortest path */
   if (chgtim == pdlatechgtim)
    {
     if (newpthp->pth_ifnone && newdel == __pdmindel) continue;

     /* newdel larger implies not shorter path, do not change */
     /* if same try to replace since for ties must replace ifnone */ 
     if (newdel > __pdmindel) continue;
    }
   /* this path's change time later(< handled above), just use */
   else pdlatechgtim = chgtim;

   __pdmindel = newdel;
   latepdp = pdp;
  }
 /* if none set __pdmindel will be max */
 /* return NULL - no path will do assign without delay */
 if (__pdmindel == MAXTIME) return(NULL);

 *pschtim = pdlatechgtim + __pdmindel;
 return(latepdp);
}

/* 
 * ROUTINES TO GET DELAY VALUE
 */

extern word64 __asl_get_del_1x(union del_u du)
{   
 word64 del;
 struct thread_t *sav_curthp;
 struct xstk_t *xsp;

 sav_curthp = __cur_thd;
 __cur_thd = NULL;

 xsp = __eval_xpr(du.d1x);

 del = asl_loc_delx_to_deltim(du.d1x, xsp);
 __pop_xstk();
 __cur_thd = sav_curthp;
 return(del);
}

extern word64 __asl_get_del_4x(union del_u du)
{   
 word64 del;
 struct thread_t *sav_curthp;
 struct xstk_t *xsp;
 word64 dv1, dv0;
 struct expr_t *dxp;


 sav_curthp = __cur_thd;
 __cur_thd = NULL;
 dxp = du.d4x[__new_gateval];
 if (dxp == NULL)
  {
   dxp = du.d4x[0];
   xsp = __eval_xpr(dxp);
   dv0 = asl_loc_delx_to_deltim(dxp, xsp);
   __pop_xstk();
   dxp = du.d4x[1];
   xsp = __eval_xpr(dxp);
     
   dv1 = asl_loc_delx_to_deltim(dxp, xsp);
   __pop_xstk();
   del = (dv1 <= dv0) ? dv1 : dv0;
   __cur_thd = sav_curthp;
   return(del);
  }
 xsp = __eval_xpr(dxp);
 del = asl_loc_delx_to_deltim(dxp, xsp);
 __pop_xstk();
 __cur_thd = sav_curthp;
 return(del);
}

static word64 asl_loc_delx_to_deltim(struct expr_t *dxp, struct xstk_t *xsp)
{
 word64 t, del;
 double d1;
 struct mod_t *mdp;

 mdp = get_inst_mod_();
 if (dxp->is_real)
  {
   memcpy(&d1, xsp->ap, sizeof(double));
   del = asl_loc_real_to_ticks(d1, mdp);
   return(del);
  }
 if (xsp->bp[0] != 0L)
  {
   __sgfwarn(565, "delay expression #(%s) evaluates to x/z changed to #0",
    __msgexpr_tostr(__xs, dxp));
   del = 0ULL;
   return(del);
  }
 t = (word64) xsp->ap[0];
 if (xsp->xslen > WBITS) t |= (((word64) xsp->ap[1]) << 32);

 if (!mdp->mno_unitcnv) cnv_num64to_ticks_(del, t, mdp);
 else del = t;
 return(del);
}

/*
 * convert a real to ticks - here must scale (multiply before) conversion
 * rule is: multiply to get ticks, round, then convert to time 
 *
 * notice this is only routine that is called even for mods that do not
 * need scaling
 */ 
static word64 asl_loc_real_to_ticks(double d1, struct mod_t *mdp)
{
 word64 del;
 int32 unit;

 if (!mdp->mno_unitcnv)
  {
    unit = __des_timeprec - mdp->mtime_units;
    d1 *= __dbl_toticks_tab[unit];
  }
 if (!__real_to_v64tim(&del, d1))
  __sgfwarn(563, "error in conversion of real %g to 64 bit time - set to %s",
   d1, __to_timstr(__xs, &del));
 return(del);
} 

static void asl_loc_record_nchg(struct net_t *np, struct nchglst_t *nchglp)
{
 if (np->enter_dce != NULL)
  {
   __nchged_i1 = nchglp->bi1;
   __nchged_i2 = nchglp->bi2;
   /* AIV 09/14/06 - if has pli access must check for dce cb */
   /* linked on to the front to the dcelst */
   /* AIV 05/13/09 - access level > 2 for call backs */
   if (np->pli_access >= 2) __asl_chk_dce_cbvc(np);
   /* AIV 01/04/07 - need to tell gcc that %esi cannot be used here */
  #ifdef __CVC32__
   __asm__ ("movl __idp, %%esi" :: :"%esi");
  #else
   __asm__ ("movq __idp, %%r15" :: :"%r15");
  #endif
   (np->enter_dce)();
  }

//AIV SAME AS - if (__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0) 
 if (!nchglp->triggered)
  {
   asl_loc_add_static_nchglst(nchglp);
  }

 /* AIV 12/06/10 - may need to add change to toggle list */
 if (np->n_has_toggle) __add_togglelst_el(np);
//AIV DUMP - AIV FIXME - should just check this bit first np->dmpv_in_src
//first the code would be better??????
//if (np->dmpv_in_src)
 if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
   == (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
  {
   __idp[np->nchgaction_ofs] &= ~(NCHG_DMPVNOTCHGED);
   __asl_add_dmpv_chglst_el(np);
  } 
 if (np->dmpp_in_src)
  {
   if ((__idp[np->nchgaction_ofs] & (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED))
     == (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED))
    {
     __idp[np->nchgaction_ofs] &= ~(NCHG_DMPP_NOTCHGED);
     __asl_add_dmpp_chglst_el(np);
    } 
  }
}

/*
 * 
 */
//AIV FIXME - just get np from nchglp
static void asl_loc_record_sel_nchg(struct net_t *np, struct nchglst_t *nchglp,
 int32 biti)
{
 if (np->enter_dce != NULL)
  {
   __nchged_i1 = biti;
   __nchged_i2 = biti;
   /* AIV 09/14/06 - if has pli access must check for dce cb */
   /* linked on to the front to the dcelst */
   /* AIV 05/13/09 - access level > 2 for call backs */
   if (np->pli_access >= 2) __asl_chk_dce_cbvc(np);
   /* AIV 01/04/07 - need to tell gcc that %esi cannot be used here */
  #ifdef __CVC32__
   __asm__ ("movl __idp, %%esi" :: :"%esi");
  #else
   __asm__ ("movq __idp, %%r15" :: :"%r15");
  #endif
   (np->enter_dce)();
  }
//AIV SAME AS - if ((__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0) 
 /* AIV 01/27/11 - rare bug if concat lhs var index with dumpvars and */
 /* no net changes this will enter via v_sim wrapper and can be NULL */
 if (nchglp != NULL && !nchglp->triggered)
   asl_loc_add_static_nchglst(nchglp);

 /* AIV 12/06/10 - may need to add change to toggle list */
 if (np->n_has_toggle) __add_togglelst_el(np);
//AIV LOOKATME -
//AIV FIXME - all these comments wrong leave marked -1 therefore 
//it will check the the entire list via __nchged_i1 && __nchged_i2
 /* AIV 11/26/07 - notice do not check if triggered here because may */
 /* need to allocate a new nchg with the new biti value */
 /* AIV 11/21/07 - wasn't recording the selected range here */
 //__asl_add_static_nchglst_sel(nchglp, biti, biti);
//AIV DUMP - AIV FIXME - should just check this bit first np->dmpv_in_src
//first the code would be better??????
//if (np->dmpv_in_src)
 if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
   == (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
  {
   __idp[np->nchgaction_ofs] &= ~(NCHG_DMPVNOTCHGED);
   __asl_add_dmpv_chglst_el(np);
  } 
 if (np->dmpp_in_src)
  {
   if ((__idp[np->nchgaction_ofs] & (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED))
     == (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED))
    {
     __idp[np->nchgaction_ofs] &= ~(NCHG_DMPP_NOTCHGED);
     __asl_add_dmpp_chglst_el(np);
    } 
  }
}

/*
 * change versions of store bit
 * know biti in range
 */
static void asl_loc_chg_st_bit(struct net_t *np, int32 biti, 
 word32 av, word32 bv, struct nchglst_t *nchglp)
{
 word32 *rap;
 int32 lhs_changed;
 word32 uwrd;
 byte *netsbp;

 /* DBG remove --*/
#ifdef __CVC_DEBUG__
 if (nchglp->bi1 != biti) __misc_terr(__FILE__, __LINE__);
#endif
 /* -- */

 lhs_changed = FALSE;
 switch ((byte) np->srep) {
 /* this is same as full value store - biti 0 or will not get here */
  case SR_SCAL:
   /* DBG remove --
   if (biti != 0) __arg_terr(__FILE__, __LINE__); 
   --- */
   uwrd = av | (bv << 1);
   if (__idp[np->nva_ofs] != uwrd)
    {
     __idp[np->nva_ofs] = uwrd;
     lhs_changed = TRUE;
    }
   break;
  case SR_VEC:
   /* rap is base of vector for current inst */
   rap = &(__idp[np->nva_ofs]);
   lhs_changed = asl_loc_chg_vec_lhsbsel(rap, biti, av, bv, np->nwid);
   break;
  case SR_SVEC:
   /* rap is base of vector for current inst */
   netsbp = (byte *) &(__idp[np->nva_ofs]);
   if (netsbp[biti] != (byte) av)
    { netsbp[biti] = (byte) av; lhs_changed = TRUE; }
   break;
  case SR_SSCAL:
   /* DBG remove ---
   if (biti != 0) __arg_terr(__FILE__, __LINE__); 
   -- */
   netsbp = (byte *) &(__idp[np->nva_ofs]);
   if (netsbp[0] != (byte) av)
    { *netsbp = (byte) av; lhs_changed = TRUE; }
   break;
#ifdef __CVC_DEBUG__
 /* AIV 03/25/09 - runtime shouldn't check for __misc_terr */
  default: __case_terr(__FILE__, __LINE__);
#endif
 }

 if (lhs_changed) 
  {
   asl_loc_record_sel_nchg(np, nchglp, biti);
  }
}

/*
 * AIV 11/21/07 - need for nb var index net changes
 */
extern void __asl_chg_vec_lhsbsel(struct net_t *np, int32 dbit, word32 aw,
 word32 bw, struct nchglst_t *nchglp) 
{
 word32 *dwp;
 int32 lhs_changed;

 dwp = &(__idp[np->nva_ofs]);
 lhs_changed = asl_loc_chg_vec_lhsbsel(dwp, dbit, aw, bw, np->nwid);
 if (lhs_changed) asl_loc_record_sel_nchg(np, nchglp, dbit);
}

/*
 * 2-state version - no b part loading
 */
extern void __asl_chg_vec_lhsbsel_2state(struct net_t *np, int32 dbit, 
 word32 aw, struct nchglst_t *nchglp) 
{
 word32 *dwp;
 int32 lhs_changed;

 dwp = &(__idp[np->nva_ofs]);
 lhs_changed = asl_loc_chg_vec_lhsbsel_2state(dwp, dbit, aw);
 if (lhs_changed) asl_loc_record_sel_nchg(np, nchglp, dbit);
}

/*
 * AIV 11/21/07 - need for nb var array index net changes
 */
extern void __asl_record_array_net_change(struct net_t *np, 
 struct nchglst_t *nchglp, int32 arri)
{
 /* AIV 12/20/07 - may just need the dumpvars recording */
 if (nchglp != NULL)
  {
   if (np->enter_dce != NULL)
    {
     __nchged_i1 = arri;
     __nchged_i2 = arri;
     /* AIV 09/14/06 - if has pli access must check for dce cb */
     /* linked on to the front to the dcelst */
     /* AIV 05/13/09 - access level > 2 for call backs */
     if (np->pli_access >= 2) __asl_chk_dce_cbvc(np);
     /* AIV 01/04/07 - need to tell gcc that %esi cannot be used here */
  #ifdef __CVC32__
   __asm__ ("movl __idp, %%esi" :: :"%esi");
  #else
   __asm__ ("movq __idp, %%r15" :: :"%r15");
  #endif
     (np->enter_dce)();
    }
  if (!nchglp->triggered) asl_loc_add_static_nchglst(nchglp);
 }

//AIV DUMP - AIV FIXME - should just check this bit first np->dmpv_in_src
//first the code would be better??????
//if (np->dmpv_in_src)
 if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
   == (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
  {
   __idp[np->nchgaction_ofs] &= ~(NCHG_DMPVNOTCHGED);
   __asl_add_dmpv_chglst_el_array(np, arri);
  } 
 if (np->dmpp_in_src)
  {
   if ((__idp[np->nchgaction_ofs] & (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED))
     == (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED))
    {
     __idp[np->nchgaction_ofs] &= ~(NCHG_DMPP_NOTCHGED);
     __asl_add_dmpp_chglst_el(np);
    } 
  }
}


/*
 * local lhs chg bsel routine
 */
static int32 asl_loc_chg_vec_lhsbsel(word32 *dwp, int32 dbit, word32 aw, 
 word32 bw, int32 blen)
{
 word32 mask, sw2;
 word32 *dwbp;
 int32 bi, wi, changed, wlen;

 changed = FALSE;
 /* dbit in wrd32 0: 0-31, wrd32 1: 32-63, etc (32 left high - 0 right low) */
 wi = get_wofs_(dbit);
 bi = get_bofs_(dbit);
 mask = 1UL << bi;
 sw2 = (aw & 1L) << bi;
 /* a part */
 if (((dwp[wi] & mask) ^ sw2) != 0L)
  { 
   changed = TRUE; 
   dwp[wi] &= ~mask; 
   dwp[wi] |= sw2; 
  }
 /* b part */
 wlen = wlen_(blen);
 dwbp = &(dwp[wlen]);
 sw2 = (bw & 1L) << bi;
 if (((dwbp[wi] & mask) ^ sw2) != 0L)
  { 
   changed = TRUE; 
   dwbp[wi] &= ~mask; 
   dwbp[wi] |= sw2; 
  }
 return(changed);
}

/*
 * 2-state local lhs chg bsel routine
 */
static int32 asl_loc_chg_vec_lhsbsel_2state(word32 *dwp, int32 dbit, word32 aw) 
{
 word32 mask, sw2;
 int32 bi, wi, changed;

 changed = FALSE;
 /* dbit in wrd32 0: 0-31, wrd32 1: 32-63, etc (32 left high - 0 right low) */
 wi = get_wofs_(dbit);
 bi = get_bofs_(dbit);
 mask = 1UL << bi;
 sw2 = (aw & 1L) << bi;
 /* a part */
 if (((dwp[wi] & mask) ^ sw2) != 0L)
  { 
   changed = TRUE; 
   dwp[wi] &= ~mask; 
   dwp[wi] |= sw2; 
  }
 return(changed);
}

/*
 * add a dumpvars change element
 * only called first time for entire net in time slot
 */
extern void __asl_add_dmpv_chglst_el(struct net_t *np)
{
 int32 inum;
 struct dvchgnets_t *dvchgp;

 /* indicate for this time slot inst of var already changed once */
 __idp[np->nchgaction_ofs] &= ~(NCHG_DMPVNOTCHGED);

 /* AIV 05/17/10 - these are fixed - no need for free list */
 inum = get_inum_();
 dvchgp = &(np->dvns[inum]);

 /* link on front since order does not matter */
 dvchgp->dvchgnxt = __dv_chgnethdr;
 __dv_chgnethdr = dvchgp;
 __slotend_action |= SE_DUMPVARS;
}

/*
 * dump an array element with known ndx
 * used with options +dump_arrays and +dump_array_cells
 * same as __add_dmpv_chglst_el_sel - in v_sim
 */
extern void __asl_add_dmpv_chglst_el_array(struct net_t *np, int32 ndx)
{
 int32 inum, num_els;
 struct dvchgnets_t *dvchgp;


 /* known to be an array */
 inum = get_inum_();
 num_els = np->arr_num_els;
 if (!np->n_arr_hasdvars[ndx]) return;
 dvchgp = &(np->dvns[(inum*num_els)+ndx]);
 /* AIV 09/02/10 - if array element do not set nchgaction_ofs */
 /* now using on_list bit - was only recording first change */
 if (dvchgp->on_list) return;
 dvchgp->on_list = TRUE;
 
 /* link on front since order does not matter */
 dvchgp->dvchgnxt = __dv_chgnethdr;
 __dv_chgnethdr = dvchgp;
 __slotend_action |= SE_DUMPVARS;
}

/*
 * same a regular dump vars but must check nchgaction ofs value
 */
extern void __asl_add_dmpv_chglst_el_mdprt(struct net_t *np)
{
 int32 inum;
 struct dvchgnets_t *dvchgp;
 
 /* AIV 12/06/10 - may need to add change to toggle list */
 if (np->n_has_toggle) __add_togglelst_el(np);
 
 /* AIV 07/21/09 - if stmt has wrong */
 if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
   != (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
  {
   return;
  }


 /* indicate for this time slot inst of var already changed once */
 __idp[np->nchgaction_ofs] &= ~(NCHG_DMPVNOTCHGED);

 inum = get_inum_();
 dvchgp = &(np->dvns[inum]);

 /* link on front since order does not matter */
 dvchgp->dvchgnxt = __dv_chgnethdr;
 __dv_chgnethdr = dvchgp;
 __slotend_action |= SE_DUMPVARS;
}

/*
 * same as above just local version so gcc will inline
 */
static void asl_loc_add_dmpv_chglst_el_mdprt(struct net_t *np)
{
 int32 inum;
 struct dvchgnets_t *dvchgp;

 /* AIV 12/06/10 - may need to add change to toggle list */
 if (np->n_has_toggle) __add_togglelst_el(np);
 
 /* AIV 07/21/09 - if stmt has wrong */
 if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
   != (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
  {
   return;
  }


 /* indicate for this time slot inst of var already changed once */
 __idp[np->nchgaction_ofs] &= ~(NCHG_DMPVNOTCHGED);

 inum = get_inum_();
 dvchgp = &(np->dvns[inum]);

 /* link on front since order does not matter */
 dvchgp->dvchgnxt = __dv_chgnethdr;
 __dv_chgnethdr = dvchgp;
 __slotend_action |= SE_DUMPVARS;
}

/*
 * add a dumpports change element
 */
extern void __asl_add_dmpp_chglst_el(struct net_t *np)
{
//AIV DUMP - inline this code then dumpports is working
 __add_dp_chglst_el(np);
}

/*
 * same a regular dump port but must check nchgaction ofs value
 */
extern void __asl_add_dmpp_chglst_el_mdprt(struct net_t *np)
{
 /* AIV 07/21/09 - if stmt has wrong */
 if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
   != (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED))
  {
   return;
  }

//AIV DUMP - inline this code then dumpports is working
 __add_dp_chglst_el(np);
}

/*
 * add a net to the toggle change list
 *
 * same as regular __add_togglelst_el_port - but must check has toggle on
 */
extern void __asl_add_togglelst_el_port(struct net_t *np)
{
 int32 inum;
 struct rt_tgl_t *togp;
 struct net_toggle_t *ntgp;

 /* SJM 06-30-13 - if tgl record off nothing to do */
 if (!__tgl_record_on) return;

 ntgp = np->ntgp;
 /* AIV 12/17/10 - special port code can have one side of a port with */
 /* toggle coverage and one without - therefore this is NULL */
 /* AIV 03/06/11 - now toggle struct will be NULL if not toggle */
 if (ntgp == NULL) return;

 if (ntgp->n_peri_tgl_on_se_list == NULL) return;
 inum = get_inum_();
 /* if this instance is on the list - return */
 /* SJM 10-30-12 - notice that toggle recording is per inst even if some */
 /* bit toggle coverage turned off */
 if (ntgp->n_peri_tgl_on_se_list[inum]) return;

 ntgp->n_peri_tgl_on_se_list[inum] = TRUE;
 togp = (struct rt_tgl_t *) __idp[ntgp->toggle_ofs];
 /* link on front since order does not matter */
 togp->tognxt = __toggle_chghdr;
 __toggle_chghdr = togp;
 __slotend_action |= SE_TOGGLE;
}

extern void __asl_process_mipd_nchg_ev(struct net_t *np)
{
 struct mipd_t *mipdp;
 int32 bi, bi2, inum;

 bi = __cur_tevp->tu.bi;

 /* turn off mipd sheduled event */
 bi2 = (bi == -1) ? 0 : bi;
 mipdp = &(np->nlds->elnpp.emipdbits[bi2]);
 inum = get_inum_();
 mipdp->mipdschd_tevs[inum] = NULL;

 /* add to nchg list if net not already all changed */
 /* dmpvars bits chg not turned on since dumpvar happens when net changes */
 /* also can't use normal macro, because never need reg dce wakeup */
 if ((__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0) 
 //AIV FIXME if (!nchglp->triggered)
  {
   __add_select_nchglst_el(np, bi, bi);
   /* SJM 19/01/02 - T because this is 2nd delayed event one so must */
   /* not schedule */
   /* BEWARE - this assumes last element added to end of list */
   __nchg_futend->delayed_mipd = TRUE;
  }
}

//AIV HERE
extern void __asl_process_mipd_scalar_nchg_ev(struct nchglst_t *nchglp)
{
 /* turn off mipd sheduled event */
 /* add to nchg list if net not already all changed */
 /* dmpvars bits chg not turned on since dumpvar happens when net changes */
 /* also can't use normal macro, because never need reg dce wakeup */
//AIV SAME AS - if (__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0) 
 if (!nchglp->triggered)
  {
   asl_loc_add_static_nchglst(nchglp);
   /* SJM 19/01/02 - T because this is 2nd delayed event one so must */
   /* not schedule */
   /* AIV 09/13/07 - uses static event so set bit to passed static event */
   nchglp->delayed_mipd = TRUE;
  }
}

/*
 * check force active bit
 */
extern int32 __asl_force_active(struct net_t *np, int32 bi) 
{
 struct qcval_t *frc_qcp;
 int32 itinum;

/* inhibit if active force */
 itinum = get_inum_();
 frc_qcp =  &(np->nu2.qcval[itinum*np->nwid + bi]);
 return(frc_qcp->qc_active);
}

/*
 * do one word rhs psel - similar to __rhspsel - known to be narrow
 *
 * might be access higher than > WBITS - but never wider than WBITS for the psel
 * does a and b part - a part is returned and b part is put in ECX
 * AIV BEWARE - b part returned in ECX
 */
extern word32 __asl_rhs_psel(word32 *swp, word32 *sbwp, int32 sbit1, 
 int32 numbits)
{
 int32 wi, corsbit1;
 word32 av, bv;

 /* case 1 - select within 1st word32 */
 if (sbit1 + numbits <= WBITS)
  {
   corsbit1 = sbit1;
do_inword:
   av = (*swp >> corsbit1) & __masktab[numbits];
   bv = (*sbwp >> corsbit1) & __masktab[numbits];
#ifdef __CVC32__
   __asm__ ("movl %0, %%ecx" : : "g" (bv));
#else
   __asm__ ("movq %0, %%rcx" : : "g" (bv));
#endif
   return(av);
  }

 /* normalize so swp and corsbit1 start of src with corsbit1 in 1st word32 */
 wi = get_wofs_(sbit1);
 swp = &(swp[wi]);
 sbwp = &(sbwp[wi]);
 corsbit1 = ubits_(sbit1);

 /* case 2 - selection does not cross word32 boundary */
 if (corsbit1 + numbits <= WBITS) goto do_inword;

 /* case 3a - selection crosses word32 boundary but start on word32 boundary */
 if (corsbit1 == 0) 
  { 
   cp_walign_(&av, swp, numbits); 
   cp_walign_(&bv, sbwp, numbits); 
#ifdef __CVC32__
   __asm__ ("movl %0, %%ecx" : : "g" (bv));
#else
   __asm__ ("movq %0, %%rcx" : : "g" (bv));
#endif
   return(av); 
  }

 /* case 3a - crosses 1 word32 boundary and <= WBITS long */
 av = (swp[0] >> corsbit1);
 av |= swp[1] << (WBITS - corsbit1);
 av &= __masktab[numbits];
 bv = (sbwp[0] >> corsbit1);
 bv |= sbwp[1] << (WBITS - corsbit1);
 bv &= __masktab[numbits];
#ifdef __CVC32__
   __asm__ ("movl %0, %%ecx" : : "g" (bv));
#else
   __asm__ ("movq %0, %%rcx" : : "g" (bv));
#endif
 return(av);
}

/*
 * 2-state version
 */
extern word32 __asl_rhs_psel_2state(word32 *swp, int32 sbit1, int32 numbits)
{
 int32 wi, corsbit1;
 word32 av;

 /* case 1 - select within 1st word32 */
 if (sbit1 + numbits <= WBITS)
  {
   corsbit1 = sbit1;
do_inword:
   av = (*swp >> corsbit1) & __masktab[numbits];
   return(av);
  }

 /* normalize so swp and corsbit1 start of src with corsbit1 in 1st word32 */
 wi = get_wofs_(sbit1);
 swp = &(swp[wi]);
 corsbit1 = ubits_(sbit1);

 /* case 2 - selection does not cross word32 boundary */
 if (corsbit1 + numbits <= WBITS) goto do_inword;

 /* case 3a - selection crosses word32 boundary but start on word32 boundary */
 if (corsbit1 == 0) 
  { 
   cp_walign_(&av, swp, numbits); 
   return(av); 
  }

 /* case 3a - crosses 1 word32 boundary and <= WBITS long */
 av = (swp[0] >> corsbit1);
 av |= swp[1] << (WBITS - corsbit1);
 av &= __masktab[numbits];
 return(av);
}

/*
 * strength rhs psel
 */
extern void __asl_rhs_st_psel(word32 *rgap, byte *sbp, int32 blen)
{
 int32 bi, wlen;
 word32 *rgbp;
 word32 tmpw;
 
 /* zero unused high bits in high word32 only - rest will be selected into */
 wlen = wlen_(blen);
 rgbp = &(rgap[wlen]); 
 rgap[wlen - 1] = 0L;
 rgbp[wlen - 1] = 0L;
 for (bi = 0; bi < blen; bi++)
  {
   tmpw = (word32) sbp[bi];
   __lhsbsel(rgap, bi, tmpw & 1L);
   __lhsbsel(rgbp, bi, (tmpw >> 1) & 1L);
  }
}

/*
 * do a wide (possibly) from a +: or -: psel
 * basically does the same as __rhspsel excepct takes a and p part
 * and with __cp_sofs_wval inlined
 *
 * AIV LOOKATME - maybe better to just assume wide??? to avoid if stmts???
 * might be <= WBITS due to trimming of out of range
 */
extern void  __asl_rhs_psel_wide(word32 *dwp, word32 *dbwp, word32 *swp, 
 word32 *sbwp, int32 sbit1, int32 numbits)
{
 int32 wi, bi, sbit2, wndx, corsbit1;
 word32 mask;

 /* case 1 - select within 1st word32 */
 if (sbit1 + numbits <= WBITS)
  {
   corsbit1 = sbit1;
do_inword:
   *dwp = (*swp >> corsbit1) & __masktab[numbits];
   *dbwp = (*sbwp >> corsbit1) & __masktab[numbits];
   return;
  }

 /* normalize so swp and corsbit1 start of src with corsbit1 in 1st word32 */
 wi = get_wofs_(sbit1);
 swp = &(swp[wi]);
 sbwp = &(sbwp[wi]);
 corsbit1 = ubits_(sbit1);

 /* case 2 - selection does not cross word32 boundary */
 if (corsbit1 + numbits <= WBITS) goto do_inword;

 /* case 3a - selection crosses word32 boundary but start on word32 boundary */
 if (corsbit1 == 0) 
  { 
   cp_walign_(dwp, swp, numbits); 
   cp_walign_(dbwp, sbwp, numbits); 
   return; 
  }

 /* case 3a - crosses 1 word32 boundary and <= WBITS long */
 if (numbits <= WBITS)
  {
   *dwp = (swp[0] >> corsbit1);
   *dwp |= swp[1] << (WBITS - corsbit1);
   *dwp &= __masktab[numbits];
   *dbwp = (sbwp[0] >> corsbit1);
   *dbwp |= sbwp[1] << (WBITS - corsbit1);
   *dbwp &= __masktab[numbits];
   return;
  }

 sbit2 = WBITS - corsbit1;
 for (bi = 0, wi = 0; ; wi++)
  {
   dwp[wi] = (swp[wi] >> corsbit1);
   dbwp[wi] = (sbwp[wi] >> corsbit1);
   if ((bi += sbit2) >= numbits) break;
   wndx = wi + 1;
   dwp[wi] |= (swp[wndx] << sbit2);
   dbwp[wi] |= (sbwp[wndx] << sbit2);
   if ((bi += corsbit1) >= numbits) break;
  }
 mask = __masktab[ubits_(numbits)];
 dwp[wi] &= mask;
 dbwp[wi] &= mask;
}

/*
 * 2-state version
 */
extern void  __asl_rhs_psel_wide_2state(word32 *dwp, word32 *swp, int32 sbit1, 
 int32 numbits)
{
 int32 wi, bi, sbit2, wndx, corsbit1;
 word32 mask;

 /* case 1 - select within 1st word32 */
 if (sbit1 + numbits <= WBITS)
  {
   corsbit1 = sbit1;
do_inword:
   *dwp = (*swp >> corsbit1) & __masktab[numbits];
   return;
  }

 /* normalize so swp and corsbit1 start of src with corsbit1 in 1st word32 */
 wi = get_wofs_(sbit1);
 swp = &(swp[wi]);
 corsbit1 = ubits_(sbit1);

 /* case 2 - selection does not cross word32 boundary */
 if (corsbit1 + numbits <= WBITS) goto do_inword;

 /* case 3a - selection crosses word32 boundary but start on word32 boundary */
 if (corsbit1 == 0) 
  { 
   cp_walign_(dwp, swp, numbits); 
   return; 
  }

 /* case 3a - crosses 1 word32 boundary and <= WBITS long */
 if (numbits <= WBITS)
  {
   *dwp = (swp[0] >> corsbit1);
   *dwp |= swp[1] << (WBITS - corsbit1);
   *dwp &= __masktab[numbits];
   return;
  }

 sbit2 = WBITS - corsbit1;
 for (bi = 0, wi = 0; ; wi++)
  {
   dwp[wi] = (swp[wi] >> corsbit1);
   if ((bi += sbit2) >= numbits) break;
   wndx = wi + 1;
   dwp[wi] |= (swp[wndx] << sbit2);
   if ((bi += corsbit1) >= numbits) break;
  }
 mask = __masktab[ubits_(numbits)];
 dwp[wi] &= mask;
}

/*
 * wrapper to produce random value with a seed
 */
extern int32 __asl_random_with_seed(int32 *localseed)
{
 int32 ranv;

 ranv = asl_loc_rtl_dist_uniform(localseed, MY_LONG_MIN, MY_LONG_MAX);
 return((int32) ranv);
}


/*
 * wrapper to produce random value with a seed
 */
extern int32 __asl_random(void)
{
 int32 ranv;

 ranv = asl_loc_rtl_dist_uniform(&__seed, MY_LONG_MIN, MY_LONG_MAX);
 return((int32) ranv);
}

static int32 asl_loc_rtl_dist_uniform(int32 *seed, int32 start, int32 end)
{
 double r;
 int32 i;

 if (start >= end) return(start);
 if (end != MY_LONG_MAX)
  {
   end++;
   r = asl_loc_uniform(seed, start, end);
   if (r >= 0)
    {
     i = (int32) r;
    }
   else
    {
     i = (int32) (r - 1);
    }
   if (i < start) i = start;
   if (i >= end) i = end-1;
  }
 else if (start != MY_LONG_MIN)
  {
   start--;
   r = asl_loc_uniform(seed, start, end) + 1.0;
   if (r >= 0)
    {
     i = (int32) r;
    }
   else
    {
     i = (int32) (r - 1);
    }
   if (i <= start) i = start+1;
   if (i > end) i = end;
  }
 else
  {
   r = (asl_loc_uniform(seed,start,end) + 2147483648.0)/4294967295.0;
   r = r*4294967296.0 - 2147483648.0;
   if (r >= 0)
    {
     i = (int32) r;
    }
   else
    {
     i = (int32) (r-1);
    }
  }
 return(i);
}

/*
 */
static double asl_loc_uniform(int32 *seed, int32 start, int32 end)
{
 /* stemp - must be 32-bit int */
 union u_s
  {
   float s;
   unsigned int stemp;
  } u;
 double d = 0.00000011920928955078125;
 double a,b,c;

 if ((*seed) == 0) *seed = 259341593;
 if (start >= end)
  {
   a = 0.0;
   b = 2147483647.0;
  }
 else
  {
   a = (double) start;
   b = (double) end;
  }
 *seed = 69069 * (*seed) + 1;
 u.stemp = *seed;

 /* This relies on IEEE floating point format */
 u.stemp = (u.stemp >> 9) | 0x3f800000;
 c = (double) u.s;
 c = c + (c*d);
 c = ((b - a) * (c - 1.0)) + a;
 return(c);
}

extern struct tev_t *__asl_free_next_event(void)
{
 struct tev_t *tevp;
 /* AIV 02/08/12  - these need to be size_t could overflow for 64-bit */
 size_t osize, nsize;

 tevp = __cur_tevp->tenxtp;
//AIV FIXME - make an array of free events
 if (__free_tev_ndx == __free_tev_size)
  {
   osize = __free_tev_size*sizeof(struct tev_t *);
   __free_tev_size += (__free_tev_size/2);
   nsize = __free_tev_size*sizeof(struct tev_t *);
   __free_tevs = (struct tev_t **) __my_realloc(__free_tevs, osize, nsize);
  }
 __free_tevs[__free_tev_ndx++] = __cur_tevp;
 __cur_tevp = tevp;
 __idp = tevp->te_idp;
 return(tevp);
}

#ifndef __STREE__
/*
 * HEAP TIME INSERT/MOVE ROUTINES
 */


/*
 * advance the time to the next minimum event in heap
 * return the new next time head event
 *
 * AIV 01/21/10 - new and improved move_time version used for the move_time
 * inlined routine in v_asmlnk.c - the older version is below this one
 */
#ifdef __CVC_DEBUG__
extern void __asl_move_time(void)
{
 int32 hash;
 struct heap_t **a;
 struct heap_t *min, *max, *minp;
 struct tev_t *tevp, *end_tevp;
 unsigned int l, r, i;

 a = __heap;
 min = a[1];
 __simtime = min->time;
 __heap_size--;
 max = a[__heap_size];
 a[1] = max;
 if (__heap_size > 2) 
  {
   /* AIV - inline heapify this code used for fixed move_time routine */
   /* asl_loc_heapify(); */
   a[0] = a[1];
   minp = a[0];
   l = 2;
   for (;;) 
    {
     r = l+1;
     if (minp->time <= a[l]->time) l = l/2;

     if (a[r]->time < a[l]->time) l = r;
 
     i = r/2;
     if (l == i) break;
 
     minp = a[i];
     a[i] = a[l];
     a[l] = minp;
     l *= 2;
     if (l >= __heap_size) break;
    }
  }

 hash = min->hash;
 __time_hash[hash] = min->next;
 /* save the freed node for reuse */
 __free_heap[__free_heap_ndx++] = min;

 /* AIV 01/12/09 - no need to set __nb_te_hdrp = __nb_dummy_hd */
 end_tevp = min->nb_endp;
 if (end_tevp != NULL)
  {
   __nb_dummy_hd.tenxtp = min->nb_hdrp;
   __nb_te_endp = end_tevp;
   if (min->te_hdrp == NULL)
    {
     /* AIV 07/21/08 - if only have non-blocking events just process */
     /* nb events with this dummy tev */
    return;
  //   return(__handle_nb_list_tevp);
    }
  }

 __nb_te_endp = &__nb_dummy_hd;
 tevp = min->te_hdrp;
 end_tevp = min->te_endp;
 end_tevp->tenxtp = __free_event_tevp;
 //AIV FIXME - make this local to comm.s file
 //end_tevp->tenxtp = (struct tev_t *) 1234;
 /* AIV 02/13/09 - removed the need to use/set __cur_te_hdrp */
 __cur_te_endp = end_tevp;
}

extern void __asl_move_time_last(void)
{
 int32 hash;
 struct heap_t **a;
 struct heap_t *min, *max, *minp;
 struct tev_t *tevp, *end_tevp;
 unsigned int l, r, i;

 a = __heap;
 min = a[1];
 __simtime = min->time;
 __heap_size--;
 max = a[__heap_size];
 a[1] = max;
 if (__heap_size > 2) 
  {
   /* AIV - inline heapify this code used for fixed move_time routine */
   /* asl_loc_heapify(); */
   minp = a[1];
   a[0] = minp;
   r = 3;
   l = 2;
   for (;;) 
    {
     if (a[l]->time >= a[0]->time) l = l/2; 

     if (r < __heap_size) 
      {
       if (a[r]->time < a[l]->time) l = r;
      }
 
     i = r/2;
     if (l == i) break;
 
     minp = a[i];
     a[i] = a[l];
     a[l] = minp;
     l *= 2;
     if (l >= __heap_size) break;
     r = l+1;
    }
  }

 hash = min->hash;
 __time_hash[hash] = min->next;
 /* save the freed node for reuse */
 __free_heap[__free_heap_ndx++] = min;

 /* AIV 01/12/09 - no need to set __nb_te_hdrp = __nb_dummy_hd */
 end_tevp = min->nb_endp;
 if (end_tevp != NULL)
  {
   __nb_dummy_hd.tenxtp = min->nb_hdrp;
   __nb_te_endp = end_tevp;
   if (min->te_hdrp == NULL)
    {
     /* AIV 07/21/08 - if only have non-blocking events just process */
     /* nb events with this dummy tev */
    return;
  //   return(__handle_nb_list_tevp);
    }
  }

 __nb_te_endp = &__nb_dummy_hd;
 tevp = min->te_hdrp;
 end_tevp = min->te_endp;
 end_tevp->tenxtp = __free_event_tevp;
 //AIV FIXME - make this local to comm.s file
 //end_tevp->tenxtp = (struct tev_t *) 1234;
 /* AIV 02/13/09 - removed the need to use/set __cur_te_hdrp */
 __cur_te_endp = end_tevp;
}
#endif
   
/*
 * run the heapify to pass down the max from the min(1) to maintain
 * heap property
 */
/* AIV 12/30/08 - used for move_time fixed lowered code this code doesn't */
/* spill with gcc -O2 on 32-bit */
/*
extern void asl_loc_heapify_no_spill(void)
{
 unsigned int l, r, i;
 struct heap_t *minp;
 struct heap_t **a;

 a = __heap;
 minp = a[1];
 a[0] = minp;
 r = 3;
 l = 2;
 for (;;) 
  {
   if (a[l]->time >= a[0]->time) l = l/2; 

   if (r < __heap_size) 
    {
     if (a[r]->time < a[l]->time) l = r;
    }
 
   i = r/2;
   if (l == i) return;
 
   minp = a[i];
   a[i] = a[l];
   a[l] = minp;
   l *= 2;
   if (l >= __heap_size) return;
   r = l+1;
  }
}
*/

/*
 * spills one word
extern void asl_loc_heapify_better(void)
{
 int32 l, r, i;
 struct heap_t *minp;
 struct heap_t **a;

 i = 1;
 l = 2;
 a = __heap;
 minp = a[1];
 for (;;) 
  {
   r = l + 1; 
   if (a[l]->time >= minp->time) l = i; 

   if (r < __heap_size) 
    {
     if (a[r]->time < a[l]->time) l = r;
    }
 
   if (l == i) return;
 
   a[i] = a[l];
   a[l] = minp;
   i = l;
   l *= 2;
   if (l >= __heap_size) return;
  }
}
*/

/* original heapify routine */
/*
static void asl_loc_heapify_orig(void)
{
 int32 l, r, min, i;
 struct heap_t *minp, *lp, *rp, *ip;
 struct heap_t **a;

 a = __heap;
// AIV FIXME - if known size can optimize
// struct heap_t *tmp;
// if (__heap_size == 3) 
//  {
//   minp = a[1];
//   tmp = a[2];
//   if (minp->time > tmp->time) 
//    {
//     a[1] = tmp;
//     a[2] = minp;
//    }
//   return;
//  }
 min = -1;
 i = 1;
 l = 2;
 for (;;) 
  {
   ip = a[i];
   lp = a[l];
   if (lp->time < ip->time) 
    {
     min = l;
     minp = lp;
    }
   else minp = ip; 

   r = l + 1; 
   if (r < __heap_size)
    {
     rp = a[r];
     if (rp->time < minp->time) 
      {
       minp = rp;
       min = r;
      }
    }
 
   if (minp == ip) return;
 
   a[i] = minp;
   a[min] = ip;
   i = min;
   l = (i << 1); 
   if (l >= __heap_size) return;
  }
}
*/

/*
 * insert an event into the heap timing queue
 */
/* AIV 12/30/08 - use keyword 'inline' here this will inline this  */
/* routine even with -O2 normally this is a -O3 optimization */
/* these common routines should be inlined - produces better code */
static inline void asl_loc_insert_event(struct tev_t *tevp)
{
 word64 schtime;
 struct heap_t *time_hp;
 struct heap_t *hp;
 struct tev_t *prevp;
 word32 h_word, lword;
 int32 hash;

 schtime = tevp->etime;
 tevp->teprevp = NULL;
 /* AIV 10/25/07 - if this is the current event don't set the next */
 /* to NULL perhaps processing should save the next point???? */
 /* AIV LOOKATME - this not positive that allowing __cur_tevp == tevp */
 /* works everytime */
 if (__cur_tevp != tevp) tevp->tenxtp = NULL;

 lword = (word32) schtime;
 h_word = (word32) (schtime >> 32);
 hash = get_time_hash_(lword, h_word);
 
 time_hp = __time_hash[hash];
 /* AIV 10/14/08 - better to write these like this gcc produces better code */
 /* make the rare case the call to search the conflict list */
 /* new time value */
 if (time_hp == NULL)
  {
   hp = asl_loc_add_new_heap_time(tevp, hash);
   hp->te_hdrp = hp->te_endp = tevp;
   hp->nb_hdrp = hp->nb_endp = NULL;
  }
 /* time already has place in heap link in */
 else if (time_hp->time == schtime) 
  {
   /* AIV 10/15/07 - may now be empty if all nodes are linked out */
   tevp->time_hp = time_hp;
   if (time_hp->te_endp == NULL)  
    {
     time_hp->te_endp = tevp;
     time_hp->te_hdrp = tevp;
     return;
    }
   prevp = time_hp->te_endp;
   prevp->tenxtp = tevp;
   tevp->teprevp = prevp;
   time_hp->te_endp = tevp;
   return;
  }
 else asl_loc_conflict_list(tevp, time_hp);
}

/*
 * add an event with a known conflict must search the conflict list to 
 * look for the scheduled time
 */
static void asl_loc_conflict_list(struct tev_t *tevp, struct heap_t *time_hp)
{
 word64 schtime;
 struct heap_t *hp, *next_hp, *last_hp;
 struct tev_t *prevp;

#ifdef __CVC_DEBUG__
 __collision_count++;
#endif

 schtime = tevp->etime;
 /* new time is the new minimum link on to front */
 if (schtime < time_hp->time)
  {
   hp = asl_loc_add_new_heap_time(tevp, time_hp->hash);
   hp->next = time_hp;
   hp->te_hdrp = hp->te_endp = tevp;
   hp->nb_hdrp = hp->nb_endp = NULL;
   return;
  }

 /* if not going on front must search the linear list */
 next_hp = time_hp->next;
 last_hp = time_hp;
 for (; next_hp != NULL; next_hp = next_hp->next)
  {
   /* same time link onto existing time */
   if (next_hp->time == schtime)
    {
     /* AIV 11/29/10 - used a 'bad' hash to find this bug as well */
     /* need to set time_hp - was not setting for if prevp == NULL */
     /* case - need to set these for linking out normally in gate sims */
     tevp->time_hp = next_hp;
     prevp = next_hp->te_endp;
     if (prevp == NULL)  
      {
       next_hp->te_endp = tevp;
       next_hp->te_hdrp = tevp;
       /* DBG remove --- */
#ifdef __CVC_DEBUG__
       if (next_hp->nb_endp == NULL) __misc_terr(__FILE__, __LINE__);
#endif
      /* ----- */
       return;
      }
     prevp->tenxtp = tevp;
     tevp->teprevp = prevp;
     next_hp->te_endp = tevp;
     return;
    }
   /* new spot is in the middle of hash conflict list */
   else if (next_hp->time > schtime)
    {
     hp = asl_loc_add_new_heap_time(tevp, time_hp->hash);
     /* AIV 11/23/10 - need restore __time_hash - to point to original */
     /* time_hp - known to be lowest - new_heap_time set every time */
     __time_hash[time_hp->hash] = time_hp;
     last_hp->next = hp;
     hp->next = next_hp;
     hp->te_hdrp = hp->te_endp = tevp;
     hp->nb_hdrp = hp->nb_endp = NULL;
     return;
    }
   last_hp = next_hp;
  }
 /* the new time is now on the end of the conflict list */
 hp = asl_loc_add_new_heap_time(tevp, time_hp->hash);
 /* AIV 11/23/10 - need restore __time_hash - to point to original */
 /* time_hp - known to be lowest - new_heap_time set every time */
 __time_hash[time_hp->hash] = time_hp;
 last_hp->next = hp;
 hp->te_hdrp = hp->te_endp = tevp;
 hp->nb_hdrp = hp->nb_endp = NULL;
}

/*
 * insert a non-blocking event into the heap timing queue
 * same as regular expcept placed into nb_ head/tail and do not need to
 * save the previous event - never linked out
 */
/* AIV 12/30/08 - use keyword 'inline' here this will inline this  */
/* routine even with -O2 normally this is a -O3 optimization */
/* these common routines should be inlined - produces better code */
static inline void asl_loc_insert_event_nb(struct tev_t *tevp)
{
 word64 schtime;
 struct heap_t *time_hp;
 struct tev_t *endp;
 word32 h_word, lword;
 int32 hash;


 schtime = tevp->etime;
 /* AIV 02/13/09 - save the last nb delay heap and compare times */
 /* it is common for rtl to have multiple 'r <= #1 1' statements */
 /* it is faster to just check if it is the same as the last */
 /* AIV LOOKATME - could just have a seperate #1 nb list which then moves */
 /* with the next time movement to the regular nb list */
 time_hp = __last_nb_hp;
 if (schtime == time_hp->time) 
  {
   endp = time_hp->nb_endp;
   time_hp->nb_endp = tevp;
   if (endp == NULL)  time_hp->nb_hdrp = tevp;
   else endp->tenxtp = tevp;
   return;
  }
 lword = (word32) schtime;
 h_word = (word32) (schtime >> 32);
 hash = get_time_hash_(lword, h_word);

 /* AIV 10/14/08 - better to write these like this gcc produces better code */
 /* make the rare case the call to search the conflict list */
 time_hp = __time_hash[hash];
 /* new time value */
 if (time_hp == NULL)
  {
   time_hp = asl_loc_add_new_heap_time(tevp, hash);
   __last_nb_hp = time_hp;
   time_hp->nb_hdrp = time_hp->nb_endp = tevp;
   time_hp->te_hdrp = time_hp->te_endp = NULL;
  }
 /* time already has place in heap link in */
 else if (schtime == time_hp->time) 
  {
   /* AIV 09/09/08 - fixed some redundant code better to write like this */
   __last_nb_hp = time_hp;
   endp = time_hp->nb_endp;
   time_hp->nb_endp = tevp;
   if (endp == NULL)  time_hp->nb_hdrp = tevp;
   else endp->tenxtp = tevp;
  }
 else asl_loc_nb_conflict_list(tevp, time_hp);
}

/*
 * all same #del version - same just do not check __last_nb_hp time
 */
static inline void asl_loc_insert_event_nb_t(struct tev_t *tevp)
{
 word64 schtime;
 struct heap_t *time_hp;
 word32 h_word, lword;
 int32 hash;


 schtime = tevp->etime;
 lword = (word32) schtime;
 h_word = (word32) (schtime >> 32);
 hash = get_time_hash_(lword, h_word);

 /* AIV 10/14/08 - better to write these like this gcc produces better code */
 /* make the rare case the call to search the conflict list */
 time_hp = __time_hash[hash];
 /* new time value */
 if (time_hp == NULL)
  {
   time_hp = asl_loc_add_new_heap_time(tevp, hash);
   __last_nb_hp = time_hp;
   time_hp->nb_hdrp = time_hp->nb_endp = tevp;
   time_hp->te_hdrp = time_hp->te_endp = NULL;
  }
 /* time already has place in heap link in */
 else if (schtime == time_hp->time) 
  {
   /* AIV 09/09/08 - fixed some redundant code better to write like this */
   __last_nb_hp = time_hp;
   time_hp->nb_endp = tevp;
   time_hp->nb_hdrp = tevp;
  }
 else asl_loc_nb_conflict_list(tevp, time_hp);
}

/*
 * gcc inlines if there is only one call
 * AIV FIXME - this is a hack - there is some keyword to tell gcc not
 * to inline a function?????
 */
extern void __garbage_calls(void)
{
 asl_loc_nb_conflict_list(NULL, NULL);
 asl_loc_conflict_list(NULL, NULL);
}

/*
 * add an nb event with a known conflict must search the conflict list to 
 * look for the scheduled time
 *
 * AIV 11/30/09 - need to set __last_nb_hp for new code to work
 */
static void asl_loc_nb_conflict_list(struct tev_t *tevp, struct heap_t *time_hp)
{
 word64 schtime;
 struct heap_t *hp, *next_hp, *last_hp;
 struct tev_t *endp;

#ifdef __CVC_DEBUG__
 __collision_count++;
#endif

 schtime = tevp->etime;
 /* new time is the new minimum link on to front */
 if (schtime < time_hp->time)
  {
   hp = asl_loc_add_new_heap_time(tevp, time_hp->hash);
   __last_nb_hp = hp;
   hp->next = time_hp;
   hp->nb_hdrp = hp->nb_endp = tevp;
   hp->te_hdrp = hp->te_endp = NULL;
   return;
  }

 /* if not going on front must search the linear list */
 next_hp = time_hp->next;
 last_hp = time_hp;
 for (; next_hp != NULL; next_hp = next_hp->next)
  {
   /* same time link onto existing time */
   if (next_hp->time == schtime)
    {
     endp = next_hp->nb_endp;
     /* if NULL it doesn't yet contain nb events */
     /* AIV 11/23/10 - need to set last nb here */
     __last_nb_hp = next_hp;
     if (endp == NULL)  
      {
       next_hp->nb_endp = tevp;
       next_hp->nb_hdrp = tevp;
       /* DBG remove --- */
#ifdef __CVC_DEBUG__
       if (next_hp->te_endp == NULL) __misc_terr(__FILE__, __LINE__);
#endif
       /* ------ */
       return;
      }
     endp->tenxtp = tevp;
     tevp->teprevp = endp;
     next_hp->nb_endp = tevp;
     return;
    }
   /* new spot is in the middle of hash conflict list */
   else if (next_hp->time > schtime)
    {
     hp = asl_loc_add_new_heap_time(tevp, time_hp->hash);
     /* AIV 11/23/10 - need restore __time_hash - to point to original */
     /* time_hp - known to be lowest - new_heap_time set every time */
     __time_hash[time_hp->hash] = time_hp;
     __last_nb_hp = hp;
     last_hp->next = hp;
     hp->next = next_hp;
     hp->nb_hdrp = hp->nb_endp = tevp;
     hp->te_hdrp = hp->te_endp = NULL;
     return;
    }
   last_hp = next_hp;
  }
 /* the new time is now on the end of the conflict list */
 hp = asl_loc_add_new_heap_time(tevp, time_hp->hash);
 /* AIV 11/23/10 - need restore __time_hash - to point to original */
 /* time_hp - known to be lowest - new_heap_time set every time */
 __time_hash[time_hp->hash] = time_hp;
 __last_nb_hp = hp;
 last_hp->next = hp;
 hp->nb_hdrp = hp->nb_endp = tevp;
 hp->te_hdrp = hp->te_endp = NULL;
}

/*
 * add a new time event to the heap - the first event at any given time
 */
static struct heap_t *asl_loc_add_new_heap_time(struct tev_t *tevp, int32 hash)
{
 word64 schtime;
 int32 i;
 struct heap_t *hp, *parent_hp;
 struct heap_t **a;

 /* AIV 04/05/10 - first try to grow heap size - this is rare becuase */
 /* init to 4096 - diff time elements */
 /* AIV 02/09/12 - made some heap changes here - if this is known to have */
 /* to grow there will be no free heap so can just check if free_ndx */
 /* is 1 need to grow the heap and free arrays */
 /* AIV LOOKATME - is this better????
     free_ndx = --__free_heap_ndx;
     if (free_ndx == 0)
      {
      asl_loc_grow_event_heap();
      free_ndx = __free_heap_ndx;
    }
    hp = __free_heap[free_ndx];
 */
 /* AIV 04/05/10 - first try to grow heap size - this is rare becuase */
 /* init to 4096 - diff time elements */
 if (__heap_size == __heap_maxsize)
  {
   asl_loc_grow_event_heap();
  }

 /* AIV 04/05/10 - removed if stmt since now grown along with the heap */
 /* no element is known to alloced */
 hp = __free_heap[--__free_heap_ndx];

 tevp->time_hp = hp;
 tevp->teprevp = NULL;

 schtime = tevp->etime;
 hp->hash = hash;
 hp->time = schtime;
 hp->next = NULL;
 __time_hash[hash] = hp;


 /* AIV 10/14/08 - better to rewrote this loop */
 /* AIV 12/30/08 - gcc produces better code with is tmp assign outside */
 /* of the loop */
 a = __heap;
 for (i = __heap_size; i > 1; i = PARENT(i))
  {
   parent_hp = a[PARENT(i)];
   if (parent_hp->time < schtime) break;
   a[i] = parent_hp;
  }
 __heap_size++;
 a[i] = hp;
 return(hp);
}
 
/*
 * grow the event heap array and the freed as well
 */
static void asl_loc_grow_event_heap(void)
{
 size_t olen, osize, nsize;
 struct heap_t *hpt;
 int32 i, add_len;

 olen = __heap_maxsize;
 osize = olen*sizeof(struct heap_t *);
 add_len = (olen/2);
 __heap_maxsize += add_len;
 nsize = __heap_maxsize*sizeof(struct heap_t *);
 __heap = (struct heap_t **) __my_realloc((char *) __heap, osize, nsize);
 /* grow the array which stores the free heap time elements */
 /* AIV 02/09/12 - this wasn't exactly right - __free_heap_ndx is known to */
 /* be 1 (empty) if growing.  Also it was leaking memory only need to grow */ 
 /* to 'add_len' size here and put into the free list */
 /* no reason to realloc just free and malloc the new size */
 __my_free(__free_heap, osize);
 __free_heap = (struct heap_t **) __my_malloc(nsize);
 hpt = (struct heap_t *) __my_malloc(add_len*sizeof(struct heap_t));
 /* AIV 04/05/10 - now must alloc the number of heap_t structs */
 /* this saves having to do an 'if' stmt everytime a new time is added */
 /* just alloc here so size know to be good */
 add_len++;
 for (i = 1; i < add_len; i++)
  {
   __free_heap[i] = hpt;
   hpt++;
  }
 __free_heap_ndx = add_len;
}
#endif

/*
 * handle a malloced net change
 * these only happen from wrapper calls or net change happens again prior to 
 * processing
 */
//AIV FIXME - make this illegal - called from wrappers and setup code
extern void __asl_process_alloced_nchg(void)
{
 struct net_t *np;
 struct nchglst_t *nchglp;
 
 /* AIV LOOKATME BEWARE - machine dependent - nchg is in register */
 /* %eax see v_asmlink for next net change event processing */
 /* nchglp = __cur_nchglp; */
#ifdef __CVC32__
 __asm__ ("movl %%eax, %0" : "=r" (nchglp):);
#else
 __asm__ ("movq %%rax, %0" : "=r" (nchglp):);
#endif
 nchglp->triggered = FALSE;
 __nchged_delayed_mipd = nchglp->delayed_mipd;  
 np = nchglp->chgnp;
 __idp = nchglp->nchg_idp;
 __idp[np->nchgaction_ofs] &= (~NCHG_ALL_CHGED);

 __nchged_i1 = nchglp->bi1;
 __nchged_i2 = nchglp->bi2;
 if (np->enter_dce != NULL)
  {
   /* AIV 09/14/06 - if has pli access must check for dce cb */
   /* linked on to the front to the dcelst */
   /* AIV 05/13/09 - access level > 2 for call backs */
   if (np->pli_access >= 2) __asl_chk_dce_cbvc(np);
   /* AIV 01/04/07 - need to tell gcc that %esi cannot be used here */
  #ifdef __CVC32__
   __asm__ ("movl __idp, %%esi" :: :"%esi");
  #else
   __asm__ ("movq __idp, %%r15" :: :"%r15");
  #endif
   (np->enter_dce)();
  }
 if (np->enter_npp != NULL)
  {
   /* AIV 01/04/07 - need to tell gcc that %esi cannot be used here */
  #ifdef __CVC32__
   __asm__ ("movl __idp, %%esi" :: :"%esi");
  #else
   __asm__ ("movq __idp, %%r15" :: :"%r15");
  #endif
   (np->enter_npp)();
  }
/* AIV LOOKATME - which is better??????
 int32 osize, nsize;
 if (__nchg_free_ndx == __nchg_free_size)
  {
   osize = __nchg_free_size*sizeof(struct nchglst_t);
   __nchg_free_size += (__nchg_free_size/2);
   nsize = __nchg_free_size*sizeof(struct nchglst_t);
   __nchg_freed = (struct nchglst_t **) 
    __my_realloc(__nchg_freed, osize, nsize);
  }
 __nchg_freed[__nchg_free_ndx++] = nchglp;
*/
 /* rare enough event so can just free it */
 __my_free(nchglp, sizeof(struct nchglst_t));
}

//AIV REMOVEME - for debugging
extern void __asl_misc_terr(void)
{
 __misc_terr(__FILE__, __LINE__);
}

/* convert scalar x/z to 0 table */
const word32 __asl_4to2[] = {0, 1, 0, 0 };

/* udp byte table values */
const word32 __asl_to_uvaltab[] = {0, 1, 2, 2 };
const word32 __asl_to_noztab[] = {0, 1, 3, 3 };

const word32 __redand[256] = {
0, 1, 0, 1, 3, 3, 3, 3, 0, 1, 0, 1, 3, 3, 3, 3, 0, 1, 0, 3, 0, 
3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 1, 0, 0, 0, 1, 0, 
0, 3, 3, 0, 0, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 
0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0, 3, 0, 3, 0, 
3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 1, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 0, 
0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 
3, 3, 3, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 
0, 0, 3, 0, 0, 0, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0, 
0, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

const word32 __nand[256] = {
1, 0, 1, 0, 3, 3, 3, 3, 1, 0, 1, 0, 3, 3, 3, 3, 1, 0, 1, 3, 1, 
3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 0, 1, 1, 1, 0, 1, 
1, 3, 3, 1, 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 
1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 1, 3, 1, 
3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 
1, 1, 0, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 1, 
1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 3, 
3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 
1, 1, 3, 1, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 
1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

const word32 __redor[256] = {
0, 1, 0, 1, 3, 3, 3, 3, 0, 1, 0, 1, 3, 3, 3, 3, 0, 1, 3, 1, 3, 
1, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 1, 1, 1, 0, 1, 1, 1, 3, 
3, 1, 1, 3, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 3, 3, 3, 
3, 3, 3, 0, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 
3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 1, 3, 1, 3, 
1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 
1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 3, 
1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 
1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 
1, 1, 1, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 
3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

const word32 __nor[256] = {
1, 0, 1, 0, 3, 3, 3, 3, 1, 0, 1, 0, 3, 3, 3, 3, 1, 0, 3, 0, 3, 
0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 1, 0, 0, 0, 3, 
3, 0, 0, 3, 3, 0, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 
3, 3, 3, 1, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 
3, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 0, 3, 0, 3, 
0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 3, 
0, 3, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 
0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 
0, 0, 0, 3, 0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 
3, 0, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

const word32 __redxor[256] = {
0, 1, 0, 1, 3, 3, 3, 3, 0, 1, 0, 1, 3, 3, 3, 3, 0, 1, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 1, 1, 0, 0, 1, 1, 0, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 
0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

const word32 __redxnor[256] = {
1, 0, 1, 0, 3, 3, 3, 3, 1, 0, 1, 0, 3, 3, 3, 3, 1, 0, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 1, 1, 0, 0, 1, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 
1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

const word32 __gbuf[4] = {0, 1, 3, 3};

const word32 __gnot[4] = {1, 0, 3, 3};

const word32 __gate_ormask_2_0[4] = {0, 1, 4, 5};
const word32 __gate_ormask_2_1[4] = {0, 2, 8, 10};
const word32 __gate_ormask_2_2[4] = {0, 4, 16, 20};
const word32 __gate_ormask_2_3[4] = {0, 8, 32, 40};
const word32 __gate_ormask_3_0[4] = {0, 1, 8, 9};
const word32 __gate_ormask_3_1[4] = {0, 2, 16, 18};
const word32 __gate_ormask_3_2[4] = {0, 4, 32, 36};
const word32 __gate_ormask_3_3[4] = {0, 8, 64, 72};
const word32 __gate_ormask_4_0[4] = {0, 1, 16, 17};
const word32 __gate_ormask_4_1[4] = {0, 2, 32, 34};
const word32 __gate_ormask_4_2[4] = {0, 4, 64, 68};
const word32 __gate_ormask_4_3[4] = {0, 8, 128, 136};

const word32 __bufif0_strval_tab[16] = {216,217,219,219,2,2,2,2,195,27,219,219,195,27,219,219};
const word32 __bufif1_strval_tab[16] = {2,2,2,2,216,217,219,219,195,27,219,219,195,27,219,219,};
const word32 __notif0_strval_tab[16] = {217,216,219,219,2,2,2,2,27,195,219,219,27,195,219,219,};
const word32 __notif1_strval_tab[16] = {2,2,2,2,217,216,219,219,27,195,219,219,27,195,219,219,};
const word32 __bufif0_strongx_tab[16] = {108,109,111,111,2,2,2,2,99,15,111,111,99,15,111,111};
const word32 __bufif1_strongx_tab[16] = {2,2,2,2,108,109,111,111,99,15,111,111,99,15,111,111,};
const word32 __notif0_strongx_tab[16] = {109,108,111,111,2,2,2,2,15,99,111,111,15,99,111,111,};
const word32 __notif1_strongx_tab[16] = {2,2,2,2,109,108,111,111,15,99,111,111,15,99,111,111,};
const word32 __bufif0_hiz_tab[16] = {2,73,11,11,2,2,2,2,0,11,11,11,0,11,11,11};
const word32 __bufif1_hiz_tab[16] = {2,2,2,2,2,73,11,11,0,11,11,11,0,11,11,11,};
const word32 __notif0_hiz_tab[16] = {73,2,11,11,2,2,2,2,11,0,11,11,11,0,11,11,};
const word32 __notif1_hiz_tab[16] = {2,2,2,2,73,2,11,11,11,0,11,11,11,0,11,11,};
const word32 __bufif0_pull0_tab[16] = {216,145,211,211,2,2,2,2,195,19,211,211,195,19,211,211};
const word32 __bufif1_pull0_tab[16] = {2,2,2,2,216,145,211,211,195,19,211,211,195,19,211,211,};
const word32 __notif0_pull0_tab[16] = {145,216,211,211,2,2,2,2,19,195,211,211,19,195,211,211,};
const word32 __notif1_pull0_tab[16] = {2,2,2,2,145,216,211,211,19,195,211,211,19,195,211,211,};
const word32 __bufif0_pull1_tab[16] = {216,181,215,215,2,2,2,2,195,23,215,215,195,23,215,215};
const word32 __bufif1_pull1_tab[16] = {2,2,2,2,216,181,215,215,195,23,215,215,195,23,215,215,};
const word32 __notif0_pull1_tab[16] = {181,216,215,215,2,2,2,2,23,195,215,215,23,195,215,215,};
const word32 __notif1_pull1_tab[16] = {2,2,2,2,181,216,215,215,23,195,215,215,23,195,215,215,};
const word32 __bufif0_supply0_tab[16] = {252,145,243,243,2,2,2,2,227,19,243,243,227,19,243,243};
const word32 __bufif1_supply0_tab[16] = {2,2,2,2,252,145,243,243,227,19,243,243,227,19,243,243,};
const word32 __notif0_supply0_tab[16] = {145,252,243,243,2,2,2,2,19,227,243,243,19,227,243,243,};
const word32 __notif1_supply0_tab[16] = {2,2,2,2,145,252,243,243,19,227,243,243,19,227,243,243,};
const word32 __bufif0_supply1_tab[16] = {252,181,247,247,2,2,2,2,227,23,247,247,227,23,247,247};
const word32 __bufif1_supply1_tab[16] = {2,2,2,2,252,181,247,247,227,23,247,247,227,23,247,247,};
const word32 __notif0_supply1_tab[16] = {181,252,247,247,2,2,2,2,23,227,247,247,23,227,247,247,};
const word32 __notif1_supply1_tab[16] = {2,2,2,2,181,252,247,247,23,227,247,247,23,227,247,247,};

/* AIV 03/09/09 - combined these array into common pattern */
/* since they have the same values */
const word32 __p1_svals[16] = {0,1,3,3,1,0,3,3,3,3,3,3,3,3,3,3};
const word32 __p2_svals[16] = {1,1,3,3,0,1,3,3,3,3,3,3,3,3,3,3};
const word32 __p3_svals[16] = {1,0,3,3,0,1,3,3,3,3,3,3,3,3,3,3};
const word32 __p4_svals[16] = {0,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3};
const word32 __shift_svals[16] = {0,1,2,3,0,0,0,0,3,3,3,3,3,3,3,3};

const word32 __times_svals[16] = {0,0,3,3,0,1,3,3,3,3,3,3,3,3,3,3};
const word32 __div_svals[16] = {3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3};
const word32 __mod_svals[16] = {3,3,3,3,0,0,3,3,3,3,3,3,3,3,3,3};
const word32 __bitand_svals[16] = {0,0,0,0,0,1,3,3,0,3,3,3,0,3,3,3};
const word32 __relgt_svals[16] = {0,1,3,3,0,0,3,3,3,3,3,3,3,3,3,3};
const word32 __relle_svals[16] = {1,0,3,3,1,1,3,3,3,3,3,3,3,3,3,3};
const word32 __rellt_svals[16] = {0,0,3,3,1,0,3,3,3,3,3,3,3,3,3,3};
const word32 __relcneq_svals[16] = {0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0};
const word32 __relceq_svals[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
#ifdef __XPROP__
const word32 __bitor_x_svals[16] = {0,1,3,3,1,1,3,3,3,3,3,3,3,3,3,3};
#endif

/* AIV 03/09/09 - removed some tables all these can share a table */
/* since they have the same values */
/* pattern one {0, 1, 3, 3} - (-, &, |, ^) */
const word32 __un_p1_svals[4] =     {0,1,3,3};
/* pattern two {1, 0, 3, 3} - (~, !, ^~) */
const word32 __un_p2_svals[4] =     {1,0,3,3};
/* AIV 09/21/09 - __bool_svals is just pattern one */

const word32 __qcol_comb_svals[16] = {0,3,3,3,3,1,3,3,3,3,3,3,3,3,3,3};

const word32 __nand_svals[16] = {1,1,1,1,1,0,3,3,1,3,3,3,1,3,3,3};
const word32 __nor_svals[16] = {1,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3};

const word32 __and_g3[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3};
const word32 __nand_g3[64] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3};
const word32 __or_g3[64] = {0,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3};
const word32 __nor_g3[64] = {1,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3};
const word32 __xor_g3[64] = {0,1,3,3,1,0,3,3,3,3,3,3,3,3,3,3,1,0,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
const word32 __xnor_g3[64] = {1,0,3,3,0,1,3,3,3,3,3,3,3,3,3,3,0,1,3,3,1,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

const word32 __and_g4[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3};
const word32 __nand_g4[256] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3,1,1,1,1,1,3,3,3,1,3,3,3,1,3,3,3};
const word32 __or_g4[256] = {0,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3,3,1,3,3,1,1,1,1,3,1,3,3,3,1,3,3};
const word32 __nor_g4[256] = {1,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3,3,0,3,3,0,0,0,0,3,0,3,3,3,0,3,3};
const word32 __xor_g4[256] = {0,1,3,3,1,0,3,3,3,3,3,3,3,3,3,3,1,0,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,0,3,3,0,1,3,3,3,3,3,3,3,3,3,3,0,1,3,3,1,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
const word32 __xnor_g4[256] = {1,0,3,3,0,1,3,3,3,3,3,3,3,3,3,3,0,1,3,3,1,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,1,0,3,3,3,3,3,3,3,3,3,3,1,0,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

/* AIV 10/14/08 compiler now has two separate routines for edge types */
/* same as __epair_tab masked with E_POSEDGE and E_NEGEDGE */
/* if 0 value is 0 otherwise 1 */
const word32 __epair_pos_tab[] = { 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 
 0 };
const word32 __epair_neg_tab[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 
 0 };

/* AIV 10/16/08 - same as interp except size is word */
const word32 __asl_epair_tab[] =
 { NOEDGE, EDGE01, EDGE0X, EDGE0X, EDGE10, NOEDGE, EDGE1X, EDGE1X,
   EDGEX0, EDGEX1, NOEDGE, NOEDGE, EDGEX0, EDGEX1, NOEDGE, NOEDGE };

#ifdef __XPROP__
/* same as epair_tab, but is TRUE is edge is on an 'X' */
const word32 __asl_is_xedge_tab[16] =
 { FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE,
   FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE };
#endif

/* AIV 10/16/08 - same as interp except size is word */
const word32 __asl_stren_map_tab[] = {

 0, 0, 0x02, 0, 0x02, 0x25, 0, 0x07,
 0x02, 0x49, 0, 0x0b, 0x02, 0x6d, 0, 0x0f,

 0x02, 0x91, 0, 0x13, 0x02, 0xb5, 0, 0x17,
 0x02, 0xd9, 0, 0x1b, 0x02, 0xfd, 0, 0x1f,

 0x24, 0x02, 0, 0x23, 0x24, 0x25, 0, 0x27,
 0x24, 0x49, 0, 0x2b, 0x24, 0x6d, 0, 0x2f,

 0x24, 0x91, 0, 0x33, 0x24, 0xb5, 0, 0x37,
 0x24, 0xd9, 0, 0x3b, 0x24, 0xfd, 0, 0x3f,

 0x48, 0x02, 0, 0x43, 0x48, 0x25, 0, 0x47,
 0x48, 0x49, 0, 0x4b, 0x48, 0x6d, 0, 0x4f,

 0x48, 0x91, 0, 0x53, 0x48, 0xb5, 0, 0x57,
 0x48, 0xd9, 0, 0x5b, 0x49, 0xfd, 0, 0x5f,

 0x6c, 0x02, 0, 0x63, 0x6c, 0x25, 0, 0x67,
 0x6c, 0x49, 0, 0x6b, 0x6c, 0x6d, 0, 0x6f,

 0x6c, 0x91, 0, 0x73, 0x6c, 0xb5, 0, 0x77,
 0x6c, 0xd9, 0, 0x7b, 0x6c, 0xfd, 0, 0x7f,

 0x90, 0x02, 0, 0x83, 0x90, 0x25, 0, 0x87,
 0x90, 0x49, 0, 0x8b, 0x90, 0x6d, 0, 0x8f,

 0x90, 0x91, 0, 0x93, 0x90, 0xb5, 0, 0x97,
 0x90, 0xd9, 0, 0x9b, 0x90, 0xfd, 0, 0x9f,

 0xb4, 0x02, 0, 0xa3, 0xb4, 0x25, 0, 0xa7,
 0xb4, 0x49, 0, 0xab, 0xb4, 0x6d, 0, 0xaf,

 0xb4, 0x91, 0, 0xb3, 0xb4, 0xb5, 0, 0xb7,
 0xb4, 0xb9, 0, 0xbb, 0xb4, 0xfd, 0, 0xbf,

 0xd8, 0x02, 0, 0xc3, 0xd8, 0x25, 0, 0xc7,
 0xd8, 0x49, 0, 0xcb, 0xd8, 0x6d, 0, 0xcf,

 0xd8, 0x91, 0, 0xd3, 0xd8, 0xb5, 0, 0xd7,
 0xd8, 0xd9, 0, 0xdb, 0xd8, 0xfd, 0, 0xdf,

 0xfc, 0x02, 0, 0xe3, 0xfc, 0x25, 0, 0xe7,
 0xfc, 0x49, 0, 0xeb, 0xfc, 0x6d, 0, 0xef,

 0xfc, 0x91, 0, 0xf3, 0xfc, 0xb5, 0, 0xf7,
 0xfc, 0xd9, 0, 0xfb, 0xfc, 0xfd, 0, 0xff
};

#ifdef __XPROP__
const word32 __asl_popcount_tab[256] =
{
 0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
 1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
 1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
 1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
 2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
 3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};
#endif

/*
 * ROUTINES FOR SystemVerilog (SV) LIBS
 */

/*
 * ROUTINES FOR SV STRING LIBS
 */

/*
 * assign nchars from rgap into string np
 */
extern void __asl_st_string_const(struct net_t *np, word32 *rgap, int32 nchars)
{
 int32 cur_size, new_size, cur_ndx;
 char *cp;
 t_midat *idp;

 /* DBG remove --- */
 if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 if (nchars <= 0) return;
 idp = &(__idp[np->nva_ofs]);
 cp = (char *) idp[STR_IDP_OFS];
 cur_ndx = (int32) idp[STR_IDP_NDX_OFS]; 
 cur_size = idp[STR_IDP_SIZE_OFS]; 
 /* get the number of chars to store */
 /* may have to grow the size of the string */
 if (nchars > cur_size)
  {
   new_size = 2*nchars;
   cp = __my_realloc(cp, cur_size, new_size);
   idp[STR_IDP_OFS] = (t_midat) cp;
   idp[STR_IDP_SIZE_OFS] = new_size; 
  }
 strncpy(cp, (char *) rgap, nchars);
 idp[STR_IDP_NDX_OFS] = nchars; 
}

/*
 * assign string rhs_np into lhs_np
 */
extern void __asl_st_string_var(struct net_t *lhs_np, struct net_t *rhs_np)
{
 int32 nchars;
 word32 *rgap;
 t_midat *idp;

 idp = &(__idp[rhs_np->nva_ofs]);
 nchars = (int32) idp[STR_IDP_NDX_OFS]; 
 rgap = (word32 *) idp[STR_IDP_OFS];
 __asl_st_string_const(lhs_np, rgap, nchars);
}

/*
 * assign rhsx into string lhs_np
 * notice uses interpreter for evaluating rhsx
 */
extern void __asl_st_string_rhsx(struct net_t *lhs_np, struct expr_t *rhsx)
{
 int32 nchars;
 struct xstk_t *xsp;

 xsp = __eval_xpr(rhsx);
 nchars = (xsp->xslen+7)/8;
 __asl_st_string_const(lhs_np, xsp->ap, nchars);
 __pop_xstk(); 
}

/*
 * store a char into string np
 */
extern void __asl_st_string_byte(struct net_t *np, int32 bi, word32 *wp)
{
 int32 cur_ndx;
 char *cp;
 t_midat *idp;

 /* just store a byte into the string */
 idp = &(__idp[np->nva_ofs]);
 cp = (char *) idp[STR_IDP_OFS];
 cur_ndx = (int32) idp[STR_IDP_NDX_OFS]; 
 if (bi > cur_ndx) return;
 /* string is stored backwards */
 cp[cur_ndx-bi-1] = (char) wp[0];
}

/*
 * store a rhs constant value into a string array
 */
extern void __asl_st_string_array_const(struct net_t *np, int32 arri, 
 word32 *wp, int32 nchars)
{
 int32 cur_size, new_size, cur_ndx;
 char *cp;
 t_midat *idp;

 /* if out of range nothing to do */
 if (arri == -1) return;

 /* string arrays are stored 3* for each element */
 idp = &(__idp[np->nva_ofs+(arri*STR_IDP_WLEN)]);
 cp = (char *) idp[STR_IDP_OFS];
 cur_ndx = (int32) idp[STR_IDP_NDX_OFS]; 
 cur_size = idp[STR_IDP_SIZE_OFS]; 
 /* may have to grow current string element size */
 if (nchars > cur_size)
  {
   new_size = 2*nchars;
   cp = __my_realloc(cp, cur_size, new_size);
   idp[STR_IDP_OFS] = (t_midat) cp;
   idp[STR_IDP_SIZE_OFS] = new_size; 
  }
 strncpy(cp, (char *) wp, nchars);
 idp[STR_IDP_NDX_OFS] = nchars; 
}

/*
 * store a rhs string ID into a string array
 */
extern void __asl_st_string_array_var(struct net_t *lhs_np, 
 struct net_t *rhs_np, int32 arri)
{
 int32 nchars;
 char *cp;
 t_midat *idp;

 /* string arrays are stored 3* for each element */
 idp = &(__idp[rhs_np->nva_ofs]);
 cp = (char *) idp[STR_IDP_OFS];
 nchars = (int32) idp[STR_IDP_NDX_OFS]; 
 __asl_st_string_array_const(lhs_np, arri, (word32 *) cp, nchars);
}

/*
 * store a rhs expr into a string array
 */
extern void __asl_st_string_array_rhsx(struct net_t *lhs_np, 
 struct expr_t *rhsx, int32 arri)
{
 int32 nchars;
 struct xstk_t *xsp;

 /* string arrays are stored 3* for each element */
 xsp = __eval_xpr(rhsx);
 nchars = (xsp->xslen+7)/8;
 __asl_st_string_array_const(lhs_np, arri, xsp->ap, nchars);
 __pop_xstk(); 
}

/*
 * get one byte (char) from string np
 */
extern word32 __asl_get_string_byte(struct net_t *np, int32 bi)
{
 int32 cur_ndx;
 char *cp, c;
 t_midat *idp;

 /* just store a byte into the string */
 idp = &(__idp[np->nva_ofs]);
 cp = (char *) idp[STR_IDP_OFS];
 cur_ndx = (int32) idp[STR_IDP_NDX_OFS]; 
 if (bi > cur_ndx) return(0);
 c = cp[cur_ndx-bi-1];
 return((word32) c);
}

/*
 * load a SV string as a C char * to pass to a DPI function 
 */
extern char *__asl_sv_dpi_string(struct expr_t *xp)
{
 int32 chlen;
 char *chp; 
 struct xstk_t *xsp;

 xsp = __eval_xpr(xp); 
 chp = __vval_to_vstr(xsp->ap, xsp->xslen,  &chlen);
 //AIV LOOKATME - leaking memory here - for both stack and char * pointer 
 /*
#ifdef __CVC32__
 __asm__ ("movl %0, %%ecx" : : "g" (chlen));
#else
 __asm__ ("movq %0, %%rcx" : : "g" (chlen));
#endif
  */
 return(chp);
}

/*
 * store SV string (char *) cp_ti into string np
 */
extern void __asl_sv_dpi_string_store(struct net_t *np, char **iicp)
{
 int32 nchars, i, new_size, cur_ndx, cur_size;
 t_midat *idp;
 char *cp, *icp;

 icp = *iicp;
 nchars = strlen(icp);
 if (nchars <= 0) return;
 idp = &(__idp[np->nva_ofs]);
 cp = (char *) idp[STR_IDP_OFS];
 cur_ndx = (int32) idp[STR_IDP_NDX_OFS]; 
 cur_size = idp[STR_IDP_SIZE_OFS]; 
 /* may have to grow current string element size */
 if (nchars > cur_size)
  {
   new_size = 2*nchars;
   cp = __my_realloc(cp, cur_size, new_size);
   idp[STR_IDP_OFS] = (t_midat) cp;
   idp[STR_IDP_SIZE_OFS] = new_size; 
  }

 cp[nchars] = '\0';
 cp = &(cp[nchars-1]);
 for (i = 0; i < nchars; i++)
  {
   *cp = icp[i];
   cp--;
  }
 idp[STR_IDP_NDX_OFS] = nchars; 
}

/*
 * handle the string binops (==, !=, etc)
 */
extern int32 __asl_string_binop(struct expr_t *ndp)
{
 int32 rta, cmp_val, xslen1;
 struct xstk_t *xsp1, *xsp2;

 xsp1 = __eval2_xpr(ndp->lu.x);
 xsp2 = __eval2_xpr(ndp->ru.x);

 rta = 0;
 xslen1 = xsp1->xslen;
 switch (ndp->optyp) {
  case /* > */ STRRELGT:
   if (xslen1 > xsp2->xslen) rta = 1;
   else
    {
     cmp_val = asl_loc_cmp_str_vals(xsp1->ap, xsp2->ap, xslen1);
     rta = (cmp_val > 0);
    }
   break;
  case /* >= */ STRRELGE:
   if (xslen1 >= xsp2->xslen) rta = 1;
   else
    {
     cmp_val = asl_loc_cmp_str_vals(xsp1->ap, xsp2->ap, xslen1);
     rta = (cmp_val >= 0);
    }
   break;
  case /* < */ STRRELLT:
   if (xslen1 < xsp2->xslen) rta = 1;
   else
    {
     cmp_val = asl_loc_cmp_str_vals(xsp1->ap, xsp2->ap, xslen1);
     rta = (cmp_val < 0);
    }
   break;
  case /* <= */ STRRELLE:
   if (xslen1 <= xsp2->xslen) rta = 1;
   else
    {
     cmp_val = asl_loc_cmp_str_vals(xsp1->ap, xsp2->ap, xslen1);
     rta = (cmp_val <= 0);
    }
   break;
  case /* == */ STRRELEQ:
   if (xslen1 != xsp2->xslen) rta = 0;
   else
    {
     cmp_val = asl_loc_cmp_str_vals(xsp1->ap, xsp2->ap, xslen1);
     rta = (cmp_val == 0);
    }
   break;
  case /* != */ STRRELNEQ:
   if (xslen1 != xsp2->xslen) rta = 1;
   else
    {
     cmp_val = asl_loc_cmp_str_vals(xsp1->ap, xsp2->ap, xslen1);
     rta = (cmp_val != 0);
    }
   break;
 }
 __pop_xstk();
 __pop_xstk();
 return(rta);
}

/*
 * local version of cmp_str_vals
 */
static int32 asl_loc_cmp_str_vals(word32 *op1ap, word32 *op2ap, int32 opwid)
{
 int32 i;

 for (i = wlen_(opwid) - 1; i >= 0; i--)
  {
   if (op1ap[i] != op2ap[i])
    { if (op1ap[i] < op2ap[i]) return(-1); else return(1); }
  }
 return(0);
}
