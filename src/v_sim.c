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
 * Verilog simulation routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#ifndef __NOSIGS__
#include <signal.h>
#endif

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

#include "igen.h"

/* local prototypes */
static void process_pnd0s(void);
static void exec_1file_slotend_dp(struct dp_fildesc_t *);
static int32 open_dumpports_file(struct dp_fildesc_t *);
static void process_all_netchgs(void);
static void eval_netchg_lds(struct net_t *, int32, int32, int32);
static void process_nbpa_ev_pnd0(void);
static void emit_nchglds_trmsg(struct net_t *, struct net_pin_t *);
static int32 is2_chg_match(int32, int32, int32);
static void std_chg_logic_gate(struct gate_t *, word32);
static void acc_chg_bufnot(struct gate_t *, word32);
static void acc_stichg_bufnot(struct gate_t *, word32);
static void acc_chg_4igate(struct gate_t *, word32);
static void acc_stichg_4igate(struct gate_t *, word32);
static void trace_gunchg(struct gate_t *, word32);
static void std_chg_udp_gate(struct gate_t *, word32);
static void std_chg_bufif_gate(struct gate_t *, word32);
static void std_chg_mos_gate(struct gate_t *, word32);
static void std_chg_cmos_gate(struct gate_t *, word32);
static void prop_gatechg(struct gate_t *, int32, int32);
static void evtr_prop_gatechg(struct gate_t *, word32, int32);
static void emit_gev_trace(struct gate_t *, struct tev_t *);
static void trace_chg_gateout(struct gate_t *, struct expr_t *);
static void gate_st_bit(word32 *, int32, int32, int32, word32, word32);
static int32 chg_mos_instate(struct gate_t *, word32);
static int32 chg_cmos_instate(struct gate_t *, word32);
static void eval_tranif_onoff(struct gate_t *);
static void evtr_eval_conta_rhs_ld(struct net_pin_t *);
static void do_compiled_sim(void);
static void process_nbpa_varndx_concat_ev_2state(struct tev_t *, 
 struct tenbpa_t *, struct net_t *);

extern void __process_nbpa_varndx_concat_ev(void);
extern void __process_compiled_thrd_ev(void);
extern void __init_cvc_sched_thd(struct mod_t *);
extern struct tev_t *__asl_loc_get_new_event(struct tev_t *);
extern void __asl_linkout_tevp_no_trigger(struct tev_t *);
extern void __asl_chg_vec_lhsbsel(struct net_t *, int32, word32, word32, 
 struct nchglst_t *);
extern void __asl_chg_vec_lhsbsel_2state(struct net_t *, int32, word32, 
 struct nchglst_t *);
extern void __asl_record_array_net_change(struct net_t *, struct nchglst_t *,
  int32);
static int32 force_inhibit_wireassign(struct net_t *, int32,
 t_midat *);
extern void __process_trpthdst_ev(void);
static int32 filter_edge_expr(struct dce_expr_t *, word32 *, word32 *);
static void trigger_evctrl(struct delctrl_t *, struct tev_t *);
static void bld_xmrsrc_ref(char *, struct net_t *);
static void bld_srcfilter_ref(char *, word32, word32, struct expr_t *);
static int32 filter_bitchange(word32, size_t, word32, struct expr_t *);
static void add_tchk_chged(struct chktchg_t *);
static void process_notify(struct net_t *);
static char *bld_tchk_srcdump(char *, struct tchk_t *, word64 *, word64 *,
 word64 *, word64 *);
static void init_stime(void);
static void reinit_stime(void);
static void init_wires(void);
static void init_itinsts(struct itree_t *);
static void init_sched_thd(struct mod_t *);
static void gate_initeval(struct gate_t *);
static void init_udp(struct gate_t *);
static void init_logic_gate(struct gate_t *);
static void init_bufif_gate(struct gate_t *);
static void init_tranif_gate(struct gate_t *);
static void conta_initeval(struct conta_t *, struct conta_t *);
static int32 move_to_time0(void);
static char *to_evtronam(char *, char *, t_midat *, struct task_t *);
static char *to_cur_evtronam(char *, char *, struct task_t *);
static char *to_cur_evtrcanam(char *, struct conta_t *);
static void do_sim(void);
static struct tev_t *schedule_1gev(struct gate_t *, word64, word64, int32);
static void reschedule_1gev(struct tev_t *, word64, word64, word32, int32);
#ifdef __XPROP__
static int32 has_x_only_edge(word32 *, word32 *, int32);
static int32 has_x_only_edge_stren(byte *, byte *, int32);
#endif
static void init_cvc_sched_thd(struct mod_t *);

#ifdef __STREE__
/* red black tree for timing balanced tree */
static struct tqnode_t *find_time(word64, struct tqnode_t **);
static void left_rotate(struct tqnode_t *);
static void left_rotate_max(struct tqnode_t *);
static void right_rotate(struct tqnode_t *);
static void right_rotate_min(struct tqnode_t *);
static void rb_insert_min(struct tqnode_t *);
static void rb_insert_middle(struct tqnode_t *);
static void rb_insert_max(struct tqnode_t *);
static struct tev_t *move_time(void);
static void rb_delete_min_fixup(struct tqnode_t *);
static struct tqnode_t *alloc_node(word64);
static void grow_free_nodes(void);
#else
/* routines for heap scheduler */
static struct tev_t *move_time(void);
static struct heap_t *add_new_heap_time(struct tev_t *, int32);
static void heapify(void);
static void grow_event_heap(void);
static void heap_reinsert_min(struct heap_t *);
#endif

/* extern prototypes defined elsewhere */
extern void __pv_sim(void);
extern void __process_gatechg_ev(void);
extern void __process_cancel_ev(void); 
extern void __process_mipd_nchg_ev(void);
extern void __process_nbpa_ev_sim_notpnd0(void);
extern void __process_conta_ev(void);
extern void __process_wire_ev(void);
extern void __get_cor_range(int32, union intptr_u, int32 *, int32 *);
extern void __set_gchg_func(struct gate_t *);
extern void __vpi_set_chg_proc(struct gate_t *);
extern void __process_all_tchk_violations(void);
extern void __set_all_toggles_off(void);
extern void __process_all_toggle_coverage(void);
extern void __exec_slotend_dv(void);
extern void __exec_slotend_dp(void);
extern int32 __gate_is_acc(struct gate_t *);
extern void __add_nchglst_el(struct net_t *);
extern void __add_dmpv_chglst_el(struct net_t *);
extern void __add_dmpv_chglst_el_sel(struct net_t *, int32);
extern void __add_dp_chglst_el(struct net_t *);
extern void __add_togglelst_el(struct net_t *);
extern void __eval_conta_rhs_ld(struct net_pin_t *);
extern void __eval_tranif_ld(struct gate_t *, int32);
extern void __add_select_nchglst_el(struct net_t *, int32, int32);
extern void __wakeup_delay_ctrls(struct net_t *, int32, int32);
extern void __process_npp_timofchg(struct net_t *, struct net_pin_t *);

extern char *__to_evtrcanam(char *, struct conta_t *, t_midat *);
extern void __evtr_resume_msg(void);
extern void __process_getpat(struct conta_t *);
extern char *__to_cur_evtrwnam(char *, struct net_t *, int32, int32);
extern void __init_sim(void);
extern void __reinit_sim(void);
extern void __insert_event(struct tev_t *);
extern void __free_telhdr_tevs(struct tev_t *);
extern void __free_1tev(struct tev_t *);
extern void __free_xtree(struct expr_t *);
extern void __call_misctfs_simstart(void);
extern void __vpi_startsim_trycall(void);
extern void __call_misctfs_endreset(void);
extern void __vpi_endreset_trycall(void);
extern void __do_interactive_loop(void);
extern void __process_thrd_ev(void);
extern void __asl_compiled_ev_to_front(struct tev_t *);
extern void __thrd_done_cleanup(struct thread_t *);
extern void __thrd_done_cleanup_auto(struct thread_t *);
extern void __o_tr_msg(char *, ...);
extern char *__to_timstr(char *, word64 *);
extern void __setdel_call_misctf(void);
extern void __process_putpdel_ev(void);
extern void __process_vpidrv_ev(void);
extern void __process_vpi_varputv_ev(void);
extern void __delay_callback(void);
extern void __sync_call_misctf(void);
extern void __exec_monit(struct dceauxlst_t *, int32);
extern void __exec_fmonits(void);
extern void __exec_strobes(void);
extern void __exec_rosync_misctf(void);
extern void __vpi_del_rosync_call(void);
extern void __vpi_del_nxtsimtim_trycall(void);
extern void __do_dmpvars_baseline(char *);
extern void __turnoff_all_dumpvars(void);
extern void __turnon_all_dumpvars(void);
extern void __do_dmpvars_chg(void);
extern int32 __tilde_creat(char *);
extern int32 __my_creat(char *);
extern void __setup_dmpvars(void);

extern void __setup_1file_dmpports(struct dp_fildesc_t *);
extern void __turnon_1file_all_dumpports(struct dp_fildesc_t *);
extern void __turnoff_1file_all_dumpports(struct dp_fildesc_t *);
extern void __do_dmpports_baseline(struct dp_fildesc_t *, char *);
extern void __turnon_all_dumpports(struct dp_fildesc_t *);
extern void __do_dmpports_chg(struct dp_fildesc_t *);

extern struct itree_t *__get_npprefloc(struct net_pin_t *);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__var_tostr(char *, struct net_t *, int32, int32, int32);
extern char *__to_npptyp(char *, struct net_pin_t *);
extern int32 __eval_logic_gate(struct gate_t *, word32, int32 *);
extern void __ld_bit(word32 *, word32 *, struct net_t *, int32);
extern int32 __correct_forced_newwireval(struct net_t *, word32 *, word32 *);
extern int32 __forced_inhibit_bitassign(struct net_t *, struct expr_t *,
 struct expr_t *);
