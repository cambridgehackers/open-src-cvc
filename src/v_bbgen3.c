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
 * compiler asm gen routines - routines for post lowering asm gen here
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <dlfcn.h> 
#include <stdarg.h>
#include <unistd.h> 

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

/* local prototypes */
static int32 emit_real_binop(int32, int32, int32);
static void emit_real_cmp(struct bblk_t *, struct bblk_t *, int32, int32,
 int32);
static int32 oneword_binop(int32, int32, int32);
static int32 lower_subl(int32, int32);
static int32 insert_1wrd_ndxreg_mov(int32);
static int32 get_1wrd_amtype(int32);
static int32 prep_push_word_arg(int32);
static int32 prep_push_real_arg(int32);
static int32 prep_push_tn_addr_arg(int32);
static int32 wide_binop(int32, int32, int32, int32, int32);
static int32 wide_shift_binop(int32, int32, int32, int32);
static void lower_narrow_copy(int32, int32, int32);
static void lower_one_byte_copy(int32, int32);
static void lower_two_bytes_copy(int32, int32);
static void lower_three_bytes_copy(int32, int32);
static void lower_contab_src_copy(int32, int32, int32);
static void lower_setbytes(int32, byte, int32);
static void lower_setbyte_tnval(int32, byte, int32);
static void lower_setbyte_tnadr(int32, byte, int32);
static int32 emit_oneword_unop(int32, int32);
static void wide_unop(int32, int32, int32, int32);
static void invert_jmp_operands(int32, struct bblk_t *, struct bblk_t *,
 int32, int32, int32, int32);
static int32 emit_adradd_addl(int32, int32, int32, int32);
static int32 eval_con_oneword_binop(int32, int32, int32, int32);

static void copy_insn(int32, int32, int32);
static cmpsword bblk_node_cmp(const void *, const struct avlnode_t *);
static struct avlnode_t *bblk_dup_node_alloc(void *);
static cmpsword conflct_tn_node_cmp(const void *, const struct avlnode_t *);
static struct avlnode_t *conflct_tn_node_alloc(void *);
static cmpsword tn_node_cmp(const void *, const struct avlnode_t *);
static struct avlnode_t *tn_dup_node_alloc(void *);
static struct np_iconn_t *find_add_np_iconn_expr(struct avlhd_t *,
 struct expr_t *, struct net_pin_t *);
static struct avlnode_t *npic_node_alloc(void *);
static cmpsword npic_node_cmp(const void *, const struct avlnode_t *);
static cmpsword gate_conta_node_cmp(const void *, const struct avlnode_t *);
static struct gate_conta_t *find_gate_expr(struct avlhd_t *, struct expr_t *);
static struct avlnode_t *gate_conta_node_alloc(void *);

static void emit_call_asl_func(int32, int32, ...);
static void emit_call_asl_proc(int32, int32, ...);
static void emit_call_asl_funcandproc(int32, int32, int32, va_list);
static void chk_callasl_arg_num(int32);
static void set_asl_call_amode(struct amode_t *, int32, int32);

static void cond_jmp_insn(int32, struct bblk_t *, struct bblk_t *);
static void cond_sgn_jmp_insn(int32, struct bblk_t *, struct bblk_t *);
static struct ftval_t *fill_new_ft_node(int32 *, int32, int32, int32,
 struct ftval_t *);  
static cmpsword ft_node_cmp(const void *, const struct avlnode_t *);
static struct avlnode_t *formaltmp_alloc(void *);
static int32 find_add_formal_tmptab(int32, int32, int32, int32, 
 struct amode_t *, struct amode_t *);
static struct adradd_dup_t *find_addradd_tn(int32, int32, int32, size_t);
static struct avlnode_t *tn_adradd_node_alloc(void *);
static cmpsword tn_adradd_cmp(const void *, const struct avlnode_t *);

static int32 leal_insn(int32, ...);
static int32 move_srep_insn2(int32, int32, int32, int32, int32, va_list);
static int32 mark_keep_eval_insn(struct insn_t *);
static int32 eval_insn(int32, int32, int32, ...);
static int32 eval_srep_insn(int32, int32, int32, int32, int32, ...);
static int32 eval_srep_insn2(int32, int32, int32, int32, int32, va_list);
static int32 unary_insn(int32, int32, int32, ...);
static int32 mark_need_keep_store_into(struct insn_t *);
static void nores_insn(int32, int32, ...);
static void lower_copy(int32, int32, int32);
static struct ndxjmp_t *alloc_ndxjmp(struct bblk_t **, int32);
static void emit_comb_1bit_onebyte(word32, int32, int32);
static int32 emit_oneword_and(int32, int32, int32, int32, int32);
static int32 emit_oneword_shift(int32, int32, int32);
static int32 emit_oneword_sgn_shift(int32, int32, int32);
static int32 is_power_of2(word32);
static int32 flowg_jumps_to_next_event(int32);
static int32 get_set_insn_from_cc(int32, int32);
static int32 cnvt_constant_real_fr_w(int32, int32);
#ifndef __CVC32__
static int32 get_real_ld(int32);
#endif

extern void __emit_block_label(struct bblk_t *);
extern void __emit_schd_caev_const(int32, word64);
extern void __emit_schd_caev(int32, int32);
extern void __emit_cancel_ev(int32);
extern int32 __emit_calc_bufif_newstate(int32, int32, int32);
extern void __emit_eval_nmos_gate(int32);
extern void __emit_eval_rnmos_gate(int32);
extern void __emit_eval_pmos_gate(int32);
extern void __emit_eval_rpmos_gate(int32);
extern int32 __emit_eval_cmos_gate(int32, int32, int32, int32);
extern int32 __emit_eval_rcmos_gate(int32, int32, int32, int32);
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
extern void __emit_copy(int32, int32, int32);
extern void __emit_sxtnd_widwdn(int32, int32, int32, int32, int32);
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
extern int32 __emit_reg_qcaf_inhibit(int32); 
extern int32 __emit_scalar_wire_inhibit(int32);
extern int32 __emit_bsel_wirfrc_inhibit(int32, int32);
extern int32 __emit_stren_correct_frc(int32, int32);
extern int32 __emit_correct_frc(int32, int32);
extern int32 __emit_xmr_rooted_base(struct net_t *);
extern int32 __emit_psel_correct_frc(int32, int32, int32, int32);
extern int32 __emit_stren_psel_correct_frc(int32, int32, int32, int32);
extern void __emit_st_const_bsel(int32, int32, int32);
extern void __emit_ld_bsel(int32, int32, int32);
extern void __emit_ld_psel(int32, int32, int32, int32);
extern void __emit_st_psel(int32, int32, int32, int32);
extern int32 __emit_mask_and(int32, int32);
extern int32 __emit_srep_mask_and(int32, int32, int32, int32);
extern void __emit_jmp_eq_stmask(struct bblk_t *, struct bblk_t *, int32, 
 int32);
extern int32 __emit_get_packtowrd(int32, int32);
extern int32 __emit_qcol_comb_opands(int32, int32, int32);
extern int32 __emit_sub(int32, int32, int32);
extern int32 __emit_add(int32, int32, int32);
extern int32 __emit_adc(int32, int32);
extern int32 __emit_mult(int32, int32, int32);
extern int32 __emit_sgn_mult(int32, int32, int32);
extern int32 __emit_div(int32, int32, int32, int32);
extern int32 __emit_sgn_div(int32, int32, int32, int32);
extern int32 __emit_mod(int32, int32, int32, int32);
extern int32 __emit_sgn_mod(int32, int32, int32, int32);
extern int32 __emit_wide_sgn_lpow(int32, int32, int32, int32);
extern int32 __emit_wide_lpow(int32, int32, int32);
extern int32 __emit_add_real(int32, int32);
extern int32 __emit_sub_real(int32, int32);
extern int32 __emit_mult_real(int32, int32);
extern int32 __emit_div_real(int32, int32);
extern void __emit_real_div0_warning(struct st_t *);
extern void __emit_real_qcol_warning(struct st_t *);
extern int32 __emit_power_real(int32, int32);
extern int32 __emit_realneg(int32);
extern int32 __emit_real_abs(int32);
extern int32 __emit_uredxor(int32);
extern void __emit_lognot(int32, int32);
extern int32 __emit_bitnot(int32, int32);
extern void __emit_wid_unbitnot(int32, int32, int32, int32);
extern int32 __emit_bin_bitand(int32, int32, int32);
extern int32 __emit_bin_bitor(int32, int32, int32);
extern int32 __emit_bin_bitxor(int32, int32, int32);
extern int32 __emit_wid_bin_redor(int32, int32, int32);
extern int32 __emit_wid_un_redor(int32, int32, int32);
extern int32 __emit_wid_bin_redxnor(int32, int32, int32, int32);
extern int32 __emit_shiftl(int32, int32, int32);
extern int32 __emit_shiftr(int32, int32, int32);
extern int32 __emit_sgn_arshift(int32, int32, int32);
extern int32 __emit_swap_sign(int32, int32);
extern void __emit_sgnmask(int32, int32, int32);
extern int32 __emit_compute_emask(struct net_t *, int32, int32, int32, int32 *);
extern void __emit_func_subr(struct task_t *);
extern void __emit_call_func(struct task_t *);
#ifdef __CVC32__
extern int32 __emit_call_func_arg_dpi(struct net_t *, int32, int32, int32, 
 int32);
extern int32 __emit_get_export_arg_dpi(struct net_t *, int32 *);
#else
extern void __emit_call_func_arg_dpi(struct net_t *, int32, int32, int32,
 int32 *, int32 *, int32 *); 
extern int32 __emit_get_export_arg_dpi(struct net_t *, int32 *, int32 *);
#endif
extern void __emit_call_func_dpi(struct task_t *);
extern int32 __gen_ld_return_dpi(struct net_t *);
extern void __gen_ld_return_real_dpi(int32);
extern void __emit_sysfcall(int32, int32);
extern void __emit_sysfcall_stmtloc(int32, int32, struct st_t *);
extern void __emit_enter_task(struct task_t *);
extern void __emit_jmpto_tsk(struct task_t *, struct sy_t *);
extern void __emit_call_tsk(struct task_t *, struct sy_t *);
extern void __emit_tskdone_cleanup(void);
extern void __emit_tsk_return(void);
extern void __emit_func_brk_jmp(int32);
extern void __emit_stskcall(int32);
extern void __emit_exec_display(int32);
extern void __emit_ndx_jmp(int32, struct bblk_t **, size_t);
extern void __emit_repcnt_jmp(struct bblk_t *, struct bblk_t *, int32, int32, 
 int32);
extern void __emit_qcol_jmp_any1(struct bblk_t *, struct bblk_t *, int32, 
 int32, int32);
extern void __emit_jmp(struct bblk_t *);
extern void __emit_jmp_0(struct bblk_t *, struct bblk_t *, int32);
extern void __emit_jmpor_0(struct bblk_t *, struct bblk_t *, int32, int32);
extern void __emit_jmp_eq(struct bblk_t *, struct bblk_t *, int32, int32);
extern void __emit_jmp_eq_abpart(struct bblk_t *, struct bblk_t *, int32, 
 int32);
extern int32 __emit_cmp_wide(int32, int32, int32, int32, int32);
extern void __emit_jmp_byte_eq(struct bblk_t *, struct bblk_t *, int32, int32);
extern void __emit_cmp(int32, int32);
extern void __emit_testl(int32);
extern void __emit_st_sete(int32, int32);
extern void __emit_jmp_ptr_eq(struct bblk_t *, struct bblk_t *, int32,
 int32);
extern void __emit_jmp_idp_eq(struct bblk_t *, struct bblk_t *, int32);
extern void __emit_jmp_real0(struct bblk_t *, struct bblk_t *, int32);
extern int32 __emit_cmp_widomitxz_ne(int32, int32);
extern int32 __emit_cmp_widall1(int32);
extern void __emit_jmp_sgn_cmp(struct bblk_t *, struct bblk_t *, int32,
 int32, int32);
extern int32 __emit_bytecmp(int32, int32, int32);
extern int32 __emit_wordcmp(int32, int32, int32);
extern void __emit_narrow_byte_eq(int32, struct bblk_t *, struct bblk_t *,
 int32, int32);
extern void __emit_jmp_cmp(struct bblk_t *, struct bblk_t *, int32, int32,
  int32);
extern int32 __chk_jmp_cmp_ops(int32, int32, int32);
extern void __emit_cmp_set_type(int32, int32, int32, int32, int32);
extern void __emit_jmp_real_eps_cmp(struct bblk_t *, struct bblk_t *, int32);
extern void __emit_sgnbit_on_jmp(struct bblk_t *, struct bblk_t *, int32);
extern int32 __emit_widcas(int32, int32, int32);
extern int32 __emit_widcasx(int32, int32, int32);
extern int32 __emit_widcasz(int32, int32, int32);
extern int32 __emit_wide_cvt_bool(int32, int32);
extern void __emit_pop_xstk(int32);
extern int32 __emit_ld_downrel_idp(int32);
extern int32 __emit_ld_uprel_idp(int32);
extern int32 __emit_set_thd_nxtst(struct st_t *);
extern void __emit_set_thd_actionst(struct st_t *);
extern void __emit_restore_assoc_tsk(int32);
extern int32 __emit_setsave_assoc_tsk(int32);
extern void __emit_st_thd_ret_lab_ndx(int32);
extern int32 __emit_thread_auto_cleanup(void);
extern void __emit_save_curthd_idp(void);
extern int32 __emit_restore_thd_idp(void);
extern void __emit_bld_nb_nodelay_tev(int32);
extern void __emit_bldsched_proc_del(int32, int32);
extern void __emit_bldsched_proc_del_nt(int32, int32);
extern void __emit_bldsched_proc_del_const(int32, word64);
extern void __emit_bldsched_proc_del_const_nt(int32, word64);
extern void __emit_arm_ectrl(int32, int32);
extern void __emit_save_tevp_to_schd(int32, int32);
extern int32 __emit_schd_nbrhs_dctrl(int32, int32, int32);
extern int32 __emit_schd_nbrhs_dctrl_const(int32, int32, int32);
extern void __emit_schd_nbrhs_nomem_dctrl_const(int32, int32);
extern int32 __emit_sched_nb_pnd0_lhs_varndx(int32, int32, int32, int32); 
extern int32 __emit_schd_nbrhs_varndx_dctrl_const(int32, int32, int32, int32);
extern int32 __emit_schd_nbrhs_varndx_dctrl(int32, int32, int32, int32, int32);
extern int32 __emit_sched_nb_pnd0_lhs_varndx_concat(int32, int32, int32,
 int32, int32); 
extern int32 __emit_schd_nbrhs_varndx_dctrl_concat(int32, int32, int32, int32,
 int32, int32);
extern int32 __emit_schd_nbrhs_varndx_dctrl_const_concat(int32, int32, int32,
 int32, int32);
extern void __emit_schd_nbrhs_scalar_dctrl(int32, int32, int32);
extern void __emit_schd_nbrhs_scalar_dctrl_const(int32, int32, int32);
extern int32 __emit_arm_nb_ectrl(int32, int32);
extern int32 __emit_arm_nb_varndx_ectrl(int32, int32, int32); 
extern void __emit_nb_next_event(int32);
extern int32 __emit_nb_cur_tev_reg(void);
extern void __emit_setup_namblk(int32);
extern void __emit_setup_task_thd(int32, int32);
extern void __emit_setup_task_thd_auto(int32, int32, int32);
extern void __emit_schd_fork(int32, int32);
extern void __emit_exec_qc_assign(int32, int32, int32, int32, int32);
extern void __emit_exec_qc_force(int32, int32, int32, int32, int32);
extern void __emit_exec_qc_wireforce(int32, int32, int32, int32, int32);
extern void __emit_exec_qc_tran_wireforce(int32, int32, int32, int32, int32);
extern void __emit_exec_qc_deassign(int32);
extern void __emit_exec_qc_deassign_force(int32, int32, int32, int32);
extern void __emit_exec_qc_wirerelease(int32, int32, int32, int32);
extern void __emit_exec_qc_tran_wirerelease(int32, int32, int32, int32);
extern void __emit_exec_cause(int32, int32);
extern int32 __emit_exec_dsable(int32);
extern void __emit_jmp_dce_off(struct bblk_t *, struct bblk_t *, int32);
extern int32 __gen_dce_expr_bp(struct dcevnt_t *);
extern int32 __gen_dce_schd_tev(struct delctrl_t *);
extern int32 __gen_gate_adr_tn(struct gate_t *);
extern int32 __emit_downrel_targ_to_ref(int32);
extern int32 __emit_uprel_targ_to_ref(int32);
extern void __emit_event_coverage(struct delctrl_t *);
extern void __emit_stmt_coverage(struct st_t *);
extern void __emit_trigger_ectrl(int32, struct delctrl_t *);
extern void __emit_nb_trigger_ectrl(int32);
extern void __emit_monit_trigger(void);
extern void __emit_fmonit_trigger(int32);
extern void __emit_assign_qcaf(int32, int32, int32);
extern void __emit_assign_scalar_qcaf(int32, int32, int32);
extern void __emit_assign_qcaf_regform(int32, int32, int32);
extern void __emit_misc_terr(void);
extern int32 __emit_exec_wide_logic_gate(int32, int32, int32);
extern int32 __emit_exec_np_tranif(int32);
extern void  __emit_immed_eval_trifchan(int32);
extern void __emit_timing_check_record(int32);
extern int32 __gen_tchk_tn(struct chktchg_t *, int32);
extern int32 __gen_del_tn(int32, void *);
extern void __emit_sched_scalar_mipd(int32, int32, struct net_pin_t *npp);
extern void __emit_sched_vec_mipd_bit(int32, int32, int32);
extern void __emit_process_mipd_nchg_ev(int32);
extern void __emit_process_mipd_scalar_nchg_ev(int32);
extern int32 __emit_force_active(int32, int32);
extern void __emit_process_trpthdst_enter(int32);
extern void __emit_eval_tran_drvr_1bit(int32, int32);
extern void __emit_eval_tran_drvr_1bit_vector(int32, int32);
extern int32 __emit_bpart_of_tran(void);
extern void __emit_eval_htran_wire_1bit_nchg(int32, int32, int32);
extern void __emit_eval_htran_wire_1bit(int32, int32);
extern void __emit_eval_htran_stwire_1bit(int32, int32);
extern void __emit_eval_htran_stwire_1bit_nchg(int32, int32, int32);
extern int32 __emit_eval_tran_bidchan_1bit(int32);
extern int32 __emit_eval_tran_scalar_bidchan_1bit(int32);
extern int32 __emit_eval_tran_stbidchan_1bit(int32);
extern int32 __emit_update_tran_harddrvs(int32);
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
static void cond_real_jmp_insn(int32, struct bblk_t *, struct bblk_t *);
extern void __emit_get_del32(int32, int32 *, int32 *, int32);
extern void __emit_reschedule_1wev32(int32, int32, int32);
#else
static void lower_bytes_four_to_seven64(int32, int32, int32);
static void lower_four_byte_copy(int32, int32);

extern void __emit_get_del64(int32, int32 *, int32);
extern void __emit_reschedule_1wev64(int32, int32);
#endif
extern void  __emit_jmp_cmp64_idp_lessthan(struct bblk_t *, struct bblk_t *, 
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
extern void __emit_call_mdprt_bsel(int32, int32, int32, int32);
extern void __emit_call_mdprt_bsel_nchg(int32, int32, int32, int32, int32);
extern void __emit_call_mdprt_bsel_dmpv(int32, int32, int32, int32, int32, 
 int32);
extern void __emit_call_mdprt_bsel_nchg_dmpv(int32, int32, int32, int32, int32, 
 int32, int32);
extern int32 __emit_ld_nchg_bptr(struct net_t *);
extern int32 __gen_process_nchg(struct net_chg_t *);
extern int32 __gen_process_nchg_to_reg_tn(struct net_chg_t *);
extern int32 __gen_ctevp_adr_tn(struct ctev_t *);
extern int32 __gen_ctevp_trigger_flag(int32);
extern int32 __gen_mipd_enter_adr_tn(int32);
extern int32 __gen_process_wire_enter(int32);
extern void __emit_add_dmpvlst(int32);
extern void __emit_add_dmpvlst_array(int32, int32);
extern void __emit_add_dmpportlst(int32);
extern void __emit_add_dmpvlst_mdprt(int32);
extern void __emit_add_togglelst_el(int32);
extern void __emit_add_togglelst_el_port(int32);
extern void __emit_add_dmpportlst_mdprt(int32);
extern void __emit_store_cint(int32, int32, int32);
extern void __emit_setr0(int32);
extern void __emit_suspend(void);
extern void __emit_complete(void);
extern void __emit_next_event(void);
extern void __emit_next_nchg_event(void);
extern void __emit_leave(void);
extern void __emit_enter_proc(struct st_t *);
extern void __emit_enter_mdc(int32);
extern void __emit_enter_nb_proc(struct st_t *);
extern void __emit_enter_nb_proc_free(struct st_t *);
extern void __emit_enter_thd_ret(int32);
extern void __emit_enter_decl(struct net_t *);
extern void __emit_enter_npp(struct net_t *);
extern void __emit_enter_mipd(int32);
extern void __emit_multfi_subr(int32, struct net_t *, struct mod_t *);
extern void __emit_enter_conta(int32);
extern void __emit_enter_iconn(int32);
extern void __emit_enter_port(int32);
extern void __emit_enter_gate_conta(int32);
extern void __emit_enter_gate_delay_assign(int32);
extern void __emit_call_conta(struct conta_t *);
extern void __emit_call_iconn(int32);
extern void __emit_call_gate_conta(int32);
extern int32 __emit_save_arg(void);
extern void __copy_arg(int32, int32, int32);
extern void __memloc_emit_set_idp(int32);
extern int32 __emit_save_idp(int32);
extern int32 __emit_save_downidp(int32);
extern int32 __emit_save_cur_idp(void);
extern int32 __emit_new_auto_idp_area(int32);
extern void __emit_cp_auto_idp_area_func(int32, int32);
extern void __emit_return(void);
extern int32 __emit_ld_nbrhs_valwp(int32, int32, int32, int32);
extern int32 __emit_ld_nbrhs_scalar_val(int32, int32);
extern int32 __emit_ld_gate_val_from_tev(int32, int32);
extern void __emit_set_tev_gate_val(int32, int32);
extern void __emit_set_tevp_trigger_off(int32);
extern void __emit_jmp_real_cmp(struct bblk_t *, struct bblk_t *,
 int32, int32, int32); 
extern void __emit_enter_bblk_dbgmsg(void);
extern void __emit_rhs_conta_stren(int32, int32, int32);
extern void __st_insn(int32, int32, ...);
extern int32 __move_insn(int32, int32, int32, ...);
extern int32 __move_srep_insn(int32, int32, int32, int32, int32, ...);
extern int32 __emit_inum(void);
extern int32 __emit_dbg_inum(void);
extern int32 __ld_nchg_var_ndx(void);
extern int32 __count_ndxjmp_lab_setsiz(struct bblk_t **, int32);
extern void __bld_ndxjmp_lab_set(struct bblk_t **, int32);
extern int32 __is_constant(int32);
extern word32 __get_con_wrd_aval_nd0bval(int32);
extern word32 __get_wrd_con_val(int32);
extern void __expand_copy(struct insn_t *);
extern int32 __cmp_amodes(struct amode_t *, struct amode_t *);
extern int32 __ld_netadr_tn(struct net_t *);
extern int32 __gen_ld_netbp(struct net_t *);
extern int32 __gen_ld_idp_netbp_addr(struct net_t *);
extern int32 __gen_stmt_tn(struct st_t *);
extern int32 __gen_mdat_storage_area(struct mod_t *);
extern int32 __emit_random_with_seed(int32);
extern int32 __emit_random(void);
extern void __emit_rhs_psel_wide(int32, int32, int32, int32, int32, int32);
extern void __emit_rhs_psel_wide_2state(int32, int32, int32, int32);
extern int32 __emit_rhs_psel(int32, int32, int32, int32);
extern int32 __emit_rhs_psel_2state(int32, int32, int32);
extern void __emit_rhs_st_psel(int32, int32, int32);
extern int32 __emit_new_narrow_word(int32, int32, int32);
extern int32 __gen_xpr_tn(struct expr_t *);

/* externs located in other files */
extern struct insn_t *__alloc_insn(int32);
extern void __init_amode(struct amode_t *);
extern void __set_amode(struct amode_t *, va_list);
extern void __set_back_edge(struct bblk_t *);
extern struct bblk_t *__alloc_bblk(int32);
extern void __add_insn_toend(struct insn_t *);
extern void __insert_after_insn(struct insn_t *, struct insn_t *);
extern struct bbedge_t *__alloc_bbedge(void);
extern char *__xi_stralloc(char *);
extern char *__my_malloc(size_t);
extern int32 __get_tnwid(int32);
extern int32 __gen_tn(int32, int32);
extern struct mod_t *__find_mod_task_of_var(struct net_t *, struct task_t **);
extern struct avlnode_t *__alloc_avlnode(void *);
extern void __init_tn_dup_trees(void);
extern struct avlhd_t *__allocinit_avlhd(void);
extern int32 __con_adradd_insn(int32, int32, int32, size_t);
extern int32 __var_adradd_insn(int32, int32, int32, int32);
extern void __linkout_insn(struct insn_t *, int32);
extern void __free_1insn(struct insn_t *);
extern struct avlnode_t *__avltfind(void *, struct avlhd_t *);
extern struct sy_t *__get_nets_containing_sy(struct net_t *, struct mod_t **);
extern int32 __get_bpti(int32);
extern int32 __gen_contab_tn(int32, int32, int32, int32, int32, int32);  
extern int32 __gen_cint_tn(word32);
extern struct tn_dup_t *__find_add_dup_tn(struct avlhd_t *, word32);
extern struct bblk_t *__find_add_dup_bblk(struct avlhd_t *, struct bblk_t *);
extern int32 __invert_cc(int32);
extern struct np_iconn_t *__add_np_iconn_expr(struct net_pin_t *, 
 struct expr_t *);
extern void __np_iconn_dup_node_free(void *);
extern struct gate_conta_t *__add_gate_expr(struct gate_t *, 
 struct net_pin_t *);
extern void __gate_conta_dup_node_free(void *);
extern int32 __is_nlptr_comlab(int32);
extern struct asl_info_t *__to_aslinfo_rec(int32);
extern int32 __check_delay_constant(union del_u, int32, word64 *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern void __obj_dup_node_free(void *);
extern void __start_bblk(struct bblk_t *);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern int32 __get_con_adradd_xvi(int32);
extern double __asl_movr_fr_w(word32 *, int32);
extern double __asl_movr_fr_sgnw(word32 *, int32);
extern int32 __tmp_is_2state(int32);
extern struct prep_obj_t *__find_add_obj(struct avlhd_t *, void *);


#ifdef __XPROP__
extern int32 __emit_get_xprop_accum(struct net_t *);
extern void __emit_get_xprop_accum_init(struct net_t *, int32, int32);
extern void __emit_get_xprop_accum_init_wide(struct net_t *, int32);
extern void __emit_get_xprop_accum_to_self(struct net_t *, int32, int32);
extern void __emit_get_xprop_accum_to_self_wide(struct net_t *, int32);
extern int32 __emit_per_bit_xprop_accum(struct st_t *, int32, int32);
extern void __emit_stmt_assign_to_accum_wide(struct st_t *, struct st_t *,
 int32, int32);
extern void __emit_stmt_assign_to_accum_1w(struct st_t *, struct st_t *,
 int32, int32);
extern void __emit_stmt_assign_to_accum_id_1w(struct net_t *, struct st_t *, 
 int32, int32);
extern void __emit_stmt_assign_to_accum_id_wide(struct net_t *, struct st_t *, 
 int32, int32);
extern void __emit_xprop_check_case_net_set(struct st_t *, int32);
extern void __emit_set_xprop_accum_block(struct st_t *);
extern void __emit_set_restore_xprop_accum_block(struct st_t *, int32);
extern void __emit_set_restore_xprop_accum_block_toself(struct st_t *);
extern void __emit_set_restore_xprop_accum_block_nodefault(struct st_t *, 
 int32, int32);
extern void __emit_trace_xprop_write(struct st_t *, int32, int32, int32);
extern void __emit_trace_xprop_write_wide(struct st_t *, int32, int32, int32);
extern int32 __emit_xprop_xcount(int32);
extern void __emit_trigger_ectrl_xprop(int32, struct delctrl_t *, int32);
extern int32 __emit_has_xedge_wide(int32, int32, int32);
extern int32 __emit_has_xedge_wide_st(int32, int32, int32);
extern void __emit_set_tev_enter_adr_xprop(int32, int32);
extern int32 __emit_xprop_xedge_net(struct st_t *);
extern void __emit_xprop_set_xedge_net(struct st_t *, struct net_t *, int32);
#endif

extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __my_free(void *, size_t);

/* max number of copy expandable words */
/* extra large because inlining is 2x as fast as using memcpy */
/* FIXME - this can be must smaller when rep insn are used */
#define XPND_COPY_WORDS 16 
/* T => if nbytes aligned on words and is less than the expandable max */
#define copy_xpnd_(nbytes) \
     ((nbytes <= WRDBYTES * XPND_COPY_WORDS) && (nbytes % WRDBYTES) == 0)

extern const word32 __masktab[];

extern void __emit_block_label(struct bblk_t *bbp)
{
 nores_insn(I_BBLK_LABEL, AM_NONE, AM_BBLK, bbp);
}

extern void __emit_schd_caev(int32 cap_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_tn_addr_arg(cap_ti);
 emit_call_asl_func(ASL_SCHD_CAEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * schedule conta with a constant delay
 */
extern void __emit_schd_caev_const(int32 tevp_ti, word64 cadel)
{
 int32 a0_ti;
 
 /* high part is zero */
 if (cadel == 0) 
  {
   a0_ti = prep_push_word_arg(tevp_ti);
   emit_call_asl_proc(ASL_SCHD_CAEV_CONST0, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
 else
  {
   a0_ti = prep_push_word_arg(tevp_ti);
   emit_call_asl_proc(ASL_SCHD_CAEV_CONST, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
}

extern void __emit_cancel_ev(int32 tevp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(tevp_ti);
 emit_call_asl_proc(ASL_CANCEL_EV, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_calc_bufif_newstate(int32 gwrd_ti, int32 base_ti,
 int32 stval_ti)
{
 int32 new_gateval_ti, a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(stval_ti);
 a1_ti = prep_push_word_arg(base_ti);
 a0_ti = prep_push_word_arg(gwrd_ti);
 emit_call_asl_proc(ASL_CALC_BUFIF_NEWSTATE, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 new_gateval_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, AR_AX);
 return(new_gateval_ti);
}

extern void __emit_eval_nmos_gate(int32 uwrd_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(uwrd_ti);
 emit_call_asl_proc(ASL_EVAL_NMOS_GATE, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_eval_rnmos_gate(int32 uwrd_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(uwrd_ti);
 emit_call_asl_proc(ASL_EVAL_RNMOS_GATE, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_eval_pmos_gate(int32 uwrd_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(uwrd_ti);
 emit_call_asl_proc(ASL_EVAL_PMOS_GATE, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_eval_rpmos_gate(int32 uwrd_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(uwrd_ti);
 emit_call_asl_proc(ASL_EVAL_RPMOS_GATE, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_eval_cmos_gate(int32 nmos_gwrd_ti, int32 pmos_gwrd_ti,
 int32 old_gateval_ti, int32 wtyp)
{
 int32 outchg_ti, wtyp_ti, a0_ti, a1_ti, a2_ti, a3_ti;

 wtyp_ti = __gen_cint_tn(wtyp);
 a3_ti = prep_push_word_arg(wtyp_ti);
 a2_ti = prep_push_word_arg(old_gateval_ti);
 a1_ti = prep_push_word_arg(pmos_gwrd_ti);
 a0_ti = prep_push_word_arg(nmos_gwrd_ti);
 emit_call_asl_func(ASL_EVAL_CMOS_GATE, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 outchg_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(outchg_ti);
}

//SJM? -notice same as cmos eval except for wrapper routine called
extern int32 __emit_eval_rcmos_gate(int32 nmos_gwrd_ti, int32 pmos_gwrd_ti,
 int32 old_gateval_ti, int32 wtyp)
{
 int32 outchg_ti, wtyp_ti, a0_ti, a1_ti, a2_ti, a3_ti;

 wtyp_ti = __gen_cint_tn(wtyp);
 a3_ti = prep_push_word_arg(wtyp_ti);
 a2_ti = prep_push_word_arg(old_gateval_ti);
 a1_ti = prep_push_word_arg(pmos_gwrd_ti);
 a0_ti = prep_push_word_arg(nmos_gwrd_ti);
 emit_call_asl_func(ASL_EVAL_RCMOS_GATE, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 outchg_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(outchg_ti);
}

/*
 * generate temp for udp l table address
 */
extern int32 __gen_l_udp_table(struct udp_t *udpp)
{
 int32 tni;
 struct tn_t *tnp;

 tni = __gen_tn(SR_VEC, WBITS);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_L_UDPADR;
 /* DBG remove -- */
 if (udpp->u_idnum == -1) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 tnp->tncu.el_ndx = udpp->u_idnum;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
#ifdef __VALTRK__
 tnp->nd_valtrk_idp_siz = TRUE;
#endif
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) udpp->utab->ludptab;
 return(tni);
}

/*
 * generate temp for udp r table address
 */
extern int32 __gen_e_udp_table(struct udp_t *udpp)
{
 int32 tni;
 struct tn_t *tnp;

 tni = __gen_tn(SR_VEC, WBITS);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_E_UDPADR;
 /* DBG remove -- */
 if (udpp->u_idnum == -1) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 tnp->tncu.el_ndx = udpp->u_idnum;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
#ifdef __VALTRK__
 tnp->nd_valtrk_idp_siz = TRUE;
#endif
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) udpp->utab->eudptabs;
 return(tni);
}

extern int32 __emit_udp_wide_adjust_state(int32 gstate_ti, int32 nins_ti)
{
 int32 r_ti, a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(nins_ti);
 a0_ti = prep_push_tn_addr_arg(gstate_ti);
 emit_call_asl_func(ASL_UDP_WIDE_ADJSTATE, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

extern void __set_widconta_new_gateval(int32 mastrhs_ti)
{
 int32 tnwid_ti, a0_ti, a1_ti;

 tnwid_ti = __gen_cint_tn(__get_tnwid(mastrhs_ti));
 a1_ti = prep_push_word_arg(tnwid_ti);
 a0_ti = prep_push_tn_addr_arg(mastrhs_ti);
 emit_call_asl_proc(ASL_SET_RHS_NEW_GATEVAL, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_set_new_gateval(int32 op1_ti)
{
 int32 r_ti;

 /* AIV 12/29/06 - need a move if it is ndxreg - mem2mem illegal */
 r_ti = insert_1wrd_ndxreg_mov(op1_ti);
 /* SJM 12/01/07 - notice this does not violate only mov/st to memory */
 /* AIV 01/22/09 - this should be storel to keep aligned */
 __st_insn(I_STOREL, AM_REG, r_ti, AM_NLO, NLO_NEWGVAL);
}

extern void __emit_set_old_gateval(int32 op1_ti)
{
 int32 r_ti;

 /* AIV 12/29/06 - need a move if it is ndxreg - mem2mem illegal */
 r_ti = insert_1wrd_ndxreg_mov(op1_ti);
 /* AIV 01/22/09 - this should be storel to keep aligned */
 __st_insn(I_STOREL, AM_REG, r_ti, AM_NLO, NLO_OLDGVAL);
}

extern void __emit_set_new_inval(int32 op1_ti)
{ 
 int32 r_ti;

 /* AIV 12/29/06 - need a move if it is ndxreg - mem2mem illegal */
 r_ti = insert_1wrd_ndxreg_mov(op1_ti);
 /* AIV 01/22/09 - this should be storel to keep aligned */
 __st_insn(I_STOREL, AM_REG, r_ti, AM_NLO, NLO_NEWINPUTVAL);
}

extern void __emit_stren_schd_1gev(int32 gp_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_func(ASL_STREN_SCHD_1GEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_schd_1gev(int32 gp_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_proc(ASL_SCHD_1GEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_schd_1gev_const(int32 tevp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_SCHD_1GEV_CONST, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_schd_1gev_pnd0(int32 tevp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_SCHD_1GEV_PND0, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_cancele_pend_nochg_1gev(int32 gp_ti, int32 tevp_ti)
{
 int32 chg_outwir_ti, a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_func(ASL_CANCELE_PEND_NOCHG_1GEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 chg_outwir_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(chg_outwir_ti);
}

extern void __emit_chg_gate_outwire(int32 tevp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_CHG_GATE_OUTWIRE, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_cancele_pend_chg_1gev(int32 gp_ti, int32 tevp_ti)
{
 int32 chg_outwir_ti, a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_func(ASL_CANCELE_PEND_CHG_1GEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 chg_outwir_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(chg_outwir_ti);
}

extern void __emit_pend_nochg_1gev(int32 tevp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_func(ASL_PEND_NOCHG_1GEV, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_stren_pend_chg_1gev(int32 gp_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_proc(ASL_STREN_PEND_CHG_1GEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_pend_chg_1gev(int32 gp_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_proc(ASL_PEND_CHG_1GEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_pend_chg_1gev_const(int32 tevp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_PEND_CHG_1GEV_CONST, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_reschd_caev(int32 cap_ti, int32 tevp_ti) 
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(cap_ti);
 emit_call_asl_func(ASL_RESCHD_CAEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * reschedule conta with a constant delay
 */
extern void __emit_reschd_caev_const(int32 tevp_ti, word64 cadel)
{
 int32 a0_ti;
 
 /* high part is zero */
 if (cadel == 0) return;
 else
  {
   a0_ti = prep_push_tn_addr_arg(tevp_ti);
   emit_call_asl_proc(ASL_RESCHD_CAEV_CONST, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
}

//////////////////////AIV NEW PLI INSNS
extern void __emit_chk_dce_cbvc(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_CHK_DCE_CBVC, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_chk_ld_vpiputv_driver(int32 np_ti, int32 drv_apti)
{
 int32 a0_ti, a1_ti;

 /* SJM 04/20/07 - in place writeable (addr) must be 1st arg of asl wrappers */
 /* notice args here in reverse order of als info tab */
 a1_ti = prep_push_tn_addr_arg(drv_apti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_CHK_LD_VPIPUTV_DRIVER, 2, a0_ti, a1_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_chk_gate_vpi_chg(int32 gndx)
{
 int32 cint_ti, a0_ti;

 cint_ti = __gen_cint_tn(gndx);
 a0_ti = prep_push_word_arg(cint_ti);
 emit_call_asl_proc(ASL_CHK_GATE_VPI_CHG, 1, a0_ti);
 chk_callasl_arg_num(1);
}
//////////////////////////////////////////

/*
 * emit a copy insn - copies n bytes from op1 src to op2 dst
 */
extern void __emit_copy(int32 nbytes, int32 op1, int32 op2)
{
 /* AIV 08/17/06 - tmps can attempt to copy to itself due */
 /* to constant expression folding during code gen time */
 if (op1 == op2) return;

 /* DBG remove -- */
 if (op1 == -1 || op2 == -1) __misc_terr(__FILE__, __LINE__);
 if (nbytes == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 copy_insn(op1, op2, nbytes);
}

extern void __emit_sxtnd_widwdn(int32 op1_ti, int32 op2_ti, int32 rhswid,
 int32 dstwid, int32 is_2state)
{
 int32 rhswid_ti, dstwid_ti, a0_ti, a1_ti, a2_ti, a3_ti;
 
 dstwid_ti = __gen_cint_tn(dstwid);
 a3_ti = prep_push_word_arg(dstwid_ti);
 rhswid_ti = __gen_cint_tn(rhswid);
 a2_ti = prep_push_word_arg(rhswid_ti);

 a1_ti = prep_push_tn_addr_arg(op2_ti);
 a0_ti = prep_push_tn_addr_arg(op1_ti);
 if (is_2state)
  {
   emit_call_asl_proc(ASL_SGN_XTND_WIDEN_2STATE, 4, a3_ti, a2_ti, a1_ti, a0_ti);
  }
 else emit_call_asl_proc(ASL_SGN_XTND_WIDEN, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}

extern int32 __emit_movw_fr_r(int32 dbl_ti)
{
 int32 wrd_ti, a0_ti, a1_ti, xvi;
 word32 *wp;
 word32 aval, bval;
 double d1;

 /* AIV 09/10/10 - should check for constant here and fold at compile time */
 if (__tntab[dbl_ti].comlab_typ == COMLAB_CONADR)
  {
   xvi = __get_con_adradd_xvi(dbl_ti);
   wp = &(__contab[xvi]);
   memcpy(&d1, wp, sizeof(double)); 
   aval = ver_rint_(d1);
   bval = 0;
   xvi = __allocfill_cval_new(&aval, &bval, 1);
   wrd_ti = __gen_contab_tn(xvi, WBITS, FALSE, FALSE, FALSE, SR_VEC);
   return(wrd_ti);
  }

//SJM FIXME ++GX - think code wrong - if dbl ti same should find in formal tn
 wrd_ti = __gen_tn(SR_VEC, WBITS); 
 a1_ti = prep_push_real_arg(dbl_ti);
 a0_ti = prep_push_tn_addr_arg(wrd_ti);
 emit_call_asl_proc(ASL_MOVW_FR_R, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 return(wrd_ti);
}

extern int32 __emit_movw_fr_r_2state(int32 dbl_ti)
{
 int32 res_ti, a0_ti, xvi;
 word32 *wp;
 word32 aval, bval;
 double d1;

 /* AIV 09/10/10 - should check for constant here and fold at compile time */
 if (__tntab[dbl_ti].comlab_typ == COMLAB_CONADR)
  {
   xvi = __get_con_adradd_xvi(dbl_ti);
   wp = &(__contab[xvi]);
   memcpy(&d1, wp, sizeof(double)); 
   aval = ver_rint_(d1);
   bval = 0;
   xvi = __allocfill_cval_new(&aval, &bval, 1);
   res_ti = __gen_contab_tn(xvi, WBITS, FALSE, FALSE, FALSE, SR_BIT2S);
   return(res_ti);
  }

 a0_ti = prep_push_real_arg(dbl_ti);
 emit_call_asl_proc(ASL_MOVW_FR_R_2STATE, 1, a0_ti);
 chk_callasl_arg_num(2);

 res_ti = __gen_tn(SR_BIT2S, WBITS);
 __st_insn(I_STOREA, AM_REG, AR_AX, AM_REG, res_ti);
 return(res_ti);
}

extern int32 __emit_movw_fr_scal(int32 blen, int32 rhs_ti, int32 is_stren)
{
 int32 res_apti, r1_ti, r2_ti, r3_ti, one_ti, res_bpti;

 res_apti = __gen_tn(SR_VEC, blen); 

 /* r1 a part and r3 bpart */
 one_ti = __gen_cint_tn(1);

 /* just and with 1 for the a part */
 r1_ti = emit_oneword_and(one_ti, rhs_ti, FALSE, -1, -1);
 __st_insn(I_STOREA, AM_REG, r1_ti, AM_REG, res_apti);
 /* SJM 07/14/06 - was using r1 - not following flow graph pattern */
 /* shift and mask for the b part */
 r2_ti = emit_oneword_sgn_shift(I_SARL, one_ti, rhs_ti);

 /* AIV 08/21/08 - only mask if it is a strength value */
 if (is_stren)
  {
   r3_ti = emit_oneword_and(one_ti, r2_ti, FALSE, -1, -1);
  }
 else r3_ti = r2_ti;
 /* only one instruction but could save doing mask with another I_ insn */
 /* unusual insn since need to set both a and b part at same time */

 /* SJM 07/17/06 - removed wrong consistency check */
 /* SJM 07/17/06 - was using wrong unset tn reg here */
 res_bpti = __get_bpti(res_apti);
 __st_insn(I_STOREA, AM_REG, r3_ti, AM_REG, res_bpti);
 return(res_apti);
} 

/*
 * move to 2state word from scalar
 */
extern int32 __emit_movw_2s_fr_scal(int32 blen, int32 rhs_ti, int32 is_stren)
{
 int32 res_ti, one_ti, r1_ti, am_type;

 one_ti = __gen_cint_tn(1);
 if (is_stren)
  {
   rhs_ti = emit_oneword_and(one_ti, rhs_ti, FALSE, -1, -1);
  }

 am_type = get_1wrd_amtype(rhs_ti);
 r1_ti = __move_insn(TN_VAL, I_MOVA, am_type, rhs_ti);
 res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, blen, 
    AM_NLO_ARRNDX, r1_ti, NLO_4STATE_TO2);
 return(res_ti);
} 

/*
 * move from a scalar 4-state to scalar 2-state
 */
extern int32 __emit_toscal_2s_fr_scal_4s(int32 rhs_ti, int32 is_stren)
{
 int32 res_ti, one_ti, r1_ti, am_type;

 one_ti = __gen_cint_tn(1);
 if (is_stren)
  {
   rhs_ti = emit_oneword_and(one_ti, rhs_ti, FALSE, -1, -1);
  }

 am_type = get_1wrd_amtype(rhs_ti);
 r1_ti = __move_insn(TN_VAL, I_MOVA, am_type, rhs_ti);
 res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL2S, 1, 
    AM_NLO_ARRNDX, r1_ti, NLO_4STATE_TO2);
 return(res_ti);
} 

extern int32 __emit_movint_fr_svec(int32 svecadr_ti)
{
 int32 am_type, r1_ti, res_ti;

 res_ti = __gen_tn(SR_SVEC, WBITS);
 am_type = get_1wrd_amtype(svecadr_ti);
 /* AIV 10/12/06 - had a misc_terr for non-ndxreg but it is ok if not */
 r1_ti = __move_insn(TN_VAL, I_MOVZBL, am_type, svecadr_ti);
 __st_insn(I_STOREA, AM_REG, r1_ti, AM_REG, res_ti); 
 return(res_ti);
}

extern int32 __emit_movabw_fr_svec(int32 svec_pti, int32 blen)
{
 int32 res_ti, blen_ti, a0_ti, a1_ti, a2_ti;
 int32 res_bpti;

 
 res_ti = __gen_tn(SR_VEC, blen);
 blen_ti = __gen_cint_tn(blen);
 /* AIV 12/29/06 - added this insn because cannot pass a pointer to a tmp */
 /* which is <= wbits (no leal) because this makes it a tmp which */
 /* cannot be put into a register */
 if (blen <= WBITS)
  {
   a1_ti = prep_push_word_arg(blen_ti);
   a0_ti = prep_push_tn_addr_arg(svec_pti);
   emit_call_asl_func(ASL_MOVABW_ONEW_FR_SVEC, 2, a1_ti, a0_ti);
   chk_callasl_arg_num(2);
   __st_insn(I_STOREA, AM_REG, AR_AX, AM_REG, res_ti);
   res_bpti = __get_bpti(res_ti);
   /* AIV 12/29/06 - the b part (resb) always goes into AR_CX */
   /* AIV LOOKATME BEWARE - machine dependent - but most of bbgen3 is as well */
   __st_insn(I_STOREA, AM_REG, AR_CX, AM_REG, res_bpti);
  }
 else
  {
   a2_ti = prep_push_word_arg(blen_ti);

   a1_ti = prep_push_tn_addr_arg(svec_pti);
   a0_ti = prep_push_tn_addr_arg(res_ti);
   emit_call_asl_proc(ASL_MOVABW_FR_SVEC, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
  }
 return(res_ti);
}

/* AIV 12/01/05 - is there a difference between this sgn/non-sgn ??? */
extern int32 __emit_movabw_fr_sgnsv(int32 svec_pti, int32 blen)
{
 int32 res_ti, blen_ti, a0_ti, a1_ti, a2_ti;

 res_ti = __gen_tn(SR_VEC, blen);
 
 blen_ti = __gen_cint_tn(blen);
 a2_ti = prep_push_word_arg(blen_ti);

 a1_ti = prep_push_tn_addr_arg(svec_pti);
 a0_ti = prep_push_tn_addr_arg(res_ti);
 emit_call_asl_proc(ASL_MOVABW_FR_SVEC, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 return(res_ti);
}

extern int32 __emit_movr_fr_w(int32 rhs_ti)
{
 int32 res_ti, width_ti, a0_ti, a1_ti;
 
 /* AIV 11/25/08 - these should be folded at compile time if constant */
 if (__is_constant(rhs_ti)) 
  {
   res_ti = cnvt_constant_real_fr_w(rhs_ti, FALSE);
   return(res_ti);
  }

 res_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[res_ti].t_real = TRUE;
 /* SJM 08/27/06 - mark real as wide since halves non separable */
 __tntab[res_ti].tn_used_wide = TRUE; 

 width_ti = __gen_cint_tn(__get_tnwid(rhs_ti));
 a1_ti = prep_push_word_arg(width_ti);
 a0_ti = prep_push_tn_addr_arg(rhs_ti);
 emit_call_asl_func(ASL_MOVR_FR_W, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
//AIV?? - notice you are assuming pass to set the result tni's
#ifdef __CVC32__
 nores_insn(I_FSTPL, AM_NONE, AM_REG, res_ti);
#else
 /* 64-bit gets result from xmm0 */
 nores_insn(I_STREAL, AM_NONE, AM_REG, res_ti);
#endif
 return(res_ti);
}

extern int32 __emit_movr_fr_sgnw(int32 rhs_ti)
{
 int32 res_ti, width_ti, a0_ti, a1_ti;

 /* AIV 11/25/08 - these should be folded at compile time if constant */
 if (__is_constant(rhs_ti)) 
  {
   res_ti = cnvt_constant_real_fr_w(rhs_ti, TRUE);
   return(res_ti);
  }

 res_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[res_ti].t_real = TRUE;
 /* SJM 08/27/06 - mark real as wide since halves non separable */
 __tntab[res_ti].tn_used_wide = TRUE; 

 width_ti = __gen_cint_tn(__get_tnwid(rhs_ti));
 a1_ti = prep_push_word_arg(width_ti);
 a0_ti = prep_push_tn_addr_arg(rhs_ti);
 emit_call_asl_func(ASL_MOVR_FR_SGNW, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
#ifdef __CVC32__
 nores_insn(I_FSTPL, AM_NONE, AM_REG, res_ti);
#else
 /* 64-bit gets result from xmm0 */
 nores_insn(I_STREAL, AM_NONE, AM_REG, res_ti);
#endif
 return(res_ti);
}

/*
 * convert a constant word into a real at compile time
 */
static int32 cnvt_constant_real_fr_w(int32 rhs_ti, int32 is_signed) 
{
 int32 tnwid, res_ti, xvi;
 word32 val[4];
 word32 *wp;
 double d1;

 xvi = __get_con_adradd_xvi(rhs_ti);
 wp = &(__contab[xvi]);

 tnwid = __get_tnwid(rhs_ti);
 if (is_signed) d1 = __asl_movr_fr_sgnw(wp, tnwid);
 else d1 = __asl_movr_fr_w(wp, tnwid);
 memcpy(val, &d1, sizeof(double));
#ifdef __CVC32__
 val[2] = 0;
 val[3] = 0;
 xvi = __allocfill_cval_new(val, &(val[2]), 2);
#else
 val[1] = 0;
 xvi = __allocfill_cval_new(val, &(val[1]), 1);
#endif
 res_ti = __gen_contab_tn(xvi, tnwid, FALSE, FALSE, TRUE, SR_VEC);
 return(res_ti);
}


extern void __emit_4state_vec_to_2state_wide(int32 new_ti, int32 rhs_ti, 
 int32 wlen)
{
 int32 a0_ti, a1_ti, a2_ti, cint_ti;
 
 cint_ti = __gen_cint_tn(wlen);
 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_tn_addr_arg(rhs_ti);
 a0_ti = prep_push_tn_addr_arg(new_ti);
 emit_call_asl_proc(ASL_4STATE_TO_2STATE_WIDE, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}


extern int32 __emit_movsb_fr_scalstad(int32 apti, int32 new_st)
{
 int32 res_ti, new_st_ti, a0_ti, a1_ti;

 res_ti = __gen_tn(SR_SSCAL, 1);

 new_st_ti = __gen_cint_tn(new_st);
 a1_ti = prep_push_word_arg(new_st_ti);
 a0_ti = prep_push_word_arg(apti);
 emit_call_asl_func(ASL_MOVSB_FR_SCALSTAD, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 __st_insn(I_STOREA, AM_REG, AR_AX, AM_REG, res_ti);
 return(res_ti);
}

extern int32 __emit_movsb_fr_wstad(int32 blen, int32 apti, int32 new_st)
{
 int32 res_ti, width_ti, new_st_ti, a0_ti, a1_ti, a2_ti, a3_ti;

 res_ti = __gen_tn(SR_SVEC, blen);

 new_st_ti = __gen_cint_tn(new_st);
 a3_ti = prep_push_word_arg(new_st_ti);

 /* AIV 12/22/06 - needs to pass the exact length */
 width_ti = __gen_cint_tn(blen);
 a2_ti = prep_push_word_arg(width_ti);

 a1_ti = prep_push_tn_addr_arg(apti);
 a0_ti = prep_push_tn_addr_arg(res_ti);
 emit_call_asl_proc(ASL_MOVSB_FR_WSTAD, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 return(res_ti);
}

extern int32 __emit_movsb_fr_widestad(int32 blen, int32 apti, int32 new_st)
{
 int32 res_ti, width_ti, new_st_ti, a0_ti, a1_ti, a2_ti, a3_ti;

 res_ti = __gen_tn(SR_SVEC, blen);

 new_st_ti = __gen_cint_tn(new_st);
 a3_ti = prep_push_word_arg(new_st_ti);

 width_ti = __gen_cint_tn(__get_tnwid(apti));
 a2_ti = prep_push_word_arg(width_ti);

 a1_ti = prep_push_tn_addr_arg(apti);
 a0_ti = prep_push_tn_addr_arg(res_ti);
 emit_call_asl_proc(ASL_MOVSB_FR_WIDESTAD, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 return(res_ti);
}

extern int32 __emit_reg_qcaf_inhibit(int32 np_ti)
{
 int32 qcaf_active_ti, a0_ti;

 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_REG_QCAF_INHIBIT, 1, a0_ti);
 chk_callasl_arg_num(1);
 qcaf_active_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(qcaf_active_ti);
} 

extern int32 __emit_scalar_wire_inhibit(int32 np_ti)
{
 int32 qcaf_active_ti, a0_ti;

 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_SCALAR_WIRE_INHIBIT, 1, a0_ti);
 chk_callasl_arg_num(1);
 qcaf_active_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(qcaf_active_ti);
}

extern int32 __emit_bsel_wirfrc_inhibit(int32 np_ti, int32 bi_ti)
{
 int32 qcaf_active_ti, a1_ti, a0_ti;

 /* SJM 07/12/06 - notice bi here is always tmp name maybe from gen cint tn */  
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_BSEL_WIRFRC_INHIBIT, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 qcaf_active_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(qcaf_active_ti);
}

extern int32 __emit_stren_correct_frc(int32 np_ti, int32 rhs_apti)
{
 int32 qcaf_active_ti, a1_ti, a0_ti;

 /* SJM 12/01/06 - push order was backward */   
 a1_ti = prep_push_word_arg(np_ti);
 a0_ti = prep_push_tn_addr_arg(rhs_apti);
 emit_call_asl_func(ASL_STREN_CORRECT_FRC, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 qcaf_active_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(qcaf_active_ti);
}

extern int32 __emit_xmr_rooted_base(struct net_t *np)
{
 int32 r_ti, mdat_offset_ti, mdat_ti;
 size_t offset;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 mdat_ti = __gen_mdat_storage_area(__inst_mod);
 offset = (__inst_ptr->itinum*__inst_mod->mod_idata_siz*WRDBYTES); 
 /* DBG remove -- */
 if (offset > (__inst_mod->flatinum*__inst_mod->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ------ */

 /* now add net offset in bytes from xmr idp */
 offset += (np->nva_ofs*WRDBYTES);
 mdat_offset_ti = __con_adradd_insn(SR_CINT, WBITS, mdat_ti, offset);
 __tntab[mdat_offset_ti].idp_typ = COMLAB_IDPDAT;
 r_ti = __move_srep_insn(TN_ADR, I_MOVA, np->srep, np->nwid, AM_REG, 
  mdat_offset_ti);
 return(r_ti);
}


extern int32 __emit_correct_frc(int32 np_ti, int32 rhs_apti)
{
 int32 qcaf_active_ti, a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(np_ti);
 a0_ti = prep_push_tn_addr_arg(rhs_apti);
 emit_call_asl_func(ASL_CORRECT_FRC, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 qcaf_active_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(qcaf_active_ti);
}

extern int32 __emit_psel_correct_frc(int32 np_ti, int32 rhs_apti, int32 ri1,
 int32 ri2)
{
 int32 qcaf_active_ti, ri1_ti, ri2_ti, a0_ti, a1_ti, a2_ti, a3_ti;

 ri2_ti = __gen_cint_tn(ri2);
 a3_ti = prep_push_word_arg(ri2_ti);
 ri1_ti = __gen_cint_tn(ri1);
 a2_ti = prep_push_word_arg(ri1_ti);

 a1_ti = prep_push_word_arg(np_ti);
 a0_ti = prep_push_tn_addr_arg(rhs_apti);
 emit_call_asl_func(ASL_PSEL_CORRECT_FRC, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 qcaf_active_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(qcaf_active_ti);
}

extern int32 __emit_stren_psel_correct_frc(int32 np_ti, int32 sbp_ti,
 int32 ri1, int32 ri2)
{
 int32 qcaf_active_ti, ri1_ti, ri2_ti, a0_ti, a1_ti, a2_ti, a3_ti;;

 ri2_ti = __gen_cint_tn(ri2);
 a3_ti = prep_push_word_arg(ri2_ti);
 ri1_ti = __gen_cint_tn(ri1);
 a2_ti = prep_push_word_arg(ri1_ti);

 a1_ti = prep_push_word_arg(np_ti);
 a0_ti = prep_push_tn_addr_arg(sbp_ti);
 emit_call_asl_func(ASL_STREN_PSEL_CORRECT_FRC, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 qcaf_active_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(qcaf_active_ti);
}

/*
 * note that bi1 is always a compile time number not a cint tmp name  
 * this does either a or b part - called twice for both
 */
/* op1[wi] &= ~(1L << op3); */
/* op1[wi] |= ((sw & 1L) << op3); */
extern void __emit_st_const_bsel(int32 lhs_ti, int32 rhs_ti, int32 bi1)
{
 int32 r1_ti, r2_ti, r3_ti, r4_ti, val_ti, am_type;
 int32 one_ti, bi1_ti;
 /* AIV 09/15/10 - these must be word32 - for 64-bit high - hacked off */
 word32 aval, lhs_bsel_val;

 /* DBG remove  -- */
 if (bi1 > WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 /* turn off the constant select into bit in the destination word */
 val_ti = __gen_cint_tn(~(1UL << bi1));
 r1_ti = emit_oneword_and(val_ti, lhs_ti, FALSE, -1, -1);

 /* SJM 07/21/06 - special case (for rhs concats) if rhs is constant */
 /* SJM 09/23/06 - better to simplify constant rhs for const bsel store here */
 if (__is_constant(rhs_ti)) 
  {
   /* get the constant value - know no bpart */
   aval = __get_wrd_con_val(rhs_ti);
   /* know the bit value to store into lhs apti at compile time */
   lhs_bsel_val = (aval & 1) << bi1;
   r3_ti = __gen_cint_tn(lhs_bsel_val);
  }
 else
  {
   /* isolate the low 1 bit rhs that is using to store in */
   one_ti = __gen_cint_tn(1);
   r2_ti = emit_oneword_and(one_ti, rhs_ti, FALSE, -1, -1);

   /* move the 1 bit to the right lhs bsel in word offset */
   bi1_ti = __gen_cint_tn(bi1);
   r3_ti = emit_oneword_shift(I_SHLL, bi1_ti, r2_ti);
  }

 /* or in the bit */
 r4_ti = oneword_binop(I_ORL, r1_ti, r3_ti);
 /* put back into the hgh wrd apti */
 am_type = get_1wrd_amtype(lhs_ti);
 __st_insn(I_STOREA, AM_REG, r4_ti, am_type, lhs_ti);
}

extern void __emit_ld_bsel(int32 rhs_apti, int32 bi_ti, int32 res_apti) 
{
 int32 am_type, r1_ti, r2_ti, one_ti, shft_amt_ti;
 word32 aval;

 /* op3 = (op1 >> op2) & 1 */
 /* DBG remove */
//AIV 07/28/06 - in 291f this was res but what about if op1 is wide and doing
//a bsel this cannot be right need to do an add to op1 
//look at gen_lhs_concat2 - but appears to have been working in 291f???
 if (__get_tnwid(res_apti) > WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */
 one_ti = __gen_cint_tn(1);
 if (__is_constant(bi_ti)) 
  {
   if (__tntab[bi_ti].comlab_typ == COMLAB_CONADR)
    {
     aval = __get_con_wrd_aval_nd0bval(bi_ti);
     shft_amt_ti = __gen_cint_tn(aval);
    }
   else shft_amt_ti = bi_ti;
  }
 else
  {
   am_type = get_1wrd_amtype(bi_ti);
   shft_amt_ti = __move_insn(TN_VAL, I_MOVA, am_type, bi_ti);
  }
 r1_ti = emit_oneword_shift(I_SHRL, shft_amt_ti, rhs_apti);
 r2_ti = emit_oneword_and(one_ti, r1_ti, FALSE, -1, -1);
 am_type = get_1wrd_amtype(r2_ti);
 __st_insn(I_STOREA, am_type, r2_ti, AM_REG, res_apti);
}

extern void __emit_ld_psel(int32 src_ti, int32 sbit1, int32 numbits,
 int32 val_ti)
{
 int32 numbits_ti, sbit1_ti, a0_ti, a1_ti, a2_ti, a3_ti;
 
 /* bbgen catches word32/aligned cases so know need to used unalignned */
 /* AIV FIXME - should probably lower this routine as well */

 numbits_ti = __gen_cint_tn(numbits);
 a3_ti = prep_push_word_arg(numbits_ti);

 sbit1_ti = __gen_cint_tn(sbit1);
 a2_ti = prep_push_word_arg(sbit1_ti);

 a1_ti = prep_push_tn_addr_arg(src_ti);
 a0_ti = prep_push_tn_addr_arg(val_ti);
 emit_call_asl_proc(ASL_CP_SOFS_WVAL, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}

extern void __emit_st_psel(int32 dst_ti, int32 val_ti, int32 lowbi_ti,
 int32 numbits_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti;

 /* if one word psel of entire word is just a move */
 /* AIV - note this should eventually be optimized away in v_bbopt */
 /* 4th arg numbits, 3rd src as wrd, 2nd in wrd bit ofset, 1th dwp adr */
 a3_ti = prep_push_word_arg(numbits_ti);
 a2_ti = prep_push_tn_addr_arg(val_ti);
 a1_ti = prep_push_word_arg(lowbi_ti);
 a0_ti = prep_push_tn_addr_arg(dst_ti);
 emit_call_asl_proc(ASL_LHSPSEL, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}

/*
 * mask of the and is usually but not always a number - caller
 * gens the tn cint if so 
 * known to be narrow case
 */
extern int32 __emit_mask_and(int32 wadr_ti, int32 mask_ti)
{
 int32 r_ti;

 r_ti = emit_oneword_and(wadr_ti, mask_ti, FALSE, -1, -1);
 return(r_ti);
}

/*
 * do a one word strength reduction andl instruction
 * - if both constant do and and return new constant value
 * - if either operand 0 return 0
 * - if one operand is all 1's return the other operand
 * if nds_srep must call the eval srep insn routine
 */
static int32 emit_oneword_and(int32 op1_ti, int32 op2_ti, int32 nds_srep,
 int32 srep, int32 blen)
{
 int32 r_ti, am_type, am_type2, can_track;

 if (__is_constant(op1_ti) || __is_constant(op2_ti)) 
  {
   /* SJM 11/19/06 - if nds srep F, do not have a bit len - use word width */
   if (!nds_srep) blen = WBITS;

   /* this tracks the bin op result only one operand is constant */
   /* and because this is constant folding - no need to save tracked */
   /* and can't pass two variable operands */ 

   /* AIV 01/08/07 - special mask andl can take a blen and srep value */
   /* if it is setting a new srep value need to can only track value */
   /* if blen and srep types are already the same for all operands */
   /* it could mask a one bit SR_VEC and return a SR_VEC but needs a SR_SCAL */
   can_track = FALSE;
   if (!nds_srep) can_track = TRUE;
   else
    {
     /* if need srep the blen and srtyp must be the same of all operands */
     if ((srep == __tntab[op1_ti].srtyp && srep == __tntab[op2_ti].srtyp) &&
        (blen == __tntab[op1_ti].tnwid && srep == __tntab[op2_ti].tnwid))
      {
       can_track = TRUE;
      }
    }
   r_ti = -1;
   if (can_track)
    {
     /* SJM 11/19/06 - new scheme got rid of too complex interpreter wrapper */
     r_ti = eval_con_oneword_binop(I_ANDL, blen, op1_ti, op2_ti);
    }

   if (r_ti != -1)
    {
     /* if need srep the types and blen must be the same otherwise move to */
     /* new tmp matching the needed type */
     if (nds_srep)
      {
       if (blen != __get_tnwid(r_ti) || srep != __get_tnwid(r_ti))
        {
         r_ti = __move_srep_insn(TN_VAL, I_MOVA, srep, blen, AM_REG, r_ti);
        }
      }
     return(r_ti);
    }
  }

 am_type = get_1wrd_amtype(op1_ti);
 am_type2 = get_1wrd_amtype(op2_ti);
 /* do bin op */
 if (nds_srep)
  {
   r_ti = eval_srep_insn(TN_VAL, I_ANDL, srep, blen, am_type, op1_ti,
    am_type2, op2_ti);
  }
 else
  {
   r_ti = eval_insn(TN_VAL, I_ANDL, am_type, op1_ti, am_type2, op2_ti);
  }
 return(r_ti);
}

/*
 * emit mask or - after zeroing to empty - use this to or in new value 
 * known to be narrow case
 */
extern int32 __emit_mask_or(int32 wadr_ti, int32 mask_ti)
{
 int32 r_ti;

 r_ti = oneword_binop(I_ORL, wadr_ti, mask_ti);
 return(r_ti);
}

/*
 * this is part of decomposed bbgen machine insn for negating a value
 * as part of decomposing the bit changing operations
 */
extern int32 __emit_bitnot(int32 blen, int32 op1_ti)
{
 int32 r1_ti; 

 if (blen <= WBITS) r1_ti = emit_oneword_unop(I_NOTL, op1_ti);
 else
  {
   if (__tmp_is_2state(op1_ti)) r1_ti = __gen_tn(SR_BIT2S, blen);
   else r1_ti = __gen_tn(SR_VEC, blen);
   wide_unop(ASL_WIDE_NOTL, r1_ti, op1_ti, wlen_(blen));
  }
 return(r1_ti);
}

/*
 * same as regular but this one needs to pass srep and size
 */
extern int32 __emit_srep_mask_and(int32 srep, int32 blen, int32 wadr_ti, 
 int32 mask_ti)
{
 int32 r_ti;

 /* DBG remove -- */
 if (blen > WBITS) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 r_ti = emit_oneword_and(wadr_ti, mask_ti, TRUE, srep, blen);
 return(r_ti);
}

extern void __emit_jmp_eq_stmask(struct bblk_t *t_bbp,
 struct bblk_t *f_bbp, int32 oval_apti, int32 nval2_ti)
{
 int32 width_ti, a0_ti, a1_ti, a2_ti;

 width_ti = __gen_cint_tn(__get_tnwid(oval_apti));
 a2_ti = prep_push_word_arg(width_ti);

 a1_ti = prep_push_tn_addr_arg(oval_apti);
 a0_ti = prep_push_tn_addr_arg(nval2_ti);
 emit_call_asl_func(ASL_JMP_EQ_STMASK, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 
 nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

extern int32 __emit_qcol_comb_opands(int32 x1_apti, int32 x2_apti,
 int32 opbits)
{
 int32 res_apti, wlen_ti, a0_ti, a1_ti, a2_ti, a3_ti;

// AIV? FIXME - WRITME - lower  <= 32
//  resbp[wi] = xsp2->bp[wi] | xsp1->bp[wi] | (xsp2->ap[wi] ^ xsp1->ap[wi]);
// resap[wi] = resbp[wi] | xsp1->ap[wi];
 res_apti = __gen_tn(SR_VEC, opbits);

 wlen_ti = __gen_cint_tn(wlen_(opbits));
 a3_ti = prep_push_word_arg(wlen_ti);

 a2_ti = prep_push_tn_addr_arg(x2_apti);
 a1_ti = prep_push_tn_addr_arg(x1_apti);
 a0_ti = prep_push_tn_addr_arg(res_apti);
 emit_call_asl_proc(ASL_WIDE_QCOL_COMB_OPANDS, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 return(res_apti);
}

extern int32 __emit_sub(int32 blen, int32 op1, int32 op2)
{
 int32 res_ti;

 if (blen <= WBITS) res_ti = lower_subl(op1, op2);
 /* AIV LOOKATME - wide_binop wrong for sub as well ??? */
 else res_ti = wide_binop(ASL_LSUB, op1, op2, blen, blen);
 return(res_ti);
}

extern int32 __emit_add(int32 blen, int32 op1, int32 op2)
{
 int32 res_ti;

 if (blen <= WBITS) res_ti = oneword_binop(I_ADDL, op1, op2);
 else res_ti = wide_binop(ASL_LADD, op1, op2, blen, blen);
 return(res_ti);
} 

extern int32 __emit_adc(int32 op1, int32 op2)
{
 int32 res_ti;

 res_ti = oneword_binop(I_ADCL, op1, op2);
 return(res_ti);
} 

/* AIV FIXME - using imull here should be mull for unsigned */
/* mull can use no memory location ????  */
extern int32 __emit_sgn_mult(int32 blen, int32 op1, int32 op2)
{
 int32 r1_ti;

 if (blen <= WBITS) 
  {
   /* AIV 12/29/08 - this can be same as emit_mult unsigned and it will */
   /* also handle the power of 2 case */
   r1_ti = __emit_mult(blen, op1, op2);
  }
 else r1_ti = wide_binop(ASL_SGN_LMULT, op1, op2, blen, blen);
 return(r1_ti);
}

extern int32 __emit_mult(int32 blen, int32 op1, int32 op2)
{
 int32 r1_ti, cint_ti;
 word32 aval, amt;

 if (blen <= WBITS)
  {
   /* AIV 01/10/07 - if either operands is a constant power of shift */
   /* just make it a shift - this is true a lot because of inum mults */
   /* are always a multiple of 2 */
   if (__is_constant(op1)) 
    {
     aval = __get_wrd_con_val(op1);
     amt = is_power_of2(aval);
     if (amt)
      {
       cint_ti = __gen_cint_tn(amt);
       r1_ti = oneword_binop(I_SHLL, cint_ti, op2);
       return(r1_ti); 
      }
#ifndef __CVC32__
     //AIV64 constants > 32 bits
     /* AIV 11/14/08 - if constant wide was using the loading large constants */
     /* so was loading into rcx and imulq expanded to use rcx just load */
     /* all constants here */
     op1 = insert_1wrd_ndxreg_mov(op1);
#endif
    }
   else if (__is_constant(op2)) 
    {
     aval = __get_wrd_con_val(op2);
     amt = is_power_of2(aval);
     if (amt)
      {
       cint_ti = __gen_cint_tn(amt);
       r1_ti = oneword_binop(I_SHLL, cint_ti, op1);
       return(r1_ti); 
      }
#ifndef __CVC32__
     //AIV64 constants > 32 bits
     /* AIV 11/14/08 - if constant wide was using the loading large constants */
     /* so was loading into rcx and imulq expanded to use rcx just load */
     /* all constants here */
     op2 = insert_1wrd_ndxreg_mov(op2);
#endif
    }
   r1_ti = oneword_binop(I_IMULL, op1, op2);
  }
 else r1_ti = wide_binop(ASL_LMULT, op1, op2, blen, blen);
 return(r1_ti);
}

/*
 * return n from 2^n if power of two else return false
 * n is greater than 0 so if opval is a power of 2 return n
 */
static int32 is_power_of2(word32 opval)
{
 word32 amt;

 /* check for a power of 2 - reduce to shift */
 if (opval > 0 && ((opval & (opval - 1)) == 0)) 
  {
   /* AIV LOOKATME - isn't there a better way to get n from 2^n */
   /* AIV 12/29/08 - this is suppose to be WBITS not 32 */
   for (amt = 0; amt < WBITS; amt++)
    {
     if (opval == (1UL << amt)) return(amt); 
    }
  }
 else return(FALSE);

 return(FALSE);
}

extern int32 __emit_div(int32 blen, int32 op1_ti, int32 op2_ti, int32 srtyp)
{
 int32 res_ti, true_ti, blen_ti, a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, cint_ti;
 word32 aval, amt;

 if (blen <= WBITS)
  {
   /* AIV 12/29/08 - if divide by power of two just do right shift */
   /* just oposite the multiply */
   if (__is_constant(op2_ti)) 
    {
     aval = __get_wrd_con_val(op2_ti);
     amt = is_power_of2(aval);
     if (amt)
      {
       cint_ti = __gen_cint_tn(amt);
       res_ti = oneword_binop(I_SHRL, cint_ti, op1_ti);
       return(res_ti); 
      }
    }
   res_ti = oneword_binop(I_DIVL, op1_ti, op2_ti);
  }
 else
  {
   res_ti = __gen_tn(srtyp, blen);

   true_ti = __gen_cint_tn(TRUE);
   a4_ti = prep_push_word_arg(true_ti);
   blen_ti = __gen_cint_tn(blen);
   a3_ti = prep_push_word_arg(blen_ti);

   a2_ti = prep_push_tn_addr_arg(op2_ti);
   a1_ti = prep_push_tn_addr_arg(op1_ti);
   a0_ti = prep_push_tn_addr_arg(res_ti);
//SJM? - WONT WORK BECAUSE OF res 
   emit_call_asl_proc(ASL_LDIVMOD, 5, a4_ti, a3_ti, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(5);
  }
 return(res_ti);
}

extern int32 __emit_mod(int32 blen, int32 op1_ti, int32 op2_ti, int32 srtyp)
{
 int32 res_ti, false_ti, blen_ti, a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 if (blen <= WBITS)
  {
   res_ti = oneword_binop(I_MODL, op1_ti, op2_ti);
  }
 else
  {
   res_ti = __gen_tn(srtyp, blen);

   false_ti = __gen_cint_tn(FALSE);
   a4_ti = prep_push_word_arg(false_ti);
   blen_ti = __gen_cint_tn(blen);
   a3_ti = prep_push_word_arg(blen_ti);

   a2_ti = prep_push_tn_addr_arg(op2_ti);
   a1_ti = prep_push_tn_addr_arg(op1_ti);
   a0_ti = prep_push_tn_addr_arg(res_ti);
   emit_call_asl_proc(ASL_LDIVMOD, 5, a4_ti, a3_ti, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(5);
  }
 return(res_ti);
}

extern int32 __emit_sgn_div(int32 blen, int32 op1_ti, int32 op2_ti, 
 int32 is_2state)
{
 int32 res_ti, true_ti, blen_ti, a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 /* AIV 12/29/08 AIV LOOKATME - could make this shifts some how gcc does */
 /* this using only shifts if divide by a multiple of 2 */
 if (blen <= WBITS)
  {
   res_ti = oneword_binop(I_SGN_DIVL, op1_ti, op2_ti);
  }
 else
  {
   if (is_2state) res_ti = __gen_tn(SR_BIT2S, blen);
   else res_ti = __gen_tn(SR_VEC, blen);

   true_ti = __gen_cint_tn(TRUE);
   a4_ti = prep_push_word_arg(true_ti);
   blen_ti = __gen_cint_tn(blen);
   a3_ti = prep_push_word_arg(blen_ti);

   a2_ti = prep_push_tn_addr_arg(op2_ti);
   a1_ti = prep_push_tn_addr_arg(op1_ti);
   a0_ti = prep_push_tn_addr_arg(res_ti);
   emit_call_asl_proc(ASL_SGN_LDIVMOD, 5, a4_ti, a3_ti, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(5);
  }
 return(res_ti);
}

extern int32 __emit_sgn_mod(int32 blen, int32 op1_ti, int32 op2_ti, 
 int32 is_2state)
{
 int32 res_ti, false_ti, blen_ti, a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 if (blen <= WBITS)
  {
   res_ti = oneword_binop(I_SGN_MODL, op1_ti, op2_ti);
  }
 else
  {
   if (is_2state) res_ti = __gen_tn(SR_BIT2S, blen);
   else res_ti = __gen_tn(SR_VEC, blen);

   false_ti = __gen_cint_tn(FALSE);
   a4_ti = prep_push_word_arg(false_ti);
   blen_ti = __gen_cint_tn(blen);
   a3_ti = prep_push_word_arg(blen_ti);

   a2_ti = prep_push_tn_addr_arg(op2_ti);
   a1_ti = prep_push_tn_addr_arg(op1_ti);
//SJM? - here is result pass addr paramenter 
//FIXME - DOES NOT WORK!!!!
   a0_ti = prep_push_tn_addr_arg(res_ti);
   emit_call_asl_proc(ASL_SGN_LDIVMOD, 5, a4_ti, a3_ti, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(5);
  }
 return(res_ti);
}

extern int32 __emit_wide_lpow(int32 op1, int32 op2, int32 blen)
{
 int32 r_ti;

 r_ti = wide_binop(ASL_WIDE_POWER, op1, op2, blen, blen);
 return(r_ti);
}

extern int32 __emit_wide_sgn_lpow(int32 op1, int32 op2, int32 blen, 
 int32 is_2state)
{
 int32 r_ti;

 if (is_2state)
  {
   r_ti = wide_binop(ASL_WIDE_SGN_POWER_2STATE, op1, op2, blen, blen);
  }
 else r_ti = wide_binop(ASL_WIDE_SGN_POWER, op1, op2, blen, blen);
 return(r_ti);
}


extern int32 __emit_add_real(int32 op1_ti, int32 op2_ti)
{
 return(emit_real_binop(I_FADDL, op1_ti, op2_ti));
}

extern int32 __emit_sub_real(int32 op1_ti, int32 op2_ti)
{
 return(emit_real_binop(I_FSUBL, op1_ti, op2_ti));
}

extern int32 __emit_mult_real(int32 op1_ti, int32 op2_ti)
{
 return(emit_real_binop(I_FMULL, op1_ti, op2_ti));
}

extern int32 __emit_div_real(int32 op1_ti, int32 op2_ti)
{
 return(emit_real_binop(I_FDIVL, op1_ti, op2_ti));
}

/*
 * emit divide by 0 warning
 */
extern void __emit_real_div0_warning(struct st_t *stp)
{
 int32 a0_ti, stmt_ti;


 /* DBG remove -- */
 if (stp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 stmt_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stmt_ti);
 emit_call_asl_func(ASL_REAL_DIV0_WARNING, 1, a0_ti);
 chk_callasl_arg_num(1);
}

/*
 * emit xz real qcol warning
 */
extern void __emit_real_qcol_warning(struct st_t *stp)
{
 int32 a0_ti, stmt_ti;


 /* DBG remove -- */
 if (stp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 stmt_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stmt_ti);
 emit_call_asl_func(ASL_REAL_QCOL_WARNING, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_power_real(int32 op1_ti, int32 op2_ti)
{
 int32 a1_ti, a0_ti, res_ti;

 res_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[res_ti].t_real = TRUE;
 __tntab[res_ti].tn_used_wide = TRUE; 

 a0_ti = prep_push_real_arg(op1_ti);
 a1_ti = prep_push_real_arg(op2_ti);
 emit_call_asl_proc(ASL_REAL_POW_FUNC, 2, a1_ti, a0_ti);
#ifdef __CVC32__
 nores_insn(I_FSTPL, AM_NONE, AM_REG, res_ti);
#else
 /* 64-bit gets result from xmm0 */
 nores_insn(I_STREAL, AM_NONE, AM_REG, res_ti);
#endif
 chk_callasl_arg_num(4);
 return(res_ti);
}


#ifdef __CVC32__
extern int32 __emit_realneg(int32 op1_ti)
{
 int32 am_type, real_ti;

 real_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[real_ti].t_real = TRUE;
 /* SJM 08/27/06 - mark real as wide since halves non separable */
 __tntab[real_ti].tn_used_wide = TRUE; 

 am_type = get_1wrd_amtype(op1_ti);
 nores_insn(I_FLDL, AM_NONE, am_type, op1_ti);
 nores_insn(I_FCHS, AM_NONE, AM_NONE);
 nores_insn(I_FSTPL, AM_NONE, AM_REG, real_ti);
 return(real_ti);
}

extern int32 __emit_real_abs(int32 op1_ti)
{
 int32 am_type, real_ti;

 real_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[real_ti].t_real = TRUE;
 /* SJM 08/27/06 - mark real as wide since halves non separable */
 __tntab[real_ti].tn_used_wide = TRUE; 

//AIV? - is fldl a load store insn with complex addressing modes?
 am_type = get_1wrd_amtype(op1_ti);
 nores_insn(I_FLDL, AM_NONE, am_type, op1_ti);
 nores_insn(I_FABS, AM_NONE, AM_NONE);
 nores_insn(I_FSTPL, AM_NONE, AM_REG, real_ti);
 return(real_ti);
}

#else
/*
 * REALNEG is a special value always put into the comm area
 *
 *  a = -b;
 * movsd	b(%rip), %xmm1
 * movsd	REALNEG, %xmm0
 * xorpd	%xmm1, %xmm0
 * movsd	%xmm0, -16(%rbp)
*/
extern int32 __emit_realneg(int32 op1_ti)
{
 int32 am_type, real_ti;


 real_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[real_ti].t_real = TRUE;
 __tntab[real_ti].tn_used_wide = TRUE; 
 /* movsd	b(%rip), %xmm1 */
 am_type = get_1wrd_amtype(op1_ti);
 nores_insn(I_LDR2, AM_NONE, am_type, op1_ti);
 /* movsd	REALNEG, %xmm0 */
 nores_insn(I_LDRNEG, AM_NONE, AM_NONE);
 /* xorpd	%xmm1, %xmm0 */
 nores_insn(I_XORNREAL, AM_NONE, AM_NONE);
 nores_insn(I_STREAL, AM_NONE, AM_REG, real_ti);
 return(real_ti);
}

/*
 * REALABS is a special value always put into the comm area
 *
 *  a = -b;
 * movsd	b(%rip), %xmm1
 * movsd	REALABS, %xmm0
 * andpd	%xmm1, %xmm0
 * movsd	%xmm0, -16(%rbp)
*/
extern int32 __emit_real_abs(int32 op1_ti)
{
 int32 am_type, real_ti;


 real_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[real_ti].t_real = TRUE;
 __tntab[real_ti].tn_used_wide = TRUE; 
 /* movsd	b(%rip), %xmm1 */
 am_type = get_1wrd_amtype(op1_ti);
 nores_insn(I_LDR1, AM_NONE, am_type, op1_ti);
 /* movsd	REALABS, %xmm0 */
 nores_insn(I_LDRABS, AM_NONE, AM_NONE);
 /* xorpd	%xmm1, %xmm0 */
 nores_insn(I_ANDAREAL, AM_NONE, AM_NONE);
 nores_insn(I_STREAL, AM_NONE, AM_REG, real_ti);
 return(real_ti);
}
#endif

extern int32 __emit_bin_bitand(int32 blen, int32 op1, int32 op2)
{
 int32 r_ti;

 if (blen <= WBITS)
  {
   r_ti = emit_oneword_and(op1, op2, FALSE, -1, -1);
  }
 else r_ti = wide_binop(ASL_WIDE_BITAND, op1, op2, blen, wlen_(blen));
 return(r_ti);
}

//AIV FIXME - do strength reduction/ constant folding for wide case
extern int32 __emit_bin_bitor(int32 blen, int32 op1_ti, int32 op2_ti)
{
 int32 r_ti;

 if (blen <= WBITS) r_ti = oneword_binop(I_ORL, op1_ti, op2_ti);
 else r_ti = wide_binop(ASL_WIDE_BITOR, op1_ti, op2_ti, blen, wlen_(blen));
 return(r_ti);
}

extern int32 __emit_bin_bitxor(int32 blen, int32 op1_ti, int32 op2_ti)
{
 int32 r1_ti;

 if (blen <= WBITS)
  {
   r1_ti = oneword_binop(I_XORL, op1_ti, op2_ti);
  }
 else r1_ti = wide_binop(ASL_WIDE_BITXOR, op1_ti, op2_ti, blen, wlen_(blen));
 return(r1_ti);
}

extern int32 __emit_wid_bin_redor(int32 blen, int32 op1_ti, int32 op2_ti)
{
 int32 r1_ti, asl_type;

 /* AIV 08/02/11 - if xprop need to use new x values table */
 asl_type = ASL_WID_BIN_BITOR;
#ifdef __XPROP__
 if (__xprop_and_or_xs) asl_type = ASL_WID_BIN_BITOR_X;
#endif
 r1_ti = wide_binop(asl_type, op1_ti, op2_ti, blen, blen);
 return(r1_ti);
}


extern int32 __emit_wid_bin_redxnor(int32 blen, int32 op1_ti, int32 op2_ti,
 int32 is_2state)
{
 int32 r1_ti;

 /* DBG remove -- */
 if (blen <= WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (is_2state)
  {
   r1_ti = wide_binop(ASL_WID_BIN_BITXNOR_2STATE, op1_ti, op2_ti, blen, blen);
  }
 else r1_ti = wide_binop(ASL_WID_BIN_BITXNOR, op1_ti, op2_ti, blen, blen);
 return(r1_ti);
}

/*
 * emit shift left
 *
 * SJM? - notice the ecx x86 assignment needs to be done at reg assign time
 * SJM 11/13/06 - now first src arg is shift amount following x86 op order
 */
extern int32 __emit_shiftl(int32 blen, int32 op1_ti, int32 op2_ti)
{
 int32 r_ti;

 if (blen <= WBITS)
  {
   r_ti = emit_oneword_shift(I_SHLL, op1_ti, op2_ti);
  }
 else r_ti = wide_shift_binop(ASL_WIDE_LSHIFT, op1_ti, op2_ti, blen);
 return(r_ti);
}

extern int32 __emit_shiftr(int32 blen, int32 op1_ti, int32 op2_ti)
{
 int32 r_ti;

 if (blen <= WBITS)
  {
   r_ti = emit_oneword_shift(I_SHRL, op1_ti, op2_ti);
  }
 else r_ti = wide_shift_binop(ASL_WIDE_RSHIFT, op1_ti, op2_ti, blen);
 return(r_ti);
}

/* AIV LOOKATME - these are the same for now ???? */
/*
 * op1 is shift amount op1 is amount, op2 is arithmetic right shifted op
 */
extern int32 __emit_sgn_arshift(int32 blen, int32 op1_ti, int32 op2_ti)
{
 int32 r_ti;

 if (blen <= WBITS)
  {
   r_ti = emit_oneword_shift(I_SHRL, op1_ti, op2_ti);
  }
 else r_ti = wide_shift_binop(ASL_WIDE_RSHIFT, op1_ti, op2_ti, blen);
 return(r_ti);
}

/*
 * wide shifts need a separate wrapper to copy op2 into the result
 * prior doing the shift
 * is much better to have the copy in the lowered code than a memcpy
 * in the wrapper routine
 */
static int32 wide_shift_binop(int32 asl_rout_num, int32 op1_ti, int32 op2_ti,
  int32 blen)
{
 int32 res_ti, len_ti, a0_ti, a1_ti, a2_ti, nbytes;
 
 /* AIV 08/26/10 - if 2-state return a two state */
 if (__tmp_is_2state(op1_ti)) res_ti = __gen_tn(SR_BIT2S, blen);
 else res_ti = __gen_tn(SR_VEC, blen);

 /* memcpy(res, op1, WRDBYTES * wlen_(blen)); */
 nbytes = WRDBYTES*wlen_(blen);
 __emit_copy(nbytes, op2_ti, res_ti);

 len_ti = __gen_cint_tn(blen);
 a2_ti = prep_push_word_arg(len_ti);
 /* get stack addresses or location with pointer address */
 a1_ti = prep_push_word_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(res_ti);

 /* call wide library file */
 emit_call_asl_proc(asl_rout_num, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 return(res_ti);
}

/*
 * do a one word shift operation
 * - if both constant do shift are return constant
 * - if shift amount 0 return op1
 * - if op1 is 0 return 0
 * - otherwise do the actual shift
 */
static int32 emit_oneword_shift(int32 opcod, int32 op1_ti, int32 op2_ti)
{
 int32 r_ti;

 /* DBG remove -- */
 if (opcod != I_SHLL && opcod != I_SHRL) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 /* do the shift */
 r_ti = oneword_binop(opcod, op1_ti, op2_ti);
 return(r_ti);
}

/*
 * same as unsigned except don't cast to words
 */
static int32 emit_oneword_sgn_shift(int32 opcod, int32 op1_ti, int32 op2_ti)
{
 int32 r_ti;

 /* DBG remove -- */
 if (opcod != I_SALL && opcod != I_SARL) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 /* do the shift */
 r_ti = oneword_binop(opcod, op1_ti, op2_ti);
 return(r_ti);
}

extern int32 __emit_swap_sign(int32 blen, int32 op1_ti)
{
 int32 r1_ti, am_type;

 /* DBG remove -- */
 if (blen > WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */
 am_type = get_1wrd_amtype(op1_ti);
 r1_ti = unary_insn(TN_VAL, I_NEGL, am_type, op1_ti);
 return(r1_ti);
}

/*
 * AIV 12/29/11 - this must have always been wrong now works correctly
 */
extern void __emit_sgnmask(int32 res_ti, int32 op1_ti, int32 blen)
{
 int32 r1_ti, r2_ti, r3_ti, r4_ti, r5_ti, am_type;
 int32 blen_ti, a0_ti, a1_ti, a2_ti;

 /* DBG remove -- */
 if (__is_constant(op1_ti)) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* rta |= (__masktab[op2a] << (ndp->szu.xclen - op2a)); */
 blen_ti = __gen_cint_tn(blen);
 if (blen <= WBITS)
  {
   am_type = get_1wrd_amtype(op1_ti);
   r1_ti = __move_insn(TN_VAL, I_MOVA, am_type, op1_ti);


   /* SJM 07/14/06 - was wrongly using am type for int blen ti */ 
   r2_ti = eval_insn(TN_VAL, I_SUBL, AM_REG, blen_ti, AM_REG, r1_ti);

   /* SJM 07/14/06 - was not using r1 ti following flow graph pattern */ 
   /* SJM 07/21/06 - for nlo objects that are accessed as glb array */
   /* need new special case amode */
   /* AIV 10/16/08 - now word aligned no reason to mult bytes any more */
   r3_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, r1_ti, NLO_MASKTAB);

   r4_ti = emit_oneword_shift(I_SHLL, r2_ti, r3_ti);
   /* SJM 07/19/06 - must or the shift result in */
   /* AIV 10/16/08 - this was always wrong should have been op1 */
   r5_ti = oneword_binop(I_ORL, res_ti, r4_ti);
   copy_insn(r5_ti, res_ti, WRDBYTES);
  }
 else
  {
   /* AIV FIXME - lower this */
   blen_ti = __gen_cint_tn(blen);
   a2_ti = prep_push_word_arg(blen_ti);

   a1_ti = prep_push_word_arg(op1_ti);
   a0_ti = prep_push_tn_addr_arg(res_ti);
   emit_call_asl_proc(ASL_SGNMASK, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
  }
}

extern int32 __emit_compute_emask(struct net_t *np, int32 oval_ti, 
 int32 nval_ti, int32 eval, int32 *set_ndx_ti) 
{
 int32 am_type, r1_ti, r2_ti, r3_ti, oval_hw_zero_ti;
 int32 two_ti, nlo_typ;
   
 if (np->n_2state && !np->n_stren)
  {
   if (eval == E_POSEDGE) 
    {
     r1_ti = __emit_bin_bitxor(WBITS, nval_ti, oval_ti);
     r2_ti = __emit_bin_bitand(WBITS, r1_ti, nval_ti);
    }
   else 
    {
     r1_ti = __emit_bin_bitxor(WBITS, nval_ti, oval_ti);
     r2_ti = __emit_bin_bitxor(WBITS, r1_ti, nval_ti);
    }
   return(r2_ti);
  }

//emask = __epair_tab[op2 | (op1 << 2)];
 two_ti = __gen_cint_tn(2);
 am_type = get_1wrd_amtype(oval_ti);
 /* AIV 03/15/07 - this needs to zero the high part of the byte oval */
 /* to do the shift operation as a word */
 /* AIV 08/19/08 - these were MOZBL - no longer need to be */
 /* these were probably only needed for pre-idp code - high known to be 0 */
 oval_hw_zero_ti = __move_insn(TN_VAL, I_MOVA, am_type, oval_ti);

 r1_ti = emit_oneword_sgn_shift(I_SALL, two_ti, oval_hw_zero_ti);
 am_type = get_1wrd_amtype(nval_ti);
 /* AIV 11/06/06 - better to zero and or as a long */
 r2_ti = eval_insn(TN_VAL, I_ORL, AM_REG, r1_ti, am_type, nval_ti);
 /* movzbl  __epair_tab(%eax), %eax */
 /* SJM 07/21/06 - for nlo objects that are accessed as glb array */
 /* need new special case amode */
 /* AIV 10/16/08 - separate tables for pos/neg to save doing mask */
 nlo_typ = -1;
 if (eval == E_NEGEDGE) nlo_typ = NLO_EPAIR_NEG_TAB;
 else if (eval == E_POSEDGE) nlo_typ = NLO_EPAIR_POS_TAB;
 else __case_terr(__FILE__, __LINE__);

#ifdef __XPROP__
 *set_ndx_ti = r2_ti;
#endif

 r3_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, r2_ti, nlo_typ);
 return(r3_ti);
}

/*
 * ROUTINES TO LOWER UNARY OPS
 */

/*
 * this is a special case because always wrapper even for narrow
 */
extern int32 __emit_uredxor(int32 op1_ti)
{
 int32 unop_ti, op1_wid_ti, a0_ti, a1_ti;

 if (__get_tnwid(op1_ti) <= WBITS)
  {
   a0_ti = prep_push_word_arg(op1_ti);
   emit_call_asl_func(ASL_WRD_REDXOR, 1, a0_ti);
   chk_callasl_arg_num(1);
   unop_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
  }
 else
  {
   op1_wid_ti = __gen_cint_tn(wlen_(__get_tnwid(op1_ti)));
   a1_ti = prep_push_word_arg(op1_wid_ti);
   a0_ti = prep_push_tn_addr_arg(op1_ti);
   emit_call_asl_func(ASL_WIDE_REDXOR, 2, a1_ti, a0_ti);
   chk_callasl_arg_num(2);
   unop_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
  }
 return(unop_ti);
}

/*
 * unary that produces one bit (T/F) but is decomposed to compare/move
 */
extern void __emit_lognot(int32 op1_ti, int32 res_ti)
{
 int32 am_type, zero_ti;
 
 /* DBG remove -- */
 if (__get_tnwid(op1_ti) > WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 am_type = get_1wrd_amtype(op1_ti);
 zero_ti = __gen_cint_tn(0);
 nores_insn(I_CMPL, AM_REG, zero_ti, am_type, op1_ti);
 /* set to 1 if equal */
 /* AIV 10/21/08 - sete can take any byte register - reg alloc now handles */
 nores_insn(I_SETE, AM_NONE, AM_REG, res_ti);
}

/*
 * this is for wide unary operands (non reducing) that return wide
 */
extern void __emit_wid_unbitnot(int32 blen, int32 res_ti, int32 op1_ti,
 int32 is_2state)
{
 if (is_2state) wide_unop(ASL_WID_UNBITNOT_2STATE, res_ti, op1_ti, blen);
 else wide_unop(ASL_WID_UNBITNOT, res_ti, op1_ti, blen);
}


extern int32 __emit_wid_un_redor(int32 op1_ti, int32 blen, int32 need_xprop)
{
 int32 blen_ti, a0_ti, a1_ti, r_ti, asl_type;

 /* AIV 08/03/11 - xprop needs to use a seperate wrapper */
 asl_type = ASL_WID_UN_REDOR;
#ifdef __XPROP__
 if (need_xprop) asl_type = ASL_WID_UN_REDOR_X;
#endif

 blen_ti = __gen_cint_tn(blen);
 a1_ti = prep_push_word_arg(blen_ti);

 a0_ti = prep_push_tn_addr_arg(op1_ti);
 emit_call_asl_func(asl_type, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 r_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, AR_AX);
 return(r_ti);
}

/*
 * lower one word unary op with constant folding and value tracking
 * this is really a c binary not (~) operator for now
 *
 * notice that for now only use is notl machine insn
 */
static int32 emit_oneword_unop(int32 iop, int32 op_ti)
{
 int32 am_type, r1_ti, cint_ti;
 word32 aval;

 if (__is_constant(op_ti))
  {
   aval = __get_wrd_con_val(op_ti);
   cint_ti = __gen_cint_tn(~aval);
   return(cint_ti);
  }

 am_type = get_1wrd_amtype(op_ti);
 r1_ti = unary_insn(TN_VAL, iop, am_type, op_ti);
 return(r1_ti);
}

/*
 * wide unop (both for one bit and wide - caller allocated res tn)
 */
static void wide_unop(int32 iop, int32 res_ti, int32 op1_ti, int32 blen)
{
 int32 blen_ti, a0_ti, a1_ti, a2_ti;

 /* AIV 05/05/06 - has passing the wrong arg for blen */
 blen_ti = __gen_cint_tn(blen);
 a2_ti = prep_push_word_arg(blen_ti);

 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(res_ti);
 emit_call_asl_proc(iop, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * ROUTINES TO EMIT PROCEDURAL M INSNS
 */

extern void __emit_func_subr(struct task_t *tskp)
{
 int32 ndx;
 char s1[RECLEN];

 ndx = tskp->t_idnum;
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* AIV 10/07/05 - need mod name to avoid name conflict */
 sprintf(s1, "FUNC.%s_%s", __inst_mod->msym->synam, tskp->tsksyp->synam);
 nores_insn(I_MULTFI_SUBR, AM_NONE, AM_LABEL, s1, ndx);
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

#ifdef __CVC32__
extern void __emit_call_func(struct task_t *tskp)
{
 char s1[RECLEN];

 sprintf(s1, "FUNC.%s_%s", __inst_mod->msym->synam, tskp->tsksyp->synam);
 nores_insn(I_CALL, AM_NONE, AM_LABEL, s1, tskp->t_idnum);
}
#else
extern void __emit_call_func(struct task_t *tskp)
{
 char s1[RECLEN];

 /* AIV 11/21/08 - 64-bit takes 8 off of rsp so need to adjust to keep */
 /* stack aligned on 16-bytes */
 nores_insn(I_SUBQ, AM_IMM, 8, AM_REG, RSP);
 sprintf(s1, "FUNC.%s_%s", __inst_mod->msym->synam, tskp->tsksyp->synam);
 nores_insn(I_CALL, AM_NONE, AM_LABEL, s1, tskp->t_idnum);
 nores_insn(I_ADDQ, AM_IMM, 8, AM_REG, RSP);
}
#endif

/*
 * emit the actual call to a DPI function
 */
extern void __emit_call_func_dpi(struct task_t *tskp)
{
 char s1[RECLEN];
 struct dpi_t *dpip;

 dpip = tskp->tf_dpip;
 /* could rename using cname = in the import stmt */
 if (dpip->cname == NULL) sprintf(s1, "%s", tskp->tsksyp->synam);
 else sprintf(s1, "%s", dpip->cname);

 /* need to set the idp reg from the global __idp since it may have changed */
 __st_insn(I_STOREA, AM_REG, IDP_REG, AM_NLO, NLO_IDP);
 nores_insn(I_CALL, AM_NONE, AM_LABEL, s1, 0);
 /* need to mark DPI enter names - no do not add special _ndx number to name */
 __cur_bbp->itail->is_dpi_enter = TRUE;
}

#ifdef __CVC32__
/*
 * emit one passed argument using 32-bit calling conventions
 * all arguments are passed on the stack
 */
extern int32 __emit_call_func_arg_dpi(struct net_t *np, int32 offset, 
 int32 val_ti, int32 pass_as_addr, int32 io_typ)
{
 int32 r_ti, new_offset, am_type;

 am_type = get_1wrd_amtype(val_ti);
 /* if output real pass in the actual net addr */
 if (np->n_isarr && np->ntyp == N_REAL)
  {
   if (!pass_as_addr)
    {
     r_ti = insert_1wrd_ndxreg_mov(val_ti);
    }
   else r_ti = leal_insn(am_type, val_ti);
   __st_insn(I_MOVL, AM_REG, r_ti, AM_NDXREG_DISP, AR_SP, offset);
   new_offset = offset+WRDBYTES;
  }
 else if (np->ntyp == N_REAL && !pass_as_addr)
  {
   nores_insn(I_FLDL, AM_NONE, am_type, val_ti);
   nores_insn(I_FSTPL, AM_NONE, AM_NDXREG_DISP, AR_SP, offset);
   /* reals are passed as 64-bit, 2-words */
   new_offset = offset+2*WRDBYTES;
  }
 /* if it is a long long int - need to pass as 64-bits */
 else if (np->ntyp == N_LONGCINT)
  {
   if (pass_as_addr) 
    {
     if (__tntab[val_ti].tn_typ == TN_ADR) 
      {
       r_ti = val_ti;
      }
     else r_ti = leal_insn(AM_REG, val_ti);
     __st_insn(I_MOVL, AM_REG, r_ti, AM_NDXREG_DISP, AR_SP, offset);
     new_offset = offset+WRDBYTES;
    }
   else 
    {
     /* need to pass 2 32-bit words */
     r_ti = insert_1wrd_ndxreg_mov(val_ti);
     __st_insn(I_MOVL, AM_REG, r_ti, AM_NDXREG_DISP, AR_SP, offset);
     offset = offset+WRDBYTES;

     val_ti = __con_adradd_insn(SR_CINT, WBITS, val_ti, WRDBYTES);
     r_ti = insert_1wrd_ndxreg_mov(val_ti);
     __st_insn(I_MOVL, AM_REG, r_ti, AM_NDXREG_DISP, AR_SP, offset);
     new_offset = offset+WRDBYTES;
   }
  }
 else
  {
   /* normal passing if address get leal overwise just move value */
   if (pass_as_addr) 
    {
     if (__tntab[val_ti].tn_typ == TN_ADR) 
      {
       r_ti = val_ti;
      }
     else r_ti = leal_insn(AM_REG, val_ti);
    }
   else r_ti = insert_1wrd_ndxreg_mov(val_ti);
   __st_insn(I_MOVL, AM_REG, r_ti, AM_NDXREG_DISP, AR_SP, offset);
   new_offset = offset+WRDBYTES;
  }
 return(new_offset);
}

/*
 * pass an argument to an export routine
 */
extern int32 __emit_get_export_arg_dpi(struct net_t *np, int32 *offset)
{
 int32 r_ti, srep;
 size_t new_offset;

 srep = np->srep;
 new_offset = *offset;
 r_ti = __move_srep_insn(TN_VAL, I_MOVA, np->srep, np->nwid, AM_NDXREG_DISP,
   AR_SP, new_offset);
 /* AIV 09/20/10 - need to mark these as they may need to be ajusted */
 /* after reg allocation */
 __cur_bbp->itail->is_export_stack = TRUE;
 if (srep == SR_SCAL || srep == SR_SSCAL || srep == SR_SCAL2S)
  {
   new_offset += WRDBYTES;
  }
 else 
  {
   new_offset += INTBYTES;
  }
 *offset = new_offset;
 return(r_ti);
}

/*
 * get a real returned value
 */
extern void __gen_ld_return_real_dpi(int32 st_into_ti)
{
 nores_insn(I_FSTPL, AM_NONE, AM_REG, st_into_ti);
}

#else
/*
 * emit one passed argument using 64-bit calling conventions
 * most args passed in registers following 64-bit ABI
 *
 * SJM 07-24-13 - 6 reg args are %rdi, %rsi, %rdx %rcx, %r8, %r9
 */
extern void __emit_call_func_arg_dpi(struct net_t *np,
 int32 val_ti, int32 pass_as_addr, int32 io_typ, int32 *inreg_argnop, 
 int32 *onstk_argnop, int32 *inreal_xmm_argnop) 
{
 int32 r_ti, am_type, passed_reg;
 int32 real_ld, inreg_argno, onstk_argno, inreal_xmm_argno;

 inreg_argno = *inreg_argnop;
 inreal_xmm_argno = *inreal_xmm_argnop;
 onstk_argno = *onstk_argnop;
 passed_reg = -1;

 am_type = get_1wrd_amtype(val_ti);
 /* if output real pass in the actual net addr */
 if (np->n_isarr && np->ntyp == N_REAL)
  {
   /* case 1: real array pointer - addr into one of 6 regs else on stack */
   r_ti = leal_insn(am_type, val_ti);

   if (inreg_argno >= 6)
    {
     /* this move is needed because if will force overflow reg to not */
     /* be used - overflow reg (%rcx) cannot be used because it is also */
     /* 64-bit ABI 4th argument passed - cannot override before call */ 
     r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, r_ti);
     __st_insn(I_MOVQ, AM_REG, r_ti, AM_NDXREG_DISP, AR_SP,
      onstk_argno*WRDBYTES);
     onstk_argno++;
    }
   else
    {
     passed_reg = __passed_regs_order[inreg_argno];
      __st_insn(I_MOVQ, AM_REG, r_ti, AM_REG, passed_reg);
     inreg_argno++;
    } 
  }
 else if (np->ntyp == N_REAL && !pass_as_addr)
  {
   /* case 2 real first xmm0 to xmm7 then onto stack */
   /* SJM 07-24-13 - only 8 of the 16 xmm regs used and guessing if more */
   /* than 8 real inputs, goes onto stack not into normal pass regs */
   if (inreal_xmm_argno >= 8)
    {
     val_ti = insert_1wrd_ndxreg_mov(val_ti);
     __st_insn(I_MOVQ, AM_REG, val_ti, AM_NDXREG_DISP, AR_SP,
      onstk_argno*WRDBYTES);
     onstk_argno++;
    }
   else
    {
     real_ld = get_real_ld(inreal_xmm_argno);
     nores_insn(real_ld, AM_NONE, am_type, val_ti);
     inreal_xmm_argno++;
    }
  }
 else 
  {
   if (pass_as_addr) 
    {
     /* case 3: inout so pass as must passs as addr even if real */
     if (__tntab[val_ti].tn_typ == TN_ADR) 
      {
       r_ti = val_ti;
      }
     else r_ti = leal_insn(AM_REG, val_ti);

     if (inreg_argno >= 6)
      {
       r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, r_ti);
       __st_insn(I_MOVQ, AM_REG, r_ti, AM_NDXREG_DISP, AR_SP,
        onstk_argno*WRDBYTES);
        onstk_argno++;
      }
     else
      {
       passed_reg = __passed_regs_order[inreg_argno];
       __st_insn(I_MOVQ, AM_REG, r_ti, AM_REG, passed_reg);
       inreg_argno++;
      }
    }
   else
    {
     /* case 4 normal non real arg that goes first in 6 regs then on stack */
     if (inreg_argno >= 6)
      {
       val_ti = insert_1wrd_ndxreg_mov(val_ti);
       __st_insn(I_MOVQ, AM_REG, val_ti, AM_NDXREG_DISP, AR_SP, 
        onstk_argno*WRDBYTES); 
       onstk_argno++; 
      }
     else
      { 
       passed_reg = __passed_regs_order[inreg_argno];
       __st_insn(I_MOVQ, am_type, val_ti, AM_REG, passed_reg);
       inreg_argno++;
      } 
    }
  }
 *inreg_argnop = inreg_argno;
 *inreal_xmm_argnop = inreal_xmm_argno;
 *onstk_argnop = onstk_argno;
}
   
/*
 * get real argument passed arg
 *
 * SJM 07-24-13 - notice I_LDR1 is really movsd [something], xmm0
 */
static int32 get_real_ld(int32 real_argno) 
{
 int32 real_ld;

 switch (real_argno) {
  case 0: real_ld = I_LDR1; break;
  case 1: real_ld = I_LDR2; break;
  case 2: real_ld = I_LDR3; break;
  case 3: real_ld = I_LDR4; break;
  case 4: real_ld = I_LDR5; break;
  case 5: real_ld = I_LDR6; break;
  case 6: real_ld = I_LDR7; break;
  case 7: real_ld = I_LDR8; break;
  case 8: real_ld = I_LDR9; break;
  case 9: real_ld = I_LDR10; break;
  case 10: real_ld = I_LDR11; break;
  case 11: real_ld = I_LDR12; break;
  case 12: real_ld = I_LDR13; break;
  case 13: real_ld = I_LDR14; break;
  case 14: real_ld = I_LDR15; break;
  case 15: real_ld = I_LDR16; break;
  default: __case_terr(__FILE__, __LINE__);
  }
 return(real_ld);
}

/*
 * call an export Verilog function argument
 */
extern int32 __emit_get_export_arg_dpi(struct net_t *np, int32 *argnop, 
 int32 *ofsp)
{
 int32 passed_reg, argno, r_ti;
 size_t offset;

 argno = *argnop;
 /* args > 6 are passed on the stack */
 if (argno >= 6) 
  {
   offset = *ofsp;
   r_ti = __move_srep_insn(TN_VAL, I_MOVA, np->srep, np->nwid, AM_NDXREG_DISP,
     AR_SP, offset);
   *ofsp = offset + WRDBYTES;
   /* AIV 09/20/10 - need to mark these as they may need to be ajusted */
   /* after reg allocation */
   __cur_bbp->itail->is_export_stack = TRUE;
  }
 else 
  {
   passed_reg = __passed_regs_order[argno];
   r_ti = __move_srep_insn(TN_VAL, I_MOVA, np->srep, np->nwid, AM_REG, 
     passed_reg);
   }
 argno++;
 *argnop = argno;
 return(r_ti);
}

/*
 * get a real returned value
 */
extern void __gen_ld_return_real_dpi(int32 st_into_ti)
{
 nores_insn(I_STREAL, AM_NONE, AM_REG, st_into_ti);
}
#endif

extern int32 __gen_ld_return_dpi(struct net_t *np)
{
 int32 r_ti;

 r_ti = __move_srep_insn(TN_VAL, I_MOVA, np->srep, np->nwid, AM_REG, AR_AX);
 return(r_ti);
}

extern int32 __gen_stack_adr(int32 val_ti)
{
 int32 adr_ti;
   
 adr_ti = leal_insn(AM_REG, val_ti);
 return(adr_ti);
}

extern void __emit_sysfcall(int32 fcallx_ti, int32 xstk_apti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(fcallx_ti);
 emit_call_asl_func(ASL_EXEC_SYSFUNC, 1, a0_ti);
 chk_callasl_arg_num(1);

 /* ret val is addr of top of stack ap - following insns copy and adjust */
 /* DBG remove -- */
 if (__tntab[xstk_apti].tn_typ != TN_ADR) __misc_terr(__FILE__, __LINE__);
 /* --- */
 __st_insn(I_STOREA, AM_REG, AR_AX, AM_REG, xstk_apti);
}

/*
 * same as regular stmt sys call but this sets stmt location at sim time
 */
extern void __emit_sysfcall_stmtloc(int32 fcallx_ti, int32 xstk_apti, 
 struct st_t *stp)
{
 int32 a0_ti, a1_ti, stmt_ti;

 /* DBG remove -- */
 if (stp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 stmt_ti = __gen_stmt_tn(stp);
 a1_ti = prep_push_word_arg(stmt_ti);
 a0_ti = prep_push_word_arg(fcallx_ti);
 emit_call_asl_func(ASL_EXEC_SYSFUNC_STMTLOC, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);

 /* ret val is addr of top of stack ap - following insns copy and adjust */
 /* DBG remove -- */
 if (__tntab[xstk_apti].tn_typ != TN_ADR) __misc_terr(__FILE__, __LINE__);
 /* --- */
 __st_insn(I_STOREA, AM_REG, AR_AX, AM_REG, xstk_apti);
}

extern void __emit_enter_task(struct task_t *tskp)
{
 int32 ndx;
 char s1[RECLEN], s2[RECLEN];

 /* notice this is a replace of thread running code so must not adjust */
 /* ebp and local variable area */
 ndx = tskp->t_idnum;
 sprintf(s2, "TSK.%s_%s_%d", __inst_mod->msym->synam, tskp->tsksyp->synam,
  ndx);
 sprintf(s1, ".globl %s", s2);
 nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);
 sprintf(s1, "TSK.%s_%s", __inst_mod->msym->synam, tskp->tsksyp->synam);
 nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

/*
 * call the actual DPI function
 */
extern void __emit_enter_task_dpi(struct task_t *tskp)
{
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];
 struct dpi_t *dpip;

 dpip = tskp->tf_dpip;
 /* could rename using cname = in the import stmt */
 if (dpip->cname == NULL) sprintf(s2, "%s", tskp->tsksyp->synam);
 else sprintf(s2, "%s", dpip->cname);

 sprintf(s1, ".globl %s", s2);
 nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);
 sprintf(s3, "%s:", s2);
 nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s3, 0); 
 /* need to mark DPI enter names - no do not add special _ndx number to name */
 __cur_bbp->itail->is_dpi_enter = TRUE;
 /* need to set __idp reg here - may use in DPI code */
 __st_insn(I_STOREA, AM_NLO, NLO_IDP, AM_REG, IDP_REG);
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_jmpto_tsk(struct task_t *tskp, struct sy_t *msym)
{
 char s1[RECLEN];

 nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
 sprintf(s1, "TSK.%s_%s", msym->synam, tskp->tsksyp->synam);
 nores_insn(I_TSKJMP, AM_NONE, AM_LABEL, s1, tskp->t_idnum);
}

#ifdef __CVC32__
extern void __emit_call_tsk(struct task_t *tskp, struct sy_t *msym)
{
 char s1[RECLEN];

 sprintf(s1, "TSK.%s_%s", msym->synam, tskp->tsksyp->synam);
 nores_insn(I_CALL, AM_NONE, AM_LABEL, s1, tskp->t_idnum);
}
#else
extern void __emit_call_tsk(struct task_t *tskp, struct sy_t *msym)
{
 char s1[RECLEN];

 /* AIV 11/21/08 - 64-bit takes 8 off of rsp so need to adjust to keep */
 /* stack aligned on 16-bytes */
 nores_insn(I_SUBQ, AM_IMM, 8, AM_REG, RSP);
 sprintf(s1, "TSK.%s_%s", msym->synam, tskp->tsksyp->synam);
 nores_insn(I_CALL, AM_NONE, AM_LABEL, s1, tskp->t_idnum);
 nores_insn(I_ADDQ, AM_IMM, 8, AM_REG, RSP);
}
#endif

extern void __emit_tskdone_cleanup(void)
{
 /* SJM 10/17/05 - no args so can run after leave machine insn */
 /* AIV 11/27/06 - this is a func uses eax for __thdjmp_ret_addr_tab jump */
 emit_call_asl_func(ASL_TSKDONE_CLEANUP_RET, 0);
 /* pass -1 because there is no index */
}

extern void __emit_tskdone_cleanup_auto(void)
{
 emit_call_asl_func(ASL_TSKDONE_CLEANUP_RET_AUTO, 0);
}


extern int32 __emit_thread_auto_cleanup(void)
{
 int32 restore_idp_ti;

 emit_call_asl_proc(ASL_THREAD_AUTO_CLEANUP, 0);
 restore_idp_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(restore_idp_ti);
}


extern void __emit_tsk_return(void)
{
 size_t tmp;
 /* AIV LOOKATME - maybe should add AM_ mode or change case jmp tab */
 /* AIV LOOKATME - this is an index jump in the sense that it is lowered */
 /* as a "jmp *" however it return from a task so it doesn't contain */
 /* a local block jump so made it it's own jump type */

//AIV? - this is special patterned ascii insn with scaling but not an adr mode
 /* SJM 12/01/07 - special pattern disp is the NLO type that must be exactly */ 
 /* nlo thdjmp ret addr tab NLO number */
 /* AIV 08/27/09 - this needs be size_t for 64 so just assign to tmp */
 tmp = NLO_THDJMP_RET_ADDR_TAB;
 nores_insn(I_TSKRET_JMP, AM_NONE, AM_NDXREG_DISP, AR_AX, tmp);
}

extern void __emit_func_brk_jmp(int32 ndx)
{
 char s1[RECLEN];

 /* this is a constant name so just get jmp label name */
 /* DBG remove -- */
 if (__thdjmp_ret_tab[ndx] == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* concat the index to the label name */
 sprintf(s1, "%s", __thdjmp_ret_tab[ndx]);
 /* set as regular non-cond jump */
 nores_insn(I_FUNC_JMP, AM_NONE, AM_LABEL, s1, ndx);
} 

extern void __emit_stskcall(int32 stp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(stp_ti);
 /* SJM 10/10/06 - directly calltsk call routine - not thru exec tsk call */
 emit_call_asl_proc(ASL_EXEC_STSK, 1, a0_ti);
 /* adjust the stack after return */
 chk_callasl_arg_num(1);
}

extern void __emit_exec_display(int32 stp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_EXEC_DISPLAY, 1, a0_ti);
 chk_callasl_arg_num(1);
}

/*
 * jmp *C_<num>(,%eax, 4)
 *
 * notice bbtab is really global ndx jmp bbtab so do not need to free
 */
extern void __emit_ndx_jmp(int32 ndx_ti, struct bblk_t **bbtab, size_t jtabsiz)
{
 int32 r1_ti;
 struct ndxjmp_t *ndxjp;

 __jmplab_nxti++;
 /* AIV 08/10/06 - needs a move regardless of the type in case of overflow */
 if (__tntab[ndx_ti].tn_typ == TN_ADR) 
  {
   r1_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, ndx_ti);
  }
 else r1_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, ndx_ti);
 nores_insn(I_IND_JMP, AM_NONE, AM_NDXREG_DISP, r1_ti, __jmplab_nxti);
 ndxjp = alloc_ndxjmp(bbtab, jtabsiz);
 __cur_bbp->itail->extrau.ndxjp = ndxjp;
}

/*
 * allocate an index jump to hold the block array and its size
 *
 * SJM 01/23/07 - passed bbtab is global ndx jmp bbtab that gets reused
 * so do not need to free it
 */
static struct ndxjmp_t *alloc_ndxjmp(struct bblk_t **bbtab, int32 jtabsiz)
{
 int32 tabi;
 size_t jtab2siz, osize, nsize;
 struct bbedge_t *bbep;
 struct bblk_t *bbp;
 struct bblk_t **new_bbtab;
 struct ndxjmp_t *ndxjp;

 jtab2siz = __count_ndxjmp_lab_setsiz(bbtab, jtabsiz);

 /* AIV 10/21/05 - can't use realloc here because if mashes the passed table */
 /* notice this is tab that goes in insn, freed when ndx jmp insn freed */
 nsize = (jtabsiz + jtab2siz)*sizeof(struct bblk_t *);
 new_bbtab = (struct bblk_t **) __my_malloc(nsize);

 osize = jtabsiz*sizeof(struct bblk_t *);
 memcpy(new_bbtab, bbtab, osize);

 /* build the set of unique labels jumped to by the ndx jump insn */
 /* know room after the jump table area */
 __bld_ndxjmp_lab_set(new_bbtab, jtabsiz); 

 /* for every index table jumped to back block - add back edge */
 /* the jump type indicates it - multiple back edges are normal */
 /* notice the current bblk violates the only 2 successor rule but */

 /* finally add the back edges only for the unduplicated set form */
 for (tabi = jtabsiz; tabi < (jtabsiz + jtab2siz); tabi++)
  {
   bbp = new_bbtab[tabi];
   /* AIV 01/30/12 - need to mark the blocks as case jump enter locations */
   bbp->is_casejmp_item = TRUE;

   bbep = __alloc_bbedge();
   bbep->bbenxt = bbp->bbe_prev;
   bbp->bbe_prev = bbep;

   bbep->eblkp = __cur_bbp;
 }

 ndxjp = (struct ndxjmp_t *) __my_malloc(sizeof(struct ndxjmp_t));
 ndxjp->bbtab = new_bbtab;
 ndxjp->jtabstart = jtabsiz;
 ndxjp->jtabsiz = jtab2siz;
 ndxjp->has_duplicates = TRUE;
 return(ndxjp);
}

/*
 * count the size of the ndxjmp insn unique bblk use set
 */
extern int32 __count_ndxjmp_lab_setsiz(struct bblk_t **bbtab, int32 jtabsiz)
{
 int32 tabi, jtab2siz;
 struct bblk_t *bbp;

 /* AIV 01/27/12 - rewrote this to use 2-pass marking scheme - previous */
 /* code was bad n^2 nested for */
 jtab2siz = 0;
 for (tabi = 0; tabi < jtabsiz; tabi++)
  {
   bbp = bbtab[tabi];
   if (bbp->in_list) continue;

   bbp->in_list = TRUE;
   jtab2siz++;
  }

 for (tabi = 0; tabi < jtabsiz; tabi++)
  {
   bbp = bbtab[tabi];
   bbp->in_list = FALSE;
  }
 return(jtab2siz);
}

/*
 * build the set of non repeated labels 
 */
extern void __bld_ndxjmp_lab_set(struct bblk_t **bbtab, int32 jtabsiz)
{
 int32 tabi, set_tabi;
 struct bblk_t *bbp;

 /* AIV 01/27/12 - rewrote this to use 2-pass marking scheme - previous */
 /* code was bad n^2 nested for */
 for (tabi = 0, set_tabi = jtabsiz; tabi < jtabsiz; tabi++)
  {
   bbp = bbtab[tabi];
   if (bbp->in_list) continue;

   bbp->in_list = TRUE;
   bbtab[set_tabi++] = bbp;
  }

 for (tabi = 0; tabi < set_tabi; tabi++)
  {
   bbp = bbtab[tabi];
   bbp->in_list = FALSE;
  }
}

extern void __emit_repcnt_jmp(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 rep_ti, int32 cnt_ti, int32 sign_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(sign_ti);
 a0_ti = prep_push_tn_addr_arg(rep_ti);
 emit_call_asl_func(ASL_REPCNT_JMP, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 /* SJM 04/26/06 rhs dest of insns must be ndx reg since will be net.bp */
 __st_insn(I_STOREA, AM_REG, AR_AX, AM_NDXREG, cnt_ti);
 nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

extern void __emit_qcol_jmp_any1(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 sel_apti, int32 sel_bpti, int32 blen)
{
 int32 r1_ti, r2_ti, r3_ti, wlen_ti, am_type, a0_ti, a1_ti, a2_ti;
 struct bblk_t *tmp_bbp;

 if (blen <= WBITS)
  {
   /* ((opap[wi] & ~opbp[wi]) != 0)  */
   am_type = get_1wrd_amtype(sel_bpti);
   r1_ti = unary_insn(TN_VAL, I_NOTL, am_type, sel_bpti);
   r2_ti = emit_oneword_and(r1_ti, sel_apti, FALSE, -1, -1);
   /* AIV 08/17/06 - LOOKATME - don't really need this move need */
   /* for now in case it is a constant but this will be folded once const */
   /* folding is done */
   r3_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, r2_ti);

   /* swap T/F since != 0 in header */
   tmp_bbp = f_bbp;
   f_bbp = t_bbp;
   t_bbp = tmp_bbp;
   /* testl just | itself to set jump flags */
   nores_insn(I_TESTL, AM_REG, r3_ti, AM_REG, r3_ti);
  }
 else
  {
   wlen_ti = __gen_cint_tn(wlen_(blen) - 1);
   a2_ti = prep_push_word_arg(wlen_ti);
   a1_ti = prep_push_tn_addr_arg(sel_bpti);
   a0_ti = prep_push_tn_addr_arg(sel_apti);
   emit_call_asl_func(ASL_WIDE_ANY1, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
   /* here do not reverse the t and f bblks */
   /* testl just | itself to set jump flags */
   nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
  }
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

extern void __emit_jmp_0(struct bblk_t *t_bbp, struct bblk_t *f_bbp, 
 int32 op_ti)
{
 int32 r1_ti, width_ti, a0_ti, a1_ti;

 /* AIV 02/03/09 - if two state is one and one block it x/z just jump */
 /* to the other block */
 /* AIV 2STATE REMOVEME - 
 if (__opt_two_state)
  {
   if (f_bbp->is_xz) { __emit_jmp(t_bbp); return; }
   else if (t_bbp->is_xz) { __emit_jmp(f_bbp); return; }
  }
 */

 if (__get_tnwid(op_ti) <= WBITS)
  {
   r1_ti = insert_1wrd_ndxreg_mov(op_ti);
   /* testl just | itself to set jump flags */
   nores_insn(I_TESTL, AM_REG, r1_ti, AM_REG, r1_ti);
   cond_jmp_insn(CC_JE, t_bbp, f_bbp);
  }
 else
  {
   width_ti = __gen_cint_tn(__get_tnwid(op_ti));
   a1_ti = prep_push_word_arg(width_ti);
   a0_ti = prep_push_tn_addr_arg(op_ti);
   emit_call_asl_func(ASL_WIDE_VVAL_IS0, 2, a1_ti, a0_ti);
   chk_callasl_arg_num(2);
   /* testl just | itself to set jump flags */
   nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
   /* swap and check if FALSE with testl */
   cond_jmp_insn(CC_JE, f_bbp, t_bbp);
  }
}

extern void __emit_jmpor_0(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti) 
{
 int32 r_ti, width_ti, a0_ti, a1_ti, a2_ti;
 word32 aval1, aval2, rval;

 /* AIV 02/03/09 - if two state is one and one block it x/z just jump */
 /* to the other block */
 /* AIV 2STATE REMOVEME - 
 if (__opt_two_state)
  {
   if (f_bbp->is_xz) { __emit_jmp(t_bbp); return; }
   else if (t_bbp->is_xz) { __emit_jmp(f_bbp); return; }
  }
 */

 if (__get_tnwid(op1_ti) <= WBITS)
  {
   /* AIV 07/17/06 - if either constant value is zero just use testl */
   /* on the other operand */
   if (__is_constant(op1_ti))
    { 
     aval1 = __get_wrd_con_val(op1_ti);
     /* AIV 11/23/09 - if not 0 is false so just jmp to false block */
     if (aval1 == 0)
      {
       r_ti = insert_1wrd_ndxreg_mov(op2_ti);
       goto test;
      }
     else { __emit_jmp(f_bbp); return; }
    }

   if (__is_constant(op2_ti))
    { 
     aval2 = __get_wrd_con_val(op2_ti);
     if (aval2 == 0)
      {
       r_ti = insert_1wrd_ndxreg_mov(op1_ti);
       goto test;
      }
     else { __emit_jmp(f_bbp); return; }
    }

   /* AIV 11/29/06 - due to value folding could be constant if constant */
   /* just make an unconditional jump */
   r_ti = oneword_binop(I_ORL, op1_ti, op2_ti);
   if (__is_constant(r_ti))
    {
     rval = __get_wrd_con_val(r_ti);
     if (rval == 0) __emit_jmp(t_bbp);
     else __emit_jmp(f_bbp);
     return;
    }
test:
   nores_insn(I_TESTL, AM_REG, r_ti, AM_REG, r_ti);
  }
 else
  {
   width_ti = __gen_cint_tn(wlen_(__get_tnwid(op1_ti)) - 1);
   a2_ti = prep_push_word_arg(width_ti);
   /* AIV LOOKATME - always pointer ??? */
   a1_ti = prep_push_tn_addr_arg(op1_ti);
   a0_ti = prep_push_tn_addr_arg(op2_ti);
   emit_call_asl_func(ASL_WIDE_JMPOR_0, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
   nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
  }
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

//  case I_JMP_EQ:
extern void __emit_jmp_eq(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti)
{
 int32 width_ti, am_type, am_type2, a0_ti, a1_ti, a2_ti, r_ti; 
 int32 wlen1, wlen2;
 word32 aval;

 /* AIV 02/03/09 - if two state is one and one block it x/z just jump */
 /* to the other block */
 /* AIV 2STATE REMOVEME - 
 if (__opt_two_state)
  {
   if (f_bbp->is_xz) { __emit_jmp(t_bbp); return; }
   else if (t_bbp->is_xz) { __emit_jmp(f_bbp); return; }
  }
 */

 /* AIV 10/15/10 - added this check 2-state was calling incorrectly */
 /* DBG remove -- */
 wlen1 = wlen_(__tntab[op1_ti].tnwid);
 wlen2 = wlen_(__tntab[op2_ti].tnwid);
 if (wlen1 != wlen2) __misc_terr(__FILE__, __LINE__);
 /* ---- */


 /* AIV 12/22/06 - due to compile time constant tracking op1 and op2 */
 /* can be equal - if they are just make a jump to the true block */
 if (op1_ti == op2_ti)
  {
   __emit_jmp(t_bbp);
   return;
  }

 if (__get_tnwid(op1_ti) <= WBITS)
  {
   /* AIV 12/29/08 - if one of the operands is constant and its value is 0 */
   /* should just be doing a jmp_0 with the other operand */ 
   /* the code produced is better by using a testl */
   if (__is_constant(op1_ti))
    {
     aval = __get_wrd_con_val(op1_ti);
     if (aval == 0)
      {
       __emit_jmp_0(t_bbp, f_bbp, op2_ti);
       return;
      }
    }
   else if (__is_constant(op2_ti))
    {
     aval = __get_wrd_con_val(op2_ti);
     if (aval == 0)
      {
       __emit_jmp_0(t_bbp, f_bbp, op1_ti);
       return;
      }
    }

   am_type = get_1wrd_amtype(op1_ti);
   am_type2 = get_1wrd_amtype(op2_ti);
   /* SJM 09/23/06 - know will be cint for word - otherwise b part non 0 */
   if (__is_constant(op2_ti))
    {
     /* DBG remove -- */
     if (__is_constant(op1_ti)) __misc_terr(__FILE__, __LINE__);
     /* --- */
     nores_insn(I_CMPL, am_type2, op2_ti, am_type, op1_ti);
    }
   else
    {
     /* AIV 12/29/06 - making mem2mem illegal so need a move */
     if (!__is_constant(op1_ti) && 
         am_type == AM_NDXREG && am_type2 == AM_NDXREG)
      {
       r_ti = insert_1wrd_ndxreg_mov(op1_ti);
       nores_insn(I_CMPL, AM_REG, r_ti, am_type2, op2_ti);
      }
     else nores_insn(I_CMPL, am_type, op1_ti, am_type2, op2_ti);
    }
  }
 else
  {
   width_ti = __gen_cint_tn(wlen_(__get_tnwid(op1_ti)) - 1);
   a2_ti = prep_push_word_arg(width_ti);
   a1_ti = prep_push_tn_addr_arg(op1_ti);
   a0_ti = prep_push_tn_addr_arg(op2_ti);
   emit_call_asl_func(ASL_WIDE_JMP_EQ, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
   nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
  }
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

/*
 * compare the a and b parts of a wide variable
 * should only be used wide because a and b narrow shouldn't be contiguous
 */
extern void __emit_jmp_eq_abpart(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti)
{
 int32 width_ti, a0_ti, a1_ti, a2_ti, blen;

 /* AIV 02/03/09 - if two state is one and one block it x/z just jump */
 /* to the other block */
 /* AIV 2STATE REMOVEME - 
 if (__opt_two_state)
  {
   if (f_bbp->is_xz) { __emit_jmp(t_bbp); return; }
   else if (t_bbp->is_xz) { __emit_jmp(f_bbp); return; }
  }
 */

 /* AIV 12/22/06 - due to compile time constant tracking op1 and op2 */
 /* can be equal - if they are just make a jump to the true block */
 if (op1_ti == op2_ti)
  {
   __emit_jmp(t_bbp);
   return;
  }
 if (__get_tnwid(op1_ti) <= WBITS) __misc_terr(__FILE__, __LINE__);
 /* AIV 06/15/07 - was passing the wrong number of bits */
 blen = 2*wlen_(__get_tnwid(op1_ti))*WBITS;
 width_ti = __gen_cint_tn(wlen_(blen) - 1);
 a2_ti = prep_push_word_arg(width_ti);
 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(op2_ti);
 emit_call_asl_func(ASL_WIDE_JMP_EQ, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

/*
 * same as above expcept do not jump return TRUE or FALSE
 */
extern int32 __emit_cmp_wide(int32 op1_ti, int32 op2_ti, int32 wlen, 
 int32 is_ne, int32 srtyp)
{
 int32 width_ti, a0_ti, a1_ti, a2_ti, cint_ti, r1_ti;

 /* AIV 12/22/06 - due to compile time constant tracking op1 and op2 */
 /* can be equal - if they are just make a jump to the true block */
 if (op1_ti == op2_ti)
  {
   if (is_ne) cint_ti = __gen_cint_tn(FALSE);
   else cint_ti = __gen_cint_tn(TRUE);
   /* AIV 10/21/08 - AIV FIXME */
   /* currently need to load constant into tmp - should fold these */
   /* would be fine if constant folding worked */
   r1_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1, AM_REG, cint_ti);
   return(r1_ti);
  }
 /* DBG remove -- */
 if (__get_tnwid(op1_ti) <= WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */

 width_ti = __gen_cint_tn(wlen - 1);
 a2_ti = prep_push_word_arg(width_ti);
 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(op2_ti);
 /* notice these are swapped because using the same wrapper for jmp code */
 if (is_ne)
  {
   emit_call_asl_func(ASL_WIDE_CMP_NEQ, 3, a2_ti, a1_ti, a0_ti);
  }
 else emit_call_asl_func(ASL_WIDE_CMP_EQ, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 r1_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1, AM_REG, AR_AX);
 return(r1_ti);
}

/*
 * AIV 09/11/09 - need a variable width that may trim at runtime
 * for the variable index width psels
 */
extern void __emit_jmp_eq_ab_wide_varmask(struct bblk_t *t_bbp, 
 struct bblk_t *f_bbp, int32 op1_ti, int32 op2_ti, int32 width_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 if (__get_tnwid(op1_ti) <= WBITS) __misc_terr(__FILE__, __LINE__);
 a2_ti = prep_push_word_arg(width_ti);
 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(op2_ti);
 emit_call_asl_func(ASL_JMP_EQ_WIDE_VARMASK, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

extern void __emit_jmp_byte_eq(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti)
{
 int32 width_ti, am_type, r1_ti, a0_ti, a1_ti, a2_ti;

 if (__get_tnwid(op1_ti) <= WBITS)
  {
   if (__is_constant(op2_ti))
    {
     invert_jmp_operands(I_CMPB, t_bbp, f_bbp, op2_ti, op1_ti, CC_JE, FALSE);
     return;
    }
   r1_ti = insert_1wrd_ndxreg_mov(op1_ti);
   am_type = get_1wrd_amtype(op2_ti);
   nores_insn(I_CMPB, AM_REG, r1_ti, am_type, op2_ti);
  }
 else
  {
   width_ti = __gen_cint_tn(wlen_(__get_tnwid(op1_ti)) - 1);
   a2_ti = prep_push_word_arg(width_ti);
   a1_ti = prep_push_tn_addr_arg(op1_ti);
   a0_ti = prep_push_tn_addr_arg(op2_ti);
   emit_call_asl_func(ASL_WIDE_JMP_EQ, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
   nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
  }
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

/*
 * do a regular compare (cmpl) - probably used with sete insns
 */
extern void __emit_cmp(int32 op1_ti, int32 op2_ti)
{
 int32 am_type, am_type2, r1_ti;

 /* DBG remove -- */
 if (__get_tnwid(op1_ti) > WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */

 am_type = get_1wrd_amtype(op1_ti);
 am_type2 = get_1wrd_amtype(op2_ti);

 if (__is_constant(op2_ti))
  {
   /* DBG remove -- */
   if (__is_constant(op1_ti)) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   nores_insn(I_CMPL, am_type2, op2_ti, am_type, op1_ti);
  }
 else
  {
   r1_ti = insert_1wrd_ndxreg_mov(op1_ti);
   am_type = get_1wrd_amtype(op2_ti);
   nores_insn(I_CMPL, AM_REG, r1_ti, am_type, op2_ti);
  }
}

/*
 * do an testl to set condition flags
 */
extern void __emit_testl(int32 op1_ti)
{
 /* if address load the value */
 if (__tntab[op1_ti].tn_typ == TN_ADR) 
  {
   op1_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, op1_ti);
  }

 nores_insn(I_TESTL, AM_REG, op1_ti, AM_REG, op1_ti);
}

/* 
 * set the byte from condition code
 * AIV 01/22/09 - this now passes the byte to set known to have high 3 bytes
 * of reg zeroed
 */
extern void __emit_st_sete(int32 jmptyp, int32 st_into)
{
 int32 scc;

 scc = get_set_insn_from_cc(jmptyp, FALSE);
 nores_insn(scc, AM_NONE, AM_REG, st_into);
}

/*
 * compare op1_ti (a known mdat address) to the current __idp (%esi)
 * cmpl $mdat + ofs, %esi
 */
extern void __emit_jmp_idp_eq(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti)
{
 /* DBG remove -- */
 if (__tntab[op1_ti].comlab_typ != COMLAB_IDPDAT)
  __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_CMPL, AM_REG, op1_ti, AM_REG, IDP_REG);
 cond_jmp_insn(CC_JNE, f_bbp, t_bbp);
}

extern void __emit_jmp_ptr_eq(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti)
{
 /* DBG remove -- */
 //AIV PUTMEBACK if (__tntab[op1_ti].tn_typ != TN_ADR) __misc_terr(__FILE__, __LINE__);
 if (__tntab[op2_ti].tn_typ != TN_ADR) __misc_terr(__FILE__, __LINE__);
 /* --- */

 nores_insn(I_CMPL, AM_REG, op1_ti, AM_REG, op2_ti);
 cond_jmp_insn(CC_JNE, f_bbp, t_bbp);
}


#ifdef __CVC32__
   /* AIV LOOKATME - better code ???? */
   /*
	fldl    t1
	fldz
	fxch	%st(1)
	fucompp
	fnstsw	%ax
	sahf
	jp      fblock	
	je      tblock	
        fall through is false 
        jmp     fblock
    */
extern void __emit_jmp_real0(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op_ti)
{
 int32 am_type;

//SJM? - is fldl an operation?
 am_type = get_1wrd_amtype(op_ti);
 nores_insn(I_FLDL, AM_NONE, am_type, op_ti);
 nores_insn(I_FLDZ, AM_NONE, AM_NONE);
 nores_insn(I_FXCH, AM_NONE, AM_REG, ST1);
 nores_insn(I_FUCOMPP, AM_NONE, AM_NONE);
 /* takes eax into indicate it changes eax */
 nores_insn(I_FNSTSW, AM_NONE, AM_REG, AR_AX);
 /* store special bits of cc flags into AX */
 nores_insn(I_SAHF, AM_NONE, AM_NONE);
 /* AIV 11/17/06 - added jump real zero case */
 cond_real_jmp_insn(CC_JRZ, t_bbp, f_bbp);
}
#else
/*
 if (d == 0.0) 

	xorpd	%xmm0, %xmm0
	movq	8(%rsp), %rbx
	ucomisd	d(%rip), %xmm0
	je	TRUE
        fallthru false
 */
extern void __emit_jmp_real0(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op_ti)
{
 int32 am_type;

 am_type = get_1wrd_amtype(op_ti);
 nores_insn(I_LDR2, AM_NONE, am_type, op_ti);

 /* do the fixed xor operation */
 /* xorpd	%xmm0, %xmm0 */
 nores_insn(I_XORSREAL, AM_NONE, AM_NONE);

 nores_insn(I_FUCOMPP, AM_NONE, AM_NONE);

 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}
#endif

extern int32 __emit_cmp_widomitxz_ne(int32 op1_ti, int32 op2_ti)
{
 int32 res_ti, width_ti, a0_ti, a1_ti, a2_ti;

 /* SJM 07/12/05 - change to compare followed by jump 0 */
 width_ti = __gen_cint_tn(wlen_(__get_tnwid(op1_ti)));
 a2_ti = prep_push_word_arg(width_ti);

 /* SJM 11/16/05 - order of these was wrong */
 a1_ti = prep_push_tn_addr_arg(op2_ti);
 a0_ti = prep_push_tn_addr_arg(op1_ti);
 emit_call_asl_func(ASL_WIDOMITXZ_NE, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_cmp_widall1(int32 op_ti)
{
 int32 res_ti, width_ti, a0_ti, a1_ti;

 width_ti = __gen_cint_tn(__get_tnwid(op_ti));
 a1_ti = prep_push_word_arg(width_ti);
 a0_ti = prep_push_tn_addr_arg(op_ti);
 emit_call_asl_func(ASL_VVAL_IS1, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern void __emit_jmp_cmp(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti, int32 cc)
{
 int32 cc_ti, op1_wid_ti, asl_call, cint_ti, am_type, am_type2;
 int32 a0_ti, a1_ti, a3_ti, r_ti, val;

 /* AIV 02/03/09 - if two state is one and one block it x/z just jump */
 /* to the other block */
 /* AIV 2STATE REMOVEME - 
 if (__opt_two_state)
  {
   if (f_bbp->is_xz) { __emit_jmp(t_bbp); return; }
   else if (t_bbp->is_xz) { __emit_jmp(f_bbp); return; }
  }
 */
 
 /* AIV 12/15/09 - check to compare if constant is known to be in or out */
 /* of range due to the width of the variable compare */
 /* if known just jump to known block */
 val = __chk_jmp_cmp_ops(op1_ti, op2_ti, cc);
 if (val != -1)
  {
   if (val) __emit_jmp(t_bbp); 
   else __emit_jmp(f_bbp); 
   return; 
  }

 if (__get_tnwid(op1_ti) <= WBITS)
  {
   /* if destination is a literal swap operands */
   if (__is_constant(op1_ti))
    {
     invert_jmp_operands(I_CMPL, t_bbp, f_bbp, op1_ti, op2_ti, cc, FALSE);
    }
   else
    {
     am_type = get_1wrd_amtype(op1_ti);
     am_type2 = get_1wrd_amtype(op2_ti);
     /* AIV 12/29/06 - making mem2mem illegal so need a move */
     /* if it is a constant don't need the move */
     if (!__is_constant(op2_ti) && 
         am_type == AM_NDXREG && am_type2 == AM_NDXREG)
      {
       r_ti = insert_1wrd_ndxreg_mov(op2_ti);
       nores_insn(I_CMPL, AM_REG, r_ti, am_type, op1_ti);
      }
     else nores_insn(I_CMPL, am_type2, op2_ti, am_type, op1_ti);
     cond_jmp_insn(cc, t_bbp, f_bbp);
    }
  }
 else
  {
   cc_ti = __gen_cint_tn(cc);
   a3_ti = prep_push_word_arg(cc_ti);

   /* AIV 10/12/06 - was incorrectly using op2 lenth (op2 is always 32) */
   /* for ASL_WIDE_WORD_CMP */
   /* AIV 01/07/08 - passed length is wlen - 1 */
   op1_wid_ti = __gen_cint_tn(wlen_(__get_tnwid(op1_ti)) - 1); 
   prep_push_word_arg(op1_wid_ti);

   /* AIV 08/01/06 - 291f allowed the second arg to be a of word len */
   if (__get_tnwid(op2_ti) <= WBITS)
    {
     if (__is_constant(op2_ti))
      {
       cint_ti = __gen_cint_tn(__tntab[op2_ti].tncu.tn_cint);
       a1_ti = prep_push_word_arg(cint_ti);
       asl_call = ASL_WIDE_WORD_CMP;
      }
     else 
      {
       a1_ti = prep_push_word_arg(op2_ti);
       asl_call = ASL_WIDE_WORD_CMP;
      }
    }
   else
    {
     a1_ti = prep_push_tn_addr_arg(op2_ti);
     asl_call = ASL_WIDE_CMP;
    }
   a0_ti = prep_push_tn_addr_arg(op1_ti);
   emit_call_asl_func(asl_call, 4, a3_ti, op1_wid_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(4);
   /* jump compared to zero should work for all compare cc's */
   nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
   cond_jmp_insn(CC_JE, t_bbp, f_bbp);
  }
}

/* 
 * check to compare if one operand is constant is known to be in or out 
 * range - for example
 * a > 8  can never be true if a's width is only 3 bits
 *
 * return -1 if value unknown
 *
 */
extern int32 __chk_jmp_cmp_ops(int32 op1_ti, int32 op2_ti, int32 cc)
{
 int32 op1wid, op2wid;
 word32 mask, val;
 
 /* skipping wide case */ 
 if (__get_tnwid(op1_ti) > WBITS) return(-1);

 op1wid = __get_tnwid(op1_ti);
 op2wid = __get_tnwid(op2_ti);
 if (__is_constant(op1_ti))
  {
   val = __get_wrd_con_val(op1_ti);
   mask = __masktab[op2wid];
   switch (cc) {
    case CC_JNE:
    case CC_JE:
     /* DBG remove -- */
     if (op1wid != op2wid) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     break;
    case CC_JGE:
     if (val >= mask) return(TRUE);
     break;
    case CC_JGT:
     if (val > mask) return(TRUE);
     break;
    case CC_JLE:
     if (val > mask) return(FALSE);
     break;
    case CC_JLT:
     if (val > mask) return(FALSE); 
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 else if (__is_constant(op2_ti))
  {
   val = __get_wrd_con_val(op2_ti);
   mask = __masktab[op1wid];
   switch (cc) {
    case CC_JNE:
    case CC_JE:
     /* DBG remove -- */
     if (op1wid != op2wid) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     break;
    case CC_JGE:
     if (mask < val) return(FALSE); 
     break;
    case CC_JGT:
     if (val > mask) return(FALSE); 
     break;
    case CC_JLE:
     if (val >= mask) return(TRUE); 
     break;
    case CC_JLT:
     if (val > mask) return(TRUE); 
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 return(-1);
}

/*
 * AIV 10/22/08 - almost the same as __emit_jmp_cmp
 * expect this routine takes no blocks it just sets a value to 
 * either TRUE or FALSE depending on condition codes
 */
extern void __emit_cmp_set_type(int32 op1_ti, int32 op2_ti, int32 cc, 
 int32 sgn_jmp, int32 res_ti)
{
 int32 am_type, am_type2, scc, r1_ti;

 /* if destination is a literal swap operands */
 am_type = get_1wrd_amtype(op1_ti);
 am_type2 = get_1wrd_amtype(op2_ti);
 /* AIV 10/22/08 - same as <= jmp compare code */
 /* AIV LOOKTAME - these appears backwards but leaving the same for now */
 if (__is_constant(op1_ti))
  {
   cc = __invert_cc(cc);
   nores_insn(I_CMPL, am_type, op1_ti, am_type2, op2_ti);
  }
 else
  {
   /* AIV 12/29/06 - making mem2mem illegal so need a move */
   /* if it is a constant don't need the move */
   if (!__is_constant(op2_ti) && 
       am_type == AM_NDXREG && am_type2 == AM_NDXREG)
    {
     r1_ti = insert_1wrd_ndxreg_mov(op2_ti);
     nores_insn(I_CMPL, AM_REG, r1_ti, am_type, op1_ti);
    }
   else nores_insn(I_CMPL, am_type2, op2_ti, am_type, op1_ti);
 }
 /* get the condition code insn */
 scc = get_set_insn_from_cc(cc, sgn_jmp);
 /* AIV 01/22/09 - no need to movzbl this high 3 bytes know to be 0 here */
 /* get the byte for the condition code */
 nores_insn(scc, AM_NONE, AM_REG, res_ti);
}
 
/*
 * get an set instruction type from a passed condition code
 */
static int32 get_set_insn_from_cc(int32 jmptyp, int32 sgn_jmp)
{
 int32 scc;
 
 scc = -1;
 switch (jmptyp) {
  case CC_JE:
   scc = I_SETE;
   break;
  case CC_JNE:
   scc = I_SETNE;
   break;
  case CC_JGE:
   if (sgn_jmp) scc = I_SETGE;  
   else scc = I_SETAE;
   break;
  case CC_JGT:
   if (sgn_jmp) scc = I_SETG;
   else scc = I_SETA;
   break;
  case CC_JLE:
   if (sgn_jmp) scc = I_SETLE;
   else scc = I_SETBE;
   break;
  case CC_JLT:
   if (sgn_jmp) scc = I_SETL;
   else scc = I_SETB;
   break;
  case CC_JNS:
  case CC_JP:
  case CC_JA:
  case CC_JB:
  case CC_JAE:
  case CC_JBE:
  case CC_JZ:
  case CC_JNZ:
  default: __case_terr(__FILE__, __LINE__);
 }
 return(scc);
}

     
/*
 * invert the compare operands to a cmpl insn
 * this is needed because the second operand cannot be constant
 */
static void invert_jmp_operands(int32 opcod, struct bblk_t *t_bbp, 
 struct bblk_t *f_bbp, int32 op1_ti, int32 op2_ti, int32 cc, int32 is_signed)
{
 int32 am_type, am_type2, new_cc;

 /* DBG remove -- */
 if (__is_constant(op2_ti)) __misc_terr(__FILE__, __LINE__);
 if (!__is_constant(op1_ti)) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 new_cc = __invert_cc(cc);

 am_type = get_1wrd_amtype(op1_ti);
 am_type2 = get_1wrd_amtype(op2_ti);
 nores_insn(opcod, am_type, op1_ti, am_type2, op2_ti);
 if (is_signed)
  {
   cond_sgn_jmp_insn(new_cc, t_bbp, f_bbp);
  }
 else cond_jmp_insn(new_cc, t_bbp, f_bbp);
}

/*
 * routine to invert cc when invert jump insn operands
 */
extern int32 __invert_cc(int32 cc)
{
 /* note that these are the same regardless of sign becaus they get fixed */
 /* according to sign at x86 gen time */
 switch (cc) {
  case CC_JNE:
  case CC_JE:
   /* same condition */
   break;
  case CC_JGE:
   cc = CC_JLE;
   break;
  case CC_JGT:
   cc = CC_JLT;
   break;
  case CC_JLE:
   cc = CC_JGE;
   break;
  case CC_JLT:
   cc = CC_JGT;
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(cc);
}

extern void __emit_jmp_sgn_cmp(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti, int32 cc)
{
 int32 width_ti, cc_ti, am_type, am_type2, a0_ti, a1_ti, a2_ti, a3_ti;
 int32 r_ti;

 /* AIV 02/03/09 - if two state is one and one block it x/z just jump */
 /* to the other block */
 /* AIV 2STATE REMOVEME - 
 if (__opt_two_state)
  {
   if (f_bbp->is_xz) { __emit_jmp(t_bbp); return; }
   else if (t_bbp->is_xz) { __emit_jmp(f_bbp); return; }
  }
 */

 if (__get_tnwid(op1_ti) <= WBITS)
  {
   /* if destination is a literal swap operands */
   if (__is_constant(op1_ti)) 
    {
     invert_jmp_operands(I_CMPL, t_bbp, f_bbp, op1_ti, op2_ti, cc, TRUE);
     return;
    }
   am_type = get_1wrd_amtype(op1_ti);
   am_type2 = get_1wrd_amtype(op2_ti);
   /* AIV 12/29/06 - making mem2mem illegal so need a move */
   if (!__is_constant(op2_ti) && 
       am_type == AM_NDXREG && am_type2 == AM_NDXREG)
    {
     r_ti = insert_1wrd_ndxreg_mov(op2_ti);
     nores_insn(I_CMPL, AM_REG, r_ti, am_type, op1_ti);
    }
   else nores_insn(I_CMPL, am_type2, op2_ti, am_type, op1_ti);
   cond_sgn_jmp_insn(cc, t_bbp, f_bbp);
  }
 else
  {
   cc_ti = __gen_cint_tn(cc);
   a3_ti = prep_push_word_arg(cc_ti);

   width_ti = __gen_cint_tn(__get_tnwid(op2_ti));
   a2_ti = prep_push_word_arg(width_ti);
 
//AIV? - where does ASL_WIDE_SGNWORD_CMP get inserted?
   a1_ti = prep_push_tn_addr_arg(op2_ti);
   a0_ti = prep_push_tn_addr_arg(op1_ti);
   emit_call_asl_func(ASL_SGN_WIDE_CMP, 4, a3_ti, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(4);
   /* jump compared to zero should work for all compare cc's */
   nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
   cond_jmp_insn(CC_JE, t_bbp, f_bbp);
  }
}
    
extern int32 __emit_bytecmp(int32 bytsiz, int32 op1_ti, int32 op2_ti)
{
 int32 res_ti, bytsiz_ti, a0_ti, a1_ti, a2_ti;

 /* DBG remove -- */
 if (bytsiz <= WRDBYTES) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 bytsiz_ti = __gen_cint_tn(bytsiz);
 a2_ti = prep_push_word_arg(bytsiz_ti);
 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(op2_ti);
 /* AIV FIMXE - just make memcmp later */
 emit_call_asl_func(ASL_BYTECMP, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

/*
 * AIV 09/08/06 - do a compare in words  
 * return 0 if equal
 * AIV FIXME - use a rep insn here
 */
extern int32 __emit_wordcmp(int32 wlen, int32 op1_ti, int32 op2_ti)
{
 int32 res_ti, wlen_ti, a0_ti, a1_ti, a2_ti;

 if (wlen == 1)
  {
   /* if one word just xor for the result */
   res_ti = __emit_bin_bitxor(WBITS, op1_ti, op2_ti);
   return(res_ti);
  }
 wlen_ti = __gen_cint_tn(wlen);
 a2_ti = prep_push_word_arg(wlen_ti);
 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(op2_ti);
 /* AIV FIMXE - just make memcmp later */
 emit_call_asl_func(ASL_WORDCMP, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

/*
 * AIV 08/29/06 - do a narrow compare of bytes <= WRDBYTES
 */
extern void __emit_narrow_byte_eq(int32 bytsiz, struct bblk_t *t_bbp, 
 struct bblk_t *f_bbp, int32 op1_ti, int32 op2_ti)
{
 int32 am_type, am_type2, op, mask_op1_ti, mask_op2_ti, mask_ti, r_ti;

 /* DBG remove -- */
 if (bytsiz > WRDBYTES) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 am_type = get_1wrd_amtype(op1_ti);
 am_type2 = get_1wrd_amtype(op2_ti);
 op = -1;
#ifdef __CVC32__
 if (bytsiz != 3)
  {
   if (bytsiz == 1) op = I_CMPB; 
   else if (bytsiz == 2) op = I_CMPW; 
   else if (bytsiz == WRDBYTES) op = I_CMPL; 
   else __case_terr(__FILE__, __LINE__);
   mask_op1_ti = op1_ti;
   mask_op2_ti = op2_ti;
  }
 else 
  {
   /* if it is a 3 byte compare just mask off the high byte of both ops */
   /* AIV 10/19/06 - mask was wrong for 3 bytes zero/f's swapped */
   mask_ti = __gen_cint_tn(0x00ffffff);
   mask_op1_ti = emit_oneword_and(op1_ti, mask_ti, FALSE, -1, -1);
   mask_op2_ti = emit_oneword_and(op2_ti, mask_ti, FALSE, -1, -1);
   op = I_CMPL; 
   am_type = AM_REG;
   am_type2 = AM_REG;
  }
#else
  mask_op1_ti = mask_op2_ti = -1;
  switch (bytsiz) {
   case 1:
    op = I_CMPB; 
    mask_op1_ti = op1_ti;
    mask_op2_ti = op2_ti;
    break;
   case 2:
    op = I_CMPW; 
    mask_op1_ti = op1_ti;
    mask_op2_ti = op2_ti;
    break;
   case 3:
    /* if it is a 3 byte compare just mask off the high byte of both ops */
    /* AIV 10/19/06 - mask was wrong for 3 bytes zero/f's swapped */
    mask_ti = __gen_cint_tn(0x00ffffff);
    mask_op1_ti = emit_oneword_and(op1_ti, mask_ti, FALSE, -1, -1);
    mask_op2_ti = emit_oneword_and(op2_ti, mask_ti, FALSE, -1, -1);
    op = I_CMPL; 
    am_type = AM_REG;
    am_type2 = AM_REG;
    break;
//AIV64 - FIXME - should be I_CMPL - not overwrite I_CMPL as I_CMPQ
   case 4:
    /* if it is a 3 byte compare just mask off the high byte of both ops */
    /* AIV 10/19/06 - mask was wrong for 3 bytes zero/f's swapped */
    mask_ti = __gen_cint_tn(0xffffffff);
    mask_op1_ti = emit_oneword_and(op1_ti, mask_ti, FALSE, -1, -1);
    mask_op2_ti = emit_oneword_and(op2_ti, mask_ti, FALSE, -1, -1);
    op = I_CMPL; 
    am_type = AM_REG;
    am_type2 = AM_REG;
    break;
   case 5:
    mask_ti = __gen_cint_tn(0xffffffffff);
    mask_op1_ti = emit_oneword_and(op1_ti, mask_ti, FALSE, -1, -1);
    mask_op2_ti = emit_oneword_and(op2_ti, mask_ti, FALSE, -1, -1);
//AIV64 - FIXME - should be I_CMPQ - not overwrite I_CMPL as I_CMPQ
    op = I_CMPL; 
    am_type = AM_REG;
    am_type2 = AM_REG;
    break;
   case 6:
    mask_ti = __gen_cint_tn(0xffffffffffff);
    mask_op1_ti = emit_oneword_and(op1_ti, mask_ti, FALSE, -1, -1);
    mask_op2_ti = emit_oneword_and(op2_ti, mask_ti, FALSE, -1, -1);
//AIV64 - FIXME - should be I_CMPQ - not overwrite I_CMPL as I_CMPQ
    op = I_CMPL; 
    am_type = AM_REG;
    am_type2 = AM_REG;
    break;
   case 7:
    mask_ti = __gen_cint_tn(0xffffffffffffff);
    mask_op1_ti = emit_oneword_and(op1_ti, mask_ti, FALSE, -1, -1);
    mask_op2_ti = emit_oneword_and(op2_ti, mask_ti, FALSE, -1, -1);
//AIV64 - FIXME - should be I_CMPQ - not overwrite I_CMPL as I_CMPQ
    op = I_CMPL; 
    am_type = AM_REG;
    am_type2 = AM_REG;
    break;
    case 8:
//AIV64 - FIXME - should be I_CMPQ - not overwrite I_CMPL as I_CMPQ
    op = I_CMPL; 
    mask_op1_ti = op1_ti;
    mask_op2_ti = op2_ti;
    break;
   default: __case_terr(__FILE__, __LINE__);
  }
#endif
 /* same eq literal checking */
 if (__is_constant(mask_op2_ti))
  {
   /* DBG remove -- */
   if (__is_constant(mask_op1_ti)) __misc_terr(__FILE__, __LINE__);
   /* --- */ 
   nores_insn(op, am_type2, mask_op2_ti, am_type, mask_op1_ti);
  }
 else
  {
   /* AIV 12/29/06 - making mem2mem illegal so need a move */
   if (!__is_constant(mask_op1_ti) && 
    am_type == AM_NDXREG && am_type2 == AM_NDXREG)
    {
     r_ti = insert_1wrd_ndxreg_mov(mask_op1_ti);
     nores_insn(I_CMPL, AM_REG, r_ti, am_type2, mask_op2_ti);
    }
   else nores_insn(op, am_type, mask_op1_ti, am_type2, mask_op2_ti);
  }
 cond_jmp_insn(CC_JE, t_bbp, f_bbp);
}

extern void __emit_jmp_real_cmp(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti, int32 cc) 
{
 emit_real_cmp(t_bbp, f_bbp, op1_ti, op2_ti, cc);
}


#ifdef __CVC32__
extern void __emit_jmp_real_eps_cmp(struct bblk_t *t_bbp, 
 struct bblk_t *f_bbp, int32 op_ti)
{
 int32 am_type;

 /* compare if op1 is less than EPSILON */
 am_type = get_1wrd_amtype(op_ti);
 nores_insn(I_FLDL, AM_NONE, am_type, op_ti);
//AIV - another RT special case
 nores_insn(I_FLDL, AM_NONE, AM_NLO, NLO_EPSILON);
 nores_insn(I_FUCOMPP, AM_NONE, AM_NONE);
 /* takes eax into indicate it changes eax */
 nores_insn(I_FNSTSW, AM_NONE, AM_REG, AR_AX);
 /* store special bits of cc flags into AX */
 nores_insn(I_SAHF, AM_NONE, AM_NONE);
 cond_jmp_insn(CC_JGE, t_bbp, f_bbp);
}
#else
extern void __emit_jmp_real_eps_cmp(struct bblk_t *t_bbp, 
 struct bblk_t *f_bbp, int32 op_ti)
{
 int32 am_type;

 /* op1 >= EPSILON */
 am_type = get_1wrd_amtype(op_ti);
 nores_insn(I_LDR2, AM_NONE, am_type, op_ti);

 nores_insn(I_LDEPSILON, AM_NONE, AM_NONE);
 nores_insn(I_FUCOMPP, AM_NONE, AM_NONE);
 cond_jmp_insn(CC_JGE, t_bbp, f_bbp);
}
#endif


extern void __emit_sgnbit_on_jmp(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op_ti)
{
 int32 r1_ti, r2_ti, blen, width_ti, mask_ti, a0_ti, a1_ti;
 word32 shftamt;

 blen = __get_tnwid(op_ti);
 if (__get_tnwid(op_ti) <= WBITS)
  {
   r2_ti = insert_1wrd_ndxreg_mov(op_ti);
   shftamt = (1UL << (blen - 1));
   mask_ti = __gen_cint_tn(shftamt);
   r1_ti = emit_oneword_and(mask_ti, r2_ti, FALSE, -1, -1);
   nores_insn(I_TESTL, AM_REG, r1_ti, AM_REG, r1_ti);
   cond_jmp_insn(CC_JE, f_bbp, t_bbp);
  }
 else
  {
   width_ti = __gen_cint_tn(blen);
   a1_ti = prep_push_word_arg(width_ti);
   a0_ti = prep_push_tn_addr_arg(op_ti);
   emit_call_asl_func(ASL_SGNBIT_ON, 2, a1_ti, a0_ti);
   chk_callasl_arg_num(2);
   nores_insn(I_TESTL, AM_REG, AR_AX, AM_REG, AR_AX);
   cond_jmp_insn(CC_JE, f_bbp, t_bbp);
  }
}

extern int32 __emit_widcas(int32 sel_ti, int32 match_ti, int32 wlen)
{
 int32 res_ti, wlen_ti, a0_ti, a1_ti, a2_ti;

 wlen_ti = __gen_cint_tn(wlen);
 a2_ti = prep_push_word_arg(wlen_ti);
 a1_ti = prep_push_tn_addr_arg(match_ti);
 a0_ti = prep_push_tn_addr_arg(sel_ti);
 emit_call_asl_func(ASL_WIDCAS_EVAL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_widcasx(int32 sel_ti, int32 match_ti, int32 wlen)
{
 int32 res_ti, wlen_ti, a0_ti, a1_ti, a2_ti;

 wlen_ti = __gen_cint_tn(wlen);
 a2_ti = prep_push_word_arg(wlen_ti);
 a1_ti = prep_push_tn_addr_arg(match_ti);
 a0_ti = prep_push_tn_addr_arg(sel_ti);
 emit_call_asl_func(ASL_WIDCASX_EVAL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_widcasz(int32 sel_ti, int32 match_ti, int32 wlen)
{
 int32 res_ti, wlen_ti, a0_ti, a1_ti, a2_ti;
 
 wlen_ti = __gen_cint_tn(wlen);
 a2_ti = prep_push_word_arg(wlen_ti);
 a1_ti = prep_push_tn_addr_arg(match_ti);
 a0_ti = prep_push_tn_addr_arg(sel_ti);
 /* SJM 11/15/06 - the arg order was reversed */ 
 emit_call_asl_func(ASL_WIDCASZ_EVAL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

/*
 * gen code to pop interpreter xstk (needed for some wrappers)
 */
extern void __emit_pop_xstk(int32 num_to_pop)
{
 int32 cint_ti, a0_ti;

 /* DBG remove -- */
 if (num_to_pop <= 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* AIV 02/09/12 - this is an int here cannot copy movq for 64-bit */
 /* was overwritting memory - this is now only used for */
 /* SV DPI Strings so just using as a wrapper */
 cint_ti = __gen_cint_tn(num_to_pop);
 a0_ti = prep_push_word_arg(cint_ti);
 emit_call_asl_func(ASL_POP_XSTK, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_wide_cvt_bool(int32 op1_ti, int32 op2_ti)
{
 int32 res_ti, wid_ti, a0_ti, a1_ti, a2_ti;

 /* DBG remove --  */
 if (__get_tnwid(op1_ti) <= WBITS) __misc_terr(__FILE__, __LINE__);
 /* ----  */

 /* SJM 06/05/06 - notice this is word len - need to push num */
 wid_ti = __gen_cint_tn(wlen_(__get_tnwid(op1_ti)));
 a2_ti = prep_push_word_arg(wid_ti);
 a1_ti = prep_push_tn_addr_arg(op2_ti);
 a0_ti = prep_push_tn_addr_arg(op1_ti);
 emit_call_asl_func(ASL_CVT_LNGBOOL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_ld_uprel_idp(int32 gref_ti)
{
 int32 res_ti, a0_ti;

 a0_ti = prep_push_word_arg(gref_ti);
 emit_call_asl_func(ASL_GET_UPREL_IDP, 1, a0_ti);
 chk_callasl_arg_num(1);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_ld_downrel_idp(int32 gref_ti)
{
 int32 res_ti, a0_ti;

 a0_ti = prep_push_word_arg(gref_ti);
 emit_call_asl_func(ASL_GET_DOWNREL_IDP, 1, a0_ti);
 chk_callasl_arg_num(1);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_set_thd_nxtst(struct st_t *nxtstp)
{
 int32 r1_ti, r2_ti, fld_ofs, nxtstp_ti;
 struct thread_t thd;
 struct thread_t *thdp;

 /* AIV 10/22/07 - was passing the wrong stmt here was getting nxtstp->stnxt */
 nxtstp_ti = __gen_stmt_tn(nxtstp);
 /* __cur_thd->thnxtstp = <next stmt> */
 /* __cur_thd->thnxtstp = dctp->actionst; */
 r2_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, nxtstp_ti);
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_NLO, NLO_CURTHD);

 /* if thread struct size changes offset may no longer be correct */ 
 thdp = &thd;
 fld_ofs = (byte *) &(thdp->thnxtstp) - (byte *) thdp;
 __st_insn(I_STOREA, AM_REG, r2_ti, AM_NDXREG_DISP, r1_ti, fld_ofs);
 return(nxtstp_ti);
}

#ifdef __XPROP__
//AIV XPROP
extern int32 __emit_get_xprop_accum(struct net_t *np)
{
 int32 res_ti, a0_ti, np_ti;

 np_ti = __ld_netadr_tn(np);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_GET_XPROP_ACCUM, 1, a0_ti);
 chk_callasl_arg_num(1);
 res_ti = __move_srep_insn(TN_ADR, I_MOVA, SR_VEC, np->nwid, AM_REG, AR_AX);
 return(res_ti);
}

extern void __emit_trace_xprop_write(struct st_t *stp, int32 aval_ti, 
 int32 bval_ti, int32 blen)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, stp_ti, cint_ti;

 cint_ti = __gen_cint_tn(blen);
 a3_ti = prep_push_word_arg(cint_ti);
 a2_ti = prep_push_word_arg(bval_ti);
 a1_ti = prep_push_word_arg(aval_ti);
 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_TRACE_XPROP_WRITE, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}

extern void __emit_trace_xprop_write_wide(struct st_t *stp, int32 aval_ti, 
 int32 bval_ti, int32 blen)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, stp_ti, cint_ti;

 cint_ti = __gen_cint_tn(blen);
 a3_ti = prep_push_word_arg(cint_ti);
 a2_ti = prep_push_tn_addr_arg(aval_ti);
 a1_ti = prep_push_tn_addr_arg(bval_ti);
 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_TRACE_XPROP_WRITE_WIDE, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}

extern int32 __emit_per_bit_xprop_accum(struct st_t *stp, int32 ndx,
 int32 accum_ti)
{
 int32 a0_ti, a1_ti, a2_ti, stp_ti, cint_ti, res_ti;

 stp_ti = __gen_stmt_tn(stp);
 a2_ti = prep_push_tn_addr_arg(accum_ti);
 cint_ti = __gen_cint_tn(ndx);
 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_PER_BIT_XPROP_ACCUM, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}
     
extern void __emit_stmt_assign_to_accum_wide(struct st_t *stp, 
 struct st_t *xprop_stp, int32 rhs_ti, int32 rhs_bpti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, stp_ti;

 a3_ti = prep_push_tn_addr_arg(rhs_bpti);
 a2_ti = prep_push_tn_addr_arg(rhs_ti);

 stp_ti = __gen_stmt_tn(xprop_stp);
 a1_ti = prep_push_word_arg(stp_ti);
 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_STMT_ASSIGN_TO_ACCUM_WIDE, 4, a3_ti, a2_ti, a1_ti, 
  a0_ti);
 chk_callasl_arg_num(4);
}

extern void __emit_stmt_assign_to_accum_1w(struct st_t *stp, 
 struct st_t *xprop_stp, int32 rhs_ti, int32 rhs_bpti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, stp_ti;

 a3_ti = prep_push_word_arg(rhs_bpti);
 a2_ti = prep_push_word_arg(rhs_ti);
 stp_ti = __gen_stmt_tn(xprop_stp);
 a1_ti = prep_push_word_arg(stp_ti);
 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_STMT_ASSIGN_TO_ACCUM_1W, 4, a3_ti, a2_ti, a1_ti, 
  a0_ti);
 chk_callasl_arg_num(4);
}

extern void __emit_stmt_assign_to_accum_id_1w(struct net_t *np, 
 struct st_t *xprop_stp, int32 rhs_ti, int32 rhs_bpti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, stp_ti, np_ti;
 int32 asl_typ;


 asl_typ = -1;
 if (xprop_stp->stmttyp == S_IF) 
  {
   asl_typ = ASL_STMT_ASSIGN_TO_ACCUM_1W_IF_ID;
  }
 else if (xprop_stp->stmttyp == S_CASE) 
  {
   asl_typ = ASL_STMT_ASSIGN_TO_ACCUM_1W_CASE_ID;
  }
 /* DBG remove -- */
 else __case_terr(__FILE__, __LINE__);
 /* -- */

 a3_ti = prep_push_word_arg(rhs_bpti);
 a2_ti = prep_push_word_arg(rhs_ti);
 stp_ti = __gen_stmt_tn(xprop_stp);
 a1_ti = prep_push_word_arg(stp_ti);
 np_ti = __ld_netadr_tn(np);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(asl_typ, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}

extern void __emit_stmt_assign_to_accum_id_wide(struct net_t *np, 
 struct st_t *xprop_stp, int32 rhs_ti, int32 rhs_bpti) 
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, stp_ti, np_ti;
 int32 asl_typ;

 asl_typ = -1;
 if (xprop_stp->stmttyp == S_IF) 
  {
   asl_typ = ASL_STMT_ASSIGN_TO_ACCUM_WIDE_IF_ID;
  }
 else if (xprop_stp->stmttyp == S_CASE) 
  {
   asl_typ = ASL_STMT_ASSIGN_TO_ACCUM_WIDE_CASE_ID;
  }
 /* DBG remove -- */
 else __case_terr(__FILE__, __LINE__);
 /* -- */

 a3_ti = prep_push_tn_addr_arg(rhs_ti);
 a2_ti = prep_push_tn_addr_arg(rhs_bpti);
 stp_ti = __gen_stmt_tn(xprop_stp);
 a1_ti = prep_push_word_arg(stp_ti);
 np_ti = __ld_netadr_tn(np);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(asl_typ, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}


extern void __emit_xprop_check_case_net_set(struct st_t *stp, int32 matched_ti)
{
 int32 a0_ti, a1_ti, stp_ti;

 a1_ti = prep_push_word_arg(matched_ti);
 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_XPROP_CHECK_CASE_NET_SET, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_set_xprop_accum_block(struct st_t *stp)
{
 int32 a0_ti, stp_ti;

 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 if (stp->stmttyp == S_CASE) 
  {
   emit_call_asl_func(ASL_SET_XPROP_ACCUM_BLOCK_CASE, 1, a0_ti);
  }
 else if (stp->stmttyp == S_IF) 
  {
   emit_call_asl_func(ASL_SET_XPROP_ACCUM_BLOCK_IF, 1, a0_ti);
  }
 else __case_terr(__FILE__, __LINE__);

 chk_callasl_arg_num(1);
}

extern void __emit_set_restore_xprop_accum_block(struct st_t *stp, 
 int32 xblock_ti)
{
 int32 a1_ti, a0_ti, stp_ti;

 a1_ti = prep_push_word_arg(xblock_ti);
 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_SET_RESTORE_XPROP_ACCUM_BLOCK, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_set_restore_xprop_accum_block_toself(struct st_t *stp)
{
 int32 a0_ti, stp_ti;

 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_SET_RESTORE_XPROP_ACCUM_TOSELF, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_set_restore_xprop_accum_block_nodefault(struct st_t *stp, 
 int32 num_matched_ti, int32 xcount_ti)
{
 int32 a2_ti, a1_ti, a0_ti, stp_ti;

 a2_ti = prep_push_word_arg(xcount_ti);
 a1_ti = prep_push_word_arg(num_matched_ti);
 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_SET_RESTORE_XPROP_ACCUM_BLOCK_NODEFAULT, 3, a2_ti,
  a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_get_xprop_accum_init(struct net_t *np, int32 rhs_ti,
 int32 rhs_bpti)
{
 int32 a0_ti, a1_ti, a2_ti, np_ti;

 np_ti = __ld_netadr_tn(np);
 a2_ti = prep_push_word_arg(rhs_bpti);
 a1_ti = prep_push_word_arg(rhs_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_SET_XPROP_ACCUM_INIT, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_get_xprop_accum_init_wide(struct net_t *np, int32 rhs_ti)
{
 int32 a0_ti, a1_ti, np_ti;

 np_ti = __ld_netadr_tn(np);
 a1_ti = prep_push_tn_addr_arg(rhs_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_SET_XPROP_ACCUM_INIT_WIDE, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_get_xprop_accum_to_self(struct net_t *np, int32 rhs_ti,
 int32 rhs_bpti)
{
 int32 a0_ti, a1_ti, a2_ti, np_ti;

 np_ti = __ld_netadr_tn(np);
 a2_ti = prep_push_word_arg(rhs_bpti);
 a1_ti = prep_push_word_arg(rhs_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_XPROP_ACCUM_TO_SELF, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_get_xprop_accum_to_self_wide(struct net_t *np, int32 rhs_ti)
{
 int32 a0_ti, a1_ti, np_ti;

 np_ti = __ld_netadr_tn(np);
 a1_ti = prep_push_tn_addr_arg(rhs_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_XPROP_ACCUM_TO_SELF_WIDE, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * count the number of bits (b part x/z bits)
 */
extern int32 __emit_xprop_xcount(int32 op_ti)
{
 int32 tnwid, ndx_ti, res_ti, a0_ti, a1_ti, cint_ti;
 
 tnwid = __get_tnwid(op_ti);
 if (tnwid <= WBITS)
  {
   /* if byte of less just use table */
   if (tnwid <= 8)
    {
     /* AIV 02/25/12 - always need to move the ndx into  a reg here */
     if (__tntab[op_ti].tn_typ == TN_ADR)
      {
       ndx_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, op_ti);
      }
     else ndx_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, op_ti);

     /* load the value from the table */
     res_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, ndx_ti, 
        NLO_POPCOUNT_BYTE);
     return(res_ti);
    }
   /* one word case just call the gcc builtin routine */
   /* call  __popcountdi2 */
   a0_ti = prep_push_word_arg(op_ti);
   emit_call_asl_func(ASL_POPCOUNT_1W, 1, a0_ti);
   chk_callasl_arg_num(1);
   res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
   return(res_ti);
  }
 /* wide wrapper case */
 cint_ti = __gen_cint_tn(wlen_(tnwid));
 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_tn_addr_arg(op_ti);
 emit_call_asl_func(ASL_POPCOUNT_WIDE, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}
#endif

extern void __emit_set_thd_actionst(struct st_t *nxtstp)
{
 int32 r1_ti, r2_ti, nxtstp_ti;
 size_t fld_ofs;

 /* AIV 05/14/07 - if no using static address just set the cur thread */
 /* next statement to the constant value */
 fld_ofs = (byte *) &(__cur_thd->thnxtstp) - (byte *) __cur_thd;
 nxtstp_ti = __gen_stmt_tn(nxtstp);
 /* __cur_thd->thnxtstp = dctp->actionst; */
 r2_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, nxtstp_ti);
//AIV? - what are address here?
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_NLO, NLO_CURTHD);
 __st_insn(I_STOREA, AM_REG, r2_ti, AM_NDXREG_DISP, r1_ti, fld_ofs);
}

extern int32 __emit_setsave_assoc_tsk(int32 stp_ti)
{
 int32 res_ti, a0_ti;

 /* SJM 11/13/05 - for named blocks not scheduled, set thrd's tsk for %m */
 /* this is pushed tsk call statement - extracted at run time */
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_SETSAV_ASSOC_TSK, 1, a0_ti);
 chk_callasl_arg_num(1);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

/*
 * restore __cur_thd->assoc_tsk
 */
extern void __emit_restore_assoc_tsk(int32 tsk_ti)
{
 int32 r1_ti;
 size_t fld_ofs;

 fld_ofs = (byte *) &(__cur_thd->assoc_tsk) - (byte *) __cur_thd;
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_NLO, NLO_CURTHD);
 __st_insn(I_STOREA, AM_REG, tsk_ti, AM_NDXREG_DISP, r1_ti, fld_ofs);
}

/*
 * __cur_thd->thd_ret_lab_ndx = ret_tab_ndx;
 */
extern void __emit_st_thd_ret_lab_ndx(int32 thdjmp_ndx_ti)
{
 int32 r1_ti;
 size_t fld_ofs;

 fld_ofs = (byte *) &(__cur_thd->thd_ret_lab_ndx) - (byte *) __cur_thd;
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_NLO, NLO_CURTHD);
 __st_insn(I_STOREA, AM_REG, thdjmp_ndx_ti, AM_NDXREG_DISP, r1_ti, fld_ofs);
}

/*
 * AIV 05/03/10 - these routines are now inlined - were simple wrappers
 */
/*
 * set __cur_thd->th_idp = __idp;
 */
extern void __emit_save_curthd_idp(void)
{
 int32 r1_ti;
 size_t fld_ofs;

 fld_ofs = (byte *) &(__cur_thd->th_idp) - (byte *) __cur_thd;
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_NLO, NLO_CURTHD);
 __st_insn(I_STOREA, AM_REG, IDP_REG, AM_NDXREG_DISP, r1_ti, fld_ofs);
}

/*
 * return __cur_thd->th_idp 
 */
extern int32 __emit_restore_thd_idp(void)
{
 int32 res_ti, r1_ti;
 size_t fld_ofs;

 fld_ofs = (byte *) &(__cur_thd->th_idp) - (byte *) __cur_thd;
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_NLO, NLO_CURTHD);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG_DISP, r1_ti, fld_ofs);
 return(res_ti);
}

extern void __emit_bld_nb_nodelay_tev(int32 tevp_ti) 
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(tevp_ti);
 emit_call_asl_proc(ASL_BLD_NB_NODELAY_TEV, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_schd_nb_vardel_rhsconst_dctrl(int32 stp_ti, int32 enter_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(enter_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_SCHD_NB_VARDEL_RHSCONST_DCTRL, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

 /*
  * movl	__cur_tevp, %ebx 
  * movl	4(%ebx), %eax 
  */
extern int32 __emit_ld_nbrhs_valwp(int32 tevp_reg_ti, int32 blen, int32 srtyp,
 int32 is_real)
{
 int32 r1_ti;
 struct tev_t *tevp;
 size_t offset;
       
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->tu.rhs_wp) - (byte *) tevp;
 /* DBG remove -- */
 if (offset != WRDBYTES) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 r1_ti = __move_srep_insn(TN_ADR, I_MOVA, srtyp, blen, AM_NDXREG_DISP, 
   tevp_reg_ti, offset);
 /* AIV 10/15/10 - need to mark if real flag */
 if (is_real) __tntab[r1_ti].t_real = TRUE;
 return(r1_ti);
}

extern int32 __emit_ld_nbrhs_scalar_val(int32 tevp_reg_ti, int32 srtyp)
{
 int32 r1_ti;
 size_t offset;
 struct tev_t *tevp;
       
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->scalar_nb_val) - (byte *) tevp;
 r1_ti = __move_srep_insn(TN_VAL, I_MOVZBL, srtyp, 1, AM_NDXREG_DISP, 
   tevp_reg_ti, offset);
 return(r1_ti);
}

/* AIV 10/12/07 - shut off the __cur_tevp->trigger flag */
extern void __emit_set_tevp_trigger_off(int32 tevp_reg_ti)
{
 int32 cint_ti;
 struct tev_t *tevp;
 size_t offset;
       
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 cint_ti = __gen_cint_tn(0);
 __st_insn(I_STOREA, AM_REG, cint_ti, AM_NDXREG_DISP, tevp_reg_ti, offset);
}

/*
 * get tevp->outv
 */
extern int32 __emit_ld_gate_val_from_tev(int32 tevp_ti, int32 is_2state)
{
 int32 r1_ti, r2_ti, srtyp;
 size_t offset;
 struct tev_t *tevp;
       
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->outv) - (byte *) tevp;
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, tevp_ti);
 if (is_2state) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;
 r2_ti = __move_srep_insn(TN_VAL, I_MOVZBL, srtyp, 1, AM_NDXREG_DISP, r1_ti, 
   offset);
 return(r2_ti);
}

/*
 * assign tevp->out = new_gateval_ti
 */
extern void __emit_set_tev_gate_val(int32 tevp_reg_ti, int32 new_gateval_ti)
{

 size_t offset;
 struct tev_t *tevp;
       
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->outv) - (byte *) tevp;
 __st_insn(I_STOREB, AM_REG, new_gateval_ti, AM_NDXREG_DISP, tevp_reg_ti, 
  offset);
}

extern void __emit_bldsched_proc_del(int32 stp_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_SCHED_PROC_DELAY, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_bldsched_proc_del_nt(int32 stp_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_SCHED_PROC_DELAY_NT, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * AIV 08/30/06 - added constant time lowerinf for proc delay
 */
extern void __emit_bldsched_proc_del_const(int32 tevp_ti, word64 del)
{
 int32 a0_ti;

 /* high part is zero */
 if (del == 0)
  {
   a0_ti = prep_push_tn_addr_arg(tevp_ti);
   emit_call_asl_proc(ASL_SCHED_PROC_DELAY_PND0, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
 else
  {
   a0_ti = prep_push_tn_addr_arg(tevp_ti);
   emit_call_asl_proc(ASL_SCHED_PROC_DELAY_CONST, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
}

/*
 * AIV 11/03/07 - tasks may need to alloc new events need special delay 
 * wrapper which may malloc new events
 */
extern void __emit_bldsched_proc_del_task_const(int32 tevp_ti, word64 del)
{
 int32 a0_ti;

 /* high part is zero */
 if (del == 0)
  {
   a0_ti = prep_push_tn_addr_arg(tevp_ti);
   emit_call_asl_proc(ASL_SCHED_PROC_DELAY_TASK_PND0, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
 else
  {
   a0_ti = prep_push_tn_addr_arg(tevp_ti);
   emit_call_asl_proc(ASL_SCHED_PROC_DELAY_TASK_CONST, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
}

extern void __emit_bldsched_proc_del_const_nt(int32 tevp_ti, word64 del)
{
 int32 a0_ti;

 /* high part is zero */
 if (del == 0)
  {
   a0_ti = prep_push_tn_addr_arg(tevp_ti);
   emit_call_asl_proc(ASL_SCHED_PROC_DELAY_PND0_NT, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
 else
  {
   a0_ti = prep_push_tn_addr_arg(tevp_ti);
   emit_call_asl_proc(ASL_SCHED_PROC_DELAY_CONST_NT, 1, a0_ti);
   chk_callasl_arg_num(1);
  }
}

extern void __emit_arm_ectrl(int32 tevp_ti, int32 schd_tev_ofs)
{
 int32 a0_ti, a1_ti, cint_ti;

 cint_ti = __gen_cint_tn(schd_tev_ofs);
 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_word_arg(tevp_ti);
 emit_call_asl_func(ASL_ARM_ECTRL, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_save_tevp_to_schd(int32 tevp_ti, int32 schd_tev_ti)
{
 int32 r_ti;

 /* AIV 03/25/09 - need to put in move was always mem2mem here */
 if (__inst_mod->flatinum > 1)
  {
   r_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, tevp_ti);
  }
 else r_ti = tevp_ti;

 __st_insn(I_STOREA, AM_REG, r_ti, AM_NDXREG, schd_tev_ti);
}

extern int32 __emit_schd_nbrhs_dctrl(int32 stp_ti, int32 tevp_ti, int32 nbytes)
{
 int32 a0_ti, a1_ti, a2_ti, res_ti, cint_ti;

 cint_ti = __gen_cint_tn(nbytes);
 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_word_arg(tevp_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_SCHED_NBRHS_DCTRL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_schd_nbrhs_varndx_dctrl(int32 stp_ti, int32 bi_ti, 
 int32 nbytes, int32 tevp_ti, int32 sel_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, cint_ti, res_ti;
 
 /* AIV 02/09/11 - need new wrapper to pass and save the select range as well */
 cint_ti = __gen_cint_tn(nbytes);
 if (sel_ti != -1)
  {
   a4_ti = prep_push_word_arg(sel_ti);
   a3_ti = prep_push_tn_addr_arg(tevp_ti);
   a2_ti = prep_push_word_arg(cint_ti);
   a1_ti = prep_push_word_arg(bi_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_SEL_DCTRL, 5, a4_ti, a3_ti, 
    a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(5);
   res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
   return(res_ti);
  }
 a3_ti = prep_push_tn_addr_arg(tevp_ti);
 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_DCTRL, 4, a3_ti, a2_ti, a1_ti, 
  a0_ti);
 chk_callasl_arg_num(4);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_schd_nbrhs_varndx_dctrl_const(int32 bi_ti, int32 nbytes, 
 int32 tevp_ti, int32 sel_ti)
{
 int32 cint_ti, a0_ti, a1_ti, a2_ti, a3_ti, res_ti;

 cint_ti = __gen_cint_tn(nbytes);
 /* AIV 02/09/11 - need new wrapper to pass and save the select range as well */
 if (sel_ti != -1)
  {
   a3_ti = prep_push_word_arg(sel_ti);
   a2_ti = prep_push_tn_addr_arg(tevp_ti);
   a1_ti = prep_push_word_arg(cint_ti);
   a0_ti = prep_push_word_arg(bi_ti);
   if (__all_nb_same_time == TRUE)
    {
     emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_SEL_T, 4,  a3_ti,
      a2_ti, a1_ti, a0_ti);
    }
   else
    {
     emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_DCTRL_SEL_CONST, 4,  a3_ti, 
      a2_ti, a1_ti, a0_ti);
    }
   chk_callasl_arg_num(4);
   res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
   return(res_ti);
  }
 a2_ti = prep_push_tn_addr_arg(tevp_ti);
 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_word_arg(bi_ti);
 if (__all_nb_same_time == TRUE)
  {
   emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_T, 3,  a2_ti, a1_ti, 
    a0_ti);
  }
 else
  {
   emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST, 3,  a2_ti, a1_ti, 
    a0_ti);
  }
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_sched_nb_pnd0_lhs_varndx(int32 bi_ti, int32 nbytes, 
 int32 tevp_ti, int32 sel_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, cint_ti, res_ti;

 cint_ti = __gen_cint_tn(nbytes);
 /* AIV 02/09/11 - need new wrapper to pass and save the select range as well */
 if (sel_ti != -1)
  {
   a3_ti = prep_push_word_arg(sel_ti);
   a2_ti = prep_push_tn_addr_arg(tevp_ti);
   a1_ti = prep_push_word_arg(cint_ti);
   a0_ti = prep_push_word_arg(bi_ti);
   emit_call_asl_func(ASL_SCHED_NB_PND0_LHS_VARNDX_SEL, 4, a3_ti, a2_ti, a1_ti, 
     a0_ti);
   chk_callasl_arg_num(4);
   res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
   return(res_ti);
  }
 a2_ti = prep_push_tn_addr_arg(tevp_ti);
 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_word_arg(bi_ti);
 emit_call_asl_func(ASL_SCHED_NB_PND0_LHS_VARNDX, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_schd_nbrhs_varndx_dctrl_concat(int32 stp_ti, int32 np_ti,
 int32 bi_ti, int32 nbytes, int32 tevp_ti, int32 nchg_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, a5_ti, cint_ti, res_ti;

 cint_ti = __gen_cint_tn(nbytes);
 a5_ti = prep_push_tn_addr_arg(nchg_ti);
 a4_ti = prep_push_tn_addr_arg(tevp_ti);
 a3_ti = prep_push_word_arg(cint_ti);
 a2_ti = prep_push_word_arg(bi_ti);
 a1_ti = prep_push_tn_addr_arg(np_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_DCTRL_CONCAT, 6, a5_ti, a4_ti, 
  a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(6);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_schd_nbrhs_varndx_dctrl_const_concat(int32 np_ti, 
  int32 bi_ti, int32 nbytes, int32 tevp_ti, int32 nchg_ti)
{
 int32 cint_ti, a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, res_ti;

 cint_ti = __gen_cint_tn(nbytes);
 a4_ti = prep_push_tn_addr_arg(nchg_ti);
 a3_ti = prep_push_tn_addr_arg(tevp_ti);
 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 if (__all_nb_same_time == TRUE)
  {
   emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_CONCAT_T, 5, a4_ti, 
    a3_ti, a2_ti, a1_ti, a0_ti);
  }
 else
  {
   emit_call_asl_func(ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_CONCAT, 5, a4_ti, 
    a3_ti, a2_ti, a1_ti, a0_ti);
  }
 chk_callasl_arg_num(5);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

extern int32 __emit_sched_nb_pnd0_lhs_varndx_concat(int32 np_ti, int32 bi_ti, 
 int32 nbytes, int32 tevp_ti, int32 nchg_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, cint_ti, res_ti;

 cint_ti = __gen_cint_tn(nbytes);
 a4_ti = prep_push_tn_addr_arg(nchg_ti);
 a3_ti = prep_push_tn_addr_arg(tevp_ti);
 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_SCHED_NB_PND0_LHS_VARNDX_CONCAT, 5, a4_ti, a3_ti, 
  a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(5);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}


extern void __emit_schd_nbrhs_scalar_dctrl(int32 tevp_ti, int32 stp_ti, 
  int32 rhs_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(rhs_ti);
 a1_ti = prep_push_word_arg(stp_ti);
 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_SCHED_NBRHS_SCALAR_DCTRL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * AIV 11/30/09 - handle is_last and all <= #sametime wrapper calls
 */
extern void __emit_schd_nbrhs_scalar_dctrl_const(int32 tevp_ti, int32 rhs_ti,
 int32 is_last)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(rhs_ti);
 a0_ti = prep_push_word_arg(tevp_ti);
 if (is_last)
  {
   emit_call_asl_proc(ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST_LAST, 2, a1_ti, a0_ti);
  }
 else if (__all_nb_same_time == TRUE)
  {
   emit_call_asl_proc(ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST_T, 2, a1_ti, a0_ti);
  }
 else emit_call_asl_proc(ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * non-blocking with a known delay constant
 */
extern int32 __emit_schd_nbrhs_dctrl_const(int32 tevp_ti, int32 nbytes,
 int32 is_last)
{
 int32 cint_ti, a0_ti, a1_ti, res_ti;

 cint_ti = __gen_cint_tn(nbytes);
 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 if (is_last)
  {
   emit_call_asl_func(ASL_SCHED_NBRHS_DCTRL_CONST_LAST, 2, a1_ti, a0_ti);
  }
 else if (__all_nb_same_time == TRUE)
  {
   emit_call_asl_func(ASL_SCHED_NBRHS_DCTRL_CONST_T, 2, a1_ti, a0_ti);
  }
 else emit_call_asl_func(ASL_SCHED_NBRHS_DCTRL_CONST, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}


/*
 * non-blocking with no stored memory and a known delay constant
 */
extern void __emit_schd_nbrhs_nomem_dctrl_const(int32 tevp_ti, int32 is_last)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(tevp_ti);
 if (is_last) 
  {
   emit_call_asl_proc(ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST_LAST, 1, a0_ti);
  }
 else if (__all_nb_same_time == TRUE)
  {
   emit_call_asl_proc(ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST_T, 1, a0_ti);
  }
 else emit_call_asl_proc(ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_arm_nb_ectrl(int32 stp_ti, int32 tevp_ti) 
{
 int32 a0_ti, a1_ti, res_ti;

 a1_ti = prep_push_word_arg(tevp_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_ARM_NB_ECTRL, 2, a1_ti, a0_ti);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(2);
 return(res_ti);
}

extern int32 __emit_arm_nb_varndx_ectrl(int32 stp_ti, int32 tevp_ti, 
 int32 bi_ti) 
{
 int32 a0_ti, a1_ti, a2_ti, res_ti;

 a2_ti = prep_push_word_arg(bi_ti);
 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_tn_addr_arg(stp_ti);
 emit_call_asl_func(ASL_ARM_NB_VARNDX_ECTRL, 3, a2_ti, a1_ti, a0_ti);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(3);
 return(res_ti);
}

/*
 * AIV BEWARE - values are now known to be in AR_AX 
 * if change move_time handling this needs to change as well
 */
extern int32 __emit_nb_cur_tev_reg(void)
{
 int32 cur_tevp_reg_ti;

 cur_tevp_reg_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(cur_tevp_reg_ti);
}


/*
 * Inlines the non-blocking back end code to jump to the next
 * nb event.  Inline to avoid __cur_tevp setting and in order to eliminate
 * moves this code needs to go through the reg alloc
 */
extern void __emit_nb_next_event(int32 cur_tevp_reg_ti)
{
 struct tev_t *tevp;
 int32 enterp_ti;
 size_t offset;
        

 /* AIV - same as emit_next_event */
 tevp = __free_event_tevp;
 /* DBG remove --  */
 if (cur_tevp_reg_ti == -1) __misc_terr(__FILE__, __LINE__);
 /* -----  */
 offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
 __st_insn(I_STOREA, AM_NDXREG_DISP, cur_tevp_reg_ti, offset, AM_REG, AR_AX);

 offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
 enterp_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG_DISP, AR_AX, offset);

 offset = (byte *) &(tevp->te_idp) - (byte *) tevp;
 __st_insn(I_STOREA, AM_NDXREG_DISP, AR_AX, offset, AM_REG, IDP_REG);

 __st_insn(I_STOREA, AM_REG, AR_AX, AM_NLO, NLO_CUR_TEVP);
 __emit_leave();
 nores_insn(I_TSKRET_JMP, AM_NONE, AM_REG, enterp_ti);
}



extern void __emit_setup_namblk(int32 stp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_SCHED_NAMBLK_THD, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_setup_task_thd(int32 stp_ti, int32 nxt_stp_ti)
{
 int32 a0_ti, a1_ti;

 /* 2nd arg is stmt to continue at after returning from scheduler */
 /* if no continue will be 0 */
 /* SJM 10/11/05 - BEWARE - 0 is same is NULL in asm - must be assumed? */
 a1_ti = prep_push_word_arg(nxt_stp_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_SETUP_TASK_THD, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_setup_task_thd_auto(int32 stp_ti, int32 nxt_stp_ti, 
 int32 saved_idp_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(saved_idp_ti);
 a1_ti = prep_push_word_arg(nxt_stp_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_SETUP_TASK_THD_AUTO, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_schd_fork(int32 stp_ti, int32 nxt_stp_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(nxt_stp_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_SCHED_FORK, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_exec_qc_assign(int32 stp_ti, int32 rhsbi_ti, int32 nchg_ti, 
 int32 nchg_idp_ofs_ti, int32 lhsx_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 /* AIV 03/02/12 - non-concat no longer load exprs */
 if (lhsx_ti == -1)
  {
   a3_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a2_ti = prep_push_tn_addr_arg(nchg_ti);
   a1_ti = prep_push_word_arg(rhsbi_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_ASSIGN, 4, a3_ti, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(4);
  }
 else
  {
   a4_ti = prep_push_tn_addr_arg(lhsx_ti);
   a3_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a2_ti = prep_push_tn_addr_arg(nchg_ti);
   a1_ti = prep_push_word_arg(rhsbi_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_ASSIGN_CONCAT, 5, a4_ti, a3_ti, a2_ti, a1_ti, 
    a0_ti);
   chk_callasl_arg_num(5);
  }
}

extern void __emit_exec_qc_force(int32 stp_ti, int32 rhsbi_ti, int32 nchg_ti, 
 int32 nchg_idp_ofs_ti, int32 lhsx_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 /* AIV 03/02/12 - non-concat no longer load exprs */
 if (lhsx_ti == -1)
  {
   a3_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a2_ti = prep_push_tn_addr_arg(nchg_ti);
   a1_ti = prep_push_word_arg(rhsbi_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_FORCE, 4, a3_ti, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(4);
  }
 else
  {
   a4_ti = prep_push_tn_addr_arg(lhsx_ti);
   a3_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a2_ti = prep_push_tn_addr_arg(nchg_ti);
   a1_ti = prep_push_word_arg(rhsbi_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_FORCE_CONCAT, 5, a4_ti, a3_ti, a2_ti, a1_ti, 
     a0_ti);
   chk_callasl_arg_num(5);
  }
}

extern void __emit_exec_qc_wireforce(int32 stp_ti, int32 lhsx_ti, int32 bi_ti,
 int32 nchg_ti, int32 nchg_idp_ofs_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 /* AIV 03/02/12 - non-concat no longer load exprs */
 if (lhsx_ti == -1)
  {
   a3_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a2_ti = prep_push_tn_addr_arg(nchg_ti);
   a1_ti = prep_push_word_arg(bi_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_WIREFORCE, 4, a3_ti, a2_ti, a1_ti, 
    a0_ti);
   chk_callasl_arg_num(4);
  }
 else
  {
   a4_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a3_ti = prep_push_tn_addr_arg(nchg_ti);
   a2_ti = prep_push_word_arg(bi_ti);
   a1_ti = prep_push_word_arg(lhsx_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_WIREFORCE_CONCAT, 5, a4_ti, a3_ti, a2_ti, 
    a1_ti, a0_ti);
   chk_callasl_arg_num(5);
  }
}

extern void __emit_exec_qc_tran_wireforce(int32 stp_ti, int32 lhsx_ti, 
 int32 bi_ti, int32 nchg_ti, int32 nchg_idp_ofs_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 /* AIV 03/02/12 - non-concat no longer load exprs */
 if (lhsx_ti == -1)
  {
   a3_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a2_ti = prep_push_tn_addr_arg(nchg_ti);
   a1_ti = prep_push_word_arg(bi_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_TRAN_WIREFORCE, 4, a3_ti, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(4);
  }
 else
  {
   a4_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a3_ti = prep_push_tn_addr_arg(nchg_ti);
   a2_ti = prep_push_word_arg(bi_ti);
   a1_ti = prep_push_word_arg(lhsx_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_TRAN_WIREFORCE_CONCAT, 5, a4_ti, a3_ti, a2_ti, 
    a1_ti, a0_ti);
   chk_callasl_arg_num(5);
  }
}

extern void __emit_exec_qc_deassign(int32 stp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_EXEC_QC_DEASSIGN, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_exec_qc_deassign_concat(int32 lhsx_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(lhsx_ti);
 emit_call_asl_proc(ASL_EXEC_QC_DEASSIGN_CONCAT, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_exec_qc_deassign_force(int32 stp_ti, int32 lhsx_ti, 
 int32 nchg_ti, int32 nchg_idp_ofs_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 /* AIV 03/02/12 - non-concat no longer load exprs */
 if (lhsx_ti == -1)
  {
   a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a1_ti = prep_push_tn_addr_arg(nchg_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_DEASSIGN_FORCE, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
  }
 else
  {
   a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a1_ti = prep_push_tn_addr_arg(nchg_ti);
   a0_ti = prep_push_word_arg(lhsx_ti);
   emit_call_asl_proc(ASL_EXEC_QC_DEASSIGN_FORCE_CONCAT, 3, a2_ti, a1_ti, 
     a0_ti);
   chk_callasl_arg_num(3);
  }
}

extern void __emit_exec_qc_wirerelease(int32 stp_ti, int32 lhsx_ti,
 int32 nchg_ti, int32 nchg_idp_ofs_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 /* AIV 03/02/12 - non-concat no longer load exprs */
 if (lhsx_ti == -1)
  {
   a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a1_ti = prep_push_tn_addr_arg(nchg_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_WIRERELEASE, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
  }
 else
  {
   a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a1_ti = prep_push_tn_addr_arg(nchg_ti);
   a0_ti = prep_push_word_arg(lhsx_ti);
   emit_call_asl_proc(ASL_EXEC_QC_WIRERELEASE_CONCAT, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
  }
}

extern void __emit_exec_qc_tran_wirerelease(int32 stp_ti, int32 lhsx_ti, 
 int32 nchg_ti, int32 nchg_idp_ofs_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 /* AIV 03/02/12 - non-concat no longer load exprs */
 if (lhsx_ti == -1)
  {
   a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a1_ti = prep_push_tn_addr_arg(nchg_ti);
   a0_ti = prep_push_word_arg(stp_ti);
   emit_call_asl_proc(ASL_EXEC_QC_TRAN_WIRERELEASE, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
  }
 else
  {
   a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
   a1_ti = prep_push_tn_addr_arg(nchg_ti);
   a0_ti = prep_push_word_arg(lhsx_ti);
   emit_call_asl_proc(ASL_EXEC_QC_TRAN_WIRERELEASE_CONCAT, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
  }
}

extern void __emit_exec_cause(int32 stp_ti, int32 nchg_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_tn_addr_arg(nchg_ti);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_EXEC_CAUSE, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern int32 __emit_exec_dsable(int32 stp_ti)
{
 int32 res_ti, a0_ti;

 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_EXEC_DISABLE, 1, a0_ti);
 chk_callasl_arg_num(1);
 res_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}
   /* FIXME - get offset otherwise fine if dcevnt_t struct doesn't change */
  /* ---
   %eax = dcep->dce_off;
    movzbl	3(%eax), %eax
  --- */
extern void __emit_jmp_dce_off(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 dce_ti)
{
 int32 r1_ti, r2_ti;

 /* AIV 09/08/08 - made dce_off a byte instead of one bit to produce */
 /* better code */
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, dce_ti);
 r2_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG_DISP, r1_ti, 3UL);
 nores_insn(I_TESTL, AM_REG, r2_ti, AM_REG, r2_ti);

 cond_jmp_insn(CC_JE, f_bbp, t_bbp);
}

extern int32 __emit_downrel_targ_to_ref(int32 gref_ti)
{
 int32 r_ti, a0_ti;

 a0_ti = prep_push_word_arg(gref_ti);
 emit_call_asl_func(ASL_DOWNREL_TARG_TO_REF, 1, a0_ti);
 chk_callasl_arg_num(1);
 r_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

extern int32 __emit_uprel_targ_to_ref(int32 gref_ti)
{
 int32 r_ti, a0_ti;

 a0_ti = prep_push_word_arg(gref_ti);
 emit_call_asl_func(ASL_UPREL_TARG_TO_REF, 1, a0_ti);
 chk_callasl_arg_num(1);
 r_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

extern void __emit_trigger_ectrl(int32 tevp_ti, struct delctrl_t *dctp) 
{
 int32 a0_ti;

 /* AIV 12/15/10 - mark this event as touced */
 if (__event_coverage) __emit_event_coverage(dctp);
 a0_ti = prep_push_word_arg(tevp_ti);
 emit_call_asl_func(ASL_TRIGGER_ECTRL, 1, a0_ti);
 chk_callasl_arg_num(1);
}

#ifdef __XPROP__
/*
 * trigger and set set enterptr address
 */
extern void __emit_trigger_ectrl_xprop(int32 tevp_ti, struct delctrl_t *dctp,
 int32 stp_ti) 
{
 int32 a0_ti, a1_ti;

 /* DBG remove --  */
 if (dctp->xprop_xedge_actionst == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* AIV 12/15/10 - mark this event as touced */
 if (__event_coverage) __emit_event_coverage(dctp);

 a1_ti = prep_push_word_arg(stp_ti);
 a0_ti = prep_push_word_arg(tevp_ti);
 emit_call_asl_func(ASL_TRIGGER_ECTRL_XPROP, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * set set enterptr address for tevp
 */
extern void __emit_set_tev_enter_adr_xprop(int32 tevp_ti, int32 enter_ti)
{
 int32 r_ti;
 struct tev_t *tevp;
 size_t offset;
#ifndef __CVC32__
 int32 tenter_ofs_ti;
#endif

 /* tevp->enterptr = ep; */
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
#ifndef __CVC32__
 /* if +large model must move $tevp and $ST values to tmps with movabsq */
 if (__cvc_use_large_model) 
  {
   /* if this is one instance this will be $tev here so must move with */
   /* movabsq here - otherwise do normal load */
   if (__tntab[tevp_ti].comlab_typ == COMLAB_TEVP && __inst_mod->flatinum == 1)
    {
     tenter_ofs_ti = __move_insn(TN_ADR, I_MOVABSQ, AM_REG, tevp_ti);
    }
   else tenter_ofs_ti = __move_insn(TN_ADR, I_MOVQ, AM_REG, tevp_ti);

   __st_insn(I_MOVA, AM_REG, enter_ti, AM_NDXREG_DISP, tenter_ofs_ti, offset);
  }
 else 
  {
   r_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, tevp_ti);
   __st_insn(I_MOVA, AM_REG, enter_ti, AM_NDXREG_DISP, r_ti, offset);
  }
#else
 r_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, tevp_ti);
 __st_insn(I_MOVA, AM_REG, enter_ti, AM_NDXREG_DISP, r_ti, offset);
#endif
}

/*
 *
 */
extern int32 __emit_has_xedge_wide(int32 op1_ti, int32 op2_ti, int32 blen)
{
 int32 a0_ti, a1_ti, a2_ti, cint_ti, r_ti;
 int32 wlen;

 wlen = wlen_(blen);
 cint_ti = __gen_cint_tn(wlen);

 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(op2_ti);
 emit_call_asl_func(ASL_HAS_XEDGE_WIDE, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

/*
 *
 */
extern int32 __emit_has_xedge_wide_st(int32 op1_ti, int32 op2_ti, int32 blen)
{
 int32 a0_ti, a1_ti, a2_ti, cint_ti, r_ti;

 cint_ti = __gen_cint_tn(blen);
 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(op2_ti);
 emit_call_asl_func(ASL_HAS_XEDGE_WIDE_ST, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

/*
 *
 */
extern int32 __emit_xprop_xedge_net(struct st_t *stp)
{
 int32 a0_ti, stp_ti, r_ti;

 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_XPROP_XEDGE_NET, 1, a0_ti);
 chk_callasl_arg_num(1);
 r_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

/*
 *
 */
extern void __emit_xprop_set_xedge_net(struct st_t *stp, struct net_t *np,
 int32 setval_ti)
{
 int32 a0_ti, a1_ti, a2_ti, stp_ti, np_ti;

 a2_ti = prep_push_word_arg(setval_ti);
 np_ti = __ld_netadr_tn(np);
 a1_ti = prep_push_word_arg(np_ti);
 stp_ti = __gen_stmt_tn(stp);
 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_func(ASL_XPROP_SET_XEDGE_NET, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}
#endif

/*
 * mark a @ delay control as triggered - for coverage
 */
extern void __emit_event_coverage(struct delctrl_t *dctp) 
{
 int32 cint_ti, event_ti;
 size_t offset;


 cint_ti = __gen_cint_tn(TRUE);
 /* if merged use the dctp merged into */
 if (dctp->head_dctp != NULL) 
  {
   dctp = dctp->head_dctp;
  }
 event_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_EVENT_COVER);
 /* DBG remove --  */
 if (dctp->dc_id_ndx < 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 offset = dctp->dc_id_ndx*WRDBYTES;
 __st_insn(I_MOVA, AM_REG, cint_ti, AM_NDXREG_DISP, event_ti, offset);
}

/*
 * mark a statement as executed - for coverage
 */
extern void __emit_stmt_coverage(struct st_t *stp) 
{
 int32 cint_ti, stp_ti;
 size_t offset;

 /* DBG remove --  */
 if (stp->st_ndx < 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 cint_ti = __gen_cint_tn(TRUE);
 stp_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_STMT_COVER);
 offset = stp->st_ndx*WRDBYTES;
 __st_insn(I_MOVA, AM_REG, cint_ti, AM_NDXREG_DISP, stp_ti, offset);
}

extern void __emit_nb_trigger_ectrl(int32 tevp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(tevp_ti);
 emit_call_asl_proc(ASL_NB_TRIGGER_ECTRL, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_monit_trigger(void)
{
 int32 se_monit_ti;

 /* AIV 07/23/08 - I think these should not be loaded and be done in place */
 /* as a store type insn???????? x86 but most of bbgen3 is */
 se_monit_ti = __gen_cint_tn(SE_MONIT_TRIGGER);
 __st_insn(I_ORL, AM_REG, se_monit_ti, AM_NLO, NLO_SLOTEND_ACTION);
 /* __slotend_action |= SE_MONIT_TRIGGER */
 /* SJM 12/01/07 - notice the loads from memory really needed here */ 
 /* SJM 12/02/07 - need store into the nlo amode - old code worked */
 /* because it copied into the nlo tn */
 /* this follows rule of only ld/store can access memory */
 /*
 int32 slotend_action_ti, r1_ti;
 slotend_action_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO,
  NLO_SLOTEND_ACTION);

 r1_ti = oneword_binop(I_ORL, se_monit_ti, slotend_action_ti);

 __st_insn(I_STOREA, AM_REG, r1_ti, AM_NLO, NLO_SLOTEND_ACTION);
 */
}

extern void __emit_fmonit_trigger(int32 dcep_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(dcep_ti);
 emit_call_asl_proc(ASL_FMONIT_TRIGGER, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_assign_qcaf_regform(int32 dcep_ti, int32 nchg_ti, 
 int32 nchg_idp_ofs_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
 a1_ti = prep_push_tn_addr_arg(nchg_ti);
 a0_ti = prep_push_tn_addr_arg(dcep_ti);
 emit_call_asl_proc(ASL_ASSIGN_QCAF_REGFORM, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_assign_qcaf(int32 dcep_ti, int32 nchg_ti, 
 int32 nchg_idp_ofs_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
 a1_ti = prep_push_tn_addr_arg(nchg_ti);
 a0_ti = prep_push_tn_addr_arg(dcep_ti);
 emit_call_asl_proc(ASL_ASSIGN_QCAF, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_assign_scalar_qcaf(int32 dcep_ti, int32 nchg_ti, 
 int32 nchg_idp_ofs_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(nchg_idp_ofs_ti);
 a1_ti = prep_push_tn_addr_arg(nchg_ti);
 a0_ti = prep_push_tn_addr_arg(dcep_ti);
 emit_call_asl_proc(ASL_ASSIGN_SCALAR_QCAF, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_assign_qcaf_regform_concat(int32 stp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_ASSIGN_QCAF_REGFORM_CONCAT, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_assign_qcaf_concat(int32 stp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(stp_ti);
 emit_call_asl_proc(ASL_ASSIGN_QCAF_CONCAT, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_exec_wide_logic_gate(int32 gp_ti, int32 obnum,
  int32 out_chg_ti)
{
 int32 obnum_ti, a0_ti, a1_ti, r_ti, r1_ti;

 obnum_ti = __gen_cint_tn(obnum);
 a1_ti = prep_push_word_arg(obnum_ti);
 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_func(ASL_EXEC_WIDE_LOGIC_GATE, 2, a1_ti, a0_ti);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 /* AIV LOOKATME BEWARE - machine dependent - but most of bbgen3 is as well */
 r1_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_CX);
 __st_insn(I_STOREA, AM_REG, r1_ti, AM_REG, out_chg_ti);
 chk_callasl_arg_num(2);
 return(r_ti);
}

extern int32 __emit_exec_np_tranif(int32 gp_ti)
{
 int32 a0_ti, r_ti;

 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_func(ASL_EVAL_TRANIF_LD, 1, a0_ti);
 chk_callasl_arg_num(1);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

extern void __emit_immed_eval_trifchan(int32 gp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_proc(ASL_IMMED_EVAL_TRIFCHAN, 1, a0_ti);
 chk_callasl_arg_num(1);
}

/*
 * generate temp for timing check address
 */
extern int32 __gen_tchk_tn(struct chktchg_t *chktcp, int32 npp_id)
{
 int32 tni;
 struct tn_t *tnp;

 tni = __gen_tn(SR_VEC, WBITS);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_TCHK;
 /* DBG remove --  */
 if (chktcp->chkoldval_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 tnp->tncu.el_ndx = npp_id;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
#ifdef __VALTRK__
 tnp->nd_valtrk_idp_siz = TRUE;
#endif
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) chktcp;
 return(tni);
}

/*
 * generate temp for path delay values
 */
extern int32 __gen_del_tn(int32 del_id, void *deladr)
{
 int32 tni;
 struct tn_t *tnp;

 tni = __gen_tn(SR_VEC, WBITS);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_DEL;
 /* DBG remove --  */
 if (del_id == -1) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 tnp->tncu.el_ndx = del_id;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
#ifdef __VALTRK__
 tnp->nd_valtrk_idp_siz = TRUE;
#endif
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) deladr;
 return(tni);
}

extern void __emit_timing_check_record(int32 tchg_adr_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(tchg_adr_ti);
 emit_call_asl_proc(ASL_TIMING_CHECK_RECORD, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_sched_scalar_mipd(int32 np_ti, int32 tevp_ti,
 struct net_pin_t *npp)
{
 int32 a0_ti, a1_ti, asltype, is_const;
 word64 mdel;
 struct mipd_t *mipdp;
 
 mipdp = &(npp->elnpp.emipdbits[0]);
 if (!mipdp->pth_mipd || mipdp->impthtab == NULL)
  {
   is_const = __check_delay_constant(mipdp->pb_mipd_du, mipdp->pb_mipd_delrep,
      &(mdel));
   if (is_const) 
    {
     /* high part is zero */
     if (mdel == 0) 
      {
       a0_ti = prep_push_tn_addr_arg(tevp_ti);
       emit_call_asl_proc(ASL_SCHED_SCALAR_MIPD_PND0, 1, a0_ti);
       chk_callasl_arg_num(1);
      }
     else
      {
       a0_ti = prep_push_tn_addr_arg(tevp_ti);
       emit_call_asl_proc(ASL_SCHED_SCALAR_MIPD_CONST, 1,  a0_ti);
       chk_callasl_arg_num(1);
      }
     return;
    }

   asltype = -1;
   switch (mipdp->pb_mipd_delrep) {
     case DT_16V: asltype = ASL_SCHED_SCALAR_MIPD_16V; break;
     case DT_IS16V: asltype = ASL_SCHED_SCALAR_MIPD_IS16V; break;
     case DT_IS16V1: asltype = ASL_SCHED_SCALAR_MIPD_IS16V1; break;
     case DT_IS16V2: asltype = ASL_SCHED_SCALAR_MIPD_IS16V2; break;
     case DT_IS1V:
     case DT_IS1V1:
     case DT_IS1V2:
      a0_ti = prep_push_tn_addr_arg(tevp_ti);
      emit_call_asl_proc(ASL_SCHED_SCALAR_MIPD_IS1V, 1, a0_ti);
      chk_callasl_arg_num(1);
      return;
     default: __case_terr(__FILE__, __LINE__); break;
    }
   a1_ti = prep_push_tn_addr_arg(tevp_ti);
   a0_ti = prep_push_word_arg(np_ti);
   emit_call_asl_proc(asltype, 2, a1_ti, a0_ti);
   chk_callasl_arg_num(2);
  }
 else
  {
   a1_ti = prep_push_tn_addr_arg(tevp_ti);
   a0_ti = prep_push_word_arg(np_ti);
   emit_call_asl_proc(ASL_SCHED_SCALAR_MIPD_PATH, 2, a1_ti, a0_ti);
   chk_callasl_arg_num(2);
  }
}

extern void __emit_sched_vec_mipd_bit(int32 np_ti, int32 tevp_ti, int32 bi)
{
 int32 a0_ti, a1_ti, a2_ti, cint_ti;

 cint_ti = __gen_cint_tn(bi);
 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_tn_addr_arg(tevp_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_SCHED_VEC_MIPD_BIT, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_process_mipd_nchg_ev(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_PROCESS_MIPD_NCHG, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_process_mipd_scalar_nchg_ev(int32 nchg_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(nchg_ti);
 emit_call_asl_proc(ASL_PROCESS_SCAL_MIPD_NCHG, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_force_active(int32 np_ti, int32 biti_ti)
{
 int32 r_ti, a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(biti_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_FORCE_ACTIVE, 2, a1_ti, a0_ti);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(2);
 return(r_ti);
}

extern void __emit_eval_tran_drvr_1bit(int32 np_ti, int32 bi_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_DRVRS, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_eval_tran_drvr_vector(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_DRVRS_VECTOR, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern int32 __emit_update_tran_harddrvs(int32 np_ti)
{
 int32 a0_ti, r_ti;

 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_UPDATE_TRAN_HARDDRVS, 1, a0_ti);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(1);
 return(r_ti);
}

extern int32 __emit_tran_addr(int32 np_ti) 
{
 int32 a0_ti, r_ti;

 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_func(ASL_TRAN_ADDR, 1, a0_ti);
 r_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(1);
 return(r_ti);
}

extern int32 __emit_stren_schd_bidpthdrvrs(int32 np_ti, int32 drv_ti,
  int32 tran_ti, int32 bi_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, r_ti;

 a4_ti = prep_push_tn_addr_arg(tevp_ti);
 a3_ti = prep_push_word_arg(bi_ti);
 a2_ti = prep_push_tn_addr_arg(tran_ti);
 a1_ti = prep_push_tn_addr_arg(drv_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_STREN_SCHD_BIDPTHDRVRS, 5, a4_ti, a3_ti, a2_ti, a1_ti, 
  a0_ti);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(5);
 return(r_ti);
}

extern int32 __emit_schd_bidpthdrvrs(int32 np_ti, int32 drv_ti, int32 tran_ti,
  int32 bi_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, r_ti;

 a4_ti = prep_push_tn_addr_arg(tevp_ti);
 a3_ti = prep_push_word_arg(bi_ti);
 a2_ti = prep_push_tn_addr_arg(tran_ti);
 a1_ti = prep_push_tn_addr_arg(drv_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_SCHD_BIDPTHDRVRS, 5, a4_ti, a3_ti, a2_ti, a1_ti, a0_ti);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(5);
 return(r_ti);
}

extern int32 __emit_schd_scalar_bidpthdrvrs(int32 np_ti, int32 drv_ti, 
 int32 tran_ti, int32 bi_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, r_ti;

 a4_ti = prep_push_tn_addr_arg(tevp_ti);
 a3_ti = prep_push_word_arg(bi_ti);
 a2_ti = prep_push_tn_addr_arg(tran_ti);
 a1_ti = prep_push_tn_addr_arg(drv_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_SCHD_SCALAR_BIDPTHDRVRS, 5, a4_ti, a3_ti, a2_ti, 
   a1_ti, a0_ti);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(5);
 return(r_ti);
}

extern void __emit_store_bidpthdrvrs(int32 np_ti, int32 tran_ti, int32 bi_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(bi_ti);
 a1_ti = prep_push_tn_addr_arg(tran_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_STORE_BIDPTHDRVRS, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern int32 __emit_trpath_scalar_store(int32 np_ti, int32 new_ti)
{
 int32 a0_ti, a1_ti, r_ti;

 a1_ti = prep_push_word_arg(new_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_TRPATH_SCALAR_STORE, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

extern int32 __emit_trpath_store(int32 np_ti, int32 new_ti, int32 bi_ti)
{
 int32 a0_ti, a1_ti, a2_ti, r_ti;

 a2_ti = prep_push_word_arg(bi_ti);
 a1_ti = prep_push_word_arg(new_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_TRPATH_STORE, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

extern int32 __emit_qc_active(int32 np_ti, int32 cint_ti)
{
 int32 a0_ti, a1_ti, r_ti;

 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_QC_ACTIVE, 2, a1_ti, a0_ti);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 chk_callasl_arg_num(2);
 return(r_ti);
}
      
extern void __emit_eval_htran_wire_1bit(int32 np_ti, int32 bi_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_EVAL_HTRAN_WIRE_1BIT, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_eval_htran_wire_1bit_nchg(int32 np_ti, int32 nchg_ti, 
 int32 bi_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(bi_ti);
 a1_ti = prep_push_tn_addr_arg(nchg_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_EVAL_HTRAN_WIRE_1BIT_NCHG, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_eval_htran_stwire_1bit(int32 np_ti, int32 bi_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_EVAL_HTRAN_STWIRE_1BIT, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_eval_htran_stwire_1bit_nchg(int32 np_ti, int32 nchg_ti, 
 int32 bi_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(bi_ti);
 a1_ti = prep_push_tn_addr_arg(nchg_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_EVAL_HTRAN_STWIRE_1BIT, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern int32 __emit_bpart_of_tran(void)
{
 int32 r_ti;

 /* AIV LOOKATME BEWARE - machine dependent - but most of bbgen3 is as well */
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_CX);
 return(r_ti);
}

extern void __emit_eval_tran_bidchan_1bit_assign(int32 chanid_ti)
{
 int32 a0_ti;


 a0_ti = prep_push_word_arg(chanid_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_BIDCHAN_1BIT_ASSIGN, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_eval_tran_stbidchan_1bit_assign(int32 chanid_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(chanid_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_STBIDCHAN_1BIT_ASSIGN, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_eval_tran_bidchan_vectored_assign(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_BIDCHAN_VECTORED_ASSIGN, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_eval_tran_stbidchan_vectored_assign(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_STBIDCHAN_VECTORED_ASSIGN, 1, a0_ti);
 chk_callasl_arg_num(1);
}


extern int32 __emit_eval_tran_bidchan_1bit(int32 chanid_ti)
{
 int32 a0_ti, r_ti;


 a0_ti = prep_push_word_arg(chanid_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_BIDCHAN_1BIT, 1, a0_ti);
 chk_callasl_arg_num(1);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

extern int32 __emit_eval_tran_scalar_bidchan_1bit(int32 chanid_ti)
{
 int32 a0_ti, r_ti;

 a0_ti = prep_push_word_arg(chanid_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_SCALAR_BIDCHAN_1BIT, 1, a0_ti);
 chk_callasl_arg_num(1);
 r_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, AR_AX);
 return(r_ti);
}

extern int32 __emit_eval_tran_stbidchan_1bit(int32 chanid_ti)
{
 int32 a0_ti, r_ti;

 a0_ti = prep_push_word_arg(chanid_ti);
 emit_call_asl_proc(ASL_EVAL_TRAN_STBIDCHAN_1BIT, 1, a0_ti);
 chk_callasl_arg_num(1);
 r_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SSCAL, 1, AM_REG, AR_AX);
 return(r_ti);
}

extern void __emit_adjust_trireg(int32 sbp_ti, int32 lhs_sbpti, int32 blen, 
 int32 stval)
{
 int32 stval_ti, blen_ti, a0_ti, a1_ti, a2_ti, a3_ti;

 stval_ti = __gen_cint_tn(stval);
 a3_ti = prep_push_word_arg(stval_ti);
 blen_ti = __gen_cint_tn(blen);
 a2_ti = prep_push_word_arg(blen_ti);
 a1_ti = prep_push_tn_addr_arg(lhs_sbpti);
 a0_ti = prep_push_tn_addr_arg(sbp_ti);
 emit_call_asl_proc(ASL_ADJUST_TRIREG, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}

extern void __emit_wdel_trireg_hiz(int32 np_ti, 
 int32 oldval_ti, int32 newsbp_ti, int32 biti_ti, int32 ctevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 /* SJM 04/26/07 - new sbp is a write ptr so must be first */
 a4_ti = prep_push_tn_addr_arg(ctevp_ti);
 a3_ti = prep_push_word_arg(biti_ti);
 a2_ti = prep_push_word_arg(oldval_ti);
 a1_ti = prep_push_tn_addr_arg(newsbp_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_WDEL_TRIREG_SCHED_HIZ, 5, a4_ti, a3_ti, a2_ti, a1_ti, 
   a0_ti);
 chk_callasl_arg_num(5);
}

extern void __emit_stren_sched_1pthbit(int32 np_ti, int32 bi_ti,
 int32 nscalw_ti, int32 oscalw_ti, int32 nchg_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, a5_ti;

 a5_ti = prep_push_tn_addr_arg(tevp_ti);
 a4_ti = prep_push_tn_addr_arg(nchg_ti);
 /* AIV LOOKATME - why is strength the same as non-stren ???????????? */
 a3_ti = prep_push_word_arg(oscalw_ti);
 /* sometimes nscalw is literal value as well */
 a2_ti = prep_push_word_arg(nscalw_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_SCHD_ST_1PTHWIREBIT, 6, a5_ti, a4_ti, a3_ti, a2_ti, 
  a1_ti, a0_ti);
 chk_callasl_arg_num(6);
}

extern void __emit_stren_sched_1wirbit(int32 np_ti, int32 bi_ti,
 int32 nscalw_ti, int32 oscalw_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 /* AIV LOOKATME - why is strength the same as non-stren ???????????? */
 /* last arg always FALSE */

 a4_ti = prep_push_tn_addr_arg(tevp_ti);
 a3_ti = prep_push_word_arg(oscalw_ti);
 a2_ti = prep_push_word_arg(nscalw_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_WDEL_SCHD_1WIREBIT, 5, a4_ti, a3_ti, a2_ti, a1_ti, 
  a0_ti);
 chk_callasl_arg_num(5);
}

extern void __emit_sched_1pthbit(int32 np_ti, int32 bi_ti, int32 nscalw_ti,
 int32 oscalw_ti, int32 nchg_ti, int32 enter_ti, int32 has_stren)
{ 
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, a5_ti;

 a5_ti = prep_push_tn_addr_arg(enter_ti);
 a4_ti = prep_push_tn_addr_arg(nchg_ti);
 a3_ti = prep_push_word_arg(oscalw_ti);
 /* sometimes nscalw is literal value as well */
 a2_ti = prep_push_word_arg(nscalw_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 if (has_stren)
  {
   emit_call_asl_proc(ASL_SCHD_ST_1PTHWIREBIT, 6, a5_ti, a4_ti, a3_ti, a2_ti,
    a1_ti, a0_ti);
  }
 else
  {
   emit_call_asl_proc(ASL_SCHD_1PTHWIREBIT, 6, a5_ti, a4_ti, a3_ti, a2_ti,
    a1_ti, a0_ti);
  }
 chk_callasl_arg_num(6);
}

extern void __emit_sched_1pthbit_nomsg(int32 np_ti, int32 bi_ti, 
 int32 nscalw_ti, int32 oscalw_ti, int32 nchg_ti, int32 enter_ti)
{ 
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, a5_ti;

 a5_ti = prep_push_tn_addr_arg(enter_ti);
 a4_ti = prep_push_tn_addr_arg(nchg_ti);
 a3_ti = prep_push_word_arg(oscalw_ti);
 /* sometimes nscalw is literal value as well */
 a2_ti = prep_push_word_arg(nscalw_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_SCHD_1PTHWIREBIT_NOMSG, 6, a5_ti, a4_ti, a3_ti, a2_ti,
    a1_ti, a0_ti);
 chk_callasl_arg_num(6);
}

extern void __emit_sched_scalar_1pthbit(int32 np_ti, int32 nscalw_ti,
 int32 oscalw_ti, int32 nchg_ti, int32 tevp_ti, int32 has_stren)
{ 
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;
 int32 call;

 a4_ti = prep_push_tn_addr_arg(tevp_ti);
 a3_ti = prep_push_tn_addr_arg(nchg_ti);
 a2_ti = prep_push_word_arg(oscalw_ti);
 /* sometimes nscalw is literal value as well */
 a1_ti = prep_push_word_arg(nscalw_ti);
 a0_ti = prep_push_word_arg(np_ti);

 if (has_stren)
  {
   call = ASL_SCHD_ST_SCALAR_1PTHWIREBIT;
  }
 else call = ASL_SCHD_SCALAR_1PTHWIREBIT;

 emit_call_asl_proc(call, 5, a4_ti, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(5);
}
 
#ifdef __CVC32__
extern void __emit_get_del32(int32 call, int32 *low_val_ti, int32 *high_val_ti, 
 int32 del_du_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(del_du_ti);
 emit_call_asl_proc(call, 1, a0_ti);
 chk_callasl_arg_num(1);
 *low_val_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 *high_val_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_DX);
}
#else
extern void __emit_get_del64(int32 call, int32 *val_ti, int32 del_du_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_word_arg(del_du_ti);
 emit_call_asl_proc(call, 1, a0_ti);
 chk_callasl_arg_num(1);
 *val_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
}
#endif

extern void __emit_schedule_scalar_1wev(int32 tevp_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_SCHD_SCALAR_1WEV, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_schedule_1wev(int32 tevp_ti, int32 biti_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(biti_ti);
 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_SCHD_1WEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

   
#ifdef __CVC32__

/* if (a < b) */
 /*
	movl	a, %eax
	movl	a+4, %edx
	cmpl	b+4, %edx
	ja	FALSE
	jb	TRUE
	cmpl	b, %eax
	jae	FALSE
        jmp	TRUE
    */
   //if (lastchg_time < pdlatechgtim) continue;
extern void  __emit_jmp_cmp64_idp_lessthan(struct bblk_t *t_bbp, 
 struct bblk_t *f_bbp, int32 a_low_ti, int32 a_high_ti, int32 b_low_ti, 
 int32 b_high_ti)
{
 struct bblk_t *jb_bbp, *jae_bbp;

 jb_bbp = __alloc_bblk(FALSE);
 jae_bbp = __alloc_bblk(FALSE);
 nores_insn(I_CMPL, AM_REG, b_high_ti, AM_NDXREG, a_high_ti);

 cond_jmp_insn(CC_JA, f_bbp, jb_bbp);
 __start_bblk(jb_bbp);

 cond_jmp_insn(CC_JB, t_bbp, jae_bbp);
 __start_bblk(jae_bbp);

 nores_insn(I_CMPL, AM_REG, b_low_ti, AM_NDXREG, a_low_ti);
 cond_jmp_insn(CC_JAE, f_bbp, t_bbp);
}


/* if (__newdel > __pdmindel) continue; */
/*
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	cmpl	__pdmindel+4, %edx
	jb	FALSE
	ja	TRUE
	cmpl	__pdmindel, %eax
	jbe	FALSE
*/
extern void __emit_jmp_cmp64_gt_pdmindel(struct bblk_t *t_bbp, 
 struct bblk_t *f_bbp, int32 newdel_low_ti, int32 newdel_high_ti)
{
 struct bblk_t *ja_bbp, *jbe_bbp;

 ja_bbp = __alloc_bblk(FALSE);
 jbe_bbp = __alloc_bblk(FALSE);
 nores_insn(I_CMPL, AM_NLO, NLO_PDMINDEL_HIGH, AM_REG, newdel_high_ti);

 cond_jmp_insn(CC_JB, f_bbp, ja_bbp);
 __start_bblk(ja_bbp);

 cond_jmp_insn(CC_JA, t_bbp, jbe_bbp);
 __start_bblk(jbe_bbp);

 nores_insn(I_CMPL, AM_NLO, NLO_PDMINDEL, AM_REG, newdel_low_ti);
 cond_jmp_insn(CC_JBE, f_bbp, t_bbp);
}



/* do a compare against __pdmindel where newdel is a known constant */
/* if (0xffffffff123ULL > a) */
/* if high value is not zero
  cmpl	$4095, a+4
  ja	FALSE
  jb	TRUE
  cmpl	$-3806, a
  ja	FALSE

  if high value is zero

  cmpl	$4095, a+4
  ja	FALSE
  cmpl	$-3806, a
  ja	FALSE
*/
extern void __emit_jmp_cmp64_gt_pdmindel_const(struct bblk_t *t_bbp, 
 struct bblk_t *f_bbp, int32 newdel_low_ti, int32 newdel_high_ti)
{
 struct bblk_t *jb_bbp, *ja_bbp;
 word32 hval;

 hval = __get_wrd_con_val(newdel_high_ti);
 /* if high value is constant don't need to compare JB */
 if (hval == 0) 
  {
   ja_bbp = __alloc_bblk(FALSE);
   nores_insn(I_CMPL, AM_REG, newdel_high_ti, AM_NLO, NLO_PDMINDEL_HIGH);

   cond_jmp_insn(CC_JA, f_bbp, ja_bbp);
  
   __start_bblk(ja_bbp);
   nores_insn(I_CMPL, AM_REG, newdel_low_ti, AM_NLO, NLO_PDMINDEL);
   cond_jmp_insn(CC_JA, f_bbp, t_bbp);
  }
 else
  {
   jb_bbp = __alloc_bblk(FALSE);
   ja_bbp = __alloc_bblk(FALSE);
   nores_insn(I_CMPL, AM_REG, newdel_high_ti, AM_NLO, NLO_PDMINDEL_HIGH);

   cond_jmp_insn(CC_JA, f_bbp, jb_bbp);
   __start_bblk(jb_bbp);

   cond_jmp_insn(CC_JB, t_bbp, ja_bbp);
   __start_bblk(ja_bbp);
  
   nores_insn(I_CMPL, AM_REG, newdel_low_ti, AM_NLO, NLO_PDMINDEL);
   cond_jmp_insn(CC_JA, f_bbp, t_bbp);
  }
}

/* if (__cvc_newdel <= __simtime) */
/*    (a <= b)
 	movl	a, %eax
	movl	a+4, %edx
	cmpl	b+4, %edx
	ja	FALSE
	jb	TRUE
	cmpl	b, %eax
	ja	FALSE
 */
extern void __emit_jmp_cmp64_newdel_lte_simtim(struct bblk_t *t_bbp,
 struct bblk_t *f_bbp, int32 new_low_ti, int32 new_high_ti)
{
 struct bblk_t *jb_bbp, *ja_bbp;

 jb_bbp = __alloc_bblk(FALSE);
 ja_bbp = __alloc_bblk(FALSE);
 nores_insn(I_CMPL, AM_NLO, NLO_SIMTIME_HIGH, AM_REG, new_high_ti);

 cond_jmp_insn(CC_JA, f_bbp, jb_bbp);
 __start_bblk(jb_bbp);

 cond_jmp_insn(CC_JB, t_bbp, ja_bbp);
 __start_bblk(ja_bbp);

 nores_insn(I_CMPL, AM_NLO, NLO_SIMTIME, AM_REG, new_low_ti);
 cond_jmp_insn(CC_JA, f_bbp, t_bbp);
}

extern void __emit_reschedule_1wev32(int32 tevp_ti, int32 time_low_ti, 
 int32 time_high_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(time_high_ti);
 a1_ti = prep_push_word_arg(time_low_ti);
 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_RESCHD_1WEV, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

#else
extern void __emit_reschedule_1wev64(int32 tevp_ti, int32 time_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(time_ti);
 a0_ti = prep_push_tn_addr_arg(tevp_ti);
 emit_call_asl_proc(ASL_RESCHD_1WEV, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}
#endif

extern void __emit_sched_1wirbit(int32 np_ti, int32 bi_ti, int32 nscalw_ti, 
 int32 oscalw_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 a4_ti = prep_push_tn_addr_arg(tevp_ti);
 a3_ti = prep_push_word_arg(oscalw_ti);
 a2_ti = prep_push_word_arg(nscalw_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_WDEL_SCHD_1WIREBIT, 5, a4_ti, a3_ti, a2_ti, a1_ti, 
  a0_ti);
 chk_callasl_arg_num(5);
}

extern void __emit_stren_sched_unknown_bit(int32 np_ti, int32 rhs_apti, 
 int32 oldsbp_ti, int32 nchg_ti, int32 tevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 a4_ti = prep_push_tn_addr_arg(tevp_ti);
 a3_ti = prep_push_tn_addr_arg(nchg_ti);
 a2_ti = prep_push_tn_addr_arg(oldsbp_ti);
 a1_ti = prep_push_word_arg(rhs_apti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_STREN_SCHED_UNKNOWN_BIT, 5, a4_ti, a3_ti, a2_ti, 
  a1_ti, a0_ti);
 chk_callasl_arg_num(5);
}

extern void __emit_sched_unknown_bit(int32 np_ti, int32 rhs_apti, 
 int32 tevp_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_tn_addr_arg(tevp_ti);
 a1_ti = prep_push_tn_addr_arg(rhs_apti);
 a0_ti = prep_push_word_arg(np_ti);
 emit_call_asl_proc(ASL_SCHED_UNKNOWN_BIT, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * this takes a literal value as the arg not a cint tn
 */
extern int32 __emit_todowniconn_inst(int32 inum)
{
 int32 r_ti, r2_ti, r3_ti;
 size_t offset;

 /*
  itp = get_itp_();
  itp = &(itp->in_its[inum]);
  return(itp->it_idp);
 */
 /* AIV 07/08/09 - fixed this - notice memory access can be done here */
 /* with only two moves was doing 3 for inum > 1 */
 r_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, MD_DOWNITPS*WRDBYTES);
 r2_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, r_ti);
 offset = (inum*sizeof(struct itree_t))+WRDBYTES;
 r3_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, r2_ti, offset);
 return(r3_ti);
}
/*
*/

/*
 * return the istance up idp
 */
extern int32 __emit_toupmdprt_inst(void)
{
 int32 r_ti;

 /* AIV 05/21/08 - has doing an unnecessary extra move here */
 r_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, MD_UPIDP*WRDBYTES);
 return(r_ti);
}

extern int32 __emit_ld_tfwarg_drvp(int32 npp_ti, int32 blen, int32 srep)
{
 int32 r_ti, a0_ti;

 a0_ti = prep_push_tn_addr_arg(npp_ti);
 emit_call_asl_func(ASL_LD_TFRWARG_DRVP, 1, a0_ti);
 chk_callasl_arg_num(1);
 r_ti = __move_srep_insn(TN_ADR, I_MOVA, srep, blen, AM_REG, AR_AX);
 return(r_ti);
}

extern void __emit_get_perinst_val(int32 cadrv_apti, int32 cadrvadr_ti, 
 int32 blen)
{
 int32 blen_ti, a0_ti, a1_ti, a2_ti;

 blen_ti = __gen_cint_tn(blen);
 a2_ti = prep_push_word_arg(blen_ti);
 a1_ti = prep_push_tn_addr_arg(cadrvadr_ti);
 a0_ti = prep_push_tn_addr_arg(cadrv_apti);
 emit_call_asl_proc(ASL_GET_PERINST_VAL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern int32 __emit_ld_logic_wide_driver(int32 gp_ti, int32 nins)
{
 int32 r_ti, a0_ti, a1_ti, cint_ti;

 cint_ti = __gen_cint_tn(nins);
 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_word_arg(gp_ti);
 emit_call_asl_func(ASL_LD_LOGIC_WIDE_DRIVER, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(r_ti);
}

extern void __emit_stren_comb_bits(int32 ntyp, int32 accum_sbpti, int32 abi1, 
 int32 abi2, int32 res_sbpti, int32 is_const)
{
 int32 abi2_ti, abi1_ti, ntyp_ti;
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti;

 if (is_const)
  {
   /* AIV 08/02/06 - if the range is only one bit use the one byte */
   /* this is needed because can't pass the one byte as an address */ 
   if (abi1 == abi2) 
    {
     /* if not the low byte do the adradd */
     if (abi1 != 0)
      {
       accum_sbpti = __con_adradd_insn(SR_SVEC, 1, accum_sbpti, abi1);
      }
     emit_comb_1bit_onebyte(ntyp, accum_sbpti, res_sbpti);
     return;
    }
   a4_ti = prep_push_tn_addr_arg(res_sbpti);
   abi2_ti = __gen_cint_tn(abi2);
   a3_ti = prep_push_word_arg(abi2_ti);
   abi1_ti = __gen_cint_tn(abi1);
   a2_ti = prep_push_word_arg(abi1_ti);
  }
 else
  {
   a4_ti = prep_push_tn_addr_arg(res_sbpti);
   a3_ti = prep_push_word_arg(abi2);
   a2_ti = prep_push_word_arg(abi1);
  }

 ntyp_ti = __gen_cint_tn(ntyp);
 a1_ti = prep_push_word_arg(ntyp_ti);

 a0_ti = prep_push_tn_addr_arg(accum_sbpti);

 /* SJM 04/20/07 - the one possible write ptr (value-return arg) must be */
 /* the first operand of asl wrapper call since reversed, last in list */
 emit_call_asl_proc(ASL_EVAL_STWIRE, 5, a4_ti, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(5);
}

/*
 * do the low bit version of asl_eval_stwire were bi and bi2 the same
 * accsbp[bi] = (byte) __comb_1bitsts(wtyp, (word32) accsbp[bi],
 *    (word32) sbp[bi2]);
 * AIV LOOKATME 07/26/06 - added this could be wrong
 */
static void emit_comb_1bit_onebyte(word32 ntyp, int32 accum_sbpti, 
 int32 sbpti)
{
 int32 am_type, r1_ti, r2_ti, ntyp_ti, a0_ti, a1_ti, a2_ti;

 am_type = get_1wrd_amtype(sbpti);
 r1_ti = __move_insn(TN_VAL, I_MOVZBL, am_type, sbpti); 
 a2_ti = prep_push_word_arg(r1_ti);

 am_type = get_1wrd_amtype(accum_sbpti);
 r2_ti = __move_insn(TN_VAL, I_MOVZBL, am_type, accum_sbpti); 
 a1_ti = prep_push_word_arg(r2_ti);

 ntyp_ti = __gen_cint_tn(ntyp);
 a0_ti = prep_push_word_arg(ntyp_ti);
 emit_call_asl_func(ASL_COMB_1BITSTS, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 am_type = get_1wrd_amtype(accum_sbpti);
 __st_insn(I_STOREB, AM_REG, AR_AX, am_type, accum_sbpti);
}

extern void __emit_comb_1w_nonstren(int32 a_apti, int32 d_apti, int32 d_bpti,
 int32 ntyp)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(d_bpti);
 a1_ti = prep_push_word_arg(d_apti);
 a0_ti = prep_push_tn_addr_arg(a_apti);
 switch ((byte) ntyp) {
  case N_WIRE: case N_TRI:
   /* know remaining bits must be x, neither and not the same */
   emit_call_asl_proc(ASL_EVAL_1W_NONSTREN_WIRE, 3, a2_ti, a1_ti, a0_ti);
   break;
  case N_TRIAND: case N_WA:
   /* if either 0, result 0, else x, since 1 1 done */ 
   emit_call_asl_proc(ASL_EVAL_1W_NONSTREN_WIRE_AND, 3, a2_ti, a1_ti, a0_ti);
   break;  
  case N_TRIOR: case N_WO:
   emit_call_asl_proc(ASL_EVAL_1W_NONSTREN_WIRE_OR, 3, a2_ti, a1_ti, a0_ti);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 chk_callasl_arg_num(3);
}

/* AIV 02/21/07 - comb wide was using np->nwid for length is pselwid */
/* SJM 04/26/07 - notice need drv b part since it width is not blen */
extern void __emit_comb_wide_nonstren(int32 a_apti, int32 d_apti, 
 int32 d_bpti, struct net_t *np, int32 blen)
{
 int32 wlen_ti, a0_ti, a1_ti, a2_ti, a3_ti;

 wlen_ti = __gen_cint_tn(wlen_(blen)); 
 a3_ti = prep_push_word_arg(wlen_ti);
 a2_ti = prep_push_tn_addr_arg(d_bpti);
 a1_ti = prep_push_tn_addr_arg(d_apti);
 a0_ti = prep_push_tn_addr_arg(a_apti);
 switch ((byte) np->ntyp) {
  case N_WIRE: case N_TRI:
   /* know remaining bits must be x, neither and not the same */
   emit_call_asl_proc(ASL_EVAL_WIDE_WIRE, 4, a3_ti, a2_ti, a1_ti, a0_ti);
   break;
  case N_TRIAND: case N_WA:
   /* if either 0, result 0, else x, since 1 1 done */ 
   emit_call_asl_proc(ASL_EVAL_WIDE_WIRE_AND, 4, a3_ti, a2_ti, a1_ti, a0_ti);
   break;  
  case N_TRIOR: case N_WO:
   emit_call_asl_proc(ASL_EVAL_WIDE_WIRE_OR, 4, a3_ti, a2_ti, a1_ti, a0_ti);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 chk_callasl_arg_num(4);
}

  /*
   * movzbl	__stren_map_tab(%eax), %eax
   * movzbl	%al, %eax
   */
extern int32 __emit_stren_map_tab(int32 t_ti)
{
 int32 r_ti, r2_ti; 

 /* AIV 12/17/07 - always need to do move here, if reg to reg will coal away */
 if (__tntab[t_ti].tn_typ == TN_ADR)
  {
   r_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, t_ti);
  }
 else r_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, t_ti);

 /* SJM 07/21/06 - for nlo objects that are accessed as glb array */
 /* need new special case amode */
 r2_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, r_ti, NLO_STREN_MAP_TAB); 
 return(r2_ti);
}

/*
 * AIV 11/02/06 - MFI address of accum is ALWAYS put into AR_AX
 */
extern int32 __emit_call_ldcomb_drvrs(struct net_t *np, int32 srep,
 struct mod_t *in_mdp)
{
 int32 val_ti, val_bpti;
 char *cp;
 char s1[RECLEN], nam[RECLEN];

 /* push first arg as address which is copied into result prior to ret */
 if (np->mfi_id == -1) np->mfi_id = ++(__inst_mod->mod_ndx_seq_no); 

 val_ti = -1;
 /* if wide or strength must use address */
 if (np->nwid > WBITS || np->srep == SR_SVEC)
  {
   val_ti = __gen_tn(srep, np->nwid);
   leal_insn(AM_REG, val_ti);
   /* AIV 11/03/06 - this is kind of a hack to put the result into AR_AX */
   /* should make a new move routine which always puts result into spec reg */
   __cur_bbp->itail->res_tni = AR_AX;
  }

 /* AIV 06/17/06 - added mod name to avoid conflicts */
 /* AIV 07/23/09 - these were causing conflicts in assembly cannot - use */
 /* [ or ] in name - just replace with a '_' */
 //AIV FIXME - remove this string - to some other ident
 strcpy(nam, np->nsym->synam);
 for (cp = nam; *cp != '\0'; cp++)
  {
   if (*cp == '[' || *cp == ']')
    *cp = '_';
  }
 sprintf(s1, "MFI.%s_%s", in_mdp->msym->synam, nam);
 nores_insn(I_CALL, AM_NONE, AM_LABEL, s1, np->mfi_id);
 /* if narrow return values in registers */
 if (val_ti == -1)
  {
   if (srep == SR_SCAL || srep == SR_SSCAL || srep == SR_SCAL2S)
    {
     val_ti = __move_srep_insn(TN_VAL, I_MOVA, srep, 1, AM_REG, AR_AX);
    }
   else
    {
     /* AIV BEWARE - values are now stored in AR_AX and bpart in AR_CX */
     if (srep == SR_BIT2S)
      {
       val_ti = __gen_tn(SR_BIT2S, np->nwid);
       __st_insn(I_STOREA, AM_REG, AR_AX, AM_REG, val_ti);
      }
     else
      {
       val_ti = __gen_tn(SR_VEC, np->nwid);
       __st_insn(I_STOREA, AM_REG, AR_AX, AM_REG, val_ti);
       val_bpti = __get_bpti(val_ti);
       __st_insn(I_STOREA, AM_REG, AR_CX, AM_REG, val_bpti);
      }
    }
  }
 return(val_ti);
}

extern void __emit_set_dce_rng(int32 ri1, int32 ri2, int32 is_const)
{
 int32 i1_ti, i2_ti;

 if (is_const) { i1_ti = __gen_cint_tn(ri1); i2_ti = __gen_cint_tn(ri2); }
 else { i1_ti = ri1; i2_ti = ri2; } 
 /* SJM 12/04/07 - now can directory store into nlo memory addrs */
 __st_insn(I_STOREA, AM_REG, i1_ti, AM_NLO, NLO_NCHGED_I1);
 __st_insn(I_STOREA, AM_REG, i2_ti, AM_NLO, NLO_NCHGED_I2);
}

extern void __emit_exec_enter_dce(struct net_t *np)
{
 int32 ndx;
 struct task_t *in_tskp;
 struct mod_t *in_mdp;
 char s1[RECLEN];

 in_mdp = __find_mod_task_of_var(np, &(in_tskp));
 sprintf(s1, "DCE_%d", in_mdp->m_idnum);
 ndx = np - in_mdp->mnets; 
 nores_insn(I_CALL, AM_NONE, AM_LABEL, s1, ndx);
}

extern void __emit_exec_enter_npp(struct net_t *np)
{
 int32 ndx;
 struct task_t *in_tskp;
 struct mod_t *in_mdp;
 char s1[RECLEN];

 in_mdp = __find_mod_task_of_var(np, &(in_tskp));
 sprintf(s1, "NPP_%d", in_mdp->m_idnum);
 ndx = np - in_mdp->mnets; 
 nores_insn(I_CALL, AM_NONE, AM_LABEL, s1, ndx);
}


/*
 *
 */
extern void __emit_call_mdprt_bsel(int32 up_lhsx_ti, int32 lhs_ti,
 int32 new_val_ti, int32 all_bsel_1w)
{
 int32 a0_ti, a1_ti, a2_ti; 
 
 a2_ti = prep_push_word_arg(new_val_ti);
 a1_ti = prep_push_word_arg(lhs_ti);
 a0_ti = prep_push_word_arg(up_lhsx_ti);
 if (all_bsel_1w)
  {
   emit_call_asl_proc(ASL_MDPRT_BSEL_1W, 3, a2_ti, a1_ti, a0_ti);
  }
 else
  {
   emit_call_asl_proc(ASL_MDPRT_BSEL, 3, a2_ti, a1_ti, a0_ti);
  }
 chk_callasl_arg_num(3);
}

extern void __emit_call_mdprt_bsel_nchg(int32 up_lhsx_ti, int32 lhs_ti,
 int32 new_val_ti, int32 nchg_ti, int32 all_bsel_1w)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti; 
 
 a3_ti = prep_push_word_arg(nchg_ti);
 a2_ti = prep_push_word_arg(new_val_ti);
 a1_ti = prep_push_word_arg(lhs_ti);
 a0_ti = prep_push_word_arg(up_lhsx_ti);
 if (all_bsel_1w)
  {
   emit_call_asl_proc(ASL_MDPRT_BSEL_NCHG_1W, 4, a3_ti, a2_ti, a1_ti, a0_ti);
  }
 else
  {
   emit_call_asl_proc(ASL_MDPRT_BSEL_NCHG, 4, a3_ti, a2_ti, a1_ti, a0_ti);
  }
 chk_callasl_arg_num(4);
}

extern void __emit_call_mdprt_bsel_dmpv(int32 up_lhsx_ti, int32 lhs_ti,
 int32 new_val_ti, int32 all_bsel_1w, int32 is_dump_ports, int32 np_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti; 
 
 if (all_bsel_1w)
  {
   a3_ti = prep_push_word_arg(np_ti);
   a2_ti = prep_push_word_arg(new_val_ti);
   a1_ti = prep_push_word_arg(lhs_ti);
   a0_ti = prep_push_word_arg(up_lhsx_ti);
   if (is_dump_ports)
    {
     emit_call_asl_proc(ASL_MDPRT_BSEL_1W_DMPP, 4, a3_ti, a2_ti, a1_ti, a0_ti);
    }
   else 
    {
     emit_call_asl_proc(ASL_MDPRT_BSEL_1W_DMPV, 4, a3_ti, a2_ti, a1_ti, a0_ti);
    }
   chk_callasl_arg_num(4);
  }
 else
  {
   a2_ti = prep_push_word_arg(new_val_ti);
   a1_ti = prep_push_word_arg(lhs_ti);
   a0_ti = prep_push_word_arg(up_lhsx_ti);
   if (is_dump_ports)
    {
     emit_call_asl_proc(ASL_MDPRT_BSEL_DMPP, 3, a2_ti, a1_ti, a0_ti);
    }
   else emit_call_asl_proc(ASL_MDPRT_BSEL_DMPV, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
  }
}

extern void __emit_call_mdprt_bsel_nchg_dmpv(int32 up_lhsx_ti, int32 lhs_ti,
 int32 new_val_ti, int32 nchg_ti, int32 all_bsel_1w, int32 is_dump_ports, 
 int32 np_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti; 
 
 if (all_bsel_1w)
  {
   a4_ti = prep_push_word_arg(np_ti);
   a3_ti = prep_push_word_arg(nchg_ti);
   a2_ti = prep_push_word_arg(new_val_ti);
   a1_ti = prep_push_word_arg(lhs_ti);
   a0_ti = prep_push_word_arg(up_lhsx_ti);
   if (is_dump_ports)
    {
     emit_call_asl_proc(ASL_MDPRT_BSEL_NCHG_1W_DMPP, 5, a4_ti, a3_ti, a2_ti, 
      a1_ti, a0_ti);
    }
   else
    {
     emit_call_asl_proc(ASL_MDPRT_BSEL_NCHG_1W_DMPV, 5, a4_ti, a3_ti, a2_ti, 
      a1_ti, a0_ti);
    }
   chk_callasl_arg_num(5);
  }
 else
  {
   a3_ti = prep_push_word_arg(nchg_ti);
   a2_ti = prep_push_word_arg(new_val_ti);
   a1_ti = prep_push_word_arg(lhs_ti);
   a0_ti = prep_push_word_arg(up_lhsx_ti);
   if (is_dump_ports)
    {
     emit_call_asl_proc(ASL_MDPRT_BSEL_NCHG_DMPP, 4, a3_ti, a2_ti, a1_ti, 
      a0_ti);
    }
   else 
    {
     emit_call_asl_proc(ASL_MDPRT_BSEL_NCHG_DMPV, 4, a3_ti, a2_ti, a1_ti, 
      a0_ti);
    }
   chk_callasl_arg_num(4);
  }
}

extern void __emit_exec_call_nchg_fg(int32 ndx, int32 var_ti)
{
 int32 am_type;

 /* AIV 09/06/07 - BEWARE variable cases passes index into AR_AX */
 /* this is fine becuase it is a call eax is known not to be save across call */
 if (var_ti != -1)
  {
   am_type = get_1wrd_amtype(var_ti);
   __st_insn(I_STOREA, am_type, var_ti, AM_REG, AR_AX);
  }

 /* AIV 07/07/09 - got rid of the need for a string here */
 nores_insn(I_FG_CALL, AM_IMM, FG_NCHG, AM_IMM, ndx);
}

/* AIV 09/06/07 - BEWARE arg must now be loaded always passed in AR_AX */ 
extern int32 __ld_nchg_var_ndx(void)
{
 int32 var_ti;

 var_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(var_ti);
}

/*
 * load a np->nchgaction address
 */
extern int32 __emit_ld_nchg_bptr(struct net_t *np)
{
 int32 nchg_ti;

 /* DBG remove -- */
 if (np->nchgaction_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */

 /* AIV FIXME ???? if (__need_net_addr) __misc_terr(__FILE__, __LINE__); */

 /* AIV 08/13/07 - handle the design wide case */
 nchg_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti,
  np->nchgaction_ofs*WRDBYTES);
 __tntab[nchg_ti].idp_typ = COMLAB_NCHGACTION;
 return(nchg_ti);
}

extern int32 __gen_process_nchg(struct net_chg_t *ncp)
{
 int32 nchg_ti;
 struct tn_t *tnp;
 int32 tni;

 /* DBG remove -- */
 if (ncp->ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 
 /* if only one module better to just use the $nchgdat address literal value */
 if (__inst_mod->flatinum == 1)
  {
   tni = __gen_tn(SR_MODADR, 0);
   tnp = &(__tntab[tni]);
   tnp->comlab_typ = COMLAB_PNCHG;
   tnp->tncu.el_ndx = ncp->ndx;
   tnp->tn_typ = TN_ADR;
   tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
   tnp->tnsyrecp->in_mdp = __inst_mod;
   return(tni);
  }
 /* DBG remove -- */
 if (ncp->nchg_idp_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 nchg_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti,
  ncp->nchg_idp_ofs*WRDBYTES);
 __tntab[nchg_ti].idp_typ = COMLAB_PNCHG;
 return(nchg_ti);
}

/*
 * move nchg into a register
 */
extern int32 __gen_process_nchg_to_reg_tn(struct net_chg_t *ncp)
{
 int32 nchg_ti, r1_ti;

 nchg_ti = __gen_process_nchg(ncp);
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, nchg_ti);
 return(r1_ti); 
}

extern int32 __gen_ctevp_adr_tn(struct ctev_t *ctevp)
{
 int32 tev_ti;
 struct tn_t *tnp;
 int32 tni;

 /* DBG remove -- */
 if (ctevp->ctev_ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* ------ */

 /* if only one module better to just use the $nchgdat address literal value */
 if (__inst_mod->flatinum == 1)
  {
   tni = __gen_tn(SR_MODADR, 0);
   tnp = &(__tntab[tni]);
   tnp->comlab_typ = COMLAB_TEVP;
   tnp->tncu.el_ndx = ctevp->ctev_ndx;
   tnp->tn_typ = TN_ADR;
   tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
   tnp->tnsyrecp->in_mdp = __inst_mod;
   return(tni);
  }
 /* DBG remove -- */
 if (ctevp->ctev_idp_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */

 tev_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti,
  ctevp->ctev_idp_ofs*WRDBYTES);
 __tntab[tev_ti].idp_typ = COMLAB_TEVP;
 return(tev_ti);
}

extern int32 __gen_ctevp_trigger_flag(int32 ctevp_reg_ti)
{
 struct tev_t *tevp;
 int32 r1_ti, r2_ti;
 size_t offset;

 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 r1_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, ctevp_reg_ti);
 r2_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, r1_ti, offset);
 return(r2_ti);
}

/*
 * get the nchgp->triggered flag
 */
/*
 * get the nchgp->triggered flag
 */
extern int32 __gen_nchg_trigger(int32 nchg_ti)
{
 struct nchglst_t *nchgp;
 int32 r1_ti;
 size_t offset;

 /* DBG remove -- */
 nchgp = &__nchg_dummy_hd;
 offset = (byte *) &(nchgp->triggered) - (byte *) nchgp;
 if (offset != 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 r1_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, nchg_ti);
 return(r1_ti);
}

extern void __emit_add_static_nchglst_sel(int32 dat_ti, int32 i1_ti, 
 int32 i2_ti)
{
 int32 a0_ti, a1_ti, a2_ti; 
 
 /* AIV 10/16/06 - ranges were swapped */
 a2_ti = prep_push_word_arg(i2_ti);
 a1_ti = prep_push_word_arg(i1_ti);
 a0_ti = prep_push_word_arg(dat_ti);
 emit_call_asl_proc(ASL_ADD_STATIC_NCHG_SEL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_add_dmpvlst(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_ADD_DMPV_CHGLST_EL, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_add_dmpvlst_array(int32 np_ti, int32 biti_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(biti_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_ADD_DMPV_CHGLST_EL_ARRAY, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_add_dmpvlst_mdprt(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_ADD_DMPV_CHGLST_EL_MDPRT, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_add_dmpportlst(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_ADD_DMPP_CHGLST_EL, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_add_dmpportlst_mdprt(int32 np_ti)
{
 int32 a0_ti;

 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_ADD_DMPP_CHGLST_EL_MDPRT, 1, a0_ti);
 chk_callasl_arg_num(1);
}

/*
 * add a net to the toggle list
 */
extern void __emit_add_togglelst_el(int32 np_ti)
{
 int32 a0_ti;

 /* SJM 06-30-13 - need this on at compile time to init right */
 __cvc_slotend_action |= SE_TOGGLE;
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_ADD_TOGGLELST_EL, 1, a0_ti);
 chk_callasl_arg_num(1);
}

/*
 * add a net to the toggle list - port version
 */
extern void __emit_add_togglelst_el_port(int32 np_ti)
{
 int32 a0_ti;

 __cvc_slotend_action |= SE_TOGGLE;
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_ADD_TOGGLELST_EL_PORT, 1, a0_ti);
 chk_callasl_arg_num(1);
}

extern void __emit_store_cint(int32 op1_ti, int32 val, int32 bytsiz)
{
 if (val == 0) lower_setbytes(op1_ti, 0, bytsiz);
 else
  {
   if (bytsiz <= WRDBYTES) lower_setbytes(op1_ti, val, bytsiz);
   else
    {
     lower_setbytes(op1_ti, 0, bytsiz);
     lower_setbytes(op1_ti, val, WRDBYTES);
    }
  }
}

extern void __emit_setall1(int32 op1_ti, int32 nbytes)
{
 /* now 2nd operand of insn is number of bytes to set */ 
 /* notice caller handles any needed high word unused bits masking to 0 */
 lower_setbytes(op1_ti, 0xff, nbytes);
}

#ifdef __CVC32__
extern void __emit_setr0(int32 r_ti)
{
 nores_insn(I_FLDZ, AM_NONE, AM_NONE);
 nores_insn(I_FSTPL, AM_NONE, AM_REG, r_ti);
}
#else
extern void __emit_setr0(int32 r_ti)
{
 int32 cint_ti;

 cint_ti = __gen_cint_tn(0);
 __st_insn(I_STOREQ, AM_REG, cint_ti, AM_REG, r_ti);
}
#endif

/* AIV LOOKATME - maybe check for valid strength values ???? */

extern void __emit_setstren(int32 sbp_ti, int32 sval, int32 blen)
{
 int32 blen_ti, sval_ti, a0_ti, a1_ti, a2_ti; 
 int32 i, bi, cint_ti, sbpw_ti, assign_last_word, wbytes;
 word32 wrdval, wsval;

 /* AIV 11/04/08 - must eval in word context not int */
 wsval = sval;
 /* AIV 07/10/08 - if setstren for under 8 words inline */
 /* setbyte of 2 for 8 bytes now become two moves */
 /* movl	$0x2020202, -44(%ebp) movl	$0x2020202, -40(%ebp) */
 if (blen <= (WRDBYTES*8))
  {
   wbytes = 0;
   bi = 1;
   /* wrdval is the word value */
   wrdval = wsval;
   assign_last_word = TRUE;
   for (i = 1; i <= blen; i++)
    {
     assign_last_word = TRUE;
     /* align on word do the actual assign */
     if ((i % WRDBYTES) == 0) 
      {
       if (i > WRDBYTES)
        {
         sbpw_ti = __con_adradd_insn(SR_SVEC, WBITS, sbp_ti, wbytes);
        }
       else sbpw_ti = sbp_ti;
       cint_ti = __gen_cint_tn(wrdval);
//AIV64 - better to just use movl????
      /* if constant is wide must do the load of constant into reg */
#ifndef __CVC32__
      if (wrdval >= 0xfffffff) 
       {
        cint_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, cint_ti);
       }
#endif
       __st_insn(I_STOREL, AM_REG, cint_ti, AM_REG, sbpw_ti);
       bi = 1;
       wrdval = wsval;
       wbytes += WRDBYTES;
       continue;
      }
     wrdval |= (wsval << (bi*8));
     bi++;
    }

   if (assign_last_word) 
    {
     if (i > WRDBYTES)
      {
       sbpw_ti = __con_adradd_insn(SR_SVEC, WBITS, sbp_ti, wbytes);
      }
     else sbpw_ti = sbp_ti;
     cint_ti = __gen_cint_tn(wrdval);
//AIV64 - better to just use movl????
      /* if constant is wide must do the load of constant into reg */
#ifndef __CVC32__
      if (wrdval >= 0xfffffff) 
       {
        cint_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, cint_ti);
       }
#endif
     __st_insn(I_STOREL, AM_REG, cint_ti, AM_REG, sbpw_ti);
    }
   return;
  }
 
 blen_ti = __gen_cint_tn(blen);
 a2_ti = prep_push_word_arg(blen_ti);
 /* SJM 07/19/06 - was not passing sval to make the sval cint tn */
 sval_ti = __gen_cint_tn(sval);
 a1_ti = prep_push_word_arg(sval_ti);
 a0_ti = prep_push_tn_addr_arg(sbp_ti);
 emit_call_asl_proc(ASL_SET_BYTEVAL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern int32 __emit_random_with_seed(int32 seed_ti)
{
 int32 a0_ti, val_ti;

 a0_ti = prep_push_tn_addr_arg(seed_ti);
 emit_call_asl_proc(ASL_RANDOM_WITH_SEED, 1, a0_ti);
 chk_callasl_arg_num(1);
 /* AIV 11/04/08 - notice random is always 32-bits defined by LRM */
 /* AIV 08/26/10 - these are zero b part aka 2-state */
 val_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, INTBITS, AM_REG, AR_AX);
 return(val_ti);
}

extern int32 __emit_random(void)
{
 int32 val_ti;

 emit_call_asl_proc(ASL_RANDOM, 0);
 /* AIV 08/26/10 - these are zero b part aka 2-state */
 val_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, INTBITS, AM_REG, AR_AX);
 return(val_ti);
}

/* AIV 09/13/10 - this built in libc math functions should just be called */
extern int32 __emit_1arg_transcendental(int32 dbl_ti, int32 asl_typ)
{
 int32 res_ti, a0_ti;

 res_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[res_ti].t_real = TRUE;
 __tntab[res_ti].tn_used_wide = TRUE; 

 a0_ti = prep_push_real_arg(dbl_ti);
 emit_call_asl_func(asl_typ, 1, a0_ti);
 chk_callasl_arg_num(2);
#ifdef __CVC32__
 nores_insn(I_FSTPL, AM_NONE, AM_REG, res_ti);
#else
 /* 64-bit gets result from xmm0 */
 nores_insn(I_STREAL, AM_NONE, AM_REG, res_ti);
#endif
 return(res_ti);
}

extern void __emit_rhs_psel_wide(int32 resadr_ti, int32 resadr_bpti, 
 int32 nadr_ti, int32 nadr_bpti, int32 bitl_ti, int32 numbits_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, a4_ti, a5_ti;

 a5_ti = prep_push_word_arg(numbits_ti);
 a4_ti = prep_push_word_arg(bitl_ti);
 a3_ti = prep_push_tn_addr_arg(nadr_bpti);
 a2_ti = prep_push_tn_addr_arg(nadr_ti);
 a1_ti = prep_push_tn_addr_arg(resadr_bpti);
 a0_ti = prep_push_tn_addr_arg(resadr_ti);
 emit_call_asl_func(ASL_RHS_PSEL_WIDE, 6, a5_ti, a4_ti, a3_ti, a2_ti, a1_ti, 
  a0_ti);
 chk_callasl_arg_num(6);
}

extern void __emit_rhs_psel_wide_2state(int32 resadr_ti, int32 nadr_ti, 
 int32 bitl_ti, int32 numbits_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti;

 a3_ti = prep_push_word_arg(numbits_ti);
 a2_ti = prep_push_word_arg(bitl_ti);
 a1_ti = prep_push_tn_addr_arg(nadr_ti);
 a0_ti = prep_push_tn_addr_arg(resadr_ti);
 emit_call_asl_func(ASL_RHS_PSEL_WIDE_2STATE, 4, a3_ti, a2_ti, a1_ti, 
  a0_ti);
 chk_callasl_arg_num(4);
}

extern int32 __emit_rhs_psel(int32 nadr_ti, int32 nadr_bpti, int32 bitl_ti, 
 int32 numbits_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, val_ti;

 a3_ti = prep_push_word_arg(numbits_ti);
 a2_ti = prep_push_word_arg(bitl_ti);
 a1_ti = prep_push_tn_addr_arg(nadr_bpti);
 a0_ti = prep_push_tn_addr_arg(nadr_ti);
 emit_call_asl_proc(ASL_RHS_PSEL, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 val_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(val_ti);
}

extern int32 __emit_rhs_psel_2state(int32 nadr_ti, int32 bitl_ti, 
 int32 numbits_ti)
{
 int32 a0_ti, a1_ti, a2_ti, val_ti;

 a2_ti = prep_push_word_arg(numbits_ti);
 a1_ti = prep_push_word_arg(bitl_ti);
 a0_ti = prep_push_tn_addr_arg(nadr_ti);
 emit_call_asl_proc(ASL_RHS_PSEL_2STATE, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
 val_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_AX);
 return(val_ti);
}
   
extern void __emit_rhs_st_psel(int32 res_apti, int32 addr_ti, int32 numbits_ti)
{
 int32 a0_ti, a1_ti, a2_ti;

 a2_ti = prep_push_word_arg(numbits_ti);
 a1_ti = prep_push_tn_addr_arg(addr_ti);
 a0_ti = prep_push_tn_addr_arg(res_apti);
 emit_call_asl_func(ASL_RHS_ST_PSEL, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

extern void __emit_suspend(void)
{
 int32 true_ti;

 if (!__needs_thread_ctrl) 
  {
   nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
   nores_insn(I_NEXT_EVENT, AM_NONE, AM_NONE);
  }
 else
  {
   true_ti = __gen_cint_tn(TRUE);
   __st_insn(I_STOREA, AM_REG, true_ti, AM_NLO, NLO_STMT_SUSPEND);
   nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
  }
 nores_insn(I_SUSPEND, AM_NONE, AM_NONE);
}

extern void __emit_complete(void)
{
 if (!flowg_jumps_to_next_event(__cur_flowg->flowgtyp))
  {
   nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
   nores_insn(I_COMPLETE, AM_NONE, AM_NONE);
  }
 else if(__needs_thread_ctrl)
  {
   nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
   nores_insn(I_COMPLETE, AM_NONE, AM_NONE);
  }
 else
  {
   nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
   nores_insn(I_NEXT_EVENT, AM_NONE, AM_NONE);
   nores_insn(I_COMPLETE, AM_NONE, AM_NONE);
  }
}

/* 
 * return TRUE if flow graphs needs a jump to the next event
 */
static int32 flowg_jumps_to_next_event(int32 flowgtyp)
{
 switch (flowgtyp) {
  case FLOWG_DCE: case FLOWG_NPP: case FLOWG_ICONN: case FLOWG_CONTA:
  case FLOWG_GATECA: case FLOWG_FUNC: case FLOWG_TASK:
  case FLOWG_MULTFI: case FLOWG_NCHG: case FLOWG_PROCESS_NCHG:
   return(FALSE);
  }
 return(TRUE);
}

extern void __emit_next_event(void)
{
 nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
 nores_insn(I_NEXT_EVENT, AM_NONE, AM_NONE);
}

extern void __emit_next_nchg_event(void)
{
 nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
 nores_insn(I_NEXT_NCHG_EVENT, AM_NONE, AM_NONE);
}

extern void __emit_leave(void)
{
 nores_insn(I_EPILOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_proc(struct st_t *stp) 
{
 int32 ndx;

 ndx = stp->st_ndx;
 /* DBG remove -- */
 if (!stp->is_enter) __misc_terr(__FILE__, __LINE__);
 if (ndx < 0 || ndx > __inst_mod->mstnum) __misc_terr(__FILE__, __LINE__);
 /* --- */
 stp->enter_created = TRUE;
 nores_insn(I_ENTER_PROC, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_mdc(int32 ndx) 
{
 /* DBG remove -- */
 if (ndx < 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_MDC, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_nb_proc(struct st_t *stp) 
{
 int32 ndx;

 ndx = stp->st_ndx;
 /* DBG remove -- */
 if (!stp->is_nb_enter) __misc_terr(__FILE__, __LINE__);
 if (ndx < 0 || ndx > __inst_mod->mstnum) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_NB_PROC, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_nb_proc_free(struct st_t *stp) 
{
 int32 ndx;

 ndx = stp->st_ndx;
 /* DBG remove -- */
 if (!stp->is_nb_enter) __misc_terr(__FILE__, __LINE__);
 if (ndx < 0 || ndx > __inst_mod->mstnum) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_NB_PROC_FREE, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

//  case I_ENTER_THD_RET: 
//  case I_DSA_BRK_LABEL: 
//AIV? - since in same file maybe DSA BRK LABEL can be simple
/* this is the task ndx number */
extern void __emit_enter_thd_ret(int32 ndx) 
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_THD_RET, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_decl(struct net_t *np)
{
 int32 ndx;

 ndx = np - __inst_mod->mnets;
 /* DBG remove -- */
 if (ndx < 0 || ndx > __inst_mod->mtotvarnum) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* SJM 08/22/06 - this is really DCE processing */
 nores_insn(I_ENTER_DECL, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_npp(struct net_t *np)
{
 int32 ndx;

 ndx = np - __inst_mod->mnets;
 /* DBG remove -- */
 if (ndx < 0 || ndx > __inst_mod->mtotvarnum) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_NPP, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_mipd(int32 ndx)
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_MIPD, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_multfi_subr(int32 ndx, struct net_t *np,
 struct mod_t *in_mdp)
{
 char *cp;
 char s1[RECLEN], nam[RECLEN];

 /* AIV 06/17/06 - added mod name to avoid conflicts */
 /* AIV 07/23/09 - these were causing conflicts in assembly cannot - use */
 /* [ or ] in name - just replace with a '_' */
 //AIV FIXME - remove this string - to some other ident
 strcpy(nam, np->nsym->synam);
 for (cp = nam; *cp != '\0'; cp++)
  {
   if (*cp == '[' || *cp == ']')
    *cp = '_';
  }
 
 sprintf(s1, "MFI.%s_%s", in_mdp->msym->synam, nam);
 nores_insn(I_MULTFI_SUBR, AM_NONE, AM_LABEL, s1, ndx);
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_conta(int32 ndx)
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_CAP, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_call_conta(struct conta_t *cap)
{
 /* AIV 07/07/09 - got rid of the need for a string here */
 nores_insn(I_FG_CALL, AM_IMM, FG_CAP, AM_IMM, cap->enter_cndx);
}

extern void __emit_enter_iconn(int32 ndx)
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_ICONN, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_port(int32 ndx)
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_PORT, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_call_iconn(int32 iconn_ndx)
{
 /* AIV 07/07/09 - got rid of the need for a string here */
 nores_insn(I_FG_CALL, AM_IMM, FG_ICONN, AM_IMM, iconn_ndx);
}

extern void __emit_call_gate_conta(int32 gc_ndx)
{
 /* AIV 07/07/09 - got rid of the need for a string here */
 nores_insn(I_FG_CALL, AM_IMM, FG_GATECA, AM_IMM, gc_ndx);
}

extern void __emit_enter_gate_conta(int32 gc_ndx)
{
 /* DBG remove -- */
 if (gc_ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_GATECA, AM_NONE, AM_IMM, gc_ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_net_chg(int32 ndx)
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_NCHG, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_process_enter_net_chg(int32 ndx)
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_PROCESS_NCHG, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_process_enter_wire_ev(int32 ndx)
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_WIRE_EV, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}
     
extern void __emit_process_trpthdst_enter(int32 ndx)
{
 /* DBG remove -- */
 if (ndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_TRPTH_EV, AM_NONE, AM_IMM, ndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

extern void __emit_enter_gate_delay_assign(int32 gndx)
{
 /* DBG remove -- */
 if (gndx == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 nores_insn(I_ENTER_GATEDA, AM_NONE, AM_IMM, gndx); 
 nores_insn(I_PROLOGUE, AM_NONE, AM_NONE);
}

/*
 *
 * AIV IDP FIXME CVC - this can probably be loaded once per module
 * like __idp - may have to be reloaded leaving for now
 */
extern int32 __emit_inum(void)
{
 int32 inum_ti;

 /* DBG remove -- */
 if (MD_INUM != 0) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 inum_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, __idp_ti);
 return(inum_ti);
}
  
///////////////////////////////
//AIV REMOVEME - need to fix port code
extern int32 __emit_dbg_inum(void)
{
 int32 inum_ti, r_ti;

 /* DBG remove -- */
 if (MD_INUM != 0) __misc_terr(__FILE__, __LINE__);
 /* ----- */
 r_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, IDP_REG);
 inum_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, r_ti);
 return(inum_ti);
}
///////////////////////////////
   

/* 
 * AIV 11/02/06 - only used for MFI where address is put into AR_AX
 */
extern int32 __emit_save_arg(void)
{
 int32 r1_ti;

 /* AIV 11/02/06 - MFI address of accum is ALWAYS put into AR_AX */
 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(r1_ti);
}

/* just a regular copy but have a diffent insn to distinguish */
extern void __copy_arg(int32 nbytes, int32 op1, int32 op2)
{
 copy_insn(op1, op2, nbytes);
}

/* 
 * set the current __idp/idp_reg(esi) 
 */
extern void __memloc_emit_set_idp(int32 new_idp_ti)
{
 int32 amode;
 struct tn_t *tnp;

 /* AIV 11/0/07 - when setting the idp need to inc the val number tracking */
 /* the new lowered tran code sets (changes the idp) and can assign to the */
 /* same value offsets - was removing store isns after idp changed */
 /* 
   movl	$0x82d6d20, %esi
   movb	%bl, 29(%esi)
   movl	$0x82d6ca0, %esi
   movb	%bl, 29(%esi) #was removing this store need this store becuase
   esi has changed
 */
 tnp = &(__tntab[new_idp_ti]);
 /* AIV 05/21/08 - if UPIDP fixed location off idp it is an AM_NDXREG */
 if (tnp->tag_parent_tni == __idp_ti
     && tnp->child_tag_offset == (WRDBYTES*MD_UPIDP)) 
  {
   amode = AM_NDXREG;
  }
 else amode = AM_REG;

 __enter_bblk_valnum = ++__cur_valnum;
 __st_insn(I_STOREA, amode, new_idp_ti, AM_REG, IDP_REG);
//AIV need to set __idp also?????????
//AIV FIXME - could see from the generated code if any wrappers reachable
//AIV 01/04/08 - now all wrappers set __idp from %esi
//from there need __idp global - if not would need to set
// __st_insn(I_STOREA, AM_REG, IDP_REG, AM_NLO, NLO_IDP);
}

/* 
 * save the pointer value idp not the current idp
 */
extern int32 __emit_save_idp(int32 idp_ti)
{
 int32 r1_ti;

 r1_ti = __gen_tn(SR_CINT, WBITS);
 __st_insn(I_STOREA, AM_REG, idp_ti, AM_REG, r1_ti);
 return(r1_ti);
}

extern int32 __emit_save_downidp(int32 idp_ti)
{
 int32 r1_ti;

 r1_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, idp_ti);
 return(r1_ti);
}

/*
 * save the current __idp (ESI) 
 */
extern int32 __emit_save_cur_idp(void)
{
 int32 r1_ti;

 r1_ti = __gen_tn(SR_CINT, WBITS);
 /* AIV 04/14/10 - this needs to be an address for wrapper passing for */
 /* new automatic code - 64-bit */
 __tntab[r1_ti].tn_typ = TN_ADR; 
 __st_insn(I_STOREA, AM_REG, IDP_REG, AM_REG, r1_ti);
 return(r1_ti);
}

/*
 * return a new copied idp area
 */
extern int32 __emit_new_auto_idp_area(int32 idp_ti)
{
 int32 a0_ti, new_idp_ti;

 a0_ti = prep_push_word_arg(idp_ti);
 emit_call_asl_proc(ASL_NEW_AUTO_IDP_AREA, 1, a0_ti);
 chk_callasl_arg_num(1);
 new_idp_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(new_idp_ti);
}

/*
 * copy back idp area for an automatic function
 */
extern void __emit_cp_auto_idp_area_func(int32 dst_ti, int32 src_ti)
{
 int32 a0_ti, a1_ti;

 a1_ti = prep_push_word_arg(src_ti);
 a0_ti = prep_push_word_arg(dst_ti);
 emit_call_asl_proc(ASL_CP_AUTO_IDP_AREA_FUNC, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

extern void __emit_return(void)
{
 nores_insn(I_RETURN, AM_NONE, AM_NONE);
}

#ifdef __CVC32__
/*
 * generate simple real binary op
 * 
 *	fldl	M_add_a
 *	faddl	M_add_b
 *	fstpl	-20(%ebp)
 */
static int32 emit_real_binop(int32 opcod, int32 op1_ti, int32 op2_ti)
{
 int32 am_type, res_ti;

//AIV LOOKATME - isn't this suppose to be 64-bit must be trumped by t_real
//since it must work
 res_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[res_ti].t_real = TRUE;
 /* SJM 08/27/06 - mark real as wide since halves non separable */
 __tntab[res_ti].tn_used_wide = TRUE; 

 am_type = get_1wrd_amtype(op1_ti);
//SJM? - treating fldl as a load/store so can have ndx reg src op
 nores_insn(I_FLDL, AM_NONE, am_type, op1_ti);

 am_type = get_1wrd_amtype(op2_ti);
 nores_insn(opcod, AM_NONE, am_type, op2_ti);

 nores_insn(I_FSTPL, AM_NONE, AM_REG, res_ti);
 return(res_ti);
}
#else
/*
 * generate simple real binary op
 *  a = a +b
 * 
 *	movsd	M_add_a, %xmm0
 *	movsd   M_add_b, %xmm1
 *	addsd	%xmm1, %xmm0
 *	movsd	%xmm0, M_add_a 
 */
static int32 emit_real_binop(int32 opcod, int32 op1_ti, int32 op2_ti)
{
 int32 am_type, res_ti;

 res_ti = __gen_tn(SR_VEC, WBITS);
 __tntab[res_ti].t_real = TRUE;
 __tntab[res_ti].tn_used_wide = TRUE; 

 am_type = get_1wrd_amtype(op1_ti);
 nores_insn(I_LDR1, AM_NONE, am_type, op1_ti);

 am_type = get_1wrd_amtype(op2_ti);
 nores_insn(I_LDR2, AM_NONE, am_type, op2_ti);

 nores_insn(opcod, AM_NONE, AM_NONE);

 nores_insn(I_STREAL, AM_NONE, AM_REG, res_ti);
 return(res_ti);
}
#endif

/*
 * lower a real compare
 * AIV FIXME - optimize like gcc ???? plus this code is kind of ugly
 */
#ifdef __CVC32__
static void emit_real_cmp(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti,int32 cc)
{
 int32 am_type, am2_type;

 /* load op1 and op2 to compare */
 am_type = get_1wrd_amtype(op1_ti);
 am2_type = get_1wrd_amtype(op2_ti);
 nores_insn(I_FLDL, AM_NONE, am_type, op1_ti);
 am_type = get_1wrd_amtype(op2_ti);
 nores_insn(I_FLDL, AM_NONE, am2_type, op2_ti);
 if (cc != CC_JLT && cc != CC_JLE)
  {
   /* fxch swap register in stack ST(1) with ST(0) */
   nores_insn(I_FXCH, AM_NONE, AM_REG, ST1);
  }
 nores_insn(I_FUCOMPP, AM_NONE, AM_NONE);
 /* this changed fixed reg AX */
 nores_insn(I_FNSTSW, AM_NONE, AM_REG, AR_AX);
 /* store special bits of cc flags into AX */
 nores_insn(I_SAHF, AM_NONE, AM_NONE);
 /* set jump codes based on insn compare type */
 switch (cc) {
  case CC_JGE:
   /* AIV 01/09/07 - these where regular jmp should be real jmp */
   /* this condition code was also wrong */
   cond_real_jmp_insn(CC_JGE, t_bbp, f_bbp);
   break;
  case CC_JGT:
   cond_real_jmp_insn(CC_JGT, t_bbp, f_bbp);
   break;
  case CC_JLE:
   cond_real_jmp_insn(CC_JGE, t_bbp, f_bbp);
   break;
  case CC_JLT:
   cond_real_jmp_insn(CC_JGT, t_bbp, f_bbp);
   break;
  case CC_JE:
   cond_real_jmp_insn(CC_JNE, f_bbp, t_bbp);
   break;
  case CC_JNE:
   cond_real_jmp_insn(CC_JNE, t_bbp, f_bbp);
   break;
  default: 
   __case_terr(__FILE__, __LINE__); 
   break;
 } 
}

static void cond_real_jmp_insn(int32 cc, struct bblk_t *t_bbp,
 struct bblk_t *f_bbp)
{
 nores_insn(I_REAL_COND_JMP, AM_BBLK, t_bbp, AM_BBLK, f_bbp);
 __cur_bbp->itail->jmptyp = cc;
 /* AIV 01/09/07 - wasn't marking the sign jump bit */
 __cur_bbp->itail->sgn_jmp = TRUE;
 __set_back_edge(t_bbp);
 __set_back_edge(f_bbp);
}

#else
static void emit_real_cmp(struct bblk_t *t_bbp, struct bblk_t *f_bbp,
 int32 op1_ti, int32 op2_ti,int32 cc)
{
 int32 am_type;

 /* load op1 and op2 to compare */
 am_type = get_1wrd_amtype(op1_ti);
 nores_insn(I_LDR1, AM_NONE, am_type, op1_ti);

 am_type = get_1wrd_amtype(op2_ti);
 nores_insn(I_LDR2, AM_NONE, am_type, op2_ti);

 nores_insn(I_FUCOMPP, AM_NONE, AM_NONE);
 /* set jump codes based on insn compare type */
 switch (cc) {
  case CC_JGE:
   cond_jmp_insn(CC_JGE, t_bbp, f_bbp);
   break;
  case CC_JGT:
   cond_jmp_insn(CC_JGT, t_bbp, f_bbp);
   break;
  case CC_JLE:
   cond_jmp_insn(CC_JLE, t_bbp, f_bbp);
   break;
  case CC_JLT:
   cond_jmp_insn(CC_JLT, t_bbp, f_bbp);
   break;
  case CC_JE:
   cond_jmp_insn(CC_JE, t_bbp, f_bbp);
   break;
  case CC_JNE:
   cond_jmp_insn(CC_JNE, t_bbp, f_bbp);
   break;
  default: 
   __case_terr(__FILE__, __LINE__); 
   break;
 } 
}

#endif

/*
 * need to have seperate routine because order of operands needs to be
 * taken into account
//AIV? - is this true still?
 */
static int32 lower_subl(int32 op1_ti, int32 op2_ti)
{
 int32 r_ti, am_type, am_type2, blen;

 if (__is_constant(op1_ti) || __is_constant(op2_ti)) 
  {
   blen = __tntab[op1_ti].tnwid;
   /* SJM 11/19/06 - new scheme got rid of too complex interpreter wrapper */
   r_ti = eval_con_oneword_binop(I_SUBL, blen, op1_ti, op2_ti);
   if (r_ti != -1) return(r_ti);
  }

 am_type = get_1wrd_amtype(op1_ti);
 am_type2 = get_1wrd_amtype(op2_ti);
 r_ti = eval_insn(TN_VAL, I_SUBL, am_type, op1_ti, am_type2, op2_ti);
 return(r_ti);
}

/*
 * emit a printf BLOCK msg for debugging
 * prints block number upon entering the block
 */
extern void __emit_enter_bblk_dbgmsg(void)
{
 int32 a1_ti, a0_ti, dbgstr_ti, cint_ti;

 dbgstr_ti = __move_insn(TN_ADR, I_MOVA, AM_NLO, NLO_DBGSTR);
 cint_ti = __gen_cint_tn(__cur_bbp->bblk_seqno);
 a1_ti = prep_push_word_arg(cint_ti);
 a0_ti = prep_push_tn_addr_arg(dbgstr_ti);

 /* call wide library file */
 emit_call_asl_proc(ASL_BBLK_DBG_MSG, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * AIV - for code coverage misc terr - used for debugging
 */
extern void __emit_misc_terr(void)
{
 emit_call_asl_func(ASL_MISC_TERR, 0);
}

/*
 * lower to correct mode for simple < 32 op
 * op r1, r2
 * NOTE - this rountine doesn't take into account operand order
 */
static int32 oneword_binop(int32 opcod, int32 op1_ti, int32 op2_ti)
{
 int32 r_ti, am_type, am_type2, blen;

 if (__is_constant(op1_ti) || __is_constant(op2_ti)) 
  {
   blen = __tntab[op1_ti].tnwid;

   /* SJM 11/19/06 - new scheme got rid of too complex interpreter wrapper */
   r_ti = eval_con_oneword_binop(opcod, blen, op1_ti, op2_ti);
   if (r_ti != -1) return(r_ti);
  }

 am_type = get_1wrd_amtype(op1_ti);
 am_type2 = get_1wrd_amtype(op2_ti);
 /* do bin op */
 r_ti = eval_insn(TN_VAL, opcod, am_type, op1_ti, am_type2, op2_ti);
 return(r_ti);
}

/*
 * lower a wide binary arith operation
 *
 * notice that the inputs can be either pointer (usually from per inst
 * where the net label had the inst size offset added) or expression
 * intermediate value on the ebp value stack where only a value exists
 * so the push code must push the addr (probably by emitting a leal)
 * AIV 01/07/08 - size can now be blen or wlen
 */
static int32 wide_binop(int32 asl_rout_num, int32 op1_ti, int32 op2_ti,
  int32 blen, int32 len)
{
 int32 res_ti, len_ti, a0_ti, a1_ti, a2_ti, a3_ti, srtyp;

 srtyp = __tntab[op1_ti].srtyp;
 /* AIV 08/17/10 - can now have 2-state wide types */
 res_ti = -1;
 if (srtyp == SR_VEC) res_ti = __gen_tn(SR_VEC, blen);
 else if (srtyp == SR_BIT2S) res_ti = __gen_tn(SR_BIT2S, blen);
 else __misc_terr(__FILE__, __LINE__);

 len_ti = __gen_cint_tn(len);
 a3_ti = prep_push_word_arg(len_ti);
 /* get stack addresses or location with pointer address */
 a2_ti = prep_push_tn_addr_arg(op2_ti);
 a1_ti = prep_push_tn_addr_arg(op1_ti);
 a0_ti = prep_push_tn_addr_arg(res_ti);

 /* call wide library file */
 emit_call_asl_proc(asl_rout_num, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
 return(res_ti);
}

/*
 * routine to gen a move insn for addresses that need x86 indexing mode
 *
 * this is needed so that virtual machine follows Alpha risc scheme
 * in which only loads and stores have complex addressing modes
 *
 * notice his is 
 *
 * SJM 07/14/06 - this routine's changes remove x86 index accesing modes 
 * from eval insns
 */
static int32 insert_1wrd_ndxreg_mov(int32 op_ti) 
{
 int32 ret_ti;

 if (__tntab[op_ti].tn_typ == TN_ADR) 
  {
   ret_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, op_ti);
  }
 else ret_ti = op_ti;
 return(ret_ti);
}

/*
 * get an access type (AM_REG, AM_NDXREG) for one word tn
 * this returns access type to get WBITS actual value 
 * because it is a tn, access type according to type 
 */
static int32 get_1wrd_amtype(int32 op_ti)
{
 int32 amtyp;

 /* DBG remove -- */
 if (op_ti < 0) __misc_terr(__FILE__, __LINE__);
 /* -- */

 if (__tntab[op_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; else amtyp = AM_REG;
 return(amtyp);
}

/*
 * gen code to prepare an asl routine arg
 *
 * will be reg push or literal cint result, i.e. ndx reg operands loaded 
 * into non index reg
 * 
 * if tn reg spills, special case 2 mem ref code will load into ecx
 * before moving into ndx reg <4*argno>(%esp) with offset
 *
 * SJM 10/23/06 - since for x86 can push mem ref this does nothing - it is
 * a place holder for checking and in case other architectures need moves
 */
static int32 prep_push_word_arg(int32 op_ti)
{
 __push_count++;
 return(op_ti);
}

/*
 * prep args to push real - doesn't do anything
//AIV? - is this right - also see the I_CALL_ASL ... esp storing insns
 */
static int32 prep_push_real_arg(int32 op_ti)
{
 __push_count += 2;
 /* DBG remove -- */
 if (!__tntab[op_ti].t_real) __misc_terr(__FILE__, __LINE__);
 /* --- */
 return(op_ti);
}


/*
 * prepare (gen insn) for later pushing an addr onto the esp stack
 *
 * for now storing using ESP index addressing
 *
 * SJM 10/25/06 - now emit any needed leal into %ecx in bbopt asl call expand
 * mark parent as used wide to prevent wide decomposition
 */
static int32 prep_push_tn_addr_arg(int32 op_ti)
{
 int32 par_tni;
 struct tn_t *tnp;

 __push_count++;
 tnp = &(__tntab[op_ti]);
 /* for non addresses need the leal */
 if (tnp->tn_typ != TN_ADR)
  {
   if (tnp->tag_parent_tni != -1) par_tni = tnp->tag_parent_tni;
   else par_tni = op_ti;
   __tntab[par_tni].tn_used_wide = TRUE;
  }
 return(op_ti);
}

/*
 * ROUTINES TO LOWER COPY 
 */

/*
 * expand the I_COPY to it's lowered insns and linkout the I_COPY
 */
extern void __expand_copy(struct insn_t *ip)
{
 int32 src_ti, dst_ti, nbytes;

 src_ti = ip->isrc.am_tni;
 dst_ti = ip->idst.am_tni;
 nbytes = ip->isrc.disp;
 /* must mark the current __copy_ip to link on the new insn on the end of */
 __copy_ip = ip;

 /* SJM 09/13/06 - must use the ifrom context of the copy insn for debugging */
#ifdef __CVC_DEBUG__
 __cur_ifrom_u = ip->ifru;
#endif

 /* do the expanding */
 lower_copy(src_ti, dst_ti, nbytes);
 /* link out the insn and set __copy_ip back to NULL */
 __linkout_insn(ip, TRUE);
 __copy_ip = NULL;
}

/*
 * lower copy - simplified version where next lowering pass determines if
 * label can be used
 */
static void lower_copy(int32 src_ti, int32 dst_ti, int32 nbytes)
{
 int32 nwrds, r1_ti, dst_am_type, nbytes_ti, a0_ti, a1_ti, a2_ti;
 size_t i;
 struct tn_t *src_tnp;

 src_tnp = &(__tntab[src_ti]);
 /* case 1: word source can be a mem label */
 if (src_tnp->comlab_typ == COMLAB_CONADR)
  {
   lower_contab_src_copy(src_ti, dst_ti, nbytes);
   return;
  }

 /* case 2: one word exactly case */
 if (nbytes == WRDBYTES)
  {
   /* SJM 07/14/06 - store (really a movl) can have an addr as src or dst */
   /* but both can't be following alpha risc pattern */
   if (__tntab[src_ti].tn_typ == TN_ADR && __tntab[dst_ti].tn_typ == TN_ADR)
    {
     r1_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, src_ti);
     __st_insn(I_STOREA, AM_REG, r1_ti, AM_NDXREG, dst_ti);
    }
   else
    {
     r1_ti = insert_1wrd_ndxreg_mov(src_ti);
     dst_am_type = get_1wrd_amtype(dst_ti);
     __st_insn(I_STOREA, AM_REG, r1_ti, dst_am_type, dst_ti);
    }
   return;
  }
 /* case 3: case narrower than word bytes */
 else if (nbytes < WRDBYTES) 
  {
   lower_narrow_copy(src_ti, dst_ti, nbytes); 
   return;
  }

 /* case 4: wide but narrow enough to inline */
 /* nbytes <= xpnd word max words and aligned on word */
 /* and know both source and destination in the %ebp variable area */
 if (copy_xpnd_(nbytes))
  {
   nwrds = nbytes/WRDBYTES;
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     /* case 4a: destination is addr */
     if (__tntab[src_ti].tn_typ == TN_ADR)
      {
       for (i = 0; i < WRDBYTES*nwrds; i += WRDBYTES)
        {
         r1_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, src_ti, i);
         __st_insn(I_STOREA, AM_REG, r1_ti, AM_NDXREG_DISP, dst_ti, i);
        }
      }
     else
      {
       for (i = 0; i < nwrds; i++)
        {
         /* SJM 02/15/06 - am reg ofs is words but wrk ndx reg ofs bytes */
         r1_ti = __move_insn(TN_VAL, I_MOVA, AM_NONREG_OFS, src_ti, WRDBYTES*i);
         __st_insn(I_STOREA, AM_REG, r1_ti, AM_NDXREG_DISP, dst_ti, i*WRDBYTES);
        }
      }
    }
   else
    {
     /* case 4b: destination is not an addr */
     if (__tntab[src_ti].tn_typ == TN_ADR)
      {
       for (i = 0; i < nwrds; i++)
        {
         r1_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, src_ti, WRDBYTES*i);
         __st_insn(I_STOREA, AM_REG, r1_ti, AM_NONREG_OFS, dst_ti, WRDBYTES*i);
        }
      }
     else
      {
       for (i = 0; i < nwrds; i++)
        {
         /* SJM 02/15/06 - am reg ofs is words but wrk ndx reg ofs bytes */
         r1_ti = __move_insn(TN_VAL, I_MOVA, AM_NONREG_OFS, src_ti, WRDBYTES*i);
         /* illegal 2 x86 memory refs in one minsn fixed later */
         __st_insn(I_STOREA, AM_REG, r1_ti, AM_NONREG_OFS, dst_ti, WRDBYTES*i);
        }  
      }
    }
   return;
  }
 /* case 5: extra wide case > 10 words */
 nbytes_ti = __gen_cint_tn(nbytes);
 a2_ti = prep_push_word_arg(nbytes_ti);
 a1_ti = prep_push_tn_addr_arg(src_ti);
 a0_ti = prep_push_tn_addr_arg(dst_ti);
 emit_call_asl_proc(ASL_MEMCPY, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * lower copy of < WRDBYTES
 */
static void lower_narrow_copy(int32 src_ti, int32 dst_ti, int32 nbytes)
{
 if (nbytes == 1)
  {
   lower_one_byte_copy(src_ti, dst_ti);
  }
 else if (nbytes == 2)
  {
   lower_two_bytes_copy(src_ti, dst_ti);
  }
 else if (nbytes == 3)
  {
   lower_three_bytes_copy(src_ti, dst_ti);
  }
#ifdef __CVC32__
 else __misc_terr(__FILE__, __LINE__);
#else
 else
  {
   lower_bytes_four_to_seven64(src_ti, dst_ti, nbytes);
/*
   int32 nbytes_ti, a0_ti, a1_ti, a2_ti;

   if (nbytes == 8) __misc_terr(__FILE__, __LINE__);

   nbytes_ti = __gen_cint_tn(nbytes);
   a2_ti = prep_push_word_arg(nbytes_ti);
   a1_ti = prep_push_tn_addr_arg(src_ti);
   a0_ti = prep_push_tn_addr_arg(dst_ti);
   emit_call_asl_proc(ASL_MEMCPY, 3, a2_ti, a1_ti, a0_ti);
   chk_callasl_arg_num(3);
*/
  }
#endif
}

#ifndef __CVC32__
/*
 * 64-bit narrow copy for 4 to 7 byte copies
 * 
 * mask the number of bytes from the src
 * mask the number to high bytes from a movq from the dst or the result
 * and just do a movq
 *
 * Not the best code but still better than a call to memcpy
 */
static void lower_bytes_four_to_seven64(int32 src_ti, int32 dst_ti, 
 int32 nbytes)
{
 word32 mask, mask2;
 int32 r1_ti, r2_ti, r3_ti, mask_ti, mask2_ti;

 switch (nbytes) {
  case 4: 
   /* AIV 08/03/10 - added ability to use movl four byte copy */
   lower_four_byte_copy(src_ti, dst_ti); 
   return; 
  case 5: mask = 0xffffffffffUL; break;
  case 6: mask = 0xffffffffffffUL; break;
  case 7: mask = 0xffffffffffffffUL; break;
  default: __case_terr(__FILE__, __LINE__); break;
 }
 
 mask_ti = __gen_cint_tn(mask);
 /* get the high mask */
 mask2 = 0xffffffffffffffffUL - mask;
 mask2_ti = __gen_cint_tn(mask2);
 if (__tntab[src_ti].tn_typ == TN_ADR)
  {
   /* mask the src */
   r1_ti = eval_insn(TN_VAL, I_ANDL, AM_REG, mask_ti, AM_NDXREG, src_ti);
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     /* mask the high part of the dst */
     r2_ti = eval_insn(TN_VAL, I_ANDL, AM_REG, mask2_ti, AM_NDXREG, dst_ti);
     /* make the new 64-bit value and store as movq */
     r3_ti = eval_insn(TN_VAL, I_ORL, AM_REG, r1_ti, AM_REG, r2_ti);
     __st_insn(I_STOREL, AM_REG, r3_ti, AM_NDXREG, dst_ti);
    }
   else
    {
     r2_ti = eval_insn(TN_VAL, I_ANDL, AM_REG, mask2_ti, AM_REG, dst_ti);
     r3_ti = eval_insn(TN_VAL, I_ORL, AM_REG, r1_ti, AM_REG, r2_ti);
     __st_insn(I_STOREL, AM_REG, r3_ti, AM_REG, dst_ti);
    }
  }
 else 
  {
   r1_ti = eval_insn(TN_VAL, I_ANDL, AM_REG, mask_ti, AM_REG, src_ti);
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     r2_ti = eval_insn(TN_VAL, I_ANDL, AM_REG, mask2_ti, AM_NDXREG, dst_ti);
     r3_ti = eval_insn(TN_VAL, I_ORL, AM_REG, r1_ti, AM_REG, r2_ti);
     __st_insn(I_STOREL, AM_REG, r3_ti, AM_NDXREG, dst_ti);
    }
   else
    {
     r2_ti = eval_insn(TN_VAL, I_ANDL, AM_REG, mask2_ti, AM_REG, dst_ti);
     r3_ti = eval_insn(TN_VAL, I_ORL, AM_REG, r1_ti, AM_REG, r2_ti);
     __st_insn(I_STOREL, AM_REG, r3_ti, AM_REG, dst_ti);
    }
  }
}

/*
 * do a 4-byte copy on a 64-bit machine
 * based on  - lower_one_byte_copy but movl for 64-bit machind
 * idea is to use special insns which have special SIZ_LL and SIZ_QL size
 * to indicate it is using a 4-byte register
 */
static void lower_four_byte_copy(int32 src_ti, int32 dst_ti)
{
 int32 r1_ti;

 if (__tntab[src_ti].tn_typ == TN_ADR)
  {
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     r1_ti = __move_insn(TN_VAL, I_MOVQL, AM_NDXREG, src_ti);
     __st_insn(I_STOREQL, AM_REG, r1_ti, AM_NDXREG, dst_ti);
    }
   else
    {
     if (__tntab[dst_ti].srtyp == SR_SVEC)
      {
       r1_ti = __move_insn(TN_VAL, I_MOVQL, AM_NDXREG, src_ti);
       __st_insn(I_STOREQL, AM_REG, r1_ti, AM_REG, dst_ti);
      }
     else 
      {
       r1_ti = __move_insn(TN_VAL, I_MOVSLQ, AM_NDXREG, src_ti);
       __st_insn(I_STOREQL, AM_REG, r1_ti, AM_REG, dst_ti);
      }
    }
  }
 else 
  {
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     __st_insn(I_STOREQL, AM_REG, src_ti, AM_NDXREG, dst_ti);
    }
   else
    {
     __st_insn(I_STOREQL, AM_REG, src_ti, AM_REG, dst_ti);
    }
  }
}
#endif

/*
 * lower the copy of one byte
 */
static void lower_one_byte_copy(int32 src_ti, int32 dst_ti)
{
 int32 r1_ti;

 if (__tntab[src_ti].tn_typ == TN_ADR)
  {
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     r1_ti = __move_insn(TN_VAL, I_MOVB, AM_NDXREG, src_ti);
     __st_insn(I_STOREB, AM_REG, r1_ti, AM_NDXREG, dst_ti);
    }
   else
    {
//AIV LOOKATME 11/08/06 - why is this true - doesn't seem right
     /* AIV 10/13/06 - if dst is a strength cannot copy more than a byte */
     if (__tntab[dst_ti].srtyp == SR_SVEC)
      {
       r1_ti = __move_insn(TN_VAL, I_MOVB, AM_NDXREG, src_ti);
       __st_insn(I_STOREB, AM_REG, r1_ti, AM_REG, dst_ti);
      }
     else 
      {
       /* AIV 10/13/06 - if dst is a not a strength zero high part */
       /* since this is going in a reg or word sized tmp */
       r1_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, src_ti);
       __st_insn(I_STOREA, AM_REG, r1_ti, AM_REG, dst_ti);
      }
    }
  }
 else 
  {
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     __st_insn(I_STOREB, AM_REG, src_ti, AM_NDXREG, dst_ti);
    }
   else
    {
     /* AIV 07/31/06 - should just be able to copy the byte without masking */
     __st_insn(I_STOREB, AM_REG, src_ti, AM_REG, dst_ti);

     /* AIV 11/04/05 - need to zero the word so tmp can be used with long */
     /* insn zero the high bits */
     /* AIV FIXME - could use movzbl with register allocation */
     /* stack location can't be zeroed with movzbl */
     /* better to avoid bytes as only because there are only 4 byte regs */
/* AIV LOOKATME why was this being done??????????
     __st_insn(I_STOREA, AM_REG, src_ti, AM_REG, dst_ti);
     ff_ti = __gen_cint_tn(0xff);
     r1_ti = eval_insn(TN_VAL, I_ANDL, AM_REG, ff_ti, AM_REG, dst_ti);
     __st_insn(I_STOREA, AM_REG, r1_ti, AM_REG, dst_ti);
*/
    }
  }
}

/*
 * lower the copy of two bytes
 * mov half word (2 bytes)
 */
static void lower_two_bytes_copy(int32 src_ti, int32 dst_ti)
{
 int32 r1_ti, ffff_ti;

 if (__tntab[src_ti].tn_typ == TN_ADR)
  {
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     r1_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, src_ti);
     __st_insn(I_STOREW, AM_REG, r1_ti, AM_NDXREG, dst_ti);
    }
   else
    {
     r1_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, src_ti);
     __st_insn(I_STOREW, AM_REG, r1_ti, AM_REG, dst_ti);
    }
  }
 else 
  {
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     __st_insn(I_STOREW, AM_REG, src_ti, AM_NDXREG, dst_ti);
    }
   else
    {
     __st_insn(I_STOREA, AM_REG, src_ti, AM_REG, dst_ti);
     ffff_ti = __gen_cint_tn(0xffff);
     r1_ti = emit_oneword_and(ffff_ti, dst_ti, FALSE, -1, -1);
     __st_insn(I_STOREA, AM_REG, r1_ti, AM_REG, dst_ti);
    }
  }
}

/*
 * lower the copy of two bytes
 */
static void lower_three_bytes_copy(int32 src_ti, int32 dst_ti)
{
 int32 r1_ti, r2_ti, r3_ti, r4_ti, r5_ti, i16_ti;
 int32 zzffzzzz_ti, zzffffff_ti;

 i16_ti = __gen_cint_tn(16);
 if (__tntab[src_ti].tn_typ == TN_ADR)
  {
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     /* both are addresses */
     //AIV FIXME -these moves aren't needed anymore
     /* put src and dst into work registers */
     /* copy half word */
     r1_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, src_ti);
     __st_insn(I_STOREW, AM_REG, r1_ti, AM_NDXREG, dst_ti);
     /* copy third byte */

     r2_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG_DISP, src_ti, 2UL);
     __st_insn(I_STOREB, AM_REG, r2_ti, AM_NDXREG_DISP, dst_ti, 2UL);
    }
   else
    {
     /* AIV 07/31/07 - this case was still wrong - correct now */
     /* src is address dst is value */
     /* AIV FIXME - probably a better method */
     /* SJM 04/06/07 - move of a tn adr must be a tn adr still */
     r1_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, src_ti);
     /* get low half word in wrkr2 */
     r2_ti = __move_insn(TN_VAL, I_MOVZWL, AM_NDXREG, r1_ti);
     /* get third byte in wrkr3 */
     r3_ti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG_DISP, r1_ti, 2UL);

     /* shift third byte over 2 bytes */
     r4_ti = emit_oneword_shift(I_SHLL, i16_ti, r3_ti);
     /* or in third byte */
     r5_ti = oneword_binop(I_ORL, r4_ti, r2_ti);
     /* assign to dst reg */
     __st_insn(I_STOREA, AM_REG, r5_ti, AM_REG, dst_ti);
    }
  }
 else 
  {
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     /* AIV FIXME - probably a better method */
     r1_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, src_ti);
     /* SJM 04/06/07 - move of a tn adr must be a tn adr still */
     r2_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, dst_ti);
     r3_ti = __move_insn(TN_VAL, I_MOVZWL, AM_REG, r1_ti);
     /* copy half word */
     __st_insn(I_STOREW, AM_REG, r3_ti, AM_NDXREG, r2_ti);

     /* isolate and assign third byte */
     zzffzzzz_ti = __gen_cint_tn(0x00ff0000);
     r4_ti = emit_oneword_and(zzffzzzz_ti, r1_ti, FALSE, -1, -1);
     r5_ti = emit_oneword_shift(I_SHRL, i16_ti, r4_ti);
     /* copy the 3 byte */ 
     __st_insn(I_STOREB, AM_REG, r5_ti, AM_NDXREG_DISP, r2_ti, 2UL);
    }
   else
    {
     /* copy wrd and mask the result this is ok because result is in reg/stk */
     zzffffff_ti = __gen_cint_tn(0x00ffffff);
     __st_insn(I_STOREA, AM_REG, src_ti, AM_REG, dst_ti);
     r1_ti = emit_oneword_and(zzffffff_ti, dst_ti, FALSE, -1, -1);
     __st_insn(I_STOREA, AM_REG, r1_ti, AM_REG, dst_ti);
    }
  }
}

/*
 * lower a copy where src is a constant in contab
 */
static void lower_contab_src_copy(int32 src_ti, int32 dst_ti, int32 nbytes)
{
 int32 cndx, nwrds, nbytes_ti, ctabndx_ti;
 int32 a0_ti, a1_ti, a2_ti;
 size_t i;
 struct tn_t *tnp;

 /* get the base contab and add the offset if there is one */
 tnp = &(__tntab[src_ti]);
 cndx = tnp->tncu.el_ndx;
 /* offset is in bytes so need contab word index */
 if (tnp->child_tag_offset != 0)
  {
   cndx += (tnp->child_tag_offset/WRDBYTES);
  }

 /* case 1: one contab word */
 if (nbytes == WRDBYTES)
  {
   ctabndx_ti = __gen_cint_tn(__contab[cndx]);

   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     __st_insn(I_STOREA, AM_REG, ctabndx_ti, AM_NDXREG, dst_ti);
    }
   else __st_insn(I_STOREA, AM_REG, ctabndx_ti, AM_REG, dst_ti);
   return;
  }

 /* case 2: one byte */
 if (nbytes == 1)
  {
   ctabndx_ti = __gen_cint_tn(__contab[cndx]);
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     __st_insn(I_STOREB, AM_REG, ctabndx_ti, AM_NDXREG, dst_ti);
    }
   else __st_insn(I_STOREB, AM_REG, ctabndx_ti, AM_REG, dst_ti);
   return;
  }

 //AIV FIXME/WRITEME - 2/3 bytes
 /* DBG remove */ 
 if ((nbytes % WRDBYTES) != 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */ 

 /* case 3: short so inline */
 if (copy_xpnd_(nbytes))
  {
   nwrds = nbytes/WRDBYTES;
   if (__tntab[dst_ti].tn_typ == TN_ADR)
    {
     /* cndx is in words but i is in bytes */
     for (i = 0; i < WRDBYTES*nwrds; cndx++, i += WRDBYTES)
      {
       ctabndx_ti = __gen_cint_tn(__contab[cndx]);
       __st_insn(I_STOREA, AM_REG, ctabndx_ti, AM_NDXREG_DISP, dst_ti, i);
      }
    }
   else
    {
     /* for dest value can use the new am reg ofs amode */
     /* cndx is in words but i is in bytes */
     for (i = 0; i < nwrds; cndx++, i++)
      {
       ctabndx_ti = __gen_cint_tn(__contab[cndx]);

       /* SJM 02/15/06 - am reg ofs is words */
       __st_insn(I_STOREA, AM_REG, ctabndx_ti, AM_NONREG_OFS, dst_ti,
        WRDBYTES*i);
      }
    }
   return;
  }

 /* case 3: use the wrapper */
 /* if get here know large copy reconstruct constant name and use memcpy */
 nbytes_ti = __gen_cint_tn(nbytes);
 a2_ti = prep_push_word_arg(nbytes_ti);
 a1_ti = prep_push_tn_addr_arg(src_ti);
 a0_ti = prep_push_tn_addr_arg(dst_ti);
 emit_call_asl_proc(ASL_MEMCPY, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * narrow an existing tmp into a new smaller tmp
 * AIV 09/08/10 - using new better code for narrow case 
 * this is common code for new DPI conversions 
 */
extern int32 __emit_new_narrow_word(int32 newwid, int32 rhs_ti, int32 is_2state)
{
 int32 res_ti, res_bpti, rhs_bpti, mask_ti, r1_ti, r2_ti, am_type;
 word32 mask;

 /* must take blen as second arg so doesn't get mapped to wrong size tn */
 /* AIV 09/12/08 - just copy a/b into a smaller blen tmp */
 if (is_2state) res_ti = __gen_tn(SR_BIT2S, newwid);
 else res_ti = __gen_tn(SR_VEC, newwid);
 if (newwid == WBITS)
  {
   __emit_copy(WRDBYTES, rhs_ti, res_ti);
   if (is_2state) return(res_ti);
   rhs_bpti = __get_bpti(rhs_ti);
   res_bpti = __get_bpti(res_ti);
   __emit_copy(WRDBYTES, rhs_bpti, res_bpti);
   return(res_ti);
  }

 if (newwid == 8)
  {
   am_type = get_1wrd_amtype(rhs_ti);
   r1_ti = __move_insn(TN_VAL, I_MOVZBL, am_type, rhs_ti);
   __emit_copy(WRDBYTES, r1_ti, res_ti);
   if (is_2state) return(res_ti);
   rhs_bpti = __get_bpti(rhs_ti);
   r1_ti = __move_insn(TN_VAL, I_MOVZBL, am_type, rhs_bpti);
   res_bpti = __get_bpti(res_ti);
   __emit_copy(WRDBYTES, r1_ti, res_bpti);
   return(res_ti);
  }
#ifndef __CVC32__
 if (newwid == 32)
  {
   __st_insn(I_STOREA, AM_IMM, 0, AM_REG, res_ti);
   am_type = get_1wrd_amtype(rhs_ti);
   __st_insn(I_STOREQL, am_type, rhs_ti, AM_REG, res_ti);
   if (is_2state) return(res_ti);

   rhs_bpti = __get_bpti(rhs_ti);
   res_bpti = __get_bpti(res_ti);
   __st_insn(I_STOREA, AM_IMM, 0, AM_REG, res_bpti);
   __st_insn(I_STOREQL, am_type, rhs_bpti, AM_REG, res_bpti);
   return(res_ti);
  }
#endif

 /* need to mask off to narrow to dst wid */ 
 mask = __masktab[newwid];
 mask_ti = __gen_cint_tn(mask);
 r1_ti = __emit_mask_and(rhs_ti, mask_ti);  
 __emit_copy(WRDBYTES, r1_ti, res_ti);
 if (is_2state) return(res_ti);
 rhs_bpti = __get_bpti(rhs_ti);
 r2_ti = __emit_mask_and(rhs_bpti, mask_ti);  
 res_bpti = __get_bpti(res_ti);
  __emit_copy(WRDBYTES, r2_ti, res_bpti);
 return(res_ti);
}


/*
 * set all bytes to the constant bval
 * equivalent to - set_byteval_(sbp, len, stval)
 */
static void lower_setbytes(int32 op_ti, byte bval, int32 nbytes)
{
 /* tn adr or tn value */
 if (__tntab[op_ti].tn_typ == TN_ADR)
  {
   lower_setbyte_tnadr(op_ti, bval, nbytes);
  }
 else lower_setbyte_tnval(op_ti, bval, nbytes);
}

/*
 * lower bytes into stack value location
 * Note 0xff special case convert value to 0xffffffff when copying words
 */
static void lower_setbyte_tnval(int32 op_ti, byte bval, int32 nbytes)
{
 int32 nwrds, rbytes, storv_ti, nbytes_ti, bval_ti;
 size_t i;
 int32 a0_ti, a1_ti, a2_ti;
 word32 mask, ibval;

 /* less than one word copy upto 3 bytes */ 
 if (nbytes < WRDBYTES)
  {
   if (nbytes == 1) mask = bval;
   else if (nbytes == 2) mask = (bval << 8) | bval;
   else  mask = (bval << 16) | (bval << 8) | bval;

   storv_ti = __gen_cint_tn(mask);
   __st_insn(I_STOREA, AM_REG, storv_ti, AM_REG, op_ti);
   return;
  }
 /* one word copy */ 
 if (nbytes == WRDBYTES)
  {
   /* special case if bval is 0xff make value all 1s to copy as word */
   if (bval == 0xff) ibval = ALL1W;
   else ibval = bval;
   storv_ti = __gen_cint_tn(ibval);
   __st_insn(I_STOREA, AM_REG, storv_ti, AM_REG, op_ti);
   return;
  }

 /*  nbytes <= xpnd word max words and aligned on word */
 if ((nbytes <= WRDBYTES*XPND_COPY_WORDS))
  {
   nwrds = nbytes/WRDBYTES;

   /* special case if bval is 0xff make value all 1s to copy as word */
   if (bval == 0xff) ibval = ALL1W; else ibval = bval;
   storv_ti = __gen_cint_tn(ibval);
   /* copy value as words */
   /* SJM 10/11/06 - this was old am reg ofs amode now gone */
   /* SJM 11/02/06 - must make all operands tmp area offset to handle used */
   /* wide forced spilling - was wrongly emitting 0 offse as NDXREG amode */
   /* AIV 01/07/10 - better to first move constant into a reg and use */
   /* the reg to store the rest of the value - this is better since */
   /* it will decompose into regs */
   /* so instead of  */
   /* movl	$0xffffffff, %eax */
   /* movl	$0xffffffff, %ebx */
   /* it now produces */
   /* movl	$0xffffffff, %eax */
   /* movl	%eax, %ebx */
   storv_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, storv_ti);
   __st_insn(I_STOREA, AM_REG, storv_ti, AM_NONREG_OFS, op_ti, 0);
   for (i = 1; i < nwrds; i++)
    {
     __st_insn(I_STOREA, AM_REG, storv_ti, AM_NONREG_OFS, op_ti, WRDBYTES*i);
    }

   /* if not aligned on word get the remaining bytes to copy value to */ 
   if ((rbytes = nbytes % WRDBYTES) != 0)
    {
     /* SJM 02/16/05 - FIXME?? - assuming can over-write and mash high byte */
     /* also assuming on the ebp stack */ 
     if (rbytes == 1) mask = bval;
     else if (rbytes == 2) mask = (bval << 8) | bval;
     else  mask = (bval << 16) | (bval << 8) | bval;

     storv_ti = __gen_cint_tn(mask);
     __st_insn(I_STOREA, AM_REG, storv_ti, AM_REG, op_ti);
    }
   return;
  }

 /* extra wide wrapper */ 
 nbytes_ti = __gen_cint_tn(nbytes);
 a2_ti = prep_push_word_arg(nbytes_ti);
 bval_ti = __gen_cint_tn(bval);
 a1_ti = prep_push_word_arg(bval_ti);
 a0_ti = prep_push_tn_addr_arg(op_ti);
 emit_call_asl_proc(ASL_MY_MEMSET, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * lower byte constant into address 
 * Note 0xff special case convert value to 0xffffffff when copying words
 */
static void lower_setbyte_tnadr(int32 op_ti, byte bval, int32 nbytes)
{
 int32 nwrds, r1_ti, nbytes_ti, bval_ti, ibval_ti;
 size_t i;
 word32 ibval;
 int32 a0_ti, a1_ti, a2_ti;

 /* if already b part get the new stack location */
 /* less than one word copy upto 3 bytes */ 
 if (nbytes < WRDBYTES)
  {
   /* AIV 09/14/07 - was wrong probably never tested/used */
   r1_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, op_ti);
   bval_ti = __gen_cint_tn(bval);
   for (i = 1; i < nbytes; i++)
    {
     __st_insn(I_STOREB, AM_REG, bval_ti, AM_NDXREG_DISP, r1_ti, i);
    }
   return;
  }

 /* one word copy */ 
 if (nbytes == WRDBYTES)
  {
   /* special case if bval is 0xff make value all 1s to copy as word */
   if (bval == 0xff) ibval = ALL1W;
   else ibval = bval;
   ibval_ti = __gen_cint_tn(ibval);
   __st_insn(I_STOREA, AM_REG, ibval_ti, AM_NDXREG, op_ti);
   return;
  }

 /*  nbytes <= xpnd word max words and aligned on word */
 if ((nbytes <= WRDBYTES*XPND_COPY_WORDS))
  {
   nwrds = nbytes/WRDBYTES;

   /* special case if bval is 0xff make value all 1s to copy as word */
   if (bval == 0xff) ibval = ALL1W; else ibval = bval;
   r1_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, op_ti);
   ibval_ti = __gen_cint_tn(ibval);
   __st_insn(I_STOREA, AM_REG, ibval_ti, AM_NDXREG, r1_ti);
   /* copy value as words */ 
   /* AIV 07/31/08 - was doing extra word here - should start at WRDBYTES */
   for (i = WRDBYTES; i < WRDBYTES*nwrds; i += WRDBYTES)
    {
     __st_insn(I_STOREA, AM_REG, ibval_ti, AM_NDXREG_DISP, r1_ti, i);
    }

   /* if not aligned on word get the remaining bytes to copy value to */ 
   if ((nbytes % WRDBYTES) != 0)
    {
     i = nbytes/WRDBYTES;
     bval_ti = __gen_cint_tn(bval);
     for (; i <  nbytes; i++)
      {
       __st_insn(I_STOREB, AM_REG, bval_ti, AM_NDXREG_DISP, r1_ti, i);
      }
    }
   return;
  }

 /* extra wide wrapper */ 
 nbytes_ti = __gen_cint_tn(nbytes);
 a2_ti = prep_push_word_arg(nbytes_ti);
 bval_ti = __gen_cint_tn(bval);
 a1_ti = prep_push_word_arg(bval_ti);
 a0_ti = prep_push_tn_addr_arg(op_ti);
 emit_call_asl_proc(ASL_MY_MEMSET, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * ROUTINES TO GENERATE TNS THAT DO NOT NEED TMP AREA (STACK?) STORAGE
 * AND ARE NET LIST DATA STRUCTURE OBJECTS ACCESSED FROM PER MOD COMM LABEL
 */

/*
 * routine to generate a stmt mem label non storage using tmp name
 *
 * also build and links on the memory area tag
 * nil stmt cases must be caught before here
 */
extern int32 __gen_stmt_tn(struct st_t *stp)
{
 int32 tni, ndx;
 struct tn_t *tnp;

 stp->is_loaded = TRUE;
 ndx = stp->st_ndx;
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_STMT;
 tnp->tncu.el_ndx = ndx;
 tnp->tn_typ = TN_ADR;
 /* AIV 08/30/07 - currently need to build address from tmp vals */
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) stp;
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

/*
 * routine to generate an xpr mem label non storage tn
 *
 * also build and links on the memory area tag
 * the tn value is really the index in inst_mod - works because always
 * in module only - other accesses through the gref struct
 */
extern int32 __gen_xpr_tn(struct expr_t *xp)
{
 int32 tni, i;
 struct tn_t *tnp;
 struct prep_obj_t *pop;

 xp->is_loaded = TRUE;
 pop = __find_add_obj(__xpr_dup_tree, (void *) xp);
 /* DBG remove -- */
 if (__avl_node_is_new) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* AIV 02/01/12 - this linear search is bad if this table is large */
 /* which it can be - say 1M force statements */
 /* these are stored in a tree anyway so just do the tree lookup */
 /*
 etp = __inst_mod->expr_tab;
 if (etp == NULL) __misc_terr(__FILE__, __LINE__);
 for (i = 0; i < etp->num; i++)
  {
   if (xp == etp->table[i]) break;
  }
 if (i == etp->num) __misc_terr(__FILE__, __LINE__);
 */

 i = pop->xvi;
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_XPR;
 tnp->tncu.el_ndx = i;
 /* AIV 08/30/07 - currently need to build address from tmp vals */
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) xp;
 tnp->tnsyrecp->in_mdp = __inst_mod;
 tnp->tn_typ = TN_ADR;
 return(tni);
}

/*
 * generate a task load tmp
 */
extern int32 __gen_taskp_tn(struct task_t *tskp)
{
 int32 tni;
 struct tn_t *tnp;

 /* AIV 12/06/07 - only used for task which contain a %m in a $display */
 /* DBG remove -- */
 if (!tskp->uses_scope) __misc_terr(__FILE__, __LINE__);
 if (tskp->t_idnum == -1) __misc_terr(__FILE__, __LINE__);
 /* ------ */

 tskp->is_loaded = TRUE;
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_TASK_ADR;
 tnp->tncu.el_ndx = tskp->t_idnum;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) tskp;
 tnp->tn_typ = TN_ADR;
 return(tni);
}

/*
 * free a expr node
 */
extern void __obj_dup_node_free(void *obj)
{
 __my_free(obj, sizeof(struct prep_obj_t));
}

/*
 * routine to generate an XMR mem label non storage tn
 * also build and links on the memory area tag 
 */
extern int32 __gen_gref_tn(struct gref_t *grp)
{
 int32 tni, ndx;
 struct mod_t *in_mdp;
 struct tn_t *tnp;

 in_mdp = grp->gin_mdp;

 grp->is_loaded = TRUE;
 /* AIV 08/24/07 - if tni is reset must generate a new tmp but not new seqno */
 /* because tmp tables are per module */
 ndx = grp - in_mdp->mgrtab;
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_GREF;
 tnp->tncu.el_ndx = ndx;
//SJM REMOVEME?
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = in_mdp;
 /* AIV 08/30/07 - currently need to build address from tmp vals */
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) grp;
 tnp->tn_typ = TN_ADR;
 /* if module has been freed tni will be set to one */
 return(tni);
}

/*
 * routine to generate a gate struct mem label non storage tn (aka gate adr)
 */
extern int32 __gen_gate_adr_tn(struct gate_t *gp)
{
 int32 tni, ndx;
 struct tn_t *tnp;

 /* AIV 07/06/09 - removed gp->is_loaded to save space in gate_t */
 //gp->is_loaded = TRUE;
 ndx = gp - __inst_mod->mgates;
 tni = __gen_tn(SR_MODADR, 0);

 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_GATE;
 tnp->tncu.el_ndx = ndx;
 tnp->tn_typ = TN_ADR;
 /* AIV 12/22/06 - need to same the in_mdp to produce the correct label */
//SJM 08-23-07 should remove    
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 /* AIV 08/30/07 - currently need to build address from tmp vals */
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) gp;
 return(tni);
}

/*
 * routine to generate a gate ptr mem label with offset non storage tn
 *
 * also build and links on the memory area tag
 */
extern int32 __gen_gatebp_tn(struct gate_t *gp, int32 blen)
{
 int32 gstate_ti;

 /* DBG remove -- */
 if (gp->gstate_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */

 /* AIV 08/13/07 - handle the design wide case */
 /* AIV FIXME - probably can remove this by getting rid of design wide */
 gstate_ti = __con_adradd_insn(SR_VEC, blen, __idp_ti,
  gp->gstate_ofs*WRDBYTES);
 __tntab[gstate_ti].idp_typ = COMLAB_GATEBP;
 return(gstate_ti);
}

/*
 *
 */
extern int32 __gen_gate_output_value(struct gate_t *gp, int32 is_2state)
{
 int32 gate_out_ti, srtyp;

 /* DBG remove -- */
 if (gp->gate_out_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */

 /* AIV 08/13/07 - handle the design wide case */
 /* AIV FIXME - probably can remove this by getting rid of design wide */
 if (is_2state) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;
 gate_out_ti = __con_adradd_insn(srtyp, 1, __idp_ti,
  gp->gate_out_ofs*WRDBYTES);
 return(gate_out_ti);
}

/*
 * generate a base for the idp comlab
 */
extern int32 __gen_idp_storage_area(void)
{
 int32 tni;
 struct tn_t *tnp;

 tni = __gen_tn(SR_VEC, WBITS);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_IDP;
 tnp->tncu.el_ndx = -1;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
#ifdef __VALTRK__
 tnp->nd_valtrk_idp_siz = TRUE;
#endif
 tnp->tn_typ = TN_ADR;
 return(tni);
}

/*
 * generate a global static memory for the fixed idp memory area 
 */
extern int32 __gen_mdata_value(struct itree_t *itp)
{
 int32 mdat_ti, mdat_offset_ti;
 size_t offset;
 struct mod_t *mdp;

 mdp = itp->itip->imsym->el.emdp;
 offset = (itp->itinum*mdp->mod_idata_siz*WRDBYTES); 
 mdat_ti = __gen_mdat_storage_area(mdp);
 if (offset == 0)
  {
   return(mdat_ti);
  }
 /* DBG remove -- */
 if (offset > (mdp->flatinum*mdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ------ */

 mdat_offset_ti = __con_adradd_insn(SR_CINT, WBITS, mdat_ti, offset);
 __tntab[mdat_offset_ti].idp_typ = COMLAB_IDPDAT;
 return(mdat_offset_ti);
}

/*
 * generate a base for the mdat comlab
 */
extern int32 __gen_mdat_storage_area(struct mod_t *mdp)
{
 int32 tni;
 struct tn_t *tnp;

 /* can use SR_VEC here for 2-state since it is always loaded into another */
 /* tmp with srep type */
 tni = __gen_tn(SR_VEC, WBITS);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_IDPDAT;
 tnp->tncu.el_ndx = mdp->m_idnum;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = mdp;
#ifdef __VALTRK__
 tnp->nd_valtrk_idp_siz = TRUE;
#endif
 tnp->tn_typ = TN_ADR;
 return(tni);
}



/*
 * routine to generate a conta struct mem label non storage tn
 *
 * also build and links on the memory area tag
 */
extern int32 __gen_ca_tn(struct conta_t *cap)
{
 int32 tni, ndx;
 struct tn_t *tnp;

 cap->is_loaded = TRUE;
 ndx = cap - __inst_mod->mcas;
 /* case 2: must allocate new one and set it */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_CA;
 tnp->tncu.el_ndx = ndx;
//SJM? - GET RID OF
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 tnp->tn_typ = TN_ADR;
 /* AIV 08/30/07 - currently need to build address from tmp vals */
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) cap;
 return(tni);
}

/*
 * routine to generate a del ctrl repeat count idp offset tn
 * index is int but value must be word32 for counting
 *
 * no need to check for duplicate because known to load only once
 */
extern int32 __gen_dctrl_rep_bp(struct delctrl_t *dctp)
{
 int32 rep_ti;

 /* pass NULL for task pointer so T_ insn't part of net name */
 rep_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
  dctp->dce_repcnt_ofs*WRDBYTES);
 __tntab[rep_ti].idp_typ = COMLAB_DELREP_BP;
 return(rep_ti);
}

/*
 * routine to generate a npp mem label non storage tn
 *
 * also build and links on the memory area tag
 * no need to check for duplicate because known to load only once
 */
extern int32 __gen_npp_adr_tn(struct net_pin_t *npp)
{
 int32 tni;
 struct tn_t *tnp;

 /* AIV 02/18/07 - no need for tree because each npp only loaded once */
 npp->is_loaded = TRUE;
 /* DBG remove -- */
 if (npp->npp_idnum == -1) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_NPPADR;

 tnp->tncu.el_ndx = npp->npp_idnum;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 /* AIV 08/30/07 - currently need to build address from tmp vals */
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) npp;
 return(tni);
}

/*
 * routine to generate a dcep mem label non storage tn
 *
 * no need to check for duplicate because known to load only once
 */
extern int32 __gen_dce_adr_tn(struct dcevnt_t *dcep)
{
 int32 tni;
 struct tn_t *tnp;

 dcep->is_loaded = TRUE;
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_DCEADR;
 tnp->tncu.el_ndx = dcep->dce_ndx;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 /* AIV 04/17/07 - saving the actual dcep in tfm_syp - maybe not such a */
 /* good idea - trying to save space in tn_t */
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) dcep;
 return(tni);
}

/*
 * NON-BLOCKING
 * routine to generate a procedural enter (function) label non storage tn
 * no need to check for duplicate because known to load only once
 */
extern int32 __gen_proc_enter_nb_adr_tn(struct st_t *stp)
{
 int32 tni, ndx;
 struct tn_t *tnp;

 /* AIV 04/17/07 - no need for tree because each only loaded once */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_PROC_NB_ENTER;
 /* only using for non-blocking statments for now */
 ndx = stp->st_ndx;
 /* DBG remove -- */
 if (!stp->is_nb_enter) __misc_terr(__FILE__, __LINE__);
 if (ndx < 0 || ndx > __inst_mod->mstnum) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tnp->tncu.el_ndx = ndx;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

/*
 * routine to generate a procedural enter (function) label non storage tn
 *
 * no need to check for duplicate because known to load only once
 */
extern int32 __gen_proc_enter_adr_tn(struct st_t *stp)
{
 int32 tni, ndx;
 struct tn_t *tnp;

 ndx = stp->st_ndx;
 /* DBG remove -- */
 if (!stp->is_enter) __misc_terr(__FILE__, __LINE__);
 if (ndx < 0 || ndx > __inst_mod->mstnum) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* AIV 04/17/07 - no need for tree because each only loaded once */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_PROC_ENTER;
 /* only using for non-blocking statments for now */
 /* SJM 08-20-07 - now get stmt enter index from the mod dat dlsym ofs */
 tnp->tncu.el_ndx = ndx;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

/*
 * routine to generate a conta enter (function) label non storage tn
 *
 * no need to check for duplicate because known to load only once
 */
extern int32 __gen_conta_enter_adr_tn(struct conta_t *cap)
{
 struct tn_t *tnp;
 int32 tni;

 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_CONTA_ENTER;
 /* only using for non-blocking statments for now */
 /* DBG remove -- */
 if (cap->enter_cndx == -1) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 tnp->tncu.el_ndx = cap->enter_cndx;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

/*
 * routine to generate a gate enter (function) label non storage tn
 *
 * no need to check for duplicate because known to load only once
 */
extern int32 __gen_gate_enter_adr_tn(struct gate_t *gp)
{
 struct tn_t *tnp;
 int32 tni, offset;

 offset = gp - __inst_mod->mgates;
 /* DBG remove -- */
 if (offset < 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_GATE_ENTER;
 /* only using for non-blocking statments for now */
 tnp->tncu.el_ndx = offset;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

////////////////////////////AIV FIXME////////////////////////////
//AIV FIXME - temporary until cmos/udp/mos backend lowered
extern int32 __gen_gate_change_enter_adr_tn(struct gate_t *gp)
{
 struct tn_t *tnp;
 int32 tni, offset;

 offset = gp - __inst_mod->mgates;
 /* DBG remove -- */
 if (offset < 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_GATE_CHANGE_ENTER;
 /* only using for non-blocking statments for now */
 tnp->tncu.el_ndx = offset;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

extern int32 __gen_gate_acc_change_enter_adr_tn(struct gate_t *gp)
{
 struct tn_t *tnp;
 int32 tni, offset;

 offset = gp - __inst_mod->mgates;
 /* DBG remove -- */
 if (offset < 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_GATE_ACC_CHANGE_ENTER;
 /* only using for non-blocking statments for now */
 tnp->tncu.el_ndx = offset;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

///////////////////////////////////////////////////////////

extern int32 __gen_mipd_enter_adr_tn(int32 offset)
{
 struct tn_t *tnp;
 int32 tni;

 /* DBG remove -- */
 if (offset < 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_MIPD_ENTER;
 /* only using for non-blocking statments for now */
 tnp->tncu.el_ndx = offset;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

extern int32 __gen_process_wire_enter(int32 offset)
{
 struct tn_t *tnp;
 int32 tni;

 /* DBG remove -- */
 if (offset < 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_PROCESS_WIRE_ENTER;
 /* only using for non-blocking statments for now */
 tnp->tncu.el_ndx = offset;
 tnp->tn_typ = TN_ADR;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = __inst_mod;
 return(tni);
}

/*
 * generate the instructions to load addr of net (var)
 *
 * new algorithm finds mod/task context from net by looking up in symbol
 * table during x86 lowering
 *
 * can compute at .so library load time with ptr in __comm file
 */
extern int32 __gen_ld_netbp(struct net_t *np)
{
 struct tn_t *tnp;
 int32 mdat_ti;
 size_t offset;
 int32 np_ti, is_scal, res_ti, ld_into_reg;
 struct mod_t *in_mdp;

 is_scal = (np->srep == SR_SCAL || np->srep == SR_SSCAL || 
            np->srep == SR_SCAL2S);
 /* AIV 08/26/10 - if narrow 2-state can just move into a register as well */
 /* since known not to have a b-part */
 if (is_scal) ld_into_reg = TRUE;
 else if (np->srep == SR_BIT2S && np->nwid <= WBITS)
  {
   ld_into_reg = TRUE;   
  }
 else ld_into_reg = FALSE;

 __get_nets_containing_sy(np, &(in_mdp));
 /* AIV 07/31/07 - using a global flag to indicate pointer values must be */
 /* used for loading nets - cannot use the __idp[] value */
 /* AIV 05/21/08 - for ports known inum value can used fixe location */
 if (__known_inum != -1) 
  {
   /* get the mdat this fixed location is based */
   mdat_ti = __gen_mdat_storage_area(in_mdp);
   offset = WRDBYTES*(__known_inum*in_mdp->mod_idata_siz);
   /* DBG remove -- */
   if (offset > (in_mdp->flatinum*in_mdp->mod_idata_siz*WRDBYTES)) 
     __misc_terr(__FILE__, __LINE__);
   /* ------ */

   /* get the fixed net offset for this inum */
   offset += (np->nva_ofs*WRDBYTES);
   np_ti = __con_adradd_insn(np->srep, np->nwid, mdat_ti, offset);
   /*  if scalar better to do the move */
   if (ld_into_reg)
    {
     if (is_scal)
      {
       np_ti = __move_srep_insn(TN_VAL, I_MOVA, np->srep, 1, AM_NDXREG, np_ti);
      }
     else
      {
       np_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, np->nwid, AM_NDXREG, 
         np_ti);
      }
     return(np_ti);
    }
   tnp = &(__tntab[np_ti]);
   tnp->idp_typ = COMLAB_IDPDAT;
   tnp->tn_typ = TN_ADR;
   if (np->ntyp == N_REAL) tnp->t_real = TRUE;
   else { if (np->n_signed) tnp->t_signed = TRUE; }
   return(np_ti);
  }

 if (__need_net_addr && !ld_into_reg)
  {
   return(__gen_ld_idp_netbp_addr(np));
  }

 __push_wrkitstk(in_mdp, 0);

 /* pass NULL for task pointer so T_ insn't part of net name */
 np_ti = __con_adradd_insn(np->srep, np->nwid, __idp_ti,
  np->nva_ofs*WRDBYTES);

 /* AIV 07/19/07 - must be in same mod otherwise need a new adradd */
 /* so set the tnsyrecp in_mdp field */
 /* DBG remove -- 
 {
  struct mod_t *tmp_mdp;
  tmp_mdp = __tntab[np_ti].tnsyrecp->in_mdp;
  if (tmp_mdp != NULL && tmp_mdp != in_mdp) 
    __misc_terr(__FILE__, __LINE__);
 }
  ----- */

 __tntab[np_ti].tnsyrecp->in_mdp = in_mdp;

 /* AIV - if real mark tn real flag as well */
 /* AIV LOOKATME - maybe should just make a new SR_REAL type */
 if (np->ntyp == N_REAL) __tntab[np_ti].t_real = TRUE;
 else { if (np->n_signed) __tntab[np_ti].t_signed = TRUE; }
 __tntab[np_ti].idp_typ = COMLAB_NETBP;
 /* AIV 01/09/08 - if rep is a scalar don't need address just move to reg */
 if (__need_net_addr && ld_into_reg)
  {
   if (is_scal)
    {
     res_ti = __move_srep_insn(TN_VAL, I_MOVA, np->srep, 1, AM_NDXREG, np_ti);
    }
   else
    {
     res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, np->nwid, AM_NDXREG, 
       np_ti);
    }
  }
 else res_ti = np_ti;
 __pop_wrkitstk();
 return(res_ti);
}

/*
 * load an address from the idp 
 */
extern int32 __gen_ld_idp_netbp_addr(struct net_t *np)
{
 int32 offset_ti, np_ti, idp_ti;
 struct mod_t *in_mdp;

 /* AIV 01/19/07 - if net is a parameter it isn't in mnets */
 /* a param can be loaded for more than 1st bsel */
 if (np->n_isaparam) __misc_terr(__FILE__, __LINE__);

 __get_nets_containing_sy(np, &(in_mdp));
 __push_wrkitstk(in_mdp, 0);

 /* pass NULL for task pointer so T_ insn't part of net name */
 offset_ti = __gen_cint_tn(np->nva_ofs*WRDBYTES);
//AIV FIXME - use SJM's new adradd splitting routines
//SJM 12/01/07 - LOOKATME? - think can just use ESI base here
//AIV? - 12/01/07 - what makes this turn out as value load rather the adrr
 idp_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, IDP_REG);
 np_ti = emit_adradd_addl(np->srep, np->nwid, idp_ti, offset_ti);

 /* AIV - if real mark tn real flag as well */
 /* AIV LOOKATME - maybe should just make a new SR_REAL type */
 if (np->ntyp == N_REAL) __tntab[np_ti].t_real = TRUE;
 else { if (np->n_signed) __tntab[np_ti].t_signed = TRUE; }
 __tntab[np_ti].idp_typ = COMLAB_NETBP;
 __pop_wrkitstk();
 return(np_ti);
}

/* * routine to generate a net addr mem label non storage tn
 *
 * also build and links on the memory area tag
 */
extern int32 __ld_netadr_tn(struct net_t *np)
{
 int32 tni, ndx;
 struct tn_t *tnp;
 struct mod_t *in_mdp;

 __get_nets_containing_sy(np, &(in_mdp));
 /* AIV 03/31/09 - this was failing for dumpvars - can just use in_mdp here */
 /* __inst_mod doesn't need to be set - for this code */
 /* DBG remove -- */
 // if (in_mdp != __inst_mod) __misc_terr(__FILE__, __LINE__);
 /* --- */

 np->is_loaded = TRUE;
 ndx = np - in_mdp->mnets;
 tni = __gen_tn(SR_MODADR, 0);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_NETADR;
 tnp->tncu.el_ndx = ndx;
 tnp->tnsyrecp = (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
 tnp->tnsyrecp->in_mdp = in_mdp;
 tnp->tnsyrecp->tfm_syp = (struct sy_t *) np;
 tnp->tn_typ = TN_ADR;
 return(tni);
}

/*
 * load storage area for dce schd tev idp offset location
 */
extern int32 __gen_dce_schd_tev(struct delctrl_t *dctp)
{
 int32 schd_tev_ti;

 /* AIV 03/03/09 - if merged and doesn't need thread just use header idp */
 /* area for the header fg tev_t */
 if (!dctp->needs_thread && dctp->head_dctp != NULL) 
  {
   dctp = dctp->head_dctp;
  }

 /* pass NULL for task pointer so T_ insn't part of net name */
 schd_tev_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
  dctp->dceschd_tev_ofs*WRDBYTES);
 __tntab[schd_tev_ti].idp_typ = COMLAB_DCESCH_TEVS;
 return(schd_tev_ti);
}

/*
 * load static memory to replace dce_epxr->bp 
 */
extern int32 __gen_dce_expr_bp(struct dcevnt_t *dcep)
{
 int32 expr_bp_ti;
 struct itree_t *itp;
 struct mod_t *mdp;

 /* AIV 02/20/07 - if upxmr or down xmr get the target mod */
 /* AIV 03/01/07 - rooted must be linked with its containing mod */
 /* AIV 08/08/09 - shouldn't this be pushed from v_bbgen2.c ????? */
 /* DBG remove -- */
 if (dcep->dce_xmrtyp == XNP_UPXMR || dcep->dce_xmrtyp == XNP_DOWNXMR)
  {
   mdp = dcep->dceu.dcegrp->targmdp;
   //if (mdp != __inst_mod) __misc_terr(__FILE__, __LINE__);
  }
 else if (dcep->dce_xmrtyp == XNP_RTXMR)
  {
   /* AIV 01/26/12 - this should be using itp - not yet converted to idp */
   itp =  dcep->dce_matchu.itp;
   mdp = itp->itip->imsym->el.emdp;
   //if (mdp != __inst_mod) __misc_terr(__FILE__, __LINE__);
  }
 else mdp = __inst_mod;
 /* ------------ */
 __push_wrkitstk(mdp, 0);

 /* pass NULL for task pointer so T_ insn't part of net name */
 expr_bp_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
  dcep->dce_expr->expr_ofs*WRDBYTES);
 __tntab[expr_bp_ti].idp_typ = COMLAB_DCEEXPR_BP;
 __pop_wrkitstk();
 return(expr_bp_ti);
}

/*
 * generate a global static memory for conta schedule storage
 */
extern int32 __gen_conta_schbp_tn(struct conta_t *cap, int32 srtyp)
{
 int32 schd_drv_ti;

 /* DBG remove -- */
 if (cap->schd_drv_ofs == 0) __misc_terr(__FILE__, __LINE__);
 if (srtyp != SR_VEC && srtyp != SR_BIT2S) __misc_terr(__FILE__, __LINE__);
 /* ----- */


 schd_drv_ti = __con_adradd_insn(srtyp, cap->lhsx->szu.xclen, __idp_ti,
  cap->schd_drv_ofs*WRDBYTES);
 __tntab[schd_drv_ti].idp_typ = COMLAB_CONTA_DRVBP;
 return(schd_drv_ti);
}

/*
 * generate a global static memory for conta drv storage
 */
extern int32 __gen_conta_drvbp_tn(struct conta_t *cap, int32 srtyp)
{
 int32 drv_ti;

 /* DBG remove -- */
 if (cap->ca_drv_ofs == 0) __misc_terr(__FILE__, __LINE__);
 if (srtyp != SR_VEC && srtyp != SR_BIT2S) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 drv_ti = __con_adradd_insn(srtyp, cap->lhsx->szu.xclen, __idp_ti, 
  cap->ca_drv_ofs*WRDBYTES);
 __tntab[drv_ti].idp_typ = COMLAB_CONTA_DRVBP;
 return(drv_ti);
}

/*
 * generate a global static memory for non-blocking assign storage
 */
extern int32 __gen_nonblocking_bp_tn(struct st_t *stp, int32 srep, 
 int32 is_real)
{
 int32 nb_ti;
 struct expr_t *lhsx;

 /* DBG remove -- */
 if (stp->rhs_idp_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 lhsx = stp->st.spra.lhsx;
 nb_ti = __con_adradd_insn(srep, lhsx->szu.xclen, __idp_ti, 
  stp->rhs_idp_ofs*WRDBYTES);
 /* AIV 10/15/10 - need to mark if real flag */
 if (is_real) __tntab[nb_ti].t_real = TRUE;
 __tntab[nb_ti].idp_typ = COMLAB_NB_BP;
 return(nb_ti);
}

/*
 * generate a global static memory for dctrl proca to store rhs value 
 */
extern int32 __gen_pd_rhsbp_tn(struct st_t *stp, int32 srep, int32 is_real)
{
 int32 pd_rhs_ti;
 struct expr_t *lhsx;

 /* DBG remove -- */
 if (stp->rhs_idp_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 lhsx = stp->st.spra.lhsx;
 pd_rhs_ti = __con_adradd_insn(srep, lhsx->szu.xclen, __idp_ti, 
  stp->rhs_idp_ofs*WRDBYTES);
 /* AIV 10/15/10 - need to mark if real flag */
 if (is_real) __tntab[pd_rhs_ti].t_real = TRUE;
 __tntab[pd_rhs_ti].idp_typ = COMLAB_PD_RHSBP;
 return(pd_rhs_ti);
}

/*
 * generate a global static memory for the repeat counter
 */
extern int32 __gen_repeat_bp_tn(struct st_t *stp)
{
 int32 rep_ti;

 /* pass NULL for task pointer so T_ insn't part of net name */
 rep_ti = __con_adradd_insn(SR_CINT, WBITS, __idp_ti, 
  stp->st.srpt.reptmp_ofs*WRDBYTES);
 __tntab[rep_ti].idp_typ = COMLAB_REP_BP;
 return(rep_ti);
}

/*
 * routine to generate a dce of a net's prevval with offset non storrage tn
 *
 * also build and links on the memory area tag
 */
extern int32 __gen_dce_prevval_tn(struct dcevnt_t *dcep, int32 blen)
{
 int32 prevval_ti, srep;
 struct net_t *np;

 /* DBG remove -- */
 if (dcep->prevval_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 np = dcep->dce_np;
 /* pass NULL for task pointer so T_ insn't part of net name */
 if (np->n_isarr)
  {
   if (np->nwid == 1) srep = np->srep;
   else srep = SR_VEC;
  }
 else srep = np->srep;

 prevval_ti = __con_adradd_insn(srep, blen, __idp_ti, 
  dcep->prevval_ofs*WRDBYTES);
 __tntab[prevval_ti].idp_typ = COMLAB_DCEPREV;
 return(prevval_ti);
}

/*
 * gen a c type int tn name (as if there was a load)
 *
 * notice this is a c int type literal so no mem area tag
 */
//SJM? - need to search so for a given int val, always return same tni
extern int32 __gen_cint_tn(word32 w)
{
 int32 tni;
 struct tn_t *tnp;
 struct tn_dup_t *tndup;

 tndup = __find_add_dup_tn(__cint_dup_tn_tree, w);

 /* case 1: found dup - just return the tni - w tn already generated */
 if (!__avl_node_is_new) return(tndup->tni);

 tni = __gen_tn(SR_CINT, WBITS);
 tnp = &(__tntab[tni]);
 tnp->tn_typ = TN_VAL;
 tnp->comlab_typ = COMLAB_CINT;
 tnp->tncu.tn_cint = w;
 tndup->tni = tni;
 return(tni);
}

/*
 * routine to generate a contab index mem label reference
 *
 * SJM 09/23/06 - NEW ALGORITHM - gens cint unless IS, b part or wide a part
 */
extern int32 __gen_contab_tn(int32 ctab_ndx, int32 blen, int32 is_form,
 int32 is_signed, int32 is_real, int32 srtyp)  
{
 int32 tni;
 struct tn_t *tnp;
 struct tn_dup_t *tndup;

//SJM? - NO I DON'T THINK SO - JUST ONE PLACE
//AIV FIXME - need to match sign/real
//find dup needs to check it the tmp is to be signed or not 
//SJM FIXME?????
 tndup = __find_add_dup_tn(__contab_dup_tn_tree, ctab_ndx);

 /* case 1: found dup - just return the tni - it is built */
 if (!__avl_node_is_new)
  {
//AIV FIXME - temporary fix if the tmps must match these flags
//__find_add_dup_tn needs to be fixed to handle these flags for consts
   tnp = &(__tntab[tndup->tni]);
   if (tnp->t_signed != is_signed) goto add_new_tmp;
   if (tnp->t_real != is_real) goto add_new_tmp;
   if (tnp->conadr_is_is != is_form) goto add_new_tmp;
   if (tnp->srtyp != srtyp) goto add_new_tmp;
   /* AIV 09/17/08 - lengths of tmps need to be that of passed blen */
   if (tnp->tnwid != blen) goto add_new_tmp;
   return(tndup->tni);
  }

add_new_tmp:
 /* case 2: must allocate new one and set it */
 tni = __gen_tn(srtyp, blen);
 tnp = &(__tntab[tni]);
 tnp->comlab_typ = COMLAB_CONADR;
 tnp->conadr_is_is = is_form;
 tnp->tncu.ctab_ndx = ctab_ndx;
 tnp->tn_typ = TN_ADR;
 tnp->t_signed = is_signed;
 tnp->t_real = is_real;
 tndup->tni = tni;
 return(tni);
}

/*
 * ROUTINES TO GEN ADRADS OR REPLACE WITH MEM LABELS
 */

/*
 * wrapper routine to gen adradd insn - like eval_insn routine except
 * probably will not need to gen any insns
 *
 * SJM 11/28/07 - first step in moving to amode instead of tn's split
 * into constant and var cases
 *
 * optimization code may decompose tn's on the stack into regs if
 * not used in a leal
 *
 * during generation of addr add result tns (in the amode), if tag parent tni
 * set, must gen the parent's base label (if comlab not none) plus the
 * result's offset
 *
 * notice adr add is an intermediate level insn so op1 but not op2 can be wide
 */
extern int32 __con_adradd_insn(int32 srep, int32 blen, int32 op1_ti,
 size_t bytofs)
{
 struct tn_t *op1tnp, *rtnp; 
 int32 res_apti, cint_ti, par_ti; 
 size_t offset;
 struct adradd_dup_t *adraddp;

 /* case 1: second operand of adr add is constant - most common */
 op1tnp = &(__tntab[op1_ti]);
 if (op1tnp->tn_typ == TN_ADR && op1tnp->comlab_typ == COMLAB_NONE)
  {
   cint_ti = __gen_cint_tn(bytofs);
   res_apti = emit_adradd_addl(srep, blen, op1_ti, cint_ti);
   return(res_apti);
  }

 if (op1tnp->tag_parent_tni != -1)
  {
   /* AIV 05/03/07 - make this legal for now all code should be able to */
   /* handle a zero offset correctly this savings having to catch 0 */
   /* offsets everywhere */
   /* DBG remove --
   if (op1tnp->child_tag_offset <= 0) __misc_terr(__FILE__, __LINE__);
    --- */

   par_ti = op1tnp->tag_parent_tni;
   offset = op1tnp->child_tag_offset + bytofs;
  } 
 else
  {
   /* DBG remove -- */
   if (op1tnp->child_tag_offset != 0) __misc_terr(__FILE__, __LINE__);
   /* --- */

   par_ti = op1_ti; 
   offset = bytofs;
  }

 /* AIV 01/26/07 - was generating a new tmp everytime */
 /* now searches for matching adradd tmp */
 adraddp = find_addradd_tn(srep, blen, par_ti, offset);
 /* if not new just return old res ti */
 if (!__avl_node_is_new)
  {
   /* DBG remove -- */
   if (srep != adraddp->srep) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   return(adraddp->res_ti);
  }

 /* generate a new adradd result and set node res_ti */ 
 res_apti = __gen_tn(srep, blen);
 adraddp->res_ti = res_apti;
 __adradd_child_tree->num_nodes++;

 op1tnp = &(__tntab[op1_ti]);
 rtnp = &(__tntab[res_apti]);

 /* AIV 04/26/07 - if svec adradd must mark */
 if (srep == SR_SVEC)
  {
   rtnp->svec_adr_add = TRUE;
   op1tnp->svec_adr_add = TRUE;
  }

 if (op1tnp->tag_parent_tni != -1)
  {
   /* AIV 05/03/07 - make this legal for now all code should be able to */
   /* handle a zero offset correctly this savings having to catch 0 */
   /* offsets everywhere */
   /* DBG remove -- 
   if (op1tnp->child_tag_offset <= 0) __misc_terr(__FILE__, __LINE__);
   --- */

   rtnp->tag_parent_tni = op1tnp->tag_parent_tni;
   rtnp->child_tag_offset = op1tnp->child_tag_offset + bytofs;
  }
 else
  {
   /* DBG remove -- */
   if (op1tnp->child_tag_offset != 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
     
   rtnp->tag_parent_tni = op1_ti; 
   rtnp->child_tag_offset = bytofs;
  }
 /* SJM 10/11/06 - result tn type (addr or val) must be same as op1's */
 rtnp->tn_typ = op1tnp->tn_typ;
 rtnp->comlab_typ = op1tnp->comlab_typ;
 rtnp->tncu = op1tnp->tncu;
 if (op1tnp->tnsyrecp != NULL)
  {
   rtnp->tnsyrecp = 
    (struct tn_syadr_t *) __my_malloc(sizeof(struct tn_syadr_t));
   *rtnp->tnsyrecp = *op1tnp->tnsyrecp;
  }
 else rtnp->tnsyrecp = NULL;
 return(res_apti);   
}

/*
 * wrapper routine to gen adradd insn - variable case that needs to
 * generate the add insns
 */
extern int32 __var_adradd_insn(int32 srep, int32 blen, int32 op1_ti,
 int32 op2_ti)
{
 int32 res_apti;

 /* SJM 11/13/06 - NEW CONVENTION - must never see wider than WBITS in */
 /* machine insns - only ASL wrappers and intermediate (copy?) can be wide */
 if (__tntab[op2_ti].tnwid > WBITS) __misc_terr(__FILE__, __LINE__);

 /* DBG remove -- */
 if (__is_constant(op2_ti)) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* case 2nd operand of adradd is variable */
 res_apti = emit_adradd_addl(srep, blen, op1_ti, op2_ti);

 /* AIV 04/27/07 - if strength add and strength is wider than one word  */
 /* need to mark the flag to later spill reg wider than one word  */
 /* LOOKATME - need to have reg alloc take all tmps - wouldn't need this */
 if (srep == SR_SVEC && __tntab[res_apti].tnwid > WRDBYTES)
  {
   __tntab[res_apti].svec_adr_add = TRUE;
  }
 return(res_apti);
}

/*
 * emit the adr add add when needed and also the load effective adr if needed
 *
 * this is a special case emit than can only be called from bbgen 
 */
static int32 emit_adradd_addl(int32 srep, int32 blen, int32 op1_ti, 
 int32 op2_ti)
{
 int32 res_ti, r1_ti;

 /* first arg must be a tmp nam reg */
 if (__tntab[op1_ti].tn_typ != TN_ADR)
  {
   /* case 1: op1 is a tn value */
   if (__tntab[op2_ti].tn_typ == TN_ADR) __misc_terr(__FILE__, __LINE__);

   r1_ti = leal_insn(AM_REG, op1_ti);
   res_ti = eval_srep_insn(TN_ADR, I_ADDL, srep, blen, AM_REG, r1_ti,
    AM_REG, op2_ti);
  }
 else
  {
   /* case 2: op1 is a tn address */
   res_ti = eval_srep_insn(TN_ADR, I_ADDL, srep, blen, AM_REG, op1_ti, 
    AM_REG, op2_ti);
  }
 return(res_ti);
}

/*
 * ROUTINES TO EVALUATE CONSTANTS ALSO FOR PARTIALLY KNOWN VALUE TRACKING
 */

/*
 * routine to evaluate constant (or know something about) expressions  
 * and track result value
 *
 * if save tracked false, for simple constant folding and therefore
 * know one operand must be constant and fit in wordl
 *
 * AIV 11/19/06 - MAYBE BUG HERE - see narrow as machine insns but 
 *                that does not match verilog narrower than 32
 * SJM 11/27/06 - for value tracking in bbopt, does not hurt to return 
 *                a cint tni since just gets the value - but maybe should
 *                return the int32 value
 */
static int32 eval_con_oneword_binop(int32 opcod, int32 blen, int32 op1_ti,
 int32 op2_ti)
{
 int32 cint_ti, op1_con, op2_con;
 word32 aval1, aval2, cval;
 long sgn_aval1, sgn_aval2;

 /* identify and extract the constant operands */ 
 op1_con = op2_con = FALSE;
 aval1 = aval2 = -1;
 if (__is_constant(op1_ti))
  { 
   op1_con = TRUE;
   aval1 = __get_wrd_con_val(op1_ti);
   /* SJM 11/19/06 - b part wrong for child tn's since may need b parts */
   /* here which go in first word (i.e. aval) */
  }
 else op1_con = FALSE;

 if (__is_constant(op2_ti))
  { op2_con = TRUE; aval2 = __get_wrd_con_val(op2_ti); }
 else op2_con = FALSE;

 cval = 0;
 switch (opcod) {
  case I_ADDL:
   if (op1_con && op2_con) { cval = aval1 + aval2; break; }
   else
    {
     if (op1_con) { if (aval1 == 0) return(op2_ti); }
     else { if (aval2 == 0) return(op1_ti); }
    }
   return(-1);
  case I_ADCL:
   /* AIV 01/21/10 cannot just chekc it one op is zero because do not */
   /* know the carry value */
   return(-1);
  case I_SUBL:
   if (op1_con && op2_con) { cval = aval1 - aval2; break; }
   /* -<var> needs simpler insn that is added later */
   if (op2_con) { if (aval2 == 0) return(op1_ti); }
   return(-1);
  case I_IMULL:
   if (op1_con && op2_con) { cval = aval1*aval2; break; }
   if (op1_con) 
    {
     if (aval1 == 0) { cval = 0; break; }
     if (aval1 == 1) return(op2_ti);
     return(-1);
    }
   else 
    {
     if (aval2 == 0) { cval = 0; break; }
     if (aval2 == 1) return(op1_ti);
     return(-1);
    }
   return(-1);
  case I_DIVL:
   if (op1_con && op2_con) { cval = aval1/aval2; break; }
   if (op1_con)
    { 
     if (aval1 == 0) { cval = 0; break; }
    }
   else { if (aval2 == 1) return(op1_ti); }
   return(-1);
  case I_SGN_DIVL:
   sgn_aval1 = (long) aval1;
   sgn_aval2 = (long) aval2;
   if (op1_con && op2_con) { cval = sgn_aval1/sgn_aval2; break; }
   if (op1_con)
    { 
     if (sgn_aval1 == 0) { cval = 0; break; }
    }
   else { if (sgn_aval2 == 1) return(op1_ti); }
   return(-1);
  case I_MODL: 
   if (op1_con && op2_con) { cval = aval1 % aval2; break; }
   if (op1_con)
    { 
     /* AIV 12/20/06 - 0 % anything is zero */
     if (aval1 == 0) { cval = 0; break; }
    }
   else
    {
     if (aval2 == 1) { cval = 0; break; }
    }
   return(-1);
  case I_SGN_MODL:
   sgn_aval1 = (long) aval1;
   sgn_aval2 = (long) aval2;
   if (op1_con && op2_con) { cval = sgn_aval1 % sgn_aval2; break; }
   if (op1_con)
    { 
     if (sgn_aval1 == 0) { cval = 1; break; }
    }
   else
    {
     if (sgn_aval2 == 1) { cval = 0; break; }
    }
   return(-1);
  case I_ORL:
   if (op1_con && op2_con) { cval = aval1 | aval2; break; }
   if (op1_con)
    { 
     if (aval1 == 0) return(op2_ti);
     if (aval1 == __masktab[blen]) { cval = __masktab[blen]; break; }
    }
   else
    {
     if (aval2 == 0) return(op1_ti);
     if (aval2 == __masktab[blen]) { cval = __masktab[blen]; break; }
    }
   return(-1);
  case I_ANDL:
   if (op1_con && op2_con) { cval = aval1 & aval2; break; }
   if (op1_con)
    { 
     if (aval1 == 0) { cval = 0; break; }
     if (aval1 == __masktab[blen]) return(op2_ti);
    }
   else
    {
     if (aval2 == 0) { cval = 0; break; }
     if (aval2 == __masktab[blen]) return(op1_ti);
    }
   return(-1);
  case I_XORL:
   if (op1_con && op2_con) { cval = aval1 ^ aval2; break; }
   if (op1_con) { if (aval1 == 0) return(op2_ti); }
   else { if (aval2 == 0) return(op1_ti); }
   return(-1);
  case I_SHLL:
   /* should never produce code to shift a 32 bit thing more than 32 bits */
   /* DBG remove -- */
   if (op1_con && aval1 >= WBITS) __misc_terr(__FILE__, __LINE__);
   /* -- */

   /* following x86 machine insn order src (1st opand) is the shift amt */
   if (op1_con && op2_con) { cval = (aval2 << aval1); break; } 
   if (op2_con)
    {
     if (aval2 == 0) { cval = 0; break; }
    }
   else
    {
     if (aval1 == 0) return(op2_ti);
     /* notice too wide shift amount already handled in insn gen */
    }
   return(-1);
  case I_SALL:
   sgn_aval1 = (long) aval1;
   sgn_aval2 = (long) aval2;
   /* following x86 machine insn order src (1st opand) is the shift amt */
   if (op1_con && op2_con) { cval = (sgn_aval2 << sgn_aval1); break; } 
   if (op2_con)
    {
     if (sgn_aval2 == 0) { cval = 0; break; }
    }
   else
    {
     if (sgn_aval1 == 0) return(op2_ti);
     /* notice too wide shift amount already handled in insn gen */
    }
   return(-1);
  case I_SHRU:   
  case I_SARU:
   /* AIV 01/05/09 - don't think these special case should be scene here */
   __case_terr(__FILE__, __LINE__);
   break;
  case I_SHRL:   
   /* should never produce code to shift a 32 bit thing more than 32 bits */
   /* DBG remove -- */
   if (op1_con && aval1 >= WBITS) __misc_terr(__FILE__, __LINE__);
   /* -- */

   /* SJM 11/19/06 ???  - for signed not sure if decomposed or should */
   /* convert to 32 bit signed for folding */
   /* following x86 machine insn order src (1st opand) is the shift amt */
   if (op1_con && op2_con) { cval = (aval2 >> aval1); break; } 
   if (op2_con)
    {
     if (aval2 == 0) { cval = 0; break; }
    }
   else
    {
     if (aval1 == 0) return(op2_ti);
     /* notice too wide shift amount already handled in insn gen */
    }
   return(-1);
  case I_SARL:
   /* should never produce code to shift a 32 bit thing more than 32 bits */
   /* DBG remove -- */
   if (op1_con && aval1 >= WBITS) __misc_terr(__FILE__, __LINE__);
   /* -- */

   sgn_aval1 = (long) aval1;
   sgn_aval2 = (long) aval2;
   /* SJM 05/01/07 - this was wrongly a left shift */
   if (op1_con && op2_con) { cval = (sgn_aval2 >> sgn_aval1); break; } 

   if (op2_con)
    {
     if (sgn_aval2 == 0) { cval = 0; break; }
    }
   else
    {
     if (sgn_aval1 == 0) return(op2_ti);
     /* notice too wide shift amount already handled in insn gen */
    }
   return(-1);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 cint_ti = __gen_cint_tn(cval);
 return(cint_ti);
}

/*
 * version of eval one word bin op where know at least one arg is constant 
 * to see if it simplifies to a constant result
 *
 * BEWARE - guts of this version except for no tn's same as above routine
 *
 * SJM 01/14/07 - this is version for insn destination (out) value tracking
 * where do not have any tn's at this stage - value stored - converted to cint
 * later if needed
//SJM? - FIXME - for places where result is other varying operand
//               should change to movl 
 */
extern word32 __trk_eval_con_oneword_binop(int32 *resval, int32 opcod,
 int32 blen, int32 op1_con, word32 aval1, int32 op2_con, word32 aval2)
{
 word32 cval;
 long sgn_aval1, sgn_aval2;

 cval = 0;
 switch (opcod) {
  case I_ADDL:
   if (op1_con && op2_con) { cval = aval1 + aval2; break; }
   return(TRK_BOT_VARYING);
  case I_SUBL:
   if (op1_con && op2_con) { cval = aval1 - aval2; break; }
   return(TRK_BOT_VARYING);
  case I_IMULL:
   if (op1_con && op2_con) { cval = aval1*aval2; break; }
   if (op1_con) 
    {
     if (aval1 == 0) { cval = 0; break; }
    }
   else 
    {
     if (aval2 == 0) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_DIVL:
   if (op1_con && op2_con) { cval = aval1/aval2; break; }
   if (op1_con)
    { 
     if (aval1 == 0) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_SGN_DIVL:
   sgn_aval1 = (long) aval1;
   sgn_aval2 = (long) aval2;
   if (op1_con && op2_con) { cval = sgn_aval1/sgn_aval2; break; }
   if (op1_con)
    { 
     if (sgn_aval1 == 0) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_MODL: 
   if (op1_con && op2_con) { cval = aval1 % aval2; break; }
   if (op1_con)
    { 
     /* AIV 12/20/06 - 0 % anything is zero */
     if (aval1 == 0) { cval = 0; break; }
    }
   else
    {
     if (aval2 == 1) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_SGN_MODL:
   sgn_aval1 = (long) aval1;
   sgn_aval2 = (long) aval2;
   if (op1_con && op2_con) { cval = sgn_aval1 % sgn_aval2; break; }
   if (op1_con)
    { 
     if (sgn_aval1 == 0) { cval = 1; break; }
    }
   else
    {
     if (sgn_aval2 == 1) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_ORL:
   if (op1_con && op2_con) { cval = aval1 | aval2; break; }
   if (op1_con)
    { 
     if (aval1 == __masktab[blen]) { cval = __masktab[blen]; break; }
    }
   else
    {
     if (aval2 == __masktab[blen]) { cval = __masktab[blen]; break; }
    }
   return(TRK_BOT_VARYING);
  case I_ANDL:
   if (op1_con && op2_con) { cval = aval1 & aval2; break; }
   if (op1_con)
    { 
     if (aval1 == 0) { cval = 0; break; }
    }
   else
    {
     if (aval2 == 0) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_XORL:
   if (op1_con && op2_con) { cval = aval1 ^ aval2; break; }
   return(TRK_BOT_VARYING);
  case I_SHLL:
   /* should never produce code to shift a 32 bit thing more than 32 bits */
   /* SJM 04/06/07 - this is legal c so can just fold and does produce */
   /* at least same result as the intrepreter - folding of wide legal */
   /* DBG remove -- */
   //?? if (op1_con && aval1 >= WBITS) __misc_terr(__FILE__, __LINE__);
   /* -- */

   /* following x86 machine insn order src (1st opand) is the shift amt */
   if (op1_con && op2_con) { cval = (aval2 << aval1); break; } 
   if (op2_con)
    {
     if (aval2 == 0) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_SALL:
   sgn_aval1 = (long) aval1;
   sgn_aval2 = (long) aval2;
   /* following x86 machine insn order src (1st opand) is the shift amt */
   if (op1_con && op2_con) { cval = (sgn_aval2 << sgn_aval1); break; } 
   if (op2_con)
    {
     if (sgn_aval2 == 0) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_SHRU:   
  case I_SARU:
   /* AIV 01/05/09 - don't think these special case should be scene here */
   __case_terr(__FILE__, __LINE__);
   break;
  case I_SHRL:   
   /* should never produce code to shift a 32 bit thing more than 32 bits */
   /* SJM 04/06/07 - this is legal c so can just fold and does produce */
   /* at least same result as the intrepreter - folding of wide legal */
   /* DBG remove -- */
   //?? if (op1_con && aval1 >= WBITS) __misc_terr(__FILE__, __LINE__);
   /* -- */

   /* SJM 11/19/06 ???  - for signed not sure if decomposed or should */
   /* convert to 32 bit signed for folding */
   /* following x86 machine insn order src (1st opand) is the shift amt */
   if (op1_con && op2_con) { cval = (aval2 >> aval1); break; } 
   if (op2_con)
    {
     if (aval2 == 0) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
  case I_SARL:
   /* should never produce code to shift a 32 bit thing more than 32 bits */
   /* DBG remove -- */
   if (op1_con && aval1 >= WBITS) __misc_terr(__FILE__, __LINE__);
   /* -- */

   sgn_aval1 = (long) aval1;
   sgn_aval2 = (long) aval2;
   /* SJM 05/01/07 - this was wrongly a left shift */
   if (op1_con && op2_con) { cval = (sgn_aval2 >> sgn_aval1); break; } 
   if (op2_con)
    {
     if (sgn_aval2 == 0) { cval = 0; break; }
    }
   return(TRK_BOT_VARYING);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 *resval = cval;
 return(TRK_CON);
}

/*
 * ROUTINES TO IMPLEMENT SETS (AVL TREES) SO DUPLICATED GEN TNS CAN BE REUSED
 */

/*
 * find bblk element that is defined in tn (in flow graph) set (avl tree)
 * if found return, else add 
 */
extern struct bblk_t *__find_add_dup_bblk(struct avlhd_t *avlhp,
 struct bblk_t *bbp)
{
 struct avlnode_t *avlp;

 if (avlhp->num_nodes == 0)
  {
   /* case 1: tree is empty - since doesn't exist need to fill tree head */ 
   avlhp->num_nodes = 1;
   avlhp->avl_cmp = bblk_node_cmp;
   avlhp->avl_alloc = bblk_dup_node_alloc;
   avlhp->avl_root = bblk_dup_node_alloc((void *) bbp);
   __avl_node_is_new = TRUE;
   return((struct bblk_t *) avlhp->avl_root->valp);
  }

 __avl_node_is_new = FALSE;
 /* if can't find, inserts new node in avl tree, fills and sets node is new */
 avlp = __avltfind((void *) bbp, avlhp);
 return((struct bblk_t *) avlp);
}

/*
 * addr compare for duplicated bblk tree
 *
 * SJM 12/26/06 - ordering by bblk addr - maybe should use seqno or rpo number
 */
static cmpsword bblk_node_cmp(const void *valp, const struct avlnode_t *nodp)
{
 return((struct bblk_t *) valp - (struct bblk_t *) nodp->valp);
}

/*
 * avl tree alloc tree element that is just a bblk (in a flow graph* 
 * do not need record since only need addr of bblk
 */
static struct avlnode_t *bblk_dup_node_alloc(void *bbp)
{
 struct avlnode_t *nodp;

 nodp = __alloc_avlnode(bbp);
 return(nodp);
}

/*
 * find bblk element that is defined in tn (in flow graph) set (avl tree)
 * if found return, else add 
 */
extern struct bblk_t *__find_add_conflct_tn(struct avlhd_t *avlhp, int32 tni)
{
 struct avlnode_t *avlp;

 if (avlhp->num_nodes == 0)
  {
   /* case 1: tree is empty - since doesn't exist need to fill tree head */ 
   avlhp->num_nodes = 1;
   avlhp->avl_cmp = conflct_tn_node_cmp;
   avlhp->avl_alloc = conflct_tn_node_alloc;
   avlhp->avl_root = conflct_tn_node_alloc((void *) (word32) tni);
   __avl_node_is_new = TRUE;
   return((struct bblk_t *) avlhp->avl_root->valp);
  }

 __avl_node_is_new = FALSE;
 /* if can't find, inserts new node in avl tree, fills and sets node is new */
 avlp = __avltfind((void *) (word32) tni, avlhp);
 return((struct bblk_t *) avlp);
}

/*
 * addr compare for duplicated bblk tree
 *
 * SJM 12/26/06 - ordering by bblk addr - maybe should use seqno or rpo number
 */
static cmpsword conflct_tn_node_cmp(const void *valp,
 const struct avlnode_t *nodp)
{
 return((cmpsword) valp - (cmpsword) nodp->valp);
}

/*
 * avl tree alloc tree element that is just a bblk (in a flow graph* 
 * do not need record since only need addr of bblk
 */
static struct avlnode_t *conflct_tn_node_alloc(void *bbp)
{
 struct avlnode_t *nodp;

 nodp = __alloc_avlnode(bbp);
 return(nodp);
}

/*
 * find in inst mod index net list element (comm area) duplicated tn avl tree
 *
 * if found return, else add 
 * this is for case where only the module element index is used because
 * all of the tn type are in the current inst mod
 */
extern struct tn_dup_t *__find_add_dup_tn(struct avlhd_t *avlhp, word32 ndx)
{
 struct tn_dup_t *tndup, tmp_tndup;
 struct avlnode_t *avlp;

 tmp_tndup.nlo_ndx = ndx;
 tmp_tndup.tni = -1;
 if (avlhp->num_nodes == 0)
  {
   /* case 1: tree is empty - since doesn't exist need to fill tree head */ 
   avlhp->num_nodes = 1;
   avlhp->avl_cmp = tn_node_cmp;
   avlhp->avl_alloc = tn_dup_node_alloc;
   avlhp->avl_root = tn_dup_node_alloc(&(tmp_tndup));
   tndup = (struct tn_dup_t *) avlhp->avl_root->valp;
   __avl_node_is_new = TRUE;
   return(tndup);
  }

 __avl_node_is_new = FALSE;
 /* if can't find, inserts new node in avl tree, fills and sets node is new */
 avlp = __avltfind(((void *) &(tmp_tndup)), avlhp);
 tndup = (struct tn_dup_t *) avlp->valp;
 return(tndup);
}

/*
 * addr compare for duplicated gen net list (comm) element tns 
 */
static cmpsword tn_node_cmp(const void *valp, const struct avlnode_t *nodp)
{
 struct tn_dup_t *p1, *p2;

 p1 = (struct tn_dup_t *) valp;
 p2 = (struct tn_dup_t *) nodp->valp;
 return(p1->nlo_ndx - p2->nlo_ndx);
}

/*
 * avl tree alloc for net list (comm area) tn dup record
 *
 * this allocates a new nodes and fills it with passed tn dup record
 */
static struct avlnode_t *tn_dup_node_alloc(void *tndup)
{
 struct tn_dup_t *newp, *oldp;
 struct avlnode_t *nodp;

 oldp = (struct tn_dup_t *) tndup;
 newp = (struct tn_dup_t *) __my_malloc(sizeof(struct tn_dup_t));
 *newp = *oldp;
 nodp = __alloc_avlnode((void *) newp);
 return(nodp);
}

/*
 * avl tree free for net list (comm area) tn dup record
 */
extern void __tn_dup_node_free(void *tndup)
{
 __my_free(tndup, sizeof(struct tn_dup_t));
}

/*
 * add a iconn info struct to a tree sorted by the up_lhsx to later generate
 * one flow graph
 */
extern struct np_iconn_t *__add_np_iconn_expr(struct net_pin_t *npp, 
 struct expr_t *up_rhsx)
{
 struct np_iconn_t *npicp;

 npicp = find_add_np_iconn_expr(__np_iconn_dup_tn_tree, up_rhsx, npp);
 if (!__avl_node_is_new)
  {
   return(npicp);
  }
 npicp->iconn_ndx = ++__iconn_seq_no;
 npicp->fgp = NULL;
 npicp->up_rhsx = up_rhsx;
 npicp->npp = npp;
 return(npicp);
}


/*
 * find or add a iconn expr
 */
static struct np_iconn_t *find_add_np_iconn_expr(struct avlhd_t *avlhp,
 struct expr_t *up_rhsx, struct net_pin_t *npp)
{
 struct np_iconn_t *npicp, tmp_npic;
 struct avlnode_t *avlp;

 tmp_npic.up_rhsx = up_rhsx;
 tmp_npic.npp = npp;
 if (avlhp->num_nodes == 0)
  {
   /* case 1: tree is empty */
   avlhp->num_nodes = 1;
   avlhp->avl_cmp = npic_node_cmp;
   avlhp->avl_alloc = npic_node_alloc;
   avlhp->avl_root = npic_node_alloc(&(tmp_npic));
   npicp = (struct np_iconn_t *) avlhp->avl_root->valp;
   __avl_node_is_new = TRUE;
   return(npicp);
  }

 __avl_node_is_new = FALSE;
 /* if can't find, inserts new node in avl tree, fills and sets node is new */
 avlp = __avltfind(((void *) &(tmp_npic)), avlhp);
 npicp = (struct np_iconn_t *) avlp->valp;
 return(npicp);
}

/*
 * compare a iconn expr node
 */
static cmpsword npic_node_cmp(const void *valp, const struct avlnode_t *nodp)
{
 cmpsword cv;
 struct np_iconn_t *p1, *p2;

 p1 = (struct np_iconn_t *) valp;
 p2 = (struct np_iconn_t *) nodp->valp;
 /* AIV LOOKATME ???? */
 /* only sort by up rhsx expr for now */
 /* AIV 11/27/07 - need to cast the expr_ to int * to do the compare */
 cv = ((cmpsword *) p1->up_rhsx - (cmpsword *) p2->up_rhsx);
 return(cv);
}

/*
 * alloc a iconn expr node
 */
static struct avlnode_t *npic_node_alloc(void *tnsydup)
{
 struct np_iconn_t *newp, *oldp;
 struct avlnode_t *nodp;

 oldp = (struct np_iconn_t *) tnsydup;
 newp = (struct np_iconn_t *) __my_malloc(sizeof(struct np_iconn_t));
 *newp = *oldp;
 nodp = __alloc_avlnode((void *) newp);
 return(nodp);
}

/*
 * free a iconn expr node
 */
extern void __np_iconn_dup_node_free(void *nv)
{
 /* must free port flow graphs */
 __my_free(nv, sizeof(struct np_iconn_t));
}

/*
 * add a gate expr to an avl tree sorted by the expression
 */
extern struct gate_conta_t *__add_gate_expr(struct gate_t *gp, 
 struct net_pin_t *npp)
{
 struct gate_conta_t *gcp;
 struct expr_t *xp;

 /* DBG remove -- */
 if (npp->obnum > 1) __misc_terr(__FILE__, __LINE__);
 /* ----- */
 xp = gp->gpins[1];

 gcp = find_gate_expr(__gate_conta_dup_tn_tree, xp);

 if (!__avl_node_is_new)
  {
   return(gcp);
  }
 gcp->mdp = __inst_mod;
 gcp->npp = npp;
 gcp->fgp = NULL;
 gcp->gc_ndx = ++__gate_conta_seq_no;
 gcp->xp = xp;
 return(gcp);
}


/*
 * find/add a gate expression
 */
static struct gate_conta_t *find_gate_expr(struct avlhd_t *avlhp,
 struct expr_t *xp)
{
 struct gate_conta_t *gcp, tmp_gcp;
 struct avlnode_t *avlp;

 tmp_gcp.xp = xp;
 if (avlhp->num_nodes == 0)
  {
   /* case 1: tree is empty */
   avlhp->num_nodes = 1;
   avlhp->avl_cmp = gate_conta_node_cmp;
   avlhp->avl_alloc = gate_conta_node_alloc;
   /* AIV 08/11/08 - this was alloc with wrong routine */
   avlhp->avl_root = gate_conta_node_alloc(&(tmp_gcp));
   gcp = (struct gate_conta_t *) avlhp->avl_root->valp;
   __avl_node_is_new = TRUE;
   return(gcp);
  }

 __avl_node_is_new = FALSE;
 /* if can't find, inserts new node in avl tree, fills and sets node is new */
 avlp = __avltfind(((void *) &(tmp_gcp)), avlhp);
 /* AIV 08/11/08 - should inc the num nodes to be consistent */
 if (__avl_node_is_new) avlhp->num_nodes++;
 gcp = (struct gate_conta_t *) avlp->valp;
 return(gcp);
}

/*
 * compare a gate expression
 */
static cmpsword gate_conta_node_cmp(const void *valp, 
 const struct avlnode_t *nodp)
{
 cmpsword cv;
 struct gate_conta_t *p1, *p2;

 p1 = (struct gate_conta_t *) valp;
 p2 = (struct gate_conta_t *) nodp->valp;
 /* AIV LOOKATME ???? */
 /* only sort by up expr for now */
 /* AIV 11/10/08 - need to cast the expr_ to word * to do the compare */
 cv = ((cmpsword *) p1->xp - (cmpsword *) p2->xp);
 return(cv);
}

/*
 * allocate a gate expr
 */
static struct avlnode_t *gate_conta_node_alloc(void *tnsydup)
{
 struct gate_conta_t *newp, *oldp;
 struct avlnode_t *nodp;

 oldp = (struct gate_conta_t *) tnsydup;
 newp = (struct gate_conta_t *) __my_malloc(sizeof(struct gate_conta_t));
 *newp = *oldp;
 nodp = __alloc_avlnode((void *) newp);
 return(nodp);
}

/*
 * free a gate expression
 */
extern void __gate_conta_dup_node_free(void *gcp)
{
 __my_free(gcp, sizeof(struct gate_conta_t));
}
///////////////////////////////////////////////////////

/*
 * initialize the tn dupl finding avl trees (sets)
 *
 * since just creating the net list objects - do not need to load - much
 * better to create and put in tmp name table - can be operand of
 * our alpha/x86 style virtual machine insns 
 */
extern void __init_tn_dup_trees(void)
{
 __cint_dup_tn_tree = __allocinit_avlhd();
 __contab_dup_tn_tree = __allocinit_avlhd();
 /* AIV 10/06/08 - if code is inlined don't need seperate xpr fgs */
 if (!__inline_code)
  {
   __np_iconn_dup_tn_tree = __allocinit_avlhd();
   __gate_conta_dup_tn_tree = __allocinit_avlhd();
  }
}

/*
 * find an adradd node 
 */
static struct adradd_dup_t *find_addradd_tn(int32 srep, int32 blen,
 int32 par_ti, size_t offset)
{
 struct adradd_dup_t *adraddp, tmp_adradd;
 struct avlhd_t *avlhp;
 struct avlnode_t *avlp;

 tmp_adradd.srep = srep; 
 tmp_adradd.blen = blen;
 tmp_adradd.par_ti = par_ti;
 tmp_adradd.offset = offset;
 tmp_adradd.mdp = __inst_mod;

 avlhp = __adradd_child_tree;
 /* case 1: tree is empty */
 if (avlhp->num_nodes == 0)
  {
   avlhp->avl_cmp = tn_adradd_cmp;
   avlhp->avl_alloc = tn_adradd_node_alloc;
   avlhp->avl_root = tn_adradd_node_alloc(&(tmp_adradd));
   adraddp = (struct adradd_dup_t *) avlhp->avl_root->valp;
   __avl_node_is_new = TRUE;
   return(adraddp);
  }

 __avl_node_is_new = FALSE;
 /* if can't find, inserts new node in avl tree, fills and sets node is new */
 avlp = __avltfind(((void *) &(tmp_adradd)), avlhp);
 adraddp = (struct adradd_dup_t *) avlp->valp;
 return(adraddp);
}

/*
 * alloc an adradd node
 */
static struct avlnode_t *tn_adradd_node_alloc(void *adraddp)
{
 struct adradd_dup_t *newp, *oldp;
 struct avlnode_t *nodp;

 oldp = (struct adradd_dup_t *) adraddp;
 newp = (struct adradd_dup_t *) __my_malloc(sizeof(struct adradd_dup_t));
 *newp = *oldp;
 nodp = __alloc_avlnode((void *) newp);
 return(nodp);
}

/*
 * compare an adradd node
 */
static cmpsword tn_adradd_cmp(const void *valp, const struct avlnode_t *nodp)
{
 cmpsword cv;
 struct adradd_dup_t *p1, *p2;

 p1 = (struct adradd_dup_t *) valp;
 p2 = (struct adradd_dup_t *) nodp->valp;
 if ((cv = (p1->par_ti - p2->par_ti)) != 0) return(cv);
 if ((cv = (p1->offset - p2->offset)) != 0) return(cv);
 if ((cv = (p1->blen - p2->blen)) != 0) return(cv);
 /* AIV 02/26/07 - need to compare srep types as well */
 if ((cv = (p1->srep - p2->srep)) != 0) return(cv);
 /* AIV 09/26/07 - need to record the mdp it is in as well becuase of idp */
 /* offsets can be changed during run/comp time */
 /* AIV 11/10/08 - need to cast the expr_ to word * to do the compare */
 if ((cv = ((cmpsword *) p1->mdp - (cmpsword *) p2->mdp)) != 0) return(cv);
 return(cv);
}

/*
 * from an adradd node
 */
extern void __addr_add_dup_node_free(void *adraddp)
{
 __my_free(adraddp, sizeof(struct adradd_dup_t));
}

/*
 * ROUTINES TO EMIT X86/ALPHA VM INSNS AND ADD TO FORMAL TMP TABLE
 */
 
/*
 * wrapper to routine that emits asl call medium level insn and builds
 * the malloced table of tn indices
 */
static void emit_call_asl_func(int32 call_op, int32 nargs, ...)
{
 va_list va;

 va_start(va, nargs);
 emit_call_asl_funcandproc(call_op, TRUE, nargs, va);
 va_end(va);
}

static void emit_call_asl_proc(int32 call_op, int32 nargs, ...)
{
 va_list va;

 va_start(va, nargs);
 emit_call_asl_funcandproc(call_op, FALSE, nargs, va);
 va_end(va);
}

/*
 * routines to gen the ASL run time support library routines
 *
 * now actual x86 insns generated just before creating ascii assembly
 * from array of tn indices build here
 *
 * for both proc and func - caller passes flag
 */
static void emit_call_asl_funcandproc(int32 call_op, int32 is_func,
 int32 nargs, va_list va)
{
 int32 ai, tni, aslotyp; 
 struct tn_t *tnp;
 struct asl_def_t *arg_udtab, *audp;
 struct amode_t *amp;
 struct asl_info_t *aslp;

 /* SJM 11/01/06 - 0 arg asl calls also be funcs */ 
 if (nargs > 0)
  {
   aslp = __to_aslinfo_rec(call_op);

   arg_udtab = (struct asl_def_t *) __my_malloc(nargs*sizeof(struct asl_def_t));
   /* notice 0th array entry last arg so can easily push last first */
   /* i.e. for 4 args, arg 3 goes into position 0 */
   for (ai = 0; ai < nargs; ai++)
    {
     /* 04/03/07 - insn coded so order of the var args is 3,2,1,0 etc. */
     tni = va_arg(va, int32);
     /* but order in ausedefs and asl info rec tables is first arg first */
     audp = &(arg_udtab[nargs - ai - 1]);
     amp = &(audp->am_arg);
     aslotyp = aslp->asl_op_typ[nargs - ai - 1];

     set_asl_call_amode(amp, tni, aslotyp);
     audp->arg_src_defips = NULL;
     audp->arg_savchain_ips = NULL;
    }
   va_end(va);
  }
 else arg_udtab = NULL;

 if (is_func) nores_insn(I_CALL_ASLFUNC, AM_NONE, AM_IMM, call_op);
 else nores_insn(I_CALL_ASLPROC, AM_NONE, AM_IMM, call_op);

 /* AIV 10/25/06 - BEWARE !!!! - when expanding copies must set copy ip */
 /* since uses the normal nores insn mechanism */
 if (__copy_ip != NULL)
  {
   __copy_ip->extrau.asl_ausedefs = arg_udtab;
   __copy_ip->callasl_argnum = nargs;
  }
 else
  {
   __cur_bbp->itail->extrau.asl_ausedefs = arg_udtab;
   __cur_bbp->itail->callasl_argnum = nargs;
  }
   
 if (nargs > __cur_flowg->max_call_args) __cur_flowg->max_call_args = nargs;
 
 if (is_func)
  {
   /* AIV 08/01/06 - each func call must index a val num for AR_AX */
   /* SJM 10/17/06 - not needed for proc calls */
   tnp = &(__tntab[AR_AX]);
   tnp->st_into_ip = __cur_bbp->itail;
   tnp->valnum = ++__cur_valnum; 
  }
}

/*
 * set amode for asl call arguments from arg tn and asl info table values
 */
static void set_asl_call_amode(struct amode_t *amp, int32 arg_ti,
 int32 aslotyp)
{
 int32 amode;
 struct tn_t *arg_tnp;

 __init_amode(amp); 
 amode = -1;
 arg_tnp = &(__tntab[arg_ti]);
 /* case 1: literal int the only com lab case possible here */
 if (aslotyp == A_INT || aslotyp == A_NUM)
  {
   /* DBG remove -- */
   if (!__is_constant(arg_ti) && aslotyp == A_NUM)
    {
     __misc_terr(__FILE__, __LINE__);
    }
   /* --- */
   if (arg_tnp->tn_typ == TN_ADR) amp->amode = AM_NDXREG;
   else amp->amode = AM_REG;
   amp->am_tni = arg_ti;
   return;
  }

 /* case 2: pushing real */
 if (arg_tnp->t_real)
  {
   if (arg_tnp->tn_typ == TN_ADR) amp->amode = AM_NDXREG;
   else amp->amode = AM_REG;
   amp->am_tni = arg_ti;
   return;
  }

 /* check for new idp type - will eventually replace comlab types */
 if (arg_tnp->idp_typ != COMLAB_NONE)
  {
   /* SJM 07-26-07 - the fields inside netadr's and other objects now */
   /* are idp type nlo since they are invisivible magic addrs passed to asl */
   /* routines */
   if (arg_tnp->idp_typ == COMLAB_NETBP
    || arg_tnp->idp_typ == COMLAB_DCEPREV
    || arg_tnp->idp_typ == COMLAB_CONTA_DRVBP 
    || arg_tnp->idp_typ == COMLAB_PD_RHSBP
    || arg_tnp->idp_typ == COMLAB_PNCHG
    || arg_tnp->idp_typ == COMLAB_TEVP
    || arg_tnp->idp_typ == COMLAB_NB_BP
    || arg_tnp->idp_typ == COMLAB_IDPDAT)
    {
     amode = AM_REG; 
    }
   else __misc_terr(__FILE__, __LINE__);

   amp->amode = amode; 
   amp->am_tni = arg_ti;
   return;
  }

 /* case 3: a comm lab */ 
 if (arg_tnp->comlab_typ != COMLAB_NONE)
  {
   /* nlptr are always am_reg - never accessed as addr $ */
   if (__is_nlptr_comlab(arg_tnp->comlab_typ)) amode = AM_REG;
   else if (aslotyp == A_WPTR || aslotyp == A_RWPTR || aslotyp == A_RPTR)
    amode = AM_REG; 
   else if (aslotyp == A_INT) amode = AM_NDXREG;
   else { amode = AM_REG; __misc_terr(__FILE__, __LINE__); }
  
   amp->amode = amode; 
   amp->am_tni = arg_ti;
  }
 else
  {
   amp->amode = AM_REG;
   amp->am_tni = arg_ti;
  }
}

/*
 * AIV's way of checking that the number of prep pushes matches expected
 * number of args for the ALS library routine
 */
static void chk_callasl_arg_num(int32 num)
{
 /* push count is just debugging count to make sure asl routines push num */
 /* matches pop num */
 if (num != __push_count) __misc_terr(__FILE__, __LINE__);
 __push_count = 0;
}

static void cond_jmp_insn(int32 cc, struct bblk_t *t_bbp, struct bblk_t *f_bbp)
{
 nores_insn(I_COND_JMP, AM_BBLK, t_bbp, AM_BBLK, f_bbp);
 __cur_bbp->itail->jmptyp = cc;
 __set_back_edge(t_bbp);
 __set_back_edge(f_bbp);
}

static void cond_sgn_jmp_insn(int32 cc, struct bblk_t *t_bbp,
 struct bblk_t *f_bbp)
{
 nores_insn(I_COND_JMP, AM_BBLK, t_bbp, AM_BBLK, f_bbp);
 __cur_bbp->itail->jmptyp = cc;
 __cur_bbp->itail->sgn_jmp = TRUE;
 __set_back_edge(t_bbp);
 __set_back_edge(f_bbp);
}

extern void __emit_jmp(struct bblk_t *bbp)
{
 /* DBG remove -- */
 if (bbp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */

 /* unconditional jump */
 nores_insn(I_BBLK_JMP, AM_NONE, AM_BBLK, bbp);
 __cur_bbp->itail->jmptyp = CC_NONE;
 __set_back_edge(bbp);
}

/*
 * add a strength to a rhs conta where rhs is a known strength
 */
extern void __emit_rhs_conta_stren(int32 rhs_ti, int32 val, int32 bytlen)
{
 int32 a0_ti, a1_ti, a2_ti, cint_ti;

 cint_ti = __gen_cint_tn(bytlen);
 a2_ti = prep_push_tn_addr_arg(cint_ti);
 cint_ti = __gen_cint_tn(val);
 a1_ti = prep_push_tn_addr_arg(cint_ti);
 a0_ti = prep_push_word_arg(rhs_ti);
 emit_call_asl_proc(ASL_RHS_CONTA_STREN, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * set a jump back edge
 */
extern void __set_back_edge(struct bblk_t *bbp)
{
 struct bbedge_t *bbep;
 
 /* DBG remove --
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "#### ==> B%d is a back edge from B%d\n",
    bbp->bblk_seqno, __cur_bbp->bblk_seqno);
  }
 if (bbp == __cur_bbp) __misc_terr(__FILE__, __LINE__);
 --- */

 /* add edge to front of list of directed graph back edges */
 /* blk can have at most 2 successors but any number of predecessors */
 bbep = __alloc_bbedge();
 bbep->eblkp = __cur_bbp;
 bbep->bbenxt = bbp->bbe_prev;
 bbp->bbe_prev = bbep;
}

/*
 * an instruction that moves a reg src to a NEW reg dst operation
 * movl %r1, %newr
 * tn typ is the type of content held in the new register (TN_VAL/TN_ADR)
 */
extern int32 __move_insn(int32 tntyp, int32 opcod, int32 src_amode, ...)
{
 int32 res_tni;
 va_list va;

 va_start(va, src_amode);
 res_tni = move_srep_insn2(tntyp, opcod, SR_CINT, WBITS, src_amode, va);
 va_end(va);
 return(res_tni);
}

/*
 * same as move_insn except this needs to set the tn used wide flag 
 * which indicates that this temp is used in a wide context
 * note - doesn't take reg type or opcode since it is a LEAL which is TN_ADR
 *
 * SJM 11/10/06 - convention is that child tmp names (results of adr adds)
 * do not have used wide set, but when checking child for used wide (i.e.
 * not decomposed), must use parent tni to determine if used wide
 */
static int32 leal_insn(int32 src_amode, ...)
{
 int32 res_tni, tni, par_tni;
 va_list va;
 struct insn_t *ip;
 struct tn_t *tnp;

 va_start(va, src_amode);
 res_tni = move_srep_insn2(TN_ADR, I_LEAL, SR_CINT, WBITS, src_amode, va);
 va_end(va);

 /* if expanding copy the last insn is always the copy insn */
 /* other it is always the tail */
 if (__copy_ip != NULL) ip = __copy_ip;
 else ip = __cur_bbp->itail;
 tni = ip->isrc.am_tni;
 /* DBG REMOVE --- */
 if (ip->opcod != I_LEAL) __misc_terr(__FILE__, __LINE__);
 if (tni == -1) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 tnp = &(__tntab[tni]);
 if (tnp->tag_parent_tni != -1) par_tni = tnp->tag_parent_tni;
 else par_tni = tni;
 __tntab[par_tni].tn_used_wide = TRUE;

 va_end(va);
 return(res_tni);
}

/*
 * same as move insn except need sr type and bit length
 */
extern int32 __move_srep_insn(int32 tntyp, int32 opcod, int32 srtyp, 
 int32 blen, int32 src_amode, ...)
{
 int32 res_tni;
 va_list va;

 va_start(va, src_amode);
 res_tni = move_srep_insn2(tntyp, opcod, srtyp, blen, src_amode, va);
 va_end(va);
 return(res_tni);
}

/*
 * move srep instruction where new register holds the srep/blen of the thing
 * either pointed to or in the register value
 * movl %r1, %newr
 * where %newr => needs srep/blen type set correctly
 */
static int32 move_srep_insn2(int32 tntyp, int32 opcod, int32 srtyp, int32 blen, 
 int32 src_amode, va_list va)
{
 int32 res_ti;
 struct insn_t *ip;
 struct amode_t tmp1_amode, tmp2_amode;

 /* DBG --- */
 if (src_amode == AM_NONE) __misc_terr(__FILE__, __LINE__);
 if (tntyp != TN_VAL && tntyp != TN_ADR) __misc_terr(__FILE__, __LINE__);
 /* ------- */

 __init_amode(&(tmp1_amode));
 __init_amode(&(tmp2_amode));

 tmp1_amode.amode = src_amode;
 __set_amode(&(tmp1_amode), va);
#ifdef __CVC32__
  /* AIV 11/17/08 - to be 32/64 bit compat just restore va advance global */
  va = __advance_seta_va;
#endif

 va_end(va);

 tmp2_amode.amode = AM_NONE;

 /* AIV LOOKATME - better method for this case ????? */
 /* AIV 08/02/06 - if source is an AR_AX must be a return from an asl call */
 /* if it is is return from a call it must always gen a new temp */
 /* this is needed because of the following sequence : */
 /*  
  * call   __asl_call1
  * movl   %eax, r1   (need to use value later) 
  *
  * call   __asl_call1
  * movl   %eax, r1  (needs to really be r2)
  * 
  * addl [first r1] put value as been overwritten
  */
 
 /* if not eax don't check formal tmp table */
 if (tmp1_amode.am_tni != AR_AX)
  {
   res_ti = find_add_formal_tmptab(opcod, tntyp, srtyp, blen, &(tmp1_amode),
    &(tmp2_amode));
   if (__avl_node_is_new) __tntab[res_ti].tn_typ = tntyp;
   else
    {
     if (__tntab[res_ti].tn_typ != tntyp) __case_terr(__FILE__, __LINE__);
    }
  }
 else 
  {
   /* if eax move need a new stored value every time */
   res_ti = __gen_tn(srtyp, blen);
   __tntab[res_ti].tn_typ = tntyp;
  }

/* ---
 if (!__avl_node_is_new)
  {
// ??? magic - use value numbering to not create insn if don't need to
  }
// record some stuff
--- */

 /* case 2: need to insert the insn */
 ip = __alloc_insn(opcod);  
//SJM? may have memory leak if do not free any labnam
 ip->isrc = tmp1_amode;
 ip->idst.amode = AM_NONE;
 ip->res_tni = res_ti;
//AIV? - need separate routines for i copy lowerering
 if (__copy_ip != NULL) 
  {
   __insert_after_insn(ip, __copy_ip);
   __copy_ip = ip;
  }
 else
  {
   if (mark_keep_eval_insn(ip)) __add_insn_toend(ip); 
  }
 return(res_ti);
}

/*
 * mark stored into tn as changed and remove the store is possible
 */
static int32 mark_need_keep_store_into(struct insn_t *ip)
{
 int32 st_tni, rv;
 struct tn_t *st_tnp; 


 /* DBG remove -- */
 if (ip == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 /* SJM 12/01/07 - store into nlo nl object legal - must always keep here */
 if (ip->idst.amode == AM_NLO) return(TRUE);

 /* DBG remove -- */
 if (ip->idst.amode == AM_NONE) __misc_terr(__FILE__, __LINE__);
 if (ip->idst.am_tni == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 st_tni = ip->idst.am_tni;
 st_tnp = &(__tntab[st_tni]);
 /* check to see if this insn is a copy with identical and never */
 /* stored into store from */
 if (st_tnp->st_into_ip != NULL && ip->opcod == st_tnp->st_into_ip->opcod)
  {
   /* destination amodes must be the same */
   rv = __cmp_amodes(&(st_tnp->st_into_ip->idst), &(ip->idst));
   if (rv != 0)
    {
     goto no_rem_insn;
    }
   /* DBG remove -- */
   if (st_tnp->st_into_ip->idst.am_tni != st_tni)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (ip->isrc.am_tni == -1 && ip->isrc.amode != AM_NLO)
      __misc_terr(__FILE__, __LINE__);
   /* if stored in a different block */
   if (st_tnp->valnum < __enter_bblk_valnum) goto no_rem_insn;
   /* if source value has been stored to must store again */
   if (__tntab[ip->isrc.am_tni].valnum > st_tnp->valnum) goto no_rem_insn;

   if (ip->opcod == I_COPY)
    {
//AIV? - fixme - why are you using disp for i copy num bytes to copy ? 
     if (ip->isrc.disp != st_tnp->st_into_ip->isrc.disp) goto no_rem_insn;
    }
   if (st_tnp->st_into_ip->isrc.am_tni == ip->isrc.am_tni)
    {
     __free_1insn(ip);
     return(FALSE);
    }
  }
no_rem_insn:
 /* case 1: no rem but mark the chg tni for laster operand chg test */
 st_tnp->valnum = ++__cur_valnum; 
 st_tnp->st_into_ip = ip;
 return(TRUE);
}

/*
 * gen eval binary operator insn that either finds the
 * same returned tmp name in the formal tmp table or gens a new tn
 *
 * not for unary because expects [op] <src amode> <dst amode> => <resutl tn>
 */
static int32 eval_insn(int32 tntyp, int32 opcod, int32 src_amode, ...)
{
 int32 res_ti;
 va_list va;

 va_start(va, src_amode);
 res_ti = eval_srep_insn2(tntyp, opcod, SR_CINT, WBITS, src_amode, va);
 va_end(va);
 return(res_ti);
}

/*
 * same as eval insn except need sr type and bit length
 */
static int32 eval_srep_insn(int32 tntyp, int32 opcod, int32 srtyp, int32 blen, 
 int32 src_amode, ...)
{
 int32 res_ti;
 va_list va;

 va_start(va, src_amode);
 res_ti = eval_srep_insn2(tntyp, opcod, srtyp, blen, src_amode, va);
 va_end(va);
 return(res_ti);
}

/*
 * same as eval srep above but set the srtyp and blen
 */
static int32 eval_srep_insn2(int32 tntyp, int32 opcod, int32 srtyp, int32 blen, 
 int32 src_amode, va_list va)
{
 int32 res_ti;
 struct insn_t *ip;
 struct amode_t tmp1_amode, tmp2_amode;

 /* DBG --- */
 if (src_amode == AM_NONE) __misc_terr(__FILE__, __LINE__);
 if (tntyp != TN_VAL && tntyp != TN_ADR) __misc_terr(__FILE__, __LINE__);
 /* ------- */

 __init_amode(&(tmp1_amode));
 __init_amode(&(tmp2_amode));

 tmp1_amode.amode = src_amode;
 __set_amode(&(tmp1_amode), va);
#ifdef __CVC32__
  va = __advance_seta_va;
#endif

 tmp2_amode.amode = va_arg(va, int32);
 __set_amode(&(tmp2_amode), va);
#ifdef __CVC32__
  va = __advance_seta_va;
#endif
 /* DBG remove --
//PUTMEBACK
//SJM??? FIXME
//do operation and make it a move ins of a cint 
 if (__is_constant(tmp1_amode.am_tni) && __is_constant(tmp2_amode.am_tni))
  {
   __misc_terr(__FILE__, __LINE__);
  }
 -- */

 va_end(va);

 res_ti = find_add_formal_tmptab(opcod, tntyp, srtyp, blen, &(tmp1_amode),
  &(tmp2_amode));

 if (__avl_node_is_new) __tntab[res_ti].tn_typ = tntyp;
 else
  {
   if (__tntab[res_ti].tn_typ != tntyp) __case_terr(__FILE__, __LINE__);
  }

 /* case 2: need to insert the insn */
 ip = __alloc_insn(opcod);  
//SJM? may have memory leak if do not free any labnam
 ip->isrc = tmp1_amode;
 ip->idst = tmp2_amode;
 ip->res_tni = res_ti;
//AIV? - need to separate out original insn list update versus add to end
 if (__copy_ip != NULL) 
  {
   __insert_after_insn(ip, __copy_ip);
   __copy_ip = ip;
  }
 else
  {
   /* try to remove insn if insn in block sets tmp name and opands unchged */
   if (mark_keep_eval_insn(ip)) __add_insn_toend(ip);
  }  
 return(res_ti);
}

/*
 * remove generated tail insn using during insn gen value numbering algorithm
 *
 * if eval insn (formal tmp tab return of same tni for same insn) removed
 * 2nd insn to same res_tni if no store into operand before here
 */
static int32 mark_keep_eval_insn(struct insn_t *ip)
{
 int32 res_tni;
 struct tn_t *res_tnp, *tnp; 

 /* DBG remove -- */
 if (ip == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */ 
 res_tni = ip->res_tni;
 res_tnp = &(__tntab[res_tni]);
 if (res_tnp->valnum < __cur_valnum)
  {
no_rem:
   res_tnp->valnum = ++__cur_valnum; 
   res_tnp->st_into_ip = ip;
   return(TRUE);
  }

 /* SJM 12/01/07 - must assume nlo label changed here */
 if (ip->isrc.amode == AM_NLO) goto no_rem;

 if (ip->isrc.amode != AM_NONE)
  {
//SJM? - since immediate is constant, can't have been changed
   if (ip->isrc.amode != AM_IMM && ip->isrc.amode != AM_NLO)
    {
     if (ip->isrc.am_tni != -1)
      {
       /* if stored in a different block */
       tnp = &(__tntab[ip->isrc.am_tni]);
       if (tnp->valnum < __enter_bblk_valnum) goto no_rem;
       if (tnp->valnum > res_tnp->valnum) goto no_rem;
      }
     else __case_terr(__FILE__, __LINE__);
    } 
  }

//AIV? 12/01/07 - think eval insn can't have nlo amode as dest */
 /* DBG remove -- */
 if (ip->idst.amode == AM_NLO) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* AIV 07/31/06 - if has a dest check its value as well */
 if (ip->idst.amode != AM_NONE)
  {
   if (ip->idst.am_tni != -1)
    {
     /* if stored in a different block */
     tnp = &(__tntab[ip->idst.am_tni]);
     if (tnp->valnum < __enter_bblk_valnum) goto no_rem;
     if (tnp->valnum > res_tnp->valnum) goto no_rem;
    }
   else __case_terr(__FILE__, __LINE__);
  } 
 __free_1insn(ip);
 return(FALSE);
}

/*
 * gen eval insn of unary operator etc. insn that either finds the
 * same returned tmp name in the formal tmp table or gens a new tn
 *
 * 2nd dst amode unused here - but dst filled in x86asm from res tni
 */
static int32 unary_insn(int32 tntyp, int32 opcod, int32 src_amode, ...)
{
 int32 res_tni;
 va_list va;

 va_start(va, src_amode);
 res_tni = move_srep_insn2(tntyp, opcod, SR_CINT, WBITS, src_amode, va);
 va_end(va);
 return(res_tni);
}

/*
 * gen a store insn - does not go in formal tmp table and store int
 * dst amode (i.e. no res tni)
 */
extern void __st_insn(int32 opcod, int32 src_amode, ...)
{
 int32 dst_amode;
 struct insn_t *ip;
 va_list va;

 /* SJM 03/11/07 - AIV lookatme - can't pass cint tn for 8 byte copy */
 /* DBG remove --
 if (nbytes > 4)
  {
   if (__tntab[op1].srtyp == SR_CINT) __misc_terr(__FILE__, __LINE__);
   if (__tntab[op2].srtyp == SR_CINT) __misc_terr(__FILE__, __LINE__);
  }
 --- */

 ip = __alloc_insn(opcod);  
 ip->is_store = TRUE;
 va_start(va, src_amode);

 /* DBG --- */
 if (src_amode == AM_NONE) __misc_terr(__FILE__, __LINE__);
 /* ------- */
 ip->isrc.amode = src_amode;
 __set_amode(&(ip->isrc), va);
#ifdef __CVC32__
  va = __advance_seta_va;
#endif
 dst_amode = va_arg(va, int32);
 ip->idst.amode = dst_amode;
 __set_amode(&(ip->idst), va);
#ifdef __CVC32__
  va = __advance_seta_va;
#endif
 va_end(va);

//SJM? FIXME - need separate replace or something not special pointer
 /* for special case of expanding I COPY need to remove and insert */
 if (__copy_ip != NULL) 
  {
   __insert_after_insn(ip, __copy_ip);
   __copy_ip = ip;
  }
 else
  {
   /* AIV 01/08/09 - tmps can attempt to copy to itself due */
   /* to constant expression folding during code gen time */
   /* used to catch this is copy expand */
   /* AIV 01/26/10 - better also just be reg to reg not ndx ofs */
   if (ip->isrc.am_tni == ip->idst.am_tni 
        && ip->isrc.amode == AM_REG && ip->idst.amode == AM_REG) 
    {
     return;
    }

   /* if can remove insn, just don't add the new one */
   if (mark_need_keep_store_into(ip))
    {
     __add_insn_toend(ip);
    }
  }
}

/*
 * gen insn that does not have a tmp name result and does not store
 * such as testl
 */
static void nores_insn(int32 opcod, int32 src_amode, ...)
{
 int32 dst_amode;
 struct insn_t *ip;
 va_list va;

 ip = __alloc_insn(opcod);  
 /* SJM 12/20/06 - for debugging, need to print AFS enter bblk number */
 if (opcod == I_PROLOGUE) ip->extrau.prologue_bblkno = __cur_bbp->bblk_seqno;

 /* AIV 08/07/09 - cannot remove stores across task calls */
 /* AIV 08/10/09 - really across all calls - including asl calls */
 if (opcod == I_CALL || opcod == I_CALL_ASLFUNC || opcod == I_CALL_ASLPROC)
  {
   __enter_bblk_valnum = ++__cur_valnum;
  }

 va_start(va, src_amode);
 /* one arg minsn - dest amode only */
 if (src_amode == AM_NONE)
  {
   ip->isrc.amode = AM_NONE;
   dst_amode = va_arg(va, int32);
   ip->idst.amode = dst_amode;
   if (dst_amode != AM_NONE)
    {
     __set_amode(&(ip->idst), va);
#ifdef __CVC32__
     va = __advance_seta_va;
#endif
    }
  }
 else 
  {
   ip->isrc.amode = src_amode;
   __set_amode(&(ip->isrc), va);
#ifdef __CVC32__
   va = __advance_seta_va;
#endif
   dst_amode = va_arg(va, int32);
   /* nores_ can take two AM_NONE values */
   if (dst_amode == AM_NONE) 
    {
     va_end(va);
     return;
    }
   ip->idst.amode = dst_amode;
   __set_amode(&(ip->idst), va);
#ifdef __CVC32__
   va = __advance_seta_va;
#endif
  }
 if (__copy_ip != NULL) 
  {
   __insert_after_insn(ip, __copy_ip);
   __copy_ip = ip;
  }
 else __add_insn_toend(ip);
 va_end(va);
}
 
/*
 * generate a copy container insn
 * this will be expanded later
 */
static void copy_insn(int32 op1, int32 op2, int32 nbytes)
{
 struct insn_t *ip;
 
 ip = __alloc_insn(I_COPY);  
 ip->is_store = TRUE;
 ip->isrc.amode = AM_REG;
 ip->isrc.am_tni = op1;
 ip->isrc.disp = nbytes;
 ip->idst.amode = AM_REG;
 ip->idst.am_tni = op2;
 /* if can remove insn, just don't add the new one */
 if (mark_need_keep_store_into(ip)) __add_insn_toend(ip);
}

/*
 * add a machine minsn to the end of one basic blocks minsn list
 */
extern void __add_insn_toend(struct insn_t *ip)
{
 /* DBG --- */
 if (__cur_bbp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (__cur_bbp->ihd == NULL) 
  {
   __cur_bbp->ihd = __cur_bbp->itail = ip;
  }
 else
  {
   __cur_bbp->itail->inxt = ip;
   ip->iprev = __cur_bbp->itail;
   __cur_bbp->itail = ip;
  }
}

/*
 * set an amode base on the the type
 *
 * for non virtual amode's the amode does not need to be changed
 */
extern void __set_amode(struct amode_t *amp, va_list va)
{
 char *chp;

 /* AIV 08/27/09 - disps needs to be size_t for 64-bit not int */
 switch (amp->amode) { 
  case AM_NONE:
   __case_terr(__FILE__, __LINE__);
   break;
  case AM_REG:
   amp->am_tni = va_arg(va, int32);
   break;
  case AM_IMM:
   amp->disp = va_arg(va, int32);
   break;
  case AM_NDXREG:
   amp->am_tni = va_arg(va, int32);
   break;
  case AM_NDXREG_DISP:
   amp->am_tni = va_arg(va, int32);
   amp->disp = va_arg(va, size_t);
   break;
  case AM_NONREG_OFS:
   /* SJM 11/11/06 - byte offset if decomposed is consistent x86 reg if */
   /* tn used wide, ebp non var tmp offset relative to ebp adjusted by disp */
   amp->am_tni = va_arg(va, int32);
   amp->disp = va_arg(va, size_t);
#ifndef __CVC32__
   /* AIV 08/27/09 - check for disp overflow */
   /* DBG remove -- */
   if (amp->disp >= 0xf0000000) __misc_terr(__FILE__, __LINE__);
   /* ---- */
#endif
   break;
  case AM_IDP_ADR_OFS:
   /* SJM 04/04/07 - new addr mode for netbp style adr comlabs with offsets */
   amp->am_tni = va_arg(va, int32);
   amp->disp = va_arg(va, size_t);
   break;
  case AM_NLO_ARRNDX:
   amp->am_tni = va_arg(va, int32);
   amp->arr_base_nlo = va_arg(va, word32);
   break;
  case AM_LABEL:
   chp =  va_arg(va, char *); 
   amp->is_labnam = TRUE;
   amp->apu.labnam = __xi_stralloc(chp);
   amp->disp = va_arg(va, int32);
   /* AIV 08/27/09 - check for block overflow */
   /* DBG remove -- */
   if (amp->disp >= 0xfffffffe) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   break;
  case AM_BBLK:
   amp->apu.bbp = va_arg(va, struct bblk_t *); 
   break;
  case AM_NLO:
   /* SJM 12/01/07 - label that is just an immed int - immediate used to */
   /* generate the RT name such as __cur thd */
   amp->disp = (size_t) va_arg(va, int32);
   break;
  default:
   __case_terr(__FILE__, __LINE__);
   break;
  }
 /* DBG remove -- */
 if (amp->am_tni != -1 && amp->am_tni > __tntab_nxti)
  __misc_terr(__FILE__, __LINE__);
 /* -- */
#ifdef __CVC32__
 /* AIV 11/17/08 - to be 32/64 bit compat just save this value as a global */
 /* and restore it upon the call - 64-bit cannot retun a va_list array */
 __advance_seta_va = va;
#endif
}

/*
 * ROUTINES FOR UPDATING THE EVAL INSN FORMAL TMP TABLE 
 */

/*
 * find/add formal tmp table entry for one insn
 */
static int32 find_add_formal_tmptab(int32 opcode, int32 tntyp, int32 srtyp,
 int32 reswid, struct amode_t *amp1, struct amode_t *amp2)
{
 struct ftval_t tmp_ftval;
 struct ftval_t *new_valp;
 struct avlhd_t *tree_rec;
 struct avlnode_t *eval_nodp;
 struct ftval_t *ftvalp;  
 struct ftval_t *nvalp;
 int32 res_ti, slen;

 tmp_ftval.tn_typ = tntyp; 
 tmp_ftval.srtyp = srtyp; 
 tmp_ftval.res_tnwid = reswid;
 tmp_ftval.res_tni = -1;
 tmp_ftval.am1 = *amp1;
 tmp_ftval.am2 = *amp2;
//SJM? - FIXME - get rid of this string that must be copied
 if (amp1->is_labnam) 
  {
   tmp_ftval.am1.apu.labnam = __xi_stralloc(amp1->apu.labnam);
  }
 if (amp2->is_labnam) 
  {
   tmp_ftval.am2.apu.labnam = __xi_stralloc(amp2->apu.labnam);
  }

 __avl_node_is_new = FALSE;
 /* case 1: tree if empty for this opcode - just add */
 if ((tree_rec = __formal_tmptab[opcode]) == NULL) 
  {
   /* if empty tree, add the node */
   __formal_tmptab[opcode] = (struct avlhd_t *)
    __my_malloc(sizeof(struct avlhd_t)); 
   tree_rec = __formal_tmptab[opcode];
   tree_rec->num_nodes = 1;
   tree_rec->avl_cmp = ft_node_cmp;
   tree_rec->avl_alloc = formaltmp_alloc;
   new_valp = fill_new_ft_node(&(res_ti), tntyp, srtyp, reswid, &(tmp_ftval)); 
   tree_rec->avl_root = __alloc_avlnode(new_valp);
   __avl_node_is_new = TRUE;
   /* this also allocates the new tn */
   return(res_ti);
  }

 /* case 2: search to see if other identical insn in module */

 /* if can't find, inserts new empty node in set (avl tree) */
 eval_nodp = __avltfind(((void *) &(tmp_ftval)), tree_rec);

 /* case 2a: no insn with identical amode and result size/srtyp in mod */
 if (__avl_node_is_new)
  {
   /* AIV 01/24/07 - was allocing a new node which was already alloc */
   /* from __avlfind just need to set the new tmp for the new node */
   nvalp = eval_nodp->valp;
   /* DBG remove -- */
   if (nvalp == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   res_ti = __gen_tn(srtyp, reswid);
   nvalp->res_tni = res_ti;
   tree_rec->num_nodes++;
   return(res_ti);
  }

//SJM? FIXME - need per module labnam string area so can just point
 /* case 2b: found match - just return the tni */
 if (tmp_ftval.am1.is_labnam)
  {
   slen = strlen(tmp_ftval.am1.apu.labnam);
   __my_free(tmp_ftval.am1.apu.labnam, slen + 1);
  }
 if (tmp_ftval.am1.is_labnam)
  {
   slen = strlen(tmp_ftval.am1.apu.labnam);
   __my_free(tmp_ftval.am1.apu.labnam, slen + 1);
  }
 ftvalp = (struct ftval_t *) eval_nodp->valp;
 return(ftvalp->res_tni);
}

/*
 * fill an avlnode - know this insn pattern not already in formal tmp tab
 */
static struct ftval_t *fill_new_ft_node(int32 *res_ti, int32 tntyp,
 int32 srtyp, int32 opwid, struct ftval_t *new_ftvalp)  
{
 int32 tni;  
 struct ftval_t *valp;

 tni = __gen_tn(srtyp, opwid);
 valp = (struct ftval_t *) __my_malloc(sizeof(struct ftval_t));
 *valp = *new_ftvalp;
 valp->tn_typ = tntyp; 
 valp->srtyp = srtyp; 
 valp->res_tnwid = opwid;
 valp->res_tni = tni;
 if (new_ftvalp->am1.is_labnam)
  {
   valp->am1.apu.labnam = __xi_stralloc(new_ftvalp->am1.apu.labnam);
  }
 if (new_ftvalp->am2.is_labnam)
  {
   valp->am2.apu.labnam = __xi_stralloc(new_ftvalp->am2.apu.labnam);
  }
 *res_ti = tni;
 return(valp);
}

/*
 * node compare for formal tmp table node 
 *
 * know the number of args must match but VAM types can differ
 *
 * LOOKATME - could have the tree node point to specialized compare
 * routine to avoid all the testing
 */
static cmpsword ft_node_cmp(const void *valp, const struct avlnode_t *nodp)
{
 cmpsword rv;
 struct ftval_t *p1, *p2;

 p1 = (struct ftval_t *) valp;
 p2 = (struct ftval_t *) nodp->valp;

 /* AIV 07/20/06 - need to make sure the tn types are the same as well */
 /* this was a bug because eax returned from wrapper calls as reg/adr */
 /* was going into the same reg or different types */
 rv = p1->tn_typ - p2->tn_typ;
 if (rv != 0) return(rv);
 rv = p1->srtyp - p2->srtyp;
 if (rv != 0) return(rv);
 rv = p1->res_tnwid - p2->res_tnwid;
 if (rv != 0) return(rv);
 rv = __cmp_amodes(&(p1->am1), &(p2->am1));
 if (rv != 0) return(rv);
 return(__cmp_amodes(&(p1->am2), &(p2->am2)));
}

/*
 * compare 2 amodes
 */
extern int32 __cmp_amodes(struct amode_t *amp1, struct amode_t *amp2)
{
 int32 rv;

 /* if amodes different, can't be the same */
 rv = amp1->amode - amp2->amode;
 if (rv != 0) return(rv);

 switch (amp1->amode) {
  case AM_NONE:
   rv = 0;
   break;
  case AM_IMM:
   rv = amp1->disp - amp2->disp;
   break; 
  case AM_REG:
   rv = amp1->am_tni - amp2->am_tni;
   break; 
  case AM_NDXREG:
   rv = amp1->am_tni - amp2->am_tni;
   break; 
  case AM_NDXREG_DISP:
   rv = amp1->am_tni - amp2->am_tni;
   if (rv != 0) return(rv);
   rv = amp1->disp - amp2->disp;
   break;
  case AM_NLO_ARRNDX:
   rv = amp1->am_tni - amp2->am_tni;
   if (rv != 0) return(rv);
   rv = (int32) amp1->arr_base_nlo - (int32) amp2->arr_base_nlo;
   break;
  case AM_LABEL:
   /* now also need label compare for putting result tns into formal tmp tab */
   rv = strcmp(amp1->apu.labnam, amp2->apu.labnam);
   if (rv != 0) return(rv);
   rv = amp1->disp - amp2->disp;
   break;
  case AM_NONREG_OFS:
   /* this is really alternative adr add form of am ndx reg disp */
   rv = amp1->am_tni - amp2->am_tni;
   if (rv != 0) return(rv);
   rv = amp1->disp - amp2->disp;
   break;
  case AM_IDP_ADR_OFS:
   rv = amp1->am_tni - amp2->am_tni;
   if (rv != 0) return(rv);
   rv = amp1->disp - amp2->disp;
   break;
  case AM_BBLK:
   rv = amp1->apu.bbp->bblk_seqno - amp2->apu.bbp->bblk_seqno;
   break;
  case AM_NLO:
   rv = amp1->disp - amp2->disp;
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(rv);
}

/*
 * avl tree alloc for formal tmp tab ftval record
 */
static struct avlnode_t *formaltmp_alloc(void *valp)
{
 struct ftval_t *newp, *oldp;
 struct avlnode_t *nodp;

 oldp = (struct ftval_t *) valp;
 newp = (struct ftval_t *) __my_malloc(sizeof(struct ftval_t));
 *newp = *oldp;
//AIV - what about amode litnam string need to copy here as well
 nodp = __alloc_avlnode((void *) newp);
 return(nodp);
}

/*
 * ROUTINES FOR SystemVerilog (SV) 
 */

/*
 * ROUTINES TO HANDLE SV STRINGS
 */

/*
 * load a SV string as a C char * to pass to a DPI function 
 */
extern int32 __emit_sv_dpi_string(struct expr_t *lhsx, int32 nchars_ti)
{
 int32 argxp_ti, a0_ti, ret_ti;

 argxp_ti = __gen_xpr_tn(lhsx);
 a0_ti = prep_push_word_arg(argxp_ti);
 emit_call_asl_func(ASL_SV_DPI_STRING, 1, a0_ti);
 chk_callasl_arg_num(1);
 //AIV LOOKATME - leaking memory here - for both stack and char * pointer 
 //__st_insn(I_STOREA, AM_REG, AR_CX, AM_REG, nchars_ti);
 ret_ti = __move_srep_insn(TN_ADR, I_MOVA, SR_BIT2S, WBITS, AM_REG, AR_AX);
 return(ret_ti);
}

/*
 * store SV string (char *) cp_ti into string np
 */
extern void __emit_sv_dpi_string_store(struct net_t *np, int32 cp_ti)
{
 int32 np_ti, a0_ti, a1_ti;

 np_ti = __ld_netadr_tn(np);
 a1_ti = prep_push_word_arg(cp_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_func(ASL_SV_DPI_STRING_STORE, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * assign a rhs constant value to a string np
 */
extern void __emit_sv_string_st_const(struct net_t *np, int32 rhs_apti)
{
 int32 a0_ti, a1_ti, a2_ti;
 int32 tnwid, nchars, cint_ti, np_ti, cp_ti, nchars_ti;

 /* DBG remove -- */
 if (np->srep != SR_STRING) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 tnwid = __get_tnwid(rhs_apti);
 nchars = (tnwid+7)/8;
 cint_ti = __gen_cint_tn(nchars);
 /* since rhs constant and <= STR_INIT_CHARS don't need to check size */
 /* just assign the value and set the size in idp storage */
 if (nchars <= STR_INIT_CHARS)
  {
   /* get the char * and move into an address tmp */
   cp_ti = __con_adradd_insn(SR_BIT2S, tnwid, __idp_ti,
     (np->nva_ofs+STR_IDP_OFS)*WRDBYTES);
   cp_ti = __move_srep_insn(TN_ADR, I_MOVA, SR_BIT2S, tnwid, AM_NDXREG, cp_ti);
   /* copy the string */
   __emit_copy(wlen_(tnwid)*WRDBYTES, rhs_apti, cp_ti);
   /* store the size of the string */
   nchars_ti = __con_adradd_insn(SR_BIT2S, WBITS, __idp_ti,
     (np->nva_ofs+STR_IDP_NDX_OFS)*WRDBYTES);
   __emit_copy(WRDBYTES, cint_ti, nchars_ti);
   return;
  }
 np_ti = __ld_netadr_tn(np);
 a2_ti = prep_push_word_arg(cint_ti);
 a1_ti = prep_push_tn_addr_arg(rhs_apti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_ST_STRING_CONST, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * assign string to string
 * s1 = s2
 */
extern void __emit_sv_string_st_var(struct net_t *lhs_np, struct net_t *rhs_np)
{
 int32 a0_ti, a1_ti;
 int32 lhs_np_ti, rhs_np_ti;

 lhs_np_ti = __ld_netadr_tn(lhs_np);
 rhs_np_ti = __ld_netadr_tn(rhs_np);
 a1_ti = prep_push_tn_addr_arg(rhs_np_ti);
 a0_ti = prep_push_tn_addr_arg(lhs_np_ti);
 emit_call_asl_proc(ASL_ST_STRING_VAR, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * assign rhs expr eval to string
 */
extern void __emit_sv_string_st_eval_rhsx(struct net_t *lhs_np, 
 struct expr_t *rhsx)
{
 int32 a0_ti, a1_ti;
 int32 rhsxp_ti, lhs_np_ti;

 rhsxp_ti = __gen_xpr_tn(rhsx);
 lhs_np_ti = __ld_netadr_tn(lhs_np);

 a1_ti = prep_push_tn_addr_arg(rhsxp_ti);
 a0_ti = prep_push_tn_addr_arg(lhs_np_ti);
 emit_call_asl_proc(ASL_ST_STRING_RHSX, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
}

/*
 * call a wrapper for string binop
 */
extern int32 __emit_binop_string(struct expr_t *xp)
{
 int32 xp_ti, a0_ti, res_ti;

//AIV LOOKATME????
 /* DBG remove --- */
 if (xp->lu.x->cnvt_to_string || xp->ru.x->cnvt_to_string)
  __misc_terr(__FILE__, __LINE__);
 /* ----- */

 switch (xp->optyp) {
  case /* > */ STRRELGT: break;
  case /* >= */ STRRELGE: break;
  case /* < */ STRRELLT: break;
  case /* <= */ STRRELLE: break;
  case /* == */ STRRELEQ: break;
  case /* != */ STRRELNEQ: break;
  default: __case_terr(__FILE__, __LINE__); break;
 }
 
 xp_ti = __gen_xpr_tn(xp);
 a0_ti = prep_push_tn_addr_arg(xp_ti);
 emit_call_asl_proc(ASL_STRING_BINOP, 1, a0_ti);
 chk_callasl_arg_num(1);
 res_ti = __move_insn(TN_ADR, I_MOVA, AM_REG, AR_AX);
 return(res_ti);
}

/*
 * wrapper for storing a char (byte) in a string
 * s[1] = "a"
 */
extern void __emit_st_string_byte(struct net_t *lhs_np, int32 bi_ti,
 int32 rhs_ti)
{
 int32 a0_ti, a1_ti, a2_ti, lhs_np_ti;

 lhs_np_ti = __ld_netadr_tn(lhs_np);
 a2_ti = prep_push_word_arg(rhs_ti);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_tn_addr_arg(lhs_np_ti);
 emit_call_asl_proc(ASL_ST_STRING_BYTE, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * wrapper to store a string array element with constant rhs
 */
extern void __emit_st_string_array_const(struct net_t *lhs_np, int32 arri_ti,
 int32 rhs_ti, int32 width_ti)
{
 int32 a0_ti, a1_ti, a2_ti, a3_ti, lhs_np_ti;

 lhs_np_ti = __ld_netadr_tn(lhs_np);
 a3_ti = prep_push_word_arg(width_ti);
 a2_ti = prep_push_word_arg(rhs_ti);
 a1_ti = prep_push_word_arg(arri_ti);
 a0_ti = prep_push_tn_addr_arg(lhs_np_ti);
 emit_call_asl_proc(ASL_ST_STRING_ARRAY_CONST, 4, a3_ti, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(4);
}

/*
 * wrapper to store a string array element with string ID rhs
 */
extern void __emit_st_string_array_var(struct net_t *lhs_np, 
 struct net_t *rhs_np, int32 arri_ti)
{
 int32 a0_ti, a1_ti, a2_ti, lhs_np_ti, rhs_np_ti;

 lhs_np_ti = __ld_netadr_tn(lhs_np);
 rhs_np_ti = __ld_netadr_tn(rhs_np);
 a2_ti = prep_push_word_arg(arri_ti);
 a1_ti = prep_push_tn_addr_arg(rhs_np_ti);
 a0_ti = prep_push_tn_addr_arg(lhs_np_ti);
 emit_call_asl_proc(ASL_ST_STRING_ARRAY_VAR, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * wrapper to store a string array element with string rhs 
 */
extern void __emit_st_string_array_rhsx(struct net_t *lhs_np, 
 struct expr_t *rhsx, int32 arri_ti)
{
 int32 a0_ti, a1_ti, a2_ti, lhs_np_ti, rhsxp_ti;

 rhsxp_ti = __gen_xpr_tn(rhsx);
 lhs_np_ti = __ld_netadr_tn(lhs_np);
 a2_ti = prep_push_word_arg(arri_ti);
 a1_ti = prep_push_tn_addr_arg(rhsxp_ti);
 a0_ti = prep_push_tn_addr_arg(lhs_np_ti);
 emit_call_asl_proc(ASL_ST_STRING_ARRAY_RHSX, 3, a2_ti, a1_ti, a0_ti);
 chk_callasl_arg_num(3);
}

/*
 * get a string byte
 * byte = s1[2]
 */
extern int32 __emit_get_string_byte(struct net_t *np, int32 bi_ti)
{
 int32 a0_ti, a1_ti, np_ti, r_ti;

 np_ti = __ld_netadr_tn(np);
 a1_ti = prep_push_word_arg(bi_ti);
 a0_ti = prep_push_tn_addr_arg(np_ti);
 emit_call_asl_proc(ASL_GET_STRING_BYTE, 2, a1_ti, a0_ti);
 chk_callasl_arg_num(2);
 r_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_BIT2S, 8, AM_REG, AR_AX);
 return(r_ti);
}
