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
 * file to generate new x86/alpha style procedural instructions and flow graph
 * basic blocks for procedural code (also declares cvc vars and has top 
 * level driver)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <stdarg.h>
#include <dlfcn.h> 
#include <unistd.h> 

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

/* variables tmp name locations (vars and consts also tmps) */
struct tn_t *__tntab; /* design wide (?) tmp name table */
size_t __tntabsiz;   /* current size */         
int32 __tntab_nxti; /* next location to use */
struct avlhd_t **__formal_tmptab;/* array index by vinsn of tmps */
int32 *__nlo_tn_used; /* table so use same NLO tn if num same */
struct avlhd_t *__adradd_child_tree;/* adradd child tree */

/* avl tree (set) hdr tress to make sure only one tn per/mod NL object */
struct avlhd_t *__stmt_dup_tn_tree;
struct avlhd_t *__netadr_sydup_tn_tree;
struct avlhd_t *__netparambp_sydup_tn_tree;
struct avlhd_t *__cint_dup_tn_tree;
struct avlhd_t *__contab_dup_tn_tree;
struct avlhd_t *__np_iconn_dup_tn_tree;
struct avlhd_t *__gate_conta_dup_tn_tree;

int32 __rev_po_ndx; /* for reverse post order nums - current ndx */
int32 __enter_bblk_valnum; /* value number at start of cur bblk */
int32 __cur_valnum; /* current highest used value number */
struct bblk_t *__dum_fg_ent_bbp;/* dummy bblk for fg enter back edges */
struct bblk_t *__loop_continue_bbp; /* loop continue block */
struct bblk_t *__loop_break_bbp;    /* loop break block */

struct bblklst_t *__cur_dom_fron_todos; /* dom frontier wrd list hd */
struct bblklst_t *__cur_dom_fron_tail; /* and tail for add to end */
int32 *__insn_order_ndx; /* bblk rpo index sort tab for ip to bblk map */

/* mod flow graph variables */
struct flowg_t *__proc_flowg_hd; /* hd of cur gen list of flow graphs */
struct flowg_t *__proc_flowg_tail; /* and its tail */
struct flowg_t *__cur_flowg;  /* current being gened flow graph */
struct flowg_t **__flowgtab; /* work array of ptrs to flowgs in mod */
size_t __flowgtabsiz;   /* current size */ 
int32 __flowg_lasti;   /* next use location */       
struct bblk_t **__ndxjmp_bbtab; /* tab of bblk ptrs for ndx jumps */
size_t __ndxjmp_bbtab_siz;/* current table size */
int32 __jmplab_nxti;   /* current jmp label number */
int32 *__jmpbase;      /* tab of jump bases for per inst ndx jumps */
size_t __jmpbas_tabsiz; /* current allocated size of jmp base tab */
struct bblk_t **__bblktab; /* work array of ptrs to bblks */
size_t __bblktabsiz;    /* current size */
int32 __bblk_lasti;    /* last used bblk index */ 
struct nb_stmt_lst_t *__nb_stmt_hd; /* non-blocking stmt head */
struct nb_stmt_lst_t *__nb_stmt_cur;/* last non-blocking stmt */
int32 __need_reg_tns;  /* T => use x86 reg for tn sets and fuds */
struct pd_rhs_lst_t *__pd_rhs_stmt_hd; /* proc rhs del stmt head */
struct pd_rhs_lst_t *__pd_rhs_stmt_cur;/* proc rhs del stmt cur */

/* variables for storing bblk information (property trees?) */
int32 __cur_mark;      /* for keeping track of current marking step */

/* basic block variables */
struct bblk_t *__cur_bbp; /* cur being filled basic block ptr */  
struct bblk_t *__enter_bbp;/* entry (1st) bblk in flow graph */
struct bblklst_t *__last_alloc_bblst; /* last allocated bblk list el */
union ifrom_u __cur_ifrom_u; /* statement or net v insn from */ 
struct insn_t *__cur_ip;   /* cur being lowered to insn ip */
int32 __push_count;        /* number of variables push to wrap call */

int32 __nxt_lab;       /* counter for creating local insn lab nums */
int32 __enter_seq_no;  /* counter for creating lab numbers */
int32 __enter_dce_seq_no; /* counter for creating enter dce numbers */
int32 __dce_no;        /* counter for creating dce numbers */
int32 __bblk_seq_no;   /* counter for creating basic block nums */ 
word32 __flowg_seq_no;  /* counter for creating flow graph nums */ 
int32 __iconn_seq_no;  /* counter for creating iconn ident nums */ 
int32 __gate_conta_seq_no; /* counter for creating scalar conta nums */ 
struct insn_t *__copy_ip; /* the current copy insn to xpnd from */
struct bblk_t *__func_complete_bbp; /* func comp bbp n case of disable */
int32 __need_net_addr;       /* need to generate net address flag */

char **__thdjmp_ret_tab;  /* jump thru current thd dynamic lnk labels */
int32 __thdjmp_siz;    /* growing tab size and next to use */
int32 __thdjmp_nxti;

struct gate_da_list_t *__hd_gdap; /* head date del assgn struct list */
struct gate_da_list_t *__tail_gdap; /* tail date del assgn struct list */

int32 __removed_bblks; /* number of removed basic blocks */ 
int32 __num_asm_insn;  /* num of asm insn */
int32 __removed_asm_insns;  /* removed num of asm insn */
int32 __trk_num_insn_removed; /* tracking - per bblk no. insn removed */
int32 __trk_num_insn_changed; /* and changed */
int32 __gening_mdc;    /* gening merged always blocks */
int32 __num_print_asm_insn;  /* number of asm insn printed */
struct st_t *__generating_stp; /* current genned stp */
 
int32 **__decomposed_tn_nums; /* decompose wide tmps into word tmps wrk area */

char **__mod_file_names;   /* module tmp file names */
char **__comm_nt_file_names; /* comm init file names - one per module */
char *__comm_file_name;    /* comm file name */
char *__exe_file_name;     /* exe main file name */
char *__cvclib_file_name;  /* cvclib file name */
int32 __idp_ti;             /* per module idp storage area tmp */
word32 __cvc_slotend_action; /* switches for possbile slot end action */
int32 __known_inum; /* for ports to indicate known inum value */
int32 __design_has_nb_events; /* design has nb events */
int32 __design_has_nb_del_events; /* design has nb with delay events */
char __asm_file_name[RECLEN];/* assembly file name */
int32 __asm_pipefd[2];       /* assembly pipe fds */
pid_t __asm_pid;             /* assembly pipe pid */
void  *__asm_stack;          /* assembly clone pipe stack */
#ifdef __CVC32__
va_list  __advance_seta_va; /* global to reset advance of varargs */
#endif

/* local prototypes */
static void gen_asm_insns_for_all_mods(void);
static void dmp_verbose_mem_info(struct mod_t *, long, int32);
static void init_cvc(void);
static void set_asm_file_names(int32);
static void init_one_mod_cvc(void);
static void free_dsgn_cvc_storage(void); 
static void gen_x86reg_tn(int32);
static void bld_mod_proc_flowgraphs(struct mod_t *);
static void bld_delctrl_merged_fgs(struct mod_t *);
static void grow_tntab(void);
static struct ctev_t *get_merged_dctp_ctev(struct delctrl_t *);
static void bld_delctrl_head_fg(struct delctrl_t *);
static void gen_nb_assigns(int32);
static void gen_nb_assign_varndx(struct expr_t *, int32);
static void gen_initalways(struct ialst_t *);
static void gen_funcbody(struct task_t *);
static void save_task_scope(struct task_t *);
static void restore_task_scope(void);
static void gen_tskbody(struct task_t *);
static void gen_tskbody_export_dpi(struct task_t *);
static void gen_stlst(struct st_t *, int32);
static struct st_t *gen_stmt(struct st_t *, int32);
static void gen_proc_assign(struct expr_t *, struct expr_t *, int32);
static void gen_proc_assign_string(struct expr_t *, struct expr_t *);
static void gen_proc_assign_const_to_id(struct expr_t *, struct expr_t *);
static void gen2_proc_assign(struct expr_t *, int32);
static void gen_stmt_inc_dec(struct st_t *, int32);
static int32 gen_inc_dec(struct expr_t *, int32, int32, int32);
static int32 gen_real_inc_dec(struct expr_t *, int32, int32, int32, int32);
static void gen_qcaf_assgn_to_regbit(struct expr_t *, int32);
static void gen_assgn_to_regbit(struct expr_t *, int32); 
static void gen_assgn_to_regpsel(struct expr_t *, int32);
static void gen_assgn_to_index_width_psel(struct expr_t *, int32, int32, int32);
static void gen_st_indexed_width_psel(int32, int32, int32, int32, int32, int32,
 int32);
static void gen_reg_qcaf_tstjmp(struct net_t *, struct bblk_t *, int32); 
static int32 cat_need_rhs_eval2(struct expr_t *, struct expr_t **, int32, 
 int32); 
static void gen_chg_st_vecval(struct net_t *, int32, int32);
static void gen_chg_st_vecval_1w(struct net_t *, int32, int32);
static void gen_chg_st_vecval_2state(struct net_t *, int32, int32);
static void gen_chg_st_scalval(struct net_t *, int32, int32);
static void gen_assgn_to_arr(struct expr_t *, int32);
static void gen_lhs_arrsel(struct expr_t *, int32, int32, int32, int32,
 struct expr_t *, int32);
static int32 gen_st_array_element_select(struct net_t *, struct expr_t *,
 int32, int32, int32, int32, int32);
static int32 gen_array_pck_element_select(struct net_t *, struct expr_t *, 
 int32, int32, int32, int32);
static int32 gen_ndxarr_ptr_var(struct net_t *, int32, int32);
static int32 gen_ndxarr_ptr_const(struct net_t *, int32, int32);
static int32 gen_pck_ofset_var(struct net_t *, int32);
static int32 gen_pck_ofset_const(struct net_t *, int32);
static void gen_chg_st_unpck_arr_val(struct net_t *, int32, int32, int32,
 int32, int32);
static void gen_st_scalar_lhs_arrsel_var(struct expr_t *, int32, int32,
 int32);
static void gen_st_scalar_lhs_arrsel_const(struct net_t *, int32, int32, 
 int32);
static void gen_st_scalar_lhs_arrsel_is_const(struct net_t *, int32, int32, 
 int32);
static void gen_chg_st_pck_arr_val(struct net_t *, int32, int32, int32,
 int32, int32);
static int32 gen_wbyti_bofs(int32, int32 *, int32);
static int32 gen_scalarr_wbyti_bofs(int32 *, int32);
static int32 gen_bld_varmask(int32, int32, int32); 
static int32 bld_pck_nwval(struct net_t *, int32, int32);  
static int32 gen_getbit(int32, int32, int32); 
static int32 comp_ndxwrd_addr(int32, int32);
static void gen_chg_lhsbsel_var(struct net_t *, int32, int32, int32);
static void gen_chg_lhsbsel_const(struct net_t *, int32, int32, int32);
static void gen_lhsbsel_const_norecord(struct net_t *, int32, int32, int32);
static void gen_chg_stren_lhsbsel(struct net_t *, int32, int32, int32,
 int32, int32);
static void gen_lhs_concat(struct expr_t *, struct expr_t **, int32, int32);
static void gen_lhs_concat2(int32, struct expr_t **, int32, int32);
static int32 gen_rhs_concat_range(int32, int32, int32, int32);
static void gen_rhs_assgn_concat(struct expr_t *, struct expr_t **, int32);
static int32 gen_cat_to_cat_match(struct expr_t *, struct expr_t **, int32,
 struct expr_t *, struct expr_t **, int32);
static int32 cat_need_rhs_eval(struct expr_t **, int32, struct expr_t **,
 int32); 
static void gen_nblkrhs_proca(struct st_t *, struct expr_t *, int32);
static void gen_nb_nodelay_tev(int32);
static void set_nonblocking_fg_num_to_ctev(struct ctev_t *, struct st_t *);
static void add_non_blocking_stmt(struct st_t *, int32, int32, int32, int32,
 int32);
static void gen_rhs_dctl_proca(struct st_t *);

static void gen_if_stmt(struct st_t *);
static int32 gen_bin_cvt_bool(int32, int32);
static word32 fold_constant_bin_cvt_bool(int32, int32, int32, int32 *);
static void gen_case(struct st_t *);
static void fnd_case_sizes(struct st_t *, int32 *, int32 *);
static void fill_castabs(struct st_t *, struct icas_t *, struct icasx_t *);
static void init_icas(struct icas_t *);
static void init_icasx(struct icasx_t *);
static int32 fold_casx_vals(struct icasx_t *, int32 *); 
static int32 igen_xpr_hasfcall(struct expr_t *);
static int32 has_duplicated_cases(struct icasx_t *);
static void get_casxpr_minmax(struct icasx_t *, word32 *, word32 *); 
static int32 get_xzcas_maxwid(struct icasx_t *);
static void gen_xzjmptab_case_select(struct st_t *, struct icas_t *,
 struct icasx_t *, int32, struct csitem_t *, int32, int32);
static void gen_jmptab_case_select(struct st_t *, struct icas_t *,
 struct icasx_t *, int32, struct csitem_t *, word32, word32, int32);
static void gen_list_case_select(struct st_t *, struct icas_t *,
 struct icasx_t *, int32, struct csitem_t *, int32, int32, int32);
static void gen_real_list_case(struct st_t *, struct icas_t *,
 struct icasx_t *, int32, struct csitem_t *);
static void gen_list_case(struct st_t *, struct icas_t *,
 struct icasx_t *, int32, struct csitem_t *, int32, int32, int32);
static int32 gen_eval_case_sel(int32, int32, int32, int32, struct st_t *); 
static int32 gen_eval_wide_case_sel(int32, int32, int32, int32);
static int32 gen_eval_casex_sel(int32, int32, int32, struct st_t *); 
static int32 gen_eval_casez_sel(int32, int32, int32, struct st_t *); 
static void gen_repeat(struct st_t *);
static void gen_forever(struct st_t *);
static void gen_repsetup(struct st_t *);
static void gen_num_repsetup(struct st_t *stp);
static void gen_while(struct st_t *);
static void gen_while_const(struct st_t *);
static void gen_do_while(struct st_t *);
static void gen_do_while_const(struct st_t *);
static void gen_for(struct st_t *);
static void gen_wait(struct st_t *);
static struct st_t *gen_dctl_stmt(struct st_t *);
static struct st_t *gen_blking_dctl_ectl(struct st_t *);
static void gen_sched_proc_del(struct st_t *, struct st_t *);
static void gen_rhs_dctl_ectl(struct st_t *);
static struct st_t *gen_nb_dctl_ectl(struct st_t *, struct expr_t *, int32);
static int32 gen_nb_arm_varndx(struct expr_t *, int32, struct st_t *, int32, 
 int32, int32, int32);
static void  gen_nb_lhs_varndx(struct st_t *, struct expr_t *, struct ctev_t *, 
 int32, int32, int32, int32);
static void  gen_nb_onelhsx_varndx(struct expr_t *, int32, int32, int32, 
 int32, int32);
static void  gen_nb_onelhsx_varndx_concat(struct expr_t *, int32, int32, 
 int32, int32, int32);
static int32 gen_nb_varndx_value(struct net_t *, struct expr_t *, 
 struct bblk_t *);
static void gen_rep_ectl_setup(struct st_t *);
static struct st_t *gen_namblk(struct st_t *);
static void gen_unfj(struct st_t *);
static void gen_tskcall(struct st_t *);
static void gen_tskcall_dpi(struct st_t *);
static void gen_assign_dpi_outputs(struct expr_t *, struct task_pin_t *, 
  int32 *, int32 *);
static int32 gen_arg_dpi(struct net_t *, int32 *, struct expr_t *, int32 *, 
 int32 **, int32, int32, int32 *);
static int32 gen_jmpto_tsk(struct sy_t *);
static int32 gen_jmpto_func_dsabl(struct sy_t *);
static void grow_thdjmp_tab(void);
static void gen_st_tf_ins(struct st_t *, int32, struct gref_t *);
static void gen_st_one_tfins(struct net_t *, struct expr_t *, int32,
 struct mod_t *);
static void gen_st_tf_outs(struct st_t *, int32, struct mod_t *);
static void gen_st_one_tfouts(struct net_t *, struct expr_t *, int32,
 struct mod_t *);
static int32 cnvt_tskassgn_rhsexpr_ifneed(int32, struct net_t *, int32, int32);
static void gen_qconta(struct st_t *);
static void gen_qconta_one_lhsx(struct st_t *, int32, struct expr_t *, int32);
static void gen_qcontdea(struct st_t *);
static void gen_qcontdea_one_lhsx(struct st_t *, struct expr_t *, int32);
static void gen_cause(struct st_t *);
static struct st_t *gen_disable(struct st_t *);
static int32 gen_comp_ndx_range(struct net_t *, struct expr_t *, int32, int32, 
 int32, struct bblk_t *);

static int32 gen_ld_nonis_vecvaradr(struct net_t *); 
static int32 gen_ld_is_apart_baseadr(struct net_t *np, struct gref_t *);
static int32 gen_sel_string(struct expr_t *);
static int32 gen_bsel(struct expr_t *, int32);
static int32 gen_bsel_const(struct expr_t *, int32);
static int32 gen_arrsel(struct expr_t *);
static int32 gen_rhs_arr_select(struct expr_t *, struct net_t *, int32);
static void gen_ab_setx(int32, int32);
static void gen_oneword_setx(int32);
static int32 gen_rhs_arrsel_var(struct net_t *, int32, int32);
static int32 gen_comp_mda_ndx(struct net_t *, struct mda_t *, struct expr_t *, 
 struct bblk_t *, struct expr_t **);
static int32 gen_one_dim_mda_ndx(struct net_t *, struct mda_t *, 
 struct expr_t *, int32, struct bblk_t *);
static int32 gen_rhs_arrsel_const(struct net_t *, int32, int32);
static int32 gen_ld_scalar_arrsel_var(struct net_t *, int32, int32);
static int32 gen_ld_scalar_arrsel_const(struct net_t *, int32, int32);
static int32 gen_rhs_psel(struct expr_t *, int32);
static int32 gen_rhs_index_width_psel(struct expr_t *);
static void gen_rhs_iw_psel(int32, int32, int32, int32, int32, int32, int32);
static int32 get_indexed_psel_range(int32 *, int32 *, word32 *, int32, 
 struct expr_t *, struct net_t *, struct bblk_t *, int32);
static void gen_ld_unaligned_rhs_psel(int32, int32, int32, int32, int32, 
 int32); 
static void gen_in1wrd_st_psel(int32, int32, int32, int32, int32, int32);
static void gen_ld_unaligned_st_psel(int32, int32, int32, int32, int32, int32);
static int32 gen_in1wrd_rhs_psel(int32, int32, int32, int32);
static int32 gen_onewrd_bound_rhs_psel(int32, int32, int32, int32, int32);
static void gen_wordalign_rhs_psel(int32, int32, int32, int32, int32);
static void gen_wordalign_st_psel(int32, int32, int32, int32, int32);
static int32 gen_onewrd_cross_rhs_psel(int32, int32, int32, int32);
static int32 gen_rhs_concat(struct expr_t *);
static int32 all_els_not_signed(struct expr_t *);
static int32 gen_rhs_concat_1w(struct expr_t *, int32);
static int32 gen_sysfcall(struct expr_t *);
static int32 gen_random_syscall(struct expr_t *);
static int32 is_1arg_transcendental(int32, int32 *);
static int32 gen_fcall(struct expr_t *, struct st_t *);
static int32 gen_fcall_dpi(struct expr_t *, struct st_t *);
static int32 gen_packed_svLogicVecVal_dpi(struct net_t *, int32, int32, int32);
static int32 gen_packed_svLogicVecVal_array_dpi(struct net_t *, int32, 
 int32 **, int32);
static int32 gen_packed_svLogicVecVal_array_1w_dpi(struct net_t *, int32,
 int32);
static int32 gen_packed_svLogicVecVal_array_1w_packed_dpi(struct net_t *, 
 int32, int32);
static int32 gen_packed_svLogicVecVal_array_real_dpi(struct net_t *, int32,
 int32);
static int32 gen_packed_svLogicVecVal_array_wide_dpi(struct net_t *, int32 **,
 int32, int32);
static int32 gen_packed_svLogicVecVal_array_scalar_dpi(struct net_t *, int32,
 int32);
static void  gen_st_unpacked_svLogicVecVal_array_dpi(struct net_t *, int32,
 int32 *);
static void gen_st_unpacked_svLogicVecVal_scalar_array_dpi(struct net_t *, 
 int32, int32);
static void gen_st_unpacked_svLogicVecVal_packed_array_dpi(struct net_t *, 
 int32, int32);
static void gen_st_unpacked_svLogicVecVal_array_1w_changes_dpi(struct net_t *, 
 int32, int32);
static void gen_st_unpacked_svLogicVecVal_array_wide_dpi(struct net_t *, 
 int32, int32 *);
static void gen_st_unpacked_svLogicVecVal_array_real_dpi(struct net_t *, 
 int32, int32);
static void gen_st_2state_svLogicVecVal_array_dpi(struct net_t *,
 int32, int32);
static int32 gen_unpacked_svLogicVecVal_dpi(struct net_t *, int32);
static int32 gen_qcol(struct expr_t *);
static int32 gen_qcol_2state(struct expr_t *, int32);
static int32 gen_qcol_const(int32, struct expr_t *);
static int32 gen_eval_qcol_oper(struct expr_t *, int32, int32, int32);
static int32 gen_scalar_qcol(struct expr_t *, int32);
static int32 gen_scalar_qcol_leaf(struct expr_t *, int32);
static void gen_lxqcol_comb(int32, int32, int32, int32);
static int32 gen_qcol_leaf(struct expr_t *, int32);
static int32 gen_realselqcol(struct expr_t *);
static int32 gen_regrealqcol(struct expr_t *);

static int32 gen_unop(struct expr_t *);
static int32 gen_unop_2state(struct expr_t *);
static int32 gen_scalar_unop(int32, int32);
static void gen_un_minusop(int32, int32, int32, int32, int32);
static int32 gen_un_bitnot(int32, int32);
static int32 gen_un_logical_not(int32);
static int32 gen_un_logical_not_wide(int32);
static int32 gen_binop(struct expr_t *);
static int32 gen_binop_2state(struct expr_t *, int32, int32, int32, int32, 
 int32);
static int32 gen_scalar_binop(int32, int32, int32, int32, int32);
static int32 gen_try_to_cnvt_scalar_const(int32);
static int32 binop_get_ndwid(int32 *, struct expr_t *);
static int32 gen_bin_arithop(struct expr_t *, int32, int32, int32);
static int32 gen_bin_arithop_2state(struct expr_t *, int32, int32, int32, 
 int32);
static int32 gen_bin_sign_mult(struct expr_t *, int32, int32, int32, int32);
static int32 gen_bin_sign_div(struct expr_t *, int32, int32, int32, int32,
 int32);
static int32 gen_bin_bitredand(struct expr_t *, int32, int32);
static int32 gen_bin_bitredor(int32, int32);
static int32 gen_bin_bitredxor(struct expr_t *, int32, int32);
static int32 gen_bin_bitredxnor(struct expr_t *, int32, int32);
static int32 gen_bin_bitredxnor_2state(struct expr_t *, int32, int32, int32);
static int32 gen_bin_relcomp(struct expr_t *, int32, int32, int32);
static int32 gen_bin_relcomp_wide(struct expr_t *, int32, int32, int32);
static int32 has_contant_xvalue(int32, int32, int32);
static int32 gen_bin_real_relcomp(struct expr_t *, int32, int32);
static int32 gen_bin_neeq(struct expr_t *, int32, int32);
static int32 gen_bin_neeq_2state(struct expr_t *, int32, int32);
static int32 gen_bin_neeq_wide(struct expr_t *, int32, int32, int32);
static int32 gen_bin_cneeq(struct expr_t *, int32, int32);
static int32 gen_bin_booland(struct expr_t *);
static void ifx_setx_else_const(int32, int32, int32);
static int32 gen_bin_booland_2state(struct expr_t *, int32);
static int32 gen_bin_real_booland(struct expr_t *, int32, int32);
static int32 gen_bin_boolor(struct expr_t *);
static int32 gen_bin_boolor_2state(struct expr_t *, int32);
static int32 gen_bin_real_boolor(struct expr_t *, int32, int32);
static int32 gen_bin_notsgn_shift(struct expr_t *, int32, int32, int32, int32);
static int32 gen_bin_notsgn_shift_2state(struct expr_t *, int32, int32, int32, 
 int32);
static int32 gen_bin_notsgn_shift_const(struct expr_t *, int32, int32);
static int32 gen_bin_notsgn_shift_const_2state(struct expr_t *, int32, int32);
static int32 gen_bin_ashiftr(struct expr_t *, int32, int32, int32, int32);
static int32 gen_bin_ashiftr_2state(struct expr_t *, int32, int32, int32, 
 int32);
static int32 gen_bin_ashiftr_const(struct expr_t *, int32, int32);
static int32 gen_bin_ashiftr_const_2state(struct expr_t *, int32, int32);
static int32 need_complete_or_suspend(void);
static int32 gen_bin_sgn_power(struct expr_t *, int32, int32, int32);
static int32 gen_bin_power(struct expr_t *, int32, int32, int32);
static void gen_power_loop(struct bblk_t *, int32, int32, int32, int32, 
 int32, int32); 
static void free_compile_time_structs(void);
static void free_net_comptime_events(struct net_t *);
static int32 gen_push_save_idp(int32);
static void gen_wordalign_hwmask_st_psel(int32, int32, int32, int32, int32);
static void gen_assgn_to_bit_var(struct expr_t *, int32, int32, int32);
static int32 gen_div_real(int32, int32);
static int32 gen_un_bitred_and_wide(int32, int32, int32, int32);

#ifdef __XPROP__
/* xprop routines */
static void gen_xprop_if_stmt(struct st_t *, int32, int32, int32);
static void gen_set_restore_xprop_accum_block(struct st_t *, int32, 
 struct xprop_t *);
static void gen_set_restore_xprop_accum_block_toself(struct st_t *, 
 struct xprop_t *);
static void gen_set_restore_xprop_accum_block_nodefault(struct st_t *, int32,
 int32, struct xprop_t *);
static void gen_set_xprop_accum_block(struct st_t *, struct xprop_t *);
static void gen_set_xblock_number(struct st_t *, int32, struct xprop_t *);
static void gen_set_xprop_check_case_net_set(struct st_t *, int32, 
 struct xprop_t *);
static void gen_xprop2_if_stmt(struct st_t *);
static void gen_xprop_enter(struct st_t *);
static void gen_xprop_case(struct st_t *, int32, int32, int32);
static void gen_assign_xprop_value(struct st_t *, struct expr_t *, int32,
 struct net_t *);
static void gen_assign_xprop_accum_values(struct st_t *);
static struct st_t *gen_xprop_stlst(struct st_t *, int32, struct st_t *);
static void gen_assign_lhsx_to_accum(struct expr_t *, int32, struct st_t *,
 struct st_t *);
static void gen_set_xprop_accum_value_id(struct net_t *, int32);
static void gen_list_case_xprop(struct st_t *, int32, int32, int32);
static void gen_xprop_trace_write(struct st_t *, int32, int32, int32);
static void gen_xprop_combine_with_self(struct xprop_t *);
static void bld_xprop_xedge_flowg(struct net_t *, struct st_t *, 
 struct delctrl_t *);
static void set_xedge_dctp_bits(struct net_t *, struct delctrl_t *, 
 struct dcevnt_t *);
static void gen_xprop_xedge_flowgs(struct mod_t *);
static void xprop_set_xedge_bits(struct mod_t *);
#endif

/* insn gen prototypes */
/* direct gen insns for new simpler virtual machine */
extern void __st_insn(int32, int32, ...);
extern int32 __move_insn(int32, int32, int32, ...);

/* extern prototypes (maybe defined in this module) */
extern int32 __cvc_driver(void);
extern char *__setstr_objdir_path(void);
extern void __pipe_dsgn_dat_asm_file(void);
extern void __prep_netlists_for_cvc(void);
extern void __bld_iinfo_tabs(void);
extern void __setup_aslinfo_map(void);
extern void __init_tn_dup_trees(void);
extern void __bld_mod_decl_flowgraphs(struct mod_t *);
extern int32 __asm_and_link_dsgn_so_lib(void);
extern void __gen_dsgn_dat_asm_file(void);
extern int32 __gen_cnvt_srep_ifneeded(int32, int32, int32, int32, int32,
 int32);
extern int32 __is_jmp_insn(int32);
extern void __init_tn(struct tn_t *);
extern int32 __get_tnwid(int32);
extern int32 __get_bpti(int32);
extern struct flowg_t *__alloc_flowg(int32);
extern struct bblk_t *__alloc_bblk(int32);
extern void __start_bblk(struct bblk_t *);
extern int32 __gen_tn(int32, int32);
extern void __push_cc_stmt(struct st_t *);
extern void __pop_cc_stmt(void);
extern struct st_t *__find_stlst_end(struct st_t *);
extern struct st_t *__find_after_tsk_nxtstmt(struct st_t *);
extern int32 __gen_expr_eval(struct expr_t *, int32);
extern int32 __gen_ld_is_svec_varadr(struct net_t *, struct gref_t *);
extern void __gen_st_bsel(int32, int32, int32, int32);
extern int32 __gen_comp_ndx(struct net_t *, struct expr_t *, struct bblk_t *, 
 int32);
extern int32 __gen_ld_netbp(struct net_t *);
extern int32 __gen_ld_con_isptr(void *, int32, int32);
extern int32 __gen_ld_net_addr(struct net_t *, struct gref_t *);
extern int32 __ldvar_addr(struct net_t *, struct gref_t *);  
extern void __gen_chg_st_val(struct net_t *, int32, int32);
extern void __gen_chg_st_svecval(struct net_t *, int32, int32, int32, int32);
extern void __gen_st_val(struct net_t *, int32, int32);
extern int32 __gen_cnvt_ab_vec_to_scalar(int32);
extern int32 __gen_cnvt_ab_vec_to_scalar_2state(int32);
extern void __gen_assgn_to_bit_const(struct expr_t *, int32, int32, int32);
extern void __gen_lhsbsel_const(struct net_t *, int32, int32, int32);
extern void __gen_lhsbsel_var(struct net_t *, int32, int32, int32);
extern void __gen_stren_lhsbsel(struct net_t *, int32, int32, int32, int32,
 int32);
extern void __gen_assgn_to_psel(struct expr_t *, int32, int32);
extern void __gen_chg_lhspsel(struct net_t *, int32, int32, int32, int32, 
 int32, int32);
extern void __gen_st_psel(int32, int32, int32, int32, int32);
extern void __gen_chg_word_lhspsel(struct net_t *, int32, int32, int32,
 int32, int32);
extern int32 __gen_scalar_operand(int32, int32);
extern int32 __any_stren_tn(int32);
extern int32 __get_comp_num_ndx(struct expr_t *);
extern void __gen_restore_idp(int32);
extern int32 __gen_arrsel_const(struct net_t *, int32, int32, struct gref_t *);
extern void __free_mod_npp_dce_table(void);
extern void __free_sysfcall_expr(void);
extern int32 __get_lhs_srep(struct expr_t *, int32 *);

/* extern routines mostly defined in other files */
extern int32 __gen_un_bitred_and(int32, int32, int32, int32);
extern int32 __gen_un_bitred_or(int32, int32, int32);
extern int32 __gen_un_bitred_xnor_nor(int32, int32, int32);
extern int32 __gen_ld_xmr_idp(struct gref_t *);
extern int32 __gen_ld_task_xmr_idp(struct gref_t *);

extern void __optimize_1mod_flowgraphs(struct mod_t *);
extern void __emit_1mod_x86_asm(struct mod_t *);
extern int32 __net_chg_nd_store(struct net_t *, int32, int32);
extern int32 __isleaf(struct expr_t *);
extern struct sy_t *__iget_lval_sym(struct expr_t *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern char *__my_malloc(size_t);
extern char *__pv_stralloc(char *);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern char *__xi_stralloc(char *);
extern int32 __wide_vval_is0(word32 *, int32);
extern int32 __cnt_cat_size(struct expr_t *);
extern int32 __same_size(int32 , int32);
extern int32 __lhsexpr_var_ndx(struct expr_t *);
extern int32 __get_widthclass(struct expr_t *);
extern int32 __trim1_0val(word32 *, int32);
extern void __free_1mod_cvc_mem(struct mod_t *);
extern void __grow_ndxjmpbbtab(size_t);
extern int32 __check_delay_constant(union del_u, int32, word64 *);
extern int32 __gen_rhs_bsel_var(struct net_t *, int32, int32); 
extern int32 __gen_rhs_bsel_scalar_var(struct net_t *, int32, int32);
extern int32 __gen_rhs_strength_scalar_bsel_var(int32, int32);
extern int32 __gen_rhs_bsel_const(struct net_t *, int32, int32); 
extern int32 __gen_rhs_bsel_scalar_const(struct net_t *, int32, int32);
extern int32 gen_rhs_strength_bsel(int32, int32, int32); 
extern int32 __gen_fradr_rhs_psel(int32, int32, int32, int32, int32);  
extern int32 __gen_to_r_cnvt(int32, int32, int32);
extern void __gen_record_const_nchg(struct net_t *, int32, int32, 
 struct bblk_t *);
extern void __gen_record_var_nchg(struct net_t *, int32, struct bblk_t *);
extern struct st_t *__exec_case(struct st_t *, struct xstk_t *);
extern int32 __is_const_expr(struct expr_t *);
extern int32 __cvc_is_const_expr(struct expr_t *);
extern void __mark_stlst_unreachable(struct mod_t *, struct st_t *);
extern void __gen_proc_id_assign(struct net_t *, int32);

extern void __linkout_insn(struct insn_t *, int32);
extern struct xstk_t *__eval_assign_rhsexpr(struct expr_t *, struct expr_t *);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern struct expr_t *__get_lvalue_idndp(struct expr_t *);
extern void __xmrpush_refgrp_to_targ_compiletime(struct gref_t *);
extern struct sy_t *__get_nets_containing_sy(struct net_t *, struct mod_t **);
extern struct net_chg_t *__gen_netchg_addr_tn(struct net_t *, int32, 
 int32, int32, int32 *);
extern void __gen_tran_1net(struct net_t *, int32, int32);

extern int32 __gen_xpr_tn(struct expr_t *);
extern int32 __gen_stmt_tn(struct st_t *);
extern int32 __gen_gref_tn(struct gref_t *);
extern int32 __ld_netadr_tn(struct net_t *);
extern int32 __gen_dctrl_rep_bp(struct delctrl_t *);
extern int32 __gen_cint_tn(word32);
extern int32 __gen_contab_tn(int32, int32, int32, int32, int32, int32);  
extern int32 __gen_nonblocking_bp_tn(struct st_t *, int32, int32);
extern int32 __gen_pd_rhsbp_tn(struct st_t *, int32, int32);
extern int32 __gen_repeat_bp_tn(struct st_t *);
extern int32 __gen_proc_enter_adr_tn(struct st_t *);
extern int32 __gen_ctevp_adr_tn(struct ctev_t *);
extern int32 __gen_proc_enter_nb_adr_tn(struct st_t *);
extern int32 __gen_dce_schd_tev(struct delctrl_t *);
extern int32 __emit_ld_nbrhs_valwp(int32, int32, int32, int32);
extern int32 __emit_ld_nbrhs_scalar_val(int32, int32);
extern int32 __con_adradd_insn(int32, int32, int32, size_t);
extern int32 __var_adradd_insn(int32, int32, int32, int32);
extern int32 __is_constant(int32);
extern int32 __is_constant_with_zero_bpart(int32);
extern int32 __is_constant_zero(int32);
extern int32 __get_wrd_con_val(int32);
extern int32 __is_fg_exit_insn(int32); 
extern int32 __get_con_adradd_xvi(int32);
extern int32 __cvt_lngbool(word32 *, word32 *, int32);
extern void __getwir_range(struct net_t *, int32 *, int32 *);
extern void __free_tn_avltree(struct avlhd_t *, void (*)(void *));
extern void __obj_dup_node_free(void *);
extern int32 __gen_idp_storage_area(void);
extern void __bld_mod_flowg_ndx(struct mod_t *);
extern int32 __get_tmpfnam(char *);
extern int32 __tmp_is_2state(int32);
extern int32 __is_cint_typ(int32);
extern int32 __gen_duplicate_tmp(int32);

/* emit routines to gen insn */
extern void __emit_block_label(struct bblk_t *);
extern void __emit_copy(int32, int32, int32);
extern int32 __emit_reg_qcaf_inhibit(int32); 
extern int32 __emit_stren_correct_frc(int32, int32);
extern int32 __emit_correct_frc(int32, int32);
extern int32 __emit_scalar_wire_inhibit(int32);
extern void __emit_st_const_bsel(int32, int32, int32);
extern void __emit_ld_bsel(int32, int32, int32);
extern void __emit_ld_psel(int32, int32, int32, int32);
extern void __emit_st_psel(int32, int32, int32, int32);
extern int32 __emit_mask_and(int32, int32);
extern int32 __emit_mask_or(int32, int32);
extern int32 __emit_srep_mask_and(int32, int32, int32, int32);
extern int32 __emit_qcol_comb_opands(int32, int32, int32);
extern int32 __emit_sub(int32, int32, int32);
extern int32 __emit_add(int32, int32, int32);
extern int32 __emit_mult(int32, int32, int32);
extern int32 __emit_sgn_mult(int32, int32 op2, int32);
extern int32 __emit_div(int32, int32, int32, int32);
extern int32 __emit_sgn_div(int32, int32, int32, int32);
extern int32 __emit_mod(int32, int32, int32, int32);
extern int32 __emit_sgn_mod(int32, int32, int32, int32);
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
extern int32 __emit_sv_dpi_string(struct expr_t *, int32);
extern void __emit_sv_dpi_string_store(struct net_t *, int32);
extern void __emit_call_pop_xtsk(void);
extern void __emit_call_func_dpi(struct task_t *);
extern int32 __gen_ld_return_dpi(struct net_t *);
extern void __gen_ld_return_real_dpi(int32);
extern void __emit_sysfcall(int32, int32);
extern void __emit_sysfcall_stmtloc(int32, int32, struct st_t *);
extern void __emit_enter_task(struct task_t *);
extern void __emit_enter_task_dpi(struct task_t *);
extern void __emit_jmpto_tsk(struct task_t *, struct sy_t *);
extern void __emit_call_tsk(struct task_t *, struct sy_t *);
extern void __emit_tskdone_cleanup(void);
extern void __emit_tskdone_cleanup_auto(void);
extern int32 __emit_thread_auto_cleanup(void);
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
extern int32 __emit_cmp_wide(int32, int32, int32, int32, int32);
extern void __emit_jmp_eq_abpart(struct bblk_t *, struct bblk_t *, int32, 
 int32);
extern void __emit_jmp_eq_ab_wide_varmask(struct bblk_t *, struct bblk_t *, 
 int32, int32, int32);
extern void __emit_jmp_byte_eq(struct bblk_t *, struct bblk_t *, int32, int32);
extern void __emit_cmp(int32, int32);
extern void __emit_cmp_set_type(int32, int32, int32, int32, int32);
extern void __emit_testl(int32);
extern void __emit_st_sete(int32, int32);
extern void __emit_narrow_byte_eq(int32, struct bblk_t *, struct bblk_t *,
 int32, int32);
extern void __emit_jmp_real0(struct bblk_t *, struct bblk_t *, int32);
extern int32 __emit_cmp_widomitxz_ne(int32, int32);
extern int32 __emit_cmp_widall1(int32);
extern void __emit_jmp_sgn_cmp(struct bblk_t *, struct bblk_t *, int32,
 int32, int32);
extern void __emit_jmp_cmp(struct bblk_t *, struct bblk_t *, int32,
 int32, int32);
extern int32 __chk_jmp_cmp_ops(int32, int32, int32);
extern void __emit_jmp_real_cmp(struct bblk_t *, struct bblk_t *, int32,
 int32, int32);
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
extern void __emit_save_curthd_idp(void);
extern int32 __emit_restore_thd_idp(void);
extern void __emit_bldsched_proc_del(int32, int32);
extern void __emit_bldsched_proc_del_nt(int32, int32);
extern void __emit_bldsched_proc_del_const(int32, word64);
extern void __emit_bldsched_proc_del_task_const(int32, word64);
extern void __emit_bldsched_proc_del_const_nt(int32, word64);
extern void __emit_arm_ectrl(int32, int32);
extern void __emit_save_tevp_to_schd(int32, int32);
extern int32 __emit_schd_nbrhs_dctrl(int32, int32, int32);
extern void __emit_schd_nbrhs_scalar_dctrl(int32, int32, int32);
extern void __emit_schd_nbrhs_scalar_dctrl_const(int32, int32, int32);
extern int32 __emit_schd_nbrhs_dctrl_const(int32, int32, int32);
extern int32 __emit_sched_nb_pnd0_lhs_varndx(int32, int32, int32, int32); 
extern int32 __emit_schd_nbrhs_varndx_dctrl(int32, int32, int32, int32, int32);
extern int32 __emit_schd_nbrhs_varndx_dctrl_const(int32, int32, int32, int32);
extern int32 __emit_sched_nb_pnd0_lhs_varndx_concat(int32, int32, int32,
 int32, int32); 
extern int32 __emit_schd_nbrhs_varndx_dctrl_concat(int32, int32, int32, int32,
 int32, int32);
extern int32 __emit_schd_nbrhs_varndx_dctrl_const_concat(int32, int32, int32,
 int32, int32);
extern void __emit_schd_nbrhs_nomem_dctrl_const(int32, int32);
extern void __emit_schd_nb_vardel_rhsconst_dctrl(int32, int32);
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
extern void __emit_exec_qc_deassign_concat(int32);
extern void __emit_exec_qc_deassign_force(int32, int32, int32, int32);
extern void __emit_exec_qc_wirerelease(int32, int32, int32, int32);
extern void __emit_exec_qc_tran_wirerelease(int32, int32, int32, int32);
extern void __emit_exec_cause(int32, int32);
extern int32 __emit_exec_dsable(int32);
extern void __emit_store_cint(int32, int32, int32);
extern void __emit_setall1(int32, int32);
extern void __emit_suspend(void);
extern void __emit_complete(void);
extern void __emit_leave(void);
extern void __emit_enter_proc(struct st_t *);
extern void __emit_enter_mdc(int32);
extern void __emit_enter_nb_proc(struct st_t *);
extern void __emit_enter_nb_proc_free(struct st_t *);
extern void __emit_enter_thd_ret(int32);
extern void __emit_enter_bblk_dbgmsg(void);
extern int32 __emit_wide_sgn_lpow(int32, int32, int32, int32);
extern int32 __emit_wide_lpow(int32, int32, int32);
extern int32 __emit_inum(void);
extern void __memloc_emit_set_idp(int32);
extern int32 __emit_save_idp(int32);
extern int32 __emit_save_cur_idp(void);
extern int32 __emit_new_auto_idp_area(int32);
extern void __emit_cp_auto_idp_area_func(int32, int32);
extern int32 __emit_xmr_rooted_base(struct net_t *);
extern void __emit_set_tevp_trigger_off(int32);
extern int32 __gen_taskp_tn(struct task_t *);
extern int32 __move_srep_insn(int32, int32, int32, int32, int32, ...);
extern int32 __emit_random_with_seed(int32);
extern int32 __emit_1arg_transcendental(int32, int32);
extern int32 __emit_random(void);
extern void __emit_rhs_psel_wide(int32, int32, int32, int32, int32, int32);
extern void __emit_rhs_psel_wide_2state(int32, int32, int32, int32);
extern int32 __emit_rhs_psel(int32, int32, int32, int32);
extern int32 __emit_rhs_psel_2state(int32, int32, int32);
extern void __emit_rhs_st_psel(int32, int32, int32);
extern int32 __emit_toscal_2s_fr_scal_4s(int32, int32);
extern int32 __gen_stack_adr(int32);
extern int32 __get_array_srep_type(struct net_t *);
extern void __emit_stmt_coverage(struct st_t *);
extern void __emit_sv_string_st_const(struct net_t *, int32);
extern void __emit_sv_string_st_var(struct net_t *, struct net_t *);
extern void __emit_sv_string_st_eval_rhsx(struct net_t *, struct expr_t *);
extern int32 __emit_binop_string(struct expr_t *);
extern void __emit_st_string_byte(struct net_t *, int32, int32);
extern void __emit_st_string_array_const(struct net_t *, int32, int32, int32);
extern void __emit_st_string_array_var(struct net_t *, struct net_t *, int32);
extern void __emit_st_string_array_rhsx(struct net_t *, struct expr_t *, int32);
extern int32 __emit_get_string_byte(struct net_t *, int32);
#ifdef __XPROP__
extern int32 __emit_get_xprop_accum(struct net_t *);
extern int32 __emit_per_bit_xprop_accum(struct st_t *, int32, int32);
extern void __emit_get_xprop_accum_init(struct net_t *, int32, int32);
extern void __emit_get_xprop_accum_to_self(struct net_t *, int32, int32);
extern void __emit_get_xprop_accum_to_self_wide(struct net_t *, int32);
extern void __emit_get_xprop_accum_init_wide(struct net_t *, int32);
extern void __emit_stmt_assign_to_accum_wide(struct st_t *, struct st_t *,
 int32, int32);
extern void __emit_stmt_assign_to_accum_1w(struct st_t *, struct st_t *,
 int32, int32);
extern void __emit_stmt_assign_to_accum_id_1w(struct net_t *, struct st_t *, 
 int32, int32);
extern void __emit_stmt_assign_to_accum_id_wide(struct net_t *, struct st_t *, 
 int32, int32);
extern void __emit_set_xprop_accum_block(struct st_t *);
extern void __emit_xprop_check_case_net_set(struct st_t *, int32);
extern void __emit_set_restore_xprop_accum_block(struct st_t *, int32);
extern void __emit_set_restore_xprop_accum_block_toself(struct st_t *);
extern void __emit_set_restore_xprop_accum_block_nodefault(struct st_t *, 
 int32, int32);
extern void __emit_trace_xprop_write(struct st_t *, int32, int32, int32);
extern void __emit_trace_xprop_write_wide(struct st_t *, int32, int32, int32);
extern struct expr_t *__alloc_newxnd(void);
extern int32 __emit_xprop_xcount(int32);
extern int32 __emit_xprop_xedge_net(struct st_t *);
extern int32 __needs_xedge_net_record(struct delctrl_t *);
extern int32 __is_stlst_net_on_rhs_assign(struct st_t *, struct net_t *,
 struct st_t *); 
#endif

extern void __my_fprintf(FILE *, char *, ...);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __cv_msg(char *s, ...);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern struct avlhd_t *__allocinit_avlhd(void);
extern void __set_mod_ent_bits(struct mod_t *);
extern void __get_qc_wirrng_comptime(struct expr_t *, struct net_t **, 
 int32 *, int32 *);
extern int32 __gen_mdata_value(struct itree_t *);
extern int32 __cvt_lngbool(word32 *, word32 *, int32); 
extern struct prep_obj_t *__find_add_obj(struct avlhd_t *, void *);
extern int32 __needs_netchg_record(struct net_t *);
extern struct net_t *__get_indexed_psel_range(struct expr_t *, int32 *, 
 int32 *);
extern void __cnvt_xzs_to_2state(word32 *, word32 *, int32);
extern int32 __is_expr_2state(struct expr_t *);
extern int32 __is_2state_typ(int32);
extern void __my_ftime(time_t *, time_t *);

extern const word32 __masktab[];
#ifndef __CVC32__
int32 __passed_regs_order[6] = {PASS_REG1, PASS_REG2, PASS_REG3, 
  PASS_REG4, PASS_REG5, PASS_REG6};
#endif

/*
 * CVC TOP LEVEL ASM GEN CONTROL (GEN AND LINKING) ROUTINES
 */

/*
 * cvc driver routines
 */
extern int32 __cvc_driver(void)
{
 int32 rv;

// SJM 09-07-12 REMOVEME
// ??? __verbose_mem = TRUE; 

#ifdef __CVC_DEBUG__
 /* AIV 11/30/09 - print if all non-blocking have same <= #delay value */
 if (__verbose && __all_nb_same_time == TRUE)
  {
#ifdef __CVC32__
   __cv_msg("  Non-blocking all times the same - %llu.\n", 
     __nb_const_last_time);
#else
   __cv_msg("  Non-blocking all times the same - %lu.\n", __nb_const_last_time);
#endif
   }
#endif

 /* routines to compute net list information needed just by CVC */
 __prep_netlists_for_cvc();
 
 /* AIV 01/24/07 - don't need to init design wide compile time variables */
 /* if loading a .so library */
 init_cvc();

 /* gen per module .s file for every mod in design but don't assemble yet */
 gen_asm_insns_for_all_mods();

 /* SJM 04/30/08 - now gen the comm .s file with new ALNK init asm code */
 if (__show_asm)
  {
   __gen_dsgn_dat_asm_file();
  }
 else
  {
   __pipe_dsgn_dat_asm_file();
  }

 /* DBG remove -- */
 if (__prpsti != 0) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (__pv_err_cnt > 0)
  {
   rv = FALSE;
   goto free_dsgn_mem;
  }

 /* emit the one design wide .s files and assembly every .s file and */
 /* and build the cvc output .so lib */
 rv = __asm_and_link_dsgn_so_lib();

free_dsgn_mem:
 free_dsgn_cvc_storage(); 
 __free_mod_npp_dce_table();
 __free_sysfcall_expr(); 
 return(rv);
}

/*
 * gen flow graph and compile to asm insns
 */
static void gen_asm_insns_for_all_mods(void)
{
 struct mod_t *mdp;
 int32 tot_compiled_lines, ni, mcount, mtotal;
 int32 save_insn_count;
 time_t mod_comp_start, mod_comp_ms_start, mod_comp_end, mod_comp_ms_end;
 double timd1;
 struct net_t *np;
 struct net_chg_t *ncp;
 long save_mem_use;

 /* code gen will work */
 tot_compiled_lines = 0;
 mcount = 1;
 mtotal = 0;
 /* get the total number of modules for compile message */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   mtotal += 1;
   /* AIV 02/21/12 - moved this up here for xprop - needs to mark all */
   /* stp->is_enter bits - for all mods just marks bits so is fine */
   /* set module enter stmt points */
   __set_mod_ent_bits(mdp);
  }

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
//SJM FOR DEBUGGING REMOVEME
/*------
   if (__verbose)
    {
     __cv_msg(
      "    <<< Before module %s mem_use=%ld\n", mdp->msym->synam, __mem_use);
    }
-------*/
   /* SJM 10-14-14 - for verbose also print elapsed compiled time for mod */
   if (__verbose || __verbose_mem)
    {
     __my_ftime(&(mod_comp_start), &(mod_comp_ms_start));
    }

   /* SJM 05/10/06 - maybe reduce the very larg tn tabs back to smaller */ 
   __tntab_nxti = HIGH_X86_REG + 1;
   /* AIV 08/07/09 - this should be "compiling" message prior */
   /* SJM 12-09-06 - print progress for verbose too */
//SJM 10-03-12 - NEED TIME AND MEM USE FOR EACH MODULE
   if (__verbose || __verbose_mem)
    {
     if (mdp->mod_last_ifi == mdp->msym->syfnam_ind)
      {
       __cv_msg("    Compiling %s (%d lines)(%d insts)(%d of %d)",
        mdp->msym->synam, mdp->mod_last_lini - mdp->msym->sylin_cnt + 1,
        mdp->flatinum, mcount, mtotal);
       tot_compiled_lines += (mdp->mod_last_lini - mdp->msym->sylin_cnt + 1);
      }
     else
      {
       __cv_msg(
        "    Compiling module %s (in more than one file) (%d insts)(%d of %d).\n",
        mdp->msym->synam, mdp->flatinum, mcount, mtotal);
      } 
     mcount++;
    }
   /* AIV 12/21/07 - print out a verbose message at compile time */
   /* by default on unless +verbose or -q used print other message */
   else if (!__quiet_msgs)
    {
     /* notice this is printf to prevent dumping to log file */
     printf("\r  Compiling module %d of %d.", mcount, mtotal);
     fflush(stdout);
     mcount++;
    }


   /* save insn and mem counts */
   save_insn_count = __insn_count;
   save_mem_use = __mem_use;

   /* insn are per module */
   __push_wrkitstk(mdp, 0);

   /* SJM 08/02/08 - uses inst mod now */
   init_one_mod_cvc();

#ifdef __XPROP__
   /* need to set event control dctp-> bits for xedge dectection */
   /* prior to doing normal FGs */
   xprop_set_xedge_bits(mdp);
#endif

//AIV LOOKATEME - now must produce proc flowgraphs first
   /* gen procedural insns and flow graphs */
   bld_mod_proc_flowgraphs(mdp);

   /* gen declarative insns and flow graphs */
   __bld_mod_decl_flowgraphs(mdp);
   
   /* optimize all flowgraphs for one module */
   __optimize_1mod_flowgraphs(mdp);

   /* gen the .s file with .comm .bss area at bottom for one module */
   __emit_1mod_x86_asm(mdp);
   __pop_wrkitstk();

   if (__verbose_mem)
    {
     /* AIV 06/18/09 - added special memory printing for +verbosemem */
     dmp_verbose_mem_info(mdp, save_mem_use, save_insn_count);
    }

   /* dump nchg tree */
   if (__opt_debug_flg)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
        {
         __my_fprintf(stdout, "NET(%s) CHG idpofs=%d i1=%d i2=%d\n", 
         np->nsym->synam, ncp->nchg_idp_ofs, ncp->i1, ncp->i2);
        }
      }
    }

   /* free all compiling work data structures */
   __free_1mod_cvc_mem(mdp);
   /* print memory out vs memory in (leaked memory) with +verbosemem */
   if (__verbose_mem) 
    {
     __cv_msg("      MI = %lu MO = %lu\n", save_mem_use, __mem_use);
    }
   /* SJM 10-14-14 - now emit the per mod compile time */
   if (__verbose || __verbose_mem)
    {
     __my_ftime(&(mod_comp_end), &(mod_comp_ms_end));
     timd1 = (double) (mod_comp_end - mod_comp_start)
      + ((double) (mod_comp_ms_end - mod_comp_ms_start))/1000.0;
     __cv_msg(" - %.2lf secs.\n", timd1);
    }
  }
 if (__verbose)
  {
   __cv_msg("    Approximately %d lines compiled.\n", tot_compiled_lines);
  }
}
         
/*
 * print out module memory compiled information
 */
static void dmp_verbose_mem_info(struct mod_t *mdp, long save_mem_use, 
 int32 save_insn_count)
{
 struct flowg_t *fgp;
 int32 fgi, i;
 int32 fg_count[FLOWG_SIZE];
 int32 fg_num_blocks[FLOWG_SIZE];
 
 /* memory usage for module */
 __cv_msg("      MEM USAGE = %lu\n", __mem_use - save_mem_use);
 /* number of tmps used in this module */
 __cv_msg("      NUM  TMPS = %d\n", __tntab_nxti);
 /* size of tntab in number of tmps not bytes */
 __cv_msg("      TT   SIZE = %lu\n", __tntabsiz);
 /* number of instructions */
 __cv_msg("      NUM INSNS = %d\n", __insn_count - save_insn_count);
 /* number ndx jmp tab */
 __cv_msg("      NDXJMP    = %lu\n", __ndxjmp_bbtab_siz);

 __bld_mod_flowg_ndx(mdp);
 memset(fg_count, 0, FLOWG_SIZE*sizeof(int32));
 memset(fg_num_blocks, 0, FLOWG_SIZE*sizeof(int32));
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   fgp = __flowgtab[fgi];
   fg_count[fgp->flowgtyp]++;
   /* number of blocks per fg type */
   fg_num_blocks[fgp->flowgtyp] += fgp->fg_num_bblks;
  }

 __cv_msg("      NUM FGS = %d\n", __flowg_lasti);

 for (i = 0; i < FLOWG_SIZE; i++)
  {
   if (fg_count[i] == 0) continue;
   __cv_msg("        t=%d  c=%d nb=%d\n", i, fg_count[i], fg_num_blocks[i]);
  }
}

/*
 * preamble (initialize) for one mod's CVC insn gen  
 */
static void init_one_mod_cvc(void)
{
 int32 ri;

 /* reset index of current jmp table label per mod */
 __jmplab_nxti = 0;  

 /* init argument push count to 0 */
 __push_count = 0;

 __need_reg_tns = FALSE;

 /* SJM 04/25/05 - once debugged make larger */
 __tntabsiz = 128;
 __tntab = (struct tn_t *) __my_malloc(__tntabsiz*sizeof(struct tn_t));  
 for (ri = 0; ri <= HIGH_X86_REG; ri++) gen_x86reg_tn(ri);
 __tntab_nxti = HIGH_X86_REG + 1;

 /* SJM 01/23/07 - formal tmp tab is only number of insns */
 /* so can reuse by initializing the ptrs */
 for (ri = 0; ri <= LAST_INSN; ri++) __formal_tmptab[ri] = NULL;

 for (ri = 0; ri <= NLO_HIGH_USED; ri++) __nlo_tn_used[ri] = -1;

 __init_tn_dup_trees();

 __copy_ip = NULL;
 __func_complete_bbp = NULL;
 __need_net_addr = FALSE;

 __rev_po_ndx = -1;
 __enter_bblk_valnum = -1;
 __cur_valnum = 0;
 __dum_fg_ent_bbp = (struct bblk_t *) __my_malloc(sizeof(struct bblk_t));
 __dum_fg_ent_bbp->bblk_seqno = -2;
 __dum_fg_ent_bbp->revpostordno = 0;

 __avl_lasti = -1;
 __flowgtabsiz = 64;
 __flowgtab = (struct flowg_t **)
  __my_malloc(__flowgtabsiz*sizeof(struct flowg_t *));
 __flowg_lasti = -1;

 __bblktabsiz = 64;      /* current size */
 __bblktab = (struct bblk_t **) 
  __my_malloc(__bblktabsiz*sizeof(struct bblk_t *));
 __bblk_lasti = -1;

 /* SJM 12/26/06 - this is now work avl tab that is copied to malloc mem */
 __avltabsiz = 1000;
 __avltab = (struct avlnode_t **)
  __my_malloc(__avltabsiz*sizeof(struct avlnode_t *));
 __avl_lasti = -1;
 /* AIV 01/26/07 - need an adradd tree to hold dup adradd values */
 __adradd_child_tree = __allocinit_avlhd();

 /* per module idp storage area tmp */
 __idp_ti = __gen_idp_storage_area();
 __nb_const_last_time = 0xffffffffffffffffULL;

 /* AIV 06/16/09 - these are now per module */
 __ndxjmp_bbtab_siz = 64;
 __ndxjmp_bbtab = (struct bblk_t **)
  __my_malloc(__ndxjmp_bbtab_siz*sizeof(struct bblk_t *));
 
 __jmpbas_tabsiz = 64;
 __jmpbase = (int32 *) __my_malloc(__jmpbas_tabsiz*sizeof(int32));
}

/*
 * free any design igen storage before starting sim 
 */
static void free_dsgn_cvc_storage(void) 
{
 int32 i, slen;
 struct mod_t *mdp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->isnum_tree != NULL)
    {
     __free_tn_avltree(mdp->isnum_tree, __obj_dup_node_free);
    }
  }

 /* AIV 12/21/07 - if compile only need solib name for compilation messgae */
 if (__exe_name != NULL && __running_cvc_exe)
  {
   __my_free(__exe_name, strlen(__exe_name) + 1);
  }

 /* AIV 06/16/09 - minor memory leak here - need to free string */
 for (i = 0; i < __thdjmp_nxti; i++)
  {
   slen = strlen(__thdjmp_ret_tab[i]) + 1;
   __my_free(__thdjmp_ret_tab[i], slen); 
  }
 __my_free(__thdjmp_ret_tab, __thdjmp_siz*sizeof(char *)); 

 __my_free(__formal_tmptab, (LAST_INSN + 1)*sizeof(struct avlhd_t *));
 __my_free(__nlo_tn_used, (NLO_HIGH_USED + 1)*sizeof(int32));
 /* AIV 03/27/07 - need to free design wide expr tree */
 /* just holding system func calls exprs */
 /* AIV LOOKTAME - can remove when sys func calls lowered */
 __free_tn_avltree(__xpr_dup_tree, __obj_dup_node_free);
 __xpr_dup_tree = NULL;
 free_compile_time_structs();
}

/*
 * free all compile time net change records
 * free all net_chg_t and ctev_t which are used at compile time
 */
static void free_compile_time_structs(void)
{
 int32 ni, gi, si;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct net_chg_t *ncp, *ncp2;
 struct ctev_t *ctevp;
 struct st_t *stp;
 struct gate_t *gp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum != 0)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       free_net_comptime_events(np);
       for (ncp = np->nchdp; ncp != NULL; ncp = ncp2)
        {
         ncp2 = ncp->nxt;
         __my_free(ncp, sizeof(struct net_chg_t));
        }
      } 
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       free_net_comptime_events(np);
       for (ncp = np->nchdp; ncp != NULL; ncp = ncp2)
        {
         ncp2 = ncp->nxt;
         __my_free(ncp, sizeof(struct net_chg_t));
        }
     }
    }
  for (gi = 0; gi < mdp->mgnum; gi++)
   {
    gp = &(mdp->mgates[gi]);
    if ((ctevp = gp->ctevp) == NULL) continue;
    __my_free(ctevp, sizeof(struct ctev_t));
    gp->ctevp = NULL;
   }
#ifdef __XPROP__
 /* AIV 02/21/12 - if xprop ctevp can be used across multiple stmts */
 /* so need to only free once */
 if (__xprop || __xprop2)
  {
   int32 count, count2;
   struct ctev_t **tarray;

   /* get the count */
   count = 0;
   for (si = 0; si < mdp->mstnum; si++) 
    {
     stp = mdp->mstmts[si];
     if ((ctevp = stp->ctevp) == NULL) continue;
     ctevp->in_list = FALSE;
     count++;
    }
   if (count == 0) return;

   /* store the ctevs only once using in_list flag */
   tarray = (struct ctev_t **) __my_malloc(count*sizeof(struct ctev_t *));
   count2 = 0;
   for (si = 0; si < mdp->mstnum; si++) 
    {
     stp = mdp->mstmts[si];
     if ((ctevp = stp->ctevp) == NULL) continue;
     if (ctevp->in_list) continue;
     ctevp->in_list = TRUE;
     tarray[count2] = ctevp;
     count2++;
    }
 
   /* now free them */
   for (si = 0; si < count2; si++) 
    {
     ctevp = tarray[si];
     __my_free(ctevp, sizeof(struct ctev_t));
    }

   return;
  }
#else
 for (si = 0; si < mdp->mstnum; si++) 
  {
   stp = mdp->mstmts[si];
   if ((ctevp = stp->ctevp) == NULL) continue;
   __my_free(ctevp, sizeof(struct ctev_t));
   stp->ctevp = NULL;
  }
#endif
 }
}
         
/*
 * free a nets compile time events (np->ndel_ctevtab)
 */
static void free_net_comptime_events(struct net_t *np)
{
 struct ctev_t **ndel_ctevtab;
 int32 bi;

 if ((ndel_ctevtab = np->ndel_ctevtab) == NULL) return;

 if (np->n_isavec)
  {
   for (bi = 0; bi < np->nwid; bi++)
    {
     __my_free(ndel_ctevtab[bi], sizeof(struct ctev_t));
    }
  }
 else 
  {
   __my_free(ndel_ctevtab[0], sizeof(struct ctev_t));
  }
 /* AIV 06/16/09 - memory leak here this is supposed to be a free */
 /* was an malloc */
 __my_free(ndel_ctevtab, np->nwid*sizeof(struct ctev_t *));
 np->ndel_ctevtab = NULL;
}
 
/*
 * ROUTINES FOR DESIGN WIDE PRE (INTIALIZATION) AND POST (
 */

/*
 * routine to initialize asm insn gen
 *
 * initialize for this run - called just before used the first time
 *
 * BEWARE - because contab can be reallocated - after this routine during
 * asm insn gen can no longer call alloc cval or alloc shareable cval
 */
static void init_cvc(void)
{
 int32 i, ri, nmods;
 struct mod_t *mdp;

 __cur_bbp = NULL;
 __enter_bbp = NULL;
 __cur_ip = NULL;
 __push_count = 0;

 __bld_iinfo_tabs();

 /* first label is 0 and never reused */
 __enter_seq_no = -1;
 /* design wide (for now) bblk and flowg sequence numbers for debugging */
 __bblk_seq_no = -1;
 /* SJM 05/12/07 - since now word so can find overflow - -1 now hex */
 __flowg_seq_no = 0xffffffff;
 __iconn_seq_no = -1;
 __gate_conta_seq_no = -1;
 __nxt_lab = -1;
 __dce_no = -1;

 __proc_flowg_hd = __proc_flowg_tail = NULL;
 __cur_flowg = NULL;

 /* per module formal tmp table - avl tree (set) for every eval insn */ 
 __formal_tmptab = (struct avlhd_t **)
  __my_malloc((LAST_INSN + 1)*sizeof(struct avlhd_t *));
 for (ri = 0; ri <= LAST_INSN; ri++) __formal_tmptab[ri] = NULL;

 __gening_tsk = FALSE;
 __gening_mdc = FALSE;   
 
 __decomposed_tn_nums = NULL;
 __cur_mark = 0;
 __nb_stmt_hd = NULL;
 __nb_stmt_cur = NULL; 
 __pd_rhs_stmt_hd = NULL;
 __pd_rhs_stmt_cur = NULL;

 __removed_bblks = 0;
 __num_asm_insn = 0;
 __removed_asm_insns = 0;
 __trk_num_insn_removed = 0;
 __trk_num_insn_changed = 0;
 __num_print_asm_insn = 0; 
 
 __idp_ti = -1;

 /* allocate the dummy insn for use-def ptrs where the use has no define */
 __cur_dom_fron_todos = __cur_dom_fron_tail = NULL;
 __insn_order_ndx = NULL;

 __nlo_tn_used = (int32 *) __my_malloc((NLO_HIGH_USED + 1)*sizeof(int32));

 /* compile time build, pre-sim dynamic link, run time jump thru table */ 
 __thdjmp_siz = 100;
 __thdjmp_nxti = -1;
 __thdjmp_ret_tab = (char **) __my_malloc(__thdjmp_siz*sizeof(char *)); 
 for (i = 0; i < __thdjmp_siz; i++) __thdjmp_ret_tab[i] = NULL;

 /* SJM 08-23-08 - init per mod datofs storage tree before generating */ 
 /* .s file for any module - must be freed after all dlsym linking done */
 nmods = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   mdp->mod_ndx_seq_no = 0;
   nmods++;
  }

 __prpsti = 0;
 __prpstk[__prpsti] = NULL;
 __hd_gdap = NULL; 
 __tail_gdap = NULL; 
 __process_compiled_thrd_ev_enterp = NULL;
 __process_nbpa_varndx_ev_enterp = NULL;
 __process_next_event_free_enterp = NULL;
 __process_trpthdst_ev_enterp = NULL;
 __process_gatechg_ev_enterp = NULL;

 set_asm_file_names(nmods);
 /* AIV 11/02/07 - insn info counts */
 __insn_count = 0;
 __insn_print_count = 0;
 __coalesce_count = 0;
 __spill_count = 0;  
 __spill_nonw_count = 0;  
 __next_nchglp = NULL;
 __process_next_nchg_enterp = NULL; 
 __first_enterp = NULL; 
 __free_event_pnd0_tevp = NULL;
 __cvc_slotend_action = 0;
 /* AIV FIXME - this can be known for PLI access scheme */
 /* for now assume pli may add either of these actions */
 /* AIV 05/13/09 - access level > 3 for sync code */
 if (__pli_access_level >= 2)
  {
   __cvc_slotend_action |= SE_TFROSYNC;
   __cvc_slotend_action |= SE_VPIROSYNC;
  }
 __known_inum = -1;
 __design_has_nb_events = FALSE; 
 __design_has_nb_del_events = FALSE;
 __init_mdp = NULL;
 __generating_stp = NULL;
#ifdef __CVC32__
__advance_seta_va = NULL;
#endif
 /* AIV 06/16/09 - memory leak here this could be malloc in v_prp2 */
 /* need to free because this is malloc per compiled mod */
 if (__avltab != NULL)
  {
   __my_free(__avltab, __avltabsiz*sizeof(struct avlnode_t *));
  }
 __loop_continue_bbp = NULL;
 __loop_break_bbp = NULL;
 __asl_info_map = NULL;
 __max_asl_rout_num = -1;
 /* AIV 01/31/12 - now setup of asl routine maps so don't have to search */
 /* everytime */
 __setup_aslinfo_map();

 __asm_file_name[0] = '\0';
 __asm_pipefd[0] = -1;
 __asm_pipefd[1] = -1;
 __asm_pid = 0;
 __asm_stack = NULL; 
}

/*
 * assembler output object path and .so names
 */
static void set_asm_file_names(int32 nmods)
{
 struct mod_t *mdp;
 char fname[RECLEN];

 /* SJM 02-07-13 - now one place to set prefix used instead of OS tmp */
 /* SJM 02-07-13 - notice must be in v dpi since rt elab does not use bbgen */
 __setstr_objdir_path();

 /* set the name of the *.so library created */
 /* if showing asm on use the current directory */
 if (__exe_name == NULL)
  {
   __exe_name = __xi_stralloc(DEF_EXE_NAME); 
  }

 /* if show_asm use normal names */
 if (__opt_emit_var_names || __show_asm) 
  {
   __mod_file_names = NULL;
   __comm_file_name = NULL;  
   __comm_nt_file_names = NULL;
   __exe_file_name = NULL;
   __cvclib_file_name = NULL;
   return;
  }

 /* if pipe use distinct names per run - the X's are replaced */
 /* comm area file name */
 sprintf(fname, "%s/comm-XXXXXX", __objdir_path);
 __get_tmpfnam(fname);
 __comm_file_name = __pv_stralloc(fname);

 /* exe_main.o file name */
 sprintf(fname, "%s/exe-XXXXXX", __objdir_path);
 __get_tmpfnam(fname);
 __exe_file_name = __pv_stralloc(fname);

 /* cvclib.o file name */
 sprintf(fname, "%s/lib-XXXXXX", __objdir_path);
 __get_tmpfnam(fname);
 __cvclib_file_name = __pv_stralloc(fname);

 /* module file names */
 __mod_file_names = (char **) __my_malloc(nmods*sizeof(char *));
 __comm_nt_file_names = (char **) __my_malloc(nmods*sizeof(char *));

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* comm init file name  - are now per module */
   sprintf(fname, "%s/comm_nt_m%d-XXXXXX", __objdir_path, mdp->m_idnum);
   if (__get_tmpfnam(fname) == -1) __misc_terr(__FILE__, __LINE__);
   __comm_nt_file_names[mdp->m_idnum] = __pv_stralloc(fname);

   sprintf(fname, "%s/M%d-XXXXXX", __objdir_path, mdp->m_idnum);
   if (__get_tmpfnam(fname) == -1) __misc_terr(__FILE__, __LINE__);
   __mod_file_names[mdp->m_idnum] = __pv_stralloc(fname);
  }
}

/*
 * gen a hardware (x86 for now) tmp reg - done once before asm gen
 * 
 * x86 specific routine - x86 reg tn's go in low 8 tmp names 
 * can only be called once
 */
static void gen_x86reg_tn(int32 regnum)
{
 struct tn_t *tnp;

 /* DBG remove --- */
 if (regnum > HIGH_X86_REG) __misc_terr(__FILE__, __LINE__);  
 /* --- */
 
 tnp = &(__tntab[regnum]);
 __init_tn(tnp);
 tnp->srtyp = SR_CINT;
 /* fix for AMD 64 */
 tnp->tnwid = WBITS;
 tnp->tn_typ = TN_VAL;
 tnp->x86_regno = regnum;
}

/*
 * ROUTINES TO GEN 3 ADR TUPLES FOR ONE MODULE
 */

/*
 * generate insns for one module procedural part
 */
static void bld_mod_proc_flowgraphs(struct mod_t *mdp)
{
 struct task_t *tskp;
 struct ialst_t *ialp;
 struct dpi_t *dpip;

 /* generate intermediate insn addr from from stmts and expr trees */
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)  
  {
   gen_initalways(ialp);
  }
#ifdef __XPROP__
 /* generate xprop always @(X) proc fgs */
 gen_xprop_xedge_flowgs(mdp);
#endif

 /* AIV 03/03/09 - build merged always blocks header flow graphs */
 bld_delctrl_merged_fgs(mdp);

 /* AIV 05/14/07 - tasks currently need thread setup code */ 
 /* AIV FIXME - need to mark c-style tasks (no reachable delays) */
 __needs_thread_ctrl = TRUE;
 /* gen declarative net chg ams insns */
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   /* if export DPI tasks - build code - otherwise nothing to compile */
   dpip = tskp->tf_dpip;
   if (dpip != NULL)
    {
     /* if an export must generate task with acutal C name and wrapper */
     /* to assign values */
     if (dpip->dpi_type == DPI_EXPORT) 
      {
       gen_tskbody_export_dpi(tskp);
      }
     continue;
    }
   /* labeled blocks and forks are gened inline */
   if (tskp->tsktyp == Begin || tskp->tsktyp == FORK) continue;

   if (tskp->tsktyp == FUNCTION) gen_funcbody(tskp);
   else gen_tskbody(tskp); 
  }
 /* AIV 08/28/07 - was never reseting the needs thread for non-blocking ctrl */
 /* was wrong for backend of non-blocking assigns */
 __needs_thread_ctrl = FALSE;

 /* generate flowgraph vm insns for all non-blocking assign */
 /* AIV 07/23/08 - now produce two backend nb flow graphs one to handle */
 /* malloc events which is the exact same except one jumps to the next event */
 /* and the other must free the malloc event prior to jumping to next event */
 gen_nb_assigns(FALSE);
 gen_nb_assigns(TRUE);
 mdp->mod_flowg = __proc_flowg_hd;
 __proc_flowg_hd = __proc_flowg_tail = NULL;
}

/*
 * generate vm insns for init/always
 */
static void gen_initalways(struct ialst_t *ialp)
{
 struct flowg_t *fgp;
 struct bblk_t *ia_bbp, *after_enter_bbp;
 int32 iatyp;

 /* SJM 09/27/05 - cur bbp used by bb opt so must init here each time */
 __cur_bbp = NULL;
 fgp = __alloc_flowg(FLOWG_PROC);
 /* AIV 01/04/07 - fg needs to record if it is using thread */
 fgp->has_thread_ctrl = ialp->needs_thread;
 __cur_flowg = fgp;
 if (__proc_flowg_hd == NULL) __proc_flowg_hd = __proc_flowg_tail = fgp;
 else
  {
   __proc_flowg_tail->flowgnxt = fgp;
   __proc_flowg_tail = fgp;
  }
 __cur_ifrom_u.from_stp = ialp->iastp;

 ia_bbp = __alloc_bblk(FALSE); 
 __start_bblk(ia_bbp);
 ia_bbp->after_suspend = TRUE;
 __emit_enter_proc(ialp->iastp);

 /* AIV 05/15/07 - if initial block doesn't need thread mechanism mark */
 /* global flag to produce better code without thread overhead */
 __needs_thread_ctrl = ialp->needs_thread; 
 iatyp = ialp->iatyp;
 /* AIV 07/12/12 - now supporting new SV always_* types */
 if (iatyp == ALWAYS || iatyp == ALWAYS_COMB || iatyp == ALWAYS_FF || 
  iatyp == ALWAYS_LATCH)
  {
   after_enter_bbp = __alloc_bblk(FALSE); 
   __start_bblk(after_enter_bbp);

   gen_stlst(ialp->iastp, TRUE);

   __emit_jmp(after_enter_bbp);
  }
 else
  {
   /* for loop statements, this start a new bblk to jump to */
   gen_stlst(ialp->iastp, FALSE);

   /* AIV 06/26/05 - don't jump if last instruction is a complete */ 
   if (need_complete_or_suspend()) __emit_complete();
  }
 __needs_thread_ctrl = FALSE; 
}

#ifdef __XPROP__
/*
 * generate always @(x) flow graphs 
 * these are just regular always @ fgs expect for special xprop handling
 */
static void gen_xprop_xedge_flowgs(struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct st_t *stp;
 struct dcevnt_t *dcep;
 struct delctrl_t *dctp;
 struct itree_t *itp;

 if (!__xprop || __xprop2) return;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   /* not handling arrays for always@() xprop */
   for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
    {
     if (dcep->dce_typ != DCE_RNG_INST && dcep->dce_typ != DCE_INST)
       continue;

     dctp = dcep->st_dctrl;
     /* DBG remove -- */ 
     if (dctp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     stp = dctp->xprop_xedge_actionst;

     //AIV LOOKATME allow XMRs???
     /* these fgs have to be built per module turning these off for now */
     if (dcep->dce_xmrtyp != XNP_LOC)
      {
       /* DBG remove -- */ 
       if (stp != NULL) __misc_terr(__FILE__, __LINE__);
       continue;
       /* ----- */ 

       if (dcep->dce_1inst) itp = dcep->dce_refu.itp;
       else itp = dcep->dceu.dcegrp->gin_mdp->moditps[0];
       __push_itstk(itp);
      }
     else itp = NULL;

     if (stp == NULL) 
      {
       if (itp != NULL) __pop_itstk(); 
       continue;
      }
     bld_xprop_xedge_flowg(np, stp, dctp);

     if (itp != NULL) __pop_itstk(); 
    }
  }
}

/*
 *
 */
static void xprop_set_xedge_bits(struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct st_t *stp;
 struct dcevnt_t *dcep;
 struct delctrl_t *dctp;
 struct itree_t *itp;

 if (!__xprop || __xprop2) return;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   /* not handling arrays for always@() xprop */
   for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
    {
     if (dcep->dce_typ != DCE_RNG_INST && dcep->dce_typ != DCE_INST)
       continue;

     dctp = dcep->st_dctrl;
     /* DBG remove -- */ 
     if (dctp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     stp = dctp->xprop_xedge_actionst;

     //AIV LOOKATME allow XMRs???
     /* these fgs have to be built per module turning these off for now */
     if (dcep->dce_xmrtyp != XNP_LOC)
      {
       /* DBG remove -- */ 
       if (stp != NULL) __misc_terr(__FILE__, __LINE__);
       continue;
       /* ----- */ 

       if (dcep->dce_1inst) itp = dcep->dce_refu.itp;
       else itp = dcep->dceu.dcegrp->gin_mdp->moditps[0];
       __push_itstk(itp);
      }
     else itp = NULL;

     if (stp == NULL) 
      {
       if (itp != NULL) __pop_itstk(); 
       continue;
      }
     set_xedge_dctp_bits(np, dctp, dcep);

     if (itp != NULL) __pop_itstk(); 
    }
  }
}

/*
 *
 */
static void set_xedge_dctp_bits(struct net_t *np,
  struct delctrl_t *dctp, struct dcevnt_t *dcep)
{
 int32 e_val, save_eligible;

 e_val = dcep->dce_edgval;
 /* AIV 03/01/12 - need to mark dctp if has edge value */
 if (e_val != NOEDGE) 
  {
   /* make sure the edge is the same */
   if (dctp->d_edgval)
    {
     if (dctp->d_same_edge) dctp->d_same_edge = (e_val == dctp->d_edgval);
    }
   dctp->d_has_edge = TRUE;
   dctp->d_edgval = e_val;
  }
 else if (dctp->d_only_edges) dctp->d_only_edges = FALSE;

 /* if greater than one always @(net1 or) is needed here - mark with 2 */
 if (dctp->d_gt_one) dctp->d_gt_one = 2;
 else dctp->d_gt_one = 1;

 /* may have to turn off if not scalar */
 if (dctp->d_only_scalars) dctp->d_only_scalars = !np->n_isavec;

 /* may have to turn off if not vectored */
 if (dctp->d_only_vectors) dctp->d_only_vectors = np->n_isavec;

 /* check if net is used on rhs */
 if (!dctp->d_uses_nets_on_rhs)
  {
   /* to suppress eligible dumping if on */
   save_eligible = __xprop_not_eligible;
   __xprop_not_eligible = FALSE;
   dctp->d_uses_nets_on_rhs =  
   __is_stlst_net_on_rhs_assign(dctp->xprop_xedge_actionst, np, NULL); 
   __xprop_not_eligible = save_eligible;
  }
}


/*
 *
 */
static void bld_xprop_xedge_flowg(struct net_t *np,
 struct st_t *stp, struct delctrl_t *dctp)
{
 struct flowg_t *fgp;
 struct bblk_t *enter_bbp, *set_bbp, *not_set_bbp;
 struct xprop_t *xprop;
 struct ctev_t *ctevp;
 int32 cint_ti, schd_tev_ti, tevp_ti, scal_adr_ti, t1_ti, save_ti;
 int32 needs_set_net;

 __cur_bbp = NULL;
 /* can have multiple calls to this off different nets if created return */
 if (stp->enter_created) return;

 fgp = __alloc_flowg(FLOWG_PROC);
//AIV LOOKATME - maybe the ones that need threads should be turned off???
 fgp->has_thread_ctrl = dctp->needs_thread;
 __cur_flowg = fgp;
 if (__proc_flowg_hd == NULL) __proc_flowg_hd = __proc_flowg_tail = fgp;
 else
  {
   __proc_flowg_tail->flowgnxt = fgp;
   __proc_flowg_tail = fgp;
  }
 __cur_ifrom_u.from_stp = stp;

 enter_bbp = __alloc_bblk(FALSE); 
 __start_bblk(enter_bbp);
 enter_bbp->after_suspend = TRUE;
 __emit_enter_proc(stp);

 __needs_thread_ctrl = dctp->needs_thread;

 xprop = stp->st.sif.xprop;
 /* DBG remove --- */
 if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
 if (stp->stmttyp != S_IF) __misc_terr(__FILE__, __LINE__);
 if (__no_xprop_edges) __misc_terr(__FILE__, __LINE__); 
 /* --- */

 if (__xprop_trace_on) 
  {  
   //AIV LOOKATME - is this setup for -1 ????? - should be
   cint_ti = __gen_cint_tn(-1);
   gen_xprop_trace_write(stp, cint_ti, cint_ti, cint_ti);
  }

 scal_adr_ti = -1;
 needs_set_net = TRUE;
 /* if only one @(posedge clk) - just set it to either 0/1 */
 if (dctp->d_only_edges && dctp->d_only_scalars && dctp->d_gt_one == 1 && 
     dctp->d_same_edge)
  {
   needs_set_net = FALSE;
   scal_adr_ti = __gen_ld_netbp(np);
   save_ti = __gen_tn(SR_CINT, WBITS); 
   __emit_copy(WRDBYTES, scal_adr_ti, save_ti);
   if (dctp->d_edgval == E_POSEDGE) __emit_store_cint(scal_adr_ti, 1, WRDBYTES);
   else if (dctp->d_edgval == E_NEGEDGE) 
    {
     __emit_store_cint(scal_adr_ti, 0, WRDBYTES);
    }
   else __misc_terr(__FILE__, __LINE__);
  }
 /* if only vectors do not check either */
 else if (dctp->d_only_vectors)
  {
   needs_set_net = FALSE;
  }
 /* if it uses no nets on rhs these are never set */
 else if (!dctp->d_uses_nets_on_rhs)
  {
   needs_set_net = FALSE;
  }

 if (needs_set_net)
  {
   scal_adr_ti = __emit_xprop_xedge_net(stp);
   /* AIV 03/01/12 - notice this returns saved value into ecx */
   save_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, AR_CX);
  }
     
 //AIV EXPROP - xprop2???
//AIV LOOKATME - is first block - then xblock always set to 0????
 gen_set_xprop_accum_block(stp, xprop);
 gen_xprop_stlst(stp->st.sif.thenst, 1, stp);

 //AIV - restore just does the combine back into itself
 gen_set_restore_xprop_accum_block_toself(stp, xprop);

 if (scal_adr_ti != -1)
  {
   if (dctp->d_only_scalars)
    {
     __st_insn(I_STOREA, AM_REG, save_ti, AM_NDXREG, scal_adr_ti);
    }
   else
    {
     not_set_bbp = __alloc_bblk(FALSE); 
     set_bbp = __alloc_bblk(FALSE); 
     t1_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, scal_adr_ti); 
     __emit_jmp_0(not_set_bbp, set_bbp, t1_ti);
     __start_bblk(set_bbp);
     __st_insn(I_STOREA, AM_REG, save_ti, AM_NDXREG, scal_adr_ti);
     __start_bblk(not_set_bbp);
    }
  }

 gen_assign_xprop_accum_values(stp);

 ctevp = get_merged_dctp_ctev(dctp);
 if (ctevp == NULL) ctevp = dctp->head_ctevp;

 /* DBG remove --- */
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 if (ctevp->wrapper_type == WRAPPER_PROCESS_THRD_EV) 
   __misc_terr(__FILE__, __LINE__);
 /* ----- */
 
 schd_tev_ti = __gen_dce_schd_tev(dctp);
 tevp_ti = __gen_ctevp_adr_tn(ctevp);
 __emit_save_tevp_to_schd(tevp_ti, schd_tev_ti);

 if (need_complete_or_suspend()) __emit_complete();
 __needs_thread_ctrl = FALSE; 
 __cur_flowg = NULL;
}

/*
 * return TRUE if need to record the net which triggered the always @
 */
extern int32 __needs_xedge_net_record(struct delctrl_t *dctp)
{
 /* if only one @(posedge clk) - just set it to either 0/1 */
 if (dctp->d_only_edges && dctp->d_only_scalars && dctp->d_gt_one == 1 && 
     dctp->d_same_edge)
  {
   return(FALSE);
  }
 /* if only vectors do not check either */
 else if (dctp->d_only_vectors) 
  {
   return(FALSE);
  }
 else if (!dctp->d_uses_nets_on_rhs)
  {
   return(FALSE);
  }
 return(TRUE);
}
#endif

/*
 *
 */
static void bld_delctrl_merged_fgs(struct mod_t *mdp)
{
 int32 i;
 struct delctrl_t *dctp;
 struct delctrl_t **da;

 if (mdp->dctrl_size == 0) return;
 da = mdp->dctrl_array;
 for (i = 0; i < mdp->dctrl_size; i++)
  {
   dctp = da[i];
   if (dctp->is_merged || dctp->merged_dctp == NULL) continue;
   if (dctp->needs_thread) continue; 

   bld_delctrl_head_fg(dctp);
  }
}
     
/*
 *
 */
static void bld_delctrl_head_fg(struct delctrl_t *head_dctp)
{
 int32 tevp_ti, schd_tev_ti;
 struct delctrl_t *dctp;
 struct flowg_t *fgp;
 struct bblk_t *enter_bbp;
 struct st_t *stp;
 struct ctev_t *ctevp;

 __cur_bbp = NULL;
 fgp = __alloc_flowg(FLOWG_MDC);
//AIV FIXME
 fgp->has_thread_ctrl = FALSE;
 __cur_flowg = fgp;
 if (__proc_flowg_hd == NULL) __proc_flowg_hd = __proc_flowg_tail = fgp;
 else
  {
   __proc_flowg_tail->flowgnxt = fgp;
   __proc_flowg_tail = fgp;
  }
 stp = head_dctp->actionst;
 /* DBG remove -- */
 if (stp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 __cur_ifrom_u.from_stp = stp;
 ctevp = head_dctp->head_ctevp;
 /* DBG remove -- */
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 enter_bbp = __alloc_bblk(FALSE); 
 __start_bblk(enter_bbp);
 enter_bbp->after_suspend = TRUE;
 __emit_enter_mdc(ctevp->dctrl_ndx);

 __gening_mdc = TRUE;
 gen_stlst(stp, TRUE);

 for (dctp = head_dctp->merged_dctp; dctp != NULL; dctp = dctp->merged_dctp)
  {
   gen_stlst(dctp->actionst, TRUE);
  }
 __gening_mdc = FALSE;
 
 tevp_ti = __gen_ctevp_adr_tn(ctevp);
 schd_tev_ti = __gen_dce_schd_tev(head_dctp);
 __emit_save_tevp_to_schd(tevp_ti, schd_tev_ti);
 if (need_complete_or_suspend()) __emit_complete();
 __cur_flowg = NULL;
}

/*
 *
 */
static struct ctev_t *get_merged_dctp_ctev(struct delctrl_t *dctp)
{
 struct ctev_t *ctevp;

 if (dctp->needs_thread) return(NULL); 

 if (dctp->head_dctp != NULL || dctp->merged_dctp != NULL) 
  {
   if (dctp->head_dctp != NULL) dctp = dctp->head_dctp;
   ctevp = dctp->head_ctevp;
   /* DBG remove -- */
   if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   return(ctevp);
  }
 return(NULL);
}

/*
 * generate flowgraph vm insns for all non-blocking assigns
 */
static void gen_nb_assigns(int32 is_free_version)
{
 int32 rhs_apti, blen, ctab_ndx, lhs_srep, nbytes;
 int32 cur_tevp_reg_ti;
 struct flowg_t *fgp;
 struct bblk_t *assgn_bbp;
 struct st_t *stp;
 struct nb_stmt_lst_t *nbalstp, *nbalst2;
 struct expr_t *lhsx, *rhsx;
 struct xstk_t *xsp;

 /* produce a flow graph for every non-blocking assign on list */
 for (nbalstp = __nb_stmt_hd; nbalstp != NULL; nbalstp = nbalst2)
  {
   nbalst2 = nbalstp->stnxt;
   /* not all nb assign can alloc a new event no need for free version */
   if (is_free_version && !nbalstp->need_free_fg) continue;
   stp = nbalstp->stp;

   /* setup the non-blocking enter info into the stmt */
   /* AIV 11/09/06 - if non-blocking can be set back to -1 */
   /* by folding a statement (case statment fold) */
   if (stp->unreachable) continue;
  
   /* normal setup flowgraph */
   __cur_bbp = NULL;
   fgp = __alloc_flowg(FLOWG_PROC);
   /* AIV 10/31/07 - need to indicate flow graph is non-blocking */
   /* nb can create new alloced events which need to be put on free list */
   fgp->is_nb = TRUE;
   /* indicate to flow graph is this is the 'malloc' version which must free */
   /* at the end of the flow graph prior to jumping to next event */
   fgp->is_nb_free = is_free_version;
   /* if not a scalar and constant on rhs must free malloc space as well as */
   /* event */ 
   if (!nbalstp->is_scalar && !nbalstp->has_rhs_const)
    {
     fgp->is_nb_rhs_mem = TRUE;
    }
 
   /* AIV 10/12/07 - must indicate checkig for pnd0s to indicate trigger */
   /* which is set at runtime */
   if (!nbalstp->processing_pnd0s) fgp->has_nb_pnd0s = TRUE;
   __cur_flowg = fgp;

   if (__proc_flowg_hd == NULL) __proc_flowg_hd = __proc_flowg_tail = fgp;
   else
    {
     __proc_flowg_tail->flowgnxt = fgp;
     __proc_flowg_tail = fgp;
    }
   __cur_ifrom_u.from_stp = stp;
   /* create the assign block */
   assgn_bbp = __alloc_bblk(FALSE); 
   __start_bblk(assgn_bbp);
   assgn_bbp->after_suspend = TRUE;

   /* setup the non-blocking enter info into the stmt */
   /* DBG remove -- */
   if (!stp->is_nb_enter) __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* setup the non-blocking enter info into the stmt */
   if (is_free_version) __emit_enter_nb_proc_free(stp);
   else __emit_enter_nb_proc(stp);

  /* AIV 09/05/07 - if don't know if pnd0s or not must check for flag at rt */
  cur_tevp_reg_ti = -1;
  /* AIV 2/13/08 - non-blocking are now stored as a separate list so no */
  /* need to schedule to later be placed on the nb list */
  /* AIV 01/31/10 - change these to now used known value for __cur_tevp */
  /* for these nb backend assign all __cur_tevp are now set in %eax */
  /* all alloc/'free' versions were left the same */
  /* also added a __emit_nb_next_event routine to inline the jumping */
  /* to the next event so that the reg alloc can remove __cur_tevp */
  if (!nbalstp->processing_pnd0s)
   {
    /* AIV 10/12/07 - must shut off the __cur_tevp->trigger flag */
    cur_tevp_reg_ti = __emit_nb_cur_tev_reg();
    __emit_set_tevp_trigger_off(cur_tevp_reg_ti);
   }
  else if (!fgp->has_nb_pnd0s && !is_free_version)
   {
    /* AIV 10/12/07 - must shut off the __cur_tevp->trigger flag */
    cur_tevp_reg_ti = __emit_nb_cur_tev_reg();
    __emit_set_tevp_trigger_off(cur_tevp_reg_ti);
   }

  lhsx = stp->st.spra.lhsx;
  rhsx = stp->st.spra.rhsx;
  blen = lhsx->szu.xclen;
  /* if rhs nba is constant just evaluate the rhs constant value */
  if (__lhsexpr_var_ndx(lhsx))
   {
    if (cur_tevp_reg_ti == -1)
     {
      cur_tevp_reg_ti = __emit_nb_cur_tev_reg();
     }
    gen_nb_assign_varndx(lhsx, cur_tevp_reg_ti);
    if (is_free_version) __emit_complete();
    else __emit_nb_next_event(cur_tevp_reg_ti);
    continue;
   }
  else if (nbalstp->has_rhs_const)
   {
    xsp = __eval_assign_rhsexpr(rhsx, lhsx);
    ctab_ndx = __allocfill_cval_new(xsp->ap, xsp->bp, wlen_(blen));
    /* build a new right width constant */
    lhs_srep = __get_lhs_srep(lhsx, &nbytes);
    if (lhs_srep == SR_BIT2S) lhs_srep = SR_BIT2S;
    else lhs_srep = SR_VEC;
    /* AIV 10/14/10 - this nees to pass the rhsx->is_real flag */
    rhs_apti = __gen_contab_tn(ctab_ndx, blen, FALSE, rhsx->has_sign, 
      rhsx->is_real, lhs_srep);
    __pop_xstk();
   }
  else if (nbalstp->has_static_mem)
   {
    /* AIV 04/13/07 - now can be scal as well not always convert to vector */
    lhs_srep = __get_lhs_srep(lhsx, &nbytes);

    rhs_apti = __gen_nonblocking_bp_tn(stp, lhs_srep, rhsx->is_real);
   }
  else if (nbalstp->is_scalar)
   {
    if (cur_tevp_reg_ti == -1)
     {
      cur_tevp_reg_ti = __emit_nb_cur_tev_reg();
     }
    lhs_srep = __get_lhs_srep(lhsx, &nbytes);
    rhs_apti =  __emit_ld_nbrhs_scalar_val(cur_tevp_reg_ti, lhs_srep);
   }
  else
   {
    if (cur_tevp_reg_ti == -1)
     {
      cur_tevp_reg_ti = __emit_nb_cur_tev_reg();
     }
    lhs_srep = __get_lhs_srep(lhsx, &nbytes);
    rhs_apti = __emit_ld_nbrhs_valwp(cur_tevp_reg_ti, blen, lhs_srep, 
     rhsx->is_real);
   }

  /* do the actual assign */
  gen2_proc_assign(lhsx, rhs_apti);

  if (is_free_version) __emit_complete();
  else __emit_nb_next_event(cur_tevp_reg_ti);
 }
}

    
/*
 *  generate back end non-blocking assign code for lhsx with a variable
 *  index on lhs
 *  known to be an array, bsel, or indexed psel with a bi in range
 */
static void gen_nb_assign_varndx(struct expr_t *lhsx, int32 cur_tevp_reg_ti)
{
 int32 biti_ti, addr_apti, lhs_srep;
 int32 rhs_apti, blen, cint_ti, nbytes, sel_ti, save_idp_ti;
 struct mod_t *targ_mdp;
 size_t offset;
 struct gref_t *grp;
 struct tev_t *tevp;
 struct net_t *np;
 struct expr_t *idndp, *ndx1, *sel_ndp;

 /* DBG remove -- */
 if (lhsx->optyp == LCB) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->t2u.bi) - (byte *) tevp;
 biti_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, cur_tevp_reg_ti, 
  offset);

 /* bi known to be in range */
 blen = lhsx->szu.xclen;
 lhs_srep = __get_lhs_srep(lhsx, &nbytes);
 rhs_apti = __emit_ld_nbrhs_valwp(cur_tevp_reg_ti, blen, lhs_srep, 
   lhsx->is_real);
 /* if array do assign - array will handle grp's if needed */
 if (np->n_isarr)
  {
   /* AIV 02/09/11 - if array select which is not constant need to save */
   /* the select index and check to make sure in range as well */
   sel_ti = -1;
   ndx1 = lhsx->ru.x;
   if (ndx1->arr_select)
    {
     sel_ndp = ndx1->next_ndx;
     /* may have to get end index for mda */
     while (ndx1 != NULL)
      {
       sel_ndp = ndx1;
       ndx1 = ndx1->next_ndx;
      }
     offset = (byte *) &(tevp->sel_ndx) - (byte *) tevp;
     /* these are known to no be constant - otherwise they are converted to */
     /* regular part selects */
     if (sel_ndp->optyp == PARTSEL_NDX_PLUS || 
         sel_ndp->optyp == PARTSEL_NDX_MINUS)
      {
       sel_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, cur_tevp_reg_ti, 
        offset);
      }
     /* skip constant part selects here */
     else if (sel_ndp->optyp != PARTSEL && !__cvc_is_const_expr(sel_ndp))
      {
       sel_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG_DISP, cur_tevp_reg_ti, 
        offset);
      }
    }
   gen_lhs_arrsel(lhsx, -1, biti_ti, rhs_apti, FALSE, NULL, sel_ti);
  }
 else if (lhsx->optyp == PARTSEL_NDX_PLUS || lhsx->optyp == PARTSEL_NDX_MINUS)
  {
   /* do indexed part select with known in range biti1 (range 1) */
   gen_assgn_to_index_width_psel(lhsx, rhs_apti, biti_ti, -1);
  }
 else
  {
   /* do a bsel may need to get xmr address */
   addr_apti = -1;
   if (idndp->optyp == ID) 
    {
     addr_apti = __ldvar_addr(np, NULL);
     __gen_lhsbsel_var(np, addr_apti, biti_ti, rhs_apti);
    }
   else if (idndp->optyp == GLBREF)
    {
     /* AIV 05/14/12 - this needs to push the XMR idp area - would be wrong */
     /* when dumpvars since it would pass an incorrect __idp */
     grp = idndp->ru.grp;
     if (__net_chg_nd_store(np, -1, -1))
      {
       save_idp_ti = __gen_ld_xmr_idp(grp);

       targ_mdp = grp->targmdp; 
       __push_wrkitstk(targ_mdp, 0);

       addr_apti = __ldvar_addr(np, NULL);
       __gen_lhsbsel_var(np, addr_apti, biti_ti, rhs_apti);

       __gen_restore_idp(save_idp_ti);
       __pop_wrkitstk();
      }
     else
      {
       addr_apti = __ldvar_addr(np, grp);
       __gen_lhsbsel_var(np, addr_apti, biti_ti, rhs_apti);
      }
    }
   else __case_terr(__FILE__, __LINE__);

  }
 /* must always store size in tevp->t2u.nb_rhs_size in case it is malloc */
 /* uses this for free size value */
 cint_ti = __gen_cint_tn(nbytes);
 __st_insn(I_STOREA, AM_REG, cint_ti, AM_NDXREG_DISP, cur_tevp_reg_ti, offset);
}

/*
 * generate exec insns for function 
 *
 * FIXME - for now arg passing handled by interpreter
 * SJM 09/18/05 - now functions never entered from scheduler
 */
static void gen_funcbody(struct task_t *tskp)
{
 int32 save_coverage;
 struct flowg_t *fgp;
 struct bblk_t *func_bbp;
 struct bblk_t *complete_bbp;

 fgp = __alloc_flowg(FLOWG_FUNC);
 __cur_flowg = fgp;
 if (__proc_flowg_hd == NULL) __proc_flowg_hd = __proc_flowg_tail = fgp;
 else
  {
   __proc_flowg_tail->flowgnxt = fgp;
   __proc_flowg_tail = fgp;
  }
 __cur_ifrom_u.from_stp = tskp->tskst;
 __cur_bbp = NULL;

 func_bbp = __alloc_bblk(FALSE);
 func_bbp->after_suspend = TRUE;
 complete_bbp = __alloc_bblk(FALSE);

 __start_bblk(func_bbp);
 __emit_func_subr(tskp);

 __func_complete_bbp = complete_bbp;
 __processing_func = TRUE;
 /* AIV 03/10/09 - now if function uses scope just save/restore to globals */
 /* functions cannot have delays so this works fine */
 if (tskp->uses_scope) 
  { 
   save_task_scope(tskp);
  }

 /* need to set global task to be used for lowered asm net naming */ 
 /* AIV 12/15/10 - if not recording tasks coverage shut off record */
 save_coverage = __stmt_coverage;
 if (!__stmt_coverage_tasks) __stmt_coverage = FALSE;

 gen_stlst(tskp->tskst, FALSE);
 __processing_func = FALSE;
 __stmt_coverage = save_coverage;
 __func_complete_bbp = NULL;

 /* return - call must access return value */
 /* AIV 03/14/07 - function needs to have complete block in case of disable */
 __start_bblk(complete_bbp);
 if (tskp->uses_scope) 
  {
   restore_task_scope();
  }

 __emit_complete();
}

/*
 * save task scope to global values
 */
static void save_task_scope(struct task_t *tskp)
{
 int32 save_tskp_ti, tskp_ti, tskp_reg_ti;

 save_tskp_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SCP_TSKP);
 __st_insn(I_STOREA, AM_REG, save_tskp_ti, AM_NLO, NLO_SAVE_SCP_TSKP);

 tskp_ti = __gen_taskp_tn(tskp);
 tskp_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, tskp_ti);
 __st_insn(I_STOREA, AM_REG, tskp_reg_ti, AM_NLO, NLO_SCP_TSKP);
}

/*
 * restore task scope to global values
 */
static void restore_task_scope(void)
{
 int32 save_tskp_ti;

 save_tskp_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SAVE_SCP_TSKP);
 __st_insn(I_STOREA, AM_REG, save_tskp_ti, AM_NLO, NLO_SCP_TSKP);
}

/*
 * generate exec insns for task
 *
 * all storing on entry of in/inout and on return of out/inout handled
 * by caller - also if task can be disabled caller allocates and builds thrd
 */
static void gen_tskbody(struct task_t *tskp)
{
 int32 save_coverage;
 struct flowg_t *fgp;
 struct bblk_t *tsk_bbp, *complete_bbp;

 /* if task is never used don't generate code */
 if (!tskp->t_used) return;

#ifdef __XPROP__
 /* do not generate code for dummy nb xprop task holder */
 if (__compiled_sim && __xprop)
  {
   /* DBG remove -- */
   if (__inst_mod->xprop_nb_taskp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (__inst_mod->xprop_nb_taskp == tskp) return;
  }
#endif

 fgp = __alloc_flowg(FLOWG_TASK);
 __cur_flowg = fgp;
 if (__proc_flowg_hd == NULL) __proc_flowg_hd = __proc_flowg_tail = fgp;
 else
  {
   __proc_flowg_tail->flowgnxt = fgp;
   __proc_flowg_tail = fgp;
  }
 __cur_ifrom_u.from_stp = tskp->tskst;
 __cur_bbp = NULL;

 tsk_bbp = __alloc_bblk(FALSE);
 /* task entry must be after suspend because it has tn area on stack set */
 tsk_bbp->after_suspend = TRUE;

 /* SJM 09/18/05 - does not need to look like entry from scheduler */
 /* setup task arg insn called and then jump (takes over thread) */
 __start_bblk(tsk_bbp); 
 __emit_enter_task(tskp);

 /* SJM 09/18/05 - set processing func was wrong since tasks can suspend */
 /* need to set global task to be used for lowered asm net naming */ 
 complete_bbp = NULL;
 /* AIV 11/09/10 - if has a return stmt need a block to jump to */
 if (tskp->has_return) 
  {
   complete_bbp = __alloc_bblk(FALSE);
   __func_complete_bbp = complete_bbp;
  }

 /* AIV 12/15/10 - if not recording tasks coverage shut off record */
 save_coverage = __stmt_coverage;
 if (!__stmt_coverage_tasks) __stmt_coverage = FALSE;
 __gening_tsk = TRUE;
 gen_stlst(tskp->tskst, FALSE);
 __gening_tsk = FALSE;
 __stmt_coverage = save_coverage;

 if (complete_bbp != NULL) 
  {
   __start_bblk(complete_bbp);
  }
 __func_complete_bbp = NULL;

 if (!tskp->no_delay || tskp->can_be_disabled)
  {
   /* SJM 11/12/05 - if task body ends with complete remove since need */
   /* cleanup return before complete */
   if (__cur_bbp->itail != NULL
    && __cur_bbp->itail->opcod == I_RETURN)
    {
     __linkout_insn(__cur_bbp->itail->iprev, TRUE);
     __linkout_insn(__cur_bbp->itail, TRUE);
    }

   /* for either has outs or no outs if not disabled, put back cur thd here */
   __emit_leave();
   /* automatic task must return cannot free automatic malloc area */
   /* until after task outputs have been assigned  separated out routines */
   if (!tskp->is_auto) __emit_tskdone_cleanup();
   else __emit_tskdone_cleanup_auto();
   __emit_tsk_return();
  }
 else __emit_complete();
}

/*
 * generate an export DPI call 
 * - called from user DPI code to a Verilog function
 * - similar to normal task but has different return and arg passing
 */
static void gen_tskbody_export_dpi(struct task_t *tskp)
{
 struct flowg_t *fgp;
 struct bblk_t *tsk_bbp;
 struct task_pin_t *tpp;
 struct net_t *np;
 int32 offset, arg_ti, addr_ti;
#ifndef __CVC32__
 int32 argno;
#endif

 /* if task is never used don't generate code */
 fgp = __alloc_flowg(FLOWG_TASK);
 __cur_flowg = fgp;
 if (__proc_flowg_hd == NULL) __proc_flowg_hd = __proc_flowg_tail = fgp;
 else
  {
   __proc_flowg_tail->flowgnxt = fgp;
   __proc_flowg_tail = fgp;
  }
 __cur_ifrom_u.from_stp = tskp->tskst;
 __cur_bbp = NULL;

 tsk_bbp = __alloc_bblk(FALSE);
 /* task entry must be after suspend because it has tn area on stack set */
 tsk_bbp->after_suspend = TRUE;

 /* SJM 09/18/05 - does not need to look like entry from scheduler */
 /* setup task arg insn called and then jump (takes over thread) */
 __start_bblk(tsk_bbp); 
 __emit_enter_task_dpi(tskp);

 /* initialize offsets for arguments passing into DPI tasks */
 /* AIV 09/20/10 - export arg passing stack was incorrect - has fixup */
 /* in v_bbopt */
 offset = WRDBYTES;
#ifndef __CVC32__
 argno = 0;
#endif
 for (tpp = tskp->tskpins; tpp != NULL; tpp = tpp->tpnxt)
  {
   /* assign rhs in or inout arg. expr. to task local variable */
   np = tpp->tpsy->el.enp;
#ifdef __CVC32__
   arg_ti = __emit_get_export_arg_dpi(np, &offset);
#else
   arg_ti = __emit_get_export_arg_dpi(np, &argno, &offset);
#endif
   addr_ti = __ldvar_addr(np, NULL);
   __gen_st_val(np, addr_ti, arg_ti);
  }

 /* SJM 09/18/05 - set processing func was wrong since tasks can suspend */
 /* need to set global task to be used for lowered asm net naming */ 

 __gening_tsk = TRUE;
 gen_stlst(tskp->tskst, FALSE);
 __gening_tsk = FALSE;

 if (!tskp->no_delay || tskp->can_be_disabled)
  {
   /* SJM 11/12/05 - if task body ends with complete remove since need */
   /* cleanup return before complete */
   if (__cur_bbp->itail != NULL
    && __cur_bbp->itail->opcod == I_RETURN)
    {
     __linkout_insn(__cur_bbp->itail->iprev, TRUE);
     __linkout_insn(__cur_bbp->itail, TRUE);
    }

   /* for either has outs or no outs if not disabled, put back cur thd here */
   __emit_leave();
   /* automatic task must return cannot free automatic malloc area */
   /* until after task outputs have been assigned  separated out routines */
   if (!tskp->is_auto) __emit_tskdone_cleanup();
   else __emit_tskdone_cleanup_auto();
   __emit_tsk_return();
  }
 else __emit_complete();
}

/*
 * ROUTINES TO GEN 3 ADR TUPLES FOR PROCEDURAL STMTS
 */

/*
 * gen vm insn for stmt list
 */
static void gen_stlst(struct st_t *hdstp, int32 has_endgoto)
{
 struct st_t *stp;
 
 /* -- REMOVE ME ---
 if (__opt_debug_flg)
  {
   stp = hdstp;
   __my_fprintf(stdout, "==> AT %s %s - BBLK STLST GEN (%s) unbhd=%d\n",
    __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt),
    __inst_mod->msym->synam, __to_sttyp(__xs2, stp->stmttyp),
    stp->st_unbhead);
  }
 --- */

 for (stp = hdstp; stp != NULL;)
  {
   stp = gen_stmt(stp, has_endgoto);
  }
}

/*
 * gen vm insns for one stmt
 */
static struct st_t *gen_stmt(struct st_t *stp, int32 has_endgoto)
{
 struct bblk_t *stmt_bbp;
 struct st_t *nxtstp, *end_stp;

 /* need global that points to currently being gened stmt */
 __cur_ifrom_u.from_stp = stp;

 /* AIV 08/17/11 - need to set these now for warning messages */
 /* currently just for div by 0 real warnings */
 __generating_stp = stp;

 /* if no cur bblk always alloc but if after suspend, the needed bblk */
 /* has already been allocated and made current */
 if (__cur_bbp == NULL)
  {
   /* always must start new bblk on entry from scheduler */
   /* SJM 06/15/05 - only need new bblk if not after suspend entry */
   stmt_bbp = __alloc_bblk(FALSE);
   __start_bblk(stmt_bbp);
  }

 /* AIV 12/15/10 - record stmt coverage */
 if (__stmt_coverage) __emit_stmt_coverage(stp);

 /* -- REMOVE ME ---
 if (__opt_debug_flg)
  {
   extern void __dmp_stmt(FILE *, struct st_t *, int32);

   __my_fprintf(stdout,
    "==> AT %s - ST GEN (%s) unbhd=%d, lpend_gt=%d, dctl_gt=%d, gt_dest=%d\n",
    __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt),
    __to_sttyp(__xs2, stp->stmttyp), stp->st_unbhead, stp->lpend_goto,
    stp->dctrl_goto, stp->lpend_goto_dest);
   __my_fprintf(stdout, " STMT:   ");
   __dmp_stmt(stdout, stp, FALSE);
   __my_fprintf(stdout, "\n");
  }
 --- */

 switch ((byte) stp->stmttyp) {
  case S_PROCA:
   /* generate code to load value onto xstk */
   gen_proc_assign(stp->st.spra.lhsx, stp->st.spra.rhsx, -1);
   break;
  case S_NBPROCA:
   /* only non delay form non blocking assign here */
   gen_nblkrhs_proca(stp, stp->st.spra.rhsx, -1);
   break;
  case S_RHSDEPROCA:
   gen_rhs_dctl_proca(stp);
   break;
  case S_IF:
#ifdef __XPROP__
   /* if xprop stmt - generate xprop code */
   if (stp->xprop_eligible)
    {
     if (__xprop2) gen_xprop2_if_stmt(stp);
     else
      {
       /* check if select has xzs */
       gen_xprop_enter(stp);
      }
    }
   else gen_if_stmt(stp);
#else
   gen_if_stmt(stp);
#endif
   break;
  case S_CASE:
#ifdef __XPROP__
   /* case xprop stmt - generate xprop code */
   if (stp->xprop_eligible)
    {
     /* xprop2 is handled in gen_case code */
     if (__xprop2) gen_case(stp);
     else
      {
       /* check case select has xzs */
       gen_xprop_enter(stp);
      }
    }
   else gen_case(stp);
#else
   gen_case(stp);
#endif
   break;
  case S_FOREVER:
   gen_forever(stp);
   break;
  case S_REPSETUP: 
   gen_repsetup(stp);
   break;
  case S_REPEAT:
   /* since know repeat stmt always follow rep setup - gen their */
   gen_repeat(stp);
   break;
  case S_WHILE:
   gen_while(stp);
   break;
  case S_DO_WHILE:
   gen_do_while(stp);
   break;
  case S_FORASSGN:
   /* for assign does nothing during code gen - only need for interpreter */
   gen_proc_assign(stp->st.spra.lhsx, stp->st.spra.rhsx, -1);
   break;
  case S_FOR:
   gen_for(stp);
   break;
  case S_WAIT:
   gen_wait(stp);
   break;
  case S_REPDCSETUP:
   gen_rep_ectl_setup(stp);
   /* DBG remove */
   if (stp->stnxt == NULL || stp->stnxt->stmttyp != S_DELCTRL)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* return stmt after next that is the already gened ectrl */
   return(stp->stnxt);
  case S_DELCTRL:
   /* for all of blocking prefix, rhs and non blocking - both dctl/ectl */
   nxtstp = gen_dctl_stmt(stp);
   return(nxtstp);
  case S_NAMBLK:
   nxtstp = gen_namblk(stp);
   return(nxtstp);
  case S_UNBLK:
   if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);
   /* if this has a GOTO at end,  it needs to be ignored */
   gen_stlst(stp->st.sbsts, TRUE);
   if (stp->stnxt != NULL) __pop_cc_stmt();

   end_stp = __find_stlst_end(stp->st.sbsts);
   /* DBG remove -- */
   if (end_stp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (end_stp->stmttyp == S_GOTO)
    {
     if (end_stp->dctrl_goto) return(end_stp->st.sgoto);
    }
   break; 
  case S_UNFJ:
   gen_unfj(stp);
   break;
  case S_TSKCALL:
   gen_tskcall(stp);
   break;
  case S_QCONTA:
   gen_qconta(stp);
   break;
  case S_QCONTDEA:
   gen_qcontdea(stp);
   break;
  case S_CAUSE:
   gen_cause(stp);
   break;
  case S_DSABLE:
   gen_disable(stp);
   break;
  case S_INC:
   gen_stmt_inc_dec(stp, TRUE);
   break;
  case S_DEC:
   gen_stmt_inc_dec(stp, FALSE);
   break;
  case S_STNONE: case S_NULL:
   break;
  case S_BREAK: 
   /* DBG remove -- */
   if (__loop_break_bbp == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   /* AIV 09/29/10 - if loop break just jump to block */
   __emit_jmp(__loop_break_bbp);
   break;
  case S_CONTINUE:
   /* DBG remove -- */
   if (__loop_continue_bbp == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   /* AIV 09/29/10 - if loop continue just jump to block */
   __emit_jmp(__loop_continue_bbp);
   break;
  case S_FUNCCALL:
   gen_fcall(NULL, stp);
   break;
  case S_RETURN: 
   /* DBG remove -- */
   if (__func_complete_bbp == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   __emit_jmp(__func_complete_bbp); 
   break;
  case S_GOTO:
   if (has_endgoto)
    {
     /* DBG remove -- THIS IS WRONG - GET RID OF?
     if (stp->stnxt == NULL && stp->dctrl_goto)
      __misc_terr(__FILE__, __LINE__);
     --- */
     /* -- REMOVE ME --
     if (__opt_debug_flg)
      {
       char s1[RECLEN], s2[RECLEN];

       if (__prpsti == -1) strcpy(s2, "**EMPTY STACK**");
       else
        {
         stp2 = __prpstk[__prpsti];

         if (stp2 == NULL) strcpy(s2, "**NULL**");
         else __bld_lineloc(s2, stp2->stfnam_ind, stp2->stlin_cnt);

         __my_fprintf(stdout,
          "==> goto: %s tos %s, lpend=%d, dctl=%d, gt_dst=%d\n",
          __bld_lineloc(s1, stp->stfnam_ind, stp->stlin_cnt), s2,
          stp->lpend_goto, stp->dctrl_goto, stp->lpend_goto_dest);
        }
      }
     --- */
     if (stp->dctrl_goto) return(stp->st.sgoto);
     break;
    }
   /* DBG remove -- */ 
   if (stp->stnxt == NULL && stp->lpend_goto)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* -- REMOVE ME
   if (__opt_debug_flg)
    {
     char s1[RECLEN], s2[RECLEN];

     stp2 = __prpstk[__prpsti];
     if (stp2 == NULL) strcpy(s2, "**NULL**");
     else __bld_lineloc(s2, stp2->stfnam_ind, stp2->stlin_cnt);
       
     __my_fprintf(stdout,
      "==> non endgoto %s tos %s, lpend=%d, dctl=%d, gt_dst=%d\n",
      __bld_lineloc(s1, stp->stfnam_ind, stp->stlin_cnt), s2,
      stp->lpend_goto, stp->dctrl_goto, stp->lpend_goto_dest);
     __my_fprintf(stdout, "    goto dest: %s (styp=%s)\n", 
      __bld_lineloc(s1, stp->st.sgoto->stfnam_ind,
     stp->st.sgoto->stlin_cnt), __to_sttyp(s2, stp->stmttyp));
    }
   --- */
   if (stp->dctrl_goto) return(stp->st.sgoto);
   /* DBG remove */
   if (!stp->lpend_goto) __misc_terr(__FILE__, __LINE__);
   /* --- */
   break;
  /* no code for break points in generated code */
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}

/*
 * ROUTINES TO GEN VM INSNS FOR PROCEDURAL ASSIGN STMT
 * COMPLEX BECAUSE DECOMPOSES CONCATS
 */

/*
 * gen vm insns for procedural assign
 */
static void gen_proc_assign(struct expr_t *lhsx, struct expr_t *rhsx,
 int32 accum_ti)
{
 int32 lxi, rxi, srtyp, want_a_vec, lhs_srep, nbytes;
 int32 lhsnels, rhsnels, t1_apti, rhs_apti, nd_sign;
 struct expr_t *catndp, **lhsxtab, **rhsxtab;
 struct expr_t *idndp;
 struct mod_t *in_mdp;
 struct net_t *np;

 lhsnels = 0;
 lhsxtab = NULL;
 rhsnels = 0;
 rhsxtab = NULL;

 /* if SV string assign handle in seperate routine */
 if (lhsx->is_sv_string)
  {
   gen_proc_assign_string(lhsx, rhsx);
   return;
  }

 /* AIV 01/03/11 - this should have been here in this SV version */
 /* catch the special case where the LHS is a id and the RHS is a const */
 /* scalar neta = 1 */
 if (lhsx->optyp == ID && rhsx->consubxpr && rhsx->optyp == NUMBER)
  {
   gen_proc_assign_const_to_id(lhsx, rhsx);   
   return;
  }


 /* case 1: neither side of assign concat */
 if (lhsx->optyp != LCB && rhsx->optyp != LCB)
  {
do_noncat:

   /* SJM 10/18/05 - simulates eval assign rhs expr - use rhs signedness */
   nd_sign = rhsx->has_sign;

   /* get lhs net to determine type/size needed */
   idndp = __get_lvalue_idndp(lhsx);
   np = idndp->lu.sy->el.enp;

   /* if array can either be scalar or vector */ 
   if (np->srep == SR_ARRAY)
    {
     /* AIV 07/31/07 - if global array ref need to use net address pointer */
     __get_nets_containing_sy(np, &(in_mdp));
     if (in_mdp != __inst_mod) __need_net_addr = TRUE;

     srtyp = __get_array_srep_type(np);
     if (np->nwid == 1)
      {
       if (accum_ti == -1) t1_apti = __gen_expr_eval(rhsx, -1);
       else t1_apti = accum_ti;
       rhs_apti = __gen_cnvt_srep_ifneeded(t1_apti, srtyp, lhsx->szu.xclen,
        nd_sign, lhsx->is_real, FALSE);
      }
     else
      {
       /* AIV 11/10/09 - want a vector here */
       if (accum_ti == -1) t1_apti = __gen_expr_eval(rhsx, WANT_A_VEC);
       else t1_apti = accum_ti;
       rhs_apti = __gen_cnvt_srep_ifneeded(t1_apti, srtyp, lhsx->szu.xclen,
        nd_sign, lhsx->is_real, FALSE);
      }
    }
   else
    {
     /* AIV 07/31/07 - if global ref need to use address for net loading */
     if (lhsx->optyp == GLBREF) __need_net_addr = TRUE;

     lhs_srep = __get_lhs_srep(lhsx, &nbytes);
     want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : 
       -1;
     /* AIV 11/10/09 - want a vector here if net is a vectore */
     if (accum_ti == -1) t1_apti = __gen_expr_eval(rhsx, want_a_vec);
     else t1_apti = accum_ti;
     /* type is equal to the lhs net */
     rhs_apti = __gen_cnvt_srep_ifneeded(t1_apti, lhs_srep, lhsx->szu.xclen,
      nd_sign, lhsx->is_real, FALSE);
    }

   /* AIV 10/22/07 - only need rhs apti to be an address */
   __need_net_addr = FALSE;
   gen2_proc_assign(lhsx, rhs_apti);
   goto free_and_ret;
  }

 /* if either side, concat must reverse so igen low to high */
 /* first reverse both into tables containing just element expr */
 if (lhsx->optyp == LCB)
  {
   lhsnels = __cnt_cat_size(lhsx);
   lhsxtab = (struct expr_t **)
    __my_malloc(lhsnels*sizeof(struct expr_t *));
   lxi = lhsnels - 1;
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x, lxi--)
    { lhsxtab[lxi] = catndp->lu.x; }
  }

 if (rhsx->optyp == LCB)
  {
   rhsnels = __cnt_cat_size(rhsx);
   rhsxtab = (struct expr_t **)
    __my_malloc(rhsnels*sizeof(struct expr_t *));
   rxi = rhsnels - 1;
   /* fill expr tab in reverse order */
   for (catndp = rhsx->ru.x; catndp != NULL; catndp = catndp->ru.x, rxi--)
    { rhsxtab[rxi] = catndp->lu.x; }
  }

 /* case 2: both lhs and rhs concat */
 if (lhsx->optyp == LCB && rhsx->optyp == LCB)
  {
   /* special case 1: both 1 element cats */
   if (lhsx->ru.x->ru.x == NULL && rhsx->ru.x->ru.x == NULL)
    {
     lhsx = lhsx->ru.x->lu.x;
     rhsx = rhsx->ru.x->lu.x;
     goto do_noncat;
    }
   /* special case 2: rhs 1 element concat */
   if (rhsx->ru.x->ru.x == NULL)
    { rhsx = rhsx->ru.x->lu.x; goto do_lhscat; }
   /* special case 3: lhs 1 element concat */
   if (lhsx->ru.x->ru.x == NULL)
    { lhsx = lhsx->ru.x->lu.x; goto do_rhscat; }

   /* special case 4: cats match exactly - i.e. perfectly decompose and */
   /* eliminate all concats from rhs then gen simple insn assign for each */
   if (gen_cat_to_cat_match(lhsx, lhsxtab, lhsnels, rhsx,
    rhsxtab, rhsnels)) goto free_and_ret; 

   /* LOOKATME - could find partial matches in cat to cat */
   /* if not exact match, treat as complex rhs lhs concat */ 
   goto do_lhscat;
  }

 /* case 2: lhs concat but rhs not treated as concat (x1, x2, x3) = xR */
 if (lhsx->optyp == LCB && rhsx->optyp != LCB)
  {
do_lhscat:
   gen_lhs_concat(rhsx, lhsxtab, lhsnels, lhsx->szu.xclen);
   goto free_and_ret;
  }

 /* case 3: rhs concat but lhs not concat - xL = (x1, x2, x3) */ 
 /* normal pattern is XL[bi1:bi2] = x1, ... */
 if (lhsx->optyp != LCB && rhsx->optyp == LCB)
  {
do_rhscat:
   /* can only decompose rhs concat for non scalar (ID/XMR/PSEL) lhs */
   /* if lhs assign to bsel or 1 bit var, must assign just low rhs cat el */
   /* if lhs arr select, must eval rhs as normal rhs expr and then assign */
   if (lhsx->optyp == LSB || lhsx->szu.xclen == 1)
    {
     if (lhsx->optyp == LSB && lhsx->lu.x->lu.sy->el.enp->n_isarr)
      goto do_noncat;
     /* this handle cases like [scalar or lhs bsel] = {a, b, c}; */
     /* notice since rhs concat el table low bit - low index, use low only */
     rhsx = rhsxtab[0]; 
     goto do_noncat;
    }

   if (cat_need_rhs_eval2(lhsx, rhsxtab, rhsnels, rhsx->szu.xclen))
    {
     /* although rhs is concat (but not lhs), because can't decompose */
     /* because rhs concat contains lhs must eval as rhs expr */
     /* AIV 11/10/09 - want a vector here */
     lhs_srep = __get_lhs_srep(lhsx, &nbytes);
     want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : 
       -1;
     t1_apti = __gen_expr_eval(rhsx, want_a_vec);

     if (lhs_srep == SR_BIT2S) srtyp = SR_BIT2S;
     else srtyp = SR_VEC;
     /* SJM 10/18/05 - simulates eval assign rhs expr - use rhs signedness */
     nd_sign = rhsx->has_sign;
     rhs_apti = __gen_cnvt_srep_ifneeded(t1_apti, srtyp, lhsx->szu.xclen,
      nd_sign, lhsx->is_real, FALSE);
     gen2_proc_assign(lhsx, rhs_apti);

     goto free_and_ret;
    }

   gen_rhs_assgn_concat(lhsx, rhsxtab, rhsnels);
   goto free_and_ret;
  }
 __misc_terr(__FILE__, __LINE__);

free_and_ret:
 /* final step, free work expr tables */
 if (lhsxtab != NULL)
  __my_free(lhsxtab, lhsnels*sizeof(struct expr_t *));
 if (rhsxtab != NULL)
  __my_free(rhsxtab, rhsnels*sizeof(struct expr_t *));
}


/*
 * assign a SV string value
 * these are split into wrappers for string id or array lhs
 * 3 possible cases for rhs
 * s1 = 
 *  s1 = constant
 *  s1 = stringid
 *  s1 = all other rhs exprs
 * same with arrays sarray[1] = 
 * handles the char store case as well
 *
 * AIV STRING FIXME - xmrs are wrong
 */
static void gen_proc_assign_string(struct expr_t *lhsx, struct expr_t *rhsx)
{
 struct expr_t *lhsx_idndp, *rhsx_idndp;
 struct net_t *lhs_np, *rhs_np;
 struct xstk_t *xsp;
 struct bblk_t *outofrng_bbp;
 int32 ctab_ndx, rhs_apti, blen, bi, bi_ti, cint_ti, nchars;

 lhsx_idndp = __get_lvalue_idndp(lhsx);
 lhs_np = lhsx_idndp->lu.sy->el.enp;

 /* if [ either array or character select */
 if (lhsx->optyp == LSB)
  {
   /* handle the array case */
   if (lhs_np->n_isarr) 
    {
     outofrng_bbp = NULL;
     /* check select index is in range */
     if (lhsx->ru.x->optyp == NUMBER)
      {
       bi = __get_comp_num_ndx(lhsx->ru.x);
       /* if out of range nothing to do */
       if (bi == -1) return;
       bi_ti = __gen_cint_tn(bi);
      }
     else 
      {
       outofrng_bbp = __alloc_bblk(FALSE);
       bi_ti = __gen_comp_ndx(lhs_np, lhsx->ru.x, outofrng_bbp, FALSE);
      }

     /* case 1: rhs is a constant value */
     if (rhsx->consubxpr && rhsx->optyp == NUMBER)
      {
       xsp = __eval_assign_rhsexpr(rhsx, lhsx);
       blen = xsp->xslen;
       ctab_ndx = __allocfill_cval_new(xsp->ap, xsp->bp, wlen_(blen));
       rhs_apti = __gen_contab_tn(ctab_ndx, blen, FALSE, rhsx->has_sign, FALSE, 
        SR_STRING);
       __pop_xstk();
       nchars = (blen+7)/8;
       cint_ti = __gen_cint_tn(nchars);
       __emit_st_string_array_const(lhs_np, bi_ti, rhs_apti, cint_ti);
      }
     /* case 2: rhs is a string ID value */
     else if (rhsx->optyp == ID)
      {
       rhsx_idndp = __get_lvalue_idndp(rhsx);
       rhs_np = rhsx_idndp->lu.sy->el.enp;
       __emit_st_string_array_var(lhs_np, rhs_np, bi_ti);
      }
     /* case 3: all other rhs expressions */
     else
      {
       __emit_st_string_array_rhsx(lhs_np, rhsx, bi_ti);
      }
     if (outofrng_bbp != NULL) __start_bblk(outofrng_bbp);
    }
   else 
    {
     /* store the string char (byte) */
     if (lhsx->ru.x->optyp == NUMBER)
      {
       bi = __get_comp_num_ndx(lhsx->ru.x);
       /* if out of range nothing to do */
       if (bi == -1) return;
       bi_ti = __gen_cint_tn(bi);
      }
     else bi_ti = __gen_expr_eval(lhsx->ru.x, lhsx->ru.x->szu.xclen);
     rhs_apti = __gen_expr_eval(rhsx, rhsx->szu.xclen);
     __emit_st_string_byte(lhs_np, bi_ti, rhs_apti);
    }
   return;
  }

 /* regular string assign */
 /* case 1: rhs constant */
 if (lhsx->optyp == ID && rhsx->consubxpr && rhsx->optyp == NUMBER)
  {
   xsp = __eval_assign_rhsexpr(rhsx, lhsx);
   /* just load SV string as a constant value */
   blen = xsp->xslen;
   ctab_ndx = __allocfill_cval_new(xsp->ap, xsp->bp, wlen_(blen));
   __pop_xstk();
   rhs_apti = __gen_contab_tn(ctab_ndx, blen, FALSE, rhsx->has_sign, FALSE, 
    SR_STRING);
   __emit_sv_string_st_const(lhs_np, rhs_apti);
   return;
  }

 /* DBG remove -- */
 if (!rhsx->is_sv_string) __case_terr(__FILE__, __LINE__);
 /* ---- */

 /* case 2: rhs is string ID */
 if (rhsx->optyp == ID)
  {
   rhsx_idndp = __get_lvalue_idndp(rhsx);
   rhs_np = rhsx_idndp->lu.sy->el.enp;
   __emit_sv_string_st_var(lhs_np, rhs_np);
  }
 else
  {
   /* case 3: all other rhs exprs */
   __emit_sv_string_st_eval_rhsx(lhs_np, rhsx);
  }
}
  

/* 
 * catch the special case where the LHS is a id and the RHS is a const 
 *
 * this saves having to do conversions at run time
 * for example scalar net assign  n = 1;
 *
 * this routine gets the net type does the conversion and returns the type
 * at compile time so it isn't need at runtime
 */
static void gen_proc_assign_const_to_id(struct expr_t *lhsx, 
 struct expr_t *rhsx)
{
 struct xstk_t *xsp;
 struct net_t *np;
 int32 ctab_ndx, blen, rhs_apti, cint_ti, np_addr_ti;
 word32 *awp, *bwp;
 word32 val, bv, mask;
   
 np = lhsx->lu.sy->el.enp;
 /* evaluate the expression and do size conversion */
 xsp = __eval_assign_rhsexpr(rhsx, lhsx);
 blen = xsp->xslen;
 awp = xsp->ap;
 bwp = xsp->bp;
 ctab_ndx = -1;
 rhs_apti = -1;
 /* convert lhs constant to net type only need conversion for scalar */
 /* AIV - SJM LOOKATME is this right ???? appears to work */
 switch ((byte) np->srep) {
  case SR_SCAL:
   /* change the vector into a scalar */
   val = ((*awp) | ((*bwp) << 1));
   cint_ti = __gen_cint_tn(val);
   /* AIV 09/14/07 - if not a force and don't need to record just do the */
   /* contant assign don't move into tmp variable */
   if (!np->frc_assgn_allocated && !__net_chg_nd_store(np, -1, -1)) 
    {
     np_addr_ti = __ldvar_addr(np, NULL);
     __emit_copy(WRDBYTES, cint_ti, np_addr_ti);
     __pop_xstk();
     return;
    }
   /* AIV 10/22/08 - can now just use a movl with srep */
   // rhs_apti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, cint_ti);
   /* AIV 02/19/09 - faster to just make the constant */
   bv = 0;
   ctab_ndx = __allocfill_cval_new(&val, &bv, 1);
   rhs_apti = __gen_contab_tn(ctab_ndx, 1, FALSE, FALSE, FALSE, SR_SCAL);
   break;
  case SR_SCAL2S:
   /* change the vector into a scalar */
   if (*bwp != 0) val = 0;
   else val = *awp;
   cint_ti = __gen_cint_tn(val);
   /* AIV 09/14/07 - if not a force and don't need to record just do the */
   /* contant assign don't move into tmp variable */
   if (!np->frc_assgn_allocated && !__net_chg_nd_store(np, -1, -1)) 
    {
     np_addr_ti = __ldvar_addr(np, NULL);
     __emit_copy(WRDBYTES, cint_ti, np_addr_ti);
     __pop_xstk();
     return;
    }
   /* AIV 10/22/08 - can now just use a movl with srep */
   // rhs_apti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, cint_ti);
   /* AIV 02/19/09 - faster to just make the constant */
   bv = 0;
   ctab_ndx = __allocfill_cval_new(&val, &bv, 1);
   rhs_apti = __gen_contab_tn(ctab_ndx, 1, FALSE, FALSE, FALSE, SR_SCAL2S);
   break;
  case SR_VEC:
   /* this may do a size conversion to value not yet in contab */
   /* AIV 12/29/11 - rare mask need here for redudant digits */
   mask =  __masktab[ubits_(blen)];
   xsp->ap[wlen_(blen) - 1] &= mask;
   xsp->bp[wlen_(blen) - 1] &= mask;
   ctab_ndx = __allocfill_cval_new(xsp->ap, xsp->bp, wlen_(blen));
   /* build a new right width probably a/b constant */
   rhs_apti = __gen_contab_tn(ctab_ndx, blen, FALSE, rhsx->has_sign, FALSE, 
    SR_VEC);
   break;
  case SR_BIT2S:
   /* AIV 12/29/11 - rare mask need here for redudant digits */
   mask =  __masktab[ubits_(blen)];
   xsp->ap[wlen_(blen) - 1] &= mask;
   /* this may do a size conversion to value not yet in contab */
   /* build a new right width probably a/b constant */
   __cnvt_xzs_to_2state(xsp->ap, xsp->bp, blen);
   ctab_ndx = __allocfill_cval_new(xsp->ap, xsp->bp, wlen_(blen));
   rhs_apti = __gen_contab_tn(ctab_ndx, blen, FALSE, rhsx->has_sign, FALSE, 
      SR_BIT2S);
   break;
  case SR_SVEC:
  case SR_SSCAL:
   __case_terr(__FILE__, __LINE__);
   break;
  default: __case_terr(__FILE__, __LINE__); break;
 }
 __pop_xstk();
 /* mark the constant has having sign */
 if (rhsx->has_sign) __tntab[rhs_apti].t_signed = TRUE;
 __gen_proc_id_assign(np, rhs_apti);
}

/*
 * variant of concat need rhs eval - here lhs non concat, rhs concat 
 *
 * if rhs concat contains lhs expr, must eval rhs separately first  
 * can't use decomposed lhs psel/bsel optimization
 *
 * LOOKATME - could eval all rhs elements into tmps first then assign
 * in turn as alternative way to do this (better for very wide worse for
 * one or two word32 lhs)
 */
static int32 cat_need_rhs_eval2(struct expr_t *lhsx, struct expr_t **rhsxtab,
 int32 rels, int32 rhsx_xlen) 
{
 int32 rxi, blen;
 struct sy_t *lsyp, *rsyp;
 struct net_t *np;
 struct expr_t *catrhsx;

 /* lhs element must be lval */ 
 if ((lsyp = __iget_lval_sym(lhsx)) == NULL) 
  __misc_terr(__FILE__, __LINE__);
 /* SJM 08/19/02 - for rhs concat assign to non concat lhs if any nchg */
 /* form (includes lhs that has force/assign) must eval rhs and one assgn */
 np = lsyp->el.enp; 
 if (np->nchg_nd_chgstore) return(TRUE); 

 /* probably better now that there is special 1w code to assign first */
 blen = lhsx->szu.xclen;
 if (blen <= WBITS) return(TRUE);

 /* DBG remove -- */
 if (np->frc_assgn_allocated) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 /* AIV 06/16/09 - if psel on lhs need to eval because widths may not */
 /* match up to the rhs - need to eval and then assign if this is the case */
 if (lhsx->optyp == PARTSEL) 
  {
   if (lhsx->szu.xclen != rhsx_xlen) return(TRUE);
  }
 else if (lhsx->optyp == PARTSEL_NDX_PLUS || lhsx->optyp == PARTSEL_NDX_MINUS) 
  {
   return(TRUE);
  }

 /* can find last by seeing if lx tab element rhs is nil */
 for (rxi = 0; rxi < rels; rxi++)
  {
   catrhsx = rhsxtab[rxi];
   if ((rsyp = __iget_lval_sym(catrhsx)) == NULL) continue;
   if (lsyp == rsyp) return(TRUE);
  }
 return(FALSE);
}

/*
 * gen proc assign from rhs tmp name addr (ptr) 
 *
 * same function as interpreter exec2 proc assign 
 * AIV 02/06/06 - added the ability to handle LCB (concat) as well
 * needed for doing non-blocking assigns
 */
static void gen2_proc_assign(struct expr_t *lhsx, int32 rhs_apti)
{
 int32 addr_ti, save_idp_ti;
 struct net_t *np;
 struct gref_t *grp;
 struct mod_t *targ_mdp;
 int32 lxi, lhsnels;
 struct expr_t **lhsxtab;
 struct expr_t *catndp;
 struct tn_t *tnp;

 switch (lhsx->optyp) {
  case GLBREF:
   grp = lhsx->ru.grp;    
   np = lhsx->lu.sy->el.enp;
   /* if possible force or change store - same as ID run in XMR context */
   if (__net_chg_nd_store(np, -1, -1) || np->frc_assgn_allocated)
    {
     /* AIV 12/12/07 - for statments such as */
     /* top.mod1_ins5.reg3= #23 reg22 ; */
     /* the delay value is stored in the rhs idp were as the lhs is stored */
     /* in a separate lhs idp so the rhs must be copied */
     /* AIV LOOKATME - better to force one side to address???? */
     /* but these are rare enough were the extra copy doesn't hurt ??? */
     tnp = &(__tntab[rhs_apti]);
     /* cannot assign accross idp value areas */
     if (tnp->comlab_typ == COMLAB_IDP) 
      {
       /* DBG remove --- */
       if (tnp->idp_typ != COMLAB_PD_RHSBP && tnp->idp_typ != COMLAB_NB_BP) 
        {
         __misc_terr(__FILE__, __LINE__);
        }
       /* ------ */
       rhs_apti = __gen_duplicate_tmp(rhs_apti);
      }
     /* AIV FIXME - believe all gref info is constant just push ref grp */
     /* AIV 05/15/06 - changed to pass gref */
     save_idp_ti = __gen_ld_xmr_idp(grp);

     /* AIV 01/09/06 - only need to push the instance module */
     targ_mdp = grp->targmdp; 
     __push_wrkitstk(targ_mdp, 0);

     /* AIV 02/20/07 - rare case it xmr assign to selft links out xmr pop */
     /* AIV LOOKATME - better method to catch */
     /* since change to targ (defined in) itree loc, do not load with grp */
     __gen_proc_id_assign(np, rhs_apti);

     __gen_restore_idp(save_idp_ti);
     __pop_wrkitstk();
    }
   else
    {
     /* simple store, can just get the xmr inum */
     addr_ti = __ldvar_addr(np, grp);
     __gen_st_val(np, addr_ti, rhs_apti);
    }
   break;
  case ID:
   np = lhsx->lu.sy->el.enp;
   __gen_proc_id_assign(np, rhs_apti);
   break;
  case LSB:
   np = lhsx->lu.x->lu.sy->el.enp;
   if (np->n_isarr)
    {
     /* arrays can't be forced/assigned */
     gen_assgn_to_arr(lhsx, rhs_apti);
    }
   else gen_assgn_to_regbit(lhsx, rhs_apti); 

   break; 
  case PARTSEL:
   gen_assgn_to_regpsel(lhsx, rhs_apti);
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   gen_assgn_to_index_width_psel(lhsx, rhs_apti, -1, -1);
   break;
  case LCB:
   lhsnels = __cnt_cat_size(lhsx);
   lhsxtab = (struct expr_t **)
    __my_malloc(lhsnels*sizeof(struct expr_t *));
   lxi = lhsnels - 1;
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x, lxi--)
    { lhsxtab[lxi] = catndp->lu.x; }
   gen_lhs_concat2(rhs_apti, lhsxtab, lhsnels, lhsx->szu.xclen);
   /* AIV 06/16/09 - memory leak here need to free */
   __my_free(lhsxtab, lhsnels*sizeof(struct expr_t *));
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * duplicate (copy) a tmp name
 * this is used to move from %esi (idp) prior to esi changing to compare.
 * Usually needed for xmr on one side and idp used on the other
 *    top.mod1_ins5.reg3  =  #23 reg22 ;
 *         lhs_idp1          (delay value stored in rhs_idp)
 */
extern int32 __gen_duplicate_tmp(int32 t_ti)
{
 int32 tnwid, srtyp, new_ti;

 tnwid = __get_tnwid(t_ti);
 srtyp = __tntab[t_ti].srtyp;
 new_ti = -1;
 switch (srtyp) {
  case SR_SCAL:
    new_ti = __gen_tn(SR_SCAL, 1);
    __emit_copy(WRDBYTES, t_ti, new_ti);
   break;
  case SR_SCAL2S:
    new_ti = __gen_tn(SR_SCAL2S, 1);
    __emit_copy(WRDBYTES, t_ti, new_ti);
   break;
  case SR_SSCAL:
    new_ti = __gen_tn(SR_SSCAL, 1);
    __emit_copy(1, t_ti, new_ti);
   break;
  case SR_VEC:
    new_ti = __gen_tn(SR_VEC, tnwid);
    __emit_copy(2*WRDBYTES*wlen_(tnwid), t_ti, new_ti);
   break;
  case SR_BIT2S:
    new_ti = __gen_tn(SR_BIT2S, tnwid);
    __emit_copy(WRDBYTES*wlen_(tnwid), t_ti, new_ti);
   break;
  case SR_SVEC:
    new_ti = __gen_tn(SR_SVEC, tnwid);
    __emit_copy(tnwid, t_ti, new_ti);
//AIV IDP FIXME CVC
//don't think this code should be needed here but removing this routine
//so marking bit for now 
    if (tnwid > WRDBYTES)
     {
      __tntab[new_ti].tn_used_wide = TRUE;
     }
   break;
  default: 
   __case_terr(__FILE__, __LINE__); 
   break;
  }
 return(new_ti);
}

/*
 * save the current idp to a local tmp (save_idp_ti) and
 */
static int32 gen_push_save_idp(int32 set_idp_ti)
{
 int32 save_idp_ti;

 save_idp_ti = __emit_save_cur_idp();
 __memloc_emit_set_idp(set_idp_ti);
 return(save_idp_ti);
}

/*
 * restore the current idp to the saved value
 */
extern void __gen_restore_idp(int32 save_idp_ti)
{
 /* if folding xmr for a constant case may not need the restore */
 if (save_idp_ti == -1)
  {
   return;
  }
 __memloc_emit_set_idp(save_idp_ti);
}

/*
 * gen assign to reg bit - wrapper with xmr/reg-qcaf processing 
 */
static void gen_assgn_to_regbit(struct expr_t *lhsx, int32 rhs_apti) 
{
 int32 bi_ti, bi, save_idp_ti;
 struct net_t *np;
 struct gref_t *grp;
 struct mod_t *targ_mdp;
 struct bblk_t *outofrng_bbp;

 outofrng_bbp = NULL;
 np = lhsx->lu.x->lu.sy->el.enp;
 if (np->frc_assgn_allocated)
  {
   gen_qcaf_assgn_to_regbit(lhsx, rhs_apti);
   return;
  }

 bi = bi_ti = -1;
 /* if constant get value otherwise load index */
 if (lhsx->ru.x->optyp == NUMBER)
  {
   bi = __get_comp_num_ndx(lhsx->ru.x);
  }
 else 
  {
   outofrng_bbp = __alloc_bblk(FALSE);
   bi_ti = __gen_comp_ndx(np, lhsx->ru.x, outofrng_bbp, FALSE);
  }

 if (lhsx->lu.x->optyp == GLBREF && __net_chg_nd_store(np, -1, -1))
  {
   /* AIV 04/11/12 - this is the same XMR idp copy restore problem */
   /* cannot use idp offset must actually copy the from idp into tmp */
   if (__tntab[rhs_apti].comlab_typ == COMLAB_IDP) 
    {
     rhs_apti = __gen_duplicate_tmp(rhs_apti);
    }
   grp = lhsx->lu.x->ru.grp;
   save_idp_ti = __gen_ld_xmr_idp(grp);
   /* AIV 01/09/06 - only need to push the instance module */
   targ_mdp = grp->targmdp; 
   __push_wrkitstk(targ_mdp, 0);

   /* assign bit sel as constant */
   if (bi != -1)
    {
     __gen_assgn_to_bit_const(lhsx, bi, rhs_apti, TRUE);
    }
   else 
    {
     gen_assgn_to_bit_var(lhsx, bi_ti, rhs_apti, TRUE);
    }

   __gen_restore_idp(save_idp_ti);
   if (bi == -1) __start_bblk(outofrng_bbp);
   __pop_wrkitstk();
   return;
  }
 if (bi != -1)
  {
   __gen_assgn_to_bit_const(lhsx, bi, rhs_apti, FALSE);
  }
 else 
  {
   gen_assgn_to_bit_var(lhsx, bi_ti, rhs_apti, FALSE);
   __start_bblk(outofrng_bbp);
  }
}

/*
 * gen qcaf tst/skip assign to bit
 *
 * wrapper when force/assign test and skip around needed
 */
static void gen_qcaf_assgn_to_regbit(struct expr_t *lhsx, int32 rhs_apti)
{
 int32 nd_itpop, biti_ti, bi, save_idp_ti;
 struct expr_t *idndp;
 struct net_t *np;
 struct bblk_t *after_bbp;
 struct mod_t *targ_mdp;
 struct bblk_t *outofrng_bbp;

 idndp = lhsx->lu.x;
 np = idndp->lu.sy->el.enp;
 nd_itpop = FALSE;
 bi = biti_ti = -1;

 outofrng_bbp = NULL;
 if (lhsx->ru.x->optyp == NUMBER)
  {
   bi = __get_comp_num_ndx(lhsx->ru.x);
  }
 else 
  {  
   outofrng_bbp = __alloc_bblk(FALSE);
   biti_ti = __gen_comp_ndx(np, lhsx->ru.x, outofrng_bbp, FALSE);
  }

 save_idp_ti = -1;
 if (idndp->optyp == GLBREF)
  { 
   save_idp_ti = __gen_ld_xmr_idp(idndp->ru.grp);
   /* AIV 01/09/06 - only need to push the instance module */
   targ_mdp = idndp->ru.grp->targmdp; 
   __push_wrkitstk(targ_mdp, 0);
   nd_itpop = TRUE;
  }

 after_bbp = __alloc_bblk(FALSE);
 gen_reg_qcaf_tstjmp(np, after_bbp, rhs_apti);

 if (bi != -1) __gen_assgn_to_bit_const(lhsx, bi, rhs_apti, TRUE);
 else
  {
   gen_assgn_to_bit_var(lhsx, biti_ti, rhs_apti, TRUE);
  }

 __start_bblk(after_bbp);
 if (nd_itpop)
  {
   __gen_restore_idp(save_idp_ti);
   __pop_wrkitstk();
  }
 if (bi == -1) __start_bblk(outofrng_bbp);
}

/*
 * gen assign to reg psel - wrapper with xmr/reg-qcaf processing 
 * qcaf for regs is entere reg only
 */
static void gen_assgn_to_regpsel(struct expr_t *lhsx, int32 rhs_apti)
{
 int32 nd_itpop, save_idp_ti;
 struct expr_t *idndp;
 struct net_t *np;
 struct bblk_t *after_bbp;
 struct mod_t *targ_mdp;

 idndp = lhsx->lu.x;
 np = idndp->lu.sy->el.enp;
 save_idp_ti = -1;
 if (lhsx->lu.x->optyp == GLBREF
  && (__net_chg_nd_store(np, -1, -1) || np->frc_assgn_allocated))
  {
   /* AIV 04/11/12 - this is the same XMR idp copy restore problem */
   /* cannot use idp offset must actually copy the from idp into tmp */
   if (__tntab[rhs_apti].comlab_typ == COMLAB_IDP) 
    {
     rhs_apti = __gen_duplicate_tmp(rhs_apti);
    }
   save_idp_ti = __gen_ld_xmr_idp(idndp->ru.grp);
   /* AIV 01/09/06 - only need to push the instance module */
   targ_mdp = idndp->ru.grp->targmdp; 
   __push_wrkitstk(targ_mdp, 0);
   nd_itpop = TRUE;
  }
 else nd_itpop = FALSE;

 after_bbp = NULL;
 if (np->frc_assgn_allocated) 
  {
   after_bbp = __alloc_bblk(FALSE);
   gen_reg_qcaf_tstjmp(np, after_bbp, rhs_apti);
  }

 /* AIV 01/31/06 - if nd_itpop no need to acess the grp again already pushed */
 __gen_assgn_to_psel(lhsx, rhs_apti, nd_itpop);

 if (np->frc_assgn_allocated) __start_bblk(after_bbp);
 if (nd_itpop)
  {
   __gen_restore_idp(save_idp_ti);
   __pop_wrkitstk();
  }
}

/*
 * routine to generate a procedural id assign
 *
 * only for cases where know current itree loc (maybe from gref push) correct
 */
extern void __gen_proc_id_assign(struct net_t *np, int32 rhs_apti)
{
 int32 addr_ti;
 struct bblk_t *after_bbp;

 after_bbp = NULL;
 addr_ti = __ldvar_addr(np, NULL);
 /* AIV 02/10/09 - no need to do anything if it is itself */
 /* was causing unused tmps def/use for the force case */
 if (addr_ti == rhs_apti) return;

 if (np->frc_assgn_allocated)
  {
   after_bbp = __alloc_bblk(FALSE);
   gen_reg_qcaf_tstjmp(np, after_bbp, rhs_apti);
  }

 /* this will usually fill low and high halves (high if there is b part) */
 if (__net_chg_nd_store(np, -1, -1)) __gen_chg_st_val(np, addr_ti, rhs_apti);
 else __gen_st_val(np, addr_ti, rhs_apti);

 if (np->frc_assgn_allocated) __start_bblk(after_bbp);
}

/*
 * generate the test and bblk start and jump after for procedural reg
 * force/assign test
 */
static void gen_reg_qcaf_tstjmp(struct net_t *np, struct bblk_t *after_bbp,
 int32 rhs_apti)
{
 int32 np_ti, qcaf_active_ti, is_wire;
 struct bblk_t *assgn_bbp;

 assgn_bbp = __alloc_bblk(FALSE);

 /* need to pass the net addr since formal tmp tab must be mod specific */
 /* and use of the net address does that - offset same for differ mods */
 np_ti = __ld_netadr_tn(np);
 /* AIV 02/03/12 - this is used in the tran channel code so must */ 
 /* also handle wires here */
 is_wire = (np->ntyp < NONWIRE_ST);
 if (is_wire)
  {
   if (np->n_isavec)
    {
     if (np->n_stren)
      {
       qcaf_active_ti = __emit_stren_correct_frc(np_ti, rhs_apti);
      }
     else qcaf_active_ti = __emit_correct_frc(np_ti, rhs_apti);
    }
   else qcaf_active_ti = __emit_scalar_wire_inhibit(np_ti);
  }
 else qcaf_active_ti = __emit_reg_qcaf_inhibit(np_ti);

 __emit_jmp_0(after_bbp, assgn_bbp, qcaf_active_ti);
 __start_bblk(assgn_bbp);
}

/*
 * gen insn to copy (store) into a net value (non chg form)
 * always passed a/b value
 *
 * for both non stren and stren
 */
extern void __gen_st_val(struct net_t *np, int32 lhs_apti, int32 apti)
{
 int32 t2_ti, bytwid, srtyp;

 switch ((byte) np->srep) {
  case SR_SCAL2S:
   /* SJM 04/28/05 - why is this never scalar in interpreter? */
   srtyp = __tntab[apti].srtyp;
   if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
    {
     __emit_copy(WRDBYTES, apti, lhs_apti);
    }
   else if (srtyp == SR_SSCAL)
    {
     __emit_copy(1, apti, lhs_apti);
    }
   else
    {
     t2_ti = __gen_cnvt_ab_vec_to_scalar_2state(apti);
     __emit_copy(WRDBYTES, t2_ti, lhs_apti);
    }
   break;
  case SR_SCAL:
   /* SJM 04/28/05 - why is this never scalar in interpreter? */
   srtyp = __tntab[apti].srtyp;
   if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
    {
     __emit_copy(WRDBYTES, apti, lhs_apti);
    }
   else if (srtyp == SR_SSCAL)
    {
     __emit_copy(1, apti, lhs_apti);
    }
   else
    {
     t2_ti = __gen_cnvt_ab_vec_to_scalar(apti);
     __emit_copy(WRDBYTES, t2_ti, lhs_apti);
    }
   break;
  case SR_VEC:
//AIV 2STATE
   /* DBG remove --- */
   if (__tntab[apti].srtyp != SR_VEC) __misc_terr(__FILE__, __LINE__);
   /* ----- */
#ifndef __CVC32__
   if (np->ntyp == N_REAL) bytwid = WRDBYTES*wlen_(np->nwid);
   else bytwid = 2*WRDBYTES*wlen_(np->nwid);
#else
   bytwid = 2*WRDBYTES*wlen_(np->nwid);
#endif
   /* AIV - not no need to size convert should be done by here */
   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(bytwid, apti, lhs_apti);
   break;
  case SR_BIT2S:
//AIV 2STATE
   /* DBG remove --- */
   if (__tntab[apti].srtyp != SR_BIT2S) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   bytwid = WRDBYTES*wlen_(np->nwid);
   __emit_copy(bytwid, apti, lhs_apti);
   break;
  case SR_SVEC:
   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(np->nwid, apti, lhs_apti);
   break;
  case SR_SSCAL:
   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(1, apti, lhs_apti);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * gen insns to convert known 1 bit sr vec a/b form to 3 value scalar
 * stored as word
 */
extern int32 __gen_cnvt_ab_vec_to_scalar(int32 apti)
{
 int32 res_ti, bpti, r1_apti, r1_bpti, r2_bpti, r3_ti, one_ti, ctab_ndx;
 int32 srtyp;
 word32 av, bv, sv;

 /* AIV 10/10/05 - if already scalar just return */
 /* LOOKATME - maybe should never be called if already scalar ???? */
 srtyp = __tntab[apti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S) return(apti);

 one_ti = __gen_cint_tn(1);
 /* if known two state just need to and with 1 */
 if (srtyp == SR_BIT2S) 
  {
   res_ti = __emit_srep_mask_and(SR_SCAL, 1, apti, one_ti);
   return(res_ti);
  }

 bpti = __get_bpti(apti);
 /* AIV 09/09/08 - if constant fold at compile time */
 if (__is_constant(apti))
  {
   av = __get_wrd_con_val(apti);
   bv = __get_wrd_con_val(bpti);
   sv = ((bv & 1) << 1) | (av & 1);
   bv = 0;
   /* AIV 10/16/08 - this should be passed wlen not byte length */
   ctab_ndx = __allocfill_cval_new(&sv, &bv, 1);
   res_ti = __gen_contab_tn(ctab_ndx, 1, FALSE, FALSE, FALSE, SR_SCAL);
   return(res_ti);
  }

 res_ti = __gen_tn(SR_SCAL, 1);

 if (__get_tnwid(apti) != 1)
  {
   r1_apti = __emit_mask_and(apti, one_ti);
   r1_bpti = __emit_mask_and(bpti, one_ti);
  }
 else
  {
   r1_apti = apti;
   r1_bpti = bpti;
  }

 /* AIV 02/03/09 - this orl can just be an addl and then would only be one */
 /* leal insn - don't have mechanism in reg assign opt to currently */
 /* handle leal double index insns - later fixing up */
 /* since this conversion is common */
 /* 
   andl	$1, %eax
   andl	$1, %edx
   leal	(%edx,%eax,2), %eax
 */
 r2_bpti = __emit_shiftl(1, one_ti, r1_bpti);
 /* AIV 03/04/09 - better code produced with an add here than or */
 /* notice this is the same for all 4 scalar states */
 r3_ti = __emit_add(1, r1_apti, r2_bpti); 
 /* AIV 10/13/06 - since res is a tmp scalar can just copy 4 bytes */
 /* this is true because tmp scalars are stored as a word */
 /* BEWARE - if changing from tmp word storage to byte this is incorrect */
 __emit_copy(WRDBYTES, r3_ti, res_ti);
 return(res_ti);
}

/*
 * convert to a 2-state scalar
 */
//AIV 2STATE - rename these routines
extern int32 __gen_cnvt_ab_vec_to_scalar_2state(int32 apti)
{
 int32 res_ti, bpti, r1_apti, r1_bpti, r2_bpti, r3_ti, one_ti, ctab_ndx;
 int32 srtyp;
 word32 av, bv, sv;

 /* AIV 10/10/05 - if already scalar just return */
 /* LOOKATME - maybe should never be called if already scalar ???? */
 srtyp = __tntab[apti].srtyp;
 if (srtyp == SR_SCAL2S) return(apti);

 /* if constant fold at compile time */
 /* AIV 09/01/10 - first try to fold constant values */
 if (__is_constant(apti))
  {
   av = __get_wrd_con_val(apti);
   if (srtyp == SR_SCAL || srtyp == SR_SSCAL)
    {
     av &= 3;
     bv = (av >> 1) & 1;
     av &= 1;
    }
   else
    {
     bpti = __get_bpti(apti);
     bv = __get_wrd_con_val(bpti);
    }
   if (bv != 0) sv = 0;
   else sv = av & 1;
   bv = 0;
   /* AIV 10/16/08 - this should be passed wlen not byte length */
   ctab_ndx = __allocfill_cval_new(&sv, &bv, 1);
   res_ti = __gen_contab_tn(ctab_ndx, 1, FALSE, FALSE, FALSE, SR_SCAL);
   return(res_ti);
  }

 /* if scalar may have to convert x/z to 0 */
 if (srtyp == SR_SCAL)
  {
   res_ti = __emit_toscal_2s_fr_scal_4s(apti, FALSE);
   return(res_ti);
  }

 if (srtyp == SR_SSCAL)
  {
   res_ti = __emit_toscal_2s_fr_scal_4s(apti, TRUE);
   return(res_ti);
  }

 one_ti = __gen_cint_tn(1);
 /* if known two state just need to and with 1 */
 if (srtyp == SR_BIT2S) 
  {
   res_ti = __emit_srep_mask_and(SR_SCAL2S, 1, apti, one_ti);
   return(res_ti);
  }


 /* DBG remove --- */
 if (srtyp != SR_VEC) __misc_terr(__FILE__, __LINE__); 
 /* ----- */

 bpti = __get_bpti(apti);
 if (__get_tnwid(apti) != 1)
  {
   r1_apti = __emit_mask_and(apti, one_ti);
   r1_bpti = __emit_mask_and(bpti, one_ti);
  }
 else
  {
   r1_apti = apti;
   r1_bpti = bpti;
  }

 r2_bpti = __emit_shiftl(1, one_ti, r1_bpti);
 r3_ti = __emit_add(1, r1_apti, r2_bpti); 
 res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL2S, 1, 
    AM_NLO_ARRNDX, r3_ti, NLO_4STATE_TO2);
 return(res_ti);
}

/*
 * store if changed (and set flag) know rgap and rgbp are adjusted and
 * z extended (if needed) to exact wire width
 * also any 1 bit cases must already be adjusted to a part only form  
 *
 * notice for XMR chg store must be run in XMR defined in inst
 */
extern void __gen_chg_st_val(struct net_t *np, int32 lhs_apti, int32 apti)
{
 switch ((byte) np->srep) {
  case SR_SCAL:
  case SR_SCAL2S:
   gen_chg_st_scalval(np, lhs_apti, apti);
   break;
  case SR_VEC:
#ifndef __CVC32__
   /* AIV 01/25/11 - this was wrong should just produce 2-state code for */
   /* 64-bit will just handle as a-part 2-state */
   if (np->ntyp == N_REAL)
    {
     gen_chg_st_vecval_2state(np, lhs_apti, apti);
     return;
    }
#endif
   gen_chg_st_vecval(np, lhs_apti, apti);
   break;
  case SR_BIT2S:
   gen_chg_st_vecval_2state(np, lhs_apti, apti);
   break;
  case SR_SVEC:
   __gen_chg_st_svecval(np, lhs_apti, apti, -1, np->nwid);
   break;
  case SR_SSCAL:
   __gen_chg_st_svecval(np, lhs_apti, apti, -1, 1);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * gen chg store vec srep value insns
 */
static void gen_chg_st_vecval(struct net_t *np, int32 lhs_apti,
 int32 rhs_apti)
{
 int32 bytwid, lhs_bpti, rhs_bpti, t1_ti, t2_ti, t3_ti, blen;
 struct bblk_t *skip_bbp, *chgstore_bbp;


 blen = np->nwid;
 bytwid = wlen_(blen)*WRDBYTES;
 /* AIV 02/21/07 - this xor method only makes sense for narrow case */
 /* if wide was producing 3 wrapper calls just do the wide compare */
 /* so the wide only does one compare */
 /* AIV 12/17/09 - have a new routine to handle 1 word case */
 if (blen <= WBITS)
  {
   /* if constant do normal code - may fold etc if possible */
   if (__is_constant(rhs_apti))
    {
     skip_bbp = __alloc_bblk(FALSE);
     chgstore_bbp = __alloc_bblk(FALSE);
     lhs_bpti = __get_bpti(lhs_apti);
     rhs_bpti = __get_bpti(rhs_apti);

     t1_ti = __emit_bin_bitxor(blen, lhs_apti, rhs_apti);
     t2_ti = __emit_bin_bitxor(blen, lhs_bpti, rhs_bpti);
     t3_ti = __emit_bin_bitor(blen, t1_ti, t2_ti);
     __emit_jmp_0(skip_bbp, chgstore_bbp, t3_ti);
    __start_bblk(chgstore_bbp);

    /* notice copies follow gas movl [from],[to] format */
    __emit_copy(2*bytwid, rhs_apti, lhs_apti);
    __gen_record_const_nchg(np, -1, -1, skip_bbp);
   
     __start_bblk(skip_bbp);
     return;
    }
   gen_chg_st_vecval_1w(np, lhs_apti, rhs_apti);
   return;
  }

 skip_bbp = __alloc_bblk(FALSE);
 chgstore_bbp = __alloc_bblk(FALSE);

 /* this compare checks the a and b parts for first diff */
 __emit_jmp_eq_abpart(skip_bbp, chgstore_bbp, lhs_apti, rhs_apti);

 __start_bblk(chgstore_bbp);

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*bytwid, rhs_apti, lhs_apti);
 __gen_record_const_nchg(np, -1, -1, skip_bbp);

 __start_bblk(skip_bbp);
}

/*
 * gen chg store vec srep value insns for <= WBITS
 */
static void gen_chg_st_vecval_1w(struct net_t *np, int32 lhs_apti,
 int32 rhs_apti)
{
 int32 lhs_bpti, rhs_bpti, t1_ti, t2_ti, t3_ti, blen;
 int32 rhs_reg_apti, rhs_reg_bpti;
 struct bblk_t *skip_bbp, *chgstore_bbp;

 skip_bbp = __alloc_bblk(FALSE);
 chgstore_bbp = __alloc_bblk(FALSE);

 blen = np->nwid;
     
 /* better to store values regardless if they change or not */
 if (__tntab[rhs_apti].tn_typ == TN_ADR) 
  {
   rhs_reg_apti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, rhs_apti); 
   t1_ti = __emit_bin_bitxor(blen, lhs_apti, rhs_reg_apti);
    __st_insn(I_STOREL, AM_REG, rhs_reg_apti, AM_NDXREG, lhs_apti);

   rhs_bpti = __get_bpti(rhs_apti);
   rhs_reg_bpti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, rhs_bpti); 

   lhs_bpti = __get_bpti(lhs_apti);
   t2_ti = __emit_bin_bitxor(blen, lhs_bpti, rhs_reg_bpti);
   __st_insn(I_STOREL, AM_REG, rhs_reg_bpti, AM_NDXREG, lhs_bpti);
   t3_ti = __emit_bin_bitor(blen, t1_ti, t2_ti);
   __emit_jmp_0(skip_bbp, chgstore_bbp, t3_ti);

   __start_bblk(chgstore_bbp);

   /* notice copies follow gas movl [from],[to] format */
    __gen_record_const_nchg(np, -1, -1, skip_bbp);

   __start_bblk(skip_bbp);
   return;
 } 
 
 rhs_bpti = __get_bpti(rhs_apti);
 lhs_bpti = __get_bpti(lhs_apti);
 t2_ti = __emit_bin_bitxor(blen, lhs_bpti, rhs_bpti);
 __st_insn(I_STOREL, AM_REG, rhs_bpti, AM_NDXREG, lhs_bpti);

 t1_ti = __emit_bin_bitxor(blen, lhs_apti, rhs_apti);
 __st_insn(I_STOREL, AM_REG, rhs_apti, AM_NDXREG, lhs_apti);

 t3_ti = __emit_bin_bitor(blen, t1_ti, t2_ti);
 __emit_jmp_0(skip_bbp, chgstore_bbp, t3_ti);

 __start_bblk(chgstore_bbp);

 /* notice copies follow gas movl [from],[to] format */
 __gen_record_const_nchg(np, -1, -1, skip_bbp);

 __start_bblk(skip_bbp);
}

//AIV LOOKATME - results in less code but think is slower
static void gen_chg_st_vecval_1w_try(struct net_t *np, int32 lhs_apti,
 int32 rhs_apti)
{
 int32 lhs_bpti, rhs_bpti, t1_ti, t2_ti, t3_ti, blen, amtyp;
 struct bblk_t *skip_bbp, *chgstore_bbp;

 skip_bbp = __alloc_bblk(FALSE);
 chgstore_bbp = __alloc_bblk(FALSE);

 blen = np->nwid;
     
 if (__tntab[rhs_apti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
 else amtyp = AM_REG;

 t2_ti = __move_insn(TN_VAL, I_MOVL, amtyp, rhs_apti);
 __st_insn(I_XORL, AM_NDXREG, lhs_apti, AM_REG, t2_ti);
 __st_insn(I_XORL, AM_REG, t2_ti, AM_NDXREG, lhs_apti);
 
 rhs_bpti = __get_bpti(rhs_apti);
 lhs_bpti = __get_bpti(lhs_apti);
 t1_ti = __move_insn(TN_VAL, I_MOVL, amtyp, rhs_bpti);
 __st_insn(I_XORL, AM_NDXREG, lhs_bpti, AM_REG, t1_ti);
 __st_insn(I_XORL, AM_REG, t1_ti, AM_NDXREG, lhs_bpti);

 t3_ti = __emit_bin_bitor(blen, t1_ti, t2_ti);
 __emit_jmp_0(skip_bbp, chgstore_bbp, t3_ti);

 __start_bblk(chgstore_bbp);

 /* notice copies follow gas movl [from],[to] format */
 __gen_record_const_nchg(np, -1, -1, skip_bbp);

 __start_bblk(skip_bbp);
}

/*
 * gen chg store 2-state vec 
 */
static void gen_chg_st_vecval_2state(struct net_t *np, int32 lhs_apti,
 int32 rhs_apti)
{
 int32 bytwid, blen;
 struct bblk_t *skip_bbp, *chgstore_bbp;

 blen = np->nwid;
 bytwid = wlen_(blen)*WRDBYTES;
 skip_bbp = __alloc_bblk(FALSE);
 chgstore_bbp = __alloc_bblk(FALSE);

 /* just do one compare of a part */
 __emit_jmp_eq(skip_bbp, chgstore_bbp, lhs_apti, rhs_apti);

 __start_bblk(chgstore_bbp);

 __emit_copy(bytwid, rhs_apti, lhs_apti);
 __gen_record_const_nchg(np, -1, -1, skip_bbp);

 __start_bblk(skip_bbp);
}

/*
 * gen chg store scalar srep insns
 *
 * SJM 07/12/05 - what is this? - for scalars with a/b rhs?
 */
static void gen_chg_st_scalval(struct net_t *np, int32 lhs_apti,
 int32 rhs_apti)
{
 int32 t1_ti, srtyp;
 struct bblk_t *skip_bbp, *chgstore_bbp;
 
 skip_bbp = __alloc_bblk(FALSE);
 chgstore_bbp = __alloc_bblk(FALSE);

 /* SJM 04/28/05 - why is this never scalar in interpreter? */
 srtyp = __tntab[rhs_apti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S) 
  {
   t1_ti = rhs_apti;
  }
 else if (np->srep == SR_SCAL2S) 
  {
   t1_ti = __gen_cnvt_ab_vec_to_scalar_2state(rhs_apti);
  }
 else t1_ti = __gen_cnvt_ab_vec_to_scalar(rhs_apti);

 /* AIV 10/24/05 - added new insn which only compare one byte */
 __emit_jmp_eq(skip_bbp, chgstore_bbp, lhs_apti, t1_ti);
 __start_bblk(chgstore_bbp);

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, t1_ti, lhs_apti);
 __gen_record_const_nchg(np, -1, -1, skip_bbp);

 __start_bblk(skip_bbp);
}

/*
 * gen vm insns for assign to memory (array)
 */
static void gen_assgn_to_arr(struct expr_t *lhsx, int32 rhs_ti)
{
 int32 biti_ti, bi;
 struct expr_t *idndp, *sel_ndp, *ndx1;
 struct net_t *np;
 struct bblk_t *inrng_bbp, *outofrng_bbp;
 struct mda_t *mdap;

 
 idndp = lhsx->lu.x;
 np = idndp->lu.sy->el.enp;
 ndx1 = lhsx->ru.x;
 sel_ndp = NULL;
 /* if multi-dim array compute the index */
 if ((mdap = np->mda) != NULL)
  {
   /* array index is folded - handle as regular array assign */
   if (ndx1->folded_ndx)
    {
     bi = __get_comp_num_ndx(ndx1);
     if (bi != -1) gen_lhs_arrsel(lhsx, bi, -1, rhs_ti, TRUE, NULL, -1);
     return;
    }
   /* compute the index - has at least one dim with variable index */
   inrng_bbp = __alloc_bblk(FALSE);
   outofrng_bbp = __alloc_bblk(FALSE);
   biti_ti = gen_comp_mda_ndx(np, mdap, ndx1, outofrng_bbp, &sel_ndp);
   __start_bblk(inrng_bbp);
   gen_lhs_arrsel(lhsx, -1, biti_ti, rhs_ti, FALSE, sel_ndp, -1);
   __start_bblk(outofrng_bbp);
  }
 else if (ndx1->optyp == NUMBER)
  {
   /* notice bi ti is an int value */
   /* if array select constant handle as constant case */
   bi = __get_comp_num_ndx(ndx1);
   if (bi != -1) gen_lhs_arrsel(lhsx, bi, -1, rhs_ti, TRUE, NULL, -1);
  }
 else
  {
   outofrng_bbp = __alloc_bblk(FALSE);
   inrng_bbp = __alloc_bblk(FALSE);
   biti_ti = __gen_comp_ndx(np, ndx1, outofrng_bbp, FALSE);
   __start_bblk(inrng_bbp);
   gen_lhs_arrsel(lhsx, -1, biti_ti, rhs_ti, FALSE, NULL, -1);
   __start_bblk(outofrng_bbp);
  }
}

/*
 * gen insns to assign to select array - non chg form
 *
 * notice: new scheme requires separate cases for packed/unpacked arrays,
 * XMR/IS and decompostion of a/b parts if needed
 * can't gen insn and then lower because missing information and can't
 * optimize more - optimization such as elimination of b parts must be
 * done on flow graph following Morgan algorithms
 *
 * also notice: because of packing, can't store using inverted indices
 * where all instances of a given index stored together - if stored
 * that way could use normal per inst vector store mechanism
 *
 */
static void gen_lhs_arrsel(struct expr_t *lhsx, int32 bi, int32 bi_ti, 
 int32 rhs_apti, int32 is_const, struct expr_t *sel_ndp, int32 sel_ti)
{
 int32 blen, wlen, nd_itpop, nuwrd_ti, nbytes, new_rhs_ti;
 int32 eladdr_ti, elofs, elofs_ti, pckel_ti, rhs_scalpti, srtyp;
 int32 save_idp_ti, addr_ti, nd_chg, is_wire, is_2state;
 struct expr_t *idndp, *ndx, *ndx1;
 struct net_t *np;
 struct mod_t *targ_mdp;
 
 idndp = lhsx->lu.x;
 np = idndp->lu.sy->el.enp;
 blen = np->nwid;
 nd_itpop = FALSE;
 save_idp_ti = -1;
 elofs = elofs_ti = -1;
 if (idndp->optyp == GLBREF)
  {
   /* SJM 01/25/06 - always use but mod inst only wrong for declarative */
   save_idp_ti = __gen_ld_xmr_idp(idndp->ru.grp);
   /* also push compile time itree context */
   /* AIV 01/09/06 - only need to push the instance module */
   targ_mdp = idndp->ru.grp->targmdp; 
   addr_ti = __gen_ld_netbp(np);
   __push_wrkitstk(targ_mdp, 0);
   nd_itpop = TRUE;
  }
 else addr_ti = __gen_ld_netbp(np);

 srtyp = __get_array_srep_type(np);
 if (blen == 1)
  {
   rhs_scalpti = __gen_cnvt_srep_ifneeded(rhs_apti, srtyp, 1, FALSE, FALSE,
    FALSE); 
   /* AIV 03/05/07 - scalar arrays with multiple instances were never */
   /* being tested, there is a problem using the rhs address from __inum */
   /* add in the lowered masking if the of rhs value */
   /* this copy will mask the high part of the word */
   if (rhs_apti == rhs_scalpti && __inst_mod->flatinum != 1)
    {
     rhs_scalpti = __gen_tn(srtyp, 1);
     __emit_copy(1, rhs_apti, rhs_scalpti);
    }
   if (is_const) 
    {
     gen_st_scalar_lhs_arrsel_const(np, addr_ti, bi, rhs_scalpti);
    }
   else gen_st_scalar_lhs_arrsel_var(lhsx, addr_ti, bi_ti, rhs_scalpti);
   goto pop_if_need;
  } 
 /* if lhs is real must convert to real if needed */
 if (lhsx->is_real)
  {
   rhs_apti = __gen_cnvt_srep_ifneeded(rhs_apti, SR_VEC, lhsx->szu.xclen,
    FALSE, TRUE, TRUE); 
  }
 else
  {
   rhs_apti = __gen_cnvt_srep_ifneeded(rhs_apti, srtyp, lhsx->szu.xclen,
    FALSE, FALSE, FALSE); 
  }
 ndx1 = lhsx->ru.x;
 /* if last index is a select get the value */
 if (ndx1->arr_select)
  {
   if (sel_ndp == NULL)
    {
     ndx = ndx1;
     while (ndx != NULL)
      {
       sel_ndp = ndx;
       ndx = ndx->next_ndx;
      }
    }
  }
 /* AIV 02/24/09 - can have arrays of wire now - handle as seperate case */
 /* since there is no packing */
 is_wire = (np->ntyp < NONWIRE_ST);
 /* if 2-state no 2*index */
 if (srtyp == SR_BIT2S) is_2state = TRUE;
 else is_2state = FALSE;

 /* 2-state are never packed */
 /* AIV 09/01/10 - 2-state array are no longer packed */
 if (is_wire || blen > WBITS/2 || is_2state)
  {
   /* case 1: unpacked - each vector element takes more than one word  */
   /* bi is a known constant */
   if (is_const)
    {
     eladdr_ti = gen_ndxarr_ptr_const(np, addr_ti, bi);
    }
   else
    {
     /* case 1: unpacked - each vector element takes more than one word  */
     eladdr_ti = gen_ndxarr_ptr_var(np, addr_ti, bi_ti);
    }

  /* if array as select of last element must store into select range */
  new_rhs_ti = rhs_apti;
  if (sel_ndp != NULL)
   {
    /* AIV 09/11/08 - select was wrong for net changes */
    /* it needs to record the change for the entire element when process */
    /* as a regular nchg on the element - if there is no change will be -1 */
    nd_chg = FALSE;
    if (is_const) 
     {
      if (__net_chg_nd_store(np, bi, bi)) nd_chg = TRUE;
     }
    else if (__net_chg_nd_store(np, -1, -1)) nd_chg = TRUE;
    new_rhs_ti = gen_st_array_element_select(np, sel_ndp, eladdr_ti, rhs_apti, 
     nd_chg, srtyp, sel_ti);
    if (new_rhs_ti >= 0) rhs_apti = new_rhs_ti;
   }

  if (new_rhs_ti >= 0)
   {
    if (is_const) 
     {
      if (__net_chg_nd_store(np, bi, bi))
       {
        gen_chg_st_unpck_arr_val(np, eladdr_ti, rhs_apti, bi, bi_ti, is_const);
       }
      else
       {
        /* AIV 08/03/10 - real copies are always 8 bytes - this avoids */
        /* checking for empty bpart for 64-bit since REALBITS is 64 */
        if (np->ntyp == N_REAL) nbytes = 8;
        else 
         {
          wlen = wlen_(blen);
          nbytes = wlen*WRDBYTES;
          if (srtyp != SR_BIT2S) nbytes *= 2;
         }
        /* notice copies follow gas movl [from],[to] format */
        __emit_copy(nbytes, rhs_apti, eladdr_ti);
       }
     }
    else if (__net_chg_nd_store(np, -1, -1))
     {
      gen_chg_st_unpck_arr_val(np, eladdr_ti, rhs_apti, bi, bi_ti, is_const);
     }
    else
     {
      /* AIV 08/03/10 - real copies are always 8 bytes - this avoids */
      /* checking for empty bpart for 64-bit since REALBITS is 64 */
      if (np->ntyp == N_REAL) nbytes = 8;
      else 
       {
        wlen = wlen_(blen);
        nbytes = wlen*WRDBYTES;
        if (srtyp != SR_BIT2S) nbytes *= 2;
       }
      /* notice copies follow gas movl [from],[to] format */
      __emit_copy(nbytes, rhs_apti, eladdr_ti);
     }
   }
  }
 else 
  {
   /* packed into byte, hword or word */ 
   /* get the elements start byte */
   if (is_const)
    {
     elofs = gen_pck_ofset_const(np, bi);
    }
   else
    {
     elofs_ti = gen_pck_ofset_var(np, bi_ti);
    }

   nbytes = -1;
   /* detremine number of bytes of copy */
   if (np->nwid <= 4) nbytes = 1;
   else if (np->nwid <= 8) nbytes = 2;
   else if (np->nwid <= WBITS/2) nbytes = WRDBYTES;
   else __case_terr(__FILE__, __LINE__);

 
   if (is_const)
    { 
     pckel_ti = __con_adradd_insn(srtyp, np->nwid, addr_ti, elofs);
    } 
   else pckel_ti = __var_adradd_insn(srtyp, np->nwid, addr_ti, elofs_ti);

   if (sel_ndp != NULL)
    {
     nuwrd_ti = gen_array_pck_element_select(np, sel_ndp, pckel_ti, rhs_apti, 
      srtyp, sel_ti);
    }
   else
    {
     nuwrd_ti = bld_pck_nwval(np, rhs_apti, blen);  
    }
   if (is_const)
    {
     if (__net_chg_nd_store(np, bi, bi))
       gen_chg_st_pck_arr_val(np, pckel_ti, nuwrd_ti, bi, bi_ti, is_const);
     else __emit_copy(nbytes, nuwrd_ti, pckel_ti);
    }
   else if (__net_chg_nd_store(np, -1, -1))
    {
     gen_chg_st_pck_arr_val(np, pckel_ti, nuwrd_ti, bi, bi_ti, is_const);
    }
   /* notice copies follow gas movl [from],[to] format */
   else 
    {
     __emit_copy(nbytes, nuwrd_ti, pckel_ti);
    }
  }

pop_if_need:
 if (nd_itpop)
  {
   __gen_restore_idp(save_idp_ti);
   __pop_wrkitstk();
  }
}

/*
 * if array last element is select (bsel/psel/index psel) do the store of 
 * rhs into the array element
 *
 * elements are not packed in this version
 * handle the net change ranges here as well
 */
static int32 gen_st_array_element_select(struct net_t *np, 
 struct expr_t *sel_ndp, int32 eladdr_ti, int32 rhs_apti, int32 nd_chg, 
 int32 srtyp, int32 sel_ti)
{
 int32 ri1, ri2, numbits, bi, biti_ti, new_el_ti;
 struct expr_t *ndx1, *ndx2;
 struct bblk_t *inrng_bbp, *outofrng_bbp;

 /* regular fixed range psel */
 if (sel_ndp->optyp == PARTSEL)
  {
   ndx1 = sel_ndp->ru.x->lu.x;
   ri1 = __contab[ndx1->ru.xvi];
   ndx2 = sel_ndp->ru.x->ru.x;
   ri2 = __contab[ndx2->ru.xvi];
   numbits = ri1 - ri2 + 1;
   if (nd_chg)
    {
     new_el_ti = __gen_duplicate_tmp(eladdr_ti);
     __gen_st_psel(srtyp, new_el_ti, rhs_apti, ri2, numbits);
     return(new_el_ti);
    }
   else
    {
     __gen_st_psel(srtyp, eladdr_ti, rhs_apti, ri2, numbits);
     return(-1);
    }
  }
 /* variable indexed psel */
 else if (sel_ndp->optyp == PARTSEL_NDX_PLUS || 
          sel_ndp->optyp == PARTSEL_NDX_MINUS)
  {
   gen_assgn_to_index_width_psel(sel_ndp, rhs_apti, -1, eladdr_ti);
   return(-1);
  }
 else
  {
   /* if not psel or indexed psel must be bsel */

   /* handle fixed constant case */
   if (sel_ndp->optyp == NUMBER)
    {
     bi = __contab[sel_ndp->ru.xvi]; 
     if (nd_chg) 
      {
       new_el_ti = __gen_duplicate_tmp(eladdr_ti);
       gen_lhsbsel_const_norecord(np, new_el_ti, bi, rhs_apti);
       return(new_el_ti);
      }
     else
      {
       __gen_lhsbsel_const(np, eladdr_ti, bi, rhs_apti);
       return(-1);
      }
    }
   else
    {
     /* check if variable in range */
     outofrng_bbp = NULL;
     /* AIV 09/02/11 - now pass down the save select for non-blocking with */
     /* a select on the end */
     if (sel_ti == -1)
      {
       outofrng_bbp = __alloc_bblk(FALSE);
       inrng_bbp = __alloc_bblk(FALSE);
       /* AIV 02/02/11 - this needs to pass TRUE was getting array range not */
       /* that of the actual element range */
       biti_ti = __gen_comp_ndx(np, sel_ndp, outofrng_bbp, TRUE);
       __start_bblk(inrng_bbp);
      }
     else biti_ti = sel_ti;

     if (nd_chg) 
      {
       gen_chg_lhsbsel_var(np, eladdr_ti, biti_ti, rhs_apti);
      }
     else
      {
       __gen_lhsbsel_var(np, eladdr_ti, biti_ti, rhs_apti);
      }
     if (outofrng_bbp != NULL) __start_bblk(outofrng_bbp);
     return(-1);
    }
  }
 return(-1);
}
     
/*
 * do the select of an array rhs store where the elements are packed
 * unpack the element, do the select, pack new value and check against
 * previous value
 */
static int32 gen_array_pck_element_select(struct net_t *np, 
 struct expr_t *sel_ndp, int32 val_ti, int32 rhs_ti, int32 srtyp, int32 sel_ti)
{
 int32 pack_ti, cint_ti, t1_ti, t2_ti, t3_ti, t1_bpti;
 int32 blen, ri1, ri2, numbits, bi, biti_ti;
 struct expr_t *ndx1, *ndx2;
 struct bblk_t *inrng_bbp, *outofrng_bbp;

 blen = np->nwid;
 /* unpack the element */
 /* tmpa = tmpw & __masktab[blen]; */
 t1_ti = __gen_tn(srtyp, blen);
 cint_ti = __gen_cint_tn(__masktab[blen]);
 t2_ti = __emit_bin_bitand(WBITS, cint_ti, val_ti);
 __emit_copy(WRDBYTES, t2_ti, t1_ti);
 /* tmpb = (tmpw >> blen); */
 if (srtyp == SR_VEC)
  {
   cint_ti = __gen_cint_tn(blen);
   t3_ti = __emit_shiftr(WBITS, cint_ti, val_ti);
   t1_bpti = __get_bpti(t1_ti);
   __emit_copy(WRDBYTES, t3_ti, t1_bpti);
  }

 /* regular fixed psel */
 if (sel_ndp->optyp == PARTSEL)
  {
   ndx1 = sel_ndp->ru.x->lu.x;
   ri1 = __contab[ndx1->ru.xvi];
   ndx2 = sel_ndp->ru.x->ru.x;
   ri2 = __contab[ndx2->ru.xvi];
   numbits = ri1 - ri2 + 1;
   __gen_st_psel(srtyp, t1_ti, rhs_ti, ri2, numbits);
  }
 /* variable indexed psel */
 else if (sel_ndp->optyp == PARTSEL_NDX_PLUS || 
          sel_ndp->optyp == PARTSEL_NDX_MINUS)
  {
   /* AIV 02/09/11 - need to pass in the select from the non-blocking saving */
   gen_assgn_to_index_width_psel(sel_ndp, rhs_ti, sel_ti, t1_ti);
  }
 else
  {
   /* bit select */
   if (sel_ndp->optyp == NUMBER)
    {
     bi = __contab[sel_ndp->ru.xvi]; 
     gen_lhsbsel_const_norecord(np, t1_ti, bi, rhs_ti);
    }
   else
    {
     /* AIV 09/02/11 - now pass down the save select for non-blocking with */
     /* a select on the end */
     if (sel_ti == -1)
      {
       outofrng_bbp = __alloc_bblk(FALSE);
       inrng_bbp = __alloc_bblk(FALSE);
       /* AIV 02/02/11 - this needs to pass TRUE was getting array range not */
       /* that of the actual element range */
       biti_ti = __gen_comp_ndx(np, sel_ndp, outofrng_bbp, TRUE);
       __start_bblk(inrng_bbp);
       __gen_lhsbsel_var(np, t1_ti, biti_ti, rhs_ti);
       __start_bblk(outofrng_bbp);
      }
     else __gen_lhsbsel_var(np, t1_ti, sel_ti, rhs_ti);
    }
  }

 /* pack the element pack for the compare */
 pack_ti = bld_pck_nwval(np, t1_ti, blen);  
 return(pack_ti);
}

/*
 * gen indexed base address into ptr to tmp name (non IS non packed case) 
 * returns addr 
 *
 * since __inum always 0 here computes:
 * rap = &(vap[arri*2*wlen]);
 */
static int32 gen_ndxarr_ptr_var(struct net_t *np, int32 addr_ti,
 int32 bi_ti)
{
 int32 wlen, elofs_ti, arrelptr_ti, cint_ti, srtyp; 
 
 wlen = wlen_(np->nwid);
 /* arri*2*wlen */
 srtyp = __get_array_srep_type(np);
 if (srtyp == SR_BIT2S) cint_ti = __gen_cint_tn(wlen*WRDBYTES);
 else cint_ti = __gen_cint_tn(2*wlen*WRDBYTES);
 elofs_ti = __emit_mult(WBITS, bi_ti, cint_ti);
 arrelptr_ti = __var_adradd_insn(srtyp, np->nwid, addr_ti, elofs_ti);
 return(arrelptr_ti);
}

/*
 * constant version
 */
static int32 gen_ndxarr_ptr_const(struct net_t *np, int32 addr_ti, int32 bi)
{
 int32 wlen, elofs, arrelptr_ti, srtyp; 
 
 /* AIV 12/08/06 - if constant add amount is zero just change arr */
 /* to a vec since it is the low element and return */
 srtyp = __get_array_srep_type(np);
 if (bi == 0)
  {
   __tntab[addr_ti].srtyp = srtyp;
   return(addr_ti);
  }
 wlen = wlen_(np->nwid);
 if (srtyp == SR_BIT2S) elofs = bi*wlen*WRDBYTES;
 else elofs = 2*bi*wlen*WRDBYTES;
 arrelptr_ti = __con_adradd_insn(srtyp, np->nwid, addr_ti, elofs);
 return(arrelptr_ti);
}

/*
 * gen packed ndx offset for packed memory - this is value not addr
 *
 * computes: nbytes*(mlen*<inum> + ndx)
 * nbytes can be 1, 2, or 4
 */
static int32 gen_pck_ofset_var(struct net_t *np, int32 bi_ti)
{
 int32 blen, nbytes, elofs_ti, cint_ti;
 
 /* 2-state arrays are no longer packed */
 /* DBG remove --- */
 if (np->n_2state) __misc_terr(__FILE__, __LINE__); 
 /* ----- */
 blen = np->nwid;
 if (blen <= 4) nbytes = 1;
 else if (blen <= 8) nbytes = 2;
 else if (blen <= WBITS/2) nbytes = WRDBYTES;
 else { nbytes = SR_UNKN; __case_terr(__FILE__, __LINE__); }

 cint_ti = __gen_cint_tn(nbytes);
 elofs_ti = __emit_mult(WBITS, cint_ti, bi_ti); 
 return(elofs_ti);
}

/*
 * generate a packed array offset - offset tn will be number of bytes
 * for IS case, need to generate variable expression using glb inum
 */
static int32 gen_pck_ofset_const(struct net_t *np, int32 bi)
{
 int32 blen, nbytes, elofs;
 
 blen = np->nwid;
 if (blen <= 4) nbytes = 1;
 else if (blen <= 8) nbytes = 2;
 else if (blen <= WBITS/2) nbytes = WRDBYTES;
 else { nbytes = SR_UNKN; __case_terr(__FILE__, __LINE__); }

 elofs = bi*nbytes;
 return(elofs);
}

/*
 * change store unpacked (at least 2 words) into lhs array select
 *
 * eladdr_ti is ptr to right inst and right index array element to change
 *
 * know right hand side in a/b word format (maybe wide) of right width
 */
static void gen_chg_st_unpck_arr_val(struct net_t *np, int32 eladdr_ti, 
 int32 rhs_apti, int32 bi, int32 bi_ti, int32 is_const)
{
 struct bblk_t *chgstore_bbp, *testb_bbp, *skip_bbp;
 int32 rhs_bpti, eladdr_bpti, blen, nbytes, srtyp;

 chgstore_bbp = __alloc_bblk(FALSE); 
 skip_bbp = __alloc_bblk(FALSE);

 /* catch the special real case */
 if (__tntab[rhs_apti].t_real)
  {
   __emit_jmp_real_cmp(skip_bbp, chgstore_bbp, rhs_apti, eladdr_ti, CC_JE);
   /* AIV 08/03/10 - real copies are always 8 bytes - this avoids */
   /* checking for empty bpart for 64-bit since REALBITS is 64 */
   nbytes = 8;
  }
 else
  {
   blen = __tntab[eladdr_ti].tnwid;
   srtyp = __get_array_srep_type(np);
   if (srtyp != SR_BIT2S) 
    {
     testb_bbp = __alloc_bblk(FALSE);
     __emit_jmp_eq(testb_bbp, chgstore_bbp, rhs_apti, eladdr_ti);
     __start_bblk(testb_bbp);

     rhs_bpti = __get_bpti(rhs_apti);
     eladdr_bpti = __get_bpti(eladdr_ti);
     /* notice b part compare knows to access the b part offset from ptr */
     __emit_jmp_eq(skip_bbp, chgstore_bbp, rhs_bpti, eladdr_bpti);
     /* copy a/b part words into the new element space */
     /* AIV 01/10/06 - was only copying 2 words all the time - wrong for wide */
     nbytes = 2*WRDBYTES*wlen_(blen);
    }
   else 
    {
     nbytes = WRDBYTES*wlen_(blen);
     __emit_jmp_eq(skip_bbp, chgstore_bbp, rhs_apti, eladdr_ti);
    }
  }

 __start_bblk(chgstore_bbp);
 /* copy a/b part words into the new element space */
 /* AIV 01/10/06 - was only copying 2 words all the time - wrong for wide */
 __emit_copy(nbytes, rhs_apti, eladdr_ti);
 if (is_const)
  {
   __gen_record_const_nchg(np, bi, bi, skip_bbp);
  }
 else
  {
   __gen_record_var_nchg(np, bi_ti, skip_bbp);
  }
 __start_bblk(skip_bbp);
}

/*
 * lhs store into scalar array (all forms) - rhs is addr of scalar  
 * scalar arrays is packed to the bit (every memory cell just 2 bits)
 *
 * notice rhs scal ti can be addr or val
 */ 
static void gen_st_scalar_lhs_arrsel_var(struct expr_t *lhsx,
 int32 addr_apti, int32 bi_ti, int32 rhs_scal_ti)
{
 int32 ouwrd_2b_ti, ouwrd_ti, nuwrd_ti, cint_ti;
 int32 wbyti_ti, bofs_ti, indi_ti, mask_ti, mask_new2b_off_ti;
 int32 isolate_2b_mask_ti, srtyp, is_2state;
 struct net_t *np;
 struct bblk_t *skip_bbp, *store_bbp;

 np = lhsx->lu.x->lu.sy->el.enp;
 
 srtyp = __get_array_srep_type(np);
 /* if 2-state no 2*index */
 if (srtyp == SR_SCAL2S) is_2state = TRUE;
 else is_2state = FALSE;

 /* compute the scalar packed array bit off (2 bits per element) */
 if (is_2state) indi_ti = bi_ti;
 else 
  {
   cint_ti = __gen_cint_tn(2);
   indi_ti = __emit_mult(WBITS, bi_ti, cint_ti);
  }

 /* compute the word as bytes and bit (bi) offsets for bit to store into */
 /* divide by 4 to gets words except sizes in asm always bytes */
 wbyti_ti = gen_scalarr_wbyti_bofs(&(bofs_ti), indi_ti);

 /* ptr to the word containing the 2 bit packed scalar to store into */
 ouwrd_ti = __var_adradd_insn(SR_VEC, 1, addr_apti, wbyti_ti);

 /* DBG remove --- */
 srtyp = __tntab[rhs_scal_ti].srtyp;
 if (srtyp != SR_SCAL && srtyp != SR_SCAL2S) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* mask is the 2 bits at correct in wrd offset 1's, all other bits 0 */
 /* uwrd &= ~(3L << bi) */ 
 if (is_2state) cint_ti = __gen_cint_tn(1);
 else cint_ti = __gen_cint_tn(3);
 mask_ti = __emit_shiftl(WBITS, bofs_ti, cint_ti);
 isolate_2b_mask_ti = __emit_bitnot(WBITS, mask_ti);

 /* this is old value with only the 2 bits that are being changed unmasked */
 ouwrd_2b_ti = __emit_bin_bitand(WBITS, ouwrd_ti, isolate_2b_mask_ti);

 /* know scal here so just shift and or in */
 /* new: uwrd |=  [rhs_scal_ti] << bofs_ti; */
 /* form inter : uwrd |= (((rgap[0] & 1L) | ((rgbp[0] & 1L) << 1)) << bi); */
 mask_new2b_off_ti = __emit_shiftl(WBITS, bofs_ti, rhs_scal_ti); 

 /* calc the new value */
 nuwrd_ti = __emit_bin_bitor(WBITS, ouwrd_2b_ti, mask_new2b_off_ti);

 /* no need for change store just copy */
 if (!__net_chg_nd_store(np, -1, -1))
  {
   __emit_copy(WRDBYTES, nuwrd_ti, ouwrd_ti);
   return;
  }

 skip_bbp = __alloc_bblk(FALSE);
 store_bbp = __alloc_bblk(FALSE);

 /* compare the old and new values */
 __emit_jmp_eq(skip_bbp, store_bbp, ouwrd_ti, nuwrd_ti); 

 __start_bblk(store_bbp); 

 /* do the copy and record */
 __emit_copy(WRDBYTES, nuwrd_ti, ouwrd_ti);

 __gen_record_var_nchg(np, bi_ti, skip_bbp);
 /* no change */
 __start_bblk(skip_bbp); 
}

/*
 * scalar array lhs where index is a known constant
 */
static void gen_st_scalar_lhs_arrsel_const(struct net_t *np,
 int32 addr_apti, int32 bi, int32 rhs_scal_ti)
{
 int32 ouwrd_2b_ti, ouwrd_ti, nuwrd_ti, indi, mask_new2b_off_ti, wi; 
 int32 srtyp, is_2state, rhs_scal_reg_ti, amtyp;
 word32 mask;
 int32 cint_ti, biti;
 struct bblk_t *skip_bbp, *store_bbp;

 /* compute the scalar packed array bit off (2 bits per element) */
 if (__inst_mod->flatinum != 1)
  {
   /* if IS handle with separate routine since index must be computed */
   gen_st_scalar_lhs_arrsel_is_const(np, addr_apti, bi, rhs_scal_ti);
   return;
  }

 srtyp = __get_array_srep_type(np);
 /* if 2-state no 2*index */
 if (srtyp == SR_SCAL2S) is_2state = TRUE;
 else is_2state = FALSE;

 if (is_2state) indi = bi;
 else indi = 2*bi;

 wi = get_wofs_(indi);
 biti = get_bofs_(indi);

 /* ptr to the word containing the 2 bit packed scalar to store into */
 ouwrd_ti = __con_adradd_insn(SR_VEC, 1, addr_apti, wi*WRDBYTES);

 /* mask is the 2 bits at correct in wrd offset 1's, all other bits 0 */
 /* uwrd &= ~(3L << bi) */ 
 if (is_2state) mask = ~(1UL << biti);
 else mask = ~(3UL << biti);

 cint_ti = __gen_cint_tn(mask);
 /* this is old value with only the 2 bits that are being changed unmasked */
 ouwrd_2b_ti = __emit_bin_bitand(WBITS, ouwrd_ti, cint_ti);

 /* know scal here so just shift and or in */
 /* new: uwrd |=  [rhs_scal_ti] << bofs_ti; */
 /* form inter : uwrd |= (((rgap[0] & 1L) | ((rgbp[0] & 1L) << 1)) << bi); */

 /* AIV 03/30/11 - rare bug for 0 element here - if rhs was zero would */
 /* not do the shift (optimize shift of zero) the overwrite the rhs value */
 /* need to do a move here */
 if (__tntab[rhs_scal_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
 else amtyp = AM_REG;
 rhs_scal_reg_ti = __move_insn(TN_VAL, I_MOVA, amtyp, rhs_scal_ti);

 cint_ti = __gen_cint_tn(biti);
 mask_new2b_off_ti = __emit_shiftl(WBITS, cint_ti, rhs_scal_reg_ti);

 /* calc the new value */
 nuwrd_ti = __emit_bin_bitor(WBITS, ouwrd_2b_ti, mask_new2b_off_ti);

 /* no need for change store just copy */
 if (!__net_chg_nd_store(np, bi, bi))
  {
   __emit_copy(WRDBYTES, nuwrd_ti, ouwrd_ti);
   return;
  }

 skip_bbp = __alloc_bblk(FALSE);
 store_bbp = __alloc_bblk(FALSE);

 /* compare the old and new values */
 __emit_jmp_eq(skip_bbp, store_bbp, ouwrd_ti, nuwrd_ti); 

 __start_bblk(store_bbp); 

 /* do the copy and record */
 __emit_copy(WRDBYTES, nuwrd_ti, ouwrd_ti);

 /* AIV 06/15/07 - was passing the wrong range value was never testing */
 /* was replacing bi with the the new bi for accessing scalar value */
 __gen_record_const_nchg(np, bi, bi, skip_bbp);
 /* no change */
 __start_bblk(skip_bbp); 
}

/*
 * IS scalar lhs arrsel where bi is known constant
 * almost the same as non-constant verison this only takes advantage in
 * a couple of places
 */
static void gen_st_scalar_lhs_arrsel_is_const(struct net_t *np,
 int32 addr_apti, int32 bi, int32 rhs_scal_ti)
{
 int32 ouwrd_2b_ti, ouwrd_ti, nuwrd_ti, cint_ti;
 int32 wofs, bofs, bofs_ti, mask_ti, srtyp, rhs_scal_reg_ti, amtyp;
 int32 isolate_2b_mask_ti, mask_new2b_off_ti, is_2state;
 struct bblk_t *skip_bbp, *store_bbp;

 /* SJM 11/30/07 - know offset know at compile time - can compute offset */  
 /* get CT the word as bytes and bit (bi) offsets for bit to store into */
 srtyp = __get_array_srep_type(np);
 /* if 2-state no 2*index */
 if (srtyp == SR_SCAL2S) is_2state = TRUE;
 else is_2state = FALSE;

 if (is_2state)
  {
   wofs = get_wofs_(bi);
   bofs = get_bofs_(bi); 
  }
 else
  {
   wofs = get_wofs_(2*bi);
   bofs = get_bofs_(2*bi); 
  }

 /* ptr to the word containing the 2 bit packed scalar to store into */
 ouwrd_ti = __con_adradd_insn(SR_VEC, 1, addr_apti, wofs);

 /* DBG remove --- */
 srtyp = __tntab[rhs_scal_ti].srtyp;
 if (srtyp != SR_SCAL && srtyp != SR_SCAL2S) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* mask is the 2 bits at correct in wrd offset 1's, all other bits 0 */
 /* uwrd &= ~(3L << bi) */ 
 if (is_2state) cint_ti = __gen_cint_tn(1);
 else cint_ti = __gen_cint_tn(3);
 /* SJM 11/30/07 - this is constant case but still need tn for now */
 bofs_ti = __gen_cint_tn(bofs);
 mask_ti = __emit_shiftl(WBITS, bofs_ti, cint_ti);
 isolate_2b_mask_ti = __emit_bitnot(WBITS, mask_ti);

 /* this is old value with only the 2 bits that are being changed unmasked */
 ouwrd_2b_ti = __emit_bin_bitand(WBITS, ouwrd_ti, isolate_2b_mask_ti);

 /* AIV 03/30/11 - rare bug for 0 element here - if rhs was zero would */
 /* not do the shift (optimize shift of zero) the overwrite the rhs value */
 /* need to do a move here */
 if (__tntab[rhs_scal_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
 else amtyp = AM_REG;
 rhs_scal_reg_ti = __move_insn(TN_VAL, I_MOVA, amtyp, rhs_scal_ti);

 /* know scal here so just shift and or in */
 /* new: uwrd |=  [rhs_scal_ti] << bofs_ti; */
 /* form inter : uwrd |= (((rgap[0] & 1L) | ((rgbp[0] & 1L) << 1)) << bi); */
 mask_new2b_off_ti = __emit_shiftl(WBITS, bofs_ti, rhs_scal_reg_ti); 

 /* calc the new value */
 nuwrd_ti = __emit_bin_bitor(WBITS, ouwrd_2b_ti, mask_new2b_off_ti);

 /* no need for change store just copy */
 if (!__net_chg_nd_store(np, bi, bi))
  {
   __emit_copy(WRDBYTES, nuwrd_ti, ouwrd_ti);
   return;
  }

 skip_bbp = __alloc_bblk(FALSE);
 store_bbp = __alloc_bblk(FALSE);

 /* compare the old and new values */
 __emit_jmp_eq(skip_bbp, store_bbp, ouwrd_ti, nuwrd_ti);

 __start_bblk(store_bbp); 

 /* do the copy and record */
 __emit_copy(WRDBYTES, nuwrd_ti, ouwrd_ti);

 __gen_record_const_nchg(np, bi, bi, skip_bbp);
 /* no change */
 __start_bblk(skip_bbp); 
}

/*
 * chg store packed array index 
 * pck el is an addr
 */
static void gen_chg_st_pck_arr_val(struct net_t *np, int32 pckel_ti,
 int32 nuwrd_ti, int32 bi, int32 bi_ti, int32 is_const)
{
 struct bblk_t *skip_bbp, *store_bbp;
 int32 cpbytes;

 skip_bbp = __alloc_bblk(FALSE);
 store_bbp = __alloc_bblk(FALSE);

 cpbytes = -1;
 if (np->nwid <= 4) cpbytes = 1;
 else if (np->nwid <= 8) cpbytes = 2; 
 else if (np->nwid <= WBITS/2) cpbytes = WRDBYTES; 
 else __case_terr(__FILE__, __LINE__);

 /* AIV 11/01/07 - no need to call packing wrapper here */
 /* AIV 10/11/09 - this was still wrong - just need to call with cpbytes */
 /* this routine handles all cases 1-4 bytes for 32, and 1-8 for 64-bit */
 /* including the word align case */
 __emit_narrow_byte_eq(cpbytes, skip_bbp, store_bbp, pckel_ti, nuwrd_ti);
 
 __start_bblk(store_bbp); 

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(cpbytes, nuwrd_ti, pckel_ti);
 if (is_const)
  {
   __gen_record_const_nchg(np, bi, bi, skip_bbp);
  }
 else
  {
   __gen_record_var_nchg(np, bi_ti, skip_bbp);
  }
 __start_bblk(skip_bbp); 
}

/*
 * gen wi and bi offsets - wid must be power of 2 less than 32 (WBITS?)
 *
 * SJM 11/21/04 - LOOKATME - think can only be 1 or 2
 */
static int32 gen_wbyti_bofs(int32 addr_ti, int32 *bofs_ti, int32 indi_ti)
{
 int32 wi_ti, wbyti_ti, cint_ti;

 /* AIV 07/15/05 - if one word don't compute index must check for -1 */ 
 if (__get_tnwid(addr_ti) <= WBITS)
  {
   wbyti_ti = -1;
   *bofs_ti = indi_ti;
  }
 else 
  {
#ifdef __CVC32__
   cint_ti = __gen_cint_tn(5);
   wi_ti = __emit_shiftr(WBITS, cint_ti, indi_ti);
   /* need offset number of word but converted to bytes */ 
   cint_ti = __gen_cint_tn(WRDBYTES);
   wbyti_ti = __emit_mult(WBITS, wi_ti, cint_ti);
   cint_ti = __gen_cint_tn(0x1f);
   *bofs_ti = __emit_mask_and(indi_ti, cint_ti);
#else
   cint_ti = __gen_cint_tn(6);
   wi_ti = __emit_shiftr(WBITS, cint_ti, indi_ti);
   /* need offset number of word but converted to bytes */ 
   cint_ti = __gen_cint_tn(WRDBYTES);
   wbyti_ti = __emit_mult(WBITS, wi_ti, cint_ti);
   cint_ti = __gen_cint_tn(0x3f);
   *bofs_ti = __emit_mask_and(indi_ti, cint_ti);
#endif
  }

 return(wbyti_ti);
}

/*
 * gen wi and bi offsets - wid must be power of 2 less than 32 (WBITS?)
 * AIV 07/15/05 - same as above but because scalar packed must add regardless
 * of the size of the tmp 
 */
static int32 gen_scalarr_wbyti_bofs(int32 *bofs_ti, int32 indi_ti)
{
 int32 wi_ti, wbyti_ti, cint_ti;

#ifdef __CVC32__
 cint_ti = __gen_cint_tn(5);
 wi_ti = __emit_shiftr(WBITS, cint_ti, indi_ti);
 /* need offset number of word but converted to bytes */ 
 cint_ti = __gen_cint_tn(WRDBYTES);
 wbyti_ti = __emit_mult(WBITS, wi_ti, cint_ti);

 cint_ti = __gen_cint_tn(0x1f);
 *bofs_ti = __emit_mask_and(indi_ti, cint_ti);
#else
 cint_ti = __gen_cint_tn(6);
 wi_ti = __emit_shiftr(WBITS, cint_ti, indi_ti);
 /* need offset number of word but converted to bytes */ 
 cint_ti = __gen_cint_tn(WRDBYTES);
 wbyti_ti = __emit_mult(WBITS, wi_ti, cint_ti);

 cint_ti = __gen_cint_tn(0x3f);
 *bofs_ti = __emit_mask_and(indi_ti, cint_ti);
#endif
 return(wbyti_ti);
}

/*
 * build a mask of a given width shifted left by bi bytes - possibly inverted
 * know mask wid WBITS or narrower
 */
static int32 gen_bld_varmask(int32 bi_ti, int32 maskwid, int32 is_invert) 
{
 int32 mask_ti, t1_ti, cint_ti;

 /* DBG --- */
 if (maskwid > WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* although srep a C int, since not using signed shift - treated as wrd32 */
 cint_ti = __gen_cint_tn(__masktab[maskwid]);
 mask_ti = __emit_shiftl(WBITS, bi_ti, cint_ti);
 if (is_invert)
  {
   t1_ti = __emit_bitnot(WBITS, mask_ti);
   mask_ti = t1_ti;
  }
 return(mask_ti);
}

/*
 * compute rhs (know a/b vec srep and exactly right width) into new word val
 * packed contiguous a/b part into word
 */
static int32 bld_pck_nwval(struct net_t *np, int32 rhs_apti, int32 blen)  
{
 int32 rhs_bpti, t1_ti, t2_ti, nuwrd_ti, cint_ti, srtyp;
 
 srtyp = __get_array_srep_type(np);

 /* build the a/b parts into a word */
 t1_ti = __gen_tn(srtyp, WBITS);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, rhs_apti, t1_ti);
 if (srtyp == SR_BIT2S) return(t1_ti);

 rhs_bpti = __get_bpti(rhs_apti);
 cint_ti = __gen_cint_tn(blen);
 t2_ti = __emit_shiftl(WBITS, cint_ti, rhs_bpti);
 nuwrd_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
 return(nuwrd_ti);
}

/*
 * gen insns to assign to bit (non stren form - lhs sr vec srep)
 * non stren form (also for proc) - for variable index assign
 *
 * caller must always check and skip if forced/assigned
 */
static void gen_assgn_to_bit_var(struct expr_t *lhsx, int32 biti_ti,
 int32 rhs_apti, int32 xmr_pushed)
{
 int32 addr_apti;
 struct expr_t *idndp;
 struct net_t *np;

 addr_apti = -1;
 idndp = lhsx->lu.x;
 np = idndp->lu.sy->el.enp;

 if (idndp->optyp == ID) addr_apti = __ldvar_addr(np, NULL);
 else if (idndp->optyp == GLBREF)
  {
   if (xmr_pushed) addr_apti = __ldvar_addr(np, NULL);
   else addr_apti = __ldvar_addr(np, idndp->ru.grp);
  }
 else __case_terr(__FILE__, __LINE__);

 /* AIV 10/23/08 - ranges are already checked around this call */
 /* if out of range will never get here */
 /* this also handles the assign */
 __gen_lhsbsel_var(np, addr_apti, biti_ti, rhs_apti);
}

/*
 * constant version of above
 */
extern void __gen_assgn_to_bit_const(struct expr_t *lhsx, int32 bi,
 int32 rhs_apti, int32 xmr_pushed)
{
 int32 addr_apti;
 struct expr_t *idndp;
 struct net_t *np;

 addr_apti = -1;
 idndp = lhsx->lu.x;
 np = idndp->lu.sy->el.enp;

 /* DBG remove -- */
 if (np->ntyp == N_STRING)__misc_terr(__FILE__, __LINE__);
 /* ---- */

 if (idndp->optyp == ID) addr_apti = __ldvar_addr(np, NULL);
 else if (idndp->optyp == GLBREF)
  {
   if (xmr_pushed) addr_apti = __ldvar_addr(np, NULL);
   else addr_apti = __ldvar_addr(np, idndp->ru.grp);
  }
 else __case_terr(__FILE__, __LINE__);

 /* AIV 10/23/08 - if out or range just skip the assign */
 if (bi == -1)
  {
   return;
  }

 __gen_lhsbsel_const(np, addr_apti, bi, rhs_apti);
}

/*
 * gen lhs proc sr vec bit store
 *
 * for change form must run in context of lhs expr
 */
extern void __gen_lhsbsel_var(struct net_t *np, int32 addr_apti,
 int32 bi_ti, int32 rhs_ti)
{
 int32 bofs_ti, wbyti_ti, mask_ti, wadr_apti, wadr_bpti, nwrd_apti;
 int32 rhs_bpti, t1_ti, t2_ti, t3_ti, mask2_ti, addr_bpti;

 if (np->n_stren)
  {
   __gen_stren_lhsbsel(np, addr_apti, -1, bi_ti, rhs_ti, FALSE);
   return;
  }
 
 if (__net_chg_nd_store(np, -1, -1))
  {
   gen_chg_lhsbsel_var(np, addr_apti, bi_ti, rhs_ti);
  }
 else
  {
 //AIV HERE FIXME - this should just assign ??????? why is this comparing ???
   wbyti_ti = gen_wbyti_bofs(addr_apti, &(bofs_ti), bi_ti);
   mask_ti = gen_bld_varmask(bofs_ti, 1, TRUE); 
   /* do not need to compute this twice */

   if (wbyti_ti != -1)
    {
     wadr_apti = comp_ndxwrd_addr(addr_apti, wbyti_ti);
    }
   else wadr_apti = addr_apti;
   /* AIV 08/01/08 - rearranged operations to prevent spill for common case */
   mask2_ti = gen_getbit(rhs_ti, bofs_ti, FALSE);
   t1_ti = __emit_mask_and(wadr_apti,  mask_ti);
   nwrd_apti = __emit_bin_bitor(WBITS, t1_ti, mask2_ti);
   __emit_copy(WRDBYTES, nwrd_apti, wadr_apti);
   if (np->n_2state) return;
 
   /* separately handle b part */
   rhs_bpti = __get_bpti(rhs_ti);
   mask2_ti = gen_getbit(rhs_bpti, bofs_ti, FALSE);

   addr_bpti = __get_bpti(addr_apti);
   if (wbyti_ti != -1)
    {
     wadr_bpti = comp_ndxwrd_addr(addr_bpti, wbyti_ti);
    }
   else wadr_bpti = addr_bpti;
   t2_ti = __emit_mask_and(wadr_bpti, mask_ti);
   t3_ti = __emit_bin_bitor(WBITS, t2_ti, mask2_ti);

   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(WRDBYTES, t3_ti, wadr_bpti);
   /* both a/b part of result now in nwrd apti */
  }
}

/*
 * generate a lhs bit select with a known constant index
 */
extern void __gen_lhsbsel_const(struct net_t *np, int32 addr_apti, int32 bi,
 int32 rhs_ti)
{
 if (np->n_stren)
  {
   __gen_stren_lhsbsel(np, addr_apti, bi, -1, rhs_ti, TRUE);
   return;
  }

 if (__net_chg_nd_store(np, bi, bi))
  {
   gen_chg_lhsbsel_const(np, addr_apti, bi, rhs_ti);
  }
 else
  {
   gen_lhsbsel_const_norecord(np, addr_apti, bi, rhs_ti);
  }
}

/*
 * generate a constant lhs bsel with no recording
 */
static void gen_lhsbsel_const_norecord(struct net_t *np, int32 addr_apti, 
 int32 bi, int32 rhs_ti)
{
 int32 wi, wadr_apti, wadr_bpti, nwrd_apti, twid, cint_ti;
 int32 rhs_bpti, t1_ti, t2_ti, t3_ti, mask2_ti, b_ofs, srtyp;
 word32 mask;

 wi = get_wofs_(bi);
 bi = get_bofs_(bi); 
 mask =  ~(__masktab[1] << bi);
 mask2_ti = gen_getbit(rhs_ti, bi, TRUE);
 
 if (np->srep == SR_ARRAY)
  {
   srtyp = __get_array_srep_type(np); 
  }
 else if (np->srep == SR_BIT2S) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;

 twid = __get_tnwid(addr_apti);
 if (wi != 0)
  {
   wadr_apti = __con_adradd_insn(srtyp, twid, addr_apti, wi*WRDBYTES);
  }
 else wadr_apti = addr_apti;

 cint_ti = __gen_cint_tn(mask);
 t1_ti = __emit_mask_and(wadr_apti, cint_ti);
 nwrd_apti = __emit_bin_bitor(WBITS, t1_ti, mask2_ti);
 /* AIV 01/21/08 - should do store here to avoid reg live range issues */
 __emit_copy(WRDBYTES, nwrd_apti, wadr_apti);
 if (srtyp == SR_BIT2S) return;

 /* separately handle b part */
 if (wi != 0)
  {
   b_ofs = (wi + wlen_(twid))*WRDBYTES;
   wadr_bpti = __con_adradd_insn(SR_VEC, twid, addr_apti, b_ofs);
  }
 else wadr_bpti = __get_bpti(addr_apti);

 cint_ti = __gen_cint_tn(mask);
 t2_ti = __emit_mask_and(wadr_bpti, cint_ti);
 rhs_bpti = __get_bpti(rhs_ti);
 mask2_ti = gen_getbit(rhs_bpti, bi, TRUE);
 t3_ti = __emit_bin_bitor(WBITS, t2_ti, mask2_ti);

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, t3_ti, wadr_bpti);
 /* both a/b part of result now in nwrd apti */
}

/*
 * gen lhs proc sr svec bit store
 */
extern void __gen_stren_lhsbsel(struct net_t *np, int32 addr_apti, int32 bi, 
 int32 bi_ti, int32 rhs_ti, int32 is_const)
{
 int32 sbp_ti, needs_chg;

 if (is_const) needs_chg = __net_chg_nd_store(np, bi, bi);
 else needs_chg = __net_chg_nd_store(np, -1, -1);

 if (needs_chg)
  {
   gen_chg_stren_lhsbsel(np, addr_apti, bi, bi_ti, rhs_ti, is_const);
  }
 else
  {
   /* AIV 01/23/06 - note addr base is already adjusted for __inum > 1 here */
   /* netsbp[biti] = (byte) av; */
   if (is_const)
    {
     sbp_ti = __con_adradd_insn(SR_VEC, np->nwid, addr_apti, bi);
    }
   else
    {
     sbp_ti = __var_adradd_insn(SR_VEC, np->nwid, addr_apti, bi_ti);
    }
   /* copy one byte */
   __emit_copy(1, rhs_ti, sbp_ti);
  }
}

/*
 * compute the following calculation
 * ((sw & 1L) << bi);
 */
static int32 gen_getbit(int32 var_apti, int32 bofs_ti, int32 is_const) 
{
 int32 t1_ti, mask_ti, one_ti;

 one_ti = __gen_cint_tn(1);
 t1_ti = __emit_mask_and(var_apti, one_ti);
 if (is_const) bofs_ti =  __gen_cint_tn(bofs_ti);
 mask_ti = __emit_shiftl(WBITS, bofs_ti, t1_ti);
 return(mask_ti);
}

/*
 * compute indexed word offset into tmp name (non IS non packed select) 
 *
 * literals and vars same here - lowering optimizer simplifies
 * addr ti must be base of a part or b part then eval the same
 *
 * if fi>1:  rap = pckv.wp + 2*wlen*<inum> + wi
 * if fi==1: rap = pckv.wp + wi 
 *
 * AIV - 09/23/05 - most computation already done - can probably remove
 */
static int32 comp_ndxwrd_addr(int32 addr_apti, int32 wbyti_ti)
{
 int32 ndxbase_ti;

 /* load base of array storage area into tmp ptr (address) reg */
 ndxbase_ti = __var_adradd_insn(SR_VEC, __get_tnwid(addr_apti),
  addr_apti, wbyti_ti);
 return(ndxbase_ti);
}

/*
 * gen assign to bsel chg store insns - complex because must compare and
 * skip if same
 * for variable lhs bsel index case
 *
 * this must run in itree context of lhs expr
 */
static void gen_chg_lhsbsel_var(struct net_t *np, int32 addr_apti,
 int32 bi_ti, int32 rhs_ti)
{
 int32 bofs_ti, wbyti_ti, mask_ti, wadr_apti, wadr_bpti, addr_bpti;
 int32 rhs_bpti, nwrd_apti, nwrd_bpti, t1_ti, t2_ti, t3_ti, mask2_ti;
 struct bblk_t *chgstore_bbp, *skip_bbp;

 chgstore_bbp = __alloc_bblk(FALSE); 
 skip_bbp = __alloc_bblk(FALSE);

 wbyti_ti = gen_wbyti_bofs(addr_apti, &(bofs_ti), bi_ti);
 mask_ti = gen_bld_varmask(bofs_ti, 1, TRUE); 
 mask2_ti = gen_getbit(rhs_ti, bofs_ti, FALSE);

 if (wbyti_ti != -1)
  {
   wadr_apti = comp_ndxwrd_addr(addr_apti, wbyti_ti);
  }
 else wadr_apti = addr_apti;
 t1_ti = __emit_mask_and(wadr_apti, mask_ti);
 nwrd_apti = __emit_bin_bitor(WBITS, t1_ti, mask2_ti);
 
 /* if two state just check the a part */
 if (np->n_2state)
  {
   /* AIV 10/15/10 - jmp_eq assumes == tmp size just xor and cmp word here */
   t1_ti = __emit_bin_bitxor(WBITS, nwrd_apti, wadr_apti);
   __emit_jmp_0(skip_bbp, chgstore_bbp, t1_ti);
   __start_bblk(chgstore_bbp);
   __emit_copy(WRDBYTES, nwrd_apti, wadr_apti);
   __gen_record_var_nchg(np, bi_ti, skip_bbp);
   __start_bblk(skip_bbp);
   return;
  }

 /* same thing with b part */
 addr_bpti = __get_bpti(addr_apti);

 if (wbyti_ti != -1)
  {
   wadr_bpti = comp_ndxwrd_addr(addr_bpti, wbyti_ti);
  }
 else wadr_bpti = addr_bpti;
 t1_ti = __emit_mask_and(wadr_bpti, mask_ti);
 rhs_bpti = __get_bpti(rhs_ti);
 mask2_ti = gen_getbit(rhs_bpti, bofs_ti, FALSE);
 nwrd_bpti = __emit_bin_bitor(WBITS, t1_ti, mask2_ti);

 /* must compare both a and b 2v parts - reg is first and ptr is 2nd opand */
 /* AIV 01/07/08 - better to the xor and only do the one compare */
 t1_ti = __emit_bin_bitxor(WBITS, nwrd_apti, wadr_apti);
 t2_ti = __emit_bin_bitxor(WBITS, nwrd_bpti, wadr_bpti);
 t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);

 __emit_jmp_0(skip_bbp, chgstore_bbp, t3_ti);
 __start_bblk(chgstore_bbp);
 
 /* this is replaces words in a wider vector */
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, nwrd_apti, wadr_apti);
 __emit_copy(WRDBYTES, nwrd_bpti, wadr_bpti);
 __gen_record_var_nchg(np, bi_ti, skip_bbp);
 __start_bblk(skip_bbp);
}

/*
 * gen assign to bsel chg store insns - complex because must compare and
 * skip if same
 *
 * for const (literal) lhs bsel index case
 */
static void gen_chg_lhsbsel_const(struct net_t *np, int32 addr_apti, 
 int32 bi, int32 rhs_ti)
{
 int32 wi, wadr_apti, wadr_bpti, twid, cint_ti, bofs, b_ofs;
 int32 rhs_bpti, nwrd_apti, nwrd_bpti, t1_ti, t2_ti, t3_ti, mask2_ti;
 word32 mask;
 struct bblk_t *chgstore_bbp, *skip_bbp;

 chgstore_bbp = __alloc_bblk(FALSE); 
 skip_bbp = __alloc_bblk(FALSE);

 /* AIV 01/08/07 - was overwriting the constant bi with the constant bi ofset */
 /* added bofs - bi is always the constant bit index */
 wi = get_wofs_(bi);
 bofs = get_bofs_(bi); 
 mask =  ~(__masktab[1] << bofs);
 mask2_ti = gen_getbit(rhs_ti, bofs, TRUE);

 twid = __get_tnwid(addr_apti);
 if (wi != 0)
  {
   wadr_apti = __con_adradd_insn(SR_VEC, twid, addr_apti, wi*WRDBYTES);
  }
 else wadr_apti = addr_apti;

 cint_ti = __gen_cint_tn(mask);
 t1_ti = __emit_mask_and(wadr_apti, cint_ti);
 nwrd_apti = __emit_bin_bitor(WBITS, t1_ti, mask2_ti);
 if (np->n_2state)
  {
   /* AIV 10/15/10 - jmp_eq assumes == tmp size just xor and cmp word here */
   t1_ti = __emit_bin_bitxor(WBITS, nwrd_apti, wadr_apti);
   __emit_jmp_0(skip_bbp, chgstore_bbp, t1_ti);

   __start_bblk(chgstore_bbp);
 
   __emit_copy(WRDBYTES, nwrd_apti, wadr_apti);
   __gen_record_const_nchg(np, bi, bi, skip_bbp);
   __start_bblk(skip_bbp);
   return;
  }

 /* same thing with b part */
 if (wi != 0)
  {
   b_ofs = (wi + wlen_(twid))*WRDBYTES;
   wadr_bpti = __con_adradd_insn(SR_VEC, twid, addr_apti, b_ofs);
  }
 else wadr_bpti = __get_bpti(addr_apti);

 cint_ti = __gen_cint_tn(mask);
 t1_ti = __emit_mask_and(wadr_bpti, cint_ti);
 rhs_bpti = __get_bpti(rhs_ti);
 mask2_ti = gen_getbit(rhs_bpti, bofs, TRUE);
 nwrd_bpti = __emit_bin_bitor(WBITS, t1_ti, mask2_ti);

 /* AIV 01/07/08 - better to the xor and only do the one compare */
 t1_ti = __emit_bin_bitxor(WBITS, nwrd_apti, wadr_apti);
 t2_ti = __emit_bin_bitxor(WBITS, nwrd_bpti, wadr_bpti);
 t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);

 __emit_jmp_0(skip_bbp, chgstore_bbp, t3_ti);
 __start_bblk(chgstore_bbp);
 
 /* this is replaces words in a wider vector */
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, nwrd_apti, wadr_apti);
 __emit_copy(WRDBYTES, nwrd_bpti, wadr_bpti);
 __gen_record_const_nchg(np, bi, bi, skip_bbp);
 __start_bblk(skip_bbp);
}

/*
 * strength - same as above but only stores the a part 
 */
static void gen_chg_stren_lhsbsel(struct net_t *np, int32 addr_apti,
 int32 bi, int32 bi_ti, int32 rhs_ti, int32 is_const)
{
 int32 sbp_ti;
 struct bblk_t *chgstore_bbp, *skip_bbp;

 chgstore_bbp = __alloc_bblk(FALSE); 
 skip_bbp = __alloc_bblk(FALSE);

 /* AIV 01/23/06 - note addr base is already adjusted for __inum > 1 here */
 /* netsbp[biti] = (byte) av; */
 if (is_const)
  {
   sbp_ti = __con_adradd_insn(SR_VEC, np->nwid, addr_apti, bi);
  } 
 else  
  {
   sbp_ti = __var_adradd_insn(SR_VEC, np->nwid, addr_apti, bi_ti);
  }

 /* must compare stren value */
 __emit_jmp_byte_eq(skip_bbp, chgstore_bbp, sbp_ti, rhs_ti);

 __start_bblk(chgstore_bbp);
 /* copy one byte */
 __emit_copy(1, rhs_ti, sbp_ti);

 if (is_const)
  {
   __gen_record_const_nchg(np, bi, bi, skip_bbp);
  }
 else
  {
   __gen_record_var_nchg(np, bi_ti, skip_bbp);
  }
 __start_bblk(skip_bbp);
}

/*
 * gen vm insns for assign to part select
 *
 * any procedural force/assign handled outside of here because for regs
 */
extern void __gen_assgn_to_psel(struct expr_t *lhsx, int32 rhs_ti, 
 int32 xmr_pushed)
{
 int32 addr_apti, ri1, ri2, srtyp, pselwid;
 struct expr_t *idndp;
 struct net_t *np;
 struct gref_t *grp;

 /* DBG remove -- */
 srtyp = __tntab[rhs_ti].srtyp;
 switch (srtyp) {
  case SR_VEC: case SR_SCAL: case SR_SVEC: case SR_BIT2S: case SR_SCAL2S:
   break;
   default: __case_terr(__FILE__, __LINE__);
   break;
  }
 /* --- */

 ri1 = (int32) __contab[lhsx->ru.x->lu.x->ru.xvi];
 ri2 = (int32) __contab[lhsx->ru.x->ru.x->ru.xvi];
 idndp = lhsx->lu.x;
 if (idndp->optyp == ID)
  {
   np = idndp->lu.sy->el.enp;
   grp = NULL;
  }
 else if (idndp->optyp == GLBREF) 
  {
   /* AIV 01/31/06 - if pushed to xmr don't need global ref */
   /* LOOKATME - currently always pushed by here (xmr_pushed = T) */ 
   np = idndp->lu.sy->el.enp;
   if (xmr_pushed) grp = NULL;
   else grp = idndp->ru.grp;
  }
 else { grp = NULL; np = NULL; __case_terr(__FILE__, __LINE__); }

 /* AIV 10/10/05 - forgot the needed conversion */
 rhs_ti = __gen_cnvt_srep_ifneeded(rhs_ti, np->srep, lhsx->szu.xclen, 
   np->n_signed, FALSE, FALSE);
 addr_apti = __ldvar_addr(np, grp);
 pselwid = ri1 - ri2 + 1;
 /* AIV 09/13/10 - check for entire net change for width one (bsel) */
 if (__net_chg_nd_store(idndp->lu.sy->el.enp, ri1, ri2))
  {
   if (pselwid == np->nwid) 
    {
     __gen_chg_st_val(np, addr_apti, rhs_ti);
     return;
    }
   else if (ri1 == ri2) 
    {
     gen_chg_lhsbsel_const(np, addr_apti, ri1, rhs_ti);
     return;
    }
   __gen_chg_lhspsel(np, lhsx->szu.xclen, addr_apti, rhs_ti, ri2, 
     ri1 - ri2 + 1, ri1);
  }
 else
  {
   if (pselwid == np->nwid) 
    {
     __gen_st_val(np, addr_apti, rhs_ti);
     return;
    }
   else if (ri1 == ri2) 
    {
     __gen_st_bsel(np->srep, addr_apti, rhs_ti, ri1);
     return;
    }

   __gen_st_psel(np->srep, addr_apti, rhs_ti, ri2, ri1 - ri2 + 1);
  }
}

/*
 * assign to a lhs psel with indexed variable +: or -:
 * if r1_ti is != -1 then the first range is already known (non-blocking)
 * no need to recompute
 */
static void gen_assgn_to_index_width_psel(struct expr_t *lhsx, int32 rhs_ti,
 int32 r1_ti, int32 arrel_ti)
{
 int32 rng1_ti, rng2_ti, t1_ti, t2_ti, t3_ti, t4_ti, t5_ti, numbits_ti;
 int32 rhs_bpti, psel_ti, psel_bpti, addr_apti, mask_ti, bytsiz;
 int32 save_idp_ti, is_2state, srtyp;
 word32 ri2;
 struct bblk_t *chgstore_bbp, *done_bbp;
 struct expr_t *idndp;
 struct net_t *np;
 struct gref_t *grp;
 struct mod_t *targ_mdp;

 idndp = lhsx->lu.x;
 save_idp_ti = -1;
 if (idndp->optyp == ID)
  {
   np = idndp->lu.sy->el.enp;
   grp = NULL;
  }
 else if (idndp->optyp == GLBREF) 
  {
   /* AIV 01/31/06 - if pushed to xmr don't need global ref */
   np = idndp->lu.sy->el.enp;
   grp = idndp->ru.grp;
  }
 else { grp = NULL; np = NULL; __case_terr(__FILE__, __LINE__); }

 if (np->srep == SR_ARRAY)
  {
   srtyp = __get_array_srep_type(np); 
  }
 else if (np->srep == SR_BIT2S) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;

 is_2state = (srtyp == SR_BIT2S);


 /* for end of array pass the element to assign to not the net addr */
 if (arrel_ti == -1)
  {
   addr_apti = __ldvar_addr(np, grp);
   /* AIV 10/10/05 - forgot the needed conversion */
   rhs_ti = __gen_cnvt_srep_ifneeded(rhs_ti, srtyp, lhsx->szu.xclen, 
     np->n_signed, FALSE, FALSE);
  }
 else addr_apti = arrel_ti;

//AIV PSEL - strength
 /* should be no strength because decl constant psel are treated as regular */
 /* constant psel */
 /* DBG remove -- */
 if (np->srep != SR_VEC && np->srep != SR_BIT2S && np->srep != SR_PNUM && 
     np->srep != SR_ARRAY) 
   __misc_terr(__FILE__, __LINE__);
 /* ---- */

 done_bbp = __alloc_bblk(FALSE);

 numbits_ti = get_indexed_psel_range(&rng1_ti, &rng2_ti, &ri2, -1, lhsx, 
  np, done_bbp, r1_ti);

 if (__net_chg_nd_store(np, -1, -1))
  {
   /* AIV 05/17/10 - this was always wrong for XMR - never has changing */
   /* to xmr idp area - need to change idp reg and restore */
   if (grp != NULL)
    {
     save_idp_ti = __gen_ld_xmr_idp(grp);
     /* AIV 01/09/06 - only need to push the instance module */
     targ_mdp = grp->targmdp; 
     __push_wrkitstk(targ_mdp, 0);
    }


   /* get psel of the net for comparison */
   psel_ti = __gen_tn(srtyp, lhsx->szu.xclen);
 
   /* AIV 05/31/09 - need to init wide case to 0 - only need to do this */
   /* for the wide case because movl's will init word case but not each */
   /* word of the wide psel */
   if (lhsx->szu.xclen > WBITS)
    {
     if (is_2state)
      {
       bytsiz = wlen_(lhsx->szu.xclen)*WRDBYTES;
      }
     else bytsiz = 2*wlen_(lhsx->szu.xclen)*WRDBYTES;
     __emit_store_cint(psel_ti, 0, bytsiz);
    }

   /* AIV 09/11/08 - operands for result/addr were wrong here */
   gen_rhs_iw_psel(addr_apti, psel_ti, rng2_ti, numbits_ti, np->nwid, 
     lhsx->szu.xclen, srtyp);

   chgstore_bbp = __alloc_bblk(FALSE);

   /* narrow case just do xor and or and only one compare */
   rhs_bpti = -1;
   if (ri2 <= WBITS)
    {
     /* AIV 09/11/08 - need to mask rhs because value on rhs could be trim */
     /* AIV 10/16/08 - now word aligned no reason to mult bytes any more */
     mask_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, numbits_ti, 
      NLO_MASKTAB);

     t4_ti = __emit_bin_bitand(WBITS, mask_ti, rhs_ti);
     if (!is_2state)
      {
       psel_bpti = __get_bpti(psel_ti);

       t1_ti = __emit_bin_bitxor(WBITS, t4_ti, psel_ti);
       rhs_bpti = __get_bpti(rhs_ti);
       t5_ti = __emit_bin_bitand(WBITS, mask_ti, rhs_bpti);
       t2_ti = __emit_bin_bitxor(WBITS, t5_ti, psel_bpti);
       t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
       __emit_jmp_0(done_bbp, chgstore_bbp, t3_ti);
      }
     else __emit_jmp_eq(done_bbp, chgstore_bbp, t4_ti, psel_ti);
    }
   else
    {
     /* AIV 09/11/08 - need to mask rhs because value on rhs could be trim */
     rhs_bpti = __get_bpti(rhs_ti);
     __emit_jmp_eq_ab_wide_varmask(done_bbp, chgstore_bbp, rhs_ti, psel_ti, 
       numbits_ti);
    }
   __start_bblk(chgstore_bbp);
   gen_st_indexed_width_psel(addr_apti, rhs_ti, rhs_bpti, rng2_ti, numbits_ti, 
    np->nwid, srtyp);
   __gen_record_const_nchg(np, -1, -1, done_bbp);
   __emit_jmp(done_bbp);

   __start_bblk(done_bbp);
   /* AIV 05/17/10 - if XMR restore idp area */
   if (grp != NULL) 
    {
     __gen_restore_idp(save_idp_ti);
     __pop_wrkitstk();
    }
  }
 else
  {
   /* no record just do regular psel */
   if (is_2state) rhs_bpti = -1;
   else rhs_bpti = __get_bpti(rhs_ti);
   gen_st_indexed_width_psel(addr_apti, rhs_ti, rhs_bpti, rng2_ti, numbits_ti,
     np->nwid, srtyp);
   __start_bblk(done_bbp);
  }
}

/*
 * store a rhs indexed width psel +: and -:
 * where bitl_ti and numbits_ti are variable
 */
static void gen_st_indexed_width_psel(int32 addr_apti, int32 rhs_ti, 
 int32 rhs_bpti, int32 bitl_ti, int32 numbits_ti, int32 nwid, int32 srtyp)
{
 int32 addr_bpti, mask_ti, t1_ti, t2_ti, t3_ti, t4_ti, t5_ti;
 int32 av_ti, bv_ti;
 
 /* inline the known narrow case */
 if (nwid <= WBITS)
  {
   /* mask = __masktab[numbits] << dbi; */
   /* *dwp = (*dwp & ~mask) | ((*swp << dbi) & mask); */
   /* AIV 10/16/08 - now word aligned no reason to mult bytes any more */
   t1_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, numbits_ti, NLO_MASKTAB);

   mask_ti = __emit_shiftl(WBITS, bitl_ti, t1_ti);
   /* ((*swp << dbi) & mask); */
   t2_ti = __emit_shiftl(WBITS, bitl_ti, rhs_ti);
   t3_ti = __emit_mask_and(mask_ti, t2_ti);

   /* (*dwp & ~mask) */
   t4_ti = __emit_bitnot(WBITS, mask_ti);
   t5_ti = __emit_mask_and(addr_apti, t4_ti);
   av_ti = __emit_bin_bitor(WBITS, t3_ti, t5_ti);
   __emit_copy(WRDBYTES, av_ti, addr_apti);
   if (srtyp == SR_BIT2S) return;

   /* ((*sbwp << dbi) & mask); */
   t2_ti = __emit_shiftl(WBITS, bitl_ti, rhs_bpti);
   t3_ti = __emit_mask_and(mask_ti, t2_ti);

   addr_bpti = __get_bpti(addr_apti);
   t5_ti = __emit_mask_and(addr_bpti, t4_ti);
   bv_ti = __emit_bin_bitor(WBITS, t3_ti, t5_ti);
   __emit_copy(WRDBYTES, bv_ti, addr_bpti);
  }
 else
  {
   __emit_st_psel(addr_apti, rhs_ti, bitl_ti, numbits_ti);
   if (srtyp == SR_BIT2S) return;
   addr_bpti = __get_bpti(addr_apti);
   __emit_st_psel(addr_bpti, rhs_bpti, bitl_ti, numbits_ti);
  }
}


/*
 * gen lhs psel chg store insns - complex because must compare and skip
 * if same
 * first compares a part if they are the same compare b part 
 */
extern void __gen_chg_lhspsel(struct net_t *np, int32 twid, 
 int32 addr_apti, int32 rhs_ti, int32 lowbi, int32 numbits, int32 ri1)
{
 int32 rhs_bpti, oval_apti, obval_ti;
 int32 nd_bpart_psel, bofs, is_2state;
 struct bblk_t *chgstore_bbp, *testb_bbp, *skip_bbp;

 /* part select fits in one word */
 if (numbits <= WBITS) 
  {
   __gen_chg_word_lhspsel(np, addr_apti, rhs_ti, lowbi, numbits, ri1); 
   return;
  }
 
 chgstore_bbp = __alloc_bblk(FALSE); 
 skip_bbp = __alloc_bblk(FALSE);

 /* SJM 11/02/04 - NOTICE - for scalar ttyp will be word so this will */
 /* load scalar correctly as 1 bit of word */

 is_2state = (np->srep == SR_BIT2S);
 nd_bpart_psel = FALSE;
 bofs = get_bofs_(lowbi);
 oval_apti = __gen_tn(np->srep, twid);
 if (bofs == 0)
  {
   /* AIV 11/17/05 - notice now passing lowbi so compute word ofset in this */
   gen_wordalign_rhs_psel(np->srep, oval_apti, addr_apti, lowbi, numbits);
  }
 else
  {
   nd_bpart_psel = TRUE;
   /* load the unaligned apart psel into oval_apti */
   gen_ld_unaligned_rhs_psel(oval_apti, addr_apti, lowbi, numbits, TRUE, 
    np->srep); 
  }

 if (!is_2state)
  {
   testb_bbp = __alloc_bblk(FALSE);
   __emit_jmp_eq(testb_bbp, chgstore_bbp, rhs_ti, oval_apti);

   __start_bblk(testb_bbp);

   if (nd_bpart_psel)
    {
     /* load the unaligned b part psel into oval_apti */
     gen_ld_unaligned_rhs_psel(oval_apti, addr_apti, lowbi, numbits, FALSE,
      np->srep); 
    }
   obval_ti = __get_bpti(oval_apti);

   rhs_bpti = __get_bpti(rhs_ti);
   __emit_jmp_eq(skip_bbp, chgstore_bbp, rhs_bpti, obval_ti);
  }
 else __emit_jmp_eq(skip_bbp, chgstore_bbp, rhs_ti, oval_apti);

 __start_bblk(chgstore_bbp);

 __gen_st_psel(np->srep, addr_apti, rhs_ti, lowbi, numbits);

 __gen_record_const_nchg(np, ri1, lowbi, skip_bbp);

 __start_bblk(skip_bbp);
}

/*
 * change store were psel fits into one word
 * like above but just xors a and b parts instead of comparing both
 * only does one jmp
 */
extern void __gen_chg_word_lhspsel(struct net_t *np, int32 addr_apti,
 int32 rhs_ti, int32 lowbi, int32 numbits, int32 ri1)
{
 int32 rhs_bpti, oval_apti, oval_bpti;
 int32 t1_ti, t2_ti, t3_ti, is_2state;
 struct bblk_t *chgstore_bbp, *skip_bbp;

 chgstore_bbp = __alloc_bblk(FALSE); 
 skip_bbp = __alloc_bblk(FALSE);

 /* part select fits in one word */
 oval_apti = gen_in1wrd_rhs_psel(np->srep, addr_apti, lowbi, numbits);
 is_2state = (np->srep == SR_BIT2S);
 if (!is_2state)
  {
   oval_bpti = __get_bpti(oval_apti);
   rhs_bpti = __get_bpti(rhs_ti);

   t1_ti = __emit_bin_bitxor(WBITS, oval_apti, rhs_ti);
   /* AIV 12/27/06 - this was or has to be xor to check for change of bpart */
   t2_ti = __emit_bin_bitxor(WBITS, oval_bpti, rhs_bpti);

   t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);

   __emit_jmp_0(skip_bbp, chgstore_bbp, t3_ti);
  }
 else __emit_jmp_eq(skip_bbp, chgstore_bbp, oval_apti, rhs_ti);

 __start_bblk(chgstore_bbp);

 gen_in1wrd_st_psel(np->srep, addr_apti, rhs_ti, lowbi, numbits, TRUE);
 if (!is_2state) 
  {
   gen_in1wrd_st_psel(np->srep, addr_apti, rhs_bpti, lowbi, numbits, FALSE);
  }

 __gen_record_const_nchg(np, ri1, lowbi, skip_bbp);

 __start_bblk(skip_bbp);
}

/*
 * return T if size same (widening in same no. of words also same)
 */
extern int32 __same_size(int32 lhswid, int32 rhswid)
{
 int32 lwlen, rwlen;
 
 if (lhswid == rhswid) return(TRUE);
 lwlen = wlen_(lhswid);
 rwlen = wlen_(rhswid);
 if (lwlen == rwlen && rhswid < lhswid) return(TRUE);
 return(FALSE);
}

/*
 * gen vm insns for lhs concat - normal case used by in sourc proc assign
 *
 * now wrapper that emit insn to eval (describe is leaf) rhs expr
 */
static void gen_lhs_concat(struct expr_t *rhsx, struct expr_t **lhsxtab,
 int32 lhsnels, int32 lhswid)
{
 int32 rhs_ti;

 /* AIV 11/10/09 - want a vector here */
 rhs_ti = __gen_expr_eval(rhsx, WANT_A_VEC);
 gen_lhs_concat2(rhs_ti, lhsxtab, lhsnels, lhswid);
}

/*
 * gen vm insns for lhs concat - variant for when know rhs evaled
 * into natural rhs width tmp 
 *
 * called directly for rhs delay controls but called through wrapper
 * for normal procedural lhs proc assign
 *
 * loop gens rhs select then lhs assign for each
 *
 * eval rhs into reg, then for each lhs el, select range and assign
 * algorithm decomposes { lx1, lx2, .. } = Rx1 into lx?= Rx1[?:?], etc. 
 *
 * handles size changes - if rhs too wide just ignored, if too narrow
 * adjust high one and then uses set0 for rest
 *
 * LOOKATME - changed to convert rhs so matches lhs concat width exactly 
 * for widening could assign 0's and not copy but think this better
 *
 * SJM 08/10/02 - now for rhs NUMBER where can use literal assigns
 * (lhs ID/XMR not wider than 64 bits) do not need rhs copy
 */
static void gen_lhs_concat2(int32 rhs_ti, struct expr_t **lhsxtab,
 int32 lhsnels, int32 lhswid)
{
 int32 lxi, srtyp, lhs_srep, nbytes;
 int32 rhs2_ti, range_rhs_ti, catxlen, last_lowbi, bi, is_2state;
 struct expr_t *catlhsx;

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

 /* SJM 08/16/05 - now mimic interpreter high to low so need last low bit */
 last_lowbi = lhswid;
 for (lxi = lhsnels - 1; lxi >= 0; lxi--)
  {
   catlhsx = lhsxtab[lxi];
   catxlen = catlhsx->szu.xclen;
   bi = last_lowbi - catxlen;
   range_rhs_ti = gen_rhs_concat_range(rhs2_ti, bi, catxlen, srtyp);

   /* AIV LOOKATME - if width is known one - rhs is going to be scalar */
   /* can produce better assign code ????? */
   lhs_srep = __get_lhs_srep(catlhsx, &nbytes);
   /* now may have to change to SR_VEC or SR_BIT2S */
   range_rhs_ti = __gen_cnvt_srep_ifneeded(range_rhs_ti, lhs_srep, 
    catxlen, catlhsx->has_sign, catlhsx->is_real, FALSE);
   gen2_proc_assign(catlhsx, range_rhs_ti);
   last_lowbi = bi;
  }
}

/*
 * get a rhs section of a lhs concat 
 */
static int32 gen_rhs_concat_range(int32 rhs_ti, int32 bi, int32 catxlen, 
 int32 srtyp)
{
 int32 t1_apti, twid, bofs;
 int32 rhs_bpti, t1_bpti, cint_ti, wofs, rhs_hghw_apti, rhs_hghw_bpti;

 /* SJM 08/16/05 - now mimic interpreter high to low so need last low bit */
 if (catxlen == 1)
  {
   /* AIV 01/04/07 - 1 bit for a wide bsel was wrong here - was always */
   /* using the low word */
   if (bi < WBITS)
    {
     t1_apti = __gen_tn(srtyp, catxlen);
     /* gen a word space and load a part the 1 bit and b part 1 bit */
     cint_ti = __gen_cint_tn(bi);
     __emit_ld_bsel(rhs_ti, cint_ti, t1_apti);
     if (!__tmp_is_2state(rhs_ti))
      {
       rhs_bpti = __get_bpti(rhs_ti);
       t1_bpti = __get_bpti(t1_apti);
       __emit_ld_bsel(rhs_bpti, cint_ti, t1_bpti);
      }
    }
   else
    {
     /* if bsel is wide need to get the high part of the word */
     /* then do the load bsel */
     wofs = get_wofs_(bi);
     /* high a part */
     rhs_hghw_apti = __con_adradd_insn(srtyp, WBITS, rhs_ti, 
      WRDBYTES*wofs);
     twid = __get_tnwid(rhs_ti);
     /* high b part */
     rhs_hghw_bpti = __con_adradd_insn(srtyp, WBITS, rhs_ti, 
      WRDBYTES*(wlen_(twid) + wofs));
     /* get bi offset and load into tmp */
     bofs = get_bofs_(bi);
     cint_ti = __gen_cint_tn(bofs);
     t1_apti = __gen_tn(srtyp, catxlen);
     __emit_ld_bsel(rhs_hghw_apti, cint_ti, t1_apti);
     if (!__tmp_is_2state(rhs_ti))
      {
       t1_bpti = __get_bpti(t1_apti);
       __emit_ld_bsel(rhs_hghw_bpti, cint_ti, t1_bpti);
      }
    }
  }
 else 
  {
   /* range within lhs is [bi + catxlen - 1:bi] */
   t1_apti = __gen_fradr_rhs_psel(srtyp, rhs_ti, catxlen, bi + catxlen - 1, 
     bi);
  }
 return(t1_apti);
}

/*
 * gen vm insns for rhs concat assign 
 *
 * algorithm decomposes Lx = { rx1, rx2, rx3, .. } into Lx[?:?] = rx1, etc. 
 *
 * handles size mismatches - if rhs too wide ignores some elements and
 * high assign is size change here, if rhs too narrow does set 0 when
 * all rhs exhausted
 * 
 * BEWARE - must not be called for forced/assigned lhs or chg form lhs
 */
static void gen_rhs_assgn_concat(struct expr_t *lhsx,
 struct expr_t **rhsxtab, int32 rhsnels)
{
 int32 rxi;
 int32 bi1, bi2, ri1, ri2, catxlen, t1_ti, bytsiz, blen;
 int32 addr_apti, rhs_ti, rhs2_ti, srtyp;
 struct expr_t *idndp, *catrhsx;
 struct net_t *np;

 /* bit select impossible since only bit so concat removed */
 idndp = NULL;
 np = NULL;
 if (lhsx->optyp == ID) idndp = lhsx;
 else if (lhsx->optyp == PARTSEL) idndp = lhsx->lu.x;
 else if (lhsx->optyp == PARTSEL_NDX_PLUS || lhsx->optyp == PARTSEL_NDX_MINUS) 
  {
   /* AIV 06/16/09 - these should never get to this code */
   __case_terr(__FILE__, __LINE__);   
  }
 else { __case_terr(__FILE__, __LINE__); }

 if (idndp->optyp == ID)
  {
   np = idndp->lu.sy->el.enp;
   addr_apti = __ldvar_addr(np, NULL);
  }
 else if (idndp->optyp == GLBREF)
  {
   np = idndp->lu.sy->el.enp;
   addr_apti = __ldvar_addr(np, idndp->ru.grp);
  }
 else { addr_apti = -1; __case_terr(__FILE__, __LINE__); } 

 for (bi2 = 0, rxi = 0; rxi < rhsnels; rxi++)
  {
   catrhsx = rhsxtab[rxi];
   catxlen = catrhsx->szu.xclen;
   /* range within rhs is [bi1:bi2] */
   bi1 = bi2 + catxlen - 1;
   /* SJM 04/05/02 when lhs exhausted must truncate - gen no more */
   /* case 1: exact match and done with no more to do */
   if (bi2 >= lhsx->szu.xclen) break;

   /* case 2: high bi1 over - adjust so high is lhs width - 1 */
   if (bi1 >= lhsx->szu.xclen) 
    {
     /* DBG remove -- 
     __my_fprintf(stdout, "*** truncating from [%d:%d] to [%d:%d]\n",
      bi1, bi2, lhsx->szu.xclen - 1, bi2);
     ---  */
     bi1 = lhsx->szu.xclen - 1;
    }

   /* if lhs is part select correct so range to match rhs inside psel */
   if (lhsx->optyp == PARTSEL)
    {
     /* adjust be adding low bit of psel to both */
     ri1 = bi1 + __contab[lhsx->ru.x->ru.x->ru.xvi];
     ri2 = bi2 + __contab[lhsx->ru.x->ru.x->ru.xvi];
    }
   else { ri1 = bi1; ri2 = bi2; }

   /* AIV 11/10/09 - want a vector here */
   rhs_ti = __gen_expr_eval(catrhsx, WANT_A_VEC);
   /* must convert rhs if needed */
   blen = ri1 - ri2 + 1;

   if (blen == 1) 
    {
     /* AIV 10/27/09 - if scalar now handled in __gen_st_bsel */
     srtyp = __tntab[rhs_ti].srtyp;
     if (srtyp != SR_SCAL && srtyp != SR_SCAL2S)
      {
       rhs2_ti = __gen_cnvt_srep_ifneeded(rhs_ti, SR_VEC, blen, FALSE,
         FALSE, FALSE);
      }
     else rhs2_ti = rhs_ti;
     /* SJM 12/16/05 - if know one bit - lhs into tmp name bsel better */ 
     __gen_st_bsel(np->srep, addr_apti, rhs2_ti, ri1);
    }
   else
    {
     /* AIV 01/25/12 - rare case that rhs is 2-state value may need to */
     /* convert to 4-state for example r = {$random(seed2)}; - has */
     /* no b part where one is assumed */
     rhs2_ti = __gen_cnvt_srep_ifneeded(rhs_ti, SR_VEC, blen, FALSE,
       FALSE, FALSE);
     __gen_st_psel(np->srep, addr_apti, rhs2_ti, ri2, blen);
    }

   /* end of last rhs cat el narrower than lhs expr - need 1 more set 0 */
   /* bi1 is high bit of previous element */
   if (rxi == rhsnels - 1 && (bi1 + 1) < lhsx->szu.xclen)
    {
     bi1++;

     if (lhsx->optyp == PARTSEL) 
      {
       ri1 = lhsx->szu.xclen - 1;
       ri2 = __contab[lhsx->ru.x->ru.x->ru.xvi] + bi2;
      }
     else { ri1 = lhsx->szu.xclen - 1; ri2 = bi1; }

     /* t1 just a part used (twice) */
     blen = ri1 - ri2 + 1;
     t1_ti = __gen_tn(SR_VEC, blen);

     /* AIV LOOKATME - this does zeros more than needed */
     /* could just zero a part and use it but __gen st psel uses the b part */
     /* actually could lower to use literal zero of psel but constant */
     /* folding should correct this anyways */
     bytsiz = 2*wlen_(blen)*WRDBYTES;
     __emit_store_cint(t1_ti, 0, bytsiz);

     __gen_st_psel(np->srep, addr_apti, t1_ti, ri2, blen);
     return;
    } 
   bi2 = bi1 + 1;
  }
}

/*
 * gen cat to cat case but only if exact match
 * if not exact match returns F
 * if matches gen insns for all and return T
 *
 * know at least 2 elements in each list to get here
 * FIXME - should also do better partial matches - maybe using dynamic
 * programming - see if makes improvements
 *
 * since concat dcomposed can reuse tmps here after each assign
 */
static int32 gen_cat_to_cat_match(struct expr_t *lhsx,
 struct expr_t **lhsxtab, int32 lels, struct expr_t *rhsx,
 struct expr_t **rhsxtab, int32 rels)
{
 int32 lxi;
 int32 lhsbi, rhs_ti, bytsiz, lhs_srep, nbytes;
 struct expr_t *catlhsx, *catrhsx;

 /* through first time to determine if exact match - no cga build yet */
 for (lxi = 0, lhsbi = 0;; lxi++)
  {
   catlhsx = lhsxtab[lxi];
   catrhsx = rhsxtab[lxi];
   /* if this one does not match width exactly - give up */
   if (catlhsx->szu.xclen != catrhsx->szu.xclen) return(FALSE);

   /* this is lhs start bi for next one */
   lhsbi += catlhsx->szu.xclen;

   /* see if all done */
   /* case 1: perfect match and sizes same  - done */
   /* this is common case - all concat elems same width (usually 1) and */
   /* port/conta/proca width same */
   if (lhsbi == lhsx->szu.xclen && lhsbi == rhsx->szu.xclen) break;

   /* case 2: narrowing off high end of lhs - just discard unused rhs */
   /* i.e. no need to eval */
   if (lhsbi == lhsx->szu.xclen) break;

   /* case 3: widening - need assign of special 0 cga to high end of lhsx */
   if (lhsbi == rhsx->szu.xclen) break;
  }

 /* if lhs element (symbol) used anywhere on rhs treat as non exact match */
 /* LOOKATME - this is too pessimistic - could chk rng, xmr inst and order */
 if (cat_need_rhs_eval(lhsxtab, lels, rhsxtab, rels)) return(FALSE); 

 /* now generate the insn addr assigns */
 for (lxi = 0, lhsbi = 0;; lxi++)
  {
   catlhsx = lhsxtab[lxi];
   /* must use oposite rhs to match interpreter */
   /* AIV 05/10/06 - this can't be right look above at the matching of the */
   /* sizes lxi is used as index for both why was this ever put in ????? */
   /* catrhsx = rhsxtab[(rels - 1) - lxi]; */
   /* know sizes match if gets here */
   catrhsx = rhsxtab[lxi];
   /* this is lhs start bi for next one */
   lhsbi += catlhsx->szu.xclen;

   /* DBG remove -- */
   if (catlhsx->szu.xclen != catrhsx->szu.xclen)
    __misc_terr(__FILE__, __LINE__);
   /* -- */
    
   /* AIV 11/10/09 - want a vector here */
   rhs_ti = __gen_expr_eval(catrhsx, WANT_A_VEC);
   lhs_srep = __get_lhs_srep(catlhsx, &nbytes);
   /* may have to convert between a 2-state and 4-state */
   rhs_ti = __gen_cnvt_srep_ifneeded(rhs_ti, lhs_srep, catlhsx->szu.xclen,
    catlhsx->has_sign, catlhsx->is_real, FALSE);
   gen2_proc_assign(catlhsx, rhs_ti);

   /* see if all done */
   /* case 1: perfect match and sizes same */
   if (lhsbi == lhsx->szu.xclen && lhsbi == rhsx->szu.xclen) break;
    
   /* case 2: widening - assign dummy 32 bit 0 expr cga to high end of lhs */
   /* know at least one more lhs to assign 0 to */
   if (lhsbi == rhsx->szu.xclen) 
    {
     /* need to assign 0 assign for every remaining lhs - know at least 1 */
     for (;;)
      {
       catlhsx = lhsxtab[++lxi];
       lhsbi += catlhsx->szu.xclen;

       /* rhs here is right width sr vec both a/b part 0 */
       lhs_srep = __get_lhs_srep(catlhsx, &nbytes);
       rhs_ti = __gen_tn(lhs_srep, catlhsx->szu.xclen);

       if (lhs_srep == SR_BIT2S)
        {
         bytsiz = wlen_(catlhsx->szu.xclen)*WRDBYTES;
        }
       else bytsiz = 2*wlen_(catlhsx->szu.xclen)*WRDBYTES;
       __emit_store_cint(rhs_ti, 0, bytsiz);

       gen2_proc_assign(catlhsx, rhs_ti);
       if (lhsbi == lhsx->szu.xclen) return(TRUE);
      } 
     break;
    }
  }
 return(TRUE);
}

/*
 * return T if any rhs concat element appears on lhs
 * only called if exact match but if var used on rhs can't decompose
 *
 * LOOKATME - for now just comparing symbols could also check ranges and XMRs
 * and even see if sequencing would still allow separation
 */
static int32 cat_need_rhs_eval(struct expr_t **lhsxtab, int32 lels,
 struct expr_t **rhsxtab, int32 rels) 
{
 int32 rxi, lxi;
 struct sy_t *lsyp, *rsyp;
 struct expr_t *catrhsx, *catlhsx;

 /* can find last by seeing if lx tab element rhs is nil */
 for (rxi = 0; rxi < rels; rxi++)
  {
   catrhsx = rhsxtab[rxi];
   /* AIV 01/18/06 - this was continue when it needs to return false */ 
   if ((rsyp = __iget_lval_sym(catrhsx)) == NULL) return(TRUE);

   for (lxi = 0; lxi < lels; lxi++)
    {
     catlhsx = lhsxtab[lxi];

     /* lhs concat el must be lval */
     if ((lsyp = __iget_lval_sym(catlhsx)) == NULL) 
      __misc_terr(__FILE__, __LINE__);
     if (lsyp == rsyp) return(TRUE);
    }
  }
 return(FALSE);
}

/*
 * get expr symbol - if not lvalue returns nil 
 */
extern struct sy_t *__iget_lval_sym(struct expr_t *xp)
{
 switch (xp->optyp) {
  case ID: case GLBREF: return(xp->lu.sy);
  case LSB: return(xp->lu.x->lu.sy);
  case PARTSEL: 
  case PARTSEL_NDX_PLUS: 
  case PARTSEL_NDX_MINUS: 
   return(xp->lu.x->lu.sy);
  default: break;
 }
 return(NULL);
}

/*
 * ROUTINES TO GEN V INSNS FOR MISC PROCEDURAL STMTS
 */

/*
 * gen insns to eval and schedule non blocking rhs assign 
 *
 * for non delay non blocking rhs proc assign where there is no dctp
 */
static void gen_nblkrhs_proca(struct st_t *stp, struct expr_t *rhsx,
 int32 accum_ti)
{
 int32 rhs_ti, tmp_ti, nd_sign, ctevp_ti, want_a_vec;
 int32 nbytes, store_nb_val_ti, lhs_srep, stmt_ent_ti;
 struct expr_t *lhsx;
 struct ctev_t *ctevp;

 /* AIV 01/19/09 - need to mark if design has non-blocking events */
 __design_has_nb_events = TRUE; 

 lhsx = stp->st.spra.lhsx;
 ctevp = stp->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 
 ctevp_ti = __gen_ctevp_adr_tn(ctevp);

 /* if rhs is a constant can just do a no delay non-blocking assign */
 /* AIV FIXME - could handle the rhs const in var lhs ndx case - seperate */
 /* skipping this case for now */
 if (!__lhsexpr_var_ndx(lhsx) && __cvc_is_const_expr(rhsx))
  {
   stmt_ent_ti = __gen_proc_enter_nb_adr_tn(stp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

   /* AIV 03/09/09 - better to inline this simple routine */
   /* __emit_bld_nb_nodelay_tev(ctevp_ti); */
   gen_nb_nodelay_tev(ctevp_ti);
   add_non_blocking_stmt(stp, FALSE, TRUE, -1, TRUE, FALSE);
   return;
  }

 /* SJM 10/18/05 - simulates eval assign rhs expr - use rhs signedness */
 nd_sign = rhsx->has_sign;

 /* AIV 01/17/07 - know pound 0 events so wrappers schedules as well */
 /* if lhs is variable index - must copy expr */
 /* AIV 04/13/07 - now can be scal as well not always convert to vector */
 lhs_srep = __get_lhs_srep(lhsx, &nbytes);
 if (__lhsexpr_var_ndx(lhsx)) 
  {
   /* AIV 11/10/09 - want a vector here */
   /* AIV 08/17/10 - lhs var index can now be a scalar array value */
   want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : -1;
   if (accum_ti == -1) tmp_ti = __gen_expr_eval(rhsx, want_a_vec);
   else tmp_ti = accum_ti;
   rhs_ti = __gen_cnvt_srep_ifneeded(tmp_ti, lhs_srep, lhsx->szu.xclen,
    nd_sign, lhsx->is_real, FALSE);
   gen_nb_lhs_varndx(stp, lhsx, ctevp, rhs_ti, TRUE, FALSE, lhs_srep);
  }
 else
  { 
   /* AIV 11/10/09 - want a vector here if is vectore */
   want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : -1;
   if (accum_ti == -1) tmp_ti = __gen_expr_eval(rhsx, want_a_vec);
   else tmp_ti = accum_ti;
   rhs_ti = __gen_cnvt_srep_ifneeded(tmp_ti, lhs_srep, lhsx->szu.xclen,
    nd_sign, lhsx->is_real, FALSE);

   store_nb_val_ti = __gen_nonblocking_bp_tn(stp, lhs_srep, rhsx->is_real);
   /* copy the value into static memory to be copied later */
   __emit_copy(nbytes, rhs_ti, store_nb_val_ti);

   add_non_blocking_stmt(stp, TRUE, FALSE, lhs_srep, TRUE, FALSE);

   /* assumes schedule for now (sim time) that is correct in this case */
   stmt_ent_ti = __gen_proc_enter_nb_adr_tn(stp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

   /* AIV 03/09/09 - better to inline this simple routine */
   /* __emit_bld_nb_nodelay_tev(ctevp_ti); */
   gen_nb_nodelay_tev(ctevp_ti);
  }
}

/*
 * add a simple non-blocking event with no delay
 *
 * no delay - regular r <= b statement
 *
 * if (tevp->trigger) return;
 * tevp->trigger = TRUE;
 * __nb_te_endp->tenxtp = tevp;
 * __nb_te_endp = tevp;
 */
static void gen_nb_nodelay_tev(int32 ctevp_ti)
{
 int32 tevp_reg_ti, trigger_ti, nb_end_ti;
 size_t offset;
 struct tev_t *tevp;
 struct bblk_t *add_bbp, *already_added_bbp;

 add_bbp = __alloc_bblk(FALSE);
 already_added_bbp = __alloc_bblk(FALSE);
 /* if there is more than one instance load the reg from memory into a reg */
 /* this is an address for only one instance so better code with less regs */
 /* for only on instance case */
 // AIVNB - better to use reg???
 /*
 if (__inst_mod->flatinum > 1)
  {
   tevp_reg_ti = __move_insn(TN_ADR, I_MOVL, AM_REG, ctevp_ti);
  }
 else tevp_reg_ti = ctevp_ti;
 */
 tevp_reg_ti = __move_insn(TN_ADR, I_MOVL, AM_REG, ctevp_ti);

 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 trigger_ti = __move_insn(TN_VAL, I_MOVL, AM_NDXREG_DISP, tevp_reg_ti, offset);
 __emit_jmp_0(add_bbp, already_added_bbp, trigger_ti);
 __start_bblk(add_bbp);


 /* __nb_te_endp->tenxtp = tevp; */
 offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
 nb_end_ti = __move_insn(TN_ADR, I_MOVL, AM_NLO, NLO_NB_TE_ENDP);
 __st_insn(I_STOREL, AM_REG, tevp_reg_ti, AM_NDXREG_DISP, nb_end_ti, offset);

 /* __nb_te_endp = tevp; */
 __st_insn(I_STOREL, AM_REG, tevp_reg_ti, AM_NLO, NLO_NB_TE_ENDP);
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 /* AIV 01/05/10 - don't set the value equal to 1 better to set to address */
 /* which is known not to be 0 - which will be in a register */
 /* AIV BEWARE - this may look like a bad memory since it is not 0/1 */
 __st_insn(I_STOREL, AM_REG, nb_end_ti, AM_NDXREG_DISP, tevp_reg_ti, offset);
 __emit_jmp(already_added_bbp);
 __start_bblk(already_added_bbp);
}

/*
 * add a list of non-blocking stmts which are lowered as their own flowgraph
 * later to do the actual assign
 *
 * static_mem - flag indicates memory is not needed to alloc for every
 * event alloc - it only assigns to the one static mem in the *.s file
 *
 * if rhs_const - flag indicates the rhsx is constant
 * AIV LOOKATME - rhs_const flag can just be found from the statment
 * leaving for now - easier to understand
 */
static void add_non_blocking_stmt(struct st_t *stp, int32 static_mem, 
 int32 rhs_const, int32 lhs_srep, int32 is_processing_pnd0s, int32 fg_free)
{
 struct nb_stmt_lst_t *nbalstp;

 /* AIV 03/03/09 - if doing merged always block fg - this is a duplicate */
 /* so do not add to the list twice */
 if (__gening_mdc) return;

#ifdef __XPROP__
 /* if xprop nb can already be added to list - only do once */
 if (__xprop)
  {
   if (stp->nb_xprop_in_list) return;
  }
 /* DBG remove -- */
 if (stp->nb_xprop_in_list) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 stp->nb_xprop_in_list = TRUE;
#endif

 /* AIV 02/07/06 - make a list of non-blocking assign stmt to later */
 /* produce flow graph to do the actual assign */
 /* LOOKATME - handle the variable index case as well ??? */ 
 nbalstp = (struct nb_stmt_lst_t *) __my_malloc(sizeof(struct nb_stmt_lst_t));
 nbalstp->stp = stp;
 nbalstp->stnxt = NULL;
 nbalstp->has_static_mem = static_mem;
 nbalstp->is_scalar = (lhs_srep == SR_SCAL || lhs_srep == SR_SCAL2S);
 nbalstp->has_rhs_const = rhs_const;
 nbalstp->processing_pnd0s = is_processing_pnd0s;
 /* need to record if fg could have possible alloc nb events create free fg */
 nbalstp->need_free_fg = fg_free;
 if (__nb_stmt_hd == NULL) __nb_stmt_hd = nbalstp;
 else __nb_stmt_cur->stnxt = nbalstp;
 __nb_stmt_cur = nbalstp; 
}
 
/*
 * set the non-blocking fg number in the ctev 
 * these are needed to set the next_enterptr to the free version
 * when generating ctevdat_
 */
static void set_nonblocking_fg_num_to_ctev(struct ctev_t *ctevp, 
 struct st_t *stp)
{
 int32 ndx;

 ndx = stp->st_ndx;
 /* DBG remove -- */
 if (!stp->is_nb_enter) __misc_terr(__FILE__, __LINE__);
 if (ndx < 0 || ndx > __inst_mod->mstnum) __misc_terr(__FILE__, __LINE__);
 /* --- */
 ctevp->nb_fg_num = ndx;
}

/*
 * gen vm insns for after delay elapsed rhs del ctrl assign
 *
 * insns never exec directory - execed when delay ctrl execed
 * AIV 05/15/07 - changed to use static memory - similar to non-blocking
 */
static void gen_rhs_dctl_proca(struct st_t *stp)
{
 int32 lxi, nbytes;
 int32 rhs_ti, lhsnels, lhs_srep, blen, ctab_ndx;
 struct expr_t *lhsx, *rhsx;
 struct expr_t *catndp, **lhsxtab;
 struct xstk_t *xsp;

 lhsx = stp->st.spra.lhsx;
 rhsx = stp->st.spra.rhsx;

 blen = lhsx->szu.xclen;
 /* if rhs is constant just eval rhs and assign constant value */
 /* the rhs constant value is never save to memory */
 /* get the lhs srep type - can now be scalar storage as well */
 lhs_srep = __get_lhs_srep(lhsx, &nbytes);
 if (__cvc_is_const_expr(rhsx)) 
  {
   xsp = __eval_assign_rhsexpr(rhsx, lhsx);
   ctab_ndx = __allocfill_cval_new(xsp->ap, xsp->bp, wlen_(blen));
   /* build a new right width constant */

   /* AIV 10/14/10 - this nees to pass the rhsx->is_real flag */
   rhs_ti = __gen_contab_tn(ctab_ndx, blen, FALSE, rhsx->has_sign, 
     rhsx->is_real, lhs_srep);
   __pop_xstk();
  }
 else
  {
   /* load the comlab save value */
   rhs_ti = __gen_pd_rhsbp_tn(stp, lhs_srep, rhsx->is_real);
  }

 /* SJM 11/27/02 - fails if lhsx concat - now call proc lhs gen if so */
 /* now need normal procedural assign - then reset tmp tab when done */
 /* if one element concat can treat as simple lhs expr */
 if (lhsx->optyp == LCB && lhsx->ru.x->ru.x != NULL)
  {
   /* build the lhs expr cat element tab */
   lhsnels = __cnt_cat_size(lhsx);
   lhsxtab = (struct expr_t **)
    __my_malloc(lhsnels*sizeof(struct expr_t *));
   lxi = lhsnels - 1;
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x, lxi--)
    { lhsxtab[lxi] = catndp->lu.x; }

   gen_lhs_concat2(rhs_ti, lhsxtab, lhsnels, blen);

   /* and when done must free it */ 
   if (lhsxtab != NULL)
    __my_free(lhsxtab, lhsnels*sizeof(struct expr_t *));
  }
 else gen2_proc_assign(lhsx, rhs_ti);
}

/*
 * gen vm insns for if statement
 */
static void gen_if_stmt(struct st_t *stp)
{
 int32 if_apti, bool_ti, t1_ti, if_bpti, blen, cint_ti;
 int32 axvi, bxvi, srtyp;
 word32 aval, bval, tmp;
 struct bblk_t *t_bbp, *f_bbp, *after_bbp;
 struct net_t *np;
 struct st_t *else_stp;
 struct expr_t *condxp;
 struct if_t *ifinfo;

 ifinfo = &(stp->st.sif);

 /* AIV 12/08/06 - empty block don't need to evaluate */
 /* AIV FIXME - need to check for these in other stmtms while/for/etc */
 /* either only has an empty if or both all none don't produce any code */
 stp = ifinfo->thenst;
 if (stp->stmttyp == S_STNONE && 
     (ifinfo->elsest == NULL || ifinfo->elsest->stmttyp == S_STNONE)) 
  {
    return;
  }

 else_stp = ifinfo->elsest;
 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);


 /* first eval condition expr */
 condxp = ifinfo->condx;
 /* AIV 12/31/10 - handle the if (!scalnet) && if (~scalnet) as a special */ 
 /* case.  It is common usage only need to compare value to 0 and not */
 /* do the actual not op */
 /* not or bitnot and the lhs is a net */
 f_bbp = NULL;
 if ((condxp->optyp == NOT || condxp->optyp == BITNOT) && 
     condxp->lu.x->optyp == ID)
  {
   np = condxp->lu.x->lu.sy->el.enp;
   /* only handle the scalar case */
   if (np->srep == SR_SCAL || np->srep == SR_SCAL2S)
    {
     /* if value is the net value */
     if_apti = __gen_ld_net_addr(np, NULL);
     t_bbp = __alloc_bblk(FALSE);
     after_bbp = __alloc_bblk(FALSE);

     /* just do a jump 0 with the if stmt */
     if (else_stp != NULL) 
      {
       f_bbp = __alloc_bblk(FALSE);
       __emit_jmp_0(t_bbp, f_bbp, if_apti);
      }
     else __emit_jmp_0(t_bbp, after_bbp, if_apti); 

     /* if block */
     __start_bblk(t_bbp);
     gen_stlst(ifinfo->thenst, TRUE);

     /* else block */
     if (else_stp != NULL)
      {
       __emit_jmp(after_bbp);
       __start_bblk(f_bbp);
       gen_stlst(else_stp, TRUE);
      }
     __start_bblk(after_bbp);
     if (stp->stnxt != NULL) __pop_cc_stmt();
     return;
    }
  }
 if_apti = __gen_expr_eval(ifinfo->condx, -1);
 blen = __get_tnwid(if_apti);

 /* AIV 11/21/06 - handle the constant if case */
 if (__is_constant(if_apti))
  {
   if_bpti = __get_bpti(if_apti);
   /* narrow constant case */
   /* constant real case */
   if (__tntab[if_apti].t_real)
    {
     double d1;

     axvi = __get_con_adradd_xvi(if_apti);
     memcpy(&d1, &(__contab[axvi]), sizeof(double));
     tmp = (d1 != 0.0);
    }
   else if (blen <= WBITS)
    {
     aval = __get_wrd_con_val(if_apti);
     bval = __get_wrd_con_val(if_bpti);
     tmp = ((aval & ~bval) != 0L);
    }
   else
    {
     axvi = __get_con_adradd_xvi(if_apti);
     /* constant wide case */
     bxvi = __get_con_adradd_xvi(if_bpti);
     tmp = (__cvt_lngbool(&(__contab[axvi]), &(__contab[bxvi]), blen));
    }
//AIV FIXME  - the unreachable code is a problem for +modlib because of the 
//linking - can just ignore stmt with unlinked enter spots after code 
//is debugged
   /* tmp = 1, the if is T */
   if (tmp) 
    {
     stp = ifinfo->thenst;
     /* gen the T case */
     gen_stlst(ifinfo->thenst, TRUE);
     /* mark else unreachable */
     if (else_stp != NULL) 
      {
       __mark_stlst_unreachable(__inst_mod, else_stp);
      }
    }
   /* mark else unreachable */
   else if (else_stp != NULL) 
    {
     /* gen the F case */
     gen_stlst(else_stp, TRUE);
     __mark_stlst_unreachable(__inst_mod, ifinfo->thenst);
    }
   /* no else and if not reachable */
   else __mark_stlst_unreachable(__inst_mod, ifinfo->thenst);

   if (stp->stnxt != NULL) __pop_cc_stmt();
   return;
  }

 f_bbp = NULL;
 t_bbp = __alloc_bblk(FALSE);
 if (else_stp != NULL) f_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* 0 is F and 1 is T */
 if (__tmp_is_2state(if_apti))
  {
   if (else_stp != NULL) __emit_jmp_0(f_bbp, t_bbp, if_apti);
   else __emit_jmp_0(after_bbp, t_bbp, if_apti); 
  }
 else if (__tntab[if_apti].t_real)
  {
   if (else_stp != NULL)
    {
     __emit_jmp_real0(f_bbp, t_bbp, if_apti);
    }
   else
    {
     __emit_jmp_real0(after_bbp, t_bbp, if_apti); 
    }
  }
 else
  {
   /* AIV 08/15/08 - if scalar just get the jump value from the pre-computed */
   /* if table values */
   srtyp = __tntab[if_apti].srtyp;
   if (srtyp == SR_SCAL || srtyp == SR_SSCAL)
    {
     if (srtyp == SR_SSCAL)
      {
       cint_ti = __gen_cint_tn(3);
       if_apti = __emit_bin_bitand(WBITS, cint_ti, if_apti);
      }
     /* AIV 03/09/09 - no need for scalar index table here */
     /* only need to compare for 1 */
     cint_ti = __gen_cint_tn(1);
     if (else_stp != NULL) __emit_jmp_eq(t_bbp, f_bbp, cint_ti, if_apti);
     else __emit_jmp_eq(t_bbp, after_bbp, cint_ti, if_apti);
    }
   else if (blen <= WBITS)
    {
     /* AIV 11/17/05 - this one incorrect for wide */
     /* better to call convert bool and do operations on wide operand */
     if_bpti = __get_bpti(if_apti);
     t1_ti = __emit_bitnot(WBITS, if_bpti);
     bool_ti = __emit_bin_bitand(WBITS, if_apti, t1_ti);
     /* compare to 0 */
     if (else_stp != NULL) __emit_jmp_0(f_bbp, t_bbp, bool_ti);
     else __emit_jmp_0(after_bbp, t_bbp, bool_ti); 
    }
   else
    {
     if_bpti = __get_bpti(if_apti);
     /* if wide use wrapper so doesn't check all words  */
     bool_ti = gen_bin_cvt_bool(if_apti, if_bpti);
     /* compare to 1 */
     cint_ti = __gen_cint_tn(1);
     if (else_stp != NULL) __emit_jmp_eq(t_bbp, f_bbp, bool_ti, cint_ti);
     else __emit_jmp_eq(t_bbp, after_bbp, bool_ti, cint_ti);
    }
  }

 __start_bblk(t_bbp);
 gen_stlst(ifinfo->thenst, TRUE);

 /* if have else need goto to skip it at end of then */
 if (else_stp != NULL)
  {
   __emit_jmp(after_bbp);
   __start_bblk(f_bbp);
   gen_stlst(else_stp, TRUE);
  }
 /* this inserts the uncond jmp if needed */ 
 __start_bblk(after_bbp);

 if (stp->stnxt != NULL) __pop_cc_stmt();
}

#ifdef __XPROP__
/*
 * xprop2 if stmt just like normal if except check for if bpart if so go
 * to pre fixed up stmts else part which is the xed out list
 */
static void gen_xprop2_if_stmt(struct st_t *if_stp)
{
 int32 if_apti, if_bpti, blen, cint_ti;
 int32 bxvi, srtyp, save_blen, is_scalar;
 word32 bval, tmp;
 struct bblk_t *t_bbp, *f_bbp, *after_bbp;
 struct st_t *stp;
 struct if_t *ifinfo;

 ifinfo = &(if_stp->st.sif);

 /* AIV 12/08/06 - empty block don't need to evaluate */
 /* AIV FIXME - need to check for these in other stmtms while/for/etc */
 /* either only has an empty if or both all none don't produce any code */
 stp = ifinfo->thenst;
 if_bpti = -1;
 if (stp->stmttyp == S_STNONE && 
     (ifinfo->elsest == NULL || ifinfo->elsest->stmttyp == S_STNONE)) 
  {
    return;
  }

 /* real conditional values left as normal if stmt */
 /* DBG remove --- */
 if (ifinfo->condx->is_real) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);


 /* first eval condition expr */
 if_apti = __gen_expr_eval(ifinfo->condx, -1);
 blen = __get_tnwid(if_apti);

 /* AIV 11/21/06 - handle the constant if case */
 if (__is_constant(if_apti))
  {
   if_bpti = __get_bpti(if_apti);
   /* narrow constant case */
   /* constant real case */
   /* DBG remove --- */
   if (__tntab[if_apti].t_real) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   if (blen <= WBITS)
    {
     bval = __get_wrd_con_val(if_bpti);
     tmp = (bval != 0);
    }
   else
    {
     /* constant wide case */
     bxvi = __get_con_adradd_xvi(if_bpti);
     tmp = !(vval_is0_(&(__contab[bxvi]), blen));
    }
   /* tmp = 1, the if is T */
   if (tmp) 
    {
     stp = ifinfo->thenst;
     /* gen the T case */
     gen_stlst(ifinfo->thenst, TRUE);
     /* mark else unreachable */
     if (ifinfo->elsest != NULL) 
      {
       __mark_stlst_unreachable(__inst_mod, ifinfo->elsest);
      }
    }
   /* mark else unreachable */
   else if (ifinfo->elsest != NULL) 
    {
     /* gen the F case */
     gen_stlst(ifinfo->elsest, TRUE);
     __mark_stlst_unreachable(__inst_mod, ifinfo->thenst);
    }
   /* no else and if not reachable */
   else __mark_stlst_unreachable(__inst_mod, ifinfo->thenst);

   if (stp->stnxt != NULL) __pop_cc_stmt();
   return;
  }

 f_bbp = NULL;
 t_bbp = __alloc_bblk(FALSE);
 if (ifinfo->elsest != NULL) f_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* should never x-prop with 2-state, and reals treated as regular if stmts */
 /* DBG remove -- */
 if (__tmp_is_2state(if_apti)) __misc_terr(__FILE__, __LINE__);
 if (__tntab[if_apti].t_real) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* DBG remove -- */
 if (ifinfo->elsest == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* AIV 08/15/08 - if scalar just get the jump value from the pre-computed */
 /* if table values */
 srtyp = __tntab[if_apti].srtyp;
 is_scalar = FALSE;
 if (srtyp == SR_SCAL || srtyp == SR_SSCAL)
  {
   if (srtyp == SR_SSCAL)
    {
     cint_ti = __gen_cint_tn(3);
     if_apti = __emit_bin_bitand(WBITS, cint_ti, if_apti);
    }
   cint_ti = __gen_cint_tn(2);
   /* need to set to WBITS otherwise compare is optimized away */
   save_blen = __tntab[if_apti].tnwid;
   __tntab[if_apti].tnwid = WBITS;
   /* if > 2 then is known to be x/z */
   __emit_jmp_cmp(t_bbp, f_bbp, if_apti, cint_ti, CC_JGE);
   __tntab[if_apti].tnwid = save_blen;
   is_scalar = TRUE;
  }
 else 
  {
   /* just check the b part if 0 goto false */
   /* compare to 0 */
   if_bpti = __get_bpti(if_apti);
   __emit_jmp_0(f_bbp, t_bbp, if_bpti);
  }

 __start_bblk(t_bbp);
 /* if xprop trace on record stmt */
 if (__xprop_trace_on) 
  {
   if (is_scalar)
    {
     if_apti = __gen_cnvt_srep_ifneeded(if_apti, SR_VEC, blen, 
       FALSE, FALSE, FALSE); 
     if_bpti = __get_bpti(if_apti);
    }
   gen_xprop_trace_write(if_stp, if_apti, if_bpti, blen);
  }
 gen_stlst(ifinfo->thenst, TRUE);
 __emit_jmp(after_bbp);

 __start_bblk(f_bbp);
 gen_stlst(ifinfo->elsest, TRUE);
 /* this inserts the uncond jmp if needed */ 
 __start_bblk(after_bbp);

 if (stp->stnxt != NULL) __pop_cc_stmt();
}

/*
 * gen insns for x-propagation if statement
 */
static void gen_xprop_if_stmt(struct st_t *stp, int32 slevel, 
 int32 if_apti, int32 if_bpti)
{
 int32 blen, cint_ti, need_combine_ti;
 int32 srtyp, save_blen;
 struct bblk_t *xz_bbp, *noxz_bbp, *after_bbp, *t_bbp, *f_bbp, *else_bbp;
 struct st_t *else_stp, *then_stp;
 struct if_t *ifinfo;
 struct xprop_t *xprop;

 ifinfo = &(stp->st.sif);

 xprop = stp->st.sif.xprop;
 /* DBG remove */
 if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
  /* --- */

 /* AIV 12/08/06 - empty block don't need to evaluate */
 /* AIV FIXME - need to check for these in other stmtms while/for/etc */
 /* either only has an empty if or both all none don't produce any code */
 then_stp = ifinfo->thenst;
 if (then_stp->stmttyp == S_STNONE && 
     (ifinfo->elsest == NULL || ifinfo->elsest->stmttyp == S_STNONE)) 
  {
    return;
  }
 
 else_stp = ifinfo->elsest;
 /* real conditional values left as normal if stmt */
 /* DBG remove --- */
 if (ifinfo->condx->is_real) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);


 if_bpti = -1;
 f_bbp = NULL;
 /* first eval condition expr */
 after_bbp = __alloc_bblk(FALSE);
 else_bbp = NULL;
 need_combine_ti = -1;
 /* if may already be evaled for the top level and is known to be x here */
 if (if_apti == -1)
  {
   need_combine_ti = __gen_tn(SR_CINT, WBITS);
   __emit_store_cint(need_combine_ti, TRUE, WRDBYTES);
   if_apti = __gen_expr_eval(ifinfo->condx, -1);
   blen = __get_tnwid(if_apti);

   /* AIV 10/18/11 - if constant just do a copy for now to force xprop handle */
   if (__is_constant(if_apti)) if_apti = __gen_duplicate_tmp(if_apti);

   xz_bbp = __alloc_bblk(TRUE);
   noxz_bbp = __alloc_bblk(FALSE);

   /* should never x-prop with 2-state, and reals treated as regular if stmts */
   /* DBG remove -- */
   if (__tmp_is_2state(if_apti)) __misc_terr(__FILE__, __LINE__);
   if (__tntab[if_apti].t_real) __misc_terr(__FILE__, __LINE__);
   /* ----- */

   /* AIV 08/15/08 - if scalar just get the jump value from the pre-computed */
   /* if table values */
   srtyp = __tntab[if_apti].srtyp;
   if_bpti = -1;
   if (srtyp == SR_SCAL || srtyp == SR_SSCAL)
    {
     if (srtyp == SR_SSCAL)
      {
       cint_ti = __gen_cint_tn(3);
       if_apti = __emit_bin_bitand(WBITS, cint_ti, if_apti);
      }
     cint_ti = __gen_cint_tn(2);
     /* need to set to WBITS otherwise compare is optimized away */
     save_blen = __tntab[if_apti].tnwid;
     __tntab[if_apti].tnwid = WBITS;
     /* if > 2 then is known to be x/z */
     __emit_jmp_cmp(xz_bbp, noxz_bbp, if_apti, cint_ti, CC_JGE);
     __tntab[if_apti].tnwid = save_blen;
    }
   else 
    {
     /* just check the b part if 0 goto false */
     /* compare to 0 */
     if_bpti = __get_bpti(if_apti);
     __emit_jmp_0(noxz_bbp, xz_bbp, if_bpti);
    }

   /* known to not contain any x/z here */
   __start_bblk(noxz_bbp);
   t_bbp = __alloc_bblk(FALSE);
   f_bbp = __alloc_bblk(FALSE);

   __emit_jmp_0(f_bbp, t_bbp, if_apti);

   __start_bblk(t_bbp);
   gen_set_xprop_accum_block(stp, xprop);
   gen_xprop_stlst(ifinfo->thenst, slevel+1, stp);
   cint_ti = __gen_cint_tn(FALSE); 
   gen_set_restore_xprop_accum_block(stp, cint_ti, xprop);
   __emit_jmp(after_bbp);

   __start_bblk(f_bbp);
   /* if 'else' is original statement else and not xprop no else created */
   /* do the else block - otherwise skip it */
   if (else_stp != NULL)
    {
     /* set need combine to FALSE */
     __emit_store_cint(need_combine_ti, FALSE, WRDBYTES);
     gen_set_xprop_accum_block(stp, xprop);
     else_bbp = __alloc_bblk(FALSE);
     /* go to combine else stmt list */
     __emit_jmp(else_bbp);
    }
   else __emit_jmp(after_bbp);

   /* this is the x/z case must now combine the values */
   __start_bblk(xz_bbp);
  }
 else blen = __get_tnwid(if_apti);

 /* if xprop trace on record stmt */
 if (__xprop_trace_on) 
  {
   gen_xprop_trace_write(stp, if_apti, if_bpti, blen);
  }

 /* if has bbit set and so else - nothing to do */
 gen_set_xprop_accum_block(stp, xprop);

 gen_xprop_stlst(ifinfo->thenst, slevel+1, stp);

 if (else_stp != NULL)
  {
   if (else_bbp != NULL) __start_bblk(else_bbp);
   cint_ti = __gen_cint_tn(1); 
   gen_set_xblock_number(stp, cint_ti, xprop);
   /* else may be combined from above need to check combine flag */
   gen_xprop_stlst(else_stp, slevel+1, stp);
  }


 /* if there is no else stmt it must combine with itself */
 if (else_bbp != NULL)
  {
   if (else_stp != NULL) 
    {
     gen_set_restore_xprop_accum_block(stp, need_combine_ti, xprop);
    }
   else gen_set_restore_xprop_accum_block_toself(stp, xprop);
  }
 else
  {
   /* not from above must always combine values */
   if (else_stp != NULL) 
    {
     cint_ti = __gen_cint_tn(TRUE); 
     gen_set_restore_xprop_accum_block(stp, cint_ti, xprop);
    }
   else gen_set_restore_xprop_accum_block_toself(stp, xprop);
  }

 /* this inserts the uncond jmp if needed */ 
 __start_bblk(after_bbp);

 if (stp->stnxt != NULL) __pop_cc_stmt();
}
   
/*
 * set xprop->xblock = number
 */
static void gen_set_xblock_number(struct st_t *stp, int32 cint_ti, 
 struct xprop_t *xprop)
{
 int32 stp_ti, s_ti, x_ti;
 size_t offset;
#ifndef __CVC32__
 int32 xblock_ti;
#endif

 if (xprop->has_one_id_only && xprop->top_single_item)
  return;

 /* inlined
	movq	ST_0_2, %rdx
	movq	24(%rdx), %rdx
	movl	$0x1, 4(%rdx)
 */
 offset = 0;
 x_ti = 0;
 stp_ti = __gen_stmt_tn(stp);
 s_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, stp_ti);
 if (stp->stmttyp == S_CASE) 
  {
   offset = (byte *) &(stp->st.scs.xprop) - (byte *) stp;
   x_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG_DISP, s_ti, offset);
  }
 else if (stp->stmttyp == S_IF)
  {
   offset = (byte *) &(stp->st.sif.xprop) - (byte *) stp;
   x_ti = __move_insn(TN_ADR, I_MOVA, AM_NDXREG_DISP, s_ti, offset);
  }
 else __case_terr(__FILE__, __LINE__);
 offset = (byte *) &(xprop->xblock) - (byte *) xprop;
#ifdef __CVC32__
 __st_insn(I_STOREL, AM_REG, cint_ti, AM_NDXREG_DISP, x_ti, offset);
#else
 xblock_ti = __con_adradd_insn(SR_CINT, INTBITS, x_ti, offset);
 __emit_copy(INTBYTES, cint_ti, xblock_ti);
#endif
}

static void gen_set_xprop_check_case_net_set(struct st_t *stp, 
 int32 matched_ti, struct xprop_t *xprop)
{
 /* AIV 02/25/12 - this doesn't need the top only item */ 
 /* if this has only one id cannot set one variable and not the other */
 if (xprop->has_one_id_only)
  return;

 __emit_xprop_check_case_net_set(stp, matched_ti);
}
     
static void gen_set_xprop_accum_block(struct st_t *stp, struct xprop_t *xprop)
{
 if (xprop->has_one_id_only && xprop->top_single_item)
  return;

 __emit_set_xprop_accum_block(stp);
}

static void gen_set_restore_xprop_accum_block(struct st_t *stp, 
 int32 xblocks_ti, struct xprop_t *xprop)
{
 if (xprop->has_one_id_only && xprop->top_single_item)
  return;

 __emit_set_restore_xprop_accum_block(stp, xblocks_ti);
}

static void gen_set_restore_xprop_accum_block_toself(struct st_t *stp, 
  struct xprop_t *xprop)
{
 if (xprop->has_one_id_only && xprop->top_single_item)
  {
   gen_xprop_combine_with_self(xprop);
   return;
  }

 __emit_set_restore_xprop_accum_block_toself(stp);
}

static void gen_set_restore_xprop_accum_block_nodefault(struct st_t *stp,
 int32 num_matched_ti, int32 xcount_ti, struct xprop_t *xprop)
{
 if (xprop->has_one_id_only && xprop->top_single_item)
  return;

 __emit_set_restore_xprop_accum_block_nodefault(stp, num_matched_ti, xcount_ti);
}
   
static void gen_assign_xprop_value(struct st_t *stp, struct expr_t *rhsx,
 int32 accum_ti, struct net_t *np)
{
 struct st_t *astp;
 struct expr_t *lhsx;
 struct delctrl_t *dctp;
 int32 save_typ, save_xclen;
 void *save_lux;


 /* now assign lhs expression */
 switch (stp->stmttyp) {
  case S_PROCA: 
   if (rhsx == NULL) rhsx = stp->st.spra.rhsx;

   /* proc assigns still may have to force to id assign */
   lhsx = stp->st.spra.lhsx;
   save_typ = lhsx->optyp;
   if (save_typ != ID)
    {
     save_lux = (void *) lhsx->lu.sy;
     save_xclen = lhsx->szu.xclen;
     lhsx->optyp = ID;
     lhsx->lu.sy = np->nsym;
     lhsx->szu.xclen = np->nwid;
     /* do the assign */
     gen_proc_assign(lhsx, rhsx, accum_ti);
     lhsx->lu.sy = save_lux;
     lhsx->optyp = save_typ;
     lhsx->szu.xclen = save_xclen;
    }
   else gen_proc_assign(lhsx, rhsx, accum_ti);
   break;
  case S_NBPROCA: 
   if (rhsx == NULL) rhsx = stp->st.spra.rhsx;
   /* nb assigns have already been converted to rhsx */
   gen_nblkrhs_proca(stp, rhsx, accum_ti);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->xprop_nb_actionst;

   if (rhsx == NULL) rhsx = astp->st.spra.rhsx;
   /* DBG remove --- */
   if (astp->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);
   lhsx = astp->st.spra.lhsx;
   if (lhsx->optyp != ID) __misc_terr(__FILE__, __LINE__);
   /* ------ */
   gen_nb_dctl_ectl(stp, rhsx, accum_ti);
   break;
  default: __case_terr(__FILE__, __LINE__); break;
 }
}

static void gen_assign_xprop_accum_values(struct st_t *stp)
{
 int32 i, accum_ti, accum_zero_ti, blen, bitset_ti;
 struct net_t *np;
 struct expr_t *rhsx;
 struct bblk_t *assign_bbp, *after_bbp;
 struct xprop_t *xprop;


 xprop = NULL;
 if (stp->stmttyp == S_CASE) xprop = stp->st.scs.xprop;
 else if (stp->stmttyp == S_IF) xprop = stp->st.sif.xprop;
 else __case_terr(__FILE__, __LINE__);

 /* DBG remove */
 if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];

   /* DBG remove -- */
   if (np->srep != SR_VEC && np->srep != SR_SCAL && np->srep != SR_ARRAY)
     __misc_terr(__FILE__, __LINE__);
   /* ---- */

   assign_bbp = __alloc_bblk(FALSE);
   after_bbp = __alloc_bblk(FALSE);
   /* if not initialized once must set to x */
   if (xprop->lhs_id_only[i])
    {
     accum_ti = __emit_get_xprop_accum(np);
     /* need to move so jmp 0 doesn't treat as word value for returned ptr */
     accum_zero_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, accum_ti);
     __emit_jmp_0(after_bbp, assign_bbp, accum_zero_ti);
     __start_bblk(assign_bbp);
    }
   else
    {
     blen = np->nwid;
     accum_ti = __gen_tn(SR_VEC, blen);
     bitset_ti = __emit_per_bit_xprop_accum(stp, i, accum_ti);
     /* need to move so jmp 0 doesn't treat as word value for returned ptr */
     __emit_jmp_0(after_bbp, assign_bbp, bitset_ti);
     __start_bblk(assign_bbp);
    }

   /* just alloc a new rhsx and set to non-constant operand */
   /* this just saves a bunch of ugly if stmt code by passing down */
   /* a dummy expr */
   rhsx = __alloc_newxnd();
   rhsx->optyp = GLBREF;
   /* set dummy operand to nets values */
   rhsx->szu.xclen = np->nwid;
   rhsx->has_sign = np->n_signed;


   gen_assign_xprop_value(xprop->astmts[i], rhsx, accum_ti, np);

   __emit_jmp(after_bbp);
   __start_bblk(after_bbp);
   __my_free(rhsx, sizeof(struct expr_t));
  }
}

/*
 * generate xprop stmt list - currently known to be if/case/lhs assign
 */
static struct st_t *gen_xprop_stlst(struct st_t *hd_stp, int32 slevel,
 struct st_t *xprop_stp)
{
 int32 rhs_ti, level;
 struct bblk_t *stmt_bbp;
 struct expr_t *lhsx, *rhsx;
 struct st_t *astp, *stp, *stp2;
 struct delctrl_t *dctp;

 /* if no cur bblk always alloc but if after suspend, the needed bblk */
 /* has already been allocated and made current */
 if (__cur_bbp == NULL)
  {
   /* always must start new bblk on entry from scheduler */
   /* SJM 06/15/05 - only need new bblk if not after suspend entry */
   stmt_bbp = __alloc_bblk(FALSE);
   __start_bblk(stmt_bbp);
  }

 stp = hd_stp;
 for (;;)
  {
   /* AIV 08/17/11 - need to set these now for warning messages */
   /* currently just for div by 0 real warnings */
   __generating_stp = stp;

   /* need global that points to currently being gened stmt */
   __cur_ifrom_u.from_stp = stp;

   /* AIV 12/15/10 - record stmt coverage */
   if (__stmt_coverage) __emit_stmt_coverage(stp);

   switch ((byte) stp->stmttyp) {
    case S_STNONE: case S_NULL:
     break;
    case S_PROCA:
    case S_NBPROCA:
     lhsx = stp->st.spra.lhsx;
     rhsx = stp->st.spra.rhsx;
     rhs_ti = __gen_expr_eval(rhsx, TRUE);
     gen_assign_lhsx_to_accum(lhsx, rhs_ti, stp, xprop_stp);
     break;
    case S_CASE:
     gen_xprop_case(stp, slevel+1, -1, -1);
     break;
    case S_IF:
     gen_xprop_if_stmt(stp, slevel+1, -1, -1);
     break;
    case S_DELCTRL:
     /* for all of blocking prefix, rhs and non blocking - both dctl/ectl */
     dctp = stp->st.sdc;
     astp = dctp->actionst;
     /* DBG remove -- */
     if (astp->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);
     /* ----- */

     lhsx = astp->st.spra.lhsx;
     rhsx = astp->st.spra.rhsx;
     rhs_ti = __gen_expr_eval(rhsx, TRUE);
     gen_assign_lhsx_to_accum(lhsx, rhs_ti, astp, xprop_stp);
     break;
    case S_GOTO:
     stp2 = stp->st.sgoto;
//AIV EXPROP - always @(c) d <= #1 e;  appears to have a empty goto
//AIV LOOKATME - is this right????? - same as exec_xprop_stmts in v_xprop
     if (stp2 == NULL) return(NULL);
     level = stp2->xprop_level;
     if (level != -1 && level < slevel) return(stp2);
     stp = stp2;
     goto nxt_stmt;
    /* no code for break points in generated code */
    default: __case_terr(__FILE__, __LINE__); break;
   }
   stp = stp->stnxt;
nxt_stmt:
   if (stp == NULL) break;
   level = stp->xprop_level;
   if (level != -1 && level > slevel) return(stp);
 }
 return(stp);
}
    
/*
 * assign lhs accumulator - currently id only is in the compiler otherwise
 * it just calls the same interp wrapper to do the assign
 */
static void gen_assign_lhsx_to_accum(struct expr_t *lhsx, int32 rhs_ti,
 struct st_t *stp, struct st_t *xprop_stp)
{
 int32 rhs_bpti;
 struct expr_t *idndp;
 struct net_t *np;
 struct xprop_t *xprop;

 xprop = NULL;
 if (xprop_stp->stmttyp == S_CASE) xprop = xprop_stp->st.scs.xprop;
 else if (xprop_stp->stmttyp == S_IF) xprop = xprop_stp->st.sif.xprop;
 /* DBG remove -- */
 else __case_terr(__FILE__, __LINE__);
 /* -- */

 rhs_bpti = -1;
 if (xprop->has_one_id_only && xprop->top_single_item) 
  {
   /* DBG remove -- */
   if (lhsx->optyp != ID) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   idndp = __get_lvalue_idndp(lhsx);
   np = idndp->lu.sy->el.enp;
   gen_set_xprop_accum_value_id(np, rhs_ti);
  }
 else
  {
   /* convert to vector */
   rhs_ti = __gen_cnvt_srep_ifneeded(rhs_ti, SR_VEC, lhsx->szu.xclen, 
     lhsx->has_sign, FALSE, FALSE); 
   rhs_bpti = __get_bpti(rhs_ti);
   if (lhsx->szu.xclen > WBITS)
    {
     /* AIV 03/26/12 - added better wrappers to do the common ID case */
     /* could do better determing id because this may access a different */
     /* net as a bit select - uses xprop wide bit for now */ 
     if (xprop->has_ids_only && lhsx->optyp == ID)
      {
       np = lhsx->lu.sy->el.enp;
       __emit_stmt_assign_to_accum_id_wide(np, xprop_stp, rhs_ti, rhs_bpti);
      }
     else __emit_stmt_assign_to_accum_wide(stp, xprop_stp, rhs_ti, rhs_bpti);
    }
   else
    {
     if (xprop->has_ids_only && lhsx->optyp == ID)
      {
       np = lhsx->lu.sy->el.enp;
       __emit_stmt_assign_to_accum_id_1w(np, xprop_stp, rhs_ti, rhs_bpti);
      }
     else  __emit_stmt_assign_to_accum_1w(stp, xprop_stp, rhs_ti, rhs_bpti);
    }
  }
}

/*
 * assign lhs id value
 */
static void gen_set_xprop_accum_value_id(struct net_t *np, int32 rhs_ti)
{
 int32 rhs_bpti;

 switch ((byte) np->srep) {
  case SR_ARRAY:
  case SR_VEC:
  case SR_SCAL:
//AIV XPROP - if scalar produce better code????
   rhs_ti = __gen_cnvt_srep_ifneeded(rhs_ti, SR_VEC, np->nwid, np->n_signed, 
    FALSE, TRUE); 
   
   if (np->nwid <= WBITS)
    {
     rhs_bpti = __get_bpti(rhs_ti);
     __emit_get_xprop_accum_init(np, rhs_ti, rhs_bpti);
    }
   else __emit_get_xprop_accum_init_wide(np, rhs_ti);
   return;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * emit the xprop tracing code 
 */
static void gen_xprop_trace_write(struct st_t *stp, int32 val_ti, 
 int32 val_bpti, int32 blen)
{
 /* DBG remove -- */
 if (stp->stmttyp != S_IF && stp->stmttyp != S_CASE) 
  __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* if scalar, etc may have to convert to vector to obtain b part */
 if (val_bpti == -1) 
  {
   val_ti = __gen_cnvt_srep_ifneeded(val_ti, SR_VEC, __tntab[val_ti].tnwid,
    __tntab[val_ti].t_signed, FALSE, TRUE); 
   val_bpti = __get_bpti(val_ti);
  }
 /* wide or narrow wrappers */
 if (blen > WBITS)
  {
   __emit_trace_xprop_write_wide(stp, val_ti, val_bpti, blen);
  }
 else __emit_trace_xprop_write(stp, val_ti, val_bpti, blen);
}

#endif

/* 
 * inline cvt_wrdbool 
 * val = ((((av) & ~(bv)) != 0L) ? 1 : (((bv) != 0L) ? 3 : 0)); 
 * AIV LOOKATME - equivalent should change macro ???? - produces less code 
 * if ((av & ~bv) != 0) val = 1; 
 * else if (bv != 0) val = 3;
 * else val = 0;
 */
static int32 gen_bin_cvt_bool(int32 term_apti, int32 term_bpti)
{
 int32 blen, val_ti, t1_ti, t2_ti, ndx_ti, srtyp, amtyp, cint_ti, scal_ti;
 struct bblk_t *xz_bbp, *check_x_bbp, *one_bbp, *done_bbp;

 /* AIV 08/21/08 - handle the scalar case */
 if (term_bpti == -1)
  {
   srtyp = __tntab[term_apti].srtyp;
   /* 2-state just return value */
   if (srtyp == SR_SCAL2S) 
    {
     if (__tntab[term_apti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
     else amtyp = AM_REG;
     ndx_ti = __move_insn(TN_VAL, I_MOVA, amtyp, term_apti);
     return(ndx_ti);
    }

   /* DBG remove -- */
   if (srtyp != SR_SCAL && srtyp != SR_SSCAL) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   if (srtyp == SR_SSCAL) 
    {
     cint_ti = __gen_cint_tn(3); 
     scal_ti =  __emit_bin_bitand(WBITS, cint_ti, term_apti);
    }
   else scal_ti = term_apti;

   if (__tntab[scal_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
   else amtyp = AM_REG;
   ndx_ti = __move_insn(TN_VAL, I_MOVA, amtyp, scal_ti);
   /* AIV 09/21/09 - __bool_svals is just pattern one */
   val_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, ndx_ti, 
     NLO_UN_P1);
   return(val_ti);
  }

 blen = __get_tnwid(term_apti);
 /* wide wrapper case */
 if (blen > WBITS)
  {
   val_ti = __emit_wide_cvt_bool(term_apti, term_bpti);
   return(val_ti);
  }

 /* DBG remove -- */
 if (__is_constant(term_apti)) __misc_terr(__FILE__, __LINE__);
 if (__is_constant(term_bpti)) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 xz_bbp = __alloc_bblk(TRUE);
 check_x_bbp = __alloc_bblk(FALSE);
 one_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);

 val_ti = __gen_tn(SR_CINT, WBITS);
 t1_ti = __emit_bitnot(WBITS, term_bpti);
 t2_ti = __emit_bin_bitand(WBITS, term_apti, t1_ti);
 /* if ((av & ~bv) != 0) val = 1; */
 /* val = 0 */
 __emit_store_cint(val_ti, 0, WRDBYTES);
 __emit_jmp_0(check_x_bbp, one_bbp, t2_ti);

 __start_bblk(one_bbp);
 /* val = 1 */
 __emit_store_cint(val_ti, 1, WRDBYTES);
 __emit_jmp(done_bbp);

 /* if (bv != 0) val = 3; */
 __start_bblk(check_x_bbp);
 __emit_jmp_0(done_bbp, xz_bbp, term_bpti);

 /* val = x (3) */
 __start_bblk(xz_bbp);
 __emit_store_cint(val_ti, 3, WRDBYTES);
 __emit_jmp(done_bbp);

 __start_bblk(done_bbp);
 return(val_ti);
}

/*
 * do the cvt_wrdbool_ macro where one value is a known constant
 */
static word32 fold_constant_bin_cvt_bool(int32 term_apti, int32 term_bpti,
 int32 do_xprop, int32 *has_bpart)
{
 word32 aval, bval, val, blen, sval; 
 int32 wlen, xvi;
 word32 *wp, *bp;
 struct tn_t *tnp;

 *has_bpart = FALSE;
 /* fold the constant case */
 /* DBG remove -- */
 if (!__is_constant(term_apti)) __misc_terr(__FILE__, __LINE__);
 if (term_bpti != -1 && !__is_constant(term_bpti)) 
   __misc_terr(__FILE__, __LINE__);
 /* ---- */
 tnp = &(__tntab[term_apti]);
 blen = tnp->tnwid;
 /* AIV 08/21/08 - now handle the scalar case here */
 if (term_bpti == -1)
  {
   sval = __get_wrd_con_val(term_apti);
   aval = sval & 1;
   bval = (sval >> 1) & 1;
   /* AIV 08/03/11 - if xprop and bval is not zero return -1 */
   if (do_xprop && bval != 0) 
    {
     *has_bpart = TRUE;
     return(-1);
    }

   /* SJM 08/26/08 - was not setting val here */
   val = cvt_wrdbool_(aval, bval);
  }
 else if (blen <= WBITS)
  {
   aval = __get_wrd_con_val(term_apti);
   bval = __get_wrd_con_val(term_bpti);
   /* AIV 08/03/11 - if xprop and bval is not zero return -1 */
   if (do_xprop && bval != 0) 
    {
     *has_bpart = TRUE;
     return(-1);
    }
   val = cvt_wrdbool_(aval, bval);
  }
 else
  {
   /* AIV 12/17/07 - need to handle the wide case */
   /* if wide better be a wide constant */
   /* DBG remove -- */
   if (tnp->comlab_typ != COMLAB_CONADR) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   xvi = __get_con_adradd_xvi(term_apti);
   wp = &(__contab[xvi]);
   wlen = wlen_(blen);
   bp = &(wp[wlen]);
   /* AIV 08/03/11 - if xprop and bval is not zero return -1 */
   if (do_xprop && !vval_is0_(bp, blen))
    {
     *has_bpart = TRUE;
     return(-1);
    }

   val = __cvt_lngbool(wp, bp, wlen);
  }
 return(val);
}

/*
 * return TRUE if is a 2-state tmp
 */
extern int32 __tmp_is_2state(int32 ti)
{
 int32 srtyp;

 srtyp = __tntab[ti].srtyp;
 if (srtyp == SR_BIT2S || srtyp == SR_SCAL2S) 
  return(TRUE);

 return(FALSE);
}

/*
 * ROUTINES TO GENERATE VM INSNS FOR CASE STMT
 */

/*
 * gen insnsfor case stmt
 *
 * notice the jump table cases must be gened here to know general
 * shape of code as insns before temp binding and optimization
 *
 * LOOKATME - need to add code to lower to jump tables when possible
 */
#define MAX_CASE_JMPTAB 1024

static void gen_case(struct st_t *case_stp)
{
 int32 nitems, nxprs, selxlen, has_xznum, nxi, jtabsiz; 
 int32 has_dflt, maxwid, all_cases_con, sel_ti;
 word32 imatch_max, imatch_min; 
 struct csitem_t *dflt_csip, *csip;
 struct icasx_t *icasxtab;
 struct icas_t *icastab;
 struct st_t *selected_stp, *stp;
 struct xstk_t *selxsp;

 /* find number of case exprs and number of items (stmt lists) in case */ 
 /* can be many exprs for one item since comma separated lists allowed */
 fnd_case_sizes(case_stp, &nitems, &nxprs);

 /* each table ends with fence so do not need to pass size */
 nitems++;
 nxprs++;
 /* also need element for default (even if no default) */
 icasxtab = (struct icasx_t *)
  __my_malloc(nxprs*sizeof(struct icasx_t));
 icastab = (struct icas_t *) __my_malloc(nitems*sizeof(struct icas_t));

 /* build the case stmt element interlinked case d.s. */ 
 fill_castabs(case_stp, icastab, icasxtab); 
 selxlen = case_stp->st.scs.maxselwid;

 dflt_csip = case_stp->st.scs.csitems; 
 /* SJM 10/02/05 - need default for empty (just ;) default stmt too */ 
 if (dflt_csip->csist != NULL) has_dflt = TRUE; else has_dflt = FALSE;

 all_cases_con = fold_casx_vals(icasxtab, &has_xznum);

 /* AIV 08/03/11 - if all case items are constant and not x/x can */
 /* handle as regular case stmt */
 /* AIV 02/13/12 - cannot do this optimization here must still match */
 /* since if has an x value must match */
 /* could do the if (no_xz) jump_table (constant) else xz_list */
 /* that is make two case statements */
 /*
 if (case_stp->st.scs.castyp != CASE) 
  {
   if (all_cases_con && !has_xznum)
    {
     case_stp->st.scs.castyp = CASE; 
    }
  }
 */


 /* if all match item exps non x/z constant - see if range allows jmp tab */
 /* AIV 08/13/08 - compiler generated constants cannot have IS numbers */
 /* was incorrectly folding a IS parameter which varies for diff intances */
 if (all_cases_con && __cvc_is_const_expr(case_stp->st.scs.csx)) 
  {
   selxsp = __eval_xpr(case_stp->st.scs.csx);
   selected_stp = __exec_case(case_stp, selxsp);
   /* AIV FIXME ------------- */
   /* need to mark all the non-reachable enter points -1 */
   /* AIV LOOKATME - should be a problem when switching to use static mem */
   /* for non-blocking assigns , regular enter stmts from sched as well */
   /* AIV FIMXE - this is a problem for +modlib */
   for (nxi = 0; nxi < nitems - 1; nxi++)
    {
     csip = icastab[nxi].csitem; 
     for (;csip != NULL; csip = csip->csinxt)
      {
       stp = csip->csist;
       if (stp == selected_stp) continue;
       __mark_stlst_unreachable(__inst_mod, stp);
      }
     }
   /* same thing with the default */
   stp = dflt_csip->csist; 
   if (stp != NULL && stp != selected_stp)
    {
     __mark_stlst_unreachable(__inst_mod, stp);
    }
   /* ------------------------- */
   gen_stlst(selected_stp, TRUE);
   goto done;
  }


 if (all_cases_con)
  {
   /* FIXME - for now not optimizing casex/casez but could optimize */  
   /* by using jump table if select non x/z and list otherwise */
   if (case_stp->st.scs.castyp != CASE) goto nd_list_cmp;

   if (selxlen > WBITS) goto nd_list_cmp;

   if (has_duplicated_cases(icasxtab)) goto nd_list_cmp;

   if (!has_xznum)
    {
     get_casxpr_minmax(icasxtab, &imatch_max, &imatch_min); 

     jtabsiz = imatch_max - imatch_min + 1;
     /* AIV 03/09/09 - if only 1 or 2 items, use list form */
     if (jtabsiz <= 2)
      {
       goto nd_list_cmp;
      }

     /* FIXME - think can use jump table for more cases - add here */
     if (imatch_max - imatch_min > (MAX_CASE_JMPTAB-1)) goto nd_list_cmp;
 
     /* allocate blocks if not folded */
     for (nxi = 0; nxi < nitems - 1; nxi++)
      {
       icastab[nxi].cstmt_bbp = __alloc_bblk(FALSE);
      }

     sel_ti = __gen_expr_eval(case_stp->st.scs.csx, -1);
     gen_jmptab_case_select(case_stp, icastab, icasxtab, has_dflt, dflt_csip,
      imatch_max, imatch_min, sel_ti);
     goto done;
    }
   maxwid = get_xzcas_maxwid(icasxtab);
   if (maxwid > 4) goto nd_list_cmp;

   /* allocate blocks if not folded */
   for (nxi = 0; nxi < nitems - 1; nxi++)
    {
     icastab[nxi].cstmt_bbp = __alloc_bblk(FALSE);
    }

   sel_ti = __gen_expr_eval(case_stp->st.scs.csx, -1);
   gen_xzjmptab_case_select(case_stp, icastab, icasxtab, has_dflt, dflt_csip,
    maxwid, sel_ti);
   goto done;
  }

nd_list_cmp:
 
 /* allocate blocks if not folded */
 for (nxi = 0; nxi < nitems - 1; nxi++)
  {
   icastab[nxi].cstmt_bbp = __alloc_bblk(FALSE);
  }

 /* for new flow graph algorithm - always gen as list */
 /* optimizer may lower to indexed jump */
 gen_list_case_select(case_stp, icastab, icasxtab, has_dflt, dflt_csip, 
   all_cases_con, has_xznum, nitems);
 
done:
 __my_free(icasxtab, nxprs*sizeof(struct icasx_t));
 __my_free(icastab, nitems*sizeof(struct icas_t));
}

#ifdef __XPROP__
/*
 * check if/case for select with a x/z value - if so enter xprop mode
 */
static void gen_xprop_enter(struct st_t *stp)
{
 int32 is_if;
 int32 srtyp, sel_apti, sel_bpti, save_blen, cint_ti;
 struct bblk_t *xz_bbp, *noxz_bbp, *after_bbp;
 struct expr_t *selxp;

 is_if = FALSE;
 selxp = NULL;
 /* must be a if/case stmt */
 if (stp->stmttyp == S_IF) 
  {
   is_if = TRUE;
   selxp = stp->st.sif.condx;
  }
 else if (stp->stmttyp == S_CASE) 
  {
   is_if = FALSE;
   selxp = stp->st.scs.csx;
  }
 else __case_terr(__FILE__, __LINE__);


/* AIV XPROP FORCE - enter for debug make sure compiler xprop entry works */
/*
{
 sel_apti = sel_bpti = -1;
 if (is_if)
  {
   gen_xprop_if_stmt(stp, stp->xprop_level, sel_apti, sel_bpti);
   gen_assign_xprop_accum_values(stp);
   return;
  }
 else
  {
   gen_xprop_case(stp, stp->xprop_level, sel_apti, sel_bpti); 
   gen_assign_xprop_accum_values(stp);
   return;
  }
}
*/

 xz_bbp = __alloc_bblk(TRUE);
 noxz_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 sel_apti = __gen_expr_eval(selxp, -1);
 sel_bpti = -1;
 srtyp = __tntab[sel_apti].srtyp;
 /* check bpart for x/z */
 if (srtyp == SR_SCAL || srtyp == SR_SSCAL)
  {
   if (srtyp == SR_SSCAL)
    {
     cint_ti = __gen_cint_tn(3);
     sel_apti = __emit_bin_bitand(WBITS, cint_ti, sel_apti);
    }
   cint_ti = __gen_cint_tn(2);
   /* need to set to WBITS otherwise compare is optimized away */
   save_blen = __tntab[sel_apti].tnwid;
   __tntab[sel_apti].tnwid = WBITS;
   /* if > 2 then is known to be x/z */
   __emit_jmp_cmp(xz_bbp, noxz_bbp, sel_apti, cint_ti, CC_JGE);
   __tntab[sel_apti].tnwid = save_blen;
  }
 else 
  {
   /* just check the b part if 0 goto false */
   /* compare to 0 */
   sel_bpti = __get_bpti(sel_apti);
   __emit_jmp_0(noxz_bbp, xz_bbp, sel_bpti);
  }

 /* xz block enter if/case xprop code */
 __start_bblk(xz_bbp);
 if (is_if)
  {
   gen_xprop_if_stmt(stp, stp->xprop_level, sel_apti, sel_bpti);
  }
 else
  {
   gen_xprop_case(stp, stp->xprop_level, sel_apti, sel_bpti); 
  }
 gen_assign_xprop_accum_values(stp);
 __emit_jmp(after_bbp);

 /* contains for xz value just handle as normal if/case */
 __start_bblk(noxz_bbp);
 if (is_if)
  {
   gen_if_stmt(stp);
  }
 else gen_case(stp);
 __emit_jmp(after_bbp);

 __start_bblk(after_bbp);

}

/*
 * generate code for xprop case
 */
static void gen_xprop_case(struct st_t *case_stp, int32 slevel,
 int32 sel_ti, int32 sel_bpti)
{
 int32 nitems, nxprs, selxlen, has_xznum;
 int32 all_cases_con, sel_signed, selwid;
 struct icasx_t *icasxtab;
 struct icas_t *icastab;
 struct expr_t *selxp;
 struct xprop_t *xprop;


 xprop = case_stp->st.scs.xprop;
 /* DBG remove */
 if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

//AIV XPROP - most of this isn't needed but leaving around for feature
//possbile case optimizations
 /* find number of case exprs and number of items (stmt lists) in case */ 
 /* can be many exprs for one item since comma separated lists allowed */
 fnd_case_sizes(case_stp, &nitems, &nxprs);

 /* each table ends with fence so do not need to pass size */
 nitems++;
 nxprs++;
 /* also need element for default (even if no default) */
 icasxtab = (struct icasx_t *)
  __my_malloc(nxprs*sizeof(struct icasx_t));
 icastab = (struct icas_t *) __my_malloc(nitems*sizeof(struct icas_t));

 /* build the case stmt element interlinked case d.s. */ 
 fill_castabs(case_stp, icastab, icasxtab); 
 selxlen = case_stp->st.scs.maxselwid;

 all_cases_con = fold_casx_vals(icasxtab, &has_xznum);
 selxp = case_stp->st.scs.csx;
 if (sel_ti == -1)
  {
   sel_ti = __gen_expr_eval(selxp, -1);
   /* if constant cannot fold rhs until sim time just copy the constant */
   /* to prevent folding */
  }
 if (all_cases_con && __cvc_is_const_expr(selxp)) 
   sel_ti = __gen_duplicate_tmp(sel_ti);


 /* may have to convert to get bpart - should be rare */

 /* if nested still need to do the combining values - only can do this */
 /* if it is a top level case stmt */
 sel_signed = FALSE;
 selwid = __get_tnwid(sel_ti);
 if (selwid < selxlen)
  { 
   if (selxp->has_sign && !selxp->unsgn_widen)
    sel_signed = TRUE;
   else sel_signed = FALSE;
  }
 sel_ti = __gen_cnvt_srep_ifneeded(sel_ti, SR_VEC, selxlen, sel_signed,
  FALSE, TRUE); 

 gen_list_case_xprop(case_stp, sel_ti, sel_bpti, slevel);
 __my_free(icasxtab, nxprs*sizeof(struct icasx_t));
 __my_free(icastab, nitems*sizeof(struct icas_t));
}

/*
 * generate case handling
 * basically must check ease case item like casex for unknown bits combining
 * all matching rhs values
 * AIV 01/31/12 - changed to match interpreter for expected xprop results
 */
static void gen_list_case_xprop(struct st_t *stp, int32 sel_ti, 
 int32 sel_bpti, int32 slevel)
{
 int32 selxlen, matchwid, match_ti, selres_ti;
 int32 sel_signed, amtyp, num_matched_ti, t1_ti, t2_ti, one_ti, xcount_ti;
 int32 cint_ti;
 struct exprlst_t *xplp;
 struct csitem_t *dflt_csip, *csip;
 struct expr_t *selxp;
 struct bblk_t *cond_bbp, *after_bbp, *default_bbp;
 struct bblk_t *trace_bbp, *skip_trace_bbp, *restore_bbp, *item_bbp;
 struct bblk_t *matched_bbp, *notall_matched_bbp;
 struct xprop_t *xprop;

 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);

 xprop = stp->st.scs.xprop;

 selxlen = stp->st.scs.maxselwid;

 /* if tracing on need to check if b part is zero and record stmt */
 selxp = stp->st.scs.csx;
 if (__xprop_trace_on) 
  {
   trace_bbp = __alloc_bblk(TRUE);
   skip_trace_bbp = __alloc_bblk(FALSE);

   sel_ti = __gen_cnvt_srep_ifneeded(sel_ti, SR_VEC, selxp->szu.xclen,
      selxp->has_sign, FALSE, TRUE); 

   if (sel_bpti == -1) sel_bpti = __get_bpti(sel_ti);
   __emit_jmp_0(skip_trace_bbp, trace_bbp, sel_bpti);
   __start_bblk(trace_bbp);
   gen_xprop_trace_write(stp, sel_ti, sel_bpti, selxp->szu.xclen);
   __emit_jmp(skip_trace_bbp);
   __start_bblk(skip_trace_bbp);
  }

 gen_set_xprop_accum_block(stp, xprop);

 after_bbp = __alloc_bblk(FALSE);
 /* generate the compare and jump iops - one for each expr */
 cond_bbp = NULL;
 one_ti = __gen_cint_tn(1);
 sel_signed = FALSE;
 dflt_csip = stp->st.scs.csitems;

 if (sel_bpti == -1) sel_bpti = __get_bpti(sel_ti);
 xcount_ti = __emit_xprop_xcount(sel_bpti);
 num_matched_ti = __gen_tn(SR_CINT, WBITS);
 __emit_store_cint(num_matched_ti, 0, WRDBYTES);

 csip = dflt_csip->csinxt;
 /* for xprop need to go through each item on the list and compare */
 for (; csip != NULL; csip = csip->csinxt)
  {
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     match_ti = __gen_expr_eval(xplp->xp, -1);
     matchwid = __get_tnwid(match_ti);
     if (matchwid > selxlen && selxlen > WBITS)
      {
       match_ti = __gen_cnvt_srep_ifneeded(match_ti, SR_VEC, selxlen,
        FALSE, FALSE, TRUE); 
      }
     else if (matchwid < selxlen)
      {
       if (stp->st.scs.csx->has_sign && !stp->st.scs.csx->unsgn_widen)
        sel_signed = TRUE;
       else sel_signed = FALSE;
       match_ti = __gen_cnvt_srep_ifneeded(match_ti, SR_VEC, selxlen,
        sel_signed, FALSE, TRUE); 
      }
     /* may have to swap between 2-state and 4-state */
     else if (SR_VEC != __tntab[match_ti].srtyp)
      {
       match_ti = __gen_cnvt_srep_ifneeded(match_ti, SR_VEC, selxlen,
        sel_signed, FALSE, TRUE); 
      }

     /* gen case list form (not jump table) compare and jump insns */
     selres_ti = gen_eval_case_sel(CASEX, selxlen, sel_ti,
        match_ti, stp);
     /* removed since they are known to never be true */
     /* doing this hack for now since these can be removed with value */
     /* tracking - but could be done here */
     /* case (1'b1) 1'b0: r = 0; (r2 == 6'd0): r = 1; endcase */
     /* if constant just move the value for now */
     if (__is_constant(selres_ti) && __tntab[selres_ti].tnwid <= WBITS) 
      {
       if (__tntab[selres_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG;
       else amtyp = AM_REG;
       selres_ti = __move_insn(TN_VAL, I_MOVA, amtyp, selres_ti);
      }

     cond_bbp = __alloc_bblk(FALSE);
     item_bbp = __alloc_bblk(FALSE);
     __emit_jmp_0(item_bbp, cond_bbp, selres_ti);

     /* AIV 10/21/05 - only generate one epxr == case if block not init */
     /* this is needed for the list case matching case */
     __start_bblk(item_bbp);

     gen_set_xblock_number(stp, num_matched_ti, xprop);

     gen_xprop_stlst(csip->csist, slevel+1, stp);
     /* inc the number of case times matched */

     /* DBG remove -- */
     if (xplp->num_xmatch == -1) __misc_terr(__FILE__, __LINE__); 
     /* --- */
     cint_ti = __gen_cint_tn(xplp->num_xmatch); 
     t1_ti = __emit_add(WBITS, num_matched_ti, cint_ti);
     __st_insn(I_STOREA, AM_REG, t1_ti, AM_REG, num_matched_ti);
     /* AIV 02/08/12 - for the second and greater case items must make */
     /* sure that all variables that were written to in the first */
     /* match are also written to in the second */
     gen_set_xprop_check_case_net_set(stp, num_matched_ti, xprop); 
      /* cannot jump to end must do all compares */
     __start_bblk(cond_bbp);
    }
  }

 if (dflt_csip->csist != NULL)
  {
   /* if has_bbit must include default */
   /* if (xcount) */
   
    /* if slevel == 0 and known to be nested this will always be true */
    /* that is the selector will be known b part */
    if (slevel == 0)
     {
      /* regardless of matched or not need to include the default */
      /* if (num_matched < (1 << xcount))  */
      matched_bbp = __alloc_bblk(FALSE);
      notall_matched_bbp = __alloc_bblk(FALSE);
      t2_ti = __emit_shiftl(WBITS, xcount_ti, one_ti);
      __emit_jmp_cmp(notall_matched_bbp, matched_bbp, num_matched_ti, t2_ti, 
         CC_JLT);

      __start_bblk(notall_matched_bbp);
      gen_set_xblock_number(stp, num_matched_ti, xprop);
      gen_xprop_stlst(dflt_csip->csist, slevel+1, stp);

      __start_bblk(matched_bbp);
      gen_set_restore_xprop_accum_block(stp, num_matched_ti, xprop);
     }
    else
     {
      default_bbp = __alloc_bblk(FALSE);
      restore_bbp = __alloc_bblk(FALSE);
      __emit_jmp_0(restore_bbp, default_bbp, xcount_ti);

      __start_bblk(restore_bbp);
      cint_ti = __gen_cint_tn(FALSE); 
      gen_set_restore_xprop_accum_block(stp, cint_ti, xprop);
      __emit_jmp(after_bbp);

      __start_bblk(default_bbp);


      matched_bbp = __alloc_bblk(FALSE);
      notall_matched_bbp = __alloc_bblk(FALSE);
      t2_ti = __emit_shiftl(WBITS, xcount_ti, one_ti);
      /* if (num_matched < (1 << xcount)) */
      __emit_jmp_cmp(notall_matched_bbp, matched_bbp, num_matched_ti, t2_ti, 
         CC_JLT);

      __start_bblk(notall_matched_bbp);

      gen_set_xblock_number(stp, num_matched_ti, xprop);
      gen_xprop_stlst(dflt_csip->csist, slevel+1, stp);

      __start_bblk(matched_bbp);
      gen_set_restore_xprop_accum_block(stp, num_matched_ti, xprop);
      __emit_jmp(after_bbp);
    }
  }
 else 
  {
   /* if didn't match all cases must xout the values */
   /* if (num_matched != (1 << xcount))  */
   if (xprop->has_one_id_only && xprop->top_single_item)
    {
     notall_matched_bbp = __alloc_bblk(FALSE);
     t2_ti = __emit_shiftl(WBITS, xcount_ti, one_ti);
     /* if (num_matched < (1 << xcount)) */
     __emit_jmp_cmp(notall_matched_bbp, after_bbp, num_matched_ti, t2_ti, 
        CC_JLT);

     __start_bblk(notall_matched_bbp);
     gen_xprop_combine_with_self(xprop);
    }
   else
    {
     gen_set_restore_xprop_accum_block_nodefault(stp, num_matched_ti, xcount_ti,
      xprop);
    }
  }

 __start_bblk(after_bbp);
 if (stp->stnxt != NULL) __pop_cc_stmt();
}
     
/*
 * combine a lhs xprop value with itself
 * this is used for no all cases possible xprop case statement
 */
static void gen_xprop_combine_with_self(struct xprop_t *xprop)
{
 struct net_t *np;
 int32 i, net_val_ti, vec_ti, vec_bpti;

 /* just assign each net an all 'X' value */
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];
   net_val_ti = __gen_ld_net_addr(np, NULL);
   vec_ti = __gen_cnvt_srep_ifneeded(net_val_ti, SR_VEC, np->nwid, np->n_signed,
    FALSE, TRUE); 
   if (np->nwid <= WBITS)
    {
     vec_bpti = __get_bpti(vec_ti);
     __emit_get_xprop_accum_to_self(np, vec_ti, vec_bpti);
    }
   else __emit_get_xprop_accum_to_self_wide(np, vec_ti);
  }
}
 
#endif

/*
 * AIV 08/13/08 - compiler generated constants cannot have IS numbers
 * these must still are evaluated at run time
 */
extern int32 __cvc_is_const_expr(struct expr_t *ndp) 
{
 int32 rval;

 __const_expr_has_isnums = FALSE;
 rval = __is_const_expr(ndp);
 if (__const_expr_has_isnums) 
  {
   __const_expr_has_isnums = FALSE;
   return(FALSE);
  }
 return(rval);
}

/*
 * find max number of case items expr list in case and number of cases
 */
static void fnd_case_sizes(struct st_t *stp, int32 *num_items,
 int32 *num_xprs)
{
 struct csitem_t *csip;
 struct exprlst_t *xplp;
 int32 itemnum, xprnum;
 struct csitem_t *dflt_csip;
 
 dflt_csip = stp->st.scs.csitems; 
 csip = dflt_csip->csinxt;
 for (itemnum = 0, xprnum = 0; csip != NULL; csip = csip->csinxt)
  {
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt) xprnum++;
   itemnum++;
  } 
 *num_items = itemnum;
 *num_xprs = xprnum; 
}


/*
 * fill the case expr table and case stmt list tables
 *
 * know tabs big enough because already scanned to to determine sizes
 * mark extra end elment as ending fence
 *
 * SJM 08/27/02 - now also allocates any needed labels but because 
 * case stmt list insn after select fill them at end
 */
static void fill_castabs(struct st_t *stp, struct icas_t *icastab, 
 struct icasx_t *icasxtab)
{
 int32 xpri, casi;
 struct csitem_t *csip;
 struct exprlst_t *xplp;
 struct csitem_t *dflt_csip;
 struct icasx_t *icasxp;
 struct icas_t *icasp;

 dflt_csip = stp->st.scs.csitems; 
 csip = dflt_csip->csinxt;
 for (casi = 0, xpri = 0; csip != NULL; csip = csip->csinxt, casi++)
  {
   icasp = &(icastab[casi]);
   init_icas(icasp);
   icasp->csitem = csip;
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     icasxp = &(icasxtab[xpri++]);
     init_icasx(icasxp);
     icasxp->casx = xplp->xp;
     icasxp->cas_tabi = casi;
    }
  } 
 icastab[casi].end_mark = TRUE;
 icasxtab[xpri].cxtyp = ICASX_ENDMARK;
}

/*
 * initializ a iop gen case record
 */
static void init_icas(struct icas_t *icasp)
{
 icasp->end_mark = 0;
 icasp->cstmt_bbp = NULL;
 icasp->csitem = NULL;
}

/*
 * initialize insn gen case record
 */
static void init_icasx(struct icasx_t *icasxp)
{
 icasxp->cxtyp = ICASX_UNKN; 
 icasxp->cas_tabi = -1;
 icasxp->aval = 0;
 icasxp->bval = 0;
 icasxp->casx = NULL;
}

/*
 * eval exprs in all iop case expr elements if possible
 * returns T if all case match items constants
 *
 * only set numeric value in case in <= WBITS and non x/z
 * expect in most common case, all case expr els small non x/z numbers so
 * can implement as compute goto table
 *
 * FIXME - when folding removed - need special handling for params here
 */
static int32 fold_casx_vals(struct icasx_t *icasxtab, int32 *has_xznum) 
{
 int32 nxi;
 word32 *wp;
 struct icasx_t *icasxp;
 struct expr_t *ndp;
 int32 wlen, all_cases_con;

 all_cases_con = TRUE;
 *has_xznum = FALSE;
 for (nxi = 0;; nxi++)
  {
   icasxp = &(icasxtab[nxi]);
   if (icasxp->cxtyp == ICASX_ENDMARK) break;

   ndp = icasxp->casx;
   if (ndp->optyp != NUMBER)
    {
     /* notice IS numbers are expressions here */ 
     if (igen_xpr_hasfcall(ndp)) icasxp->cxtyp = ICASX_COMPLEX;
     else icasxp->cxtyp = ICASX_EXPR;
     all_cases_con = FALSE;
     continue;
    } 
   wp = &(__contab[ndp->ru.xvi]);
   if (ndp->szu.xclen > WBITS)
    {
     /* even if wider than WBITS, if all a/b high 0, still simple number */ 
     wlen = wlen_(ndp->szu.xclen);
     if (vval_is0_(&(wp[1]), ndp->szu.xclen - WBITS) 
      && vval_is0_(&(wp[wlen]), ndp->szu.xclen - WBITS))
      {
       icasxp->aval = wp[0];
       icasxp->bval = wp[wlen];
      }
     /* wide number still treated as expr - peep hole will improve */
     else
      {
       icasxp->cxtyp = ICASX_EXPR;
       all_cases_con = FALSE;
       continue;
      }
    }
   else { icasxp->aval = wp[0]; icasxp->bval = wp[1]; }

   if (icasxp->bval == 0) icasxp->cxtyp = ICASX_NONXZNUM;
   else { *has_xznum = TRUE; icasxp->cxtyp = ICASX_XZNUM; }
  }
 return(all_cases_con);
}

/*
 * return T if expr has user function call
 *
 * can't use has non sys func v fx3 call that is for const exprs here
 * LOOKATME - duplicate of this rout in fx3 but think should keep separate
 */
static int32 igen_xpr_hasfcall(struct expr_t *ndp)
{
 struct sy_t *syp;

 if (ndp->optyp == FCALL)
  {
   syp = ndp->lu.x->lu.sy;
   if (syp->sytyp != SYM_SF) return(TRUE);
  }
 if (__isleaf(ndp)) return(FALSE);

 if (ndp->lu.x != NULL) { if (igen_xpr_hasfcall(ndp->lu.x)) return(TRUE); }
 if (ndp->ru.x != NULL) { if (igen_xpr_hasfcall(ndp->ru.x)) return(TRUE); }
 return(FALSE);
}

/*
 * return T if has case has any duplicated select expressions
 *
 * SJM 11/07/06 - even if normally could be a jump table if duplicates
 * select expressions, the expressions are unreachable so must leave
 * as case compare list here since probably can do much better optimizing
 * in bbopt
 */
static int32 has_duplicated_cases(struct icasx_t *icasxtab)
{
 int32 nxi, nxi2;
 struct icasx_t *icasxp, *icasxp2;

 /* SJM 06/22/06 - just init to satisfy lint - always set 1st time */ 
 for (nxi = 0;; nxi++)
  {
   icasxp = &(icasxtab[nxi]);
   if (icasxp->cxtyp == ICASX_ENDMARK) break;
   for (nxi2 = nxi + 1;; nxi2++)
    {
     icasxp2 = &(icasxtab[nxi2]);
     if (icasxp2->cxtyp == ICASX_ENDMARK) break;

     if (icasxp->aval == icasxp2->aval && icasxp->bval == icasxp2->bval)
      return(TRUE);
   }
 }
 return(FALSE);
}

/*
 * compute max and min value among all case item numeric expr here
 * not called unless all expr's non x/z numeric
 *
 * do not worry about casex/casez here although will probably stop tab form
 * need to find int min max since could subtract for offset - LOOKATME
 */
static void get_casxpr_minmax(struct icasx_t *icasxtab, word32 *cmax,
 word32 *cmin) 
{
 int32 nxi;
 struct icasx_t *icasxp;

 /* SJM 06/22/06 - just init to satisfy lint - always set 1st time */ 
 *cmin = *cmax = 0;
 for (nxi = 0;; nxi++)
  {
   icasxp = &(icasxtab[nxi]);
   if (icasxp->cxtyp == ICASX_ENDMARK) break;

   if (nxi == 0) { *cmax = *cmin = icasxp->aval; continue; }
   if (icasxp->aval > *cmax) *cmax = icasxp->aval;
   else if (icasxp->aval < *cmin) *cmin = icasxp->aval;
  }
}

/*
 * compute max used width in bits when some contain x/z (high non 0 bit)
 * 
 * not called unless all expr's numeric (possibly x/z)
 * jump tab ndx must match both a and b parts so only up to 4 bits for now
 */
static int32 get_xzcas_maxwid(struct icasx_t *icasxtab)
{
 int32 nxi;
 int32 awid, bwid, maxwid;
 word32 av, bv;
 struct icasx_t *icasxp;

 maxwid = 0;
 for (nxi = 0;; nxi++)
  {
   icasxp = &(icasxtab[nxi]);
   if (icasxp->cxtyp == ICASX_ENDMARK) break;

   av = icasxp->aval;
   bv = icasxp->bval;
   awid = __trim1_0val(&av, icasxp->casx->szu.xclen);
   bwid = __trim1_0val(&bv, icasxp->casx->szu.xclen);
   if (awid > maxwid) maxwid = awid;
   if (bwid > maxwid) maxwid = bwid;
  } 
 return(maxwid);
}

/*
 * GEN VINSNS FOR CASE SELECTS
 */

/*
 * gen insns for non xz jump table case select
 *
 * SJM 10/02/05 - after2 must be default before after
 */
static void gen_jmptab_case_select(struct st_t *stp, struct icas_t *icastab,
 struct icasx_t *icasxtab, int32 has_dflt, struct csitem_t *dflt_csip,
 word32 cmax, word32 cmin, int32 sel_ti)
{
 int32 xpri, casi, is_sel_2state, srtyp;
 int32 selxlen, selwid, sel_signed, need_xprop;
 int32 sel_bpti, ndx_ti, ndx, cint_ti, selwidth, known_in_range;
 size_t jtabsiz;
 struct bblk_t *inrng_bbp, *after_bbp, *dflt_bbp, *case_bbp, *goto_bbp;
 struct icas_t *icasp;
#ifdef __XPROP__
 struct bblk_t *handlex_bbp;
#endif

 is_sel_2state = (__tmp_is_2state(sel_ti) || 
                  __is_constant_with_zero_bpart(sel_ti));
 if (is_sel_2state) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;
 selxlen = stp->st.scs.maxselwid;
 selwid = __get_tnwid(sel_ti);
 if (selwid < selxlen)
  { 
   if (stp->st.scs.csx->has_sign && !stp->st.scs.csx->unsgn_widen)
    sel_signed = TRUE;
   else sel_signed = FALSE;
   sel_ti = __gen_cnvt_srep_ifneeded(sel_ti, srtyp, selxlen, sel_signed,
    FALSE, TRUE); 
  }
 else
  {
   /* if scalar must convert to vec to get the parts */
   sel_ti = __gen_cnvt_srep_ifneeded(sel_ti, srtyp, __tntab[sel_ti].tnwid,
    __tntab[sel_ti].t_signed, FALSE, TRUE); 
  }

 jtabsiz = cmax - cmin + 1;
 /* DBG remove -- */
 if (jtabsiz > MAX_CASE_JMPTAB) __misc_terr(__FILE__, __LINE__); 
 /* --- */

 /* AIV 08/03/11 - added this optimization to check if value is in range */
 /* if select width is all possible values no reason to check in range */
 /* this was actually optimized out in cmp but need for new xprop code */
 known_in_range = FALSE;
 selwidth = (1 << selxlen) - 1;
 if ((cmin == 0) && (cmax == selwidth))
  {
   known_in_range = TRUE;
  }

 /* dflt becomes after if no case default */
 dflt_bbp = __alloc_bblk(FALSE);
 /* AIV 08/03/11 - handle xprop case which does special x checking */
#ifdef __XPROP__
 /* if xprop2 must check for x bits */
 need_xprop = FALSE;
 handlex_bbp = NULL;
 if (__xprop2 && stp->xprop_eligible && !is_sel_2state) 
  {
   need_xprop = TRUE;
   handlex_bbp = __alloc_bblk(TRUE);
   goto_bbp = handlex_bbp;
  }
 else goto_bbp = dflt_bbp; 
#else
 need_xprop = FALSE;
 goto_bbp = dflt_bbp; 
#endif

 sel_bpti = -1;
 if (!is_sel_2state)
  {
   sel_bpti = __get_bpti(sel_ti);
   case_bbp = __alloc_bblk(FALSE);

   /* AIV 09/15/05 - as of now this is optimized only for cases that have */
   /* constants that have no b part so if selector has b part it is false */
   __emit_jmp_0(case_bbp, goto_bbp, sel_bpti);

   __start_bblk(case_bbp);
  }

 /* subtract min to normalize select value so jmp tab indexed with 0 */
 if (cmin != 0)
  {
   /* subtracting min is same as adding inverse for negative */
   cint_ti = __gen_cint_tn(cmin); 
   ndx_ti = __emit_sub(WBITS, sel_ti, cint_ti);
  }
 else ndx_ti = sel_ti;

 if (!known_in_range)
  {
   /* AIV 03/03/09 - better range checking code - can be done with one cmpl */
   cint_ti = __gen_cint_tn(jtabsiz); 
   inrng_bbp = __alloc_bblk(FALSE);
   __emit_jmp_cmp(inrng_bbp, goto_bbp, cint_ti, ndx_ti, CC_JGT);
   __start_bblk(inrng_bbp);
  }

 /* make sure enough room in the design wide ndx jmp bb ptr table */
 if (jtabsiz >= __ndxjmp_bbtab_siz) __grow_ndxjmpbbtab(jtabsiz);

 if (has_dflt) after_bbp = __alloc_bblk(FALSE); else after_bbp = dflt_bbp;

 for (xpri = 0; xpri < jtabsiz; xpri++) __ndxjmp_bbtab[xpri] = goto_bbp;
 
 /* set the ndx jmp bblk ptrs */
 for (xpri = 0;; xpri++) 
  {
   /* tab may be large and dense but still jump table if min-max not large */
   if (icasxtab[xpri].cxtyp == ICASX_ENDMARK) break;
   casi = icasxtab[xpri].cas_tabi;
   ndx = icasxtab[xpri].aval - cmin;
   __ndxjmp_bbtab[ndx] = icastab[casi].cstmt_bbp;
  }
  
 /* SJM 01/23/07 - since building new bigger tab with non dup sets */
 /* do not alloc - just pass the filled reused global ndx jmp tab */ 
 __emit_ndx_jmp(ndx_ti, __ndxjmp_bbtab, jtabsiz);

 /* generate the eval case stmt code */
 for (casi = 0;; casi++)
  {
   icasp = &(icastab[casi]);
   /* SJM 03/17/05 - notice icastab has moved default to end */ 
   if (icasp->end_mark) break;
   __start_bblk(icasp->cstmt_bbp);

   /* if gets here know it is nested case stmt - need to do the xprop st lst */
   gen_stlst(icastab[casi].csitem->csist, TRUE);

   /* works because case forward jumps do not gen insns (only backward) */
   /* after2 can be same as after if no default */
   __emit_jmp(after_bbp);
  }
#ifdef __XPROP__
 /* AIV 08/03/11 - if xprop and selector has x/z handle x/z prop list */
 if (need_xprop)
  {
   struct bblk_t *xlist_bbp;
   struct st_t *xlist_stp;

   xlist_stp = stp->st.scs.xprop_lstp;
   /* DBG remove -- */
   /* AIV 10/26/10 - this can actually be NULL for empty block */
   //if (xlist_stp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */ 

   __start_bblk(handlex_bbp);

   if (has_dflt)
    {
     xlist_bbp = __alloc_bblk(TRUE);
     __emit_jmp_0(dflt_bbp, xlist_bbp, sel_bpti);

     __start_bblk(dflt_bbp);
     gen_stlst(dflt_csip->csist, TRUE);
     __emit_jmp(after_bbp);

     __start_bblk(xlist_bbp);
     /* if xprop trace on record stmt */
     if (__xprop_trace_on) 
      {
       gen_xprop_trace_write(stp, sel_ti, sel_bpti, selxlen);
      }

     gen_stlst(xlist_stp, TRUE);
    }
   else
    {
     /* if xprop trace on record stmt */
     if (__xprop_trace_on) 
      {
       gen_xprop_trace_write(stp, sel_ti, sel_bpti, selxlen);
      }
     gen_stlst(xlist_stp, TRUE);
    }

   __start_bblk(after_bbp);
   return;
  }
#endif


 if (has_dflt)
  {
   __start_bblk(dflt_bbp);
   /* if gets here know it is nested case stmt - need to do the xprop st lst */
   gen_stlst(dflt_csip->csist, TRUE);
   __start_bblk(after_bbp);
  }
 else __start_bblk(after_bbp);
}

/*
 * grow ndxjmp table of pointers to basic blocks
 */
extern void __grow_ndxjmpbbtab(size_t addtabels)
{
 size_t old_tabsiz, osize, nsize;

 /* AIV 06/17/09 - changed these to use size_t */
 old_tabsiz = __ndxjmp_bbtab_siz;
 osize = old_tabsiz*sizeof(struct bblk_t *);
 /* SJM 03/29/05 - 3/2 growth may not be large enough for larg tab */ 
 /* make sure add enough new area */
 __ndxjmp_bbtab_siz = (3*__ndxjmp_bbtab_siz)/2 + addtabels; 
 nsize = __ndxjmp_bbtab_siz*sizeof(struct bblk_t *);
 
 __ndxjmp_bbtab = (struct bblk_t **)
  __my_realloc(__ndxjmp_bbtab, osize, nsize);
}

/*
 * gen insns for xz jump table case select (con only be 4 bits or narrower)
 */
static void gen_xzjmptab_case_select(struct st_t *stp, struct icas_t *icastab,
 struct icasx_t *icasxtab, int32 has_dflt, struct csitem_t *dflt_csip,
 int32 maxwid, int32 sel_apti)
{
 int32 xpri, casi, need_xprop;
 int32 sel_bpti, rng_apti, rng_bpti, ndx_ti, ndx2_ti;
 int32 sel_signed, selxlen, tabndxi, selwid, cint_ti;
 size_t jtabsiz;
 struct bblk_t *inrng_bbp, *after_bbp, *dflt_bbp, *goto_bbp;
 struct icas_t *icasp;
 struct icasx_t *icasxp;
#ifdef __XPROP__
 struct bblk_t *handlex_bbp;
#endif

 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);

 selxlen = stp->st.scs.maxselwid;
 selwid = __get_tnwid(sel_apti);
 if (selwid < selxlen)
  { 
   if (stp->st.scs.csx->has_sign && !stp->st.scs.csx->unsgn_widen)
    sel_signed = TRUE;
   else sel_signed = FALSE;
   sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_VEC, selxlen, sel_signed,
    FALSE, TRUE); 
  }
 else
  {
   /* if scalar must convert to vec to get the parts */
   sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_VEC, 
    __tntab[sel_apti].tnwid, __tntab[sel_apti].t_signed, FALSE, TRUE); 
  }
 sel_bpti = __get_bpti(sel_apti);
 cint_ti = __gen_cint_tn(~(__masktab[maxwid]));
 rng_apti = __emit_bin_bitand(WBITS, sel_apti, cint_ti);
 rng_bpti = __emit_bin_bitand(WBITS, sel_bpti, cint_ti);

 /* after may be default or after if no default */
 dflt_bbp = __alloc_bblk(FALSE);
 inrng_bbp = __alloc_bblk(FALSE);

 __emit_jmpor_0(inrng_bbp, dflt_bbp, rng_apti, rng_bpti);
 __start_bblk(inrng_bbp);

 /* since combining a and b parts, never sign extend left shift */
 cint_ti = __gen_cint_tn(maxwid);
 ndx_ti = __emit_shiftl(WBITS, cint_ti, sel_bpti);
 /* kow high sel bits for both a and b parts 0 */
 ndx2_ti = __emit_bin_bitor(WBITS, sel_apti, ndx_ti);

 jtabsiz = 1 << (2*maxwid);
 /* make sure enough room in the design wide ndx jmp bb ptr table */
 if (jtabsiz >= __ndxjmp_bbtab_siz) __grow_ndxjmpbbtab(jtabsiz);

 if (has_dflt) after_bbp = __alloc_bblk(FALSE); else after_bbp = dflt_bbp;

 /* initialize all jump table case labels to default (or after) */ 
#ifdef __XPROP__
 /* AIV 08/03/11 - handle xprop case which does special x checking */
 handlex_bbp = NULL;
 if (__xprop2 && stp->xprop_eligible)
  {
   handlex_bbp = __alloc_bblk(TRUE);
   goto_bbp = handlex_bbp;
   need_xprop = TRUE;
  }
 else 
  {
    /* SJM 10/02/05 - must jump to default block if present */
   need_xprop = FALSE;
   goto_bbp = dflt_bbp;
  }
#else
   need_xprop = FALSE;
   goto_bbp = dflt_bbp;
#endif
 /* initialize all jump table case labels to default (or after) */ 
 for (xpri = 0; xpri < jtabsiz; xpri++) __ndxjmp_bbtab[xpri] = goto_bbp;

 /* go thru each expr, fill jmptab ndx of sel val that run time produces */
 for (xpri = 0;; xpri++) 
  {
   icasxp = &(icasxtab[xpri]);
   /* SJM 03/18/05 - must exit at end mark */
   if (icasxp->cxtyp == ICASX_ENDMARK) break;

   /* DBG remove -- */
   if ((icasxp->aval & ~(__masktab[maxwid])) != 0
    || (icasxp->bval & ~(__masktab[maxwid])) != 0)
    __misc_terr(__FILE__, __LINE__);
   /* --- */

   icasp = &(icastab[icasxp->cas_tabi]);
   tabndxi = (int) (icasxp->aval | (icasxp->bval << maxwid));
   __ndxjmp_bbtab[tabndxi] = icasp->cstmt_bbp;
  }

 /* SJM 01/23/07 - since building new bigger tab with non dup sets */
 /* do not alloc - just pass the filled reused global ndx jmp tab */ 
 __emit_ndx_jmp(ndx2_ti, __ndxjmp_bbtab, jtabsiz);

 /* generate the eval case stmt code */
 for (casi = 0;; casi++)
  {
   icasp = &(icastab[casi]);
   if (icasp->end_mark) break;

   __start_bblk(icasp->cstmt_bbp);

   /* if gets here know it is nested case stmt - need to do the xprop st lst */
   gen_stlst(icastab[casi].csitem->csist, TRUE);
   /* works because case forward jumps do not gen insns (only backward) */

   /* if no default after2 same as after */
   __emit_jmp(after_bbp);
  }

#ifdef __XPROP__
 /* AIV 08/03/11 - if xprop and selector has x/z handle x/z prop list */
 if (need_xprop)
  {
   struct bblk_t *xlist_bbp;
   struct st_t *xlist_stp;

   xlist_stp = stp->st.scs.xprop_lstp;
   /* DBG remove -- */
   /* AIV 10/26/10 - this can actually be NULL for empty block */
   //if (xlist_stp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */ 

   __start_bblk(handlex_bbp);

   if (has_dflt)
    {
     xlist_bbp = __alloc_bblk(TRUE);
     __emit_jmp_0(dflt_bbp, xlist_bbp, sel_bpti);

     __start_bblk(dflt_bbp);
     gen_stlst(dflt_csip->csist, TRUE);
     __emit_jmp(after_bbp);

     __start_bblk(xlist_bbp);
     gen_stlst(xlist_stp, TRUE);
     /* if xprop trace on record stmt */
     if (__xprop_trace_on) 
      {
       gen_xprop_trace_write(stp, sel_apti, sel_bpti, selxlen);
      }
    }
   else 
    {
     if (__xprop_trace_on) 
      {
       gen_xprop_trace_write(stp, sel_apti, sel_bpti, selxlen);
      }
     gen_stlst(xlist_stp, TRUE);
    }

   __start_bblk(after_bbp);
   if (stp->stnxt != NULL) __pop_cc_stmt();
   return;
  }
#endif

 if (has_dflt)
  {
   __start_bblk(dflt_bbp);
   /* if gets here know it is nested case stmt - need to do the xprop st lst */
   gen_stlst(dflt_csip->csist, TRUE);
   __start_bblk(after_bbp);
  }
 else __start_bblk(after_bbp);

 if (stp->stnxt != NULL) __pop_cc_stmt();
}

/*
 * gen insns for simple list form case stmts
 *
 * follows interpreter exec case since general expression list match
 * algorithm required
 */
static void gen_list_case_select(struct st_t *stp, struct icas_t *icastab,
 struct icasx_t *icasxtab, int32 has_dflt, struct csitem_t *dflt_csip,
 int32 all_cases_con, int32 has_xznum, int32 nitems)
{
 struct expr_t *selxp;

 selxp = stp->st.scs.csx;
 if (selxp->is_real || selxp->cnvt_to_real)
  {
   gen_real_list_case(stp, icastab, icasxtab, has_dflt, dflt_csip);
   return;
  }
 gen_list_case(stp, icastab, icasxtab, has_dflt, dflt_csip, all_cases_con, 
   has_xznum, nitems);
}

/*
 * gen general compare list case statement list visnsn for reals
 *
 * casex and casez when either select or match is real are same as case
 */
static void gen_real_list_case(struct st_t *stp, struct icas_t *icastab,
 struct icasx_t *icasxtab, int32 has_dflt, struct csitem_t *dflt_csip)
{
 int32 sel_ti, nxi, match_ti, rdiff_ti, fabs_ti;
 struct bblk_t *cond_bbp, *after_bbp;
 struct expr_t *matchxp;
 struct icasx_t *icasxp;

 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);

 /* compute the case type - determines operator to use */
 sel_ti = __gen_expr_eval(stp->st.scs.csx, -1);

 /* if select expr not real convert it */
 if (stp->st.scs.csx->cnvt_to_real)
  {
   sel_ti = __gen_to_r_cnvt(sel_ti, TRUE, SR_VEC);
  }

 /* generate the compare and jump iops - one for each expr */
 cond_bbp = NULL;
 after_bbp = __alloc_bblk(FALSE);
 for (nxi = 0;; nxi++)
  {
   icasxp = &(icasxtab[nxi]);
   if (icasxp->cxtyp == ICASX_ENDMARK) break;

   matchxp = icasxp->casx;
   match_ti = __gen_expr_eval(matchxp, -1);

   if (matchxp->cnvt_to_real)
    {
     match_ti = __gen_to_r_cnvt(match_ti, TRUE, SR_VEC);
    }
   cond_bbp = __alloc_bblk(FALSE);
  
   /* since taking abs operands can be in either order */
   rdiff_ti = __emit_sub_real(sel_ti, match_ti);
   __tntab[rdiff_ti].t_real = TRUE;
   __tntab[rdiff_ti].tn_used_wide = TRUE;

   fabs_ti = __emit_real_abs(rdiff_ti);
   __tntab[fabs_ti].t_real = TRUE;
   __tntab[fabs_ti].tn_used_wide = TRUE;

   __emit_jmp_real_eps_cmp(icastab[icasxp->cas_tabi].cstmt_bbp, cond_bbp,
    fabs_ti);

   /* AIV 10/21/05 - only generate one epxr == case if block not init */
   /* this is needed for the list case matching case */
   if (icastab[icasxp->cas_tabi].cstmt_bbp->ihd == NULL)
    {
     __start_bblk(icastab[icasxp->cas_tabi].cstmt_bbp);
     gen_stlst(icastab[icasxp->cas_tabi].csitem->csist, TRUE);
     __emit_jmp(after_bbp);
    }

   /* AIV LOOKATME - cond_bbp always needs to be generated - always used */
   /* here was the original code with if stmt */
   /* SJM 10/16/04 - also needed for last one since may be default */  
   __start_bblk(cond_bbp);
  }
 if (has_dflt)
  {
   gen_stlst(dflt_csip->csist, TRUE);
  }
 __start_bblk(after_bbp);

 if (stp->stnxt != NULL) __pop_cc_stmt();
}

/*
 * gen general list compare case statement list insns for case
 * also for casx and casz
 */
static void gen_list_case(struct st_t *stp, struct icas_t *icastab,
 struct icasx_t *icasxtab, int32 has_dflt, struct csitem_t *dflt_csip,
 int32 all_cases_con, int32 has_xznum, int32 nitems)
{
 int32 nxi, sel_ti, selxlen, selwid, matchwid, match_ti, selres_ti;
 int32 sel_signed, amtyp, is_sel_2state, srtyp, castyp, sel_bpti;
 struct icasx_t *icasxp;
 struct bblk_t *cond_bbp, *after_bbp, *dflt_bbp;

 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);

 sel_ti = __gen_expr_eval(stp->st.scs.csx, -1);
 sel_bpti = -1;

 castyp = stp->st.scs.castyp;
 if (castyp != CASEX && castyp != CASEZ)
  {
   is_sel_2state = (__tmp_is_2state(sel_ti) || 
                    __is_constant_with_zero_bpart(sel_ti));
  }
 else is_sel_2state = FALSE;

 if (is_sel_2state) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;

 selxlen = stp->st.scs.maxselwid;
 selwid = __get_tnwid(sel_ti);
 //AIV LOOKATME - why is narrow case the only one with signed check 
 sel_signed = FALSE;
 if (selwid < selxlen)
  { 
   if (stp->st.scs.csx->has_sign && !stp->st.scs.csx->unsgn_widen)
    sel_signed = TRUE;
   else sel_signed = FALSE;
  }
 sel_ti = __gen_cnvt_srep_ifneeded(sel_ti, srtyp, selxlen, sel_signed,
  FALSE, TRUE); 

 after_bbp = __alloc_bblk(FALSE);
 /* AIV 08/03/11 - if all case items are constant and non are xz then just */
 /* check one for an x value, if more than 4 items */
 dflt_bbp = NULL;

 /* AIV 02/13/12 - this optimization cannot be done need to match */
 /* the xs with 0/1s */
 //if (!is_sel_2state && all_cases_con && !has_xznum && nitems > 4)
 
 /* generate the compare and jump iops - one for each expr */
 cond_bbp = NULL;
 for (nxi = 0;; nxi++)
  {
   icasxp = &(icasxtab[nxi]);
   if (icasxp->cxtyp == ICASX_ENDMARK) break;

   match_ti = __gen_expr_eval(icasxp->casx, -1);
   matchwid = __get_tnwid(match_ti);
   if (matchwid > selxlen && selxlen > WBITS)
    {
     /* SJM 01/03/05 - LOOKATME - think this case is impossible */
     /* narrowing never signed */
     match_ti = __gen_cnvt_srep_ifneeded(match_ti, srtyp, selxlen,
      FALSE, FALSE, TRUE); 
    }
   else if (matchwid < selxlen)
    {
     if (stp->st.scs.csx->has_sign && !stp->st.scs.csx->unsgn_widen)
      sel_signed = TRUE;
     else sel_signed = FALSE;
     match_ti = __gen_cnvt_srep_ifneeded(match_ti, srtyp, selxlen,
      sel_signed, FALSE, TRUE); 
    }
   /* may have to swap between 2-state and 4-state */
   else if (srtyp != __tntab[match_ti].srtyp)
    {
     match_ti = __gen_cnvt_srep_ifneeded(match_ti, srtyp, selxlen,
      sel_signed, FALSE, TRUE); 
    }

   cond_bbp = __alloc_bblk(FALSE);
   /* gen case list form (not jump table) compare and jump insns */
   if (is_sel_2state) 
    {
     if (selxlen <= WBITS)
      {
       selres_ti = __emit_bin_bitxor(selxlen, sel_ti, match_ti);
      }
     else
      {
       selres_ti = __emit_cmp_wide(sel_ti, match_ti, wlen_(selxlen), TRUE, 
                    SR_SCAL2S);
      }
    }
   else
    {
     selres_ti = gen_eval_case_sel(stp->st.scs.castyp, selxlen, sel_ti,
       match_ti, stp);
    }
//AIV LOOKATME??????
   /* AIV 10/13/08 - there was a bug for this type of case stmt */
   /* with selector and case values constant - notice these should be */
   /* removed since they are known to never be true */
   /* doing this hack for now since these can be removed with value */
   /* tracking - but could be done here */
   /* case (1'b1) 1'b0: r = 0; (r2 == 6'd0): r = 1; endcase */
   /* if constant just move the value for now */
   if (__is_constant(selres_ti) && __tntab[selres_ti].tnwid <= WBITS) 
    {
     if (__tntab[selres_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG;
     else amtyp = AM_REG;
     selres_ti = __move_insn(TN_VAL, I_MOVA, amtyp, selres_ti);
    }

   __emit_jmp_0(icastab[icasxp->cas_tabi].cstmt_bbp, cond_bbp, selres_ti);

   /* AIV 10/21/05 - only generate one epxr == case if block not init */
   /* this is needed for the list case matching case */
   if (icastab[icasxp->cas_tabi].cstmt_bbp->ihd == NULL)
    {
     __start_bblk(icastab[icasxp->cas_tabi].cstmt_bbp);
     /* if gets here know is nested case stmt - need to do the xprop st lst */
     gen_stlst(icastab[icasxp->cas_tabi].csitem->csist, TRUE);
     __emit_jmp(after_bbp);
    }

   /* AIV LOOKATME - cond_bbp always needs to be generated - always used */
   /* here was the original code with if stmt */
   /* SJM 10/16/04 - also needed for last one since may be default */  
   __start_bblk(cond_bbp);
  }

#ifdef __XPROP__
 /* AIV 08/03/11 - handle xprop case which does special x checking */
 if (__xprop2 && !is_sel_2state && stp->xprop_eligible)
  {
   struct bblk_t *xlist_bbp;
   struct st_t *xlist_stp;

   xlist_stp = stp->st.scs.xprop_lstp;
   /* DBG remove -- */
   /* AIV 10/26/10 - this can actually be NULL for empty block */
   //if (xlist_stp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */ 

   if (has_dflt)
    {
     dflt_bbp = __alloc_bblk(TRUE);
     xlist_bbp = __alloc_bblk(TRUE);
     sel_bpti = __get_bpti(sel_ti);
     __emit_jmp_0(dflt_bbp, xlist_bbp, sel_bpti);

     __start_bblk(dflt_bbp);
     gen_stlst(dflt_csip->csist, TRUE);
     __emit_jmp(after_bbp);

     __start_bblk(xlist_bbp);
     gen_stlst(xlist_stp, TRUE);
     /* if xprop trace on record stmt */
     if (__xprop_trace_on) 
      {
       gen_xprop_trace_write(stp, sel_ti, sel_bpti, selxlen);
      }
    }
   else 
    {
     /* if xprop trace on record stmt */
     if (__xprop_trace_on) 
      {
       gen_xprop_trace_write(stp, sel_ti, sel_bpti, selxlen);
      }
     gen_stlst(xlist_stp, TRUE);
    }

   __start_bblk(after_bbp);

   if (stp->stnxt != NULL) __pop_cc_stmt();
   return;
  }
#endif

 if (has_dflt)
  {
   /* AIV 08/04/11 - if skipping due to x may have to execute default */
   if (dflt_bbp != NULL)
    {
     __start_bblk(dflt_bbp);
    }
   /* if gets here know it is nested case stmt - need to do the xprop st lst */
   gen_stlst(dflt_csip->csist, TRUE);
  }
 __start_bblk(after_bbp);

 if (stp->stnxt != NULL) __pop_cc_stmt();
}

/*
 * gen compare insns for list
 *
 * if missing b parts can gen much better code - also wide different
 * know the sizes match exactly and srep is svec
 */
static int32 gen_eval_case_sel(int32 castyp, int32 bsiz, int32 sel_apti,
 int32 match_apti, struct st_t *stp) 
{
 int32 sel_bpti, match_bpti;
 int32 t1_apti, t2_ti, t3_ti, selres_ti;


 /* AIV 01/04/06 - must convert it a vec to get the bpart */
 match_apti = __gen_cnvt_srep_ifneeded(match_apti, SR_VEC, 
  __tntab[match_apti].tnwid, FALSE, FALSE, FALSE); 

 if (bsiz > WBITS) 
  {
   t1_apti = gen_eval_wide_case_sel(castyp, sel_apti, match_apti, bsiz);
   return(t1_apti);
  }
 if (castyp == CASEX)
  {
   t1_apti = gen_eval_casex_sel(bsiz, sel_apti, match_apti, stp); 
   return(t1_apti);
  }
 if (castyp == CASEZ)
  {
   t1_apti = gen_eval_casez_sel(bsiz, sel_apti, match_apti, stp); 
   return(t1_apti);
  }
 t2_ti = __emit_bin_bitxor(bsiz, sel_apti, match_apti);
 sel_bpti = __get_bpti(sel_apti);
 match_bpti = __get_bpti(match_apti);
 t3_ti = __emit_bin_bitxor(bsiz, sel_bpti, match_bpti);

 /* SJM 02/18/05 - if had cint (no b parts) results - could use here */
 selres_ti = __emit_bin_bitor(WBITS, t2_ti, t3_ti); 
 /* this sets for entire b part but for other need the byte num to set */
 /* AIV 05/25/06 - no reason to set the bpart since it is never used */
 return(selres_ti);
}

/*
 * gen wide case select asm lib insns (either may not have b part) 
 *
 * same routine for all 3 since gens wrapper
 * also only possible srep is wide svec
 */
static int32 gen_eval_wide_case_sel(int32 castyp, int32 sel_apti,
 int32 match_apti, int32 selxlen)
{
 int32 t1_apti;

 if (castyp == CASE)
  {
// opcod = I WIDCAS; 
   t1_apti = __emit_widcas(sel_apti, match_apti, wlen_(selxlen));
  }
 else if (castyp == CASEX)
  {
// opcod = I WIDCASX;
   t1_apti = __emit_widcasx(sel_apti, match_apti, wlen_(selxlen));
  }
 else
// opcod = I WIDCASZ;
  {
   t1_apti = __emit_widcasz(sel_apti, match_apti, wlen_(selxlen));
  }

 return(t1_apti);
}

/*
 * expand casex select insn
 *
 * know the sizes (bsiz) match exactly and srep is svec
 */
static int32 gen_eval_casex_sel(int32 bsiz, int32 sel_apti,
 int32 match_apti, struct st_t *stp) 
{
 int32 sel_bpti, match_bpti, selres_ti, blen;
 int32 t1_ti, t2_ti, t3_ti, t4_ti, t5_ti;

 blen = __get_tnwid(sel_apti);
 /* AIV 01/13/06 - need to conver to get the bpart */
 /* LOOKATME - possible optimize for scalar selectors */
 sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_VEC, 
  blen, __tntab[sel_apti].t_signed, FALSE, FALSE); 

 sel_bpti = __get_bpti(sel_apti);
#ifdef __XPROP__
 /* AIV 08/03/11 - handle xprop case which does special x checking */
 if (__xprop2 && stp->xprop_eligible)
  {
   struct bblk_t *xz_bbp, *regular_bbp, *after_bbp;
   int32 res_ti;

   xz_bbp = __alloc_bblk(TRUE);
   regular_bbp = __alloc_bblk(FALSE);
   after_bbp = __alloc_bblk(FALSE);
   res_ti = __gen_tn(SR_CINT, bsiz);
   __emit_jmp_0(regular_bbp, xz_bbp, sel_bpti);
   __start_bblk(xz_bbp);
   t2_ti = __emit_bin_bitxor(bsiz, sel_apti, match_apti);
   match_bpti = __get_bpti(match_apti);
   t3_ti = __emit_bin_bitxor(bsiz, sel_bpti, match_bpti);
   selres_ti = __emit_bin_bitor(bsiz, t2_ti, t3_ti); 
   __emit_copy(WRDBYTES*wlen_(bsiz), selres_ti, res_ti); 

   __emit_jmp(after_bbp);
   /* do the same code as below */
   __start_bblk(regular_bbp);
   t1_ti = __emit_bin_bitxor(bsiz, sel_apti, match_apti);
   t2_ti = __emit_bin_bitxor(bsiz, sel_bpti, match_bpti);
   t3_ti = __emit_bin_bitor(bsiz, t1_ti, t2_ti); 

   t4_ti = __emit_bin_bitor(bsiz, sel_bpti, match_bpti);
   t5_ti = __emit_bitnot(bsiz, t4_ti);

   selres_ti = __emit_bin_bitand(bsiz, t3_ti, t5_ti);
   __emit_copy(WRDBYTES*wlen_(bsiz), selres_ti, res_ti); 

   __start_bblk(after_bbp);
   return(res_ti);
  }
#endif
 match_bpti = __get_bpti(match_apti);
 /* AIV 03/16/07 - this was above the conversion of sel_apti - must be after */
 t1_ti = __emit_bin_bitxor(bsiz, sel_apti, match_apti);
 t2_ti = __emit_bin_bitxor(bsiz, sel_bpti, match_bpti);
 t3_ti = __emit_bin_bitor(bsiz, t1_ti, t2_ti); 

 t4_ti = __emit_bin_bitor(bsiz, sel_bpti, match_bpti);
 t5_ti = __emit_bitnot(bsiz, t4_ti);

 /* AIV 02/10/09 - no need for b part result here */
 selres_ti = __emit_bin_bitand(bsiz, t3_ti, t5_ti);
 return(selres_ti);
}

/*
 * expand casez select insn
 *
 * if missing b parts can gen much better code - also wide different
 * know the sizes (bsiz) match exactly and srep is svec
 */
static int32 gen_eval_casez_sel(int32 bsiz, int32 sel_apti,
 int32 match_apti, struct st_t *stp) 
{
 int32 selres_ti, sel_bpti, match_bpti, mask_ti, blen;
 int32 t1_ti, t2_ti, t4_ti, t5_ti, t6_ti, t7_ti;
 
 blen = __get_tnwid(sel_apti);
 /* AIV 01/13/06 - need to conver to get the bpart */
 /* LOOKATME - possible optimize for scalar selectors */
 sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_VEC, blen, 
   __tntab[sel_apti].t_signed, FALSE, FALSE); 

 sel_bpti = __get_bpti(sel_apti);
#ifdef __XPROP__
 /* AIV 08/03/11 - handle xprop case which does special x checking */
 if (__xprop2 && stp->xprop_eligible)
  {
   struct bblk_t *xz_bbp, *regular_bbp, *after_bbp;
   int32 res_ti, t3_ti;

   xz_bbp = __alloc_bblk(TRUE);
   regular_bbp = __alloc_bblk(FALSE);
   after_bbp = __alloc_bblk(FALSE);
   res_ti = __gen_tn(SR_CINT, bsiz);
   __emit_jmp_0(regular_bbp, xz_bbp, sel_bpti);
   __start_bblk(xz_bbp);
   t2_ti = __emit_bin_bitxor(bsiz, sel_apti, match_apti);
   match_bpti = __get_bpti(match_apti);
   t3_ti = __emit_bin_bitxor(bsiz, sel_bpti, match_bpti);
   selres_ti = __emit_bin_bitor(bsiz, t2_ti, t3_ti); 
   __emit_copy(WRDBYTES*wlen_(bsiz), selres_ti, res_ti); 

   __emit_jmp(after_bbp);
   /* do the same code as below */
   __start_bblk(regular_bbp);

   t6_ti = __emit_bitnot(bsiz, sel_bpti);
   t1_ti = __emit_bin_bitor(bsiz, sel_apti, t6_ti); 
   match_bpti = __get_bpti(match_apti);
   t6_ti = __emit_bitnot(bsiz, match_bpti);
   t2_ti = __emit_bin_bitor(bsiz, match_apti, t6_ti); 
   mask_ti = __emit_bin_bitand(bsiz, t1_ti, t2_ti);
  
   t4_ti = __emit_bin_bitxor(bsiz, sel_apti, match_apti);
   t7_ti = __emit_bin_bitxor(bsiz, sel_bpti, match_bpti);
   t5_ti = __emit_bin_bitor(bsiz, t4_ti, t7_ti); 

   /* AIV 02/10/09 - no need for b part result here */
   selres_ti = __emit_bin_bitand(bsiz, t5_ti, mask_ti);
   __emit_copy(WRDBYTES*wlen_(bsiz), selres_ti, res_ti); 

   __start_bblk(after_bbp);
   return(res_ti);
  }
#endif

 t6_ti = __emit_bitnot(bsiz, sel_bpti);
 t1_ti = __emit_bin_bitor(bsiz, sel_apti, t6_ti); 
 /* SJM 02/18/05 - FIXME ??? - CHECK THESE THINK TMPS NOT SAME */
 match_bpti = __get_bpti(match_apti);
 t6_ti = __emit_bitnot(bsiz, match_bpti);
 t2_ti = __emit_bin_bitor(bsiz, match_apti, t6_ti); 
 mask_ti = __emit_bin_bitand(bsiz, t1_ti, t2_ti);

 t4_ti = __emit_bin_bitxor(bsiz, sel_apti, match_apti);
 t7_ti = __emit_bin_bitxor(bsiz, sel_bpti, match_bpti);
 t5_ti = __emit_bin_bitor(bsiz, t4_ti, t7_ti); 

 /* AIV 02/10/09 - no need for b part result here */
 selres_ti = __emit_bin_bitand(bsiz, t5_ti, mask_ti);
 return(selres_ti);
}

/*
 * gen code for forever loop
 */
static void gen_forever(struct st_t *stp)
{
 struct bblk_t *enter_bbp, *after_bbp;
 struct bblk_t *save_continue_bbp, *save_break_bbp;

 /* AIV 12/08/06 - empty block don't need to evaluate */
 if (stp->st.swh.lpst->stmttyp == S_STNONE) return;

 /* AIV 09/28/10 - save/restore for break/continue stmts */
 enter_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 save_continue_bbp = __loop_continue_bbp; 
 save_break_bbp = __loop_break_bbp;
 __loop_continue_bbp = enter_bbp; 
 __loop_break_bbp = after_bbp;

 __start_bblk(enter_bbp);
 gen_stlst(stp->st.swh.lpst, TRUE);
     
 /* SJM 08/05/05 - now goto do not gen insn so need loop jumps */
 __emit_jmp(enter_bbp);
 __start_bblk(after_bbp);
 __loop_continue_bbp = save_continue_bbp;
 __loop_break_bbp = save_break_bbp;
}

/*
 * ROUTINES TO GENERATE V INSNS FOR LOOP STMTS
 */

/*
 * gen insns for repeat setup stmt
 *
 * new scheme assumes that for wide a/b vectors the high part of packed
 * points to base of b part area
 */
static void gen_repsetup(struct st_t *stp)
{
 int32 lpcnt_apti, lpcnt_bpti, lpcnt2_apti, lpcnt2_bpti, cint_ti;
 int32 repcnt_adrti, t1_ti, t2_ti, is_2state;
 struct bblk_t *set1_bbp, *tst0_bbp, *nonxz_bbp, *stcnt_bbp, *done_bbp;
 struct expr_t *cntx;

 /* eval count expr */
 cntx = stp->stnxt->st.srpt.repx;

 /* do not need to generate any test for constants - can do at compile time */
 if (cntx->optyp == NUMBER || cntx->optyp == REALNUM)
  {
   gen_num_repsetup(stp);
   return;
  }

 
 lpcnt_apti = __gen_expr_eval(cntx, -1);
 is_2state = __tmp_is_2state(lpcnt_apti);

 set1_bbp = __alloc_bblk(FALSE);
 nonxz_bbp = __alloc_bblk(FALSE);
 stcnt_bbp = __alloc_bblk(FALSE);
 done_bbp = __alloc_bblk(FALSE);

 /* make sure either have 2v (i.e. unchanged) or an word (ab) pr tmp */ 
 if (cntx->is_real)
  {
   lpcnt2_apti = __gen_cnvt_srep_ifneeded(lpcnt_apti, SR_VEC, WBITS, TRUE,
    TRUE, FALSE); 
  }
 else
  {
   if (!is_2state)
    {
     lpcnt2_apti = __gen_cnvt_srep_ifneeded(lpcnt_apti, SR_VEC, WBITS,
       cntx->has_sign, FALSE, FALSE); 
    }
   else lpcnt2_apti = lpcnt_apti;
  }

 repcnt_adrti = __gen_repeat_bp_tn(stp->stnxt);

 /* if has b part must test if b part non 0 and if non 0, set counter 0 */ 
 if (!cntx->is_real && !is_2state)
  {
   tst0_bbp = __alloc_bblk(TRUE);
   lpcnt2_bpti = __get_bpti(lpcnt2_apti);
   __emit_jmp_0(tst0_bbp, set1_bbp, lpcnt2_bpti);
   __start_bblk(tst0_bbp);
  }

 /* AIV 01/25/06 - need to use converted count to get b part */
 if (!is_2state)
  {
   lpcnt_bpti = __get_bpti(lpcnt2_apti);
   t2_ti = __emit_bin_bitxor(WBITS, lpcnt_apti, lpcnt_bpti);
   __emit_jmp_0(set1_bbp, nonxz_bbp, t2_ti);
  }
 else __emit_jmp(nonxz_bbp);

 __start_bblk(set1_bbp);

 /* since repeat starts even first time by dec - 1 is skip */
 __emit_store_cint(repcnt_adrti, 1, WRDBYTES);
 __emit_jmp(done_bbp);

 __start_bblk(nonxz_bbp);

 if (cntx->has_sign)
  {
   cint_ti = __gen_cint_tn(0);
   __emit_jmp_sgn_cmp(stcnt_bbp, set1_bbp, lpcnt_apti, cint_ti, CC_JGT);
  }

 /* this inserts the unconditional jump */
 __start_bblk(stcnt_bbp); 

 /* starts one higher than evaled expr count */
 cint_ti = __gen_cint_tn(1);
 t1_ti = __emit_add(WBITS, lpcnt2_apti, cint_ti);

 __emit_copy(WRDBYTES, t1_ti, repcnt_adrti);

 __start_bblk(done_bbp);
}

/*
 * gen insns for repeat stmt
 * called for repeat setup statement moves to next that always repeat
 *
 * SJM 08/07/05 - REWRITEME - now can be much simpler with goto's gened here
 */
static void gen_repeat(struct st_t *stp)
{
 int32 repcnt_adrti, t1_ti, cint_ti;
 struct bblk_t *enter_bbp, *loop_bbp, *after_bbp;
 struct bblk_t *save_continue_bbp, *save_break_bbp;

 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);

 enter_bbp = __alloc_bblk(FALSE);
 /* AIV 11/03/09 - mark as enter block for alignment */
 enter_bbp->is_enter_loop = TRUE;
 loop_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 /* AIV 09/28/10 - save/restore for break/continue stmts */
 save_continue_bbp = __loop_continue_bbp; 
 save_break_bbp = __loop_break_bbp;
 __loop_continue_bbp = loop_bbp; 
 __loop_break_bbp = after_bbp;

 __start_bblk(enter_bbp);

 //SJM? - extra but optimizer should remove 2nd if can */
 repcnt_adrti = __gen_repeat_bp_tn(stp);

 cint_ti = __gen_cint_tn(1);
 t1_ti = __emit_sub(WBITS, repcnt_adrti, cint_ti);
 
 __emit_jmp_0(after_bbp, loop_bbp, t1_ti);
 __start_bblk(loop_bbp);

 __emit_copy(WRDBYTES, t1_ti, repcnt_adrti);

 gen_stlst(stp->st.srpt.repst, TRUE);

 /* SJM 08/05/05 - now goto do not gen insn so need loop jumps */
 __emit_jmp(enter_bbp);
 __start_bblk(after_bbp);

 if (stp->stnxt != NULL) __pop_cc_stmt();
 __loop_continue_bbp = save_continue_bbp;
 __loop_break_bbp = save_break_bbp;
}

/*
 * gen insns for number/real const repeat count that fits in 32 bits 
 */
static void gen_num_repsetup(struct st_t *stp)
{
 int32 i1, repcnt, repcnt_adrti, cint_ti;
 word32 *wp;
 double d1;
 struct expr_t *cntx;

 /* eval count expr */
 cntx = stp->stnxt->st.srpt.repx;
 wp = &(__contab[cntx->ru.xvi]);
 if (cntx->is_real)
  {
   memcpy(&d1, wp, 2*WRDBYTES); 
   i1 = (int32) d1;
  }
 else
  {
   if (cntx->szu.xclen > WBITS)
    {
     if (!vval_is0_(wp, cntx->szu.xclen)) i1 = 0;
     else if (!vval_is0_(&(wp[1]), cntx->szu.xclen - WBITS)) i1 = 0;
     else i1 = (int32) wp[0];
    }
   else
    {
     if (wp[1] != 0) i1 = 0; else i1 = (int32) wp[0];
    }
  }
 if (cntx->has_sign)
  {
   if (i1 < 0) i1 = 0;
  }
 repcnt = (int32) (((word32) i1) + 1);
 cint_ti = __gen_cint_tn(repcnt);

 repcnt_adrti = __gen_repeat_bp_tn(stp->stnxt);
 __emit_copy(WRDBYTES, cint_ti, repcnt_adrti);
}

/*
 * gen insns for while stmt
 */
static void gen_while(struct st_t *stp)
{
 int32 while_ti, while_bpti, t1_ti, t2_ti, blen, cint_ti, srtyp, is_2state;
 struct expr_t *condx;
 struct bblk_t *body_bbp, *after_bbp, *enter_bbp;
 struct bblk_t *save_continue_bbp, *save_break_bbp;

 condx = stp->st.swh.lpx;
 /* AIV 11/27/06 - handle constant while condition case */
 if (__cvc_is_const_expr(condx)) 
  {
   gen_while_const(stp); 
   return;
  }
 body_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 enter_bbp = __alloc_bblk(FALSE);
 /* AIV 09/28/10 - save/restore for break/continue stmts */
 save_continue_bbp = __loop_continue_bbp; 
 save_break_bbp = __loop_break_bbp;
 __loop_continue_bbp = enter_bbp;
 __loop_break_bbp = after_bbp;
 /* AIV 11/03/09 - mark as enter block for alignment */
 enter_bbp->is_enter_loop = TRUE;

 /* gen insns to eval select self determine width expr */
 __start_bblk(enter_bbp);
 while_ti = __gen_expr_eval(condx, -1);
 /* if scalar must convert to vec to get the parts */
 /* AIV 08/25/08 - if scalar just load value from scalar table value */
 srtyp = __tntab[while_ti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   /* AIV 03/09/09 - no need for scalar index table here */
   /* only need to compare for 1 */
   cint_ti = __gen_cint_tn(1);
   __emit_jmp_eq(body_bbp, after_bbp, cint_ti, while_ti);
  }
 else
  {
   is_2state = __tmp_is_2state(while_ti);

   if (!is_2state)
    {
     while_ti = __gen_cnvt_srep_ifneeded(while_ti, SR_VEC, 
      __tntab[while_ti].tnwid, __tntab[while_ti].t_signed, FALSE, TRUE); 
     while_bpti = __get_bpti(while_ti);
     /* ap[0] & ~bp[0] */
     blen = __get_tnwid(while_ti);
     t1_ti = __emit_bitnot(blen, while_bpti); 
     t2_ti = __emit_bin_bitand(blen, while_ti, t1_ti);
     __emit_jmp_0(after_bbp, body_bbp, t2_ti);
    }
   else __emit_jmp_0(after_bbp, body_bbp, while_ti);
  }

 __start_bblk(body_bbp);
 gen_stlst(stp->st.swh.lpst, TRUE);

 __emit_jmp(enter_bbp);
 __start_bblk(after_bbp);
 __loop_continue_bbp = save_continue_bbp;
 __loop_break_bbp = save_break_bbp;
}

/*
 * generate code for a do-while loop
 */
static void gen_do_while(struct st_t *stp)
{
 int32 while_ti, while_bpti, t1_ti, t2_ti, blen, cint_ti, srtyp, is_2state;
 struct expr_t *condx;
 struct bblk_t *after_bbp, *enter_bbp;
 struct bblk_t *save_continue_bbp, *save_break_bbp;

 condx = stp->st.swh.lpx;
 if (__cvc_is_const_expr(condx)) 
  {
   gen_do_while_const(stp); 
   return;
  }
 after_bbp = __alloc_bblk(FALSE);
 enter_bbp = __alloc_bblk(FALSE);
 /* AIV 09/28/10 - save/restore for break/continue stmts */
 save_continue_bbp = __loop_continue_bbp; 
 save_break_bbp = __loop_break_bbp;
 __loop_continue_bbp = enter_bbp;
 __loop_break_bbp = after_bbp;
 enter_bbp->is_enter_loop = TRUE;

 /* gen insns to eval select self determine width expr */
 __start_bblk(enter_bbp);
 gen_stlst(stp->st.swh.lpst, TRUE);

 while_ti = __gen_expr_eval(condx, -1);
 /* if scalar must convert to vec to get the parts */
 srtyp = __tntab[while_ti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   /* only need to compare for 1 */
   cint_ti = __gen_cint_tn(1);
   __emit_jmp_eq(enter_bbp, after_bbp, cint_ti, while_ti);
  }
 else
  {
   is_2state = __tmp_is_2state(while_ti);

   if (!is_2state)
    {
     while_ti = __gen_cnvt_srep_ifneeded(while_ti, SR_VEC, 
      __tntab[while_ti].tnwid, __tntab[while_ti].t_signed, FALSE, TRUE); 
     while_bpti = __get_bpti(while_ti);
     /* ap[0] & ~bp[0] */
     blen = __get_tnwid(while_ti);
     t1_ti = __emit_bitnot(blen, while_bpti); 
     t2_ti = __emit_bin_bitand(blen, while_ti, t1_ti);
     __emit_jmp_0(after_bbp, enter_bbp, t2_ti);
    }
   else __emit_jmp_0(after_bbp, enter_bbp, while_ti);
  }

 __start_bblk(after_bbp);
 __loop_continue_bbp = save_continue_bbp;
 __loop_break_bbp = save_break_bbp;
}

/*
 * AIV 11/27/06 - added while stmt lower were condition is a know constant
 * - if condition is T treate like a forever stmt
 * - if condition if F mark code unreachable and don't lower
 */
static void gen_while_const(struct st_t *stp)
{
 struct xstk_t *xsp;
 int32 execute;
 word32 val;
 struct expr_t *condx;
 struct bblk_t *enter_bbp, *after_bbp;
 struct bblk_t *save_continue_bbp, *save_break_bbp;

 /* AIV 06/21/07 - removed warning messages user must run +interp to see */
 condx = stp->st.swh.lpx;
 xsp = __eval_xpr(condx);
 execute = FALSE;

 if (xsp->xslen <= WBITS)
  {
   /* SJM 07/20/00 - must convert to real if real */
   if (condx->is_real)
    {
     double d1;
  
     memcpy(&d1, xsp->ap, sizeof(double));
     __pop_xstk();
     /* must not emit informs from val if real */
     if (d1 != 0.0) execute = TRUE;
    }
   else
    {
     val = xsp->bp[0];
     if ((xsp->ap[0] & ~val) != 0L)
      {
       execute = TRUE;
      }
    }
   }
  else if (__cvt_lngbool(xsp->ap, xsp->bp, wlen_(xsp->xslen)) == 1)
   {
    execute = TRUE;
   }

 /* if never executed due to constant condition mark unreachable */
 if (!execute)
  {
   __pop_xstk();
   __mark_stlst_unreachable(__inst_mod, stp->st.swh.lpst);
   return;
  }
 /* AIV 09/28/10 - save/restore for break/continue stmts */
 save_continue_bbp = __loop_continue_bbp; 
 save_break_bbp = __loop_break_bbp;

 /* if constant condition always TRUE execute forever */
 enter_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 __loop_continue_bbp = enter_bbp; 
 __loop_break_bbp = after_bbp;

 /* gen insns to eval select self determine width expr */
 __start_bblk(enter_bbp);

 gen_stlst(stp->st.swh.lpst, TRUE);

 __emit_jmp(enter_bbp);
 /* AIV 03/14/07 - need a new block at the end because block cannot */
 /* have a jump in the middle of the block insn set */
 __start_bblk(after_bbp);
 __loop_continue_bbp = save_continue_bbp;
 __loop_break_bbp = save_break_bbp;
 __pop_xstk();
}

/*
 * generate code for a do-while loop where while(expr) is constant
 */
static void gen_do_while_const(struct st_t *stp)
{
 struct xstk_t *xsp;
 int32 execute, tmp;
 word32 val;
 struct expr_t *condx;
 struct bblk_t *enter_bbp, *after_bbp;
 struct bblk_t *save_continue_bbp, *save_break_bbp;

 condx = stp->st.swh.lpx;
 xsp = __eval_xpr(condx);
 execute = FALSE;

 if (xsp->xslen <= WBITS)
  {
   if (condx->is_real)
    {
     double d1;
  
     memcpy(&d1, xsp->ap, sizeof(double));
     __pop_xstk();
     if (d1 != 0.0) execute = TRUE;
    }
   else
    {
     val = xsp->bp[0];
     if ((xsp->ap[0] & ~val) != 0L)
      {
       execute = TRUE;
      }
    }
  }
 else if ((tmp = __cvt_lngbool(xsp->ap, xsp->bp, wlen_(xsp->xslen))) == 1)
  {
   execute = TRUE;
  }

 /* if while condition is false - just execute once */
 if (!execute) 
  {
   __pop_xstk();
   gen_stlst(stp->st.swh.lpst, TRUE);
   return;
  }

 save_continue_bbp = __loop_continue_bbp; 
 save_break_bbp = __loop_break_bbp;

 enter_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 __loop_continue_bbp = enter_bbp; 
 __loop_break_bbp = after_bbp;

 __start_bblk(enter_bbp);

 gen_stlst(stp->st.swh.lpst, TRUE);

 __emit_jmp(enter_bbp);
 /* AIV 03/14/07 - need a new block at the end because block cannot */
 /* have a jump in the middle of the block insn set */
 __start_bblk(after_bbp);
 __loop_continue_bbp = save_continue_bbp;
 __loop_break_bbp = save_break_bbp;
 __pop_xstk();
}


/*
 * gen insn for "for" stmt
 *
 * decompose to: 
 *
 *  for assign 
 *  L1: if (for termx F) goto past end of loop L2;
 *  <body>
 *  inc assign statement
 *  goto L1
 * L2:
 *
 * LOOKATME - where setting beg stp code for for
 * know cur iop stp is for stmt itself when called and this adjusts
 */
static void gen_for(struct st_t *stp)
{
 int32 term_ti, term_bpti, t1_ti, t2_ti, blen, cint_ti, srtyp, is_2state;
 struct bblk_t *enter_bbp, *body_bbp, *after_bbp;
 struct bblk_t *save_continue_bbp, *save_break_bbp, *inc_bbp;
 struct expr_t *termx;
 struct for_t *forp;
 struct st_t *stp2;
 
 forp = stp->st.sfor;
 /* AIV 09/28/10 - record continue/break blocks */
 save_continue_bbp = __loop_continue_bbp; 
 save_break_bbp = __loop_break_bbp;
 enter_bbp = __alloc_bblk(FALSE);
 /* AIV 11/03/09 - mark as enter block for alignment */
 enter_bbp->is_enter_loop = TRUE;
 body_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 inc_bbp = NULL;
 /* if has continue stmt need block to jump to */
 if (forp->has_continue)
  {
   inc_bbp = __alloc_bblk(FALSE);
  }
 __loop_continue_bbp = inc_bbp;
 __loop_break_bbp = after_bbp;

 __cur_ifrom_u.from_stp = stp;

 /* gen insns to eval select self determine width expr */
 __start_bblk(enter_bbp);
 termx = stp->st.sfor->fortermx;
 term_ti = __gen_expr_eval(termx, -1);
 /* AIV 08/15/08 - this could now evaluate to a scalar and need evaluate */
 /* scalar value */
 srtyp = __tntab[term_ti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   /* AIV 03/09/09 - no need for scalar index table here */
   /* only need to compare for 1 */
   cint_ti = __gen_cint_tn(1);
   __emit_jmp_eq(body_bbp, after_bbp, cint_ti, term_ti);
  }
 else
  {
   /* generate the conditional jump past end (loop exit) on F insn */
   /* AIV FIXME - need conversions ????? */
   /* ap[0] & ~bp[0] */
   is_2state = __tmp_is_2state(term_ti);
   if (!is_2state)
    {
     term_bpti = __get_bpti(term_ti);
     blen = __get_tnwid(term_ti);
     t1_ti = __emit_bitnot(blen, term_bpti); 
     t2_ti = __emit_bin_bitand(blen, term_ti, t1_ti);
     __emit_jmp_0(after_bbp, body_bbp, t2_ti);
    }
   else __emit_jmp_0(after_bbp, body_bbp, term_ti);
  }

 __start_bblk(body_bbp);

 /* generate insns of for body */
 /* if has continue stmt need block to jump to */
 /* forinc - inc stmt has been linked onto the body - just find the end */
 /* for continue to jump to */
 if (forp->has_continue)
  {
   for (stp2 = forp->forbody; stp2 != NULL;)
    {
     if (stp2 == forp->forinc)
      {
       __start_bblk(inc_bbp);
      }
     stp2 = gen_stmt(stp2, TRUE);
    }
 
    /* DBG remove -- */ 
   if (__cur_bbp == body_bbp) __misc_terr(__FILE__, __LINE__);
   /* ---- */ 
  }
 else gen_stlst(forp->forbody, TRUE);

 /* SJM 08/05/05 - now goto do not gen insn so need loop jumps */
 __emit_jmp(enter_bbp);
 __start_bblk(after_bbp);
 __loop_continue_bbp = save_continue_bbp;
 __loop_break_bbp = save_break_bbp;
}

/*
 * gen insns for wait stmt
 */
static void gen_wait(struct st_t *stp)
{
 int32 term_apti, term_bpti, tmp1_ti, cint_ti, schd_tev_ti;
 int32 tevp_ti, stmt_ent_ti, srtyp, is_2state, blen, t1_ti, has_bpart;
 struct bblk_t *body_bbp, *rearm_bbp, *after_bbp;
 struct bblk_t *eval_xpr_bbp, *repeat_wait_bbp;
 struct expr_t *termx;
 struct delctrl_t *dctp;
 struct ctev_t *ctevp;
 word32 val1;

 /* AIV 05/16/06 - the stp could already be entered here if so don't */
 /* create an enter point - this occurs with initial/always with */
 /* the first stmt a wait so don't need a new enter point */
 if (!stp->enter_created)
  {
   repeat_wait_bbp = __alloc_bblk(FALSE);
   eval_xpr_bbp = __alloc_bblk(FALSE);
   __emit_jmp(eval_xpr_bbp);

   __start_bblk(repeat_wait_bbp);
   repeat_wait_bbp->after_suspend = TRUE;
   __emit_enter_proc(stp);
   __start_bblk(eval_xpr_bbp);
  }

 termx = stp->st.swait.lpx;
 /* eval expr, if T, execute wait body starting with disarm (if needed */
 /* because not first time), if F, jump to insn to rearm wait */
 term_apti = __gen_expr_eval(termx, -1);
 is_2state = __tmp_is_2state(term_apti);

 /* if has b part need to convert to boolean 0 - "aval & ~bval" */
 /* i.e. if any bits x - then non 0 */
 /* FIXME - this should be expanded to and and not and z compare */
 term_bpti = -1;
 srtyp = __tntab[term_apti].srtyp;
 /* AIV 08/27/08 - no need to convert the scalar case gen_bin_cvt_bool */
 /* will handle as a value index from table */
 /* AIV 09/13/10 - do not convert it strenght scalar either */
 if (!is_2state && srtyp != SR_SCAL && srtyp != SR_SSCAL)
  {
   term_apti = __gen_cnvt_srep_ifneeded(term_apti, SR_VEC, 
    __tntab[term_apti].tnwid, __tntab[term_apti].t_signed, FALSE, TRUE); 
   /* if has b part need to convert to boolean 0 - "aval & ~bval" */
   /* i.e. if any bits x - then non 0 */
   /* FIXME - this should be expanded to and and not and z compare */
   term_bpti = __get_bpti(term_apti);
  }

 dctp = stp->st.swait.wait_dctp;
 /* AIV 05/16/09 - can have constant value here - causing misc_terr */
 if (__is_constant(term_apti)) 
  {
   /* AIV 08/03/11 - if constant x just set to x and return */
   /* AIV 12/29/11 - need to execute non-zero case here as T */
   val1 = fold_constant_bin_cvt_bool(term_apti, term_bpti, FALSE, &has_bpart);
   if (has_bpart || val1 != 0) 
    {
     if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);
     /* generate wait body stmt list insns */
     gen_stlst(stp->st.swait.lpst, TRUE);

     if (stp->stnxt != NULL) __pop_cc_stmt();
     return;
    }
   else 
    {
     after_bbp = __alloc_bblk(FALSE);
     goto rearm;
    }
  }
   
 body_bbp = __alloc_bblk(FALSE);
 rearm_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 blen = __get_tnwid(term_apti);
 /* AIV 09/10/10 - this should be just like if handling */
 /* do not use gen_bin_cvt_bool unless wide - because does extra */
 /* condition checking/jmps */
 if (!is_2state) 
  {
   if (srtyp == SR_SCAL || srtyp == SR_SSCAL)
    {
     if (srtyp == SR_SSCAL)
      {
       cint_ti = __gen_cint_tn(3);
       term_apti = __emit_bin_bitand(WBITS, cint_ti, term_apti);
      }
     cint_ti = __gen_cint_tn(1);
     __emit_jmp_eq(body_bbp, rearm_bbp, term_apti, cint_ti); 
    }
   else if (blen <= WBITS)
    {
     t1_ti = __emit_bitnot(WBITS, term_bpti);
     tmp1_ti = __emit_bin_bitand(WBITS, term_apti, t1_ti);
     __emit_jmp_0(rearm_bbp, body_bbp, tmp1_ti);
    }
   else
    {
     /* if wide use wrapper so doesn't check all words  */
     tmp1_ti = gen_bin_cvt_bool(term_apti, term_bpti);
     /* compare to 1 */
     cint_ti = __gen_cint_tn(1);
     __emit_jmp_eq(body_bbp, rearm_bbp, tmp1_ti, cint_ti); 
    }
  }
 else 
  {
   tmp1_ti = term_apti;
   cint_ti = __gen_cint_tn(1);
   __emit_jmp_eq(body_bbp, rearm_bbp, tmp1_ti, cint_ti); 
  }
 __start_bblk(body_bbp);

 /* wait condition true - disarm, exec body and done */
 /* fall thru and disarm wait before execing wait body */
 /* AIV 05/14/07 - inlined disarm wait better code - no need for wrapper */
 schd_tev_ti = __gen_dce_schd_tev(dctp);

 cint_ti = __gen_cint_tn((word32) NULL);
 __emit_copy(WRDBYTES, cint_ti, schd_tev_ti);

 if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);

 /* generate wait body stmt list insns */
 gen_stlst(stp->st.swait.lpst, TRUE);

 if (stp->stnxt != NULL) __pop_cc_stmt();

 /* goto end - event ctrl trigged and stmt list execed - done */
 __emit_jmp(after_bbp);

 /* event control triggered but wait expr F, rearm and wait again */
 __start_bblk(rearm_bbp);

rearm:
 ctevp = stp->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 

 tevp_ti = __gen_ctevp_adr_tn(ctevp);
 /* this also set th nxt stp to the wait */
 /* AIV 05/14/07 - inlined schedule rearm no need to pass statment */
 if (!__needs_thread_ctrl)
  {
   stmt_ent_ti = __gen_proc_enter_adr_tn(stp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;
  }
 else 
  {
   ctevp->ct_el_ndx = -1;
   ctevp->wrapper_type = WRAPPER_PROCESS_THRD_EV;
   /* AIV 09/24/09 - removed __emit_rearm_wait - wrapper code does the */
   /* same thing as arm_ectrl - better to just use one wrapper */
   __emit_arm_ectrl(tevp_ti, dctp->dceschd_tev_ofs);
  }

 /* AIV 11/03/07 - rearm ectrl no longer does anything - using static */
 schd_tev_ti = __gen_dce_schd_tev(dctp);
 __emit_save_tevp_to_schd(tevp_ti, schd_tev_ti);

 /* set thrd action to next statement */
 if (__needs_thread_ctrl)
  {
   __emit_set_thd_actionst(stp);
  }
 
 __emit_suspend();

 __start_bblk(after_bbp);
}

/*
 * generate code for a ++/-- statement
 */
static void gen_stmt_inc_dec(struct st_t *stp, int32 is_inc)
{
 int32 val_ti;
 struct expr_t *lhsx; 

 /* just call eval lhs expr and do the eval code */
 lhsx = stp->st.spra.lhsx;
 val_ti = __gen_expr_eval(lhsx->lu.x, TRUE);
 gen_inc_dec(lhsx, is_inc, val_ti, FALSE);
}

/*
 * evaluate a ++/-- 
 * handle reals/narrow/wide - known to not have an scalar values
 */
static int32 gen_inc_dec(struct expr_t *ndp, int32 is_inc, int32 val_ti,
 int32 nd_result)
{
 int32 is_2state, srtyp, blen, amtyp, nbytes;
 int32 val_bpti, res_ti, res_bpti, cint_ti, inc_ti, cp_ti, one_ti;
 struct expr_t *lhsx;
 struct bblk_t *bpart_zero_bbp, *isxz_bbp, *done_bbp;

 lhsx = ndp->lu.x;
 is_2state =__tmp_is_2state(val_ti);
 isxz_bbp = NULL;
 done_bbp = NULL;
 val_bpti = -1;

 blen = lhsx->szu.xclen;
 if (is_2state) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;

 if (nd_result)
  {
   res_ti = __gen_tn(srtyp, blen); 
   /* if signed need to set result as well */
   if (ndp->has_sign) __tntab[res_ti].t_signed = TRUE;
  }
 else res_ti = -1;

 /* if real handle in separate routine */
 if (lhsx->is_real)
  {
   gen_real_inc_dec(ndp, is_inc, val_ti, nd_result, res_ti);
   return(res_ti);
  }

 if (!is_2state)
  {
   val_bpti = __get_bpti(val_ti);
   bpart_zero_bbp = __alloc_bblk(FALSE);
   isxz_bbp = __alloc_bblk(TRUE);
   if (nd_result) done_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(bpart_zero_bbp, isxz_bbp, val_bpti); 
   __start_bblk(bpart_zero_bbp);
  }

 if (blen <= WBITS)
  {
   cint_ti = __gen_cint_tn(1);
   if (is_inc) inc_ti = __emit_add(blen, val_ti, cint_ti);
   else inc_ti = __emit_sub(blen, val_ti, cint_ti);

   if (ndp->post_inc_dec && nd_result)
    {
     if (__tntab[val_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
     else amtyp = AM_REG;
     cp_ti = __move_insn(TN_VAL, I_MOVA, amtyp, val_ti);
    }
   else cp_ti = val_ti;

   __emit_copy(WRDBYTES, inc_ti, val_ti);
   gen2_proc_assign(lhsx, val_ti);

   if (nd_result)
    {
     if (is_2state)
      {
       __emit_copy(WRDBYTES, cp_ti, res_ti);
      }
     else
      {
       __emit_copy(WRDBYTES, cp_ti, res_ti);
       res_bpti = __get_bpti(res_ti);
       cint_ti = __gen_cint_tn(0);
       __emit_copy(WRDBYTES, cint_ti, res_bpti);
      }

     if (!is_2state) 
      {
       __emit_jmp(done_bbp);
       __start_bblk(isxz_bbp);
       __emit_copy(WRDBYTES, val_ti, res_ti);
       res_bpti = __get_bpti(res_ti);
       __emit_copy(WRDBYTES, val_bpti, res_bpti);
       __start_bblk(done_bbp);
      }
    }
   else if (!is_2state) __start_bblk(isxz_bbp);
   return(res_ti);
  }
   
 /* almost the same as the narrow version - but has larger copies */
 /* and needs to make a larger one to do the addition */
 /* AIV LOOKATME - code could just get high word - and check for carry */
 /* value since know adding only 1 - this code should be rarely reached */
 /* wide case must use wrapper since for the carry */
 nbytes = wlen_(blen)*WRDBYTES;
 if (srtyp != SR_BIT2S) nbytes *= 2;

 /* make a large one */
 cint_ti = __gen_cint_tn(1);
 one_ti = __gen_tn(srtyp, blen);
 __emit_store_cint(one_ti, 0, nbytes);
 __emit_copy(WRDBYTES, cint_ti, one_ti);

 if (is_inc) inc_ti = __emit_add(blen, val_ti, one_ti);
 else inc_ti = __emit_sub(blen, val_ti, one_ti);


 if (ndp->post_inc_dec && nd_result)
  {
   cp_ti = __gen_tn(srtyp, blen);   
   __emit_copy(nbytes, val_ti, cp_ti);
  }
 else cp_ti = val_ti;

 /* only copy the apart for both 2-state and 4 */
 __emit_copy(wlen_(blen)*WRDBYTES, inc_ti, val_ti);

 gen2_proc_assign(lhsx, val_ti);

 if (nd_result)
  {
   __emit_copy(nbytes, cp_ti, res_ti);

   if (!is_2state) 
    {
     __emit_jmp(done_bbp);
     __start_bblk(isxz_bbp);
     __emit_copy(nbytes, val_ti, res_ti);
     __start_bblk(done_bbp);
    }
  }
 else if (!is_2state) __start_bblk(isxz_bbp);
 return(res_ti);
}

/*
 * do a real inc/dec
 * 64-bit can just do one word copies - but 32-bit needs to copy the two
 * words
 */
static int32 gen_real_inc_dec(struct expr_t *ndp, int32 is_inc, int32 val_ti,
 int32 nd_result, int32 res_ti)
{
 int32 cint_ti, inc_ti, cp_ti, one_ti, amtyp;
 word64 w64;
#ifdef __CVC32__
 int32 one_bpti, cp_high_ti, val_bpti, res_bpti;
#endif
 double d1;
 struct expr_t *lhsx;

 __tntab[res_ti].t_real = TRUE;
 __tntab[res_ti].tn_used_wide = TRUE;
 d1 = 1;
 memcpy(&w64, &d1, sizeof(double));
 cint_ti = __gen_cint_tn((word32) w64);
 one_ti = __gen_tn(SR_VEC, WBITS); 
 __tntab[one_ti].t_real = TRUE;
 __tntab[one_ti].tn_used_wide = TRUE;
 __emit_copy(WRDBYTES, cint_ti, one_ti);
#ifdef __CVC32__
 one_bpti = __get_bpti(one_ti);
 cint_ti = __gen_cint_tn((word32) (w64 >> 32));
 __emit_copy(WRDBYTES, cint_ti, one_bpti);
#endif
 if (is_inc) inc_ti = __emit_add_real(val_ti, one_ti);
 else inc_ti = __emit_sub_real(val_ti, one_ti);
 __tntab[inc_ti].t_real = TRUE;
 __tntab[inc_ti].tn_used_wide = TRUE;

 if (ndp->post_inc_dec && nd_result)
  {
   if (__tntab[val_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
   else amtyp = AM_REG;
#ifdef __CVC32__
   cp_ti = __move_insn(TN_VAL, I_MOVA, amtyp, val_ti);
   val_bpti = __get_bpti(val_ti);
   cp_high_ti = __move_insn(TN_VAL, I_MOVA, amtyp, val_bpti);
#else
   cp_ti = __move_insn(TN_VAL, I_MOVA, amtyp, val_ti);
#endif
  }
 else 
  {
   cp_ti = val_ti;
#ifdef __CVC32__
   cp_high_ti = __get_bpti(val_ti);
#endif
  }

 lhsx = ndp->lu.x;
 gen2_proc_assign(lhsx, inc_ti);

 if (nd_result)
  {
#ifdef __CVC32__
   __emit_copy(WRDBYTES, cp_ti, res_ti);
   res_bpti = __get_bpti(res_ti);
   __emit_copy(WRDBYTES, cp_high_ti, res_bpti);
#else
   __emit_copy(WRDBYTES, cp_ti, res_ti);
#endif
  }
 return(res_ti);
}


/*
 * generate insns and basic blocks for all 4 different dctl types
 *
 * notice for rhs blocking forms - continue stmt is the same stmt 
 */
static struct st_t *gen_dctl_stmt(struct st_t *stp)
{
 struct delctrl_t *dctp;
 struct st_t *nxtstp;

 dctp = stp->st.sdc;
 /* this is the the rhs form continuation */
 nxtstp = dctp->actionst;

 switch (dctp->dctyp) {
  case DC_DELAY: case DC_EVENT:
   nxtstp = gen_blking_dctl_ectl(stp);
   break;
  case DC_RHSDELAY:
   if (nxtstp->stmttyp == S_NBPROCA)
    {
     nxtstp = gen_nb_dctl_ectl(stp, nxtstp->st.spra.rhsx, -1);
    }
   else gen_rhs_dctl_ectl(stp);
   break;
  case DC_RHSEVENT:
   if (nxtstp->stmttyp == S_NBPROCA)
    {
     nxtstp = gen_nb_dctl_ectl(stp, nxtstp->st.spra.rhsx, -1);
    }
   else gen_rhs_dctl_ectl(stp);
   break;
 }
 return(nxtstp);
}

/*
 * gen bblks and insns for blocking prefix delay/event control
 */
static struct st_t *gen_blking_dctl_ectl(struct st_t *stp)
{
 int32 tevp_ti, schd_tev_ti, stmt_ent_ti;
 struct delctrl_t *dctp;
 struct st_t *nxtstp;
 struct bblk_t *suspend_bbp;
 struct ctev_t *ctevp;

 /* non rhs delay always has action stmt - even if just S_NULL */
 dctp = stp->st.sdc;
 nxtstp = dctp->actionst;

 /* DBG remove -- */ 
 if (nxtstp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* see if this is a merged always block - if not will return NULL */
 ctevp = get_merged_dctp_ctev(dctp);

 /* if not better be regular - with ctevp in the stmt */
 if (ctevp == NULL) ctevp = stp->ctevp;

 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 

 /* only set thread acton of using thread control */
 if (__needs_thread_ctrl)
  {
   __emit_set_thd_actionst(nxtstp);
  }

 if (dctp->dctyp == DC_DELAY) gen_sched_proc_del(stp, nxtstp);
 else if (dctp->dctyp == DC_EVENT) 
  {
   /* AIV 05/14/07 - set scheduled tevpi into static memory area */
   /* better because don't need to pass/access from statement */
   tevp_ti = __gen_ctevp_adr_tn(ctevp);
   if (__needs_thread_ctrl)
    {
     ctevp->ct_el_ndx = -1;
     ctevp->wrapper_type = WRAPPER_PROCESS_THRD_EV;
     __emit_arm_ectrl(tevp_ti, dctp->dceschd_tev_ofs);
    }
   else
    {
     stmt_ent_ti = __gen_proc_enter_adr_tn(nxtstp);
     /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
     ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
     ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;
     /* AIV 10/31/07 - arm ectrl no longer does anything - using static */
    }
   schd_tev_ti = __gen_dce_schd_tev(dctp);
   __emit_save_tevp_to_schd(tevp_ti, schd_tev_ti);
  }
 else __case_terr(__FILE__, __LINE__);

 /* DBG remove -- */
 if (nxtstp->stmttyp == S_GOTO) __misc_terr(__FILE__, __LINE__);
 /* -- */

 suspend_bbp = __alloc_bblk(FALSE);
 suspend_bbp->after_suspend = TRUE;
 __emit_suspend();

 /* by setting bit, enter insn gened as part of stmt gen */
 __start_bblk(suspend_bbp);
 __emit_enter_proc(nxtstp);

 return(nxtstp);
}

/*
 * generate a proc delay 
 * handle constant delay as a seperate case
 */
static void gen_sched_proc_del(struct st_t *stp, struct st_t *nxtstp)
{
 struct delctrl_t *dctp;
 struct ctev_t *ctevp;
 word64 pdel;
 int32 is_const, stp_ti, stmt_ent_ti, ctevp_ti;

 dctp = stp->st.sdc;
 ctevp = stp->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 
 is_const = __check_delay_constant(dctp->dc_du, dctp->dc_delrep, &(pdel));
 if (is_const)
  {
   /* if not using thread control use better delay wrapper */
   if (!__needs_thread_ctrl)
    {
     stmt_ent_ti = __gen_proc_enter_adr_tn(nxtstp);

     /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
     ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
     ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

     ctevp_ti = __gen_ctevp_adr_tn(ctevp);
     __emit_bldsched_proc_del_const_nt(ctevp_ti, pdel);
    }
   else
    {
   
     /* time is constant */
     ctevp->ct_el_ndx = -1;
     ctevp->wrapper_type = WRAPPER_PROCESS_THRD_EV;
     ctevp_ti = __gen_ctevp_adr_tn(ctevp);
     if (__gening_tsk)
      {
       __emit_bldsched_proc_del_task_const(ctevp_ti, pdel);
      }
     else __emit_bldsched_proc_del_const(ctevp_ti, pdel);
    }
  }
 else
  {
   /* not constant do a regular proc delay */
   stp_ti =  __gen_stmt_tn(stp);
   if (!__needs_thread_ctrl)
    {
     stmt_ent_ti = __gen_proc_enter_adr_tn(nxtstp);
     ctevp_ti = __gen_ctevp_adr_tn(ctevp);

     /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
     ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
     ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

     __emit_bldsched_proc_del_nt(stp_ti, ctevp_ti);
    }
   else
    {
     ctevp->ct_el_ndx = -1;
     ctevp->wrapper_type = WRAPPER_PROCESS_THRD_EV;
     ctevp_ti = __gen_ctevp_adr_tn(ctevp);
     __emit_bldsched_proc_del(stp_ti, ctevp_ti);
    }
  }
}

/*
 * gen bblks and insns for rhs delay/event control
 *
 * notice action stmt here must be special non directly execed rhs de proca 
 * AIV 05/15/07 - changed to use static memory - similar to non-blocking
 */
static void gen_rhs_dctl_ectl(struct st_t *stp)
{
 int32 tmp_ti, rhs_ti, nd_sign, tevp_ti, schd_tev_ti, want_a_vec;
 int32 lhs_srep, stmt_ent_ti, store_rhs_ti, nbytes;
 struct st_t *astp;
 struct delctrl_t *dctp;
 struct expr_t *lhsx, *rhsx;
 struct bblk_t *suspend_bbp;
 struct ctev_t *ctevp;

 dctp = stp->st.sdc;

 /* DBG remove -- */ 
 if (dctp->actionst == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 astp = dctp->actionst;
 /* only set thread info if using */
 if (__needs_thread_ctrl)
  {
   __emit_set_thd_actionst(astp);
  }
 
 ctevp = stp->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 

 if (dctp->dctyp == DC_RHSDELAY)
  { 
   /* notice this both builds and schedules a proc delay */
   gen_sched_proc_del(stp, astp);
  }
 else if (dctp->dctyp == DC_RHSEVENT)
  {
   /* AIV 05/14/07 - set scheduled tevpi into static memory area */
   /* better because don't need to pass/access from statement */
   tevp_ti = __gen_ctevp_adr_tn(ctevp);
   if (__needs_thread_ctrl)
    {
     ctevp->ct_el_ndx = -1;
     ctevp->wrapper_type = WRAPPER_PROCESS_THRD_EV;
     __emit_arm_ectrl(tevp_ti, dctp->dceschd_tev_ofs);
    }
   else
    {
     stmt_ent_ti = __gen_proc_enter_adr_tn(astp);

     /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
     ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
     ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

     /* AIV 10/31/07 - arm ectrl no longer does anything - using static */
    }
   schd_tev_ti = __gen_dce_schd_tev(dctp);
   __emit_save_tevp_to_schd(tevp_ti, schd_tev_ti);
  }
 else __case_terr(__FILE__, __LINE__);

 /* the rhs forms - know action st never nil */
 lhsx = astp->st.spra.lhsx;
 rhsx = astp->st.spra.rhsx;
 /* if not constant expression must evaluate the rhs */
 /* AIV 04/23/09 - this cannot use regular __is_const_expr need special */
 /* handling for IS params which __cvc_is_const_expr does */
 if (!__cvc_is_const_expr(rhsx)) 
  {
   /* AIV 05/15/07 - now can be scal as well not always convert to vector */
   lhs_srep = __get_lhs_srep(lhsx, &nbytes);

   want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : -1;
   tmp_ti = __gen_expr_eval(rhsx, want_a_vec);
   /* SJM 10/18/05 - simulates eval assign rhs expr - use rhs signedness */
   /* notice this may or may not copy */
   nd_sign = rhsx->has_sign;
   /* do the conversion if needed */
   rhs_ti = __gen_cnvt_srep_ifneeded(tmp_ti, lhs_srep, lhsx->szu.xclen,
    nd_sign, lhsx->is_real, FALSE);

   /* load the static memory comlab */
   store_rhs_ti = __gen_pd_rhsbp_tn(astp, lhs_srep, rhsx->is_real);

   __emit_copy(nbytes, rhs_ti, store_rhs_ti);
  }

 suspend_bbp = __alloc_bblk(FALSE);
 suspend_bbp->after_suspend = TRUE;
 __emit_suspend();

 /* by setting bit, enter insn gened as part of stmt gen */
 __start_bblk(suspend_bbp);
 __emit_enter_proc(astp);
}

/*
 * gen bblks and insns for non blocking delay/event control
 * always rhs
 *
 * AIV 11/30/09 - new handling of non blocking with constant values for 
 * better performance
 *
 *  1) if same block and same delay value it is known that the second nb sched
 *  can just be added to the end of the first scheduled value
 *
 *  for example if this is called in the same block
 *  __asl_sched_nbrhs_scalar_dctrl_const
 *
 *  the second is now _last which doesn't schedule but just adds to end
 *  of __last_nb_hp->nb_endp
 *  __asl_sched_nbrhs_scalar_dctrl_const_last
 *
 *  2) if __all_nb_same_time - can produce better code as well
 *
 */
static struct st_t *gen_nb_dctl_ectl(struct st_t *stp, struct expr_t *rhsx,
 int32 accum_ti)
{
 int32 rhs_ti, tmp_ti, stp_ti, stmt_ent_ti, ctevp_ti, want_a_vec;
 int32 nd_signed, is_const, lhs_srep, store_wp_ti, nbytes, is_last;
 word64 nbdel;
 struct delctrl_t *dctp;
 struct st_t *astp, *nxtstp;
 struct expr_t *lhsx;
 struct ctev_t *ctevp;

 /* AIV 01/19/09 - need to mark if design has non-blocking events */
 __design_has_nb_events = TRUE; 

 dctp = stp->st.sdc;
 /* DBG remove -- */ 
 if (dctp->actionst == NULL) __misc_terr(__FILE__, __LINE__);
 if (dctp->actionst->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);
 /* --- */

#ifdef __XPROP__
 /* if xprop assign accum will be set */
 if (accum_ti != -1) astp = dctp->xprop_nb_actionst;
 else astp = dctp->actionst;
#else
 astp = dctp->actionst;
#endif

 /* the rhs forms - know action st never nil */
 lhsx = astp->st.spra.lhsx;
 ctevp = astp->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 

 /* AIV 04/13/07 - now can be scal as well not always convert to vector */
 lhs_srep = __get_lhs_srep(lhsx, &nbytes);

 if (dctp->dctyp == DC_RHSDELAY)
  {
   /* AIV 01/19/09 - need to mark design having <= #delay style nb */
   __design_has_nb_del_events = TRUE; 
   /* check if it has a constant delay */
   is_const = __check_delay_constant(dctp->dc_du, dctp->dc_delrep, &(nbdel));
   if (is_const)
    {
     /* if has a time #0 delay can treat it as not having a delay */
     /* this produces much better code because if doesn't malloc memory */
     if (nbdel == 0) 
      {
       gen_nblkrhs_proca(astp, astp->st.spra.rhsx, -1);
       goto next_stmt;
      }
       
     if (__nb_const_last_time == nbdel) is_last = TRUE;
     else is_last = FALSE;

     /* if rhs is a constant can just do a no delay non-blocking assign */
     /* AIV 04/23/09 - this cannot use regular __is_const_expr need special */
     /* handling for IS params which __cvc_is_const_expr does */
     if (!__lhsexpr_var_ndx(lhsx) && __cvc_is_const_expr(rhsx))
      {
       /* no need to save the rhsx if it is constant just assign */
       stmt_ent_ti = __gen_proc_enter_nb_adr_tn(astp);
       ctevp_ti = __gen_ctevp_adr_tn(ctevp);

       /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
       ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
       ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

       __emit_schd_nbrhs_nomem_dctrl_const(ctevp_ti, is_last);
       __nb_const_last_time = nbdel;
       add_non_blocking_stmt(astp, TRUE, TRUE, -1, FALSE, TRUE);
       set_nonblocking_fg_num_to_ctev(ctevp, astp);
       goto next_stmt;
      }
 

     /* AIV 11/10/09 - want a vector here */
     want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : 
      -1;
     if (accum_ti == -1) tmp_ti = __gen_expr_eval(rhsx, want_a_vec);
     else tmp_ti = accum_ti;
     /* AIV 12/28/06 - if lhs is signed still may need to sign xtnd here */
     if (lhsx->has_sign || __tntab[tmp_ti].t_signed) nd_signed = TRUE;
     else nd_signed = FALSE;

     rhs_ti = __gen_cnvt_srep_ifneeded(tmp_ti, lhs_srep, lhsx->szu.xclen,
      nd_signed, lhsx->is_real, FALSE);

     __nb_const_last_time = nbdel;
     /* not constant do a regular proc delay */
     /* AIV 08/17/10 - lhs var index can now be a scalar array value */
     if (__lhsexpr_var_ndx(lhsx)) 
      {
       gen_nb_lhs_varndx(astp, lhsx, ctevp, rhs_ti, FALSE, -1, lhs_srep);
      }
     else if (lhs_srep == SR_SCAL || lhs_srep == SR_SCAL2S)
      {
       /* not constant do a regular proc delay */

       stmt_ent_ti = __gen_proc_enter_nb_adr_tn(astp);
       ctevp_ti = __gen_ctevp_adr_tn(ctevp);

       /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
       ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
       ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

       __emit_schd_nbrhs_scalar_dctrl_const(ctevp_ti, rhs_ti, is_last);
       add_non_blocking_stmt(astp, FALSE, FALSE, lhs_srep, FALSE, TRUE);
       set_nonblocking_fg_num_to_ctev(ctevp, astp);
      }
     else
      {
       stmt_ent_ti = __gen_proc_enter_nb_adr_tn(astp);
       ctevp_ti = __gen_ctevp_adr_tn(ctevp);

       /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
       ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
       ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

       /* AIV 04/26/08 - memory is now fixed for these - record size */
       /* for later dumping of memory when creating event */
       ctevp->nb_rhs_byt_size = nbytes;
       ctevp->srep = lhs_srep;
       store_wp_ti = __emit_schd_nbrhs_dctrl_const(ctevp_ti, nbytes, is_last);
       __emit_copy(nbytes, rhs_ti, store_wp_ti);
       add_non_blocking_stmt(astp, FALSE, FALSE, lhs_srep, FALSE, TRUE);
       set_nonblocking_fg_num_to_ctev(ctevp, astp);
      }
    }
   else
    {
     __nb_const_last_time = 0xffffffffffffffffULL;
     /* if rhs is a constant can just do a no delay non-blocking assign */
     if (!__lhsexpr_var_ndx(lhsx) && __cvc_is_const_expr(rhsx))
      {
       /* no need to allocate memory det delay and schedule event */
       stp_ti = __gen_stmt_tn(stp);
       stmt_ent_ti = __gen_proc_enter_nb_adr_tn(astp);

       /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
       ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
       ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

       ctevp_ti = __gen_ctevp_adr_tn(ctevp);
       __emit_schd_nb_vardel_rhsconst_dctrl(stp_ti, ctevp_ti);
       add_non_blocking_stmt(astp, TRUE, TRUE, -1, FALSE, TRUE);
       set_nonblocking_fg_num_to_ctev(ctevp, astp);
       goto next_stmt;
      }

     /* AIV 11/10/09 - want a vector here */
     want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : 
      -1;
     if (accum_ti == -1) tmp_ti = __gen_expr_eval(rhsx, want_a_vec);
     else tmp_ti = accum_ti;

     /* AIV 12/28/06 - if lhs is signed still may need to sign xtnd here */
     if (lhsx->has_sign || __tntab[tmp_ti].t_signed) nd_signed = TRUE;
     else nd_signed = FALSE;

     rhs_ti = __gen_cnvt_srep_ifneeded(tmp_ti, lhs_srep, lhsx->szu.xclen,
      nd_signed, lhsx->is_real, FALSE);

     stp_ti =  __gen_stmt_tn(stp);
     /* AIV 08/17/10 - lhs var index can now be a scalar array value */
     if (__lhsexpr_var_ndx(lhsx)) 
      {
       /* not constant do a regular proc delay */
       gen_nb_lhs_varndx(astp, lhsx, ctevp, rhs_ti, FALSE, stp_ti, lhs_srep);
      }
     else if (lhs_srep == SR_SCAL || lhs_srep == SR_SCAL2S)
      {
       /* not constant do a regular proc delay */
       stmt_ent_ti = __gen_proc_enter_nb_adr_tn(astp);
       ctevp_ti = __gen_ctevp_adr_tn(ctevp);

       /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
       ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
       ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

       __emit_schd_nbrhs_scalar_dctrl(ctevp_ti, stp_ti, rhs_ti);
       add_non_blocking_stmt(astp, FALSE, FALSE, lhs_srep, FALSE, TRUE);
       set_nonblocking_fg_num_to_ctev(ctevp, astp);
      }
     else
      {
       stmt_ent_ti = __gen_proc_enter_nb_adr_tn(astp);

       /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
       ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
       ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

       ctevp_ti = __gen_ctevp_adr_tn(ctevp);
       /* AIV 04/26/08 - memory is now fixed for these - record size */
       /* for later dumping of memory when creating event */
       ctevp->nb_rhs_byt_size = nbytes;
       ctevp->srep = lhs_srep;
       store_wp_ti = __emit_schd_nbrhs_dctrl(stp_ti, ctevp_ti, nbytes);
       __emit_copy(nbytes, rhs_ti, store_wp_ti);
       add_non_blocking_stmt(astp, FALSE, FALSE, lhs_srep, FALSE, TRUE);
       set_nonblocking_fg_num_to_ctev(ctevp, astp);
     }
   }
  }
 else if (dctp->dctyp == DC_RHSEVENT)
  {
   __nb_const_last_time = 0xffffffffffffffffULL;
   if (accum_ti == -1) tmp_ti = __gen_expr_eval(rhsx, WANT_A_VEC);
   else tmp_ti = accum_ti;
   /* no scalar storage inside scheduler */
   /* notice this may or may not copy */
   /* AIV 12/28/06 - if lhs is signed still may need to sign xtnd here */
   if (lhsx->has_sign || __tntab[tmp_ti].t_signed) nd_signed = TRUE;
   else nd_signed = FALSE;

   rhs_ti = __gen_cnvt_srep_ifneeded(tmp_ti, lhs_srep, lhsx->szu.xclen,
    nd_signed, lhsx->is_real, FALSE);
   stp_ti = __gen_stmt_tn(stp);
   stmt_ent_ti = __gen_proc_enter_nb_adr_tn(astp);

   /* SJM 04/08/08 - now need tn info in ct since goes in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

   ctevp_ti = __gen_ctevp_adr_tn(ctevp);
   /* AIV 04/26/08 - memory is now fixed for these - record size */
   /* for later dumping of memory when creating event */
   ctevp->nb_rhs_byt_size = nbytes;
   ctevp->srep = lhs_srep;
   if (__lhsexpr_var_ndx(lhsx))  
    {
     /* notice this does the store - only if in range */
     gen_nb_arm_varndx(lhsx, stp_ti, astp, nbytes, ctevp_ti, rhs_ti, lhs_srep);
    }
   else
    {
     store_wp_ti = __emit_arm_nb_ectrl(stp_ti, ctevp_ti);
     __emit_copy(nbytes, rhs_ti, store_wp_ti);
     add_non_blocking_stmt(astp, FALSE, FALSE, lhs_srep, FALSE, TRUE);
    }
   set_nonblocking_fg_num_to_ctev(ctevp, astp);
  }
 else __case_terr(__FILE__, __LINE__);

next_stmt:
 if (astp->stnxt != NULL) nxtstp = astp->stnxt;
 /* nil continuation handled here */ 
 else nxtstp = stp->stnxt;
 return(nxtstp);
}

/*
 * handle the special case - must pass bi known to be in range
 * mem[i] <= repeat (cnt) @(clk) i + 10;
 */
static int32 gen_nb_arm_varndx(struct expr_t *lhsx, int32 stp_ti, 
 struct st_t *astp, int32 nbytes, int32 ctevp_ti, int32 rhs_ti, int32 lhs_srep)
{
 int32 bi_ti, store_wp_ti;
 struct bblk_t *outofrng_bbp, *inrng_bbp;
 struct expr_t *idndp;
 struct net_t *np;

 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;
 outofrng_bbp = __alloc_bblk(FALSE);
 inrng_bbp = __alloc_bblk(FALSE);
 bi_ti = gen_nb_varndx_value(np, lhsx, outofrng_bbp);
 /* if index is out of change no reason to schedule */
 __start_bblk(inrng_bbp); 

 store_wp_ti = __emit_arm_nb_varndx_ectrl(stp_ti, ctevp_ti, bi_ti);
 __emit_copy(nbytes, rhs_ti, store_wp_ti);
 add_non_blocking_stmt(astp, FALSE, FALSE, lhs_srep, FALSE, TRUE);
 __start_bblk(outofrng_bbp); 
 return(store_wp_ti);
}


/*
 * generate a non-blocking assign where the lhs is a variable index
 * this handle the lhs concat as well
 */
static void  gen_nb_lhs_varndx(struct st_t *stp, struct expr_t *lhsx, 
 struct ctev_t *ctevp, int32 rhs_ti, int32 is_pnd0, int32 stp_ti, int32 srtyp)
{
 int32 ctevp_ti, lxi, lhsnels, last_lowbi, lhswid, catxlen, bi, range_rhs_ti;
 int32 stmt_ent_ti, nbytes;
 struct expr_t *catndp, *catlhsx;
 struct expr_t **lhsxtab;

 ctevp_ti = __gen_ctevp_adr_tn(ctevp);
 /* if not a concat just do regular lhsx nb varndx and return */
 /* if lhs concat with a variable must handle as special case */
 /* still must use wrapper */
 if (lhsx->optyp != LCB) 
  {
   /* AIV 07/23/08 - static mem flag should be fasle here */
   add_non_blocking_stmt(stp, FALSE, FALSE, srtyp, TRUE, TRUE);
   set_nonblocking_fg_num_to_ctev(ctevp, stp);
   stmt_ent_ti = __gen_proc_enter_nb_adr_tn(stp);

   /* SJM 04/08/08 - now need tn info in ct since in dsgn dat area */
   ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

   /* AIV 04/26/08 - memory is now fixed for these - record size */
   /* for later dumping of memory when creating event */
   /* AIV 08/17/10 - this can now take a scalar value */
   if (srtyp == SR_SCAL || srtyp == SR_SCAL2S) nbytes = WRDBYTES;
   else if (srtyp == SR_BIT2S) nbytes = wlen_(lhsx->szu.xclen)*WRDBYTES;
   else nbytes = 2*wlen_(lhsx->szu.xclen)*WRDBYTES;
   ctevp->nb_rhs_byt_size = nbytes;
   ctevp->srep = srtyp;
   gen_nb_onelhsx_varndx(lhsx, rhs_ti, is_pnd0, stp_ti, ctevp_ti, nbytes);
   return;
  }
 
 /* wrapper for varndx now only used for varndx with lhs concat */
 ctevp->wrapper_type = WRAPPER_NPBA_VARNDX_CONCAT_EV;
 //AIV LOOKATME - better to alloc more than one but rare enough???????
 /* AIV 12/12/07 - notice the concat only uses one static ctevp */
 /* this is fine - becuase this will force a new runtime tevp */
 /* to be alloced for each in the lhs concat */

 /* AIV 12/12/07 - notice this is nearly identical to gen_lhs_concat(2) */

 /* build the lhs expr cat element tab */
 lhsnels = __cnt_cat_size(lhsx);
 lhsxtab = (struct expr_t **) __my_malloc(lhsnels*sizeof(struct expr_t *));
 lxi = lhsnels - 1;
 for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x, lxi--)
  { lhsxtab[lxi] = catndp->lu.x; }

 lhswid = lhsx->szu.xclen;
 /* following interpreter, rhs widened to size of lhs if needed */
 /* if narrower, some just won't be selected */
 if (__get_tnwid(rhs_ti) < lhswid || __tntab[rhs_ti].srtyp != srtyp)
  {
   rhs_ti = __gen_cnvt_srep_ifneeded(rhs_ti, srtyp, lhswid, FALSE,
    FALSE, FALSE);
  }

 last_lowbi = lhswid;
 for (lxi = lhsnels - 1; lxi >= 0; lxi--)
  {
   catlhsx = lhsxtab[lxi];
   catxlen = catlhsx->szu.xclen;
   bi = last_lowbi - catxlen;
   range_rhs_ti = gen_rhs_concat_range(rhs_ti, bi, catxlen, srtyp);

   /* now may have to change to SR_VEC or SR_BIT2S */
   range_rhs_ti = __gen_cnvt_srep_ifneeded(range_rhs_ti, srtyp, 
    catxlen, catlhsx->has_sign, catlhsx->is_real, FALSE);

   /* AIV LOOKATME - if width is known one - rhs is going to be scalar */
   /* can produce better assign code ????? */
   gen_nb_onelhsx_varndx_concat(catlhsx, range_rhs_ti, is_pnd0, stp_ti, 
    ctevp_ti, srtyp);
   last_lowbi = bi;
  }

 /* and when done must free it */ 
 __my_free(lhsxtab, lhsnels*sizeof(struct expr_t *));
}

/*
 * generate a non-blocking assign where the lhs is a variable index
 */
static void  gen_nb_onelhsx_varndx(struct expr_t *lhsx, int32 rhs_ti, 
 int32 is_pnd0, int32 stp_ti, int32 ctevp_ti, int32 nbytes)
{
 int32 bi_ti, store_wp_ti, sel_ti, biti;
 struct bblk_t *outofrng_bbp, *inrng_bbp;
 struct expr_t *idndp, *ndx1, *sel_ndp;
 struct net_t *np;

 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;
 outofrng_bbp = __alloc_bblk(FALSE);
 inrng_bbp = __alloc_bblk(FALSE);
 ndx1 = lhsx->ru.x;
 sel_ti = -1;
 /* AIV 02/09/11 - if array select which is not constant need to save */
 /* the select index and check to make sure in range as well */
 if (np->n_isarr)
  {
   /* can now have first index constant with variable bit select */
   /* AIV 04/19/11 - cannot fold this here if MD arrays - was folding index */
   if (ndx1->optyp == NUMBER && np->mda == NULL)
    {
     biti = __get_comp_num_ndx(ndx1);
     bi_ti = __gen_cint_tn(biti);
    }
   else bi_ti = gen_nb_varndx_value(np, lhsx, outofrng_bbp);

   if (ndx1->arr_select)
    {
     sel_ndp = ndx1->next_ndx;
     /* may have to get end index for mda */
     while (ndx1 != NULL)
      {
       sel_ndp = ndx1;
       ndx1 = ndx1->next_ndx;
      }
     
     if (sel_ndp->optyp == PARTSEL_NDX_PLUS || 
         sel_ndp->optyp == PARTSEL_NDX_MINUS)
      {
       sel_ti = __gen_comp_ndx(np, sel_ndp->ru.x->lu.x, outofrng_bbp, FALSE);
      }
     /* skip constant part selects here */
     else if (sel_ndp->optyp != PARTSEL && !__cvc_is_const_expr(sel_ndp))
      {
       sel_ti = __gen_comp_ndx(np, sel_ndp, outofrng_bbp, FALSE);
      }
    }
  }
 else bi_ti = gen_nb_varndx_value(np, lhsx, outofrng_bbp);
 /* if index is out of change no reason to schedule */
 __start_bblk(inrng_bbp); 

 store_wp_ti = -1;
 if (is_pnd0)
  {
   store_wp_ti = __emit_sched_nb_pnd0_lhs_varndx(bi_ti, nbytes, ctevp_ti, 
      sel_ti); 
  }
 /* constant case - uses no stmt */
 else if (stp_ti == -1)
  {
   store_wp_ti = __emit_schd_nbrhs_varndx_dctrl_const(bi_ti, nbytes, ctevp_ti,
      sel_ti);
   }
 else
  {
   store_wp_ti = __emit_schd_nbrhs_varndx_dctrl(stp_ti, bi_ti, nbytes, 
     ctevp_ti, sel_ti);
  }

 __emit_copy(nbytes, rhs_ti, store_wp_ti);
 __start_bblk(outofrng_bbp); 
}

/*
 * generate a non-blocking assign where the lhs is a variable index
 * special case where lhs is concat with a variable index
 * {mem[i], r}  <= #1 32'hffff0000;
 * AIV LOOKATME - this is the most efficient but is rare enough so 
 * shouldn't matter much didn't have a better non-complex solution
 */
static void  gen_nb_onelhsx_varndx_concat(struct expr_t *lhsx, int32 rhs_ti, 
 int32 is_pnd0, int32 stp_ti, int32 ctevp_ti, int32 srtyp)
{
 int32 bi_ti, nchg_ti, np_ti, store_wp_ti, nbytes;
 struct bblk_t *outofrng_bbp, *inrng_bbp;
 struct expr_t *idndp;
 struct net_chg_t *ncp;
 struct net_t *np;

 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;
 /* may have an inter mix of regular assign which don't have an index */
 if (__lhsexpr_var_ndx(lhsx)) 
  {
   outofrng_bbp = __alloc_bblk(FALSE);
   inrng_bbp = __alloc_bblk(FALSE);
   bi_ti = gen_nb_varndx_value(np, lhsx, outofrng_bbp);
   __start_bblk(inrng_bbp); 
  }
 else
  {
   outofrng_bbp = NULL;
   bi_ti = __gen_cint_tn(-1);
  }
 np_ti = __ld_netadr_tn(np);
 /* AIV 03/31/09 - this needs to call routine not just check flag */
 if (__needs_netchg_record(np)) 
  {
   ncp = __gen_netchg_addr_tn(np, -1, -1, FALSE, &nchg_ti);
   /* DBG remove -- */
   if (ncp == NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */
  }
 else nchg_ti = __gen_cint_tn(0);

 if (srtyp == SR_BIT2S)
  {
   nbytes = wlen_(lhsx->szu.xclen)*WRDBYTES;
  }
 else nbytes = 2*wlen_(lhsx->szu.xclen)*WRDBYTES;

 store_wp_ti = -1;
 if (is_pnd0)
  {
   store_wp_ti = __emit_sched_nb_pnd0_lhs_varndx_concat(np_ti, bi_ti, nbytes, 
    ctevp_ti, nchg_ti); 
  }
 /* constant case - uses no stmt */
 else if (stp_ti == -1)
  {
   store_wp_ti = __emit_schd_nbrhs_varndx_dctrl_const_concat(np_ti, bi_ti, 
    nbytes, ctevp_ti, nchg_ti);
   }
 else
  {
   store_wp_ti = __emit_schd_nbrhs_varndx_dctrl_concat(stp_ti, np_ti, bi_ti, 
    nbytes, ctevp_ti, nchg_ti);
  }

 __emit_copy(nbytes, rhs_ti, store_wp_ti);
 if (outofrng_bbp != NULL) __start_bblk(outofrng_bbp); 
}

/*
 * return the bi_ti for the variable non-blocking index where the index
 * is a variable (non-constant)
 */
static int32 gen_nb_varndx_value(struct net_t *np, struct expr_t *lhsx, 
 struct bblk_t *outofrng_bbp)
{
 int32 bi_ti, val_bpti, val_ti;
 struct expr_t *sel_ndp;
 struct bblk_t *bpart_zero_bbp;
 struct mda_t *mdap;

 bi_ti = -1;
 switch (lhsx->optyp) {
  case GLBREF: case ID:
  case PARTSEL:
   __case_terr(__FILE__, __LINE__);
   break; 
  case LSB:
   /* for multi-dim array compute the index */
   if ((mdap = np->mda) != NULL)
    {
     bi_ti = gen_comp_mda_ndx(np, mdap, lhsx->ru.x, outofrng_bbp, &sel_ndp);
    }
   else
    {
     if (lhsx->ru.x->optyp == NUMBER)
      __misc_terr(__FILE__, __LINE__);
     bi_ti = __gen_comp_ndx(np, lhsx->ru.x, outofrng_bbp, FALSE);
    }
   break;
  case PARTSEL_NDX_MINUS:
  case PARTSEL_NDX_PLUS:
   /* return a non-normalized bi (range one) value */
   bi_ti = __gen_tn(SR_CINT, WBITS);
   val_ti = __gen_expr_eval(lhsx->ru.x->lu.x, -1);
   /* AIV 02/19/09 - if two state no need to check b part */
   if (!__tmp_is_2state(val_ti))
    {
     /* AIV 09/14/10 - may have to convert to get bpart (scalar) */ 
     val_ti = __gen_cnvt_srep_ifneeded(val_ti, SR_VEC, __get_tnwid(val_ti),
      FALSE, FALSE, FALSE);
     val_bpti = __get_bpti(val_ti);
     bpart_zero_bbp = __alloc_bblk(FALSE);
     /* if bpart not zero return -1 otherwise set biti to first range */
     __emit_jmp_0(bpart_zero_bbp, outofrng_bbp, val_bpti); 
     __start_bblk(bpart_zero_bbp);
    }
   __emit_copy(WRDBYTES, val_ti, bi_ti);
   break;
  case LCB:
   __case_terr(__FILE__, __LINE__);
   /* AIV FIXME - AIV WRITEME
    for (catxp = xp->ru.x; catxp != NULL; catxp = catxp->ru.x)
     struct expr_t *catxp;
     {
     }
    */
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(bi_ti);
}

/*
 * gen insns for repeat form event control
 *
 * only can be rhs ev control or rhs non blocking assign ev ctrl
 * pattern is S_REPDCSETUP followed immediately always by del ctrl
 * stmt with repeat form rhs ev control
 */
static void gen_rep_ectl_setup(struct st_t *stp)
{
 int32 rep_ti, rhs_ti, tmp_ti, lhs_srep, stmt_ent_ti; 
 int32 repcnt_ti, sign_ti, ctevp_ti, want_a_vec;
 int32 nd_sign, rep_bpti, nbytes, store_nb_val_ti, is_2state;
 struct st_t *astp, *nxtstp;
 struct expr_t *rhsx, *lhsx, *repx;
 struct bblk_t *immed_bbp, *after_bbp, *bpart_zero_bbp;
 struct delctrl_t *rdctp;
 struct ctev_t *ctevp;

 ctevp = stp->ctevp;
 /* DBG remove -- */ 
 if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -- */ 

 immed_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 nxtstp = stp->stnxt;
 rdctp = nxtstp->st.sdc;

 /* eval self determined count expr - same as select or condition */ 
 repx = rdctp->repcntx;
 rep_ti = __gen_expr_eval(repx, WANT_A_VEC);
 is_2state = __tmp_is_2state(rep_ti);

 if (!is_2state)
  {
   bpart_zero_bbp = __alloc_bblk(FALSE);

   /* need to do conversion if real */
   rep_ti = __gen_cnvt_srep_ifneeded(rep_ti, SR_VEC, __get_tnwid(rep_ti),
    FALSE, FALSE, FALSE);

   /* need to check the b part for zero */
   rep_bpti = __get_bpti(rep_ti);
   __emit_jmp_0(bpart_zero_bbp, immed_bbp, rep_bpti); 
  
   __start_bblk(bpart_zero_bbp);
  }
 else
  {
   rep_ti = __gen_cnvt_srep_ifneeded(rep_ti, SR_BIT2S, __get_tnwid(rep_ti),
     FALSE, FALSE, FALSE);
  }

 /* condition must be WBITS */
 /* special insn to test for no count and jump if need rep count */
 /* ectl, if jump, just before jump, set the rdctp count field */ 
 repcnt_ti =  __gen_dctrl_rep_bp(rdctp);
 if (repx->has_sign) sign_ti = __gen_cint_tn(TRUE);
 else sign_ti = __gen_cint_tn(FALSE);
 
 __emit_repcnt_jmp(immed_bbp, after_bbp, rep_ti, repcnt_ti, sign_ti);
 __start_bblk(immed_bbp);

 /* fall thru - code to exec statment immediately */
 /* LOOKATME - could add x/z caused no wait warning here */
 astp = nxtstp->st.sdc->actionst;
 rhsx = astp->st.spra.rhsx;
 lhsx = astp->st.spra.lhsx;

 /* AIV FIXME FIXME - no way this is right */
 if (astp->stmttyp == S_NBPROCA)
  {
   /* case 1: NB assign - becomes no delay NB assign form */ 
   /* notice size/type here is determined by lhs context */

   /* no scalar storage inside scheduler */
   /* notice this may or may not copy */

   /* SJM 10/18/05 - simulates eval assign rhs expr - use rhs signedness */
   nd_sign = rhsx->has_sign;

   /* AIV 04/13/07 - now can be scal as well not always convert to vector */
   lhs_srep = __get_lhs_srep(lhsx, &nbytes);

   /* AIV 11/10/09 - want a vector here */
   want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : -1;
   tmp_ti = __gen_expr_eval(repx, want_a_vec);

   /* AIV 04/16/07 - FIXME - this cannot be right - not testing thoroughly */
   rhs_ti = __gen_cnvt_srep_ifneeded(tmp_ti, lhs_srep, lhsx->szu.xclen,
    nd_sign, lhsx->is_real, FALSE);

   store_nb_val_ti = __gen_nonblocking_bp_tn(astp, lhs_srep, rhsx->is_real);
   __emit_copy(nbytes, rhs_ti, store_nb_val_ti);

   /* AIV 08/30/06 - know delay is 0 here */
   /* AIV 05/01/08 - non-blocking uses astp->ctevp not stp's */
   ctevp = astp->ctevp;
   /* DBG remove -- */ 
   if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */ 
   stmt_ent_ti = __gen_proc_enter_nb_adr_tn(astp);

   /* SJM 04/08/08 - now filling ctevp in prp code */
   ctevp->ct_el_ndx = __tntab[stmt_ent_ti].tncu.el_ndx;
   ctevp->ct_comlab_typ = __tntab[stmt_ent_ti].comlab_typ;

   ctevp_ti = __gen_ctevp_adr_tn(ctevp);
   /* AIV 04/26/08 - memory is now fixed for these - record size */
   /* for later dumping of memory when creating event */
   if (lhs_srep != SR_SCAL && lhs_srep != SR_SCAL2S)
    {
     ctevp->nb_rhs_byt_size = nbytes;
     if (is_2state) ctevp->srep = SR_BIT2S;
     else ctevp->srep = SR_VEC;
    }
   /* AIV 07/25/08 - just need to nb delay here */
   /* AIV 03/09/09 - better to inline this simple routine */
   /* __emit_bld_nb_nodelay_tev(ctevp_ti); */
   gen_nb_nodelay_tev(ctevp_ti);
  }
 else
  {
   /* case 2: rhs repeat event control - treat as simple proca */ 
   gen_proc_assign(lhsx, rhsx, -1);
  }
 __emit_jmp(after_bbp);
 __start_bblk(after_bbp);
}

/*
 * insn gen to set up thread tree and fall thru to exec name block
 *
 * LOOKATME - only need this if named block can be disabled
 * 
 */
static struct st_t *gen_namblk(struct st_t *stp)
{
 int32 stp_ti, assoc_tsk_ti;
 struct st_t *end_stp;
 struct task_t *tskp;
 struct bblk_t *after_namblk_bbp, *after_nb_dsa_brk_bbp;

 stp_ti = __gen_stmt_tn(stp);
 tskp = stp->st.snbtsk;
 /* SJM 10/18/05 - if task can't be disabled just insert stmts */
 /* SJM 12/03/05 - if in task, higher up can be disabled so can't inline */ 
 /* SJM FIXME - need code to trace up task tree making sure can't be */
 /* disabled */ 
 assoc_tsk_ti = -1;
 if (__processing_func || (!__gening_tsk && !tskp->can_be_disabled))
  {
   /* SJM 11/15/05 - since taking over thread need to preserve global state */
   /* but only global state is assoc_tsk (must save/replace) and th itp */
   /* but th itp never changes for named block */

   /* SJM 11/13/05 - for named blocks not sched set the assoc task for %m */
   /* AIV 12/12/07 - only needed if uses_scope flag is set or has delay */
   /* AIV 03/10/09 - scope only needs thread if there is a delay */
   if (tskp->uses_scope) 
    {
     /* AIV 03/24/09 - still cannot uses scope if tasks is called and that */
     /* task uses thread mechanism save/restore cannot work */
     if (tskp->no_delay && !tskp->thas_tskcall) 
      {
       save_task_scope(tskp); 
      }
     else  assoc_tsk_ti = __emit_setsave_assoc_tsk(stp_ti);
    }

   /* SJM 09/14/05 - now separate simpler code for named blk in function */
   if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);
   /* this has a GOTO at end that needs to be ignored */
   gen_stlst(tskp->tskst, TRUE);
   if (stp->stnxt != NULL) __pop_cc_stmt();

   /* SJM 09/29/05 - LOOKATME - for in func ignored name blocks */
   /* think needs to gen the statements after the named block since */
   /* no suspend and setting of thread continue */
   /* DBG remove -- */
   end_stp = __find_stlst_end(tskp->tskst);
   if (end_stp->stmttyp == S_GOTO
    && (end_stp->lpend_goto || end_stp->dctrl_goto))
    __misc_terr(__FILE__, __LINE__);
   /* --- */

   if (tskp->uses_scope) 
    {
     if (tskp->no_delay && !tskp->thas_tskcall) 
      {
       restore_task_scope(); 
      }
     else __emit_restore_assoc_tsk(assoc_tsk_ti);
    }
   if (tskp->dsa_brk_ndx != -1)
    {
     /* must complete prior to enter new disable enter code */
     __emit_complete();

     after_nb_dsa_brk_bbp = __alloc_bblk(FALSE);
     __start_bblk(after_nb_dsa_brk_bbp);
     after_nb_dsa_brk_bbp->after_suspend = TRUE;
     /* make a new task disable enter location */
     __emit_enter_thd_ret(tskp->dsa_brk_ndx);
    }
   return(stp->stnxt);
  }

 /* need iop to call routine to setup thread tree in case named */
 /* block can be disabled */
 /* for compiler, thread setup for suspends/disables in block - exec */
 /* is immediate */
 /* don't set up thrd tree if disable impossible */
 if (!tskp->can_be_disabled)
  {
   gen_stlst(tskp->tskst, FALSE);
   return(stp->stnxt);
  }

 __emit_setup_namblk(stp_ti);

 /* fall thru to exec named block */
 /* need to set global named block to be used for lowered asm net naming */ 
 gen_stlst(tskp->tskst, FALSE);
 
 /* if generating task must cleanup task code thread as well */
 /* SJM 10/18/05 - since only needed if named block can be disabled */
 /* continue after stmt better than tsk ret jump */
 if (stp->stnxt != NULL)
  {
   after_namblk_bbp = __alloc_bblk(FALSE);
   after_namblk_bbp->after_suspend = TRUE;
   
   /* KHAI? this to return scheduler without set __stm_suspend = TRUE */
   if (need_complete_or_suspend())
    {
     __emit_complete();
    }

   __start_bblk(after_namblk_bbp);
   __emit_enter_proc(stp->stnxt);
  }
 /* AIV 04/03/07 -  if has next stmt and gening task need thrd cleanup here */
 /* AIV 04/03/07 - this area a little iffy need improve task/disables */
 else if (__gening_tsk && stp->stnxt == NULL)
  {
   __emit_tskdone_cleanup();
  }
 return(stp->stnxt);
}

/*
 * generate nsns for each for each statement in fork-join
 * fork joins always unnamed - for labeled block contents is unnamed fj
 *
 * LOOKATME - why can labeled fork-joins not happen 
 */
static void gen_unfj(struct st_t *stp)
{
 int32 fji;
 struct st_t *fjstp;
 int32 stp_ti, nxtstp_ti;
 struct bblk_t *after_suspend_bbp, *ent_after_fj_bbp;

 /* DBG --- */
 if (stp->st.fj.fjstps[0] == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 __push_cc_stmt((struct st_t *) NULL);

 stp_ti = __gen_stmt_tn(stp);
 if (stp->stnxt != NULL)
  {
   nxtstp_ti = __gen_stmt_tn(stp->stnxt);
  }
 else
  {
   nxtstp_ti = __gen_tn(SR_VEC, WBITS);
   __emit_store_cint(nxtstp_ti, 0, 2*WRDBYTES);
  }
 __emit_schd_fork(stp_ti, nxtstp_ti);
 /* DBG remove -- */
 if (stp->st.fj.fjstps[0] == NULL) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 __emit_suspend();

 /* generate code for each fork-join stmt (list?) and set resume labels */
 for (fji = 0;; fji++)
  {
   /* need nil end also for table of ssl lists */
   if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;

   after_suspend_bbp = __alloc_bblk(FALSE);
   after_suspend_bbp->after_suspend = TRUE;
   __start_bblk(after_suspend_bbp);

   /* SJM 07/26/05 - must remove any unnamed block list hdrs here */
   if (fjstp->stmttyp == S_UNBLK)
    {
     __emit_enter_proc(fjstp->st.sbsts);
     gen_stlst(fjstp->st.sbsts, FALSE);
    }
   else 
    {
     __emit_enter_proc(fjstp);
     gen_stlst(fjstp, FALSE);
    }
   /* DBG remove --- */
   if (__cur_bbp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
//AIV? -- do we need to fix this?
   if (__cur_bbp->itail == NULL || __cur_bbp->itail->opcod != I_RETURN)
    {
     __emit_complete();
    }
  }
 if (stp->stnxt != NULL)
  {
   /* AIV 11/29/06 - REMOVEME - don't think this is ever needed and wrong */
   /* REMOVEME ----
   if (need_complete_or_suspend())
    {
     __emit_suspend();
    }
   --- */
   ent_after_fj_bbp = __alloc_bblk(FALSE); 
   ent_after_fj_bbp->after_suspend = TRUE;
   __start_bblk(ent_after_fj_bbp);
   __emit_enter_proc(stp->stnxt);
  }
 __pop_cc_stmt();
}

/*
 * ROUTINES TO GENERATE TSK CALL VINSNS
 */

/*
 * generate insns for task call
 */
static void gen_tskcall(struct st_t *stp)
{
 int32 stp_ti, nxtstp_ti, set_idp_ti, cint_ti, thd_idp_ti, restore_idp_ti;
 int32 save_tskp_ti, tskp_ti, tskp_reg_ti, save_idp_ti, output_idp_ti;
 int32 thdjmp_ndx, has_thread;
 struct tskcall_t *tkcp;
 struct expr_t *tkxp;
 struct task_t *tskp;
 struct gref_t *grp;
 struct sy_t *msym, *tsyp;
 struct systsk_t *stbp;
 struct st_t *nxtstp;
 struct bblk_t *task_ret_bbp, *ent_after_dsable_bbp, *after_ent_bbp;
 struct mod_t *mdp;
 
 tkcp = &(stp->st.stkc);
 tkxp = tkcp->tsksyx;
 tskp = tkxp->lu.sy->el.etskp;

 /* must load stmt from current calling mod itre context even if XMR */
 thdjmp_ndx = -1;
 nxtstp_ti = -1;
 if (tkxp->lu.sy->sytyp == SYM_STSK)
  {
   stp_ti = __gen_stmt_tn(stp);
   /* AIV 04/10/08 - need to record the possible slot end action */
   tsyp = tkxp->lu.sy;
   stbp = tsyp->el.esytbp;
   switch (stbp->stsknum) {
    case STN_MONITORON:
     __cvc_slotend_action |= SE_MONIT_CHG;
    break;
    case STN_FMONITOR: case STN_FMONITORH: case STN_FMONITORB:
    case STN_FMONITORO:
     __cvc_slotend_action |= SE_FMONIT_TRIGGER;
    break;
    case STN_FSTROBE: case STN_FSTROBEH: case STN_FSTROBEB: case STN_FSTROBEO:
    case STN_STROBE: case STN_STROBEH: case STN_STROBEB: case STN_STROBEO:
     __cvc_slotend_action |= SE_STROBE;
    break;
    /* AIV 10/20/08 - seperate out the common $display case - whas its own */
    /* wrapper - skips a layer from __exec_stsk */
    /* AIV LOOKATME - could add more of these here */
    case STN_DISPLAY:
     __emit_exec_display(stp_ti);
     return;
   }
   __emit_stskcall(stp_ti);
   return;
  }

 /* if DPI call handle as special case */
 if (tskp->tf_dpip)
  {
   gen_tskcall_dpi(stp);
   return;
  }

 grp = NULL;
 msym = NULL;
 save_idp_ti = -1;
 /* run time to code to find itree tn, but does not change cntxt */
 if (tkxp->optyp == GLBREF)
  {
   /* for XMR task call, get inst_ptr into addr reg but can't push */
   /* SJM 01/25/06 - always use but mod inst only wrong for declarative */
   grp = tkxp->ru.grp;
   /* must get tsk exec itree location but cannot change to yet */
   set_idp_ti = __gen_ld_task_xmr_idp(grp);
   msym = grp->targmdp->msym;
   if (tskp->is_auto) set_idp_ti = __emit_new_auto_idp_area(set_idp_ti);
  }
 else 
  {
   msym = __inst_mod->msym;
   set_idp_ti = -1; 
   if (tskp->is_auto) 
    {
     save_idp_ti = __emit_save_cur_idp();
     set_idp_ti = __emit_new_auto_idp_area(save_idp_ti);
    }
  }

 /* if XMR, evals each in callee then chgs to caller it cntxt to store */
 gen_st_tf_ins(stp, set_idp_ti, grp);

 nxtstp = __find_after_tsk_nxtstmt(stp);
 /* AIV 05/29/07 - if task uses scope (%m) need to use thread as well */
 /* could optimize to not use thread if no thread needed but code is rare */
 /* AIV 04/13/10 - if automatic tasks need to be thread control */
 has_thread = (!tskp->no_delay || tskp->can_be_disabled || !tskp->no_xmrcall 
    || tskp->is_auto);

 if (has_thread)
  {
   /* AIV 03/25/09 - no need to set the == NULL - case never used */
   if (nxtstp != NULL)
    {
     nxtstp_ti = __emit_set_thd_nxtst(nxtstp); 
    }
  }
 else if (tskp->uses_scope) 
  {
   /* AIV 03/10/09 - task doesn't need thread if has scope but no delay */
   save_tskp_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO, NLO_SCP_TSKP);
   __st_insn(I_STOREA, AM_REG, save_tskp_ti, AM_NLO, NLO_SAVE_SCP_TSKP);

   if (set_idp_ti != -1)
    {
     __push_wrkitstk(grp->targmdp, 0);
     tskp_ti = __gen_taskp_tn(tskp);
     __pop_wrkitstk();
    }
   else tskp_ti = __gen_taskp_tn(tskp);

   tskp_reg_ti = __move_insn(TN_VAL, I_MOVA, AM_REG, tskp_ti);
   __st_insn(I_STOREA, AM_REG, tskp_reg_ti, AM_NLO, NLO_SCP_TSKP);
  }

 /* AIV 02/03/05 - need to push the instance before setup task thread */
 /* replace (can't change height) itree stack with callee's XMR */
 /* and set current in cur thd th itp field */
 /* AIV 05/03/10 - only need to save curthread info if using thread */
 if (set_idp_ti != -1)
  {
   if (has_thread) 
    {
     __emit_save_curthd_idp();
    }
   else save_idp_ti = __emit_save_cur_idp();
   __memloc_emit_set_idp(set_idp_ti);
  }


 /* stmt is in caller's itree loc in case XMR */
 if (has_thread)
  {
   stp_ti = __gen_stmt_tn(stp);

   /* if xmr call, the one up task thread contains the caller's itree loc */
   if (nxtstp != NULL)
    {
     if (save_idp_ti == -1 ) __emit_setup_task_thd(stp_ti, nxtstp_ti); 
     else __emit_setup_task_thd_auto(stp_ti, nxtstp_ti, save_idp_ti);
    }
   else
    {
     cint_ti = __gen_cint_tn(0);
     if (save_idp_ti == -1 ) __emit_setup_task_thd(stp_ti, cint_ti);
     else __emit_setup_task_thd_auto(stp_ti, cint_ti, save_idp_ti);
    }
   /* notice the index for the label to return to is known at compile time */
   /* entry in table for every task call in source */
   thdjmp_ndx = gen_jmpto_tsk(msym);
   cint_ti = __gen_cint_tn(thdjmp_ndx);
   __emit_st_thd_ret_lab_ndx(cint_ti);
  
   /* AIV 02/03/06 - need to set the jump index to the return label */
   /* this is need because a disable in a task can return to scheduler */
   /* which needs to be able to enter back to task return location */
   if (nxtstp != NULL)
    {
     nxtstp->task_thrd_jmpndx = thdjmp_ndx;
    }
   /* call task - new thread creates so this looks like continuing */
   __emit_jmpto_tsk(tskp, msym);
   task_ret_bbp = __alloc_bblk(FALSE);
   __start_bblk(task_ret_bbp);
   task_ret_bbp->after_suspend = TRUE;
  }
 else __emit_call_tsk(tskp, msym);

 /* clean up thread tree - if task disabled, may not get here, but */
 /* if get here can just clean up thread tree, assign outs if needed */
 /* without going to scheduler */
 /* if do not get here because of disable - scheduler will handle clean up */ 
 /* BEWARE - works because if disabled, never need to store task outs */

 if (has_thread)
  {
   __emit_enter_thd_ret(thdjmp_ndx);
  }
 else if (tskp->uses_scope) 
  {
   restore_task_scope();
  }

 output_idp_ti = -1;
 thd_idp_ti = -1;
 if (tkxp->optyp == GLBREF)
  {
   /* if not disabled and XMR call, chg cur itree context to caller */ 
   /* this pop callee itstk and pushes cur thd th itp */
   /* AIV 05/03/10 - only need to save curthread info if using thread */
   if (has_thread)
    {
     thd_idp_ti = __emit_restore_thd_idp();
     __memloc_emit_set_idp(thd_idp_ti);
    }
   else __memloc_emit_set_idp(save_idp_ti);
  }

 /* if task has outs, load the down formal parameter nets and assign */ 
 /* to the up lhs expr actual argument */ 
 /* SJM 11/12/05 - never exec this code if disable */
 if (tskp->thas_outs)
  {
   /* AIV 04/12/10 - due to automatic alloc __idp area this now must check */
   /* for gref version and may have to still use new idp area */
   /* AIV 01/06/06 - if xmr call must reload the itp_ti since it is stored */ 
   /* on local stack */
   if (tkxp->optyp == GLBREF)
    {
     /* only need to reload xmr inst if more than one instance */
     /* this is true because only needed to get __inum index into net */
//AIV IDP FIXME CVC - must reload everytime now????
     //if (grp->targmdp->flatinum > 1)
      {
       output_idp_ti = __gen_ld_task_xmr_idp(grp);
      }
    }
   //else output_idp_ti = thd_idp_ti;
   if (grp == NULL) mdp = __inst_mod;
   else mdp = grp->targmdp;

   gen_st_tf_outs(stp, output_idp_ti, mdp);
  }

 /* SJM 12/03/05 - task calls and named block enables inside tasks for */
 /* now must be scheduled since no code to trace up call chain to see */
 /* if higher can be disabled */
 after_ent_bbp = NULL;
 /* AIV 05/16/06 - the nxtstp could already be entered here */
 /* if enter point is already created don't build a new one */
 if (has_thread)
  {
   /* automatic task must return cannot free automatic malloc area */
   /* so no free here after output assigns - and restore old idp area */
   if (tskp->is_auto) 
    {
     restore_idp_ti = __emit_thread_auto_cleanup();
     __st_insn(I_STOREA, AM_REG, restore_idp_ti, AM_REG, IDP_REG);
     }
   if ((__gening_tsk || tskp->can_be_disabled) && nxtstp != NULL
     && !nxtstp->enter_created)
    {
     /* SJM 11/06 - LOOATME must alloc bblks in order they are started or */
     /* else if insn needs to be inserted at end or beginning it will fail */
     ent_after_dsable_bbp = __alloc_bblk(FALSE); 
     after_ent_bbp = __alloc_bblk(FALSE);
     __emit_jmp(after_ent_bbp);

     ent_after_dsable_bbp->after_suspend = TRUE;
     __start_bblk(ent_after_dsable_bbp);
     __emit_enter_proc(nxtstp);
    }
   if (after_ent_bbp != NULL) __start_bblk(after_ent_bbp);
  }
}

/*
 * call an import DPI user code
 */
static void gen_tskcall_dpi(struct st_t *stp)
{
 struct task_pin_t *tpp;
 struct expr_t *tkxp, *xp, *lhsx;
 struct task_t *tskp;
 struct tskcall_t *tkcp;
 struct net_t *np;
 struct sy_t *syp;
 int32 rhs_apti, offset, nargs, i, pass_as_adr, save_idp_ti; 
 int32 num_strings;
 int32 *input_tmps, *wide_tmps, *string_tmps;
#ifndef __CVC32__
 int32 inreg_argno, onstk_argno, inreal_xmm_argno;
#endif

 tkcp = &(stp->st.stkc);
 tkxp = tkcp->tsksyx;
 syp = tkxp->lu.sy;
 tskp = syp->el.etskp;
 tpp = tskp->tskpins;

 lhsx = NULL;
 nargs = 0;
 wide_tmps = NULL;
 string_tmps = NULL;
 /* count the number of args */
 for (xp = tkcp->targs; xp != NULL; xp = xp->ru.x, tpp = tpp->tpnxt)
  {
   nargs++;
  }
 input_tmps = NULL;
 if (nargs != 0)
  {
   input_tmps = (int32 *) __my_malloc(nargs*sizeof(int32));
   string_tmps = (int32 *) __my_malloc(nargs*sizeof(int32));
   memset(input_tmps, 0, nargs*sizeof(int32));
   memset(string_tmps, 0, nargs*sizeof(int32));
  }
 tpp = tskp->tskpins;
 i = 0;
 num_strings = 0;
 /* AIV 11/15/10 - need to convert strings to C-style strings */
 /* need to do these first since use wrappers cannot set stack to call */
 /* DPI function until after all wrapper calls have been made */
 for (xp = tkcp->targs; xp != NULL; xp = xp->ru.x, tpp = tpp->tpnxt, i++)
  {
   np = tpp->tpsy->el.enp;
   lhsx = xp->lu.x;
   if (np->ntyp == N_STRING)
    {
     /* if output just make dummy space */
     if (tpp->trtyp == IO_OUT)
      {
       rhs_apti = __gen_tn(SR_BIT2S, 2048);
       __tntab[rhs_apti].tn_used_wide = TRUE;
       rhs_apti = __gen_stack_adr(rhs_apti);
      }
     //AIV LOOKATME - leaking memory here - for both stack and char * pointer 
     //nchars_ti = __gen_tn(SR_CINT, WBITS);
     else 
      {
       rhs_apti = __emit_sv_dpi_string(lhsx, -1);
       num_strings++;
      }
     string_tmps[i] = rhs_apti;    
    }
  }


 i = 0;
 offset = 0;
#ifndef __CVC32__
 inreg_argno = 0;
 onstk_argno = 0;
 inreal_xmm_argno = 0;
#endif
 tpp = tskp->tskpins;
 for (xp = tkcp->targs; xp != NULL; xp = xp->ru.x, tpp = tpp->tpnxt, i++)
  {
   /* assign rhs in or inout arg. expr. to task local variable */
   np = tpp->tpsy->el.enp;

   lhsx = xp->lu.x;
   /* this will pass one DPI argument depending on type - may pack */
   /* to SV type */
   rhs_apti = gen_arg_dpi(np, &pass_as_adr, lhsx, input_tmps, &wide_tmps, i, 
     tpp->trtyp, string_tmps);
#ifdef __CVC32__
   offset = __emit_call_func_arg_dpi(np, offset, rhs_apti, pass_as_adr, 
     tpp->trtyp);
#else
   __emit_call_func_arg_dpi(np, rhs_apti, pass_as_adr, 
     tpp->trtyp, &(inreg_argno), &(onstk_argno), &(inreal_xmm_argno));
#endif
  }
 /* AIV 05/23/12 - need to record the number of words passed to DPI wrapper */
 __cur_flowg->max_dpi_wrds = offset/WRDBYTES;

 /* AIV 11/15/10 - SV strings are just evaled - need to adjust stack */
 //AIV LOOKATME - leaking memory here - for both stack and char * pointer 
 //for string inputs, inout/outputs are freed in __sv_dpi_string_store
 if (num_strings > 0) __emit_pop_xstk(num_strings);

 /* need to save/restore idp since uses can now change using setScope */
 save_idp_ti = __emit_save_cur_idp();
 /* do the actual call to the user DPI code */
 __emit_call_func_dpi(tskp);
 __gen_restore_idp(save_idp_ti);

 tpp = tskp->tskpins;
 gen_assign_dpi_outputs(tkcp->targs, tpp, input_tmps, wide_tmps);
 
 if (input_tmps != NULL) 
  {
   __my_free(input_tmps, nargs*sizeof(int32));
   __my_free(string_tmps, nargs*sizeof(int32));
  }
}
   
/*
 * pass one argument to a DPI function - depending on type
 */
static int32 gen_arg_dpi(struct net_t *np, int32 *pass_as_adr, 
 struct expr_t *lhsx, int32 *input_tmps, int32 **wide_tmps, int32 argno, 
 int32 trtyp, int32 *string_tmps)
{
 int32 rhs_apti, rhs2_apti;
 int32 lhs_srep, want_a_vec, nbytes, needs_record, is_output, tmp_ti; 
 struct net_t *pass_np;
 struct expr_t *idndp;

 rhs_apti = -1;
 *pass_as_adr = FALSE;
 idndp = NULL;
 /* if passed net has record need to check for change */
 if (lhsx->optyp == GLBREF || lhsx->optyp == ID) idndp = lhsx;
 if (lhsx->optyp == LSB || lhsx->optyp == PARTSEL ||
     lhsx->optyp == PARTSEL_NDX_PLUS || lhsx->optyp == PARTSEL_NDX_MINUS) 
  {
   idndp = lhsx->lu.x;
  }
 if (idndp == NULL) 
  {
   needs_record = FALSE;
   pass_np = NULL;
  }
 else
  {
   pass_np = idndp->lu.sy->el.enp;
   needs_record = __net_chg_nd_store(pass_np, -1, -1);
  }

 if (np->ntyp == N_STRING)
  {
   rhs_apti = string_tmps[argno];

   /* DBG remove -- */  
   if (!rhs_apti) __misc_terr(__FILE__, __LINE__);
   /* ---- */ 
  }
 /* arrays are passed as entire array */
 else if (!np->n_isarr)
  {
   lhs_srep = __get_lhs_srep(lhsx, &nbytes);
   want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : -1;
   rhs2_apti = __gen_expr_eval(lhsx, want_a_vec);

   rhs_apti = cnvt_tskassgn_rhsexpr_ifneed(rhs2_apti, np, lhsx->is_real, 
     lhsx->has_sign); 
  }
 is_output = (trtyp == IO_OUT || trtyp == IO_BID);
 tmp_ti = -1;
 if (np->ntyp == N_STRING)
  {
//AIV WRITEME - string arrays
   /* DBG remove -- */ 
   if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
   /* ---- */ 
   /* if output need to create stack space to pass as char ** */
   if (is_output) 
    {
     rhs2_apti = rhs_apti;
     rhs_apti = __gen_tn(SR_BIT2S, WBITS);
     __st_insn(I_STOREA, AM_REG, rhs2_apti, AM_REG, rhs_apti);
     __tntab[rhs_apti].tn_used_wide = TRUE;
    }
   *pass_as_adr = TRUE;
   if (input_tmps != NULL) input_tmps[argno] = rhs_apti;
  }
//AIV FIXME - 64-bit must pack to these svLogicVecVal as 32 as well
 else if (np->n_isarr)
  {
   if (np->n_2state) 
    {
     /* DBG remove -- */ 
     if (pass_np == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     if (np->nwid == 1) 
      {
       /* packed scalar array into svLogicVecVal */
       rhs_apti = gen_packed_svLogicVecVal_array_scalar_dpi(np, trtyp, 
         needs_record);
       if (input_tmps != NULL) input_tmps[argno] = rhs_apti;
      }
#ifdef __CVC32__
     else if (np->nwid <= INTBITS) 
      {
       if (needs_record) 
        {
         rhs_apti = __gen_ld_netbp(pass_np);
         tmp_ti = __gen_tn(SR_VEC, np->nwid*np->arr_num_els);
         __tntab[tmp_ti].tn_used_wide = TRUE;
         __emit_copy(wlen_(np->nwid*np->arr_num_els)*WRDBYTES, rhs_apti, 
           tmp_ti);
         rhs_apti = tmp_ti;
         if (input_tmps != NULL) input_tmps[argno] = rhs_apti;
        }
       else rhs_apti = __gen_ld_netbp(pass_np);
      }
     else 
      {
       rhs_apti = gen_packed_svLogicVecVal_array_wide_dpi(pass_np, wide_tmps, 
         trtyp, needs_record);
       if (input_tmps != NULL) input_tmps[argno] = rhs_apti;
      }
#else
     else if (np->nwid <= INTBITS)
      {
       rhs_apti = gen_packed_svLogicVecVal_array_1w_packed_dpi(pass_np, 
         trtyp, needs_record);
      }
     else 
      {
       rhs_apti = gen_packed_svLogicVecVal_array_wide_dpi(pass_np, wide_tmps, 
        trtyp, needs_record);
      }
     if (input_tmps != NULL) input_tmps[argno] = rhs_apti;
#endif
     *pass_as_adr = TRUE;
    }
   else
    {
     /* DBG remove -- */ 
     if (pass_np == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     rhs_apti = gen_packed_svLogicVecVal_array_dpi(pass_np, trtyp, wide_tmps,
      needs_record);
     if (input_tmps != NULL) input_tmps[argno] = rhs_apti;
     *pass_as_adr = TRUE;
    }
  }
#ifdef __CVC32__
 /* 32-bit two state already in correct form */
 else if (np->nwid > INTBITS && !np->n_2state && np->ntyp != N_REAL)
#else
 /* AIV 09/16/10 - do not pack 64-bit pointers (chandles) */
 /* long long cint - passed as 64-bits in one reg here */
 else if (np->nwid > INTBITS && np->ntyp != N_REAL && np->ntyp != N_LONGCINT &&
          np->ntyp != N_CHANDLE)
#endif
  {
   rhs_apti = gen_packed_svLogicVecVal_dpi(np, rhs_apti, trtyp, needs_record);
   if (input_tmps != NULL) input_tmps[argno] = rhs_apti;
   *pass_as_adr = TRUE;
  }
 else 
  {
   if (np->n_isavec)
    {
     /* if c-style type (byte/int/etc) and input just pass value */
     if (!is_output && __is_cint_typ(np->ntyp))
      {
       tmp_ti = -1;
      }
     /* if input still passed as pointer so need to copy it */
     /* or if output has change record need to check for change from */
     /* original so must copy to tmp storage */
     else if (is_output && needs_record)
      {
       if (np->n_2state)
        {
         tmp_ti = __gen_tn(SR_BIT2S, np->nwid);
         __emit_copy(WRDBYTES, rhs_apti, tmp_ti);
        }
       else
        {
         tmp_ti = __gen_tn(SR_VEC, np->nwid);
         __emit_copy(2*WRDBYTES, rhs_apti, tmp_ti);
        }
      }
     else *pass_as_adr = TRUE;
    }
   else
    {
     if (is_output)
      {
       if (needs_record)
        {
         if (np->n_2state) tmp_ti = __gen_tn(SR_SCAL2S, 1);
         else tmp_ti = __gen_tn(SR_SCAL, 1);
         __emit_copy(WRDBYTES, rhs_apti, tmp_ti);
        }
       else *pass_as_adr = TRUE;
      }
    }
   /* only if it is wide or passed by address */
   if (tmp_ti != -1)
    {
     __tntab[tmp_ti].tn_used_wide = TRUE;
     *pass_as_adr = TRUE;
     if (input_tmps != NULL) input_tmps[argno] = tmp_ti;
     rhs_apti = tmp_ti;
    }
  }
 return(rhs_apti);
}
 
/*
 * assign DPI output values
 * AIV 11/16/10 - made this a routine since SV functions can have outputs 
 */
static void gen_assign_dpi_outputs(struct expr_t *argshd_xp, 
 struct task_pin_t *thdp, int32 *input_tmps, int32 *wide_tmps)
{
 int32 i, arg_ti, arg2_ti, srtyp, nbytes;
 struct task_pin_t *tpp;
 struct expr_t *xp, *lhsx;
 struct net_t *np;

 /* no inouts/outputs */
 if (thdp == NULL) return;

 tpp = thdp;
 i = 0;
 for (xp = argshd_xp; xp != NULL; xp = xp->ru.x, tpp = tpp->tpnxt, i++)
  {
   /* assign rhs in or inout arg. expr. to task local variable */
   np = tpp->tpsy->el.enp;
   /* skip inputs */
   if (tpp->trtyp == IO_IN) continue;

   if ((arg_ti = input_tmps[i]) == 0) continue;

   /* if string output need to copy back string value */
   lhsx = xp->lu.x;
   /* case 1 : string */
   if (np->ntyp == N_STRING)
    {
     np = lhsx->lu.sy->el.enp;
     __emit_sv_dpi_string_store(np, arg_ti);
     continue;
    }
   /* if it is an array - unpack from SV DPI types pack to CVC storage */
   /* case 2 array */
   if (np->n_isarr)
    {
     /* SJM - 03-03-13 - array non select check in fx3 chk 1tsk arg expr */
     np = lhsx->lu.sy->el.enp;
     gen_st_unpacked_svLogicVecVal_array_dpi(np, arg_ti, wide_tmps);
     continue;
    }
   /* case 3: may need unpacking */ 
   if (np->nwid > INTBITS && np->ntyp != N_REAL)
    {
     /* only packed if it is an input */
     arg2_ti = gen_unpacked_svLogicVecVal_dpi(np, arg_ti);
     gen2_proc_assign(lhsx, arg2_ti);
    }
   else if (np->ntyp == N_REAL)
    {
     /* SJM 03-02-13 - reals only direct connect allowed */
     gen2_proc_assign(lhsx, arg_ti);
    }
   else
    {
     /* SJM 02-07-13 - was not doing conversion when import arg type */
     /* does not match lhs output of dpi_ task to be assigned to */
     /* know the dpi c type from import statement */

     /* if needed gen conversion code to match up actual lhs expr arg */ 
     /* AIV 08/27/08 - if width of one assign as scalar */
     srtyp = __get_lhs_srep(lhsx, &nbytes);
     arg2_ti = __gen_cnvt_srep_ifneeded(arg_ti, srtyp, lhsx->szu.xclen,
      lhsx->has_sign, lhsx->is_real, FALSE);
      /* SJM 02-07-13 - same as get st one tfouts since now lhs concat works */
     gen2_proc_assign(lhsx, arg2_ti);
    }
  }
}

/*
 * generate the jump to task insn
 *
 * allocs the table that is dynamically linked and jumped thru at runtime
 */
static int32 gen_jmpto_tsk(struct sy_t *msym)
{
 int32 ndx;
 char s1[RECLEN];

 if (++__thdjmp_nxti >= __thdjmp_siz) grow_thdjmp_tab();
 ndx = __thdjmp_nxti;

 /* just add sym name ndx is later added to string name */
 sprintf(s1, "THD_JMP.%s", msym->synam); 
 __thdjmp_ret_tab[ndx] = __xi_stralloc(s1);
 return(ndx);
}

/*
 * generate the disable (really c style break) jump to end of named
 * block in function (tasks need thread cactus tree mechanism)
 *
 * allocs the table that is dynamically linked and jumped thru at runtime
 */
static int32 gen_jmpto_func_dsabl(struct sy_t *msym)
{
 int32 ndx;
 char s1[RECLEN];

 if (++__thdjmp_nxti >= __thdjmp_siz) grow_thdjmp_tab();
 ndx = __thdjmp_nxti;

 /* just add sym name ndx is later added to string name */
 sprintf(s1, "NBA_BRK.%s", msym->synam); 
 __thdjmp_ret_tab[ndx] = __xi_stralloc(s1);
 return(ndx);
}

/*
 * grow the thread jump within ams design table by reallocating
 */
static void grow_thdjmp_tab(void)
{
 size_t otabsiz, osize, nsize;

 otabsiz = __thdjmp_siz;
 osize = otabsiz*sizeof(char *);
 __thdjmp_siz = (3*otabsiz)/2; 
 nsize = __thdjmp_siz*sizeof(char *); 
 __thdjmp_ret_tab = (char **) __my_realloc(__thdjmp_ret_tab, osize, nsize);
}

/*
 * gen insns to eval actual task/func in params and store in tf locals
 * pass task call stmt
 *
 * assign to task vars since values persist - user tasks are value-result
 *
 * SJM 07/10/05 - interpreter assumes task ins/inouts can't be forced - is
 * that true?
 */
static void gen_st_tf_ins(struct st_t *call_stp, int32 idp_ti,
 struct gref_t *grp)
{
 struct task_pin_t *tpp;
 struct expr_t *tkxp, *xp;
 struct task_t *tskp;
 struct tskcall_t *tkcp;
 struct net_t *np;
 struct sy_t *syp;
 struct mod_t *mdp;

 tkcp = &(call_stp->st.stkc);
 tkxp = tkcp->tsksyx;
 syp = tkxp->lu.sy;
 tskp = syp->el.etskp;
 tpp = tskp->tskpins;

 if (grp != NULL) mdp = grp->targmdp;
 else mdp = __inst_mod;

 for (xp = tkcp->targs; xp != NULL; xp = xp->ru.x, tpp = tpp->tpnxt)
  {
   if (tpp->trtyp == IO_OUT) continue;

   /* assign rhs in or inout arg. expr. to task local variable */
   np = tpp->tpsy->el.enp;
   gen_st_one_tfins(np, xp->lu.x, idp_ti, mdp);
  }
}

/*
 * gen code to store one tf input actual parameter into formal
 *
 * Verilog parameters not stacked so stored into the one per func/inst
 * variable that gets overwritten
 *
 * itree context is the callers context - eval in caller then if XMR
 * store in task body variable formal argument
 */
static void gen_st_one_tfins(struct net_t *np, struct expr_t *argxp,
 int32 set_idp_ti, struct mod_t *mdp)
{
 int32 rhs_apti, rhs2_apti, addr_apti, save_idp_ti; 
 int32 lhs_srep, want_a_vec, nbytes; 
 int32 blen, ctab_ndx;
 struct xstk_t *xsp;
 struct expr_t *idndp;
 struct net_t *arg_np;

 save_idp_ti = -1;
 /* AIV - if from task called from function/task must set rhs to search */ 
 /* within that function for the rhs net then restore orig task */
 /* AIV 07/31/07 - if set_idp_ti know this is a global call so need to use */
 /* address for loading of the nets */
 if (set_idp_ti != -1)
  {
   __need_net_addr = TRUE;
  }

 /* if SV string need to handle with wrappers */
 if (np->ntyp == N_STRING)
  {
   /* case 1: rhs constant */
   if (argxp->consubxpr && argxp->optyp == NUMBER)
    {
     xsp = __eval_xpr(argxp);
     /* just load SV string as a constant value */
     blen = xsp->xslen;
     ctab_ndx = __allocfill_cval_new(xsp->ap, xsp->bp, wlen_(blen));
     __pop_xstk();
     rhs_apti = __gen_contab_tn(ctab_ndx, blen, FALSE, argxp->has_sign, FALSE, 
      SR_STRING);
     __emit_sv_string_st_const(np, rhs_apti);
    }
   /* case 2: rhs ID */
   else if (argxp->optyp == ID)
    {
     idndp = __get_lvalue_idndp(argxp);
     arg_np = idndp->lu.sy->el.enp;
     __emit_sv_string_st_var(np, arg_np);
    }
   /* case 3: rhs all other exprs */
   else
    {
     __emit_sv_string_st_eval_rhsx(np, argxp);
    }
   return;
  }
 /* AIV 11/10/09 - want a vector here */
 lhs_srep = __get_lhs_srep(argxp, &nbytes);
 want_a_vec = (lhs_srep == SR_VEC || lhs_srep == SR_BIT2S) ? WANT_A_VEC : -1;
 rhs2_apti = __gen_expr_eval(argxp, want_a_vec);

 /* AIV 01/09/08 - only the rhs needs to be loaded as addr */
 __need_net_addr = FALSE;

 rhs_apti = cnvt_tskassgn_rhsexpr_ifneed(rhs2_apti, np, argxp->is_real, 
   argxp->has_sign); 

 /* if xmr call, afer eval in cur. itree loc. must store in xmr dest */
 if (set_idp_ti != -1)
  {
   save_idp_ti = gen_push_save_idp(set_idp_ti);
   __push_wrkitstk(mdp, 0);
  }
 addr_apti = __ldvar_addr(np, NULL);

 /* think will always be change store */
 if (__net_chg_nd_store(np, -1, -1)) __gen_chg_st_val(np, addr_apti, rhs_apti);
 else __gen_st_val(np, addr_apti, rhs_apti);

 if (set_idp_ti != -1) 
  { 
//AIV IDP FIXME CVC
   __gen_restore_idp(save_idp_ti);
   __pop_wrkitstk(); 
  }
}

/*
 * convert rhs for task assign - works from flags not var properties
 */
static int32 cnvt_tskassgn_rhsexpr_ifneed(int32 rhs_apti, struct net_t *np,
 int32 rhsreal, int32 rhssign)
{
 int32 rhs2_apti, lhsreal;

 lhsreal = (np->ntyp == N_REAL);
 if (lhsreal)
  { 
   /* think passing packed bit does not work on all compilers ? */ 
   if (!rhsreal)
    {
     rhs2_apti = __gen_cnvt_srep_ifneeded(rhs_apti, SR_VEC, WBITS, TRUE,
      TRUE, TRUE);
    }
   else rhs2_apti = rhs_apti;
  }
 else
  { 
   /* AIV 08/29/06 - was passing the wrong srep for vec of size 1 */
   rhs2_apti = __gen_cnvt_srep_ifneeded(rhs_apti, np->srep, np->nwid, 
    rhssign, lhsreal, FALSE);
  }
 return(rhs2_apti);
}

/*
 * gen store task return output parameters
 * if disabled this code never executed
 *
 * assign to task vars since values persist - user tasks are value-result
 *
 * SJM 07/10/05 - interpreter assumes task ins/inouts can't be forced - is
 * that true?
 */
static void gen_st_tf_outs(struct st_t *call_stp, int32 save_idp_ti,
 struct mod_t *mdp)
{
 struct tskcall_t *tkcp; 
 struct task_pin_t *tpp;
 struct expr_t *tkxp, *xp;
 struct task_t *tskp;
 struct sy_t *syp;
 struct net_t *np;

 tkcp = &(call_stp->st.stkc);
 tkxp = tkcp->tsksyx;
 syp = tkxp->lu.sy;
 tskp = syp->el.etskp;
 tpp = tskp->tskpins;

 for (xp = tkcp->targs; xp != NULL; xp = xp->ru.x, tpp = tpp->tpnxt)
  {
   if (tpp->trtyp == IO_IN) continue;

   /* assign rhs in or inout arg. expr. to task local variable */
   np = tpp->tpsy->el.enp;
   gen_st_one_tfouts(np, xp->lu.x, save_idp_ti, mdp);
  }
}

/*
 * gen code to store one tf output actual parameter into formal
 * called from itree context of caller
 *
 * Verilog parameters not stacked so down formal argument net is loaded
 * into a tmp and then assigned to the up lhs actual argument expression
 */
static void gen_st_one_tfouts(struct net_t *intsk_np, struct expr_t *uplhsx,
 int32 set_idp_ti,  struct mod_t *mdp)
{
 int32 rhs_apti, rhs_addr_apti, nd_itpop, lhsnels, lxi, nbytes;
 int32 save_idp_ti, srtyp;
 struct expr_t *catndp, **lhsxtab;
 struct expr_t *idndp;
 struct net_t *np;

 /* if SV string need to handle with wrapper */
 if (intsk_np->ntyp == N_STRING)
  {
   if (uplhsx->optyp == ID)
    {
     idndp = __get_lvalue_idndp(uplhsx);
     np = idndp->lu.sy->el.enp;
     __emit_sv_string_st_var(np, intsk_np);
    }
   else __case_terr(__FILE__, __LINE__);
   return;
  }

 /* assigns to up must run in called task itree context */
 save_idp_ti = -1;
 if (set_idp_ti != -1)
  {
   save_idp_ti = gen_push_save_idp(set_idp_ti);
   __push_wrkitstk(mdp, 0);
   /* AIV 07/31/07 - if set_idp_ti know this is a global call so need to use */
   /* address for loading of the nets */
   __need_net_addr = TRUE;
   nd_itpop = TRUE;
  }
 else nd_itpop = FALSE;

 /* loading var addr is same as rhs eval where have net not expr */
 /* eval in called task so current task right */
 rhs_addr_apti = __ldvar_addr(intsk_np, NULL);
 /* AIV 01/09/08 - only the rhs needs to be loaded as addr */
 __need_net_addr = FALSE;


 /* AIV - if from task called from function/task must set rhs to search */ 
 /* within that function for the rhs net then restore orig task */
 /* if calling from task - global current task wrong - need from task */
 /* SJM 10/07/05 - since always restoring just set current task */

 /* if needed gen conversion code to match up actual lhs expr arg */ 
 /* AIV 08/27/08 - if width of one assign as scalar */
 srtyp = __get_lhs_srep(uplhsx, &nbytes);

 rhs_apti = __gen_cnvt_srep_ifneeded(rhs_addr_apti, srtyp, uplhsx->szu.xclen,
  uplhsx->has_sign, uplhsx->is_real, FALSE);
  
 /* if XMR task move back to caller to do assign */
 if (nd_itpop) 
  { 
   __gen_restore_idp(save_idp_ti);
   __pop_wrkitstk(); 
  }

 /* need assign from rhs expr - net loaded as addr - same as rhs eval */
 if (uplhsx->optyp == LCB)
  {
   lhsnels = __cnt_cat_size(uplhsx);
   lhsxtab = (struct expr_t **)
    __my_malloc(lhsnels*sizeof(struct expr_t *));
   lxi = lhsnels - 1;
   for (catndp = uplhsx->ru.x; catndp != NULL; catndp = catndp->ru.x, lxi--)
    { lhsxtab[lxi] = catndp->lu.x; }

   gen_lhs_concat2(rhs_addr_apti, lhsxtab, lhsnels, uplhsx->szu.xclen);

   /* and when done must free it */ 
   if (lhsxtab != NULL)
    __my_free(lhsxtab, lhsnels*sizeof(struct expr_t *));
  }
 else
  {
   gen2_proc_assign(uplhsx, rhs_apti);
  }
}

/*
 * ROUTINES TO GEN QUASI-CONTINOUS STMT VINSNS
 */

/*
 * generate insns for various type of quasi-continuous assign/force 
 */
static void gen_qconta(struct st_t *stp)
{
 struct expr_t *catndp;
 struct dceauxlstlst_t *dcllp;
 int32 catxlen, bi1; 
 struct expr_t *lhsx, *catlhsx;

 lhsx = stp->st.sqca->qclhsx;
 /* only possibilities are concat and ID */
 if (lhsx->optyp != LCB) 
  {
   gen_qconta_one_lhsx(stp, -1, lhsx, FALSE);
  }
 else
  {
   dcllp = stp->st.sqca->rhs_qcdlstlst;
   /* concatenate case know lhs full wire - tricky extractions of rhs */
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x,
    dcllp = dcllp->dcelstlstnxt)
    {
     catlhsx = catndp->lu.x;
     catxlen = catlhsx->szu.xclen;
     bi1 = catndp->szu.xclen - catxlen;
     gen_qconta_one_lhsx(stp, bi1, catlhsx, TRUE);
    }
  }
}

//REMOVEME SJM 09-07-12
// ??? static int32 frc_st_cnt = 0;

/*
 * generate insns for one lhs value quasi-continuous assign/force 
 */
static void gen_qconta_one_lhsx(struct st_t *stp, int32 bi, struct expr_t *lhsx,
 int32 is_concat)
{
 int32 stp_ti, lhsx_ti, biti_ti, np_ti;
 struct expr_t *idndp;
 int32 nchg_ti, biti, bitj, nchg_idp_ofs_ti;
 struct gref_t *grp;
 struct net_t *np;
 struct net_chg_t *ncp;

 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;
 /* if lhsx is an id or glbl id need -1 to indicate the whole net */
 /* __get_wc_wirrng returns the net's width */
 if (lhsx->optyp == ID || lhsx->optyp == GLBREF)
  {
   biti = bitj = -1;
  }
 else __get_qc_wirrng_comptime(lhsx, &np, &biti, &bitj); 

 grp = NULL;
 /* AIV 12/10/07 - note stmt must be generated from the __inst it is in */
 /* so must gen here becuase for xmr is pushing to grp's module */
 stp_ti = __gen_stmt_tn(stp);
 if (idndp->optyp == GLBREF)
  {
   grp = idndp->ru.grp;
   __xmrpush_refgrp_to_targ_compiletime(grp);
  }

 /* AIV 11/15/07 - need to pass idp because if xmr may need to recalc */
 /* the nchg this could be done if set here at runtime and not in wrapper */
 if (__net_chg_nd_store(np, biti, bitj))
  {
   ncp = __gen_netchg_addr_tn(np, biti, bitj, FALSE, &nchg_ti);
   /* AIV 11/17/08 - if called xmr was passing bad offset from idp reg */
   /* just needs to be != NULL (0) so will get the net change from */
   /* the __idp[nchg_idp_ofs at runtime */
   if (__inst_mod->flatinum > 1 && idndp->optyp == GLBREF)
    {
     nchg_ti = __gen_cint_tn(1); 
    }
   nchg_idp_ofs_ti = __gen_cint_tn(ncp->nchg_idp_ofs);
  }
 else 
  {
   nchg_ti = __gen_cint_tn(0); 
   nchg_idp_ofs_ti = nchg_ti;
  }

 /* AIV 08/13/08 - these qc assign were never handling the concat case */
 /* need to pass down the expression because it may be concat */
 /* AIV 03/02/12 - if force is not concat now using seperate routines which */
 /* do not require passing a fixed lhsx expr - since it is fixed and can */
 /* just access stp->st.sqca->qclhsx */
 if (is_concat)
  {
   lhsx_ti = __gen_xpr_tn(lhsx);
  }
 else lhsx_ti = -1;

 biti_ti = __gen_cint_tn(bi);
 if (stp->st.sqca->qcatyp == ASSIGN) 
  {
   /* qc assign needs flag giving reg/wire type - T is wire */ 
   __emit_exec_qc_assign(stp_ti, biti_ti, nchg_ti, nchg_idp_ofs_ti, lhsx_ti);
  }
 else if (stp->st.sqca->regform)
  {
   /* force of reg, is like assign except overrides assign */
   __emit_exec_qc_force(stp_ti, biti_ti, nchg_ti, nchg_idp_ofs_ti, lhsx_ti);
  }
 else
  {
   if (np->ntraux != NULL)
    {

//SJM 09-07-12 - REMOVEME
/* DBG remove --- 
   frc_st_cnt++;
   __cv_msg("++ force of wire %s (cnt=%d) memory usage = %ldK ++\n",
    np->nsym->synam, frc_st_cnt,  __mem_use/1000);
=== */

     /* must call again because this needs the nets width for vec case */
     if (np->n_isavec)
      {
       /* AIV 02/02/12 - if not rooted this was a problem because this */
       /* routine pushes as well so it would get __misc_terr finding mod */
       if (grp != NULL) __pop_itstk(); 
       __get_qc_wirrng_comptime(lhsx, &np, &biti, &bitj); 
       if (grp != NULL) __xmrpush_refgrp_to_targ_compiletime(grp);
       /* AIV 11/15/07 - force wrappers access the entire wire per bit nchg */
       /* AIV LOOKATME - currently need to mark the bit */
       if (__net_chg_nd_store(np, biti, biti))
        {
         for (bi = biti; bi >= bitj; bi--)
          {
           ncp = __gen_netchg_addr_tn(np, bi, bi, FALSE, &nchg_ti);
           ncp->is_lowered = TRUE;
          }
        }
      }
     /* wrapper starts with biti advancing for each bit of the vectors nchg */
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
     __emit_exec_qc_tran_wireforce(stp_ti, lhsx_ti, biti_ti, nchg_ti, 
       nchg_idp_ofs_ti);
     np_ti = __ld_netadr_tn(np);
     __gen_tran_1net(np, np_ti, FALSE);
    }
   else
    {
     __emit_exec_qc_wireforce(stp_ti, lhsx_ti, biti_ti, nchg_ti, 
        nchg_idp_ofs_ti);
    }
  }
 if (grp != NULL) __pop_itstk(); 
}


/*
 * AIV 08/19/09 - need seperate routine for compile time same as v_ex3.c
 * version expect must call seperate xmrget routine - no longer have 
 * idp area are compile time
 */
extern void __get_qc_wirrng_comptime(struct expr_t *lhsx, 
 struct net_t **nnp, int32 *biti, int32 *bitj)
{
 int32 bi;
 word32 *wp;
 struct gref_t *grp;
 struct net_t *np;
 struct expr_t *idndp, *ndx;

 np = NULL;
 grp = NULL; 
 switch (lhsx->optyp) {
  case GLBREF:
   grp = lhsx->ru.grp;
   __xmrpush_refgrp_to_targ_compiletime(grp);
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
     __xmrpush_refgrp_to_targ_compiletime(grp);
    }
   np = idndp->lu.sy->el.enp;
   /* know error before here if non in range constant value */ 
   if (lhsx->optyp == LSB) 
    {
     /* DBG remove -- */ 
     if (lhsx->ru.x->optyp != NUMBER) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     wp = &(__contab[lhsx->ru.x->ru.xvi]);
     if (wp[1] != 0) bi = -1; 
     else bi = (int32) wp[0];
     *bitj = *biti = bi;
    }
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
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   __get_indexed_psel_range(lhsx, biti, bitj);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (grp != NULL) __pop_itstk(); 
 *nnp = np;
}

/*
 * generate insns for various types of quasi-continuous assign/force 
 * LOOKATME - this is same as qcont assign except it is deassign
 */
static void gen_qcontdea(struct st_t *stp)
{
 struct expr_t *catndp;
 struct expr_t *lhsx, *catlhsx;

 lhsx = stp->st.sqcdea.qcdalhs;
 /* only possibilities are concat and ID */
 if (lhsx->optyp != LCB) 
  {
   gen_qcontdea_one_lhsx(stp, lhsx, FALSE);
  }
 else
  {
   /* concatenate case know lhs full wire - tricky extractions of rhs */
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     catlhsx = catndp->lu.x;
     gen_qcontdea_one_lhsx(stp, catlhsx, TRUE);
    }
  }
}

/*
 * generate one quasi-continuous deassign
 */
static void gen_qcontdea_one_lhsx(struct st_t *stp, struct expr_t *lhsx, 
 int32 is_concat)
{
 struct expr_t *idndp;
 int32 nchg_ti, biti, bitj, lhsx_ti, bi, nchg_idp_ofs_ti, np_ti, stp_ti; 
 struct net_t *np;
 struct net_chg_t *ncp;
 struct gref_t *grp;

 idndp = __get_lvalue_idndp(lhsx);
 np = idndp->lu.sy->el.enp;
 /* if lhsx is an id or glbl id need -1 to indicate the whole net */
 /* __get_wc_wirrng returns the net's width */
 if (lhsx->optyp == ID || lhsx->optyp == GLBREF)
  {
   biti = bitj = -1;
  }
 else __get_qc_wirrng_comptime(lhsx, &np, &biti, &bitj); 
 
 /* need to do this here prior to the push for xmr */
 if (!is_concat)
  {
   stp_ti = __gen_stmt_tn(stp);
  }
 else stp_ti = -1;

 grp = NULL;
 if (idndp->optyp == GLBREF)
  {
   grp = idndp->ru.grp;
   __xmrpush_refgrp_to_targ_compiletime(grp);
  }

 /* AIV 11/15/07 - need to pass idp because if xmr may need to recalc */
 /* the nchg this could be done if set here at runtime and not in wrapper */
 if (__net_chg_nd_store(np, biti, bitj))
  {
   ncp = __gen_netchg_addr_tn(np, biti, bitj, FALSE, &nchg_ti);
   /* AIV 11/17/08 - if called xmr was passing bad offset from idp reg */
   /* just needs to be != NULL (0) so will get the net change from */
   /* the __idp[nchg_idp_ofs at runtime */
   if (__inst_mod->flatinum > 1 && idndp->optyp == GLBREF)
    {
     nchg_ti = __gen_cint_tn(1); 
    }
   nchg_idp_ofs_ti = __gen_cint_tn(ncp->nchg_idp_ofs);
  }
 else 
  {
   nchg_ti = __gen_cint_tn(0); 
   nchg_idp_ofs_ti = nchg_ti;
  }

 /* AIV 03/02/12 - if force is not concat now using seperate routines which */
 /* do not require passing a fixed lhsx expr - since it is fixed and can */
 /* just access stp->st.sqca->qclhsx */
 if (is_concat)
  {
   lhsx_ti = __gen_xpr_tn(lhsx);
  }
 else lhsx_ti = -1;

 if (stp->st.sqcdea.qcdatyp == DEASSIGN)
  {
   if (is_concat) __emit_exec_qc_deassign_concat(lhsx_ti);
   else
    {
     __emit_exec_qc_deassign(stp_ti);
    }
  }
 else if (stp->st.sqcdea.regform)
  {
   __emit_exec_qc_deassign_force(stp_ti, lhsx_ti, nchg_ti, nchg_idp_ofs_ti);
  }
 else
  {
   if (np->ntraux != NULL)
    {
     /* must call again because this needs the nets width for vec case */
     if (np->n_isavec)
      {
       /* AIV 02/02/12 - if not rooted this was a problem because this */
       /* routine pushes as well so it would get __misc_terr finding mod */
       if (grp != NULL) __pop_itstk(); 
       __get_qc_wirrng_comptime(lhsx, &np, &biti, &bitj); 
       if (grp != NULL) __xmrpush_refgrp_to_targ_compiletime(grp);
       /* AIV 11/15/07 - force wrappers access the entire wire per bit nchg */
       /* AIV LOOKATME - currently need to mark the bit */
       if (__net_chg_nd_store(np, biti, biti))
        {
         for (bi = biti; bi >= bitj; bi--)
          {
           ncp = __gen_netchg_addr_tn(np, bi, bi, FALSE, &nchg_ti);
           ncp->is_lowered = TRUE;
          }
        }
      }
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
     __emit_exec_qc_tran_wirerelease(stp_ti, lhsx_ti, nchg_ti, nchg_idp_ofs_ti);
     np_ti = __ld_netadr_tn(np);
     __gen_tran_1net(np, np_ti, FALSE);
    }
   else
    {
     __emit_exec_qc_wirerelease(stp_ti, lhsx_ti, nchg_ti, nchg_idp_ofs_ti);
    }
  }

 if (grp != NULL) __pop_itstk(); 
}

/*
 * generate insns for cause stmt - here operand is stmt
 *
 * notice only simple net or xmr possible (although changes in v2k)
 * so iop uses expr
 */
static void gen_cause(struct st_t *stp)
{
 int32 stp_ti, nchg_ti;
 struct expr_t *xp;
 struct net_t *np;

 xp = stp->st.scausx;
 np = xp->lu.sy->el.enp;
 np->n_cause = TRUE;
 stp_ti = __gen_stmt_tn(stp);
 /* if has net change value get the address otherwise pass NULL */
 if (np->nlds != NULL || (np->ntyp < NONWIRE_ST && np->dcelst != NULL))
  {
   nchg_ti = -1;
   __gen_netchg_addr_tn(np, -1, -1, FALSE, &nchg_ti);
  }
 else nchg_ti = __gen_cint_tn(0);
 __emit_exec_cause(stp_ti, nchg_ti); 
}

/*
 * generate insns for disable
 */
static struct st_t *gen_disable(struct st_t *stp)
{
 int32 stp_ti, break_ti, funcbrk_ndx;
 struct expr_t *dsxp;
 struct sy_t *syp;
 struct task_t *tskp; 
 struct bblk_t *disable_elsewhere_bbp, *complete_bbp;
 struct bblk_t *start_bbp;

 dsxp = stp->st.sdsable.dsablx;
 syp = dsxp->lu.sy;
 tskp = syp->el.etskp;
 if (__processing_func)
  {
   /* SJM 10/19/05 - disable within func is either func ret or */
   /* or jmp to pass labeled block */
   if (syp->sytyp == SYM_F)
    {
     /* disable a function is a simple retun (c style break out of) */
     /* AIV 03/14/07 - function needs to return out of function */
     /* function can have only one return at end of block so jump to it */
     __emit_jmp(__func_complete_bbp); 
     /* need to start new block since jump must be at end of block */
     start_bbp = __alloc_bblk(FALSE);
     __start_bblk(start_bbp);
     return(NULL);
    }
   else
    { 
     /* works because func breaks are always forward jumps */
     if (tskp->dsa_brk_ndx != -1) funcbrk_ndx = tskp->dsa_brk_ndx;
     else
      {
       /* since exit from labeled blk, know current inst mod right */
       funcbrk_ndx = gen_jmpto_func_dsabl(__inst_mod->msym);
       tskp->dsa_brk_ndx = funcbrk_ndx; 
      }
     /* restore current stack before entering new return func location */
     __emit_leave();
     __emit_func_brk_jmp(funcbrk_ndx);
    }
   return(NULL);
  }

 /* SJM 11/15/06 - must allocate bblks in start order or insn numbering */
 /* if need to insert at start or end of bblk will not work */
 complete_bbp = __alloc_bblk(FALSE);
 disable_elsewhere_bbp = __alloc_bblk(FALSE);

 /* LOOKATME - need optimization here especially simple jumps */
 /* this set virt machine tmpi to non 0 if not disable this thrd or par */
 /* SJM 01/25/06 - always use but mod inst only wrong for declarative */
 stp_ti = __gen_stmt_tn(stp);
 break_ti = __emit_exec_dsable(stp_ti);

 /* interpreter wrapper sets to T/F */
 __emit_jmp_0(disable_elsewhere_bbp, complete_bbp, break_ti); 

 __start_bblk(complete_bbp);
 /* AIV 07/27/07 - if generating task know this is a named thread must */
 /* free task named block thread and the task it is entered so two cleanups */
 /* SJM??????? can there be one new asl wrapper to get handle these cases?? */
 /* cannot just do the complete here 
 if (__gening_tsk)
  {
   __emit_leave();
   __emit_tskdone_cleanup();
   __emit_tskdone_cleanup();
   __emit_tsk_return();
  }
 else __emit_complete();
 */
 __emit_complete();
 
 __start_bblk(disable_elsewhere_bbp);
 return(stp->stnxt);
}

/*
 * ROUTINES TO EMIT EXPR EVAL INSNS
 */

/*
 * emit insns to eval expression 
 * result can only be scalar, ab vec, or real 
 *
 * AIV 11/10/09 - this now takes xwid - a desired width
 * currently this is only used for bit selects where it can return
 * a scalar or a 1-bit vector - this saves double conversions
 */
extern int32 __gen_expr_eval(struct expr_t *ndp, int32 xwid)
{
 int32 res_apti;
 struct net_t *np;

 res_apti = -1;
 switch (ndp->optyp) {
  case ISNUMBER:
   /* this calculates the right conadr in the per const IS region */ 
   /* AIV 12/01/08 - should be ndp->has_sign no always TRUE */
   res_apti = __gen_ld_con_isptr(ndp, ndp->has_sign, FALSE);
   break;
  case NUMBER:
   /* always insert the load con adr insn but will be removed for non wide */
   res_apti = __gen_contab_tn(ndp->ru.xvi, ndp->szu.xclen, FALSE, 
    ndp->has_sign, FALSE, SR_VEC);
   break;
  case ISREALNUM:
   /* same as IS number except tn real type bit set */
   res_apti = __gen_ld_con_isptr(ndp, TRUE, TRUE);
   break;
  case REALNUM:
   /* SJM 04/11/05 - works because one contab per design - but has problems */
   res_apti = __gen_contab_tn(ndp->ru.xvi, ndp->szu.xclen, FALSE, 
    FALSE, TRUE, SR_VEC);
   break;
  case OPEMPTY:
   /* notice this now uses same contab place as interpreter */
   /* op empty is a sr vec with a part space and b part 0 */
   res_apti = __gen_tn(SR_VEC, 8);
   /* space is hex 0x20 */
   __emit_store_cint(res_apti, 0x20, 2*WRDBYTES);
   break;
  case UNCONNPULL:
   /* only for inst. input where down must be marked strength */
   __case_terr(__FILE__, __LINE__);
   break;
  case ID:
   np = ndp->lu.sy->el.enp;
   res_apti = __gen_ld_net_addr(np, NULL);
   break;
  case GLBREF:
   np = ndp->lu.sy->el.enp;
   res_apti = __gen_ld_net_addr(np, ndp->ru.grp);
   break;
  case LSB:
   np = ndp->lu.x->lu.sy->el.enp;
   /* handle SV string select case */
   if (np->ntyp == N_STRING) res_apti = gen_sel_string(ndp);
   else if (np->n_isarr) res_apti = gen_arrsel(ndp);
   else res_apti = gen_bsel(ndp, xwid);
   break;
  case PARTSEL:
   res_apti = gen_rhs_psel(ndp, xwid);
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   res_apti = gen_rhs_index_width_psel(ndp);
   break;
  case LCB:
   res_apti = gen_rhs_concat(ndp);
   break;
  case FCALL:
   if (ndp->lu.x->lu.sy->sytyp == SYM_SF) res_apti = gen_sysfcall(ndp);
   else res_apti = gen_fcall(ndp, NULL);
   break;
  case QUEST:
   /* notice that because of side effects, must evaluate in order */
   res_apti = gen_qcol(ndp);
   break;
  case REALREALQUEST: case REALREGQUEST:
   res_apti = gen_realselqcol(ndp);
   break;
  case REGREALQUEST:
   res_apti = gen_regrealqcol(ndp);
   break;
  default:
   if (ndp->ru.x == NULL) res_apti = gen_unop(ndp);
   else res_apti = gen_binop(ndp);
  }
 return(res_apti);
}

/*
 * load an internal storage location IS form per inst contab addr
 * from __idp offset area
 */
extern int32 __gen_ld_con_isptr(void *obj, int32 is_signed, int32 is_real)
{
 int32 idp_ofs, t1_ti;
 struct prep_obj_t *pop;
 struct tn_t *tnp;


 pop = __find_add_obj(__inst_mod->isnum_tree, obj);
 idp_ofs = pop->isnum_idp_ofs;
 /* DBG remove -- */ 
 if (__avl_node_is_new) __misc_terr(__FILE__, __LINE__);
 if (idp_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */

 t1_ti = __con_adradd_insn(SR_VEC, pop->blen, __idp_ti, idp_ofs*WRDBYTES);
 tnp = &(__tntab[t1_ti]);
 tnp->t_signed = is_signed; 
 tnp->t_real = is_real;
 return(t1_ti);
}

/*
 * gen insn to load net address (handles XMR and inum adjustment)
 */
extern int32 __gen_ld_net_addr(struct net_t *np, struct gref_t *grp)
{
 int32 res_ti;

 switch ((byte) np->srep) {
  case SR_VEC:
  case SR_BIT2S:
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     res_ti = gen_ld_is_apart_baseadr(np, grp);
    }
   else res_ti = gen_ld_nonis_vecvaradr(np);
   break;
  case SR_SVEC:
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     res_ti = __gen_ld_is_svec_varadr(np, grp);
    }
   else res_ti = __gen_ld_netbp(np);
   break;
  case SR_SCAL: case SR_SSCAL:
  case SR_SCAL2S:
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     res_ti = __gen_ld_is_svec_varadr(np, grp);
    }
   else res_ti = __gen_ld_netbp(np);
   break;
  default: res_ti = SR_UNKN; __case_terr(__FILE__, __LINE__);
 }
 return(res_ti);
}


// ##########################################################################
/*
 * ROUTINES TO LOAD NET (VAR) EITHER ADDR OR VALUE 
 */

/*
 * gen load addr v insns for variable (either ID or XMR)
 *
 * var addr is addr of the net correct for the current (or xmr) inst
 * mainly used to get per instance base for stores
 */
extern int32 __ldvar_addr(struct net_t *np, struct gref_t *grp)
{
 int32 addr_ti, xvi, wlen, sav_srep;
 word32 *ap, *bp;

 switch ((byte) np->srep) {
  case SR_VEC:
  case SR_BIT2S:
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     addr_ti = gen_ld_is_apart_baseadr(np, grp);
    }
   else addr_ti = __gen_ld_netbp(np);
   break;
  case SR_SVEC:
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     addr_ti = __gen_ld_is_svec_varadr(np, grp);
    }
   else addr_ti = __gen_ld_netbp(np);
   break;
  case SR_SCAL: case SR_SSCAL: case SR_SCAL2S:
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     addr_ti = __gen_ld_is_svec_varadr(np, grp);
    }
   else addr_ti = __gen_ld_netbp(np);
   break;
  case SR_PNUM: 
//AIV? - SR_PNUM should never have param loaded set - is not IS
  case SR_PISNUM: 
   /* AIV 10/21/05 - need to lower params as well */
   /* this is true for the param[index] case - works as follows: */
   /* if param has only one instances use as contstant otherwise must */
   /* lower into the comm_ file to be accessed using the __inum */
   /* change type to SR_VEC to treat as a regular vec value */
   /* AIV FIXME - changing to SR_VEC wrong what about other types ???? */
   /* AIV 01/13/06 - need to save and restore the srep param type */
   sav_srep = np->srep;
   np->srep = SR_VEC;
   /* if IS mark as loaded as use regular accessing scheme */
   if (__inst_mod->flatinum > 1 || grp != NULL)
    {
     /* AIV 03/06/07 - was doing svec always regular vec here */
     addr_ti = gen_ld_is_apart_baseadr(np, grp);
    }
   else
    {
     /* non-is just get contab hash and treat as a regular constant value */
     wlen = wlen_(np->nwid);
     ap = &(np->prm_nva.wp[0]);
     bp = &(np->prm_nva.wp[wlen]);
     xvi = __allocfill_cval_new(ap, bp, wlen);
     /* this is non IS case */
     addr_ti = __gen_contab_tn(xvi, np->nwid, FALSE, FALSE, FALSE, SR_VEC);
    }
   /* restore the srep param type */
   np->srep = sav_srep;
   break;
  default: { addr_ti = SR_UNKN; __case_terr(__FILE__, __LINE__); }
 }
 return(addr_ti);
}

/*
 * routine to load non IS sr vec resp only ptr
 * for wide but narrow ok if ptr needed
 *
 * this loads a part and then uses var adr offset insn to load b part adr 
 * if vec srep var is not a real
 */
static int32 gen_ld_nonis_vecvaradr(struct net_t *np) 
{
 int32 res_ti;

 /* DBG remove -- */
 if (np->srep != SR_VEC && np->srep != SR_BIT2S) 
    __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* this is ld sim state (ss) because ld tmp needs pr tmp reg ptr */
 /* SJM 02/09/05 - LOOKATME? net in pr tmp can be used to get signedness */
 res_ti = __gen_ld_netbp(np);
 if (np->ntyp == N_REAL)
  {
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
  }
 else
  {
   if (np->n_signed) __tntab[res_ti].t_signed = TRUE;
  }
 return(res_ti);
}

/*
 * routine to load a part of a/b form is var base
 *
 * also for reals since each takes 8 bytes (same as 32 bit vec)
 * AIV IDP FIXME - think this routine and next are the same now????
 * is the same expcept for the isparam code but this should be fixed in 
 * v_prp2.c to have the right value
 */
static int32 gen_ld_is_apart_baseadr(struct net_t *np, struct gref_t *grp)
{
 int32 base_apti, t1_ti, gref_ti, xmr_idp_ti, cint_ti;
 int32 inum_ti, iofs_ti;
 

 if (grp == NULL)
  {
   base_apti = __gen_ld_netbp(np); 
   return(base_apti);
  }
 else
  {
   __xmrpush_refgrp_to_targ_compiletime(grp);
   /* AIV 02/26/07 - if rooted rel is constant */
   /* need to catch the adradd case of 0 since offsets will be 0 */
   /* mashes consistency check for adradd of 0 */
   if (grp->is_rooted) 
    {
     t1_ti = __emit_xmr_rooted_base(np); 
    }
   else if (grp->upwards_rel) 
    {
     /* AIV 08/02/07 - if folding ports need to can get the known upward */
     /* instance and load as a constant */
     gref_ti = __gen_gref_tn(grp);
     xmr_idp_ti = __emit_ld_uprel_idp(gref_ti);
     t1_ti = __con_adradd_insn(np->srep, np->nwid, xmr_idp_ti, 
      np->nva_ofs*WRDBYTES);
    }
   else
    {
     gref_ti = __gen_gref_tn(grp);
     xmr_idp_ti = __emit_ld_downrel_idp(gref_ti);
     t1_ti = __con_adradd_insn(np->srep, np->nwid, xmr_idp_ti,
      np->nva_ofs*WRDBYTES);
    }
   __pop_itstk(); 
  }

     
//AIV IDP FIXME CVC - shouldn't these be adjusted in the __idp area - interp
//wrong as well
 /* if net is a parameter it isn't in mnets */
 /* a param can be loaded for more than 1st bsel */
 if (np->n_isaparam)
  {
   //AIV PARAM
   __misc_terr(__FILE__, __LINE__);
   inum_ti = __emit_inum();
   cint_ti = __gen_cint_tn(2*wlen_(np->nwid)*WRDBYTES);
   iofs_ti = __emit_mult(WBITS, inum_ti, cint_ti);
   t1_ti = __var_adradd_insn(SR_VEC, np->nwid, t1_ti, iofs_ti);
  }

 if (np->ntyp == N_REAL)
  {
   __tntab[t1_ti].t_real = TRUE;
   __tntab[t1_ti].tn_used_wide = TRUE;
  }
 else
  {
   if (np->n_signed) __tntab[t1_ti].t_signed = TRUE;
  }
 return(t1_ti);
}

/*
 * load a svec (including scalar that is 1 byte svec) IS base
 */
extern int32 __gen_ld_is_svec_varadr(struct net_t *np, struct gref_t *grp)
{
 int32 base_apti, t1_ti, gref_ti, xmr_idp_ti;

 if (grp == NULL)
  {
   base_apti = __gen_ld_netbp(np); 
   return(base_apti);
  }
 else
  {
   __xmrpush_refgrp_to_targ_compiletime(grp);
   /* AIV 02/26/07 - if rooted rel is constant */
   /* need to catch the adradd case of 0 since offsets will be 0 */
   /* mashes consistency check for adradd of 0 */
   if (grp->is_rooted) 
    {
     t1_ti = __emit_xmr_rooted_base(np); 
    }
   else if (grp->upwards_rel) 
    {
     gref_ti = __gen_gref_tn(grp);
     xmr_idp_ti = __emit_ld_uprel_idp(gref_ti);
     t1_ti = __con_adradd_insn(np->srep, np->nwid, xmr_idp_ti,
      np->nva_ofs*WRDBYTES);
    }
   else
    {
     gref_ti = __gen_gref_tn(grp);
     xmr_idp_ti = __emit_ld_downrel_idp(gref_ti);
     t1_ti = __con_adradd_insn(np->srep, np->nwid, xmr_idp_ti,
      np->nva_ofs*WRDBYTES);
    }
   __pop_itstk(); 
  }

 if (np->ntyp == N_REAL)
  {
   __tntab[t1_ti].t_real = TRUE;
   __tntab[t1_ti].tn_used_wide = TRUE;
  }
 else
  {
   if (np->n_signed) __tntab[t1_ti].t_signed = TRUE;
  }
 return(t1_ti);
}

/*
 * ROUTINES TO LOAD XMR INUM GIVEN NET AND GREF 
 */

/*
 * return the idp of the xmr reference 
 */
extern int32 __gen_ld_xmr_idp(struct gref_t *grp)
{
 int32 gref_ti, const_idp_ti, save_idp_ti, up_idp_ti, down_idp_ti;

 save_idp_ti = __emit_save_cur_idp();

 /* rooted case is constant */
 __xmrpush_refgrp_to_targ_compiletime(grp);
 /* AIV 12/12/07 - if only one module no need to call uprel/downrel */
 /* at runtime know will always be the one instance value */
 if (grp->is_rooted || __inst_mod->flatinum == 1) 
  {
   const_idp_ti = __gen_mdata_value(__inst_ptr);
   __memloc_emit_set_idp(const_idp_ti);
  }
 else if (grp->upwards_rel) 
  {
   /* upward instance path must be loaded */
   gref_ti = __gen_gref_tn(grp);
   up_idp_ti = __emit_ld_uprel_idp(gref_ti);
   __memloc_emit_set_idp(up_idp_ti);
  }
 else
  {
   /* downward instance path must be searched */
   gref_ti = __gen_gref_tn(grp);
   down_idp_ti = __emit_ld_downrel_idp(gref_ti);
   __memloc_emit_set_idp(down_idp_ti);
  }
 __pop_itstk(); 
 return(save_idp_ti);
}

/*
 * return the idp for the xmr task
 */
extern int32 __gen_ld_task_xmr_idp(struct gref_t *grp)
{
 int32 gref_ti, const_idp_ti, save_idp_ti, xmr_idp_ti;


 __xmrpush_refgrp_to_targ_compiletime(grp);
 /* AIV 12/12/07 - if only one module no need to call uprel/downrel */
 /* at runtime know will always be the one instance value */
 /* rooted case is constant */
 if (grp->is_rooted || __inst_mod->flatinum == 1) 
  {
   const_idp_ti = __gen_mdata_value(__inst_ptr);
   __pop_itstk(); 
   return(const_idp_ti);
  }
 else if (grp->upwards_rel) 
  {
   /* upward instance path must be loaded */
   gref_ti = __gen_gref_tn(grp);
   xmr_idp_ti = __emit_ld_uprel_idp(gref_ti);
  }
 else
  {
   /* downward instance path must be searched */
   gref_ti = __gen_gref_tn(grp);
   xmr_idp_ti = __emit_ld_downrel_idp(gref_ti);
  }

 __pop_itstk(); 
 save_idp_ti = __emit_save_idp(xmr_idp_ti);
 return(save_idp_ti);
}

/*
 * ROUTINES TO GEN VINSNS FOR RHS SELECTS
 */

/*
 * emit insns for to evaluate rhs bsel or rhs array select into tmp
 *
 * access a selected bit or array locaton on top of reg. stack
 * know width will be 1 if bit or array vector width if array
 *
 * this can be improved by assigning free reg not just pushing
 * for now not separating at compile time (stupid) so separate is done here
 *
 * AIV 11/10/09 - this now takes in xwid if <= 1 then return a scalar
 * value if xwid > 1 (WANT_A_VEC) then return a one bit vector
 */
static int32 gen_bsel(struct expr_t *ndp, int32 xwid)
{
 int32 addr_ti, bi_ti, res_ti, bsel_ti, cint_ti, bsel_bpti, res_bpti;
 struct expr_t *idndp;
 struct bblk_t *outofrng_bbp, *inrng_bbp, *after_bbp;
 struct net_t *np;

 /* if bit select constant handle as constant case */
 if (ndp->ru.x->optyp == NUMBER)
  {
   res_ti = gen_bsel_const(ndp, xwid); 
   return(res_ti);
  }
 res_bpti = -1;
 outofrng_bbp = __alloc_bblk(FALSE);
 inrng_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 
 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;

 /* can be either constant or expr. - both handled in comp. */
 bi_ti = __gen_comp_ndx(np, ndp->ru.x, outofrng_bbp, FALSE);
 __start_bblk(inrng_bbp);

 np = idndp->lu.sy->el.enp;
 /* for bsel load net addr */
 if (idndp->optyp == ID)
  {
   addr_ti = __ldvar_addr(np, NULL);
  }
 else if (idndp->optyp == GLBREF)
  {
   addr_ti = __ldvar_addr(np, idndp->ru.grp);
  }
 else { addr_ti = SR_UNKN; __case_terr(__FILE__, __LINE__); }

 /* notice both these routines handle per inst versus 1 inst */
 /* SJM 07/19/06 - var rhs bsel gens the tmp name but the const version */
 /* AIV 11/10/09 - now indicate if want a scalar or vec */
 if (xwid <= 1) 
  {
   if (np->n_2state) res_ti = __gen_tn(SR_SCAL2S, 1);
   else res_ti = __gen_tn(SR_SCAL, 1);
   bsel_ti = __gen_rhs_bsel_scalar_var(np, addr_ti, bi_ti); 
   /* AIV 10/06/05 - need to do copy into result in case value is x */
   /* wasn't placing out of range value and actual bsel in same result */
   __emit_copy(WRDBYTES, bsel_ti, res_ti);
   res_bpti = -1;
  }
 else
  {
   if (np->n_2state)
    {
     res_ti = __gen_tn(SR_BIT2S, 1);
     bsel_ti = __gen_rhs_bsel_var(np, addr_ti, bi_ti); 
     __emit_copy(WRDBYTES, bsel_ti, res_ti);
    }
   else
    {
     res_ti = __gen_tn(SR_VEC, 1);
     bsel_ti = __gen_rhs_bsel_var(np, addr_ti, bi_ti); 
     __emit_copy(WRDBYTES, bsel_ti, res_ti);
     bsel_bpti = __get_bpti(bsel_ti);
     res_bpti = __get_bpti(res_ti);
     __emit_copy(WRDBYTES, bsel_bpti, res_bpti);
    }
  }

 __emit_jmp(after_bbp);

 __start_bblk(outofrng_bbp); 
 /* gen twid x (a and b part used bits all 1s) */
//AIV 2STATE - out of range???? - making 0 for now????
 if (np->n_2state)
  {
   cint_ti = __gen_cint_tn(0);
   __emit_copy(WRDBYTES, cint_ti, res_ti);
  }
 else
  {
   if (res_bpti == -1)
    {
     cint_ti = __gen_cint_tn(3);
     __emit_copy(WRDBYTES, cint_ti, res_ti);
    }
   else
    {
     cint_ti = __gen_cint_tn(1);
     __emit_copy(WRDBYTES, cint_ti, res_ti);
     __emit_copy(WRDBYTES, cint_ti, res_bpti);
    }
  }
 /* this ends previous block and always jumps to after block - this is */
 /* code to jump over the else part of condition */
 __emit_jmp(after_bbp);
 __start_bblk(after_bbp);
 return(res_ti);
}
   
/* 
 * handle SV string select case - select or char of string
 */
static int32 gen_sel_string(struct expr_t *ndp)
{
 struct net_t *np;
 int32 res_apti, bi, bi_ti;


 np = ndp->lu.x->lu.sy->el.enp;
 /* AIV FIXME - due to the fact that most rhs string exprs are handled as */
 /* wrapper through interpreter this case should never occur */
 /* DBG REMOVE --- */
 if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* get a select of the char of the string */
 if (ndp->ru.x->optyp == NUMBER)
  {
   bi = __get_comp_num_ndx(ndp->ru.x);
   bi_ti = __gen_cint_tn(bi);
  }
 else bi_ti = __gen_expr_eval(ndp->ru.x, ndp->ru.x->szu.xclen);

 res_apti = __emit_get_string_byte(np, bi_ti);
 return(res_apti);
}

/*
 * bit select where bit select is a known constant 
 *
 * SJM 07/19/06 - notice rhs bsel const is passed result but
 * gen rhs bsel var creates the tn
 *
 * AIV 11/10/09 - this now takes in xwid if <= 1 then return a scalar
 * value if xwid > 1 (WANT_A_VEC) then return a one bit vector
 */
static int32 gen_bsel_const(struct expr_t *ndp, int32 xwid)
{
 int32 addr_ti, bi, res_ti, twid, cint_ti;
 struct expr_t *idndp;
 struct net_t *np;

 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;
 twid = ndp->szu.xclen;

 bi = __get_comp_num_ndx(ndp->ru.x);
 /* if -1 out of range always set to x */
 if (bi == -1)
  {
   /* gen twid x (a and b part used bits all 1s) */
   /* SJM 07/19/06 - since rhs bsel const gens tn - only gen here */
   if (xwid <= 1) 
    {
     if (np->n_2state) res_ti = __gen_tn(SR_SCAL2S, 1);
     else res_ti = __gen_tn(SR_SCAL, 1);
     cint_ti = __gen_cint_tn(3);
     __emit_copy(WRDBYTES, cint_ti, res_ti);
    }
   else 
    {
     res_ti = __gen_tn(SR_VEC, twid);
     gen_ab_setx(res_ti, FALSE);
    }
   return(res_ti);
  }

 np = idndp->lu.sy->el.enp;
 /* for bsel load net addr */
 if (idndp->optyp == ID)
  {
   addr_ti = __ldvar_addr(np, NULL);
  }
 else if (idndp->optyp == GLBREF)
  {
   addr_ti = __ldvar_addr(np, idndp->ru.grp);
  }
 else { addr_ti = SR_UNKN; __case_terr(__FILE__, __LINE__); }

 /* AIV 08/21/08 - better to return a scalar value for expr width 1 */
 /* AIV 11/10/09 - now indicate if want a scalar or vec */
 if (xwid <= 1) res_ti = __gen_rhs_bsel_scalar_const(np, addr_ti, bi); 
 else res_ti = __gen_rhs_bsel_const(np, addr_ti, bi); 
 return(res_ti);
}

/*
 * generate code for store bsel from rhs_ti into addr_apti
 * does both the a and b part and know index compile time constant
 * 
 * this routines is for storing bits into tns not nets
 */
extern void __gen_st_bsel(int32 srtyp, int32 res_apti, int32 rhs_ti, 
 int32 bi)
{
 int32 bi1, wofs, twid, hghw_apti, hghw_bpti, rhs_bpti, hw_ofs;
 int32 cint_ti, is_2state;

 is_2state = (srtyp == SR_BIT2S);
 hghw_bpti = -1;
 if (bi >= WBITS)
  {
   wofs = get_wofs_(bi);
   bi1 = get_bofs_(bi);
   hghw_apti = __con_adradd_insn(SR_VEC, WBITS, res_apti,
    WRDBYTES*wofs);
   if (!is_2state)
    {
     twid = __get_tnwid(res_apti);
     hw_ofs = WRDBYTES*(wlen_(twid) + wofs);
     hghw_bpti = __con_adradd_insn(SR_VEC, WBITS, res_apti, hw_ofs);
    }
  }
 else 
  {
   hghw_apti = res_apti;
   if (!is_2state) hghw_bpti = __get_bpti(res_apti);
   bi1 = bi;
  }

 /* AIV 10/27/09 - now handle scalars here - produces better code */
 __emit_st_const_bsel(hghw_apti, rhs_ti, bi1);
 if (is_2state) return;

 if (__tntab[rhs_ti].srtyp == SR_SCAL)
  {
   cint_ti = __gen_cint_tn(1);
   rhs_bpti = __emit_shiftr(1, cint_ti, rhs_ti);
  }
 else rhs_bpti = __get_bpti(rhs_ti);
 __emit_st_const_bsel(hghw_bpti, rhs_bpti, bi1);
}

/*
 * same as gen_bsel except net base acess is different because of
 * inum used in computing of array index
 */
static int32 gen_arrsel(struct expr_t *ndp)
{
 int32 addr_ti, bi_ti, res_ti, blen, arrsel_ti, nbytes, cint_ti, bi;
 int32 nd_pop, save_idp_ti, srtyp;
 struct expr_t *idndp, *sel_ndx, *ndx1;
 struct bblk_t *outofrng_bbp, *inrng_bbp, *after_bbp;
 struct net_t *np;
 struct gref_t *grp;
 struct mod_t *targ_mdp;
 struct mda_t *mdap;

 /* if bit select constant handle as constant case */
 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;
 blen = ndp->szu.xclen;

 mdap = np->mda;
 ndx1 = ndp->ru.x;
 sel_ndx = ndx1->next_ndx;
 /* if not mda or is mda with all constant values handle as regular select */
 if (ndp->ru.x->optyp == NUMBER && (mdap == NULL || ndx1->folded_ndx))
  {
   bi = __get_comp_num_ndx(ndx1);
   if (idndp->optyp == GLBREF)
    {
     grp = idndp->ru.grp;
    }
   else grp = NULL;

   res_ti = __gen_arrsel_const(np, bi, blen, grp); 
   /* AIV 05/12/10 - if it is a scalar array there is nothing to select it */
   /* is just the low bit - was attempting to bpart a scalar here */
   if (sel_ndx != NULL && np->nwid != 1)
    {
     res_ti = gen_rhs_arr_select(sel_ndx, np, res_ti);
    }

   if (ndp->is_real)
    {
     __tntab[res_ti].t_real = TRUE;
     __tntab[res_ti].tn_used_wide = TRUE;
    }
   return(res_ti);
  }
 outofrng_bbp = __alloc_bblk(FALSE);
 inrng_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 
 /* if mda compute the index otherwise just get single index */
 if (mdap != NULL)
  {
   bi_ti = gen_comp_mda_ndx(np, mdap, ndx1, outofrng_bbp, &sel_ndx);
  }
 else
  {
   bi_ti = __gen_comp_ndx(np, ndx1, outofrng_bbp, FALSE);
  }

 __start_bblk(inrng_bbp);

 nd_pop = FALSE;
 /* for arr sel load actual net base addr since inum used in indexing */
 np = idndp->lu.sy->el.enp;
 save_idp_ti = -1;
 if (idndp->optyp == ID)
  {
   addr_ti = __gen_ld_netbp(np);
  }
 else if (idndp->optyp == GLBREF)
  {
   /* AIV 02/03/06 - need to push module gen_rhs_arr checks for flatinum */
   /* and array index is computed using __inum */
   /* AIV LOOKATME - this is all constant information - could fold info */
   save_idp_ti = __gen_ld_xmr_idp(idndp->ru.grp);
   targ_mdp = idndp->ru.grp->targmdp; 
   __push_wrkitstk(targ_mdp, 0);
   addr_ti = __gen_ld_netbp(np);
   nd_pop = TRUE;
  }
 else { addr_ti = SR_UNKN; __case_terr(__FILE__, __LINE__); }

 /* notice both these routines handle per inst versus 1 inst */
 /* AIV 10/06/05 - need to do copy into result in case value is x */
 /* wasn't placing out of range value and actual arr sel in same result */
 arrsel_ti = gen_rhs_arrsel_var(np, addr_ti, bi_ti); 

 /* AIV 05/12/10 - if it is a scalar array there is nothing to select it */
 /* is just the low bit - was attempting to bpart a scalar here */
 if (ndx1->arr_select && np->nwid != 1)
  {
   arrsel_ti = gen_rhs_arr_select(sel_ndx, np, arrsel_ti);
   /* if has select width is now that of the select range */
   blen = sel_ndx->szu.xclen;
  }

 srtyp = __get_array_srep_type(np);
 if (blen == 1) 
  {
   if (srtyp == SR_SCAL2S)
    {
     res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL2S, 1, AM_REG, arrsel_ti);
    }
   else
    {
     cint_ti = __gen_cint_tn(3);
     res_ti = __emit_srep_mask_and(SR_SCAL, 1, cint_ti, arrsel_ti);
    }
  }
 else 
  {
   if (srtyp == SR_BIT2S)
    {
     nbytes = wlen_(blen)*WRDBYTES;
     res_ti = __gen_tn(SR_BIT2S, blen);
    }
   else
    {
     nbytes = 2*wlen_(blen)*WRDBYTES;
     res_ti = __gen_tn(SR_VEC, blen);
    }
   __emit_copy(nbytes, arrsel_ti, res_ti);
  }

 if (nd_pop) 
  { 
   __gen_restore_idp(save_idp_ti);
   __pop_wrkitstk(); 
  }

 __emit_jmp(after_bbp);

 __start_bblk(outofrng_bbp);

 /* gen insns to set twid svec a/b tmp to x's (unused bits 0) */
 /* if scalar just make x */
 if (blen == 1)
  {
   cint_ti = __gen_cint_tn(3);
   __emit_copy(WRDBYTES, cint_ti, res_ti);
  }
 else gen_ab_setx(res_ti, FALSE);

 /* this ends previous block and always jumps to after block - this is */
 /* code to jump over the else part of condition */
 __emit_jmp(after_bbp);

 __start_bblk(after_bbp);
 /* if result is real must set real bit */
 if (ndp->is_real) 
  {
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
  }
 /* AIV 01/04/07 - if array is signed so it the tmp */
 if (np->n_signed) __tntab[res_ti].t_signed = TRUE;
 return(res_ti);
}

/*
 * for the last value of the array select on rhs get select value
 * select can be psel/indexed psel/bsel
 *
 */
static int32 gen_rhs_arr_select(struct expr_t *sel_ndx, struct net_t *np,
 int32 arrval_ti)
{
 int32 res_ti, bi_ti, bi, numbits, bi1, bi2, rng1_ti, rng2_ti, numbits_ti;
 int32 selbi_ti, res_bpti;
 int32 bytsiz, srtyp;
 word32 ri2;
 struct expr_t *ndx1, *ndx2;
 struct bblk_t *outofrng_bbp, *inrng_bbp;
 

 /* fixed value psel */
 srtyp = __get_array_srep_type(np);
 if (sel_ndx->optyp == PARTSEL)
  {
   ndx1 = sel_ndx->ru.x->lu.x;
   ndx2 = sel_ndx->ru.x->ru.x;
   bi1 = __contab[ndx1->ru.xvi];
   bi2 = __contab[ndx2->ru.xvi];

   numbits = bi1 - bi2 + 1;
   if (numbits <= WBITS) 
    {
     /* this is in one word but not necessarily the low word */
     res_ti = gen_in1wrd_rhs_psel(srtyp, arrval_ti, bi2, numbits);
    }
   else
    {
     res_ti = __gen_fradr_rhs_psel(srtyp, arrval_ti, numbits, bi1, bi2);
    }
  }
 /* variable value indexed psel */
 else if (sel_ndx->optyp == PARTSEL_NDX_PLUS || 
          sel_ndx->optyp == PARTSEL_NDX_MINUS)
  {
   outofrng_bbp = __alloc_bblk(FALSE);
   res_ti = __gen_tn(srtyp, sel_ndx->szu.xclen);
   /* AIV 05/31/09 - need to init wide case to 0 - only need to do this */
   /* for the wide case because movl's will init word case but not each */
   /* word of the wide psel */
   if (sel_ndx->szu.xclen > WBITS)
    {
     if (srtyp == SR_BIT2S)
      {
       bytsiz = wlen_(sel_ndx->szu.xclen)*WRDBYTES;
      }
     else bytsiz = 2*wlen_(sel_ndx->szu.xclen)*WRDBYTES;
     __emit_store_cint(res_ti, 0, bytsiz);
    }
   numbits_ti = get_indexed_psel_range(&rng1_ti, &rng2_ti, &ri2, res_ti, 
    sel_ndx, np, outofrng_bbp, -1);

   gen_rhs_iw_psel(arrval_ti, res_ti, rng2_ti, numbits_ti, np->nwid, 
     sel_ndx->szu.xclen, srtyp);

   __start_bblk(outofrng_bbp);
  }
 else 
  {
   /* bit select */
   if (sel_ndx->optyp == NUMBER)
    {
     bi = __get_comp_num_ndx(sel_ndx);
     res_ti = __gen_rhs_bsel_const(np, arrval_ti, bi); 
    }
   else 
    {
     outofrng_bbp = __alloc_bblk(FALSE);
     inrng_bbp = __alloc_bblk(FALSE);

     /* AIV 01/01/12 - this needs to make a tmp and copy it here */
     /* if it was out of range res_ti was never set need to init and copy */
     if (np->n_2state) 
      {
       res_ti = __gen_tn(SR_BIT2S, 1);
       /* init to 0 */
       __emit_store_cint(res_ti, 0, WRDBYTES);
      }
     else 
      {
       /* init to x */
       res_ti = __gen_tn(SR_VEC, 1);
       __emit_store_cint(res_ti, 1, WRDBYTES);
       res_bpti = __get_bpti(res_ti);
       __emit_store_cint(res_bpti, 1, WRDBYTES);
      }

     bi_ti = __gen_comp_ndx(np, sel_ndx, outofrng_bbp, TRUE);
     __start_bblk(inrng_bbp);
     selbi_ti = __gen_rhs_bsel_var(np, arrval_ti, bi_ti); 
     __emit_copy(2*WRDBYTES, selbi_ti, res_ti);
     __start_bblk(outofrng_bbp);
    }
  }
 return(res_ti);
}

/*
 * gen array select where select is constant
 * same as gen_arrsel except doesn't check range
 */
extern int32 __gen_arrsel_const(struct net_t *np, int32 bi, int32 twid,
 struct gref_t *grp)
{
 int32 addr_ti, arrsel_ti, cint_ti, save_idp_ti, res_ti;
 int32 nd_pop, nbytes, srtyp;

 if (bi == -1)
  {
   /* if -1 out of range always set to x */
//AIV 2STATE - out of range????
   if (np->nwid == 1) 
    {
     res_ti = __gen_tn(SR_SCAL, 1);
     cint_ti = __gen_cint_tn(3);
     __emit_copy(WRDBYTES, cint_ti, res_ti);
    }
   else 
    {
     res_ti = __gen_tn(SR_VEC, twid);
     gen_ab_setx(res_ti, FALSE);
    }
   /* AIV 11/10/09 - this should return if -1 here */
   if (np->n_signed) __tntab[res_ti].t_signed = TRUE;
   return(res_ti);
  }
 
 save_idp_ti = -1;
 nd_pop = FALSE;
 /* for arr sel load actual net base addr since inum used in indexing */
 if (grp != NULL)
  {
   save_idp_ti = __gen_ld_xmr_idp(grp);
   __xmrpush_refgrp_to_targ_compiletime(grp);
   addr_ti = __gen_ld_netbp(np);
   nd_pop = TRUE;
  }
 else addr_ti = __gen_ld_netbp(np);

 arrsel_ti = gen_rhs_arrsel_const(np, addr_ti, bi); 

 if (nd_pop) 
  { 
   /* AIV 11/10/09 - only need the copy if it is a gref copy out of idp ofs */
   /* AIV 09/02/08 - this needs to copy a whole word to zero high part of reg */
   /* this was causing the scalar arrays to fail because high part non-zero */
   srtyp = __get_array_srep_type(np);
   if (np->nwid == 1) 
    {
     res_ti = __gen_tn(srtyp, 1);
     __emit_copy(WRDBYTES, arrsel_ti, res_ti);
    }
   else
    {
     res_ti = __gen_tn(srtyp, twid);
     nbytes = wlen_(twid)*WRDBYTES;
     if (srtyp != SR_BIT2S) nbytes *= 2;
     __emit_copy(nbytes, arrsel_ti, res_ti);
    }
   /* AIV 01/04/07 - if array is signed so it the tmp */
   if (np->n_signed) __tntab[res_ti].t_signed = TRUE;
   __gen_restore_idp(save_idp_ti);
   __pop_itstk(); 
   return(res_ti);
  }
 /* AIV 01/04/07 - if array is signed so it the tmp */
 if (np->n_signed) __tntab[arrsel_ti].t_signed = TRUE;
 return(arrsel_ti);
}

/*
 * gen insns to set a/b vec to x (all 1's in used a and b parts)
 *
 * SJM 10/03/05 - set x insn didn't mask off a/b part unused high bits right
 */
static void gen_ab_setx(int32 res_apti, int32 skip_2state_zero)
{
 int32 blen, bytsiz, ubits, res_hw_apti, res_hw_bpti;
 int32 mask_ti, wlen, res_bpti, hw_ofs, srtyp;
 word32 mask;

//AIV 2STATE - just zero?????
 blen = __get_tnwid(res_apti);
 if (!skip_2state_zero && __tmp_is_2state(res_apti))
  {
   __emit_store_cint(res_apti, 0, wlen_(blen)*WRDBYTES);
   return;
  }
 srtyp = __tntab[res_apti].srtyp;
 /* AIV 08/30/10 - this routine must handle scalar now as well */
 /* just set to scalar 'bx */
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   __emit_store_cint(res_apti, 3, WRDBYTES);
   return;
  }

 ubits = ubits_(blen);
 if (ubits == 0)
  {
   __emit_setall1(res_apti, 2*wlen_(blen)*WRDBYTES);
   return;
  }

 mask = (__masktab[ubits] & ALL1W);
 mask_ti = __gen_cint_tn(mask);
 /* set twid bit x (1's in both a and b parts) */
 if (blen > WBITS)
  {
   wlen = wlen_(blen) - 1;
   bytsiz = wlen*WRDBYTES;
   __emit_setall1(res_apti, bytsiz);
   res_bpti = __get_bpti(res_apti);
   __emit_setall1(res_bpti, bytsiz);
   res_hw_apti = __con_adradd_insn(SR_VEC, blen, res_apti, bytsiz);
   hw_ofs = (2*wlen_(blen) - 1)*WRDBYTES;
   res_hw_bpti = __con_adradd_insn(SR_VEC, blen, res_apti, hw_ofs);
  }
 else
  {
   res_hw_apti = res_apti;
   res_hw_bpti = __get_bpti(res_apti);
  }
 __emit_copy(WRDBYTES, mask_ti, res_hw_apti);
 __emit_copy(WRDBYTES, mask_ti, res_hw_bpti);
}

/*
 * gen insns to set oneword (a part) vec to x 
 */
static void gen_oneword_setx(int32 res_ti)
{
 int32 blen, bytsiz, ubits, res_hw_ti;
 int32 mask_ti, wlen;
 word32 mask;

 blen = __get_tnwid(res_ti);
 ubits = ubits_(blen);
 if (ubits == 0) 
  {
   __emit_setall1(res_ti, wlen_(blen)*WRDBYTES);
   return;
  }

 mask = (__masktab[ubits] & ALL1W);
 mask_ti = __gen_cint_tn(mask);
 /* set twid bit x (1's in both a and b parts) */
 if (blen > WBITS)
  {
   wlen = wlen_(blen) - 1;
   bytsiz = wlen*WRDBYTES;
   __emit_setall1(res_ti, bytsiz);
   res_hw_ti = __con_adradd_insn(SR_VEC, blen, res_ti, bytsiz);
  }
 else res_hw_ti = res_ti;

 __emit_copy(WRDBYTES, mask_ti, res_hw_ti);
}

/*
 * generate vm insns where index is known to be constant expr (number)
 * if need -1, known at compile time so just returns tmp constant
 *
 * can't use for IS numbers or params
 */
extern int32 __get_comp_num_ndx(struct expr_t *ndx)
{
 int32 wlen, indi;

 wlen = wlen_(ndx->szu.xclen);
 if (!vval_is0_(&(__contab[ndx->ru.xvi + wlen]), ndx->szu.xclen)
  || (ndx->szu.xclen > WBITS
  && !vval_is0_(&(__contab[ndx->ru.xvi + 1]), ndx->szu.xclen - WBITS))) 
  {
   indi = -1;
  }
 else indi = (int32) __contab[ndx->ru.xvi];
 return(indi);
}

/*
 * emit instructions to compute variable select index 
 * need x/z, out of range testing and normalizing
 *
 * returns a sr vec but know b part always 0
 */
extern int32 __gen_comp_ndx(struct net_t *np, struct expr_t *ndx, 
 struct bblk_t *outofrng_bbp, int32 need_net_width)
{
 int32 ri1, ri2, obwid;

 /* should never call this with a constant index */
 /* DBG REMOVE --- */
 if (ndx->optyp == NUMBER) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* fall thru to in range */
 /* sizes are compile time */
 if (!need_net_width && np->n_isarr)
  {
   ri1 = np->nu.rngarr->ai1;
   ri2 = np->nu.rngarr->ai2;
   obwid = (ri1 >= ri2) ? (ri1 - ri2 + 1) : (ri2 - ri1 + 1);
  }
 else
  {
   /* SJM 06/13/04 - is compile time (CT) representation possible here? */
   if (np->nrngrep == NX_CT)
    {
     ri1 = (int32) __contab[np->nu.ct->nx1->ru.xvi];
     ri2 = (int32) __contab[np->nu.ct->nx2->ru.xvi];
    }
   else
    {
     ri1 = np->nu.rngdwir->ni1;
     ri2 = np->nu.rngdwir->ni2;
    }
   obwid = np->nwid;
  }
 return(gen_comp_ndx_range(np, ndx, ri1, ri2, obwid, outofrng_bbp));
}

/*
 * AIV 02/19/09 - made a separarte routine to share same code as mda
 *
 * emit instructions to compute variable select index 
 */
static int32 gen_comp_ndx_range(struct net_t *np, struct expr_t *ndx, 
 int32 ri1, int32 ri2, int32 obwid, struct bblk_t *outofrng_bbp)
{
 int32 tmpndx_ti, tmpndx_bpti, biti_ti, bi_ti, cint_ti, srtyp;
 struct bblk_t *inrng_bbp, *inrng2_bbp;

 /* alloc accum */
 tmpndx_ti = __gen_expr_eval(ndx, -1);
 /* AIV 08/25/10 - can have an array index - cannot just pass srep */
 if (__is_2state_typ(np->ntyp)) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;

 /* emit conversion load - copies tmp nam index if no conversion */
 tmpndx_ti = __gen_cnvt_srep_ifneeded(tmpndx_ti, srtyp, WBITS, FALSE, FALSE,
    FALSE);

 /* notice whether number (so no normalize range check needed) or not */
 /* known at compile time so can generate 2 different code sequences */
 /* any x bits in b part causes index to be set to -1 */
 if (srtyp != SR_BIT2S)
  {
   inrng_bbp = __alloc_bblk(FALSE);
   tmpndx_bpti = __get_bpti(tmpndx_ti);
   __emit_jmp_0(inrng_bbp, outofrng_bbp, tmpndx_bpti);
   /* fall thru to normalize */
   __start_bblk(inrng_bbp);
  }

 /* since know b part 0, convert a part to cint */ 
 biti_ti = tmpndx_ti;

 /* always need 2nd part of range for normalizing */
 /* SJM 05/14/05 - these should be done with int arithmetic */
 cint_ti = __gen_cint_tn(ri2);
 if (ri1 >= ri2) bi_ti = __emit_sub(WBITS, biti_ti, cint_ti);
 else bi_ti = __emit_sub(WBITS, cint_ti, biti_ti);

 /* know res ti a part only */
 inrng2_bbp = __alloc_bblk(FALSE);
 /* check for out of range */
 /* biti >= obwid  same as obwid < biti goto out of range */ 
 /* AIV 10/23/08 - this can be calculated with one compare */
 /* if (biti >= 23 || biti < 0) */
 /* cmpl  $22, biti */
 /* jbe  true_label */	
 cint_ti = __gen_cint_tn(obwid-1);
 __emit_jmp_cmp(inrng2_bbp, outofrng_bbp, bi_ti, cint_ti, CC_JLE);

 __start_bblk(inrng2_bbp);
 /* after block */ 
 if (__tntab[bi_ti].tn_typ == TN_ADR) 
  {
   bi_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, bi_ti);
  }
 return(bi_ti);
}
     
/*
 * compute the multi-dimensional array index return the compute tmp
 * the select expr (if there is one) is the last expr returned in sel_ndx
 * 
 */
static int32 gen_comp_mda_ndx(struct net_t *np, struct mda_t *mdap, 
 struct expr_t *ndx1, struct bblk_t *after_bbp, struct expr_t **sel_ndx)
{
 struct expr_t *ndx;
 int32 i, arrndx_ti, ndx_ti, cint_ti, t1_ti; 
 word32 val;

 /* narri = arri * mdap->dim_mult[0]; */
 ndx = ndx1;
 arrndx_ti = -1;
 for (i = 0; i < mdap->dimension; i++)
  {
   /* constant index */
   if (ndx->optyp == NUMBER) 
    {
     val = __contab[ndx->ru.xvi];
     /* DBG remove -- */
     if (__contab[ndx->ru.xvi + 1] != 0) __misc_terr(__FILE__, __LINE__);
     /* ----- */
     t1_ti = __gen_cint_tn(mdap->dim_mult[i]*val);
    }
   else
    {
     /* variable compute the index */
     ndx_ti = gen_one_dim_mda_ndx(np, mdap, ndx, i, after_bbp);
     cint_ti = __gen_cint_tn(mdap->dim_mult[i]);
     t1_ti = __emit_mult(WBITS, cint_ti, ndx_ti);
    }
   /* accumulate the index */
   if (i == 0) arrndx_ti = t1_ti;
   else
    {
     arrndx_ti = __emit_add(WBITS, t1_ti, arrndx_ti);
    }
   ndx = ndx->next_ndx;
  }
 *sel_ndx = ndx;
 return(arrndx_ti);
}

/*
 * check one variable of a multi-dim array at runtime jump to outofrng_bbp
 * if variable is out of dimension range at rt
 */
static int32 gen_one_dim_mda_ndx(struct net_t *np, struct mda_t *mdap, 
 struct expr_t *ndx, int32 dim, struct bblk_t *outofrng_bbp)
{
 int32 ri1, ri2, obwid;

 /* DBG remove -- */
 if (ndx->optyp == NUMBER) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* sizes are compile time */
 ri1 = mdap->rng1[dim];
 ri2 = mdap->rng2[dim];
 obwid = (ri1 >= ri2) ? (ri1 - ri2 + 1) : (ri2 - ri1 + 1);
 /* AIV 02/19/09 - this can share same range check as bsel */
 return(gen_comp_ndx_range(np, ndx, ri1, ri2, obwid, outofrng_bbp));
}


/*
 * gen insns to load rhs array select
 *
 * generates different types of pr tmps depending on array type - 
 * word ptr for wide, word for packed, and 4 value byte in 32 bit
 * word for scalar
 */
static int32 gen_rhs_arrsel_var(struct net_t *np, int32 addr_ti,
 int32 bi_ti)
{
 int32 blen, res_ti, eladdr_ti, elofs_ti, t1_bpti, cint_ti, mask_ti; 
 int32 pckeladr_ti, pck_apti, pck_bpti, r1_ti, is_wire, srtyp;
 word32 mask;

 blen = np->nwid;
 if (blen == 1)
  {
   res_ti = gen_ld_scalar_arrsel_var(np, addr_ti, bi_ti);
   return(res_ti);
  } 

 /* AIV 02/24/09 - can have arrays of wire now - handle as seperate case */
 /* since there is no packing */
 is_wire = (np->ntyp < NONWIRE_ST);
 srtyp = __get_array_srep_type(np);
 /* AIV 09/01/10 - 2-state array are no longer packed */
 if (is_wire || blen > WBITS/2 || srtyp == SR_BIT2S)
  {
   /* case 1: unpacked - each vector element takes more than one word  */
   eladdr_ti = gen_ndxarr_ptr_var(np, addr_ti, bi_ti);
   return(eladdr_ti);
  }
 /* packed into byte, hword or word */ 

 /* get the elements start byte */
 elofs_ti = gen_pck_ofset_var(np, bi_ti);
 /* add offset to the byte addr of the element to access */ 
 pckeladr_ti = __var_adradd_insn(srtyp, blen, addr_ti, elofs_ti);

 mask = __masktab[np->nwid];
 /* mask off b part in a part */
 mask_ti = __gen_cint_tn(mask);
 pck_apti = __gen_tn(srtyp, WBITS);
 r1_ti = __emit_mask_and(pckeladr_ti, mask_ti);
 __emit_copy(WRDBYTES, r1_ti, pck_apti);

 /* copy into b part */
 cint_ti = __gen_cint_tn(np->nwid);
 t1_bpti = __emit_shiftr(WBITS, cint_ti, pckeladr_ti);
 r1_ti = __emit_mask_and(t1_bpti, mask_ti);

 pck_bpti = __get_bpti(pck_apti);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, r1_ti, pck_bpti);

 return(pck_apti);
}

/*
 * generate one rhs array select with known constant index
 */
static int32 gen_rhs_arrsel_const(struct net_t *np, int32 addr_ti, int32 bi)
{
 int32 blen, res_ti, eladdr_ti, t1_bpti, cint_ti, is_wire, srtyp; 
 int32 pckeladr_ti, pck_apti, pck_bpti, mask_ti, res_bpti, elofs;
 word32 mask;
 
 blen = np->nwid;
 if (blen == 1)
  {
   res_ti = gen_ld_scalar_arrsel_const(np, addr_ti, bi);
   return(res_ti);
  } 

 /* AIV 02/24/09 - can have arrays of wire now - handle as seperate case */
 /* since there is no packing */
 is_wire = (np->ntyp < NONWIRE_ST);
 srtyp = __get_array_srep_type(np);
 /* AIV 09/01/10 - 2-state array are no longer packed */
 if (is_wire || blen > WBITS/2 || srtyp == SR_BIT2S)
  {
   /* case 1: unpacked - each vector element takes more than one word  */
   eladdr_ti = gen_ndxarr_ptr_const(np, addr_ti, bi);
   return(eladdr_ti);
  }
 /* packed into byte, hword or word */ 

 /* get the elements start byte */
 elofs = gen_pck_ofset_const(np, bi);
 /* add offset to the byte addr of the element to access */ 
 pckeladr_ti = __con_adradd_insn(srtyp, blen, addr_ti, elofs);

 mask = __masktab[np->nwid];
 /* mask off b part in a part */
 mask_ti = __gen_cint_tn(mask);
 /* AIV 11/10/09 - need blen here now no reason for extra copy */
 res_ti = __gen_tn(srtyp, blen);
 pck_apti = __emit_mask_and(pckeladr_ti, mask_ti);
 __emit_copy(WRDBYTES, pck_apti, res_ti);

 /* copy into b part */
 cint_ti = __gen_cint_tn(np->nwid);
 t1_bpti = __emit_shiftr(WBITS, cint_ti, pckeladr_ti);
 pck_bpti = __emit_mask_and(t1_bpti, mask_ti);
 res_bpti = __get_bpti(res_ti);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, pck_bpti, res_bpti);
 return(res_ti);
}

/*
 * gen scalar array load insns - for variable (loaded into tmp nam) index
 *
 * LOOKATME - result put in 32 bit 2v (3 bit) pr tmp (not byte and not a/b)
 * is this right?
 */
static int32 gen_ld_scalar_arrsel_var(struct net_t *np, int32 addr_ti, 
 int32 bi_ti)
{
 int32 t1_ti, wbyti_ti, bofs_ti, indi_ti, ascalwptr_ti, cint_ti;
 int32 mask_ti, r1_ti, srtyp, is_2state;

 srtyp = __get_array_srep_type(np);
 /* if 2-state no 2*index */
 if (srtyp == SR_SCAL2S) is_2state = TRUE;
 else is_2state = FALSE;

 /* compute the scalar packed array bit off (2 bits per element) */

 if (is_2state) indi_ti = bi_ti;
 else 
  {
   cint_ti = __gen_cint_tn(2);
   indi_ti = __emit_mult(WBITS, bi_ti, cint_ti);
  }

 /* compute the word (wi) and bit (bi) offsets for bit to store into */
 wbyti_ti = gen_scalarr_wbyti_bofs(&(bofs_ti), indi_ti);

 /* ptr to the word containing the 2 bits to change */
 ascalwptr_ti = __var_adradd_insn(SR_VEC, 1, addr_ti, wbyti_ti);
 t1_ti = __emit_shiftr(1, bofs_ti, ascalwptr_ti);

 /* AIV 11/16/05 - need to mask the two low bits */
 if (is_2state) mask_ti = __gen_cint_tn(1);
 else mask_ti = __gen_cint_tn(3);
 r1_ti = __emit_srep_mask_and(srtyp, 1, t1_ti, mask_ti);
 return(r1_ti);
}

/*
 * gen scalar array load insns - for constant (literal) index case 
 *
 * same as non-constant version expcept taking advantage of bi known constant
 */
static int32 gen_ld_scalar_arrsel_const(struct net_t *np, int32 addr_ti, 
 int32 bi)
{
 int32 wi, t1_ti, indi, ascalwptr_ti;
 int32 cint_ti, mask_ti, r1_ti, srtyp, is_2state;

 /* take advantage of bi known constant */
 srtyp = __get_array_srep_type(np);
 /* if 2-state no 2*index */
 if (srtyp == SR_SCAL2S) is_2state = TRUE;
 else is_2state = FALSE;

 if (is_2state) indi = bi;
 else indi = 2*bi;

 wi = get_wofs_(indi);
 bi = get_bofs_(indi);

 ascalwptr_ti = __con_adradd_insn(SR_VEC, 1, addr_ti, wi*WRDBYTES);
 cint_ti = __gen_cint_tn(bi);
 t1_ti = __emit_shiftr(1, cint_ti, ascalwptr_ti);
 /* AIV 03/01/07 - was returning t1_ti need to return the masked value */
 if (is_2state) mask_ti = __gen_cint_tn(1);
 else mask_ti = __gen_cint_tn(3);
 r1_ti = __emit_srep_mask_and(srtyp, 1, t1_ti, mask_ti); 
 return(r1_ti);
}

/*
 * gen insns for rhs bit select from variable index
 * returns a/b but high 16 bits are b part pr tmp reg and low a part
 */
extern int32 __gen_rhs_bsel_var(struct net_t *np, int32 var_apti, int32 bi_ti) 
{
 int32 bofs_ti, wbyti_ti;
 int32 res_apti, res_bpti, wadr_apti, wadr_bpti;
 int32 r1_ti, r2_ti, r3_ti, r4_ti, one_ti;

 /* handle strength bsel */
 if (__tntab[var_apti].srtyp == SR_SVEC)
  {
   res_apti = gen_rhs_strength_bsel(var_apti, bi_ti, FALSE); 
   return(res_apti);
  }

 /* AIV 11/10/09 - this should have width one not WBITS */
 if (np->n_2state) res_apti = __gen_tn(SR_BIT2S, 1);
 else res_apti = __gen_tn(SR_VEC, 1);

 wbyti_ti = gen_wbyti_bofs(var_apti, &(bofs_ti), bi_ti);
 /* isolate the 1 bit */
 if (wbyti_ti != -1)
  {
   wadr_apti = comp_ndxwrd_addr(var_apti, wbyti_ti);
  }
 else wadr_apti = var_apti;


 r1_ti = __emit_shiftr(WBITS, bofs_ti, wadr_apti);
 one_ti = __gen_cint_tn(1);
 r2_ti = __emit_mask_and(r1_ti, one_ti);
 __emit_copy(WRDBYTES, r2_ti, res_apti);
 if (np->n_2state) return(res_apti);

 /* can just get corresponding b part - do not need to index again */
 wadr_bpti = __get_bpti(wadr_apti); 
 r3_ti = __emit_shiftr(WBITS, bofs_ti, wadr_bpti);
 r4_ti = __emit_mask_and(r3_ti, one_ti);
 res_bpti = __get_bpti(res_apti); 
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, r4_ti, res_bpti);
 return(res_apti);
}


/*
 * do a bit select returned as a scalar value
 */
extern int32 __gen_rhs_bsel_scalar_var(struct net_t *np, int32 var_apti, 
 int32 bi_ti) 
{
 int32 bofs_ti, wbyti_ti, srtyp;
 int32 res_ti, wadr_apti, wadr_bpti;
 int32 r1_ti, r2_ti, r3_ti, r4_ti, r5_ti, r6_ti, one_ti;

 /* handle strength bsel */
 if (__tntab[var_apti].srtyp == SR_SVEC)
  {
   res_ti = __gen_rhs_strength_scalar_bsel_var(var_apti, bi_ti); 
   return(res_ti);
  }

 wbyti_ti = gen_wbyti_bofs(var_apti, &(bofs_ti), bi_ti);
 /* isolate the 1 bit */
 if (wbyti_ti != -1)
  {
   wadr_apti = comp_ndxwrd_addr(var_apti, wbyti_ti);
  }
 else wadr_apti = var_apti;


 r1_ti = __emit_shiftr(WBITS, bofs_ti, wadr_apti);
 one_ti = __gen_cint_tn(1);

 if (np->n_2state)
  {
   r2_ti = __emit_srep_mask_and(SR_SCAL2S, 1, r1_ti, one_ti);
   return(r2_ti);
  }
 r2_ti = __emit_mask_and(r1_ti, one_ti);
 /* can just get corresponding b part - do not need to index again */
 wadr_bpti = __get_bpti(wadr_apti); 
 r3_ti = __emit_shiftr(WBITS, bofs_ti, wadr_bpti);
 r4_ti = __emit_mask_and(r3_ti, one_ti);

 /* pack value into a scalar value */
 r5_ti = __emit_shiftl(1, one_ti, r4_ti);
 /* AIV 03/04/09 - better code produced with an add here than or */
 /* notice this is the same for all 4 scalar states */
 r6_ti = __emit_add(1, r2_ti, r5_ti); 
 /* AIV 09/14/10 - this should just be a move srep */
 if (np->n_2state) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;
 res_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1, AM_REG, r6_ti);
 return(res_ti);
}

/*
 * do a strength bit select returned as a scalar value
 */
extern int32 __gen_rhs_strength_scalar_bsel_var(int32 var_apti, int32 bi) 
{
 int32 t1_ti, t2_ti, t3_ti, t4_ti, t5_ti, t6_ti, one_ti, res_ti;

 /* get byte addr + bi */
 t1_ti = __var_adradd_insn(SR_VEC, WBITS, var_apti, bi);

 one_ti = __gen_cint_tn(1);
 t3_ti = __emit_mask_and(t1_ti, one_ti); 

 /*  rgbp[0] = (uwrd >> 1) & 1L */
 t2_ti = __emit_shiftr(2, one_ti, t1_ti);
 t4_ti = __emit_mask_and(t2_ti, one_ti);

 t5_ti = __emit_shiftl(1, one_ti, t4_ti);
 /* AIV 03/04/09 - better code produced with an add here than or */
 /* notice this is the same for all 4 scalar states */
 t6_ti = __emit_add(1, t3_ti, t5_ti); 
 /* AIV 09/14/10 - this should just be a move srep */
 res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, t6_ti);
 return(res_ti);
}

/*
 * rhs bit select where bit select is a known constant 
 * SJM 09/21/06 - notice numeric index passed that is converted into cint tn 
 */
extern int32 __gen_rhs_bsel_const(struct net_t *np, int32 var_apti, int32 bi) 
{
 int32 res_apti, res_bpti, wadr_apti, wadr_bpti, cint_ti;
 int32 wi, twid, r1_ti, r2_ti, r3_ti, r4_ti, one_ti, b_ofs;

 /* handle strength bsel */
 if (__tntab[var_apti].srtyp == SR_SVEC)
  {
   res_apti = gen_rhs_strength_bsel(var_apti, bi, TRUE); 
   return(res_apti);
  }
 
 /* AIV 11/10/09 - this should have width one not WBITS */
 if (np->n_2state) res_apti = __gen_tn(SR_BIT2S, 1);
 else res_apti = __gen_tn(SR_VEC, 1);
 wi = get_wofs_(bi);
 bi = get_bofs_(bi); 

 wadr_bpti = -1;
 if (wi != 0)
  {
   wadr_apti = __con_adradd_insn(SR_VEC, __get_tnwid(var_apti), var_apti,
    wi*WRDBYTES);
   if (!np->n_2state)
    {
     twid = __get_tnwid(wadr_apti);
     b_ofs = (wi + wlen_(twid))*WRDBYTES;
     wadr_bpti = __con_adradd_insn(SR_VEC, __get_tnwid(var_apti),
      var_apti, b_ofs);
    }
  }
 else 
  {
   wadr_apti = var_apti;
   if (!np->n_2state) wadr_bpti = __get_bpti(wadr_apti); 
  }

 cint_ti = __gen_cint_tn(bi);
 r1_ti = __emit_shiftr(WBITS, cint_ti, wadr_apti);

 one_ti = __gen_cint_tn(1);
 r2_ti = __emit_mask_and(r1_ti, one_ti);
 __emit_copy(WRDBYTES, r2_ti, res_apti);
 if (np->n_2state) return(res_apti);

 cint_ti = __gen_cint_tn(bi);
 r3_ti = __emit_shiftr(WBITS, cint_ti, wadr_bpti);
 r4_ti = __emit_mask_and(r3_ti, one_ti);
 res_bpti = __get_bpti(res_apti); 
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, r4_ti, res_bpti);
 return(res_apti);
}

/*
 *
 * same as regular bsel expcept this version backs into scalar value
 */
extern int32 __gen_rhs_bsel_scalar_const(struct net_t *np, int32 var_apti, 
 int32 bi) 
{
 int32 wadr_apti, wadr_bpti, cint_ti, srtyp, res_ti;
 int32 wi, twid, r1_ti, r2_ti, r3_ti, r4_ti, r5_ti, r6_ti, one_ti, b_ofs;

 /* handle strength bsel */
 if (__tntab[var_apti].srtyp == SR_SVEC)
  {
   res_ti = gen_rhs_strength_bsel(var_apti, bi, TRUE); 
   return(res_ti);
  }
 wi = get_wofs_(bi);
 bi = get_bofs_(bi); 

 wadr_bpti = -1;
 if (wi != 0)
  {
   wadr_apti = __con_adradd_insn(SR_VEC, __get_tnwid(var_apti), var_apti,
    wi*WRDBYTES);
   if (!np->n_2state)
    {
     twid = __get_tnwid(wadr_apti);
     b_ofs = (wi + wlen_(twid))*WRDBYTES;
     wadr_bpti = __con_adradd_insn(SR_VEC, __get_tnwid(var_apti),
      var_apti, b_ofs);
    }
  }
 else 
  {
   wadr_apti = var_apti;
   if (!np->n_2state) wadr_bpti = __get_bpti(wadr_apti); 
  }

 cint_ti = __gen_cint_tn(bi);
 r1_ti = __emit_shiftr(WBITS, cint_ti, wadr_apti);

 one_ti = __gen_cint_tn(1);
 if (np->n_2state)
  {
   r2_ti = __emit_srep_mask_and(SR_SCAL2S, 1, r1_ti, one_ti);
   return(r2_ti);
  }

 r2_ti = __emit_mask_and(r1_ti, one_ti);

 cint_ti = __gen_cint_tn(bi);
 r3_ti = __emit_shiftr(WBITS, cint_ti, wadr_bpti);
 r4_ti = __emit_mask_and(r3_ti, one_ti);
 /* notice copies follow gas movl [from],[to] format */
 /* pack value into a scalar value */
 r5_ti = __emit_shiftl(1, one_ti, r4_ti);
 /* AIV 03/04/09 - better code produced with an add here than or */
 /* notice this is the same for all 4 scalar states */
 r6_ti = __emit_add(1, r2_ti, r5_ti); 
 /* AIV 09/14/10 - this should just be a move srep */
 if (np->n_2state) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;
 res_ti = __move_srep_insn(TN_VAL, I_MOVA, srtyp, 1, AM_REG, r6_ti);
 return(res_ti);
}

/*
 * strength rhs bit select where bit select is a known constant 
 * uwrd = (word32) np->nva.bp[__inum*np->nwid + biti];
 */
extern int32 gen_rhs_strength_bsel(int32 var_apti, int32 bi, int32 is_const) 
{
 int32 res_apti, res_bpti, t1_ti, t2_ti, one_ti, r1_ti, r2_ti;

 /* AIV 08/14/10 FIXME - shouldn't this return a SR_SVEC and just do a */
 /* conadr to get the byte???? - is expecting SR_VEC - in some places */
 res_apti = __gen_tn(SR_VEC, 1);
 /* get byte addr + bi */
 if (is_const)
  {
   t1_ti = __con_adradd_insn(SR_VEC, WBITS, var_apti, bi);
  }
 else t1_ti = __var_adradd_insn(SR_VEC, WBITS, var_apti, bi);

 one_ti = __gen_cint_tn(1);
 r1_ti = __emit_mask_and(t1_ti, one_ti); 

 /* isolate the byte with a copy */
 /* AIV 10/10/06 - was incorrectly copy only a byte need to copy one word */
 /* the byte is allocated with the and the word is need to zero tmp storage */
 __emit_copy(WRDBYTES, r1_ti, res_apti);

 /*  rgbp[0] = (uwrd >> 1) & 1L */
 res_bpti = __get_bpti(res_apti);
 t2_ti = __emit_shiftr(2, one_ti, t1_ti);
 r2_ti = __emit_mask_and(t2_ti, one_ti);
 /* AIV 11/29/06 - need to copy whole word not a single byte */
 __emit_copy(WRDBYTES, r2_ti, res_bpti);
 return(res_apti);
}

/*
 * emit instructions to compute rhs part select
 * know range constant so no out of range or x/z testing
 *
 * these are written as wide masks but will be reduced from a/b region
 * word32 offsets
 *
 * SJM 02/07/05 - FIXME - how make sure psel a/b contiguous?
 */
static int32 gen_rhs_psel(struct expr_t *ndp, int32 xwid)
{
 struct expr_t *ndx1, *ndx2;
 int32 bi1, bi2, numbits, addr_apti, res_apti;
 int32 lhs_srep, nbytes;
 struct expr_t *idndp;
 struct net_t *np;

 /* know these are both constant nodes */
 ndx1 = ndp->ru.x->lu.x;
 ndx2 = ndp->ru.x->ru.x;
 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;

 bi1 = __contab[ndx1->ru.xvi];
 bi2 = __contab[ndx2->ru.xvi];
 numbits = bi1 - bi2 + 1;

 /* SJM 11/21/04 - for now only decompose if fits in one word */
 if (idndp->optyp == ID) addr_apti = __ldvar_addr(np, NULL);
 else if (idndp->optyp == GLBREF)
  {
   addr_apti = __ldvar_addr(np, idndp->ru.grp);
  }
 else { addr_apti = SR_UNKN; __case_terr(__FILE__, __LINE__); }

 /* AIV 02/12/07 - if range of net is the same as psel just return net */
 /* AIV 09/13/10 - ranges don't need to match just the width */
 if (numbits == np->nwid) 
  {
   return(addr_apti);
  }

 if (numbits == 1) 
  {
   /* need vector bsel version here */
   if (xwid <= 1) res_apti = __gen_rhs_bsel_scalar_const(np, addr_apti, bi1); 
   else res_apti = __gen_rhs_bsel_const(np, addr_apti, bi1); 
   return(res_apti);
  }

 lhs_srep = __get_lhs_srep(ndp, &nbytes);
 if (numbits <= WBITS) 
  {
   /* this is in one word but not necessarily the low word */
   res_apti = gen_in1wrd_rhs_psel(lhs_srep, addr_apti, bi2, numbits);
  }
 else
  {
   res_apti = __gen_fradr_rhs_psel(lhs_srep, addr_apti, numbits, bi1, bi2);
  }
 return(res_apti);
}
   
/*
 * generate code for index psels +: and -:
 */
static int32 gen_rhs_index_width_psel(struct expr_t *ndp)
{
 int32 addr_apti, res_apti, sbp_ti, srtyp;
 int32 rng1_ti, rng2_ti, numbits_ti, bytsiz, is_2state;
 word32 ri2;
 struct bblk_t *done_bbp;
 struct expr_t *idndp;
 struct net_t *np;

 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;

 /* SJM 11/21/04 - for now only decompose if fits in one word */
 if (idndp->optyp == ID) addr_apti = __ldvar_addr(np, NULL);
 else if (idndp->optyp == GLBREF)
  {
   addr_apti = __ldvar_addr(np, idndp->ru.grp);
  }
 else { addr_apti = SR_UNKN; __case_terr(__FILE__, __LINE__); }

 if (np->n_isarr)
  {
   srtyp = __get_array_srep_type(np);
  }
 else if (np->srep == SR_BIT2S) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;

 is_2state = (srtyp == SR_BIT2S);

 res_apti = __gen_tn(srtyp, ndp->szu.xclen);
 /* AIV 09/10/08 - can have strength here */
 /* AIV 05/07/09 - can have IS param here as well - works fine */
 /* DBG remove -- */
 if (np->srep != SR_VEC && np->srep != SR_PNUM && np->srep != SR_ARRAY 
     && np->srep != SR_SVEC && np->srep != SR_PISNUM && np->srep != SR_BIT2S) 
   __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* will jump to done if out of range */
 done_bbp = __alloc_bblk(FALSE);
 /* AIV 05/31/09 - need to init wide case to 0 - only need to do this */
 /* for the wide case because movl's will init word case but not each */
 /* word of the wide psel */
 if (ndp->szu.xclen > WBITS)
  {
   if (is_2state)
    {
     bytsiz = wlen_(ndp->szu.xclen)*WRDBYTES;
    }
   else bytsiz = 2*wlen_(ndp->szu.xclen)*WRDBYTES;
   __emit_store_cint(res_apti, 0, bytsiz);
  }
 numbits_ti = get_indexed_psel_range(&rng1_ti, &rng2_ti, &ri2, res_apti, ndp,
  np, done_bbp, -1);
 
 if (np->srep == SR_SVEC)
  {
   sbp_ti = __var_adradd_insn(SR_SVEC, ndp->szu.xclen, addr_apti, rng2_ti);
   __emit_rhs_st_psel(res_apti, sbp_ti, numbits_ti);
  }
 else
  {
   gen_rhs_iw_psel(addr_apti, res_apti, rng2_ti, numbits_ti, np->nwid, 
     ndp->szu.xclen, srtyp);
  }

 __start_bblk(done_bbp);
 return(res_apti);
}

/*
 * generate code for index psels +: and -: 
 */
static void gen_rhs_iw_psel(int32 addr_apti, int32 res_apti, int32 bitl_ti,
 int32 numbits_ti, int32 nwid, int32 opwid, int32 srtyp)
{
 int32 t1_ti, t2_ti, mask_ti; 
 int32 res_bpti, addr_bpti;

 /* three cases to do the actual part select */
 /* case 1 - net width is narrow cannot exceed net width do simple narrow */
 /* case 2 - net width is wide and can have to access high parts base on var ndx */
 /* case 3 - net width is wide and so is its width - notice the width might */
 /* be trimmed to < WBITS at runtime */
 if (nwid <= WBITS)
  {
   /* av = (sav >> sbit1) & __masktab[numbits]; */
   /* bv = (sbv >> sbit1) & __masktab[numbits]; */
   t1_ti = __emit_shiftr(WBITS, bitl_ti, addr_apti);
   /* notice cannot get use constant numbits because may truncate at runtime */
   /*   mask_ti = __gen_cint_tn(__masktab[ri2]); */
   /* AIV 10/16/08 - now word aligned no reason to mult bytes any more */
   mask_ti = __move_insn(TN_VAL, I_MOVA, AM_NLO_ARRNDX, numbits_ti, 
    NLO_MASKTAB);

   t2_ti = __emit_mask_and(t1_ti, mask_ti);
   __emit_copy(WRDBYTES, t2_ti, res_apti);
   if (srtyp == SR_BIT2S) return;

   addr_bpti = __get_bpti(addr_apti);
   res_bpti = __get_bpti(res_apti);
   t1_ti = __emit_shiftr(WBITS, bitl_ti, addr_bpti);
   t2_ti = __emit_mask_and(t1_ti, mask_ti);
   __emit_copy(WRDBYTES, t2_ti, res_bpti);
  }
 else if (opwid > WBITS)
  {
   if (srtyp == SR_BIT2S)
    {
     __emit_rhs_psel_wide_2state(res_apti, addr_apti, bitl_ti, numbits_ti);
    }
   else
    {
     addr_bpti = __get_bpti(addr_apti);
     res_bpti = __get_bpti(res_apti);
     __emit_rhs_psel_wide(res_apti, res_bpti, addr_apti, addr_bpti, bitl_ti, 
       numbits_ti);
    }
  }
 else
  {
   if (srtyp == SR_BIT2S)
    {
     t1_ti = __emit_rhs_psel_2state(addr_apti, bitl_ti, numbits_ti);
     __emit_copy(WRDBYTES, t1_ti, res_apti);
    }
   else
    {
     /* does a and b part - a part is returned and b part is put in ECX */
     /* AIV BEWARE - b part returned in ECX */
     addr_bpti = __get_bpti(addr_apti);
     res_bpti = __get_bpti(res_apti);
     t1_ti = __emit_rhs_psel(addr_apti, addr_bpti, bitl_ti, numbits_ti);
     __emit_copy(WRDBYTES, t1_ti, res_apti);
     __emit_copy(WRDBYTES, AR_CX, res_bpti);
    }
  }
}
 
/*
 * get the index for the indexed width part select
 *
 * return the normalized range in r1_ti and r2_ti
 * returns numbits_ti
 * returns the constant width in ri2
 *
 * if the first index evals to x/s make rval_ti x
 * jump to done_bbp if x
 * otherwise compute indices
 *
 * if r1_ti is set there is no need to check if range is in range
 */
static int32 get_indexed_psel_range(int32 *r1_ti, int32 *r2_ti, word32 *ri2, 
 int32 rval_ti, struct expr_t *ndp, struct net_t *np, struct bblk_t *done_bbp,
 int32 ri1_ti)
{
 int32 ri2_ti, rng1_ti, rng2_ti, nri1_ti, nri2_ti, nri1, nri2; 
 int32 ri1_bpti, numbits_ti, t1_ti, one_ti, is_2state, cint_ti;
 struct expr_t *ndx1, *ndx2;
 struct bblk_t *trunc_one_bbp, *next_bbp, *trunc_two_bbp, *norm_bbp;
 struct bblk_t *outofrng_bbp, *some_rng_bbp, *inrng_bbp;
 struct bblk_t *op_bbp, *xz_bbp;

 /* check if b part is x/z if so value is x */
 if (ri1_ti == -1)
  {
   ndx1 = ndp->ru.x->lu.x;
   ri1_ti = __gen_expr_eval(ndx1, -1);
   
   is_2state = __tmp_is_2state(ri1_ti);
   if (!is_2state)
    {
     op_bbp = __alloc_bblk(FALSE);

     ri1_bpti = __get_bpti(ri1_ti);
     /* if rhs set the value to x otherwise don't write to if x/z */
     if (rval_ti != -1)
      {
       xz_bbp = __alloc_bblk(TRUE);
       __emit_jmp_0(op_bbp, xz_bbp, ri1_bpti);
       __start_bblk(xz_bbp);
  
       gen_ab_setx(rval_ti, FALSE);
       __emit_jmp(done_bbp);
      }
     else
      {
       __emit_jmp_0(op_bbp, done_bbp, ri1_bpti);
      }
     __start_bblk(op_bbp);
    }
  }

 if (__tntab[ri1_ti].tn_typ == TN_ADR) 
  {
   ri1_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, ri1_ti);
  }

 ndx2 = ndp->ru.x->ru.x;
 *ri2 = __contab[ndx2->ru.xvi];

 __getwir_range(np, &nri1, &nri2); 

 ri2_ti = __gen_cint_tn(*ri2-1);
 if (ndp->optyp == PARTSEL_NDX_PLUS)
  {
   if (nri1 > nri2)
    {
     /* r2 = ri1; r1 = ri1 + (ri2 - 1); */
     rng2_ti = ri1_ti;
     rng1_ti = __emit_add(WBITS, ri2_ti, ri1_ti);
    }
   else
    {
     /* r1 = ri1; r2 = ri1 + (ri2 - 1); */
     rng1_ti = ri1_ti;
     rng2_ti = __emit_add(WBITS, ri2_ti, ri1_ti);
    }
  }
 else 
  {
   if (nri1 > nri2)
    {
     /* r1 = ri1; r2 = ri1 - (ri2 - 1); */
     rng1_ti = ri1_ti;
     rng2_ti = __emit_sub(WBITS, ri1_ti, ri2_ti);
    }
   else
    {
     /* r2 = ri1; r1 = ri1 - (ri2 - 1); */
     rng2_ti = ri1_ti;
     rng1_ti = __emit_sub(WBITS, ri1_ti, ri2_ti);
    }
  }

 /* truncate out of range values and normalize for use in psel op */
 trunc_one_bbp = __alloc_bblk(FALSE);
 next_bbp = __alloc_bblk(FALSE);
 trunc_two_bbp = __alloc_bblk(FALSE);
 norm_bbp = __alloc_bblk(FALSE);
 nri1_ti = __gen_cint_tn(nri1);
 nri2_ti = __gen_cint_tn(nri2);
 outofrng_bbp = __alloc_bblk(FALSE);
 some_rng_bbp = __alloc_bblk(FALSE);
 if (nri1 >= nri2) 
  {
   /* completely out of range return 'bx */
   /* if (r2 > nri1) set to x return; */
   __emit_jmp_cmp(outofrng_bbp, some_rng_bbp, rng2_ti, nri1_ti, CC_JGT);
   __start_bblk(outofrng_bbp);
   if (rval_ti != -1) gen_ab_setx(rval_ti, FALSE);
   __emit_jmp(done_bbp);

   __start_bblk(some_rng_bbp);

   /* if (r1 > nri1) r1 = nri1; */
   __emit_jmp_cmp(trunc_one_bbp, next_bbp, rng1_ti, nri1_ti, CC_JGT);

   __start_bblk(trunc_one_bbp);
   __emit_copy(WRDBYTES, nri1_ti, rng1_ti);
   __emit_jmp(next_bbp);

   /* if (r2 < nri2) r2 = nri2; */
   __start_bblk(next_bbp);
   __emit_jmp_cmp(trunc_two_bbp, norm_bbp, rng2_ti, nri2_ti, CC_JLT);

   __start_bblk(trunc_two_bbp);
   __emit_copy(WRDBYTES, nri2_ti, rng2_ti);
   __emit_jmp(norm_bbp);

   __start_bblk(norm_bbp);
   /* if (r1 < nri2) return(np); */
   if (ndp->optyp == PARTSEL_NDX_PLUS)
    {
     cint_ti = __gen_cint_tn(nri2);
     inrng_bbp = __alloc_bblk(FALSE);
     __emit_jmp_cmp(outofrng_bbp, inrng_bbp, rng1_ti, cint_ti, CC_JLT);
     __start_bblk(inrng_bbp);
    }

   /* r1 = r1 - nri2; */
   rng1_ti = __emit_sub(WBITS, rng1_ti, nri2_ti);
   /* r2 = r2 - nri2; */
   rng2_ti = __emit_sub(WBITS, rng2_ti, nri2_ti);
   /* AIV 08/16/10 - can be out of range here as well */
  }
 else
  {
   /* completely out of range return 'bx */
   /* if (r1 > nri2) set to x; */
   __emit_jmp_cmp(outofrng_bbp, some_rng_bbp, rng1_ti, nri2_ti, CC_JGT);
   __start_bblk(outofrng_bbp);
   if (rval_ti != -1) gen_ab_setx(rval_ti, FALSE);
   __emit_jmp(done_bbp);

   __start_bblk(some_rng_bbp);
   /* if (r2 > nri2) r2 = nri2; */
   __emit_jmp_cmp(trunc_one_bbp, next_bbp, rng2_ti, nri2_ti, CC_JGT);
   __start_bblk(trunc_one_bbp);
   __emit_copy(WRDBYTES, nri2_ti, rng2_ti);
   __emit_jmp(next_bbp);

   /* if (r1 < nri1) r1 = nri1; */
   __start_bblk(next_bbp);
   __emit_jmp_cmp(trunc_two_bbp, norm_bbp, rng1_ti, nri1_ti, CC_JLT);
   __start_bblk(trunc_two_bbp);
   __emit_copy(WRDBYTES, nri1_ti, rng1_ti);
   __emit_jmp(norm_bbp);

   __start_bblk(norm_bbp);
   /* r1 = nri2 - r1; */
   rng1_ti = __emit_sub(WBITS, nri2_ti, rng1_ti);
   /* r2 = nri2 - r2; */
   rng2_ti = __emit_sub(WBITS, nri2_ti, rng2_ti);
  }
 *r1_ti = rng1_ti;
 *r2_ti = rng2_ti;

 /* numbits = rng1 - rng2 + 1; */
 t1_ti = __emit_sub(WBITS, rng1_ti, rng2_ti);
 one_ti = __gen_cint_tn(1);
 numbits_ti = __emit_add(WBITS, one_ti, t1_ti);
 return(numbits_ti);
}

/*
 * generate decomposed rhs part select when all in one word
 *
 * SJM 05/22/05 - for part select the offset and number of bits constant
 */
static int32 gen_in1wrd_rhs_psel(int32 srtyp, int32 var_apti, int32 lowbiti, 
 int32 numbits)
{
 int32 res_apti, wofs, wadr_apti, bofs, var_bpti, blen;
 int32 t1_apti, t1_bpti, b_ofs;

 /* AIV - 11/17/05 - if any strength just return + num bytes */
 if (__any_stren_tn(var_apti))
  {
   res_apti = __con_adradd_insn(SR_SVEC, numbits, var_apti, lowbiti);
   return(res_apti);
  }

 t1_bpti = -1;
 var_bpti = -1;
 /* case 1 - select within 1st word32 */
 if (lowbiti + numbits <= WBITS)
  {

   /* SJM 04/06/07 - must select out of WBITS object although low wrd of wid */
   if (__get_tnwid(var_apti) > WBITS)
    {
     t1_apti = __gen_tn(srtyp, WBITS);
     __emit_copy(WRDBYTES, var_apti, t1_apti);
     if (srtyp != SR_BIT2S)
      {
       t1_bpti = __get_bpti(t1_apti);
       var_bpti = __get_bpti(var_apti);
       __emit_copy(WRDBYTES, var_bpti, t1_bpti);
      }
     res_apti = gen_onewrd_bound_rhs_psel(srtyp, t1_apti, t1_bpti, lowbiti, 
       numbits);
    }
   else
    {
     if (srtyp != SR_BIT2S)
      {
       var_bpti = __get_bpti(var_apti);
      }
     else var_bpti = -1;
     res_apti = gen_onewrd_bound_rhs_psel(srtyp, var_apti, var_bpti, lowbiti, 
       numbits);
    }
   return(res_apti);
  }

 bofs = get_bofs_(lowbiti);
 /* case 2 - selection does not cross word32 boundary */
 if (bofs + numbits <= WBITS)
  {
   wofs = get_wofs_(lowbiti);
   /* SJM 08/16/05 - for wide also need the bit ofset */
   /* word ofset can't be 0 for this case - or not in 1 word */
   /* DBG remove -- */
   if (wofs == 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   blen = __get_tnwid(var_apti);
   wadr_apti = __con_adradd_insn(srtyp, WBITS, var_apti, WRDBYTES*wofs);
   /* do one add to get the b part word + offset word */
   if (srtyp != SR_BIT2S)
    {
     b_ofs = (wlen_(blen) + wofs)*WRDBYTES;
     var_bpti = __con_adradd_insn(srtyp, WBITS, var_apti, b_ofs);
    }
   else var_bpti = -1;

   /* SJM 04/06/07 - notice select here out of 1 word not wide low wrd tn */
   res_apti = gen_onewrd_bound_rhs_psel(srtyp, wadr_apti, var_bpti, bofs, 
    numbits);
  }
 /* case 3a - selection crosses word32 boundary but start on word32 boundary */
 else if (bofs == 0) 
  { 
   res_apti = __gen_tn(srtyp, numbits);
   gen_wordalign_rhs_psel(srtyp, res_apti, var_apti, lowbiti, numbits);
  }
 /* case 3a - crosses 1 word32 boundary and <= WBITS */
 else
  {
   res_apti = gen_onewrd_cross_rhs_psel(srtyp, var_apti, lowbiti, numbits);
  }
 return(res_apti);
}

/*
 * generate decomposed rhs part select when all in FIRST word
 *  from v_ex2.c:
 *  if (corsbit1 == 0) *dwp = *swp & __masktab[numbits];
 *  else *dwp = (*swp >> corsbit1) & __masktab[numbits];
 */
static int32 gen_onewrd_bound_rhs_psel(int32 srtyp, int32 var_apti, 
 int32 var_bpti, int32 lowbiti, int32 numbits)
{
 int32 res_apti, res_bpti, cint_ti, mask_ti;
 int32 t1_ti, t1_apti, t1_bpti, t2_ti, ofs;
 
 /* if psel is aligned on word boundary just copy a/b word - no need to mask */
 if (ubits_(lowbiti) == 0 && numbits == WBITS)
  {
   res_apti = __gen_tn(srtyp, WBITS);
   __emit_copy(WRDBYTES, var_apti, res_apti);
   if (srtyp != SR_BIT2S)
    {
     res_bpti = __get_bpti(res_apti);
     __emit_copy(WRDBYTES, var_bpti, res_bpti);
    }
   return(res_apti);
  }

 cint_ti = __gen_cint_tn(__masktab[numbits]);

 /* AIV 10/27/09 - if aligned on byte can just make this a simple movzbl */
 /* to move and zero into a reg */
 /* only do if it is a memory offset off idp reg memory area */
 if (numbits == 8 && ((lowbiti % 8) == 0) 
     && (__tntab[var_apti].comlab_typ == COMLAB_IDP || 
         __tntab[var_apti].comlab_typ == COMLAB_NETADR))
  {
   res_apti = __gen_tn(srtyp, numbits);
   ofs = lowbiti/8;

   if (ofs == 0)
    {
     t1_apti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, var_apti);
     __emit_copy(WRDBYTES, t1_apti, res_apti);

     if (srtyp != SR_BIT2S)
      {
       res_bpti = __get_bpti(res_apti);
       t1_bpti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG, var_bpti);
       __emit_copy(WRDBYTES, t1_bpti, res_bpti);
      }
    }
   else
    {
     t1_apti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG_DISP, var_apti, ofs);
     __emit_copy(WRDBYTES, t1_apti, res_apti);

     if (srtyp != SR_BIT2S)
      {
       res_bpti = __get_bpti(res_apti);
       t1_bpti = __move_insn(TN_VAL, I_MOVZBL, AM_NDXREG_DISP, var_bpti, ofs);
       __emit_copy(WRDBYTES, t1_bpti, res_bpti);
      }
    }
   return(res_apti);
  }

 if (lowbiti == 0) 
  {
   /* AIV 08/19/08 - result size is numbits not WBITS - doing too many */
   /* conversions to match the size */
   res_apti = __gen_tn(srtyp, numbits);
   t1_apti = __emit_mask_and(var_apti, cint_ti);
   __emit_copy(WRDBYTES, t1_apti, res_apti);
   if (srtyp != SR_BIT2S)
    {
     t1_bpti = __emit_mask_and(var_bpti, cint_ti);
     res_bpti = __get_bpti(res_apti);
     __emit_copy(WRDBYTES, t1_bpti, res_bpti);
    }
  }
 else
  {
   /* AIV 01/25/06 - result size is numbits not WBITS */
   res_apti = __gen_tn(srtyp, numbits);
   cint_ti = __gen_cint_tn(lowbiti);
   t1_ti = __emit_shiftr(WBITS, cint_ti, var_apti);
   mask_ti = __gen_cint_tn(__masktab[numbits]);
   t1_apti = __emit_mask_and(t1_ti, mask_ti);
   __emit_copy(WRDBYTES, t1_apti, res_apti);

   if (srtyp != SR_BIT2S)
    {
     t2_ti = __emit_shiftr(WBITS, cint_ti, var_bpti);
     t1_bpti = __emit_mask_and(t2_ti, mask_ti);
     res_bpti = __get_bpti(res_apti);
     __emit_copy(WRDBYTES, t1_bpti, res_bpti);
    }
  }
 return(res_apti);
}

/*
 * generate decomposed rhs part select when all in FIRST word
 * this is across word32 boundary
 * from v_ex2.c:
 *  *dwp = (swp[0] >> corsbit1);
 *  *dwp |= swp[1] << (WBITS - corsbit1);
 *  *dwp &= __masktab[numbits];
 */
static int32 gen_onewrd_cross_rhs_psel(int32 srtyp, int32 var_apti, 
 int32 lowbiti, int32 numbits)
{
 int32 bofs, wofs, blen, mask_ti, mask2_ti, ofs;
 int32 word_0_apti, word_1_apti, word_0_bpti, word_1_bpti; 
 int32 res_apti, res_bpti, t1_ti, t2_ti, t3_ti, cint_ti, r1_ti, r2_ti, r3_ti;
 word32 mask;

 wofs = get_wofs_(lowbiti);
 bofs = get_bofs_(lowbiti);

 word_0_apti =  word_1_apti = -1;
 word_0_bpti = word_1_bpti = -1; 

 /* AIV 11/10/09 - this should be numbits WBITS */
 res_apti = __gen_tn(srtyp, numbits); 

 blen = __get_tnwid(var_apti);
 /* SJM 11/15/06 - if wofs 0 - do not need the addr add */
 if (wofs != 0) 
  {
   word_0_apti = __con_adradd_insn(srtyp, WBITS, var_apti, WRDBYTES*wofs);
  }
 else word_0_apti = var_apti;

 ofs = WRDBYTES*wofs + WRDBYTES;
 word_1_apti = __con_adradd_insn(srtyp, WBITS, var_apti, ofs);

 /* get the first and second word of the b part */
 if (srtyp != SR_BIT2S) 
  {
   ofs =  (wlen_(blen) + wofs)*WRDBYTES;
   word_0_bpti = __con_adradd_insn(srtyp, WBITS, var_apti, ofs);

   ofs = (wlen_(blen) + wofs)*WRDBYTES +WRDBYTES;
   word_1_bpti = __con_adradd_insn(srtyp, WBITS, var_apti, ofs);
  }

 cint_ti = __gen_cint_tn(bofs);
 t1_ti = __emit_shiftr(WBITS, cint_ti, word_0_apti);

 mask = WBITS - bofs;
 mask_ti = __gen_cint_tn(mask);
 t2_ti = __emit_shiftl(WBITS, mask_ti, word_1_apti);
 r3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);

 mask2_ti = __gen_cint_tn(__masktab[numbits]);
 r1_ti = __emit_mask_and(r3_ti, mask2_ti);
 __emit_copy(WRDBYTES, r1_ti, res_apti);

 if (srtyp == SR_BIT2S) return(res_apti);

 /* now do the same thing with the b part */
 cint_ti = __gen_cint_tn(bofs);
 t1_ti = __emit_shiftr(WBITS, cint_ti, word_0_bpti);
 t2_ti = __emit_shiftl(WBITS, mask_ti, word_1_bpti);
 t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
 r2_ti = __emit_mask_and(t3_ti, mask2_ti);

 res_bpti = __get_bpti(res_apti);
 __emit_copy(WRDBYTES, r2_ti, res_bpti);
 return(res_apti);
}

/*
 * rhs psel aligned on a word32 boundary  
 * select from lowbi (aligned on a word) numbits from var apti into res apti
 *
 * generates code for interpreter cp_walign_
 */
static void gen_wordalign_rhs_psel(int32 srtyp, int32 res_apti, int32 var_apti, 
 int32 lowbiti, int32 numbits)
{
 int32 ubits, wofs, pselfromwid, ofs, mask_ti;
 int32 word_apti, word_bpti, res_bpti, r1_ti, r2_ti, hghw_apti, hghw_bpti; 
 word32 mask;

 wofs = get_wofs_(lowbiti);
 ubits = ubits_(numbits);
 mask = __masktab[ubits];

 /* get ptr to word aligned psel from start addr */ 
 /* SJM 11/15/06 - if wofs 0 - do not need the addr add */
 if (wofs != 0)
  {
   word_apti = __con_adradd_insn(srtyp, numbits, var_apti, WRDBYTES*wofs);
  }
 else word_apti = var_apti;

 /* SJM 09/25/06 - need to set mask ti to satisfy lint */
 mask_ti = 0;
 /* since word aligned on both sides copy the main a part */
 __emit_copy(wlen_(numbits)*WRDBYTES, word_apti, res_apti);
 if (ubits != 0)
  {
   ofs =  WRDBYTES*(wlen_(numbits) - 1);
   hghw_apti = __con_adradd_insn(srtyp, WBITS, res_apti, ofs);
   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);
  }

 if (srtyp == SR_BIT2S) return;

 /* get start of psel b part word */ 
 pselfromwid = wlen_(__get_tnwid(var_apti));
 ofs = WRDBYTES*(pselfromwid + wofs);
 /* b part is from-var addr plus from-var wide plus start word offset */
 word_bpti = __con_adradd_insn(srtyp, WBITS, var_apti, ofs);

 ofs =  WRDBYTES*wlen_(numbits);
 res_bpti = __con_adradd_insn(srtyp, WBITS, res_apti, ofs);
 __emit_copy(wlen_(numbits)*WRDBYTES, word_bpti, res_bpti);

 /* need to mask high words, if not all bits in high word part of rhs psel */
 if (ubits != 0)
  {
   ofs = (2*wlen_(numbits) - 1)*WRDBYTES;
   hghw_bpti = __con_adradd_insn(srtyp, WBITS, res_apti, ofs);
   r2_ti = __emit_mask_and(hghw_bpti, mask_ti);
   __emit_copy(WRDBYTES, r2_ti, hghw_bpti);
  }
}

/*
 * store psel aligned word - aligned on both sides
 *
 * AIV 07/20/06 - the lower lhs is aligned but the high isn't always so may
 * need the mask of the high bits
 */
static void gen_wordalign_st_psel(int32 srtyp, int32 addr_apti, 
 int32 rhs_apti, int32 lowbiti, int32 numbits)
{
 int32 bofs, wofs, twid, nbytes, hghw_apti, hghw_bpti, ofs;
 int32 wi_adr_apti, wi_adr_bpti, rhs_bpti, r1_ti, mask_ti;
 word32 mask;

 wofs = get_wofs_(lowbiti);
 bofs = get_bofs_(numbits);
 mask = __masktab[bofs];
 mask_ti = __gen_cint_tn(mask);

 /* SJM 11/15/06 - if wofs 0 - do not need the addr add */
 if (wofs != 0)
  {
   wi_adr_apti = __con_adradd_insn(srtyp, numbits, addr_apti, 
    WRDBYTES*wofs);
  }
 else wi_adr_apti = addr_apti;

 __emit_copy(wlen_(numbits)*WRDBYTES, rhs_apti, wi_adr_apti);

 if (bofs != 0)
  {
   ofs =  WRDBYTES*(wlen_(numbits) - 1);
   hghw_apti = __con_adradd_insn(srtyp, WBITS, wi_adr_apti, ofs);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);
  }

 /* if 2state skip the bpart */
 if (srtyp == SR_BIT2S) return;

 twid = __get_tnwid(addr_apti); 
 nbytes = (wlen_(twid)+wofs)*WRDBYTES;
 wi_adr_bpti = __con_adradd_insn(srtyp, numbits, addr_apti, nbytes);
 rhs_bpti = __get_bpti(rhs_apti);
 __emit_copy(wlen_(numbits)*WRDBYTES, rhs_bpti, wi_adr_bpti);

 if (bofs != 0)
  {
   ofs = WRDBYTES*(wlen_(twid) + wlen_(numbits) - 1);
   hghw_bpti = __con_adradd_insn(srtyp, WBITS, wi_adr_apti, ofs);
   r1_ti = __emit_mask_and(hghw_bpti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_bpti);
  }
}

/*
 * gen from right itree context addr rhs psel
 *
 * for rhs part selects where may not be net - but know h:l
 * emit 2 psel insns and then copy 2nd to b part
 *
 * so psel creates as a/b sr vec form
 * know addr is right itree context entire area (maybe not var)
 */
extern int32 __gen_fradr_rhs_psel(int32 srtyp, int32 addr_apti, 
 int32 nwid, int32 i1, int32 i2)  
{
 int32 pselwid, t1_apti, sbp_ti, bofs;

 /* case 1: from stren svec */
 pselwid = i1 - i2 + 1;
 if (__any_stren_tn(addr_apti))
  {
   pselwid = i1 - i2 + 1;
   sbp_ti = __con_adradd_insn(SR_SVEC, pselwid, addr_apti, i2);
   return(sbp_ti);
  }

 /* part select fits in one word */
 if (nwid <= WBITS) 
  {
   t1_apti = gen_in1wrd_rhs_psel(srtyp, addr_apti, i2, nwid);
   return(t1_apti); 
  }

 /* selection crosses word32 boundary but start on word32 boundary */
 bofs = get_bofs_(i2);
 if (bofs == 0)
  {
   t1_apti = __gen_tn(srtyp, nwid);
   gen_wordalign_rhs_psel(srtyp, t1_apti, addr_apti, i2, nwid);
   return(t1_apti);
  }

 /* unaligned across words case */
 /* AIV 11/17/05 -  notice now passing i2 that is not word offset */
 /* case 2: from a/b vec */
 if (srtyp == SR_BIT2S)
  {
   t1_apti = __gen_tn(SR_BIT2S, nwid);
   gen_ld_unaligned_rhs_psel(t1_apti, addr_apti, i2, pselwid, TRUE, SR_BIT2S); 
   return(t1_apti);
  }

 t1_apti = __gen_tn(SR_VEC, nwid);
 /* load the unaligned a and b part psel into t1_apti */ 
 gen_ld_unaligned_rhs_psel(t1_apti, addr_apti, i2, pselwid, TRUE, SR_VEC); 
 gen_ld_unaligned_rhs_psel(t1_apti, addr_apti, i2, pselwid, FALSE, SR_VEC); 
 return(t1_apti);
} 

/*
 * load an unaligned wide psel into val_ti
 * mimics __cp_sofs_wval in v_ex3.c
 */
static void gen_ld_unaligned_rhs_psel(int32 val_ti, int32 addr_apti, 
 int32 lowbi, int32 numbits, int32 is_apart, int32 srtyp)
{
 int32 dst_ti, src_ti, bofs, cint2_ti, cint3_ti, cint4_ti, ofs;
 int32 word_ndx, dst_ndx, wi, twid, dstwid, sbit1, sbit2, bi, r1_ti, r2_ti;

 twid = __get_tnwid(addr_apti);
 wi = get_wofs_(lowbi);
 sbit1 = get_bofs_(lowbi);
 
 /* don't use this routine if aligned on word boundary */
 /* DBG ---- */
 if (sbit1 == 0) __misc_terr(__FILE__, __LINE__); 
 /* ----- */

 /* if a part start at word offset for low bit */
 /* if b part start at word offset plus the a part word length */
 if (is_apart) word_ndx = wi; else word_ndx = (wi+wlen_(twid));

 /* if psel wider than ten words just do the wrapper */ 
 if (wlen_(numbits) > 10)
  {
   src_ti = __con_adradd_insn(srtyp, WBITS, addr_apti, word_ndx*WRDBYTES);
   if (!is_apart) val_ti = __get_bpti(val_ti);
   __emit_ld_psel(src_ti, sbit1, numbits, val_ti); 
  }
 else
  {
   sbit2 = WBITS - sbit1;
   dstwid = __get_tnwid(val_ti);
   /* start at the right index for the destination word offset */ 
   if (is_apart) dst_ndx = 0; else dst_ndx = wlen_(dstwid);

   for (bi = 0; ; word_ndx++, dst_ndx++)
    {
     /* dwp[wi] = (swp[wi] >> sbit1); */
     src_ti = __con_adradd_insn(srtyp, WBITS, addr_apti, word_ndx*WRDBYTES);
     dst_ti = __con_adradd_insn(srtyp, WBITS, val_ti, dst_ndx*WRDBYTES);
     cint3_ti = __gen_cint_tn(sbit1);
     r1_ti = __emit_shiftr(WBITS, cint3_ti, src_ti);
     __emit_copy(WRDBYTES, r1_ti, dst_ti);

     if ((bi += sbit2) >= numbits) break;
     /* dwp[wi] |= (swp[wi + 1] << sbit2); */

     ofs = (word_ndx + 1)*WRDBYTES;
     src_ti = __con_adradd_insn(srtyp, WBITS, addr_apti, ofs);
     cint2_ti = __gen_cint_tn(sbit2);
     r1_ti = __emit_shiftl(WBITS, cint2_ti, src_ti);
     /* since dest word new part already cleared to 0, this ors in rest */
     r2_ti = __emit_mask_or(dst_ti, r1_ti);
     __emit_copy(WRDBYTES, r2_ti, dst_ti);

     if ((bi += sbit1) >= numbits) break;
    }
   /* mask the high bits of the high word if needed */
   bofs = ubits_(numbits);
   if (bofs != 0)
    {
     cint4_ti = __gen_cint_tn(__masktab[bofs]);
     r2_ti = __emit_mask_and(dst_ti, cint4_ti);
     __emit_copy(WRDBYTES, r2_ti, dst_ti);
    }
  }
}

/*
 * generate code for store psel from rhs_apti into addr_apti
 * does both the a and b part
 */
extern void __gen_st_psel(int32 srtyp, int32 addr_apti, int32 rhs_apti, 
 int32 lowbi, int32 numbits)
{
 int32 dbi, rhs_bpti, rhs_sbp_ti, addr_sbp_ti;

 /* if strength to strength just copy bytes */
 if (__any_stren_tn(addr_apti))
  {
   rhs_sbp_ti = __con_adradd_insn(SR_SVEC, numbits, rhs_apti, numbits);
   addr_sbp_ti = __con_adradd_insn(SR_SVEC, numbits, addr_apti, numbits);
   __emit_copy(numbits, rhs_sbp_ti, addr_sbp_ti);
   return;
  }
 /* if rhs strength and stored into isn't must convert to non-stren vec */
 else if (__any_stren_tn(rhs_apti))
  {
   /* AIV 01/23/06 - number of bits passed was wrong not WBITS */
   rhs_apti = __gen_cnvt_srep_ifneeded(rhs_apti, srtyp, numbits, FALSE, 
    FALSE, FALSE);
  }

 /* fits into one word store psel case*/
 if (numbits <= WBITS)
  {
   gen_in1wrd_st_psel(srtyp, addr_apti, rhs_apti, lowbi, numbits, TRUE);
   if (srtyp == SR_BIT2S) return;
   rhs_bpti = __get_bpti(rhs_apti);
   gen_in1wrd_st_psel(srtyp, addr_apti, rhs_bpti, lowbi, numbits, FALSE);
   return;
  }
 else
  {
   dbi = get_bofs_(lowbi);
   /* bit aligned on word boundary */
   if (dbi == 0)
    {
     if (ubits_(numbits) == 0)
      {
       /* note this loads the psel for both a and b part */
       gen_wordalign_st_psel(srtyp, addr_apti, rhs_apti, lowbi, numbits);
      }
     else
      {
       /* high word must be masked */
       gen_wordalign_hwmask_st_psel(srtyp, addr_apti, rhs_apti, lowbi, numbits);
      }
    }
   /* not aligned case */
   else
    {
     /* do both a and b part will figure out offsets from passed flag */
     gen_ld_unaligned_st_psel(srtyp, addr_apti, rhs_apti, lowbi, numbits, TRUE); 
     if (srtyp == SR_BIT2S) return;
     gen_ld_unaligned_st_psel(srtyp, addr_apti, rhs_apti, lowbi, numbits, 
      FALSE); 
    }
  }
}

/*
 * psel lowbi starts on word boundary but doesn't end so need to mask
 * the high word 
 * code from v_ex3.c
 *    wlen = wlen_(numbits);
 *    save_val = dwp[wlen - 1] & ~__masktab[ubits];
 *    cp_walign_(dwp, swp, numbits);
 *    dwp[wlen - 1] |= save_val;
 */
static void gen_wordalign_hwmask_st_psel(int32 srtyp, int32 addr_apti, 
 int32 rhs_apti, int32 lowbi, int32 numbits)
{
 int32 twid, wi, ubits, mask_ti, ofs; 
 int32 sav_hwadr_apti, sav_hw_apti, sav_hwadr_bpti, sav_hw_bpti;
 int32 r1_ti, r2_ti;
 word32 mask;

 sav_hwadr_bpti = sav_hw_bpti = -1;
 twid = __get_tnwid(addr_apti);
 /* AIV 01/23/06 - needed to add wlen of lowbi */
 wi = wlen_(lowbi) + wlen_(numbits);
 /* save the a part high word */
 ofs = WRDBYTES*(wi - 1);
 sav_hwadr_apti = __con_adradd_insn(srtyp, WBITS, addr_apti, ofs);
 /* SJM 07/18/09 - was generating an unneeded tn here */
 
 /* mask the high word */
 ubits = ubits_(numbits);
 mask = ~(__masktab[ubits]);
 mask_ti = __gen_cint_tn(mask);
 sav_hw_apti = __emit_mask_and(sav_hwadr_apti, mask_ti);
 
 /* save the b part high word */
 /* if 2state do not save/restore b-part */
 if (srtyp != SR_BIT2S) 
  {
   wi = wlen_(lowbi) + wlen_(twid) + wlen_(numbits);
   ofs = WRDBYTES*(wi - 1);
   sav_hwadr_bpti = __con_adradd_insn(SR_VEC, WBITS, addr_apti, ofs);
   /* SJM 07/18/09 - was generating an unneeded tn here */
   sav_hw_bpti = __emit_mask_and(sav_hwadr_bpti, mask_ti);
  }

 /* do a word aligned on both end psel store */
 /* note this loads the psel for both a and b part */
 gen_wordalign_st_psel(srtyp, addr_apti, rhs_apti, lowbi, numbits);

 /* or the high words back in - know high bit areas will be zero */
 r1_ti = __emit_mask_or(sav_hwadr_apti, sav_hw_apti);
 __emit_copy(WRDBYTES, r1_ti, sav_hwadr_apti);
 /* if 2state do not save/restore b-part */
 if (srtyp != SR_BIT2S) 
  {
   r2_ti = __emit_mask_or(sav_hwadr_bpti, sav_hw_bpti);
   __emit_copy(WRDBYTES, r2_ti, sav_hwadr_bpti);
  }
}

/*
 * store a psel where the psel fits into one word
 */
static void gen_in1wrd_st_psel(int32 srtyp, int32 addr_ti, int32 rhs_ti, 
 int32 dbi, int32 numbits, int32 is_apart)
{
 int32 w2bits, wi, twid, cint_ti, mask_ti, cint2_ti, ofs;
 int32 wadr_ti, t1_ti, t2_ti, t3_ti, wadr_1_ti;
 int32 r1_ti, r2_ti, r3_ti;
 word32 mask;

 wi = get_wofs_(dbi);
 dbi = get_bofs_(dbi);
 /* determine the offset index */
 if (!is_apart) 
  {
   twid = __get_tnwid(addr_ti);
   wi += wlen_(twid);
  }
 if (wi != 0)
  {
   wadr_ti = __con_adradd_insn(srtyp, WBITS, addr_ti, WRDBYTES*wi);
  }
 else wadr_ti = addr_ti;

 /* case 1 : aligned on 32 bit boundary */
 if (dbi == 0)
  {
   /*
    * *dwp &= ~__masktab[numbits];
    * *dwp |= (*swp & __masktab[numbits]);
    */
   mask = __masktab[numbits];
   /* if alinged on 0 and wbits just copy the entire word */
   if (numbits == WBITS)
    {
     __emit_copy(WRDBYTES, rhs_ti, wadr_ti);
    }
   else
    {
     /* zero the destination in word area in prep to stick in new value */
     cint_ti = __gen_cint_tn(~(mask));
     r1_ti = __emit_mask_and(wadr_ti, cint_ti);

     /* SJM 07/19/06 - this is a narrowing size change - why needed */
     cint2_ti = __gen_cint_tn(mask);
     r2_ti = __emit_mask_and(rhs_ti, cint2_ti);

     /* build the new entire word to be stored into lhs psel dest */
     r3_ti = __emit_mask_or(r2_ti, r1_ti);
     __emit_copy(WRDBYTES, r3_ti, wadr_ti);
    }
  }
 /* case 2 : not aligned but psel from one word */
 else if (dbi + numbits <= WBITS)
  {
   /*
    * mask = __masktab[numbits] << dbi;
    * *dwp = (*dwp & ~mask) | ((*swp << dbi) & mask);
    */
   mask = __masktab[numbits] << dbi;
   cint_ti = __gen_cint_tn(~(mask));
   t1_ti = __emit_mask_and(wadr_ti, cint_ti);

   cint_ti = __gen_cint_tn(dbi);
   t2_ti = __emit_shiftl(WBITS, cint_ti, rhs_ti);
   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(t2_ti, mask_ti);
   t3_ti = __emit_bin_bitor(WBITS, r1_ti, t1_ti);
   __emit_copy(WRDBYTES, t3_ti, wadr_ti);
  }
 /* case 3 - less than 32 bits but crosses word32 boundary */
 else
  {
  /*
   * *dwp = (*dwp & __masktab[dbi]);
   * *dwp |= (*swp << dbi);
   */
   mask = __masktab[dbi];
   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(wadr_ti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, wadr_ti);  
   cint_ti = __gen_cint_tn(dbi);
   t1_ti = __emit_shiftl(WBITS, cint_ti, rhs_ti);
   r2_ti = __emit_mask_or(wadr_ti , t1_ti);
   __emit_copy(WRDBYTES, r2_ti, wadr_ti);  

  /*
   * dwp[1] = (dwp[1] & ~__masktab[w2bits])
   * | ((*swp >> (WBITS - dbi)) & __masktab[w2bits]);
   */
   w2bits = numbits - (WBITS - dbi);
   mask = __masktab[w2bits];

   ofs = WRDBYTES*(wi + 1);
   wadr_1_ti = __con_adradd_insn(srtyp, WBITS, addr_ti, ofs);
   cint_ti = __gen_cint_tn(~(mask));
   t1_ti = __emit_mask_and(wadr_1_ti, cint_ti);
   cint_ti = __gen_cint_tn(WBITS - dbi);
   t2_ti = __emit_shiftr(WBITS, cint_ti, rhs_ti);
   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(t2_ti, mask_ti);
   t3_ti = __emit_bin_bitor(WBITS, t1_ti, r1_ti);
   __emit_copy(WRDBYTES, t3_ti, wadr_1_ti);
  }
}

/*
 * store multiword unaligned psel from val_ti into addr_apti 
 */
static void gen_ld_unaligned_st_psel(int32 srtyp, int32 addr_apti, 
 int32 val_ti, int32 lowbi, int32 numbits, int32 is_apart)
{
 int32 dst_ti, src_ti, t1_ti, bofs, mask_ti, numbits_ti, lowbi_ti;
 int32 cint_ti, cint_ti2, cint_ti3, r1_ti, r2_ti;
 int32 word_ndx, dst_ndx, wi, twid, dbit1, dbit2, bi, sbit1, sbit2;
 int32 dst_0_ti, val_bpti, addr_bpti, val_adr_ti, ofs;
 int32 sav_hwadr_ti, sav_hw_ti, w2bits, high_wlen, n_numbits;
 word32 mask;

 twid = __get_tnwid(addr_apti);
 wi = get_wofs_(lowbi);
 dbit1 = get_bofs_(lowbi);
 
 /* don't use this routine if aligned on word boundary */
 /* DBG ---- */
 if (dbit1 == 0) __misc_terr(__FILE__, __LINE__); 
 /* ----- */

 if (wlen_(numbits) > 10)
  {
   numbits_ti = __gen_cint_tn(numbits);
   lowbi_ti = __gen_cint_tn(lowbi);
   if (is_apart)
    {
     __emit_st_psel(addr_apti, val_ti, lowbi_ti, numbits_ti);
    }
   else
    {
     addr_bpti = __get_bpti(addr_apti);
     val_bpti = __get_bpti(val_ti);
     __emit_st_psel(addr_bpti, val_bpti, lowbi_ti, numbits_ti);
    }
  }
 else
  {
   /*
    * w2bits = numbits + dbi;
    * wlen = wlen_(w2bits);
    * save_val = dwp[wlen - 1] & ~__masktab[ubits_(w2bits)];
    * cp_dofs_wval(dwp, swp, dbi, numbits);
    * dwp[wlen - 1] |= save_val;
    */
   w2bits = numbits + ubits_(lowbi);
   if (is_apart)
    {
     dst_ndx = wi;
     word_ndx = 0;
     high_wlen = wi + wlen_(w2bits);
    }
   else 
    {
     dst_ndx = (wi+wlen_(twid));
     word_ndx = wlen_(numbits);
     high_wlen = wi + wlen_(w2bits) + wlen_(twid);
    }

   /* get the high word to save */
   ofs = (high_wlen - 1)*WRDBYTES;
   sav_hwadr_ti = __con_adradd_insn(srtyp, WBITS, addr_apti, ofs);

   /* copy the high word */
   sav_hw_ti = __gen_tn(srtyp, WBITS);
   __emit_copy(WRDBYTES, sav_hwadr_ti, sav_hw_ti);
     
   /* mask the high word */
   mask_ti = __gen_cint_tn(~(__masktab[ubits_(w2bits)]));
   r1_ti = __emit_mask_and(sav_hw_ti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, sav_hw_ti);

   /*
    * dwp[0] &= __masktab[dbit1];
    * dwp[0] |= (swp[0] << dbit1);
    * dbit2 = WBITS - dbit1;
    * if (dbit2 >= numbits) return;
    * numbits -= dbit2;
    */
   mask = __masktab[dbit1];
   dst_0_ti = __con_adradd_insn(srtyp, WBITS, addr_apti, dst_ndx*WRDBYTES);
   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(dst_0_ti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, dst_0_ti);

   if (word_ndx != 0)
    {
     val_adr_ti = __con_adradd_insn(srtyp, WBITS, val_ti,
      (word_ndx*WRDBYTES));
    }
   else
    {
     /* if val ti tmp name wide, need copy - machine insns can't have wide op */
     if (__tntab[val_ti].tnwid > WBITS)
      {
       val_adr_ti = __gen_tn(srtyp, WBITS);
       /* intermediate level copy if from src to dst */
       __emit_copy(WRDBYTES, val_ti, val_adr_ti);
      }
     else val_adr_ti = val_ti;
    }

   cint_ti = __gen_cint_tn(dbit1);
   t1_ti = __emit_shiftl(WBITS, cint_ti, val_adr_ti);
   r1_ti = __emit_mask_or(dst_0_ti, t1_ti);
   __emit_copy(WRDBYTES, r1_ti, dst_0_ti);

   dbit2 = WBITS - dbit1;
   if (dbit2 >= numbits) return;

   n_numbits = numbits - dbit2;
   /* inc destination index  &(dwp[1]) */
   dst_ndx++;
   sbit1 = dbit2;
   sbit2 = WBITS - sbit1;
   for (bi = 0; ; word_ndx++, dst_ndx++)
    {
     /* dwp[wi] = (swp[wi] >> sbit1); */
     cint_ti = __gen_cint_tn(word_ndx*WRDBYTES);
     src_ti = __con_adradd_insn(srtyp, WBITS, val_ti, word_ndx*WRDBYTES);

     cint_ti2 = __gen_cint_tn(dst_ndx*WRDBYTES);
     dst_ti = __con_adradd_insn(srtyp, WBITS, addr_apti, dst_ndx*WRDBYTES);
     cint_ti3 = __gen_cint_tn(sbit1);
     t1_ti = __emit_shiftr(WBITS, cint_ti3, src_ti);
     __emit_copy(WRDBYTES, t1_ti, dst_ti);

     if ((bi += sbit2) >= n_numbits) break;

     /* dwp[wi] |= (swp[wi + 1] << sbit2); */
     ofs = (word_ndx + 1)*WRDBYTES;
     src_ti = __con_adradd_insn(srtyp, WBITS, val_ti, ofs);
     cint_ti2 = __gen_cint_tn(sbit2);
     t1_ti = __emit_shiftl(WBITS, cint_ti2, src_ti);
     r1_ti = __emit_mask_or(dst_ti, t1_ti);
     __emit_copy(WRDBYTES, r1_ti, dst_ti);

      if ((bi += sbit1) >= n_numbits) break;
    }
   /* mask the high bits if needed */
   bofs = ubits_(n_numbits);
   if (bofs != 0)
    {
     mask_ti = __gen_cint_tn(__masktab[bofs]);
     r1_ti = __emit_mask_and(dst_ti, mask_ti);
     __emit_copy(WRDBYTES, r1_ti, dst_ti);
    }
   /* or in the save high word back in */
   r2_ti = __emit_mask_or(sav_hwadr_ti, sav_hw_ti);
   __emit_copy(WRDBYTES, r2_ti, sav_hwadr_ti);
  }
}

/*
 * emit instructions to evaluate rhs part select into pr tmp
 *
 * notice new algorithsm that uses copies not in formal tmp tab so result
 * always in the same tmp
 */
static int32 gen_rhs_concat(struct expr_t *lcbndp)
{
 int32 catxlen;
 struct expr_t *catndp, *catrhsx; 
 int32 bi1, res_apti, rhs_ti, blen, rhs_srtyp, srtyp;
 int32 hghw_apti, hghw_bpti, res_bpti, ofs;

 /* AIV 10/27/09 - now have better code to just shift/orin one word concat */
 blen = lcbndp->szu.xclen;
 if (__is_expr_2state(lcbndp))
  {
   srtyp = SR_BIT2S;
  }
 else srtyp = SR_VEC;

 if (blen <= WBITS && all_els_not_signed(lcbndp))
  {
   return(gen_rhs_concat_1w(lcbndp, srtyp));
  }

 res_apti = __gen_tn(srtyp, blen);
 /* AIV 10/27/09 - only need to zero the high word if not word aligned */
 if (ubits_(blen) != 0)
  {
   ofs = WRDBYTES*(wlen_(blen) - 1);
   hghw_apti = __con_adradd_insn(srtyp, blen, res_apti, ofs);
   __emit_store_cint(hghw_apti, 0, WRDBYTES);
 
   if (srtyp == SR_VEC)
    {
     res_bpti = __get_bpti(res_apti);
     hghw_bpti = __con_adradd_insn(srtyp, blen, res_bpti, ofs);
     __emit_store_cint(hghw_bpti, 0, WRDBYTES);
    }
  }

 /* now evaluate components and assign to section of ap/bp */
 /* first concat component is highest bit(s) so work from high bits to low */ 
 for (catndp = lcbndp->ru.x; catndp != NULL; catndp = catndp->ru.x)
  {
   /* catrhsx actual rhs concat component expr. with width catxlen */
   catrhsx = catndp->lu.x;
   catxlen = catrhsx->szu.xclen;
   /* catndp comma node is dist. to low bit, bi1 is low bit of rhs psel */
   bi1 = catndp->szu.xclen - catxlen;

   /* know select index in rng */
   /* AIV 11/10/09 - want a vector here */
   rhs_ti = __gen_expr_eval(catrhsx, WANT_A_VEC);
   rhs_srtyp = __tntab[rhs_ti].srtyp;
   if (rhs_srtyp != srtyp)
    {
     rhs_ti = __gen_cnvt_srep_ifneeded(rhs_ti, srtyp, catxlen, FALSE,
       FALSE, FALSE);
    }
   if (catxlen == 1)
    {
     /* AIV 10/27/09 - if scalar now handled in __gen_st_bsel */
     __gen_st_bsel(srtyp, res_apti, rhs_ti, bi1);
    }
   else
    {
     __gen_st_psel(srtyp, res_apti, rhs_ti, bi1, catxlen);
    }
   /* size is exact width of cat pr tmp */
  }
 return(res_apti);
}

/*
 * return T if all elements of concat are unsigned - if any sized usually
 * ints really need the psels
 *
 * SJM 03-03-14 - new routine - can use shift and or for signed
 */
static int32 all_els_not_signed(struct expr_t *lcbndp)
{
 struct expr_t *catndp, *catrhsx;

 for (catndp = lcbndp->ru.x; catndp != NULL; catndp = catndp->ru.x)
  {
   catrhsx = catndp->lu.x;
   if (catrhsx->has_sign) return(FALSE);
  }
 return(TRUE);
}

/*
 * AIV 10/27/09 - known to fit into 1 word rhs concat
 * just need to shift and or - no complicate bsel/psel
 *
 */
static int32 gen_rhs_concat_1w(struct expr_t *lcbndp, int32 srtyp)
{
 int32 catxlen;
 struct expr_t *catndp, *catrhsx; 
 int32 bi1, res_apti, res_bpti, rhs_ti, rhs_bpti, blen; 
 int32 t1_ti, t2_ti, cint_ti, is_a_set, is_b_set;

 blen = lcbndp->szu.xclen;

 /* must init result to 0 both a and b part */
 res_apti = __gen_tn(srtyp, blen);

 is_a_set = is_b_set = FALSE;
 /* now evaluate components and assign to section of ap/bp */
 /* first concat component is highest bit(s) so work from high bits to low */ 
 for (catndp = lcbndp->ru.x; catndp != NULL; catndp = catndp->ru.x)
  {
   /* catrhsx actual rhs concat component expr. with width catxlen */
   catrhsx = catndp->lu.x;
   catxlen = catrhsx->szu.xclen;
   bi1 = catndp->szu.xclen - catxlen;

   /* AIV 11/10/09 - want a vector here */
   rhs_ti = __gen_expr_eval(catrhsx, WANT_A_VEC);
   rhs_ti = __gen_cnvt_srep_ifneeded(rhs_ti, srtyp, catxlen, FALSE, FALSE, 
      FALSE);

   /* just need to shift and or in value */
   cint_ti = __gen_cint_tn(bi1);
   t1_ti = __emit_shiftl(WBITS, cint_ti, rhs_ti);
   /* first pass just assign the value no need to or in */
   if (!is_a_set)
    {
     t2_ti = t1_ti;
     is_a_set = TRUE;
    }
   else t2_ti = __emit_bin_bitor(WBITS, t1_ti, res_apti);
   __emit_copy(WRDBYTES, t2_ti, res_apti);

   if (srtyp == SR_BIT2S) continue;

   /* same thing with the b part */
   res_bpti = __get_bpti(res_apti);
   rhs_bpti = __get_bpti(rhs_ti);
   t1_ti = __emit_shiftl(WBITS, cint_ti, rhs_bpti);
   if (!is_b_set)
    {
     t2_ti = t1_ti;
     is_b_set = TRUE;
    }
   else t2_ti = __emit_bin_bitor(WBITS, t1_ti, res_bpti);
   __emit_copy(WRDBYTES, t2_ti, res_bpti);
  }
 return(res_apti);
}

/*
 * gen insn wrapper to call sys func (uses RT support code)
 */
static int32 gen_sysfcall(struct expr_t *ndp)
{
 int32 blen, fcallx_ti, res_ti, xstk_apti, input_ti, dbl_ti, asl_typ;
 int32 nbytes, rettyp, is_trans;
 struct expr_t *fax;
 struct sy_t *fsyp;
 struct sysfunc_t *sfbp;

 fsyp = ndp->lu.x->lu.sy; 
 sfbp = fsyp->el.esyftbp;
 asl_typ = -1;
 /* AIV 07/24/08 - if common $random just call wrapper and return rand value */
 /* AIV LOOKATME - add more of the common case system calls ??????? */
 //AIV FIXME - lower new SV functions - like $isunknown 
 is_trans = is_1arg_transcendental(sfbp->syfnum, &asl_typ);
 if (sfbp->syfnum == STN_RANDOM)
  {
   return(gen_random_syscall(ndp));
  }
 /* AIV 08/17/11 - if not real warns just inline the real functions */
 /* otherwise use the wrapper which will emit the warning messages */
 /* same as the interpreter */
 else if (!__real_warns && is_trans)
  {
   /* AIV 09/13/10 - this built in libc math functions should just be called */
   /* no need to do the sysfunc wrapper */
   fax = ndp->ru.x->lu.x;
   input_ti = __gen_expr_eval(fax, -1);
   /* need to pass in a double */
   dbl_ti = __gen_cnvt_srep_ifneeded(input_ti, SR_VEC, 64, FALSE, TRUE, FALSE);
   res_ti = __emit_1arg_transcendental(dbl_ti, asl_typ);
   return(res_ti);
  }
 blen = ndp->szu.xclen;
 rettyp = sfbp->retntyp;
 /* AIV 09/13/10 - if two state return a 2-state type */
 /* notice can only have N_REG/N_REAL/N_TIME/ here */
 /* also changed this to only copy 64-bits for reals - one copy on 64-bit */
 res_ti = nbytes = -1;
 if (__opt_two_state)
  {
   /* AIV 02/24/12 - also need to check N_WIRE here as well */
   if (rettyp == N_REG || rettyp == N_TIME || rettyp == N_WIRE) 
    {
     res_ti = __gen_tn(SR_BIT2S, blen);
     nbytes = wlen_(blen)*WRDBYTES;
    }
   else if (rettyp == N_REAL) 
    {
     res_ti = __gen_tn(SR_VEC, blen);
     nbytes = 2*wlen_(blen)*WRDBYTES;
    }
   else __case_terr(__FILE__, __LINE__);
  }
 else 
  {
   res_ti = __gen_tn(SR_VEC, blen);
   nbytes = 2*wlen_(blen)*WRDBYTES;
  }

 /* SJM 01/25/06 - always use but mod inst only wrong for declarative */
 fcallx_ti = __gen_xpr_tn(ndp);

 /* this is the ptr to (addr of) tmp name that will hold fcall result */ 
 /* that is put on xstk */
 /* LOOKATME - change this when syscall doesn't use stack location for res */
 xstk_apti = __gen_tn(SR_VEC, blen);
 __tntab[xstk_apti].tn_typ = TN_ADR;

 /* AIV 08/17/11 - if is trans reals ops must set stmt location for */
 /* warning messages for NaNs */
 if (is_trans)
  {
   __emit_sysfcall_stmtloc(fcallx_ti, xstk_apti, __generating_stp); 
  }
 else __emit_sysfcall(fcallx_ti, xstk_apti); 

 /* since need RT support wrapper for sys fcalls - need xstk pop */
 __emit_copy(nbytes, xstk_apti, res_ti);
 /* AIV 09/01/05 - need to mark the sign and real type of the result */
 /* was doing wrong conversions otherwise */
 if (sfbp->retntyp == N_REAL) 
  {
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
  }
 if (sfbp->retsigned) __tntab[res_ti].t_signed = TRUE;
 return(res_ti);
}
   
/*
 * generate code for $random
 */
static int32 gen_random_syscall(struct expr_t *ndp)
{
 int32 seed_ti, seed_bpti, val_ti, cint_ti, save_idp_ti;
 struct mod_t *targ_mdp;
 struct net_t *np;
 struct bblk_t *after_bbp;
 struct expr_t *fax, *idndp;
 struct gref_t *grp;
 
 cint_ti = __gen_cint_tn(0);
 /* if has seed must pass it other wise just call wrapper call */
 if (ndp->ru.x != NULL && ndp->ru.x->optyp != OPEMPTY)
  {
   fax = ndp->ru.x->lu.x;

   seed_ti = __gen_expr_eval(fax, -1);
   if (!__tmp_is_2state(seed_ti))
    {
     seed_bpti = __get_bpti(seed_ti);
     __emit_copy(WRDBYTES, cint_ti, seed_bpti);
    }

   val_ti = __emit_random_with_seed(seed_ti);

   /* AIV 12/08/10 - seed value may need a change value */
   idndp = __get_lvalue_idndp(fax);
   np = idndp->lu.sy->el.enp;
   /* AIV 01/26/12 - must just check the bit flag here cannot optimize away */
   if (__net_chg_nd_store(np, -1, -1))
    {
     after_bbp = __alloc_bblk(FALSE);

     save_idp_ti = -1;
     /* AIV 05/14/12 - if XMR need to push __idp here for net change record */
     if (fax->optyp == GLBREF)
      {
       grp = fax->ru.grp;
       save_idp_ti = __gen_ld_xmr_idp(grp);

       targ_mdp = grp->targmdp; 
       __push_wrkitstk(targ_mdp, 0);
      }

     __gen_record_const_nchg(np, -1, -1, after_bbp);
     __start_bblk(after_bbp);

     if (save_idp_ti != -1)
      {
       __gen_restore_idp(save_idp_ti);
       __pop_wrkitstk();
      }
    }
  }
 else val_ti = __emit_random();

 /* AIV 08/01/08 - forgot to turn signed bit on this is always signed */
 __tntab[val_ti].t_signed = TRUE;
 return(val_ti);
}
 
/*
 * if is a 1 arg transcendental return TRUE along with wrapper type set
 * else false
 */
static int32 is_1arg_transcendental(int32 syfnum, int32 *asl_typ)
{
 switch (syfnum) {
  case STN_COS: *asl_typ = ASL_COS;  return(TRUE);
  case STN_SIN: *asl_typ = ASL_SIN;  return(TRUE);
  case STN_TAN: *asl_typ = ASL_TAN;  return(TRUE);
  case STN_CEIL: *asl_typ = ASL_CEIL;  return(TRUE);
  case STN_FLOOR: *asl_typ = ASL_FLOOR;  return(TRUE);
  case STN_ACOS: *asl_typ = ASL_ACOS;  return(TRUE);
  case STN_ASIN: *asl_typ = ASL_ASIN;  return(TRUE);
  case STN_ATAN: *asl_typ = ASL_ATAN;  return(TRUE);
  case STN_COSH: *asl_typ = ASL_COSH;  return(TRUE);
  case STN_SINH: *asl_typ = ASL_SINH;  return(TRUE);
  case STN_TANH: *asl_typ = ASL_TANH;  return(TRUE);
  case STN_ACOSH: *asl_typ = ASL_ACOSH;  return(TRUE);
  case STN_ASINH: *asl_typ = ASL_ASINH;  return(TRUE);
  case STN_ATANH: *asl_typ = ASL_ATANH;  return(TRUE);
  case STN_LN: *asl_typ = ASL_LN;  return(TRUE);
  case STN_LOG10: *asl_typ = ASL_LOG10;  return(TRUE);
  case STN_ABS: *asl_typ = ASL_ABS;  return(TRUE);
  case STN_SQRT: *asl_typ = ASL_SQRT;  return(TRUE);
  case STN_EXP: *asl_typ = ASL_EXP;  return(TRUE);
 }
 return(FALSE);
}

/*
 * gen insns to call user function 
 * returns index of tmp name containing result
 */
static int32 gen_fcall(struct expr_t *ndp, struct st_t *stp)
{
 int32 res_apti, copy_res_ti, is_void;
 int32 xmr_save_idp_ti, func_idp_ti, cp_back_idp_ti;
 struct sy_t *fsyp;
 struct task_pin_t *tpp;
 struct task_t *tskp;
 struct net_t *np;
 struct expr_t *argxp;
 struct gref_t *grp;
 struct mod_t *mdp;
 struct expr_t *tkxp, *xp, *argshd_xp;
 struct tskcall_t *tkcp;

 /* AIV 11/08/10 - need to handle SV 'void functions' */
 if (ndp == NULL)
  {
   tkcp = &(stp->st.stkc);
   tkxp = tkcp->tsksyx;
   fsyp = tkxp->lu.sy;
   tskp = fsyp->el.etskp;
   is_void = TRUE;
   /* DBG remove -- */
   if (!tskp->is_void_func) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   xp = tkxp;
   argshd_xp = tkcp->targs;
  }
 else
  {
   fsyp = ndp->lu.x->lu.sy; 
   tskp = fsyp->el.etskp;
   is_void = FALSE;
   /* DBG remove -- */
   if (tskp->is_void_func) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   xp = ndp;
   argshd_xp = ndp->ru.x; 
  }

 /* if function is DPI - handle in seperate routine */
 if (tskp->tf_dpip)
  {
   return(gen_fcall_dpi(ndp, stp));
  }

 /* compute the xmr fcall target (defined in) itree loc */
 grp = NULL;
 xmr_save_idp_ti = -1;
 cp_back_idp_ti = -1;
 /* AIV 04/12/10 - put in the code to be handle automatic functions */
 /* just need to alloc and copy into new tmp idp and later copy back */
 if (xp->lu.x->optyp == GLBREF)
  {
   /* for XMR task call, get inst_ptr into addr reg but can't push */
   /* SJM 01/25/06 - always use but mod inst only wrong for declarative */
   /* must get tsk exec itree location but cannot change to yet */
   grp = xp->lu.x->ru.grp;
   xmr_save_idp_ti = __emit_save_cur_idp();
   func_idp_ti = __gen_ld_task_xmr_idp(grp);
   if (tskp->is_auto) 
    {
     cp_back_idp_ti = func_idp_ti;
     func_idp_ti = __emit_new_auto_idp_area(func_idp_ti);
    }

   mdp = grp->targmdp;
  }
 else 
  {
   if (tskp->is_auto) 
    {
     xmr_save_idp_ti = __emit_save_cur_idp();
     cp_back_idp_ti = xmr_save_idp_ti;
     func_idp_ti = __emit_new_auto_idp_area(xmr_save_idp_ti);
    }
   else func_idp_ti = -1; 
   mdp = __inst_mod;
  }
  

 /* evaluate and store input params */
 /* 1st tpp is by convention is return value but 1st arg is real arg */
 /* know number matches exactly (no ,,) or will not get here */ 
 /* AIV - if from task called from function/task must set rhs to search */ 
 /* within that function */
 tpp = tskp->tskpins->tpnxt;
 for (argxp = argshd_xp; argxp != NULL; argxp = argxp->ru.x, tpp = tpp->tpnxt)
  {
   /* AIV 11/22/10 - now SV functions can have outputs */
   if (tpp->trtyp == IO_OUT) continue;
   np = tpp->tpsy->el.enp;
   /* AIV 07/06/07 - shouldn't be changing to indx again for passed args */
   gen_st_one_tfins(np, argxp->lu.x, func_idp_ti, mdp);
  }

 if (func_idp_ti != -1)
  {
   __push_wrkitstk(mdp, 0);
   __memloc_emit_set_idp(func_idp_ti);
  }

 __emit_call_func(tskp);

 copy_res_ti = -1;
 if (!is_void)
  {
   tpp = tskp->tskpins;
   np = tpp->tpsy->el.enp;
   res_apti = __gen_ld_net_addr(np, NULL);
   /* AIV 11/09/06 - need to save the result to handle the case : */
   /* res = f1(r0)^f1(r1); */
   /* AIV LOOKATME - really only need to copy for more than one call on rhs */
   /* probably better to just pass the stack location as an address to */
   /* the function and have it place the value into the addr */
   copy_res_ti = __gen_tn(np->srep, np->nwid);
   __gen_st_val(np, copy_res_ti, res_apti);
   /* must set the bits of the tmp storage area to do correct conversion */
   if (np->n_signed) __tntab[copy_res_ti].t_signed = TRUE;
   if (np->ntyp == N_REAL)  
    {
     __tntab[copy_res_ti].t_real = TRUE;
     __tntab[copy_res_ti].tn_used_wide = TRUE;
    }
  }

 /* AIV 11/22/10 - now SV functions can have outputs - assign out values */
 tpp = tskp->tskpins->tpnxt;
 for (argxp = argshd_xp; argxp != NULL; argxp = argxp->ru.x, tpp = tpp->tpnxt)
  {
   if (tpp->trtyp == IO_IN) continue;

   np = tpp->tpsy->el.enp;
   gen_st_one_tfouts(np, argxp->lu.x, func_idp_ti, __inst_mod);
  }

 if (func_idp_ti != -1) 
  { 
   __gen_restore_idp(xmr_save_idp_ti);
   __pop_wrkitstk(); 
  }
 /* if automatic need to copy back the local idp area into static idp area */
 if (tskp->is_auto) 
  {
   __emit_cp_auto_idp_area_func(cp_back_idp_ti, func_idp_ti);
  }

 /* notice function returns its result - call may need to convert */
 return(copy_res_ti);
}

/*
 * generate code to call a DPI function
 * almost identical to task DPI - but currently no need unpack since it
 * cannot take outputs
 */
static int32 gen_fcall_dpi(struct expr_t *ndp, struct st_t *stp)
{
 int32 res_apti, offset, srep, copy_res_ti, mask_ti, nargs;
 int32 pass_as_adr, i, save_idp_ti, rhs_apti, num_strings;
 int32 *string_tmps, *input_tmps, *wide_tmps;
 struct sy_t *fsyp;
 struct task_pin_t *tpp;
 struct task_t *tskp;
 struct net_t *np;
 struct expr_t *argxp, *lhsx;
 struct dpi_t *dpip;
 struct expr_t *tkxp, *argshd_xp;
 struct tskcall_t *tkcp;
#ifdef __CVC32__
 int32 r_ti, ubits, wlen, copy_ofs_ti;
#else
 int32 inreg_argno, onstk_argno, inreal_xmm_argno;
#endif


 /* AIV 11/08/10 - need to handle SV 'void functions' */
 if (ndp == NULL)
  {
   tkcp = &(stp->st.stkc);
   tkxp = tkcp->tsksyx;
   fsyp = tkxp->lu.sy;
   tskp = fsyp->el.etskp;
   /* DBG remove -- */
   if (!tskp->is_void_func) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   argshd_xp = tkcp->targs;
  }
 else
  {
   fsyp = ndp->lu.x->lu.sy; 
   tskp = fsyp->el.etskp;
   /* DBG remove -- */
   if (tskp->is_void_func) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   argshd_xp = ndp->ru.x; 
  }

 /* DBG remove -- */
 if (tskp->is_auto) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* compute the xmr fcall target (defined in) itree loc */
 wide_tmps = NULL;
 num_strings = 0;
 nargs = 0;
 /* count the number of args */
 tpp = tskp->tskpins->tpnxt;
 for (argxp = argshd_xp; argxp != NULL; argxp = argxp->ru.x, tpp = tpp->tpnxt)
  {
   nargs++;
  }

 if (nargs != 0)
  {
   string_tmps = (int32 *) __my_malloc(nargs*sizeof(int32));
   input_tmps = (int32 *) __my_malloc(nargs*sizeof(int32));
   memset(string_tmps, 0, nargs*sizeof(int32));
   memset(input_tmps, 0, nargs*sizeof(int32));
  }
 /* AIV 11/15/10 - need to convert strings to C-style strings */
 /* need to do these first since use wrappers cannot set stack to call */
 /* DPI function until after all wrapper calls have been made */
 tpp = tskp->tskpins->tpnxt;
 i = 0;
 for (argxp = argshd_xp; argxp != NULL; argxp = argxp->ru.x, tpp = tpp->tpnxt)
  {
   np = tpp->tpsy->el.enp;
   lhsx = argxp->lu.x;
   if (np->ntyp == N_STRING)
    {
     /* if output just make dummy space */
     if (tpp->trtyp == IO_OUT)
      {
       rhs_apti = __gen_tn(SR_BIT2S, 2048);
       __tntab[rhs_apti].tn_used_wide = TRUE;
       rhs_apti = __gen_stack_adr(rhs_apti);
      }
     //AIV LOOKATME - leaking memory here - for both stack and char * pointer 
     //nchars_ti = __gen_tn(SR_CINT, WBITS);
     else 
      {
       rhs_apti = __emit_sv_dpi_string(lhsx, -1);
       num_strings++;
      }
     string_tmps[i] = rhs_apti;    
    }
  }

 /* evaluate and store input params */
 /* 1st tpp is by convention is return value but 1st arg is real arg */
 /* know number matches exactly (no ,,) or will not get here */ 
 /* AIV - if from task called from function/task must set rhs to search */ 
 /* within that function */
 tpp = tskp->tskpins->tpnxt;
 offset = 0;
#ifndef __CVC32__
 inreg_argno = 0;
 onstk_argno = 0;
 inreal_xmm_argno = 0;
#endif
 i = 0;
 for (argxp = argshd_xp; argxp != NULL; argxp = argxp->ru.x, tpp = tpp->tpnxt)
  {
   np = tpp->tpsy->el.enp;

   lhsx = argxp->lu.x;
   rhs_apti = gen_arg_dpi(np, &pass_as_adr, lhsx, input_tmps, &wide_tmps, i, 
     tpp->trtyp, string_tmps);

#ifdef __CVC32__
   offset = __emit_call_func_arg_dpi(np, offset, rhs_apti, pass_as_adr, 
     tpp->trtyp);
#else
   __emit_call_func_arg_dpi(np, rhs_apti, pass_as_adr, tpp->trtyp, 
     &(inreg_argno), &(onstk_argno), &(inreal_xmm_argno));
#endif
   i++;
  }

 /* AIV 05/23/12 - need to record the number of words passed to DPI wrapper */
 __cur_flowg->max_dpi_wrds = offset/WRDBYTES;

 /* AIV 11/15/10 - SV strings are just evaled - need to adjust stack */
 //AIV LOOKATME - leaking memory here - for both stack and char * pointer 
 if (num_strings > 0) __emit_pop_xstk(num_strings);

 /* need to save/restore idp since uses can now change using setScope */
 save_idp_ti = __emit_save_cur_idp();
 __emit_call_func_dpi(tskp);
 __gen_restore_idp(save_idp_ti);

 tpp = tskp->tskpins;
 /* AIV 11/16/10 - SV functions can have outputs */
 gen_assign_dpi_outputs(argshd_xp, tpp, input_tmps, wide_tmps);

 np = tpp->tpsy->el.enp;
 dpip = tskp->tf_dpip;
 copy_res_ti = -1;
 /* 'void functions' - have no return value */
 if (dpip->has_ret)
  {
   copy_res_ti = __gen_tn(np->srep, np->nwid);
   if (np->ntyp == N_REAL)  
    {
     __tntab[copy_res_ti].t_real = TRUE;
     __tntab[copy_res_ti].tn_used_wide = TRUE;
     __gen_ld_return_real_dpi(copy_res_ti);
     if (string_tmps != NULL) 
      {
       __my_free(input_tmps, nargs*sizeof(int32));
       __my_free(string_tmps, nargs*sizeof(int32));
      }
     return(copy_res_ti);
    }
   res_apti = __gen_ld_return_dpi(np);
   srep = np->srep;
  //AIV WRITEME
#ifdef __CVC32__
   if (srep == SR_SCAL || srep == SR_SSCAL || srep == SR_SCAL2S)
    {
     /* user could return larger than valid value - must mask */
     if (np->n_2state) mask_ti = __gen_cint_tn(1);
     else mask_ti = __gen_cint_tn(3);
     res_apti = __emit_bin_bitand(WBITS, mask_ti, res_apti);

     __emit_copy(1, res_apti, copy_res_ti);
    }
   else 
    {
     wlen = wlen_(np->nwid);
     ubits = ubits_(np->nwid);
     if (ubits_(np->nwid) != 0)
      {
       mask_ti = __gen_cint_tn(__masktab[ubits]);
       res_apti = __emit_bin_bitand(WBITS, mask_ti, res_apti);
      }
     __emit_copy(WRDBYTES, res_apti, copy_res_ti);
     /* AIV BEWARE - machine dependent - return high part in edx */
     /* this is only for long long int (longint) which returns high */
     /* word in edx */
     if (wlen == 2)
      {
       copy_ofs_ti = __con_adradd_insn(SR_VEC, WBITS, copy_res_ti, WRDBYTES);
       r_ti = __move_srep_insn(TN_VAL, I_MOVA, np->srep, np->nwid, AM_REG, 
         AR_DX);
       __emit_copy(WRDBYTES, r_ti, copy_ofs_ti);
      }
    }
#else
   if (srep == SR_SCAL || srep == SR_SSCAL || srep == SR_SCAL2S)
    {
     /* user could return larger than valid value - must mask */
     if (np->n_2state) mask_ti = __gen_cint_tn(1);
     else mask_ti = __gen_cint_tn(3);
     res_apti = __emit_bin_bitand(WBITS, mask_ti, res_apti);

     __emit_copy(1, res_apti, copy_res_ti);
    }
   else
    {
     if (ubits_(np->nwid) != 0)
      {
       mask_ti = __gen_cint_tn(__masktab[ubits_(np->nwid)]);
        res_apti = __emit_bin_bitand(WBITS, mask_ti, res_apti);
      }
     __emit_copy(WRDBYTES, res_apti, copy_res_ti);
    }
#endif

   /* must set the bits of the tmp storage area to do correct conversion */
   if (np->n_signed) __tntab[copy_res_ti].t_signed = TRUE;
  }

 /* notice function returns its result - call may need to convert */
 if (string_tmps != NULL) 
  {
   __my_free(input_tmps, nargs*sizeof(int32));
   __my_free(string_tmps, nargs*sizeof(int32));
  }
 return(copy_res_ti);
}
     
/*
 * pack a vector into 32-bit defined svLogicVecVal
 */
static int32 gen_packed_svLogicVecVal_dpi(struct net_t *np, int32 rhs_apti, 
 int32 trtyp, int32 needs_record)
{
 int32 new_ti, new_ofs_ti, rhs_ofs_ti, blen, srtyp;
 int32 i, wlen, ofs, r_bpti_ofs, r_apti_ofs, is_2state;

#ifndef __CVC32__
 /* AIV FIXME - these has issues with alignment on 32-bit */
 /* this was to be marked wide because 32-64 bits on 64-bit will not decomp */
 /* so always mark as wide */
 __tntab[rhs_apti].tn_used_wide = TRUE;
#endif

 if (np->n_2state)
  {
   is_2state = TRUE;
   srtyp = SR_BIT2S;
  }
 else
  {
   is_2state = FALSE;
   srtyp = SR_VEC;
  }

 blen = np->nwid;
 new_ti = __gen_tn(srtyp, blen);

 __tntab[new_ti].tn_used_wide = TRUE;
 /* if output no need to pack results just passing space to store */
 if (trtyp == IO_OUT && !needs_record) return(new_ti);

 wlen = (blen + 31) >> 5;
 __emit_copy(INTBYTES, rhs_apti, new_ti);

 r_bpti_ofs = 0;
 if (!is_2state)
  {
   r_bpti_ofs = wlen_(blen)*WRDBYTES;
   rhs_ofs_ti = __con_adradd_insn(srtyp, INTBITS, rhs_apti, r_bpti_ofs);
   r_bpti_ofs += INTBYTES;
   r_apti_ofs = INTBYTES;

   ofs = INTBYTES;
   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, ofs);
   __emit_copy(INTBYTES, rhs_ofs_ti, new_ofs_ti);
   ofs += INTBYTES;
  }
 else 
  {
   r_apti_ofs = INTBYTES;
   ofs = INTBYTES;
  }

 for (i = 1; i < wlen; i++) 
  {
   rhs_ofs_ti = __con_adradd_insn(srtyp, INTBITS, rhs_apti, r_apti_ofs);
   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, ofs);
   __emit_copy(INTBYTES, rhs_ofs_ti, new_ofs_ti);
   r_apti_ofs += INTBYTES;
   ofs += INTBYTES;

   if (is_2state) continue;

   rhs_ofs_ti = __con_adradd_insn(srtyp, INTBITS, rhs_apti, r_bpti_ofs);
   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, ofs);
   __emit_copy(INTBYTES, rhs_ofs_ti, new_ofs_ti);
   r_bpti_ofs += INTBYTES;
   ofs += INTBYTES;
  }
 return(new_ti);
}

/*
 * pack a CVC array into 32-bit svLogicVecVal
 */
static int32 gen_packed_svLogicVecVal_array_dpi(struct net_t *np, int32 trtyp,
 int32 **wide_tmps, int32 needs_record)
{
 int32 new_ti;

//AIV WRITEME
 if (np->mda != NULL) __misc_terr(__FILE__, __LINE__);

 *wide_tmps = NULL;
 if (np->ntyp == N_REAL)
  {
   /* if input only must copy the expression to tmp area */
#ifdef __CVC32__
   if (needs_record)
#else
   /* 64-bit must pack into 64-bit since REALBITS is 64-bit */
   /* wasting space and must pack into C style double array */
   if (trtyp == IO_IN || trtyp == IO_BID)
#endif
    {
     new_ti = gen_packed_svLogicVecVal_array_real_dpi(np, trtyp, needs_record);
    }
   else new_ti = __gen_ld_netbp(np);
   return(new_ti);
  }
 else if (np->nwid == 1) 
  {
   new_ti = gen_packed_svLogicVecVal_array_scalar_dpi(np, trtyp, needs_record);
  }
 /* these need to be INTBITS - since packed into 32-bit values in svdpi.h */
 else if (np->nwid <= INTBITS)
  {
   if (np->nwid > INTBITS/2) 
    {
     new_ti = gen_packed_svLogicVecVal_array_1w_dpi(np, trtyp, needs_record);
    }
   else 
    {
     new_ti = gen_packed_svLogicVecVal_array_1w_packed_dpi(np, trtyp, 
        needs_record);
    }
  }
 else 
  {
   /* array elements are wide */
   new_ti = gen_packed_svLogicVecVal_array_wide_dpi(np, wide_tmps, trtyp, 
    needs_record);
  }

 return(new_ti);
}


/* 
 * packed scalar array into svLogicVecVal 
 */
static int32 gen_packed_svLogicVecVal_array_scalar_dpi(struct net_t *np,
 int32 trtyp, int32 needs_record)
{
 int32 new_ti, array_ti, i, arr_sel_ti, new_ofs_ti, srtyp;
 
 if (np->n_2state) new_ti = __gen_tn(SR_VEC, np->arr_num_els);
 else new_ti = __gen_tn(SR_VEC, np->arr_num_els/2);

 array_ti = __gen_ld_netbp(np); 
 __tntab[new_ti].tn_used_wide = TRUE;

 /* if output no need to pack results just passing space to store */
 if (trtyp == IO_OUT && !needs_record) return(new_ti);

//AIV LOOKATME - this could be more effecient????
 for (i = 0; i < np->arr_num_els; i++)
  {
   arr_sel_ti = gen_ld_scalar_arrsel_const(np, array_ti, i);
   if (np->n_2state) srtyp = SR_SCAL2S;
   else srtyp = SR_SCAL;

   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, i);
   __emit_copy(1, arr_sel_ti, new_ofs_ti);
  }
 return(new_ti);
}

static int32 gen_packed_svLogicVecVal_array_1w_dpi(struct net_t *np, 
 int32 trtyp, int32 needs_record)
{
 int32 new_ti, array_ti;

 array_ti = __gen_ld_netbp(np); 
 new_ti = __gen_tn(SR_VEC, np->nwid*np->arr_num_els);
 __tntab[new_ti].tn_used_wide = TRUE;
 /* if output no need to pack results just passing space to store */
 if (trtyp == IO_OUT && !needs_record) return(new_ti);

 __emit_copy(2*wlen_(np->nwid*np->arr_num_els)*WRDBYTES, array_ti, new_ti);
 return(new_ti);
}

/*
 * pack a word array into a 32-bit array
 */
static int32 gen_packed_svLogicVecVal_array_1w_packed_dpi(struct net_t *np, 
 int32 trtyp, int32 needs_record)
{
 int32 new_ti, array_ti, i, sel_apti, sel_bpti, new_ofs_ti, ofs;
 int32 srtyp;

 array_ti = __gen_ld_netbp(np); 
 if (np->n_2state) srtyp = SR_BIT2S;
 else srtyp = SR_VEC;

 new_ti = __gen_tn(srtyp, np->nwid*np->arr_num_els);
 __tntab[new_ti].tn_used_wide = TRUE;

 /* if output no need to pack results just passing space to store */
 if (trtyp == IO_OUT && !needs_record) return(new_ti);

 ofs = 0;
 for (i = 0; i < np->arr_num_els; i++)
  {
   sel_apti = gen_rhs_arrsel_const(np, array_ti, i);
   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, ofs);
   __emit_copy(INTBYTES, sel_apti, new_ofs_ti);
   ofs += INTBYTES;
   if (srtyp == SR_BIT2S) continue;
   sel_bpti = __get_bpti(sel_apti);
   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, ofs);
   __emit_copy(INTBYTES, sel_bpti, new_ofs_ti);
   ofs += INTBYTES;
  }
 return(new_ti);
}

#ifdef __CVC32__
static int32 gen_packed_svLogicVecVal_array_real_dpi(struct net_t *np, 
 int32 trtyp, int32 needs_record)
{
 int32 new_ti, array_ti;

 array_ti = __gen_ld_netbp(np); 
 new_ti = __gen_tn(SR_VEC, (64*np->arr_num_els)/2);

 /* AIV 08/01/10 - need to shut off due to set_asl_call_amode code */
 /* need to handle as plan memory - not real */
 /* AIV LOOKATME - better method??? */
 /* case 2: pushing real */
 /* if (arg_tnp->t_real) */
 __tntab[array_ti].t_real = FALSE;
 __tntab[new_ti].tn_used_wide = TRUE;
 /* if output no need to pack results just passing space to store */
 if (trtyp == IO_OUT && !needs_record) return(new_ti);

 __emit_copy(WRDBYTES*(wlen_(64)*np->arr_num_els/2), array_ti, new_ti);
 return(new_ti);
}
#else
/*
 * 64-bit version is every other word since REALBITS is 64 for 64-bits
 * this is true because wlen_ in the interpreter so 64-bit reals are stored
 * in the a-part and the b-part is stored as wasted space.
 */
static int32 gen_packed_svLogicVecVal_array_real_dpi(struct net_t *np, 
 int32 trtyp, int32 needs_record)
{
 int32 new_ti, array_ti, i, array_ofs_ti, new_ofs_ti, ofs;

 array_ti = __gen_ld_netbp(np); 
 new_ti = __gen_tn(SR_VEC, (64*np->arr_num_els)/2);

 /* AIV 08/01/10 - need to shut off due to set_asl_call_amode code */
 /* need to handle as plan memory - not real */
 /* AIV LOOKATME - better method??? */
 /* case 2: pushing real */
 /* if (arg_tnp->t_real) */
 __tntab[array_ti].t_real = FALSE;
 __tntab[new_ti].tn_used_wide = TRUE;
 /* if output no need to pack results just passing space to store */
 if (trtyp == IO_OUT && !needs_record) return(new_ti);

 __emit_copy(WRDBYTES, array_ti, new_ti);
 /* AIV 09/16/10 - this wasn't quite right - still uses 2x */
 ofs = (2*WRDBYTES);
 for (i = 1; i < np->arr_num_els; i++)
  {
   array_ofs_ti = __con_adradd_insn(SR_VEC, WBITS, array_ti, ofs);
   new_ofs_ti = __con_adradd_insn(SR_VEC, WBITS, new_ti, (i*WRDBYTES));
   __emit_copy(WRDBYTES, array_ofs_ti, new_ofs_ti);
   ofs += (2*WRDBYTES);
  }
 return(new_ti);
}
#endif
   
/*
 * pack wide arrays into a pointer of wide elements
 */
static int32 gen_packed_svLogicVecVal_array_wide_dpi(struct net_t *np, 
 int32 **wide_tmps, int32 trtyp, int32 needs_record)
{
 int32 one_array_el_ti, arrays_ti, i, arr_sel_ti, ofs, arrays_ofs_ti;
 int32 array_ti, one_array_adr_ti;
 int32 *saved_tmps;

 arrays_ti = __gen_tn(SR_VEC, (np->arr_num_els*WBITS)/2);
 __tntab[arrays_ti].tn_used_wide = TRUE;

 array_ti = __gen_ld_netbp(np); 
 ofs = 0;
 saved_tmps = (int32 *) __my_malloc(np->arr_num_els*sizeof(int32));
 for (i = 0; i < np->arr_num_els; i++)
  {
   arr_sel_ti = gen_rhs_arrsel_const(np, array_ti, i);
   one_array_el_ti = gen_packed_svLogicVecVal_dpi(np, arr_sel_ti, trtyp, 
     needs_record);
   saved_tmps[i] = one_array_el_ti;
   arrays_ofs_ti = __con_adradd_insn(SR_VEC, INTBITS, arrays_ti, ofs);
   one_array_adr_ti = __gen_stack_adr(one_array_el_ti);
   __st_insn(I_STOREA, AM_REG, one_array_adr_ti, AM_REG, arrays_ofs_ti);
   ofs += WRDBYTES;
  }
 if (wide_tmps != NULL)
   *wide_tmps = saved_tmps;
 return(arrays_ti);
}

static void gen_st_unpacked_svLogicVecVal_array_dpi(struct net_t *np, 
 int32 rhs_ti, int32 *wide_tmps)
{
 int32 array_ti, needs_record;

 array_ti = __gen_ld_netbp(np); 
 needs_record = __net_chg_nd_store(np, -1, -1);
//AIV WRITEME
 if (np->mda != NULL) __misc_terr(__FILE__, __LINE__);

 if (np->ntyp == N_REAL)
  {
   /* if 32-bit double array is stored in C style */
   /* otherwise if 64-bit because REALBITS is 64 must unpack */
#ifdef __CVC32__
   if (!needs_record) return;
   gen_st_unpacked_svLogicVecVal_array_real_dpi(np, rhs_ti, array_ti);
#else
   gen_st_unpacked_svLogicVecVal_array_real_dpi(np, rhs_ti, array_ti);
#endif
  }
 else if (np->nwid == 1) 
  {
   gen_st_unpacked_svLogicVecVal_scalar_array_dpi(np, rhs_ti, array_ti);
  }
 else if (np->n_2state)
  {
#ifdef __CVC32__
   if (np->nwid > INTBITS) 
    {
     gen_st_unpacked_svLogicVecVal_array_wide_dpi(np, array_ti, wide_tmps);
    }
   else
    {
     gen_st_2state_svLogicVecVal_array_dpi(np, rhs_ti, array_ti);
    }
#else
   if (np->nwid > INTBITS) 
    {
     gen_st_unpacked_svLogicVecVal_array_wide_dpi(np, array_ti, wide_tmps);
    }
   else
    {
     gen_st_2state_svLogicVecVal_array_dpi(np, rhs_ti, array_ti);
    }
#endif
  }
 /* this needs to be INTBITS - always 32-bit even for 64-bit as defined by */
 /* the 32-bit structs in svdpi.h */
 else if (np->nwid <= INTBITS)
  {
   if (np->nwid > INTBITS/2) 
    {
     if (needs_record) 
      {
       gen_st_unpacked_svLogicVecVal_array_1w_changes_dpi(np, rhs_ti, array_ti);
      }
     else
      {
       __emit_copy(2*wlen_(np->nwid*np->arr_num_els)*WRDBYTES, rhs_ti, 
         array_ti);
      }
    }
   else 
    {
     gen_st_unpacked_svLogicVecVal_packed_array_dpi(np, rhs_ti, array_ti);
    }
  }
 else 
  {
   gen_st_unpacked_svLogicVecVal_array_wide_dpi(np, array_ti, wide_tmps);
  }
}
     
/*
 * 2-state array packing
 */
static void gen_st_2state_svLogicVecVal_array_dpi(struct net_t *np,
 int32 rhs_ti, int32 array_ti)
{
 int32 array_ofs_ti, rhs_ofs_ti, ofs, rofs, i;
 struct bblk_t *chg_bbp, *skip_bbp;

 ofs = 0;
 rofs = 0;
 for (i = 0; i < np->arr_num_els; i++)
  {
   array_ofs_ti = __con_adradd_insn(SR_BIT2S, INTBITS, array_ti, ofs);
   ofs += WRDBYTES;
   rhs_ofs_ti = __con_adradd_insn(SR_BIT2S, INTBITS, rhs_ti, rofs);
   rofs += INTBYTES;
   if (__net_chg_nd_store(np, i, i))
    {
     chg_bbp = __alloc_bblk(FALSE);
     skip_bbp = __alloc_bblk(FALSE);
     __emit_jmp_eq(skip_bbp, chg_bbp, array_ofs_ti, rhs_ofs_ti);
     __start_bblk(chg_bbp);
     __emit_copy(INTBYTES, rhs_ofs_ti, array_ofs_ti);
     __gen_record_const_nchg(np, i, i, skip_bbp);
     __emit_jmp(skip_bbp);
     __start_bblk(skip_bbp);
    }
   else __emit_copy(INTBYTES, rhs_ofs_ti, array_ofs_ti);
  }
}

#ifdef __CVC32__
/*
 * real 64-bit array unpack just copy in every other word
 */
static void gen_st_unpacked_svLogicVecVal_array_real_dpi(struct net_t *np, 
 int32 rhs_ti, int32 array_ti)
{
 int32 i, array_ofs_apti, rhs_ofs_apti, ofs;
 int32 t1_ti, t2_ti, t3_ti, array_ofs_bpti, rhs_ofs_bpti;
 struct bblk_t *chg_bbp, *skip_bbp;

 ofs = 0;
 for (i = 0; i < np->arr_num_els; i++)
  {
   array_ofs_apti = __con_adradd_insn(SR_VEC, WBITS, array_ti, ofs);
   rhs_ofs_apti = __con_adradd_insn(SR_VEC, WBITS, rhs_ti, ofs);
   ofs += WRDBYTES;
   __emit_copy(WRDBYTES, rhs_ofs_apti, array_ofs_apti);

   array_ofs_bpti = __con_adradd_insn(SR_VEC, WBITS, array_ti, ofs);
   rhs_ofs_bpti = __con_adradd_insn(SR_VEC, WBITS, rhs_ti, ofs);
   ofs += WRDBYTES;
   if (!__net_chg_nd_store(np, i, i)) 
    {
     __emit_copy(WRDBYTES, rhs_ofs_apti, array_ofs_apti);
     __emit_copy(WRDBYTES, rhs_ofs_bpti, array_ofs_bpti);
     continue;
    }
   skip_bbp = __alloc_bblk(FALSE);
   chg_bbp = __alloc_bblk(FALSE);

   t1_ti = __emit_bin_bitxor(WBITS, rhs_ofs_apti, array_ofs_apti);
   t2_ti = __emit_bin_bitxor(WBITS, rhs_ofs_bpti, array_ofs_bpti);
   t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
   __emit_jmp_0(skip_bbp, chg_bbp, t3_ti);
   __start_bblk(chg_bbp);
   __emit_copy(WRDBYTES, rhs_ofs_apti, array_ofs_apti);
   __emit_copy(WRDBYTES, rhs_ofs_bpti, array_ofs_bpti);
   __gen_record_const_nchg(np, i, i, skip_bbp);
   __emit_jmp(skip_bbp);
   __start_bblk(skip_bbp);
  }
}

#else
/*
 * real 64-bit array unpack just copy in every other word
 */
static void gen_st_unpacked_svLogicVecVal_array_real_dpi(struct net_t *np, 
 int32 rhs_ti, int32 array_ti)
{
 int32 i, array_ofs_ti, rhs_ofs_ti, ofs;
 struct bblk_t *chg_bbp, *skip_bbp;

 __emit_copy(WRDBYTES, rhs_ti, array_ti);
 /* AIV 09/16/10 - this wasn't quite right - still uses 2x */
 
 ofs = (2*WRDBYTES);
 for (i = 1; i < np->arr_num_els; i++)
  {
   array_ofs_ti = __con_adradd_insn(SR_VEC, WBITS, array_ti, ofs);
   rhs_ofs_ti = __con_adradd_insn(SR_VEC, WBITS, rhs_ti, (i*WRDBYTES));

   ofs += (2*WRDBYTES);
   if (!__net_chg_nd_store(np, i, i)) 
    {
     __emit_copy(WRDBYTES, rhs_ofs_ti, array_ofs_ti);
     continue;
    }

   skip_bbp = __alloc_bblk(FALSE);
   chg_bbp = __alloc_bblk(FALSE);
   __emit_jmp_eq(skip_bbp, chg_bbp, rhs_ofs_ti, array_ofs_ti);
   __start_bblk(chg_bbp);
   __emit_copy(WRDBYTES, rhs_ofs_ti, array_ofs_ti);
   __gen_record_const_nchg(np, i, i, skip_bbp);
   __emit_jmp(skip_bbp);
   __start_bblk(skip_bbp);
  }
}
#endif
   
/*
 * unpack a scalar array into CVC style storage
 */
static void gen_st_unpacked_svLogicVecVal_scalar_array_dpi(struct net_t *np, 
 int32 rhs_ti, int32 array_ti)
{
 int32 i, rhs_ofs_ti, srtyp;

 if (np->n_2state) srtyp = SR_SCAL2S;
 else srtyp = SR_SCAL;

 for (i = 0; i < np->arr_num_els; i++)
  {
   rhs_ofs_ti = __con_adradd_insn(srtyp, INTBITS, rhs_ti, i);
   gen_st_scalar_lhs_arrsel_const(np, array_ti, i, rhs_ofs_ti);
  }
}

/*
 * unpack a array into CVC packed array style storage
 */
static void gen_st_unpacked_svLogicVecVal_packed_array_dpi(struct net_t *np,
 int32 rhs_ti, int32 array_ti)
{
 int32 i, rhs_ofs_apti, rhs_ofs_bpti, tmp_ti, tmp_bpti, elofs, pckel_ti;
 int32 nbytes, wrd_ti, ofs;

 nbytes = -1;
 /* detremine number of bytes of copy */
 if (np->nwid <= 4) nbytes = 1;
 else if (np->nwid <= 8) nbytes = 2;
 else if (np->nwid <= WBITS/2) nbytes = WRDBYTES;
 else __case_terr(__FILE__, __LINE__);

 ofs = 0;
 for (i = 0; i < np->arr_num_els; i++)
  {
   rhs_ofs_apti = __con_adradd_insn(SR_VEC, INTBITS, rhs_ti, ofs);
   ofs += INTBYTES;
   rhs_ofs_bpti = __con_adradd_insn(SR_VEC, INTBITS, rhs_ti, ofs);
   ofs += INTBYTES;
   tmp_ti = __gen_tn(SR_VEC, INTBITS);
   __emit_copy(INTBYTES, rhs_ofs_apti, tmp_ti);

   tmp_bpti = __get_bpti(tmp_ti);
   __emit_copy(INTBYTES, rhs_ofs_bpti, tmp_bpti);

   elofs = gen_pck_ofset_const(np, i);
   pckel_ti = __con_adradd_insn(SR_VEC, np->nwid, array_ti, elofs);

   wrd_ti = bld_pck_nwval(np, tmp_ti, np->nwid);  
   if (__net_chg_nd_store(np, i, i))
      gen_chg_st_pck_arr_val(np, pckel_ti, wrd_ti, i, -1, TRUE);
   else __emit_copy(nbytes, wrd_ti, pckel_ti);
  }
}

/*
 * unpack a < 1w array into CVC style storage
 */
static void gen_st_unpacked_svLogicVecVal_array_1w_changes_dpi(
 struct net_t *np, int32 rhs_ti, int32 array_ti)
{
 int32 i, rhs_ofs_apti, rhs_ofs_bpti, array_ofs_apti, array_ofs_bpti;
 int32 ofs, t1_ti , t2_ti, t3_ti, rhs_wlen, arr_wlen;
 struct bblk_t *chg_bbp, *skip_bbp;

 /* rhs is always 32-bit wlen */
 rhs_wlen = (np->nwid + 31) >> 5;
 arr_wlen = wlen_(np->nwid);
 for (i = 0; i < np->arr_num_els; i++)
  {
   ofs = 2*i*arr_wlen*INTBYTES;
   array_ofs_apti = __con_adradd_insn(SR_VEC, INTBITS, array_ti, ofs);
   ofs += INTBYTES;
   array_ofs_bpti = __con_adradd_insn(SR_VEC, INTBITS, array_ti, ofs);

   ofs = 2*i*rhs_wlen*INTBYTES;
   rhs_ofs_apti = __con_adradd_insn(SR_VEC, INTBITS, rhs_ti, ofs);
   ofs += INTBYTES;
   rhs_ofs_bpti = __con_adradd_insn(SR_VEC, INTBITS, rhs_ti, ofs);
   if (!__net_chg_nd_store(np, i, i)) 
    {
     __emit_copy(INTBYTES, rhs_ofs_apti, array_ofs_apti);
     __emit_copy(INTBYTES, rhs_ofs_bpti, array_ofs_bpti);
     continue;
    }

   chg_bbp = __alloc_bblk(FALSE);
   skip_bbp = __alloc_bblk(FALSE);
   t1_ti = __emit_bin_bitxor(WBITS, rhs_ofs_apti, array_ofs_apti);
   t2_ti = __emit_bin_bitxor(WBITS, rhs_ofs_bpti, array_ofs_bpti);
   t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
   __emit_jmp_0(skip_bbp, chg_bbp, t3_ti);
   __start_bblk(chg_bbp);
   __emit_copy(INTBYTES, rhs_ofs_apti, array_ofs_apti);
   __emit_copy(INTBYTES, rhs_ofs_bpti, array_ofs_bpti);
   __gen_record_const_nchg(np, i, i, skip_bbp);
   __emit_jmp(skip_bbp);
   __start_bblk(skip_bbp);
  }
}


/*
 * unpack a wide array into CVC array style storage
 */
static void gen_st_unpacked_svLogicVecVal_array_wide_dpi(struct net_t *np, 
 int32 array_ti, int32 *wide_tmps)
{
 int32 one_array_el_ti, i, arrays_ofs_ti;
 int32 eladdr_ti, wlen, nbytes;
 struct bblk_t *chg_bbp, *skip_bbp;

 /* DBG remove -- */
 if (wide_tmps == NULL) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 wlen = wlen_(np->nwid);
 for (i = 0; i < np->arr_num_els; i++)
  {
   arrays_ofs_ti = wide_tmps[i];
   one_array_el_ti = gen_unpacked_svLogicVecVal_dpi(np, arrays_ofs_ti);

   eladdr_ti = gen_ndxarr_ptr_const(np, array_ti, i);
   nbytes = wlen*WRDBYTES;
   if (!np->n_2state) nbytes *= 2;

   if (__net_chg_nd_store(np, i, i))
    {
     chg_bbp = __alloc_bblk(FALSE);
     skip_bbp = __alloc_bblk(FALSE);
     __emit_jmp_eq(skip_bbp, chg_bbp, one_array_el_ti, eladdr_ti);
     __start_bblk(chg_bbp);
     __emit_copy(nbytes, one_array_el_ti, eladdr_ti);
     __gen_record_const_nchg(np, i, i, skip_bbp);
     __emit_jmp(skip_bbp);
     __start_bblk(skip_bbp);
    }
   else __emit_copy(nbytes, one_array_el_ti, eladdr_ti);
  }
 __my_free(wide_tmps, np->arr_num_els*sizeof(int32));
}


/*
 * unpack a 32-bit Vector into CVC style storage
 */
static int32 gen_unpacked_svLogicVecVal_dpi(struct net_t *np, int32 pli_ti)
{
 int32 new_ti, new_ofs_ti, pli_ofs_ti, is_2state, srtyp;
 int32 blen, i, wlen, ofs, new_bpti_ofs, pli_ofs;

 blen = np->nwid;
 if (np->n_2state)
  {
   is_2state = TRUE;
   srtyp = SR_BIT2S;
  }
 else
  {
   is_2state = FALSE;
   srtyp = SR_VEC;
  }
 new_ti = __gen_tn(srtyp, blen);
#ifndef __CVC32__
 /* AIV FIXME - these has issues with alignment on 32-bit */
 /* this was to be marked wide because 32-64 bits on 64-bit will not decomp */
 /* so always mark as wide */
 __tntab[new_ti].tn_used_wide = TRUE;
#endif

 wlen = (blen + 31) >> 5;
 __emit_copy(INTBYTES, pli_ti, new_ti);

 new_bpti_ofs = 0;
 if (!is_2state)
  {
   new_bpti_ofs = wlen_(blen)*WRDBYTES;
   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, new_bpti_ofs);
   new_bpti_ofs += INTBYTES;

   pli_ofs = INTBYTES;
   pli_ofs_ti = __con_adradd_insn(srtyp, INTBITS, pli_ti, pli_ofs);
   __emit_copy(INTBYTES, pli_ofs_ti, new_ofs_ti);
   pli_ofs += INTBYTES;
   ofs = INTBYTES;
  }
 else
  {
   pli_ofs = INTBYTES;
   ofs = INTBYTES;
  }
 

 for (i = 1; i < wlen; i++) 
  {
   pli_ofs_ti = __con_adradd_insn(srtyp, INTBITS, pli_ti, pli_ofs);
   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, ofs);
   __emit_copy(INTBYTES, pli_ofs_ti, new_ofs_ti);
   pli_ofs += INTBYTES;
   ofs += INTBYTES;

   if (is_2state) continue;

   new_ofs_ti = __con_adradd_insn(srtyp, INTBITS, new_ti, new_bpti_ofs);
   pli_ofs_ti = __con_adradd_insn(srtyp, INTBITS, pli_ti, pli_ofs);
   __emit_copy(INTBYTES, pli_ofs_ti, new_ofs_ti);

   new_bpti_ofs += INTBYTES;
   pli_ofs += INTBYTES;
  }
 return(new_ti);
}
 

/*
 * gen insns to eval ?: and return pr tmp index
 * for any qcol that has non real result 
 *
 * following interpreter tricky since unless sel x/z only eval one of : opands
 *
 * notice that key to this is that the various X/T/F results are all copied
 * into the actual return value tmp
 */
static int32 gen_qcol(struct expr_t *ndp)
{
 int32 sel_apti, sel_bpti, res_apti, x1_apti, x1_tmp_apti, x2_apti, blen;
 int32 is_bzero_ti, cint_ti, is_sel_scalar, srtyp, is_sel_2state;
 struct expr_t *f_ndp, *t_ndp;
 struct bblk_t *qcol_bbp, *xz_bbp, *t_bbp, *f_bbp, *after_bbp;
 struct bblk_t *non_xz_bbp, *t_assign_bbp, *f_assign_bbp, *bpart_nonzero_bbp; 
 struct bblk_t *check_any1_bbp; 

 blen = ndp->szu.xclen;
 /* AIV 09/02/08 - if all widths of qcol are 1 do as scalar op */
 f_ndp = ndp->ru.x->ru.x;
 t_ndp = ndp->ru.x->lu.x;
 sel_apti = __gen_expr_eval(ndp->lu.x, -1);
 is_sel_2state = (__tmp_is_2state(sel_apti) || 
                  __is_constant_with_zero_bpart(sel_apti));
 if (is_sel_2state)
  {
   return(gen_qcol_2state(ndp, sel_apti));
  }
 if (blen == 1 && ndp->lu.x->szu.xclen == 1 
     && ndp->ru.x->lu.x->szu.xclen == 1)
  {
   /* AIV 11/1209 - this was a problem for the same reasons the regular */
   /* qcol was - added a new leaf version and changed the other */
   if (__isleaf(f_ndp) && __isleaf(t_ndp)) 
    {
     return(gen_scalar_qcol_leaf(ndp, sel_apti));
    }
   else return(gen_scalar_qcol(ndp, sel_apti));
  }
 /* AIV 09/09/08 - if select value is constant just eval according to val */
 /* this is actually common because of following code */
 /* assign w = (constparam == "wide") ? narrow : wide; */
 if (__is_constant(sel_apti)) 
  {
   return(gen_qcol_const(sel_apti, ndp));
  }
 /* AIV 09/10/08 - if not chainded ?: do better code which evals each expr */
 /* this code is better because it doesn't double check values after */
 /* evals of t/f exprs */ 
 /* AIV LOOKATME - could determine depth and if < than x do this as well */
 /* AIV 02/13/09 - this should have been check for leaf with isleaf */
 if (__isleaf(f_ndp) && __isleaf(t_ndp))
  {
   /* AIV 02/10/09 - this was completely wrong - was missing return here */
   res_apti = gen_qcol_leaf(ndp, sel_apti);
   return(res_apti);
  }

 non_xz_bbp = xz_bbp = NULL;
 /* only need these blocks for wide */
 if (blen > WBITS)
  {
   xz_bbp = __alloc_bblk(TRUE);
   non_xz_bbp = __alloc_bblk(FALSE);
  }
 qcol_bbp = __alloc_bblk(FALSE);
 t_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 t_assign_bbp = __alloc_bblk(FALSE);
 f_assign_bbp = __alloc_bblk(FALSE);
 bpart_nonzero_bbp = __alloc_bblk(TRUE);

 /* all conditional results copied into this */
 res_apti = __gen_tn(SR_VEC, blen);
 /* SJM 10/24/04 - LOOKATME? insn for signs should be inserted but should */
 /* not cause any machine insns to be generated */
 is_sel_scalar = FALSE;
 srtyp = __tntab[sel_apti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   cint_ti = __gen_cint_tn(1);
   sel_bpti = __emit_shiftr(WBITS, cint_ti, sel_apti);
   sel_apti = __emit_bin_bitand(WBITS, cint_ti, sel_apti);
   is_sel_scalar = TRUE;
  }
 else
  {
   sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_VEC, ndp->lu.x->szu.xclen,
    ndp->lu.x->has_sign, FALSE, FALSE);

   sel_bpti = __get_bpti(sel_apti);
  }

 /* AIV 08/29/08 - if select is wide set save if b part in a reg */
 /* otherwise narrow is just the one reg actual b part */
 /* this was dumb for narrow because bpart fits in the one reg */
 if (blen > WBITS)
  {
   /* holds whether or not bpart is 0 */
   /* only set the word bpart value if wide */
   __emit_jmp_0(non_xz_bbp, xz_bbp, sel_bpti);
   is_bzero_ti = __gen_tn(SR_CINT, WBITS);

   /* set bpart to false (0) */ 
   __start_bblk(non_xz_bbp);
   __emit_store_cint(is_bzero_ti, 0, WRDBYTES);
   /* jump to test for if true */
   __emit_jmp(qcol_bbp);

   /* set bpart to true */ 
   __start_bblk(xz_bbp);
   __emit_store_cint(is_bzero_ti, 1, WRDBYTES);
   /* jump to true to do eval of T part of expression */
   __emit_jmp(t_bbp);
  }
 else 
  {
   /* AIV 09/09/08 - still need to check b part is 0 here */
   is_bzero_ti = sel_bpti;
   __emit_jmp_0(qcol_bbp, t_bbp, sel_bpti);
  }

 __start_bblk(qcol_bbp);
 /* check if expr T or F */
 __emit_jmp_0(f_bbp, t_bbp, sel_apti);
 __start_bblk(t_bbp);

 /* expr is T */
 x1_apti = gen_eval_qcol_oper(t_ndp, ndp->has_sign, blen, SR_VEC);

 /* check if b part was set if not assign and go to end otherwise eval F part */
 /* if scalar can only be 1 if true */
 if (is_sel_scalar)
  {
   __emit_jmp_0(t_assign_bbp, f_bbp, is_bzero_ti);
  }
 else
  {
   check_any1_bbp = __alloc_bblk(FALSE);
   __emit_jmp_0(t_assign_bbp, check_any1_bbp, is_bzero_ti);
   __start_bblk(check_any1_bbp);

   /* AIV 01/19/06 - removed convert x1_apti better be converted by here */
   /* AIV 09/10/08 - should check this here - was evaluating false expr */
   /* event if has at least one bit */
   __emit_qcol_jmp_any1(t_assign_bbp, f_bbp, sel_apti, sel_bpti, 
    __get_tnwid(sel_apti));
  }
 __start_bblk(t_assign_bbp);

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*wlen_(blen)*WRDBYTES, x1_apti, res_apti);

 __emit_jmp(after_bbp);
 __start_bblk(f_bbp);

 /* AIV 08/15/06 - need to save a copy of the first expression if a function */
 /* this is needed becuase of 1'bx ? func(val1) : func(val2);  */
 /* both the t/f part must be evaluated but func values are placed */
 /* in one global location so x2_apti replaces the value before x1_apti */
 /* is evaluated so its value must be saved */
 if (t_ndp->optyp == FCALL)
  {
   x1_tmp_apti = __gen_tn(SR_VEC, blen);
   __emit_copy(2*wlen_(blen)*WRDBYTES, x1_apti, x1_tmp_apti);
   x1_apti = x1_tmp_apti;
  }
 x2_apti = gen_eval_qcol_oper(f_ndp, ndp->has_sign, blen, SR_VEC);

 /* check if bpart set if so goto lxqcol otherwise assign and jmp to end */
 __emit_jmp_0(f_assign_bbp, bpart_nonzero_bbp, is_bzero_ti);

 __start_bblk(f_assign_bbp);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*wlen_(blen)*WRDBYTES, x2_apti, res_apti);

 __emit_jmp(after_bbp);

 __start_bblk(bpart_nonzero_bbp); 
 /* inside here the jumps to after bblk generated */
 gen_lxqcol_comb(res_apti, blen, x1_apti, x2_apti);

 __start_bblk(after_bbp);
 if (ndp->has_sign) __tntab[res_apti].t_signed = TRUE;
 return(res_apti);
}

/*
 * simple 2-state qcol
 */
static int32 gen_qcol_2state(struct expr_t *ndp, int32 sel_apti)
{
 int32 res_apti, x1_apti, x1_tmp_apti, x2_apti, blen, srtyp;
 struct expr_t *t_ndp;
 struct bblk_t *t_bbp, *f_bbp, *after_bbp;

 blen = ndp->szu.xclen;
 /* AIV 09/02/08 - if all widths of qcol are 1 do as scalar op */
 t_ndp = ndp->ru.x->lu.x;

 if (__is_constant(sel_apti)) 
  {
   return(gen_qcol_const(sel_apti, ndp));
  }
 
 if (blen == 1 && ndp->lu.x->szu.xclen == 1 
     && ndp->ru.x->lu.x->szu.xclen == 1)
  {
   srtyp = SR_SCAL2S;
  }
 else srtyp = SR_BIT2S;

 res_apti = __gen_tn(srtyp, blen);
 /* all conditional results copied into this */
 t_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* SJM 10/24/04 - LOOKATME? insn for signs should be inserted but should */
 /* not cause any machine insns to be generated */
 /* check if expr T or F */
 __emit_jmp_0(f_bbp, t_bbp, sel_apti);

 /* expr is T */
 __start_bblk(t_bbp);
 x1_apti = gen_eval_qcol_oper(ndp->ru.x->lu.x, ndp->has_sign, blen, srtyp);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(wlen_(blen)*WRDBYTES, x1_apti, res_apti);
 __emit_jmp(after_bbp);

 __start_bblk(f_bbp);
 if (t_ndp->optyp == FCALL)
  {
   x1_tmp_apti = __gen_tn(srtyp, blen);
   __emit_copy(wlen_(blen)*WRDBYTES, x1_apti, x1_tmp_apti);
  }
 x2_apti = gen_eval_qcol_oper(ndp->ru.x->ru.x, ndp->has_sign, blen, srtyp);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(wlen_(blen)*WRDBYTES, x2_apti, res_apti);
 __emit_jmp(after_bbp);

 __start_bblk(after_bbp);

 if (ndp->has_sign) __tntab[res_apti].t_signed = TRUE;
 return(res_apti);
}

/*
 * generate code for ?: where the selector is a known constant
 */
static int32 gen_qcol_const(int32 sel_apti, struct expr_t *ndp)
{
 int32 sel_bpti, res_apti, x1_apti, x2_apti, blen, wlen, wi, ndx;
 word32 av, bv, sval, srtyp; 
 word32 *wp, *wbp;

 blen = __get_tnwid(sel_apti);
 /* if scalar use the scalar value if it is scalar - otherwise turn the */
 /* constant value into a scalar value */
 srtyp = __tntab[sel_apti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   sval = __get_wrd_con_val(sel_apti);
  }
 else if (blen <= WBITS)
  {
   av = __get_wrd_con_val(sel_apti);
   sel_bpti = __get_bpti(sel_apti);
   bv = __get_wrd_con_val(sel_bpti);
   /* if any 1 eval true, if bval comb, otherwise 0 */
   if ((av & ~bv) != 0) sval = 1;
   else if (bv != 0) sval = 2;
   else sval = 0;
  }
 else
  {
   wlen = wlen_(blen);
   ndx = __get_con_adradd_xvi(sel_apti);
   wp = &(__contab[ndx]);
   wbp = &(wp[wlen]);
   sval = -1;
   /* check for any one when true */
   for (wi = 0; wi < wlen; wi++)
    { 
     if ((wp[wi] & ~wbp[wi]) != 0)
      {
       sval = 1;
       break;
      }
    }
   /* if not true then either combine or false */
   if (sval != 1)
    {
     if (!vval_is0_(wbp, blen))
      {
       sval = 2;
      }
     else sval = 0;
    }
  }

 blen = ndp->szu.xclen;
 res_apti = -1;
 switch (sval) {
  case 0: 
   /* FALSE */
   res_apti = gen_eval_qcol_oper(ndp->ru.x->ru.x, ndp->has_sign, blen, SR_VEC);
   break;
  case 1: 
   /* TRUE */
   res_apti = gen_eval_qcol_oper(ndp->ru.x->lu.x, ndp->has_sign, blen, SR_VEC);
   break;
  /* x/z */
  case 2: 
  case 3: 
   res_apti = __gen_tn(SR_VEC, blen);
   /* TRUE */
   x1_apti = gen_eval_qcol_oper(ndp->ru.x->lu.x, ndp->has_sign, blen, SR_VEC);
   x2_apti = gen_eval_qcol_oper(ndp->ru.x->ru.x, ndp->has_sign, blen, SR_VEC);
   gen_lxqcol_comb(res_apti, blen, x1_apti, x2_apti);
  break;
  default: __case_terr(__FILE__, __LINE__); break;
 }

 if (ndp->has_sign) __tntab[res_apti].t_signed = TRUE;
 return(res_apti); 
}
   
/*
 * evaluate a qcol operand 
 * - evaluate, save sign, and convert if need be
 * - need to routine now because of multiple calls
 */
static int32 gen_eval_qcol_oper(struct expr_t *ndp, int32 has_sign, int32 blen,
 int32 srtyp)
{
 int32 t1_ti, tmp_ti, save_sign, want_a_vec;

 want_a_vec = (srtyp == SR_VEC || srtyp == SR_BIT2S) ? WANT_A_VEC : -1;
 t1_ti = __gen_expr_eval(ndp, want_a_vec);
 /* AIV 12/28/06 - special case need to force sign extend for sign xtnd */
 if (has_sign)
  {
   /* save sign call convert and put sign bit back */
   save_sign = __tntab[t1_ti].t_signed;
   __tntab[t1_ti].t_signed = TRUE;
   tmp_ti = __gen_cnvt_srep_ifneeded(t1_ti, srtyp, blen, TRUE, FALSE, FALSE);
   __tntab[t1_ti].t_signed = save_sign;
    t1_ti = tmp_ti;
  }
 else
  { 
   t1_ti = __gen_cnvt_srep_ifneeded(t1_ti, srtyp, blen, FALSE, FALSE, FALSE);
  }
 return(t1_ti);
}

/*
 * if all widths are 1 do qcol as scalar operation 
 * with only leaf expressions for t/f
 */
static int32 gen_scalar_qcol_leaf(struct expr_t *ndp, int32 sel_apti)
{
 int32 res_ti, x1_apti, x2_apti, cint_ti;
 int32 t1_ti, t2_ti, t3_ti, ndx_ti, amtyp, sel_bpti; 
 word32 sval;
 struct bblk_t *t_bbp, *f_bbp, *after_bbp, *non_xz_bbp, *xz_bbp;

 /* eval select */
 res_ti = __gen_tn(SR_SCAL, 1);
 sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_SCAL, 1, FALSE, FALSE, FALSE);
 /* AIV 09/09/08 - if select value is constant just eval according to val */
 if (__is_constant(sel_apti)) 
  {
   sval = __get_wrd_con_val(sel_apti);
   switch (sval) {
    case 0: 
     /* FALSE */
     x2_apti = __gen_expr_eval(ndp->ru.x->ru.x, -1);
     res_ti = __gen_cnvt_srep_ifneeded(x2_apti, SR_SCAL, 1, FALSE, FALSE, 
      FALSE);
     break;
    case 1: 
     /* TRUE */
     x1_apti = __gen_expr_eval(ndp->ru.x->lu.x, -1);
     res_ti = __gen_cnvt_srep_ifneeded(x1_apti, SR_SCAL, 1, FALSE, FALSE, 
      FALSE);
     break;
     /* x/z */
    case 2: 
    case 3: 
     x2_apti = __gen_expr_eval(ndp->ru.x->ru.x, -1);
     x2_apti = __gen_cnvt_srep_ifneeded(x2_apti, SR_SCAL, 1, FALSE, FALSE, 
      FALSE);

     /* get the index op1 | (op2 << 2) */
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, x2_apti);
     x1_apti = __gen_expr_eval(ndp->ru.x->lu.x, -1);
     x1_apti = __gen_cnvt_srep_ifneeded(x1_apti, SR_SCAL, 1, FALSE, FALSE, 
      FALSE);
     t2_ti = __emit_bin_bitor(WBITS, x1_apti, t1_ti);
     /* this operation is now just stored in scalar table */
     /* resbp[0] = xsp2->bp[0] | xsp1->bp[0] | (xsp2->ap[0] ^ xsp1->ap[0]); */
     /* resap[0] = resbp[0] | xsp1->ap[0]; */
     if (__tntab[t2_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
     else amtyp = AM_REG;
     ndx_ti = __move_insn(TN_VAL, I_MOVA, amtyp, t2_ti);
     res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, 
       AM_NLO_ARRNDX, ndx_ti, NLO_QCOL_COMB);
     break;
     default: __case_terr(__FILE__, __LINE__); break;
    }
   return(res_ti); 
  }

 t_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 non_xz_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 after_bbp = __alloc_bblk(FALSE);
 

 cint_ti = __gen_cint_tn(1);
 sel_bpti = __emit_shiftr(WBITS, cint_ti, sel_apti);

 __emit_jmp_0(non_xz_bbp, xz_bbp, sel_bpti);
 /* has x/z must evaluate both */
 __start_bblk(xz_bbp);
 x2_apti = __gen_expr_eval(ndp->ru.x->ru.x, -1);
 x2_apti = __gen_cnvt_srep_ifneeded(x2_apti, SR_SCAL, 1, FALSE, FALSE, FALSE);

 /* get the index op1 | (op2 << 2) */
 cint_ti = __gen_cint_tn(2);
 t1_ti = __emit_shiftl(WBITS, cint_ti, x2_apti);
 x1_apti = __gen_expr_eval(ndp->ru.x->lu.x, -1);
 x1_apti = __gen_cnvt_srep_ifneeded(x1_apti, SR_SCAL, 1, FALSE, FALSE, FALSE);
 t2_ti = __emit_bin_bitor(WBITS, x1_apti, t1_ti);
 /* this operation is now just stored in scalar table */
 /* resbp[0] = xsp2->bp[0] | xsp1->bp[0] | (xsp2->ap[0] ^ xsp1->ap[0]); */
 /* resap[0] = resbp[0] | xsp1->ap[0]; */
 if (__tntab[t2_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
 else amtyp = AM_REG;
 ndx_ti = __move_insn(TN_VAL, I_MOVA, amtyp, t2_ti);
 t3_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, 
    AM_NLO_ARRNDX, ndx_ti, NLO_QCOL_COMB);
 __emit_copy(WRDBYTES, t3_ti, res_ti);

 __emit_jmp(after_bbp);

 __start_bblk(non_xz_bbp);
 cint_ti = __gen_cint_tn(1);
 __emit_jmp_eq(t_bbp, f_bbp, cint_ti, sel_apti);

 /* expr is T */
 __start_bblk(t_bbp);
 x1_apti = __gen_expr_eval(ndp->ru.x->lu.x, -1);
 x1_apti = __gen_cnvt_srep_ifneeded(x1_apti, SR_SCAL, 1, FALSE, FALSE, FALSE);
 __emit_copy(WRDBYTES, x1_apti, res_ti);
 __emit_jmp(after_bbp);

 /* expr is F */
 __start_bblk(f_bbp);
 x2_apti = __gen_expr_eval(ndp->ru.x->ru.x, -1);
 x2_apti = __gen_cnvt_srep_ifneeded(x2_apti, SR_SCAL, 1, FALSE, FALSE, FALSE);
 __emit_copy(WRDBYTES, x2_apti, res_ti);
 __emit_jmp(after_bbp);

 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * if all widths are 1 do qcol as scalar operation non-leaf exprs
 * AIV 11/12/09 - this had the same problem for complex nested ?: 
 * changed this scalar version to only eval t/f once
 */
static int32 gen_scalar_qcol(struct expr_t *ndp, int32 sel_apti)
{
 int32 res_ti, x1_apti, x2_apti, cint_ti;
 int32 t1_ti, t2_ti, t3_ti, ndx_ti, amtyp, sel_bpti; 
 word32 sval;
 struct bblk_t *t_bbp, *f_bbp, *after_bbp, *qcol_bbp, *xz_bbp;

 /* eval select */
 res_ti = __gen_tn(SR_SCAL, 1);
 sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_SCAL, 1, FALSE, FALSE, FALSE);
 /* AIV 09/09/08 - if select value is constant just eval according to val */
 if (__is_constant(sel_apti)) 
  {
   sval = __get_wrd_con_val(sel_apti);
   switch (sval) {
    case 0: 
     /* FALSE */
     x2_apti = __gen_expr_eval(ndp->ru.x->ru.x, -1);
     res_ti = __gen_cnvt_srep_ifneeded(x2_apti, SR_SCAL, 1, FALSE, FALSE, 
      FALSE);
     break;
    case 1: 
     /* TRUE */
     x1_apti = __gen_expr_eval(ndp->ru.x->lu.x, -1);
     res_ti = __gen_cnvt_srep_ifneeded(x1_apti, SR_SCAL, 1, FALSE, FALSE, 
      FALSE);
     break;
     /* x/z */
    case 2: 
    case 3: 
     x2_apti = __gen_expr_eval(ndp->ru.x->ru.x, -1);
     x2_apti = __gen_cnvt_srep_ifneeded(x2_apti, SR_SCAL, 1, FALSE, FALSE, 
      FALSE);

     /* get the index op1 | (op2 << 2) */
     cint_ti = __gen_cint_tn(2);
     t1_ti = __emit_shiftl(WBITS, cint_ti, x2_apti);
     x1_apti = __gen_expr_eval(ndp->ru.x->lu.x, -1);
     x1_apti = __gen_cnvt_srep_ifneeded(x1_apti, SR_SCAL, 1, FALSE, FALSE, 
      FALSE);
     t2_ti = __emit_bin_bitor(WBITS, x1_apti, t1_ti);
     /* this operation is now just stored in scalar table */
     /* resbp[0] = xsp2->bp[0] | xsp1->bp[0] | (xsp2->ap[0] ^ xsp1->ap[0]); */
     /* resap[0] = resbp[0] | xsp1->ap[0]; */
     if (__tntab[t2_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
     else amtyp = AM_REG;
     ndx_ti = __move_insn(TN_VAL, I_MOVA, amtyp, t2_ti);
     res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, 
       AM_NLO_ARRNDX, ndx_ti, NLO_QCOL_COMB);
     break;
     default: __case_terr(__FILE__, __LINE__); break;
    }
   return(res_ti); 
  }

 t_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 qcol_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 after_bbp = __alloc_bblk(FALSE);

 /*
  * if (sel_b) eval t 
  * check if selb 0 again if T done
  * else execute F check selb combine  if not 0
  */
 
 cint_ti = __gen_cint_tn(1);
 sel_bpti = __emit_shiftr(WBITS, cint_ti, sel_apti);

 __emit_jmp_0(qcol_bbp, t_bbp, sel_bpti);

 __start_bblk(qcol_bbp);
 cint_ti = __gen_cint_tn(1);
 __emit_jmp_eq(t_bbp, f_bbp, cint_ti, sel_apti);

 /* expr is T */
 __start_bblk(t_bbp);
 x1_apti = __gen_expr_eval(ndp->ru.x->lu.x, -1);
 x1_apti = __gen_cnvt_srep_ifneeded(x1_apti, SR_SCAL, 1, FALSE, FALSE, FALSE);

 /* assume T assign and double check bpart */
 __emit_copy(WRDBYTES, x1_apti, res_ti);
 __emit_jmp_0(after_bbp, f_bbp, sel_bpti);

 /* expr is F */
 __start_bblk(f_bbp);
 x2_apti = __gen_expr_eval(ndp->ru.x->ru.x, -1);
 x2_apti = __gen_cnvt_srep_ifneeded(x2_apti, SR_SCAL, 1, FALSE, FALSE, FALSE);
 __emit_copy(WRDBYTES, x2_apti, res_ti);
 __emit_jmp_0(after_bbp, xz_bbp, sel_bpti);

 /* has x/z must evaluate both */
 __start_bblk(xz_bbp);
 /* get the index op1 | (op2 << 2) */
 cint_ti = __gen_cint_tn(2);
 t1_ti = __emit_shiftl(WBITS, cint_ti, x2_apti);
 t2_ti = __emit_bin_bitor(WBITS, x1_apti, t1_ti);
 /* this operation is now just stored in scalar table */
 /* resbp[0] = xsp2->bp[0] | xsp1->bp[0] | (xsp2->ap[0] ^ xsp1->ap[0]); */
 /* resap[0] = resbp[0] | xsp1->ap[0]; */
 if (__tntab[t2_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
 else amtyp = AM_REG;
 ndx_ti = __move_insn(TN_VAL, I_MOVA, amtyp, t2_ti);
 t3_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, 
    AM_NLO_ARRNDX, ndx_ti, NLO_QCOL_COMB);
 __emit_copy(WRDBYTES, t3_ti, res_ti);
 __emit_jmp(after_bbp);

 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * do the combine for qcol
 * this is for non-true with b part not 0
 */
static void gen_lxqcol_comb(int32 res_apti, int32 opbits, int32 x1_apti, 
 int32 x2_apti)
{
 int32 cbits_apti, cbits_bpti, hghw_cbits_apti, hghw_cbits_bpti;
 int32 ubits, mask_ti, r2_ti, r1_ti, ofs; 
 int32 t1_ti, t2_ti, t3_ti, t4_ti, x1_bpti, x2_bpti, res_bpti, bval_ti, aval_ti;
 word32 mask;

 /* AIV 06/26/08 - put in the handling for the narrow case */
 mask_ti = -1;
 ubits = ubits_(opbits);
 mask = __masktab[ubits];
 if (opbits <= WBITS)
  {
   /* resbp[0] = xsp2->bp[0] | xsp1->bp[0] | (xsp2->ap[0] ^ xsp1->ap[0]); */
   t1_ti = __emit_bin_bitxor(WBITS, x1_apti, x2_apti);
   x1_bpti = __get_bpti(x1_apti);
   x2_bpti = __get_bpti(x2_apti);
   t2_ti = __emit_bin_bitor(WBITS, x1_bpti, x2_bpti); 
   t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti); 
   /* resap[0] = resbp[0] | xsp1->ap[0]; */
   t4_ti = __emit_bin_bitor(WBITS, t3_ti, x1_apti); 
   if (ubits != 0)
    {
     mask_ti = __gen_cint_tn(mask);
     bval_ti = __emit_mask_and(t3_ti, mask_ti);
    }
   else bval_ti = t3_ti;

   res_bpti = __get_bpti(res_apti);
   __emit_copy(WRDBYTES, bval_ti, res_bpti);
   if (ubits != 0)
    {
     aval_ti = __emit_mask_and(t4_ti, mask_ti);
    }
   else aval_ti = t4_ti;

   __emit_copy(WRDBYTES, aval_ti, res_apti);
  }
 else 
  {
   cbits_apti = __emit_qcol_comb_opands(x1_apti, x2_apti, opbits);
   /* AIV 11/28/05 - wasn't masking the high word in the wide case */
   if (ubits != 0)
    {
     cbits_bpti = __get_bpti(cbits_apti);
     ofs = WRDBYTES*(wlen_(opbits) - 1);
     hghw_cbits_apti = __con_adradd_insn(SR_VEC, opbits, cbits_apti, ofs);
     hghw_cbits_bpti = __con_adradd_insn(SR_VEC, opbits, cbits_bpti, ofs);
     mask_ti = __gen_cint_tn(mask);
     r1_ti = __emit_mask_and(hghw_cbits_apti, mask_ti);
     __emit_copy(WRDBYTES, r1_ti, hghw_cbits_apti);
     r2_ti = __emit_mask_and(hghw_cbits_bpti, mask_ti);
     __emit_copy(WRDBYTES, r2_ti, hghw_cbits_bpti);
    }
   __emit_copy(2*wlen_(opbits)*WRDBYTES, cbits_apti, res_apti);
  }
}

/*
 * generate ?: with simple structure 
 * ? t_epxr : f_expr
 * evalutes t/f expr based on x/z 
 */
static int32 gen_qcol_leaf(struct expr_t *ndp, int32 sel_apti)
{
 int32 sel_bpti, res_apti, x1_apti, x2_apti, blen, is_sel_scalar;
 int32 cint_ti, srtyp;
 struct bblk_t *xz_bbp, *t_bbp, *f_bbp, *after_bbp;
 struct bblk_t *non_xz_bbp, *comb_bbp; 

 blen = ndp->szu.xclen;
 xz_bbp = __alloc_bblk(TRUE);
 non_xz_bbp = __alloc_bblk(FALSE);
 t_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* all conditional results copied into this */
 res_apti = __gen_tn(SR_VEC, blen);
 /* SJM 10/24/04 - LOOKATME? insn for signs should be inserted but should */
 /* not cause any machine insns to be generated */
 is_sel_scalar = FALSE;
 srtyp = __tntab[sel_apti].srtyp;
 if (srtyp == SR_SCAL || srtyp == SR_SCAL2S)
  {
   cint_ti = __gen_cint_tn(1);
   sel_bpti = __emit_shiftr(WBITS, cint_ti, sel_apti);
   sel_apti = __emit_bin_bitand(WBITS, cint_ti, sel_apti);
   is_sel_scalar = TRUE;
  }
 else
  {
   sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_VEC, ndp->lu.x->szu.xclen,
    ndp->lu.x->has_sign, FALSE, FALSE);

   sel_bpti = __get_bpti(sel_apti);
  }

 /* holds whether or not bpart is 0 */
 /* only set the word bpart value if wide */
 __emit_jmp_0(non_xz_bbp, xz_bbp, sel_bpti);
 __start_bblk(non_xz_bbp);
 /* check if expr T or F */
 __emit_jmp_0(f_bbp, t_bbp, sel_apti);

 /* expr is T */
 __start_bblk(t_bbp);
 x1_apti = gen_eval_qcol_oper(ndp->ru.x->lu.x, ndp->has_sign, blen, SR_VEC);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*wlen_(blen)*WRDBYTES, x1_apti, res_apti);
 __emit_jmp(after_bbp);

 __start_bblk(f_bbp);
 x2_apti = gen_eval_qcol_oper(ndp->ru.x->ru.x, ndp->has_sign, blen, SR_VEC);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*wlen_(blen)*WRDBYTES, x2_apti, res_apti);
 __emit_jmp(after_bbp);

 __start_bblk(xz_bbp); 
 x1_apti = gen_eval_qcol_oper(ndp->ru.x->lu.x, ndp->has_sign, blen, SR_VEC);
 /* if scalar no it cannot have a one - otherwise need to check */
 /* if value has any 1 bit - if so the result is true */
 if (!is_sel_scalar)
  {
   /* if has any one bit jump to assign true */
   comb_bbp = __alloc_bblk(FALSE);
   __emit_qcol_jmp_any1(t_bbp, comb_bbp, sel_apti, sel_bpti, 
    __get_tnwid(sel_apti));
   __start_bblk(comb_bbp);
  }
 x2_apti = gen_eval_qcol_oper(ndp->ru.x->ru.x, ndp->has_sign, blen, SR_VEC);
 /* inside here the jumps to after bblk generated */
 gen_lxqcol_comb(res_apti, blen, x1_apti, x2_apti);

 __start_bblk(after_bbp);

 if (ndp->has_sign) __tntab[res_apti].t_signed = TRUE;
 return(res_apti);
}


/*
 * gen insns to eval real select ?: and return pr tmp index
 *
 * different insn gen code because real select can't be x/z
 * : opands can be real or not real
 */
static int32 gen_realselqcol(struct expr_t *ndp)
{
 int32 blen, sel_apti, x1_apti, res_apti, x2_apti;
 struct bblk_t *f_bbp, *t_bbp, *after_bbp;
 struct expr_t *xp;

 f_bbp = __alloc_bblk(FALSE);
 t_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* all of the various conditional results copied into this */
 /* because must return only one pr tmp location */
 blen = ndp->szu.xclen;
 res_apti = __gen_tn(SR_VEC, blen);

 sel_apti = __gen_expr_eval(ndp->lu.x, -1);
 __emit_jmp_real0(f_bbp, t_bbp, sel_apti);

 /* T case */
 __start_bblk(t_bbp);

 xp = ndp->ru.x->lu.x;
 /* AIV 11/10/09 - want a vector here */
 x1_apti = __gen_expr_eval(xp, WANT_A_VEC);
 x1_apti = __gen_cnvt_srep_ifneeded(x1_apti, SR_VEC, blen, ndp->has_sign,
  xp->cnvt_to_real, FALSE);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*wlen_(blen)*WRDBYTES, x1_apti, res_apti);
 __emit_jmp(after_bbp);
 
 /* F case */
 __start_bblk(f_bbp);

 xp = ndp->ru.x->ru.x;
 /* AIV 11/10/09 - want a vector here */
 x2_apti = __gen_expr_eval(xp, WANT_A_VEC);
 x2_apti = __gen_cnvt_srep_ifneeded(x2_apti, SR_VEC, blen, ndp->has_sign, 
  xp->cnvt_to_real, FALSE);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*wlen_(blen)*WRDBYTES, x2_apti, res_apti);

 __start_bblk(after_bbp);
 return(res_apti);
}

/*
 * eval regreal ?: - condition reg but : operands and therefore result real
 * 
 * different because no combining of x/z needed 
 */
static int32 gen_regrealqcol(struct expr_t *ndp)
{
 int32 sel_apti, sel_bpti, res_apti, x1_apti, x2_apti, blen;
 int32 xvi, zero_ti;
 struct bblk_t *xz_bbp, *qcol_bbp, *t_bbp, *f_bbp, *after_bbp;
 double d0;
 word32 dtmp[2];
 struct expr_t *xp;

 xz_bbp = __alloc_bblk(TRUE);
 t_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 qcol_bbp = __alloc_bblk(FALSE);

 /* all conditional results copied into this */
 blen = ndp->szu.xclen;
 res_apti = __gen_tn(SR_VEC, blen);
 __tntab[res_apti].t_real = TRUE;
 __tntab[res_apti].tn_used_wide = TRUE;

 /* AIV 11/10/09 - want a vector here */
 sel_apti = __gen_expr_eval(ndp->lu.x, WANT_A_VEC);
 sel_apti = __gen_cnvt_srep_ifneeded(sel_apti, SR_VEC, ndp->lu.x->szu.xclen,
  ndp->lu.x->has_sign, FALSE, FALSE);
 sel_bpti = __get_bpti(sel_apti);

 __emit_jmp_0(qcol_bbp, xz_bbp, sel_bpti);
 __start_bblk(xz_bbp);

 /* AIV 02/03/11 - this code was bad it was producing a tmp of 0 */
 /* and converting it to a real.  Just create the 2-word tmp at compile */
 /* time and store the value */
 /* AIV 08/18/11 - if +realwarns on print this message as well */
 if (__real_warns) 
  {
   __emit_real_qcol_warning(__generating_stp);
  }
 d0 = 0.0;
 dtmp[0] = 0;
 dtmp[1] = 0;
 memcpy(dtmp, &d0, sizeof(double));
 xvi = __allocfill_cval_new(dtmp, &(dtmp[1]), 1);
 zero_ti = __gen_contab_tn(xvi, WBITS, FALSE, FALSE, FALSE, SR_VEC);
 __emit_copy(2*wlen_(blen)*WRDBYTES, zero_ti, res_apti);
 __emit_jmp(after_bbp);

 __start_bblk(qcol_bbp);

 __emit_jmp_0(f_bbp, t_bbp, sel_apti);
 /* T case */
 __start_bblk(t_bbp);

 xp = ndp->ru.x->lu.x;
 /* AIV 11/10/09 - want a vector here */
 x1_apti = __gen_expr_eval(xp, WANT_A_VEC);
 /* AIV 02/03/11 - these should take xp->sign - not always signed like interp */
 x1_apti = __gen_cnvt_srep_ifneeded(x1_apti, SR_VEC,WBITS, xp->has_sign, TRUE, 
   FALSE);

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*wlen_(blen)*WRDBYTES, x1_apti, res_apti);

 __emit_jmp(after_bbp);
 
 /* F case */
 __start_bblk(f_bbp);

 xp = ndp->ru.x->ru.x;
 x2_apti = __gen_expr_eval(xp, WANT_A_VEC);
 /* AIV 02/03/11 - these should take xp->sign - not always signed like interp */
 x2_apti = __gen_cnvt_srep_ifneeded(x2_apti, SR_VEC,WBITS, xp->has_sign, TRUE, 
   FALSE);
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(2*wlen_(blen)*WRDBYTES, x2_apti, res_apti);
 __start_bblk(after_bbp);
 return(res_apti);
}

/*
 * ROUTINES TO EMIT EVAL OF UNARY OPERATORS INSNS
 */

/*
 * generate insns for unary operators
 *
 * SJM 10/16/04 - notice because eval tmp always go into same formal
 * tmp location - since there are b parts and conditionals - must usually
 * copy result into actual tmp (not searched for in formal tmp table)
 * also needed for binary operations in Verilog
 */
static int32 gen_unop(struct expr_t *ndp)
{
 int32 res_ti, res_bpti, op_ti, blen, srtyp, is_op1_2state; 
 struct bblk_t *after_bbp, *t_bbp, *f_bbp, *op_bbp;

 op_ti = __gen_expr_eval(ndp->lu.x, -1);

 is_op1_2state = (__tmp_is_2state(op_ti) || 
                  __is_constant_with_zero_bpart(op_ti));
 if (is_op1_2state)
  {
   return(gen_unop_2state(ndp));
  }

 /* set the blen size to the width of the result */ 
 if (ndp->szu.xclen <= WBITS) blen = WBITS;
 else blen = ndp->szu.xclen;

 res_ti = -1;

 /* AIV 10/01/08 - can only do this if bit len 1 because of the following */
 /* must widen to lhs size  reg32 = ~scal */
 srtyp = __tntab[op_ti].srtyp;
 /* AIV 08/15/08 - if both operands are scalar just get value from the */ 
 /* pre-computed scalar unary op tables */
 if (ndp->szu.xclen == 1 && (srtyp == SR_SCAL || srtyp == SR_SSCAL))
  {
   res_ti = gen_scalar_unop(ndp->optyp, op_ti);
   return(res_ti);
  }

 /* AIV 11/29/05 - if operand is not a vec must convert */ 
 /* AIV 12/27/07 - BITNOT are handled for the scalar case */
//AIV LOOKAMTE - handle all non-real scalar cases here?????????????
 if (__tntab[op_ti].srtyp != SR_VEC && ndp->optyp != REALMINUS)
  {
   op_ti = __gen_cnvt_srep_ifneeded(op_ti, SR_VEC, __get_tnwid(op_ti), 
    ndp->has_sign, FALSE, TRUE); 
  }

 switch (ndp->optyp) {
  /* both unary and binary but used as unary here */
  case /* + */ PLUS:
   /* plus removed (no op) before here */
   __misc_terr(__FILE__, __LINE__);
   break;
  case /* - */ MINUS:
   res_ti = __gen_tn(SR_VEC, blen);
   gen_un_minusop(res_ti, op_ti, ndp->szu.xclen, ndp->has_sign, SR_VEC);
   break;
  case /* real - */ REALMINUS:
   /* notice do not need copy since no bblks allocated */
   /* AIV 09/01/05 - need a least one block to do actual op in */
   /* was jumping back to convert code */
   op_bbp = __alloc_bblk(FALSE);
   __start_bblk(op_bbp);
   res_ti = __emit_realneg(op_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   return(res_ti);
  case /* ~ */ BITNOT:
   op_ti = __gen_cnvt_srep_ifneeded(op_ti, SR_VEC, blen, ndp->has_sign, FALSE,
      TRUE); 
   res_ti = gen_un_bitnot(op_ti, ndp->szu.xclen);
   break;
  /* notice for reduction and logicals - result is always 1 bit */
  case /* logical ! */ NOT:
   res_ti = gen_un_logical_not(op_ti);
   break;
  case /* logical real ! */ REALNOT:
   after_bbp = __alloc_bblk(FALSE);
   t_bbp = __alloc_bblk(FALSE);
   f_bbp = __alloc_bblk(FALSE);

   /* AIV 09/01/05 - need a least one block to do actual op in */
   /* was jumping back to convert code */
   op_bbp = __alloc_bblk(FALSE);
   __start_bblk(op_bbp);
   res_ti = __gen_tn(SR_VEC, blen);
   res_bpti = __get_bpti(res_ti);
   __emit_store_cint(res_bpti, 0, WRDBYTES);

   /* notice this needs to check epsilon range around 0 */
//?AIV - again is order reall f then t?
   __emit_jmp_real0(f_bbp, t_bbp, op_ti);
   __start_bblk(f_bbp);

   __emit_store_cint(res_ti, 1, WRDBYTES);
   __emit_jmp(after_bbp);

   __start_bblk(t_bbp);

   /* not 0 is T so not is F */
   __emit_store_cint(res_ti, 0, WRDBYTES);
   __start_bblk(after_bbp);
   break;
  case /* & */ BITREDAND:
   blen = ndp->lu.x->szu.xclen;
   res_ti = __gen_un_bitred_and(op_ti, blen, FALSE, FALSE);
   break;
  case /* | */ BITREDOR:
   res_ti = __gen_un_bitred_or(op_ti, FALSE, FALSE);
   break;
  case /* ^ */ BITREDXOR: case /* ^~ */ REDXNOR:
   res_ti = __gen_un_bitred_xnor_nor(op_ti, (ndp->optyp == REDXNOR), SR_SCAL);
   break;
  case /* ++ */ INC:
   res_ti = gen_inc_dec(ndp, TRUE, op_ti, TRUE);
   break;
  case /* -- */ DEC:
   res_ti = gen_inc_dec(ndp, FALSE, op_ti, TRUE);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(res_ti);
}

/*
 * 2-state version
 */
static int32 gen_unop_2state(struct expr_t *ndp)
{
 int32 res_ti, op_ti, blen, srtyp, t1_ti, t2_ti, mask_ti;
 struct bblk_t *f_bbp, *t_bbp, *after_bbp;
 word32 mask;

 op_ti = __gen_expr_eval(ndp->lu.x, -1);

 /* set the blen size to the width of the result */ 
 if (ndp->szu.xclen <= WBITS) blen = WBITS;
 else blen = ndp->szu.xclen;

 res_ti = -1;

 srtyp = __tntab[op_ti].srtyp;
 switch (ndp->optyp) {
  /* both unary and binary but used as unary here */
  case /* + */ PLUS:
   /* plus removed (no op) before here */
   __misc_terr(__FILE__, __LINE__);
   break;
  case /* - */ MINUS:
   res_ti = __gen_tn(srtyp, blen);
   gen_un_minusop(res_ti, op_ti, ndp->szu.xclen, ndp->has_sign, srtyp);
   break;
  case /* logical real ! */ REALNOT:
  case /* real - */ REALMINUS:
   __misc_terr(__FILE__, __LINE__);
   break;
  case /* ~ */ BITNOT:
   blen = ndp->szu.xclen;
   if (blen == 1) srtyp = SR_SCAL2S;
   else
    {
     srtyp = SR_BIT2S;
     op_ti = __gen_cnvt_srep_ifneeded(op_ti, SR_BIT2S, blen, ndp->has_sign, 
      FALSE, TRUE); 
    }
   res_ti = __gen_tn(srtyp, ndp->szu.xclen);
   if (blen > WBITS)
    {
     __emit_wid_unbitnot(blen, res_ti, op_ti, TRUE);
    }
   else 
    {
     t1_ti = __emit_bitnot(blen, op_ti); 
     if (ubits_(blen) != 0)
      {
       mask = __masktab[ubits_(blen)];
       mask_ti = __gen_cint_tn(mask);
       t2_ti = __emit_mask_and(mask_ti, t1_ti);
      }
     else t2_ti = t1_ti;
     __emit_copy(WRDBYTES, t2_ti, res_ti);
    }
   break;
  /* notice for reduction and logicals - result is always 1 bit */
  case /* logical ! */ NOT:
   res_ti = __gen_tn(SR_SCAL2S, 1);
   blen = __get_tnwid(op_ti);
   if (blen > WBITS)
    {
     t_bbp = __alloc_bblk(FALSE);
     f_bbp = __alloc_bblk(FALSE);
     after_bbp = __alloc_bblk(FALSE);
     __emit_jmp_0(f_bbp, t_bbp, op_ti);
     __start_bblk(f_bbp);
 
     __emit_store_cint(res_ti, 1, WRDBYTES);
   
     __emit_jmp(after_bbp);

     __start_bblk(t_bbp);
     __emit_store_cint(res_ti, 0, WRDBYTES);
     __emit_jmp(after_bbp);
     __start_bblk(after_bbp);
     break;
    }
   __emit_store_cint(res_ti, 0, WRDBYTES);
   __emit_testl(op_ti);
   __emit_st_sete(CC_JE, res_ti);
   break;
  case /* & */ BITREDAND:
   blen = ndp->lu.x->szu.xclen;
   res_ti = __gen_tn(SR_SCAL2S, 1);
   if (blen > WBITS)
    {
     t_bbp = __alloc_bblk(FALSE);
     after_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 0, WRDBYTES);
     t1_ti = __emit_cmp_widall1(op_ti);
     __emit_jmp_0(after_bbp, t_bbp, t1_ti);
     __start_bblk(t_bbp);
     __emit_store_cint(res_ti, 1, WRDBYTES);
     __start_bblk(after_bbp);
     break;
    }
   mask_ti = __gen_cint_tn(__masktab[ubits_(blen)]);
   __emit_store_cint(res_ti, 0, WRDBYTES);
   __emit_cmp(mask_ti, op_ti);

   __emit_st_sete(CC_JE, res_ti);
   break;
  case /* | */ BITREDOR:
   blen = __get_tnwid(op_ti);
   res_ti = __gen_tn(SR_SCAL2S, 1);
   if (blen > WBITS)
    {
     t_bbp = __alloc_bblk(FALSE);
     after_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 0, WRDBYTES);
     __emit_jmp_0(after_bbp, t_bbp, op_ti);
     __start_bblk(t_bbp);
     __emit_store_cint(res_ti, 1, WRDBYTES);
     __start_bblk(after_bbp);
     break;
    }
   __emit_store_cint(res_ti, 0, WRDBYTES);
   __emit_testl(op_ti);
   /* AIV 01/22/09 - no need for the movzbl high part zero from init above */
   __emit_st_sete(CC_JNE, res_ti);
   break;
  case /* ^ */ BITREDXOR: case /* ^~ */ REDXNOR:
   res_ti = __gen_un_bitred_xnor_nor(op_ti, (ndp->optyp == REDXNOR), SR_SCAL2S);
   break;
  default: __case_terr(__FILE__, __LINE__);
  case /* ++ */ INC:
   res_ti = gen_inc_dec(ndp, TRUE, op_ti, TRUE);
   break;
  case /* -- */ DEC:
   res_ti = gen_inc_dec(ndp, FALSE, op_ti, TRUE);
   break;
 }
 return(res_ti);
}
   
/*
 * AIV 08/15/08 - if doing a unary op of a scalar just load the value from
 * pre-computed 4-byte tables
 */
static int32 gen_scalar_unop(int32 optyp, int32 op_ti)
{
 int32 res_ti, nlotyp, ndx_ti, cint_ti, amtyp;

 /* if strength mask off strength value */
 if (__tntab[op_ti].srtyp == SR_SSCAL)
  {
   cint_ti = __gen_cint_tn(3);
   op_ti = __emit_bin_bitand(WBITS, cint_ti, op_ti);
  }

 /* get the table type */
 nlotyp = -1;
 
 switch (optyp) {
  /* AIV 03/09/09 - these can share scalar table since all the value */
  /* are the same {0, 1, 3, 3}*/
  case /* - */ MINUS: 
  case /* & */ BITREDAND:
  case /* | */ BITREDOR:
  case /* ^ */ BITREDXOR: 
   nlotyp = NLO_UN_P1; 
  break;

  /* AIV 03/09/09 - these can share scalar table since all the value */
  /* are the same {1, 0, 3, 3}*/
  case /* ~ */ BITNOT: 
  case /* logical ! */ NOT: 
  case /* ^~ */ REDXNOR: 
   nlotyp = NLO_UN_P2; 
  break;
  default: __case_terr(__FILE__, __LINE__);
 }
 
 /* ndx_ti must be in a reg if folded and still address must move to reg */
 if (__tntab[op_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
 else amtyp = AM_REG;
 ndx_ti = __move_insn(TN_VAL, I_MOVA, amtyp, op_ti);

 /* load index (value) into a reg and index table */
 res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, 
    AM_NLO_ARRNDX, ndx_ti, nlotyp);
 return(res_ti);
}

static int32 gen_scalar_unop_try(int32 optyp, int32 op_ti)
{
 int32 res_ti,  cint_ti, orval_ti; 
 int32 t1_ti, t2_ti, t3_ti;

 /* if strength mask off strength value */
 if (__tntab[op_ti].srtyp == SR_SSCAL)
  {
   cint_ti = __gen_cint_tn(3);
   op_ti = __emit_bin_bitand(WBITS, cint_ti, op_ti);
  }

 /* get the table type */
 res_ti = -1;
 switch (optyp) {
  case /* - */ MINUS: 
  case /* & */ BITREDAND: 
  case /* | */ BITREDOR: 
  case /* ^ */ BITREDXOR: 
   /* 
    *   if (op_ti == 0) orval_ti = 0;
    *   else orval_ti = 1;
    *   rv = op_ti | orval_ti;
    */
   orval_ti = __gen_tn(SR_SCAL, 1);
   __emit_store_cint(orval_ti, 0, WRDBYTES);
   __emit_testl(op_ti);
   __emit_st_sete(CC_JNE, orval_ti);
   t1_ti = __emit_bin_bitor(WBITS, op_ti, orval_ti); 
   res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, t1_ti);
   return(res_ti);
  /* AIV 01/22/09 - no need for the movzbl high part zero from init above */
  case /* ~ */ BITNOT: 
  case /* logical ! */ NOT: 
  case /* ^~ */ REDXNOR: 
//nlotyp = NLO_SUN_BITXNOR; 
//   nlotyp = NLO_SUN_BITNOT; 
//nlotyp = NLO_SUN_LOGNOT; break;
   /*
    * res_ti = op_ti ^ 3;
    * if (res_ti == 2) res_ti + 1;
    */
    /*
	xorl	$3, %edx
	cmpl	$2, %eax
	sete	%al
	movzbl	%al, %eax
	addl	%eax, %edx
     */
   cint_ti = __gen_cint_tn(1);
   t1_ti = __emit_bin_bitxor(WBITS, cint_ti, op_ti);

   t2_ti = __gen_tn(SR_SCAL, 1);
   __emit_store_cint(t2_ti, 0, WRDBYTES);
   cint_ti = __gen_cint_tn(2);
   __emit_cmp(cint_ti, t1_ti);
   __emit_st_sete(CC_JE, t2_ti);
   t3_ti = __emit_add(WBITS, t1_ti, t2_ti); 
   res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, t3_ti);
   return(res_ti);
  default: __case_terr(__FILE__, __LINE__);
 }
 
 return(res_ti);
}

/*
 * gen unary mins insns
 *
 * know op1 and result same width or will be converted before here
 */
static void gen_un_minusop(int32 res_ti, int32 op_ti, int32 blen, 
 int32 nd_signop, int32 srtyp)
{
 int32 res_bpti, op_bpti, t1_ti, zero_ti, bytsiz, hghw_apti, is_2state;
 int32 r2_ti, mask_ti, r1_ti, ofs; 
 word32 mask;
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp;

 bytsiz = WRDBYTES*(wlen_(blen));

 is_2state = (srtyp == SR_SCAL2S || srtyp == SR_BIT2S);

 after_bbp = NULL;
 res_bpti = -1;
 /* notice do not need the size/type change mov before this test */
 if (!is_2state)
  {
   op_bbp = __alloc_bblk(FALSE);
   xz_bbp = __alloc_bblk(TRUE);
   after_bbp = __alloc_bblk(FALSE);

   res_bpti = __get_bpti(res_ti);
   op_bpti = __get_bpti(op_ti);
   __emit_jmp_0(op_bbp, xz_bbp, op_bpti);

   __start_bblk(xz_bbp);
   gen_ab_setx(res_ti, FALSE);

  __emit_jmp(after_bbp);
  __start_bblk(op_bbp);
 }

 /* AIV 09/25/06 - needs to do sign conversion if needed */
 op_ti = __gen_cnvt_srep_ifneeded(op_ti, srtyp, blen, nd_signop, FALSE,
  FALSE); 

 /* SJM 09/06/04 - this assume b part set to 0 in result */  
 zero_ti = __gen_tn(SR_VEC, blen);
 /* set a part only to 0 */
 __emit_store_cint(zero_ti, 0, wlen_(blen)*WRDBYTES);

 t1_ti = __emit_sub(blen, zero_ti, op_ti);
 /* mask just the a part */
 if (ubits_(blen) != 0)
  {
   mask = __masktab[ubits_(blen)];
   mask_ti = __gen_cint_tn(mask);
   if (wlen_(blen) == 1)
    {
//AIV? - this does need copy?
     r1_ti = __emit_mask_and(t1_ti, mask_ti);
     __emit_copy(WRDBYTES, r1_ti, t1_ti);
    }
   else
    {
     ofs = WRDBYTES*(wlen_(blen) - 1);
     hghw_apti = __con_adradd_insn(SR_VEC, blen, t1_ti, ofs);
     r2_ti = __emit_mask_and(hghw_apti, mask_ti);
     __emit_copy(WRDBYTES, r2_ti, hghw_apti);
    } 
  }
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(bytsiz, t1_ti, res_ti);
 if (!is_2state)
  {
   __emit_store_cint(res_bpti, 0, bytsiz);
   __start_bblk(after_bbp);
  }
}

/*
 * gen unary bit not insns
 */
static int32 gen_un_bitnot(int32 op_ti, int32 blen)
{
 int32 op_bpti, res_ti, res_bpti, t1_ti, t2_ti, mask_ti; 
 int32 t3_apti, t3_bpti;
 word32 mask;

 /* AIV currently can't decompose wide case because it has internal loop */
 op_bpti = __get_bpti(op_ti);
 res_ti = __gen_tn(SR_VEC, blen);
 if (blen > WBITS)
  {
   __emit_wid_unbitnot(blen, res_ti, op_ti, FALSE);
   res_bpti = __get_bpti(res_ti);
   /* b value remains unchanged so must copy b part */
   __emit_copy(wlen_(blen)*WRDBYTES, op_bpti, res_bpti);
   return(res_ti);
  }
 t1_ti = __emit_bitnot(blen, op_ti); 
 t2_ti = __emit_bin_bitor(blen, t1_ti, op_bpti); 

 res_bpti = __get_bpti(res_ti);

 /* SJM 07/18/06 - removed old wide code since can't happen */
 if (ubits_(blen) != 0)
  {
   mask = __masktab[ubits_(blen)];
   mask_ti = __gen_cint_tn(mask);
   t3_apti = __emit_mask_and(t2_ti, mask_ti);
   t3_bpti = __emit_mask_and(op_bpti, mask_ti);
  }
 else
  {
   t3_apti = t2_ti;
   t3_bpti = op_bpti;
  }
 __emit_copy(WRDBYTES, t3_apti, res_ti);
 __emit_copy(WRDBYTES, t3_bpti, res_bpti);
 return(res_ti);
}

/*
 * gen unary mins insns
 * unary logical not always produces a 1 bit result
 */
static int32 gen_un_logical_not(int32 op_ti)
{
 int32 op_bpti, res_ti, tnwid; 
 struct bblk_t *op_bbp, *xz_bbp;
 
 tnwid = __get_tnwid(op_ti);
 if (tnwid > WBITS)
  {
   return(gen_un_logical_not_wide(op_ti));
  }

 /* notice do not need the size/type change mov before this test */
 op_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(FALSE);

 
 res_ti = __gen_tn(SR_SCAL, 1);
 __emit_store_cint(res_ti, 3, WRDBYTES);

 op_bpti = __get_bpti(op_ti);
 __emit_jmp_0(op_bbp, xz_bbp, op_bpti);
 __start_bblk(op_bbp);

 __emit_testl(op_ti);

 /* AIV 01/22/09 - no need for the movzbl high part zero from init above */
 __emit_st_sete(CC_JE, res_ti);

 __emit_jmp(xz_bbp);
 __start_bblk(xz_bbp);
 return(res_ti);
}

/*
 * gen unary mins insns for wide op1
 */
static int32 gen_un_logical_not_wide(int32 op_ti)
{
 int32 op_bpti, res_ti; 
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp, *t_bbp, *f_bbp;

 /* notice do not need the size/type change mov before this test */
 op_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 t_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 res_ti = __gen_tn(SR_SCAL, 1);
 op_bpti = __get_bpti(op_ti);

 __emit_jmp_0(op_bbp, xz_bbp, op_bpti);
 __start_bblk(op_bbp);

 __emit_jmp_0(f_bbp, t_bbp, op_ti);
 __start_bblk(f_bbp);
 
 /* SJM 02/13/05 - maybe better to use a move since this does not go */
 /* into formal tmp tab */
 __emit_store_cint(res_ti, 1, WRDBYTES);
   
 __emit_jmp(after_bbp);

 __start_bblk(t_bbp);
 /* not of T (0) is F */
 __emit_store_cint(res_ti, 0, WRDBYTES);
 __emit_jmp(after_bbp);

 __start_bblk(xz_bbp);
 __emit_store_cint(res_ti, 3, WRDBYTES);
 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen unary bit red and
 */
extern int32 __gen_un_bitred_and(int32 op_apti, int32 blen, int32 nd_invert,
 int32 is_gate_op)
{
 int32 res_ti, op_bpti, t1_ti, cint_ti, need_xprop; 
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp, *set_bbp; 

 /* AIV 08/03/11 - if xprop need to use set to x values table */
 /* do not prop gate operation or nand (invert) */
#ifdef __XPROP__
 need_xprop = (__inst_mod->m_use_xprop_and_or_x && !is_gate_op && !nd_invert);
#else
 need_xprop = FALSE;
#endif
 if (blen > WBITS) 
  {
   return(gen_un_bitred_and_wide(op_apti, blen, nd_invert, need_xprop));
  }

 xz_bbp = NULL;
 after_bbp = __alloc_bblk(FALSE);
 op_bbp = __alloc_bblk(FALSE);

 op_bpti = __get_bpti(op_apti);
 res_ti = __gen_tn(SR_SCAL, 1);
  __emit_store_cint(res_ti, 3, WRDBYTES);
 /* if b part zero, 0 if any 0, else 1 */
 /* if xprop init to x just go to done */
 if (need_xprop) __emit_jmp_0(op_bbp, after_bbp, op_bpti);
 else 
  {
   xz_bbp = __alloc_bblk(TRUE);
   __emit_jmp_0(op_bbp, xz_bbp, op_bpti);
  }

 __start_bblk(op_bbp);

 cint_ti = __gen_cint_tn(__masktab[ubits_(blen)]);
 __emit_cmp(cint_ti, op_apti);
 /* AIV 01/22/09 - no need for the movzbl high part zero from init above */
 if (nd_invert) __emit_st_sete(CC_JNE, res_ti);
 else __emit_st_sete(CC_JE, res_ti);

 __emit_jmp(after_bbp);

 if (!need_xprop)
  {
   /* b part has some x/z bits - or to see if any actual 0's */
   __start_bblk(xz_bbp);
 
   set_bbp = __alloc_bblk(FALSE);
   t1_ti = __emit_bin_bitor(blen, op_apti, op_bpti);
   __emit_jmp_cmp(after_bbp, set_bbp, t1_ti, cint_ti, CC_JE);

   /* if any 0 from or of a and b parts, result 0, else result x */
   __start_bblk(set_bbp);
   if (nd_invert) __emit_store_cint(res_ti, 1, WRDBYTES);
   else __emit_store_cint(res_ti, 0, WRDBYTES);
   __emit_jmp(after_bbp);
  }

 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen unary wide bit red and
 */
static int32 gen_un_bitred_and_wide(int32 op_apti, int32 blen, int32 nd_invert,
 int32 need_xprop)
{
 int32 res_ti, op_bpti, t1_ti, cond_ti, cond2_ti; 
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp;
 struct bblk_t *one_bbp, *zero_bbp, *setxz_bbp;

#ifdef __XPROP__
 need_xprop = __inst_mod->m_use_xprop_and_or_x;
#else
 need_xprop = FALSE;
#endif
 res_ti = __gen_tn(SR_SCAL, 1);
 one_bbp = __alloc_bblk(FALSE);
 zero_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 op_bbp = __alloc_bblk(FALSE);
 if (!need_xprop) setxz_bbp = __alloc_bblk(TRUE);
 else setxz_bbp = NULL;

 op_bpti = __get_bpti(op_apti);

 /* if b part zero, 0 if any 0, else 1 */
 __emit_jmp_0(op_bbp, xz_bbp, op_bpti);
 __start_bblk(op_bbp);

 cond_ti = __emit_cmp_widall1(op_apti);
 __emit_jmp_0(zero_bbp, one_bbp, cond_ti);
 __start_bblk(one_bbp);
 if (nd_invert)
  {
   /* for logic gate eval, need nand (inverted) gate - no expr operator */
   __emit_store_cint(res_ti, 0, WRDBYTES);
  }
 else
  {
   /* store value 1 */
   __emit_store_cint(res_ti, 1, WRDBYTES);
  }
 __emit_jmp(after_bbp);

 __start_bblk(zero_bbp);
 if (nd_invert)
  {
   /* store value 1 */
   __emit_store_cint(res_ti, 1, WRDBYTES);
  }
 else
  {
   __emit_store_cint(res_ti, 0, WRDBYTES);
  }
 __emit_jmp(after_bbp);

 /* b part has some x/z bits - or to see if any actual 0's */
 __start_bblk(xz_bbp);
 
 /* AIV 08/03/11 - if xz and xprop just set to x */
 if (need_xprop)
  {
   __emit_store_cint(res_ti, 3, WRDBYTES);
   __start_bblk(after_bbp);
   return(res_ti);
  }
 t1_ti = __emit_bin_bitor(blen, op_apti, op_bpti);

 /* if any 0 from or of a and b parts, result 0, else result x */
 cond2_ti = __emit_cmp_widall1(t1_ti);
 __emit_jmp_0(zero_bbp, setxz_bbp, cond2_ti);

 __start_bblk(setxz_bbp);
 /* set to a single x and zero the high a/b part */
 /* maybe make into a routine */
 __emit_store_cint(res_ti, 3, WRDBYTES);
 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen unary bit red or 
 */
extern int32 __gen_un_bitred_or(int32 op_ti, int32 nd_invert, int32 is_gate_op)
{
 int32 res_ti, op_bpti, t1_ti, t2_ti, blen, need_xprop; 
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp, *set_bbp;

 blen = __get_tnwid(op_ti);
 /* AIV currently can't decompose wide case because it has internal loop */
 /* AIV 08/03/11 - if xprop need to use set to x values table */
 /* do not prop gate operation or nand (invert) */
#ifdef __XPROP__
 need_xprop = (__inst_mod->m_use_xprop_and_or_x && !is_gate_op && !nd_invert);
#else
 need_xprop = FALSE;
#endif

 if (blen > WBITS)
  {
   res_ti = __emit_wid_un_redor(op_ti, blen, need_xprop);
   return(res_ti);
  }

 after_bbp = __alloc_bblk(FALSE);
 op_bbp = __alloc_bblk(FALSE);

 op_bpti = __get_bpti(op_ti);

 res_ti = __gen_tn(SR_SCAL, 1);
 __emit_store_cint(res_ti, 3, WRDBYTES);

 xz_bbp = set_bbp = NULL;
 /* if xprop init to x just go to done */
 if (need_xprop) __emit_jmp_0(op_bbp, after_bbp, op_bpti);
 else 
  {
   set_bbp = __alloc_bblk(FALSE);
   xz_bbp = __alloc_bblk(TRUE);
   __emit_jmp_0(op_bbp, xz_bbp, op_bpti);
  }

 __start_bblk(op_bbp);

 __emit_testl(op_ti);
 /* AIV 01/22/09 - no need for the movzbl high part zero from init above */
 if (nd_invert) __emit_st_sete(CC_JE, res_ti);
 else __emit_st_sete(CC_JNE, res_ti);

 __emit_jmp(after_bbp);

 if (!need_xprop)
  {
   __start_bblk(xz_bbp);

   t1_ti = __emit_bitnot(blen, op_bpti);
   t2_ti = __emit_bin_bitand(blen, op_ti, t1_ti);

   __emit_jmp_0(after_bbp, set_bbp, t2_ti);
   __start_bblk(set_bbp);
   /* nor - only for logic gates */
   if (nd_invert) __emit_store_cint(res_ti, 0, WRDBYTES);
   else __emit_store_cint(res_ti, 1, WRDBYTES);
   __emit_jmp(after_bbp);
  }

 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen unary bit red xnor or nor
 */
extern int32 __gen_un_bitred_xnor_nor(int32 op_ti, int32 is_xnor, int32 srtyp)
{
 int32 op_bpti, res_ti, tmpres_ti, is_2state; 
 int32 t1_ti, t2_ti, cint_ti, shftamt, opblen;
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp;

 xz_bbp = NULL;
 op_bbp = NULL;
 after_bbp = NULL;

 is_2state = (srtyp == SR_SCAL2S || srtyp == SR_BIT2S);
 res_ti = __gen_tn(srtyp, 1);
 if (!is_2state)
  {
   xz_bbp = __alloc_bblk(TRUE);
   op_bbp = __alloc_bblk(FALSE);
   after_bbp = __alloc_bblk(FALSE);

   op_bpti = __get_bpti(op_ti);
   /* init the result space to 0 */
   __emit_store_cint(res_ti, 0, WRDBYTES);
   __emit_jmp_0(op_bbp, xz_bbp, op_bpti);

   __start_bblk(xz_bbp);
   /* store scalar value for x - 3 */
   __emit_store_cint(res_ti, 3, WRDBYTES);
   __emit_jmp(after_bbp);
   __start_bblk(op_bbp);
  }
 else __emit_store_cint(res_ti, 0, WRDBYTES);

 
 /* either one word32 or for loop wrd redxor call */
 opblen = __get_tnwid(op_ti);
 if (opblen <= WBITS)
  {
   t1_ti = op_ti;
   if (opblen == 1)
    {
     cint_ti = __gen_cint_tn(0);
     tmpres_ti = __emit_bin_bitxor(WBITS, cint_ti, op_ti);
    }
   else
    {
#ifdef __CVC32__
     if (opblen >= 16) shftamt = 16;
#else
     if (opblen >= 32) shftamt = 32;
     else if (opblen >= 16) shftamt = 16;
#endif
     else if (opblen >= 8) shftamt = 8;
     else if (opblen >= 4) shftamt = 4;
     else shftamt = 2;

     for (; ; shftamt = shftamt/2)
      {
       cint_ti = __gen_cint_tn(shftamt);
       t2_ti = __emit_shiftr(WBITS, cint_ti, t1_ti);
       t1_ti = __emit_bin_bitxor(WBITS, t2_ti, t1_ti);
       if (shftamt == 1) break;
      }
     cint_ti = __gen_cint_tn(1);
     tmpres_ti = __emit_bin_bitand(WBITS, cint_ti, t1_ti);
    }
  }
 else tmpres_ti = __emit_uredxor(op_ti);

 if (is_xnor) __emit_lognot(tmpres_ti, res_ti);
 else 
  {
   /* notice copies follow gas movl [from],[to] format */
   /* copy the low word the high is already zero */
   __emit_copy(WRDBYTES, tmpres_ti, res_ti);
  }

 if (!is_2state) __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * ROUTINES TO EMIT EVAL OF BINARY OPERATION INSNS
 */

/*
 * generate insns for binary operators
 */
static int32 gen_binop(struct expr_t *ndp)
{
 int32 op1_ti, op2_ti, nd_signop, res_ti, srtyp1, srtyp2;
 int32 op1_nd_wid, op2_nd_wid, op1_scal_const, op2_scal_const;
 int32 is_op1_2state, is_op2_2state;
 struct bblk_t *op_bbp;

 res_ti = -1;
 /* if expression is string handle string binop */
 /* AIV 11/03/10 - if SV string - just handle as wrapper routine */
 if (ndp->is_sv_string)
  {
   res_ti = __emit_binop_string(ndp);
   res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, AM_REG, res_ti);
   return(res_ti);
  }

 /* AIV 10/27/08 - bool expression may not have to evaluate the rhs */
 /* depending on the value of the first expr - handle these as special cases */
 if (ndp->optyp == BOOLAND)
  {
   return(gen_bin_booland(ndp));
  }
 else if (ndp->optyp == BOOLOR)
  {
   return(gen_bin_boolor(ndp));
  }

 op2_nd_wid = FALSE;
 op1_nd_wid = binop_get_ndwid(&(op2_nd_wid), ndp);

 /* set during checking - result has sign if < WBITS and not 1 bit */
 /* and one or both operaads have sign */
 if (ndp->has_sign || ndp->rel_ndssign) nd_signop = TRUE;
 else nd_signop = FALSE;


 /* AIV 11/10/09 - if blen 1 will try to return a scalar else a vec */
 op1_ti = __gen_expr_eval(ndp->lu.x, ndp->szu.xclen);
 op2_ti = __gen_expr_eval(ndp->ru.x, ndp->szu.xclen);
 /* if it is a SR_BIT2S or SR_SCAL2S or a constant which will be */
 /* converted to a 2-state value - if has no x/z */
//AIV 2STATE - bit2s and real should convert here as well
 is_op1_2state = (__tmp_is_2state(op1_ti) || 
                  __is_constant_with_zero_bpart(op1_ti));
 is_op2_2state = (__tmp_is_2state(op2_ti) || 
                  __is_constant_with_zero_bpart(op2_ti));

 if (is_op1_2state && is_op2_2state)
  {
   res_ti = gen_binop_2state(ndp, op1_ti, op2_ti, op1_nd_wid, op2_nd_wid,
      nd_signop);
   return(res_ti);
  }

 /* AIV 08/25/08 - new convention is to use scalar values whenever */
 /* width is 1 - this is better because of table scalar handling */

 /* AIV 08/15/08 - if both operands are scalar just get value from the */ 
 /* pre-computed scalar binary op tables */
 /* width has to be one for widden context */
 /* AIV 12/29/11 - in the rare case the scalar op is signed cannot use table */
 if (ndp->szu.xclen == 1 && !nd_signop)
  {
   srtyp1 = __tntab[op1_ti].srtyp;
   srtyp2 = __tntab[op2_ti].srtyp;

   /* for width of one and both operands scalar handle as table operation */
   switch (ndp->optyp) {
    case /* << */ SHIFTL: case /* <<< */ ASHIFTL:
    case /* >> */ SHIFTR:
    case /* >>> */ ASHIFTR:
    case /* >= */ RELGE: 
    case /* > */ RELGT: 
    case /* <= */ RELLE:
    case /* < */ RELLT: 
    case /* != */ RELNEQ:
    case /* == */ RELEQ: 
    case /* === */ RELCEQ: 
    case /* !== */ RELCNEQ: 
    case /* && */ BOOLAND: 
    case /* || */ BOOLOR: 
     /* both operands must be scalar for these operations */ 
     if ((srtyp1 == SR_SCAL || srtyp1 == SR_SSCAL) &&
         (srtyp2 == SR_SCAL || srtyp2 == SR_SSCAL))
      {
       res_ti = gen_scalar_binop(ndp->optyp, op1_ti, op2_ti, srtyp1, srtyp2);
       return(res_ti);
      }
     else if (ndp->lu.x->szu.xclen == 1 && ndp->ru.x->szu.xclen == 1)
      {
       res_ti = gen_scalar_binop(ndp->optyp, op1_ti, op2_ti, srtyp1, srtyp2);
       return(res_ti);
      }
     /* AIV 09/16/08 - if one operand scalar see if the other can be */
     /* a constant scalar value and handle as scalar */
     else if (srtyp1 == SR_SCAL || srtyp1 == SR_SSCAL)
      {
       op2_scal_const = gen_try_to_cnvt_scalar_const(op2_ti);
       if (op2_scal_const != -1)
        {
         res_ti = gen_scalar_binop(ndp->optyp, op1_ti, op2_ti, srtyp1, SR_SCAL);
         return(res_ti);
        }
      }
     else if (srtyp2 == SR_SCAL || srtyp2 == SR_SSCAL)
      {
       op1_scal_const = gen_try_to_cnvt_scalar_const(op1_ti);
       if (op1_scal_const != -1)
        {
         res_ti = gen_scalar_binop(ndp->optyp, op1_ti, op2_ti, SR_SCAL, srtyp2);
         return(res_ti);
        }
      }
    break;
   default:
    /* if not real convert to scalar and handle as scalar operation */
    if (!ndp->lu.x->cnvt_to_real && !ndp->lu.x->is_real &&
        !ndp->ru.x->cnvt_to_real && !ndp->ru.x->is_real)
     {
      res_ti = gen_scalar_binop(ndp->optyp, op1_ti, op2_ti, srtyp1, srtyp2);
      return(res_ti);
     }
    break;
   }
  }


 /* this is result operator not operands width */
 switch (ndp->optyp) {
  case /* + */ PLUS:
  case /* - */ MINUS:
  case /* * */ TIMES:
  case /* / */ DIV:
  case /* % */ MOD:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, FALSE, FALSE); 
 
   res_ti = gen_bin_arithop(ndp, op1_ti, op2_ti, nd_signop);
   break;
  case /* + real */ REALPLUS:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   /* AIV 09/01/05 - need a least one block to do actual op in */
   /* was jumping back to convert code */
   op_bbp = __alloc_bblk(FALSE);
   __start_bblk(op_bbp);
   res_ti = __emit_add_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* - real */ REALMINUS:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   op_bbp = __alloc_bblk(FALSE);
   __start_bblk(op_bbp);
   res_ti = __emit_sub_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* * real */ REALTIMES:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   op_bbp = __alloc_bblk(FALSE);
   __start_bblk(op_bbp);
   res_ti = __emit_mult_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* * real */ REALDIV:
   /* SJM 06/17/04 - what happens with divide by 0? - x is 0.0 maybe? */
   /* for now using IEEE floating point result */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   op_bbp = __alloc_bblk(FALSE);
   __start_bblk(op_bbp);
   res_ti = gen_div_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* ** real */ REALPOWER:
   /* AIV 01/10/07 - added real power lowering */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   op_bbp = __alloc_bblk(FALSE);
   __start_bblk(op_bbp);
   res_ti = __emit_power_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* & */ BITREDAND:
   /* AIV 10/13/06 - bitred never have signed - was converting to signed */
   /* AIV 09/29/08 - these need to be sign extend - misread LRM */
   /* see LRM section 5.1.1 */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, FALSE, FALSE); 

   res_ti = gen_bin_bitredand(ndp, op1_ti, op2_ti);
   break;
  case /* | */ BITREDOR:
   /* AIV 09/29/08 - these need to be sign extend - misread LRM */
   /* see LRM section 5.1.1 */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, FALSE, FALSE); 

   res_ti = gen_bin_bitredor(op1_ti, op2_ti);
   break;
  case /* ^ */ BITREDXOR:
   /* AIV 09/29/08 - these need to be sign extend - misread LRM */
   /* see LRM section 5.1.1 */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, FALSE, FALSE); 

   res_ti = gen_bin_bitredxor(ndp, op1_ti, op2_ti);
   break;
  case /* not ^ */ REDXNOR:
   /* can't be just invert xor because need masking if not exactly WBITS */
   /* AIV 09/29/08 - these need to be sign extend - misread LRM */
   /* see LRM section 5.1.1 */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, FALSE, FALSE); 

   res_ti = gen_bin_bitredxnor(ndp, op1_ti, op2_ti);
   break;
  case /* >= */ RELGE:
  case /* > */ RELGT:
  case /* <= */ RELLE:
  case /* < */ RELLT:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, FALSE, FALSE); 
   res_ti = gen_bin_relcomp(ndp, op1_ti, op2_ti, SR_SCAL);
   break;
  case /* >= real */ REALRELGE:
  case /* > real */ REALRELGT:
  case /* <= real */ REALRELLE:
  case /* < real */ REALRELLT:
  case /* == real */ REALRELEQ:
  case /* == real */ REALRELNEQ:
   res_ti = gen_bin_real_relcomp(ndp, op1_ti, op2_ti);
   break;
  case /* != */ RELNEQ:
  case /* == */ RELEQ:
   res_ti = gen_bin_neeq(ndp, op1_ti, op2_ti);
   break;
  case /* === */ RELCEQ:
  case /* !== */ RELCNEQ:
   res_ti = gen_bin_cneeq(ndp, op1_ti, op2_ti);
   break; 
  case /* && */ BOOLAND:
   __case_terr(__FILE__, __LINE__);
   break;
  case /* && real */ REALBOOLAND:
   res_ti = gen_bin_real_booland(ndp, op1_ti, op2_ti);
   break;
  case /* || */ BOOLOR:
   __case_terr(__FILE__, __LINE__);
   break;
  case /* && real */ REALBOOLOR:
   res_ti = gen_bin_real_boolor(ndp, op1_ti, op2_ti);
   break;
  case /* << */ SHIFTL: case /* <<< */ ASHIFTL:
  case /* >> */ SHIFTR:
   /* SJM 09/30/03 - notice new arithmetic lshift same as logical */
   /* if shift amt x/z, result is 0 */ 
   res_ti = gen_bin_notsgn_shift(ndp, op1_ti, op2_ti, op1_nd_wid, op2_nd_wid);
   break;
  case /* >>> */ ASHIFTR:
   /* if first opand word32, same as logical right shift */ 
   if (!ndp->has_sign)
    res_ti = gen_bin_notsgn_shift(ndp, op1_ti, op2_ti, op1_nd_wid, op2_nd_wid);
   else res_ti = gen_bin_ashiftr(ndp, op1_ti, op2_ti, op1_nd_wid, op2_nd_wid);
   break;
  case /* ** */ POWER:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    nd_signop, FALSE, FALSE); 

   if (ndp->szu.xclen > WBITS) 
    {
     res_ti = gen_bin_arithop(ndp, op1_ti, op2_ti, nd_signop);
    }
   else if (nd_signop) res_ti = gen_bin_sgn_power(ndp, op1_ti, op2_ti, FALSE);
   else res_ti = gen_bin_power(ndp, op1_ti, op2_ti, FALSE);
   break;
  default: res_ti = SR_UNKN; __case_terr(__FILE__, __LINE__);
 }
 return(res_ti);
}

/*
 * generate a 2-state binop
 */
static int32 gen_binop_2state(struct expr_t *ndp, int32 op1_ti, int32 op2_ti, 
 int32 op1_nd_wid, int32 op2_nd_wid, int32 nd_signop)
{
 int32 res_ti, srtyp;

 if (ndp->szu.xclen == 1) srtyp = SR_SCAL2S;
 else srtyp = SR_BIT2S;
 /* this is result operator not operands width */
 res_ti = -1;
 switch (ndp->optyp) {
  case /* + */ PLUS:
  case /* - */ MINUS:
  case /* * */ TIMES:
  case /* / */ DIV:
  case /* % */ MOD:

  case /* & */ BITREDAND:
  case /* | */ BITREDOR:
  case /* ^ */ BITREDXOR:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, srtyp, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, srtyp, op2_nd_wid,
    nd_signop, FALSE, FALSE); 
 
   res_ti = gen_bin_arithop_2state(ndp, op1_ti, op2_ti, nd_signop, srtyp);
   break;
  case /* not ^ */ REDXNOR:
   /* can't be just invert xor because need masking if not exactly WBITS */
   /* AIV 09/29/08 - these need to be sign extend - misread LRM */
   /* see LRM section 5.1.1 */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, srtyp, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, srtyp, op2_nd_wid,
    nd_signop, FALSE, FALSE); 

   res_ti = gen_bin_bitredxnor_2state(ndp, op1_ti, op2_ti, srtyp);
   break;
  case /* >= */ RELGE:
  case /* > */ RELGT:
  case /* <= */ RELLE:
  case /* < */ RELLT:
   if (ndp->lu.x->szu.xclen == 1 && ndp->ru.x->szu.xclen == 1) 
    {
     srtyp = SR_SCAL2S;
    }
   else srtyp = SR_BIT2S;

   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, srtyp, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, srtyp, op2_nd_wid,
    nd_signop, FALSE, FALSE); 
   res_ti = gen_bin_relcomp(ndp, op1_ti, op2_ti, SR_SCAL2S);
   break;
  case /* != */ RELNEQ:
  case /* == */ RELEQ:
  case /* === */ RELCEQ:
  case /* !== */ RELCNEQ:
   /* notice === now the same as == for 2-state */
   res_ti = gen_bin_neeq_2state(ndp, op1_ti, op2_ti);
   break; 
  case /* && */ BOOLAND:
   __case_terr(__FILE__, __LINE__);
   break;
  case /* || */ BOOLOR:
   __case_terr(__FILE__, __LINE__);
   break;
  case /* << */ SHIFTL: case /* <<< */ ASHIFTL:
  case /* >> */ SHIFTR:
   /* SJM 09/30/03 - notice new arithmetic lshift same as logical */
   /* if shift amt x/z, result is 0 */ 
   res_ti = gen_bin_notsgn_shift_2state(ndp, op1_ti, op2_ti, op1_nd_wid, 
      op2_nd_wid);
   break;
  case /* >>> */ ASHIFTR:
   /* if first opand word32, same as logical right shift */ 
   if (!ndp->has_sign)
    {
     res_ti = gen_bin_notsgn_shift_2state(ndp, op1_ti, op2_ti, op1_nd_wid, 
       op2_nd_wid);
    }
   else 
    {
     res_ti = gen_bin_ashiftr_2state(ndp, op1_ti, op2_ti, op1_nd_wid, 
       op2_nd_wid);
    }
   break;
  case /* ** */ POWER:
   srtyp = SR_BIT2S;
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, srtyp, op1_nd_wid,
    nd_signop, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, srtyp, op2_nd_wid,
    nd_signop, FALSE, FALSE); 

   if (ndp->szu.xclen > WBITS) 
    {
     res_ti = gen_bin_arithop_2state(ndp, op1_ti, op2_ti, nd_signop, srtyp);
    }
   else if (nd_signop) res_ti = gen_bin_sgn_power(ndp, op1_ti, op2_ti, TRUE);
   else res_ti = gen_bin_power(ndp, op1_ti, op2_ti, TRUE);
   break;
  case /* + real */ REALPLUS:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_BIT2S, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   res_ti = __emit_add_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* - real */ REALMINUS:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_BIT2S, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   res_ti = __emit_sub_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* * real */ REALTIMES:
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_BIT2S, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   res_ti = __emit_mult_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* * real */ REALDIV:
   /* SJM 06/17/04 - what happens with divide by 0? - x is 0.0 maybe? */
   /* for now using IEEE floating point result */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_BIT2S, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   res_ti = gen_div_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   break;
  case /* ** real */ REALPOWER:
   /* AIV 01/10/07 - added real power lowering */
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, op1_nd_wid,
    nd_signop, TRUE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_BIT2S, op2_nd_wid,
    nd_signop, TRUE, FALSE); 

   res_ti = __emit_power_real(op1_ti, op2_ti);
   __tntab[res_ti].t_real = TRUE;
   __tntab[res_ti].tn_used_wide = TRUE;
   /* AIV 10/09/10 - was missing break statement here */
   break;
  /* AIV 10/13/10 - these can still get here - I believe by folding */
  /* constant values */
  case /* >= real */ REALRELGE:
  case /* > real */ REALRELGT:
  case /* <= real */ REALRELLE:
  case /* < real */ REALRELLT:
  case /* == real */ REALRELEQ:
  case /* == real */ REALRELNEQ:
   res_ti = gen_bin_real_relcomp(ndp, op1_ti, op2_ti);
   break;
  default: res_ti = SR_UNKN; __case_terr(__FILE__, __LINE__);
 }
 return(res_ti);
}

static int32 gen_bin_arithop_2state(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti, int32 nd_signop, int32 srtyp)
{
 int32 res_ti, res_bpti, hghw_apti, mask_it; 
 int32 t1_ti, blen, bytsiz, ofs;
 int32 r1_ti, mask_ti, is_div_2state;
 word32 mask, val;
 struct bblk_t *xz_bbp, *after_bbp, *op_bbp;

 blen = ndp->szu.xclen;
 bytsiz = WRDBYTES*wlen_(blen);
 /* must copy result into a tmp */

 /* if no b parts, skip the x/z test */
 after_bbp = NULL;
 /* if divide must check for divide by zero and result is 4-state */
 is_div_2state = FALSE;
 if (ndp->optyp == MOD || ndp->optyp == DIV) 
  {
   if (__is_constant(op2_ti))
    {
     is_div_2state = TRUE;
     if (__is_constant_zero(op2_ti))
      {
       /* convert to 4-state for the x */
       if (srtyp == SR_SCAL2S) srtyp = SR_SCAL;
       else srtyp = SR_VEC;

       res_ti = __gen_tn(srtyp, blen);
       gen_ab_setx(res_ti, TRUE);
       return(res_ti);
      }
     else res_ti = __gen_tn(srtyp, blen);
    }
   else
    {
     /* convert to 4-state for the x */
     if (srtyp == SR_SCAL2S) srtyp = SR_SCAL;
     else srtyp = SR_VEC;
     res_ti = __gen_tn(srtyp, blen);

     after_bbp = __alloc_bblk(FALSE);
     op_bbp = __alloc_bblk(FALSE);
     /* for divsor a part also can't be 0 */
     xz_bbp = __alloc_bblk(FALSE);
     __emit_jmp_0(xz_bbp, op_bbp, op2_ti);
     __start_bblk(xz_bbp);
     gen_ab_setx(res_ti, TRUE);

     __emit_jmp(after_bbp);
     __start_bblk(op_bbp);
    }
  }
 else res_ti = __gen_tn(srtyp, blen);

 if (blen == 1) mask_it = FALSE;
 else mask_it = TRUE;

 /* AIV 01/09/07 - added power and converted to ifs to switch stmt */
 switch (ndp->optyp) {
  case PLUS: 
   t1_ti = __emit_add(blen, op1_ti, op2_ti); 
   mask_it = TRUE;
   break;
  /* SJM 05/14/05 - order must be same as plus */
  case MINUS: 
   t1_ti = __emit_sub(blen, op1_ti, op2_ti); 
   mask_it = TRUE;
   break;
  case TIMES:
   if (nd_signop)
    {
     t1_ti = gen_bin_sign_mult(ndp, res_ti, op1_ti, op2_ti, TRUE);
     return(t1_ti);
    }
   else t1_ti = __emit_mult(blen, op1_ti, op2_ti);
   mask_it = TRUE;
   break;
  case DIV:
   if (nd_signop)
    {
     t1_ti = gen_bin_sign_div(ndp, res_ti, op1_ti, op2_ti, FALSE, 
       is_div_2state);
     if (after_bbp != NULL) __start_bblk(after_bbp);
     return(t1_ti);
    }
   else 
    {
     /* divide may still need to convert to x for / by zero */
     if (blen > 1 && !is_div_2state)
      {
       t1_ti = __emit_div(blen, op1_ti, op2_ti, SR_VEC);
      }
     else t1_ti = __emit_div(blen, op1_ti, op2_ti, SR_BIT2S);
    }
   mask_it = TRUE;
   break; 
  case MOD:
   if (nd_signop)
    {
     t1_ti = gen_bin_sign_div(ndp, res_ti, op1_ti, op2_ti, TRUE, is_div_2state);
     if (after_bbp != NULL) __start_bblk(after_bbp);
     return(t1_ti);
    }
   else 
    {
     /* divide may still need to convert to x for / by zero */
     if (blen > 1 && !is_div_2state)
      {
       t1_ti = __emit_mod(blen, op1_ti, op2_ti, SR_VEC);
      }
     else t1_ti = __emit_mod(blen, op1_ti, op2_ti, SR_BIT2S);
    }
   mask_it = TRUE;
   break;
  case POWER:
   if (nd_signop)
    {
     t1_ti = __emit_wide_sgn_lpow(op1_ti, op2_ti, blen, TRUE);
     return(t1_ti);
    }
   else t1_ti = __emit_wide_lpow(op1_ti, op2_ti, blen);
   mask_it = TRUE;
   break;
  case /* & */ BITREDAND:
   t1_ti = __emit_bin_bitand(blen, op1_ti, op2_ti); 
   break;
  case /* | */ BITREDOR:
   t1_ti = __emit_bin_bitor(blen, op1_ti, op2_ti); 
   break;
  case /* ^ */ BITREDXOR:
   t1_ti = __emit_bin_bitxor(blen, op1_ti, op2_ti); 
   break;
  default: t1_ti = SR_UNKN; __case_terr(__FILE__, __LINE__); 
 }

 /* need to mask the result as well */
 if (mask_it && ubits_(blen) != 0)
  {
   mask = __masktab[ubits_(blen)];
   /* AIV 12/28/11 - if this is folded need to also fold the mask as well */
   /* was trying to copy into a constant here */
   if (__is_constant(t1_ti))
    {
     /* DBG remove -- */
     if (blen > WBITS) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     val = __get_wrd_con_val(t1_ti);
     val = val & mask; 
     hghw_apti = __gen_cint_tn(val);
    }
   else
    {
     if (blen > WBITS)
      {
       ofs = WRDBYTES*(wlen_(blen) - 1);
       hghw_apti = __con_adradd_insn(SR_VEC, blen, t1_ti, ofs);
      }
     else hghw_apti = t1_ti;
    }

   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);
  }
 __emit_copy(bytsiz, t1_ti, res_ti);
      
 if (!is_div_2state && (ndp->optyp == MOD || ndp->optyp == DIV) && blen > 1) 
  {
   res_bpti = __get_bpti(res_ti);
   __emit_store_cint(res_bpti, 0, bytsiz);
  }

 if (after_bbp != NULL) __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * AIV 08/17/11 - now if compiled with +realwarns must check for divide
 * by zero to emit warning message
 */
static int32 gen_div_real(int32 op1_ti, int32 op2_ti)
{
 int32 res_ti;
 struct bblk_t *divzero_bbp, *div_bbp;
 

 /* if not turn on just do a normal divide */
 if (!__real_warns) 
  {
   res_ti = __emit_div_real(op1_ti, op2_ti);
   return(res_ti);
  }

 divzero_bbp = __alloc_bblk(FALSE);
 div_bbp = __alloc_bblk(FALSE);
 __emit_jmp_real0(divzero_bbp, div_bbp, op2_ti);
 __start_bblk(divzero_bbp);
 __emit_real_div0_warning(__generating_stp);

 /* fallthru and still do the divide */
 __start_bblk(div_bbp);
 res_ti = __emit_div_real(op1_ti, op2_ti);
 return(res_ti);
}
       
/*
 * try to convert a 32-bit constant into a scalar value
 * can only turn 32-bit 1'b1, 1'b0, 1'bz, 1'bx into scalar 
 * return -1 if cannot convert
 */
static int32 gen_try_to_cnvt_scalar_const(int32 op_ti)
{
 int32 xvi, sval, cint_ti;
 word32 av, bv;
 word32 *wp;
 struct tn_t *tnp;
     
 tnp = &(__tntab[op_ti]);

 /* if wide or not constant return -1 */
 if (tnp->tnwid > WBITS) return(-1);
 if (tnp->comlab_typ != COMLAB_CONADR) return(-1);

 xvi = __get_con_adradd_xvi(op_ti);
 wp = &(__contab[xvi]);

 av = wp[0];
 bv = wp[0];
 sval = -1;
 /* bpart 0 can be 1 or 0 */
 if (bv == 0)
  {
   if (av == 0) sval = 0;
   else if (av == 1) sval = 1;
  }
 else if (bv == 1)
  {
   /* x or z */
   if (av == 0) sval = 2;
   else if (av == 1) sval = 3;
  }
 if (sval == -1) return(-1);

 cint_ti = __gen_cint_tn(sval);
 return(cint_ti);
}
   
/*
 * if both operands of a binary operation are scalar just get value from
 * precomputed tables
 *
 * index for the table is op1 | ( op2 << 2) with values between 0-15
 *
 */
static int32 gen_scalar_binop(int32 optyp, int32 op1_ti, int32 op2_ti, 
 int32 srtyp1, int32 srtyp2)
{
 int32 res_ti, cint_ti, t2_ti, t1_ti, ndx_ti, nlotyp;

 /* if strength mask off strength value */
 op1_ti = __gen_scalar_operand(srtyp1, op1_ti);
 op2_ti = __gen_scalar_operand(srtyp2, op2_ti);
 /* get the index op1 | (op2 << 2) */
 cint_ti = __gen_cint_tn(2);
 t1_ti = __emit_shiftl(WBITS, cint_ti, op2_ti);
 t2_ti = __emit_bin_bitor(WBITS, op1_ti, t1_ti);

 nlotyp = -1;
 /* AIV 03/09/09 - combined the tables which have the same value into */
 /* new 'pattern' arrays */
 switch (optyp) {
  /* PATTERN 1 */
  case /* + */ PLUS:
  case /* - */ MINUS: 
  case /* != */ RELNEQ: 
  case /* ^ */ BITREDXOR: 
   nlotyp = NLO_SBO_P1; 
   break;
  /* PATTERN 2 */
  case /* ** */ POWER:
  case /* >= */ RELGE:
   nlotyp = NLO_SBO_P2; 
   break;
  /* PATTERN 3 */
  case /* not ^ */ REDXNOR: 
  case /* == */ RELEQ: 
   nlotyp = NLO_SBO_P3; 
   break;
  /* PATTERN 4 */
  case /* | */ BITREDOR: 
  case /* || */ BOOLOR: 
   nlotyp = NLO_SBO_P4; 
#ifdef __XPROP__
   /* AIV 08/02/11 - if xprop need to use new x values table */
   if (__inst_mod->m_use_xprop_and_or_x) nlotyp = NLO_SBO_X_BITOR; 
#endif
   break;
  /* AIV 08/02/11 - these are really the same removed NLO_BOOLAND */
  case /* & */ BITREDAND: 
  case /* && */ BOOLAND: 
   nlotyp = NLO_SBO_BITREDAND; 
#ifdef __XPROP__
   /* AIV 08/02/11 - if xprop need to use new values table which is the */
   /* same as times table */
   if (__inst_mod->m_use_xprop_and_or_x) nlotyp = NLO_SBO_TIMES; 
#endif
   break;
  /* PATTERN 5 - shifts */
  case /* << */ SHIFTL: 
  case /* <<< */ ASHIFTL: 
  case /* >> */ SHIFTR:
  case /* >>> */ ASHIFTR: 
   nlotyp = NLO_SBO_SHIFT; 
   break;
  /* INIVIDUAL - no common pattern */
  case /* * */ TIMES: nlotyp = NLO_SBO_TIMES; break;
  case /* / */ DIV: nlotyp = NLO_SBO_DIV; break;
  case /* % */ MOD: nlotyp = NLO_SBO_MOD; break;
  case /* > */ RELGT: nlotyp = NLO_SBO_RELGT; break;
  case /* <= */ RELLE: nlotyp = NLO_SBO_RELLE; break;
  case /* < */ RELLT: nlotyp = NLO_SBO_RELLT; break;
  case /* === */ RELCEQ: nlotyp = NLO_SBO_RELCEQ; break;
  case /* !== */ RELCNEQ: nlotyp = NLO_SBO_RELCNEQ; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 
 /* ndx_ti must be in a reg if folded and still address must move to reg */
 if (__tntab[t2_ti].tn_typ == TN_ADR)
  {
   ndx_ti = __move_insn(TN_VAL, I_MOVA, AM_NDXREG, t2_ti);
  }
 else ndx_ti = t2_ti;

 /* load the value from the table */
 res_ti = __move_srep_insn(TN_VAL, I_MOVA, SR_SCAL, 1, 
    AM_NLO_ARRNDX, ndx_ti, nlotyp);
 return(res_ti);
}

/*
 * generate a SR_SCAL from a SR_VEC, SR_SSCAL, or SR_SCAL
 */
extern int32 __gen_scalar_operand(int32 srtyp, int32 op_ti)
{
 int32 cint_ti, scal_ti, op_bpti, t1_ti;

 scal_ti = op_ti;
 /* if strength just mask */
 if (srtyp == SR_SSCAL || srtyp == SR_SVEC)
  {
   cint_ti = __gen_cint_tn(3);
   scal_ti = __emit_bin_bitand(WBITS, cint_ti, op_ti);
  }
 /* vector do the conversion */
 else if (srtyp == SR_VEC)
  {
   cint_ti = __gen_cint_tn(1);
   op_bpti = __get_bpti(op_ti);
   if (__get_tnwid(op_ti) != 1)
    {
     op_bpti = __emit_mask_and(cint_ti, op_bpti);
     op_ti = __emit_mask_and(cint_ti, op_ti);
    }
   t1_ti = __emit_shiftl(1, cint_ti, op_bpti);
   /* AIV 03/04/09 - better code produced with an add here than or */
   /* notice this is the same for all 4 scalar states */
   scal_ti = __emit_add(1, t1_ti, op_ti); 
  }
 else if (srtyp != SR_SCAL && srtyp != SR_SCAL2S && srtyp != SR_BIT2S) 
   __misc_terr(__FILE__, __LINE__);
 return(scal_ti);
}


/*
 * computer the needed width for binary operators
 * know the 
 */
static int32 binop_get_ndwid(int32 *op2_nd_wid, struct expr_t *ndp)
{
 int32 wclass, op1_nd_wid;
 
 if (ndp->lu.x->cnvt_to_real || ndp->ru.x->cnvt_to_real)
  {
   op1_nd_wid = *op2_nd_wid = WBITS;
   return(op1_nd_wid);
  }

 wclass = __get_widthclass(ndp);
 switch ((byte) wclass) {
  case WIDONE:
   /* for && type - operands width are self determined */
   op1_nd_wid = ndp->lu.x->szu.xclen;
   *op2_nd_wid = ndp->ru.x->szu.xclen;
   break;
  case WIDENONE:
   /* for relationals operand widths is max */
   if (ndp->lu.x->szu.xclen > ndp->ru.x->szu.xclen)
    op1_nd_wid = ndp->lu.x->szu.xclen;
   else op1_nd_wid = ndp->ru.x->szu.xclen;
   *op2_nd_wid = op1_nd_wid;
   break;
  case WIDMAX:
   /* for arithmetic - width is width in operator expr */
   op1_nd_wid = *op2_nd_wid = ndp->szu.xclen;
   break;
  case WIDLEFT:
   op1_nd_wid = ndp->szu.xclen;  
   *op2_nd_wid = ndp->ru.x->szu.xclen;
   break;
  case WIDSELF:
   /* can't occur for binary */
   op1_nd_wid = -1;
   __case_terr(__FILE__, __LINE__);
  default: { op1_nd_wid = SR_UNKN; __case_terr(__FILE__, __LINE__); }
 }
 return(op1_nd_wid);
}

/*
 * gen insns for binary non real arithmetic operators 
 *
 * know both operands srep vec and correct width 
 */
static int32 gen_bin_arithop(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti, int32 nd_signop)
{
 int32 res_ti, res_bpti, hghw_apti; 
 int32 t1_ti, op1_bpti, op2_bpti, blen, bytsiz, ofs;
 int32 r1_ti, mask_ti;
 word32 mask;
 struct bblk_t *op2_bbp, *xz_bbp, *after_bbp, *op_bbp;

 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);

 blen = ndp->szu.xclen;
 bytsiz = WRDBYTES*wlen_(blen);
 /* must copy result into a tmp */
 res_ti = __gen_tn(SR_VEC, blen);
 res_bpti = __get_bpti(res_ti);

 /* if no b parts, skip the x/z test */
 after_bbp = NULL;

 if (ndp->optyp == MOD || ndp->optyp == DIV)
  {
   /* AIV 08/30/10 - should check for constant value 0 here */
   /* if divide by known constant not 0  - skip runtime check */
   if (__is_constant(op2_ti))
    {
     if (__is_constant_zero(op2_ti))
      {
       gen_ab_setx(res_ti, FALSE);
       return(res_ti); 
      }
     else
      {
       op_bbp = __alloc_bblk(FALSE);
       after_bbp = __alloc_bblk(FALSE);
       xz_bbp = __alloc_bblk(TRUE);
       __emit_jmpor_0(op_bbp, xz_bbp, op1_bpti, op2_bpti);
      }
    }
   else
    {
     op_bbp = __alloc_bblk(FALSE);
     after_bbp = __alloc_bblk(FALSE);

     /* AIV 02/03/09 - divide still must check for 0 can never remove */
     xz_bbp = __alloc_bblk(FALSE);
     /* LOOKATME - could add cmp 3 or insn to or all 3 using normal */
     /* expand cases code */
     op2_bbp = __alloc_bblk(FALSE);
     /* compare the b parts */
     /* SJM 01/13/05 - or will be T (non 0) if any x part bits on */
     /* so need x/z case but if 0 then will be false so need 3rd label */
     __emit_jmpor_0(op2_bbp, xz_bbp, op1_bpti, op2_bpti);

     __start_bblk(op2_bbp);
     /* for divsor a part also can't be 0 */
     __emit_jmp_0(xz_bbp, op_bbp, op2_ti);
    }
  }
 else
  {
   op_bbp = __alloc_bblk(FALSE);
   after_bbp = __alloc_bblk(FALSE);
   xz_bbp = __alloc_bblk(TRUE);
   __emit_jmpor_0(op_bbp, xz_bbp, op1_bpti, op2_bpti);
  }
 __start_bblk(xz_bbp);
 gen_ab_setx(res_ti, FALSE);
 __emit_jmp(after_bbp);

 __start_bblk(op_bbp);

 /* AIV 01/09/07 - added power and converted to ifs to switch stmt */
 switch (ndp->optyp) {
  case PLUS: 
   t1_ti = __emit_add(blen, op1_ti, op2_ti); 
   break;
  /* SJM 05/14/05 - order must be same as plus */
  case MINUS: 
   t1_ti = __emit_sub(blen, op1_ti, op2_ti); 
   break;
  case TIMES:
   if (nd_signop)
    {
     t1_ti = gen_bin_sign_mult(ndp, res_ti, op1_ti, op2_ti, FALSE);
     __start_bblk(after_bbp);
     return(t1_ti);
    }
   else t1_ti = __emit_mult(blen, op1_ti, op2_ti);
   break;
  case DIV:
   if (nd_signop)
    {
     t1_ti = gen_bin_sign_div(ndp, res_ti, op1_ti, op2_ti, FALSE, FALSE);
     __start_bblk(after_bbp);
     return(t1_ti);
    }
   else t1_ti = __emit_div(blen, op1_ti, op2_ti, SR_VEC);
   break; 
  case MOD:
   if (nd_signop)
    {
     t1_ti = gen_bin_sign_div(ndp, res_ti, op1_ti, op2_ti, TRUE, FALSE);
     __start_bblk(after_bbp);
     return(t1_ti);
    }
   else t1_ti = __emit_mod(blen, op1_ti, op2_ti, SR_VEC);
   break;
  case POWER:
   if (nd_signop)
    {
     t1_ti = __emit_wide_sgn_lpow(op1_ti, op2_ti, blen, FALSE);
     __start_bblk(after_bbp);
     return(t1_ti);
    }
   else t1_ti = __emit_wide_lpow(op1_ti, op2_ti, blen);
   break;
  default: t1_ti = SR_UNKN; __case_terr(__FILE__, __LINE__); 
 }

 /* need to mask the result as well */
 /* AIV 05/25/06 - don't need to mask the bpart since it is always set to 0 */
 if (ubits_(blen) != 0)
  {
   mask = __masktab[ubits_(blen)];
   if (blen > WBITS)
    {
     ofs = WRDBYTES*(wlen_(blen) - 1);
     hghw_apti = __con_adradd_insn(SR_VEC, blen, t1_ti, ofs);
    }
   else hghw_apti = t1_ti;

   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);
  }
 __emit_copy(bytsiz, t1_ti, res_ti);
 __emit_store_cint(res_bpti, 0, bytsiz);
 __start_bblk(after_bbp);
 return(res_ti);
}


/*
 * gen a signed multiply op 
 * op1 and op2 known not to be 0 here
 * op1 and op2 are converted to right size and sign by here
 * AIV LOOKATME - mimics interpreter maybe better method using asm insns ???
 */
static int32 gen_bin_sign_mult(struct expr_t *ndp, int32 res_ti,
 int32 op1_ti, int32 op2_ti, int32 is_2state)
{
 int32 t1_ti, t2_ti, t3_ti, t4_ti, val_ti, res_bpti, blen, cint_ti;
 int32 r1_ti, mask_ti;
 word32 mask;
 struct bblk_t *op1_neg_bbp, *op1_pos_bbp;
 struct bblk_t *both_neg_bbp, *op1_neg_op2_pos_bbp, *zerob_mask_bbp;
 struct bblk_t *op1_pos_op2_neg_bbp, *both_pos_bbp;

 /* if 32 bits do regular sign mult */
 blen = ndp->szu.xclen;
 if (__get_tnwid(op1_ti) == WBITS && __get_tnwid(op2_ti) == WBITS)
  {
   val_ti = __emit_sgn_mult(blen, op1_ti, op2_ti);
   __emit_copy(WRDBYTES, val_ti, res_ti);
   if (!is_2state)
    {
     res_bpti = __get_bpti(res_ti);
     __emit_store_cint(res_bpti, 0, WRDBYTES);
    }
   return(res_ti); 
  }

 /* DBG remove -- */
 if (__get_tnwid(op1_ti) != __get_tnwid(op2_ti)) 
  __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* if wid just call size op since it is a wrapper */
 if (blen > WBITS)
  {
   val_ti = __emit_sgn_mult(blen, op1_ti, op2_ti);
   __emit_copy(wlen_(blen)*WRDBYTES, val_ti, res_ti);
   if (!is_2state)
    {
     res_bpti = __get_bpti(res_ti);
     __emit_store_cint(res_bpti, 0, wlen_(blen)*WRDBYTES);
    }
   return(res_ti);
  }

 /* if it gets here do narrow signed op */
 op1_neg_bbp = __alloc_bblk(FALSE);
 op1_pos_bbp = __alloc_bblk(FALSE);
 both_neg_bbp = __alloc_bblk(FALSE);
 op1_neg_op2_pos_bbp = __alloc_bblk(FALSE);
 op1_pos_op2_neg_bbp = __alloc_bblk(FALSE);
 both_pos_bbp = __alloc_bblk(FALSE);;
 zerob_mask_bbp = __alloc_bblk(FALSE);

 /* check if op1 signed bit on */
 __emit_sgnbit_on_jmp(op1_neg_bbp, op1_pos_bbp, op1_ti);

 __start_bblk(op1_neg_bbp);

 /* sign extend op1 */
 mask = ~(__masktab[blen]);
 cint_ti = __gen_cint_tn(mask);
 t1_ti = __emit_bin_bitor(blen, op1_ti, cint_ti);
 t2_ti = __emit_swap_sign(blen, t1_ti); 

 /* check if op2 signed bit on */
 __emit_sgnbit_on_jmp(both_neg_bbp, op1_neg_op2_pos_bbp, op2_ti);

 /* only one is negative op and change sign */
 __start_bblk(op1_neg_op2_pos_bbp);

 t3_ti = __emit_sgn_mult(blen, t2_ti, op2_ti);
 val_ti = __emit_swap_sign(blen, t3_ti); 
 __emit_copy(WRDBYTES, val_ti, res_ti);
 __emit_jmp(zerob_mask_bbp);


 /* both op1 and op2 negative */ 
 __start_bblk(both_neg_bbp);

 /* sign extend op2 */
 mask = ~(__masktab[blen]);
 cint_ti = __gen_cint_tn(mask);
 t3_ti = __emit_bin_bitor(blen, op2_ti, cint_ti);
 t4_ti = __emit_swap_sign(blen, t3_ti); 
 val_ti = __emit_sgn_mult(blen, t2_ti, t4_ti);
 __emit_copy(WRDBYTES, val_ti, res_ti);
 __emit_jmp(zerob_mask_bbp);

 /* op1 positive */ 
 __start_bblk(op1_pos_bbp);
 /* check if op2 signed bit on */
 __emit_sgnbit_on_jmp(op1_pos_op2_neg_bbp, both_pos_bbp, op2_ti);

 /* op1 postive, op2 negative */
 __start_bblk(op1_pos_op2_neg_bbp);

 mask = ~(__masktab[blen]);
 cint_ti = __gen_cint_tn(mask);
 t1_ti = __emit_bin_bitor(blen, op2_ti, cint_ti);
 t2_ti = __emit_swap_sign(blen, t1_ti); 
 t3_ti = __emit_sgn_mult(blen, op1_ti, t2_ti);
 val_ti = __emit_swap_sign(blen, t3_ti); 
 __emit_copy(WRDBYTES, val_ti, res_ti);
 __emit_jmp(zerob_mask_bbp);

 /* both operands positive */
 __start_bblk(both_pos_bbp);
 val_ti = __emit_sgn_mult(blen, op1_ti, op2_ti);
 __emit_copy(WRDBYTES, val_ti, res_ti);
 __emit_jmp(zerob_mask_bbp);

 /* mask a part and zero b */
 __start_bblk(zerob_mask_bbp);
 mask = __masktab[ubits_(blen)];
 mask_ti = __gen_cint_tn(mask);
 r1_ti = __emit_mask_and(res_ti, mask_ti);
 __emit_copy(WRDBYTES, r1_ti, res_ti);  

 if (!is_2state)
  {
   res_bpti = __get_bpti(res_ti);
   __emit_store_cint(res_bpti, 0, WRDBYTES);
  }
 return(res_ti);
}

/*
 * gen a signed divided op 
 * op1 and op2 known not to be 0 here
 * op1 and op2 are converted to right size and sign by here
 *
 * SJM 03-27-14 - for mod first operand determines sign but for div if both
 * or neither signed, then unsigned (no need to negate) else need to negate
 * to make signed - was wrongly assuming always use mod result signed rules
 *
 * AIV LOOKATME - mimics interpreter maybe better method using asm insns ???
 */
static int32 gen_bin_sign_div(struct expr_t *ndp, int32 res_ti,
 int32 op1_ti, int32 op2_ti, int32 is_mod, int32 is_2state)
{
 int32 t1_ti, t2_ti, t3_ti, t4_ti, val_ti;
 int32 mask_ti, res_bpti, blen, cint_ti, r1_ti;
 word32 mask;
 struct bblk_t *op1_neg_bbp, *op1_pos_bbp;
 struct bblk_t *both_neg_bbp, *op1_neg_op2_pos_bbp, *zerob_mask_bbp;
 struct bblk_t *op1_pos_op2_neg_bbp, *both_pos_bbp;

 /* if wbits do regular (machine code) sign mod/div */
 blen = ndp->szu.xclen;
 if (__get_tnwid(op1_ti) == WBITS && __get_tnwid(op2_ti) == WBITS)
  {
   if (is_mod) val_ti = __emit_sgn_mod(blen, op1_ti, op2_ti, is_2state);
   else val_ti = __emit_sgn_div(blen, op1_ti, op2_ti, is_2state);
   __emit_copy(WRDBYTES, val_ti, res_ti);
   if (!is_2state)
    {
     res_bpti = __get_bpti(res_ti);
     __emit_store_cint(res_bpti, 0, WRDBYTES);
    }
   return(res_ti); 
  }
#ifndef __CVC32__
 /* AIV 01/03/11 - if both operands (ints) just movslq and do operation */
 /* and 64-bit and mask it - this produces much better code */
 if (__get_tnwid(op1_ti) == 32 && __get_tnwid(op2_ti) == 32)
  {
   int32 amtyp;

   /* do the moves */
   if (__tntab[op1_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
   else amtyp = AM_REG;

   op1_ti = __move_insn(TN_VAL, I_MOVSLQ, amtyp, op1_ti);

   if (__tntab[op2_ti].tn_typ == TN_ADR) amtyp = AM_NDXREG; 
   else amtyp = AM_REG;
   op2_ti = __move_insn(TN_VAL, I_MOVSLQ, amtyp, op2_ti);

   if (is_mod) val_ti = __emit_sgn_mod(blen, op1_ti, op2_ti, is_2state);
   else val_ti = __emit_sgn_div(blen, op1_ti, op2_ti, is_2state);
   /* mask value to 32-bit */
   mask = __masktab[blen];
   cint_ti = __gen_cint_tn(mask);
   val_ti = __emit_bin_bitand(blen, val_ti, cint_ti);
   __emit_copy(WRDBYTES, val_ti, res_ti);

   if (!is_2state)
    {
     res_bpti = __get_bpti(res_ti);
     __emit_store_cint(res_bpti, 0, WRDBYTES);
    }
   return(res_ti); 
  }
#endif

 /* DBG remove -- */
 if (__get_tnwid(op1_ti) != __get_tnwid(op2_ti)) 
  __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* if wid just call size op since it is a wrapper */
 if (blen > WBITS)
  {
   if (is_mod) val_ti = __emit_sgn_mod(blen, op1_ti, op2_ti, is_2state);
   else val_ti = __emit_sgn_div(blen, op1_ti, op2_ti, is_2state);
   __emit_copy(wlen_(blen)*WRDBYTES, val_ti, res_ti);
   if (!is_2state)
    {
     res_bpti = __get_bpti(res_ti);
     __emit_store_cint(res_bpti, 0, wlen_(blen)*WRDBYTES);
    }
   return(res_ti);
  }

 /* if it gets here do narrow signed op */
 op1_neg_bbp = __alloc_bblk(FALSE);
 op1_pos_bbp = __alloc_bblk(FALSE);
 both_neg_bbp = __alloc_bblk(FALSE);
 op1_neg_op2_pos_bbp = __alloc_bblk(FALSE);
 op1_pos_op2_neg_bbp = __alloc_bblk(FALSE);
 both_pos_bbp = __alloc_bblk(FALSE);;
 zerob_mask_bbp = __alloc_bblk(FALSE);

 /* check if op1 signed bit on, i.e. value is negative  */
 __emit_sgnbit_on_jmp(op1_neg_bbp, op1_pos_bbp, op1_ti);

 __start_bblk(op1_neg_bbp);

 /* sign extend op1 */
 mask = ~(__masktab[blen]);
 cint_ti = __gen_cint_tn(mask);
 t1_ti = __emit_bin_bitor(blen, op1_ti, cint_ti);
 t2_ti = __emit_swap_sign(blen, t1_ti); 

 /* check if op2 signed bit on */
 __emit_sgnbit_on_jmp(both_neg_bbp, op1_neg_op2_pos_bbp, op2_ti);

 /* only one is negative op and change sign */
 __start_bblk(op1_neg_op2_pos_bbp);

 if (is_mod) t3_ti = __emit_sgn_mod(blen, t2_ti, op2_ti, is_2state);
 else t3_ti = __emit_sgn_div(blen, t2_ti, op2_ti, is_2state);
 /* SJM 03-29-14 - always negative since for mod first and for div one of */
 val_ti = __emit_swap_sign(blen, t3_ti); 

 __emit_copy(WRDBYTES, val_ti, res_ti);
 __emit_jmp(zerob_mask_bbp);

 /* both op1 and op2 negative */ 
 __start_bblk(both_neg_bbp);

 /* sign extend op2 */
 mask = ~(__masktab[blen]);
 cint_ti = __gen_cint_tn(mask);
 t3_ti = __emit_bin_bitor(blen, op2_ti, cint_ti);
 t4_ti = __emit_swap_sign(blen, t3_ti); 

 /* AIV 01/03/11 - can be mod or div here need to handle */
 if (is_mod) val_ti = __emit_sgn_mod(blen, t2_ti, t4_ti, is_2state);
 else val_ti = __emit_sgn_div(blen, t2_ti, t4_ti, is_2state);
 /* SJM 03-29-14 - for mod, negative since first negative but for div */ 
 /* not negative since both negative */
 if (is_mod) val_ti = __emit_swap_sign(blen, val_ti); 
 __emit_copy(WRDBYTES, val_ti, res_ti);
 __emit_jmp(zerob_mask_bbp);

 /* op1 positive */ 
 __start_bblk(op1_pos_bbp);
 /* check if op2 signed bit on */
 __emit_sgnbit_on_jmp(op1_pos_op2_neg_bbp, both_pos_bbp, op2_ti);

 /* op1 postive, op2 negative */
 __start_bblk(op1_pos_op2_neg_bbp);

 cint_ti = __gen_cint_tn(mask);
 t1_ti = __emit_bin_bitor(blen, op2_ti, cint_ti);
 t2_ti = __emit_swap_sign(blen, t1_ti); 
 if (is_mod) t3_ti = __emit_sgn_mod(blen, op1_ti, t2_ti, is_2state);
 else  t3_ti = __emit_sgn_div(blen, op1_ti, t2_ti, is_2state);

 /* SJM 03-29-14 - only need swap sign (negate minus unary) if div */
 /* for mod, first op determines for div if either neg, result neg */
 if (!is_mod) t3_ti = __emit_swap_sign(blen, t3_ti); 

 __emit_copy(WRDBYTES, t3_ti, res_ti);
 __emit_jmp(zerob_mask_bbp);

 /* both operands positive */
 __start_bblk(both_pos_bbp);
 if (is_mod) val_ti = __emit_sgn_mod(blen, op1_ti, op2_ti, is_2state);
 else  val_ti = __emit_sgn_div(blen, op1_ti, op2_ti, is_2state);
 __emit_copy(WRDBYTES, val_ti, res_ti);
 /* result positve and no conversion of operands to positive */
 __emit_jmp(zerob_mask_bbp);

 /* mask a part and zero b */
 __start_bblk(zerob_mask_bbp);
 mask = __masktab[ubits_(blen)];
 mask_ti = __gen_cint_tn(mask);
 r1_ti = __emit_mask_and(res_ti, mask_ti);
 __emit_copy(WRDBYTES, r1_ti, res_ti);
 if (!is_2state)
  {
   res_bpti = __get_bpti(res_ti);
   __emit_store_cint(res_bpti, 0, WRDBYTES);
  }
 return(res_ti);
}

/*
 * gen insns for binary bit reducing and op
 */
static int32 gen_bin_bitredand(struct expr_t *ndp, int32 op1_ti, int32 op2_ti)
{
 int32 res_ti, res_bpti, blen;
 int32 op1_bpti, op2_bpti;
 int32 t1_ti, t2_ti, t3_ti, t4_ti, t5_ti;
 struct bblk_t *xz_bbp, *after_bbp, *op_bbp;

 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);
 /* notice result must go into non addr ptr pr tmp */
// ====> FIX SIGNED HANDLING HERE
 /* must copy result into a tmp */
 blen = ndp->szu.xclen;
 res_ti = __gen_tn(SR_VEC, blen);
#ifdef __XPROP__
 /* AIV 08/02/11 - if xprop do the following code */
 if (__inst_mod->m_use_xprop_and_or_x)
  {
   //rta = (op1a & op2a) | (op1b | op2b);
   //rtb = (op1b | op2b);
   t1_ti = __emit_bin_bitand(blen, op1_ti, op2_ti);
   t2_ti = __emit_bin_bitor(blen, op1_bpti, op2_bpti);
   t3_ti = __emit_bin_bitor(blen, t1_ti, t2_ti);

   __emit_copy(wlen_(blen)*WRDBYTES, t3_ti, res_ti);
   res_bpti = __get_bpti(res_ti);
   __emit_copy(wlen_(blen)*WRDBYTES, t2_ti, res_bpti);
   return(res_ti);
  } 
#endif

 op_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 after_bbp = __alloc_bblk(FALSE);
//AIV LOOKATME - 08/02/11 - think I tried this but is this faster without
//the jump just do the more complicated bcase for <= WBITS????
 res_bpti = __get_bpti(res_ti);
 __emit_jmpor_0(xz_bbp, op_bbp, op1_bpti, op2_bpti);
  
 __start_bblk(op_bbp);

 t2_ti = __emit_bin_bitor(blen, op1_ti, op1_bpti);
 t3_ti = __emit_bin_bitor(blen, op2_ti, op2_bpti);
 /* this is he x/z a part value */ 
 t1_ti = __emit_bin_bitand(blen, t2_ti, t3_ti);

 t4_ti = __emit_bin_bitor(blen, op1_bpti, op2_bpti);
 t5_ti = __emit_bin_bitand(blen, t1_ti, t4_ti);
 
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(wlen_(blen)*WRDBYTES, t1_ti, res_ti);
 __emit_copy(wlen_(blen)*WRDBYTES, t5_ti, res_bpti);
 __emit_jmp(after_bbp);

 __start_bblk(xz_bbp);
 t1_ti = __emit_bin_bitand(blen, op1_ti, op2_ti);
 __emit_copy(wlen_(blen)*WRDBYTES, t1_ti, res_ti);
 __emit_store_cint(res_bpti, 0, wlen_(blen)*WRDBYTES);
 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen insns for binary bit reducing or op
 */
static int32 gen_bin_bitredor(int32 op1_ti, int32 op2_ti)
{
 int32 res_ti, res_bpti, blen, blen2;
 int32 op1_bpti, op2_bpti;
 int32 t1_ti, t2_ti, t3_ti, t4_ti, t5_ti, t6_ti, or_ti, t8_ti;
 int32 save_blen1, save_blen2;
 struct bblk_t *xz_bbp, *after_bbp, *op_bbp;

 /* during exec result must always end up in same tmp no matter  */
 blen = __get_tnwid(op1_ti);
 /* AIV currently can't decompose wide case because it has internal loop */
 /* AIV 12/22/06 - need to or to the widest op1 can have different blen */
 /* for wide and wide does the masking to the larger blen */
 blen2 = __get_tnwid(op2_ti);
 if (blen2 > blen) blen = blen2;

 if (blen > WBITS)
  {
   res_ti = __emit_wid_bin_redor(blen, op1_ti, op2_ti);
   return(res_ti);
  }

 /* AIV 11/28/05 - if gets here know it is in a word so just make 32 bits */
 /* this is needed because wasn't masking in convert to scalar because */
 /* the result was 1 bit but was never masked at end of operations */
 /* AIV 11/05/09 - this needs to set result blen to actual length */
 /* was doint extra masking - also wlen removed always 1 here */
 res_ti = __gen_tn(SR_VEC, blen);
 blen = WBITS;
 res_bpti = __get_bpti(res_ti);

 /* AIV 08/19/08 - better to just change tmp length and put back */
 /* this works because never these tmps can never be evaled again */
 /* this prevents bitor from optimize width 1 or's away */
 /* don't do the move/copy here because this code uses a lot of regs */
 save_blen1 = __tntab[op1_ti].tnwid;
 save_blen2 = __tntab[op2_ti].tnwid;
 __tntab[op1_ti].tnwid = blen;
 __tntab[op2_ti].tnwid = blen;

 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);
 /* AIV 08/02/11 - if xprop do the following code */
#ifdef __XPROP__
 if (__inst_mod->m_use_xprop_and_or_x)
  {
   //rta = (op1a | op2a) | (op1b | op2b);
   //rtb = (op1b | op2b);
   t1_ti = __emit_bin_bitor(blen, op1_ti, op2_ti);
   t2_ti = __emit_bin_bitor(blen, op1_bpti, op2_bpti);
   t3_ti = __emit_bin_bitor(blen, t1_ti, t2_ti);

   __emit_copy(wlen_(blen)*WRDBYTES, t3_ti, res_ti);
   res_bpti = __get_bpti(res_ti);
   __emit_copy(wlen_(blen)*WRDBYTES, t2_ti, res_bpti);
   /* put back saved blens */
   __tntab[op1_ti].tnwid = save_blen1;
   __tntab[op2_ti].tnwid = save_blen2;
   return(res_ti);
  }
#endif

 op_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 after_bbp = __alloc_bblk(FALSE);

 or_ti = __emit_bin_bitor(blen, op2_ti, op1_ti);
 __emit_jmpor_0(op_bbp, xz_bbp, op1_bpti, op2_bpti);
 __start_bblk(xz_bbp);
 /* AIV 09/19/08 - rearranged this to reduce register pressure */
 /* better to do operations with op1/op2 which then frees the regs */
 /* that were used for each a/b part */
 /* rtb = op2b ^ op1b ^ ((op1a | op1b) & (op2b | (op2a & op1b))); */
 t2_ti = __emit_bin_bitand(blen, op2_ti, op1_bpti);
 t1_ti = __emit_bin_bitor(blen, op1_ti, op1_bpti);
 t5_ti = __emit_bin_bitxor(blen, op1_bpti, op2_bpti);
 t3_ti = __emit_bin_bitor(blen, t2_ti, op2_bpti);
 t4_ti = __emit_bin_bitand(blen, t1_ti, t3_ti);
 t6_ti = __emit_bin_bitxor(blen, t5_ti, t4_ti);
 __emit_copy(WRDBYTES, t6_ti, res_bpti);

 /* this becomes b part of result - but notice formal tmp created */
 t8_ti = __emit_bin_bitor(blen, t6_ti, or_ti);
 /* finally copy - need separate a and b part copies */
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, t8_ti, res_ti);

 __emit_jmp(after_bbp);

 __start_bblk(op_bbp);

 /* a part of wide non x/z result */
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, or_ti, res_ti);
 __emit_store_cint(res_bpti, 0, WRDBYTES);
 __start_bblk(after_bbp);

 /* put back saved blens */
 __tntab[op1_ti].tnwid = save_blen1;
 __tntab[op2_ti].tnwid = save_blen2;
 return(res_ti);
}

static int32 gen_bin_bitredor_try(int32 op1_ti, int32 op2_ti)
{
 int32 res_ti, res_bpti, blen, blen2;
 int32 op1_bpti, op2_bpti;
 int32 t1_ti, t2_ti, t3_ti, t4_ti, t5_ti, t6_ti, t7_ti, t8_ti;
 int32 save_blen1, save_blen2;

 /* during exec result must always end up in same tmp no matter  */
 blen = __get_tnwid(op1_ti);
 /* AIV currently can't decompose wide case because it has internal loop */
 /* AIV 12/22/06 - need to or to the widest op1 can have different blen */
 /* for wide and wide does the masking to the larger blen */
 blen2 = __get_tnwid(op2_ti);
 if (blen2 > blen) blen = blen2;

 if (blen > WBITS)
  {
   res_ti = __emit_wid_bin_redor(blen, op1_ti, op2_ti);
   return(res_ti);
  }

 /* AIV 11/28/05 - if gets here know it is in a word so just make 32 bits */
 /* this is needed because wasn't masking in convert to scalar because */
 /* the result was 1 bit but was never masked at end of operations */
 /* AIV 11/05/09 - this needs to set result blen to actual length */
 /* was doint extra masking - also wlen removed always 1 here */
 res_ti = __gen_tn(SR_VEC, blen);
 blen = WBITS;
 res_bpti = __get_bpti(res_ti);

 /* AIV 08/19/08 - better to just change tmp length and put back */
 /* this works because never these tmps can never be evaled again */
 /* this prevents bitor from optimize width 1 or's away */
 /* don't do the move/copy here because this code uses a lot of regs */
 save_blen1 = __tntab[op1_ti].tnwid;
 save_blen2 = __tntab[op2_ti].tnwid;
 __tntab[op1_ti].tnwid = blen;
 __tntab[op2_ti].tnwid = blen;

 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);
 /* AIV 09/19/08 - rearranged this to reduce register pressure */
 /* better to do operations with op1/op2 which then frees the regs */
 /* that were used for each a/b part */
 /* rtb = op2b ^ op1b ^ ((op1a | op1b) & (op2b | (op2a & op1b))); */
 t2_ti = __emit_bin_bitand(blen, op2_ti, op1_bpti);
 t7_ti = __emit_bin_bitor(blen, op2_ti, op1_ti);
 t1_ti = __emit_bin_bitor(blen, op1_ti, op1_bpti);
 t5_ti = __emit_bin_bitxor(blen, op1_bpti, op2_bpti);
 t3_ti = __emit_bin_bitor(blen, t2_ti, op2_bpti);
 t4_ti = __emit_bin_bitand(blen, t1_ti, t3_ti);
 t6_ti = __emit_bin_bitxor(blen, t5_ti, t4_ti);
 __emit_copy(WRDBYTES, t6_ti, res_bpti);

 /* this becomes b part of result - but notice formal tmp created */
 t8_ti = __emit_bin_bitor(blen, t6_ti, t7_ti);
 
 /* finally copy - need separate a and b part copies */
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, t8_ti, res_ti);

 /* put back saved blens */
 __tntab[op1_ti].tnwid = save_blen1;
 __tntab[op2_ti].tnwid = save_blen2;
 return(res_ti);
}



/*
 * gen insns for binary bit reducing xor op
 */
static int32 gen_bin_bitredxor(struct expr_t *ndp, int32 op1_ti, int32 op2_ti)
{
 int32 res_ti, res_bpti, t1_ti, op1_bpti, op2_bpti;
 int32 t2_ti, t3_ti, blen;
 struct bblk_t *xz_bbp, *after_bbp, *op_bbp;

 blen = ndp->szu.xclen;
 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);
 /* must copy result into a tmp */
 res_ti = __gen_tn(SR_VEC, blen);
 res_bpti = __get_bpti(res_ti);

 /* AIV 11/23/09 - if narrow better to just inline instead of doing the */
 /* jmp or of the b part */
 if (blen > WBITS)
  {
   op_bbp = __alloc_bblk(FALSE);
   xz_bbp = __alloc_bblk(TRUE);
   after_bbp = __alloc_bblk(FALSE);

   __emit_jmpor_0(op_bbp, xz_bbp, op1_bpti, op2_bpti);
   __start_bblk(xz_bbp);

   /* rtb = op1b | op2b; */ 
   t2_ti = __emit_bin_bitor(blen, op1_bpti, op2_bpti);

   /* rta = rtb | (op1a ^ op2a); */ 
   t3_ti = __emit_bin_bitxor(blen, op1_ti, op2_ti);
   t1_ti = __emit_bin_bitor(blen, t2_ti, t3_ti);

   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(wlen_(blen)*WRDBYTES, t1_ti, res_ti);

   __emit_copy(wlen_(blen)*WRDBYTES, t2_ti, res_bpti);
   __emit_jmp(after_bbp);

   __start_bblk(op_bbp);
   t1_ti = __emit_bin_bitxor(blen, op1_ti, op2_ti);

   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(wlen_(blen)*WRDBYTES, t1_ti, res_ti);
   /* zero the b part */
   __emit_store_cint(res_bpti, 0, wlen_(blen)*WRDBYTES);
   __start_bblk(after_bbp);
  }
 else
  {
   /* rtb = op1b | op2b; */ 
   t2_ti = __emit_bin_bitor(blen, op1_bpti, op2_bpti);
   t3_ti = __emit_bin_bitxor(blen, op1_ti, op2_ti);

   /* rta = rtb | (op1a ^ op2a); */ 
   t1_ti = __emit_bin_bitor(blen, t2_ti, t3_ti);

   /* notice copies follow gas movl [from],[to] format */
   __emit_copy(WRDBYTES, t1_ti, res_ti);
   __emit_copy(WRDBYTES, t2_ti, res_bpti);
  }

 return(res_ti);
}

/*
 * gen insns for binary bit reducing xnor op
 */
static int32 gen_bin_bitredxnor(struct expr_t *ndp, int32 op1_ti, 
 int32 op2_ti)
{
 int32 res_ti, res_bpti, op1_bpti, op2_bpti, blen;
 int32 t1_ti, t2_ti, t3_ti, t4_ti, r1_ti, mask_ti;
 word32 mask;

 blen = ndp->szu.xclen;
 /* AIV currently can't decompose wide case because it has internal loop */
 /* which checks each b part */
 if (blen > WBITS)
  {
   res_ti = __emit_wid_bin_redxnor(blen, op1_ti, op2_ti, FALSE);
   return(res_ti);
  }
 
 /* AIV 11/23/09 - if narrow better to just inline instead of doing the */
 /* jmp or of the b part */
 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);
 /* notice result must go into non addr ptr pr tmp */
 // ====> FIX SIGNED HANDLING HERE

 /* must copy result into a tmp */
 res_ti = __gen_tn(SR_VEC, blen);
 res_bpti = __get_bpti(res_ti);

 t2_ti = __emit_bin_bitxor(blen, op1_ti, op2_ti);
 t3_ti = __emit_bitnot(blen, t2_ti);
 t4_ti = __emit_bin_bitor(blen, op1_bpti, op2_bpti);
 t1_ti = __emit_bin_bitor(blen, t4_ti, t3_ti);
 if (ubits_(blen) != 0)
  {
   mask = __masktab[ubits_(blen)];
   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(t1_ti, mask_ti);
  }
 else r1_ti = t1_ti;

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, r1_ti, res_ti);
 __emit_copy(WRDBYTES, t4_ti, res_bpti);
 return(res_ti);
}

/*
 * 2-state XNOR version
 * rta = ~(op1a ^ op2a) & mask;
 */
static int32 gen_bin_bitredxnor_2state(struct expr_t *ndp, int32 op1_ti, 
 int32 op2_ti, int32 srtyp)
{
 int32 res_ti, blen;
 int32 t1_ti, t2_ti, r1_ti, mask_ti;
 word32 mask;

 blen = ndp->szu.xclen;
//AIV 2STATE - this isn't true for 2-state could decompose 
 /* AIV currently can't decompose wide case because it has internal loop */
 /* which checks each b part */
 if (blen > WBITS)
  {
   res_ti = __emit_wid_bin_redxnor(blen, op1_ti, op2_ti, TRUE);
   return(res_ti);
  }
 
 /* must copy result into a tmp */
 res_ti = __gen_tn(srtyp, blen);

 t1_ti = __emit_bin_bitxor(blen, op1_ti, op2_ti);
 t2_ti = __emit_bitnot(blen, t1_ti);

 if (ubits_(blen) != 0)
  {
   mask = __masktab[ubits_(blen)];
   mask_ti = __gen_cint_tn(mask);
   r1_ti = __emit_mask_and(t2_ti, mask_ti);
  }
 else r1_ti = t2_ti;

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(WRDBYTES, r1_ti, res_ti);
 return(res_ti);
}

/*
 * gen insns for binary relation compare insns (not for equals)
 */
static int32 gen_bin_relcomp(struct expr_t *ndp, int32 op1_ti, int32 op2_ti,
 int32 srtyp)
{
 int32 cc, blen, cint_ti, val, is_2state;
 int32 res_ti, op1_bpti, op2_bpti;
 struct bblk_t *op_bbp, *after_bbp;

 res_ti = __gen_tn(srtyp, 1);

 is_2state = (srtyp == SR_SCAL2S);
 /* AIV 11/20/06 - if either operands have are constant with x return x */
 /* if 2-state this can never be true */
 if (!is_2state)
  {
   if (has_contant_xvalue(res_ti, op1_ti, op2_ti))
    {
     return(res_ti);
    }
  }

 /* AIV 12/01/05 - if need signed and fits is one word must shift left */
 /* idea is that op is less that wbits shift high bits to the left to make */
 /* word bit signed and do a regular signed word compare */
 /* AIV 01/16/06 - LOOKATME - still not sure about this but must shift by */
 /* the max blen amount to do the x86 compare */
 blen = __get_tnwid(op1_ti);
 if (blen < __get_tnwid(op2_ti)) blen = __get_tnwid(op2_ti);

 /* if wide do normal wide compare */
 if (blen > WBITS)
  {
   return(gen_bin_relcomp_wide(ndp, op1_ti, op2_ti, srtyp));
  }

 after_bbp = NULL;
 if (!is_2state)
  {
   op1_bpti = __get_bpti(op1_ti);
   op2_bpti = __get_bpti(op2_ti);

   after_bbp = __alloc_bblk(FALSE);
   op_bbp = __alloc_bblk(FALSE);

   /* if either b part has any x/z bit, result is x */ 
   __emit_store_cint(res_ti, 3, WRDBYTES);
   __emit_jmpor_0(op_bbp, after_bbp, op1_bpti, op2_bpti);
   /* for wide will need wrapper since complex but without x/z test */
   __start_bblk(op_bbp);
  }
 else __emit_store_cint(res_ti, 0, WRDBYTES);

 /* SJM 06/19/04 - LOOKATME - realy only need 2 and reverse sense */ 
 cc = CC_UNKN;
 switch (ndp->optyp) {
  case RELGE: cc = CC_JGE; break;
  case RELGT: cc = CC_JGT; break;
  case RELLE: cc = CC_JLE; break;
  case RELLT: cc = CC_JLT; break;
  default: __case_terr(__FILE__, __LINE__);
 }

 if (ndp->rel_ndssign && blen < WBITS)
  {
   cint_ti = __gen_cint_tn(WBITS - blen);
   op1_ti = __emit_shiftl(WBITS, cint_ti, op1_ti);
   op2_ti = __emit_shiftl(WBITS, cint_ti, op2_ti);
  }

 /* AIV 12/15/09 - check to compare if constant is known to be in or out */
 /* of range due to the width of the variable compare */
 /* if known just set value */
 /* AIV 11/18/10 - this was bug if signed compare and WBITS - can not */
 /* do a compare of unsigned values - in chk_jmp_cmp_ops */
 if (ndp->rel_ndssign && blen == WBITS) val = -1;
 else val = __chk_jmp_cmp_ops(op1_ti, op2_ti, cc);
 
 if (val != -1)
  {
   if (val) __emit_store_cint(res_ti, 1, WRDBYTES);
   else __emit_store_cint(res_ti, 0, WRDBYTES);
   if (!is_2state) __start_bblk(after_bbp);
   return(res_ti); 
  }

 /* get the value set via set instructions condition codes */
 __emit_cmp_set_type(op1_ti, op2_ti, cc, ndp->rel_ndssign, res_ti);
 if (!is_2state) __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * do a wide compare
 */
static int32 gen_bin_relcomp_wide(struct expr_t *ndp, int32 op1_ti, 
 int32 op2_ti, int32 srtyp)
{
 int32 cc, res_ti, op1_bpti, op2_bpti, is_2state;
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp, *t_bbp, *f_bbp;

 res_ti = __gen_tn(srtyp, 1);

 is_2state = (srtyp == SR_SCAL2S);

 t_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 if (!is_2state)
  {
   op1_bpti = __get_bpti(op1_ti);
   op2_bpti = __get_bpti(op2_ti);

   op_bbp = __alloc_bblk(FALSE);
   xz_bbp = __alloc_bblk(TRUE);
   /* if either b part has any x/z bit, result is x */ 
   __emit_jmpor_0(op_bbp, xz_bbp, op1_bpti, op2_bpti);

   __start_bblk(xz_bbp);
   __emit_store_cint(res_ti, 3, WRDBYTES);

   __emit_jmp(after_bbp);

   /* for wide will need wrapper since complex but without x/z test */
   __start_bblk(op_bbp);
  }

 /* SJM 06/19/04 - LOOKATME - realy only need 2 and reverse sense */ 
 cc = CC_UNKN;
 switch (ndp->optyp) {
  case RELGE: cc = CC_JGE; break;
  case RELGT: cc = CC_JGT; break;
  case RELLE: cc = CC_JLE; break;
  case RELLT: cc = CC_JLT; break;
  default: __case_terr(__FILE__, __LINE__);
 }

 /* AIV 12/01/05 - if need signed and fits is one word must shift left */
 /* idea is that op is less that wbits shift high bits to the left to make */
 /* word bit signed and do a regular signed word compare */
 /* AIV 01/16/06 - LOOKATME - still not sure about this but must shift by */
 /* the max blen amount to do the x86 compare */
 if (ndp->rel_ndssign)
  {
   __emit_jmp_sgn_cmp(t_bbp, f_bbp, op1_ti, op2_ti, cc);
  }
 else
  {
   __emit_jmp_cmp(t_bbp, f_bbp, op1_ti, op2_ti, cc);
  }

 /* AIV FIXME - could skip these blocks if wide jmp compare just return value */
 __start_bblk(t_bbp);
 __emit_store_cint(res_ti, 1, WRDBYTES);
 __emit_jmp(after_bbp);

 __start_bblk(f_bbp);
 __emit_store_cint(res_ti, 0, WRDBYTES);
 __start_bblk(after_bbp);
 return(res_ti);
}


/*
 * if either operand has a constant with in x put a x in the res_ti
 * used for if (a == constant) check if constant has an x value
 */
static int32 has_contant_xvalue(int32 res_ti, int32 op1_ti, int32 op2_ti)
{
 int32 op1_bpti, op2_bpti, con_ti, blen, xvi;
 word32 bval;
 struct tn_t *contnp;

 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);

 if (__is_constant(op1_bpti)) con_ti = op1_bpti;
 else if (__is_constant(op2_bpti)) con_ti = op2_bpti;
 else con_ti = -1;

 if (con_ti != -1)
  {
   blen = __get_tnwid(con_ti);
   if (blen <= WBITS)
    {
     bval = __get_wrd_con_val(con_ti);
     if (bval != 0)
      {
       __emit_store_cint(res_ti, 3, WRDBYTES);
       return(TRUE);
      }
    }
   else
    {
     contnp = &(__tntab[con_ti]);
     /* DBG remove -- */
     if (contnp->comlab_typ != COMLAB_CONADR) __misc_terr(__FILE__, __LINE__);
     /* -- */
     xvi = __get_con_adradd_xvi(con_ti);
     /* check the b part if non zero, compare is unknown (x) */
     /* AIV 11/02/07 - this was passing wlen should be blen */
     if (!vval_is0_(&(__contab[xvi]), blen))
      {
       __emit_store_cint(res_ti, 3, WRDBYTES);
       return(TRUE);
      }
    }
  }
 return(FALSE);
}


/*
 * gen insns for binary real relation compare insns (not for equals)
 */
static int32 gen_bin_real_relcomp(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti)
{
 int32 res_ti, cc;
 struct bblk_t *t_bbp, *after_bbp;

 res_ti = __gen_tn(SR_SCAL, 1);

 t_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* just simple converts to real hear */
 if (ndp->lu.x->cnvt_to_real)
  {
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, WBITS, TRUE,
    TRUE, FALSE);
  }
 if (ndp->ru.x->cnvt_to_real)
  {
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, WBITS, TRUE, TRUE,
    FALSE);
  }
  
 cc = CC_UNKN;
 switch (ndp->optyp) {
  case REALRELGE: cc = CC_JGE; break;
  case REALRELGT: cc = CC_JGT; break;
  case REALRELLE: cc = CC_JLE; break;
  case REALRELLT: cc = CC_JLT; break;
  case REALRELEQ: cc = CC_JE; break;
  case REALRELNEQ: cc = CC_JNE; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 /* AIV 09/13/10 - better to just set to zero and jump to done if FALSE */
 /* than jump to extra false block */
 __emit_store_cint(res_ti, 0, WRDBYTES);
 __emit_jmp_real_cmp(t_bbp, after_bbp, op1_ti, op2_ti, cc);

 __start_bblk(t_bbp);
 __emit_store_cint(res_ti, 1, WRDBYTES);
 __emit_jmp(after_bbp);


 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen insns for binary relation eq/ne (not for ceq/cne)
 *
 * computes ne and inverts result for eq
 */
static int32 gen_bin_neeq(struct expr_t *ndp, int32 op1_ti, int32 op2_ti)
{
 int32 opwid, wid1, wid2; 
 int32 res_ti, op1_bpti, op2_bpti, t1_ti, t2_ti, t3_ti;
 word32 bval;
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp;

 wid1 = __get_tnwid(op1_ti);
 wid2 = __get_tnwid(op2_ti);
 /* must convert operand size if needed before compare */
 /* AIV 12/20/06 - need exact size here for conversions - mask narrow */
 if (wid2 > wid1) opwid = wid2;
 else opwid = wid1;

 /* if wide handle wide case */
 if (opwid > WBITS) 
  {
   return(gen_bin_neeq_wide(ndp, op1_ti, op2_ti, opwid));
  }

 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, opwid, ndp->rel_ndssign,
    FALSE, TRUE);
 op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, opwid, ndp->rel_ndssign,
    FALSE, TRUE);

 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);

 res_ti = __gen_tn(SR_SCAL, 1);

 after_bbp = NULL;
 t1_ti = __emit_bin_bitor(opwid, op1_bpti, op2_bpti);
 bval = 0;
 /* if bpart is known do one part of the calculation */
 if (__is_constant(t1_ti)) 
  {
   bval = __get_wrd_con_val(t1_ti);
   /* bpart is 0 just do regular compare */
   if (bval == 0) 
    {
     /* AIV 01/22/09 - need to zero the high part if jump to set byte */
     __emit_store_cint(res_ti, 0, WRDBYTES);
     goto do_op;
    }
   else
    {
     /* known not to be zero bpart is x */
     __emit_store_cint(res_ti, 3, WRDBYTES);
     return(res_ti);
    }
  }
 after_bbp = __alloc_bblk(FALSE);
 op_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 __emit_jmp_0(op_bbp, xz_bbp, t1_ti);

 /* has x/z */
 __start_bblk(xz_bbp);

 /* LOOKATME - think can get rid of the b setting to 0 here */
 /* F if result x, else compute != on non x/z bits */
 /* know both opands widened to widest */
 /* formula is t1 is xzmask | more mask with each a part then check for = */
 /* LOOKATME - for narrow better to xor and cmp once - but not for wide */
 /* pre-lowered insns for wide for loop and handles missing b parts */
 t2_ti = __emit_bin_bitor(opwid, op1_ti, t1_ti);
 t3_ti = __emit_bin_bitor(opwid, op2_ti, t1_ti);
 /* result x/z */
 /* AIV 12/15/09 - move res_ti here and to no xz block for better */
 /* register range */
 __emit_store_cint(res_ti, 3, WRDBYTES);
 /* need a/b in contab const for 1 bit a/b x */
 __emit_jmp_eq(after_bbp, op_bbp, t2_ti, t3_ti);

 /* for wide will need wrapper since complex but without x/z test */
 __start_bblk(op_bbp);

do_op:
 /* know b parts 0 or will not get here */
 /* AIV 01/22/09 - no need for the movzbl high part zero from init 0 here */
 __emit_store_cint(res_ti, 0, WRDBYTES);
 __emit_cmp(op1_ti, op2_ti);

 if (ndp->optyp == RELNEQ) __emit_st_sete(CC_JNE, res_ti);
 else __emit_st_sete(CC_JE, res_ti);
 
 if (after_bbp != NULL)
  {
   __emit_jmp(after_bbp);
   __start_bblk(after_bbp);
  }
 return(res_ti);
}

/*
 * 2-state
 */
static int32 gen_bin_neeq_2state(struct expr_t *ndp, int32 op1_ti, int32 op2_ti)
{
 int32 opwid, wid1, wid2, srtyp, res_ti, t1_ti, is_ne; 

 wid1 = __get_tnwid(op1_ti);
 wid2 = __get_tnwid(op2_ti);
 /* must convert operand size if needed before compare */
 /* AIV 12/20/06 - need exact size here for conversions - mask narrow */
 if (wid2 > wid1) opwid = wid2;
 else opwid = wid1;

 /* if wide handle wide case */
 if (opwid == 1) srtyp = SR_SCAL2S;
 else srtyp = SR_BIT2S;

 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, srtyp, opwid, ndp->rel_ndssign,
    FALSE, TRUE);
 op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, srtyp, opwid, ndp->rel_ndssign,
    FALSE, TRUE);
 res_ti = __gen_tn(SR_SCAL2S, 1);
 __emit_store_cint(res_ti, 0, WRDBYTES);
 is_ne = (ndp->optyp == RELNEQ || ndp->optyp == RELCNEQ);
 if (opwid > WBITS) 
  {
   t1_ti = __emit_cmp_wide(op1_ti, op2_ti, wlen_(opwid), is_ne, SR_SCAL2S);
   __emit_copy(WRDBYTES, t1_ti, res_ti);
   return(res_ti);
  }

 __emit_cmp(op1_ti, op2_ti);
 if (is_ne) __emit_st_sete(CC_JNE, res_ti);
 else __emit_st_sete(CC_JE, res_ti);
 return(res_ti);
}

/*
 * gen insns for wide binary relation eq/ne (not for ceq/cne)
 */
static int32 gen_bin_neeq_wide(struct expr_t *ndp, int32 op1_ti, int32 op2_ti, 
 int32 opwid)
{
 int32 res_ti, t1_ti, op1_bpti, op2_bpti, cond_ti;
 struct bblk_t *op_bbp, *xz_bbp, *after_bbp;

 op_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 after_bbp = __alloc_bblk(FALSE);

 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, opwid, ndp->rel_ndssign,
    FALSE, TRUE);
 op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, opwid, ndp->rel_ndssign,
    FALSE, TRUE);

 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);

 /* LOOKATME - for narrow better to xor and cmp once - but not for wide */
 /* pre-lowered insns for wide for loop and handles missing b parts */
 __emit_jmpor_0(op_bbp, xz_bbp, op1_bpti, op2_bpti);

 /* has x/z */
 __start_bblk(xz_bbp);

 /* LOOKATME - think can get rid of the b setting to 0 here */
 /* F if result x, else compute != on non x/z bits */
 
 cond_ti = __emit_cmp_widomitxz_ne(op1_ti, op2_ti);
 res_ti = __gen_tn(SR_SCAL, 1);
 /* need a/b in contab const for 1 bit a/b x */
 __emit_store_cint(res_ti, 3, WRDBYTES);
 __emit_jmp_0(op_bbp, after_bbp, cond_ti);

 /* for wide will need wrapper since complex but without x/z test */
 __start_bblk(op_bbp);
 t1_ti = __emit_cmp_wide(op1_ti, op2_ti, wlen_(opwid), (ndp->optyp == RELNEQ), 
   SR_SCAL);
 __emit_copy(WRDBYTES, t1_ti, res_ti);
 __emit_jmp(after_bbp);

 /* zero the bpart */ 
 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen insns for binary relation ceq/cne
 *
 * computes cne and inverts result for ceq
 */
static int32 gen_bin_cneeq(struct expr_t *ndp, int32 op1_ti, int32 op2_ti)
{
 int32 op1_bpti, op2_bpti, op1wid, op2wid, opwid, wlen;
 int32 t1_ti, t2_ti, t3_ti, res_ti;

 op1wid = __get_tnwid(op1_ti);
 op2wid = __get_tnwid(op2_ti);
 if (op1wid > op2wid) opwid = op1wid;
 else opwid = op2wid;
 
 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, opwid,
    ndp->rel_ndssign, FALSE, FALSE);
 op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, opwid,
    ndp->rel_ndssign, FALSE, FALSE);

 /* if wide just call wrapper to do the compare */
 if (opwid > WBITS)
  {
   wlen = 2*(wlen_(__get_tnwid(op1_ti)));
   res_ti = __emit_cmp_wide(op1_ti, op2_ti, wlen, (ndp->optyp == RELCNEQ),
    SR_SCAL);
   return(res_ti);
  }

 t1_ti = __emit_bin_bitxor(opwid, op1_ti, op2_ti);
 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);
 t2_ti = __emit_bin_bitxor(opwid, op1_bpti, op2_bpti);
 t3_ti = __emit_bin_bitor(opwid, t1_ti, t2_ti);
 res_ti = __gen_tn(SR_SCAL, 1);
 __emit_store_cint(res_ti, 0, WRDBYTES);
 __emit_testl(t3_ti);

 /* AIV 01/22/09 - no need for the movzbl high part zero from init above */
 if (ndp->optyp == RELCNEQ) __emit_st_sete(CC_JNE, res_ti);
 else __emit_st_sete(CC_JE, res_ti);
 return(res_ti);
}

/*
 * gen insns for binary bool and
 *
 * this just uses each operands width - no size chges
 * AIV 10/27/08 - rewrote this to only evaluate the second expr if the 
 * first is true
 */
static int32 gen_bin_booland(struct expr_t *ndp)
{
 int32 tmp1_ti, tmp2_ti, res_ti, cint_ti, srtyp, srtyp2, is_scalar;
 int32 op1_ti, op2_ti, op1_bpti, op2_bpti, t1_ti, t2_ti, t3_ti;
 int32 is_op1_2state, has_bpart, need_xprop;
 struct bblk_t *tmp1_not0_bbp, *tmp2_not0_bbp;
 struct bblk_t *xz_bbp, *after_bbp;
 struct expr_t *lhsx, *rhsx;
 word32 val1, val2;

 lhsx = ndp->lu.x;
 rhsx = ndp->ru.x;
 /* if both widths are one handle as scalar */
 op1_ti = __gen_expr_eval(lhsx, -1);
 is_op1_2state = __tmp_is_2state(op1_ti);
 if (is_op1_2state)
  {
   return(gen_bin_booland_2state(ndp, op1_ti));
  }

 if (lhsx->szu.xclen == 1 && rhsx->szu.xclen == 1)
  {
//AIV FIXME - this should evaluate the second if it is not a leaf
//could be a complicate expression which does not need to be evaluated
   op2_ti = __gen_expr_eval(rhsx, -1);
   srtyp = __tntab[op1_ti].srtyp;
   srtyp2 = __tntab[op2_ti].srtyp;
   res_ti = gen_scalar_binop(BOOLAND, op1_ti, op2_ti, srtyp, srtyp2);
   return(res_ti);
  }

 /* if either operand is constant handle as special case */
 /* do the conversion of op1 and op2 in this routine in needed */

 /* only need to convert is strength vector */
 op1_bpti = op2_bpti = -1;
 srtyp = __tntab[op1_ti].srtyp;
 is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
 if (!is_scalar)
  {
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, __tntab[op1_ti].tnwid, 
    FALSE, FALSE, FALSE); 
   op1_bpti = __get_bpti(op1_ti);
  }
#ifdef __XPROP__
 need_xprop = __inst_mod->m_use_xprop_and_or_x;
#else
 need_xprop = FALSE;
#endif

 res_ti = __gen_tn(SR_SCAL, 1);
 val1 = val2 = 0xffffffff;
 op2_ti = -1;
 if (__is_constant(op1_ti)) 
  {
   val1 = fold_constant_bin_cvt_bool(op1_ti, op1_bpti, need_xprop, &has_bpart);
   /* AIV 08/03/11 - if constant x just set to x and return */
   if (has_bpart) 
    {
     __emit_store_cint(res_ti, 3, WRDBYTES);
     return(res_ti);
    }
   /* if value is zero - no need to check other operand value is FALSE */
   if (val1 == 0)
    {
     /* if xprop still need to check other operand */
     if (need_xprop)
      {
       op2_ti = __gen_expr_eval(rhsx, -1);
       ifx_setx_else_const(op2_ti, 0, res_ti);
       return(res_ti);
      }
     __emit_store_cint(res_ti, 0, WRDBYTES);
     return(res_ti);
    }
   tmp1_ti = __gen_cint_tn(val1);
   tmp2_not0_bbp = __alloc_bblk(FALSE);
   after_bbp = __alloc_bblk(FALSE);
   xz_bbp = __alloc_bblk(TRUE);
   __emit_store_cint(res_ti, 0, WRDBYTES);
   goto check_op2;
  }
 /* AIV 04/23/09 - this cannot use regular __is_const_expr need special */
 /* handling for IS params which __cvc_is_const_expr does */
 else if (__cvc_is_const_expr(rhsx))
  {
   op2_ti = __gen_expr_eval(rhsx, -1);
   srtyp = __tntab[op2_ti].srtyp;
   is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
   if (!is_scalar)
    {
     op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
      FALSE, FALSE, FALSE); 
     op2_bpti = __get_bpti(op2_ti);
    }
   val2 = fold_constant_bin_cvt_bool(op2_ti, op2_bpti, need_xprop, &has_bpart);
   /* AIV 08/03/11 - if constant x just set to x and return */
   if (has_bpart) 
    {
     __emit_store_cint(res_ti, 3, WRDBYTES);
     return(res_ti);
    }
   /* if value is zero - no need to check other operand value is FALSE */
   if (val2 == 0)
    {
     /* still need to check other operand */
     if (need_xprop)
      {
       ifx_setx_else_const(op1_ti, 0, res_ti);
       return(res_ti);
      }
     __emit_store_cint(res_ti, 0, WRDBYTES);
     return(res_ti);
    }
   tmp2_ti = gen_bin_cvt_bool(op1_ti, op1_bpti);
   tmp1_ti = __gen_cint_tn(val2);
   tmp2_not0_bbp = __alloc_bblk(FALSE);
   after_bbp = __alloc_bblk(FALSE);
   xz_bbp = __alloc_bblk(TRUE);
   __emit_store_cint(res_ti, 0, WRDBYTES);
   goto check_op2_const;
  }

 op2_ti = -1;
 /* AIV 08/03/11 - if either is x/z - must return x */
 after_bbp = NULL;
 if (need_xprop)
  {
   struct bblk_t *regular_bbp, *xz_check_bbp;

   after_bbp = __alloc_bblk(FALSE);
   regular_bbp = __alloc_bblk(FALSE);
   xz_check_bbp = __alloc_bblk(TRUE);

   /* eval both operands and check for x/z set */
   op2_ti = __gen_expr_eval(rhsx, -1);
   srtyp = __tntab[op2_ti].srtyp;
   if (srtyp != SR_VEC)
    {
     op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
      FALSE, FALSE, FALSE); 
    }
   op2_bpti = __get_bpti(op2_ti);
   if (op1_bpti == -1)
    {
     srtyp = __tntab[op1_ti].srtyp;
     is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
     if (srtyp != SR_VEC)
      {
       op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, __tntab[op1_ti].tnwid, 
        FALSE, FALSE, FALSE); 
      }
     op1_bpti = __get_bpti(op1_ti);
    }
   /* if x/z return x otherwise of normal op */
   __emit_jmpor_0(regular_bbp, xz_check_bbp, op1_bpti, op2_bpti);
   __start_bblk(xz_check_bbp);
   __emit_store_cint(res_ti, 3, WRDBYTES);
   __emit_jmp(after_bbp);
   __start_bblk(regular_bbp);
  }

 if (after_bbp == NULL)
  after_bbp = __alloc_bblk(FALSE);
 tmp2_not0_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 tmp1_not0_bbp = __alloc_bblk(FALSE);
 tmp1_ti = gen_bin_cvt_bool(op1_ti, op1_bpti);
 __emit_store_cint(res_ti, 0, WRDBYTES);
 __emit_jmp_0(after_bbp, tmp1_not0_bbp, tmp1_ti);

 __start_bblk(tmp1_not0_bbp);

check_op2:
 if (op2_ti == -1)
  {
   op2_ti = __gen_expr_eval(rhsx, -1);
   
   srtyp = __tntab[op2_ti].srtyp;
   is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
   if (!is_scalar)
    {
     op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
      FALSE, FALSE, FALSE); 
     op2_bpti = __get_bpti(op2_ti);
    }
  }

 tmp2_ti = gen_bin_cvt_bool(op2_ti, op2_bpti);
check_op2_const:
 __emit_jmp_0(after_bbp, tmp2_not0_bbp, tmp2_ti);

 /* if get here know convert isn't 0 of either so only need to check for */
 /* value of 3 in either tmp1_ti or tmp2_ti - just check the second bit */
 __start_bblk(tmp2_not0_bbp);
 cint_ti = __gen_cint_tn(2);
 t1_ti = __emit_bin_bitand(WBITS, cint_ti, tmp1_ti);
 t2_ti = __emit_bin_bitand(WBITS, cint_ti, tmp2_ti);
 t3_ti = __emit_bin_bitor(WBITS, t1_ti, t2_ti);
 __emit_store_cint(res_ti, 1, WRDBYTES);
 __emit_jmp_0(after_bbp, xz_bbp, t3_ti);

 __start_bblk(xz_bbp);
 __emit_store_cint(res_ti, 3, WRDBYTES);
 __emit_jmp(after_bbp);

 /* this inserts the uncond jmp if needed */ 
 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * xprop code
 * if (op_ti has bpart)
 *  res_ti = 3;
 * else res_ti = val_const;
 */
static void ifx_setx_else_const(int32 op_ti, int32 val, int32 res_ti)
{
 int32 is_scalar, srtyp, op_bpti, cint_ti, save_blen;
 struct bblk_t *after_bbp, *assign_bbp;

 /* DBG remove -- */
 if (op_ti == -1) __misc_terr(__FILE__, __LINE__);
 /* -- */

 srtyp = __tntab[op_ti].srtyp;
 is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
 after_bbp = __alloc_bblk(FALSE);
 assign_bbp = __alloc_bblk(FALSE);
 /* init to x */
 __emit_store_cint(res_ti, 3, WRDBYTES);
 if (is_scalar)
  {
   /* need to mask if strength */
   if (srtyp == SR_SSCAL)
    {
     cint_ti = __gen_cint_tn(3);
     op_ti = __emit_bin_bitand(WBITS, cint_ti, op_ti);
    }
   cint_ti = __gen_cint_tn(2);
   /* need to save/restore and set width to WBITS otherwise will see */
   /* as one bit compare to 2 which gets optimized away */
   save_blen = __tntab[op_ti].tnwid;
   __tntab[op_ti].tnwid = WBITS;
   __emit_jmp_cmp(after_bbp, assign_bbp, op_ti, cint_ti, CC_JGE);
   __tntab[op_ti].tnwid = save_blen;
   __start_bblk(assign_bbp);
   __emit_store_cint(res_ti, val, WRDBYTES);
   __emit_jmp(after_bbp);
  }
 else
  {
   op_ti = __gen_cnvt_srep_ifneeded(op_ti, SR_VEC, __tntab[op_ti].tnwid, 
    FALSE, FALSE, FALSE); 
   op_bpti = __get_bpti(op_ti);

   __emit_jmp_0(assign_bbp, after_bbp, op_bpti);
   __start_bblk(assign_bbp);
   __emit_store_cint(res_ti, val, WRDBYTES);
   __emit_jmp(after_bbp);
  }
 __start_bblk(after_bbp);
}

/*
 * 2-state booland - op1_ti is known to be 2-state 
 */
static int32 gen_bin_booland_2state(struct expr_t *ndp, int32 op1_ti)
{
 int32 tmp1_ti, tmp2_ti, res_ti, srtyp, srtyp2, is_scalar;
 int32 op2_ti, op2_bpti, t1_ti; 
 int32 is_op2_2state, is_wide;
 struct bblk_t *done_bbp, *op2_bbp, *no_op2_xz_bbp, *t_bbp, *f_bbp;
 struct expr_t *lhsx, *rhsx;

 lhsx = ndp->lu.x;
 rhsx = ndp->ru.x;
 if (lhsx->szu.xclen == 1 && rhsx->szu.xclen == 1)
  {
   op2_ti = __gen_expr_eval(ndp->ru.x, -1);
   is_op2_2state = (__tmp_is_2state(op2_ti) || 
                  __is_constant_with_zero_bpart(op2_ti));
   if (is_op2_2state)
    {
     res_ti = __gen_tn(SR_SCAL2S, 1);
     t1_ti = __emit_bin_bitand(WBITS, op1_ti, op2_ti);
     __emit_copy(WRDBYTES, t1_ti, res_ti);
     return(res_ti);
    }
   srtyp = __tntab[op1_ti].srtyp;
   srtyp2 = __tntab[op2_ti].srtyp;
   res_ti = gen_scalar_binop(BOOLAND, op1_ti, op2_ti, srtyp, srtyp2);
   return(res_ti);
  }

 is_wide = !(lhsx->szu.xclen <= WBITS && rhsx->szu.xclen <= WBITS);

 /* if not wide and is a leaf just eval op2 as well */
 if (!is_wide && __isleaf(ndp->ru.x))
  {
   op2_ti = __gen_expr_eval(ndp->ru.x, -1);
   is_op2_2state = (__tmp_is_2state(op2_ti) || 
                  __is_constant_with_zero_bpart(op2_ti));
   if (is_op2_2state)
    {
     res_ti = __gen_tn(SR_SCAL2S, 1);
     tmp1_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp1_ti, 0, WRDBYTES);
     __emit_testl(op1_ti);
     __emit_st_sete(CC_JNE, tmp1_ti);
     tmp2_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp2_ti, 0, WRDBYTES);
     __emit_testl(op2_ti);
     __emit_st_sete(CC_JNE, tmp2_ti);
     t1_ti = __emit_bin_bitand(WBITS, tmp1_ti, tmp2_ti);
     __emit_copy(WRDBYTES, t1_ti, res_ti);
    }
   else
    {
     res_ti = __gen_tn(SR_SCAL, 1);
     srtyp = __tntab[op2_ti].srtyp;
     is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL);
     //if (!is_scalar)
      {
       op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
        FALSE, FALSE, FALSE); 
       op2_bpti = __get_bpti(op2_ti);
      }
     done_bbp = __alloc_bblk(FALSE);
     op2_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 3, WRDBYTES);
     __emit_jmp_0(op2_bbp, done_bbp, op2_bpti);
     __start_bblk(op2_bbp);

     tmp1_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp1_ti, 0, WRDBYTES);
     __emit_testl(op1_ti);
     __emit_st_sete(CC_JNE, tmp1_ti);
     tmp2_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp2_ti, 0, WRDBYTES);
     __emit_testl(op2_ti);
     __emit_st_sete(CC_JNE, tmp2_ti);
     t1_ti = __emit_bin_bitand(WBITS, tmp1_ti, tmp2_ti);
     __emit_copy(WRDBYTES, t1_ti, res_ti);
     __start_bblk(done_bbp);
    }
   return(res_ti);
  }


 done_bbp = __alloc_bblk(FALSE);
 op2_bbp = __alloc_bblk(FALSE);
 res_ti = __gen_tn(SR_SCAL2S, 1);
 __emit_store_cint(res_ti, 0, WRDBYTES);
 __emit_jmp_0(done_bbp, op2_bbp, op1_ti);

 __start_bblk(op2_bbp);
 op2_ti = __gen_expr_eval(ndp->ru.x, -1);
 is_op2_2state = (__tmp_is_2state(op2_ti) || 
                 __is_constant_with_zero_bpart(op2_ti));
 if (!is_wide)
  {
   if (is_op2_2state)
    {
     __emit_testl(op2_ti);
     __emit_st_sete(CC_JNE, res_ti);
    }
   else
    {
     __tntab[res_ti].srtyp = SR_SCAL;
     srtyp = __tntab[op2_ti].srtyp;
     is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL);
     //if (!is_scalar)
      {
       op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
        FALSE, FALSE, FALSE); 
       op2_bpti = __get_bpti(op2_ti);
      }
     no_op2_xz_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 3, WRDBYTES);
     __emit_jmp_0(no_op2_xz_bbp, done_bbp, op2_bpti);
     __start_bblk(no_op2_xz_bbp);

     tmp1_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp1_ti, 0, WRDBYTES);
     __emit_testl(op2_ti);
     __emit_st_sete(CC_JNE, tmp1_ti);
     __emit_copy(WRDBYTES, tmp1_ti, res_ti);
    }
   __start_bblk(done_bbp);
  }
 else
  {
   t_bbp = __alloc_bblk(FALSE);
   if (is_op2_2state)
    {
     __emit_jmp_0(done_bbp, t_bbp, op2_ti);
     __start_bblk(t_bbp);
     __emit_store_cint(res_ti, 1, WRDBYTES);
     __emit_jmp(done_bbp);
    }
   else
    {
     __tntab[res_ti].srtyp = SR_SCAL;
     srtyp = __tntab[op2_ti].srtyp;
     is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL);
 //    if (!is_scalar)
      {
       op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
        FALSE, FALSE, FALSE); 
       op2_bpti = __get_bpti(op2_ti);
      }
     no_op2_xz_bbp = __alloc_bblk(FALSE);
     f_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 3, WRDBYTES);
     __emit_jmp_0(no_op2_xz_bbp, done_bbp, op2_bpti);
     __start_bblk(no_op2_xz_bbp);

     __emit_jmp_0(done_bbp, t_bbp, op2_ti);
     __start_bblk(t_bbp);
     __emit_store_cint(res_ti, 1, WRDBYTES);
     __emit_jmp(done_bbp);

     __start_bblk(f_bbp);
     __emit_store_cint(res_ti, 0, WRDBYTES);
     __emit_jmp(done_bbp);
    }
   __start_bblk(done_bbp);
  }
 return(res_ti);
}

/*
 * gen insns for real bool and
 */
static int32 gen_bin_real_booland(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti)
{
 int32 res_ti;
 struct bblk_t *op2_bbp, *f_bbp, *t_bbp, *after_bbp;

 res_ti = __gen_tn(SR_SCAL, 1);

 op2_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 t_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* just simple converts to real hear */
 if (ndp->lu.x->cnvt_to_real)
  {
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, WBITS, TRUE, TRUE, FALSE);
  }
 if (ndp->ru.x->cnvt_to_real)
  {
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, WBITS, TRUE, TRUE, FALSE);
  }

 /* if either opand 0, value is 0 */
 __emit_jmp_real0(f_bbp, op2_bbp, op1_ti);

 __start_bblk(op2_bbp);
 __emit_jmp_real0(f_bbp, t_bbp, op2_ti);

 __start_bblk(t_bbp);
 __emit_store_cint(res_ti, 1, WRDBYTES);
 __emit_jmp(after_bbp);

 __start_bblk(f_bbp);
 __emit_store_cint(res_ti, 0, WRDBYTES);

 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen insns for binary bool or
 *
 * this just uses each operands width - no size chges
 * AIV 10/27/08 - rewrote this to only evaluate the second expr if the 
 * first is not already true
 */
static int32 gen_bin_boolor(struct expr_t *ndp)
{
 int32 res_ti, cint_ti, srtyp, srtyp2, op1_ti, op2_ti, is_op1_2state;
 int32 tmp1_ti, tmp2_ti, op1_bpti, op2_bpti, t1_ti, is_scalar, has_bpart;
 int32 need_xprop;
 word32 val1, val2;
 struct bblk_t *tmp1_not1_bbp, *tmp2_not1_bbp, *after_bbp, *xz_bbp;
 struct expr_t *lhsx, *rhsx;
 
 lhsx = ndp->lu.x;
 rhsx = ndp->ru.x;
 /* these should be folded prior to compile time - but they are not so */
 /* check for here - 4-state handled below but 2-state currently doesn't */
 /* if both widths are one handle as scalar */
 op1_ti = __gen_expr_eval(lhsx, -1);
 is_op1_2state = __tmp_is_2state(op1_ti);
 if (is_op1_2state)
  {
   return(gen_bin_boolor_2state(ndp, op1_ti));
  }

 if (lhsx->szu.xclen == 1 && rhsx->szu.xclen == 1)
  {
   op2_ti = __gen_expr_eval(rhsx, -1);
   srtyp = __tntab[op1_ti].srtyp;
   srtyp2 = __tntab[op2_ti].srtyp;
   res_ti = gen_scalar_binop(BOOLOR, op1_ti, op2_ti, srtyp, srtyp2);
   return(res_ti);
  }

#ifdef __XPROP__
 need_xprop = __inst_mod->m_use_xprop_and_or_x;
#else
 need_xprop = FALSE;
#endif
 /* if either operand is constant handle as special case */
 op1_bpti = op2_bpti = -1;
 val1 = val2 = 0xffffffff;
 /* only need to convert is strength vector */
//AIV 2STATE - seperate routine for 2-state????
 srtyp = __tntab[op1_ti].srtyp;
 is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
 if (!is_scalar)
  {
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, __tntab[op1_ti].tnwid, 
    FALSE, FALSE, FALSE); 
   op1_bpti = __get_bpti(op1_ti);
  }


 res_ti = __gen_tn(SR_SCAL, 1);
 if (__is_constant(op1_ti)) 
  {
   val1 = fold_constant_bin_cvt_bool(op1_ti, op1_bpti, need_xprop, &has_bpart);
   /* AIV 08/03/11 - if constant x just set to x and return */
   if (has_bpart) 
    {
     __emit_store_cint(res_ti, 3, WRDBYTES);
     return(res_ti);
    }
    /* if one return 1 */
   if (val1 == 1)
    {
     /* if xprop still need to check other operand */
     if (need_xprop)
      {
       op2_ti = __gen_expr_eval(rhsx, -1);
       ifx_setx_else_const(op2_ti, 1, res_ti);
       return(res_ti);
      }
     __emit_store_cint(res_ti, 1, WRDBYTES);
     return(res_ti);
    }
   op2_ti = __gen_expr_eval(rhsx, -1);
   /* only need to convert if strength vector */
   srtyp = __tntab[op1_ti].srtyp;
   is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
   if (!is_scalar)
    {
     op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
      FALSE, FALSE, FALSE); 
     op2_bpti = __get_bpti(op2_ti);
    }


   tmp2_ti = gen_bin_cvt_bool(op2_ti, op2_bpti);
   /* value is now either 0 or 3 */
   /* if zero just set to the others bool value */
   if (val1 == 0) 
    {
     __emit_copy(WRDBYTES, tmp2_ti, res_ti);
    }
   else
    {
     /* otherwise if 3 if other value is one bool is one else 3 */
     xz_bbp = __alloc_bblk(TRUE);
     after_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 1, WRDBYTES);
     cint_ti = __gen_cint_tn(1);
     __emit_jmp_eq(after_bbp, xz_bbp, cint_ti, tmp2_ti);
     __start_bblk(xz_bbp);
     __emit_store_cint(res_ti, 3, WRDBYTES);
     __emit_jmp(after_bbp);
     __start_bblk(after_bbp);
    }
   return(res_ti);
  }
 /* AIV 04/23/09 - this cannot use regular __is_const_expr need special */
 /* handling for IS params which __cvc_is_const_expr does */
 else if (__cvc_is_const_expr(rhsx)) 
  {
   op2_ti = __gen_expr_eval(rhsx, -1);
   srtyp = __tntab[op2_ti].srtyp;
   is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
   if (!is_scalar)
    {
     op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
      FALSE, FALSE, FALSE); 
     op2_bpti = __get_bpti(op2_ti);
    }

   val2 = fold_constant_bin_cvt_bool(op2_ti, op2_bpti, need_xprop, &has_bpart);
   /* AIV 08/03/11 - if constant x just set to x and return */
   if (has_bpart) 
    {
     __emit_store_cint(res_ti, 3, WRDBYTES);
     return(res_ti);
    }
   if (val2 == 1)
    {
     /* if xprop still need to check other operand */
     if (need_xprop)
      {
       ifx_setx_else_const(op1_ti, 1, res_ti);
       return(res_ti);
      }
     __emit_store_cint(res_ti, 1, WRDBYTES);
     return(res_ti);
    }
   tmp1_ti = gen_bin_cvt_bool(op1_ti, op1_bpti);
   if (val2 == 0) 
    {
     __emit_copy(WRDBYTES, tmp1_ti, res_ti);
    }
   else
    {
     xz_bbp = __alloc_bblk(TRUE);
     after_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 1, WRDBYTES);
     cint_ti = __gen_cint_tn(1);
     __emit_jmp_eq(after_bbp, xz_bbp, cint_ti, tmp1_ti);
     __start_bblk(xz_bbp);
     __emit_store_cint(res_ti, 3, WRDBYTES);
     __emit_jmp(after_bbp);
     __start_bblk(after_bbp);
    }
   return(res_ti);
  }

 after_bbp = __alloc_bblk(FALSE);
 tmp1_not1_bbp = __alloc_bblk(FALSE);
 tmp2_not1_bbp = __alloc_bblk(FALSE);

 op2_ti = op2_bpti = -1;
 /* AIV 08/03/11 - if either is x/z - must return x */
 if (need_xprop)
  {
   struct bblk_t *regular_bbp, *xz_check_bbp;

   regular_bbp = __alloc_bblk(FALSE);
   xz_check_bbp = __alloc_bblk(TRUE);

   /* eval both operands and check for x/z set */
   op2_ti = __gen_expr_eval(rhsx, -1);
   srtyp = __tntab[op2_ti].srtyp;
   if (srtyp != SR_VEC)
    {
     op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
      FALSE, FALSE, FALSE); 
    }
   op2_bpti = __get_bpti(op2_ti);

   /* if x/z return x otherwise of normal op */
   if (op1_bpti == -1)
    {
     srtyp = __tntab[op1_ti].srtyp;
     if (srtyp != SR_VEC)
      {
       op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, __tntab[op1_ti].tnwid, 
        FALSE, FALSE, FALSE); 
      }
     op1_bpti = __get_bpti(op1_ti);
    }
   __emit_jmpor_0(regular_bbp, xz_check_bbp, op1_bpti, op2_bpti);
   __start_bblk(xz_check_bbp);
   __emit_store_cint(res_ti, 3, WRDBYTES);
   __emit_jmp(after_bbp);
   __start_bblk(regular_bbp);
  }

 
 /* DBG remove -- */
 if (ndp->szu.xclen != 1) __misc_terr(__FILE__, __LINE__);
 /* -- */
 /* FIXME - this should be expanded to and and not and z compare */
 tmp1_ti = gen_bin_cvt_bool(op1_ti, op1_bpti);

 __emit_store_cint(res_ti, 1, WRDBYTES);
 cint_ti = __gen_cint_tn(1);
 __emit_jmp_cmp(tmp1_not1_bbp, after_bbp, tmp1_ti, cint_ti, CC_JNE);

 __start_bblk(tmp1_not1_bbp);

 if (op2_ti == -1)
  {
   op2_ti = __gen_expr_eval(rhsx, -1);

   /* only need to convert if strength vector */
   srtyp = __tntab[op2_ti].srtyp;
   is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL || srtyp == SR_SCAL2S);
   if (!is_scalar)
    {
     op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
      FALSE, FALSE, FALSE); 
     op2_bpti = __get_bpti(op2_ti);
    }
  }


 tmp2_ti = gen_bin_cvt_bool(op2_ti, op2_bpti);

 cint_ti = __gen_cint_tn(1);
 __emit_jmp_cmp(tmp2_not1_bbp, after_bbp, tmp2_ti, cint_ti, CC_JNE); 

 __start_bblk(tmp2_not1_bbp);
 /* if tmp1 == 0 and tmp2 == 0) => result 0 else result x */
 /* these can just or in the results if 3 will remain 3 otherwise 0 */
 t1_ti = __emit_bin_bitor(WBITS, tmp1_ti, tmp2_ti);
 __emit_copy(WRDBYTES, t1_ti, res_ti);
 __emit_jmp(after_bbp);

 /* this inserts the uncond jmp if needed */ 
 __start_bblk(after_bbp);
 return(res_ti);
}


/*
 * 2-state boolor
 */
static int32 gen_bin_boolor_2state(struct expr_t *ndp, int32 op1_ti)
{
 int32 tmp1_ti, tmp2_ti, res_ti, srtyp, srtyp2, is_scalar;
 int32 op2_ti, op2_bpti, t1_ti; 
 int32 is_op2_2state, is_wide;
 struct bblk_t *done_bbp, *op2_bbp, *no_op2_xz_bbp, *t_bbp, *f_bbp;
 struct bblk_t *check_op1_only_bbp;
 struct expr_t *lhsx, *rhsx;

 lhsx = ndp->lu.x;
 rhsx = ndp->ru.x;
 if (lhsx->szu.xclen == 1 && rhsx->szu.xclen == 1)
  {
   op2_ti = __gen_expr_eval(ndp->ru.x, -1);
   is_op2_2state = (__tmp_is_2state(op2_ti) || 
                  __is_constant_with_zero_bpart(op2_ti));
   if (is_op2_2state)
    {
     res_ti = __gen_tn(SR_SCAL2S, 1);
     t1_ti = __emit_bin_bitor(WBITS, op1_ti, op2_ti);
     __emit_copy(WRDBYTES, t1_ti, res_ti);
     return(res_ti);
    }
   srtyp = __tntab[op1_ti].srtyp;
   srtyp2 = __tntab[op2_ti].srtyp;
   res_ti = gen_scalar_binop(BOOLOR, op1_ti, op2_ti, srtyp, srtyp2);
   return(res_ti);
  }

 is_wide = !(lhsx->szu.xclen <= WBITS && rhsx->szu.xclen <= WBITS);

 /* if not wide and is a leaf just eval op2 as well */
 if (!is_wide && __isleaf(ndp->ru.x))
  {
   op2_ti = __gen_expr_eval(ndp->ru.x, -1);
   is_op2_2state = (__tmp_is_2state(op2_ti) || 
                  __is_constant_with_zero_bpart(op2_ti));
   if (is_op2_2state)
    {
     res_ti = __gen_tn(SR_SCAL2S, 1);
     tmp1_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp1_ti, 0, WRDBYTES);
     __emit_testl(op1_ti);
     __emit_st_sete(CC_JNE, tmp1_ti);
     tmp2_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp2_ti, 0, WRDBYTES);
     __emit_testl(op2_ti);
     __emit_st_sete(CC_JNE, tmp2_ti);
     t1_ti = __emit_bin_bitor(WBITS, tmp1_ti, tmp2_ti);
     __emit_copy(WRDBYTES, t1_ti, res_ti);
    }
   else
    {
     res_ti = __gen_tn(SR_SCAL, 1);
     srtyp = __tntab[op2_ti].srtyp;
     is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL);
     //if (!is_scalar)
      {
       op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
        FALSE, FALSE, FALSE); 
       op2_bpti = __get_bpti(op2_ti);
      }
     done_bbp = __alloc_bblk(FALSE);
     op2_bbp = __alloc_bblk(FALSE);
     check_op1_only_bbp = __alloc_bblk(FALSE);
     /* if op2 x/z just must still check op1 */
     __emit_jmp_0(op2_bbp, check_op1_only_bbp, op2_bpti);

     __start_bblk(check_op1_only_bbp);
     tmp1_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp1_ti, 0, WRDBYTES);
     __emit_testl(op1_ti);
     __emit_st_sete(CC_JNE, tmp1_ti);
     __emit_copy(WRDBYTES, tmp1_ti, res_ti);
     __emit_jmp(done_bbp);

     __start_bblk(op2_bbp);
     tmp1_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp1_ti, 0, WRDBYTES);
     __emit_testl(op1_ti);
     __emit_st_sete(CC_JNE, tmp1_ti);
     tmp2_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp2_ti, 0, WRDBYTES);
     __emit_testl(op2_ti);
     __emit_st_sete(CC_JNE, tmp2_ti);
     t1_ti = __emit_bin_bitor(WBITS, tmp1_ti, tmp2_ti);
     __emit_copy(WRDBYTES, t1_ti, res_ti);
     __start_bblk(done_bbp);
    }
   return(res_ti);
  }


 done_bbp = __alloc_bblk(FALSE);
 op2_bbp = __alloc_bblk(FALSE);
 res_ti = __gen_tn(SR_SCAL2S, 1);
 __emit_store_cint(res_ti, 1, WRDBYTES);
 __emit_jmp_0(op2_bbp, done_bbp, op1_ti);

 __start_bblk(op2_bbp);
 __emit_store_cint(res_ti, 0, WRDBYTES);
 op2_ti = __gen_expr_eval(ndp->ru.x, -1);
 is_op2_2state = (__tmp_is_2state(op2_ti) || 
                 __is_constant_with_zero_bpart(op2_ti));
 if (!is_wide)
  {
   if (is_op2_2state)
    {
     __emit_testl(op2_ti);
     __emit_st_sete(CC_JNE, res_ti);
    }
   else
    {
     __tntab[res_ti].srtyp = SR_SCAL;
     srtyp = __tntab[op2_ti].srtyp;
     is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL);
     //if (!is_scalar)
      {
       op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
        FALSE, FALSE, FALSE); 
       op2_bpti = __get_bpti(op2_ti);
      }
     no_op2_xz_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 3, WRDBYTES);
     __emit_jmp_0(no_op2_xz_bbp, done_bbp, op2_bpti);
     __start_bblk(no_op2_xz_bbp);

     tmp1_ti = __gen_tn(SR_BIT2S, WBITS);
     __emit_store_cint(tmp1_ti, 0, WRDBYTES);
     __emit_testl(op2_ti);
     __emit_st_sete(CC_JNE, tmp1_ti);
     __emit_copy(WRDBYTES, tmp1_ti, res_ti);
    }
   __start_bblk(done_bbp);
  }
 else
  {
   t_bbp = __alloc_bblk(FALSE);
   if (is_op2_2state)
    {
     __emit_jmp_0(done_bbp, t_bbp, op2_ti);
     __start_bblk(t_bbp);
     __emit_store_cint(res_ti, 1, WRDBYTES);
     __emit_jmp(done_bbp);
    }
   else
    {
     __tntab[res_ti].srtyp = SR_SCAL;
     srtyp = __tntab[op2_ti].srtyp;
     is_scalar = (srtyp == SR_SCAL || srtyp == SR_SSCAL);
 //    if (!is_scalar)
      {
       op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, __tntab[op2_ti].tnwid, 
        FALSE, FALSE, FALSE); 
       op2_bpti = __get_bpti(op2_ti);
      }
     no_op2_xz_bbp = __alloc_bblk(FALSE);
     f_bbp = __alloc_bblk(FALSE);
     __emit_store_cint(res_ti, 3, WRDBYTES);
     __emit_jmp_0(no_op2_xz_bbp, done_bbp, op2_bpti);
     __start_bblk(no_op2_xz_bbp);

     __emit_jmp_0(done_bbp, t_bbp, op2_ti);
     __start_bblk(t_bbp);
     __emit_store_cint(res_ti, 1, WRDBYTES);
     __emit_jmp(done_bbp);

     __start_bblk(f_bbp);
     __emit_store_cint(res_ti, 0, WRDBYTES);
     __emit_jmp(done_bbp);
    }
   __start_bblk(done_bbp);
  }
 return(res_ti);
}

/*
 * gen insns for real bool or
 */
static int32 gen_bin_real_boolor(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti)
{
 int32 res_ti, res_bpti;
 struct bblk_t *op2_bbp, *f_bbp, *t_bbp, *after_bbp;

 res_ti = __gen_tn(SR_VEC, ndp->szu.xclen);
 
 op2_bbp = __alloc_bblk(FALSE);
 f_bbp = __alloc_bblk(FALSE);
 t_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* just simple converts to real hear */
 if (ndp->lu.x->cnvt_to_real)
  {
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, WBITS, TRUE, TRUE,
    FALSE);
  }
 if (ndp->ru.x->cnvt_to_real)
  {
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, WBITS, TRUE, TRUE,
    FALSE);
  }

 /* since compare real, result never x/z */
 /* AIV 10/24/05 - needed to zero the high part of the real */
 res_bpti = __get_bpti(res_ti);
 __emit_store_cint(res_bpti, 0, WRDBYTES);

 /* if either opand 0, value is 0 */
 __emit_jmp_real0(op2_bbp, t_bbp, op1_ti);
 __start_bblk(op2_bbp);

 __emit_jmp_real0(f_bbp, t_bbp, op2_ti);

 __start_bblk(t_bbp);
 __emit_store_cint(res_ti, 1, WRDBYTES);
 __emit_jmp(after_bbp);

 __start_bblk(f_bbp);
 __emit_store_cint(res_ti, 0, WRDBYTES);
 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen insns for arithmetic or logical shift left and logical shift right
 */
static int32 gen_bin_notsgn_shift(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti, int32 op1_nd_wid, int32 op2_nd_wid)
{
 int32 res_apti, res_bpti, op1_bpti, op2_bpti, blen, bytsiz, r1_ti, r2_ti;
 int32 tmpres_apti, tmpres_bpti, hghw_apti, hghw_bpti, cint_ti, mask_ti, ofs;
 struct bblk_t *shft_bbp, *zero_bbp, *op2_bbp, *xz_bbp, *after_bbp;

 /* AIV 08/03/06 - handle shift amount as constant */
 if (__is_constant(op2_ti))
  {
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
    FALSE, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
    FALSE, FALSE, FALSE); 
   return(gen_bin_notsgn_shift_const(ndp, op1_ti, op2_ti));
  }
 blen = ndp->szu.xclen;
 bytsiz = WRDBYTES*wlen_(blen);
 res_apti = __gen_tn(SR_VEC, blen);
 res_bpti = __get_bpti(res_apti);

 op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
   FALSE, FALSE, FALSE); 
 op2_bpti = __get_bpti(op2_ti);

 shft_bbp = __alloc_bblk(FALSE);
 zero_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* if op2 (shift amount) x/z result is all 1s */
 xz_bbp = __alloc_bblk(TRUE);
 op2_bbp = __alloc_bblk(FALSE);
 __emit_jmp_0(op2_bbp, xz_bbp, op2_bpti);
 __start_bblk(xz_bbp);
 gen_ab_setx(res_apti, FALSE);
 __emit_jmp(after_bbp);

 __start_bblk(op2_bbp);

 /* SJM 06/20/04 - interpreter checks for 0 a/b but not checking here */
 /* only checking for too wide shift amount */

 /* result 0 if shift amount too wide */
 cint_ti = __gen_cint_tn(blen);
 __emit_jmp_cmp(shft_bbp, zero_bbp, op2_ti, cint_ti, CC_JLT);

 /* if shift amount too wide, result is 0 */
 __start_bblk(zero_bbp);

 __emit_store_cint(res_apti, 0, 2*bytsiz);
 __emit_jmp(after_bbp);

 __start_bblk(shft_bbp);


 /* only convert the first operand if needed */
 /* AIV 08/24/10 - if operands are signed need exact size here */
 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, blen, ndp->has_sign,
  FALSE, __tntab[op1_ti].t_signed);
 op1_bpti = __get_bpti(op1_ti);

 if (ndp->optyp == SHIFTL)
  {
   tmpres_apti = __emit_shiftl(blen, op2_ti, op1_ti);
   tmpres_bpti = __emit_shiftl(blen, op2_ti, op1_bpti);
  }
 else
  {
   tmpres_apti = __emit_shiftr(blen, op2_ti, op1_ti);
   tmpres_bpti = __emit_shiftr(blen, op2_ti, op1_bpti);
  }

 /* only need to mask << since 0's injected into high bits */
 if (ndp->optyp == SHIFTL && ubits_(blen) != 0)
  {
   /* if greater than one word get the high part */
   if (blen > WBITS)
    {
     ofs = WRDBYTES*(wlen_(blen) - 1);
     hghw_apti = __con_adradd_insn(SR_VEC, blen, tmpres_apti, ofs);
     hghw_bpti = __con_adradd_insn(SR_VEC, blen, tmpres_bpti, ofs);
    }
   else 
    {
     hghw_apti = tmpres_apti; 
     hghw_bpti = tmpres_bpti; 
    }

   /* SJM 07/19/06 - was not generating the mask cint tn */
   mask_ti = __gen_cint_tn(__masktab[ubits_(blen)]);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);
   r2_ti = __emit_mask_and(hghw_bpti, mask_ti);
   __emit_copy(WRDBYTES, r2_ti, hghw_bpti);
  }

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(wlen_(blen)*WRDBYTES, tmpres_apti, res_apti);
 __emit_copy(wlen_(blen)*WRDBYTES, tmpres_bpti, res_bpti);

 __start_bblk(after_bbp);
 return(res_apti);
}

/*
 * 2-state version
 */
static int32 gen_bin_notsgn_shift_2state(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti, int32 op1_nd_wid, int32 op2_nd_wid)
{
 int32 res_apti, blen, bytsiz, r1_ti;
 int32 tmpres_apti, hghw_apti, cint_ti, mask_ti, ofs;
 struct bblk_t *shft_bbp, *zero_bbp, *after_bbp;

 /* AIV 08/03/06 - handle shift amount as constant */
 if (__is_constant(op2_ti))
  {
   op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, op1_nd_wid,
    FALSE, FALSE, FALSE); 
   op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_BIT2S, op2_nd_wid,
    FALSE, FALSE, FALSE); 
   return(gen_bin_notsgn_shift_const_2state(ndp, op1_ti, op2_ti));
  }
 blen = ndp->szu.xclen;
 bytsiz = WRDBYTES*wlen_(blen);
 res_apti = __gen_tn(SR_BIT2S, blen);

 op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_BIT2S, op2_nd_wid,
   FALSE, FALSE, FALSE); 

 shft_bbp = __alloc_bblk(FALSE);
 zero_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);

 /* result 0 if shift amount too wide */
 cint_ti = __gen_cint_tn(blen);
 __emit_jmp_cmp(shft_bbp, zero_bbp, op2_ti, cint_ti, CC_JLT);

 /* if shift amount too wide, result is 0 */
 __start_bblk(zero_bbp);

 __emit_store_cint(res_apti, 0, bytsiz);
 __emit_jmp(after_bbp);

 __start_bblk(shft_bbp);

 /* only convert the first operand if needed */
 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, blen, ndp->has_sign,
  FALSE, FALSE);

 if (ndp->optyp == SHIFTL) tmpres_apti = __emit_shiftl(blen, op2_ti, op1_ti);
 else tmpres_apti = __emit_shiftr(blen, op2_ti, op1_ti);

 /* only need to mask << since 0's injected into high bits */
 if (ndp->optyp == SHIFTL && ubits_(blen) != 0)
  {
   /* if greater than one word get the high part */
   if (blen > WBITS)
    {
     ofs = WRDBYTES*(wlen_(blen) - 1);
     hghw_apti = __con_adradd_insn(SR_VEC, blen, tmpres_apti, ofs);
    }
   else hghw_apti = tmpres_apti; 

   /* SJM 07/19/06 - was not generating the mask cint tn */
   mask_ti = __gen_cint_tn(__masktab[ubits_(blen)]);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);
  }

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(wlen_(blen)*WRDBYTES, tmpres_apti, res_apti);
 __start_bblk(after_bbp);
 return(res_apti);
}

/*
 * gen insns for arithmetic or logical shift left and logical shift right
 * where the shift amount is a known constant
 * seperate this case so it doesn't have to do so many cases
 *
 * AIV 08/03/06 - added to handle the shift by const amount case
 * SJM 09/23/06 - can generate better code if know shift amount constant 
 */
static int32 gen_bin_notsgn_shift_const(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti)
{
 int32 res_apti, res_bpti, op1_bpti, blen, bytsiz, r1_ti, r2_ti, ofs;
 int32 tmpres_apti, tmpres_bpti, hghw_apti, hghw_bpti, cint_ti, mask_ti;
 int32 bpart_not_zero, twid, ndx, shift_is_zero, op2_bpti;
 word32 shftamt, bval;
 word32 *wp, *wp2;

 blen = ndp->szu.xclen;
 res_apti = __gen_tn(SR_VEC, blen);

 twid = __get_tnwid(op2_ti);
 bpart_not_zero = FALSE;

 ndx = -1;
 op2_bpti = __get_bpti(op2_ti);
 /* check if the bpart of the shift value is zero */
 if (twid > WBITS)
  {
   ndx = __get_con_adradd_xvi(op2_bpti);
   wp = &(__contab[ndx]);
   if (!__wide_vval_is0(wp, twid)) bpart_not_zero = TRUE;
  }
 else
  {
   bval = __get_wrd_con_val(op2_bpti);
   if (bval != 0) bpart_not_zero = TRUE;
  }

 /* if bpart is zero assign all 1s */
 bytsiz = WRDBYTES*wlen_(blen);
 /* SJM 08/08/06 - was not getting b part */  
 if (bpart_not_zero)
  {
   gen_ab_setx(res_apti, FALSE);
   return(res_apti);
  }

 /* result 0 if shift amount too wide */
 ndx = __get_con_adradd_xvi(op2_ti);
 wp = &(__contab[ndx]); 
 wp2 = &(__contab[ndx + 1]); 
 shftamt = wp[0];
 /* AIV 12/10/09 - this should have been <= cannot shift a 32 bit */
 /* word over by 32 - needs to zero */
 if (shftamt >= blen || (twid > WBITS && !vval_is0_(wp2, twid - WBITS)))
  {
   /* shift wider than just assign 0 */
   __emit_store_cint(res_apti, 0, 2*bytsiz);
   return(res_apti);
  }

 /* if op2 is zero just copy op1 and return */
 shift_is_zero = FALSE;
 if (twid <= WBITS)
  {
   if (shftamt == 0) shift_is_zero = TRUE;
  }
 else
  {
   if (__wide_vval_is0(wp, twid)) 
    {
     shift_is_zero = TRUE;
    }
  }

 /* shift amount is zero */
 if (shift_is_zero)
  {
   __emit_copy(2*wlen_(blen)*WRDBYTES, op1_ti, res_apti);
   return(res_apti);
  }
 
 /* only convert the first operand if needed */
 /* AIV 08/24/10 - if operands are signed need exact size here */
 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, blen, ndp->has_sign, 
  FALSE, __tntab[op1_ti].t_signed);

 op1_bpti = __get_bpti(op1_ti);
 cint_ti = __gen_cint_tn(shftamt);
 /* AIV 09/30/10 - this needs ASHIFTL as well */
 if (ndp->optyp == SHIFTL || ndp->optyp == ASHIFTL)
  {
   tmpres_apti = __emit_shiftl(blen, cint_ti, op1_ti);
   tmpres_bpti = __emit_shiftl(blen, cint_ti, op1_bpti);
  }
 else
  {
   tmpres_apti = __emit_shiftr(blen, cint_ti, op1_ti);
   tmpres_bpti = __emit_shiftr(blen, cint_ti, op1_bpti);
  }

 /* only need to mask << since 0's injected into high bits */
 /* AIV 09/30/10 - this needs ASHIFTL as well */
 if ((ndp->optyp == SHIFTL  || ndp->optyp == ASHIFTL) && ubits_(blen) != 0)
  {
   /* if greater than one word get the high part */
   if (blen > WBITS)
    {
     ofs =  WRDBYTES*(wlen_(blen) - 1);
     hghw_apti = __con_adradd_insn(SR_VEC, blen, tmpres_apti, ofs);
     hghw_bpti = __con_adradd_insn(SR_VEC, blen, tmpres_bpti, ofs);
    }
   else 
    {
     hghw_apti = tmpres_apti; 
     hghw_bpti = tmpres_bpti; 
    }

   /* SJM 07/19/06 - was not generating the mask cint tn */
   mask_ti = __gen_cint_tn(__masktab[ubits_(blen)]);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);
   r2_ti = __emit_mask_and(hghw_bpti, mask_ti);
   __emit_copy(WRDBYTES, r2_ti, hghw_bpti);
  }
  
 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(wlen_(blen)*WRDBYTES, tmpres_apti, res_apti);
 res_bpti = __get_bpti(res_apti);
 __emit_copy(wlen_(blen)*WRDBYTES, tmpres_bpti, res_bpti);
 return(res_apti);
}

/*
 * 2-state version
 */
static int32 gen_bin_notsgn_shift_const_2state(struct expr_t *ndp, int32 op1_ti,
 int32 op2_ti)
{
 int32 tmpres_apti, hghw_apti, cint_ti, mask_ti, res_apti;
 int32 twid, ndx, shift_is_zero, blen, bytsiz, ofs, r1_ti;
 word32 shftamt;
 word32 *wp, *wp2;

 blen = ndp->szu.xclen;
 res_apti = __gen_tn(SR_BIT2S, blen);

 twid = __get_tnwid(op2_ti);
 bytsiz = WRDBYTES*wlen_(blen);

 /* result 0 if shift amount too wide */
 ndx = __get_con_adradd_xvi(op2_ti);
 wp = &(__contab[ndx]); 
 wp2 = &(__contab[ndx + 1]); 
 shftamt = wp[0];
 /* AIV 12/10/09 - this should have been <= cannot shift a 32 bit */
 /* word over by 32 - needs to zero */
 if (shftamt >= blen || (twid > WBITS && !vval_is0_(wp2, twid - WBITS)))
  {
   /* shift wider than just assign 0 */
   __emit_store_cint(res_apti, 0, bytsiz);
   return(res_apti);
  }

 /* if op2 is zero just copy op1 and return */
 shift_is_zero = FALSE;
 if (twid <= WBITS)
  {
   if (shftamt == 0) shift_is_zero = TRUE;
  }
 else
  {
   if (__wide_vval_is0(wp, twid)) 
    {
     shift_is_zero = TRUE;
    }
  }

 /* shift amount is zero */
 if (shift_is_zero)
  {
   __emit_copy(wlen_(blen)*WRDBYTES, op1_ti, res_apti);
   return(res_apti);
  }
 
 /* only convert the first operand if needed */
 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, blen, ndp->has_sign,
  FALSE, FALSE);

 cint_ti = __gen_cint_tn(shftamt);
 if (ndp->optyp == SHIFTL) tmpres_apti = __emit_shiftl(blen, cint_ti, op1_ti);
 else tmpres_apti = __emit_shiftr(blen, cint_ti, op1_ti);

 /* only need to mask << since 0's injected into high bits */
 if (ndp->optyp == SHIFTL && ubits_(blen) != 0)
  {
   /* if greater than one word get the high part */
   if (blen > WBITS)
    {
     ofs =  WRDBYTES*(wlen_(blen) - 1);
     hghw_apti = __con_adradd_insn(SR_BIT2S, blen, tmpres_apti, ofs);
    }
   else hghw_apti = tmpres_apti; 

   /* SJM 07/19/06 - was not generating the mask cint tn */
   mask_ti = __gen_cint_tn(__masktab[ubits_(blen)]);
   r1_ti = __emit_mask_and(hghw_apti, mask_ti);
   __emit_copy(WRDBYTES, r1_ti, hghw_apti);
  }

 /* notice copies follow gas movl [from],[to] format */
 __emit_copy(wlen_(blen)*WRDBYTES, tmpres_apti, res_apti);
 return(res_apti);
}

/*
 * gen insns for arithmetic right shift when shift opand signed
 *
 * if shift opand word32 even for ashiftr - same as logical shiftr
 */
static int32 gen_bin_ashiftr(struct expr_t *ndp, int32 op1_ti, int32 op2_ti,
 int32 op1_nd_wid, int32 op2_nd_wid)
{
 int32 res_ti, res_bpti, op1_bpti, op2_bpti, blen, bytsiz;
 int32 t1_ti, t3_ti, cint_ti, nd_signop;
 struct bblk_t *op2_bbp, *xz_bbp, *shft_bbp, *after_bbp;
 struct bblk_t *sgn_mask_bbp, *zero_bbp, *bad_shft_bbp;
 struct bblk_t *mask_bbp, *op2_zero_bbp, *chk_zero_bbp;

 if (ndp->has_sign || ndp->rel_ndssign) nd_signop = TRUE;
 else nd_signop = FALSE;
 
 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_VEC, op1_nd_wid,
   nd_signop, FALSE, FALSE); 
 op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_VEC, op2_nd_wid,
   nd_signop, FALSE, FALSE); 

 /* AIV 08/03/06 - handle shift amount as constant */
 if (__is_constant(op2_ti))
  {
   return(gen_bin_ashiftr_const(ndp, op1_ti, op2_ti));
  }
 blen = ndp->szu.xclen;
 bytsiz = WRDBYTES*wlen_(blen);
 res_ti = __gen_tn(SR_VEC, blen);
 res_bpti = __get_bpti(res_ti);

 op1_bpti = __get_bpti(op1_ti);
 op2_bpti = __get_bpti(op2_ti);

 op2_bbp = __alloc_bblk(FALSE);
 xz_bbp = __alloc_bblk(TRUE);
 op2_zero_bbp = __alloc_bblk(FALSE);
 chk_zero_bbp = __alloc_bblk(FALSE);
 shft_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 sgn_mask_bbp = __alloc_bblk(FALSE);
 bad_shft_bbp = __alloc_bblk(FALSE);
 zero_bbp = __alloc_bblk(FALSE);
 mask_bbp = __alloc_bblk(FALSE);

 /* if op2 (shift amount) x/z result is all 1s */
 __emit_jmp_0(chk_zero_bbp, xz_bbp, op2_bpti); 
 /* if shift amt x/z, result still all xs */
 __start_bblk(xz_bbp);
 gen_ab_setx(res_ti, FALSE);
 __emit_jmp(after_bbp);

 /* if op2 is zero just copy op1 and return */
 __start_bblk(chk_zero_bbp);
 __emit_jmp_0(op2_zero_bbp, op2_bbp, op2_ti); 
 __start_bblk(op2_zero_bbp);
 __emit_copy(2*wlen_(blen)*WRDBYTES, op1_ti, res_ti);
 __emit_jmp(after_bbp);

 __start_bblk(op2_bbp);

 /* check shift amount is valid  */
 cint_ti = __gen_cint_tn(blen);
 __emit_jmp_cmp(bad_shft_bbp, shft_bbp, op2_ti, cint_ti, CC_JGT);

 __start_bblk(bad_shft_bbp);
 /* check if sign bit is on if so -1 else 0 */
 __emit_sgnbit_on_jmp(mask_bbp, zero_bbp, op1_ti);

 /* if op1 bit set result is -1 */
 __start_bblk(mask_bbp);
 gen_oneword_setx(res_ti);
 /* sets to b part 0 */
 __emit_store_cint(res_bpti, 0, bytsiz);
 __emit_jmp(after_bbp);

 /* if not signed bit not on and shft amount too large zero result */
 __start_bblk(zero_bbp);
 /* sets to 0 */
 __emit_store_cint(res_ti, 0, 2*bytsiz);
 __emit_jmp(after_bbp);

 /* do the actual shift */
 __start_bblk(shft_bbp);
 t1_ti = __emit_sgn_arshift(blen, op2_ti, op1_ti);
 /* SJM 09/23/06 - must be a part of op2 not b part as it was */
 t3_ti = __emit_sgn_arshift(blen, op2_ti, op1_bpti);

 /* copy into result */
 __emit_copy(wlen_(blen)*WRDBYTES, t1_ti, res_ti);
 __emit_copy(wlen_(blen)*WRDBYTES, t3_ti, res_bpti);

 /* if negative must 1 the remaining bits */
 __emit_sgnbit_on_jmp(sgn_mask_bbp, after_bbp, op1_ti);

 __start_bblk(sgn_mask_bbp);
 __emit_sgnmask(res_ti, op2_ti, blen);

 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * 2-state version
 */
static int32 gen_bin_ashiftr_2state(struct expr_t *ndp, int32 op1_ti, 
 int32 op2_ti, int32 op1_nd_wid, int32 op2_nd_wid)
{
 int32 res_ti, blen, bytsiz;
 int32 t1_ti, cint_ti, nd_signop;
 struct bblk_t *op2_bbp, *shft_bbp, *after_bbp;
 struct bblk_t *sgn_mask_bbp, *zero_bbp, *bad_shft_bbp;
 struct bblk_t *mask_bbp, *op2_zero_bbp, *chk_zero_bbp;

 if (ndp->has_sign || ndp->rel_ndssign) nd_signop = TRUE;
 else nd_signop = FALSE;
 
 op1_ti = __gen_cnvt_srep_ifneeded(op1_ti, SR_BIT2S, op1_nd_wid,
   nd_signop, FALSE, FALSE); 
 op2_ti = __gen_cnvt_srep_ifneeded(op2_ti, SR_BIT2S, op2_nd_wid,
   nd_signop, FALSE, FALSE); 

 /* AIV 08/03/06 - handle shift amount as constant */
 if (__is_constant(op2_ti))
  {
   return(gen_bin_ashiftr_const_2state(ndp, op1_ti, op2_ti));
  }
 blen = ndp->szu.xclen;
 bytsiz = WRDBYTES*wlen_(blen);
 res_ti = __gen_tn(SR_BIT2S, blen);

 op2_bbp = __alloc_bblk(FALSE);
 op2_zero_bbp = __alloc_bblk(FALSE);
 chk_zero_bbp = __alloc_bblk(FALSE);
 shft_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 sgn_mask_bbp = __alloc_bblk(FALSE);
 bad_shft_bbp = __alloc_bblk(FALSE);
 zero_bbp = __alloc_bblk(FALSE);
 mask_bbp = __alloc_bblk(FALSE);

 /* if op2 is zero just copy op1 and return */
 __start_bblk(chk_zero_bbp);
 __emit_jmp_0(op2_zero_bbp, op2_bbp, op2_ti); 
 __start_bblk(op2_zero_bbp);
 __emit_copy(wlen_(blen)*WRDBYTES, op1_ti, res_ti);
 __emit_jmp(after_bbp);

 __start_bblk(op2_bbp);

 /* check shift amount is valid  */
 cint_ti = __gen_cint_tn(blen);
 __emit_jmp_cmp(bad_shft_bbp, shft_bbp, op2_ti, cint_ti, CC_JGT);

 __start_bblk(bad_shft_bbp);
 /* check if sign bit is on if so -1 else 0 */
 __emit_sgnbit_on_jmp(mask_bbp, zero_bbp, op1_ti);

 /* if op1 bit set result is -1 */
 __start_bblk(mask_bbp);
 gen_oneword_setx(res_ti);
 /* sets to b part 0 */
 __emit_jmp(after_bbp);

 /* if not signed bit not on and shft amount too large zero result */
 __start_bblk(zero_bbp);
 /* sets to 0 */
 __emit_store_cint(res_ti, 0, bytsiz);
 __emit_jmp(after_bbp);

 /* do the actual shift */
 __start_bblk(shft_bbp);
 t1_ti = __emit_sgn_arshift(blen, op2_ti, op1_ti);

 /* copy into result */
 __emit_copy(wlen_(blen)*WRDBYTES, t1_ti, res_ti);

 /* if negative must 1 the remaining bits */
 __emit_sgnbit_on_jmp(sgn_mask_bbp, after_bbp, op1_ti);

 __start_bblk(sgn_mask_bbp);
 __emit_sgnmask(res_ti, op2_ti, blen);

 __start_bblk(after_bbp);
 return(res_ti);
}

/*
 * gen insns for arithmetic right shift when shift opand signed
 * and the shift amount is constant
 *
 * AIV 08/03/06 - added to handle the shift by const amount case
 */
static int32 gen_bin_ashiftr_const(struct expr_t *ndp, int32 op1_ti, 
 int32 op2_ti)
{
 int32 res_apti, res_bpti, op1_bpti, blen, bytsiz, cint_ti;
 int32 ndx, bpart_not_zero, twid, shift_is_zero, op2_bpti, ofs;
 int32 t1_ti, t3_ti, wi, bi, res_hw_apti, nblen;
 struct bblk_t *mask_bbp, *after_bbp, *zero_bbp, *sgn_mask_bbp;
 word32 *wp;
 word32 shftamt, bval, orin_val;

 blen = ndp->szu.xclen;
 res_apti = __gen_tn(SR_VEC, blen);
 wp = NULL;
 bpart_not_zero = FALSE;
 twid = __get_tnwid(op2_ti);

 ndx = -1;
 op2_bpti = __get_bpti(op2_ti);
 /* check if the bpart of the shift value is zero */
 if (blen > WBITS)
  {
   ndx = __get_con_adradd_xvi(op2_bpti);
   wp = &(__contab[ndx]);
   if (!__wide_vval_is0(wp, twid)) bpart_not_zero = TRUE;
  }
 else
  {
   bval = __get_wrd_con_val(op2_bpti);
   if (bval != 0) bpart_not_zero = TRUE;
  }

 /* bpart is not zero set all 1 */
 bytsiz = WRDBYTES*wlen_(blen);
 /* SJM 08/08/06 - was not getting b part and one if branch mask ti un-init */  
 res_bpti = __get_bpti(res_apti);
 if (bpart_not_zero)
  {
   gen_ab_setx(res_apti, FALSE);
   return(res_apti);
  }
 
 /* if greater than blen */
 /* result 0 if shift amount too wide */
 ndx = __get_con_adradd_xvi(op2_ti);
 wp = &(__contab[ndx]); 
 shftamt = wp[0];
 if (shftamt > blen || (twid > WBITS && !vval_is0_(wp, twid - WBITS)))
  {
   mask_bbp = __alloc_bblk(FALSE); 
   after_bbp = __alloc_bblk(FALSE);
   zero_bbp = __alloc_bblk(FALSE);
   __emit_sgnbit_on_jmp(mask_bbp, zero_bbp, op1_ti);

   /* if op1 bit set result is -1 */
   __start_bblk(mask_bbp);
   gen_oneword_setx(res_apti);
   /* sets to b part 0 */
   __emit_store_cint(res_bpti, 0, bytsiz);
   __emit_jmp(after_bbp);

   /* if not signed bit not on and shft amount too large zero result */
   __start_bblk(zero_bbp);
   /* sets to 0 */
   __emit_store_cint(res_apti, 0, 2*bytsiz);
   __emit_jmp(after_bbp);

   __start_bblk(after_bbp);
   return(res_apti);
  }

 /* if op2 is zero just copy op1 and return */
 shift_is_zero = FALSE;
 if (twid <= WBITS)
  {
   if (shftamt == 0) shift_is_zero = TRUE;
  }
 else
  {
   if (__wide_vval_is0(wp, twid)) shift_is_zero = TRUE;
  }
 
 /* shift amount is zero */
 if (shift_is_zero)
  {
   __emit_copy(2*wlen_(blen)*WRDBYTES, op1_ti, res_apti);
   return(res_apti);
  }

 sgn_mask_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 op1_bpti = __get_bpti(op1_ti);
 cint_ti = __gen_cint_tn(shftamt);
 /* do the actual shift */
 t1_ti = __emit_sgn_arshift(blen, cint_ti, op1_ti);
 t3_ti = __emit_sgn_arshift(blen, cint_ti, op1_bpti);

 /* copy into result */
 res_bpti = __get_bpti(res_apti);
 __emit_copy(wlen_(blen)*WRDBYTES, t1_ti, res_apti);
 __emit_copy(wlen_(blen)*WRDBYTES, t3_ti, res_bpti);

 /* if negative must 1 the remaining bits */
 /* rta |= (__masktab[op2a] << (ndp->szu.xclen - op2a)); */
 __emit_sgnbit_on_jmp(sgn_mask_bbp, after_bbp, op1_ti);

 __start_bblk(sgn_mask_bbp);
 /* need to do the mask - (the __asl_sgnmask wrapper) */
 if (blen <= WBITS) 
  {
   /* mask in the amount and store it */
   orin_val = (__masktab[shftamt] << (ndp->szu.xclen - shftamt));
   cint_ti = __gen_cint_tn(orin_val);
   t1_ti = __emit_bin_bitor(WBITS, cint_ti, res_apti);
   __emit_copy(WRDBYTES, t1_ti, res_apti);
  }
 else
  {
   nblen = blen - shftamt;
   bi = get_bofs_(nblen);
   wi = get_wofs_(nblen); 
   cint_ti = __gen_cint_tn(wi*WRDBYTES);
   res_hw_apti = __con_adradd_insn(SR_VEC, nblen, res_apti, wi*WRDBYTES);
   if (bi != 0)
    {
     /*
      * valwp[wi] |= (__masktab[WBITS - bi] << bi);
      * one_allbits_(&(valwp[wi + 1]), shiftval - (WBITS - bi));
      */
     orin_val = (__masktab[WBITS - bi] << bi); 
     cint_ti = __gen_cint_tn(orin_val);
     t1_ti = __emit_bin_bitor(WBITS, cint_ti, res_hw_apti);
     __emit_copy(WRDBYTES, t1_ti, res_hw_apti);

     bytsiz = WRDBYTES*wlen_(shftamt - (WBITS - bi));
     if (bytsiz != 0)
      {
       ofs = (wi + 1)*WRDBYTES;
       res_hw_apti = __con_adradd_insn(SR_VEC, nblen, res_apti, ofs);
       __emit_setall1(res_hw_apti, bytsiz);
     }
    }
   else 
    {
     /* one_allbits_(&(valwp[wi]), shifval); */
     bytsiz = WRDBYTES*wlen_(shftamt);
     __emit_setall1(res_hw_apti, bytsiz);
    }
  }
 __start_bblk(after_bbp);
 return(res_apti);
}

/*
 * 2-state version
 */
static int32 gen_bin_ashiftr_const_2state(struct expr_t *ndp, int32 op1_ti, 
 int32 op2_ti)
{
 int32 res_apti, blen, bytsiz, cint_ti;
 int32 ndx, twid, shift_is_zero, ofs;
 int32 t1_ti, wi, bi, res_hw_apti, nblen;
 struct bblk_t *mask_bbp, *after_bbp, *zero_bbp, *sgn_mask_bbp;
 word32 *wp;
 word32 shftamt, orin_val;

 blen = ndp->szu.xclen;
 res_apti = __gen_tn(SR_BIT2S, blen);
 twid = __get_tnwid(op2_ti);

 /* bpart is not zero set all 1 */
 bytsiz = WRDBYTES*wlen_(blen);
 
 /* if greater than blen */
 /* result 0 if shift amount too wide */
 ndx = __get_con_adradd_xvi(op2_ti);
 wp = &(__contab[ndx]); 
 shftamt = wp[0];
 if (shftamt > blen || (twid > WBITS && !vval_is0_(wp, twid - WBITS)))
  {
   mask_bbp = __alloc_bblk(FALSE); 
   after_bbp = __alloc_bblk(FALSE);
   zero_bbp = __alloc_bblk(FALSE);
   __emit_sgnbit_on_jmp(mask_bbp, zero_bbp, op1_ti);

   /* if op1 bit set result is -1 */
   __start_bblk(mask_bbp);
   gen_oneword_setx(res_apti);
   /* sets to b part 0 */
   __emit_jmp(after_bbp);

   /* if not signed bit not on and shft amount too large zero result */
   __start_bblk(zero_bbp);
   /* sets to 0 */
   __emit_store_cint(res_apti, 0, bytsiz);
   __emit_jmp(after_bbp);

   __start_bblk(after_bbp);
   return(res_apti);
  }

 /* if op2 is zero just copy op1 and return */
 shift_is_zero = FALSE;
 if (twid <= WBITS)
  {
   if (shftamt == 0) shift_is_zero = TRUE;
  }
 else
  {
   if (__wide_vval_is0(wp, twid)) shift_is_zero = TRUE;
  }
 
 /* shift amount is zero */
 if (shift_is_zero)
  {
   __emit_copy(wlen_(blen)*WRDBYTES, op1_ti, res_apti);
   return(res_apti);
  }

 sgn_mask_bbp = __alloc_bblk(FALSE);
 after_bbp = __alloc_bblk(FALSE);
 cint_ti = __gen_cint_tn(shftamt);
 /* do the actual shift */
 t1_ti = __emit_sgn_arshift(blen, cint_ti, op1_ti);

 /* copy into result */
 __emit_copy(wlen_(blen)*WRDBYTES, t1_ti, res_apti);

 /* if negative must 1 the remaining bits */
 /* rta |= (__masktab[op2a] << (ndp->szu.xclen - op2a)); */
 __emit_sgnbit_on_jmp(sgn_mask_bbp, after_bbp, op1_ti);

 __start_bblk(sgn_mask_bbp);
 /* need to do the mask - (the __asl_sgnmask wrapper) */
 if (blen <= WBITS) 
  {
   /* mask in the amount and store it */
   orin_val = (__masktab[shftamt] << (ndp->szu.xclen - shftamt));
   cint_ti = __gen_cint_tn(orin_val);
   t1_ti = __emit_bin_bitor(WBITS, cint_ti, res_apti);
   __emit_copy(WRDBYTES, t1_ti, res_apti);
  }
 else
  {
   nblen = blen - shftamt;
   bi = get_bofs_(nblen);
   wi = get_wofs_(nblen); 
   cint_ti = __gen_cint_tn(wi*WRDBYTES);
   res_hw_apti = __con_adradd_insn(SR_BIT2S, nblen, res_apti, wi*WRDBYTES);
   if (bi != 0)
    {
     /*
      * valwp[wi] |= (__masktab[WBITS - bi] << bi);
      * one_allbits_(&(valwp[wi + 1]), shiftval - (WBITS - bi));
      */
     orin_val = (__masktab[WBITS - bi] << bi); 
     cint_ti = __gen_cint_tn(orin_val);
     t1_ti = __emit_bin_bitor(WBITS, cint_ti, res_hw_apti);
     __emit_copy(WRDBYTES, t1_ti, res_hw_apti);

     bytsiz = WRDBYTES*wlen_(shftamt - (WBITS - bi));
     if (bytsiz != 0)
      {
       ofs = (wi + 1)*WRDBYTES;
       res_hw_apti = __con_adradd_insn(SR_BIT2S, nblen, res_apti, ofs);
       __emit_setall1(res_hw_apti, bytsiz);
     }
    }
   else 
    {
     /* one_allbits_(&(valwp[wi]), shifval); */
     bytsiz = WRDBYTES*wlen_(shftamt);
     __emit_setall1(res_hw_apti, bytsiz);
    }
  }
 __start_bblk(after_bbp);
 return(res_apti);
}

/*
 * 01/09/07 - added power operand ** lowering code
 * code is taken from v_ex2.c for the power eval code
 */
static int32 gen_bin_power(struct expr_t *ndp, int32 op1_ti, int32 op2_ti,
 int32 is_2state)
{
 int32 res_apti, res_bpti, blen, mask_ti, one_ti;
 int32 op1_bpti, op2_bpti, cint_ti, op1_is_const;
 struct bblk_t *xz_bbp, *op1_one_bbp, *op2_one_bbp, *doit_bbp, *after_bbp;
 struct bblk_t *chk_op1_one_bbp, *chk_op2_one_bbp, *init_loop_bbp;
 word32 mask;

 blen = ndp->szu.xclen;
 /* DBG remove -- */
 if (blen > WBITS) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 mask = __masktab[ubits_(blen)];
 res_bpti = -1;
 if (is_2state)
  {
   res_apti = __gen_tn(SR_BIT2S, blen);
  }
 else
  {
   res_apti = __gen_tn(SR_VEC, blen);
   res_bpti = __get_bpti(res_apti);
  }
 mask_ti = __gen_cint_tn(mask);
 op1_is_const =  __is_constant(op1_ti);

 after_bbp = __alloc_bblk(FALSE); 
 op1_one_bbp = __alloc_bblk(FALSE); 
 op2_one_bbp = __alloc_bblk(FALSE); 
 init_loop_bbp = __alloc_bblk(FALSE); 
 doit_bbp = __alloc_bblk(FALSE); 
 chk_op2_one_bbp = __alloc_bblk(FALSE); 
 if (op1_is_const) chk_op1_one_bbp = NULL;
 else chk_op1_one_bbp = __alloc_bblk(FALSE); 

 if (!is_2state)
  {
   xz_bbp = __alloc_bblk(TRUE); 
   op1_bpti = __get_bpti(op1_ti);
   op2_bpti = __get_bpti(op2_ti);
   __emit_jmpor_0(doit_bbp, xz_bbp, op1_bpti, op2_bpti);

   __start_bblk(xz_bbp);
   __emit_copy(WRDBYTES, mask_ti, res_apti);
   __emit_copy(WRDBYTES, mask_ti, res_bpti);
   __emit_jmp(after_bbp);
  }

 one_ti = __gen_cint_tn(1);

 __start_bblk(doit_bbp);
 /* make the bpart 0 */
 cint_ti = __gen_cint_tn(0);
 if (!is_2state) __emit_copy(WRDBYTES, cint_ti, res_bpti);

 /* n^0 always = 1 */ 
 /* AIV 07/12/10 - there was a bug the op1 is constant - never need to check */
 /* if op1 is equal to one - just check other operand */
 if (!op1_is_const)
  {
   __emit_jmp_0(op1_one_bbp, chk_op1_one_bbp, op2_ti);
  }
 else __emit_jmp_0(op1_one_bbp, chk_op2_one_bbp, op2_ti);
 

 __start_bblk(op1_one_bbp);
 __emit_copy(WRDBYTES, one_ti, res_apti);
 __emit_jmp(after_bbp);

 /* 1^n = 1 */
 if (!op1_is_const)
  {
   __start_bblk(chk_op1_one_bbp);
   __emit_jmp_eq(op1_one_bbp, chk_op2_one_bbp, op1_ti, one_ti);
  }


 __start_bblk(chk_op2_one_bbp);
 __emit_jmp_0(op2_one_bbp, init_loop_bbp, op2_ti);
 /* n^1 = n */
 __start_bblk(op2_one_bbp);
 __emit_copy(WRDBYTES, op1_ti, res_apti);
 __emit_jmp(after_bbp);
 __start_bblk(init_loop_bbp);

 /* do the actual operation loop */
 gen_power_loop(after_bbp, op1_ti, op2_ti, res_apti, mask_ti, one_ti, -1);
 return(res_apti);
}

/*
 * 01/09/07 - added power operand ** lowering code for signed operands
 * code is taken from v_ex2.c for the power eval code
 * AIV LOOKATME - code is complicated and produces a lot of code
 * better off as wrapper ??????????????????????
 */
static int32 gen_bin_sgn_power(struct expr_t *ndp, int32 op1_ti, int32 op2_ti,
 int32 is_2state)
{
 int32 res_apti, res_bpti, blen, mask_ti, one_ti, zero_ti, cint_ti;
 int32 op1_bpti, op2_bpti, op1_is_neg_ti, op2_is_neg_ti, t2_ti;
 int32 pos_op2_ti, pos_op1_ti, has_sign_ti, t1_ti, t3_ti, op1_is_const;
 struct bblk_t *xz_bbp, *op2_one_bbp, *doit_bbp, *after_bbp;
 struct bblk_t *chk_op1_one_bbp, *chk_op2_one_bbp, *init_loop_bbp;
 struct bblk_t *assign_x_bbp, *zero_bbp, *mask_bbp, *assign_one_bbp;
 struct bblk_t *check_odd_bbp, *op2neg_op1neg_bbp, *op2neg_op1pos_bbp;
 struct bblk_t *op2_neg_chk_bbp, *check_sign_bbp, *has_sign_true_bbp;
 struct bblk_t *op2pos_chk_op1_neg_bbp, *chk_sgn_cnv_bbp;
 struct bblk_t *op1_pos_bbp, *op1_neg_bbp, *op2_pos_bbp, *op2_neg_bbp;
 struct bblk_t * chk_sign_ops_bbp, *op2pos_op1neg_bbp, *chk_op2_sgn_bbp;
 word32 mask;

 blen = ndp->szu.xclen;
 /* DBG remove -- */
 if (blen > WBITS) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 res_bpti = -1;
 mask = __masktab[ubits_(blen)];
 if (is_2state)
  {
   res_apti = __gen_tn(SR_BIT2S, blen);
  }
 else
  {
   res_apti = __gen_tn(SR_VEC, blen);
   res_bpti = __get_bpti(res_apti);
  }
 mask_ti = __gen_cint_tn(mask);

 after_bbp = __alloc_bblk(FALSE); 
 op2_one_bbp = __alloc_bblk(FALSE); 
 init_loop_bbp = __alloc_bblk(FALSE); 
 doit_bbp = __alloc_bblk(FALSE); 

 op1_is_const =  __is_constant(op1_ti);
 if (op1_is_const) chk_op1_one_bbp = NULL;
 else chk_op1_one_bbp = __alloc_bblk(FALSE); 
 chk_op2_one_bbp = __alloc_bblk(FALSE); 

 assign_x_bbp  = __alloc_bblk(FALSE); 
 zero_bbp = __alloc_bblk(FALSE); 
 mask_bbp = __alloc_bblk(FALSE); 
 assign_one_bbp = __alloc_bblk(FALSE); 
 check_odd_bbp  = __alloc_bblk(FALSE); 
 op2neg_op1neg_bbp = __alloc_bblk(FALSE); 
 op2neg_op1pos_bbp = __alloc_bblk(FALSE); 
 op2_neg_chk_bbp = __alloc_bblk(FALSE); 
 check_sign_bbp = __alloc_bblk(FALSE); 
 has_sign_true_bbp = __alloc_bblk(FALSE); 
 op2pos_chk_op1_neg_bbp = __alloc_bblk(FALSE); 
 chk_sgn_cnv_bbp = __alloc_bblk(FALSE); 
 op1_pos_bbp = __alloc_bblk(FALSE); 
 op1_neg_bbp = __alloc_bblk(FALSE); 
 op2_pos_bbp = __alloc_bblk(FALSE); 
 op2_neg_bbp = __alloc_bblk(FALSE); 
 chk_sign_ops_bbp = __alloc_bblk(FALSE); 
 op2pos_op1neg_bbp = __alloc_bblk(FALSE); 
 chk_op2_sgn_bbp = __alloc_bblk(FALSE); 

 if (!is_2state)
  {
   xz_bbp = __alloc_bblk(TRUE); 
   op1_bpti = __get_bpti(op1_ti);
   op2_bpti = __get_bpti(op2_ti);
   __emit_jmpor_0(doit_bbp, xz_bbp, op1_bpti, op2_bpti);

   __start_bblk(xz_bbp);
   __emit_copy(WRDBYTES, mask_ti, res_apti);
   __emit_copy(WRDBYTES, mask_ti, res_bpti);
   __emit_jmp(after_bbp);
  }

 /* gen a constant 1 */
 one_ti = __gen_cint_tn(1);

 __start_bblk(doit_bbp);
 /* make the bpart 0 */
 zero_ti = __gen_cint_tn(0);
 if (!is_2state)
  {
   __emit_copy(WRDBYTES, zero_ti, res_bpti);
  }

 /* n^0 always = 1 */ 
 /* AIV 07/12/10 - there was a bug the op1 is constant - never need to check */
 /* if op1 is equal to one - just check other operand */
 if (!op1_is_const)
  {
   __emit_jmp_0(assign_one_bbp, chk_op1_one_bbp, op2_ti);
  }
 else  __emit_jmp_0(assign_one_bbp, chk_op2_one_bbp, op2_ti);

 /* 1^n = 1 */
 if (!op1_is_const)
  {
   __start_bblk(chk_op1_one_bbp);
   __emit_jmp_eq(assign_one_bbp, chk_op2_one_bbp, op1_ti, one_ti);
  }


 __start_bblk(chk_op2_one_bbp);
 __emit_jmp_0(op2_one_bbp, chk_sign_ops_bbp, op2_ti);
 /* n^1 = n */
 __start_bblk(op2_one_bbp);
 __emit_copy(WRDBYTES, op1_ti, res_apti);
 __emit_jmp(after_bbp);
 __start_bblk(chk_sign_ops_bbp);

 __emit_sgnbit_on_jmp(op1_neg_bbp, op1_pos_bbp, op1_ti);

 pos_op1_ti = __gen_tn(SR_VEC, WBITS);
 op1_is_neg_ti = __gen_tn(SR_VEC, WBITS);

 /* op1 is neg make pos by inverting bits */
 __start_bblk(op1_neg_bbp);
 mask = ~(__masktab[blen]);
 cint_ti = __gen_cint_tn(mask);
 t2_ti = __emit_bin_bitor(blen, op1_ti, cint_ti);
 t1_ti = __emit_swap_sign(blen, t2_ti); 
 __emit_copy(WRDBYTES, t1_ti, pos_op1_ti);
 __emit_copy(WRDBYTES, one_ti, op1_is_neg_ti);
 __emit_jmp(chk_op2_sgn_bbp);

 /* already positive just copy */
 __start_bblk(op1_pos_bbp);
 __emit_copy(WRDBYTES, op1_ti, pos_op1_ti);
 __emit_copy(WRDBYTES, zero_ti, op1_is_neg_ti);
 __emit_jmp(chk_op2_sgn_bbp);

 __start_bblk(chk_op2_sgn_bbp);
 __emit_sgnbit_on_jmp(op2_neg_bbp, op2_pos_bbp, op2_ti);
 pos_op2_ti = __gen_tn(SR_VEC, WBITS);
 op2_is_neg_ti = __gen_tn(SR_VEC, WBITS);

 /* op1 is neg make pos by inverting bits */
 __start_bblk(op2_neg_bbp);
 t2_ti = __emit_bin_bitor(blen, op2_ti, cint_ti);
 /* AIV 11/09/11 - there was a bug here - this should be t2_ti */
 t1_ti = __emit_swap_sign(blen, t2_ti); 
 __emit_copy(WRDBYTES, t1_ti, pos_op2_ti);
 __emit_copy(WRDBYTES, one_ti, op2_is_neg_ti);
 __emit_jmp(chk_sgn_cnv_bbp);

 /* already positive just copy */
 __start_bblk(op2_pos_bbp);
 __emit_copy(WRDBYTES, op2_ti, pos_op2_ti);
 __emit_copy(WRDBYTES, zero_ti, op2_is_neg_ti);
 __emit_jmp(chk_sgn_cnv_bbp);

 /* now check the sign conventions from LRM */
 has_sign_ti = __gen_tn(SR_VEC, WBITS);
 __start_bblk(chk_sgn_cnv_bbp);
 __emit_copy(WRDBYTES, zero_ti, has_sign_ti);
 __emit_jmp_0(op2pos_chk_op1_neg_bbp, op2_neg_chk_bbp, op2_is_neg_ti);

 __start_bblk(op2pos_chk_op1_neg_bbp);
 /* op1 & op2 do regular loop */
 __emit_jmp_0(init_loop_bbp, op2pos_op1neg_bbp, op1_is_neg_ti);

 /* op2 positive and op1 is negative */
 __start_bblk(op2pos_op1neg_bbp);
 __emit_jmp_eq(check_odd_bbp, check_sign_bbp, pos_op2_ti, one_ti);

 __start_bblk(check_sign_bbp);
 t1_ti = __emit_bin_bitand(WBITS, pos_op2_ti, one_ti);
 __emit_jmp_0(init_loop_bbp, has_sign_true_bbp, t1_ti);

 __start_bblk(has_sign_true_bbp);
 __emit_copy(WRDBYTES, one_ti, has_sign_ti);
 __emit_jmp(init_loop_bbp);

 __start_bblk(op2_neg_chk_bbp);
 __emit_jmp_0(op2neg_op1pos_bbp, op2neg_op1neg_bbp, op1_is_neg_ti);

 /* op2 is neg and op1 is positive - result is always zero */
 __start_bblk(op2neg_op1pos_bbp);
 __emit_jmp_0(assign_x_bbp, zero_bbp, pos_op1_ti);

 /* op1 & op2 are negative */
 __start_bblk(op2neg_op1neg_bbp);
 
 /* if one check for odd else zero */
 __emit_jmp_eq(check_odd_bbp, zero_bbp, pos_op1_ti, one_ti);
 
 /* if odd result = mask else result = 1 */
 __start_bblk(check_odd_bbp);
 t3_ti = __emit_bin_bitand(WBITS, pos_op2_ti, one_ti);
 __emit_jmp_0(assign_one_bbp, mask_bbp, t3_ti);

 __start_bblk(assign_one_bbp);
 __emit_copy(WRDBYTES, one_ti, res_apti);
 __emit_jmp(after_bbp);

 __start_bblk(mask_bbp);
 __emit_copy(WRDBYTES, mask_ti, res_apti);
 __emit_jmp(after_bbp);

 __start_bblk(zero_bbp);
 __emit_copy(WRDBYTES, zero_ti, res_apti);
 __emit_jmp(after_bbp);

 __start_bblk(assign_x_bbp);
 if (is_2state)
  {
   __emit_copy(WRDBYTES, zero_ti, res_apti);
  }
 else
  {
   __emit_copy(WRDBYTES, one_ti, res_apti);
   __emit_copy(WRDBYTES, one_ti, res_bpti);
  }
 __emit_jmp(after_bbp);

 __start_bblk(init_loop_bbp);
 /* after sign handling do the actual power loop */
 gen_power_loop(after_bbp, pos_op1_ti, pos_op2_ti, res_apti, mask_ti, one_ti, 
  has_sign_ti);
 return(res_apti);
}

/*
 * do the simple right-to-left exponentiation loop on now positive values 
 * the sign case passes has_sign_ti to indicate its value must be negated
 */
static void gen_power_loop(struct bblk_t *after_bbp, int32 op1_ti, 
 int32 op2_ti, int32 res_apti, int32 mask_ti, int32 one_ti, int32 has_sign_ti) 
{
 int32 rta_apti, wtmp1_apti, op1_tmp_apti, blen;
 int32 tmp1_ti, t1_ti, t2_ti, t3_ti, t4_ti, t5_ti;
 struct bblk_t *loop_done_bbp, *loop_bbp, *odd_bbp, *not_odd_bbp;
 struct bblk_t *neg_bbp, *pos_bbp;

//AIV LOOKATME - may need actual ndp->szu.xlen blen
 blen = __get_tnwid(op1_ti);;
 loop_done_bbp = __alloc_bblk(FALSE); 
 loop_bbp = __alloc_bblk(FALSE); 
 odd_bbp = __alloc_bblk(FALSE); 
 not_odd_bbp = __alloc_bblk(FALSE); 

 /* copy operands to tmp work areas */
 wtmp1_apti = __gen_tn(SR_VEC, WBITS);
 __emit_copy(WRDBYTES, op2_ti, wtmp1_apti);
 op1_tmp_apti = __gen_tn(SR_VEC, WBITS);
 __emit_copy(WRDBYTES, op1_ti, op1_tmp_apti);

 rta_apti = __gen_tn(SR_VEC, WBITS);
 __emit_copy(WRDBYTES, one_ti, rta_apti);

 /* check odd bit and divide by 2 (shift right 1) */
 __start_bblk(loop_bbp);
 tmp1_ti = __emit_bin_bitand(WBITS, wtmp1_apti, one_ti);
 t1_ti = __emit_shiftr(WBITS, one_ti, wtmp1_apti);
 __emit_copy(WRDBYTES, t1_ti, wtmp1_apti);
 __emit_jmp_0(not_odd_bbp, odd_bbp, tmp1_ti); 

 __start_bblk(odd_bbp);
 /* rta_apti = rta_apti * op1_tmp_apti */
 t2_ti = __emit_mult(WBITS, rta_apti, op1_tmp_apti);
 __emit_copy(WRDBYTES, t2_ti, rta_apti);
 __emit_jmp_0(loop_done_bbp, not_odd_bbp, wtmp1_apti); 

 __start_bblk(not_odd_bbp);
//AIV FIXME - same operands in mult is optim is lower to 2 op
 t3_ti = __emit_mult(WBITS, op1_tmp_apti, op1_tmp_apti);
 __emit_copy(WRDBYTES, t3_ti, op1_tmp_apti);
 __emit_jmp(loop_bbp);

 __start_bblk(loop_done_bbp);
 /* need to check for signed bit for signed version */
 /* rta &= mask; */
 if (has_sign_ti != -1)
  {
   neg_bbp = __alloc_bblk(FALSE); 
   pos_bbp = __alloc_bblk(FALSE); 
   __emit_jmp_0(pos_bbp, neg_bbp, has_sign_ti); 
   __start_bblk(neg_bbp);
   t4_ti = __emit_swap_sign(blen, rta_apti); 
   __emit_copy(WRDBYTES, t4_ti, rta_apti);
   __start_bblk(pos_bbp);
  }
 t5_ti = __emit_bin_bitand(WBITS, rta_apti, mask_ti);
 __emit_copy(WRDBYTES, t5_ti, res_apti);
 __start_bblk(after_bbp);
}

/*
 * ROUTINES TO BUILD (ALLOC) BASIC BLOCKS AND FLOW GRAPHS
 */

/*
 * start a basic block - prepare to add insns 
 */
extern void __start_bblk(struct bblk_t *bbp)
{
 struct insn_t *tail_ip;

 /* DBG remove -- */
 if (bbp == NULL) __misc_terr(__FILE__, __LINE__);
 if (bbp->ihd != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 /* AIV 11/30/09 - reset non-blocking delay time since in block */
 __nb_const_last_time = 0xffffffffffffffffULL;

 if (__cur_bbp == NULL) 
  { 
   __cur_bbp = bbp; 
   __enter_bblk_valnum = ++__cur_valnum;
   return; 
  }

 /* DBG remove -- */
 // if (__cur_bbp == bbp) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

//AIV? FIXME - what should this be? - is there a back edge?
 tail_ip = __cur_bbp->itail;
 if (tail_ip != NULL && (__is_jmp_insn(tail_ip->opcod)
  || __is_fg_exit_insn(tail_ip->opcod)))
  {
   __cur_bbp = bbp;
   /* SJM 12/20/06 - must never start AFS (after delay ctrl) block with */
   /* a label - was wrongly generating extra unused first lable insn */
   if (!bbp->after_suspend) __emit_block_label(bbp);
   __enter_bblk_valnum = ++__cur_valnum;
   return;
  }

 /* if bblk empty or last vm insn not jump, add unc. jump to new start */
 /* end (or only) vm insn of every block must be jump */
 /* this sets the next flow graph edge (from op code no uncond) */

 /* SJM 11/04/06 - emit jump sets the back edge */
 __emit_jmp(bbp);

 /* create the label for the new block */
 __cur_bbp = bbp;
 __emit_block_label(bbp);
 /* start of the blocks val number */
 __enter_bblk_valnum = ++__cur_valnum;
 /* AIV 12/12/06 - print the enter block message for debugging */
 if (__opt_block_trace)
  {
   __emit_enter_bblk_dbgmsg();
  }
}

/* 
 * checks last block to see if a jmp or complete is needed
 * last bblk is empty or last insn is not a complete or jmp
 */
//AIV - this can't be used anymore
static int32 need_complete_or_suspend(void)
{
 int32 ocod, need_jmp;

 need_jmp = FALSE;
 if (__cur_bbp != NULL) 
  {
   if (__cur_bbp->itail == NULL) need_jmp = TRUE;
   else 
    {
     ocod = __cur_bbp->itail->opcod;
     if (ocod != I_RETURN && !__is_jmp_insn(ocod)) need_jmp = TRUE;
     else need_jmp = FALSE;
    }
  }
 return(need_jmp);
}

/*
 * LOW LEVEL TMP NAME ROUTINES
 */

/*
 * routine to get ptr to b part given ptr to a part by adding to addr
 *
 * know tmp (or net) stored as srep SR VEC form
 */
extern int32 __get_bpti(int32 apti)
{
 int32 bpti, blen;

 /* DBG remove -- */
 if (__tntab[apti].srtyp != SR_VEC) __misc_terr(__FILE__, __LINE__); 
 /* --- */

 blen = __get_tnwid(apti);
 bpti = __con_adradd_insn(SR_VEC, blen, apti, wlen_(blen)*WRDBYTES);
 return(bpti);
}

/*
 * alloc new tmp name for value on %ebp stack - return index in table
 * caller must set net list object type and amth if needed
 */
extern int32 __gen_tn(int32 srtyp, int32 bsiz)
{
 struct tn_t *tnp;
 
 if (__tntab_nxti >= __tntabsiz - 2) grow_tntab();
 tnp = &(__tntab[__tntab_nxti]);
 __init_tn(tnp);
 tnp->srtyp = srtyp;
 /* assume tn is value, caller change tn type to addr if needed */
 /* may decompose later into multiple narrows if possible */ 
 tnp->tn_typ = TN_VAL;
 tnp->tnwid = bsiz;

 __tntab_nxti++;

#ifdef __CVC_DEBUG__
 /* AIV 06/18/09 - check for overflow of the tntab - this may happen */
 /* for large designs since it is module wide ??? */
 if (__tntab_nxti == 0x7ffffffe) __misc_terr(__FILE__, __LINE__);
#endif

 return(__tntab_nxti - 1);
}

/*
 * initialize a tmp name table element 
 */
extern void __init_tn(struct tn_t *tnp)
{
 tnp->srtyp = SR_UNKN;
 tnp->tn_typ = TN_UNKN;
 /* none means not a label or a cint immediate (constant) */
 tnp->comlab_typ = COMLAB_NONE;
 tnp->idp_typ = COMLAB_NONE;
 tnp->t_signed = FALSE;
 tnp->t_real = FALSE;
 tnp->t_used_in_bw_insn = FALSE;
 tnp->t_used_cross_call = FALSE;
 tnp->conadr_is_is = FALSE;
 tnp->tn_used_wide = FALSE;
 tnp->tn_spilled = FALSE;
 tnp->tn_assigned = FALSE;
 tnp->used_in_asm = FALSE;
 tnp->x86_regno = REG_NONE;
 tnp->svec_adr_add = FALSE;
 tnp->tn_cnvt_from_2state = FALSE;
 tnp->tn_bpart_zero = FALSE;
 tnp->tn_spill_fold = FALSE;
#ifdef __VALTRK__
 tnp->res_tn_useistays = FALSE;
 tnp->nd_valtrk_idp_siz = FALSE; 
#endif
 //AIV 07/02/09 - these are only used for debuging
 //tnp->is_reg_use = FALSE;
 //tnp->is_reg_def = FALSE;
 tnp->tn_used_var_shift = FALSE;

 tnp->tnwid = -1;  
 tnp->spill_ebp_byt_ofs = -1;
 tnp->valnum = -1;
 tnp->tn_coalesce_into = -1;
 tnp->tncu.el_ndx = -1;
 tnp->tnsyrecp = NULL;
 tnp->st_into_ip = NULL;
 tnp->tag_parent_tni = -1;
 tnp->child_tag_offset = 0;
 tnp->tn_conflct_tree = NULL;
 tnp->tn_adj_lst = NULL;
 tnp->ralloci = NULL;
#ifndef __CVC32__
 tnp->passed_args = 0;
#endif
#ifdef __VALTRK__
 tnp->curdef_ip = NULL; 
 tnp->trk_valp = NULL;
 tnp->trk_known = NULL;
 tnp->bb_def_tree = NULL; 
 tnp->bb_use_tree = NULL; 
#endif
}

/*
 * grow tmp name table by re-allocating 
 * must always access by index for this to work
 */
static void grow_tntab(void)
{
 size_t old_tmptabsiz, osize, nsize;

 /* AIV 06/17/09 - changed this to size_t could overflow for large gate */
 /* designs need 64 for 64-bit */
 old_tmptabsiz = __tntabsiz;
 osize = old_tmptabsiz*sizeof(struct tn_t);
 /* AIV 06/18/09 - if tntab is large grow at only 10% not 1.5 */
 /* this should keep memory down for large designs */
 if (__tntabsiz > 200000)
  {
   __tntabsiz = (11*__tntabsiz)/10; 
  }
 else __tntabsiz = (3*__tntabsiz)/2; 

 nsize = __tntabsiz*sizeof(struct tn_t);
 __tntab = (struct tn_t *) __my_realloc(__tntab, osize, nsize);
}

/*
 * access width of a tmp name given its per module index
 */
extern int32 __get_tnwid(int32 tni)
{
 return(__tntab[tni].tnwid);
}
