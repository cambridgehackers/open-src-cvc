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
 * compiler declarative flow graph vinsn routines plus all conversion gen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <dlfcn.h> 
#include <unistd.h> 
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

/* local prototypes */
static int32 gen_ndst_expr_eval(struct expr_t *);
static int32 gen_get_stwire_addr(struct net_t *, struct gref_t *);
static int32 gen_access_stbsel(struct expr_t *);
static int32 gen_access_stbsel_const(struct expr_t *, int32);
static int32 gen_access_stpsel(struct expr_t *);
static int32 rhs_stconcat(struct expr_t *); 
static void bld_1net_ldcomb_multfi_flowg(struct net_t *);
static void bld_1net_trpthdst_flowgs(struct net_t *);
static void bld_1net_trpthdst_1bit_flowg(struct net_t *, int32, int32);
static void gen_tran_1bit(struct net_t *, int32, int32, int32); 
static void gen_tran_1net_vectored(struct net_t *, int32, int32, 
 struct chanrec_t *);
static void gen_eval_tran_bits(struct net_t *, struct traux_t *, int32, int32, 
  int32, int32, int32);
static int32 get_tran_id(struct traux_t *, int32, int32);
static void add_flowg_to_netfg_list(struct net_t *, struct flowg_t *);
static int32 gen_load_mdrwire_subr(struct net_t *);
static int32 need_npp_downinst_push(int32);
static void gen_ldcomb_1_drvr(int32, struct net_t *, struct net_pin_t *,
 int32, int32);
static void gen_drvr_competition_upd(int32, int32, struct net_t *,
 struct net_pin_t *);
static void gen_drvr_competition_upd_2state(int32, int32, struct net_t *,
 struct net_pin_t *);
static int32 gen_stload_mdrwire_subr(struct net_t *);
static void gen_dce_flowg(struct net_t *);
static int32 gen_1net_wakeup_insns(struct net_t *, int32, int32, int32, int32);
static void gen_1dce_trigger_insns(struct net_t *, struct dcevnt_t *,
 struct bblk_t *, int32, int32);
static void gen_dce_inst(struct net_t *, struct dcevnt_t *dcep,
 struct bblk_t *, int32);
static void gen_trigger_ectrl_pnd0(int32, struct delctrl_t *);
static void gen_dce_inst_duplicates(struct net_t *, struct dcevnt_t *,
 struct bblk_t *, int32);
static void gen_decl_outofrng_tst(void *, int32, union intptr_u, 
 struct bblk_t *, int32);
static void gen_scal_filter_dce_chg(struct net_t *, struct dcevnt_t *,
 int32 *, int32 *, struct bblk_t *);
static int32 gen_filter_dce_chg(struct net_t *, struct dcevnt_t *, int32 *,
 int32 *, struct bblk_t *, struct delctrl_t *);
static int32 gen_stren_filter_dce_chg(struct net_t *, struct dcevnt_t *,
 int32 *, int32 *, struct bblk_t *, struct delctrl_t *);
static int32 gen_match_targ_to_ref(int32, struct gref_t *, struct bblk_t *);
static void gen_filter_edge_expr(struct dcevnt_t *, int32 *, int32 *,
 struct bblk_t *, struct net_t *);
static void gen_dce_monit(struct dcevnt_t *, struct bblk_t *);
static void gen_dce_off_insns(struct dcevnt_t *, struct bblk_t *);
static void gen_dce_qcaf(struct dcevnt_t *, struct bblk_t *);
static void gen_npp_flowg(struct net_t *);
static void gen_conta_flowgs(struct mod_t *);
static void gen_iconn_flowgs(struct mod_t *);
static void gen_net_chgs_flowgs(struct mod_t *);
static void gen_one_net_dumpvar_record(struct net_t *, struct bblk_t *, int32,
 int32);
static void gen_one_net_dumpport_record(struct net_t *, struct bblk_t *);
static void gen_nchg_process_wire_flowg(struct net_t *, struct net_chg_t *);
static void gen_nchg_process_wire_record(struct net_t *, int32, int32);
static void gen_nchg_process_flowg(struct net_t *, struct net_chg_t *);
static void gen_one_net_chg_const(struct net_t *, struct net_chg_t *,
 struct bblk_t *);
static void gen_one_net_chg_var(struct net_t *, struct net_chg_t *, int32, 
 struct bblk_t *);
static void gen_mipd_flowgs(struct mod_t *);
static void try_gen_mipd_flowg(struct net_t *);
static void gen_conta_one_flowgs(struct conta_t *);
static int32 gen_1net_npp_insns(struct net_t *, int32, int32, int32, int32);
static void gen_np_tranif(struct gate_t *);
static void gen_wide_logic_gate(struct gate_t *, struct net_pin_t *);
static void gen_ld_const_idp(struct itree_t *, int32 *, int32);
static void gen_np_iconn_insns(struct net_pin_t *);
static void gen_iconn(struct expr_t *, struct expr_t *, struct mod_t *, 
 struct mod_t *, int32, int32);
static void gen_one_np_iconn_flowg(struct np_iconn_t *);
static void gen_np_iconn(struct expr_t *, struct expr_t *, 
 struct itree_t *, struct itree_t *, int32, int32, int32);
static int32 gen_one_to_one_port_assign(struct expr_t *, struct expr_t *, 
 int32, int32);
static int32 gen_fixed_mdata_net_loc(struct net_t *, int32);
static void gen_one_gate_conta_flowg(struct gate_conta_t *);
static void gen_gate_delay_assign_flowgs(struct mod_t *);
static void gen_gate_delay_assign(struct gate_t *);
static void gen_gate_conta_flowgs(void);
static void gen_np_mdprt_insns(struct net_pin_t *, struct bblk_t *, int32);
static void gen_np_gate_insns(struct net_pin_t *, struct bblk_t *);
static void gen_np_chg_logic_gate(struct net_pin_t *, struct bblk_t *);
static void gen_chg_logic_gate(struct net_pin_t *, struct bblk_t *);
static void gen_chg_logic_gate_1term(struct net_pin_t *, struct bblk_t *);
static void gen_chg_logic_gate_narrow(struct net_pin_t *, struct bblk_t *);
static void gen_chg_logic_gate_narrow_leaves(struct net_pin_t *, 
 struct bblk_t *); 
static void gen_prop_gatechg(struct gate_t *, int32, int32, struct bblk_t *,
 int32);
static void gen_np_chg_bufif_gate(struct net_pin_t *, struct bblk_t *);
static void gen_np_chg_bufif_gate_strdrv(struct net_pin_t *, struct bblk_t *);
static void gen_np_chg_udp_gate(struct net_pin_t *, struct bblk_t *);
static void gen_gate_stren_added_assign(struct gate_t *, struct expr_t *, 
 int32, int32);
static void gen_gate_udp_delay_assign(struct gate_t *, struct expr_t *, int32);
static void gen_np_conta(struct net_pin_t *);
static void gen_getpattern(struct conta_t *);
static void gen_np_timechg(struct net_pin_t *, struct net_t *);
static void gen_npchg_tcchk(struct net_pin_t *, int32);
static void gen_filter_bitchange(int32, size_t, int32, struct expr_t *, 
 struct bblk_t *);
static void gen_assign_simtime_to_lasttime(int32);
static void gen_np_conta_nodelay(struct conta_t *);
static void assign_conta_rhs(struct conta_t *, int32);
static void gen_1inst_np_mdprt_insns(struct net_pin_t *, struct mod_pin_t *,
 int32, struct mod_t *, int32, int32, int32);
static void gen_1inst_np_mdprt_insns_scalar_optim(struct net_pin_t *, 
 struct mod_pin_t *, struct mod_t *);
static void gen_1inst_np_mdprt_insns_optim_mixed_xpr(struct net_pin_t *, 
 struct mod_pin_t *, struct mod_t *, int32, int32, int32, int32, int32, int32,
 int32, int32);
static void gen_one_scalar_optim_mdprt_scalar(int32, int32, int32, int32, 
 int32, int32, int32, int32, int32, int32);

static int32 gen_bld_peri_basendx(struct net_pin_t *, struct mod_t *);
static void grow_jmpbasetab(int32);
static void gen_np_chg_mos_gate(struct net_pin_t *, struct bblk_t *);
static void gen_np_chg_cmos_gate(struct net_pin_t *, struct bblk_t *);
static void gen_gate_stren_assign(struct expr_t *, int32);
static void gen_conta_addstren_assgn(struct expr_t *, struct expr_t *, byte);
static void gen_delay_rhs_ca_ld(struct net_pin_t *, int32, int32); 
static void gen_schd_or_reschd_caev(int32, struct conta_t *, int32, int32);
static void gen_conta_var_assign(struct net_t *, int32);
static void gen_conta_simple_var_assign(struct net_t *, struct expr_t *,
 int32);
static void gen_conta_bit_assign(struct net_t *, int32, int32, int32, int32);
static void gen_conta_psel_assign(struct expr_t *, int32);
static void gen_decl_lhscat(struct expr_t *, int32);
static void gen_stren_decl_lhscat(struct expr_t *, int32);
static void gen_multfi_decl_lhscat(struct expr_t *);
static void gen_mdr_assgn_or_schd_insns(struct expr_t *);
static void gen_tran_drvrs(struct net_t *, int32); 
static void gen_schd_bidpthdrvrs(struct net_t *);
static void gen_stren_schd_bidpthdrvrs(struct net_t *);
static void gen_peri_chan_no_vtxs(struct net_t *, struct traux_t *, int32, 
 int32, int32);
static int32 gen_1inst_tran_chan_no_vtxs(struct net_t *, int32, int32, int32);
static int32 gen_1inst_tran_chan_no_vtxs_wrappers(struct net_t *, int32, int32, 
 int32);
static int32 gen_1inst_tran_chan_no_vtxs_inline(struct net_t *, int32, int32, 
 int32);
static void gen_tran_assign_to_vertices(struct chanrec_t *, int32, int32, 
 int32, int32);
static void gen_assign_1tran_bit(struct net_t *, int32, int32, int32);
static void gen_conta_assgn(struct expr_t *, int32);
static void gen_stren_conta_assgn(struct expr_t *, int32);
static int32 gen_chgtorefgrp(struct expr_t *, int32 *, int32);
static void gen_conta_stren_bit_assign(struct net_t *, int32, int32, int32);
static void gen_conta_stren_psel_assign(struct expr_t *, int32);
static void mark_optim_iconn_port_scalar(struct mod_t *);
static int32 mark_if_scalar_iconn_port_optim(struct net_t *);

static void gen_assign_1stmdrwire(struct net_t *, int32, int32, int32);
static void gen_assign_1mdrwire(struct net_t *, int32, int32, int32);
static int32 get_accum_init_stren(struct net_t *);
static void gen_st_ldcomb_1_drvr(int32, struct net_t *, struct net_pin_t *,
 int32, int32);
static void gen_st_drvr_competition_upd(int32, int32, struct net_t *,
 struct net_pin_t *);

static int32 gen_ld_conta_driver(struct net_pin_t *);
static int32 gen_ld_stconta_driver(struct net_pin_t *);
static int32 gen_ld_is_svec_ofset(int32, int32, int32);
static int32 gen_ld_sttfrwarg_driver(struct net_pin_t *);
static int32 gen_ld_tfrwarg_driver(struct net_pin_t *);
static int32 gen_ld_gate_driver(struct net_pin_t *);
static int32 gen_ld_stgate_driver(struct net_pin_t *);
static int32 gen_ld_iconn_up_driver(struct net_pin_t *);
static int32 gen_ld_sticonn_up_driver(struct net_pin_t *);
static int32 gen_ld_mdprt_down_driver(struct net_pin_t *, int32);
static int32 gen_ld_1inst_mdprt_down_driver(struct net_pin_t *, int32,
 struct mod_t *, struct mod_t *);
static int32 gen_ld_st1inst_mdprt_down_driver(struct net_pin_t *, int32,
 struct mod_t *, struct mod_t *);
static int32 gen_ld_stpull_driver(struct net_pin_t *);
static int32 gen_st_standval(int32, int32, byte);
static void gen_sched_conta_assign(struct expr_t *, int32);
static void gen_stren_schd_allofwire(struct net_t *, int32, int32); 

static void gen_wdel_trireg(struct net_t *, int32, int32);
static void gen_stren_scalar_schd(struct net_t *, int32, int32, int32);
static void gen_sched_scalar_1pthbit(struct net_t *, int32, int32, int32, 
 int32, int32, int32);
static void gen_sched_vector_1pthbit(struct net_t *, int32, int32, int32, 
 int32, int32, int32);
static int32 any_on_path_cond(struct pthdst_t *);
static int32 all_paths_same(struct pthdst_t *, word64 *);
static int32 is_one_path_same(union del_u, int32, word64 *);
static int32 is_path_same_delrep(struct pthdst_t *);
#ifdef __CVC32__
static int32 gen_get_path_del32(struct net_t *, int32 *, int32 *, int32, int32,
 int32, struct bblk_t *);
static int32 gen_get_path_del32_const(struct net_t *, int32 *, int32 *, int32,
 word64, int32, struct bblk_t *);
static int32 gen_get_del32(struct net_t *, int32 *, int32 *, union del_u, int32,
 int32, int32 *, int32, int32, int32);
static void gen_schedule_path_bit32(struct net_t *, struct bblk_t *, int32, 
 int32, int32, int32, int32, struct bblk_t *, int32);
#else
static int32 gen_get_path_del64(struct net_t *, int32 *, int32, int32, int32,
 struct bblk_t *);
static int32 gen_get_path_del64_const(struct net_t *, int32 *, int32, word64,
 int32, struct bblk_t *);
static int32 gen_get_del64(struct net_t *, int32 *, union del_u, int32, int32,
 int32 *, int32, int32, int32);
static void gen_schedule_path_bit64(struct net_t *, struct bblk_t *, int32, 
 int32, int32, int32, struct bblk_t *, int32);
#endif
static void gen_stren_1bit_schd(struct net_t *, int32, int32, int32, int32);
static void gen_schd_allofwire(struct net_t *, int32, int32); 
static void gen_scalar_sched(struct net_t *, int32, int32, int32);
static void gen_1bit_sched(struct net_t *, int32, int32, int32, int32);
static void gen_stren_sched_to_bit(struct net_t *, struct expr_t *, 
 struct expr_t *, int32);
static void gen_stren_sched_to_bit_const(struct net_t *, struct expr_t *, 
 int32, int32);
static void gen_sched_to_bit(struct net_t *, struct expr_t *, struct expr_t *, 
 int32);
static void gen_sched_to_bit_const(struct net_t *, struct expr_t *, int32, 
 int32);
static void gen_stren_sched_to_psel(struct expr_t *, int);
static void gen_sched_to_psel(struct expr_t *, int);
static int32 bit_has_path(struct net_t *, int32);
static void assign_bit_to_net(struct net_t *, int32, int32);
static void gen_sched_1mdrwire(struct net_t *, int32);
static int32 dcelist_needs_range(struct net_t *);
#ifdef __XPROP__
static int32 gen_has_xedge(int32, int32, int32, int32);
#endif

static int32 gen_vec_sizchg(int32, int32, int32, int32, int32);
static int32 gen_wrd_sign_sizchg(int32, int32, int32, int32);
static int32 gen_wrd_sgnxtnd_widen(int32, int32, int32, int32);
static int32 gen_wide_sizchg_widen(int32, int32, int32);
static int32 gen_vec_narrow(int32, int32, int32);
static int32 gen_narrow_new_constant(int32, int32, int32);
static int32 gen_wrd_unsigned_sizchg(int32, int32, int32, int32);
static int32 gen_widen_new_constant(int32, int32, int32);
static int32 gen_widen_new_constant_signed(int32, int32, int32, int32);
static int32 gen_wrd_unsigned_widen(int32, int32, int32, int32);
static int32 gen_vec_to_svec_cnvt(int32, int32, int32);
static int32 gen_2state_vec_to_4state(int32, int32);
static int32 gen_4state_vec_to_2state(int32, int32);
static int32 gen_cnvt_svec_to_ab(int32, int32, int32);
static int32 gen_svec_widen(int32, int32, int32);
static void gen_set_save_idp(int32, int32 *, int32);
static void gen_add_static_nchglst(int32, int32);

/* direct gen insns for new simpler virtual machine */
extern void __st_insn(int32, int32, ...);
extern int32 __move_insn(int32, int32, int32, ...);
extern int32 __move_srep_insn(int32, int32, int32, int32, int32, ...);

/* extern prototypes (maybe defined in this module) */
extern void __gen_record_const_nchg(struct net_t *, int32, int32, 
 struct bblk_t *);
extern struct net_chg_t *__find_nchg_range(struct net_t *, int32, int32);
extern void __gen_record_var_nchg(struct net_t *, int32, struct bblk_t *);
extern struct net_chg_t *__gen_netchg_addr_tn(struct net_t *, int32, 
 int32, int32, int32 *);
extern void __emit_process_mipd_nchg_ev(int32);
extern void __emit_enter_mipd(int32);
extern void __emit_process_mipd_scalar_nchg_ev(int32);
extern int32 __emit_force_active(int32, int32);

extern int32 __gen_fradr_rhs_psel(int32, int32, int32, int32, int32);  
extern void __gen_chg_st_svecval(struct net_t *, int32, int32, int32, int32);
extern int32 __gen_cnvt_srep_ifneeded(int32, int32, int32, int32, int32,
 int32);
extern int32 __get_tnwid(int32);
extern int32 __get_bpti(int32);
extern int32 __gen_to_r_cnvt(int32, int32, int32);
extern struct flowg_t *__alloc_flowg(int32);
extern struct bblk_t *__alloc_bblk(int32);
extern void __start_bblk(struct bblk_t *);
extern int32 __gen_tn(int32, int32);
extern int32 __gen_expr_eval(struct expr_t *, int32);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern int32 __cvc_is_const_expr(struct expr_t *);
extern int32 __gen_mdat_storage_area(struct mod_t *);
extern int32 __gen_scalar_operand(int32, int32);
extern word64 __get_del_inum(union del_u, word32, int32);
extern int32 __set_mark_mdprt_flags(struct net_pin_t *, int32 *, int32 *, 
 int32 *, int32 *, int32 *, int32 *, int32 *, int32 *, int32 *);

extern int32 __gen_un_bitred_and(int32, int32, int32, int32);
extern int32 __gen_un_bitred_or(int32, int32, int32);
extern int32 __gen_un_bitred_xnor_nor(int32, int32, int32);

extern int32 __gen_ld_con_isptr(void *, int32, int32);
extern int32 __gen_ld_is_svec_varadr(struct net_t *, struct gref_t *);
extern int32 __gen_ld_netbp(struct net_t *);
extern int32 __gen_ld_net_addr(struct net_t *, struct gref_t *);
extern int32 __ldvar_addr(struct net_t *, struct gref_t *);  
extern void __gen_chg_st_val(struct net_t *, int32, int32);
extern void __gen_st_val(struct net_t *, int32, int32);
extern void __gen_assgn_to_psel(struct expr_t *, int32, int32);
extern void __gen_lhsbsel_var(struct net_t *, int32, int32, int32);
extern void __gen_lhsbsel_const(struct net_t *, int32, int32, int32);
extern void __gen_chg_lhspsel(struct net_t *, int32, int32, int32, int32, 
 int32, int32);
extern void __gen_st_psel(int32, int32, int32, int32, int32);
extern void __gen_st_bsel(int32, int32, int32, int32);
extern int32 __gen_comp_ndx(struct net_t *, struct expr_t *, struct bblk_t *,
 int32);
extern int32 __gen_cnvt_ab_vec_to_scalar(int32);
extern int32 __gen_cnvt_ab_vec_to_scalar_2state(int32);
extern int32 __gen_rhs_bsel_var(struct net_t *, int32, int32); 
extern int32 __gen_rhs_bsel_scalar_var(struct net_t *, int32, int32);
extern int32 __gen_rhs_bsel_const(struct net_t *, int32, int32); 
extern int32 __gen_rhs_bsel_scalar_const(struct net_t *, int32, int32);
extern int32 __gen_arrsel_const(struct net_t *, int32, int32, struct gref_t *);
extern int32 __any_stren_tn(int32);
extern int32 __any_scalar_tn(int32);
extern int32 __get_comp_num_ndx(struct expr_t *);

extern int32 __gen_stmt_tn(struct st_t *);
extern int32 __gen_gref_tn(struct gref_t *);
extern int32 __gen_gate_adr_tn(struct gate_t *);
extern int32 __gen_gatebp_tn(struct gate_t *, int32);
extern int32 __gen_ca_tn(struct conta_t *);
extern int32 __ld_netadr_tn(struct net_t *);
extern int32 __gen_npp_adr_tn(struct net_pin_t *);
extern int32 __gen_dce_adr_tn(struct dcevnt_t *);
extern int32 __gen_dctrl_rep_bp(struct delctrl_t *);
extern int32 __gen_dce_expr_bp(struct dcevnt_t *);
extern int32 __gen_conta_schbp_tn(struct conta_t *, int32);
extern int32 __gen_conta_drvbp_tn(struct conta_t *, int32);
extern int32 __gen_dce_prevval_tn(struct dcevnt_t *, int32);
extern int32 __gen_cint_tn(word32);
extern int32 __gen_contab_tn(int32, int32, int32, int32, int32, int32);  
extern int32 __con_adradd_insn(int32, int32, int32, size_t);
extern int32 __var_adradd_insn(int32, int32, int32, int32);
extern struct np_iconn_t *__add_np_iconn_expr(struct net_pin_t *, 
 struct expr_t *);
extern struct gate_conta_t *__add_gate_expr(struct gate_t *, 
 struct net_pin_t *);
extern struct itree_t *__find_unrt_targitp(struct gref_t *, struct itree_t *,
 int32);
extern int32 __gen_ld_xmr_idp(struct gref_t *);
extern void __gen_restore_idp(int32);
extern int32 __gen_gate_output_value(struct gate_t *, int32);
extern int32 __gen_ctevp_adr_tn(struct ctev_t *);
extern int32 __gen_gate_enter_adr_tn(struct gate_t *);
extern int32 __gen_gate_change_enter_adr_tn(struct gate_t *);
extern int32 __gen_gate_acc_change_enter_adr_tn(struct gate_t *);
extern int32 __needs_netchg_record(struct net_t *);
extern void __gen_tran_1net(struct net_t *, int32, int32);

/* emit routines to gen insn */
extern void __emit_schd_caev(int32, int32);
extern void __emit_cancel_ev(int32);
extern int32 __emit_calc_bufif_newstate(int32, int32, int32);
extern void __emit_eval_nmos_gate(int32);
extern void __emit_eval_rnmos_gate(int32);
extern void __emit_eval_pmos_gate(int32);
extern void __emit_eval_rpmos_gate(int32);
extern int32 __emit_eval_cmos_gate(int32, int32, int32, int32);
extern int32 __emit_eval_rcmos_gate(int32, int32, int32, int32);
extern int32 __gen_l_udp_table(struct udp_t *);
extern int32 __gen_e_udp_table(struct udp_t *);
extern int32 __emit_udp_wide_adjust_state(int32, int32);
extern void __set_widconta_new_gateval(int32);
extern void __emit_set_new_gateval(int32);
extern void __emit_set_old_gateval(int32);
extern void __emit_set_new_inval(int32);
extern void __emit_stren_schd_1gev(int32, int32);
extern void __emit_schd_1gev(int32, int32);
extern void __emit_schd_1gev_const(int32);
extern void __emit_schd_1gev_pnd0(int32);
extern int32 __emit_cancele_pend_nochg_1gev(int32, int32);
extern void __emit_chg_gate_outwire(int32);
extern int32 __emit_cancele_pend_chg_1gev(int32, int32);
extern void __emit_pend_nochg_1gev(int32);
extern void __emit_stren_pend_chg_1gev(int32, int32);
extern void __emit_pend_chg_1gev(int32, int32);
extern void __emit_pend_chg_1gev_const(int32);
extern void __emit_reschd_caev(int32, int32);
extern void __emit_reschd_caev_const(int32, word64);
extern void __emit_schd_caev_const(int32, word64);
extern void __emit_copy(int32, int32, int32);
extern void __emit_sxtnd_widwdn(int32, int32, int32, int32, int32);
extern int32 __emit_movw_fr_r(int32);
extern int32 __emit_movw_fr_r_2state(int32);
extern int32 __emit_movw_fr_scal(int32, int32, int32);
extern int32 __emit_movw_2s_fr_scal(int32, int32, int32);
extern int32 __emit_movint_fr_svec(int32);
extern int32 __emit_movabw_fr_svec(int32, int32);
extern int32 __emit_movabw_fr_sgnsv(int32, int32);
extern int32 __emit_movr_fr_w(int32);
extern int32 __emit_movr_fr_sgnw(int32);
extern int32 __emit_movsb_fr_scalstad(int32, int32);
extern int32 __emit_movsb_fr_wstad(int32, int32, int32);
extern int32 __emit_movsb_fr_widestad(int32, int32, int32);
extern int32 __emit_scalar_wire_inhibit(int32);
extern int32 __emit_bsel_wirfrc_inhibit(int32, int32);
extern int32 __emit_stren_correct_frc(int32, int32);
extern int32 __emit_correct_frc(int32, int32);
extern int32 __emit_psel_correct_frc(int32, int32, int32, int32);
extern int32 __emit_stren_psel_correct_frc(int32, int32, int32, int32);
extern int32 __emit_mask_and(int32, int32);
extern int32 __emit_srep_mask_and(int32, int32, int32, int32);
extern void __emit_jmp_eq_stmask(struct bblk_t *, struct bblk_t *, int32, 
 int32);
extern int32 __emit_sub(int32, int32, int32);
extern int32 __emit_add(int32, int32, int32);
extern int32 __emit_adc(int32, int32);
extern int32 __emit_mult(int32, int32, int32);
extern int32 __emit_bin_bitand(int32, int32, int32);
extern int32 __emit_bin_bitor(int32, int32, int32);
extern int32 __emit_bin_bitxor(int32, int32, int32);
extern int32 __emit_shiftl(int32, int32, int32);
extern int32 __emit_shiftr(int32, int32, int32);
extern int32 __emit_compute_emask(struct net_t *, int32, int32, int32, int32 *);
extern void __emit_ndx_jmp(int32, struct bblk_t **, size_t);
extern void __emit_jmp(struct bblk_t *);
extern void __emit_jmp_0(struct bblk_t *, struct bblk_t *, int32);
extern void __emit_jmp_eq(struct bblk_t *, struct bblk_t *, int32, int32);
extern void __emit_jmp_eq_abpart(struct bblk_t *, struct bblk_t *, int32, 
 int32);
extern void __emit_jmp_idp_eq(struct bblk_t *, struct bblk_t *, int32);
extern void __emit_jmp_byte_eq(struct bblk_t *, struct bblk_t *, int32, int32);
extern void __emit_jmp_ptr_eq(struct bblk_t *, struct bblk_t *, int32,
 int32);
extern int32 __emit_bytecmp(int32, int32, int32);
extern int32 __emit_wordcmp(int32, int32, int32);
extern void __emit_narrow_byte_eq(int32, struct bblk_t *, struct bblk_t *,
 int32, int32);
extern void __emit_jmp_cmp(struct bblk_t *, struct bblk_t *, int32,
 int32, int32);
extern void __emit_sgnbit_on_jmp(struct bblk_t *, struct bblk_t *, int32);
extern void __emit_jmp_dce_off(struct bblk_t *, struct bblk_t *, int32);
extern int32 __gen_dce_schd_tev(struct delctrl_t *);
extern void __emit_trigger_ectrl(int32, struct delctrl_t *);
extern void __emit_event_coverage(struct delctrl_t *);
extern void __emit_nb_trigger_ectrl(int32);
extern void __emit_monit_trigger(void);
extern void __emit_fmonit_trigger(int32);
extern void __emit_assign_qcaf(int32, int32, int32);
extern void __emit_assign_qcaf_regform_concat(int32);
extern void __emit_assign_qcaf_concat(int32);
extern void __emit_assign_scalar_qcaf(int32, int32, int32);
extern void __emit_assign_qcaf_regform(int32, int32, int32);
extern int32 __emit_exec_wide_logic_gate(int32, int32, int32);
extern int32 __emit_exec_np_tranif(int32);
extern void  __emit_immed_eval_trifchan(int32);
extern int32 __gen_tchk_tn(struct chktchg_t *, int32);
extern int32 __gen_del_tn(int32, void *);
extern void __emit_timing_check_record(int32);
extern void __emit_sched_scalar_mipd(int32, int32, struct net_pin_t *);
extern void __emit_sched_vec_mipd_bit(int32, int32, int32);
extern void __emit_eval_tran_drvr_1bit(int32, int32);
extern void __emit_eval_tran_drvr_vector(int32);
extern int32 __emit_bpart_of_tran(void);
extern void __emit_eval_htran_wire_1bit(int32, int32);
extern void __emit_eval_htran_wire_1bit_nchg(int32, int32, int32);
extern void __emit_eval_htran_stwire_1bit(int32, int32);
extern void __emit_eval_htran_stwire_1bit_nchg(int32, int32, int32);
extern void __emit_eval_tran_bidchan_1bit_assign(int32);
extern void __emit_eval_tran_stbidchan_1bit_assign(int32);
extern void __emit_eval_tran_bidchan_vectored_assign(int32);
extern void __emit_eval_tran_stbidchan_vectored_assign(int32);
extern int32 __emit_eval_tran_bidchan_1bit(int32);
extern int32 __emit_eval_tran_scalar_bidchan_1bit(int32);
extern int32 __emit_eval_tran_stbidchan_1bit(int32);
extern int32 __emit_update_tran_harddrvs(int32);
extern int32 __emit_tran_addr(int32); 
extern int32 __emit_stren_schd_bidpthdrvrs(int32, int32, int32, int32, int32);
extern int32 __emit_schd_bidpthdrvrs(int32, int32, int32, int32, int32);
extern int32 __emit_schd_scalar_bidpthdrvrs(int32, int32, int32, int32, int32);
extern void __emit_store_bidpthdrvrs(int32, int32, int32);
extern int32 __emit_trpath_store(int32, int32, int32);
extern int32 __emit_trpath_scalar_store(int32, int32);
extern int32 __emit_qc_active(int32, int32);
extern void __emit_adjust_trireg(int32, int32, int32, int32);
extern void __emit_wdel_trireg_hiz(int32, int32, int32, int32, int32);
extern void __emit_stren_sched_1pthbit(int32, int32, int32, int32, int32, 
 int32);
extern void __emit_stren_sched_1wirbit(int32, int32, int32, int32, int32);
extern void __emit_sched_1pthbit(int32, int32, int32, int32, int32, int32, 
 int32);
extern void __emit_sched_1pthbit_nomsg(int32, int32, int32, int32, int32, 
 int32);
extern void __emit_sched_scalar_1pthbit(int32, int32, int32, int32, int32, 
  int32);
extern void __emit_schedule_scalar_1wev(int32);
extern void __emit_schedule_1wev(int32, int32);
#ifdef __CVC32__
extern void __emit_get_del32(int32, int32 *, int32 *, int32);
extern void __emit_reschedule_1wev32(int32, int32, int32);
#else
extern void __emit_get_del64(int32, int32 *, int32);
extern void __emit_reschedule_1wev64(int32, int32);
#endif
extern void __emit_jmp_cmp64_idp_lessthan(struct bblk_t *, struct bblk_t *,
 int32, int32, int32, int32);
extern void __emit_jmp_cmp64_gt_pdmindel(struct bblk_t *, struct bblk_t *, 
 int32, int32);
extern void __emit_jmp_cmp64_gt_pdmindel_const(struct bblk_t *, 
 struct bblk_t *, int32, int32);
extern void __emit_jmp_cmp64_newdel_lte_simtim(struct bblk_t *,
 struct bblk_t *, int32, int32);
extern void __emit_sched_1wirbit(int32, int32, int32, int32, int32);
extern void __emit_stren_sched_unknown_bit(int32, int32, int32, int32, int32);
extern void __emit_sched_unknown_bit(int32, int32, int32);
extern int32 __emit_todowniconn_inst(int32);
extern int32 __emit_toupmdprt_inst(void);
extern int32 __emit_ld_tfwarg_drvp(int32, int32, int32);
extern void __emit_get_perinst_val(int32, int32, int32);
extern int32 __emit_ld_logic_wide_driver(int32, int32);
extern void __emit_stren_comb_bits(int32, int32, int32, int32, int32, int32);
extern void __emit_comb_1w_nonstren(int32, int32, int32, int32);
extern void __emit_comb_wide_nonstren(int32, int32, int32, struct net_t *,
 int32);
extern int32 __emit_stren_map_tab(int32);
extern int32 __emit_call_ldcomb_drvrs(struct net_t *, int32, struct mod_t *);
extern void __emit_set_dce_rng(int32, int32, int32); 
extern void __emit_exec_enter_dce(struct net_t *);
extern int32 __emit_ld_nchg_bptr(struct net_t *);
extern void __emit_add_dmpvlst(int32);
extern void __emit_add_dmpvlst_array(int32, int32);
extern void __emit_add_dmpportlst(int32);
extern void __emit_add_dmpvlst_mdprt(int32);
extern void __emit_add_dmpportlst_mdprt(int32);
extern void __emit_add_togglelst_el(int32);
extern void __emit_add_togglelst_el_port(int32);
extern void __emit_store_cint(int32, int32, int32);
extern void __emit_setall1(int32, int32);
extern void __emit_setstren(int32, int32, int32);
extern void __emit_setr0(int32);
extern void __emit_complete(void);
extern void __emit_next_event(void);
extern void __emit_next_nchg_event(void);
extern void __emit_enter_decl(struct net_t *);
extern void __emit_enter_npp(struct net_t *);
extern void __emit_multfi_subr(int32, struct net_t *, struct mod_t *);
extern void __emit_enter_conta(int32);
extern void __emit_enter_gate_delay_assign(int32);
extern void __emit_enter_iconn(int32);
extern void __emit_enter_gate_conta(int32);
extern void __emit_call_conta(struct conta_t *);
extern void __emit_call_iconn(int32);
extern void __emit_call_gate_conta(int32);
extern int32 __emit_save_arg(void);
extern void __copy_arg(int32, int32, int32);
extern int32 __emit_mask_and(int32, int32);
extern int32 __emit_mask_or(int32, int32);
extern void __emit_chk_dce_cbvc(int32);
extern void __emit_chk_ld_vpiputv_driver(int32, int32);
extern void __emit_chk_gate_vpi_chg(int32);
extern int32 __emit_downrel_targ_to_ref(int32);
extern int32 __emit_uprel_targ_to_ref(int32);
extern void __emit_rhs_conta_stren(int32, int32, int32);
extern int32 __emit_inum(void);
extern void __memloc_emit_set_idp(int32);
extern int32 __emit_save_cur_idp(void);
extern int32 __emit_ld_gate_val_from_tev(int32, int32);
extern int32 __ld_nchg_var_ndx(void);
extern void __emit_add_static_nchglst_sel(int32, int32, int32);
extern int32 __gen_process_nchg(struct net_chg_t *);
extern int32 __gen_process_nchg_to_reg_tn(struct net_chg_t *);
extern int32 __gen_nchg_trigger(int32);
extern int32 __gen_mipd_enter_adr_tn(int32);
extern int32 __gen_process_wire_enter(int32);
extern void __gen_proc_id_assign(struct net_t *, int32);
extern void __emit_process_enter_net_chg(int32);
extern void __emit_process_enter_wire_ev(int32);
extern void __emit_process_trpthdst_enter(int32);
extern int32 __gen_ctevp_trigger_flag(int32);
extern int32 __gen_mdata_value(struct itree_t *);
extern void __emit_call_mdprt_bsel(int32, int32, int32, int32);
extern void __emit_call_mdprt_bsel_nchg(int32, int32, int32, int32, int32);
extern void __emit_call_mdprt_bsel_dmpv(int32, int32, int32, int32, int32, 
  int32);
extern void __emit_call_mdprt_bsel_nchg_dmpv(int32, int32, int32, int32, 
 int32, int32, int32);
extern int32 __emit_bitnot(int32, int32);
extern void __emit_4state_vec_to_2state_wide(int32, int32, int32);
extern int32 __emit_new_narrow_word(int32, int32, int32);
#ifdef __XPROP__
extern void __emit_trigger_ectrl_xprop(int32, struct delctrl_t *, int32);
extern void __emit_set_tev_enter_adr_xprop(int32, int32);
extern int32 __emit_has_xedge_wide(int32, int32, int32);
extern int32 __emit_has_xedge_wide_st(int32, int32, int32);
extern int32 __gen_proc_enter_adr_tn(struct st_t *);
extern void __emit_xprop_set_xedge_net(struct st_t *, struct net_t *, int32);
extern int32 __needs_xedge_net_record(struct delctrl_t *);
extern void __emit_testl(int32);
extern void __emit_st_sete(int32, int32);
extern int32 __emit_get_xprop_tev(struct st_t *);
extern void  __emit_set_xprop_tev(struct st_t *);
#endif

extern void __grow_ndxjmpbbtab(size_t);

/* extern routines mostly defined in other files */
extern int32 __gate_needs_output_word(int32);
extern int32 __net_chg_nd_store(struct net_t *, int32, int32);
extern struct expr_t *__get_lvalue_idndp(struct expr_t *);
extern char *__my_malloc(size_t);
extern void __my_free(void *, size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern int32 __cnt_cat_size(struct expr_t *);
extern int32 __get_dcewid(struct dcevnt_t *, struct net_t *);
extern void __xmrpush_refgrp_to_targ_compiletime(struct gref_t *);
extern int32 __same_size(int32 , int32);
extern int32 __check_delay_constant(union del_u, int32, word64 *);
extern struct avlnode_t **__linearize_avl_tree(struct avlhd_t *, int32 *);
extern void __get_qc_wirrng_comptime(struct expr_t *, struct net_t **, 
 int32 *, int32 *);
extern struct sy_t *__get_nets_containing_sy(struct net_t *, struct mod_t **);
extern int32 __get_con_adradd_xvi(int32);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern int32 __isleaf(struct expr_t *);
extern int32 __get_lhs_srep(struct expr_t *, int32 *);
extern int32 __is_constant(int32);
extern int32 __tmp_is_2state(int32);
extern int32 __is_expr_2state(struct expr_t *);
extern void __asl_sgn_xtnd_widen(word32 *, word32 *, int32, int32);
extern int32 __gen_duplicate_tmp(int32);
extern double __cnvt_stk_to_real(struct xstk_t *, int32);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern int32 __alloc_shareable_rlcval(double);

extern void __my_fprintf(FILE *, char *, ...);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);

extern const word32 __masktab[];
extern const word32 __cap_to_stren[];
extern const word32 __pow3tab[];
extern const byte __stren_map_tab[];
extern const int32 __bufif_base_tab[];

/*
 * ROUTINES TO GENERATE RECORD NET CHG VINSNS
 */

/*
 * gen vinsn to record constant (literal) nchg 
 * i1 can be a tmp name (bi ti var bit sel) but then must be bit select
 *
 * intermediate form of inline - calling wrappers for test/add still
 * same for select/non select since index is constant in machine insn
 */
extern void __gen_record_const_nchg(struct net_t *np, int32 i1, int32 i2, 
 struct bblk_t *after_bbp)
{
 struct net_chg_t *ncp;

 ncp = __find_nchg_range(np, i1, i2);

 /* AIV - no reason to make this a seperate flow graph for now - inlining */
 // __emit_exec_call_nchg_fg(ncp->ndx, -1);
 gen_one_net_chg_const(np, ncp, after_bbp);
}

/*
 * gen vinsn to record variable nchg (i.e.
 * i1 can be a tmp name (bi ti var bit sel) but then must be bit select
 *
 * intermediate form of inline - calling wrappers for test/add still
 * same for select/non select since index is constant in machine insn
 */
extern void __gen_record_var_nchg(struct net_t *np, int32 bi_ti, 
 struct bblk_t *after_bbp)
{
 struct net_chg_t *ncp;

 ncp = __find_nchg_range(np, -1, -1);
 /* AIV - no reason to make this a seperate flow graph for now - inlining */
 // __emit_exec_call_nchg_fg(ncp->ndx, -1);
 gen_one_net_chg_var(np, ncp, bi_ti, after_bbp);
}

/*
 * return TRUE if np dce list needs to set ranges prior to calling dce execute
 * code
 */
static int32 dcelist_needs_range(struct net_t *np)
{
 struct dcevnt_t *dcep;
   
 /* know if net is scalar never need range */
 if (np->srep == SR_SCAL || np->srep == SR_SSCAL || np->srep == SR_SCAL2S)
  return(FALSE);

 /* check entire list if any use range return TRUE */
 for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt) 
  {
   switch ((byte) dcep->dce_typ) {
    case DCE_RNG_INST: return(TRUE);
    case DCE_INST: continue;
    case DCE_RNG_MONIT: return(TRUE);
    case DCE_MONIT: continue;
    case DCE_RNG_QCAF: return(TRUE);
    case DCE_QCAF: continue;
    /* AIV 02/19/07 - no pli currently compiled in at compile time */
    case DCE_RNG_PVC:
    case DCE_PVC:
    case DCE_RNG_CBVC:
     __case_terr(__FILE__, __LINE__);
     break;
    case DCE_CBF: case DCE_RNG_CBF: case DCE_CBR: case DCE_RNG_CBR:
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 /* no range types found in list return false */
 return(FALSE);
}

/*
 * ROUTINES TO GENERATE DECLARATIVE PRE LOWERING PER NET FLOW GRAPHS
 */

/*
 * gen pre lowering decl insns for one mod's declararative operations 
 *
 * since just building the basic blocks, any order works
 */
extern void __bld_mod_decl_flowgraphs(struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct task_t *tskp;

 /* LOOKATME - does this runs in any instance of mod? */
 __push_itstk(mdp->moditps[0]);
 /* AIV 07/09/09 - if not inlining code mark scalar-to-scalar ports */
 /* for later fixed code creating - this saves large amounts of memory */
 /* for large gate designs with large number of NP_ICONN */ 
 if (!__inline_code)
  {
   mark_optim_iconn_port_scalar(mdp);
  }

 /* first gen one long vinsn list for every net in mod */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   /* for regs first gen all dces as one separate flow grap and then */
   /* npps as one separate flow graph */

   /* SJM 06/24/04 - FIXME - must be simpler way to test this */
   if ((np->nchg_nd_chgstore || np->nchg_has_dces || np->monit_in_src
    || np->dmpv_in_src || np->dmpp_in_src) && np->dcelst != NULL)
     {
      gen_dce_flowg(np);
     }
   if (np->nlds != NULL) gen_npp_flowg(np);

   /* only wires can have mfi subroutines */
   /* can generate subroutine after npp's because just subroutines and */
   /* know mfi entry label index set for all net in all mods before here */
   /* AIV 01/04/10 - if no drivers no need to create fg */
   if (np->ntyp < NONWIRE_ST && (np->n_multfi || np->cc_need_multfi)
       && np->ntraux == NULL && np->ndrvs != NULL)
     { 
      bld_1net_ldcomb_multfi_flowg(np);
     }
   /* AIV 11/19/07 - if has tran chan and bid with path need mfi fg */
   /* and backend __process_trpthdst_ev flow graphs */
   if (np->ntraux != NULL && np->iotyp == IO_BID && np->n_isapthdst && 
       np->ndrvs != NULL)
    {
     bld_1net_ldcomb_multfi_flowg(np);
     bld_1net_trpthdst_flowgs(np);
    }
  }

 /* regs in tasks can require net chg processing too but always */
 /* separate flowgs */
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     /* only chg form regs with a dce list have separate dce insn section */
     /* SJM 06/24/04 - FIXME - must be simpler way to test this */
     if ((np->nchg_nd_chgstore || np->nchg_has_dces || np->monit_in_src
      || np->dmpv_in_src) && np->dcelst != NULL)
      {
       gen_dce_flowg(np);
       gen_npp_flowg(np);
      }
    }
  }
 /* SJM 08-21-07 - BEWARE must gen the dce and npp processing flow graphs */
 /* before here, since these routines may need to call them */

 /* generate continuous assign flow graphs */
 gen_conta_flowgs(mdp);
 /* AIV 10/06/08 - if code is inlined don't need the flow graph */
 if (!__inline_code)
  {
   /* generate iconn flow graphs */
   gen_iconn_flowgs(mdp);
   /* generate gate conta (scalar ca) flow graphs */
   gen_gate_conta_flowgs();
  }

 /* generate backend gate (gates with delays) assign value flow graphs */
 gen_gate_delay_assign_flowgs(mdp);

 /* generate flor graphs for backend mipd handling */
 gen_mipd_flowgs(mdp);

 /* generate flow graph for the net chgs */
 gen_net_chgs_flowgs(mdp);

 __pop_itstk();
}
 
/*
 * mark each net if all nlds are just scalar to scalar NP_ICONNS
 */
static void mark_optim_iconn_port_scalar(struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct task_t *tskp;

 /* first gen one long vinsn list for every net in mod */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   mark_if_scalar_iconn_port_optim(np);
  }
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     mark_if_scalar_iconn_port_optim(np);
    }
  }
}

/*
 * mark each net if all nlds are just scalar to scalar NP_ICONNS
 * sets np->is_iconn_port_scalar_opt if can be simple assign
 */
static int32 mark_if_scalar_iconn_port_optim(struct net_t *np)
{
 struct expr_t *down_lhsx, *up_rhsx;
 struct itree_t *itp, *up_itp;
 struct inst_t *ip;
 struct mod_t *downmdp, *upmdp;
 struct mod_pin_t *mpp;
 struct net_pin_t *npp;
 struct net_t *down_np;

 /* if has PLI cannot assume simple assign */
 /* AIV 12/17/10 - this needs to check the net access level since */
 /* with new option setting file - no longer design wide */
 if (np->pli_access >= 2) return(FALSE);
 /* must be scalar */
 if (np->srep != SR_SCAL && np->srep != SR_SCAL2S) return(FALSE);
 if (np->nlds == NULL) return(FALSE);
 /* if has dces cannot do simple assign - need to also do dce list */
 if (np->dcelst != NULL) return(FALSE);
 /* skip if it has a force */
 if (np->frc_assgn_allocated) return(FALSE);

 upmdp = __inst_mod;
 up_itp = upmdp->moditps[0];
  
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* only handling all NP_ICONN */
   if (npp->npntyp != NP_ICONN) return(FALSE);
   /* skip xmrs */
   if (npp->npproctyp != NP_PROC_INMOD) return(FALSE);


   itp = &(up_itp->in_its[npp->elnpp.eii]);
   ip = itp->itip; 
   downmdp = ip->imsym->el.emdp; 

    mpp = &(downmdp->mpins[npp->obnum]); 
    if (npp->npntyp == NP_PB_ICONN)
     {
      mpp = &(mpp->pbmpps[npp->pbi]);
      up_rhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
     }
    else up_rhsx = ip->ipins[npp->obnum]; 
    
    /* up better be simple ID */
    if (up_rhsx->optyp != ID) return(FALSE);

    down_lhsx = mpp->mpref;
   
    /* skip edge cases */
    if (down_lhsx->x_multfi || down_lhsx->x_stren || down_lhsx->lhsx_ndel) 
     {
      return(FALSE);
     }

    /* down better be simple scalar ID */
    if (down_lhsx->optyp != ID) return(FALSE);
    down_np = down_lhsx->lu.sy->el.enp;
    /* skip if it has a force */
    if (down_np->frc_assgn_allocated) return(FALSE);
    if (down_np->srep != SR_SCAL && np->srep != SR_SCAL2S) return(FALSE);
   }

 np->is_iconn_port_scalar_opt = TRUE;
 return(TRUE);
}

/*
 * generate all the nets in a modules net change flow graph
 * build a flow graph for each range (ncp) on a net for all nets in the module
 */
static void gen_net_chgs_flowgs(struct mod_t *mdp)
{
 int32 ni;
 struct net_chg_t *ncp;
 struct net_t *np;

 /* for each net and each range of net build the net change flow graph */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
    {
     __push_wrkitstk(mdp, 0);
  /* AIV LOOKATME - no reason to make this a seperate flow graph for now */
  /********************************************
     fgp = __alloc_flowg(FLOWG_NCHG);
     // if has set idp know it uses design wide idp area 
     ncp->nchg_fgp = fgp;
     __cur_ifrom_u.from_gateca = ncp->ndx;
     __cur_flowg = fgp;
     __cur_bbp = NULL;
  
     enter_bbp = __alloc_bblk(FALSE);
     __start_bblk(enter_bbp); 
     enter_bbp->after_suspend = TRUE;
     __emit_enter_net_chg(ncp->ndx);
  
     if (ncp->is_const) 
      {
       gen_one_net_chg_const(np, ncp);
      }
     else gen_one_net_chg_var(np, ncp->ndx, -1);
    
     __emit_complete();
  ********************************************/
     /* generate back end for wire delay handling */
     if (ncp->is_wire_ev) 
       gen_nchg_process_wire_flowg(np, ncp);

     /* if these are T => don't need any back end handling from nchg events */
     /* being scheduled - this from the flow graphs above never call nchg */
     /* actions */
     if (!np->n_cause && __needs_netchg_record(np)) 
      {
       gen_nchg_process_flowg(np, ncp);
      }
     __pop_wrkitstk();
    }
  }
}

/*
 * build a net change flow graph for the passed net with the given range
 * passed in the ncp
 */
static void gen_nchg_process_flowg(struct net_t *np, struct net_chg_t *ncp)
{
 struct bblk_t *enter_bbp;
 struct flowg_t *fgp;
 int32 cint_ti, mask_ti, nchga_addrti, np_ti; 
 int32 has_range, has_dce, has_lds, in_range;
 int32 mipd_flag_ti, nxt_nchg_ti; 
 size_t offset;
 struct nchglst_t *nchgp;
 struct net_pin_t *npp;
 struct npaux_t *npauxp;

 fgp = __alloc_flowg(FLOWG_PROCESS_NCHG);

 /* if has set idp know it uses design wide idp area */
 ncp->process_nchg_fgp = fgp;
 __cur_ifrom_u.from_gateca = ncp->ndx;
 __cur_flowg = fgp;
 __cur_bbp = NULL;

 enter_bbp = __alloc_bblk(FALSE);
 __start_bblk(enter_bbp); 
 enter_bbp->after_suspend = TRUE;
 __emit_process_enter_net_chg(ncp->ndx);

 /* AIV 07/09/09 - if marked used fixed code in v_asmlnk.c */
 if (np->is_iconn_port_scalar_opt) 
  {
   fgp->optim_scalar_port = TRUE;
   fgp->optim_port_np = np; 
   __emit_complete();
   return;
  }

 /* nchglp->triggered = FALSE; */
 
 /* __nchged_delayed_mipd = nchglp->delayed_mipd */
 /* AIV LOOKAMTE AIV BEWARE */
 /* the current net change is stored in %eax */
 /* store into __next_nchglp simply to not waste a register - could later */
 /* place in register if there was one available */
 /* __next_nchglp is later used to when __emit_next_nchg_event(); */
 /* is expanded to get the next net change */
 /* AIV 10/23/08 - swapped these better to do write insn followed by */
 /* a bunch of read insns */
 nchgp = &__nchg_dummy_hd;
 cint_ti = __gen_cint_tn(FALSE);
 __st_insn(I_STOREA, AM_REG, cint_ti, AM_NDXREG, AR_AX);
 offset = (byte *) &(nchgp->nchg_idp) - (byte *) nchgp;
 __st_insn(I_STOREA, AM_NDXREG_DISP, AR_AX, offset, AM_REG, IDP_REG);

 if (np->n_mipd)
  {
   offset = (byte *) &(nchgp->delayed_mipd) - (byte *) nchgp;
   mipd_flag_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, AR_AX, offset);
   __st_insn(I_STOREA, AM_REG, mipd_flag_ti, AM_NLO, NLO_DELAYED_MIPD);
  }
 
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 nxt_nchg_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG_DISP, AR_AX, offset);
 __st_insn(I_STOREA, AM_REG, nxt_nchg_ti, AM_NLO, NLO_NEXT_NCHGLP);

 /*  __idp[np->nchgaction_ofs] &= (~NCHG_ALL_CHGED) */
 /* AIV 01/08/08 - nchgaction array is only used for dumpvars */
 if (np->dmpv_in_src || np->dmpp_in_src)
  {
   cint_ti = __gen_cint_tn(~NCHG_ALL_CHGED);
   nchga_addrti =  __emit_ld_nchg_bptr(np);
   mask_ti = __emit_mask_and(nchga_addrti, cint_ti);
   __st_insn(I_STOREA, AM_REG, mask_ti, AM_NDXREG, nchga_addrti);
  }

 /* AIV 05/13/09 - access level > 2 for call backs */
 /* AIV 05/09/12 - access level can be set per net via optconfig */ 
 if (np->pli_access >= 2)
  {
   np_ti = __ld_netadr_tn(np);
   __emit_chk_dce_cbvc(np_ti);
  }

 has_lds = FALSE;
 has_range = FALSE;
 /* check if any npp has range */
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   has_lds = TRUE;
   if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 != -1)
    {
     has_range = TRUE;
    }
  }
     
 /* check if dce has range */
 has_dce = FALSE;
 if (__needs_netchg_record(np))
  {
   if (np->ntyp < NONWIRE_ST)
    {
     has_dce = TRUE;
     /* AIV 10/19/09 - this is never needed only used for nlds */ 
     /* if (dcelist_needs_range(np)) has_range = TRUE; */
    }
  }

 /* must be producing nchg for either dce or load else no need for recording */
 /* DBG remove -- */
 /* AIV 11/14/07 - if has force may need to propgate changes for dces */
 /* AIV 11/21/07 - if nb var ndx on lhs need to propgate changes for dces */
 if (!has_dce && !has_lds && !np->frc_assgn_allocated 
     && !np->n_on_nblhs_varndx  && !np->pli_access && !np->n_has_toggle) 
    __misc_terr(__FILE__, __LINE__);
 /* ---- */

 if (has_dce) 
  {
   //__emit_exec_enter_dce(np);
   in_range = gen_1net_wakeup_insns(np, ncp->i1, ncp->i2, FALSE, TRUE);
//AIV FIXME - need to tell if code is not executable - should never rec change
   //if (!in_range) __misc_terr(__FILE__, __LINE__);
  }
 if (has_lds) 
  {
 //  __emit_exec_enter_npp(np);
   if (ncp->i1 == -1) 
    {
     in_range = gen_1net_npp_insns(np, FALSE, -1, -1, TRUE);
    }
   else in_range = gen_1net_npp_insns(np, has_range, ncp->i1, ncp->i2, TRUE);
//AIV FIXME - need to tell if code is not executable - should never rec change
   //if (!in_range) __misc_terr(__FILE__, __LINE__);
  }

 __emit_next_nchg_event();
}
     
/*
 * process back end of wire delay assign
 */
static void gen_nchg_process_wire_flowg(struct net_t *np, struct net_chg_t *ncp)
{
 struct flowg_t *fgp;
 struct bblk_t *enter_bbp, *forced_bbp, *not_forced_bbp;
 int32 has_record, bi;
 struct ctev_t *ctevp;
 int32 bi_ti, np_ti, outv_ti, ctevp_ti, sbp_ti, nadr_ti, chk_force_ti;

 forced_bbp = NULL;
 fgp = __alloc_flowg(FLOWG_WIRE_EV);
 /* if has set idp know it uses design wide idp area */
 ncp->wire_fgp = fgp;
 __cur_ifrom_u.from_np = np;
 __cur_flowg = fgp;
 __cur_bbp = NULL;

 enter_bbp = __alloc_bblk(FALSE);
 __start_bblk(enter_bbp); 
 enter_bbp->after_suspend = TRUE;
 __emit_process_enter_wire_ev(ncp->ndx);

 np_ti = __ld_netadr_tn(np);

 /* DBG remove -- */
 if (ncp->i1 != -1 && ncp->i1 != ncp->i2) 
   __misc_terr(__FILE__, __LINE__);
 /* -- */
 
 if (ncp->i1 == -1 && ncp->i2 == -1) bi = 0;
 else bi = ncp->i1;


 /* if scalar net change range for change is always -1 */
 if (np->nwid == 1) has_record = __net_chg_nd_store(np, -1, -1);
 else has_record = __net_chg_nd_store(np, bi, bi);

 /* if needs record or dumpvars check for change */
 if (has_record) 
  {
   gen_nchg_process_wire_record(np, np_ti, bi);
   __emit_complete();
   return;
  }

 nadr_ti = __gen_ld_netbp(np);
 /* DBG remove -- */ 
 if (np->ndel_ctevtab == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 
 /* frc_qcp =  &(np->nu2.qcval[itinum*np->nwid + bi]); */
 /* if (frc_qcp->qc_active) return; */
 if (np->frc_assgn_allocated) 
  {
   forced_bbp = __alloc_bblk(FALSE);
   not_forced_bbp = __alloc_bblk(FALSE);
   bi_ti = __gen_cint_tn(bi);
   chk_force_ti = __emit_force_active(np_ti, bi_ti);
   __emit_jmp_0(not_forced_bbp, forced_bbp, chk_force_ti);
   __start_bblk(not_forced_bbp);
  }

/* AIV LOOKATME - can this not going in compiler SJM?????
 if (__cur_tevp->te_trdecay)
  {
   __gfwarn(649, np->nsym->syfnam_ind, np->nsym->sylin_cnt,
     "charge on node %s.%s has decayed", __msg2_cur_blditree(__xs),
     np->nsym->synam);
  }
*/

 ctevp = np->ndel_ctevtab[bi];
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);
 outv_ti = __emit_ld_gate_val_from_tev(ctevp_ti, np->n_2state);
 /* __idp[np->nva_ofs] = __cur_tevp->outv; */
 if (np->srep == SR_SCAL || np->srep == SR_SCAL2S) 
  {
   __emit_copy(1, outv_ti, nadr_ti);
  }
 /* sbp = (byte *) &(__idp[np->nva_ofs]); sbp[bi] = __cur_tevp->outv; */
 else if (np->n_stren) 
  {
   sbp_ti = __con_adradd_insn(SR_SVEC, WBITS, nadr_ti, bi);
   __emit_copy(1, outv_ti, sbp_ti);
  }
 /* __lhsbsel(rap, bi, nval & 1); */
 /* __lhsbsel(&(rap[wlen]), bi, (nval >> 1) & 1); */
 else 
  {
   /* gen_st_bsel is expecting a vector convert scalar to vec */
   /* AIV 10/27/09 - if scalar now handled in __gen_st_bsel */
   __gen_st_bsel(np->srep, nadr_ti, outv_ti, bi);
  }

 /* skip assign if forced */
 if (np->frc_assgn_allocated) 
  {
   __start_bblk(forced_bbp);
  }

 __emit_complete();
}
   
/*
 * process backend of wire delay with a net change record on np
 */
static void gen_nchg_process_wire_record(struct net_t *np, int32 np_ti, 
 int32 bi)
{
 struct bblk_t *done_bbp, *not_forced_bbp, *not_eq_bbp;
 struct ctev_t *ctevp;
 int32 bi_ti, outv_ti, ctevp_ti, sbp_ti, nadr_ti, chk_force_ti, vec_ti;

 /* frc_qcp =  &(np->nu2.qcval[itinum*np->nwid + bi]); */
 /* if (frc_qcp->qc_active) return; */
 done_bbp = __alloc_bblk(FALSE);
 if (np->frc_assgn_allocated) 
  {
   not_forced_bbp = __alloc_bblk(FALSE);
   bi_ti = __gen_cint_tn(bi);
   chk_force_ti = __emit_force_active(np_ti, bi_ti);
   __emit_jmp_0(not_forced_bbp, done_bbp, chk_force_ti);
   __start_bblk(not_forced_bbp);
  }

 ctevp = np->ndel_ctevtab[bi];
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);
 outv_ti = __emit_ld_gate_val_from_tev(ctevp_ti, np->n_2state);

 nadr_ti = __gen_ld_netbp(np);
 if (np->srep == SR_SCAL || np->srep == SR_SCAL2S) 
  {
   /* if (__idp[np->nva_ofs] != nval) */
   not_eq_bbp = __alloc_bblk(FALSE);
   __emit_jmp_eq(done_bbp, not_eq_bbp, outv_ti, nadr_ti); 
   __start_bblk(not_eq_bbp);
   __emit_copy(WRDBYTES, outv_ti, nadr_ti);
   /* may not need record but needs dumpvar change */
    __gen_record_const_nchg(np, -1, -1, done_bbp);
  }
 else if (np->n_stren) 
  {
   /* if (sbp[bi] != nval) */
   not_eq_bbp = __alloc_bblk(FALSE);
   if (np->srep == SR_SSCAL)
    {
     sbp_ti = nadr_ti;
     bi = -1;
    }
   else sbp_ti = __con_adradd_insn(SR_SVEC, WBITS, nadr_ti, bi);
   __emit_jmp_byte_eq(done_bbp, not_eq_bbp, sbp_ti, outv_ti); 
   __start_bblk(not_eq_bbp);
   __emit_copy(1, outv_ti, sbp_ti);
   __gen_record_const_nchg(np, bi, bi, done_bbp);
  }
 else 
  {
   /* gen_st_bsel is expecting a vector convert scalar to vec */
   vec_ti = __emit_movw_fr_scal(1, outv_ti, FALSE);
   /* notice this does the recording */
   __gen_lhsbsel_const(np, nadr_ti, bi, vec_ti);
  }
 __start_bblk(done_bbp);
}
 
/*
 * generate code for a net change with the known constant range passed
 * in ncp - inline the net change code
 */
static void gen_one_net_chg_const(struct net_t *np, struct net_chg_t *ncp, 
 struct bblk_t *after_bbp)
{
 int32 np_ti, i1, i2, in_range;
 int32 nchg_trigger_ti, nchg_reg_ti;
 struct bblk_t *add_nchg_bbp, *tst_dmpv_bbp;

 /* AIV 09/14/06 - pli access all nets must check for change */
 i1 = ncp->i1;
 i2 = ncp->i2;
 np_ti = -1;
 /* AIV 05/13/09 - access level > 2 for call backs */
 /* AIV 05/09/12 - access level can be set per net via optconfig */ 
 if (np->pli_access >= 2)
  {
   /* SJM 07-25-07 - for pli need to load netadr for np here */ 
   np_ti = __ld_netadr_tn(np);
   __emit_chk_dce_cbvc(np_ti);
  }

 /* may need to record change for toggle */
 if (np->n_has_toggle) 
  {
   if (np_ti == -1) np_ti = __ld_netadr_tn(np);
   __emit_add_togglelst_el(np_ti);
  }

 /* AIV 10/19/09 - on need to check monit_in_src flag here */
 if (np->ntyp >= NONWIRE_ST && np->nchg_has_dces)
  {
   /* AIV 10/21/05 - if index isn't set do it here */
   /* this is needed here because lowering can be in different mod */
   //__emit_exec_enter_dce(np);
   in_range = gen_1net_wakeup_insns(np, i1, i2, FALSE, FALSE);

   /* AIV 05/10/07 - if net is >= NONEWIRE and has no loads and is not */
   /* dumpvars don't record change */
   /* AIV 05/10/07 LOOKATME - PLI changes ok here ????? */
   if (np->nlds == NULL && (!np->dmpv_in_src && !np->dmpp_in_src)) 
    {
     /* AIV 09/27/07 - if doesn't have dce in range and no load should never */
     /* do this record in the first place */
     //AIV LOOAKTME - this is not true for the variable case mem might be index
     //with a variable but assigned else where with a constant value 
     //therefore missing the dce list
     //if (!in_range) __misc_terr(__FILE__, __LINE__); 
     return;
    }
  }

 /* if toggle - it can get here without a need to dump and no loads - just toggle */
 if (np->n_has_toggle)
  {
   if (!np->dmpv_in_src && !np->dmpp_in_src)
    {
     if (!(np->nlds != NULL || (np->ntyp < NONWIRE_ST && np->dcelst != NULL)))
      return;
    }
  }
 add_nchg_bbp = __alloc_bblk(FALSE);

 if (!np->dmpv_in_src && !np->dmpp_in_src)
  {
   nchg_reg_ti = __gen_process_nchg_to_reg_tn(ncp);
   nchg_trigger_ti = __gen_nchg_trigger(nchg_reg_ti);

   __emit_jmp_0(add_nchg_bbp, after_bbp, nchg_trigger_ti);
   __start_bblk(add_nchg_bbp);

   gen_add_static_nchglst(np->n_mipd, nchg_reg_ti);
  }
 else
  {
   if (np->nlds != NULL || (np->ntyp < NONWIRE_ST && np->dcelst != NULL))
    {
     nchg_reg_ti = __gen_process_nchg_to_reg_tn(ncp);
     nchg_trigger_ti = __gen_nchg_trigger(nchg_reg_ti);

     tst_dmpv_bbp = __alloc_bblk(FALSE);
     __emit_jmp_0(add_nchg_bbp, tst_dmpv_bbp, nchg_trigger_ti);
     __start_bblk(add_nchg_bbp);

     gen_add_static_nchglst(np->n_mipd, nchg_reg_ti);

     __start_bblk(tst_dmpv_bbp);
    }
   else __start_bblk(add_nchg_bbp);

   if (np->dmpv_in_src)
    {
     gen_one_net_dumpvar_record(np, after_bbp, i1, TRUE);
    }
   if (np->dmpp_in_src)
    {
     gen_one_net_dumpport_record(np, after_bbp);
    }
  }
}

/*
 * generate code for a net change with the var or entire net change range
 */
static void gen_one_net_chg_var(struct net_t *np, struct net_chg_t *ncp,
  int32 bi_ti, struct bblk_t *after_bbp)
{
 int32 np_ti, nchg_ti;
 int32 ndx_ti, nchg_reg_ti, nchg_trigger_ti;
 struct bblk_t *add_nchg_bbp, *tst_dmpv_bbp;

 np_ti = -1;
 /* AIV 09/06/07 - BEWARE arg must now be loaded always passed in EAX */ 
 if (bi_ti == -1) ndx_ti = __ld_nchg_var_ndx(); 
 else ndx_ti = bi_ti;

 /* AIV 09/14/06 - pli access all nets must check for change */
 /* AIV 05/13/09 - access level > 2 for call backs */
 /* AIV 05/09/12 - access level can be set per net via optconfig */ 
 if (np->pli_access >= 2)
  {
   np_ti = __ld_netadr_tn(np);

   /* call wrapper to look for change */
   __emit_chk_dce_cbvc(np_ti);
  }
 
 /* may need to record change for toggle */
 if (np->n_has_toggle) 
  {
   if (np_ti == -1) np_ti = __ld_netadr_tn(np);
   __emit_add_togglelst_el(np_ti);
  }

 /* SJM 08/02/05 - LOOKATME - why need to test monit in src? */
 if (np->ntyp >= NONWIRE_ST && (np->nchg_has_dces || np->monit_in_src))
  {
   /* AIV 05/10/07 - only set range if dce list checks it */
   if (dcelist_needs_range(np))
    {
     __emit_set_dce_rng(ndx_ti, ndx_ti, FALSE);
    }
   __emit_exec_enter_dce(np);
   /* AIV 05/10/07 - if net is >= NONEWIRE and has no loads and is not */
   /* dumpvars don't record change */
   /* AIV 05/10/07 LOOKATME - PLI changes ok here ????? */
   if (np->nlds == NULL && (!np->dmpv_in_src && !np->dmpp_in_src)) 
    {
     return;
    }
  }

 /* if toggle - it can get here without a need to dump and no loads - just toggle */
 if (np->n_has_toggle)
  {
   if (!np->dmpv_in_src && !np->dmpp_in_src)
    {
     if (!(np->nlds != NULL || (np->ntyp < NONWIRE_ST && np->dcelst != NULL)))
      return;
    }
  }

 add_nchg_bbp = __alloc_bblk(FALSE);
 if (!np->dmpv_in_src && !np->dmpp_in_src)
  {
   nchg_reg_ti = __gen_process_nchg_to_reg_tn(ncp);
   nchg_trigger_ti = __gen_nchg_trigger(nchg_reg_ti);

   __emit_jmp_0(add_nchg_bbp, after_bbp, nchg_trigger_ti);
   __start_bblk(add_nchg_bbp);

   __gen_netchg_addr_tn(np, -1, -1, FALSE, &nchg_ti);
   __emit_add_static_nchglst_sel(nchg_ti, ndx_ti, ndx_ti);
  }
 else
  {
   if (np->nlds != NULL || (np->ntyp < NONWIRE_ST && np->dcelst != NULL))
    {
     nchg_reg_ti = __gen_process_nchg_to_reg_tn(ncp);
     nchg_trigger_ti = __gen_nchg_trigger(nchg_reg_ti);

     tst_dmpv_bbp = __alloc_bblk(FALSE);
     __emit_jmp_0(add_nchg_bbp, tst_dmpv_bbp, nchg_trigger_ti);
     __start_bblk(add_nchg_bbp);

     nchg_ti = __gen_process_nchg(ncp);
     __emit_add_static_nchglst_sel(nchg_ti, ndx_ti, ndx_ti);

     __start_bblk(tst_dmpv_bbp);
    }
   else __start_bblk(add_nchg_bbp);

   if (np->dmpv_in_src)
    {
     gen_one_net_dumpvar_record(np, after_bbp, bi_ti, FALSE);
    }
   if (np->dmpp_in_src)
    {
     gen_one_net_dumpport_record(np, after_bbp);
    }
  }
}

/*
 nchglp->triggered = TRUE;
 nchglp->nchglnxt = NULL;
 __nchg_futend->nchglnxt = nchglp; 
 __nchg_futend = nchglp; 
*/
static void gen_add_static_nchglst(int32 has_n_mipd, int32 nchg_reg_ti)
{
 int32 end_ti, cint_ti;
 struct nchglst_t *nchgp;
 size_t offset;

 /* AIV 03/04/07 - only do these here if net has mipd not in wrapper */
 /* nchglp->delayed_mipd = FALSE; */
 /* AIV 11/09/11 - this needs to be assigned here */
 nchgp = &__nchg_dummy_hd;
 if (has_n_mipd)
  {
   offset = (byte *) &(nchgp->delayed_mipd) - (byte *) nchgp;
   cint_ti = __gen_cint_tn(FALSE);
   __st_insn(I_STOREA, AM_REG, cint_ti, AM_NDXREG_DISP, nchg_reg_ti, offset);
  }

 /* DBG remove -- */
 offset = (byte *) &(nchgp->triggered) - (byte *) nchgp;
 if (offset != 0) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* nchglp->triggered = TRUE; */
 end_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NCHG_FUTEND);
 /* AIV 02/13/09 - don't set the value equal to 1 better to set to address */
 /* which is known not to be 0 - which will be in a register */
 /* AIV BEWARE - this may look like a bad memory since it is not 0/1 */
 /* cint_ti = __gen_cint_tn(TRUE); */
 __st_insn(I_STOREA, AM_REG, end_ti, AM_NDXREG, nchg_reg_ti);
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 /* AIV 12/30/08 - this is not needed - it will always be set to dummy */
 /* event - can set for debugging */
 /* nchglp->nchglnxt = NULL; */
#ifdef __CVC_DEBUG__
 //cint_ti = __gen_cint_tn(FALSE);
 //__st_insn(I_STOREA, AM_REG, cint_ti, AM_NDXREG_DISP, nchg_reg_ti, offset);
#endif
 __st_insn(I_STOREA, AM_REG, nchg_reg_ti, AM_NDXREG_DISP, end_ti, offset);
 __st_insn(I_STOREA, AM_REG, nchg_reg_ti, AM_NLO, NLO_NCHG_FUTEND);
}


/*
 * do one net dump var record
 */
static void gen_one_net_dumpvar_record(struct net_t *np, 
 struct bblk_t *after_bbp, int32 bi, int32 is_const)
{
 struct bblk_t *add_dmpv_bbp;
 int32 cint_ti, nd_dmpv_ti, nchga_addr_ti, np_ti;
 

 /* AIV 01/26/11 - cannot dump auto task variables or wire arrays */
 /* DBG remove -- */
 if (np->n_is_auto_var) __misc_terr(__FILE__, __LINE__);
 if (np->n_isarr && np->ntyp < NONWIRE_ST) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 __cvc_slotend_action |= SE_DUMPVARS;
 /* AIV FIXME - now should use this bit since these elements are fixed */
 add_dmpv_bbp = __alloc_bblk(FALSE);
 //AIV FIXME - need a different flag for dumpvars - so don't need nchg word
 //in idp area
 nchga_addr_ti =  __emit_ld_nchg_bptr(np);
 cint_ti = __gen_cint_tn(NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED);
 nd_dmpv_ti = __emit_mask_and(nchga_addr_ti, cint_ti);
 __emit_jmp_eq(add_dmpv_bbp, after_bbp, nd_dmpv_ti, cint_ti);
 __start_bblk(add_dmpv_bbp);  
 np_ti = __ld_netadr_tn(np);
 /* AIV 07/14/10 - now allowing dumping of arrays */
 if (np->n_isarr)
  {
   /* DBG remove -- */
   if (!__dump_arrays) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   if (is_const)
    {
     /* DBG remove -- */
     if (bi == -1) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     bi = __gen_cint_tn(bi);
    }
   __emit_add_dmpvlst_array(np_ti, bi);
  }
 else __emit_add_dmpvlst(np_ti);
}

/*
 * do one net dump port record
 * almost identical to dumpvars - masks and call are different
 */
static void gen_one_net_dumpport_record(struct net_t *np, 
 struct bblk_t *after_bbp)
{
 struct bblk_t *add_dmpp_bbp;
 int32 cint_ti, nd_dmpv_ti, nchga_addr_ti, np_ti;

 add_dmpp_bbp = __alloc_bblk(FALSE);

 __cvc_slotend_action |= SE_DUMPPORTS;
 nchga_addr_ti =  __emit_ld_nchg_bptr(np);
 cint_ti = __gen_cint_tn(NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED);
 nd_dmpv_ti = __emit_mask_and(nchga_addr_ti, cint_ti);
 __emit_jmp_eq(add_dmpp_bbp, after_bbp, nd_dmpv_ti, cint_ti);
 __start_bblk(add_dmpp_bbp);  
 np_ti = __ld_netadr_tn(np);
 __emit_add_dmpportlst(np_ti);
}

/*
 * return the net change fixed struct for the given range
 */
extern struct net_chg_t *__gen_netchg_addr_tn(struct net_t *np, int32 i1, 
 int32 i2, int32 is_wire_ev, int32 *rnchg_ti)
{
 int32 nchg_ti;
 struct net_chg_t *ncp;

//AIV FIXME - still need to add for WIRE_EV tree - need seperate wire ev tree
 ncp = __find_nchg_range(np, i1, i2);
 /* DBG remove -- */
//AIV FIXME
 //if (is_wire_ev && !ncp->is_wire_ev) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 ncp->is_wire_ev = is_wire_ev;
 nchg_ti = __gen_process_nchg(ncp);
 *rnchg_ti = nchg_ti;
 return(ncp);
}
 
/*
 * generate back end MIPD flow graphs
 */
static void gen_mipd_flowgs(struct mod_t *mdp)
{
 int32 ni;
 struct task_t *tskp;
 struct net_t *np;

 /* module contains no mipds nothing to do */
 if (!mdp->mod_has_mipds) return;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   if (np->nlds != NULL) try_gen_mipd_flowg(np);
  }

 /* regs in tasks can require net chg processing too but always */
 /* separate flowgs */
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     if (np->nlds != NULL) try_gen_mipd_flowg(np);
    }
  }
}
     
/*
 * generate a MIPD flow graph if net has an MIPD npp on its load list
 */
static void try_gen_mipd_flowg(struct net_t *np)
{
 struct net_pin_t *npp;
 struct bblk_t *enter_bbp;
 struct flowg_t *fgp;
 int32 np_ti, nchg_ti;

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt) 
  {
   if (npp->npntyp != NP_MIPD_NCHG) continue;

   fgp = __alloc_flowg(FLOWG_MIPD);
   __cur_ifrom_u.from_np = np;
   np->n_mipd = TRUE;
   __cur_flowg = fgp;
   npp->npp_fgp = fgp;
   __cur_bbp = NULL;

   enter_bbp = __alloc_bblk(FALSE);
   __start_bblk(enter_bbp); 
   enter_bbp->after_suspend = TRUE;

   __emit_enter_mipd(npp->npp_idnum);
   if (np->n_isavec)
    {
     np_ti = __ld_netadr_tn(np);
     __emit_process_mipd_nchg_ev(np_ti);
    }
   else
    {
     __gen_netchg_addr_tn(np, -1, -1, FALSE, &nchg_ti);
     __emit_process_mipd_scalar_nchg_ev(nchg_ti);
    }
   __emit_complete();
  }
}

/*
 * ROUTINES TO GEN VINSN SUBROUTINES TO EVAL MULT FAN IN DRVRS INTO TMP NAME
 */

/*
 * generate for one multfi net the load and comb driver insns
 * the multfi eval code is a proc with fi>1 accum addr passed as arg
 */
static void bld_1net_ldcomb_multfi_flowg(struct net_t *np)
{
 int32 res_ti, arg_ti, nbytes, amtype, res_bpti;
 struct flowg_t *fgp;
 struct bblk_t *multfi_bbp;

 fgp = __alloc_flowg(FLOWG_MULTFI);
 add_flowg_to_netfg_list(np, fgp);
 __cur_flowg = fgp;
 __cur_bbp = NULL;

 multfi_bbp = __alloc_bblk(FALSE);
 /* SJM 02/21/06 - any entry from interpreter RT needs AFS bit set */
 multfi_bbp->after_suspend = TRUE;
 __start_bblk(multfi_bbp); 
 __cur_ifrom_u.from_np = np;

 if (np->mfi_id == -1) np->mfi_id = ++(__inst_mod->mod_ndx_seq_no); 

 __emit_multfi_subr(np->mfi_id, np, __inst_mod);
 /* need to save the result address passed to the subroutine */
 /* AIV 07/08/08 - if value is narrow non-stren value is returned in regs */
 arg_ti = -1;
 if (np->nwid > WBITS || np->srep == SR_SVEC)
  {
   arg_ti = __emit_save_arg();
  }

 /* SJM 06/21/05 - think this can use the set RT globals */
 if (!np->n_stren) 
  {
   res_ti = gen_load_mdrwire_subr(np);
   if (np->n_2state) nbytes = wlen_(__get_tnwid(res_ti))*WRDBYTES;
   else nbytes = 2*wlen_(__get_tnwid(res_ti))*WRDBYTES;
  }
 else
  {
   res_ti = gen_stload_mdrwire_subr(np);
   /* if strength copy number of bytes for each bit */
   nbytes = __get_tnwid(res_ti);
  }
 /* if net is scalar only copy a byte */
 if (np->srep == SR_SCAL || np->srep == SR_SSCAL || np->srep == SR_SCAL2S) 
  {
   nbytes = WRDBYTES;
  }

 /* AIV 10/27/05 - need to convert to the right size and type */
 res_ti = __gen_cnvt_srep_ifneeded(res_ti, np->srep, np->nwid, FALSE, FALSE, 
  FALSE);

 /* copy the restult into the address passed as the saved arg to MFI subr */
 if (arg_ti != -1)
  {
   __copy_arg(nbytes, res_ti, arg_ti);
   __emit_complete();
   return;
  }

 if (__tntab[res_ti].tn_typ == TN_ADR) amtype = AM_NDXREG; 
 else amtype = AM_REG;

 /* AIV 07/08/08 - if value is narrow non-stren value is returned in regs */
 if (np->srep == SR_SCAL || np->srep == SR_SSCAL || np->srep == SR_SCAL2S) 
  {
   __st_insn(I_STOREA, amtype, res_ti, AM_REG, AR_AX);
  }
 else
  {
   /* AIV BEWARE - values are now returned in EAX and ECX */
   __st_insn(I_STOREA, amtype, res_ti, AM_REG, AR_AX);
   if (!np->n_2state)
    {
     res_bpti = __get_bpti(res_ti);
     __st_insn(I_STOREA, amtype, res_bpti, AM_REG, AR_CX);
    }
  }
 __emit_complete();
}

/*
 * links a flowg onto the front of the a net's nflowg list
 */
static void add_flowg_to_netfg_list(struct net_t *np, struct flowg_t *fgp)
{
 /* AIV 02/03/12 - removed tail_nflowg to shrink net_t struct - can just */
 /* always link these on the front */
 /* always put on front */
 if (np->nflowg == NULL)
  {
   np->nflowg = fgp;
  }
 else
  {
   fgp->flowgnxt = np->nflowg;
   np->nflowg = fgp;
  }
}

/*
 * ROUTINES TO GEN VINSNS TO LOAD MULTI DRIVER WIRE INTO TMP REG  
 */

/*
 * gen vinsns to load non stren multi-drive wire
 *
 * handling of match push tricky because at run time some insts may
 * need change targ to reference and some no, since not needed at 
 * compile time emit the pop but make sure to jump over it if not pushed
 * at run time
 */
static int32 gen_load_mdrwire_subr(struct net_t *np)
{
 struct net_pin_t *npp;
 int32 accum_apti, accum_bpti, bytsiz, nd_itpop, ofs; 
 int32 accum_hw_bpti, ubits, idp_ti, mask_ti, fixed_mdat_ti;
 word32 mask;
 struct bblk_t *skip_npp_bbp, *after_bbp;
 struct mod_t *ref_in_mdp;
 int32 nd_rt_itpop, save_idp_ti;
 struct itree_t *itp;

 save_idp_ti = -1;
 bytsiz = WRDBYTES*wlen_(np->nwid);
 if (np->n_2state)
  {
   accum_apti = __gen_tn(SR_BIT2S, np->nwid);
   __emit_store_cint(accum_apti, 0, bytsiz);
  }
 else
  {
   accum_apti = __gen_tn(SR_VEC, np->nwid);
   __emit_store_cint(accum_apti, 0, bytsiz);
   accum_bpti = __get_bpti(accum_apti);

   /* AIV 02/20/07 - wasn't masking for the b part bits for nwid < WBITS */
   /* AIV 03/12/12 - this should be <= here not < */
   if (np->nwid <= WBITS)
    {
     mask = __masktab[np->nwid];
     mask_ti = __gen_cint_tn(mask);
     /* AIV 08/01/07 - was using store_cint here but cannot use here becuase */
     /* it extends 0xff to 0xfffffff for a word copy so a simple word copy */
     /* is needed here */
     __emit_copy(WRDBYTES, mask_ti, accum_bpti);
    }
   else 
    {
     bytsiz = bytsiz - WRDBYTES;
     __emit_setall1(accum_bpti, bytsiz);
     ubits = ubits_(np->nwid);
     mask = __masktab[ubits];
     ofs = (2*wlen_(np->nwid) -1)*WRDBYTES;
     accum_hw_bpti = __con_adradd_insn(SR_VEC, WBITS, accum_apti, ofs);
     mask_ti = __gen_cint_tn(mask);
     __emit_copy(WRDBYTES, mask_ti, accum_hw_bpti);
    }
  }

 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt) 
  {
   after_bbp = NULL;
   if (npp->npproctyp == NP_PROC_FILT && __inst_mod->flatinum > 1)
    {
     skip_npp_bbp = __alloc_bblk(FALSE);
     after_bbp = __alloc_bblk(FALSE);

     itp = (struct itree_t *) npp->npaux->npu.filtidp;
     fixed_mdat_ti = __gen_mdata_value(itp);
     __emit_jmp_idp_eq(skip_npp_bbp, after_bbp, fixed_mdat_ti); 
     __start_bblk(skip_npp_bbp);
    }

   nd_rt_itpop = nd_itpop = FALSE;
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* 12/16/05 - SJM - if push itree, pushing to driving rhs itree loc */
     /* proc gref means instance tree relative (not 1 inst) */
     /* this always pushes a matching one at compile time too */
     if (npp->npproctyp == NP_PROC_GREF)
      {
       /* even if current (1st) inst does not match, finds one to push */
       /* at compile time */
       if (after_bbp == NULL) after_bbp = __alloc_bblk(FALSE);
       idp_ti = gen_match_targ_to_ref(npp->np_xmrtyp, npp->npaux->npu.npgrp,
                  after_bbp);
       /* AIV 05/09/07 FIXME - notice next npp scheme not needing save */
       /* of inum/indx doesn't work here for mfi - FIXME?????? */
       gen_set_save_idp(idp_ti, &save_idp_ti, TRUE);

       /* SJM 01/23/06 - for match push, any compile time inst will work */
       /* since just need inst mod, but can't use push wrk itstk because */
       /* need rooted inst in other case */
       ref_in_mdp = npp->npaux->npu.npgrp->gin_mdp;
       __push_itstk(ref_in_mdp->moditps[0]);
       nd_rt_itpop = TRUE;
      }
     else 
      {
       /* AIV 04/10/07 - just push the constant value */
       if (need_npp_downinst_push(npp->npntyp))
        {
         itp = npp->npaux->npdownitp;
         gen_ld_const_idp(itp, &save_idp_ti, TRUE);
         nd_rt_itpop = TRUE;
        }
       /* SJM 09/29/05 - must move to rooted ref itree loc at comp time */
       __push_itstk(npp->npaux->npdownitp);
      }
     nd_itpop = TRUE;
    }

   /* this pops itree loc is one was pushed in the middle of it */
   /* SJM 01/23/06 - notice if match push does not match, i.e. this decl */
   /* in instance does not get pushed, skips this code so never exec the pop */
   if (nd_rt_itpop)
    {
     gen_ldcomb_1_drvr(accum_apti, np, npp, nd_itpop, save_idp_ti);
    }
   else gen_ldcomb_1_drvr(accum_apti, np, npp, nd_itpop, -1);

   /* AIV 01/31/06 - xmr jump after still need to go next */
   if (after_bbp != NULL) __start_bblk(after_bbp); 
  }
 /* restore original current npp  */
 return(accum_apti);
}

/* 
 * AIV 02/28/07 - incorrectly removed a push when removing __cur_npp
 * this pushes the __cur_npp->npaux->npdownitp which is actually dumb
 * because it is constant however the __inst_pr must be correct to load
 * be placed into nchgs events so it is needed until the compiler can
 * deal only with __inums
 *
 * these npp types must do the push
 * AIV 04/10/07 - now used to push the constant itstk values
 */
static int32 need_npp_downinst_push(int32 npntyp)
{
 
 if (npntyp == NP_ICONN || npntyp == NP_PB_ICONN ||
     npntyp == NP_GATE || npntyp == NP_CONTA) 
  {
   return(TRUE);
  }
 return(FALSE);
}

/*
 * load and combine one driver into passed accum tmp name
 *
 * know any inst filtering already emitted and entry itree loc is
 * loc of driving rhs for XMR driver
 */
static void gen_ldcomb_1_drvr(int32 accum_apti, struct net_t *np,
 struct net_pin_t *npp, int32 nd_itpop, int32 save_idp_ti)
{
 int32 tmp_apti, i1, i2, np_ti, pselwid;
 struct mod_t *save_inst_mdp, *in_mdp;
 struct npaux_t *npauxp;

 /* compute driver using rhs itree loc */
 tmp_apti = -1;
 /* AIV 09/14/06 - if has pli access check for changes */
 if (np->pli_access)
  {
   /* AIV 06/06/08 - rare case this is xmr and it doesn't push */
   /* save_idp_ti is -1 because NPP not xmr must handle in pli code */
   /* __ld_netadr_tn checks to make sure __inst_mod is correct */
   //AIV LOOKATME - this isn't true even it xmr pli code must handle???
   //if (npp->npproctyp != NP_PROC_INMOD)
   save_inst_mdp = __inst_mod;
   __get_nets_containing_sy(np, &(in_mdp));
   __inst_mod = in_mdp;
   np_ti = __ld_netadr_tn(np);
   __inst_mod = save_inst_mdp;

   __emit_chk_ld_vpiputv_driver(np_ti, accum_apti);
  }
 switch ((byte) npp->npntyp) {
  case NP_CONTA:
   tmp_apti = gen_ld_conta_driver(npp);
   break;
  case NP_TFRWARG:
   /* AIV 03/19/07 - removed these but are needed - were never tested */
   /* AIV 03/24/09 - for the same reason above code need to save/restore */
   /* proper module from containing net */
   /* AIV LOOKATME ???? */
   save_inst_mdp = __inst_mod;
   __get_nets_containing_sy(np, &(in_mdp));
   __inst_mod = in_mdp;
   tmp_apti = gen_ld_tfrwarg_driver(npp);
   __inst_mod = save_inst_mdp;
   break;
  case NP_VPIPUTV:
   /* AIV 02/16/07 - these aren't at compile time */
   __case_terr(__FILE__, __LINE__);
   break;
  case NP_GATE:
   tmp_apti = gen_ld_gate_driver(npp);
//AIV 2STATE - leaving gate four state for now and converting
/* AIV PUTMEBACK when new combine code works
   if (np->n_2state)
    {
     tmp_apti = __gen_cnvt_srep_ifneeded(tmp_apti, SR_BIT2S, 
        __tntab[tmp_apti].tnwid, FALSE, FALSE, TRUE);
    }
*/
   break; 
  /* these are up to highconn strength output port drivers */
  case NP_ICONN: case NP_PB_ICONN:
   /* pb same except access the 2 known to be 1 bit PB exprs */
   tmp_apti = gen_ld_iconn_up_driver(npp);
   break;
  case NP_MDPRT: case NP_PB_MDPRT:
   /* pb same except access the 2 known to be 1 bit PB exprs */
   tmp_apti = gen_ld_mdprt_down_driver(npp, FALSE);
   break;
  /* TRAN impossible here */
  default: __case_terr(__FILE__, __LINE__);
 }

 /* if was XMR driver - now move back to the lhs being driven net itree loc */
 if (nd_itpop) __pop_itstk();
 if (save_idp_ti != -1) 
  {
   /* AIV 03/12/12 - if xmr made need to move into actual tmp area */
   /* cannot just use the idp (reg) offset */
   if (__tntab[tmp_apti].tn_typ == TN_ADR)
    {
     tmp_apti = __gen_duplicate_tmp(tmp_apti);
    }
   __gen_restore_idp(save_idp_ti);
  }

 /* case 1 (very rare - maybe impossible): lhs non stren */ 
 /* if lhs concatenate, must select section out of rhs value */
 /* the npaux lcbi1 lhs concat value are the index in the lhs */

 if ((npauxp = npp->npaux) != NULL && npauxp->lcbi1 != -1)
  {
   i1 = npauxp->lcbi1;
   i2 = npauxp->lcbi2;

   /* know thing driving wire is 1 bit - will eval. to 1 bit */
   /* AIV 08/13/10 - should handle the bit case here */
   if (i1 == i2) 
    {
     tmp_apti = __gen_rhs_bsel_const(np, tmp_apti, i1);
    }
   else 
    {
     /* this is case for lhs concatenate to extract matching part of rhs */ 
     /* AIV 10/19/06 -  was passing the wrong width  */
     pselwid = i1 - i2 + 1; 
     tmp_apti = __gen_fradr_rhs_psel(np->srep, tmp_apti, pselwid, 
       i2 + pselwid - 1, i2);
    }
  }
 /* if not driver into part of lhs concat use rhs driving tmp name as is */

 /* run non stren (hiz) competition update accumulator with result */
 gen_drvr_competition_upd(accum_apti, tmp_apti, np, npp); 
}

/*
 * gen vinsn to run non stren (hiz) competition between current accum
 * and one driver - non stren version
 *
 * know runs in lhs net expr's itree context - but for XMR npp eval in 
 * rhs itree context - will have popped to put before calling this
 */
static void gen_drvr_competition_upd(int32 accum_apti, int32 drv_apti,
 struct net_t *np, struct net_pin_t *npp)
{
 int32 pselwid, i1, i2, drv_bpti, res_apti;
 int32 con_apti, inum_ti, iofs_ti, ndx_apti, cint_ti;
 struct npaux_t *npauxp;

 if (np->n_2state)
  {
   gen_drvr_competition_upd_2state(accum_apti, drv_apti, np, npp);
   return;
  }
 /* driver must be a vector */ 
 drv_apti = __gen_cnvt_srep_ifneeded(drv_apti, SR_VEC, np->nwid, FALSE, FALSE,
  TRUE);

 drv_bpti = __get_bpti(drv_apti);

 /* entire wire */
 if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1)
  {
   if (np->nwid > WBITS)
    {
     __emit_comb_wide_nonstren(accum_apti, drv_apti, drv_bpti, np, np->nwid);
    }
   else
    {
     __emit_comb_1w_nonstren(accum_apti, drv_apti, drv_bpti, np->ntyp);
    }
   return;
  }

 /* know that driver is section of lhs wire - i.e. lhs select decl assign */
 /* know npaux field exists */
 if (npauxp->nbi1 == -2)
  {
   /* this is per inst, depending on current lhs itree inst num variable */
   con_apti = __gen_contab_tn(npauxp->nbi2.xvi, WBITS, TRUE, FALSE,
    FALSE, SR_VEC);
   inum_ti = __emit_inum();
   cint_ti = __gen_cint_tn(8);
   iofs_ti = __emit_mult(WBITS, inum_ti, cint_ti);
   ndx_apti = __var_adradd_insn(SR_VEC, WBITS, con_apti, iofs_ti);

   res_apti = __gen_rhs_bsel_var(np, accum_apti, ndx_apti);
   /* combine into part of accum - know never wide */
   __emit_comb_1w_nonstren(res_apti, drv_apti, drv_bpti, np->ntyp);
   return;
  }
 i1 = npauxp->nbi1;
 i2 = npauxp->nbi2.i;
 /* know thing driving wire is 1 bit - will eval. to 1 bit */
 if (i1 == i2) 
  {
   res_apti = __gen_rhs_bsel_const(np, accum_apti, i1);
   /* combine into part of accum - know never wide */
   __emit_comb_1w_nonstren(res_apti, drv_apti, drv_bpti, np->ntyp);

   /* SJM - 12/16/05 - now store the one bit stren competition result back */
   __gen_st_bsel(np->srep, accum_apti, res_apti, i1);
   return;
  }

 /* lhs being driven expr is part select */
 pselwid = i1 - i2 + 1; 
 res_apti = __gen_fradr_rhs_psel(np->srep, accum_apti, pselwid, 
   i2 + pselwid - 1, i2);

 if (pselwid > WBITS)
  {
   /* AIV 02/21/07 - comb wide was using np->nwid for length is pselwid */
   __emit_comb_wide_nonstren(res_apti, drv_apti, drv_bpti, np, pselwid);
  }
 else 
  {
   __emit_comb_1w_nonstren(res_apti, drv_apti, drv_bpti, np->ntyp);
  }
 /* AIV 01/20/06 - was incorrectly using drv_apti */
 /* store back into multi-driver but non stren here accumulator */
 __gen_st_psel(np->srep, accum_apti, res_apti, i2, pselwid);
}

/*
 * AIV 2STATE
 */
static void gen_drvr_competition_upd_2state(int32 accum_apti, int32 drv_apti,
 struct net_t *np, struct net_pin_t *npp)
{
 int32 pselwid, i1, i2, res_apti, addr_apti;
 int32 con_apti, inum_ti, iofs_ti, ndx_apti, cint_ti, blen, newval_ti;
 struct npaux_t *npauxp;

 /* driver must be a vector */ 
 drv_apti = __gen_cnvt_srep_ifneeded(drv_apti, SR_BIT2S, np->nwid, FALSE, FALSE,
  TRUE);

 blen = np->nwid;
 /* entire wire */
 if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1)
  {
   /* AIV LOOKATME - better to do this inplace ??? */
   newval_ti = __emit_bin_bitor(blen, accum_apti, drv_apti); 
   __emit_copy(WRDBYTES*wlen_(blen), newval_ti, accum_apti);
   return;
  }

 /* know that driver is section of lhs wire - i.e. lhs select decl assign */
 /* know npaux field exists */
 if (npauxp->nbi1 == -2)
  {
   /* this is per inst, depending on current lhs itree inst num variable */
   con_apti = __gen_contab_tn(npauxp->nbi2.xvi, WBITS, TRUE, FALSE,
    FALSE, SR_VEC);
   inum_ti = __emit_inum();
   cint_ti = __gen_cint_tn(8);
   iofs_ti = __emit_mult(WBITS, inum_ti, cint_ti);
   ndx_apti = __var_adradd_insn(SR_VEC, WBITS, con_apti, iofs_ti);

   res_apti = __gen_rhs_bsel_var(np, accum_apti, ndx_apti);
   /* combine into part of accum - know never wide */
   newval_ti = __emit_bin_bitor(blen, res_apti, drv_apti); 

   addr_apti = __ldvar_addr(np, NULL);
   __gen_lhsbsel_var(np, addr_apti, ndx_apti, newval_ti);
   return;
  }
 i1 = npauxp->nbi1;
 i2 = npauxp->nbi2.i;
 /* know thing driving wire is 1 bit - will eval. to 1 bit */
 if (i1 == i2) 
  {
//AIV 2STATE - think can just or in place the entire word?????
   res_apti = __gen_rhs_bsel_const(np, accum_apti, i1);
   /* combine into part of accum - know never wide */
   newval_ti = __emit_bin_bitor(blen, res_apti, drv_apti); 

   /* SJM - 12/16/05 - now store the one bit stren competition result back */
   __gen_st_bsel(np->srep, accum_apti, newval_ti, i1);
   return;
  }

 /* lhs being driven expr is part select */
 pselwid = i1 - i2 + 1; 
 res_apti = __gen_fradr_rhs_psel(np->srep, accum_apti, pselwid, 
   i2 + pselwid - 1, i2);

 newval_ti = __emit_bin_bitor(blen, res_apti, drv_apti); 
 /* AIV 01/20/06 - was incorrectly using drv_apti */
 /* store back into multi-driver but non stren here accumulator */
 __gen_st_psel(np->srep, accum_apti, newval_ti, i2, pselwid);
}

/*
 * gen vinsns to load stren multi-drive wire
 */
static int32 gen_stload_mdrwire_subr(struct net_t *np)
{
 int32 accum_sbpti, nd_itpop, stval;
 int32 nd_rt_itpop, idp_ti, save_idp_ti, fixed_mdat_ti;
 struct net_pin_t *npp;
 struct bblk_t *skip_npp_bbp, *after_bbp;
 struct mod_t *ref_in_mdp;
 struct itree_t *itp;

 save_idp_ti = -1;
 /* set all of accum to z - same for stren and non stren */
 if (np->n_stren) stval = get_accum_init_stren(np);
 else stval = ST_HIZ;

 accum_sbpti = __gen_tn(np->srep, np->nwid);
 __emit_setstren(accum_sbpti, stval, np->nwid);

 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt) 
  {
   after_bbp = NULL;
   if (npp->npproctyp == NP_PROC_FILT && __inst_mod->flatinum > 1)
    {
     skip_npp_bbp = __alloc_bblk(FALSE);
     after_bbp = __alloc_bblk(FALSE);

     itp = (struct itree_t *) npp->npaux->npu.filtidp;
     fixed_mdat_ti = __gen_mdata_value(itp);
     __emit_jmp_idp_eq(skip_npp_bbp, after_bbp, fixed_mdat_ti); 
     __start_bblk(skip_npp_bbp);
    }

   nd_itpop = nd_rt_itpop = FALSE;
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* proc gref means instance tree relative (not 1 inst) */
     if (npp->npproctyp == NP_PROC_GREF)
      {
       /* even if current (1st) inst does not match, finds one to push */
       /* at compile time */
       if (after_bbp == NULL) after_bbp = __alloc_bblk(FALSE);
       idp_ti = gen_match_targ_to_ref(npp->np_xmrtyp, npp->npaux->npu.npgrp,
                 after_bbp);

       /* AIV 05/09/07 FIXME - notice next npp scheme not needing save */
       /* inum/indx doesn't work here because of wrapper calls for tris */
       gen_set_save_idp(idp_ti, &save_idp_ti, TRUE);
       /* SJM 01/23/06 - for match push, any compile time inst will work */
       /* since just need inst mod, but can't use push wrk itstk because */
       /* need rooted inst in other case */
       ref_in_mdp = npp->npaux->npu.npgrp->gin_mdp;
       __push_itstk(ref_in_mdp->moditps[0]);
       nd_rt_itpop = TRUE;
      }
     else 
      {
       /* AIV 04/10/07 - just push the constant value */
       if (need_npp_downinst_push(npp->npntyp))
        {
         itp = npp->npaux->npdownitp;
         gen_ld_const_idp(itp, &save_idp_ti, TRUE);
         nd_rt_itpop = TRUE;
        }
       /* SJM 09/29/05 - must move to rooted ref itree loc at comp time */
       __push_itstk(npp->npaux->npdownitp);
      }
     nd_itpop = TRUE;
    }

   /* if itree chged, this must pop before any possible lhs cat extract */
   if (nd_rt_itpop)
    {
     gen_st_ldcomb_1_drvr(accum_sbpti, np, npp, nd_itpop, save_idp_ti);
    }
   else gen_st_ldcomb_1_drvr(accum_sbpti, np, npp, nd_itpop, -1);

   /* AIV 01/31/06 - xmr jump after still need to go next */
   if (after_bbp != NULL) __start_bblk(after_bbp); 
  }
 return(accum_sbpti);
}

/*
 * initialize a wire for multi-fi combination (depends on wire type)
 * this push value on to expr. stack
 */
static int32 get_accum_init_stren(struct net_t *np)
{
 byte stval;

 /* initialize in case unc., */
 switch ((byte) np->ntyp) {
  case N_TRI0: stval = ST_PULL0; break;
  case N_TRI1: stval = ST_PULL1; break;
  case N_SUPPLY0: stval = ST_SUPPLY0; break;
  case N_SUPPLY1: stval = ST_SUPPLY1; break;
  default: stval = ST_HIZ; break; 
 }
 return(stval);
}

/*
 * load and combine one stren driver into passed accum tmp name
 *
 * know any inst filtering already emitted and entry itree loc is
 * loc of driving rhs for XMR driver
 */
static void gen_st_ldcomb_1_drvr(int32 accum_sbpti, struct net_t *np,
 struct net_pin_t *npp, int32 nd_itpop, int32 save_idp_ti)
{
 int32 tmp_sbpti, i1, i2, np_ti, pselwid;
 struct mod_t *save_inst_mdp, *in_mdp;
 struct npaux_t *npauxp;

 tmp_sbpti = -1;
 /* AIV 09/14/06 - if has pli access check for changes */
 //AIV LOOKATME - don't think strength is different
 if (np->pli_access)
  {
   /* AIV 06/06/08 - rare case this is xmr and it doesn't push */
   /* save_idp_ti is -1 because NPP not xmr must handle in pli code */
   /* __ld_netadr_tn checks to make sure __inst_mod is correct */
   save_inst_mdp = __inst_mod;
   __get_nets_containing_sy(np, &(in_mdp));
   __inst_mod = in_mdp;
   np_ti = __ld_netadr_tn(np);
   __inst_mod = save_inst_mdp;
   __emit_chk_ld_vpiputv_driver(np_ti, accum_sbpti);
  }
 switch ((byte) npp->npntyp) {
  case NP_CONTA:
   tmp_sbpti = gen_ld_stconta_driver(npp);
   break;
  case NP_TFRWARG:
   /* AIV 03/19/07 - removed these but are needed - were never tested */
   /* AIV 03/19/07 - removed these but are needed - were never tested */
   /* AIV 03/24/09 - for the same reason above code need to save/restore */
   /* proper module from containing net */
   /* AIV LOOKATME ???? */
   save_inst_mdp = __inst_mod;
   __get_nets_containing_sy(np, &(in_mdp));
   __inst_mod = in_mdp;
   tmp_sbpti = gen_ld_sttfrwarg_driver(npp);
   __inst_mod = save_inst_mdp;
   break;
  case NP_VPIPUTV:
   /* AIV 02/17/07 - these aren't at compile time */
   __case_terr(__FILE__, __LINE__);
   break;
  case NP_GATE:
   tmp_sbpti = gen_ld_stgate_driver(npp);
   break; 
  /* these are up to highconn strength output port drivers */
  case NP_ICONN: case NP_PB_ICONN:
   /* pb same except access the 2 known to be 1 bit PB exprs */
   tmp_sbpti = gen_ld_sticonn_up_driver(npp);
   break;
  case NP_MDPRT: case NP_PB_MDPRT:
   /* pb same except access the 2 known to be 1 bit PB exprs */
   tmp_sbpti = gen_ld_mdprt_down_driver(npp, TRUE);
   break;
  case NP_PULL:
   tmp_sbpti = gen_ld_stpull_driver(npp);
   break;
  /* TRAN impossible here */
  default: __case_terr(__FILE__, __LINE__);
 }

 /* if pushed, always pop before lhs cat extract */
 if (save_idp_ti != -1)
  {
   __gen_restore_idp(save_idp_ti);
  }
 if (nd_itpop)  __pop_itstk();

 /* first figure out region of being driven accum into net */
 if ((npauxp = npp->npaux) != NULL && npauxp->lcbi1 != -1)
  {
   i1 = npauxp->lcbi1;
   i2 = npauxp->lcbi2;

   /* know thing driving wire is 1 bit - will eval. to 1 bit */
   /* this is case for lhs concatenate to extract matching part of rhs */ 
   /* really just an addr add for svec */
   /* AIV 09/19/07 -  was passing the wrong width  */
   pselwid = i1 - i2 + 1; 
   tmp_sbpti = __gen_fradr_rhs_psel(np->srep, tmp_sbpti, pselwid, i1, i2);  
  }
 /* run non stren (hiz) competition update accumulator with result */
 gen_st_drvr_competition_upd(accum_sbpti, tmp_sbpti, np, npp); 
}

/*
 * gen vinsn to run stren competition between current accum and one driver 
 *
 * know runs in lhs net expr's itree context - but for XMR npp eval in 
 * rhs itree context - will have popped to put before calling this
 */
static void gen_st_drvr_competition_upd(int32 accum_sbpti, int32 drv_sbpti,
 struct net_t *np, struct net_pin_t *npp)
{
 int32 res_sbpti, con_apti, inum_ti, iofs_ti, ndx_apti;
 int32 lowbi, numbits, i1, i2, cint_ti;
 struct npaux_t *npauxp;

 if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1) numbits = np->nwid;
 else if (npauxp->nbi1 == -2 || npauxp->nbi1 == npauxp->nbi2.i) numbits = 1;
 else numbits = npauxp->nbi1 - npauxp->nbi2.i;

 if (__get_tnwid(drv_sbpti) < numbits)
  {
   /* widening copy where z's added */
   res_sbpti = gen_svec_widen(numbits, drv_sbpti, ST_HIZ);
  }
 else res_sbpti = drv_sbpti;

 /* entire wire */
 if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1)
  {
   /* notice order here match different interpret stren arg order */

   /* SJM 05/28/03 - for wider than 1 bit must use the vector combine form */
   /* otherwise the rhs only low bit is used wrongly for all bits */
   /* SJM 09/18/05 - was not using right intermediate result */
   __emit_stren_comb_bits(np->ntyp, accum_sbpti, np->nwid - 1, 0, res_sbpti,
    TRUE);
   return;
  }

 if (npauxp->nbi1 == -2)
  {
   /* this is per inst, depending on current lhs itree inst num variable */
   con_apti = __gen_contab_tn(npauxp->nbi2.xvi, WBITS, TRUE, FALSE,
    FALSE, SR_VEC);
   inum_ti = __emit_inum();
   cint_ti = __gen_cint_tn(8);
   iofs_ti = __emit_mult(WBITS, inum_ti, cint_ti);
   ndx_apti = __var_adradd_insn(SR_VEC, WBITS, con_apti, iofs_ti);

   __emit_stren_comb_bits(np->ntyp, accum_sbpti, ndx_apti, ndx_apti, res_sbpti,
    FALSE);
   return;
  }

 /* now all same - just calculate the fixed know at compile time indices */
 if (npauxp->lcbi1 != -1)
  {
   /* ALGORITHM: driver is entire rhs but accumulator to apply stren */
   /* competition algorithm to is part of lhs concat so need to select */
   /* section of entire rhs expression that matches lhs concat section */ 
   /* notice that rhs driver evaled into size that matches lhs concat */
   /* width no lhs concat component width */
   lowbi = npauxp->lcbi2;
  }
 else lowbi = -1;

 /* for bit select, i1 == i2 but otherwise the same */
 i1 = npauxp->nbi1;
 i2 = npauxp->nbi2.i;
   
//AIV? - what is the explanation for this
 /* adjust for lhs concat so low bit of rhs matches lhs cat wire section */
 /* AIV 09/07/06 this isn't needed and was wrong in all versions */
 /* if (lowbi != -1) { i1 += lowbi; i2 += lowbi; } */

 __emit_stren_comb_bits(np->ntyp, accum_sbpti, i1, i2, res_sbpti, TRUE);
}

/*
 * ROUTINES TO LOAD EACH TYPE OF MULTI FAN IN DRIVERS
 */

/*
 * gen insns to load a conta non stren driver npp 
 * returns tmp name result loaded into
 *
 * NOTICE - can't be used for conta initialize
 */
static int32 gen_ld_conta_driver(struct net_pin_t *npp)
{
 int32 blen, drv_apti, tmp_apti, lhs_srep, nbytes, srtyp;
 struct conta_t *cap;

 cap = npp->elnpp.ecap;
 if (cap->ca_pb_sim) cap = &(cap->pbcau.pbcaps[npp->pbi]);
 blen = cap->lhsx->szu.xclen;

 /* case 1: driver not stored, eval rhs expr */
 /* AIV 06/19/07 - was comparing ca_drv_ofs == 0 but was not linked */
 /* by here need to do if has delay or is mfi */
 lhs_srep = __get_lhs_srep(cap->lhsx, &nbytes);
 if (lhs_srep == SR_SCAL2S || lhs_srep == SR_BIT2S)
  {
   srtyp = SR_BIT2S;
  }
 else srtyp = SR_VEC;
 if (cap->ca_delrep == DT_NONE && !cap->lhsx->x_multfi) 
  {
   /* case 1b: lhs non stren */
   /* AIV 11/10/09 - want a vector here */
   tmp_apti = __gen_expr_eval(cap->rhsx, WANT_A_VEC);

   drv_apti = __gen_cnvt_srep_ifneeded(tmp_apti, lhs_srep, blen,
    cap->rhsx->has_sign, FALSE, TRUE);

   return(drv_apti);
  }

 drv_apti = __gen_conta_drvbp_tn(cap, srtyp);
 return(drv_apti);
}

/*
 * gen insns to load a conta non stren driver npp 
 * returns tmp name result loaded into
 *
 * NOTICE - can't be used for conta initialize
 */
static int32 gen_ld_stconta_driver(struct net_pin_t *npp)
{
 int32 drv_apti, drv_sbpti, tmp_apti, blen;
 struct conta_t *cap;

 cap = npp->elnpp.ecap;
 if (cap->ca_pb_sim) cap = &(cap->pbcau.pbcaps[npp->pbi]);
 blen = cap->lhsx->szu.xclen;

 /* case 1: driver not stored, eval rhs expr */
 /* AIV 06/19/07 - was comparing ca_drv_ofs == 0 but was not linked */
 /* by here need to do if has delay or is mfi */
 if (cap->ca_delrep == DT_NONE && !cap->lhsx->x_multfi) 
  {
   /* AIV 11/10/09 - want a vector here */
   tmp_apti = __gen_expr_eval(cap->rhsx, WANT_A_VEC);
   drv_apti = __gen_cnvt_srep_ifneeded(tmp_apti, SR_VEC, blen,
    cap->rhsx->has_sign, FALSE, TRUE);
  }
 else
  {
   /* know ca drv even for stren lhs stored as a/b since stren added */
   drv_apti = __gen_conta_drvbp_tn(cap, SR_VEC);
  }
 /* convert to stren and add in the conta stren */
 drv_sbpti = gen_st_standval(blen, drv_apti, cap->ca_stval);
 return(drv_sbpti);
}

/*
 * gen vinsns to load a tf_ task/func arg rw parameter driver
 * non stren version
 * AIV 03/19/07 - these routines were removed but are needed
 * this code hasn't been thourghly tested - may have problems
 */
static int32 gen_ld_tfrwarg_driver(struct net_pin_t *npp)
{
 int32 drv_apti, drvadr_ti, blen, npp_ti;
 struct tfrec_t *tfrp;
 struct tfarg_t *tfap;
 struct expr_t *xp;

 tfrp = npp->elnpp.etfrp;
 tfap = &(tfrp->tfargs[npp->obnum]);
 xp = tfap->arg.axp;
 blen = xp->szu.xclen;

 if (tfap->tfdrv_wp.wp == NULL)
  {
   /* case 1b: lhs non stren */
   drv_apti = __gen_expr_eval(xp, -1);

   if (blen != __get_tnwid(drv_apti)) __misc_terr(__FILE__, __LINE__);
   return(drv_apti);
  }

 npp_ti = __gen_npp_adr_tn(npp);
 drvadr_ti = __emit_ld_tfwarg_drvp(npp_ti, blen, SR_VEC);
 drv_apti = __gen_tn(SR_VEC, blen);
 __emit_get_perinst_val(drv_apti, drvadr_ti, blen);
 return(drv_apti);
}

/*
 * gen vinsns to load a tf_ task/func arg rw parameter driver
 * stren version
 */
static int32 gen_ld_sttfrwarg_driver(struct net_pin_t *npp)
{
 int32 drv_sbpti, npp_ti, sbpti, blen;
 struct tfrec_t *tfrp;
 struct tfarg_t *tfap;
 struct expr_t *xp;

 tfrp = npp->elnpp.etfrp;
 tfap = &(tfrp->tfargs[npp->obnum]);
 xp = tfap->arg.axp;
 blen = xp->szu.xclen;

 if (tfap->tfdrv_wp.wp == NULL)
  {
   /* case 1b: lhs non stren */
   drv_sbpti = gen_ndst_expr_eval(xp);
   if (blen != __get_tnwid(drv_sbpti)) __misc_terr(__FILE__, __LINE__);
   return(drv_sbpti);
  }
 /* case 2: multi-fi */
 npp_ti = __gen_npp_adr_tn(npp);
 sbpti = __emit_ld_tfwarg_drvp(npp_ti, xp->szu.xclen, SR_SVEC);

 /* if copy needed for stren vec must explicity gen the copy vinsn */
 drv_sbpti = gen_ld_is_svec_ofset(sbpti, 0, blen);
 return(drv_sbpti);
}

/*
 * load a svec (or sscal) ptr offset from a byte area base
 *
 * for getting stren bit selects and driving per inst byte addresses
 * only for const offsets known at compile time since declarative
 * itree context must correct (no XMRs)
 */
// AIV HERE PLI FIX?????????
static int32 gen_ld_is_svec_ofset(int32 sbp_ti, int32 bofs, int32 blen)
{
 int32 sbp_ofs_ti, inum_ti, iofs_ti, inst_sbp_ti, cint_ti;

 if (__inst_mod->flatinum == 1)
  {
   if (bofs == 0) return(sbp_ti);
   sbp_ofs_ti = __con_adradd_insn(SR_SVEC, blen, sbp_ti, bofs);
   return(sbp_ofs_ti);    
  }
 inum_ti = __emit_inum();

 if (blen > 1)
  {
   cint_ti = __gen_cint_tn(blen);
   iofs_ti = __emit_mult(WBITS, inum_ti, cint_ti);
  }
 else iofs_ti = inum_ti;

 inst_sbp_ti = __var_adradd_insn(SR_SVEC, blen, sbp_ti, iofs_ti);
 if (bofs == 0) return(inst_sbp_ti);

 sbp_ofs_ti = __con_adradd_insn(SR_SVEC, blen, inst_sbp_ti, bofs);
 return(sbp_ofs_ti);
}


/*
 * gen vinsns to eval gate driver - non stren
 */
static int32 gen_ld_gate_driver(struct net_pin_t *npp)
{
 int32 drv_apti, tmp_ti, gp_ti, nins, is_2state, srtyp;
 struct expr_t *xp;
 struct gate_t *gp;

 gp = npp->elnpp.egp;

 /* know driver always one bit - but some stren and some non stren */
 /* which is set from case */
 tmp_ti = -1;
 /* 12/5/05 - AIV FIXME lower this code uses constant info */
 /*  dumb to make scalar and later convert to svec */
 
 /* if 2-state get load as SR_SCAL2S */
 xp = gp->gpins[0];
 if (__is_expr_2state(xp)) is_2state = TRUE;
 else is_2state = FALSE;

 switch ((byte) gp->g_class) {
  case GC_LOGIC:
   /* know if driving non stren gate can't have stren */
   if (gp->g_hasst) __misc_terr(__FILE__, __LINE__);
   nins = gp->gpnum - 1;
   if (nins > 15)
    {
     gp_ti = __gen_gate_adr_tn(gp);
     tmp_ti = __emit_ld_logic_wide_driver(gp_ti, nins);
     tmp_ti = __emit_movw_fr_scal(WBITS, tmp_ti, FALSE);
    }
   else
    {
     tmp_ti = __gen_gate_output_value(gp, is_2state);
    }
   break;
  /* AIV 11/20/07 - these are all the same because the output value is no */
  /* longer packed */
  case GC_UDP:
  case GC_BUFIF:
  case GC_MOS: 
  case GC_CMOS:
   tmp_ti = __gen_gate_output_value(gp, FALSE);
   tmp_ti = __emit_movw_fr_scal(WBITS, tmp_ti, gp->g_hasst);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 /* know if driving non stren gate can't have stren */
 if (gp->g_hasst) __misc_terr(__FILE__, __LINE__);


 drv_apti = -1;
 /* rare case if gate output connected to wider var must widen driver */ 
 /* with z's - know never narrowing */
 if (gp->gpins[0]->szu.xclen > 1)
  {
   /* SJM 08/24/04 - LOOKATME ### ??? - is this right */ 
   if (is_2state) srtyp = SR_BIT2S;
   else srtyp = SR_VEC;
   drv_apti = __gen_cnvt_srep_ifneeded(tmp_ti, srtyp,
    gp->gpins[0]->szu.xclen, FALSE, FALSE, TRUE);
  }
 else drv_apti = tmp_ti;
 return(drv_apti);
}

/*
 * gen vinsns to eval gate driver - stren
 */
static int32 gen_ld_stgate_driver(struct net_pin_t *npp)
{
 int32 drv_sbpti, tmp_ti, gp_ti, has_stren, cint_ti, r1_ti, byte_ti;
 int32 nins, tmp2_ti;
 struct gate_t *gp;
 struct bblk_t *shft_bbp, *no_shft_bbp;

 gp = npp->elnpp.egp;

 has_stren = FALSE;
 tmp_ti = -1;
 /* know driver always one bit - but some stren and some non stren */
 /* which is set from case */
 switch ((byte) gp->g_class) {
  case GC_UDP:
   tmp_ti = __gen_gate_output_value(gp, FALSE);
  /* AIV 01/16/06 - stren case has handled wrong changed to mimic interp */
adjust_stren:
   if (gp->g_hasst) 
    {
     /* if (wrd != 2) wrd |= (gp->g_stval << 2L); */
     /* wrd = (word32) __stren_map_tab[wrd]; */
     no_shft_bbp = __alloc_bblk(FALSE);
     shft_bbp = __alloc_bblk(FALSE);
     cint_ti = __gen_cint_tn(2);
     /* AIV 12/13/07 - now need to do copies into a new tmp here */
     /* since tmp1 is a memory(idp area) value the copy was storing */
     /* into itself where it shouldn't be need tmp (reg) not memory */ 
     tmp2_ti = __gen_tn(SR_SSCAL, 1); 
     __emit_copy(WRDBYTES, tmp_ti, tmp2_ti);
     __emit_jmp_eq(no_shft_bbp, shft_bbp, tmp2_ti, cint_ti);

     __start_bblk(shft_bbp);
//AIV? - can be this better
     cint_ti = __gen_cint_tn(gp->g_stval << 2);
     r1_ti = __emit_mask_or(tmp2_ti, cint_ti);
     __emit_copy(WRDBYTES, r1_ti, tmp2_ti);

     __start_bblk(no_shft_bbp);
     tmp2_ti = __emit_stren_map_tab(tmp2_ti);
     has_stren = TRUE;
     /* tmp is now know to be tmp2_ti regardless of rt path */
     tmp_ti = tmp2_ti;
    }
   break;
  case GC_LOGIC:
   nins = gp->gpnum - 1;
   if (nins > 15)
    {
     gp_ti = __gen_gate_adr_tn(gp);
     tmp_ti = __emit_ld_logic_wide_driver(gp_ti, nins);
    }
   else
    {
     tmp_ti = __gen_gate_output_value(gp, FALSE);
    }
   goto adjust_stren;
  /* AIV 11/20/07 - these are all the same because the output value is no */
  /* longer packed */
  case GC_BUFIF:
  case GC_MOS: 
  case GC_CMOS:
   byte_ti = __gen_gate_output_value(gp, FALSE);
   /* AIV 06/18/07 - expecting a strength value of length 1 */
   tmp_ti = __gen_tn(SR_SVEC, 1); 
   __emit_copy(WRDBYTES, byte_ti, tmp_ti);
   has_stren = TRUE;
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 /* AIV 01/16/06 - stren case has handled wrong changed to mimic interp */
 if (!has_stren)
  {
   /* AIV 12/13/07 - now need to do copies into a new tmp here */
   /* since tmp1 is a memory(idp area) value the copy was storing */
   /* into itself where it shouldn't be need tmp (reg) not memory */ 
   no_shft_bbp = __alloc_bblk(FALSE);
   shft_bbp = __alloc_bblk(FALSE);
   cint_ti = __gen_cint_tn(2);
   tmp2_ti = __gen_tn(SR_SCAL, 1); 
   __emit_copy(WRDBYTES, tmp_ti, tmp2_ti);
   __emit_jmp_eq(no_shft_bbp, shft_bbp, tmp_ti, cint_ti);

   __start_bblk(shft_bbp);
   cint_ti = __gen_cint_tn((ST_STRVAL << 2));
   r1_ti = __emit_mask_or(tmp_ti, cint_ti); 
   __emit_copy(WRDBYTES, r1_ti, tmp2_ti);
   __start_bblk(no_shft_bbp);

   /* tmp is now know to be tmp2_ti regardless of rt path */
   tmp_ti = tmp2_ti;
  }

 /* rare case if gate output connected to wider var must widen driver */ 
 /* with z's - know never narrowing */
 if (gp->gpins[0]->szu.xclen > 1)
  {
   drv_sbpti = __gen_cnvt_srep_ifneeded(tmp_ti, SR_SVEC,
    gp->gpins[0]->szu.xclen, FALSE, FALSE, TRUE);
  }
 else drv_sbpti = tmp_ti;
 return(drv_sbpti);
}

/*
 * gen vinsns to load iconn hiconn fi>1 driver - down rhs is mod port
 * non stren version (for both entire port and per bit form)
 *
 * since down drivers not per inst - if OPEMPTY (not sure if possible)
 * there will be no npp driver
 */
static int32 gen_ld_iconn_up_driver(struct net_pin_t *npp)
{
 int32 drv_apti, tmp_apti, save_idp_ti, down_idp_ti, lhs_srep, nbytes, srtyp;
 struct mod_pin_t *mpp;
 struct expr_t *up_lhsx, *down_rhsx;
 struct inst_t *ip;
 struct mod_t *downmdp;
 struct itree_t *down_itp, *cur_itp;

 /* assign from down module port rhs into up iconn lhs expr. */
 /* driver is down module port - called with itree location of up */

 save_idp_ti = -1;
 /* inst mod of up expr known at compile time */
 /* DBG remove -- */
 cur_itp = __inst_ptr;
 if (cur_itp->in_its == NULL) __misc_terr(__FILE__, __LINE__);
 if (npp->elnpp.eii >= __inst_mod->minum)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 down_itp = &(cur_itp->in_its[npp->elnpp.eii]);
 ip = down_itp->itip;
 downmdp = ip->imsym->el.emdp;
 mpp = &(downmdp->mpins[npp->obnum]);
 if (npp->npntyp == NP_PB_ICONN)
  {
   mpp = &(mpp->pbmpps[npp->pbi]);
   up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
  }
 /* up expr just needed for getting width */
 else up_lhsx = ip->ipins[npp->obnum];
 down_rhsx = mpp->mpref; 

 /* AIV 05/01/07 - this is rarely needed - fixme */
 /* AIV 07/18/07 - new idp code needs to up inst context */
 /* AIV 07/09/08 - if only one instance set known inum to zero */
 /* this way no need to save/set idp */
 /* AIV 08/28/09 - if 64-bit large model avoid using fixed idpdat areas */
#ifdef __CVC32__
 if (downmdp->flatinum > 1)
#else
 if (downmdp->flatinum > 1 || __cvc_use_large_model)
#endif
  {
   down_idp_ti = __emit_todowniconn_inst(npp->elnpp.eii);
   gen_set_save_idp(down_idp_ti, &save_idp_ti, TRUE);
   __need_net_addr = TRUE;
  }
 else 
  {
   down_idp_ti = -1;
   __known_inum = 0;
  }
 /* SJM 03/09/03 - during code gen need down mod context */
 __push_itstk(downmdp->moditps[0]);

 /* AIV 11/10/09 - want a vector here */
 lhs_srep = __get_lhs_srep(up_lhsx, &nbytes);
 if (lhs_srep == SR_SCAL2S || lhs_srep == SR_BIT2S)
  {
   srtyp = SR_BIT2S;
  }
 else srtyp = SR_VEC;
 tmp_apti = __gen_expr_eval(down_rhsx, WANT_A_VEC);
 drv_apti = __gen_cnvt_srep_ifneeded(tmp_apti, srtyp, up_lhsx->szu.xclen,
  up_lhsx->has_sign, FALSE, TRUE);
 __need_net_addr = FALSE;

 if (down_idp_ti != -1)
  {
   __gen_restore_idp(save_idp_ti);
  }
 __known_inum = -1;

 /* restore the compile time code gen itree context */ 
 __pop_itstk();
 return(drv_apti);
}

/*
 * gen vinsns to load iconn hiconn fi>1 driver - down rhs is mod port
 * stren version for both entire port and per bit forms
 */
static int32 gen_ld_sticonn_up_driver(struct net_pin_t *npp)
{
 int32 drv_sbpti, rhs_sbpti, save_idp_ti, down_idp_ti;
 struct mod_pin_t *mpp;
 struct expr_t *up_lhsx, *down_rhsx;
 struct inst_t *ip;
 struct mod_t *downmdp;
 struct itree_t *down_itp, *cur_itp;

 /* assign from down module port rhs into up iconn lhs expr. */
 /* driver is down module port - called with itree location of up */

 save_idp_ti = -1;
 /* inst mod of up expr known at compile time */
 /* DBG remove -- */
 cur_itp = __inst_ptr;
 if (cur_itp->in_its == NULL) __misc_terr(__FILE__, __LINE__);
 if (npp->elnpp.eii >= __inst_mod->minum)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 down_itp = &(cur_itp->in_its[npp->elnpp.eii]);
 ip = down_itp->itip;
 downmdp = ip->imsym->el.emdp;
 mpp = &(downmdp->mpins[npp->obnum]);
 if (npp->npntyp == NP_PB_ICONN)
  {
   mpp = &(mpp->pbmpps[npp->pbi]);
   up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
  }
 /* up expr just needed for getting width */
 else up_lhsx = ip->ipins[npp->obnum];
 down_rhsx = mpp->mpref; 
 
 /* SJM 01/24/03 - must access driver in run time down itree context */
 /* SJM 03/09/03 - during code gen need down mod context */
 __push_itstk(downmdp->moditps[0]);
 /* AIV 05/01/07 - better way to save/restore only when needed ????? */
 /* AIV 07/18/07 - new idp code needs to up inst context */
 /* AIV 07/09/08 - if only one instance set known inum to zero */
 /* this way no need to save/set idp */
 /* AIV 08/28/09 - if 64-bit large model avoid using fixed idpdat areas */
#ifdef __CVC32__
 if (downmdp->flatinum > 1)
#else
 if (downmdp->flatinum > 1 || __cvc_use_large_model)
#endif
  {
   down_idp_ti = __emit_todowniconn_inst(npp->elnpp.eii);
   gen_set_save_idp(down_idp_ti, &save_idp_ti, TRUE);
   __need_net_addr = TRUE;
  }
 else 
  {
   down_idp_ti = -1;
   __known_inum = 0;
  }
 rhs_sbpti = gen_ndst_expr_eval(down_rhsx);

 /* AIV 01/25/06 - from interp if wide need to z widen */
 /* only if rhs too narrow, need to add in HIZ and maybe widen alloc area */
 /* if too wide just ignores high bytes */
 if (up_lhsx->szu.xclen > __get_tnwid(rhs_sbpti))
  {
   drv_sbpti = gen_svec_widen(up_lhsx->szu.xclen, rhs_sbpti, ST_HIZ);
  }
 else drv_sbpti = rhs_sbpti;
 __need_net_addr = FALSE;

 if (down_idp_ti != -1)
  {
   __gen_restore_idp(save_idp_ti);
  }
 __known_inum = -1;
 /* restore the compile time code gen itree context */ 
 __pop_itstk();
 return(drv_sbpti);
}

/*
 * gen insns to eval highconn rhs iconn connection that is driver
 * for input port of down mod port 
 *
 * for driver of down mdprt low conn expr, driver is the entire up 
 * highconn iconn expr (for drvrs of highconn concat caller selects section) 
 *
 * only difference for per bit form port is up driver needs per bit expr 
 *
 * notice for ports loads and drivers are reversed
 * also notice since down driver same for all mods, its width/type fixed
 *
 * LOOKATME - this is hard case because driver of down port npp comes
 * from high conn expr that may differ in size and contents (completely
 * different exprs possible) for every inst
 */
static int32 gen_ld_mdprt_down_driver(struct net_pin_t *npp, int32 is_stren)
{
 int32 ii, ii2;
 int32 drv_ti, inum_ti, bval, res_ti, drv2_ti;
 int32 num_highconns, some_unc, ndxjmp_nxti, nbytes, lhs_srep;
 size_t jtabsiz; 
 struct mod_t *downmdp, *up_mdp;
 struct mod_pin_t *mpp;
 struct expr_t *down_lhsx;
 struct bblk_t *end_bbp;

 drv_ti = -1;
 /* know down mod always same but input port up driver may not be */
 /* and these vinsns are being generated in context of down mod port */
 downmdp = __inst_ptr->itip->imsym->el.emdp;

 /* DBG remove -- */
 if (npp->obnum >= downmdp->mpnum) __misc_terr(__FILE__, __LINE__);
 /* --- */

 mpp = &(downmdp->mpins[npp->obnum]);
 if (npp->npntyp == NP_PB_MDPRT) mpp = &(mpp->pbmpps[npp->pbi]);

 /* DBG remove -- */
 if (downmdp->moditps[0] == NULL || downmdp->moditps[0]->up_it == NULL) 
  __misc_terr(__FILE__, __LINE__);
 /* -- */

 /* any one up inst mod needed - use 0th inst of down to up */
 up_mdp = downmdp->moditps[0]->up_it->itip->imsym->el.emdp;
 if (downmdp->flatinum == 1 || downmdp->flatinum == up_mdp->flatinum)
  {
   /* SJM - 12/16/05 - for OP EMPTY only, will load pointless hiz here */
   /* if all highconn same - for per inst case will just jump over */
   if (is_stren)
    {
     drv_ti = gen_ld_st1inst_mdprt_down_driver(npp, 0, downmdp, up_mdp);
     return(drv_ti);
    }
   else
    {
     drv_ti = gen_ld_1inst_mdprt_down_driver(npp, 0, downmdp, up_mdp);
     return(drv_ti);
    }
  }
 /* val -2 if unc., -1 if first, >= 0 is index of earlier same highconn */
 bval = gen_bld_peri_basendx(npp, downmdp);
 /* if all unconn return - nothing to generate */
 if (bval == -2)
  {
   drv_ti = gen_ld_1inst_mdprt_down_driver(npp, 0, downmdp, up_mdp);
   return(drv_ti);
  }
 else 
  {
   /* if large number of instances just flatten */
   if (bval == -1) goto flatten;
  }
 /* if all unc., nothing to generate */
 for (ii = 0; ii < downmdp->flatinum; ii++)
  {
   if (__jmpbase[ii] == -1) goto chk_1inst;
   if (__jmpbase[ii] == -2) continue;
   /* know earlier duplicated - can just ignore */
  }
 /* SJM 08/05/04 - needed to set drv ti to z's but does extra work */
 /* because getting here means all insts unc. */
 drv_ti = gen_ld_1inst_mdprt_down_driver(npp, 0, downmdp, up_mdp);
 return(drv_ti);

chk_1inst:
 /* if only 1 non -1, simple one inst case */
 /* can only happen if all but highconn itree loc, unc. */
 /* AIV 11/09/11 - this some_unc was set wrong - always was true */
 some_unc = FALSE;
 for (num_highconns = 0, ii2 = -1, ii = 0; ii < downmdp->flatinum; ii++)
  {
   if (__jmpbase[ii] == -1)
    { 
     num_highconns++; 
     ii2 = ii;
    }
   else if (__jmpbase[ii] == -2) some_unc = TRUE;
   /* know unc. highconn or earlier duplicated - can just ignore */
  }
 if (some_unc) num_highconns++;
 if (num_highconns == 1)
  {
   /* counting unc., all highconn same - use any of non unc. high conn */
   if (is_stren)
    {
     drv_ti = gen_ld_st1inst_mdprt_down_driver(npp, ii2, downmdp, up_mdp);
     return(drv_ti);
    }
   else
    {
     drv_ti = gen_ld_1inst_mdprt_down_driver(npp, ii2, downmdp, up_mdp);
     return(drv_ti);
    }
  }

flatten:
 /* AIV 05/08/07 - could make this a jump table per insts as well */
 /* code is relatively rare - leaving for now */
 /* plus would need to have the per insts port functions return a value */
 /* maybe just do for wide??????? */


 /* need jump table because more than 1 different high conn */ 
 /* unc. have jump to here in jump table */
 /* this is jmp tab labref can't be optimized away */
 /* when label is gened the vinsn jmptab bit set so only 1 needed */
 end_bbp = __alloc_bblk(FALSE);

 /* alloc the jump table - every element filled below */ 
 jtabsiz = downmdp->flatinum;
 if (jtabsiz >= __ndxjmp_bbtab_siz) __grow_ndxjmpbbtab(jtabsiz);

 /* fill i jmp lab tab with labref's for each entry in table */ 
 for (ndxjmp_nxti = 0, ii = 0; ii < downmdp->flatinum; ii++) 
  {
   if (__jmpbase[ii] == -2)
    {
     /* case 1: unc. highconn - mark so will fill with offset past end */
     __ndxjmp_bbtab[ndxjmp_nxti++] = end_bbp;
     continue;
    }
   if (__jmpbase[ii] >= 0)
    {
     /* case 2: vinsns for this iop already gened */ 
     /* set to label ref of first - know exists since earlier in array */
     __ndxjmp_bbtab[ndxjmp_nxti++] = __ndxjmp_bbtab[__jmpbase[ii]];
     continue;
    }
   __ndxjmp_bbtab[ndxjmp_nxti++] = __alloc_bblk(FALSE);
  } 
 inum_ti = __emit_inum();

 /* SJM 01/23/07 - since building new bigger tab with non dup sets */
 /* do not alloc - just pass the filled reused global ndx jmp tab */ 
 __emit_ndx_jmp(inum_ti, __ndxjmp_bbtab, jtabsiz);


 /* AIV 06/01/11 - this was always wrong.  Need to generate a tmp and copy */
 /* in value for the return value */
 down_lhsx = mpp->mpref; 
 /* get the tmp type to return */
 if (is_stren)
  {
   if (down_lhsx->szu.xclen == 1) lhs_srep = SR_SSCAL;
   else lhs_srep = SR_SVEC;
   nbytes = down_lhsx->szu.xclen;
  }
 else
  {
   lhs_srep = __get_lhs_srep(down_lhsx, &nbytes);
  }

 /* AIV 01/25/12 - this should be down_lhsx->szu.xlcen - not nbytes */
 res_ti = __gen_tn(lhs_srep, down_lhsx->szu.xclen);
 /* gnerate the mdprt np change for each highconn */
 for (ii = 0; ii < downmdp->flatinum; ii++) 
  {
   if (__jmpbase[ii] != -1) continue;

   /* SJM 01/23/07 - since re-using ndx jmp bbtab can be used here */
   __start_bblk(__ndxjmp_bbtab[ii]);

   /* case 3: gen mdprt np change for one highconn loc */ 
   /* this generates the per inst area for each inst */
   /* SJM 08/24/04 - notice because of formal tmp tab everyone same */
   if (is_stren)
    {
     drv_ti = gen_ld_st1inst_mdprt_down_driver(npp, ii, downmdp, up_mdp);
    }
   else
    {
     drv_ti = gen_ld_1inst_mdprt_down_driver(npp, ii, downmdp, up_mdp);
    }
   /* leaving this check for now better be returning the same type */ 
   /* DBG remove -- */
   drv2_ti = __gen_cnvt_srep_ifneeded(drv_ti, lhs_srep,
       down_lhsx->szu.xclen, down_lhsx->has_sign, FALSE, TRUE);
   if (drv2_ti != drv_ti) __misc_terr(__FILE__, __LINE__);
   /* ----- */

   /* copy the value to the result */
   __emit_copy(nbytes, drv_ti, res_ti);

   if (ii != downmdp->flatinum - 1) __emit_jmp(end_bbp);
  }
 __start_bblk(end_bbp);
 return(res_ti);
}

/*
 * gen insns to eval highconn rhs iconn connection that is driver
 * for 1 inst (actually per static tree high mod type)
 */
static int32 gen_ld_1inst_mdprt_down_driver(struct net_pin_t *npp,
 int32 ii, struct mod_t *downmdp, struct mod_t *upmdp)
{
 int32 drv_apti, drv_bpti, up_rhs_apti, up_idp_ti;
 int32 save_idp_ti, lhs_srep, nbytes, want_a_vec;
 struct itree_t *itp;
 struct inst_t *ip;
 struct expr_t *up_rhsx, *down_lhsx;
 struct mod_pin_t *mpp;

 mpp = &(downmdp->mpins[npp->obnum]);
 down_lhsx = mpp->mpref; 
 itp = downmdp->moditps[ii];
 /* this is an instance of mod containing rhs output port load */
 ip = itp->itip;
 
 /* since ip comes from this insts highconn, each inst may differ */
 if (npp->npntyp == NP_PB_MDPRT)
  {
   up_rhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
  }
 /* up expr just needed for getting width */
 else up_rhsx = ip->ipins[npp->obnum];

 lhs_srep = __get_lhs_srep(down_lhsx, &nbytes);
 if (up_rhsx->optyp == OPEMPTY)
  {
   /* SJM 12/16/05 - FIXME - for now making z - but since only seen for */
   /* non per inst case, should just not do the stren competition */
   /* but for now trying to use flow graph optimizer to fix */
   /* notice even if non stren scalar must eval as a/b vec part */ 

   nbytes = wlen_(down_lhsx->szu.xclen)*WRDBYTES;
   drv_apti = __gen_tn(lhs_srep, down_lhsx->szu.xclen);
   /* AIV 02/24/12 - need to check for scalar 2 state here as well */
   if (lhs_srep == SR_BIT2S || lhs_srep == SR_SCAL2S)
    {
     /* to set to z just zero a part and set all 1 to the b part */
     __emit_store_cint(drv_apti, 0, nbytes);
    }
   /* AIV 01/25/12 - this can be scalar here just set to 'x' */
   else if (lhs_srep == SR_SCAL || lhs_srep == SR_SSCAL)
    {
     /* just set to 'x' (3) */
     __emit_store_cint(drv_apti, 3, 1);
    }
   else
    {
     /* to set to z just zero a part and set all 1 to the b part */
     __emit_store_cint(drv_apti, 0, nbytes);
     drv_bpti = __get_bpti(drv_apti);
     __emit_setall1(drv_bpti, nbytes);
    }
   return(drv_apti);
  }

 /* the change itree to mod up input port driver same for all insts */
 /* AIV 05/01/07 - no need to save istk info here - remove save/restore */
 /* AIV 07/18/07 - new idp code needs to up inst context */
//AIV IDP FIXME CVC - doesn't this need to save/restore idp here ???
 up_idp_ti = __emit_toupmdprt_inst();
 save_idp_ti = -1;
 /* AIV 07/09/08 - if more than one instance and multfi need to save idp */
 /* AIV 01/11/09 - this was wrong flatinum was usually one so this worked */
 /* however rare case which has flatinum == 1 (assign to input) was wrong */
 /* so was never restoring idp reg for this case */
 /* if (down_lhsx->x_multfi && downmdp->flatinum > 1) */
 if (down_lhsx->x_multfi) 
  {
   gen_set_save_idp(up_idp_ti, &save_idp_ti, TRUE);
   __need_net_addr = TRUE;
  }
 else __memloc_emit_set_idp(up_idp_ti);

 /* SJM 03/09/03 - during code gen need down mod context */
 __push_itstk(upmdp->moditps[0]);

 /* AIV 06/01/11 - should choose correct type base on lhs here */
 want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : -1;
 up_rhs_apti = __gen_expr_eval(up_rhsx, want_a_vec);
 /* AIV 04/25/07 - was converting uncorrectly into a SR_SVEC */
 drv_apti = __gen_cnvt_srep_ifneeded(up_rhs_apti, lhs_srep,
  down_lhsx->szu.xclen, down_lhsx->has_sign, FALSE, TRUE);

 if (save_idp_ti != -1)
  {
   __gen_restore_idp(save_idp_ti);
  }

 __need_net_addr = FALSE;

 /* restore to input port down mod port lhs itree loc to store */
 __pop_itstk();
 return(drv_apti);
}

/*
 * gen insns to eval highconn rhs iconn connection that is driver
 * for 1 inst (actually per static tree high mod type)
 */
static int32 gen_ld_st1inst_mdprt_down_driver(struct net_pin_t *npp,
 int32 ii, struct mod_t *downmdp, struct mod_t *upmdp)
{
 int32 drv_sbpti, up_rhs_sbpti, srep, up_idp_ti;
 int32 save_idp_ti;
 struct itree_t *itp;
 struct inst_t *ip;
 struct expr_t *up_rhsx, *down_lhsx;
 struct mod_pin_t *mpp;

 mpp = &(downmdp->mpins[npp->obnum]);
 down_lhsx = mpp->mpref; 
 itp = downmdp->moditps[ii];
 /* this is an instance of mod containing rhs output port load */
 ip = itp->itip;
 
 /* since ip comes from this insts highconn, each inst may differ */
 if (npp->npntyp == NP_PB_MDPRT)
  {
   up_rhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
  }
 /* up expr just needed for getting width */
 else up_rhsx = ip->ipins[npp->obnum];

 if (up_rhsx->optyp == OPEMPTY)
  {
   /* SJM 12/16/05 - FIXME - for now making z - but since only seen for */
   /* non per inst case, should just not do the stren competition */
   /* but for now trying to use flow graph optimizer to fix */

   drv_sbpti = __gen_tn(SR_SVEC, down_lhsx->szu.xclen);
   /* to set to z just zero a part and set all 1 to the b part */
//AIV? - this is not really in place
   __emit_setstren(drv_sbpti, ST_HIZ, down_lhsx->szu.xclen);
   return(drv_sbpti);
  }

 /* AIV 07/18/07 - new idp code needs to up inst context */
//AIV IDP FIXME CVC - doesn't this need to save/restore idp here ???
 up_idp_ti = __emit_toupmdprt_inst();

 save_idp_ti = -1;

 /* AIV 07/09/08 - if more than one instance and multfi need to save idp */
 /* AIV 01/11/09 - this was wrong flatinum was usually one so this worked */
 /* however rare case which has flatinum == 1 (assign to input) was wrong */
 /* so was never restoring idp reg for this case */
 if (down_lhsx->x_multfi)
  {
   gen_set_save_idp(up_idp_ti, &save_idp_ti, TRUE);
   __need_net_addr = TRUE;
  }
 else __memloc_emit_set_idp(up_idp_ti);

 /* the change itree to mod up input port driver same for all insts */
 /* AIV 05/01/07 - no need to save istk info here - remove save/restore */
 /* SJM 03/09/03 - during code gen need down mod context */
 __push_itstk(upmdp->moditps[0]);

 up_rhs_sbpti = gen_ndst_expr_eval(up_rhsx);
 if (down_lhsx->szu.xclen == 1) srep = SR_SSCAL; else srep = SR_SVEC;
 drv_sbpti = __gen_cnvt_srep_ifneeded(up_rhs_sbpti, srep,
  down_lhsx->szu.xclen, down_lhsx->has_sign, FALSE, TRUE);

 if (save_idp_ti != -1)
  {
   __gen_restore_idp(save_idp_ti);
  }

 __need_net_addr = FALSE;

 /* restore to input port down mod port lhs itree loc to store */
 __pop_itstk();
 return(drv_sbpti);
}

/*
 * gen insns to compute and return constant pull stren tmp of right width
 * always stren form only
 */
static int32 gen_ld_stpull_driver(struct net_pin_t *npp)
{
 int32 drv_sbpti, stval, srep;
 struct expr_t *ndp;
 struct gate_t *gp;

 gp = npp->elnpp.egp;
 ndp = gp->gpins[npp->obnum];
 /* get pull out lhs wire or select */
 stval = (gp->g_stval << 2) | npp->pullval;
 if (ndp->szu.xclen == 1) srep = SR_SSCAL; else srep = SR_SVEC;
 drv_sbpti = __gen_tn(srep, ndp->szu.xclen);
 __emit_setstren(drv_sbpti, stval, __get_tnwid(drv_sbpti));
 return(drv_sbpti);
}

/*
 * ROUTINES TO GEN VINSNS FOR DCE PROCESSING
 */

/*
 * gen insns for 1 regs all dces - this also builds the flow graph
 * if no dces or not reg will not be called
 */
static void gen_dce_flowg(struct net_t *np)
{
 struct flowg_t *fgp;
 struct bblk_t *regdce_bbp;

 /* alloc and link on front of net's flow graph list */
 fgp = __alloc_flowg(FLOWG_DCE);
 add_flowg_to_netfg_list(np, fgp);
 __cur_flowg = fgp;
 __cur_bbp = NULL;

 regdce_bbp = __alloc_bblk(FALSE);
 /* SJM 02/24/06 - need after suspend bit on for any entry from scheduler */
 /* although no cross jump processing for these */
 regdce_bbp->after_suspend = TRUE; 
 __start_bblk(regdce_bbp); 

 __cur_ifrom_u.from_np = np;
 /* this handles entry to compiled code - set changed rng, cntxt */
 __emit_enter_decl(np);

 /* for tmps need to record if dce or npp base */
 gen_1net_wakeup_insns(np, -1, -1, TRUE, FALSE);

 /* return on finish is back to run time scheduler */
 __emit_complete();
}

/*
 * gen vm insns for wakeup of dces 
 *
 * notice unlike old vinsns code, this is modified from interpreter
 */
static int32 gen_1net_wakeup_insns(struct net_t *np, int32 i1, int32 i2, 
 int32 range_check, int32 processing_pnd0s)
{
 int32 match_idp_ti, in_range;
 struct itree_t *itp;
 struct dcevnt_t *dcep;
 struct bblk_t *after_bbp, *dce_typ_bbp;
 
 in_range = FALSE;
 for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt) 
  {
   /* AIV 02/29/08 - if merged skip all are triggered off one dce edge */
   if (dcep->merged) continue;

   /* DBG remove -- */
   if (dcep->dci2.xvi == -2) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (i1 != -1)
    {
     if (dcep->dci1 != -1)
      {
       if (i1 < dcep->dci2.xvi || i2 > dcep->dci1) continue;
      }
    }
   in_range = TRUE;
   after_bbp = __alloc_bblk(FALSE);

   if (dcep->dce_1inst && __inst_mod->flatinum > 1)
    {
     dce_typ_bbp = __alloc_bblk(FALSE);

     itp = (struct itree_t *) dcep->dce_matchu.idp;
     match_idp_ti = __gen_mdata_value(itp);
     __emit_jmp_idp_eq(dce_typ_bbp, after_bbp, match_idp_ti); 
     __start_bblk(dce_typ_bbp);
    }

   gen_1dce_trigger_insns(np, dcep, after_bbp, range_check, processing_pnd0s);


   /* SJM 07/27/05 - even when skip must move to next one */ 
   /* each one is filtered and move to test following one if no match */
   __start_bblk(after_bbp);
  }
 return(in_range);
}

/*
 * gen vm insns for wakeup triggering of all dces for one net 
 *
 * notice unlike old vinsns code, this is modified from interpreter
 */
static void gen_1dce_trigger_insns(struct net_t *np, struct dcevnt_t *dcep,
 struct bblk_t *after_bbp, int32 range_check, int32 processing_pnd0s)
{
 switch ((byte) dcep->dce_typ) {
  case DCE_RNG_INST:
   /* SJM 07/19/04 - FIXME - need to determine if rng possible at run time */
   /* if dcep is entire net, do not need rng filter */
   /* DBG remove -- */
   if (dcep->dci1 == -1) __misc_terr(__FILE__, __LINE__);
   /* -- */
   if (range_check)
    {
     gen_decl_outofrng_tst(dcep, dcep->dci1, dcep->dci2, after_bbp, TRUE);
    }
   /* FALLTHRU */
  case DCE_INST:
   gen_dce_inst(np, dcep, after_bbp, processing_pnd0s);
   break;
  case DCE_RNG_MONIT:
   if (range_check)
    {
     /* use standard routine even though know dci1 of -2 impossible */
     gen_decl_outofrng_tst(dcep, dcep->dci1, dcep->dci2, after_bbp, TRUE);
    }
   /* FALLTHRU */
  case DCE_MONIT:
   gen_dce_monit(dcep, after_bbp);
   break;
  case DCE_RNG_QCAF:
   if (range_check)
    {
     /* use standard routine even though know dci1 of -2 impossible */
     gen_decl_outofrng_tst(dcep, dcep->dci1, dcep->dci2, after_bbp, TRUE);
    }
   /* FALLTHRU */
  case DCE_QCAF:
   gen_dce_qcaf(dcep, after_bbp);
   break;
  /* AIV 02/19/07 - no pli currently compiled in at compile time */
  case DCE_RNG_PVC:
  case DCE_PVC:
  case DCE_RNG_CBVC:
   __case_terr(__FILE__, __LINE__);
   break;
  case DCE_CBF: case DCE_RNG_CBF: case DCE_CBR: case DCE_RNG_CBR:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * gen vm insns for dce inst event control - range filtering done
 */
static void gen_dce_inst(struct net_t *np, struct dcevnt_t *dcep,
 struct bblk_t *after_bbp, int32 processing_pnd0s)
{
 int32 nd_itpop, oval_ti, nval_ti, nxttev_ti;
 int32 emask_ti, schd_tev_ti, cint_ti, cp_nval_ti, tevp_reg_ti;
 int32 repcnt_ti, dec_ti, nd_rt_itpop, save_idp_ti, idp_ti; 
 int32 xedge_ti, ndx_ti;
 struct delctrl_t *dctp;
 struct bblk_t *chk_edge_bbp, *chk_rep_bbp, *trigger_bbp, *do_pop_bbp;
 struct mod_t *ref_in_mdp;
 struct itree_t *itp;
#ifdef __XPROP__
 int32 srep, stp_ent_ti, sset_to_ti, xprop_ent_ti;
 int32 t1_ti, set_ti, skip_x_edge, xtevp_ti;
 struct bblk_t *xz_bbp, *noxz_bbp, *new_val_bbp, *op_val_bbp;
 struct ctev_t *ctevp;
#endif
 
 /* if dcep is base merged edge handle as seperate case */
 if (dcep->merged_count != -1)
  {
   gen_dce_inst_duplicates(np, dcep, after_bbp, processing_pnd0s);
   return;
  }
 dctp = dcep->st_dctrl;
 /* AIV 03/09/09 - if it is an merged always block and doesn't need thread */
 /* only gen code for merge header dctp */
 if (!dctp->needs_thread && dctp->head_dctp != NULL) return;

 /* will stay as -1 if not used, but since not used ok */
 oval_ti = nval_ti = -1; 
 ndx_ti = -1;
 nd_itpop = FALSE;
 xedge_ti = -1;
 if (dcep->prevval_ofs != 0)
  {
   /* AIV 12/11/07 - this can now be an array - handle like a vec */
   if (np->n_isarr)
    {
     xedge_ti = gen_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), after_bbp,
      dctp);
    }
   else if (!np->n_isavec)
    {   
#ifdef __XPROP__
     /* AIV 02/24/12 - if xprop always load oval_ti/nval_ti here */ 
     if (dctp->xprop_xedge_actionst != NULL)
      {
       gen_scal_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), after_bbp);
      }
     else
#endif
     /* notice unlike interpreter, both stren/non stren scalar gen same */
     /* AIV 06/06/08 - only need to filter if has an edge or stren */
     if (dcep->dce_edge || np->n_stren)
      {
       gen_scal_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), after_bbp);
      }
     /* AIV 07/31/07 - now if xmr must copy the nval into the saved local */
     /* tmp area if it is and idp offset */
     if (dcep->dce_xmrtyp != XNP_LOC &&
       (nval_ti != -1 && __tntab[nval_ti].comlab_typ == COMLAB_IDP)) 
      { 
       if (np->n_2state) cp_nval_ti = __gen_tn(SR_SCAL2S, 1);
       else cp_nval_ti = __gen_tn(SR_SCAL, 1);
       __emit_copy(WRDBYTES, nval_ti, cp_nval_ti);
       nval_ti = cp_nval_ti;
      }
    }
   else
    {
     if (!np->n_stren)
      {
       xedge_ti = gen_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), 
         after_bbp, dctp);
      }
     else 
      {
       xedge_ti = gen_stren_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), 
         after_bbp, dctp);
      }
    }
  }
 nd_itpop = nd_rt_itpop = FALSE;
 save_idp_ti = -1;
 if (dcep->dce_1inst)
  {
   /* AIV 02/19/07 - save the current inum and make the inum the ref inum */
   /* need to save to put back to current inum */
   /* no need to push dce refiti just need to have inum */
   /* AIV 05/06/07 - don't want the rhs to be folded constant value */
   /* AIV FIXME - this wouldn't be need if all unnecessary saves removed */
//AIV IDP FIXME CVC - why was this not saving in the old code???
   itp = (struct itree_t *) dcep->dce_refu.idp;
   idp_ti = __gen_mdata_value(itp);
   gen_set_save_idp(idp_ti, &save_idp_ti, TRUE);
   /* SJM 09/30/05 - need compile time push too */
   __push_itstk(itp);
   nd_itpop = TRUE;
   nd_rt_itpop = TRUE;
  }
 else if (dcep->dce_xmrtyp != XNP_LOC) 
  {
   /* last insn emitted here must be jump */
   /* notice this is after because if this fails, no push */
   /* SJM 01/23/06 - this starts a bblk for match push jump */ 
   idp_ti = gen_match_targ_to_ref(dcep->dce_xmrtyp, dcep->dceu.dcegrp, 
    after_bbp);
   gen_set_save_idp(idp_ti, &save_idp_ti, TRUE);

   /* 01/23/06 - this is compile time push but can't use push wrk itstk */
   ref_in_mdp = dcep->dceu.dcegrp->gin_mdp;
   __push_itstk(ref_in_mdp->moditps[0]);
   nd_itpop = TRUE;
   nd_rt_itpop = TRUE;
  }

 chk_edge_bbp = __alloc_bblk(FALSE);
 /* tevp tmp set to -1 if not armed else armed event tab number */ 
 schd_tev_ti = __gen_dce_schd_tev(dctp);

 do_pop_bbp = __alloc_bblk(FALSE);
 tevp_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, schd_tev_ti);
#ifdef __XPROP__
 /* skipping events as well */
 skip_x_edge = FALSE;
  if (np->ntyp == N_EVENT)
   {
    skip_x_edge = TRUE;
   }
  //AIV FIXME - shouldn't set xedge_ti then
  /* cannot handle variable arrays for now */
  if (np->n_isarr && dcep->dci2.i == -1)
   {
    skip_x_edge = TRUE;
   }
  /* if no vector edge dectection continue on */
  if (__no_xprop_vectors && np->n_isavec && !dcep->dce_edge) 
   {
    /* DBG remove -- */ 
    if (xedge_ti != -1) __misc_terr(__FILE__, __LINE__);
    /* ----- */ 
    skip_x_edge = TRUE;
   }
  /* if no negedge/posedge skip x edge dectection */
  if (__xprop_pos_neg_only && !dcep->dce_edge)
   {
    /* DBG remove -- */ 
    if (xedge_ti != -1) __misc_terr(__FILE__, __LINE__);
    /* ----- */ 
    skip_x_edge = TRUE;
   }

 /* AIV 03/27/12 if first xedge is set the next possible edge may be real */
 /* so may have to put back regular non-xprop stmt enter point */
 /* if clk triggers xedge and rst is a real edge - no xprop */
 /* always (posedge clk or negedge rst) */
 /* if single always(clk) do not use this code */
 xtevp_ti = -1;
 if (!skip_x_edge && dctp->xprop_xedge_actionst != NULL && dctp->d_gt_one > 1)
  {
   ctevp = dctp->head_ctevp;
   /* DBG remove -- */ 
   if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */ 
   xtevp_ti = __gen_ctevp_adr_tn(ctevp);
  }
 else
  {
   __emit_jmp_0(do_pop_bbp, chk_edge_bbp, tevp_reg_ti);
  }
#else
 /* AIV 12/29/08 - should be jmp_0 here slightly better code - not eq 0 */
 /* also better to load ctevp to a reg here */
 __emit_jmp_0(do_pop_bbp, chk_edge_bbp, tevp_reg_ti);
#endif

 __start_bblk(chk_edge_bbp);
 if (dcep->dce_edge)
  {
   if (dcep->dce_expr != NULL)
    {
     gen_filter_edge_expr(dcep, &(oval_ti), &(nval_ti), do_pop_bbp, np);
    }
   /* AIV 10/14/08 - this routine now has two jump tables - pos/neg */
   /* that way there is no need for masking at runtime */
   emask_ti = __emit_compute_emask(np, oval_ti, nval_ti, dcep->dce_edgval,
    &ndx_ti);
   chk_rep_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(do_pop_bbp, chk_rep_bbp, emask_ti);
   __start_bblk(chk_rep_bbp);
  }

 if (dctp->repcntx != NULL)
  {
   repcnt_ti =  __gen_dctrl_rep_bp(dctp);
   cint_ti = __gen_cint_tn(1);
   dec_ti = __emit_sub(WBITS, repcnt_ti, cint_ti);
   __emit_copy(WRDBYTES, dec_ti, repcnt_ti);
   trigger_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(trigger_bbp, do_pop_bbp, dec_ti);
   __start_bblk(trigger_bbp);
  }
#ifdef __XPROP__
 /* if has xprop xedge dectection must be done */
 if (dctp->xprop_xedge_actionst != NULL)
  {
   stp_ent_ti = __gen_proc_enter_adr_tn(dctp->actionst);
   sset_to_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, stp_ent_ti);
   /* AIV 03/01/12 - this wasn't right if another thing such as a scalar */
   /* triggered it need to put the stmt pointer back to the non-xprop */
   /* statement enter location everytime */
   if (skip_x_edge) goto skip_x_check;

   noxz_bbp = __alloc_bblk(FALSE);
   xz_bbp = __alloc_bblk(TRUE);

   srep = np->srep;
   /* if xedge_ti is set (vectors) then check against set tmp */
   if (xedge_ti != -1)
    {
     /* DBG remove -- */ 
     if (np->nwid == 1) __misc_terr(__FILE__, __LINE__);
     /* ----- */ 
 
     __emit_jmp_0(xz_bbp, noxz_bbp, xedge_ti);
    }
   else 
    {
     /* DBG remove -- */ 
     if (nval_ti == -1 || oval_ti == -1) __misc_terr(__FILE__, __LINE__);
     /* ----- */ 

     /* __is_xedge_tab[nval | (oval << 2)]; */
     /* if posedge/negedge ndx will only be compute once */
     /* AIV FIXME - this can really just use one table lookup */
     /* say x changes all return values > 1 */
     if (ndx_ti == -1) 
      {
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, oval_ti);
       ndx_ti = __emit_bin_bitor(WBITS, nval_ti, t1_ti);
      }
     xedge_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, ndx_ti, 
        NLO_IS_XEDGE_TAB);
     __emit_jmp_0(noxz_bbp, xz_bbp, xedge_ti);
    }

   __start_bblk(xz_bbp);

   if (!np->n_isavec)
    {
     /* DBG remove -- */ 
     if (nval_ti == -1) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     set_ti = -1;
     /* always set the edge value */
     if (dcep->dce_edge)
      {
       /* only record if need to */
       if (__needs_xedge_net_record(dctp))
        {
         if (dcep->dce_edgval == E_POSEDGE) set_ti = __gen_cint_tn(1);
         else if (dcep->dce_edgval == E_NEGEDGE) set_ti = __gen_cint_tn(0);
         else __misc_terr(__FILE__, __LINE__);
         __emit_xprop_set_xedge_net(dctp->xprop_xedge_actionst, np, set_ti);
        }
      }
     else 
      {
       /* set = !oval */
       new_val_bbp = __alloc_bblk(FALSE);
       op_val_bbp = __alloc_bblk(FALSE);
       /* init to new val */
       set_ti = __gen_tn(SR_SCAL2S, 1);
       __emit_copy(WRDBYTES, nval_ti, set_ti);
       /* if oval == 3 - just set to new val */
       cint_ti = __gen_cint_tn(3);
       __emit_jmp_eq(new_val_bbp, op_val_bbp, cint_ti, oval_ti);
       __start_bblk(op_val_bbp);
       __emit_store_cint(set_ti, 0, WRDBYTES);
       __emit_testl(oval_ti);
       __emit_st_sete(CC_JE, set_ti);
       __start_bblk(new_val_bbp);
       __emit_xprop_set_xedge_net(dctp->xprop_xedge_actionst, np, set_ti);
      }

    }

   /* DBG remove -- */ 
   if (dcep->st_dctrl->dc_nblking) __misc_terr(__FILE__, __LINE__);
   /* ----- */ 
   xprop_ent_ti = __gen_proc_enter_adr_tn(dctp->xprop_xedge_actionst);
   __st_insn(I_STOREA, AM_REG, xprop_ent_ti, AM_REG, sset_to_ti);

  /* AIV 03/28/12 - may have to set stmt pointer back to non-xprop */
  /* and check for NULL tevp */
  if (xtevp_ti != -1)
   {
    struct bblk_t *do_trigger_bbp, *check_null_bbp;

    do_trigger_bbp = __alloc_bblk(FALSE);
    check_null_bbp = __alloc_bblk(FALSE);
    /* tevp can be NULL here */
    __start_bblk(check_null_bbp);
    __emit_jmp_0(do_pop_bbp, do_trigger_bbp, tevp_reg_ti);

    __start_bblk(noxz_bbp);
    /* set back to normal stmt enter point */
    __emit_set_tev_enter_adr_xprop(xtevp_ti, sset_to_ti);
    __emit_jmp(check_null_bbp);

    __start_bblk(do_trigger_bbp);
   }
  else __start_bblk(noxz_bbp);


skip_x_check:

   if (processing_pnd0s)
    {
     __emit_set_tev_enter_adr_xprop(tevp_reg_ti, sset_to_ti);
     gen_trigger_ectrl_pnd0(tevp_reg_ti, dctp);
    }
   else __emit_trigger_ectrl_xprop(tevp_reg_ti, dctp, sset_to_ti);

   nxttev_ti = __gen_cint_tn((word32) NULL);
   __emit_copy(WRDBYTES, nxttev_ti, schd_tev_ti);

   __start_bblk(do_pop_bbp);

   if (nd_itpop) __pop_itstk();
   if (nd_rt_itpop) __gen_restore_idp(save_idp_ti);

   return;
  }
#endif

 /* AIV 02/20/07 - seperated the non-blocking case */
 if (dcep->st_dctrl->dc_nblking)
  {
   __emit_nb_trigger_ectrl(tevp_reg_ti);
  }
 else
  {
   if (processing_pnd0s)
    {
     gen_trigger_ectrl_pnd0(tevp_reg_ti, dctp);
    }
   else __emit_trigger_ectrl(tevp_reg_ti, dctp);
  }
 nxttev_ti = __gen_cint_tn((word32) NULL);
 __emit_copy(WRDBYTES, nxttev_ti, schd_tev_ti);

 __start_bblk(do_pop_bbp);

 if (nd_itpop) __pop_itstk();
 if (nd_rt_itpop) 
  {
   __gen_restore_idp(save_idp_ti);
  }
}

/*
 * to the trigger ectrl where it is known to be processing pnd0
 *
 * execute the following code - basically just add to the list
 *
 * __p0_te_hdrp = tevp;
 * if (__p0_te_hdrp == NULL) __p0_te_endp = tevp; 
 * else 
 * { 
 *  tevp->tenxtp = __p0_te_hdrp; 
 * }
 */
static void gen_trigger_ectrl_pnd0(int32 tevp_reg_ti, struct delctrl_t *dctp)
{
 int32 hdrp_ti;
 size_t offset;
 struct bblk_t *empty_bbp, *next_bbp, *after_bbp;
 struct tev_t *tevp;
 
 /* AIV 12/15/10 - mark this event as touced */
 if (__event_coverage) __emit_event_coverage(dctp);
 empty_bbp = __alloc_bblk(FALSE);
 next_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 /* AIV 03/05/09 - no need to zero trigger for pnd0 case */
 /* could turn on for debugging to view active events */
 /* tevp->trigger = TRUE; */
 // __st_insn(I_STOREA, AM_REG, cint_ti, AM_NDXREG_DISP, tevp_reg_ti, offset);
 hdrp_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_P0_TE_HDRP);
 /* __p0_te_hdrp = tevp; */
 __st_insn(I_STOREA, AM_REG, tevp_reg_ti, AM_NLO, NLO_P0_TE_HDRP);

 __emit_jmp_0(empty_bbp, next_bbp, hdrp_ti);

 /* if (__p0_te_hdrp == NULL) __p0_te_endp = tevp; */
 __start_bblk(empty_bbp);
 __st_insn(I_STOREA, AM_REG, tevp_reg_ti, AM_NLO, NLO_P0_TE_ENDP);
 __emit_jmp(after_bbp);

 /*  tevp->tenxtp = __p0_te_hdrp; */
 __start_bblk(next_bbp);
 offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
 __st_insn(I_STOREA, AM_REG, hdrp_ti, AM_NDXREG_DISP, tevp_reg_ti, offset);
 __emit_jmp(after_bbp);

 __start_bblk(after_bbp);
}

/*
 * generate an edge dce with has more than one trigger for the edge
 * i.e. multiple @(posedge clk)
 * these have been merged in v_prp 
 * this checks the edges only once and then checks each trigger separately
 * known to not be xmr, repeat, variable selects
 */
static void gen_dce_inst_duplicates(struct net_t *np, struct dcevnt_t *dcep,
 struct bblk_t *after_bbp, int32 processing_pnd0s)
{
 int32 oval_ti, nval_ti;
 int32 emask_ti, schd_tev_ti, cint_ti, tevp_reg_ti;
 int32 i, count, ndx_ti;
 struct dcevnt_t *dcep2;
 struct delctrl_t *dctp;
 struct bblk_t *chk_rep_bbp, *trigger_bbp, *done_bbp;
 struct bblk_t *next_bbp;

 /* better have edge and previous val */
 /* DBG remove -- */ 
 if (dcep->dce_xmrtyp != XNP_LOC) __misc_terr(__FILE__, __LINE__); 
 if (dcep->prevval_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */ 

 /* will stay as -1 if not used, but since not used ok */
 oval_ti = nval_ti = -1;
 ndx_ti = -1;
 dctp = dcep->st_dctrl;
 /* AIV 12/11/07 - this can now be an array - handle like a vec */
 if (np->n_isarr)
  {
   gen_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), after_bbp, dctp);
  }
 else if (!np->n_isavec)
  {   
   /* notice unlike interpreter, both stren/non stren scalar gen same */
   gen_scal_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), after_bbp);
  }
 else
  {
   if (!np->n_stren)
    {
     gen_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), after_bbp, dctp);
    }
   else 
    {
     gen_stren_filter_dce_chg(np, dcep, &(oval_ti), &(nval_ti), after_bbp, 
       dctp);
    }
  }

 /* better not have xmr or edge */
 /* DBG remove -- */ 
 if (dcep->dce_1inst) __misc_terr(__FILE__, __LINE__);
 if (dcep->dce_expr != NULL) __misc_terr(__FILE__, __LINE__);
 if (!dcep->dce_edge) __misc_terr(__FILE__, __LINE__);
 /* ---- */ 

 /* check the edge only once */
 chk_rep_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);
 /* AIV 10/14/08 - this routine now has two jump tables - pos/neg */
 /* that way there is no need for masking at runtime */
 emask_ti = __emit_compute_emask(np, oval_ti, nval_ti, dcep->dce_edgval, 
   &ndx_ti);
 __emit_jmp_0(done_bbp, chk_rep_bbp, emask_ti);
 __start_bblk(chk_rep_bbp);

 count = dcep->merged_count;
 /* DBG remove -- */ 
 if (count < 1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* check each trigger for all shared edge dces */
 /* notice -1 here because the first dce is the base */
 dcep2 = dcep;
 for (i = -1; ; )
  {
   dctp = dcep2->st_dctrl;

   /* AIV 03/09/09 - if merged always blocks no code for the merged dces */
   if (!dctp->needs_thread && dctp->head_dctp != NULL) 
    {
     i++;
     if (i == count) break;
     dcep2 = dcep->merged_dces[i];
     continue;
    }
   /* DBG remove -- */ 
   /* AIV 05/02/08 - was merging xmr catch here */
   if (dcep2->dce_xmrtyp != XNP_LOC) __misc_terr(__FILE__, __LINE__); 
   if (dctp->repcntx != NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */ 
   /* now check each trigger */
   next_bbp = __alloc_bblk(FALSE);
   trigger_bbp = __alloc_bblk(FALSE);
   schd_tev_ti = __gen_dce_schd_tev(dctp);
   tevp_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, schd_tev_ti);
   __emit_jmp_0(next_bbp, trigger_bbp, tevp_reg_ti);
   __start_bblk(trigger_bbp);

//AIV EXPROP 
#ifdef __XPROP__
   if (dctp->xprop_xedge_actionst != NULL)
    {
     __misc_terr(__FILE__, __LINE__);
    }
#endif

   if (dcep2->st_dctrl->dc_nblking)
    {
     __emit_nb_trigger_ectrl(tevp_reg_ti);
    }
   else
    {
     if (processing_pnd0s)
      {
       gen_trigger_ectrl_pnd0(tevp_reg_ti, dctp);
      }
     else __emit_trigger_ectrl(tevp_reg_ti, dctp);
    }
   cint_ti = __gen_cint_tn((word32) NULL);
   __emit_copy(WRDBYTES, cint_ti, schd_tev_ti);
   __start_bblk(next_bbp);
   i++;
   if (i == count) break;
   dcep2 = dcep->merged_dces[i];
  }
 __start_bblk(done_bbp);
}

/*
 * gen vm insns for declarative out of range test
 * notice - know chg i1 and chg i2 always non b part 2v tmp names
 */
static void gen_decl_outofrng_tst(void *obj, int32 i1, union intptr_u i2,
 struct bblk_t *after_bbp, int32 test_i1_neg1)
{
 int32 i1_ti, i2_ti, cint_ti, chgi1_ti, chgi2_ti;	
 struct bblk_t *rng_tst_bbp, *rng2_tst_bbp, *cont_bbp;

 /* SJM 12/01/07 - for new limited memory access vm, move needed */
//AIV FIXME - no reason to do the moves for compare against constant
//this causes spills
 chgi1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NCHGED_I1);

 cont_bbp = __alloc_bblk(FALSE);
 /* if change i1 is -1 goto match from v_sim.c:995 */
 if (test_i1_neg1)
  {
   rng_tst_bbp = __alloc_bblk(FALSE);
   cint_ti = __gen_cint_tn(-1);
   __emit_jmp_eq(cont_bbp, rng_tst_bbp, cint_ti, chgi1_ti);
   __start_bblk(rng_tst_bbp);
  }

 if (i1 == -2)
  {
   /* this loads into tmp name */
   i1_ti = __gen_ld_con_isptr(obj, FALSE, FALSE);
   i2_ti = i1_ti;
   rng2_tst_bbp = __alloc_bblk(FALSE);
   /* AIV 11/25/09 - swapped these since chgi1_ti  is loaded into reg */
   /* doing the compare of it first has less register pressure */
   /* if low changed range higher than decl npp/dce range, eliminate */  
   __emit_jmp_cmp(after_bbp, rng2_tst_bbp, chgi1_ti, i2_ti, CC_JLT);
   __start_bblk(rng2_tst_bbp);

   /* if high changed range lower than decl npp/dce range, eliminate */  
   chgi2_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NCHGED_I2);
   __emit_jmp_cmp(after_bbp, cont_bbp, chgi2_ti, i1_ti, CC_JGT);
   __start_bblk(cont_bbp);
  }
 else
  {
   /* AIV 11/25/09 - has comparing twice for one bit (bsel) - only */
   /* need to do one compare if constant values are the same */
   if (i1 == i2.i)
    {
     cint_ti = __gen_cint_tn(i1);
     __emit_jmp_eq(cont_bbp, after_bbp, cint_ti, chgi1_ti);
     __start_bblk(cont_bbp);
     return;
    }

   /* AIV 11/25/09 - swapped these since chgi1_ti  is loaded into reg */
   /* doing the compare of it first has less register pressure */
   rng2_tst_bbp = __alloc_bblk(FALSE);
   cint_ti = __gen_cint_tn(i2.i);
   /* if low changed range higher than decl npp/dce range, eliminate */  
   __emit_jmp_cmp(rng2_tst_bbp, after_bbp, chgi1_ti, cint_ti, CC_JGE);
   __start_bblk(rng2_tst_bbp);

   /* if high changed range lower than decl npp/dce range, eliminate */  
   cint_ti = __gen_cint_tn(i1);
   chgi2_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NCHGED_I2);
   __emit_jmp_cmp(cont_bbp, after_bbp, chgi2_ti, cint_ti, CC_JLE);
   __start_bblk(cont_bbp);
  }
}

/*
 * gen vm insns to filter scalar old val for chg
 * if no edge, not setting - oval and nval ptrs (leave as -1) 
 * only does this for edge or strength
 */
static void gen_scal_filter_dce_chg(struct net_t *np, struct dcevnt_t *dcep, 
 int32 *oval_ti, int32 *nval_ti, struct bblk_t *after_bbp)
{
 int32 nv_ti, ov_ti, nval2_ti, oval2_ti;
 int32 cint_ti;
 struct bblk_t *tst_edge_bbp;

 /* DBG remove -- */ 
 if (np->nwid != 1) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* load the variable - always a scalar even for more than 1 inst */
 nv_ti = __gen_ld_netbp(np);

 /* wrapper that uses set __cur dce global */
 /* SJM 12/16/05 - even for multiple insts, this is addr of the one byte */
 ov_ti = __gen_dce_prevval_tn(dcep, 1);

 if (np->n_stren)
  {
   cint_ti = __gen_cint_tn(3);
   oval2_ti = __emit_mask_and(ov_ti, cint_ti);
   nval2_ti = __emit_mask_and(nv_ti, cint_ti);
   /* SJM 12/16/05 - needs to be a byte compare for nva.bp ptr in comm file */
   tst_edge_bbp = __alloc_bblk(FALSE);
   __emit_jmp_eq(after_bbp, tst_edge_bbp, oval2_ti, nval2_ti); 
   __start_bblk(tst_edge_bbp);
  
   __emit_copy(WRDBYTES, nval2_ti, ov_ti);

   /* only set global (used in future) old and new values if has edge */
   /* notice old val 2 and new val 2 both have stren mask if needed */
   /* AIV 02/24/12 - always set these may be used for xprop - no reason */
   /* not to, if not used will not produce any code */
   *oval_ti = oval2_ti; *nval_ti = nval2_ti; 
   return;
  } 

 /* if not strength better have an edge */
 /* DBG remove -- */ 
 /* AIV 02/24/12 - xprop uses this code as well */
 /* if (!dcep->dce_edge)  __misc_terr(__FILE__, __LINE__); */
 /*---- */ 

 /* AIV 06/15/05 - need to preserve old value in tmp storage */
 /* note compiler now checks for strength can't overwrite addr value */
 /* just changing tmp value to original ti overwrites the edge compare  */
 /* AIV 07/08/08 - for scalar case better to not even check if changed */
 /* just do the assign */
 oval2_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, ov_ti);
 nv_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, nv_ti);

 *oval_ti = oval2_ti; 
 *nval_ti = nv_ti;
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, nv_ti, ov_ti);
}

/*
 * gen vm insns to filter non stren vector old val for chg
 * AIV 03/02/07 - compiled code now treats all dce_edge prevval as scalar
 * no need to save more than the low bit - probably true for interp 
 * as well but leaving for compiler only for now
 * just get the low bit regardless of the size
 */
static int32 gen_filter_dce_chg(struct net_t *np, struct dcevnt_t *dcep,
 int32 *oval_ti, int32 *nval_ti, struct bblk_t *after_bbp, 
 struct delctrl_t *dctp)
{
 int32 dcewid, naddr_apti, oval_apti, oval_scal_adr_ti, nscalw_ti;
 int32 nval2_ti, i1_ti, t1_ti, t2_ti, ld_nval_ti, ld_nval_bpti, eq_ti;
 int32 oval2_bpti, nval2_bpti, oval_bpti, nbytes, srtyp;
 struct bblk_t *tst_edge_bbp;
#ifdef __XPROP__
 int32 xedge_ti;
#endif

 dcewid = __get_dcewid(dcep, np);

 /* now uses wrapper that acesses cur dce global - ptr to a/b right inst */ 
 oval_scal_adr_ti = -1;
 /* if dce xmr, will have already moved to access from itree loc */
 naddr_apti = -1;
 nval2_ti = -1;
 nscalw_ti = -1;
 if (!np->n_isarr) naddr_apti = __gen_ld_net_addr(np, NULL);


 if (dcep->dci1 != -1)
  {
   if (dcep->dci1 == -2 || dcep->dci1 == dcep->dci2.i)
    {
     /* AIV 12/11/07 - need to no handle the array case */
     if (np->n_isarr)
      {
       /* DBG remove -- */
       //AIV FIXME - can this happen - put these in idp anyway ??????
       if (dcep->dci1 == -2) __misc_terr(__FILE__, __LINE__);
       /* --- */
       nval2_ti = __gen_arrsel_const(np, dcep->dci1, np->nwid, NULL);
      }
     else if (dcep->dci1 == -2)
      {
       i1_ti = __gen_ld_con_isptr(dcep, FALSE, FALSE);
       nval2_ti = __gen_rhs_bsel_var(np, naddr_apti, i1_ti);
      }
     else
      {
       nval2_ti = __gen_rhs_bsel_const(np, naddr_apti, dcep->dci2.i);
      }
    }
   else
    {
     /* AIV 09/19/07 - this was incorrecly passing np->nwid should be dcewid */
     nval2_ti = __gen_fradr_rhs_psel(np->srep, naddr_apti, dcewid, dcep->dci1,
      dcep->dci2.i);
    }
   *nval_ti = nval2_ti;
  }
 else
  {
   /* variable index case is treated as expression which is eval */
   /* should never be here for array case */
   /* DBG remove -- */
   if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   nval2_ti = naddr_apti; 
  }

 /* AIV 03/02/07 - compiled code now treats all dce_edge prevval as scalar */
 if (dcep->dce_edge || dcewid == 1)
  {
   oval_scal_adr_ti = __gen_dce_prevval_tn(dcep, WBITS);
   oval_apti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1,
     AM_NDXREG, oval_scal_adr_ti);
  }
 else
  {
   /* AIV 03/01/07 - length is dcewid not np->nwid */
   oval_apti = __gen_dce_prevval_tn(dcep, dcewid);
  }

 /* convert a vector to a packed scalar */
 /* AIV 01/03/06 - if dcewid it is scalar so use the scalar case */
 if (dcep->dce_edge || dcewid == 1)
  {
   /* AIV 03/02/07 - compiled code now treats all dce_edge prevval as scalar */
   /* new value must be converted to scalar */
   if (np->n_2state) nscalw_ti = __gen_cnvt_ab_vec_to_scalar_2state(nval2_ti);
   else nscalw_ti = __gen_cnvt_ab_vec_to_scalar(nval2_ti);
   /* DBG remove -- */
   srtyp = __tntab[oval_apti].srtyp; 
   if (srtyp != SR_SCAL && srtyp != SR_SCAL2S) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   tst_edge_bbp = __alloc_bblk(FALSE);
   __emit_jmp_eq(after_bbp, tst_edge_bbp, nscalw_ti, oval_apti); 
   __start_bblk(tst_edge_bbp);

   /* store scalar into bp */
   __emit_copy(WRDBYTES, nscalw_ti, oval_scal_adr_ti);
   /* only set global (used in future) old and new values if has edge */
   *oval_ti = oval_apti;
   *nval_ti = nscalw_ti;
  }
 else
  {
   /* AIV 01/21/08 - handle the narrow case as xor and single jump */
   tst_edge_bbp = __alloc_bblk(FALSE);
   if (dcewid <= WBITS) 
    {
     /* AIV 07/08/08 - if narrow and known to be net address do the load */
     if (np->n_2state) 
      {
       __emit_jmp_eq(after_bbp, tst_edge_bbp, oval_apti, nval2_ti); 
       __start_bblk(tst_edge_bbp);
       nbytes = wlen_(dcewid)*WRDBYTES;
       __emit_copy(nbytes, nval2_ti, oval_apti);
      }
     else if (nval2_ti == naddr_apti) 
      {
       oval2_bpti = __get_bpti(oval_apti);
       ld_nval_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, nval2_ti);
       t1_ti = __emit_bin_bitxor(WBITS, oval_apti, ld_nval_ti);

       nval2_bpti = __get_bpti(nval2_ti);
       ld_nval_bpti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, nval2_bpti);
       t2_ti = __emit_bin_bitxor(WBITS, oval2_bpti, ld_nval_bpti);
       eq_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
       __emit_jmp_0(after_bbp, tst_edge_bbp, eq_ti);
       __start_bblk(tst_edge_bbp);
#ifdef __XPROP__
       /* if xprop need to check for x edge and no other 1/0/z changes */
       if (dctp->xprop_xedge_actionst != NULL && __do_xprop_xedge_vectors)
        {
         oval_bpti = __con_adradd_insn(SR_VEC, WBITS, oval_apti, WRDBYTES);
         xedge_ti = gen_has_xedge(ld_nval_ti, ld_nval_bpti, oval_apti, 
               oval_bpti);
         __st_insn(I_STOREA, AM_REG, ld_nval_ti, AM_NDXREG, oval_apti);
         __st_insn(I_STOREA, AM_REG, ld_nval_bpti, AM_NDXREG, oval_bpti);
         return(xedge_ti);
        }
#endif
       __st_insn(I_STOREA, AM_REG, ld_nval_ti, AM_NDXREG, oval_apti);
       oval_bpti = __con_adradd_insn(SR_VEC, WBITS, oval_apti, WRDBYTES);
       __st_insn(I_STOREA, AM_REG, ld_nval_bpti, AM_NDXREG, oval_bpti);
      }
     else 
      {
       nval2_bpti = __get_bpti(nval2_ti);
       oval2_bpti = __get_bpti(oval_apti);
       t1_ti = __emit_bin_bitxor(WBITS, oval_apti, nval2_ti);
       t2_ti = __emit_bin_bitxor(WBITS, oval2_bpti, nval2_bpti);
       eq_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
       __emit_jmp_0(after_bbp, tst_edge_bbp, eq_ti);
       __start_bblk(tst_edge_bbp);

#ifdef __XPROP__
      /* if has xprop xedge dectection - must check for xedge */
      if (dctp->xprop_xedge_actionst != NULL && __do_xprop_xedge_vectors)
       {
        xedge_ti = gen_has_xedge(nval2_ti, nval2_bpti, oval_apti, 
             oval2_bpti);
        nbytes = 2*wlen_(dcewid)*WRDBYTES;
        __emit_copy(nbytes, nval2_ti, oval_apti);
        return(xedge_ti);
       }
#endif

       nbytes = 2*wlen_(dcewid)*WRDBYTES;
       __emit_copy(nbytes, nval2_ti, oval_apti);
      }
    }
   else
    {
     /* AIV 07/02/08 - better to check a/b part as one call will */
     /* return as soon as they don't match - so one call is better */
     nbytes = wlen_(dcewid)*WRDBYTES;
     if (np->srep == SR_BIT2S) 
      {
       __emit_jmp_eq(after_bbp, tst_edge_bbp, oval_apti, nval2_ti); 
       __start_bblk(tst_edge_bbp);
      }
     else
      {
       nbytes *= 2;
       __emit_jmp_eq_abpart(after_bbp, tst_edge_bbp, oval_apti, nval2_ti); 
       __start_bblk(tst_edge_bbp);
#ifdef __XPROP__
       /* if has xprop xedge dectection - must check for xedge */
       if (dctp->xprop_xedge_actionst != NULL && __do_xprop_xedge_vectors)
        {
         xedge_ti = __emit_has_xedge_wide(oval_apti, nval2_ti, dcewid);
         __emit_copy(nbytes, nval2_ti, oval_apti);
         return(xedge_ti);
        }
#endif
      }

    /* notice copies follow gas movl [from],[to] format - copies b part too */
    __emit_copy(nbytes, nval2_ti, oval_apti);
   }
  }
 return(-1);
}

#ifdef __XPROP__
/*
 * <= WBITS handling for X edge dectection
 */
static int32 gen_has_xedge(int32 val1_ti, int32 val1_bpti, int32 val2_ti,
 int32 val2_bpti)
{
 int32 xbval1_ti, xbval2_ti, has_xval_ti, or1_ti, or2_ti, xedge_ti, xor_ti;
 struct bblk_t *no_xs_bbp, *xor_bbp;

 //AIV FIXME - there must be a better way to do this without the jump
 /* bval1 = wbp1[i] & aval1; */
 xbval1_ti = __emit_bin_bitand(WBITS, val1_bpti, val1_ti);
 /* bval2 = wbp2[i] & aval2; */
 xbval2_ti = __emit_bin_bitand(WBITS, val2_bpti, val2_ti);

 /* has_xval = (bval1 | bval2); */
 no_xs_bbp = __alloc_bblk(FALSE);
 xor_bbp = __alloc_bblk(FALSE);
 has_xval_ti = __emit_bin_bitor(WBITS, xbval1_ti, xbval2_ti);
 /* assume does not have xs and init is not ~ the no b part */
 xedge_ti = __emit_bitnot(WBITS, has_xval_ti);
 __emit_jmp_0(no_xs_bbp, xor_bbp, has_xval_ti);
 __start_bblk(xor_bbp);

 /* if ((aval1 | has_xval) ^ (aval2 | has_xval)) */
 or1_ti = __emit_bin_bitor(WBITS, val1_ti, has_xval_ti);
 or2_ti = __emit_bin_bitor(WBITS, val2_ti, has_xval_ti);
 xor_ti = __emit_bin_bitxor(WBITS, or1_ti, or2_ti);
 __emit_copy(WRDBYTES, xor_ti, xedge_ti);

 __start_bblk(no_xs_bbp);
 return(xedge_ti);
}
#endif

/*
 * gen vm insns to filter stren vector old val for chg
 * set T/F cond tmp name
 *
 * AIV 07/06/07 FIXME - LOOKATME - this code was never really being tested
 * and could have never worked
 * it currently does to many conversion - it gets a strength bsel and returns
 * a SR_VEC then converts it to a scalar to compare - this is dumb
 */
static int32 gen_stren_filter_dce_chg(struct net_t *np, struct dcevnt_t *dcep,
 int32 *oval_ti, int32 *nval_ti, struct bblk_t *after_bbp, 
 struct delctrl_t *dctp)
{
 int32 dcewid, oval_sbpti, nval2_ti, nscalw_ti, oscalw_ti, cint_ti;
 int32 i2_ti, naddr_apti;
 int32 oval3_ti, nval3_ti;
 struct bblk_t *tst_edge_bbp;
#ifdef __XPROP__
 int32 xedge_ti, nvec_ti, nvec_bpti, ovec_ti, ovec_bpti;
#endif

 tst_edge_bbp = __alloc_bblk(FALSE);

 dcewid = __get_dcewid(dcep, np);
 /* uses what will be set at run time dce - dcep needed to get offset */
 /* AIV 03/01/07 - length is dcewid not np->nwid */
 oval_sbpti = __gen_dce_prevval_tn(dcep, dcewid);

 /* notice always loading ptr */ 
 naddr_apti = __gen_ld_net_addr(np, NULL);
 /* adjust to base of area if dce is select */
 if (dcep->dci1 != -1) 
  {
   if (dcep->dci1 == -2 || dcep->dci1 == dcep->dci2.i)
    {
     if (dcep->dci1 == -2)
      {
       /* since non wide - will load the value not the ptr */
       i2_ti = __gen_ld_con_isptr(dcep, FALSE, FALSE);
       nval2_ti = __gen_rhs_bsel_var(np, naddr_apti, i2_ti); 
      }
     else
      {
       nval2_ti = __gen_rhs_bsel_const(np, naddr_apti, dcep->dci2.i);
      }
    }
   else
    {
     /* AIV 09/19/07 - this was incorrecly passing np->nwid should be dcewid */
     nval2_ti = __gen_fradr_rhs_psel(np->srep, naddr_apti, dcewid, dcep->dci1,
      dcep->dci2.i);
    }
  }
 else { nval2_ti = naddr_apti; }

 /* notice gen of only one of these code sequences possible */
 if (dcep->dce_edge)
  {
   /* DBG remove -- */
   if (dcewid != 1) __misc_terr(__FILE__, __LINE__);
   /* --- */
   nscalw_ti = __gen_cnvt_srep_ifneeded(nval2_ti, SR_SCAL, 1, FALSE, FALSE,
    TRUE);
   oscalw_ti = __gen_cnvt_srep_ifneeded(oval_sbpti, SR_SCAL, 1, FALSE, FALSE,
    TRUE);

   cint_ti = __gen_cint_tn(3);
   oval3_ti = __emit_mask_and(oscalw_ti, cint_ti);
   nval3_ti = __emit_mask_and(nscalw_ti, cint_ti); 

   __emit_jmp_eq(after_bbp, tst_edge_bbp, oscalw_ti, nscalw_ti); 
   /* not equal - i.e. wasn't filtered out */
   __start_bblk(tst_edge_bbp);

   *oval_ti = oval3_ti;
   *nval_ti = nval3_ti;
   __emit_copy(1, nscalw_ti, oval_sbpti);
  }
 else
  {
   __emit_jmp_eq_stmask(after_bbp, tst_edge_bbp, oval_sbpti, nval2_ti); 
   /* not equal - i.e. wasn't filtered out */
   __start_bblk(tst_edge_bbp);

#ifdef __XPROP__
  /* if xprop edge dectection is on must check for xedge */
  if (dctp->xprop_xedge_actionst != NULL && __do_xprop_xedge_vectors)
   {
    /* if scalar just convert and use normal a/b word xedge code */
    if (np->nwid == 1)
     {
      nvec_ti = __gen_cnvt_srep_ifneeded(nval2_ti, SR_VEC, 1, FALSE, FALSE,
         TRUE);
      ovec_ti = __gen_cnvt_srep_ifneeded(oval_sbpti, SR_VEC, 1, FALSE, FALSE,
         TRUE);
      nvec_bpti = __get_bpti(nvec_ti);
      ovec_bpti = __get_bpti(ovec_ti);
      xedge_ti = gen_has_xedge(nvec_ti, nvec_bpti, ovec_ti, ovec_bpti);
     }
    else
     {
      /* vector cases just uses a wrapper */
      xedge_ti = __emit_has_xedge_wide_st(oval_sbpti, nval2_ti, dcewid);
     }
    __emit_copy(dcewid, nval2_ti, oval_sbpti);
    return(xedge_ti); 
   }
#endif

   *oval_ti = oval_sbpti;
   *nval_ti = nval2_ti;
   __emit_copy(dcewid, nval2_ti, oval_sbpti);
  }
 return(-1);
}

/*
 * compare get a xmr idp skipping to after block on return of -1
 */
static int32 gen_match_targ_to_ref(int32 xmrtyp, struct gref_t *grp,
 struct bblk_t *after_bbp)
{
 int32 gref_ti, idp_ti, cint_ti;
 struct bblk_t *pushed_bbp;

 pushed_bbp = __alloc_bblk(FALSE);

 gref_ti = __gen_gref_tn(grp);
 idp_ti = -1;
 switch ((byte) xmrtyp) {
  case XNP_DOWNXMR:
   idp_ti =  __emit_downrel_targ_to_ref(gref_ti);
   break;
  case XNP_UPXMR:
   idp_ti =  __emit_uprel_targ_to_ref(gref_ti);
   break;
  case XNP_RTXMR:
  default:
   /* rooted not part of np union field - never called uses filter fld */ 
   __case_terr(__FILE__, __LINE__);
 } 
 cint_ti = __gen_cint_tn(-1);
 __emit_jmp_ptr_eq(after_bbp, pushed_bbp, cint_ti, idp_ti);

 /* for true still need to start new basic block */
 __start_bblk(pushed_bbp);
 return(idp_ti);
}


/*
 * routine to copy new idp into __idp - destination idp must be label
 */
static void gen_set_save_idp(int32 set_idp_ti, int32 *save_idp_ti, 
 int32 need_save)
{
 *save_idp_ti = -1;
 if (need_save)
  {
   /* save __idp */
   *save_idp_ti = __emit_save_cur_idp();
  }

 __memloc_emit_set_idp(set_idp_ti);
}

/*
 * routine to load constant idp
 *
 * SJM 12/01/07 - should be in MDP area - need consistent interface
 */
//AIV IDP FIXME CVC
//AIV FIXME - will no longer work with +load_solib
static void gen_ld_const_idp(struct itree_t *itp,  int32 *save_idp_ti, 
 int32 needs_save)
{
 int32 const_idp_ti;

 *save_idp_ti = -1;
 /* save __idp */
 if (needs_save)
  {
   *save_idp_ti = __emit_save_cur_idp();
  }
 
 const_idp_ti = __gen_mdata_value(itp);
 __memloc_emit_set_idp(const_idp_ti);
}

/*
 * gen insns to filter an edge expression
 */
static void gen_filter_edge_expr(struct dcevnt_t *dcep, int32 *oval_ti,
 int32 *nval_ti, struct bblk_t *after_bbp, struct net_t *np)
{
 int32 t1_ti, edgval_ti, bp_ti, srtyp; 
 struct bblk_t *edge_seen_bbp;

 edge_seen_bbp = __alloc_bblk(FALSE);

 /* get edge val - notice both old and new edge vals always copied to tmp */
 t1_ti = __gen_expr_eval(dcep->dce_expr->edgxp, -1);
 if (np->n_2state) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;

 edgval_ti = __gen_cnvt_srep_ifneeded(t1_ti, srtyp, 1, FALSE, FALSE,
  TRUE);
 /* convert a vector to a packed scalar */
 *nval_ti = edgval_ti;

 bp_ti = __gen_dce_expr_bp(dcep);
 *oval_ti = __gen_tn(srtyp, 1);
 __emit_copy(WRDBYTES, bp_ti, *oval_ti);

 /* AIV 10/13/06 - was generating an incorrect type needs to be scalar */

 /* uses what will be set at run time dce - dcep needed to get offset */
 /* AIV LOOKATME 01/02/06 - why bother to check for change better to just do */
 /* the store everytime - than doing the compare ?????? */
 /* AIV 03/15/07 - this was supposed to be byte eq not word equal */
 /* I fixed the mem2mem fixup incorrectly - to compenstate for this */
 __emit_jmp_eq(after_bbp, edge_seen_bbp, *oval_ti,*nval_ti); 
 __start_bblk(edge_seen_bbp);

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, *nval_ti, bp_ti);
}

/*
 * gen the monitor dce record insns
 */
static void gen_dce_monit(struct dcevnt_t *dcep, struct bblk_t *after_bbp)
{
 int32 dcep_ti;

 /* if dce off gen insns to jump over */
 gen_dce_off_insns(dcep, after_bbp);

 /* interpreter test for wrong inst here but already gened */
 if (!dcep->is_fmon)
  {
   __cvc_slotend_action |= SE_MONIT_TRIGGER;
   /* LOOKATME - maybe don't need wrapper - it is just: "__se |= <bits>" */
   __emit_monit_trigger();
  }
 else
  {
   __cvc_slotend_action |= SE_FMONIT_TRIGGER;
   dcep_ti = __gen_dce_adr_tn(dcep);
   __emit_fmonit_trigger(dcep_ti);
  }
}

/*
 * gen dce off test insns
 */
static void gen_dce_off_insns(struct dcevnt_t *dcep, struct bblk_t *after_bbp)
{
 int32 dcep_ti;
 struct bblk_t *dce_on_bbp;

 dce_on_bbp = __alloc_bblk(FALSE);
 dcep_ti = __gen_dce_adr_tn(dcep);
 __emit_jmp_dce_off(after_bbp, dce_on_bbp, dcep_ti);
 __start_bblk(dce_on_bbp);
}

/*
 * gen qcaf wakeup event insns that cause rhs re-eval 
 * needed because qc off and on so can't use npps
 */
static void gen_dce_qcaf(struct dcevnt_t *dcep, struct bblk_t *after_bbp)
{
 struct qcval_t *qcvalp;
 struct st_t *stp;
 struct expr_t *lhsx, *idndp;
 struct net_t *np;
 struct net_chg_t *ncp;
 struct mod_t *in_mdp;
 struct itree_t *itp;
 int32 biti, bitj, stp_ti;
 int32 dcep_ti, nchg_ti, nchg_idp_ofs_ti;

 /* if dce off gen insns to jump over */
 gen_dce_off_insns(dcep, after_bbp);
 dcep_ti = __gen_dce_adr_tn(dcep);
 qcvalp = dcep->dceu2.dce_qcvalp;
 /* AIV 08/19/08 - for xmr need to push __inst_mod - wrong for loading */
 /* of ncp - expects __inst_mod to be set */
 /* AIV 08/19/09 - these now remain itp during compile time */
 itp = (struct itree_t *) dcep->dce_refu.idp; 
 in_mdp = itp->itip->imsym->el.emdp;
 __push_itstk(in_mdp->moditps[0]);
 stp = qcvalp->qcstp;
 /* DBG remove -- */
 if (stp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ----- */
 lhsx = stp->st.sqca->qclhsx;

 /* AIV 05/09/11 - concat version never worked  - just making a wrapper */
 /* this will be slow but code is rarely used */
 if (lhsx->optyp == LCB) 
  {
   stp_ti = __gen_stmt_tn(stp);
   if (stp->st.sqca->regform) __emit_assign_qcaf_regform_concat(stp_ti);
   else __emit_assign_qcaf_concat(stp_ti);
  }
 else
  {
   /* if reg form and not concatenate, easy just use changed qcval */
   idndp = __get_lvalue_idndp(lhsx);
   np = idndp->lu.sy->el.enp;
   if (stp->st.sqca->regform)
    {
     /* if lhsx is an id or glbl id need -1 to indicate the whole net */
     /* __get_wc_wirrng returns the net's width */
     if (lhsx->optyp == ID || lhsx->optyp == GLBREF)
      {
       biti = bitj = -1;
      }
     else __get_qc_wirrng_comptime(lhsx, &np, &biti, &bitj); 

     if (__net_chg_nd_store(np, biti, bitj))
      {
       ncp = __gen_netchg_addr_tn(np, biti, bitj, FALSE, &nchg_ti);
       nchg_idp_ofs_ti = __gen_cint_tn(ncp->nchg_idp_ofs);
      }
     else 
      {
       nchg_ti = __gen_cint_tn(0); 
       nchg_idp_ofs_ti = nchg_ti;
      }
     __emit_assign_qcaf_regform(dcep_ti, nchg_ti, nchg_idp_ofs_ti);
    }
   else
    {
     /* handle the scalar case */
     /* AIV 12/14/07 - these all always recorded as the whole net changing */
     /* AIV LOOKATME - could be per bit - would be better code?????? */
     biti = -1;
     if (__net_chg_nd_store(np, biti, biti))
      {
       ncp = __gen_netchg_addr_tn(np, biti, biti, FALSE, &nchg_ti);
       nchg_idp_ofs_ti = __gen_cint_tn(ncp->nchg_idp_ofs);
      }
     else 
      {
       nchg_ti = __gen_cint_tn(0);
       nchg_idp_ofs_ti = nchg_ti;
      }
     if (np->n_isavec)
      {
       __emit_assign_qcaf(dcep_ti, nchg_ti, nchg_idp_ofs_ti);
      }
     else __emit_assign_scalar_qcaf(dcep_ti, nchg_ti, nchg_idp_ofs_ti);
    }
  }
 __pop_itstk();
}
   
/*
 * ROUTINES TO GENERATE NPP PROCESSING FLOW GRAPHS
 */

/*
 * gen insns for 1 regs all npps - this builds the flow graph
 * if no npp or not reg will not be called
 */
static void gen_npp_flowg(struct net_t *np)
{
 struct flowg_t *fgp;
 struct bblk_t *npps_bbp, *no_range_bbp, *range_bbp, *done_bbp;
 struct npaux_t *npauxp;
 int32 has_range, chgi1_ti, cint_ti;
 struct net_pin_t *npp;

 /* alloc and link on front of net's flow graph list */
 fgp = __alloc_flowg(FLOWG_NPP);
 add_flowg_to_netfg_list(np, fgp);
 __cur_flowg = fgp;
 __cur_bbp = NULL;


 npps_bbp = __alloc_bblk(FALSE);
 __start_bblk(npps_bbp); 
 /* SJM 02/21/06 - any entry from interpreter RT needs AFS bit set */
 npps_bbp->after_suspend = TRUE;
 __cur_ifrom_u.from_np = np;

 /* this handles entry from run time scheduler */
 __emit_enter_npp(np);

 /* AIV 07/09/09 - if marked used fixed code in v_asmlnk.c */
 if (np->is_iconn_port_scalar_opt) 
  {
   fgp->optim_scalar_port = TRUE;
   fgp->optim_port_np = np; 
   __emit_complete();
   return;
  }

 /* AIV 05/10/07 - check if any loads on the list has a range */
 has_range = FALSE;
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 != -1)
    {
     has_range = TRUE;
    }
  }

 /* if has a range make two lists of the npp lists - one for the entire */
 /* wire (__nchged_i1 == -1) and one for range checking */
 /* this is ok to make two flow graph lists because nearly all are */
 /* just function calls to the lowered code any how */
 /* AIV FIXME - some rare cases have performance problem - due to two fgs ?? */
 if (has_range)
  {
   /* check if __nchged == -1 if so call all without range checking */
   /* otherwise need to do the range checking */
   no_range_bbp = __alloc_bblk(FALSE);
   range_bbp = __alloc_bblk(FALSE);
   done_bbp = __alloc_bblk(FALSE);

   /* SJM 12/01/07 - for new limited memory access vm, move needed */
   chgi1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NCHGED_I1);
   cint_ti = __gen_cint_tn(-1);
   __emit_jmp_eq(no_range_bbp, range_bbp, chgi1_ti, cint_ti);
   __start_bblk(no_range_bbp);
   /* npp flow graphs with no range checking */
   gen_1net_npp_insns(np, FALSE, -1, -1, FALSE);
   __emit_jmp(done_bbp);

   __start_bblk(range_bbp);
   /* npp flow graphs with range checking */
   gen_1net_npp_insns(np, TRUE, -1, -1, FALSE);
   __emit_jmp(done_bbp);
   __start_bblk(done_bbp);
  }
 /* no ranges do regular checking */
 else gen_1net_npp_insns(np, TRUE, -1, -1, FALSE);



 /* return on finish is back to run time scheduler */
 __emit_complete();
}

/*
 * gen the npp insns for one net
 *
 * if separate npp list for reg, caller must build the flow graph
 * no current call graph and current basic block when called
 */
static int32 gen_1net_npp_insns(struct net_t *np, int32 needs_range, int32 i1,
 int32 i2, int32 is_nchg_fg)
{
 int32  np_ti, ctevp_ti, fixed_mdat_ti, rng1, rng2, bi; 
 int32 nd_rt_itpop, itp_ti, has_lds_after, in_range;
 int32 delayed_mipd_ti, nd_itpop, save_idp_ti, mipd_enter_ti;
 struct net_pin_t *npp;
 struct npaux_t *npauxp;
 struct bblk_t *after_bbp, *npp_filt_bbp, *schd_mipd_bbp; 
 struct bblk_t *use_bbp, *after_nd_pop_bbp; 
 struct gate_t *gp;
 struct mod_t *ref_in_mdp;
 struct itree_t *itp;
 struct ctev_t *ctevp;

 /* must process all loads on net */
 in_range = FALSE;
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* SJM 08/29/08 - if no mipd glitch check option selected, never */
   /* reschedule MIPD delays - if reschedule needed option will cause */
   /* wrong results, but can speed by by 20-30% */
   if (npp->npntyp == NP_MIPD_NCHG && __mipd_cycle_pnd0_schd)
    {
     /* must put in comm lab tree or will not link right */
     __gen_npp_adr_tn(npp);
     continue;
    } 

   if (needs_range)
    {
     if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 != -1)
      {
       if (i1 != -1)
        {
         if (i1 < npauxp->nbi2.i || i2 > npauxp->nbi1) continue;
        }
      }
    }
   has_lds_after = (npp->npnxt != NULL);
   after_bbp = __alloc_bblk(FALSE);
   after_nd_pop_bbp = NULL;

//AIV LOOKATME - maybe should check range first for this case?????
   /* rare only for XMRs but when gened think will almost always eliminate */
   /* SJM 03/09/03 - for fi>1 ports have move around must use push inst mod */
   if (npp->npproctyp == NP_PROC_FILT && __inst_mod->flatinum > 1)
    {
     npp_filt_bbp = __alloc_bblk(FALSE);

     itp = (struct itree_t *) npp->npaux->npu.filtidp;
     fixed_mdat_ti = __gen_mdata_value(itp);
     /* SJM 12/03/07 - the addr here is really a value to compare against */
     __emit_jmp_idp_eq(npp_filt_bbp, after_bbp, fixed_mdat_ti); 
     __start_bblk(npp_filt_bbp);
    }

   /* AIV 05/10/07 - only check range if flag is passed T */
   if (i1 == -1)
    {
     if (needs_range)
      {
       if ((npauxp = npp->npaux) != NULL && npauxp->nbi1 != -1)
        {
         /* AIV 05/10/07 - know by time gets here already checked for -1 */
         gen_decl_outofrng_tst(npp, npauxp->nbi1, npauxp->nbi2, after_bbp, 
          FALSE);
        }
      }
    }

   in_range = TRUE;
   save_idp_ti = -1;
   nd_rt_itpop = nd_itpop = FALSE;
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* proc gref means instance tree relative (not 1 inst) */
     /* this always pushes a matching one at compile time too */
     if (npp->npproctyp == NP_PROC_GREF)
      {
       /* even if current (1st) inst does not match, finds one to push */
       /* at compile time - this allocs and startconditional non jmp bblk */
       /* SJM 01/23/06 - if not matched - no need to exec the RT pop */
       itp_ti = gen_match_targ_to_ref(npp->np_xmrtyp, npp->npaux->npu.npgrp, 
                 after_bbp);
       /* 01/23/06 - this is compile time push but can't use push wrk itstk */
       /* AIV 05/09/07 - if no loads following current no need to save */
       gen_set_save_idp(itp_ti, &save_idp_ti, has_lds_after);
       ref_in_mdp = npp->npaux->npu.npgrp->gin_mdp;
       __push_itstk(ref_in_mdp->moditps[0]);
       if (has_lds_after) nd_rt_itpop = TRUE;
      }
     else 
      {
       /* AIV 04/10/07 - just push the constant value */
       if (need_npp_downinst_push(npp->npntyp))
        {
         itp = npp->npaux->npdownitp;
         /* AIV 05/09/07 - if no loads following current no need to save */
         gen_ld_const_idp(itp, &save_idp_ti, has_lds_after);
         if (has_lds_after) nd_rt_itpop = TRUE;
        }
       __push_itstk(npp->npaux->npdownitp);
      }
     nd_itpop = TRUE;
    }

   if (nd_rt_itpop)
    {
     after_nd_pop_bbp = __alloc_bblk(FALSE);
     use_bbp = after_nd_pop_bbp;
    }
   else use_bbp = after_bbp;

   switch ((byte) npp->npntyp) {
    case NP_ICONN: case NP_PB_ICONN:
     gen_np_iconn_insns(npp);
     break;
    case NP_MDPRT: case NP_PB_MDPRT:
     gen_np_mdprt_insns(npp, use_bbp, is_nchg_fg);
     break;
    case NP_GATE:
     gp = npp->elnpp.egp;
     if (gp->g_class == GC_LOGIC)
      {
       /* wide case still a wrapper for now */
       if (gp->gpnum <= 16) 
        {
         gen_np_gate_insns(npp, use_bbp);
        }
       else
        {
         gen_wide_logic_gate(gp, npp);
        }
      }
     else gen_np_gate_insns(npp, use_bbp);
     break;
    case NP_CONTA:
     gen_np_conta(npp);
     break;
    case NP_TRANIF:
     gp = npp->elnpp.egp;
     gen_np_tranif(gp);
     break;
    case NP_TCHG:
     gen_np_timechg(npp, np);
     break;
    case NP_MIPD_NCHG:
     /* DBG remove -- */
     if (np->nlds != npp) __misc_terr(__FILE__, __LINE__);
     if (nd_itpop) __misc_terr(__FILE__, __LINE__);
     /* -- */

     schd_mipd_bbp = __alloc_bblk(FALSE);

     /* SJM 12/01/07 - really need the move here for limited mem access vm */
     delayed_mipd_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO,
      NLO_DELAYED_MIPD);
     /* AIV 09/14/05 - need to goto to next npp if not scheduling */
     /* SJM 01/23/06 - after works here because never need XMR pop */
     __emit_jmp_0(schd_mipd_bbp, after_bbp, delayed_mipd_ti);

     __start_bblk(schd_mipd_bbp);
     
//AIV FIXME - npp_ti is no longer passed but currently need to add to tree
//perhaps mipd should be in seperate tree
//SJM? 08/02/08 FIXME - BEWARE FOR NOW need to gen the npp tn to put it into
//                      the dlsym tree - should just be label
     __gen_npp_adr_tn(npp);
     np_ti = __ld_netadr_tn(np);
     mipd_enter_ti = __gen_mipd_enter_adr_tn(npp->npp_idnum);

     /* DBG remove -- */ 
     if (np->ndel_ctevtab == NULL) __misc_terr(__FILE__, __LINE__);
     /* -- */ 
 
    /* AIV 12/28/11 - this needs to pass per bit since the ptevp is different */
    /* for each bit */
     if (np->n_isavec)
      { 
       /* either the entire net or just bit range */
       if (i1 == -1)
        {
         rng1 = np->nwid - 1;
         rng2 = 0;
        }
       else
        {
         rng1 = i1;
         rng2 = i2;
        }
       //AIV LOOKATME - this can be optimized to not call for each bit?
       for (bi = rng1; bi >= rng2; bi--)
        {
         ctevp = np->ndel_ctevtab[bi];
         ctevp_ti = __gen_ctevp_adr_tn(ctevp);
         ctevp->ct_el_ndx = __tntab[mipd_enter_ti].tncu.el_ndx;
         ctevp->ct_comlab_typ = __tntab[mipd_enter_ti].comlab_typ;
         __emit_sched_vec_mipd_bit(np_ti, ctevp_ti, bi);
        }
      }
     else
      {
       ctevp = np->ndel_ctevtab[0];
       ctevp_ti = __gen_ctevp_adr_tn(ctevp);

       /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
       ctevp->ct_el_ndx = __tntab[mipd_enter_ti].tncu.el_ndx;
       ctevp->ct_comlab_typ = __tntab[mipd_enter_ti].comlab_typ;

       __emit_sched_scalar_mipd(np_ti, ctevp_ti, npp);
      }
     /* SJM 09/23/05 - never XMR because of internal error above */ 
     /* SJM 01/23/06 - this is really complete because this is really */ 
     /* pseudo change and know first on list so schedule and stop */ 
     /* processing any changes at run time - did not really change yet */
     /* AIV 01/03/07 - if is inlined nchg graph jump to next event */
     /* if used as npp alloc net change handle graph returns (norm complete) */
     if (is_nchg_fg) __emit_next_nchg_event();
     else __emit_complete();
     break;
     /* pull driver only illlegal here */
    default: __case_terr(__FILE__, __LINE__);
   }
   if (nd_rt_itpop)
    {
     __start_bblk(after_nd_pop_bbp);
     __gen_restore_idp(save_idp_ti);
     __pop_itstk();
    }
   else if (nd_itpop) 
    {
     __pop_itstk();
    }

   /* SJM 07/27/05 - even when skip, must always move to next npp */
   __start_bblk(after_bbp);
  }
 return(in_range);
}

/*
 * AIV 11/20/07 - do the NP_TRANIF
 * just call the wrapper and returns T if changed if changed prop change
 */
static void gen_np_tranif(struct gate_t *gp)
{
 struct bblk_t *eval_chg_bbp, *done_bbp, *make_x_bbp, *assgn_ng_bbp;
 int32 gp_ti, eval_chg_ti, chg_ti, old_gateval_ti, new_gateval_ti;
 int32 cint_ti, gstate_adr_apti;

 eval_chg_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);
 gp_ti = __gen_gate_adr_tn(gp);
 chg_ti = __gen_tn(SR_CINT, WBITS);
 eval_chg_ti = __emit_exec_np_tranif(gp_ti);

 __emit_jmp_0(done_bbp, eval_chg_bbp, eval_chg_ti);

 __start_bblk(eval_chg_bbp);
 /* SJM 12/01/07 - notice need to load the gate values only in prop bblk */
 old_gateval_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_OLDGVAL);
 new_gateval_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NEWGVAL);
 if (gp->g_delrep != DT_NONE)
  {
   gen_prop_gatechg(gp, new_gateval_ti, old_gateval_ti, done_bbp, chg_ti);
  }
 else
  {
   /* __change_gate_outwire for GC_TRANIF */
   /* if (__new_gateval == 2) __new_gateval = 3; */
   /* __idp[gp->gstate_ofs] = __new_gateval; */
   /* __asl_immed_eval_trifchan(gp); */
   make_x_bbp = __alloc_bblk(FALSE);
   assgn_ng_bbp = __alloc_bblk(FALSE);
   cint_ti = __gen_cint_tn(2);
   __emit_jmp_eq(make_x_bbp, assgn_ng_bbp, cint_ti, new_gateval_ti);
   __start_bblk(make_x_bbp);

   cint_ti = __gen_cint_tn(3);
   __emit_copy(WRDBYTES, cint_ti, new_gateval_ti);
   __emit_jmp(assgn_ng_bbp);
   __start_bblk(assgn_ng_bbp);

   gstate_adr_apti = __gen_gatebp_tn(gp, WBITS); 
   __emit_copy(WRDBYTES, new_gateval_ti, gstate_adr_apti);

   __emit_immed_eval_trifchan(gp_ti);
  }
 __emit_jmp(done_bbp);
 __start_bblk(done_bbp);
}
    
/*
 * lower a timing check npp
 */
static void gen_np_timechg(struct net_pin_t *npp, struct net_t *np)
{
 int32 addr_ti, bi, res_ti;
 struct npaux_t *npauxp;
 struct tchg_t *tchgp;
 struct tchk_t *tcp;
 struct bblk_t *no_change_bbp;
 struct spcpth_t *newpthp;

 /* get the bit to select */
 if ((npauxp = npp->npaux) == NULL) bi = 0; else bi = npauxp->nbi1;
 /* load net address */
 addr_ti = __ldvar_addr(np, NULL);
 /* if not equal to one is a bit select */
 if (bi != 0)
  {
   /* AIV 11/10/09 - this should be just call scalar bsel */
   res_ti = __gen_rhs_bsel_scalar_const(np, addr_ti, bi); 
  }
 else
  {
   /* if scalar just set to address otherwise do conversion */
   if (np->srep == SR_SCAL || np->srep == SR_SCAL2S)
    {
     res_ti = addr_ti;
    }
   else
    {
     res_ti = __gen_cnvt_srep_ifneeded(addr_ti, SR_SCAL, 1, FALSE, FALSE,
      FALSE);
    }
  }
 /* call timing check type of npp */
 switch (npp->chgsubtyp) {
  case NPCHG_TCSTART: 
   tchgp = npp->elnpp.etchgp;
   tcp = tchgp->chgu.chgtcp;

   no_change_bbp = __alloc_bblk(FALSE);
   gen_filter_bitchange(res_ti, tchgp->oldval_ofs, tcp->startedge, 
    tcp->startcondx, no_change_bbp);
   gen_assign_simtime_to_lasttime(tchgp->lastchg_ofs);
   __start_bblk(no_change_bbp);
   break;
  case NPCHG_TCCHK: 
   __cvc_slotend_action |= SE_TCHK_VIOLATION;
   gen_npchg_tcchk(npp, res_ti);
   break;
  case NPCHG_PTHSRC: 
   tchgp = npp->elnpp.etchgp;
   newpthp = tchgp->chgu.chgpthp;

   no_change_bbp = __alloc_bblk(FALSE);
   /* AIV 01/12/12 - path conditions are no longer checked here passing */
   /* NULL instead of pthcondx - these are checked during path delay calc */
   gen_filter_bitchange(res_ti, tchgp->oldval_ofs, newpthp->pthedge, 
    NULL, no_change_bbp);
   gen_assign_simtime_to_lasttime(tchgp->lastchg_ofs);
   __start_bblk(no_change_bbp);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}
   
/*
 * do filter_bitchange code
 * AIV 01/04/12 - oldval_ofs needs to be passed as size_t not int
 */
static void gen_filter_bitchange(int32 newval_ti, size_t oldval_ofs, 
 int32 signat, struct expr_t *condx, struct bblk_t *no_chg_bbp)
{
 int32 oldval_ti, cond_ti, t1_ti, t2_ti, oval_ti, ndx_ti, cint_ti, epair_ti;
 struct bblk_t *chg_bbp, *chk_cond_bbp, *cond_notzero_bbp; 
 /* 
 old_eval = __idp[old_ofs];
 if (new_eval == old_eval) return(FALSE);
 __idp[old_ofs] = new_eval;
 */
 chg_bbp = __alloc_bblk(FALSE);

 oldval_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*oldval_ofs);

 __emit_jmp_eq(no_chg_bbp, chg_bbp, oldval_ti, newval_ti);
 __start_bblk(chg_bbp);
 
 /* need to save the old value for edge comp */
 oval_ti = -1;
 if (signat != 0)
  {
   oval_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, oldval_ti);
  }
 __emit_copy(WRDBYTES, newval_ti, oldval_ti);

 /*
 if (signat != 0)
  {
   epair = __epair_tab[new_eval | (old_eval << 2)];
   if ((signat & epair) == 0) return(FALSE);
  }
 */
 if (signat != 0)
  {
   chk_cond_bbp = __alloc_bblk(FALSE);
   cint_ti = __gen_cint_tn(2);
   t1_ti = __emit_shiftl(WBITS, cint_ti, oval_ti);
   ndx_ti = __emit_bin_bitor(WBITS, newval_ti, t1_ti);
   epair_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, ndx_ti, NLO_EPAIR_TAB);
   cint_ti = __gen_cint_tn(signat);
   t2_ti = __emit_bin_bitand(WBITS, cint_ti, epair_ti);

   __emit_jmp_0(no_chg_bbp, chk_cond_bbp, t2_ti);
   __start_bblk(chk_cond_bbp);
  }

 /*
 if (condx != NULL)
  {
   xsp = __eval2_xpr(condx);
   if ((xsp->ap[0] & 1L) == 0L && (xsp->bp[0] & 1L) == 0L)
    { __pop_xstk(); return(FALSE); }
   __pop_xstk();
  }
 */
 /* AIV 01/12/12 - this condition code is a boolean can just handle as */
 /* scalar and check for scalar 0 value - do not want a vector here */
 if (condx != NULL)
  {
   cond_notzero_bbp = __alloc_bblk(FALSE);
   cond_ti = __gen_expr_eval(condx, -1);

   cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
      FALSE);
   __emit_jmp_0(no_chg_bbp, cond_notzero_bbp, cond_ti);
   __start_bblk(cond_notzero_bbp);
  }
}

/*
 * assign __simtime to tchgp->lastchg_ofs offset 
 */
#ifdef __CVC32__
static void gen_assign_simtime_to_lasttime(int32 ofs)
{
 int32 t_low_ti, t_high_ti, idpt_low_ti, idpt_high_ti;

 /* movl	__simtime,  %eax */
 /* movl	%eax, 396(%esi) */
 t_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SIMTIME);
 idpt_low_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
 __st_insn(I_STOREA, AM_REG, t_low_ti, AM_NDXREG, idpt_low_ti);

 /* movl	__simtime+4,  %eax */
 /* movl	%eax, 400(%esi) */
 t_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SIMTIME_HIGH);
 /* move one word up */
 idpt_high_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*(ofs+1));
 __st_insn(I_STOREA, AM_REG, t_high_ti, AM_NDXREG, idpt_high_ti);
}

/*
 * lower the code for NPCHG_TCCHK
 */
static void gen_npchg_tcchk(struct net_pin_t *npp, int32 res_ti)
{
 int32 t_low_ti, t_high_ti, idpt_low_ti, idpt_high_ti; 
 int32 t1_ti, cint_ti, chk_active_ti, chktcp_ti;
 struct bblk_t *no_change_bbp, *is_zero_bbp, *check_last_bbp, *record_tchk_bbp;
 struct tchg_t *tchgp;
 struct tchk_t *tcp;
 struct chktchg_t *chktcp;

 chktcp = npp->elnpp.echktchgp;
 tchgp = chktcp->startchgp;
 tcp = tchgp->chgu.chgtcp;

 no_change_bbp = __alloc_bblk(FALSE);
 is_zero_bbp = __alloc_bblk(FALSE);
 check_last_bbp = __alloc_bblk(FALSE);
 record_tchk_bbp = __alloc_bblk(FALSE);
 gen_filter_bitchange(res_ti, chktcp->chkoldval_ofs, tcp->chkedge,
  tcp->chkcondx, no_change_bbp);

 /*
 w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
 reftim = *w64p;
 if (reftim == 0ULL)
  {
   if (tcp->tchktyp == TCHK_PERIOD) 
    {
     *w64p = __simtime;
    }
   return;
  }
 */
 idpt_low_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*tchgp->lastchg_ofs);
 idpt_high_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*(tchgp->lastchg_ofs+1));
 /* if (reftim == 0ULL) */
 t_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idpt_low_ti);
 t1_ti = __emit_bin_bitor(WBITS, idpt_high_ti, t_low_ti);

 __emit_jmp_0(is_zero_bbp, check_last_bbp, t1_ti);
 __start_bblk(is_zero_bbp);
 if (tcp->tchktyp == TCHK_PERIOD) 
  {
   /* __idp[tchgp->lastchg_ofs] = __simtime; */
   t_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SIMTIME);
   __st_insn(I_STOREA, AM_REG, t_low_ti, AM_NDXREG, idpt_low_ti);
   t_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SIMTIME_HIGH);
   __st_insn(I_STOREA, AM_REG, t_high_ti, AM_NDXREG, idpt_high_ti);
  }
 __emit_jmp(no_change_bbp);

 __start_bblk(check_last_bbp);

 /* AIV 10/15/09 - now just check if on list with the flag T/F */
 /* if (__idp[chktcp->chkactive_ofs]) */
 chk_active_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*chktcp->chkactive_ofs);

 __emit_jmp_0(record_tchk_bbp, no_change_bbp, chk_active_ti);

 __start_bblk(record_tchk_bbp);
 chktcp_ti = __gen_tchk_tn(chktcp, npp->npp_idnum);
 __emit_timing_check_record(chktcp_ti);
 cint_ti = __gen_cint_tn(TRUE);
 __emit_copy(WRDBYTES, cint_ti, chk_active_ti);

 __start_bblk(no_change_bbp);
}
#else
/* 
 * 64-bit version is just one movq store into the idp offset
 */
static void gen_assign_simtime_to_lasttime(int32 ofs)
{
 int32 simt_ti, idpt_ti;

 /* movq	__simtime,  %eax */
 /* movl	%eax, 396(%esi) */
 simt_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SIMTIME);
 idpt_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
 __st_insn(I_STOREA, AM_REG, simt_ti, AM_NDXREG, idpt_ti);
}

/*
 * 64-bit lower the code for NPCHG_TCCHK
 */
static void gen_npchg_tcchk(struct net_pin_t *npp, int32 res_ti)
{
 int32 t1_ti, chktcp_ti, idpt_ti, chk_active_ti, cint_ti;
 struct bblk_t *no_change_bbp, *is_zero_bbp, *check_last_bbp, *record_tchk_bbp;
 struct tchg_t *tchgp;
 struct tchk_t *tcp;
 struct chktchg_t *chktcp;

 chktcp = npp->elnpp.echktchgp;
 tchgp = chktcp->startchgp;
 tcp = tchgp->chgu.chgtcp;

 no_change_bbp = __alloc_bblk(FALSE);
 is_zero_bbp = __alloc_bblk(FALSE);
 check_last_bbp = __alloc_bblk(FALSE);
 record_tchk_bbp = __alloc_bblk(FALSE);
 gen_filter_bitchange(res_ti, chktcp->chkoldval_ofs, tcp->chkedge,
  tcp->chkcondx, no_change_bbp);

 /*
 w64p = (word64 *) &(__idp[tchgp->lastchg_ofs]);
 reftim = *w64p;
 if (reftim == 0ULL)
  {
   if (tcp->tchktyp == TCHK_PERIOD) 
    {
     *w64p = __simtime;
    }
   return;
  }
 */
 idpt_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*tchgp->lastchg_ofs);
 /* if (reftim == 0ULL) */

 __emit_jmp_0(is_zero_bbp, check_last_bbp, idpt_ti);
 __start_bblk(is_zero_bbp);
 if (tcp->tchktyp == TCHK_PERIOD) 
  {
   /* __idp[tchgp->lastchg_ofs] = __simtime; */
   t1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SIMTIME);
   __st_insn(I_STOREA, AM_REG, t1_ti, AM_NDXREG, idpt_ti);
  }
 __emit_jmp(no_change_bbp);

 __start_bblk(check_last_bbp);

 /* AIV 10/15/09 - now just check if on list with the flag T/F */
 /* if (__idp[chktcp->chkactive_ofs]) */
 chk_active_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*chktcp->chkactive_ofs);

 __emit_jmp_0(record_tchk_bbp, no_change_bbp, chk_active_ti);

 __start_bblk(record_tchk_bbp);
 chktcp_ti = __gen_tchk_tn(chktcp, npp->npp_idnum);
 __emit_timing_check_record(chktcp_ti);
 cint_ti = __gen_cint_tn(TRUE);
 __emit_copy(WRDBYTES, cint_ti, chk_active_ti);

 __start_bblk(no_change_bbp);
}
#endif
 
/*
 * generate insns for NP ICONN nchg npp
 *
 * highconn iconn source changes and need to assign to down mdprt sink
 * lowconn lhs
 *
 * know inst mod compile time itree context is up module (in port highconn)
 * caller handles pushing and popping of itree context
 * 
 * AIV 02/13/07 - this now stores iconn info for later iconn flow graph
 * generation and just calls that flow graph here
 */
static void gen_np_iconn_insns(struct net_pin_t *npp)
{
 int32 has_lds_after;
 struct expr_t *down_lhsx, *up_rhsx;
 struct itree_t *itp, *up_itp;
 struct inst_t *ip;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 struct np_iconn_t *npicp;

 /* DBG remove -- */
 if (npp->elnpp.eii >= __inst_mod->minum) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 /* SJM 03/09/03 - for fi>1 ports have move around must use push inst mod */
 /* any up itree inst works since down mdp always same */ 
 /* SJM 04/23/03 - up itp is itree loc of input port highconn */
 up_itp = __inst_mod->moditps[0];

 /* SJM 04/23/03 - notice keeping both one inst ref and decl hconn itps */
 /* removed itree move since must start at highconn mod context of */
 /* input port not the define location of highconn */

 /* SJM 12/06/02 - for xmr iconn loads, must set "any" itree loc using gref */
 /* or down module */
 itp = &(up_itp->in_its[npp->elnpp.eii]);
 ip = itp->itip; 
 downmdp = ip->imsym->el.emdp; 

 /* DBG remove --- */
 if (npp->obnum >= downmdp->mpnum) __misc_terr(__FILE__, __LINE__);
 /* --- */

 mpp = &(downmdp->mpins[npp->obnum]); 
 if (npp->npntyp == NP_PB_ICONN)
  {
   mpp = &(mpp->pbmpps[npp->pbi]);
   up_rhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
  }
 else up_rhsx = ip->ipins[npp->obnum]; 
 down_lhsx = mpp->mpref;

 /* DBG remove -- */
 if (up_rhsx->optyp == OPEMPTY) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* AIV 10/06/08 - if inline option - generate the code here */
 if (__inline_code)
  {
   has_lds_after = (npp->npnxt != NULL);
   gen_iconn(up_rhsx, down_lhsx, downmdp, __inst_mod, npp->elnpp.eii, 
    has_lds_after);
  }
 else
  {
   /* store flow graph info for later generation */
   /* call the flow graph */
   npicp = __add_np_iconn_expr(npp, up_rhsx);
   __emit_call_iconn(npicp->iconn_ndx);
  }
}

/*
 * all iconn are now stored in a tree and called as a function
 * this generates a flow graph for each iconn 
 */
static void gen_iconn_flowgs(struct mod_t *mdp)
{
 int32 i, num_iconns;
 struct np_iconn_t *npicp;
 struct avlnode_t **iconn_avltab;
 
 /* linearize tree and create a flow graph for each iconn */
 iconn_avltab = __linearize_avl_tree(__np_iconn_dup_tn_tree, &(num_iconns));

 if (num_iconns == 0) return;

 __push_itstk(mdp->moditps[0]);
 for (i = 0; i < num_iconns; i++)
  {
   npicp = (struct np_iconn_t *) iconn_avltab[i]->valp;
   gen_one_np_iconn_flowg(npicp);
  }
 __pop_itstk();
 __my_free(iconn_avltab, num_iconns*sizeof(struct avlnode_t *)); 
}

/*
 * generate a flow graph for one iconn
 */
static void gen_one_np_iconn_flowg(struct np_iconn_t *npicp)
{
 struct expr_t *down_lhsx, *up_rhsx;
 struct flowg_t *fgp;
 struct bblk_t *iconn_bbp;
 struct itree_t *itp, *up_itp;
 struct inst_t *ip;
 struct mod_t *downmdp, *ref_in_mdp;
 struct mod_pin_t *mpp;
 struct net_pin_t *npp;
 int32 nd_itpop;

 /* AIV 07/07/09 - changed this to save some space in npicp */
 /* all the previously saved values can be found from net_pin_t npp */
 nd_itpop = FALSE;
 npp = npicp->npp;
 if (npp->npproctyp != NP_PROC_INMOD)
  {
   if (npp->npproctyp == NP_PROC_GREF)
    {
     ref_in_mdp = npp->npaux->npu.npgrp->gin_mdp;
     __push_itstk(ref_in_mdp->moditps[0]);
    }
   else 
    {
     __push_itstk(npp->npaux->npdownitp);
    }
   nd_itpop = TRUE;
  }


 /* create flow graph and then same as old iconn code */
 fgp = __alloc_flowg(FLOWG_ICONN);
 __cur_ifrom_u.from_iconn = npicp->iconn_ndx;
 __cur_flowg = fgp;
 npicp->fgp = fgp;
 __cur_bbp = NULL;

 iconn_bbp = __alloc_bblk(FALSE);
 __start_bblk(iconn_bbp); 
 iconn_bbp->after_suspend = TRUE;
 __emit_enter_iconn(npicp->iconn_ndx);

 /* DBG remove -- */
 if (npp->elnpp.eii >= __inst_mod->minum) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 up_itp = __inst_mod->moditps[0];
 itp = &(up_itp->in_its[npp->elnpp.eii]);
 ip = itp->itip; 
 downmdp = ip->imsym->el.emdp; 

 mpp = &(downmdp->mpins[npp->obnum]); 
 down_lhsx = mpp->mpref;
 up_rhsx = npicp->up_rhsx; 

 /* AIV 10/22/08 - need to restore idp because these may be called */
 /* from nchg wrapper code - expecting idp to be put back */
 /* has_lds_after is always true */
 gen_iconn(up_rhsx, down_lhsx, downmdp, __inst_mod, npp->elnpp.eii, TRUE);

 __emit_complete();
 if (nd_itpop) __pop_itstk();
}

/*
 * generate code for the iconn assign
 */
static void gen_iconn(struct expr_t *up_rhsx, struct expr_t *down_lhsx,
 struct mod_t *downmdp, struct mod_t *upmdp, int32 inum, int32 has_lds_after)
{
 int32 down_idp_ti, save_idp_ti;
 struct itree_t *itp, *downitp;

 /* same iconn code as before */
 if (down_lhsx->x_multfi)
  {
   /* move to down mdprt lhs inst tree location */
   /* eval rhsx in it context then move to other side */
   __push_itstk(downmdp->moditps[0]);
//AIV FIXME - isn't this always true because of multfi
   down_idp_ti = __emit_todowniconn_inst(inum);
   gen_set_save_idp(down_idp_ti, &save_idp_ti, TRUE);

   /* if port fi>1, no need to eval rhs since no stored driver */
   if (down_lhsx->optyp == LCB) 
    {
     gen_multfi_decl_lhscat(down_lhsx);
    }
   else gen_mdr_assgn_or_schd_insns(down_lhsx);

   __pop_itstk();
   __gen_restore_idp(save_idp_ti);
   /* AIV 05/17/07 - need to reset the nchg action */
   return;
  }
 
 if (upmdp->flatinum == 1)
  {
   itp = upmdp->moditps[0];
   downitp = &(itp->in_its[inum]);
   /* AIV 05/27/08 - should have been passing 0 for one inst inum case */
   gen_np_iconn(down_lhsx, up_rhsx, itp, downitp, TRUE, 0, has_lds_after);
   return;
  }

 itp = upmdp->moditps[0];
 downitp = &(itp->in_its[inum]);
 gen_np_iconn(down_lhsx, up_rhsx, itp, downitp, FALSE, inum, has_lds_after);
}


/*
 * generate the code to do the ICONN
 */
static void gen_np_iconn(struct expr_t *down_lhsx, struct expr_t *up_rhsx, 
 struct itree_t *upitp, struct itree_t *downitp, int32 oneinst, int32 nppi,
 int32 has_lds_after)
{
 int32 up_rhs_ti, up2_rhs_ti, rhswid, save_idp_ti, down_idp_ti; 

 save_idp_ti = -1;
 up_rhs_ti = -1;
 __push_itstk(upitp);

 /* AIV 07/08/08 - if both side have on instance try simple port assign */
 /* AIV 08/28/09 - if 64-bit large model avoid using fixed idpdat areas */
#ifdef __CVC32__
 if (oneinst && !down_lhsx->x_stren)
#else
 if (oneinst && !down_lhsx->x_stren && !__cvc_use_large_model)
#endif
  {
   if (downitp->itip->imsym->el.emdp->flatinum == 1)
    {
     if (gen_one_to_one_port_assign(up_rhsx, down_lhsx, 0, 0))
      {
       __pop_itstk();
       return;
      }
    }
  }

 /* AIV 05/21/08 - this can only work for the one inst case - since */
 /* both sides have variable runtime values */
#ifdef __CVC32__
 if (oneinst) __known_inum = nppi;
#else
 if (oneinst && !__cvc_use_large_model) __known_inum = nppi;
#endif
 __need_net_addr = TRUE;
 /* because for MIPD delays delay put on net change propagate */
 /* ports never have delays and therefore no stored driving values */
 if (down_lhsx->x_stren)
  {
   /* case 1: down lhs is stren */

   /* this adds strong or uses stren present - natural unchanged size */
   up2_rhs_ti = gen_ndst_expr_eval(up_rhsx);
   rhswid = __get_tnwid(up2_rhs_ti);

   /* widening here must z extend - narrowing will only copy part from ptr */
   if (rhswid < down_lhsx->szu.xclen)
    {
     up_rhs_ti = gen_svec_widen(down_lhsx->szu.xclen, up2_rhs_ti, ST_HIZ);
    }
   else up_rhs_ti = up2_rhs_ti;
  } 
 else
  {
   /* case 2: down lhs non stren */ 
   /* SJM 01/29/07 - this calculates too many time */
   up_rhs_ti = __gen_expr_eval(up_rhsx, -1);
  }
 __pop_itstk();
 __need_net_addr = FALSE;
 __known_inum = -1;

 __push_itstk(downitp);
 if (oneinst)
  {
   down_idp_ti = __gen_mdata_value(downitp);
  }
 else down_idp_ti = __emit_todowniconn_inst(nppi);

 /* AIV 10/20/08 - like down this only should have idp if has another */
 /* npp on after this one is executed it is common to have only one */
 gen_set_save_idp(down_idp_ti, &save_idp_ti, has_lds_after);

 /* lhs cat decompose handles fi>1 case */ 
 if (down_lhsx->optyp == LCB)
  {
   if (down_lhsx->x_stren) 
    {
     gen_stren_decl_lhscat(down_lhsx, up_rhs_ti);
    }
   else gen_decl_lhscat(down_lhsx, up_rhs_ti);
  }
 else
  {
   /* NOTICE - do not need add stren form since for immed, rhs has stren */
   /* for fi>1 or schedule back side iop to add will be stren gened there */
   if (down_lhsx->lhsx_ndel) 
    {
     gen_sched_conta_assign(down_lhsx, up_rhs_ti);
    }
   else
    {
     if (down_lhsx->x_stren) gen_stren_conta_assgn(down_lhsx, up_rhs_ti);
     else gen_conta_assgn(down_lhsx, up_rhs_ti);
    }
  }
 if (has_lds_after)
  {
   __gen_restore_idp(save_idp_ti);
  }
 __pop_itstk();
}

/*
 * do a basic port assign where both side of the port have only one instance
 * and don't need to do any recording or converting
 *
 *  usually just product this code for the port assign
 *	movl	__idpdat_0 + 40, %eax
 *	movl	%eax, __idpdat_1 + 40
 */
static int32 gen_one_to_one_port_assign(struct expr_t *from_xp, 
 struct expr_t *to_xp, int32 from_inum, int32 to_inum)
{
 struct net_t *to_np, *from_np;
 int32 from_np_ti, to_np_ti, t1_ti, nbytes;

 /* both not sides of port must just be whole net */
 if (from_xp->optyp != ID) return(FALSE);
 if (to_xp->optyp != ID) return(FALSE);
 
 /* if need to do conversion of type or width return */
 to_np = to_xp->lu.sy->el.enp;
 from_np = from_xp->lu.sy->el.enp;

 /* AIV 10/17/08 - if force cannot do this code must do regular conta */
 if (to_np->frc_assgn_allocated || from_np->frc_assgn_allocated)
   return(FALSE);

// AIV ??? think this is ok to just take the low part????? - no stren here
 /* AIV 08/18/10 - now must match the 2-state and 4-state as well */
 if (to_np->nwid != from_np->nwid || from_np->srep != to_np->srep || 
     from_np->n_2state != to_np->n_2state)
   return(FALSE);


 /* if need record do normal assign */
 if (__net_chg_nd_store(to_np, -1, -1)) return(FALSE);
         
 from_np_ti = gen_fixed_mdata_net_loc(from_np, from_inum);
 to_np_ti = gen_fixed_mdata_net_loc(to_np, to_inum);

 /* do simple assign */
 /* movb	__idpdat_0 + 40, %eax */
 /* movb	%eax, __idpdat_1 + 40 */
 /* AIV 10/16/08 - word align made these movl */
 if (to_np->srep == SR_SCAL || to_np->srep == SR_SSCAL || 
     to_np->srep == SR_SCAL2S) 
  {
   t1_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, from_np_ti);
   __st_insn(I_STOREA, AM_REG, t1_ti, AM_NDXREG, to_np_ti);
  }
 else 
  {
   /* create copy for later expansion */
   if (to_np->n_2state) nbytes = wlen_(to_np->nwid)*WRDBYTES;
   else nbytes = 2*wlen_(to_np->nwid)*WRDBYTES;

   __emit_copy(nbytes, from_np_ti, to_np_ti);
  }
 return(TRUE);
}

/*
 * get a fixed __idpdat_ location tmp
 * ie __idpdat_1 + 40
 */
static int32 gen_fixed_mdata_net_loc(struct net_t *np, int32 inum)
{
 struct tn_t *tnp;
 int32 mdat_ti;
 int32 np_ti;
 struct mod_t *in_mdp;
 size_t offset;

 __get_nets_containing_sy(np, &(in_mdp));
 mdat_ti = __gen_mdat_storage_area(in_mdp);
 offset = WRDBYTES*(inum*in_mdp->mod_idata_siz);
 /* DBG remove -- */
 if (offset > (in_mdp->flatinum*in_mdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ------ */

 /* get the fixed net offset for this inum */
 offset += (np->nva_ofs*WRDBYTES);
 np_ti = __con_adradd_insn(np->srep, np->nwid, mdat_ti, offset);
 tnp = &(__tntab[np_ti]);
 tnp->idp_typ = COMLAB_IDPDAT;
 tnp->tn_typ = TN_ADR;
 return(np_ti);
}

/*
 * generate insns for NP MDPRT nchg npp - for output port
 *
 * rhs expr is down mdprt and up lhs is the iconn highconn that may differ 
 * for each down inst
 *
 * new algorithm that generates per inst (indexed by inum) jump table where  
 * end of code jumps past end and unc. also jump past end
 *
 * SJM 12/26/02 - must keep jump base for setting same inst pattern offsets
 * during iop gen - freed there
 */
static void gen_np_mdprt_insns(struct net_pin_t *npp, struct bblk_t *after_bbp,
 int32 is_nchg_fg)
{
 int32 ii, ii2, bval;
 int32 num_highconns, some_unc, inum_ti, ninsts, has_lds_after, ndxjmp_nxti;
 int32 has_shared_blocks;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;

 downmdp = npp->elnpp.emdp;
 mpp = &(downmdp->mpins[npp->obnum]);
 if (npp->npntyp == NP_PB_MDPRT) mpp = &(mpp->pbmpps[npp->pbi]);

 /* any one up inst mod needed - use 0th inst of down to up */
 has_lds_after = (npp->npnxt != NULL);

 /* if no port flag on can do this optimization otherwise just split up */
 /* inum cases in port flatten */
 /* SJM 06-17-07 - can't flatten port because ndx reg disps mashed */
 if (downmdp->flatinum == 1)
  {
   /* if all highconn same - can gen for any inst */
   gen_1inst_np_mdprt_insns(npp, mpp, 0, downmdp, TRUE, has_lds_after, FALSE);
   return;
  }

 /* AIV 07/20/09 - if optimize port flag is on do special scalar-scalar */
 /* code instead of code with the index jump C_* */
 if (npp->scalar_mdprt_ofs != 0)
  {
   gen_1inst_np_mdprt_insns_scalar_optim(npp, mpp, downmdp);
   return;
  }

 /* glb jmp base is the control table for gening md port nchg propagate code */
 /* val -2 if unc., -1 if first, >= 0 is index of earlier same highconn */
 bval = gen_bld_peri_basendx(npp, downmdp);
 /* if all unconn return - nothing to generate */
 if (bval == -2)
  {
   return;
  }
 else 
  {
   /* if large number of instances just flatten */
   if (bval == -1) goto flatten;
  }

 /* if all unc., nothing to generate */
 for (ii = 0; ii < downmdp->flatinum; ii++)
  {
   if (__jmpbase[ii] == -1) goto chk_1inst;
   if (__jmpbase[ii] == -2) continue;
   /* know earlier duplicated - can just ignore */
  }
 return;

chk_1inst:
 /* if only 1 non -1, simple one inst case */
 /* can only happen if all but one highconn itree loc, unc. */
 some_unc = FALSE;
 for (ii2 = -1, num_highconns = 0, ii = 0; ii < downmdp->flatinum; ii++)
  {
   if (__jmpbase[ii] == -1)
    { 
     num_highconns++; 
     ii2 = ii;
    }
   else if (__jmpbase[ii] == -2) some_unc = TRUE;
   /* if earlier duplicated - can just ignore */
  }
 if (some_unc) num_highconns++;
 if (num_highconns == 1)
  {
   /* if all highconn same - can gen for any inst */
   gen_1inst_np_mdprt_insns(npp, mpp, ii2, downmdp, FALSE, has_lds_after, TRUE);
   return;
  }

 /* fill glb ndx jmp tab with bblks for each entry in table */ 
flatten:
 ninsts = downmdp->flatinum;

 after_bbp = __alloc_bblk(FALSE);

 if (ninsts >= __ndxjmp_bbtab_siz) __grow_ndxjmpbbtab(ninsts);

 /* fill glb ndx jmp tab with bblks for each entry in table */ 
 ndxjmp_nxti = 0;
 has_shared_blocks = FALSE;
 for (ii = 0; ii < ninsts; ii++) 
  {
   if (__jmpbase[ii] == -2)
    {
     /* case 1: unc. highconn - mark so will fill with bblk after end */
     __ndxjmp_bbtab[ndxjmp_nxti++] = after_bbp;
     continue;
    }
   if (__jmpbase[ii] >= 0)
    {
     has_shared_blocks = TRUE;
     /* case 2: vinsns for this iop already gened */ 
     /* set to label ref of first - know exists since earlier in array */
     __ndxjmp_bbtab[ndxjmp_nxti++] = __ndxjmp_bbtab[__jmpbase[ii]];
     continue;
    }
   __ndxjmp_bbtab[ndxjmp_nxti++] = __alloc_bblk(FALSE);
  }
 inum_ti = __emit_inum();

 /* know inum in range */
 /* SJM 01/23/07 - since building new bigger tab with non dup sets */
 /* do not alloc - just pass the filled reused global ndx jmp tab */
 __emit_ndx_jmp(inum_ti, __ndxjmp_bbtab, ninsts);
   
 /* gnerate the mdprt np change for each highconn */
 for (ii = 0; ii < ninsts; ii++) 
  {
   if (__jmpbase[ii] != -1) continue;
  
   __start_bblk(__ndxjmp_bbtab[ii]);
    
   /* case 3: gen mdprt np change for one highconn loc */ 
   /* this generates the per inst area for each inst */
   gen_1inst_np_mdprt_insns(npp, mpp, ii, downmdp, FALSE, has_lds_after,
    has_shared_blocks);

   /* AIV 05/22/08 - to avoid the problem of many blocks jumping to one */
   /* block - should be just returning for the common case */
   //SJM????? - if there are loads after this could still have performance 
   //problem then removing the empty blocks
   if (has_lds_after)
    {
     if (ii != ninsts - 1) __emit_jmp(after_bbp);
    }
   else if (is_nchg_fg) 
    {
     if (ii != ninsts - 1) __emit_next_nchg_event();
    }
   else __emit_complete();
  }
 __start_bblk(after_bbp);
}

/*
 * generate insns for one inst NP MDPRT nchg npp itree loc (inum)
 * returns F if unc. so no vinsns gened else T 
 *
 * rhs expr is down mdprt (that changes and is inst of npp) and up lhs
 * is the iconn
 *
 * for different highconns this routine called once or each highconn
 * (may be many all same insts if up inst contained in multiple inst
 * mod) - caller inserts the per instance table jump and jumps to
 * end after
 */
static void gen_1inst_np_mdprt_insns(struct net_pin_t *npp,
 struct mod_pin_t *mpp, int32 ii, struct mod_t *downmdp, int32 oneinst,
 int32 has_lds_after, int32 has_shared_blocks)
{
 int32 down_rhs_ti, down2_rhs_ti, down3_rhs_ti;
 int32 save_idp_ti, up_idp_ti;
 struct itree_t *itp;
 struct inst_t *ip;
 struct expr_t *up_lhsx, *down_rhsx;

#ifndef __CVC32__
 /* AIV 08/28/09 - if large 64-bit model avoid fixed idpdat areas */
 if (__cvc_use_large_model) oneinst = FALSE;
#endif
 itp = downmdp->moditps[ii];
 /* this is an instance of mod containing rhs output port load */
 ip = itp->itip;

 if (npp->npntyp == NP_PB_ICONN) 
  up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
 else up_lhsx = ip->ipins[npp->obnum];
 down_rhsx = mpp->mpref;

 /* if unconnected nothing to generate */ 
 if (up_lhsx->optyp == OPEMPTY) return;

 /* if port fi>1 no need to eval rhs since no stored driver */
 /* because for MIPD delays, delay put on net change propagate */
 down_rhs_ti = -1;

 /* AIV 05/21/08 - if no shared blocks set the known inum */
#ifdef __CVC32__
 if (!has_shared_blocks) __known_inum = ii;
 else __known_inum = -1;
#else
 /* AIV 08/28/09 - if 64-bit large model avoid using fixed idpdat areas */
 if (!has_shared_blocks && !__cvc_use_large_model) __known_inum = ii;
 else __known_inum = -1;
#endif

 /* AIV 07/08/08 - if both side have on instance try simple port assign */
 /* AIV 09/03/08 - cannot use this code is up expr has strength */
 if (__known_inum != -1 && oneinst && !up_lhsx->x_multfi && !up_lhsx->x_stren) 
  {
   if (gen_one_to_one_port_assign(down_rhsx, up_lhsx, ii, 0))
    {
     __known_inum = -1;
     return;
    }
  }

 /* if one instance see if still needs idp loaded - if flag not set */
 /* always load the idps */
 if (!up_lhsx->x_multfi) 
  {
   /* if one instance know it mark as using design wide idp */
   __need_net_addr = TRUE;
   /* ports never have delays and therefore no stored driving values */
   if (up_lhsx->x_stren)
    {
     /* case 1: up lhs is stren */
     if (down_rhsx->x_stren)
      {
       /* case 1a: down rhs is also stren */
       down2_rhs_ti = gen_ndst_expr_eval(down_rhsx);
       if (__get_tnwid(down2_rhs_ti) < up_lhsx->szu.xclen)
        {
         down_rhs_ti = gen_svec_widen(up_lhsx->szu.xclen, down2_rhs_ti,
          ST_HIZ);
        }
       else down_rhs_ti = down2_rhs_ti;
      }
     else
      {
       /* case 1b: up rhs non stren */
       /* AIV 11/10/09 - want a vector here */
       down3_rhs_ti = __gen_expr_eval(down_rhsx, WANT_A_VEC);
       /* size must match exactly before adding stren */
       down2_rhs_ti = __gen_cnvt_srep_ifneeded(down3_rhs_ti, SR_VEC,
        up_lhsx->szu.xclen, up_lhsx->has_sign, FALSE, TRUE);
       /* AIV 12/28/06 - was passing the wrong width to convert */
       down_rhs_ti = gen_st_standval(down_rhsx->szu.xclen, down2_rhs_ti, 
         ST_STRVAL);
      }
     if (up_lhsx->x_stren && down_rhsx->szu.xclen < up_lhsx->szu.xclen)
      {
       down_rhs_ti = __gen_cnvt_srep_ifneeded(down_rhs_ti, SR_SVEC, 
        up_lhsx->szu.xclen, FALSE, FALSE, TRUE);
      }
    }
   else
    {
     /* case 2: down lhs non stren */ 
     down_rhs_ti = __gen_expr_eval(down_rhsx, -1);
     /* size must match exactly before adding stren */
     /* AIV 01/15/07 - widen bug that was fixed in interp  never fixed here */
     /* widen to lhs width with z's - if too narrow, high part just unused */
     /* SJM 05/10/04 - no sign extension because widening to z'x */
     /* SJM 11/21/06 - for stren's xsp is 4 times width for byte per bit */
     /* problem is xslen for stren is not the expr bit width */
     if (up_lhsx->x_stren && down_rhsx->szu.xclen < up_lhsx->szu.xclen)
      {
       down_rhs_ti = __gen_cnvt_srep_ifneeded(down_rhs_ti, SR_SVEC, 
        up_lhsx->szu.xclen, FALSE, FALSE, TRUE);
      }
    }
  }
 __known_inum = -1;
 __need_net_addr = FALSE;

 /* move to containing inst */
 __push_itstk(itp->up_it);
 save_idp_ti = -1;

 /* SJM 12/01/07 - do not need the nlo idp label here */

 /* not one instance must get the up idp */
 if (oneinst) up_idp_ti = __gen_mdata_value(itp->up_it);
 else up_idp_ti = __emit_toupmdprt_inst();

 /* if has loads following this need to save the current idp */
 gen_set_save_idp(up_idp_ti, &save_idp_ti, has_lds_after);

 /* lhs cat decompose handles fi>1 case */ 
 if (up_lhsx->optyp == LCB)
  {
   /* SJM 12/14/05 - for up (high con) fi>1 lhs concat need to gen */
   /* lhs concat fi>1 code */
   if (up_lhsx->x_multfi) gen_multfi_decl_lhscat(up_lhsx);
   else gen_decl_lhscat(up_lhsx, down_rhs_ti);
  }
 else
  {
   /* case 1: fi>1 - assign to the entire lhs wire */
   if (up_lhsx->x_multfi)
    {
     /* since in up lhs port sink iconn itree cntxt - normal fi>1 works */
     gen_mdr_assgn_or_schd_insns(up_lhsx);
    }
   else
    {
     /* NOTICE - do not need add stren form since for immed, rhs has stren */
     /* for fi>1 or sched, back side iop to add will be stren gened there */
     if (up_lhsx->lhsx_ndel) 
      {
       gen_sched_conta_assign(up_lhsx, down_rhs_ti);
      }
     else
      {
       if (up_lhsx->x_stren) gen_stren_conta_assgn(up_lhsx, down_rhs_ti);
       else gen_conta_assgn(up_lhsx, down_rhs_ti);
      }
    }
  }
 /* AIV 05/07/07 - has loads after this one so need to save inum */
 if (has_lds_after)
  {
   __gen_restore_idp(save_idp_ti);
  }
 __pop_itstk();
}

/*
 * do a scalar to scalar optimized NP_MDPRT down port 
 * 
 *  this code uses value placed in idp area at load time - this prevents
 *  compile time wasted from C_ index jumps and increases perfomance
 *  for large gate designs
 *
 *  this works by loading net offset, net changes address, and net address
 *  from idp area - removing the need for the initial index jump
 *  which produces code for each instance
 */
static void gen_1inst_np_mdprt_insns_scalar_optim(struct net_pin_t *npp,
 struct mod_pin_t *mpp, struct mod_t *downmdp)
{
 size_t ofs;
 int32 down_rhs_ti, new_val_ti, up_idp_ti, np_ti, save_idp_ti;
 int32 up_np_ti, up_ofs_ti, nchg_ti, has_toggle;
 int32 has_some_nchg, has_all_nchg, has_dmpvs, has_empty, has_dmpps; 
 int32 has_all_bsel, all_bsel_1w, mixed_exprs, all_empty;
 struct itree_t *itp;
 struct inst_t *ip;
 struct expr_t *up_lhsx, *down_rhsx;
 struct net_t *up_np;


 nchg_ti = -1;
 /* get the mdprt flags */
 mixed_exprs = __set_mark_mdprt_flags(npp, &has_all_nchg, &has_some_nchg, 
  &has_dmpvs, &has_dmpps, &has_empty, &has_all_bsel, &all_bsel_1w, 
  &all_empty, &has_toggle);

 /* if all empty nothing to do */
 if (all_empty) return;

 /* AIV 08/18/09 - expanded this scheme to handle 3 common exprs */
 /* handle mixed expressions - opempty, scalar, or bsel */
 if (mixed_exprs) 
  {
   gen_1inst_np_mdprt_insns_optim_mixed_xpr(npp, mpp, downmdp, has_all_nchg,
    has_some_nchg, has_dmpvs, has_dmpps, has_empty, has_all_bsel, all_bsel_1w, 
    has_toggle);
   return;
  }


 itp = downmdp->moditps[0];
 /* this is an instance of mod containing rhs output port load */
 ip = itp->itip;

 if (npp->npntyp == NP_PB_ICONN) 
  up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
 else up_lhsx = ip->ipins[npp->obnum];
 down_rhsx = mpp->mpref;

 /* DBG remove -- */
 if (has_all_bsel) __misc_terr(__FILE__, __LINE__);
 if (has_empty) __misc_terr(__FILE__, __LINE__);
 if (down_rhsx->x_stren) __misc_terr(__FILE__, __LINE__);
 if (up_lhsx->x_multfi)  __misc_terr(__FILE__, __LINE__);
 if (up_lhsx->x_stren) __misc_terr(__FILE__, __LINE__);
 if (up_lhsx->lhsx_ndel) __misc_terr(__FILE__, __LINE__);
 if (up_lhsx->optyp != ID) __misc_terr(__FILE__, __LINE__);
 /* ---- */

  /* case 1b: up rhs non stren */
 down_rhs_ti = __gen_expr_eval(down_rhsx, -1);
 new_val_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, down_rhs_ti);
 
 ofs = npp->scalar_mdprt_ofs;
 /* get the up nets offset and move it into a reg */
 up_ofs_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
 up_ofs_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, up_ofs_ti);

 /* AIV BEWARE - these offsets are order dependent from here down */
 /* if has net change get the offset and load it into a reg */
 if (has_some_nchg)
  {
   ofs++;
   nchg_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
   nchg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, nchg_ti);
  }

 /* if has net dumpvars get the offset and load it into a reg */
 np_ti = -1;
 /* AIV 12/06/10 - if has change call wrapper to add to toggle list */
 if (has_dmpvs || has_toggle)
  {
   ofs++;
   np_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
   np_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG, np_ti);
  }

 /* move to containing inst */
 __push_itstk(itp->up_it);

 up_idp_ti = __emit_toupmdprt_inst();
 save_idp_ti = -1;
 if (has_some_nchg || has_dmpvs || has_toggle)
  {
   /* AIV 08/14/09 - allowing multiple npp types - may need to now save idp */
   if (npp->npnxt != NULL)
    {
     save_idp_ti = __emit_save_cur_idp();
    }
   __st_insn(I_STOREA, AM_NDXREG, up_idp_ti, AM_REG, IDP_REG);
   up_idp_ti = IDP_REG;
  }

 /* dumpvars needs global __idp set */
 if (has_dmpvs || has_toggle)
  {
   __st_insn(I_STOREA, AM_REG, IDP_REG, AM_NLO, NLO_IDP);
  }

 up_np_ti = __emit_add(WBITS, up_ofs_ti, up_idp_ti);
 up_np = up_lhsx->lu.sy->el.enp;

 /* record slotend changes */
 if (up_np->dmpv_in_src) __cvc_slotend_action |= SE_DUMPVARS;
 else if (up_np->dmpp_in_src) __cvc_slotend_action |= SE_DUMPPORTS;
 if (up_np->n_has_toggle) __cvc_slotend_action |= SE_TOGGLE;

 gen_one_scalar_optim_mdprt_scalar(has_some_nchg, has_all_nchg, has_dmpvs,
  has_dmpps, nchg_ti, np_ti, up_np_ti, new_val_ti, up_idp_ti, has_toggle);

 if (save_idp_ti != -1) __gen_restore_idp(save_idp_ti);
 __pop_itstk();
}

/* 
 * AIV 08/18/09 - expanded this scheme to handle 3 common exprs 
 *
 * handle mdprt with up lhsx mixed expressions - opempty, scalar, or bsel 
 */
static void gen_1inst_np_mdprt_insns_optim_mixed_xpr(struct net_pin_t *npp,
 struct mod_pin_t *mpp, struct mod_t *downmdp, int32 has_all_nchg,
 int32 has_some_nchg, int32 has_dmpvs, int32 has_dmpps, int32 has_empty, 
 int32 has_all_bsel, int32 all_bsel_1w, int32 has_toggle)
{
 size_t ofs;
 int32 down_rhs_ti, up_idp_ti, np_ti, save_idp_ti, cint_ti, new_val_ti;
 int32 up_np_ti, up_ofs_ti, nchg_ti, lhsx_ti, nchg2_ti;
 struct itree_t *itp;
 struct inst_t *ip;
 struct expr_t *up_lhsx, *down_rhsx;
 struct bblk_t *bsel_bbp, *scalar_bbp, *done_bbp, *conn_bbp, *unconn_bbp;
 struct bblk_t *store_bbp, *nchg_bbp;

 unconn_bbp = scalar_bbp = NULL;
 itp = downmdp->moditps[0];
 /* this is an instance of mod containing rhs output port load */
 ip = itp->itip;

 if (npp->npntyp == NP_PB_ICONN) 
  up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi];
 else up_lhsx = ip->ipins[npp->obnum];
 down_rhsx = mpp->mpref;

 /* DBG remove -- */
 if (down_rhsx->x_stren) __misc_terr(__FILE__, __LINE__);
 if (up_lhsx->x_multfi)  __misc_terr(__FILE__, __LINE__);
 if (up_lhsx->x_stren) __misc_terr(__FILE__, __LINE__);
 if (up_lhsx->lhsx_ndel) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* AIV BEWARE - these offsets are order dependent from here down */
 ofs = npp->scalar_mdprt_ofs;
 /* get the up nets offset and move it into a reg */
 up_ofs_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
 up_ofs_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, up_ofs_ti);

 /* if has empty and is unconnected this will be 0 */
 if (has_empty)
  {
   unconn_bbp = __alloc_bblk(FALSE);
   conn_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(unconn_bbp, conn_bbp, up_ofs_ti);
   __start_bblk(conn_bbp);
  }


  /* case 1b: up rhs non stren */
 down_rhs_ti = __gen_expr_eval(down_rhsx, -1);
 /* notice no 2-state special code needed here since - no conversions */
 new_val_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_NDXREG, 
  down_rhs_ti);
 
 ofs++;
 lhsx_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
 lhsx_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, lhsx_ti);

 /* if has net change get the offset and load it into a reg */
 nchg_ti = -1;
 if (has_some_nchg)
  {
   ofs++;
   nchg_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
   nchg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, nchg_ti);
  }

 /* if has net dumpvars get the offset and load it into a reg */
 np_ti = -1;
 /* AIV 12/06/10 - if has change call wrapper to add to toggle list */
 if (has_dmpvs || has_toggle)
  {
   ofs++;
   np_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, WRDBYTES*ofs);
   np_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG, np_ti);
  }

 /* move to containing inst */
 __push_itstk(itp->up_it);

 up_idp_ti = __emit_toupmdprt_inst();
 save_idp_ti = -1;
 if (has_some_nchg || has_dmpvs || has_dmpps || has_toggle)
  {
   /* AIV 08/14/09 - allowing multiple npp types - may need to now save idp */
   if (npp->npnxt != NULL)
    {
     save_idp_ti = __emit_save_cur_idp();
    }
   __st_insn(I_STOREA, AM_NDXREG, up_idp_ti, AM_REG, IDP_REG);
   up_idp_ti = IDP_REG;
  }

 /* dumpvars needs global __idp set */
 if (has_dmpvs || has_toggle)
  {
   __st_insn(I_STOREA, AM_REG, IDP_REG, AM_NLO, NLO_IDP);
  }

 up_np_ti = __emit_add(WBITS, up_ofs_ti, up_idp_ti);

 /* record slotend changes */
 if (has_dmpvs) __cvc_slotend_action |= SE_DUMPVARS;
 else if (has_dmpps) __cvc_slotend_action |= SE_DUMPPORTS;
 if (has_toggle) __cvc_slotend_action |= SE_TOGGLE;

 done_bbp = __alloc_bblk(FALSE);
 /* if need to check for scalar if not all bsel */
 if (!has_all_bsel)
  {
   bsel_bbp = __alloc_bblk(FALSE);
   scalar_bbp = __alloc_bblk(FALSE);
   cint_ti = __gen_cint_tn(-1);

   __emit_jmp_eq(scalar_bbp, bsel_bbp, lhsx_ti, cint_ti);
   __start_bblk(bsel_bbp);
  }

 /* do the code to do the bit select - currently all wrappers */
 if (nchg_ti == -1)
  {
   if (has_dmpvs || has_dmpps || has_toggle) 
    {
     __emit_call_mdprt_bsel_dmpv(lhsx_ti, up_np_ti, new_val_ti, all_bsel_1w, 
      has_dmpps, np_ti);
    }
   else __emit_call_mdprt_bsel(lhsx_ti, up_np_ti, new_val_ti, all_bsel_1w);
  }
 else 
  {
   if (!has_all_nchg)
    {
     store_bbp = __alloc_bblk(FALSE);
     nchg_bbp = __alloc_bblk(FALSE);
     __emit_jmp_0(store_bbp, nchg_bbp, nchg_ti);
     __start_bblk(nchg_bbp);
     nchg2_ti = __emit_add(WBITS, nchg_ti, up_idp_ti);
     nchg2_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG, nchg2_ti);
     if (has_dmpvs || has_dmpps || has_toggle) 
      {
       __emit_call_mdprt_bsel_nchg_dmpv(lhsx_ti, up_np_ti, new_val_ti, 
        nchg2_ti, all_bsel_1w, has_dmpps, np_ti);
      }
     else
      {
       __emit_call_mdprt_bsel_nchg(lhsx_ti, up_np_ti, new_val_ti, 
        nchg2_ti, all_bsel_1w);
      }
     __emit_jmp(done_bbp);

     __start_bblk(store_bbp);
     if (has_dmpvs || has_dmpps || has_toggle) 
      {
       __emit_call_mdprt_bsel_dmpv(lhsx_ti, up_np_ti, new_val_ti, all_bsel_1w, 
        has_dmpps, np_ti);
      }
     else
      {
       __emit_call_mdprt_bsel(lhsx_ti, up_np_ti, new_val_ti, all_bsel_1w);
      }
    }
   else
    {
     nchg2_ti = __emit_add(WBITS, nchg_ti, up_idp_ti);
     nchg2_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG, nchg2_ti);
     if (has_dmpvs || has_dmpps || has_toggle) 
      {
       __emit_call_mdprt_bsel_nchg_dmpv(lhsx_ti, up_np_ti, new_val_ti, 
        nchg2_ti, all_bsel_1w, has_dmpps, np_ti);
      }
     else
      {
       __emit_call_mdprt_bsel_nchg(lhsx_ti, up_np_ti, new_val_ti, nchg2_ti, 
        all_bsel_1w);
      }
    }
  }
 __emit_jmp(done_bbp);

 /* do the scalar code */
 if (!has_all_bsel)
  {
   __start_bblk(scalar_bbp);
   gen_one_scalar_optim_mdprt_scalar(has_some_nchg, has_all_nchg, has_dmpvs,
    has_dmpps, nchg_ti, np_ti, up_np_ti, new_val_ti, up_idp_ti, has_toggle);
   __emit_jmp(done_bbp);
  }

 __start_bblk(done_bbp);
 if (save_idp_ti != -1) __gen_restore_idp(save_idp_ti);
 if (has_empty)
  {
   __start_bblk(unconn_bbp);
  }
 __pop_itstk();
}

/*
 * generate code for a scalar id to id mdprt 
 */
static void gen_one_scalar_optim_mdprt_scalar(int32 has_some_nchg, 
 int32 has_all_nchg, int32 has_dmpvs, int32 has_dmpps, int32 nchg_ti, 
 int32 np_ti, int32 up_np_ti, int32 new_val_ti, int32 up_idp_ti, 
 int32 has_toggle)
{
 struct nchglst_t *nchgp;
 int32 triggered_ti;
 size_t offset;
 struct bblk_t *nchg_bbp, *store_bbp, *done_bbp, *check_trigger_bbp;
 struct bblk_t *add_nchg_bbp, *dmpv_bbp;

 store_bbp = NULL;
 /* no net changes produce simple code */
 if (!has_some_nchg)
  {
   /* if dumpvars check for change */
   if (has_dmpvs || has_dmpps || has_toggle) 
    {
     done_bbp = __alloc_bblk(FALSE);
     store_bbp = __alloc_bblk(FALSE);
     dmpv_bbp = __alloc_bblk(FALSE);

     up_np_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, up_np_ti);
     __emit_jmp_eq(store_bbp, dmpv_bbp, new_val_ti, up_np_ti);
     __start_bblk(dmpv_bbp);

     __st_insn(I_STOREA, AM_REG, new_val_ti, AM_NDXREG, up_np_ti);

     if (has_dmpvs) 
      {
       __emit_add_dmpvlst_mdprt(np_ti);
      }
     else if (has_dmpps) 
      {
       __emit_add_dmpportlst_mdprt(np_ti);
      }
     if (has_toggle) 
      {
       __emit_add_togglelst_el_port(np_ti);
      }
     __emit_jmp(done_bbp);

     __start_bblk(store_bbp);
     __st_insn(I_STOREA, AM_REG, new_val_ti, AM_NDXREG, up_np_ti);
     __emit_jmp(done_bbp);

     __start_bblk(done_bbp);
    }
   else
    {
     /* no recording simple assign */
     __st_insn(I_STOREA, AM_REG, new_val_ti, AM_NDXREG, up_np_ti);
    }
   return;
  }


 /* contians at least some net changes here */
 up_np_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, up_np_ti);
 done_bbp = __alloc_bblk(FALSE);
 check_trigger_bbp = __alloc_bblk(FALSE);
 add_nchg_bbp =  __alloc_bblk(FALSE);

 /* mixed nchg and not must check for NULL to see if record is needed */
 if (!has_all_nchg)
  {
   store_bbp = __alloc_bblk(FALSE);
   nchg_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(store_bbp, nchg_bbp, nchg_ti);
   __start_bblk(nchg_bbp);
  }

 /* check the net change */
 __emit_jmp_eq(done_bbp, check_trigger_bbp, new_val_ti, up_np_ti);
 __start_bblk(check_trigger_bbp);
 __st_insn(I_STOREA, AM_REG, new_val_ti, AM_NDXREG, up_np_ti);

 nchgp = &__nchg_dummy_hd;
 offset = (byte *) &(nchgp->triggered) - (byte *) nchgp;
 /* DBG remove -- */
 if (offset != 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 nchg_ti = __emit_add(WBITS, nchg_ti, up_idp_ti);
 nchg_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG, nchg_ti);

 /* check to see if already on the list */
 triggered_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, nchg_ti);
 __emit_jmp_0(add_nchg_bbp, done_bbp, triggered_ti);
 __start_bblk(add_nchg_bbp);

 /* add it to the list */
 gen_add_static_nchglst(FALSE, nchg_ti);
 if (has_dmpvs) __emit_add_dmpvlst_mdprt(np_ti);
 else if (has_dmpps) __emit_add_dmpportlst_mdprt(np_ti);
 if (has_toggle) __emit_add_togglelst_el_port(np_ti);

 __emit_jmp(done_bbp);


 /* mixed net changes */
 if (!has_all_nchg)
  {
   __start_bblk(store_bbp);
   __st_insn(I_STOREA, AM_REG, new_val_ti, AM_NDXREG, up_np_ti);
   if (has_dmpvs) __emit_add_dmpvlst_mdprt(np_ti);
   else if (has_dmpps)  __emit_add_dmpportlst_mdprt(np_ti);
   if (has_toggle) __emit_add_togglelst_el_port(np_ti);
   __emit_jmp(done_bbp);
  }

 __start_bblk(done_bbp);
}

/*
 * build the per inst processing table - this builds global jmp base table
 *
 * only called if needed, i.e. at least 2 highconns differ
 * -2 is unc., -1 is first, >= 0 is index of earlier with same highconn
 */
static int32 gen_bld_peri_basendx(struct net_pin_t *npp, struct mod_t *downmdp)
{
 int32 ii;
 int32 ii2, all_empty;
 struct itree_t *itp, *up_itp2;
 struct inst_t *ip;
 struct mod_t *up_mdp;
 struct expr_t *up_rhsx;
 
 /* DBG remove -- */
 if (downmdp->flatinum == 1) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (__jmpbas_tabsiz < downmdp->flatinum) grow_jmpbasetab(downmdp->flatinum);

 /* AIV 08/18/09 - bad algorithm below - just flatten for a large number */
 /* of instances - AIV LOOKATME 1000???? */ 
 if (downmdp->flatinum > 1000 && !__inline_code)
  {
   all_empty = TRUE;
   for (ii = 0; ii < downmdp->flatinum; ii++) 
    {
     itp = downmdp->moditps[ii];
     ip = itp->itip;
 
     if (npp->npntyp == NP_PB_MDPRT)
      { up_rhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi]; }
     else up_rhsx = ip->ipins[npp->obnum];

     /* just mark as -1 - produce code or -2 - empty */
     if (up_rhsx->optyp == OPEMPTY) __jmpbase[ii] = -2;
     else 
      {
       __jmpbase[ii] = -1;
       all_empty = FALSE;
      }
    }
   
   /* if all empty return -2 */
   if (all_empty)
    {
     return(-2);
    }
   /* if just flatten all instances return -1 */
   return(-1);
  }


 /* -3 means unprocessed */
 for (ii = 0; ii < downmdp->flatinum; ii++) __jmpbase[ii] = -3;

 for (ii = 0; ii < downmdp->flatinum; ii++) 
  {
   if (__jmpbase[ii] != -3) continue;

   itp = downmdp->moditps[ii];
   /* this is an instance of mod containing rhs output port load */
   ip = itp->itip;
 
   /* since ip comes from this insts highconn, each inst may differ */
   if (npp->npntyp == NP_PB_MDPRT)
    { up_rhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi]; }
   /* up expr just needed for getting width */
   else up_rhsx = ip->ipins[npp->obnum];

   /* -2 means empty - peri jump table jumps past end immediately */
   if (up_rhsx->optyp == OPEMPTY) __jmpbase[ii] = -2;
   /* -1 means need to gen some vinsns */
   else __jmpbase[ii] = -1;

   /* find all up insts with same up containing module and same inst */
   /* notice same up matching same as for NP ICONN - just lhs/rhs reversed */
   up_mdp = itp->up_it->itip->imsym->el.emdp;
   for (ii2 = ii + 1; ii2 < downmdp->flatinum; ii2++)
    {
     if (__jmpbase[ii2] == -3)
      { 
       up_itp2 = downmdp->moditps[ii2]->up_it; 
       if (up_itp2 == NULL) continue;
       if (up_mdp != up_itp2->itip->imsym->el.emdp) continue;
       /* must also be same inst in up mod */
       if (ip != downmdp->moditps[ii2]->itip) continue;
       /* DBG remove --
       if (__opt_debug_flg)
        {
         __my_fprintf(stdout,
          "PERI JMPTAB - inst %s(ii=%d) same vinsns as %s(ii=%d)\n", 
          __msg2_blditree(__xs, downmdp->moditps[ii2]), ii2,
          __msg2_blditree(__xs2, downmdp->moditps[ii]), ii);
        }
       -- */
       __jmpbase[ii2] = ii; 
       /* SJM 07/13/03 - if same as previous but prev unc - mark unc. */
       if (__jmpbase[ii] == -2) __jmpbase[ii2] = -2;
      }
    }
  } 
 return(TRUE);
}

/*
 * grow jmpi base global table of per instance jump table indices and markers
 */
static void grow_jmpbasetab(int32 newsiz)
{
 size_t old_tabsiz, osize, nsize;

 /* AIV 06/17/09 - changed these to use size_t */
 old_tabsiz = __jmpbas_tabsiz;
 osize = old_tabsiz*sizeof(int32);
 /* SJM 03/29/05 - 3/2 growth may not be large enough for larg tab */ 
 /* make sure add enough new area */
 __jmpbas_tabsiz = (3*__jmpbas_tabsiz)/2 + newsiz;
 nsize = __jmpbas_tabsiz*sizeof(int32);
 __jmpbase = (int32 *) __my_realloc(__jmpbase, osize, nsize);
}

/*
 * ROUTINE TO GENERATE VINSN FOR GATE NET TERM INPUT CHANGE
 */

/*
 * AIV 11/17/07 - lowered gate wide code propogate needs to use the static
 * net changes from the output of the gate
 */
static void gen_wide_logic_gate(struct gate_t *gp, struct net_pin_t *npp)
{
 struct expr_t *xp;
 struct bblk_t *eval_chg_bbp, *done_bbp;
 int32 gp_ti, eval_chg_ti, chg_ti, old_gateval_ti, new_gateval_ti;
 int32 scal_ngval_ti, srtyp;

 eval_chg_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);
 gp_ti = __gen_gate_adr_tn(gp);
 /* if 2-state get load as SR_SCAL2S */
 xp = gp->gpins[0];
 if (__is_expr_2state(xp)) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;

 chg_ti = __gen_tn(srtyp, WBITS);
 eval_chg_ti = __emit_exec_wide_logic_gate(gp_ti, npp->obnum, chg_ti);

 __emit_jmp_0(done_bbp, eval_chg_bbp, eval_chg_ti);
 __start_bblk(eval_chg_bbp);
 /* AIV 07/06/09 - this was wrong for gates without a delay */
 /* was never testing */
 /* SJM 12/01/07 - really need the moves because of new vm */
 if (gp->g_delrep != DT_NONE)
  {
   old_gateval_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_OLDGVAL);
   new_gateval_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NEWGVAL);
   gen_prop_gatechg(gp, new_gateval_ti, old_gateval_ti, done_bbp, chg_ti);
  }
 else
  {
   scal_ngval_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1, 
    AM_NLO, NLO_NEWGVAL);
   if (xp->x_multfi) 
    {
     gen_mdr_assgn_or_schd_insns(xp);
    }
   else if (xp->x_stren) 
    {
     gen_gate_stren_added_assign(gp, xp, scal_ngval_ti, TRUE);
    }
   else
    {
     if (xp->lhsx_ndel) gen_sched_conta_assign(xp, scal_ngval_ti);
     else gen_conta_assgn(xp, scal_ngval_ti);
    }
   }
 __emit_jmp(done_bbp);
 __start_bblk(done_bbp);
}

/*
 * gen gate input gate eval vinsns
 */
static void gen_np_gate_insns(struct net_pin_t *npp, struct bblk_t *done_bbp)
{
 struct gate_t *gp;
 int32 gi;

 gp = npp->elnpp.egp;
 switch ((byte) gp->g_class) {
  case GC_LOGIC:
   gen_np_chg_logic_gate(npp, done_bbp);
   break;
  case GC_UDP:
   gen_np_chg_udp_gate(npp, done_bbp);
   break;
  case GC_BUFIF:
   gen_np_chg_bufif_gate(npp, done_bbp);
   break;
  case GC_MOS:
   gen_np_chg_mos_gate(npp, done_bbp);
   break;
  case GC_CMOS:
   gen_np_chg_cmos_gate(npp, done_bbp);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 /* AIV 09/14/06 - if has pli access must check for change */
 /* AIV 05/13/09 - access level > 2 for call backs */
 if (__pli_access_level >= 2)
  {
   gi = gp - __inst_mod->mgates;
   __emit_chk_gate_vpi_chg(gi);
  }
}

/*
 * when propagating changes from a wire that connects to an input
 * of a gate - gen vinsns to eval the input, update state, schedule 
 * gate chg if needed and ...
 *
 * the changed input is the constant obnum field of the gate npp
 * AIV 02/15/07 - if gate is a scalar conta place it in its own flow graph
 */
static void gen_np_chg_logic_gate(struct net_pin_t *npp, 
 struct bblk_t *done_bbp) 
{
 struct gate_t *gp;
 struct gate_conta_t *gcp;
 
 gp = npp->elnpp.egp;
 /* gate is a scalar assign just call and later create flow graph */
 if (!__inline_code)
  {
   if (gp->gmsym->el.eprimp->gateid == G_ASSIGN)
    {
     /* DBG remove --- */
     if (npp->obnum != 1) __case_terr(__FILE__, __LINE__); 
     /* --- */
     gcp = __add_gate_expr(gp, npp);
     __emit_call_gate_conta(gcp->gc_ndx);
     return;
    }
  }
 /* not scalar conta just do regular gate logic code */
 gen_chg_logic_gate(npp, done_bbp);
}

/*
 * all scalar conta (gates) are now a seperate flow graph
 * this generates a flow graph for each gate
 */
static void gen_gate_conta_flowgs(void)
{
 int32 i, num;
 struct gate_conta_t *gcp;
 struct avlnode_t **gcp_avltab;
 
 /* linearize tree and create a flow graph for each iconn */
 gcp_avltab = __linearize_avl_tree(__gate_conta_dup_tn_tree, &(num));
 if (num == 0) return;

 /* generate one flow graph for each assign gate */
 for (i = 0; i < num; i++)
  {
   gcp = (struct gate_conta_t *) gcp_avltab[i]->valp;
   /* AIV LOOKATME - per module compile problems if in different module ?? */
   __push_itstk(gcp->mdp->moditps[0]);
   gen_one_gate_conta_flowg(gcp);
   __pop_itstk();
  }
 __my_free(gcp_avltab, num*sizeof(struct avlnode_t *)); 
}
 
/*
 * generate a flow graph for one scalar conta (gate)
 */
static void gen_one_gate_conta_flowg(struct gate_conta_t *gcp)
{
 struct flowg_t *fgp;
 struct bblk_t *enter_bbp, *done_bbp;

 /* create flow graph and then same as old iconn code */
 fgp = __alloc_flowg(FLOWG_GATECA);
 __cur_ifrom_u.from_gateca = gcp->gc_ndx;
 __cur_flowg = fgp;
 gcp->fgp = fgp;
 __cur_bbp = NULL;

 enter_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);
 __start_bblk(enter_bbp); 
 enter_bbp->after_suspend = TRUE;
 __emit_enter_gate_conta(gcp->gc_ndx);
 gen_chg_logic_gate(gcp->npp, done_bbp);
 __start_bblk(done_bbp); 
 __emit_complete();
}


/*
 * generate code for logic gate
 */
static void gen_chg_logic_gate(struct net_pin_t *npp, 
 struct bblk_t *done_bbp) 
{
 int32 gwid, bi, cint_ti, gateid, srtyp;
 int32 inval2_apti, inval_apti, inval_bpti, uwrd1_ti, uwrd_ti;
 int32 gstate_adr_apti, in_all_leaves, i;
 int32 t1_ti, t2_ti, t3_ti;
 int32 gv_apti, gv_bpti, scal_ngval_ti, ogval_ti;
 word32 mask;
 struct gate_t *gp;
 struct expr_t *xp;
 struct bblk_t *state_chg_bbp, *gate_chg_bbp;
 
 /* gpnum is number of terminals - logic gates always num ins plus 1 out */
 /* bi is input number - 0th is output so npp obnum one too high */
 gp = npp->elnpp.egp;
 /* gpnum is number of terminals - logic gates always num ins plus 1 out */
 gwid = gp->gpnum;
 gateid = gp->gmsym->el.eprimp->gateid;

 in_all_leaves = TRUE;
 /* AIV 03/09/09 - if input expressions all leaves can produce better code */
 /* for the narrow version */
 for (i = 1; i < gwid; i++)
  {
   xp = gp->gpins[i];
   if (!__isleaf(xp)) 
    {
     in_all_leaves = FALSE;
     break;
    }
  }
 
 /* if narrow logic gate use the pre-computed table values */
 if (gateid == G_ASSIGN || gateid == G_BUF || gateid == G_NOT) 
  {
   gen_chg_logic_gate_1term(npp, done_bbp);
   return; 
  }
 else if (in_all_leaves && gwid > 2 && gwid < 6)
  {
   gen_chg_logic_gate_narrow_leaves(npp, done_bbp);
   return;
  }
 else if (gwid < 5)
  {
   gen_chg_logic_gate_narrow(npp, done_bbp);
   return; 
  }
 /* bi is input number - 0th is output so npp obnum one too high */
 bi = npp->obnum - 1; 
 xp = gp->gpins[npp->obnum];

 /* need both the scalar and the a/b input terminal connected value */
 /* even if scalar (stren/non stren) - this always converts to non st a/b */
 inval2_apti = __gen_expr_eval(xp, -1);
 /* this may do a size change - but know already a/b */ 
 inval_apti = __gen_cnvt_srep_ifneeded(inval2_apti, SR_VEC, 1, FALSE,
  FALSE, TRUE);

 /* DBG remove -- */
 if (gwid > 16) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* compute new state value in a word */ 
 // uwrd |= ((gav << bi) | (gbv << (gwid + bi)));
 cint_ti = __gen_cint_tn(bi);
 /* SJM 11/13/06 - shift amount now src not dsp operand */
 t1_ti = __emit_shiftl(WBITS, cint_ti, inval_apti);
 inval_bpti = __get_bpti(inval_apti);
 cint_ti = __gen_cint_tn(gwid + bi);
 t2_ti = __emit_shiftl(WBITS, cint_ti, inval_bpti);
 t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);

 // uwrd = ouwrd & ~(1L << bi) & ~(1L << (gwid + bi));
 gstate_adr_apti = __gen_gatebp_tn(gp, WBITS); 
 mask = ~(1UL << bi) & ~(1UL << (gwid + bi));
 cint_ti = __gen_cint_tn(mask);
 uwrd1_ti = __emit_bin_bitand(WBITS, cint_ti, gstate_adr_apti);
 uwrd_ti = __emit_bin_bitor(WBITS, uwrd1_ti, t3_ti);

 state_chg_bbp = __alloc_bblk(FALSE);
 __emit_jmp_eq(done_bbp, state_chg_bbp, uwrd_ti, gstate_adr_apti);

 __start_bblk(state_chg_bbp);

 /* store uwrd (new state) into state value */
 // __idp[gp->gstate_ofs] = uwrd;
 __emit_copy(WRDBYTES, uwrd_ti, gstate_adr_apti);

 /* for gate eval new a/b form so can use expr eval boolean operations */
 
 mask = __masktab[gwid - 1];
 cint_ti = __gen_cint_tn(mask);
 /* AIV 11/29/07 - width is really gwid - 1 not WBIS */
 gv_apti = __emit_srep_mask_and(SR_VEC, gwid - 1, uwrd_ti, cint_ti);
 // gv_bpti = (uwrd >> gwid) & mask;
 cint_ti = __gen_cint_tn(gwid);
 t1_ti = __emit_shiftr(WBITS, cint_ti, uwrd_ti);
 cint_ti = __gen_cint_tn(mask);
 t2_ti = __emit_bin_bitand(WBITS, t1_ti, cint_ti);
 gv_bpti = __get_bpti(gv_apti);
 __emit_copy(wlen_(gwid - 1)*WRDBYTES, t2_ti, gv_bpti);


 xp = gp->gpins[0];
 if (__is_expr_2state(xp)) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;

 /* evaluate gate by using unary reducing logic gen routines */
 scal_ngval_ti = -1;
 switch ((byte) gp->gmsym->el.eprimp->gateid) {
  case G_BITREDAND:
   scal_ngval_ti = __gen_un_bitred_and(gv_apti, gwid - 1, FALSE, TRUE);
   break;
  case G_NAND:
   /* logic gate nand is not of bit red and, but no expression unary op */
   scal_ngval_ti = __gen_un_bitred_and(gv_apti, gwid - 1, TRUE, TRUE);
   break;
  case G_BITREDOR:
   scal_ngval_ti = __gen_un_bitred_or(gv_apti, FALSE, TRUE);
   break;
  case G_NOR:
   /* logic gate nor is not of bit red or, but no expression unary op */
   scal_ngval_ti = __gen_un_bitred_or(gv_apti, TRUE, TRUE);
   break;
  case G_BITREDXOR:
   scal_ngval_ti = __gen_un_bitred_xnor_nor(gv_apti, FALSE, srtyp);
   break;
  case G_REDXNOR:
   scal_ngval_ti = __gen_un_bitred_xnor_nor(gv_apti, TRUE, srtyp);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }

 // __old_gateval = __idp[gp->gate_out_ofs]
 ogval_ti = __gen_gate_output_value(gp, (srtyp == SR_SCAL2S));
 /* handle delay case using normal gate chg */
 /* thrd param T because being called from acc routine */
 if (gp->g_delrep != DT_NONE)
  {
   gen_prop_gatechg(gp, scal_ngval_ti, ogval_ti, done_bbp, -1);
   return;
  }

 /* gen vinsns to assign to the output terminal */ 
 xp = gp->gpins[0];

 gate_chg_bbp = __alloc_bblk(FALSE);
 /* __old_gateval != __new_gateval */
 __emit_jmp_eq(done_bbp, gate_chg_bbp, scal_ngval_ti, ogval_ti);
 __start_bblk(gate_chg_bbp);
 
 /* AIV 11/06/07 - was still storing the output value as back value */
 /* store new gate value into __idp[gp->gate_out_ofs] */
 __emit_copy(WRDBYTES, scal_ngval_ti, ogval_ti);

 if (xp->x_multfi) 
  {
   gen_mdr_assgn_or_schd_insns(xp);
  }
 else if (xp->x_stren) 
  {
   gen_gate_stren_added_assign(gp, xp, scal_ngval_ti, TRUE);
  }
 else
  {
   if (xp->lhsx_ndel) gen_sched_conta_assign(xp, scal_ngval_ti);
   else gen_conta_assgn(xp, scal_ngval_ti);
  }
}

/*
 * process gates with one input G_ASSIGN, G_BUF, G_NOT
 */
static void gen_chg_logic_gate_1term(struct net_pin_t *npp, 
 struct bblk_t *done_bbp) 
{
 int32 inval_ti, scal_inval_ti, ogval_ti, r1_ti, scal_ngval_ti;
 int32 amtyp, srtyp;
 struct gate_t *gp;
 struct expr_t *xp;
 struct bblk_t *gate_chg_bbp;
 
 scal_ngval_ti = -1;
 gp = npp->elnpp.egp;
 xp = gp->gpins[npp->obnum];
 inval_ti = __gen_expr_eval(xp, -1);
 /* if 2-state get load as SR_SCAL2S */
 xp = gp->gpins[0];
 if (__is_expr_2state(xp)) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;

 scal_inval_ti = __gen_cnvt_srep_ifneeded(inval_ti, srtyp, 1, FALSE,
     FALSE, TRUE);
 
 if (__tntab[scal_inval_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
 else amtyp = AM_REG;

 switch ((byte) gp->gmsym->el.eprimp->gateid) {
  case G_BUF:
   r1_ti = __move_insn(TN_VAL, I_MOVA, amtyp, scal_inval_ti);
   scal_ngval_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1,
    AM_NLO_ARRNDX, r1_ti, NLO_GBUFVAL);
   break;
  case G_ASSIGN:
   /* AIV 12/27/07 - need move here in because if is xmr will not use */
   /* off of fixed idp [ofs(%esi)] - will coal away if not idp ofs */
   scal_ngval_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1, 
     amtyp, scal_inval_ti);
   break;
  case G_NOT:
   r1_ti = __move_insn(TN_VAL, I_MOVA, amtyp, scal_inval_ti);
   scal_ngval_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1,
    AM_NLO_ARRNDX, r1_ti, NLO_GNOTVAL);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }

 ogval_ti = __gen_gate_output_value(gp, (srtyp == SR_SCAL2S));
 
 if (gp->g_delrep != DT_NONE)
  {
   gen_prop_gatechg(gp, scal_ngval_ti, ogval_ti, done_bbp, -1);
   return;
  }

 xp = gp->gpins[0];
 /* if not mfi or have delay just do the simple assign regardless if changed */
 /* or not - if net needs change record will compare later */
 if (xp->x_multfi || xp->lhsx_ndel) 
  {
   gate_chg_bbp = __alloc_bblk(FALSE);
   /* __old_gateval != __new_gateval */
   __emit_jmp_eq(done_bbp, gate_chg_bbp, scal_ngval_ti, ogval_ti);
   __start_bblk(gate_chg_bbp);
   __emit_copy(WRDBYTES, scal_ngval_ti, ogval_ti);
  }
 /* AIV 11/23/09 - need to keep track of sys func wrappers which need to */
 /* have gp->gate_out_ofs set - for compiled code - no need to */
 /* store this value if not comparing against */
 else if (__cvc_nd_old_gate_store || __design_has_ld_pli_libs)
  {
   __emit_copy(WRDBYTES, scal_ngval_ti, ogval_ti);
  }

 if (xp->x_multfi) 
  {
   gen_mdr_assgn_or_schd_insns(xp);
  }
 else if (xp->x_stren) 
  {
   gen_gate_stren_added_assign(gp, xp, scal_ngval_ti, TRUE);
  }
 else
  {
   if (xp->lhsx_ndel) gen_sched_conta_assign(xp, scal_ngval_ti);
   else gen_conta_assgn(xp, scal_ngval_ti);
  }
}

/*
 * calculate a narrow gwid < 6 value for a logic gate by getting the 
 * new value for uwrd which is used as an index into the precomputed
 * gate tables
 */
static void gen_chg_logic_gate_narrow(struct net_pin_t *npp, 
 struct bblk_t *done_bbp) 
{
 int32 gwid, bi, cint_ti, nlo_tab, or_nlo_type, srtyp;
 int32 inval_ti, scal_inval_ti, uwrd1_ti, uwrd_ti, amtyp;
 int32 gstate_adr_apti;
 int32 t1_ti, t2_ti;
 int32 scal_ngval_ti, ogval_ti;
 word32 mask;
 /* gwid can never be less than two */
 int32 nlo_or_mask[5][4] = {
  {-1, -1, -1, -1},
  {-1, -1, -1, -1},
  {NLO_ORM_2_0, NLO_ORM_2_1, NLO_ORM_2_2, NLO_ORM_2_3},
  {NLO_ORM_3_0, NLO_ORM_3_1, NLO_ORM_3_2, NLO_ORM_3_3},
  {NLO_ORM_4_0, NLO_ORM_4_1, NLO_ORM_4_2, NLO_ORM_4_3}};
 struct gate_t *gp;
 struct expr_t *xp;
 struct bblk_t *gate_chg_bbp;
 
 /* gpnum is number of terminals - logic gates always num ins plus 1 out */
 /* bi is input number - 0th is output so npp obnum one too high */
 gp = npp->elnpp.egp;
 /* gpnum is number of terminals - logic gates always num ins plus 1 out */
 gwid = gp->gpnum;
 /* DBG remove -- */
 if (gwid > 4 || gwid < 2) __misc_terr(__FILE__, __LINE__);
 /* ----- */
 /* bi is input number - 0th is output so npp obnum one too high */
 bi = npp->obnum - 1; 
 xp = gp->gpins[npp->obnum];

 /* need both the scalar and the a/b input terminal connected value */
 inval_ti = __gen_expr_eval(xp, -1);

 /* if 2-state get load as SR_SCAL2S */
 xp = gp->gpins[0];
 if (__is_expr_2state(xp)) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;

 /* mask value index by scalar so compute to scalar */
 scal_inval_ti = __gen_cnvt_srep_ifneeded(inval_ti, srtyp, 1, FALSE,
     FALSE, TRUE);
 if (__tntab[scal_inval_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
 else amtyp = AM_REG;
 t1_ti = __move_insn(TN_VAL, I_MOVA, amtyp, scal_inval_ti);
 or_nlo_type = nlo_or_mask[gwid][bi];
 /* table which precomputes ((gav << bi) | (gbv << (gwid + bi))) */
 /* index by scalar value 0-3 */
 t2_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, t1_ti, or_nlo_type);

 gstate_adr_apti = __gen_gatebp_tn(gp, WBITS); 
 // uwrd = ouwrd & ~(1L << bi) & ~(1L << (gwid + bi));
 mask = ~(1UL << bi) & ~(1UL << (gwid + bi));
 cint_ti = __gen_cint_tn(mask);
 uwrd1_ti = __emit_bin_bitand(WBITS, cint_ti, gstate_adr_apti);
 uwrd_ti = __emit_bin_bitor(WBITS, uwrd1_ti, t2_ti);

/* AIV better just do it???????
 state_chg_bbp = __alloc_bblk(FALSE);
 __emit_jmp_eq(done_bbp, state_chg_bbp, uwrd_ti, gstate_adr_apti);

 __start_bblk(state_chg_bbp);
*/

 /* store uwrd (new state) into state value */
 // __idp[gp->gstate_ofs] = uwrd;
 __emit_copy(WRDBYTES, uwrd_ti, gstate_adr_apti);

 /* evaluate gate by using unary reducing logic gen routines */
 nlo_tab = -1;
 switch ((byte) gp->gmsym->el.eprimp->gateid) {
  case G_BITREDAND:
   nlo_tab = NLO_GBITREDAND;
   break;
  case G_NAND:
   nlo_tab = NLO_GNAND;
   break;
  case G_BITREDOR:
   nlo_tab = NLO_GBITREDOR;
   break;
  case G_NOR:
   nlo_tab = NLO_GNOR;
   break;
  case G_BITREDXOR:
   nlo_tab = NLO_GBITREDXOR;
   break;
  case G_REDXNOR:
   nlo_tab = NLO_GREDXNOR;
   break;
  default: __case_terr(__FILE__, __LINE__);
 }

 scal_ngval_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1, 
     AM_NLO_ARRNDX, uwrd_ti, nlo_tab);
 /* handle delay case using normal gate chg */
 /* thrd param T because being called from acc routine */
 /* for gate eval new a/b form so can use expr eval boolean operations */
 // __old_gateval = __idp[gp->gate_out_ofs]
 ogval_ti = __gen_gate_output_value(gp, (srtyp == SR_SCAL2S));

 if (gp->g_delrep != DT_NONE)
  {
   gen_prop_gatechg(gp, scal_ngval_ti, ogval_ti, done_bbp, -1);
   return;
  }
 
 /* if not mfi or have delay just do the simple assign regardless if changed */
 /* or not - if net needs change record will compare later */
 if (xp->x_multfi || xp->lhsx_ndel) 
  {
   gate_chg_bbp = __alloc_bblk(FALSE);
   /* __old_gateval != __new_gateval */
   __emit_jmp_eq(done_bbp, gate_chg_bbp, scal_ngval_ti, ogval_ti);
   __start_bblk(gate_chg_bbp);
   /* gen vinsns to assign to the output terminal */ 
   /* AIV 11/06/07 - was still storing the output value as back value */
   /* store new gate value into __idp[gp->gate_out_ofs] */
   /* AIV 09/17/08 - only need store for old value this case */
   __emit_copy(WRDBYTES, scal_ngval_ti, ogval_ti);
  }
 /* AIV 11/23/09 - need to keep track of sys func wrappers which need to */
 /* have gp->gate_out_ofs set - for compiled code - no need to */
 /* store this value if not comparing against */
 else if (__cvc_nd_old_gate_store || __design_has_ld_pli_libs)
  {
   __emit_copy(WRDBYTES, scal_ngval_ti, ogval_ti);
  }
 

 xp = gp->gpins[0];
 if (xp->x_multfi)
  {
   gen_mdr_assgn_or_schd_insns(xp);
  }
 else if (xp->x_stren) 
  {
   gen_gate_stren_added_assign(gp, xp, scal_ngval_ti, TRUE);
  }
 else if (xp->lhsx_ndel) 
  {
   gen_sched_conta_assign(xp, scal_ngval_ti);
  }
 else 
  {
   gen_conta_assgn(xp, scal_ngval_ti);
  }
}

/*
 * AIV 03/09/09 - this routine just evaluates and doesn't save state
 * if is fast to evaluate with tables if all inputs are leaf exprs
 * 
 * just or in the values and shift over two for 4 - state value 
 * to create index into the correct table
 */
static void gen_chg_logic_gate_narrow_leaves(struct net_pin_t *npp, 
 struct bblk_t *done_bbp) 
{
 int32 t1_ti, cint_ti, ndx_ti, op_type, srtyp;
 int32 inval_ti, inval2_ti;
 int32 scal_ngval_ti, ogval_ti, gwid, shftamt, i;
 struct gate_t *gp;
 struct expr_t *xp, *xp2;
 struct bblk_t *gate_chg_bbp;
 
 /* gpnum is number of terminals - logic gates always num ins plus 1 out */
 /* bi is input number - 0th is output so npp obnum one too high */
 gp = npp->elnpp.egp;
 gwid = gp->gpnum;
 /* DBG remove -- */ 
 if (gwid >= 6) __misc_terr(__FILE__, __LINE__);
 /* ---- */ 

 /* 0th is the output so start at 1 */
 xp2 = gp->gpins[2];
 inval2_ti = __gen_expr_eval(xp2, -1);
 inval2_ti = __gen_scalar_operand(__tntab[inval2_ti].srtyp, inval2_ti);
 
 /* do the first two inputs */
 /* get the index op1 | (op2 << 2) */
 cint_ti = __gen_cint_tn(2);
 t1_ti = __emit_shiftl(WBITS, cint_ti, inval2_ti);

 xp = gp->gpins[1];
 inval_ti = __gen_expr_eval(xp, -1);
 inval_ti = __gen_scalar_operand(__tntab[inval_ti].srtyp, inval_ti);

 ndx_ti = __emit_bin_bitor(WBITS, inval_ti, t1_ti);
 shftamt = 4;

 /* or in the remaining inputs to create index */
 for (i = 3; i < gwid; i++)
  {
   xp = gp->gpins[i];
   inval_ti = __gen_expr_eval(xp, -1);
   inval_ti = __gen_scalar_operand(__tntab[inval_ti].srtyp, inval_ti);

   /* get the index ndx_ti | (op << shftamt) */
   cint_ti = __gen_cint_tn(shftamt);
   t1_ti = __emit_shiftl(WBITS, cint_ti, inval_ti);
   ndx_ti = __emit_bin_bitor(WBITS, ndx_ti, t1_ti);
   shftamt += 2;
  }

 /* get the correct table value */
 op_type = -1;
 if (gwid == 3)
  {
   /* AIV 03/09/09 - combined these values into common shared arrays */
   switch ((byte) gp->gmsym->el.eprimp->gateid) {
    case G_BITREDAND: op_type = NLO_SBO_BITREDAND; break;
    case G_NAND: op_type = NLO_SBO_NAND; break;
    case G_BITREDOR: op_type = NLO_SBO_P4; break;
    case G_NOR: op_type = NLO_SBO_NOR; break;
    case G_BITREDXOR: op_type = NLO_SBO_P1; break;
    case G_REDXNOR: op_type = NLO_SBO_P3; break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 else if (gwid == 4)
  {
   switch ((byte) gp->gmsym->el.eprimp->gateid) { 
    case G_BITREDAND: op_type = NLO_G3_BITREDAND; break;
    case G_NAND: op_type = NLO_G3_NAND; break;
    case G_BITREDOR: op_type = NLO_G3_BITREDOR; break;
    case G_NOR: op_type = NLO_G3_NOR; break;
    case G_BITREDXOR: op_type = NLO_G3_BITREDXOR; break;
    case G_REDXNOR: op_type = NLO_G3_REDXNOR; break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 else if (gwid == 5)
  {
   switch ((byte) gp->gmsym->el.eprimp->gateid) {
    case G_BITREDAND: op_type = NLO_G4_BITREDAND; break;
    case G_NAND: op_type = NLO_G4_NAND; break;
    case G_BITREDOR: op_type = NLO_G4_BITREDOR; break;
    case G_NOR: op_type = NLO_G4_NOR; break;
    case G_BITREDXOR: op_type = NLO_G4_BITREDXOR; break;
    case G_REDXNOR: op_type = NLO_G4_REDXNOR; break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 else __case_terr(__FILE__, __LINE__);
 
 /* ndx_ti must be in a reg if folded and still address must move to reg */
 if (__tntab[ndx_ti].tn_typ == TN_ADR)
  {
   ndx_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, ndx_ti);
  }

 /* if 2-state get load as SR_SCAL2S */
 xp = gp->gpins[0];
 if (__is_expr_2state(xp)) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;
  
 /* load the value from the table */
 scal_ngval_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1, 
      AM_NLO_ARRNDX, ndx_ti, op_type);

 /* normal gate propagation */
 /* handle delay case using normal gate chg */
 /* thrd param T because being called from acc routine */
 /* for gate eval new a/b form so can use expr eval boolean operations */
 // __old_gateval = __idp[gp->gate_out_ofs]
 ogval_ti = __gen_gate_output_value(gp, (srtyp == SR_SCAL2S));

 if (gp->g_delrep != DT_NONE)
  {
   gen_prop_gatechg(gp, scal_ngval_ti, ogval_ti, done_bbp, -1);
   return;
  }
 
 /* if not mfi or have delay just do the simple assign regardless if changed */
 /* or not - if net needs change record will compare later */
 /* AIV 11/23/09 - this was wrong should be xp needs to go here */
 if (xp->x_multfi || xp->lhsx_ndel) 
  {
   gate_chg_bbp = __alloc_bblk(FALSE);
   /* __old_gateval != __new_gateval */
   __emit_jmp_eq(done_bbp, gate_chg_bbp, scal_ngval_ti, ogval_ti);
   __start_bblk(gate_chg_bbp);
   /* gen vinsns to assign to the output terminal */ 
   /* AIV 11/06/07 - was still storing the output value as back value */
   /* store new gate value into __idp[gp->gate_out_ofs] */
   /* AIV 09/17/08 - only need store for old value this case */
   __emit_copy(WRDBYTES, scal_ngval_ti, ogval_ti);
  }
 /* AIV 11/23/09 - need to keep track of sys func wrappers which need to */
 /* have gp->gate_out_ofs set - for compiled code - no need to */
 /* store this value if not comparing against */
 else if (__cvc_nd_old_gate_store || __design_has_ld_pli_libs)
  {
   __emit_copy(WRDBYTES, scal_ngval_ti, ogval_ti);
  }
 

 if (xp->x_multfi)
  {
   gen_mdr_assgn_or_schd_insns(xp);
  }
 else if (xp->x_stren) 
  {
   gen_gate_stren_added_assign(gp, xp, scal_ngval_ti, TRUE);
  }
 else if (xp->lhsx_ndel) 
  {
   gen_sched_conta_assign(xp, scal_ngval_ti);
  }
 else 
  {
   gen_conta_assgn(xp, scal_ngval_ti);
  }
}
   

/*
 * gen insn to propagate (schedule) gate that has delay 
 *
 * notice this works for all gates since scheduler back side event
 * processor still uses interpreter code that detemines gate type 
 *
 * AIV 03/09/09 - added a few changes and added a constant wrapper handle
 * for the constant delay case
 */
static void gen_prop_gatechg(struct gate_t *gp, int32 new_gateval_ti,
 int32 old_gateval_ti, struct bblk_t *done_bbp, int32 eq_cmp_ti)
{
 int32 gp_ti, chg_outwir_ti, gp_enter_ti, outv_ti;
 int32 tevp_trigger_ti, tevp_ti, eq_ti, is_const, tevp_reg_ti;
 size_t offset, out_offset;
 word64 gdel;
 struct bblk_t *pend_chg_bbp, *chg_outwir_bbp, *chg2_outwir_bbp;
 struct bblk_t *outchg_bbp, *noschd_bbp, *pend_schd_bbp;
 struct bblk_t *pend_nochg_bbp, *tevi_neg1_bbp, *reschedule_bbp;
 struct ctev_t *ctevp;
 struct tev_t *tevp;

 outchg_bbp = __alloc_bblk(FALSE);
   
 ctevp = gp->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 

 gp_ti = -1;
 /* AIV 11/07/05 - must set __new_gateval when delay on udp */
 /* AIV 10/23/07 - cmos passes __new_gateval no need to set to itself */
 /* AIV FIXME - can remove this when cmos/mos lowered */
 /* AIV 01/07/08 - the only time the globals need to be set are for */
 /* delays which need set or for glith warn messages */
 is_const = __check_delay_constant(gp->g_du, gp->g_delrep, &(gdel));
 /* AIV 02/25/09 - these are only loaded for non-const delay */
 /* strength or special inform options */
 if (!is_const || __show_cancel_e || __warn_cancel_e || gp->g_hasst)
  {
   if (new_gateval_ti != __nlo_tn_used[NLO_NEWGVAL])
    {
     __emit_set_new_gateval(new_gateval_ti);
    }
   if (old_gateval_ti != __nlo_tn_used[NLO_OLDGVAL])
    {
     __emit_set_old_gateval(old_gateval_ti);
    }
   gp_ti = __gen_gate_adr_tn(gp);
  }
 noschd_bbp = __alloc_bblk(FALSE);
 pend_schd_bbp = __alloc_bblk(FALSE);

 /* AIV 10/24/07 - cmos already does the compare due to wrapper just need */
 /* to pass down the compared value returned from wrapper */
 if (eq_cmp_ti == -1)
  {
   eq_ti = __emit_bin_bitxor(WBITS, new_gateval_ti, old_gateval_ti);
  }
 else eq_ti = eq_cmp_ti;

 tevp_ti = __gen_ctevp_adr_tn(ctevp);
 tevp = __free_event_tevp;
 tevp_reg_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, tevp_ti);
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 out_offset = (byte *) &(tevp->outv) - (byte *) tevp;
 tevp_trigger_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, tevp_reg_ti, 
    offset);
 __emit_jmp_0(noschd_bbp, pend_schd_bbp, tevp_trigger_ti);

 __start_bblk(noschd_bbp);

 /* AIV 06/16/06 - was incorrectly comparing word here need to compare byte */
 __emit_jmp_0(done_bbp, outchg_bbp, eq_ti); 

 __start_bblk(outchg_bbp);

 /* know RT globals new and old gateval previously set */
 //AIV FIXME - temporary until cmos/udp/mos backend lowered
 if (gp->g_class == GC_LOGIC || gp->g_class == GC_BUFIF 
    || gp->g_class == GC_CMOS || gp->g_class == GC_MOS || gp->g_class == GC_UDP)
  {
   gp_enter_ti = __gen_gate_enter_adr_tn(gp);
  }
 else
  {
   if (gp->g_pdst) 
    {
     gp_enter_ti = __gen_gate_acc_change_enter_adr_tn(gp);
    }
   else  gp_enter_ti = __gen_gate_change_enter_adr_tn(gp);
  }

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[gp_enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[gp_enter_ti].comlab_typ;

 if (gp->g_hasst)
  {
   __emit_stren_schd_1gev(gp_ti, tevp_reg_ti);
  }
 else
  {
   __st_insn(I_STOREB, AM_REG, new_gateval_ti, AM_NDXREG_DISP, tevp_reg_ti,
    out_offset);
   if (is_const)
    {
     if (gdel == 0) __emit_schd_1gev_pnd0(tevp_reg_ti);
     else __emit_schd_1gev_const(tevp_reg_ti);
    }
   else __emit_schd_1gev(gp_ti, tevp_reg_ti);
  }

 __emit_jmp(done_bbp);

 __start_bblk(pend_schd_bbp);

 pend_nochg_bbp = __alloc_bblk(FALSE);
 pend_chg_bbp = __alloc_bblk(FALSE);
 /* AIV 06/16/06 - was incorrectly comparing word here need to compare byte */
 __emit_jmp_0(pend_nochg_bbp, pend_chg_bbp, eq_ti); 
  
 __start_bblk(pend_nochg_bbp);
 if (__show_cancel_e || __warn_cancel_e)
  {
   /* case 1a: cancele nochg */
   /* if need to store gate out val, return T (1) */
   chg_outwir_bbp = __alloc_bblk(FALSE);
   chg2_outwir_bbp = __alloc_bblk(FALSE);
   tevi_neg1_bbp = __alloc_bblk(FALSE);

   chg_outwir_ti = __emit_cancele_pend_nochg_1gev(gp_ti, tevp_reg_ti);
   __emit_jmp_0(tevi_neg1_bbp, chg_outwir_bbp, chg_outwir_ti);

   __start_bblk(tevi_neg1_bbp);
   __emit_jmp(done_bbp);

   __start_bblk(chg_outwir_bbp);
//SJM? - lower this
   __emit_chg_gate_outwire(tevp_reg_ti);
   __emit_jmp(done_bbp);

   /* case 1b: cancele chg */
   __start_bblk(pend_chg_bbp);
   chg_outwir_ti = __emit_cancele_pend_chg_1gev(gp_ti, tevp_reg_ti);

   __emit_jmp_0(chg2_outwir_bbp, done_bbp, chg_outwir_ti);
//SJM? - lower this
   __start_bblk(chg2_outwir_bbp);
   __emit_chg_gate_outwire(tevp_reg_ti);
   __emit_jmp(done_bbp);
  }
 else
  {
   /* case 2a: no cancele nochg */
   
   /* AIV 10/22/07 - this wrapper is actually just a cancel always NULL */
   /* strength and non-stren do the same thing */
   __emit_pend_nochg_1gev(tevp_reg_ti);
   __emit_jmp(done_bbp);

   /* case 1b: non cancele chg */
   __start_bblk(pend_chg_bbp);
   if (gp->g_hasst)
    {
     __emit_stren_pend_chg_1gev(gp_ti, tevp_reg_ti);
    }
   else
    {
     /* if pnd0 this doesn't do anything */
     if (is_const && gdel == 0) return;
     /* if (tevp->outv == (byte) __new_gateval) return; */
     reschedule_bbp = __alloc_bblk(FALSE);
     outv_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG_DISP, tevp_reg_ti, 
       out_offset);
      __emit_jmp_eq(done_bbp, reschedule_bbp, outv_ti, new_gateval_ti); 
      __start_bblk(reschedule_bbp);
     __st_insn(I_STOREB, AM_REG, new_gateval_ti, AM_NDXREG_DISP, tevp_reg_ti,
      out_offset);

     if (is_const) __emit_pend_chg_1gev_const(tevp_reg_ti);
     else __emit_pend_chg_1gev(gp_ti, tevp_reg_ti);
    }
  }
}

/*
 * gen vinsns to eval bufif gate (fixed 2 inputs and 1 output)
 */
static void gen_np_chg_bufif_gate(struct net_pin_t *npp, 
 struct bblk_t *done_bbp) 
{
 int32 inval_apti, scal_inval_ti, scal_wrd_ti, cint_ti;
 int32 gstate_ti, t1_ti, t2_ti, gwrd_ti, base;
 int32 new_gateval_ti, gout_val_ti;
 int32 ndx_ti, nlo_type, ndx, ndx2;
 word32 mask;
 struct gate_t *gp;
 struct expr_t *xp;
 struct bblk_t *nodel_outchg_bbp;
 int32 nlo_bufif_tables[4][7] = {
  {NLO_BF0_STRVAL, NLO_BF0_STRONGX, NLO_BF0_HIZ, NLO_BF0_PULL0, NLO_BF0_PULL1,
   NLO_BF0_SUPPLY0, NLO_BF0_SUPPLY1},
  {NLO_BF1_STRVAL, NLO_BF1_STRONGX, NLO_BF1_HIZ, NLO_BF1_PULL0, NLO_BF1_PULL1,
   NLO_BF1_SUPPLY0, NLO_BF1_SUPPLY1},
  {NLO_NF0_STRVAL, NLO_NF0_STRONGX, NLO_NF0_HIZ, NLO_NF0_PULL0, NLO_NF0_PULL1,
   NLO_NF0_SUPPLY0, NLO_NF0_SUPPLY1},
  {NLO_NF1_STRVAL, NLO_NF1_STRONGX, NLO_NF1_HIZ, NLO_NF1_PULL0, NLO_NF1_PULL1,
   NLO_NF1_SUPPLY0, NLO_NF1_SUPPLY1}};

 ndx = ndx2 = -1;
 gp = npp->elnpp.egp;
 switch ((byte) gp->g_stval) {
  case ST_STRVAL: ndx2 = 0; break;
  case ST_STRONGX: ndx2 = 1; break;
  case ST_HIZ: ndx2 = 2; break;
  case ST_PULL0: ndx2 = 3; break;
  case ST_PULL1: ndx2 = 4; break;
  case ST_SUPPLY0: ndx2 = 5; break;
  case ST_SUPPLY1: ndx2 = 6; break;
 }
 
//AIV LOOKATME
//there currently are not tables for the bufif stren assigns
//would need tables for all the possible combinations - should
//probably make tables  - using the old code for now
//bufif0 (s1, s2) (out, in1, in2);
 if (ndx2 == -1)
  {
   gen_np_chg_bufif_gate_strdrv(npp, done_bbp);
   return;
  }

 base = __bufif_base_tab[gp->gmsym->el.eprimp->gateid];
 switch ((byte) base) {
  /* bufif0 */
  case 0: ndx = 0; break;
  /* bufif1 */
  case 16: ndx = 1; break;
  /* notif0 */
  case 32: ndx = 2; break;
  /* notif1 */
  case 48: ndx = 3; break;
  default: __case_terr(__FILE__, __LINE__);
 }

 xp = gp->gpins[npp->obnum];
 inval_apti = __gen_expr_eval(xp, -1);
 scal_inval_ti = __gen_cnvt_srep_ifneeded(inval_apti, SR_SCAL, 1, FALSE,
  FALSE, TRUE);

 gstate_ti = __gen_gatebp_tn(gp, 16); 
 /* AIV 10/18/06 - there was a bug with using a scalar in word operations */
 /* say inval_ti was scalar it was leaving scalar and doing word operations */
 /* this is a problem because of the following code */
 /* movl M_scalar, %eax; shll %ebx, %eax;   need to zero the high part */
 /* of the reg the copy of 1 byte will zero with mozbl */
 /* AIV 12/28/07 - better to just mask it */
 cint_ti = __gen_cint_tn(0xff);
 scal_wrd_ti = __emit_bin_bitand(WBITS, cint_ti, scal_inval_ti);

 if (npp->obnum == 1)
  {
   mask = ~(3);
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, gstate_ti, cint_ti);
   gwrd_ti = __emit_bin_bitor(WBITS, t1_ti, scal_wrd_ti);
  }
 else if (npp->obnum == 2)
  {
   mask = ~(3 << 2);
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, gstate_ti, cint_ti);
   cint_ti = __gen_cint_tn(2);
   t2_ti = __emit_shiftl(12, cint_ti, scal_wrd_ti);
   gwrd_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
  }
 else { gwrd_ti = -1; __case_terr(__FILE__, __LINE__); }

 __emit_copy(WRDBYTES, gwrd_ti, gstate_ti);


 cint_ti = __gen_cint_tn(0xf);
 ndx_ti = __emit_bin_bitand(WBITS, gwrd_ti, cint_ti);
 nlo_type = nlo_bufif_tables[ndx][ndx2];
 new_gateval_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SSCAL, 1,
    AM_NLO_ARRNDX, ndx_ti, nlo_type);

 gout_val_ti = __gen_gate_output_value(gp, FALSE);

 if (gp->g_delrep != DT_NONE)
  {
   /* SJM 01/26/06 - this handles its own do nothing skipping inside */ 
   gen_prop_gatechg(gp, new_gateval_ti, gout_val_ti, done_bbp, -1);
   return;
  }

 xp = gp->gpins[0];
 /* if not mfi or have delay just do the simple assign regardless if changed */
 /* or not - if net needs change record will compare later */
 if (xp->x_multfi || xp->lhsx_ndel) 
  {
   nodel_outchg_bbp = __alloc_bblk(FALSE); 
   /* no delay case - if state unchged, nothing to do */
   __emit_jmp_eq(done_bbp, nodel_outchg_bbp, new_gateval_ti, gout_val_ti);

   __start_bblk(nodel_outchg_bbp);

   /* bufif changed and no delay - update state and assign to out term */
   __emit_copy(WRDBYTES, new_gateval_ti, gout_val_ti);
  }
 else
  {
   /* bufif changed and no delay - update state and assign to out term */
   __emit_copy(WRDBYTES, new_gateval_ti, gout_val_ti);
  }

 /* gen vinsns to assign to the output terminal */ 
 if (xp->x_multfi) gen_mdr_assgn_or_schd_insns(xp);
 else gen_gate_stren_assign(xp, new_gateval_ti);
}

/*
 * AIV REMOVEME???? make all strength combination tables????????
 */
static void gen_np_chg_bufif_gate_strdrv(struct net_pin_t *npp, 
 struct bblk_t *done_bbp) 
{
 int32 inval_apti, old_inval_ti, scal_inval_ti, scal_wrd_ti, cint_ti;
 int32 gstate_ti, t1_ti, t2_ti, gwrd_ti, base_ti, base;
 int32 new_gateval_ti, gout_val_ti;
 word32 mask;
 struct gate_t *gp;
 struct expr_t *xp;
 struct bblk_t *update_state_bbp, *nodel_outchg_bbp;

 update_state_bbp = __alloc_bblk(FALSE); 
 
 gp = npp->elnpp.egp;
 xp = gp->gpins[npp->obnum];

 inval_apti = __gen_expr_eval(xp, -1);
 scal_inval_ti = __gen_cnvt_srep_ifneeded(inval_apti, SR_SCAL, 1, FALSE,
  FALSE, TRUE);

 gstate_ti = __gen_gatebp_tn(gp, 16); 

 if (npp->obnum == 2)
  {
   cint_ti = __gen_cint_tn(2);
   t1_ti = __emit_shiftr(12, cint_ti, gstate_ti); 
  }
 else if (npp->obnum == 1) t1_ti = gstate_ti;
 else { t1_ti = -1; __case_terr(__FILE__, __LINE__); }

 cint_ti = __gen_cint_tn(3);
 old_inval_ti = __emit_bin_bitand(WBITS, t1_ti, cint_ti);

 __emit_jmp_eq(done_bbp, update_state_bbp, scal_inval_ti, old_inval_ti);

 __start_bblk(update_state_bbp);

 /* AIV 10/18/06 - there was a bug with using a scalar in word operations */
 /* say inval_ti was scalar it was leaving scalar and doing word operations */
 /* this is a problem because of the following code */
 /* movl M_scalar, %eax; shll %ebx, %eax;   need to zero the high part */
 /* of the reg the copy of 1 byte will zero with mozbl */
 /* AIV 12/28/07 - better to just mask it */
 cint_ti = __gen_cint_tn(0xff);
 scal_wrd_ti = __emit_bin_bitand(WBITS, cint_ti, scal_inval_ti);

 if (npp->obnum == 1)
  {
   mask = ~(3);
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, gstate_ti, cint_ti);
   gwrd_ti = __emit_bin_bitor(WBITS, t1_ti, scal_wrd_ti);
  }
 else if (npp->obnum == 2)
  {
   mask = ~(3 << 2);
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, gstate_ti, cint_ti);
   cint_ti = __gen_cint_tn(2);
   t2_ti = __emit_shiftl(12, cint_ti, scal_wrd_ti);
   gwrd_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
  }
 else { gwrd_ti = -1; __case_terr(__FILE__, __LINE__); }

 __emit_copy(WRDBYTES, gwrd_ti, gstate_ti);

 /* this does the table look up using bufif stren driving value */
 /* and 4 bit current input value as index - sets new gateval global*/
 cint_ti = __gen_cint_tn(((word32) gp->g_stval) << 2);
 base = __bufif_base_tab[gp->gmsym->el.eprimp->gateid];
 base_ti = __gen_cint_tn(base);
 new_gateval_ti = __emit_calc_bufif_newstate(gwrd_ti, base_ti, cint_ti);

 gout_val_ti = __gen_gate_output_value(gp, FALSE);

 if (gp->g_delrep != DT_NONE)
  {
   /* SJM 01/26/06 - this handles its own do nothing skipping inside */ 
   gen_prop_gatechg(gp, new_gateval_ti, gout_val_ti, done_bbp, -1);
   return;
  }

 /* if not mfi or have delay just do the simple assign regardless if changed */
 /* or not - if net needs change record will compare later */
 if (xp->x_multfi || xp->lhsx_ndel) 
  {
   nodel_outchg_bbp = __alloc_bblk(FALSE); 
   /* no delay case - if state unchged, nothing to do */
   __emit_jmp_eq(done_bbp, nodel_outchg_bbp, new_gateval_ti, gout_val_ti);

   __start_bblk(nodel_outchg_bbp);

   __emit_copy(WRDBYTES, new_gateval_ti, gout_val_ti);
  }
 else 
  {
   __emit_copy(WRDBYTES, new_gateval_ti, gout_val_ti);
  }

 /* gen vinsns to assign to the output terminal */ 
 xp = gp->gpins[0];
 if (xp->x_multfi) gen_mdr_assgn_or_schd_insns(xp);
 else gen_gate_stren_assign(xp, new_gateval_ti);
}

/*
 * gen vinsns to eval mos gate after input change and propagate/assgn chg 
 */
static void gen_np_chg_udp_gate(struct net_pin_t *npp, struct bblk_t *done_bbp)
{
 int32 pi, is_edge, cint_ti, gout_val_ti, three_ti;
 int32 inval_apti, uwrd_ti, tab_ndx_ti, edgetab_ti;
 int32 gstate_apti, udptab_l_ti, udptab_e_ti, add_ti;
 int32 scal_inval_ti, t1_ti, t2_ti, w_ndx_ti, wrd_ti, t3_ti;
 int32 old_inval_ti, ndxvec_state_apti, ndx_polynomial_ti;
 int32 wi_ti, bi_ti, ndx_ti, new_gateval_ti, new_gateval2_ti, wi_shift_ti;
 int32 bi_shift_ti;
 word32 mask;
 struct gate_t *gp;
 struct expr_t *xp;
 struct udp_t *udpp;
 struct bblk_t *update_state_bbp, *nodel_outchg_bbp;
 struct bblk_t *newgat_x_bbp, *newgat_nonx_bbp;
 
 /* init since wide separate sometimes and rest common */ 
 ndx_polynomial_ti = -1;
 ndxvec_state_apti = -1;

 gp = npp->elnpp.egp;
 /* gpnum is number of terminals - logic gates always num ins plus 1 out */
 /* bi is input number - 0th is output so npp obnum one too high */
 xp = gp->gpins[npp->obnum];

 /* need both the scalar and the a/b input terminal connected value */
 inval_apti = __gen_expr_eval(xp, -1);
 
 scal_inval_ti = __gen_cnvt_srep_ifneeded(inval_apti, SR_SCAL, 1, FALSE,
  FALSE, TRUE);
 /* AIV 05/11/08 - should use these simple tables instead of doing compare */
 three_ti = __gen_cint_tn(3);
 scal_inval_ti = __emit_mask_and(three_ti, scal_inval_ti);
 scal_inval_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, 
   AM_NLO_ARRNDX, scal_inval_ti, NLO_UDP_NOZTAB);

 udpp = gp->gmsym->el.eudpp;
 is_edge = (udpp->utyp == U_EDGE);
 pi = npp->obnum - 1;
 update_state_bbp = __alloc_bblk(FALSE);
 if (!udpp->u_wide)
  {
   gstate_apti = __gen_gatebp_tn(gp, 16); 

   /* copy the state value into a tmp - know fits in machine wrd */
   uwrd_ti = __gen_tn(SR_VEC, WBITS);
   __emit_copy(2, gstate_apti, uwrd_ti);

   cint_ti = __gen_cint_tn(2*pi);
   t1_ti = __emit_shiftr(WBITS, cint_ti, uwrd_ti);
   old_inval_ti = __emit_bin_bitand(WBITS, t1_ti, three_ti);

   __emit_jmp_eq(done_bbp, update_state_bbp, scal_inval_ti, old_inval_ti);

   __start_bblk(update_state_bbp);
   
   mask = ~(3UL << (2*pi));
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, uwrd_ti, cint_ti);
   cint_ti = __gen_cint_tn(2*pi);
   t2_ti = __emit_shiftl(WBITS, cint_ti, scal_inval_ti);
   uwrd_ti = __emit_bin_bitor(2*udpp->numins, t1_ti, t2_ti);
   
   __emit_copy(2, uwrd_ti, gstate_apti);

   mask = __masktab[2*udpp->numstates];
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, uwrd_ti, cint_ti);
   cint_ti = __gen_cint_tn(2);
   ndx_ti = __emit_mult(WBITS, t1_ti, cint_ti);
  }
 else
  {
   /* wide polynomial vector needs 2nd state word */
   gstate_apti = __gen_gatebp_tn(gp, 64); 

   /* copy the state value into a tmp - know fits in machine wrd */
   uwrd_ti = __gen_tn(SR_VEC, WBITS);
   __emit_copy(WRDBYTES, gstate_apti, uwrd_ti);

   /* get get old input val from low state word */
   cint_ti = __gen_cint_tn(2*pi);
   t1_ti = __emit_shiftr(WBITS, cint_ti, uwrd_ti);
   old_inval_ti = __emit_bin_bitand(WBITS, t1_ti, three_ti);

   __emit_jmp_eq(done_bbp, update_state_bbp, scal_inval_ti, old_inval_ti);

   __start_bblk(update_state_bbp);

   mask = ~(3UL << (2*pi));
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, uwrd_ti, cint_ti);
   cint_ti = __gen_cint_tn(2*pi);
   t2_ti = __emit_shiftl(WBITS, cint_ti, scal_inval_ti);
   uwrd_ti = __emit_bin_bitor(2*udpp->numins, t2_ti, t1_ti);

   /* update just the low state word new input here */
   __emit_copy(WRDBYTES, uwrd_ti, gstate_apti);

   ndxvec_state_apti = __con_adradd_insn(SR_VEC, WBITS, gstate_apti, WRDBYTES);

   /* copy the the current index state polynomial running index into wrd */
   ndx_polynomial_ti = __gen_tn(SR_VEC, WBITS);
   __emit_copy(WRDBYTES, ndxvec_state_apti, ndx_polynomial_ti);

   /* remove old coordinate's (input terminal) contribution */
   /* AIV 05/11/08 - should use these simple tables instead of doing compare */
   //old_inval_ti = __emit_bin_bitand(WBITS, three_ti, old_inval_ti);
   t1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, old_inval_ti, 
     NLO_UDP_UVALTAB);

   cint_ti = __gen_cint_tn(__pow3tab[pi]);
   t2_ti = __emit_mult(WBITS, t1_ti, cint_ti);
   ndx_polynomial_ti = __emit_sub(WBITS, ndx_polynomial_ti, t2_ti);

   /* add in new coodinate's (input terminal) contribution */
   /* AIV 05/11/08 - should use these simple table instead of doing compare */
   /* AIV 06/05/08 - need the mask here - cannot ndx with byte high not zero */
   t3_ti = __emit_bin_bitand(WBITS, three_ti, scal_inval_ti);
   t1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, t3_ti, 
    NLO_UDP_UVALTAB);
   /* AIV 10/16/06 - was missing the multiply */
   t2_ti = __emit_mult(WBITS, t1_ti, cint_ti);
   ndx_polynomial_ti = __emit_add(WBITS, ndx_polynomial_ti, t2_ti);
  
   /* update polynomial vector in geometric space even if no output chg */
   __emit_copy(WRDBYTES, ndx_polynomial_ti, ndxvec_state_apti);

   cint_ti = __gen_cint_tn(2);
   ndx_ti = __emit_mult(WBITS, ndx_polynomial_ti, cint_ti);
  }

 /* set old gateval tmp name and global */

 /* ndx integer already multiplied by 2 for 2 bit table values */
 
 /* ngval = (utab->ludptab[wi] >> bi) & 3; */
#ifdef __CVC32__
 /* this is get wofs */
 wi_shift_ti = __gen_cint_tn(5);
 wi_ti = __emit_shiftr(WBITS, wi_shift_ti, ndx_ti);
 cint_ti = __gen_cint_tn(WRDBYTES);
 w_ndx_ti = __emit_mult(WBITS, cint_ti, wi_ti);

 udptab_l_ti = __gen_l_udp_table(udpp);
 wrd_ti = __var_adradd_insn(SR_VEC, WBITS, udptab_l_ti, w_ndx_ti);
 /* this is get bofs */
 bi_shift_ti = __gen_cint_tn(0x1f);
 bi_ti = __emit_bin_bitand(WBITS, ndx_ti, bi_shift_ti);
 t1_ti = __emit_shiftr(WBITS, bi_ti, wrd_ti);
#else
 /* this is get wofs 64-bit */
 wi_shift_ti = __gen_cint_tn(6);
 wi_ti = __emit_shiftr(WBITS, wi_shift_ti, ndx_ti);
 cint_ti = __gen_cint_tn(WRDBYTES);
 w_ndx_ti = __emit_mult(WBITS, cint_ti, wi_ti);

 udptab_l_ti = __gen_l_udp_table(udpp);
 wrd_ti = __var_adradd_insn(SR_VEC, WBITS, udptab_l_ti, w_ndx_ti);
 /* this is get bofs 64-bit */
 bi_shift_ti = __gen_cint_tn(0x3f);
 bi_ti = __emit_bin_bitand(WBITS, ndx_ti, bi_shift_ti);
 t1_ti = __emit_shiftr(WBITS, bi_ti, wrd_ti);
#endif

 new_gateval_ti = __emit_srep_mask_and(SR_SCAL, 1, three_ti, t1_ti);

 gout_val_ti = __gen_gate_output_value(gp, FALSE);
 if (is_edge)
  {
   newgat_nonx_bbp = __alloc_bblk(FALSE);
   newgat_x_bbp = __alloc_bblk(FALSE);

   /* if edge and new gateval would be x, need 2nd table look up */
   __emit_jmp_eq(newgat_x_bbp, newgat_nonx_bbp, three_ti, new_gateval_ti);
   __start_bblk(newgat_x_bbp);

   /* tabi = 3*pi + ((old_ival == 3) ? 2 : old_ival); */
   t1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, old_inval_ti, 
       NLO_UDP_UVALTAB);

   cint_ti = __gen_cint_tn(3*pi);
   add_ti = __emit_add(WBITS, cint_ti, t1_ti);

   /* wp = udpp->utab->eudptabs[tabi]; */
   cint_ti = __gen_cint_tn(WRDBYTES);
   tab_ndx_ti = __emit_mult(WBITS, cint_ti, add_ti);

   udptab_e_ti = __gen_e_udp_table(udpp);
   edgetab_ti = __var_adradd_insn(SR_VEC, WBITS, udptab_e_ti, tab_ndx_ti);
 
   edgetab_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG, edgetab_ti);

   /* ngval = (wp[wi] >> bi) & 3L; */
   /* if number register are less than 5 - recompute the ndx here */
   /* 32-bit is known to spill because of register pressure this reduces */
   /* enough to never spill */
   if (NUM_ALLOCABLE_REGS <= 5) 
    {
     wi_ti = __emit_shiftr(WBITS, wi_shift_ti, ndx_ti);
    }
   w_ndx_ti = __emit_mult(WBITS, cint_ti, wi_ti);
   wrd_ti = __var_adradd_insn(SR_VEC, WBITS, edgetab_ti, w_ndx_ti);
   if (NUM_ALLOCABLE_REGS <= 5) 
    {
     bi_ti = __emit_bin_bitand(WBITS, ndx_ti, bi_shift_ti);
    }
   t1_ti = __emit_shiftr(WBITS, bi_ti, wrd_ti);
   new_gateval2_ti = __emit_bin_bitand(WBITS,  three_ti, t1_ti);

   /* new gate value must have the same tmp regardless if adjust is done */
   __emit_copy(WRDBYTES, new_gateval2_ti, new_gateval_ti);

   __start_bblk(newgat_nonx_bbp);
  }
 
 if (gp->g_delrep == DT_NONE)
  {
   nodel_outchg_bbp = __alloc_bblk(FALSE); 
   /* no delay case - if state unchged, nothing to do */
   __emit_jmp_eq(done_bbp, nodel_outchg_bbp, new_gateval_ti, gout_val_ti);

   __start_bblk(nodel_outchg_bbp);

   /* notice must update state - but have already computed it */
   if (udpp->u_wide)
    {
     /* notice the new gate value is also the state */
     /* remove old coordinate's (old gate out (state) term) contribution */
     /* AIV LOOKATME - aren't these know to be converted from above ???? */
     t1_ti = __emit_bin_bitand(WBITS, three_ti, gout_val_ti);
     /* AIV 05/11/08 - should use these simple table instead of doing compare */
     t1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, t1_ti, 
      NLO_UDP_UVALTAB);

     cint_ti = __gen_cint_tn(__pow3tab[udpp->numins]);
     t2_ti = __emit_mult(WBITS, t1_ti, cint_ti);
     ndx_polynomial_ti = __emit_sub(WBITS, ndx_polynomial_ti, t2_ti);

     /* add in new coodinate's (input terminal) contribution */
     /* AIV 05/11/08 - should use these simple table instead of doing compare */
     /* AIV 06/05/08 - need the mask here cannot ndx with byte high not zero */
     t3_ti = __emit_bin_bitand(WBITS, three_ti, new_gateval_ti);
     t1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, t3_ti, 
       NLO_UDP_UVALTAB);

     t2_ti = __emit_mult(WBITS, t1_ti, cint_ti);
     ndx_polynomial_ti = __emit_add(WBITS, ndx_polynomial_ti, t2_ti);

     /* only update state 2nd word vector for wide */
     __emit_copy(WRDBYTES, ndx_polynomial_ti, ndxvec_state_apti);
     __emit_copy(WRDBYTES, new_gateval_ti, gout_val_ti);

     /* also update the terminal state 0th word */
     mask = ~(3UL << (2*udpp->numins));
     cint_ti = __gen_cint_tn(mask);
     t1_ti = __emit_bin_bitand(WBITS,  uwrd_ti, cint_ti);
     cint_ti = __gen_cint_tn(2*udpp->numins);
     t2_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);
     uwrd_ti = __emit_bin_bitor(2*udpp->numins,  t1_ti, t2_ti);
     __emit_copy(WRDBYTES, uwrd_ti, gstate_apti);
    }
   else
    {
     mask = ~(3UL << (2*udpp->numins));
     cint_ti = __gen_cint_tn(mask);
     t1_ti = __emit_bin_bitand(WBITS, cint_ti, uwrd_ti);
     cint_ti = __gen_cint_tn(2*udpp->numins);
     t2_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);
     uwrd_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
     // gp->gstate.hwp[__inum] = (hword) gwrd;
     __emit_copy(2, uwrd_ti, gstate_apti);
     __emit_copy(WRDBYTES, new_gateval_ti, gout_val_ti);
    }

   /* gen vinsns to assign to the output terminal */ 
   xp = gp->gpins[0];
   if (xp->x_multfi) gen_mdr_assgn_or_schd_insns(xp);
   else if (xp->x_stren) 
    {
     gen_gate_stren_added_assign(gp, xp, new_gateval_ti, TRUE);
    }
   else if (xp->lhsx_ndel) 
    {
     gen_sched_conta_assign(xp, new_gateval_ti);
    }
   else gen_conta_assgn(xp, new_gateval_ti);
  }
 else 
  {
   gen_prop_gatechg(gp, new_gateval_ti, gout_val_ti, done_bbp, -1);
  }
}

/*
 * code from v_sim.c to do strength add assign
 store gate or udp where value maybe needs constant strength added 
 */
static void gen_gate_stren_added_assign(struct gate_t *gp, struct expr_t *xp, 
 int32 new_gateval_ti, int32 needs_stren_map)
{
 int32 tmp_sbpti, t1_ti, t2_ti, sb_ti, cint_ti;
 word32 mask;
 struct bblk_t *ngtwo_bbp, *st_map_bbp, *assign_bbp;

 if (needs_stren_map) 
  {
   ngtwo_bbp = __alloc_bblk(FALSE);
   st_map_bbp = __alloc_bblk(FALSE);
   assign_bbp = __alloc_bblk(FALSE);

   sb_ti = __gen_tn(SR_VEC, WBITS);
   cint_ti = __gen_cint_tn(2);
   __emit_jmp_byte_eq(ngtwo_bbp, st_map_bbp, new_gateval_ti, cint_ti);

   __start_bblk(ngtwo_bbp);
   __emit_copy(WRDBYTES, cint_ti, sb_ti);
   __emit_jmp(assign_bbp);

   __start_bblk(st_map_bbp);
   mask = gp->g_stval << 2;
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitor(WBITS, new_gateval_ti, cint_ti);
   t2_ti = __emit_stren_map_tab(t1_ti);
   __emit_copy(WRDBYTES, t2_ti, sb_ti);
   __start_bblk(assign_bbp);
  }
 else sb_ti = new_gateval_ti;

 /* other bits to z since only has 1 driver */
 if (xp->szu.xclen > 1)
  {
   tmp_sbpti = __gen_tn(SR_SVEC, xp->szu.xclen);
   __emit_setstren(tmp_sbpti, ST_HIZ, __get_tnwid(tmp_sbpti));
  }
 else tmp_sbpti = __gen_tn(SR_SSCAL, xp->szu.xclen);
  /* copy the low byte */
 __emit_copy(1, sb_ti, tmp_sbpti);

 if (xp->lhsx_ndel) gen_sched_conta_assign(xp, tmp_sbpti);
 else gen_conta_assgn(xp, tmp_sbpti);
}
     
/*
 * do the udp with delay assign and updating of udp state
 * __change_gate_outwire for GC_UDP state case
 */
static void gen_gate_udp_delay_assign(struct gate_t *gp, struct expr_t *xp, 
 int32 newval_ti)
{
 int32 gstate_adr_ti, gstate_1_ti, cint_ti, t1_ti, t2_ti, t3_ti, wp1_ti;
 int32 nins, bi; 
 word32 mask;
 struct udp_t *udpp;

 udpp = gp->gmsym->el.eudpp;
 gstate_adr_ti = __gen_gatebp_tn(gp, WBITS); 
 nins = udpp->numins;
 if (udpp->u_wide)
  {
   /* special case does some special adjusting */
   if (udpp->utyp != U_COMB)
    {
     gstate_1_ti = __con_adradd_insn(SR_VEC, WBITS, gstate_adr_ti, WRDBYTES);
     wp1_ti = __emit_udp_wide_adjust_state(gstate_adr_ti, nins);
     __emit_copy(WRDBYTES, wp1_ti, gstate_1_ti);
    }
  }
 /* wp[0] &= ~(3L << bi); wp[0] |= (__new_gateval << bi); */
 bi = 2*nins;
 mask = ~(3UL << bi);
 cint_ti = __gen_cint_tn(mask);
 t1_ti = __emit_bin_bitand(WBITS, gstate_adr_ti, cint_ti);
 cint_ti = __gen_cint_tn(bi);
 t2_ti = __emit_shiftl(WBITS, cint_ti, newval_ti);
 t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
 __emit_copy(WRDBYTES, t3_ti, gstate_adr_ti);

 if (xp->lhsx_ndel) gen_sched_conta_assign(xp, newval_ti);
 else gen_conta_assgn(xp, newval_ti);
}

/*
 * gen vinsns to eval mos gate after input change and propagate/assgn chg 
 */
static void gen_np_chg_mos_gate(struct net_pin_t *npp, struct bblk_t *done_bbp)
{
 int32 gbp_ti, scal_inval_ti, gout_val_ti;
 int32 old_inval_ti, uwrd_ti, new_gateval_ti, inval_tmp_ti;
 int32 inval_apti, t1_ti, t2_ti, gid, cint_ti;
 word32 mask;
 struct gate_t *gp;
 struct expr_t *xp;
 struct bblk_t *update_state_bbp, *nodel_outchg_bbp;

 update_state_bbp = __alloc_bblk(FALSE);

 gp = npp->elnpp.egp;
 gbp_ti = __gen_gatebp_tn(gp, 12); 

 /* copy the state value into a tmp */
 uwrd_ti = __gen_tn(SR_VEC, WBITS);
 __emit_copy(WRDBYTES, gbp_ti, uwrd_ti);

 gp = npp->elnpp.egp;
 xp = gp->gpins[npp->obnum];

 if (npp->obnum == 1)
  {
   /* copy only the low byte into the result */
   /* __new_inputval = sbp[0]; */
   inval_tmp_ti = gen_ndst_expr_eval(xp);
   scal_inval_ti = __gen_tn(SR_VEC, 8);
   __emit_copy(WRDBYTES, inval_tmp_ti, scal_inval_ti);
   cint_ti = __gen_cint_tn(0xff);
   scal_inval_ti = __emit_bin_bitand(WBITS, scal_inval_ti, cint_ti);
   
   __emit_set_new_inval(scal_inval_ti);
   old_inval_ti = __emit_bin_bitand(WBITS, uwrd_ti, cint_ti);
  }
 else
  {
   inval_apti = __gen_expr_eval(xp, -1);
   scal_inval_ti = __gen_cnvt_srep_ifneeded(inval_apti, SR_SCAL, 1, FALSE,
    FALSE, TRUE);

   cint_ti = __gen_cint_tn(8);
   t1_ti = __emit_shiftr(WBITS, cint_ti, uwrd_ti);
   cint_ti = __gen_cint_tn(3);
   old_inval_ti = __emit_bin_bitand(WBITS, t1_ti, cint_ti);
  }

 __emit_jmp_eq(done_bbp, update_state_bbp, scal_inval_ti, old_inval_ti);
 __start_bblk(update_state_bbp);

 if (npp->obnum == 1)
  {
   mask = ~(0xff);
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, uwrd_ti, cint_ti);
   uwrd_ti = __emit_bin_bitor(WBITS, t1_ti, scal_inval_ti);
  }
 else
  {
   mask = ~(3 << 8);
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, uwrd_ti, cint_ti);
   cint_ti = __gen_cint_tn(8);
   t2_ti = __emit_shiftl(WBITS, cint_ti, scal_inval_ti);
   uwrd_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
  } 
 // gp->gstate.wp[__inum] = (hword) gwrd;
 __emit_copy(WRDBYTES, uwrd_ti, gbp_ti);


 gid = gp->gmsym->el.eprimp->gateid;
 /* gen the wrapper for the complex routines to set new and old gate vals */
 switch (gid) {
  case G_NMOS:
   __emit_eval_nmos_gate(uwrd_ti);
   break;
  case G_RNMOS:
   __emit_eval_rnmos_gate(uwrd_ti);
   break;
  case G_PMOS:
   __emit_eval_pmos_gate(uwrd_ti);
   break;
  case G_RPMOS:
   __emit_eval_rpmos_gate(uwrd_ti);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }

 /* need to load old gateval and new gateval */
 /* SJM 11/01/05 - better for interpreter mos gate eval to return out_chg */
 new_gateval_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NEWGVAL);

 gout_val_ti = __gen_gate_output_value(gp, FALSE);
 if (gp->g_delrep == DT_NONE)
  {
   nodel_outchg_bbp = __alloc_bblk(FALSE); 
   /* no delay case - if state unchged, nothing to do */
   __emit_jmp_eq(done_bbp, nodel_outchg_bbp, new_gateval_ti, gout_val_ti);

   __start_bblk(nodel_outchg_bbp);

   /* mos changed and no delay - update state and assign to out term */
   __emit_copy(WRDBYTES, new_gateval_ti, gout_val_ti);

   /* gen vinsns to assign to the output terminal */ 
   xp = gp->gpins[0];
   if (xp->x_multfi) gen_mdr_assgn_or_schd_insns(xp);
   else gen_gate_stren_assign(xp, new_gateval_ti);
  }
 else 
  {
   gen_prop_gatechg(gp, new_gateval_ti, gout_val_ti, done_bbp, -1);
  }
}

/*
 * gen vinsns to eval mos gate after input change and propagate/assgn chg 
 *
 * notice cmos gate state still fits in one word 
 */
static void gen_np_chg_cmos_gate(struct net_pin_t *npp, struct bblk_t *done_bbp)
{
 int32 gbp_ti, scal_inval_ti, scal_wrd_ti;
 int32 old_inval_ti, gwrd_ti, new_gateval_ti, gout_val_ti;
 int32 pmos_gwrd_ti, nmos_gwrd_ti, outchg_ti, inval_tmp_ti, cint_ti;
 int32 inval_apti, t1_ti, t2_ti, t3_ti, gid, wtyp, shftamt;
 word32 mask;
 struct gate_t *gp;
 struct expr_t *xp;
 struct bblk_t *update_state_bbp, *nodel_outchg_bbp;

 update_state_bbp = __alloc_bblk(FALSE);

 gp = npp->elnpp.egp;
 gbp_ti = __gen_gatebp_tn(gp, 12); 

 /* copy the state value into a tmp */
 gwrd_ti = __gen_tn(SR_VEC, WBITS);
 __emit_copy(WRDBYTES, gbp_ti, gwrd_ti);

 gp = npp->elnpp.egp;
 xp = gp->gpins[npp->obnum];

 if (npp->obnum == 1)
  {
   /* copy only the low byte into the result */
   /* __new_inputval = sbp[0]; */
   inval_tmp_ti = gen_ndst_expr_eval(xp);
   scal_inval_ti = __gen_tn(SR_VEC, 8);
   __emit_copy(WRDBYTES, inval_tmp_ti, scal_inval_ti);

   cint_ti = __gen_cint_tn(0xff);
   old_inval_ti = __emit_bin_bitand(WBITS, gwrd_ti, cint_ti);
  }
 else
  {
   inval_apti = __gen_expr_eval(xp, -1);
   /* this will remove stren if needed */
   scal_inval_ti = __gen_cnvt_srep_ifneeded(inval_apti, SR_SCAL, 1, FALSE,
    FALSE, TRUE);

   if (npp->obnum == 2)
    {
     /* n (mos) control bits 15-8 */
     cint_ti = __gen_cint_tn(8);
     t1_ti = __emit_shiftr(WBITS, cint_ti, gwrd_ti);
    }
   else
    {
     cint_ti = __gen_cint_tn(16);
     t1_ti = __emit_shiftr(WBITS, cint_ti, gwrd_ti);
    }
   cint_ti = __gen_cint_tn(3);
   old_inval_ti = __emit_bin_bitand(WBITS, t1_ti, cint_ti);
  }
 __emit_set_new_inval(scal_inval_ti);

 __emit_jmp_eq(done_bbp, update_state_bbp, scal_inval_ti, old_inval_ti);

 __start_bblk(update_state_bbp);
 
 /* AIV 12/27/06 - had the same problem bufif had */
 /* AIV 10/18/06 - there was a bug with using a scalar in word operations */
 /* say inval_ti was scalar it was leaving scalar and doing word operations */
 /* this is a problem because of the following code */
 /* movl M_scalar, %eax; shll %ebx, %eax;   need to zero the high part */
 /* of the reg the copy of 1 byte will zero with mozbl */
 /* AIV 02/25/08 - better to just mask low byte */
 mask = 0xff;
 cint_ti = __gen_cint_tn(mask);
 scal_wrd_ti = __emit_bin_bitand(WBITS, cint_ti, scal_inval_ti);

 if (npp->obnum == 1)
  {
   mask = ~(0xff);
   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, cint_ti, gwrd_ti);
   gwrd_ti = __emit_bin_bitor(WBITS, t1_ti, scal_wrd_ti);
  }
 else
  {
   shftamt = 0;
   if (npp->obnum == 2) 
    {
     /* n ctrl bits 15-8 */
     mask = ~(3 << 8);
     shftamt = 8;
    }
   else if (npp->obnum == 3)
    {
     /* p ctrl bits 23-16 */
     mask = ~(3 << 16);
     shftamt = 16;
    }
   else __case_terr(__FILE__, __LINE__);

   cint_ti = __gen_cint_tn(mask);
   t1_ti = __emit_bin_bitand(WBITS, gwrd_ti, cint_ti);
   cint_ti = __gen_cint_tn(shftamt);
   t2_ti = __emit_shiftl(WBITS, cint_ti, scal_wrd_ti);
   gwrd_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
  }
 __emit_copy(WRDBYTES, gwrd_ti, gbp_ti);

 gid = gp->gmsym->el.eprimp->gateid;

 /* compute tmp word for nmos half for eval */
 // tmpwrd = (gwrd & 0xffffL) | ((gwrd >> 8) & 0x00ff0000L);
 cint_ti = __gen_cint_tn(0xffff);
 t1_ti = __emit_bin_bitand(WBITS, gwrd_ti, cint_ti);
 cint_ti = __gen_cint_tn(8);
 t2_ti = __emit_shiftr(WBITS, cint_ti, gwrd_ti);
 cint_ti = __gen_cint_tn(0x00ff0000);
 t3_ti = __emit_bin_bitand(WBITS, t2_ti, cint_ti);
 nmos_gwrd_ti = __emit_bin_bitor(WBITS, t1_ti, t3_ti);

 /* compute tmp word for pmos half for eval */
 // tmpwrd = (gwrd & 0xffL) | ((gwrd >> 8) & 0x00ffff00L);
 cint_ti = __gen_cint_tn(0xff);
 t1_ti = __emit_bin_bitand(WBITS, gwrd_ti, cint_ti);
 cint_ti = __gen_cint_tn(0x00ffff00);
 t3_ti = __emit_bin_bitand(WBITS, t2_ti, cint_ti);
 pmos_gwrd_ti = __emit_bin_bitor(WBITS, t1_ti, t3_ti);

 gout_val_ti = __gen_gate_output_value(gp, FALSE);

 xp = gp->gpins[0];
 wtyp = (word32) N_REG;
 switch (xp->optyp) {
  case ID: case GLBREF: wtyp = xp->lu.sy->el.enp->ntyp; break;
  case LSB: wtyp = xp->lu.x->lu.sy->el.enp->ntyp; break;
  default: __case_terr(__FILE__, __LINE__);
 }

 if (gid == G_CMOS)
  {
   outchg_ti = __emit_eval_cmos_gate(nmos_gwrd_ti, pmos_gwrd_ti, 
    gout_val_ti, wtyp);
  }
 else if (gid == G_RCMOS) 
  {
   outchg_ti = __emit_eval_rcmos_gate(nmos_gwrd_ti, pmos_gwrd_ti, 
    gout_val_ti, wtyp);
  }
 else { outchg_ti = -1; __case_terr(__FILE__, __LINE__); }

 /* need to load old gateval and new gateval */
 /* SJM 11/01/05 - better for interpreter mos gate eval to return out_chg */
 new_gateval_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NEWGVAL);

 if (gp->g_delrep == DT_NONE)
  {
   nodel_outchg_bbp = __alloc_bblk(FALSE); 
   /* no delay case - if state unchged, nothing to do */
   __emit_jmp_0(done_bbp, nodel_outchg_bbp, outchg_ti);

   __start_bblk(nodel_outchg_bbp);

   /* mos changed and no delay - update state and assign to out term */
   __emit_copy(WRDBYTES, new_gateval_ti, gout_val_ti);

   // gp->gstate.wp[__inum] = (hword) gwrd;
   __emit_copy(WRDBYTES, gwrd_ti, gbp_ti);

   /* gen vinsns to assign to the output terminal */ 
   xp = gp->gpins[0];
   if (xp->x_multfi) gen_mdr_assgn_or_schd_insns(xp);
   else gen_gate_stren_assign(xp, new_gateval_ti);
  }
 else 
  {
   gen_prop_gatechg(gp, new_gateval_ti, gout_val_ti, done_bbp, outchg_ti);
  }
}

/*
 * do gate strength assign from v_sim.c:do_hasstren_assign
 */
static void gen_gate_stren_assign(struct expr_t *xp, int32 new_gateval_ti)
{
 int32 tmp_sbpti;

 /* other bits to z since only has 1 driver */
 if (xp->szu.xclen > 1)
  {
   tmp_sbpti = __gen_tn(SR_SVEC, xp->szu.xclen);
   __emit_setstren(tmp_sbpti, ST_HIZ, __get_tnwid(tmp_sbpti));
//AIV LOOKATME 11/08/06 - problem area unit memory ???????
//only copying one byte
   /* copy the low byte */
   __emit_copy(1, new_gateval_ti, tmp_sbpti);
  }
 else 
  {
   tmp_sbpti = __gen_tn(SR_SSCAL, xp->szu.xclen);
   /* copy the low byte */
   __emit_copy(1, new_gateval_ti, tmp_sbpti);
  }

 if (xp->lhsx_ndel) gen_sched_conta_assign(xp, tmp_sbpti);
 else gen_conta_assgn(xp, tmp_sbpti);
}

/*
 * generate backend gate (gates with delays) assign value flow graphs 
 */
static void gen_gate_delay_assign_flowgs(struct mod_t *mdp)
{
 int32 gi;
 struct gate_t *gp;
 struct flowg_t *fgp;
 struct bblk_t *enter_bbp;
 struct gate_da_list_t *gdap;

 for (gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);
   /* AIV FIXME - only doing logic and bufif gates for now */
   if (!__gate_needs_output_word(gp->g_class)) continue;
   /* not decomposing the wide case */
   if (gp->g_delrep == DT_NONE) continue;

   /* basically flow graph is gate conta LOOKATME???? call something else??? */ 
   fgp = __alloc_flowg(FLOWG_GATEDA);
   __cur_ifrom_u.from_gateca = gi;
   __cur_flowg = fgp;
   __cur_bbp = NULL;

   enter_bbp = __alloc_bblk(FALSE);
   __start_bblk(enter_bbp); 
   enter_bbp->after_suspend = TRUE;

   __emit_enter_gate_delay_assign(gi);
   gen_gate_delay_assign(gp);
   __emit_complete();

   gdap = (struct gate_da_list_t *) __my_malloc(sizeof(struct gate_da_list_t));
   gdap->fgp = fgp;
   gdap->nxt = NULL;
   if (__hd_gdap == NULL)
    {
     __hd_gdap = __tail_gdap = gdap;
    }
   else
    {
     __tail_gdap->nxt = gdap;
     __tail_gdap = gdap;
    }
  }
}
   
/*
 * generate the guts of the backend gate (gates with delays) assigns
 */
static void gen_gate_delay_assign(struct gate_t *gp)
{
 int32 gout_val_ti, newval_ti, ctevp_ti, srtyp;
 struct expr_t *xp;
 struct ctev_t *ctevp;

 ctevp = gp->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);
 /* if 2-state get load as SR_SCAL2S */
 xp = gp->gpins[0];
 if (__is_expr_2state(xp)) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;

 newval_ti =  __emit_ld_gate_val_from_tev(ctevp_ti, (srtyp == SR_SCAL2S));

 gout_val_ti = __gen_gate_output_value(gp, (srtyp == SR_SCAL2S));
 __emit_copy(WRDBYTES, newval_ti, gout_val_ti);

 if (xp->x_multfi) gen_mdr_assgn_or_schd_insns(xp);
 else if (xp->x_stren) 
  {
 //AIV LOOKATME - bufif does not need the stren mapping - stored as stren 
//this whole gate backend scheduling assign is a work in progress
   if (gp->g_class == GC_LOGIC)
    {
     gen_gate_stren_added_assign(gp, xp, newval_ti, TRUE);
    }
   else if (gp->g_class == GC_BUFIF || gp->g_class == GC_CMOS 
        || gp->g_class == GC_MOS)
    {
     gen_gate_stren_added_assign(gp, xp, newval_ti, FALSE);
    }
   else if (gp->g_class == GC_UDP)
    {
     gen_gate_udp_delay_assign(gp, xp, newval_ti);
    }
   else __case_terr(__FILE__, __LINE__);
  }
 else 
  {
   /* AIV 12/20/07 - need to update udp state here as well */
   if (gp->g_class == GC_UDP)
    {
     gen_gate_udp_delay_assign(gp, xp, newval_ti);
    }
   else if (xp->lhsx_ndel) 
    {
     gen_sched_conta_assign(xp, newval_ti);
    }
   else gen_conta_assgn(xp, newval_ti);
  }
}


/*
 * ROUTINES TO GENERATE NET PIN CHG PROPAGATE FOR CONT ASSIGNS 
 */

/*
 * gen insnss for NP CONTA continuous assign 
 *
 * see eval conta rhs ld routine for interpreted routine - vinsns
 * gened here to mimic its function 
 *
 * following LRM, no pulse/glitch for contas - just inertial algorithm
 * conta do not pass rhs stren, but may add stren from conta stmt 
 */
static void gen_np_conta(struct net_pin_t *npp)
{
 int32 rhs2_ti, rhs_ti, cap_del_rhs_ti, lhs_srep, nbytes, srtyp;
 struct conta_t *cap, *mast_cap;
 struct expr_t *lhsx, *rhsx;

 mast_cap = npp->elnpp.ecap;
 if (mast_cap->ca_pb_sim) cap = &(mast_cap->pbcau.pbcaps[npp->pbi]);
 else cap = mast_cap;

 /* get pattern never decomposd per bit and use wrapper iop since rare */
 /* special case where know rhs is non decomposable concat */
 /* know getpat never has delay */
 if (mast_cap->lhsx->getpatlhs)
  {
   gen_getpattern(mast_cap);
   return;
  }

 /* if conta doesn't have a delay just call the lowered conta flowg */
 if (mast_cap->ca_delrep == DT_NONE)
  {
   /* AIV 10/06/08 - if code is inlined don't call - inline the conta  */
   if (__inline_code)
    {
     gen_np_conta_nodelay(cap);
    }
   else
    {
     __emit_call_conta(cap);
    }
   return;
  }

 /* know getpat never has delay */
 lhsx = cap->lhsx;
 rhsx = cap->rhsx;

 /* for all non simple case, need to eval non stren and then add stren */
 /* even if removes stren */
 /* AIV 11/10/09 - want a vector here */
 rhs2_ti = __gen_expr_eval(rhsx, WANT_A_VEC);
 lhs_srep = __get_lhs_srep(lhsx, &nbytes);

 /* need copy if sizes different */
 /* SJM 02/27/03 - must fill tmp with exactly right width rhs */
 /* since rhs width must exactly match lhs for concat and stren add */
 if (lhs_srep == SR_SCAL2S || lhs_srep == SR_BIT2S)
  {
   srtyp = SR_BIT2S;
  }
 else srtyp = SR_VEC;
 rhs_ti = __gen_cnvt_srep_ifneeded(rhs2_ti, srtyp, lhsx->szu.xclen,
    lhsx->has_sign, FALSE, TRUE);

 /* any lhs concat, lhs fi>1, path delay assign schedule handled in */
 /* ev processing routine */
 gen_delay_rhs_ca_ld(npp, rhs_ti, srtyp); 
 cap_del_rhs_ti = __gen_conta_schbp_tn(cap, srtyp);
 __emit_copy(nbytes, rhs_ti, cap_del_rhs_ti);
}
   
/*
 * AIV 11/20/07 - must be inlined because uses has net changes
 */
static void gen_getpattern(struct conta_t *cap)
{
 int32 bi, is_2state;
 struct expr_t *catx;
 int32 cbita_ti, cbitb_ti, t1_ti, t2_ti, t3_ti, cint_ti, one_ti, uwrd_ti;
 int32 tmpa_wi_ti, tmpb_wi_ti, rhs_ti, addr_ti;
 int32 wi, wlen, ubits, ofs;
 struct expr_t *idndp, *lhsxp, *rhsxp;
 struct net_t *np;

 /* know rhs is variable array index */
 /* rhs is get pattern function call */
 lhsxp = cap->lhsx;
 rhsxp = cap->rhsx;
 /* AIV 11/10/09 - want a vector here */
 rhs_ti = __gen_expr_eval(rhsxp->ru.x->lu.x, WANT_A_VEC);

 tmpb_wi_ti = -1;
 wlen = wlen_(lhsxp->szu.xclen);
 ubits = ubits_(lhsxp->szu.xclen);
 catx = lhsxp->ru.x;
 bi = (ubits == 0) ? WBITS - 1: ubits - 1;
 idndp = catx->lu.x;
 np = idndp->lu.sy->el.enp;
 is_2state = (np->n_2state);
 for (wi = wlen - 1; wi >= 0; wi--)
  {
   if (is_2state)
    {
     tmpa_wi_ti = __con_adradd_insn(SR_BIT2S, WBITS, rhs_ti, wi*WRDBYTES);
    }
   else
    {
     tmpa_wi_ti = __con_adradd_insn(SR_VEC, WBITS, rhs_ti, wi*WRDBYTES);
     ofs = (wi + wlen)*WRDBYTES;
     tmpb_wi_ti = __con_adradd_insn(SR_VEC, WBITS, rhs_ti, ofs);
    }

   for (; bi >= 0; catx = catx->ru.x, bi--)
    {
     if (catx == NULL) return;

     idndp = catx->lu.x;
     np = idndp->lu.sy->el.enp;

     /* know lhs get pat concat elements are scalars */
     /* cbita = (tmpa >> bi) & 1L; */
     cint_ti = __gen_cint_tn(bi);
     t1_ti = __emit_shiftr(WBITS, cint_ti, tmpa_wi_ti);
     one_ti = __gen_cint_tn(1);
     /* cbitb = (tmpb >> bi) & 1L; */
     if (is_2state)
      {
       uwrd_ti = __emit_srep_mask_and(SR_SCAL2S, 1, t1_ti, one_ti);
      }
     else
      {
       cbita_ti = __emit_bin_bitand(WBITS, t1_ti, one_ti);
       t2_ti = __emit_shiftr(WBITS, cint_ti, tmpb_wi_ti);
       cbitb_ti = __emit_bin_bitand(WBITS, t2_ti, one_ti);

       /* uwrd = cbita | (cbitb << 1); */
       t3_ti = __emit_shiftl(WBITS, one_ti, cbitb_ti);
       uwrd_ti = __emit_bin_bitor(WBITS, cbita_ti, t3_ti);
       /* __get_st* are expecting type scalar which this is know to be */
       __tntab[uwrd_ti].srtyp = SR_SCAL;
      }
 
//AIV FIXME AIV LOOKATME - what about xmr isn't this wrong in interp??????
     addr_ti = __ldvar_addr(np, NULL);
     if (__net_chg_nd_store(np, -1, -1)) 
      {
       __gen_chg_st_val(np, addr_ti, uwrd_ti);
      }
     else __gen_st_val(np, addr_ti, uwrd_ti);
    }
   bi = WBITS - 1;
   if (catx == NULL) break;
  }
}

/*
 * gen a np continuous assign with no delay
 */
static void gen_np_conta_nodelay(struct conta_t *cap)
{
 int32 rhs2_ti, rhs_ti, lhs_srep, nbytes, want_a_vec;
 struct expr_t *lhsx, *rhsx;

 lhsx = cap->lhsx;
 rhsx = cap->rhsx;

 rhs_ti = -1;
 /* handle some special cases only if simple */
 /* if need to store driving/event sim state or complex lhs can't use */
 if (cap->ca_delrep == DT_NONE && !lhsx->x_multfi
  && lhsx->optyp != LCB && !lhsx->lhsx_ndel)
  {
   /* these are cases where can just do simple copies of rhs */ 
   if (lhsx->x_stren) gen_conta_addstren_assgn(lhsx, rhsx, cap->ca_stval);
   else
    {
     /* case 2: lhs non stren - implied strong */
     /* eval possibly removing strens then simple assign */
     rhs_ti = __gen_expr_eval(rhsx, -1);
     /* decl assign optimum and handles possible lhs wire force */
     gen_conta_assgn(lhsx, rhs_ti);
    }
   return;
  }

 /* for all non simple case, need to eval non stren and then add stren */
 /* even if removes stren */
 lhs_srep = __get_lhs_srep(lhsx, &nbytes);
 want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : -1;
 rhs2_ti = __gen_expr_eval(rhsx, want_a_vec);

 /* need copy if sizes different */
 /* SJM 02/27/03 - must fill tmp with exactly right width rhs */
 /* since rhs width must exactly match lhs for concat and stren add */
 rhs_ti = __gen_cnvt_srep_ifneeded(rhs2_ti, lhs_srep, lhsx->szu.xclen,
    lhsx->has_sign, FALSE, TRUE);
 assign_conta_rhs(cap, rhs_ti);
}

/*
 * assign rhs conta 
 */
static void assign_conta_rhs(struct conta_t *cap, int32 rhs_ti)
{
 int32 rhs2_ti, drvadr_ti, nbytes, lhs_srep, srtyp;
 struct expr_t *lhsx;
 
 lhsx = cap->lhsx;
 /* for lhsx fi>1 always store rhs expr val into ca drv wp driving val */
 /* value is entire rhs for lhs concat immediate conta */
 if (lhsx->x_multfi)
  {
   lhs_srep = __get_lhs_srep(lhsx, &nbytes);
   if (lhs_srep == SR_SCAL2S || lhs_srep == SR_BIT2S)
    {
     srtyp = SR_BIT2S;
    }
   else srtyp = SR_VEC;
   drvadr_ti = __gen_conta_drvbp_tn(cap, srtyp);

   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(nbytes, rhs_ti, drvadr_ti);

   /* SJM 03/09/03 - for fi>1 ports move around must use push inst mod */
   /* here context itree loc can be any itree loc */
   if (lhsx->optyp == LCB) gen_multfi_decl_lhscat(lhsx);
   else gen_mdr_assgn_or_schd_insns(lhsx);
   return;
  }

 /* NOTICE - do not need add stren form since for immed, rhs has stren */
 /* for fi>1 or schedule back side iop to add will be stren gened there */
 if (lhsx->lhsx_ndel) 
  {
   /* AIV 10/13/06 - need to convert to strength */
   /* AIV 10/13/06 - LOOKATME - can't rhs be a strength - always need this?? */
   if (lhsx->x_stren)
    {
     rhs2_ti = gen_st_standval(lhsx->szu.xclen, rhs_ti, cap->ca_stval);
     rhs_ti = rhs2_ti;
    }
   /* AIV 01/11/07 - gen_decl_lhscat - handles lhsx_ndel with and without */
   if (lhsx->optyp == LCB) gen_decl_lhscat(lhsx, rhs_ti);
   else gen_sched_conta_assign(lhsx, rhs_ti);
  }
 else
  {
   if (lhsx->x_stren)
    {
     rhs2_ti = gen_st_standval(lhsx->szu.xclen, rhs_ti, cap->ca_stval);
     rhs_ti = rhs2_ti;
    }
   /* rhs tmp fld must have stren added and match lhs stren */ 
   if (lhsx->optyp == LCB) gen_decl_lhscat(lhsx, rhs_ti);
   else gen_conta_assgn(lhsx, rhs_ti);
  }
}

/*
 * create all continuous assign flow graphs
 * all continuous assigns (expect getpatlhs) are lowered as a 
 * seperate flow graph linked onto contas
 */
static void gen_conta_flowgs(struct mod_t *mdp)
{
 int32 i, pbi;
 struct conta_t *cap, *pb_cap;

 for (i = 0; i < mdp->mcanum; i++)
  {
   cap = &(mdp->mcas[i]);
   if (cap->lhsx->getpatlhs) continue;
   /* AIV 03/18/10 - if inlined and no delay there is no need to */
   /* produce the conta flowg - since they are inlined */
   /* if has delay can be schedule during init so still need */
   if (cap->ca_delrep == DT_NONE && __inline_code) continue;
   /* conta can only have one flowg */
   if (cap->flowg != NULL) continue;
//AIV LOOKATME - right insts??????
   __push_itstk(mdp->moditps[0]);
   gen_conta_one_flowgs(cap);
   if (cap->ca_pb_sim)
    {
     for (pbi = 0; pbi < cap->lhsx->szu.xclen; pbi++)
      { 
       pb_cap = &(cap->pbcau.pbcaps[pbi]);
       if (pb_cap->flowg != NULL) __misc_terr(__FILE__, __LINE__);
       gen_conta_one_flowgs(pb_cap);
      }
    }
   __pop_itstk();
  }
}

/*
 * generate all continuous assign flowgs
 */
static void gen_conta_one_flowgs(struct conta_t *cap)
{
 struct flowg_t *fgp;
 struct bblk_t *conta_bbp;
 struct expr_t *lhsx;
 int32 rhs_ti, cadrvadr_ti, processing_pnd0s_ti, nbytes, lhs_srep, srtyp;
 struct bblk_t *notnchg_bbp, *nchg_bbp;

 fgp = __alloc_flowg(FLOWG_CONTA);
 cap->flowg = fgp;
 __cur_flowg = fgp;

 __cur_bbp = NULL;

 conta_bbp = __alloc_bblk(FALSE);
 __start_bblk(conta_bbp); 
 __cur_ifrom_u.from_cap = cap;
 conta_bbp->after_suspend = TRUE;
 __emit_enter_conta(cap->enter_cndx);

 lhsx = cap->lhsx;
 /* if has a delay copy value stored in static memory */
 if (cap->ca_delrep != DT_NONE)
  {
   /* copy sched memory into driver memory */
   lhs_srep = __get_lhs_srep(lhsx, &nbytes);
   if (lhs_srep == SR_SCAL2S || lhs_srep == SR_BIT2S)
    {
     srtyp = SR_BIT2S;
    }
   else srtyp = SR_VEC;
   rhs_ti = __gen_conta_schbp_tn(cap, srtyp);

   cadrvadr_ti = __gen_conta_drvbp_tn(cap, srtyp);
   __emit_copy(nbytes, rhs_ti, cadrvadr_ti);
   /* do the continuous assign */
   assign_conta_rhs(cap, rhs_ti);
  }
 else 
  {
   /* gen continuous assign with no delay */
   gen_np_conta_nodelay(cap);
  }
 
 /* AIV 08/29/07 - can enter through conta sched delay */
 /* or process_complied_all_netchgs - if sched must jump to next event */
 /* nchgs events must return where sched must go to next schedule event */
 if (cap->ca_delrep != DT_NONE)
  {
   notnchg_bbp = __alloc_bblk(FALSE); 
   nchg_bbp = __alloc_bblk(FALSE); 

   /* AIV 12/29/08 - better to do a jmp0 than a compare against zero */
   processing_pnd0s_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_CUR_TEVP);
  __emit_jmp_0(nchg_bbp, notnchg_bbp, processing_pnd0s_ti);

   __start_bblk(notnchg_bbp);
   __emit_next_event();

   /* jump to complete block but will never reach it because of next jump */
   __emit_jmp(nchg_bbp);
   __start_bblk(nchg_bbp);

   __emit_complete();
  }
 else __emit_complete();
}

/*
 * gen lhs stren continuous assign vinsns
 * non stren same as normal assign so no separate routine
 */
static void gen_conta_addstren_assgn(struct expr_t *lhsx,
 struct expr_t *rhsx, byte ca_stren)
{
 int32 rhswid, rhs_ti, t1_ti, val;

 /* this just returns ptr for already stren var - else evals to sbp tmp */
 /* if rhs doesn't have strength eval and convert into svec */
 /* AIV 10/11/05 - LOOKATME - can't use convert here because stren here */
 /* are init/widen to have ca_stren value not stength 0 */
 /* AIV LOOKATME - maybe convert always init to strenght 0 is wrong */ 
 /* convert could take an initial strenght value ???? */
 if (!rhsx->x_stren)
  {
   t1_ti = __gen_expr_eval(rhsx, -1);
   rhs_ti = gen_st_standval(rhsx->szu.xclen, t1_ti, ca_stren);
   /* AIV 12/18/06 - was passing the wrong const value to the svec_cnvt */
   val = ca_stren << 2;
   val = __stren_map_tab[val];
   rhs_ti = gen_vec_to_svec_cnvt(lhsx->szu.xclen, rhs_ti, val);
  }
 else 
  {
   /* if rhs has strength only need to widen to lhs if needed */
   rhs_ti = gen_ndst_expr_eval(rhsx);
   rhswid = __get_tnwid(rhs_ti);
   if (rhswid < lhsx->szu.xclen) 
    {
     rhs_ti = gen_svec_widen(lhsx->szu.xclen, rhs_ti, (ca_stren << 2));
    }
   /* AIV 04/27/07 - was never adding strength */
   __emit_rhs_conta_stren(rhs_ti, ca_stren, lhsx->szu.xclen);
  }
 gen_stren_conta_assgn(lhsx, rhs_ti);
}

/*
 * gen insns to delay continuous assign to conta lhs
 *
 * for lhs concat delay schedule conta - schedule entire lhs concat conta,
 * then exec no delay conta when delay elapsed in ev processing routine 
 */
static void gen_delay_rhs_ca_ld(struct net_pin_t *npp, int32 rhs_apti,
 int32 srtyp) 
{
 int32 lhslen, cint_ti;
 int32 cap_ti, mastcap_ti, mastrhs_ti, tevp_ti, tevp_trigger_ti;
 int32 cadrv_apti, caschddrvadr_ti;
 int32 cond_nval_eq_ti, cond2_eq_ti;
 int32 rhs_bpti, cadrv_bpti, t1_ti, t2_ti, caschddrv_bpti, is_2state;
 struct conta_t *mast_cap, *cap; 
 struct bblk_t *done_bbp, *reschd_bbp, *chk_cancel_bbp, *cancel_bbp;
 struct bblk_t *nval_eq_bbp, *chk_evpend_bbp, *chk_reschd_bbp, *schd_bbp;
 struct ctev_t *ctevp;

 done_bbp = __alloc_bblk(FALSE);
 reschd_bbp = __alloc_bblk(FALSE);
 nval_eq_bbp = __alloc_bblk(FALSE);
 chk_evpend_bbp = __alloc_bblk(FALSE);
 chk_reschd_bbp = __alloc_bblk(FALSE);
 chk_cancel_bbp = __alloc_bblk(FALSE);
 cancel_bbp = __alloc_bblk(FALSE);
 schd_bbp = __alloc_bblk(FALSE);

 mast_cap = npp->elnpp.ecap;
 mastcap_ti = __gen_ca_tn(mast_cap);
 if (mast_cap->ca_pb_sim)
  {
   cap = &(mast_cap->pbcau.pbcaps[npp->pbi]); 
   cap_ti = __gen_ca_tn(cap);
  }
 else { cap_ti = mastcap_ti; cap = mast_cap; } 

 lhslen = cap->lhsx->szu.xclen;

 /* access the driving value, always sr vec even if stren added conta */
 is_2state = (srtyp == SR_BIT2S || srtyp == SR_SCAL2S);
 if (is_2state) cadrv_apti = __gen_conta_drvbp_tn(cap, SR_BIT2S);
 else cadrv_apti = __gen_conta_drvbp_tn(cap, SR_VEC);
 /* msgen table determines how vinsn args are interpreted */
 /* need to compare both a an b parts so need byte cmp */
 /* AIV 09/08/06 - changed to word compare since always aligned on word */
 if (is_2state)
  {
   if (lhslen > WBITS)
    {
     cond_nval_eq_ti = __emit_wordcmp(wlen_(lhslen), cadrv_apti, rhs_apti);
    }
   else cond_nval_eq_ti = __emit_bin_bitxor(WBITS, cadrv_apti, rhs_apti);
  }
 else if (lhslen > WBITS)
  {
   rhs_bpti = __get_bpti(rhs_apti);
   cond_nval_eq_ti = __emit_wordcmp(2*wlen_(lhslen), cadrv_apti, rhs_apti);
  }
 else
  {
   /* narrow case just xor (drv_a ^ rhsa) | (drv_b ^ rhsb) */
   rhs_bpti = __get_bpti(rhs_apti);
   cadrv_bpti = __get_bpti(cadrv_apti);
   t1_ti = __emit_bin_bitxor(WBITS, cadrv_apti, rhs_apti);
   t2_ti = __emit_bin_bitxor(WBITS, cadrv_bpti, rhs_bpti);
   cond_nval_eq_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
  }

 /* AIV 10/24/07 - now just check the trigger flag for fixed tevp */
 if (mast_cap->ca_pb_sim) ctevp = mast_cap->ctevp;
 else ctevp = cap->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 
 tevp_ti = __gen_ctevp_adr_tn(ctevp);
 tevp_trigger_ti = __gen_ctevp_trigger_flag(tevp_ti);

 __emit_jmp_0(nval_eq_bbp, chk_evpend_bbp, cond_nval_eq_ti);
 __start_bblk(nval_eq_bbp);

 __emit_jmp_0(done_bbp, chk_evpend_bbp, tevp_trigger_ti);
 __start_bblk(chk_evpend_bbp);

 /* SJM 08/21/05 - because $sdf annotate can change ca 4vdel would need */
 /* wrapper if sdf in source - for now knew only sdf option possible */
 if (mast_cap->ca_4vdel)
  {
   if (mast_cap->ca_pb_sim)
    {
     mastrhs_ti = __gen_expr_eval(mast_cap->rhsx, -1);
    }
   else mastrhs_ti = rhs_apti;

   __set_widconta_new_gateval(mastrhs_ti);
  }
 else
  {
   cint_ti = __gen_cint_tn(-1);
   __emit_set_new_gateval(cint_ti);
  }

 __emit_jmp_0(schd_bbp, chk_reschd_bbp, tevp_trigger_ti);
 __start_bblk(schd_bbp);
 
 if (mast_cap->ca_pb_sim)
  { 
   gen_schd_or_reschd_caev(tevp_ti, mast_cap, cap_ti, TRUE);
  }
 else
  {
   gen_schd_or_reschd_caev(tevp_ti, cap, cap_ti, TRUE);
  }
 __emit_jmp(done_bbp);
 __start_bblk(chk_reschd_bbp);

 caschddrvadr_ti = __gen_conta_schbp_tn(cap, srtyp);
 if (is_2state)
  {
   if (lhslen > WBITS)
    {
     cond2_eq_ti = __emit_wordcmp(wlen_(lhslen), caschddrvadr_ti, rhs_apti);
    }
   else cond2_eq_ti = __emit_bin_bitxor(WBITS, caschddrvadr_ti, rhs_apti);
  }
 else if (lhslen > WBITS)
  {
   cond2_eq_ti = __emit_wordcmp(2*wlen_(lhslen), caschddrvadr_ti, rhs_apti);
  }
 else
  {
   /* narrow case just xor (drv_a ^ rhsa) | (drv_b ^ rhsb) */
   caschddrv_bpti = __get_bpti(caschddrvadr_ti);
   rhs_bpti = __get_bpti(rhs_apti);
   t1_ti = __emit_bin_bitxor(WBITS, caschddrvadr_ti, rhs_apti);
   t2_ti = __emit_bin_bitxor(WBITS, caschddrv_bpti, rhs_bpti);
   cond2_eq_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
  }

 /* if pending scheduled same as new to re-schedule, nothing to do */
 __emit_jmp_0(done_bbp, chk_cancel_bbp, cond2_eq_ti);
 __start_bblk(chk_cancel_bbp);

 __emit_jmp_0(cancel_bbp, reschd_bbp, cond_nval_eq_ti);
 __start_bblk(cancel_bbp);

 __emit_cancel_ev(tevp_ti);

 __emit_jmp(done_bbp);
 __start_bblk(reschd_bbp);

 if (mast_cap->ca_pb_sim)
  {
   gen_schd_or_reschd_caev(tevp_ti, cap, cap_ti, FALSE);
  }
 else
  {
   gen_schd_or_reschd_caev(tevp_ti, cap, cap_ti, FALSE);
  }
 __start_bblk(done_bbp);
}

/*
 * schbed or reschedule a continuous assign 
 * if is_schd flag FLASE it is regular assign otherwise reschedule
 * if mastercap_ti == -1 it is regular otherwise pb
 */
static void gen_schd_or_reschd_caev(int32 tevp_ti, struct conta_t *delcap, 
 int32 cap_ti, int32 is_schd)
{
 int32 is_const;
 word64 candel;

 is_const = __check_delay_constant(delcap->ca_du, delcap->ca_delrep, &(candel));
 if (is_const)
  {
   /* time is constant */
   if (!is_schd)
    {
     __emit_reschd_caev_const(tevp_ti, candel);
    }
   else
    {
     __emit_schd_caev_const(tevp_ti, candel);
    }
  }
 else
  {
   if (!is_schd)
    {
     /* if mastercap_ti != -1 it is pb */
     /* AIV 11/29/06 - wasn't passing correct arguments to reschd_caev */
     __emit_reschd_caev(cap_ti, tevp_ti);
    }
   else
    {
     __emit_schd_caev(cap_ti, tevp_ti);
    }
  }
}

/*
 * ROUTINES TO GEN VINSNS FOR DECL ASSIGN/SCHED (MEDIUM LEVEL - RHS KNOWN)
 */

/*
 * routine to gen vinsn for fi>1 declarative lhs concat assign or schedule
 *
 * SJM 11/13/05 - FIXME - would be better to decompose concat components 
 * so could avoid fi>1 if component not multfi
 */
static void gen_multfi_decl_lhscat(struct expr_t *lhsx)
{
 int32 nels, lxi;
 struct expr_t *catlhsx, **lhsxtab;

 /* build the low to high decomposed lhs concat table */
 nels = __cnt_cat_size(lhsx);
 lhsxtab = (struct expr_t **) __my_malloc(nels*sizeof(struct expr_t *));
 lxi = nels - 1;
 /* fill expr tab in reverse order */
 catlhsx = lhsx->ru.x;
 for (; catlhsx != NULL; catlhsx = catlhsx->ru.x, lxi--)
  { lhsxtab[lxi] = catlhsx->lu.x; }

 /* but process in low to high order */
 for (lxi = 0; lxi < nels; lxi++)
  {
   /* gen vinsns to sel from rhs tmp into width that matches lhs cat el */
   gen_mdr_assgn_or_schd_insns(lhsxtab[lxi]);
  }
 /* AIV 01/23/07 - missing free lhsxtab */
 __my_free(lhsxtab, nels*sizeof(struct expr_t *));
}

/*
 * routine to gen insns for assign or schedule multi-fi net
 *
 * separate routine because same for decomposed concat and for decl conta
 * this routine run in lhs ref loc so for XMR must move to define (targ) loc
 */
static void gen_mdr_assgn_or_schd_insns(struct expr_t *lhsx)
{
 int32 nd_itpop, drv_apti, i1, i2, biti;
 int32 save_idp_ti;
 struct expr_t *idndp, *ndx1;
 struct net_t *np;

 i1 = i2 = -1;
 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;

 /* fi>1 must eval in any lhs xmr context */ 
 nd_itpop = FALSE;
 save_idp_ti = -1;
 if (idndp->optyp == GLBREF)
  {
   /* SJM 01/25/06 - right module set in bbgen but will be wrong in x86gen */
   gen_chgtorefgrp(idndp, &save_idp_ti, -1); 
   nd_itpop = TRUE;
  }

 /* handle fi>1 eval and store of bits in tran channel */
 /* any scheduling handled during tran channel update */ 
 if (np->ntraux != NULL)
  {
   /* AIV 11/12/07 - drivers are now lowered because need to pass static */
   /* net change events to wrappers */
   gen_tran_drvrs(np, nd_itpop); 
   if (nd_itpop)
    {
     __gen_restore_idp(save_idp_ti);
     /* SJM 04/23/03 - must update compile time module context too */
     __pop_itstk();
    }
   return;
  }

//AIV FIX - this need to call the prc gened in multi-driver load - how find?
 __ld_netadr_tn(np);
 /* AIV 09/27/07 - need to get the lhs change range because if lhsx */
 /* doesn't contain a change range don't need to do the change store */
 if (lhsx->optyp == GLBREF || lhsx->optyp == ID) 
  {
   i1 = i2 = -1;
  }
 else if (lhsx->optyp == LSB)
  {
   ndx1 = lhsx->ru.x;
   if (!__cvc_is_const_expr(ndx1))
    i1 = i2 = -1;
   else 
    {
     biti = __comp_ndx(np, ndx1);
     i1 = i2 = biti;
    }
  }
 else if (lhsx->optyp == PARTSEL) 
  {
   i1 = (int32) __contab[lhsx->ru.x->lu.x->ru.xvi];
   i2 = (int32) __contab[lhsx->ru.x->ru.x->ru.xvi];
  }
 else __misc_terr(__FILE__, __LINE__);

 /* this is a call insn of other gened insns */
 drv_apti = __emit_call_ldcomb_drvrs(np, np->srep, __inst_mod);


 /* stren competition includes any conta strens, must not add here */
 if (np->nrngrep == NX_DWIR)
  {
   gen_sched_1mdrwire(np, drv_apti);
  }
 else
  {
   if (np->n_stren) gen_assign_1stmdrwire(np, drv_apti, i1, i2);
   else gen_assign_1mdrwire(np, drv_apti, i1, i2);
  }

 if (nd_itpop)
  {
   __gen_restore_idp(save_idp_ti);
   __pop_itstk();
  }
}

 
/*
 * generate code to do the tran channel drivers
 */
static void gen_tran_drvrs(struct net_t *np, int32 idp_saved) 
{
 struct bblk_t *update_tran_bbp, *dont_update_bbp;
 int32 update_ti, np_ti;
 
 /* some bit changed update or schedule path dest. per bit channels */
 if (np->iotyp == IO_BID && np->n_isapthdst)
  {
   if (np->n_stren) gen_stren_schd_bidpthdrvrs(np);
   else gen_schd_bidpthdrvrs(np);
   return;
  }
 np_ti = __ld_netadr_tn(np);
 update_tran_bbp = __alloc_bblk(FALSE);
 dont_update_bbp = __alloc_bblk(FALSE);

 /* check if value has changed */
 update_ti = __emit_update_tran_harddrvs(np_ti);
 __emit_jmp_0(dont_update_bbp, update_tran_bbp, update_ti);

 __start_bblk(update_tran_bbp);
 __gen_tran_1net(np, np_ti, idp_saved);
 __emit_jmp(dont_update_bbp);
 __start_bblk(dont_update_bbp);
}

/*
 * build fg to process a path dest. tran (inout) wire delay internal 
 * hard driver change event for each bit of np
 */
static void bld_1net_trpthdst_flowgs(struct net_t *np)
{
 int32 bi, np_ti;

 /* build one for each bit */
 np_ti = __ld_netadr_tn(np);
 for (bi = 0; bi < np->nwid; bi++)
  {
   bld_1net_trpthdst_1bit_flowg(np, bi, np_ti);
  }
}
     
/*
 * build fg to process a path dest. tran (inout) wire delay internal 
 * hard driver change for bit bi for net np
 */
static void bld_1net_trpthdst_1bit_flowg(struct net_t *np, int32 bi, 
 int32 np_ti)
{
 int32 outv_ti, tran_sbp_ti, cint_ti, tran_sbp_bi_ti, tevp_ti;
 int32 tran_update_ti, tran_id;
 struct flowg_t *fgp;
 struct bblk_t *trpth_bbp, *chg_bbp, *no_chg_bbp;
 struct traux_t *trap;

 trap = np->ntraux;

 fgp = __alloc_flowg(FLOWG_TRPTH);
 add_flowg_to_netfg_list(np, fgp);
 __cur_flowg = fgp;
 __cur_bbp = NULL;

 trpth_bbp = __alloc_bblk(FALSE);
 __start_bblk(trpth_bbp); 
 trpth_bbp->after_suspend = TRUE;
 tran_id = get_tran_id(trap, np->nwid, bi);
 __emit_process_trpthdst_enter(tran_id);
 __cur_ifrom_u.from_np = np;


 cint_ti = __gen_cint_tn(bi);
 tevp_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_CUR_TEVP);
 outv_ti = __emit_ld_gate_val_from_tev(tevp_ti, FALSE);
 /* strength case */
 if (np->n_stren)
  {
   tran_sbp_ti = __emit_tran_addr(np_ti); 
   tran_sbp_bi_ti = __con_adradd_insn(SR_VEC, WBITS, tran_sbp_ti, bi);
   chg_bbp = __alloc_bblk(FALSE);
   no_chg_bbp = __alloc_bblk(FALSE);
   __emit_jmp_byte_eq(no_chg_bbp, chg_bbp, tran_sbp_bi_ti, outv_ti);
   __start_bblk(chg_bbp);
   __emit_copy(1, outv_ti, tran_sbp_bi_ti);
   /* do the one bit tran channel processing */
   gen_tran_1bit(np, np_ti, bi, FALSE); 
   __emit_jmp(no_chg_bbp);
   __start_bblk(no_chg_bbp);
  }
 else
  {
   if (np->n_isavec)
    {
     tran_update_ti = __emit_trpath_store(np_ti, outv_ti, cint_ti);
    }
   else tran_update_ti = __emit_trpath_scalar_store(np_ti, outv_ti);

   chg_bbp = __alloc_bblk(FALSE);
   no_chg_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(no_chg_bbp, chg_bbp, tran_update_ti);
   __start_bblk(chg_bbp);
   /* do the one bit tran channel processing */
   gen_tran_1bit(np, np_ti, bi, FALSE); 
   __emit_jmp(no_chg_bbp);
   __start_bblk(no_chg_bbp);
  }
 __emit_complete();
}

/*
 * set/get a tran id 
 */
static int32 get_tran_id(struct traux_t *trap, int32 nwid, int32 bi)
{
 /* if not yet set malloc values */
 if (trap->tran_ids == NULL) 
  {
   trap->tran_ids = (int32 *) __my_malloc(sizeof(int32)*nwid);
   memset(trap->tran_ids, 0xff, sizeof(int32)*nwid);
  }

 /* if bit not yet set value */
 if (trap->tran_ids[bi] == -1) 
  {
   trap->tran_ids[bi] = ++(__inst_mod->mod_ndx_seq_no); 
  }
 return(trap->tran_ids[bi]);
}

/*
 * schedule stren inout channel path destination hard drivers and channel
 * some bits may not have changed or need immediate assign and chan update
 *
 * AIV LOOKATME - combine these two routines
 * stren_schd_bidpthdrvrs & schd_bidpthdrvrs
 */
static void gen_stren_schd_bidpthdrvrs(struct net_t *np)
{
 int32 np_ti, drv_sbp_ti, tran_sbp_ti, drv_sbp_bi_ti, cint_ti, r1_ti;
 int32 srep, bi, tran_sbp_bi_ti, chg_ti, tevp_ti, tran_id;
 struct bblk_t *chg_bbp, *nochg_bbp;
 struct ctev_t *ctevp;
 struct traux_t *trap;

 np_ti = __ld_netadr_tn(np);
 trap = np->ntraux;
 if (np->nwid == 1) srep = SR_SSCAL; else srep = SR_SVEC;
 /* this is a call insn of other gened insns */
 /* xsp = __stload_mdrwire(np); sbp = (byte *) xsp->ap; */
 drv_sbp_ti = __emit_call_ldcomb_drvrs(np, srep, __inst_mod);
 /* sbp2 = &(np->ntraux->trnva.bp[inum*np->nwid]); */
 tran_sbp_ti = __emit_tran_addr(np_ti); 
 /* get the drv_apti[bi], tran_ti[bp_ti] */
 /* SJM 12/03/07 - now must use literal nlo amode as storeb src */
 for (bi = 0; bi < np->nwid; bi++)
  {
   cint_ti = __gen_cint_tn(bi);
   drv_sbp_bi_ti = __con_adradd_insn(SR_VEC, WBITS, drv_sbp_ti, bi);
   tran_sbp_bi_ti = __con_adradd_insn(SR_VEC, WBITS, tran_sbp_ti, bi);
   ctevp = np->ndel_ctevtab[bi];
   tevp_ti = __gen_ctevp_adr_tn(ctevp);

   tran_id = get_tran_id(trap, np->nwid, bi);
   ctevp->path_ndx = tran_id;
   chg_ti = __emit_stren_schd_bidpthdrvrs(np_ti, drv_sbp_bi_ti, 
     tran_sbp_bi_ti, cint_ti, tevp_ti);
   chg_bbp = __alloc_bblk(FALSE);
   nochg_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(nochg_bbp, chg_bbp, chg_ti);
   __start_bblk(chg_bbp);

   /* SJM 12/03/07 - now with new nlo amode, can emit a literal storeb */
   /* since tran is stren will be bp ptr so need index reg store */
   r1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NEWGVAL);
   __st_insn(I_STOREB, AM_REG, r1_ti, AM_NDXREG, tran_sbp_bi_ti);

   gen_tran_1bit(np, np_ti, bi, FALSE); 
   __emit_jmp(nochg_bbp);
   __start_bblk(nochg_bbp);
  }
}

/*
 * lower code for schedule non stren inout channel path dest. hard drivers 
 * and channel some bits may not have changed or need immediate assign 
 * and chan update
 */
static void gen_schd_bidpthdrvrs(struct net_t *np)
{
 int32 np_ti, drv_apti, tran_ti, cint_ti; 
 int32 srep, bi, chg_ti, tevp_ti, tran_id, new_gateval_ti;
 struct bblk_t *chg_bbp, *nochg_bbp;
 struct ctev_t *ctevp;
 struct traux_t *trap;
 
 np_ti = __ld_netadr_tn(np);
 trap = np->ntraux;
 if (np->nwid == 1) srep = SR_SCAL; else srep = SR_VEC;
 drv_apti = __emit_call_ldcomb_drvrs(np, srep, __inst_mod);
 for (bi = 0; bi < np->nwid; bi++)
  {
   cint_ti = __gen_cint_tn(bi);
   /* AIV LOOKATME - could do bsels here doing in wrapper for now */
   ctevp = np->ndel_ctevtab[bi];
   tevp_ti = __gen_ctevp_adr_tn(ctevp);

   tran_id = get_tran_id(trap, np->nwid, bi);
   ctevp->path_ndx = tran_id;
   tran_ti = __emit_tran_addr(np_ti); 
//AIV FIXME - these code is bad for scalars doing bsel of scalar????
   if (np->srep == SR_SCAL)
    {
     chg_ti = __emit_schd_scalar_bidpthdrvrs(np_ti, drv_apti, tran_ti, cint_ti, 
       tevp_ti);
    }
   else
    {
     chg_ti = __emit_schd_bidpthdrvrs(np_ti, drv_apti, tran_ti, cint_ti, 
       tevp_ti);
    }
   chg_bbp = __alloc_bblk(FALSE);
   nochg_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(nochg_bbp, chg_bbp, chg_ti);
   __start_bblk(chg_bbp);
//AIV FIXME - this is per instance - should go into idp area - leaving
//as a wrapper for now 
   /* AIV 12/19/11 - this was wrong for scalars cannot use the wrapper just */
   /* need to copy the byte in which is better anyway */
   if (np->srep == SR_SCAL)
    {
     new_gateval_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_NEWGVAL);
     __emit_copy(1, new_gateval_ti, tran_ti);
    }
   else __emit_store_bidpthdrvrs(np_ti, tran_ti, cint_ti);
   gen_tran_1bit(np, np_ti, bi, FALSE); 
   __emit_jmp(nochg_bbp);
   __start_bblk(nochg_bbp);
  }
}
 
/*
 * evaluate one tran channel bit - version for path dest. event 
 * so know always per inst form
 * just one bit part of all bits routine
 */
extern void __gen_tran_1net(struct net_t *np, int32 np_ti, int32 idp_saved) 
{
 int32 bi;
 int32 cint_ti, nchg_ti;
 int32 orig_chanid, base, ii, chanid;
 struct net_chg_t *ncp;
 struct vbinfo_t *vbip;
 struct traux_t *trap;
 struct chanrec_t *chanp;


 trap = np->ntraux;
 vbip = trap->vbitchans[0];
 chanp = &(__chantab[vbip->chan_id]);
 /* AIV 02/19/12 - if inout vectored handle as vectored - not per bit */
 if (chanp->chan_vectored)
  {
   gen_tran_1net_vectored(np, np_ti, idp_saved, chanp);
   return;
  }
 
 /* check if value has changed */
 for (bi = np->nwid - 1; bi >= 0; bi--) 
  {
   /* AIV 01/27/12 - if vector case it should first do the instance jump */
   /* table - just once then do each bit of the tran */
   /* cannot just call gen_tran_1bit - using the body of tran_1bit */
   /* but if vector now returns */
   /* gen_tran_1bit(np, np_ti, bi, idp_saved); */
   /* check if value has changed */
   vbip = trap->vbitchans[bi];
   cint_ti = __gen_cint_tn(bi);
   if (vbip == NULL)
    {
     ncp = NULL;
     if (np->n_isavec)
      {
       if (__net_chg_nd_store(np, bi, bi))
        {
         ncp = __gen_netchg_addr_tn(np, bi, bi, FALSE, &nchg_ti);
        }
      }
     else if (__net_chg_nd_store(np, -1, -1))
      {
       ncp = __gen_netchg_addr_tn(np, -1, -1, FALSE, &nchg_ti);
      }
  
     if (np->n_stren)
      {
       /* if don't need record nchg don't pass the nchg */
       if (ncp == NULL) __emit_eval_htran_stwire_1bit(np_ti, cint_ti);
       else __emit_eval_htran_stwire_1bit_nchg(np_ti, nchg_ti, cint_ti);
      }
     else
      {
       if (ncp == NULL) __emit_eval_htran_wire_1bit(np_ti, cint_ti);
       else __emit_eval_htran_wire_1bit_nchg(np_ti, nchg_ti, cint_ti);
      }
    }
    else
     {
      orig_chanid = vbip->chan_id;
      /* AIV 02/06/12 - need chanid init here */
      chanid = orig_chanid;
      /* if more than one instance scalar cannot do */
      if (__inst_mod->flatinum > 1 && np->nwid > 1)
       {
        chanid = -1;
       }
      else
       {
        for (ii = 1; ii < __inst_mod->flatinum; ii++)
         {
          base = ii*np->nwid;
          vbip = trap->vbitchans[base+bi];
          if (orig_chanid != vbip->chan_id)
           {
            chanid = -1;
            break;
           }
         }
       }

     gen_eval_tran_bits(np, trap, idp_saved, chanid, bi, TRUE, orig_chanid);
     return;
    }
  }
}
   
/*
 *
 */
static void gen_tran_1net_vectored(struct net_t *np, int32 np_ti, 
 int32 idp_saved, struct chanrec_t *chanp)
{
 if (chanp->chtyp == TRPROC_STBID) 
  {
   __emit_eval_tran_stbidchan_vectored_assign(np_ti);
  }
 else if (chanp->chtyp == TRPROC_BID)
  {
   __emit_eval_tran_bidchan_vectored_assign(np_ti);
  }
 else __misc_terr(__FILE__, __LINE__);
}

/*
 * evaluate one tran channel bit - version for path dest. event 
 * so know always per inst form
 * just one bit part of all bits routine
 */
static void gen_tran_1bit(struct net_t *np, int32 np_ti, int32 bi, 
 int32 idp_saved) 
{
 int32 cint_ti, nchg_ti;
 int32 orig_chanid, base, ii, chanid;
 struct net_chg_t *ncp;
 struct vbinfo_t *vbip;
 struct traux_t *trap;

 trap = np->ntraux;
 /* check if value has changed */
 vbip = trap->vbitchans[bi];
 cint_ti = __gen_cint_tn(bi);
 if (vbip == NULL)
  {
   ncp = NULL;
   if (np->n_isavec)
    {
     if (__net_chg_nd_store(np, bi, bi))
      {
       ncp = __gen_netchg_addr_tn(np, bi, bi, FALSE, &nchg_ti);
      }
    }
   else if (__net_chg_nd_store(np, -1, -1))
    {
     ncp = __gen_netchg_addr_tn(np, -1, -1, FALSE, &nchg_ti);
    }

//AIV FIXME - decompose these into the above scalar, force, N_TRIREG, etc
//see the wrapper code for these, too many if stmts
   if (np->n_stren)
    {
     /* if don't need record nchg don't pass the nchg */
     if (ncp == NULL) __emit_eval_htran_stwire_1bit(np_ti, cint_ti);
     else __emit_eval_htran_stwire_1bit_nchg(np_ti, nchg_ti, cint_ti);
    }
   else
    {
     if (ncp == NULL) __emit_eval_htran_wire_1bit(np_ti, cint_ti);
     else __emit_eval_htran_wire_1bit_nchg(np_ti, nchg_ti, cint_ti);
    }
  }
 else
  {
   orig_chanid = vbip->chan_id;
   chanid = orig_chanid;
   for (ii = 1; ii < __inst_mod->flatinum; ii++)
    {
     base = ii*np->nwid;
     vbip = trap->vbitchans[base+bi];
     if (orig_chanid != vbip->chan_id)
      {
       chanid = -1;
       break;
      }
    }

   gen_eval_tran_bits(np, trap, idp_saved, chanid, bi, FALSE, orig_chanid);
  }
}

/*
 *
 */
static void gen_eval_tran_bits(struct net_t *np, struct traux_t *trap,
 int32 idp_saved, int32 chanid, int32 bi, int32 do_all_bits, int32 orig_chanid)
{
 struct vbinfo_t *vbip;
 int32 bi2;

 /* if chanid == -1 do the peri case */
 if (chanid == -1) 
  {
   gen_peri_chan_no_vtxs(np, trap, idp_saved, bi, do_all_bits);
  }
 else
  {
   if (!do_all_bits)
    {
     gen_1inst_tran_chan_no_vtxs(np, orig_chanid, idp_saved, bi);
    }
   else
    {
     /* if vector do all the bits */
     for (bi2 = bi; bi2 >= 0; bi2--)
      {
       vbip = trap->vbitchans[bi2];

       /* DBG remove -- */
       if (vbip == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       if (gen_1inst_tran_chan_no_vtxs(np, vbip->chan_id, idp_saved, bi2))
        return;
      }
    }
  }
}

/*
 * for one stren bid only per bit same wire type tran channel
 * combine all nodes into one stren value using chan rec list
 * - multiple instance case
 */
static void gen_peri_chan_no_vtxs(struct net_t *np, struct traux_t *trap, 
 int32 idp_saved, int32 bi, int32 do_all_bits)
{
 int32 ii, base, ninsts, inum_ti, to_bi, bi2, need_jmptab;
 struct bblk_t *after_bbp;
 struct bblk_t **jmp_bbtab;
 struct vbinfo_t *vbip;
 struct chanrec_t *chanp;

 need_jmptab = FALSE;
 /* AIV 01/30/12 - if all of these have no vertex there is no need for */
 /* the jump table  - if (chanp->chan_no_vtxs) uses wrapper */
 for (ii = 0; ii < __inst_mod->flatinum; ii++)
  {
   for (bi2 = 0; bi2 < np->nwid; bi2++)
    {
     base = ii*np->nwid;
     vbip = trap->vbitchans[base+bi2];
     chanp = &(__chantab[vbip->chan_id]);
     if (chanp->chan_no_vtxs) 
      {
       need_jmptab = TRUE;
       goto need_jmptab;
      }
     else need_jmptab = FALSE;
    }
  }

need_jmptab:

 ninsts = __inst_mod->flatinum;
 if (need_jmptab)
  {
   //AIV FIXME - this should exploit the fact that its inst is known
   /* AIV 11/09/07 - notice cannot use __ndxjmp_bbtab here because */
   /* its usage would be nested from  gen_np_mdprt_insns */
   jmp_bbtab = (struct bblk_t **) __my_malloc(ninsts*sizeof(struct bblk_t *)); 
   for (ii = 0; ii < __inst_mod->flatinum; ii++)
    {
     jmp_bbtab[ii] = __alloc_bblk(FALSE);
    }

   inum_ti = __emit_inum();
   __emit_ndx_jmp(inum_ti, jmp_bbtab, ninsts);

   after_bbp = __alloc_bblk(FALSE);
  }

 for (ii = 0; ii < __inst_mod->flatinum; ii++)
  {
   if (need_jmptab) __start_bblk(jmp_bbtab[ii]);

   /* AIV 01/27/12 - if vector case it should first do the instance jump */
   /* table - just once then do each bit of the tran */
   if (do_all_bits) to_bi = 0;
   else to_bi = bi;

   for (bi2 = bi; bi2 >= to_bi; bi2--)
    {
     base = ii*np->nwid;
     vbip = trap->vbitchans[base+bi2];

     chanp = &(__chantab[vbip->chan_id]);
     /* DBG remove -- */
     if (!need_jmptab && chanp->chan_no_vtxs) __misc_terr(__FILE__, __LINE__);
     if (vbip == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     if (gen_1inst_tran_chan_no_vtxs(np, vbip->chan_id, idp_saved, bi2))
      {
       if (!need_jmptab) return;
       /* ---- */
      }
    }
   if (need_jmptab) __emit_jmp(after_bbp);
  }

 if (need_jmptab) 
  {
   __start_bblk(after_bbp);
   __my_free(jmp_bbtab, ninsts*sizeof(struct bblk_t *)); 
  }
}

/*
 * AIV 01/30/12 - this was producing too much code so for modules with 
 * large number of instances it is a problem.  Now just use wrappers to
 * avoid producing too much code.
 */
static int32 gen_1inst_tran_chan_no_vtxs(struct net_t *np, int32 chanid, 
 int32 idp_saved, int32 bi)
{
 /* AIV 02/03/12 - I think the problem is really nested jump tables from */ 
 /* vectors - so scalars can use inline for more modules and not have */
 /* compile time issues */
 /* AIV 02/07/12 - if is the NPP wrapper just use additional wrappers */
 if (__cur_flowg->flowgtyp == FLOWG_NPP)
  {
   return(gen_1inst_tran_chan_no_vtxs_wrappers(np, chanid, idp_saved, bi));
  }
 else if (np->nwid == 1)
  {
   if (__inst_mod->flatinum > 100)
    {
     return(gen_1inst_tran_chan_no_vtxs_wrappers(np, chanid, idp_saved, bi));
    }
   else return(gen_1inst_tran_chan_no_vtxs_inline(np, chanid, idp_saved, bi));
  }
 else if (__inst_mod->flatinum > 10)
  {
   return(gen_1inst_tran_chan_no_vtxs_wrappers(np, chanid, idp_saved, bi));
  }
 else return(gen_1inst_tran_chan_no_vtxs_inline(np, chanid, idp_saved, bi));
}

/*
 * for one stren bid only per bit same wire type tran channel
 * combine all nodes into one stren value using chan rec list
 * - one instance case
 * - this routine _wrappers uses asl wrapper calls this is needed for large
 *   number of instances since it prodcues a lot of code
 */
static int32 gen_1inst_tran_chan_no_vtxs_wrappers(struct net_t *np, 
 int32 chanid, int32 idp_saved, int32 bi)
{
 int32 np_ti, cint_ti; 
 struct bidvtx_t *bidvtxp; 
 struct chanrec_t *chanp;

 chanp = &(__chantab[chanid]);
 if (chanp->chan_no_vtxs)
  {
   bidvtxp = &(chanp->bid_vtxtab[0]);
   /* non-strength case */
   cint_ti = __gen_cint_tn(chanid);
   if (chanp->chtyp == TRPROC_BID) 
    {
     /* if not all scalar pass both an ab value and a scalar value */
     __emit_eval_tran_bidchan_1bit_assign(cint_ti);
    }
   else 
    {
     /* strength case */
     __emit_eval_tran_stbidchan_1bit_assign(cint_ti);
    }
  }
 else 
  {
   np_ti = __ld_netadr_tn(np);
   /* AIV 01/30/12 - if vector do not pass per bit just pass net */
   if (np->n_isavec) __emit_eval_tran_drvr_vector(np_ti);
   else
    {
     cint_ti = __gen_cint_tn(bi);
     //AIV FIXME - uses net changes
     __emit_eval_tran_drvr_1bit(np_ti, cint_ti);
    }
   /* return TRUE means no handling per bit */
   return(TRUE);
  }
 return(FALSE);
}

/*
 * for one stren bid only per bit same wire type tran channel
 * combine all nodes into one stren value using chan rec list
 * - one instance case
 * - inlined code version
 */
static int32 gen_1inst_tran_chan_no_vtxs_inline(struct net_t *np, int32 chanid, 
 int32 idp_saved, int32 bi)
{
 int32 count, scalar_count, aval_ti, bval_ti, np_ti; 
 int32 vi, cint_ti, bpart_ti, sval_ti, abval_ti;
 struct bidvtx_t *bidvtxp; 
 struct chanrec_t *chanp;

 chanp = &(__chantab[chanid]);
 if (chanp->chan_no_vtxs)
  {
   count = 0;
   scalar_count = 0;

   /* count the number of scalar vertices */
   /* if not all assigns are of the same type (scalar/vec) then a conversion */
   /* is done on this top level to avoid lower multiple conversion */
   bidvtxp = &(chanp->bid_vtxtab[0]);
   for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
    {
     np = bidvtxp->vnp;
     if (!np->n_isavec) scalar_count++;
     count++;
    }

   abval_ti = -1;
   sval_ti = -1;
   /* non-strength case */
   if (chanp->chtyp == TRPROC_BID) 
    {
     /* if not all scalar pass both an ab value and a scalar value */
     if (scalar_count != count)
      {
       cint_ti = __gen_cint_tn(chanid);
       aval_ti = __emit_eval_tran_bidchan_1bit(cint_ti);
       abval_ti = __gen_tn(SR_VEC, 1);
       __emit_copy(WRDBYTES, aval_ti, abval_ti);
       bpart_ti = __con_adradd_insn(SR_VEC, WBITS, abval_ti, WRDBYTES);
       /* AIV BEWARE - machine dependent - */
       /* returning the bpart in ecx and then making one ab value */
       bval_ti = __emit_bpart_of_tran();
       __emit_copy(WRDBYTES, bval_ti, bpart_ti);
       /* if not assigning all vector values convert to a scalar */
       if (scalar_count != 0)
        {
         /* AIV 08/24/10 - if 2state need to do conversion here */
         if (np->n_2state) 
          {
           sval_ti = __gen_cnvt_ab_vec_to_scalar_2state(abval_ti);
          }
         else sval_ti = __gen_cnvt_ab_vec_to_scalar(abval_ti);
        }
       gen_tran_assign_to_vertices(chanp, abval_ti, sval_ti, idp_saved, FALSE);
      }
     else 
      {
       /* scalar - wrapper returns scalar */
       cint_ti = __gen_cint_tn(chanid);
       sval_ti = __emit_eval_tran_scalar_bidchan_1bit(cint_ti);
       /* all assigned bits are known to be scalar */
       /* AIV 08/24/10 - if 2state need to do conversion here */
       if (np->n_2state) sval_ti = __gen_cnvt_ab_vec_to_scalar_2state(sval_ti);
       gen_tran_assign_to_vertices(chanp, -1, sval_ti, idp_saved, FALSE);
      }
    }
   else 
    {
     /* strength case */
     cint_ti = __gen_cint_tn(chanid);
     sval_ti = __emit_eval_tran_stbidchan_1bit(cint_ti);
     /* if all assigns are not scalar do one time conversion into ab value */
     if (scalar_count != count)
      {
       abval_ti = __gen_cnvt_srep_ifneeded(sval_ti, SR_SVEC, 1, FALSE, FALSE, 
         FALSE);
      }
     gen_tran_assign_to_vertices(chanp, abval_ti, sval_ti, idp_saved, TRUE);
    }
  }
 else 
  {
   np_ti = __ld_netadr_tn(np);
   /* AIV 01/30/12 - if vector do not pass per bit just pass net */
   if (np->n_isavec) __emit_eval_tran_drvr_vector(np_ti);
   else
    {
     cint_ti = __gen_cint_tn(bi);
     //AIV FIXME - uses net changes
     __emit_eval_tran_drvr_1bit(np_ti, cint_ti);
    }
   /* return TRUE means no handling per bit */
   return(TRUE);
  }
 return(FALSE);
}
          
/*
 * assign a value to each of the tran channels vertices
 */
static void gen_tran_assign_to_vertices(struct chanrec_t *chanp, 
 int32 abval_ti, int32 sval_ti, int32 idp_saved, int32 is_stren)
{
 struct net_t *np;
 struct bidvtx_t *bidvtxp; 
 struct bblk_t *qc_active_bbp, *not_active_bbp;
 int32 vi, qc_ti, np_ti, cint_ti, bi, save_idp_ti;
 struct mod_t *in_mdp;
 struct itree_t *itp, *last_itp;
 int32 const_idp_ti;

 save_idp_ti = -1;
 last_itp = NULL;
 bidvtxp = &(chanp->bid_vtxtab[0]);
 if (!idp_saved)
  {
   save_idp_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, IDP_REG);
  }
 for (vi = 0; vi < chanp->numvtxs; vi++, bidvtxp++)
  {
   np = bidvtxp->vnp;
//AIV FIXME - np_ti needs to move to the module __inst_mod it is in
   __get_nets_containing_sy(np, &(in_mdp));
   __push_itstk(in_mdp->moditps[0]);
   bi = bidvtxp->vi1;
   cint_ti = __gen_cint_tn(bi);
//AIV always need to set idp??????
//AIV IDP FIXME CVC
   itp = bidvtxp->bidvtx_itp;
   if (itp != last_itp)
    {
     const_idp_ti = __gen_mdata_value(itp);
     __memloc_emit_set_idp(const_idp_ti);
    }

   if (!np->n_isavec)
    {
     /*  notice this code handels the np->frc_assgn_allocated case */
     /* DBG remove -- */
     if (bi != -1) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     __gen_proc_id_assign(np, sval_ti);
    }
   else if (np->frc_assgn_allocated)
    {
     qc_active_bbp = __alloc_bblk(FALSE);
     not_active_bbp = __alloc_bblk(FALSE);
     np_ti = __ld_netadr_tn(np);
     
     qc_ti = __emit_qc_active(np_ti, cint_ti);
     __emit_jmp_0(not_active_bbp, qc_active_bbp, qc_ti);
     __start_bblk(not_active_bbp);

     /* DBG remove -- */
     if (abval_ti == -1) __misc_terr(__FILE__, __LINE__);
     /* -- */
     gen_assign_1tran_bit(np, bi, abval_ti, is_stren);
     __start_bblk(qc_active_bbp);
    }
   else
    {
     /* if more than half are scalar this will be scalar need to turn into */
     /* ab value */
     /* DBG remove -- */
     if (abval_ti == -1) __misc_terr(__FILE__, __LINE__);
     /* -- */
     gen_assign_1tran_bit(np, bi, abval_ti, is_stren);
    }
   __pop_itstk();
  }
 if (!idp_saved)
  {
   __memloc_emit_set_idp(save_idp_ti);
  }
}

/*
 * routine to assign 1 non stren bid only channel tran bit
 */
static void gen_assign_1tran_bit(struct net_t *np, int32 bi, int32 val_ti, 
 int32 is_stren)
{
 int32 addr_ti, cint_ti, sb_bi_ti, new_sval_ti;
 int32 r1_ti, r2_ti, nchg_ti;
 struct bblk_t *hiz_bbp, *not_hiz_bbp, *store_bbp, *chg_bbp, *no_chg_bbp;
 struct net_chg_t *ncp;

 /* DBG remove -- */
 if (!np->n_isavec) __misc_terr(__FILE__, __LINE__);
 /* --- */

 //sbp2[bind] = (byte) sbv;
 addr_ti = __ldvar_addr(np, NULL);
 if (is_stren)
  {
   cint_ti = __gen_cint_tn(bi);
   sb_bi_ti = __con_adradd_insn(SR_SVEC, 1, addr_ti, bi);
   if (np->ntyp == N_TRIREG)
    {
     /* if trireg must do the following at runtime
       if (sbv == ST_HIZ)
       sbv = (byte) ((sbp2[bind] & 3) | __cap_to_stren[np->n_capsiz]);
      */
     hiz_bbp = __alloc_bblk(FALSE);
     not_hiz_bbp = __alloc_bblk(FALSE);
     store_bbp = __alloc_bblk(FALSE);
     cint_ti = __gen_cint_tn(ST_HIZ);
     __emit_jmp_eq(hiz_bbp, not_hiz_bbp, cint_ti, val_ti);
     __start_bblk(hiz_bbp);
     
     /* sbv = (byte) ((sbp2[bind] & 3) | __cap_to_stren[np->n_capsiz]) */
     cint_ti = __gen_cint_tn(3);
     r1_ti = __emit_mask_and(sb_bi_ti, cint_ti);  
     cint_ti = __gen_cint_tn(__cap_to_stren[np->n_capsiz]);
     r2_ti = __emit_mask_or(r1_ti, cint_ti);  
     new_sval_ti = __gen_tn(SR_SVEC, 1);
     __emit_copy(1, r2_ti, new_sval_ti);
     __emit_jmp(store_bbp);

     __start_bblk(not_hiz_bbp);
     __emit_copy(1, sb_bi_ti, new_sval_ti);
     __emit_jmp(store_bbp);

     __start_bblk(store_bbp);
    }
   else new_sval_ti = val_ti;

   ncp = NULL;
   if (np->n_isavec)
    {
     if (__net_chg_nd_store(np, bi, bi))
      {
       ncp = __gen_netchg_addr_tn(np, bi, bi, FALSE, &nchg_ti);
      }
    }
   else if (__net_chg_nd_store(np, -1, -1))
    {
     ncp = __gen_netchg_addr_tn(np, -1, -1, FALSE, &nchg_ti);
    }

   if (ncp != NULL)
    {
     no_chg_bbp = __alloc_bblk(FALSE);
     chg_bbp = __alloc_bblk(FALSE);

     __emit_jmp_byte_eq(no_chg_bbp, chg_bbp, sb_bi_ti, new_sval_ti);

     __start_bblk(chg_bbp);
     __emit_copy(1, new_sval_ti, sb_bi_ti);
//AIV FIXME - what about dumpvars???????????
//#define record_sel_nchg_(np, i1, i2) 
//AIV LOOKATME - maybe shouldn't inline produces lots of code which slows
//down the register alloc
     gen_1net_wakeup_insns(np, bi, bi, FALSE, FALSE);
     __gen_record_const_nchg(np, bi, bi, no_chg_bbp);

     __start_bblk(no_chg_bbp);
    }
   else __emit_copy(1, new_sval_ti, sb_bi_ti);
  }
 else
  {
   /* non-strength - this handles change record if needed */
   __gen_lhsbsel_const(np, addr_ti, bi, val_ti);
  }
}

/*
 * same as __xmrget_refgrp_to_targ - this one has different pushing
 * the regular is done at compile time this one at run time
 */
extern void __xmrpush_refgrp_to_targ_compiletime(struct gref_t *grp)
{
 struct itree_t *itp;

 /* rooted case */
 if (grp->is_rooted)
  {
   __push_itstk(grp->targu.targitp);
   return;
  }
 /* upward relative case - requires linear list search */
 if (grp->upwards_rel)
  {
   __push_itstk(grp->targu.uprel_itps[__inum]);
   return;
  }
 /* normal downward instance path case */
 itp = __find_unrt_targitp(grp, __inst_ptr, 0);
 __push_itstk(itp);
} 

/*
 * gen vinsns for declarative schedule to fi>1 net 
 *
 * caller set correct lhs expr net itree context before here
 * no lhs expr here and only for fi>1 cases
 */
static void gen_sched_1mdrwire(struct net_t *np, int32 rhs_ti)
{
 if (np->n_stren) gen_stren_schd_allofwire(np, rhs_ti, np->nwid); 
 else gen_schd_allofwire(np, rhs_ti, np->nwid); 
}

/*
 * gen insns for declarative assign to stren net where know rhs fld
 * exactly matches lhs in width (stren form)
 *
 * this differs from 1 decl assign in that there is no lhs expr
 * for both ID and XMR, caller must emit if XMR itree push/pop
 */
static void gen_assign_1stmdrwire(struct net_t *np, int32 sbp_ti, 
 int32 ri1, int32 ri2)
{
 int32 qcaf_active_ti, lhs_sbpti, np_ti, pselwid; 
 int32 lhs_adr_ti, sbp_adr_ti;
 struct bblk_t *wfrc_bbp, *assgn_bbp;

 wfrc_bbp = NULL;
 if (np->frc_assgn_allocated) 
  {
   wfrc_bbp = __alloc_bblk(FALSE);
   assgn_bbp = __alloc_bblk(FALSE);

   np_ti = __ld_netadr_tn(np);
   if (!np->n_isavec)
    {
     qcaf_active_ti = __emit_scalar_wire_inhibit(np_ti);
    }
   else
    { 
     qcaf_active_ti = __emit_stren_correct_frc(np_ti, sbp_ti);
    }
   __emit_jmp_0(wfrc_bbp, assgn_bbp, qcaf_active_ti);
   __start_bblk(assgn_bbp);
  }

 /* no offset and know itree loc right - caller may have pushed */
 lhs_sbpti = gen_get_stwire_addr(np, NULL);
 /* no delay form trireg wire, correct for same value cap. strength */
 if (np->ntyp == N_TRIREG)
  {
   __emit_adjust_trireg(sbp_ti, lhs_sbpti, np->nwid, 
     __cap_to_stren[np->n_capsiz]);
  }

 /* AIV 09/27/07 - need to pass lhs change range */
 if (__net_chg_nd_store(np, ri1, ri2))
  {
   /* AIV 10/10/07 - need to pass the width of the actual vector chg part */
   /* AIV 12/10/07 - this was doing entire net for selected ranges */
   if (ri1 == -1)
    {
     /* entire net range */
     __gen_chg_st_svecval(np, lhs_sbpti, sbp_ti, -1, np->nwid);
    }
   else
    {
     /* part selected of net range */
     pselwid = ri1 - ri2 + 1; 
     sbp_adr_ti = __con_adradd_insn(SR_SVEC, pselwid, sbp_ti, ri2);
     lhs_adr_ti = __con_adradd_insn(SR_SVEC, pselwid, lhs_sbpti, ri2);
     __gen_chg_st_svecval(np, lhs_adr_ti, sbp_adr_ti, ri2, pselwid);
    }
  }
 else
  {
   __emit_copy(np->nwid, sbp_ti, lhs_sbpti);
  }
 if (np->frc_assgn_allocated) __start_bblk(wfrc_bbp);
}

/*
 * gen insns for declarative assign to net where know rhs fld
 * exactly matches lhs in width (non stren form)
 *
 * this differs from 1 decl assign in that there is no lhs expr
 * for both ID and XMR, caller must emit if XMR itree push/pop
 */
static void gen_assign_1mdrwire(struct net_t *np, int32 rhs_apti, 
 int32 ri1, int32 ri2)
{
 int32 qcaf_active_ti, rhs2_apti, np_ti, addr_ti, pselwid;
 struct bblk_t *wfrc_bbp, *assgn_bbp;

 wfrc_bbp = assgn_bbp = NULL;
 if (np->frc_assgn_allocated) 
  {
   wfrc_bbp = __alloc_bblk(FALSE);
   assgn_bbp = __alloc_bblk(FALSE);

   np_ti = __ld_netadr_tn(np);
   if (!np->n_isavec)
    {
     qcaf_active_ti = __emit_scalar_wire_inhibit(np_ti);
     rhs2_apti = rhs_apti;
    }
   else
    { 
     rhs2_apti = __gen_tn(SR_VEC, np->nwid);
     if (np->n_2state)
      {
       __emit_copy(WRDBYTES*wlen_(np->nwid), rhs_apti, rhs2_apti);
      }
     else __emit_copy(2*WRDBYTES*wlen_(np->nwid), rhs_apti, rhs2_apti);

     /* AIV 01/23/06 - was passing np->nwid returns T/F so size is one word */
     qcaf_active_ti = __emit_correct_frc(np_ti, rhs2_apti);
    }
   __emit_jmp_0(wfrc_bbp, assgn_bbp, qcaf_active_ti);
   __start_bblk(assgn_bbp);
  }
 else rhs2_apti = rhs_apti;



 /* non stren can't be tri reg */
 addr_ti = __ldvar_addr(np, NULL);
 /* AIV 09/07/07 - was recording everytime - record not always needed */
 /* AIV 09/27/07 - need to pass lhs change range */
 if (__net_chg_nd_store(np, ri1, ri2)) 
  {
   /* AIV 12/11/07 - need to select the proper range for the change */
   if (ri1 == -1)
    {
     rhs2_apti = __gen_cnvt_srep_ifneeded(rhs2_apti, np->srep, np->nwid,
      __tntab[rhs2_apti].t_signed, FALSE, TRUE);
     __gen_chg_st_val(np, addr_ti, rhs2_apti);
    }
   else
    {
     /* if same range is one bit just do bsel otherwise psel */
     /* AIV LOOKATME - if drv known to be always of select range make mfi */
     /* only work on one bit/psel range */
     if (ri1 == ri2)
      {
       /* select the bit from the rhs accum to compare to the rhs bit */
       rhs2_apti = __gen_rhs_bsel_const(np, rhs2_apti, ri1); 
       __gen_lhsbsel_const(np, addr_ti, ri1, rhs2_apti);
      }
     else
      {
       pselwid = ri1 - ri2 + 1;
       /* select the psel from the rhs accum to compare to the lhs psel */
       rhs2_apti = __gen_fradr_rhs_psel(np->srep, rhs2_apti, pselwid, 
        ri2 + pselwid - 1, ri2);
       __gen_chg_lhspsel(np, pselwid, addr_ti, rhs2_apti, ri2, pselwid, ri1);
      }
    }
  }
 else 
  {
   rhs2_apti = __gen_cnvt_srep_ifneeded(rhs2_apti, np->srep, np->nwid,
    __tntab[rhs2_apti].t_signed, FALSE, TRUE);
   __gen_st_val(np, addr_ti, rhs2_apti);
  }

 if (wfrc_bbp != NULL) __start_bblk(wfrc_bbp);
}

/*
 * gen insns for lhs concat where can't be (not) changed to PB form
 * lhs non stren case - know rhs also not stren
 *
 * always called for port lhs concats, but can't be used for conta
 * delayed assign since lhs decomposition different 
 *
 * runs in lhs itree context set by caller
 * must be passed a/b sr vec form
 */
static void gen_decl_lhscat(struct expr_t *lhsx, int32 rhs_ti)
{
 int32 t1_apti, nels, lxi, catxlen, bi2, srtyp; 
 int32 rhs2_ti, lhswid, last_lowbi, is_2state;
 struct expr_t *catlhsx, **lhsxtab;
 
 /* AIV REMOVEME SJM FIX */
 if (rhs_ti == -1) __misc_terr(__FILE__, __LINE__);
 /* ------- */
 
 lhswid = lhsx->szu.xclen;
 /* following interpreter, rhs widened to size of lhs if needed */
 /* if narrower, some just won't be selected */
 is_2state = __tmp_is_2state(rhs_ti);
 if (is_2state)
  {
   if (__get_tnwid(rhs_ti) < lhswid || __tntab[rhs_ti].srtyp != SR_BIT2S)
    {
     rhs2_ti = __gen_cnvt_srep_ifneeded(rhs_ti, SR_BIT2S, lhswid, FALSE,
      FALSE, FALSE);
    }
   else rhs2_ti = rhs_ti;
   srtyp = SR_BIT2S;
  }
 else if (__get_tnwid(rhs_ti) < lhswid || __tntab[rhs_ti].srtyp != SR_VEC)
  {
   rhs2_ti = __gen_cnvt_srep_ifneeded(rhs_ti, SR_VEC, lhswid, FALSE,
    FALSE, FALSE);
   srtyp = SR_VEC;
  }
 else 
  {
   rhs2_ti = rhs_ti;
   srtyp = SR_VEC;
  }

 /* build the low to high decomposed lhs concat table */
 nels = __cnt_cat_size(lhsx);
 lhsxtab = (struct expr_t **) __my_malloc(nels*sizeof(struct expr_t *));
 lxi = nels - 1;
 /* fill expr tab in reverse order */
 catlhsx = lhsx->ru.x;
 for (; catlhsx != NULL; catlhsx = catlhsx->ru.x, lxi--)
  { lhsxtab[lxi] = catlhsx->lu.x; }

 /* SJM 08/16/05 - now mimic interpreter high to low so need last low bit */
 /* know rhs non stren and exactly needed width */
 /* bi2 is low bit advanced each time at end of loop */
 last_lowbi = lhsx->szu.xclen; 
 for (lxi = nels - 1; lxi >= 0; lxi--)
  {
   /* gen vinsns to sel from rhs tmp into width that matches lhs cat el */
   catlhsx = lhsxtab[lxi];
   catxlen = catlhsx->szu.xclen;
   /* range within lhs is [bi1:bi2] */
   bi2 = last_lowbi - catxlen;
   last_lowbi = bi2;

   /* AIV 08/15/06 - was passing the wrong width rhslen should be catxlen */
   /* AIV LOOKATME - optimize 1 bit to bsel ?????? */
   t1_apti = __gen_fradr_rhs_psel(srtyp, rhs2_ti, catxlen, bi2 + catxlen - 1, 
    bi2); 

   /* know rhs tmp has right stren added and stren match cat lhs stren */
   /* case 2: need path dest/wdel schedule of assign */  
   /* AIV 03/07/12 - apparently this needs to use lhsx to check for the delay */ 
   /* not catlhsx - since the bit is only set for the actual conta lhsx */
  if (lhsx->lhsx_ndel) 
   {
    gen_sched_conta_assign(catlhsx, t1_apti);
   }
  else
   {
    /* case 3: no delay immediate conta - stren already added */
    /* and handles lhs xmr */
    gen_conta_assgn(catlhsx, t1_apti);
   }
  }
 /* AIV 01/23/07 - missing free lhsxtab */
 __my_free(lhsxtab, nels*sizeof(struct expr_t *));
}

/*
 * gen insns for lhs stren concat where can't be (not) changed to PB form
 * know rhs and lhs both stren and exactly same width
 *
 * always called for port lhs concats, but can't be used for conta
 * delayed assign since lhs decomposition different 
 *
 * runs in lhs itree context set by caller
 */
static void gen_stren_decl_lhscat(struct expr_t *lhsx, int32 rhsadr_ti)
{
 int32 nels, lxi, catxlen, bi2, rhswid, last_lowbi;
 int32 sbp_ti;
 struct expr_t *catlhsx, **lhsxtab;

 rhswid = __get_tnwid(rhsadr_ti);
 /* DBG remove -- */
 if (rhswid != lhsx->szu.xclen) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* build the low to high decomposed lhs concat table */
 nels = __cnt_cat_size(lhsx);
 lhsxtab = (struct expr_t **) __my_malloc(nels*sizeof(struct expr_t *));
 lxi = nels - 1;
 /* fill expr tab in reverse order */
 catlhsx = lhsx->ru.x;
 for (; catlhsx != NULL; catlhsx = catlhsx->ru.x, lxi--)
  { lhsxtab[lxi] = catlhsx->lu.x; }

 /* SJM 08/16/05 - now mimic interpreter high to low so need last low bit */
 /* know rhs non stren and exactly needed width */
 /* bi2 is low bit advanced each time at end of loop */
 last_lowbi = lhsx->szu.xclen; 
 for (lxi = nels - 1; lxi >= 0; lxi--)
  {
   /* gen vinsns to sel from rhs tmp into width that matches lhs cat el */
   catlhsx = lhsxtab[lxi];
   catxlen = catlhsx->szu.xclen;
   /* range within lhs is [bi1:bi2] */
   bi2 = last_lowbi - catxlen;
   last_lowbi = bi2;

   /* if rhswid 1 bit, must be stren scalar so no need for addr add */
   if (rhswid != 1)
    {
     /* for very rare rhs 1 bit word32 tab, still psel from the 1 bit */
     /* into a 1 bit a/b tmp */
     /* AIV 10/12/06 - needs to be svec here */
     sbp_ti = __con_adradd_insn(SR_SVEC, rhswid, rhsadr_ti, bi2);
    }
   else sbp_ti = rhsadr_ti;

   /* know rhs tmp has right stren added and stren match cat lhs stren */
   /* case 2: need path dest/wdel schedule of assign */  
   /* AIV 03/07/12 - apparently this needs to use lhsx to check for the delay */ 
   /* not catlhsx - since the bit is only set for the actual conta lhsx */
   if (lhsx->lhsx_ndel) gen_sched_conta_assign(catlhsx, sbp_ti);
   else
    {
     /* case 3: no delay immediate conta - stren already added */
     /* and handles lhs xmr */
     gen_stren_conta_assgn(catlhsx, sbp_ti);
    }
  }
 /* AIV 01/23/07 - missing free lhsxtab */
 __my_free(lhsxtab, nels*sizeof(struct expr_t *));
}

/*
 * gen insns for declarative stren assign to lvalue
 * rhs width must match lhs - any needed stren added must be done before here
 *
 * called conta assign to match interpreter but really any declarative 
 * including port assigns since rhs stren must be added before this
 * routine can be called
 */
static void gen_stren_conta_assgn(struct expr_t *lhsx, int32 rhs_apti)
{
 int32 bi, biti_ti, sbp_ti, sbp2_ti;
 int32 save_idp_ti, needs_chg, ri1, ri2;
 struct bblk_t *outofrng_bbp;
 struct net_t *np;
 struct expr_t *idndp;
 struct gref_t *grp;

 save_idp_ti = -1;
 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;

 outofrng_bbp = NULL;
 bi = biti_ti = -1;
 /* adjust rhs by adding stren if needed */
 switch (lhsx->optyp) {
  case GLBREF:
   if (np->frc_assgn_allocated || __net_chg_nd_store(np, -1, -1))
    {
     rhs_apti = gen_chgtorefgrp(lhsx, &save_idp_ti, rhs_apti);

     gen_conta_var_assign(np, rhs_apti);

     __gen_restore_idp(save_idp_ti);
     __pop_itstk();
    }
   /* for simple assign - xmr's handled by accessing right inum and compile */
   /* time inst mod */
   else gen_conta_simple_var_assign(np, idndp, rhs_apti);
   break; 
  case ID:
   if (np->frc_assgn_allocated || __net_chg_nd_store(np, -1, -1))
    {
     gen_conta_var_assign(np, rhs_apti);
    }
   else gen_conta_simple_var_assign(np, idndp, rhs_apti);
   break;
  case LSB:
   /* check if bit select is constant */
   if (lhsx->ru.x->optyp == NUMBER)
    {
     bi = __get_comp_num_ndx(lhsx->ru.x);
     needs_chg = __net_chg_nd_store(np, bi, bi);
    }
   else 
    {
     outofrng_bbp = __alloc_bblk(FALSE);
     biti_ti = __gen_comp_ndx(np, lhsx->ru.x, outofrng_bbp, FALSE);
     needs_chg = __net_chg_nd_store(np, -1, -1);
    }
 

   if (np->frc_assgn_allocated || needs_chg)
    {
     if (idndp->optyp == GLBREF) 
      {
       rhs_apti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_apti);
      }
     if (bi != -1)
      {
       gen_conta_stren_bit_assign(np, bi, rhs_apti, TRUE);
      }
     else gen_conta_stren_bit_assign(np, biti_ti, rhs_apti, FALSE);

     if (idndp->optyp == GLBREF)
      { 
       __gen_restore_idp(save_idp_ti);
       __pop_itstk(); 
      }
     if (bi == -1) __start_bblk(outofrng_bbp);
    }
   else
    {
     /* since need address can't use get st bsel offset */
     if (idndp->optyp == ID) grp = NULL; else grp = idndp->ru.grp;
     sbp2_ti = gen_get_stwire_addr(np, grp);
     /* handle constant case */
     if (bi != -1)
      {
       sbp_ti = __con_adradd_insn(SR_SVEC, idndp->szu.xclen, sbp2_ti, bi);
      }
     else
      {
       sbp_ti = __var_adradd_insn(SR_SVEC, idndp->szu.xclen, sbp2_ti,
        biti_ti);
      }

     /* DBG remove --- */
     if (!__any_stren_tn(rhs_apti)) __misc_terr(__FILE__, __LINE__);
     /* --- */
     __emit_copy(1, rhs_apti, sbp_ti);
    }
   break; 
  case PARTSEL:
   ri1 = (int32) __contab[lhsx->ru.x->lu.x->ru.xvi];
   ri2 = (int32) __contab[lhsx->ru.x->ru.x->ru.xvi];
   if (np->frc_assgn_allocated || __net_chg_nd_store(np, ri2, ri1))
    {
     if (idndp->optyp == GLBREF) 
      {
       rhs_apti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_apti);
      }
     gen_conta_stren_psel_assign(lhsx, rhs_apti);
     if (idndp->optyp == GLBREF)
      { 
       __gen_restore_idp(save_idp_ti);
       __pop_itstk(); 
      }
    }
   else 
    { 
     /* this gets right instance stren vec area base plus psel offset*/
     /* and always returns addr */
     sbp_ti = gen_access_stpsel(lhsx);

     /* DBG remove --- */
     if (!__any_stren_tn(rhs_apti)) __misc_terr(__FILE__, __LINE__);
     /* --- */
     __emit_copy(lhsx->szu.xclen, rhs_apti, sbp_ti);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * routine to gen change of itree context from ref to target (defined in)
 */
static int32 gen_chgtorefgrp(struct expr_t *ndp, int32 *save_idp_ti, 
 int32 rhs_apti) 
{
 int32 dup_rhs_apti;
 struct gref_t *grp;

 /* AIV 12/12/11 - may have to copy rhs to tmp storage prior to changing */
 /* idp area reg - just copy the value */
 dup_rhs_apti = -1;
 if (rhs_apti != -1)
  {
   if (__tntab[rhs_apti].tn_typ == TN_ADR)
    {
     dup_rhs_apti = __gen_duplicate_tmp(rhs_apti);
    }
   else dup_rhs_apti = rhs_apti;
  }
 grp = ndp->ru.grp; 
 /* SJM 01/25/06 - right module set in bbgen but will be wrong in x86gen */
 /* must also change to one at compile time */
 *save_idp_ti = __gen_ld_xmr_idp(grp);
 __xmrpush_refgrp_to_targ_compiletime(grp);
 return(dup_rhs_apti);
}

/*
 * gen conta bit assign (complex case - either change store or can be force)
 * stren case - know itree loc changed by caller if XMR
 */
static void gen_conta_stren_bit_assign(struct net_t *np, int32 bi,
 int32 rhs_sbpti, int32 is_const)
{
 int32 qcaf_active_ti, sbp_ti, sbp2_ti, np_ti, biti_ti; 
 int32 needs_chg;
 struct bblk_t *after_bbp, *assgn_bbp;

 after_bbp = NULL;
 if (is_const) biti_ti = __gen_cint_tn(bi);
 else biti_ti = bi;

 if (np->frc_assgn_allocated)
  {
   after_bbp = __alloc_bblk(FALSE);
   assgn_bbp = __alloc_bblk(FALSE);

   np_ti = __ld_netadr_tn(np);
   /* returns T if force active */
   qcaf_active_ti = __emit_bsel_wirfrc_inhibit(np_ti, biti_ti);
   __emit_jmp_0(after_bbp, assgn_bbp, qcaf_active_ti);
   __start_bblk(assgn_bbp);
  }

 /* DBG remove --- */
 if (!__any_stren_tn(rhs_sbpti)) __misc_terr(__FILE__, __LINE__);
 /* --- */

 sbp2_ti = gen_get_stwire_addr(np, NULL);
 /* SJM 11/30/07 - REDO? routine for const and var indices - need to sep */
 if (is_const)
  {
   sbp_ti = __con_adradd_insn(SR_SVEC, np->nwid, sbp2_ti, bi);
   needs_chg = __net_chg_nd_store(np, bi, bi);
  }
 else
  {
   sbp_ti = __var_adradd_insn(SR_SVEC, np->nwid, sbp2_ti, biti_ti);
   needs_chg = __net_chg_nd_store(np, -1, -1);
  }
 
 if (needs_chg)
  {
   /* SJM 07/18/05 - start index really is 0 index added to sbp ti */
   /* AIV 03/02/07 - constant case must base bit index - was passing 0 */
   if (is_const) __gen_chg_st_svecval(np, sbp_ti, rhs_sbpti, bi, 1);
   else __gen_chg_st_svecval(np, sbp_ti, rhs_sbpti, 0, 1);
  }
 else
  {
   __emit_copy(1, rhs_sbpti, sbp_ti);
  }

 if (np->frc_assgn_allocated) __start_bblk(after_bbp);
}

/*
 * gen stren conta lhs psel assign
 * (complex case - either change store or can be force)
 * know itree loc changed by caller if XMR above here
 */
static void gen_conta_stren_psel_assign(struct expr_t *lhsx, int32 rhs_sbpti)
{
 int32 ri1, ri2, pselwid, qcaf_active_ti, sbp_ti, sbp2_ti, np_ti;
 struct net_t *np;
 struct bblk_t *after_bbp, *assgn_bbp;

 ri1 = (int32) __contab[lhsx->ru.x->lu.x->ru.xvi];
 ri2 = (int32) __contab[lhsx->ru.x->ru.x->ru.xvi];
 np = lhsx->lu.x->lu.sy->el.enp;
 pselwid  = ri1 - ri2 + 1;
 
 after_bbp = NULL;
 if (np->frc_assgn_allocated)
  {
   after_bbp = __alloc_bblk(FALSE);
   assgn_bbp = __alloc_bblk(FALSE);

   sbp2_ti = __gen_tn(SR_SVEC, np->nwid);
   __emit_copy(np->nwid, rhs_sbpti, sbp2_ti);

   np_ti = __ld_netadr_tn(np);
   /* returns T if all bit forced */ 
   qcaf_active_ti = __emit_stren_psel_correct_frc(np_ti, sbp2_ti, ri1, ri2);

   __emit_jmp_0(after_bbp, assgn_bbp, qcaf_active_ti);
   __start_bblk(assgn_bbp);
  }

 /* DBG remove --- */
 if (!__any_stren_tn(rhs_sbpti)) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* caller must have set correct itree loc if XMR */
 sbp2_ti = gen_get_stwire_addr(np, NULL);
 /* AIV 12/10/07 - width is ony pselwid here not np->nwid */
 sbp_ti = __con_adradd_insn(SR_SVEC, np->nwid, sbp2_ti, ri2);

 if (__net_chg_nd_store(np, ri2, ri1))
  {
   __gen_chg_st_svecval(np, sbp_ti, rhs_sbpti, ri2, pselwid);
  }
 else
  {
   __emit_copy(pselwid, rhs_sbpti, sbp_ti);
  }

 if (np->frc_assgn_allocated) __start_bblk(after_bbp);
}

/*
 * gen change store svec value of section pselwid 
 * if lowbi is -1, emit record nchg else record select nchg
 *
 * one gen routine can handle vectors, psels, bsels and sscals since
 * just generating different vinss (copies)
 */
extern void __gen_chg_st_svecval(struct net_t *np, int32 lhs_apti,
 int32 rhs_apti, int32 lowbi, int32 pselwid)
{
 int32 cond_ti;
 struct bblk_t *skip_bbp, *chgstore_bbp;

 skip_bbp = __alloc_bblk(FALSE);
 chgstore_bbp = __alloc_bblk(FALSE);

 if (pselwid <= WRDBYTES)
  {
   __emit_narrow_byte_eq(pselwid, skip_bbp, chgstore_bbp, lhs_apti, rhs_apti);
  }
 else
  {
   cond_ti = __emit_bytecmp(pselwid, lhs_apti, rhs_apti);
   __emit_jmp_0(skip_bbp, chgstore_bbp, cond_ti); 
  }
 __start_bblk(chgstore_bbp);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(pselwid, rhs_apti, lhs_apti);

 if (lowbi == -1) __gen_record_const_nchg(np, -1, -1, skip_bbp);
 else __gen_record_const_nchg(np, lowbi + pselwid - 1, lowbi, skip_bbp);

 __start_bblk(skip_bbp);
}

/*
 * gen insns for declarative assign to lvalue (non stren case)
 * know rhs separate sr_vec (never stren) that exactly matches lhs width 
 *
 * concats removed before here
 * each assign type gens either non force assign or if forced because
 * wire force gens assign with per bit forcing 
 * since decl assign wire forcing bit by bit, 1 bit easy, vector needs masking
 *
 * caller must set correct down lhs itree context before here
 * uses the proc assign routines since know not stren
 */
static void gen_conta_assgn(struct expr_t *lhsx, int32 rhs_apti)
{
 int32 addr_apti, biti_ti, bi, needs_chg;
 struct net_t *np;
 struct expr_t *idndp;
 struct gref_t *grp;
 struct bblk_t *outofrng_bbp;
 int32 save_idp_ti, ri1, ri2;

 bi = biti_ti = -1;
 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;

 outofrng_bbp = NULL;
 save_idp_ti = -1;
 /* adjust rhs by adding stren if needed */
 switch (lhsx->optyp) {
  case GLBREF:
   if (np->frc_assgn_allocated || __net_chg_nd_store(np, -1, -1))
    {
     /* AIV 12/12/11 - need to copy the rhs since the idp area changes here */
     rhs_apti = gen_chgtorefgrp(lhsx, &save_idp_ti, rhs_apti);

     gen_conta_var_assign(np, rhs_apti);

     __gen_restore_idp(save_idp_ti);
     __pop_itstk();
    }
   /* for simple assign - xmr's handled by accessing right inum and compile */
   /* time inst mod */
   else gen_conta_simple_var_assign(np, idndp, rhs_apti);
   break; 
  case ID:
   if (np->frc_assgn_allocated || __net_chg_nd_store(np, -1, -1))
    {
     gen_conta_var_assign(np, rhs_apti);
    }
   else gen_conta_simple_var_assign(np, idndp, rhs_apti);
   break;
  case LSB:
   /* check if bit select is constant */
   if (lhsx->ru.x->optyp == NUMBER)
    {
     bi = __get_comp_num_ndx(lhsx->ru.x);
     needs_chg = __net_chg_nd_store(np, bi, bi);
    }
   else 
    {
     outofrng_bbp = __alloc_bblk(FALSE);
     biti_ti = __gen_comp_ndx(np, lhsx->ru.x, outofrng_bbp, FALSE);
     needs_chg = __net_chg_nd_store(np, -1, -1);
    }

   if (np->frc_assgn_allocated || needs_chg)
    {
     if (idndp->optyp == GLBREF) 
      {
       rhs_apti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_apti);
      }
     if (bi != -1) 
      {
       gen_conta_bit_assign(np, bi, -1, rhs_apti, TRUE);
      }
     else gen_conta_bit_assign(np, -1, biti_ti, rhs_apti, FALSE);

     if (idndp->optyp == GLBREF)
      {  
       __gen_restore_idp(save_idp_ti);
       __pop_itstk(); 
      }
     if (bi == -1) __start_bblk(outofrng_bbp);
    }
   else
    {
     if (idndp->optyp == GLBREF) grp = idndp->ru.grp; else grp = NULL;
     addr_apti = __ldvar_addr(np, grp);
     /* this handles both chg (ok if not XMR) and non chg forms */ 
     /* AIV 10/24/05 - need to convert scalar to svec to do the bsel */
     /* AIV 12/28/07 - conversion size is known to be 1 here for bsel */
     /* was doing np->nwid - causes incorrect widening */
     rhs_apti = __gen_cnvt_srep_ifneeded(rhs_apti, np->srep, 
       1, np->n_signed, FALSE, FALSE);
     if (bi != -1)
      {
       __gen_lhsbsel_const(np, addr_apti, bi, rhs_apti);
      }
     else
      {
       __gen_lhsbsel_var(np, addr_apti, biti_ti, rhs_apti);
       __start_bblk(outofrng_bbp);
      }
    }
   break; 
  case PARTSEL:
   ri1 = (int32) __contab[lhsx->ru.x->lu.x->ru.xvi];
   ri2 = (int32) __contab[lhsx->ru.x->ru.x->ru.xvi];
   if (np->frc_assgn_allocated || __net_chg_nd_store(np, ri2, ri1))
    {
     if (idndp->optyp == GLBREF) 
      {
       rhs_apti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_apti);
      }
     gen_conta_psel_assign(lhsx, rhs_apti);
     if (idndp->optyp == GLBREF)
      {  
       __gen_restore_idp(save_idp_ti);
       __pop_itstk(); 
      }
    }
   /* AIV 02/02/06 - was true need to get xmr ref here */
   else __gen_assgn_to_psel(lhsx, rhs_apti, FALSE);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * gen conta var assign - simple case (chg form and qcaf not possible)
 *
 * get base address - XMR works since - one inst base known, just copy
 *
 */
static void gen_conta_simple_var_assign(struct net_t *np, struct expr_t *idndp,
 int32 rhsadr_ti)
{
 int32 addr_ti;

 if (idndp->optyp == ID) addr_ti = __ldvar_addr(np, NULL);
 else if (idndp->optyp == GLBREF) addr_ti = __ldvar_addr(np, idndp->ru.grp);
 else { addr_ti = SR_UNKN; __case_terr(__FILE__, __LINE__); }

 /* AIV 10/10/05 - forgot the needed conversion */
 rhsadr_ti = __gen_cnvt_srep_ifneeded(rhsadr_ti, np->srep, np->nwid,
  np->n_signed, FALSE, TRUE);
 __gen_st_val(np, addr_ti, rhsadr_ti);
}

/*
 * gen vinsns for a continous assign (any decl that does not need stren add
 * really) change or possible qcaf forced variable assign
 *
 * need to pass the net addr since formal tmp tab must be mod specific
 * and use of the net address does that - offset same for differ mods
 *
 * this is unusual routine for both stren and non stren
 */
static void gen_conta_var_assign(struct net_t *np, int32 rhs_apti)
{
 int32 np_ti, rhs2_apti, qcaf_active_ti, addr_ti, blen;
 struct bblk_t *after_bbp, *assgn_bbp;

 after_bbp = NULL;
 if (np->frc_assgn_allocated)
  {
   after_bbp = __alloc_bblk(FALSE);
   assgn_bbp = __alloc_bblk(FALSE);

   np_ti = __ld_netadr_tn(np);
   /* AIV 10/10/05 - forgot the needed conversion */
   rhs_apti = __gen_cnvt_srep_ifneeded(rhs_apti, np->srep, np->nwid,
     np->n_signed, FALSE, TRUE);

   if (!np->n_isavec)
    {
     qcaf_active_ti = __emit_scalar_wire_inhibit(np_ti);
     rhs2_apti = rhs_apti;
    }
   else if (np->n_stren)
    {
     /* the correct forced new wire val vinsn complex because it both */ 
     /* overwrites the rhs (that must be non var tmp name) and returns T/F */
     rhs2_apti = __gen_tn(SR_SVEC, np->nwid);
     __emit_copy(np->nwid, rhs_apti, rhs2_apti);
     qcaf_active_ti = __emit_stren_correct_frc(np_ti, rhs2_apti);
    }
   else
    {
     if (np->n_2state)
      {
       rhs2_apti = __gen_tn(SR_BIT2S, np->nwid);
       __emit_copy(WRDBYTES*wlen_(np->nwid), rhs_apti, rhs2_apti);
      }
     else
      {
       rhs2_apti = __gen_tn(SR_VEC, np->nwid);
       __emit_copy(2*WRDBYTES*wlen_(np->nwid), rhs_apti, rhs2_apti);
      }

     qcaf_active_ti = __emit_correct_frc(np_ti, rhs2_apti);
    }

   __emit_jmp_0(after_bbp, assgn_bbp, qcaf_active_ti);
   __start_bblk(assgn_bbp);
  }
 else rhs2_apti = rhs_apti;

 /* this will usually fill low and high halves (high if there is b part) */
 addr_ti = __ldvar_addr(np, NULL);
 blen = __get_tnwid(addr_ti);
 /* if lhs is a different size must do conversion */
 rhs2_apti = __gen_cnvt_srep_ifneeded(rhs2_apti, np->srep, blen,
  __tntab[rhs2_apti].t_signed, FALSE, TRUE);
 if (__net_chg_nd_store(np, -1, -1)) __gen_chg_st_val(np, addr_ti, rhs2_apti);
 else __gen_st_val(np, addr_ti, rhs2_apti);

 if (np->frc_assgn_allocated) __start_bblk(after_bbp);
}

/*
 * gen conta bit assign (complex case - either change store or can be force)
 */
static void gen_conta_bit_assign(struct net_t *np, int32 bi, int32 biti_ti,
 int32 rhs_apti, int32 is_const)
{
 int32 qcaf_active_ti, np_ti, addr_apti;
 struct bblk_t *after_bbp, *assgn_bbp;

 after_bbp = NULL;
 if (np->frc_assgn_allocated)
  {
   after_bbp = __alloc_bblk(FALSE);
   assgn_bbp = __alloc_bblk(FALSE);

   np_ti = __ld_netadr_tn(np);
   /* SJM 07/12/06 - bit index here can be literal con - need cint gen here */
   /* AIV 11/09/06 - was passing the tmp not the constant bi */
   if (is_const) biti_ti = __gen_cint_tn(bi);
   qcaf_active_ti = __emit_bsel_wirfrc_inhibit(np_ti, biti_ti);
   __emit_jmp_0(after_bbp, assgn_bbp, qcaf_active_ti);
   __start_bblk(assgn_bbp);
  }

 addr_apti = __ldvar_addr(np, NULL);
 /* AIV 10/24/05 - need to convert scalar to svec to do the bsel */
 rhs_apti = __gen_cnvt_srep_ifneeded(rhs_apti, np->srep, 
  np->nwid, np->n_signed, FALSE, FALSE);
 /* this handles both chg and non chg forms */ 
 if (is_const) __gen_lhsbsel_const(np, addr_apti, bi, rhs_apti);
 else __gen_lhsbsel_var(np, addr_apti, biti_ti, rhs_apti);

 if (np->frc_assgn_allocated) __start_bblk(after_bbp);
}

/*
 * gen conta lhs psel assign
 * (complex case - either change store or can be force)
 *
 * caller must push to right XMR itree loc if needed
 */
static void gen_conta_psel_assign(struct expr_t *lhsx, int32 rhs_apti)
{
 int32 addr_apti, qcaf_active_ti, rhs2_apti, np_ti, blen;
 int32 ri1, ri2;
 struct expr_t *idndp;
 struct net_t *np;
 struct bblk_t *after_bbp, *assgn_bbp;

 idndp = lhsx->lu.x;
 np = idndp->lu.sy->el.enp;
 ri1 = (int32) __contab[lhsx->ru.x->lu.x->ru.xvi];
 ri2 = (int32) __contab[lhsx->ru.x->ru.x->ru.xvi];
 after_bbp = NULL;
 /* AIV 03/02/06 - was using np->nwid in some places where it needs lhsx */
 blen = lhsx->szu.xclen;
 if (np->frc_assgn_allocated) 
  {
   after_bbp = __alloc_bblk(FALSE);
   assgn_bbp = __alloc_bblk(FALSE);

   /* AIV 10/10/05 - forgot the needed conversion */
   rhs_apti = __gen_cnvt_srep_ifneeded(rhs_apti, np->srep, blen, 
     np->n_signed, FALSE, FALSE);
   if (np->n_2state)
    {
     rhs2_apti = __gen_tn(SR_BIT2S, blen);
     __emit_copy(WRDBYTES*wlen_(blen), rhs_apti, rhs2_apti);
    }
   else
    {
     rhs2_apti = __gen_tn(SR_VEC, blen);
     __emit_copy(2*WRDBYTES*wlen_(blen), rhs_apti, rhs2_apti);
    }

   np_ti = __ld_netadr_tn(np);
   qcaf_active_ti = __emit_psel_correct_frc(np_ti, rhs2_apti, ri1, ri2); 
   __emit_jmp_0(after_bbp, assgn_bbp, qcaf_active_ti);
   __start_bblk(assgn_bbp);
  }
 else rhs2_apti = rhs_apti;

 /* AIV 10/10/05 - forgot the needed conversion */
 rhs2_apti = __gen_cnvt_srep_ifneeded(rhs2_apti, np->srep, blen, 
   np->n_signed, FALSE, FALSE);
 addr_apti = __ldvar_addr(np, NULL);
 if (__net_chg_nd_store(np, ri2, ri1))
  {
   __gen_chg_lhspsel(np, lhsx->szu.xclen, addr_apti, rhs2_apti, ri2,
    ri1 - ri2 + 1, ri1);
  }
 else
  {
   __gen_st_psel(np->srep, addr_apti, rhs2_apti, ri2, ri1 - ri2 + 1);
  }

 if (np->frc_assgn_allocated) __start_bblk(after_bbp);
}

/*
 * ROUTINES TO GEN VINSNS FOR DECLARATIVE ASSIGN SCHEDULING
 */

/*
 * gen vm ins to schedule assign of all bits from wire
 * that is lhs of conta (and other)
 *
 * NOTICE - this is not for fi>1 lhs exprs 
 *
 * must always schedule even if qc force/assign active because may
 * not be when assign happens
 *
 * either completing no delay conta or processing conta assign event - this
 * delays wire value change including delay path processing
 *
 * NOTE: this is only used for fi==1 assign so trireg impossible since fi>1
 *
 * LOOKATME - why are lhs bsel/psel never tr decay?
 */
static void gen_sched_conta_assign(struct expr_t *xlhs, int32 rhs_ti)
{
 int32 nd_itpop, save_idp_ti;
 struct expr_t *idndp;
 struct net_t *np;

 idndp = __get_lvalue_idndp(xlhs);
 np = idndp->lu.sy->el.enp;

 save_idp_ti = -1;
 nd_itpop = FALSE;
 switch (xlhs->optyp) {
  case GLBREF:
   rhs_ti = gen_chgtorefgrp(xlhs, &save_idp_ti, rhs_ti);
   nd_itpop = TRUE;
   /* FALLTHRU */
  case ID:
   /* var forms either path delay or wire delay but bsel/psel only path */
   if (np->n_stren)
    {
     gen_stren_schd_allofwire(np, rhs_ti, xlhs->szu.xclen); 
    }
   else gen_schd_allofwire(np, rhs_ti, xlhs->szu.xclen); 

   if (nd_itpop) 
    {  
     __gen_restore_idp(save_idp_ti);
     __pop_itstk(); 
    }
   break;
  case LSB:
   if (np->n_stren)
    {
     gen_stren_sched_to_bit(np, xlhs->lu.x, xlhs->ru.x, rhs_ti);
    }
   else gen_sched_to_bit(np, xlhs->lu.x, xlhs->ru.x, rhs_ti);
   break;
  case PARTSEL:
   /* part select never wdel schedule */
   if (np->n_stren) gen_stren_sched_to_psel(xlhs, rhs_ti);
   else gen_sched_to_psel(xlhs, rhs_ti);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * ROUTINES TO GENERATE VINSNS FOR BOTH SPECIFY PATH AND WIRE DEL SCHEDULES
 */

/*
 * gen vinsns to schedule an entire stren specify path delay wire
//SJM - what if rhs narrow scalar (not svec?) but non scalar np?
 */
static void gen_stren_schd_allofwire(struct net_t *np, int32 newsbp_ti, 
 int32 sblen) 
{
 int32 rhswid, oldsbp_ti, oldscalw_ti, svecadr_ti, np_ti, bi; 
 int32 cint_ti, cint2_ti, nchg_ti, enter_ti, ctevp_ti;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 /* base of current itree loc area addr - this will be svec ptr */
 oldsbp_ti = gen_get_stwire_addr(np, NULL);

 np_ti = __ld_netadr_tn(np);
 if (np->ntyp == N_TRIREG)
  {
   /* DBG remove -- */
   if (np->nu.rngdwir->n_delrep == DT_PTHDST)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* tri reg only wire delay and never select */
   gen_wdel_trireg(np, oldsbp_ti, newsbp_ti);
   return;
  }

 if (!np->n_isavec)
  {
   gen_stren_scalar_schd(np, np_ti, newsbp_ti, oldsbp_ti);
   return;
  }
 
 /* AIV 01/11/12 - this was wrong - only need to assign to width of the rhs */
 rhswid = __get_tnwid(newsbp_ti);

 /* SJM 07/20/05 - LOOKATME - should maybe add inc insns */ 
 for (bi = 0; bi < rhswid; bi++)
  {
   gen_stren_1bit_schd(np, np_ti, bi, newsbp_ti, oldsbp_ti);
  }

 if (sblen >= np->nwid) return;

 /* case 2: widen rhs */
 for (bi = sblen; bi < np->nwid; bi++)
  {
   svecadr_ti = __con_adradd_insn(SR_SVEC, np->nwid, oldsbp_ti, bi);
   oldscalw_ti = __emit_movint_fr_svec(svecadr_ti);

   cint2_ti = __gen_cint_tn(2);
   cint_ti = __gen_cint_tn(bi);
   ncp = __gen_netchg_addr_tn(np, bi, bi, TRUE, &nchg_ti);
   enter_ti = __gen_process_wire_enter(ncp->ndx);

   ctevp = np->ndel_ctevtab[bi];
   ctevp_ti = __gen_ctevp_adr_tn(ctevp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

   if (np->nu.rngdwir->n_delrep == DT_PTHDST)
    {
     __emit_stren_sched_1pthbit(np_ti, cint_ti, cint2_ti, oldscalw_ti, 
      nchg_ti, ctevp_ti);
    }
   else
    {
     /* although for wire delay entire wire - scheduling bit by bit */
     __emit_stren_sched_1wirbit(np_ti, cint_ti, cint2_ti, oldscalw_ti, 
      ctevp_ti);
    }
  }
}
   
/*
 * inline routine wrapper to schedule trireg wdel 
 * if (np->ntyp == N_TRIREG)  case from __wdel_stren_schd_allofwire
 */
static void gen_wdel_trireg(struct net_t *np, int32 oldsbp_ti, int32 newsbp_ti)
{
 int32 bi, np_ti, cint_ti, nchg_ti, ctevp_ti, enter_ti, biti_ti; 
 int32 old_bi_ti, new_bi_ti, hiz_ti, r1_ti, r2_ti, biti;
 struct net_chg_t *ncp;
 struct bblk_t *hiz_bbp, *not_hiz_bbp, *eq_bbp, *not_eq_bbp, *next_bbp;
 struct ctev_t *ctevp;

 /* DBG remove -- */ 
 if (np->nu.rngdwir->n_delrep == DT_PTHDST) __misc_terr(__FILE__, __LINE__);
 /* ---- */ 

 np_ti = __ld_netadr_tn(np);
 hiz_ti = __gen_cint_tn(ST_HIZ);
 for (bi = 0; bi < np->nwid; bi++)
  {
   if (np->n_isavec) biti = bi; else biti = -1;
   /* SJM 10/30/07 - need bi as tn for wrapper call still */
   biti_ti = __gen_cint_tn(bi);

   old_bi_ti = __con_adradd_insn(SR_SVEC, 1, oldsbp_ti, bi);
   new_bi_ti = __con_adradd_insn(SR_SVEC, 1, newsbp_ti, bi);

   hiz_bbp = __alloc_bblk(FALSE);
   not_hiz_bbp = __alloc_bblk(FALSE);
   eq_bbp = __alloc_bblk(FALSE);
   not_eq_bbp = __alloc_bblk(FALSE);
   next_bbp = __alloc_bblk(FALSE);
   /* if (nsbp[bi] == ST_HIZ) */
   __emit_jmp_byte_eq(hiz_bbp, not_hiz_bbp, new_bi_ti, hiz_ti); 
   __start_bblk(hiz_bbp);

   /* ntrival = (*osbp & 3) | __cap_to_stren[np->n_capsiz]; */
   cint_ti = __gen_cint_tn(3);
   r1_ti = __emit_mask_and(old_bi_ti, cint_ti);  
   cint_ti = __gen_cint_tn(__cap_to_stren[np->n_capsiz]);
   r2_ti = __emit_mask_or(r1_ti, cint_ti);  
   /* if (ntrival != *osbp) */
   __emit_jmp_byte_eq(eq_bbp, not_eq_bbp, r2_ti, old_bi_ti); 
//AIV FIXME - make this a routine
   __start_bblk(not_eq_bbp);
   __emit_copy(1, r2_ti, old_bi_ti);

   /* only do record if needed */
   if (__net_chg_nd_store(np, biti, biti))
    {
     __gen_record_const_nchg(np, biti, biti, next_bbp);
    }
   __emit_jmp(eq_bbp);
   __start_bblk(eq_bbp);

   ncp = __gen_netchg_addr_tn(np, biti, biti, TRUE, &nchg_ti);
   enter_ti = __gen_process_wire_enter(ncp->ndx);
   ctevp = np->ndel_ctevtab[bi];
   ctevp_ti = __gen_ctevp_adr_tn(ctevp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

   __emit_wdel_trireg_hiz(np_ti, oldsbp_ti, newsbp_ti, biti_ti, ctevp_ti);

   __emit_jmp(next_bbp);
   __start_bblk(not_hiz_bbp);
   __emit_stren_sched_1wirbit(np_ti, biti_ti, new_bi_ti, old_bi_ti, ctevp_ti);
   __start_bblk(next_bbp);
  }
}

/*
 * generate stren schd vinsn for scalar specify path and wire delay 
 */
static void gen_stren_scalar_schd(struct net_t *np, int32 np_ti, 
 int32 newsbp_ti, int32 oldsbp_ti)
{
 int32 oldscalw_ti, newscalw_ti, cint_ti, nchg_ti, enter_ti, ctevp_ti;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 ctevp = np->ndel_ctevtab[0];
 oldscalw_ti = __emit_movint_fr_svec(oldsbp_ti);
 /* if new value (new rhs being scheduled) load into cint tmp val */ 
 /* if the byte is an address must isolate the byte to a val to compare */
 /* with the oldscalw int value */
 if (__tntab[newsbp_ti].tn_typ == TN_ADR)
  {
   newscalw_ti = __emit_movint_fr_svec(newsbp_ti);
  }
 else newscalw_ti = newsbp_ti; 
   
 /* DBG remove -- */
 if (np->n_isavec) __misc_terr(__FILE__, __LINE__);
 //ncp = __gen_netchg_addr_tn(np, 0, 0, TRUE, &nchg_ti);
 /* -- */
 ncp = __gen_netchg_addr_tn(np, -1, -1, TRUE, &nchg_ti);
 enter_ti = __gen_process_wire_enter(ncp->ndx);

 ctevp_ti = __gen_ctevp_adr_tn(ctevp);

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

 /* AIV 08/19/10 - may have to convert from 4-state to 2-state */
 if (np->n_2state)
  {
   newscalw_ti = __gen_cnvt_srep_ifneeded(newscalw_ti, np->srep, 1, 
     FALSE, FALSE, FALSE);
  }

 /* AIV 09/25/07 - this should have been scalar */
 if (np->nu.rngdwir->n_delrep == DT_PTHDST)
  {
   gen_sched_scalar_1pthbit(np, np_ti, newscalw_ti, oldscalw_ti, nchg_ti, 
    ctevp_ti, np->n_stren);
  }
 else
  {
   cint_ti = __gen_cint_tn(0);
   __emit_sched_1wirbit(np_ti, cint_ti, newscalw_ti, oldscalw_ti, ctevp_ti);
  }
}
 
/*
 * schedule a scalar path delay 
 */
static void gen_sched_scalar_1pthbit(struct net_t *np, int32 np_ti, 
 int32 newscalw_ti, int32 oldscalw_ti, int32 nchg_ti, int32 ctevp_ti, 
 int32 is_stren)
{
 int32 has_msg, trigger_ti, tevp_reg_ti, chk_path_set;
#ifdef __CVC32__
 int32 newtime_low_ti, newtime_high_ti;
#else
 int32 newtime_ti;
#endif
 size_t offset;
 struct bblk_t *eq_bbp, *not_eq_bbp, *done_bbp, *cancel_tev_bbp, *assign_bbp;
 struct tev_t *tevp;

 /* if has warning print options just use wrappers */
 has_msg = (__warn_cancel_e || __show_cancel_e);
 if (has_msg)
  {
   __emit_sched_scalar_1pthbit(np_ti, newscalw_ti, oldscalw_ti, nchg_ti, 
    ctevp_ti, is_stren);
   return;
  }

 /*
  * if (nval == oval) 
  * { 
  *  if (ptevp->trigger) linkout_tevp(ptevp);
  *  return;
  * }
  */
   
 eq_bbp = __alloc_bblk(FALSE);
 not_eq_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);
 cancel_tev_bbp = __alloc_bblk(FALSE);


 /* nval == oval */
 __emit_jmp_eq(eq_bbp, not_eq_bbp, newscalw_ti, oldscalw_ti); 
 __start_bblk(eq_bbp);

 /* if (tevp->trigger) */
 tevp_reg_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, ctevp_ti);
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 trigger_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, tevp_reg_ti, offset);

 /* cancel event */
 __emit_jmp_0(done_bbp, cancel_tev_bbp, trigger_ti); 
 __start_bblk(cancel_tev_bbp);
 /* AIV 02/21/09 - this should use the reg here - no worse on reg alloc */
 __emit_cancel_ev(tevp_reg_ti);
 __emit_jmp(done_bbp);

 __start_bblk(not_eq_bbp);
//AIV LOOKATME 01/12/12 - don't think these global settings are needed
//they one was set for 32 and other ifdef for 64
 __emit_set_new_gateval(newscalw_ti);
 __emit_set_old_gateval(oldscalw_ti);
 /* AIV 01/13/12 - this now has to alloc and pass the assign block */
 /* if single path case and cond is false get_path should just jump */
 /* to assign in the schedule path routine */
 assign_bbp = __alloc_bblk(FALSE);
#ifdef __CVC32__
 chk_path_set = gen_get_path_del32(np, &newtime_low_ti, &newtime_high_ti, 0, 
   newscalw_ti, oldscalw_ti, assign_bbp);
 gen_schedule_path_bit32(np, done_bbp, ctevp_ti, newtime_low_ti, 
   newtime_high_ti, -1, chk_path_set, assign_bbp, newscalw_ti);
#else
 chk_path_set = gen_get_path_del64(np, &newtime_ti, 0, newscalw_ti, 
  oldscalw_ti, assign_bbp);
 gen_schedule_path_bit64(np, done_bbp, ctevp_ti, newtime_ti, -1, chk_path_set,
  assign_bbp, newscalw_ti);
#endif
 __start_bblk(done_bbp);
}

#ifdef __CVC32__
/*
 * get a path delay 64-bit time places the low value of the scheduled time 
 * in lowval_ti and the high in highval_ti
 * AIV 01/13/12 - rewrote this to check for condition code here at
 * path selection
 */
static int32 gen_get_path_del32(struct net_t *np, int32 *lowval_ti,
 int32 *highval_ti, int32 bi, int32 newscalw_ti, int32 oldscalw_ti,
 struct bblk_t *assign_bbp)
{
 int32 newdel_low_ti, newdel_high_ti;
 int32 idplast_low_ti, idplast_high_ti, is_const, ndx_ti;
 int32 pdmindel_low_ti, pdmindel_high_ti, low_reg_ti, high_reg_ti;
 int32 pdlatchgtim_low_ti, pdlatchgtim_high_ti, t1_ti, t2_ti, eq_ti;
 int32 chk_path_set, has_path_cond, cond_ti, one_path, cint_ti;
 word64 del;
 struct pthdst_t *pdp;
 struct spcpth_t *pthp;
 struct rngdwir_t *dwirp; 
 struct tchg_t *tchgp;
 struct bblk_t *next_bbp, *get_newdel_bbp, *eq_bbp, *not_eq_bbp;
 struct bblk_t *set_pdmindel_bbp, *use_bbp;
 struct bblk_t *cond_notzero_bbp;
 struct expr_t *condx;

 dwirp = np->nu.rngdwir;
 pdp = dwirp->n_du.pb_pthdst[bi];
 /* DBG remove -- */
 if (pdp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* need to check if any on path has a if(cond) condition */
 pdmindel_low_ti = -1;
 pdmindel_high_ti = -1;
 chk_path_set = FALSE;
 has_path_cond = any_on_path_cond(pdp);
 /* if all paths are the same delay can produce better code */
 if (all_paths_same(pdp, &del)) 
  {
   chk_path_set = gen_get_path_del32_const(np, lowval_ti, highval_ti, bi, del,
     has_path_cond, assign_bbp);
   return(chk_path_set);
  }
 
 /* if has any cond set flag to false */
 if (has_path_cond) chk_path_set = TRUE;

 pthp = pdp->pstchgp->chgu.chgpthp;
 condx = pthp->pthcondx;
 one_path = (pdp->pdnxt == NULL);
 /* AIV 03/09/09 - if all paths are the same only compute the index once */
 if (is_path_same_delrep(pdp))
  {
   ndx_ti = -1;
   /* if first one was a cond this may never get executed - and it needs to */
   /* compute the index for the first time - if it has a cond this may */
   /* never get computed so need to do it for the first time */
   if (condx != NULL && !one_path)
    {
     gen_get_del32(np, &pdmindel_low_ti, &pdmindel_high_ti, pthp->pth_du, 
       pthp->pth_delrep, pthp->spcpth_id, &ndx_ti, newscalw_ti, 
       oldscalw_ti, !one_path);
    }
  }
 else ndx_ti = FALSE;


 /* AIV 01/13/12 - just init this to largest and smallest - this saves */
 /* an additional if stmt inside the loop */
 /* __pdmindel = MAXTIME; __pdlatechgtim = 0; */
 pdlatchgtim_low_ti = __gen_tn(SR_CINT, WBITS);
 pdlatchgtim_high_ti = __gen_tn(SR_CINT, WBITS);
 if (!one_path) 
  {
   cint_ti = __gen_cint_tn(0);
   __emit_copy(WRDBYTES, cint_ti, pdlatchgtim_low_ti);
   __emit_copy(WRDBYTES, cint_ti, pdlatchgtim_high_ti);

   cint_ti = __gen_cint_tn(0xffffffff);
   __st_insn(I_STOREL, AM_REG, cint_ti, AM_NLO, NLO_PDMINDEL);
   __st_insn(I_STOREL, AM_REG, cint_ti, AM_NLO, NLO_PDMINDEL_HIGH);
  }


 /* common case there is only one */
 tchgp = pdp->pstchgp;
 idplast_low_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
     WRDBYTES*(tchgp->lastchg_ofs));
 idplast_high_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
    WRDBYTES*(tchgp->lastchg_ofs+1));

 if (condx != NULL)
  {
   cond_notzero_bbp = __alloc_bblk(FALSE);
   if (one_path) use_bbp = assign_bbp;
   else use_bbp = __alloc_bblk(FALSE);

   cond_ti = __gen_expr_eval(condx, -1);

   cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
      FALSE);
   __emit_jmp_0(use_bbp, cond_notzero_bbp, cond_ti);
   __start_bblk(cond_notzero_bbp);

    gen_get_del32(np, &pdmindel_low_ti, &pdmindel_high_ti, 
      pthp->pth_du, pthp->pth_delrep, pthp->spcpth_id, &ndx_ti,
      newscalw_ti, oldscalw_ti, !one_path);

   if (!one_path) 
    {
     __emit_copy(WRDBYTES, idplast_low_ti, pdlatchgtim_low_ti);
     __emit_copy(WRDBYTES, idplast_high_ti, pdlatchgtim_high_ti);
    }

   __st_insn(I_STOREA, AM_REG, pdmindel_low_ti, AM_NLO, NLO_PDMINDEL);
   __st_insn(I_STOREA, AM_REG, pdmindel_high_ti, AM_NLO, NLO_PDMINDEL_HIGH);

   /* if skipping block just set time to 0 and return -1 */
   /* this works because new time will be 0 <= __simtime */
   /* this saves a compare */
   if (one_path) 
    {
     /* __cvc_newdel = pdlatechgtim + __pdmindel; */
     /* do a 64-bit add */
     low_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_low_ti);
     *lowval_ti = __emit_add(WBITS, pdmindel_low_ti, low_reg_ti);

     high_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_high_ti);
     *highval_ti = __emit_adc(pdmindel_high_ti, high_reg_ti);
     return(-1);
    }
   __start_bblk(use_bbp);
  }
 else
  {
    gen_get_del32(np, &pdmindel_low_ti, &pdmindel_high_ti, 
      pthp->pth_du, pthp->pth_delrep, pthp->spcpth_id, &ndx_ti,
      newscalw_ti, oldscalw_ti, !one_path);

   __st_insn(I_STOREA, AM_REG, pdmindel_low_ti, AM_NLO, NLO_PDMINDEL);
   __st_insn(I_STOREA, AM_REG, pdmindel_high_ti, AM_NLO, NLO_PDMINDEL_HIGH);

   if (one_path) 
    {
     /* __cvc_newdel = pdlatechgtim + __pdmindel; */
     /* do a 64-bit add */
     low_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_low_ti);
     *lowval_ti = __emit_add(WBITS, pdmindel_low_ti, low_reg_ti);

     high_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_high_ti);
     *highval_ti = __emit_adc(pdmindel_high_ti, high_reg_ti);
     return(chk_path_set);
    }

   __emit_copy(WRDBYTES, idplast_low_ti, pdlatchgtim_low_ti);
   __emit_copy(WRDBYTES, idplast_high_ti, pdlatchgtim_high_ti);
  }

 next_bbp = __alloc_bblk(FALSE);
 get_newdel_bbp = __alloc_bblk(FALSE);
 eq_bbp = __alloc_bblk(FALSE);
 not_eq_bbp = __alloc_bblk(FALSE);
 set_pdmindel_bbp = __alloc_bblk(FALSE);

 for (pdp = pdp->pdnxt; pdp != NULL; pdp = pdp->pdnxt)
  {
   tchgp = pdp->pstchgp;
   pthp = pdp->pstchgp->chgu.chgpthp;
   /* AIV 01/13/12 must check the condition */
   condx = pthp->pthcondx;
   if (condx != NULL)
    {
     cond_notzero_bbp = __alloc_bblk(FALSE);
     cond_ti = __gen_expr_eval(condx, -1);

     cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
       FALSE);
     __emit_jmp_0(next_bbp, cond_notzero_bbp, cond_ti);
     __start_bblk(cond_notzero_bbp);
    }

   /* lastchg_time = *((word64 *) &(__idp[pdp->pstchgp->lastchg_ofs])); */
   /* if (lastchg_time < pdlatechgtim) continue; */
   idplast_low_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*(tchgp->lastchg_ofs));
   idplast_high_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
    WRDBYTES*(tchgp->lastchg_ofs+1));

   __emit_jmp_cmp64_idp_lessthan(next_bbp, get_newdel_bbp, 
     idplast_low_ti, idplast_high_ti, pdlatchgtim_low_ti, pdlatchgtim_high_ti);

   __start_bblk(get_newdel_bbp);

   /* newdel = __get_del(pthp->pth_du, pthp->pth_delrep); */
   is_const = gen_get_del32(np, &newdel_low_ti, &newdel_high_ti, 
      pthp->pth_du, pthp->pth_delrep, pthp->spcpth_id, &ndx_ti,
      newscalw_ti, oldscalw_ti, FALSE);

   /* if (lastchg_time == pdlatechgtim) */
   t1_ti = __emit_bin_bitxor(WBITS, idplast_low_ti, pdlatchgtim_low_ti);
   t2_ti = __emit_bin_bitxor(WBITS, idplast_high_ti, pdlatchgtim_high_ti);
   eq_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
   __emit_jmp_0(eq_bbp, not_eq_bbp, eq_ti);
   __start_bblk(eq_bbp);

   /* if (newdel > __pdmindel) continue; */
   /* if it is comparing a literal value must do special 64-bit compare */
   if (is_const)
    {
     __emit_jmp_cmp64_gt_pdmindel_const(next_bbp, set_pdmindel_bbp, 
       newdel_low_ti, newdel_high_ti);
    }
   else
    {
     __emit_jmp_cmp64_gt_pdmindel(next_bbp, set_pdmindel_bbp, newdel_low_ti,
      newdel_high_ti);
    }
   
   /* pdlatechgtim = lastchg_time; */
   __start_bblk(not_eq_bbp);
   __emit_copy(WRDBYTES, idplast_low_ti, pdlatchgtim_low_ti);
   __emit_copy(WRDBYTES, idplast_high_ti, pdlatchgtim_high_ti);
   __emit_jmp(set_pdmindel_bbp);

   /* __pdmindel = newdel; */
   __start_bblk(set_pdmindel_bbp);
   __st_insn(I_STOREA, AM_REG, newdel_low_ti, AM_NLO, NLO_PDMINDEL);
   __st_insn(I_STOREA, AM_REG, newdel_high_ti, AM_NLO, NLO_PDMINDEL_HIGH);

   __emit_jmp(next_bbp);
   

   /* AIV 03/07/12 - there is no reason to check for this because if the time */
   /* is the same will can just set to the same value again */
   /* if (pthp->pth_ifnone && newdel == __pdmindel) continue; */
   /* if (pthp->pth_ifnone) __misc_terr(__FILE__, __LINE__); */
    
   __start_bblk(next_bbp);
   if (pdp->pdnxt != NULL) 
    {
     next_bbp = __alloc_bblk(FALSE);
     get_newdel_bbp = __alloc_bblk(FALSE);
     eq_bbp = __alloc_bblk(FALSE);
     not_eq_bbp = __alloc_bblk(FALSE);
     set_pdmindel_bbp = __alloc_bblk(FALSE);
    }
  }

 /* __cvc_newdel = pdlatechgtim + __pdmindel; */
 pdmindel_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_PDMINDEL);
 *lowval_ti = __emit_add(WBITS, pdmindel_low_ti, pdlatchgtim_low_ti);

 pdmindel_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_PDMINDEL_HIGH);
 *highval_ti = __emit_adc(pdmindel_high_ti, pdlatchgtim_high_ti);
 return(chk_path_set);
}

/*
 * get the delay were all delays are known to be the same
 * if all paths are the same delay can produce better code 
 */
static int32 gen_get_path_del32_const(struct net_t *np, int32 *lowval_ti,
 int32 *highval_ti, int32 bi, word64 del, int32 has_path_cond, 
 struct bblk_t *assign_bbp)
{
 int32 d_low_ti, d_high_ti, chk_path_set, cond_ti, one_path, cint_ti;
 int32 idplast_low_ti, idplast_high_ti;
 int32 low_reg_ti, high_reg_ti;
 int32 pdlatchgtim_low_ti, pdlatchgtim_high_ti;
 word32 low, high;
 struct pthdst_t *pdp;
 struct spcpth_t *pthp;
 struct rngdwir_t *dwirp; 
 struct tchg_t *tchgp;
 struct bblk_t *next_bbp, *set_newdel_bbp, *use_bbp;
 struct bblk_t *cond_notzero_bbp;
 struct expr_t *condx;

 dwirp = np->nu.rngdwir;
 pdp = dwirp->n_du.pb_pthdst[bi];
 low = (word32) del;
 d_low_ti = __gen_cint_tn(low);
 high = (word32) (del >> 32ULL);
 d_high_ti = __gen_cint_tn(high);

 chk_path_set = FALSE;
 /* if has cond set all set to false */
 if (has_path_cond) chk_path_set = TRUE;
 
 one_path = (pdp->pdnxt == NULL);
 pdlatchgtim_low_ti = __gen_tn(SR_CINT, WBITS);
 pdlatchgtim_high_ti = __gen_tn(SR_CINT, WBITS);
 if (!one_path) 
  {
   cint_ti = __gen_cint_tn(0);
   __emit_copy(WRDBYTES, cint_ti, pdlatchgtim_low_ti);
   __emit_copy(WRDBYTES, cint_ti, pdlatchgtim_high_ti);
  }


 tchgp = pdp->pstchgp;
 idplast_low_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
    WRDBYTES*(tchgp->lastchg_ofs));
 idplast_high_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
    WRDBYTES*(tchgp->lastchg_ofs+1));
 pthp = pdp->pstchgp->chgu.chgpthp;
 condx = pthp->pthcondx;
 /* common case there is only one */
 if (condx != NULL)
  {
   cond_notzero_bbp = __alloc_bblk(FALSE);

   if (one_path) use_bbp = assign_bbp;
   else use_bbp = __alloc_bblk(FALSE);

   cond_ti = __gen_expr_eval(condx, -1);

   cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
      FALSE);
   __emit_jmp_0(use_bbp, cond_notzero_bbp, cond_ti);
   __start_bblk(cond_notzero_bbp);
   /* AIV 01/16/12 - need to set __pdmindel here */
   __st_insn(I_STOREL, AM_REG, d_low_ti, AM_NLO, NLO_PDMINDEL);
   __st_insn(I_STOREL, AM_REG, d_high_ti, AM_NLO, NLO_PDMINDEL_HIGH);
   /* 
    w64p = (word64 *) &(__idp[pdp->pstchgp->lastchg_ofs]);
    pdlatechgtim = *w64p;
   */
   if (!one_path) 
    {
     __emit_copy(WRDBYTES, idplast_low_ti, pdlatchgtim_low_ti);
     __emit_copy(WRDBYTES, idplast_high_ti, pdlatchgtim_high_ti);
    }

   /* if skipping block just set time to 0 and return -1 */
   /* this works because new time will be 0 <= __simtime */
   /* this saves a compare */
   /* __cvc_newdel = pdlatechgtim + __pdmindel; */
   /* do a 64-bit add */
   /*  res = a + b
	movl	a, %eax
	movl	a+4, %edx
	addl	b, %eax
	adcl	b+4, %edx
	movl	%eax, res
	movl	%edx, res+4
    */
   if (one_path) 
    {
     /* __cvc_newdel = pdlatechgtim + __pdmindel; */
     /* do a 64-bit add */
     low_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_low_ti);
 
     /* AIV 01/28/10 - need to catch 0 case here was working before because */
     /* was elimnated addl and adcl - but impossbile to remove the second */
     /* adcl if the value is not zero - but cannot remove both else */
     /* carry value is wrong */
     if (low == 0 && high == 0)
      { 
       *lowval_ti = low_reg_ti;
       idplast_high_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
         WRDBYTES*(tchgp->lastchg_ofs+1));
       high_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_high_ti);
        *highval_ti = high_reg_ti;
       return(-1);
      }


     *lowval_ti = __emit_add(WBITS, d_low_ti, low_reg_ti);
     high_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_high_ti);
     *highval_ti = __emit_adc(d_high_ti, high_reg_ti);
     return(-1);
    }
   __start_bblk(use_bbp);
  }
 else
  {
   __st_insn(I_STOREA, AM_REG, d_low_ti, AM_NLO, NLO_PDMINDEL);
   __st_insn(I_STOREA, AM_REG, d_high_ti, AM_NLO, NLO_PDMINDEL_HIGH);

   /* common case there is only one */
   if (one_path) 
    {
     /* __cvc_newdel = pdlatechgtim + __pdmindel; */
     /* do a 64-bit add */
     low_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_low_ti);
 
     /* AIV 01/28/10 - need to catch 0 case here was working before because */
     /* was elimnated addl and adcl - but impossbile to remove the second */
     /* adcl if the value is not zero - but cannot remove both else */
     /* carry value is wrong */
     if (low == 0 && high == 0)
      { 
       *lowval_ti = low_reg_ti;
       idplast_high_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
         WRDBYTES*(tchgp->lastchg_ofs+1));
       high_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_high_ti);
        *highval_ti = high_reg_ti;
       return(chk_path_set);
      }


     *lowval_ti = __emit_add(WBITS, d_low_ti, low_reg_ti);
     high_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, idplast_high_ti);
     *highval_ti = __emit_adc(d_high_ti, high_reg_ti);
     return(chk_path_set);
    }
   __emit_copy(WRDBYTES, idplast_low_ti, pdlatchgtim_low_ti);
   __emit_copy(WRDBYTES, idplast_high_ti, pdlatchgtim_high_ti);
  }

 next_bbp = __alloc_bblk(FALSE);
 set_newdel_bbp = __alloc_bblk(FALSE);
 for (pdp = pdp->pdnxt; pdp != NULL; pdp = pdp->pdnxt)
  {
   /* lastchg_time = *((word64 *) &(__idp[pdp->pstchgp->lastchg_ofs])); */
   /* if (lastchg_time < pdlatechgtim) continue; */
   pthp = pdp->pstchgp->chgu.chgpthp;
   condx = pthp->pthcondx;
   tchgp = pdp->pstchgp;
   if (condx != NULL)
    {
     cond_notzero_bbp = __alloc_bblk(FALSE);
     cond_ti = __gen_expr_eval(condx, -1);

     cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
       FALSE);
     __emit_jmp_0(next_bbp, cond_notzero_bbp, cond_ti);
     __start_bblk(cond_notzero_bbp);
    }
 
   idplast_low_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*(tchgp->lastchg_ofs));
   idplast_high_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
    WRDBYTES*(tchgp->lastchg_ofs+1));

   __emit_jmp_cmp64_idp_lessthan(next_bbp, set_newdel_bbp, 
     idplast_low_ti, idplast_high_ti, pdlatchgtim_low_ti, pdlatchgtim_high_ti);

   __start_bblk(set_newdel_bbp);

   __emit_copy(WRDBYTES, idplast_low_ti, pdlatchgtim_low_ti);
   __emit_copy(WRDBYTES, idplast_high_ti, pdlatchgtim_high_ti);
   __emit_jmp(next_bbp);

   /* AIV 03/07/12 - there is no reason to check for this because if the time */
   /* is the same will can just set to the same value again */
   /* if (pthp->pth_ifnone && newdel == __pdmindel) continue; */
   /* if (pthp->pth_ifnone) __misc_terr(__FILE__, __LINE__); */
    
   __start_bblk(next_bbp);
   if (pdp->pdnxt != NULL) 
    {
     next_bbp = __alloc_bblk(FALSE);
     set_newdel_bbp = __alloc_bblk(FALSE);
    }
  }

 /* AIV 01/28/10 - need to catch 0 case here was working before because */
 /* was elimnated addl and adcl - but impossbile to remove the second */
 /* adcl if the value is not zero - but cannot remove both else */
 /* carry value is wrong */
 /* __cvc_newdel = pdlatechgtim + __pdmindel; */
 if (low == 0 && high == 0)
  {
   *lowval_ti = pdlatchgtim_low_ti;
   *highval_ti = pdlatchgtim_high_ti;
  }
 else
  {
   *lowval_ti = __emit_add(WBITS, d_low_ti, pdlatchgtim_low_ti);
   *highval_ti = __emit_adc(d_high_ti, pdlatchgtim_high_ti);
  }
 return(chk_path_set);
}
 
/*
 * generate a 64-bit delay according to type placing the low word
 * in del_low_ti and the high word in del_high_ti
 *  
 * return TRUE if constant (currently just DT_1v)
 *
 * AIV 03/09/09 - pass ndx_ti which computes the index only once for the
 * path loop. If ndx_ti is false the path delays are not all the same 
 * type so they must be computed each time. Also passing the old/new
 * scalar values instead of using globals.
 *
 *
 * AIV FIXME - specnetdrvstren.v  - AIV 03/09/09 - removed this code and
 * all examples work - must have been separate problem????
 * cannot just use np->n_stren for some reason???? 
 * this should work __new_gateval sometimes has strength driven by strength
 * must always mask - not a big deal to just do the andl's
 */
static int32 gen_get_del32(struct net_t *np, int32 *del_low_ti, 
 int32 *del_high_ti, union del_u du, int32 drep, int32 del_id, int32 *ndx_ti,
 int32 new_gateval_ti, int32 old_gateval_ti, int32 has_next)
{
 int32 val_ti, t1_ti, t2_ti, cint_ti, ind_ti;
 int32 inum_ti, t3_ti, t4_ti;
 int32 del_du_ti, is_const;
 word32 low, high;
 word64 del;

 /* DBG remove -- */
 if (MD_INUM != 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 *del_low_ti = -1;
 *del_high_ti = -1;
 is_const = FALSE;
 /* AIV 03/09/09 - if the same path handle as constant value */
 if (is_one_path_same(du, drep, &del))
  {
   is_const = TRUE;
  }
 else if (drep == DT_1V)
  {
   del = du.d1v[0]; 
   is_const = TRUE;
  }
   
 if (is_const)
  {
   low = (word32) del;
   *del_low_ti = __gen_cint_tn(low);
   high = (word32) (del >> 32ULL);
   *del_high_ti = __gen_cint_tn(high);
  
   /* AIV 08/12/09 - if index is -1 for the first time and the first is */
   /* folded *ndx_ti has never been set later uses - only compute */
   /* the index once if same drep type */
   /* duplicated code - but only one switch needed could make routine ??? */
   if (*ndx_ti == -1 && has_next) 
    {
     switch ((byte) drep) {
      case DT_IS1V: 
       inum_ti = __emit_inum();
       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS1V2:
       /* del = (word64) du.dis1v2[inum]; */
       inum_ti = __emit_inum();
       cint_ti = __gen_cint_tn(2);
       ind_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_4V:
       /* del = du.d4v[__new_gateval & 3]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, new_gateval_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS4V:
      /* del = du.d4v[4*inum + (__new_gateval & 3)]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       /* t1 = 4*inum */
       cint_ti = __gen_cint_tn(4);
       inum_ti = __emit_inum();
       t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       t2_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS4V1:
       /* del = (word64) du.dis4v1[4*inum + (__new_gateval & 3)]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       /* t1 = 4*inum */
       cint_ti = __gen_cint_tn(4);
       inum_ti = __emit_inum();
       t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       ind_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS4V2:
       /* del = (word64) du.dis4v2[4*inum + (__new_gateval & 3)]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       /* t1 = 4*inum */
       cint_ti = __gen_cint_tn(4);
       inum_ti = __emit_inum();
       t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       t2_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
       cint_ti = __gen_cint_tn(2);
       ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_16V:
/* ind = 16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) &0xf); */
/* del = du.dis16v[ind]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
        }
       t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS16V:
/* ind = 16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) &0xf); */
/* del = du.dis16v[ind]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
        }
       t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
  
       /* 16*inum */
       cint_ti = __gen_cint_tn(16);
       inum_ti = __emit_inum();
       t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       t4_ti = __emit_add(WBITS, t2_ti, t3_ti);

       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, t4_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS16V1:
   /* ind = 
    16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) & 0xf); */
   /* del = (word64) du.dis16v1[ind]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);
  
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
        }
       t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
  
       /* 16*inum */
       cint_ti = __gen_cint_tn(16);
       inum_ti = __emit_inum();
       t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       ind_ti = __emit_add(WBITS, t2_ti, t3_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS16V2:
       /* ind = 
        16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) & 0xf); */
       /* del = (word64) du.dis16v2[ind]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);
  
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
        }
       t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
   
       /* 16*inum */
       cint_ti = __gen_cint_tn(16);
       inum_ti = __emit_inum();
       t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       t4_ti = __emit_add(WBITS, t2_ti, t3_ti);
  
       cint_ti = __gen_cint_tn(2);
       ind_ti = __emit_mult(WBITS, cint_ti, t4_ti);
       *ndx_ti = ind_ti;
       break;
     /* notice these last two - use the expression eval so inum is passed */
     /* global __inum must be set */
     case DT_1V:
     case DT_IS1V1: 
     case DT_1X:
     case DT_4X:
      break;
     default: __case_terr(__FILE__, __LINE__);
     }
    }
   return(TRUE);
  }

 del_du_ti = __gen_del_tn(del_id, (void *) du.d4v);
 switch ((byte) drep) {
  case DT_IS1V: 
   /* del = du.dis1v[inum]; */
   if (*ndx_ti <= 0)
    {
     inum_ti = __emit_inum();
     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   cint_ti = __gen_cint_tn(4);
   val_ti = __emit_add(WBITS, cint_ti, val_ti);
   *del_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS1V1:
   /* del = (word64) du.dis1v1[inum]; */
   inum_ti = __emit_inum();
   val_ti = __emit_add(WBITS, del_du_ti, inum_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, val_ti);

   *del_high_ti = __gen_cint_tn(0);
   return(TRUE);
  case DT_IS1V2:
   /* del = (word64) du.dis1v2[inum]; */
   if (*ndx_ti <= 0)
    {
     inum_ti = __emit_inum();
     cint_ti = __gen_cint_tn(2);
     ind_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, val_ti);
   *del_high_ti = __gen_cint_tn(0);
   return(TRUE);
  case DT_4V:
   /* del = du.d4v[__new_gateval & 3]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, new_gateval_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   cint_ti = __gen_cint_tn(4);
   val_ti = __emit_add(WBITS, cint_ti, val_ti);
   *del_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS4V:
   /* del = du.d4v[4*inum + (__new_gateval & 3)]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     /* t1 = 4*inum */
     cint_ti = __gen_cint_tn(4);
     inum_ti = __emit_inum();
     t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     t2_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);

   cint_ti = __gen_cint_tn(4);
   val_ti = __emit_add(WBITS, cint_ti, val_ti);
   *del_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS4V1:
   /* del = (word64) du.dis4v1[4*inum + (__new_gateval & 3)]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     /* t1 = 4*inum */
     cint_ti = __gen_cint_tn(4);
     inum_ti = __emit_inum();
     t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     ind_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, val_ti);
   *del_high_ti = __gen_cint_tn(0);
   return(TRUE);
  case DT_IS4V2:
  /* del = (word64) du.dis4v2[4*inum + (__new_gateval & 3)]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     /* t1 = 4*inum */
     cint_ti = __gen_cint_tn(4);
     inum_ti = __emit_inum();
     t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     t2_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
     cint_ti = __gen_cint_tn(2);
     ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, val_ti);

   cint_ti = __gen_cint_tn(0);
   *del_high_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, cint_ti);
   *del_high_ti = __gen_cint_tn(0);
   return(TRUE);
  case DT_16V:
/* ind = 16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) &0xf); */
/* del = du.dis16v[ind]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
      }
     t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   cint_ti = __gen_cint_tn(4);
   val_ti = __emit_add(WBITS, cint_ti, val_ti);
   *del_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS16V:
/* ind = 16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) &0xf); */
/* del = du.dis16v[ind]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
      }
     t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);

     /* 16*inum */
     cint_ti = __gen_cint_tn(16);
     inum_ti = __emit_inum();
     t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     t4_ti = __emit_add(WBITS, t2_ti, t3_ti);

     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, t4_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);

   *del_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   cint_ti = __gen_cint_tn(4);
   val_ti = __emit_add(WBITS, cint_ti, val_ti);
   *del_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS16V1:
   /* ind = 
    16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) & 0xf); */
   /* del = (word64) du.dis16v1[ind]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
      }
     t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);

     /* 16*inum */
     cint_ti = __gen_cint_tn(16);
     inum_ti = __emit_inum();
     t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     ind_ti = __emit_add(WBITS, t2_ti, t3_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_low_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, val_ti);
   *del_high_ti = __gen_cint_tn(0);
   return(TRUE);
  case DT_IS16V2:
   /* ind = 
    16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) & 0xf); */
   /* del = (word64) du.dis16v2[ind]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);
  
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
      }
     t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);

     /* 16*inum */
     cint_ti = __gen_cint_tn(16);
     inum_ti = __emit_inum();
     t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     t4_ti = __emit_add(WBITS, t2_ti, t3_ti);

     cint_ti = __gen_cint_tn(2);
     ind_ti = __emit_mult(WBITS, cint_ti, t4_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);

   *del_low_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, val_ti);
   cint_ti = __gen_cint_tn(4);
   *del_high_ti = __gen_cint_tn(0);
   return(TRUE);
  /* notice these last two - use the expression eval so inum is passed */
  /* global __inum must be set */
  case DT_1X:
   __emit_get_del32(ASL_GET_DEL_1X, del_low_ti, del_high_ti, del_du_ti);
   break;
  case DT_4X:
   __emit_get_del32(ASL_GET_DEL_4X, del_low_ti, del_high_ti, del_du_ti);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}

 
/*
 * schedule the path delay time for the scalar bit
 */
static void gen_schedule_path_bit32(struct net_t *np, 
 struct bblk_t *done_bbp, int32 ctevp_ti, 
 int32 newtime_low_ti, int32 newtime_high_ti, int32 bi,
 int32 chk_path_set, struct bblk_t *le_simtime_bbp, int32 newscalw_ti)
{
 int32 addr_ti, tevp_reg_ti, trigger_ti, cint_ti; 
 int32 mindel_low_ti, mindel_high_ti, t1_ti, t2_ti, eq_ti;
 int32 biti_ti, srtyp;
 size_t offset;
 struct tev_t *tevp;
 struct bblk_t *chk_trigger_bbp;
 struct bblk_t *schedule_bbp, *reschedule_bbp;
 struct bblk_t *delay_assign_bbp;

//AIV 01/13/12 - LOOKATME - was reloading newscalw_ti from __new_gateval here
//think to save some register pressure ???? now just passing

 /* AIV 05/19/08 - could pass this value down but reloading to remove */
 /* some of the register pressure from gen_get_path_del */
 /* this is known to be in __new_gateval so reload here */
 if (np->n_2state) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;
 addr_ti = __ldvar_addr(np, NULL);

 /* AIV 01/12/12 - if path contains condition codes */
 if (chk_path_set)
  {
   /* if none set __pdmindel will be max */
   /* return NULL - no path will do assign without delay */
   /* if (__mindel == 0xffffffffffffffff) */
   cint_ti = __gen_cint_tn(0xffffffff);
   mindel_low_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_PDMINDEL);
   t1_ti = __emit_bin_bitxor(WBITS, cint_ti, mindel_low_ti);


   mindel_high_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_PDMINDEL_HIGH);
   t2_ti = __emit_bin_bitxor(WBITS, cint_ti, mindel_high_ti);
   eq_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);

   delay_assign_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(le_simtime_bbp, delay_assign_bbp, eq_ti);
   __start_bblk(delay_assign_bbp);
  }
 chk_trigger_bbp = __alloc_bblk(FALSE);
 schedule_bbp = __alloc_bblk(FALSE);
 reschedule_bbp = __alloc_bblk(FALSE);

 /* if (__cvc_newdel <= __simtime) */
 /*
    {
     bp = (byte *) &(__idp[np->nva_ofs]);
     *bp = (byte) nval; 
     asl_loc_record_nchg(np, nchglp);
     return;
    }
  */
 __emit_jmp_cmp64_newdel_lte_simtim(le_simtime_bbp, chk_trigger_bbp, 
  newtime_low_ti, newtime_high_ti);

 __start_bblk(le_simtime_bbp);
 if (bi == -1)
  {
   /* DBG remove -- */
   if (np->srep != SR_SCAL && np->srep != SR_SSCAL && np->srep != SR_SCAL2S) 
     __misc_terr(__FILE__, __LINE__);
   /* ---- */
   /* AIV 02/23/09 - this is known to have changed here since it is */
   /* checked prior to calling this - so just assigna and record */
   __emit_copy(WRDBYTES, newscalw_ti, addr_ti);
   __gen_record_const_nchg(np, -1, -1, done_bbp);
  }
 else 
  {
   /* AIV 06/05/08 - this is known constant not variable case */
   assign_bit_to_net(np, bi, newscalw_ti);
  }
 __emit_jmp(done_bbp);
 
 __start_bblk(chk_trigger_bbp);
 /* if (tevp->trigger) */
 tevp_reg_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, ctevp_ti);
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
   
 trigger_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, tevp_reg_ti, offset);

 __emit_jmp_0(schedule_bbp, reschedule_bbp, trigger_ti); 

 __start_bblk(schedule_bbp);
 offset = (byte *) &(tevp->etime) - (byte *) tevp;
  __st_insn(I_STOREA, AM_REG, newtime_low_ti, AM_NDXREG_DISP, tevp_reg_ti, 
    offset);
  __st_insn(I_STOREA, AM_REG, newtime_high_ti, AM_NDXREG_DISP, tevp_reg_ti, 
    offset+WRDBYTES);
//AIV FIXME - these should be init in fixed events no reason to set here
//tevp->tu.bi could then just use one wrapper 
//notice the same except passing bit value
//these are always constant here
 if (bi == -1)
  {
   __emit_schedule_scalar_1wev(tevp_reg_ti);
  }
 else 
  {
   biti_ti = __gen_cint_tn(bi);
   __emit_schedule_1wev(tevp_reg_ti, biti_ti);
  }
 __emit_jmp(done_bbp);

 __start_bblk(reschedule_bbp);
 /* notice scalar and vector the same */
 __emit_reschedule_1wev32(tevp_reg_ti, newtime_low_ti, newtime_high_ti);
 __emit_jmp(done_bbp);
}
#else

/*
 * AIV 01/13/12 - rewrote this to check for condition code here at
 * path selection
 */
static int32 gen_get_path_del64(struct net_t *np, int32 *val_ti, int32 bi,
 int32 newscalw_ti, int32 oldscalw_ti, struct bblk_t *assign_bbp)
{
 int32 idplast_ti, newdel_ti, pdmindel_ti, pdlatchgtim_ti; 
 int32 t1_ti, t2_ti, ndx_ti, cint_ti, one_path; 
 int32 chk_path_set, has_path_cond, cond_ti;
 word64 del;
 struct pthdst_t *pdp;
 struct spcpth_t *pthp;
 struct rngdwir_t *dwirp; 
 struct tchg_t *tchgp;
 struct bblk_t *next_bbp, *get_newdel_bbp, *eq_bbp, *not_eq_bbp;
 struct bblk_t *set_pdmindel_bbp, *use_bbp;
 struct bblk_t *cond_notzero_bbp;
 struct expr_t *condx;

 dwirp = np->nu.rngdwir;
 pdp = dwirp->n_du.pb_pthdst[bi];
 /* DBG remove -- */
 if (pdp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 
 /* need to check if any on path has a if(cond) condition */
 pdmindel_ti = -1;
 chk_path_set = FALSE;
 has_path_cond = any_on_path_cond(pdp);
 /* if all paths are the same delay can produce better code */
 if (all_paths_same(pdp, &del)) 
  {
   chk_path_set = gen_get_path_del64_const(np, val_ti, bi, del, has_path_cond,
    assign_bbp);
   return(chk_path_set);
  }

 /* if has any cond set flag to false */
 if (has_path_cond) chk_path_set = TRUE;

 pthp = pdp->pstchgp->chgu.chgpthp;
 condx = pthp->pthcondx;
 one_path = (pdp->pdnxt == NULL);
 /* AIV 03/09/09 - if all paths are the same only compute the index once */
 if (is_path_same_delrep(pdp))
  {
   ndx_ti = -1;
   /* if first one was a cond this may never get executed - and it needs to */
   /* compute the index for the first time - if it has a cond this may */
   /* never get computed so need to do it for the first time */
   if (condx != NULL && !one_path)
    {
     gen_get_del64(np, &pdmindel_ti, pthp->pth_du, pthp->pth_delrep, 
       pthp->spcpth_id, &ndx_ti, newscalw_ti, oldscalw_ti, !one_path);
    }
  }
 else ndx_ti = FALSE;

 /* common case there is only one */
 tchgp = pdp->pstchgp;

 pdlatchgtim_ti = __gen_tn(SR_CINT, WBITS);
 /* AIV 01/13/12 - just init this to largest and smallest - this saves */
 /* an additional if stmt inside the loop */
 /* __pdmindel = MAXTIME; __pdlatechgtim = 0; */
 if (!one_path) 
  {
   cint_ti = __gen_cint_tn(0);
   __emit_copy(WRDBYTES, cint_ti, pdlatchgtim_ti);

   cint_ti = __gen_cint_tn(MAXTIME);
   __st_insn(I_STOREQ, AM_REG, cint_ti, AM_NLO, NLO_PDMINDEL);
  }

 /*
  w64p = (word64 *) &(__idp[pdp->pstchgp->lastchg_ofs]);
  pdlatechgtim = *w64p;
  __pdmindel = __get_del(pthp->pth_du, pthp->pth_delrep);
 */
 idplast_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*(tchgp->lastchg_ofs));
 if (condx != NULL)
  {
   cond_notzero_bbp = __alloc_bblk(FALSE);
   if (one_path) use_bbp = assign_bbp;
   else use_bbp = __alloc_bblk(FALSE);

   cond_ti = __gen_expr_eval(condx, -1);

   cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
      FALSE);
   __emit_jmp_0(use_bbp, cond_notzero_bbp, cond_ti);
   __start_bblk(cond_notzero_bbp);
   gen_get_del64(np, &pdmindel_ti, pthp->pth_du, pthp->pth_delrep, 
     pthp->spcpth_id, &ndx_ti, newscalw_ti, oldscalw_ti, !one_path);
   if (!one_path) __emit_copy(WRDBYTES, idplast_ti, pdlatchgtim_ti);
   __st_insn(I_STOREQ, AM_REG, pdmindel_ti, AM_NLO, NLO_PDMINDEL);
   /* if skipping block just set time to 0 and return -1 */
   /* this works because new time will be 0 <= __simtime */
   /* this saves a compare */
   if (one_path) 
    {
     /* __cvc_newdel = pdlatechgtim + __pdmindel; */
     /* do a 64-bit add */
     *val_ti = __emit_add(WBITS, idplast_ti, pdmindel_ti);
     return(-1);
    }
   __start_bblk(use_bbp);
  }
 else
  {
   gen_get_del64(np, &pdmindel_ti, pthp->pth_du, pthp->pth_delrep, 
     pthp->spcpth_id, &ndx_ti, newscalw_ti, oldscalw_ti, !one_path);
   __st_insn(I_STOREQ, AM_REG, pdmindel_ti, AM_NLO, NLO_PDMINDEL);
   if (one_path) 
    {
     /* __cvc_newdel = pdlatechgtim + __pdmindel; */
     /* do a 64-bit add */
     *val_ti = __emit_add(WBITS, idplast_ti, pdmindel_ti);
     return(chk_path_set);
    }
    __emit_copy(WRDBYTES, idplast_ti, pdlatchgtim_ti);
  }


 next_bbp = __alloc_bblk(FALSE);
 get_newdel_bbp = __alloc_bblk(FALSE);
 eq_bbp = __alloc_bblk(FALSE);
 not_eq_bbp = __alloc_bblk(FALSE);
 set_pdmindel_bbp = __alloc_bblk(FALSE);

 for (pdp = pdp->pdnxt; pdp != NULL; pdp = pdp->pdnxt)
  {
   tchgp = pdp->pstchgp;
   pthp = pdp->pstchgp->chgu.chgpthp;
   /* AIV 01/13/12 must check the condition */
   condx = pthp->pthcondx;
   if (condx != NULL)
    {
     cond_notzero_bbp = __alloc_bblk(FALSE);
     cond_ti = __gen_expr_eval(condx, -1);

     cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
       FALSE);
     __emit_jmp_0(next_bbp, cond_notzero_bbp, cond_ti);
     __start_bblk(cond_notzero_bbp);
    }

   idplast_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
     WRDBYTES*(tchgp->lastchg_ofs));
   /* lastchg_time = *((word64 *) &(__idp[pdp->pstchgp->lastchg_ofs])); */
   /* if (lastchg_time < pdlatechgtim) continue; */
   __emit_jmp_cmp(next_bbp, get_newdel_bbp, idplast_ti, pdlatchgtim_ti, CC_JLT);

   __start_bblk(get_newdel_bbp);

   /* newdel = __get_del(pthp->pth_du, pthp->pth_delrep); */
   gen_get_del64(np, &newdel_ti, pthp->pth_du, 
      pthp->pth_delrep, pthp->spcpth_id, &ndx_ti, newscalw_ti, 
      oldscalw_ti, FALSE);

   /* if (lastchg_time == pdlatechgtim) */
   t1_ti = __emit_bin_bitxor(WBITS, idplast_ti, pdlatchgtim_ti);
   __emit_jmp_0(eq_bbp, not_eq_bbp, t1_ti);
   __start_bblk(eq_bbp);

   /* if (newdel > __pdmindel) continue; */
   /* if it is comparing a literal value must do special 64-bit compare */
   t2_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_PDMINDEL);
   __emit_jmp_cmp(next_bbp, set_pdmindel_bbp, newdel_ti, t2_ti, CC_JGT);
   
   /* pdlatechgtim = lastchg_time; */
   __start_bblk(not_eq_bbp);
   __emit_copy(WRDBYTES, idplast_ti, pdlatchgtim_ti);
   __emit_jmp(set_pdmindel_bbp);

   /* __pdmindel = newdel; */
   __start_bblk(set_pdmindel_bbp);
   __st_insn(I_STOREQ, AM_REG, newdel_ti, AM_NLO, NLO_PDMINDEL);

   __emit_jmp(next_bbp);
   /* AIV 03/07/12 - there is no reason to check for this because if the time */
   /* is the same will can just set to the same value again */
   /* if (pthp->pth_ifnone && newdel == __pdmindel) continue; */
   /* if (pthp->pth_ifnone) __misc_terr(__FILE__, __LINE__); */
    
   __start_bblk(next_bbp);
   if (pdp->pdnxt != NULL) 
    {
     next_bbp = __alloc_bblk(FALSE);
     get_newdel_bbp = __alloc_bblk(FALSE);
     eq_bbp = __alloc_bblk(FALSE);
     not_eq_bbp = __alloc_bblk(FALSE);
     set_pdmindel_bbp = __alloc_bblk(FALSE);
    }
  }

 /* __cvc_newdel = pdlatechgtim + __pdmindel; */
 t2_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_PDMINDEL);
 *val_ti = __emit_add(WBITS, t2_ti, pdlatchgtim_ti);
 return(chk_path_set);
}

/*
 * 64-bit version
 * get the delay were all delays are known to be the same
 * if all paths are the same delay can produce better code 
 *
 * AIV 01/13/12 - rewrote this to check for condition code here at
 * path selection
 */
static int32 gen_get_path_del64_const(struct net_t *np, int32 *val_ti, int32 bi,
 word64 del, int32 has_path_cond, struct bblk_t *assign_bbp)
{
 int32 idplast_ti, pdmindel_const_ti, pdlatchgtim_ti, chk_path_set, cond_ti; 
 int32 cint_ti, one_path;
 struct pthdst_t *pdp;
 struct spcpth_t *pthp;
 struct rngdwir_t *dwirp; 
 struct tchg_t *tchgp;
 struct bblk_t *next_bbp, *set_newdel_bbp;
 struct bblk_t *cond_notzero_bbp, *use_bbp;
 struct expr_t *condx;

 dwirp = np->nu.rngdwir;
 pdp = dwirp->n_du.pb_pthdst[bi];
 /* DBG remove -- */
 if (pdp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 
 chk_path_set = FALSE;
 /* if has cond set all set to false */
 if (has_path_cond) chk_path_set = TRUE;

/*
 w64p = (word64 *) &(__idp[pdp->pstchgp->lastchg_ofs]);
 pdlatechgtim = *w64p;
 pthp = pdp->pstchgp->chgu.chgpthp;
 __pdmindel = __get_del(pthp->pth_du, pthp->pth_delrep);
*/
 pthp = pdp->pstchgp->chgu.chgpthp;
 tchgp = pdp->pstchgp;

 one_path = (pdp->pdnxt == NULL);
 pdmindel_const_ti = __gen_cint_tn(del);
 if (!one_path) 
  {
   pdlatchgtim_ti = __gen_tn(SR_CINT, WBITS);
   cint_ti = __gen_cint_tn(0);
   __emit_copy(WRDBYTES, cint_ti, pdlatchgtim_ti);
  }

 condx = pthp->pthcondx;
 idplast_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
   WRDBYTES*(tchgp->lastchg_ofs));
 if (condx != NULL)
  {
   cond_notzero_bbp = __alloc_bblk(FALSE);

   if (one_path) use_bbp = assign_bbp;
   else use_bbp = __alloc_bblk(FALSE);

   cond_ti = __gen_expr_eval(condx, -1);

   cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
      FALSE);
   __emit_jmp_0(use_bbp, cond_notzero_bbp, cond_ti);
   __start_bblk(cond_notzero_bbp);
   /* AIV 01/16/12 - need to set __pdmindel here */
   __st_insn(I_STOREQ, AM_REG, pdmindel_const_ti, AM_NLO, NLO_PDMINDEL);
   /* 
    w64p = (word64 *) &(__idp[pdp->pstchgp->lastchg_ofs]);
    pdlatechgtim = *w64p;
   */
   if (!one_path) __emit_copy(WRDBYTES, idplast_ti, pdlatchgtim_ti);

   /* if skipping block just set time to 0 and return -1 */
   /* this works because new time will be 0 <= __simtime */
   /* this saves a compare */
   if (one_path) 
    {
     /* __cvc_newdel = pdlatechgtim + __pdmindel; */
     /* do a 64-bit add */
     *val_ti = __emit_add(WBITS, idplast_ti, pdmindel_const_ti);
     return(-1);
    }
   __start_bblk(use_bbp);
  }
 else
  {
   __st_insn(I_STOREQ, AM_REG, pdmindel_const_ti, AM_NLO, NLO_PDMINDEL);
   /* common case there is only one */
   if (one_path) 
    {
     /* __cvc_newdel = pdlatechgtim + __pdmindel; */
     /* do a 64-bit add */
     *val_ti = __emit_add(WBITS, idplast_ti, pdmindel_const_ti);
     return(chk_path_set);
    }
    __emit_copy(WRDBYTES, idplast_ti, pdlatchgtim_ti);
  }

 next_bbp = __alloc_bblk(FALSE);
 set_newdel_bbp = __alloc_bblk(FALSE);

 for (pdp = pdp->pdnxt; pdp != NULL; pdp = pdp->pdnxt)
  {
   pthp = pdp->pstchgp->chgu.chgpthp;
   condx = pthp->pthcondx;
   tchgp = pdp->pstchgp;
   if (condx != NULL)
    {
     cond_notzero_bbp = __alloc_bblk(FALSE);
     cond_ti = __gen_expr_eval(condx, -1);

     cond_ti = __gen_cnvt_srep_ifneeded(cond_ti, SR_SCAL, WBITS, FALSE, FALSE, 
       FALSE);
     __emit_jmp_0(next_bbp, cond_notzero_bbp, cond_ti);
     __start_bblk(cond_notzero_bbp);
    }

   idplast_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
     WRDBYTES*(tchgp->lastchg_ofs));
   /* lastchg_time = *((word64 *) &(__idp[pdp->pstchgp->lastchg_ofs])); */
   /* if (lastchg_time < pdlatechgtim) continue; */
   __emit_jmp_cmp(next_bbp, set_newdel_bbp, idplast_ti, pdlatchgtim_ti, CC_JLT);

   __start_bblk(set_newdel_bbp);

   __emit_copy(WRDBYTES, idplast_ti, pdlatchgtim_ti);
   /* AIV 03/07/12 - there is no reason to check for this because if the time */
   /* is the same will can just set to the same value again */
   /* if (pthp->pth_ifnone && newdel == __pdmindel) continue; */
   /* if (pthp->pth_ifnone) __misc_terr(__FILE__, __LINE__); */
    
   __start_bblk(next_bbp);
   if (pdp->pdnxt != NULL) 
    {
     next_bbp = __alloc_bblk(FALSE);
     set_newdel_bbp = __alloc_bblk(FALSE);
    }
  }

 /* __cvc_newdel = pdlatechgtim + __pdmindel; */
 *val_ti = __emit_add(WBITS, pdmindel_const_ti, pdlatchgtim_ti);
 return(chk_path_set);
}

/*
 * generate a 64-bit delay according to type placing the low word
 * in del_low_ti and the high word in del_high_ti
 *  
 * return TRUE if constant (currently just DT_1v)
 *
 * AIV 03/09/09 - changed this to reflect changes in 32-bit version.  
 *
 * AIV FIXME - specnetdrvstren.v 
 * cannot just use np->n_stren for some reason???? 
 * this should work __new_gateval sometimes has strength driven by strength
 * must always mask - not a big deal to just do the andl's
 */
static int32 gen_get_del64(struct net_t *np, int32 *del_ti, union del_u du, 
 int32 drep, int32 del_id, int32 *ndx_ti, int32 new_gateval_ti, 
 int32 old_gateval_ti, int32 has_next)
{
 int32 val_ti, t1_ti, t2_ti, cint_ti, ind_ti;
 int32 inum_ti, t3_ti, t4_ti, is_const;
 int32 del_du_ti;
 word64 del;

 /* DBG remove -- */
 if (MD_INUM != 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 
 *del_ti = -1;
 
 is_const = FALSE;
 if (is_one_path_same(du, drep, &del))
  {
   is_const = TRUE;
  }
 else if (drep == DT_1V)
  {
   del = du.d1v[0]; 
   is_const = TRUE;
  }

 if (is_const)
  {
   *del_ti = __gen_cint_tn(del);

   /* AIV 08/12/09 - if index is -1 for the first time and the first is */
   /* folded *ndx_ti has never been set later uses - only compute */
   /* the index once if same drep type */
   /* duplicated code - but only one switch needed could make routine ??? */
   if (*ndx_ti == -1 && has_next) 
    {
     switch ((byte) drep) {
      case DT_IS1V: 
       /* del = du.dis1v[inum]; */
       inum_ti = __emit_inum();
       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS1V2:
       /* del = (word64) du.dis1v2[inum]; */
       inum_ti = __emit_inum();
       cint_ti = __gen_cint_tn(2);
       ind_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_4V:
       /* del = du.d4v[__new_gateval & 3]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, new_gateval_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS4V:
       /* del = du.d4v[4*inum + (__new_gateval & 3)]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       /* t1 = 4*inum */
       cint_ti = __gen_cint_tn(4);
       inum_ti = __emit_inum();
       t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
        t2_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
        cint_ti = __gen_cint_tn(8);
        ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
        /* AIV 07/22/09 - this should be here - was wrong */
        *ndx_ti = ind_ti;
        break;
      case DT_IS4V1:
       /* del = (word64) du.dis4v1[4*inum + (__new_gateval & 3)]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       /* t1 = 4*inum */
       cint_ti = __gen_cint_tn(4);
       inum_ti = __emit_inum();
       t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       ind_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS4V2:
       /* del = (word64) du.dis4v2[4*inum + (__new_gateval & 3)]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       /* t1 = 4*inum */
       cint_ti = __gen_cint_tn(4);
       inum_ti = __emit_inum();
       t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       t2_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
       cint_ti = __gen_cint_tn(2);
       ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_16V:
/* ind = 16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) &0xf); */
/* del = du.dis16v[ind]; */
        if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
        }
       t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS16V:
/* ind = 16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) &0xf); */
/* del = du.dis16v[ind]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
        }
       t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
    
       /* 16*inum */
       cint_ti = __gen_cint_tn(16);
       inum_ti = __emit_inum();
       t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       t4_ti = __emit_add(WBITS, t2_ti, t3_ti);

       cint_ti = __gen_cint_tn(8);
       ind_ti = __emit_mult(WBITS, cint_ti, t4_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS16V1:
       /* ind = 
        16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) & 0xf); */
       /* del = (word64) du.dis16v1[ind]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
        }
       t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);

       /* 16*inum */
       cint_ti = __gen_cint_tn(16);
       inum_ti = __emit_inum();
       t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       ind_ti = __emit_add(WBITS, t2_ti, t3_ti);
       *ndx_ti = ind_ti;
       break;
      case DT_IS16V2:
       /* ind = 
        16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) & 0xf); */
       /* del = (word64) du.dis16v2[ind]; */
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
        }
       cint_ti = __gen_cint_tn(2);
       t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);
      
       if (np == NULL || np->n_stren)
        {
         cint_ti = __gen_cint_tn(3);
         old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
        }
       t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
        
       /* 16*inum */
       cint_ti = __gen_cint_tn(16);
       inum_ti = __emit_inum();
       t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
       t4_ti = __emit_add(WBITS, t2_ti, t3_ti);

       cint_ti = __gen_cint_tn(2);
       ind_ti = __emit_mult(WBITS, cint_ti, t4_ti);
       *ndx_ti = ind_ti;
       break;
      /* notice these last two - use the expression eval so inum is passed */
      /* global __inum must be set */
      case DT_1V:
      case DT_IS1V1:
      case DT_1X:
      case DT_4X:
       break;
      default: __case_terr(__FILE__, __LINE__);
     }
    }
   return(TRUE);
  }

 del_du_ti = __gen_del_tn(del_id, (void *) du.d4v);
 switch ((byte) drep) {
  case DT_IS1V: 
   /* del = du.dis1v[inum]; */
   if (*ndx_ti <= 0)
    {
     inum_ti = __emit_inum();
     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS1V1:
   /* del = (word64) du.dis1v1[inum]; */
   inum_ti = __emit_inum();
   val_ti = __emit_add(WBITS, del_du_ti, inum_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, val_ti);
   return(TRUE);
   break;
  case DT_IS1V2:
   /* del = (word64) du.dis1v2[inum]; */
   if (*ndx_ti <= 0)
    {
     inum_ti = __emit_inum();
     cint_ti = __gen_cint_tn(2);
     ind_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, val_ti);
   return(TRUE);
   break;
  case DT_4V:
   /* del = du.d4v[__new_gateval & 3]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, new_gateval_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS4V:
   /* del = du.d4v[4*inum + (__new_gateval & 3)]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     /* t1 = 4*inum */
     cint_ti = __gen_cint_tn(4);
     inum_ti = __emit_inum();
     t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     t2_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
     /* AIV 07/22/09 - this should be here - was wrong */
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS4V1:
   /* del = (word64) du.dis4v1[4*inum + (__new_gateval & 3)]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     /* t1 = 4*inum */
     cint_ti = __gen_cint_tn(4);
     inum_ti = __emit_inum();
     t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     ind_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, val_ti);
   return(TRUE);
   break;
  case DT_IS4V2:
  /* del = (word64) du.dis4v2[4*inum + (__new_gateval & 3)]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     /* t1 = 4*inum */
     cint_ti = __gen_cint_tn(4);
     inum_ti = __emit_inum();
     t1_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     t2_ti = __emit_add(WBITS, t1_ti, new_gateval_ti);
     cint_ti = __gen_cint_tn(2);
     ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, val_ti);
   return(TRUE);
   break;
  case DT_16V:
/* ind = 16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) &0xf); */
/* del = du.dis16v[ind]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
      }
     t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, t2_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS16V:
/* ind = 16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) &0xf); */
/* del = du.dis16v[ind]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
      }
     t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);

     /* 16*inum */
     cint_ti = __gen_cint_tn(16);
     inum_ti = __emit_inum();
     t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     t4_ti = __emit_add(WBITS, t2_ti, t3_ti);

     cint_ti = __gen_cint_tn(8);
     ind_ti = __emit_mult(WBITS, cint_ti, t4_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);

   *del_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, val_ti);
   break;
  case DT_IS16V1:
   /* ind = 
    16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) & 0xf); */
   /* del = (word64) du.dis16v1[ind]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);

     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
      }
     t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);

     /* 16*inum */
     cint_ti = __gen_cint_tn(16);
     inum_ti = __emit_inum();
     t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     ind_ti = __emit_add(WBITS, t2_ti, t3_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);
   *del_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, val_ti);
   return(TRUE);
   break;
  case DT_IS16V2:
   /* ind = 
    16*inum + ((((__new_gateval & 3) << 2) | (__old_gateval & 3)) & 0xf); */
   /* del = (word64) du.dis16v2[ind]; */
   if (*ndx_ti <= 0)
    {
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       new_gateval_ti = __emit_bin_bitand(WBITS, new_gateval_ti, cint_ti);
      }
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, new_gateval_ti);
  
     if (np == NULL || np->n_stren)
      {
       cint_ti = __gen_cint_tn(3);
       old_gateval_ti = __emit_bin_bitand(WBITS, old_gateval_ti, cint_ti);
      }
     t2_ti = __emit_bin_bitor(WBITS, old_gateval_ti, t1_ti);
    
     /* 16*inum */
     cint_ti = __gen_cint_tn(16);
     inum_ti = __emit_inum();
     t3_ti = __emit_mult(WBITS, cint_ti, inum_ti);
     t4_ti = __emit_add(WBITS, t2_ti, t3_ti);

     cint_ti = __gen_cint_tn(2);
     ind_ti = __emit_mult(WBITS, cint_ti, t4_ti);
     if (*ndx_ti == -1) *ndx_ti = ind_ti;
    }
   else ind_ti = *ndx_ti;

   val_ti = __emit_add(WBITS, del_du_ti, ind_ti);

   *del_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, val_ti);
   return(TRUE);
   break;
  /* notice these last two - use the expression eval so inum is passed */
  /* global __inum must be set */
  case DT_1X:
   __emit_get_del64(ASL_GET_DEL_1X, del_ti, del_du_ti);
   break;
  case DT_4X:
   __emit_get_del64(ASL_GET_DEL_4X, del_ti, del_du_ti);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}

 
/*
 * schedule the path delay time for the scalar bit
 */
static void gen_schedule_path_bit64(struct net_t *np, 
 struct bblk_t *done_bbp, int32 ctevp_ti, int32 newtime_ti, int32 bi,
 int32 chk_path_set, struct bblk_t *le_simtime_bbp, int32 newscalw_ti)
{
 int32 addr_ti, tevp_reg_ti, trigger_ti, outv_ti, mindel_ti, cint_ti;
 int32 biti_ti, simtime_ti, srtyp;
 size_t offset;
 struct tev_t *tevp;
 struct bblk_t *chk_trigger_bbp;
 struct bblk_t *chk_outv_bbp, *schedule_bbp, *reschedule_bbp;
 struct bblk_t *delay_assign_bbp;

//AIV 01/13/12 - LOOKATME - was reloading newscalw_ti from __new_gateval here
//think to save some register pressure ???? now just passing

 /* AIV 05/19/08 - could pass this value down but reloading to remove */
 /* some of the register pressure from gen_get_path_del */
 /* this is known to be in __new_gateval so reload here */
 if (np->n_2state) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;
 addr_ti = __ldvar_addr(np, NULL);

 /* AIV 01/12/12 - if path contains condition codes */
 if (chk_path_set)
  {
   /* if none set __pdmindel will be max */
   /* return NULL - no path will do assign without delay */
   /* if (__pdmindel == MAXTIME) do assign; */
   delay_assign_bbp = __alloc_bblk(FALSE);
   mindel_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_PDMINDEL);
   cint_ti = __gen_cint_tn(MAXTIME);
 
   __emit_jmp_eq(le_simtime_bbp, delay_assign_bbp, cint_ti, mindel_ti); 

   __start_bblk(delay_assign_bbp);
  }

 chk_trigger_bbp = __alloc_bblk(FALSE);
 chk_outv_bbp = __alloc_bblk(FALSE);
 schedule_bbp = __alloc_bblk(FALSE);
 reschedule_bbp = __alloc_bblk(FALSE);

 /* if (__cvc_newdel <= __simtime) */
 /*
    {
     bp = (byte *) &(__idp[np->nva_ofs]);
     *bp = (byte) nval; 
     asl_loc_record_nchg(np, nchglp);
     return;
    }
  */

 simtime_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SIMTIME);
 __emit_jmp_cmp(le_simtime_bbp, chk_trigger_bbp, newtime_ti, simtime_ti, 
  CC_JLE);

 __start_bblk(le_simtime_bbp);
 if (bi == -1)
  {
   __gen_chg_st_val(np, addr_ti, newscalw_ti);
  }
 else 
  {
   /* AIV 06/05/08 - this is known constant not variable case */
   assign_bit_to_net(np, bi, newscalw_ti);
  }
 __emit_jmp(done_bbp);
 
 __start_bblk(chk_trigger_bbp);
 /* if (tevp->trigger) */
 tevp_reg_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, ctevp_ti);
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 trigger_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, tevp_reg_ti, offset);

 __emit_jmp_0(schedule_bbp, chk_outv_bbp, trigger_ti); 

 __start_bblk(schedule_bbp);
//AIV FIXME - these should be init in fixed events no reason to set here
//tevp->tu.bi could then just use one wrapper 
//notice the same except passing bit value
//these are always constant here
 /* AIV 03/27/09 - changed from I_STOREQ - which it should be */
 /* was causing problems in v_bbopt.c:insn_offset_acess:503 because */
 /* it had no I_STOREQ - maybe should had ??? AIV FIXME ??? */
 offset = (byte *) &(tevp->etime) - (byte *) tevp;
 __st_insn(I_MOVA, AM_REG, newtime_ti, AM_NDXREG_DISP, tevp_reg_ti, offset);
 if (bi == -1)
  {
   __emit_schedule_scalar_1wev(tevp_reg_ti);
  }
 else 
  {
   biti_ti = __gen_cint_tn(bi);
   __emit_schedule_1wev(tevp_reg_ti, biti_ti);
  }
 __emit_jmp(done_bbp);

 /* if (ptevp->outv == (byte) nval) return; */
 __start_bblk(chk_outv_bbp);
 offset = (byte *) &(tevp->outv) - (byte *) tevp;
 outv_ti = __move_insn(TN_VAL, I_MOVB, AM_NDXREG_DISP, tevp_reg_ti, offset);
 __emit_jmp_byte_eq(done_bbp, reschedule_bbp, outv_ti, newscalw_ti); 

 __start_bblk(reschedule_bbp);
 /* notice scalar and vector the same */
 __emit_reschedule_1wev64(tevp_reg_ti, newtime_ti);
 __emit_jmp(done_bbp);
}

#endif

 
/* 
 * return TRUE if any path has a condition
 */
static int32 any_on_path_cond(struct pthdst_t *pdp_hdr)
{
 struct pthdst_t *pdp;

 for (pdp = pdp_hdr; pdp != NULL; pdp = pdp->pdnxt)
  {
   if (pdp->pstchgp->chgu.chgpthp->pthcondx != NULL) return(TRUE);
  }
 return(FALSE);
}

/*
 * check if all delays on the paths are the same value
 * return TRUE if all delays are the same
 */
static int32 all_paths_same(struct pthdst_t *pdp, word64 *val)
{
 word64 firstdel, del;
 struct spcpth_t *pthp;
 
 pthp = pdp->pstchgp->chgu.chgpthp;
 if (!is_one_path_same(pthp->pth_du, pthp->pth_delrep, &firstdel))
  {
   return(FALSE);
  }

 for (pdp = pdp->pdnxt;pdp != NULL; pdp = pdp->pdnxt)
  {
   /* AIV 08/11/09 - this was always using the first one - need to set */
   /* pthp again inside of loop */
   pthp = pdp->pstchgp->chgu.chgpthp;
   if (!is_one_path_same(pthp->pth_du, pthp->pth_delrep, &del))
    {
     return(FALSE);
    }
   if (firstdel != del) return(FALSE);
  }
 *val = firstdel;
 return(TRUE);
}

/*
 * check one path to see if all delay values are the same
 * return TRUE if delay is the same for all 16 scalar values
 */
static int32 is_one_path_same(union del_u du, int32 drep, word64 *val)
{
 word64 firstdel, del;
 int32 i, j, inum;

 /* cannot handle expression delays here */
 if (drep == DT_1X || drep == DT_4X) return(FALSE);

 /* AIV 08/19/09 - think this was incorrectly folding the wrong values */
 /* need to check each instance for delay values */
 /* easy way to do this is just check all 16 scalar values for the same */
 /* delay for all the values */
 /* AIV 11/09/11 - really this should use ALL1W not -1 */
 firstdel = ALL1W;
 for (inum = 0; inum < __inst_mod->flatinum; inum++)
  {
   for (i = 0; i < 4; i++)
    {
     __new_gateval = i;
     for (j = 0; j < 4; j++)
      {
       if (i == j) continue;
  
       __old_gateval = j;
       del = __get_del_inum(du, drep, inum);
       if (firstdel == ALL1W) firstdel = del;
  
       if (del != firstdel) 
        {
         __new_gateval = __old_gateval = 0;
         return(FALSE);
        }
      }
    }
  }
 __new_gateval = __old_gateval = 0;
 *val = firstdel;
 return(TRUE);
}
 
/*
 * return TRUE if path delay types are all the same
 */
static int32 is_path_same_delrep(struct pthdst_t *pdp)
{
 int32 firstrep;
 struct spcpth_t *pthp;
 
 pthp = pdp->pstchgp->chgu.chgpthp;

 firstrep = pthp->pth_delrep;
 for (pdp = pdp->pdnxt;pdp != NULL; pdp = pdp->pdnxt)
  {
   pthp = pdp->pstchgp->chgu.chgpthp;
   if (firstrep != pthp->pth_delrep) return(FALSE);
  }
 return(TRUE);
}


/*
 * generate stren schd vinsn for 1 fixed constant index bit 
 * for either specify path delay or bit of entire wire, wire delay
 */
static void gen_stren_1bit_schd(struct net_t *np, int32 np_ti, int32 bi, 
 int32 newsbp_ti, int32 oldsbp_ti)
{
 int32 svecadr_ti, svecadr2_ti, newscalw_ti, oldscalw_ti, cint_ti, nchg_ti;
 int32 enter_ti, ctevp_ti;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 cint_ti = __gen_cint_tn(bi);
 svecadr_ti = __con_adradd_insn(SR_SVEC, np->nwid, oldsbp_ti, bi);
 oldscalw_ti = __emit_movint_fr_svec(svecadr_ti);

 svecadr2_ti = __con_adradd_insn(SR_SVEC, np->nwid, newsbp_ti, bi);
 newscalw_ti = __emit_movint_fr_svec(svecadr2_ti);

 ncp = __gen_netchg_addr_tn(np, bi, bi, TRUE, &nchg_ti);
 enter_ti = __gen_process_wire_enter(ncp->ndx);

 ctevp = np->ndel_ctevtab[bi];
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

 if (np->nu.rngdwir->n_delrep == DT_PTHDST)
  {
   __emit_stren_sched_1pthbit(np_ti, cint_ti, newscalw_ti, oldscalw_ti, 
     nchg_ti, ctevp_ti);
  }
 else
  {
   /* never trireg */
   __emit_stren_sched_1wirbit(np_ti, cint_ti, newscalw_ti, oldscalw_ti,
    ctevp_ti);
  }
}

/*
 * gen vinsns to schedule an entire wire (for both specify pth del and wire)
 * non stren case
 */
static void gen_schd_allofwire(struct net_t *np, int32 new_apti, int32 blen) 
{
 int32 addr_apti, oscalw_ti, np_ti, nchg_ti, ctevp_ti;
 int32 bi, cint_ti, cint2_ti, enter_ti, rhswid; 
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 np_ti = __ld_netadr_tn(np);
 addr_apti = __ldvar_addr(np, NULL);
 if (!np->n_isavec)
  {
   gen_scalar_sched(np, np_ti, new_apti, addr_apti);
   return;
  }
 
 /* vector cases */ 
 /* AIV 01/11/12 - this was wrong - only need to assign to width of the rhs */
 rhswid = __get_tnwid(new_apti);

 /* SJM 07/20/05 - LOOKATME - should maybe add inc insns */ 
 for (bi = 0; bi < rhswid; bi++)
  {
   /* although non stren wdel sched entire wire, decomposed to per bit here */ 
   gen_1bit_sched(np, np_ti, bi, new_apti, addr_apti);
  }
 if (blen >= np->nwid) return;

 for (bi = blen; bi < np->nwid; bi++)
  {
   /* AIV 11/10/09 - this should be just call scalar bsel */
   oscalw_ti = __gen_rhs_bsel_scalar_const(np, addr_apti, bi);

   cint2_ti = __gen_cint_tn(2);
   ncp = __gen_netchg_addr_tn(np, bi, bi, TRUE, &nchg_ti);
   enter_ti = __gen_process_wire_enter(ncp->ndx);

   ctevp = np->ndel_ctevtab[bi];
   ctevp_ti = __gen_ctevp_adr_tn(ctevp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

   if (np->nu.rngdwir->n_delrep == DT_PTHDST)
    {
     gen_sched_vector_1pthbit(np, np_ti, cint2_ti, oscalw_ti, nchg_ti, 
       ctevp_ti, bi);
    }
   else
    {
     cint_ti = __gen_cint_tn(bi);
     __emit_sched_1wirbit(np_ti, cint_ti, cint2_ti, oscalw_ti, ctevp_ti);
    }
  }
}


/*
 * generate path schd vinsn for scalar (non stren)
 */
static void gen_scalar_sched(struct net_t *np, int32 np_ti, int32 new_apti, 
 int32 addr_apti)
{
 int32 nscalw_ti, oscalw_ti, cint_ti, nchg_ti, enter_ti, ctevp_ti;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 if (np->n_2state) 
  {
   nscalw_ti = __gen_cnvt_ab_vec_to_scalar_2state(new_apti);
   oscalw_ti = __gen_cnvt_ab_vec_to_scalar_2state(addr_apti);
  }
 else
  {
   nscalw_ti = __gen_cnvt_ab_vec_to_scalar(new_apti);
   oscalw_ti = __gen_cnvt_ab_vec_to_scalar(addr_apti);
  }

 ctevp = np->ndel_ctevtab[0];

 /* DBG remove -- */
 if (np->n_isavec) __misc_terr(__FILE__, __LINE__);
 //ncp = __gen_netchg_addr_tn(np, 0, 0, TRUE, &nchg_ti);
 /* -- */

 ncp = __gen_netchg_addr_tn(np, -1, -1, TRUE, &nchg_ti);
 enter_ti = __gen_process_wire_enter(ncp->ndx);
 
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;
 /* AIV 08/19/10 - may have to convert from 4-state to 2-state */
 if (np->n_2state)
  {
   nscalw_ti = __gen_cnvt_srep_ifneeded(nscalw_ti, np->srep, 1, 
     FALSE, FALSE, FALSE);
  }

 if (np->nu.rngdwir->n_delrep == DT_PTHDST)
  {
   gen_sched_scalar_1pthbit(np, np_ti, nscalw_ti, oscalw_ti, nchg_ti, 
    ctevp_ti, np->n_stren);
  }
 else
  {
   cint_ti = __gen_cint_tn(0);
   __emit_sched_1wirbit(np_ti, cint_ti, nscalw_ti, oscalw_ti, ctevp_ti);
  }
}

/*
 * generate path schd vinsn for 1 fixed constant index bit (non stren)
 */
static void gen_1bit_sched(struct net_t *np, int32 np_ti, int32 bi, 
 int32 new_apti, int32 addr_apti)
{
 int32 oscalw_ti, nscalw_ti, cint_ti, nchg_ti, srtyp;
 int32 enter_ti, ctevp_ti;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 /* AIV 08/27/08 - use the scalar version of bsel const */
 /* AIV 09/08/08 - can have scalar new_apti - rare case */
 srtyp = __tntab[new_apti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   nscalw_ti = new_apti;
  }
 else nscalw_ti = __gen_rhs_bsel_scalar_const(np, new_apti, bi); 
 oscalw_ti = __gen_rhs_bsel_scalar_const(np, addr_apti, bi);

 ncp = __gen_netchg_addr_tn(np, bi, bi, TRUE, &nchg_ti);
 enter_ti = __gen_process_wire_enter(ncp->ndx);

 ctevp = np->ndel_ctevtab[bi];
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

 if (np->nu.rngdwir->n_delrep == DT_PTHDST)
  {
   gen_sched_vector_1pthbit(np, np_ti, nscalw_ti, oscalw_ti, nchg_ti, 
     ctevp_ti, bi);
  }
 else
  {
   cint_ti = __gen_cint_tn(bi);
   __emit_sched_1wirbit(np_ti, cint_ti, nscalw_ti, oscalw_ti, ctevp_ti);
  }
}

/*
 * generate a path delay for one bit of a vector
 * almost the same as scalar version
 * expecpt checking to make sure has path and operation on the fixed bit bi
 */
static void gen_sched_vector_1pthbit(struct net_t *np, int32 np_ti, 
 int32 newscalw_ti, int32 oldscalw_ti, int32 nchg_ti, int32 ctevp_ti, int32 bi)
{
 int32 has_msg, trigger_ti, tevp_reg_ti, biti_ti, chk_path_set;
#ifdef __CVC32__
 int32 newtime_low_ti, newtime_high_ti;
#else
 int32 newtime_ti;
#endif
 size_t offset;
 struct bblk_t *eq_bbp, *not_eq_bbp, *done_bbp, *cancel_tev_bbp, *assign_bbp;
 struct tev_t *tevp;

 /* if no path just do the assign */
 if (!bit_has_path(np, bi))
  {
   /* AIV 06/05/08 - this is known constant not variable case */
   assign_bit_to_net(np, bi, newscalw_ti);
   return;
  }

 has_msg = (__warn_cancel_e || __show_cancel_e);
 if (has_msg)
  {
   biti_ti = __gen_cint_tn(bi);
   __emit_sched_1pthbit(np_ti, biti_ti, newscalw_ti, oldscalw_ti, nchg_ti,
    ctevp_ti, np->n_stren);
  return;
 }

 /*
  * if (nval == oval) 
  * { 
  *  if (ptevp->trigger) linkout_tevp(ptevp);
  *  return;
  * }
  */
   
 eq_bbp = __alloc_bblk(FALSE);
 not_eq_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);
 cancel_tev_bbp = __alloc_bblk(FALSE);


 /* nval == oval */
 __emit_jmp_eq(eq_bbp, not_eq_bbp, newscalw_ti, oldscalw_ti); 
 __start_bblk(eq_bbp);

 /* if (tevp->trigger) */
 tevp_reg_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, ctevp_ti);
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 trigger_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, tevp_reg_ti, offset);

 /* cancel event */
 __emit_jmp_0(done_bbp, cancel_tev_bbp, trigger_ti); 
 __start_bblk(cancel_tev_bbp);
 __emit_cancel_ev(ctevp_ti);
 __emit_jmp(done_bbp);

 __start_bblk(not_eq_bbp);
//AIV LOOKATME 01/12/12 - don't think these global settings are needed
//they one was set for 32 and other ifdef for 64
 __emit_set_new_gateval(newscalw_ti);
 __emit_set_old_gateval(oldscalw_ti);
 /* AIV 01/13/12 - this now has to alloc and pass the assign block */
 /* if single path case and cond is false get_path should just jump */
 /* to assign in the schedule path routine */
 assign_bbp = __alloc_bblk(FALSE);
#ifdef __CVC32__
 chk_path_set = gen_get_path_del32(np, &newtime_low_ti, &newtime_high_ti, bi, 
  newscalw_ti, oldscalw_ti, assign_bbp);
 gen_schedule_path_bit32(np, done_bbp, ctevp_ti, newtime_low_ti, 
   newtime_high_ti, bi, chk_path_set, assign_bbp, newscalw_ti);
#else
 chk_path_set = gen_get_path_del64(np, &newtime_ti, bi, newscalw_ti, 
   oldscalw_ti, assign_bbp);
 gen_schedule_path_bit64(np, done_bbp, ctevp_ti, newtime_ti, bi, chk_path_set,
  assign_bbp, newscalw_ti);
#endif
 __start_bblk(done_bbp);
}

/*
 * gen vinsns to schedule later assignment to a stren bit
 *
 * rhs may be wider than one bit
 * this is for both specify delay path schedule and wire delay schedule  
 * runs in reference expr itree loc (changes here for XMR)
 */
static void gen_stren_sched_to_bit(struct net_t *np, struct expr_t *idndp, 
 struct expr_t *ndx, int32 rhs_sbpti)
{
 int32 np_ti, biti_ti, oldsbp_ti, nd_itpop, svecadr_ti, bi, enter_ti;
 int32 oldscalw_ti, save_idp_ti, nchg_ti, ctevp_ti;
 struct bblk_t *schd_unkn_bbp, *schd_del_bbp, *end_bbp;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 if (ndx->optyp == NUMBER)
  {
   bi = __get_comp_num_ndx(ndx);
   gen_stren_sched_to_bit_const(np, idndp, rhs_sbpti, bi);
   return;
  }
 schd_unkn_bbp = __alloc_bblk(FALSE);
 schd_del_bbp = __alloc_bblk(FALSE);
 end_bbp = __alloc_bblk(FALSE);

 /* must eval index in reference itree loc */
 biti_ti = __gen_comp_ndx(np, ndx, schd_unkn_bbp, FALSE);  

 nd_itpop = FALSE;
 save_idp_ti = -1;
 if (idndp->optyp == GLBREF) 
  { 
   rhs_sbpti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_sbpti);
   nd_itpop = TRUE; 
  }

 np_ti = __ld_netadr_tn(np);
 oldsbp_ti = gen_get_stwire_addr(np, NULL);

 ncp = __gen_netchg_addr_tn(np, -1, -1, TRUE, &nchg_ti);
 enter_ti = __gen_process_wire_enter(ncp->ndx);

 __start_bblk(schd_del_bbp);
 svecadr_ti = __var_adradd_insn(SR_SVEC, np->nwid, oldsbp_ti, biti_ti);
 oldscalw_ti = __emit_movint_fr_svec(svecadr_ti);

//AIV PTR FIXME - what about this case -1 entire wire?????? using 0 is this ok
 ctevp = np->ndel_ctevtab[0];
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

 if (np->nu.rngdwir->n_delrep == DT_PTHDST)
  {
   __emit_stren_sched_1pthbit(np_ti, biti_ti, rhs_sbpti, oldscalw_ti, nchg_ti,
    ctevp_ti);
  }
 else
  {
   /* never trireg */
   __emit_stren_sched_1wirbit(np_ti, biti_ti, rhs_sbpti, oldscalw_ti, ctevp_ti);
  }
 __emit_jmp(end_bbp);

 __start_bblk(schd_unkn_bbp);
 /* this may schedule delay for every bit if all changed */
 __emit_stren_sched_unknown_bit(np_ti, rhs_sbpti, oldsbp_ti, nchg_ti, enter_ti);
 __emit_jmp(end_bbp);


 __start_bblk(end_bbp);
 if (nd_itpop) 
  {  
   __gen_restore_idp(save_idp_ti);
   __pop_itstk(); 
  }
}


/*
 * same as non-constant expect skip code for known bi
 */
static void gen_stren_sched_to_bit_const(struct net_t *np, 
 struct expr_t *idndp, int32 rhs_sbpti, int32 bi)
{
 int32 np_ti, oldsbp_ti, nd_itpop, svecadr_ti, nchg_ti;
 int32 oldscalw_ti, cint_ti, save_idp_ti, enter_ti, ctevp_ti;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 nd_itpop = FALSE;
 save_idp_ti = -1;
 if (idndp->optyp == GLBREF) 
  { 
   rhs_sbpti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_sbpti);
   nd_itpop = TRUE; 
  }

 np_ti = __ld_netadr_tn(np);
 oldsbp_ti = gen_get_stwire_addr(np, NULL);

 ncp = __gen_netchg_addr_tn(np, bi, bi, TRUE, &nchg_ti);
 enter_ti = __gen_process_wire_enter(ncp->ndx);
 if (bi == -1)
  {
   /* this may schedule delay for every bit if all changed */
   __emit_stren_sched_unknown_bit(np_ti, rhs_sbpti, oldsbp_ti, nchg_ti, 
    enter_ti);
   return;
  }

 svecadr_ti = __con_adradd_insn(SR_SVEC, np->nwid, oldsbp_ti, bi);

 oldscalw_ti = __emit_movint_fr_svec(svecadr_ti);

 ctevp = np->ndel_ctevtab[bi];
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

 cint_ti = __gen_cint_tn(bi);
 if (np->nu.rngdwir->n_delrep == DT_PTHDST)
  {
   __emit_stren_sched_1pthbit(np_ti, cint_ti, rhs_sbpti, oldscalw_ti, nchg_ti,
    ctevp_ti);
  }
 else
  {
   /* never trireg */
   __emit_stren_sched_1wirbit(np_ti, cint_ti, rhs_sbpti, oldscalw_ti, ctevp_ti);
  }

 if (nd_itpop) 
  {  
   __gen_restore_idp(save_idp_ti);
   __pop_itstk(); 
  }
}

/*
 * gen vinsns to schedule later assignment to a bit (non stren vor
 * ap and bp may be wider than 1 bit 
 */
static void gen_sched_to_bit(struct net_t *np, struct expr_t *idndp, 
 struct expr_t *ndx1, int32 rhs_apti)
{
 int32 biti_ti, np_ti, bi, nd_itpop, oscalw_ti, addr_apti;
 int32 nscalw_ti, enter_ti;
 int32 save_idp_ti, nchg_ti, ctevp_ti, has_msg;
 struct net_chg_t *ncp;
 struct bblk_t *schd_unkn_bbp, *schd_del_bbp, *end_bbp;
 struct ctev_t *ctevp;

 /* better always have an nchg action */
 /* DBG remove -- */
 if (np->nchgaction_ofs == -1) __misc_terr(__FILE__, __LINE__);
 /* -- */

 if (ndx1->optyp == NUMBER)
  {
   bi = __get_comp_num_ndx(ndx1);
   gen_sched_to_bit_const(np, idndp, rhs_apti, bi);
   return;
  }
 schd_unkn_bbp = __alloc_bblk(FALSE);
 schd_del_bbp = __alloc_bblk(FALSE);
 end_bbp = __alloc_bblk(FALSE);

 biti_ti = __gen_comp_ndx(np, ndx1, schd_unkn_bbp, FALSE);

 nd_itpop = FALSE;
 save_idp_ti = -1;
 if (idndp->optyp == GLBREF)
  { 
   rhs_apti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_apti);
   nd_itpop = TRUE;
  }

 ncp = __gen_netchg_addr_tn(np, -1, -1, TRUE, &nchg_ti);

 np_ti = __ld_netadr_tn(np);
 __start_bblk(schd_del_bbp);

 addr_apti = __ldvar_addr(np, NULL);
 /* get the right bit */
 /* AIV 08/27/08 - now a routine which returns a scalar */
 oscalw_ti = __gen_rhs_bsel_scalar_var(np, addr_apti, biti_ti); 

 /* combine the 1 bit as a/b ptr into a word 3 value scalar */
 if (np->n_2state) nscalw_ti = __gen_cnvt_ab_vec_to_scalar_2state(rhs_apti);
 else nscalw_ti = __gen_cnvt_ab_vec_to_scalar(rhs_apti);
   
 ctevp = np->ndel_ctevtab[0];
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);
 enter_ti = __gen_process_wire_enter(ncp->ndx);

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

 if (np->nu.rngdwir->n_delrep == DT_PTHDST)
  {
   /* variable case still uses wrappers */
   has_msg = (__warn_cancel_e || __show_cancel_e);
   if (has_msg)
    {
     __emit_sched_1pthbit(np_ti, biti_ti, nscalw_ti, oscalw_ti, nchg_ti, 
      ctevp_ti, np->n_stren);
    }
   else
    {
     __emit_sched_1pthbit_nomsg(np_ti, biti_ti, nscalw_ti, oscalw_ti, nchg_ti, 
      ctevp_ti);
    }
  }
 else
  {
   __emit_sched_1wirbit(np_ti, biti_ti, nscalw_ti, oscalw_ti, ctevp_ti);
  }
 __emit_jmp(end_bbp);

 __start_bblk(schd_unkn_bbp);
 __emit_sched_unknown_bit(np_ti, rhs_apti, ctevp_ti);
 __emit_jmp(end_bbp);

 __start_bblk(end_bbp);
 if (nd_itpop)
  {  
   __gen_restore_idp(save_idp_ti);
   __pop_itstk(); 
  }
}

/*
 * constant bit selector version
 */
static void gen_sched_to_bit_const(struct net_t *np, struct expr_t *idndp, 
 int32 rhs_apti, int32 bi)
{
 int32 np_ti, nd_itpop, oscalw_ti, addr_apti, nchg_ti, enter_ti;
 int32 nscalw_ti, cint_ti, ctevp_ti;
 int32 save_idp_ti;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 ncp = __gen_netchg_addr_tn(np, bi, bi, TRUE,  &nchg_ti);

 nd_itpop = FALSE;
 save_idp_ti = -1;
 if (idndp->optyp == GLBREF) 
  { 
   rhs_apti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_apti);
   nd_itpop = TRUE; 
  }

 np_ti = __ld_netadr_tn(np);
 
 enter_ti = __gen_process_wire_enter(ncp->ndx);
 ctevp = np->ndel_ctevtab[bi];
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);

 /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
 ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
 ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

 if (bi == -1)
  {
   __emit_sched_unknown_bit(np_ti, rhs_apti, ctevp_ti);
   /* AIV 04/10/07 - must pop here */
   if (nd_itpop)
    {  
     __gen_restore_idp(save_idp_ti);
     __pop_itstk(); 
    }
   return;
  }

 addr_apti = __ldvar_addr(np, NULL);
 /* get the right bit */
 /* AIV 08/27/08 - now have a bsel which returns a scalar value */
 oscalw_ti =  __gen_rhs_bsel_scalar_const(np, addr_apti, bi); 

 /* combine the 1 bit as a/b ptr into a word 3 value scalar */
 if (np->n_2state) nscalw_ti = __gen_cnvt_ab_vec_to_scalar_2state(rhs_apti);
 else nscalw_ti = __gen_cnvt_ab_vec_to_scalar(rhs_apti);

 if (np->nu.rngdwir->n_delrep == DT_PTHDST)
  {
   gen_sched_vector_1pthbit(np, np_ti, nscalw_ti, oscalw_ti, nchg_ti, 
     ctevp_ti, bi);
  }
 else
  {
   cint_ti = __gen_cint_tn(bi);
   __emit_sched_1wirbit(np_ti, cint_ti, nscalw_ti, oscalw_ti, ctevp_ti);
  }

 if (nd_itpop)
  {  
   __gen_restore_idp(save_idp_ti);
   __pop_itstk(); 
  }
}

/*
 * gen vinsns for schedule of later assignment to a stren part select
 *
 * know rhs tmp name width and strengthness exactly matches
 * this is for both specify delay path schedule and wire delay schedule  
 */
static void gen_stren_sched_to_psel(struct expr_t *xlhs, int newsbp_ti)
{
 int32 bi, bi2;
 int32 ri1, ri2, pslen, nd_itpop, np_ti, oldsbp_ti, bi_int_ti;
 int32 oldscalw_ti, svecadr2_ti, newscalw_ti, svecadr_ti, nchg_ti, enter_ti;
 int32 ctevp_ti;
 struct net_t *np;
 int32 save_idp_ti;
 struct expr_t *idndp, *ndx1, *ndx2;
 struct net_chg_t *ncp;
 struct ctev_t *ctevp;

 idndp = xlhs->lu.x;
 np = idndp->lu.sy->el.enp;

 ndx1 = xlhs->ru.x->lu.x;
 ri1 = (int32) __contab[ndx1->ru.xvi];
 ndx2 = xlhs->ru.x->ru.x;
 ri2 = (int32) __contab[ndx2->ru.xvi];
 pslen = ri1 - ri2 + 1;

 nd_itpop = FALSE;
 save_idp_ti = -1;
 if (idndp->optyp == GLBREF) 
  { 
   newsbp_ti = gen_chgtorefgrp(idndp, &save_idp_ti, newsbp_ti);
   nd_itpop = TRUE; 
  }

 np_ti = __ld_netadr_tn(np);
 /* get strength wire address */
 oldsbp_ti = gen_get_stwire_addr(np, NULL);

 for (bi = ri2, bi2 = 0; bi < ri2 + pslen; bi++, bi2++)
  {
   /* notice can't use schedule to bit because bi and bi2 differ */
   svecadr_ti = __con_adradd_insn(SR_SVEC, np->nwid, oldsbp_ti, bi2);
   oldscalw_ti = __emit_movint_fr_svec(svecadr_ti);

   bi_int_ti = __gen_cint_tn(bi);
   svecadr2_ti = __con_adradd_insn(SR_SVEC, np->nwid, newsbp_ti, bi);

   newscalw_ti = __emit_movint_fr_svec(svecadr2_ti);

   ncp = __gen_netchg_addr_tn(np, bi, bi, TRUE,  &nchg_ti);
   enter_ti = __gen_process_wire_enter(ncp->ndx);
   ctevp = np->ndel_ctevtab[bi];
   ctevp_ti = __gen_ctevp_adr_tn(ctevp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

   if (np->nu.rngdwir->n_delrep == DT_PTHDST)
    {
     __emit_stren_sched_1pthbit(np_ti, bi_int_ti, newscalw_ti, oldscalw_ti, 
      nchg_ti, ctevp_ti);
    }
   else
    {
     /* never trireg */
     __emit_stren_sched_1wirbit(np_ti, bi_int_ti, newscalw_ti, oldscalw_ti,
      ctevp_ti);
    }
  }
 if (nd_itpop)
  {  
   __gen_restore_idp(save_idp_ti);
   __pop_itstk(); 
  }
}

/*
 * gen vinsns for schedule of later assignment to a part select
 *
 * know rhs tmp name width and strengthness exactly matches
 * this is for both specify delay path schedule and wire delay schedule  
 */
static void gen_sched_to_psel(struct expr_t *xlhs, int rhs_apti)
{
 int32 bi, bi2;
 int32 ri1, ri2, pslen, nd_itpop, cint_ti, nchg_ti, enter_ti;
 int32 np_ti, addr_apti, nscalw_ti, oscalw_ti, ctevp_ti;
 int32 save_idp_ti;
 struct net_chg_t *ncp;
 struct net_t *np;
 struct expr_t *idndp, *ndx1, *ndx2;
 struct ctev_t *ctevp;

 idndp = xlhs->lu.x;
 np = idndp->lu.sy->el.enp;

 ndx1 = xlhs->ru.x->lu.x;
 ri1 = (int32) __contab[ndx1->ru.xvi];
 ndx2 = xlhs->ru.x->ru.x;
 ri2 = (int32) __contab[ndx2->ru.xvi];
 pslen = ri1 - ri2 + 1;

 nd_itpop = FALSE;
 save_idp_ti = -1;
 if (idndp->optyp == GLBREF) 
  { 
   rhs_apti = gen_chgtorefgrp(idndp, &save_idp_ti, rhs_apti);
   nd_itpop = TRUE;
  }

 np_ti = __ld_netadr_tn(np);
 /* get wire a/bp part address for right instance */
 addr_apti = __ldvar_addr(np, NULL);

 /* schedule for each bit */
 for (bi = ri2, bi2 = 0; bi < ri2 + pslen; bi++, bi2++)
  {
   /* notice can't use schd one bit because bi and bi2 differ */
   /* AIV 08/27/08 - use the scalar version of bsel const */
   oscalw_ti = __gen_rhs_bsel_scalar_const(np, addr_apti, bi2);
   nscalw_ti = __gen_rhs_bsel_scalar_const(np, rhs_apti, bi); 

   ncp = __gen_netchg_addr_tn(np, bi, bi, TRUE,  &nchg_ti);
   enter_ti = __gen_process_wire_enter(ncp->ndx);

   ctevp = np->ndel_ctevtab[bi];
   ctevp_ti = __gen_ctevp_adr_tn(ctevp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[enter_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[enter_ti].comlab_typ;

   if (np->nu.rngdwir->n_delrep == DT_PTHDST)
    {
     gen_sched_vector_1pthbit(np, np_ti, nscalw_ti, oscalw_ti, nchg_ti, 
       ctevp_ti, bi);
    }
   else
    {
     cint_ti = __gen_cint_tn(bi);
     __emit_sched_1wirbit(np_ti, cint_ti, nscalw_ti, oscalw_ti, ctevp_ti);
    }

  }
 if (nd_itpop)
  {  
   __gen_restore_idp(save_idp_ti);
   __pop_itstk(); 
  }
}
     

/*
 * return TRUE if there is a path the the net bi
 */
static int32 bit_has_path(struct net_t *np, int32 bi)
{
 struct rngdwir_t *dwirp; 

 dwirp = np->nu.rngdwir;
 if (dwirp->n_du.pb_pthdst[bi] == NULL) return(FALSE);
 return(TRUE);
}
 
/*
 * assign a net bit the a value
 */
static void assign_bit_to_net(struct net_t *np, int32 bi, int32 val_ti)
{
 int32 addr_apti, vec_ti, srtyp;

 /* should never get an array here */
 /* DBG remove -- */
 if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
 /* ---- */
   
 /* convert scalar to vector */
 if (np->n_2state) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;
 vec_ti = __gen_cnvt_srep_ifneeded(val_ti, srtyp, 1, FALSE, FALSE,
    FALSE); 

 addr_apti = __ldvar_addr(np, NULL);
 /* AIV 06/05/08 - this is known constant not variable case */
 __gen_lhsbsel_const(np, addr_apti, bi, vec_ti);
}

/*
 * 
 * DECL EXPR EVAL VINSN GEN ROUTINES
 */

/*
 * gen vinsns to convert a/b value (even if 1 bit but still stored as a/b)  
 * to stren scalar or vector
 */
static int32 gen_st_standval(int32 blen, int32 apti, byte new_st)
{
 int32 sbp_ti, srtyp;

 srtyp = __tntab[apti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   sbp_ti = __emit_movsb_fr_scalstad(apti, new_st);
   return(sbp_ti);
  }
 /* AIV 08/24/10 - expecting a 4-state value here */
 if (__tmp_is_2state(apti))
  {
   apti = __gen_cnvt_srep_ifneeded(apti, SR_VEC, blen, 
    FALSE, FALSE, FALSE);
  }
 if (blen <= WBITS)
  {
   sbp_ti = __emit_movsb_fr_wstad(blen, apti, new_st);
  }
 else 
  {
   sbp_ti = __emit_movsb_fr_widestad(blen, apti,  new_st);
  }
 return(sbp_ti);
}

/*
 * gen vinsn to evaluate expression where stren is needed
 * always returns address of (ptr to) value - usually just load addr
 *
 * following interpreter nd st eval - eval and add stren caller must
 * handle size and stren changes
 */
static int32 gen_ndst_expr_eval(struct expr_t *ndp)
{
 int32 t3_ti, t1_ti, xpr_ti;
 struct net_t *np;

 if (!ndp->x_stren)
  {
   /* this always loads in a/b form even for scalar - never stren */ 
   t1_ti = __gen_expr_eval(ndp, -1);
   /* AIV 12/22/06 - needs to pass the exact length */
   t3_ti = gen_st_standval(ndp->szu.xclen, t1_ti, ST_STRVAL);
   return(t3_ti);
  }

 xpr_ti = -1;
 /* possible for this to be non stength reg. where strong added */
 /* in this case, must put value on tos */
 switch (ndp->optyp) {
  case UNCONNPULL:
   /* connection is unconnected but directives causes unc. to be pulled */
   /* know width here always exactly port width and stren */
   xpr_ti = __gen_tn(SR_SVEC, ndp->szu.xclen); 
   __emit_setstren(xpr_ti, 
    (ndp->unc_pull == UNCPULL0) ? ST_PULL0 : ST_PULL1, __get_tnwid(xpr_ti));
   break;
  case ID:
   np = ndp->lu.sy->el.enp;
   /* this returns the address of the stren vector */
   xpr_ti = gen_get_stwire_addr(np, NULL);
   break;
  case GLBREF:
   np = ndp->lu.sy->el.enp;
   xpr_ti = gen_get_stwire_addr(np, ndp->ru.grp);
   break;
  case LSB:
   /* can never be array */
   xpr_ti = gen_access_stbsel(ndp);
   break;
  case PARTSEL:
   xpr_ti = gen_access_stpsel(ndp);
   break;
  case PARTSEL_NDX_MINUS:
  case PARTSEL_NDX_PLUS:
//AIV PSEL - strength
  /* should be no strength because decl constant psel are treated as regular */
  /* constant psel */
  __case_terr(__FILE__, __LINE__); 
  /* DBG remove -- 
  np = ndp->lu.x->lu.sy->el.enp;
  if (np->srep != SR_VEC && np->srep != SR_PNUM) 
   __case_terr(__FILE__, __LINE__); 
   ---- */
   break;
  case LCB:
   xpr_ti = rhs_stconcat(ndp);
   break;
  default: xpr_ti = -1; __case_terr(__FILE__, __LINE__);
 }
 return(xpr_ti);
}

/*
 * gen vinsn to load stren net value always into svec value addr 
 *
 * even for scalar, also returns the addr - never copies
 * corresponds to interpreter get stwire addr macro
 */
static int32 gen_get_stwire_addr(struct net_t *np, struct gref_t *grp)
{
 int32 sbp_ti;

 sbp_ti = -1;
 switch ((byte) np->srep) {
  case SR_SVEC:
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     sbp_ti = __gen_ld_is_svec_varadr(np, grp);
    }
   else sbp_ti = __gen_ld_netbp(np);
   break;
  case SR_SSCAL:
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     sbp_ti = __gen_ld_is_svec_varadr(np, grp);
    }
   else sbp_ti = __gen_ld_netbp(np);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(sbp_ti);
}

/*
 * gen access a stren bit select - always returns sbp addr (even if scalar)
 *
 * this if for cases where accessing strength and know it is needed and
 * know value has strength
 * obviously never a b part
 *
 * SJM 07/18/05 - can this be variable and/or x/z
 */
static int32 gen_access_stbsel(struct expr_t *ndp)
{
 int32 biti_ti, xpr_ti, sbp_ti, res_sbpti, bi;
 struct net_t *np;
 struct expr_t *idndp;
 struct bblk_t *setstren_bbp, *done_bbp;

 if (ndp->ru.x->optyp == NUMBER)
  {
   bi = __get_comp_num_ndx(ndp->ru.x);
   sbp_ti = gen_access_stbsel_const(ndp, bi);
   return(sbp_ti);
  }
 setstren_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);

 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;
 biti_ti = __gen_comp_ndx(np, ndp->ru.x, setstren_bbp, FALSE);  

 res_sbpti = __gen_tn(SR_SVEC, ndp->szu.xclen); 
 /* unknown index is strong x - cannot emit warning happens too often */
 /* strong x 6,6,3 - 11011011 */
 /* AIV 10/23/08 - index cannot be -1 here - removed jmp */

 sbp_ti = -1;
 if (idndp->optyp == ID) sbp_ti = gen_get_stwire_addr(np, NULL);
 else if (idndp->optyp == GLBREF)
  {
   sbp_ti = gen_get_stwire_addr(np, idndp->ru.grp);
  }
 else __case_terr(__FILE__, __LINE__);

 xpr_ti = __var_adradd_insn(SR_SVEC, ndp->szu.xclen, sbp_ti, biti_ti);
 __emit_jmp(done_bbp);

 __start_bblk(setstren_bbp);
 __emit_setstren(res_sbpti,  0xdb, __get_tnwid(res_sbpti));
 __emit_jmp(done_bbp);
 
 __start_bblk(done_bbp);

 __emit_copy(ndp->szu.xclen, xpr_ti, res_sbpti);
 return(res_sbpti);
}

/*
 * constant bit selector version
 */
static int32 gen_access_stbsel_const(struct expr_t *ndp, int32 bi)
{
 int32 xpr_ti, sbp_ti, tmp_sbpti;
 struct net_t *np;
 struct expr_t *idndp;

 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;

 if (bi == -1)
  {
   tmp_sbpti = __gen_tn(SR_SVEC, 1); 
   __emit_setstren(tmp_sbpti, 0xdb, __get_tnwid(tmp_sbpti));
   return(tmp_sbpti);
  }

 sbp_ti = -1;
 if (idndp->optyp == ID) sbp_ti = gen_get_stwire_addr(np, NULL);
 else if (idndp->optyp == GLBREF)
  {
   sbp_ti = gen_get_stwire_addr(np, idndp->ru.grp);
  }
 else __case_terr(__FILE__, __LINE__);

 xpr_ti = __con_adradd_insn(SR_SVEC, ndp->szu.xclen, sbp_ti, bi);
 return(xpr_ti);
}

/*
 * gen access a stren part select - always returns sbp vec addr
 *
 * same as bsel except low index access differently and known in range
 * one bit ok but cannot part select from scalar
 */
static int32 gen_access_stpsel(struct expr_t *ndp)
{
 struct net_t *np;
 struct expr_t *idndp;
 int32 bi2, xpr_ti, sbp_ti;

 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;
 /* access 2nd low bit address */
 bi2 = (int32) __contab[ndp->ru.x->ru.x->ru.xvi];
 if (bi2 == -1) __misc_terr(__FILE__, __LINE__);

 sbp_ti = -1;
 if (idndp->optyp == ID) sbp_ti = gen_get_stwire_addr(np, NULL);
 else if (idndp->optyp == GLBREF)
  {
   sbp_ti = gen_get_stwire_addr(np, idndp->ru.grp);
  }
 else __case_terr(__FILE__, __LINE__);

 xpr_ti = __con_adradd_insn(SR_SVEC, ndp->szu.xclen, sbp_ti, bi2);
 return(xpr_ti);
}

/*
 * gen vinsns to eval a known strength expr node rhs concatenate
 * key is that { op. node width is same as starting high bit of value
 *
 * notice that subexpressions of strength concat can be non strength
 * strength stored low bit (0) to high bit (n)
 */
static int32 rhs_stconcat(struct expr_t *lcbndp) 
{
 struct expr_t *ndp; 
 int32 bi2, sbp_ti, sbp2_ti, cat_ti;
 struct expr_t *catndp;
 
 /* SJM 02/07/05 - fixme - why can't this go in formal tmp table? */
 sbp_ti = __gen_tn(SR_SVEC, lcbndp->szu.xclen); 
 for (ndp = lcbndp->ru.x; ndp != NULL; ndp = ndp->ru.x)
  {
   catndp = ndp->lu.x;

   cat_ti = gen_ndst_expr_eval(catndp);
   /* here know cat width must match rhs width */
   /* AIV 03/15/07 - was using the wrong expr for the lenght conversion */
   cat_ti = __gen_cnvt_srep_ifneeded(cat_ti, SR_SVEC, catndp->szu.xclen, FALSE,
    FALSE, FALSE);

   /* bi2 is low bit, LCB node xclen start high bit, catndp is id/num width */
   bi2 = ndp->szu.xclen - catndp->szu.xclen;
   if (bi2 > 0)
    {
     sbp2_ti = __con_adradd_insn(SR_SVEC, catndp->szu.xclen, sbp_ti, bi2); 
    }
   else sbp2_ti = sbp_ti;
   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(catndp->szu.xclen, cat_ti, sbp2_ti);
  }
 return(sbp_ti);
}


/*
 * CONVERSION VINSN GEN ROUTINES (BOTH PROC AND DECL)
 */

/*
 * gen rhs match srep size/representation conversion
 *
 * passed ptr to pr tmp reg object to convert and may returns pointer to
 * if conversion needed
 */
extern int32 __gen_cnvt_srep_ifneeded(int32 rhs_ti, int32 nd_srep,
 int32 nd_wid, int32 nd_signed, int32 nd_real, int32 exact_size)
{
 int32 res_ti, rhs2_ti, rhs3_ti, chg_size, cint_ti, r1_ti, is_stren;
 int32 srtyp, amtype;
 
 /* DBG remove -- */
 if (__tntab[rhs_ti].srtyp == SR_CINT)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* if need real but is already real just return */
 if (nd_real && __tntab[rhs_ti].t_real) return(rhs_ti);

 /* if nd srep is not svec or scalar (stren scalar), convert to natural */
 /* width a/b vector to start */ 
 if ((__tntab[rhs_ti].srtyp == SR_SVEC)
  && (nd_srep != SR_SVEC && nd_srep != SR_SCAL && nd_srep != SR_SSCAL))
  {
   rhs2_ti = gen_cnvt_svec_to_ab(rhs_ti, nd_wid, nd_signed);
  }
 else rhs2_ti = rhs_ti;

 switch ((byte) nd_srep) {
  case SR_VEC:
   srtyp = __tntab[rhs2_ti].srtyp;
   /* need a/b vec value */ 
   /* although real stored as 64 bit (look like a/b) must treat as svec */
   if (nd_real)
    {
     if (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S)
      {
       /* eval insns that return tmp nam result in are <dst> <= <src> order */
       is_stren = (srtyp == SR_SSCAL);
       rhs3_ti = __emit_movw_fr_scal(WBITS, rhs2_ti, is_stren);
      }
     else rhs3_ti = rhs2_ti;

     res_ti = __gen_to_r_cnvt(rhs3_ti, nd_signed, SR_VEC);
     break;
    }
   if (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S)
    {
     /* AIV 10/19/05 - if moving to less than word no need to widen */
     /* AIV 01/02/07 - if rhs can still be signed here */
     /* may need to sign extend so must mark the size - one bit */
     is_stren = (srtyp == SR_SSCAL);
     if (__tntab[rhs2_ti].t_signed) 
      {
       rhs3_ti = __emit_movw_fr_scal(1, rhs2_ti, is_stren);
       /* need to mark the new signed as well for signed xtnd */
       __tntab[rhs3_ti].t_signed = TRUE;
      }
     else if (nd_wid <= WBITS)
      {
       rhs3_ti = __emit_movw_fr_scal(nd_wid, rhs2_ti, is_stren);
      }
     else rhs3_ti = __emit_movw_fr_scal(1, rhs2_ti, is_stren);
     rhs2_ti = rhs3_ti;
    }
   else if (__tntab[rhs2_ti].t_real)
    {
     /* this needs to be a c wrapper lowered to x86 code */
     rhs3_ti = __emit_movw_fr_r(rhs2_ti);
     rhs2_ti = rhs3_ti;
    }
   else if (srtyp == SR_BIT2S) 
    {
     if (nd_signed) 
      {
       rhs2_ti = gen_2state_vec_to_4state(rhs2_ti, __get_tnwid(rhs2_ti));
       __tntab[rhs2_ti].t_signed = TRUE;
      }
     else 
      {
       rhs2_ti = gen_2state_vec_to_4state(rhs2_ti, nd_wid);
       return(rhs2_ti);
      }
    }

   /* same width or narrowing in same number of words is same */
   if (nd_signed || exact_size) chg_size = (nd_wid != __get_tnwid(rhs2_ti));
   else
    {
     chg_size = !(__same_size(nd_wid, __get_tnwid(rhs2_ti)));
    }

   /* notice chg size is compile time determined value */
   if (!chg_size) return(rhs2_ti);
   res_ti = gen_vec_sizchg(rhs2_ti, nd_wid, __get_tnwid(rhs2_ti), nd_signed,
    FALSE);
   break;
  case SR_SVEC:
   /* need a svec */
   if (__tntab[rhs2_ti].srtyp == SR_SVEC)
    {
     /* widen must z xtnd */
     /* if narrowing - just ignore high bit so no copy needed */
     if (nd_wid > __get_tnwid(rhs2_ti))
      {
       res_ti = gen_svec_widen(nd_wid, rhs2_ti, ST_HIZ);
      }
     else res_ti = rhs2_ti;
    }
   else res_ti = gen_vec_to_svec_cnvt(nd_wid, rhs2_ti, (ST_STRVAL << 2));
   break;
  case SR_SCAL: case SR_SSCAL:
   srtyp = __tntab[rhs_ti].srtyp;
   if (srtyp == SR_SCAL2S) 
    {
     if (__tntab[rhs_ti].tn_typ == TN_ADR) amtype = AM_NDXREG; 
     else amtype = AM_REG;

     res_ti = __move_srep_insn(TN_VAL, I_MOVA, nd_srep, 1, amtype, rhs_ti); 
     return(res_ti);
    }

   /* if two state just and the low bit */
   if (srtyp == SR_BIT2S) 
    {
     cint_ti = __gen_cint_tn(1);
     res_ti = __emit_srep_mask_and(nd_srep, 1, rhs_ti, cint_ti);
     return(res_ti);
    }


   if (nd_srep == srtyp)
    {
     /* DBG remove -- */
     if (__tntab[rhs_ti].tnwid != 1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     return(rhs_ti);
    }
   /* convert from strength scalar to regular scalar */
   if (nd_srep == SR_SCAL && srtyp == SR_SSCAL)
    {
      cint_ti = __gen_cint_tn(3);
      rhs2_ti = __emit_srep_mask_and(SR_SCAL, 1, rhs_ti, cint_ti);
      return(rhs2_ti);
    }

   /* AIV 01/23/06 - if rhs is svec just and 1 has no bpart */
   if (srtyp == SR_SVEC)
    {
     /* AIV 01/08/07 - mask was 1 need to mask for the low byte */
     /* AIV 09/03/08 - notice above this can be scal or sscal */
     /* mask was wrong for scalar and type was wrong for sscal */
     if (nd_srep == SR_SSCAL)
      {
       cint_ti = __gen_cint_tn(0xff);
       rhs2_ti = __emit_srep_mask_and(SR_SSCAL, 1, rhs_ti, cint_ti);
      }
     else
      {
       /* scalar can only have 4 state values mask with 4 */
       cint_ti = __gen_cint_tn(0x3);
       rhs2_ti = __emit_srep_mask_and(SR_SCAL, 1, rhs_ti, cint_ti);
      }
     return(rhs2_ti);
    }

   /* AIV LOOKATME - should this ever occur ??? */
   if (nd_srep == SR_SSCAL) 
    {
     /* AIV 11/30/05 - if rhs is a svec and need sscal just return */
     /* the low byte is the scalar value so should be ok */
     if (srtyp == SR_SVEC)
      {
        return(rhs_ti);
      }

     /* DBG remove -- */
     if (srtyp == SR_SCAL) __misc_terr(__FILE__, __LINE__);
     /* --- */
    }

   /* convert to scalar if not scalar */ 
   if (__tntab[rhs2_ti].t_real)
    {
     rhs3_ti = __emit_movw_fr_r(rhs_ti);
     rhs2_ti = rhs3_ti;
    }
   if (__get_tnwid(rhs2_ti) > WBITS)
    {
     rhs3_ti = gen_vec_narrow(rhs2_ti, WBITS, FALSE);
     rhs2_ti = rhs3_ti;
    }
   res_ti = __gen_cnvt_ab_vec_to_scalar(rhs2_ti);
   if (nd_srep == SR_SSCAL)
    {
     cint_ti = __gen_cint_tn((ST_STRVAL << 2));
     r1_ti = __emit_mask_or(res_ti, cint_ti);
     __emit_copy(WRDBYTES, r1_ti, res_ti); 
    }
   break;
  case SR_BIT2S:
   if (nd_real) 
    {
     res_ti = __gen_to_r_cnvt(rhs2_ti, nd_signed, SR_BIT2S);
     break;
    }

   srtyp = __tntab[rhs2_ti].srtyp;
   if (__tntab[rhs2_ti].t_real) 
    {
     rhs2_ti = __emit_movw_fr_r_2state(rhs2_ti);
    }
   else if (srtyp == SR_SCAL || srtyp == SR_SSCAL)
    {
     is_stren = (srtyp == SR_SSCAL);
     if (__tntab[rhs2_ti].t_signed) 
      {
       rhs3_ti = __emit_movw_2s_fr_scal(1, rhs2_ti, is_stren);
       /* need to mark the new signed as well for signed xtnd */
       __tntab[rhs3_ti].t_signed = TRUE;
      }
     else if (nd_wid <= WBITS)
      {
       rhs3_ti = __emit_movw_2s_fr_scal(nd_wid, rhs2_ti, is_stren);
      }
     else rhs3_ti = __emit_movw_2s_fr_scal(1, rhs2_ti, is_stren);
     rhs2_ti = rhs3_ti;
    }
   else if (srtyp == SR_SCAL2S)
    {
     /* if 2state scalar just do move to change type and width */
     if (__tntab[rhs2_ti].tn_typ == TN_ADR) amtype = AM_NDXREG; 
     else amtype = AM_REG;

     /* may have to widen */
     if (nd_wid <= WBITS) 
      {
       res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, nd_wid, amtype, 
         rhs2_ti); 
       return(res_ti);
      }
    }
   else if (srtyp == SR_VEC)
    {
     if (nd_signed) 
      {
       rhs2_ti = gen_4state_vec_to_2state(rhs2_ti, __get_tnwid(rhs2_ti));
       __tntab[rhs2_ti].t_signed = TRUE;
      }
     else rhs2_ti = gen_4state_vec_to_2state(rhs2_ti, nd_wid);
    }
   else if (srtyp == SR_SVEC) __misc_terr(__FILE__, __LINE__);

   /* same width or narrowing in same number of words is same */
   if (nd_signed || exact_size) chg_size = (nd_wid != __get_tnwid(rhs2_ti));
   else
    {
     chg_size = !(__same_size(nd_wid, __get_tnwid(rhs2_ti)));
    }
   /* notice chg size is compile time determined value */
   if (!chg_size) return(rhs2_ti);
   res_ti = gen_vec_sizchg(rhs2_ti, nd_wid, __get_tnwid(rhs2_ti), nd_signed,
    TRUE);
   break;
  case SR_SCAL2S:
   res_ti =  __gen_cnvt_ab_vec_to_scalar_2state(rhs2_ti);
   break;
  default: res_ti = -1; __case_terr(__FILE__, __LINE__);
 }
 return(res_ti);
}

/*
 * gen sr vec size change - uses right signedness
 */
static int32 gen_vec_sizchg(int32 rhs_ti, int32 newwid, int32 oldwid, 
 int32 nd_signed, int32 is_2state)
{
 int32 res_ti;

 if (nd_signed)
  {
   res_ti = gen_wrd_sign_sizchg(rhs_ti, newwid, oldwid, is_2state);
  }
 else res_ti = gen_wrd_unsigned_sizchg(rhs_ti, newwid, oldwid, is_2state);
 return(res_ti);
}

/*
 * gen vinsn to do signed size change
 *
 * for wide, rhs will be ptr but result will be tmp (not ptr to tmp) 
 */
static int32 gen_wrd_sign_sizchg(int32 rhs_ti, int32 dstwid, int32 rhswid,
 int32 is_2state)
{
 int32 res_ti;

 res_ti = -1;
 if (rhswid > dstwid)
  {
   res_ti = gen_vec_narrow(rhs_ti, dstwid, is_2state);
   return(res_ti);
  }
 else if (rhswid < dstwid)
  {
   /* AIV 12/01/05 - if rhs not signed know just a regular widen */
   if (!__tntab[rhs_ti].t_signed)
    {
     return(gen_wrd_unsigned_widen(rhs_ti, dstwid, rhswid, is_2state));
    }
   else if (dstwid <= WBITS)
    {
     return(gen_wrd_sgnxtnd_widen(rhs_ti, dstwid, rhswid, is_2state));
    }
   else
    {
     /* AIV FIXME REMOVEME - either fix or remove probably remove
       will genereate too much code
      return(gen_wide_sizchg_widen(rhs_ti, dstwid, rhswid));
     */
     if (is_2state)
      {
       res_ti = __gen_tn(SR_BIT2S, dstwid);
       __emit_sxtnd_widwdn(res_ti, rhs_ti, rhswid, dstwid, TRUE);
      }
     else
      {
       res_ti = __gen_tn(SR_VEC, dstwid);
       __emit_sxtnd_widwdn(res_ti, rhs_ti, rhswid, dstwid, FALSE);
      }
     /* AIV 01/10/07 - noticed sign bit wasn't being set - found no bug */
     __tntab[res_ti].t_signed = TRUE;
    }
  }
 else __case_terr(__FILE__, __LINE__);
 return(res_ti);
}

/*
 *
 *  AIV FIXME REMOVEME - either fix or remove probably remove
 *  will genereate too much code 
 *  DOESN'T WORK
 */
static int32 gen_wide_sizchg_widen(int32 rhs_ti, int32 dstwid, int32 rhswid)
{
 int32 t1_apti, t1_bpti, rhs_bpti, ofs;
 int32 hghw_apti, hghw_bpti, hghw_xtnd_apti, hghw_xtnd_bpti, r1_ti;
 struct bblk_t *onea_bbp, *checkb_bbp, *oneb_bbp, *done_bbp;
 struct bblk_t *zeroa_bbp, *zerob_bbp;
 int32 nwlen, widen_amt, rhs_bytes, mask_ti; 
 int32 xtra_bytes, osgn_bofs, xtra_wbits;
 word32 mask;

 nwlen = wlen_(dstwid);
 rhs_bytes = wlen_(rhswid)*WRDBYTES;

 onea_bbp = __alloc_bblk(FALSE);
 oneb_bbp = __alloc_bblk(FALSE);
 checkb_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);
 zeroa_bbp = __alloc_bblk(FALSE);
 zerob_bbp = __alloc_bblk(FALSE);

 osgn_bofs = get_bofs_(dstwid - 1);
 widen_amt = dstwid - rhswid; 
 xtra_wbits = widen_amt - (WBITS - osgn_bofs - 1);
 xtra_bytes = xtra_wbits * WRDBYTES;
 mask = __masktab[WBITS - osgn_bofs - 1] << (osgn_bofs + 1);

 t1_apti = __gen_tn(SR_VEC, dstwid);
 t1_bpti = __get_bpti(t1_apti);
 rhs_bpti = __get_bpti(rhs_ti);

 ofs = WRDBYTES*(nwlen - 1);
 hghw_apti = __con_adradd_insn(SR_VEC, dstwid, t1_apti, ofs);
 hghw_bpti = __con_adradd_insn(SR_VEC, dstwid, t1_bpti, ofs);

 ofs = WRDBYTES*nwlen;
 hghw_xtnd_apti = __con_adradd_insn(SR_VEC, dstwid, t1_apti, ofs);
 hghw_xtnd_bpti = __con_adradd_insn(SR_VEC, dstwid, t1_bpti, ofs);

 __emit_copy(rhs_bytes, rhs_ti, t1_apti);
 __emit_sgnbit_on_jmp(onea_bbp, zeroa_bbp, rhs_ti);

 __start_bblk(onea_bbp);
 mask_ti = __gen_cint_tn(mask);
 r1_ti = __emit_mask_or(hghw_apti, mask_ti);
 __emit_copy(WRDBYTES, r1_ti, hghw_apti); 

 __emit_store_cint(hghw_xtnd_apti, 0, mask_ti);
 __emit_jmp(checkb_bbp);

 __start_bblk(zeroa_bbp);
 //FIXME - need another mask takes bits not bytes
 __emit_setall1(hghw_xtnd_apti, xtra_bytes);

 __start_bblk(checkb_bbp);
 __emit_copy(rhs_bytes, rhs_bpti, t1_bpti);
 __emit_sgnbit_on_jmp(oneb_bbp, zerob_bbp, rhs_bpti);

 __start_bblk(oneb_bbp);
 r1_ti = __emit_mask_or(hghw_bpti, mask_ti);
 __emit_copy(WRDBYTES, r1_ti, hghw_bpti); 

 //FIXME - need another mask takes bits not bytes
  __emit_setall1(hghw_xtnd_bpti, xtra_bytes);
  __emit_jmp(done_bbp);

 __start_bblk(zerob_bbp);
 //FIXME - need another mask takes bits not bytes
 __emit_store_cint(hghw_xtnd_bpti, 0, xtra_bytes);
 __start_bblk(done_bbp);
 return(t1_apti);
}

/*
 * sign extend of <= WBITS
 */
static int32 gen_wrd_sgnxtnd_widen(int32 rhs_ti, int32 dstwid, int32 rhswid,
 int32 is_2state)
{
 int32 t1_apti, t1_bpti, rhs_bpti, cint_ti, r1_ti, r2_ti; 
 struct bblk_t *maska_bbp, *checkb_bbp, *maskb_bbp, *done_bbp;
 word32 mask;

 /* AIV 11/18/10 - should fold constant values here */
 /* 64-bit was producing bad asm with movlsq which cannot have a const src */
 if (__tntab[rhs_ti].comlab_typ == COMLAB_CONADR)
  {
   return(gen_widen_new_constant_signed(rhs_ti, dstwid, rhswid, is_2state));
  }

#ifndef __CVC32__
 int32 amtype;
 /* AIV 09/13/10 - this is common code for 64 bit code - to widen to 64 */
 /* for example i < 10, were i is 32-bit integer - but the 10 is 64 */
 /* just need to move using movslq insns */
 if (dstwid == 64 && rhswid == 32)
  {
   if (__tntab[rhs_ti].tn_typ == TN_ADR) amtype = AM_NDXREG; 
   else amtype = AM_REG;

   if (is_2state) 
    {
     t1_apti = __move_srep_insn(TN_VAL, I_MOVSLQ, SR_BIT2S, 64, amtype, rhs_ti);
    }
   else
    {
     t1_apti = __gen_tn(SR_VEC, dstwid);
     r1_ti = __move_srep_insn(TN_VAL, I_MOVSLQ, SR_VEC, 64, amtype, rhs_ti);
     __emit_copy(WRDBYTES, r1_ti, t1_apti);
     t1_bpti = __get_bpti(t1_apti);
     rhs_bpti = __get_bpti(rhs_ti);
     r2_ti = __move_srep_insn(TN_VAL, I_MOVSLQ, SR_VEC, 64, amtype, rhs_bpti);
     __emit_copy(WRDBYTES, r2_ti, t1_bpti);
    }
   return(t1_apti);
  }
#endif

 maska_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);
 if (is_2state) 
  {
   t1_apti = __gen_tn(SR_BIT2S, dstwid);
   __emit_copy(WRDBYTES, rhs_ti, t1_apti);
   __emit_sgnbit_on_jmp(maska_bbp, done_bbp, rhs_ti);

   __start_bblk(maska_bbp);
   mask = __masktab[dstwid - rhswid] << rhswid;
   cint_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_or(t1_apti, cint_ti); 
   __emit_copy(WRDBYTES, r1_ti, t1_apti);
   __start_bblk(done_bbp);
   return(t1_apti);
  }

 t1_apti = __gen_tn(SR_VEC, dstwid);
 maskb_bbp = __alloc_bblk(FALSE);
 checkb_bbp = __alloc_bblk(FALSE);
 rhs_bpti = __get_bpti(rhs_ti);

 __emit_copy(WRDBYTES, rhs_ti, t1_apti);
 __emit_sgnbit_on_jmp(maska_bbp, checkb_bbp, rhs_ti);

 __start_bblk(maska_bbp);
 mask = __masktab[dstwid - rhswid] << rhswid;
 cint_ti = __gen_cint_tn(mask);
 r1_ti = __emit_mask_or(t1_apti, cint_ti); 
 __emit_copy(WRDBYTES, r1_ti, t1_apti);

 __start_bblk(checkb_bbp);
 t1_bpti = __get_bpti(t1_apti);
 __emit_copy(WRDBYTES, rhs_bpti, t1_bpti);
 __emit_sgnbit_on_jmp(maskb_bbp, done_bbp, rhs_bpti);

 __start_bblk(maskb_bbp);
 r2_ti = __emit_mask_or(t1_bpti, cint_ti); 
 __emit_copy(WRDBYTES, r2_ti, t1_bpti);

 __start_bblk(done_bbp);
 return(t1_apti);
}

/*
 * gen vinsns to narrow a/b vec form to narrower a/b vec form
 *
 * notice both source and destination must be SR_VEC (a/b) form
 */
static int32 gen_vec_narrow(int32 rhs_ti, int32 dstbitwid, int32 is_2state)
{
 int32 rhs_bpti, res_ti, res_bpti, hghw_apti, hghw_bpti, ofs;
 int32 dst_bytes, r2_ti, r1_ti, mask_ti, srtyp;
 word32 mask;

 /* AIV 11/30/05 - if strength vector high part just unused */
 /* AIV LOOKATME - is this always true ??????? */
 if (__tntab[rhs_ti].srtyp == SR_SVEC)
  {
   return(rhs_ti);
  }
 res_ti = -1;
 /* AIV 01/17/08 - if rhs is contab just mask the old contab value */
 /* mask it if needed and create new contab value */
 /* AIV 09/12/08 - new routine works for narrow and wide */
 if (__tntab[rhs_ti].comlab_typ == COMLAB_CONADR)
  {
   res_ti = gen_narrow_new_constant(rhs_ti, dstbitwid, is_2state);
   return(res_ti);
  }
  
 if (is_2state) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;
 /* narrowing into one word (WBITS) or less */
 /* case 1: narrow into one word */
 res_bpti = -1;
 if (dstbitwid <= WBITS)
  {
   /* AIV 09/08/10 - using new better code for narrow case */
   /* this is common code for new DPI conversions */
   res_ti = __emit_new_narrow_word(dstbitwid, rhs_ti, is_2state);
   return(res_ti);
  }

 /* case 2: narrow into more than one word */
 /* AIV 09/12/08 - no need for __emit_ call really just copy here */
 res_ti = __gen_tn(srtyp, dstbitwid);
 dst_bytes = WRDBYTES*wlen_(dstbitwid);
 __emit_copy(dst_bytes, rhs_ti, res_ti);
 if (!is_2state)
  {
   res_bpti = __get_bpti(res_ti);
   /* notice cp is <dst> => <src> gas order */
   rhs_bpti = __get_bpti(rhs_ti);
   __emit_copy(dst_bytes, rhs_bpti, res_bpti);
  }

 if (ubits_(dstbitwid) != 0)
  {
   mask = __masktab[ubits_(dstbitwid)];
   ofs = WRDBYTES*(wlen_(dstbitwid) - 1);
   hghw_apti = __con_adradd_insn(srtyp, dstbitwid, res_ti, ofs);
   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);  
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);

   if (!is_2state)
    {
     hghw_bpti = __get_bpti(hghw_apti);
     r2_ti = __emit_mask_and(hghw_bpti, mask_ti);  
     __emit_copy(WRDBYTES, r2_ti, hghw_bpti);
    }
  }
 return(res_ti);
}
 
/*
 * narrow a constant value to a new narrower constant value
 */
static int32 gen_narrow_new_constant(int32 rhs_ti, int32 dstbitwid, 
 int32 is_2state)
{
 int32 xvi, nwlen, owlen, blen, res_ti;
 word32 mask;
 word32 *nwp, *wp;

 xvi = __get_con_adradd_xvi(rhs_ti);
 wp = &(__contab[xvi]);
 nwlen = wlen_(dstbitwid);
 /* malloc new wp to hold constant value */
 nwp = (word32 *) __my_malloc(2*nwlen*WRDBYTES);
 /* copy and mask the a part */
 memcpy(nwp, wp, nwlen*WRDBYTES);
 mask = __masktab[ubits_(dstbitwid)];
 nwp[nwlen-1] &= mask;

 /* copy and mask the b part */
 blen = __get_tnwid(rhs_ti);
 owlen = wlen_(blen);
 memcpy(&(nwp[nwlen]), &(wp[owlen]), nwlen*WRDBYTES);
 nwp[nwlen] &= mask;

 /* get the new tmp value and free tmp storage */
 xvi = __allocfill_cval_new(nwp, &(nwp[nwlen]), nwlen);
 __my_free(nwp, 2*nwlen*WRDBYTES);
 if (is_2state)
  {
   res_ti = __gen_contab_tn(xvi, dstbitwid, FALSE, FALSE, FALSE, SR_BIT2S);
  }
 else
  {
   res_ti = __gen_contab_tn(xvi, dstbitwid, FALSE, FALSE, FALSE, SR_VEC);
  }
 return(res_ti);
}

/*
 * gen vinsn to do unsigned sr vec ptr object size change
 */
static int32 gen_wrd_unsigned_sizchg(int32 rhs_ti, int32 dstwid, int32 rhswid,
 int32 is_2state)
{
 int32 res_ti;

 /* narrowing same for signed and unsigned */
 if (rhswid > dstwid)
  {
   res_ti = gen_vec_narrow(rhs_ti, dstwid, is_2state);
   return(res_ti);
  }

 /* AIV 09/12/08 - if constant just create a new constant */
 if (__tntab[rhs_ti].comlab_typ == COMLAB_CONADR)
  {
   res_ti = gen_widen_new_constant(rhs_ti, dstwid, is_2state);
   return(res_ti);
  }

 /* if widening in same number of words */
 /* AIV 11/09/06 - this is has just returning for the number of words == */
 /* this insn't true through because the width (tnwid) needs to be the */
 /* correct size, this was causing an error when converting to strength */
 /* it wasn't init the right amount */
 /* AIV LOOKATME - could just set to new size but may later need to narrow */
 /* no better - so do the copy for now */
 if (__same_size(dstwid, rhswid)) 
  {
   if (is_2state)
    {
     res_ti = __gen_tn(SR_BIT2S, dstwid);
     __emit_copy(wlen_(rhswid)*WRDBYTES, rhs_ti, res_ti);
    }
   else
    {
     res_ti = __gen_tn(SR_VEC, dstwid);
     __emit_copy(2*wlen_(rhswid)*WRDBYTES, rhs_ti, res_ti);
    }
   return(res_ti);
  }

 /* unsigned widen */
 res_ti = gen_wrd_unsigned_widen(rhs_ti, dstwid, rhswid, is_2state);
 return(res_ti);
}

/*
 * widen a constant to a new wider constant
 */
static int32 gen_widen_new_constant(int32 rhs_ti, int32 dstwid, int32 is_2state)
{
 int32 xvi, owlen, nwlen, res_ti, blen;
 word32 *nwp, *wp;

 xvi = __get_con_adradd_xvi(rhs_ti);
 wp = &(__contab[xvi]);

 nwlen = wlen_(dstwid);
 blen = __get_tnwid(rhs_ti);
 owlen = wlen_(blen);

 /* malloc new wp to hold constant value */
 nwp = (word32 *) __my_malloc(2*nwlen*WRDBYTES);

 /* just zero new value and no need to mask */
 memset(nwp, 0, 2*nwlen*WRDBYTES);

 /* copy a part */
 memcpy(nwp, wp, owlen*WRDBYTES);

 /* copy b part */
 memcpy(&(nwp[nwlen]), &(wp[owlen]), owlen*WRDBYTES);

 /* get the new tmp value and free tmp storage */
 xvi = __allocfill_cval_new(nwp, &(nwp[nwlen]), nwlen);
 __my_free(nwp, 2*nwlen*WRDBYTES);
 if (is_2state)
  {
   res_ti = __gen_contab_tn(xvi, dstwid, FALSE, FALSE, FALSE, SR_BIT2S);
  }
 else res_ti = __gen_contab_tn(xvi, dstwid, FALSE, FALSE, FALSE, SR_VEC);
 return(res_ti);
}

/*
 * sign extend into a new wide constant
 */
static int32 gen_widen_new_constant_signed(int32 rhs_ti, int32 dstwid, 
 int32 rhswid, int32 is_2state)
{
 int32 xvi, nwlen, res_ti;
 word32 *nwp, *wp;

 xvi = __get_con_adradd_xvi(rhs_ti);
 wp = &(__contab[xvi]);

 nwlen = wlen_(dstwid);

 /* malloc new wp to hold constant value */
 nwp = (word32 *) __my_malloc(2*nwlen*WRDBYTES);

 /* just zero new value and no need to mask */
 memset(nwp, 0, 2*nwlen*WRDBYTES);
 /* just use asl sign extend wrapper */
 __asl_sgn_xtnd_widen(nwp, wp, rhswid, dstwid);

 if (is_2state)
  {
   res_ti = __gen_contab_tn(xvi, dstwid, FALSE, FALSE, FALSE, SR_BIT2S);
  }
 else res_ti = __gen_contab_tn(xvi, dstwid, FALSE, FALSE, FALSE, SR_VEC);
 return(res_ti);
}

/*
 * unsigned word widen 
 */
static int32 gen_wrd_unsigned_widen(int32 rhs_ti, int32 dstwid, int32 rhswid,
 int32 is_2state)
{
 int32 res_ti, res_bpti, rhs_bpti, hgharea_apti, ofs; 
 int32 rhs_bytes, hgharea_bpti, nbytes, srtyp;

 /* if widening in same number of words - nothing to do */
 if (__same_size(dstwid, rhswid)) return(rhs_ti);

 if (__tntab[rhs_ti].comlab_typ == COMLAB_CONADR)
  {
   return(gen_widen_new_constant(rhs_ti, dstwid, is_2state));
  }

 /* know widening into more words (i.e. dest at least 2 words) */
 /* this moves narrow part in wider tmp name */
 /* must take blen as second arg so doesn't get mapped to wrong size tn */
 /* AIV 09/12/08 - call to wrapper no need here just a copy */
 if (is_2state) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;
 res_ti = __gen_tn(srtyp, dstwid);
 rhs_bytes = WRDBYTES*wlen_(rhswid);
 __emit_copy(rhs_bytes, rhs_ti, res_ti);

 /* copy the old narrower size a part into the larger's a part */
 /* same with the b part */
 res_bpti = rhs_bpti = -1;
 if (!is_2state)
  {
   rhs_bpti = __get_bpti(rhs_ti);
   res_bpti = __get_bpti(res_ti);
   __emit_copy(rhs_bytes, rhs_bpti, res_bpti);
  }

 /* hgh area is a ptr to starting wrd addr of high new zeroed area */
 /* does not really exist but high area tmp name is just ptr */
 /* thing pointed to size is in bits */
 ofs = WRDBYTES*(wlen_(rhswid));
 hgharea_apti = __con_adradd_insn(SR_VEC, dstwid - WBITS*(wlen_(rhswid)),
  res_ti, ofs);

 nbytes = WRDBYTES*(wlen_(dstwid) - wlen_(rhswid));
 /* now in place set0 for the widened to high a and b part words */
 /* do not need masking since any high unused bits of from 0 already */
 __emit_store_cint(hgharea_apti, 0, nbytes);

 if (!is_2state)
  {
   ofs = WRDBYTES*(wlen_(rhswid));
   hgharea_bpti = __con_adradd_insn(SR_VEC, dstwid - WBITS*(wlen_(rhswid)),
    res_bpti, ofs);
   __emit_store_cint(hgharea_bpti, 0, nbytes);
  }
 return(res_ti);
}

/*
 * routines to gen vinsn to load svec ptr into a and b 2v tmps
 */
static int32 gen_cnvt_svec_to_ab(int32 svec_pti, int32 vwid, int32 is_signed)
{
 int32 ap_ti, res_ti, blen;

 /* AIV 11/29/05 - blen only as wide as max of rhs */
 if (vwid > __get_tnwid(svec_pti)) blen = __get_tnwid(svec_pti);
 else blen = vwid;

 /* convert into tmp areas */
 /* AIV LOOKATME - this currently do the same thing and later sign extend */
 /* if needed */
 if (is_signed) 
  {
   ap_ti = __emit_movabw_fr_sgnsv(svec_pti, blen);
  }
 else
  {
   /* AIV LOOKATME - probably better way to do this if signed ????? */
   ap_ti = __emit_movabw_fr_svec(svec_pti, blen);
  }

 /* if signed and wider need to sign extend */
 if (is_signed)
  {
   if (vwid > blen) 
    {
     if (vwid < WBITS)
      {
       res_ti = gen_wrd_sgnxtnd_widen(ap_ti, vwid, blen, FALSE);
      }
     else
      {
       /* --- AIV FIXME REMOVEME - either fix or remove probably remove
              will genereate too much code
       gen_wide_sizchg_widen(rhs_ti, dstwid, rhswid);
       --- */
       res_ti = __gen_tn(SR_VEC, vwid);
       __emit_sxtnd_widwdn(res_ti, ap_ti, blen, vwid, FALSE);
       /* AIV 10/13/06 - was missing sign bit set */
       __tntab[ap_ti].t_signed = TRUE;
      }
     return(res_ti);
    }
   /* no need to sign xnted but mark as signed */
   __tntab[ap_ti].t_signed = TRUE;
  }
 return(ap_ti);
}

/*
 * gen svec widen - never need to narrow since can just ignore high bytes
 */
static int32 gen_svec_widen(int32 dstwid, int32 rhs_ti, int32 stval)
{
 int32 t1_ti, hghz_apti, rhswid;

 rhswid = __get_tnwid(rhs_ti);
 t1_ti = __gen_tn(SR_SVEC, dstwid); 

 /* DBG remove -- */
 if (dstwid < rhswid) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 
 /* copy the low number of bits into the new destination */
 __emit_copy(rhswid, rhs_ti, t1_ti);

 /* AIV 11/27/06 - was passing sr_vec, not sr_svec */
 hghz_apti = __con_adradd_insn(SR_SVEC, dstwid - rhswid, t1_ti, rhswid);

 /* === always widening with strong 0 - is that right? */
 __emit_setstren(hghz_apti, stval, dstwid - rhswid);
 return(t1_ti);
}

/*
 * gen convert to svec (special case because need to combine a/b parts)
 * from always SR VEC 
 */
static int32 gen_vec_to_svec_cnvt(int32 dstwid, int32 rhs_ti, int32 stval)
{
 int32 rhswid, res_ti, res2_ti, t1_ti, rhs2_ti;
 struct tn_t *tnp;

 tnp = &(__tntab[rhs_ti]);
 rhswid = tnp->tnwid;
 /* if real, convert to WBITS a part only vector */
 if (tnp->t_real)
  {
   t1_ti = __emit_movw_fr_r(rhs_ti);
   rhs_ti = t1_ti;
  }

 /* convert the a/b part to svec of current rhs width */ 
 if (dstwid < rhswid)
  {
   /* for narrowing better to narrow sr vec a/b form */
   rhs2_ti = gen_vec_narrow(rhs_ti, dstwid, FALSE);
   rhs_ti = rhs2_ti;
  }
 /* AIV LOOKATME - why is this needed isn't already init by here ??? */
 /* res_ti = gen_st_standval(rhs_ti, ST_STRVAL << 2); */

 /* finally widen more if needed - better to widen after convert to svec */
 if (dstwid > rhswid)
  {
   res2_ti = gen_svec_widen(dstwid, rhs_ti, stval);
   res_ti = res2_ti; 
  }
 else res_ti = rhs_ti;
 return(res_ti);
}

/*
 * conversion from any sr vec to new sr vec that is real (double)
 *
 * possibly more than one conversion because only exactly WBITS to real
 */
extern int32 __gen_to_r_cnvt(int32 rhs_ti, int32 nd_signed, int32 srtyp)
{
 int32 res_ti, t1_ti, t1_bpti, is_2state;
 struct tn_t *tnp;
 struct bblk_t *after_bbp, *xz_bbp, *cnvt_bbp; 
 int32 xvi, wlen, nbytes, nxvi;
 struct xstk_t *xsp;
 word32 *wp;
 double d1;

 tnp = &(__tntab[rhs_ti]);
 /* AIV 12/29/11 - this should have been folding for constant values */
 /* plus was off due to the folding signedness */
 if (__is_constant(rhs_ti))
  {
   /* DBG remove -- */
   if (tnp->srtyp == SR_CINT) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   xvi = __get_con_adradd_xvi(rhs_ti);
   wp = &(__contab[xvi]);
   wlen = wlen_(tnp->tnwid);
   push_xstk_(xsp, tnp->tnwid);
   if (srtyp == SR_BIT2S) 
    {
     nbytes = wlen*sizeof(word32);
     memcpy(xsp->ap, wp, nbytes);
     memset(xsp->bp, 0, nbytes);
     d1 = __cnvt_stk_to_real(xsp, tnp->t_signed);
     nxvi = __alloc_shareable_rlcval(d1);
     res_ti = __gen_contab_tn(nxvi, 64, FALSE, FALSE, TRUE, SR_BIT2S);
    }
   else 
    {
     nbytes = 2*wlen*sizeof(word32);
     memcpy(xsp->ap, wp, nbytes);
     d1 = __cnvt_stk_to_real(xsp, tnp->t_signed);
     nxvi = __alloc_shareable_rlcval(d1);
     res_ti = __gen_contab_tn(nxvi, WBITS, FALSE, FALSE, TRUE, SR_VEC);
    }

   __tntab[res_ti].tn_used_wide = TRUE; 
   __pop_xstk();
   return(res_ti);
  }


 /* DBG remove -- */
 if (tnp->srtyp != SR_VEC && tnp->srtyp != SR_BIT2S) 
   __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (tnp->tnwid > WBITS)
  {
   if (tnp->srtyp == SR_BIT2S) is_2state = TRUE;
   else is_2state = FALSE;

   t1_ti = gen_vec_sizchg(rhs_ti, WBITS, tnp->tnwid, FALSE, is_2state);
  }
 else t1_ti = rhs_ti;

 /* real stored in 8 byes - same as a/b 4 byte sr vec */
 if (srtyp == SR_BIT2S) res_ti = __gen_tn(SR_BIT2S, 64);
 else res_ti = __gen_tn(SR_VEC, WBITS);

 __tntab[res_ti].t_real = TRUE;
 /* SJM 08/27/06 - mark real as wide since halves non separable */
 __tntab[res_ti].tn_used_wide = TRUE; 

 /* if 2-state just skip b-part checking */
 /* AIV 10/13/10 - this needs to reassign tnp since __tntab may grow between */
 /* here and the first assign up top */
 tnp = &(__tntab[rhs_ti]);
 if (tnp->srtyp == SR_BIT2S)
  {
   if (nd_signed)
    {
     t1_ti =  __emit_movr_fr_sgnw(rhs_ti);
    }
   else
    {
     t1_ti =  __emit_movr_fr_w(rhs_ti);
    }
   __tntab[t1_ti].t_real = TRUE;
   /* SJM 08/27/06 - mark real as wide since halves non separable */
   __tntab[t1_ti].tn_used_wide = TRUE; 
   __emit_copy(8, t1_ti, res_ti);
   __tntab[res_ti].t_real = TRUE;
   /* SJM 08/27/06 - mark real as wide since halves non separable */
   __tntab[res_ti].tn_used_wide = TRUE; 
   return(res_ti);
  }

 /* now convert from 2v (with possible b part) to real */
 after_bbp = __alloc_bblk(FALSE);
 cnvt_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 t1_bpti = __get_bpti(t1_ti);
 __emit_jmp_0(cnvt_bbp, xz_bbp, t1_bpti); 
 __start_bblk(xz_bbp);

 __emit_setr0(res_ti);
 __emit_jmp(after_bbp);
 __start_bblk(cnvt_bbp);
 
 if (nd_signed)
  {
/* === need to make sure when gen tmp name for formal tmp tab of signed */
/*     or real, must set bits */
   t1_ti =  __emit_movr_fr_sgnw(rhs_ti);
  }
 else
  {
   t1_ti =  __emit_movr_fr_w(rhs_ti);
  }
 __tntab[t1_ti].t_real = TRUE;
 /* SJM 08/27/06 - mark real as wide since halves non separable */
 __tntab[t1_ti].tn_used_wide = TRUE; 

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(8, t1_ti, res_ti);
 __start_bblk(after_bbp);
 /* must set real bit */
 __tntab[res_ti].t_real = TRUE;
 /* SJM 08/27/06 - mark real as wide since halves non separable */
 __tntab[res_ti].tn_used_wide = TRUE; 
 return(res_ti);
}

/* 
 * convert a 2-state vec to a 4-state
 */
static int32 gen_2state_vec_to_4state(int32 two_ti, int32 nwid)
{
 int32 four_ti, four_bpti, blen, nbytes, four_ofs_ti;

 blen = __get_tnwid(two_ti);
 four_ti = __gen_tn(SR_VEC, nwid);
 __tntab[four_ti].tn_cnvt_from_2state = TRUE;
 /* if longer just take low words and zero b part */
 if (blen > nwid) blen = nwid;
 nbytes = WRDBYTES*wlen_(blen);
 __emit_copy(nbytes, two_ti, four_ti);

 /* same size just zero b part */
 if (blen == nwid)
  {
   four_bpti = __get_bpti(four_ti);
   __emit_store_cint(four_bpti, 0, nbytes);
  }
 else
  {
   /* if wider zero all remaining a high and b parts */
   four_ofs_ti = __con_adradd_insn(SR_VEC, WBITS, four_ti, nbytes);
   nbytes = 2*WRDBYTES*wlen_(nwid) - nbytes;
   __emit_store_cint(four_ofs_ti, 0, nbytes);
  }
 return(four_ti);
}
     
/*
 * convert all x/z to 0 and zero high part if wider
 */
static int32 gen_4state_vec_to_2state(int32 four_ti, int32 ndwid)
{
 int32 blen, two_ti, t1_ti, t2_ti, t3_ti, four_bpti, four_ofs_ti, new_ofs_ti; 
 int32 nwlen, wlen, i, ofs, bofs, hghw_ti, mask_ti, cp_wlen, xvi, ctab_ndx;
 int32 nbytes;
 word32 *owp, *nwp, *ow_bp;
 word32 mask, t1;

 blen = __get_tnwid(four_ti);
 wlen = wlen_(blen);
 nwlen = wlen_(ndwid);
 
 if (nwlen < wlen) cp_wlen = nwlen;
 else cp_wlen = wlen;

 if (__is_constant(four_ti))
  {
   /* DBG remove -- */
   if (__tntab[four_ti].srtyp == SR_CINT) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   /* if it is a constant just convert to a 2-state constant value */
   /* this will narrow or widen just be making another constant */
   xvi = __get_con_adradd_xvi(four_ti);
   owp = &(__contab[xvi]);
   ow_bp = &(owp[wlen]);
   nwlen = wlen_(ndwid);
   nbytes = 2*nwlen*sizeof(word32);
   nwp = (word32 *) __my_malloc(nbytes);
   memset(nwp, 0, nbytes);
   for (i = 0; i < cp_wlen; i++)
    {
     t1 = ~ow_bp[i];
     nwp[i] = owp[i] & t1;
     if (i == (nwlen-1) && ubits_(ndwid)) 
      {
       mask = __masktab[ubits_(ndwid)];
        nwp[i] &= mask;
      }
    }

   ctab_ndx = __allocfill_cval_new(nwp, &(nwp[nwlen]), nwlen);
   two_ti = __gen_contab_tn(ctab_ndx, ndwid, FALSE, FALSE, FALSE, SR_BIT2S);
   __my_free(nwp, nbytes);
   return(two_ti);
  }

 /* t1 = ~bp[0]; ap[0] &= t1; */
 if (ndwid <= WBITS)
  {
   four_bpti = __get_bpti(four_ti);
   t1_ti = __emit_bitnot(WBITS, four_bpti);
   t2_ti = __emit_bin_bitand(WBITS, four_ti, t1_ti);
   if (ubits_(ndwid) == 0)
    {
     two_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, ndwid, AM_REG, t2_ti);
     return(two_ti);
    }

   mask = __masktab[ubits_(ndwid)];
   mask_ti = __gen_cint_tn(mask);
   t3_ti = __emit_mask_and(t2_ti, mask_ti);
   two_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, ndwid, AM_REG, t3_ti);
   return(two_ti);
  }
 two_ti = __gen_tn(SR_BIT2S, ndwid);

//AIV 2STATE - LOOKATME - four_ti could be constant and produce bad code
//because it will be called with CON_ as a wrapper value
 if (nwlen > 10) 
  {
   __emit_4state_vec_to_2state_wide(two_ti, four_ti, cp_wlen);
   i = cp_wlen;
   goto maybe_mask;
  }

 ofs = 0;
 bofs = wlen_(blen)*WRDBYTES;
 /* t1 = ~bp[i]; ap[i] &= t1; */
 for (i = 0; i < cp_wlen; i++)
  {
   if (i == 0) four_ofs_ti = four_ti;
   else four_ofs_ti = __con_adradd_insn(SR_VEC, WBITS, four_ti, ofs);


   four_bpti = __con_adradd_insn(SR_VEC, WBITS, four_ti, bofs);
   t1_ti = __emit_bitnot(WBITS, four_bpti);
   t2_ti = __emit_bin_bitand(WBITS, four_ofs_ti, t1_ti);
   if (i == 0) new_ofs_ti = two_ti;
   else new_ofs_ti = __con_adradd_insn(SR_BIT2S, WBITS, two_ti, ofs);
   __emit_copy(WRDBYTES, t2_ti, new_ofs_ti);

   ofs += WRDBYTES;
   bofs += WRDBYTES;
  }

maybe_mask:
 /* zero the remaining high part */
 ofs = cp_wlen*WRDBYTES;
 for (; i < nwlen; i++)
  {
   new_ofs_ti = __con_adradd_insn(SR_BIT2S, WBITS, two_ti, ofs);
   __emit_store_cint(new_ofs_ti, 0, WRDBYTES);
   ofs += WRDBYTES;
  }

 /* may have to mask the last word */
 if (ubits_(ndwid) != 0)
  {
   ofs = (wlen_(ndwid)-1)*WRDBYTES;
   hghw_ti = __con_adradd_insn(SR_BIT2S, WBITS, two_ti, ofs);
   mask = __masktab[ubits_(ndwid)];
   mask_ti = __gen_cint_tn(mask);
   t1_ti = __emit_mask_and(hghw_ti, mask_ti);
   __emit_copy(WRDBYTES, t1_ti, hghw_ti);
  }
 return(two_ti);
}

/*
 * return T if any stren tmp
 */
extern int32 __any_stren_tn(int32 tmp_ti)
{
 int32 ttyp;

 ttyp = __tntab[tmp_ti].srtyp; 
 switch (ttyp) {
  /* SJM 12/05/04 ### ??? FIXME - can't distinguish stren/non stren byte */
  case SR_SSCAL: 
  case SR_SVEC:
   break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * return T if any scalar (a/b in one word) tmp
 */
extern int32 __any_scalar_tn(int32 tmp_ti)
{
 int32 ttyp;

 ttyp = __tntab[tmp_ti].srtyp; 
 switch (ttyp) {
  case SR_SSCAL: 
  case SR_SCAL:
   break;
  default: return(FALSE);
 }
 return(TRUE);
}
