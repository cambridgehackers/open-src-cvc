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
 * routines to optimize and lower basic block form flow graph insns
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <unistd.h> 
#include <alloca.h>
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

static int32 cnt_mod_insns(void);
static int32 cnt_bblk_insns(struct bblk_t *);
static void grow_flowgtab(void);
static void add_mipd_flowg(struct net_t *);
static int32 count_fg_bblks(struct flowg_t *); 
static void simplify_1fg_bblks(struct flowg_t *, struct mod_t *);
static void rm_afs_unreachable_bblks(struct flowg_t *);
static void track_rm_1bblk(struct bblk_t *, struct flowg_t *, int32);
static void track_rm_jmpto_back_edges(struct bblk_t *);
static void rm_and_merge_bblks(struct flowg_t *, int32);
static void early_mark_reachable(struct bblk_t *);
static void remove_empty_bblks(struct flowg_t *);
static int32 is_enter_insn(int32);
static void check_bad_or_unreachable_bblks(struct flowg_t *);
static void remove_jmponly_bblks(struct flowg_t *, struct mod_t *);
static void merge_uncond_1entry_bblks(struct flowg_t *, struct mod_t *);
static void mark_fallthru_jumps(struct flowg_t *);
static void fixup_reverse_cond_jumps(struct flowg_t *);
static void merge_bblks(struct flowg_t *, struct bblk_t *,
 struct bblk_t *);
static void subst_backedges(struct flowg_t *, struct bblk_t *,
 struct bblk_t *);

static void set_rpos_and_ent_bblklst(struct flowg_t *, struct mod_t *);
static struct bblklst_t *alloc_bblklst(void);
static void set_bblk_rev_postorder_nums(struct bblk_t *, struct bblk_t *);
static void dmp_1fg_rev_po_bblktab(int32);

#ifdef __VALTRK__
static void bld_tn_sets(struct flowg_t *);
static int32 xget_tnreg(struct amode_t *);
static void bld_tn_used_in_fg_set(struct flowg_t *, struct bblk_t *);
static void tryadd_var_tn_in_fg(struct flowg_t *, int32);
static int32 tn_valtrk_invisible(int32);
static void bld_bblk_defuse_in_tn_sets(struct bblk_t *);
static void tryadd_bblk_defines_tn(int32, struct bblk_t *); 
static void tryadd_bblk_uses_tn(int32, struct bblk_t *); 
static void dmp_fg_tn_info(struct flowg_t* );

static int32 cmp_ihd_ndx(const void *, const void *); 
static int32 insn_ndx_srch(int32, int32 *, int32);

static void bld_insert_fud_chains(struct flowg_t *);
static void insert_fg_deflsts(struct flowg_t *, struct avlnode_t **, int32);
static void try_insert_deflst_dom_fronts(int32, struct bblk_t *);
static void lnk_deflst_live_defs(struct flowg_t *, struct avlnode_t **,
 int32);
static void allocinit_curdef_ip(struct tn_t *, int32);
static int32 has_deflst_insn(struct bblk_t *, int32);
static void search_link_fud_uses(struct bblk_t *);
static void try_set_curdefs_and_savchains(struct bblk_t *);
static void try_set_asl_wrapper_curdefs(struct insn_t *);
static int32 is_unsupported_asl_insn(int32);
static int32 valtrk_insn_skip_dst(struct insn_t *);
static int32 get_amode_wdisp(int32 *, struct insn_t *, struct amode_t *,
 struct tn_t *);
static int32 get_insn_res_wdisp(struct insn_t *);
static void add_deflst_livdefs(struct bblk_t *);
static void restore_savchains(struct bblk_t *);
static int32 def_is_immed_pred(struct insn_t *, struct bblk_t *);

static void alloc_fill_bblk_insn_order_tab(int32);

static int32 sequencer_1fg_track_optimize(struct flowg_t *, struct mod_t *); 
static void init_1fg_trk_insns(struct flowg_t *);
static void set_1fg_insn_out_symbolic_vals(struct flowg_t *);
static void set_insn_dst_state_val(struct insn_t *);
static void set_deflst_in_state_val(struct insn_t *);
static void set_cmp_trk_state_val(struct insn_t *);
static int32 get_jmp_cmpl_cc_result(int32, int32, int32);
static void set_asl_wrapper_trk_state_val(struct insn_t *);
static void set_wide_jmpor0_cmp_trk_state_val(struct insn_t *);
static void chg_testl_to_con(struct insn_t *, int32); 
static int32 wide_trk_valp_any1_con(int32, int32 *, word32 *, int32);
static int32 asl_wide_all_trk_con(int32, int32 *, int32);
static void set_wide_cmp_trk_state_val(struct insn_t *);
static void set_wide_binop_trk_state_val(struct insn_t *);
static int32 get_1w_trk_val(struct insn_t *, struct amode_t *, struct insn_t *,
 word32 *);
static int32 get_asl_wide_trk_val(struct insn_t *, struct amode_t *, int32,
 struct insn_t **, int32 *,  word32 *);
static void optimize_1fg_symbolic_con_out_insns(struct flowg_t *);
static int32 is_int_returning_asl(struct insn_t *);
static void replace_asl_with_copy_insn(struct insn_t *, word32 *, int32);
static void fix_binop_trk_opand(struct insn_t *, int32);
static int32 dbg_get_trk_ipval(struct insn_t *);
static int32 tn_is_trackable(int32);
static int32 can_rm_trk_insn(int32);
static word32 *get_tracked_con(int32, word32 *);
static void remove_unneeded_machreg_insns(struct flowg_t *, struct mod_t *);

static void bld_fuds_and_simplify_1fg(struct mod_t *, struct flowg_t *);
static void bld_1fg_doms_sets_fuds(struct flowg_t *);
static void bld_predominators(struct flowg_t *);
static void bld_predom_tree(struct flowg_t *);
static int32 predom_intersect(int32 *, int32, int32);
static int32 add_bblst_linear_set(struct bblk_t *, struct bblk_t *);
static void dmp_predom_frontier_lists(struct flowg_t *);
static void bld_bblk_predom_frontier(struct flowg_t *);
static void dmp_doms(int32 *, int32);
static void dmp_1fg_predom_trees(struct flowg_t *);
static void bld_bblk_predom_of_lists(struct flowg_t *);

extern void __free_flowg_doms_and_sets(struct flowg_t *);
#endif

static void lower_insns_to_mach_level(struct flowg_t *, struct mod_t *);
static void expand_fg_copies(struct flowg_t *);
static void decompose_fg_non_leal_wide_amode_tns(struct flowg_t *);
static void try_replace_amode_wide_tn(struct amode_t *);
static int32 tmp_is_decomposable(struct tn_t *);
static void try_replace_amode_call_wide_tn(struct insn_t *);
static void replace_child_tns(struct flowg_t *);
static void try_replace_amode_child_tn(struct amode_t *);

static void convert_to_2op_insn(struct flowg_t *, struct mod_t *);
static int32 convert_insn_to_2op(struct insn_t *);
static int32 is_commutative_insn(int32);
static void convert_div_insn_to_x86_2op(struct insn_t *);

static void rm_1endjmp_bblk(struct bblk_t *, struct flowg_t *,
 struct mod_t *);
static void rm_one_bbedge(struct bblk_t *, struct bblk_t *); 
static int32 fnd_bbedge(struct bblk_t *, struct bblk_t *); 
static void adjust_jmpfr_end_insn(struct bblk_t *, struct bblk_t *, int32);
static void fix_rmbblk_ndxjmp_insn(struct bblk_t *, struct insn_t *, int32);
static void chk_bblk_connectivity(struct flowg_t *);

static void final_machine_insn_fixup(struct flowg_t *, struct mod_t *);
static void fixup_coalesced_away_tns(struct flowg_t *);
static void try_set_amode_to_reg(struct amode_t *);
static void set_amode_ebp_disp(int32, struct amode_t *);
static int32 determine_2memref_class(struct insn_t *);
static void expand_fg_asl_calls(struct flowg_t *);
static void expand_one_asl_call(struct insn_t *);
static void fixup_1fg_2memrefs(struct flowg_t *);
static void fix_nlo_arrndx_insn(struct insn_t *);
static void chk_insns_2memrefs(struct flowg_t *);
static void dbg_chk_legal_wide_tn(struct amode_t *);
static void peep_hole_optimize(struct flowg_t *);
static int32 try_convert_mov0_reg_to_xor(struct insn_t *);
static struct insn_t *try_convert_vec_to_scalar(struct insn_t *);
static void cnvt_idp_offset(struct flowg_t *, int32); 
static void convert_idp_amode(struct amode_t *, int32);
static int32 insn_offset_access(struct insn_t *, int32);
static void fixup_dpi_export_args(struct flowg_t *);

#ifndef __CVC32__
static void fixup_64bit_constants(struct flowg_t *);
static void fixup_large_model(struct flowg_t *, struct mod_t *);
#endif

extern void __optimize_1mod_flowgraphs(struct mod_t *);
extern void __bld_mod_flowg_ndx(struct mod_t *);
extern void __tryadd_tn_use_in_fg(struct flowg_t *, int32);
extern void __fill_fg_po_bblktab(struct flowg_t *);
extern void __free_1bblk(struct bblk_t *, struct flowg_t *, int32);
extern void __free_1insn(struct insn_t *);
extern void __chk_one_bblk_connectivity(struct bblk_t *);
extern int32 __get_tn_vec_size(struct tn_t *);
extern int32 __get_lowered_tmp_size(struct tn_t *);
extern int32 __get2_par_tni(int32);
extern int32 __amode_mem_ref(struct amode_t *);
extern void __expand_copy(struct insn_t *);
extern void __dmp_mod_insns(struct mod_t *);
extern void __dmp_flowg_insns(struct flowg_t *, struct mod_t *);
extern void __dmp_bblk_backelst(struct bblk_t *, struct flowg_t *,
 struct mod_t *);
extern void __chk_bblk_bedges(struct bblk_t *, struct flowg_t *,
 struct mod_t *); 
extern int32 __count_ndxjmp_lab_setsiz(struct bblk_t **, int32);
extern void __bld_ndxjmp_lab_set(struct bblk_t **, int32);
extern char *__tn_tostr(char *, struct tn_t *, int32);
extern char *__trk_state_tostr(char *, int32);
extern void __dmp_mod_tmp_table(struct mod_t *);
extern size_t __calc_ebp_spill_offset(int32, size_t);
extern word32 __trk_eval_con_oneword_binop(int32 *, int32,
 int32, int32, word32, int32, word32);
extern int32 __get_con_adradd_xvi(int32);
extern int32 __get_asl_insn_retsiz(struct insn_t *, int32 *);
extern int32 __canbe_dst_mem_label(int32);

extern int32 __asl_wide_cmp(word32 *, word32 *, int32, int32);
extern int32 __asl_wide_jmp_eq(word32 *, word32 *, int32);
extern int32 __asl_sgn_wide_cmp(word32 *, word32 *, int32, int32);
extern void __ladd(word32 *, word32 *, word32 *, int32);
extern word32 __get_wrd_con_val(int32);

extern struct insn_info_t *__to_iinfo_rec(int32);
extern struct asl_info_t *__to_aslinfo_rec(int32);
extern char *__to_flowgnam(char *, struct flowg_t *);
extern struct avlnode_t **__linearize_avl_tree(struct avlhd_t *, int32 *);
extern int32 __is_fg_enter_insn(int32); 
extern int32 __gen_tn(int32, int32);
extern int32 __gen_cint_tn(word32);
extern int32 __gen_contab_tn(int32, int32, int32, int32, int32, int32);  
extern struct avlhd_t *__allocinit_avlhd(void);
extern struct bblk_t *__find_add_dup_bblk(struct avlhd_t *, struct bblk_t *);
extern struct tn_dup_t *__find_add_dup_tn(struct avlhd_t *, word32);
extern struct iusedef_t *__alloc_init_iusedef(void);
extern struct insn_t *__insert_insn(struct insn_t *, int32, int32,
 int32, ...);
extern void __linkout_insn(struct insn_t *, int32);
extern void __insert_srcdup_movl(struct insn_t *, int32, struct amode_t *,
 int32);
extern void __copy_amode(struct amode_t *, struct amode_t *);
extern int32 __is_constant(int32);
extern int32 __is_mem_label(int32);
extern void __init_amode(struct amode_t *);
extern int32 __is_nlptr_comlab(int32);
extern void __renumber_fg_insns(struct flowg_t *);
extern word32 __get_wrd_amode_con_val(struct amode_t *);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern void __assign_regs_and_wides_adjacent(struct flowg_t *);
extern int32 __invert_cc(int32);
extern struct avlnode_t * __get_avlnode(void *, struct avlhd_t *); 
extern int32 __is_jmp_insn(int32);
extern char *__my_realloc(void *, size_t, size_t);
extern char *__my_malloc(size_t);
extern void __my_free(void *, size_t);
extern int32 __cmp_amodes(struct amode_t *, struct amode_t *);
#ifndef __CVC32__
extern word32 __get_stack_size(struct flowg_t *, int32);
#endif

extern void __my_fprintf(FILE *, char *, ...);
extern void __misc_terr(char *, int32);
extern void __case_terr(char *, int32);

extern const char *__regs[];

/*
 * ROUTINES TO OPTIMIZE FLOW GRAPH FOR ONE MODULE
 */

/*
 * routine to optimize flow graph for one module
 *
 * SJM 07-26-07 - NOTICE there was a push wrk itstk so can get current mod
 * values (idata size) from inst mod
 */
extern void __optimize_1mod_flowgraphs(struct mod_t *mdp)
{
 int32 fgi, tni, save_nxti, wlen;
 int32 save_removed_bblks, mod_num_asm_insns;
 struct tn_t *tnp;
 struct flowg_t *fgp;
 size_t dsize;

 dsize = __tntab_nxti*sizeof(int32 *);
 __decomposed_tn_nums = (int32 **) __my_malloc(dsize);
 memset(__decomposed_tn_nums, 0, dsize);
 /* need to save because can grow tntab */
 save_nxti = __tntab_nxti;

 /* SJM 05/01/07 - moved declaration to igen dot h and bbgen */
 __trk_num_insn_removed = 0;
 __trk_num_insn_changed = 0;
 save_removed_bblks = __removed_bblks; 

 __bld_mod_flowg_ndx(mdp);
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   fgp = __flowgtab[fgi];

   /* SJM 04/04/07 - need this flowg's flowg context for any dumping */
   /* previously was setting by expand copy by accident */
#ifdef __CVC_DEBUG__
   __cur_ifrom_u = fgp->fg_bblks->ihd->ifru;
#endif

   /* DBG remove -- */
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout, "BEFORE bblk connectivity simplification");
     __dmp_flowg_insns(fgp, mdp);
    }
   /* --- */

   /* remove bblks to simplify flow graph block structure */
   /* start by simplifying bblk structure - creates well formed flow graphs */
   simplify_1fg_bblks(fgp, mdp);
   fgp->fg_num_bblks = count_fg_bblks(fgp); 

   /* need reverse post order bblk numbers required for many of the */
   /* algorithms after here - also build list of entry and exit bblks */ 
   set_rpos_and_ent_bblklst(fgp, mdp);

   /* bld reverse post order bblk tab index once for all initial blks */
   /* can use one global tab since list can tolerate already removed bblks */
   __fill_fg_po_bblktab(fgp);

   /* DBG remove --- */ 
   if (__opt_debug_flg)
    {
     dmp_1fg_rev_po_bblktab(fgp->fg_num_bblks);
   }
   /* --- */

   /* at this point have created as many tn's as possible (except for */
   /* decomposed wide tmps), need to lowered to machine level insns so can */
   /* assign machine registers and ebp stack overflow locations to tns */

   /* this routine doesn't use FUD/dominator records, but reg assign does */
   lower_insns_to_mach_level(fgp, mdp);

   /* SJM 04/03/07 - eliminate all child tn's - needed for value tracking */
   /* BEWARE - after here can't use child tag offsets */
   replace_child_tns(fgp);
  }

 /* now remove all children since can't use after here */
 for (tni = 0; tni < save_nxti; tni++)
  {
   tnp = &(__tntab[tni]);
   tnp->tag_parent_tni = -1;
   tnp->child_tag_offset = 0;
   /* AIV 08/19/09 - was leaking memory here - need to free */
   if (__decomposed_tn_nums[tni] != NULL)
    {
     wlen = __get_tn_vec_size(tnp);
     __my_free(__decomposed_tn_nums[tni], 2*wlen*WRDBYTES);
    }
  }

 __my_free(__decomposed_tn_nums, dsize);
 __decomposed_tn_nums = NULL;


 /* now for every flowg in module simplify using value tracking and then */
 /* finish lowering to x86 maching insns flowg by flowg */
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   fgp = __flowgtab[fgi];

   /* SJM 04/04/07 - need this flowg's flowg context for any dumping */
   /* previously was setting by expand copy by accident */
#ifdef __CVC_DEBUG__
   __cur_ifrom_u = fgp->fg_bblks->ihd->ifru;
#endif

   /* DBG remove -- */
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout, "AFTER removal of child tag offsets\n");
     __dmp_flowg_insns(fgp, mdp);
    }
   /* --- */

   /* bld reverse post order bblk tab index once for all initial blks */
   /* can use one global tab since list can tolerate already removed bblks */
   __fill_fg_po_bblktab(fgp);

   /* SJM 06-10-07 - now value tracking only on if +Ovaltrack on */
#ifdef __VALTRK__
   if (__opt_valtrk)
    {
     bld_fuds_and_simplify_1fg(mdp, fgp);
    }
#endif

   /* SJM 03/15/07 - after value tracking so not part of to mach insn lower */ 
   /* need 2 op insns for x86/AMD architecture for machine reg assignment */
   convert_to_2op_insn(fgp, mdp);

   /* DBG remove --- */ 
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout, "BEFORE limiting resources\n");
     __dmp_flowg_insns(fgp, mdp); 
    }
   /* --- */

   /* assign physical machine registers to tns and determine overflow/wide */ 
   /* ebp stack area locations */
   /* SJM 12/27/06 - FIXME - for now commenting out routine to determine */ 
   /* which register allocator is used (select one) - could run time opti9n */
#ifndef __CVC32__
   fixup_64bit_constants(fgp);
   if (__cvc_use_large_model) fixup_large_model(fgp, mdp);
#endif
   cnvt_idp_offset(fgp, __idp_ti);
   expand_fg_asl_calls(fgp);

   __assign_regs_and_wides_adjacent(fgp);
    
   fixup_coalesced_away_tns(fgp);

   /* final fixup of machine insns - expand asl call boiler plate, fixup */
   /* so X86/AMD64 convention of only 1 mem ref per insn enforced */
   /* plus some peep hole optimization - after here ascii asm generated */
   final_machine_insn_fixup(fgp, mdp);

#ifndef __CVC32__
   /* AIV 11/04/08 - do this twice in case there are registers spills */   
   /* need to add the move for the spilled imm stack location */
   /* movq	$0xfffffffff, -72(%rbp) */
   fixup_64bit_constants(fgp);
#endif

   /* free the optimization data structures for one flow graph */
   /* final fixup does not need any of the sets or predominators */
#ifdef __VALTRK__
   __free_flowg_doms_and_sets(fgp);
#endif

   /* AIV 09/20/10 - if has DPI may have to fixup calls to export DPI calls */
   /* this must be done after register allocation - because if spilled */
   /* need to adjust offset of passed in arguments */
   if (__sv_lib_hdrp != NULL) fixup_dpi_export_args(fgp);
  }


 /* DBG remove -- */
 if (__dump_flowg)
  { 
   __dmp_mod_insns(mdp);
   /* need to dump tmp table after reg numbers set */
   __dmp_mod_tmp_table(mdp);
  }
 /* -- */

 /* SJM 05/01/07 - print insn tracking removed insn stats - new verbose flg */
 if (__opt_trk_verbose && (__trk_num_insn_removed > 0
  || __trk_num_insn_changed > 0))
  {
   mod_num_asm_insns = cnt_mod_insns();
   __my_fprintf(stdout,
    "++VAL TRK(%s): %d insns of %d removed, %d changed, %d bblks removed.\n",
    mdp->msym->synam, __trk_num_insn_removed, mod_num_asm_insns,
    __trk_num_insn_changed, __removed_bblks - save_removed_bblks);
  }
}


/*
 * convert idp offsets to ndx reg disp of idp reg offset
 */
static void cnvt_idp_offset(struct flowg_t *fgp, int32 idp_ti) 
{
 int32 tni;
 struct insn_t *ip;
 struct bblk_t *bbp;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     /* DBG remove -- */
     if (ip->res_tni != -1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* SJM 12/01/07 - illegal to gen an instruction that use __idp - NLO */
     /* idp label as src */
     /* DBG remove -- */
     if (ip->isrc.amode == AM_NLO && ip->isrc.amode == NLO_IDP)
      __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* AIV 12/04/08 - no longer handle the case for the asl wrapper */
     /* calls these are handled in expand_one_asl_call */
     tni = ip->isrc.am_tni;
     if (tni != -1)
      {
       if (tni == idp_ti)
        {
         if (insn_offset_access(ip, idp_ti))
          {
           continue;
          }
#ifdef __CVC32__
         convert_idp_amode(&(ip->isrc), FALSE);
#else
         convert_idp_amode(&(ip->isrc), ip->is_large_ofs);
#endif
        }
      }

     tni = ip->idst.am_tni;
     if (tni == idp_ti)
      {
#ifdef __CVC32__
       convert_idp_amode(&(ip->idst), FALSE);
#else
       convert_idp_amode(&(ip->idst), ip->is_large_ofs);
#endif
      }
    }
  }
}

/*
 * need to access address of $esi + 8
 * AIV 12/04/08 - changed this to take one leal with the correct offset
 * there was no need to do the mov/add - this results in only one leal insn
 */
static int32 insn_offset_access(struct insn_t *ip, int32 idp_ti)
{
 struct amode_t *amp;
 int32 newtmp_ti;

 amp = &(ip->isrc);
 /* DBG remove -- */
 if (amp->am_tni != idp_ti) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 if (amp->amode != AM_IDP_ADR_OFS) return(FALSE);

 if (ip->opcod == I_ADDL || ip->opcod == I_MOVA)
  {
   newtmp_ti = __gen_tn(SR_CINT, WBITS);
   __insert_insn(ip, FALSE, I_LEAL, AM_NDXREG_DISP, IDP_REG, 
    amp->disp, AM_REG, newtmp_ti);
   /* AIV 11/02/07 - due to the coal of registers must set type to tn adr */
   /* because coal of register may be passed to wrapper and when the wrappers */
   /* are expanded the type is needed */
   __tntab[newtmp_ti].tn_typ = TN_ADR;
   amp->amode = AM_REG;
   amp->am_tni =  newtmp_ti;
   return(TRUE);
  }
 else __misc_terr(__FILE__, __LINE__);
 return(FALSE);
}
           
/*
 * convert an __idp address to an offset of %esi
 */
static void convert_idp_amode(struct amode_t *amp, int32 is_large_ofs)
{
 /* DBG remove -- */
 if (amp->amode == AM_LABEL || amp->amode == AM_IDP_ADR_OFS) 
  __misc_terr(__FILE__, __LINE__);
 /* ---- */
 amp->am_tni = IDP_REG;
#ifndef __CVC32__
 /* AIV 09/07/11 - if this is adjusted for +large model must leave */
 /* as AM_REG - regular idp reg %r15 here */
 if (is_large_ofs) 
  {
   amp->amode = AM_REG;
   return;
  }
#endif
 if (amp->disp == 0) amp->amode = AM_NDXREG;
 else amp->amode = AM_NDXREG_DISP;
}

/*
 * AIV 09/20/10 - if has DPI may have to fixup calls to export DPI calls 
 * this must be done after register allocation - because if spilled 
 * need to adjust offset of passed in arguments 
 */
static void fixup_dpi_export_args(struct flowg_t *fgp)
{
 word32 stack_size;
 struct insn_t *ip;
 struct bblk_t *bbp;
 struct amode_t *srcp;
 int32 callee_count;

 /* have to get the stack size - this code take from v_asmlnk.c */
 callee_count = 0;
#ifdef __CVC32__
 if (fgp->uses_ebx) callee_count++;
 if (fgp->uses_edi) callee_count++;
 if (fgp->uses_esi) callee_count++;
 if (fgp->uses_ebp) callee_count++;
#else
 if (fgp->uses_ebx) callee_count++;
 if (fgp->uses_ebp) callee_count++;
 if (fgp->uses_r12) callee_count++;
 if (fgp->uses_r13) callee_count++;
 if (fgp->uses_r14) callee_count++;
 if (fgp->uses_r15) callee_count++;
#endif

#ifdef __CVC32__
 if (fgp->has_overflow)
  {
   stack_size = WRDBYTES *
     (fgp->ebp_wrd_area_siz+fgp->max_call_args+callee_count);
  }
 else stack_size = WRDBYTES*(fgp->max_call_args);
#else
 if (!fgp->has_overflow)
  {
   stack_size = callee_count*WRDBYTES;
   if ((stack_size % 16) != 0)
    {
     stack_size += 8;
    }
  }
 else if (callee_count >= 1)
  {
   stack_size = __get_stack_size(fgp, callee_count);
  }
 else if (fgp->has_overflow)
  {
   stack_size = __get_stack_size(fgp, 0);
  }
#endif

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp; 
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     /* check for flag */
     if (!ip->is_export_stack) continue;
     
     /* only need to check source since to passing into storage */
     srcp = &(ip->isrc);
     srcp->disp += (stack_size);
    }
  }
}


#ifndef __CVC32__

/* AIV 09/07/11 - this the max constant for 64-bit until offsets/etc must */
/* be moved into a reg */
#define MAX64_CONSTANT 0x7fffffff

/*
 * 64-bit cannot do operations on a > 64 bit constant value so
 * must first be loaded into a register
 *
 * convert 
 * andq	$0xffffffff, -48(%rbp)
 * =>
 * movq	$0xffffffff, %rax
 * andq	%rax, -48(%rbp)
 */
static void fixup_64bit_constants(struct flowg_t *fgp)
{
 word32 val;
 int32 tni, am_type;
 struct bblk_t *bbp;
 struct insn_t *ip, *ip2, *new_ip;
 struct amode_t *srcp, *dstp;
 struct tn_t *tnp;
 struct insn_info_t *iip;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp; 
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     iip = __to_iinfo_rec(ip->opcod);
    
     /* AIV 11/13/08 - 64-bit must record if fg uses specail xmm regs */
     if (iip->iclass == ICLASS_REAL_NORD)
      {
       fgp->has_real_ops = TRUE;
      }
//movq with wide needs a move as well for dst with memory
     if (iip->iclass == ICLASS_STORE || iip->iclass == ICLASS_MOV)
      {
       dstp = &(ip->idst);
       if (!__amode_mem_ref(dstp)) continue;
      }
     else if (iip->iclass != ICLASS_BIN && iip->iclass != ICLASS_CMP) 
      {
       continue;
      }

     srcp = &(ip->isrc);
     tni = srcp->am_tni;
     if (tni == -1) continue;
     tnp = &(__tntab[tni]);
     if (tnp->comlab_typ != COMLAB_CINT && tnp->comlab_typ != COMLAB_CONADR)
       continue;
     val = __get_wrd_amode_con_val(srcp);
     /* AIV 01/05/10 - this must only move constants for this larger const */
     if (val <= MAX64_CONSTANT) continue;
     if (tnp->tn_typ == TN_ADR) am_type = AM_NDXREG;
     else am_type = AM_REG;
     new_ip = __insert_insn(ip, FALSE, I_MOVQ, am_type, tni, AM_REG, OFLW_REG);
     /* copy src to src constant amode */
     *(&(new_ip->isrc)) = *srcp;
     __init_amode(srcp);
     srcp->am_tni = OFLW_REG;
     srcp->amode = AM_REG;
    }
  }
}

/*
 * fixup special static memory areas to fit the 64-bit large model
 *
 */
static void fixup_large_model(struct flowg_t *fgp, struct mod_t *mdp)
{
 int32 src_tni, dst_tni, reg_ti;
 struct bblk_t *bbp;
 struct insn_t *ip, *ip2, *new_ip;
 struct amode_t *srcp, *dstp;
 struct tn_t *tnp;
 size_t disp;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp; 
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     srcp = &(ip->isrc);
     src_tni = srcp->am_tni;
     if (src_tni == -1) continue;
     tnp = &(__tntab[src_tni]);

     dstp = &(ip->idst);
     dst_tni = dstp->am_tni;
     /* AIV 09/07/11 - think +large was always wrong need to move and add */
     /* to get offset would compile but would segv */
     /* movq	2147552152(%r15), %rdx */
     /* converts to this
     =>
        movabsq	$2147552224, %rbx
        addq	%r15, %rbx
        movq	(%rbx), %rdx
     */
     if (srcp->amode == AM_NDXREG_DISP)
      {
       disp = srcp->disp;
       if (disp > MAX64_CONSTANT) 
        {
	 reg_ti = __gen_tn(SR_CINT, WBITS);
         /* cannot just pass as AM_IMM - because these are cap at size int */
         /* so just pass as AM_NDXREG_DISP pass offset and set back */
         /* to 64-bit constant */
         new_ip = __insert_insn(ip, FALSE, I_MOVABSQ, AM_NDXREG_DISP, reg_ti, 
          disp, AM_REG, reg_ti);
         new_ip->is_large_ofs = TRUE;
         new_ip->isrc.amode = AM_IMM; 
         new_ip->isrc.disp = disp; 
         new_ip->isrc.am_tni = -1; 

         /* now do the add */
         new_ip = __insert_insn(new_ip, TRUE, I_ADDQ, AM_REG, srcp->am_tni, 
          AM_REG, reg_ti);
         new_ip->is_large_ofs = TRUE;

         srcp->amode = AM_NDXREG;
         srcp->am_tni = reg_ti;
         srcp->disp = 0;
        }
      }
     /* AIV 09/07/11 - think +large was always wrong need to move and add */
     /* to get offset would compile but would segv */
     /*  movabsq	$__tevdat_0, 32212254784(%r15)  */
     /* converts to this
     =>
     movabsq	$__tevdat_0, %rax
     movabsq	$2147552224, %rbx
     addq	%r15, %rbx
     movq	%rax, (%rbx)
     */
     if (dstp->amode == AM_NDXREG_DISP)
      {
       disp = dstp->disp;
       if (disp > MAX64_CONSTANT) 
        {
	 reg_ti = __gen_tn(SR_CINT, WBITS);
         new_ip = __insert_insn(ip, FALSE, I_MOVABSQ, AM_NDXREG_DISP, reg_ti, 
          disp, AM_REG, reg_ti);
         new_ip->is_large_ofs = TRUE;
         new_ip->isrc.amode = AM_IMM; 
         new_ip->isrc.disp = disp; 
         new_ip->isrc.am_tni = -1; 
         new_ip = __insert_insn(new_ip, TRUE, I_ADDQ, AM_REG, dstp->am_tni, 
          AM_REG, reg_ti);
         new_ip->is_large_ofs = TRUE;
         dstp->amode = AM_NDXREG;
         dstp->am_tni = reg_ti;
         dstp->disp = 0;
        }
      }

     /* fixup the fixed comlab */
     if (tnp->comlab_typ != COMLAB_NONE)
      {
       if (tnp->comlab_typ != COMLAB_IDP && tnp->comlab_typ != COMLAB_CONADR
           && tnp->comlab_typ != COMLAB_CINT)
        {
         /* DBG remove -- */
         if (ip->opcod != I_MOVQ && ip->opcod != I_STOREQ && 
             ip->opcod != I_MOVL && ip->opcod != I_STOREL &&
#ifdef __CVC32__
             ip->opcod != I_CMPL) 
#else
             /* AIV 03/27/12 - can now have I_MOVABSQ here as well */
             ip->opcod != I_CMPL && ip->opcod != I_MOVABSQ) 
#endif
            __misc_terr(__FILE__, __LINE__);
         if (dst_tni == -1) __misc_terr(__FILE__, __LINE__);
         /* -- */
 
         /* special filter compare address (filter) idp */
         if (ip->opcod == I_CMPL) 
          {
           /* DBG remove -- */
           if (tnp->comlab_typ != COMLAB_IDPDAT)
              __misc_terr(__FILE__, __LINE__);
           /* -- */
	   /* cmpq	$__idpdat_1 + 120, %r15 */
	   /* => movabsq	$__idpdat_1 + 120, %r12 */
	   /* => cmpq	        %r12, %r15 */
	   reg_ti = __gen_tn(SR_CINT, WBITS);
           new_ip = __insert_insn(ip, FALSE, I_MOVABSQ, AM_NDXREG, src_tni, 
            AM_REG, reg_ti);
           new_ip->isrc = *srcp;
           ip->isrc.amode = AM_REG;
           ip->isrc.am_tni = reg_ti;
           continue;
          }
         //AIV FIXME - COMLAB_DEL ??????
         /* if is nlptr need the extra move */
         if (__is_nlptr_comlab(tnp->comlab_typ) || 
             tnp->comlab_typ == COMLAB_DEL)
          {
           ip->opcod = I_MOVABSQ;
           /* mark special label to print as address with $ */
           ip->isrc.is_large_label = TRUE;
           __insert_insn(ip, TRUE, I_MOVQ, AM_NDXREG, dst_tni, AM_REG, 
            dst_tni);
          }
         else if (__is_mem_label(dst_tni))
          {
           /* cannot do this for movabsq need the extra move */
	   /* movabsq	$__tevdat_0, 32212254784(%r15) */
	   reg_ti = __gen_tn(SR_CINT, WBITS);
           __insert_insn(ip, FALSE, I_MOVABSQ, AM_REG, src_tni, AM_REG, 
            reg_ti);

           srcp->amode = AM_REG;
           srcp->am_tni = reg_ti;
          }
         else ip->opcod = I_MOVABSQ;
        }
      }
     if (dst_tni == -1) continue;
     if (dst_tni < HIGH_X86_REG) continue;

     tnp = &(__tntab[dst_tni]);
     if (tnp->comlab_typ != COMLAB_NONE)
      {
       if (!__is_nlptr_comlab(tnp->comlab_typ)) continue;
       /* DBG remove -- */
       __misc_terr(__FILE__, __LINE__);
       /* ---- */
      }
    }
  }
}
#endif

/*
 * count number of insns in a module 
 * this routine assumes mod's flowg index build and good
 */
static int32 cnt_mod_insns(void)
{
 int32 fgi, mod_num_insns;
 struct flowg_t *fgp;
 struct bblk_t *bbp;

 mod_num_insns = 0;
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   fgp = __flowgtab[fgi];
   for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
    {
     mod_num_insns += cnt_bblk_insns(bbp);
    }
  }
 return(mod_num_insns);
}

/*
 * debugging routine to count number of insns in a bblk
 */
static int32 cnt_bblk_insns(struct bblk_t *bbp)
{
 int32 bblk_inum;
 struct insn_t *ip;

 bblk_inum = 0;
 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
  {
   switch (ip->opcod) {
    case I_BBLK_LABEL: case I_ENTER_PROC: case I_ENTER_NB_PROC: 
    case I_ENTER_THD_RET: case I_ENTER_DECL: case I_ENTER_NPP:
    case I_ENTER_CAP: case I_ENTER_ICONN:
    case I_ENTER_GATECA: case I_MULTFI_SUBR: case I_SUSPEND: case I_COMPLETE:
    case I_ENTER_GATEDA:
    case I_PROLOGUE: case I_EPILOGUE: case I_DEFLST:
    case I_DIRECTIVE: case I_LABEL: case I_ENTER_LABEL: case I_ENTER_PORT:
    case I_ENTER_MDC:
     break;
    default: bblk_inum++; 
   }
  }
 return(bblk_inum);
} 


/*
 * ROUTINES TO BUILD SIMPLE PROC AND NET TAB OF FLOW GRAPHS IN ONE MODULE
 */

/*
 * build an index array containing all flow graphs in a module
 *
 * this saves needing to maintain complex linked list
 */
extern void __bld_mod_flowg_ndx(struct mod_t *mdp)
{
 int32 ni, i, num, pbi;
 struct flowg_t *fgp;
 struct net_t *np;
 struct conta_t *cap, *pb_cap;
 struct task_t *tskp;
 struct np_iconn_t *npicp;
 struct gate_conta_t *gcp;
 struct gate_da_list_t *gdap;
 struct net_chg_t *ncp;
 struct avlnode_t **avltab;
 
 __flowg_lasti = -1;
 for (fgp = mdp->mod_flowg; fgp != NULL; fgp = fgp->flowgnxt)
  {
   if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
   __flowgtab[__flowg_lasti] = fgp;
  }
 /* SJM 11/14/05 - can be at leat 3 flow graphs now from MFI subrs */
 for (np = &(mdp->mnets[0]), ni = 0; ni < mdp->mnnum; ni++, np++)
  {
   if (np->nflowg == NULL) continue;

   if (np->nlds != NULL) add_mipd_flowg(np);

   for (fgp = np->nflowg; fgp != NULL; fgp =fgp->flowgnxt)
    {
     if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
     __flowgtab[__flowg_lasti] = fgp;
    }
  }
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     if (np->nflowg == NULL) continue;

     if (np->nlds != NULL) add_mipd_flowg(np);

     /* still think only max of 2 task reg flow graphs */
     for (fgp = np->nflowg; fgp != NULL; fgp = fgp->flowgnxt)
      {
       if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
       __flowgtab[__flowg_lasti] = fgp;
      }
    }
  }
 /* AIV 01/16/07 - contas are now treated as a seperate flowg */
 for (ni = 0; ni < mdp->mcanum; ni++)
  {
   cap = &(mdp->mcas[ni]);
   if (cap->flowg == NULL) continue;
   if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
   __flowgtab[__flowg_lasti] = cap->flowg;
   if (cap->ca_pb_sim)
    {
     for (pbi = 0; pbi < cap->lhsx->szu.xclen; pbi++)
      { 
       pb_cap = &(cap->pbcau.pbcaps[pbi]);
       if (pb_cap->flowg == NULL) continue;
       if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
       __flowgtab[__flowg_lasti] = pb_cap->flowg;
      }
    }
  }


 /* AIV 02/13/07 - iconn's are now a seperate flowg */
 /* AIV 10/06/08 - if code is inlined don't need iconn fgs */
 if (!__inline_code)
  {
   avltab = __linearize_avl_tree(__np_iconn_dup_tn_tree, &(num));
   for (i = 0; i < num; i++)
    {
     npicp = (struct np_iconn_t *) avltab[i]->valp;
     if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
     /* DBG remove -- */
     if (npicp->fgp == NULL) __misc_terr(__FILE__, __LINE__);
     /* -- */
     __flowgtab[__flowg_lasti] = npicp->fgp;
    }
   __my_free(avltab, num*sizeof(struct avlnode_t *)); 
 
   /* AIV 02/15/07 - scalar conta (gate) now a seperate flowg */
   avltab = __linearize_avl_tree(__gate_conta_dup_tn_tree, &(num));
   for (i = 0; i < num; i++)
    {
     gcp = (struct gate_conta_t *) avltab[i]->valp;
     if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
     /* DBG remove -- */
     if (gcp->fgp == NULL) __misc_terr(__FILE__, __LINE__);
     /* -- */
  
     __flowgtab[__flowg_lasti] = gcp->fgp;
    }
   __my_free(avltab, num*sizeof(struct avlnode_t *)); 
  }

 /* AIV 06/13/07 - add back end gates with delay assign flow graphs */
 for (gdap = __hd_gdap; gdap != NULL; gdap = gdap->nxt)
  {
   if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
   __flowgtab[__flowg_lasti] = gdap->fgp;
  }

 /* AIV 01/09/08 - this need to be mtotvarnum - was skipping tasks */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
    {
     if (ncp->nchg_fgp != NULL)
      {
       if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
       __flowgtab[__flowg_lasti] = ncp->nchg_fgp;
      }
     if (ncp->wire_fgp != NULL)
      {
       if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
       __flowgtab[__flowg_lasti] = ncp->wire_fgp;
      }
     /* only add if net type < NONWIRE_ST */
    if (ncp->process_nchg_fgp == NULL) continue;
    if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
    __flowgtab[__flowg_lasti] = ncp->process_nchg_fgp;
   }
  }
}
   