extern void __chg_st_bit(struct net_t *, int32, word32, word32);
extern word32 __wrd_redxor(word32);
extern int32 __eval_udp(struct gate_t *, word32, int32 *, int32);
extern int32 __eval_bufif_gate(struct gate_t *, word32, int32 *);
extern void __eval_pmos_gate(word32);
extern void __eval_rpmos_gate(word32);
extern void __eval_nmos_gate(word32);
extern void __eval_rnmos_gate(word32);
extern void __eval_cmos_gate(struct gate_t *);
extern int32 __get_acc_class(struct gate_t *);
extern word64 __hizstrengate_getdel(struct gate_t *);
extern word64 __get_del(union del_u, word32);
extern int32 __em_suppr(int32);
extern char *__to_ginam(char *, struct gate_t *, word32, int32);
extern char *__to_gonam(char *, struct gate_t *, word32);
extern char *__msg_blditree(char *, struct itree_t *, struct task_t *);
extern char *__schop(char *, char *);
extern char *__msg2_blditree(char *, struct itree_t *);
extern char *__msg2_ndx_blditree(char *, int32);
extern char *__msg2_cur_blditree(char *);
extern char *__msg_idp_blditree(char *, t_midat *, struct task_t *);
extern char *__msg2_idp_blditree(char *, t_midat *);
extern void __mdr_assign_or_sched(struct expr_t *);
extern void __exec_conta_assign(struct expr_t *, word32 *, word32 *, int32);
extern char *__gstate_tostr(char *, struct gate_t *, int32);
extern void __immed_eval_trifchan(struct gate_t *);
extern char *__to_gassign_str(char *, struct expr_t *);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern void __lhsbsel(word32 *, int32, word32);
extern struct xstk_t *__ndst_eval_xpr(struct expr_t *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern void __sgn_xtnd_widen(struct xstk_t *, int32);
extern void __sizchg_widen(struct xstk_t *, int32);
extern void __narrow_sizchg(struct xstk_t *, int32);
extern void __fix_widened_toxs(struct xstk_t *, int32);
extern void __st_perinst_val(union pck_u, int32, word32 *, word32 *);
extern void __st_val(struct net_t *, word32 *, word32 *, int32);
extern void __st_idp_val(word32 *, int32, word32 *, word32 *);
extern void __st_idp_val(word32 *, int32, word32 *, word32 *);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern void __st_standval(byte *, struct xstk_t *, byte);
extern void __stren_exec_ca_concat(struct expr_t *, byte *, int32);
extern void __exec_ca_concat(struct expr_t *, word32 *, word32 *, int32);
extern int32 __wide_vval_is0(word32 *, int32);
extern int32 __vval_is1(word32 *, int32);
extern char *__regab_tostr(char *, word32 *, word32 *, int32, int32, int32);
extern char *__st_regab_tostr(char *, byte *, int32);
extern char *__bld_lineloc(char *, word32, int32);
extern void __my_free(void *, size_t);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern char *__to_vvnam(char *, word32);
extern char *__xregab_tostr(char *, word32 *, word32 *, int32, struct expr_t *);
extern void __exec2_proc_assign(struct expr_t *, word32 *, word32 *, int32);
extern int32 __unnormalize_ndx(struct net_t *, int32);
extern void __eval_tran_1bit(struct net_t *, int32);
extern struct itree_t *__match_targ_to_ref(word32, struct gref_t *);
extern void __assign_qcaf(struct dcevnt_t *);
extern void __pvc_call_misctf(struct dcevnt_t *);
extern void __cbvc_callback(struct dcevnt_t *, struct cbrec_t *, struct h_t *);
extern void __exec_vpi_gateoutcbs(struct tev_t *);
extern void __add_ev_to_front(struct tev_t *);
extern int32 __get_dcewid(struct dcevnt_t *, struct net_t *);
extern void __ld_wire_sect(struct xstk_t *, struct net_t *, int32, int32);
extern void __ld_wire_val_xstk(struct xstk_t *, struct net_t *);
extern char *__to_tcnam(char *, word32);
extern void __vpi_tchkerr_trycall(struct tchk_t *, struct itree_t *);
extern void __chg_st_val(struct net_t *, word32 *, word32 *);
extern void __adds(char *);
extern void __chg_xprline_size(int32);
extern char *__to_edgenam(char *, word32);
extern void __trunc_exprline(int32, int32);
extern char *__pv_stralloc(char *);
extern void __init_interactive(void);
extern void __my_fclose(FILE *);
extern void __init_all_trchans(void);
extern void __init_instdownport_contas(struct itree_t *, struct itree_t *);
extern void __init_instupport_contas(struct itree_t *);
extern struct thread_t *__alloc_thrd(void);
extern void __ld_perinst_val(word32 *, word32 *, union pck_u,
 int32);
extern void __ld_val(word32 *, word32 *, word32 *, int32);
extern int32 __sim_sigint_handler(void);
extern void __dmp_event_tab(void);
extern void __dmp1_nplstel(struct mod_t *, struct net_t *, struct net_pin_t *);
extern void __sched_mipd_nchg(struct net_t *, int32, struct mipd_t *);
extern void __exec_var_decl_init_assigns(void);
extern void __schedule_1caev(struct conta_t *, word64, word64, word32 *);
extern void __reschedule_1caev(struct tev_t *, word64, word64, word32 *);
extern word32 __get_showcancele_val(struct gate_t *);
extern void __emit_pulsewarn(struct gate_t *, struct tev_t *, word64 *,
 word64 *, char *);
extern void __acc_evchg_gate_outwire(struct gate_t *);
extern void __change_gate_outwire(struct gate_t *);
extern struct tev_t *__get_next_time_header(void);
extern void __restore_min_time_heap(int32);
extern char *__to_evtrwnam(char *, struct net_t *, int32, int32, t_midat *);
extern void __st_arr_val(struct net_t *, struct expr_t *, int32, word32 *, 
 word32 *, int32);
extern void __chg_st_arr_val(struct net_t *, struct expr_t *, int32, 
 word32 *, word32 *);
extern void __ld_wire_val_wrds(word32 *, word32 *, struct net_t *);

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
extern void __copy_auto_idp_area(t_midat *, t_midat *, int32);

static void fst_exec_slotend(void);

extern void __fst_do_vars_chg(void);
extern void __fst_do_vars_baseline(char *, int32);

extern void __cv_msg(char *, ...);
extern void __cvsim_msg(char *, ...);
extern void __tr_msg(char *, ...);
extern void __dbg_msg(char *, ...);
extern void __pv_err(int32, char *, ...);
extern void __pv_warn(int32, char *,...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __ia_warn(int32, char *, ...);

extern const word32 __masktab[];
extern const byte __stren_map_tab[];
extern const byte __hizstren_del_tab[];

/*
 * ROUTINES TO RUN SIMULATION
 */

/*
 * actually run the simulation
 * need better way to handle p0 (events that must go at end) queue
 *
 * LOOKATME - set up so never check entering interact unless one event
 * processed (except -s entry before start of sim)
 */
extern void __pv_sim(void)
{
 /* unless quiet mode, need blank line before sim writing */
 __cv_msg("\n");
 /* possible that no events scheduled at 0, must really move time to 0 */
 /* this assumes wrap works ? */
 __simtime = 0xffffffffffffffffULL;

 /* move time to 0 */
 move_to_time0();

 /* now have timing wheel - can run vpi sim controls that are like */
 /* system task execs */
 __can_exec = TRUE;

 /* do not call vpiStartOfSim routine if resetting */
 if (__now_resetting)
  {
   __now_resetting = FALSE;
   if (__tfrec_hdr != NULL) __call_misctfs_endreset();
   if (__have_vpi_actions) __vpi_endreset_trycall();

   /* if no events after reset - nothing to do so terminate */
   if (__num_init_events == 0 && __p0_te_hdrp == NULL)
    {
     __pv_warn(614,
     "no pending statements or events after reset to time 0 - nothing to do");
     return;
    }
  }
 else
  {
   /* no sim (variables) d.s. and time before here */
   /* notice these routines cannot cause inside entry of debugger */
   /* so can call from here - just scan and register */
   if (__tfrec_hdr != NULL) __call_misctfs_simstart();
   if (__have_vpi_actions) __vpi_startsim_trycall();

   /* if no events after initializationand PLI start of sim - nothing to do */
   if (__num_init_events == 0 && __p0_te_hdrp == NULL)
    {
     __pv_warn(614,
      "no pending statements or events after initialization - nothing to do");
     return;
    }
  }

 /* enter immediately if -s option, . here just starts sim */
 __cur_tevp = NULL;

 /* if this is at least 100 entering from debugger reset */
 if (__dbg_stop_before >= 100)
  {
   if (__dbg_stop_before != 101) { __dbg_stop_before = 0; goto no_stop; }
   __dbg_stop_before = 0;
   goto stop;
  }

 /* else use -s option to decide if stop before sim */
 if (__stop_before_sim)
  {
   /* if no interactive ignore stop before sim with warning */
   if (__no_iact)
    {
     __pv_warn(628,
      "-s option ignored - +nointeractive disabled interactive mode");
     goto no_stop;
    }
stop:
   /* interactive loop expects int32 (^c) signal to be ignored */
   __do_interactive_loop();
  }

no_stop:
 /* set up during simulation control c signal handler - can set flag only */
#ifndef __NOSIGS__
#if defined(INTSIGS)
 signal(SIGINT, __sim_sigint_handler);
#else
 signal(SIGINT, (void (*)()) __sim_sigint_handler);
#endif
#endif

 /* AIV 12/21/07 - if compiling just compile and return for exit */
 if (__compiled_sim && !__running_cvc_exe) return;

 /* SJM 09/30/04 - execute all new Verilog 2001 variable decl assigns */
 /* as the first step in simulation - do not need any events */
 /* SJM 09/30/04 - LOOKATME - could build and schedule separate init block */
 __exec_var_decl_init_assigns();

 /* repeat this loop for every time */
 __processing_pnd0s = FALSE;
//AIV IDP FIXME - no longer use global __inum at runtime setting to -1 for dbg
 __inum = -1;
 /* do the actual simulation */
 /* AIV 04/10/07 - seperated out compiled sim to minimize if/else inside */
 /* of the simulation move time loop */
 if (__compiled_sim) do_compiled_sim();
 else do_sim();
}

/*
 * run the actual simulation until all events are done
 */
static void do_sim(void)
{
 struct tev_t *tevp;

 tevp = __cur_te_hdrp;
 for (;;)
  {
   /* execute events until current time event list empty */
   /* events never added here (maybe to pound 0) */
   for (; tevp != NULL; tevp = tevp->tenxtp)
    {
     __cur_tevp = tevp;
     /* every event has associated itree element */
     __idp = tevp->te_idp;

     /* -- DBG remove --
     if (tevp->enterptr == NULL) __misc_terr(__FILE__, __LINE__);
      ---- */

     (tevp->enterptr)();
  
     /* notice before event executed, cur. itp set from event */
     __num_proc_tevents++;
     /* DBG remove - notice between events itree stack must be empty ---
     if (__itspi != -1) __misc_terr(__FILE__, __LINE__);
     --- */

     /* notice adding to front adds after current which is really done */
     /* see if pending control c, if add to front, next is right header */
     if (__pending_enter_iact) __do_interactive_loop();
    }

   /* done with normal events, free and remove from time wheel */
   process_pnd0s();

   /* AIV 07/05/05 - added processing of separate after all pnd0's non */
   /* blocking events processing nb events can add new pnd0's that are */
   /* processed as added and new nb's that are saved and added to do */
   /* after all current level nbs and pnd0s done */
   if (__nb_te_hdrp != NULL)
    {
     for (;;)
      { 
       __p0_te_hdrp = __nb_te_hdrp; 
       __p0_te_endp = __nb_te_endp;
       __nb_te_hdrp = __nb_te_endp = NULL;

       /* notice the move to pnd 0 queue events add to free list in */
       /* process pnd0 routine */
       process_pnd0s();
       if (__nb_te_hdrp == NULL) break;
     }
    }
   /* --- DBG remove
   if (__debug_flg && __ev_tracing
    && (__nchg_futhdr != NULL || __p0_te_hdrp != NULL))
     __tr_msg("-- processing #0 end of slot events\n");
   --- */

   /* final step do slot end timing checks and monitoring */
   /* cannot schedule any events from here */
   if (__slotend_action != 0)
    {
     if ((__slotend_action & SE_TCHK_VIOLATION) != 0)
      __process_all_tchk_violations();
     if ((__slotend_action & SE_DUMPVARS) != 0) __exec_slotend_dv();
     /* SJM 09-26-08 se dumports means some file has dumpports - chks all */
     if ((__slotend_action & SE_DUMPPORTS) != 0) __exec_slotend_dp();
     if (__monit_active && ((__slotend_action
      & (SE_MONIT_TRIGGER | SE_MONIT_CHG)) != 0))
      __exec_monit(__monit_dcehdr,
       (int32) (__slotend_action & SE_MONIT_CHG) != 0);

     /* LOOKATME - should monitoroff (on) effect fmonitor (think no) */
     if ((__slotend_action & SE_FMONIT_TRIGGER) != 0) __exec_fmonits();
     if ((__slotend_action & SE_STROBE) != 0) __exec_strobes();
     if ((__slotend_action & SE_TFROSYNC) != 0) __exec_rosync_misctf();
     if ((__slotend_action & SE_VPIROSYNC) != 0) __vpi_del_rosync_call();
     if ((__slotend_action & SE_TOGGLE) != 0) __process_all_toggle_coverage();
     /* SJM 06-30-13 - key is that the various slot (tick) end actions */
     /* are turned off here after processing - if not actions next tick */ 
     /* will stay off */
     __slotend_action = 0;
    }
   /* contrl c here serviced at beginning of next time slot */
   /* if no more events done if timing tree root is empty */
   /* move time - this updates the timing tree and sets __sim_time */
   __cur_te_endp->tenxtp = __tefreelstp;
   __tefreelstp = __cur_te_hdrp;
   __cur_te_hdrp = __cur_te_endp = NULL;

   tevp = move_time();
   if (tevp == NULL) return;
   /* call backs from vpi cb NextSimTime (after debugger entered) */
   if (__have_vpi_actions) __vpi_del_nxtsimtim_trycall();
   /* SJM 06-19-07 - for debugger could remove */
   __idp = NULL;
  }
}

/*
 * run the actual simulation until all events are done
 */
static void do_compiled_sim(void)
{
#ifdef __CVC32__
 void (*enterp)(void);
#endif
 /* initialize free area list */
 __cur_te_endp->tenxtp = __free_event_tevp;
 __cur_tevp = __cur_te_hdrp;
 /* AIV 01/05/08 - first event must enter the wrapper which now sets */
 /* the idp reg (esi) and then enters the first event */
 /* couldn't use the __asm__ here because of the restore (popl) of %esi */
 /* when compiling with -O2 */
#ifdef __CVC32__
 /* AIV 10/21/09 - make extra space for asl wrappers args no need create */
 /* extra space in the lowered code */
 __asm__ ("subl   $32, %%esp" ::: "%esp");
 enterp = __first_enterp;
 (enterp)(); 
#else
 /* AIV 11/21/08 - just jump to enter for 64-bit need to keep align */
 /* on 16-byte call enter is -8 from rsp */
 __asm__ ("movq   __first_enterp, %%rax" ::: "%rax");
 __asm__ ("jmp    *%%rax" ::: "%rax");
#endif
}

/*
 * process a compiled assembly code thread event
 *
 * must handle updating active (uncompleted) thread tree
 *
 * for now also handling task call ouput (and inout) assigning here
 *
 * key assumption is that old processing for loop only needed for
 * statement tracing - now with asm no stmt tracing or debugging so
 * only cases are stmt suspend true (hit event/delay ctrl) or
 * thread done so do not need for loop
 *
 * SJM 01/05/05 - LOOKATME - maybe should add another event type
 * or even compile the procedural event processing code
 * SJM 01/06/05 - LOOKATME - for now need the stmt interpreter code
 * but should be rewritten to find continuation from .s label
 *
 * AIV 04/11/07 - moved here to make static for gcc to inline
 */
extern void __process_compiled_thrd_ev(void)
{
 struct st_t *stp;
 struct thread_t *parthp;
 decl_idp_locals_;

 /* AIV 05/14/07 - never can enter interactive debugger for compiled code */
 /* no need to set these */
 /*
 __suspended_thd = NULL;
 __suspended_idp = NULL;
 */
 /* set current thread and remove connection of thread to event */
 __proc_thrd_tevents++;
 __cur_thd = __cur_tevp->tu.tethrd;
 __cur_thd->thdtevp = NULL;

 stp = __cur_thd->thnxtstp;
 /* keep executing behavioral stmts until done or hit timing control */
 __stmt_suspend = FALSE;
 save_idp_();
 for (;;)
  {
   if (stp != NULL)
    {
     /* notice if thread completes - stmt suspend must not be T */
     /* AIV 01/04/07 - cannot use %esi here last arg is clob regs */
#ifdef __CVC32__
     __asm__ ("movl __idp, %%esi" ::: "%esi");
     (stp->enterptr)();
#else
     __asm__ ("movq __idp, %%r15" ::: "%r15");
     /* AIV 11/21/08 - need to keep align on 16-byte */
     /* call is -8 bytes our lowered code is expecting align on 16-bytes */
     __asm__ ("subq $8, %%rsp" ::: "%rsp");
     (stp->enterptr)();
     __asm__ ("addq $8, %%rsp" ::: "%rsp");
#endif
     if (__stmt_suspend) break;
    }

   /* this thread tree done if nil - can only be interactive or init/always */
   /* this handles all freeing because entire thread tree done */
   if ((parthp = __cur_thd->thpar) == NULL)
    {
     __stmt_suspend = TRUE;
     break;
    }

   /* AIV 05/17/10 - thrd done may need to get inum from __idp */
   /* when codes enters asm code it may not return a set __idp */
   /* since it only uses idp reg - need to reset here for possible */
   /* task inum access - usually worked by bad mem write */
   __idp = __cur_thd->th_idp;
   /* this thread finished - remove it from control thread d.s. */
   __thrd_done_cleanup(parthp);

   /* more fork-join subthreads to complete */
   if (parthp->thofscnt > 0) { __stmt_suspend = TRUE; break; }

   /* all subthreads finished, continue with parent */
   /* for enabled task (not named block), know out arg. store phase done */
   parthp->thofs = NULL;
   /* continue with parent by executing next statement */
   /* no suspend here */
   __cur_thd = parthp;
   set_idp_(__cur_thd->th_idp); 
   stp = __cur_thd->thnxtstp;
  }
 /* AIV 10/24/07 - was never setting trigger off for thread excuted code */
 __cur_tevp->trigger = FALSE;
 restore_idp_();
 __cur_thd = NULL;
 return;
}

/*
 * same as above but this wrapper is for designs which contain autoc task/funcs
 * must do some extra checking
 */
extern void __process_compiled_thrd_ev_auto(void)
{
 struct st_t *stp;
 struct thread_t *parthp;
 decl_idp_locals_;

 /* AIV 05/14/07 - never can enter interactive debugger for compiled code */
 /* no need to set these */
 /*
 __suspended_thd = NULL;
 __suspended_idp = NULL;
 */
 /* set current thread and remove connection of thread to event */
 __proc_thrd_tevents++;
 __cur_thd = __cur_tevp->tu.tethrd;
 __cur_thd->thdtevp = NULL;
 /* AIV 04/12/10 - need to set __idp now since this value may change */
 /* with an automatic function it is alloced in the thread */
 /* normally was just set using the tev_t idp area - but now can change */
 __idp = __cur_thd->th_idp;

 /* AIV 04/16/10 - if is auto idp area must copy back into current idp */
 /* this idp area could also be an auto area so if changed global values */
 /* across two tasks calls need to copy known good idp area back into */
 /* this local global space */
 if (__cur_thd->th_save_idp != NULL)
  {
   __copy_auto_idp_area(__idp, __cur_thd->th_save_idp, FALSE);
  }

 stp = __cur_thd->thnxtstp;
 /* keep executing behavioral stmts until done or hit timing control */
 __stmt_suspend = FALSE;
 save_idp_();
 for (;;)
  {
   if (stp != NULL)
    {
     /* notice if thread completes - stmt suspend must not be T */
     /* AIV 01/04/07 - cannot use %esi here last arg is clob regs */
  #ifdef __CVC32__
     __asm__ ("movl __idp, %%esi" ::: "%esi");
     (stp->enterptr)();
  #else
     __asm__ ("movq __idp, %%r15" ::: "%r15");
     /* AIV 11/21/08 - need to keep align on 16-byte */
     /* call is -8 bytes our lowered code is expecting align on 16-bytes */
     __asm__ ("subq $8, %%rsp" ::: "%rsp");
     (stp->enterptr)();
     __asm__ ("addq $8, %%rsp" ::: "%rsp");
  #endif
     if (__stmt_suspend) break;
    }

   /* this thread tree done if nil - can only be interactive or init/always */
   /* this handles all freeing because entire thread tree done */
   if ((parthp = __cur_thd->thpar) == NULL)
    {
     __stmt_suspend = TRUE;
     break;
    }

   /* AIV 05/17/10 - thrd done may need to get inum from __idp */
   /* when codes enters asm code it may not return a set __idp */
   /* since it only uses idp reg - need to reset here for possible */
   /* task inum access - usually worked by bad mem write */
   __idp = __cur_thd->th_idp;
   /* this thread finished - remove it from control thread d.s. */
   __thrd_done_cleanup_auto(parthp);

   /* more fork-join subthreads to complete */
   if (parthp->thofscnt > 0) { __stmt_suspend = TRUE; break; }

   /* all subthreads finished, continue with parent */
   /* for enabled task (not named block), know out arg. store phase done */
   parthp->thofs = NULL;
   /* continue with parent by executing next statement */
   /* no suspend here */
   __cur_thd = parthp;
   set_idp_(__cur_thd->th_idp); 
   stp = __cur_thd->thnxtstp;
  }
  
 /* AIV 04/12/10 - if have automatic idp area need to copy back */
 if (__cur_thd != NULL &&  __cur_thd->th_save_idp != NULL)
  {
   __copy_auto_idp_area(__cur_thd->th_save_idp, __idp, FALSE);
  }

 /* AIV 10/24/07 - was never setting trigger off for thread excuted code */
 __cur_tevp->trigger = FALSE;
 restore_idp_();
 __cur_thd = NULL;
 return;
}

//AIV TEV FIXME
extern void __process_nbpa_ev(void)
{
 /* AIV 01/07/09 - just check pnd0 pointer != NULL not __processing_pnd0s */
 if (__p0_te_endp != NULL) process_nbpa_ev_pnd0();
 else __process_nbpa_ev_sim_notpnd0();
}

/*
 * process a non-blocking (TE_NBPA) pound0 event
 */
extern void __process_nbpa_ev_sim_notpnd0(void)
{
 struct tev_t *tevp;
 struct tev_t *tevp2;

 tevp = __cur_tevp;
 /* 10/27/00 SJM - this is rhs delay that has elapsed - never rep form */
 /* non blocking proc assign, jump to #0 queue to process */
 alloc_tev_(tevp2, tevp->enterptr, tevp->te_idp, __simtime);
 /* this moves entire nb records - since not needed here */
 tevp2->enterptr = tevp->enterptr;
 /* if present ptr to constant index lhs expr. copy also copied */
 tevp2->tu.tenbpa = tevp->tu.tenbpa;
 /* AIV 08/22/07 - now used for both compiler and interp must copy scalar */
 tevp2->scalar_nb_val = tevp->scalar_nb_val;
 tevp->tu.tenbpa = NULL;
 __num_proc_tevents--;
 /* AIV 07/05/05 - to match XL need nb te list that only processed */
 /* when all pnd 0 done effectively adds another section to current */
 /* time event queue */
 if (__nb_te_hdrp == NULL) __nb_te_hdrp = __nb_te_endp = tevp2;
 else { __nb_te_endp->tenxtp = tevp2; __nb_te_endp = tevp2; }
}

/*
 * process a non-blocking (TE_NBPA) pound0 event
 */
extern void __process_compiled_nbpa_ev_sim_notpnd0(void)
{
 struct tev_t *tevp, *new_tevp;

 tevp = __cur_tevp;
 /* AIV rare case this is getting freed must realloc a new one to add list */
 /* it is going to be free prior to it execution on the nb list */
//AIV FIXME - this can go when free is set - for now free is in next_event
//free should match when the trigger flag is set
 if (tevp->next_enterptr == __process_next_event_free_enterp)
  {
   new_tevp = __asl_loc_get_new_event(tevp);
   new_tevp->scalar_nb_val = tevp->scalar_nb_val;
   new_tevp->tu.bi = tevp->tu.bi;
   tevp = new_tevp;
  }
 tevp->etime = __simtime;
 /* AIV 07/05/05 - to match XL need nb te list that only processed */
 /* when all pnd 0 done effectively adds another section to current */
 /* time event queue */
#ifdef __CVC_DEBUG__
 if (__nb_te_endp == NULL) __misc_terr(__FILE__, __LINE__);
#endif
 __nb_te_endp->tenxtp = tevp; 
 __nb_te_endp = tevp; 
}

/*
 *  process all net changes - this can only enter pnd0 events at now
 * next process net changes, if any new pnd0's process
 * may then add new net changes that in turn can add pnd0's
 * if no 0 delay loop (must catch) will eventually terminate
 * can add normal delays but will occur in future
 */
static void process_pnd0s(void)
{
 struct tev_t *tevp;

 for (__processing_pnd0s = TRUE, __cur_tevp = NULL;;)
  {
   if (__nchg_futhdr != NULL) process_all_netchgs();

   /* needed in case PLI tf_dostop or vpi_control(vpiStop called */
   if (__pending_enter_iact) __do_interactive_loop();

   /* no pending net changes and no more pound 0 events, can move time */
   tevp = __p0_te_hdrp;
   if (tevp == NULL) break;

   /* every event has associated itree element */
   for (; tevp != NULL; tevp = tevp->tenxtp)
    {
     /* canceled because interactive thread disabled */
     /* but pound 0 events not counted as timing wheel events */
     __cur_tevp = tevp;

     /* notice, pnd0 never canceled since can just replace guts */
     __idp = tevp->te_idp;

     /* -- DBG remove -- 
     if (tevp->enterptr == NULL) __misc_terr(__FILE__, __LINE__);
     ---- */

     (tevp->enterptr)();

     __num_proc_tevents++;
     /* when put into pnd0 list, no inc. of number of twheel events */
     __idp = NULL;
     /* here cur_tevp done so any add to front after it */
     if (__pending_enter_iact) __do_interactive_loop();
    }

   /* all #0 events for this time slot processed but may be new net chgs */
   if (__p0_te_hdrp != NULL)
    {
     __p0_te_endp->tenxtp = __tefreelstp;
     __tefreelstp = __p0_te_hdrp;
     __p0_te_hdrp = __p0_te_endp = NULL;
    }
   __cur_tevp = NULL;
  }
 __processing_pnd0s = FALSE;
}

/*
 * routine to exec dump vars functions
 *
 * notice only normal dumpvars will change to over file size limit state
 * from then on until flush or limit change will not do any dumping
 * or for that matter recording.
 */
extern void __exec_slotend_dv(void)
{
 if (__is_fst)
  {
   fst_exec_slotend();
   return;
  }
 /* must only emit time once in all processing */
 __dv_time_emitted = FALSE;
 /* first execute any dumpall */
 if ((__slotend_action & SE_DUMPALL) != 0)
  {
   /* if over limit silently do nothing */
   /* dump all is indpendent of normal dumpvars processing */
   if (__dv_state != DVST_OVERLIMIT)
    __do_dmpvars_baseline("$dumpall");
  }

 switch ((byte) __dv_state) {
  case DVST_DUMPING:
   /* if encountered dumpoff, handle here */
   if ((__slotend_action & SE_DUMPOFF) != 0)
    {
     /* remove any pending changes */
     __dv_chgnethdr = NULL;
     __do_dmpvars_baseline("$dumpoff");
     __dv_state = DVST_NOTDUMPING;
     __turnoff_all_dumpvars();
     break;
    }
   /* if no changes this time slot, nothing to do */
   /* on file over dump limit, will return */
   if (__dv_chgnethdr != NULL) __do_dmpvars_chg();
   break;
  case DVST_NOTDUMPING:
   /* if not dumpon and no dump on action do nothing here */
   if ((__slotend_action & SE_DUMPON) != 0)
    {
     /* start with baseline dump */
     __do_dmpvars_baseline("$dumpon");
     __dv_state = DVST_DUMPING;
     /* turn on dump change recording and dumping for next time slot */
     __turnon_all_dumpvars();
    }
   break;
  /* if not set up only way for pending to be on if need to setup */
  case DVST_NOTSETUP:
   /* try to open the file */
   if ((__dv_fd = __tilde_creat(__dv_fnam)) == -1)
    {
     if (strcmp(__dv_fnam, DFLTDVFNAM) == 0)
      {
bad_dvfnam:
       __pv_err(759,
	"cannot open $dumpvars output file at %s - $dumpvars not executed",
	 __to_timstr(__xs, &__simtime));
       /* not setup but dv seen stops any future setup */
       __dv_seen = TRUE;
       __dv_state = DVST_NOTSETUP;
       return;
      }
     else
      {
       __pv_warn(589, "cannot open $dumpvars output file %s trying %s",
	__dv_fnam, DFLTDVFNAM);
       strcpy(__dv_fnam, DFLTDVFNAM);
       if ((__dv_fd = __my_creat(__dv_fnam)) == -1) goto bad_dvfnam;
      }
    }
   /* write the file reference header and setup dv "events" on wires */
   __setup_dmpvars();
   __do_dmpvars_baseline("$dumpvars");
   if (__verbose)
    {
     __cv_msg(
      "  $dumpvars setup complete at %s - variables dumped to file %s.\n",
      __to_timstr(__xs, &__simtime), __dv_fnam);
    }
   if (__dv_state != DVST_OVERLIMIT)
    {
     __dv_state = DVST_DUMPING;
     /* enable dmpv change recording */
    }
   /* more setup now disabled */
   __dv_seen = TRUE;
   break;
  case DVST_OVERLIMIT:
   if (__dv_chgnethdr != NULL) __misc_terr(__FILE__, __LINE__);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * routine to exec dump ports at slot end including inital end of slot set up
 */
extern void __exec_slotend_dp(void)
{
 int32 dpdi;
 struct dp_fildesc_t *fdescp;

 for (dpdi = 0; dpdi < __dp_fildesc_nxti; dpdi++)
  {
   fdescp = &(__dp_fildesc_tab[dpdi]);
   exec_1file_slotend_dp(fdescp);
  }
}

/*
 * exec one file slot end dump ports  
 *
 * SJM 09-29-08 it is possible for many instances to be written to the
 * same dumpports file so dumping commands and sequencing control must be
 * from the dp file descriptor table, but change processing needs each
 * inst (itree loc) so processing must be from the dp inst el struct
 * (since each points to the other now have two d.s entry points)
 */
static void exec_1file_slotend_dp(struct dp_fildesc_t *fdescp)
{
 /* must only emit time once in all processing */
 fdescp->dp_time_emitted = FALSE;

 /* first execute any dumpall */
 if ((fdescp->dp_slotend_action & SE_DUMPPORTSALL) != 0)
  {
   /* if over limit silently do nothing */
   /* dump all is indpendent of normal dumpvars processing */
   if (fdescp->dp_state != DPST_OVERLIMIT)
    {
     __do_dmpports_baseline(fdescp, "$dumpportsall");
    }
  }

 switch ((byte) fdescp->dp_state) {
  case DVST_DUMPING:
   /* if encountered dumpoff, handle here */
   if ((fdescp->dp_slotend_action & SE_DUMPPORTSOFF) != 0)
    {
     /* remove any pending changes */
     __dv_chgnethdr = NULL;
     __do_dmpports_baseline(fdescp, "$dumpportsoff");
     fdescp->dp_state = DVST_NOTDUMPING;
     __turnoff_1file_all_dumpports(fdescp);
     break;
    }
   /* if no changes this time slot, nothing to do */
   /* on file over dump limit, will return */
   if (fdescp->dp_chgnethdr != NULL) __do_dmpports_chg(fdescp);
   break;
  case DVST_NOTDUMPING:
   /* if not dumpon and no dump on action do nothing here */
   if ((fdescp->dp_slotend_action & SE_DUMPPORTSON) != 0)
    {
     /* start with baseline dump */
     __do_dmpports_baseline(fdescp, "$dumpportson");
     fdescp->dp_state = DVST_DUMPING;
     /* turn on dump change recording and dumping for next time slot */
     __turnon_1file_all_dumpports(fdescp);
    }
   break;
  /* if not set up only way for pending to be on if need to setup */
  case DVST_NOTSETUP:
   /* SJM 09-25-08 - ??? if any files can't be open - no dump ports at all */ 
   if (!open_dumpports_file(fdescp)) return;

   /* write the file reference header and setup dv "events" on wires */
   __setup_1file_dmpports(fdescp);
   __do_dmpports_baseline(fdescp, "$dumpports");
   if (__verbose)
    {
     __cv_msg(
      "  $dumpports setup complete at %s - ports values dumped to file %s.\n",
      __to_timstr(__xs, &__simtime), fdescp->dp_fnam);
    }
   if (fdescp->dp_state != DVST_OVERLIMIT)
    {
     fdescp->dp_state = DVST_DUMPING;
     /* enable dmpv change recording */
    }
   /* more setup now disabled */
   __dp_seen = TRUE;
   break;
  case DVST_OVERLIMIT:
   if (fdescp->dp_chgnethdr != NULL) __misc_terr(__FILE__, __LINE__);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * open the dump ports file associated with file descriptor fdescp
 */
static int32 open_dumpports_file(struct dp_fildesc_t *fdescp)
{
 /* try to open the file */
 if ((fdescp->dp_fd = __tilde_creat(fdescp->dp_fnam)) == -1)
  {
   __pv_err(759,
    "cannot open $dumpports output file %s at %s - $dumpports not executed",
    fdescp->dp_fnam, __to_timstr(__xs, &__simtime));
   /* not setup but dv seen stops any future setup */
   fdescp->dp_state = DVST_NOTSETUP;
   return(FALSE);
  }
 return(TRUE);
}

/*
 * fst version
 * routine to exec fst vars functions
 */
static void fst_exec_slotend(void)
{
 /* must only emit time once in all processing */
 __dv_time_emitted = FALSE;
 /* first execute any dumpall */
 if ((__slotend_action & SE_DUMPALL) != 0)
  {
   /* if over limit silently do nothing */
   /* dump all is indpendent of normal dumpvars processing */
   if (__dv_state != DVST_OVERLIMIT)
    {
     __fst_do_vars_baseline("$fst_dumpall", FALSE);
    }
  }

 switch ((byte) __dv_state) {
  case DVST_DUMPING:
   /* if encountered dumpoff, handle here */
   if ((__slotend_action & SE_DUMPOFF) != 0)
    {
     /* remove any pending changes */
     __dv_chgnethdr = NULL;
     __fst_do_vars_baseline("$fst_dumpoff", TRUE);
     __dv_state = DVST_NOTDUMPING;
     __turnoff_all_dumpvars();
     break;
    }
   /* if no changes this time slot, nothing to do */
   /* on file over dump limit, will return */
   if (__dv_chgnethdr != NULL) __fst_do_vars_chg();
   break;
  case DVST_NOTDUMPING:
   /* if not dumpon and no dump on action do nothing here */
   if ((__slotend_action & SE_DUMPON) != 0)
    {
     /* start with baseline dump */
     __fst_do_vars_baseline("$fst_dumpon", FALSE);
     __dv_state = DVST_DUMPING;
     /* turn on dump change recording and dumping for next time slot */
     __turnon_all_dumpvars();
    }
   break;
  /* if not set up only way for pending to be on if need to setup */
  case DVST_NOTSETUP:
   /* try to open the file */
   /* write the file reference header and setup dv "events" on wires */
   __setup_dmpvars();
   __fst_do_vars_baseline("$fst_dumpvars", FALSE);
   if (__verbose)
    {
     __cv_msg(
      "  $fst_dumpvars setup complete at %s - variables dumped to file %s.\n",
      __to_timstr(__xs, &__simtime), __dv_fnam);
    }
   if (__dv_state != DVST_OVERLIMIT)
    {
     __dv_state = DVST_DUMPING;
     /* enable dmpv change recording */
    }
   /* more setup now disabled */
   __dv_seen = TRUE;
   break;
  case DVST_OVERLIMIT:
   if (__dv_chgnethdr != NULL) __misc_terr(__FILE__, __LINE__);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * AFTER CHANGE PROPOGATION FROM RHS ROUTINES
 */

/*
 * go through processing all nets (maybe a select) that changed
 * a pass may create more net changes that are in turn processed
 * until list empty
 * this is heuristic to try to cause breath first processing
 * when done future net change list empty
 *
 * if net (probably reg) has no load and no dcelst els not added to chg list
 *
 * SJM - 06/19/00 - now only save up and process structural net changes
 * event controls must be checked (and for force/release) done immediately
 */
static void process_all_netchgs(void)
{
 struct net_t *np;
 struct nchglst_t *nchglp, *last_nchglp;
 struct nchglst_t *sav_nchglp;
 int32 num_this_pass, num_passes, total_num;

 num_passes = 0;
 total_num = 0;
 for (;;)
  {
   if (__nchg_futhdr == NULL) break;

   /* point nchglp to all pending net chg elements for processing */
   nchglp = __nchg_futhdr;
   /* save head so can free at end of pass */
   sav_nchglp = nchglp;
   /* empty future so all net change elements added here will be put on */
   /* end of list and processed when all these done - breadth first */
   __nchg_futend = __nchg_futhdr = NULL;
   last_nchglp = NULL;
   for (num_this_pass = 0; nchglp != NULL; nchglp = nchglp->nchglnxt)
    {
     np = nchglp->chgnp;
     /* must eval. in definition itree loc. */
     __idp = nchglp->nchg_idp;
     /* SJM 04/19/01 - must turn off all changed to allow load propagation */
     /* switch channel changes to be added to next pass change list */
     /* turn off all changed - if get here know has n lds */
     __idp[np->nchgaction_ofs] &= (~NCHG_ALL_CHGED);

     /* DEBUG remove ---
     {
      struct net_pin_t *npp;

      __dbg_msg("*** dumping loads for net %s (itp=%s)***\n",
       np->nsym->synam, __msg2_cur_blditree(__xs));
      for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
       {
        mdp = get_inst_mod_();
        __dmp1_nplstel(mdp, np, npp);
       }
      __dbg_msg("*** end of loads ***\n");
     }
    --- */

     /* SJM 07/24/00 - propagate changes to dces for wires at end of queue */
     /* new algorithm - for regs immediate propagate, for wires end of queue */
     /* LOOKATME - think event controls should be before lds */
     if (np->ntyp < NONWIRE_ST && np->dcelst != NULL)
      __wakeup_delay_ctrls(np, nchglp->bi1, nchglp->bi2);

     /* SJM 07/24/00 - for wires with no lds but only dces still need */
     /* to record nothing to do here */
     if (np->nlds != NULL)
      eval_netchg_lds(np, nchglp->bi1, nchglp->bi2, nchglp->delayed_mipd);

     last_nchglp = nchglp;
     num_this_pass++;
     __idp = NULL;
    }
   total_num += num_this_pass;
   if (++num_passes > 1000 && (num_passes % 1000) == 0)
    {
     if (__pending_enter_iact)
      {
       __ia_warn(1604,
         "interactive mode probably entered from zero delay oscillation - no scheduling");
       __do_interactive_loop();
      }
    }

   /* know last nchg lp set since routine not called if at least one */
   /* SJM 08/02/01 - add if to keep lint happy */
   if (last_nchglp != NULL) last_nchglp->nchglnxt = __nchgfreelst;
   __nchgfreelst = sav_nchglp;
   /* LINUX DBG - add me */
   /* chk_nchgnlst(__nchgfreelst); */
   /* --- */
  }
 if (__debug_flg && __ev_tracing)
  {
   __tr_msg(
    "-- net change event scheduling %d processed in %d passes\n",
    total_num, num_passes);
  }
 __num_netchges += total_num;
}

/*
 * check nchg free list
 */
/* UNUSED LINUX DEBUG ---
void chk_nchgnlst(struct nchglst_t *hdr)
{
 struct nchglst_t *nchglp;
 int32 ndx;

 ndx = 0;
 for (nchglp = hdr; nchglp != NULL; nchglp = nchglp->nchglnxt)
  {
   if ((void *) nchglp > (void *) 0x13257400)
    {
     __tr_msg("problem at index %d\n", ndx);
     __misc_terr(__FILE__, __LINE__);
    }
   if (nchglp->nchglnxt > (void *) 0x13257400)
    {
     __tr_msg("problem at index %d\n", ndx);
     __misc_terr(__FILE__, __LINE__);
    }
   ndx++;
  }
}
--- */

/*
 * after changed net (wire or reg) go through loads evaluating the
 * load net's drivers assigning to the load net a new value
 *
 * bit range passed and used to eliminate fan-out for other bit here
 * all ranges here normalized high to low form
 * notice will neve get to event trigger through this path (through cause)
 * this is called with current itstk set to wire targ. (maybe target of xmr)
 *
 * the driver evaluations caused by this cause any changed wires to be
 * added to a list which is then used to provide the next pass of wire
 * loads
 */
static void eval_netchg_lds(struct net_t *np, int32 chgi1, int32 chgi2,
 int32 is_delayed_mipd)
{
 int32 bi;
 struct net_pin_t *npp;
 struct npaux_t *npauxp;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 struct itree_t *itp, *cur_itp;
 struct inst_t *ip;
 struct gate_t *gp;
 struct mipd_t *mipdp;
 decl_idp_locals_;

 if (__ev_tracing)
  {
   __evtr_resume_msg();
   __tr_msg("-- evaluating loads of reg/wire %s\n",
    __to_cur_evtrwnam(__xs, np, chgi1, chgi2));
  }

 /* must process all loads on net */
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* immediately filter out - npp's that require particular inst. */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != __idp)
    continue;

   /* first need non empty union with 2 ranges */
   /* case 1: all bits of changed or driven bits unknown */
   if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1 || chgi1 == -1)
    goto got_match;
   /* case 2: range of npp is IS form */
   if (npauxp->nbi1 == -2)
    {
     if (is2_chg_match(npauxp->nbi2.xvi, chgi1, chgi2))
      goto got_match;
     continue;
    }
   /* case 3: must check to see if net chg in range */
   if (chgi1 < npauxp->nbi2.i || chgi2 > npauxp->nbi1) continue;

got_match:
   /* process various xmr special cases */
   /* know any instance filtering done before here */
   /* move from definition target xmr loc. back to ref. loc */
   /* for vpi_ just pushed same inst. on to stack again since no ref. loc. */
   save_idp = NULL;
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - if XMR path does not match, do not eval */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_save_idp_itp_(itp); 
    }

   /* maybe some tracing info */
   if (__ev_tracing) emit_nchglds_trmsg(np, npp);

   switch ((byte) npp->npntyp) {
    case NP_ICONN:
     /* notice iconn load (rhs) causes assign to down lhs mdprt */
     /* but iconn driver assigns from down rhs to iconn lhs for out port */
     __immed_assigns++;
     /* SJM 09/08/01 - can now remove this consistency check */
     /* DBG remove ---
     if (npp->elnpp.eii >= cur_itp->itip->imsym->el.emdp->minum)
      __misc_terr(__FILE__, __LINE__);
     --- */
     cur_itp = get_itp_();
     itp = &(cur_itp->in_its[npp->elnpp.eii]);
     ip = itp->itip;
     downmdp = ip->imsym->el.emdp;
     /* SJM 09/08/01 - can now remove this consistency check */
     /* DBG remove ---
     if (npp->obnum >= downmdp->mpnum) __misc_terr(__FILE__, __LINE__);
     --- */
     mpp = &(downmdp->mpins[npp->obnum]);
     /* assign from rhs up rhs iconn to lhs down mpp ref. for input port */
     /* notice down always take only 4 args, down do not have first mpp */
     (*mpp->mpaf.mpp_downassgnfunc)(mpp->mpref, ip->ipins[npp->obnum], itp);
     break;
    case NP_PB_ICONN:
     /* notice iconn load (rhs) causes assign to down lhs mdprt */
     /* but iconn driver assigns from down rhs to iconn lhs for out port */
     __immed_assigns++;
     /* SJM 09/08/01 - can now remove this consistency check */
     /* DBG remove ---
     if (npp->elnpp.eii >= cur_itp->itip->imsym->el.emdp->minum)
      __misc_terr(__FILE__, __LINE__);
     --- */
     cur_itp = get_itp_();
     itp = &(cur_itp->in_its[npp->elnpp.eii]);
     ip = itp->itip;
     downmdp = ip->imsym->el.emdp;
     /* SJM 09/08/01 - can now remove this consistency check */
     /* DBG remove ---
     if (npp->obnum >= downmdp->mpnum) __misc_terr(__FILE__, __LINE__);
     --- */
     mpp = &(downmdp->mpins[npp->obnum]);
     mpp = &(mpp->pbmpps[npp->pbi]);
     /* assign from rhs up rhs iconn to lhs down mpp ref. for input port */
     /* notice down always take only 4 args, down do not have first mpp */
     (*mpp->mpaf.mpp_downassgnfunc)(mpp->mpref,
      ip->pb_ipins_tab[npp->obnum][npp->pbi], itp);
     break;
    case NP_MDPRT:
     /* top of itstk determines which module inst this is and */
     /* which up instance port to assign to for output port */
     __immed_assigns++;
     downmdp = npp->elnpp.emdp;
     /* DBG remove --- */
     if (npp->obnum >= downmdp->mpnum) __misc_terr(__FILE__, __LINE__);
     /* --- */
     mpp = &(downmdp->mpins[npp->obnum]);
     cur_itp = get_itp_();
     itp = cur_itp->up_it;
     /* DBG remove - bug if trying to assign output of top module --- */
     if (itp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* assign from rhs down mpp ref. to up lhs iconn for output port */
     /* for input port, assign from rhs up iconn to down mod port */
     /* notice up always take only 3 args, down have extra 1st arg mpp */
     (*mpp->mpaf.mpp_upassgnfunc)(cur_itp->itip->ipins[npp->obnum],
      mpp->mpref, itp);
     break;
    case NP_PB_MDPRT:
     /* top of itstk determines which module inst this is and */
     /* which up instance port to assign to for output port */
     __immed_assigns++;
     downmdp = npp->elnpp.emdp;
     mpp = &(downmdp->mpins[npp->obnum]);
     mpp = &(mpp->pbmpps[npp->pbi]);
     cur_itp = get_itp_();
     itp = cur_itp->up_it;
     (*mpp->mpaf.mpp_upassgnfunc)(
      cur_itp->itip->pb_ipins_tab[npp->obnum][npp->pbi],
      mpp->mpref, itp);
     break;
    case NP_GATE:
     /* evaluate load that is gate input and probably schedule gate chg */
     gp = npp->elnpp.egp;
     (*gp->gchg_func)(gp, npp->obnum);
     break;
    case NP_CONTA:
     /* know input that changed is always port 0 (only input) */
     /* SJM - 09/18/02 - for per bit rhs concat form same net pin type */
     __eval_conta_rhs_ld(npp);
     break;
    case NP_TRANIF:
     __eval_tranif_ld(npp->elnpp.egp, (int32) npp->obnum);
     break;
    case NP_TCHG:
     __process_npp_timofchg(np, npp);
     break;
    case NP_MIPD_NCHG:
     /* SJM 07/09/01 - for MIPD inserted between net(s) that connect to port */
     /* and loads, net pin t that causes schedule before processing rest */

     /* DBG remove --- */
     if (np->nlds != npp) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* SJM 07/13/01 if mipd net load processing already delayed, skip sched */
     /* and stop processing, algorithm is to store port conn net val and */
     /* sched ev, then ev processing routine puts on nchg list as if store */
     /* had happened after del - can't propagate MIPD nchges until normal */
     /* nchg loop */

     /* SJM 08/29/08 - if no mipd glitch check option selected, never */
     /* reschedule MIPD delays - if reschedule needed option will cause */
     /* wrong results, but can speed by by 20-30% */
     if (__mipd_cycle_pnd0_schd || is_delayed_mipd) break;

     /* scalar is special case */
     if (!np->n_isavec)
      {
       mipdp = &(npp->elnpp.emipdbits[0]);
       if (mipdp->no_mipd) break;
       __sched_mipd_nchg(np, -1, mipdp);
      }
     else if (chgi1 == -1)
      {
       for (bi = np->nwid - 1; bi >= 0; bi--)
        {
         mipdp = &(npp->elnpp.emipdbits[bi]);
         /* SJM 07/24/05 - must process all bits even if middle no mipd */
         if (mipdp->no_mipd) continue;
         __sched_mipd_nchg(np, bi, mipdp);
        }
      }
     else
      {
       for (bi = chgi1; bi >= chgi2; bi--)
        {
         mipdp = &(npp->elnpp.emipdbits[bi]);
         /* SJM 07/24/05 - must process all bits even if middle no mipd */
         if (mipdp->no_mipd) continue;
         __sched_mipd_nchg(np, bi, mipdp);
        }
      }
     if (save_idp != NULL)
      { 
       restore_idp_();
      }
     /* notice must return since because of MIPD wasn't really changed */
     /* works because mipd npp always first on list */
     return;
     /* pull driver only illlegal here */
    default: __case_terr(__FILE__, __LINE__);
   }
   if (save_idp != NULL)
    {
     restore_idp_();
    }
  }
}

/*
 * process MIPD event
 *
 * simple proc that just processes all but first MIPD delay schedule NPP
 * routine here since same as eval nchgs
 *
 * all MIPD events do is delay propagation from changed net(s) connected
 * to input or inout ports to its loads by delay amount - tricky part is
 * path-src delay value calculation
 */
extern void __process_mipd_nchg_ev(void)
{
 int32 bi, bi2, inum;
 struct net_t *np;
 struct mipd_t *mipdp;
 struct tev_t *tevp;

 tevp = __cur_tevp;
 np = tevp->tu.tenp->tenu.np;
 bi = tevp->tu.tenp->nbi;

 if (__ev_tracing)
  {
   __evtr_resume_msg();
   __tr_msg("-- tracing MIPD event for %s\n",
    __to_cur_evtrwnam(__xs, np, bi, bi));
  }

 /* turn off mipd sheduled event */
 bi2 = (bi == -1) ? 0 : bi;
 mipdp = &(np->nlds->elnpp.emipdbits[bi2]);
 inum = get_inum_();
 mipdp->mipdschd_tevs[inum] = NULL;

 /* add to nchg list if net not already all changed */
 /* dmpvars bits chg not turned on since dumpvar happens when net changes */
 /* also can't use normal macro, because never need reg dce wakeup */
 if (!np->n_isavec)
  {
   if ((__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0)
    {
     __add_nchglst_el(np);
     /* SJM 19/01/02 - T because this is 2nd delayed event one so must */
     /* not schedule */
     /* BEWARE - this assumes last element added to end of list */
     __nchg_futend->delayed_mipd = TRUE;
    }
  }
 else
  {
   if ((__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0)
    {
     __add_select_nchglst_el(np, bi, bi);
     /* SJM 19/01/02 - T because this is 2nd delayed event one so must */
     /* not schedule */
     /* BEWARE - this assumes last element added to end of list */
     __nchg_futend->delayed_mipd = TRUE;
    }
  }

 /* free mipd event auxialiary field here since bit and wire extracted */
 __my_free(tevp->tu.tenp, sizeof(struct tenp_t));
 tevp->tu.tenp = NULL;
}

/*
 * emit eval netchg lds trace message
 */
static void emit_nchglds_trmsg(struct net_t *np, struct net_pin_t *npp)
{
 int32 i1, i2;
 struct npaux_t *npauxp;
 char s1[RECLEN], s2[RECLEN];

 __evtr_resume_msg();
 if (__debug_flg)
  {
   if ((npauxp = npp->npaux) == NULL) i1 = i2 = -1;
   else __get_cor_range(npauxp->nbi1, npauxp->nbi2, &i1, &i2);
   __tr_msg("-- after %s %s changed to %s processing %s\n",
    __to_wtnam(s1, np), __to_cur_evtrwnam(__xs, np, i1, i2),
   __var_tostr(__xs2, np, i1, i2, BHEX), __to_npptyp(s2, npp));
  }
}

/*
 * return T if is IS2 form bit range (depends on itree place) matches
 * T if bit inside npi1..npi2
 * will overlap unless either high changed below low of range
 * or low changed above high of range
 *
 * SJM 10/12/04 - changed to pass contab ndx instead of ptr since contab
 * realloced
 */
static int32 is2_chg_match(int32 nbi2_xvi, int32 npi1, int32 npi2)
{
 int32 i1;
 word32 *wp;
 int32 inum;

 wp = &(__contab[nbi2_xvi]);
 inum = get_inum_();
 wp = &(wp[2*inum]);
 /* if value x - force match since unknown - only can happen for procedural */
 if (wp[1] != 0L) return(TRUE);
 i1 = (int32) wp[0];
 /* know form here h:0 */
 return(npi1 >= i1 && npi2 <= i1);
}

/*
 * get an possibly corrected for is2 form bit index (part select always split)
 */
extern void __get_cor_range(int32 oi1, union intptr_u oi2, int32 *i1,
 int32 *i2)
{
 word32 *wp;
 int32 inum;

 if (oi1 != -2) { *i1 = oi1; *i2 = oi2.i; }
 else
  {
   /* SJM 10/12/04 - because contab realloced, must be ndx base of IS */
   wp = &(__contab[oi2.xvi]);
   inum = get_inum_();
   *i1 = *i2 = (int32) wp[2*inum];
  }
}

/*
 * DECLARATIVE EVENT SCHEDULING/PROCESSING ROUTINES
 */

/*
 * GATE EVENT ROUTINES
 */

/*
 * GENERAL COMMENTS FOR ALL ROUTINES:
 *
 * evaluate a gate because gate input changed and the gate input is
 * a load of the changed wire
 *
 * when gate gp input i of inst. cur. itp changes, eval. gate and maybe
 * schedule output change if has delay and output changed
 * after changing input in gate/inst. state vector
 *
 * notice 1 bit conta's are transformed to gates during fix up
 * so changes handled here
 *
 * after these if inputs differ all of old gate value, new gate val,
 * old gate strength and new gate strength set
 */

/* --- unused non proc call gate eval routine
static void eval_gatein_ld(struct gate_t *gp, int32 i)
{
 switch ((byte) gp->g_class) {
  case GC_LOGIC: std_chg_logic_gate(gp, i); break;
  case GC_UDP: std_chg_udp_gate(gp, i); break;
  case GC_BUFIF: std_chg_bufif_gate(gp, i); break;
  case GC_MOS: std_chg_mos_gate(gp, i); break;
  case GC_CMOS: std_chg_cmos_gate(gp, i); break;
  default: __case_terr(__FILE__, __LINE__);
 }
}
--- */

/*
 * evaluate a logic - std not optimized version
 */
static void std_chg_logic_gate(struct gate_t *gp, word32 i)
{
 int32 out_chg;

 if (!__eval_logic_gate(gp, i, &out_chg))
  { if (__ev_tracing) trace_gunchg(gp, i); return; }

 if (__ev_tracing) evtr_prop_gatechg(gp, i, out_chg);
 else
  {
   if (gp->g_delrep == DT_NONE) { if (out_chg) __change_gate_outwire(gp); }
   else prop_gatechg(gp, out_chg, FALSE);
  }
}

/*
 * accelerated 2 input gate (all XL style simple expressions)
 *
 * if no delay and not ev trace does all inline, if delay call normal prop
 * both ports must be constant bit select or scalar
 * inputs can not be strength for this most optimized routine
 */
static void acc_chg_bufnot(struct gate_t *gp, word32 i)
{
 int32 out_chg, gatid, biti;
 word32 ouwrd, uwrd, ngav, ngbv;
 word32 *wp, igav, igbv;
 struct expr_t *xp;
 struct net_t *np;

 xp = gp->gpins[1];
 if (xp->optyp == ID)
  {
   np = xp->lu.sy->el.enp;
   igav = __idp[np->nva_ofs];
   igbv = (igav >> 1) & 1;
   igav &= 1;
  }
 else
  {
   np = xp->lu.x->lu.sy->el.enp;
   __ld_bit(&igav, &igbv, np, (int32) __contab[xp->ru.x->ru.xvi]);
  }

 __new_inputval = igav | (igbv << 1);
 /* eval changed input and store in gstate if needed */
 /* 12/19/99 SJM - notice buf or not still packed into 1 byte but vars */
 /* only packed into word32 as smallest */
 ouwrd = __idp[gp->gstate_ofs];

 /* input for not is bits 0 and 2 */
 uwrd = ouwrd & ~(0x5L);
 uwrd |= (igav | (igbv << 2));
 /* input change did not change gate */
 if (uwrd == ouwrd) { if (__ev_tracing) trace_gunchg(gp, i); return; }
 __idp[gp->gstate_ofs] = uwrd;

 /* value for not is bits 1 and 3 */
 __old_gateval = ((uwrd >> 1) & 1L) | ((uwrd >> 2) & 2L);

 /* evaluate - not and buf always convert z to x */
 gatid = gp->gmsym->el.eprimp->gateid;
 ngbv = (uwrd >> 2) & 1L;
 if (gatid == G_NOT) ngav = (!(uwrd & 1L)) | ngbv;
 else if (gatid == G_BUF) ngav = (uwrd & 1L) | ngbv;
 /* but cont. ASSIGN passes z */
 else ngav = (uwrd & 1L);

 __new_gateval = ngav | (ngbv << 1);
 /* set to T (non 0) if not equal if changed (different) */
 out_chg = (__old_gateval != __new_gateval);
 /* if tracing must use std trace store-propagate routine */
 if (__ev_tracing) { evtr_prop_gatechg(gp, i, out_chg); return; }
 /* handle delay case using normal gate chg */
 /* third param means acc possible because called from acc routine */
 if (gp->g_delrep != DT_NONE) { prop_gatechg(gp, out_chg, TRUE); return; }

 /* immediate fast assign for accelerated */
 /* inline steps in store gate output value */
 if (!out_chg) return;

 /* g pdst on if wire driven by gate is path dest. or has delay */
 if (gp->g_pdst) { __change_gate_outwire(gp); return; }

 /* non delay acc immediate assign code */
 xp = gp->gpins[0];
 /* update state with computed output value is bits 1 and 3 */
 uwrd = uwrd & ~(0x2L) & ~(0x8L);
 uwrd |= ((ngav << 1) | (ngbv << 3));
 __idp[gp->gstate_ofs] = uwrd;

 /* accelerated assign to pin 0 (output) */
 if (xp->optyp == ID)
  {
   np = xp->lu.sy->el.enp;
   if (np->frc_assgn_allocated)
    {
     igav = ngav; igbv = ngbv;
     if (!__correct_forced_newwireval(np, &igav, &igbv))
      goto try_trace;
    }
   /* here since avoiding value store, need to add net change el. */
   wp = &(__idp[np->nva_ofs]);
   chg_st_scalval_(wp, ngav, ngbv);
   /* not 0 for mask ands is T */
   /* if lhs chged and no lds/dces and not entire inst changed, record it */
   if (__lhs_changed) 
    {
     record_nchg_(np);
    }
  }
 else
  {
   np = xp->lu.x->lu.sy->el.enp;
   biti = (int32) __contab[xp->ru.x->ru.xvi];

   /* if the 1 bit is forced nothing to do else normal assign */
   if (np->frc_assgn_allocated
    && __forced_inhibit_bitassign(np, xp->lu.x, xp->ru.x)) goto try_trace;
   /* notice this adds the net chg element if needed */
   __chg_st_bit(np, biti, ngav, ngbv);
  }
try_trace:
 if (__ev_tracing) trace_chg_gateout(gp, xp);
}

/*
 * accelerated 1 input (maybe stren) gate (all XL style simple expressions)
 *
 * if no delay and not ev trace does all inline, if delay call normal prop
 * both ports must be constant bit select or scalar
 * here inputs may be strength (removed), but cannot drive stren
 *
 * only difference is slow if for accessing value from strength
 */
static void acc_stichg_bufnot(struct gate_t *gp, word32 i)
{
 int32 out_chg, gatid, biti;
 word32 *wp, ouwrd, uwrd, ngav, ngbv;
 word32 igav, igbv;
 struct expr_t *xp;
 struct net_t *np;

 xp = gp->gpins[1];
 np = xp->lu.sy->el.enp;
 if (xp->optyp == ID)
  {
   /* SJM - 06-28-07 - now stren and non stren cases the same */
   igav = __idp[np->nva_ofs];
   igbv = (igav >> 1) & 1;
   igav &= 1;
  }
 else __ld_bit(&igav, &igbv, np, (int32) __contab[xp->ru.x->ru.xvi]);

 __new_inputval = igav | (igbv << 1);
 /* eval changed input and store in gstate if needed */
 ouwrd = __idp[gp->gstate_ofs];
 /* input for not is bits 0 and 2 */
 uwrd = ouwrd & ~(0x5L);
 uwrd |= (igav | (igbv << 2));
 /* input change did not change gate */
 if (uwrd == ouwrd) { if (__ev_tracing) trace_gunchg(gp, i); return; }
 __idp[gp->gstate_ofs] = uwrd;

 /* value for not is bits 1 and 3 */
 __old_gateval = ((uwrd >> 1) & 1L) | ((uwrd >> 2) & 2L);

 /* evaluate - not and buf always convert z to x */
 gatid = gp->gmsym->el.eprimp->gateid;
 ngbv = (uwrd >> 2) & 1L;
 if (gatid == G_NOT) ngav = (!(uwrd & 1L)) | ngbv;
 else if (gatid == G_BUF) ngav = (uwrd & 1L) | ngbv;
 /* but cont. ASSIGN passes z */
 else ngav = (uwrd & 1L);

 __new_gateval = ngav | (ngbv << 1);
 /* set to T (non 0) if not equal if changed (different) */
 out_chg = (__old_gateval != __new_gateval);
 /* if tracing must use std trace store-propagate routine */
 if (__ev_tracing) { evtr_prop_gatechg(gp, i, out_chg); return; }
 /* handle delay case using normal gate chg */
 /* thrd param T because being called from acc routine */
 if (gp->g_delrep != DT_NONE) { prop_gatechg(gp, out_chg, TRUE); return; }

 /* immediate fast assign for accelerated */
 /* inline steps in store gate output value */
 if (!out_chg) return;

 /* g pdst on if wire driven by gate is path dest. or has delay */
 if (gp->g_pdst) { __change_gate_outwire(gp); return; }

 /* non delay acc assign code */
 xp = gp->gpins[0];
 /* update state with computed output value is bits 1 and 3 */
 uwrd = uwrd & ~(0x2L) & ~(0x8L);
 uwrd |= ((ngav << 1) | (ngbv << 3));
 __idp[gp->gstate_ofs] = uwrd;
 /* accelerated assign to pin 0 (output) */
 if (xp->optyp == ID)
  {
   np = xp->lu.sy->el.enp;
   if (np->frc_assgn_allocated)
    {
     igav = ngav; igbv = ngbv;
     if (!__correct_forced_newwireval(np, &igav, &igbv))
      goto try_trace;
    }
   /* here since avoiding value store, need to add net change el. */
   wp = &(__idp[np->nva_ofs]);
   chg_st_scalval_(wp, ngav, ngbv);

   /* not 0 for mask ands is T */
   /* if lhs chged and no lds/dces and not entire inst changed, record it */
   if (__lhs_changed) 
    {
     record_nchg_(np);
    }
  }
 else
  {
   np = xp->lu.x->lu.sy->el.enp;
   biti = (int32) __contab[xp->ru.x->ru.xvi];
   /* if the 1 bit is forced nothing to do else normal assign */
   if (np->frc_assgn_allocated
    && __forced_inhibit_bitassign(np, xp->lu.x, xp->ru.x)) goto try_trace;
   /* notice this adds the net chg element if needed */
   __chg_st_bit(np, biti, ngav, ngbv);
  }
try_trace:
 if (__ev_tracing) trace_chg_gateout(gp, xp);
}

/*
 * acceleated up to 3 input (4 pints) gate with no delay
 *
 * could unwind to separate for each gate type
 * if no delay and not ev trace does all inline, if delay call normal prop
 * both ports must be constant bit select or scalar
 * inputs must not be stren wires
 * degenerate 2 input gate not accelerated
 */
static void acc_chg_4igate(struct gate_t *gp, word32 i)
{
 int32 out_chg, biti, bi;
 word32 ouwrd, uwrd, ngav, ngbv, gwid;
 struct expr_t *xp;
 struct net_t *np;
 word32 gav, gbv, mask, *wp;

 xp = gp->gpins[i];
 if (xp->optyp == ID)
  {
   /* SJM 06-28-07 - now faster to avoid macro */
   gav = __idp[xp->lu.sy->el.enp->nva_ofs];
   gbv = (gav >> 1) & 1;
   gav &= 1;
  }
 else
  {
   __ld_bit(&gav, &gbv, xp->lu.x->lu.sy->el.enp,
    (int32) __contab[xp->ru.x->ru.xvi]);
  } 
 bi = i - 1;
 gwid = gp->gpnum;
 __new_inputval = gav | (gbv << 1);

 /* eval changed input and store in gstate if needed */
 ouwrd = __idp[gp->gstate_ofs];
 uwrd = ouwrd & ~(1L << bi) & ~(1L << (gwid + bi));
 uwrd |= ((gav << bi) | (gbv << (gwid + bi)));
 /* input change did not change gate */
 if (uwrd == ouwrd) { if (__ev_tracing) trace_gunchg(gp, i); return; }
 __idp[gp->gstate_ofs] = uwrd;

 /* mask off a/b output bit - now gav/gbv all inputs */
 mask = __masktab[gwid - 1];
 gav = uwrd & mask;
 gbv = (uwrd >> gwid) & mask;
 /* works since know n ins at least 1 - b shifts 1 less, goes b bit */
 __old_gateval = ((uwrd >> (gwid - 1)) & 1L) | ((uwrd >> (2*gwid - 2)) & 2L);

 /* evaluate gate */
 /* LOOKATME - could split and copy for each pin/gate combination */
 ngav = ngbv = 1L;
 switch ((byte) gp->gmsym->el.eprimp->gateid) {
  case G_BITREDAND:
   /* if even 1 0 value in any used bit, result is 0 */
   if (gbv == 0L) { ngav = (gav != mask) ? 0L : 1L; ngbv = 0L; }
   else if ((gav | gbv) != mask) ngav = ngbv = 0L;
   break;
  case G_NAND:
   /* if even 1 0 value in any used bit, result is 1 */
   if (gbv == 0L) { ngav = (gav != mask) ? 1L : 0L; ngbv = 0L; }
   else if ((gav | gbv) != mask) ngbv = 0L;
   break;
  case G_BITREDOR:
   /* if even 1 1 value in any used bit, result is 1 */
   if (gbv == 0L) { ngav = (gav != 0L) ? 1L : 0L; ngbv = 0L; }
   else if ((gav & ~gbv) != 0L) ngbv = 0L;
   break;
  case G_NOR:
   /* if even 1 1 value in any used bit, result is 0 */
   if (gbv == 0L) { ngav = (gav != 0L) ? 0L : 1L; ngbv = 0L; }
   else if ((gav & ~gbv) != 0L) ngav = ngbv = 0L;
   break;
  case G_BITREDXOR:
   if (gbv == 0L) { ngbv = 0L; ngav = __wrd_redxor(gav); }
   break;
  case G_REDXNOR:
   if (gbv == 0L) { ngbv = 0L; ngav = !__wrd_redxor(gav); }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 __new_gateval = ngav | (ngbv << 1);
 /* set to T (non 0) if not equal if changed (different) */
 out_chg = (__old_gateval != __new_gateval);
 /* if tracing must use std trace store-propagate routine */
 if (__ev_tracing) { evtr_prop_gatechg(gp, i, out_chg); return; }
 /* handle delay case using normal gate chg */
 /* thrd param T because being called from acc routine */
 if (gp->g_delrep != DT_NONE) { prop_gatechg(gp, out_chg, TRUE); return; }

 /* immediate fast assign for accelerated */
 /* inline steps in store gate output value */
 if (!out_chg) return;

 /* g pdst on if wire driven by gate is path dest. or has delay */
 if (gp->g_pdst) { __change_gate_outwire(gp); return; }

 /* non delay acc immediate assign code */
 xp = gp->gpins[0];
 /* mask off separated value bits to update output value in uwrd */
 uwrd = uwrd & ~(1L << (gwid - 1)) & ~(1L << (2*gwid - 1));
 /* works because ngav and ngbv exactly 1 low bit */
 uwrd |= ((ngav << (gwid - 1)) | (ngbv << (2*gwid - 1)));
 /* must store twice because update of input may not change output */
 __idp[gp->gstate_ofs] = uwrd;
 /* accelerated assign to pin 0 (output) */
 if (xp->optyp == ID)
  {
   np = xp->lu.sy->el.enp;
   if (np->frc_assgn_allocated)
    {
     gav = ngav; gbv = ngbv;
     if (!__correct_forced_newwireval(np, &gav, &gbv))
      goto try_trace;
    }
   /* here since avoiding value store, need to add net change el. */
   wp = &(__idp[np->nva_ofs]);
   chg_st_scalval_(wp, ngav, ngbv);
   if (__lhs_changed) 
    {
     record_nchg_(np);
    }
  }
 else
  {
   np = xp->lu.x->lu.sy->el.enp;
   biti = (int32) __contab[xp->ru.x->ru.xvi];
   /* if the 1 bit is forced nothing to do else normal assign */
   if (np->frc_assgn_allocated
    && __forced_inhibit_bitassign(np, xp->lu.x, xp->ru.x)) goto try_trace;
   /* this adds the nchg el if needed */
   __chg_st_bit(np, biti, ngav, ngbv);
  }
try_trace:
 if (__ev_tracing) trace_chg_gateout(gp, xp);
}

/*
 * accelerated up to 4 input gate
 *
 * could unwind to separate for each gate type
 * if no delay and not ev trace does all inline, if delay call normal prop
 * both ports must be constant bit select or scalar
 *
 * inputs can be strength wires (removed) but cannot driver stren
 */
static void acc_stichg_4igate(struct gate_t *gp, word32 i)
{
 int32 out_chg, biti, bi;
 word32 *wp, gav, gbv, mask;
 word32 ouwrd, uwrd, ngav, ngbv, gwid;
 struct expr_t *xp;
 struct net_t *np;

 xp = gp->gpins[i];
 np = xp->lu.sy->el.enp;
 if (xp->optyp == ID)
  {
   /* SJM 06-28-07 now both stren and non stren code same here */ 
   gav = __idp[np->nva_ofs];
   gbv = (gav >> 1) & 1;
   gav &= 1;
  }
 else __ld_bit(&gav, &gbv, np, (int32) __contab[xp->ru.x->ru.xvi]);
 bi = i - 1;
 gwid = gp->gpnum;
 __new_inputval = gav | (gbv << 1);

 /* eval changed input and store in gstate if needed */
 ouwrd = __idp[gp->gstate_ofs];
 uwrd = ouwrd & ~(1L << bi) & ~(1L << (gwid + bi));
 uwrd |= ((gav << bi) | (gbv << (gwid + bi)));
 /* input change did not change gate */
 if (uwrd == ouwrd) { if (__ev_tracing) trace_gunchg(gp, i); return; }
 __idp[gp->gstate_ofs] = uwrd;

 /* mask off a/b output bit - now gav/gbv all inputs */
 mask = __masktab[gwid - 1];
 gav = uwrd & mask;
 gbv = (uwrd >> gwid) & mask;
 /* works since know n ins at least 1 - b shifts 1 less, goes b bit */
 __old_gateval = ((uwrd >> (gwid - 1)) & 1L) | ((uwrd >> (2*gwid - 2)) & 2L);

 /* evaluate gate */
 /* LOOKATME - could split and copy for each pin/gate combination */
 ngav = ngbv = 1L;
 switch ((byte) gp->gmsym->el.eprimp->gateid) {
  case G_BITREDAND:
   /* if even 1 0 value in any used bit, result is 0 */
   if (gbv == 0L) { ngav = (gav != mask) ? 0L : 1L; ngbv = 0L; }
   else if ((gav | gbv) != mask) ngav = ngbv = 0L;
   break;
  case G_NAND:
   /* if even 1 0 value in any used bit, result is 1 */
   if (gbv == 0L) { ngav = (gav != mask) ? 1L : 0L; ngbv = 0L; }
   else if ((gav | gbv) != mask) ngbv = 0L;
   break;
  case G_BITREDOR:
   /* if even 1 1 value in any used bit, result is 1 */
   if (gbv == 0L) { ngav = (gav != 0L) ? 1L : 0L; ngbv = 0L; }
   else if ((gav & ~gbv) != 0L) ngbv = 0L;
   break;
  case G_NOR:
   /* if even 1 1 value in any used bit, result is 0 */
   if (gbv == 0L) { ngav = (gav != 0L) ? 0L : 1L; ngbv = 0L; }
   else if ((gav & ~gbv) != 0L) ngav = ngbv = 0L;
   break;
  case G_BITREDXOR:
   if (gbv == 0L) { ngbv = 0L; ngav = __wrd_redxor(gav); }
   break;
  case G_REDXNOR:
   if (gbv == 0L) { ngbv = 0L; ngav = !__wrd_redxor(gav); }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 __new_gateval = ngav | (ngbv << 1);
 /* set to T (non 0) if not equal if changed (different) */
 out_chg = (__old_gateval != __new_gateval);
 /* if tracing must use std trace store-propagate routine */
 if (__ev_tracing) { evtr_prop_gatechg(gp, i, out_chg); return; }
 /* handle delay case using normal gate chg */
 /* thrd param T because being called from acc routine */
 if (gp->g_delrep != DT_NONE) { prop_gatechg(gp, out_chg, TRUE); return; }

 /* immediate fast assign for accelerated */
 /* inline steps in store gate output value */
 if (!out_chg) return;

 /* g pdst on if wire driven by gate is path dest. or has delay */
 if (gp->g_pdst) { __change_gate_outwire(gp); return; }

 /* non delay acc immediate assign code */
 xp = gp->gpins[0];
 /* mask off separated value bits to update output value in uwrd */
 uwrd = uwrd & ~(1L << (gwid - 1)) & ~(1L << (2*gwid - 1));
 /* works because ngav and ngbv exactly 1 low bit */
 uwrd |= ((ngav << (gwid - 1)) | (ngbv << (2*gwid - 1)));
 /* must store twice because update of input may not change output */
 __idp[gp->gstate_ofs] = uwrd;
 /* accelerated assign to pin 0 (output) */
 if (xp->optyp == ID)
  {
   np = xp->lu.sy->el.enp;
   if (np->frc_assgn_allocated)
    {
     gav = ngav; gbv = ngbv;
     if (!__correct_forced_newwireval(np, &gav, &gbv))
      goto try_trace;
    }
   /* here since avoiding value store, need to add net change el. */
   wp = &(__idp[np->nva_ofs]);
   chg_st_scalval_(wp, ngav, ngbv);
   if (__lhs_changed) 
    {
     record_nchg_(np);
    }
  }
 else
  {
   np = xp->lu.x->lu.sy->el.enp;
   biti = (int32) __contab[xp->ru.x->ru.xvi];
   /* if the 1 bit is forced nothing to do else normal assign */
   if (np->frc_assgn_allocated
    && __forced_inhibit_bitassign(np, xp->lu.x, xp->ru.x)) goto try_trace;
   /* this adds the nchg el if needed */
   __chg_st_bit(np, biti, ngav, ngbv);
  }
try_trace:
 if (__ev_tracing) trace_chg_gateout(gp, xp);
}

/*
 * write gate value unchanged when input changes trace msg
 */
static void trace_gunchg(struct gate_t *gp, word32 i)
{
 char s1[RECLEN];

 __tr_msg("-- %s %s %s input %u value unchanged\n",
  gp->gmsym->synam, (gp->g_class == GC_UDP) ? "udp" : "gate",
  to_cur_evtronam(s1, gp->gsym->synam, (struct task_t *) NULL), i);
}

/*
 * evaluate a udp - std not optimized version
 */
static void std_chg_udp_gate(struct gate_t *gp, word32 i)
{
 int32 is_edge, out_chg;

 __cur_udp = gp->gmsym->el.eudpp;
 is_edge = (__cur_udp->utyp == U_EDGE) ? TRUE : FALSE;
 if (!__eval_udp(gp, i, &out_chg, is_edge))
  { if (__ev_tracing) trace_gunchg(gp, i); return; }

 if (__ev_tracing) evtr_prop_gatechg(gp, i, out_chg);
 else
  {
   if (gp->g_delrep == DT_NONE)
    { if (out_chg) __change_gate_outwire(gp); return; }
   prop_gatechg(gp, out_chg, FALSE);
  }
}

/*
 * evaluate a bufif gate - std not optimized version
 */
static void std_chg_bufif_gate(struct gate_t *gp, word32 i)
{
 int32 out_chg;

 /* this sets __new_gateval to strength if out changed T */
 if (!__eval_bufif_gate(gp, i, &out_chg))
  { if (__ev_tracing) trace_gunchg(gp, i); return; }

 if (__ev_tracing) evtr_prop_gatechg(gp, i, out_chg);
 else
  {
   if (gp->g_delrep == DT_NONE)
    { if (out_chg) __change_gate_outwire(gp); return; }
   prop_gatechg(gp, out_chg, FALSE);
  }
}

/*
 * evaluate a mos gate - std not optimized version
 *
 * g resist here is for real resistive gate not flag for acc
 */
static void std_chg_mos_gate(struct gate_t *gp, word32 i)
{
 int32 out_chg, gid;

 /* this sets __new_gateval to strength if out changed T */
 if (!chg_mos_instate(gp, i))
  { if (__ev_tracing) trace_gunchg(gp, i); return; }

 out_chg = TRUE;
 gid = gp->gmsym->el.eprimp->gateid;
 switch (gid) {
  case G_NMOS: __eval_nmos_gate(__idp[gp->gstate_ofs]); break;
  case G_RNMOS: __eval_rnmos_gate(__idp[gp->gstate_ofs]); break;
  case G_PMOS: __eval_pmos_gate(__idp[gp->gstate_ofs]); break;
  case G_RPMOS: __eval_rpmos_gate(__idp[gp->gstate_ofs]); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (__new_gateval == __old_gateval) out_chg = FALSE;

 if (__ev_tracing) evtr_prop_gatechg(gp, i, out_chg);
 else
  {
   if (gp->g_delrep == DT_NONE)
    { if (out_chg) __change_gate_outwire(gp); return; }
   prop_gatechg(gp, out_chg, FALSE);
  }
}

/*
 * evaluate a cmos gate - std not optimized version
 */
static void std_chg_cmos_gate(struct gate_t *gp, word32 i)
{
 int32 out_chg;

 if (!chg_cmos_instate(gp, i))
  { if (__ev_tracing) trace_gunchg(gp, i); return; }

 /* this sets __new_gateval to strength if out changed T */
 __eval_cmos_gate(gp);
 if (__new_gateval == __old_gateval) out_chg = FALSE; else out_chg = TRUE;

 if (__ev_tracing) evtr_prop_gatechg(gp, i, out_chg);
 else
  {
   if (gp->g_delrep == DT_NONE)
    { if (out_chg) __change_gate_outwire(gp); return; }
   prop_gatechg(gp, out_chg, FALSE);
  }
}

/*
 * routine used during prep to determine and set gate in change routine
 * called for all including udp but not trans
 */
extern void __set_gchg_func(struct gate_t *gp)
{
 int32 acc_class;

 switch ((byte) gp->g_class) {
  case GC_LOGIC:
   /* accelerate class is 2 for buf/not and 3 for any up to 4 logic gate */
   /* 0 for cannot accelerate */
   if (!__accelerate) gp->gchg_func = std_chg_logic_gate;
   else
    {
     acc_class = __get_acc_class(gp);
     switch ((byte) acc_class) {
      case ACC_STD: gp->gchg_func = std_chg_logic_gate; break;
      case ACC_BUFNOT: gp->gchg_func = acc_chg_bufnot; break;
      case ACC_STIBUFNOT: gp->gchg_func = acc_stichg_bufnot; break;
      case ACC_4IGATE: gp->gchg_func = acc_chg_4igate; break;
      case ACC_ST4IGATE: gp->gchg_func = acc_stichg_4igate; break;
      default: __case_terr(__FILE__, __LINE__);
     }
    }
   break;
  case GC_UDP: gp->gchg_func = std_chg_udp_gate; break;
  case GC_BUFIF: gp->gchg_func = std_chg_bufif_gate; break;
  case GC_MOS: gp->gchg_func = std_chg_mos_gate; break;
  case GC_CMOS: gp->gchg_func = std_chg_cmos_gate; break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * routine to turn off acceleration for logic gates when gate out terminal
 * value change call back registered
 */
extern void __logic_acc_off(struct gate_t *gp)
{
 if (gp->g_class == GC_LOGIC && gp->gchg_func != std_chg_logic_gate)
  gp->gchg_func = std_chg_logic_gate;
}

/*
 * for gate that because of added vpi driver needs to be chaned to fi>1
 * set the standard unoptimized gate assign routine
 */
extern void __vpi_set_chg_proc(struct gate_t *gp)
{
 /* if non logic gate, never optimized so can just use the std */
 if (gp->g_class == GC_LOGIC)
  {
   if (gp->gchg_func != std_chg_logic_gate)
    {
     gp->gchg_func = std_chg_logic_gate;
    }
  }
}

/*
 * return T if gate has accelerated action routine
 */
extern int32 __gate_is_acc(struct gate_t *gp)
{
 if (gp->gchg_func == acc_chg_bufnot || gp->gchg_func == acc_stichg_bufnot
  || gp->gchg_func == acc_chg_4igate || gp->gchg_func == acc_stichg_4igate)
  return(TRUE);
 return(FALSE);
}

/*
 * propagate the gate change - normal version called when event tracing off
 * complicated because of spike analysis
 * this works for strength
 * this assumed old and new gateval globals set before here
 *
 * if gate or udp drives highz[01] strength used to access delay but gate
 * must drive actual value which is converted when assigned to wire
 * outchg for highz[01] not changed since same hiz will be same 0 or 1
 *
 * show cancel e analysis uses gate output not possible hiz wire since 0/1
 * glitch will just map to hiz spikes
 *
 * only called if know has delay and know old gateval and new gateval
 * globals set
 */
static void prop_gatechg(struct gate_t *gp, int32 outchg, int32 is_acc)
{
 struct tev_t *tevp;
 word64 gdel, schtim;

 /* no pending scheduled event */
 if ((tevp = (struct tev_t *) __idp[gp->schd_tevs_ofs]) == NULL)
  {
   /* case 1a: output changed */
   if (outchg)
    {
     /* if 0 or 1 and hiz strength gate need to use to hiz delay */
     if (gp->g_hasst && (__new_gateval & 2) == 0
      && __hizstren_del_tab[gp->g_stval] == 1)
      gdel = __hizstrengate_getdel(gp);
     else gdel = __get_del(gp->g_du, gp->g_delrep);

     schtim = __simtime + gdel;
     schedule_1gev(gp, gdel, schtim, is_acc);
    }
   /* if output did not change, nothing to do */
   return;
  }

 /* need time of new value scheduled change for this analysis */
 if (gp->g_hasst && (__new_gateval & 2) == 0
  && __hizstren_del_tab[gp->g_stval] == 1) gdel = __hizstrengate_getdel(gp);
 else gdel = __get_del(gp->g_du, gp->g_delrep);

 schtim = __simtime + gdel;

 /* pending event */
 /* new and old same - scheduled different - real pulse/glitch */
 if (!outchg)
  {
   if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
    __emit_pulsewarn(gp, tevp, &(tevp->etime), &schtim, "drives glitch");

   /* if spike, suppress future but schedule to x at currently scheduled */
   if (__show_cancel_e)
    {
     if (__showe_onevent)
      { tevp->outv = __get_showcancele_val(gp); return; }

     /* immediate assign then cancel */
on_detect_show_x:
     __new_gateval = __get_showcancele_val(gp);
     if (tevp->gev_acc) __acc_evchg_gate_outwire(gp);
     else __change_gate_outwire(gp);
     /* newly scheduled to same so no event */
     if (__compiled_sim) 
      {
       __asl_linkout_tevp_no_trigger(tevp);
      }
     else tevp->enterptr = __process_cancel_ev_enterp;
     __inertial_cancels++;
     __idp[gp->schd_tevs_ofs] = (t_midat) NULL;
     return;
    }
   /* newly scheduled to same so no event */
   if (__compiled_sim) 
    {
     __asl_linkout_tevp_no_trigger(tevp);
    }
   else tevp->enterptr = __process_cancel_ev_enterp;
   __inertial_cancels++;
   __idp[gp->schd_tevs_ofs] = (t_midat) NULL;
   return;
  }
 /* new schedule to same value case */
 /* know that delay same and later so just discard new event */
 /* done silently here - trace message only */
 if (tevp->outv == (byte) __new_gateval) return;

 /* normal inertial reschedule */
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_pulsewarn(gp, tevp, &(tevp->etime), &schtim, "unstable");

 if (__show_cancel_e)
  {
   if (__showe_onevent) { tevp->outv = __get_showcancele_val(gp); return; }
   goto on_detect_show_x;
  }
 /* reschedule - handles cancel */
 reschedule_1gev(tevp, gdel, schtim, __new_gateval, is_acc);
}

/*
 * propagate the gate change
 * complicated because of show cancel e analysis
 *
 * notice new gateval and old gateval set and has strength value if present
 * see prop gatechg routines for more comments
 * unlike prop_gatechg, this must be called for DT_NONE assigns
 * all events scheduled from here must not set event accelerate bit
 *
 * SJM 11/27/00 - this always calls or schedules change gate outwire where
 * the gate terminal call back is checked so do not need separate code
 */
static void evtr_prop_gatechg(struct gate_t *gp, word32 i, int32 outchg)
{
 word64 gdel, schtim;
 struct tev_t *tevp;
 char vs1[10], vs2[10], vs3[10];
 char s1[RECLEN], s2[RECLEN];

 __tr_msg("-- %s gate %s input %d changed to %s:\n",
  gp->gmsym->synam, to_cur_evtronam(s1, gp->gsym->synam,
  (struct task_t *) NULL), i, __to_ginam(vs1, gp, __new_inputval, i));

 /* case 0: gate has no delay - not even #0 */
 if (gp->g_delrep == DT_NONE)
  {
   if (!outchg) { __tr_msg(" NODEL, NOCHG\n"); return; }

   /* this assigns or schedules the 1 bit net change */
   __tr_msg(" NODEL <OV=%s, NV=%s>\n",
    __to_gonam(vs1, gp, __old_gateval), __to_gonam(vs2, gp, __new_gateval));
   __change_gate_outwire(gp);
   return;
  }

 /* need time of new value scheduled change for this analysis */
 if (gp->g_hasst && (__new_gateval & 2) == 0
  && __hizstren_del_tab[gp->g_stval] == 1) gdel = __hizstrengate_getdel(gp);
 else gdel = __get_del(gp->g_du, gp->g_delrep);
 schtim = __simtime + gdel;

 /* case 1: no pending scheduled event */
 if ((tevp = (struct tev_t *) __idp[gp->schd_tevs_ofs]) == NULL)
  {
   /* output did not change */
   if (!outchg)
    {
     /* no net change and must cancel any already scheduled event */
     __tr_msg(" DEL, NOCHG <OV=%s>\n",
      __to_gonam(vs1, gp, __old_gateval));
     return;
    }
   __tr_msg(" DEL, SCHD AT %s <OV=%s, NSV=%s>\n",
    __to_timstr(s1, &schtim), __to_gonam(vs1, gp, __old_gateval),
    __to_gonam(vs2, gp, __new_gateval));
   /* schedule */
   schedule_1gev(gp, gdel, schtim, FALSE);
   return;
  }
 /* pending event */
 /* new and old same - scheduled different - real pluse/glitch */
 if (!outchg)
  {
   if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
    __emit_pulsewarn(gp, tevp, &(tevp->etime), &schtim, "drives glitch");

   /* if spike on set to x at time of previous change not inertial */
   if (__show_cancel_e)
    {
     if (__showe_onevent) sprintf(s2, "%s (on event)", __to_timstr(__xs,
      &(tevp->etime)));
     else sprintf(s2, "%s (on detect)", __to_timstr(__xs, &__simtime));
     __tr_msg(
      " DEL, PEND AT %s PULSE <OV=NSV=%s, OSV=%s SHOWING X AT %s MAYBE SWITCHED>\n",
      __to_timstr(s1, &(tevp->etime)), __to_gonam(vs1, gp, __old_gateval),
      __to_gonam(vs2, gp, tevp->outv), s2);

     if (__showe_onevent)
      { tevp->outv = __get_showcancele_val(gp); return; }

     /* immediate assign then cancel */
on_detect_show_x:
     __new_gateval = __get_showcancele_val(gp);
     if (tevp->gev_acc) __acc_evchg_gate_outwire(gp);
     else __change_gate_outwire(gp);
     /* newly scheduled to same so no event */
     tevp->enterptr = __process_cancel_ev_enterp;
     __inertial_cancels++;
     __idp[gp->schd_tevs_ofs] = (t_midat) NULL;
     return;
    }
   /* newly scheduled to same (pulse) so no event */
   tevp->enterptr = __process_cancel_ev_enterp;
   __inertial_cancels++;
   __idp[gp->schd_tevs_ofs] = (t_midat) NULL;
   /* SJM 01/21/02 - msg unclear since new sched value was missing */
   __tr_msg(" DEL, PEND, PULSE, INERTIAL CANCEL AT %s <OV=%s, OSV=%s NSV=%s>\n",
    __to_timstr(s1, &(tevp->etime)), __to_gonam(vs1, gp, __old_gateval),
    __to_gonam(vs2, gp, tevp->outv), __to_gonam(vs3, gp, __new_gateval));
   return;
  }

 /* new schedule to same value case */
 /* know that delay same and later so just discard new event */
 /* done silently here - trace message only */
 if (tevp->outv == (byte) __new_gateval)
  {
   __tr_msg(
    " DEL, MODEL ANOMALLY IGNORE SCHED TO SAME <OSV=NSV=%s> OLD AT %s NEW %s\n",
    __to_gonam(vs1, gp, __new_gateval), __to_timstr(s1, &(tevp->etime)),
    __to_timstr(s2, &schtim));
   return;
  }

 /* normal inertial reschedule */
 if (__warn_cancel_e && !__no_warns && !__em_suppr(592))
  __emit_pulsewarn(gp, tevp, &(tevp->etime), &schtim, "unstable");

 if (__show_cancel_e)
  {
   if (__showe_onevent) __to_timstr(s2, &schtim);
   else __to_timstr(s2, &__simtime);
   if (__showe_onevent) sprintf(s1, "%s (on event)", __to_timstr(__xs,
    &(tevp->etime)));
   else sprintf(s1, "%s (on detect)", __to_timstr(s1, &__simtime));
   __tr_msg(
    " DEL, PEND AT %s, UNSTABLE <OV=%s, OSV=%s, NSV=%s SHOWING X AT %s MAYBE SWITCHED>\n",
    __to_timstr(s1, &(tevp->etime)), __to_gonam(vs1, gp, __old_gateval),
    __to_gonam(vs2, gp, tevp->outv), __to_gonam(vs3, gp, __new_gateval), s2);

   if (__showe_onevent) { tevp->outv = __get_showcancele_val(gp); return; }
   goto on_detect_show_x;
  }

 __tr_msg(" DEL, PEND, UNSTABLE RESCHD <OV=%s, OSV=%s AT %s, NSV=%s AT %s>\n",
  __to_gonam(vs1, gp, __old_gateval),
  __to_gonam(vs2, gp, tevp->outv), __to_timstr(s1, &(tevp->etime)),
  __to_gonam(vs3, gp, __new_gateval), __to_timstr(s2, &schtim));
 reschedule_1gev(tevp, gdel, schtim, __new_gateval, FALSE);
}

/*
 * compute show cancel x value depending on gate class and strength
 *
 * idea is to change event change to value but time still start of
 * region after place where gate may or may not have switched
 */
extern word32 __get_showcancele_val(struct gate_t *gp)
{
 int32 nd_stren = FALSE;

 switch ((byte) gp->g_class) {
  /* these never have strength value */
  case GC_LOGIC: case GC_UDP:
   if (gp->g_hasst) nd_stren = TRUE;
   break;
  case GC_BUFIF: nd_stren = TRUE; break;
  case GC_MOS: case GC_CMOS:
   /* LOOKATME - since mos gates pass strength for now driving strong x */
   /* maybe could take strength from input? and leave z */
   return(ST_STRONGX);
  /* for tranif input spike sched. only, x is turned off (0) */
  case GC_TRANIF: return(0);
  default: __case_terr(__FILE__, __LINE__);
 }
 /* notice no need to correct for possible highz strength since value x */
 /* SJM 08/07/01 - this works because with val x need both 0 and 1 strens */
 if (nd_stren) return((gp->g_stval << 2) | 3);
 return(3);
}

/*
 * emit an object name for tracing with path
 * cannot use __xs in here
 */
static char *to_evtronam(char *s, char *onam, t_midat *te_idp,
 struct task_t *tskp)
{
 char s1[RECLEN], s2[RECLEN];

 sprintf(s, "%s.%s", __msg_idp_blditree(s2, te_idp, tskp), __schop(s1, onam));
 return(s);
}

/*
 * emit an object name for tracing with path
 * cannot use __xs in here
 */
static char *to_cur_evtronam(char *s, char *onam, struct task_t *tskp)
{
 struct itree_t *itp;
 char s1[RECLEN], s2[RECLEN];

 itp = get_itp_();
 sprintf(s, "%s.%s", __msg_blditree(s2, itp, tskp), __schop(s1, onam));
 return(s);
}

/*
 * schedule 1 gate event
 * expects __new_gateval to contain value to schedule to
 */
static struct tev_t *schedule_1gev(struct gate_t *gp, word64 gdel,
 word64 schtim, int32 is_acc)
{
 struct tev_t *tevp;

 alloc_cur_tev_(tevp, __process_gatechg_ev_enterp, schtim);
 if (gdel == 0ULL)
  {
   /* this is #0, but must still build tev */
   if (__p0_te_hdrp == NULL) __p0_te_hdrp = __p0_te_endp = tevp;
   else { __p0_te_endp->tenxtp = tevp; __p0_te_endp = tevp; }
  }
 else __insert_event(tevp);

 __idp[gp->schd_tevs_ofs] = (t_midat) tevp;
 tevp->tu.tegp = gp;
 /* if logic or udp, no strength, event processing assign will handle */
 /* if bufif, mos or cmos, know has strength, if tranif conducting state */
 tevp->outv = (byte) __new_gateval;
 /* acc. store only if gate is acc. and no conn. wire delay (resist off) */
 /* is acc T only if called from acc routine because acc routine never */
 /* possible for real resistive mos or tran */
 /* for mos with delay, can get here with g pdst on but is acc off */
 tevp->gev_acc = (is_acc && !gp->g_pdst);
 return(tevp);
}

/*
 * take event and new value and either update if time same or cancel and
 * create new event if later
 */
static void reschedule_1gev(struct tev_t *tevp, word64 gdel, word64 newtim,
 word32 newoutv, int32 is_acc)
{
 /* if del == 0 (pnd0), will always be same time reschedule */
 if (gdel == 0ULL)
  {
   /* new value replaces old - must also be in event */
   __newval_rescheds++;
   tevp->outv = (byte) newoutv;
   return;
  }

 /* case 3c-3 - more in future, cancel and reschedule */
 if (__compiled_sim) 
  {
   __asl_linkout_tevp_no_trigger(tevp);
  }
 else tevp->enterptr = __process_cancel_ev_enterp;

 __inertial_cancels++;
 tevp = schedule_1gev(tevp->tu.tegp, gdel, newtim, is_acc);
 tevp->outv = (byte) newoutv;
}

/*
 * emit the pulse (inertial reschedule) warning if not turned off
 * types are drives for normal spike and unstable for change that does not
 * do anything but interfere with transition
 */
extern void __emit_pulsewarn(struct gate_t *gp, struct tev_t *tevp,
 word64 *etim, word64 *newetim, char *sptnam)
{
 char s1[RECLEN], s2[RECLEN], s3[10], s4[10], s5[10];

 /* must turn on spike analysis */
 if (__show_cancel_e)
  {
   if (__showe_onevent) strcpy(s1, " - edge event to x");
   else strcpy(s1, " - now detect to x");
  }
 else strcpy(s1, "");

 sprintf(s2, "old %s, scheduled %s, new %s%s",
  __to_gonam(s3, gp, __old_gateval), __to_gonam(s4, gp, tevp->outv),
  __to_gonam(s5, gp, __new_gateval), s1);
 /* notice spike means new and old the same */
 __gfwarn(592, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
  "%s gate %s.%s %s (edge at %s replaced by new at %s) - %s",
  gp->gmsym->synam, __msg2_idp_blditree(s1, tevp->te_idp), gp->gsym->synam,
   sptnam, __to_timstr(__xs, etim), __to_timstr(__xs2, newetim), s2);
}

/* AIV 05/26/11 - this didn't have enough elements in table - can have */
/* upto 12 values - resulting in bad memory reads */
const word32 __pow3tab[] = { 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 
 19683, 59049, 177147, 531441 };

/*
 * process a gate change event - new level has reached output
 * know thing connected to gate output is 1 bit (bit select if needed)
 * but maybe has strength
 */
extern void __process_gatechg_ev(void)
{
 struct gate_t *gp;
 struct tev_t *tevp;

 tevp = __cur_tevp;
 /* notice event here emitted in change gate outwire */
 gp = tevp->tu.tegp;
 __new_gateval = tevp->outv;
 if (__ev_tracing) emit_gev_trace(gp, tevp);
 __idp[gp->schd_tevs_ofs] = (t_midat) NULL;
 /* this handle added the 1 bit net change */
 if (tevp->gev_acc) __acc_evchg_gate_outwire(gp);
 else __change_gate_outwire(gp);
}

/*
 *
 */
extern void __process_cancel_ev(void)
{
 __num_cancel_tevents++;
}


/*
 * accelerated routine for assigning a xl type simple gate event
 *
 * if assigned to net fi>1 (maybe from run time vpi_put_value) or has
 * delay can not use accelerated event processing
 * this requires new value in new gateval global
 */
extern void __acc_evchg_gate_outwire(struct gate_t *gp)
{
 struct expr_t *xp;
 word32 uwrd, ngav, ngbv;
 struct net_t *lhsnp;
 int32 biti, gwid;
 word32 igav, igbv;

 __immed_assigns++;
 ngav = __new_gateval & 1L;
 ngbv = __new_gateval >> 1;
 xp = gp->gpins[0];
 uwrd = __idp[gp->gstate_ofs];
 if ((gwid = gp->gpnum) < 3)
  {
   /* update state with computed output value is bits 1 and 3 */
   uwrd = uwrd & ~(0xaL);
   uwrd |= ((ngav << 1) | (ngbv << 3));
  }
 else
  {
   /* mask off separated value bits to update output value in uwrd */
   uwrd = uwrd & ~(1L << (gwid - 1)) & ~(1L << (2*gwid - 1));
   /* works because ngav and ngbv exactly 1 low bit */
   uwrd |= ((ngav << (gwid - 1)) | (ngbv << (2*gwid - 1)));
  }
 __idp[gp->gstate_ofs] = uwrd;

 /* accelerated assign to pin 0 (output) */
 if (xp->optyp == ID)
  {
   lhsnp = xp->lu.sy->el.enp;
   if (lhsnp->frc_assgn_allocated)
    {
     igav = ngav; igbv = ngbv;
     if (!__correct_forced_newwireval(lhsnp, &igav, &igbv))
      goto try_trace;
    }
   /* here since avoiding value store, need to add net change el. */
   
   uwrd = ngav | (ngbv << 1);
   if (__idp[lhsnp->nva_ofs] != uwrd)
    {
     __idp[lhsnp->nva_ofs] = uwrd; 
     __lhs_changed = TRUE;
     record_nchg_(lhsnp);
    }
  }
 else
  {
   lhsnp = xp->lu.x->lu.sy->el.enp;
   biti = (int32) __contab[xp->ru.x->ru.xvi];
   /* if the 1 bit is forced nothing to do else normal assign */
   if (lhsnp->frc_assgn_allocated
    && __forced_inhibit_bitassign(lhsnp, xp->lu.x, xp->ru.x)) goto try_trace;
   /* notice this adds the net chg element if needed */
   __chg_st_bit(lhsnp, biti, ngav, ngbv);
  }
try_trace:
 if (__ev_tracing) trace_chg_gateout(gp, xp);
}

/*
 * emit gate event process trace message
 */
static void emit_gev_trace(struct gate_t *gp, struct tev_t *tevp)
{
 char s1[RECLEN], s2[RECLEN], vs1[10];

 __evtr_resume_msg();
 if (gp->gpins[0]->x_multfi) strcpy(s2, "this driver of multiple:");
 else strcpy(s2, "the fi=1 driver:");
 __tr_msg("-- %s gate %s processing store event to output, %s %s\n",
  gp->gmsym->synam, to_evtronam(s1, gp->gsym->synam, tevp->te_idp,
  (struct task_t *) NULL), s2, __to_gonam(vs1, gp, __new_gateval));
}

/*
 * add a net change record when entire net changes(usually scalar)
 *
 * add to end of next pass, netchg list elements
 * notice this needs itstk of target wire for xmr
 */
extern void __add_nchglst_el(struct net_t *np)
{
 struct nchglst_t *nchglp;

//AIV REMOVEME AIV FIXME - can on longer call this from compiler
//if (__compiled_sim && __run_state != SS_LOAD && __simtime > 0) __misc_terr(__FILE__, __LINE__);
 if (__nchgfreelst == NULL)
  nchglp = (struct nchglst_t *) __my_malloc(sizeof(struct nchglst_t));
 else
  {
   nchglp = __nchgfreelst;
   __nchgfreelst = __nchgfreelst->nchglnxt;

   /* DBG LINUX ADDME ??? */
   /* chk_nchgnlst(__nchgfreelst); */
   /* --- */
  }

 /* DBG AIV REMOVEME - 
 if (__idp == NULL) __misc_terr(__FILE__, __LINE__);
  ---- */

 /* only turn on bit if all changed, each subrange goes on by itself */
 nchglp->chgnp = np;
 nchglp->nchg_idp = __idp;
 nchglp->bi1 = -1;
 /* AIV 02/08/11 - should zero bi2 to be consistent */
 nchglp->bi2 = -1;
 nchglp->delayed_mipd = FALSE;
 nchglp->triggered = FALSE;
 nchglp->process_enterptr = __process_next_nchg_enterp;

 /* all needed change info for this time slot now records */
 /* AIV 01/08/08 - if init code for compiler do not change the value */
 /* the nchgaction is only used for dumpvars in the compiler */
 if (!__compiled_sim)
  {
   __idp[np->nchgaction_ofs] |= NCHG_ALL_CHGED;
  }

 nchglp->nchglnxt = NULL;
 /* LOOKATME - maybe add dummy list element on front to avoid comparison */
 if (__nchg_futend != NULL)
  { __nchg_futend->nchglnxt = nchglp; __nchg_futend = nchglp; }
 else __nchg_futhdr = __nchg_futend = nchglp;

 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  {
   __o_tr_msg("-- NOW %s: added net change element %s\n",
    __to_timstr(__xs2, &(__simtime)), __to_cur_evtrwnam(__xs, np, -1, -1));
  }
 --- */
}

/*
 * add a net change record select range (usually bit) changed
 *
 * add to end of next pass, netchg list elements
 * notice this needs inst. loc of target wire for xmr
 */
extern void __add_select_nchglst_el(struct net_t *np, int32 i1, int32 i2)
{
 struct nchglst_t *nchglp;

//AIV REMOVEME AIV FIXME - can on longer call this from compiler
// if (__compiled_sim && __run_state != SS_LOAD && __simtime > 0) __misc_terr(__FILE__, __LINE__);
 if (__nchgfreelst == NULL)
  nchglp = (struct nchglst_t *) __my_malloc(sizeof(struct nchglst_t));
 else
  {
   nchglp = __nchgfreelst;
   __nchgfreelst = __nchgfreelst->nchglnxt;
   /* DBG LINUX ADDME */
   /* chk_nchgnlst(__nchgfreelst); */
   /* --- */
  }

 /* only turn on bit if all changed, each subrange goes on by itself */
 nchglp->chgnp = np;
 nchglp->nchg_idp = __idp;
 nchglp->bi1 = i1;
 nchglp->bi2 = i2;
 /* AIV 04/30/07 - was not init the delay_mipd flag */
 nchglp->delayed_mipd = FALSE;
 nchglp->triggered = FALSE;
 nchglp->process_enterptr = __process_next_nchg_enterp;

 /* here since range not marked as all changed so will match ranges */

 /* link on end since good heuristic to process in change order */
 nchglp->nchglnxt = NULL;
 /* LOOKATME - maybe add dummy list element on front to avoid comparison */
 if (__nchg_futend != NULL)
  { __nchg_futend->nchglnxt = nchglp; __nchg_futend = nchglp; }
 else __nchg_futhdr = __nchg_futend = nchglp;

 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  {
   __o_tr_msg(
    "-- added net change element %s\n",
    __to_cur_evtrwnam(__xs, np, i1, i2));
  }
 --- */
}

/*
 * add a dumpvars change element
 *
 * only called first time for entire net in time slot
 * SJM 09-26-08 this is now only for dumpvars not dump ports 
 */
extern void __add_dmpv_chglst_el(struct net_t *np)
{
 int32 inum;
 struct dvchgnets_t *dvchgp;

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
 * dump an array element used with +dump_arrays and +dump_array_cells
 */
extern void __add_dmpv_chglst_el_sel(struct net_t *np, int32 ndx)
{
 int32 inum, num_els;
 struct dvchgnets_t *dvchgp;


 inum = get_inum_();
 /* if an array check the if dumpvars is on at get fixed dvchg struct */
 if (np->n_isarr)
  {
   /* AIV 09/02/10 - if array element do not set nchgaction_ofs */
   /* now using on_list bit - was only recording first change */
   num_els = np->arr_num_els;
   if (!np->n_arr_hasdvars[ndx]) return;
   dvchgp = &(np->dvns[(inum*num_els)+ndx]);
   /* if alreay on list continue */
   if (dvchgp->on_list) return;
   dvchgp->on_list = TRUE;
  }
 else 
  {
   dvchgp = &(np->dvns[inum]);
   /* indicate for this time slot inst of var already changed once */
   __idp[np->nchgaction_ofs] &= ~(NCHG_DMPVNOTCHGED);
  }

 /* link on front since order does not matter */
 dvchgp->dvchgnxt = __dv_chgnethdr;
 __dv_chgnethdr = dvchgp;
 __slotend_action |= SE_DUMPVARS;
}

/*
 * add a dumpports change element
 *
 * only called first time for entire net in time slot
 * SJM 09-26-08 this is now only for dump ports 
 */
extern void __add_dp_chglst_el(struct net_t *np)
{
 int32 inum;
 struct dp_fildesc_t *fdescp;
 struct dvchgnets_t *dpchgp;
 struct dpinstel_t *dpip;

 /* indicate for this time slot inst of var already changed once */
 __idp[np->nchgaction_ofs] &= ~(NCHG_DMPP_NOTCHGED);

 dpip = (struct dpinstel_t *) __idp[MD_DPIP];
 /* DBG remove ---*/
 if (dpip == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 fdescp = dpip->dpi_fdescp;

 /* if dump ports off for this file nothing to do */ 
 if ((fdescp->dp_slotend_action && SE_DUMPPORTSOFF) != 0) return;

 inum = get_inum_();
 dpchgp = &(np->dvns[inum]);

 /* link onto this file's dp change list */
 dpchgp->dvchgnxt = fdescp->dp_chgnethdr;
 fdescp->dp_chgnethdr = dpchgp;

 __slotend_action |= SE_DUMPPORTS;
}

/*
 * add a net to the toggle change list
 *
 * SJM 06-30-13 - for tgl off, calling this proc because called from many
 * places.  Efficiency not a problem since once toggled then will be stopped
 * by setting n peri tgl on se list to T so appears as always already
 * toggled.  Once toggled both 0->1 and 1->0 nothing more to do
 */
extern void __add_togglelst_el(struct net_t *np)
{
 int32 inum;
 struct rt_tgl_t *togp;
 struct net_toggle_t *ntgp;

 /* SJM 06-30-13 - if tgl record off nothing to do */
 /* notice only other place for tgl recording if port wrapper for this */
 /* proc in v aslib file */
 if (!__tgl_record_on) return;

 inum = get_inum_();
 /* if this instance is on the list - return */
 /* this flag may also be set for 100% coverage */
 ntgp = np->ntgp;
 /* DBG remove 
 if (ntgp == NULL) __misc_terr(__FILE__, __LINE__);
 ------ */

 if (ntgp->n_peri_tgl_on_se_list == NULL) return;
 if (ntgp->n_peri_tgl_on_se_list[inum]) return;

 ntgp->n_peri_tgl_on_se_list[inum] = TRUE;
 togp = (struct rt_tgl_t *) __idp[ntgp->toggle_ofs];
 /* link on front since order does not matter */
 togp->tognxt = __toggle_chghdr;
 __toggle_chghdr = togp;
 __slotend_action |= SE_TOGGLE;
}

//AIV TEV FIXME - REMOVEME - will not need when mos/udp gates backend lowered
//currently no args are passed to must get the gate fromt the event
extern void __cvc_change_gate_outwire(void)
{
 struct tev_t *tevp;
 struct gate_t *gp;

 tevp = __cur_tevp;
 __new_gateval = tevp->outv;
 gp = tevp->tu.tegp;
 __change_gate_outwire(gp);
}

//AIV TEV FIXME - REMOVEME - will not need when mos/udp gates backend lowered
//currently no args are passed to must get the gate fromt the event
extern void __cvc_acc_evchg_gate_outwire(void)
{
 struct tev_t *tevp;
 struct gate_t *gp;

 tevp = __cur_tevp;
 __new_gateval = tevp->outv;
 gp = tevp->tu.tegp;
 __acc_evchg_gate_outwire(gp);
 __idp[gp->schd_tevs_ofs] = (t_midat) NULL;
}

/*
 * assign gate output to driven wire
 * this assumes __new_gateval previously set
 * works for both 8 bit strength and 2 bit non strength values
 *
 * notice simultaneously when changing wire (or scheduling if wire has delay)
 * must store gate state output - needed since when evaluating driver for
 * gate with delay need previous until actual store
 */
extern void __change_gate_outwire(struct gate_t *gp)
{
 int32 bi;
 int32 schd_wire, nins, srep;
 int32 inum;
 word32 *wp;
 word32 av, bv;
 byte sb2, *sbp;
 word32 uwrd;
 struct expr_t *xp;
 struct xstk_t *xsp;
 struct mod_t *mdp;

 __immed_assigns++;
 xp = gp->gpins[0];
 switch ((byte) gp->g_class) {
  case GC_LOGIC:
   /* SJM 02/07/01 - remove st gstate out routine since only for logic */
   /* this removes inner loop case stmt */

   nins = gp->gpnum - 1;
   if (nins > 15) srep = SR_VEC; else srep = SR_PVEC;
   /* FIXME - why are these not wrd? */
   av = ((word32) __new_gateval) & 1;
   bv = ((word32) __new_gateval) >> 1;

   /* must store new gate value into state here - value does not have stren */
   /* AIV 08/25/10 - this needs to do this for the wide case as well */
   if (__compiled_sim)
    {
     __idp[gp->gate_out_ofs] = __new_gateval;
     /* AIV 12/27/07 - no need for the compiler call gate_st_bit to pack */
     /* output value here */
    }
   else gate_st_bit(&(__idp[gp->gstate_ofs]), nins + 1, nins, srep, av, bv);
   break;
  case GC_UDP:
   /* new gateval for udp does not have strength - maybe added in store */
   /* tricky part for wide udp's - must update running signature if present */
   __cur_udp = gp->gmsym->el.eudpp;
   nins = __cur_udp->numins;
   bi = 2*nins;
   /* comb means no state - edge always has state */
   if (__cur_udp->u_wide)
    {
     wp = &(__idp[gp->gstate_ofs]);
     /* update running 2nd state signature word32 */
     if (__cur_udp->utyp != U_COMB)
      {
       /* need to access old gate value (out about to change) */
       /* since for event schedule will not be stored */
       /* during initialize this will be meaningless 0 */
       __old_gateval = (wp[0] >> (2*nins)) & 3L;

       /* correct running index of output since part of state if not comb. */
       /* num ins is index of state */
       /* subtract off old contribution of state output */
       wp[1] -= ((__old_gateval == 3) ? 2 : __old_gateval)*__pow3tab[nins];
       /* add in new contribution of state output */
       wp[1] += ((__new_gateval == 3) ? 2 : __new_gateval)*__pow3tab[nins];
      }
     /* update first value word32 */
     wp[0] &= ~(3L << bi);
     wp[0] |= (__new_gateval << bi);
    }
   /* do the the gate state output store */
   /* udp state stored as nins 2 bit vals + out/state 2 bits */
   else
    {
     wp = &(__idp[gp->gstate_ofs]);
     /* -- RELASE remove
     if (__debug_flg && __ev_tracing)
      __tr_msg("-- st udp out old %x\n", *wp);
     -- */
     *wp &= ~(3 << bi);
     *wp |= (__new_gateval << bi);
     /* -- RELEASE remove ---
     if (__debug_flg && __ev_tracing)
      __tr_msg(" new %x\n", *wp);
     -- */
    }
   break;
  case GC_BUFIF:
   /* store new gate val into bufif state - here must merge in stren */
   wp = &(__idp[gp->gstate_ofs]);
   wp[0] &= ~(0xff << 4);
   wp[0] |= ((hword) (__new_gateval << 4));
   goto do_hasstren_assign;
  case GC_MOS:
   /* store new gate val into mos state */
   wp = &(__idp[gp->gstate_ofs]);
   wp[0] &= ~(0xff << 16);
   wp[0] |= (__new_gateval << 16);
   goto do_hasstren_assign;
  case GC_CMOS:
   /* store new gate val into cmos state */
   wp = &(__idp[gp->gstate_ofs]);
   wp[0] &= ~(0xff << 24);
   wp[0] |= (__new_gateval << 24);

do_hasstren_assign:
   /* then assign - here strength variable and new gateval has strength */
   if (xp->x_multfi) __mdr_assign_or_sched(xp);
   else
    {
     if (xp->lhsx_ndel && !__wire_init) schd_wire = TRUE;
     else schd_wire = FALSE;

     /* 07/08/00 - if gate (always 1 bit) drives wider vec must initialize */
     /* other bits to z since only has 1 driver */
     push_xstk_(xsp, 4*xp->szu.xclen);
     sbp = (byte *) xsp->ap;
     set_byteval_(sbp, xp->szu.xclen, ST_HIZ);
     /* set the low bit */
     sbp[0] = (byte) __new_gateval;
     __exec_conta_assign(xp, (word32 *) sbp, (word32 *) NULL, schd_wire);
     __pop_xstk();
    }
   goto done;
  case GC_TRANIF:
   /* out wire here is conducting state from 3rd input */
   /* SJM 12/13/00 - serious malloc bug was using bit ofset */
   /* 2 bits give conducting state */
   if (__new_gateval == 2) __new_gateval = 3;
//AIV FIXME?????????
   wp = &(__idp[gp->gstate_ofs]);
   wp[0] = __new_gateval;
   if (__ev_tracing)
    {
     __tr_msg("-- relaxing %s in switch channel\n",
      __gstate_tostr(__xs, gp, TRUE));
    }
   /* tranif enable changed must evaluate channel */
   /* LOOKATME think this only needs to be called if from/to 0, x same as 1 */
   /* SJM 04/11/00 - put back so immediately perturb both terminal vertices */
   __immed_eval_trifchan(gp);
   return;
  /* tran can never get here */
  default: __case_terr(__FILE__, __LINE__);
 }

 /* store gate or udp where value maybe needs constant strength added */
 /* gate state now updated, must assign to wire or schedule assign */
 if (xp->x_multfi) __mdr_assign_or_sched(xp);
 else
  {
   /* even though decl. no need for z extend since 1 bit max. wide */
   if (xp->lhsx_ndel && !__wire_init) schd_wire = TRUE;
   else schd_wire = FALSE;
   /* notice lhs cannot be concat here and know source and dest 1 bit */
   if (xp->x_stren)
    {
     /* here any strength constant */
     /* notice always need to add strength logic gate cannot drive z */
     if (__new_gateval == 2) sb2 = 2;
     else
      {
       /* notice tran that uses g st val for mark never goes here */
       uwrd = __new_gateval | (gp->g_stval << 2);
       uwrd = (word32) __stren_map_tab[uwrd];
       sb2 = (byte) uwrd;
      }
     /* 07/08/00 - if gate (always 1 bit) drives wider vec must initialize */
     /* other bits to z since only has 1 driver */
     push_xstk_(xsp, 4*xp->szu.xclen);
     sbp = (byte *) xsp->ap;
     set_byteval_(sbp, xp->szu.xclen, ST_HIZ);
     /* set the low bit */
     sbp[0] = sb2;
     __exec_conta_assign(xp, (word32 *) sbp, (word32 *) NULL, schd_wire);
     __pop_xstk();
    }
   else
    {
     av = __new_gateval & 1L;
     bv = __new_gateval >> 1;
     /* assign needed although only bit select or 1 bit wire, can be xmr */
     __exec_conta_assign(xp, &av, &bv, schd_wire);
    }
  }

done:
 /* SJM 11/27/00 - know out changed, state has been updated and strength */
 /* competition done to set new wire value - this call back monitors the */
 /* gate state so it does ont matter if after wire changed */
 if (__have_vpi_gateout_cbs)
  {
   int32 gi; 
   struct tev_t *tevp;

   mdp = get_inst_mod_();
   gi = gp - mdp->mgates;
   inum = get_inum_();
   if (mdp->mgateout_cbs != NULL && mdp->mgateout_cbs[gi] != NULL
    && (tevp = (struct tev_t *) mdp->mgateout_cbs[gi][inum]) != NULL)
    {
     __exec_vpi_gateoutcbs(tevp);
    }
  }

 if (__ev_tracing) trace_chg_gateout(gp, xp);
}

/*
 * trace message after change gate outwire
 */
static void trace_chg_gateout(struct gate_t *gp, struct expr_t *xp)
{
 char s1[RECLEN], s2[RECLEN], vs1[10], vs2[10];

 if (xp->lhsx_ndel && !__wire_init) strcpy(vs1, "schedule");
 else strcpy(vs1, "assign");
 if (gp->g_class == GC_UDP) strcpy(vs2, "udp"); else strcpy(vs2, "gate");
 __tr_msg("-- %s %s event output %s, %s to %s\n", vs1,
  __gstate_tostr(__xs, gp, TRUE), vs2, __to_gassign_str(s1, xp),
  __msgexpr_tostr(s2, xp));
}

/* SJM 02/07/01 - removed st gstate out routine - moved only used logic */

/*
 * store into coded wp of length blen at biti for current instance
 * that is stored according to srep format from low 2 bits of rgap
 * notice bits are separated into a and b parts in gate representation
 *
 * this differs from lhs bit select in accessing value for current instance
 * and adjusting place to select from according to storage representation
 * cannot be used to access array or strength value and called
 * with know good index (not -1)
 * this is for logic gates only
 *
 * SJM 08-03-10 - SV - since always wire can never be 2 state
 */
static void gate_st_bit(word32 *wp, int32 blen, int32 biti, int32 srep,
 word32 av, word32 bv)
{
 word32 uwrd, ouwrd;
 int32 wlen;

 /* this is same as full value store - biti 0 or will not get here */
 switch ((byte) srep) {
  case SR_SCAL: st_scalval_(wp, av, bv); return;
  case SR_VEC:
   wlen = wlen_(blen);
   /* rap is base of vector for current inst */
   __lhsbsel(wp, biti, av);
   __lhsbsel(&(wp[wlen]), biti, bv);
   return;
  case SR_PVEC:
   ouwrd = wp[0];
   uwrd = ouwrd & ~(1L << biti) & ~(ouwrd & (1L << (blen + biti)));
   uwrd |= ((av & 1L) << biti) | ((bv & 1L) << (blen + biti));
   if (uwrd != ouwrd)
    {
     wp[0] = uwrd;
    }
   return;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * change input i part of gstate vector for mos style gate
 * strens passed thru so must load with stren even if driver no stren
 * returns false if new input value is same as old
 * this requires correct cur. itp
 */
static int32 chg_mos_instate(struct gate_t *gp, word32 i)
{
 word32 uwrd;
 struct expr_t *ndp;
 byte *sbp;
 struct xstk_t *xsp;

 uwrd = __idp[gp->gstate_ofs];
 /* split because change scheduled or assigned if only strength changed */
 if (i == 1)
  {
   ndp = gp->gpins[1];
   /* if port a reg cannot have strength, this will add strong */
   xsp = __ndst_eval_xpr(ndp);
   sbp = (byte *) xsp->ap;
   __new_inputval = sbp[0];
   __pop_xstk();
   __old_inputval = uwrd & 0xffL;
   if (__new_inputval == __old_inputval) return(FALSE);
   uwrd &= ~0xffL;
   uwrd |= __new_inputval;
  }
 else
  {
   /* control input should not have strength but if does ignored */
   xsp = __eval_xpr(gp->gpins[2]);
   __new_inputval = (xsp->ap[0] & 1L) | ((xsp->bp[0] & 1L) << 1);
   __pop_xstk();
   __old_inputval = (uwrd >> 8) & 3L;
   if (__new_inputval == __old_inputval) return(FALSE);
   uwrd &= ~(3L << 8);
   uwrd |= (__new_inputval << 8);
  }
 __idp[gp->gstate_ofs] = uwrd;
 return(TRUE);
}

/*
 * change input i part of gstate vector for cmos 2 ctrl input style gate
 * strens passed thru so must load with stren even if driver no stren
 * returns false if new input value is same as old
 * this requires correct cur. itp
 *
 * format is 3 8 bit values (0th input data, 1 nmos in, 2 pmos in, 3 output)
 * but only 2 bits of 1st and 2nd control inputs used
 * notice input starts at 1 because output is pos. 0
 */
static int32 chg_cmos_instate(struct gate_t *gp, word32 i)
{
 word32 uwrd;
 byte *sbp;
 struct expr_t *ndp;
 struct xstk_t *xsp;

 uwrd = __idp[gp->gstate_ofs];
 /* split because change scheduled or assigned if only strength changed */
 if (i == 1)
  {
   ndp = gp->gpins[1];
   xsp = __ndst_eval_xpr(ndp);
   sbp = (byte *) xsp->ap;
   __new_inputval = sbp[0];
   __pop_xstk();
   __old_inputval = uwrd & 0xffL;
   if (__new_inputval == __old_inputval) return(FALSE);
   uwrd &= ~0xffL;
   uwrd |= __new_inputval;
  }
 else
  {
   /* control inputs should not have strength but if does removed */
   xsp = __eval_xpr(gp->gpins[i]);
   __new_inputval = (xsp->ap[0] & 1L) | ((xsp->bp[0] & 1L) << 1);
   __pop_xstk();
   if (i == 2)
    {
     /* n ctrl bits 15-8 */
     __old_inputval = (uwrd >> 8) & 3L;
     if (__new_inputval == __old_inputval) return(FALSE);
     uwrd &= ~(3L << 8);
     uwrd |= (__new_inputval << 8);
    }
   else
    {
     /* p ctrl bits 23-16 */
     __old_inputval = (uwrd >> 16) & 3L;
     if (__new_inputval == __old_inputval) return(FALSE);
     uwrd &= ~(3L << 16);
     uwrd |= (__new_inputval << 16);
    }
  }
 __idp[gp->gstate_ofs] = uwrd;
 return(TRUE);
}

/*
 * TRANIF EVALUATION ROUTINES
 */

/*
 * evaluate tranif when third enable port changes
 */
extern void __eval_tranif_ld(struct gate_t *gp, int32 i)
{
 int32 out_chg;

 /* DBG remove */
 if (i != 2) __arg_terr(__FILE__, __LINE__);
 /* --- */
 /* third in chged - schedule (if needed) conducting state chg */
 /* must always go through scheduling code for spike analysis */
 eval_tranif_onoff(gp);
 /* out_chg T if conducting state changed */
 out_chg = (__new_gateval != __old_gateval);
 /* must evaluate both sides */
 if (gp->g_delrep == DT_NONE)
  { if (out_chg) __change_gate_outwire(gp); return; }
 prop_gatechg(gp, out_chg, FALSE);
}

/*
 * handle on (conducting) state checking and change for input state
 *
 * here for delay case gate value is pending conducting state (1 on, 0 off)
 * actual current conducting state is same as stored output wire value
 *
 * stored conducting state corrected for tranif1 and tranif0 (value
 * computed then reversed depnding on if1 or if0)
 */
static void eval_tranif_onoff(struct gate_t *gp)
{
 int32 bi;
 int32 gateid, inum;
 word32 cval;
 struct xstk_t *xsp;

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

/*
 * CONTINOUS ASSIGN EVENT ROUTINES
 */

/*
 * load of changed wire is >1 bit conta rhs needs to be evaluated and
 * if delay scheduled else assigned and lhs added to net changes
 *
 * current itree element never changes in here
 * for now evaluating and scheduling - no optimization
 *
 * know rhs real illegal here since cannot assign to wire
 *
 * all computations done with non strength values since strength
 * added from conta type if needed when assigning to strength wire
 *
 * no pulse/glitch analysis here just inertial algorithm because
 * continuous assigns do not correspond to silicon rather modeling convention
 */
extern void __eval_conta_rhs_ld(struct net_pin_t *npp)
{
 int32 cv, cv2, schd_wire;
 int32 lhswlen, orhslen, lhslen;
 byte *sbp;
 word64 cadel, schtim;
 struct xstk_t *xsp, *xsp2;
 struct conta_t *cap;
 struct tev_t *tevp;
 struct expr_t *lhsxp;
 struct xstk_t *xsp3;
 struct conta_t *mast_cap;

 if (__ev_tracing) { evtr_eval_conta_rhs_ld(npp); return; }

 /* SJM 09/18/02 - no separate per bit NP type, just check for pb sim on */
 mast_cap = npp->elnpp.ecap;
 /* get pattern never decomposd per bit */
 if (mast_cap->lhsx->getpatlhs) { __process_getpat(mast_cap); return; }

 if (mast_cap->ca_pb_sim) cap = &(mast_cap->pbcau.pbcaps[npp->pbi]);
 else cap = mast_cap;
 /* know getpat never has delay */
 lhsxp = cap->lhsx;
 lhslen = cap->lhsx->szu.xclen;
 /* this pushes rhs new maybe to be scheduled value onto expression stack */
 xsp = __eval_xpr(cap->rhsx);

 /* here rhs must be z with fixed conta strength merged in if present */
 if (xsp->xslen != lhslen)
  {
   orhslen = xsp->xslen;

   /* SJM 09/29/03 - change to handle sign extension and separate types */
   if (xsp->xslen > lhslen) __narrow_sizchg(xsp, lhslen);
   else if (xsp->xslen < lhslen)
    {
     if (cap->rhsx->has_sign) __sgn_xtnd_widen(xsp, lhslen);
     else __sizchg_widen(xsp, lhslen);
    }

   /* SJM 07/09/03 - now understand XL algorithm to mimic - for conta */
   /* semantics requires rhs non stren eval with 0 widening then add stren */
   /* SJM 05/10/04 init x widending not related to new signed widening */
   if (__wire_init) __fix_widened_toxs(xsp, orhslen);
  }

 /* case 1: no delay assign */
 /* since 1 bit handled as gate, not checking for no change - just assign */
 /* also rhs eval. is driver (i.e. not stored) */
 if (mast_cap->ca_delrep == DT_NONE)
  {
   __immed_assigns++;
   /* in here deals with saved driver - if any lhs bits fi>1 all must be */
   /* SJM 09/28/02 - know if master fi>1 all per bit will be */
   if (lhsxp->x_multfi)
    {
     /* this packs if possible */
     __st_idp_val(&(__idp[cap->ca_drv_ofs]), lhslen, xsp->ap, xsp->bp);
     __mdr_assign_or_sched(lhsxp);
    }
   else
    {
     /* here do not need drv and do not need schd driver, rhs is driver */
     if (lhsxp->lhsx_ndel && !__wire_init) schd_wire = TRUE;
     else schd_wire = FALSE;
     if (lhsxp->x_stren)
      {
       /* convert to strength bytes forms - add in driven from ca */
       push_xstk_(xsp2, 4*lhslen);
       sbp = (byte *) xsp2->ap;
       __st_standval(sbp, xsp, cap->ca_stval);
       if (lhsxp->optyp == LCB) __stren_exec_ca_concat(lhsxp, sbp, schd_wire);
       else __exec_conta_assign(lhsxp, xsp2->ap, xsp2->bp, schd_wire);
       __pop_xstk();
      }
     else
      {
       if (lhsxp->optyp == LCB)
        __exec_ca_concat(lhsxp, xsp->ap, xsp->bp, schd_wire);
       else __exec_conta_assign(lhsxp, xsp->ap, xsp->bp, schd_wire);
      }
    }
   __pop_xstk();
   return;
  }

 /* case 2: has delay */
 lhswlen = wlen_(lhslen);
 /* xsp2 is currently driving (old) value and must exist */
 /* DBG remove ---
 if (cap->ca_drv_ofs == 0) __arg_terr(__FILE__, __LINE__);
 -- */

 push_xstk_(xsp2, lhslen);
 __ld_val(xsp2->ap, xsp2->bp, &(__idp[cap->ca_drv_ofs]), lhslen);
 tevp = (struct tev_t *) __idp[cap->caschd_tevs_ofs];
 cv = memcmp(xsp2->ap, xsp->ap, 2*lhswlen*WRDBYTES);
 __pop_xstk();
 /* case 2a: short circuit case no event and new and old same */
 if (tevp == NULL && cv == 0) { __pop_xstk(); return; }

 /* compute delay - know at least one bit changed */
 __new_gateval = 1L;
 /* if 4v delay, must set new_gateval for use in delay selection */
 /* notice modified LRM if left hand side all x's, minimum delay is used */
 if (mast_cap->ca_4vdel)
  {
   if (mast_cap->ca_pb_sim)
    {
     struct xstk_t *mast_xsp;

     /* if 4v delay, must always eval entire conta rhs to select delay */
     mast_xsp = __eval_xpr(mast_cap->rhsx);
     orhslen = mast_xsp->xslen;
     if (vval_is0_(mast_xsp->ap, orhslen))
      {
       if (vval_is0_(mast_xsp->bp, orhslen)) __new_gateval = 0;
       else
        {
         if (__vval_is1(mast_xsp->bp, orhslen)) __new_gateval = 2;
        }
      }
     else if (__vval_is1(mast_xsp->ap, orhslen)
      && __vval_is1(mast_xsp->bp, orhslen)) { __new_gateval = 3; }
     __pop_xstk();
    }
   else
    {
     if (vval_is0_(xsp->ap, lhslen))
      {
       if (vval_is0_(xsp->bp, lhslen)) __new_gateval = 0;
       else if (__vval_is1(xsp->bp, lhslen)) __new_gateval = 2;
      }
     else if (__vval_is1(xsp->ap, lhslen) && __vval_is1(xsp->bp, lhslen))
      { __new_gateval = 3; }
    }
  }
 /* this may use new gateval global to select delay */
 /* SJM 09/28/02 - delay same for all so stored in master */
 cadel = __get_del(mast_cap->ca_du, mast_cap->ca_delrep);
 schtim = __simtime + cadel;

 /* case 2b: no pending event and different */
 if (tevp == NULL)
  {
   /* case 1b: new value to schedule */
   /* know xsp is lhs width */
   __schedule_1caev(cap, cadel, schtim, xsp->ap);
   __pop_xstk();
   return;
  }

 push_xstk_(xsp3, lhslen);
 __ld_val(xsp3->ap, xsp3->bp, &(__idp[cap->schd_drv_ofs]), lhslen);
 /* compare currently scheduled to to new to be scheduled */
 /* if same do nothing since already schedule to right value and know */
 /* value will be later */
 cv2 = memcmp(xsp3->ap, xsp->ap, 2*lhswlen*WRDBYTES);
 __pop_xstk();
 if (cv2 == 0) { __pop_xstk(); return; }

 /* case 2c: pending event - no spike analysis for >1 bit contas */
 /* case 2c-1 - new and old the same - cancel */
 if (cv == 0)
  {
   tevp->enterptr = __process_cancel_ev_enterp;
   __inertial_cancels++;
   __idp[cap->caschd_tevs_ofs] = (t_midat) NULL;
  }
 /* case 2c-2 - new and old differ - reschedule latest input change */
 /* notice even for modeling anomally where latest input change leads to */
 /* earlier output event, use latest input change */
 else __reschedule_1caev(tevp, cadel, schtim, xsp->ap);

 __pop_xstk();
}

/*
 * event tracing version of eval conta rhs
 */
static void evtr_eval_conta_rhs_ld(struct net_pin_t *npp)
{
 int32 cv, schd_wire;
 int32 lhswlen, orhslen, lhslen;
 byte *sbp;
 word64 cadel, schtim;
 struct tev_t *tevp;
 struct conta_t *cap, *mast_cap;
 struct xstk_t *xsp, *xsp2, *xsp3;
 struct expr_t *lhsxp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN], s5[RECLEN];

 /* SJM 09/18/02 - no separate per bit NP type, just check for pb tab */
 mast_cap = npp->elnpp.ecap;
 /* know getpat never has delay and never decomposed per bit */
 if (mast_cap->lhsx->getpatlhs) { __process_getpat(mast_cap); return; }

 if (mast_cap->ca_pb_sim) cap = &(mast_cap->pbcau.pbcaps[npp->pbi]);
 else cap = mast_cap;
 lhsxp = cap->lhsx;

 if (mast_cap->ca_pb_sim)
  {
   __tr_msg("-- %s RHS bit %d changed:\n",
    to_cur_evtrcanam(__xs2, mast_cap), npp->pbi);
  }
 else
  {
   __tr_msg("-- %s RHS changed:\n", to_cur_evtrcanam(__xs2, mast_cap));
  }
 lhslen = cap->lhsx->szu.xclen;
 xsp = __eval_xpr(cap->rhsx);

 /* here rhs must be z with fixed conta strength merged in if present */
 if (xsp->xslen != lhslen)
  {
   orhslen = xsp->xslen;

   /* SJM 09/29/03 - change to handle sign extension and separate types */
   if (xsp->xslen > lhslen) __narrow_sizchg(xsp, lhslen);
   else if (xsp->xslen < lhslen)
    {
     if (cap->rhsx->has_sign) __sgn_xtnd_widen(xsp, lhslen);
     else __sizchg_widen(xsp, lhslen);
    }
   /* SJM 07/09/03 - now understand XL algorithm to mimic - if rhs is reg */
   /* or reg type expr, must widen with 0's (automatic) if net with zs */
   /* wire init is special case */
   /* SJM 05/10/04 init x widending not related to new signed widening */
   if (__wire_init) __fix_widened_toxs(xsp, orhslen);
  }

 /* case 1: no delay assign */
 /* since 1 bit handled as gate, not checking for no change - just assign */
 if (mast_cap->ca_delrep == DT_NONE)
  {
   __immed_assigns++;
   __tr_msg(" NODEL <NV=%s>\n",
    __regab_tostr(s1, xsp->ap, xsp->bp, lhslen, BHEX, FALSE));
   /* in here deals with saved driver */

   /* SJM 09/28/0-2 - know if master fi>1 all per bit will be */
   if (lhsxp->x_multfi)
    {
     __st_idp_val(&(__idp[cap->ca_drv_ofs]), lhslen, xsp->ap, xsp->bp);
     __mdr_assign_or_sched(lhsxp);
    }
   else
    {
     /* here do not need drv and do not need schd driver, rhs is driver */
     if (lhsxp->lhsx_ndel && !__wire_init) schd_wire = TRUE;
     else schd_wire = FALSE;
     if (lhsxp->x_stren)
      {
       /* convert to strength bytes forms - add in driven from ca */
       push_xstk_(xsp2, 4*lhslen);
       sbp = (byte *) xsp2->ap;
       /* stren val also in PB */
       __st_standval(sbp, xsp, cap->ca_stval);
       if (lhsxp->optyp == LCB) __stren_exec_ca_concat(lhsxp, sbp, schd_wire);
       /* SJM 03/30/99 - was storing value without strength added */
       else __exec_conta_assign(lhsxp, xsp2->ap, xsp2->bp, schd_wire);
       __pop_xstk();
      }
     else
      {
       if (lhsxp->optyp == LCB)
        __exec_ca_concat(lhsxp, xsp->ap, xsp->bp, schd_wire);
       else __exec_conta_assign(lhsxp, xsp->ap, xsp->bp, schd_wire);
      }
    }
   __pop_xstk();
   return;
  }

 /* case 2: has delay */
 /* this is current (old) driving value */
 lhswlen = wlen_(lhslen);
 push_xstk_(xsp2, lhslen);
 __ld_val(xsp2->ap, xsp2->bp, &(__idp[cap->ca_drv_ofs]), lhslen);
 tevp = (struct tev_t *) __idp[cap->caschd_tevs_ofs];
 cv = memcmp(xsp2->ap, xsp->ap, 2*lhswlen*WRDBYTES);
 /* case 2a: short circuit case no event and new and old same */
 if (tevp == NULL && cv == 0)
  {
   __tr_msg(" DEL, NOCHG <OV=%s>\n",
    __regab_tostr(s1, xsp2->ap, xsp2->bp, lhslen, BHEX, FALSE));
   __pop_xstk();
   __pop_xstk();
   return;
  }

 /* compute delay */
 __new_gateval = 1L;
 /* if 4v delay, must set new gateval for use in delay selection */
 /* SJM 09/28/02 - now match non evtr 4v case */
 if (mast_cap->ca_4vdel)
  {
   if (mast_cap->ca_pb_sim)
    {
     struct xstk_t *mast_xsp;

     /* if 4v delay, must always eval entire conta rhs to select delay */
     mast_xsp = __eval_xpr(mast_cap->rhsx);
     if (vval_is0_(mast_xsp->ap, lhslen))
      {
       if (vval_is0_(mast_xsp->bp, lhslen)) __new_gateval = 0L;
       else if (__vval_is1(mast_xsp->bp, lhslen)) __new_gateval = 2L;
      }
     else if (__vval_is1(mast_xsp->ap, lhslen)
      && __vval_is1(mast_xsp->bp, lhslen)) { __new_gateval = 3L; }
     __pop_xstk();
    }
   else
    {
     if (vval_is0_(xsp->ap, lhslen))
      {
       if (vval_is0_(xsp->bp, lhslen)) __new_gateval = 0L;
       else if (__vval_is1(xsp->bp, lhslen)) __new_gateval = 2L;
      }
     else if (__vval_is1(xsp->ap, lhslen) && __vval_is1(xsp->bp, lhslen))
      { __new_gateval = 3L; }
    }
  }
 /* this may use new gateval global to select delay */
 cadel = __get_del(mast_cap->ca_du, mast_cap->ca_delrep);
 schtim = __simtime + cadel;

 /* case 2b: no pending event and different */
 if (tevp == NULL)
  {
   /* case 1b: new value to schedule */
   __tr_msg(" DEL, SCHD AT %s <OV=%s, NSV=%s>\n",
    __to_timstr(s1, &schtim),
    __regab_tostr(s2, xsp2->ap, xsp2->bp, lhslen, BHEX, FALSE),
    __regab_tostr(s3, xsp->ap, xsp->bp, lhslen, BHEX, FALSE));

   /* know xsp is lhs width */
   __schedule_1caev(cap, cadel, schtim, xsp->ap);
   __pop_xstk();
   __pop_xstk();
   return;
  }

 /* case 2c: pending event - no spike analysis for >1 bit contas */
 push_xstk_(xsp3, lhslen);
 __ld_val(xsp3->ap, xsp3->bp, &(__idp[cap->schd_drv_ofs]), lhslen);

 /* compare currently scheduled to to new to be scheduled */
 /* if same do nothing since already schedule to right value and know */
 /* value will be later */
 if (memcmp(xsp3->ap, xsp->ap, 2*lhswlen*WRDBYTES) == 0)
  {
   __tr_msg(
    " DEL, MODEL ANOMALLY IGNORE SCHED TO SAME <OSV=NSV=%s> OLD AT %s NEW %s\n",
    __regab_tostr(s1, xsp->ap, xsp->bp, lhslen, BHEX, FALSE),
    __to_timstr(s2, &(tevp->etime)), __to_timstr(s3, &schtim));
   goto done;
  }

 /* case 2c-1-a - new and old the same - remove inertial pulse */
 if (cv == 0)
  {
   /* cancel pending and return */
   __tr_msg(" DEL, PEND, SAME <OV=NSV=%s, OSV=%s AT %s INERTIAL CANCEL>\n",
    __regab_tostr(s1, xsp->ap, xsp->bp, lhslen, BHEX, FALSE),
    __regab_tostr(s2, xsp3->ap, xsp3->bp, lhslen, BHEX, FALSE),
    __to_timstr(s3, &(tevp->etime)));
   /* cancel */
   tevp->enterptr = __process_cancel_ev_enterp;
   __inertial_cancels++;
   __idp[cap->caschd_tevs_ofs] = (t_midat) NULL;
   goto done;
  }
 /* case 2c-1-b - new and old differ */
 __tr_msg(
  " DEL, PEND, RESCHD <OV=%s, OSV=%s AT %s, NSV=%s AT %s REPLACES>\n",
  __regab_tostr(s1, xsp2->ap, xsp2->bp, lhslen, BHEX, FALSE),
  __regab_tostr(s2, xsp3->ap, xsp3->bp, lhslen, BHEX, FALSE),
  __to_timstr(s5, &(tevp->etime)),
  __regab_tostr(s3, xsp->ap, xsp->bp, lhslen, BHEX, FALSE),
  __to_timstr(s4, &schtim));

 /* reschedule by replacing (if same time) or cancelling */
 __reschedule_1caev(tevp, cadel, schtim, xsp->ap);

done:
 __pop_xstk();
 __pop_xstk();
 __pop_xstk();
}

/*
 * emit an continous assign locator
 * must make sure s at least IDLEN + MSG TRUNC LEN
 */
extern char *__to_evtrcanam(char *s, struct conta_t *cap, t_midat *te_idp)
{
 char s1[RECLEN], s2[RECLEN];

 sprintf(s, "continuous assign in %s %s", __msg2_idp_blditree(s1, te_idp),
  __bld_lineloc(s2, cap->casym->syfnam_ind, cap->casym->sylin_cnt));
 return(s);
}

/*
 * emit an continous assign locator
 * must make sure s at least IDLEN + MSG TRUNC LEN
 */
static char *to_cur_evtrcanam(char *s, struct conta_t *cap)
{
 struct itree_t *itp;
 char s1[RECLEN], s2[RECLEN];

 itp = get_itp_();
 sprintf(s, "continuous assign in %s %s", __msg2_blditree(s1, itp),
  __bld_lineloc(s2, cap->casym->syfnam_ind, cap->casym->sylin_cnt));
 return(s);
}

/*
 * schedule 1 conta event
 * know rhs wp width is exactly lhs width
 */
extern void __schedule_1caev(struct conta_t *cap, word64 cadel, word64 schtim,
 word32 *rhs_wp)
{
 int32 lhslen;
 struct tev_t *tevp;

 alloc_cur_tev_(tevp, __process_conta_ev, schtim);
 if (cadel == 0ULL)
  {
   /* this is #0, but must still build tev */
   if (__p0_te_hdrp == NULL) __p0_te_hdrp = __p0_te_endp = tevp;
   else { __p0_te_endp->tenxtp = tevp; __p0_te_endp = tevp; }
  }
 else __insert_event(tevp);

 __idp[cap->caschd_tevs_ofs] = (t_midat) tevp;
 tevp->tu.tecap = cap;
 lhslen = cap->lhsx->szu.xclen;
 __st_idp_val(&(__idp[cap->schd_drv_ofs]), lhslen, rhs_wp, 
  &(rhs_wp[wlen_(lhslen)]));
}

/*
 * take ca event and new value and either update if time same or cancel and
 * create new event if later
 *
 * know rhs wp width is exactly lhs width
 */
extern void __reschedule_1caev(struct tev_t *tevp, word64 cadel, word64 newtim,
 word32 *rhs_wp)
{
 int32 lhslen;
 struct conta_t *cap;

 /* if del == 0 (pnd0), will always be same time reschedule */
 cap = tevp->tu.tecap;
 if (cadel == 0ULL)
  {
   /* new scheduled value replaces old */
   __newval_rescheds++;
   /* know length must be the same */
   lhslen = cap->lhsx->szu.xclen;
   __st_idp_val(&(__idp[cap->schd_drv_ofs]), lhslen, rhs_wp,
    &(rhs_wp[wlen_(lhslen)]));
   return;
  }
 /* cancel */
 tevp->enterptr = __process_cancel_ev_enterp;
 __inertial_cancels++;
 /* this will change the scheduled field so no need to set to nil */
 __schedule_1caev(cap, cadel, newtim, rhs_wp);
}

/*
 * process a continous assign actual assignment (end of delay ev triggered)
 * 1 bit continuous assign are processed as gates per Verilog semantics
 * and not seen here
 *
 * will only get here if delay >= 0 (maybe #0)
 * SJM 09/28/02 - for rhs concat decomposed into PB, event ptr is PB
 */
extern void __process_conta_ev(void)
{
 int32 schd_wire, lhslen;
 struct xstk_t *xsp, *xsp2;
 struct conta_t *cap;
 byte *sbp;
 struct expr_t *lhsxp;

 cap = __cur_tevp->tu.tecap;
 lhsxp = cap->lhsx;
 lhslen = cap->lhsx->szu.xclen;

 push_xstk_(xsp, lhslen);
 __ld_val(xsp->ap, xsp->bp, &(__idp[cap->schd_drv_ofs]), lhslen);
 if (__ev_tracing)
  {
   struct conta_t *cap2;

   __evtr_resume_msg();
   if (cap->ca_pb_el) cap2 = cap->pbcau.mast_cap; else cap2 = cap;
   to_cur_evtrcanam(__xs, cap2);
   __regab_tostr(__xs2, xsp->ap, xsp->bp, lhslen, BHEX, FALSE);
   if (lhsxp->x_multfi)
    __tr_msg("-- %s event this driver of multiple:\n   %s\n", __xs, __xs2);
   else __tr_msg("-- %s event the fi=1 driver: %s\n", __xs, __xs2);
  }
 /* move value from scheduled to driver wp - never store constant strength */
 /* has delay so will always have ca drv wp */
 /* store scheduled value into driving value */
 __st_idp_val(&(__idp[cap->ca_drv_ofs]), lhslen, xsp->ap, xsp->bp);

 if (lhsxp->x_multfi) __mdr_assign_or_sched(lhsxp);
 else
  {
   /* here do not need drv and do not need schd driver, rhs is driver */
   if (lhsxp->lhsx_ndel && !__wire_init) schd_wire = TRUE;
   else schd_wire = FALSE;

   if (lhsxp->x_stren)
    {
     /* convert to strength bytes forms - add in driven from ca */
     /* know all widths exactly  required lhs width */
     push_xstk_(xsp2, 4*lhslen);
     sbp = (byte *) xsp2->ap;
     /* notice stren value also in each per bit, just not delay */
     __st_standval(sbp, xsp, cap->ca_stval);
     if (lhsxp->optyp == LCB) __stren_exec_ca_concat(lhsxp, sbp, schd_wire);
     else __exec_conta_assign(lhsxp, xsp2->ap, xsp2->bp, schd_wire);
     __pop_xstk();
    }
   else
    {
     if (lhsxp->optyp == LCB)
      __exec_ca_concat(lhsxp, xsp->ap, xsp->bp, schd_wire);
     else __exec_conta_assign(lhsxp, xsp->ap, xsp->bp, schd_wire);
    }
  }
 __pop_xstk();
 __idp[cap->caschd_tevs_ofs] = (t_midat) NULL;
 /* can just leave scheduled wire value - nothing to free */
}

/*
 * process a wire delay event - know this is always 1 bit
 * non inout path dest. scheduled wire changes processed here also
 *
 * since r,f or path delays will have different delays and inertial
 * conditions for every bit
 * know for scalar bi 0 not -1
 *
 * could possibly optimize one delay form
 * will only get here if wire has delay > 0 (or #0)
 * also know path source or destination can never have wire delay
 *
 * notice when wire changes must see if really changes by doing
 * fi>1 competition of right type using scheduled plus current
 * then know scheduled value really changed
 */
extern void __process_wire_ev(void)
{
 int32 bi;
 int32 itinum;
 byte *sbp;
 word32 nval;
 struct net_t *np;
 struct rngdwir_t *dwirp;
 struct tev_t *tevp;

 tevp = __cur_tevp;
 np = tevp->tu.tenp->tenu.np;
 bi = tevp->tu.tenp->nbi;
 /* DBG remove ---
 if (bi < 0) __misc_terr(__FILE__, __LINE__);
 --- */

 /* free wire event auxialiary field here since bit and wire extracted */
 __my_free(tevp->tu.tenp, sizeof(struct tenp_t));
 tevp->tu.tenp = NULL;

 nval = tevp->outv;
 if (__ev_tracing)
  {
   char s1[RECLEN], s2[RECLEN];

   __evtr_resume_msg();
   if (np->n_isapthdst) strcpy(s2, " (path destination)");
   else strcpy(s2, "");
   __tr_msg("-- processing delay wire %s%s store event, value %s\n",
    __to_evtrwnam(__xs, np, bi, bi, tevp->te_idp), s2,
     __to_vvnam(s1, (word32) nval));
  }
 dwirp = np->nu.rngdwir;
 itinum = (int32) tevp->te_idp[MD_INUM];
 dwirp->wschd_pbtevs[np->nwid*itinum + bi] = NULL;

 /* inhibit if active force */
 if (np->frc_assgn_allocated && force_inhibit_wireassign(np, bi, tevp->te_idp))
  return;

 __idp = tevp->te_idp;

 /* store bit into wire - value is after any multi-fi competition */
 /* this add net chg element if needed */
 if (np->n_stren)
  {
   if (tevp->te_trdecay)
    __gfwarn(649, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
     "charge on node %s.%s has decayed", __msg2_cur_blditree(__xs),
     np->nsym->synam);

   /* get strength wire address */
   sbp = (byte *) &(__idp[np->nva_ofs]);
   if (sbp[bi] != nval)
    {
     sbp[bi] = nval;
     /* know change, record if needed */
     record_sel_nchg_(np, bi, bi);
    }
  }
 else __chg_st_bit(np, bi, nval & 1L, (nval >> 1) & 1L);
 __idp = NULL;
}

/*
 * process a a non blocking procedural assign event - do the assign
 * here just assign - no inertial - each just overwrites
 *
 * SJM 08/08/99 - fixed so lhs indices evaluated at schedule time not
 * event proces time to match LRM and XL
 */
static void process_nbpa_ev_pnd0(void)
{
 int32 wlen;
 word32 *wp;
 struct expr_t *con_lhsxp;
 struct st_t *stp;
 struct tenbpa_t *tenbp;
 struct tev_t *tevp;

 tevp = __cur_tevp;
 tenbp = tevp->tu.tenbpa;
 stp = tenbp->nbastp;
 con_lhsxp = tenbp->nblhsu.nblhsxp;
 wp = tenbp->nbawp;
 /* SJM 08/08/99 - need to assign to copied lhs expr with select indices */
 /* (possibly many if lhs concatenate) replaced by constants */
 /* SJM PUTMEBACK */
 if (con_lhsxp == NULL) con_lhsxp = stp->st.spra.lhsx;
 wlen = wlen_(con_lhsxp->szu.xclen);
 if (__ev_tracing)
  {
   char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN];

   __tr_msg("-- nb event assign in %s %s of %s to %s at %s\n",
    __msg2_idp_blditree(s1, tevp->te_idp), __bld_lineloc(s2,
     tenbp->nbastp->stfnam_ind, tenbp->nbastp->stlin_cnt),
    __xregab_tostr(s3, wp, &wp[wlen], con_lhsxp->szu.xclen, stp->st.spra.rhsx),
    __msgexpr_tostr(s4, con_lhsxp), __to_timstr(__xs, &__simtime));
  }

 /* SJM 05/19/04 - complex procedural assign needs stmt file/line context */
 /* for error messages such as out of range - do not need to save since */
 /* no statement context in event processing - this is exception */
 __slin_cnt = stp->stlin_cnt;
 __sfnam_ind = stp->stfnam_ind;

 /* do assign - know if lhs expr copied, widith still same */
 __exec2_proc_assign(con_lhsxp, wp, &(wp[wlen]), wlen*WBITS);
 /* final step is freeing contents */
 __my_free(wp, 2*wlen*WRDBYTES);

 /* if needed to copy lhs expr., now free */
 if (tenbp->nblhsu.nblhsxp != NULL) __free_xtree(tenbp->nblhsu.nblhsxp);

 __my_free(tevp->tu.tenbpa, sizeof(struct tenbpa_t));
 tevp->tu.tenbpa = NULL;
}

extern void __process_nbpa_varndx_concat_ev(void)
{
 word32 *wp, *rap, *ap, *bp;
 struct net_t *np;
 struct tev_t *tevp;
 int32 wlen, biti;
 word32 av, bv;
 struct nchglst_t *nchglp;
 struct tenbpa_t *tenbp;

//AIV TEV FIXME
 /* AIV 01/07/09 - just check pnd0 pointer != NULL not __processing_pnd0s */
 if (__p0_te_endp == NULL)
  {
   __process_compiled_nbpa_ev_sim_notpnd0();
   return;
  }

 tevp = __cur_tevp;
 tenbp = tevp->tu.tenbpa;
 np = tenbp->nblhsu.nblhsnp;
 /* AIV 08/24/10 - handle 2-state as different routine */
 if (np->n_2state)
  {
   process_nbpa_varndx_concat_ev_2state(tevp, tenbp, np);
   return;
  }
 wp = tenbp->nbawp;
 /* AIV 04/17/07 - some error messages are no longer exact includin these */
 /* this way no need to load static memory statments */
 /* SJM 05/19/04 - complex procedural assign needs stmt file/line context */
 /* for error messages such as out of range - do not need to save since */
 /* no statement context in event processing - this is exception */
 /*
 __slin_cnt = stp->stlin_cnt;
 __sfnam_ind = stp->stfnam_ind;
 */

 /* do assign - know if lhs expr copied, widith still same */
 /* AIV 11/26/07 - number of bytes is 2* for a and b part */
 wlen = (tenbp->nbytes/(2*WRDBYTES));
 biti = tenbp->bi;
 /* AIV 04/30/08 - lhs concat can have a non - index value indicated by -1 */
 if (biti == -1)
  {
   ap = &(wp[0]);
   bp = &(wp[wlen]);
   if (np->nchg_nd_chgstore) __chg_st_val(np, ap, bp);
   else __st_val(np, ap, bp, wlen*WBITS);
  }
 else if (np->n_isarr)
  {
   if (np->nchg_nd_chgstore)
    {
     __chg_st_arr_val(np, NULL, biti, wp, &(wp[wlen]));
     if (__lhs_changed) 
      {
//SJM 08/25/08 - FIXME - why comment out in psel8 but not 366a ?????
       nchglp = tenbp->nchglp;
       __asl_record_array_net_change(np, nchglp, biti);
       __lhs_changed = FALSE;
      }
    }
   /* SJM 02-12-1 - only have n bytes since 8 bytes per a/b word works */
   /* rhs width is a part width in bits */
   else __st_arr_val(np, NULL, biti, wp, &(wp[wlen]), WBITS*wlen);
  }
 else
  {
   /* known to be SR VEC here */
   av = wp[0];
   bv = wp[wlen];
   if (np->nchg_nd_chgstore)
    {
//SJM 08/25/08 - FIXME - why comment out in psel8 but not 366a ?????
     nchglp = tenbp->nchglp;
     __asl_chg_vec_lhsbsel(np, biti, av, bv, nchglp);
    }
   else 
    {
     rap = &(__idp[np->nva_ofs]);
     wlen = wlen_(np->nwid);
     __lhsbsel(rap, biti, av);
     __lhsbsel(&(rap[wlen]), biti, bv);
    }
  }
 /* final step is freeing contents */
 /* lhsxp with no time delay has static memory cannot free */
 __my_free(wp, tenbp->nbytes);
 /* if needed to copy lhs expr., now free */
 __my_free(tevp->tu.tenbpa, sizeof(struct tenbpa_t));
 tevp->tu.tenbpa = NULL;
}

/*
 * 2-state concat nb <= varndx assignments 
 */
static void process_nbpa_varndx_concat_ev_2state(struct tev_t *tevp, 
 struct tenbpa_t *tenbp, struct net_t *np)
{
 word32 *wp, *rap, *ap;
 int32 biti;
 word32 av;
 struct nchglst_t *nchglp;

 wp = tenbp->nbawp;
 /* do assign - know if lhs expr copied, widith still same */
 /* AIV 11/26/07 - number of bytes is 2* for a and b part */
 biti = tenbp->bi;
 /* AIV 04/30/08 - lhs concat can have a non - index value indicated by -1 */
 if (biti == -1)
  {
   ap = &(wp[0]);
   if (np->nchg_nd_chgstore) __chg_st_val(np, ap, NULL);
   else __st_val(np, ap, NULL, np->nwid);
  }
 else if (np->n_isarr)
  {
   if (np->nchg_nd_chgstore)
    {
     __chg_st_arr_val(np, NULL, biti, wp, __addr_2state_zero);
     if (__lhs_changed) 
      {
       nchglp = tenbp->nchglp;
       __asl_record_array_net_change(np, nchglp, biti);
       __lhs_changed = FALSE;
      }
    }
   /* SJM 02-12-13 - never  SV string store here so rhs width same and works */
   else __st_arr_val(np, NULL, biti, wp, __addr_2state_zero, np->nwid);
  }
 else
  {
   /* known to be SR VEC here */
   av = wp[0];
   if (np->nchg_nd_chgstore)
    {
//SJM 08/25/08 - FIXME - why comment out in psel8 but not 366a ?????
     nchglp = tenbp->nchglp;
     __asl_chg_vec_lhsbsel_2state(np, biti, av, nchglp);
    }
   else 
    {
     rap = &(__idp[np->nva_ofs]);
     __lhsbsel(rap, biti, av);
    }
  }
 /* final step is freeing contents */
 /* lhsxp with no time delay has static memory cannot free */
 __my_free(wp, tenbp->nbytes);
 /* if needed to copy lhs expr., now free */
 __my_free(tevp->tu.tenbpa, sizeof(struct tenbpa_t));
 tevp->tu.tenbpa = NULL;
}

/*
 * print out event trace time - not in event trace message
 */
extern void __evtr_resume_msg(void)
{
 char s1[RECLEN];

 if (__last_evtrtime != __simtime)
  {
   /* this should go through time format ? */
   __tr_msg("\n<<< event tracing at time %s\n", __to_timstr(s1, &__simtime));
   __last_evtrtime = __simtime;
  }
}

/*
 * print out evnet trace time - not in event trace message
 */
extern void __o_evtr_resume_msg(void)
{
 char s1[RECLEN];

 if (__last_evtrtime != __simtime)
  {
   /* this should go through time format ? */
   __o_tr_msg("\n<<< event tracing at time %s\n", __to_timstr(s1, &__simtime));
   __last_evtrtime = __simtime;
  }
}

/*
 * process a special getpattern form continous assigment
 * know left of rhsx is $getpattern symbol and right is var. array index
 *
 * notice this is a special immediate overriding assign and does not handle
 * multi-fi wire properties or wire delays or strengths
 *
 * should probably try to optimize special 64 bit case too
 * point of this is to optimized for known fixed form
 *
 * could keep old getpattern value and build index of change and bit
 * select to change those
 * cannot be xmr
 */
extern void __process_getpat(struct conta_t *cap)
{
 int32 bi;
 int32 i, wlen, ubits;
 word32 cbita, cbitb;
 word32 tmpa, tmpb, uwrd, t1, ttmpa, ttmpb;
 struct expr_t *catx;
 struct expr_t *idndp, *lhsxp, *rhsxp;
 struct xstk_t *xsp;
 struct net_t *np;

 /* know rhs is variable array index */
 /* rhs is get pattern function call */
 lhsxp = cap->lhsx;
 rhsxp = cap->rhsx;
 xsp = __eval_xpr(rhsxp->ru.x->lu.x);
 /* this is except to convert to lhs width - extra array bits ignored or */
 /* lhs just not filled */

 /* if out of range or x, value will be changed to x */

 if (__ev_tracing)
  {
   __evtr_resume_msg();
   __tr_msg("-- $getpattern %s processed\n", to_cur_evtrcanam(__xs, cap));
  }

 /* wider than 1 word32 case */
 wlen = wlen_(lhsxp->szu.xclen);
 ubits = ubits_(lhsxp->szu.xclen);
 catx = lhsxp->ru.x;
 bi = (ubits == 0) ? WBITS - 1: ubits - 1;
 for (i = wlen - 1; i >= 0; i--)
  {
   tmpa = xsp->ap[i];
   tmpb = xsp->bp[i];
   /* know need prop. turned off after last propagation (off here) */
   for (; bi >= 0; catx = catx->ru.x, bi--)
    {
     if (catx == NULL) goto done;

     idndp = catx->lu.x;
     np = idndp->lu.sy->el.enp;

     /* AIV 08/23/10 - if 2-state must do conversion */
     if (np->n_2state)
      {
       ttmpa = tmpa; 
       ttmpb = tmpb; 
       t1 = ~ttmpb;
       ttmpa = ttmpa & t1;
       uwrd = (ttmpa >> bi) & 1L;
      }
     else
      {
       /* know lhs get pat concat elements are scalars */
       cbita = (tmpa >> bi) & 1L;
       cbitb = (tmpb >> bi) & 1L;
       uwrd = cbita | (cbitb << 1);
      }
     if (__idp[np->nva_ofs] != uwrd)
      {
       __idp[np->nva_ofs] = uwrd; 
       __lhs_changed = TRUE;
       record_nchg_(np);
      }
    }
   bi = WBITS - 1;
   if (catx == NULL) break;
  }
done:
 __immed_assigns++;
 __pop_xstk();
}

/*
 * emit an netname for tracing with path if needed
 * for ev. know never task/func. part of xmr reference
 */
extern char *__to_evtrwnam(char *s, struct net_t *np, int32 bi1, int32 bi2,
 t_midat *te_idp)
{
 char s1[RECLEN], s2[RECLEN];

 __msg2_idp_blditree(s1, te_idp);
 strcat(s1, ".");
 strcat(s1, __schop(s2, np->nsym->synam));

 if (bi1 == -1 || !np->n_isavec) strcpy(s, s1);
 else if (bi1 == bi2) sprintf(s, "%s[%d]", s1, __unnormalize_ndx(np, bi1));
 else sprintf(s, "%s[%d:%d]", s1, __unnormalize_ndx(np, bi1),
  __unnormalize_ndx(np, bi2));
 return(s);
}

/*
 * emit an netname for tracing with path if needed
 * for ev. know never task/func. part of xmr reference
 */
extern char *__to_cur_evtrwnam(char *s, struct net_t *np, int32 bi1, 
 int32 bi2)
{
 struct itree_t *itp;
 char s1[RECLEN], s2[RECLEN];

 itp = get_itp_();
 __msg2_blditree(s1, itp);
 strcat(s1, ".");
 strcat(s1, __schop(s2, np->nsym->synam));

 if (bi1 == -1 || !np->n_isavec) strcpy(s, s1);
 else if (bi1 == bi2) sprintf(s, "%s[%d]", s1, __unnormalize_ndx(np, bi1));
 else sprintf(s, "%s[%d:%d]", s1, __unnormalize_ndx(np, bi1),
  __unnormalize_ndx(np, bi2));
 return(s);
}

/*
 * for one bit, know some bits forced inhibit assign if this bit forced
 * here do not need to worry about some bits only forced from range
 * this is only for wire where 1 bit per bit*inst product
 */
static int32 force_inhibit_wireassign(struct net_t *np, int32 biti,
 t_midat *te_idp)
{
 struct qcval_t *frc_qcp;
 int32 rv, inum;

 /* DBG remove ---*/
 if (te_idp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 inum = (int32) te_idp[MD_INUM];

 frc_qcp =  &(np->nu2.qcval[inum*np->nwid + biti]);
 if (frc_qcp->qc_active) rv = TRUE; else rv = FALSE;
 return(rv);
}

/*
 * process a path dest. tran (inout) wire delay internal hard driver
 * change event
 *
 * for inout path. know the one driver changed previously and path delayed
 * update of hard driver internal tran channel value for the wire
 * any other change of path will cause event cancel and new schedule
 * so fact that the drivers if evaled will be new value still works
 *
 * since r,f or path delays will have different delays and inertial
 * conditions for every bit, know for scalar bi 0 not -1
 */
extern void __process_trpthdst_ev(void)
{
 int32 bi;
 int32 inum;
 byte *sbp;
 word32 nval, av, bv;
 struct net_t *np;
 struct traux_t *trap;
 struct rngdwir_t *dwirp;
 struct xstk_t *xsp;
 struct tev_t *tevp;

 tevp = __cur_tevp;
 /* notice event here emitted in change gate outwire */
 np = tevp->tu.tenp->tenu.np;
 bi = tevp->tu.tenp->nbi;
 /* DBG remove ---
 if (bi < 0) __misc_terr(__FILE__, __LINE__);
 --- */

 /* free wire event auxialiary field here since bit and wire extracted */
 __my_free(tevp->tu.tenp, sizeof(struct tenp_t));
 tevp->tu.tenp = NULL;

 nval = tevp->outv;
 if (__ev_tracing)
  {
   char s1[RECLEN];

   __evtr_resume_msg();
   __tr_msg(
    "-- processing inout path dest. %s driven value update event, value %s\n",
    __to_evtrwnam(__xs, np, bi, bi, tevp->te_idp),
    __to_vvnam(s1, (word32) nval));
  }
 dwirp = np->nu.rngdwir;
 __idp = tevp->te_idp;
 inum = get_inum_();
 dwirp->wschd_pbtevs[np->nwid*inum + bi] = NULL;

 trap = np->ntraux;
 /* update hard driver stored value and re-eval tran channel if needed */
 if (np->n_stren)
  {
   /* get strength wire address */
   sbp = &(trap->trnva.bp[inum*np->nwid]);
   if (sbp[bi] == nval) goto done;
   sbp[bi] = nval;
  }
 else
  {
   if (!np->n_isavec)
    {
     /* AIV 07/12/07 - BEWARE local inum now is used in reg_fr_inhibit_ macro */
     ld_peri_scalval_(&av, &bv, trap->trnva.bp);
     if (nval == (av | (bv << 1))) goto done;
     /* SJM 07/16/01 - typo was storing old val so tr chan value never chgs */
     /* need to store new non stren value not old */
     /* ??? wrong - st_scalval_(trap->trnva.bp, av, bv); */
     st2_peri_scalval_(trap->trnva.bp, nval);
    }
   else
    {
     push_xstk_(xsp, np->nwid);
     __ld_perinst_val(xsp->ap, xsp->bp, trap->trnva, np->nwid);
     av = rhsbsel_(xsp->ap, bi);
     bv = rhsbsel_(xsp->bp, bi);
     if (nval == (av | (bv << 1))) { __pop_xstk(); goto done; }
     __lhsbsel(xsp->ap, bi, (nval & 1L));
     __lhsbsel(xsp->bp, bi, ((nval >> 1) & 1L));
     __st_perinst_val(trap->trnva, np->nwid, xsp->ap, xsp->bp);
     __pop_xstk();
    }
  }
 /* if some but not this bit in tran channel, just assign */
 /* SJM - 03/15/01 - know bit not -1 since schedules as 0 for scalar */
 __eval_tran_1bit(np, bi);
done:
 __idp = NULL;
}


/* 
 * compiled versions of above slightly different to use static nchgs
 */
extern void __process_compiled_trpthdst_ev(void)
{
 int32 bi;
 byte *sbp;
 word32 nval, av, bv;
 struct net_t *np;
 struct traux_t *trap;
 struct rngdwir_t *dwirp;
 struct xstk_t *xsp;
 struct tev_t *tevp;
 int32 inum;

 tevp = __cur_tevp;
 /* notice event here emitted in change gate outwire */
 np = tevp->tu.tenp->tenu.np;
 bi = tevp->tu.tenp->nbi;

 /* free wire event auxialiary field here since bit and wire extracted */
//AIV FIXME -  should need this struct/free
 __my_free(tevp->tu.tenp, sizeof(struct tenp_t));
 tevp->tu.tenp = NULL;

 nval = tevp->outv;
 dwirp = np->nu.rngdwir;
 __idp = tevp->te_idp;
//AIV FIXME - don't think this is needed either
 inum = get_inum_();
 dwirp->wschd_pbtevs[np->nwid*inum + bi] = NULL;

 trap = np->ntraux;
 /* update hard driver stored value and re-eval tran channel if needed */
 if (np->n_stren)
  {
   /* get strength wire address */
   sbp = &(trap->trnva.bp[inum*np->nwid]);
   if (sbp[bi] == nval) goto done;
   sbp[bi] = nval;
  }
 else
  {
   if (!np->n_isavec)
    {
     /* AIV 07/12/07 - BEWARE local inum now is used in reg_fr_inhibit_ macro */
     ld_peri_scalval_(&av, &bv, trap->trnva.bp);
     if (nval == (av | (bv << 1))) goto done;
     /* SJM 07/16/01 - typo was storing old val so tr chan value never chgs */
     /* need to store new non stren value not old */
     /* ??? wrong - st_scalval_(trap->trnva.bp, av, bv); */
     st2_peri_scalval_(trap->trnva.bp, nval);
    }
   else
    {
     push_xstk_(xsp, np->nwid);
     __ld_perinst_val(xsp->ap, xsp->bp, trap->trnva, np->nwid);
     av = rhsbsel_(xsp->ap, bi);
     bv = rhsbsel_(xsp->bp, bi);
     if (nval == (av | (bv << 1))) { __pop_xstk(); goto done; }
     __lhsbsel(xsp->ap, bi, (nval & 1L));
     __lhsbsel(xsp->bp, bi, ((nval >> 1) & 1L));
     __st_perinst_val(trap->trnva, np->nwid, xsp->ap, xsp->bp);
     __pop_xstk();
    }
  }
 /* if some but not this bit in tran channel, just assign */
 /* SJM - 03/15/01 - know bit not -1 since schedules as 0 for scalar */
//AIV FIXME - need to get the nchglstp here - could use global??????
// __asl_eval_tran_1bit(np, bi);
 __eval_tran_1bit(np, bi);
done:
 __idp = NULL;
}

/*
 * ROUTINES TO PROCESS BEHAVIORAL EVENTS
 */

/* table for converting 4 bit (oonn) edge pair to edge value byte */
/* table treats edge with z as x here */
const byte __epair_tab[] =
 { NOEDGE, EDGE01, EDGE0X, EDGE0X, EDGE10, NOEDGE, EDGE1X, EDGE1X,
   EDGEX0, EDGEX1, NOEDGE, NOEDGE, EDGEX0, EDGEX1, NOEDGE, NOEDGE };

#ifdef __XPROP__
/* same as epair_tab, but is TRUE is edge is on an 'X' */
const byte __is_xedge_tab[] =
 { FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE,
   FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE };
#endif

/*
 * after net changed net (wire or reg) progagate to all dces wire drives
 * bit range passed and used to eliminate fan-out for other bits here
 * all ranges here normalized high to low form
 * notice will never get to event trigger through this path (through cause)
 *
 * inst. ptr here is place np changed (i.e. for XMR define itree loc)
 * know npi1 >= npi2 since normalized internally
 */
extern void __wakeup_delay_ctrls(struct net_t *np, int32 npi1, int32 npi2)
{
 int32 i1, inum;
 word32 *wp;
 word32 oval, nval;
 byte emask;
 struct dcevnt_t *dcep, *dcep2;
 struct tev_t *tevp;
 struct delctrl_t *dctp;
 struct fmonlst_t *fmonp;
 struct fmselst_t *fmsep;
 struct dce_expr_t *dcexp;
 struct itree_t *itp;
 decl_idp_locals_;
#ifdef __XPROP__
 struct st_t *xstp;
 struct xprop_t *xprop;
 struct tev_t *xtevp;
 int32 has_xedge, need_check;
#endif

 dcexp = NULL;
 for (dcep = np->dcelst; dcep != NULL;)
  {
   /* --- DBG remove ---
   if (__idp == NULL) __misc_terr(__FILE__, __LINE__);
   --- */

   /* filter one instance forms before case */
   if (dcep->dce_1inst && dcep->dce_matchu.idp != __idp) 
    { dcep = dcep->dcenxt; continue; } 

   /* SJM 10/06/06 - for vpi vc call back, may free the dcep so must save */
   dcep2 = dcep->dcenxt; 
   switch ((byte) dcep->dce_typ) {
    case DCE_RNG_INST:
     /* SJM 11/25/02 - notice can't be turned off/on */
     dctp = dcep->st_dctrl;
     /* all of wire changed match */
     if (npi1 == -1) goto do_event_ctrl;
     /* dce is range DCE range, know dci1 cannot be -1 */
     if (dcep->dci1 == -2)
      {
       /* SJM 10/12/04 - because contab realloced, must be ndx base of IS */
       wp = &(__contab[dcep->dci2.xvi]);
       inum = get_inum_();
       i1 = (int32) wp[2*inum];
       /* change must be inside range to match */
       if (i1 > npi1 || i1 < npi2) break;
      }
     else
      {
       /* SJM 06/26/04 - FIXME ??? ### isn't else needed here ??? */
       /* eliminate if changed bit do not overlap range */
       /* if low chged above high or high chged below low, eliminate */
       if (npi2 > dcep->dci1 || npi1 < dcep->dci2.i) break;
      }
     goto do_event_ctrl;
    case DCE_INST:
     /* notice dce that is entire wire always matches changed range */
     dctp = dcep->st_dctrl;

do_event_ctrl:
     save_idp = NULL;
     /* first see if variable really changed (plus edge filtering) */
     oval = nval = 3;
     /* if no chg record, then array or reg entire wire so know changed */
     /* know for any wire even scalar, will exist */
     /* LOOKATME - filtering even for DOWN XMR insts that do not match? */
     if (dcep->prevval_ofs != 0)
      {
       /* also eliminate if event control range or wire did not change */
       /* for xmr and/or collpase - look in target itree where dce attached */
       /* for non dce expr form, sets old and new values for edge detection */
       /* AIV 12/11/07 - this can now be an array - handle like a vec */
       if (np->n_isarr)
        {
         if (!__filter_dce_chg(np, dcep, &(__idp[dcep->prevval_ofs]), &oval,
          &nval)) goto dce_done;
        }
       else if (!np->n_isavec)
        {
         /* SJM 06/29/04 - simplified - always use stren version for scalar */
         if (!__scal_stfilter_dce_chg(np, (byte *) &(__idp[dcep->prevval_ofs]),
               &oval, &nval)) goto dce_done;
        }
       else
        {
         if (!np->n_stren)
          {
           if (!__filter_dce_chg(np, dcep, &(__idp[dcep->prevval_ofs]), &oval,
            &nval)) goto dce_done;
          }
         else
          {
           if (!__stfilter_dce_chg(np, dcep, 
             (byte * ) &(__idp[dcep->prevval_ofs]), &oval, &nval)) 
            goto dce_done;
          }
        }
      }
     /*
      * idea for normal event control dce:
      * during prep: first for xmr trace from ref to target (place where wire)
      *
      * here when triggering (i.e. wakeup and schedule thread)
      * if xmr to on target place to wake up, for multiply
      * instantiated down will be one dce for each down inst. - when up wire
      * changes need to match one right dce itree loc which is done by
      * comparing against when match move down to xmr move from target back
      * to xmr ref.
      */
     /* if one inst form (know matches) move to reference itree loc. */
     if (dcep->dce_1inst)
      { 
       set_save_idp_(dcep->dce_refu.idp);
      }
     /* for xmr know target wire changed @(i1.i2.i3.i4.w)  w in dest. */
     else if (dcep->dce_xmrtyp != XNP_LOC)
      {
       /* SJM 04/17/03 - if not right instance do not process */
        
       itp = __match_targ_to_ref(dcep->dce_xmrtyp, dcep->dceu.dcegrp);
       if (itp == NULL) break;
       set_save_idp_itp_(itp);
      }

     /* if armed (i.e. evctrl active) normal processing */
     /* notice current thread (init/always) may differ from dctp thread */
     /* so current thread must not be used here */
#ifdef __XPROP__
     /* AIV 03/27/12 - if xprop xedge is triggered may need to shut off */
     /* if a real edge has occurred */
     /* if clk triggers xedge and rst is a real edge - no xprop */
     /* always (posedge clk or negedge rst) */
     tevp = (struct tev_t *) __idp[dctp->dceschd_tev_ofs];
     need_check = TRUE;
     xtevp = NULL;
     if (tevp == NULL)
      {
       /* if xprop and previous event was trigged may have to turn back */
       /* to non-xprop stmt list */
       if ((xstp = dctp->xprop_xedge_actionst) != NULL)
        {
         inum = get_inum_();
         xprop = xstp->st.sif.xprop;
         xtevp = xprop->xevents[inum];
         if (xtevp == NULL) need_check = FALSE;
        }
       else need_check = FALSE;
      }

     if (need_check)
#else
     if ((tevp = (struct tev_t *) __idp[dctp->dceschd_tev_ofs]) != NULL)
#endif
      {
       /* RELEASE remove ---
       {
        struct tev_t *tevp;

        if (tevp->tetyp < 1 || tevp->tetyp > 14)
         __misc_terr(__FILE__, __LINE__);
       }
       --- */
       /* filter out if wrong edge - know if has edge prev val set */
       /* unless dce expr also set (non nul) */
       if (dcep->dce_edge)
        {
         /* eval. expr - know at ref. (not var. chg) itree loc. */
         if ((dcexp = dcep->dce_expr) != NULL)
          {
           /* if XMR dce, already at ref itree loc*/
           if (!filter_edge_expr(dcexp, &oval, &nval)) goto dce_done;
           /* nval and oval set for edge checking below */
          }

         /* even though only pos and neg legal here use general signature */
         /* dce edgval is 1 bit per edge type table - epair tab maps to bit */
         emask = __epair_tab[nval | (oval << 2)];
         /* if no bits in common, no match */
         if (((byte) dcep->dce_edgval & emask) == 0) goto dce_done;
        }
       /* last: after move to ref inst, need to match itree loc for iact */
       /* need edge check before here because update old eval */
       if (dctp->dc_iact && dcep->iact_idp != __idp) goto dce_done;

       /* 10/27/00 SJM - if repeat form check and decrement repeat count */
       /* and if not counted down to 0 yet, do nothing (filter out) */
       if (dctp->repcntx != NULL)
        {
         /* REMOVEME AGAIN 04/01/02 ??? */
         /* DBG remove --- */
         if (__debug_flg)
          {
           __dbg_msg(
            "+++ now %s repeated edge for net %s (inst %s) count %d\n",
            __to_timstr(__xs2, &__simtime), np->nsym->synam,
            __msg2_cur_blditree(__xs), (int32) __idp[dctp->dce_repcnt_ofs] - 1);
          }
         /* --- */
         /* SJM 04/02/02 since word32, any positive still do not trigger */
         if (--(__idp[dctp->dce_repcnt_ofs]) != 0) goto dce_done;
        }
#ifdef __XPROP__
      /* AIV 02/16/12 - must now handle always @(X) changes for X-propagation */
      if ((xstp = dctp->xprop_xedge_actionst) != NULL)
       {
        xprop = xstp->st.sif.xprop;
        /* DBG remove --- */
        if (!xstp->xprop_eligible) __misc_terr(__FILE__, __LINE__);
        /* ----- */
        has_xedge = FALSE;
        /* if edge just check for x edge from x tab */
        if (__xprop_pos_neg_only) 
         {
          if (dcep->dce_edge) has_xedge = __is_xedge_tab[nval | (oval << 2)];
         }
        else if (dcep->dce_edge || (!np->n_isavec && !np->n_isarr))
         {
          /* known to be be an xprop if here */
          /* if edge expr just check if new value is x */
          /* if net is array nval will be set above */
          /* only include the x edges - not zs */
          has_xedge = __is_xedge_tab[nval | (oval << 2)];
          if (has_xedge && !np->n_isavec)
           {
            inum = get_inum_();
            if (dcep->dce_edge)
             {
              /* posedge */
              if (dcep->dce_edgval == E_POSEDGE)
               {
                /* X-> must be 1 to be posedge */
                /* 0->X must also be a 1 */
                /* if not 3 this will already be 1 */
                if (nval == 3)
                 {
                  xprop->xedge_to_vals[inum] = 1;
                  xprop->xedge_nets[inum] = np;
                 }
               }
              /* negedge */
              else 
               {
                /* X-> must be 0 */
                /* 1->X must also be 0 */
                /* if not 3 this will already be 1 */
                if (nval == 3)
                 {
                  xprop->xedge_to_vals[inum] = 0;
                  xprop->xedge_nets[inum] = np;
                 }
               }
             }
            else 
             {
              /* 1/0 -> must change to opposite */
              if (oval != 3) 
               {
                xprop->xedge_to_vals[inum] = !oval; 
                xprop->xedge_nets[inum] = np;
               }
             }
           }
         }
        /* otherwise check if net has X parts */
        else 
         {
          /* if array value is known to be stored in prevval_ofs by here */
          if (__do_xprop_xedge_vectors)
           {
            /* DBG remove --- */
            if (__xprop_xedge == -1) __misc_terr(__FILE__, __LINE__);
            if (__xprop_pos_neg_only) __misc_terr(__FILE__, __LINE__);
            /* ----- */
            has_xedge = __xprop_xedge;
            __xprop_xedge = -1;
           }
         }
        /* if xedge already set - may have to switch back to non-xprop */
        /* stmt handling */
        if (xtevp != NULL)
         {
          if (!has_xedge) xtevp->tu.tethrd->thnxtstp = dctp->actionst;
          goto dce_done;
         }
        /* if has xedge mark the bit and set to xprop action list */
        /* otherwise restore the original stmt (non-xprop) list */
        if (!has_xedge)
         {
          tevp->tu.tethrd->thnxtstp = dctp->actionst;
         }
        else  
         {
          tevp->tu.tethrd->thnxtstp = xstp;
          inum = get_inum_();
          xprop->xevents[inum] = tevp;
         }
       }
#endif
       trigger_evctrl(dctp, tevp);
      }

dce_done:
     if (save_idp != NULL)
      {
       restore_idp_();
      }
     break;  
    case DCE_RNG_MONIT:
     /* no -2 IS form since 1 active monit from 1 itree place only */
     /* if enire wire changed, always match */
     if (npi1 != -1 && (npi1 < dcep->dci2.i || npi2 > dcep->dci1)) break;
     /*FALLTHRU */
    case DCE_MONIT:
     /* SJM 11/25/02 - only check off for ones that can be off */
     if (dcep->dce_off) break;

     /* notice these work by storing old and new values */
     if (dcep->dce_matchu.idp != __idp) break;
     /* fmon nil for the one monitor in design */
     if (dcep->dceu2.dce_fmon == NULL) __slotend_action |= SE_MONIT_TRIGGER;
     else
      {
       fmonp = dcep->dceu2.dce_fmon;
       /* if already activated, nothing to do */
       if (fmonp->fmse_trig == NULL)
        {
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
      }
     break;
    case DCE_RNG_QCAF:
     if (dcep->dce_off) break;
     /* no -2 IS form since 1 active from 1 itree place only */
     /* if enire wire changed, always match */
     if (npi1 != -1 && (npi1 < dcep->dci2.i || npi2 > dcep->dci1)) break;
     /*FALLTHRU */
    case DCE_QCAF:
     if (dcep->dce_off) break;
     if (dcep->dce_matchu.idp != __idp) break;
     /* do not care which rhs wire changed must eval and assign all */
     __assign_qcaf(dcep);
     break;
    case DCE_RNG_PVC:
     /* SJM 07/24/00 - must turn off PLI 1.0 PV dces from inside self */
     if (dcep->dce_off) break;

     /* no -2 IS form since 1 active from 1 itree place only */
     /* if enire wire changed, always match */
     if (npi1 != -1 && (npi1 < dcep->dci2.i || npi2 > dcep->dci1)) break;
     /*FALLTHRU */
    case DCE_PVC:
     /* SJM 07/24/00 - must turn off PLI 1.0 PV dces from inside self */
     if (dcep->dce_off) break;

     /* notice tf PV change always per instance */
     if (dcep->dce_matchu.idp != __idp) break;

     /* must check to make sure psel assign changed bits in actual range */
     oval = nval = 3;
     /* if no chg record, then array or reg entire wire so know changed */
     /* one dce for each different inst and location of _tf call */
     if (dcep->pli_prevval.wp != NULL)
      {
       if (np->n_stren)
        {
         if (!__stfilter_dce_chg(np, dcep, dcep->pli_prevval.bp, &oval, &nval))
          break;
        }
       else
        {
         if (!__filter_dce_chg(np, dcep, dcep->pli_prevval.wp, &oval, &nval))
          break;
        }
      }
     /* do not care which rhs wire changed must eval and assign all */
     __pvc_call_misctf(dcep);
     break;
    case DCE_RNG_CBVC:
     /* SJM 07/24/00 - must turn off PLI 1.0 PV dces from inside self */
     if (dcep->dce_off) break;

     /* callback value change but dce contents differ */
     /* no -2 IS form since 1 active from 1 itree place only */
     /* if enire wire changed, always match */
     if (npi1 != -1 && (npi1 < dcep->dci2.i || npi2 > dcep->dci1)) break;
     /*FALLTHRU */
    case DCE_CBVC:
     /* SJM 07/24/00 - must turn off PLI 1.0 PV dces from inside self */
     if (dcep->dce_off) break;

     if (dcep->dce_matchu.idp != __idp) break;
     /* DBG remove ---
     if (__debug_flg && np->n_stren)
      {
       int32 dwid;
       byte *sbp;
       char s1[RECLEN];

       sbp = (byte *) &(__idp[np->nva_ofs]);
       -* SJM 06/03/02 - was wrongly checking dci2 *-
       if (dcep->dci1 == -2) __misc_terr(__FILE__, __LINE__);

       if (dcep->dci1 != -1)
        {
         sbp = &(sbp[dcep->dci2.i]);
         dwid = (dcep->dci1 - dcep->dci2.i) + 1;
         sprintf(s1, "%s[%d:%d]", np->nsym->synam, dcep->dci1, dcep->dci2.i);
        }
       else { dwid = np->nwid; strcpy(s1, np->nsym->synam); }
       __dbg_msg("CBVC: %s strength value %s (old %s)\n", s1,
        __st_regab_tostr(__xs, sbp, dwid),
        __st_regab_tostr(__xs2, dcep->pli_prevval.bp, dwid));
      }
     else
      {
       struct xstk_t *xsp, *xsp2;

       push_xstk_(xsp, np->nwid);
       __ld_wire_val(xsp->ap, xsp->bp, np);

       if (dcep->pli_prevval.wp != NULL)
        {
         -* know have current instance here *-
         push_xstk_(xsp2, np->nwid);
         __ld_perinst_val(xsp2->ap, xsp2->bp, dcep->prevval, np->nwid);
         __regab_tostr(__xs2, xsp2->ap, xsp2->bp, xsp2->xslen, BHEX, FALSE);
         __pop_xstk();
        }
       else strcpy(__xs2, "**none**");

       __dbg_msg("CBVC: value %s (old %s)\n",
        __regab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE), __xs2);
       __pop_xstk();
      }
     --- */

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
           if (!__scal_stfilter_dce_chg(np, dcep->pli_prevval.bp,
            &oval, &nval)) break;
          }
         else
          {
           /* need strength changes too */
            if (!__vccb_scal_standval_filter(np, dcep->pli_prevval.bp,
             &oval, &nval, dcep->dce_edge)) break;
          }
        }
       else
        {
         if (!np->n_stren)
          {
           if (!__filter_dce_chg(np, dcep, dcep->pli_prevval.wp, &oval,
            &nval)) break;
          }
         else
          {
           /* 05/20/00 - SJM - following LRM vi vpi stren report st chg */
           /* user passed non stren val request to vpi_ cb call back */
           if (dcep->dce_nomonstren)
            {
             if (!__stfilter_dce_chg(np, dcep, dcep->pli_prevval.bp, &oval,
              &nval)) break;
            }
           else
            {
             /* need strength changes too */
             if (!__vccb_vec_standval_filter(np, dcep, dcep->pli_prevval.bp,
              &oval, &nval)) break;
            }
          }
        }
      }
     /* need one call back for every change */

     /* SJM 07/24/00 - must run with this call back turned off in case */
     /* call back c code does put value to reg because change propagation */
     /* for regs must be immediate */
     /* notice will never get here unless dce on */
     dcep->dce_off = TRUE;
     /* SJM 10/06/06 - must pass the dce since dce cbp has list of dces */ 
     __cbvc_callback(dcep, dcep->dceu.dce_cbp, dcep->dceu.dce_cbp->cb_hp);

     /* SJM 10/06/06 - dcep may be free in the user call back so cbvc */
     /* call back processing code handles turning back on if user did */
     /* not turn off in the cb routine - also loop must handle freed case */
     break;

    /* these are used only in vpi_ for force/release call backs */
    case DCE_CBF: case DCE_RNG_CBF: case DCE_CBR: case DCE_RNG_CBR:
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
   dcep = dcep2;
  }
}

/*
 * evaluate, set edge new and old and filter for dce change - non xmr case
 */
static int32 filter_edge_expr(struct dce_expr_t *dcexp, word32 *oval,
 word32 *nval)
{
 word32 nav, nbv;
 word32 av, bv;
 struct xstk_t *xsp;

 /* evaluate expr. to get current edge in ref. context */
 xsp = __eval_xpr(dcexp->edgxp);
 /* extract low bit in case wide */
 nav = xsp->ap[0] & 1L;
 nbv = xsp->bp[0] & 1L;
 /* SJM 08/07/00 - now done with pushed expr value */
 __pop_xstk();

 *nval = nav | (nbv << 1);
 ld_scalval_(&av, &bv, __idp[dcexp->expr_ofs]);
 *oval = av | (bv << 1);
 /* if variable does not effect expr. value, no edge */
 if (nval == oval) return(FALSE);
 st_scalval_(&(__idp[dcexp->expr_ofs]), nav, nbv);
 return(TRUE);
}

/*
 * trigger an armed event control for current itree loc.
 * changes pending delay control event and thread resume event, and links in
 *
 * itree loc. must match and for xmr/col. is ref. itree loc.
 * know will not see if event delay control not active (armed)
 */
static void trigger_evctrl(struct delctrl_t *dctp, struct tev_t *tevp)
{
 /* AIV 12/15/10 - mark event as triggered */
 if (__event_covered != NULL) 
  {
   __event_covered[dctp->dc_id_ndx] = TRUE;
  }

 /* getting here means dctrl event triggered */
 /* DBG remove --- */
 if (__debug_flg && __st_tracing)
  {
   struct st_t *stp;
   struct itree_t *itp, *thd_itp;

   if (tevp->enterptr == __process_nbpa_ev)
    {
     itp = get_itp_();
     stp = tevp->tu.tenbpa->nbastp;
     __tr_msg(
      "-- scheduling NB event control assign for now line %s (itree=%s)\n",
      __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt),
      itp->itip->isym->synam);
    }
   else
    {
     itp = get_itp_();
     stp = tevp->tu.tethrd->thnxtstp;
     /* SJM 07/07/08 - need to get idp from head of idp area not inum */ 
     thd_itp = (struct itree_t *) tevp->tu.tethrd->th_idp[MD_ITP];
     __tr_msg(
      "-- scheduling event control resume for now line %s (chg in thd=%s, itree=%s)\n",
      __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt),
       thd_itp->itip->isym->synam,
      itp->itip->isym->synam);
    }
  }
 /* --- */

 /* must schedule wakeup since no way to interupt current context */
 /* which may not be procedural threads */
 tevp->etime = __simtime;
 /* armed event and now resume event already associated with thread */
 /* restart thread already set - must add to front for interactive */
 if (tevp->enterptr != __process_nbpa_ev)
  {
   /* AIV 09/05/07 - compiler must do special case handling for free events */
   if (__compiled_sim) __asl_compiled_ev_to_front(tevp);
   else __add_ev_to_front(tevp);
   __idp[dctp->dceschd_tev_ofs] = (t_midat) NULL;
   /* in case disable, indicate suspended on ev thrd no suspend to disable */
   /* AIV 05/15/07 - should never be getting here during compiled code */
   /* put still does during tran channel/exec_cause wrappers etc */
   /* AIV FIXME */
   if (!__compiled_sim)
    {
     tevp->tu.tethrd->th_dctp_tev_ofs = 0;
    }
  }
 /* else add to #0 for non blocking assign */
 else
  {
   /* LOOKATME - is this right */
   /* here ok to have list of events (non inertial) */
   /* know at least 1 event, remove head schedule for now after trigger */
   __idp[dctp->dceschd_tev_ofs] = (t_midat) tevp->tenxtp;
   if (__p0_te_hdrp == NULL) __p0_te_hdrp = __p0_te_endp = tevp;
   else { __p0_te_endp->tenxtp = tevp; __p0_te_endp = tevp; }

   /* works because no new tevs that could cause realloc called */
   tevp->tenxtp = NULL;
   /* this now looks like normal delay control nb */
   tevp->tu.tenbpa->nbdctp = NULL;
  }
}

/*
 * stren filter non monit dce for real change - return F if not changed
 *
 * needed because may assign to range but monitor bit in range did not chged
 * also if edge operator (not chaange) sets the oval and nval
 * dce put on target
 *
 * oneinst for cases where must load right inst of wire but only one inst
 * for dce
 *
 * this is for change operator not %v so value not strength change used
 */
extern int32 __stfilter_dce_chg(struct net_t *np, struct dcevnt_t *dcep,
 byte *dcesbp, word32 *oval, word32 *nval)
{
 int32 bi;
 int32 dcewid, i1, i2;
 byte *nsbp;
 byte dcev, nv;

 __get_cor_range(dcep->dci1, dcep->dci2, &i1, &i2);
 /* point to wire value */
 nsbp = (byte *) &(__idp[np->nva_ofs]);
 /* since LRM allows vector - this automatically accesses low bit */
 if (i1 != -1) nsbp = &(nsbp[i1]);

 /* only need to set values for edge if complicated need expr form */
 if (dcep->dce_edge)
  {
   if ((dcev = (dcesbp[0] & 3)) == (nv = (nsbp[0] & 3))) return(FALSE);
   *oval = dcev;
   *nval = nv;
   /* update the prevval for next wire change */
   dcesbp[0] = nsbp[0];
   return(TRUE);
  }

 /* all change operators here (%v handled elsewhere) are value only */
 dcewid = __get_dcewid(dcep, np);
 for (bi = 0; bi < dcewid; bi++)
  { if ((dcesbp[bi] & 3) != (nsbp[bi] & 3)) goto not_same_val; }
 return(FALSE);

not_same_val:

#ifdef __XPROP__
 /* AIV 02/22/12 - if xprop must now check for xedges - must do this here */
 /* before prevval is stored to new value - just set the global */
 /* only do this if it does not have an edge */
 if (!dcep->dce_edge)
  {
   if ((__xprop || __xprop2) && __do_xprop_xedge_vectors)
    {
     __xprop_xedge = has_x_only_edge_stren(dcesbp, nsbp, dcewid);
    }
  }
#endif
 /* old value comes from internally stored prev. val, new is value of wire */
 /* copy from nbsp to dcesbp */
 memcpy(dcesbp, nsbp, dcewid);
 return(TRUE);
}

/*
 * vector stren and value filter for vpi_ stren only val chg call back
 * return F if not changed
 *
 * needed because may assign to range but monitor bit in range did not chged
 * also if edge operator (not chaange) sets the oval and nval
 * dce put on target
 *
 * 06/06/00 - SJM - new routine to filter vpi vec stren only chg
 */
extern int32 __vccb_vec_standval_filter(struct net_t *np,
 struct dcevnt_t *dcep, byte *dcesbp, word32 *oval, word32 *nval)
{
 int32 dcewid, i1, i2;
 byte *nsbp;
 byte dcev, nv;

 __get_cor_range(dcep->dci1, dcep->dci2, &i1, &i2);
 /* point to wire value */
 nsbp = (byte *) &(__idp[np->nva_ofs]);
 /* since LRM allows vector - this automatically accesses low bit */
 if (i1 != -1) nsbp = &(nsbp[i1]);

 /* only need to set values for edge if complicated need expr form */
 /* for edges only low bit */
 /* LOOKATME - think edges can't happen here */
 if (dcep->dce_edge)
  {
   if ((dcev = dcesbp[0]) == (nv = nsbp[0])) return(FALSE);
   *oval = dcev & 3;
   *nval = nv & 3;
   /* update the prevval for next wire change */
   dcesbp[0] = nsbp[0];
   return(TRUE);
  }

 /* call back happens if only strength changes */
 dcewid = __get_dcewid(dcep, np);
 if (memcmp((char *) nsbp, (char *) dcesbp, dcewid) == 0) return(FALSE);
 memcpy(dcesbp, nsbp, dcewid);
 return(TRUE);
}

/*
 * vpi_ scalar val chg stren and value filter (report stren only chges)
 * return F if not changed
 *
 * 06/06/00 - SJM - new routine to filter vpi scalar stren only chg
 */
extern int32 __vccb_scal_standval_filter(struct net_t *np, byte *dcesbp,
 word32 *oval, word32 *nval, int32 dce_edge)
{
 byte *nsbp;
 byte dcev, nv;

 /* point to wire value */
 nsbp = (byte *) &(__idp[np->nva_ofs]);
 /* if values same, no edge or no change */
 if ((dcev = dcesbp[0]) == (nv = nsbp[0])) return(FALSE);
 dcesbp[0] = nsbp[0];

 /* only need to set values for edge if complicated need expr form */
 /* but need value without strength for edge */
 if (dce_edge) { *oval = dcev & 3; *nval = nv & 3; }

 return(TRUE);
}

/*
 * filter non monit dce for actual change - return F if not changed
 * called from decl itree contextfor XMR
 *
 * needed because may assign to range but monitor bit in range did not chged
 * also if edge operator (not change) sets the oval and nval
 * know wire changed so "new" prevval is wire value
 */
extern int32 __filter_dce_chg(struct net_t *np, struct dcevnt_t *dcep,
 word32 *dcewp, word32 *oval, word32 *nval)
{
 int32 dcewid, i1, i2, rv, wlen;
 word32 aval, bval;
 struct xstk_t *nxsp;

 dcewid = __get_dcewid(dcep, np);
 /* load wire value */
 push_xstk_(nxsp, dcewid);
 __get_cor_range(dcep->dci1, dcep->dci2, &i1, &i2);
 __ld_wire_sect(nxsp, np, i1, i2);

 /* SJM 08-10-07 if one bit will be scalar, need to convert to a/b */ 
 if (dcewid == 1)
  {
   ld_scalval_(&(aval), &(bval), dcewp[0]);
   if (aval == nxsp->ap[0] && bval == nxsp->bp[0]) { rv = FALSE; goto done; }

   /* only need to set values for edge if complicated need expr form */
   if (dcep->dce_edge)
    {
     /* old value comes from internally stored preval, new is value of wire */
     *oval = dcewp[0];
     *nval = (nxsp->ap[0] & 1) | ((nxsp->bp[0] << 1) & 2);
    }
  }
 else
  {
   wlen = wlen_(dcewid);
   if (cmp_vval_(dcewp, nxsp->ap, dcewid) == 0 &&
    (cmp_vval_(&(dcewp[wlen]), nxsp->bp, dcewid) == 0))
    { rv = FALSE; goto done; }

   /* only need to set values for edge if complicated need expr form */
   if (dcep->dce_edge)
    {
     /* old value comes from internally stored preval, new is value of wire */
     *oval = (dcewp[0] & 1) | ((dcewp[wlen] << 1) & 2);
     *nval = (nxsp->ap[0] & 1) | ((nxsp->bp[0] << 1) & 2);
    }
  }
#ifdef __XPROP__
 /* AIV 02/22/12 - if xprop must now check for xedges - must do this here */
 /* before prevval is stored to new value - just set the global */
 /* only do this if it does not have an edge */
 if (!dcep->dce_edge)
  {
   if ((__xprop || __xprop2) && __do_xprop_xedge_vectors)
    {
     __xprop_xedge = has_x_only_edge(dcewp, nxsp->ap, dcewid);
    }
  }
#endif

 __st_idp_val(dcewp, dcewid, nxsp->ap, nxsp->bp);
 rv = TRUE;
done:
 __pop_xstk();
 return(rv);
}

#ifdef __XPROP__
/*
 * return TRUE if x edge has at least one 'x' and no real 0/1 changes
 */
static int32 has_x_only_edge(word32 *wp1, word32 *wp2, int32 blen)
{
 int32 i, has_xs, wlen;
 word32 *wbp1, *wbp2;
 word32 aval1, aval2, bval1, bval2, has_bval;

 wlen = wlen_(blen);
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
   has_bval = (bval1 | bval2);
   if (has_bval)
    {
     has_xs = TRUE;
     /* mask out b bits */
     if ((aval1 | has_bval) ^ (aval2 | has_bval))
        return(FALSE);
    }
  }
 return(has_xs);
}

/*
 * same as above but strenght version
 */
static int32 has_x_only_edge_stren(byte *bp1, byte *bp2, int32 blen)
{
 int32 i, has_xs;
 byte aval1, aval2, bval1, bval2, has_bval;

 has_xs = FALSE;
 for (i = 0; i < blen; i++)
  {
   /* only include the x edges - not zs */
   aval1 = bp1[i] & 1;
   aval2 = bp2[i] & 1;
   bval1 = (((bp1[i] & 3) >> 1) & 1L) & aval1;
   bval2 = (((bp2[i] & 3) >> 1) & 1L) & aval2;
   /* if has xs */
   has_bval = (bval1 | bval2);
   if (has_bval)
    {
     has_xs = TRUE;
     /* mask out b bits */
     if ((aval1 | has_bval) ^ (aval2 | has_bval))
        return(FALSE);
    }
  }
 return(has_xs);
}
#endif

extern int32 __scal_stfilter_dce_chg(struct net_t *np, byte *dcesbp,
 word32 *oval, word32 *nval)
{
 byte *nsbp;
 byte dcev, nv;

 /* point to wire value */
 nsbp = (byte *) &(__idp[np->nva_ofs]);
 /* if values same, no edge or no change */
 if ((dcev = (dcesbp[0] & 3)) == (nv = (nsbp[0] & 3))) return(FALSE);
 dcesbp[0] = nsbp[0];

 /* only need to set values for edge if complicated need expr form */
 /* AIV 02/22/12 always set these since it never hurts */
 *oval = dcev; 
 *nval = nv;

 /* LOOKATME - could fix %v strength only change on value here */
 /* if knew which dce was not %v and dcewid is number of bytes since stren */

 return(TRUE);
}

/*
 * TIMING CHECK SIMULATION ROUTINES
 */

/*
 * process some time change record net pin record
 * action depends on npp subtype
 * these are always 1 bit only (bsel, scalar or can be low bit of vector)
 */
extern void __process_npp_timofchg(struct net_t *np, struct net_pin_t *npp)
{
 int32 i1;
 word32 new_eval, old_eval, av, bv;
 word64 reftim;
 word64 *w64p;
 word32 *wp;
 struct tchg_t *tchgp;
 struct tchk_t *tcp;
 struct chktchg_t *chktcp;
 struct npaux_t *npauxp;
 struct spcpth_t *newpthp;

 /* notice because load bit of scalar works for entire wire get bit 0 */
 if ((npauxp = npp->npaux) == NULL) i1 = 0; else i1 = npauxp->nbi1;
 /* all but in module need this correction */
 /* AIV INUM FIXME - cannot get this case past evaluation */
 /* ask SJM if what to do about???????? */
 if (npp->npproctyp != NP_PROC_INMOD) __misc_terr(__FILE__, __LINE__);
 __ld_bit(&av, &bv, np, i1);
 new_eval = av | (bv << 1);

 /* know inst ptr does not change in here */
 switch (npp->chgsubtyp) {
  case NPCHG_TCSTART:
   /* notice reference event always recorded */
   /* $period does not have reference event net pin change element */
   tchgp = npp->elnpp.etchgp;
   tcp = tchgp->chgu.chgtcp;
   if (!filter_bitchange(new_eval, tchgp->oldval_ofs, tcp->startedge,
    tcp->startcondx)) break;

   w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
   *w64p = __simtime;

   if (__debug_flg && __ev_tracing)
    {
     char s1[RECLEN], s2[RECLEN];

     if (npp->npproctyp != NP_PROC_INMOD) bld_xmrsrc_ref(s1, np);
     else sprintf(s1, "%s.%s", __msg2_cur_blditree(__xs),
      np->nsym->synam);

     __tr_msg("## wire %s recording %s (line %s) reference event at %s\n", s1,
      __to_tcnam(__xs, tcp->tchktyp),
      __bld_lineloc(s2, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt),
      __to_timstr(__xs2, &__simtime));

      bld_srcfilter_ref(s2, FALSE, tcp->startedge, tcp->startcondx);
      if (strcmp(s2, "") != 0) __tr_msg("   %s\n", s2);
    }
   break;
  case NPCHG_TCCHK:
   chktcp = npp->elnpp.echktchgp;
   tchgp = chktcp->startchgp;
   tcp = tchgp->chgu.chgtcp;
   /* this returns F if condition or edge does not match */
   if (!filter_bitchange(new_eval, chktcp->chkoldval_ofs, tcp->chkedge,
    tcp->chkcondx)) break;

   w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
   reftim = *w64p;

   /* filter out initialize changes - need real change for timing check */
   if (reftim == 0ULL)
    {
     /* first during run change for period recorded but no violation */
     if (tcp->tchktyp == TCHK_PERIOD)
      {
       w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
       *w64p = __simtime;
      }
     break;
    }
   /* also if already on list for now, do not add again */
   /* AIV 10/15/09 - now just check if on list with the flag T/F */
   wp = &(__idp[chktcp->chkactive_ofs]);
   if (!(*wp))
    {
     add_tchk_chged(chktcp);
     /* possibly better to only record for "record before check" case */
     *wp = TRUE;

     if (__debug_flg && __ev_tracing)
      {
       char s1[RECLEN], s2[RECLEN];

       if (npp->npproctyp != NP_PROC_INMOD) bld_xmrsrc_ref(s1, np);
       else sprintf(s1, "%s.%s", __msg2_cur_blditree(__xs), np->nsym->synam);

       __tr_msg("## wire %s recording %s (line %s) data event at %s\n", s1,
        __to_tcnam(__xs, tcp->tchktyp),
        __bld_lineloc(s2, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt),
        __to_timstr(__xs2, &__simtime));

        bld_srcfilter_ref(s2, FALSE, tcp->chkedge, tcp->chkcondx);
        if (strcmp(s2, "") != 0) __tr_msg("   %s\n", s2);
      }
     /* if repeated edge during same time - use 1st of this time as ref. */
    }
   /* SJM 10/10/04 - was wrongly setting ref even change time when repeated */
   /* check event changes during same time */
   break;
  case NPCHG_PTHSRC:
   tchgp = npp->elnpp.etchgp;
   newpthp = tchgp->chgu.chgpthp;
   /* special case code if no path edge or cond - also always record ifnone */
   /* because must be simple path */
   if (newpthp->pth_ifnone || (newpthp->pthedge == NOEDGE))
    {
     old_eval = __idp[tchgp->oldval_ofs];
     if (new_eval == old_eval) break;
     /* always save new value to old because value changed */
     __idp[tchgp->oldval_ofs] = new_eval;
    }
   else
    {
     /* AIV 01/12/12 - path conditions are no longer checked here passing */
     /* NULL instead of pthcondx - these are checked during path delay calc */
     if (!filter_bitchange(new_eval, tchgp->oldval_ofs, newpthp->pthedge,
      NULL)) break;
    }
   w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
   *w64p = __simtime;

   if ((__debug_flg && __ev_tracing) || __pth_tracing)
    {
     char s1[RECLEN], s2[RECLEN];

     if (npp->npproctyp != NP_PROC_INMOD) bld_xmrsrc_ref(s1, np);
     else sprintf(s1, "%s.%s", __msg2_cur_blditree(__xs), np->nsym->synam);

     /* notice cannot identify by delay since do not know old/new value */
     __tr_msg("## wire %s recording path (line %s) source change at %s\n", s1,
      __bld_lineloc(s2, newpthp->pthsym->syfnam_ind,
      newpthp->pthsym->sylin_cnt), __to_timstr(__xs, &__simtime));

     bld_srcfilter_ref(s2, newpthp->pth_ifnone, newpthp->pthedge,
      newpthp->pthcondx);
     if (strcmp(s2, "") != 0) __tr_msg("   %s\n", s2);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * build xmr source net instance reference
 */
static void bld_xmrsrc_ref(char *s, struct net_t *np)
{
 sprintf(s, "%s.%s (xmr from %s)",
  __msg2_blditree(__xs, __itstk[__itspi - 1]), np->nsym->synam,
  __msg2_cur_blditree(__xs2));
}

/*
 * build path source filter (ifnone, or edge and/or condition)
 */
static void bld_srcfilter_ref(char *s, word32 pthifnone, word32 cedge,
 struct expr_t *cxp)
{
 int32 has_edge;
 struct xstk_t *xsp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 has_edge = FALSE;
 strcpy(s, "");
 if (pthifnone) strcpy(s, "CONDITION: ifnone)");
 else
  {
   if (cedge != NOEDGE)
    {
     sprintf(s1, "EDGE: %s", __to_edgenam(s2, cedge));
     strcpy(s, s1);
     has_edge = TRUE;
    }
   if (cxp != NULL)
    {
     xsp = __eval_xpr(cxp);
     sprintf(s1, "CONDITION: %s TRUE value %s", __msgexpr_tostr(s2, cxp),
      __regab_tostr(s3, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE));
     /* SJM 08/30/99 - for edge trace was not popping stack */
     __pop_xstk();
     if (has_edge) strcat(s, ", and ");
     strcat(s, s1);
    }
  }
}

/*
 * return T if bit changed (must pass all filters to change
 * because new edge value already computed (in up), need down itree here
 * AIV 01/04/12 - old_ofs needs to be size_t - could truncate for 64-bit
 */
static int32 filter_bitchange(word32 new_eval, size_t old_ofs,
 word32 signat, struct expr_t *condx)
{
 int32 epair;
 word32 old_eval;
 struct xstk_t *xsp;

 old_eval = __idp[old_ofs];

 /* first filter: this bit did not change */
 if (new_eval == old_eval) return(FALSE);
 /* always save new value to old */
 __idp[old_ofs] = new_eval;

 /* second filter if has edge - only change if matching edge */
 if (signat != 0)
  {
   /* build edge 4 bit index */
   epair = __epair_tab[new_eval | (old_eval << 2)];
   /* if any edge table bit is 1, then found edge */
   if ((signat & epair) == 0) return(FALSE);
  }
 /* third filter &&& cond or sdpd or edge sensitive path */
 if (condx != NULL)
  {
   /* only eliminate if evaluates to 0 - x/z condition match */
   xsp = __eval2_xpr(condx);
   /* timing check condition expressions must be 1 bit - use low */
   /* fastest to just always mask */
   /* LRM requires anything but explicit false (0) is T */
   /* for === operators never x/z (only 1 or 0) possible so always works */
   /* === illegal in SDPDs so never a problem */
   /* for nondeterministic x or z is always T on paths or tchks */

   if ((xsp->ap[0] & 1L) == 0L && (xsp->bp[0] & 1L) == 0L)
    { __pop_xstk(); return(FALSE); }
   __pop_xstk();
  }
 return(TRUE);
}

/*
 * add a timing check to end of now data change routines
 * for processing at end of time slot (required by semantics)
 */
static void add_tchk_chged(struct chktchg_t *chkchgp)
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
 * routine to process all timing check violations at end of time slot
 * LOOKATME - this is maybe wrong because of recording of data event order?
 * AIV 10/15/09 - rewrote some of this routine
 *  - added chkactive_ofs - this is just a word flag - replaced chklastchg_ofs
 *    which held time 2 - words for 32-bit, plus better to check for 0 in 
 *    compiler
 * - got rid of inum (never used) 
 * - move lim1 = __get_del(tcp->tclim_du, tcp->tc_delrep) into each
 *   case stmt - better code
 */
extern void __process_all_tchk_violations(void)
{
 word64 diff, lim1, lim2, reftim;
 word64 *w64p;
 struct tc_pendlst_t *tcpendp;
 struct tchk_t *tcp, *tcp2;
 struct chktchg_t *chktcp;
 struct tchg_t *chgp;
 char s1[RECLEN], s2[RECLEN];
 struct itree_t *itp;

 for (tcpendp = __tcpendlst_hdr; tcpendp != NULL; tcpendp = tcpendp->tc_plnxt)
  {
   __idp = tcpendp->tc_idp;
   chktcp = tcpendp->tc_chkchgp;
   /* AIV 10/15/09 - need to set active flag back to FALSE */
   __idp[chktcp->chkactive_ofs] = FALSE;
   chgp = chktcp->startchgp;
   tcp = chgp->chgu.chgtcp;
   w64p = (word64 *) &(__idp[chgp->lastchg_ofs]);
   reftim = *w64p;
   diff = __simtime - reftim;
   /* notice no edge globals set but error before here if not simple delay */
   lim2 = 0ULL;
   switch ((byte) tcp->tchktyp) {
    case TCHK_SETUP:
     if (tcp->tc_supofsuphld)
      {
       /* added setup of setup hold needs limit from 1st lim of setuphold */
       /* because must be able to change both delays during sim */
       tcp2 = (struct tchk_t *) tcp->tclim_du.pdels;
       lim1 = __get_del(tcp2->tclim_du, tcp2->tc_delrep);
      }
     else lim1 = __get_del(tcp->tclim_du, tcp->tc_delrep);
     /* for setup if simultaneous change no violation */
     /* setup of setuphold also here with reversed for setup conns/lim1 */
     if (diff >= lim1 || diff == 0ULL) break;

emit_msg:
     bld_tchk_srcdump(__xs, tcp, &reftim, &__simtime, &lim1, &lim2);
     __gfwarn(566, tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt,
      "timing violation in %s (diff. %s)\n %s",
      __msg2_cur_blditree(s1), __to_timstr(s2, &diff), __xs);
     /* toggle notify reg if present */
     if (tcp->ntfy_np != NULL) process_notify(tcp->ntfy_np);
     if (__have_vpi_actions) 
      {
       itp = get_itp_();
       __vpi_tchkerr_trycall(tcp, itp);
      }
     break;
    case TCHK_SETUPHOLD:
     /* this is hold part of setup hold */
     lim2 = __get_del(tcp->tclim2_du, tcp->tc_delrep2);
     /* 2nd limit is hold part */
     lim1 = lim2;
     /* AIV 01/06/12 - this comment about 0 is wrong - modelsim also */
     /* includes these intra-time as violations */
     /* AIV 09/15/04 - difference of 0 must not cause check - see hold */
     /* if (diff < lim1 && diff != 0ULL) goto emit_msg; */
     if (diff < lim1) goto emit_msg;
     break;
    case TCHK_HOLD:
     lim1 = __get_del(tcp->tclim_du, tcp->tc_delrep);
     /* AIV 01/06/12 - this comment about 0 is wrong - modelsim also */
     /* includes these intra-time as violations */
     /* AIV 09/15/04 - difference of 0 must not cause check */
     /* if (diff < lim1 && diff != 0ULL) goto emit_msg; */
     if (diff < lim1) goto emit_msg;
     break;
    case TCHK_WIDTH:
     /* opposite edge data event less than limit after 1st edge ref., err */
     /* if time less than threshold, ignore very narrow pulses */
     /* if no threshold, will be set to 0, if same as threshold still err */
     if (tcp->tc_haslim2) lim2 = __get_del(tcp->tclim2_du, tcp->tc_delrep2);
     lim1 = __get_del(tcp->tclim_du, tcp->tc_delrep);

     /* ignore pulse width (ok) if less than lim2 (threshold) */
     /* ? think LRM says if occur simultaneously no change (threshhold 0) */
     if (diff < lim1 && diff >= lim2) goto emit_msg;
     break;
    case TCHK_PERIOD:
     /* same edge data event less than limit after 1st edge ref. */
     /* period error if clock period too narrow, no threshold */
     /* no separate reference event */
     /* must set reference event to now even if no violation */
     w64p = (word64 *) &(__idp[chgp->lastchg_ofs]);
     *w64p = __simtime;

     lim1 = __get_del(tcp->tclim_du, tcp->tc_delrep);
     /* notice if edge repeated in time slot, it is timing violation */
     if (diff < lim1) goto emit_msg;
     break;
    case TCHK_SKEW:
     /* if data event (2nd) more than limit after ref. 1st => err */
     /* skew error if date event too long after reference event */
     /* i.e. too much skew (lateness) of arriving signal */
     /* SJM 04/13/04 - if backward should be opposite of PERIOD above */
     lim1 = __get_del(tcp->tclim_du, tcp->tc_delrep);
     if (diff > lim1) goto emit_msg;
     break;
    case TCHK_RECREM:
     /* this is removal part of recrem */
     lim2 = __get_del(tcp->tclim2_du, tcp->tc_delrep2);
     /* 2nd limit is hold part */
     lim1 = lim2;
     if (diff < lim1 && diff != 0ULL) goto emit_msg;
     break;
    case TCHK_RECOVERY:
     /* SJM 01/16/04 - terminals reversed for rec part of recrem */
     if (tcp->tc_recofrecrem)
      {
       /* added setup of setup hold needs limit from 1st lim of setuphold */
       /* because must be able to change both delays during sim */
       tcp2 = (struct tchk_t *) tcp->tclim_du.pdels;
       lim1 = __get_del(tcp2->tclim_du, tcp2->tc_delrep);
      }
     else lim1 = __get_del(tcp->tclim_du, tcp->tc_delrep);

     /* if data event (2nd clock) occurs too soon after 1st (clear edge) */
     /* recovery like hold but error if reference event not edge */
     /* recovery err if clock happens too soon after clear or preset edge */
     if (diff < lim1 && diff != 0ULL) goto emit_msg;
     break;
    case TCHK_REMOVAL:
     /* if data event (2nd clock) does not occur soon enough after 1st */
     /* (clear edge) - removal like setup but error if reference event not */
     /* edge - removal err if clock happens too soon after clear or preset */
     /* edge */
     /* AIV 07/09/04 - removal test was reversed - was > but needs to be < */
     lim1 = __get_del(tcp->tclim_du, tcp->tc_delrep);
     if (diff < lim1 && diff != 0ULL) goto emit_msg;
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 __idp = NULL;
 /* must move all processed to front of free list */
 __tcpendlst_end->tc_plnxt = __tcpendfreelst;
 __tcpendfreelst = __tcpendlst_hdr;
 __tcpendlst_hdr = __tcpendlst_end = NULL;
}

/*
 * process end of time slot toggle changes 
 * - currently just turn on the 0->1/1->0 transitions
 *
 * if b part not 0, do not count in the toggle
 * SJM 10-30-12 - should put back the toggle counting
 *
 * SJM 06-30-13 - new tgl record on/off system tasks do not effect this
 * since tgl chg recording is independent and remembering toggle for
 * output report
 */
extern void __process_all_toggle_coverage(void)
{
 byte cursval, lastsval;
 int32 wlen, i, count10, count01, inum, bi, ubits;
 struct net_t *np;
 struct rt_tgl_t *togp, *togp2;
 byte *sbp;
 word32 val01, val10, tmpw, mask, tmpbw;
 word32 *curwp, *lastwp, *seen10wp, *seen01wp;
 word32 *cur_b_wp, *last_b_wp, *nwp;
 t_midat *idp;

 /* go through every net on the list */
 for (togp = __toggle_chghdr; togp != NULL; togp = togp2)
  {
   /* move to next and remove current from list when done */
   togp2 = togp->tognxt;
   togp->tognxt = NULL; 
   idp = togp->idp;
   np = togp->np;
   /* turn off on list flag */ 
   inum = idp[MD_INUM];
   np->ntgp->n_peri_tgl_on_se_list[inum] = FALSE;
   curwp = &(idp[np->nva_ofs]);
   lastwp = togp->last_valp;
   seen10wp = togp->seen10p;
   seen01wp = togp->seen01p;
   wlen = wlen_(np->nwid);
   if (!np->n_isavec)
    {
     cursval = curwp[0] & 3; 
     lastsval = lastwp[0] & 3; 
     if (cursval <= 2) 
      {
       /* 0 -> 1 */
       if (lastsval == 0 && cursval == 1) seen01wp[0] = TRUE;
       /* 1 -> 0 */
       else if (lastsval == 1 && cursval == 0) seen10wp[0] = TRUE;
      }

     /* scalar version if 100% coverage never add back to list */
     //AIV LOOKATME - if going to have count version - cannot do this
//SJM 10-30-12 - FIXME? - not sure what happen with new tgl on/off sys tasks */
     /* notice even though only low bit on, bit and will have 1 in low bit */  

     if (seen10wp[0] & seen01wp[0])
      {
       np->ntgp->n_peri_tgl_on_se_list[inum] = TRUE;
      }
     lastwp[0] = cursval;
    }
   /* handle the 2-state case */
   else if (togp->is_2state)
    {
     count10 = count01 = 0;
     i = 0;
     if (wlen > 1) 
      {
       for (; i < wlen-1; i++)
        {
         tmpw = curwp[i];
         val01 = (lastwp[i] | tmpw) & ~lastwp[i];
         seen01wp[i] |= val01;
//AIV LOOKATME - get count???
//       count01 += __builtin_popcountl(seen01wp[i]);
         val10 = (lastwp[i] | tmpw) & ~tmpw;
         seen10wp[i] |= val10;
//       count01 += __builtin_popcountl(seen10wp[i]);
         lastwp[i] =  tmpw;
        }
      }

     /* mask off the highbits to not over count */
     ubits = ubits_(np->nwid);
     tmpw = curwp[i];
     if (ubits != 0)
      {
       mask = __masktab[ubits];
       tmpw &= mask;
      }
     
     tmpw = curwp[i];
     val01 = (lastwp[i] | tmpw) & ~lastwp[i];
     seen01wp[i] |= val01;

//AIV LOOKATME - get count???
//   count01 += __builtin_popcountl(seen01wp[i]);
//
     val10 = (lastwp[i] | tmpw) & ~tmpw;
     seen10wp[i] |= val10;

//   count01 += __builtin_popcountl(seen10wp[i]);
     lastwp[i] =  tmpw;

// if 100% coverage never add back to list ?????
//   if ((count10+count01) == (2*np->nwid))
//   np->ntgp->n_peri_tgl_on_se_list[inum] = TRUE;
    }
   /* strength vector */
   else if (np->n_stren)
    {
     nwp = (word32 *) __my_malloc(wlen_(np->nwid)*WRDBYTES);
     memset(nwp, 0, wlen_(np->nwid)*WRDBYTES);
     sbp = (byte *) curwp;
     for (bi = 0; bi < np->nwid; bi++)
      {
       tmpw = (word32) sbp[bi];
       __lhsbsel(nwp, bi, tmpw & 1L);
      }
     count10 = count01 = 0;
     for (i = 0; i < wlen; i++)
      {
       val01 = (lastwp[i] | nwp[i]) & ~lastwp[i];
       seen01wp[i] |= val01;
//AIV LOOKATME - get count???
//     count01 += __builtin_popcountl(seen01wp[i]);
       val10 = (lastwp[i] | nwp[i]) & ~nwp[i];
       seen10wp[i] |= val10;
//     count01 += __builtin_popcountl(seen10wp[i]);
       lastwp[i] =  nwp[i];
      }
     __my_free(nwp, wlen_(np->nwid)*WRDBYTES);
//   if 100% coverage never add back to list ?????
//   if ((count10+count01) == (2*np->nwid))
//   np->ntgp->n_peri_tgl_on_se_list[inum] = TRUE;
    }
   else
    {
     /* mask off the highbits to not over count */
     cur_b_wp = &(curwp[wlen]);
     last_b_wp = &(lastwp[wlen]);
     count10 = count01 = 0;
     i = 0;
     if (wlen > 1) 
      {
       for (; i < wlen - 1; i++)
        {
         tmpw = curwp[i];
         tmpbw = cur_b_wp[i];
     
         val01 = (lastwp[i] | tmpw) & ~lastwp[i];
         val01 &= (~tmpbw);
         val01 &= (~last_b_wp[i]);
         seen01wp[i] |= val01;
//AIV LOOKATME - get count???
     //  count01 += __builtin_popcountl(seen01wp[i]);
         val10 = (lastwp[i] | tmpw) & ~tmpw;
         val10 &= (~tmpbw);
         val10 &= (~last_b_wp[i]);
         seen10wp[i] |= val10;
//       count01 += __builtin_popcountl(seen10wp[i]);

         lastwp[i] =  tmpw;
         last_b_wp[i] =  tmpbw;
        }
      }

     ubits = ubits_(np->nwid);
     tmpw = curwp[i];
     tmpbw = cur_b_wp[i];
     if (ubits != 0)
      {
       mask = __masktab[ubits];
       tmpw &= mask;
       tmpbw &= mask;
      }

     val01 = (lastwp[i] | tmpw) & ~lastwp[i];
     val01 &= (~tmpbw);
     val01 &= (~last_b_wp[i]);
     seen01wp[i] |= val01;
//AIV LOOKATME - get count???
//  count01 += __builtin_popcountl(seen01wp[i]);
     val10 = (lastwp[i] | tmpw) & ~tmpw;
     val10 &= (~tmpbw);
     val10 &= (~last_b_wp[i]);
     seen10wp[i] |= val10;

     lastwp[i] =  tmpw;
     last_b_wp[i] =  tmpbw;
//   count10 += __builtin_popcountl(seen10wp[i]);
//   if ((count10+count01) == (2*np->nwid))
//    np->ntgp->n_peri_tgl_on_se_list[inum] = TRUE;
    }
  }
 __toggle_chghdr = NULL;

 /* SJM 06-27-13 - reset toggle states to untoggled always */
 /* need to process tgl's normally so recording continues next tick as usual */
 /* SJM 06-27-13 - BEWARE - algorithm for non 2 state means no toggle */
 /* recorded until second transition because first will now be x to 0 or 1 */
 if (__se_reset_to_untgled)
  {
   __set_all_toggles_off();
   __se_reset_to_untgled = FALSE; 
   if (__verbose)
    {
     __cv_msg(
      "  $toggle_state_reset executed at %s - all recorded net toggles discarded.\n",
      __to_timstr(__xs, &__simtime));
    }
  }
}

/* LOOKATME - to match OVISIM x goes to 1 not 0 */
static const word32 ntfy_toggle_tab[] = {1, 0, 2, 1};

/*
 * process notify
 */
static void process_notify(struct net_t *np)
{
 struct xstk_t *xsp;
 word32 val;

 push_xstk_(xsp, np->nwid);
 __ld_wire_val_xstk(xsp, np);
 /* DBG remove */
 if (xsp->xslen != 1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 val = xsp->ap[0] | (xsp->bp[0] << 1);
 val = ntfy_toggle_tab[val];
 xsp->ap[0] = val & 1L;
 xsp->bp[0] = (val >> 1) & 1L;
 __chg_st_val(np, xsp->ap, xsp->bp);
 __pop_xstk();
}

/*
 * build a timing check source dump string with constants
 *
 * notice for setuphold (hold part) lim1 is correct lim2
 */
static char *bld_tchk_srcdump(char *s, struct tchk_t *tcp, word64 *tim1,
 word64 *tim2, word64 *lim1, word64 *lim2)
{
 int32 nd_rpar;
 char s1[RECLEN];

 __cur_sofs = 0;
 /* indicate whether setup or hold */
 if (tcp->tchktyp == TCHK_SETUPHOLD) __adds("hold(of setuphold)");
 else if (tcp->tc_supofsuphld) __adds("setup(of setuphold)");
 else if (tcp->tchktyp == TCHK_RECREM) __adds("removal(of recrem)");
 else if (tcp->tc_recofrecrem) __adds("recovery(of recrem)");
 else __adds(__to_tcnam(s1, tcp->tchktyp));

 __adds("(");
 if (tcp->startedge != NOEDGE || tcp->startcondx != NULL)
  { addch_('('); nd_rpar = TRUE; }
 else nd_rpar = FALSE;
 if (tcp->startedge != NOEDGE)
  { __adds(__to_edgenam(s1, tcp->startedge)); addch_(' '); }
 __adds(__msgexpr_tostr(s1, tcp->startxp));
 if (tcp->startcondx != NULL)
  { __adds(" &&& "); __adds(__msgexpr_tostr(s1, tcp->startcondx));  }
 if (nd_rpar) addch_(')');
 addch_(':');
 __adds(__to_timstr(s1, tim1));

 __adds(", ");
 if (tcp->chkedge != NOEDGE || tcp->chkcondx != NULL)
  { addch_('('); nd_rpar = TRUE; }
 else nd_rpar = FALSE;
 if (tcp->chkedge != NOEDGE)
  { __adds(__to_edgenam(s1, tcp->chkedge)); addch_(' '); }
 __adds(__msgexpr_tostr(s1, tcp->chkxp));
 if (tcp->chkcondx != NULL)
  { __adds(" &&& "); __adds(__msgexpr_tostr(s1, tcp->chkcondx));  }
 if (nd_rpar) addch_(')');
 addch_(':');
 __adds(__to_timstr(s1, tim2));

 __adds(", ");
 __adds(__to_timstr(s1, lim1));

 if ((tcp->tchktyp == TCHK_WIDTH || tcp->tchktyp == TCHK_PERIOD)
  && *lim2 != 0ULL)
  { __adds(", "); __adds(__to_timstr(s1, lim2)); }
 __adds(");");
 __trunc_exprline(MSGTRUNCLEN, FALSE);
 strcpy(s, __exprline);
 __cur_sofs = 0;
 return(s);
}

/*
 * ROUTINES TO INITIALIZE BEFORE START OF SIMULATION
 * TRICKY BEGINNING OF TIME 0 PROPOGATION HERE
 */

/*
 * initialization just before simulation start
 * need a dummy thread for functions on rhs of contas
 *
 * notice can execute statements from called conta rhs functions in here
 */
extern void __init_sim(void)
{
 char *sav_fnam;
 int i;
 struct thread_t *thp, *tail_thp, *head_thp;

 /* this is never called for resets, so initialize to no resets */
 __reset_count = 0;
 /* just set this to some value - task exec. always sets again */
 __reset_value = 0;

 init_stime();
 sav_fnam = __in_fils[0];
 __in_fils[0] = __pv_stralloc("**initialize none**");

 /* do not emit new message at time 0 since initialize time */
 __last_trtime = 0ULL;
 __last_evtrtime = 0ULL;

 __suspended_thd = NULL;
 __suspended_idp = NULL;
 __cur_thd = NULL;
 /* AIV 05/03/10 - add 128 threads init to the free list */
 /* will just get/put on free lists during sim better than malloc/free */
 thp = __alloc_thrd();
 tail_thp = head_thp = thp;
 for (i = 0; i < 127; i++)
  {
   thp = __alloc_thrd();
   tail_thp->thright = thp;
   tail_thp = thp;
  }
 __thd_freelst = head_thp;

 /* current inst. stack needs nil on bottom for debugging and must be empty */
 /* DBG remove -- */
 if (__itspi != -1) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* must leave instance stack exactly as is - cannot initialize */
 init_wires();
 __pv_stlevel = 0;

 /* initialize dumpvars state */
 __dv_calltime = 0ULL;
 __dv_seen = FALSE;
 __dv_state = DVST_NOTSETUP;
 __dv_dumplimit_size = 0;
 __dv_chgnethdr = NULL;
 __dv_hdr = __dv_end = NULL;

 /* initialize dumpports state */
 __dp_calltime = 0ULL;
 __dp_seen = FALSE;

 __in_fils[0] = sav_fnam;
 /* debugger source files go through last library file */
 __last_srcf = __last_lbf;
 /* putting any $input files on end since last_inf only needed for $input */
 /* from now on */
 /* resetting does not effect this */
 __last_inf = __last_lbf;

 /* last step is to setup interactive environment */
 /* needed since interactive setup stuff can be in source */
 __init_interactive();
 /* AIV 11/21/07 - need to dumpvars for all nets with +dumpvars flag */
 if (__dmpvars_all)
  {
   /* same as $dumpvars with no args */
   struct mdvmast_t *mdvp;
   mdvp = (struct mdvmast_t *) __my_malloc(sizeof(struct mdvmast_t));
   mdvp->mdv_levels = 0;
   mdvp->mdv_itprt_idp = NULL;
   mdvp->mdv_tskp = NULL;
   mdvp->mdv_np = NULL;
   mdvp->mdvnxt = NULL;
   __dv_hdr = __dv_end = mdvp;
   __slotend_action |= SE_DUMPVARS;
   __dv_isall_form = TRUE;
   __dv_seen = TRUE;
  }
 __run_state = SS_SIM;

 /* AIV 12/15/10 - init coverage event/stmt marking arrays */
 if (__event_coverage)
  {
   __event_covered = (word32 *) __my_malloc(sizeof(word32)*__dc_id_ndx);
   memset(__event_covered, 0, sizeof(word32)*__dc_id_ndx);
  }
 if (__stmt_coverage)
  {
   __stmt_covered = (word32 *) __my_malloc(sizeof(word32)*__stmt_id_ndx);
   memset(__stmt_covered, 0, sizeof(word32)*__stmt_id_ndx);
  }
}

/*
 * initial simulation time and variables
 */
static void init_stime(void)
{
 /* initialize the simulation realloced event table */
 /* because fibronacci growth start with small value */

 __cur_timehdr = (struct telhdr_t *) __my_malloc(sizeof(struct telhdr_t));
 __cur_timehdr->te_hdrp = NULL;
 __cur_timehdr->te_endp = NULL;

 __simtime = 0ULL;
 __cur_te_hdrp = __cur_te_endp = NULL;
 __p0_te_hdrp = __p0_te_endp = NULL;
 /* SJM 07/05/05 - also initialize non block current time after pnd0 queue */
 __nb_te_hdrp = __nb_te_endp = NULL;
 /* AIV 04/09/08 - set the non-blocking dummy headers */
 if (__compiled_sim)
  {
   __nb_te_hdrp = __nb_te_endp = &__nb_dummy_hd;
  }

 __tedpfreelst = NULL;
 __teputvfreelst = NULL;

 __num_init_events = 0;
 __num_proc_tevents = __num_cancel_tevents = 0;
 __inertial_cancels = __newval_rescheds = 0;
 __proc_thrd_tevents = 0;
 __num_netchges = 0;
 __num_switch_vtxs_processed = 0;
 __immed_assigns = 0;
 __strobe_hdr = __strobe_end = __strb_freelst = NULL;
 __monit_active = TRUE;
 __monit_dcehdr = NULL;
 __fmon_hdr = __fmon_end = NULL;
 __fmonse_hdr = __fmonse_end = __fmse_freelst = NULL;
 __nchg_futend = __nchg_futhdr = __nchgfreelst = NULL;
 /* AIV 04/09/08 - if compiled sim use the dummy net change headers */
 if (__compiled_sim)
  {
   __nchg_futhdr = __nchg_futend = &__nchg_dummy_hd;
  }
 /* SJM 08/16/03 - now need to start with lhs changed off */
 __lhs_changed = FALSE;
 __tcpendlst_end = __tcpendlst_hdr = __tcpendfreelst = NULL;
 __dltevfreelst = NULL;
 __cur_thd = NULL;
 /* tf one way pending event free list */
 __ltevfreelst = NULL;
 __wrkevtab = NULL;
 __last_wevti = -1;
 __size_wrkevtab = 0;
}

/*
 * after debugger :rerun command - do initialization
 */
extern void __reinit_sim(void)
{
 char *sav_fnam;

 /* another reset - needed first in case init code uses $reset_count */
 __reset_count++;

 /* for catching problems with incorrectly reset dces */
 /* DBG remove ---
 chk_schd_dces();
 --- */

 reinit_stime();

 sav_fnam = __in_fils[0];
 __in_fils[0] = __pv_stralloc("**initialize none**");

 /* no time 0 messages */
 __last_trtime = 0ULL;
 __last_evtrtime = 0ULL;

 /* current inst. stack needs nil on bottom for debugging */
 __cur_thd = NULL;
 __suspended_thd = NULL;
 __suspended_idp = NULL;
 /* must empty stack since may have been called from running code */
 __itspi = -1;
 __itstk[0] = NULL;
 __inst_ptr = NULL;
 __inst_mod = NULL;

 /* must leave instance stack exactly as is - cannot initialize */
 init_wires();
 __pv_stlevel = 0;

 /* reinitialize dumpvars state */
 __dv_calltime = 0ULL;
 __dv_seen = FALSE;
 __dv_state = DVST_NOTSETUP;
 __dv_dumplimit_size = 0;
 __dv_chgnethdr = NULL;
 __dv_hdr = __dv_end = NULL;
 __dv_isall_form = FALSE;

 /* reinitialize dumpports state */
 __dp_calltime = 0ULL;
 __dp_seen = FALSE;

 /* free and maybe close open command file - for reset will use start cmd_s */
 if (__cmd_s != NULL)
  {
   __my_fclose(__cmd_s);
   __cmd_s = NULL;
   __my_free(__cmd_fnam, strlen(__cmd_fnam) + 1);
   __cmd_fnam = NULL;
  }

 __in_fils[0] = sav_fnam;

 /* interactive environment must be left as is */
 __slotend_action = 0;

 /* things initialized in pv that need to be re-initialized */
 __next_dvnum = 0;
 /* reset interactive run state */
 __pending_enter_iact = FALSE;
 __iact_reason = IAER_UNKN;
 /* this will cause any -i file to be read on first iact entry */
 __ia_entered = FALSE;
 __cur_sofs = 0;
 __xspi = __itspi = __fcspi = -1;
 __inst_ptr = NULL;
 /* reinit $scope must start at first top level module */
 __scope_idp = __it_roots[0]->it_idp;
 __scope_tskp = NULL;
 __run_state = SS_SIM;
}

/*
 * reinitial simulation time and variables
 */
static void reinit_stime(void)
{
 __simtime = 0ULL;
 __cur_te_hdrp = __cur_te_endp = NULL;
 __p0_te_hdrp = __p0_te_endp = NULL;
 /* SJM 07/05/05 - also initialize non block current time after pnd0 queue */
 __nb_te_hdrp = __nb_te_endp = NULL;

 __num_init_events = 0;
 __num_proc_tevents = __num_cancel_tevents = 0;
 __inertial_cancels = __newval_rescheds = 0;
 __proc_thrd_tevents = 0;
 __num_netchges = 0;
 __immed_assigns = 0;
 __strobe_hdr = __strobe_end = NULL;
 __monit_active = TRUE;
 __monit_dcehdr = NULL;
 __fmon_hdr = __fmon_end = NULL;
 /* here leave the free list to reuse storage from there */
 __fmonse_hdr = __fmonse_end = NULL;

 /* SJM 08/16/03 - now need to start with lhs changed off */
 __lhs_changed = FALSE;

 /* notice must leave free lists - will begin by allocating from there */
 __nchg_futend = __nchg_futhdr = NULL;
 __tcpendlst_end = __tcpendlst_hdr = NULL;
 __cur_thd = NULL;

 /* must leave tevtab timing queue - free added o free list */
 /* num used stays same */
}

/*
 * initialize by scheduling a wire change for every wire driver
 * needs empty timing wheel header for delay 0 scheduling
 *
 * this needs to be run with all wire delays disabled
 * no PLI interaction here and run in SS_RESET or SS_LOAD run state
 */
static void init_wires(void)
{
 int32 ii;

 __wire_init = TRUE;
 /* go through list of 1 inst. corresponding to each top level module */
 /* ignore all delays in propagating from lhs's to rhs's */
 __nchg_futend = __nchg_futhdr = NULL;
 /* AIV 04/09/08 - init the net change dummy header events */
 if (__compiled_sim)
  {
   __nchg_futhdr = __nchg_futend = &__nchg_dummy_hd;
  }
 __initalw_thrd_hdr = NULL;

 /* SJM - 05/24/00 - must not process var changes until 0 normal #0 pt. */
 /* if (__nchg_futhdr != NULL) process_all_netchgs(); */

 for (ii = 0; ii < __numtopm; ii++)
  {
   init_itinsts(__it_roots[ii]);
   /* even though top modules can be linked by xmrs, do here can at worst */
   /* cause a few extra events to be processed from xmrs */
   /* SJM - 05/24/00 - must not process var changes until 0 normal #0 pt. */
   /* if (__nchg_futhdr != NULL) process_all_netchgs(); */
  }

 /* SJM 04/11/01 - initializing tran channels after drivers propagated */
 /* hard drivers as possible have changed */
 __init_all_trchans();

 __wire_init = FALSE;
 if (__ev_tracing)
  __tr_msg("\n>>>> wire initialization complete <<<<<\n");
}

/*
 * initialize all wires and threads in one itree instance
 * know that when storage for all wires allocated, also initialized
 *
 * algorithm is to evaluate every cont. assign (including cross module ports)
 * and gate/udp and schedule wire change at some point
 * this adds all no delay to netchg list and all delays are scheduledo
 * with pnd0's going on pnd0 list
 *
 * also allocate and schedules all behavioral initial/always threads
 * notice behavior force/assign can only occur during time 0 or later
 */
static void init_itinsts(struct itree_t *up_itp)
{
 int32 gi, pbi;
 int32 cai, ii;
 struct conta_t *cap;
 struct mod_t *mdp;
 struct itree_t *itp;

 if (__debug_flg)
  {
   __dbg_msg("== initializing wires in %s\n", __msg2_blditree(__xs, up_itp));
  }
 /* on entry know unprocessed net change list empty */
 mdp = up_itp->itip->imsym->el.emdp;
 
 __idp = up_itp->it_idp;
 /* schedule all behavioral threads for this instance */
 /* AIV 08/21/07 - if compiled sim need to link in enter address locations */
 if (__compiled_sim) init_cvc_sched_thd(mdp);
 else init_sched_thd(mdp);

 /* evaluate and schedule all gates in instance */
 for (gi = 0; gi < mdp->mgnum; gi++) gate_initeval(&(mdp->mgates[gi]));

 /* and all contas */
 for (cap = mdp->mcas, cai = 0; cai < mdp->mcanum; cai++, cap++)
  {
   /* SJM 09/28/02 - need to initialize the PB separated contas */
   if (cap->ca_pb_sim)
    {
     /* SJM 08/08/03 - for per bit sim form, need 2nd arg master conta */
     for (pbi = 0; pbi < cap->lhsx->szu.xclen; pbi++)
      { conta_initeval(&(cap->pbcau.pbcaps[pbi]), cap); }
    }
   else conta_initeval(cap, cap);
  }
 __idp = NULL;
 
 for (ii = 0; ii < mdp->minum; ii++)
  {
   itp = &(up_itp->in_its[ii]);
   /* force downward cross port continuous assign for inputs and inouts */
   __init_instdownport_contas(up_itp, itp);

   /* process depth first down one instance */
   init_itinsts(itp);

   /* force upward from down (after its processed) output/inout contas */
   __init_instupport_contas(itp);
  }
 __idp = NULL;
}

/*
 * build thread and schedule time 0 event for each initial always block
 * just goes into time 0 current time event list as if time move from -1
 *
 * if initial/always statement is named block will have unnamed block
 * put around it by here
 *
 * this requires cur. itp to be set to current place in itree
 */
static void init_sched_thd(struct mod_t *mdp)
{
 struct ialst_t *ialp;
 struct tev_t *tevp;
 struct thread_t *thp;
 struct telhdr_t *tw0;
 struct st_t *stp, *stp2;
 struct delctrl_t *dctp;

 /* each element in ia sts list is a possibly added unnamed begin block */
 /* each separate intial/always must be its own thread */
 /* because one blocking does not block others */
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   /* AIV 07/16/12 - new SV always_comb/alway_latch are always triggered */
   /* after initial blocks doing in new loop below */
   if (ialp->iatyp == ALWAYS_COMB || ialp->iatyp == ALWAYS_LATCH)
    continue;

   /* build the initial/always thread */
   /* build the event and allocate assoc. thread */
   alloc_cur_tev_(tevp, __process_thrd_ev, __tim_zero);
   stp = ialp->iastp;

   thp = __alloc_thrd();
   thp->th_ialw = TRUE;
   __cur_thd = thp;
   thp->thenbl_sfnam_ind = ialp->ia_first_ifi;
   thp->thenbl_slin_cnt = ialp->ia_first_lini;
   /* caller must alloc any event type specific fields, cannot assume NULL */
   tevp->tu.tethrd = thp;
   thp->thnxtstp = stp;
   thp->thpar = NULL;
   thp->th_idp = __idp;
   /* link on sequential list for rerun freeing */
   if (__initalw_thrd_hdr == NULL) __initalw_thrd_hdr = thp;
   else
    {
     thp->thright = __initalw_thrd_hdr;
     __initalw_thrd_hdr->thleft = thp;
     __initalw_thrd_hdr = thp;
    }

   /* this just causes all initial and always 1st statements to happen */
   /* at time 0 - know thnxtstp is just list of statements */
   if (__ev_tracing)
    {
     stp2 = tevp->tu.tethrd->thnxtstp;
     if (stp2 == NULL)
      {
       __tr_msg(
        "-- adding initial machine code thread for init/always at %s\n",
        __bld_lineloc(__xs, ialp->ia_first_ifi, ialp->ia_first_lini));
      }
     else
      {
       __tr_msg("-- adding initial procedural start at statement %s\n",
        __bld_lineloc(__xs, stp2->stfnam_ind, stp2->stlin_cnt));
      }
    }

   tw0 = __cur_timehdr;
   if (tw0->te_hdrp == NULL) tw0->te_hdrp = tw0->te_endp = tevp;
   else { tw0->te_endp->tenxtp = tevp; tw0->te_endp = tevp; }
   __num_init_events++;
   __cur_thd = NULL;
  }
 
 /* AIV 07/16/12 - new SV always_comb/alway_latch are always triggered */
 /* nearly identical as above loop just scheduling actual stmt events */ 
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   /* these are already handled in the first loop */
   if (ialp->iatyp != ALWAYS_COMB && ialp->iatyp != ALWAYS_LATCH)
    continue;

   /* better be a delay control to schedule time0 statement list */
   stp = ialp->iastp;
   /* DBG remove --- */
   if (stp->stmttyp != S_DELCTRL) __misc_terr(__FILE__, __LINE__);
   /* ----- */
  
   dctp = stp->st.sdc;
   stp2 = dctp->actionst;

   /* build the initial/always thread */
   /* build the event and allocate assoc. thread */
   alloc_cur_tev_(tevp, __process_thrd_ev, __tim_zero);

   thp = __alloc_thrd();
   thp->th_ialw = TRUE;
   __cur_thd = thp;
   thp->thenbl_sfnam_ind = ialp->ia_first_ifi;
   thp->thenbl_slin_cnt = ialp->ia_first_lini;
   /* caller must alloc any event type specific fields, cannot assume NULL */
   tevp->tu.tethrd = thp;
   thp->thnxtstp = stp2;
   thp->thpar = NULL;
   thp->th_idp = __idp;
   /* link on sequential list for rerun freeing */
   if (__initalw_thrd_hdr == NULL) __initalw_thrd_hdr = thp;
   else
    {
     thp->thright = __initalw_thrd_hdr;
     __initalw_thrd_hdr->thleft = thp;
     __initalw_thrd_hdr = thp;
    }

   if (__ev_tracing)
    {
     __tr_msg("-- adding always_comb/always_latch start at statement %s\n",
      __bld_lineloc(__xs, stp2->stfnam_ind, stp2->stlin_cnt));
    }

   tw0 = __cur_timehdr;
   if (tw0->te_hdrp == NULL) tw0->te_hdrp = tw0->te_endp = tevp;
   else { tw0->te_endp->tenxtp = tevp; tw0->te_endp = tevp; }
   __num_init_events++;
   __cur_thd = NULL;
  }
}

static void init_cvc_sched_thd(struct mod_t *mdp)
{
 struct ialst_t *ialp;
 struct thread_t *thp;
 struct tev_t *tevp;
 struct telhdr_t *tw0;
 struct st_t *stp, *stp2;
 struct delctrl_t *dctp;

 /* each element in ia sts list is a possibly added unnamed begin block */
 /* each separate intial/always must be its own thread */
 /* because one blocking does not block others */
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   /* AIV 07/16/12 - new SV always_comb/alway_latch are always triggered */
   /* after initial blocks doing in new loop below */
   if (ialp->iatyp == ALWAYS_COMB || ialp->iatyp == ALWAYS_LATCH)
    continue;

   /* build the initial/always thread */
   /* build the event and allocate assoc. thread */
   if (!ialp->needs_thread)
    {
     /* DBG remove --- */
     if (ialp->enterptr == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     alloc_cur_tev_(tevp, ialp->enterptr, __tim_zero);
    }
   else alloc_cur_tev_(tevp, __process_compiled_thrd_ev_enterp, __tim_zero);

   stp = ialp->iastp;

   thp = __alloc_thrd();
   thp->th_ialw = TRUE;
   __cur_thd = thp;
   thp->thenbl_sfnam_ind = ialp->ia_first_ifi;
   thp->thenbl_slin_cnt = ialp->ia_first_lini;
   /* caller must alloc any event type specific fields, cannot assume NULL */
   tevp->tu.tethrd = thp;
   thp->thnxtstp = stp;
   thp->thpar = NULL;
   thp->th_idp = __idp;
   /* link on sequential list for rerun freeing */
   if (__initalw_thrd_hdr == NULL) __initalw_thrd_hdr = thp;
   else
    {
     thp->thright = __initalw_thrd_hdr;
     __initalw_thrd_hdr->thleft = thp;
     __initalw_thrd_hdr = thp;
    }

   /* this just causes all initial and always 1st statements to happen */
   /* at time 0 - know thnxtstp is just list of statements */
   if (__ev_tracing)
    {
     stp2 = tevp->tu.tethrd->thnxtstp;
     if (stp2 == NULL)
      {
       __tr_msg(
        "-- adding initial machine code thread for init/always at %s\n",
        __bld_lineloc(__xs, ialp->ia_first_ifi, ialp->ia_first_lini));
      }
     else
      {
       __tr_msg("-- adding initial procedural start at statement %s\n",
        __bld_lineloc(__xs, stp2->stfnam_ind, stp2->stlin_cnt));
      }
    }

   tw0 = __cur_timehdr;
   if (tw0->te_hdrp == NULL) tw0->te_hdrp = tw0->te_endp = tevp;
   else { tw0->te_endp->tenxtp = tevp; tw0->te_endp = tevp; }
   __num_init_events++;
   __cur_thd = NULL;
  }

 /* AIV 07/16/12 - new SV always_comb/alway_latch are always triggered */
 /* nearly identical as above loop just scheduling actual stmt events */ 
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   /* these are already handled in the first loop */
   if (ialp->iatyp != ALWAYS_COMB && ialp->iatyp != ALWAYS_LATCH)
    continue;

   /* better be a delay control to schedule time0 statement list */
   stp = ialp->iastp;
   /* DBG remove --- */
   if (stp->stmttyp != S_DELCTRL) __misc_terr(__FILE__, __LINE__);
   /* ----- */
  
   dctp = stp->st.sdc;
   stp2 = dctp->actionst;

   /* build the initial/always thread */
   /* build the event and allocate assoc. thread */
   if (!ialp->needs_thread)
    {
     /* DBG remove --- */
     if (stp2->enterptr == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     alloc_cur_tev_(tevp, stp2->enterptr, __tim_zero);
    }
   else alloc_cur_tev_(tevp, __process_compiled_thrd_ev_enterp, __tim_zero);

   thp = __alloc_thrd();
   thp->th_ialw = TRUE;
   __cur_thd = thp;
   thp->thenbl_sfnam_ind = ialp->ia_first_ifi;
   thp->thenbl_slin_cnt = ialp->ia_first_lini;
   /* caller must alloc any event type specific fields, cannot assume NULL */
   tevp->tu.tethrd = thp;
   thp->thnxtstp = stp2;
   thp->thpar = NULL;
   thp->th_idp = __idp;
   /* link on sequential list for rerun freeing */
   if (__initalw_thrd_hdr == NULL) __initalw_thrd_hdr = thp;
   else
    {
     thp->thright = __initalw_thrd_hdr;
     __initalw_thrd_hdr->thleft = thp;
     __initalw_thrd_hdr = thp;
    }

   /* this just causes all initial and always 1st statements to happen */
   /* at time 0 - know thnxtstp is just list of statements */
   if (__ev_tracing)
    {
     __tr_msg("-- adding always_comb/always_latch start at statement %s\n",
      __bld_lineloc(__xs, stp2->stfnam_ind, stp2->stlin_cnt));
    }

   tw0 = __cur_timehdr;
   if (tw0->te_hdrp == NULL) tw0->te_hdrp = tw0->te_endp = tevp;
   else { tw0->te_endp->tenxtp = tevp; tw0->te_endp = tevp; }
   __num_init_events++;
   __cur_thd = NULL;
  }
}

/*
 * initialize gate by evaluating all inputs, changing wire if needed,
 * and if wire changed, propagate changes
 * called once for every gate in itree
 */
static void gate_initeval(struct gate_t *gp)
{
 int32 i, gid;

 /* evaluate gate - even if no change assign (this stores state) */
 /* if input value same, nothing to do */
 switch ((byte) gp->g_class) {
  case GC_LOGIC: init_logic_gate(gp); break;
  case GC_UDP: init_udp(gp); break;
  case GC_BUFIF: init_bufif_gate(gp); break;
  case GC_MOS:
   chg_mos_instate(gp, 1);
   chg_mos_instate(gp, 2);

   gid = gp->gmsym->el.eprimp->gateid;
   /* note here input change routine and eval separate */
   /* eval always evals even if new and old input are the same */
   if (gid == G_NMOS) __eval_nmos_gate(__idp[gp->gstate_ofs]);
   else if (gid == G_RNMOS) __eval_rnmos_gate(__idp[gp->gstate_ofs]);
   else if (gid == G_PMOS) __eval_pmos_gate(__idp[gp->gstate_ofs]);
   else if (gid == G_RPMOS) __eval_rpmos_gate(__idp[gp->gstate_ofs]);
   else __case_terr(__FILE__, __LINE__);
   break;
  case GC_CMOS:
   chg_mos_instate(gp, 1);
   chg_mos_instate(gp, 2);
   chg_mos_instate(gp, 3);
   /* note here input change routine and eval separate */
   /* eval always evals even if new and old input are the same */
   __eval_cmos_gate(gp);
   break;
  case GC_PULL:
   /* each port is pull wire */
   /* this is needed since probably all drivers tristate at time 0 */
   /* but pull must start at time 0 */
   /* notice no output here so starts at 0 not 1 (normally 0 output) */
   for (i = 0; i < (int32) gp->gpnum; i++)
    __mdr_assign_or_sched(gp->gpins[i]);
   if (__debug_flg)
    {
     __dbg_msg("-- all connections of pull %s evalutated for initialization\n",
     to_cur_evtronam(__xs, gp->gsym->synam, (struct task_t *) NULL));
    }
   return;
  case GC_TRANIF: init_tranif_gate(gp); return;
  /* nothing to do for trans */
  case GC_TRAN: return;
  default: __case_terr(__FILE__, __LINE__);
 }

 if (__debug_flg && __ev_tracing)
  {
   char s1[RECLEN];

   if (gp->g_class == GC_UDP) strcpy(s1, "udp"); else strcpy(s1, "gate");
   /* notice during wire init all wire delays off */
   __tr_msg("-- %s %s %s assign initialized to state:\n",
    gp->gmsym->synam, s1, to_cur_evtronam(__xs, gp->gsym->synam, 
     (struct task_t *) NULL));
   __tr_msg("   %s\n", __gstate_tostr(__xs, gp, FALSE));
  }
 /* must always immediately assign to wire */
 /* must store new gate value into state here - value does not have stren */
 if (__compiled_sim && gp->gpnum <= 15 && gp->gate_out_ofs != -1)
  {
   __idp[gp->gate_out_ofs] = __new_gateval;
  }
 __change_gate_outwire(gp);
}

/*
 * initialize udps
 * 1) evaluate all udp input exprs in case constant (update wide signature)
 * 2) if has initial value, set new gate value to initial and do not eval
 * 3) if no initial value, force evaluate to get new gate value
 * for sequential use combinatorial table
 *
 * for wide this updates signature to x that is then adjusted by
 * storing gate output that always happens during init.
 *
 * notice that for gpins, 0 is output and first input is 1
 * but values in upd state word32 are input 0 in low 2 bits, and high (maybe
 * output if sequential) in high 2 bits
 */
static void init_udp(struct gate_t *gp)
{
 int32 i, nins;
 int32 out_chg;
 word32 wide_ival, new_inputval, *wp;
 struct xstk_t *xsp;
 extern const word32 __to_noztab[];
 extern const word32 __to_uvaltab[];

 __cur_udp = gp->gmsym->el.eudpp;
 /* for level, this includes state */
 nins = __cur_udp->numins;
 if (!__cur_udp->u_wide)
  {
   /* here can ingore old state (if present) since just over-written */
   wp = &(__idp[gp->gstate_ofs]);
   /* eval and store all inputs in case constant expr. */
   for (i = 0; i < nins; i++)
    {
     xsp = __eval_xpr(gp->gpins[i + 1]);
     new_inputval = __to_noztab[(xsp->ap[0] & 1L) | ((xsp->bp[0] & 1L) << 1)];
     __pop_xstk();
     /* know z will always cause new input value */
     /* change the input */
     wp[0] &= ~(3L << (2*i));
     wp[0] |= ((hword) new_inputval << (2*i));
     /* -- RELEASE remove ---
     if (__debug_flg)
      __dbg_msg("-- udp init after %dth input wp=%lx\n", i, wp[0]);
     -- */
    }
   /* -- RELEASE remove --
   if (__debug_flg)
    __dbg_msg("-- narrow before init eval: wp=%lx\n", wp[0]);
   -- */
  }
 else
  {
   /* in wide, case need 2nd running value index word32 */
   wp = &(__idp[gp->gstate_ofs]);
   for (i = 0; i < nins; i++)
    {
     /* remove signature contribution from initialized value */
     wide_ival = __to_uvaltab[((wp[0] >> (2*i)) & 3L)];
     wp[1] -= wide_ival*__pow3tab[i];

     xsp = __eval_xpr(gp->gpins[i + 1]);
     /* think evaluate can be wide thing that must be truncated */
     new_inputval = __to_noztab[(xsp->ap[0] & 1L) | ((xsp->bp[0] & 1L) << 1)];
     __pop_xstk();
     wp[0] &= ~(3L << (2*i));
     wp[0] |= (new_inputval << (2*i));

     /* add in new input signature value */
     wide_ival = __to_uvaltab[new_inputval];
     wp[1] += wide_ival*__pow3tab[i];
    }
   /* -- RELEASE remove ---
   if (__debug_flg)
     __dbg_msg("-- wide before init eval: w0=%lx, w1=%lu\n", wp[0], wp[1]);
   -- */
  }
 /* know combinatorial will never have initial value */
 if (__cur_udp->ival == NO_VAL)
  {
   /* change old input 0 to force evaluation - new replace set wrong */
   if (!__cur_udp->u_wide)
    {
     wp = &(__idp[gp->gstate_ofs]);
     new_inputval = (word32) (wp[0] & 3L);
     if (new_inputval == 0) new_inputval = 3; else new_inputval = 0;
     wp[0] &= ~(3L);
     wp[0] |= (hword) new_inputval;
    }
   else
    {
     wp = &(__idp[gp->gstate_ofs]);
     new_inputval = wp[0] & 3L;
     /* subtract out old signature contribution */
     wide_ival = __to_uvaltab[new_inputval];
     wp[1] -= wide_ival*__pow3tab[0];

     if (new_inputval == 0) new_inputval = 2; else new_inputval = 0;
     wp[0] &= ~(3L);
     wp[0] |= new_inputval;

     /* add in new input signature value */
     wide_ival = __to_uvaltab[new_inputval];
     wp[1] += wide_ival*__pow3tab[0];
    }
   /* this sets new gate value */
   __eval_udp(gp, 1, &out_chg, FALSE);
  }
 else __new_gateval = __cur_udp->ival;
 /* caller will store or schedule store into output connection */
}

/*
 * initialize logic gate by evaluating all inputs then forcing eval of
 * logic gate - not for buf and mos types gates
 */
static void init_logic_gate(struct gate_t *gp)
{
 int32 i;
 int32 srep, nins;
 int32 out_chg;
 struct xstk_t *xsp;

 if (gp->gpnum > 16) srep = SR_VEC; else srep = SR_PVEC;

 /* tricky part must - make sure input 0 does not eval the same */
 /* simply invert b bit of input 0 result */
 nins = gp->gpnum - 1;
 for (i = 0; i < nins; i++)
  {
   xsp = __eval_xpr(gp->gpins[i + 1]);
   xsp->ap[0] &= 1L;
   xsp->bp[0] &= 1L;
   if (i == 0) xsp->bp[0] = (~xsp->bp[0]) & 1L;
   gate_st_bit(&(__idp[gp->gstate_ofs]), (int32) gp->gpnum, i, srep, 
    xsp->ap[0], xsp->bp[0]);
   __pop_xstk();
  }
 /* know reevaluating 1st input will result in new value so will eval. */
 __eval_logic_gate(gp, 1, &out_chg);
 /* wire assign in caller */
}

/*
 * initialize a bufif style gate
 * evaluate both inputs and change gate state for data to opposite
 *
 * storage: low 2 bits data in, next 2 control in - next 8 out strength
 * stored as half word
 */
static void init_bufif_gate(struct gate_t *gp)
{
 int32 out_chg;
 word32 *wp;
 struct xstk_t *xsp;

 wp = &(__idp[gp->gstate_ofs]);
 xsp = __eval_xpr(gp->gpins[1]);
 xsp->ap[0] &= 1L;
 xsp->bp[0] &= 1L;
 /* invert to force eval */
 xsp->bp[0] = (~xsp->bp[0]) & 1L;
 wp[0] &= ~3L;
 wp[0] |= ((hword) (xsp->ap[0] | (xsp->bp[0] << 1)));
 __pop_xstk();

 xsp = __eval_xpr(gp->gpins[2]);
 xsp->ap[0] &= 1L;
 xsp->bp[0] &= 1L;
 wp[0] &= ~(3L << 2);
 wp[0] |= ((hword) ((xsp->ap[0] | (xsp->bp[0] << 1)) << 2));
 __pop_xstk();
 /* eval. 1st input in gpins - index 1 */
 __eval_bufif_gate(gp, 1, &out_chg);
}

/*
 * initialize the state of a tranif gate by evaluating control input
 * here must evaluate input and store into state
 * for tran, do not need any initialization
 */
static void init_tranif_gate(struct gate_t *gp)
{
 int32 conducting, gateid, bi, inum;
 word32 cval;
 struct xstk_t *xsp;

 /* first initialize conducting state */
 xsp = __eval_xpr(gp->gpins[2]);
 conducting = (xsp->ap[0] & 1L) | ((xsp->bp[0] & 1L) << 1);
 if (conducting == 2) conducting = 3;
 __pop_xstk();
 gateid = gp->gmsym->el.eprimp->gateid;
 /* for if0s, 0 turns on (1), 1 of (0) */
 if (gateid == G_TRANIF0 || gateid == G_RTRANIF0)
  {
   if (conducting == 0) conducting = 1;
   else if (conducting == 1) conducting = 0;
  }

 /* immediate change to conducting state during initialization */
 inum = get_inum_();
 bi = get_bofs_(2*inum);
 cval = __idp[gp->gstate_ofs];
 cval &= ~(3L << bi);
 cval |= (conducting << bi);
 __idp[gp->gstate_ofs] = cval;

 if (__debug_flg && __ev_tracing)
  {
   __tr_msg("-- %s %s 3rd input evaluated - initial conducting: %s\n",
    gp->gmsym->synam, to_cur_evtronam(__xs, gp->gsym->synam, 
    (struct task_t *) NULL), (conducting == 1) ? "*ON*"
     : ((conducting == 0) ? "*OFF*" : "*UNKNOWN*"));
  }
}

/*
 * evaluate continous assign to initialize lhs
 * notice ignore conta delay here but use wire delay
 *
 * SJM 09/28/02 - for per bit rhs concat contas, caller passed decomposed PB
 */
static void conta_initeval(struct conta_t *cap, struct conta_t *mast_cap)
{
 int32 lhslen, orhslen;
 byte *sbp;
 struct xstk_t *xsp, *xsp2;
 struct expr_t *xp, *lhsxp;
 struct sy_t *syp;

 /* do not need to set lhs here before schedule changed */
 xp = cap->rhsx;
 lhsxp = cap->lhsx;
 /* if rhs normal function must call it in case of constant args */
 /* but $getpattern must just assign right width x's since index probably */
 /* out of range at this point */
 if (xp->optyp == FCALL)
  {
   syp = xp->lu.x->lu.sy;
   /* know getpat conta form never has rhsval wp or driver wp */
   /* rule is that $getpattern with unknown index is x's */
   if (syp->sytyp == SYM_SF && syp->el.esyftbp->syfnum == STN_GETPATTERN)
    {
     lhslen = lhsxp->szu.xclen;
     push_xstk_(xsp, lhslen);
     /* IN - getpattern with unknown index (like at init) return x value */
     one_allbits_(xsp->ap, lhslen);
     one_allbits_(xsp->bp, lhslen);

     /* know all getpat lhs wires fi == 1 and no wire delay and no stren */
     __exec_ca_concat(lhsxp, xsp->ap, xsp->bp, FALSE);
     __pop_xstk();
     return;
    }
  }

 lhslen = lhsxp->szu.xclen;
 xsp = __eval_xpr(xp);
 if (xsp->xslen != lhslen)
  {
   orhslen = xsp->xslen;

   /* SJM 09/29/03 - change to handle sign extension and separate types */
   if (xsp->xslen > lhslen) __narrow_sizchg(xsp, lhslen);
   else if (xsp->xslen < lhslen)
    {
     if (xp->has_sign) __sgn_xtnd_widen(xsp, lhslen);
     else __sizchg_widen(xsp, lhslen);
    }
   /* during initialization widen to x not 0 */

   /* SJM 05/19/04 - remove see below must widen rhs expr using 0's */
   /* --
   if (orhslen < xsp->xslen)
    {
     if (__wire_init) __fix_widened_toxs(xsp, orhslen);
    }
   -- */
  }

 /* fi == 1 and no delay contas have no driver state stored */
 if (cap->ca_drv_ofs != 0)
  {
   /* SJM - 02/18/03 - remove - since above does same change so never exec */
   /* --- REMOVED
   if (xsp->xslen != lhslen)
    {
     orhslen = xsp->xslen;

     -* SJM 09/29/03 - change to handle sign extension and separate types *-
     if (xsp->xslen > lhslen) __narrow_sizchg(xsp, lhslen);
     else if (xsp->xslen < lhslen)
      {
       if (xp->has_sign) __sgn_xtnd_widen(xsp, lhslen);
       else __sizchg_widen(xsp, lhslen);
      }

     __fix_widened_toxs(xsp, orhslen);
    }
   -- */
   __st_idp_val(&(__idp[cap->ca_drv_ofs]), lhslen, xsp->ap, xsp->bp);
  }
 if (__debug_flg && __ev_tracing)
  {
   char s1[RECLEN];

   /* notice even if delay wire, off during wire initialization */
   strcpy(s1, "assigned");
   __tr_msg("-- %s %s initial value %s\n", s1, to_cur_evtrcanam(__xs, mast_cap),
    __regab_tostr(__xs2, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE));
  }

 /* notice multi-fi case assume new driving value already assigned */
 /* this will add any conta driving strength if needed from ca drv wp */
 if (lhsxp->x_multfi) __mdr_assign_or_sched(lhsxp);
 else
  {
   /* notice wire delays including specify paths off during wire init */
   if (lhsxp->x_stren)
    {
     push_xstk_(xsp2, 4*lhslen);
     sbp = (byte *) xsp2->ap;
     __st_standval(sbp, xsp, cap->ca_stval);
     if (lhsxp->optyp == LCB) __stren_exec_ca_concat(lhsxp, sbp, FALSE);
     /* SJM 03/30/99 - was storing value without strength added */
     else __exec_conta_assign(lhsxp, xsp2->ap, xsp2->bp, FALSE);
     __pop_xstk();
    }
   else
    {
     if (lhsxp->optyp == LCB)
      __exec_ca_concat(lhsxp, xsp->ap, xsp->bp, FALSE);
     else __exec_conta_assign(lhsxp, xsp->ap, xsp->bp, FALSE);
    }
  }
 __pop_xstk();
}

#ifdef __STREE__
/*
 * MEDIUM LEVEL SCHEDULING MECHANISM ROUTINES
 * RB TIMING TREE SCHEDULE ROUTINES
 */
/*
 * insert an event into the timing rb tree
 */
extern void __insert_event(struct tev_t *tevp)
{
 struct tqnode_t *nodep, *pn;
 word64 schtime;

 schtime = tevp->etime;
 /* the tree is empty just insert event as root */
 if (__min_time_node == SENTINEL) 
  {
   nodep = alloc_node(schtime);
   /* root node is black */
   nodep->color = BLACK;
   __min_time_node = nodep;
   __max_time_node = nodep;
   __tree_root = nodep; 
   tevp->teprevp = NULL;
   nodep->te_hdrp = nodep->te_endp = tevp;
   tevp->nodep = nodep;
   return;
  }
 /* if the scheduled time is less than the min time node insert as min */
 else if (schtime < __min_time_node->time)
  {
   nodep = alloc_node(schtime);
   pn = __min_time_node;
   nodep->parent = pn;
   pn->left = nodep;
   /* insert as min node */
   rb_insert_min(nodep);
   tevp->teprevp = NULL;
   nodep->te_hdrp = nodep->te_endp = tevp;
   /* save min node */
   __min_time_node = nodep;
   tevp->nodep = nodep;
   return;
  }
 /* if the scheduled time is > max time node insert as max node */
 else if (schtime > __max_time_node->time)
  {
   nodep = alloc_node(schtime);
   pn = __max_time_node;
   nodep->parent = pn;
   pn->right = nodep;
   // insert max node 
   rb_insert_max(nodep);
   tevp->teprevp = NULL;
   nodep->te_hdrp = nodep->te_endp = tevp;
   // save max node 
   __max_time_node = nodep;
   tevp->nodep = nodep;
   return;
  }
 /* scheduled time is in the middle of the tree and a search is done  */
 else if ((nodep = find_time(schtime, &(pn))) == SENTINEL)
  {
   nodep = alloc_node(schtime);
   nodep->parent = pn;

   if (schtime < pn->time) pn->left = nodep;
   else pn->right = nodep;

   /* insert middle node */
   rb_insert_middle(nodep);

   tevp->teprevp = NULL;
   //tevp->tenxtp = NULL;
   nodep->te_hdrp = nodep->te_endp = tevp;
   tevp->nodep = nodep;
   return;
  }
 else
  {
   tevp->nodep = nodep;
   /* AIV 10/15/07 - may now be empty if all nodes are linked out */
   if (nodep->te_endp == NULL)  
    { 
     tevp->teprevp = NULL;
     /* AIV 10/25/07 - if this is the current event don't set the next */
     /* to NULL perhaps processing should save the next point???? */
     /* AIV LOOKATME - this not positive that allowing __cur_tevp == tevp */
     /* works everytime */
     if (__cur_tevp != tevp) tevp->tenxtp = NULL;
     nodep->te_hdrp = nodep->te_endp = tevp; 
    }
   else if (tevp->vpi_onfront)  
    { 
     tevp->teprevp = NULL;
     tevp->tenxtp = nodep->te_hdrp; 
     nodep->te_hdrp = tevp; 
    }
   else
    { 
     tevp->teprevp = nodep->te_endp;
     nodep->te_endp->tenxtp = tevp; 
     nodep->te_endp = tevp; 
     /* AIV 10/17/07 - if this is the current event don't set the next */
     /* to NULL perhaps processing should save the next point???? */
     /* AIV LOOKATME - this not positive that allowing __cur_tevp == tevp */
     /* works everytime */
     if (__cur_tevp != tevp) tevp->tenxtp = NULL;
    }
  }
}

/*
 * add a non-blocking event to the non-blocking time list
 * exact same as above expect adding to nb list and not doubly linked
 */
extern void __insert_event_nb(struct tev_t *tevp)
{
 struct tqnode_t *nodep, *pn;
 word64 schtime;

 schtime = tevp->etime;
 /* the tree is empty just insert event as root */
 if (__min_time_node == SENTINEL) 
  {
   nodep = alloc_node(schtime);
   /* root node is black */
   nodep->color = BLACK;
   __min_time_node = nodep;
   __max_time_node = nodep;
   __tree_root = nodep; 
   nodep->nb_hdrp = nodep->nb_endp = tevp;
   tevp->nodep = nodep;
   return;
  }
 /* if the scheduled time is less than the min time node insert as min */
 else if (schtime < __min_time_node->time)
  {
   nodep = alloc_node(schtime);
   pn = __min_time_node;
   nodep->parent = pn;
   pn->left = nodep;
   /* insert as min node */
   rb_insert_min(nodep);
   nodep->nb_hdrp = nodep->nb_endp = tevp;
   /* save min node */
   __min_time_node = nodep;
   tevp->nodep = nodep;
   return;
  }
 /* if the scheduled time is > max time node insert as max node */
 else if (schtime > __max_time_node->time)
  {
   nodep = alloc_node(schtime);
   pn = __max_time_node;
   nodep->parent = pn;
   pn->right = nodep;
   // insert max node 
   rb_insert_max(nodep);
   nodep->nb_hdrp = nodep->nb_endp = tevp;
   // save max node 
   __max_time_node = nodep;
   tevp->nodep = nodep;
   return;
  }
 /* scheduled time is in the middle of the tree and a search is done  */
 else if ((nodep = find_time(schtime, &(pn))) == SENTINEL)
  {
   nodep = alloc_node(schtime);
   nodep->parent = pn;

   if (schtime < pn->time) pn->left = nodep;
   else pn->right = nodep;

   /* insert middle node */
   rb_insert_middle(nodep);

   nodep->nb_hdrp = nodep->nb_endp = tevp;
   tevp->nodep = nodep;
   return;
  }
 else
  {
   tevp->nodep = nodep;
   /* AIV 10/15/07 - may now be empty if all nodes are linked out */
   if (nodep->nb_endp == NULL)  
    { 
     tevp->teprevp = NULL;
     /* AIV 10/25/07 - if this is the current event don't set the next */
     /* to NULL perhaps processing should save the next point???? */
     /* AIV LOOKATME - this not positive that allowing __cur_tevp == tevp */
     /* works everytime */
     if (__cur_tevp != tevp) tevp->tenxtp = NULL;
     nodep->nb_hdrp = nodep->nb_endp = tevp; 
    }
   else if (tevp->vpi_onfront)  
    { 
     tevp->tenxtp = nodep->nb_hdrp; 
     nodep->nb_hdrp = tevp; 
    }
   else
    { 
     nodep->nb_endp->tenxtp = tevp; 
     nodep->nb_endp = tevp; 
     /* AIV 10/17/07 - if this is the current event don't set the next */
     /* to NULL perhaps processing should save the next point???? */
     /* AIV LOOKATME - this not positive that allowing __cur_tevp == tevp */
     /* works everytime */
     if (__cur_tevp != tevp) tevp->tenxtp = NULL;
    }
  }
}

/*
 * binary search of the timing tree to find node of time t
 * places the parent node into pn
 */
static struct tqnode_t *find_time(word64 t, struct tqnode_t **pn)
{
 struct tqnode_t *n;
 struct tqnode_t *par; 

 par = SENTINEL;
 for (n = __tree_root; n != SENTINEL; ) 
  {
   par = n;
   if (t == n->time) return(n);
   if (t < n->time) n = n->left;
   else n = n->right;
  }
 *pn = par;
 return(SENTINEL);
}

/*
 * rotate left
 */
static void left_rotate(struct tqnode_t *x)
{
 struct tqnode_t *y;

 y = x->right;
 x->right = y->left;

 if (y->left != SENTINEL) y->left->parent = x;

 y->parent = x->parent;
 if (x->parent == SENTINEL) __tree_root = y; 
 else if (x == x->parent->left) x->parent->left = y;
 else x->parent->right = y;

 y->left = x;
 x->parent = y;
}

/*
 * rotate right for max insert
 */
static void left_rotate_max(struct tqnode_t *x)
{
 struct tqnode_t *y;

 y = x->right;
 x->right = y->left;

 if (y->left != SENTINEL) y->left->parent = x;

 y->parent = x->parent;
 if (x->parent == SENTINEL) __tree_root = y; 
 else x->parent->right = y;

 y->left = x;
 x->parent = y;
}

/*
 * rotate right
 */
static void right_rotate(struct tqnode_t *x)
{
 struct tqnode_t *y;

 y = x->left;
 x->left = y->right;
 if (y->right != SENTINEL) y->right->parent = x;
 y->parent = x->parent;
 if (x->parent == SENTINEL) __tree_root = y;
 else if (x == x->parent->right) x->parent->right = y;
 else x->parent->left = y;

 y->right = x;
 x->parent = y;
}

/*
 * rotate right for min node insert
 */
static void right_rotate_min(struct tqnode_t *x)
{
 struct tqnode_t *y;

 y = x->left;
 x->left = y->right;

 if (y->right != SENTINEL) y->right->parent = x;

 y->parent = x->parent;
 if (x->parent == SENTINEL) __tree_root = y;
 else x->parent->left = y;

 y->right = x;
 x->parent = y;
}

/*
 * regular insert (not min/max time) 
 * regular rb insert of node into a tree (hanles all cases)
 */
static void rb_insert_middle(struct tqnode_t *n)
{
 struct tqnode_t *y;

 while (n != __tree_root && n->parent->color == RED) 
  {
   if (n->parent == n->parent->parent->left)
    {
     y = n->parent->parent->right; 
     if (y != SENTINEL && y->color == RED)
      {
       n->parent->color = BLACK;
       y->color = BLACK;
       n->parent->parent->color = RED;
       n = n->parent->parent;
      }
     else
      {
       if (n == n->parent->right)
        {
         n = n->parent;
         left_rotate(n);
        }
       n->parent->color = BLACK;
       n->parent->parent->color = RED;
       right_rotate(n->parent->parent);
      }
    }
   else
    {
     y = n->parent->parent->left; 
     if (y != SENTINEL && y->color == RED)
      {
       n->parent->color = BLACK;
       y->color = BLACK;
       n->parent->parent->color = RED;
       n = n->parent->parent;
      }
     else
      {
       if (n == n->parent->left)
        {
         n = n->parent;
         right_rotate(n);
        }
       n->parent->color = BLACK;
       n->parent->parent->color = RED;
       left_rotate(n->parent->parent);
      }
    }
  }
 __tree_root->color = BLACK;
}

/*
 * min insert of a node (node is known to be min time)
 */
static void rb_insert_min(struct tqnode_t *n)
{
 struct tqnode_t *y;

 while (n != __tree_root && n->parent->color == RED) 
  {
   y = n->parent->parent->right; 
   if (y != SENTINEL && y->color == RED)
    {
     n->parent->color = BLACK;
     y->color = BLACK;
     n->parent->parent->color = RED;
     n = n->parent->parent;
    }
   else
    {
     n->parent->color = BLACK;
     n->parent->parent->color = RED;
     right_rotate_min(n->parent->parent);
    }
  }
 __tree_root->color = BLACK;
}

/*
 * max insert of a node (node is known to be max time)
 */
static void rb_insert_max(struct tqnode_t *n)
{
 struct tqnode_t *y;

 while (n != __tree_root && n->parent->color == RED) 
  {
   y = n->parent->parent->left; 
   if (y != SENTINEL && y->color == RED)
    {
     n->parent->color = BLACK;
     y->color = BLACK;
     n->parent->parent->color = RED;
     n = n->parent->parent;
    }
   else
    {
     n->parent->color = BLACK;
     n->parent->parent->color = RED;
     left_rotate_max(n->parent->parent);
    }
  }
 __tree_root->color = BLACK;
}


/*
 * move the actual time
 * - get the minimum node time returning tevp index
 * - update __min_time_node to be the new min time node
 * - set __sim_time from __min_time_node
 * - remove current __min_time_node and update tree
 */
static struct tev_t *move_time(void)
{
 struct tqnode_t *nodep; 
 struct tqnode_t *rightp, *parentp;
 struct tev_t *tevp;

 /* get the minimum node info */
 nodep = __min_time_node;
 tevp = __cur_te_hdrp = nodep->te_hdrp;
 __cur_te_endp = nodep->te_endp;
 /* time is just the minimum node */
 __simtime = nodep->time;

 /* DBG remove ---
  if (nodep == SENTINEL) __misc_terr(__FILE__, __LINE__);
 ---- */

 /* get the new minimum time node */
 rightp = nodep->right;
 parentp = nodep->parent;
 /* if has a right child it is the new minimum node otherwise the par is */
 if (rightp != SENTINEL) __min_time_node = rightp;
 else  __min_time_node = parentp;

 rightp->parent = parentp;

 /* parent is null make the right node the new root */
 if (parentp == SENTINEL)
  {
   rightp->color = BLACK;
   __tree_root = rightp;
  }
 else 
  {
   /* remove the node with a rb fixup if needed */
   parentp->left = rightp;
   if (nodep->color == BLACK) rb_delete_min_fixup(rightp);
  }

 /* save the freed node for reuse */
 if (__free_node_ndx == __free_node_size)
  {
   grow_free_nodes();
  }
 __free_nodes[__free_node_ndx++] = nodep;
 return(tevp);
}

extern struct tev_t *__move_compiled_time(void)
{
 struct tqnode_t *nodep; 
 struct tqnode_t *rightp, *parentp;
 struct tev_t *tevp;

 /* get the minimum node info */
 nodep = __min_time_node;
 __nb_te_hdrp = nodep->nb_hdrp;
 __nb_te_endp = nodep->nb_endp;
 tevp = nodep->te_hdrp;
 /* AIV 10/15/07 - may now be empty if all nodes are linked out */
 if (tevp != NULL)
  {
   __cur_te_hdrp = tevp;
   __cur_te_endp = nodep->te_endp;
   __cur_te_endp->tenxtp = __free_event_tevp;
  }
 else if (__nb_te_hdrp != NULL)
  {
   tevp = __free_event_tevp;
  }

 /* time is just the minimum node */
 __simtime = nodep->time;

 /* DBG remove ---
  if (nodep == SENTINEL) __misc_terr(__FILE__, __LINE__);
 ---- */

 /* get the new minimum time node */
 rightp = nodep->right;
 parentp = nodep->parent;
 /* if has a right child it is the new minimum node otherwise the par is */
 if (rightp != SENTINEL) __min_time_node = rightp;
 else  __min_time_node = parentp;

 rightp->parent = parentp;

 /* parent is null make the right node the new root */
 if (parentp == SENTINEL)
  {
   rightp->color = BLACK;
   __tree_root = rightp;
  }
 else 
  {
   /* remove the node with a rb fixup if needed */
   parentp->left = rightp;
   if (nodep->color == BLACK) rb_delete_min_fixup(rightp);
  }

 /* save the freed node for reuse */
 if (__free_node_ndx == __free_node_size)
  {
   grow_free_nodes();
  }
 __free_nodes[__free_node_ndx++] = nodep;
 return(tevp);
}

static void grow_free_nodes(void)
{
 /* AIV 02/08/12  - these need to be size_t could overflow for 64-bit */
 size_t osize, nsize;

 osize = __free_node_size*sizeof(struct tqnode_t *);
 __free_node_size += (__free_node_size/2);
 nsize = __free_node_size*sizeof(struct tqnode_t *);
 __free_nodes = (struct tqnode_t **) __my_realloc(__free_nodes, osize, nsize);
}

/*
 * return the next time header struct from the timing tree if there is one
 * updates (removes the minimum node) the rb timing tree 
 * this is needed for the debug commands ($snapshot)
 * then using this routine to "peek ahead" at upcoming events must call
 * __restore_min_time_nodes() with the caller saving/restoring 
 * __free_node_ndx/__tree_root 
 * so it pops/restores upcoming events
 *
 * NOTE - it is just like move_time but it returns a not the index
 *   and it doesn't update __simtime
 *
 */
extern struct tev_t *__get_next_time_header(void)
{
 struct tqnode_t *nodep; 
 struct tqnode_t *rightp, *parentp;

 /* the tree is empty - return NULL */
 if (__tree_root == SENTINEL) return(NULL);

 /* get the next event */
 nodep = __min_time_node;
 
 rightp = nodep->right;
 parentp = nodep->parent;
 /* if has a right child it is the new minimum node otherwise the par is */
 if (rightp != SENTINEL) __min_time_node = rightp;
 else  __min_time_node = parentp;

 rightp->parent = parentp;

 /* remove the node with a rb fixup if needed */
 if (parentp == SENTINEL)
  {
   rightp->color = BLACK;
   __tree_root = rightp;
  }
 else 
  {
   parentp->left = rightp;
   if (nodep->color == BLACK) rb_delete_min_fixup(rightp);
  }

 /* save the freed node for reuse */
 if (__free_node_ndx == __free_node_size)
  {
   grow_free_nodes();
  }
 __free_nodes[__free_node_ndx++] = nodep;
 return(nodep->te_hdrp);
}

/*
 * restore the popped minimum event nodes
 * caller saves/restores  __free_node_ndx/__tree_root 
 */
extern void __restore_min_time_nodes(int32 restore_point)
{
 struct tqnode_t *nodep;
 int32 i;

 /* the freed number better be more than the restore number */
 /* DBG remove --- */
 if (__free_node_ndx <= restore_point) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* start backwards to get the max (current min) to stick back in tree */
 nodep = NULL;
 for (i = __free_node_ndx - 1; i >= restore_point; i--)
  {
   nodep = __free_nodes[i];
   /* know it is a minimum since it is removed in min order */
   rb_insert_min(nodep);
  }
 /* reset the minimum time node and freed index */
 __min_time_node = nodep;
 __free_node_ndx = restore_point;
}



/*
 * do a fixup (rotate/color) of node x which is known to a node of min time
 */
static void rb_delete_min_fixup(struct tqnode_t *x)
{
 struct tqnode_t *w;

 while (x != __tree_root && x->color == BLACK)
  {
   w = x->parent->right;
   if (w->color == RED)
    {
     w->color = BLACK;
     x->parent->color = RED;
     left_rotate(x->parent);
     w = x->parent->right;
    }
   if (w->left->color == BLACK && w->right->color == BLACK)
    {
     w->color = RED;
     x = x->parent;
    }
   else 
    {
     if (w->right->color == BLACK)
      {
       w->left->color = BLACK;
       w->color = RED;
       right_rotate(w);
       w = x->parent->right;
      }
     w->color = x->parent->color;
     x->parent->color = BLACK;
     w->right->color = BLACK;
     left_rotate(x->parent);
     x = __tree_root;
   }
  }
 x->color = BLACK;
}

/*
 * allocate a node to hold a time event in a rb tree
 */
static struct tqnode_t *alloc_node(word64 t)
{
 struct tqnode_t *n;

 if (__free_node_ndx > 1)
  {
   n = __free_nodes[--__free_node_ndx];
  }
 else
  {
   n = (struct tqnode_t *) __my_malloc(sizeof(struct tqnode_t));
  }
 n->time = t;
 /* init to RED - only root is init to black */
 n->color = RED;
 /* set all nodes to SENTINEL (NULL) */
 n->parent = SENTINEL;
 n->left = SENTINEL;
 n->right = SENTINEL;
 /* AIV 10/15/07 - need to init the list for setting teprevp */
 n->te_hdrp = NULL;
 n->te_endp = NULL;
 n->nb_hdrp = NULL;
 n->nb_endp = NULL;
 return(n);
}

#else
/*
 * insert an event into the heap timing queue
 *
 * AIV FIXME - this can get rid of teprevp when compiled code doesn't share
 * any init code which calls this since interp doesn't use static events
 * events are never linked out so there are no empty time elements
 */
extern void __insert_event(struct tev_t *tevp)
{
 word64 schtime;
 struct heap_t *time_hp;
 struct heap_t *hp, *next_hp, *last_hp;
 struct tev_t *prevp;
 word32 hash, h_word, lword;

 schtime = tevp->etime;
 /* AIV 10/25/07 - if this is the current event don't set the next */
 /* to NULL perhaps processing should save the next point???? */
 /* AIV LOOKATME - this not positive that allowing __cur_tevp == tevp */
 /* works everytime */
 if (__cur_tevp != tevp) tevp->tenxtp = NULL;

 lword = (word32) schtime;
 h_word = (word32) (schtime >> 32);
 hash = get_time_hash_(lword, h_word);

 time_hp = __time_hash[hash];
 /* new time value */
 if (time_hp == NULL)
  {
   add_new_heap_time(tevp, hash);
   return;
  }

 /* time already has place in heap link in */
 if (time_hp->time == schtime) 
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

#ifdef __CVC_DEBUG__
 __collision_count++;
#endif

 /* new time is the new minimum link on to front */
 if (schtime < time_hp->time)
  {
   hp = add_new_heap_time(tevp, hash);
   hp->next = time_hp;
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
     prevp = next_hp->te_endp;
     prevp->tenxtp = tevp;
     tevp->teprevp = prevp;
     next_hp->te_endp = tevp;
     tevp->time_hp = next_hp;
     return;
    }
   /* new spot is in the middle of hash conflict list */
   else if (next_hp->time > schtime)
    {
     hp = add_new_heap_time(tevp, hash);
     /* AIV 11/23/10 - need restore __time_hash - to point to original */
     /* time_hp - known to be lowest - new_heap_time set every time */
     __time_hash[time_hp->hash] = time_hp;
     last_hp->next = hp;
     hp->next = next_hp;
     return;
    }
   last_hp = next_hp;
  }
 /* the new time is now on the end of the conflict list */
 hp = add_new_heap_time(tevp, hash);
 /* AIV 11/23/10 - need restore __time_hash - to point to original */
 /* time_hp - known to be lowest - new_heap_time set every time */
 __time_hash[time_hp->hash] = time_hp;
 last_hp->next = hp;
}
 
/*
 * add a new time event to the heap - the first event at any given time
 */
static struct heap_t *add_new_heap_time(struct tev_t *tevp, int32 hash)
{
 word64 schtime;
 int32 i, parent;
 struct heap_t *hp, *parent_hp;

 if (__free_heap_ndx > 1) hp = __free_heap[--__free_heap_ndx];
 else hp = (struct heap_t *) __my_malloc(sizeof(struct heap_t));

 /* event must store its time heap element in case of later linkout */
 tevp->time_hp = hp;
 tevp->teprevp = NULL;

 schtime = tevp->etime;
 /* save hash so it does not have to be recomputed */
 hp->hash = hash;
 hp->time = schtime;
 /* set the first element */
 hp->te_hdrp = tevp;
 hp->te_endp = tevp;
 hp->next = NULL;
 /* first event at this hash store this time heap element */
 __time_hash[hash] = hp;

 /* must grow the heap */
 if (__heap_size == __heap_maxsize)
  {
   grow_event_heap();
  }

 /* place new time into the heap */
 i = __heap_size;
 if (i > 1)
  {
   parent = PARENT(i);
   parent_hp = __heap[parent];
   for (; ;)
    {
     if (parent_hp->time < schtime) break;
     __heap[i] = parent_hp;
     i = parent;
     if (i <= 1) break;
     parent = PARENT(i);
     parent_hp = __heap[parent];
    }
  }
 /* inc heap size and store new heap pointer */
 __heap_size++;
 __heap[i] = hp;
 return(hp);
}
 
/*
 * grow the event heap array and the freed as well
 */
static void grow_event_heap(void)
{
 /* AIV 02/08/12  - these need to be size_t could overflow for 64-bit */
 size_t olen, osize, nsize;

 olen = __heap_maxsize;
 osize = olen*sizeof(struct heap_t *);
 __heap_maxsize += (olen/2);
 nsize = __heap_maxsize*sizeof(struct heap_t *);
 __heap = (struct heap_t **) __my_realloc((char *) __heap, osize, nsize);
 /* grow the array which stores the free heap time elements */
 __free_heap = (struct heap_t **) __my_realloc(__free_heap, osize, nsize);
}

/*
 * adance the time to the next minimum event in heap
 * return the new next time head event
 */
static struct tev_t *move_time(void)
{
 int32 hash;
 struct heap_t **a;
 struct heap_t *min_hp, *max_hp;
 struct tev_t *tevp;

 /* no event return NULL */
 if (__heap_size == 1) return(NULL);

 a = __heap;
 min_hp = a[1];
 /* set the time */
 __simtime = min_hp->time;
 __heap_size--;
 /* swap the max and min and 'heapify' down the max value */
 max_hp = a[__heap_size];
 a[1] = max_hp;
 /* no need to heapify one element */
 if (__heap_size > 2) 
  {
   heapify();
  }

 hash = min_hp->hash;
 __cur_te_endp = min_hp->te_endp;
 tevp = min_hp->te_hdrp;
 __cur_te_hdrp = tevp;
 /* move time hash to next event (hash conflict ) */
 /* most of the time this should be NULL because of no conflict */
 __time_hash[hash] = min_hp->next;
 /* free event list is same size as __heap so known to fit */
 __free_heap[__free_heap_ndx++] = min_hp;
 return(tevp);
}

/*
 * run the heapify to pass down the max from the min(1) to maintain
 * heap property
 */
static void heapify(void)
{
 int32 l, r, i, min;
 struct heap_t *minp, *lp, *rp, *ip;
 struct heap_t **a;

 a = __heap;
 i = 1;
 l = 2;
 min = -1;
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

/*
 * peek ahead to get the next time event head
 *
 * AIV LOOKATME - make sure this works?????????
 * only used for interpreter???????
 */
extern struct tev_t *__get_next_time_header(void)
{
 word64 save_simtime;
 struct tev_t *tevp;

 /* save the simulation time and put back */
 save_simtime = __simtime;
 tevp = move_time();
 __simtime = __simtime;
 return(tevp);
}

/*
 * restore the popped minimum event nodes
 * caller saves/restores  __free_heap_ndx
 *
 * AIV LOOKATME - make sure this works?????????
 */
extern void __restore_min_time_heap(int32 restore_point)
{
 struct heap_t *hp;
 int32 i;

 /* the freed number better be more than the restore number */
 /* DBG remove --- */
 if (__free_heap_ndx <= restore_point) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* start backwards to get the max (current min) to stick back in tree */
 hp = NULL;
 for (i = __free_heap_ndx - 1; i >= restore_point; i--)
  {
   hp = __free_heap[i];
   /* know it is a minimum since it is removed in min order */
   heap_reinsert_min(hp);
  }
 /* reset the freed index */
 __free_heap_ndx = restore_point;
} 
 
/*
 * reinsert a known minimum back into the heap
 */
static void heap_reinsert_min(struct heap_t *hp)
{
 word64 schtime;
 int32 i, parent;
 struct heap_t *parent_hp;

 i = __heap_size;
 schtime = hp->time;
 if (i > 1)
  {
   parent = PARENT(i);
   parent_hp = __heap[parent];
   for (; ; )
    {
     if (parent_hp->time < schtime) break;
     __heap[i] = parent_hp;
     i = parent;
     if (i <= 1) break;
     parent = PARENT(i);
     parent_hp = __heap[parent];
    }
  }
 __heap_size++;
 __heap[i] = hp;
}
#endif

/*
 * routine to allocate event - non macro for debugging
 * the b zero initializes all flags to off
 */
/* DBG ??? remove --- */
extern struct tev_t *__alloc_tev(void *enterptr, t_midat *te_idp, 
 word64 absetime)
{
 struct tev_t *tevp__;
 tmp_tev_ndx tevpi;

 if (__tefreelstp != NULL)
  { 
   tevp__ = __tefreelstp; 
   __tefreelstp = tevp__->tenxtp; 
  }
 else
  {
   if (++__numused_tevtab >= TEVTAB_ALLOC_SIZE) 
    {
     __tevtab = (struct tev_t *) 
      __my_malloc(TEVTAB_ALLOC_SIZE*sizeof(struct tev_t));
     __numused_tevtab = 0;
    }
   tevpi = __numused_tevtab;
   tevp__ = &(__tevtab[tevpi]);
  }
 /* LOOKATME - maybe zeroing to init bit fields unportable */
 /* AIV 09/28/07 - only need to zero the first two words of the struct */
 /* since the rest are set here no need to zero all fields */
 memset(tevp__, 0, 8);
 tevp__->enterptr = enterptr;
 tevp__->te_idp = te_idp;
 tevp__->etime = absetime;
 tevp__->tenxtp = NULL;
 tevp__->delay = 0; 
 tevp__->trigger = FALSE; 
 tevp__->teprevp = NULL;
 tevp__->next_enterptr = __process_next_ev_enterp;
 return(tevp__);
}

/*  --- */
extern struct tev_t *__alloc_cur_tev(void *enterptr, word64 absetime)
{
 struct tev_t *tevp__;
 tmp_tev_ndx tevpi;

 if (__tefreelstp != NULL)
  { 
   tevp__ = __tefreelstp; 
   __tefreelstp = tevp__->tenxtp; 
  }
 else
  {
   if (++__numused_tevtab >= TEVTAB_ALLOC_SIZE) 
    {
     __tevtab = (struct tev_t *) 
      __my_malloc(TEVTAB_ALLOC_SIZE*sizeof(struct tev_t));
     __numused_tevtab = 0;
    }
   tevpi = __numused_tevtab;
   tevp__ = &(__tevtab[tevpi]);
  }
 /* LOOKATME - maybe zeroing to init bit fields unportable */
 /* AIV 09/28/07 - only need to zero the first two words of the struct */
 /* since the rest are set here no need to zero all fields */
 memset(tevp__, 0, 8);
 tevp__->enterptr = enterptr;
 tevp__->te_idp = __idp;
 tevp__->etime = absetime;
 tevp__->tenxtp = NULL;
 tevp__->delay = 0; 
 tevp__->trigger = FALSE; 
 tevp__->teprevp = NULL;
 tevp__->next_enterptr = __process_next_ev_enterp;
 return(tevp__);
}

/*
 * normally unused routine for checking pending scheduled dce events
 * UNUSED
 */
/* ---
static void chk_schd_dces(void)
{
 int32 ni;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct net_t *np;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     if (np->dcelst == NULL) continue;
     chk_1nschd_dce(np, mdp);
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       if (np->dcelst == NULL) continue;
       chk_1nschd_dce(np, mdp);
      }
    }
  }
}
-- */

/*
 * check one static scheduled dce
 * UNUSED
 */
/* ---
static void chk_1nschd_dce(struct net_t *np, struct mod_t *mdp)
{
 struct dcevnt_t *dcep;
 int32 ii;
 tmp_tev_ndx tevpi;
 struct delctrl_t *dctp;
 t_midat *tidp;

 for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
  {
   if (dcep->dce_typ != DCE_RNG_INST && dcep->dce_typ != DCE_INST)
     continue;
   dctp = dcep->st_dctrl;
   if (dctp->dceschd_tev_ofs == -1)
    __cvsim_msg("*** net %s dcep no dce schd tevs\n", np->nsym->synam);
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     tidp = mdp->moditps[ii]->it_idp;

     if ((tevpi = tidp[dctp->dceschd_tev_ofs]) != -1)
      __cvsim_msg("*** net %s inst num. %s dce schd tevs index %d set\n",
       np->nsym->synam, ii, tevpi);
     if (__tevtab[tevpi].tetyp < 1 || __tevtab[tevpi].tetyp > 14)
      __misc_terr(__FILE__, __LINE__);
    }
  }
}
--- */

/*
 * ROUTINES TO IMPLEMENT TIME FLOW
 */

static int32 move_to_time0(void)
{
 struct telhdr_t *twp;

 __simtime++;
 twp = __cur_timehdr;
 __cur_te_hdrp = twp->te_hdrp;
 __cur_te_endp = twp->te_endp;
 return(TRUE);
}

/*
 * free list of tevs - either btree node or timing wheel list
 *
 * normally add entire period's events to free list - this is for reset only
 * because when an event is processed guts (if any) freed so can link on
 * free list but here need to free guts too
 */
extern void __free_telhdr_tevs(struct tev_t *hdr_tevp)
{
 struct tev_t *tevp, *tevp2;

 for (tevp = hdr_tevp; tevp != NULL;)
  {
   tevp2 = tevp->tenxtp;
   __free_1tev(tevp);
   tevp = tevp2;
  }
}

/*
 * free 1 event - may need to free auxiliary since will never be processed
 * freeing just puts on front of ev free list
 */
extern void __free_1tev(struct tev_t *tevp)
{
 word32 *wp;
 struct tenbpa_t *tenbp;
 struct tedputp_t *tedp;
 struct teputv_t *tepvp;
 void *enterp;

 enterp = tevp->enterptr;
 if (enterp == __process_wire_ev || enterp == __process_trpthdst_ev 
     || enterp == __process_mipd_nchg_ev) 
  {
   if (tevp->tu.tenp != NULL) __my_free(tevp->tu.tenp, sizeof(struct tenp_t));
  }
 else if (enterp == __process_nbpa_ev)
  {
   /* for non #0 original freed here but no tenbpa - moved to new */
   if ((tenbp = tevp->tu.tenbpa) != NULL) 
    {
     wp = tenbp->nbawp;
     __my_free(wp, tenbp->nbytes);
     /* if needed to copy lhs expr., now free */
     if (tenbp->nblhsu.nblhsxp != NULL) __free_xtree(tenbp->nblhsu.nblhsxp);
     __my_free(tevp->tu.tenbpa, sizeof(struct tenbpa_t));
    }
  }
 else if (enterp == __process_putpdel_ev)
  {
   if ((tedp = tevp->tu.tedputp) != NULL) 
    {
     tevp->tu.tedputp = NULL;
     tedp->tedtfrp =  (struct tfrec_t *) __tedpfreelst;
     __tedpfreelst = tedp;
    }
   }
 else if (enterp == __process_vpi_varputv_ev || enterp == __process_vpidrv_ev)
  {
   if ((tepvp = tevp->tu.teputvp) != NULL)
    {
     tevp->tu.teputvp = NULL;
     tepvp->np =  (struct net_t *) __teputvfreelst;
     __teputvfreelst = tepvp;
    }
  }
 /* ** DBG remove --
 memset(tevp, 0, sizeof(struct tev_t));
 __dbg_msg("--- free tev at %x\n", tevp);
 --- */
 tevp->tenxtp = __tefreelstp;
 __tefreelstp = tevp;
}

