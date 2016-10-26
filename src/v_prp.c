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
#include <alloca.h>
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

#include "igen.h"

#include "vpi_user.h"

/* local prototypes */
static void rem_inc_dupes(void);
static void prep_udps(void);
static void prep1_udp(struct udp_t *);
static void prep_comb_udptab(struct udp_t *);
static void xpnd_1wcard(int32, word32);
static void init_utab(word32 *, int32);
static void chg_unfilled_tox(word32 *, int32);
static void bld_wcardtab(char *, word32, word32);
static word32 bld_uinitndx(char *, word32, int32);
static void setchk_uval(word32);
static char *bld_udploc(char *, word32, word32, word32);
static char *udploc_to_line(char *, char *);
static void dmp_comb_udptab(struct udp_t *);
static void dmp_udp3v_tab(word32 *, word32);
static char *bld3vndx_str(char *, word32, word32);
static void dmp_udp2b_tab(word32 *, word32);
static int32 udmp_impossible_value(word32, word32);
static char *bldndx_str(char *, word32, word32);
static void dmp_edge_udptab(struct udp_t *);
static void dmp_udp3v_etab(word32 *, word32, int32, int32);
static void dmp_udp2b_etab(word32 *, word32, int32, int32);
static void prep_edge_udptab(struct udp_t *);
static void xpnd_edge_wcard(word32, int32, int32, word32);
static void free_udp_lines(struct udp_t *);
static void change_all_rngreps(void);
static void set_optim_nflds(struct net_t *, int32);
static void free_ncablks(void);
static void emit_varunused_informs(struct net_t *, struct task_t *);
static void rt_change_rngrep(struct net_t *);
static void bld_gstate(void);
static void prep_conta_dels(void);
static int32 rhs_cat_separable(struct expr_t *);
static int32 rhs_modpin_separable(struct expr_t *);
static void bld_pbsep_input_mpps(void);
static void bld_pbsep_output_mpps(void);
static int32 output_pb_separable(void);
static void bld_pb_mpps(struct mod_pin_t *);
static void bld_pb_contas(void);
static void init_pbexpr_el(struct pbexpr_t *);
static struct expr_t *bld_1sep_pbit_expr(struct pbexpr_t *, int32);
static struct expr_t *cnvt_to_bsel_expr(struct expr_t *, int32);
static void bld_nplist(void);
static void bld_lhsexpr_npins(struct expr_t *, int32);
static void bld2_lhsexpr_npins(struct expr_t *, int32);
static void bld_rhsexpr_npins(struct expr_t *, int32);
static void bld_rhsexpr_npins_var_wire_array(struct expr_t *, int32,
 struct gref_t *);
static void conn_rtxmr_npin(struct net_t *, int32, int32, int32, int32,
 struct gref_t *, int32, char *);
static void conn_xmr_npin(struct net_t *, int32, int32, int32, int32,
 struct gref_t *, int32, char *);
static struct net_pin_t *conn2_npin(struct net_t *, int32, int32, int32,
 int32);
static void set_chgsubfld(struct net_pin_t *, int32, char *);
static void add_netdel_pnp(struct net_t *, struct paramlst_t *);
static void fixup_idps_where_used_itp(void);
static void init_pnp(struct parmnet_pin_t *);
static void addto_parmnplst(struct expr_t *, struct parmnet_pin_t *);
static void add_gatedel_pnp(struct gate_t *, struct paramlst_t *);
static void add_contadel_pnp(struct conta_t *, struct paramlst_t *);
static void free_1parm_pnps(struct net_t *);
static void eat_gates(void);
static int32 has_muststay_npp(struct net_pin_t *);
static void mark_muststay_wires(struct expr_t *);
static void eat_nets(int32);
static void rem_del_npps(void);
static void remove_all_npps(struct net_t *);
static void bld1vec_fifo(struct net_t *);
static void update_vec_fifo(struct net_t *, word32 *, int32 *, int32 *,
 int32 *);
static int32 wire_implied_driver(struct net_t *);
static void eat_cells(int32 *);
static int32 conn_expr_gone(struct expr_t *);
static void mark_maybe_gone_nets(struct expr_t *);
static void getbit_fifo(struct net_t *, int32, int32 *, int32 *);
static void rm_comb_dup_lds(void); 
static void assgn_idnums_and_bld_indices(void);
static void count_mods(void);
static void count_udps(void);
static void bld_1mod_specify_pth_ndx(struct mod_t *);
static void bld_1mod_npp_ndx(struct mod_t *);
static int32 count_1mod_npps(struct mod_t *); 
static int32 count_tskvars(struct task_t *);
static void prep_confunc_stmts(struct task_t *);
static void extra_confunc_prep(struct task_t *);
static void extra_confunc_prep_stmt(struct st_t *);
static void extra_confunc_prep_stlst(struct st_t *);
static void extra_confunc_prep_csitemlst(struct csitem_t *);
static void init_all_confunc_vars(struct task_t *); 

extern struct expr_t *__get_lvalue_idndp(struct expr_t *);
extern int32 __net_chg_nd_store(struct net_t *, int32, int32);
extern void __add_isnum_to_tree(void *, int32, int32);
extern int32 __check_delay_constant(union del_u, int32, word64 *);
extern void __add_net_to_netchg_lst(struct net_t *);

static void merge_always_ev_dctrl(void);
static struct delctrl_t **make_dctrl_event_array(struct mod_t *, int32 *);
static int32 is_dctrl_in_array(struct delctrl_t *, struct delctrl_t **, 
 int32);
static void merge_edge_dces(void); 
static int32 try_merge_dces(struct dcevnt_t *);
static int32 can_merge_dce(struct dcevnt_t *);
static void bld_all_netchanges(void);
static void bld_all_time_events(void);
static void bld_all_proc_time_events(struct mod_t *);
static void bld_conta_time_events(struct mod_t *);
static void bld_wire_ev_time_events(struct mod_t *);
static void bld_lhsx_time_events(struct expr_t *, struct mod_t *);
static void bld_gate_time_events(struct mod_t *);
static void add_dctl_stmt_event(struct st_t *, struct mod_t *);
static struct ctev_t *alloc_ctev(union del_u, int32, struct mod_t *, int32);
static void prep_idp_area(void);
static void merge_rm_1net_ld_dups(struct mod_t *, struct net_t *);
static int32 cnt_npps(struct net_pin_t *);
static int32 npp_can_del_or_merge(struct net_pin_t *);
static int32 npps_same(struct mod_t *, struct net_pin_t *, struct net_pin_t *);
static int32 vec_merge_rm_iconn_npps(int32);
static int32 scalar_rm_iconn_npps(int32);
static void mark_npps_for_del(struct npopt_t *, int32);
static void delrm_rebld_npp_list(struct net_t *, int32);
static void add_lhsx_to_netchg_lst(struct expr_t *, int32, int32);
static void add_proc_stmt_netchgs(struct mod_t *);
static void add_lhsx_netchgs(struct mod_t *, struct expr_t *);
static void add_one_lhsx_netchgs(struct mod_t *, struct expr_t *, int32, int32);
static void add_conta_netchgs(struct mod_t *);
static void add_lhsx_concat_to_netchg_lst(struct expr_t *, int32);
static void add_net_changes_from_lds(struct net_t *);
static void add_net_changes_from_drvs(struct net_t *);
static void add_force_net_tran_changes(struct net_t *);
static void add_net_changes_from_tran(struct net_t *);
static void set_process_wire_ev_flag(struct mod_t *, struct net_t *);
static void add_net_changes_from_dces(struct net_t *);
static void add_net_change(struct net_t *, int32, int32, int32, int32, int32);
static void add_1mod_nchges_from_nd_chgst_bit(struct mod_t *, int32);
static void bld_no_lds_and_no_drvs_nchges(void);
static void try_add_analyze_late_nchges(struct net_t *, struct mod_t *,
 struct task_t *);

/* extern prototypes (maybe defined in this module) */
extern void __prep_sim(void);
extern void __rd_setup_optcfg(void);
extern struct pbexpr_t *__bld_pb_expr_map(struct expr_t *, int32);
extern void __conn_npin(struct net_t *, int32, int32, int32, int32,
 struct gref_t *, int32, char *);
extern struct net_pin_t *__alloc_npin(int32, int32, int32);
extern struct npaux_t *__alloc_npaux(void);
extern void __add_dctldel_pnp(struct st_t *);
extern void __add_tchkdel_pnp(struct tchk_t *, int32);
extern void __add_pathdel_pnp(struct spcpth_t *);
extern void __free_design_pnps(void);
extern int32 __get_acc_class(struct gate_t *);
extern int32 __add_gate_pnd0del(struct gate_t *, struct mod_t *, char *);
extern int32 __add_conta_pnd0del(struct conta_t *, struct mod_t *, char *);

extern void __prep_xmrs(void);
extern void __set_net_srep_types(void);
extern void __set_all_mods_1inst_storage_offsets(void);
extern void __alloc_sim_storage(void);
extern void __init_sim_storage(void);
extern void __rd_set_from_tgldat_toggled(void);
extern void __bld_bidandtran_graph(void);
extern void __setchk_all_fifo(void);
extern void __prep_exprs_and_ports(void);
extern void __prep_contas(void);
extern void __prep_stmts(void);
extern void __set_optimtab_bits(void);
extern void __set_mpp_assign_routines(void);
extern void __set_pb_mpp_assign_routines(void);
extern void __set_mpp_aoff_routines(void);
extern void __prep_specify(void);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern char *__to_uvvnam(char *, word32);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_ptnam(char *, word32);
extern void __prep_delay(struct gate_t *, struct paramlst_t *, int32, int32,
 char *, int32, struct sy_t *, int32);
extern void __free_xtree(struct expr_t *);
extern char *__to_mpnam(char *, char *);
extern int32 __isleaf(struct expr_t *);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern void __free_dellst(struct paramlst_t *);
extern void __free_del(union del_u, word32, int32);
extern void __bld_pb_fifo(struct net_t *, int32 *, int32 *, int32 *, int32);
extern int32 __gate_is_acc(struct gate_t *);
extern char *__bld_lineloc(char *, word32, int32);
extern void __init_all_inst_conta_drv(int32, int32, struct mod_t *);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern void __rem_0path_dels(void);
extern int32 __chk_0del(word32, union del_u, struct mod_t *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern struct expr_t *__copy_expr(struct expr_t *);
extern int32 __cnt_cat_size(struct expr_t *);
extern struct expr_t *__alloc_newxnd(void);
extern struct expr_t *__bld_rng_numxpr(word32, word32, int32);
extern int32 __get_itp_const_bselndx(struct expr_t *);
extern void __getwir_range(struct net_t *, int32 *, int32 *);
extern int32 __is_const_expr(struct expr_t *);
extern void __bld_provisional_mstabs(void);
extern void __dmpmod_nplst(struct mod_t *, int32);
extern void __show_allvars(void);
extern void __set_pre_idp_nchgaction_bits(void);
extern void __init_idp_nchgaction(void);
extern void __process_sdf_files(void);
extern void __process_sdf_tskenables(void);
extern int32 __mda_multiplier(struct net_t *, int32);
extern void __getarr_range_mda(struct net_t *, int32 *, int32 *mnai2, int32 *, 
 int32);
extern void __copy_fixup_prep_exec_const_func(struct task_t *);
extern struct xstk_t *__exec_const_func(struct expr_t *); 
extern struct task_t *__image_copy_confunc(struct task_t *);
extern void __chg_task_prms_to_tab(struct task_t *);
extern void __chk_taskvars(struct task_t *, int32);
extern void __chk_funcdef(struct task_t *);
extern void __set_1net_srep(struct net_t *);
extern void __set_1var_net_ofs(struct net_t *np, struct mod_t *);
extern struct st_t *__prep_lstofsts(struct st_t *, int32, int32);
extern void __init_stmt(struct st_t *, int32);
extern void __init_var(struct net_t *);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern struct sy_t *__get_forw_funcdef_sy(struct expr_t *, int32);
extern void __fill_wire_arr_sym_wrkstab(struct net_t *, struct mod_t *);

extern void __alloc_compiled_sim_storage(void);
extern void __init_compiled_sim_storage(void);
extern int32 __cmp_xpr(struct expr_t *, struct expr_t *, int32 *);

extern void __cv_msg(char *, ...);
extern void __dbg_msg(char *, ...);
extern void __pv_ferr(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __sgfinform(int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);

extern void __vpi_err(int32, int32, char *, ...);

extern const word32 __masktab[];
extern const word32 __pow3tab[];

/*
 * SIMULATION PREPARATION ROUTINES
 */

/*
 * prepare for simulation
 */
extern void __prep_sim(void)
{
 int32 sav_declobj, wlen;

 /* because checking delay expressions need object type global set */
 sav_declobj = __cur_declobj;
 __cur_declobj = MODULE;

 /* done reading source files - remove all duplicates from inc dbg list */
 if (__inclst_hdr != NULL) rem_inc_dupes();

 /* build per type udp tables - 1st since can free lots of storage */
 prep_udps();

 /* first change all wire ranges to constant form - need to build np list */
 change_all_rngreps();
 wlen = wlen_(__max_net_blen);
 /* AIV 08/25/10 - allocate enough dummy space for 2-state bpart */
 if (wlen < 30) wlen = 30;
 __addr_2state_zero = (word32 *) __my_malloc(wlen*sizeof(word32));
 /* init area to zero */
 memset(__addr_2state_zero, 0, wlen*WRDBYTES);

 /* allocate and fill xmr table - used when building np list */
 __prep_xmrs();

 /* SJM 09/18/02 - build the per bit decomposed ports and iconns */
 bld_pbsep_input_mpps();
 bld_pbsep_output_mpps();
 bld_pb_contas();

 /* AIV 08/14/07 - used to set nchg action area here now in idp area */
 /* so just need to set the srep types for each net */
 __set_net_srep_types();

 /* build the various net pin lists */
 bld_nplist();

 /* if errors building np list can't check further */
 if (__pv_err_cnt != 0) return;

 bld_gstate();
 prep_conta_dels();

 /* build inout tran and tran channel connection graphs */
 __bld_bidandtran_graph();

 /* SJM 02/09/07 - can't convert npp lists to array since too many exceptions */
 /* worst exceptions are tchks - now always keep as list */
 /* never worked and was never used, i.e. always accessed through npnxt */
 /* CANNOTCALL realloc_npplist_to_tab(); */ 

 if (__gateeater_on) eat_gates();

 /* mark each wire that has multi fan in for any bit */
 __setchk_all_fifo();

 /* allocate inout port memory and mark expr. fi>1 */
 __prep_exprs_and_ports();

 /* special preparation for contas (alloc drive values) and check getpats */
 __prep_contas();

 /* modify statements where needed */
 /* this also needs sim storage to be allocated */
 __prep_stmts();

 /* new first step toward compiler optimization routines (this for ports) */ 
 if (__accelerate)
  {
   __set_mpp_assign_routines();
   __set_pb_mpp_assign_routines();
  }
 else __set_mpp_aoff_routines();

 /* SJM 02/26/08 - REORGANIZED BACK - prep sim now more complicated */
 /* because prep the net list but also builds the per inst (one for */
 /* each module) idp area that has variable values but also fixed */
 /* known at compile time nchgs and events (tevs) */

 /* SJM 02/26/08 - must prep specify before any idp prep */
 sav_declobj = __cur_declobj;
 __cur_declobj = SPECIFY;
 __prep_specify();
 __cur_declobj = sav_declobj;

 /* SJM 02/03/07 - npp (load) optimize - simplifies npp by combining dups */
 rm_comb_dup_lds(); 

 /* AIV 02/28/12 - moved this back even further now need to set module */
 /* m_use_xprop prior to merge always @ blocks */

 /* read opt config file and set opt config properties in net list */ 
 /* complicated because may interact with program options and turning off */
 /* allowed for tgl cover recording and reporting - also PLI options */
 /* interact with opt config file stmts */
 __rd_setup_optcfg();

 __ctev_ndx = 0;

 if (__compiled_sim)
  {
   merge_always_ev_dctrl(); 
   merge_edge_dces(); 
  }

 /* SJM 08/08/03 - order was wrong, this is needed before setting chg bits */
 /* LOOKATME - only setting optim fields for dmpvars so far */
 __set_optimtab_bits();

 /* this just sets bits in net's that after idp set up moved to there */
 __set_pre_idp_nchgaction_bits();

 prep_idp_area();

 /* assign n.l. element ids and bld indices - now also build for interpreter */ 
 /* SJM 08/04/08 - need to assign ids last because prep idp area does the */ 
 /* SDF annotation that add MIPD npps - if added in PLI, then uses interp */
 /* wrappers so indices and for that matter any of the fixed not used */ 
 assgn_idnums_and_bld_indices();
}

/*
 * ROUTINES TO PREPARE SOURCE FOR DEBUGGER CAN BE DONE ANY TIME
 */

/*
 * remove all duplicated (exactly same name) include files 
 */
static void rem_inc_dupes(void)
{
 struct incloc_t *ilp, *ilp2, *last_ilp2, *ilp3;

 for (ilp = __inclst_hdr; ilp != NULL; ilp = ilp->inclocnxt) 
  {
   last_ilp2 = ilp;
   for (ilp2 = ilp->inclocnxt; ilp2 != NULL;)
    {
     ilp3 = ilp2->inclocnxt;
     /* notice if same file included with different path ref. just left */
     if (strcmp(__in_fils[ilp->inc_fnind], __in_fils[ilp2->inc_fnind]) == 0)
      {
       /* if same leave first and link out next and keep looking */
       last_ilp2->inclocnxt = ilp2->inclocnxt;
       __my_free(ilp2, sizeof(struct incloc_t));
      }
     else last_ilp2 = ilp2;
     ilp2 = ilp3;
    }
  }
}

/*
 * ROUTINES TO BUILD UDP STATE CHANGE TABLES
 */

/*
 * prepare all udp types - i.e. build the tables
 */
static void prep_udps(void)
{
 struct udp_t *udpp;
 struct udp_t *udpp2, *last_udpp;
 long sav_mem_use;

 sav_mem_use = __mem_use;
 for (last_udpp = NULL, udpp = __udphead; udpp != NULL;)
  {
   udpp2 = udpp->udpnxt;
   if (udpp->u_used)
    {
     __mem_use = sav_mem_use;
     prep1_udp(udpp);
     __mem_udpuse += __mem_use - sav_mem_use;
     __mem_use = sav_mem_use; 

     /* cannot free lines since dumping source for debug after prep DBG */
     /* free_udp_lines(udpp); */
     last_udpp = udpp;
    }
   else
    {
     free_udp_lines(udpp);
     __my_free(udpp, sizeof(struct udp_t));
     if (last_udpp == NULL) __udphead = udpp2;
     else last_udpp->udpnxt = udpp2;  
     /* do not change last_udpp here */ 
    }
   udpp = udpp2;
  }
}

/*
 * prepare one udp
 */
static void prep1_udp(struct udp_t *udpp)
{
 /* either combinatorial (no state) or level */
 if (udpp->utyp != U_EDGE)
  {
   udpp->utab = (struct udptab_t *) __my_malloc(sizeof(struct udptab_t));
   udpp->utab->eudptabs = NULL;
   prep_comb_udptab(udpp);
   /* array of pointers to tables is of size [number of edge tables-1] */
   udpp->utab->ludptab = __cur_utab;
   /* DBG remove --
   if (__debug_flg) dmp_comb_udptab(udpp);
   --- */
   return;
  }
 /* build the edge table - for now always build even if no level entries */
 prep_edge_udptab(udpp);
 /* -- DBG remove
 if (__debug_flg) dmp_edge_udptab(udpp);
 --- */
}

/* table of combinatorial table output sizes in bits (2 per entry) */
/* constant must be <= 7 since 7 inputs is 4k bytes per table */
static int32 combtabsiz[] = { 0, 8, 32, 128, 512, 2048, 8192, 32768 };

/* table of slower encoding scheme sizes in bits (standard <= 10 ins) */
static int32 comb2tabsiz[] = { 0, 6, 18, 54, 162, 486, 1458, 4374, 13122,
 39366, 118098, 354294, 1062882, 3188646, 9565938, 28697814 };

/*
 * build the combinatorial table
 * also needed for sequential udps where levels override edges
 * use 2 bit per input form for up to 6 inputs
 *
 * notice output can not be wild card since would means 1 input combination
 * to multiple outputs
 */
static void prep_comb_udptab(struct udp_t *udpp)
{
 struct utline_t *utlp;
 word32 nstates;
 int32 blen, bytsiz;
 word32 ndx;
 char out_ch;

 /* for comb. errors must indicate no edge */
 __cur_ueipnum = NO_VAL;
 __cur_utabsel = NO_VAL;
 /* udp number of states includes output for sequentials */
 nstates = udpp->numstates;
 /* set size of table */
 if (udpp->u_wide) blen = comb2tabsiz[nstates];
 else blen = combtabsiz[nstates];
 /* notice Verilog assumes 8 bit bytes */
 /* SJM 05/19/01 - since fill using word32 ptr need to round to wrd bytes */
 bytsiz = WRDBYTES*wlen_(blen);
 /* RELEASE remove --
 if (__debug_flg)
  __dbg_msg("## comb (part?) udp %s - %u states with table size %d bytes\n",
   udpp->usym->synam, nstates, bytsiz); 
 --- */
 __cur_utab = (word32 *) __my_malloc(bytsiz);
 /* initialize to unfilled (3) - maps table x (2) to real 3 as last step */
 init_utab(__cur_utab, blen);
 __cur_udp = udpp;

 for (utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt)
  {
   /* if this is edge line, goes in edge not combinatorial table */
   if (utlp->uledinum != NO_VAL) continue;

   __sfnam_ind = utlp->utlfnam_ind;
   __slin_cnt = utlp->utlin_cnt;

   /* next output state can be wildcard */
   if (utlp->ulhas_wcard) bld_wcardtab(utlp->tline, nstates, nstates + 1);

   /* build 2 bit form for narrow or signature for wide */
   /* wildcards here always make 0 contribution */  
   ndx = bld_uinitndx(utlp->tline, nstates, -1);

   /* out ch gets the output value (as char here) */
   out_ch = utlp->tline[udpp->numstates];
   /* if output - (no change form) must set output (__cur_uoval) during */
   /* wild card expansion */  
   if (out_ch == '-') __cur_unochange = TRUE;
   else
    {
     /* else can set it immediately */
     __cur_unochange = FALSE;
     /* must be for checking so will match x */
     __cur_uoval = (word32) ((out_ch == '0') ? 0 : ((out_ch == '1') ? 1 : 2));  
    }
   /* this sets 1st to each and recursives call self to expand others */
   if (utlp->ulhas_wcard) xpnd_1wcard(0, ndx);
   /* if no wildcards, even if '-' output, will be 0/1/x (3 since out) */
   /* this sets current output value */
   else setchk_uval(ndx);
  }
 /* finally for all locations left unitialized changed to udp x (2) */
 chg_unfilled_tox(__cur_utab, blen);
}

/*
 * recursively expand 1 wild card
 * if wildcard, must be used to set all o states (even 1st)
 * notice recursion depends on fact that passed ndx is by value
 */
static void xpnd_1wcard(int32 wci, word32 ndx)
{
 int32 wcvi, wchval, i;
 word32 ndx2;
 
 wchval = (__wcardtab[wci].wcchar == '?') ? 2 : 1;
 i = __wcardtab[wci].wcinum;
 /* notice need to go through for 0 since table value not yet set */
 for (wcvi = 0; wcvi <= wchval; wcvi++)
  {
   if (!__cur_udp->u_wide)
    {
     /* know i input 2 bits will always be 0 */
     if (wcvi == 0) ndx2 = ndx;
     else
      { 
       /* needed because even though now sticking 2 in as x output */
       /* index must be 3 which will be the value after table prepared */
       /* for non wide table entry */
       if (wcvi == 2) wcvi = 3;
       ndx2 = ndx | (word32) (wcvi << (2*i));
      }
    }
   else
    { 
     /* know here contribution from i, is 0 in ndx */
     if (wcvi != 0) ndx2 = ndx + wcvi*__pow3tab[i];
     else ndx2 = ndx;
     /* know if this is true, will always be rightmost wild card */
     if (i == __cur_udp->numstates - 1) __cur_upstate = (word32) wcvi;
     if (ndx2 >= __pow3tab[__cur_udp->numstates])
      __misc_terr(__FILE__, __LINE__);
    }
   /* - (no change) output handled in level value setting */
   if (wci == __last_wci) setchk_uval(ndx2);
   else xpnd_1wcard(wci + 1, ndx2);
  }
}

/*
 * init a udp table to 3 (not set) - later change 2 (x for now) to x (3)
 * notice udp 2 is unused not z (no z in udp world) 
 * inputs always just 3 for normal rep, 2 add value for signature
 *
 * when done here all 2's changed to 3's (real x's stored in output gstate)
 * radix form uses 3's in vector but changed to 2 in signature update
 * notice any unused in high word32 just set to unfilled
 */
static void init_utab(word32 *taddr, int32 blen)
{
 int32 i, wlen;
 word32 *wp;

 wlen = wlen_(blen);
 /* initialize to real x's - during table building x's are 2 that are then */
 /* changed to 3's where needed */
 /* since most of table is x's can check and change to x much faster */
 for (wp = taddr, i = 0; i < wlen; i++) wp[i] = ALL1W;
 wp[wlen - 1] &= __masktab[ubits_(blen)];
}

/*
 * convert 1 unfilled (defaults to x) from unfill 2 to x (3)
 */
static void chg_unfilled_tox(word32 *taddr, int32 blen)
{
 word32 tmp;
 int32 wi, bi;
 int32 wlen, ubits;

 wlen = wlen_(blen);
 for (wi = 0; wi < wlen - 1; wi++) 
  {
   /* if all bits already literally set to x's continue */
   if ((tmp = taddr[wi]) == ALL1W) continue;

   /* must change 2 (tmp. udp table build x) to 3 - real x */
   for (bi = 0; bi < WBITS; bi += 2)
    {
     if (((tmp >> bi) & 0x3L) == 2L)
      tmp |= (3L << bi);
    }
   taddr[wi] = tmp;
  }
 /* if by accident high word32 full and already all x's - done */
 if ((tmp = taddr[wlen - 1]) == ALL1W) return; 

 /* high word32 needs special handling */
 if ((ubits = ubits_(blen)) == 0) ubits = WBITS;
 for (bi = 0; bi < ubits; bi += 2) 
  {
   if (((tmp >> bi) & 0x3L) == 2L) tmp |= (3L << bi);
  }
 taddr[wlen - 1] = tmp;
}

/*
 * build wild card table from input line
 * for each wild card table contains input no. and wild card char
 *
 * even if edge (\?\?) form (really *) do not include in wild card table
 * for combinatorial table pass one past last input
 */
static void bld_wcardtab(char *chp, word32 nstates, word32 einum)
{
 word32 i;
 struct wcard_t *wcp;

 for (__last_wci = -1, i = 0; i < nstates; i++, chp++)
  {
   if (i == einum) continue;

   if (*chp == 'b' || *chp == '?')
    {
     wcp = &(__wcardtab[++__last_wci]);
     wcp->wcinum = i;
     wcp->wcchar = *chp;
    }
  }
}

/*
 * build the initial udp table index - 
 * either 2 bit per input with x as 3 or signature with x as 2 contribution
 */
static word32 bld_uinitndx(char *tlp, word32 nstates, int32 einum)
{
 word32 i;
 char *chp;
 word32 ndx;

 /* ? (01x) and b (01) are only that later require loops */
 ndx = 0;
 /* build initial state vector and set rep table start */
 /* wild cards 0 for now */
 /* notice cannot build incrementally, pins in initial signature backward*/ 
 for (i = 0, chp = tlp; i < nstates; i++, chp++)
  {
   /* for edge tab, if wildcard table select do not include, added in xpnd */
   if (i == (int32) einum) continue;
   switch (*chp) {
    /* make edge wildcards 0 here also - r/f just (01) and (10) by here */
    case '0': case 'b': case '?': case '*': case 'n': case 'p':
     if (__cur_udp->u_wide) __cur_upstate = 0L;
     break;
    case '1':
     if (__cur_udp->u_wide) { ndx += __pow3tab[i]; __cur_upstate = 1L; }
     else { ndx &= ~(3L << (2*i)); ndx |= (1L << (2*i)); }
     break;
    /* explicit x is always 2 here for normal udp (later changed to 3) */
    case 'x':
     if (__cur_udp->u_wide) { ndx += 2*__pow3tab[i]; __cur_upstate = 2L; }
     else ndx |= (3L << (2*i));
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 return(ndx);
}

/*
 * set and check if already set a normal non signature udp table entry
 * this is only place in udp preparation code that udp tables indexed
 * this is passed input state in 2 bit form with x == 2
 * uninitialized is 3 here that statys as real x (3) before exec
 * set to x is 2 here that is changed to 3, real x  
 */
static void setchk_uval(word32 init_ndx)
{
 int32 wi, bi;
 word32 tw, tw2;
 word32 ndx;
 char s1[RECLEN], s2[RECLEN];

 /* by here init_ndx is correct for this wildcard */ 
 if (__cur_udp->u_wide) ndx = init_ndx;
 else ndx = init_ndx & (int32) __masktab[2*__cur_udp->numstates];

 /* set 2: get old value */
 wi = get_wofs_(2*ndx);
 bi = get_bofs_(2*ndx);
 /* notice for edge cur utab set to right table from edge pair */
 tw = __cur_utab[wi];
 tw2 = (tw >> bi) & 3L;

 /* step 2a: if - output form get output */
 /* if output is '-' use last input that is state */
 /* if not '-' form, know __cur_uoval not set */
 if (__cur_unochange)
  {
   /* notice this can only happen for udp's with state */
   if (__cur_udp->u_wide) __cur_uoval = __cur_upstate;
   else
    {
     __cur_uoval = (init_ndx >> (2*(__cur_udp->numins))) & 0x3L;
     /* must be 2 so if table set (old value == 2) will get warn if 2 */
     if (__cur_uoval == 3L) __cur_uoval = 2L;
    }
  }
 /* step3: if table value already set - check it */
 if (tw2 != 3L)
  {
   if (__cur_uoval == tw2)
    {
     /* do not know previous line - could save but complicated */
    __sgfinform(462, "udp %s selector %s repeated", __cur_udp->usym->synam,
      bld_udploc(s1, ndx, __cur_uoval, __cur_udp->numstates));
     goto done;
    }
  __sgferr(970, "udp %s selector %s conflicts with previous %s",
   __cur_udp->usym->synam, bld_udploc(s1, ndx, __cur_uoval,
   __cur_udp->numstates), bld_udploc(s2, ndx, tw2, __cur_udp->numstates));
   /* fall thru here, even though error, use latest */
  }
 
 /* step4: change output to new value, here x must be represented as 2 */
 /* that gets changed later */
 __cur_utab[wi] = (tw & ~(3L << bi)) | (__cur_uoval << bi);

done:;
 /* --- RELEASE ---
 if (__debug_flg)
  { 
   __dbg_msg("+++ udp set: %s, val=%x, bi=%d, wi=%d\n", 
    bld_udploc(s1, ndx, __cur_uoval, __cur_udp->numstates),
    __cur_utab[wi], bi, wi);
   __dbg_msg("+++ udp set: %s\n", bld_udploc(s1, ndx, __cur_uoval,
    __cur_udp->numstates));
  }
 --- */
}

/*
 * build a udp location entry - for error messages
 * notice for wide signature form index must be wp[1] actual table index
 */
static char *bld_udploc(char *s, word32 ndx, word32 val, word32 nstates)
{
 char s1[RECLEN], s2[RECLEN];

 if (__cur_udp->u_wide) bld3vndx_str(s1, ndx, nstates);
 else bldndx_str(s1, ndx, nstates);
 udploc_to_line(s2, s1);

 sprintf(s, "%s : %s", s2, __to_uvvnam(s1, (word32) val));
 return(s);
}

/*
 * convert a simple edge char array to edge line 
 */
static char *udploc_to_line(char *s, char *line)
{
 int32 i;
 int32 slen;
 char *chp, *lchp;

 /* first add edge */
 if (__cur_ueipnum != NO_VAL)
  {
   lchp = line;
   chp = s;
   for (i = 0; *lchp != '\0'; i++)
    {
     if (i == __cur_ueipnum)
      {
       *chp++ = '('; 
       *chp++ = (__cur_utabsel == 0) ? '0': (__cur_utabsel == 1) ? '1' : 'x'; 
       *chp++ = *lchp++;
       *chp++ = ')';   
      }
     else *chp++ = *lchp++;     
    }
   *chp = '\0';
  }
 else strcpy(s, line);
 /* then add : if has state */
 if (__cur_udp->numins != __cur_udp->numstates)
  {
   slen = strlen(s);
   s[slen + 1] = '\0';
   s[slen] = s[slen - 1];
   s[slen - 1] = ':';
  }
 return(s);
}

/*
 * dump a non edge udp table only 6 states or less
 */
static void dmp_comb_udptab(struct udp_t *udpp)
{
 word32 *utabp;
 word32 nstates;

 utabp = udpp->utab->ludptab;
 nstates = udpp->numstates;
 if (nstates > 6) return;

 __dbg_msg(".. dumping combinatorial udp %s with %d states\n",
  udpp->usym->synam, nstates);
 if (udpp->u_wide) dmp_udp3v_tab(utabp, nstates);
 else dmp_udp2b_tab(utabp, nstates);
 __dbg_msg("... end dump\n");
}

/*
 * dump a non superposition 2b per element form udp table
 * input is array of words and number of inputs 
 * need more sophisticated version
 */
static void dmp_udp3v_tab(word32 *tabp, word32 nstates) 
{
 int32 bi, wi;
 word32 i;
 word32 val, ndx;
 char s1[RECLEN], s2[RECLEN];

 ndx = 0;
 for (i = 0, bi = 0; i < __pow3tab[nstates]; i++) 
  { 
   ndx = i;
   wi = get_wofs_(2*ndx);
   bi = get_bofs_(2*ndx); 
   val = (tabp[wi] >> bi) & 0x3L;
   /* RELEASE ---
   __dbg_msg("%s: %s, val=%lx, bi=%d, wi=%d\n", bld3vndx_str(s1, ndx,
    nstates), __to_uvvnam(s2, val), tabp[wi], bi, wi);
   --- */
   __dbg_msg("%s: %s\n", bld3vndx_str(s1, ndx, nstates),
    __to_uvvnam(s2, val));
  }
}

/*
 * build the input string with high value (rightmost on left)
 */
static char *bld3vndx_str(char *s, word32 ndx, word32 nstates)
{
 word32 i;
 word32 val;
 char s1[10];

 for (i = 0; i < nstates; i++)
  { val = ndx % 3; ndx /= 3; __to_uvvnam(s1, val); s[i] = s1[0]; }
 s[i] = '\0';
 return(s);
}

/*
 * dump a non superposition 2b per element form udp table
 * input is array of words and number of inputs 
 */
static void dmp_udp2b_tab(word32 *tabp, word32 nstates)
{
 word32 i;
 int32 bi, wi;
 word32 val, ndx;
 char s1[RECLEN], s2[RECLEN];

 ndx = 0;
 for (i = 0; i < (1 << (2*nstates)); i++)
  { 
   ndx = (word32) i;
   /* for narrow case, z's in signature but never used */
   if (udmp_impossible_value(ndx, nstates)) continue;

   wi = get_wofs_(2*ndx);
   bi = get_bofs_(2*ndx); 
   val = (tabp[wi] >> bi) & 0x3L;
   /* --- RELEASE
   if (__debug_flg)
    { 
     __dbg_msg("%s: %s, val=%lx, bi=%d, wi=%d\n", bldndx_str(s1, ndx,
      nstates), __to_uvvnam(s2, val), tabp[wi], bi, wi);
    }
   -- */
   __dbg_msg("%s: %s\n", bldndx_str(s1, ndx, nstates),
    __to_uvvnam(s2, val));
  }
}

/*
 * return T if somewhere there is a 2 bit 10 pattern in word
 * since for narrow know 10 index never used just 00, 01, 11
 */
static int32 udmp_impossible_value(word32 ndx, word32 nstates)
{
 word32 i;

 for (i = 0; i < nstates; i++)
  { if (((ndx >> (2*i)) & 3L) == 2L) return(TRUE); }
 return(FALSE);
}

/*
 * build the input string with high value (rightmost on left)
 */
static char *bldndx_str(char *s, word32 ndx, word32 nstates)
{
 word32 i;
 word32 val;
 char vs1[10];

 for (i = 0; i < nstates; i++)
  { val = (ndx >> (2*i)) & 3L; __to_uvvnam(vs1, val); s[i] = vs1[0]; }
 s[i] = '\0';
 return(s);
}

/*
 * dump an combinatorial udp table if not more than 5 inputs
 */
static void dmp_edge_udptab(struct udp_t *udpp)
{
 word32 *utabp;
 int32 nins, i, v;

 nins = udpp->numins;
 if (nins > 5) return;

 __dbg_msg(".. dumping edge udp %s with %d inputs\n", udpp->usym->synam,
  nins);
 __dbg_msg(" - combinatorial table:\n");
 dmp_comb_udptab(udpp);

 __dbg_msg(" - edge tables:\n");
 /* notice, edge udp always sequential and no edge for state input */
 for (i = 0; i < nins; i++)  
  {
   for (v = 0; v < 3; v++)
    {
     __dbg_msg(
      "--> input no. %d changed from %c\n", i, ((v > 1) ? 'x': '0' + v ));
     utabp = udpp->utab->eudptabs[3*i + v];
     if (udpp->u_wide) dmp_udp3v_etab(utabp, udpp->numstates, i, v);
     else dmp_udp2b_etab(utabp, udpp->numstates, i, v);
    }
  }
 __dbg_msg("... end dump\n");
}

/*
 * dump a superposition form edge udp table
 * input is array of words and number of inputs 
 * leave out lines where edge input and edge new value are same
 * know eipnum never state value
 */
static void dmp_udp3v_etab(word32 *tabp, word32 nstates, int32 eipnum,
 int32 e1val) 
{
 int32 bi, wi, ndxev;
 word32 i;
 word32 val, ndx;
 char s1[RECLEN], s2[RECLEN];

 ndx = 0;
 for (i = 0, bi = 0; i < __pow3tab[nstates]; i++) 
  { 
   ndx = i;
   bld3vndx_str(s1, ndx, nstates),
   ndxev = (s1[eipnum] == 'x') ? 2 : (s1[eipnum] - '0'); 
   if (e1val == ndxev) continue;

   wi = get_wofs_(2*ndx);
   bi = get_bofs_(2*ndx); 
   val = (tabp[wi] >> bi) & 0x3L;
   /* --- RELEASE remove
   __dbg_msg("%s: %s, val=%lx, bi=%d, wi=%d\n", s1, __to_uvvnam(s2, val),
    tabp[wi], bi, wi);
   --- */
   __dbg_msg("%s: %s\n", s1, __to_uvvnam(s2, val));
  }
}

/*
 * dump a non superposition 2b per element form udp table
 * input is array of words and number of inputs 
  * notice for 11 states size will be 1 million lines
 */
static void dmp_udp2b_etab(word32 *tabp, word32 nstates, int32 eipnum,
 int32 e1val) 
{
 word32 i, bi, wi, ndxev;
 word32 val, ndx;
 char s1[RECLEN], s2[RECLEN];

 ndx = 0L;
 for (i = 0; i < (1 << (2*nstates)); i++)
  { 
   ndx = (word32) i;
   /* for narrow case, z's in signature but never used */
   if (udmp_impossible_value(ndx, nstates)) continue;

   bldndx_str(s1, ndx, nstates);
   ndxev = (s1[eipnum] == 'x') ? 2 : (s1[eipnum] - '0'); 
   if (e1val == ndxev) continue;

   wi = get_wofs_(2*ndx);
   bi = get_bofs_(2*ndx); 
   val = (tabp[wi] >> bi) & 0x3L;
   /* RELEASE remove --- 
   __dbg_msg("%s: %s, val=%lx, bi=%d, wi=%d\n", s1, __to_uvvnam(s2, val),
    tabp[wi], bi, wi);
   --- */
   __dbg_msg("%s: %s\n", s1, __to_uvvnam(s2, val));
  }
}

/*
 * allocate the edge index and all the edge tables and set values from lines
 * know level table already filled and edge tables pointer array allocated
 */
static void prep_edge_udptab(struct udp_t *udpp)
{
 int32 i;
 int32 nins, eutabels, blen, bytsiz, tabi, e1val, e2val;
 word32 nstates;
 word32 ustate;
 struct utline_t *utlp;
 char ech, out_ch, ech2;

 nstates = udpp->numstates;
 nins = udpp->numins;
 /* these are size for 1 table in bits */
 if (udpp->u_wide) blen = comb2tabsiz[nstates];
 else blen = combtabsiz[nstates];
 /* SJM 05/19/01 - since fill using word32 ptr need to round to wrd bytes */
 bytsiz = WRDBYTES*wlen_(blen);

 /* idea is that old input value selects table, new is index in table */
 /* 1 input 3 table 0,1,x, 2 inputs 6, 3 for 1st and 3 for 2nd, ... */  
 /* state input cannot have edge */
 eutabels = 3*nins;
 /* -- RELEASE remove
 if (__debug_flg)
  __dbg_msg("## edge udp %s - %d inputs %d tables of size %d bytes\n",
   udpp->usym->synam, nins, eutabels, bytsiz); 
 -- */

 /* number of separate tables is 1 per 3*[non state ins (ins-1)] + 1 */
 /* 3 is possible values and extra 1 is for level lines without edges */
 udpp->utab = (struct udptab_t *) __my_malloc(sizeof(struct udptab_t));
 udpp->utab->ludptab = NULL;
 udpp->utab->eudptabs = (word32 **) __my_malloc(eutabels*sizeof(word32 *));
 /* build the level tab - for now always build even if no level entries */
 prep_comb_udptab(udpp);
 udpp->utab->ludptab = __cur_utab;

 /* initialize all edge tables to */
 for (i = 0; i < eutabels; i++)
  {
   __cur_utab = (word32 *) __my_malloc(bytsiz);
   init_utab(__cur_utab, blen);
   udpp->utab->eudptabs[i] = __cur_utab;
  }

 for (utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt)
  {
   __cur_utlp = utlp;
   /* if no edge, already used to set level table output */
   if (utlp->uledinum == NO_VAL) continue;

   __slin_cnt = utlp->utlin_cnt;
   __sfnam_ind = utlp->utlfnam_ind;

   /* notice 1 possible edge wild card not in wild card table */
   /* but state can be wild card */
   /* never add in edge 2nd value here, added in xpnd or const. case */
   if (utlp->ulhas_wcard) bld_wcardtab(utlp->tline, nstates, utlp->uledinum);

   /* sets any wild cards including edge 1st values will be 00 */
   /* gets converted if wide form */
   ustate = bld_uinitndx(utlp->tline, nstates, (int32) utlp->uledinum);

   /* use the previuos state - if wildcard just */
   if ((out_ch = utlp->tline[nstates]) == '-') __cur_unochange = TRUE;
   else
    { 
     /* if no '-' current output value fixed for all iterations */
     __cur_unochange = FALSE;
     /* must be 2 so if output set will match x */
     __cur_uoval = (out_ch == '0') ? 0 : ((out_ch == '1') ? 1 : 2);
    }
   /* for edge wild cards, both values same so can use first tab index */
   switch ((byte) utlp->utabsel) {
    case '*':
do_star:
     xpnd_edge_wcard(ustate, 0, 1, utlp->uledinum);
     xpnd_edge_wcard(ustate, 0, 2, utlp->uledinum);
     xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum);
     xpnd_edge_wcard(ustate, 1, 2, utlp->uledinum);
     xpnd_edge_wcard(ustate, 2, 0, utlp->uledinum);
     xpnd_edge_wcard(ustate, 2, 1, utlp->uledinum);
     break;
    case 'p':
     /* potential rising edge */
     xpnd_edge_wcard(ustate, 0, 1, utlp->uledinum);
     xpnd_edge_wcard(ustate, 0, 2, utlp->uledinum);
     xpnd_edge_wcard(ustate, 2, 1, utlp->uledinum);
     break;
    case 'n':
     /* potential falling edge */
     xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum);
     xpnd_edge_wcard(ustate, 1, 2, utlp->uledinum);
     xpnd_edge_wcard(ustate, 2, 0, utlp->uledinum);
     break;
    case '?':
     ech2 = utlp->tline[utlp->uledinum];
     /* notice (..) form can be value or b or ? but not edge abbreviation */
     /* also notice for edge only wildcard is possible '-' */
     switch (ech2) {
      case '?':
       /* (\?\?) is same as * */
       goto do_star;
      case 'b':
       /* (?b) */
       xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum);
       xpnd_edge_wcard(ustate, 2, 0, utlp->uledinum);
       xpnd_edge_wcard(ustate, 0, 1, utlp->uledinum);
       xpnd_edge_wcard(ustate, 2, 1, utlp->uledinum);
       break;
      case '0':
       /* (?0) */
       xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum);
       xpnd_edge_wcard(ustate, 2, 0, utlp->uledinum);
       break;
      case '1':
       /* (?1) */
       xpnd_edge_wcard(ustate, 0, 1, utlp->uledinum);
       xpnd_edge_wcard(ustate, 2, 1, utlp->uledinum);
       break;
      case 'x':  
       /* (?x) */
       xpnd_edge_wcard(ustate, 0, 2, utlp->uledinum);
       xpnd_edge_wcard(ustate, 1, 2, utlp->uledinum);
       break;
      default: __case_terr(__FILE__, __LINE__);
     }
     break;
    case 'b': 
     ech2 = utlp->tline[utlp->uledinum];
     switch (ech2) {
      case '?':
       /* (b?) */
       xpnd_edge_wcard(ustate, 0, 1, utlp->uledinum);
       xpnd_edge_wcard(ustate, 0, 2, utlp->uledinum);
       xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum);
       xpnd_edge_wcard(ustate, 1, 2, utlp->uledinum);
       break;
      case 'b':
       /* (bb) */
       xpnd_edge_wcard(ustate, 0, 1, utlp->uledinum);
       xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum);
       break;
      case '0':
       /* (b0) */
       xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum);
       break;
      case '1':
       /* (b1) */
       xpnd_edge_wcard(ustate, 0, 0, utlp->uledinum);
       break;
      case 'x':
       /* (bx) */
       xpnd_edge_wcard(ustate, 0, 2, utlp->uledinum);
       xpnd_edge_wcard(ustate, 1, 2, utlp->uledinum);
       break;
      default: __case_terr(__FILE__, __LINE__);
     }
     break;
    case '0': case '1': case 'x':
     /* notice ech is case index for output tab too */
     ech = (char) utlp->utabsel;
     /* may have ([01x][?b]) style wild card form  */
     ech2 = utlp->tline[utlp->uledinum];
     if (ech2 == '?')
      {
       switch (ech) {
        case '0':
         xpnd_edge_wcard(ustate, 0, 1, utlp->uledinum);
         xpnd_edge_wcard(ustate, 0, 2, utlp->uledinum);
         break;
        case '1':
         xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum);
         xpnd_edge_wcard(ustate, 1, 2, utlp->uledinum);
         break;
        case 'x':
         xpnd_edge_wcard(ustate, 2, 0, utlp->uledinum);
         xpnd_edge_wcard(ustate, 2, 1, utlp->uledinum);
         break;
        default: __case_terr(__FILE__, __LINE__); 	   
       }
       break;
      }
     if (ech2 == 'b')
      {
       switch (ech) {
        case '0': xpnd_edge_wcard(ustate, 0, 1, utlp->uledinum); break;
        case '1': xpnd_edge_wcard(ustate, 1, 0, utlp->uledinum); break;
        case 'x':
         xpnd_edge_wcard(ustate, 2, 0, utlp->uledinum);
         xpnd_edge_wcard(ustate, 2, 1, utlp->uledinum);
         break;
        default: __case_terr(__FILE__, __LINE__);
       }
       break;
      }

     e1val = (ech == '0') ? 0 : ((ech == '1') ? 1 : 2);
     tabi = 3*utlp->uledinum + e1val;

     /* non edge wild card case - must add in 2nd edge part of state */
     /* know contribution before here 0 */
     e2val = (ech2 == '0') ? 0 : ((ech2 == '1') ? 1 : 2);
     if (udpp->u_wide) ustate += (e2val*__pow3tab[utlp->uledinum]); 
     else
      {
       /* SJM 03-16-12 - need to set (0x) or (1x) here to 3 for non wide */
       /* needed to match set 1 wcard routine */
       if (e2val == 2) e2val = 3;
       ustate |= (e2val << (2*utlp->uledinum));
      }

     /* RELEASE remove --- 
     if (__debug_flg)
      __dbg_msg(
       "=== non wildcard input edge (%c%c) with from value %d - table %d\n",
       utlp->uledinum, ech, ech2, tabi);
     --- */
     /* once current table corresponding to edge is set, just like level */
     __cur_utab = udpp->utab->eudptabs[tabi];
     if (!utlp->ulhas_wcard) setchk_uval(ustate);
     else xpnd_1wcard(0, ustate);
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 /* final step is conversion of x (set x) to 3 real x */ 
 for (i = 0; i < eutabels; i++)
  {
   __cur_utab = udpp->utab->eudptabs[i];
   chg_unfilled_tox(__cur_utab, blen);
  }
}