/*
 * add mipd flow graph backend
 */
static void add_mipd_flowg(struct net_t *np)
{
 struct net_pin_t *npp;

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt) 
  {
   if (npp->npntyp != NP_MIPD_NCHG) continue;
   
   /* DBG remove -- */
   if (npp->npp_fgp == NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */

   if (++__flowg_lasti >= __flowgtabsiz) grow_flowgtab();
   __flowgtab[__flowg_lasti] = npp->npp_fgp;
  }
}

/*
 * grow module flow graph table
 */
static void grow_flowgtab(void)
{
 size_t osize, nsize;

 /* AIV 06/17/09 - changed these to size_t */
 osize = __flowgtabsiz*sizeof(struct flowg_t *);
 __flowgtabsiz = (4*__flowgtabsiz)/3; 
 nsize = __flowgtabsiz*sizeof(struct flowg_t *);
 __flowgtab = (struct flowg_t **) __my_realloc(__flowgtab, osize, nsize);
}

/*
 * count the number of bblks in a flow graph
 */
static int32 count_fg_bblks(struct flowg_t *fgp) 
{
 int32 nbblks;
 struct bblk_t *bbp;

 for (nbblks = 0, bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   nbblks++;
  }
 /* need to add the dummy entry bblk (since can be many AFS enters) */
 nbblks++;
 return(nbblks);
}

/*
 * BASIC BLOCK CONNECTIVITY SIMPLIFYING ROUTINES
 */

/*
 * routine to simplify on flow graphs basic block structure
 */
static void simplify_1fg_bblks(struct flowg_t *fgp, struct mod_t *mdp)
{
 int32 sav_rm_bblks;

 sav_rm_bblks = __removed_bblks;

 /* first remove all bblks unreachable from an AFS */
 rm_afs_unreachable_bblks(fgp);

 /* DBG remove --
 if (__opt_debug_flg)
  {
    __my_fprintf(stdout, "AFTER bblks unreachable from AFS removed\n");
   __dmp_flowg_insns(fgp, mdp);
  }
 --- */

 /* DBG remove --
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "AFTER pre-optimzie rm and merge of bblks\n");
   __dmp_flowg_insns(fgp, mdp);
  }
 --- */

 remove_empty_bblks(fgp);
 check_bad_or_unreachable_bblks(fgp);
 remove_jmponly_bblks(fgp, mdp);
 /* AIV 10/09/10 - moved this routine below the jump only blocks */
 /* this routine is inefficient then it does merge_blocks-> subst_backedges */
 /* subst_backedges should be fixed - but most are just jump only blocks */
 /* so these will be removed by here */

 /* AIV 02/01/12 - these routines really do not do anything besides remove */
 /* fallthru blocks - which are removed anyways */
 /* these are inefficient due to subst_backedges - I believe gets into */
 /* trouble for index jumps - could try skipping index jump blocks */
 /* (cbbp->is_casejmp_item)  - but just commenting out for now */
 /* need to remove bblk with no back edges and merge uncond jmp bblks */
 /* when possible */
 //rm_and_merge_bblks(fgp, FALSE);
 //merge_uncond_1entry_bblks(fgp, mdp);
 
 /* DBG remove -- */
 if (__opt_debug_flg && __removed_bblks > sav_rm_bblks) 
  {
   __my_fprintf(stdout, "&& %d bblks removed from flow graph bblk simplify:\n",
    __removed_bblks - sav_rm_bblks);
   __dmp_flowg_insns(fgp, mdp);
  }
 /* --- */ 
}

/*
 * mark all bblks reachable from an after suspend bblks
 * bblks not marked are unreachable and are removed
 *
 * unreachable connected components gened from forever's with delay controls
 *
 * routine is tricky and needs successor traversal because must be
 * called before any of the entry-exit, reverse post order numbering
 * or dominators built
 */
static void rm_afs_unreachable_bblks(struct flowg_t *fgp)
{
 int32 rm_bblks;
 struct bblk_t *bbp, *bbp2;
 struct bbedge_t *bbep, *bbep2;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   bbp->afs_reachable = FALSE;
  }
 /* first turn off unreachable bits (reachable t) */ 
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   if (!bbp->after_suspend) continue;
   __cur_mark++;
   early_mark_reachable(bbp);
  }
 rm_bblks = 0;
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp2)
  {
   bbp2 = bbp->bbnxt;

   if (bbp->afs_reachable) continue;

   /* remove the back edge since just part of unreachable cycle */
   for (bbep = bbp->bbe_prev; bbep != NULL; bbep = bbep2)
    {
     bbep2 = bbep->bbenxt;
     __my_free(bbep, sizeof(struct bbedge_t));
    }
   bbp->bbe_prev = NULL;

   /* must remove back edges for this routine to work */
   track_rm_1bblk(bbp, fgp, FALSE);
   rm_bblks++;
  }
 /* AIV 10/14/10 - this needs two passes track_rm_1bblk - will just mark */
 /* the block for removal.  valgrind was complaining about reading of */ 
 /* freed memory from within track_rm_1bblk */
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp2)
  {
   bbp2 = bbp->bbnxt;
   if (bbp->mark_for_rm) __free_1bblk(bbp, fgp, TRUE);
  }
 /* DBG remove -- */
 if (__opt_debug_flg && rm_bblks > 0)
  {
   __my_fprintf(stdout,
    "== %d unreachable from AFS bblks removed from fg %s\n", rm_bblks,
    __to_flowgnam(__xs, fgp));
  }
}

/*
 * turn off unreachable bit for all bblks reachable from passed bblk
 */
static void early_mark_reachable(struct bblk_t *bbp)
{
 int32 jti, jt_set_starti, jt_set_endi;
 struct insn_t *ip;
 struct ndxjmp_t *ndxjp;

 /* already visited */
 if (bbp->mark == __cur_mark) return;
 bbp->afs_reachable = TRUE;
 bbp->mark = __cur_mark;

 ip = bbp->itail;
 if (ip->opcod == I_BBLK_JMP) 
  {
   early_mark_reachable(ip->idst.apu.bbp);
  }
 else if (ip->opcod == I_COND_JMP || ip->opcod == I_REAL_COND_JMP)
  {
   early_mark_reachable(ip->isrc.apu.bbp);
   early_mark_reachable(ip->idst.apu.bbp);
  }
 /* AIV 05/07/07 - should never get an index port jump */
 /* DBG remove -- */
 else if (ip->opcod == I_PORT_IND_JMP) __case_terr(__FILE__, __LINE__);
 /* -- */
 else if (ip->opcod == I_IND_JMP)
  {
   ndxjp = ip->extrau.ndxjp;

   jt_set_starti = ndxjp->jtabstart;
   jt_set_endi = jt_set_starti + ndxjp->jtabsiz;
   for (jti = jt_set_starti; jti < jt_set_endi; jti++)
    {
     early_mark_reachable(ndxjp->bbtab[jti]);
    }
  }
 /* nothing to do for the other bblk end insns */
}

/*
 * remove unreachable bblks
 *
 * called after value tracking optimization not here
 */
static void rm_and_merge_bblks(struct flowg_t *fgp, int32 rebuild_rpo)
{
 int32 chged, sav_rm_bblks, nremoved, npasses;
 struct bblk_t *bbp, *bbp2;
 struct bblk_t *jmpto_bbp;
 struct bblklst_t *bblp;

 sav_rm_bblks = __removed_bblks;
 npasses = 0;
 chged = TRUE;
 while (chged)
  {
   npasses++;
   chged = FALSE;
   
   /* first remove all the no back edge routines */ 
   for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp2)
    {
     bbp2 = bbp->bbnxt;

     if (!bbp->after_suspend && bbp->bbe_prev == NULL)
      {
       track_rm_1bblk(bbp, fgp, TRUE);
       chged = TRUE;
      }
    }
   
   /* then try to merge together uncond jmp bblks with back edge */
   for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp2)
    {
     bbp2 = bbp->bbnxt;

     if (bbp->itail->opcod != I_BBLK_JMP) continue;
     jmpto_bbp = bbp->itail->idst.apu.bbp;

     if (jmpto_bbp->after_suspend) continue;
     /* if jump to bblk has more than one edge, can't do more */
     if (jmpto_bbp->bbe_prev != NULL && jmpto_bbp->bbe_prev->bbenxt != NULL)
      continue;

     merge_bblks(fgp, bbp, jmpto_bbp);  

     /* SJM 12/10/06 - if bbp2 being removed must adjust to next */
     if (bbp2 == jmpto_bbp) bbp2 = jmpto_bbp->bbnxt;

     /* SJM 12/10/06 - since guts of merge from gone, only this frees it */
     if (rebuild_rpo) __bblktab[jmpto_bbp->revpostordno] = NULL;
     __free_1bblk(jmpto_bbp, fgp, TRUE);
     __removed_bblks++;
     chged = TRUE;
    }
  }
 nremoved = __removed_bblks - sav_rm_bblks;
 if (nremoved == 0) 
  { 
   /* DBG remove --- */
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout, "&& - no unreachable or mergable bblks removed\n");
    }
   /* --- */
   return;
  }
 
 /* AIV 12/12/06 - if don't need to rebuild rpo numbers - skip */
 if (rebuild_rpo)
  {
   /* some removed - must rebuild the rpo numbers */
   fgp->fg_num_bblks = count_fg_bblks(fgp); 
   __rev_po_ndx = fgp->fg_num_bblks;
   __cur_mark++;
   /* set new reverse post order numbers after tracking optimize */
   for (bblp = fgp->enter_bblks; bblp != NULL; bblp = bblp->bl_nxt)  
    {
     set_bblk_rev_postorder_nums(bblp->bl_bbp, NULL);
    }
   /* build the new bblk rpo index */
   __fill_fg_po_bblktab(fgp);
   __cur_bbp = NULL;
  }
 /* DBG remove --- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout,
    "&& - %d unreachable or mergeable bblks removed in %d passes\n",
    nremoved, npasses);
  }
 /* --- */
}


/*
 * during value tracking - change from cond to uncond jump exposed
 * a bblk that now has no back edges, this routine removes it 
 *
 * this is simplified routine to removed one unreachable non AFS bblk
 * and removed back edges for bblks it jumped to
 *
 * does not try to recursively removed other newly removable bblks
 */
static void track_rm_1bblk(struct bblk_t *rm_bbp, struct flowg_t *fgp,
 int32 free_bblk)
{
 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "&& removing B%d - no back edges\n",
    rm_bbp->bblk_seqno);
  }
 /* --- */ 

 /* DBG remove -- */
 if (rm_bbp->after_suspend) __misc_terr(__FILE__, __LINE__);
 if (rm_bbp->bbe_prev != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* update index so will not see if RPO number later */
 /* SJM 12/17/06 - now can be called before RPO numbers set, so check */
 if (rm_bbp->revpostordno != -1) __bblktab[rm_bbp->revpostordno] = NULL;

 /* remove back edges - tricky because of possible rm bblk index jumps */
 /* SJM 12/10/06 - using this for remove of merge in - in that case */
 /* there is no jump to since merge already updated it */
 track_rm_jmpto_back_edges(rm_bbp);

 /* free block removes all insn when passed TRUE */
 /* AIV 10/14/10 - only remove if flag is true otherwise - mark for later */
 /* removal */
 if (free_bblk) __free_1bblk(rm_bbp, fgp, TRUE);
 else rm_bbp->mark_for_rm = TRUE;
 __removed_bblks++;
}

/* 
 * for tracking - routine to remove all back edges of jumped to bblks
 * for a removed bblk
 *
 * notice suspend and task jmp do not have back edges
 */
static void track_rm_jmpto_back_edges(struct bblk_t *rm_bbp)
{
 int32 tabi, tabsiz;
 struct bblk_t *jmpto_bbp;
 struct insn_t *end_ip;
 struct insn_info_t *iip;
 struct ndxjmp_t *ndxjp;

 end_ip = rm_bbp->itail;
 iip = __to_iinfo_rec(end_ip->opcod);

 if (iip->iclass == ICLASS_JMP)
  {
   if (end_ip->opcod == I_BBLK_JMP)
    {
     jmpto_bbp = end_ip->idst.apu.bbp;
     rm_one_bbedge(rm_bbp, jmpto_bbp);
    }
   else if (end_ip->opcod == I_COND_JMP || end_ip->opcod == I_REAL_COND_JMP)
    {
     jmpto_bbp = end_ip->isrc.apu.bbp;
     rm_one_bbedge(rm_bbp, jmpto_bbp);
     jmpto_bbp = end_ip->idst.apu.bbp;
     rm_one_bbedge(rm_bbp, jmpto_bbp);
    }
   else __case_terr(__FILE__, __LINE__);
  }
 else if (iip->iclass == ICLASS_NDXJMP)
  {
   ndxjp = end_ip->extrau.ndxjp;
   /* DBG remove -- */
   if (ndxjp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   tabsiz = ndxjp->jtabstart + ndxjp->jtabsiz;
   for (tabi = ndxjp->jtabstart; tabi < tabsiz; tabi++)
    {
     jmpto_bbp = ndxjp->bbtab[tabi]; 
     rm_one_bbedge(rm_bbp, jmpto_bbp);
    }
  }
 /* for any other type of end (complete/suspend) no back edges to remove */
}


/*
 * remove empty bblks
 * SJM 01/05/06 - BEWARE from here for bpo number require unreachable removed 
 */
static void remove_empty_bblks(struct flowg_t *fgp)
{
 struct bblk_t *bbp, *bbp2;
 struct insn_t *ip, *ip2;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp2)
  {
   bbp2 = bbp->bbnxt;

   __cur_bbp = bbp;
   ip = bbp->ihd; 
//SJM? FIXME 
   /* for now must leave enter (AFS) bblks since needed for scheduler */
   if (is_enter_insn(ip->opcod)) continue;

   if (ip->opcod == I_BBLK_LABEL) 
    {
     if ((ip2 = ip->inxt) == NULL) __case_terr(__FILE__, __LINE__);
     if (ip2->opcod == I_EPILOGUE) 
      {
       if ((ip2 = ip2->inxt) == NULL) __case_terr(__FILE__, __LINE__);
       if (ip2->opcod == I_COMPLETE)
        {
         /* DBG remove --- */
         if (ip2->inxt != NULL) __case_terr(__FILE__, __LINE__);
         /* --- */ 
         /* case 1: bblk unreachable */
         if (bbp->bbe_prev == NULL)
          {
           /* unreachable bblks much be removed */
           __free_1bblk(bbp, fgp, TRUE);
          }
        }
      }
    }
  }
 __cur_bbp = NULL;
}


/*
 * return T if enter bblk insn (real entry or AFS) 
 */
static int32 is_enter_insn(int32 opcod)
{
 switch (opcod) {
  case I_ENTER_PROC: 
  case I_ENTER_THD_RET: 
  case I_ENTER_NB_PROC:
  case I_ENTER_DECL: 
  case I_ENTER_NPP: 
  case I_ENTER_MDC:
    return(TRUE);
   break;
  }
 return(FALSE);
}

/*
 * check to make sure there are no unreachable bblks - shouldb
 */
static void check_bad_or_unreachable_bblks(struct flowg_t *fgp)
{
 struct bblk_t *bbp;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp;
   if (!bbp->after_suspend && bbp->bbe_prev == NULL)
    {
     /* DBG remove -- */
     __misc_terr(__FILE__, __LINE__);
     /* ---- */
     continue;
    }
   if (bbp->ihd == NULL) __misc_terr(__FILE__, __LINE__);
// SJM? - SOMEWHERE SHOULD JUST REMOVE THESE IF HAPPEN
   if (bbp->itail->opcod == I_COND_JMP || bbp->itail->opcod == I_REAL_COND_JMP)
    {
     if (bbp->itail->isrc.apu.bbp == bbp->itail->idst.apu.bbp) 
      __misc_terr(__FILE__, __LINE__);
    }
  }
 __cur_bbp = NULL;
}

/* 
 * link out basic blocks that only contain one unconditional jump
 */
static void remove_jmponly_bblks(struct flowg_t *fgp, struct mod_t *mdp)
{
 int32 sav_rm_bblks, rm_bblks, chged, num_passes;
 struct bblk_t *bbp, *bbp2;
  
 sav_rm_bblks = __removed_bblks;

 for (num_passes = 1;; num_passes++)
  {
   chged = FALSE;
   for (bbp = fgp->fg_bblks; bbp != NULL;)
    {
     bbp2 = bbp->bbnxt;

     /* DBG remove -- */
     if (bbp->ihd == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     if (bbp->ihd->opcod == I_BBLK_LABEL
      && bbp->ihd->inxt->opcod == I_BBLK_JMP && bbp->ihd->inxt == bbp->itail)
      {
       rm_1endjmp_bblk(bbp, fgp, mdp);
       __free_1bblk(bbp, fgp, TRUE);
       __removed_bblks++;
       chged = TRUE;
      }
     bbp = bbp2;
    } 
   if (!chged) break;
  }
 rm_bblks = __removed_bblks - sav_rm_bblks;
 if (__opt_debug_flg && rm_bblks > 0)
  {
   __my_fprintf(stdout,
    "== %d uncond jmp only bblks removed from fg %s in %s (%d passes)\n",
    rm_bblks, __to_flowgnam(__xs, fgp), mdp->msym->synam, num_passes);
  }
}

/*
 * routine to remove one basic block that only contains a jump
 * (not cond jump) insn
 *
 * blocks that jump to it must jump to where it jumps too
 * notice can't remove index or conditional jumps - must simplify first
 */
static void rm_1endjmp_bblk(struct bblk_t *rm_bbp, struct flowg_t *fgp,
 struct mod_t *mdp)
{
 int32 rm_seqno;
 struct bbedge_t *bbep;
 struct bblk_t *jmpto_bbp, *jmpfr_bbp; 
 struct bbedge_t *new_bbep;

 /* can't remove after suspend bblks */
 /* DBG remove -- */
 if (rm_bbp->after_suspend) __misc_terr(__FILE__, __LINE__);
 /* -- */ 

 /* DBG remove --
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "back edge list for to be removed bblk %d\n",
    rm_bbp->bblk_seqno);
   __dmp_bblk_backelst(rm_bbp, fgp, mdp);
  }
 --- */

// SJM 12/01/06 - REMOVEME - what does this do? 
 if (rm_bbp->itail->opcod != I_BBLK_JMP) __misc_terr(__FILE__, __LINE__);

 jmpto_bbp = rm_bbp->itail->idst.apu.bbp;
 rm_seqno = rm_bbp->bblk_seqno;

 /* go through the to be removed bblk's back edges adjusting */
 /* the jmp insn destinations to the one bblk the to be removed jumps to */
 /* and adding a back edge to the jmp to bblk */
 for (bbep = rm_bbp->bbe_prev; bbep != NULL; bbep = bbep->bbenxt) 
  {
   jmpfr_bbp = bbep->eblkp;

   /* fix the bblk that jumped to the removed one to jump to the one */
   /* bblk the removed bblk jumped to */
   adjust_jmpfr_end_insn(jmpfr_bbp, jmpto_bbp, rm_seqno);

   /* if the jump from bblk has another path to the jump to bblk, */
   /* then nothing to do else add the back edge to the jump to bblk */
   if (!fnd_bbedge(jmpto_bbp, jmpfr_bbp)) 
    {
     new_bbep = (struct bbedge_t *) __my_malloc(sizeof(struct bbedge_t));
     new_bbep->eblkp = jmpfr_bbp;
     /* since this is back edge list, prev means head - link on front */
     new_bbep->bbenxt = jmpto_bbp->bbe_prev;
     jmpto_bbp->bbe_prev = new_bbep;
    }
  }
 /* AIV 12/08/06 - need to remove back edge from the rm to jmp block */
 rm_one_bbedge(rm_bbp, jmpto_bbp);
 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout,
    "flow graph updated and back edge list for jump to bblk %d removed\n",
    jmpto_bbp->bblk_seqno);
   __dmp_bblk_backelst(jmpto_bbp, fgp, mdp);
   chk_bblk_connectivity(fgp);
  }
 /* -- */
}

/*
 * find and remove a bblk's back edge from a jmp to bblk's back edge list
 *
 * SJM 04/15/06 - lookatme maybe need doubly linked list 
 */
static void rm_one_bbedge(struct bblk_t *jmpfr_bbp, struct bblk_t *jmpto_bbp) 
{
 struct bbedge_t *bbep;
 struct bbedge_t *last_bbep;

 last_bbep = NULL;
 for (bbep = jmpto_bbp->bbe_prev; bbep != NULL; bbep = bbep->bbenxt)
  {
   if (bbep->eblkp->bblk_seqno == jmpfr_bbp->bblk_seqno)
    {
     if (last_bbep == NULL) jmpto_bbp->bbe_prev = bbep->bbenxt;
     else last_bbep->bbenxt = bbep->bbenxt;
     __my_free(bbep, sizeof(struct bbedge_t));
     return;
    }
   last_bbep = bbep;
  }
 /* DBG remove -- */
 if (jmpto_bbp->bbe_prev != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
}

/*
 * return T if a basic block is in the back edge list of another bblk
 */
static int32 fnd_bbedge(struct bblk_t *jmpto_bbp, struct bblk_t *jmpfr_bbp) 
{
 int32 seqno;
 struct bbedge_t *bbep;

 seqno = jmpfr_bbp->bblk_seqno;
 for (bbep = jmpto_bbp->bbe_prev; bbep != NULL; bbep = bbep->bbenxt)
  {
   if (bbep->eblkp->bblk_seqno == seqno) return(TRUE);
  }
 return(FALSE);
}

/*
 * change the jump to location of a jmp from bblk (on the back edge list
 * of the to be remove bblk) to the new jump to (one bblk the rem jmped to)
 */
static void adjust_jmpfr_end_insn(struct bblk_t *jmpfr_bbp,
 struct bblk_t *jmpto_bbp, int32 rm_seqno)
{
 struct insn_t *ip, *cmp_ip;
 struct insn_info_t *iip;

 ip = jmpfr_bbp->itail; 
 /* update the tail insn of prev to point to successor of removed */
 /* know ip is jump insn - only one exit or two exit possible or index tab */
 if (ip->opcod == I_BBLK_JMP) ip->idst.apu.bbp = jmpto_bbp;
 else if (ip->opcod == I_COND_JMP || ip->opcod == I_REAL_COND_JMP)
  {
   if (ip->isrc.apu.bbp->bblk_seqno == rm_seqno) ip->isrc.apu.bbp = jmpto_bbp;
   else ip->idst.apu.bbp = jmpto_bbp;

   /* AIV 12/18/06 - rare case cond jump is made cond jump to same block */
   if (ip->isrc.apu.bbp == ip->idst.apu.bbp) 
    {
     /* SJM 01/21/07 - remove the cmp/test before converting to uncond jmp */
     cmp_ip = ip->iprev;
     /* DBG remove -- */
     if (cmp_ip == NULL) __misc_terr(__FILE__, __LINE__);
     iip = __to_iinfo_rec(cmp_ip->opcod);

     /* SJM 04/06/07 - the real cond jmp is different boiler plate sequence */
     /* must remove "I_FNSTSW; I_SAHF; I_REAL_COND_JMP" sequence */
     if (cmp_ip->opcod == I_SAHF)
      {
       /* DBG remove --- */
       if (cmp_ip->iprev->opcod != I_FNSTSW) __misc_terr(__FILE__, __LINE__);
       /* --- */
       __cur_bbp = jmpfr_bbp;
       __linkout_insn(cmp_ip->iprev, TRUE);
       __linkout_insn(cmp_ip, TRUE);
       __cur_bbp = NULL;
      }
     else
      {
       if (iip->iclass != ICLASS_CMP) __misc_terr(__FILE__, __LINE__);
       __cur_bbp = jmpfr_bbp;
       __linkout_insn(cmp_ip, TRUE);
       __cur_bbp = NULL;
      } 
     
     ip->opcod = I_BBLK_JMP;
     __init_amode(&(ip->isrc));
     ip->jmptyp = CC_NONE;
     ip->isrc.amode = AM_NONE;
    }
  }
 else if (ip->opcod == I_IND_JMP)
  {
   fix_rmbblk_ndxjmp_insn(jmpto_bbp, ip, rm_seqno);
  }
 else __case_terr(__FILE__, __LINE__);
}

/*
 * for index jump insn that is on back edge of removed bblk, change
 * to destination bbblk and rebuild the insn ndx jump table 
 *
 * now only called if there is a back edge from to be removed bblk
 *
 * removed bblk is jumped to from ndx jump 
 */
static void fix_rmbblk_ndxjmp_insn(struct bblk_t *new_bbp,
 struct insn_t *ndxjmp_ip, int32 rm_seqno)
{
 int32 tabi, chged;
 size_t jtabsiz, jtab2siz, osize, nsize;
 struct bblk_t **bbtab, **new_bbtab;
 struct ndxjmp_t *ndxjp;

 ndxjp = ndxjmp_ip->extrau.ndxjp;
 /* DBG remove -- */
 if (ndxjp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 jtabsiz = ndxjp->jtabstart;
 bbtab = ndxjp->bbtab;
 for (chged = FALSE, tabi = 0; tabi < jtabsiz; tabi++)
  {
   if (bbtab[tabi]->bblk_seqno == rm_seqno)
    {
     bbtab[tabi] = new_bbp;
     chged = TRUE;
    }
  }
 /* DBG remove -- */
 if (!chged) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* SJM 03/29/05 - adding 2nd area for unduped (set) of jmp to bblks */
 /* also fix up the unduplicated index jump to bblk tab section */
 /* SJM 06/07/05 - recalc set of unrepeated labels since label renum */
 jtab2siz = __count_ndxjmp_lab_setsiz(bbtab, jtabsiz);
 if (jtab2siz != ndxjp->jtabsiz)
  { 
   osize = (jtabsiz + ndxjp->jtabsiz)*sizeof(struct bblk_t *);
   nsize = (jtabsiz + jtab2siz)*sizeof(struct bblk_t *);
   new_bbtab = (struct bblk_t **) __my_realloc(bbtab, osize, nsize);
   ndxjp->bbtab = new_bbtab; 
   ndxjp->jtabsiz = jtab2siz;
  } 
 else new_bbtab = bbtab;

 /* know new bbtab linked into insn - now build the new unrepeated set */
 __bld_ndxjmp_lab_set(new_bbtab, jtabsiz);
}

/*
 * check internal connectivity of all basic blocks in a flow graph
 */
static void chk_bblk_connectivity(struct flowg_t *fgp)
{
 struct bblk_t *bbp, *bbp2;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (bbp2 = bbp->bbnxt; bbp2 != NULL; bbp2 = bbp2->bbnxt)
    {
     if (bbp->bbprev == NULL)
      {
       if (bbp->bbnxt == NULL)
        {
         if (fgp->fg_bblks != bbp || fgp->fg_bblkend != bbp) 
          __misc_terr(__FILE__, __LINE__);
        }
       else
        {
         if (fgp->fg_bblks != bbp) __misc_terr(__FILE__, __LINE__);
         if (fgp->fg_bblkend == bbp) __misc_terr(__FILE__, __LINE__);
         if (bbp->bbnxt->bbprev != bbp) __misc_terr(__FILE__, __LINE__);
        }
      }
     else
      {
       if (bbp->bbnxt == NULL)
        {
         if (fgp->fg_bblkend != bbp) __misc_terr(__FILE__, __LINE__);
         if (fgp->fg_bblks == bbp) __misc_terr(__FILE__, __LINE__);
         if (bbp->bbprev->bbnxt != bbp) __misc_terr(__FILE__, __LINE__);
        }
       else
        {
         if (fgp->fg_bblkend == bbp) __misc_terr(__FILE__, __LINE__);
         if (fgp->fg_bblks == bbp) __misc_terr(__FILE__, __LINE__);
         if (bbp->bbprev->bbnxt != bbp) __misc_terr(__FILE__, __LINE__);
         if (bbp->bbprev->bbnxt != bbp) __misc_terr(__FILE__, __LINE__);
         if (bbp->bbnxt->bbprev != bbp) __misc_terr(__FILE__, __LINE__);
        }
      }
     if (bbp->bblk_seqno == bbp2->bblk_seqno)
      __misc_terr(__FILE__, __LINE__);
    }
  }
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __chk_one_bblk_connectivity(bbp);
  }
}

/*
 * check internal connectivity of one basic block
 */
extern void __chk_one_bblk_connectivity(struct bblk_t *bbp)
{
 struct insn_t *ip;

 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
  {
   if (ip == ip->inxt) __misc_terr(__FILE__, __LINE__);
  }
}

/*
 * merge (remove) a block that is jumped to with unconditional jump
 * and no other bblk jumps to it
 * 
 * this combines 2 insn lists
 */
static void merge_uncond_1entry_bblks(struct flowg_t *fgp,
 struct mod_t *mdp)
{
 int32 chged, num_passes, num_removed;  
 struct bblk_t *bbp, *bbp2, *addto_bbp, *rm_bbp;
 struct insn_t *tail_ip;

 num_removed = 0;
 num_passes = 0;
 do {
  num_passes++; 
  chged = FALSE;
  for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp2)
   {
    bbp2 = bbp->bbnxt;

    /* can't remove after suspend */
    if (bbp->bbe_prev == NULL)
     {
      if (!bbp->after_suspend) __misc_terr(__FILE__, __LINE__);
      continue;
     }

    /* if more than one bblk jumps to it (>1 back edge), can't join */
    if (bbp->bbe_prev->bbenxt != NULL) continue;
     
    addto_bbp = bbp->bbe_prev->eblkp;
    tail_ip = addto_bbp->itail;
    /* AIV 12/08/06 - need to check because code can be created for empty */
    /* blocks - from S_STNONE - statements */
    /* DBG remove -- */
    if (tail_ip->opcod == I_COND_JMP)
     {
      if (tail_ip->isrc.apu.bbp == tail_ip->idst.apu.bbp)
       __misc_terr(__FILE__, __LINE__);
     }
    /* -------  */
    if (tail_ip->opcod != I_BBLK_JMP) continue;
  
    rm_bbp = bbp;
    /* add bbp (merge at end) to addto bbp */
    merge_bblks(fgp, addto_bbp, rm_bbp);  
    __free_1bblk(rm_bbp, fgp, TRUE);

    num_removed++;
    chged = TRUE;
   }
 } while (chged);
 if (__opt_debug_flg && num_removed > 0)
  {
   __my_fprintf(stdout,
    "== %d in %d passes of bblks merged into another bblk in module %s\n",
    num_removed, num_passes, mdp->msym->synam);
  }
}


/*
 * move the insn from rm bbp to end of addto_bbp list and remove bbp 
 */
static void merge_bblks(struct flowg_t *fgp, struct bblk_t *addto_bbp,
 struct bblk_t *rm_bbp)
{
 struct insn_t *rem_ip, *lab_ip, *jmp_ip;

 /* DBG remove -- */
 if (addto_bbp->ihd == addto_bbp->itail) __misc_terr(__FILE__, __LINE__);
 /* --- */ 
 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout,
    "&& merge insns from to be remove B%d - onto end of B%d\n",
    rm_bbp->bblk_seqno, addto_bbp->bblk_seqno);
  }
 /* --- */ 
 
 /* remove the addto bblk tail jump insn */
 rem_ip = addto_bbp->itail;
 rem_ip->iprev->inxt = NULL;
 addto_bbp->itail = rem_ip->iprev; 
 /* free the removed insn */
 __free_1insn(rem_ip);

 /* DBG --- */ 
 if (rm_bbp->ihd->opcod != I_BBLK_LABEL) __misc_terr(__FILE__, __LINE__);
 /* --- */ 
 /* first insn is label that does not get moved as part of merge in as tail */
 lab_ip = rm_bbp->ihd;
 rm_bbp->ihd = lab_ip->inxt;
 rm_bbp->ihd->iprev = NULL;
 __free_1insn(lab_ip);
 
 /* merge the insns from the rm bblk onto tail of the addto bblk */ 
 addto_bbp->itail->inxt = rm_bbp->ihd;

 rm_bbp->ihd->iprev = addto_bbp->itail;
 addto_bbp->itail = rm_bbp->itail; 

 /* SJM 12/17/07 if merge into and removed bblk jumps to merge into */
 /* bblk, this is a look that implies unreachable - must change */ 
 /* the jump here */
 /* SJM 12/17/07 - can't happen for index (case) jump, since looping */ 
 /* is out side the case */ 
 jmp_ip = addto_bbp->itail; 
 if (jmp_ip->opcod == I_BBLK_JMP)
  {
   /* if newly added bblk jumps back to itself - jump is bogus */
   if (jmp_ip->idst.apu.bbp == addto_bbp)
    {
     rm_one_bbedge(rm_bbp, addto_bbp);
     /* change to a complete since no longer a jump */ 
     __init_amode(&(jmp_ip->isrc));
     jmp_ip->isrc.amode = AM_NONE;
     __init_amode(&(jmp_ip->idst));
     jmp_ip->idst.amode = AM_NONE;
     jmp_ip->opcod = I_COMPLETE;
    }
  }
 else if (jmp_ip->opcod == I_COND_JMP || jmp_ip->opcod == I_REAL_COND_JMP)
  {
   if (jmp_ip->isrc.apu.bbp == addto_bbp)
    {
     jmp_ip->opcod = I_BBLK_JMP;
     __init_amode(&(jmp_ip->isrc));
     jmp_ip->isrc.amode = AM_NONE;
     rm_one_bbedge(rm_bbp, addto_bbp);
    }
   else if (jmp_ip->idst.apu.bbp == addto_bbp)
    {
     jmp_ip->opcod = I_BBLK_JMP;
     __copy_amode(&(jmp_ip->idst), &(jmp_ip->isrc));
     __init_amode(&(jmp_ip->isrc));
     jmp_ip->isrc.amode = AM_NONE;
     rm_one_bbedge(rm_bbp, addto_bbp);
    }
  }

 /* since insn moved, make sure not freed */
 rm_bbp->ihd = rm_bbp->itail = NULL;

 /* for all back edges in updated flow graph, substitute addto bbp */
 subst_backedges(fgp, rm_bbp, addto_bbp);
}

/*
 * substitute back edge eblks
 *
 * SJM 04/18/06 - FIXME - this should look at jump and just fix the 
 * jumped to (even with ndx) bblks back edge lists
 */
static void subst_backedges(struct flowg_t *fgp, struct bblk_t *rm_bbp,
 struct bblk_t *addto_bbp)
{
 struct bblk_t *bbp;
 struct bbedge_t *bbep;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   if (bbp == addto_bbp || bbp == rm_bbp) continue;

   for (bbep = bbp->bbe_prev; bbep != NULL; bbep = bbep->bbenxt)
    {
     if (bbep->eblkp == rm_bbp) bbep->eblkp = addto_bbp;
    }
  }
}

/*
 * ROUTINES TO IMPROVE FLOW GRAPHS AND SET REVERSE POST ORDER BBLK NUMBERS
 */

/*
 * determine flowg entry/ exit bblks and size and set reverse post order nums
 * needed because flow well formed flow graphs can only have one entry bblk
 * (in our case an implied virtual entr) and one exit bblk (again in our
 * case is a list of bblk so the actual exit bblk is virtual)
 *
 * this routine is another step in produces a systematic well formed
 * flowgraph for value tracking and register assignment
 */
static void set_rpos_and_ent_bblklst(struct flowg_t *fgp,
 struct mod_t *mdp)
{
 int32 num_bblks;
 struct bblk_t *bbp;
 struct bblklst_t *bblp;
 struct insn_t *start_ip;

 /* build the list of the flow graph's enter nodes (AFS/complete) */
 /* and exit nodes and count nodes */
 num_bblks = 0;
 __cur_bbp = __dum_fg_ent_bbp;
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   num_bblks++;

   /* DBG remove -- */
   if (__opt_debug_flg)
    {
     __chk_bblk_bedges(bbp, fgp, mdp);
    }
   /* --- */

   start_ip = bbp->ihd;
   /* SJM 09/11/06 - all bblks with after suspend bit on are also enter */
   if (bbp->after_suspend || __is_fg_enter_insn(start_ip->opcod))
    {
     bblp = alloc_bblklst();
     if (fgp->enter_bblks == NULL) fgp->enter_bblks = bblp; 
     else
      {
       fgp->enter_bblks->bl_prev = bblp;
       bblp->bl_nxt = fgp->enter_bblks;
       fgp->enter_bblks = bblp;
      }
     bblp->bl_bbp = bbp;
    }
  }
 fgp->fg_num_bblks = num_bblks + 1;

 /* since ordered using reverse post order, set bblk rev order num first */ 
 /* val num glb used as bblk number here */
 __rev_po_ndx = fgp->fg_num_bblks;
 __cur_mark++;
 /* SJM 08/08/06 - can't build the rev postorder blk tab until after here */ 
 for (bblp = fgp->enter_bblks; bblp != NULL; bblp = bblp->bl_nxt)  
  {
   set_bblk_rev_postorder_nums(bblp->bl_bbp, NULL);
  }
 /* DBG remove -- */
 if (__rev_po_ndx != 1) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* DBG remove -- 
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   if (bbp->revpostordno == -1) __misc_terr(__FILE__, __LINE__);
  }
 --- */
}

/*
 * alloc and initialize a bblk list element
 */
static struct bblklst_t *alloc_bblklst(void)
{
 struct bblklst_t *bblp;

 /* this bblk node is pre dominated */
 bblp = (struct bblklst_t *) __my_malloc(sizeof(struct bblklst_t));

 bblp->bl_bbp = NULL;
 bblp->bl_prev = NULL;
 bblp->bl_nxt = NULL;
 return(bblp);
}

/*
 * set reverse post order numbers
 */
static void set_bblk_rev_postorder_nums(struct bblk_t *cbbp, 
 struct bblk_t *case_bbp)
{
 int32 jti;
 struct insn_t *end_ip;
 struct ndxjmp_t *ndxjp;
 struct bblk_t *bbp, **bbtab;

 /* AIV 01/30/12 - if reached the next case jump item return */ 
 /* this routine has falling through to all case items - when it gets to */
 /* the next case item just return */
 if (cbbp != case_bbp)
  {
   if (cbbp->is_casejmp_item) return;
  }
 /* first mark that this node has been visited */
 cbbp->mark = __cur_mark;

 end_ip = cbbp->itail;
 if (end_ip->opcod == I_BBLK_JMP)
  {
   /* DBG remove -- */
   if (end_ip->isrc.amode != AM_NONE) __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* SJM 08/08/06 - nores insns with one opand amode in dst not src */ 
   bbp = end_ip->idst.apu.bbp;
   if (bbp->mark != __cur_mark) set_bblk_rev_postorder_nums(bbp, case_bbp);
  }
 else if (end_ip->opcod == I_COND_JMP || end_ip->opcod == I_REAL_COND_JMP)
  {
   /* AIV 02/03/09 - if xz block reverse order to make the non-xz block */
   /* the fallthru block */
   if (end_ip->idst.apu.bbp->is_xz)
    {
     bbp = end_ip->isrc.apu.bbp;
     if (bbp->mark != __cur_mark) set_bblk_rev_postorder_nums(bbp, case_bbp);
     bbp = end_ip->idst.apu.bbp;
     if (bbp->mark != __cur_mark) set_bblk_rev_postorder_nums(bbp, case_bbp);
    }
   else
    {
     bbp = end_ip->idst.apu.bbp;
     if (bbp->mark != __cur_mark) set_bblk_rev_postorder_nums(bbp, case_bbp);
     bbp = end_ip->isrc.apu.bbp;
     if (bbp->mark != __cur_mark) set_bblk_rev_postorder_nums(bbp, case_bbp);
    }
  }
 /* AIV 05/07/07 - should never get an index port jump */
 /* DBG remove -- */
 else if (end_ip->opcod == I_PORT_IND_JMP) __case_terr(__FILE__, __LINE__);
 /* ---- */
 else if (end_ip->opcod == I_IND_JMP)
  {
   ndxjp = end_ip->extrau.ndxjp;
   /* DBG remove -- */
   if (ndxjp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   bbtab = (struct bblk_t **) ndxjp->bbtab;
   /* AIV 05/08/07 - was starting at size when should be index */
   jti = ndxjp->jtabstart;
   for (; jti < (ndxjp->jtabstart + ndxjp->jtabsiz); jti++)
    {
     bbp = bbtab[jti]; 
     if (bbp->mark == __cur_mark) continue;
     /* AIV 01/30/12 - now pass the case item - to return when done */ 
     set_bblk_rev_postorder_nums(bbp, bbp);
    }
  }
 /* DBG remove -- */
 else  
  {
   if (end_ip->opcod != I_SUSPEND && end_ip->opcod != I_COMPLETE 
    && end_ip->opcod != I_TSKJMP && end_ip->opcod != I_TSKRET_JMP
    && end_ip->opcod != I_NEXT_EVENT && end_ip->opcod != I_NEXT_NCHG_EVENT)
    __case_terr(__FILE__, __LINE__);
  }
 /* --- */

 /* gets here either from flowg exit (suspend/complete) or return from */
 /* depth first routine finish */
 cbbp->revpostordno = --__rev_po_ndx;
 /* DBG remove -- */
 if (__opt_debug_flg)
  { 
   __my_fprintf(stdout, "set rpo number for B%d = %d\n",
    cbbp->bblk_seqno, __rev_po_ndx);
  }
 /* --- */
}

/*
 * for traversing bblks now always build the reverse post order list
 *
 * think always faster to traverse a flow graph's bblks in rev post order
 * routine also used to rebuild the rpo table after reassigning rpos
 */
extern void __fill_fg_po_bblktab(struct flowg_t *fgp)
{
 int32 blki;
 struct bblk_t *bbp;
 size_t osize, nsize;

 /* AIV 06/17/09 - changed these to use size_t */
 if (fgp->fg_num_bblks >= __bblktabsiz)
  {
   osize = __bblktabsiz*sizeof(struct bblk_t *);
   nsize = fgp->fg_num_bblks*sizeof(struct bblk_t *);
   __bblktab = (struct bblk_t **) __my_realloc(__bblktab, osize, nsize);
   /* AIV 06/17/09 - need to set new value here - leaking memory */
   __bblktabsiz = fgp->fg_num_bblks;
  }
 for (blki = 1; blki < fgp->fg_num_bblks; blki++) __bblktab[blki] = NULL;
 __bblktab[0] = __dum_fg_ent_bbp;
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   /* AIV 12/11/06 - revpostorder should never be -1 */
   /* DBG remove -- */
   if (bbp->revpostordno == -1 || bbp->revpostordno > fgp->fg_num_bblks)
    {
     __misc_terr(__FILE__, __LINE__);
    } 
   /* ---- */
   __bblktab[bbp->revpostordno] = bbp;
  }
}

/*
 * routine to dump a flow graph's bblk tab reverse post order index
 *
 * don't need to have cur bbp set here
 */
static void dmp_1fg_rev_po_bblktab(int32 numblks)
{
 int32 blki;
 struct bblk_t *bbp;

 __my_fprintf(stdout,
  "### DUMPING FLOW GRAPH BBLKS IN REVERSE POST ORDER ###\n"); 
 for (blki = 0; blki < numblks; blki++)
  {
   bbp = __bblktab[blki];

   if (bbp == NULL)
    {
     __my_fprintf(stdout, "+++ bblk with RPO number %d removed\n", blki);
     continue;
    }

   /* DBG remove --
   if (bbp->revpostordno != blki) __misc_terr(__FILE__, __LINE__);
   --- */
   __my_fprintf(stdout, "bblk B%0d (rpo num = %0d)\n", bbp->bblk_seqno,
    bbp->revpostordno);
  }
 __my_fprintf(stdout, "### END FLOW GRAPH DUMP ###\n");
}

#ifdef __VALTRK__
/*
 * ROUTINES TO BUILD FUDS AND DATA STRUCTURES AND SIMPLIFY FROM TRACKING
 */

/*
 * build fud d.s. and track and simplify basic blocks if can
 */
static void bld_fuds_and_simplify_1fg(struct mod_t *mdp, struct flowg_t *fgp)
{
 int32 fg_chged, pass_no;

 fg_chged = TRUE;
 pass_no = 0;
 while (fg_chged)
  {
   pass_no++;
   /* DBG remove -- */
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout,
       "BEFORE tracking insn/block optimization - pass %d\n", pass_no);
     __dmp_flowg_insns(fgp, mdp);
    }
   /* --- */

   /* routine to build predoms, sets and fuds after flow bblk structure chg */ 
   bld_1fg_doms_sets_fuds(fgp);

   /* next step needs the full FUD form of SSA lists and sets (avl trees) */
   /* to trk variable values to remove insns and simplify bblk structure */
   /* calls a high level sequencer since only basic tracking for now */
   fg_chged = sequencer_1fg_track_optimize(fgp, mdp);

   /* flowg completely reformed and done withy old one so free all including */
   /* free all predom and fud data structures since now wrong */ 
   __free_flowg_doms_and_sets(fgp);
  }
}

/*
 * build all the sets and structural connectivity d.s. needed for factored 
 * use-def changes and insert deflst insns
 *
 * in the literature, def list insns are called phi operators
 */
static void bld_1fg_doms_sets_fuds(struct flowg_t *fgp)
{
 bld_predominators(fgp);

 /* now done with purely bblk simplification and data struct building */
 /* bld some needed tn use and def sets (avl trees) */
 bld_tn_sets(fgp);

 /* build various tn sets and factored use-def (FUD) chain form of SSA */
 /* the sets and FUD chains and their deflst insns also used later in */ 
 /* register allocation */
 bld_insert_fud_chains(fgp);
}

/*
 * ROUTINES TO BUILD PREDOM AND PREDOM FRONTIER SETS
 * OPERATION IS PURELY STRUCTURAL ON BBLKS SO NO NEED FOR USE-DEF/SSA SETS YET
 */


/*
 * routine to build the various predominator data structures
 *
 * first build the flow graph's predom tree (bblk b is predominated by
 * predoms(b) - path goes to root entry node, then build the predomintor
 * frontier lists (node predominated by a predecessor) and finally
 * build the list for each bblk of the nodes it predominates that is
 * needed by the factored use-def (FUD) linking algorithm
 */
static void bld_predominators(struct flowg_t *fgp)
{
 /* build bblk predominate tree and predom frontier lists for later use */
 bld_predom_tree(fgp);

 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   dmp_1fg_predom_trees(fgp);
  }
 /* -- */
 bld_bblk_predom_frontier(fgp);
 /* DBG remove -- */ 
 if (__opt_debug_flg) 
  {
   dmp_predom_frontier_lists(fgp);
  }
 /* -- */

 bld_bblk_predom_of_lists(fgp);
}

/*
 * compute the doms array that stores the predominator tree
 *
 * predom routines are structural that just process bblks in a flowg
 */
static void bld_predom_tree(struct flowg_t *fgp)
{
 int32 di, blki;
 int32 chged, cb_num, idom1, idom2, *idoms;
 struct bblk_t *bbp;
 struct bbedge_t *bbep;
 struct bblklst_t *bblp;

 fgp->predoms = (int32 *) __my_malloc(sizeof(int32)*fgp->fg_num_bblks);
 idoms = fgp->predoms;
 for (di = 0; di < fgp->fg_num_bblks; di++) idoms[di] = -1;
 
 /* SJM 12/19/06 - AFS bblks have their final predom value set here */ 
 /* the parent is always the virtual dummy entry bblk with seq number -2 */
 /* -- needed because we are not inserting the actual back edges */
 /* the predom algorithm relaxes so once correct parent is set */
 /* it works right with rest of algorithm and never changes */
 for (bblp = fgp->enter_bblks; bblp != NULL; bblp = bblp->bl_nxt)  
  {
   cb_num = bblp->bl_bbp->revpostordno; 
   idoms[cb_num] = 0;
  }

 chged = TRUE;
 while (chged) { 
  chged = FALSE; 
  for (blki = 1; blki < fgp->fg_num_bblks; blki++)
   {
    bbp = __bblktab[blki];
    /* SJM 12/15/06 - must insure that no nodes have been removed here */
    /* DBG remove -- */
    if (bbp == NULL) __misc_terr(__FILE__, __LINE__);
    /* --- */

    cb_num = bbp->revpostordno; 
    bbep = bbp->bbe_prev;
    /* this is after suspend node */
    if (bbep == NULL)
     {
      /* first time AFS bblks are -1 from then on only 0 possible */
      /* DBG remove -- */
      if (!bbp->after_suspend) __misc_terr(__FILE__, __LINE__);
      if (idoms[cb_num] != 0) __misc_terr(__FILE__, __LINE__);
      /* --- */
      continue;
     }
    idom2 = bbep->eblkp->revpostordno;
    for (bbep = bbep->bbenxt; bbep != NULL; bbep = bbep->bbenxt)
     {
      idom1 = bbep->eblkp->revpostordno;
      if (idoms[idom1] != -1)
       {
        idom2 = predom_intersect(idoms, idom1, idom2);
       }
     }
    if (idoms[cb_num] != idom2)
     {
      idoms[cb_num] = idom2;
      chged = TRUE;
     }
//REMOVEME
    /* DBG remove -- 
    if (__opt_debug_flg) dmp_doms(idoms, fgp->fg_num_bblks);
    --- */
   }
  /* DBG remove -- */
  if (__opt_debug_flg) dmp_doms(idoms, fgp->fg_num_bblks);
  /* --- */
 } 
}

/*
 * routine to intersect two revers port order tree (as array) stored pre
 * dominator sets
 *
 * this works backwards until first common ancestors is found
 * know idom1 on entry is never -1 or won't be called
 *
 * SJM 12/19/06 - algorithm modified from "A simple, Fast Dominance
 * Algorithm" by Cooper, K et. al. - our flow graphs entry node reverse
 * post order number is smallest - the Cooper algorithms assumes largest
 * so that when an undefined doms location is set the loop stops - we
 * need to check for the -1
 *
 * idea is that idoms stores the tree in an array so that
 * idoms[RPO number 5] is the predominator parent in the dominator
 * tree of 5
 */
static int32 predom_intersect(int32 *doms, int32 idom1, int32 idom2)
{
 while (idom1 != idom2) 
  {
   /* work backward as long as chain of idom1 predecessors RPO num below */ 
   while (idom1 > idom2) 
    {
     idom1 = doms[idom1];
     /* DBG remove -- */
     if (idom1 == -1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     if (idom1 == 0) return(idom1);
    }
   /* if hit common predecessor (ancestor), done */
   if (idom1 == idom2) break;
   /* work backward as long as chain of idom2 predecessors RPO num below */ 
   while (idom2 > idom1)
    {
     idom2 = doms[idom2];
     if (idom2 == -1) return(idom1);
    }
  }
 /* know idom1 and idom2 same here */
 return(idom1);
}

/*
 * dump the doms array - work immediate pre dominator array as tree
 */
static void dmp_doms(int32 *idoms, int32 num_bblks)
{
 int32 di, idom_rpo, idom_seqno;

 __my_fprintf(stdout, "+++ DUMPING idoms:\n");
 for (di = 1; di < num_bblks; di++)
  {
   if (idoms[di] == -1) idom_rpo = idom_seqno = -1;
   else
    {
     idom_rpo = idoms[di];
     idom_seqno = __bblktab[idom_rpo]->bblk_seqno;
    }
   __my_fprintf(stdout, "idoms[SEQ=%d - RPO=%d] = SEQ=%d (RPO=%d)\n", 
    __bblktab[di]->bblk_seqno, di, idom_seqno, idom_rpo);
  }
}

/*
 * dump a on-all-paths (pre-dom) tree 
 */
static void dmp_1fg_predom_trees(struct flowg_t *fgp)
{
 int32 blki, imdom_rpo, rpo_num, *idoms;
 struct bblk_t *bbp, *bbp2;

 idoms = fgp->predoms;
 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];

   /* SJM 12/02/06 - bblk may already have been removed */  
   if (bbp == NULL)
    {
     __my_fprintf(stdout, "+++ bblk with RPO number %d removed\n", blki);
     continue;
    }
   rpo_num = bbp->revpostordno;

   __my_fprintf(stdout,
    "=== predominator path to root for node B%0d (rpo num = %0d):\n",
    bbp->bblk_seqno, rpo_num);
  
   imdom_rpo = idoms[rpo_num];
   for (;;)
    {
     bbp2 = __bblktab[imdom_rpo]; 
     __my_fprintf(stdout, "    predom B%0d (rpo num = %0d):\n",
       bbp2->bblk_seqno, bbp2->revpostordno);
     if (imdom_rpo == -1) break;
     if (imdom_rpo == bbp2->revpostordno) break;

     imdom_rpo = idoms[imdom_rpo];
    }
   __my_fprintf(stdout, "===\n");
  }
}

/*
 * dump a list of basic blocks in reverse post order
 */
static void bld_bblk_predom_frontier(struct flowg_t *fgp)
{
 int32 blki, *doms, runner, was_added;
 struct bblk_t *bbp, *pred_bbp;
 struct bbedge_t *bbep;
 char s1[RECLEN];
 
 doms = fgp->predoms;
 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki]; 
   /* only look at join nodes (>= 2 back edges) */
   if (bbp->bbe_prev == NULL || bbp->bbe_prev->bbenxt == NULL)
    continue;
  
   for (bbep = bbp->bbe_prev; bbep != NULL; bbep = bbep->bbenxt)
    {
     pred_bbp = bbep->eblkp;
     runner = pred_bbp->revpostordno;
     while (runner != doms[bbp->revpostordno])
      {
       was_added = add_bblst_linear_set(__bblktab[runner], bbp);
       /* DBG remove -- */
       if (__opt_debug_flg)
        {
         if (was_added) strcpy(s1, "added to"); else strcpy(s1, "already in");
         __my_fprintf(stdout,
          "+++ B%d (RPO=%d) %s predom frontier for B%d (RPO=%d)\n",
          bbp->bblk_seqno, bbp->revpostordno, s1,
          __bblktab[runner]->bblk_seqno, runner);
         /* --- */
        }
       runner = doms[runner];
       /* SJM 12/17/06 - a node is not in its own predominator frontier */
       if (runner == bbp->revpostordno) break; 

       /* DBG remove -- */
       if (__opt_debug_flg)
        {
         __my_fprintf(stdout, "** new runner B%d (RPO=%d)\n",
          __bblktab[runner]->bblk_seqno, runner);
        }
       /* -- */
      }
    }
  }
}

/*
 * add to the pre-dominator frontier set stored as a linear list for now   
 */
static int32 add_bblst_linear_set(struct bblk_t *runner_bbp,
 struct bblk_t *bbp)
{
 struct bblklst_t *bblp, *new_bblp;

 if (runner_bbp->predom_frontiers == NULL)
  {
   new_bblp = alloc_bblklst();
   runner_bbp->predom_frontiers = new_bblp;
   new_bblp->bl_bbp = bbp;
   return(TRUE);
  }
 for (bblp = runner_bbp->predom_frontiers; bblp != NULL; bblp = bblp->bl_nxt)
  {
   if (bblp->bl_bbp->revpostordno == bbp->revpostordno)
    return(FALSE); 
  }
 new_bblp = alloc_bblklst();
 new_bblp->bl_bbp = bbp;
 /* put new on front */
 runner_bbp->predom_frontiers->bl_prev = new_bblp;
 new_bblp->bl_nxt = runner_bbp->predom_frontiers;
 runner_bbp->predom_frontiers = new_bblp;
 return(TRUE);
}

/*
 * routine to dump the predominator frontier list for a node
 */
static void dmp_predom_frontier_lists(struct flowg_t *fgp)
{
 int32 blki;
 struct bblk_t *bbp;
 struct bblklst_t *bblp;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki]; 

   __my_fprintf(stdout, "=== node B%d (RPO=%d) predominator frontier list: ",
    bbp->bblk_seqno, bbp->revpostordno);

   bblp = bbp->predom_frontiers;
   if (bblp == NULL) 
    {
     __my_fprintf(stdout, "EMPTY\n");
     continue;
    }
   for (; bblp != NULL; bblp = bblp->bl_nxt) 
    {
     __my_fprintf(stdout, "B%0d (RPO=%d) ", bblp->bl_bbp->bblk_seqno,
      bblp->bl_bbp->revpostordno);
    }
   __my_fprintf(stdout, "\n");
  }
}

/*
 * build the per bblk lists of bblks predominated by the bblk
 */
static void bld_bblk_predom_of_lists(struct flowg_t *fgp)
{
 int32 rpo_i, *idoms;
 struct bblk_t *dominee_bbp, *dom_bbp;
 struct bblklst_t *new_bblp;

 idoms = fgp->predoms;
 /* the pseudo 0th position predoms entry does not need list */
 for (rpo_i = fgp->fg_num_bblks - 1; rpo_i > 0; rpo_i--)
  {
   dominee_bbp = __bblktab[rpo_i];
   dom_bbp = __bblktab[idoms[rpo_i]];
   
   /* SJM 06/15/07 - dummy fg enter bblk has no predom by list */
   if (dom_bbp->bblk_seqno == -2) continue;

   new_bblp = alloc_bblklst();
   new_bblp->bl_bbp = dominee_bbp;

   if (dom_bbp->bblk_pdoms == NULL) dom_bbp->bblk_pdoms = new_bblp;
   else
    {
     new_bblp->bl_nxt = dom_bbp->bblk_pdoms;
     dom_bbp->bblk_pdoms = new_bblp;
    }
  }
}

/*
 * ROUTINES TO BUILD TN SETS USED BY LATER OPTIMIZATIONS
 */

/*
 * build tn sets needed for later optimization
 *
 * for now build the set (avl tree) of tn's used in the flow graph
 * and the set (avl tree) for each tn of the bblks it is used in
 * (either referenced or assigned to)
 *
 * for per fg, tn used in flowg set, includes children here and also res tn's
 * since at this point minsns still are <op1>,<op2> => <result> format
 */
static void bld_tn_sets(struct flowg_t *fgp)
{
 struct bblk_t *bbp;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   bld_tn_used_in_fg_set(fgp, bbp);
   bld_bblk_defuse_in_tn_sets(bbp);
  }
 /* DBG remove --
 if (__opt_debug_flg)
  {
   dmp_fg_tn_info(fgp);
  }
 --- */
}

/*
 * routine to go through the insns in a bblk and build the per flow graph
 * tn used in flow graph avl tree (set)
 */
static void bld_tn_used_in_fg_set(struct flowg_t *fgp, struct bblk_t *bbp)
{
 int32 ai, tni;
 struct insn_t *ip;
 struct asl_def_t *aslap;

 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
  {
   /* need to handle ASL calls as a special case */
   if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
    {
     for (ai = 0; ai < ip->callasl_argnum; ai++)
      {
       aslap = &(ip->extrau.asl_ausedefs[ai]);
       tni = aslap->am_arg.am_tni;
       /* DBG remove -- */
       if (tni == -1) __misc_terr(__FILE__, __LINE__);
       /* --- */
       tryadd_var_tn_in_fg(fgp, tni);
      }
     continue;
    }
   tni = xget_tnreg(&(ip->isrc));
   if (tni != -1) tryadd_var_tn_in_fg(fgp, tni);
 
   tni = xget_tnreg(&(ip->idst));
   /* if amode not a tn reg, tni will be -1 so works */
   if (tni != -1) tryadd_var_tn_in_fg(fgp, tni);

   /* notice result tn's never machine regs */
   if (ip->res_tni != -1) tryadd_var_tn_in_fg(fgp, ip->res_tni);
  }
}

/*
 * add one tn to set of used in flowg for constant tracking
 *
 * at this point no decomposition so everything used wide
 */
static void tryadd_var_tn_in_fg(struct flowg_t *fgp, int32 tni)
{
//AIV? - should not see parent here
/* === */
 int32 par_tni;
/* === */

 if (tn_valtrk_invisible(tni)) return;

 par_tni = __get2_par_tni(tni);
 __tryadd_tn_use_in_fg(fgp, par_tni);
}

/*
 * routine to eliminate tn's that are comlab's and therefore invisible
 * for value tracking
 */
static int32 tn_valtrk_invisible(int32 tni)
{
 struct tn_t *tnp;

 tnp = &(__tntab[tni]);

 /* SJM 04/27/07 - tn's that are the result of an operation such as addl */   
 /* or a mov from a net addr becomes a static addr that is invisible */
 /* because it can never be assigned to (killed) */
 /* AIV 01/17/09 - removed static adr flag - see older version if needed */
 /* if (tnp->is_static_adr) return(TRUE); */

 /* SJM 04/05/07 - can't track array's or svecs since offset assigns are */
 /* not killing assigns */
 if (tnp->srtyp != SR_VEC && tnp->srtyp != SR_CINT && tnp->srtyp != SR_SCAL
  && tnp->srtyp != SR_SSCAL & tnp->srtyp != SR_SCAL2S 
  && tnp->srtyp != SR_BIT2S) 
   {
    return(TRUE);
   }

 /* SJM 07-26-07 - if part of a new netadr sequence must not track */
 /* also nlo offsets in netadrs for now - maybe other later */
 if (tnp->idp_typ == COMLAB_NETADR) return(TRUE);

 switch (tnp->comlab_typ) {
  case COMLAB_NONE: break;
  case COMLAB_CONADR:
   if (!tnp->conadr_is_is) break;
   return(TRUE);
  case COMLAB_DCESCH_TEVS: 
  case COMLAB_IDP: 
  case COMLAB_IDPDAT:
   break;
  case COMLAB_STMT: case COMLAB_XPR: case COMLAB_GREF: case COMLAB_GATE:
  case COMLAB_NETADR: case COMLAB_CA: case COMLAB_NPPADR: case COMLAB_DCEADR:
  case COMLAB_L_UDPADR: case COMLAB_E_UDPADR: 
  case COMLAB_TCHK: case COMLAB_DEL:
   return(TRUE);
  /* cint is seen when tracking constant values so do not need in per fg */
  case COMLAB_CINT:
   return(TRUE);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}

/*
 * access a tn index (after reg assign uses the tni of the machine reg)
 */
static int32 xget_tnreg(struct amode_t *amp)
{
 int32 tni;

 if (__need_reg_tns)
  {
   if (amp->x86_regno != REG_NONE) tni = amp->x86_regno; 
   else tni = amp->am_tni;
  }
 else tni = amp->am_tni;
 return(tni);
}

/*
 * get an insn's destination tni (leave child if dest is child)
 *
 * can only use before conversion from 3 op risc insns to 2 op x86 insns
 * BEWARE - not for asl wrappers
 */
static int32 xget_insn_res_tni(struct insn_t *ip) 
{
 int32 tni;
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(ip->opcod);
 if (iip->iclass == ICLASS_STORE || ip->opcod == I_DEFLST)
  {
   tni = xget_tnreg(&(ip->idst));
  }
 else tni = ip->res_tni; 
 return(tni);
}

/*
 * buiild the set of bblks defined in and referenced for each tn 
 *
 * terminology is factored use-def lists - where use is a reference that
 * does not change value and define (killing) of the value
 */
static void bld_bblk_defuse_in_tn_sets(struct bblk_t *bbp)
{
 int32 ai, tni, asltyp;
 struct insn_t *ip;
 struct insn_info_t *iip;
 struct asl_info_t *aslp;
 struct asl_def_t *aslap;

 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
  {
   /* need to handle ASL calls as a special case */
   if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
    {
     for (ai = 0; ai < ip->callasl_argnum; ai++)
      {
       aslap = &(ip->extrau.asl_ausedefs[ai]);
       tni = aslap->am_arg.am_tni;
       /* DBG remove -- */
       if (tni == -1) __misc_terr(__FILE__, __LINE__);
       /* --- */

       /* SJM 12/28/06 - should return value in eax be a define here? */
       aslp = __to_aslinfo_rec(ip->idst.disp);
       asltyp = aslp->asl_op_typ[ip->callasl_argnum - ai - 1];

       /* only write ptr or read/write ptr are a defines */
       if (asltyp == A_WPTR || asltyp == A_RWPTR)
        {
         tryadd_bblk_defines_tn(tni, bbp); 
        }
       /* others are references - except ignore numbers (consts) */
       else tryadd_bblk_uses_tn(tni, bbp); 
      }
     continue;
    }
   iip = __to_iinfo_rec(ip->opcod);
   /* only copy and store have results in dst amode instead of res tni */ 
   /* copy has class store */
   if (iip->iclass == ICLASS_STORE)
    {
     tni = xget_tnreg(&(ip->isrc));
     if (tni != -1) tryadd_bblk_uses_tn(tni, bbp);

     tni = xget_tnreg(&(ip->idst));
     /* DBG remove -- */
     if (tni == -1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* if amode not a tn reg, tni will be -1 so works */
     tryadd_bblk_defines_tn(tni, bbp); 
    }
   else 
    {
     tni = xget_tnreg(&(ip->isrc));
     if (tni != -1) tryadd_bblk_uses_tn(tni, bbp);
     tni = xget_tnreg(&(ip->idst));
     if (tni != -1) tryadd_bblk_uses_tn(tni, bbp);

     /* any other insn - misc insns have -1 tn indices */
     tni = ip->res_tni;
     if (tni != -1) tryadd_bblk_defines_tn(tni, bbp); 
    }
  }
}

/*
 * add to avl tree (set) linked on each tn of the bblks in which tn defined
 *
 * for building and filling deflist insns at start of bblks
 * simple tree with no extra info needed in tree
 */
static void tryadd_bblk_defines_tn(int32 tni, struct bblk_t *bbp) 
{
 struct tn_t *tnp;

 if (tn_valtrk_invisible(tni)) return;

 tnp = &(__tntab[tni]);
 if (tnp->bb_def_tree == NULL) tnp->bb_def_tree = __allocinit_avlhd();

 /* if allocated since avlhd value is just a ptr, will be set here if new */
 __find_add_dup_bblk(tnp->bb_def_tree, bbp);
}

/*
 * add to avl tree (set) linked on each tn of the bblks in which tn used
 *
 * for building and filling deflist insns at start of bblks
 * simple tree with no extra info needed in tree
 */
static void tryadd_bblk_uses_tn(int32 tni, struct bblk_t *bbp) 
{
 struct tn_t *tnp;

 if (tn_valtrk_invisible(tni)) return;

 tnp = &(__tntab[tni]);
 if (tnp->bb_use_tree == NULL) tnp->bb_use_tree = __allocinit_avlhd();
 /* if allocated since avlhd value is just a ptr, will be set here if new */
 __find_add_dup_bblk(tnp->bb_use_tree, bbp);
}

/*
 * dump each tmp stored in one flow graphs tn use and/or def list
 *
 * know linearized avl tree of the set of tn's used in flow graph usable
 */   
static void dmp_fg_tn_info(struct flowg_t* fgp)
{
 int32 avli, avli2, tni, num_tnrefs, num_bblks;
 struct tn_t *tnp;
 struct bblk_t *bbp;
 struct tn_dup_t *tndup;
 struct avlnode_t **tn_ref_avltab, **bblk_usedef_avltab;
 char s1[RECLEN], s2[RECLEN];

 /* since only a dump routine this routine not too slow */
 tn_ref_avltab = __linearize_avl_tree(fgp->fg_tn_ref_tree, &(num_tnrefs));

 __my_fprintf(stdout, "DUMPING TMP STORED INFO FOR ONE FLOWG %d\n",
  fgp->fg_seqno);
 for (avli = 0; avli < num_tnrefs; avli++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[avli]->valp;
   tni = tndup->tni; 
   tnp = &(__tntab[tni]); 
   __tn_tostr(s1, tnp, FALSE);
   if (tni <= HIGH_MACH_REG) sprintf(s2, "%s", __regs[tni]);
   else sprintf(s2, "r%d", tni);
    
   __my_fprintf(stdout, "TN: %s %s\n", s2, s1);
   /* also dump the bblk's this tn is defined in tree */

   bblk_usedef_avltab = __linearize_avl_tree(tnp->bb_def_tree, &(num_bblks));
   for (avli2 = 0; avli2 < num_bblks; avli2++)
    {
     bbp = (struct bblk_t *) bblk_usedef_avltab[avli2]->valp;
     __my_fprintf(stdout, "\tdefined in B%d\n", bbp->bblk_seqno);
    }
   __my_free(bblk_usedef_avltab, num_bblks*sizeof(struct avlnode_t *));

   /* also dump the bblk's this tn is used in tree */
   bblk_usedef_avltab = __linearize_avl_tree(tnp->bb_use_tree, &(num_bblks));
   for (avli2 = 0; avli2 < num_bblks; avli2++)
    {
     bbp = (struct bblk_t *) bblk_usedef_avltab[avli2]->valp;
     __my_fprintf(stdout, "\tused in B%d\n", bbp->bblk_seqno);
    }
   __my_free(bblk_usedef_avltab, num_bblks*sizeof(struct avlnode_t *));
   __my_fprintf(stdout, "\n");
  }
 __my_free(tn_ref_avltab, num_tnrefs*sizeof(struct avlnode_t *));
}

/*
 * ROUTINES TO BUILD FACTORED USE-DEF CHAINS (FUD SSA FORM)
 */

/*
 * insert and connect FUD form SSA use-def chains
 */
static void bld_insert_fud_chains(struct flowg_t *fgp)
{
 int32 num_tnrefs;
 struct avlnode_t **tn_ref_avltab;
 
 /* need the linear array of tn used in flow graph array for FUD processing */
 tn_ref_avltab = __linearize_avl_tree(fgp->fg_tn_ref_tree, &(num_tnrefs));

 /* insert the deflst (phi) insns */
 insert_fg_deflsts(fgp, tn_ref_avltab, num_tnrefs);
 lnk_deflst_live_defs(fgp, tn_ref_avltab, num_tnrefs);
}

/*
 * ROUTINES TO USE VARIOUS SETS TO INSERT AND CONNECT FUD (SSA) PHI INSNS
 */

/*
 * insert deflst (phi) insns for needed control flow join bblks in a flowg
 * joins are the dominance frontier nodes along def to use paths
 */
static void insert_fg_deflsts(struct flowg_t *fgp,
 struct avlnode_t **tn_ref_avltab, int32 num_tnrefs)
{
 int32 avli, avli2, num_bblkdefs;
 struct bblk_t *bbp;
 struct tn_t *tnp;
 struct avlnode_t **bblk_def_avltab;
 struct tn_dup_t *tndup;
 struct bblk_t *deflst_bbp;
 struct bblklst_t *bblp;

 /* first mark each bblk in flowg un processed and not added */
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt) 
  { 
   bbp->deflst_processed = FALSE;
   bbp->deflst_added = FALSE; 
  }

 /* SJM 03/26/07 - need to reset the tn must stay bits since each time */ 
 /* through here deflst insns change */
 for (avli = 0; avli < num_tnrefs; avli++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[avli]->valp;
   __tntab[tndup->tni].res_tn_useistays = FALSE;
  }

 /* for every parent sym referenced at all in a flow graph, insert its list */
 /* of live defines (deflst insn) */
 /* SJM 01/13/07 - new scheme only see parent tnis - always mapped */
 for (avli = 0; avli < num_tnrefs; avli++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[avli]->valp;
   tnp = &(__tntab[tndup->tni]);
   bblk_def_avltab = __linearize_avl_tree(tnp->bb_def_tree, &(num_bblkdefs));

   /* for every bblk that defines the tn, try to add a deflst insn */ 
   for (avli2 = 0; avli2 < num_bblkdefs; avli2++)
    {
     deflst_bbp = (struct bblk_t *) bblk_def_avltab[avli2]->valp;
     deflst_bbp->deflst_processed = TRUE;
     try_insert_deflst_dom_fronts(tndup->tni, deflst_bbp);
    }
   /* finally, try to insert deflst insns in chain of predom frontier bblks */
   for (;;)
    { 
     bblp = __cur_dom_fron_todos;
     if (bblp == NULL) break;
     __cur_dom_fron_todos = __cur_dom_fron_todos->bl_nxt;
     if (__cur_dom_fron_todos == NULL) __cur_dom_fron_tail = NULL;

     deflst_bbp = bblp->bl_bbp;
     deflst_bbp->deflst_processed = TRUE;
     try_insert_deflst_dom_fronts(tndup->tni, deflst_bbp);

     /* finally free this bblk list element - it is linked out */
     __my_free(bblp, sizeof(struct bblklst_t));
    }
  } 
}

/*
 * try to insert a deflst insn (phi operator) for tn tni in bblk deflst bbp
 *
 * if already inserted will not get here - then add this predom frontier
 * bblk to the tail of the unprocessed list
 *
 * SJM 12/30/06 - question? - when a DEFLST insn is inserted should current
 * deflst inserted into bblk be added to tn's define set - think not?
 */
static void try_insert_deflst_dom_fronts(int32 tni, struct bblk_t *deflst_bbp)
{
 int32 wi, wlen;
 struct bblk_t *domfron_bbp;
 struct bblklst_t *domfron_bblp, *new_bblp, *bblp;
 struct insn_t *lab_ip;

 /* only possible candidates for add deflst insns are dom frontier bblks */ 
 domfron_bblp = deflst_bbp->predom_frontiers;
 for (; domfron_bblp != NULL; domfron_bblp = domfron_bblp->bl_nxt)
  {
   domfron_bbp = domfron_bblp->bl_bbp;
   /* DBG remove -- */
   if (domfron_bbp->after_suspend) __misc_terr(__FILE__, __LINE__);

   /* if tn not used in bblk (not used but can be defined) no deflist insn */
   if (__get_avlnode(domfron_bbp, __tntab[tni].bb_use_tree) == NULL)
    {
     /* SJM 05/01/07 - still need the deflst insn if tni is used in */
     /* any bblk that is predominated by the frontier bblk (node) */
     for (bblp = domfron_bbp->bblk_pdoms; bblp != NULL; bblp = bblp->bl_nxt)
      {
       if (__get_avlnode(bblp->bl_bbp, __tntab[tni].bb_use_tree) != NULL)
        goto need_deflst;
      }

     /* in any node predominated by domfron_bbp */
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "** No deflst insn for r%d - not used in B%d or bblk it predominates\n",
        tni, domfron_bbp->bblk_seqno); 
      }
     /* -- */
     continue;
    }

need_deflst:
   //SJM not resetting between tn's - if (domfron_bbp->deflst_added) continue;
   /* SJM 02/20/07 - every tn in deflst defined ip list will try to */ 
   /* insert a deflst insn - so only insert one */
   if (has_deflst_insn(domfron_bbp, tni)) continue;

   lab_ip = domfron_bbp->ihd;
   /* DBG remove -- */
   if (lab_ip->opcod != I_BBLK_LABEL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* SJM 02/20/07 - insert insn need to have cur_bbp set */
   __cur_bbp = domfron_bbp;
    
   /* SJM 03/17/07 - since do not know what is really referenced after here, */
   /* must insert a deflst for each decomposed word of this tni */ 
   wlen = __get_tn_vec_size(&(__tntab[tni]));
   for (wi = 0; wi < wlen; wi++)
    {
     __insert_insn(lab_ip, TRUE, I_DEFLST, AM_NONE, AM_REG, tni);
     lab_ip->inxt->isrc.disp = wi;

     /* SJM 01/21/07 - need to set ifru same as previous insn since no */
     /* other obvious way to know net list from location here */
#ifdef __CVC_DEBUG__
     lab_ip->inxt->ifru = lab_ip->ifru;
#endif
    }
   __cur_bbp = NULL;
    
   /* notice do not add the links to the live on entry defines yet */
   domfron_bbp->deflst_added = TRUE;
   if (!domfron_bbp->deflst_processed)
    {
     /* SJM 12/28/06 - LOOKATME - using doubly linked bblklst but */
     /* not setting the bl_prev link - may need later */ 
     new_bblp = alloc_bblklst();
     new_bblp->bl_bbp = domfron_bbp;
     /* add predom frontier to front of to be processed frontier bblks */
     if (__cur_dom_fron_todos == NULL)
      {
       __cur_dom_fron_todos = __cur_dom_fron_tail = new_bblp;
      }
     else
      {
       __cur_dom_fron_tail->bl_nxt = new_bblp;
       __cur_dom_fron_tail = new_bblp;
      } 
    }
  }
}

/*
 * return T if a given bblk already has a deflst insn for a tn 
 */
static int32 has_deflst_insn(struct bblk_t *bbp, int32 tni)
{
 struct insn_t *ip;
 int32 dst_tni;

 for (ip = bbp->ihd->inxt; ip != NULL; ip = ip->inxt)
  {
   if (ip->opcod != I_DEFLST) break;

   dst_tni = xget_tnreg(&(ip->idst));
   if (dst_tni == tni) return(TRUE);
  }
 return(FALSE);
}

/*
 * insert the phi defines for a flow graph entering from each AFS bblk
 *
 * routine is needed because pseudo enter bblk not explicit and the
 * back edges never stored
*/
static void lnk_deflst_live_defs(struct flowg_t *fgp,
 struct avlnode_t **tn_ref_avltab, int32 num_tnrefs)
{
 int32 avli;
 struct bblklst_t *bblp;
 struct tn_dup_t *tndup;
 struct tn_t *tnp;