/*
 * process edge wildcard entry - passed fixed edge generated from iteration
 * e1 val selects table and e2 val is table value (changed to)  
 */
static void xpnd_edge_wcard(word32 ustate, int32 e1val, int32 e2val,
 word32 einpnum)
{
 int32 tabi;

 /* first select the table */
 tabi = 3*einpnum + e1val;
 /* --- RELEASE remove 
 if (__debug_flg)
  __dbg_msg("=== expand wildcard input edge %d from value %d - table %d\n",
   einpnum, e1val, tabi);
 --- */
 /* once current table corresponding to edge is set, just like level */
 __cur_utab = __cur_udp->utab->eudptabs[tabi];

 /* must set ustate input no. einpnum to ech2 value - know 0 on input */
 /* know this can never be last previous state input or will not get here */
 /* ustate is 2 bit per element form */
 /* ustate is table index so for narrow form must be 3 */
 if (__cur_udp->u_wide) ustate += e2val*__pow3tab[einpnum];
 else
  {
   /* ustate is index which for narrow must be 3 - value is 2 */
   if (e2val == 2) e2val = 3;
   ustate |= (((word32) e2val) << (2*einpnum));
  }

 /* need some global to be set for errors */
 __cur_ueipnum = einpnum;
 __cur_utabsel = e1val;

 /* ulhas_wcard is only level wildcard */
 if (!__cur_utlp->ulhas_wcard) setchk_uval(ustate);
 else xpnd_1wcard(0, ustate);
}

/*
 * free udp lines
 * only called for uninstantiated udps since size small and needed for PLI
 */
static void free_udp_lines(struct udp_t *udpp)
{
 struct utline_t *utlp, *utlp2;

 for (utlp = udpp->utlines; utlp != NULL;)
  {
   utlp2 = utlp->utlnxt;
   /* notice this is not 0 terminated string */
   __my_free(utlp->tline, (int32) utlp->ullen);
   __my_free(utlp, sizeof(struct utline_t));
   utlp = utlp2;
  }
 udpp->utlines = NULL;
}

/*
 * ROUTINES TO CHANGE ALL WIRE RANGE REPS 
 */

/*
 * change representation and allocate sim net struct for every net range
 * must do unused var. checking before change range rep since uses ncomp
 * range form bits
 *
 * BEWARE - for normal nets allocating nu.ct to large chunk area because
 * freeing too slow - but here for params (also specparams) since cannot
 * distinguish must copy since now can be annotated too
 *
 * AIV 01/19/07 - need to do local params here as well for mod and tasks
 * 09/27/06 - local params not used in delay annotation so not copied here
 */
static void change_all_rngreps(void)
{
 int32 ni;
 int32 pi, sav_declobj;
 struct net_t *np;
 struct ncomp_t *oncomp, *nncomp;
 struct mod_t *mdp;
 struct task_t *tskp;

 sav_declobj = __cur_declobj;
 __cur_declobj = MODULE;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   __cur_declobj = MODULE;

   if (__inst_mod->mnnum != 0) 
    {
     for (ni = 0, np = &(__inst_mod->mnets[0]); ni < __inst_mod->mnnum;
      ni++, np++)
      {
//SJM FIXME - why both
        {
         /* expect inout ports to be set but not used or used but not set */
         if (np->iotyp != IO_BID)
          emit_varunused_informs(np, (struct task_t *) NULL);
        }
       set_optim_nflds(np, __inst_mod->mod_dumpports_in_src);
       rt_change_rngrep(np); 
      }
    } 
   /* copy ncomp that are still needed for delay annotation */
   /* needed because ncomps allocated and freed in blocks */
   for (pi = 0; pi < __inst_mod->mprmnum; pi++)  
    {
     np = &(__inst_mod->mprms[pi]);
     oncomp = np->nu.ct;
     nncomp = (struct ncomp_t *) __my_malloc(sizeof(struct ncomp_t));
     /* expressions not freed and copied will point to right ones */ 
     memcpy(nncomp, oncomp, sizeof(struct ncomp_t));
     np->nu.ct = nncomp;
    }

   /* AIV 01/19/07 - need to do local params here as well */
   for (pi = 0; pi < __inst_mod->mlocprmnum; pi++)  
    {
     np = &(__inst_mod->mlocprms[pi]);
     oncomp = np->nu.ct;
     nncomp = (struct ncomp_t *) __my_malloc(sizeof(struct ncomp_t));
     /* expressions not freed and copied will point to right ones */ 
     memcpy(nncomp, oncomp, sizeof(struct ncomp_t));
     np->nu.ct = nncomp;
    }

   /* AIV 09/27/06 - do not need copy for local params since */
   /* can't be set with SDF label annotate */
   __cur_declobj = TASK; 
   for (tskp = __inst_mod->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;

     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       emit_varunused_informs(np, tskp);

       set_optim_nflds(np, FALSE);
       rt_change_rngrep(np); 
      }
     /* copy ncomp that are still needed for delay annotation */
     /* needed because ncomps allocated and freed in blocks */
     for (pi = 0; pi < tskp->tprmnum; pi++)  
      {
       np = &(tskp->tsk_prms[pi]);
       oncomp = np->nu.ct;
       nncomp = (struct ncomp_t *) __my_malloc(sizeof(struct ncomp_t));
       /* expressions not freed and copied will point to right ones */ 
       memcpy(nncomp, oncomp, sizeof(struct ncomp_t ));
       np->nu.ct = nncomp;
      }
     /* AIV 01/19/07 - need to do local params here as well */
     for (pi = 0; pi < tskp->tlocprmnum; pi++)  
      {
       np = &(tskp->tsk_locprms[pi]);
       oncomp = np->nu.ct;
       nncomp = (struct ncomp_t *) __my_malloc(sizeof(struct ncomp_t));
       /* expressions not freed and copied will point to right ones */ 
       memcpy(nncomp, oncomp, sizeof(struct ncomp_t ));
       np->nu.ct = nncomp;
      }
    }
   if (__inst_mod->mspfy != NULL)
    {
     __cur_declobj = SPECIFY;
     for (pi = 0; pi < __inst_mod->mspfy->sprmnum; pi++)  
      {
       np = &(__inst_mod->mspfy->msprms[pi]);
       oncomp = np->nu.ct;
       nncomp = (struct ncomp_t *) __my_malloc(sizeof(struct ncomp_t));
       /* expressions not freed and copied will point to right ones */ 
       memcpy(nncomp, oncomp, sizeof(struct ncomp_t ));
       np->nu.ct = nncomp;
      }
    }
   __pop_wrkitstk();
  }

 __cur_declobj = sav_declobj;
 free_ncablks();
}

/*
 * copy fields form ncomp into run time net fields
 *
 * LOOAKTME - think no longer need 2 step setting of optim fields
 */
static void set_optim_nflds(struct net_t *np, int32 mod_has_dumpports)
{
 np->frc_assgn_allocated = FALSE;
 np->dmpv_in_src = FALSE;
 np->monit_in_src = FALSE;
 np->n_onrhs = FALSE;
 np->n_onlhs = FALSE;
 
 if (np->nu.ct->frc_assgn_in_src) np->frc_assgn_allocated = TRUE;
 if (np->nu.ct->dmpv_in_src) np->dmpv_in_src = TRUE;
//AIV DUMP - could just set in v_fx3.c????
 if (mod_has_dumpports)
  {
   if (np->iotyp != NON_IO)
    {
     np->dmpp_in_src = TRUE;
    }
  }
 if (np->nu.ct->monit_in_src) np->monit_in_src = TRUE;
 if (np->nu.ct->n_onrhs) np->n_onrhs = TRUE;
 if (np->nu.ct->n_onlhs) np->n_onlhs = TRUE;
}


/*
 * routine to free all allocated ncmp blks when no longed used at all
 *
 * this frees all ncomps but param comp previously copied because needed
 * for delay annotation
 */
static void free_ncablks(void)
{
 struct ncablk_t *ncabp, *ncabp2;

 /* free all ncomp ablks since ncomp form now gone */
 for (ncabp = __hdr_ncablks; ncabp != NULL;)
  {
   ncabp2 = ncabp->ncablknxt;
   __my_free(ncabp->ancmps, BIG_ALLOC_SIZE);
   __my_free(ncabp, sizeof(struct ncablk_t));
   ncabp = ncabp2;
  }
}

/*
 * emit any unused inform
 * notice this is called just before change to non comp representation
 */
static void emit_varunused_informs(struct net_t *np, struct task_t *tskp)
{
 struct ncomp_t *ncmp;
 int32 infnum;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN];

 ncmp = np->nu.ct;
 if (ncmp->n_onrhs && ncmp->n_onlhs) return;

 if (tskp != NULL)
  {
   switch (tskp->tsktyp) {
    case Begin: strcpy(s2, "in begin block"); break;
    case FORK: strcpy(s2, "in fork block"); break;
    case FUNCTION: strcpy(s2, "in function"); break;
    case TASK: strcpy(s2, "in task"); break;
    default: __case_terr(__FILE__, __LINE__);   
   }
   sprintf(s1, "%s %s in %s", s2, tskp->tsksyp->synam,
    __inst_mod->msym->synam);
  }
 else sprintf(s1, "in module %s", __inst_mod->msym->synam);
 
 if (np->n_isarr) strcpy(s2, "array"); else __to_wtnam(s2, np);

 if (np->ntyp == N_EVENT)
  {
   if (!ncmp->n_onrhs && !ncmp->n_onlhs)
    { strcpy(s3, "unused"); infnum = 436; }
   else if (!ncmp->n_onrhs && ncmp->n_onlhs)
    { strcpy(s3, "caused but used in no event control"); infnum = 437; }
   else { strcpy(s3, "used in event control but not caused"); infnum = 438; }
  }
 else
  {
   if (!ncmp->n_onrhs && !ncmp->n_onlhs) { strcpy(s3, "unused");
    infnum = 436; }
   else if (!ncmp->n_onrhs && ncmp->n_onlhs)
    { strcpy(s3, "set but not accessed"); infnum = 437; }
   else { strcpy(s3, "accessed but not set"); infnum = 438; }
  } 

 /* if completely unreferenced normal inform */
 if (np->iotyp == NON_IO || infnum == 436)
  {
   __gfinform(infnum, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
    "%s: %s %s %s", s1, s2, np->nsym->synam, s3);
  } 
 else
  {
   if (infnum == 437) infnum = 467;
   else if (infnum == 438) infnum = 468;
   else __case_terr(__FILE__, __LINE__);

   __gfinform(infnum, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
    "%s: %s %s %s %s", s1, __to_ptnam(s4, np->iotyp), s2, np->nsym->synam,
    s3);
  }
}

/*
 * change auxiliary nx from compile to run time (numbers) form
 * only for wires (and regs)
 *
 * notice this is place nwid set
 * also after here ncomps gone
 */
static void rt_change_rngrep(struct net_t *np)
{
 int32 bi;
 int32 nni1, nni2, nai1, nai2, bits, i, dim, nels, arrwid;
 struct mda_t *mdap;
 struct ncomp_t *ncmp;
 struct rngarr_t *rap;
 struct rngdwir_t *rdwp;
 struct gate_t gwrk;
 struct rngwir_t *rwp;

 /* in XL parameters can be regs at run time */
 /* not legal in standard so must catch before here */
 /* DBG remove --- */
 if (np->n_isaparam || np->nrngrep != NX_CT)
  __arg_terr(__FILE__, __LINE__);
 /* -- */

 ncmp = np->nu.ct;

 /* know this is number since range */
 if (np->n_isavec)
  {
   nni1 = (int32) __contab[ncmp->nx1->ru.xvi];
   nni2 = (int32) __contab[ncmp->nx2->ru.xvi];

   /* AIV 02/24/10 - LRM allows negative indices */
   /* if (nni1 == -1 || nni2 == -2) __arg_terr(__FILE__, __LINE__); */
   np->nwid = ((nni1 >= nni2) ? (nni1 - nni2 + 1) : (nni2 - nni1 + 1));
   /* AIV 08/25/10 - need the max vector size for empty bpart for */
   /* the interp for 2-state */
   if (np->nwid > __max_net_blen) __max_net_blen = np->nwid;
   /* need to handle options that set default splitting state */
   switch (ncmp->n_spltstate) {
    case SPLT_DFLT:
     np->vec_scalared = (__no_expand) ? FALSE : TRUE;
     break;
    case SPLT_SCAL: np->vec_scalared = TRUE; break;
    case SPLT_VECT: np->vec_scalared = FALSE; break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 /* scalar wire has vec scalared off since 1 bit treated as entity */
 else { np->vec_scalared = FALSE; np->nwid = 1; nni1 = nni2 = 0; }

 /* registers and arrays always vectored (non split into bits) */  
 /* AIV 09/17/07 - registers are always scalared without vectored keyword */
 if (np->ntyp >= NONWIRE_ST) np->vec_scalared = TRUE;
 else
  {
   if (np->n_stren && np->n_isavec && !np->vec_scalared)
    {
     __gferr(982, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
      "non scalar strength wire %s cannot be vectored", np->nsym->synam);
    }
  }

 if (np->n_isarr)
  {
   /* range is normal net width for mda as well */
   rap = (struct rngarr_t *) __my_malloc(sizeof(struct rngarr_t));
   rap->ni1 = nni1;
   rap->ni2 = nni2;
   /* if net is multi allocate ranges */
   mdap = np->mda; 
   if (mdap != NULL)
    {
     /* set the net width */
     mdap->ni1 = nni1;
     mdap->ni2 = nni2;
     /* allocate space for the ranges and the dimension multiplier */
     dim = mdap->dimension;
     /* AIV 02/25/09 - these may have already been alloc - due to the */
     /* vectorize of wire arrays in v_fx */
     if (mdap->rng1 == NULL)
      {
       mdap->rng1 = (int32 *) __my_malloc(sizeof(int32)*dim);
       mdap->rng2 = (int32 *) __my_malloc(sizeof(int32)*dim);
       mdap->dim_mult = (int32 *) __my_malloc(sizeof(int32)*dim);
      }
     /* AIV 07/19/10 - need to record the number of elements in the array */
     /* for optional array dumping */
     nels = 0;
     for (i = 0; i < dim; i++)
      {
       nai1 = (int32) __contab[mdap->tab_ax1[i]->ru.xvi];
       mdap->rng1[i] = nai1;
       nai2 = (int32) __contab[mdap->tab_ax2[i]->ru.xvi];
       mdap->rng2[i] = nai2;
       /* compute and store the multiplier to avoid computing at runtime */
       mdap->dim_mult[i] = __mda_multiplier(np, i);
       arrwid = (nai1 > nai2) ? nai1 - nai2 + 1 : nai2 - nai1 + 1;
       if (i == 0)
        {
         rap->ai1 = nai1;
         rap->ai2 = nai2;
         nels = arrwid;
        }
       else nels *= arrwid;
      }
     np->arr_num_els = nels;
    }
   else
    {
     nai1 = (int32) __contab[ncmp->ax1->ru.xvi];
     nai2 = (int32) __contab[ncmp->ax2->ru.xvi];

     rap->ai1 = nai1;
     rap->ai2 = nai2;
     /* AIV 07/19/10 - need to record the number of elements in the array */
     /* for optional array dumping */
     arrwid = (nai1 > nai2) ? nai1 - nai2 + 1 : nai2 - nai1 + 1;
     np->arr_num_els = arrwid;
    }
   np->nu.rngarr = rap;
   np->nrngrep = NX_ARR;
  }
 else if (ncmp->n_dels_u.pdels != NULL || np->n_isapthdst)
  {
   /* path dest. can not have delays */
   /* if has delay and path dest., turn off dst. to cause later error */
   if (ncmp->n_dels_u.pdels != NULL)
    { if (np->n_isapthdst) np->n_isapthdst = FALSE; }

   rdwp = (struct rngdwir_t *) __my_malloc(sizeof(struct rngdwir_t));
   rdwp->ni1 = nni1;
   rdwp->ni2 = nni2;

   if (!np->n_isapthdst)
    {
     /* add any defparams (or spec but impossible) to param np list */
     add_netdel_pnp(np, np->nu.ct->n_dels_u.pdels);
     /* preprocess wire delays into indexable array or value */
     __prep_delay(&gwrk, np->nu.ct->n_dels_u.pdels, FALSE,
      (np->ntyp == N_TRIREG), "path delay", TRUE, np->nsym, FALSE); 

     if (__nd_neg_del_warn)
      {
       __gferr(971, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
        "wire %s delay negative (0 used)", np->nsym->synam);
       __nd_neg_del_warn = FALSE;
      } 

     rdwp->n_delrep = gwrk.g_delrep;
     /* is union assign portable */
     rdwp->n_du = gwrk.g_du;
    }
   /* this is allocated and filled later */
   else { rdwp->n_delrep = DT_PTHDST; rdwp->n_du.pb_pthdst = NULL; }

   /* must allocate the per bit pending scheduled value */
   bits = __inst_mod->flatinum*np->nwid;
   rdwp->wschd_pbtevs = 
     (struct tev_t **) __my_malloc(bits*sizeof(struct tev_t *));
   for (bi = 0; bi < bits; bi++) rdwp->wschd_pbtevs[bi] = NULL;
   np->nu.rngdwir = rdwp;
   np->nrngrep = NX_DWIR;
  }
 else
  {
   /* finally any other wire */
   if (np->n_isavec) 
    {
     rwp = (struct rngwir_t *) __my_malloc(sizeof(struct rngwir_t));
     rwp->ni1 = nni1;
     rwp->ni2 = nni2;
     np->nu.rngwir = rwp;
     np->nrngrep = NX_WIR;
    }
   else { np->nu.rngwir = NULL; np->nrngrep = NX_SCALWIR; }
  }
 /* just free the expressions since if arg. nil does nothing */
 __free_xtree(ncmp->nx1);
 __free_xtree(ncmp->nx2);
 __free_xtree(ncmp->ax1);
 __free_xtree(ncmp->ax2);
} 

/*
 * compute the multi-dimensional array multiplier value
 */
extern int32 __mda_multiplier(struct net_t *np, int32 di)
{
 int32 i, r1, r2, mult, dwid, dim;
 struct mda_t *mdap; 

 mdap = np->mda;
 mult = 1;
 dim = mdap->dimension;
 for (i = di+1; i < dim; i++)
  {
   __getarr_range_mda(np, &r1, &r2, &dwid, i);
   mult *= dwid;
  }
 return(mult);
}

/*
 * ROUTINES TO ALLOCATE AND INITIALIZE GATE INTERNAL STATE
 */

/*
 * 
 * build the schedule array and gate state value for each gate
 * also prepares delays
 */
static void bld_gstate(void)
{
 int32 gi;
 struct mod_t *mdp;
 struct gate_t *gp;

 /* for each module in design */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   for (gi = 0; gi < mdp->mgnum; gi++)
    {
     gp = &(mdp->mgates[gi]);

     /* pull gate (really source) has no state or scheduled events */
     /* no state for trans */ 
     if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN) continue;

     /* if output unc. (OPEMPTY), changes are not seen (do not propagate) */
     if (gp->g_class != GC_TRANIF && gp->gpins[0]->optyp == OPEMPTY)
      continue;

     if (gp->g_du.pdels == NULL)
      { gp->g_du.d1v = NULL; gp->g_delrep = DT_NONE; }
     else
      {
       add_gatedel_pnp(gp, gp->g_du.pdels);
       __prep_delay(gp, gp->g_du.pdels, FALSE, FALSE, "primitive delay",
        FALSE, gp->gsym, FALSE);
       if (__nd_neg_del_warn)
        {
         __gferr(972, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
          "gate %s delay negative (0 used)", gp->gsym->synam);
         __nd_neg_del_warn = FALSE;
        } 
      }
     /* remove #0 if special option on - annotation may put back */ 
     if (__rm_gate_pnd0s)
      {
       if (__chk_0del(gp->g_delrep, gp->g_du, mdp) == DBAD_0) 
        {
         __num_rem_gate_pnd0s++; 
         __num_flat_rem_gate_pnd0s += mdp->flatinum;
         __free_del(gp->g_du, gp->g_delrep, mdp->flatinum);
         gp->g_du.d1v = NULL;
         gp->g_delrep = DT_NONE;
        }
      }
     /* only gates have gstate, eval. for conta (can be func. on rhs) */
    }
   __pop_wrkitstk();
  }
}