 /* mark every variable as having undefined current live define insn */
 for (avli = 0; avli < num_tnrefs; avli++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[avli]->valp;
   tnp = &(__tntab[tndup->tni]);

   if (tnp->curdef_ip == NULL) allocinit_curdef_ip(tnp, TRUE);
   else allocinit_curdef_ip(tnp, FALSE);
  }
 /* 05-25-2007 always alloc and init AR_AX since used if any asl wrapper used */ 
 /* must mark as untracked */
 tnp = &(__tntab[AR_AX]);
 if (tnp->curdef_ip == NULL) allocinit_curdef_ip(tnp, TRUE);
 else allocinit_curdef_ip(tnp, FALSE);

 /* even if cross jumps, must insert for every AFS entry */
 for (bblp = fgp->enter_bblks; bblp != NULL; bblp = bblp->bl_nxt)  
  {
   search_link_fud_uses(bblp->bl_bbp);
  }
}

/*
 * alloc and initialize a curdef insn table 
 */
static void allocinit_curdef_ip(struct tn_t *tnp, int32 nd_alloc)
{
 size_t wi, wlen;

 /* SJM 07-26-07 - special case idp base (__idp ti) need netire mod idata siz */
 if (tnp->nd_valtrk_idp_siz) wlen = __inst_mod->mod_idata_siz; 
 else wlen = __get_tn_vec_size(tnp);
 if (nd_alloc)
  {
   tnp->curdef_ip = (struct insn_t **)
    __my_malloc(wlen*sizeof(struct insn_t *));
  }
 for (wi = 0; wi < wlen; wi++) tnp->curdef_ip[wi] = NULL;
}

/*
 * recursively fill every use with the one corresponding live define
 *
 * for uses within a bblk, just set a ptr to the def insn
 *
 * for uses where there is only one def in a predecesor bblk, set def insn
 * ptr from whatever the current tn's define insn is (at most one possible)
 *
 * treats start of bblk live deflst insns as a define - the operands 
 * are the only place multiple join fan-in defines represented
 */
static void search_link_fud_uses(struct bblk_t *bbp)
{
 int32 tabi, tabsiz;
 struct insn_t *end_ip;
 struct bblk_t *succ_bbp;
 struct ndxjmp_t *ndxjp;
 struct bblklst_t *bblp;
 struct insn_info_t *iip;

 /* for each insn in forward direction set use ptrs to def insns and */ 
 /* update current tn live def insns */
 try_set_curdefs_and_savchains(bbp);

 /* add the deflst insn reachable live define RHS list elements for only */
 /* immediate successor of the current bblk */
 end_ip = bbp->itail; 
 iip = __to_iinfo_rec(end_ip->opcod);
 if (iip->iclass == ICLASS_JMP)
  {
   if (end_ip->opcod == I_BBLK_JMP)
    {
     succ_bbp = end_ip->idst.apu.bbp;
     add_deflst_livdefs(succ_bbp);
    }
   else if (end_ip->opcod == I_COND_JMP || end_ip->opcod == I_REAL_COND_JMP)
    {
     succ_bbp = end_ip->isrc.apu.bbp;
     add_deflst_livdefs(succ_bbp);
     succ_bbp = end_ip->idst.apu.bbp;
     add_deflst_livdefs(succ_bbp);
    }
   else __case_terr(__FILE__, __LINE__);
  }
 else if (iip->iclass == ICLASS_NDXJMP)
  {
   ndxjp = end_ip->extrau.ndxjp;
   /* DBG remove -- */
   if (ndxjp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   tabsiz = ndxjp->jtabstart + ndxjp->jtabsiz;
   for (tabi = ndxjp->jtabstart; tabi < tabsiz; tabi++)
    {
     succ_bbp = ndxjp->bbtab[tabi]; 
     add_deflst_livdefs(succ_bbp);
    }
  }
 /* recursively set deflst insn fields and use live def insn links */
 /* for every bblk that current bblk predominates */
 for (bblp = bbp->bblk_pdoms; bblp != NULL; bblp = bblp->bl_nxt)
  {
   search_link_fud_uses(bblp->bl_bbp);
  }

 /* finally resotre any deflst insn or defined tn curdef fields to value */
 /* before processing this bblk - insns processed in backward order */
 restore_savchains(bbp);
}

/*
 * routine to scan forward in a basic block and set use ptrs in insns
 * for tn uses and update save chains and current (last) defs for defines
 */
static void try_set_curdefs_and_savchains(struct bblk_t *bbp)
{
 int32 tni, wdisp, tn_idp_base;
 struct insn_t *ip;
 struct tn_t *tnp;
 struct insn_info_t *iip;

 /* for use, set use ptr, for def or deflst (phi) insn, set save */
 /* so can restore later and update current */
 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt) 
  {
   iip = __to_iinfo_rec(ip->opcod);
   if (ip->opcod == I_DEFLST)
    {
     /* def lists always killing parent defines and never invisible */ 
     tni = xget_tnreg(&(ip->idst));
     tnp = &(__tntab[tni]);
     /* SJM 03/17/07 - the deflst insn's word disp comes from isrc disp fld */
     wdisp = ip->isrc.disp;
     /* DBG remove -- */
     if (tnp->tag_parent_tni != -1) __misc_terr(__FILE__, __LINE__);
     /* --- */

     if (ip->optu.fudp == NULL) ip->optu.fudp = __alloc_init_iusedef();
     ip->optu.fudp->savchain_ip = tnp->curdef_ip[wdisp];
     tnp->curdef_ip[wdisp] = ip;
    }
   else if (iip->iclass == ICLASS_STORE) 
    {
     tni = xget_tnreg(&(ip->isrc));
     /* SJM 03/17/07 - constants are invisible plus non values */
     if (!tn_valtrk_invisible(tni))
      {
       /* for use, can set the chain to define field */
       tnp = &(__tntab[tni]);
       wdisp = get_amode_wdisp(&(tn_idp_base), ip, &(ip->isrc), tnp);

       if (ip->optu.fudp == NULL) ip->optu.fudp = __alloc_init_iusedef();

       /* it is possible for a use to occur with no previous define */
       /* SJM 02/26/07 - for use, point to killing define of the parent */
       if (tnp->curdef_ip[wdisp] == NULL) ip->optu.fudp->isrc_defip = NULL;
       else ip->optu.fudp->isrc_defip = tnp->curdef_ip[wdisp];
      }
     
     tni = xget_tnreg(&(ip->idst));
     if (!tn_valtrk_invisible(tni))
      {
       tnp = &(__tntab[tni]);
       wdisp = get_amode_wdisp(&(tn_idp_base), ip, &(ip->idst), tnp);

       if (ip->optu.fudp == NULL) ip->optu.fudp = __alloc_init_iusedef();

       ip->optu.fudp->savchain_ip = tnp->curdef_ip[wdisp];
       tnp->curdef_ip[wdisp] = ip;
      }
    }
   /* SJM 05-23-2007 why are these iclass cal not iclass asl? */
   else if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
    {
     /* may need to back up here - returns T if need to */
     try_set_asl_wrapper_curdefs(ip);
    } 
   else
    {
     /* for use, can set the chain to define field */
     tni = xget_tnreg(&(ip->isrc));
     if (tni != -1 && !tn_valtrk_invisible(tni))
      {
       tnp = &(__tntab[tni]);
       wdisp = get_amode_wdisp(&(tn_idp_base), ip, &(ip->isrc), tnp);

       if (ip->optu.fudp == NULL) ip->optu.fudp = __alloc_init_iusedef();

       /* it is possible for a use to occur with no previous define */
       /* set to a fixed dummy undef insn since differs from cur not set */
       if (tnp->curdef_ip[wdisp] == NULL) ip->optu.fudp->isrc_defip = NULL;
       else ip->optu.fudp->isrc_defip = tnp->curdef_ip[wdisp];
      }

     /* SJM 03/26/07 - must skip various special case insns that use */ 
     /* dest amode for non insn displacements - never have res tni */
     if (valtrk_insn_skip_dst(ip)) continue;

     /* SJM 02/26/07 - notice to get here dest is a use for binary */
     tni = xget_tnreg(&(ip->idst));
     if (tni != -1 && !tn_valtrk_invisible(tni))
      {
       tnp = &(__tntab[tni]);

       wdisp = get_amode_wdisp(&(tn_idp_base), ip, &(ip->idst), tnp);

       if (ip->optu.fudp == NULL) ip->optu.fudp = __alloc_init_iusedef();
       /* it is possible for a use to occur with no previous define */
       /* set to a fixed dummy undef insn since differs from cur not set */
       if (tnp->curdef_ip[wdisp] == NULL) ip->optu.fudp->idst_defip = NULL;
       else ip->optu.fudp->idst_defip = tnp->curdef_ip[wdisp];
      }
     /* res tnis are never machine regs and never have word disps */
     tni = ip->res_tni;
     if (tni != -1 && !tn_valtrk_invisible(tni))
      {
       tnp = &(__tntab[tni]);
       if (ip->optu.fudp == NULL) ip->optu.fudp = __alloc_init_iusedef();
       ip->optu.fudp->savchain_ip = tnp->curdef_ip[0];
       tnp->curdef_ip[0] = ip;
      }
    }
  }
}

/*
 * routine to set curdef and save chains for asl calls
 *
 * define insn ptr goes in asl def record and gets arg direction
 * (src/dst) from asl info record
 *
 * if there is a write ptr know that asl wrapper ret type is arg ptr and
 * there can be only one arg - it is like pascal value result arg type
 */
static void try_set_asl_wrapper_curdefs(struct insn_t *ip)
{ 
 int32 ai;
 int32 start_ai, arg_tni, wdisp, retwlen, wlen, opand_bytsiz, wi, wi2;
 int32 tn_idp_base;
 struct asl_info_t *aslp;
 struct asl_def_t *aslap;
 struct tn_t *tnp;

 retwlen = __get_asl_insn_retsiz(ip, &opand_bytsiz);
 aslp = __to_aslinfo_rec(ip->idst.disp);
 start_ai = 0;
 /* know if this is an in place change write ptr (value-result), */
 /* will be first argument and return must be void */ 
 if (aslp->asl_op_typ[0] == A_WPTR || aslp->asl_op_typ[0] == A_RWPTR)
  {
   /* DBG remove -- */
   if (!is_unsupported_asl_insn(ip->idst.disp) && aslp->asl_ret_typ != RE_VOID) 
    {
     __misc_terr(__FILE__, __LINE__);
    }
   /* --- */
   aslap = &(ip->extrau.asl_ausedefs[0]);
   /* this is the value-result tn */
   arg_tni = aslap->am_arg.am_tni;
   /* DBG --- */
   if (arg_tni == -1) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* SJM 05-25-07 - if filling wide tht must go on stack, can't track */
   if (tn_valtrk_invisible(arg_tni)) return;

   tnp = &(__tntab[arg_tni]);
   if (ip->optu.fudp == NULL) ip->optu.fudp = __alloc_init_iusedef();
   /* DBG remove -- */
   if (retwlen == 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (aslap->arg_savchain_ips == NULL)
    {
     aslap->arg_savchain_ips = (struct insn_t **)
      __my_malloc(retwlen*sizeof(struct insn_t *));
     for (wi = 0; wi < retwlen; wi++) aslap->arg_savchain_ips[wi] = NULL;
    } 
   wdisp = get_amode_wdisp(&(tn_idp_base), ip, &(aslap->am_arg), tnp);
   for (wi2 = 0, wi = wdisp; wi < wdisp + retwlen; wi++, wi2++)
    {
     aslap->arg_savchain_ips[wi2] = tnp->curdef_ip[wi];
     tnp->curdef_ip[wi] = ip;
    }
   if (aslp->asl_op_typ[0] != A_RWPTR) start_ai = 1;
  }
 else if (aslp->asl_ret_typ != RE_VOID)
  {
   /* DBG remove -- */
   if (retwlen != 1) __misc_terr(__FILE__, __LINE__);
   /* --- */
   arg_tni = AR_AX;
   tnp = &(__tntab[arg_tni]);
   if (ip->optu.fudp == NULL) ip->optu.fudp = __alloc_init_iusedef();
   ip->optu.fudp->savchain_ip = tnp->curdef_ip[0]; 
   tnp->curdef_ip[0] = ip;
  }

 for (ai = start_ai; ai < ip->callasl_argnum; ai++) 
  {
   aslap = &(ip->extrau.asl_ausedefs[ai]);
   arg_tni = aslap->am_arg.am_tni;
   /* src (input) operands */

   if (arg_tni == -1 || tn_valtrk_invisible(arg_tni)) continue;
   tnp = &(__tntab[arg_tni]);

   /* asl wrapper info table determines argument type */
   switch (aslp->asl_op_typ[ai]) {
    case A_INT: case A_NUM:
     /* DBG REMOVE -- */ 
     if (aslp->asl_op_typ[ai] == A_NUM && aslap->am_arg.amode != AM_REG)
      __misc_terr(__FILE__, __LINE__);
     /* --- */
     wdisp = get_amode_wdisp(&(tn_idp_base), ip, &(aslap->am_arg), tnp);
     if (aslap->arg_src_defips == NULL)
      {
       aslap->arg_src_defips = (struct insn_t **) 
        __my_malloc(sizeof(struct insn_t *));
        aslap->arg_src_defips[0] = NULL;
      } 
     if (tnp->curdef_ip[wdisp] == NULL) aslap->arg_src_defips[0] = NULL;
     else aslap->arg_src_defips[0] = tnp->curdef_ip[wdisp];
     break;
    case A_RPTR: case A_RWPTR: case A_DBLE:
     wdisp = get_amode_wdisp(&(tn_idp_base), ip, &(aslap->am_arg), tnp);
     /* SJM 06-12-07 - was wrong treating as bit not byte size */
     wlen = (opand_bytsiz + WRDBYTES - 1)/WRDBYTES;
     if (aslap->arg_src_defips == NULL)
      {
       aslap->arg_src_defips = (struct insn_t **) 
        __my_malloc(wlen*sizeof(struct insn_t *));
       for (wi = 0; wi < wlen; wi++) aslap->arg_src_defips[wi] = NULL;
      } 
     for (wi2 = 0, wi = wdisp; wi < wlen + wdisp; wi++, wi2++)
      {
       if (tnp->curdef_ip[wi] == NULL) aslap->arg_src_defips[wi2] = NULL;
       else aslap->arg_src_defips[wi2] = tnp->curdef_ip[wi];
      } 
     break;
    case A_WPTR: __case_terr(__FILE__, __LINE__);
    default: __case_terr(__FILE__, __LINE__);
   }
  }
}

/*
 * return true for illegal asl wrapper instructions
 */
static int32 is_unsupported_asl_insn(int32 asltyp)
{

 if (asltyp == ASL_STREN_CORRECT_FRC || asltyp == ASL_CORRECT_FRC
   || asltyp == ASL_PSEL_CORRECT_FRC || asltyp == ASL_STREN_PSEL_CORRECT_FRC)
  {
   return(TRUE);
  }
 return(FALSE);
}

/*
 * return T if insn has a dst amode that must be skipped but has 
 * some value (not -1)
 */
static int32 valtrk_insn_skip_dst(struct insn_t *ip)
{
 if (ip->opcod == I_IND_JMP || ip->opcod == I_TSKRET_JMP
  || ip->opcod == I_PORT_IND_JMP) return(TRUE);
 return(FALSE);
}

/*
 * get a one word insns (not an asl wrapper) displacement word disp
 */
static int32 get_insn_res_wdisp(struct insn_t *ip)
{
 int32 tni, wdisp, tn_idp_base;
 struct insn_info_t *iip;
 struct amode_t *amp;

 iip = __to_iinfo_rec(ip->opcod);
 if (iip->iclass == ICLASS_STORE)
  {
   amp = &(ip->idst);
   tni = xget_tnreg(amp);
   wdisp = get_amode_wdisp(&(tn_idp_base), ip, amp, &(__tntab[tni]));
  }
 else if (ip->opcod == I_DEFLST)
  {
   wdisp = ip->isrc.disp;
  }
 else 
  {
   wdisp = 0;
  }
 return(wdisp);
}

/*
 * get a disp (word ndx) for an amode that is the decomposed word offset
 * within a tn (usually 2 words for the a and b parts)
 */
static int32 get_amode_wdisp(int32 *tn_idp_base, struct insn_t *ip,
 struct amode_t *amp, struct tn_t *tnp)
{
 size_t disp, wdisp;
 struct idp_map_t *idp_mapp;
 struct mod_t *mdp;

 disp = 0;
 *tn_idp_base = 0;
 switch (amp->amode) {
  case AM_REG: case AM_NDXREG: 
   break;
  case AM_NDXREG_DISP:
   if (tnp->comlab_typ == COMLAB_NONE)
    { 
     /* DBG remove -- */
     if (tnp->tn_typ != TN_ADR) __misc_terr(__FILE__, __LINE__);
     /* --- */
     disp = 0;
    }
   else if (tnp->nd_valtrk_idp_siz)
    {
     /* SJM 07-24-07 - for idp (%esi) offsets ndx reg disp's need the */
     /* netbp's base - mod's idp area index build so can use */
     wdisp = amp->disp/WRDBYTES;
     /* SJM 07-26-07 - must return low offset for the fix idp offset ones */
     if (wdisp < IDP_HD_WOFS) return(wdisp);

     mdp = ip->inmdp;
     idp_mapp = mdp->mod_idp_map[wdisp];
     /* DBG remove -- */ 
     if (wdisp >= mdp->mod_idata_siz) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* DBG remove -- */
     if (idp_mapp->idpmaptyp != IDPMAP_NVAOFS) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* SJM 07-26-07 - for IDP (%esi) area netbp's wdisp is mod's idata area */
     *tn_idp_base = wdisp - idp_mapp->idpobju.enp->nva_ofs;
     return(wdisp);
    }
   disp = amp->disp;
   break;
  case AM_NONREG_OFS:
   disp = amp->disp;
   break;
  case AM_IDP_ADR_OFS:
   /* DBG remove -- */  
   //PUTMEBACK __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (tnp->comlab_typ == COMLAB_IDP)
    {
     /* SJM 07-24-07 - for idp (%esi) offsets ndx reg disp's need the */
     /* netbp's base - mod's idp area index build so can use */
     wdisp = amp->disp/WRDBYTES;

     /* SJM 07-26-07 - must return low offset for the fix idp offset ones */
     if (wdisp < IDP_HD_WOFS) return(wdisp);

     mdp = ip->inmdp;
     idp_mapp = mdp->mod_idp_map[wdisp];

     /* DBG remove -- */ 
     if (wdisp >= mdp->mod_idata_siz) __misc_terr(__FILE__, __LINE__);
     if (idp_mapp->idpmaptyp != IDPMAP_NVAOFS)
      __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* SJM 07-26-07 - for IDP (%esi) area netbp's wdisp is mod's idata area */
     *tn_idp_base = wdisp - idp_mapp->idpobju.enp->nva_ofs;
     return(wdisp);
    }
   disp = amp->disp;
   break;
  case AM_LABEL: case AM_NLO_ARRNDX: case AM_BBLK: case AM_NLO: 
   break;
  default: __case_terr(__FILE__, __LINE__);
 } 
 /* DBG remove ---
 if ((disp % WRDBYTES) != 0) __misc_terr(__FILE__, __LINE__); 
 --- */
 return(disp/WRDBYTES);
}

/*
 * link one deflst insn ptr ilst element onto front of deflst insn def list
 * for every deflst insn at the beginning of bblk succ bbp
 *
 * insn def list pointed to by extrau field
 * the correct cur live define set previously in the tn's curdef ip field
 */
static void add_deflst_livdefs(struct bblk_t *succ_bbp)
{
 int32 def_tni, wdisp;
 struct insn_t *deflst_ip;
 struct defilst_t *dfilp;

 deflst_ip = succ_bbp->ihd->inxt; 
 /* SJM 12/30/06 - think possible not have no defls (phi) insns */
 for (; deflst_ip->opcod == I_DEFLST; deflst_ip = deflst_ip->inxt)
  {
   /* this is the define tn for this deflst (phi) added insn */
   def_tni = xget_tnreg(&(deflst_ip->idst));
   /* DBG remove -- */
   if (def_tni == -1) __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* def tni is not defined in the bblk entry (AFS) so is really a bottom */
   /* varying but there is no insn that defines it */
   dfilp = (struct defilst_t *) __my_malloc(sizeof(struct defilst_t));
   /* SJM 03/17/07 - the deflst insn's word disp comes from isrc disp fld */
   wdisp = deflst_ip->isrc.disp;
   dfilp->defip = __tntab[def_tni].curdef_ip[wdisp];
   
   /* for now putting on front */
   if (deflst_ip->extrau.defilst == NULL) dfilp->defilstnxt = NULL;
   else dfilp->defilstnxt = deflst_ip->extrau.defilst; 
   deflst_ip->extrau.defilst = dfilp;
  }
}

/*
 * for insns in current bblk in reverse order, for defines and deflst insns
 * restore the current def to value before processing current bblk 
 */
static void restore_savchains(struct bblk_t *bbp)
{
 int32 tni, wdisp, retwlen, opand_bytsiz, wi, wi2, tn_idp_base;
 struct insn_t *ip;
 struct tn_t *tnp;
 struct asl_info_t *aslp;
 struct asl_def_t *aslap;

 /* for use, set use ptr, for def or deflst (phi) insn, set save */
 /* so can restore later and update current */
 for (ip = bbp->itail; ip != NULL; ip = ip->iprev) 
  {
   /* SJM 05-23-2007 why are these iclass call not iclass asl? */
   if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
    {
     aslp = __to_aslinfo_rec(ip->idst.disp);
     aslap = &(ip->extrau.asl_ausedefs[0]);
     /* this is the value-result tn */
     if (aslp->asl_op_typ[0] == A_WPTR || aslp->asl_op_typ[0] == A_RWPTR)
      {
       tni = aslap->am_arg.am_tni;
       tnp = &(__tntab[tni]);
       if (tn_valtrk_invisible(tni)) continue;

       /* DBG remove -- */
       if (ip->optu.fudp == NULL) __misc_terr(__FILE__, __LINE__);
      /* --- */ 

       retwlen = __get_asl_insn_retsiz(ip, &opand_bytsiz);
       wdisp = get_amode_wdisp(&(tn_idp_base), ip, &(aslap->am_arg), tnp);
       /* DBG remove -- */
       if (aslap->arg_savchain_ips == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       for (wi2 = 0, wi = wdisp; wi < wdisp + retwlen; wi++, wi2++)
        {
         tnp->curdef_ip[wi] = aslap->arg_savchain_ips[wi2];
        }
      } 
     else if (aslp->asl_ret_typ != RE_VOID)
      {
       tnp = &(__tntab[AR_AX]);
       tnp->curdef_ip[0] = ip->optu.fudp->savchain_ip;
      }
    }
   else
    {
     tni = xget_insn_res_tni(ip);
     if (tni == -1 || tn_valtrk_invisible(tni)) continue;
       
     /* DBG remove -- */
     if (ip->optu.fudp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */ 

     tnp = &(__tntab[tni]);
     wdisp = get_insn_res_wdisp(ip);
     tnp->curdef_ip[wdisp] = ip->optu.fudp->savchain_ip;
    }
  }
}

/*
 * return T if predecessor bblk is immediate predecessor of bbp 
 * can only be used if know bbp reachable from pred bbp
 */
static int32 def_is_immed_pred(struct insn_t *def_ip, struct bblk_t *bbp)
{
 int32 jti, jt_set_starti, jt_set_endi;
 struct insn_t *ip;
 struct insn_t *jmp_ip;
 struct ndxjmp_t *ndxjp;

 for (ip = def_ip->inxt; ip != NULL; ip = ip->inxt)
  {
   if (__is_jmp_insn(ip->opcod)) goto got_jmp;
  }
 __misc_terr(__FILE__, __LINE__);

got_jmp:
 jmp_ip = ip;
 if (jmp_ip->opcod == I_BBLK_JMP) 
  {
   if (jmp_ip->idst.apu.bbp == bbp) return(TRUE); 
   return(FALSE);
  }
 if (jmp_ip->opcod == I_COND_JMP || jmp_ip->opcod == I_REAL_COND_JMP)
  {
   if (jmp_ip->isrc.apu.bbp == bbp || jmp_ip->idst.apu.bbp == bbp) return(TRUE);
   return(FALSE);
  }
 /* only called if know bbp reachable from pred bblk */
 /* DBG --- */
 if (jmp_ip->opcod != I_IND_JMP) __misc_terr(__FILE__, __LINE__);
 /* --- */
 ndxjp = jmp_ip->extrau.ndxjp;
 jt_set_starti = ndxjp->jtabstart;
 jt_set_endi = jt_set_starti + ndxjp->jtabsiz;
 for (jti = jt_set_starti; jti < jt_set_endi; jti++)
  {
   if (ndxjp->bbtab[jti] == bbp) return(TRUE);
  }
 return(FALSE);
}

// **** UNUSED FROM HERE ****

/*
 * UNUSED ROUTINE TO ALLOW FINDING BBLK FROM INSN INDEX
 * BEWARE CURRENTLY UNUSED AND NEED ENTIRE FLOW GRAPH TO BE RENUMBERS IN ORDER
 */

/*
 * allocate, fill and sort the insn order bbtab
 * assumes glb bblk tab has been filled with flow graph's bblk rpo order tab
 *
 * build a sorted bblk rpo number table sorted by insn order for mapping 
 * from insn to the bblk they are in using fast binary search
 */
//SJM 01/01/07? - not used - could find bblk's from searching sorted bblk
// insn order but not sure how to handle value tracking removed bblks?      
static void alloc_fill_bblk_insn_order_tab(int32 nbblks)
{
 int32 blki;

 /* notice since dummy entry bblk has insns, index is one smaller */
 __insn_order_ndx = (int32 *) __my_malloc((nbblks - 1)*sizeof(int32)); 

 /* copy reverse-post-order bblk tab into insn order bblk tab before sort */
 for (blki = 0; blki < nbblks - 1; blki++)
  {
   __insn_order_ndx[blki] = blki + 1;
  }
 /* can just sort by starting insn ndx */
 qsort(__insn_order_ndx, nbblks - 1, sizeof(int32), cmp_ihd_ndx);
}

/*
 * given 2 bblk reverse post order number - return compare of the
 * corresponding bblk's first insn ndx field
 */
//SJM - unused - for alternative map ip to bblk it is in code
static int32 cmp_ihd_ndx(const void *bblki1, const void *bblki2) 
{
 int32 i1, i2;
 struct bblk_t *bbp1, *bbp2;

 i1 = *((int32 *) bblki1);
 i2 = *((int32 *) bblki2);
 bbp1 = __bblktab[i1];
 bbp2 = __bblktab[i2];
 return(bbp1->ihd->ndx - bbp2->ihd->ndx);
}

/*
 * binary search routine to a bblk that contains a given insn index
 *
 * BEWARE - must call routine to renumber flow graph insns in order before
 * calling this routine
 */
//SJM - unused - for alternative map ip to bblk it is in code
static int32 insn_ndx_srch(int32 ndx, int32 *insn_ndx_bbtab, int32 nbblks)
{
 int32 l, h, m, cv;
 struct bblk_t *bbp;

 if (nbblks == 0) return(-1);

 l = 0; h = nbblks - 1;
 for (;;)
  {
   m = (l + h)/2;

   bbp = __bblktab[insn_ndx_bbtab[m]];

   if (ndx < bbp->ihd->ndx) cv = -1;
   else if (ndx > bbp->itail->ndx) cv = 1;
   else return(m);

   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) break;
  }
 return(-1);
}

// **** UNUSED TO HERE ****

/*
 * ROUTINES TO IMPLEMENT VALUE TRACKING OPTIMIZATION  
 */

/*
 * routine to sequence steps in value tracking optimization for one flow graph
 *
 * after here know RPO numbers and bblk RPO tab good
 *
 * 01/23/07 - notice this must free factored use-defs since shares union
 *
 * 03/10/07 - BEWARE - this can't be called using machine regs without
 * having many uses of am tni fixed
 */
static int32 sequencer_1fg_track_optimize(struct flowg_t *fgp,
 struct mod_t *mdp) 
{
 int32 sav_rm_bblks;
 struct bblklst_t *bblp;

 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "BEFORE ANY value tracking - after deflist insert\n");
   __dmp_flowg_insns(fgp, mdp);
  }

 fgp->fg_num_bblks = count_fg_bblks(fgp); 
 /* mark all insn symolic results unknown (untracked) */
 init_1fg_trk_insns(fgp);
 set_1fg_insn_out_symbolic_vals(fgp);

 /* this simplifies the flow graph - removing insns where can, changing */
 /* amodes if need to and changing back edges and cond jmps to jmps if can */
 optimize_1fg_symbolic_con_out_insns(fgp);

 /* DBG remove ---
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "BEFORE AFTER DEL bblk removal and joining\n");
   __dmp_flowg_insns(fgp, mdp);
  }
 ---- */

 sav_rm_bblks = __removed_bblks;
 /* remove bblks to simplify flow graph block structure */
 /* start by simplifying bblk structure - creates well formed flow graphs */
 simplify_1fg_bblks(fgp, mdp);

 if (__removed_bblks > sav_rm_bblks)
  {
   fgp->fg_num_bblks = count_fg_bblks(fgp); 
   /* since ordered using reverse post order, set bblk rev order num first */ 
   /* val num glb used as bblk number here */
   __rev_po_ndx = fgp->fg_num_bblks;

   __cur_mark++;
   /* SJM 08/08/06 - can't build the rev postorder blk tab until after here */ 
   for (bblp = fgp->enter_bblks; bblp != NULL; bblp = bblp->bl_nxt)  
    {
     set_bblk_rev_postorder_nums(bblp->bl_bbp, NULL);
    }
   __fill_fg_po_bblktab(fgp);
  }
 if (__removed_bblks > sav_rm_bblks)
  {
   /* DBG remove -- */
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout,
      "AFTER SYMBOLIC value tracking optimized (%d bblk removed)\n",
      __removed_bblks - sav_rm_bblks); 

     __dmp_flowg_insns(fgp, mdp);
    }
   /* --- */
   return(TRUE);
  }
 return(FALSE);
}

/*
 * mark all insns in the flow graph as having untracked (unknown) symbolic
 * result value and mark all deflst define insns as undeleable 
 */
static void init_1fg_trk_insns(struct flowg_t *fgp)
{
 int32 blki, tni;
 struct insn_t *ip;
 struct defilst_t *dfilp;
 struct insn_t *defip;
 struct bblk_t *bbp;
 struct asl_info_t *aslp;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];

   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     ip->symb_res_val = TRK_TOP_UNDEF; 
     /* SJM 03/11/07 - can't delete insn's that are input to succ bblk */
     /* deflst when deflst's rebuilt insns may then be non input to deflst */
     /* deflst removed and rebuild after each trk pass */
     if (ip->opcod == I_DEFLST)
      {
       dfilp = ip->extrau.defilst;
       for (; dfilp != NULL; dfilp = dfilp->defilstnxt)
        {
         if (dfilp->defip == NULL) continue;
         defip = dfilp->defip; 
          
         /* SJM 05-24-07 - def lists defines can now be asl wrappers */
         if (defip->opcod == I_CALL_ASLPROC || defip->opcod == I_CALL_ASLFUNC)
          {
           aslp = __to_aslinfo_rec(defip->idst.disp);
           if (aslp->asl_ret_typ == RE_VOID) __misc_terr(__FILE__, __LINE__);
           tni = AR_AX;
          }
         else tni = xget_insn_res_tni(dfilp->defip);

         /* DBG remove -- */
         if (__tntab[tni].tag_parent_tni != -1)
          __misc_terr(__FILE__, __LINE__);
         /* --- */
         __tntab[tni].res_tn_useistays = TRUE;
        }
      }
    }
  }
}

/*
 * determine symbolic output for every insn with result in flow graph
 */
static void set_1fg_insn_out_symbolic_vals(struct flowg_t *fgp)
{
 int32 blki;
 struct insn_t *ip;
 struct bblk_t *bbp;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   __cur_bbp = bbp;

   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     /* SJM 01/20/07 - never need to track com labels NLO type objects */
     /* every insn with a result has a factored use def record */
     if (ip->optu.fudp != NULL)
      {
       /* find symbolic output value for every insn not yet processed */
       if (ip->symb_res_val == TRK_TOP_UNDEF)
        {
         set_insn_dst_state_val(ip);
        }
      }
    }
  }
 __cur_bbp = NULL;
}

/*
 * set insn's destination track state and value 
 *
 * this routine's function is to eval insns and set insn tracked value
 * so if result is a child tracked width is child width - uses
 * use (operand) complex get tracked value for finding the value
 *
 * get tracked value deals with non killing child defines after nearest
 * parent killing define (assuming any define of a parent kills the
 * entire parent)
 *
 * notice that this call get tracked state (and valuue) which in turn
 * may recursively call this routine - works because when know the
 * state and tracking value is fixed (i.e. no need to go through bblks
 * keeping track of tracked state)
 */
static void set_insn_dst_state_val(struct insn_t *ip)
{
 int32 resval, op1_con, op2_con;
 int32 blen, src_con_ti;
 word32 abvec[2], aval1, aval2, res_trk, op1_trk, op2_trk;
 struct insn_t *cmp_ip, *movzbl_ip;
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(ip->opcod);
 abvec[0] = abvec[1] = 0;
 if (ip->opcod == I_DEFLST)
  {
   /* SJM 03/06/07 - deflst insn is unkn unless can do better to chg later */
   ip->symb_res_val = TRK_BOT_VARYING;
   set_deflst_in_state_val(ip);
   return;
  }
 /* SJM 01/19/07 - also need div class here */
 if (iip->iclass == ICLASS_BIN || iip->iclass == ICLASS_SHFT
  || iip->iclass == ICLASS_DIV) 
  {
   /* SJM 01/27/07 - this may get the the use tn's (maybe a child) */
   /* section (or all if a parent) of the defining insns tracked killing */
   /* parent assign updated with intervening non killing child defines */
   op1_trk = get_1w_trk_val(ip, &(ip->isrc), ip->optu.fudp->isrc_defip, abvec);
   if (op1_trk == TRK_CON) aval1 = abvec[0]; else aval1 = 0; 
   op2_trk = get_1w_trk_val(ip, &(ip->idst), ip->optu.fudp->idst_defip, abvec);
   if (op2_trk == TRK_CON) aval2 = abvec[0]; else aval2 = 0;

   if (op1_trk == TRK_BOT_VARYING && op2_trk == TRK_BOT_VARYING) 
    {
     ip->symb_res_val = TRK_BOT_VARYING;
     return;
    }
   if (op1_trk == TRK_CON) op1_con = TRUE; else op1_con = FALSE;
   if (op2_trk == TRK_CON) op2_con = TRUE; else op2_con = FALSE;

   //AIV? - is this width right for your constant eval?
   /* SJM 01/22/07 - know this blen less WBITS or less - for masking */
   blen = __tntab[ip->res_tni].tnwid;

   res_trk = __trk_eval_con_oneword_binop(&(resval), ip->opcod, blen, op1_con,
    aval1, op2_con, aval2); 
   if (res_trk == TRK_CON)
    {
     ip->symb_res_val = TRK_CON;
     if (ip->optu.fudp->ip_trk_valp == NULL)
      {
       /* SJM 02/27/07 - insn tracking when result is child is child size */
       ip->optu.fudp->ip_trk_valp = (word32 *) __my_malloc(WRDBYTES);
       ip->optu.fudp->trk_nbytes = WRDBYTES;
      }
     ip->optu.fudp->ip_trk_valp[0] = resval;
    }
   else ip->symb_res_val = res_trk;
   return;
  }

 /* this is only unary insn that can be simplified - others con folded only */
 if (ip->opcod == I_NOTL || ip->opcod == I_NEGL)
  {
   /* need to call to make sure insn's symbolic output state set */ 
   /* valp is tracked is src operand tn's tracked value */

   op1_trk = get_1w_trk_val(ip, &(ip->isrc), ip->optu.fudp->isrc_defip, abvec);
   if (op1_trk == TRK_BOT_VARYING) ip->symb_res_val = TRK_BOT_VARYING;
   else if (op1_trk == TRK_CON)
    {
     ip->symb_res_val = TRK_CON;
     if (ip->optu.fudp->ip_trk_valp == NULL)
      {
       /* SJM 02/27/07 - insn tracking when result is child is child size */
       ip->optu.fudp->ip_trk_valp = (word32 *) __my_malloc(WRDBYTES);
       ip->optu.fudp->trk_nbytes = WRDBYTES;
      }
     /* SJM 04/28/07 - x86 notl insn is 1's complement and x86 negl is 2's */
     /* complement that is only generated in sign extension - the Verilog */
     /* logical not (!) is decomposed so never seen here */
     if (ip->opcod == I_NOTL) resval = ~(abvec[0]);
     /* neg insn also may be constant from tracking */
     else if (ip->opcod == I_NEGL) resval = ~(abvec[0]) + 1;
     else __case_terr(__FILE__, __LINE__);
     ip->optu.fudp->ip_trk_valp[0] = resval;
    }
   else __case_terr(__FILE__, __LINE__);
   return;
  }
 if (ip->opcod == I_TESTL)
  {
   /* DBG remove -- */
   if (ip->isrc.am_tni != ip->idst.am_tni) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* valp is tracked is src operands (both) one tn's tracked value */
   op1_trk = get_1w_trk_val(ip, &(ip->isrc), ip->optu.fudp->isrc_defip, abvec);
   if (op1_trk == TRK_BOT_VARYING) ip->symb_res_val = TRK_BOT_VARYING;
   else if (op1_trk == TRK_CON) 
    {
     ip->symb_res_val = TRK_CON;
     if (ip->optu.fudp->ip_trk_valp == NULL)
      {
       ip->optu.fudp->ip_trk_valp = (word32 *) __my_malloc(WRDBYTES);
       ip->optu.fudp->trk_nbytes = WRDBYTES;
      }
     ip->optu.fudp->ip_trk_valp[0] = (abvec[0] == 0);
    }
   else __case_terr(__FILE__, __LINE__);
   return;
  }
 /* SJM 01/24/07 - need special case tracking of sete insn */
 if (ip->opcod == I_SETE) 
  {
   cmp_ip = ip->iprev;
   /* track logical not (sete used in boiler plate sequence) */
   /* DBG  remove -- */
   if (cmp_ip->opcod != I_CMPL || !__is_constant(cmp_ip->isrc.am_tni))
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* valp is tracked is src operands (both) one tn's tracked value */
   op2_trk = get_1w_trk_val(cmp_ip, &(ip->idst), cmp_ip->optu.fudp->idst_defip,
    abvec);

   /* must leave cmpl $0, <op2>; sete %eax; movzbl if not track con */
   if (op2_trk != TRK_CON) return;

   /* must change insn boilerplate sequence here */
   movzbl_ip = ip->inxt;
   /* DBG remove -- */
   if (movzbl_ip->opcod != I_MOVZBL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* can and must link out the previous cmpl */
   __linkout_insn(cmp_ip, TRUE);
   /* can't link out current sete - but must mark for removal */
   ip->symb_res_val = TRK_CON;

   if (abvec[0] == 0) src_con_ti = __gen_cint_tn(1);
   else src_con_ti = __gen_cint_tn(0);
   movzbl_ip->opcod = I_MOVA;
   __init_amode(&(movzbl_ip->isrc));
   movzbl_ip->isrc.am_tni = src_con_ti;
   movzbl_ip->isrc.amode = AM_REG;
   /* loop next will track the new movl insn */
   return;
  }
 if (iip->iclass == ICLASS_CMP)
  {
   set_cmp_trk_state_val(ip);
   return;
  }
 /* SJM 03/16/07 - copy insn no longer possible - moved tracking past */
 /* copy expand and wide tn decompositon but still with 3 addr res insns */
 /* DBG remove -- */
 if (ip->opcod == I_COPY) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (iip->iclass == ICLASS_MOV || iip->iclass == ICLASS_STORE)
  {
   /* valp is tracked is src operand tn's tracked value */
   /* need to call to make sure insn's symbolic output state set */ 
   op1_trk = get_1w_trk_val(ip, &(ip->isrc), ip->optu.fudp->isrc_defip, abvec);
   if (op1_trk == TRK_BOT_VARYING) ip->symb_res_val = TRK_BOT_VARYING;
   else if (op1_trk == TRK_CON)
    {
     ip->symb_res_val = TRK_CON;

     if (ip->optu.fudp->ip_trk_valp == NULL)
      {
       /* 02/27/07 - a move into a child output insn values is width of */
       /* child taken from nearest parent killing assign corrected for */
       /* any intervening non killing child defines */

       ip->optu.fudp->ip_trk_valp = (word32 *) __my_malloc(WRDBYTES);
       ip->optu.fudp->trk_nbytes = WRDBYTES;
      }
     ip->optu.fudp->ip_trk_valp[0] = abvec[0];
    }
   else __case_terr(__FILE__, __LINE__);
   return;
  }
 /* SJM 03/04/07 - no tracking yet for other insns such as ASL wrappers */
 if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
  {
   set_asl_wrapper_trk_state_val(ip);
  }
 return;
}

/*
 * routine to set the in (combined backed edge fan in) state for a given
 * deflst insn's one tn (phi entry state)
 *
 * know symbolic output (in to bblk) value not know or will not be called
 *
 * SJM 02/27/07 - FIXME? - should put in code to insure that after the
 * deflst last killing assign there are no children non killing assigns
 * afterward in the back edge (possibly distant predecessor) parent killing
 * assign
//AIV? is this true?
 */
static void set_deflst_in_state_val(struct insn_t *ip)
{
 int32 di, one_bot_varying, wlen;
 word32 *valp, *valp2;
 struct defilst_t *dfilp;
 struct insn_t *def_ip;

 /* first make sure all defines deflst define ins have their output dst */
 /* value set and known */
 one_bot_varying = FALSE;
 dfilp = ip->extrau.defilst;
 for (di = 0; dfilp != NULL; dfilp = dfilp->defilstnxt, di++)
  {
   def_ip = dfilp->defip;

   /* SJM 01/20/07 - def ip nil means one back edge entry a use before def */
   if (def_ip == NULL)
    {
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "++ DEFLST B%d:%d: def insn (no. %d) is use before def\n",
        __cur_bbp->bblk_seqno, ip->ndx, di);
      } 
     /* --- */
     one_bot_varying = TRUE;
     continue;
    }

   /* DBG remove -- */
   if (def_ip->symb_res_val == TRK_UNKN) __misc_terr(__FILE__, __LINE__);
   /* -- */

   /* SJM 03/23/07 - if def insn track state not know, compute it */
   /* think should never need this anymore? */
   if (def_ip->symb_res_val == TRK_TOP_UNDEF)
    { 
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "++ DEFLST B%d:%d: def insn (no. %d) -  track state set here\n",
        __cur_bbp->bblk_seqno, ip->ndx, di);
      } 
     /* --- */
     set_insn_dst_state_val(def_ip);
    }

   if (def_ip->symb_res_val == TRK_BOT_VARYING)
    {
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "++ DEFLST B%d:%d: def insn %d (no. %d) bottom varying\n", 
        __cur_bbp->bblk_seqno, ip->ndx, def_ip->ndx, di);
      } 
     /* --- */
     one_bot_varying = TRUE;
     continue;
    }
   /* if trk con, nothing to do */
   if (def_ip->symb_res_val == TRK_CON)
    {
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "++ DEFLST B%d:%d: def insn %d (no. %d) const val %d\n", 
        __cur_bbp->bblk_seqno, ip->ndx, def_ip->ndx, di,
        def_ip->optu.fudp->ip_trk_valp[0]);
      } 
     /* --- */
     continue;
    }
   __case_terr(__FILE__, __LINE__);
  }
 if (one_bot_varying)
  {
   ip->symb_res_val = TRK_BOT_VARYING;
   return;
  }

 /* if all TRK CON, must make sure also all the same value */
 valp = NULL;
 wlen = __get_tn_vec_size(&(__tntab[ip->idst.am_tni]));

 /* deflst (phi) insn's back edge join tn must always be a parent */
 /* DBG remove -- */ 
 if (__tntab[ip->idst.am_tni].tag_parent_tni != -1)
  __misc_terr(__FILE__, __LINE__); 
 /* --- */ 
 dfilp = ip->extrau.defilst;
 for (di = 0; dfilp != NULL; dfilp = dfilp->defilstnxt, di++)
  {
   /* if def ip nil (use before def) can never get here */ 
   def_ip = dfilp->defip;
   /* DBG remove -- */
   if (def_ip->symb_res_val != TRK_CON) __misc_terr(__FILE__, __LINE__);
   /* --- */

   if (valp == NULL) valp = def_ip->optu.fudp->ip_trk_valp;
   else
    {
     valp2 = def_ip->optu.fudp->ip_trk_valp;
     if (memcmp(valp, valp2, WRDBYTES*wlen) != 0)
      {
       ip->symb_res_val = TRK_BOT_VARYING;
//SJM - BEWARE if trying to use tracking on machine reg assigned flowgs
//      think this can't work?        
       __tntab[ip->idst.am_tni].res_tn_useistays = TRUE;

       /* DBG remove -- */
       if (__opt_debug_flg)
        {
         __my_fprintf(stdout,
         "++ DEFLST B%d:%d: con trk val %d differs from (no. %d) con val %d\n",
         __cur_bbp->bblk_seqno, ip->ndx, valp[0], di, valp2[0]);
        }
       /* --- */
       return;
      }
    }
  }
 /* DBG remove -- */
 if (valp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* DBG remove -- */
 if (__opt_debug_flg)
   {
    __my_fprintf(stdout, "++ DEFLST B%d:%d: all same trk const value %d\n",
     __cur_bbp->bblk_seqno, ip->ndx, valp[0]);
   }
  /* --- */

 ip->symb_res_val = TRK_CON;
 if (ip->optu.fudp->ip_trk_valp == NULL)
  {
   ip->optu.fudp->ip_trk_valp = (word32 *) __my_malloc(WRDBYTES*wlen);
   ip->optu.fudp->trk_nbytes = WRDBYTES*wlen;
  }
 memcpy(ip->optu.fudp->ip_trk_valp, valp, WRDBYTES*wlen);
}

/*
 * routine to set the track state for a compare insn
 *
 * since testl now have repeated args, treated as separate case
 *
 * SJM 01/15/07 - this is special case for one TRK CON - must change
 * insn so tracked is changed to right con - info only known here
 * for constand testl/cmp[lbw] - insn removed and flowg changed elsewhere 
 */
static void set_cmp_trk_state_val(struct insn_t *cmp_ip)
{
 int32 src_trk, dst_trk, src_con_ti, new_cc, jmp_lab1;
 word32 abvec[2], aval1, aval2;
 struct insn_t *jmp_ip;

 jmp_ip = cmp_ip->inxt;

 /* SJM 01/23/07 - sequence "cmpl <src>, <dst>; sete ..." possible */
 /* FIXME? need sete tracking */
 if (jmp_ip->opcod == I_SETE) 
  {
   /* ok for sete to follow cmpl, the sete is tracked - nothing to do here */
   return;
  } 

 /* DBG remove -- */
 if (jmp_ip->opcod != I_COND_JMP && jmp_ip->opcod != I_REAL_COND_JMP)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* moves tracked into abvec - is src operands (both) one tn's tracked value */
 src_trk = get_1w_trk_val(cmp_ip, &(cmp_ip->isrc), 
  cmp_ip->optu.fudp->isrc_defip, abvec);

 aval1 = abvec[0];
 dst_trk = get_1w_trk_val(cmp_ip, &(cmp_ip->idst), 
  cmp_ip->optu.fudp->idst_defip, abvec);
 aval2 = abvec[0];
 if (src_trk == TRK_BOT_VARYING && dst_trk == TRK_BOT_VARYING)
  {
   cmp_ip->symb_res_val = TRK_BOT_VARYING;
   return;
  }
 /* SJM 12/16/06 - if one but not both cmp insn operands is tracked */
 /* must change the insn - convert the tracked tn to a cint */
 else if (src_trk == TRK_CON && dst_trk != TRK_CON)
  {
   cmp_ip->symb_res_val = TRK_BOT_VARYING;

   src_con_ti = __gen_cint_tn(aval1);
   __init_amode(&(cmp_ip->isrc));
   cmp_ip->isrc.am_tni = src_con_ti;
   cmp_ip->isrc.amode = AM_REG;
  }
 else if (src_trk != TRK_CON && dst_trk == TRK_CON)
  {
   cmp_ip->symb_res_val = TRK_BOT_VARYING;

   src_con_ti = __gen_cint_tn(aval2);
   __copy_amode(&(cmp_ip->idst), &(cmp_ip->isrc));
   __init_amode(&(cmp_ip->isrc));
   cmp_ip->isrc.am_tni = src_con_ti;
   cmp_ip->isrc.amode = AM_REG;
 
   /* jmp insn sense needs to be inverted */
   new_cc = __invert_cc(jmp_ip->jmptyp);
   jmp_ip->jmptyp = new_cc;
  }
 else if (src_trk == TRK_CON && dst_trk == TRK_CON)
  { 
   cmp_ip->symb_res_val = TRK_CON;
   if (cmp_ip->optu.fudp->ip_trk_valp == NULL)
    {
     cmp_ip->optu.fudp->ip_trk_valp = (word32 *) __my_malloc(WRDBYTES);
     cmp_ip->optu.fudp->trk_nbytes = WRDBYTES;
    }
   jmp_lab1 = get_jmp_cmpl_cc_result(jmp_ip->jmptyp, aval1, aval2);
   cmp_ip->optu.fudp->ip_trk_valp[0] = jmp_lab1;
  }
 else __case_terr(__FILE__, __LINE__);
}

/*
 * determine if jump is T or F tracked value depending on constant 
 * (tracked) operands to a cmpl and the jump's condition code
 */
static int32 get_jmp_cmpl_cc_result(int32 cc, int32 op1val, int32 op2val)
{
 int32 jmp_lab1; 

 jmp_lab1 = -1;
 switch (cc) {
  case CC_JE:
   jmp_lab1 = (op1val == op2val);
   break;
  case CC_JNE:
   jmp_lab1 = !(op1val != op2val);
   break;
  case CC_JGE:
//AIV? LOOKATME 
   jmp_lab1 = !(op1val >= op2val);
   break;
  case CC_JGT:
//AIV? LOOKATME 
   jmp_lab1 = !(op1val > op2val);
   break;
  case CC_JLE:
//AIV? LOOKATME 
   jmp_lab1 = !(op1val <= op2val);
   break;
  case CC_JLT:
//AIV? LOOKATME - to make shift work - need to test op2 < op1 - WHY????
   /* SJM cmp x86 insn is src - dst (dst sign extended) */ 
   /* so not sure why bbgen3 code expects cmpl (CC_JLT) 32, 18 takes label 1 */
   /* AIV FIXME - insn't this backward? - you are using dst <= src? */
   jmp_lab1 = !(op1val < op2val);
   break;
  case CC_JP: case CC_JRZ:
   /* only for reals - will never be tracked */  
   __case_terr(__FILE__, __LINE__);
   break;
  /* never used */
  case CC_NONE: case CC_JNZ: case CC_JZ: case CC_JNS:
  case CC_JA: case CC_JB: case CC_JAE: case CC_JBE:
   __case_terr(__FILE__, __LINE__);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(jmp_lab1);
}

/*
 * ROUTINES TO ACESS TRACKED VALUES TO SET INSN RESULT TRACKING STATE
 */

/*
 * routine to set trk output value for asl wrapper 
 */
static void set_asl_wrapper_trk_state_val(struct insn_t *ip)
{
 int32 asl_trk;
 word32 abvec[2];
 struct asl_info_t *aslp;
 struct asl_def_t *aslap;

 aslp = __to_aslinfo_rec(ip->idst.disp);
 switch (aslp->asl_rout_num) {
  case ASL_WRD_REDXOR:
   /* know result and src arg are exactly one word for this one - non wide */
   aslap = &(ip->extrau.asl_ausedefs[0]);
   asl_trk = get_1w_trk_val(ip, &(aslap->am_arg), aslap->arg_src_defips[0],
    abvec);
   if (asl_trk == TRK_BOT_VARYING) ip->symb_res_val = TRK_BOT_VARYING;
   else if (asl_trk == TRK_CON)
    {
     ip->symb_res_val = TRK_CON;
     if (ip->optu.fudp->ip_trk_valp == NULL)
      {
       /* SJM 02/27/07 - insn tracking when result is child is child size */
       ip->optu.fudp->ip_trk_valp = (word32 *) __my_malloc(WRDBYTES);
       ip->optu.fudp->trk_nbytes = WRDBYTES;
      }
     ip->optu.fudp->ip_trk_valp[0] = abvec[0];
    }
   else __case_terr(__FILE__, __LINE__);
   break;
  case ASL_LADD:
   set_wide_binop_trk_state_val(ip);
   break;
  case ASL_WIDE_JMPOR_0:
   set_wide_jmpor0_cmp_trk_state_val(ip);
   break;
  case ASL_SGN_WIDE_CMP: case ASL_WIDE_CMP: case ASL_WIDE_JMP_EQ:
   set_wide_cmp_trk_state_val(ip);
   break;
  default:
   ip->symb_res_val = TRK_BOT_VARYING;
   break;
 }
}

/*
 * set the track state for wide jmp or0
 */ 
static void set_wide_jmpor0_cmp_trk_state_val(struct insn_t *cmp_ip)
{
 int32 opand_bytsiz, testl_res;
 int32 retwlen, a1_all_trk, a2_all_trk;
 int32 arg_wlen, one_def, *trk_state_vec;
 word32 *valp;
 struct asl_def_t *aslap;

 /* get width of operands (always same) in bytes and return wlen */
 aslap = &(cmp_ip->extrau.asl_ausedefs[2]);
 retwlen = __get_asl_insn_retsiz(cmp_ip, &opand_bytsiz);

 /* DBG remove -- */
 if ((opand_bytsiz % WRDBYTES) != 0) __misc_terr(__FILE__, __LINE__);
 if (retwlen != 1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 arg_wlen = opand_bytsiz/WRDBYTES;
 trk_state_vec = (int32 *) alloca(arg_wlen);
 valp = (word32 *) alloca(arg_wlen);

 aslap = &(cmp_ip->extrau.asl_ausedefs[0]);
 one_def = get_asl_wide_trk_val(cmp_ip, &(aslap->am_arg), arg_wlen,
  aslap->arg_src_defips, trk_state_vec, valp); 
 if (wide_trk_valp_any1_con(one_def, trk_state_vec, valp, arg_wlen))
  {
   /* SJM 06-12-07 - any 1 is false, i.e. not 0 - T is 1 */
   testl_res = 1;
   goto rem_fix_testl;
  }
 if (asl_wide_all_trk_con(one_def, trk_state_vec, arg_wlen)) a1_all_trk = TRUE;
 else a1_all_trk = FALSE;

 aslap = &(cmp_ip->extrau.asl_ausedefs[1]);
 one_def = get_asl_wide_trk_val(cmp_ip, &(aslap->am_arg), arg_wlen,
  aslap->arg_src_defips, trk_state_vec, valp); 
 if (wide_trk_valp_any1_con(one_def, trk_state_vec, valp, arg_wlen))
  {
   /* SJM 06-12-07 - any 1 is false, i.e. not 0 - T is 1 */
   testl_res = 1;
   goto rem_fix_testl;
  }
 if (asl_wide_all_trk_con(one_def, trk_state_vec, arg_wlen)) a2_all_trk = TRUE;
 else a2_all_trk = FALSE;

 /* SJM 06-12-07 - if both 0 trk con known T */
 if (a1_all_trk && a2_all_trk) { testl_res = 0; goto rem_fix_testl; }
 cmp_ip->symb_res_val = TRK_BOT_VARYING;
 return;
 
rem_fix_testl:
 chg_testl_to_con(cmp_ip, testl_res);
 __linkout_insn(cmp_ip, TRUE);
}

/*
 * change a testl insn with %eax (from wide asl compares) to a constant testl
 */
static void chg_testl_to_con(struct insn_t *cmp_ip, int32 retval) 
{
 int32 cint_ti;
 struct insn_t *testl_ip;

 /* remove the ASL jmp or0 and make the testl constant - tracking set their */
 testl_ip = cmp_ip->inxt;
 /* DBG remove -- */
 if (testl_ip->opcod != I_TESTL) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 /* SJM 06/10/07 - since don't see ASL insns remove here and make */
 /* the testl have a constant arg - works since result goes into %eax */
 __init_amode(&(testl_ip->isrc));
 __init_amode(&(testl_ip->idst));
 cint_ti = __gen_cint_tn(retval);
 testl_ip->isrc.amode = AM_REG;
 testl_ip->isrc.am_tni = cint_ti; 
 testl_ip->idst.amode = AM_REG;
 testl_ip->idst.am_tni = cint_ti; 
}

/*
 * return T if asl wide tracked value has any 1
 */
static int32 wide_trk_valp_any1_con(int32 one_def, int32 *trk_state_vec,
 word32 *valp, int32 arg_wlen)
{
 int32 ai; 

 if (one_def)
  {
   if (trk_state_vec[0] == TRK_BOT_VARYING) return(FALSE);
   if (trk_state_vec[0] == TRK_CON)
    {
     for (ai = 0; ai < arg_wlen; ai++)
      {
       if (valp[ai] != 0) return(TRUE);
      }
     return(FALSE);
    }
   else __misc_terr(__FILE__, __LINE__);
   return(FALSE);
  }
 for (ai = 0; ai < arg_wlen; ai++)
  {
   if (trk_state_vec[ai] != TRK_CON) continue;
   if (valp[ai] != 0) return(TRUE);
  }
 return(FALSE);
}

/*
 * return T if asl wide operand tracked
 */
static int32 asl_wide_all_trk_con(int32 one_def, int32 *trk_state_vec,
 int32 arg_wlen)
{
 int32 ai;

 if (one_def)
  {
   if (trk_state_vec[0] == TRK_CON) return(TRUE);
   return(FALSE);
  }
 for (ai = 0; ai < arg_wlen; ai++) 
  {
   if (trk_state_vec[ai] != TRK_CON) return(FALSE);
  }
 return(TRUE);
}

/*
 * set the track state for wide cmp
 */ 
static void set_wide_cmp_trk_state_val(struct insn_t *cmp_ip)
{
 int32 opand_bytsiz, blen, retwlen, cc;
 int32 arg_wlen, one_def, *trk_state_vec, trk_val, retval;
 word32 *a1_valp, *a2_valp;
 struct asl_info_t *aslp;
 struct asl_def_t *aslap;

 aslp = __to_aslinfo_rec(cmp_ip->idst.disp);

 trk_val = -1;
 retval = -1;
 /* get width of operands (always same) in bytes and return wlen */
 aslap = &(cmp_ip->extrau.asl_ausedefs[2]);
 retwlen = __get_asl_insn_retsiz(cmp_ip, &opand_bytsiz);

 /* DBG remove -- */
 if ((opand_bytsiz % WRDBYTES) != 0) __misc_terr(__FILE__, __LINE__);
 if (retwlen != 1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 arg_wlen = opand_bytsiz/WRDBYTES;
 trk_state_vec = (int32 *) alloca(arg_wlen);
 a1_valp = (word32 *) alloca(arg_wlen);
 a2_valp = (word32 *) alloca(arg_wlen);

 aslap = &(cmp_ip->extrau.asl_ausedefs[0]);
 one_def = get_asl_wide_trk_val(cmp_ip, &(aslap->am_arg), arg_wlen,
  aslap->arg_src_defips, trk_state_vec, a1_valp); 
 /* if any part of arg 1 untracked - compare can't be tracked */
 if (!asl_wide_all_trk_con(one_def, trk_state_vec, arg_wlen))
  {
   cmp_ip->symb_res_val = TRK_BOT_VARYING;
   return;
  }

 aslap = &(cmp_ip->extrau.asl_ausedefs[1]);
 one_def = get_asl_wide_trk_val(cmp_ip, &(aslap->am_arg), arg_wlen,
  aslap->arg_src_defips, trk_state_vec, a2_valp); 

 if (!asl_wide_all_trk_con(one_def, trk_state_vec, arg_wlen))
  {
   cmp_ip->symb_res_val = TRK_BOT_VARYING;
   return;
  }

 /* SJM 06-10-07 - could use the arg wlen converted to bits here */
 aslap = &(cmp_ip->extrau.asl_ausedefs[2]);
 blen = __get_wrd_con_val(aslap->am_arg.am_tni);

 if (aslp->asl_rout_num == ASL_SGN_WIDE_CMP)
  {
   aslap = &(cmp_ip->extrau.asl_ausedefs[3]);
   cc = __get_wrd_con_val(aslap->am_arg.am_tni);
   retval = __asl_sgn_wide_cmp(a1_valp, a2_valp, blen, cc);
  }
 else if (aslp->asl_rout_num == ASL_WIDE_CMP)
  {
   aslap = &(cmp_ip->extrau.asl_ausedefs[3]);
   cc = __get_wrd_con_val(aslap->am_arg.am_tni);
   retval = __asl_wide_cmp(a1_valp, a2_valp, blen, cc);
  }
 else if (aslp->asl_rout_num == ASL_WIDE_JMP_EQ)
  {
//AIV - is comp of jump eq compare the same as jmp eq
   retval = __asl_wide_jmp_eq(a1_valp, a2_valp, blen);
  }
 else __case_terr(__FILE__, __LINE__);

 chg_testl_to_con(cmp_ip, retval);
 __linkout_insn(cmp_ip, TRUE);
}

/*
 * set value tracking wide binop state - if folds replace with expanded
 * copy insn
 */
static void set_wide_binop_trk_state_val(struct insn_t *ip)
{
 int32 opand_bytsiz, blen, retwlen;
 int32 arg_wlen, one_def, *trk_state_vec;
 word32 *a1_valp, *a2_valp, *res_valp;
 struct asl_info_t *aslp;
 struct asl_def_t *aslap;

 aslp = __to_aslinfo_rec(ip->idst.disp);

 /* get width of operands (always same) in bytes and return wlen */
 aslap = &(ip->extrau.asl_ausedefs[2]);
 retwlen = __get_asl_insn_retsiz(ip, &opand_bytsiz);

 /* DBG remove -- */
 if ((opand_bytsiz % WRDBYTES) != 0) __misc_terr(__FILE__, __LINE__);
 if (opand_bytsiz != retwlen*WRDBYTES) __misc_terr(__FILE__, __LINE__);
 /* --- */
 arg_wlen = opand_bytsiz/WRDBYTES;
 trk_state_vec = (int32 *) alloca(arg_wlen);
 a1_valp = (word32 *) alloca(arg_wlen);
 a2_valp = (word32 *) alloca(arg_wlen);
 res_valp = (word32 *) alloca(arg_wlen);

 aslap = &(ip->extrau.asl_ausedefs[1]);
 one_def = get_asl_wide_trk_val(ip, &(aslap->am_arg), arg_wlen,
  aslap->arg_src_defips, trk_state_vec, a1_valp); 
 /* if any part of arg 1 untracked - compare can't be tracked */
 if (!asl_wide_all_trk_con(one_def, trk_state_vec, arg_wlen))
  {
   ip->symb_res_val = TRK_BOT_VARYING;
   return;
  }

 aslap = &(ip->extrau.asl_ausedefs[2]);
 one_def = get_asl_wide_trk_val(ip, &(aslap->am_arg), arg_wlen,
  aslap->arg_src_defips, trk_state_vec, a2_valp); 

 if (!asl_wide_all_trk_con(one_def, trk_state_vec, arg_wlen))
  {
   ip->symb_res_val = TRK_BOT_VARYING;
   return;
  }

 /* SJM 06-10-07 - could use the arg wlen converted to bits here */
 aslap = &(ip->extrau.asl_ausedefs[3]);
 blen = __get_wrd_con_val(aslap->am_arg.am_tni);

 if (aslp->asl_rout_num == ASL_LADD)
  {
   __ladd(res_valp, a1_valp, a2_valp, blen);
  }
 else __case_terr(__FILE__, __LINE__);

 ip->symb_res_val = TRK_CON;
 if (ip->optu.fudp->ip_trk_valp == NULL)
  {
   /* SJM 02/27/07 - insn tracking when result is child is child size */
   ip->optu.fudp->ip_trk_valp = (word32 *) __my_malloc(retwlen*WRDBYTES);
   ip->optu.fudp->trk_nbytes = retwlen*WRDBYTES;
  }
 memcpy(ip->optu.fudp->ip_trk_valp, res_valp, retwlen*WRDBYTES);
}

/*
 * get non wide wrapper insn tracked val state
 *
 * starts at use and keep working back until  know start of use-def chain
 * which make all symbolic val states fixed (i.e. works back to beginning of
 * chain so is relaxed)
 * 
 * SJM 01/14/07 - since storing tracked symbolic out state in each insn 
 * do not need any tn processing here - during insn simplification may change
 * insns and tns
 *
 * except for tracked (trk con) trkvalp not changed
 *
 * SJM 02/27/07 - BEWARE - new algorithm requires that all assign to parent
 * tn's are killing, i.e. their is an implied setting to x of higher words
 * if the assigned number of bytes is less than the tn size
 *
 * SJM 02/27/07 - maybe need consistency checking for prefix killing assigns
 */
static int32 get_1w_trk_val(struct insn_t *ip, struct amode_t *amp,
 struct insn_t *def_ip, word32 *valp)
{
 int32 use_tni, wdisp, tn_idp_base;
 word32 abvec[2], *convalp;

 use_tni = xget_tnreg(amp);
 wdisp = get_amode_wdisp(&(tn_idp_base), ip, amp, &(__tntab[use_tni]));
 /* case 1: src is a constant - easy get tracked value */
 if (__is_constant(use_tni))
  {
   /* SJM 04/30/07 - for conadr need to get the disp (offset in contab) */
   /* from amode so get b parts of contabs when needed */
   convalp = get_tracked_con(use_tni, abvec);
   if (wdisp > 0) convalp = &(convalp[wdisp]);

   /* SJM 04/30/07 - since all non wrappers are 4 byte x86 insns operand */
   /* must be 4 bytes - wide asl wrappers can never call this */
   /* get vec size can be wider than 4 bytes but just uses the first word */
   valp[0] = convalp[0];

   /* DBG remove -- */
   if (__opt_debug_flg)
     {
      __my_fprintf(stdout,
       "++ SRC con (FROM B%d:%d) - FROM CON r%d wrd val %x\n",
       __cur_bbp->bblk_seqno, ip->ndx, use_tni, valp[0]);
     }
    /* --- */
   return(TRK_CON);
  }

 /* case 2: use does not have a def - value if bottom varying */
 if (def_ip == NULL)
  {
   /* DBG remove -- */
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout,
      "++ SRC bottom varying (FROM B%d:%d) - r%d USE BEFORE DEF\n",
      __cur_bbp->bblk_seqno, ip->ndx, use_tni);
    }
   /* --- */
   return(TRK_BOT_VARYING);
  }

 /* case 3: there is a defining insn */ 
 /* if this is the first time see this killing parent define, must */
 /* determine its result trk state and value if tracked */
 if (def_ip->symb_res_val == TRK_TOP_UNDEF)
  {
//SJM 06-10-07 REMOVE - NEED TO DO THIS BEFORE HERE
   //??? __misc_terr(__FILE__, __LINE__);
   set_insn_dst_state_val(def_ip);
  }

 /* case 3a: defining insn def (output) not tracked */
 /* tracked output state of the uses defining insn known */
 if (def_ip->symb_res_val == TRK_BOT_VARYING)
  {
   /* DBG remove -- */
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout,
      "++ SRC bottom varying (FROM B%d:%d) - r%d FROM DEF INSN %d\n",
      __cur_bbp->bblk_seqno, ip->ndx, use_tni, def_ip->ndx);
    }
   /* --- */
   return(TRK_BOT_VARYING);
  }

 /* case 3b: defining insn def (output) killing parent tracked */
 /* DBG remove -- */
 if (def_ip->symb_res_val != TRK_CON) __misc_terr(__FILE__, __LINE__); 
 /* --- */

 /* SJM 03/16/07 - no longer have the child killing part of parent problem */ 

 /* copy in to caller passed area, src use's defining killing parent */
 /* insn's tracked value */

 /* SJM 07-24-06 - def insn may be an asl wrapper (probably wide) */
 /* when it is, need to get the tracked value of the move/store, i.e. */
 /* word machine insn from the right tracked value offset */
 /* works because the the def insn disp is the right tracked offset of the */ 
 /* wide insn */ 
//SJM? - LOOKATME - can the amode only be AM_NONREG_OFS here?
 if (def_ip->opcod == I_CALL_ASLPROC || def_ip->opcod == I_CALL_ASLFUNC)
  {
   valp[0] = def_ip->optu.fudp->ip_trk_valp[wdisp - tn_idp_base]; 
  }
 else
  {
   /* SJM 07-25-07 - know non wrappers always one word insns - wdisp from */
   /* amode (<nva_ofs>(%esi)?) offset in tn may be non 0 but valp always 0 */
   valp[0] = def_ip->optu.fudp->ip_trk_valp[0]; 
  }
 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout,
    "++ SRC con (FROM B%d:%d) - r%d FROM KILL INSN %d - wrd val %x\n",
    __cur_bbp->bblk_seqno, ip->ndx, use_tni, def_ip->ndx, valp[0]);
  }
 /* --- */
 return(TRK_CON);
}

/*
 * get wide asl wrapper insn tracked val state - set per wrod tracked state
 * and return T if all tracked values are the same, else FALSE
 *
 * if all tracked values the same just fills 0th passed trk val state vector 
 *
 * this is passed the ASL wrapper arg src defip array (one defip for each
 * word (commonly most will be repeated) - need to compute right value
 * using both amode disp and word in the wide tn if it is wide and also
 * assign to right word of the wide valp
 *
 * there is one tracked state for every word of arg
 */
static int32 get_asl_wide_trk_val(struct insn_t *ip, struct amode_t *amp,
 int32 argwlen, struct insn_t **def_ip_vec, int32 *trk_state_vec, word32 *valp)
{
 int32 ai;
 int32 trk_state_all_same, use_tni, wdisp, defip_ai, tn_idp_base;
 word32 abvec[2], *convalp;
 struct insn_t *def_ip, *last_def_ip; 

 use_tni = xget_tnreg(amp);
 /* case 1: asl arg is a constant - easy get tracked value - know every */
 /* insn word def ip element the same */ 
 if (__is_constant(use_tni))
  {
   /* SJM 04/30/07 - for conadr need to get the disp (offset in contab) */
   /* from amode so get b parts of contabs when needed */
   convalp = get_tracked_con(use_tni, abvec);
   wdisp = get_amode_wdisp(&(tn_idp_base), ip, amp, &(__tntab[use_tni]));
   /* SJM 06-13-07 - the con is a tn so wdisp needed to get right area */
   /* within the tn's contab area */
   if (wdisp > 0) convalp = &(convalp[wdisp]);

   memcpy(valp, convalp, argwlen*WRDBYTES);
   /* DBG remove -- */
   if (__opt_debug_flg)
    {
     __my_fprintf(stdout,
      "++ SRC con (FROM B%d:%d) - FROM CON r%d asl wide disp %d first val %x\n",
      __cur_bbp->bblk_seqno, ip->ndx, use_tni, wdisp, valp[0]);
    }
   /* --- */
   trk_state_vec[0] = TRK_CON;
   return(TRUE);
  }

 def_ip = def_ip_vec[0]; 
 trk_state_all_same = TRUE;
 for (ai = 1; ai < argwlen; ai++)
  {
   if (def_ip_vec[ai] != def_ip)
    { trk_state_all_same = FALSE; goto not_same_skip; }
  }
 trk_state_all_same = TRUE;

not_same_skip:
 if (trk_state_all_same)
  {
   /* case 2: arg is a tn used wide where def ip set it all at once */ 
   /* SJM 06-13-07 - think can only happen if asl wide changed all */
   def_ip = def_ip_vec[0]; 
   if (def_ip == NULL)
    {
     /* case 2a: use before def (probably set in other flowg?) */
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "++ SRC bottom varying (FROM B%d:%d) - r%d ASL WIDE 1 INSN USE BEFORE DEF\n",
       __cur_bbp->bblk_seqno, ip->ndx, use_tni);
      }
     /* --- */
     trk_state_vec[0] = TRK_BOT_VARYING;
     return(TRUE);
    }
   /* only reg that is used wide tn on ebp stack possible */
   /* DBG remove -- */
   if (def_ip->symb_res_val == TRK_TOP_UNDEF) __misc_terr(__FILE__, __LINE__);
   /* ---- */ 
   /* notice no wdisp needed here since it must be zero */
   /* tracked output state of the uses defining insn known */
   if (def_ip->symb_res_val == TRK_BOT_VARYING)
    {
     /* case 2b: defining insn def (output) not tracked */
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "++ SRC bottom varying (FROM B%d:%d) - r%d FROM ASL WIDE 1 INSN DEF INSN %d\n",
        __cur_bbp->bblk_seqno, ip->ndx, use_tni, def_ip->ndx);
      }
     /* --- */
     trk_state_vec[0] = TRK_BOT_VARYING;
     return(TRUE);
    } 
   /* case 2c: defining insn def (output) killing parent tracked */
   /* DBG remove -- */
   if (def_ip->symb_res_val != TRK_CON) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   for (ai = 0; ai < argwlen; ai++)
    {
     valp[ai] = def_ip->optu.fudp->ip_trk_valp[ai];
    }
   trk_state_vec[0] = TRK_CON;
   return(TRUE);
  }
 /* case 3: various insns */
 /* SJM 06-10-07 LOOKATME - since copy decomposed will see here but might */
 /* have just been one copy from a wide on ebp stack tn */

 wdisp = get_amode_wdisp(&(tn_idp_base), ip, amp, &(__tntab[use_tni]));
 last_def_ip = NULL;
// ===> what is als trk wi
 defip_ai = 0;
 for (ai = 0; ai < argwlen; ai++)
  {
   /* case 3: arg is a tn used wide with more than one def ips */
   /* decomposed copies will be here */
   def_ip = def_ip_vec[ai];
   if (def_ip != last_def_ip) { defip_ai = 0; last_def_ip = def_ip; }
   /* DBG remove -- */
   else
    {
     if (def_ip != NULL && def_ip->opcod != I_CALL_ASLPROC
      && def_ip->opcod != I_CALL_ASLFUNC) __misc_terr(__FILE__, __LINE__);
     defip_ai++;
    }
   /* --- */
   if (def_ip == NULL)
    {
     /* case 3a: use before def (probably set in other flowg?) */
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "++ SRC bottom varying (FROM B%d:%d) - r%d ASL WIDE USE BEFORE DEF\n",
        __cur_bbp->bblk_seqno, ip->ndx, use_tni);
      }
     /* --- */
     /* SJM 06-13-07 - trk state matches def insn result */
     trk_state_vec[ai] = TRK_BOT_VARYING;
     continue;
    }
   /* DBG remove -- */
   if (def_ip->symb_res_val == TRK_TOP_UNDEF) __misc_terr(__FILE__, __LINE__);
   /* ---- */ 

   /* tracked output state of the uses defining insn known */
   if (def_ip->symb_res_val == TRK_BOT_VARYING)
    {
     /* case 3b: defining insn def (output) not tracked */
     /* DBG remove -- */
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout,
        "++ SRC bottom varying (FROM B%d:%d) - r%d FROM ASL WIDE DEF INSN %d\n",
        __cur_bbp->bblk_seqno, ip->ndx, use_tni, def_ip->ndx);
      }
     /* --- */
     /* SJM 06-13-07 - trk state matches def insn result */
     trk_state_vec[ai] = TRK_BOT_VARYING;
     continue;
    } 
   /* case 3c: defining insn def (output) killing parent tracked */
   /* DBG remove -- */
   if (def_ip->symb_res_val != TRK_CON) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   /* define insn has already subtracted out insn displacement */
   /* but valp corresponds to the tn not the insn result */
   valp[ai] = def_ip->optu.fudp->ip_trk_valp[defip_ai]; 
   /* SJM 06-13-07 - trk state matches def insn result */
   trk_state_vec[ai] = TRK_CON;
  }
 return(FALSE);
}

/*
 * optimize (simplify and/or remove) insns with TRK CON symbolic results
 *
 * if any flow graph block struct change, must remove all deflst insns
 */