/*
 * prep conta delays
 *
 * SJM 09/28/02 - even for rhs concat PB separated, delay in master
 */
static void prep_conta_dels(void)
{
 int32 cai, ci;
 struct mod_t *mdp;
 struct conta_t *cap;
 struct conta_t *pb_cap;
 struct gate_t gwrk;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   for (cap = &(mdp->mcas[0]), cai = 0; cai < mdp->mcanum; cai++, cap++)
    {
     /* 1 bit lhs conta delays like gate delays - 3rd arg determines */
     if (cap->ca_du.pdels == NULL)
      { 
       cap->ca_du.d1v = NULL; 
       cap->ca_delrep = DT_NONE; 
       /* AIV 03/20/07 - wasn't setting pb assigns delays to null */
       /* need for linking in compiler */
       if (__compiled_sim)
        {
         if (cap->ca_pb_sim)
          {
           for (ci = 0; ci < cap->lhsx->szu.xclen; ci++) 
            {
             pb_cap = &(cap->pbcau.pbcaps[ci]);
             pb_cap->ca_du.d1v = NULL; 
             pb_cap->ca_delrep = DT_NONE; 
            }
          }
        }
      }
     else
      {
       add_contadel_pnp(cap, cap->ca_du.pdels);
       __prep_delay(&gwrk, cap->ca_du.pdels, FALSE, FALSE,
        "continuous assignment delay", FALSE, cap->casym, FALSE);
       if (__nd_neg_del_warn)
        {
         __gferr(973, cap->casym->syfnam_ind, cap->casym->sylin_cnt,
          "continuous assign delay negative (0 used)");
         __nd_neg_del_warn = FALSE;
        } 
       cap->ca_du = gwrk.g_du;
       cap->ca_delrep = gwrk.g_delrep;
       /* SJM 09/28/02 - now set ca 4v del during fixup */ 
      }
    }
   __pop_wrkitstk();
  }
}

/*
 * ROUTINES TO BUILD PER BIT INPUT PORT ICONN PINS, MOD PORTS, and CONCATS
 */

/*
 * bld the separated per bit iconn rhs net pins for one iconn
 *
 * notice building one PB for every down mod port bit - if highconn inst
 * conn wider nothing to change if and mod port wider unc. no value
 * since pb not used for initialization
 */
static void bld_pbsep_input_mpps(void)
{
 int32 pi, bi;
 int32 ii, pi2, numpins, ptyp;
 struct mod_t *mdp;
 struct mod_t *imdp;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct expr_t *xp, *xp2;
 struct pbexpr_t *pbexpr;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* first process all instances in module */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((numpins = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < numpins; pi++)
      {
       mpp = &(imdp->mpins[pi]);
       xp = ip->ipins[pi];
       ptyp = mpp->mptyp;
       if (ptyp != IO_IN) continue; 
       /* notice decl lhs always separable but no separate unless hconn cat */
       if (!rhs_cat_separable(xp)) continue;

       if (ip->pb_ipins_tab == NULL)
        {
         ip->pb_ipins_tab = (struct expr_t ***)
          __my_malloc(numpins*sizeof(struct expr_t **));
         for (pi2 = 0; pi2 < numpins; pi2++) ip->pb_ipins_tab[pi2] = NULL;
        }
       /* all bits filled below */
       ip->pb_ipins_tab[pi] = (struct expr_t **)
        __my_malloc(mpp->mpwide*sizeof(struct expr_t *));
       
       pbexpr = __bld_pb_expr_map(xp, mpp->mpwide);
       for (bi = 0; bi < mpp->mpwide; bi++)
        {
         /* for unc. (lhs wider) builds the constant rhs 0/z */
         xp2 = bld_1sep_pbit_expr(&(pbexpr[bi]), xp->x_stren);
         ip->pb_ipins_tab[pi][bi] = xp2;
        }
       __my_free(pbexpr, numpins*sizeof(struct pbexpr_t));

       /* T means at least one highconn iconn is per bit concat */
       mpp->has_scalar_mpps = TRUE;
      }
    }
   __pop_wrkitstk();
  }

 /* always build separated per bit mpps if any hconn separable concat */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   numpins = mdp->mpnum;
   for (pi = 0; pi < numpins; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     ptyp = mpp->mptyp;
     if (ptyp != IO_IN) continue; 
     if (!mpp->has_scalar_mpps) continue;
     bld_pb_mpps(mpp);
    }
   __pop_wrkitstk();
  }
}

/*
 * bld the separated per bit output mod port lhs net pins for one iconn
 *
 * this is symmetric case to bld per bit separable mpps and and iconn 
 * pb ipins tabs for output but here as long as all highconns for port
 * can be separated into bits will separate if any low conn or high concats
 *
 * can only build PB records for output ports if all iconn widths exactly
 * same as mod port width
 */
static void bld_pbsep_output_mpps(void)
{
 int32 pi, bi;
 int32 ii, pi2, numpins, ptyp;
 struct mod_t *mdp;
 struct mod_t *imdp;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct expr_t *xp, *xp2;
 struct pbexpr_t *pbexpr;

 if (!output_pb_separable()) return;

 /* first bld per bit ipins tab for output port lhs separable highconns */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* process all instances in module */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((numpins = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < numpins; pi++)
      {
       mpp = &(imdp->mpins[pi]);
       ptyp = mpp->mptyp;
       if (ptyp != IO_OUT) continue; 
       if (!mpp->has_scalar_mpps) continue;
       xp = ip->ipins[pi];

       if (ip->pb_ipins_tab == NULL)
        {
         ip->pb_ipins_tab = (struct expr_t ***)
          __my_malloc(numpins*sizeof(struct expr_t **));
         for (pi2 = 0; pi2 < numpins; pi2++) ip->pb_ipins_tab[pi2] = NULL;
        }
       /* all bits filled below - know lhs iconn and rhs mpp same width */
       ip->pb_ipins_tab[pi] = (struct expr_t **)
        __my_malloc(mpp->mpwide*sizeof(struct expr_t *));
       
       pbexpr = __bld_pb_expr_map(xp, mpp->mpwide);
       for (bi = 0; bi < mpp->mpwide; bi++)
        {
         xp2 = bld_1sep_pbit_expr(&(pbexpr[bi]), xp->x_stren);
         ip->pb_ipins_tab[pi][bi] = xp2;
        }
       __my_free(pbexpr, numpins*sizeof(struct pbexpr_t));
      }
    }
   __pop_wrkitstk();
  }

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   numpins = mdp->mpnum;
   for (pi = 0; pi < numpins; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     ptyp = mpp->mptyp;
     if (ptyp != IO_IN) continue; 
     if (!mpp->has_scalar_mpps) continue;
     bld_pb_mpps(mpp);
    }
   __pop_wrkitstk();
  }
}

/*
 * mark each mod output port that can be and gains from separate into PB form
 * return T if some ports can be separated into PB form
 * 
 * separable only if more than half total highconn inst connections separble
 * and concats not too narrow only counted
 */
static int32 output_pb_separable(void)
{
 int32 pi, ii;
 int32 numpins, nels, num_cat_insts, not_pbsep, some_pbsep;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 struct itree_t *down_itp;
 struct expr_t *up_lhsx;

 /* first go through and make sure all high conns can be separated into pb */ 
 some_pbsep = FALSE;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* SJM 11/19/02 - if top level mod, never separable since no highconn */
   if (mdp->minstnum == 0) continue;

   if ((numpins = mdp->mpnum) == 0) continue;
   __push_wrkitstk(mdp, 0);
   for (pi = 0; pi < numpins; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     if (mpp->mptyp != IO_OUT) continue;


     /* if down rhs lowconn mod port not separable, can't PB separate any */
     if (!rhs_modpin_separable(mpp->mpref)) continue;
   
     num_cat_insts = 0; 
     not_pbsep = FALSE;
     for (ii = 0; ii < mdp->flatinum; ii++) 
      {
       down_itp = mdp->moditps[ii];
       /* LOOKATME - is nil here possible? */
       up_lhsx = down_itp->itip->ipins[pi];
       if (up_lhsx->optyp != LCB) continue;

       /* if any width differences, can't separate */
       /* LOOKATME - is this really required? */
       if (mpp->mpref->szu.xclen != up_lhsx->szu.xclen)  
        { not_pbsep = TRUE; break; }

       nels = __cnt_cat_size(up_lhsx);
       /* only gain from separate if 4 or more els and wider than 4 bits */
       /* LOOKATME - if many wide per bit maybe not better */
       if (nels < 4 || up_lhsx->szu.xclen < 4) continue;
       num_cat_insts++;
      }
     if (num_cat_insts/2 < mdp->flatinum) not_pbsep = TRUE;
     if (!not_pbsep)
      {
       some_pbsep = TRUE;
       mpp->has_scalar_mpps = TRUE;
      }
    }
   __pop_wrkitstk();
  }
 return(some_pbsep);
}

/*
 * build per bit mpps for simulation 
 */
static void bld_pb_mpps(struct mod_pin_t *mpp)
{
 int32 bi;
 struct mod_pin_t *mpp2;
 struct expr_t *xp;
 struct pbexpr_t *pbexpr;

 xp = mpp->mpref;
 pbexpr = __bld_pb_expr_map(xp, mpp->mpwide);
 mpp->pbmpps = (struct mod_pin_t *)
  __my_malloc(mpp->mpwide*sizeof(struct mod_pin_t));
 for (bi = 0; bi < mpp->mpwide; bi++)
  {
   /* fields except for per bit same */
   mpp->pbmpps[bi] = *mpp;
   mpp2 = &(mpp->pbmpps[bi]);
   /* since expr copied for ID/XMR part, stren and other bits set right */
   xp = bld_1sep_pbit_expr(&(pbexpr[bi]), mpp2->mpref->x_stren);
   mpp2->mpref = xp;
   mpp2->mpwide = 1;
   mpp2->pbmpps = NULL;
   mpp2->has_scalar_mpps = FALSE;
  }
 __my_free(pbexpr, mpp->mpwide*sizeof(struct pbexpr_t));
}

/*
 * bld the separated per bit rhs concat - stored in non pb concat 
 */
static void bld_pb_contas(void)
{
 int32 bi;
 int32 cawid, cai;
 struct mod_t *mdp;
 struct conta_t *cap, *pbcap;
 struct expr_t *lhsx, *xp2, *xp3;
 struct pbexpr_t *rhs_pbexpr, *lhs_pbexpr;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   for (cap = &(mdp->mcas[0]), cai = 0; cai < mdp->mcanum; cai++, cap++)
    {
     /* if not concat expr, should not separate so this returns F */
     if (!rhs_cat_separable(cap->rhsx)) continue;

     /* SJM 09/28/02 - now always use per bit for rhs concat */
     /* fi>1 works and may allow per bit driver load and 4v delay works */
     /* because evaluates all bits of rhs during sim */
     lhsx = cap->lhsx;
     cawid = lhsx->szu.xclen;
     cap->ca_pb_sim = TRUE;
     cap->pbcau.pbcaps = (struct conta_t *)
      __my_malloc(cawid*sizeof(struct conta_t));
     for (bi = 0; bi < cawid; bi++)
      {
       cap->pbcau.pbcaps[bi] = *cap;
       pbcap = &(cap->pbcau.pbcaps[bi]);
       /* SJM 08/28/02 - sym and delays in mast not per bit */
       pbcap->casym = NULL;
       pbcap->ca_du.pdels = NULL;
       pbcap->ca_pb_sim = FALSE;
       pbcap->ca_pb_el = TRUE;
       pbcap->pbcau.mast_cap = cap;
       if (__compiled_sim) pbcap->enter_cndx = ++__cap_seq_no;
       else pbcap->enter_cndx = -1;
       pbcap->flowg = NULL;
      }

     rhs_pbexpr = __bld_pb_expr_map(cap->rhsx, cawid);
     lhs_pbexpr = __bld_pb_expr_map(lhsx, cawid);
     for (bi = 0; bi < cawid; bi++)
      {
       pbcap = &(cap->pbcau.pbcaps[bi]);
       /* if lhs too narrow, 0/z determened by whether lhs stren */
       xp2 = bld_1sep_pbit_expr(&(rhs_pbexpr[bi]), lhsx->x_stren);
       pbcap->rhsx = xp2;

       xp3 = bld_1sep_pbit_expr(&(lhs_pbexpr[bi]), lhsx->x_stren);
       pbcap->lhsx = xp3;
       if (cap->lhsx->x_multfi) pbcap->lhsx->x_multfi = TRUE;
      }
     __my_free(rhs_pbexpr, cawid*sizeof(struct pbexpr_t));
     __my_free(lhs_pbexpr, cawid*sizeof(struct pbexpr_t));
    }
   __pop_wrkitstk();
  }
}

/*
 * return T if separable into per bit rhs concat 
 * now called with any expr 
 *
 * all elements must be simple
 * think width self determined exps legal in cats but can't per bit separate
 */
static int32 rhs_cat_separable(struct expr_t *rhsx)
{
 struct expr_t *catndp;
 struct net_t *np;

//AIV FIXME - 09/20/07 - rhs cat are not separable
 return(FALSE);

 if (rhsx->optyp != LCB) return(FALSE);
 /* if only one element in rhs concat - no optimize */
 if (rhsx->ru.x->ru.x == NULL) return(FALSE);

 for (catndp = rhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
  {
   switch (catndp->lu.x->optyp) {
    case ID: case GLBREF:
     np = catndp->lu.x->lu.sy->el.enp;
     if (!np->vec_scalared) return(FALSE);
     break;
    case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
     np = catndp->lu.x->lu.x->lu.sy->el.enp;
     if (!np->vec_scalared) return(FALSE);
     break; 
    case LSB:
     /* SJM 12/17/02 - old vectored keyword also prevents pb separation */ 
     np = catndp->lu.x->lu.x->lu.sy->el.enp;
     if (np->n_isarr || !np->vec_scalared)
      return(FALSE);
     /* SJM 03/03/07 - bit select inside concat must be constant bsel */ 
     if (!__is_const_expr(catndp->lu.x->ru.x)) return(FALSE);
     break;
    case NUMBER: 
     break;
    default: return(FALSE);
   }
  }
 return(TRUE);
}

/*
 * return T if rhs mod pin separable (can be cat or not)
 */
static int32 rhs_modpin_separable(struct expr_t *rhsx)
{
 struct expr_t *catndp;

 /* 1 bit ports never separable */
 switch (rhsx->optyp) {
  case ID: case GLBREF:
   /* evan regs always separable */
   break;
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   break; 
  case LSB:
   /* bsel not separable if array select */
   if (rhsx->lu.x->lu.sy->el.enp->n_isarr) return(FALSE);
   break;
  case NUMBER: 
   break;
  case LCB:  
   for (catndp = rhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     if (!rhs_modpin_separable(catndp->lu.x)) return(FALSE);
    }
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * decompose expr into per bit expr record 
 */
extern struct pbexpr_t *__bld_pb_expr_map(struct expr_t *xp, int32 xwid)
{
 int32 bi, bi2;
 int32 nels, xi, xofs, biti, bitj, wi, wlen;
 struct expr_t *catndp;
 word32 av, bv;
 struct expr_t **xtab, *cur_xp, *idndp;
 struct pbexpr_t *pbexpr, *pbxp;
 struct net_t *np;

 /* make sure both rhs and lhs in low to high order tables */
 /* needed because for concat, first in list is high order part */
 if (xp->optyp == LCB)
  {
   nels = __cnt_cat_size(xp);
   xtab = (struct expr_t **) __my_malloc(nels*sizeof(struct expr_t *));
   xi = nels - 1;
   /* fill expr tab in reverse order */
   catndp = xp->ru.x;
   for (; catndp != NULL; catndp = catndp->ru.x, xi--)
    { xtab[xi] = catndp->lu.x; }
  }
 else
  {
   xtab = (struct expr_t **) __my_malloc(sizeof(struct expr_t *));
   xtab[0] = xp;
   nels = 1;
  }

 /* size determined by lhs expr */
 pbexpr = (struct pbexpr_t *) __my_malloc(xwid*sizeof(struct pbexpr_t));
 for (bi = 0; bi < xwid; bi++) init_pbexpr_el(&(pbexpr[bi]));
 
 /* first fill lhs, then another loop to fill rhs matching */
 /* process one lhs expr element every time through */
 for (xofs = 0, xi = 0; xi < nels; xi++)
  {
   cur_xp = xtab[xi];
   pbxp = &(pbexpr[xofs]);
   /* fill lhs */
   switch (cur_xp->optyp) {
    case GLBREF: case ID:
     idndp = cur_xp; 
     np = idndp->lu.sy->el.enp;
     /* scalar */
     /* lhs bi is offset in object, -1 is entire object such as out of rng */
     if (!np->n_isavec)
      {
       pbxp = &(pbexpr[xofs]);
       pbxp->xp = idndp;
       pbxp->bi = -1;
       /* SJM 05/25/05 - need gt-eq since must stop at xwid not 1 past */
       if (++xofs >= xwid) goto done;
       break;
      }
     /* vector */
     for (bi2 = 0; bi2 < np->nwid; bi2++) 
      {
       pbxp = &(pbexpr[xofs]);
       pbxp->xp = idndp;
       /* this is offset in expr */
       pbxp->bi = bi2;
       if (++xofs >= xwid) goto done;
      }        
     break;
    case LSB:
     idndp = cur_xp->lu.x; 
     np = idndp->lu.sy->el.enp;
     pbxp->xp = cur_xp;
     /* DBG remove */
     if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* SJM 09/03/02 - IS number legal since scalar decl assigns allow it */  
     if (cur_xp->ru.x->optyp == ISNUMBER) biti = -2;
     else biti = __get_itp_const_bselndx(cur_xp);
     /* LOOKATME - think out of rng for const index not possible */ 
     if (biti == -1) pbxp->ndx_outofrng = TRUE;
     /* offset is offset in ID/XMR object */
     pbxp->bi = biti; 
     if (++xofs >= xwid) goto done;
     break;
    case PARTSEL:
     idndp = cur_xp->lu.x; 
     np = idndp->lu.sy->el.enp;
     /* know part select never IS */
     biti = __contab[cur_xp->ru.x->lu.x->ru.xvi];
     bitj = __contab[cur_xp->ru.x->ru.x->ru.xvi];
     for (bi2 = bitj; bi2 <= biti; bi2++)
      {
       pbxp = &(pbexpr[xofs]);
       pbxp->xp = idndp;
       /* this is offset in expr */
       pbxp->bi = bi2;
       /* this is offset from low end of concat element */
       if (++xofs >= xwid) goto done;
      } 
     break;
    case NUMBER:
     /* LOOKATME - could include ISNUMBER here if always has inst context */
     for (bi = 0; bi < cur_xp->szu.xclen; bi++)
      {
       pbxp = &(pbexpr[xofs]);
       pbxp->xp = cur_xp; 
       pbxp->rhs_const = TRUE;
       /* this is offset in expr */
       pbxp->bi = -1;
       wlen = wlen_(cur_xp->szu.xclen);
       wi = get_wofs_(bi);
       bi2 = get_bofs_(bi);
       av = (__contab[cur_xp->ru.xvi + wi] >> bi) & 1;
       bv = (__contab[cur_xp->ru.xvi + wlen + wi] >> bi) & 1;
       pbxp->aval = av;
       pbxp->bval = bv;
       /* SJM 05/25/05 - if out of lhs - remaining rhs unused so ignore */
       if (++xofs >= xwid) goto done; 
      } 
     break;
    default: __case_terr(__FILE__, __LINE__);
   } 
  }
 /* if still more lhs elements - rhs too narrow - this is bit by bit */
 for (; xofs < xwid; xofs++)
  {
   pbxp = &(pbexpr[xofs]);
   /* for extra lhs, need z assign if stren else 0 assign */
   pbxp->no_rhs_expr = TRUE;
   /* LOOKATME - just leaving rhs fields empty for now */
  }

done:
 if (xtab != NULL) __my_free(xtab, nels*sizeof(struct expr_t *));
 return(pbexpr);
} 

/*
 * initialize decomposed into per bit expr 1 bit table entry 
 */
static void init_pbexpr_el(struct pbexpr_t *pbxp)
{
 pbxp->ndx_outofrng = FALSE;
 pbxp->rhs_const = FALSE;
 pbxp->no_rhs_expr = FALSE;
 pbxp->xp = NULL;
 pbxp->bi = -1;
 /* initialize to x */
 pbxp->aval = 1;
 pbxp->bval = 1;
}

/*
 * fill separated per bit assign expr pair table
 */
static struct expr_t *bld_1sep_pbit_expr(struct pbexpr_t *pbxp,
 int32 is_stren)
{
 struct expr_t *xp;

 /* some special cases */
 if (pbxp->ndx_outofrng)
  {
   xp = __bld_rng_numxpr(1, 1, 1);
   xp->ibase = BHEX;
   return(xp); 
  }
 if (pbxp->no_rhs_expr)
  {
   if (is_stren)
    {
     xp = __bld_rng_numxpr(0, 0, 1);
     xp->ibase = BDEC;
    }
   else
    {
     /* SJM 06/27/05 - rhs widening - always widen with 0's */
     xp = __bld_rng_numxpr(0, 0, 1);
     xp->ibase = BHEX;
    }
   return(xp); 
  }

 /* lhs bsel or ID/XMR scalar - copy the expr  */ 
 if (pbxp->xp->optyp == LSB ||
  ((pbxp->xp->optyp == ID || pbxp->xp->optyp == GLBREF)
  && !pbxp->xp->lu.sy->el.enp->n_isavec))
  { xp = __copy_expr(pbxp->xp); }
 /* rhs number - can never be IS number */
 else if (pbxp->xp->optyp == NUMBER)
  {
   xp = __bld_rng_numxpr(pbxp->aval, pbxp->bval, 1);
   xp->ibase = BDEC;
  }
 /* ID/XMR vector or psel, build bsel expr */
 else xp = cnvt_to_bsel_expr(pbxp->xp, pbxp->bi);
 return(xp);
}

/*
 * convert id or psel to constant bsel
 * passed index must be normalized to h:0 form
 *
 * LOOKATME - for bsel just copying expression - ignoring various IS
 * and out of range conditions - could get rid of flags
 */
static struct expr_t *cnvt_to_bsel_expr(struct expr_t *xp, int32 i1)
{
 int32 ri1, ri2;
 struct expr_t *new_xp, *new_xp2, *idndp, *selxp;
 struct net_t *np;

 if (xp->optyp == PARTSEL || xp->optyp == PARTSEL_NDX_PLUS || 
  xp->optyp == PARTSEL_NDX_MINUS)
  {
   idndp = xp->lu.x; 
  }
 else idndp = xp;
 new_xp = __copy_expr(idndp);
 np = idndp->lu.sy->el.enp;

 /* root expr of bit select */
 new_xp2 = __alloc_newxnd();
 new_xp2->optyp = LSB;
 new_xp2->szu.xclen = 1;
 new_xp2->lu.x = new_xp;
 selxp = __bld_rng_numxpr((word32) i1, 0L, WBITS);
 selxp->ibase = BDEC;
 
 __getwir_range(np, &ri1, &ri2); 
 if (ri2 != 0 || ri1 < ri2) selxp->ind_noth0 = TRUE;
 new_xp2->ru.x = selxp;
 return(new_xp2);
}

/*
 * compute number of elements in concat (passed LSB expr node)
 */
extern int32 __cnt_cat_size(struct expr_t *xp)
{
 int32 nels;
 struct expr_t *catndp;

 for (nels = 0, catndp = xp->ru.x; catndp != NULL; catndp = catndp->ru.x)
  nels++;
 return(nels);
}

/*
 * ROUTINES TO BUILD SYMMETRIC NET PIN LIST
 */

/*
 * build the net pin list and gate state and set port expr. storarge ptrs.
 *
 * this will automatically include xmr's
 * net ranges must have been changed from NX_CT
 * also short circuits expression node id's to point to storage
 *
 * know will not see def or spec params since frozed before here
 * and different code for special param np lists disjoint
 */
static void bld_nplist(void)
{
 int32 pi, pbi, cai;
 int32 ii, gi, ptyp, pnum;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct mod_t *mdp, *imdp;
 struct gate_t *gp;
 struct conta_t *cap, *pb_cap;
 struct expr_t *xp, *pb_xp;
 struct tfrec_t *tfrp; 
 struct tfarg_t *tfap;
 struct mod_pin_t *pb_mpp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* first process all instances in module */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     __cur_npii = ii;
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((pnum = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < pnum; pi++)
      {
       mpp = &(imdp->mpins[pi]);
       xp = ip->ipins[pi];
       ptyp = mpp->mptyp;

       __cur_npnum = pi;
       __cur_pbi = -1;
       /* inst. input port rhs is driver that propagates down into module */
       if (ptyp == IO_IN)
        { 
         /* SJM 09/18/02 - scalarize if separable concat hconn */
         if (mpp->has_scalar_mpps && rhs_cat_separable(xp))
          {
           /* lhs width is mpp width since input port down assign */
           for (pbi = 0; pbi < mpp->mpwide; pbi++)
            {
             pb_xp = ip->pb_ipins_tab[pi][pbi];
             __cur_pbi = pbi;
             bld_rhsexpr_npins(pb_xp, NP_PB_ICONN);
            }
          }
         else bld_rhsexpr_npins(xp, NP_ICONN);
        }

       /* inst output port lhs is load propagated up from down module */
       /* whether in load or driver list determines interpretation */
       else if (ptyp == IO_OUT)
        {
         if (mpp->has_scalar_mpps)
          {
           for (pbi = 0; pbi < mpp->mpwide; pbi++)
            {
             pb_xp = ip->pb_ipins_tab[pi][pbi];
             __cur_pbi = pbi;
             bld_lhsexpr_npins(pb_xp, NP_PB_ICONN);
            }
          }
         else bld_lhsexpr_npins(xp, NP_ICONN);
        }
       /* SJM 08/23/00 - for empty port IO type unknown and no npins */
       else if (ptyp == IO_UNKN) ;
       else
        {
         /* SJM - 08/25/00 - now allowing concat inouts */ 
         /* FIXME - SJM - 08/27/00 - still but when concat on both sides */
         if (xp->optyp == LCB && mpp->mpref->optyp == LCB)  
          {
           __gferr(711, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
            "instance %s of type %s inout port %s (pos. %d) concatenate on both sides unsupported",
            ip->isym->synam, ip->imsym->synam, __to_mpnam(__xs, mpp->mpsnam),
            pi + 1);
          }
         else bld_lhsexpr_npins(xp, NP_BIDICONN);
	}
      }
    }

   /* next gates including udps */
   /* need for rhs select for lhs concat never possible for gates */
   __cur_pbi = -1;
   __cur_lhscati1 = __cur_lhscati2 = -1;
   for (gi = 0; gi < mdp->mgnum; gi++)
    {
     gp = &(mdp->mgates[gi]);
     __cur_npgp = gp;
     switch ((byte) gp->g_class) {
      case GC_PULL:
       /* one gate all drivers can have multiple pins */
       for (pi = 0; pi < (int32) gp->gpnum; pi++)
        {
         xp = gp->gpins[pi];
         __cur_npnum = pi;
         bld_lhsexpr_npins(xp, NP_PULL);
        }
       continue;
      /* trans in separate switch channels, drvs needed here for building */
      /* and to store tran graph edge, but removed from ndrvs */ 
      case GC_TRAN: 
       /* SJM 04/26/01 - if both terminals same, no effect - omit from nl */ 
       if (gp->g_gone) continue;

       /* build for directional tran to first lhs port */
       /* first driver for forward to port 0 lhs tran */
bld_tran_ports:
       __cur_npnum = 0;
       xp = gp->gpins[0];
       if (xp->optyp != OPEMPTY) bld_lhsexpr_npins(xp, NP_TRAN);
       /* then driver for backwards port 1 lhs tran */
       __cur_npnum = 1;
       xp = gp->gpins[1];
       if (xp->optyp != OPEMPTY) bld_lhsexpr_npins(xp, NP_TRAN);
       continue;
      case GC_TRANIF:
       /* SJM 04/26/01 - if both terminals same, no effect - omit from nl */ 
       if (gp->g_gone) continue;

       /* build rhs load for 3rd port enable input */
       /* 3rd input port is only a load - never assigned to */
       __cur_npnum = 2;
       bld_rhsexpr_npins(gp->gpins[2], NP_TRANIF);
       goto bld_tran_ports;
      default:
       /* if output unc. (OPEMPTY), chges are not seen (do not propagate) */
       if (gp->gpins[0]->optyp == OPEMPTY) continue;
       __cur_npnum = 0;
       bld_lhsexpr_npins(gp->gpins[0], NP_GATE);
       /* notice pnum is only input pins */
       for (pi = 1; pi < (int32) gp->gpnum; pi++)
        {
         xp = gp->gpins[pi];
         __cur_npnum = pi;
         bld_rhsexpr_npins(xp, NP_GATE);
        }
     }
    }
   __cur_npnum = 0;
   for (cap = &(mdp->mcas[0]), cai = 0; cai < mdp->mcanum; cai++, cap++)
    {
     if (cap->ca_pb_sim)
      { 
       /* for rhs cat without 4v delay, simulator as per bit */ 
       for (pbi = 0; pbi < cap->lhsx->szu.xclen; pbi++)
        {
         pb_cap = &(cap->pbcau.pbcaps[pbi]);
        /* notice for PB cap still need actual cap - will index during sim */
         __cur_npcap = cap;
         __cur_pbi = pbi;
         bld_lhsexpr_npins(pb_cap->lhsx, NP_CONTA);
         bld_rhsexpr_npins(pb_cap->rhsx, NP_CONTA);
        }
      }
     else
      {
       __cur_npcap = cap;
       __cur_pbi = -1;
       /* for conta expression determines width */
       bld_lhsexpr_npins(cap->lhsx, NP_CONTA);
       bld_rhsexpr_npins(cap->rhsx, NP_CONTA);
      }
    }

   /* SJM - 04/30/99 - no longer removing ports but still no npps */
   /* for top level modules that have ports still - no npps */
   if (mdp->minstnum == 0) goto nxt_mod;

   /* module ports */
   pnum = mdp->mpnum;
   for (pi = 0; pi < pnum; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     xp = mpp->mpref;
     ptyp = mpp->mptyp;
     __cur_npmdp = mdp;
     __cur_npnum = pi;
     __cur_pbi = -1;

     /* module inputs are lvalues (opposite cells) */
     if (ptyp == IO_IN)
      {
       /* SJM 09/18/02 - scalarize if any concat hconn */
       /* LOOKATME ??? - what if some high conns not pb seperable concats? */ 
       /* since only for inputs only drivers here, think for non sep */
       /* does not hurt to use per bit drivers */
       if (mpp->has_scalar_mpps)
        {
         /* lhs width is mpp width since input port down assign */
         for (pbi = 0; pbi < mpp->mpwide; pbi++)
          {
           pb_mpp = &(mpp->pbmpps[pbi]);
           pb_xp = pb_mpp->mpref;
           __cur_pbi = pbi;
           bld_lhsexpr_npins(pb_xp, NP_PB_MDPRT);
          }
        }
       else bld_lhsexpr_npins(xp, NP_MDPRT);
      }
     else if (ptyp == IO_OUT)
      {
       if (mpp->has_scalar_mpps)
        {
         for (pbi = 0; pbi < mpp->mpwide; pbi++)
          {
           pb_mpp = &(mpp->pbmpps[pbi]);
           pb_xp = pb_mpp->mpref;
           __cur_pbi = pbi;
           bld_rhsexpr_npins(pb_xp, NP_PB_MDPRT);
          }
        }
       else bld_rhsexpr_npins(xp, NP_MDPRT);
      }
     /* inouts have no loads or drivers since tran channel eval instead */
     /* but for PLI nlds and ndrvs set but never used for simulation */
     else if (ptyp == IO_BID)
      {
       /* SJM - 08/25/00 - now allowing concat connected inout port defs */ 
       bld_lhsexpr_npins(xp, NP_BIDMDPRT);
      }
     /* SJM 08/23/00 - for empty port IO type unknown and no npins */
     else if (ptyp == IO_UNKN) ;
     else __case_terr(__FILE__, __LINE__);
    }
nxt_mod:
   __pop_wrkitstk();
  }

 /* keeping one module wide tf rec list */
 __cur_pbi = -1;
 for (tfrp = __tfrec_hdr; tfrp != NULL; tfrp = tfrp->tfrnxt)
  { 
   /* AIV 03/19/07 - the compiler currently needs the right mod since */
   /* it loads the npp (passed to an asl wrapper call) */
   __push_wrkitstk(tfrp->tf_inmdp, 0);
   for (pi = 1; pi < tfrp->tfanump1; pi++)
    {
     tfap = &(tfrp->tfargs[pi]);
     xp = tfap->arg.axp; 
     if (!xp->tf_isrw) continue;

     /* DBG remove --- */
     if (tfap->anp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     if (tfap->anp->ntyp >= NONWIRE_ST) continue; 
     __cur_nptfrp = tfrp; 
     __cur_npnum = pi;
     bld_lhsexpr_npins(xp, NP_TFRWARG);
    } 
   __pop_wrkitstk();
  } 
}

/*
 * build net_pin elements for wire only (lhs) output or inout port
 * or gate or conta output port
 * know bit/part select not declared with vectored attribute or prev. error
 * know concatenates must be exactly 1 level 
 *
 * this also sets has delay bit in top level noded if any element has delay
 */
static void bld_lhsexpr_npins(struct expr_t *xp, int32 npctyp)
{
 __cur_lhscati1 = __cur_lhscati2 = -1;
 __lhsxpr_has_ndel = FALSE;
 bld2_lhsexpr_npins(xp, npctyp);
 if (__lhsxpr_has_ndel) xp->lhsx_ndel = TRUE;
}

/*
 * notice lhs xmr's automatically work on lhs no cross module propagation
 * either assign to wires where gref info used to find storage and propagate
 * in target inst. or eval. drivers using target inst. where needed
 * propagation after assignment in cur. itp of destination is wire by wire
 */
static void bld2_lhsexpr_npins(struct expr_t *xp, int32 npctyp)
{
 int32 biti, bitj;
 struct expr_t *idndp;
 struct net_t *np;
 struct expr_t *catxp;
 struct gref_t *grp;

 grp = NULL;
 switch (xp->optyp) {
  /* this can happen for unc. */
  case GLBREF:
   idndp = xp;
   np = xp->lu.sy->el.enp;
   grp = idndp->ru.grp;
   if (np->nrngrep == NX_DWIR) __lhsxpr_has_ndel = TRUE;
   __conn_npin(np, -1, -1, TRUE, npctyp, grp, NPCHG_NONE, (char *) NULL);
   break;
  case ID:
   np = xp->lu.sy->el.enp;
   if (np->nrngrep == NX_DWIR) __lhsxpr_has_ndel = TRUE;
   /* by here anything that must be scalared has been or error */
   __conn_npin(np, -1, -1, TRUE, npctyp, grp, NPCHG_NONE, (char *) NULL);
   break;
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM: case OPEMPTY:
   return;
  case LSB:
   idndp = xp->lu.x;
   np = idndp->lu.sy->el.enp;
   if (np->nrngrep == NX_DWIR) __lhsxpr_has_ndel = TRUE;
   /* know will be constant or will not be on decl. lhs */
   /* DBG remove --- */ 
   if (!np->vec_scalared) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (idndp->optyp == GLBREF) grp = idndp->ru.grp;
   if (xp->ru.x->optyp == ISNUMBER)
    {
     /* SJM 10/12/04 - IS const must be contab ndx since contab realloced */
     __isform_bi_xvi = xp->ru.x->ru.xvi;
     __conn_npin(np, -2, 0, TRUE, npctyp, grp, NPCHG_NONE, (char *) NULL);
    }
   else
    {
     biti = (int32 ) __contab[xp->ru.x->ru.xvi];
     __conn_npin(np, biti, biti, TRUE, npctyp, grp, NPCHG_NONE,
      (char *) NULL);
    }
   break;
  case PARTSEL:
   idndp = xp->lu.x;
   np = idndp->lu.sy->el.enp;

   /* DBG remove --- */ 
   if (!np->vec_scalared) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (idndp->optyp == GLBREF) grp = idndp->ru.grp;

   /* for path dest. this is on */
   if (np->nrngrep == NX_DWIR) __lhsxpr_has_ndel = TRUE;
   /* array stored from 0 to size even though bits go high to 0 */
   /* never IS form */
   biti = (int32) (__contab[xp->ru.x->lu.x->ru.xvi]);
   bitj = (int32) (__contab[xp->ru.x->ru.x->ru.xvi]);

   __conn_npin(np, biti, bitj, TRUE, npctyp, grp, NPCHG_NONE, (char *) NULL);
   break;
  case LCB:
   for (catxp = xp->ru.x; catxp != NULL; catxp = catxp->ru.x)
    {
     /* catxp length is distance from high bit to rhs end (0) */
     __cur_lhscati1 = catxp->szu.xclen - 1;
     __cur_lhscati2 = __cur_lhscati1 - catxp->lu.x->szu.xclen + 1;
     bld2_lhsexpr_npins(catxp->lu.x, npctyp);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * build net_pin elements for rhs reg or wire
 * these are things that when wire changes (is assigned to) are traced to
 * propagate change by evaluating rhs these are in
 *
 * idea here is too build as normal, then add special itp stuff if needed
 * for any global needed because when wire changes in target (eval itp),
 * must propagate cross module to place used
 */
static void bld_rhsexpr_npins(struct expr_t *xp, int32 npctyp)
{
 int32 biti, bitj;
 struct net_t *np;
 struct expr_t *idndp, *selxp;
 struct gref_t *grp;

 grp = NULL;
 switch (xp->optyp) {
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM: return;
  case OPEMPTY:
   /* could handle `unconndrive by adding some kind of driver here ? */
   return; 
  case GLBREF:
   idndp = xp;
   np = xp->lu.sy->el.enp;
   grp = idndp->ru.grp;
   __conn_npin(np, -1, -1, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
   break;
  case ID:
   np = xp->lu.sy->el.enp;
   __conn_npin(np, -1, -1, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
   break;
  case LSB:
   idndp = xp->lu.x;
   np = idndp->lu.sy->el.enp;
   if (idndp->optyp == GLBREF) grp = idndp->ru.grp;
   selxp = xp->ru.x;
   /* for registers or arrays, never split, change must always propagate */
   /* this means no per array cell tab, if any cell changes, reevaluate */
   /* if reg (not wire) or vectored and not arr, any chg causes propagation */ 
   if (!np->vec_scalared && !np->n_isarr)
    {
     /* if this constant just does nothing */
     bld_rhsexpr_npins(selxp, npctyp);
     __conn_npin(np, -1, -1, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
    }
   else if (selxp->optyp == NUMBER)
    {
     biti = (int32) (__contab[selxp->ru.xvi]);
     __conn_npin(np, biti, biti, FALSE, npctyp, grp, NPCHG_NONE,
      (char *) NULL);
    }
   else if (selxp->optyp == ISNUMBER)
    {
     /* SJM 10/12/04 - IS const must be contab ndx since contab realloced */
     __isform_bi_xvi = selxp->ru.xvi;
     __conn_npin(np, -2, 0, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
    }
   else
    {
     /* AIV 02/01/11 - again variable wire arrays need to add all  */
     /* the flattened wire array vectors here as well */
     if (np->n_isarr && np->ntyp < NONWIRE_ST)
      {
       bld_rhsexpr_npins_var_wire_array(xp, npctyp, grp);
      }
     __conn_npin(np, -1, -1, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
     bld_rhsexpr_npins(selxp, npctyp);
    }
   break;
  case PARTSEL:
   idndp = xp->lu.x;
   np = idndp->lu.sy->el.enp;
   if (idndp->optyp == GLBREF) grp = idndp->ru.grp;
   /* for part select of reg - still need to match all bits */
   /* know here both range will be constants */
   if (!np->vec_scalared)
    __conn_npin(np, -1, -1, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
   else
    {
     /* array stored from 0 to size even though bits go high to 0 */
     selxp = xp->ru.x;
     /* never IS form */
     biti = (int32) (__contab[selxp->lu.x->ru.xvi]);
     bitj = (int32) (__contab[selxp->ru.x->ru.xvi]);
     __conn_npin(np, biti, bitj, FALSE, npctyp, grp, NPCHG_NONE,
      (char *) NULL);
    }
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   /* AIV 07/30/08 - these are known to be variable */
   idndp = xp->lu.x;
   np = idndp->lu.sy->el.enp;
   if (idndp->optyp == GLBREF) grp = idndp->ru.grp;
   /* for part select of reg - still need to match all bits */
   /* know here both range will be constants */
   if (!np->vec_scalared)
    __conn_npin(np, -1, -1, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
   else
    {
     selxp = xp->ru.x;
     __conn_npin(np, -1, -1, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
     bld_rhsexpr_npins(selxp, npctyp);
    }
   break;
  case FCALL:
   {
    struct expr_t *fax;

    /* if any args of system or user functions change, monitor triggers */
    for (fax = xp->ru.x; fax != NULL; fax = fax->ru.x)
     bld_rhsexpr_npins(fax->lu.x, npctyp);
   }
   return;
  case LCB:
   {
    struct expr_t *catxp;

    for (catxp = xp->ru.x; catxp != NULL; catxp = catxp->ru.x)
     bld_rhsexpr_npins(catxp->lu.x, npctyp);
   }
   return;
  default:
   if (xp->lu.x != NULL) bld_rhsexpr_npins(xp->lu.x, npctyp);
   if (xp->ru.x != NULL) bld_rhsexpr_npins(xp->ru.x, npctyp);
   return;
 }
}

/*
 * AIV 02/01/11 - again variable wire arrays need to add all 
 * the flattened wire array vectors here as well
 */
static void bld_rhsexpr_npins_var_wire_array(struct expr_t *xp, int32 npctyp,
 struct gref_t *grp)
{
 struct net_t *np;
 struct sy_t *syp;
 struct net_t *el_np;
 struct expr_t *idndp;
 int32 i, wirarr_el_num;

 /* get the net */
 idndp = __get_lvalue_idndp(xp);
 np = idndp->lu.sy->el.enp;

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
 /* fill the wire array element symbols */
 __fill_wire_arr_sym_wrkstab(np, __inst_mod);

 /* add each vector net value */
 for (i = 0; i <= __last_sy2; i++)
  {
   syp = __wrkstab2[i];
   el_np = syp->el.enp;
   /* DBG remove -- */
   if (syp->sytyp != SYM_N) __misc_terr(__FILE__, __LINE__);
   if (!el_np->n_isarr_vector) __misc_terr(__FILE__, __LINE__);
   /* --- */
   __conn_npin(el_np, -1, -1, FALSE, npctyp, grp, NPCHG_NONE, (char *) NULL);
  }

 /* free tmp symbol array */
 if (wirarr_el_num != 0)
  {
   __my_free(__wrkstab2, wirarr_el_num*sizeof(struct sy_t *)); 
  }
}

/*
 * scheme for various types of xmr npps
 *
 * not xmr (0)          - simple no bits set, no move to ref, no filter
 * xmr (not root)   (1) - xmrtyp, npu gref, no filter 
 * any rooted xmr   (2) - xmrtyp/1inst, npu filtidp to ref, npaux npdownitp 
 */

/*
 * routine to build 1 net pin connection per static location 
 *
 * LOOKATME - here do matching to find identical static tree upward inst_t
 * path but have static tree so maybe could traverse to not need to match?
 */
extern void __conn_npin(struct net_t *np, int32 ni1, int32 ni2, int32 islhs,
 int32 npctyp, struct gref_t *grp, int32 chgtyp, char *chgp)
{
 struct net_pin_t *npp;

 /* case: non xmr */ 
 if (grp == NULL)
  {
   npp = conn2_npin(np, ni1, ni2, islhs, npctyp);
   if (chgtyp != NPCHG_NONE) set_chgsubfld(npp, chgtyp, chgp);
   return;
  }
 /* case 2: rooted xmr */
 if (grp->is_rooted)
  conn_rtxmr_npin(np, ni1, ni2, islhs, npctyp, grp, chgtyp, chgp);
 /* case 3: non rooted xmr */ 
 else conn_xmr_npin(np, ni1, ni2, islhs, npctyp, grp, chgtyp, chgp);
}

/*
 * connect any rooted xmr net pin
 *
 * idea here is that there will be one npp for each module containing
 * reference the one driver or load (rooted xmr) drivers or is a load
 * of all instances
 *
 * for rooted:
 *  when wire changes must match npauxp npdownitp inst or not load or driver
 *  to move from target (wire that changes) to ref. one loc. is npdownitp
 */
static void conn_rtxmr_npin(struct net_t *np, int32 ni1, int32 ni2,
 int32 islhs, int32 npctyp, struct gref_t *grp, int32 chgtyp, char *chgp)
{
 int32 ii;
 struct net_pin_t *npp; 
 struct itree_t *targitp;

 targitp = grp->targu.targitp;
 /* here npp is not instance specific */ 
 for (ii = 0; ii < grp->gin_mdp->flatinum; ii++)
  {
   npp = conn2_npin(np, ni1, ni2, islhs, npctyp);
   if (chgtyp != NPCHG_NONE) set_chgsubfld(npp, chgtyp, chgp);  
   if (npp->npaux == NULL) npp->npaux = __alloc_npaux();
   /* this is place npp referenced from */
   npp->npaux->npdownitp = (struct itree_t *) grp->gin_mdp->moditps[ii];

   /* for rooted, target (place wire in) must be the one changed wire in */
   /* itree location - need to filter */
   npp->npaux->npu.filtidp = (t_midat *) targitp;

   npp->np_xmrtyp = XNP_RTXMR;
   npp->npproctyp = NP_PROC_FILT;
  }
}

/*
 * connect an xmr that is not rooted
 * for upwards or downwards relative search using normal routines
 * no filtering since one npp where all refs have different target
 */
static void conn_xmr_npin(struct net_t *np, int32 ni1, int32 ni2, int32 islhs,
 int32 npctyp, struct gref_t *grp, int32 chgtyp, char *chgp)
{
 struct net_pin_t *npp;

 npp = conn2_npin(np, ni1, ni2, islhs, npctyp);
 if (chgtyp != NPCHG_NONE) set_chgsubfld(npp, chgtyp, chgp);  
 if (npp->npaux == NULL) npp->npaux = __alloc_npaux();
 /* use gref to move from target (npp on wire/inst) to ref. */
 npp->npaux->npu.npgrp = grp;
 if (grp->upwards_rel) npp->np_xmrtyp = XNP_UPXMR;
 else npp->np_xmrtyp = XNP_DOWNXMR;
 npp->npproctyp = NP_PROC_GREF;
}

/*
 * connect a range of net bits
 * not for register output or trigger net pin list building
 * all allocation and connecting of net pins done through here
 *
 * the xmr fields must be set by caller if needed
 */
static struct net_pin_t *conn2_npin(struct net_t *np, int32 ni1, int32 ni2,
 int32 islhs, int32 npctyp)
{
 struct net_pin_t *npp;
 
 /* if load of vectored vector - always just mark change of entire wire */ 
 if (!islhs && !np->n_isarr && np->n_isavec && !np->vec_scalared)
  ni1 = ni2 = -1; 

 npp = __alloc_npin(npctyp, ni1, ni2);
 /* notice 32 bit dependent since assumes ptr and int32 both 4 bytes */
 /* also __isform_bi xvi is contab index so can just use it */
 if (ni1 == -2)
  {
   npp->npaux->nbi2.xvi = __isform_bi_xvi;
   /* AIV 03/06/08 - add IS form to tree so it can be added to idp */
   if (__compiled_sim)
    {
     __add_isnum_to_tree((void *) npp, __isform_bi_xvi, WBITS);
    }
  }

 /* link on front */
 if (islhs)
  {
   if (__cur_lhscati1 != -1)
    {
     if (npp->npaux == NULL) npp->npaux = __alloc_npaux();
     npp->npaux->lcbi1 = __cur_lhscati1;
     npp->npaux->lcbi2 = __cur_lhscati2;
    }
   npp->npnxt = np->ndrvs;
   np->ndrvs = npp;
  }
 else
  {
   /* never insert mipd nchg using this routine */
   /* DBG remove -- */
   if (npp->npntyp == NP_MIPD_NCHG) __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* SJM 07/10/01 - MIPD load must always be first on list */
   /* SJM 07/24/01 - logic was wrong - now if front mipd nchg insert after */
   if (np->nlds != NULL && np->nlds->npntyp == NP_MIPD_NCHG)
    { npp->npnxt = np->nlds->npnxt; np->nlds->npnxt = npp; }
   else { npp->npnxt = np->nlds; np->nlds = npp; }
  }
//SJM 10-26-12 - PUTMEBACK
 /* DBG remove --- */
 if (__debug_flg)
  {
   struct npaux_t *npauxp;

   __dbg_msg(".. mod %s adding net %s pin type %d to front",
    __inst_mod->msym->synam, np->nsym->synam, npp->npntyp);
   if ((npauxp = npp->npaux) != NULL && npauxp->lcbi1 != -1)
    __dbg_msg("([%d:%d])\n", npauxp->lcbi1, npauxp->lcbi2);
   else __dbg_msg("\n");
  }
 /* --- */
 /* just put on front */
 return(npp);
}

/*
 * allocate a net pin element 
 * net pin form converted to table for all net pins in current module
 *
 * notice [i1:i2] are corrected to h:0 form by here
 * also notice some globals such as obnum (port) must be set before calling
 */
extern struct net_pin_t *__alloc_npin(int32 nptyp, int32 i1, int32 i2)
{
 struct net_pin_t *npp;
 struct primtab_t *ptp;

 npp = (struct net_pin_t *) __my_malloc(sizeof(struct net_pin_t));
 npp->npntyp = (word32) nptyp;
 npp->npproctyp = NP_PROC_INMOD;
 /* value explicitly set if needed */
 npp->chgsubtyp = 0; 
 
 npp->np_xmrtyp = XNP_LOC;
 npp->pullval = 0;
 /* assume more common load */
 npp->obnum = __cur_npnum;
 npp->pbi = -1;
 npp->npaux = NULL;
 npp->npp_idnum = -1;
 npp->is_loaded = FALSE;
 npp->is_printed = FALSE;
 npp->npp_fgp = NULL;
 npp->scalar_mdprt_ofs = 0;
 switch ((byte) nptyp) {
  case NP_ICONN: case NP_BIDICONN:
   npp->elnpp.eii = __cur_npii;
   break;
  case NP_PB_ICONN:
   npp->elnpp.eii = __cur_npii;
   npp->pbi = __cur_pbi;
   break;
  case NP_GATE: case NP_TRAN: case NP_TRANIF:
   npp->elnpp.egp = __cur_npgp;
   break;
  case NP_CONTA:
   npp->elnpp.ecap = __cur_npcap;
   npp->pbi = __cur_pbi;
   break;
  case NP_MDPRT: case NP_BIDMDPRT:
   npp->elnpp.emdp = __cur_npmdp;
   break;
  case NP_PB_MDPRT:
   npp->elnpp.emdp = __cur_npmdp;
   npp->pbi = __cur_pbi;
   break;
  /* set later */
  case NP_TCHG: 
   npp->elnpp.etchgp = NULL;
   break;
  case NP_PULL:
   npp->elnpp.egp = __cur_npgp;
   ptp = __cur_npgp->gmsym->el.eprimp; 
   npp->pullval = (ptp->gateid == G_PULLUP) ? 1 : 0; 
   break;
  case NP_TFRWARG:
   npp->elnpp.etfrp = __cur_nptfrp; 
   npp->obnum = __cur_npnum;
   break;
  case NP_VPIPUTV:
   npp->elnpp.enp = __cur_npnp;
   /* caller sets to index number of this driver */
   npp->obnum = 0;
   break;
  case NP_MIPD_NCHG: 
   npp->elnpp.enp = __cur_npnp;
   npp->obnum = 0;
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 npp->npnxt = NULL;

 if (i1 != -1)
  {
   npp->npaux = __alloc_npaux();
   npp->npaux->nbi1 = i1;
   npp->npaux->nbi2.i = i2;
  }
 return(npp);
}

/*
 * allocate and initialize the aux. net pin record
 */
extern struct npaux_t *__alloc_npaux(void)
{
 struct npaux_t *npauxp;

 npauxp = (struct npaux_t *) __my_malloc(sizeof(struct npaux_t));
 npauxp->idp_ofs = 0;
 npauxp->mdp = NULL;
 npauxp->nbi1 = -1;
 npauxp->nbi2.i = -1;
 npauxp->npu.npgrp = NULL;
 npauxp->npdownitp = NULL;
 npauxp->lcbi1 = npauxp->lcbi2 = -1;
 return(npauxp);
}

/*
 * set change subtype fields for a npp
 */
static void set_chgsubfld(struct net_pin_t *npp, int32 chgtyp, char *chgp) 
{
 npp->chgsubtyp = chgtyp;
 switch (chgtyp) {
  case NPCHG_TCSTART: npp->elnpp.etchgp = (struct tchg_t *) chgp; break;
  case NPCHG_TCCHK: npp->elnpp.echktchgp = (struct chktchg_t *) chgp; break;
  case NPCHG_PTHSRC: npp->elnpp.etchgp = (struct tchg_t *) chgp; break;
  default: __case_terr(__FILE__, __LINE__); 
 }
}

/*
 * routine to fixup npp filtidp fields and dce match itp fields 
 *
 * convert from itp to idp now that idp's are known
 *
 * this routine is needed because the filt itp field for rooted xmr npps
 * must be used (compared) during v prp because fan-in must be known
 * and filtering of the itree location of a rooted can be the fi target
 *
 * works because up to here comparing itps to itps - after here compare
 * filt idp to idp
 */
static void fixup_idps_where_used_itp(void)
{
 int32 ni;
 struct mod_t *mdp, *imdp;
 struct net_t *np;
 struct net_pin_t *npp;
 struct itree_t *itp;
 struct dcevnt_t *dcep;
 struct dce_idp_info_t *didp;
 t_midat *idp;
 size_t offset;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* do not need separate traversal of task since task vars also in mnets */
   /* if tot var num used */
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
    {
     for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
      {
       if (npp->np_xmrtyp != XNP_RTXMR) continue;
       if (npp->npproctyp != NP_PROC_FILT) continue;
   
       itp = (struct itree_t *) npp->npaux->npu.filtidp;
       idp = itp->it_idp;
       npp->npaux->npu.filtidp = idp;

       imdp = (struct mod_t *) idp[MD_MDP];
       /* AIV 02/26/08 - need to save the module and the offset to */
       /* link the new mod_idata area for the compiler */
       npp->npaux->mdp = imdp;
       offset = ((word32) idp - (word32) imdp->mod_idata)/WRDBYTES;
       npp->npaux->idp_ofs = offset;
      }
     for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
      {
       if (npp->np_xmrtyp != XNP_RTXMR) continue;
       if (npp->npproctyp != NP_PROC_FILT) continue;
   
       itp = (struct itree_t *) npp->npaux->npu.filtidp;
       idp = itp->it_idp;
       npp->npaux->npu.filtidp = idp;

       imdp = (struct mod_t *) idp[MD_MDP];
       npp->npaux->mdp = imdp;
       offset = ((word32) idp - (word32) imdp->mod_idata)/WRDBYTES;
       npp->npaux->idp_ofs = offset;
      }
     /* if compiled sim need to save the offsets and mdp for later linking */
     if (__compiled_sim)
      {
       for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
        {
         if (dcep->nd_chg_to_idp)
          {
           didp = (struct dce_idp_info_t *) 
            __my_malloc(sizeof(struct dce_idp_info_t));
           dcep->didp = didp;
           itp = (struct itree_t *) dcep->dce_matchu.itp;
           idp = itp->it_idp;
           dcep->dce_matchu.idp = idp;
           imdp = (struct mod_t *) idp[MD_MDP];
           didp->match_mdp = imdp;
           offset = ((word32) idp - (word32) imdp->mod_idata)/WRDBYTES;
           didp->match_idp_ofs = offset;
  
           itp = (struct itree_t *) dcep->dce_refu.itp;
           idp = itp->it_idp;
           dcep->dce_refu.idp = idp;
           imdp = (struct mod_t *) idp[MD_MDP];
           didp->ref_mdp = imdp;
           offset = ((word32) idp - (word32) imdp->mod_idata)/WRDBYTES;
           didp->ref_idp_ofs = offset;
          }
        }
      }
     else
      {
       for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
        {
         if (dcep->nd_chg_to_idp)
          {
           itp = (struct itree_t *) dcep->dce_matchu.itp;
           dcep->dce_matchu.idp = itp->it_idp;
           itp = (struct itree_t *) dcep->dce_refu.itp;
           dcep->dce_refu.idp = itp->it_idp;
          }
        }
      }
    }
  }
}

/*
 * ROUTINES TO BUILD DEFPARAM AND SPECPARAM CONTAINING EXPR LIST
 */

/*
 * add delay list parameters to param parm nplst for a net
 */
static void add_netdel_pnp(struct net_t *np, struct paramlst_t *pdels)
{
 int32 sav_fnam_ind, sav_slin_cnt;
 struct paramlst_t *pmp;
 struct expr_t *dxp;
 struct parmnet_pin_t tmpl_pnp;

 init_pnp(&tmpl_pnp);
 tmpl_pnp.pnptyp = PNP_NETDEL;
 /* object delay for */ 
 tmpl_pnp.elpnp.enp = np;
 /* not copied but moved from previous pdels whose field is overwritten */
 tmpl_pnp.pnplp = pdels;

 sav_fnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) np->nsym->syfnam_ind;
 __slin_cnt = np->nsym->sylin_cnt;

 /* only free first one */
 __nd_parmpnp_free = TRUE;
 for (pmp = pdels; pmp != NULL; pmp = pmp->pmlnxt)
  { dxp = pmp->plxndp; addto_parmnplst(dxp, &tmpl_pnp); }

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * initialize a param net pin elemnt 
 */
static void init_pnp(struct parmnet_pin_t *pnp)
{
 pnp->pnp_free = FALSE;
 pnp->elpnp.enp = NULL;
 pnp->pnplp = NULL;
 pnp->pnpnxt = NULL;
}

/*
 * build a param nplst element from a param in an expression
 */
static void addto_parmnplst(struct expr_t *xp,
 struct parmnet_pin_t *tmplate_pnp)
{
 struct net_t *np;
 struct parmnet_pin_t *pnp;
 struct expr_t *xp2;

 if (__isleaf(xp))
  {
   if (xp->optyp == GLBREF)
    {
     np = xp->lu.sy->el.enp;
      __sgfinform(457, 
       "hierarchical parameter %s used in delay expression can not be annotated to",
       __msgexpr_tostr(__xs, xp));
     return;
    }
   if (xp->optyp != ID || xp->lu.sy->sytyp != SYM_N) return;

   np = xp->lu.sy->el.enp;
   if (!np->n_isaparam) return;

   pnp = (struct parmnet_pin_t *) __my_malloc(sizeof(struct parmnet_pin_t));   
   *pnp = *tmplate_pnp; 
   if (__nd_parmpnp_free)
    { pnp->pnp_free = TRUE; __nd_parmpnp_free = FALSE; }
   else pnp->pnp_free = FALSE;
   /* reverse order, put on front */
   if (np->nlds == NULL) np->nlds = (struct net_pin_t *) pnp;
   else
    {
     pnp->pnpnxt = (struct parmnet_pin_t *) np->nlds; 
     np->nlds = (struct net_pin_t *) pnp;
    }
   return;
  }

 for (xp2 = xp->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx) 
  {
   addto_parmnplst(xp2, tmplate_pnp);
  }

 if (xp->lu.x != NULL) addto_parmnplst(xp->lu.x, tmplate_pnp);
 if (xp->ru.x != NULL) addto_parmnplst(xp->ru.x, tmplate_pnp);
}

/*
 * add delay list parameters to param parm nplst for a gate
 */
static void add_gatedel_pnp(struct gate_t *gp, struct paramlst_t *pdels)
{
 int32 sav_fnam_ind, sav_slin_cnt;
 struct paramlst_t *pmp;
 struct expr_t *dxp;
 struct parmnet_pin_t tmpl_pnp;

 init_pnp(&tmpl_pnp);
 tmpl_pnp.pnptyp = PNP_GATEDEL;
 /* object delay for */ 
 tmpl_pnp.elpnp.egp = gp;
 /* not copied but moved from previous pdels whose field is overwritten */
 tmpl_pnp.pnplp = pdels;

 sav_fnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) gp->gsym->syfnam_ind;
 __slin_cnt = gp->gsym->sylin_cnt;

 /* only free first use - all other uses point to same parm npp */
 __nd_parmpnp_free = TRUE;
 for (pmp = pdels; pmp != NULL; pmp = pmp->pmlnxt)
  { dxp = pmp->plxndp; addto_parmnplst(dxp, &tmpl_pnp); }

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * add delay list parameters to param parm nplst for a conta
 */
static void add_contadel_pnp(struct conta_t *cap, struct paramlst_t *pdels)
{
 int32 sav_fnam_ind, sav_slin_cnt;
 struct paramlst_t *pmp;
 struct expr_t *dxp;
 struct parmnet_pin_t tmpl_pnp;

 init_pnp(&tmpl_pnp);
 tmpl_pnp.pnptyp = PNP_CONTADEL;
 /* object delay for */ 
 tmpl_pnp.elpnp.ecap = cap;
 /* not copied but moved from previous pdels whose field is overwritten */
 tmpl_pnp.pnplp = pdels;

 sav_fnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) cap->casym->syfnam_ind;
 __slin_cnt = cap->casym->sylin_cnt;

 /* only free first one */
 __nd_parmpnp_free = TRUE;
 for (pmp = pdels; pmp != NULL; pmp = pmp->pmlnxt)
  { dxp = pmp->plxndp; addto_parmnplst(dxp, &tmpl_pnp); }

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * add delay list parameters to param parm nplst for a procedural delay ctrl
 *
 * know will only be one delay
 */
extern void __add_dctldel_pnp(struct st_t *stp)
{
 int32 sav_fnam_ind, sav_slin_cnt;
 struct paramlst_t *pmp;
 struct delctrl_t *dctp;
 struct paramlst_t *pdels;
 struct expr_t *dxp;
 struct parmnet_pin_t tmpl_pnp;

 init_pnp(&tmpl_pnp);
 tmpl_pnp.pnptyp = PNP_PROCDCTRL;
 /* object delay for */ 
 dctp = stp->st.sdc;
 tmpl_pnp.elpnp.edctp = dctp;
 pdels = dctp->dc_du.pdels;
 /* not copied but moved from previous pdels whose field is overwritten */
 tmpl_pnp.pnplp = pdels;

 sav_fnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) stp->stfnam_ind;
 __slin_cnt = stp->stlin_cnt;

 /* only free first one */
 __nd_parmpnp_free = TRUE;
 /* DBG remove -- */
 if (pdels->pmlnxt != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 for (pmp = pdels; pmp != NULL; pmp = pmp->pmlnxt)
  { dxp = pmp->plxndp; addto_parmnplst(dxp, &tmpl_pnp); }

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * add delay list parameters to param parm nplst for a timing check
 *
 * know will only be one delay
 */
extern void __add_tchkdel_pnp(struct tchk_t *tcp, int32 is_1st)
{
 int32 sav_fnam_ind, sav_slin_cnt;
 struct paramlst_t *pmp;
 struct paramlst_t *pdels;
 struct expr_t *dxp;
 struct parmnet_pin_t tmpl_pnp;

 init_pnp(&tmpl_pnp);
 tmpl_pnp.elpnp.etcp = tcp;
 if (is_1st)
  { tmpl_pnp.pnptyp = PNP_TCHKP1; pdels = tcp->tclim_du.pdels; }
 else { tmpl_pnp.pnptyp = PNP_TCHKP2; pdels = tcp->tclim2_du.pdels; }
 /* not copied but moved from previous pdels whose field is overwritten */
 tmpl_pnp.pnplp = pdels;

 sav_fnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) tcp->tcsym->syfnam_ind;
 __slin_cnt = tcp->tcsym->sylin_cnt;

 /* only free first one */
 __nd_parmpnp_free = TRUE;
 /* DBG remove -- */
 if (pdels->pmlnxt != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 for (pmp = pdels; pmp != NULL; pmp = pmp->pmlnxt)
  { dxp = pmp->plxndp; addto_parmnplst(dxp, &tmpl_pnp); }

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * add delay list parameters to param parm nplst for a timing check
 */
extern void __add_pathdel_pnp(struct spcpth_t *pthp)
{
 int32 sav_fnam_ind, sav_slin_cnt;
 struct paramlst_t *pmp;
 struct paramlst_t *pdels;
 struct expr_t *dxp;
 struct parmnet_pin_t tmpl_pnp;

 init_pnp(&tmpl_pnp);
 tmpl_pnp.elpnp.epthp = pthp;
 tmpl_pnp.pnptyp = PNP_PATHDEL;
 pdels = pthp->pth_du.pdels;
 /* not copied but moved from previous pdels whose field is overwritten */
 tmpl_pnp.pnplp = pdels;

 sav_fnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) pthp->pthsym->syfnam_ind;
 __slin_cnt = pthp->pthsym->sylin_cnt;

 /* only free first one */
 __nd_parmpnp_free = TRUE;
 for (pmp = pdels; pmp != NULL; pmp = pmp->pmlnxt)
  { dxp = pmp->plxndp; addto_parmnplst(dxp, &tmpl_pnp); }

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * free all parm net pin in design
 *
 * after this is called information required to annotate delays from
 * params (labels) gone
 */
extern void __free_design_pnps(void)
{
 int32 ni;
 struct net_t *prmp;
 struct mod_t *mdp;
 struct task_t *tskp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   if (__inst_mod->mprmnum != 0) 
    {
     for (ni = 0, prmp = &(__inst_mod->mprms[0]); ni < __inst_mod->mprmnum;
      ni++, prmp++)
      {
       /* DBG remove -- */
       if (!prmp->n_isaparam) __misc_terr(__FILE__, __LINE__);
       /* --- */
        
       if (prmp->nlds == NULL) continue;
       free_1parm_pnps(prmp); 
      }
    }
   for (tskp = __inst_mod->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->tprmnum == 0) continue;
     prmp = &(tskp->tsk_prms[0]);
     for (ni = 0; ni < tskp->tprmnum; ni++, prmp++)
      {
       if (!prmp->n_isaparam) continue;
       if (prmp->nlds == NULL) continue;
       free_1parm_pnps(prmp); 
      }
    }
   __pop_wrkitstk();
  }
}

/*
 * free the pnp parm net list for one parameter
 *
 * called after SDF and vpi_ cbEndOfCompile call back since from then
 * on assign to parameters in delay expressions (by vpi_, SDF annotate done)
 * has no effect since delays elaborated (or frozen)
 */
static void free_1parm_pnps(struct net_t *prmp)
{
 struct parmnet_pin_t *pnp, *pnp2;

 for (pnp = (struct parmnet_pin_t *) prmp->nlds; pnp != NULL;)
  {
   pnp2 = pnp->pnpnxt;   
   if (pnp->pnp_free) __free_dellst(pnp->pnplp);
   __my_free(pnp, sizeof(struct parmnet_pin_t));
   pnp = pnp2;
  }
}

/*
 * ROUTINES TO IMPLEMENT GATE EATER
 */

/*
 * remove all gates and nets that are not driver or drive nothing
 *
 * if wire connects to I/O port never removed
 * if instance source or destination of xmr never removed 
 * 
 * this uses n_ispthsrc flag since deletable wires never I/O ports
 * also only I/O ports can be deleted so since I/O ports not deletable
 * will never see here 
 * this builds nqc_u (nu2) for keepping track of fan-in/fan-out but always
 * freed when done
 */
static void eat_gates(void)
{
 int32 pi, ni;
 int32 some_eaten, first_time, wlen;
 word32 *wp;
 struct net_t *np;
 struct tfrec_t *tfrp;
 struct mod_t *mdp;
 struct tfarg_t *tfap;

 /* first mark all wires in design that are undeletable */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum == 0) continue;

   __push_wrkitstk(mdp, 0);
   /* this sets n_mark for all nets not candidates for deletion */
   for (ni = 0, np = &(__inst_mod->mnets[0]); ni < __inst_mod->mnnum;
    ni++, np++)
    {
     np->n_mark = FALSE;

     /* cannot delete i/o ports or arrays and must be wire to delete */
     /* temporary n_mark indicates not deletable */
     /* never delete wire in tran channel really has drivers and loads */

     if (np->ntyp >= NONWIRE_ST || np->iotyp != NON_IO || np->ntraux != NULL)
      { np->n_mark = TRUE; continue; }

     /* if only drivers or loads but has must stay npp's cannot delete */
     /* cannot delete if xmr or IS form */
     if (np->ndrvs != NULL && has_muststay_npp(np->ndrvs))
      { np->n_mark = TRUE; continue; }
     if (np->nlds != NULL && has_muststay_npp(np->nlds))
      { np->n_mark = TRUE; continue; }
    }
   __pop_wrkitstk();
  }
 /* also mark all wires that connect to tf_ args - list is design wide */
 /* even if only used in rhs connection */
 for (tfrp = __tfrec_hdr; tfrp != NULL; tfrp = tfrp->tfrnxt)
  {
   for (pi = 1; pi < tfrp->tfanump1; pi++)
    {
     tfap = &(tfrp->tfargs[pi]);
     mark_muststay_wires(tfap->arg.axp);
    }
  }

 /* next do deleting module by module */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   some_eaten = TRUE;
   first_time = TRUE;
   while (some_eaten)
    {
     /* notice only deleted cells can allow new net deletions */
     eat_nets(first_time);
     first_time = FALSE;
     eat_cells(&some_eaten);
    } 
   /* this module done free any qcval fields */
   /* if any qc forms, will be rebuilt and used for different purpose */
   if (__inst_mod->mnnum != 0)
    {
     for (ni = 0, np = &(__inst_mod->mnets[0]); ni < __inst_mod->mnnum;
      ni++, np++)
      {
       /* turn mark off */
       np->n_mark = FALSE;
       if (np->nu2.wp != NULL)
        {
         wlen = 2*wlen_(np->nwid);
         wp = np->nu2.wp;
         __my_free(wp, wlen*WRDBYTES);
         np->nu2.wp = NULL;
        }
      }
    }
   __pop_wrkitstk();
  }
}

/*
 * return T if has some kind of net pin that cannot be deleted
 * 1) if IS form undeletable 
 * 2) if net pin is xmr then net it is on cannot be deleted
 *
 * also) if has I/O port connection, but should never see here
 */
static int32 has_muststay_npp(struct net_pin_t *npp)
{
 struct npaux_t *npauxp;

 for (; npp != NULL; npp = npp->npnxt)
  {
   if (npp->np_xmrtyp != XNP_LOC) return(TRUE);
   if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 == -2) return(TRUE); 
   /* --- DBG remove */
   if (npp->npntyp == NP_MDPRT || npp->npntyp == NP_PB_MDPRT)
    __misc_terr(__FILE__, __LINE__);
  }
 return(FALSE);
}

/*
 * mark wires that must remain uneaten because connect to tf_ arg
 */
static void mark_muststay_wires(struct expr_t *xp)
{
 struct net_t *np;

 if (__isleaf(xp))
  {
   if (xp->optyp == ID || xp->optyp == GLBREF)
    {
     np = xp->lu.sy->el.enp;
     if (np->ntyp < NONWIRE_ST) np->n_mark = TRUE;
    }
   return;
  }
//AIV? 01-18-09 - when add arrays of wires, must go through next ndx here

 if (xp->lu.x != NULL) mark_muststay_wires(xp->lu.x);
 if (xp->ru.x != NULL) mark_muststay_wires(xp->ru.x);
}

/*
 * remove net and npp's for unc. bits 
 * know only nets marked n_ispthsrc (tmp. flag) 
 * tri0/tri1 implied driver nets always have fi = 1
 * 
 */
static void eat_nets(int32 first_time)
{
 int32 ni, wi;
 int32 nfi, nfo, impl_drv, wlen;
 struct net_t *np;
 word32 *wpfi, *wpfo; 

 if (__inst_mod->mnnum == 0) return;
 if (!first_time) rem_del_npps();
 for (ni = 0, np = &(__inst_mod->mnets[0]); ni < __inst_mod->mnnum; ni++, np++)
  {
   if (np->n_mark || np->n_gone) continue;

   impl_drv = wire_implied_driver(np);
   /* assume has fi and fan out */
   nfi = nfo = 1;
   if (!np->n_isavec)
    {
     /* any type of driver including tri0/1 implied prevents deletion */
     /* wire used in any rhs (i.e. procedural) has loads even if no wire */
     /* loads that require event propagation */  
     if (np->nlds == NULL && !np->n_onprocrhs) nfo = 0;
     if (np->ndrvs == NULL && !impl_drv) nfi = 0; 
     if (nfo != 0 && nfi != 0) continue;

do_delete:
     if (nfo == 0 && nfi == 0)
      __gfinform(447, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
       "net %s in %s disconnected: no drivers, no loads and no procedural connections",
       np->nsym->synam, __inst_mod->msym->synam);
     else if (nfi == 0)
      __gfinform(447, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
       "net %s in %s disconnected: no drivers", np->nsym->synam,
       __inst_mod->msym->synam);
     else 
      __gfinform(447, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
       "net %s in %s disconnected: no loads and no procedural connections",
       np->nsym->synam, __inst_mod->msym->synam);
del_done:
     np->n_gone = TRUE;
     remove_all_npps(np);
     __flnets_removable += __inst_mod->flatinum;
     __nets_removable++;
     continue; 
    }
   /* if vector no loads (or proc rhs conns) or drivers can just delete */
   if (np->nlds == NULL && !np->n_onprocrhs) nfo = 0;
   if (np->ndrvs == NULL && !impl_drv) nfi = 0;
   if (nfi == 0 || nfo == 0)
    {
     /* in case last npp removed, mark processed */
     /* here know non i/o that can be deleted is never path source so use */
     /* as temporary need to delete this time flag */
     np->n_isapthsrc = FALSE;
     goto do_delete; 
    }

   /* if npp list changed or not yet built, must build */ 
   if ((wpfi = np->nu2.wp) == NULL || np->n_isapthsrc)
    {
     bld1vec_fifo(np);
     np->n_isapthsrc = FALSE;
     /* make sure wpfi set from nu2 wp union member */
     wpfi = (word32 *) np->nu2.wp;
    }

   /* if at least one driver and used on rhs cannot delete */
   /* but still need per bit fifo vec since if gate connecting bit */
   /* has no fi and no fo even though has proc. connection gate del. gate */
   if (np->ndrvs != NULL && np->n_onprocrhs) goto nxt_net;

   /* must check bit by bit - possible for some bits have fi others fo */  
   wlen = wlen_(np->nwid);
   wpfo = &(wpfi[wlen]);
   for (wi = 0; wi < wlen; wi++)
    {
     /* if even 1 bit fi/fo cannot delete net - but maybe still cells */
     if ((wpfi[wi] & wpfo[wi]) != 0) goto nxt_net;
    }  
   __gfinform(447, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
    "net %s disconnected: no procedural connections and no bit has both drivers and loads",
    np->nsym->synam);
   goto del_done;

nxt_net:;
  }
}

/*
 * routine to remove all marked (n_isapthsrc is tmp flag)
 * this routine is called only after eat cells (not first time)
 * error if at least one not deleted
 * only called if has nets
 */
static void rem_del_npps(void)
{
 int32 ni;
 int32 net_chged;
 struct net_t *np;
 struct net_pin_t *npp;
 struct net_pin_t *npp2, *last_npp;

 for (ni = 0, np = &(__inst_mod->mnets[0]); ni < __inst_mod->mnnum; ni++, np++)
  {
   if (np->n_mark || !np->n_isapthsrc || np->n_gone) continue;

   /* first remove net pin elements connected to removed cells */ 
   for (net_chged = FALSE, last_npp = NULL, npp = np->ndrvs; npp != NULL;)
    {
     switch ((byte) npp->npntyp) {
      case NP_GATE:
       /* know this is at most 1 wire and net pin element no xmr field */ 
       if (!npp->elnpp.egp->g_gone) break;
do_gate_npp_del:
       if (last_npp == NULL) np->ndrvs = npp->npnxt;
       else last_npp->npnxt = npp->npnxt;
       npp2 = npp->npnxt;      
       __my_free(npp, sizeof(struct net_pin_t));  
       npp = npp2;
       net_chged = TRUE;
       continue;
      case NP_CONTA:
       if (npp->elnpp.ecap->ca_gone) goto do_gate_npp_del;
       break;
     }
     last_npp = npp;
     npp = npp->npnxt; 
    }
   for (last_npp = NULL, npp = np->nlds; npp != NULL;)
    {
     switch ((byte) npp->npntyp) {
      case NP_GATE:
       /* know this is at most 1 wire and net pin element no xmr field */ 
       if (!npp->elnpp.egp->g_gone) break;
do_npp_del:
       if (last_npp == NULL) np->nlds = npp->npnxt;
       else last_npp->npnxt = npp->npnxt;
       npp2 = npp->npnxt;      
       __my_free(npp, sizeof(struct net_pin_t));  
       npp = npp2;
       net_chged = TRUE;
       continue;
      case NP_CONTA:
       if (npp->elnpp.ecap->ca_gone) goto do_npp_del;
       break;
       /* tf form should only be driver */
     }
     last_npp = npp;
     npp = npp->npnxt; 
    }
   /* no net pin list change - do not rebuild the per bit table */
   if (!net_chged) np->n_isapthsrc = FALSE;
  }
}

/* 
 * when net deleted, remove all npps 
 */
static void remove_all_npps(struct net_t *np)
{
 struct net_pin_t *npp;
 struct net_pin_t *npp2;

 for (npp = np->ndrvs; npp != NULL;)
  {
   npp2 = npp->npnxt;      
   __my_free(npp, sizeof(struct net_pin_t));  
   npp = npp2;
  }
 np->ndrvs = NULL;
 for (npp = np->nlds; npp != NULL;)
  {
   npp2 = npp->npnxt;      
   __my_free(npp, sizeof(struct net_pin_t));  
   npp = npp2;
  }
 np->nlds = NULL;
}

/*
 * build (rebuild) the per bit fi/fo table
 * sets nfi/nfo to 0 if entire wire unc. and 1 if at least one bit has conn.
 * for implied driver nets, set to 1 even if no "real" drivers
 */
static void bld1vec_fifo(struct net_t *np)
{
 int32 *pbfi, *pbfo, *pbtcfo, wlen;
 word32 *wp;

 /* first try simple case */
 pbfi = (int32 *) __my_malloc(sizeof(int32)*np->nwid);
 pbfo = (int32 *) __my_malloc(sizeof(int32)*np->nwid);
 pbtcfo = (int32 *) __my_malloc(sizeof(int32)*np->nwid);
 /* inst. number not used here since never remove net iwth IS form */
 __bld_pb_fifo(np, pbfi, pbfo, pbtcfo, 0);
 wp = np->nu2.wp;
 if (wp == NULL)
  {
   wlen = 2*wlen_(np->nwid);
   wp = (word32 *) __my_malloc(wlen*WRDBYTES);
   memset(wp, 0, wlen*WRDBYTES);
   np->nu2.wp = wp;
  }
 update_vec_fifo(np, wp, pbfi, pbfo, pbtcfo);
 __my_free(pbfi, sizeof(int32)*np->nwid);
 __my_free(pbfo, sizeof(int32)*np->nwid);
 __my_free(pbtcfo, sizeof(int32)*np->nwid);
}

/*
 * set per bit fi/fo values in net working fi/fo ares
 * tri0/tri1 implied driver net has has fi 1
 * if wire bit drivers timing check then still has driver and must stay
 */
static void update_vec_fifo(struct net_t *np, word32 *wpfi, int32 *pbfi, 
 int32 *pbfo, int32 *pbtcfo)
{
 int32 bi;
 int32 wi, biti;
 int32 wlen, implied_drv;
 word32 *wpfo;

 wlen = wlen_(np->nwid);
 wpfo = &(wpfi[wlen]);
 implied_drv = wire_implied_driver(np);
 for (bi = 0; bi < np->nwid; bi++)
  {
   wi = get_wofs_(bi);
   biti = get_bofs_(bi);
   if (pbfi[bi] == 0 && !implied_drv) wpfi[wi] &= ~(1L << biti);
   else wpfi[wi] |= (1L << biti);
   /* know 2 bits never cross word32 boundary */
   if (pbfo[bi] == 0 && pbtcfo[bi] == 0) wpfo[wi] &= ~(1L << biti);
   else wpfo[wi] |= (1L << biti);
  }
}

/*
 * return T if wire is implied driver type
 */
static int32 wire_implied_driver(struct net_t *np) 
{
 switch ((byte) np->ntyp) {
  case N_TRI0: case N_TRI1: case N_TRIREG: case N_SUPPLY0: case N_SUPPLY1:
   return(TRUE);
 }
 return(FALSE);
}

/*
 * delete cells (gate and non xmr source/destination module instances
 * only gate and continuous assignments are removed
 */
static void eat_cells(int32 *some_eaten)
{
 int32 i, gi;
 struct gate_t *gp;
 struct conta_t *cap;
 int32 cai, out_unconn, ins_unconn;

 /* go through module gates tryng to remove (disconnect) */
 *some_eaten = FALSE;
 for (gi = 0; gi < __inst_mod->mgnum; gi++)
  {
   gp = &(__inst_mod->mgates[gi]);
   if (gp->g_gone) continue;

   /* can never delete pullup or pulldown */
   out_unconn = ins_unconn = FALSE;
   if (gp->g_class == GC_PULL) continue;
   /* for trans, in tran channels so do not process here */
   if (gp->g_class == GC_TRAN || gp->g_class == GC_TRANIF) continue;

   /* if output not gone, see if all inputs gone */
   if (conn_expr_gone(gp->gpins[0])) out_unconn = TRUE;
   for (i = 1; i < (int32) gp->gpnum; i++)
    { if (!conn_expr_gone(gp->gpins[i])) goto try_delete; }
   ins_unconn = TRUE;
   /* mark the gate deleted */
try_delete:
   if (ins_unconn || out_unconn)
    {
     if (ins_unconn && out_unconn)
      __gfinform(448, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
       "%s gate %s deleteable because all ports unconnected",
       gp->gmsym->synam, gp->gsym->synam);
     else if (out_unconn)
      __gfinform(448, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
       "%s gate %s deleteable because output unconnected",
       gp->gmsym->synam, gp->gsym->synam);
     else 
      __gfinform(448, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
       "%s gate %s deleteable because all inputs unconnected",
       gp->gmsym->synam, gp->gsym->synam);
     gp->g_gone = TRUE;
     /* gate is gone - mark all nets not already deleted for fi-fo re-eval */
     for (i = 1; i < (int32) gp->gpnum; i++)
      mark_maybe_gone_nets(gp->gpins[i]);
     *some_eaten = TRUE;
     __flgates_removable += __inst_mod->flatinum;
     __gates_removable++;
    }
  }
 /* no module removable - better to first use some kind of inlining */
 /* and then remove gates from that if possible */

 /* try to remove (disconnect) continuous assigns */ 
 /* go through module gates tryng to remove (disconnect) */
 for (cap = __inst_mod->mcas, cai = 0; cai < __inst_mod->mcanum; cai++, cap++)
  {
   if (cap->ca_gone) continue;

   /* can never delete pullup or pulldown */
   out_unconn = ins_unconn = FALSE;  
   /* if output not gone, see if all inputs gone */
   if (conn_expr_gone(cap->lhsx)) out_unconn = TRUE;
   if (conn_expr_gone(cap->rhsx)) ins_unconn = TRUE;
   if (ins_unconn || out_unconn)
    {
     if (ins_unconn && out_unconn)
      __gfinform(448, cap->casym->syfnam_ind, cap->casym->sylin_cnt,
       "continuous assign deleteable because it has no connections");
     else if (out_unconn)
      __gfinform(448, cap->casym->syfnam_ind, cap->casym->sylin_cnt,
       "continuous assign deletable because left hand side drives nothing");
     else 
      __gfinform(448, cap->casym->syfnam_ind, cap->casym->sylin_cnt,
       "continuous assign deletable because right hand side unconnected");
     cap->ca_gone = TRUE;
     mark_maybe_gone_nets(cap->lhsx);
     mark_maybe_gone_nets(cap->rhsx);
     *some_eaten = TRUE;
     __flcontas_removable += __inst_mod->flatinum;
     __contas_removable++;
    }
  }
}

/*
 * return T if expression is removable (no connectons) 
 * notice constants cannot be deleted
 *
 * also n_mark set for undeletable nets that do not have fi-fo table
 * know if n_mark off and not already deleted, know fi-fo table exists
 */
static int32 conn_expr_gone(struct expr_t *xp)
{
 int32 bi;
 int32 bi2, nfi, nfo;
 struct net_t *np;
 struct expr_t *ndx, *ndx2; 

 switch (xp->optyp) {
  case ID:
   np = xp->lu.sy->el.enp; 
   if (!np->n_gone) return(FALSE);
   break;
  case OPEMPTY: break;
  case LSB: 
   np = xp->lu.x->lu.sy->el.enp; 
   if (!np->n_gone) 
    {
     if (np->n_mark) return(FALSE);
     ndx = xp->ru.x; 
     if (ndx->optyp == NUMBER)
      {
       bi = __comp_ndx(np, ndx);
       if (bi == -1) return(FALSE);  
       getbit_fifo(np, bi, &nfi, &nfo);
       if (nfi == 0 || (nfo == 0 && !np->n_onprocrhs)) break;
      }
     return(FALSE);
    }
   break;
  case PARTSEL:
   np = xp->lu.x->lu.sy->el.enp; 
   if (!np->n_gone) 
    {
     if (np->n_mark) return(FALSE);
     ndx = xp->ru.x->lu.x;
     if ((bi = __comp_ndx(np, ndx)) == -1) return(FALSE);
     ndx2 = xp->ru.x->ru.x;
     if ((bi2 = __comp_ndx(np, ndx2)) == -1) return(FALSE);
     for (; bi >= bi2; bi--)
      {
       getbit_fifo(np, bi, &nfi, &nfo);
       if (nfi != 0 && (nfo != 0 || np->n_onprocrhs)) return(FALSE);
      }
     /* fall thru, all bits of part select unc. */
    }
   break;
  case LCB:
   /* for concatenate all components must be gone */
   for (ndx2 = xp->ru.x; ndx2 != NULL; ndx2 = ndx2->ru.x)
    { if (!conn_expr_gone(ndx2->lu.x)) return(FALSE); }
   break;
  /* anything else (such as function or arithmetic expr. must stay */
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * set n_isapthsrc to indicate net can be deleted and must have nlds and
 * ndrvs updated and maybe removed
 *
 * must mark all nets in expr.
 * notice constants cannot be deleted
 */
static void mark_maybe_gone_nets(struct expr_t *xp)
{
 struct net_t *np;
 struct expr_t *ndx2;

 switch (xp->optyp) {
  case ID:
   np = xp->lu.sy->el.enp; 
   if (!np->n_gone) np->n_isapthsrc = TRUE;
   break;
  case OPEMPTY: break;
  case LSB: case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   np = xp->lu.x->lu.sy->el.enp; 
   if (!np->n_gone) np->n_isapthsrc = TRUE;
   break;
  case LCB:
   /* for concatenate all components must be gone */
   for (ndx2 = xp->ru.x; ndx2 != NULL; ndx2 = ndx2->ru.x)
    mark_maybe_gone_nets(ndx2->lu.x);
   break;
 }
}

/*
 * the the fi and fo for 1 bit
 */
static void getbit_fifo(struct net_t *np, int32 bi, int32 *nfi, int32 *nfo)
{
 int32 wi, biti, wlen;
 word32 *wpfi, *wpfo;

 /* must check the bit if constant */
 wi = get_wofs_(bi);
 biti = get_bofs_(bi);
 /* DBG remove */
 if ((wpfi = (word32 *) np->nu2.wp) == NULL) __misc_terr(__FILE__, __LINE__);
 wlen = wlen_(np->nwid);
 wpfo = &(wpfi[wlen]);
 *nfi = ((wpfi[wi] & (1L << biti)) != 0L) ? 1 : 0;
 *nfo = ((wpfo[wi] & (1L << biti)) != 0L) ? 1 : 0;
}

/*
 * ROUTINES TO DETERMINE IF GATE CAN BE OPTIMIZED (USED ACC ROUTINE)
 */

/*
 * return T if gate is acceleratable buf or not
 * accelerate classes are 0 std non accel., 2 buf/not, 3 acc. logic
 *
 * will not accelerate if: 1) >3 inputs, 2) drives strength, 3) 1 in and style 
 * 4) drives fi>1 wire, 5) output is not scalar or constant bit select,
 * 6) inputs not accelerable
 *
 * notice whether or not has delay does effect acc class
 */
extern int32 __get_acc_class(struct gate_t *gp)
{
 int32 gi;
 int32 acc_class, st_on_input, wire_pthdel;
 word32 gatid;
 struct expr_t *xp;
 struct net_t *np;

 acc_class = ACC_NONE;
 st_on_input = FALSE;
 /* can have up to 3 inputs and 1 output for acceleration - fits in byte */
 if (gp->g_hasst || gp->gpnum > 4) return(ACC_STD);
 gatid = gp->gmsym->el.eprimp->gateid;
 switch ((byte) gatid) { 
  case G_NOT: case G_BUF: case G_ASSIGN: acc_class = ACC_BUFNOT; break; 
  case G_NAND: case G_BITREDAND: case G_BITREDOR:
  case G_NOR: case G_BITREDXOR: case G_REDXNOR:
   /* never accelerate degenerate 2 input gates that are usually >=3 in */
   if (gp->gpnum == 2) return(ACC_STD);
   acc_class = ACC_4IGATE;
   break;
  default: return(ACC_STD);
 }  
 /* only get here for logic gates - mos, tran, etc. always std */
 /* output must be simple wire or constant bsel from wire */
 xp = gp->gpins[0];
 /* cannot be fi>1 and know if in tran channel will be fi>1 */
 if (xp->x_multfi) return(ACC_STD);
 if (xp->optyp == ID)
  {
   np = xp->lu.sy->el.enp; 
   if (np->n_isavec || np->n_stren) return(ACC_STD);
  }
 else if (xp->optyp == LSB)
  {
   if (xp->ru.x->optyp != NUMBER) return(ACC_STD);
   np = xp->lu.x->lu.sy->el.enp; 
   if (np->n_stren) return(ACC_STD);
  }
 else return(ACC_STD);
 /* DBG remove */
 if (np->ntraux != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (np->nrngrep == NX_DWIR) wire_pthdel = TRUE; else wire_pthdel = FALSE;

 /* all inputs must be XL accelerateable */
 for (st_on_input = FALSE, gi = 0; gi < (int32) gp->gpnum; gi++)
  {
   xp = gp->gpins[gi];
   if (xp->optyp == ID)
    {
     np = xp->lu.sy->el.enp;
     if (np->n_isavec) return(ACC_STD);
     if (np->n_stren) st_on_input = TRUE; 
    }
   /* strength on bit select ok, slower does not need separate case */
   else if (xp->optyp == LSB)
    {
     if (xp->ru.x->optyp != NUMBER) return(ACC_STD);
     /* AIV 02/11/12 - if XMR bit select cannot do the accelerated case */
     /* was setting the wrong idp which slightly causes problems */
     /* that and the lu.x->lu.sy->n_isarr is not right for XMR */
     if (xp->lu.x->optyp == GLBREF) return(ACC_STD);
     /* SJM 05/17/03 - array (memory) selects on input must not accelerate */
     if (xp->lu.x->lu.sy->el.enp->n_isarr) return(ACC_STD);
    }
   else return(ACC_STD);
  }
 if (st_on_input)
  {
   if (acc_class == ACC_BUFNOT) acc_class = ACC_STIBUFNOT;
   else if (acc_class == ACC_4IGATE) acc_class = ACC_ST4IGATE;
  }
 gp->g_pdst = wire_pthdel;
 return(acc_class);
}

/*
 * ROUTINES TO CONVERT FROM DT_NONE TO #0 FOR DELAY ANNOTATION
 */

/*
 * add delay (set to #0) to gate
 *
 * know called after prep
 */
extern int32 __add_gate_pnd0del(struct gate_t *gp, struct mod_t *mdp,
 char *sdfmsg)
{
 struct net_t *np;
 struct primtab_t *ptp;
 struct expr_t *xp;

 ptp = gp->gmsym->el.eprimp;
 /* make sure gate can have delay */
 if (ptp->gateid == G_TRAN || ptp->gateid == G_RTRAN)
  {
   /* rnotice error here will stop simulation */
   if (sdfmsg != NULL)
    __pv_ferr(1199, 
     "%s delay annotate to %s gate %s for which delay illegal", sdfmsg,
     gp->gmsym->synam, gp->gsym->synam);
   else __vpi_err(1893, vpiError,
    "vpi_put_delays illegal for %s gate %s for which delay illegal",
    gp->gmsym->synam, gp->gsym->synam);
   return(FALSE);
  }
 /* set delay to pnd 0 */
 gp->g_du.d1v = (word64 *) __my_malloc(sizeof(word64));
 gp->g_du.d1v[0] = 0ULL;
 gp->g_delrep = DT_1V;

//AIV LOOKATME - not so sure about this ???????
//AIV REMOVEME - this isn't no longer set and init here done at idp init
 /* DBG remove --- */
 //if (gp->schd_tevs_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* allocate and initialize the inertial pending schd event table */
 /* ---------------
 for (i = 0; i < mdp->flatinum; i++) 
  {
   idp = mdp->moditps[i]->it_idp;
   idp[gp->schd_tevs_ofs] = (t_midat) NULL;
  }
 ------------------*/

 /* if accelerated set g resist if driven wire has delay or path dest */
 if (__gate_is_acc(gp))
  {
   xp = gp->gpins[0];
   if (xp->optyp == ID) np = xp->lu.sy->el.enp; 
   else if (xp->optyp == LSB) np = xp->lu.x->lu.sy->el.enp; 
   else { np = NULL;  __case_terr(__FILE__, __LINE__); }
   if (np->nrngrep == NX_DWIR) gp->g_pdst = TRUE; 
  }
 return(TRUE);
}

/*
 * add conta delay (add drivers and internal conta value too) (set to #0)
 *
 * know called after prep and know no delay 
 * SJM 09/29/02 - if per bit this must set master delay and PB drv/schd
 */
extern int32 __add_conta_pnd0del(struct conta_t *cap, struct mod_t *mdp,
 char *sdfmsg)
{
 int32 bi, i;
 struct conta_t *pbcap;
 t_midat *idp;

 /* make sure gate can have delay */
 if (cap->lhsx->getpatlhs)
  {
   /* rnotice error here will stop simulation */
   __bld_lineloc(__xs, cap->casym->syfnam_ind, cap->casym->sylin_cnt);
   if (sdfmsg != NULL)
    __pv_ferr(1379, 
     "%s delay annotate to $getpattern continuous assign at %s illegal",
     sdfmsg, __xs);
   else __vpi_err(1905, vpiError,
     "vpi_put_delays illegal for $getpattern continuous assign at %s", __xs);
   return(FALSE);
  }
 
 if (!cap->ca_pb_sim)
  {
   /* since before any sim or new PLI added del, initialized value correct */
   if (!cap->lhsx->x_multfi)
    {
     /* DBG remove --- */
     if (cap->ca_drv_ofs == 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
//AIV FIXME - don't think this is needed because it is now stored in
//idp area and is inti there
     __init_all_inst_conta_drv(cap->ca_drv_ofs, cap->lhsx->szu.xclen, mdp);
    }
   /* DBG remove --- */
   if (cap->schd_drv_ofs == 0) __misc_terr(__FILE__, __LINE__);
   if (cap->caschd_tevs_ofs == 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* nothing will be scheduled and this will not be allocated */
   for (i = 0; i < mdp->flatinum; i++) 
    {
     idp = mdp->moditps[i]->it_idp;
     idp[cap->caschd_tevs_ofs] = (t_midat) NULL;
    }
//AIV FIXME - don't think this is needed because it is now stored in
//idp area and is inti there
   __init_all_inst_conta_drv(cap->schd_drv_ofs, cap->lhsx->szu.xclen, mdp);
  }
 else
  {
   for (bi = 0; bi < cap->lhsx->szu.xclen; bi++)
    {
     pbcap = &(cap->pbcau.pbcaps[bi]);
     /* DBG remove */
     if (pbcap->lhsx->szu.xclen != 1) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* since before any sim or new PLI added del, init value correct */
     /* SJM 09/28/02 - if master cat expr fi>1, need all per bits */
     if (!cap->lhsx->x_multfi)
      {
       /* DBG remove --- */
       if (pbcap->ca_drv_ofs == 0) __misc_terr(__FILE__, __LINE__);
       if (pbcap->caschd_tevs_ofs == 0) __misc_terr(__FILE__, __LINE__);
       /* --- */
//AIV FIXME - don't think this is needed because it is now stored in
//idp area and is inti there
       __init_all_inst_conta_drv(pbcap->ca_drv_ofs, 1, mdp);
      }
     /* DBG remove --- */
     if (pbcap->schd_drv_ofs == 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
     for (i = 0; i < mdp->flatinum; i++) 
      {
       idp = mdp->moditps[i]->it_idp;
       idp[pbcap->caschd_tevs_ofs] = (t_midat) NULL;
      }
     /* nothing will be scheduled and this will not be allocated */
//AIV FIXME - don't think this is needed because it is now stored in
//idp area and is inti there
     __init_all_inst_conta_drv(pbcap->schd_drv_ofs, 1, mdp);
    } 
  }

 /* SJM 09/28/02 - delay always in master never per bit */
 /* set delay to pnd 0 */
 cap->ca_du.d1v = (word64 *) __my_malloc(sizeof(word64));
 cap->ca_du.d1v[0] = 0ULL;
 cap->ca_delrep = DT_1V;

 return(TRUE);
}

/*
 * ROUTINES TO REMOVE ALL 0 DELAY PATHS
 */

/*
 * remove 0 path delays
 *
 * all this does is link out npp - rest of d.s. small and interlinked
 * only remove source tchg npps if not part of other non removed path
 *
 * FIXME - for now not removing source changes - set ref. count but not using
 * will do extra work in recording each path source change but no path 
 * processing because destinations not path dests any more
 */
extern void __rem_0path_dels(void)
{
 int32 pi;
 int32 has_0del, dbi, dbi2, ni, ii, ofs;
 int32 num_pthrem_mods, num_pthrems, num_flat_pthrems;
 int32 num_pthrem_nets, num_flat_pthrem_nets;
 word64 *w64p;
 word64 newtime;
 t_midat *idp;
 struct net_pin_t *npp;
 struct spcpth_t *pthp; 
 struct mod_t *mdp;
 struct pathel_t *spep, *dpep;
 struct npaux_t *npauxp;
 struct net_t *snp, *dnp;
 struct pthdst_t *pdp, *pdp2, *last_pdp; 
 struct rngdwir_t *dwirp; 
 struct expr_t *lhsx;

 num_pthrem_mods =  num_pthrems = num_flat_pthrems = 0;
 num_pthrem_nets = num_flat_pthrem_nets = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mspfy == NULL || mdp->mspfy->spcpths == NULL) continue;

   /* know each delay is NUMBER or REALNUM */ 
   has_0del = FALSE;
   for (pthp = mdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
    {
     if (pthp->pth_gone) continue;

     if (__chk_0del(pthp->pth_delrep, pthp->pth_du, mdp) == DBAD_0) 
      {
       pthp->pth_0del_rem = TRUE;
       num_pthrem_mods++;
       has_0del = TRUE;
      } 
    }
   if (!has_0del) continue;

   /* know at least one path must be removed */
   /* step 1: set all path src ref counts - >1 dests for one src possible */
   for (pthp = mdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
    {
     /* think impossible for some paths to be gone and make it to prep */   
     if (pthp->pth_gone) continue;

     for (pi = 0; pi <= pthp->last_pein; pi++)
      {
       spep = &(pthp->peins[pi]);
       snp = spep->penp;
       for (npp = snp->nlds; npp != NULL; npp = npp->npnxt) 
        {
         if (npp->npntyp != NP_TCHG || npp->chgsubtyp != NPCHG_PTHSRC)
          continue;
         /* know tchg sources always per bit - for scalar 0 */

         /* path source npp's always one bit, -1 only if scalar */
         if ((npauxp = npp->npaux) != NULL) dbi = npauxp->nbi1;
         else dbi = -1;
         if (spep->pthi1 == -1 || (dbi <= spep->pthi1 && dbi >= spep->pthi2)) 
          {
           /* AIV 08/19/09 - compiler no longer sets __idp at comp time */
           if (__compiled_sim && !__running_cvc_exe) continue;
           /* inc ref. count - know value previously inited to 0 */
           for (ii = 0; ii < mdp->flatinum; ii++)
            {
             idp = mdp->moditps[ii]->it_idp;
             /* DBG remove */
             if (idp == NULL) __misc_terr(__FILE__, __LINE__);
             /* -- */
             ofs = npp->elnpp.etchgp->lastchg_ofs;
             w64p = (word64 *) &(idp[ofs]);
             newtime = *w64p;
             newtime++;
             *w64p = newtime;
            }
          }
        }
      }
    } 
   /* step 2: actually remove path dst npp's and decr. pstchg source counts */
   for (pthp = mdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
    {
     if (!pthp->pth_0del_rem) continue;
     
     num_pthrems++;
     num_flat_pthrems += mdp->flatinum;
  
     for (pi = 0; pi <= pthp->last_peout; pi++)
      {
       dpep = &(pthp->peouts[pi]);
       dnp = dpep->penp;
  
       for (npp = dnp->nlds; npp != NULL; npp = npp->npnxt) 
        {
         if (npp->npntyp != NP_TCHG || npp->chgsubtyp != NPCHG_PTHSRC)
          continue;
         if (!dnp->n_isavec) dbi = dbi2 = 0; 
         else
          {
           if (dpep->pthi1 == -1) { dbi = dnp->nwid - 1; dbi2 = 0; }  
           else { dbi = dpep->pthi1; dbi2 = dpep->pthi2; }
          }
  
         /* for every bit of destination path element */
         dwirp = dnp->nu.rngdwir;
         for (; dbi >= dbi2; dbi--)
          {
           last_pdp = NULL;
           for (pdp = dwirp->n_du.pb_pthdst[dbi]; pdp != NULL;)
            {
             pdp2 = pdp->pdnxt;
             if (pdp->pstchgp->chgu.chgpthp == pthp)
              {
               if (last_pdp == NULL) dwirp->n_du.pb_pthdst[dbi] = pdp->pdnxt; 
               else last_pdp->pdnxt = pdp->pdnxt;
               __my_free(pdp, sizeof(struct pthdst_t)); 
              }
             else last_pdp = pdp;
             pdp = pdp2; 
            }
          }
        }
      }
    }

   /* for path dest. nets with all pthdst removed - set as non path dest. */
   for (ni = 0, dnp = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, dnp++) 
    {
     if (!dnp->n_isapthdst) continue;

     dwirp = dnp->nu.rngdwir;
     if (!dnp->n_isavec)
      {
       if (dwirp->n_du.pb_pthdst[0] != NULL) continue;
      }
     else
      {
       for (dbi = dnp->nwid - 1; dbi >= 0; dbi--)
        {
         if (dwirp->n_du.pb_pthdst[dbi] != NULL) continue;
        }
      } 
     /* convert to non path dest. */
     __my_free(dwirp->n_du.pb_pthdst, dnp->nwid*sizeof(struct pthdst_t *));
     dwirp->n_du.d1v = NULL;
     dwirp->n_delrep = DT_NONE;
     dnp->n_isapthdst = FALSE;
     num_pthrem_nets++;
     num_flat_pthrem_nets += mdp->flatinum;
     /* SJM 07/23/03 - must turn off all lhsx ndel marks for completely */
     /* removed paths where driver is gate out or conta */
     for (npp = dnp->ndrvs; npp != NULL; npp = npp->npnxt) 
      {
       if (npp->npntyp == NP_GATE) lhsx = npp->elnpp.egp->gpins[0];
       else if (npp->npntyp == NP_CONTA) lhsx = npp->elnpp.ecap->lhsx; 
       else continue;
  
       /* DBG remove */
       if (!lhsx->lhsx_ndel) __misc_terr(__FILE__, __LINE__);
       /* -- */
       if (lhsx->lhsx_ndel) lhsx->lhsx_ndel = FALSE;
      }
    }

   /* step 3: reset lastchg field and remove if needed - no longer ref cnt */
   for (pthp = mdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
    {
     if (pthp->pth_gone) continue;

     for (pi = 0; pi <= pthp->last_pein; pi++)
      {
       spep = &(pthp->peins[pi]);
       snp = spep->penp;
       for (npp = snp->nlds; npp != NULL; npp = npp->npnxt) 
        {
         if (npp->npntyp != NP_TCHG || npp->chgsubtyp != NPCHG_PTHSRC)
          continue;
         /* path source npp's always one bit, -1 only if scalar */
         if ((npauxp = npp->npaux) != NULL) dbi = npauxp->nbi1;
         else dbi = -1;
         if (spep->pthi1 == -1 || (dbi <= spep->pthi1 && dbi >= spep->pthi2)) 
          {
           /* AIV 08/19/09 - compiler no longer sets __idp at comp time */
           if (__compiled_sim && !__running_cvc_exe) continue;
           /* reset ref. count */
           for (ii = 0; ii < mdp->flatinum; ii++)
            {
             idp = mdp->moditps[ii]->it_idp;
             /* DBG remove */
             if (idp == NULL) __misc_terr(__FILE__, __LINE__);
             /* -- */
             ofs = npp->elnpp.etchgp->lastchg_ofs;
             w64p = (word64 *) &(idp[ofs]);
             *w64p = 0ULL;
            }
          }
        }
      }
    } 
  }
 if (num_pthrem_mods != 0 && __verbose) 
  {
   __cv_msg(
    "  %d zero delay paths (%d flat) in %d types removed - no effect.\n",
    num_pthrems, num_flat_pthrems, num_pthrem_mods);
  }
 if (num_pthrem_nets != 0 && __verbose)
  {
   __cv_msg(
    "  %d nets (%d flat) no longer path destinations (all paths zero delay).\n",
    num_pthrem_nets, num_flat_pthrem_nets);
  }
}

/*
 * ROUTINES TO BUILD ALL NET CHANGES
 */

/*
 * build all static net changes
 * build compile time information on all possible net changes recording
 * all possible range changes to make the fixed net change structs
 */
static void bld_all_netchanges(void)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct task_pin_t *tpp;

#ifdef __XPROP__
 /* AIV 02/28/12 - this needs to go first - as others are made from this */
 //AIV LOOKATME - can now be making changes which are not needed because they
 //do nothing 
 
 /* AIV 10/25/11 - __xprop needs to make sure that lhs nets have a net */
 /* change struct ID.  xprop assigns the entire net at the end of combining */
 /* so if only net changes on certain bits this will not be set */
 if (__xprop)
  {
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     /* AIV 02/28/12 if module does not use xprop don't need these */
     if (!mdp->m_use_xprop) continue;

     add_1mod_nchges_from_nd_chgst_bit(mdp, FALSE);
    }
  }
#endif
 /* SJM 11-07-12 - SJM - needed or no drvr/no ld toggle coverage not chg st */
 /* for toggle coverage also need to turn on entire net - if others added */
 /* will be matched and not added */
 /* notice any use optconfigfile or option, will turn this flag on */
 if (__toggle_coverage)
  {
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     /* AIV 02/28/12 if module does not use xprop don't need these */
     if (!mdp->m_has_toggle_cover) continue;

     add_1mod_nchges_from_nd_chgst_bit(mdp, TRUE);
    }
  }

 /* AIV 02/14/12 - cannot set __nchg_ndx here must init at cvc init */
 /* variables because some net changes are now added earlier than here */
 /* __nchg_ndx = -1; */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum != 0)
    {
     /* get possible net changes for each net */
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       /* AIV 02/03/11 - forced tran nets need to be the first net change */
       /* items added */
       add_force_net_tran_changes(np);
       /* first do loads */
       add_net_changes_from_lds(np);
       /* possbile dce net changes */
       add_net_changes_from_dces(np);
       /* driver net changes */
       add_net_changes_from_drvs(np);
       /* wire delay events */
       set_process_wire_ev_flag(mdp, np);
       /* tran channel net changes */
       add_net_changes_from_tran(np);
      } 
    }

   /* same for all task nets */
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       add_force_net_tran_changes(np);
       add_net_changes_from_lds(np);
       add_net_changes_from_dces(np);
       add_net_changes_from_drvs(np);
       set_process_wire_ev_flag(mdp, np);
       add_net_changes_from_tran(np);
      }

     /* add net change for all task pins */
     for (tpp = tskp->tskpins; tpp != NULL; tpp = tpp->tpnxt)
      {
       if (tpp->tpsy == NULL) continue;
       np = tpp->tpsy->el.enp;
       if (np->nchg_nd_chgstore) 
        {
         add_net_change(np, -1, -1, FALSE, FALSE, FALSE); 
        }
      }
    }
  }

 /* now get all net changes for continous assigns and procedural */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   add_conta_netchgs(mdp);
   add_proc_stmt_netchgs(mdp);
  }
 /* AIV 12/12/07 - this needs to be a separate pass a different mod's */
 /* proc statements may change due to another mod's */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* AIV LOOKATME - better way to do this or avoid the record ????? */
   /* AIV 10/18/07 need to do stmts twice in case later stmt effects a later */
   /* r[0] = 1, needs to record due to a later processed r = 3'b001; */
   /* AIV FIXME if @r[2] don't need to record the r[0] know never triggers */
   add_proc_stmt_netchgs(mdp);
  }
}

/*
 * add net chges from nchg nd chgstore (interpreter bits)
 *
 * SJM 11-07-12 - new proc because missing compiler run time needed fixed
 * nchg records
 *
 * idea for ompiler is not not build const net chges that do not really
 * propagate anything but needed for xprop and for toggle coverage
 *
 * proc builds static which need to exist at run time as fixed storage
 */
static void add_1mod_nchges_from_nd_chgst_bit(struct mod_t *mdp,
 int32 filter_net_tgl_on)
{
 int32 ni;
 struct net_t *np;
 struct task_t *tskp;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   if (np->nchg_nd_chgstore) 
    {
     if (filter_net_tgl_on && !np->n_has_toggle) continue;
     add_net_change(np, -1, -1, TRUE, FALSE, FALSE); 
    }
  }
 /* need chg stores if xprop also for task vars */
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   if (tskp->trnum == 0) continue;
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     if (np->nchg_nd_chgstore) 
      {
       if (filter_net_tgl_on && !np->n_has_toggle) continue;

       add_net_change(np, -1, -1, TRUE, FALSE, FALSE); 
      }
    }
  } 
}

/* 
 * add net change for all its loads
 */
static void add_net_changes_from_lds(struct net_t *np)
{
 struct net_pin_t *npp;
 struct npaux_t *npauxp;

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 != -1)
    {
     add_net_change(np, npauxp->nbi1, npauxp->nbi2.xvi, TRUE, FALSE, FALSE); 
    }
   else add_net_change(np, -1, -1, TRUE, FALSE, FALSE); 
  }
}

/* 
 * add net change for a net's dces
 */
static void add_net_changes_from_dces(struct net_t *np)
{
 struct dcevnt_t *dcep;

 for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt) 
  {
//AIV FIXME - don't think this is needed but leaving until works
   switch ((byte) dcep->dce_typ) {
    case DCE_RNG_INST: 
     add_net_change(np, dcep->dci1, dcep->dci2.xvi, TRUE, FALSE, FALSE); 
    break;
    case DCE_INST: 
     if (dcep->dci1 != -1 && dcep->dci2.xvi != -1) 
       __misc_terr(__FILE__, __LINE__);
     add_net_change(np, dcep->dci1, dcep->dci2.xvi, TRUE, FALSE, FALSE); 
    break;
    case DCE_RNG_MONIT: 
     add_net_change(np, dcep->dci1, dcep->dci2.xvi, TRUE, FALSE, FALSE); 
     break;
    case DCE_MONIT: 
     if (dcep->dci1 != -1 && dcep->dci2.xvi != -1) 
       __misc_terr(__FILE__, __LINE__);
     add_net_change(np, dcep->dci1, dcep->dci2.xvi, TRUE, FALSE, FALSE); 
     break;
    case DCE_RNG_QCAF: 
     add_net_change(np, dcep->dci1, dcep->dci2.xvi, TRUE, FALSE, FALSE); 
     break;
    case DCE_QCAF: 
     if (dcep->dci1 != -1 && dcep->dci2.xvi != -1) 
       __misc_terr(__FILE__, __LINE__);
     add_net_change(np, dcep->dci1, dcep->dci2.xvi, TRUE, FALSE, FALSE); 
     break;
    case DCE_RNG_PVC:
    case DCE_PVC:
    case DCE_RNG_CBVC:
     __case_terr(__FILE__, __LINE__);
     break;
    case DCE_CBF: case DCE_RNG_CBF: case DCE_CBR: case DCE_RNG_CBR:
     if (dcep->dci1 != -1 && dcep->dci2.xvi != -1) 
       __misc_terr(__FILE__, __LINE__);
     add_net_change(np, dcep->dci1, dcep->dci2.xvi, TRUE, FALSE, FALSE); 
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
 }
}

/*
 * get all net changes from a nets drivers
 */
static void add_net_changes_from_drvs(struct net_t *np)
{
 int32 i1, i2;
 struct net_pin_t *npp;
 struct npaux_t *npauxp;

 /* don't need to record return - nothing to add */
 if (!np->nchg_nd_chgstore) return;

 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 != -1)
    {
     i1 = npauxp->nbi1; 
     i2 = npauxp->nbi2.xvi;
     /* AIV 12/21/07 - if ever forced need to add change here as well */
     if (__net_chg_nd_store(np, i1, i2) || np->frc_assgn_allocated)
      {
       add_net_change(np, i1, i2, TRUE, FALSE, FALSE); 
      }
//AIV LOOKATME - could give warning here out of range ?????????
//   else __misc_terr(__FILE__, __LINE__);
    }
   else add_net_change(np, -1, -1, TRUE, FALSE, FALSE); 
  }
}

/*
 * get all net changes wire delay
 */
static void set_process_wire_ev_flag(struct mod_t *mdp, struct net_t *np)
{
 int32 ii;
 struct net_pin_t *npp;
 struct itree_t *itp;
 struct inst_t *ip;
 struct mod_t *downmdp;
 struct expr_t *lhsx, *xp;
 struct gate_t *gp;

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp == NP_PB_MDPRT) __misc_terr(__FILE__, __LINE__);
   if (npp->npntyp == NP_PB_ICONN) __misc_terr(__FILE__, __LINE__);
//AIV HERE - what about range??????
/*-----------------
   if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 != -1)
    {
     i1 = npauxp->nbi1; 
     i2 = npauxp->nbi2.xvi;
    }
   else i1 = i2 = -1;
-------------*/

   if (npp->npntyp == NP_MDPRT)
    {
     downmdp = npp->elnpp.emdp;
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       itp = downmdp->moditps[ii];
       ip = itp->itip;
       lhsx = ip->ipins[npp->obnum];
       if (lhsx->lhsx_ndel) 
        {
         add_lhsx_netchgs(mdp, lhsx);
         break;
        }
      }
    }
   else if (npp->npntyp == NP_GATE)
    {
     gp = npp->elnpp.egp;
     xp = gp->gpins[0];
     if (xp->lhsx_ndel) 
      {
       add_lhsx_netchgs(mdp, xp);
      }
    }
  }
}

       
/*
 * add all continous assign net changes
 */