static void optimize_1fg_symbolic_con_out_insns(struct flowg_t *fgp)
{
 int32 blki, can_rm, cint_ti;
 int32 num_rm, num_chg;
 word32 trkval;
 struct insn_t *ip, *ip2;
 struct insn_t *jmp_ip, *cmp_ip, *ip3;
 struct bblk_t *bbp, *jmpto_bbp, *unreach_bbp;
 struct insn_info_t *iip;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   /* need cur bbp for linking out insns */
   __cur_bbp = bbp;
  
   num_rm = num_chg = 0;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     iip = __to_iinfo_rec(ip->opcod);

     if (ip->symb_res_val != TRK_CON)
      {
       if (iip->iclass == ICLASS_BIN || iip->iclass == ICLASS_SHFT
        || iip->iclass == ICLASS_DIV)
        {
         if (!__is_constant(ip->isrc.am_tni))
          {
           /* SJM - 03/17/07 - for NLO and other read only may need to mult */
           if (tn_valtrk_invisible(ip->isrc.am_tni)) continue;

           /* src may be tracked but not const, convert to cint here */
           if (ip->optu.fudp != NULL) ip3 = ip->optu.fudp->isrc_defip;
           else ip3 = NULL;
           if (ip3 != NULL && ip3->symb_res_val == TRK_CON)
            {
             fix_binop_trk_opand(ip, TRUE);
             num_chg++;
            }
          }
         if (!__is_constant(ip->idst.am_tni))
          {
           /* DBG remove -- */
           /* SJM - 03/17/07 - for NLO and other read only may need to mult */
           if (tn_valtrk_invisible(ip->idst.am_tni)) continue;
           /* --- */

           if (ip->optu.fudp != NULL) ip3 = ip->optu.fudp->idst_defip;
           else ip3 = NULL;
           if (ip3 != NULL && ip3->symb_res_val == TRK_CON)
            {
             fix_binop_trk_opand(ip, FALSE);
             num_chg++;
            }
          }
        }
       continue;
      }

     /* unneeded sete marked as tracked con and just removed */
     if (ip->opcod == I_SETE) 
      {
       ip->trk_later_del = TRUE;
       num_rm++;
       continue;
      }
 
     if (iip->iclass == ICLASS_BIN || iip->iclass == ICLASS_SHFT
      || iip->iclass == ICLASS_UN || iip->iclass == ICLASS_DIV)
      {
       /* SJM 03/26/07 - binary may have const operators but res tni */
       /* must stay */
       if (!can_rm_trk_insn(ip->res_tni))
        {
         ip->opcod = I_MOVA;
         trkval = ip->optu.fudp->ip_trk_valp[0];
         cint_ti = __gen_cint_tn(trkval);
        
         /* SJM 04/05/07 - when change to cint, must init amode and make reg */
         __init_amode(&(ip->isrc));
         ip->isrc.amode = AM_REG;
         ip->isrc.am_tni = cint_ti; 

         __init_amode(&(ip->idst));
         ip->idst.amode = AM_NONE;
         continue;
        }
       /* DBG remove -- */
       if (__opt_debug_flg)
        {
         __my_fprintf(stdout,
          "++ DEL B%d:%d: binary op insn - tracked result r%d value %d\n",
          __cur_bbp->bblk_seqno, ip->ndx, ip->res_tni, dbg_get_trk_ipval(ip));
        }
       /* --- */
       num_rm++;
       ip->trk_later_del = TRUE;
       continue;
      }
     if (iip->iclass == ICLASS_MOV || iip->iclass == ICLASS_STORE)
      {
       if (iip->iclass == ICLASS_STORE)
        {
         can_rm = can_rm_trk_insn(xget_tnreg(&(ip->idst)));
        }
       else can_rm = can_rm_trk_insn(ip->res_tni); 

       if (can_rm)
        {
         /* DBG remove -- */
         if (__opt_debug_flg)
          {
           int32 tni;

           if (iip->iclass == ICLASS_STORE) tni = ip->idst.am_tni;
           else tni = ip->res_tni;
           __my_fprintf(stdout,
            "++ DEL B%d:%d: mov/store insn - tracked result r%d %d\n",
            __cur_bbp->bblk_seqno, ip->ndx, tni, dbg_get_trk_ipval(ip));
          }
         /* --- */
         num_rm++;
         ip->trk_later_del = TRUE;
        }
       else if (!__is_constant(ip->isrc.am_tni))
        {
         /* DBG remove -- */
         if (tn_valtrk_invisible(ip->isrc.am_tni))
          __misc_terr(__FILE__, __LINE__);
         /* --- */

         /* for store to mem label (usually netbp) - replace src amode with */
         /* store of cint AM REG */
         trkval = ip->optu.fudp->ip_trk_valp[0];
         cint_ti = __gen_cint_tn(trkval);
         /* DBG remove --- */
         if (ip->isrc.amode != AM_REG && ip->isrc.amode != AM_NDXREG
          && ip->isrc.amode != AM_NDXREG_DISP)
          __misc_terr(__FILE__, __LINE__); 
         /* --- */
         /* DBG remove -- */
         if (__opt_debug_flg)
          {
           __my_fprintf(stdout,
            "++ CHG B%d:%d: mov/store src amode to cint %d\n",
            __cur_bbp->bblk_seqno, ip->ndx, trkval);
          }
         /* --- */
         num_chg++;
         /* SJM 04/05/07 - when change to cint, must init amode and make reg */
         __init_amode(&(ip->isrc));
         ip->isrc.amode = AM_REG;
         ip->isrc.am_tni = cint_ti;
        }
       continue;
      }
     /* SJM 03/16/07 - copy can't exist here */
     if (ip->opcod == I_COPY) __misc_terr(__FILE__, __LINE__);
     /* --- */
     if (iip->iclass == ICLASS_CMP) 
      {
       cmp_ip = ip;
       jmp_ip = ip->inxt;

       /* both testl and cmp processed same here */
       /* isnsn tracked value is T/F (0 non 0 value for testl) */
       trkval = ip->optu.fudp->ip_trk_valp[0];
       /* DBG remove -- */ 
       if (trkval != 0 && trkval != 1) __misc_terr(__FILE__, __LINE__);
       /* --- */
       /* SJM 04/28/07 - cmp versus test was inconsistent - T condition */
       /* not always set tracked value as 1 so first label bbp selected */
       /* T (1) is jump takes label 1 and F (0) is jump takes label 2 */ 
       if (trkval == 1) 
        { 
         jmpto_bbp = jmp_ip->isrc.apu.bbp; 
         unreach_bbp = jmp_ip->idst.apu.bbp; 
        }
       else 
        { 
         jmpto_bbp = jmp_ip->idst.apu.bbp; 
         unreach_bbp = jmp_ip->isrc.apu.bbp; 
        }

       /* remove the current block from the unreachable bblk back edge list */
       /* SJM 12/05/06 - args were backwards - bbp is jmp from- unreachable */
       /* is jump to whose back edge is removed */
       rm_one_bbedge(bbp, unreach_bbp);

       /* DBG remove -- */
       if (__opt_debug_flg)
        {
         char s1[RECLEN];

         if (ip->opcod == I_TESTL) strcpy(s1, "testl");
         else strcpy(s1, "cmp");
         __my_fprintf(stdout,
          "++ CHG B%d:%d: del %s and change cond jmp to uncond jmp\n",
          __cur_bbp->bblk_seqno, ip->ndx, s1);
        }
       /* --- */

       num_rm++;
       /* can always free the compare insn */
       cmp_ip->trk_later_del = TRUE;

       /* convert to the uncond jump */
       jmp_ip->opcod = I_BBLK_JMP;
       jmp_ip->jmptyp = CC_NONE;
       num_chg++;

       __init_amode(&(jmp_ip->isrc));
       /* SJM 01/17/07 - must always set amode after calling init amode */
       jmp_ip->isrc.amode = AM_NONE;
       jmp_ip->idst.apu.bbp = jmpto_bbp;
      }
     if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
      {
       /* must handle asl wrappers that return an int as special case */
       /* returns T and marks for later del if this asl wrapper return int */
       if (is_int_returning_asl(ip))
        {
         num_rm++;
         ip->trk_later_del = TRUE;
        }
       else
        {
         /* know asl is trk constant so can simplify */
         /* for wide cmps, won't get here because must remove and fix testl */
         replace_asl_with_copy_insn(ip, ip->optu.fudp->ip_trk_valp,
          ip->optu.fudp->trk_nbytes);
         num_chg++;
        }
      }
    }
   /* DBG remove -- */
   if (__opt_trk_verbose && (num_rm > 0 || num_chg > 0))
    {
     int32 bblk_i_num;

     bblk_i_num = cnt_bblk_insns(__cur_bbp);
     __my_fprintf(stdout,
      "STATS B%d: removed %d insns and changed %d of bblk %d insns\n",
      __cur_bbp->bblk_seqno, num_rm, num_chg, bblk_i_num);
    }
   /* --- */
   __trk_num_insn_removed += num_rm;
   __trk_num_insn_changed += num_chg;
  }
 /* SJM 02/20/07 - FIXME should bld delete list or at least removed if need */
 /* remove all deflst insns and all marked for delete here */
 /* must mark because the tracked insn may have amode replace cint */
 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];

   /* need cur bbp for linking out insns */
   __cur_bbp = bbp;
   for (ip = bbp->ihd->inxt; ip != NULL; ip = ip2) 
    {
     ip2 = ip->inxt;
     if (ip->opcod == I_DEFLST || ip->trk_later_del)
      {
       __linkout_insn(ip, TRUE);
      }
    }
  }
 __cur_bbp = NULL;
}

/*
 * special case for asl wrappers that return int (goes into eax)
 *
 * no ip is an asl routine or will not be called
 */
static int32 is_int_returning_asl(struct insn_t *ip)
{
 int32 retwlen, opand_bytsiz;
 struct asl_info_t *aslp;

 aslp = __to_aslinfo_rec(ip->idst.disp);
 if (aslp->asl_ret_typ == RE_VOID) return(FALSE);  
 /* know the result into copied into eax */
 /* DBG remove -- */
 { 
  int32 ai;

  retwlen = __get_asl_insn_retsiz(ip, &opand_bytsiz);
  if (retwlen != 1) __misc_terr(__FILE__, __LINE__);
  for (ai = 0; ai < ip->callasl_argnum; ai++)
   {
    if (aslp->asl_op_typ[ai] == A_WPTR ||
     aslp->asl_op_typ[ai] == A_RWPTR) __misc_terr(__FILE__, __LINE__);
   }
 } 
 /* --- */
 return(TRUE); 
}

/*
 * replace a asl wrapper with an expanded copy (needed since tn used wide)
 *
 * insert a copy, delete the original asl insn and then in place expand
 *
 * know can always convert the asl call to an expanded copy, i.e. can't
 * delete but can simplify
 */
static void replace_asl_with_copy_insn(struct insn_t *asl_ip,
 word32 *res_valp, int32 ret_nbytes)
{
 int32 ctab_ndx, conadr_ti, wlen; 
 word32 *zero_valp;
 struct insn_t *cp_ip;
 struct asl_def_t *aslap;

 /* insert after */
 cp_ip = __insert_insn(asl_ip, TRUE, I_COPY, AM_NONE, AM_NONE);
 cp_ip->is_store = TRUE;

 zero_valp = alloca(ret_nbytes);
 memset(zero_valp, 0, ret_nbytes);
 wlen = (ret_nbytes + (WRDBYTES - 1))/WRDBYTES;
 ctab_ndx = __allocfill_cval_new(res_valp, zero_valp, ret_nbytes*WRDBYTES);
 /* SJM 07-11-07 - always treating this as signed - is that right? */
 conadr_ti = __gen_contab_tn(ctab_ndx, wlen*WBITS, FALSE, TRUE, FALSE, SR_VEC);

 cp_ip->isrc.amode = AM_REG;
 cp_ip->isrc.am_tni = conadr_ti;
 cp_ip->isrc.disp = wlen*WRDBYTES;

 aslap = &(asl_ip->extrau.asl_ausedefs[0]);
 /* DBG remove -- */
 if (aslap->am_arg.amode != AM_REG) __misc_terr(__FILE__, __LINE__);
 /* --- */
 cp_ip->idst.amode = AM_REG;
 cp_ip->idst.am_tni = aslap->am_arg.am_tni;

 /* now remove the asl insn */
 __linkout_insn(asl_ip, TRUE);

 /* final step is decomposing the copy to movl's if possible */
 __expand_copy(cp_ip);
}

/*
 * get insn tracked value - for debugging 
 *
 * always one word for now - wdisp used for getting right decomposed  
 * insn but at least for now (no asl wrapper tracking) value one word
 */
static int32 dbg_get_trk_ipval(struct insn_t *ip)
{
 int32 trkval; 

 /* DBG remove -- */
 if (ip->optu.fudp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 trkval = (int32) ip->optu.fudp->ip_trk_valp[0];
 return(trkval);
}

/*
 * routine to replace tracked binary insn src/dst with cint tn
 */
static void fix_binop_trk_opand(struct insn_t *ip, int32 is_src)
{
 int32 trkval, cint_ti;
 struct amode_t *amp;

 if (is_src)
  {
   amp = &(ip->isrc);
   trkval = ip->optu.fudp->isrc_defip->optu.fudp->ip_trk_valp[0];
  }
 else
  {
   amp = &(ip->idst);
   trkval = ip->optu.fudp->idst_defip->optu.fudp->ip_trk_valp[0];
  }
 cint_ti = __gen_cint_tn(trkval);
 /* DBG remove -- */
 if (amp->amode != AM_REG && amp->amode != AM_NDXREG
  && amp->amode != AM_NDXREG_DISP && amp->amode != AM_NONREG_OFS)
  __misc_terr(__FILE__, __LINE__); 
 /* --- */
 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "++ CHG B%d:%d: binary amode to cint %d\n",
    __cur_bbp->bblk_seqno, ip->ndx, trkval);
  }
 /* --- */
 __init_amode(amp);
 amp->amode = AM_REG;
 amp->am_tni = cint_ti; 
}

/*
 * VARIOUS LOW LEVEL MEM LABEL CLASSIFICATION ROUTINES
 */

/*
 * return T if tn is trackable - anything but constants or non value addrs
 *
 * SJM 01/02/07 - not sure which are trackable - XMR's too?
 * maybe should try to track IS form conadr's 
 */
static int32 tn_is_trackable(int32 tni)
{
 struct tn_t *tnp;

 tnp = &(__tntab[tni]);
 if (tnp->comlab_typ == COMLAB_NONE) return(TRUE);
 switch (tnp->comlab_typ) {
  case COMLAB_CINT: case COMLAB_STMT: case COMLAB_XPR: case COMLAB_GREF:
  case COMLAB_GATE: case COMLAB_CA: case COMLAB_CONADR: case COMLAB_L_UDPADR:
  case COMLAB_E_UDPADR: case COMLAB_TCHK: case COMLAB_DEL:
   return(FALSE);
  default: break;
 } 
 return(TRUE);
}

/*
 * return T if destination tni (only parents can be passed) is a mem label
 */
static int32 can_rm_trk_insn(int32 dtni)
{
 struct tn_t *tnp;
 
 tnp = &(__tntab[dtni]);
 /* DBG remove -- */
 if (tnp->tag_parent_tni != -1) __misc_terr(__FILE__, __LINE__); 
 /* --- */

 /* SJM 04/28/07 - if used wide can never be removed because the movl's */
 /* that initialize the ebp stack must not be removed */
 if (tnp->tn_used_wide) 
  {
   if (tnp->bb_use_tree != NULL) return(FALSE);
  }

 /* SJM 01/17/07 - if tn is a deflst join entry varying tn, can't remove */ 
 if (tnp->res_tn_useistays) return(FALSE);

 /* must leave insn if destination is a mem addr */
 if (__is_mem_label(dtni))
  {
   /* DBG remove --- */
   if (!__is_mem_label(dtni)) __misc_terr(__FILE__, __LINE__);
   if (!__canbe_dst_mem_label(dtni)) __misc_terr(__FILE__, __LINE__);
   /* --- */
   return(FALSE);
  }
 return(TRUE);
}

/*
 * FINAL STEP PEEP HOLE OPTIMIZATION - CAN ONLY REARRANGE INSNS HERE
 */

/*
 * removed unneeded x86 machine insns from no effect x86 reg usage
 */
static void remove_unneeded_machreg_insns(struct flowg_t *fgp,
 struct mod_t *mdp)
{
 int32 blki, rno;
 struct bblk_t *bbp;
 struct insn_t *ip, *ip2;
 struct iusedef_t *fudp;

 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "AFTER UNNEDED insn removed\n");
   __dmp_flowg_insns(fgp, mdp);
  }
 /* --- */

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   /* SJM 12/03/06 - block may already have been removed */
   if (bbp == NULL) continue; 

   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     /* case 1: x86 reg defined as dest in flow graph but never used */
     rno = ip->idst.x86_regno; 
     if (rno != -1 && rno <= HIGH_GEN_REG)
      {
       if (__get_avlnode(bbp, __tntab[rno].bb_def_tree) != NULL)
        {
         if (__get_avlnode(bbp, __tntab[rno].bb_use_tree) == NULL)
          {
           if (__opt_debug_flg)
            {
             __my_fprintf(stdout, "++ removed B%d;%d defined but never used\n",
              __cur_bbp->bblk_seqno, ip->ndx); 
            }
           __linkout_insn(ip, TRUE);
           continue;
          }
        }
      }
     /* case 2: x86 reg used as src in flow graph but no define */
     rno = ip->isrc.x86_regno; 
     if (rno != -1 && rno <= HIGH_GEN_REG)
      {
       if (__get_avlnode(bbp, __tntab[rno].bb_use_tree) != NULL)
        {
         fudp = ip->optu.fudp;
         if (fudp->isrc_defip == NULL) 
          {
           if (__opt_debug_flg)
            {
             __my_fprintf(stdout, "++ removed B%d;%d used but never defined\n",
              __cur_bbp->bblk_seqno, ip->ndx); 
            }
           __linkout_insn(ip, TRUE);
           continue;
          }
        }
      }
    }
  }
 __cur_bbp = NULL;
}

/*
 * routine to get tracked val for constant
 *
 * 04/30/07 - this returns base of contab area - caller may use amode disp
 * to get right word of conadr
 */
static word32 *get_tracked_con(int32 tni, word32 *wrdwrkp)
{
 int32 xvi;
 word32 *valp;
 struct tn_t *tnp;

 /* case 1: src value is a constant - constants always tracked */
 tnp = &(__tntab[tni]);
 if (tnp->comlab_typ == COMLAB_CINT)
  {
   wrdwrkp[0] = tnp->tncu.tn_cint;
   wrdwrkp[1] = 0;
   valp = &(wrdwrkp[0]);
  }
 else
  {
   /* if this is a child of a parent contab entry, xvi corrected */
   xvi = __get_con_adradd_xvi(tni);
   valp = &(__contab[xvi]);
  }
 return(valp);
}

#endif // __VALTRK__ 

/*
 * add the tn to one flow graph' tn used in flow graph avl tree (set)
 *
 * ref (reference) means either use (non killing access) or define (def) 
 * that kills the tn
 * 
 * caller must select which tn's are added (such as parent or children etc.)
 */
extern void __tryadd_tn_use_in_fg(struct flowg_t *fgp, int32 tni)
{
 struct tn_dup_t *tndup;

 if (fgp->fg_tn_ref_tree == NULL) fgp->fg_tn_ref_tree = __allocinit_avlhd();

 tndup = __find_add_dup_tn(fgp->fg_tn_ref_tree, tni);
 /* case 1: found dup - nothing to add */
 if (!__avl_node_is_new) return;
 tndup->tni = tni;
}


/*
 * return T for mem labels that can be destinations of copies
 */
extern int32 __canbe_dst_mem_label(int32 par_tni)
{
 struct tn_t *par_tnp;

 par_tnp = &(__tntab[par_tni]);
 switch (par_tnp->comlab_typ)  {
  case COMLAB_DCESCH_TEVS: case COMLAB_IDP: case COMLAB_IDPDAT:
   break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * ROUTINES TO EXPAND MEDIUM LEVEL INSNS AND TRY TO EXPAND WIDE TNS
 */

/*
 * lower original bbgen flowg insns to machine level two address with
 * medium level insns expaned and decomposed when possible
 *
 * these routines do not use bblk structural information but instead
 * use local insn info or build their own data structures
 */
static void lower_insns_to_mach_level(struct flowg_t *fgp, struct mod_t *mdp)
{
 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "BEFORE copy expand\n");
   __dmp_flowg_insns(fgp, mdp);
  }
 /* --- */

 /* expand copies to machine width tn moves */ 
 expand_fg_copies(fgp);

 /* SJM 03/15/07 - put back if want to be able to find bblk from insn ndx */
 // PUTMEBACK FOR DEBUGGING - __renumber_fg_insns(fgp);

 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "BEFORE wide tn decomposition\n");
   __dmp_flowg_insns(fgp, mdp);
  }
 /* --- */

 /* optimize by replacing wide tns by decomposed machine wrd tns if possible */
 decompose_fg_non_leal_wide_amode_tns(fgp);
}

/*
 * expand all the I_COPY instructions to it's lowered equiv
 * in one flow graph
 *
 * SJM 08/08/06 - idea for expanding copies after insn gen is that
 * the value numbers may get rid of entire wide copies - must be
 * done before bb opt processing since need information (live-dead
 * intervals for example) about thenew tn's created in the lowering
 */
static void expand_fg_copies(struct flowg_t *fgp)
{
 struct insn_t *ip, *ip2;
 struct bblk_t *bbp;

 /* notice the RPO bblk tab not built yet */
 __cur_flowg = fgp;
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp; 
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     if (ip->opcod != I_COPY) continue;

     __expand_copy(ip);
    }
  }
 __cur_bbp = NULL; 
}

/*
 * for every reg unkn (wide?) tn that is not the src operand of a leal 
 * anywhere - decompose the tn into per machine word tns and fixup every
 * amode that uses the reg unkn tn
 *
 * notice must do entire flow graph after copy lowering because copy
 * lowering can generate leals of any wide tn
 */
static void decompose_fg_non_leal_wide_amode_tns(struct flowg_t *fgp)
{
 struct insn_t *ip;
 struct bblk_t *bbp;
 struct amode_t tmpamode;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp; 
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     /* AIV 10/30/06 - need to change operands to calls to be new decomp */
     /* tni changes the arguments to new narrow arg */
     if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
      {
       try_replace_amode_call_wide_tn(ip);
       continue;
      }
     if (ip->isrc.am_tni != -1) try_replace_amode_wide_tn(&(ip->isrc));
     if (ip->idst.am_tni != -1) try_replace_amode_wide_tn(&(ip->idst));
     if (ip->res_tni != -1)
      {
       __init_amode(&(tmpamode));
       tmpamode.amode = AM_REG;
       tmpamode.am_tni = ip->res_tni;
       tmpamode.disp = 0;
       try_replace_amode_wide_tn(&(tmpamode));
       if (tmpamode.am_tni != ip->res_tni)
        {
         ip->res_tni = tmpamode.am_tni;
        }
      }
    }
  }
 __cur_bbp = NULL; 
}

/*
 * for reg unkn tns that are wide and non real decompose each chunk
 * into machine word tmp names 
 *
 * this assigns the new tns if needed and updates the amode
 */
static void try_replace_amode_wide_tn(struct amode_t *amp)
{
 int32 j, tni, par_tni, wlen, decompose_tni;
 size_t ndx;
 struct tn_t *tnp, *partnp;

 /* is a tmp reg */
 if ((tni = amp->am_tni) == -1) return;

 tnp = &(__tntab[tni]);
 /* DBG remove --- */
 if (tnp->tn_typ == TN_UNKN) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 if (!tmp_is_decomposable(tnp)) return;

 /* DBG remove -- */
 if (amp->am_tni < HIGH_MACH_REG) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 par_tni = __get2_par_tni(tni);
 partnp = &(__tntab[par_tni]); 

 /* if used wide (i.e. operand of load effective addr.), can't decompose */
 if (partnp->tn_used_wide || partnp->tn_typ != TN_VAL
  || partnp->comlab_typ != COMLAB_NONE) return;

 /* if other adradd not seen to assign the decomposed tns, assign now */
 if (__decomposed_tn_nums[par_tni] == NULL)
  { 
   /*  for each word assign a new register */
   wlen = __get_tn_vec_size(partnp);
  __decomposed_tn_nums[par_tni] = (int32 *) __my_malloc(wlen*sizeof(int32));
   for (j = 0; j < wlen; j++) 
    {
     decompose_tni = __gen_tn(SR_CINT, WBITS);
     __tntab[decompose_tni].tn_typ = TN_VAL;
     /* gen tn can grow tn tab so must use index not par tnp pointer */ 
     __decomposed_tn_nums[par_tni][j] = decompose_tni;
    }
  }
 /* gen tn can be realloc and move tntab so must use base_tni from here */
 /* NOTICE - critical to reassign par tnp */
 /* SJM 10/11/06 - all offsets are in bytes byt ndx is a word index */
 partnp = &(__tntab[par_tni]); 
 /* AIV 11/27/06 - need to reassign tmp in case of realloc as well */
 tnp = &(__tntab[tni]);

 /* SJM 10/11/06 - tag inside offset must come from child not parent */ 
 if (tnp->child_tag_offset != 0) ndx = tnp->child_tag_offset;
 else ndx = 0;

 /* DBG remove -- */
 if ((ndx % WRDBYTES) != 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 ndx += amp->disp;

 /* disp is always in bytes but need ndx also in words */
 ndx /= WRDBYTES;

 /* DBG remove -- */
 wlen = __get_tn_vec_size(partnp);
 if (ndx >= wlen) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* convert amode to REG VAL and assign right decomposed tn num */
 amp->amode = AM_REG;
 amp->am_tni = __decomposed_tn_nums[par_tni][ndx];
 amp->disp = 0;
}

/*
 * takes a asl call and checks to see if its arguments were changed to a
 * by decomposing into a new tmp 
 * changes asl call arg use def = new decomposed tmp
 */
static void try_replace_amode_call_wide_tn(struct insn_t *ip)
{
 int32 arg_ti, par_tni, ai, wlen, decompose_tni, i;
 size_t ndx;
 struct tn_t *arg_tnp, *partnp;
 struct asl_def_t *aslap;

 /* check each arg */
 for (ai = 0; ai < ip->callasl_argnum; ai++)
  {
   aslap = &(ip->extrau.asl_ausedefs[ai]);
   arg_ti = aslap->am_arg.am_tni;
   arg_tnp = &(__tntab[arg_ti]);

   if (!tmp_is_decomposable(arg_tnp)) continue;

   /* check for a parent */
   par_tni = __get2_par_tni(arg_ti);
   partnp = &(__tntab[par_tni]); 

   if (partnp->tn_used_wide || partnp->tn_typ != TN_VAL
    || partnp->comlab_typ != COMLAB_NONE) continue;
   
   /* AIV 11/28/06 - need to alloc decomposed memory here as well */
   /* may get here prior to amode decomposing of wides */
   /* decomposed */
   wlen = __get_tn_vec_size(partnp);
   if (__decomposed_tn_nums[par_tni] == NULL)
    { 
     /*  for each word assign a new register */
     __decomposed_tn_nums[par_tni] = (int32 *) __my_malloc(wlen*sizeof(int32));
     for (i = 0; i < wlen; i++) 
      {
       decompose_tni = __gen_tn(SR_CINT, WBITS);
       __tntab[decompose_tni].tn_typ = TN_VAL;
       /* gen tn can grow tn tab so must use index not par tnp pointer */ 
       __decomposed_tn_nums[par_tni][i] = decompose_tni;
      }
    }

   /* must reset because __gen_tn may have realloc table */
   partnp = &(__tntab[par_tni]); 
   arg_tnp = &(__tntab[arg_ti]);

   if (arg_tnp->child_tag_offset != 0) ndx = arg_tnp->child_tag_offset;
   else ndx = 0;
   /* DBG remove -- */
   if ((ndx % WRDBYTES) != 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   
   ndx /= WRDBYTES;
   /* DBG remove -- */
   if (ndx >= wlen) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* set the new decomposed value */
   aslap = &(ip->extrau.asl_ausedefs[ai]);
   aslap->am_arg.am_tni = __decomposed_tn_nums[par_tni][ndx];
  }
}

/*
 * return T if can decompose tmp value into seperate words
 */
static int32 tmp_is_decomposable(struct tn_t *tnp)
{
 if (tnp->t_real) return(FALSE);

 /* AIV 08/25/08 - if tmp is scalar do not decompose */
 /* was working for vector put no need to decompose */
 switch (tnp->srtyp)
  {
   /* AIV 10/12/06 - cannot decompose strengths or reals into word regs */
   case SR_CINT:
   case SR_SVEC: 
   case SR_SCAL: 
   case SR_SSCAL: 
   case SR_SCAL2S: 
    return(FALSE);
  }
 return(TRUE);
}

/*
 * routine to remove all children tn's by replacing with ndx reg disp  
 * for one flow graph
 */
static void replace_child_tns(struct flowg_t *fgp)
{
 int32 ai;
 struct insn_t *ip;
 struct bblk_t *bbp;
 struct asl_def_t *aslap;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp; 
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     /* DBG remove -- */
     if (ip->opcod == I_COPY) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* SJM 03/16/07 - not changing asl child tns? */
     if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
      {
       for (ai = 0; ai < ip->callasl_argnum; ai++) 
        {
         aslap = &(ip->extrau.asl_ausedefs[ai]);
         /* DBG remove -- */
         if (aslap->am_arg.am_tni == -1) __misc_terr(__FILE__, __LINE__);
         /* --- */
         try_replace_amode_child_tn(&(aslap->am_arg));
        }
       continue;
      }

     if (ip->isrc.am_tni != -1) try_replace_amode_child_tn(&(ip->isrc));
     if (ip->idst.am_tni != -1) try_replace_amode_child_tn(&(ip->idst));

     /* SJM 03/16/07 - result tn's can't be ndx reg disp insns */
     /* DBG remove -- */
     if (ip->res_tni != -1)
      {
       if (__tntab[ip->res_tni].child_tag_offset != 0) 
        __misc_terr(__FILE__, __LINE__);
      }
     /* --- */
    }
  }
 __cur_bbp = NULL; 
}

/*
 * try to replace one amode child tn - does nothing unless tn is a child
 */
static void try_replace_amode_child_tn(struct amode_t *amp)
{
 int32 tni, par_tni;

 tni = amp->am_tni;
 par_tni = __tntab[tni].tag_parent_tni;
 if (par_tni == -1) return; 

 switch (amp->amode) {
  case AM_REG:
   /* SJM 03/26/07 - for anding b part high words, can be reg not index reg */
   /* SJM 04/03/07 - if netbp type thing or conadr, convert to ndx reg disp */
   /* AIV 09/26/07 - net change don't need to convert and address contains */
   /* the address value */
   if ((__canbe_dst_mem_label(par_tni)
    || __tntab[par_tni].comlab_typ == COMLAB_CONADR)
    && __tntab[tni].idp_typ != COMLAB_PNCHG
    && __tntab[tni].idp_typ != COMLAB_TEVP
    && __tntab[tni].idp_typ != COMLAB_TASK_ADR)
    { 
     amp->amode = AM_IDP_ADR_OFS;
     amp->am_tni = par_tni;
     amp->disp = __tntab[tni].child_tag_offset;
    }
   else
    {
     amp->amode = AM_NONREG_OFS;
     amp->am_tni = par_tni;
     amp->disp = __tntab[tni].child_tag_offset;
    }
   break;
  case AM_NDXREG: 
   /* SJM 03/16/07 - is it true child tn's will always be ndx regs? */
   amp->amode = AM_NDXREG_DISP;
   amp->am_tni = par_tni;
   amp->disp = __tntab[tni].child_tag_offset;
   break;
  case AM_NDXREG_DISP:
//AIV FIXME? - ndx 234 tn 101 in prtcnbg01.v SHOULD THIS BE NDXREG
   /* SJM 03/26/07 - for anding b part high words, has ndx reg disp 0 - why */
   amp->am_tni = par_tni;
   amp->disp = amp->disp + __tntab[tni].child_tag_offset;
   break;
  case AM_NONREG_OFS:
   amp->am_tni = par_tni;
   amp->disp += __tntab[tni].child_tag_offset;
   break;
  case AM_NLO_ARRNDX:
   __misc_terr(__FILE__, __LINE__);
   break;
  case AM_LABEL: case AM_BBLK: case AM_NLO:
   break;
  default: __case_terr(__FILE__, __LINE__);
 } 
}

/*
 * ROUTINES TO CONVERT 3 OP FLOW GRAPH INSNS TO X86 SRC-DST 2 OP
 */

/*
 * convert one flow graph's 3 addr <op1>,<op2> => <res_tni> virtual machine 
 * instructions to X86 src,dst 2 op insns
 *
 * for now need to do this before register assignment and spilling but
 * should move to final convert to particular machine asm link
 *
 * SJM 08/18/06 - need routine to insert copies when dst and res_tni not
 * same
 */
static void convert_to_2op_insn(struct flowg_t *fgp, struct mod_t *mdp)
{
 struct insn_t *ip, *ip2, *ip3;
 struct bblk_t *bbp;

 ip3 = NULL;
 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "BEFORE convert to 2 op X86 insns\n");
   __dmp_flowg_insns(fgp, mdp);
  }
 /* --- */

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     /* AIV 10/31/07 - the next insn may now be linked out */
     if (ip2 != NULL) ip3 = ip2->inxt;
     if (convert_insn_to_2op(ip))
      {
       ip2 = ip3;
      }
    }
  }
 __cur_bbp = NULL;
}

/*
 * convert one insn from X86 <src>,<dst> => <dst> format to <src>, <dst>
 */
static int32 convert_insn_to_2op(struct insn_t *ip)
{
 struct amode_t *dstp, *srcp, *movep;
 word32 aval;
 int32 res_tni;
 struct amode_t tmpamp;
 struct insn_t *nextip;
 struct insn_info_t *iip;

 /* don't need to do anything with the store insn */
 if (ip->is_store) return(FALSE);

 iip = __to_iinfo_rec(ip->opcod);
 dstp = &(ip->idst);
 srcp = &(ip->isrc);
 res_tni = ip->res_tni;
 if (iip->iclass == ICLASS_MOV)
  {
   /* DBG remove -- */
   if (dstp->amode != AM_NONE) __misc_terr(__FILE__, __LINE__);
   if (res_tni == -1) __misc_terr(__FILE__, __LINE__);
   /* --- */
   dstp->amode = AM_REG;
   dstp->am_tni = res_tni;
   ip->res_tni = -1;
  }
 else if (iip->iclass == ICLASS_BIN)
  {
   /* DBG remove -- */
   if (res_tni == -1) __misc_terr(__FILE__, __LINE__);
   if (dstp->amode == AM_NONE) __misc_terr(__FILE__, __LINE__);
   /* --- */
   nextip = ip->inxt;
   /* AIV 10/31/07 - handle the case where the next insn stores into itself */
   /* movl	__slotend_action, %eax */
   /* orl	$0x4, %eax */
   /*  movl	%eax, __slotend_action */

   /* => instead linkout next store ins */
   /* orl	$0x4, __slotend_action */
   if (nextip != NULL && nextip->is_store && 
       nextip->isrc.am_tni == ip->res_tni && 
       nextip->idst.am_tni == dstp->am_tni)
    {
     __linkout_insn(nextip, TRUE);
     ip->res_tni = -1;
     return(TRUE);
    }
   /* AIV LOOKATME - this can't always be a movl can it ????????? */
   /* addl %r1, %r2 => %r3 */ 
   /*   => movl %r1, %r3 */ 
   /*   => addl %r2, %r3 */ 
   /* if commutative insns can switch operands */
   if (is_commutative_insn(ip->opcod))
    {
     /* SJM 08/02/08 - now can have label in addl but only first arg */
     if (srcp->amode == AM_LABEL || __is_constant(srcp->am_tni))
      {
       /* AIV LOOKATME - what about stored into case????? */
       __insert_srcdup_movl(ip, FALSE, dstp, res_tni);
      }
     else if (__is_constant(dstp->am_tni))
      {
       /* AIV 10/31/07 - handle the case where the next insn stores to self */
       /* movl	36(%esi), %eax */
       /* andl	$0xfffffff7, %eax */
       /* movl	%eax, 36(%esi) */

       /* => instead linkout next store ins */
       /* orl	$0x4, __slotend_action */
       if (nextip != NULL && nextip->is_store &&
        nextip->isrc.am_tni == ip->res_tni &&
        (__cmp_amodes(&(nextip->idst), srcp)) == 0) 
        {
         __copy_amode(&(tmpamp), srcp);
         __copy_amode(srcp, dstp);
         __copy_amode(dstp, &(tmpamp));
         __linkout_insn(nextip, TRUE);
         ip->res_tni = -1;
         return(TRUE);
        }
       __insert_srcdup_movl(ip, FALSE, srcp, res_tni);
       __copy_amode(srcp, dstp);
      }
     else 
      {
       /* AIV 10/16/08 - better to do the load of the memory into */
       /* a register first and do the binop that it is to move two */
       /* registers and then do the binop on the memory */
       /* is better */
       /* movl    60(%esi), %edx */
       /* xorl    %eax, %edx */
       /* than */
       /* movl    %eax, %edx */
       /* xorl    60(%esi), %edx */
       /* AIV 01/21/10 - this was true of older processors */
       /* do not find this is the case anymore - new method creates less */
       /* instructions and spills */
       /* AIV 09/07/11 - if large still need to do dst fist the fixup routine */
       /* assumes original style - AIV LOOKATME - maybe change large */
       /* fixup routine ??? */
#ifdef __CVC32__
       movep = srcp;
#else
       if (__cvc_use_large_model) movep = dstp;
       else movep = srcp;
#endif

       if (__amode_mem_ref(movep))
        {
         __insert_srcdup_movl(ip, FALSE, dstp, res_tni);
         __copy_amode(dstp, srcp);
        }
       else
        {
         __insert_srcdup_movl(ip, FALSE, srcp, res_tni);
         __copy_amode(srcp, dstp);
        }
      }
    }
   else
   {
    __insert_srcdup_movl(ip, FALSE, srcp, res_tni);
    __copy_amode(srcp, dstp);
   }
   dstp->amode = AM_REG;
   dstp->am_tni = res_tni;
   ip->res_tni = -1;
  }
 else if (iip->iclass == ICLASS_SHFT)
  {
   /* DBG remove -- */
   if (res_tni == -1) __misc_terr(__FILE__, __LINE__);
   if (dstp->amode == AM_NONE) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (__is_constant(srcp->am_tni))
    {
     /* shrl $2, %r1 => %r3 */ 
     /*   => movl %r1, %r3 */ 
     /*   => shrl $2, %r3 */ 
     __insert_srcdup_movl(ip, FALSE, dstp, res_tni);
     aval = __get_wrd_amode_con_val(srcp);
     /* AIV 01/05/09 - if shift by one just add to itself */
     /* better to do an add then a shift and this case is common */
     /* due to the conversion code */
     /* BEWARE - this code is machine dependent */
     if (aval == 1)
      {
       dstp->amode = AM_REG;
       dstp->am_tni = res_tni;
       /* once mapped turn off all res tnis so will print as 2 opand insns */
       ip->res_tni = -1;
       if (ip->opcod == I_SHLL || ip->opcod == I_SALL) 
        {
         srcp->amode = AM_REG;
         srcp->am_tni = res_tni;
         ip->opcod = I_ADDL;
         return(FALSE);
        }
       /* right shift looks like a unary - uses special insns */
       /* shrl %eax */
       srcp->amode = AM_NONE;
       srcp->am_tni = -1;
       if (ip->opcod == I_SHRL) ip->opcod = I_SHRU;
       else if(ip->opcod == I_SARL) ip->opcod = I_SARU;
       else __case_terr(__FILE__, __LINE__);
       return(FALSE);
      }
     /* SJM 11/13/06 - since shift cnt now in src opand not need amode copy */
    }
   else
    {
     /* shrl %r1, %r2 => %r3 */ 
     /*   => movl %r2, %r3 */ 
     /*   => movl %r1, %ecx */ 
     /*   => shrl %ecx, %r3 */ 
     /* AIV 02/19/09 - set the tmp variable shift flag */
     /* the reg alloc will attempt to use the x86 shift reg for this tmp */
     __tntab[srcp->am_tni].tn_used_var_shift = TRUE;
     __insert_srcdup_movl(ip, FALSE, dstp, res_tni);
     __insert_srcdup_movl(ip, FALSE, srcp, AR_CX);
     srcp->amode = AM_REG;
     srcp->am_tni = AR_CX;
    }
   dstp->amode = AM_REG;
   dstp->am_tni = res_tni;
  }
 else if (iip->iclass == ICLASS_DIV)
  {
   convert_div_insn_to_x86_2op(ip);
  }
 else if (iip->iclass == ICLASS_UN)
  {
   /* DBG remove -- */
   if (res_tni == -1) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* AIV LOOKATME - this can't always be a movl can it ????????? */
   /* negl %r1 => %r2 */ 
   /*   => movl %r1, %r2 */ 
   /*   => addl %r2 */ 
   __insert_srcdup_movl(ip, FALSE, srcp, res_tni);
   srcp->amode = AM_NONE;
   srcp->am_tni = -1;
   dstp->amode = AM_REG;
   dstp->am_tni = res_tni;
  }
 else return(FALSE);
 /* once mapped turn off all res tnis so will print as 2 opand insns */
 ip->res_tni = -1;
 return(FALSE);
}
   