static void add_conta_netchgs(struct mod_t *mdp)
{
 int32 i, pbi;
 struct conta_t *cap, *pb_cap;

 for (i = 0; i < mdp->mcanum; i++)
  {
   cap = &(mdp->mcas[i]);
   add_lhsx_netchgs(mdp, cap->lhsx);

   if (cap->ca_pb_sim)
    {
     for (pbi = 0; pbi < cap->lhsx->szu.xclen; pbi++)
      { 
       pb_cap = &(cap->pbcau.pbcaps[pbi]);
       add_lhsx_netchgs(mdp, pb_cap->lhsx);
      }
    }
  }
}

/*
 * add a net change for one lhsx expression
 */
static void add_lhsx_netchgs(struct mod_t *mdp, struct expr_t *lhsx)
{
 struct expr_t *catndp;

 if (lhsx->getpatlhs) return;

 if (!lhsx->x_multfi && !lhsx->lhsx_ndel) return;

 /* handle the concat case */
 if (lhsx->optyp == LCB) 
  {
   catndp = lhsx->ru.x;
   for (; catndp != NULL; catndp = catndp->ru.x)
    { 
     add_one_lhsx_netchgs(mdp, catndp->lu.x, lhsx->x_multfi, lhsx->lhsx_ndel);
    }
   return;
  }
 add_one_lhsx_netchgs(mdp, lhsx, lhsx->x_multfi, lhsx->lhsx_ndel);
}
       
/*
 * add net changes for one lhsx 
 */
static void add_one_lhsx_netchgs(struct mod_t *mdp, struct expr_t *lhsx,
 int32 has_mfi, int32 has_del)
{
 struct expr_t *idndp;
 struct net_t *np;
 int32 bi;
 
 if (has_mfi)
  {
   idndp = __get_lvalue_idndp(lhsx);
   np = idndp->lu.sy->el.enp;

   if (np->nrngrep == NX_DWIR)
    {
     if (!np->n_isavec)
      {
       add_net_change(np, -1, -1, TRUE, TRUE, FALSE); 
       return;
      }
     for (bi = 0; bi < np->nwid; bi++)
      {
       add_net_change(np, bi, bi, TRUE, TRUE, FALSE); 
      }
    }  
   return;
  }

 if (has_del) 
  {
   idndp = __get_lvalue_idndp(lhsx);
   np = idndp->lu.sy->el.enp;
   if (!np->n_isavec)
    {
     add_net_change(np, -1, -1, TRUE, TRUE, FALSE); 
     return;
    }
   for (bi = 0; bi < np->nwid; bi++)
    {
     add_net_change(np, bi, bi, TRUE, TRUE, FALSE); 
    }
  }
}
   
/*
 * add net changes for a procedural statments
 */
static void add_proc_stmt_netchgs(struct mod_t *mdp)
{
 int32 i;
 struct st_t *stp;
 struct expr_t *lhsx;
 struct tskcall_t *tkcp;
 struct sy_t *syp;
 struct sysfunc_t *sfbp;
 struct expr_t *tkxp, *xp;
 struct task_t *tskp;
 struct task_pin_t *tpp;
 struct net_t *np;


 for (i = 0; i < mdp->prov_mstnum; i++) 
  {
   stp = mdp->prov_mstndx[i];
   switch ((byte) stp->stmttyp) {
    case S_INC:
    case S_DEC:
    case S_FORASSGN:
    case S_PROCA:
    case S_RHSDEPROCA:
     lhsx = stp->st.spra.lhsx;
     add_lhsx_to_netchg_lst(lhsx, FALSE, FALSE);
     break;
    case S_NBPROCA:
     lhsx = stp->st.spra.lhsx;
     add_lhsx_to_netchg_lst(lhsx, FALSE, TRUE);
     break;
    case S_FUNCCALL:
    case S_TSKCALL:
     tkcp = &(stp->st.stkc);
     tkxp = tkcp->tsksyx;
     syp = tkxp->lu.sy;
     /* system tasks are wrappers calls do nothing */
     /* AIV 01/26/12 - this is not true of $random could change the seed */
     /* AIV LOOKATME - other syscalls could have the same problem???? */
     if (syp->sytyp == SYM_STSK) 
      {
       sfbp = syp->el.esyftbp;
       if (sfbp->syfnum != STN_RANDOM) break;
      }
     tskp = syp->el.etskp;
     tpp = tskp->tskpins;
     for (xp = tkcp->targs; xp != NULL; xp = xp->ru.x, tpp = tpp->tpnxt)
      {
       if (tpp->trtyp == IO_IN) continue;
       np = tpp->tpsy->el.enp;
       if (!np->nchg_nd_chgstore) continue;
       lhsx = xp->lu.x;
       add_lhsx_to_netchg_lst(lhsx, FALSE, FALSE);
      }
     break;
    case S_QCONTA:
     lhsx = stp->st.sqca->qclhsx;
     add_lhsx_to_netchg_lst(lhsx, FALSE, FALSE);
     break;
    case S_QCONTDEA:
     lhsx = stp->st.sqcdea.qcdalhs; 
     add_lhsx_to_netchg_lst(lhsx, FALSE, FALSE);
     break;
   }
  }
}

/*
 * add procedural lhsx net changes
 */
static void add_lhsx_to_netchg_lst(struct expr_t *lhsx, int32 is_wire_ev,
 int32 is_nb_stmt)
{
 struct net_t *np;
 struct expr_t *idndp, *ndx1, *ndx; 
 int32 ri1, ri2, biti, is_const_expr;

 switch (lhsx->optyp) {
  case GLBREF:
  case ID:
   np = lhsx->lu.sy->el.enp;
   if (np->nchg_nd_chgstore) 
    {
     add_net_change(np, -1, -1, TRUE, is_wire_ev, FALSE); 
    }
   break;
  case LSB:
   idndp = lhsx->lu.x;
   ndx1 = lhsx->ru.x;
   np = idndp->lu.sy->el.enp;
   
   if (!np->nchg_nd_chgstore) break;

   __const_expr_has_isnums = FALSE; 
   /* AIV 03/06/08 - if constant expression has IS number cannot use */
   /* fixed net change must use the variable case */
   is_const_expr = __is_const_expr(ndx1);
   if (__const_expr_has_isnums)
    is_const_expr = FALSE;
   ndx = ndx1->next_ndx;
  
   /* AIV 03/31/09 - was not adding constant nchg for first dimension */
   /* for a select off of the constant first index */
   /* array2[3][6:4] = 4'b1101; */
   if (is_const_expr)
    {
     biti = __comp_ndx(np, ndx1);
     if (!__net_chg_nd_store(np, biti, biti)) break;
     add_net_change(np, biti, biti, TRUE, is_wire_ev, FALSE); 
    }

   /* AIV 08/13/08 - for multi dim arrays if any indices have variable index */
   /* then it cannot be constant */
   if (is_const_expr)
    {
     while (ndx != NULL)
      {
       is_const_expr = __is_const_expr(ndx);
       if (!is_const_expr) break;
       if (__const_expr_has_isnums)
        {
         is_const_expr = FALSE;
         break;
        }
       ndx = ndx->next_ndx;
      }
    }

   __const_expr_has_isnums = FALSE; 
 
   if (!is_const_expr)
    {
     if (!__net_chg_nd_store(np, -1, -1)) break;
     /* AIV 11/21/07 - if lhs is a variable index of a lhs nb need to mark */
     if (is_nb_stmt) np->n_on_nblhs_varndx = TRUE;
     add_net_change(np, -1, -1, FALSE, is_wire_ev, FALSE); 
     break; 
    }
  //????? if (np->n_isarr) __assign_to_arr(np, idndp, ndx1, ap, bp);
   else
    {
     biti = __comp_ndx(np, ndx1);
     if (!__net_chg_nd_store(np, biti, biti)) break;
     add_net_change(np, biti, biti, TRUE, is_wire_ev, FALSE); 
    }
   break;
  case PARTSEL:
   idndp = lhsx->lu.x;
   np = idndp->lu.sy->el.enp;
   ri1 = (int32) __contab[lhsx->ru.x->lu.x->ru.xvi];
   ri2 = (int32) __contab[lhsx->ru.x->ru.x->ru.xvi];

   if (!np->nchg_nd_chgstore) break;

   if (!__net_chg_nd_store(np, ri1, ri2)) break;
   add_net_change(np, ri1, ri2, TRUE, is_wire_ev, FALSE); 
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   idndp = lhsx->lu.x;
   np = idndp->lu.sy->el.enp;
   ndx1 = lhsx->ru.x->lu.x;
   if (!np->nchg_nd_chgstore) break;
   /* ndx1 better be variable here otherwise should be regular psel */
   /* DBG --- */
   if (__is_const_expr(ndx1)) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   if (!__net_chg_nd_store(np, -1, -1)) break;
   /* AIV 11/21/07 - if lhs is a variable index of a lhs nb need to mark */
   if (is_nb_stmt) np->n_on_nblhs_varndx = TRUE;
   add_net_change(np, -1, -1, FALSE, is_wire_ev, FALSE); 
   break; 
  case LCB:
   add_lhsx_concat_to_netchg_lst(lhsx, is_wire_ev);
   break;
  case INC: case DEC:
   add_lhsx_to_netchg_lst(lhsx->lu.x, is_wire_ev, is_nb_stmt);
   break;
  /* AIV 07/30/12 - can have concats here which contain constants */
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * AIV 07/18/12 - add a new to the net change struct list
 */
extern void __add_net_to_netchg_lst(struct net_t *np)
{
 add_net_change(np, -1, -1, TRUE, FALSE, FALSE); 
}


/*
 * add a lhsx concat expression's net changes
 */
static void add_lhsx_concat_to_netchg_lst(struct expr_t *lhsx, int32 is_wire_ev)
{
 struct expr_t *catndp, *catlhsx;

 /* do lhs concatenate assigns from left to right */
 for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
  {
   catlhsx = catndp->lu.x;
   add_lhsx_to_netchg_lst(catlhsx, is_wire_ev, FALSE);
  }
}

/* 
 * AIV 02/03/11 - forced tran nets need to be the first net changes added
 * so that the each net change for the bit nchgs are in order.
 * 
 * AIV FIXME - this is really need because of how asl_loc_qc_tran_wireforce
 * get the next net change bit strct - see this in v_aslib.c
 * AIV PTR FIXME - don't think this is portable or good
 * take the original netchg address and get the bi's from theis address
 */
static void add_force_net_tran_changes(struct net_t *np)
{
 int32 bi;
 struct traux_t *trap;
 
 /* no tran just return */
 trap = np->ntraux;
 if (trap == NULL) return;

 /* no force return */
 if (!np->frc_assgn_allocated) return;

 /* no net change */
 if (!np->nchg_nd_chgstore) return;

 /* no a vector */
 if (!np->n_isavec) return;

 /* now add each item to the list */
 /* add net changes are now put on the front of the list so order will */
 /* be reversed as expected in v_aslib force vector wrapper */
 for (bi = 0; bi < np->nwid; bi++) 
  {
   add_net_change(np, bi, bi, TRUE, FALSE, TRUE); 
  }
}

//AIV TRAN - this needs the new vector use code
static void add_net_changes_from_tran(struct net_t *np)
{
 struct vbinfo_t *vbip;
 struct chanrec_t *chanp;
 struct traux_t *trap;
 struct bidvtx_t *bidvtxp; 
 struct net_t *np2;
 int32 vi, bi, bi2;

 trap = np->ntraux;
 if (trap == NULL) return;
 vbip = trap->vbitchans[0];
 chanp = &(__chantab[vbip->chan_id]);
 /* AIV 02/19/12 - if chan vectored can just alloc the one whole net */
 /* fixed change no reason for per bit */
 if (chanp->chan_vectored)
  {
   add_net_change(np, -1, -1, TRUE, FALSE, FALSE); 
   return;
  }

 for (bi = 0; bi < np->nwid; bi++) 
  {
   vbip = trap->vbitchans[bi];
   if (vbip != NULL)
    {
     chanp = &(__chantab[vbip->chan_id]);
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
               add_net_change(np2, bi2, bi2, TRUE, FALSE, TRUE); 
              }
            }
           else
            {
             if (__net_chg_nd_store(np2, -1, -1))
              {
               add_net_change(np2, -1, -1, TRUE, FALSE, FALSE); 
              }
            }
          }
        }
      }
    }
   if (np->n_isavec)
    {
     if (__net_chg_nd_store(np, bi, bi)) 
       add_net_change(np, bi, bi, TRUE, FALSE, TRUE); 
    }
   else if (__net_chg_nd_store(np, -1, -1))
    {
     add_net_change(np, -1, -1, TRUE, FALSE, FALSE); 
    }
  }
}
 