/*
 * return T if insn opcod is commutative
 */
static int32 is_commutative_insn(int32 opcod)
{
 struct insn_info_t *iip;

 /* routine should only be used with binary insn */
 /* not shift are a different class */
 iip = __to_iinfo_rec(opcod);
 /* DBG remove -- */
 if (iip->iclass != ICLASS_BIN) __misc_terr(__FILE__, __LINE__);
 /* --- */
 switch(opcod) {
   case I_SUBL:
   case I_DIVL:
   case I_SGN_DIVL:
   case I_MODL:
   case I_SGN_MODL:
    return(FALSE);
 }
 return(TRUE);
}

/*
 * convert X86 special case div insn (it takes fixed regs) to 2 op form  
 */
static void convert_div_insn_to_x86_2op(struct insn_t *ip)
{
 struct amode_t *dstp, *srcp;
 int32 res_tni, new_ti;

 dstp = &(ip->idst);
 srcp = &(ip->isrc);
 res_tni = ip->res_tni;
 /* DBG remove -- */
 if (res_tni == -1) __misc_terr(__FILE__, __LINE__);
 if (dstp->amode == AM_NONE) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* divl %r1, %r2 => %r3 */ 
 /*   movl %r2 => %newr */ 
 /*   movl %r1 => %eax */ 
 /*   cltd */ 
 /*   divl %newr  */ 
 /*   %eax => %r3 */ 
 new_ti = __gen_tn(SR_CINT, WBITS);
 __tntab[new_ti].tn_typ = TN_VAL;
 __insert_srcdup_movl(ip, FALSE, dstp, new_ti);
 __insert_srcdup_movl(ip, FALSE, srcp, AR_AX);
#ifndef __CVC32__
  /* AIV 11/09/08 - 64-bit y = x/y divide does the following code */
  /*	movq	x(%rip), %rsi */
  /*	movq	%rsi, %rdx */
  /*	movq	%rsi, %rax */
  /*	sarq	$63, %rdx */
  /*	idivq	y(%rip) */
  /*	movq	%rax, y(%rip) */
 __insert_srcdup_movl(ip, FALSE, srcp, AR_DX);
#endif
//AIV FIXME -???????????
// should be using this but uses __cur_bbp - change not to use __cur_bbp???
// __insert_insn(ip, FALSE, I_PUSHL, AM_NONE, AM_REG, ESI);
//AIV FIXME - need to handle special cases for the conflict graph to work
//could just w/r edx/eax to get to work at first
 if (ip->opcod == I_DIVL || ip->opcod == I_MODL)
  {
   /* AIV 10/26/05 - non-signed div only needs to zero %edx */
   /* AIV FIXME -  is this true doing the same now for both */
   __insert_insn(ip, FALSE, I_MOVA, AM_IMM, 0, AM_REG, AR_DX);
  }
 else
  {
#ifdef __CVC32__
   /* note this write to edx */
   __insert_insn(ip, FALSE, I_CLTD, AM_NONE, AM_REG, AR_DX);
#else
   /* AIV 11/09/08  64-bit needs to zero rdx */
   /* AIV FIXME - there are much better ways to do divide see gcc produced */
   /* code for signed and unsigned divide */
   __insert_insn(ip, FALSE, I_SARL, AM_IMM, 63, AM_REG, AR_DX);
#endif
  }
 __insert_insn(ip, FALSE, ip->opcod, AM_NONE, AM_REG, new_ti);

 srcp->amode = AM_REG;
 if (ip->opcod == I_DIVL || ip->opcod == I_SGN_DIVL)
  {
   srcp->am_tni = AR_AX;
  }
 else srcp->am_tni = AR_DX;
 ip->opcod = I_MOVA;
 dstp->amode = AM_REG;
 dstp->am_tni = res_tni;
}

/*
 * ROUTINES TO FIXUP MACHINE INSNS JUST BEFORE EMITTING THE ASM
 */

/*
 * if found any coalescing tns, go through and fixup all uses in amodes
 */
static void fixup_coalesced_away_tns(struct flowg_t *fgp)
{
 int32 blki;
 struct insn_t *ip;
 struct bblk_t *bbp;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   /* SJM 12/03/06 - block may already have been removed */
   if (bbp == NULL) continue; 

   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     if (ip->isrc.amode != AM_NONE && ip->isrc.am_tni != -1)
      {
       if (__tntab[ip->isrc.am_tni].tn_coalesce_into != -1) 
        {
         ip->isrc.am_tni = __tntab[ip->isrc.am_tni].tn_coalesce_into;   
        }
      }
     if (ip->idst.amode != AM_NONE && ip->idst.am_tni != -1)
      {
       if (__tntab[ip->idst.am_tni].tn_coalesce_into != -1) 
        {
         /* SJM 11/10/06 - fixed bug was replacing source not dest */
         ip->idst.am_tni = __tntab[ip->idst.am_tni].tn_coalesce_into;   
        }
      }
    }
  }
}

/*
 * final stage machine insn fixup - mostly gen asl call boiler plate and
 * use ecx to removed any insns with 2 memory refs
 */
static void final_machine_insn_fixup(struct flowg_t *fgp, struct mod_t *mdp)
{
 /* DBG remove -- */
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "BEFORE expand of ASL calls\n");
   __dmp_flowg_insns(fgp, mdp);
  }
 /* --- */

 /* AIV 01/22/09 - swap the condition codes to create fall thrus */
 fixup_reverse_cond_jumps(fgp);


 // SJM PUT BACK TO FOR LESS READABLE ASM
 /* SJM 03/15/07 - remove fall thru jump is not writing .s files */
 if (!__show_asm)
  {
   mark_fallthru_jumps(fgp);
  }

 /* fix the mem2mem overflow - insns illegal for x86 have 2 mem refs */ 
 /* SJM 10/26/06 - now also handles assigning regs to amodes */
 /* because old scheme couldn't handle struct offset ndx reg disps */
 fixup_1fg_2memrefs(fgp);

 /* SJM 11/13/06 - now check for all but ASL operands fit in WBITS */
 /* and all 2 memref insns removed */
 /* DBG remove -- */
 chk_insns_2memrefs(fgp);
 /* -- */
 
 /* build tn sets and def-use chains - for use in peep hole optimization */
 __need_reg_tns = TRUE;
 /* TRK remove */ // bld_1fg_doms_sets_fuds(fgp);
 __need_reg_tns = FALSE;

 /* DBG remove --
 if (__opt_debug_flg)
  {
   __my_fprintf(stdout, "BEFORE peep hole optimization\n");
   dmp_fg_tn_info(fgp);
   __dmp_flowg_insns(fgp, mdp);
  }
 --- */

 /* remove insns that are x86 reg uses without def or defs without use */
 /* TRK remove */ // remove_unneeded_machreg_insns(fgp, mdp);

 /* SJM 03/10/07 - what does this do */
 peep_hole_optimize(fgp);
}

/*
 * swap the condition codes and blocks to create fall thrus
 *
 * for example
 *	testl	%ebx, %ebx
 *	je	L_16
 *	jmp	L_17
 * L_16:
 *	movl	%eax, __p0_te_endp
 * => swap condition and block to create a fall thru
 *
 *	testl	%ebx, %ebx
 *      jne	L_17
 *	movl	%eax, __p0_te_endp
 */
static void fixup_reverse_cond_jumps(struct flowg_t *fgp)
{
 struct insn_t *ip, *next_ip, *prev_ip;
 struct bblk_t *bbp, *next_bbp, *tmp_bbp;
 int32 blki, cc, t_seqno, new_cc;
   
 for (blki = 1; ;)
  {
   bbp = __bblktab[blki];
   __cur_bbp = bbp;

   ip = bbp->itail;
   /* if doens't have another block break */
   if (++blki == fgp->fg_num_bblks) break;
   next_bbp = __bblktab[blki];
   /* I_REAL_COND_JMP - more complicated */
   if (ip->opcod != I_COND_JMP && ip->opcod != I_BBLK_JMP) continue;
   
   /* only test for testl and cmpl conditions */
   prev_ip = ip->iprev;
   if (prev_ip->opcod != I_TESTL && prev_ip->opcod != I_CMPL) continue;

   /* get the next block if it is one */
   next_ip = next_bbp->ihd;
   if (next_ip == NULL || next_ip->opcod != I_BBLK_LABEL) continue;

   /* see if it is the true condition */
   cc = ip->jmptyp;
   t_seqno = ip->isrc.apu.bbp->bblk_seqno;
   if (t_seqno != next_ip->idst.apu.bbp->bblk_seqno) continue;

   /* swap condition for common case */
   /* note there are more conditions but these are special cases */
   /* mostly compares for 64-bit on 32-bit machines so skip them */
   switch (cc) {
    case CC_JE:
     new_cc = CC_JNE; 
     break;
    case CC_JNE:
     new_cc = CC_JE; 
     break;
    case CC_JGE:
     new_cc = CC_JLT;
     break;
    case CC_JGT:
     new_cc = CC_JLE;
     break;
    case CC_JLE:
     new_cc = CC_JGT;
     break;
    case CC_JLT:
     new_cc = CC_JGE;
     break;
    default: continue;
   }

   /* change to new condition and swap t/f blocks */
   ip->jmptyp = new_cc;
   tmp_bbp = ip->isrc.apu.bbp;
   ip->isrc.apu.bbp = ip->idst.apu.bbp;
   ip->idst.apu.bbp = tmp_bbp;
  }
}

/*
 * AIV 12/08/06 - remove fallthru blocks from the flowg 
 * if next block is a label remove the jmp 
 * if COND_JMP, b1, b2 -> next block head is label b2 mark jmp as not needed
 * if BBLK_JMP can linkout insn - because it is never needed
 * if label has no back edge mark it so it isn't lowered in asm generation
 */
static void mark_fallthru_jumps(struct flowg_t *fgp)
{
 struct insn_t *ip, *next_ip;
 struct bblk_t *bbp, *next_bbp;
 struct bbedge_t *bbep;
 int32 blki;
   
 for (blki = 1; ;)
  {
   bbp = __bblktab[blki];
   __cur_bbp = bbp;

   ip = bbp->itail;
   /* if doens't have another block break */
   if (++blki == fgp->fg_num_bblks) break;
   next_bbp = __bblktab[blki];
   /* AIV 01/10/07 - need to add I_REAL_COND_JMP - more complicated */
   if (ip->opcod != I_COND_JMP && ip->opcod != I_BBLK_JMP) continue;
   next_ip = next_bbp->ihd;

   if (next_ip == NULL || next_ip->opcod != I_BBLK_LABEL) continue;
   if (ip->idst.apu.bbp->bblk_seqno != next_ip->idst.apu.bbp->bblk_seqno) 
     continue;

   if (ip->opcod == I_BBLK_JMP) __linkout_insn(ip, TRUE);
   /* set to disp to -2 to indicate to printing that it is a fall thru */
   else ip->idst.disp = -2;

   /* if the jmpto block has only one back edge to this block */
   /* mark label as not needed to print (mark with -2) */
   bbep = next_bbp->bbe_prev;
   if (bbep == NULL) __misc_terr(__FILE__, __LINE__);
   if (bbep->eblkp == bbp && bbep->bbenxt == NULL)
    {
     next_ip->idst.disp = -2;
    }
  }
}

/*
 * expand asl func (returns val in eax) and proc no return val medium
 * level ASL RT entry routines
 */
static void expand_fg_asl_calls(struct flowg_t *fgp)
{
 struct bblk_t *bbp;
 struct insn_t *ip, *ip2; 

 /* notice the RPO bblk tab not built yet */
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp; 
   for (ip = bbp->ihd; ip != NULL;)
    {
     ip2 = ip->inxt;
     if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
      {
       /* SJM 02/19/07 - for debugging need original insn nl location */
#ifdef __CVC_DEBUG__
       __cur_ifrom_u = ip->ifru;
#endif

       expand_one_asl_call(ip);
      }
     ip = ip2;
    }
  }
 __cur_bbp = NULL; 
}

/*
 * expand one asl call insn - just replaces with lots of fixed boiler plate
 * array of args keeps args in reversed (as if pushed) order
 * 
 * called after reg assign - does not effect since the args already used
 * in reg assign and spilling (can spill asl call regs)
 *
 * this does not change reg assign since uses ecx where needed
 * think need to separate from reg allocation because of need for machine
 * reg preservation across asl calls
 *
 * for wide a/b used wides, the tn value will be the ebp address ptr tn
 * new algorithm pushes args onto ABI stack in reverse order
 */
#ifdef __CVC32__
static void expand_one_asl_call(struct insn_t *ip)
{
 int32 ai;
 int32 arg_ti, am_type, aslotyp, amode, ndx, overflow_reg, is_mem;
 word32 aval, wndx;
 size_t offsets[6];
 struct asl_info_t *aslp;
 struct tn_t *arg_tnp;
 struct insn_t *new_ip;
 struct asl_def_t *aslap;
 struct amode_t *amp;

 aslp = __to_aslinfo_rec(ip->idst.disp);

 if (aslp->uses_idp)
  {
   __insert_insn(ip, FALSE, I_MOVA, AM_REG, IDP_REG, AM_NLO, NLO_IDP);
  }

 /* no argument return */
 if (ip->callasl_argnum <= 0) 
  {
   /* for ASL calls with no args the call args tn union will be nil */
   ip->opcod = I_ASL_CALL;
   return;
  }

 wndx = 0;
 /* DBG revmoe -- */
 if (ip->callasl_argnum > 6) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 for (ai = 0; ai < ip->callasl_argnum; ai++) 
  {
   aslotyp = aslp->asl_op_typ[ai];
   offsets[ai] = wndx*WRDBYTES;
   /* notice use arg tnp pointer but pass the arg tn index */
   if (aslotyp == A_DBLE) 
    {
     wndx += 2;
    }
   else wndx++;
  }

 for (ai = 0; ai < ip->callasl_argnum; ai++) 
  {
   /* notice use arg tnp pointer but pass the arg tn index */
   ndx = ip->callasl_argnum - ai - 1;
   aslap = &(ip->extrau.asl_ausedefs[ndx]);
   amp = &(aslap->am_arg);
   arg_ti = amp->am_tni;
   arg_tnp = &(__tntab[arg_ti]);

   /* SJM 12/01/07 - nlo amode can't be passed to wrappers */
   /* DBG remove -- */
   if (aslap->am_arg.amode == AM_NLO) __misc_terr(__FILE__, __LINE__);
   /* --- */   

   /* case 1: literal int the only com lab case possible here */
   aslotyp = aslp->asl_op_typ[ndx];
   if (aslotyp == A_INT || aslotyp == A_NUM)
    {
     if (__is_constant(arg_ti))
      {
       aval = __get_wrd_amode_con_val(amp);
       /* always just insert before old asl call - then each inserted */
       /* goes after the previously inserted - then rem high level call */
       __insert_insn(ip, FALSE, I_MOVA, AM_IMM, aval, AM_NDXREG_DISP,
        AR_SP, offsets[ndx]);
       continue;
      }
     else if (aslotyp == A_NUM) __misc_terr(__FILE__, __LINE__);
    }

   /* case 3: pushing real */
   if (aslotyp == A_DBLE)
    {
     if (arg_tnp->tn_typ == TN_ADR) am_type = AM_NDXREG;
     else am_type = AM_REG;
     /* this is push for 8 byte real */
     /* if idp will have a know offset off of the idp reg */
     if (arg_ti == __idp_ti)
      {
       __insert_insn(ip, FALSE, I_FLDL, AM_NONE, AM_NDXREG_DISP, IDP_REG,
        amp->disp);
      }
     else __insert_insn(ip, FALSE, I_FLDL, AM_NONE, am_type, arg_ti);
     __insert_insn(ip, FALSE, I_FSTPL, AM_NONE, AM_NDXREG_DISP, AR_SP, 
      offsets[ndx]);
     continue;
    }

   /* AIV 12/04/08 - changed this to use a leal with the correct offset */
   /* before was expanding these to use add/mov which made for bad */
   /* register ranges since the add was computed and then passed */
   if (arg_ti == __idp_ti && amp->amode == AM_IDP_ADR_OFS) 
    {
     if (aslotyp == A_RPTR || aslotyp == A_WPTR || aslotyp == A_RWPTR)
      {
       overflow_reg = __gen_tn(SR_CINT, WBITS);
       new_ip = __insert_insn(ip, FALSE, I_LEAL, AM_NDXREG_DISP, IDP_REG, 
         amp->disp, AM_REG, overflow_reg);
       __insert_insn(ip, FALSE, I_MOVA, AM_REG, overflow_reg, AM_NDXREG_DISP,
         AR_SP, offsets[ndx]);
       continue;
      }
     else __misc_terr(__FILE__, __LINE__);
    }

   if (arg_ti == __idp_ti)
    {
     /* no special handling code is needed here amp->amode should be set */
     overflow_reg = __gen_tn(SR_CINT, WBITS);
     new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP, IDP_REG, 
       amp->disp, AM_REG, overflow_reg);
     __insert_insn(ip, FALSE, I_MOVA, AM_REG, overflow_reg, AM_NDXREG_DISP,
        AR_SP, offsets[ndx]);
     continue;
    }

   /* case 2: a comm lab */ 
   if (arg_tnp->comlab_typ != COMLAB_NONE)
    {
     /* nlo comlab or nlptr are always am_reg - never accessed as addr $ */
     if (__is_nlptr_comlab(arg_tnp->comlab_typ)) is_mem = TRUE;
     else if (aslotyp == A_WPTR || aslotyp == A_RWPTR || aslotyp == A_RPTR)
      { is_mem = FALSE; }
     else if (aslotyp == A_INT) is_mem = TRUE;
     else { is_mem = FALSE; __misc_terr(__FILE__, __LINE__); }

     if (is_mem)
      {
       overflow_reg = __gen_tn(SR_CINT, WBITS);
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG, arg_ti, 
        AM_REG, overflow_reg);
       __copy_amode(&(new_ip->isrc), amp);
       __insert_insn(ip, FALSE, I_MOVA, AM_REG, overflow_reg, AM_NDXREG_DISP,
         AR_SP, offsets[ndx]);
      }
     else
      {
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, arg_ti, 
        AM_NDXREG_DISP, AR_SP, offsets[ndx]);
       __copy_amode(&(new_ip->isrc), amp);
      }
     continue;
    }

   if (arg_tnp->tn_used_wide)
    {
     if (aslotyp == A_RPTR || aslotyp == A_WPTR || aslotyp == A_RWPTR)
      {
       overflow_reg = __gen_tn(SR_CINT, WBITS);
       new_ip = __insert_insn(ip, FALSE, I_LEAL, AM_REG, arg_ti, AM_REG,
        overflow_reg);
       __copy_amode(&(new_ip->isrc), amp);
       __insert_insn(ip, FALSE, I_MOVA, AM_REG, overflow_reg, AM_NDXREG_DISP,
         AR_SP, offsets[ndx]);
       continue;
      }
    }

   /* if reg assigned, just use it to store into <arg offset>(%esp) */
   amode = -1;
   if (aslotyp == A_RPTR || aslotyp == A_WPTR || aslotyp == A_RWPTR)
    {
     /* DBG revmoe -- */
     //if (arg_tnp->tn_typ != TN_ADR) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     amode = AM_REG;
    }
   else if (aslotyp == A_INT)
    {
     if (arg_tnp->tn_typ == TN_ADR) amode = AM_NDXREG;
     else amode = AM_REG;
    }
   else __case_terr(__FILE__, __LINE__);

   if (amode == AM_NDXREG)
    {
     overflow_reg = __gen_tn(SR_CINT, WBITS);
     new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG, arg_ti, 
      AM_REG, overflow_reg);
     __insert_insn(ip, FALSE, I_MOVA, AM_REG, overflow_reg, AM_NDXREG_DISP,
       AR_SP, offsets[ndx]);
    }
   else
    {
     new_ip = __insert_insn(ip, FALSE, I_MOVA, amode, arg_ti, AM_NDXREG_DISP,
         AR_SP, offsets[ndx]);
    }
  }

 __insert_insn(ip, FALSE, I_ASL_CALL, AM_NONE, AM_IMM, ip->idst.disp);
 __linkout_insn(ip, TRUE);
}

#else
/*
 * 64-bit expand one asl call
 */
static void expand_one_asl_call(struct insn_t *ip)
{
 int32 arg_ti, am_type, aslotyp, amode, ndx, ai, ri;
 word32 aval, number_of_reals, real_reg;
 struct asl_info_t *aslp;
 struct tn_t *arg_tnp;
 struct insn_t *new_ip;
 struct asl_def_t *aslap;
 struct amode_t *amp;

 aslp = __to_aslinfo_rec(ip->idst.disp);

 if (aslp->uses_idp)
  {
   __insert_insn(ip, FALSE, I_MOVQ, AM_REG, IDP_REG, AM_NLO, NLO_IDP);
  }

 /* no argument return */
 if (ip->callasl_argnum <= 0) 
  {
   /* for ASL calls with no args the call args tn union will be nil */
   ip->opcod = I_ASL_CALL;
   return;
  }

 /* stored in insn from 0 to n but must store on stack in reverse order */ 
 number_of_reals = 0;
 for (ai = 0; ai < ip->callasl_argnum; ai++) 
  {
   /* notice use arg tnp pointer but pass the arg tn index */
   ndx = ip->callasl_argnum - ai - 1;
   aslap = &(ip->extrau.asl_ausedefs[ndx]);
   amp = &(aslap->am_arg);
   arg_ti = amp->am_tni;
   arg_tnp = &(__tntab[arg_ti]);

   /* case 1: literal int the only com lab case possible here */
   aslotyp = aslp->asl_op_typ[ndx];
   if (aslotyp == A_INT || aslotyp == A_NUM)
    {
     if (__is_constant(arg_ti))
      {
       aval = __get_wrd_amode_con_val(amp);
       /* always just insert before old asl call - then each inserted */
       /* goes after the previously inserted - then rem high level call */
       new_ip = __insert_insn(ip, FALSE, I_MOVQ, AM_IMM, aval, AM_REG, 
         __passed_regs_order[ndx]);
       continue;
      }
     else if (aslotyp == A_NUM) __misc_terr(__FILE__, __LINE__);
    }

   /* case 3: pushing real */
   if (aslotyp == A_DBLE)
    {
     if (arg_tnp->tn_typ == TN_ADR) am_type = AM_NDXREG;
     else am_type = AM_REG;
     /* AIV 11/12/08 - if passing double to a wrapper pass in xmm regs */
     /* only real power takes more than one real so make number of reals */
     /* passed in two */
     real_reg = I_LDR1;
     if (aslp->asl_rout_num == ASL_REAL_POW_FUNC)
      {
       if (number_of_reals == 0) real_reg = I_LDR2;
       else if (number_of_reals == 1) real_reg = I_LDR1;
       }
     else if (number_of_reals > 0) __case_terr(__FILE__, __LINE__);

     if (arg_ti == __idp_ti)
      {
       __insert_insn(ip, FALSE, real_reg, AM_NONE, AM_NDXREG_DISP, IDP_REG,
        amp->disp);
      }
     else __insert_insn(ip, FALSE, real_reg, AM_NONE, am_type, arg_ti);
     number_of_reals++;
     continue;
    }

   if (arg_ti == __idp_ti && amp->amode == AM_IDP_ADR_OFS) 
    {
     if (aslotyp == A_RPTR || aslotyp == A_WPTR || aslotyp == A_RWPTR)
      {
       __insert_insn(ip, FALSE, I_LEAL, AM_NDXREG_DISP, IDP_REG, amp->disp,
         AM_REG, __passed_regs_order[ndx]);
       continue;
      }
     else __misc_terr(__FILE__, __LINE__);
    }

   if (arg_ti == __idp_ti)
    {
     /* no special handling code is needed here amp->amode should be set */
     new_ip = __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP,
       IDP_REG, amp->disp, AM_REG, __passed_regs_order[ndx]);
     continue;
    }

   /* case 2: a comm lab */ 
   if (arg_tnp->comlab_typ != COMLAB_NONE)
    {
     /* AIV 08/28/09 - if large model need the special instruction and */
     /* extra level of indirection */
     if (__cvc_use_large_model)
      {
       ri = __passed_regs_order[ndx];
       new_ip = __insert_insn(ip, FALSE, I_MOVABSQ, AM_REG, arg_ti, AM_REG, ri);
       __copy_amode(&(new_ip->isrc), amp);
       if (__is_nlptr_comlab(arg_tnp->comlab_typ))
        {
         /* mark amode to print as addresss */
         new_ip->isrc.is_large_label = TRUE;
         new_ip = __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG, ri, AM_REG, ri);
        }
       continue;
      }
     /* nlo comlab or nlptr are always am_reg - never accessed as addr $ */
     if (__is_nlptr_comlab(arg_tnp->comlab_typ)) amode = AM_REG;
     else if (aslotyp == A_WPTR || aslotyp == A_RWPTR || aslotyp == A_RPTR)
      { amode = AM_REG; }
     else if (aslotyp == A_INT) amode = AM_NDXREG;
     else { amode = AM_REG; __misc_terr(__FILE__, __LINE__); }

     new_ip = __insert_insn(ip, FALSE, I_MOVQ, amode, arg_ti, AM_REG, 
      __passed_regs_order[ndx]);
     __copy_amode(&(new_ip->isrc), amp);
     continue;
    }

   if (arg_tnp->tn_used_wide)
    {
     if (aslotyp == A_RPTR || aslotyp == A_WPTR || aslotyp == A_RWPTR)
      {
       new_ip = __insert_insn(ip, FALSE, I_LEAL, AM_REG, arg_ti, AM_REG,
        __passed_regs_order[ndx]);
       __copy_amode(&(new_ip->isrc), amp);
       continue;
      }
    }

   /* if reg assigned, just use it to store into <arg offset>(%esp) */
   amode = -1;
   if (aslotyp == A_RPTR || aslotyp == A_WPTR || aslotyp == A_RWPTR)
    {
     /* DBG revmoe -- */
     if (arg_tnp->tn_typ != TN_ADR) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     amode = AM_REG;
    }
   else if (aslotyp == A_INT)
    {
     if (arg_tnp->tn_typ == TN_ADR) amode = AM_NDXREG;
     else amode = AM_REG;
    }
   else __case_terr(__FILE__, __LINE__);
   new_ip = __insert_insn(ip, FALSE, I_MOVQ, amode, arg_ti, 
     AM_REG, __passed_regs_order[ndx]);

   /* AIV 03/18/10 - set which tmps are passed as args to wrappers */
   /* this is used for the reg alloc to place this tmp into the passed */
   /* reg to get rid of moves - +1 because this is field init to 0 */
   __tntab[arg_ti].passed_args = ndx+1;
  }

 __insert_insn(ip, FALSE, I_ASL_CALL, AM_NONE, AM_IMM, ip->idst.disp);
 __linkout_insn(ip, TRUE);
}
#endif

/*
 * AIV 03/08/07 - took me a good day to find this problem and the current
 *  solution isn't good but here is the problem and the current fix:
 * 
 * expand of calls is done after register allocation - and currently register
 * alloc (liveness analysis) is only done on tmps that fit in a reg
 * when the register alloc runs out of regs it attempts to use the overflow
 * reg (ecx) if it doesn't conflict with any spilled regs
 * therefore this bug is created 
 *
 * addl    $N_196_33, %ecx   //ecx dst
 * pushl   $0x1300 
 * leal    -5072(%ebp), %ecx  //ecx overwritten by the source
 * pushl   %ecx    //cannot pass two args of the same value
 * pushl   %ecx 
 * call    memcpy 
 *
 * the current fix is to check for this case and if it occurs to use eax
 * eax should be able to be used because it is killed across the call
 *
 * there is only one example that makes this occur bug 04/19/05 - need a 
 * smaller test case - try to expand random tests to extra wide
 * AIV FIXME - this is dumb and should be fixed by doing liveness on all tmps
 */
/* AIV REMOVME - no longer used?????
static int32 get_aslcall_overflow_reg(struct asl_info_t *aslp,
  struct insn_t *ip)
{
 int32 ai, arg_ti, aslotyp;
 int32 uses_overflow, assigned_overflow, uses_eax, uses_edx;
 struct asl_def_t *aslap;
 struct tn_t *arg_tnp;
 struct amode_t *amp;

 assigned_overflow = FALSE;
 uses_overflow = FALSE;
 uses_eax = FALSE;
 uses_edx = FALSE;
 for (ai = 0; ai < ip->callasl_argnum; ai++) 
  {
   aslap = &(ip->extrau.asl_ausedefs[ip->callasl_argnum - ai - 1]);
   amp = &(aslap->am_arg);
   arg_ti = amp->am_tni;
   arg_tnp = &(__tntab[arg_ti]);

   aslotyp = aslp->asl_op_typ[ip->callasl_argnum - ai - 1];
   // if assigned and it is the overflow reg mark the flag 
   if (arg_tnp->tn_assigned)
    {
     if (arg_tnp->x86_regno == OFLW_REG)
      {
       assigned_overflow = TRUE;
      }
     // keep track of eax to make sure this isn't used if - attempting to use 
     else if (arg_tnp->x86_regno == AR_AX)
      {
       uses_eax = TRUE;
      }
     else if (arg_tnp->x86_regno == AR_DX)
      {
       uses_edx = TRUE;
      }
    }
   // using overflow in leal 
   else if (arg_tnp->tn_spilled)
    {
     if (aslotyp == A_RPTR || aslotyp == A_WPTR || aslotyp == A_RWPTR)
      {
       if (arg_tnp->tn_typ != TN_ADR)
        {
         uses_overflow = TRUE;
        }
      }
    }
   // using overflow as ndx reg 
   else if (aslotyp == A_INT && arg_tnp->tn_typ == TN_ADR)
    {
     uses_overflow = TRUE;
    }
  }
 // if assigned overflow and it needs to use it try to use eax 
 if (assigned_overflow && uses_overflow) 
  {
   // AIV 11/09/07 - expanding this code to use AR_DX if eax and ecx used 
   // this shouldn't be a problem in new SJM version which expands the 
   // asl calls inplace 
   if (uses_eax) 
    {
     // DBG revmoe -- 
     if (uses_edx) __misc_terr(__FILE__, __LINE__);
     // ----- 
     return(AR_DX);
    }
   return(AR_AX);
  }
 return(OFLW_REG);
}
*/
 

/*
 * ROUTINES TO FIX ILLEGAL 2 MEMREF X86 INSNS 
 */

/*
 * assign overflow by changing amodes to their stack location
 * and fixing memory to memory problems
 * overflow already lowered with ebp offset by here
 *
 * SJM 10/26/06 - now sets amodes in this routine too
 */
static void fixup_1fg_2memrefs(struct flowg_t *fgp)
{
 int32 blki, mr2_typ;
 struct bblk_t *bbp;
 struct insn_t *ip, *ip2, *new_ip;
 struct amode_t *srcp, *dstp;
 struct tn_t *srctnp, *dsttnp;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     srcp = &(ip->isrc);
     dstp = &(ip->idst);

     /* case 0: handle all the NLO ARRNDX insns as a special case */
     if (srcp->amode == AM_NLO_ARRNDX)
      {
       /* DBG revmoe -- */
       if (srcp->arr_base_nlo == NLO_NONE) __misc_terr(__FILE__, __LINE__);
       /* --- */
       fix_nlo_arrndx_insn(ip);
       continue;
      }

#ifndef __CVC32__
     /* AIV 08/28/09 - special movabsq cannot be spilled - but in move */
     if (ip->opcod == I_MOVABSQ)
      {
       /* DBG remove -- */
       if (!__cvc_use_large_model) __misc_terr(__FILE__, __LINE__);
       /* ----- */
       /* movabsq	$__idpdat_2 + 446440, 1408(%rsp) */
       if (__tntab[dstp->am_tni].tn_spilled)
        {
         new_ip = __insert_insn(ip, FALSE, I_MOVABSQ, AM_REG, OFLW_REG, AM_REG,
          OFLW_REG); 
         __copy_amode(&(new_ip->isrc), srcp);
         ip->isrc.amode = AM_REG;
         ip->isrc.x86_regno = OFLW_REG;
         ip->isrc.am_tni = OFLW_REG;
         set_amode_ebp_disp(dstp->am_tni, dstp);
         ip->opcod = I_MOVQ;
         continue;
        }
      }
#endif

     /* case 1: not 2 memref - just set the amode */
     if (!__amode_mem_ref(srcp) || !__amode_mem_ref(dstp))
      {   
       /* AIV 12/04/07 - may need to handle the spilled NLO case here */
       /* movl  -36(%ebp), __new_inputval */
       /* => movl -36(%ebp), %ecx */
       /* => movl %ecx, __new_inputval */
       /* rare case but can occur */
       if (srcp->am_tni != -1 && __tntab[srcp->am_tni].tn_spilled 
         && dstp->amode == AM_NLO) 
        {
         set_amode_ebp_disp(srcp->am_tni, srcp);
         ip->idst.amode = AM_REG;
         ip->idst.x86_regno = OFLW_REG;
         ip->idst.am_tni = OFLW_REG;
         new_ip = __insert_insn(ip, TRUE, I_MOVA, AM_REG, OFLW_REG, AM_NLO,
          dstp->disp);
         continue;
        }



       /* AIV 12/04/07 - may need to handle the spilled NLO case here */
       /* movl  __idp, -36(%ebp) */
       /* => movl __idp, %ecx */
       /* => %ecx, -36(%ebp) */
       if (srcp->amode == AM_NLO && dstp->am_tni != -1 &&
           __tntab[dstp->am_tni].tn_spilled)
        {
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NLO,
          srcp->disp, AM_REG, OFLW_REG);
  
         ip->isrc.amode = AM_REG;
         ip->isrc.x86_regno = OFLW_REG;
         ip->isrc.am_tni = OFLW_REG;
         set_amode_ebp_disp(dstp->am_tni, dstp);
         continue;
        }

       /* SJM 10/28/06 - spilled ndx amode also requires mapping because */
       /* offset if from contents of <spill disp>(%ebp) - can't combine */
       if ((srcp->amode == AM_NDXREG || srcp->amode == AM_NDXREG_DISP)
        && __tntab[srcp->am_tni].tn_spilled)
        {
         /* movl 4(-12(%ebp)), %ebx */
         /* ==> movl -12(%ebp), %ecx; movl 4(%ecx), %ebx */
         /* trick is that the disp in the insn is not part of the spilled */
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP,
          srcp->am_tni, 0UL, AM_REG, OFLW_REG);
         set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));
  
         /* original insn src amode and disp correct */
         ip->isrc.x86_regno = OFLW_REG;
         ip->isrc.am_tni = OFLW_REG;
        }
       else
        {
         /* simple assign regs to amode */
         try_set_amode_to_reg(srcp);
        } 

       /* dest can never be __nlo_type(%eax) */
       /* DBG remove -- */
       if (dstp->arr_base_nlo != NLO_NONE) __misc_terr(__FILE__, __LINE__);
       /* ----- */

       if ((dstp->amode == AM_NDXREG || dstp->amode == AM_NDXREG_DISP)
        && __tntab[dstp->am_tni].tn_spilled)
        {
         /* movl %ebx, 4(-12(%ebp)) */
         /* ==> movl -12(%ebp), %ecx; movl %ebx, 4(%ecx) */
         /* trick is that the disp in the insn is not part of the spilled */
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP,
          dstp->am_tni, 0UL, AM_REG, OFLW_REG);
         set_amode_ebp_disp(dstp->am_tni, &(new_ip->isrc));
  
         /* original insn dst amode and disp correct */
         ip->idst.x86_regno = OFLW_REG;
         ip->idst.am_tni = OFLW_REG;
        }
       /* AIV 11/06/06 - multiply cannot take any memory operand as dst */
       /* need to handle as a special case */
       else if (ip->opcod == I_IMULL && __tntab[dstp->am_tni].tn_spilled)
        {
         /* imull $0x8, -4(%ebp) */
         /* => movl -4(%ebp), %ecx */
         /* => imull $0x8, %ecx */
         /* => movl %ecx, -4(%ebp) */
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP,
          dstp->am_tni, 0UL, AM_REG, OFLW_REG);
         set_amode_ebp_disp(dstp->am_tni, &(new_ip->isrc));

         new_ip = __insert_insn(ip, TRUE, I_MOVA, AM_REG, OFLW_REG, 
          AM_NDXREG_DISP, dstp->am_tni, 0UL);
         set_amode_ebp_disp(dstp->am_tni, &(new_ip->idst));

         /* original insn dst amode and disp correct */
         ip->idst.x86_regno = OFLW_REG;
         ip->idst.am_tni = OFLW_REG;
        }
       else try_set_amode_to_reg(dstp);
       continue;
      }

     /* case 2: illegal x86 insn because has 2 mem refs */
     srctnp = &(__tntab[srcp->am_tni]);
     dsttnp = &(__tntab[dstp->am_tni]);

     /* handle two static comm area labels */
     /* movl M_a_b, prev.bp */
     /* => movl M_a_b, %ecx; movl %ecx, prev.bp */
     /* AIV 12/29/06 - this is now illegal - bbgen3 should never produce */
     /* code that causes this */
     /* DBG remove -- */
     if (srctnp->comlab_typ != COMLAB_NONE && dsttnp->comlab_typ != COMLAB_NONE)
      {
       __misc_terr(__FILE__, __LINE__);
      }
     /* ----- */