/*
 * allocate an compile time net change struct and link onto its net
 */
static void add_net_change(struct net_t *np, int32 i1, int32 i2, 
 int32 is_const, int32 is_wire_ev, int32 is_tran_force_vec)
{
 struct net_chg_t *ncp;

 /* check for duplicate */
//AIV - maybe skip duplicates and merge later??????
 for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
  {
   if (ncp->i1 == i1 && ncp->i2 == i2 && ncp->is_const == is_const)
    {
     /* range may share that of non-wire ev */
     if (!ncp->is_wire_ev) ncp->is_wire_ev = is_wire_ev;
     return;
    }
  }

 ncp = (struct net_chg_t *) __my_malloc(sizeof(struct net_chg_t));
 ncp->ndx = ++__nchg_ndx;
 ncp->nchg_idp_ofs = 0;
 ncp->is_wire_ev = is_wire_ev;
 ncp->i1 = i1;
 ncp->i2 = i2;
 ncp->is_const = is_const;
 ncp->wire_fgp = NULL;
 ncp->nchg_fgp = NULL;
 ncp->process_nchg_fgp = NULL;
 ncp->nxt = NULL;
 ncp->is_lowered = FALSE;
 ncp->is_printed = FALSE;
 /* AIV 06/23/09 - need to know if is a vector force need to produce special */
 /* code in assembly for wrapper codes - see v_asmlnk.c */
 ncp->is_tran_force_vec = is_tran_force_vec;

 /* AIV 02/03/12 - removed nctlp - which is the tail there is no reason to */
 /* have a tail just link on to front of the list - saves net_t space */
 if (np->nchdp == NULL)
  {
   np->nchdp = ncp;
  }
 else
  {
   ncp->nxt = np->nchdp;
   np->nchdp = ncp;
  }
}

/*
 * proc to add net chg records for net's that have nchg nd chgstore on
 * but code optimized away - must make sure net's that need a net wide
 * change even if no loads and drivers such as dumpvars and toggle coverage
 *
 * SJM 11-07-12 - FIXME!! - there are still bugs where static compiled
 * sim nchdp (net chg t) needed but not put on - this has code to add
 * and analyze - need systematic algorithm which is not just add hoc
 */
static void bld_no_lds_and_no_drvs_nchges(void)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum != 0)

   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
    {
     if (np->nchdp == NULL && np->nlds == NULL && np->ndrvs == NULL)
      {
       try_add_analyze_late_nchges(np, mdp, NULL);
      }
    }
  
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;

     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       if (np->nchdp == NULL && np->nlds == NULL && np->ndrvs == NULL)
        {
         try_add_analyze_late_nchges(np, mdp, tskp);
        }
      }
    }
  }
}

/*
 * add a late nchg that did not get added but needs to - figure out and
 * fix so added normally
 *
 * only called if no net changes
 *
 * SJM 11-07-12 - goal of this is to remove need for it.  Proc compensates
 * for bugs when no lds and no drvs
 */
static void try_add_analyze_late_nchges(struct net_t *np, struct mod_t *mdp,
 struct task_t *tskp)
{
 char s1[RECLEN];

 if (tskp != NULL) sprintf(s1, " task=%s", tskp->tsksyp->synam);
 else strcpy(s1, "");
 if (np->dmpv_in_src || np->dmpp_in_src || np->n_hasdvars
  || np->n_has_toggle)
  {
   /* add the nchg so compiler will run right */
   add_net_change(np, -1, -1, TRUE, FALSE, FALSE); 
   if (__missing_nchg_trace)
    {
     __gfwarn(4131, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
      "net %s mod=%s%s - need late nchg add: dmpv_in_src=%d, dmpp_in_src=%d, hasdvars=%d has_tgl=%d nd_chgst=%d\n",
      np->nsym->synam, mdp->msym->synam, s1, np->dmpv_in_src, np->dmpp_in_src,
      np->n_hasdvars, np->n_has_toggle, np->nchg_nd_chgstore);
    }
  }
 else
  {
   if (np->nchg_nd_chgstore && __missing_nchg_trace)
    {
     __gfwarn(4132, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
      "net %s mod=%s%s - nchg_nd_chgstore but not added: dmpv_in_src=%d, dmpp_in_src=%d, hasdvars=%d has_tgl=%d nd_chgst=%d\n",
      np->nsym->synam, mdp->msym->synam, s1, np->dmpv_in_src, np->dmpp_in_src,
      np->n_hasdvars, np->n_has_toggle, np->nchg_nd_chgstore);
    }
  }
}

/*
 * ROUTINES TO MERGE OR DELETED DUPLICATED VECTOR LOADS (NPPS)
 */

/*
 * for every vector net in every module remove/merge duplicate loads (npps)
 */
static void rm_comb_dup_lds() 
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;

 __siz_opt_npptab = 100;
 __opt_npptab = (struct npopt_t *)
  __my_malloc(__siz_opt_npptab*sizeof(struct npopt_t));

 __total_lds_removed = 0;
 __total_lds_from_nets = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum != 0)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       /* do not process duplicated for scalar nets since dups very rare */
       merge_rm_1net_ld_dups(mdp, np);
      } 
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       merge_rm_1net_ld_dups(mdp, np);
      }
    }
  }
 __my_free(__opt_npptab, __siz_opt_npptab*sizeof(struct npopt_t));
 __siz_opt_npptab = -1;
 __opt_npptab = NULL;

#ifdef __CVC_DEBUG__
 if (__debug_flg) 
  {
   if (__total_lds_removed == 0)
    {
     __cv_msg("  No overlapping or merged range loads could be removed.\n");
    }
   else
    {
     __cv_msg("  %d overlapping or merged range loads removed from %d nets.\n",
      __total_lds_removed, __total_lds_from_nets);
    }
  }
#endif
}

/*
 * merge same object duplicated or range overlapp npp's into one npp
 *
 * SJM 02/03/07 - BEWARE npps in table although still linked together so both 
 *                nxt field and table indexing possible - if chg must rebld
 */
static void merge_rm_1net_ld_dups(struct mod_t *mdp, struct net_t *np)
{
 int32 nppi;
 int32 nppi2, i1, i2, num_npps, last_grp_nppi;
 size_t osize, nsize;
 int32 has_chgable_npp, some_npp_rmdel;
 struct npopt_t *npp_optp, *npp_optp2;
 struct net_pin_t *npp, *npp2;
 struct npaux_t *npauxp;

 if (np->nlds == NULL) return;
 
 num_npps = cnt_npps(np->nlds);
 if (__siz_opt_npptab < num_npps) 
  {
   osize = __siz_opt_npptab*sizeof(struct npopt_t);
   __siz_opt_npptab = 2*num_npps;
   nsize = __siz_opt_npptab*sizeof(struct npopt_t);
   __opt_npptab = (struct npopt_t *) __my_realloc(__opt_npptab, osize, nsize);
  }
 for (nppi = 0, npp = np->nlds; nppi < num_npps; nppi++, npp = npp->npnxt)
  {
   npp_optp = &(__opt_npptab[nppi]);

   npp_optp->cant_opt = FALSE;
   npp_optp->npp_processed = FALSE;
   npp_optp->opt_in_grp = FALSE;
   npp_optp->npp_del = FALSE;
   npp_optp->npp = npp;
   npp_optp->nxt_dup_nppi = -1;
   npp_optp->new_i1 = -1;
   npp_optp->new_i2 = -1;
  
   /* eliminate if must remain on npp list */
   if (!npp_can_del_or_merge(npp))
    {
     npp_optp->cant_opt = TRUE;
     continue;
    }

   /* get the ranges */
   if ((npauxp = npp->npaux) == NULL) i1 = i2 = -1;
   else { i1 = npauxp->nbi1; i2 = npauxp->nbi2.i; }
   npp_optp->new_i1 = i1;
   npp_optp->new_i2 = i2;
  }
 /* find possibly deletable or mergeable same npp groups */
 has_chgable_npp = FALSE;
 for (nppi = 0; nppi < num_npps; nppi++)
  {
   npp_optp = &(__opt_npptab[nppi]);
   if (npp_optp->cant_opt) continue;
   if (npp_optp->opt_in_grp) continue;

   npp = npp_optp->npp;
   last_grp_nppi = -1;
   for (nppi2 = nppi + 1; nppi2 < num_npps; nppi2++)
    {
     npp_optp2 = &(__opt_npptab[nppi2]);
     if (npp_optp2->opt_in_grp) continue;

     npp2 = npp_optp2->npp;
     if (npp->npntyp != npp2->npntyp) continue;
     if (!npps_same(mdp, npp, npp2)) continue;

     /* DBG --- */
     if (__debug_flg)
      {
       __dbg_msg("group npp=%p[%d:%d]\n", npp2,
        npp_optp2->new_i1, npp_optp2->new_i2);
      }
     /* --- */

     /* 02/11/07 - must insert on tail */
     if (last_grp_nppi == -1)
      {
       npp_optp->opt_in_grp = TRUE;
       npp_optp->nxt_dup_nppi = nppi2;
      }
     else __opt_npptab[last_grp_nppi].nxt_dup_nppi = nppi2;
      
     last_grp_nppi = nppi2;
     npp_optp2->opt_in_grp = TRUE; 
     has_chgable_npp = TRUE;
    }
  }
 if (has_chgable_npp)
  {
   if (np->n_isavec) some_npp_rmdel = vec_merge_rm_iconn_npps(num_npps);
   else some_npp_rmdel = scalar_rm_iconn_npps(num_npps);

   if (some_npp_rmdel) delrm_rebld_npp_list(np, num_npps);
  }
}

/*
 * count number of npps
 */
static int32 cnt_npps(struct net_pin_t *npp)
{
 int32 num_npps;

 for (num_npps = 0; npp != NULL; npp = npp->npnxt) num_npps++;
 return(num_npps);
}
 
/*
 * return F if npp is not optimizable
 * non optimizable npp typ or XMR or IS param range
 */
static int32 npp_can_del_or_merge(struct net_pin_t *npp)
{
 struct npaux_t *npauxp;

 if (npp->npproctyp != NP_PROC_INMOD) return(FALSE);

 npauxp = npp->npaux;
 if (npauxp != NULL)
  {
   if (npauxp->nbi1 == -2) return(FALSE);
  }
 /* since gate terminals 1 bit and can't be concat, don't bother with gates */
 switch (npp->npntyp) {
 case NP_PB_ICONN: case NP_PB_MDPRT:
  case NP_MIPD_NCHG: case NP_TCHG: case NP_TRANIF: 
   return(FALSE);
  case NP_ICONN: case NP_MDPRT:
   return(TRUE);
  case NP_GATE:
   /* SJM 02/17/07 - for now only 1 bit contas del/rem of npps */
   if (npp->elnpp.egp->gmsym->el.eprimp->gateid != G_ASSIGN) return(FALSE);
   break;
  case NP_CONTA:
   /* per bit concats never match */
   /* AIV 05/15/07 - per bit concat should be merged */
   /* AIV LOOKATME - why are these converted into pb in the first place ??? */
   /* if (npp->elnpp.ecap->ca_pb_sim) return(FALSE); */
   return(TRUE);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(TRUE);
}

/*
 * return T if 2 npps on a net are the same - candidates for delete/merge  
 * 
 * npp's that can't be deleted or merged never seen here
 */
static int32 npps_same(struct mod_t *mdp, struct net_pin_t *npp1,
 struct net_pin_t *npp2)
{
 int32 ii;
 struct inst_t *ip;
 struct itree_t *dritp, *dritp2;

 switch ((byte) npp1->npntyp) {
  case NP_ICONN:
   /* if not same inst number in mod's inst tab, not same npp */
   if (npp1->elnpp.eii != npp2->elnpp.eii) return(FALSE); 
   /* if not the same port, not same npp */
   if (npp1->obnum != npp2->obnum) return(FALSE);

   dritp = &(mdp->moditps[0]->in_its[npp1->elnpp.eii]);
   /* for each iconn itree loc, the down itree loc will be different but */
   /* the down mod's inst_t will be the same */
   ip = dritp->itip;
   /* SJM 02/04/07 - think some mod insts can be different, if so leave */
   /* DBG remove --- */
   for (ii = 1; ii < mdp->flatinum; ii++)
    {
     dritp2 = &(mdp->moditps[ii]->in_its[npp1->elnpp.eii]);
     if (ip != dritp2->itip) __misc_terr(__FILE__, __LINE__);
    }
   /* --- */
   return(TRUE);
  case NP_MDPRT:
   /* this is rare case of different nets connected to one port */ 
   /* the .<port>(<connection list>) explicit form */
   /* DBG remove -- */
   if (npp1->elnpp.emdp != npp2->elnpp.emdp) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* only port numbers need to match */
   if (npp1->obnum != npp2->obnum) return(FALSE);
   return(TRUE);
  case NP_CONTA:
   /* same rhs - know wide and will have complex rhs expr with dup net uses */
   if (npp1->elnpp.ecap != npp2->elnpp.ecap) return(FALSE);
   return(TRUE);
  case NP_GATE:
   /* SJM 02/17/07 - for now only 1 bit conta npp del/rem */
   /* same conta style gate's only 1 terminal, do not need term number cmp */
   if (npp1->elnpp.egp != npp2->elnpp.egp) return(FALSE);
   return(TRUE);
  default: __case_terr(__FILE__, __LINE__);
 }
 /* DBG remove -- */
 __misc_terr(__FILE__, __LINE__);
 /* --- */
 return(FALSE);
}

/*
 * routine to delete and/or merge same mod/port iconn npps for one net 
 *
 * assume npp opt record (parallel array) preprocessing done
 * only called if know has at least one changeable (removable or deletable)
 */
static int32 vec_merge_rm_iconn_npps(int32 num_npps)
{
 int32 rng_nppi, rng_nppi2;
 int32 nppi, stay_nppi, some_npp_rmdel, onebit;
 struct npopt_t *npp_optp, *npp_optp2, *npp_optp3;

 /* for every npp that is a load of current net */
 some_npp_rmdel = FALSE;
 for (nppi = 0; nppi < num_npps; nppi++)
  {
   npp_optp = &(__opt_npptab[nppi]);

   /* know lowest index npp is head of group list */
   if (!npp_optp->opt_in_grp) continue;

   /* if this one was processed from earlier group head, nothing to do */
   if (npp_optp->npp_processed) continue;

   /* case 2: if any entire net, all others are marked for later deleting */
   stay_nppi = -1;
   for (rng_nppi = nppi; rng_nppi != -1; rng_nppi = npp_optp2->nxt_dup_nppi)
    {
     npp_optp2 = &(__opt_npptab[rng_nppi]);
     if (npp_optp2->new_i1 == -1) { stay_nppi = rng_nppi; break; } 
    }
   if (stay_nppi != -1)
    {
     /* have an entire net, can remove all in group except this one */
     mark_npps_for_del(npp_optp, stay_nppi);
     some_npp_rmdel = TRUE;
     /* only need one npp - done with merge/del for this npp group */
     continue;
    }

   /* case 3: go through each npp in group marking for del and merging rnges */
   for (rng_nppi = nppi; rng_nppi != -1; rng_nppi = npp_optp2->nxt_dup_nppi)
    {
     /* notice first of equal except for bit range first one here */
     npp_optp2 = &(__opt_npptab[rng_nppi]);
     if (npp_optp2->npp_processed) continue;

     /* since going through every one in group as current, this marks all */
     npp_optp2->npp_processed = TRUE;

     /* if removed from previous pass, nothing to do */
     if (npp_optp2->npp_del) continue;

     rng_nppi2 = npp_optp2->nxt_dup_nppi;
     for (; rng_nppi2 != -1; rng_nppi2 = npp_optp3->nxt_dup_nppi)
      {
       npp_optp3 = &(__opt_npptab[rng_nppi2]);
       if (npp_optp3->npp_del) continue;

       /* DBG remove -- */
       if (npp_optp3->npp_processed) __misc_terr(__FILE__, __LINE__);
       /* --- */

       /* AIV 05/17/07 - waiting for SJM???? - this will work for now */
       /* AIV 09/18/07 - was wrong for pb for both interp and compiler */
       /* pb conta weren't working correctly in the compiler */
/////////////////AIV REMOVEME/////////////////
       onebit = npp_optp2->new_i1;
       if (onebit == npp_optp2->new_i2)
        {
         if (onebit != npp_optp3->new_i1) continue;
         if (onebit != npp_optp3->new_i2) continue;
        }
//////////////////////////////////

       /* case 3a: current contains compare to */
       if (npp_optp2->new_i1 >= npp_optp3->new_i1 &&
        npp_optp2->new_i2 <= npp_optp3->new_i2)
        {
         npp_optp3->npp_processed = TRUE;   
         npp_optp3->npp_del = TRUE;
         some_npp_rmdel = TRUE;
         continue;
        }
       /* case 3b: compare to contains current */
       if (npp_optp2->new_i1 <= npp_optp3->new_i1 &&
        npp_optp2->new_i2 >= npp_optp3->new_i2)
        {
         npp_optp2->npp_processed = TRUE;   
         npp_optp2->npp_del = TRUE;
         some_npp_rmdel = TRUE;
         goto nxt_current;
        }

       /* case 3c: disjoint */
       if (npp_optp3->new_i2 > npp_optp2->new_i1
        || npp_optp3->new_i1 < npp_optp2->new_i2)
        {
         /* case 3c-1: abut on high side */
         if (npp_optp2->new_i2 - 1 == npp_optp3->new_i1) 
          {
           npp_optp3->npp_processed = TRUE;   
           npp_optp3->npp_del = TRUE;
           some_npp_rmdel = TRUE;
           npp_optp2->new_i2 = npp_optp3->new_i2; 
           continue;
          }
         /* case 3c-2: abut on low side */
         if (npp_optp3->new_i2 - 1 == npp_optp2->new_i1) 
          {
           npp_optp3->npp_processed = TRUE;   
           npp_optp3->npp_del = TRUE;
           some_npp_rmdel = TRUE;
           npp_optp2->new_i1 = npp_optp3->new_i1; 
           continue;
          }
         /* case 3c-3: disjoint with gap - nothing to do */
         continue;
        }

       /* case 3d: overlap on high side of current */
       if (npp_optp2->new_i1 < npp_optp3->new_i1)
        {
         /* widen current high end - delete compare to */
         npp_optp2->new_i1 = npp_optp3->new_i1;
         npp_optp3->npp_processed = TRUE;   
         npp_optp3->npp_del = TRUE;
         some_npp_rmdel = TRUE;
         continue;
        }
       /* case 3e: overlap on low side of current */
       if (npp_optp2->new_i2 > npp_optp3->new_i2)
        {
         /* widen current high end - delete compare to */
         npp_optp2->new_i2 = npp_optp3->new_i2;
         npp_optp3->npp_processed = TRUE;   
         npp_optp3->npp_del = TRUE;
         some_npp_rmdel = TRUE;
         continue;
        }
       /* DBG remove -- */
       __misc_terr(__FILE__, __LINE__);
       /* --- */
      }
nxt_current:;
    }
  }
 return(some_npp_rmdel);
}

/*
 * mark all same npp's in a group except for passed for later deletion
 */
static void mark_npps_for_del(struct npopt_t *npp_optp, int32 not_del_nppi)
{
 int32 nppi;

 nppi = (npp_optp - &(__opt_npptab[0]));
 for (;;)
  {
   npp_optp = &(__opt_npptab[nppi]);
   npp_optp->npp_processed = TRUE;
   if (nppi != not_del_nppi) npp_optp->npp_del = TRUE;
   nppi = npp_optp->nxt_dup_nppi;
   if (nppi == -1) break;
  }
}

/*
 * routine to delete repeated same npp's for scalar nets
 *
 * assume npp opt record (parallel array) preprocessing done
 * only called if know has at least one changeable (removable or deletable)
 */
static int32 scalar_rm_iconn_npps(int32 num_npps)
{
 int32 nppi, some_npp_del;
 struct npopt_t *npp_optp;

 /* for every npp that is a load of current net */
 some_npp_del = FALSE;
 for (nppi = 0; nppi < num_npps; nppi++)
  {
   npp_optp = &(__opt_npptab[nppi]);

   /* if not a group of same, nothing to do */
   if (npp_optp->nxt_dup_nppi == -1) continue;

   /* have an entire net, can remove all except this one */
   mark_npps_for_del(npp_optp, nppi);
   some_npp_del = TRUE;
  }
 return(some_npp_del);
}

/*
 * ROUTINES TO MERGE ALWAYS BLOCKS ON THE SAME EDGE (DELAY CONTROLS) 
 */

/*
 * make a list of 'always @(edge)' blocks and determine which share a common
 * epxression for later merging
 *
 * if block contains no blocking delays and needs no thread mechanism
 * the blocks can be merged
 *
 * AIV FIXME - this uses n^2 operations were n is the number of always @
 * could make this a tree???? - usually the number isn't large
 */
static void merge_always_ev_dctrl(void) 
{
 struct mod_t *mdp;
 struct expr_t *xp1, *xp2;
 struct delctrl_t *dctp1, *dctp2, *last_dctp, *dctp;
 struct delctrl_t **da;
 struct ctev_t *ctevp;
 int32 dsize, i, j, has_xmr, is_eq;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
#ifdef __XPROP__
 //AIV EXPROP - PUTBACK - need to handle merge blocks for xprop
   /* AIV 02/29/08 - if compiled sim combine dces that share an edge */
   //also need to fix for xprop2
   if (mdp->m_use_xprop && !__no_xprop_edges) continue;
#endif
   /* allocate the array of delay controls */
   da = make_dctrl_event_array(mdp, &dsize);
   if (dsize == 0) continue;
   /* process last to first - to preverse souce order */
   for (i = dsize - 1; i >= 0; i--)
    {
     dctp1 = da[i];
     /* already added continue */
     if (dctp1->is_merged) continue; 
     xp1 = dctp1->dc_du.d1x;
     for (j = i-1; j >= 0; j--)
      {
       dctp2 = da[j];
       if (dctp2->is_merged) continue; 

       xp2 = dctp2->dc_du.d1x;
       /* check for the same edge expr if TRUE add */
       
       has_xmr = FALSE;
       is_eq = __cmp_xpr(xp1, xp2, &has_xmr);
       /* AIV 11/16/10 - if expr has xmr do not merge */
       if (is_eq && !has_xmr)
        {
#ifdef __CVC_DEBUG__
         if (__debug_flg)
          {
           __cv_msg("Merging delay control on expr [ %s ]\n", 
              __msgexpr_tostr(__xs, xp1));
           __cv_msg("\tAround stmt1  %s and stmt2  %s\n", 
              __bld_lineloc(__xs, dctp1->actionst->stfnam_ind, 
                dctp1->actionst->stlin_cnt), 
              __bld_lineloc(__xs2, dctp2->actionst->stfnam_ind, 
                dctp2->actionst->stlin_cnt));
          }
#endif
         dctp2->is_merged = TRUE;
         /* if first one this is the header - used for merge fg */
         if (dctp1->merged_dctp == NULL)
          {
           dctp1->merged_dctp = dctp2;
           /* DBG remove --- */
           if (dctp1->head_ctevp != NULL) __misc_terr(__FILE__, __LINE__);
           /* ----- */
           /* alloc new merged fg tev */
           ctevp = alloc_ctev(dctp1->dc_du, dctp1->dc_delrep, mdp, FALSE); 
           ctevp->dctrl_ndx = ++__dctrl_seq_no; 
           dctp1->head_ctevp = ctevp; 
          }
         else
          {
           /* add to the end of the list */
           dctp = dctp1->merged_dctp; 
           for (; dctp != NULL; dctp = dctp->merged_dctp)
            last_dctp = dctp;
           last_dctp->merged_dctp = dctp2;
          }
         dctp2->head_dctp = dctp1;
        }
      }
    }
   /* save the modules delay control info */
   mdp->dctrl_array = da;
   mdp->dctrl_size = dsize;
  }
}

/*
 * allocate an array of delay controls
 * if dctrl has been marked with a nested blocking delay do not add to 
 * the array
 */
static struct delctrl_t **make_dctrl_event_array(struct mod_t *mdp, 
 int32 *dsize)
{
 struct delctrl_t **da;
 struct delctrl_t *dctp;
 struct dcevnt_t *dcep;
 struct net_t *np;
 int32 ni, count; 
 size_t size, osize, nsize;

 count = 0;
 size = 128;
 da = (struct delctrl_t **) __my_malloc(size*sizeof(struct delctrl_t **));
 /* check all nets for delctrls and add to the array */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
  {
   for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
    {
     dctp = dcep->st_dctrl;
     if (dctp == NULL) continue;
     /* not always or nested do not add to the array */
     if (dctp->dctyp != DC_EVENT || !dctp->is_always) continue;
#ifdef __CVC_DEBUG__
     if (dctp->nested_dctrl)
      {
       if (__debug_flg)
        {
         __cv_msg(
          "Delay control - contains blocking dctrl[ %s ]\n", 
           __bld_lineloc(__xs, dctp->actionst->stfnam_ind, 
             dctp->actionst->stlin_cnt));
        }
      }
#endif
     if (dctp->nested_dctrl) continue;
     /* don't add duplicates */
     if (is_dctrl_in_array(dctp, da, count)) continue;
     /* grow the array */
     if (count == size)
      {
       osize = size*sizeof(struct delctrl_t *);
       size *= 2;
       nsize = size*sizeof(struct delctrl_t *);
       da = (struct delctrl_t **) __my_realloc(da, osize, nsize);
      }
     da[count] = dctp;
     count++;
    }
  }
 *dsize = count;
 return(da);
}
       
/*
 * return TRUE if dctp is already in the array
 *
 * AIV FIXME - this uses n^2 operations were n is the number of always @
 * could make this a tree???? - usually the number isn't large
 */
static int32 is_dctrl_in_array(struct delctrl_t *dctp, struct delctrl_t **da, 
 int32 count)
{
 int32 i;

 for (i = 0; i < count; i++)
  {
   if (da[i] == dctp) return(TRUE);
  }
 return(FALSE);
}


/*
 * ROUTINES TO MERGE DCE ON THE SAME EDGE
 */

/*
 * merge all edges dces into one dcep - shared egdes
 * do through all mods=>nets=>dces attemping to merge on an edge
 */
static void merge_edge_dces(void) 
{
 struct dcevnt_t *dcep;
 struct mod_t *mdp;
 struct net_t *np;
 int32 ni, count;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
#ifdef __XPROP__
 //AIV EXPROP - PUTBACK - need to handle merge blocks for xprop
   /* AIV 02/29/08 - if compiled sim combine dces that share an edge */
   //also need to fix for xprop2
   if (mdp->m_use_xprop && !__no_xprop_edges) continue;
#endif
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
    {
     for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
      {
       /* already merge continue */
       if (dcep->merged) continue;
       /* dce doesn't contain an edge to merge */
       if (!can_merge_dce(dcep)) continue;
       count = try_merge_dces(dcep);
       if (count == 0) continue;
#ifdef __CVC_DEBUG__
       if (__debug_flg)
        {
         __cv_msg("Merging dces on net %s in mod %s total %d\n", 
         np->nsym->synam, mdp->msym->synam, count + 1);
        }
#endif
      }
    }
  }
}
       
/*
 * Start with a dce and attempt to merge it if it has an edge
 * all shared edges (posedge/negedge) will be merged into the first
 * dce.  At compile time only the first edge will be checked for.  
 * 
 * Algortihm starts with one, searching remainder of list if duplicates
 * are found they are added to the first occurence dcep's merged_dces
 * array to be used later at compilation 
 * 
 */
static int32 try_merge_dces(struct dcevnt_t *dcep)
{
 int32 edgeval, count, bi1, bi2;
 struct dcevnt_t *dcep2;
 struct dcevnt_t **combined_dceps;
     
 /* AIV 05/02/08 - if cannot merge first one just return false */
 if (!can_merge_dce(dcep)) return(FALSE);

 /* start with orginal dce edge value/bit to match */
 bi1 = dcep->dci1;
 bi2 = dcep->dci2.i;
 edgeval = dcep->dce_edgval;
 count = 0;
//AIV LOOKATME - could do one pass and expand the array dynamically????????
 /* first pass does the counting */
 for (dcep2 = dcep->dcenxt; dcep2 != NULL; dcep2 = dcep2->dcenxt)
  {
   /* AIV 05/02/08 - was checking dcep - should be dcep2 */
   /* not mergable cannot match */
   if (!can_merge_dce(dcep2)) continue;
   /* edge value must match */
   if (edgeval != dcep2->dce_edgval) continue;
   /* if has a bit must match bit as well */
   if (bi1 != dcep2->dci1 || bi2 != dcep2->dci2.i) continue;
   count++;
  }

 /* nothing to merge */
 if (!count) return(FALSE);

 /* alloc the new array for shared edges and save the count */
 combined_dceps = 
   (struct dcevnt_t **) __my_malloc(count*sizeof(struct dcevnt_t *));
 dcep->merged_dces = combined_dceps;
 dcep->merged_count = count;

 /* pass2 is the same storing the merged dces */
 count = 0;
 for (dcep2 = dcep->dcenxt; dcep2 != NULL; dcep2 = dcep2->dcenxt)
  {
   /* AIV 05/02/08 - was checking dcep - should be dcep2 */
   if (!can_merge_dce(dcep2)) continue;
   if (edgeval != dcep2->dce_edgval) continue;
   if (bi1 != dcep2->dci1 || bi2 != dcep2->dci2.i) continue;
   /* mark flag and save merged dce */
   dcep2->merged = TRUE;
   combined_dceps[count] = dcep2;
   count++;
  }
 return(count);
}

/*
 * return TRUE if dce can be merged
 */
static int32 can_merge_dce(struct dcevnt_t *dcep)
{
 struct delctrl_t *dctp;

 /* contains no edge */
 if (!dcep->dce_edge) return(FALSE);
 /* variable index case cannot be merged */
 if (dcep->dci1 == -2) return(FALSE);
 /* xmr case is not merged */
 if (dcep->dce_xmrtyp != XNP_LOC) return(FALSE);
 /* no expression */
 if (dcep->dce_expr != NULL) return(FALSE);
 /* no rep form */
 dctp = dcep->st_dctrl;
 if (dctp->repcntx != NULL) return(FALSE);

 return(TRUE);
}

/*
 * rebuild the npp tab (and list) 
 *
 * npp's are tab but also last nxt field link to one index higher
 * only called if know some change to npp tab (list)
 */
static void delrm_rebld_npp_list(struct net_t *np, int32 num_npps)
{
 int32 nppi;
 int32 new_num_npps;
 struct npopt_t *npp_optp;
 struct net_pin_t *npp, *npp2, *last_npp;

 /* first count new number and update npp's that have different ranges */
 new_num_npps = 0;
 for (nppi = 0; nppi < num_npps; nppi++)
  {
   npp_optp = &(__opt_npptab[nppi]);
   if (npp_optp->npp_del) continue;
   new_num_npps++;
   if (npp_optp->cant_opt) continue;
   npp = npp_optp->npp;
   if (npp->npaux == NULL) continue;

   if (npp_optp->new_i1 == np->nwid - 1 && npp_optp->new_i2 == 0)
    {
     npp_optp->new_i1 = npp_optp->new_i2 = -1;
    }

   if (npp_optp->new_i1 != npp->npaux->nbi1)
    {
     npp->npaux->nbi1 = npp_optp->new_i1;
    }
   if (npp_optp->new_i2 != npp->npaux->nbi2.i)
    {
     npp->npaux->nbi2.i = npp_optp->new_i2;
    }
  }

 /* DBG remove --- */
 if (new_num_npps == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 last_npp = NULL;
 for ( nppi = 0, npp = np->nlds; nppi < num_npps; nppi++)
  {
   npp_optp = &(__opt_npptab[nppi]);
   if (npp_optp->npp_del)
    {
     /* remove this npp from list */
     if (npp->npaux != NULL)
      {
       __my_free(npp->npaux, sizeof(struct npaux_t));
       npp->npaux = NULL; 
      }
     npp2 = npp->npnxt;
     __my_free(npp, sizeof(struct net_pin_t));
     if (last_npp == NULL) np->nlds = npp2; else last_npp->npnxt = npp2;
     /* for remove, do not update last npp */
     npp = npp2;
    }
   else
    {
     last_npp = npp;
     npp = npp->npnxt;
    }
  }

 /* DBG remove -- */
 if (num_npps == new_num_npps) __misc_terr(__FILE__, __LINE__);
 /* --- */

 __total_lds_removed += (num_npps - new_num_npps);
 __total_lds_from_nets++;
/* SJM - REMOVED FOR RELEASE
 if (__verbose)
  {
   if (np->n_isavec) 
    {
     __cv_msg("### Module %s net %s[%d:0]: now %d loads reduced from %d\n",
      mdp->msym->synam,  np->nsym->synam, np->nwid - 1, new_num_npps,
      num_npps);
    }
   else
    {
     __cv_msg("### Module %s net %s: now %d loads reduced from %d\n",
      mdp->msym->synam,  np->nsym->synam, new_num_npps, num_npps);
    }
  }
--- */
}

/*
 * ROUTINES TO BLD FIXED LOCATION (AT LEAST LAB) KNOWN AT COMPILE TIME EVENTS
 */

/*
 * build all time events for each module
 */
static void bld_all_time_events(void)
{
 struct mod_t *mdp;
   
 __nb_const_last_time = 0xffffffffffffffffULL;
 __all_nb_same_time = -1;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* build all proc time events */
   bld_all_proc_time_events(mdp);
   /* build all continous assign events */
   bld_conta_time_events(mdp);
   /* build all gate delay events */
   bld_gate_time_events(mdp);
   /* build all wire delay events */
   bld_wire_ev_time_events(mdp);
  }
}


/*
 * build all proc time events
 */
static void bld_all_proc_time_events(struct mod_t *mdp)
{
 int32 i;
 union del_u del;
 struct st_t *stp;

 del.d1v = NULL;
 for (i = 0; i < mdp->prov_mstnum; i++) 
  {
   stp = mdp->prov_mstndx[i];
   switch ((byte) stp->stmttyp) {
    case S_DELCTRL:
     add_dctl_stmt_event(stp, mdp);
     break;
    case S_NBPROCA:
     /* this may already be added if <= has delay */
     /* SJM 07/11/08 - must init to dt none, can't be -1, causes case terr */
//SJM 10-16-11 - not del nil here, but ok since DT_NONE type
     if (stp->ctevp == NULL) stp->ctevp = alloc_ctev(del, DT_NONE, mdp, FALSE); 
     break;
    case S_WAIT:
     /* DBG remove -- */
     if (stp->ctevp != NULL) __misc_terr(__FILE__, __LINE__);
     /* -- */
     stp->ctevp = alloc_ctev(del, DT_NONE, mdp, FALSE); 
     break;
    case S_REPDCSETUP:
     /* DBG remove -- */
     if (stp->ctevp != NULL) __misc_terr(__FILE__, __LINE__);
     /* -- */
     stp->ctevp = alloc_ctev(del, DT_NONE, mdp, FALSE); 
     break;
   }
  }
}

/*
 * add a delay control event 
 */
static void add_dctl_stmt_event(struct st_t *stp, struct mod_t *mdp)
{
 struct delctrl_t *dctp;
 struct st_t *nxtstp;
 struct ctev_t *ctevp;
 word64 nbdel;
 int32 is_const;

 dctp = stp->st.sdc;
 nxtstp = dctp->actionst;

 switch (dctp->dctyp) {
  case DC_DELAY: case DC_EVENT:
   /* AIV 03/03/09 - if is the merged always block header need */
   /* merged block event */
   if (dctp->head_dctp != NULL || dctp->merged_dctp != NULL) 
    {
     if (dctp->head_dctp != NULL) dctp = dctp->head_dctp;
     ctevp = dctp->head_ctevp;
     /* DBG remove -- */
     if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
    }
   stp->ctevp = alloc_ctev(dctp->dc_du, dctp->dc_delrep, mdp, FALSE); 
   break;
  case DC_RHSDELAY:
  case DC_RHSEVENT:
   ctevp = alloc_ctev(dctp->dc_du, dctp->dc_delrep, mdp, FALSE); 
   /* AIV 11/30/09 - if nb check if all <= #delays are the same value */
   if (nxtstp->stmttyp == S_NBPROCA) 
    {
     is_const = __check_delay_constant(dctp->dc_du, dctp->dc_delrep, &(nbdel));
     //AIV LOOKATME #0 can count as well????
     /* if not constant false, -1 first value scene, false if any not eq */
     if (!is_const)
      {
       __all_nb_same_time = FALSE;
      }
     else if (__all_nb_same_time == -1)
      {
       __nb_const_last_time = nbdel;
       __all_nb_same_time = TRUE;
      }
     else if (__all_nb_same_time)
      {
       if (nbdel != __nb_const_last_time)
        {
         __all_nb_same_time = FALSE;
        }
      }
     nxtstp->ctevp = ctevp;
    }
   else stp->ctevp = ctevp;
   break;
 }
}

/*
 * add a continous assign delay time event
 */
static void bld_conta_time_events(struct mod_t *mdp)
{
 int32 i;
 struct expr_t *catndp, *lhsx, *catlhsx;
 struct conta_t *cap;

 for (i = 0; i < mdp->mcanum; i++)
  {
   cap = &(mdp->mcas[i]);
   lhsx = cap->lhsx;
   if (lhsx->getpatlhs) continue;

   if (cap->ca_delrep != DT_NONE) 
    {
     /* DBG remove -- */
     if (cap->ca_pb_sim) __misc_terr(__FILE__, __LINE__);
     if (cap->ctevp != NULL) __misc_terr(__FILE__, __LINE__);
     /* -- */
     cap->ctevp = alloc_ctev(cap->ca_du, cap->ca_delrep, mdp, FALSE); 
    }

   if (lhsx->lhsx_ndel) 
    {
     if (lhsx->optyp == LCB) 
      {
       catndp = lhsx->ru.x;
       for (; catndp != NULL; catndp = catndp->ru.x)
        { 
         catlhsx = catndp->lu.x;
         bld_lhsx_time_events(catlhsx, mdp);
        }
      }
     else 
      {
       bld_lhsx_time_events(lhsx, mdp);
      }
    }
  }
}

/*
 * add a continous assign delay time event for each lhsx
 */
static void bld_lhsx_time_events(struct expr_t *lhsx, struct mod_t *mdp)
{
 int32 bi;
 struct expr_t *idndp;
 struct net_t *np;
 struct ctev_t **tmp_ndel_ctevtab;
 struct rngdwir_t *dwirp; 

 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;

 if (np->ndel_ctevtab != NULL) return;

 dwirp = np->nu.rngdwir;
 tmp_ndel_ctevtab = (struct ctev_t **)
  __my_malloc(np->nwid*sizeof(struct ctev_t *));
 if (np->n_isavec)
  {
   for (bi = 0; bi < np->nwid; bi++)
    {
     add_net_change(np, bi, bi, TRUE, TRUE, FALSE); 
     tmp_ndel_ctevtab[bi] = alloc_ctev(dwirp->n_du, dwirp->n_delrep, mdp,
      TRUE); 
    }
  }
 else 
  {
   tmp_ndel_ctevtab[0] = alloc_ctev(dwirp->n_du, dwirp->n_delrep, mdp, TRUE); 
  }
 np->ndel_ctevtab = tmp_ndel_ctevtab;
}
   
/*
 * add a wire delay time event
 */
static void bld_wire_ev_time_events(struct mod_t *mdp)
{
 int32 ni, ii, i;
 struct net_pin_t *npp;
 struct expr_t *lhsx, *catndp, *catlhsx;
 struct mod_t *downmdp, *upmdp;
 struct itree_t *itp;
 struct inst_t *ip;
 struct net_t *np;
 struct mipd_t *mipdp;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
//AIV pb now illegal
     if (npp->npntyp == NP_PB_MDPRT) __misc_terr(__FILE__, __LINE__);
     if (npp->npntyp == NP_PB_ICONN) __misc_terr(__FILE__, __LINE__);
     if (npp->npntyp == NP_MDPRT)
      {
       downmdp = npp->elnpp.emdp;
       /* AIV 10/04/07 - need to check if any instance has lhsx_ndel */
       for (ii = 0; ii < downmdp->flatinum; ii++)
        {
         itp = downmdp->moditps[ii];
         ip = itp->itip;
         lhsx = ip->ipins[npp->obnum];
         upmdp = itp->up_it->itip->imsym->el.emdp;
         /* AIV 05/04/11 - need to handle concat as special case here */
         if (lhsx->lhsx_ndel) 
          {
           if (lhsx->optyp == LCB) 
            {
             catndp = lhsx->ru.x;
             for (; catndp != NULL; catndp = catndp->ru.x)
              { 
               catlhsx = catndp->lu.x;
               bld_lhsx_time_events(catlhsx, upmdp);
              }
            }
           else 
            {
             bld_lhsx_time_events(lhsx, upmdp);
            }
          }
        }
      }
     else if (npp->npntyp == NP_MIPD_NCHG)
      {
       if (np->n_isavec) 
        {
         np->ndel_ctevtab = 
          (struct ctev_t **) __my_malloc(np->nwid*sizeof(struct ctev_t *)); 
         for (i = 0; i < np->nwid; i++)
          {
           /* AIV 12/28/11 - these need to have an nchg for each bit */
           /* the linking code is expecting one for each bit - was getting */
           /* misc terr */
           add_net_change(np, i, i, TRUE, FALSE, FALSE); 
           mipdp = &(np->nlds->elnpp.emipdbits[i]);
           np->ndel_ctevtab[i] = alloc_ctev(mipdp->pb_mipd_du, 
            mipdp->pb_mipd_delrep, mdp, FALSE); 
          }
        }
       else
        {
         mipdp = &(np->nlds->elnpp.emipdbits[0]);
         np->ndel_ctevtab = 
          (struct ctev_t **) __my_malloc(sizeof(struct ctev_t *)); 
         np->ndel_ctevtab[0] = alloc_ctev(mipdp->pb_mipd_du, 
           mipdp->pb_mipd_delrep, mdp, FALSE); 
        }
      }
    }
  }
}
   
/*
 * add a gate delay time event
 */
static void bld_gate_time_events(struct mod_t *mdp)
{
 int32 gi;
 struct gate_t *gp;
 struct expr_t *xp;

 for (gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);

   /* pull gate (really source) has no state or scheduled events */
   /* no state for trans */ 
   if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN) continue;

   /* if output unc. (OPEMPTY), changes are not seen (do not propagate) */
   if (gp->g_class != GC_TRANIF && gp->gpins[0]->optyp == OPEMPTY)
    continue;

   if (gp->g_delrep != DT_NONE) 
    {
     /* DBG remove -- */
     if (gp->ctevp != NULL) __misc_terr(__FILE__, __LINE__);
     /* -- */
     gp->ctevp = alloc_ctev(gp->g_du, gp->g_delrep, mdp, FALSE); 
    }

   xp = gp->gpins[0];
   if (xp->lhsx_ndel) 
    {
     bld_lhsx_time_events(xp, mdp);
    }
  }
}
   
/*
 * allocate a compile time event used for compilation
 */
static struct ctev_t *alloc_ctev(union del_u du, int32 del_rep, 
 struct mod_t *mdp, int32 wire_ev)
{
 struct ctev_t *ctevp;

 ctevp = (struct ctev_t *) __my_malloc(sizeof(struct ctev_t));
 ctevp->has_wire_ev = wire_ev;
 ctevp->wrapper_type = WRAPPER_NONE;
 ctevp->ct_comlab_typ = COMLAB_NONE;
 ctevp->in_list = FALSE;
 ctevp->del_rep = del_rep;

 ctevp->mdp = mdp;
 ctevp->ct_el_ndx = -1;
 if (del_rep == DT_NONE) ctevp->du.d1v = NULL;
 else ctevp->du = du;
 ctevp->nb_fg_num = -1;
 ctevp->ctev_idp_ofs = 0;
 ctevp->path_ndx = -1;
 ctevp->ctev_ndx = __ctev_ndx++;
 ctevp->ca_ndx = -1;
 ctevp->wev_ndx = -1;
 ctevp->dctrl_ndx = -1;
 ctevp->ctev_gp = NULL;
 ctevp->nb_rhs_byt_size = -1;
 ctevp->srep = SR_UNKN;
 ctevp->ctevnxt = NULL;
 return(ctevp);
}

/*
 * ROUTINES TO PREP ALLOC AND INIT PER INST IDP AREA (NOT JUST FOR VARS NOW) 
 */

/*
 * routine to assign idp area offset - now last step before init sim
 * this is the prep of the idp area (often copies from n.l.) that
 * must be last step in prep 
 *
 * BEWARE first step in idp prep is handling sdf elaboraration so sdf
 * can't use idp
 *
 * SJM 08-08-07 - moving net and idp location offset assigning to last
 * prep sim step
 */
static void prep_idp_area(void)
{
 struct mod_t *mdp;

 /* SJM 08-07-07 - need provisional mst tab until final one blt in xform */ 
 __bld_provisional_mstabs();

 /* notice advantage of option is allows use in initialization */
 /* assumes called from first top level module */ 
 if (__sdflst != NULL)
  {
   __process_sdf_files();
   if (__pv_err_cnt != 0) return;
  }

 if (__sdftskenlst != NULL && !__sdf_during_sim)
  {
   __process_sdf_tskenables();
   if (__pv_err_cnt != 0) return;
  }
 
 /* build the compile time net changes and time events */
 if (__compiled_sim) 
  {
   bld_all_netchanges(); 
   bld_all_time_events();
   /* SJM 11-07-12 - new code that tries to avoid nchges for constants */
   /* does not work at least for no ld/nl drv dumpvars need routine to fix */
   /* up and emit warnings if old (and used by interpreter) nchg nd chgstore */
   /* bit set */
   bld_no_lds_and_no_drvs_nchges();
  }

 /* calculate variable (net) sizes and set start offset for every mod */  
 __set_all_mods_1inst_storage_offsets();

 /* AIV 08/20/09 - made changes so compiler no longer needs to alloc */
 /* and init __idp area (mod_idata) */
 /* allocate storage for wire and regs (variables) and gate states */
 /* if CVC compiled sim storage is linked in and init later */
 //AIV IDP FIXME - need to make idp storage area in *.so storage area
 if (__compiled_sim) 
  {
   if (__running_cvc_exe)
    {
     __alloc_compiled_sim_storage();
    }
  }
 else __alloc_sim_storage();

 /* AIV 07/12/07 - init nets now need to be separated from the alloc */
 /* the init values for the nets now depends on drivers and npps are now */
 /* filtered by the matching idp so these need to be separated out */
 if (__compiled_sim) 
  {
   if (__running_cvc_exe) __init_compiled_sim_storage();
  }
 else __init_sim_storage();

 /* SJM 04-23-13 - new initialize toggle processed here - idp area now */
 /* allocated and initialized - this sets starting tgl coverage from */
 /* previous run take from previously written .tgldat file(s) */
 if (__tgldat_infils_lst_hd != NULL)
  {
   if (__compiled_sim)
    {
     if (__running_cvc_exe) __rd_set_from_tgldat_toggled();
    }
   else __rd_set_from_tgldat_toggled();
  }
 

 /* final step - after idp locations know fixup npp and dce fields */
 /* that were originally set to itp to idp now that idp mechanism built */
 /* AIV 08/19/09 - if compiling do not do conversion here */
 /* compiler no longer can use idp areas */
 if (__compiled_sim)
  {
   if (__running_cvc_exe) fixup_idps_where_used_itp();
  }
 else fixup_idps_where_used_itp();

 /* SJM 07/19/02 - need to prep specify to add tchk and path loads */
 /* before setting nchg action bits */
 /* SJM 05/05/05 - since using new nchgbtab for per inst nchg bytes */
 /* must always initialize the nchg action bits here */
 /* notice all event control dces added by here */
 /* AIV 08/14/07 - must now set nchgaction init afer idp area because */
 /* nchaction is now stored in idp */
 if (__compiled_sim)
  {
   if (__running_cvc_exe) __init_idp_nchgaction();
  }
 else __init_idp_nchgaction();

 if (__debug_flg && !__compiled_sim)
  {
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    __dmpmod_nplst(mdp, FALSE); 
  }

 /* when compiling show vars can't be run since it val not yet alloced */ 
 if (!__compiled_sim)
  {
   if (__debug_flg) __show_allvars();
  }
}


/*
 * ROUTINES TO ASSIGN ELEMENT ID NUMBERS AND BLD INDEXES
 */

/*
 * assign idnum and bld indices
 *
 * this is almost last step of prep (idp area bld after) - for now the
 * various indices are only used by CVC but now build for interpreter too
 * since want to be able to change algorithms and saves some duplicated
 * design statistics code
 */
static void assgn_idnums_and_bld_indices(void)
{
 struct udp_t *udpp;
 int32 nxt_mdi, nxt_tski, nxt_udpi;
 struct mod_t *mdp; 
 struct task_t *tskp;

 nxt_mdi = nxt_tski = nxt_udpi = -1;

 count_mods();
 __dsgn_mod_ndx = (struct mod_t **)
  __my_malloc(__dsgn_num_mods*sizeof(struct mod_t *));

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   mdp->m_idnum = ++nxt_mdi;
   __dsgn_mod_ndx[mdp->m_idnum] = mdp;
   nxt_tski = -1;

   /* notice tsk id numbers are design wide */
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt) 
    {
     tskp->t_idnum = ++nxt_tski;
    }
   if (mdp->mspfy != NULL) bld_1mod_specify_pth_ndx(mdp);
   bld_1mod_npp_ndx(mdp);
  }
 
 count_udps();
 if (__dsgn_num_udps == 0) return;

 __dsgn_udp_ndx = (struct udp_t **)
  __my_malloc(__dsgn_num_udps*sizeof(struct udp_t *));

 __dsgn_num_udps = 0;
 for (udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
  {
   udpp->u_idnum = ++nxt_udpi;
   __dsgn_udp_ndx[udpp->u_idnum] = udpp;
  }
}

/*
 * count number of modules and top modules in design
 */
static void count_mods(void)
{
 struct mod_t *mdp;

 /* AIV 08/24/11 - this routine no longers counts __numtopm and */
 /* can no longer set the value since some may be linked out */
 /* DBG remove */
 if (__numtopm == 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 __dsgn_num_mods = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __dsgn_num_mods++;
  }
}

/*
 * count number of udps in design
 */
static void count_udps(void)
{
 struct udp_t *udpp;

 __dsgn_num_udps = 0;
 for (udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
  {
   __dsgn_num_udps++;
  }
}

/*
 * build the specify path ndx for every specify delay in a module
 *
 * SJM 08/01/08 - FIXME - should put this in specify record - save some mem
 */
static void bld_1mod_specify_pth_ndx(struct mod_t *mdp)
{
 struct spcpth_t *pthp;
 int32 nxt_pthi;

 nxt_pthi = -1;
 for (pthp = mdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
  {
   pthp->spcpth_id = ++nxt_pthi;
  }
 if (nxt_pthi < 0) return;

 mdp->mpthnum = nxt_pthi + 1;
 mdp->m_pth_ndx = (struct spcpth_t **)
  __my_malloc(mdp->mpthnum*sizeof(struct spcpth_t *));
 for (pthp = mdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
  {
   mdp->m_pth_ndx[pthp->spcpth_id] = pthp;
  }
}

/*
 * bld npp index for one module - indices (tables) are per mod not per dsgn
 */ 
static void bld_1mod_npp_ndx(struct mod_t *mdp)
{
 struct net_pin_t *npp;
 struct net_t *np;
 int32 ni, num_npps, npp_nxti;

 num_npps = count_1mod_npps(mdp);
 if (num_npps == 0) return;

 mdp->mnppnum = num_npps;
 mdp->m_npp_ndx = (struct net_pin_t **)
  __my_malloc(num_npps*sizeof(struct net_pin_t *));

 npp_nxti = -1;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
     npp->npp_idnum = ++npp_nxti;
     mdp->m_npp_ndx[npp->npp_idnum] = npp;
    }
   for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
    {
     npp->npp_idnum = ++npp_nxti;
     mdp->m_npp_ndx[npp->npp_idnum] = npp;
    }
  }
}
 
/*
 * count number of udps in one module
 *
 * SJM 08/01/08 - think need per mod npp indices for eventual model compiler
 * but could have maybe simpler design wide npp index
 */
static int32 count_1mod_npps(struct mod_t *mdp) 
{
 struct net_pin_t *npp;
 struct net_t *np;
 int32 ni, npp_cnt;

 npp_cnt = 0;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    npp_cnt++;
   for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
    npp_cnt++;
  }
 return(npp_cnt);
}

/*
 * ROUTINES TO EXEC AND COPY-FIXUP-PREP CONST FUNC IF NEEDED AND EXEC IT
 */

/*
 * first time exec const func in const context need to copy and then run
 * do minimal amount of nl fixup and prep
 *
 * SJM 02-08-09 - FIXME? - think there is a minor problem with this algorithm
 * namely when exprs are checked in chk task body stmt, the exprs will be
 * folded using current value of parameter - need way to turn off folding
 */
extern struct xstk_t *__setup_and_exec_const_func(struct expr_t *ndp)
{
 struct xstk_t *xsp;
 struct sy_t *fsyp;
 struct task_t *tskp, *confp;
 t_midat *sav_idp;

 fsyp = NULL;
 /* SJM 02-19-09 - now using proc to access forward const func symbs */
 if (ndp->lu.x->optyp == GLBREF)
  {
   if ((fsyp = __get_forw_funcdef_sy(ndp->lu.x, TRUE)) == NULL) 
    __misc_terr(__FILE__, __LINE__);
  } 
 else if (ndp->lu.x->optyp == ID) fsyp = ndp->lu.x->lu.sy;
 else __case_terr(__FILE__, __LINE__);

 tskp = fsyp->el.etskp;

 /* SJM 02-18-09 - even if syntax error - try to do as much checking and */
 /* eval as possible - since can't exec, just reutnr x here */
 if (!tskp->is_con_func)
  {
   /* DBG remove */
   if (__pv_err_cnt == 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   push_xstk_(xsp, ndp->szu.xclen);
   set_regtox_(xsp->ap, xsp->bp, ndp->szu.xclen);
   return(xsp);
  }

 /* first time execed - elaborate, after that just reinit vars */
 if (tskp->cfu.to_exec_confunc == NULL)
  {
   __copy_fixup_prep_exec_const_func(tskp);
   confp = tskp->cfu.to_exec_confunc;
  }
 else
  {
   /* have already elaborated once, but params may have changed */
   /* SJM 02-08-09 - idea is that every time during elaboration when */
   /* new param values are possible, the mark is inced */
   confp = tskp->cfu.to_exec_confunc;
   /* DBG remove --- */
   if (confp->cfu.cf_auxp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
  }

 /* SJM 02-08-09 - semantics for conct funcs is no persistence - all vars */ 
 /* are set to x each time a const func is executed */
 init_all_confunc_vars(confp);
 
 /* SJM 02-18-09 - LOOKATME - think idp should always be left as nil */
 sav_idp = __idp; 
 __idp = confp->cfu.cf_auxp->conf_idata;
 xsp = __exec_const_func(ndp);
 __idp = sav_idp;
 return(xsp);
}

/*
 * routine to on demand copy-fixup-prep a constant function if needed
 * and exec it
 *
 * SJM 02-07-09 - if already elaborated and do not need to elaborate again,
 * not called
 */
extern void __copy_fixup_prep_exec_const_func(struct task_t *tskp)
{
 struct conf_aux_t *cfauxp;
 struct task_t *confp;
 t_midat *idp;

 /* DBG reomve -- */
 if (tskp->cfu.to_exec_confunc != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* copy func body - new task (func) name uses con$$ prefix */
 /* SJM 03-20-09 - image copying works because know all expr's access */ 
 /* only local to con func copied sym tables so spltsy always set */
 __confunc_copying = TRUE;
 tskp->cfu.to_exec_confunc = __image_copy_confunc(tskp);
 __confunc_copying = FALSE;

 confp = tskp->cfu.to_exec_confunc;
 confp->is_cp_conf_image = TRUE;

 confp->cfu.cf_auxp = (struct conf_aux_t *)
  __my_malloc(sizeof(struct conf_aux_t));
 cfauxp = confp->cfu.cf_auxp;
 cfauxp->conf_idata = 0;
 cfauxp->conf_idata_siz = 0;
   
 __chg_task_prms_to_tab(confp);
 
 /* convert con funcs vars to tab form and set decl ranges and chk */
 confp->trnum = count_tskvars(confp);
 __chk_taskvars(confp, -1);
 
 /* check function definition args and stmts - steps form v fixup */ 
 /* if body declares variables they are local to stmt's labeled blk */
 __chk_funcdef(confp);

 /* minimal amount of prep needed so can exec func at elaborate time */
 prep_confunc_stmts(confp);

 /* now can allocate the idp area */
 idp = (t_midat *) __my_malloc(__nxt_ofs*WRDBYTES);
 /* 0's for now - every time execed must set wire values to initial val */
 memset(idp, 0, __nxt_ofs*WRDBYTES);
 /* initialize the low fixed idp area as much as possible */
//SJM? - 02-09-09 - how should these be set????
 idp[MD_INUM] = 0;
 /* AIV 03/25/09 - need to set MD_MDP - needed for prep stmts */
 idp[MD_MDP] = (t_midat) __inst_mod;
 idp[MD_ITP] = -1;
 idp[MD_UPIDP] = 0;
 idp[MD_DOWNITPS] = 0;
 idp[MD_DPIP] = -1;

 cfauxp->conf_idata = idp;
 cfauxp->conf_idata_siz = __nxt_ofs;
}

/*
 * count number of variables in task - can only use symbol tab to count here
 */
static int32 count_tskvars(struct task_t *tskp)
{
 int32 nnum, syi;
 struct symtab_t *sytp;
 struct sy_t *syp, **syms;
 struct net_t *np;

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
 return(nnum);
}

/*
 * prep minimum amount to eval a const function bodies during elaborate
 */
static void prep_confunc_stmts(struct task_t *confp)
{
 int32 ni, sav_cur_declobj;
 struct net_t *np;

 sav_cur_declobj = __cur_declobj;
 __cur_declobj = TASK; 
 __processing_func = TRUE;

 /* prep all nets - set the idp nva ofs but does not alloc idp area */
 if (confp->trnum != 0)
  {
   for (ni = 0, np = &(confp->tsk_regs[0]); ni < confp->trnum; ni++, np++)
    {
     emit_varunused_informs(np, confp);
     set_optim_nflds(np, FALSE);
     rt_change_rngrep(np); 
     __set_1net_srep(np);
    }
  }

 /* prep list of stmts for interp - do not need xform */
 __prpsti = 0;
 __nbsti = -1;
 __prpstk[0] = NULL;
 confp->tskst = __prep_lstofsts(confp->tskst, FALSE, FALSE);
 /* DBG remove --- */ 
 if (__prpsti != 0) __misc_terr(__FILE__, __LINE__); 
 /* --- */

 /* these routine set idp ofs (nva_ofs) and update __nxt ofs global */
 /* nxt ofs is in words */
 __nxt_ofs = IDP_HD_WOFS;
 /* extra confunc prep - assign repeat stmt idp areas and remove sys tasks */
 extra_confunc_prep(confp);

 if (confp->trnum != 0)
  {
   for (ni = 0, np = &(confp->tsk_regs[0]); ni < confp->trnum; ni++, np++)
    {
     /* no declarative in functions so do not need nchg action idp slots */
     __set_1var_net_ofs(np, __inst_mod);
    }
  }
 __processing_func = FALSE;
 __cur_declobj = sav_cur_declobj;
}

/*
 * extra prep for confunc statements
 *
 * assigns repeat idp area offset and removes system tasks
 *
 * SJM 02-06-09 - new con func specific routine allows flexibility in making
 * confuncs execute as pre nl fixup point - not sure what else needed but
 * can go here
 */
static void extra_confunc_prep(struct task_t *confp)
{
 extra_confunc_prep_stlst(confp->tskst);
}


/*
 * extra prep confunc stmts
 *
 * SJM 02-07-09 - does two things - set repeat idp ofs and converts any
 * system task enable to a nil (st none) stmt
 */
static void extra_confunc_prep_stmt(struct st_t *stp)
{
 struct for_t *frp;
 struct st_t *nxtstp;
 struct tskcall_t *tkcp;
 struct sy_t *syp;

 if (stp == NULL) return;

 switch ((byte) stp->stmttyp) {
  case S_INC: case S_DEC:
  case S_NULL: case S_STNONE: break;
  case S_PROCA: case S_FORASSGN: 
   break;
  case S_IF:
   extra_confunc_prep_stmt(stp->st.sif.thenst);
   extra_confunc_prep_stmt(stp->st.sif.elsest);
   break;
  case S_CASE:
   /* this also frees default: (maybe just place holder) and list els */
   extra_confunc_prep_csitemlst(stp->st.scs.csitems);
#ifdef __XPROP__
   /* AIV 08/02/11 - now might have xprop list to process as well */
   if (stp->st.scs.xprop_lstp != NULL)
     extra_confunc_prep_stlst(stp->st.scs.xprop_lstp);
#endif
   break;
  case S_REPEAT:
   stp->st.srpt.reptmp_ofs = __nxt_ofs;
   __nxt_ofs++;
   extra_confunc_prep_stlst(stp->st.srpt.repst);
   break;
  case S_FOREVER:
  case S_WHILE:
  case S_DO_WHILE:
   extra_confunc_prep_stlst(stp->st.swh.lpst);
   break;
  case S_FOR:
   frp = stp->st.sfor;
   /* notice for assign already freed */
   extra_confunc_prep_stlst(frp->forinc);
   extra_confunc_prep_stlst(frp->forbody);
   break;
  case S_UNBLK:
   extra_confunc_prep_stlst(stp->st.sbsts);
   break;
  case S_FUNCCALL:
  case S_TSKCALL:
   /* here must change any system task call to place holder st none stmt */
   tkcp = &(stp->st.stkc);
   syp = tkcp->tsksyx->lu.sy;
   if (syp->sytyp != SYM_STSK) break;
   /* task call stmt has arg expr - get rid of it since not execed */
   __free_xtree(stp->st.stkc.targs);
   nxtstp = stp->stnxt;
   __init_stmt(stp, S_STNONE);
   stp->stnxt = nxtstp;
   break;
  case S_DSABLE:
   break;
  /* statement added for execution */
  case S_REPSETUP:
   break;
  case S_CONTINUE: case S_BREAK: case S_RETURN: break;
  case S_GOTO: break;
  /* notice named block non freeable (at least for now) */
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * extra prep confunc stmt list
 */
static void extra_confunc_prep_stlst(struct st_t *hdstp)
{
 struct st_t *stp;

 for (stp = hdstp; stp != NULL; stp = stp->stnxt)
  {
   extra_confunc_prep_stmt(stp);    
  }  
}

/*
 * extra prep for case item list
 */
static void extra_confunc_prep_csitemlst(struct csitem_t *csip)
{
 for (;csip != NULL; csip = csip->csinxt)
  {
   /* if no default, stmt of first nil */
   if (csip->csist != NULL) extra_confunc_prep_stmt(csip->csist);
  }
}

/*
 * routine to initialize all task variables
 *
 * SJM 02-07-09 - called as first step in exec of const function every
 * time called - needed because con funcs variables do not persist like
 * sim time functions
 *
 * this routine needs __idp to be set
 * func arguments and return value (var with same name as func) all inited here
 */
static void init_all_confunc_vars(struct task_t *confp) 
{
 int32 ni;
 struct net_t *np;
 t_midat *sav_idp;

 if (confp->trnum == 0) return;

 sav_idp = __idp; 
 __idp = confp->cfu.cf_auxp->conf_idata;
 for (ni = 0, np = &(confp->tsk_regs[0]); ni < confp->trnum; ni++, np++)
  {
   /* no declarative in functions so do not need nchg action idp slots */
   __init_var(np);
  }
 __idp = sav_idp;
}