//AIV? - LOOKATME what this should be?
     if (srctnp->comlab_typ != COMLAB_NONE && __amode_mem_ref(srcp)) 
      {
       /* know src is a comlab that requires a memory ref */

       /* movl M_a_b + 4, (%eax) */
       /* ==> movl M_a_b + 4, %ecx; movl %ecx, (%eax) */  
       if (!dsttnp->tn_spilled) 
        {
         /* DBG remove -- */
         if (dstp->amode != AM_NDXREG_DISP && dstp->amode != AM_NDXREG)
           __misc_terr(__FILE__, __LINE__);
         if (!dsttnp->tn_assigned)
           __misc_terr(__FILE__, __LINE__);
         /* --- */
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
           AM_REG, OFLW_REG);
         __copy_amode(&(new_ip->isrc), &(ip->isrc));

         __init_amode(&(ip->isrc));
         ip->isrc.amode = AM_REG;
         ip->isrc.x86_regno = OFLW_REG;
         ip->isrc.am_tni = OFLW_REG;
         try_set_amode_to_reg(dstp);
         continue;
        }

       /* DBG remove -- */
       if (dstp->amode == AM_NDXREG_DISP || dstp->amode == AM_NDXREG) 
         __misc_terr(__FILE__, __LINE__);
       /* --- */
       
       /* key observation - moving comlab into a memory is always simple */
       /* movl M_a_b + 4, -24(%ebp) */
       /* ==> movl M_a_b + 4, %ecx; movl %ecx, -24(%ebp) */  
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, OFLW_REG);
       /* need copy not set ebp offset since this is the comm lab */
       /* SJM 10/29/06 - dest is first arg */
       __copy_amode(&(new_ip->isrc), &(ip->isrc));

       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;
       /* fills the new ip src amode from the src tn - so can use dummy */
       set_amode_ebp_disp(dstp->am_tni, &(ip->idst));
       continue;
      }
     if (dsttnp->comlab_typ != COMLAB_NONE && __amode_mem_ref(dstp))
      {
       /* know src is a comlab that requires a memory ref */
       /* key observation - moving a comlab into a memory always simple */
       /* movl -24(%ebp), M_a_b + 4 */
       /* ==> movl -24(%ebp), %ecx; movl %ecx, M_a_b + 4 */
       if (ip->isrc.amode == AM_REG)
        {
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
          AM_REG, OFLW_REG);
         /* fills the new ip src amode from the src tn - so can use dummy */
         set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));

         __init_amode(&(ip->isrc));
         ip->isrc.amode = AM_REG;
         ip->isrc.x86_regno = OFLW_REG;
         ip->isrc.am_tni = OFLW_REG;
         continue;
        }
       /* this should handle ndxdisp as well but don't think any occur */
       /* DBG remove -- */
       if (ip->isrc.amode != AM_NDXREG)  __misc_terr(__FILE__, __LINE__);
       /* ----- */

       /* movl (-4(%ebp)), M_a_b + 4 */
       /* ==> movl -4(%ebp), %ecx; movl (%ecx), %ecx; movl %ecx, M_a_b + 4 */
       if (srctnp->tn_spilled) 
        {
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
          AM_REG, OFLW_REG);
         __copy_amode(&(new_ip->isrc), &(ip->isrc));
         set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));

         __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG, OFLW_REG, 
           AM_REG, OFLW_REG);

         __init_amode(&(ip->isrc));
         ip->isrc.amode = AM_REG;
         ip->isrc.x86_regno = OFLW_REG;
         ip->isrc.am_tni = OFLW_REG;
         continue;
        }
       /* movl (%eax), M_a_b + 4 */
       /* ==> movl (%eax), %ecx; movl %ecx, M_a_b + 4 */
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, OFLW_REG);
       __copy_amode(&(new_ip->isrc), &(ip->isrc));
       try_set_amode_to_reg(&(new_ip->isrc));

       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;
       continue;
      }
       
     /* AIV 12/31/07 - handle the testl which spills as a special case */
     /* we always use this as testl r1, r1 it was doing the following */
     /* movl -40(%ebp), %ecx, testl %ecx, -40(%ebp) */
     /* should be movl -40(%ebp), %ecx, testl %ecx, %ecx */
     if (ip->opcod == I_TESTL && srcp->am_tni != -1 && 
         __tntab[srcp->am_tni].tn_spilled)
        {
         /* DBG remove -- */
         if (srcp->am_tni != dstp->am_tni) __misc_terr(__FILE__, __LINE__);
         if (srcp->amode != AM_REG && srcp->amode != AM_NONREG_OFS) 
           __misc_terr(__FILE__, __LINE__);
         /* ----- */
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP,
          dstp->am_tni, dstp->disp, AM_REG, OFLW_REG);
         set_amode_ebp_disp(dstp->am_tni, &(new_ip->isrc));
  
         /* original insn dst amode and disp correct */
         ip->idst.x86_regno = OFLW_REG;
         ip->idst.am_tni = OFLW_REG;
         ip->idst.amode = AM_REG; 
         ip->isrc.x86_regno = OFLW_REG;
         ip->isrc.am_tni = OFLW_REG;
         ip->isrc.amode = AM_REG; 
         continue;
        }

     mr2_typ = determine_2memref_class(ip);
     switch (mr2_typ) {
      case MR2_SPILL_SPILL:
       /* movl -4(%ebp), -8(%ebp) */
       /* ==> movl -4(%ebp), %ecx; movl %ecx, -8(%ebp) */
       /* just use dummy src since changed after */ 
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, OFLW_REG);
       /* notice only set ebp disp for spilled - not for other ndx reg */
       /* SJM 10/27/06 - do not need copy amode here because get info from */
       /* src tn but set in different passed amode */
       /* need to copy the amode since can't use set ebp disp for this */
       __copy_amode(&(new_ip->isrc), srcp);
       set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));

       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;
       set_amode_ebp_disp(dstp->am_tni, &(ip->idst));
       /* AIV 09/10/10 - rare case this can occur - need to swap the opcods */
       /* was attempting the leal on the new overflow reg */
       if (ip->opcod == I_LEAL)
        {
         new_ip->opcod = I_LEAL;
         ip->opcod = I_MOVL;
        }
       break;
      case MR2_SPILL_SPILL_NOMEM:
       /* insn that has two spills and cannot take any operands a memory */
       /* imull -4(%ebp), -8(%ebp) */
       /* ==> pushl %eax */
       /* ==> movl -4(%ebp), %ecx */
       /* ==> movl -8(%ebp), %eax */
       /* ==> imull %ecx, %eax */
       /* ==> movl  %eax, -8(%ebp) */
       /* ==> popl  %eax */

       /* ==> pushl %eax */
       /* save stored reg can just save on stack know no call of arg here */
       __insert_insn(ip, FALSE, I_MOVL, AM_REG, AR_AX, AM_NDXREG, AR_SP); 

       /* ==> movl -4(%ebp), %ecx */
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, OFLW_REG);
       __copy_amode(&(new_ip->isrc), srcp);
       set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));

       /* ==> movl -8(%ebp), %eax */
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, AR_AX);
       __copy_amode(&(new_ip->isrc), dstp);
       set_amode_ebp_disp(dstp->am_tni, &(new_ip->isrc));

       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;

       /* ==> movl %eax, -8(%ebp) */
       new_ip = __insert_insn(ip, TRUE, I_MOVA, AM_REG, AR_AX,
        AM_REG, AM_NONE);
       __copy_amode(&(new_ip->idst), dstp);
       set_amode_ebp_disp(dstp->am_tni, &(new_ip->idst));

       __init_amode(&(ip->idst));
       ip->idst.amode = AM_REG;
       ip->idst.x86_regno = AR_AX;
       ip->idst.am_tni = AR_AX;

       /* ==> popl  %eax */
       __insert_insn(new_ip, TRUE, I_MOVL, AM_NDXREG, AR_SP, AM_REG, AR_AX); 
       break;
      case MR2_SPILL_SPILLNDX:
       /* movl -4(%ebp), 12(-8(%ebp)) */
       /* ==> movl -4(%ebp), %ecx; pushl %eax; movl -8(%ebp), %eax; */
       /*     movl %ecx, <disp>(%eax); popl %eax */
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, OFLW_REG);
       /* fills the new ip src amode from the src tn - so can use dummy */
       __copy_amode(&(new_ip->isrc), srcp);
       set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));
       /* save stored reg can just save on stack know no call of arg here */
       __insert_insn(ip, FALSE, I_MOVL, AM_REG, AR_AX, AM_NDXREG, AR_SP); 

       /* the src eax is just a place holder */
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, AR_AX,
        AM_REG, AR_AX); 
       /* this fills the new ip src amode from the src tn so can use dummy */
       set_amode_ebp_disp(dstp->am_tni, &(new_ip->isrc));

       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;

       /* the dest amode type and disp if any stay the same */
       ip->idst.x86_regno = AR_AX;
       ip->idst.am_tni = AR_AX;

       /* now restore eax */ 
       __insert_insn(ip, TRUE, I_MOVL, AM_NDXREG, AR_SP, AM_REG, AR_AX); 
       break;
      case MR2_SPILL_X86NDX:
       /* movl -12(%ebp), 12(%esi)) */ 
       /* ==> movl -12(%ebp), %ecx; movl %ecx, 12(%esi) */
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, OFLW_REG);
       /* this fills the new ip src amode from the src tn so can use dummy */
       __copy_amode(&(new_ip->isrc), srcp);
       set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));

       /* fixup src of 2nd insn - dst is good ndx reg or ndx reg disp */
       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;
       /* notice do not set ebp offset here - ndx reg dest stays same */

       /* SJM 10/28/06 - still must set x86 reg since no assigned reg */
       ip->idst.x86_regno = __tntab[ip->idst.am_tni].x86_regno;
       break;
      case MR2_SPILLNDX_SPILL:
       /* movl 8(-12(%ebp)), -44(%ebp) */ 
       /* ==> movl -12(%ebp), %ecx; movl 8(%ecx), %ecx; movl %ecx, -44(%ebp) */
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, OFLW_REG);
       /* this fills the new ip src amode from the src tn so can use dummy */
       set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));

       if (srcp->amode == AM_NDXREG)
        {
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG,
          OFLW_REG, AM_REG, OFLW_REG);
        }
       else
        {
         /* notice ip isrc disp not yet overwritten */
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP,
          OFLW_REG, ip->isrc.disp, AM_REG, OFLW_REG);
        }
       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;
       /* must set ebp offset for spill dest */
       set_amode_ebp_disp(dstp->am_tni, &(ip->idst));
       break;
      case MR2_X86NDX_SPILL:
       /* AIV 02/29/08 - need to handle the mult special case here */
       /* imull can must have register for the dst */
       if (ip->opcod == I_IMULL)
        {
         /* imull 8(%esi), -44(%ebp) */ 
         /* ==> movl 8(%esi), %ecx; imull -44(%ebp), %ecx */
         /*     movl %ecx, -44(%ebp) */

         /* movl 8(%esi), %ecx */
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, AR_AX,
          AM_REG, OFLW_REG);
         __copy_amode(&(new_ip->isrc), &(ip->isrc));
         new_ip->isrc.x86_regno = __tntab[new_ip->isrc.am_tni].x86_regno;

         /* imull -44(%ebp), %ecx */
         __copy_amode(&(ip->isrc), &(ip->idst));
         set_amode_ebp_disp(dstp->am_tni, &(ip->isrc));
         __init_amode(&(ip->idst));
         ip->idst.amode = AM_REG;
         ip->idst.x86_regno = OFLW_REG;
         ip->idst.am_tni = OFLW_REG;

         /*     movl %ecx, -44(%ebp) */
         new_ip = __insert_insn(ip, TRUE, I_MOVA, AM_REG, OFLW_REG,
          AM_REG, AR_AX);
          __copy_amode(&(new_ip->idst), &(ip->isrc));
         break;
        }

       /* AIV 12/04/08 - now can have special case leal here just do */
       /* leal 56(%ebx), 44(%esp) */
       /* => leal 56(%ebx), %ecx */
       /* => movl %ecx, 44(%esp) */
       if (ip->opcod == I_LEAL)
        {
         new_ip = __insert_insn(ip, TRUE, I_MOVA, AM_REG, OFLW_REG,
           AM_REG, OFLW_REG);

         /* must set ebp offset for spill dest */
         set_amode_ebp_disp(dstp->am_tni, &(new_ip->idst));

         __init_amode(dstp);
         dstp->amode = AM_REG;
         dstp->x86_regno = OFLW_REG;
         dstp->am_tni = OFLW_REG;
         break;
        }
       /* movl 8(%esi), -44(%ebp) */ 
       /* ==> movl 8(%esi), %ecx; movl %ecx, -44(%ebp) */
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, AR_AX,
        AM_REG, OFLW_REG);
       /* need to copy the amode since can't use set ebp disp for this */
       __copy_amode(&(new_ip->isrc), &(ip->isrc));

       /* SJM 10/28/06 - still must set x86 reg since no assigned reg */
       new_ip->isrc.x86_regno = __tntab[new_ip->isrc.am_tni].x86_regno;

       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;
       /* must set ebp offset for spill dest */
       set_amode_ebp_disp(dstp->am_tni, &(ip->idst));
       break;
      case MR2_SPILLNDX_SPILLNDX:
       /* movl 24(-12(%ebp)), 12(-44(%ebp)) */ 
       /* ==> movl -12(%ebp), %ecx; pushl %eax; movl -44(%ebp), %eax; */
       /*     movl 24(%ecx), %ecx; movl %ecx, 12(%eax); popl %eax */
       /* AIV 03/25/09 - this case is no longer needed */
       /* DBG remove -- */
       __misc_terr(__FILE__, __LINE__);
       /* --- */
       break;
      case MR2_SPILLNDX_X86NDX:
       /* movl 8(-12(%ebp)), 4(%esi) */
       /* ==> movl -12(%ebp), %ecx; movl 8(%ecx), %ecx; movl %ecx, -4(%esi)*/
       new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_REG, REG_NONE,
        AM_REG, OFLW_REG);
       set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));
 
       if (srcp->amode == AM_NDXREG)
        {
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG,
          OFLW_REG, AM_REG, OFLW_REG);
        }
       else
        {
         /* ip src disp still unchanged here */ 
         new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP,
          OFLW_REG, ip->isrc.disp, AM_REG, OFLW_REG);
        }
 
       __init_amode(&(ip->isrc));
       ip->isrc.amode = AM_REG;
       ip->isrc.x86_regno = OFLW_REG;
       ip->isrc.am_tni = OFLW_REG;
 
       /* do not need set ebp offset for non spilled ndx addr mode */
       /* SJM 10/28/06 - but still must set x86 reg since no assigned reg */
       ip->idst.x86_regno = __tntab[ip->idst.am_tni].x86_regno;
       break;
      case MR2_X86NDX_SPILLNDX:
       /* movl 8(%esi), 12(-44(%ebp)) */
       /* ==> movl 8(%esi), %ecx; pushl %eax; movl -44(%ebp), %eax; */
       /*     movl %ecx, 12(%eax); popl %eax */
       /* AIV 03/25/09 - this case is no longer needed */
       /* DBG remove -- */
       __misc_terr(__FILE__, __LINE__);
       /* --- */
       break;
      case MR2_X86NDX_X86NDX:
       /* movl 8(%esi)), 12(%edi)) */
       /* ==> movl 8(%esi), %ecx; movl %ecx, 12(%esi) */
       /* since index to index - no need to call set ebp mode */
       /* AIV 03/25/09 - this case is no longer needed */
       /* DBG remove -- */
       __misc_terr(__FILE__, __LINE__);
       /* --- */
       break;
      default: __case_terr(__FILE__, __LINE__);
     }
    }
  }
 __cur_bbp = NULL;
}

/*
 * fix the special case of src that is an NLO RT fixed address such as __epair
 *
 * movl __epair(%r44), %r80 - where both or none can spill
 * SJM 11/15/06 - added this new routine
 */
static void fix_nlo_arrndx_insn(struct insn_t *ip)
{
 struct amode_t *srcp, *dstp;
 struct tn_t *srctnp, *dsttnp;
 struct insn_t *new_ip;

 srcp = &(ip->isrc);
 dstp = &(ip->idst);
 srctnp = &(__tntab[srcp->am_tni]);
 dsttnp = &(__tntab[dstp->am_tni]);

 /* if both assigned to regs, nothing to do - movl __epair_tab(%esi), %ebx */
 if (srctnp->tn_assigned && dsttnp->tn_assigned)
  {
   try_set_amode_to_reg(srcp);
   try_set_amode_to_reg(dstp);
   return;
  }

 /* case 1: NLO ARRNDX spilled but not the dest reg */
 if (srctnp->tn_spilled && dsttnp->tn_assigned)
  {
   /* fixup   movzbl __epair_tab(-4(%ebp)), %esi */
   /*         => movl  -4(%ebp), %ecx */
   /*         => movzbl __epair_tab(%ecx), %esi */
   new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP, srcp->am_tni, 0UL,
    AM_REG, OFLW_REG);
   set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));
   ip->isrc.x86_regno = OFLW_REG;
   ip->isrc.am_tni = OFLW_REG;
   try_set_amode_to_reg(dstp);
   return;
  }
 /* case 2: only dest reg spilled */
 if (srctnp->tn_assigned && dsttnp->tn_spilled)
  {
   /* fixup   movzbl __epair_tab(%edi), -4(%ebp) */
   /*         => movzbl __epair_tab(%edi), %ecx */
   /*         => movl  %ecx, -4(%ebp) */
   /* dest. is a place holder */
   new_ip = __insert_insn(ip, TRUE, I_MOVA, AM_REG, OFLW_REG, AM_REG, AR_AX);
   __copy_amode(&(new_ip->idst), &(ip->idst));
   try_set_amode_to_reg(srcp);
   set_amode_ebp_disp(dstp->am_tni, &(new_ip->idst));
   ip->idst.amode = AM_REG;
   ip->idst.am_tni = OFLW_REG;
   ip->idst.x86_regno = OFLW_REG;
   return;
  } 
 /* case 3: both spilled */
 /* fixup   movzbl __epair_tab(-4(%ebp)), -12(%ebp) */
 /*         => movl -4(%ebp), %ecx */ 
 /*         => movzbl __epair_tab(%ecx), %ecx */
 /*         => movl  %ecx, -12(%ebp) */
 new_ip = __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP, srcp->am_tni, 0UL,
  AM_REG, OFLW_REG);
 set_amode_ebp_disp(srcp->am_tni, &(new_ip->isrc));
 ip->isrc.am_tni = OFLW_REG;
 ip->isrc.x86_regno = OFLW_REG;
 new_ip = __insert_insn(ip, TRUE, I_MOVA, AM_REG, OFLW_REG, AM_REG, AR_AX);
 __copy_amode(&(new_ip->idst), &(ip->idst));
 set_amode_ebp_disp(dstp->am_tni, &(new_ip->idst));
 /* final step change original mov of ARRNDX insn dest to ecx */  
 ip->idst.amode = AM_REG;
 ip->idst.am_tni = OFLW_REG;
 ip->idst.x86_regno = OFLW_REG;
}

/*
 * for debugging - check for no 2 memref insns and for no wide tn amodes
 * 
 * this is the place for misc consistency checking before register allocation 
 */
static void chk_insns_2memrefs(struct flowg_t *fgp)
{
 struct insn_t *ip, *ip2;
 struct amode_t *srcp, *dstp;
 struct bblk_t *bbp;
 int32 blki;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   /* SJM 12/03/06 - block may already have been removed */
   if (bbp == NULL) continue; 

   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     srcp = &(ip->isrc);
     dstp = &(ip->idst);

     if (srcp->am_tni != -1) dbg_chk_legal_wide_tn(srcp);
     if (dstp->am_tni != -1) dbg_chk_legal_wide_tn(dstp);
    }
  }
}

/*
 * emit a misc terr for illegal tn's - if used wide probably legal
 *
 * know am tni not -1 (i.e. has some tn or not called)
 */
static void dbg_chk_legal_wide_tn(struct amode_t *amp)
{
 struct tn_t *tnp;

 tnp = &(__tntab[amp->am_tni]);
 /* labels, can be wide or not */
 if (tnp->comlab_typ != COMLAB_NONE) return;

 if (tnp->tnwid <= WBITS) return;

 if (__amode_mem_ref(amp))
  {
   if (amp->amode == AM_REG) __misc_terr(__FILE__, __LINE__);
   return;
  }

 /* used wide (possibly child contained inside used wide) */
 if (tnp->tn_used_wide || (tnp->tag_parent_tni != -1
  && __tntab[tnp->tag_parent_tni].tn_used_wide))
  {
   /* used wide legal wide if used in index addr mode */
   if (amp->amode == AM_NDXREG || amp->amode == AM_NDXREG_DISP) return; 
  }
 /* SJM 11/15/06 - any tn that is a ptr to a wide will have the width */
 /* of the pointed to object although its value is the addr so good */
 if (tnp->tn_typ == TN_ADR) return;

 __misc_terr(__FILE__, __LINE__);
}

/*
 * set an amode to a register if it has one assigned
 * also set wide tmp spilled area
 */
static void try_set_amode_to_reg(struct amode_t *amp)
{
 struct tn_t *tnp;

 if (amp->am_tni == -1) return;

 tnp = &(__tntab[amp->am_tni]); 

 /* if this is a com label, can't set amode to a reg or a spill */
 if (tnp->comlab_typ != COMLAB_NONE) return;

 /* fixed x86 reg */
 if (amp->am_tni <= HIGH_X86_REG)
  {
   amp->x86_regno = amp->am_tni;
  }
 /* assigned a x86 reg */
 else if (tnp->tn_assigned)
  {
   /* DBG remove -- */
   if (tnp->tn_spilled) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   amp->x86_regno = tnp->x86_regno;
  }
 /* else if used in wide context no fixup so lower here */
 else if (tnp->tn_used_wide || tnp->tn_spilled)
  {
   /* DBG remove -- */
   if (tnp->tn_used_wide && !tnp->tn_spilled)
    __misc_terr(__FILE__, __LINE__);
   /* --- */

   set_amode_ebp_disp(amp->am_tni, amp);
  }
 else __case_terr(__FILE__, __LINE__);
}

/*
 * set a tmp name amode to its actual x86 offset on the stack 
 * convert to x86 reg %ebp  
 *
 * this just handles AM REG and AM REG OFS but not the 2 index amodes
 *
 * SJM 10/11/06 - all offset now bytes - converted to words when needed
 */
static void set_amode_ebp_disp(int32 tni, struct amode_t *amp)
{
 size_t area_ofs, spill_ebp_ofs;

 /* amode displacement relative to the tn's ebp location (bottom grows up) */
 if (amp->amode == AM_NDXREG_DISP || amp->amode == AM_NONREG_OFS
  || amp->amode == AM_IDP_ADR_OFS)
  { 
   area_ofs = amp->disp;
  }
 else area_ofs = 0;

 amp->amode = AM_NDXREG_DISP;
 amp->x86_regno = AR_SP;

 /* SJM 10/17/06 - need to set am tni since no longer done in asm lnk */
 /* AIV 04/12/07 - better always be ebp */
 amp->am_tni = AR_SP;

 /* SJM 11/08/06 - ebp ofs is the offset for this tn in the ebp area */
 /* if there is a parent tni, then the offset is the parents ebp byte offset */
 /* plus the child's tag offset (amount of any combined addr add chain) */ 
 spill_ebp_ofs = __calc_ebp_spill_offset(tni, area_ofs);

#ifdef STACK_GROWS_DOWN
 /* SJM - 11/08/06 - must fix for non x86 upward growing stack */
 /* DBG remove -- */
 if (spill_ebp_ofs >= 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */
#endif 
 amp->disp = spill_ebp_ofs;
}

/*
 * calculate the spill ebp byte offset - know spilled into ebp area 
 *
 * SJM 11/08/06 - new algorithm - for wides that always spill the ebp area
 * byte offset is only set in the parent - for chains of adradd tn's,
 * each points to the original parent and for any tn, the tag parent tni
 * must be used to calculate the location of the wide non parent tn
 *
 * narrow spilled, do not have parent tns so can just used the
 * spill ebp byte offset
 *
 * see map to downward growing routines but in cvc all spill variable
 * ebp stack area offsets are positive starting at botton growing upward
 * but X86 stack area grows downward under %ebp pointed to addr
 */
extern size_t __calc_ebp_spill_offset(int32 tni, size_t area_ofs)
{
 size_t child_ofs, amdisp; 
 struct tn_t *tnp, *partnp;

 tnp = &(__tntab[tni]); 
 /* if parent (inside a wide area) or a simple spill, tag parent must be -1 */ 
 /* DBG remove -- */
 if (tnp->tag_parent_tni == -1)
  {
   if (tnp->child_tag_offset != 0) __misc_terr(__FILE__, __LINE__);
   if (tnp->spill_ebp_byt_ofs < 0) __misc_terr(__FILE__, __LINE__);
  }
 /* --- */ 

 /* results of addr adds become children tags of the parent (master) */
 /* and only parents (top of chain) have spill ebp byte offsets set */
 if (tnp->tag_parent_tni != -1) partnp = &(__tntab[tnp->tag_parent_tni]); 
 else partnp = tnp;

 /* child tag offset can be -1 in two ways, either because parent or */
 /* because child 0 offset from parent */
 if (tnp->child_tag_offset != 0) child_ofs = tnp->child_tag_offset; 
 else child_ofs = 0;

 /* AIV - don't think this ever happens but checking for now */
 /* DBG remove -- */
 if (partnp->srtyp == SR_CINT)
  {
   if (child_ofs != 0 || area_ofs != 0) __misc_terr(__FILE__, __LINE__);
  }
 /* ---- */
#ifdef STACK_GROWS_DOWN
 {
  word32 byte_ofs;

  byte_ofs = WRDBYTES*__get_lowered_tmp_size(partnp);
  amdisp = -((partnp->spill_ebp_byt_ofs + byte_ofs) - child_ofs) + area_ofs;
 }
#else
 amdisp = partnp->spill_ebp_byt_ofs + child_ofs + area_ofs;
#endif
 return(amdisp);
}

/* 
 * analysis 2 mem ref instructions into types and return the type
 * so other routine can insert and modify the insns
 *
 * only called if know insn has 2 memref operands 
 *
 * this routine assumes neither amode is a COMLAB since can be peeled off
 * as a speical case
 */
static int32 determine_2memref_class(struct insn_t *ip)
{
 int32 src_base_reg, dst_base_reg, rval;
 struct amode_t *srcp, *dstp;
 struct tn_t *srctnp, *dsttnp;

 srcp = &(ip->isrc);
 dstp = &(ip->idst);
 srctnp = &(__tntab[srcp->am_tni]);
 dsttnp = &(__tntab[dstp->am_tni]);

 /* DBG remove -- */
 if (srctnp->comlab_typ != COMLAB_NONE) __misc_terr(__FILE__, __LINE__); 
 if (dsttnp->comlab_typ != COMLAB_NONE) __misc_terr(__FILE__, __LINE__); 
 /* --- */

//special expanded but spilled souce case
 /* AIV 12/03/08 - if 32-bit args are expanded and passed on the stack */
 //AIV LOOKATME -  amount <= for passed args using fix 20 for now
 //need a define max num args passed
 /* AIV 08/02/10 - removed dstp->disp <= 20 - no reason for it */
 /* plus DPI can now be called with many arguments */
 /* AIV 08/02/10 - DPI for 64-bit may spill with > 6 args passed */
 /* so this needs to be done for 64-bit code as well */
 if (srctnp->tn_spilled && dstp->am_tni == AR_SP && 
     dstp->amode == AM_NDXREG_DISP)
  {
   rval = MR2_SPILL_X86NDX;
   return(rval);
  }

 src_base_reg = REG_NONE;
 if (srctnp->tn_spilled) src_base_reg = AR_SP;
 else if (srcp->amode == AM_NDXREG || srcp->amode == AM_NDXREG_DISP)
  {
   /* DBG remove --- */
   /* AIV 06/20/07 - register can now be the idp register (esi) */
   /* AIV 11/16/09 - this should just check > HIGH_MACH_REG not just idp */
   if (!srctnp->tn_assigned && srcp->am_tni > HIGH_MACH_REG) 
     __misc_terr(__FILE__, __LINE__);
   /* --- */
   src_base_reg = srctnp->x86_regno;
  }
 else __case_terr(__FILE__, __LINE__);

 dst_base_reg = REG_NONE;
 if (dsttnp->tn_spilled) dst_base_reg = AR_SP;
 else if (dstp->amode == AM_NDXREG || dstp->amode == AM_NDXREG_DISP)
  {
   /* DBG remove --- */
   /* AIV 06/20/07 - register can now be the idp register (esi) */
   /* AIV 11/16/09 - this should just check > HIGH_MACH_REG not just idp */
   if (!dsttnp->tn_assigned && dstp->am_tni > HIGH_MACH_REG) 
     __misc_terr(__FILE__, __LINE__);
   /* --- */
   dst_base_reg = dsttnp->x86_regno;
  }
 else __case_terr(__FILE__, __LINE__);

 rval = MR2_UNKN;
 switch (srcp->amode) {
  case AM_REG:
  case AM_NONREG_OFS:
   /* case 1: src amode is a reg can only be spilled reg */ 
   switch (dstp->amode) {
    case AM_REG:
    case AM_NONREG_OFS:
     /* movl -12(%ebp), -44(%ebp) */ 
     /* AIV 11/29/06 - multiple cannot take any memory operands */
     /* AIV LOOKATME - make this a part of the insn table info */
     /* imull is only insn for now */
     if (ip->opcod == I_IMULL) rval = MR2_SPILL_SPILL_NOMEM;
     else rval = MR2_SPILL_SPILL;
     break;
    case AM_NDXREG: case AM_NDXREG_DISP:
     if (dst_base_reg == AR_SP)
      {
       /* dest spilled ndx reg */
       /* movl -12(%ebp), 12(-44(%ebp)) */ 
       rval = MR2_SPILL_SPILLNDX;
      }
     else
      {
       /* dest is an index reg that did not spill */       
       /* movl -12(%ebp), 12(%esi)) */ 
       rval = MR2_SPILL_X86NDX;
      }
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
   break;

   case AM_NDXREG: case AM_NDXREG_DISP:
    /* case 2: src amode is ndx reg - can be spilled or x86 ndx addr mode */
    switch (dstp->amode) {
     case AM_REG: case AM_NONREG_OFS:
      if (src_base_reg == AR_SP)
       {
        /* movl 8(-12(%ebp)), -44(%ebp) */ 
        rval = MR2_SPILLNDX_SPILL;
       }
      else
       {
        /* movl 8(%esi), -44(%ebp) */ 
        rval = MR2_X86NDX_SPILL;
       }
      break;
     case AM_NDXREG: case AM_NDXREG_DISP:
      /* case 2b: both src and dst index regs */
      if (src_base_reg == AR_SP)
       {
        if (dst_base_reg == AR_SP)
         {
          /* both src and dst spilled ndx regs */ 
          /* movl 24(-12(%ebp)), 12(-44(%ebp)) */ 
          rval = MR2_SPILLNDX_SPILLNDX;
         }
        else
         {
          /* src spilled ndx reg - dst x86 index addr mode */
          /* movl 12(-12(%ebp)), 8(%esi) */
          rval = MR2_SPILLNDX_X86NDX;
         }
       }
      else
       {
        if (dst_base_reg == AR_SP) 
         {
          /* src x86 ndx reg - dst spilled index addr mode */
          /* movl 8(%esi)), 12(-44(%ebp)) */
          rval = MR2_X86NDX_SPILLNDX;
         }
        else
         {
//AIV? - LOOKATME can this happen?
          /* src x86 ndx reg - dst x86 ndx reg */
          /* movl 8(%esi)), 12(%edi)) */
          rval = MR2_X86NDX_X86NDX;
         }
       }
      break;
     default: __case_terr(__FILE__, __LINE__);
    }  
   break;
  }
 return(rval);
}


/*
 * final optimize insn re-arrangement routine
 *
 * only changes after here are linerizing insns from bblks into flowg
 * linear list and change to byte/hword insns
 */
static void peep_hole_optimize(struct flowg_t *fgp)
{
 int32 blki;
 struct bblk_t *bbp;
 struct insn_t *ip, *ip2, *prev_ip, *new_ip;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   /* SJM 12/03/06 - block may already have been removed */
   if (bbp == NULL) continue; 

   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     /* try to conver a movl $0, %eax => xorl %eax, %eax */
     if (try_convert_mov0_reg_to_xor(ip)) continue;

     /* AIV 11/30/06 - linkout movl %eax, %eax insn */
     /* AIV FIXME - REMOVEME - reg alloc should handle doing here for now */
     /* leaving for now until register coalescing in done */
#ifdef __CVC32__
     if ((ip->opcod == I_MOVA || ip->opcod == I_STOREA
        || ip->opcod == I_MOVB || ip->opcod == I_STOREB
        || ip->opcod == I_MOVW || ip->opcod == I_STOREW)
      && (ip->isrc.amode == AM_REG && ip->idst.amode == AM_REG)
      && (ip->isrc.x86_regno == ip->idst.x86_regno)
      && (ip->isrc.x86_regno >= AR_AX))
#else
     /* AIV 08/03/10 - added new movl for 64-bit */
     if ((ip->opcod == I_MOVA || ip->opcod == I_STOREA
        || ip->opcod == I_MOVB || ip->opcod == I_STOREB
        || ip->opcod == I_MOVW || ip->opcod == I_STOREW
        || ip->opcod == I_MOVQL || ip->opcod == I_STOREQL)
      && (ip->isrc.amode == AM_REG && ip->idst.amode == AM_REG)
      && (ip->isrc.x86_regno == ip->idst.x86_regno)
      && (ip->isrc.x86_regno >= AR_AX))
#endif
      {
       __linkout_insn(ip, TRUE);
       continue;
      }
 
//AIV 11/06/06 - should this really be a peephole optim making illegal assembly
//good - it should never be generated ???????
     if (ip->opcod != I_MOVZBL && ip->opcod != I_MOVSBL 
         && ip->opcod != I_MOVZWL) continue; 

     if (ip->isrc.amode == AM_REG && ip->isrc.x86_regno <= HIGH_MACH_REG)
      {
       if (ip->idst.amode == AM_NDXREG_DISP && ip->idst.x86_regno == AR_SP)
        {
         if (ip->isrc.x86_regno == OFLW_REG)
          {
           prev_ip = ip->iprev;
           /* DBG remove --- */
           if (prev_ip == NULL) __misc_terr(__FILE__, __LINE__);
           if (prev_ip->opcod != I_MOVA && prev_ip->opcod != I_STOREA)
            __misc_terr(__FILE__, __LINE__);
           /* --- */
           prev_ip->opcod = ip->opcod;
           ip->opcod = I_MOVA;
          }
         /* shrb  %cl, %al  */
         /* movzbl %al, -12(%ebp) */
         /* =>shrb %cl, %al */
         /* =>movzbl %al, %ecx */
         /* =>movl %ecx, -12(%ebp) */
         else
          {
           new_ip = __insert_insn(ip, TRUE, I_MOVA, AM_REG, OFLW_REG,
            AM_NDXREG_DISP, ip->idst.am_tni, 0UL);
           __copy_amode(&(new_ip->idst), &(ip->idst));
           ip->idst.amode = AM_REG;
           ip->idst.am_tni = OFLW_REG;
           ip->idst.x86_regno = OFLW_REG;
          }
        }
      }
    }
  }
 /* AIV 02/03/09 - try to change common vec to scalar insns */
 /* convert instructions to optimized leal */
 /* this must be done after the optimizations in the first loop */
 /*
 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   if (bbp == NULL) continue; 

   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     if (try_convert_vec_to_scalar(ip) != NULL)
      {
       ip2 = ip->inxt;
      }
     }
   }
 */
 __cur_bbp = NULL;
}
     
/*
 * try to convert 
 * movl $0, %eax
 * => xorl %eax, %eax
 * return TRUE if it does the conversion
 */
static int32 try_convert_mov0_reg_to_xor(struct insn_t *ip)
{
 struct amode_t *srcp, *dstp;
 struct tn_t *tnp;
 int32 xvi; 
 word32 cval;

 if (ip->opcod == I_MOVA || ip->opcod == I_STOREA) 
  {
   srcp = &(ip->isrc);
   dstp = &(ip->idst);
   /* souce has to be 0 and dest a regular register */
   if (srcp->am_tni != -1 && dstp->amode == AM_REG 
       && dstp->x86_regno != REG_NONE)
    {
     tnp = &(__tntab[srcp->am_tni]);
     cval = -1;
     if (tnp->comlab_typ == COMLAB_CINT)
      {
       cval = tnp->tncu.tn_cint; 
      }
     else if (srcp->amode == AM_NDXREG && tnp->comlab_typ == COMLAB_CONADR)
      {
       xvi = __get_con_adradd_xvi(srcp->am_tni);
       cval = __contab[xvi]; 
      }
     if (cval == 0)
      {
       ip->opcod = I_XORL;
       *srcp = *dstp;
       return(TRUE);
      }
    }
   /* AIV 08/05/10 - if zero of AMODE AM_IMM immediate zero can should */
   /* aslo make this an xorl reg, reg */
   if (srcp->amode == AM_IMM && dstp->amode == AM_REG 
       && dstp->x86_regno != REG_NONE)
    {
     if (srcp->disp == 0)
      {
       ip->opcod = I_XORL;
       *srcp = *dstp;
       return(TRUE);
      }
    }
  }
 return(FALSE);
}

/*
 * convert the following common case which is a conversion of a vector
 * into a scalar - return NULL if no conversion is done
 *
 *  this takes advantage of the fact that the a/b can be added
 *
 *  notice the shrl has been converted to a addl to itself here
 *  addl	%ebx, %ebx
 *  orl	%ebx, %eax
 *
 *  leal	(%ebx,%eax,2), %eax
*/
static struct insn_t *try_convert_vec_to_scalar(struct insn_t *ip)
{
 struct amode_t *srcp, *dstp;
 struct insn_t *next_ip;

 /* AIV 02/04/09 - no need for flag just check for specific pattern */
 /* was missing a bunch of places to mark the flag so this is better */
 /* must be an addl to itself */
 if (ip->opcod != I_ADDL) return(NULL);

 next_ip = ip->inxt;
 /* next insn must be the orl */
 if (next_ip == NULL || next_ip->opcod != I_ADDL) return(NULL);
 srcp = &(ip->isrc);
 /* this must be assigned register for this to work */
 if (srcp->x86_regno == REG_NONE) return(NULL);
 dstp = &(ip->idst);
 /* must be an addl to itself - which is a shiftl by one */
 if (srcp->x86_regno != dstp->x86_regno) return(NULL);

 if (srcp->amode != AM_REG || dstp->amode != AM_REG) return(NULL); 

 dstp = &(next_ip->idst);
 if (dstp->x86_regno == REG_NONE) return(NULL);

 if (srcp->x86_regno == dstp->x86_regno) return(NULL);
 srcp = &(next_ip->isrc);

 /* AIV 04/05/10 - srcp must be a reg as well - can be const here */
 if (srcp->x86_regno == REG_NONE) return(NULL);
 /* can have two shifts in a row which are turned into two addl */
 if (srcp->x86_regno == dstp->x86_regno) return(NULL);

 if (dstp->amode != AM_REG) return(NULL); 

 /* offsets better to zero */
 /* DBG remove -- */
 if (srcp->disp > 0 || dstp->disp > 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* make it a leal with the special amode to indicate leal double offset 2 */
 next_ip->opcod = I_LEAL;
 next_ip->isrc.amode = AM_NDXREG_DBL;
 next_ip->isrc.x86_regno = srcp->x86_regno;
 next_ip->isrc.disp = dstp->x86_regno;

 __linkout_insn(ip, TRUE);
 return(next_ip);
}
