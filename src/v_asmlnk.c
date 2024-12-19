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

/* AIV 03/28/12 - this is needed for some systems for clone call */
// #ifndef _GNU_SOURCE
// #define _GNU_SOURCE
// #endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <dlfcn.h> 
#include <stdarg.h>
#include <unistd.h> 
#include <errno.h> 

#include <err.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sched.h>
// SJM 05-30-13 - valut 4x does not support this include
#ifndef __RHEL4X__
#include <linux/sched.h>
#endif

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

/* Alignment for jump enters */
#define ALIGN_JMPE_STR "\t.p2align 4,,7\n\t.p2align 3"
//#define ALIGN_JMPE_STR ".p2align 4,,10\n .p2align 3"

/* Alignment for jump functions */
//#define ALIGN_FUNC_STR ""
#define ALIGN_FUNC_STR ".p2align 4,,15"
//#define ALIGN_FUNC_STR ".p2align 4,,2"
//#define ALIGN_FUNC_STR ".align 4"

/* local prototypes */
static void map_1mod_to_linearized_x86_insn(struct mod_t *); 
static void save_fgs_next_nchg_in_reg_and_merge_fgips(void);
static void try_to_save_next_nchg_in_reg(struct flowg_t *);
static int32 get_free_callee_save_reg(int32 *);
static void change_contags_to_imms(struct bblk_t *);
static int32 try_convert_amode_to_imm(struct amode_t *);
static int32 is_real_insn(struct insn_t *);
static void lower_epilogue_prologue(struct bblk_t *, struct flowg_t *);
static int32 flow_graphs_needs_call_save_regs(struct flowg_t *);
static void lower_bblk_enter_exits(struct mod_t *, struct bblk_t *); 
static void convert_insn_bytes_hwords(struct bblk_t *);
static void convert_inter_block_jumps(struct bblk_t *);
static void merge_insns_to_1fg_list(struct flowg_t *);

static void emit_1mod_asm_insns(struct mod_t *);
static void pipe_1mod_asm_insns(struct mod_t *);
static void emit_1mod_data_section(FILE *, struct mod_t *);
static void emit_dbg_idp_info_symbols(FILE *, struct mod_t *);
static char *get_idp_map_str(char *, struct mod_t *, size_t);
static char *get_fixed_idp_map_str(char *, struct mod_t *, int32);

static void emit_oneflowg_asm(FILE *, struct flowg_t *, struct mod_t *, int32);
static void emit_one_insn(FILE *, char *, ...);
static void emit_optim_scalar_port_npps(FILE *, struct flowg_t *, 
 struct mod_t *, int32);
static void emit_one_scalar_port_optim_1inst(FILE *, struct mod_t *, 
 struct mod_t *, struct net_t *, struct net_t *, struct itree_t *);
static void emit_one_scalar_port_optim_1inst_dmpv(FILE *, struct mod_t *, 
 struct mod_t *, struct net_t *, struct net_t *, struct itree_t *);
static void emit_one_scalar_port_optim(FILE *, struct net_t *, struct net_t *,
 int32);
static void emit_one_scalar_port_optim_dmpv(FILE *, struct mod_t *,
 struct net_t *, struct net_t *, int32);
static void emit_scalar_optim_temp_no_nchg(FILE *, struct mod_t *, 
 struct net_t *);
static void emit_one_scalar_port_optim_nchg_1inst(FILE *, struct mod_t *, 
 struct mod_t *, struct net_t *, struct net_t *, struct itree_t *, int32);
static void emit_one_scalar_port_optim_nchg_1inst_dmpv(FILE *, struct mod_t *, 
 struct mod_t *, struct net_t *, struct net_t *, struct itree_t *, int32);
static void emit_dump_scalar_port_template(FILE *, struct mod_t *, 
 struct net_t *, int32);
static void emit_one_scalar_port_optim_nchg(FILE *, struct net_t *, 
 struct net_t *, int32, int32);
static void emit_one_scalar_port_optim_nchg_dmpv(FILE *, struct mod_t *,
 struct net_t *, struct net_t *, int32, int32);
static void turn_off_used_in_asm_flag(struct flowg_t *);
static char *call_asl_insn_tostr(char *, struct insn_t *);
static char *deflst_insn_tostr(char *, struct insn_t *);
static void bld_comlab_tostr(char *, struct amode_t *, int32);
static char *reg_tostr(char *, struct amode_t *, int32);
static char *dbg_reg_tostr(char *, struct amode_t *);
static void emit_1mod_constants(FILE *, struct mod_t *);
static int32 need_inam(int32);
static char *get_fixed_fg_call_nam(char *, int32);

static void emit_dsgn_wide_asm_file(FILE *, char *);
static void emit_one_mod_init_asm_file(FILE *, char *, struct mod_t *, int32);
static void emit_executable_args_str(FILE *);
static void fill_1mod_ctevs(struct mod_t *);
static void fill_addtolst_ctev_flds(struct mod_t *, struct ctev_t *,
 struct ctev_t **, int32, int32, struct gate_t *);
static void emit_1mod_tev_glbs(FILE *, struct mod_t *);
static int32 correct_walign_nb_rhs_area(int32);
static void asm_wr_globl(FILE *, char *, size_t);
static void emit_1ctev_is1v_dels(FILE *, struct mod_t *, struct ctev_t *,
 int32 *);
static int32 is1v_nds_64bits(union del_u, int32);
static void emit_1mod_nchg_glbs(FILE *, struct mod_t *);
static void emit_1mod_commlabs(FILE *, struct mod_t *, int32);
static void emit_1mod_pth_del_adr_labs(FILE *, struct mod_t *);
static void ll_awr_set_stmt_entptr(FILE *, char *, int32);
static void emit_1mod_tchk_tchg_adr_labs(FILE *, struct mod_t *);

static void emit_dsgn_udptab_adr_labs(FILE *);
static void emit_dsgn_idparea(FILE *, struct mod_t *);
static void emit_ialst_enter_points_array(FILE *, struct mod_t *);
static void emit_process_next_event(FILE *, char *, int32);
static void emit_move_time_routine(FILE *);
static void emit_move_time_routine_nonb(FILE *);
static void emit_next_event(FILE *);
static void emit_jump_to_next_event(FILE *, int32);
static void emit_free_next_event(FILE *, int32);
static int32 exec_command_file(char *, char *);
static void pipe_cvcsim(void);
static void create_cvclib_files(int32);
static void write_binary_file(char *, byte *, int32);
static void run_makefile(void);

static void gen_mkfil_and_compile_solib(void);
static void emit_fixed_text_boiler_plate(FILE *);
static void emit_comm_task_jmptable(FILE *); 
static void emit_last_nchglst_fence(FILE *);
static void emit_boiler_plate_enter_next_events(FILE *);
static void emit_fixed_wrapper_ptrs(FILE *);
static void emit_static_tev_events(FILE *, char *, char *);
static void emit_fixed_scalar_iconn(FILE *, int32, int32);
static void emit_wrapper_routine(FILE *, char *, char *, int32, int32);
static void emit_slotend_action(FILE *);
static void emit_slotend_action_call(FILE *, int32, int32, int32);
static void emit_slotend_monit_code(FILE *, int32, int32);
static int32 is_gate_loaded(struct gate_t *);

static void ll_awr_allmods_init_func_def(FILE *);
static void ll_awr_fixup_allmods_comm_idp_areas(FILE *);
static void ll_awr_alnk_set_tev_nxtptr(FILE *, char *);
static void ll_awr_1mod_init_func_def(FILE *, struct mod_t *);
static void ll_init_glbl_mdp(FILE *, int32);
static void ll_awr_1mod_tevdat_init(FILE *, struct mod_t *);
static int32 is_const_is1v_delay(int32);
static char *ct_get_tev_enterptr_labnam(char *, struct ctev_t *);
static int32 get_const_del(union del_u, int32,  word64 *, int32);
static void ll_awr_init_udptab_adrs(FILE *);
static void ll_awr_init_tchk_tchg_adr(FILE *, struct mod_t *);
static void ll_awr_init_pth_del_adr(FILE *, struct mod_t *);
static void ll_awr_1mod_thrd_ret_stmts(FILE *, struct mod_t *); 

static void ll_awr_init_tev_dat(FILE *, char *, int32, char *, size_t, word64,
 int32);
static void ll_awr_alnk_set_tev_gp_u(FILE *, char *, int32, int32);
static void ll_awr_set_tev_ent_nb_free(FILE *, char *, char *, int32);
static void ll_awr_alnk_tev_set_tu_nbrhs(FILE *, char *, char *,
 int32, int32, int32);
static void ll_awr_alnk_cp_is1v_32b_tev_dels(FILE *, char *, char *, int32);
static void ll_awr_alnk_cp_is1v_64b_tev_dels(FILE *, char *, char *, int32);
static void ll_awr_alnk_init_nchglst_el(FILE *, char *, char *, char *,
 int32, struct net_chg_t *);
static void ll_awr_alnk_set_trchan_vtx_nchgs(FILE *);
static void ll_awr_alnk_set_udptab_adr(FILE *, char *, char *, int32);
static void ll_awr_alnk_set_tchk_tchg_adr(FILE *, char *, int32);
static void ll_awr_alnk_set_pth_del_adr(FILE *, char *, int32);

static void ll_awr_set_glb_movl(FILE *, char *, char *);
static void ll_awr_iaslt_enter_init(FILE *, struct mod_t *);
static void ll_stmt_enter_init(FILE *, struct mod_t *);
static int32 ll_awr_1mod_nchg_init_and_npp_enter(FILE *, struct mod_t *);
static void ll_dce_enter_init(FILE *, struct mod_t *);
static void ll_stmt_addr_init(FILE *, struct mod_t *);
static void ll_dcep_addr_init(FILE *, struct mod_t *);
static void ll_grp_addr_init(FILE *, struct mod_t *);
static void ll_gate_addr_init(FILE *, struct mod_t *);
static void ll_conta_addr_init(FILE *, struct mod_t *);
static void ll_net_addr_init(FILE *, struct mod_t *);
static void ll_task_addr_init(FILE *, struct mod_t *);
static void ll_all_npp_addr_init(FILE *, struct mod_t *);
static void ll_xpr_addr_init(FILE *, struct mod_t *);
static void ll_one_npp_addr_init(FILE *, char *, int32);
static void ll_awr_proc_enter_insns(FILE *);
static void ll_awr_call_proc_leave_insns(FILE *);
static char *ll_2op_insn_to_str(char *, int32, int32, int32, int32, char *,
 int32, int32, int32);
static void ll_pass_arg_insn_to_str(FILE *, char *, int32, int32, 
 int32, size_t, char *, int32);
static char *ll_1op_insn_to_str(char *, int32, int32, int32, int32, char *);
static char *ll_bld_amode_str(char *, int32, int32, size_t, char *);


static int32 cnt_bblk_num(struct flowg_t *);
static void prt_1bblk_cvc_stats(struct flowg_t *, struct bblk_t *);
static FILE *do_popen(char *, char *);
static void do_pclose(FILE *);
static FILE *my_popen(void);
static void my_pclose(FILE *);
static int32 popen_child_process_func(void *);

/* external prototypes */
extern char *__bld_asm_fnam_stem(char *, struct mod_t *);
extern char *__bld_asm_comm_fnam_stem(char *);
extern void __emit_1mod_x86_asm(struct mod_t *);

extern char *__bldchk_var_comm_ref(char *, struct net_t *, struct mod_t *,
 struct task_t *);
extern void __bld_mod_flowg_ndx(struct mod_t *);
extern void __fill_fg_po_bblktab(struct flowg_t *);
extern struct asl_info_t *__to_aslinfo_rec(int32);
extern struct insn_info_t *__to_iinfo_rec(int32);
extern char *__asm_insn_tostr(char *, struct insn_t *, int32, struct flowg_t *);
extern char *__get_jmp_insn_nam(char *, struct insn_t *);
extern char *__bld_amods(char *, struct insn_t *, int32, struct amode_t *,
 int32, struct flowg_t *);
extern char *__gen_comm_lab_amods(char *, struct tn_t *);
extern int32 __is_nlptr_comlab(int32);
extern struct insn_t *__insert_insn(struct insn_t *, int32, int32, int32, ...);
extern char *__bld_nlo_lab_nam(char *, int32);
extern int32 __is_jmp_insn(int32);
extern void __my_ftime(time_t *, time_t *);
extern word32 __get_wrd_con_val(int32);
extern word32 __get_wrd_amode_con_val(struct amode_t *);
extern int32 __amode_mem_ref(struct amode_t *);
extern int32 __is_constant(int32);
extern size_t __calc_ebp_spill_offset(int32, size_t);
extern struct tn_dup_t *__find_add_dup_tn(struct avlhd_t *, word32);
extern struct net_chg_t *__find_nchg_range(struct net_t *, int32, int32);
extern int32 __check_delay_constant(union del_u, int32, word64 *);
extern int32 __get_tmpfnam(char *);
#ifndef __CVC32__
extern word32 __get_stack_size(struct flowg_t *, int32);
#endif

extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern void __crit_msg(char *, ...);
extern void __my_fprintf(FILE *, char *, ...);
extern char *__bld_lineloc(char *, word32, int32);
extern struct avlnode_t **__linearize_avl_tree(struct avlhd_t *, int32 *);
extern char *__xi_stralloc(char *);
extern int32 __needs_netchg_record(struct net_t *);
extern void __gen_dsgn_dat_asm_file(void);
extern void __pipe_dsgn_dat_asm_file(void);

extern void __linkout_insn(struct insn_t *, int32);
extern void __init_amode(struct amode_t *);

extern FILE *__my_fopen(char *, char *);
extern void __my_fclose(FILE *);
extern void __prt_1fg_cvc_stats(struct flowg_t *, struct mod_t *); 
extern char *__to_flowgnam(char *, struct flowg_t *);

extern void __cv_msg(char *s, ...);
extern void __pv_err(int32, char *, ...);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __pv_terr(int32, char *, ...);

/* reg name array */
#ifdef __CVC32__
char *__regs[] = {
 "NONE", "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%ebp", "%esp",
 /* byte eq values */                          
 "%st(1)", "%al", "%bl", "%cl", "%dl", "%si", "%di", "%ebpb", "%espb", 
 /* special real stk reg*/
  "%ax", "%bx", "%cx", "%dx"}; 

/* reg to byte map */
/* AIV LOOKATME - don't really need map could be reg + HIGH GENERAL_REG? */
static int32 reg_bytes[] = {REG_NONE, AL, BL, CL, DL, SI, DI }; 

/* word represtation of registers */
static int32 reg_16bytes[] = {REG_NONE, AX, BX, CX, DX, SI, DI }; 

#else
//AIV LOOKATME - maybe it is better to just add suffix to the reg
//instead of having different reg wasn't so bad with small num of x86 regs
//but not this code is ugly and isn't as portable for future archs with
//even a greater numb of regs
char *__regs[] = {
 "NONE", "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", 
 "%rax", "%rbx", "%rcx", "%rdx", "%rsi", "%rdi", 
 "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15",
 "%rbp", "%rsp", 
 /* byte eq values */                          
 "%badreg", "%al", "%bl", "%cl", "%dl", "%si", "%di", 
 "%r8b", "%r9b", "%r10b", "%r11b", "%r12b", "%r13b", "%r14b", "%r15b", 
 "%ebpb", "%espb", 
 /* 16 - byte regs */
  "%ax", "%bx", "%cx", "%dx",
  "%r8w", "%r9w", "%r10w", "%r11w", "%r12w", "%r13w", "%r14w", "%r15w", 
  /* AIV 09/08/10 - these 32-bit regs are now supported */
  "%r8d", "%r9d", "%r10d", "%r11d", "%r12d", "%r13d", "%r14d", 
  "%r15d"}; 
 

static int32 reg_bytes[] = {REG_NONE, REG_NONE, REG_NONE, REG_NONE, REG_NONE,
 REG_NONE, REG_NONE, AL, BL, CL, DL, SI, DI, 
 R8B, R9B, R10B, R11B, R12B, R13B, R14B, R15B}; 

static int32 reg_16bytes[] = {REG_NONE, REG_NONE, REG_NONE, REG_NONE, REG_NONE,
 REG_NONE, REG_NONE, AX, BX, CX, DX, SI, DI,
 R8W, R9W, R10W, R11W, R12W, R13W, R14W, R15W}; 

/* AIV 08/03/10 - added ability to do 4-byte movl on 64-bit machines */
static int32 reg_32bytes[] = {REG_NONE, REG_NONE, REG_NONE, REG_NONE, REG_NONE,
 REG_NONE, REG_NONE, EAX, EBX, ECX, EDX, ESI, EDI,
 R8D, R9D, R10D, R11D, R12D, R13D, R14D, R15D}; 
#endif

/*
 * ROUTINES TO GEN (LOWER) ONE MODULE TO ASCII X86 .S FILE MACHINE INSNS
 */

/*
 * routine to emit the .s file and assembly it for one module
 *
 * insns as a list aleady gened and optimized by the bbgen/bbopt code
 * always runs with interpreter inst mod global set
 */
extern void __emit_1mod_x86_asm(struct mod_t *mdp)
{
 /* build the mod flow graph bblk index once for all of this */
 __bld_mod_flowg_ndx(mdp);

 map_1mod_to_linearized_x86_insn(mdp); 

 /* AIV 07/21/08 - save __next_nchlp in a reg if there is a reg avail */
 save_fgs_next_nchg_in_reg_and_merge_fgips();

/* --- PUT ME BACK - FOR LOOKING AT MERGED INSN  
 if (__opt_debug_flg)
  {
   int32 fgi;
   struct insn_t *ip;
   char iline[RECLEN];
    
   __my_fprintf(stdout, "\nFINAL LINEARIZED INTO FLOW GRAPH ASM:\n");
   for (fgi = 0; fgi <= __flowg_lasti; fgi++)
    {
     for (ip = __flowgtab[fgi]->fg_ihd; ip != NULL; ip = ip->inxt)
      {
       if (__asm_emit_loc == 3)
        {
         __my_fprintf(stdout, "%s #%d\n", __asm_insn_tostr(iline, ip, TRUE),
          ip->ndx);
        }
       else __my_fprintf(stdout, "%s\n", __asm_insn_tostr(iline, ip, TRUE));
      }
    }
  }
--- */

 /* write the .s file */
 if (__show_asm) emit_1mod_asm_insns(mdp);
 else pipe_1mod_asm_insns(mdp);
}

/*
 * save __next_nchlp in a reg if there is a reg avail for PROCESS_NCHG fgs
 */
static void save_fgs_next_nchg_in_reg_and_merge_fgips(void)
{
 int32 fgi;
 struct flowg_t *fgp;

 __cur_bbp = NULL;
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   fgp = __flowgtab[fgi];
   __fill_fg_po_bblktab(fgp);
   /* AIV 09/03/08 - this now needs to merge fgp - here */
   /* was doing prior to here which made the save routine run slow */
   /* because the ip->inxt were already linked for fgps - so it was */
   /* doing the entire fg of instructions not a block */
   if (fgp->flowgtyp != FLOWG_PROCESS_NCHG) 
    {
     /* finally merge all bblk insn into one flow graph list */
     merge_insns_to_1fg_list(fgp);
     continue;
    }
   try_to_save_next_nchg_in_reg(fgp);

   /* finally merge all bblk insn into one flow graph list */
   merge_insns_to_1fg_list(fgp);
  }
}

/* 
 * for PROCESS_NCHG fg use a reg instead of memory __next_nchglp
 * this isn't loaded in reg to begin with because it may cause spill
 * and ruins reg alloc performance since it might be live across a large
 * number of blocks 
 * just does the easy fixup
 *
 * movl	%eax, __next_nchglp
 * movl	mdat_0 + 40, %eax
 * movl	%eax, mdat_1 + 40
 * movl	mdat_0 + 44, %eax
 * movl	%eax, mdat_1 + 44
 * movl	__next_nchglp, %eax
 * => changes to
 *  use ebx since available
 * movl	%eax, %ebx
 * movl	mdat_0 + 40, %eax
 * movl	%eax, mdat_1 + 40
 * movl	mdat_0 + 44, %eax
 * movl	%eax, mdat_1 + 44
 * movl	%ebx, %eax
 */
static void try_to_save_next_nchg_in_reg(struct flowg_t *fgp)
{
 struct insn_t *ip, *prev_ip, *ip2;
 struct amode_t *srcp, *dstp;
 struct bblk_t *bbp;
 int32 blki, reg, has_call, i, use_reg, next_save, next_restore, start_reg;
 int32 used_regs[HIGH_X86_REG+1];

 /* AIV 07/09/09 - fixed flow graph nothing to do */
 if (fgp->optim_scalar_port) return;

 /* zero available regs */
 memset(used_regs, 0, (HIGH_X86_REG+1)*INTBYTES);
 has_call = FALSE;
 /* record if there is a call and which regs are used */
 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   /* SJM 12/03/06 - block may already have been removed */
   if (bbp == NULL) continue; 
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     if (ip->opcod == I_CALL || ip->opcod == I_FG_CALL || 
         ip->opcod == I_ASL_CALL)
      {
       has_call = TRUE;
       continue;
      }

     srcp = &(ip->isrc);
     reg = srcp->x86_regno;
     if (reg != REG_NONE && reg <= HIGH_X86_REG) used_regs[reg] = TRUE;
     dstp = &(ip->idst);
     reg = dstp->x86_regno;
     if (reg != REG_NONE && reg <= HIGH_X86_REG) used_regs[reg] = TRUE;

     if (srcp->amode == AM_NLO && srcp->disp == NLO_NEXT_NCHGLP)
      {
       break;
      }
    }
  }

 /* 64-bit address must be stored in 64-bit reg */
#ifdef __CVC32__
 start_reg = EAX;
#else
 start_reg = RAX;
#endif
 /* find a reg - if call can only use ebx, edi, esi */
 use_reg = -1;
 if (has_call)
  {
   use_reg = get_free_callee_save_reg(used_regs);
   if (use_reg == -1) return;
  }
 else
  {
   /* use any general reg */
   for (i = start_reg; i <= HIGH_GEN_REG; i++) 
    {
     if (!used_regs[i]) 
      {
       /* AIV 10/21/08 - was skipping byte/word registers which could be */
       /* overwritten by the byte/word usage */
       /* AIV 12/02/08 - can now use ebp has a general reg - has no byte/word */
       /* register usage */
       if (i == AR_BP) 
        {
         use_reg = AR_BP;
         break;
        }
       /* AIV 08/03/10 - need to check 4-byte copy on 64-bit machines  */
#ifdef __CVC32__
       if (!(used_regs[reg_bytes[i]]) && !(used_regs[reg_16bytes[i]]))
#else
       if (!(used_regs[reg_bytes[i]]) && !(used_regs[reg_16bytes[i]])
            && !(used_regs[reg_32bytes[i]]))
#endif
        {
         use_reg = i;
         break;
        }
      }
    }
   if (i > HIGH_GEN_REG) return;
  }

 /* DBG remove -- */
 if (use_reg == -1) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* do the fixup using the register */
 next_save = next_restore = FALSE;
 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   if (bbp == NULL) continue; 
   __cur_bbp = bbp;
   prev_ip = NULL;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     dstp = &(ip->idst);
     if (dstp->amode == AM_NLO && dstp->disp == NLO_NEXT_NCHGLP)
      {
       next_save = TRUE;
       dstp = &(prev_ip->idst);
       dstp->amode = AM_REG;
       dstp->x86_regno = use_reg;
       /* AIV 10/23/08 - can always remove the extra movl insn */
       __linkout_insn(ip, TRUE);
       continue;
      }
     srcp = &(ip->isrc);
     prev_ip = ip;
     if (srcp->amode == AM_NLO && srcp->disp == NLO_NEXT_NCHGLP)
      {
       next_restore = TRUE;
       srcp->amode = AM_REG;
       srcp->x86_regno = use_reg;
       break;
      }
    }
  }
 /* DBG remove -- */
 if (!next_save || !next_restore) __misc_terr(__FILE__, __LINE__);
 /* ---- */
}


#ifdef __CVC32__
/*
 * return an available calleed saved register 32-bit
 * ebx, edi, esi
 */
static int32 get_free_callee_save_reg(int32 *used_regs)
{
 int32 free_reg;

 /* AIV 10/21/08 - was skipping byte/word registers which could be */
 /* overwritten by the byte/word usage */
 free_reg = -1;
 if (!used_regs[EBX] && !used_regs[BL] && !used_regs[BX]) free_reg = EBX;
 else if (!used_regs[EDI]) free_reg = EDI;
 else if (!used_regs[ESI]) free_reg = ESI;
 /* AIV 12/02/08 - can now use ebp has a general reg - has no byte/word */
 else if (!used_regs[EBP]) free_reg = EBP;
 return(free_reg);
}
#else
/*
 * return an available calleed saved register 64-bit
 * rbx, and r12-r15
 */
static int32 get_free_callee_save_reg(int32 *used_regs)
{
 int32 free_reg;

 free_reg = -1;
 if (!used_regs[RBX] && !used_regs[BL] && !used_regs[BX]) free_reg = RBX;
 else if (!used_regs[R12] && !used_regs[R12B] && !used_regs[R12W]) 
  {
   free_reg = R12;
  }
 else if (!used_regs[R13] && !used_regs[R13B] && !used_regs[R13W]) 
  {
   free_reg = R13;
  }
 else if (!used_regs[R14] && !used_regs[R14B] && !used_regs[R14W]) 
  {
   free_reg = R14;
  }
 else if (!used_regs[R15] && !used_regs[R15B] && !used_regs[R15W]) 
  {
   free_reg = R15;
  }
 /* AIV 12/02/08 - can now use ebp has a general reg - has no byte/word */
 else if (!used_regs[AR_BP]) free_reg = AR_BP;
 return(free_reg);
}
#endif

/*
 * final mapping of our virtual machine insns to x86 2 addr insns
 * 
 * routines called from here assume mod flowg index table built
 */
static void map_1mod_to_linearized_x86_insn(struct mod_t *mdp) 
{
 int32 fgi, blki;
 struct flowg_t *fgp;
 struct bblk_t *bbp;

 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   fgp = __flowgtab[fgi];

   __fill_fg_po_bblktab(fgp);
   for (blki = 1; blki < fgp->fg_num_bblks; blki++)
    {
     bbp = __bblktab[blki];
     /* SJM 12/02/06 - bblk maybe removed but RPOs numbers not re assigned */
     if (bbp == NULL) continue;

     __cur_bbp = bbp;

//SJM 08/14/06 - think this needs to be moved into bbopt?
     /* convert con tags to immediate values */
     change_contags_to_imms(bbp);

     lower_epilogue_prologue(bbp, fgp);

     /* convert inter-block jumps - now with continue/break - may be in */
     /* middle of block - not on the tail end */
     convert_inter_block_jumps(bbp);

     /* AIV 02/22/10 - no longer need to get and print the enter func name */
     /* removed .size for OSX */
     lower_bblk_enter_exits(mdp, bbp);

     /* convert 32 bit insns to narrow byte and hwords op code where needed */
     convert_insn_bytes_hwords(bbp);
    }
   __cur_bbp = NULL;
   /* 08/21/06 - now printing per flow graph insn stats */
   if (__opt_prt_stats) __prt_1fg_cvc_stats(fgp, mdp);
  }
}

/*
 * fix to mem2mem references for all the bblks in one flow graph
 */
static void change_contags_to_imms(struct bblk_t *bbp)
{
 struct insn_t *ip, *ip2;
 struct amode_t *srcp, *dstp;

 for (ip = bbp->ihd; ip != NULL; ip = ip2)
  {
   ip2 = ip->inxt;
   srcp = &(ip->isrc);
   /* AIV 01/21/11 - this needs to check the instruction - if real */
   /* x86 needs to pass as a memory value - before was just not */
   /* turning tmps into reals if marked as constant */
   if (is_real_insn(ip)) continue;
   try_convert_amode_to_imm(srcp);
   dstp = &(ip->idst);
   try_convert_amode_to_imm(dstp); 
  }
}

/*
 * return TRUE if this is a real insn
 */
static int32 is_real_insn(struct insn_t *ip)
{
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(ip->opcod);
 switch (iip->iclass) {
  case ICLASS_REAL_1RD:
  case ICLASS_REAL_NORD:
  case ICLASS_REAL_WRAX:
   return(TRUE);
 }
 return(FALSE);
}

/*
 * convert gen cint tn to x86 insn immediate
 */
static int32 try_convert_amode_to_imm(struct amode_t *amp)
{
 struct tn_t *tnp;
 word32 cval;

 if (amp->am_tni == -1) return(FALSE);

 tnp = &(__tntab[amp->am_tni]);
 /* AIV 07/31/06 - don't convert real constants used as 64 bit wide */
 /* AIV 01/21/11 - this really depends on the instruction not the type */
 /* of the constant */
 /* if (tnp->t_real) return(FALSE); */

 if (tnp->comlab_typ == COMLAB_CINT)
  {
   /* SJM 10/11/06 - NOTICE that numbers (cints) are not quite labels but */
   /* are comlabs whose name happens to be the same as the numeric value */ 
   amp->amode = AM_IMM;
   amp->disp = tnp->tncu.tn_cint;
   amp->am_tni = -1;
   return(TRUE);
  }
 if (tnp->comlab_typ != COMLAB_CONADR) return(FALSE);
 /* if not index reg, con adr used as wide */
 if (amp->amode != AM_NDXREG && amp->amode != AM_NDXREG_DISP) return(FALSE);

 /* SJM 11/13/06 - NEW CONVENTION - must never see wider than WBITS in */
 /* machine insns - only ASL wrappers and intermediate (copy?) can be wide */
 if (tnp->tnwid > WBITS) __misc_terr(__FILE__, __LINE__);

 cval = __get_wrd_amode_con_val(amp);

 /* SJM 10/11/06 - here the tn is the b part so the returned bval will */ 
 /* be wrong so just ignore */

 amp->amode = AM_IMM;
 amp->disp = cval;
 amp->am_tni = -1;
 return(TRUE);
}

/*
 * T => amode is a memory reference (label of something in per mod comm area)
 */
extern int32 __amode_mem_ref(struct amode_t *amp)
{
 struct tn_t *tnp;

 if (amp->am_tni == -1) return(FALSE);

 tnp = &(__tntab[amp->am_tni]);
 
 /* if nlo amode type - __epair(%eax) */
 if (amp->arr_base_nlo != NLO_NONE) return(TRUE);

 /* if it is spilled it is in memory */
 if (tnp->tn_spilled) return(TRUE);

 /* nlo comlab or nlptr are always accessed as a memory */
 if (tnp->comlab_typ != COMLAB_NONE)
  {
   if (__is_constant(amp->am_tni)) return(FALSE);

   if (__is_nlptr_comlab(tnp->comlab_typ)) return(TRUE);
  }

 switch(amp->amode) {
  case AM_NDXREG: case AM_NDXREG_DISP: case AM_NONREG_OFS: case AM_NLO:
   return(TRUE);
  case AM_REG: break;
  default: break;
 }
 return(FALSE);
}

/*
 * ROUTINES TO CONVERT MEDIUM LEVEL INSNS TO MACH INSNS
 */

/*
 * change ipilogue and prologue insns to the stack adjust machine insns
 *
 * tricky because for tasks, leave not one from end  
 * this also changes ASL call restore to the addl
 * FIXME - need to change so can use I_LEAVE for returns even with callee save
 */
#ifdef __CVC32__
static void lower_epilogue_prologue(struct bblk_t *bbp, struct flowg_t *fgp)
{
 struct tev_t *tevp;
 struct insn_t *ip, *ip2, *ip3;
 struct nchglst_t *nchgp;
 int32 callee_count, nwrds;
 size_t offset;

 callee_count = 0;
 if (fgp->uses_ebx) callee_count++;
 if (fgp->uses_edi) callee_count++;
 /* AIV 12/17/09 - this should be uses_esi not uses_edi */
 if (fgp->uses_esi) callee_count++;
 if (fgp->uses_ebp) callee_count++;

 for (ip = bbp->ihd; ip != NULL; ip = ip2)
  {
   ip2 = ip->inxt;
   if (ip->opcod == I_PROLOGUE)
    {
     if (flow_graphs_needs_call_save_regs(fgp))
      {
       if (fgp->uses_edi)
        {
         __insert_insn(ip, FALSE, I_PUSHA, AM_NONE, AM_REG, AR_DI);
        }
       if (fgp->uses_esi)
        {
         __insert_insn(ip, FALSE, I_PUSHA, AM_NONE, AM_REG, AR_SI);
        }
       if (fgp->uses_ebx)
        {
         __insert_insn(ip, FALSE, I_PUSHA, AM_NONE, AM_REG, AR_BX);
        }
      }
     /* AIV 10/21/09 - no need to push space for non call save fgs */
     /* of tasks - just set to zero saves  subl/addl of esp */
     else if (fgp->flowgtyp != FLOWG_TASK) fgp->max_call_args = 0;

     if (fgp->uses_ebp)
      {
       __insert_insn(ip, FALSE, I_PUSHA, AM_NONE, AM_REG, AR_BP);
      }
     /* SJM 09/11/06 - if no spilling - do not allocate stack area */
     /* stack must now alloc space for call args as well */
     if (fgp->has_overflow)
      {
       nwrds = (fgp->ebp_wrd_area_siz+fgp->max_call_args+callee_count);
       __insert_insn(ip, FALSE, I_SUBA, AM_IMM, WRDBYTES*nwrds, AM_REG, AR_SP);
      }  
     else if (fgp->max_call_args)
      {
       __insert_insn(ip, FALSE, I_SUBA, AM_IMM, 
        WRDBYTES*(fgp->max_call_args), AM_REG, AR_SP);
      }
     __linkout_insn(ip, TRUE);
    }
   else if (ip->opcod == I_EPILOGUE)
    {
     /* SJM 09/11/06 - if no spilling - do not allocate stack area */
     /* stack must now alloc space for call args as well */
     if (fgp->has_overflow)
      {
       nwrds = (fgp->ebp_wrd_area_siz+fgp->max_call_args+callee_count);
       __insert_insn(ip, FALSE, I_ADDA, AM_IMM, WRDBYTES*nwrds, AM_REG, AR_SP);
      } 
     else if (fgp->max_call_args)
      {
       __insert_insn(ip, FALSE, I_ADDA, AM_IMM, 
         WRDBYTES*(fgp->max_call_args), AM_REG, AR_SP);
      } 
     if (fgp->uses_ebp)
      {
       __insert_insn(ip, FALSE, I_POPA, AM_NONE, AM_REG, AR_BP);
      }
     if (flow_graphs_needs_call_save_regs(fgp))
      {
       if (fgp->uses_ebx)
        {
         __insert_insn(ip, FALSE, I_POPA, AM_NONE, AM_REG, AR_BX);
        }
       if (fgp->uses_esi)
        {
         __insert_insn(ip, FALSE, I_POPA, AM_NONE, AM_REG, AR_SI);
        }
       if (fgp->uses_edi)
        {
         __insert_insn(ip, FALSE, I_POPA, AM_NONE, AM_REG, AR_DI);
        }
       }
     __linkout_insn(ip, TRUE);
    }
   else if (ip->opcod == I_NEXT_EVENT)
    {
     /* AIV 10/12/07 - set trigger bit to off for all except nb pnd0 */
     /* the non-blocking might reschedule which will set the bit at runtime */
     tevp = __free_event_tevp;
     /* AIV 10/31/07 - only if it is nb can it have new alloc events */
     /* AIV 10/14/08 - rewrote these next jump code to use different regs */
     /* makes a slight difference since code is always executed */
     if (fgp->is_nb_free)
      {
       __insert_insn(ip, FALSE, I_MOVA, AM_NLO, NLO_CUR_TEVP, AM_REG, AR_AX);
       if (!fgp->has_nb_pnd0s)
        {
         /* __cur_tevp->trigger = FALSE */
         offset = (byte *) &(tevp->trigger) - (byte *) tevp;
         __insert_insn(ip, FALSE, I_MOVA, AM_IMM, 0, AM_NDXREG_DISP, AR_AX, 
            offset);
        }
     
       /* rhs memory may need to be freed as well otherwise just event */
       if (fgp->is_nb_rhs_mem)
        {
         __insert_insn(ip, FALSE, I_CALL_FREE_NBMEM_EVENT, AM_NONE, AM_NONE); 
        }
       else __insert_insn(ip, FALSE, I_CALL_FREE_EVENT, AM_NONE, AM_NONE); 
      }
     else 
      {
        __insert_insn(ip, FALSE, I_MOVA, AM_NLO, NLO_CUR_TEVP, AM_REG, AR_CX);
       /* AIV - same as emit_next_event */
       offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
       //fprintf(fp, "\tmovl   %d(%%eax), %%eax\n", offset);
       __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP, AR_CX, offset, AM_REG, 
        AR_AX);

       offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
       __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP, AR_AX, offset, AM_REG, 
        AR_BX);

       offset = (byte *) &(tevp->te_idp) - (byte *) tevp;
       __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP, AR_AX, offset, AM_REG, 
        IDP_REG);

       /* AIV 10/31/07 - only if it is nb can it have new alloc events */
       if (!fgp->has_nb_pnd0s)
        {
         /* __cur_tevp->trigger = FALSE */
         offset = (byte *) &(tevp->trigger) - (byte *) tevp;
         __insert_insn(ip, FALSE, I_MOVA, AM_IMM, 0, AM_NDXREG_DISP, AR_CX, 
          offset);
        }
       __insert_insn(ip, FALSE, I_MOVA, AM_REG, AR_AX, AM_NLO, NLO_CUR_TEVP);
       __insert_insn(ip, FALSE, I_NEVENT_JMP, AM_NONE, AM_REG, AR_BX);
      }
     __linkout_insn(ip, TRUE);
     /* AIV 01/26/10 - if known to jump to next event remove the 'ret' */
     /* insn - will not be returning */
     if (ip2 != NULL)
      {
       if (ip2->opcod == I_SUSPEND || ip2->opcod == I_RETURN 
           || ip2->opcod == I_COMPLETE)
        {
         ip3 = ip2->inxt;
         __linkout_insn(ip2, TRUE);
         ip2 = ip3;
        }
      }
    }
   else if (ip->opcod == I_NEXT_NCHG_EVENT)
    {
     __insert_insn(ip, FALSE, I_MOVA, AM_NLO, NLO_NEXT_NCHGLP, AM_REG, AR_AX);
     nchgp = &__nchg_dummy_hd;
     offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
     __insert_insn(ip, FALSE, I_MOVA, AM_NDXREG_DISP, AR_AX, offset, AM_REG, 
        AR_BX);
     __insert_insn(ip, FALSE, I_NEVENT_JMP, AM_NONE, AM_REG, AR_BX);
     __linkout_insn(ip, TRUE);
     /* AIV 01/26/10 - if known to jump to next event remove the 'ret' */
     /* insn - will not be returning */
     if (ip2 != NULL)
      {
       if (ip2->opcod == I_SUSPEND || ip2->opcod == I_RETURN 
           || ip2->opcod == I_COMPLETE)
        {
         ip3 = ip2->inxt;
         __linkout_insn(ip2, TRUE);
         ip2 = ip3;
        }
      }
    }
   else if (ip->opcod == I_ASL_REST_STK)
    {
     __insert_insn(ip, FALSE, I_ADDA, AM_IMM, ip->idst.disp, AM_REG, AR_SP);
     __linkout_insn(ip, TRUE);
    }
  }
}
#else
/*
 * AIV 12/03/08 - new algorithm (for now at least)
 * 64-bit must be aligned on 16 bytes
 *
 * following possibilties
 * 1) no stack, no save regs - do nothing
 * 2) no stack, save regs - just push/pop
 * 3) stack, no save regs - just sub/add rsp
 * 4) stack, save regs,  - just sub/add with extra space on rsp for save regs
 *
 * this was causing sprintf with doubles to fail think this is because
 * the stack wasn't aligned on 16 bytes
 */
static void lower_epilogue_prologue(struct bblk_t *bbp, struct flowg_t *fgp)
{
 struct tev_t *tevp;
 struct insn_t *ip, *ip2, *ip3;
 struct nchglst_t *nchgp;
 int32 callee_count, needs_call_save, stack_size;
 size_t offset, osize;

 /* get callee register count */
 callee_count = 0;
 if (fgp->uses_ebx) callee_count++;
 if (fgp->uses_ebp) callee_count++;
 if (fgp->uses_r12) callee_count++;
 if (fgp->uses_r13) callee_count++;
 if (fgp->uses_r14) callee_count++;
 if (fgp->uses_r15) callee_count++;

 needs_call_save = flow_graphs_needs_call_save_regs(fgp);

 for (ip = bbp->ihd; ip != NULL; ip = ip2)
  {
   ip2 = ip->inxt;
   if (ip->opcod == I_PROLOGUE)
    {
     if (needs_call_save)
      {
       /* needs to save regs and no stack just push/pop */
       if (!fgp->has_overflow)
        {
         if (fgp->uses_ebx)
          {
           __insert_insn(ip, FALSE, I_PUSHQ, AM_NONE, AM_REG, RBX);
          }
         if (fgp->uses_r12)
          {
           __insert_insn(ip, FALSE, I_PUSHQ, AM_NONE, AM_REG, R12);
          }
         if (fgp->uses_r13)
          {
           __insert_insn(ip, FALSE, I_PUSHQ, AM_NONE, AM_REG, R13);
          }
         if (fgp->uses_r14)
          {
           __insert_insn(ip, FALSE, I_PUSHQ, AM_NONE, AM_REG, R14);
          }
         if (fgp->uses_r15)
          {
           __insert_insn(ip, FALSE, I_PUSHQ, AM_NONE, AM_REG, R15);
          }
         if (fgp->uses_ebp)
          {
           __insert_insn(ip, FALSE, I_PUSHQ, AM_NONE, AM_REG, RBP);
          }
         /* if only push off number adjust stack by 8 */
         if (((callee_count*WRDBYTES) % 16) != 0)
          {
           __insert_insn(ip, FALSE, I_SUBA, AM_IMM, 8, AM_REG, AR_SP);
          }
        }
       else if (callee_count >= 1)
        {
         /* stack with callee save regs */
         stack_size = __get_stack_size(fgp, callee_count);
          __insert_insn(ip, FALSE, I_SUBA, AM_IMM, stack_size, AM_REG, RSP);
         osize = WRDBYTES*(fgp->ebp_wrd_area_siz);
         if (fgp->uses_ebx)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_REG, RBX, AM_NDXREG_DISP, 
             RSP, osize);
          }
         if (fgp->uses_r12)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_REG, R12, AM_NDXREG_DISP, 
             RSP, osize);
          }
         if (fgp->uses_r13)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_REG, R13, AM_NDXREG_DISP, 
             RSP, osize);
          }
         if (fgp->uses_r14)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_REG, R14, AM_NDXREG_DISP, 
             RSP, osize);
          }
         if (fgp->uses_r15)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_REG, R15, AM_NDXREG_DISP, 
             RSP, osize);
          }
         if (fgp->uses_ebp)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_REG, RBP, AM_NDXREG_DISP, 
             RSP, osize);
          }
        }
       else if (fgp->has_overflow)
        {
         /* regular stack - no save regs */
         stack_size = __get_stack_size(fgp, 0);
         __insert_insn(ip, FALSE, I_SUBA, AM_IMM, stack_size, AM_REG, RSP);
        }
       }
      else if (fgp->has_overflow)
       {
        /* regular stack - no save regs */
        stack_size = __get_stack_size(fgp, 0);
        __insert_insn(ip, FALSE, I_SUBA, AM_IMM, stack_size, AM_REG, RSP);
       }

     __linkout_insn(ip, TRUE);
    }
   else if (ip->opcod == I_EPILOGUE)
    {
     /* same as prologue is in reverse to restore values */
     if (needs_call_save)
      {
       if (!fgp->has_overflow)
        {
         if (((callee_count*WRDBYTES) % 16) != 0)
          {
           __insert_insn(ip, FALSE, I_ADDQ, AM_IMM, 8, AM_REG, AR_SP);
          }
         if (fgp->uses_ebp)
          {
           __insert_insn(ip, FALSE, I_POPQ, AM_NONE, AM_REG, RBP);
          }
         if (fgp->uses_r15)
          {
           __insert_insn(ip, FALSE, I_POPQ, AM_NONE, AM_REG, R15);
          }
         if (fgp->uses_r14)
          {
           __insert_insn(ip, FALSE, I_POPQ, AM_NONE, AM_REG, R14);
          }
         if (fgp->uses_r13)
          {
           __insert_insn(ip, FALSE, I_POPQ, AM_NONE, AM_REG, R13);
          }
         if (fgp->uses_r12)
          {
           __insert_insn(ip, FALSE, I_POPQ, AM_NONE, AM_REG, R12);
          }
         if (fgp->uses_ebx)
          {
           __insert_insn(ip, FALSE, I_POPQ, AM_NONE, AM_REG, RBX);
          }
        }
       else if (callee_count >= 1)
        {
         stack_size = __get_stack_size(fgp, callee_count);
         osize = WRDBYTES*(fgp->ebp_wrd_area_siz);
         if (fgp->uses_ebx)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RSP, osize, 
            AM_REG, RBX);
          }
         if (fgp->uses_r12)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RSP, osize, 
            AM_REG, R12);
          }
         if (fgp->uses_r13)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RSP, osize, 
            AM_REG, R13);
          }
         if (fgp->uses_r14)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RSP, osize, 
            AM_REG, R14);
          }
         if (fgp->uses_r15)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RSP, osize, 
            AM_REG, R15);
          }
         if (fgp->uses_ebp)
          {
           osize += WRDBYTES;
           __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RSP, osize, 
            AM_REG, RBP);
          }
         __insert_insn(ip, FALSE, I_ADDA, AM_IMM, stack_size, AM_REG, RSP);
        }
       else if (fgp->has_overflow)
        {
         stack_size = __get_stack_size(fgp, 0);
         __insert_insn(ip, FALSE, I_ADDA, AM_IMM, stack_size, AM_REG, RSP);
        }
       }
     else if (fgp->has_overflow)
      {
       stack_size = __get_stack_size(fgp, 0);
       __insert_insn(ip, FALSE, I_ADDA, AM_IMM, stack_size, AM_REG, RSP);
      }
     __linkout_insn(ip, TRUE);
    }
   else if (ip->opcod == I_NEXT_EVENT)
    {
     /* AIV 10/12/07 - set trigger bit to off for all except nb pnd0 */
     /* the non-blocking might reschedule which will set the bit at runtime */
     tevp = __free_event_tevp;
     /* AIV 10/31/07 - only if it is nb can it have new alloc events */
     /* AIV 10/14/08 - rewrote these next jump code to use different regs */
     /* makes a slight difference since code is always executed */
     if (fgp->is_nb_free)
      {
       __insert_insn(ip, FALSE, I_MOVQ, AM_NLO, NLO_CUR_TEVP, AM_REG, RAX);
       if (!fgp->has_nb_pnd0s)
        {
         /* __cur_tevp->trigger = FALSE */
         offset = (byte *) &(tevp->trigger) - (byte *) tevp;
         __insert_insn(ip, FALSE, I_MOVQ, AM_IMM, 0, AM_NDXREG_DISP, RAX, 
            offset);
        }
     
       /* rhs memory may need to be freed as well otherwise just event */
       if (fgp->is_nb_rhs_mem)
        {
         __insert_insn(ip, FALSE, I_CALL_FREE_NBMEM_EVENT, AM_NONE, AM_NONE); 
        }
       else __insert_insn(ip, FALSE, I_CALL_FREE_EVENT, AM_NONE, AM_NONE); 
      }
     else 
      {
       __insert_insn(ip, FALSE, I_MOVQ, AM_NLO, NLO_CUR_TEVP, AM_REG, RCX);
       /* AIV - same as emit_next_event */
       offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
       //fprintf(fp, "\tmovl   %d(%%eax), %%eax\n", offset);
       __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RCX, offset, AM_REG, 
        RAX);

       offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
       __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RAX, offset, AM_REG, 
        RBX);

       offset = (byte *) &(tevp->te_idp) - (byte *) tevp;
       __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RAX, offset, AM_REG, 
        IDP_REG);

       /* AIV 10/31/07 - only if it is nb can it have new alloc events */
       if (!fgp->has_nb_pnd0s)
        {
         /* __cur_tevp->trigger = FALSE */
         offset = (byte *) &(tevp->trigger) - (byte *) tevp;
         __insert_insn(ip, FALSE, I_MOVQ, AM_IMM, 0, AM_NDXREG_DISP, RCX, 
          offset);
        }
       __insert_insn(ip, FALSE, I_MOVQ, AM_REG, RAX, AM_NLO, NLO_CUR_TEVP);
       __insert_insn(ip, FALSE, I_NEVENT_JMP, AM_NONE, AM_REG, RBX);
      }

     __linkout_insn(ip, TRUE);
     /* AIV 01/26/10 - if known to jump to next event remove the 'ret' */
     /* insn - will not be returning */
     if (ip2 != NULL)
      {
       if (ip2->opcod == I_SUSPEND || ip2->opcod == I_RETURN 
           || ip2->opcod == I_COMPLETE)
        {
         ip3 = ip2->inxt;
         __linkout_insn(ip2, TRUE);
         ip2 = ip3;
        }
      }
    }
   else if (ip->opcod == I_NEXT_NCHG_EVENT)
    {
     __insert_insn(ip, FALSE, I_MOVQ, AM_NLO, NLO_NEXT_NCHGLP, AM_REG, RAX);
     nchgp = &__nchg_dummy_hd;
     offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
     __insert_insn(ip, FALSE, I_MOVQ, AM_NDXREG_DISP, RAX, offset, AM_REG, 
        RBX);
     __insert_insn(ip, FALSE, I_NEVENT_JMP, AM_NONE, AM_REG, RBX);
     __linkout_insn(ip, TRUE);
     /* AIV 01/26/10 - if known to jump to next event remove the 'ret' */
     /* insn - will not be returning */
     if (ip2 != NULL)
      {
       if (ip2->opcod == I_SUSPEND || ip2->opcod == I_RETURN 
           || ip2->opcod == I_COMPLETE)
        {
         ip3 = ip2->inxt;
         __linkout_insn(ip2, TRUE);
         ip2 = ip3;
        }
      }
    }
   else if (ip->opcod == I_ASL_REST_STK)
    {
     __insert_insn(ip, FALSE, I_ADDQ, AM_IMM, ip->idst.disp, AM_REG, RSP);
     __linkout_insn(ip, TRUE);
    }
  }
}

/*
 * routine to make sure stack is aligned on 16 bytes
 * gets into problems for sprintf - stack must be aligned on 16 bytes 
 */
extern word32 __get_stack_size(struct flowg_t *fgp, int32 push_count)
{
 word32 stack_size;

 /* +1 for call area already pushed */
 /* must take into account the push count */
 stack_size = WRDBYTES*(fgp->ebp_wrd_area_siz+push_count+1);
 if ((stack_size % 16) != 0) 
  {
   stack_size += WRDBYTES;
  }
 return(stack_size);
}
#endif


/*
 * return T if flow graph must save the callee saved registers
 */
static int32 flow_graphs_needs_call_save_regs(struct flowg_t *fgp)
{
 /* all those which can be called from the lowered code must save the regs */
 switch (fgp->flowgtyp) {
  case FLOWG_PROC:
   /* if flow graph can be entered via stp->enterptr (thread wrapper) */
   /* need to save the callee regs in case the wrapper code uses these */
   /* register */
   return(fgp->has_thread_ctrl);
  /* AIV 02/12/10 - tasks needs to go here as well - can can be called */
  /* and need to save regs - found this bug on OSX */
  case FLOWG_TASK:
  case FLOWG_FUNC:
  case FLOWG_MULTFI:
  case FLOWG_GATECA:
  case FLOWG_ICONN:
  case FLOWG_CONTA:
  /* these can be called from __asl_process_alloced_nchg which gcc */
  /* may optimize to use callee regs so must save */
  case FLOWG_DCE:
  case FLOWG_NPP:
   return(TRUE);
  }
 return(FALSE);
}

/*
 * lower medium level jumps and enter exits to x86 machine instruction boiler
 * plate sequences
 *
 * now boiler plater enter and exits especially jumps are kepts as medium
 * level jumps until final asm gen since they are just expanded boiler plate
 */
static void lower_bblk_enter_exits(struct mod_t *mdp, struct bblk_t *bbp) 
{
 int32 bblk_num, ndx, t_seqno, f_seqno, i, linkout_start, jtabsize;
 struct insn_t *start_ip, *end_ip, *new_ip;
 struct bblk_t *lbbp;
 char s1[RECLEN], s2[RECLEN];
 struct ndxjmp_t *ndxjp;

 start_ip = bbp->ihd;
 /* enters */
 /* AIV 12/06/06 - if marked with -2 label isn't need becuase of optimizs */
 /* need to mark here because of end fixup - link out at end of routine */
 if (start_ip->idst.disp == -2) linkout_start = TRUE;
 else linkout_start = FALSE;

 if (start_ip->opcod == I_BBLK_LABEL)
  {
   /* DBG remove -- */
   if (start_ip->isrc.amode != AM_NONE) __misc_terr(__FILE__, __LINE__);
   /* -- */

   /* here can just change body of insn */
   start_ip->opcod = I_LABEL;
   /* SJM 08/28/06 - the uncond jump the label is in dst not src amode */
   /* since src amode already AM NONE, put the label string into dst too */
   lbbp = start_ip->idst.apu.bbp;
   bblk_num = lbbp->bblk_seqno;
   /* nothing to free since points a bblk that must not be freed here */

   __init_amode(&(start_ip->idst));
   start_ip->idst.amode = AM_LABEL;
   /* AIV 08/19/09 - memory leak here need to set flag to free string */
   start_ip->idst.is_labnam = TRUE;
   /* AIV 11/03/09 - align enter loops */
   if (lbbp->is_enter_loop)
    {
     sprintf(s1, "%s\nL", ALIGN_JMPE_STR);
     start_ip->idst.apu.labnam = __xi_stralloc(s1);
    }
   else start_ip->idst.apu.labnam = __xi_stralloc("L");
   start_ip->idst.disp = bblk_num;
   
   /* SJM 09/11/06 - know that enter's always follow labels */
   /* AIV 06/27/08 - rare case that all the block's insn are removed due to */
   /* coalesce of register removes all the move insns - from qcol code ??? */
   /* LOOKATME - doing this for now just leave as label - no need for fixup */
   if (start_ip->inxt != NULL)
    {
     start_ip = start_ip->inxt;
    }
  }

 if (start_ip->opcod == I_ENTER_PROC)
  {
   ndx = start_ip->idst.disp;
   sprintf(s2, "ST_ENT_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE - nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "ST_ENT_%d", mdp->m_idnum); 
   /* REPLACE: nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  }
 else if (start_ip->opcod == I_ENTER_MDC)
  {
   /* enter for merged delay control fg (always @same expr) */
   ndx = start_ip->idst.disp;
   sprintf(s2, "MDC_ENT_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE - nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "MDC_ENT_%d", mdp->m_idnum); 
   /* REPLACE: nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  }
 else if (start_ip->opcod == I_ENTER_NB_PROC)
  {
   ndx = start_ip->idst.disp;
   sprintf(s2, "ST_ENT_NB_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE - nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "ST_ENT_NB_%d", mdp->m_idnum); 
   /* REPLACE: nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  }
 else if (start_ip->opcod == I_ENTER_NB_PROC_FREE)
  {
   ndx = start_ip->idst.disp;
   sprintf(s2, "ST_ENT_NB_FREE_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE - nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "ST_ENT_NB_FREE_%d", mdp->m_idnum); 
   /* REPLACE: nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  }
 else if (start_ip->opcod == I_ENTER_THD_RET)
  {
   ndx = start_ip->idst.disp;
   sprintf(s2, "%s_%d", __thdjmp_ret_tab[ndx], ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   strcpy(s1, __thdjmp_ret_tab[ndx]); 
   /* REPLACE: nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  }
 else if (start_ip->opcod == I_ENTER_DECL)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "DCE_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE: nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "DCE_%d", mdp->m_idnum);
   /* this adds the index number */
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  }
 else if (start_ip->opcod == I_ENTER_NPP)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "NPP_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "NPP_%d", mdp->m_idnum); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_MULTFI_SUBR)
  {
   ndx = start_ip->idst.disp;

   /* notice for this only know the mod/net at original insn gen time */
   sprintf(s2, "%s_%d", start_ip->idst.apu.labnam, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s2, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL,
   start_ip->idst.apu.labnam, ndx);

   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_CAP)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "CAP_%d", ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   strcpy(s1, "CAP"); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_ICONN)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "ICONN_%d", ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   strcpy(s1, "ICONN"); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_PORT)
  {
   ndx = start_ip->idst.disp;
   strcpy(s1, "PORT"); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_GATECA)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "GATECA_%d", ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   strcpy(s1, "GATECA"); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_NCHG)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "NCHG_%d", ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   strcpy(s1, "NCHG"); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_GATEDA)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "GATEDA_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "GATEDA_%d", mdp->m_idnum); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_PROCESS_NCHG)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "PROCESS_NCHG_%d", ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   strcpy(s1, "PROCESS_NCHG"); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_MIPD)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "MIPD_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "MIPD_%d", mdp->m_idnum); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_WIRE_EV)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "WIRE_EV_%d", ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   strcpy(s1, "WIRE_EV"); 
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 
 else if (start_ip->opcod == I_ENTER_TRPTH_EV)
  {
   ndx = start_ip->idst.disp;

   sprintf(s2, "TRPTH_EV_%d_%d", mdp->m_idnum, ndx);
   sprintf(s1, "\t%s\n.globl %s", ALIGN_FUNC_STR, s2);
   /* REPLACE:  nores_insn(I_DIRECTIVE, AM_NONE, AM_LABEL, s1, -1); */
   __insert_insn(start_ip, FALSE, I_DIRECTIVE, AM_NONE, AM_LABEL, s1, 0);

   sprintf(s1, "TRPTH_EV_%d", mdp->m_idnum);
   /* REPLACE:  nores_insn(I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx); */ 
   __insert_insn(start_ip, FALSE, I_ENTER_LABEL, AM_NONE, AM_LABEL, s1, ndx);
   __linkout_insn(start_ip, TRUE);
  } 

 /* exits */
 end_ip = bbp->itail;
 if (end_ip->opcod == I_SUSPEND || end_ip->opcod == I_COMPLETE)
  {
   /* ret; */
//AIV? 08/14/06 - FIXME - this should be a leave not decomposed
//SJM? 08/14/06 - for now always pushing and popping callee saved
//                regs ebx, esi and edi
   /* just change opcod since no args */
   end_ip->opcod = I_RETURN;
   goto done;
  }

 /* flow graph jump needs bblk pointer, asm need label index */
 if (end_ip->opcod == I_BBLK_JMP)
  {
   /* uncond jmp easy - just change guts of insn */
   end_ip->opcod = I_JMP;
   /* SJM 08/28/06 - for uncond jump - jmptyp must never be set? */
   /* DBG remove --- */
   if (end_ip->jmptyp != CC_NONE || end_ip->sgn_jmp)
    {
     __misc_terr(__FILE__, __LINE__);
    }
   if (end_ip->isrc.amode != AM_NONE) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* jump insn target bblk goes in src amode */
   bblk_num = end_ip->idst.apu.bbp->bblk_seqno;
   /* nothing to free since points a bblk that must not be freed here */
   __init_amode(&(end_ip->idst));
   end_ip->idst.amode = AM_LABEL;
   /* AIV 08/19/09 - memory leak here need to set flag to free string */
   end_ip->idst.is_labnam = TRUE;
   end_ip->idst.apu.labnam = __xi_stralloc("L");
   end_ip->idst.disp = bblk_num;
   goto done;
  }

 /* fix up the cond jump */
 if (end_ip->opcod == I_REAL_COND_JMP)
  {
   t_seqno = end_ip->isrc.apu.bbp->bblk_seqno;
   f_seqno = end_ip->idst.apu.bbp->bblk_seqno;
   switch (end_ip->jmptyp) {
    case CC_JGE:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JGE;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JGT:
     /* AIV 01/09/07 - condition code was wrong */
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JGT;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JLE:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JGE;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JLT:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JGT;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JE:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_JNE;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_JP;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JNE:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JNE;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JP;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JRZ:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_JP;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JE;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JA:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JA;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JP;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JB:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JB;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JP;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JAE:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JAE;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JP;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
    case CC_JBE:
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JBE;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", t_seqno);
     end_ip->iprev->jmptyp = CC_JP;

     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L", f_seqno);
     end_ip->iprev->jmptyp = CC_NONE;
     break;
   }
   __linkout_insn(end_ip, TRUE);
   goto done;
  }

 if (end_ip->opcod == I_COND_JMP)
  {
   /* idea is to insert the asm insns before the bblk jumps */
   /* in order then delete the bblk jump */
   __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L",
    end_ip->isrc.apu.bbp->bblk_seqno); 
   end_ip->iprev->jmptyp = end_ip->jmptyp;
   end_ip->iprev->sgn_jmp = end_ip->sgn_jmp;

   /* AIV 12/06/06 - if marked with -2 destination is a fall thru */
   if (end_ip->idst.disp != -2)
    {
     __insert_insn(end_ip, FALSE, I_JMP, AM_NONE, AM_LABEL, "L",
      end_ip->idst.apu.bbp->bblk_seqno); 
     end_ip->iprev->jmptyp = CC_NONE;
     end_ip->iprev->sgn_jmp = end_ip->sgn_jmp;
    }

   __linkout_insn(end_ip, TRUE);
   goto done;
  }
 if (end_ip->opcod == I_IND_JMP)
  {
   /* SJM 09/11/06 - for index jumps the first jump insn stays - rest */
   /* of these insns generate the jump table */

   /* expand index jump bblk jump to table and add boiler plate */
   /* some gas directives to set section and alignment */
   new_ip = __insert_insn(end_ip, TRUE, I_DIRECTIVE, AM_NONE,
    AM_LABEL, "\t.section\t.rodata", 0);
   sprintf(s1, "\t.align %d", WRDBYTES);
   new_ip = __insert_insn(new_ip, TRUE, I_DIRECTIVE, AM_NONE, AM_LABEL,
    s1, 0);

   /* jmplab nxt stored in dst amode disp field by convention */
   new_ip = __insert_insn(new_ip, TRUE, I_ENTER_LABEL, AM_NONE, AM_LABEL,
    "C", end_ip->idst.disp);

   /* SJM 08/19/05 - need one tab loc for each inst, was just including */  
   /* the set that was too small and causing core dumps */
   ndxjp = end_ip->extrau.ndxjp;
   /* AIV 05/08/07 - if has duplicates ndx jump starts at start */
   if (ndxjp->has_duplicates) jtabsize = ndxjp->jtabstart;
   else jtabsize = ndxjp->jtabsiz;

   for (i = 0; i < jtabsize; i++)
    {
     sprintf(s1, "\t.%s L_%d", AW_STR, ndxjp->bbtab[i]->bblk_seqno);
     new_ip = __insert_insn(new_ip, TRUE, I_DIRECTIVE, AM_NONE, AM_LABEL,
      s1, 0);
    }
   /* put in the insn at end of pattern first */
   __insert_insn(new_ip, TRUE, I_DIRECTIVE, AM_NONE, AM_LABEL,
    "\t.text\n", 0);
   goto done;
  }
done:
//SJM? ===> what else can end bblks?
 /* AIV 12/06/06 - if marked with -2 label isn't need becuase of optimizs */
 /* AIV 02/22/10 - bug here which removes all insn from bblk was causing */
 /* core dump due to linking out all insn in block - only happening for */
 /* explrm32bit.v with -O */
 /* AIV LOOKATME - this could really be a bug in v_bbopt - block removal */
 if (linkout_start && bbp->ihd->inxt != NULL)
  {
   __linkout_insn(bbp->ihd, TRUE);
  }
}

/*
 * convert all insn that use byte or hword regs from long reg opcode to byte
 * or hword op code
 */
static void convert_insn_bytes_hwords(struct bblk_t *bbp)
{
 struct insn_t *ip, *ip2;
 struct insn_info_t *iip;
 struct amode_t *srcp, *dstp;
 int32 reg;
 
 for (ip = bbp->ihd; ip != NULL; ip = ip2)
  {
   ip2 = ip->inxt;
   /* SJM 04/02/06 - notice not no checking - replace for debugging */
   iip = __to_iinfo_rec(ip->opcod);
   srcp = &(ip->isrc);
   dstp = &(ip->idst);
   /* this is needed to avoid warning messages from assembler */
   if (srcp->amode == AM_IMM)
    {
     /* AIV FIXME - need a new field to put literal values in */
     /* should put stack displacement and literals in same field */
     if (iip->rdwr_siz == SIZ_B || iip->rdwr_siz == SIZ_BL)
      {
       srcp->disp = srcp->disp & 0xff;
      }
     else if (iip->rdwr_siz == SIZ_W)
      {
       srcp->disp = srcp->disp & 0xffff;
      }
#ifndef __CVC32__
     /* AIV 08/03/10 - added ability to do movl on 64-bit machine */
     else if (iip->rdwr_siz == SIZ_LL || iip->rdwr_siz == SIZ_QL)
      {
       srcp->disp = srcp->disp & 0xffffffff;
      }
#endif
    }
   
   /* if insn is a byte insn change reg to corresponding byte rep */
   /* only swap %r1 => r1_byte not (%r1) to (%r1_byte) */
   if (srcp->amode == AM_REG)
    {
     reg = srcp->x86_regno;
     if (reg == -1) __misc_terr(__FILE__, __LINE__);

     /* SJM 04/11/06 - word shifts dest is read and written but in */
     /* conversion to byte/hword code first arg count is byte */
     if (iip->rdwr_siz == SIZ_B || iip->rdwr_siz == SIZ_BL)
      {
       /* DBG remove -- */
       if (reg == AR_SI || reg == AR_DI) __misc_terr(__FILE__, __LINE__);
       /* ---- */

       srcp->x86_regno = reg_bytes[reg];
      }
     else if (iip->rdwr_siz == SIZ_W || iip->rdwr_siz == SIZ_WL)
      {
       /* DBG remove -- */
       if (reg == AR_SI || reg == AR_DI) __misc_terr(__FILE__, __LINE__);
       /* ---- */

       srcp->x86_regno = reg_16bytes[reg];
      }
#ifndef __CVC32__
     /* AIV 08/03/10 - added ability to do movl on 64-bit machine */
     else if (iip->rdwr_siz == SIZ_LL || iip->rdwr_siz == SIZ_QL)
      {
       /* DBG remove -- */
       if (reg == AR_SI || reg == AR_DI) __misc_terr(__FILE__, __LINE__);
       /* ---- */

       srcp->x86_regno = reg_32bytes[reg];
      }
#endif
    }
   if (dstp->amode == AM_REG)
    {
     reg = dstp->x86_regno;

     if (reg == -1) __misc_terr(__FILE__, __LINE__);
     if (iip->rdwr_siz == SIZ_B)
      {
       /* DBG remove -- */
       if (reg == AR_SI || reg == AR_DI) __misc_terr(__FILE__, __LINE__);
       /* ---- */

       dstp->x86_regno = reg_bytes[reg];
      }
     if (iip->rdwr_siz == SIZ_W)
      {
       /* DBG remove -- */
       if (reg == AR_SI || reg == AR_DI) __misc_terr(__FILE__, __LINE__);
       /* ---- */

       dstp->x86_regno = reg_16bytes[reg];
      }
#ifndef __CVC32__
     /* AIV 08/03/10 - added ability to do movl on 64-bit machine */
     else if (iip->rdwr_siz == SIZ_LL)
      {
       /* DBG remove -- */
       if (reg == AR_SI || reg == AR_DI) __misc_terr(__FILE__, __LINE__);
       /* ---- */

       dstp->x86_regno = reg_32bytes[reg];
      }
#endif
    }
  }
 __cur_bbp = NULL;
}

/*
 * convert inter-block jumps - now with continue/break - may be in 
 * middle of block - not on the tail end 
 * tail end - jumps are converted in lower_bblk_enter_exits
 *
 * move a middle jump insn to the tail and remove all other insns
 * AIV LOOKATME - maybe this should go in v_bbopt.c
 */
static void convert_inter_block_jumps(struct bblk_t *bbp)
{
 struct insn_t *ip, *end_ip, *ip2, *ip3;
 
 end_ip = bbp->itail;
 __cur_bbp = bbp;
 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
  {
   /* if it is a jump and not a tail - make it the tail and remove */
   /* the rest ot the insns */
   if (ip->opcod == I_BBLK_JMP && ip != end_ip)
    {
     bbp->itail = ip;
     for (ip2 = ip->inxt; ip2 != end_ip; ip2 = ip3)
      {
       ip3 = ip2->inxt;  
       __linkout_insn(ip2, TRUE);
      }
     return;
    }
  }
}

//AIV LOOKATME - AIV REMOVEME - OLD CODE????
static void convert_inter_block_jumps_works(struct bblk_t *bbp)
{
 int32 bblk_num;
 struct insn_t *ip;
 
 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
  {
   if (ip->opcod == I_BBLK_JMP)
    {
     /* uncond jmp easy - just change guts of insn */
     ip->opcod = I_JMP;
     /* DBG remove --- */
     if (ip->jmptyp != CC_NONE || ip->sgn_jmp)
      {
       __misc_terr(__FILE__, __LINE__);
      }
     if (ip->isrc.amode != AM_NONE) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* jump insn target bblk goes in src amode */
     bblk_num = ip->idst.apu.bbp->bblk_seqno;
     /* nothing to free since points a bblk that must not be freed here */
     __init_amode(&(ip->idst));
     ip->idst.amode = AM_LABEL;
     ip->idst.is_labnam = TRUE;
     ip->idst.apu.labnam = __xi_stralloc("L");
     ip->idst.disp = bblk_num;
    }
  }
}

/*
 * merge insns in each bblk for each flow graph into one
 * linear flow graph list
 */
static void merge_insns_to_1fg_list(struct flowg_t *fgp)
{
 int32 blki;
 struct bblk_t *bbp;

 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];
   /* SJM 12/02/06 - bblk maybe removed but RPOs numbers not re assigned */
   if (bbp == NULL) continue;
   __cur_bbp = bbp;

   if (fgp->fg_ihd == NULL) fgp->fg_ihd = bbp->ihd;
   else
    {
     fgp->fg_itail->inxt = bbp->ihd;
     bbp->ihd->iprev = fgp->fg_itail;
    }
   fgp->fg_itail = bbp->itail;
  }
 __cur_bbp = NULL; 
}

/*
 * ROUTINES TO EMIT INSNS TO .S FILE FOR EACHY MODULE IN GAS ASSEMBLER FORMAT
 * ALSO BUILDS THE PER MODULE COMM DEFINES AND STORAGE AREAS
 * IF SHOW ASM FLAG OFF, ALL FILES AND PIPED AND ASSEMBLED IMMEDIATELY 
 */

/*
 * emit gas assembler input format X86 machine insns for one module
 *
 * this handles file and stream opening and closing
 *
 * SJM 04/12/08 - now only constants are in the per mod .s - all storage
 * in mod wide comm file
 */
static void emit_1mod_asm_insns(struct mod_t *mdp)
{
 int32 fgi;
 FILE *fp;
 char fnam[RECLEN];

 __bld_asm_fnam_stem(__xs, mdp);
 sprintf(fnam, "%s.s", __xs);
 if ((fp = __my_fopen(fnam, "w")) == NULL)
  {
   __pv_err(2904, "unable to write into .s file %s", fnam);
   return;
  } 

 if (__show_asm)
  {
   __my_fprintf(fp, "# MODULE %s (ndx=%d) at %s\n", mdp->msym->synam, 
    mdp->m_idnum, __bld_lineloc(__xs, mdp->msym->syfnam_ind,
    mdp->msym->sylin_cnt));
  }

//SJM? 08/14/06 - no reason to keep building the per mod flowg index
 __bld_mod_flowg_ndx(mdp);

// SJM 07-20-13 - IDP MAP NO LONGER AVAILABLE AT COMPILE TIME ????
 /* if opt debug flag dump the set symbols for debbuging from __idp area */
// if (__opt_debug_flg)
//  {
//   /* SJM 04/12/08 - notice need the idp dat area equivs in the mod .s file */
//   emit_dbg_idp_info_symbols(fp, mdp);
//  }
 
 /* reset insn count to 0 */
 __num_print_asm_insn = 0;
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   /* AIV 07/22/09 - if going to produce a large assembly file partition */ 
   /* into multiple files - this creates better performance and uses */
   /* less memory for the assembler - problem for large gate designs */
   /* just inc asm_partition count and close old file and and open new */
   if (__num_print_asm_insn > PARTITION_MAX_INSN_COUNT)
    {
     emit_1mod_constants(fp, mdp);
     __my_fclose(fp);
     __bld_asm_fnam_stem(__xs, mdp);
     mdp->asm_partition_cnt++;
     sprintf(fnam, "%s_%d.s", __xs, mdp->asm_partition_cnt);
     if ((fp = __my_fopen(fnam, "w")) == NULL)
      {
       __pv_err(2904, "unable to write into .s file %s", fnam);
       return;
      } 
     /* reset insn count to 0 */
     __num_print_asm_insn = 0;
    }
   emit_oneflowg_asm(fp, __flowgtab[fgi], mdp, FALSE);
  }

 emit_1mod_data_section(fp, mdp);
 /* SJM 04/08/08 - now only constants go in mod .s end */
 emit_1mod_constants(fp, mdp);
 __my_fclose(fp);
}

/*
 * same as above except pipe directly into gnu assembler 
 */
static void pipe_1mod_asm_insns(struct mod_t *mdp)
{
 int32 fgi;
 FILE *pp;
 char as_cmd[RECLEN];

 __bld_asm_fnam_stem(__xs, mdp);
 /* AIV LOOKATME - different flags, more ifdefs, ect */
 /* FIXME - must make tmp available for release */
#ifdef __CVC32__
 sprintf(as_cmd, "as --32 -o %s", __xs);
#else
 sprintf(as_cmd, "as -o %s", __xs);
#endif
 strcpy(__asm_file_name, __xs);

 if ((pp = do_popen(as_cmd, "w")) == NULL)
  {
   __pv_err(2904, "unable to locate GNU assembler");
   return;
  } 

//SJM? 08/14/06 - no reason to keep building the per mod flowg index
 /* reset insn count to 0 */
 __num_print_asm_insn = 0;

 __bld_mod_flowg_ndx(mdp);
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   /* emit the ascii asm for each flow graph */
   /* AIV 07/22/09 - if going to produce a large assembly file partition */ 
   /* into multiple files - this creates better performance and uses */
   /* less memory for the assembler - problem for large gate designs */
   /* just inc asm_partition count and close old pipe and and open new */
   if (__num_print_asm_insn > PARTITION_MAX_INSN_COUNT)
    {
     emit_1mod_constants(pp, mdp);
     pclose(pp);
     mdp->asm_partition_cnt++;
#ifdef __CVC32__
     sprintf(as_cmd, "as --32 -o %s_%d.o", __xs, mdp->asm_partition_cnt);
#else
     sprintf(as_cmd, "as -o %s_%d.o", __xs, mdp->asm_partition_cnt);
#endif
     sprintf(__asm_file_name, "%s_%d.o", __xs, mdp->asm_partition_cnt);
     if ((pp = do_popen(as_cmd, "w")) == NULL)
      {
       __pv_err(2904, "unable to locate GNU assembler");
      return;
     } 
     /* reset insn count to 0 */
     __num_print_asm_insn = 0;
    }
   emit_oneflowg_asm(pp, __flowgtab[fgi], mdp, FALSE);
  }

 emit_1mod_data_section(pp, mdp);
 /* SJM 04/08/08 - now only constants go in mod .s end */
 emit_1mod_constants(pp, mdp);
 do_pclose(pp);
}

/*
 * emit a modules fixed data items at the end of M_?.s file
 *
 * AIV 08/05/09 - it is best to place these by the code which uses them
 */
static void emit_1mod_data_section(FILE *fp, struct mod_t *mdp)
{
 /* first build tev (ctev compile time describe) list (also fills some) */
 /* needed since by here may know that some ctev's may never be used */
 fill_1mod_ctevs(mdp);

 if (__show_asm)
  {
   __my_fprintf(fp, "# PMD DATA FOR %s (ndx=%d) at %s\n", mdp->msym->synam, 
    mdp->m_idnum, __bld_lineloc(__xs, mdp->msym->syfnam_ind,
    mdp->msym->sylin_cnt));
  }

 /* emit entire designs per mod per inst idp area .bss (unitialized) area */ 
 emit_dsgn_idparea(fp, mdp);

 /* emit all of a mod's fixed time events - for is1v const dels also dels */
 emit_1mod_tev_glbs(fp, mdp);

 /* emit all of a mod's fixed nchglst elements */
 emit_1mod_nchg_glbs(fp, mdp);

 /* AIV 03/12/12 - emit the mod's fixed structs */
 emit_1mod_commlabs(fp, mdp, FALSE);
   
 /* SJM 07/11/08 - new direct access .globl labels to n.l. areas */ 
 emit_1mod_tchk_tchg_adr_labs(fp, mdp);
 emit_1mod_pth_del_adr_labs(fp, mdp);
}


/*
 * build the per module .s file names
 *
 * since most same adding file name prefix
 * SJM 02-07-13 - if emit var names or showing asm, various gen file names
 */
extern char *__bld_asm_fnam_stem(char *fnam, struct mod_t *mdp)
{
 /* AIV 09/02/09 - use new temp area random generated file names */
 /* will be nil */
 if (!__opt_emit_var_names)
  {
   if (__show_asm)
    {
     sprintf(fnam, "M_%d", mdp->m_idnum);
     return(fnam);
    }
   
   /* DBG remove -- */
   if (__mod_file_names[mdp->m_idnum] == NULL) 
     __misc_terr(__FILE__, __LINE__);
   /* ---- */
   strcpy(fnam, __mod_file_names[mdp->m_idnum]); 
   return(fnam);
  }
 if (mdp->msym->synam[0] == '\\') sprintf(fnam, "M_%d", mdp->m_idnum);
 else sprintf(fnam, "M_%s", mdp->msym->synam);
 return(fnam);
}

/*
 * dump debugging strings for things in the __idp area
 *
 * SJM 08/04/08 - need to dump once at the top of each module since equiv
 * names do not include module name
 *
 * SJM 07-20-13 - L0OKATME? IDP map no longer available at compile time
 * BEWARE - THIS PROC CAN'T BE CALLED
 */
static void emit_dbg_idp_info_symbols(FILE *fp, struct mod_t *mdp)
{
 size_t i;
 char s[RECLEN];

 /* AIV 01/11/08 - the offset + 1 is always dummy net change word - so skip */
 /* may never be set if never used but is always alloc */
 for (i = IDP_HD_WOFS + 1; i < mdp->mod_idata_siz; i++) 
  {
   get_idp_map_str(s, mdp, i);
//SJM PUTMEBACK     emit_one_insn(fp, ".set\t%s, %d\n", s, i*WRDBYTES);
#ifdef __CVC32__
   emit_one_insn(fp, ".equiv\t%s, %u\n", s, i*WRDBYTES);
#else
   emit_one_insn(fp, ".equiv\t%s, %ld\n", s, i*WRDBYTES);
#endif
  }
 for (i = 0; i < IDP_HD_WOFS; i++)
  {
   get_fixed_idp_map_str(s, mdp, i);
#ifdef __CVC32__
   emit_one_insn(fp, ".equiv\t%s, %u\n", s, i*WRDBYTES);
#else
   emit_one_insn(fp, ".equiv\t%s, %ld\n", s, i*WRDBYTES);
#endif
  }
}
   
/*
 * get an idp description string from the __idp offset item map 
 *
 * SJM 12/04/07 - notice idp area offsets (map) and size is words but insns
 * need bytes
 * SJM 08/04/08 - every equiv name needs the idp offset index because
 * net name in task/func and module may be same
 */
static char *get_idp_map_str(char *s, struct mod_t *mdp, size_t ndx)
{
 struct net_t *np;
 struct idp_map_t *idp_mapp;
 char s1[RECLEN];

 /* DBG remove -- */
 if (mdp == NULL) __misc_terr(__FILE__, __LINE__);
 if (ndx >= mdp->mod_idata_siz) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 
 if (ndx < IDP_HD_WOFS)
  {
   get_fixed_idp_map_str(s, mdp, ndx);
   return(s);
  }

 idp_mapp = mdp->mod_idp_map[ndx];

 switch (idp_mapp->idpmaptyp) {
  case IDPMAP_NVAOFS:
   /* SJM 12/06/07 - for now only nva ofs (net's val in idp) uses obj name */
   np = idp_mapp->idpobju.enp;
   sprintf(s, "NETBP_%s_%s", mdp->msym->synam, np->nsym->synam); 
   break;
  case IDPMAP_NCHGACTION:
   np = idp_mapp->idpobju.enp;
   sprintf(s, "COMLAB_NCHGACTION_%s_%s", mdp->msym->synam,
    np->nsym->synam);
   break;
  case IDPMAP_NET_TEVP: case IDPMAP_ST_TEVP: case IDPMAP_CA_TEVP:
  case IDPMAP_GP_TEVP:
   sprintf(s, "COMLAB_TEVP_%s", mdp->msym->synam);
   break;
  case IDPMAP_REP_BP:
   sprintf(s, "REPBP_%s", mdp->msym->synam);
   break;
  case IDPMAP_DCESCH_TEVS:
   sprintf(s, "DCE_SCH_TEVS_%s", mdp->msym->synam);
   break;
  case IDPMAP_DELREP_BP:
   sprintf(s, "DELREPBP_%s", mdp->msym->synam);
   break;
  case IDPMAP_PD_RHSBP:
   sprintf(s, "COMLAB_PD_RHSBP_%s", mdp->msym->synam);
   break;
  case IDPMAP_NB_BP:
   sprintf(s, "CONTA_NB_BP_%s", mdp->msym->synam);
   break;
  case IDPMAP_CA_DRVBP:
   sprintf(s, "CONTA_DRVBP_%s", mdp->msym->synam);
   break;
  case IDPMAP_CA_SCHBP:
   sprintf(s, "CONTA_SCHBP_%s", mdp->msym->synam);
   break;
  case IDPMAP_GATE_OUTBP:
   sprintf(s, "COMLAB_GATE_OUTBP_%s", mdp->msym->synam);
   break;
  case IDPMAP_GATEBP:
   sprintf(s, "COMLAB_GATEBP_%s", mdp->msym->synam);
   break;
  case IDPMAP_DCEPREV:
   sprintf(s, "DCE_PREV_%s", mdp->msym->synam);
   break;
  case IDPMAP_DCEEXPR_BP:
   sprintf(s, "DCEEXPR_BP_%s", mdp->msym->synam);
   break;
  case IDPMAP_PNCHG:
   sprintf(s, "PNCHG_%s", mdp->msym->synam);
   break;
  case IDPMAP_ISNUM:
   sprintf(s, "ISNUM_%s", mdp->msym->synam);
   break;
  case IDPMAP_TCHK_CHG:
   sprintf(s, "TCHK_CHG_%s", mdp->msym->synam);
   break;
  case IDPMAP_DPFD:
   sprintf(s, "DPFD_%s", mdp->msym->synam);
   break;
  default: strcpy(s, ""); __case_terr(__FILE__, __LINE__);
 }
#ifdef __CVC32__
 sprintf(s1, "_%d", ndx);
#else
 sprintf(s1, "_%ld", ndx);
#endif
 strcat(s, s1);
 return(s);
}

/*
 * get idp low area strings 
 */
static char *get_fixed_idp_map_str(char *s, struct mod_t *mdp, int32 ndx)
{
 switch (ndx) {
  case MD_INUM:
   sprintf(s, "inum_%s_%d", mdp->msym->synam, ndx);
   break;
  case MD_MDP:
   sprintf(s, "mdp_%s_%d", mdp->msym->synam, ndx);
   break;
  case MD_ITP:
   sprintf(s, "itp_%s_%d", mdp->msym->synam, ndx);
   break;
  case MD_UPIDP:
   sprintf(s, "upitp_%s_%d", mdp->msym->synam, ndx);
   break;
  case MD_DOWNITPS:
   sprintf(s, "downitps_%s_%d", mdp->msym->synam, ndx);
   break;
  default: strcpy(s, "<ERROR>"); __case_terr(__FILE__, __LINE__);
 } 
 return(s);
}

/*
 * ROUTINES TO WRITE INSNS TO ASCII ASM .S FILE (OR TO PIPE) 
 */

/*
 * emit to file gas fmt asm insns for one flow graph
 *
 * depth first expansion of flow graph into a table of bblks build by caller
 * then in order emits each insn in each bblk 
 *
 * SJM 09/23/04 - LOOKATME - seemingly this does not need bblk struct ptr
 */
static void emit_oneflowg_asm(FILE *fp, struct flowg_t *fgp, struct mod_t *mdp,
 int32 dbg_flg)
{
 struct insn_t *ip;
 char iline[RECLEN];
  
 /* SJM 12/26/06 - for ever flowg, must mark all used in flowg tn's */ 
 /* unused in asm - for constants that are almost always converted to */
 /* literals so do not need to go in comm area */
 turn_off_used_in_asm_flag(fgp);

 /* AIV 07/09/09 - if marked used fixed code */
 if (fgp->optim_scalar_port)
  {
   emit_optim_scalar_port_npps(fp, fgp, mdp, dbg_flg);
   return;
  }

 for (ip = fgp->fg_ihd; ip != NULL; ip = ip->inxt)
  {
   /* SJM 12/27/06 - phi FUD insns invisible except if debug flg on */ 
   if (ip->opcod == I_DEFLST && !dbg_flg) continue;

   __insn_print_count++;

   if (__asm_emit_loc == 3)
    {
     emit_one_insn(fp, "%s #%d\n", __asm_insn_tostr(iline, ip, dbg_flg, fgp), 
      ip->ndx);
    }
   else emit_one_insn(fp, "%s\n", __asm_insn_tostr(iline, ip, dbg_flg, fgp));
  }
}

/*
 * print one insn with a counter to count number of printed assembly
 * instructions - if reach max partition assembly into multiple files
 */
static void emit_one_insn(FILE *fp, char *s, ...)
{
 va_list va;

 /* just inc and print */
 __num_print_asm_insn++;
 va_start(va, s);
 vfprintf(fp, s, va);
 va_end(va);
}

   
/*
 * dump code to do scalar-scalar NP_ICONN
 */
static void emit_optim_scalar_port_npps(FILE *fp, struct flowg_t *fgp, 
 struct mod_t *upmdp, int32 dbg_flg)
{
 int32 count, jmp_nchg_nxt; 
 size_t offset;
 word32 mask;
 struct expr_t *down_lhsx;
 struct itree_t *itp, *up_itp;
 struct inst_t *ip;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 struct net_pin_t *npp;
 struct net_t *down_np;
 struct net_t *np;
 struct insn_t *iip;
 struct nchglst_t *nchgp;
 char iline[RECLEN];

 iip = fgp->fg_ihd;
 /* first 2 lines are alloc as normal */
 /* AIV 02/09/10 BEWARE - this assume fixed template number of lines from */
 /* lower_bblk_enter_exits routine */
 for (count = 0; count < 2; iip = iip->inxt, count++)
  {
   __insn_print_count++;

   if (__asm_emit_loc == 3)
    {
     emit_one_insn(fp, "%s #%d\n", __asm_insn_tostr(iline, iip, dbg_flg, fgp), 
      iip->ndx);
    }
   else emit_one_insn(fp, "%s\n", __asm_insn_tostr(iline, iip, dbg_flg, fgp));
  }

 /* flowgraph can be FLOWG_PROCESS_NCHG or FLOWG_NPP - see v_bbgen2 for */
 /* np_iconn code produced here */
 np = fgp->optim_port_np;
 if (fgp->flowgtyp == FLOWG_PROCESS_NCHG)
  {
   /* zero the nchgp->trigged flag movl $0, (%eax) */
   emit_one_insn(fp, "\t%s\t$0, (%s)\n", MOVA_STR, __regs[AR_AX]);
   nchgp = &__nchg_dummy_hd;
   /* AIV LOOKATME NO MIPD for NOW 
   if (np->n_mipd)
    {
     offset = (byte *) &(nchgp->delayed_mipd) - (byte *) nchgp;
     emit_one_insn(fp, "\tmovl\t%d(%%eax), %%ecx\n", offset);
     emit_one_insn(fp, "\tmovl\t%%ecx, __nchged_delayed_mipd\n");
    }
    */
   /* may need to load idp reg  - nchg is know to be in %eax/%rax */
   if (upmdp->flatinum != 1 || np->dmpv_in_src || np->dmpp_in_src) 
    {
     /* load idp into %esi */
     offset = (byte *) &(nchgp->nchg_idp) - (byte *) nchgp;
#ifdef __CVC32__
     emit_one_insn(fp, "\t%s\t%d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
      __regs[IDP_REG]);
#else
     emit_one_insn(fp, "\t%s\t%lu(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
      __regs[IDP_REG]);
#endif
     /*  __idp[np->nchgaction_ofs] &= (~NCHG_ALL_CHGED) */
     if (np->dmpv_in_src || np->dmpp_in_src) 
      {
       mask = ~NCHG_ALL_CHGED;
       /* DBG remove -- */
       if (np->nchgaction_ofs == 0) __misc_terr(__FILE__, __LINE__);
       /* ------ */
       offset = np->nchgaction_ofs*WRDBYTES;
#ifdef __CVC32__
       emit_one_insn(fp, "\t%s\t$0x%lx, %d(%s)\n", ANDA_STR, mask, offset,
         __regs[IDP_REG]);
#else
       emit_one_insn(fp, "\t%s\t$0x%lx, %lu(%s)\n", ANDA_STR, mask, offset,
         __regs[IDP_REG]);
#endif
      }
    }
   /* load the next event into %eax */
   offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
#ifdef __CVC32__
   emit_one_insn(fp, "\t%s\t%d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
    __regs[AR_AX]);
#else
   emit_one_insn(fp, "\t%s\t%lu(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
    __regs[AR_AX]);
#endif
  }
 else
  {
   /* callee save by pushing %ebx */
#ifdef __CVC32__
  /* AIV 12/08/10 - 32-bit version must create some space on stack for 32-bit */
  if (__toggle_coverage)
   {
    emit_one_insn(fp, "\t%s\t$%d, %s\n", SUBA_STR, 2*WRDBYTES, __regs[AR_SP]);
    emit_one_insn(fp, "\t%s\t%s, %d(%s)\n", MOVA_STR, __regs[AR_BX], WRDBYTES, 
       __regs[AR_SP]);
   }
  else emit_one_insn(fp, "\t%s\t%s\n", PUSHA_STR, __regs[AR_BX]);
#else
   emit_one_insn(fp, "\t%s\t%s\n", PUSHA_STR, __regs[AR_BX]);
#endif
  }

 /* do the assign for every iconn */
 jmp_nchg_nxt = FALSE;
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   jmp_nchg_nxt = FALSE;
   if (npp->npproctyp != NP_PROC_INMOD) __misc_terr(__FILE__, __LINE__);
   
   up_itp = upmdp->moditps[0];

   itp = &(up_itp->in_its[npp->elnpp.eii]);
   ip = itp->itip; 
   downmdp = ip->imsym->el.emdp; 
   mpp = &(downmdp->mpins[npp->obnum]); 
   if (npp->npntyp == NP_PB_ICONN)
    {
     mpp = &(mpp->pbmpps[npp->pbi]);
    }

   down_lhsx = mpp->mpref;
   down_np = down_lhsx->lu.sy->el.enp;
   /* if needs record of down net change */
   if (__needs_netchg_record(down_np)) 
    {
     jmp_nchg_nxt = (npp->npnxt == NULL) && 
        (fgp->flowgtyp == FLOWG_PROCESS_NCHG);
     /* handle the one instance case */
     /* AIV 12/08/10 - these now need to handle toggle nets for changes as well */
     if (upmdp->flatinum == 1)
      {
       /* need the dmpvars code */
       if (down_np->dmpv_in_src || down_np->dmpp_in_src || down_np->n_has_toggle) 
        {
         emit_one_scalar_port_optim_nchg_1inst_dmpv(fp, downmdp, upmdp, 
          down_np, np, itp, jmp_nchg_nxt);
        }
       else
        {
         emit_one_scalar_port_optim_nchg_1inst(fp, downmdp, upmdp, down_np, np, 
          itp, jmp_nchg_nxt);
        }
      }
     else
      {
       /* up with more than one instance */
       if (down_np->dmpv_in_src || down_np->dmpp_in_src || down_np->n_has_toggle) 
        {
         emit_one_scalar_port_optim_nchg_dmpv(fp, downmdp, down_np, np, 
          npp->elnpp.eii, jmp_nchg_nxt);
        }
       else
        {
         emit_one_scalar_port_optim_nchg(fp, down_np, np, npp->elnpp.eii, jmp_nchg_nxt);
        }
      }
    }
   else 
    {
     /* same as above except no net change recording is done */
     if (upmdp->flatinum == 1)
      {
       if (down_np->dmpv_in_src || down_np->dmpp_in_src || down_np->n_has_toggle) 
        { 
         emit_one_scalar_port_optim_1inst_dmpv(fp, downmdp, upmdp, down_np, np,
          itp);
        }
       else
        { 
         emit_one_scalar_port_optim_1inst(fp, downmdp, upmdp, down_np, np, itp);
        }
      }
     else
      {
       if (down_np->dmpv_in_src || down_np->dmpp_in_src || down_np->n_has_toggle) 
        {
         emit_one_scalar_port_optim_dmpv(fp, downmdp, down_np, np, 
          npp->elnpp.eii);
        }
       else
        {
         emit_one_scalar_port_optim(fp, down_np, np, npp->elnpp.eii);
        }
      }
    }
  }
 
 if (fgp->flowgtyp == FLOWG_PROCESS_NCHG)
  {
   if (!jmp_nchg_nxt)
    {
     nchgp = &__nchg_dummy_hd;
     offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
#ifdef __CVC32__
     emit_one_insn(fp, "\t%s\t%d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
       __regs[AR_BX]);
#else
     emit_one_insn(fp, "\t%s\t%lu(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
       __regs[AR_BX]);
#endif
     emit_one_insn(fp, "\tjmp\t*%s\n", __regs[AR_BX]);
    }
  }
 else
  {
#ifdef __CVC32__
   if (__toggle_coverage)
    {
     emit_one_insn(fp, "\t%s\t%d(%s), %s\n", MOVA_STR, WRDBYTES, __regs[AR_SP],
       __regs[AR_BX]);
     emit_one_insn(fp, "\t%s\t$%d, %s\n", ADDA_STR, 2*WRDBYTES, __regs[AR_SP]);
    }
   else emit_one_insn(fp, "\t%s\t%s\n", POPA_STR, __regs[AR_BX]);
#else
   emit_one_insn(fp, "\t%s\t%s\n", POPA_STR, __regs[AR_BX]);
#endif
   emit_one_insn(fp, "\tret\n");
  }
}
   

#ifdef __CVC32__
/*
 * do one instance with net change recording 
 */
static void emit_one_scalar_port_optim_nchg_1inst(FILE *fp, 
 struct mod_t *downmdp, struct mod_t *upmdp, struct net_t *downnp, 
 struct net_t *upnp, struct itree_t *downitp, int32 jmp_nchg_nxt)
{
 struct net_chg_t *ncp;
 size_t offset, inst_ofs;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 inst_ofs = (downitp->itinum*downmdp->mod_idata_siz*WRDBYTES); 
 /* DBG remove -- */
 if (inst_ofs > (downmdp->flatinum*downmdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ------ */

 ncp = __find_nchg_range(downnp, -1, -1);

 /* AIV 07/21/09 - this code is assuming this is always true */
 /* dependent upon order of offset alloc in prep code */
 /* DBG remove -- */
 if (ncp->nchg_idp_ofs < downnp->nva_ofs) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 fprintf(fp, "\tmovl\t__idpdat_%d + %d, %%ebx\n", upmdp->m_idnum, 
  WRDBYTES*upnp->nva_ofs);
 offset = inst_ofs + WRDBYTES*downnp->nva_ofs;
 fprintf(fp, "\tmovl\t$__idpdat_%d + %d, %%ecx\n", downmdp->m_idnum, offset);
 offset = (inst_ofs + (WRDBYTES*ncp->nchg_idp_ofs)) - offset;
 fprintf(fp, "\tmovl\t%d(%%ecx), %%edx\n", offset);

 if (jmp_nchg_nxt)
  {
   if (downnp->n_mipd) fprintf(fp, "\tjmp\tICONN_S_S_NCHG_NXT_MIPD\n");
   else fprintf(fp, "\tjmp\tICONN_S_S_NCHG_NXT\n");
  }
 else
  {
   if (downnp->n_mipd) fprintf(fp, "\tcall\tICONN_S_S_NCHG_MIPD\n");
   else fprintf(fp, "\tcall\tICONN_S_S_NCHG\n");
  }
}

/*
 * do one instance with net change recording and dumpvars
 */
static void emit_one_scalar_port_optim_nchg_1inst_dmpv(FILE *fp, 
 struct mod_t *downmdp, struct mod_t *upmdp, struct net_t *downnp, 
 struct net_t *upnp, struct itree_t *downitp, int32 jmp_nchg_nxt)
{
 struct net_chg_t *ncp;
 size_t offset;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 offset = (downitp->itinum*downmdp->mod_idata_siz*WRDBYTES); 
 /* DBG remove -- */
 if (offset > (downmdp->flatinum*downmdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* save next nchg back into %ebx */
 emit_one_insn(fp, "\tmovl\t%%eax, %%ebx\n");

 emit_one_insn(fp, "\tmovl\t__idpdat_%d + %d, %%eax\n", upmdp->m_idnum, 
  WRDBYTES*upnp->nva_ofs);
 if (offset == 0)
  {
   emit_one_insn(fp, "\tmovl\t$__idpdat_%d, %%ecx\n", downmdp->m_idnum);
  }
 else
  {
   emit_one_insn(fp, "\tmovl\t$__idpdat_%d + %d, %%ecx\n", downmdp->m_idnum, offset);
  }
 ncp = __find_nchg_range(downnp, -1, -1);
 emit_one_insn(fp, "\tmovl\t%d(%%ecx), %%edx\n", WRDBYTES*ncp->nchg_idp_ofs);
 
 emit_dump_scalar_port_template(fp, downmdp, downnp, jmp_nchg_nxt);
}
 
/*
 * dump the template for the scalar dumpvars handling
 */
static void emit_dump_scalar_port_template(FILE *fp, struct mod_t *downmdp, 
 struct net_t *downnp, int32 jmp_nchg_nxt)
{
 int32 mask, ndx;
 struct nchglst_t *nchgp;
 size_t offset;
 char retlab[RECLEN], chklab[RECLEN], np_str[RECLEN], s1[RECLEN];

 __bblk_seq_no++;
 sprintf(retlab, "L_%d", __bblk_seq_no);
 __bblk_seq_no++;
 sprintf(chklab, "L_%d", __bblk_seq_no);
 
 __bldchk_var_comm_ref(s1, downnp, downmdp, NULL);
 ndx = downnp - downmdp->mnets;
 sprintf(np_str, "%s_np_%d", s1, ndx);
 nchgp = &__nchg_dummy_hd;
 offset =  WRDBYTES*downnp->nva_ofs;
 emit_one_insn(fp, "\tcmpl	%d(%%ecx), %%eax\n", offset);
 emit_one_insn(fp, "\tje	%s\n", retlab);
 emit_one_insn(fp, "\tmovl	%%eax, %d(%%ecx)\n", offset);
 emit_one_insn(fp, "\tmovl	(%%edx), %%eax\n");
 emit_one_insn(fp, "\ttestl	%%eax, %%eax\n");
 emit_one_insn(fp, "\tjne	%s\n", chklab);

 emit_one_insn(fp, "\tmovl	__nchg_futend, %%eax\n");

 if (downnp->n_mipd)
  {
   offset = (byte *) &(nchgp->delayed_mipd) - (byte *) nchgp;
   emit_one_insn(fp, "\tmovl	$0, %d(%%edx)\n", offset);
  }

 emit_one_insn(fp, "\tmovl	%%eax, (%%edx)\n");
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 emit_one_insn(fp, "\tmovl	%%edx, %d(%%eax)\n", offset);
 emit_one_insn(fp, "\tmovl	%%edx, __nchg_futend\n");
 emit_one_insn(fp, "%s:\n", chklab);

 /* DBG remove -- */
 if (downnp->nchgaction_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 downnp->is_loaded = TRUE;
 offset = (downnp->nchgaction_ofs*WRDBYTES);

 /* handle the toggle change */
 if (downnp->n_has_toggle)
  {
   emit_one_insn(fp, "\tmovl	%%ecx, __idp\n");
   emit_one_insn(fp, "\tmovl	%s, %%eax\n", np_str);
   emit_one_insn(fp, "\tmovl	%%eax, (%%esp)\n");
   emit_one_insn(fp, "\tcall	__add_togglelst_el\n");
   emit_one_insn(fp, "\tmovl	__idp, %%ecx\n");
  }
 if (downnp->dmpv_in_src || downnp->dmpp_in_src)
  {
   /* AIV 04/22/11 - mask was wrong for dumpports */
   if (downnp->dmpv_in_src) mask = (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED);
   else mask = (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED);
   emit_one_insn(fp, "\tmovl	%d(%%ecx), %%eax\n", offset);
   emit_one_insn(fp, "\tandl	$%d, %%eax\n", mask);
   emit_one_insn(fp, "\tcmpl	$%d, %%eax\n", mask);
   emit_one_insn(fp, "\tjne	%s\n", retlab);

   emit_one_insn(fp, "\tmovl	%%ecx, __idp\n");
   emit_one_insn(fp, "\tmovl	%s, %%eax\n", np_str);
   emit_one_insn(fp, "\tmovl	%%eax, (%%esp)\n");
   if (downnp->dmpv_in_src) emit_one_insn(fp, "\tcall	__asl_add_dmpv_chglst_el\n");
   if (downnp->dmpp_in_src) emit_one_insn(fp, "\tcall	__asl_add_dmpp_chglst_el\n");
  }

 emit_one_insn(fp, "%s:\n", retlab);
 /* put next nchg back into %eax */
 emit_one_insn(fp, "\tmovl\t%%ebx, %%eax\n");
 if (jmp_nchg_nxt)
  {
   nchgp = &__nchg_dummy_hd;
   offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
   emit_one_insn(fp, "\tmovl\t%d(%%eax), %%ebx\n", offset);
   emit_one_insn(fp, "\tjmp\t*%%ebx\n");
  }
}

/*
 * do one scalar port of more than one instance with net change record
 */
static void emit_one_scalar_port_optim_nchg(FILE *fp, 
 struct net_t *downnp, struct net_t *upnp, int32 inum, int32 jmp_nchg_nxt)
{
 struct net_chg_t *ncp;
 size_t offset;

 emit_one_insn(fp, "\tmovl\t%d(%%esi), %%ebx\n", WRDBYTES*upnp->nva_ofs);
 /* get the down instance */
 offset = MD_DOWNITPS*WRDBYTES;
 emit_one_insn(fp, "\tmovl\t%d(%%esi), %%ecx\n", offset);
 offset = WRDBYTES + inum*sizeof(struct itree_t);
 emit_one_insn(fp, "\tmovl\t%d(%%ecx), %%ecx\n", offset);

 ncp = __find_nchg_range(downnp, -1, -1);
 emit_one_insn(fp, "\tmovl\t%d(%%ecx), %%edx\n", WRDBYTES*ncp->nchg_idp_ofs);
 emit_one_insn(fp, "\taddl\t$%d, %%ecx\n", WRDBYTES*downnp->nva_ofs);
 if (jmp_nchg_nxt)
  {
   if (downnp->n_mipd) emit_one_insn(fp, "\tjmp\tICONN_S_S_NCHG_NXT_MIPD\n");
   else emit_one_insn(fp, "\tjmp\tICONN_S_S_NCHG_NXT\n");
  }
 else
  {
   if (downnp->n_mipd) emit_one_insn(fp, "\tcall\tICONN_S_S_NCHG_MIPD\n");
   else emit_one_insn(fp, "\tcall\tICONN_S_S_NCHG\n");
  }
}

/*
 * do one scalar port of more than one instance with net change record
 * and dumpvars
 */
static void emit_one_scalar_port_optim_nchg_dmpv(FILE *fp, 
 struct mod_t *downmdp, struct net_t *downnp, struct net_t *upnp, 
 int32 inum, int32 jmp_nchg_nxt)
{
 struct net_chg_t *ncp;
 size_t offset;

 /* need to save next into ebx */
 emit_one_insn(fp, "\tmovl\t%%eax, %%ebx\n");

 emit_one_insn(fp, "\tmovl\t%d(%%esi), %%eax\n", WRDBYTES*upnp->nva_ofs);

 /* get the down instance */
 offset = MD_DOWNITPS*WRDBYTES;
 emit_one_insn(fp, "\tmovl\t%d(%%esi), %%ecx\n", offset);
 offset = WRDBYTES + inum*sizeof(struct itree_t);
 emit_one_insn(fp, "\tmovl\t%d(%%ecx), %%ecx\n", offset);

 ncp = __find_nchg_range(downnp, -1, -1);
 emit_one_insn(fp, "\tmovl\t%d(%%ecx), %%edx\n", WRDBYTES*ncp->nchg_idp_ofs);
 emit_dump_scalar_port_template(fp, downmdp, downnp, jmp_nchg_nxt);
}

/*
 * do one scalar port of more than one instance to one instance 
 * with no record
 */
static void emit_one_scalar_port_optim_1inst(FILE *fp, struct mod_t *downmdp, 
 struct mod_t *upmdp, struct net_t *downnp, struct net_t *upnp, 
 struct itree_t *downitp)
{
 size_t offset;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 offset = (downitp->itinum*downmdp->mod_idata_siz*WRDBYTES); 
 /* DBG remove -- */
 if (offset > (downmdp->flatinum*downmdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ----- */

 offset += WRDBYTES*downnp->nva_ofs;
 emit_one_insn(fp, "\tmovl\t__idpdat_%d + %d, %%ecx\n", upmdp->m_idnum, 
  WRDBYTES*upnp->nva_ofs);
 emit_one_insn(fp, "\tmovl\t%%ecx, __idpdat_%d + %d\n", downmdp->m_idnum, 
     offset);
}

/*
 * do one scalar port of more than one instance to down multiple instance 
 * with no record but with dumpvars
 */
static void emit_one_scalar_port_optim_1inst_dmpv(FILE *fp, 
 struct mod_t *downmdp, struct mod_t *upmdp, struct net_t *downnp, 
 struct net_t *upnp, struct itree_t *downitp)
{
 size_t offset;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 offset = (downitp->itinum*downmdp->mod_idata_siz*WRDBYTES); 
 /* DBG remove -- */
 if (offset > (downmdp->flatinum*downmdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* save next nchg into ebx */
 emit_one_insn(fp, "\tmovl	%%eax, %%ebx\n");

 emit_one_insn(fp, "\tmovl\t__idpdat_%d + %d, %%eax\n", upmdp->m_idnum, 
  WRDBYTES*upnp->nva_ofs);

 if (offset == 0)
  {
   emit_one_insn(fp, "\tmovl\t$__idpdat_%d, %%ecx\n", downmdp->m_idnum);
  }
 else 
  {
   emit_one_insn(fp, "\tmovl\t$__idpdat_%d + %d, %%ecx\n", downmdp->m_idnum, offset);
  }

 emit_scalar_optim_temp_no_nchg(fp, downmdp, downnp);
}

/*
 * do one scalar port of more than one instances for both sides
 */
static void emit_one_scalar_port_optim(FILE *fp, struct net_t *downnp, 
 struct net_t *upnp, int32 inum)
{
 int32 offset;

 emit_one_insn(fp, "\tmovl\t%d(%%esi), %%ebx\n", WRDBYTES*upnp->nva_ofs);
 /* get the down instance */
 offset = MD_DOWNITPS*WRDBYTES;
 emit_one_insn(fp, "\tmovl\t%d(%%esi), %%ecx\n", offset);
 offset = WRDBYTES + inum*sizeof(struct itree_t);
 emit_one_insn(fp, "\tmovl\t%d(%%ecx), %%ecx\n", offset);

 emit_one_insn(fp, "\tmovl %%ebx, %d(%%ecx)\n", WRDBYTES*downnp->nva_ofs);
}

/*
 * do one scalar port of more than one instances for both sides
 * with dumpvars
 */
static void emit_one_scalar_port_optim_dmpv(FILE *fp, struct mod_t *downmdp,
 struct net_t *downnp, struct net_t *upnp, int32 inum)
{
 size_t offset;

 /* save next nchg into ebx */
 emit_one_insn(fp, "\tmovl	%%eax, %%ebx\n");

 emit_one_insn(fp, "\tmovl\t%d(%%esi), %%eax\n", WRDBYTES*upnp->nva_ofs);
 /* get the down instance */
 offset = MD_DOWNITPS*WRDBYTES;
 emit_one_insn(fp, "\tmovl\t%d(%%esi), %%ecx\n", offset);
 offset = WRDBYTES + inum*sizeof(struct itree_t);
 emit_one_insn(fp, "\tmovl\t%d(%%ecx), %%ecx\n", offset);
 emit_scalar_optim_temp_no_nchg(fp, downmdp, downnp);
}

/*
 * emit code to do a dumpvars with no net change record
 */
static void emit_scalar_optim_temp_no_nchg(FILE *fp, struct mod_t *downmdp, 
 struct net_t *downnp)
{
 int32 mask, ndx;
 size_t offset;
 char retlab[RECLEN], np_str[RECLEN], s1[RECLEN];

 __bblk_seq_no++;
 sprintf(retlab, "L_%d", __bblk_seq_no);

 __bldchk_var_comm_ref(s1, downnp, downmdp, NULL);
 ndx = downnp - downmdp->mnets;
 sprintf(np_str, "%s_np_%d", s1, ndx);

 offset = WRDBYTES*downnp->nva_ofs;
 emit_one_insn(fp, "\tcmpl	%d(%%ecx), %%eax\n", offset);
 emit_one_insn(fp, "\tje	%s\n", retlab);
 emit_one_insn(fp, "\tmovl	%%eax, %d(%%ecx)\n", offset);
 /* DBG remove -- */
 if (downnp->nchgaction_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */

 downnp->is_loaded = TRUE;
 /* handle the toggle change */
 if (downnp->n_has_toggle)
  {
   emit_one_insn(fp, "\tmovl	%%ecx, __idp\n");
   emit_one_insn(fp, "\tmovl	%s, %%eax\n", np_str);
   emit_one_insn(fp, "\tmovl	%%eax, (%%esp)\n");
   emit_one_insn(fp, "\tcall	__add_togglelst_el\n");
   emit_one_insn(fp, "\tmovl	__idp, %%ecx\n");
  }

 if (downnp->dmpv_in_src || downnp->dmpp_in_src)
  {
   offset = (downnp->nchgaction_ofs*WRDBYTES);
   /* AIV 04/22/11 - mask was wrong for dumpports */
   if (downnp->dmpv_in_src) mask = (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED);
   else mask = (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED);
   emit_one_insn(fp, "\tmovl	%d(%%ecx), %%eax\n", offset);
   emit_one_insn(fp, "\tandl	$%d, %%eax\n", mask);
   emit_one_insn(fp, "\tcmpl	$%d, %%eax\n", mask);
   emit_one_insn(fp, "\tjne	%s\n", retlab);
   emit_one_insn(fp, "\tmovl	%%ecx, __idp\n");
 
   emit_one_insn(fp, "\tmovl	%s, %%eax\n", np_str);
   emit_one_insn(fp, "\tmovl	%%eax, (%%esp)\n");
   if (downnp->dmpv_in_src) emit_one_insn(fp, "\tcall	__asl_add_dmpv_chglst_el\n");
   if (downnp->dmpp_in_src) emit_one_insn(fp, "\tcall	__asl_add_dmpp_chglst_el\n");
  }

 emit_one_insn(fp, "%s:\n", retlab);
 /* put next nchg back into %eax */
 emit_one_insn(fp, "\tmovl\t%%ebx, %%eax\n");
}
#else
/*
 * 64 - bit version same as 32-bit version except insns/regs have been
 * changed to use movq and rsi registers along with %r15 for idp reg
 * AIV 11/03/09 - these should use %rip for globals - added %rip
 */
/*
 * refer to 32-bit version above
 */
static void emit_one_scalar_port_optim_nchg_1inst(FILE *fp, 
 struct mod_t *downmdp, struct mod_t *upmdp, struct net_t *downnp, 
 struct net_t *upnp, struct itree_t *downitp, int32 jmp_nchg_nxt)
{
 struct net_chg_t *ncp;
 size_t offset, inst_ofs;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 inst_ofs = (downitp->itinum*downmdp->mod_idata_siz*WRDBYTES); 

 /* DBG remove -- */
 if (inst_ofs > (downmdp->flatinum*downmdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ----- */

 ncp = __find_nchg_range(downnp, -1, -1);


 /* AIV 07/21/09 - this code is assuming this is always true */
 /* dependent upon order of offset alloc in prep code */
 /* DBG remove -- */
 if (ncp->nchg_idp_ofs < downnp->nva_ofs) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* AIV 08/28/09 - added support for large model - just need extra */
 /* level of direction for possible large static memory areas */
 if (__cvc_use_large_model)
  {
   fprintf(fp, "\tmovabsq\t$__idpdat_%d + %lu, %%rbx\n", upmdp->m_idnum, 
     WRDBYTES*upnp->nva_ofs);
   offset = inst_ofs + WRDBYTES*downnp->nva_ofs;
   fprintf(fp, "\tmovabsq\t$__idpdat_%d + %lu, %%rcx\n", downmdp->m_idnum, 
    offset);
   fprintf(fp, "\tmovq\t(%%rbx), %%rbx\n");
  }
 else
  {
   fprintf(fp, "\tmovq\t__idpdat_%d+%lu(%%rip), %%rbx\n", upmdp->m_idnum, 
     WRDBYTES*upnp->nva_ofs);
   offset = inst_ofs + WRDBYTES*downnp->nva_ofs;
   fprintf(fp, "\tmovq\t$__idpdat_%d + %lu, %%rcx\n", downmdp->m_idnum, 
     offset);
  }
 offset = (inst_ofs + (WRDBYTES*ncp->nchg_idp_ofs)) - offset;
 fprintf(fp, "\tmovq\t%lu(%%rcx), %%rdx\n", offset);
 if (jmp_nchg_nxt)
  {
   if (downnp->n_mipd) fprintf(fp, "\tjmp\tICONN_S_S_NCHG_NXT_MIPD\n");
   else fprintf(fp, "\tjmp\tICONN_S_S_NCHG_NXT\n");
  }
 else
  {
   if (downnp->n_mipd) fprintf(fp, "\tcall\tICONN_S_S_NCHG_MIPD\n");
   else fprintf(fp, "\tcall\tICONN_S_S_NCHG\n");
  }
}

/*
 * refer to 32-bit version above
 */
static void emit_one_scalar_port_optim_nchg_1inst_dmpv(FILE *fp, 
 struct mod_t *downmdp, struct mod_t *upmdp, struct net_t *downnp, 
 struct net_t *upnp, struct itree_t *downitp, int32 jmp_nchg_nxt)
{
 struct net_chg_t *ncp;
 size_t offset;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 offset = (downitp->itinum*downmdp->mod_idata_siz*WRDBYTES); 
 /* DBG remove -- */
 if (offset > (downmdp->flatinum*downmdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* save next nchg back into %ebx */
 emit_one_insn(fp, "\tmovq\t%%rax, %%rbx\n");

 /* AIV 08/28/09 - added support for large model - just need extra */
 /* level of direction for possible large static memory areas */
 if (__cvc_use_large_model)
  {
   emit_one_insn(fp, "\tmovabsq\t$__idpdat_%d + %lu, %%rax\n", upmdp->m_idnum, 
    WRDBYTES*upnp->nva_ofs);
   if (offset == 0)
    {
     emit_one_insn(fp, "\tmovabsq\t$__idpdat_%d, %%rcx\n", downmdp->m_idnum);
    }
   else
    {
     emit_one_insn(fp, "\tmovabsq\t$__idpdat_%d + %lu, %%rcx\n", 
      downmdp->m_idnum, offset);
    }
   fprintf(fp, "\tmovq\t(%%rax), %%rax\n");
  }
 else
  {
   emit_one_insn(fp, "\tmovq\t__idpdat_%d+%lu(%%rip), %%rax\n", upmdp->m_idnum, 
    WRDBYTES*upnp->nva_ofs);
   if (offset == 0)
    {
     emit_one_insn(fp, "\tmovq\t$__idpdat_%d, %%rcx\n", downmdp->m_idnum);
    }
   else
    {
     emit_one_insn(fp, "\tmovq\t$__idpdat_%d + %lu, %%rcx\n", downmdp->m_idnum,
      offset);
    }
  }
 ncp = __find_nchg_range(downnp, -1, -1);
 emit_one_insn(fp, "\tmovq\t%lu(%%ecx), %%rdx\n", WRDBYTES*ncp->nchg_idp_ofs);
 
 emit_dump_scalar_port_template(fp, downmdp, downnp, jmp_nchg_nxt);
}

/*
 * refer to 32-bit version above
 */
static void emit_dump_scalar_port_template(FILE *fp, struct mod_t *downmdp, 
 struct net_t *downnp, int32 jmp_nchg_nxt)
{
 int32 mask, ndx;
 struct nchglst_t *nchgp;
 size_t offset;
 char retlab[RECLEN], chklab[RECLEN], np_str[RECLEN], s1[RECLEN];

 __bblk_seq_no++;
 sprintf(retlab, "L_%d", __bblk_seq_no);
 __bblk_seq_no++;
 sprintf(chklab, "L_%d", __bblk_seq_no);

 __bldchk_var_comm_ref(s1, downnp, downmdp, NULL);
 ndx = downnp - downmdp->mnets;
 /* AIV 09/13/11 - this needs the extra movabsq for the large model */
 /* movabsq	$c, %rax */
 /* movq (%rax), %rax */
 if (__cvc_use_large_model)
  {
   sprintf(np_str, "%s_np_%d", s1, ndx);
   emit_one_insn(fp, "\tmovabsq	$%s, %%r8\n", np_str);
   emit_one_insn(fp, "\tmovq	(%%r8), %%r8\n");
   strcpy(np_str, "%r8");
  }
 /* AIV 09/13/11 - this should have the (%rip) */
 else sprintf(np_str, "%s_np_%d(%%rip)", s1, ndx);
 
 nchgp = &__nchg_dummy_hd;
 offset =  WRDBYTES*downnp->nva_ofs;
 emit_one_insn(fp, "\tcmpq	%lu(%%rcx), %%rax\n", offset);
 emit_one_insn(fp, "\tje	%s\n", retlab);
 emit_one_insn(fp, "\tmovq	%%rax, %lu(%%rcx)\n", offset);
 emit_one_insn(fp, "\tmovq	(%%rdx), %%rax\n");
 emit_one_insn(fp, "\ttestq	%%rax, %%rax\n");
 emit_one_insn(fp, "\tjne	%s\n", chklab);
 emit_one_insn(fp, "\tmovq	__nchg_futend(%%rip), %%rax\n");
 emit_one_insn(fp, "\tmovq	%%rax, (%%rdx)\n");
 if (downnp->n_mipd)
  {
   offset = (byte *) &(nchgp->delayed_mipd) - (byte *) nchgp;
   emit_one_insn(fp, "\tmovq	$0, %lu(%%edx)\n", offset);
  }
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 emit_one_insn(fp, "\tmovq	%%rdx, %lu(%%rax)\n", offset);
 emit_one_insn(fp, "\tmovq	%%rdx, __nchg_futend(%%rip)\n");
 emit_one_insn(fp, "%s:\n", chklab);

 /* DBG remove -- */
 if (downnp->nchgaction_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 downnp->is_loaded = TRUE;
 offset = (downnp->nchgaction_ofs*WRDBYTES);

 /* handle the toggle change */
 if (downnp->n_has_toggle)
  {
   emit_one_insn(fp, "\tmovq	%%rcx, __idp(%%rip)\n");
   emit_one_insn(fp, "\tmovq	%s, %%rdi\n", np_str);
   emit_one_insn(fp, "\tcall	__add_togglelst_el\n");
   emit_one_insn(fp, "\tmovq	__idp(%%rip), %%rcx\n");
  }

 if (downnp->dmpv_in_src || downnp->dmpp_in_src)
  {
   /* AIV 04/22/11 - mask was wrong for dumpports */
   if (downnp->dmpv_in_src) mask = (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED);
   else mask = (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED);
   emit_one_insn(fp, "\tmovq	%lu(%%rcx), %%rax\n", offset);
   emit_one_insn(fp, "\tandq	$%d, %%rax\n", mask);
   emit_one_insn(fp, "\tcmpq	$%d, %%rax\n", mask);
   emit_one_insn(fp, "\tjne	%s\n", retlab);
   emit_one_insn(fp, "\tmovq	%%rcx, __idp(%%rip)\n");
 
   emit_one_insn(fp, "\tmovq	%s, %%rdi\n", np_str);
   if (downnp->dmpv_in_src) emit_one_insn(fp, "\tcall	__asl_add_dmpv_chglst_el\n");
   if (downnp->dmpp_in_src) emit_one_insn(fp, "\tcall	__asl_add_dmpp_chglst_el\n");
  }

 emit_one_insn(fp, "%s:\n", retlab);
 /* put next nchg back into %eax */
 emit_one_insn(fp, "\tmovq\t%%rbx, %%rax\n");
 if (jmp_nchg_nxt)
  {
   nchgp = &__nchg_dummy_hd;
   offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
   emit_one_insn(fp, "\tmovq\t%lu(%%rax), %%rbx\n", offset);
   emit_one_insn(fp, "\tjmp\t*%%rbx\n");
  }
}

/*
 * refer to 32-bit version above
 */
static void emit_one_scalar_port_optim_nchg(FILE *fp, 
 struct net_t *downnp, struct net_t *upnp, int32 inum, int32 jmp_nchg_nxt)
{
 struct net_chg_t *ncp;
 size_t offset;

 emit_one_insn(fp, "\tmovq\t%lu(%s), %%rbx\n", WRDBYTES*upnp->nva_ofs, 
   __regs[IDP_REG]);
 /* get the down instance */
 offset = MD_DOWNITPS*WRDBYTES;
 emit_one_insn(fp, "\tmovq\t%lu(%s), %%rcx\n", offset, __regs[IDP_REG]);
 offset = WRDBYTES + inum*sizeof(struct itree_t);
 emit_one_insn(fp, "\tmovq\t%lu(%%rcx), %%rcx\n", offset);
 ncp = __find_nchg_range(downnp, -1, -1);
 emit_one_insn(fp, "\tmovq\t%lu(%%rcx), %%rdx\n", WRDBYTES*ncp->nchg_idp_ofs);
 emit_one_insn(fp, "\taddq\t$%lu, %%rcx\n", WRDBYTES*downnp->nva_ofs);
 if (jmp_nchg_nxt)
  {
   if (downnp->n_mipd) emit_one_insn(fp, "\tjmp\tICONN_S_S_NCHG_NXT_MIPD\n");
   else emit_one_insn(fp, "\tjmp\tICONN_S_S_NCHG_NXT\n");
  }
 else
  {
   if (downnp->n_mipd) emit_one_insn(fp, "\tcall\tICONN_S_S_NCHG\n");
   else emit_one_insn(fp, "\tcall\tICONN_S_S_NCHG_MIPD\n");
  }
}

/*
 * refer to 32-bit version above
 */
static void emit_one_scalar_port_optim_nchg_dmpv(FILE *fp, 
 struct mod_t *downmdp, struct net_t *downnp, struct net_t *upnp, 
 int32 inum, int32 jmp_nchg_nxt)
{
 struct net_chg_t *ncp;
 size_t offset;

 /* need to save next into ebx */
 emit_one_insn(fp, "\tmovq\t%%rax, %%rbx\n");

 emit_one_insn(fp, "\tmovq\t%lu(%%r15), %%rax\n", WRDBYTES*upnp->nva_ofs);

 /* get the down instance */
 offset = MD_DOWNITPS*WRDBYTES;
 emit_one_insn(fp, "\tmovq\t%lu(%%r15), %%rcx\n", offset);
 offset = WRDBYTES + inum*sizeof(struct itree_t);
 emit_one_insn(fp, "\tmovq\t%lu(%%rcx), %%rcx\n", offset);

 ncp = __find_nchg_range(downnp, -1, -1);
 emit_one_insn(fp, "\tmovq\t%lu(%%rcx), %%rdx\n", WRDBYTES*ncp->nchg_idp_ofs);
 emit_dump_scalar_port_template(fp, downmdp, downnp, jmp_nchg_nxt);
}

/*
 * refer to 32-bit version above
 */
static void emit_one_scalar_port_optim_1inst(FILE *fp, struct mod_t *downmdp, 
 struct mod_t *upmdp, struct net_t *downnp, struct net_t *upnp, 
 struct itree_t *downitp)
{
 size_t offset;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 offset = (downitp->itinum*downmdp->mod_idata_siz*WRDBYTES); 
 /* DBG remove -- */
 if (offset > (downmdp->flatinum*downmdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ----- */

 offset += WRDBYTES*downnp->nva_ofs;
 /* AIV 08/28/09 - added support for large model - just need extra */
 /* level of direction for possible large static memory areas */
 if (__cvc_use_large_model)
  {
   emit_one_insn(fp, "\tmovabsq\t$__idpdat_%d + %lu, %%rcx\n", upmdp->m_idnum, 
    WRDBYTES*upnp->nva_ofs);
   fprintf(fp, "\tmovq\t(%%rcx), %%rdi\n");
   emit_one_insn(fp, "\tmovabsq\t$__idpdat_%d + %lu, %%rdx\n", 
    downmdp->m_idnum, offset);
   fprintf(fp, "\tmovq\t%%rdi, (%%rdx)\n");
  }
 else
  {
   emit_one_insn(fp, "\tmovq\t__idpdat_%d+%lu(%%rip), %%rcx\n", upmdp->m_idnum, 
    WRDBYTES*upnp->nva_ofs);
   emit_one_insn(fp, "\tmovq\t%%rcx, __idpdat_%d+%lu(%%rip)\n", 
    downmdp->m_idnum, offset);
  }
}

/*
 * refer to 32-bit version above
 */
static void emit_one_scalar_port_optim_1inst_dmpv(FILE *fp, 
 struct mod_t *downmdp, struct mod_t *upmdp, struct net_t *downnp, 
 struct net_t *upnp, struct itree_t *downitp)
{
 size_t offset;

 /* AIV 08/19/09 - changed this - can no longer use idp */
 offset = (downitp->itinum*downmdp->mod_idata_siz*WRDBYTES); 
 /* DBG remove -- */
 if (offset > (downmdp->flatinum*downmdp->mod_idata_siz*WRDBYTES)) 
   __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* save next nchg into ebx */
 emit_one_insn(fp, "\tmovq	%%rax, %%rbx\n");

 /* AIV 08/28/09 - added support for large model - just need extra */
 /* level of direction for possible large static memory areas */
 if (__cvc_use_large_model)
  {
   emit_one_insn(fp, "\tmovabsq\t$__idpdat_%d + %lu, %%rax\n", upmdp->m_idnum, 
    WRDBYTES*upnp->nva_ofs);
  }
 else
  {
   emit_one_insn(fp, "\tmovq\t__idpdat_%d+%lu(%%rip), %%rax\n", upmdp->m_idnum, 
    WRDBYTES*upnp->nva_ofs);
  }

 /* AIV 09/13/11 - added support for large model - just need extra */
 /* level of direction for possible large static memory areas */
 if (__cvc_use_large_model)
  {
   if (offset == 0)
    {
     emit_one_insn(fp, "\tmovabsq\t$__idpdat_%d, %%rcx\n", downmdp->m_idnum);
    }
   else 
    {
     emit_one_insn(fp, "\tmovabsq\t$__idpdat_%d+%lu, %%rcx\n", 
       downmdp->m_idnum, offset);
    }
  }
 else
  {
   if (offset == 0)
    {
     emit_one_insn(fp, "\tmovq\t$__idpdat_%d, %%rcx\n", downmdp->m_idnum);
    }
   else 
    {
     emit_one_insn(fp, "\tmovq\t$__idpdat_%d+%lu, %%rcx\n", 
       downmdp->m_idnum, offset);
    }
  }
 if (__cvc_use_large_model)
  {
   fprintf(fp, "\tmovq\t(%%rax), %%rax\n");
  }

 emit_scalar_optim_temp_no_nchg(fp, downmdp, downnp);
}

/*
 * refer to 32-bit version above
 */
static void emit_one_scalar_port_optim(FILE *fp, struct net_t *downnp, 
 struct net_t *upnp, int32 inum)
{
 size_t offset;

 emit_one_insn(fp, "\tmovq\t%ld(%s), %%rbx\n", WRDBYTES*upnp->nva_ofs, 
   __regs[IDP_REG]);
 /* get the down instance */
 offset = MD_DOWNITPS*WRDBYTES;
 emit_one_insn(fp, "\tmovq\t%lu(%s), %%rcx\n", offset, __regs[IDP_REG]);
 offset = WRDBYTES + inum*sizeof(struct itree_t);
 emit_one_insn(fp, "\tmovq\t%lu(%%rcx), %%rcx\n", offset);

 emit_one_insn(fp, "\tmovq %%rbx, %ld(%%rcx)\n", WRDBYTES*downnp->nva_ofs);
}

/*
 * refer to 32-bit version above
 */
static void emit_one_scalar_port_optim_dmpv(FILE *fp, struct mod_t *downmdp,
 struct net_t *downnp, struct net_t *upnp, int32 inum)
{
 size_t offset;

 /* save next nchg into ebx */
 emit_one_insn(fp, "\tmovq	%%rax, %%rbx\n");

 emit_one_insn(fp, "\tmovq\t%lu(%%r15), %%rax\n", WRDBYTES*upnp->nva_ofs);
 /* get the down instance */
 offset = MD_DOWNITPS*WRDBYTES;
 emit_one_insn(fp, "\tmovq\t%lu(%%r15), %%rcx\n", offset);
 offset = WRDBYTES + inum*sizeof(struct itree_t);
 emit_one_insn(fp, "\tmovq\t%lu(%%rcx), %%rcx\n", offset);
 emit_scalar_optim_temp_no_nchg(fp, downmdp, downnp);
}

/*
 * refer to 32-bit version above
 */
static void emit_scalar_optim_temp_no_nchg(FILE *fp, struct mod_t *downmdp, 
 struct net_t *downnp)
{
 int32 mask, ndx;
 size_t offset;
 char retlab[RECLEN], np_str[RECLEN], s1[RECLEN];

 __bblk_seq_no++;
 sprintf(retlab, "L_%d", __bblk_seq_no);

 __bldchk_var_comm_ref(s1, downnp, downmdp, NULL);
 ndx = downnp - downmdp->mnets;
 /* AIV 09/13/11 - this needs the extra movabsq for the large model */
 /* movabsq	$c, %rax */
 /* movq (%rax), %rax */
 if (__cvc_use_large_model)
  {
   sprintf(np_str, "%s_np_%d", s1, ndx);
   emit_one_insn(fp, "\tmovabsq	$%s, %%r8\n", np_str);
   emit_one_insn(fp, "\tmovq	(%%r8), %%r8\n");
   strcpy(np_str, "%r8");
  }
 /* AIV 09/13/11 - this should have the (%rip) */
 else sprintf(np_str, "%s_np_%d(%%rip)", s1, ndx);

 offset = WRDBYTES*downnp->nva_ofs;
 emit_one_insn(fp, "\tcmpq	%lu(%%rcx), %%rax\n", offset);
 emit_one_insn(fp, "\tje	%s\n", retlab);
 emit_one_insn(fp, "\tmovq	%%rax, %lu(%%rcx)\n", offset);
 /* DBG remove -- */
 if (downnp->nchgaction_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 downnp->is_loaded = TRUE;
 
 /* handle the toggle change */
 if (downnp->n_has_toggle)
  {
   emit_one_insn(fp, "\tmovq	%%rcx, __idp(%%rip)\n");
   emit_one_insn(fp, "\tmovq	%s, %%rdi\n", np_str);
   emit_one_insn(fp, "\tcall	__add_togglelst_el\n");
   emit_one_insn(fp, "\tmovq	__idp(%%rip), %%rcx\n");
  }

 if (downnp->dmpv_in_src || downnp->dmpp_in_src)
  {
   offset = (downnp->nchgaction_ofs*WRDBYTES);
   /* AIV 04/22/11 - mask was wrong for dumpports */
   if (downnp->dmpv_in_src) mask = (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED);
   else mask = (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED);
   emit_one_insn(fp, "\tmovq	%lu(%%rcx), %%rax\n", offset);
   emit_one_insn(fp, "\tandq	$%d, %%rax\n", mask);
   emit_one_insn(fp, "\tcmpq	$%d, %%rax\n", mask);
   emit_one_insn(fp, "\tjne	%s\n", retlab);
   emit_one_insn(fp, "\tmovq	%%rcx, __idp(%%rip)\n");
 
   emit_one_insn(fp, "\tmovq	%s, %%rdi\n", np_str);
   if (downnp->dmpv_in_src) emit_one_insn(fp, "\tcall	__asl_add_dmpv_chglst_el\n");
   if (downnp->dmpp_in_src) emit_one_insn(fp, "\tcall	__asl_add_dmpp_chglst_el\n");
  }

 emit_one_insn(fp, "%s:\n", retlab);
 /* put next nchg back into %eax */
 emit_one_insn(fp, "\tmovq\t%%rbx, %%rax\n");
}
#endif

/*
 * turn off the used in asm flag for all tn's used in flow graph
 *
 * this is for consntants that are mostly converted to literals so do not
 * need to emit in mod's contab area
 */
static void turn_off_used_in_asm_flag(struct flowg_t *fgp)
{
 int32 avli;
 int32 siz_avltab;
 struct avlnode_t *nodp, **tn_avltab;
 struct tn_dup_t *tndup;

 tn_avltab = __linearize_avl_tree(fgp->fg_tn_ref_tree, &(siz_avltab));
 if (siz_avltab <= 0) return;

 for (avli = 0; avli < siz_avltab; avli++)
  {
   nodp = (struct avlnode_t *) tn_avltab[avli];
   tndup = (struct tn_dup_t *) nodp->valp;
   __tntab[tndup->tni].used_in_asm = FALSE;
  }
 __my_free(tn_avltab, siz_avltab*sizeof(struct avlnode_t *));
}

/*
 * build gas format insn into one line without adding the new line
 * now passed 3 arg that is true if need debug amode printing
 *
 * new algorithm - if res tni set uses 3 addr form - when convert to 2
 * addr x86 form must set res tni to -1
 */
extern char *__asm_insn_tostr(char *s, struct insn_t *ip, int32 dbg_fmt,
 struct flowg_t *fgp)
{
 struct insn_info_t *iip;
 char isrcnam[RECLEN], idstnam[RECLEN], inam[RECLEN];

 iip = __to_iinfo_rec(ip->opcod);

 /* AIV 07/07/09 - added this to remove the string calls from bbgen3 */
 /* call fixed ICONN_, DCE_, CAP_, etc  */
 if (ip->opcod == I_FG_CALL)
  {
   get_fixed_fg_call_nam(isrcnam, ip->isrc.disp);
#ifdef __CVC32__
   sprintf(s, "\t%s\t%s_%u", iip->inam, isrcnam, ip->idst.disp);
#else
   sprintf(s, "\t%s\t%s_%lu", iip->inam, isrcnam, ip->idst.disp);
#endif
   return(s);
  }

 /* need to use cond. code to build x86 jump vinsn name */
 /* jmp is the x86 insn after lowering to label jump */
 if (ip->opcod == I_JMP) __get_jmp_insn_nam(inam, ip);
 else 
  {
   /* notice the index jump goes here because no condition codes */
   strcpy(inam, iip->inam);

   /* SJM 04/29/07 - need to add condition code to bblk style cond jumps */
   if (ip->opcod == I_COND_JMP || ip->opcod == I_REAL_COND_JMP)
    {
     char s1[RECLEN], s2[RECLEN];

     __get_jmp_insn_nam(s1, ip);
     sprintf(s2, "%s[%s]", inam, s1);
     strcpy(inam, s2);
    }
  }

#ifdef __CVC32__
 /* AIV 08/02/06 - this is a special insn used for real compare */
 /* currently it takes eax - because the instruction writes eax */
 /* but it doesn't take eax but is passed to indicate it's use conflicts */ 
 /* AIV LOOKATME - better method ???? - maybe put into insn_info table */
 if (ip->opcod == I_FNSTSW || ip->opcod == I_CLTD)
  {
   sprintf(s, "\t%s", inam);
   return(s);
  }
#else
 /* AIV 11/12/08 - handle reals as special load/store into xmm0 and xmm1 */
 switch (ip->opcod) {
  case I_LDR1:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm0", inam, idstnam);
   return(s);
  case I_LDR2:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm1", inam, idstnam);
   return(s);
  case I_LDR3:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm2", inam, idstnam);
   return(s);
  case I_LDR4:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm3", inam, idstnam);
   return(s);
  case I_LDR5:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm4", inam, idstnam);
   return(s);
  case I_LDR6:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm5", inam, idstnam);
   return(s);
  case I_LDR7:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm6", inam, idstnam);
   return(s);
  case I_LDR8:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm7", inam, idstnam);
   return(s);
  case I_LDR9:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm8", inam, idstnam);
   return(s);
  case I_LDR10:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm9", inam, idstnam);
   return(s);
  case I_LDR11:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm10", inam, idstnam);
   return(s);
  case I_LDR12:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm11", inam, idstnam);
   return(s);
  case I_LDR13:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm12", inam, idstnam);
   return(s);
  case I_LDR14:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm13", inam, idstnam);
   return(s);
  case I_LDR15:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm14", inam, idstnam);
   return(s);
  case I_LDR16:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %s, %%xmm15", inam, idstnam);
   return(s);
  case I_STREAL:
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   sprintf(s, "\t%s   %%xmm0, %s", inam, idstnam);
   return(s);
  }
#endif

 /* SJM 10/25/06 - pre lowered ASL call insns are now special cases */
 /* because there is a table of argument tns so many amodes */
 if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
  {
   /* DBG remove -- */ 
   if (!dbg_fmt) __misc_terr(__FILE__, __LINE__);
   /* --- */
   call_asl_insn_tostr(s, ip);
   return(s);
  }

 if (ip->opcod == I_DEFLST)
  {
   /* DBG remove -- */
   if (!dbg_fmt) __misc_terr(__FILE__, __LINE__);
   /* --- */ 

   /* phi - factored def use beginning of bblk ptrs to define live */
   /* on bblk entry do not exist in asm - only for optimizing */
   deflst_insn_tostr(s, ip);
   return(s);
  }

 if (ip->isrc.amode == AM_NONE && ip->idst.amode == AM_NONE)
  {
   /* SJM 12/20/06 - for debugging, add bblk name in prologue pseudo insn */   
   if (dbg_fmt)
    {
     if (ip->opcod == I_PROLOGUE)
      {
       sprintf(s, "\t%s\tbblk_seqno=%d", inam, ip->extrau.prologue_bblkno);
       return(s);
      }
    }
   sprintf(s, "\t%s", inam);
   return(s);
  }

 if (ip->isrc.amode == AM_NONE)
  {
   /* 1 operand x86 machine insns */
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
   if (need_inam(ip->opcod)) sprintf(s, "\t%s\t%s", inam, idstnam);
   else sprintf(s, "%s", idstnam);
   return(s);
  }
 if (iip->iclass == ICLASS_MOV || iip->iclass == ICLASS_UN)
  {
   __bld_amods(isrcnam, ip, ip->opcod, &(ip->isrc), dbg_fmt, fgp);

   /* for moves uses first src operand for src but no dst amode */
   /* until converted from 3 to 2 operand form */
   if (ip->res_tni != -1)
    {
     sprintf(s, "\t%s\t%s =>r%d", inam, isrcnam, ip->res_tni);
    }
   else
    {
     __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);
     sprintf(s, "\t%s\t%s, %s", inam, isrcnam, idstnam);
    }
   return(s);
  }

 /* 2 operand x86 machine insns */
 __bld_amods(isrcnam, ip, ip->opcod, &(ip->isrc), dbg_fmt, fgp);
 __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), dbg_fmt, fgp);

 /* 08/04/06 SJM - if only one amode must be in dst */
 /* i.e. if only one operand goes in dst */
 /* DBG remove -- */
 if (ip->idst.amode == AM_NONE) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (iip->iclass == ICLASS_CMP)
  {
   /* compare never have 3rd result operand */
   sprintf(s, "\t%s\t%s, %s", inam, isrcnam, idstnam);
   return(s);
  }
 if (iip->iclass == ICLASS_STORE)
  {
   /* compare never have 3rd result operand */
   if (dbg_fmt)
    {
     /* SJM 11/20/06 - for copy also print the number of bytes */
     if (ip->opcod == I_COPY)
      {
#ifdef __CVC32__
       sprintf(s, "\t%s[BYTES=%u]\t%s, %s", inam, ip->isrc.disp,
        isrcnam, idstnam);
#else
       sprintf(s, "\t%s[BYTES=%lu]\t%s, %s", inam, ip->isrc.disp,
        isrcnam, idstnam);
#endif
      }
     else sprintf(s, "\t%s[STORE]\t%s, %s", inam, isrcnam, idstnam);
    }
   else sprintf(s, "\t%s\t%s, %s", inam, isrcnam, idstnam);
   return(s);
  }

 if (ip->res_tni != -1)
  {
   __bld_amods(idstnam, ip, ip->opcod, &(ip->idst), TRUE, fgp);
   sprintf(s, "\t%s\t%s, %s =>r%d", inam, isrcnam, idstnam, ip->res_tni);
  }
 else sprintf(s, "\t%s\t%s, %s", inam, isrcnam, idstnam);
 return(s);
}

/*
 * get a fixed flow graph name stem
 */
static char *get_fixed_fg_call_nam(char *s, int32 type)
{
 switch (type) {
  case FG_ICONN:
   strcpy(s, "ICONN");
   break;
  case FG_GATECA:
   strcpy(s, "GATECA");
   break;
  case FG_CAP:
   strcpy(s, "CAP");
   break;
  case FG_NCHG:
   strcpy(s, "NCHG");
   break;
  default:
   __case_terr(__FILE__, __LINE__);
   break;
 }
 return(s);
}


/*
 * get jump insn name (jmptyp is the cc)
 * asm insn name differs for signed since it needs to check SF (signed) flg
 *
 * routine can only be called while converting to asm insn string
 */
extern char *__get_jmp_insn_nam(char *s, struct insn_t *ip) 
{
 switch (ip->jmptyp) {
  case CC_NONE:
   strcpy(s, "jmp");
   break;
  case CC_JE:
   strcpy(s, "je");
   break;
  case CC_JNE:
   strcpy(s, "jne");
   break;
  case CC_JZ:
   strcpy(s, "jz");
   break;
  case CC_JNZ:
   strcpy(s, "jnz");
   break;
  case CC_JGE:
   if (ip->sgn_jmp) strcpy(s, "jge"); else strcpy(s, "jae");
   break;
  case CC_JGT:
   if (ip->sgn_jmp) strcpy(s, "jg"); else strcpy(s, "ja");
   break;
  case CC_JLE:
   if (ip->sgn_jmp) strcpy(s, "jle"); else strcpy(s, "jbe");
   break;
  case CC_JLT:
   if (ip->sgn_jmp) strcpy(s, "jl"); else strcpy(s, "jb");
   break;
  case CC_JNS:
   /* DBG remove -- */
   if (ip->sgn_jmp) __misc_terr(__FILE__, __LINE__);
   /* --- */
   strcpy(s, "jns");
   break;
  case CC_JP:
   /* DBG remove -- */
   if (ip->sgn_jmp) __misc_terr(__FILE__, __LINE__);
   /* --- */
   strcpy(s, "jp");
   break;
  case CC_JA:
   strcpy(s, "ja");
   break;
  case CC_JB:
   strcpy(s, "jb");
   break;
  case CC_JAE:
   strcpy(s, "jae");
   break;
  case CC_JBE:
   strcpy(s, "jbe");
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * build the insn name string for a pre-lowering call asl insn
 */
static char *call_asl_insn_tostr(char *s, struct insn_t *ip)
{
 int32 ai, tni, atyp, amode;
 struct asl_info_t *aslp;
 struct amode_t tmp_amode;
 struct asl_def_t *aslap;
 char aslcallnam[RECLEN], argnam[RECLEN];

 aslp = __to_aslinfo_rec(ip->idst.disp);
 strcpy(aslcallnam, aslp->asl_rout_nam);
 sprintf(s, "\t%s", aslcallnam);
 /* SJM 11/02/06 - 0 args can be function that returns a value */
 if (ip->callasl_argnum == 0)
  {
   if (ip->opcod == I_CALL_ASLFUNC) strcat(s, " ==> %eax");
   return(s);
  }

 for (ai = 0; ai < ip->callasl_argnum; ai++)
  {
   aslap = &(ip->extrau.asl_ausedefs[ai]);
   tni = aslap->am_arg.am_tni;

   __init_amode(&(tmp_amode));
   tmp_amode.am_tni = tni;
   atyp = aslp->asl_op_typ[ai];

   if (atyp == A_NUM) 
    {
     amode = AM_IMM;
     tmp_amode.disp = __get_wrd_con_val(tni);
    }
   else amode = AM_REG;

/* -----
    {
     if (__tntab[tni].comlab_typ != COMLAB_NONE)
      {
       if (__is_nlptr_comlab(__tntab[tni].comlab_typ)) amode = AM_REG;
       else amode = AM_NDXREG;
      }
     else if (__tntab[tni].tn_typ == TN_ADR) amode = AM_REG;
     else amode = AM_NDXREG;
    }
---- */

   tmp_amode.amode = amode;
   __bld_amods(argnam, ip, ip->opcod, &(tmp_amode), TRUE, NULL);
   if (ai == 0) strcat(s, "("); else strcat(s, ", ");
   strcat(s, argnam);
  }
 if (ip->opcod == I_CALL_ASLFUNC) strcat(s, ") ==> %eax");
 else strcat(s, ")");

 return(s);
}

/*
 * print the phi insns use tn and the list of all define <bblk, ndx> tuples
 * live on entry to the bblk
 */
static char *deflst_insn_tostr(char *s, struct insn_t *ip)
{
 struct defilst_t *dfilp;
 char s1[RECLEN];

 /* DBG remove -- */
 if (ip->idst.amode != AM_REG) __misc_terr(__FILE__, __LINE__);

 /* -- */
#ifdef __CVC32__
 sprintf(s, "\tI_DEFLST-%u\tr%d\t", ip->isrc.disp, ip->idst.am_tni);
#else
 sprintf(s, "\tI_DEFLST-%lu\tr%d\t", ip->isrc.disp, ip->idst.am_tni);
#endif
 for (dfilp = ip->extrau.defilst; dfilp != NULL; dfilp = dfilp->defilstnxt)
  {
   if (dfilp->defip == NULL) sprintf(s1, "(USE-BEFORE-DEF)");
   else sprintf(s1, "(NDX=%d)", dfilp->defip->ndx);
   strcat(s, s1);
   if (dfilp->defilstnxt != NULL) strcat(s, ", ");
  }
 return(s);
}

/*
 * ROUTINES TO CONVERT AMODES TO STRINGS
 */

/*
 * build the amode string given a reg string name (if has one)
 *
 * normally builds exactly the gas x86 amode string but if dbg_fmt is
 * on, returns a debugging non gas legal syntax string
 */
extern char *__bld_amods(char *amods, struct insn_t *ip, int32 opcode,
 struct amode_t *amp, int32 dbg_fmt, struct flowg_t *fgp)
{
 struct asl_info_t *aslp;
// SJM 09-13-13 - need IDP map at compile time to uncomment this stuff 
// size_t ndx;
 char regs[RECLEN], s1[RECLEN];

 switch (amp->amode) {
  case AM_REG:
   /* %eax */
   if (dbg_fmt)
    { reg_tostr(regs, amp, TRUE); sprintf(amods, "%s", regs); break; }

   if (amp->x86_regno > REG_NONE)
    { reg_tostr(amods, amp, FALSE); break; }

   /* DBG remove -- */
   if (amp->am_tni == -1) __misc_terr(__FILE__, __LINE__);
   /* ---- */

   /* SJM 08/17/06 - bbopt set x86 reg numbers for low explict tn's */
   /* but for debugging before reg assignment still need this */
   if (amp->am_tni <= HIGH_X86_REG)
    { 
     amp->x86_regno = amp->am_tni;
     reg_tostr(amods, amp, FALSE); 
     /* reg assign routine will set this later */
     amp->x86_regno = REG_NONE;
     break;
    }
   /* DBG remove -- */
   if (__tntab[amp->am_tni].comlab_typ == COMLAB_NONE)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   bld_comlab_tostr(amods, amp, dbg_fmt);
   break;
  case AM_IDP_ADR_OFS:
   if (dbg_fmt)
    { reg_tostr(regs, amp, TRUE); sprintf(amods, "%s", regs); break; }
   /* DBG remove -- */
   if (__tntab[amp->am_tni].comlab_typ == COMLAB_NONE)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   bld_comlab_tostr(amods, amp, dbg_fmt);
   break;
  case AM_NDXREG: 
   /* (%esi) */
   /* DBG remove -- */
   if (amp->am_tni == -1) __misc_terr(__FILE__, __LINE__);
   /* ---- */

   /* dbg format reg tostr handles memory area tag conversion */
   if (dbg_fmt)
    { reg_tostr(regs, amp, TRUE); sprintf(amods, "(%s)", regs); break; }

   if (__tntab[amp->am_tni].comlab_typ != COMLAB_NONE)
    {
     bld_comlab_tostr(amods, amp, dbg_fmt);
     break;
    }
   reg_tostr(regs, amp, FALSE);
   sprintf(amods, "(%s)", regs);
   break;
  /* AIV 03/02/09 - this is special case which is a fixed optim amode */
  case AM_NDXREG_DBL:
   sprintf(amods, "(%s,%s,2)", __regs[amp->disp], __regs[amp->x86_regno]);
   break;
  case AM_NDXREG_DISP:
   if (opcode == I_TSKRET_JMP)
    {
     reg_tostr(regs, amp, dbg_fmt);
     /* DBG remove --- */
     if (amp->disp != NLO_THDJMP_RET_ADDR_TAB)
      __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* SJM 07/17/06 - not sure why the disp is the tni not the nlo type? */ 
     __bld_nlo_lab_nam(s1, NLO_THDJMP_RET_ADDR_TAB);
     sprintf(amods, "%s(,%s,%d)", s1, regs, WRDBYTES);
    }
   else if (opcode == I_IND_JMP || opcode == I_PORT_IND_JMP)
    {
     reg_tostr(regs, amp, dbg_fmt);
#ifdef __CVC32__
     sprintf(amods, "C_%u(,%s,%d)", amp->disp, regs, WRDBYTES);
#else
     sprintf(amods, "C_%lu(,%s,%d)", amp->disp, regs, WRDBYTES);
#endif
    }
   else
    {
     /* neta_bp, etc */
     if (__tntab[amp->am_tni].comlab_typ != COMLAB_NONE)
      {
       /* SJM - 11/20/06 - need to use dbg form of reg to str so both */
       /* the mem addr and the tn number printed */
       /* dbg format reg tostr handles memory area tag conversion */
       if (dbg_fmt)
        { reg_tostr(regs, amp, TRUE); sprintf(amods, "(%s)", regs); break; }

       bld_comlab_tostr(amods, amp, dbg_fmt);
      }
     else
      {
// SJM 07-20-13 - IDP MAP NO LONGER AVAILABLE AT COMPILE TIME
//       if (__opt_debug_flg)
//        {
//         /* if using design wide idp cannot print debugging string for now */
//         if (amp->am_tni == IDP_REG && fgp != NULL)
//          {
//       /* SJM 12/04/07 - just use closest down word boundary for idp info */
//
//           ndx = amp->disp/WRDBYTES;
//           /* in idp area - know IDP REG set to base of current inst */
//#ifdef __CVC_DEBUG__
//           get_idp_map_str(s1, ip->inmdp, ndx);
//#else
//           __misc_terr(__FILE__, __LINE__);
//#endif
//           reg_tostr(regs, amp, dbg_fmt);
//           sprintf(amods, "%s(%s)", s1, regs);
//          }
//        else
//          {
//           /* -8(%ebp) */
//           reg_tostr(regs, amp, dbg_fmt);
// #ifdef __CVC32__
//           sprintf(amods, "%u(%s)", amp->disp, regs);
//#else
//           sprintf(amods, "%lu(%s)", amp->disp, regs);
// #endif
//          }
//         }
//       else
//        {
         /* -8(%ebp) or %eax */
         reg_tostr(regs, amp, dbg_fmt);
         if (amp->disp == 0)
          {
           sprintf(amods, "(%s)", regs);
          }
#ifdef __CVC32__
         else sprintf(amods, "%u(%s)", amp->disp, regs);
#else
         else sprintf(amods, "%lu(%s)", amp->disp, regs);
#endif
 //       }
      }
    }
   break;
  case AM_NONREG_OFS:
   /* SJM 10/11/06 - this amode removed before .s file asm gen */ 
   if (dbg_fmt)
    {
     /* must make work before decomposing of needs contigous a/b tmp areas */ 
     if (__tntab[amp->am_tni].child_tag_offset == 0)
      {
#ifdef __CVC32__
       sprintf(amods, "<disp=%u+spill=%d of r%0d>(%%ebp)",
        amp->disp, __tntab[amp->am_tni].spill_ebp_byt_ofs, amp->am_tni);
#else
       sprintf(amods, "<disp=%lu+spill=%d of r%0d>(%%ebp)",
        amp->disp, __tntab[amp->am_tni].spill_ebp_byt_ofs, amp->am_tni);
#endif
      }
     else
      {
#ifdef __CVC32__
       sprintf(amods,
        "<disp=%u+child=%u+spill=%d of r%0d>(%%ebp)",
        amp->disp, __tntab[amp->am_tni].child_tag_offset,
        __tntab[amp->am_tni].spill_ebp_byt_ofs, amp->am_tni);
#else
       sprintf(amods,
        "<disp=%lu+child=%lu+spill=%d of r%0d>(%%ebp)",
        amp->disp, __tntab[amp->am_tni].child_tag_offset,
        __tntab[amp->am_tni].spill_ebp_byt_ofs, amp->am_tni);
#endif
      }
    } 
   else __case_terr(__FILE__, __LINE__);
   break;
  case AM_NLO_ARRNDX:
   reg_tostr(regs, amp, dbg_fmt);
   __bld_nlo_lab_nam(s1, amp->arr_base_nlo);
   /* AIV 10/16/08 - now all tables are word aligned */
   sprintf(amods, "%s(,%s,%d)", s1, regs, WRDBYTES); 
   break;
  case AM_LABEL:
   /* AIV 07/30/10 - if dpi enter do not add _%d number - must match C */
   /* declared name */
   if (ip->is_dpi_enter)
    {
     /* DBG remove -- */
     if (amp->disp != 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
     sprintf(amods, "%s", amp->apu.labnam);
    }
   /* SJM 07/19/06 - jump to task is a supsend but needs label gen */ 
   else if (__is_jmp_insn(opcode) || opcode == I_CALL || opcode == I_TSKJMP 
    || opcode == I_FUNC_JMP)
    {
#ifdef __CVC32__
     sprintf(amods, "%s_%u", amp->apu.labnam, amp->disp);
#else
     sprintf(amods, "%s_%lu", amp->apu.labnam, amp->disp);
#endif
    }
   else if (opcode == I_LABEL || opcode == I_ENTER_LABEL)
    {
#ifdef __CVC32__
     sprintf(amods, "%s_%0u:", amp->apu.labnam, amp->disp);
#else
     sprintf(amods, "%s_%0lu:", amp->apu.labnam, amp->disp);
#endif
    }
   else if (opcode == I_DIRECTIVE || opcode == I_ADDA)
    {
     /* for new label adr add, must be contents with no offset, i.e. no $ */
     /* DBG remove -- */
     if (amp->disp != 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
     sprintf(amods, "%s", amp->apu.labnam);
    }
   else if (opcode == I_COMPLETE)
    {
     /* label here is just for debugging */
    }
   /* lots of boiler plate's take lables - but do not need to emit string */
   break;
  case AM_IMM:
   if (opcode == I_ASL_CALL)
    {
     aslp = __to_aslinfo_rec(amp->disp);
     sprintf(amods, "%s", aslp->asl_rout_nam);
    }
   else
    {
     /* $num */
     if (amp->disp == 0) sprintf(amods, "$0");
#ifdef __CVC32__
     else sprintf(amods, "$0x%x", amp->disp);
#else
     else sprintf(amods, "$0x%lx", amp->disp);
#endif
    }
   break;
  case AM_BBLK:
   /* DBG remove -- */ 
   if (!dbg_fmt) __misc_terr(__FILE__, __LINE__);
   /* --- */
   sprintf(amods, "B%0d", amp->apu.bbp->bblk_seqno); 
   break;
  case AM_NLO:
   __bld_nlo_lab_nam(amods, amp->disp);
   break;
  case AM_UNKN: case AM_NONE:
   __case_terr(__FILE__, __LINE__);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(amods);
}

/*
 * build a label name from an amode of type am mem label 
 *
 * SJM 04/04/07 - simplfied by adding new amode and removing need for
 * child ofs since now for new addr mode in the disp field already
 */
static void bld_comlab_tostr(char *amods, struct amode_t *amp, int32 dbg_fmt)
{
 int32 tni;
 struct tn_t *tnp;
 char s1[RECLEN], s2[RECLEN];
#ifndef __CVC32__
 char s3[RECLEN];
#endif
 struct tn_dup_t *tndup;

 tni = amp->am_tni;
 tnp = &(__tntab[tni]);
 /* DBG remove -- */
 if (tni < 0 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 if (tnp->comlab_typ == COMLAB_NONE) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* SJM 10/11/06 - cint's are constants where label is the number */
 if (tnp->comlab_typ == COMLAB_CINT)
  { 
   /* DBG remove -- */
   if (tnp->tn_typ != TN_VAL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   sprintf(amods, "CINT=%lx", tnp->tncu.tn_cint);
   return;
  }

 if (tnp->comlab_typ == COMLAB_CONADR)
  {
   /* SJM 04/04/07 - know only labadr ofs and ndx reg disp amodes have disps */
   if (amp->disp <= 0) sprintf(s1, "CON_%d", tnp->tncu.el_ndx); 
#ifdef __CVC32__
   else sprintf(s1, "CON_%d + %u", tnp->tncu.el_ndx, amp->disp); 
#else
   else sprintf(s1, "CON_%d + %lu", tnp->tncu.el_ndx, amp->disp); 
#endif

   /* can be a non-address for real values */
   if (amp->amode == AM_REG || amp->amode == AM_IDP_ADR_OFS)
    {
     sprintf(amods, "$%s", s1);
    }
   else if (amp->amode == AM_NDXREG || amp->amode == AM_NDXREG_DISP)
    strcpy(amods, s1);
   else __case_terr(__FILE__, __LINE__);

   /* AIV 11/30/06 - if constant never used in assemble don't dump to memory */
   /* if not debug mode record as used in lowered assembly */
   /* most constants get lowered to literal values */

   /* SJM 12/26/06 - keep flag in tn and initialize for each flow graph */
   /* before emitting asm to .s file or pipe much simpler */
   /* AIV 01/21/07 - need to do the search to find the tmp placed in tree */
   /* sometimes index is different because of width mismatch etc */
   tndup = __find_add_dup_tn(__contab_dup_tn_tree, tnp->tncu.el_ndx);
   if (!dbg_fmt) __tntab[tndup->tni].used_in_asm = TRUE;
   return;
  }

 /* DBG remove -- */
 if (tnp->tn_typ != TN_ADR) __misc_terr(__FILE__, __LINE__);
 /* --- */
#ifdef __CVC32__
 __gen_comm_lab_amods(s2, tnp);
#else
 /* AIV 08/28/09 - if marked as special flag - need to add a $ */
 /* extra level of indirection has been handled in v_bbopt - extra moves */
 if (amp->is_large_label)
  {
   /* DBG remove -- */
   if (!__cvc_use_large_model) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   
   /* just add a $ to the front */
   __gen_comm_lab_amods(s3, tnp);
   strcpy(s2, "$"); 
   strcat(s2, s3); 
  }
 else __gen_comm_lab_amods(s2, tnp);
#endif

 /* SJM 10/23/06 - the nl object stmt types that have pointers to them */ 
 /* in the comm area such as stmt or gate never have $ in front */
 if (__is_nlptr_comlab(tnp->comlab_typ))
  {
   /* DBUG remove -- */
   if (amp->disp > 0) __misc_terr(__FILE__, __LINE__);
   if (amp->amode == AM_NDXREG || amp->amode == AM_NDXREG_DISP)
    __misc_terr(__FILE__, __LINE__); 
   /* --- */
   strcpy(amods, s2);
   return;
  }

 if (amp->disp <= 0) strcpy(s1, s2); 
 else
  {
#ifdef __CVC32__
   sprintf(s1, "%s + %u", s2, amp->disp);
#else
   sprintf(s1, "%s + %lu", s2, amp->disp);
#endif
  }

 if (amp->amode == AM_REG || amp->amode == AM_IDP_ADR_OFS)
  {
   sprintf(amods, "$%s", s1);
  }
 /* SJM 08/23/06 - also the ndx disp amode here */
 else if (amp->amode == AM_NDXREG || amp->amode == AM_NDXREG_DISP)
  {
#ifdef __CVC32__
   strcpy(amods, s1);
#else
   /* AIV 11/03/09 - this should use global offset %rip */
   /* AIV 11/11/09 - if large model skip %rip offset */
   if (__cvc_use_large_model) strcpy(amods, s1);
   else sprintf(amods, "%s(%%rip)", s1);
#endif
  }
 else __case_terr(__FILE__, __LINE__);
}

/*
 * return T for the com label types that are net list ptrs with no $ ever
 * can only be called for non NLO com labs
 */
extern int32 __is_nlptr_comlab(int32 comlabtyp)
{
 switch (comlabtyp) {
  case COMLAB_STMT:
  case COMLAB_XPR:
  case COMLAB_GREF:
  case COMLAB_GATE:
  case COMLAB_NETADR:
  case COMLAB_CA:
  case COMLAB_NPPADR:
  case COMLAB_DCEADR:
  case COMLAB_TASK_ADR:
  case COMLAB_L_UDPADR:
  case COMLAB_E_UDPADR:
  case COMLAB_TCHK:
   return(TRUE);
  case COMLAB_NONE: __case_terr(__FILE__, __LINE__);
  default: break;
 }
 return(FALSE);
}

/*
 * get the RT .so label name corresponding to a NLO object 
 */
extern char *__bld_nlo_lab_nam(char *s, int32 nlotyp)
{
 /* AIV 11/17/08 - 64-bit uses __global(%rip) offset for better code */
 /* only for non-indexed (not tables) */
 switch (nlotyp) {
  case NLO_NCHGED_I1:
   sprintf(s, "__nchged_i1%s", GBL_OFS_STR);
   break;
  case NLO_NCHGED_I2:
   sprintf(s, "__nchged_i2%s", GBL_OFS_STR);
   break;
  case NLO_DELAYED_MIPD:
   sprintf(s, "__nchged_delayed_mipd%s", GBL_OFS_STR);
   break;
  case NLO_OLDGVAL:
   sprintf(s, "__old_gateval%s", GBL_OFS_STR);
   break;
  case NLO_NEWGVAL:
   sprintf(s, "__new_gateval%s", GBL_OFS_STR);
   break;
  case NLO_NEWINPUTVAL:
   sprintf(s, "__new_inputval%s", GBL_OFS_STR); 
   break;
  case NLO_CURTHD:
   sprintf(s, "__cur_thd%s", GBL_OFS_STR); 
   break;
  case NLO_MASKTAB:
   strcpy(s, "__masktab");
   break;
  case NLO_EPAIR_TAB:
   strcpy(s, "__asl_epair_tab");
   break;
  case NLO_EPAIR_POS_TAB:
   strcpy(s, "__epair_pos_tab");
   break;
  case NLO_EPAIR_NEG_TAB:
   strcpy(s, "__epair_neg_tab");
   break;
  case NLO_EPSILON:
   sprintf(s, "EPSILON%s", GBL_OFS_STR);
   break;
  case NLO_SLOTEND_ACTION:
   sprintf(s, "__slotend_action%s", GBL_OFS_STR);
   break;
  case NLO_STMT_SUSPEND:
   sprintf(s, "__stmt_suspend%s", GBL_OFS_STR);
   break;
  case NLO_THDJMP_RET_ADDR_TAB:
   strcpy(s, "__thdjmp_ret_addr_tab");
   break;
  case NLO_STREN_MAP_TAB:
   strcpy(s, "__asl_stren_map_tab");
   break;
  case NLO_DBGSTR:
   strcpy(s, "$.STR");
   break;
  case NLO_IDP:
   sprintf(s, "__idp%s", GBL_OFS_STR);
   break;
  case NLO_CUR_TEVP:
   sprintf(s, "__cur_tevp%s", GBL_OFS_STR);
   break;
  case NLO_GBITREDAND:
   strcpy(s, "__redand");
   break;
  case NLO_GNAND:
   strcpy(s, "__nand");
   break;
  case NLO_GBITREDOR: 
   strcpy(s, "__redor");
   break;
  case NLO_GNOR:
   strcpy(s, "__nor");
   break;
  case NLO_GBITREDXOR: 
   strcpy(s, "__redxor");
   break;
  case NLO_SBO_BITREDAND:
   strcpy(s, "__bitand_svals");
   break;
  case NLO_GREDXNOR:
   strcpy(s, "__redxnor");
   break;
  case NLO_ORM_2_0:
   strcpy(s, "__gate_ormask_2_0");
   break;
  case NLO_ORM_2_1:
   strcpy(s, "__gate_ormask_2_1");
   break;
  case NLO_ORM_2_2:
   strcpy(s, "__gate_ormask_2_2");
   break;
  case NLO_ORM_2_3:
   strcpy(s, "__gate_ormask_2_3");
   break;
  case NLO_ORM_3_0:
   strcpy(s, "__gate_ormask_3_0");
   break;
  case NLO_ORM_3_1:
   strcpy(s, "__gate_ormask_3_1");
   break;
  case NLO_ORM_3_2:
   strcpy(s, "__gate_ormask_3_2");
   break;
  case NLO_ORM_3_3:
   strcpy(s, "__gate_ormask_3_3");
   break;
  case NLO_ORM_4_0:
   strcpy(s, "__gate_ormask_4_0");
   break;
  case NLO_ORM_4_1:
   strcpy(s, "__gate_ormask_4_1");
   break;
  case NLO_ORM_4_2:
   strcpy(s, "__gate_ormask_4_2");
   break;
  case NLO_ORM_4_3:
   strcpy(s, "__gate_ormask_4_3");
   break;
  case NLO_GBUFVAL:
   strcpy(s, "__gbuf");
   break;
  case NLO_GNOTVAL:
   strcpy(s, "__gnot");
   break;
  case NLO_BF0_STRVAL:
   strcpy(s, "__bufif0_strval_tab");
   break;
  case NLO_BF0_STRONGX:
   strcpy(s, "__bufif0_strongx_tab");
   break;
  case NLO_BF0_HIZ:
   strcpy(s, "__bufif0_hiz_tab");
   break;
  case NLO_BF0_PULL0:
   strcpy(s, "__bufif0_pull0_tab");
   break;
  case NLO_BF0_PULL1:
   strcpy(s, "__bufif0_pull1_tab");
   break;
  case NLO_BF0_SUPPLY0:
   strcpy(s, "__bufif0_supply0_tab");
   break;
  case NLO_BF0_SUPPLY1:
   strcpy(s, "__bufif0_supply1_tab");
   break;
  case NLO_BF1_STRVAL:
   strcpy(s, "__bufif1_strval_tab");
   break;
  case NLO_BF1_STRONGX:
   strcpy(s, "__bufif1_strongx_tab");
   break;
  case NLO_BF1_HIZ:
   strcpy(s, "__bufif1_hiz_tab");
   break;
  case NLO_BF1_PULL0:
   strcpy(s, "__bufif1_pull0_tab");
   break;
  case NLO_BF1_PULL1:
   strcpy(s, "__bufif1_pull1_tab");
   break;
  case NLO_BF1_SUPPLY0:
   strcpy(s, "__bufif1_supply0_tab");
   break;
  case NLO_BF1_SUPPLY1:
   strcpy(s, "__bufif1_supply1_tab");
   break;
  /* notif tables */
  case NLO_NF0_STRVAL:
   strcpy(s, "__notif0_strval_tab");
   break;
  case NLO_NF0_STRONGX:
   strcpy(s, "__notif0_strongx_tab");
   break;
  case NLO_NF0_HIZ:
   strcpy(s, "__notif0_hiz_tab");
   break;
  case NLO_NF0_PULL0:
   strcpy(s, "__notif0_pull0_tab");
   break;
  case NLO_NF0_PULL1:
   strcpy(s, "__notif0_pull1_tab");
   break;
  case NLO_NF0_SUPPLY0:
   strcpy(s, "__notif0_supply0_tab");
   break;
  case NLO_NF0_SUPPLY1:
   strcpy(s, "__notif0_supply1_tab");
   break;
  case NLO_NF1_STRVAL:
   strcpy(s, "__notif1_strval_tab");
   break;
  case NLO_NF1_STRONGX:
   strcpy(s, "__notif1_strongx_tab");
   break;
  case NLO_NF1_HIZ:
   strcpy(s, "__noif1_hiz_tab");
   break;
  case NLO_NF1_PULL0:
   strcpy(s, "__notif1_pull0_tab");
   break;
  case NLO_NF1_PULL1:
   strcpy(s, "__notif1_pull1_tab");
   break;
  case NLO_NF1_SUPPLY0:
   strcpy(s, "__notif1_supply0_tab");
   break;
  case NLO_NF1_SUPPLY1:
   strcpy(s, "__notif1_supply1_tab");
   break;
  case NLO_NCHG_FUTEND:
   sprintf(s, "__nchg_futend%s", GBL_OFS_STR);
   break;
  case NLO_NCHG_FUTHDR:
   sprintf(s, "__nchg_futhdr%s", GBL_OFS_STR);
   break;
  case NLO_NEXT_NCHGLP:
   sprintf(s, "__next_nchglp%s", GBL_OFS_STR);
   break;
  case NLO_UDP_UVALTAB:
   strcpy(s, "__asl_to_uvaltab");
   break;
  case NLO_UDP_NOZTAB:
   strcpy(s, "__asl_to_noztab");
   break;
  case NLO_SIMTIME:
   sprintf(s, "__simtime%s", GBL_OFS_STR);
   break;
  case NLO_PDMINDEL_ADR:
   sprintf(s, "$__pdmindel%s", GBL_OFS_STR);
   break;
  case NLO_PDMINDEL:
   sprintf(s, "__pdmindel%s", GBL_OFS_STR);
   break;
  case NLO_P0_TE_HDRP:
   sprintf(s, "__p0_te_hdrp%s", GBL_OFS_STR);
   break;
  case NLO_P0_TE_ENDP:
   sprintf(s, "__p0_te_endp%s", GBL_OFS_STR);
   break;
  case NLO_SBO_P1:
   strcpy(s, "__p1_svals");
   break;
  case NLO_SBO_P2:
   strcpy(s, "__p2_svals");
   break;
  case NLO_SBO_P3:
   strcpy(s, "__p3_svals");
   break;
  case NLO_SBO_P4:
   strcpy(s, "__p4_svals");
   break;
  case NLO_SBO_TIMES:
   strcpy(s, "__times_svals");
   break;
  case NLO_SBO_DIV:
   strcpy(s, "__div_svals");
   break;
  case NLO_SBO_MOD:
   strcpy(s, "__mod_svals");
   break;
  case NLO_SBO_RELGT:
   strcpy(s, "__relgt_svals");
   break;
  case NLO_SBO_RELLE:
   strcpy(s, "__relle_svals");
   break;
  case NLO_SBO_RELLT:
   strcpy(s, "__rellt_svals");
   break;
  case NLO_SBO_RELCEQ:
   strcpy(s, "__relceq_svals");
   break;
  case NLO_SBO_RELCNEQ:
   strcpy(s, "__relcneq_svals");
   break;
#ifdef __XPROP__
  case NLO_SBO_X_BITOR:
   strcpy(s, "__bitor_x_svals");
   break;
  case NLO_POPCOUNT_BYTE:
   strcpy(s, "__asl_popcount_tab");
   break;
  case NLO_XEDGE_SET_POS_TAB:
   strcpy(s, "__asl_xedge_set_pos_tab");
   break;
  case NLO_XEDGE_SET_NEG_TAB:
   strcpy(s, "__asl_xedge_set_neg_tab");
   break;
  case NLO_XEDGE_SET_TAB:
   strcpy(s, "__asl_xedge_set_tab");
   break;
  case NLO_IS_XEDGE_TAB:
   strcpy(s, "__asl_is_xedge_tab");
   break;
#endif
  case NLO_SBO_SHIFT:
   strcpy(s, "__shift_svals");
   break;
  case NLO_UN_P1:
   strcpy(s, "__un_p1_svals");
   break;
  case NLO_UN_P2:
   strcpy(s, "__un_p2_svals");
   break;
  case NLO_QCOL_COMB:
   strcpy(s, "__qcol_comb_svals");
   break;
  case NLO_SBO_NAND:
   strcpy(s, "__nand_svals");
   break;
  case NLO_SBO_NOR:
   strcpy(s, "__nor_svals");
   break;
  case NLO_G3_BITREDAND:
   strcpy(s, "__and_g3");
   break;
  case NLO_G3_NAND:
   strcpy(s, "__nand_g3");
   break;
  case NLO_G3_BITREDOR:
   strcpy(s, "__or_g3");
   break;
  case NLO_G3_NOR: 
   strcpy(s, "__nor_g3");
   break;
  case NLO_G3_BITREDXOR:
   strcpy(s, "__xor_g3");
   break;
  case NLO_G3_REDXNOR:
   strcpy(s, "__xnor_g3");
   break;
  case NLO_G4_BITREDAND:
   strcpy(s, "__and_g4");
   break;
  case NLO_G4_NAND:
   strcpy(s, "__nand_g4");
   break;
  case NLO_G4_BITREDOR:
   strcpy(s, "__or_g4");
   break;
  case NLO_G4_NOR: 
   strcpy(s, "__nor_g4");
   break;
  case NLO_G4_BITREDXOR:
   strcpy(s, "__xor_g4");
   break;
  case NLO_G4_REDXNOR:
   strcpy(s, "__xnor_g4");
   break;
  case NLO_NB_TE_ENDP:
   strcpy(s, "__nb_te_endp");
   break;
  case NLO_SCP_TSKP:
   strcpy(s, "__scope_tskp");
   break;
  case NLO_SAVE_SCP_TSKP:
   strcpy(s, "__save_scope_tskp");
   break;
  case NLO_4STATE_TO2:
   strcpy(s, "__asl_4to2");
   break;
  case NLO_EVENT_COVER:
   strcpy(s, "__event_covered");
   break;
  case NLO_STMT_COVER:
   strcpy(s, "__stmt_covered");
   break;
#ifdef __CVC32__
  case NLO_SIMTIME_HIGH:
   strcpy(s, "__simtime+4");
   break;
  case NLO_PDMINDEL_HIGH:
   strcpy(s, "__pdmindel+4");
   break;
#endif
  default:
   __case_terr(__FILE__, __LINE__);
   break;
 }
 return(s);
}

/*
 * build an amods string from a a know comm lab tmp name (tn)
 *
 * SJM 10/11/06 - this routine now build a string with the adradd result
 * child offset part of the string - caller should just use
 */
extern char *__gen_comm_lab_amods(char *s, struct tn_t *tnp)
{
 struct mod_t *mdp;
 struct net_t *np;
 struct dcevnt_t *dcep;
 int32 ndx;
 char s2[RECLEN];

 switch (tnp->comlab_typ) {
  case COMLAB_STMT:
   /* stmt el ndx number of smtm in current module goes into comm area */
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "ST_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_XPR:
   /* xpr el ndx in current (inst mod) goes in comm area */
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "XPR_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_GREF:
   /* AIV 08/03/06 - the mod it is from is cast and stored in el2_ndx */
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "GRP_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_GATE:
   /* AIV 12/22/06 - the mod it is from is cast and stored in el2_ndx */
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "G_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_CA:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "CA_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_NETADR:
   mdp = tnp->tnsyrecp->in_mdp;
   np = (struct net_t *) tnp->tnsyrecp->tfm_syp;
   /* the addr for this net_t net list data struct is in the comm area */
   __bldchk_var_comm_ref(s2, np, mdp, NULL);
   sprintf(s, "%s_np_%d", s2, tnp->tncu.el_ndx);
   break;
  case COMLAB_CONADR:
   /* the index is the global contab index but the constant including */
   /* possibly IS constants goes into this module's comm area */ 
   sprintf(s, "CON_%d", tnp->tncu.el_ndx);
   break;
  case COMLAB_NPPADR:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "NPPA_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_DCEADR:
   mdp = tnp->tnsyrecp->in_mdp;
   //AIV FIXME - if leaving this make this a union
   dcep = (struct dcevnt_t *) tnp->tnsyrecp->tfm_syp;
   np = dcep->dce_np;
   ndx = np - mdp->mnets;
   sprintf(s, "DCEA_%d_%d_%d", mdp->m_idnum, ndx, tnp->tncu.el_ndx);
   break;
  case COMLAB_PROC_ENTER:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "ST_ENT_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_PROC_NB_ENTER:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "ST_ENT_NB_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_CONTA_ENTER:
   sprintf(s, "CAP_%d", tnp->tncu.el_ndx);
   break;
  case COMLAB_GATE_ENTER:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "GATEDA_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_GATE_CHANGE_ENTER:
   strcpy(s, "GATECHG_EV");
   break;
  case COMLAB_GATE_ACC_CHANGE_ENTER:
   strcpy(s, "GATECHG_ACC_EV");
   break;
  case COMLAB_IDP:
   strcpy(s, "__idp");
   break;
  case COMLAB_PNCHG:
   sprintf(s, "__nchgdat_%d", tnp->tncu.el_ndx);
   break;
  case COMLAB_MIPD_ENTER:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "MIPD_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_PROCESS_WIRE_ENTER:
   sprintf(s, "WIRE_EV_%d", tnp->tncu.el_ndx);
   break;
  case COMLAB_TEVP:
   sprintf(s, "__tevdat_%d", tnp->tncu.el_ndx);
   break;
  case COMLAB_IDPDAT:
   sprintf(s, "__idpdat_%d", tnp->tncu.el_ndx);
   break;
  case COMLAB_TASK_ADR:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "TSKP_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_L_UDPADR:
   sprintf(s, "__UDPL_%d", tnp->tncu.el_ndx);
   break;
  case COMLAB_E_UDPADR:
   sprintf(s, "__UDPE_%d", tnp->tncu.el_ndx);
   break;
  case COMLAB_TCHK:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "__TCHK_TCHG_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  case COMLAB_DEL:
   mdp = tnp->tnsyrecp->in_mdp;
   sprintf(s, "__PTHDEL_%d_%d", mdp->m_idnum, tnp->tncu.el_ndx);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * get a x86 register string 
 */
static char *reg_tostr(char *s1, struct amode_t *amp, int32 dbg_fmt)
{
 int32 regno;

 if (dbg_fmt) { dbg_reg_tostr(s1, amp); return(s1); }

 regno = amp->x86_regno;
 /* DBG remove -- */
 if (regno <= REG_NONE || regno > HIGH_X86_REG) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 strcpy(s1, __regs[regno]);
 return(s1);
}

/*
 * get a register debug string - know reg spilled (not in x86 reg) to get here
 */
static char *dbg_reg_tostr(char *s1, struct amode_t *amp)
{
 int32 tni; 
 size_t ebp_ofs;
 char tags[RECLEN];

 tni = amp->am_tni;
 /* DBG remove -- */
 if (tni < 0 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 
 /* if has a tag value add the string to the tag as well */
 if (__tntab[tni].comlab_typ != COMLAB_NONE)
  {
   bld_comlab_tostr(tags, amp, TRUE);
   sprintf(s1, "r%d [%s]", tni, tags);
   return(s1);
  }
 
 if (tni < HIGH_X86_REG) strcpy(s1, __regs[tni]);
 else
  {
   if (__tntab[tni].tn_assigned)
    {
     sprintf(s1, "r%d [REG=%s]", tni, __regs[__tntab[tni].x86_regno]);
    }
   else if (__tntab[tni].tn_spilled)
    {
     ebp_ofs =  __calc_ebp_spill_offset(tni, 0);
     if (__tntab[tni].tag_parent_tni != -1)
      {
#ifdef __CVC32__
       sprintf(s1, "r%d [SPILL=%d(%%ebp) OF r%d]", tni, ebp_ofs, 
        __tntab[tni].tag_parent_tni);
#else
       sprintf(s1, "r%d [SPILL=%ld(%%ebp) OF r%d]", tni, ebp_ofs, 
        __tntab[tni].tag_parent_tni);
#endif
      }
#ifdef __CVC32__
     else sprintf(s1, "r%d [SPILL=%d(%%ebp)]", tni, ebp_ofs);
#else
     else sprintf(s1, "r%d [SPILL=%ld(%%ebp)]", tni, ebp_ofs);
#endif
    }
   else
    {
     if (__tntab[tni].tag_parent_tni != -1)
      {
       sprintf(s1, "r%d [CHILD OF r%d]", tni, __tntab[tni].tag_parent_tni);
      }
     else sprintf(s1, "r%d [UNSET]", tni);
    }
  }
 return(s1);
}

/*
 * return T if need actual x86 insn name or just string
 */
static int32 need_inam(int32 opcod)
{
 switch(opcod) {
  case I_LABEL:
  case I_ENTER_LABEL:
  case I_DIRECTIVE:
   return(FALSE);
 }
 return(TRUE);
}

/*
 * emit the contab area for one module at the end of the module's one .s file
 * SJM 04/11/08 
 */
static void emit_1mod_constants(FILE *fp, struct mod_t *mdp)
{
 int32 avli, j;
 int32 ctndx, wid, tni, siz_avltab;
 struct avlnode_t *nodp, **con_avltab;
 struct tn_dup_t *tndup;
 char s1[RECLEN];

 con_avltab = __linearize_avl_tree(__contab_dup_tn_tree, &(siz_avltab));

 if (__show_asm && siz_avltab > 0)
  {
   emit_one_insn(fp, "\n# *** START OF PER MODULE CONST DEFINES\n");
  }

 /* SJM 04/08/08 - need block tracing even if no consts */
 /* AIV 12/12/06 - print the enter block message for debugging */
 if (__opt_block_trace)
  {
   emit_one_insn(fp,
    "\t.section\t.rodata\n.STR:\n\t.asciz \"ENTERING BLOCK %%d\\n\"\n");
  }

 if (siz_avltab <= 0) return;

 emit_one_insn(fp, "\t.section\t.rodata\n");
 for (avli = 0; avli < siz_avltab; avli++)
  {
   nodp = (struct avlnode_t *) con_avltab[avli];
   tndup = (struct tn_dup_t *) nodp->valp;

   tni = tndup->tni;

   /* AIV 11/30/06 - if constant never used in assemble don't dump to memory */
   /* SJM 12/26/06 - can just put this flag in the tmp name */
   if (!__tntab[tni].used_in_asm) continue;

   /* notice ctab ndx in the tmp name and in the tn dup record */
   ctndx = tndup->nlo_ndx;
   sprintf(s1, "CON_%d", ctndx); 
   emit_one_insn(fp, ".local %s\n", s1);
   emit_one_insn(fp, "\t.align %d\n", WRDBYTES);
   wid = 2*wlen_(__tntab[tni].tnwid);
   emit_one_insn(fp, "%s:\n", s1);
   if (__tntab[tni].conadr_is_is)
    {
     for (j = ctndx; j < ctndx + 2*(mdp->flatinum*wid); j++)
      {
       emit_one_insn(fp, "\t.%s\t%ld\n", AW_STR, __contab[j]);
      }
    }
   else
    {
     for (j = ctndx; j < ctndx + wid; j++)
      {
       emit_one_insn(fp, "\t.%s\t%ld\n", AW_STR, __contab[j]);
      }
    }
  }
 emit_one_insn(fp, "\t.section\t.bss\n");

 /* SJM 12/26/06 - caller must now free malloced linearized avl tree (set) */
 __my_free(con_avltab, siz_avltab*sizeof(struct avlnode_t *));
}

/* 
 * ROUTINES TO GEN (EMIT) DESIGN WIDE .S FILE INCLUDING ALL PMD AND IDP STORAGE
 */

/*
 * gen the one design wide .s file
 *
 * this is run time routines after whatever incremental compilation done
 * (no incremental compilation for now)
 */
extern void __gen_dsgn_dat_asm_file(void)
{
 FILE *fp;
 char s1[RECLEN], comm_fnam[RECLEN], s2[RECLEN];
 struct mod_t *mdp;

 /* use first file for comm fnam info */
 sprintf(comm_fnam, "%s.s", __bld_asm_comm_fnam_stem(s1));
 /* always over write for now */
 if ((fp = __my_fopen(comm_fnam, "w")) == NULL)
  {
   __pv_err(2904, "unable to open variable common storage asm output file %s",  
    comm_fnam);
   return;
  }
 emit_dsgn_wide_asm_file(fp, comm_fnam);
 __my_fclose(fp);

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   sprintf(s2, "comm_M%d_nt.s", mdp->m_idnum);
   if ((fp = __my_fopen(s2, "w")) == NULL)
    {
     __pv_err(2904, "unable to open variable common storage asm output file %s",  
       s2);
     return;
    }
   emit_one_mod_init_asm_file(fp, s2, mdp, (mdp == __modhdr));
   __my_fclose(fp);
  }
}


/*
 * same as above except piping to obj directory instead of creating files
 */
extern void __pipe_dsgn_dat_asm_file(void)
{
 FILE *pp;
 char as_cmd[RECLEN];
 char *init_cp;
 struct mod_t *mdp;

#ifdef __CVC32__
 sprintf(as_cmd, "as --32 -o %s", __comm_file_name);
#else
 sprintf(as_cmd, "as -o %s", __comm_file_name);
#endif
 sprintf(__asm_file_name, "%s", __comm_file_name);

 if ((pp = do_popen(as_cmd, "w")) == NULL)
  {
   __pv_err(2904, "unable to open pipe for asm comm storage");
   return;
  }
 emit_dsgn_wide_asm_file(pp, __comm_file_name);
 do_pclose(pp);



 __num_print_asm_insn = 0;
 /* each module now has a its own initilization file - however if these are */
 /* small - they will be combined into one file or partitioned across modules */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* first mod or reset */
   init_cp = __comm_nt_file_names[mdp->m_idnum];
   if (__num_print_asm_insn == 0) 
    {
     mdp->m_using_init_file = TRUE;
     /* AIV 08/05/09 - init file should be seperate file */
     sprintf(__asm_file_name, "%s", init_cp);
#ifdef __CVC32__
     sprintf(as_cmd, "as --32 -o %s", init_cp);
#else
     sprintf(as_cmd, "as -o %s", init_cp);
#endif

     if ((pp = do_popen(as_cmd, "w")) == NULL)
      {
       __pv_err(2904, "unable to open pipe for asm comm storage");
       return;
      }
    }
   else
    {
     /* if not using unlink the tmp made name */
     unlink(init_cp);   
    }
   emit_one_mod_init_asm_file(pp, init_cp, mdp, (mdp == __modhdr));

   /* if created a large amount of insns start new init file */
   if (__num_print_asm_insn > PARTITION_MAX_INSN_COUNT)
    {
     do_pclose(pp);
     __num_print_asm_insn = 0;
     pp = NULL;
    }
  }
 /* may have to close the last one */
 if (pp != NULL) do_pclose(pp);
}

/*
 * build stem (without the .s/.o/.c) name of asm comm (.bss) var define file
 * and also design wide .c file 
 *
 * use first file name in design
 */
extern char *__bld_asm_comm_fnam_stem(char *s)
{
 char mnam[RECLEN];

 __bld_asm_fnam_stem(mnam, __modhdr);
 strcpy(s, "comm_");
 strcat(s, mnam);
 return(s);
}

/*
 * write design wide initialized data to comm_ file
 *
 * SJM 04/21/08 - new scheme lays out module wide design data in specific
 * pattern in comm .s asm file (will change to c file) but for now
 * c language file is just used after linking (either static or dynamic dlsym)
 * to copy init data into part of design wide comm area
 *
 * __DES_RT_BASE:
 * __MOD_%d_RT_BASE:
 * # the per design index - i.e. do not need mod index too for now
 * __tevdat_0:
 * ... <fill tev times number of insts size with 0>
 * __tevdat_1:
 * ... <fill tev times number of insts size with 0>
 *
 *   <the mod's struct tev_t fixed known at compile time records>
 *   <flatinum identical copies except for one ptr into idp area>
 * <labeled (current COMLAB_ records)
 * <nchg area - what is it>
 *
 * __idpdat_0:
 * ... <fill mod's idp size with 0>
 * .idpdat_<last>:
 * ... <fill mod's idp size with 0>
 *
 * <fixed boiler plate area in .s file - easy just to write each time>
 */
static void emit_dsgn_wide_asm_file(FILE *fp, char *comm_fnam)
{
 struct mod_t *mdp;

 emit_one_insn(fp, "\t.file \"%s\"\n", comm_fnam);

 /* then at bottom of file is the fixed boiler plate area */
 /* SJM 04/21/08 - could almost be .s file shipped with CVC */
 emit_fixed_text_boiler_plate(fp);



 emit_one_insn(fp, "\t.section\t.data\n");
 emit_one_insn(fp, "\t.align %d\n", WRDBYTES);

 /* emit the one nchglst fence - saves some nil checks */
 emit_last_nchglst_fence(fp);

 /* need base of design wide entire RT data area PMD and IDP for all mods */ 
 /* must be first PMD for each mod then contiguous just after IDP per mod */ 
 //emit_one_insn(fp, ".globl %s\n", "__DSGN_BASE_LABEL");

 /* then add the per module (not per inst) storage areas */
 /* SJM 04/08/08 - now all per mod date here in design wide file */ 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* emit all of a mod's fixed nchglst elements */
   emit_1mod_nchg_glbs(fp, mdp);

   /* SJM 04/21/08 - no longer using has static addrs for non loadlib or dbg */
   /* so always emit this file - overhead removed when c file done */
   /* emit the asm commlabs */ 
   emit_1mod_commlabs(fp, mdp, TRUE);
  }

 /* SJM 07/11/08 - emit the design wide udp table .glob labels */ 
 /* allows direct access of the udp tables */ 
 emit_dsgn_udptab_adr_labs(fp);

 /* SJM 04/08/08 - now the boiler plater goes at bottom of file */
 emit_comm_task_jmptable(fp);

 /* create special case reals */
 /* just always create these constant whether they are need or not */
 /* AIV 09/01/05 - need special constant epsilon double */
 emit_one_insn(fp, "\t.section\t.rodata\n");
 emit_one_insn(fp, ".globl EPSILON\n");
 emit_one_insn(fp, "\t.align 8\n");
 emit_one_insn(fp, "EPSILON:\t.double\t%g\n", EPSILON);

#ifndef __CVC32__
 /* need this special value for real operation */
 /* real a = -b; */
 emit_one_insn(fp, "\t.section\t.rodata\n");
 emit_one_insn(fp, ".globl %s\n", "REALNEG");
 emit_one_insn(fp, "\t.align 16\n");
 emit_one_insn(fp, "REALNEG:\n");
 emit_one_insn(fp, "\t.long\t0\n");
 emit_one_insn(fp, "\t.long\t-2147483648\n");
 emit_one_insn(fp, "\t.long\t0\n");
 emit_one_insn(fp, "\t.long\t0\n");
 
 /* absolute value real */
 emit_one_insn(fp, "\t.section\t.rodata\n");
 emit_one_insn(fp, ".globl %s\n", "REALABS");
 emit_one_insn(fp, "\t.align 16\n");
 emit_one_insn(fp, "REALABS:\n");
 emit_one_insn(fp, "\t.long\t4294967295\n");
 emit_one_insn(fp, "\t.long\t2147483647\n");
 emit_one_insn(fp, "\t.long\t0\n");
 emit_one_insn(fp, "\t.long\t0\n");
#endif

}

/*
 * create info for the comm_M_0_nt.s file
 *
 * contains the init_M* routines and other init setup code
 *
 */
static void emit_one_mod_init_asm_file(FILE *fp, char *comm_fnam,
 struct mod_t *mdp, int32 is_first_mod)
{
 int32 nmods;

 emit_one_insn(fp, "\t.file \"%s\"\n", comm_fnam);
 /* AIV 04/13/12 - this needs to include the .text directive */
 /* this was a problem for older 64-bit version of 'as' */ 
 /* this was moved around with the new per module comm_ files */
 emit_one_insn(fp, "\t.text\n");

 if (__show_asm)
  {
   __my_fprintf(fp, "\n#================================================\n");
   __my_fprintf(fp, "# ASM FUNCS TO INIT DESIGN WIDE CVC RECORDS\n");
   __my_fprintf(fp, "#================================================\n");
  } 

 ll_awr_1mod_init_func_def(fp, mdp);

 if (is_first_mod)
  {
   ll_awr_allmods_init_func_def(fp);
   /* AIV 03/07/07 - save the design size to match if loaded with +so_lib */
   /* later now memory usage should match if design source/options the same */
   emit_one_insn(fp, ".globl __dsnmem\n");
   emit_one_insn(fp, "\t.align %d\n", WRDBYTES);
   emit_one_insn(fp, "__dsnmem:\n");
   emit_one_insn(fp, "\t.%s %ld\n", AW_STR, __mem_cvc_use);

   emit_executable_args_str(fp); 
  }

 emit_ialst_enter_points_array(fp, mdp);

 /* AIV 11/18/08 - these are set to null since binary doesn't need */
 /* this large data area */
 if (is_first_mod)
  {
   emit_one_insn(fp, ".globl  __cvclib_str\n");
   emit_one_insn(fp, "\t.section	.rodata\n");
   emit_one_insn(fp, "\t.align 4\n");
   emit_one_insn(fp, "__cvclib_str:\n");
   emit_one_insn(fp, "\t.long    0\n");
  
   emit_one_insn(fp, ".globl  __cvclib_size\n");
   emit_one_insn(fp, "\t.section	.rodata\n");
   emit_one_insn(fp, "\t.align 4\n");
   emit_one_insn(fp, "__cvclib_size:\n");
   emit_one_insn(fp, "\t.long    0\n");
  
   emit_one_insn(fp, ".globl  __exe_main_str\n");
   emit_one_insn(fp, "\t.section	.rodata\n");
   emit_one_insn(fp, "\t.align 4\n");
   emit_one_insn(fp, "__exe_main_str:\n");
   emit_one_insn(fp, "\t.long    0\n");
  
   emit_one_insn(fp, ".globl  __exe_main_size\n");
   emit_one_insn(fp, "\t.section	.rodata\n");
   emit_one_insn(fp, "\t.align 4\n");
   emit_one_insn(fp, "__exe_main_size:\n");
   emit_one_insn(fp, "\t.long    0\n");
  }
  
 /* AIV 07/25/09 - if running the executable cvcsim - just get the */
 /* fixed __idpdat address - previously was allocing and then */
 /* freeing later - this is much better because there isn't a need */
 /* for two copies of the idp area and a need to memcpy/free the other */

 /* get the mod count */
 if (is_first_mod)
  {
   nmods = 0;
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     nmods++;
    }
  
   /* this is just a array of the __idpdat_ addresses */
   emit_one_insn(fp, ".globl  __idpdat_areas\n");
   emit_one_insn(fp, "\t.section	.rodata\n");
   emit_one_insn(fp, "\t.align %d\n", WRDBYTES);
  
     /* dump the address for each mod */
   emit_one_insn(fp, "__idpdat_areas:\n");
   nmods = 0;
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt, nmods++)
    {
#ifdef __CVC32__
     emit_one_insn(fp, "\t.long    __idpdat_%d\n", mdp->m_idnum);
#else
     emit_one_insn(fp, "\t.quad    __idpdat_%d\n", mdp->m_idnum);
#endif
     /* assuming m_idnum - is in order */
     /* DBG remove -- */
     if (nmods != mdp->m_idnum) __misc_terr(__FILE__, __LINE__);
     /* ---- */
    }
 }
}
 
/*
 * emit a string array to replace the main's 
 * argc/argv - just make a string array of the opt list
 */
static void emit_executable_args_str(FILE *fp)
{
 int32 i, j, k, len, nlen;
 char c;
 char *cp;
 struct optlst_t *olp;
 char wstr[RECLEN], s1[RECLEN];

 emit_one_insn(fp, ".globl __exe_args_str\n");
 emit_one_insn(fp, "\t.section\t.rodata\n");
 i = 0;
 emit_one_insn(fp, ".ARG0:\n");
 emit_one_insn(fp, "\t.asciz \"EXE\"\n");
 i = 1;
 for (olp = __opt_hdr; olp != NULL; olp = olp->optlnxt)
  {
   cp = olp->opt;
   if (olp->is_bmark || olp->is_emark) continue;
   len = strlen(cp);
   /* AIV 12/01/09 - need to add escape char '\' to " */
   for (nlen = k = 0; k < len; k++)
    {
     c = cp[k];
     /* if quote add an escape '\' for assembly string */
     if (c == '"') 
      {
       s1[nlen] = '\\';
       nlen++;
      }
     s1[nlen] = c;
     nlen++;
    }
   s1[nlen] = '\0';

   emit_one_insn(fp, ".ARG%d:\n", i);
   emit_one_insn(fp, "\t.asciz \"%s\"\n", s1);
   i++;
  }
 emit_one_insn(fp, "\t.data\n");

#ifdef __CVC32__
 emit_one_insn(fp, "\t.align 4\n");
 strcpy(wstr, ".long");
#else
 emit_one_insn(fp, "\t.align 16\n");
 strcpy(wstr, ".quad");
#endif

 emit_one_insn(fp, "__exe_args_str:\n");
 for (j = 0; j < i; j++)
  {
   emit_one_insn(fp, "\t%s   .ARG%d\n", wstr, j);
  }

 /* the argc value */
 emit_one_insn(fp, ".globl __exe_args_num\n");
 emit_one_insn(fp, "__exe_args_num:\n");
 emit_one_insn(fp, "\t.long   %d\n", i);
}

/*
 * routine to fill ctev fields during asmlnk time scan of all ctevs
 * through net list (stp, net, gate etc.) traversal
 *
 * builds the linked list for later couting and writing
 */
static void fill_1mod_ctevs(struct mod_t *mdp)
{
 struct st_t *stp;
 struct ctev_t *ctevp;
 struct gate_t *gp;
 struct net_t *np;
 struct net_chg_t *ncp;
 struct conta_t *cap;
 struct ctev_t *last_ctevp;
 struct delctrl_t **da;
 struct delctrl_t *dctp;
 int32 i, ni;

 last_ctevp = NULL;
 for (i = 0; i < mdp->mstnum; i++) 
  {
   stp = mdp->mstmts[i];
   /* AIV 11/10/06 - if stmt is marked unreachable skip linking */
   if (stp->unreachable) continue;
   if ((ctevp = stp->ctevp) == NULL) continue;
   fill_addtolst_ctev_flds(mdp, ctevp, &(last_ctevp), -1, -1, NULL);
  }

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   if (np->ndel_ctevtab == NULL) continue;
   /* if not process wire event - known to be mipd */
   //AIV LOOKATME - should NP_MIPD_NCHG events - be stored else where??????
   if (!np->ndel_ctevtab[0]->has_wire_ev) 
    {
     if (np->n_isavec) 
      {
       for (i = 0; i < np->nwid; i++)
        {
         ncp = __find_nchg_range(np, i, i);
         /* DBG remove -- */ 
         if (ncp == NULL) __misc_terr(__FILE__, __LINE__);
         /* ---- */ 
         fill_addtolst_ctev_flds(mdp, np->ndel_ctevtab[i], &(last_ctevp),
          -1, -1, NULL);
        }
      }
     else
      {
       fill_addtolst_ctev_flds(mdp, np->ndel_ctevtab[0], &(last_ctevp), -1,
        -1, NULL);
      }
     continue;
    }

   /* these are all process wire events */
   if (np->n_isavec)
    {
     for (i = 0; i < np->nwid; i++)
      {
       ncp = __find_nchg_range(np, i, i);
       /* DBG remove -- */ 
       if (ncp == NULL) __misc_terr(__FILE__, __LINE__);
       /* ---- */ 
       fill_addtolst_ctev_flds(mdp, np->ndel_ctevtab[i], &(last_ctevp), -1,
        ncp->ndx, NULL);
      }
    }
   else 
    {
     ncp = __find_nchg_range(np, -1, -1);
     /* DBG remove -- */ 
     if (ncp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     fill_addtolst_ctev_flds(mdp, np->ndel_ctevtab[0], &(last_ctevp),
      -1, ncp->ndx, NULL);
    }
  }

 for (i = 0; i < mdp->mgnum; i++)
  {
   gp = &(mdp->mgates[i]);

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

   fill_addtolst_ctev_flds(mdp, ctevp, &(last_ctevp), -1, -1, gp);
  }

 for (i = 0; i < mdp->mcanum; i++)
  {
   cap = &(mdp->mcas[i]);
   if (cap->lhsx->getpatlhs) continue;
   /* DBG remove -- */ 
   if (cap->ca_pb_sim) __misc_terr(__FILE__, __LINE__);
   /* ---- */ 

   if (cap->ca_delrep != DT_NONE) 
    {
     fill_addtolst_ctev_flds(mdp, cap->ctevp, &(last_ctevp), cap->enter_cndx,
      -1, NULL);
    }
  }

 /* AIV 03/09/09 - make tev for every merged always block */
 da = mdp->dctrl_array;
 for (i = 0; i < mdp->dctrl_size; i++)
  {
   dctp = da[i];
   /* only create on for merged header fg */
   if (!dctp->is_merged && dctp->merged_dctp != NULL && !dctp->needs_thread)
    {
     ctevp = dctp->head_ctevp;
     /* DBG remove -- */ 
     if (ctevp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */ 
     fill_addtolst_ctev_flds(mdp, ctevp, &(last_ctevp), -1, -1, NULL);
    }
  }
}

/*
 * routine to add new asmlnk itme fields to one ctev and link on end of mods 
 * list
 *
 * SJM 04/23/08 - bet there is cross linking - need to catch
 */
static void fill_addtolst_ctev_flds(struct mod_t *mdp, struct ctev_t *ctevp,
 struct ctev_t **last_ctevpp, int32 ca_ndx, int32 wev_ndx, struct gate_t *gp)
{
#ifdef __XPROP__
 /* AIV 02/20/12 - xprop can now share this across statements */
 /* the xedge can use this one ctev across xedge and no xedge stmt fgs */
 if (ctevp->in_list) return;
#else
 if (ctevp->in_list) __misc_terr(__FILE__, __LINE__);
#endif

 ctevp->in_list = TRUE;
 if (*(last_ctevpp) == NULL)
  { 
   /* DBG remove -- */
   if (mdp->ctev_list_hd != NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   mdp->ctev_list_hd = ctevp;  
  }
 else
  {
   if ((*last_ctevpp)->ctevnxt != NULL) __misc_terr(__FILE__, __LINE__);
   (*last_ctevpp)->ctevnxt = ctevp;
  }
 *(last_ctevpp) = ctevp;

 ctevp->ca_ndx = ca_ndx;
 ctevp->wev_ndx = wev_ndx;
 ctevp->ctev_gp = gp;
}

/*
 * routine to emit the tev areas for 1 mod - assumes ctev linked list built
 *
 * this just defines asm storage and initializes it in design wide comm .s file
 */
static void emit_1mod_tev_glbs(FILE *fp, struct mod_t *mdp)
{
 struct ctev_t *ctevp;
 int32 first_time, alloc_nbytes;
 char s1[RECLEN];

 /* write nothing if no tevs - can always make static */
 if (mdp->ctev_list_hd == NULL) return;

 for (ctevp = mdp->ctev_list_hd; ctevp != NULL; ctevp = ctevp->ctevnxt) 
  {
   /* AIV 04/26/08 - if nb needs memory create fixed memory */
   /* SJM 07/18/08 - intertwine tev dats and nb mem tnbs */ 
   if (ctevp->nb_rhs_byt_size != -1)
    {
     /* SJM 07/22/08 - area for scalars must still be in words */
     /* and each tev tu rhswp ptr must be word aligned */
     alloc_nbytes = correct_walign_nb_rhs_area(ctevp->nb_rhs_byt_size);

     /* nb_rhs_area is the per inst non blking rhs val - saves a malloc */ 
     sprintf(s1, "__nb_rhs_area_%d", ctevp->ctev_ndx);
     asm_wr_globl(fp, s1, mdp->flatinum*alloc_nbytes);
    }
   sprintf(s1, "__tevdat_%d", ctevp->ctev_ndx);
   asm_wr_globl(fp, s1, mdp->flatinum*sizeof(struct tev_t));
  }

 /* for the is1v delays (const events at RT) need the table in the .s file */
 /* because for gcc compiling of the possibly giant initializer too slow */ 
 /* SJM 05/11/08 - need the literal numbers in some file because when */
 /* load lib used, the ctev records not built */
 first_time = TRUE;
 for (ctevp = mdp->ctev_list_hd; ctevp != NULL; ctevp = ctevp->ctevnxt)
  {
   if (mdp->flatinum > 1 && is_const_is1v_delay(ctevp->del_rep))
    {
     emit_1ctev_is1v_dels(fp, mdp, ctevp, &(first_time));
    }
  }
}

/*
 * routine to alloc bytes so for scalars still save one word per inst
 * this routine mostly just checks for consistency
 *
 * for Verilog happens that non block assigns can't involve wires so
 * works in sense that only scalar can be 1 byte although memory area
 * needs to be word aligned - code is still inconsistent so need the
 * byte assign and therefore can't use a byte size of 4 (WRDBYTES)
 *
 * AIV - LOOKATME - what if for system Verilog wires can be in nb assigns?
 */
static int32 correct_walign_nb_rhs_area(int32 rhs_byt_siz)
{
 int32 alloc_nbytes;

//AIV? - 07/22/08 - what is going on - how can byte aligned for scalar work????
 /* SJM 07/22/08 - if scalar need byt size of 1 for movb but must align */
 /* each inst fixed area on word boundary */
 /* reserve area in the comm asm .s file - bbgen set right num bytes */
 if ((rhs_byt_siz % WRDBYTES) != 0) 
  { 
   /* DBG remove -- */
   if (rhs_byt_siz != 1) __misc_terr(__FILE__, __LINE__);
   /* --- */
   alloc_nbytes = WRDBYTES;
  }
 else alloc_nbytes = rhs_byt_siz;
 return(alloc_nbytes);
}

/*
 * routine to write one global in .data section with a 0 fill of area
 */
static void asm_wr_globl(FILE *fp, char *glbnam, size_t glbsiz)
{
 /* AIV 06/23/09 - .fill creates large .o and uses large amount of memory */
 /* in ld, no need to zero these here since they are all set */
 /* AIV 06/23/09 - this needs to take size_t here - not int */
 /* AIV 07/02/09 - better to align on 32 for both 32/64 - following gcc */
#ifdef __CVC32__
 emit_one_insn(fp, "\t.comm %s, %d, 32\n", glbnam, glbsiz);
#else
 emit_one_insn(fp, "\t.comm %s, %ld, 32\n", glbnam, glbsiz);
#endif
}

/*
 * proc to emit the is1v delays (linear 1w or 2w per inst) tab in comm .s file
 */
static void emit_1ctev_is1v_dels(FILE *fp, struct mod_t *mdp,
 struct ctev_t *ctevp, int32 *first_time)
{
 int32 cti;
 word32 w1;
 word64 w64;
 char s1[RECLEN], s2[RECLEN];

 if (*first_time)
  {
   emit_one_insn(fp, "\n# const in tev dat settable per inst 1v delays\n");
   *first_time = FALSE;
  }
 sprintf(s1, "__tevdat_%d", ctevp->ctev_ndx);
 sprintf(s2, "%s_1v_peri_tab", s1);
 emit_one_insn(fp, ".globl %s\n", s2);
 emit_one_insn(fp, "\t.align 8\n");
 /* case 1: needs 2 longs per inst (delay) */
 if (ctevp->del_rep == DT_IS1V && is1v_nds_64bits(ctevp->du, mdp->flatinum))
  {
   /* here need 2 longs for each delay */
   emit_one_insn(fp, "%s:\n", s2);

   /* following Verilog always store low word first - little endian */
   for (cti = 0; cti < mdp->flatinum; cti++)
    {
     w64 = ctevp->du.dis1v[cti];
#ifdef __CVC32__
     emit_one_insn(fp, "\t.quad\t%llu\n", w64);
#else
     emit_one_insn(fp, "\t.quad\t%lu\n", w64);
#endif
    }
   return;
  }
 /* case 2: only one word per inst (delay) needed */
 w1 = 0;
 emit_one_insn(fp, "%s:\n", s2);
 for (cti = 0; cti < mdp->flatinum; cti++)
  {
   if (ctevp->del_rep == DT_IS1V) w1 = (word32) (ctevp->du.dis1v[cti] & ALL1W);
   else if (ctevp->del_rep == DT_IS1V1) w1 = (word32) ctevp->du.dis1v1[cti];
   else if (ctevp->del_rep == DT_IS1V2) w1 = (word32) ctevp->du.dis1v2[cti]; 
   else __case_terr(__FILE__, __LINE__);

   emit_one_insn(fp, "\t.%s\t%lu\n", AW_STR, w1);
  }
}

/*
 * return T if at least one delays wider than 32 bits
 * only called for IS1V forms (since only pack 1 byte and 2 byte cases)
 *
 * for constant delays where all peri values known
 * think very rare for delay to be large enough to require 32 bits
 */
static int32 is1v_nds_64bits(union del_u isdelu, int32 ninsts)
{
 int32 cti;

 for (cti = 0; cti < ninsts; cti++)
  {
   if ((isdelu.dis1v[cti] >> 32) != 0) return(TRUE);
  }
 return(FALSE);
}

/*
 * emit the asm comm .s file .data .globl areas for every nchg list element
 * in mod
 */
static void emit_1mod_nchg_glbs(FILE *fp, struct mod_t *mdp)
{
 int32 ni;
 struct net_chg_t *ncp;
 struct net_t *np;
 char s1[RECLEN];
 size_t size;

 if (__show_asm)
  {
   emit_one_insn(fp, "# asm comm storage for nchges in module %s\n",
    mdp->msym->synam);
  }

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   /* AIV 08/05/09 - this should be in first loop */
   if (!__needs_netchg_record(np)) continue;

   for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
    {
     /* AIV 11/20/07 - may use the tran channels in wrapper code so lowered */
     /* flag may not be set */
     if (!ncp->is_lowered && !ncp->is_wire_ev && np->ntraux == NULL) continue;

     /* AIV 08/05/09 - this now makes two passes because is_lowered */
     /* flag may not be set until all mods processed */
     if (ncp->is_printed) continue;

     ncp->is_printed = TRUE;
     sprintf(s1, "__nchgdat_%d", ncp->ndx);
     /* AIV 06/23/09 - if used in tran force need to dump special code */
     /* to keep it contiguous this is because the wrapper code - takes */
     /* the 'base' for each and then adds to get the get nchglp for */
     /* each bit from v_aslib.c: */
//AIV PTR FIXME - don't think this is portable or good
//take the original netchg address and get the bi's from theis address
//nchglp = (struct nchglst_t *) ((word32) nchglp + 
//         ((word32) sizeof(struct nchglst_t) * (ninsts-inum)));
     size = mdp->flatinum*sizeof(struct nchglst_t);
     /* AIV 02/12/10 - should use .space here not .zero - more portable */
     /* .zero doesn't work on OSX */
     if (ncp->is_tran_force_vec)
      {
       emit_one_insn(fp, ".globl\t%s\n", s1);
       emit_one_insn(fp, "\t.align %d\n", WRDBYTES);
#ifdef __CVC32__
       emit_one_insn(fp, "%s:\n", s1);
       emit_one_insn(fp, "\t.space %d\n", size);
#else
       emit_one_insn(fp, "%s:\n", s1);
       emit_one_insn(fp, "\t.space %lu\n", size);
#endif
      }
     else
      {
      /* AIV 07/02/09 - better to align on 32 for both 32/64 - following gcc */
#ifdef __CVC32__
       emit_one_insn(fp, "\t.comm %s, %d, 32\n", s1, size);
#else
       emit_one_insn(fp, "\t.comm %s, %lu, 32\n", s1, size);
#endif
      }
   }
 } 
}

/*
 * emit the commlabs 
 * AIV 03/12/12 - now these are ideally placed at the end of each module's
 * M_0.s generated file.  This is better because of cache reasons and it
 * keeps the the comm_ files small.  Just print once and mark as printed,
 * will make one last pass for the comm files for those not yet printed.
 */
static void emit_1mod_commlabs(FILE *fp, struct mod_t *mdp, int32 is_comm_file)
{
 int32 i;
 struct task_t *tskp;
 struct net_pin_t *npp;
 struct gref_t *grp;
 struct conta_t *cap;
 struct net_t *np;
 struct gate_t *gp;
 struct dcevnt_t *dcep;
 struct st_t *stp;
 struct expr_t *xp;
 struct expr_tab_t *etp;
 char s1[RECLEN], s2[RECLEN];
     
 /* loaded statments */
 for (i = 0; i < mdp->mstnum; i++) 
  {
   stp = mdp->mstmts[i];
   if (!stp->is_loaded) continue;

   /* AIV 03/12/12 - this now makes two passes because is_lowered */
   /* flag may not be set until all mods processed */
   if (stp->is_printed) continue;
   stp->is_printed = TRUE;

   sprintf(s1, "ST_%d_%d", mdp->m_idnum, i);
   asm_wr_globl(fp, s1, WRDBYTES);
  }

 /* loaded net items */
 for (i = 0, np = &(mdp->mnets[0]); i < mdp->mtotvarnum; i++, np++)
  {
   /* loaded dces */
   for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt) 
    {
     if (dcep->merged || !dcep->is_loaded) continue;

     if (dcep->is_printed) continue;
     dcep->is_printed = TRUE;

     sprintf(s1, "DCEA_%d_%d_%d", mdp->m_idnum, i, dcep->dce_ndx);
     asm_wr_globl(fp, s1, WRDBYTES);
    }

   /* loaded npps */
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
     if (!npp->is_loaded) continue;

     if (npp->is_printed) continue;
     npp->is_printed = TRUE;

     sprintf(s1, "NPPA_%d_%d", mdp->m_idnum, npp->npp_idnum);
     asm_wr_globl(fp, s1, WRDBYTES);
    }

   for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
    {
     if (!npp->is_loaded) continue;

     if (npp->is_printed) continue;
     npp->is_printed = TRUE;

     sprintf(s1, "NPPA_%d_%d", mdp->m_idnum, npp->npp_idnum);
     asm_wr_globl(fp, s1, WRDBYTES);
    }
   
   /* loaded nets */
   if (!np->is_loaded) continue;

   if (np->is_printed) continue;
   np->is_printed = TRUE;

   __bldchk_var_comm_ref(s2, np, mdp, NULL);
   sprintf(s1, "%s_np_%d", s2, i);
   asm_wr_globl(fp, s1, WRDBYTES);
  }

 /* loaded expressions */
 /* XPR_* must go at the end in the comm_ file because xprs (pointer adrs) */
 /* are shared across mods */
 if (is_comm_file)
  {
   if ((etp = mdp->expr_tab) != NULL)
    {
     for (i = 0; i < etp->num; i++)
      {
       xp = etp->table[i];
       if (!xp->is_loaded) continue;
   
       sprintf(s1, "XPR_%d_%d", mdp->m_idnum, i);
       asm_wr_globl(fp, s1, WRDBYTES);
      }
    }
  }

 /* loaded gates */
 for (i = 0, gp = &(mdp->mgates[0]); i < mdp->mgnum; i++, gp++)
  {
   /* AIV 07/06/09 - removed gp->is_loaded to save space in gate_t */
   if (!is_gate_loaded(gp)) continue;

   sprintf(s1, "G_%d_%d", mdp->m_idnum, i);
   asm_wr_globl(fp, s1, WRDBYTES);
  }
 
 /* loaded contas */
 for (i = 0, cap = &(mdp->mcas[0]); i < mdp->mcanum; i++, cap++)
  {
   if (!cap->is_loaded) continue;

   if (cap->is_printed) continue;
   cap->is_printed = TRUE;

   sprintf(s1, "CA_%d_%d", mdp->m_idnum, i);
   asm_wr_globl(fp, s1, WRDBYTES);
  }
 
 /* loaded xmrs */
 for (i = 0, grp = &(mdp->mgrtab[0]); i < mdp->mgrnum; i++, grp++)
  {
   if (!grp->is_loaded) continue;

   if (grp->is_printed) continue;
   grp->is_printed = TRUE;

   sprintf(s1, "GRP_%d_%d", mdp->m_idnum, i);
   asm_wr_globl(fp, s1, WRDBYTES);
  }

 /* loaded tasks */
 for (i = 0, tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt, i++)
  {
   if (!tskp->is_loaded) continue;

   if (tskp->is_printed) continue;
   tskp->is_printed = TRUE;

   sprintf(s1, "TSKP_%d_%d", mdp->m_idnum, i);
   asm_wr_globl(fp, s1, WRDBYTES);
  }
}

/*
 * emit ptr (addr) location that directly points to tchk tchg struct
 *
 * saves the complex indirection to get to the tchg_t record 
 */
static void emit_1mod_tchk_tchg_adr_labs(FILE *fp, struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct net_pin_t *npp;
 char s1[RECLEN];

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
  {
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
     if (npp->npntyp != NP_TCHG) continue;
     if (npp->chgsubtyp != NPCHG_TCCHK) continue;

     sprintf(s1, "__TCHK_TCHG_%d_%d", mdp->m_idnum, npp->npp_idnum); 
     asm_wr_globl(fp, s1, WRDBYTES);
    }
  }
}

/*
 * emit ptr (addr) location that directly points to specify path del table
 *
 * saves the complex indirection to access the delay of a specify path
 * separates path selection in mod (complex wrapper) from delay access
 */
static void emit_1mod_pth_del_adr_labs(FILE *fp, struct mod_t *mdp)
{
 struct spcpth_t *pthp; 
 char s1[RECLEN];

 if (mdp->mspfy == NULL) return;

 for (pthp = mdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
  {
   /* DBG remove -- */
   if (pthp->spcpth_id == -1) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   sprintf(s1, "__PTHDEL_%d_%d", mdp->m_idnum, pthp->spcpth_id);
   asm_wr_globl(fp, s1, WRDBYTES);
  }
}

/*
 * emit up to two ptr (addr) really labels asm globals that are linked to
 * malloced udp tables (works because static linker links with the .s files)
 * for each udp in mod
 *
 * this allocates one ptr for each udp table - an alnk time routine sets
 */
static void emit_dsgn_udptab_adr_labs(FILE *fp)
{
 struct udp_t *udpp;
 char s1[RECLEN];
 
 for (udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
  {
   /* DBG remove -- */
   if (udpp->utab->ludptab == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* DBG remove -- */
   if (udpp->u_idnum == -1) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   /* here address is just ptr to the one level udp tab */
   sprintf(s1, "__UDPL_%d", udpp->u_idnum);
   asm_wr_globl(fp, s1, WRDBYTES);

   if (udpp->utyp == U_EDGE)
    {
     /* DBG remove -- */
     if (udpp->utab->eudptabs == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* here label in comm .s file ptr to up to 27 element ptr array */  
     sprintf(s1, "__UDPE_%d", udpp->u_idnum);
     asm_wr_globl(fp, s1, WRDBYTES);
    }
  }
}

/*
 * ROUTINES TO EMIT PER DESIGN IDP BSS AREA STILL INTO ASM COMM FILE 
 */

/*
 * routine to emit the contiguous idp areas
 *
 * the .data .globl size is enough room for one idp area for each inst of mod
 * all regions contigous and contiguously after the pmd area for all mods 
 */
static void emit_dsgn_idparea(FILE *fp, struct mod_t *mdp)
{
 char s1[RECLEN]; 

 __my_fprintf(fp, "\n");

 /* SJM 04/10/08 - now need first all mod pmd regions (initialized) */
 /* then here all uninitialized per inst idp regions for every module */
 if (__show_asm)
  {
   __my_fprintf(fp,
    "# ALL INST CONTIGUOUS IDP REGIONS FOR MOD %s (ndx=%d) at %s\n",
    mdp->msym->synam, mdp->m_idnum, __bld_lineloc(__xs,
    mdp->msym->syfnam_ind, mdp->msym->sylin_cnt));
  }

 /* SJM now putting ctev data into design wide .data segment area and init */
 emit_one_insn(fp, "\t.data\n");
 /* AIV 06/23/09 - .fill creates large .o and uses large amount of memory */
 /* in ld, no need to zero these here since they are all set */
 /* AIV 07/02/09 - better to align on 32 for both 32/64 - following gcc */
 sprintf(s1, "__idpdat_%d", mdp->m_idnum);
#ifdef __CVC32__
 emit_one_insn(fp, "\t.comm %s, %u, 32\n", s1, 
  (mdp->flatinum*mdp->mod_idata_siz)*WRDBYTES);
#else
 emit_one_insn(fp, "\t.comm %s, %lu, 32\n", s1, 
  (mdp->flatinum*mdp->mod_idata_siz)*WRDBYTES);
#endif
}

 
/*
 * create an array of enter points for init/always enter blocks
 */
static void emit_ialst_enter_points_array(FILE *fp, struct mod_t *mdp)
{
 int32 ndx;
 struct ialst_t *ialp;
 struct st_t *stp;
 char s1[RECLEN]; 

 __my_fprintf(fp, "\n");

 /* contains no always/init blocks continue */
 if (mdp->ialst == NULL) return;

 if (__show_asm)
  {
   __my_fprintf(fp,
    "# DATA ALWAYS/INIT ENTER POINT ARRAYS %s(%d)", mdp->msym->synam, 
     mdp->m_idnum);
  }

 sprintf(s1, "ialst_%d", mdp->m_idnum);
 emit_one_insn(fp, "\t.data\n");
 emit_one_insn(fp, ".globl\t%s\n", s1);
 emit_one_insn(fp, "\t.align\t%d\n", WRDBYTES);
 emit_one_insn(fp, "%s:\n", s1);

 /* init the array - 0 (NULL) if there isn't an enter point */
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   if (ialp->needs_thread) 
    {
     emit_one_insn(fp, "\t.%s 0\n", AW_STR);
     continue;
    }
   stp = ialp->iastp;
   ndx = stp->st_ndx;
   /* DBG remove -- */
   if (ndx == -1) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   sprintf(s1, "ST_ENT_%d_%d", mdp->m_idnum, ndx);
   emit_one_insn(fp, "\t.%s %s\n", AW_STR, s1);
  }
}

 
/*
 * ROUTINES THAT EMIT FIXED BOILER PLATE AT BOTTOM OF DESIGN WIDE .s FILE
 */

/*
 * emit all the fixed boiler plate into the design wide comm file 
 *
 * data here is completed fixed boiler plate so could be in .s file that
 * is shipped with CVC but the problem is where to put it - easier to
 * just gen the .s file each time
 *
 * the design specific jump table is also here - it is design specific
 * but otherwide mostly boiler plate - if inlude the .s file, must move it
 * back to the design wide comm file
 * 
 * SJM 08/26/08 - BEWARE - only .text insns can be emitted here
 *
 * fp can either be .s comm file for debugging or the opened pipe
 */
static void emit_fixed_text_boiler_plate(FILE *fp)
{
 if (__show_asm)
  {
   __my_fprintf(fp, "\n#================================================\n");
   __my_fprintf(fp, "# MISC FIXED DESIGN WIDE INSN BOILER PLATE\n");
   __my_fprintf(fp, "#================================================\n");
  } 
 emit_one_insn(fp, "\t.text\n");
 /* emit boiler plate wrappers for back end of sched process code */
 emit_boiler_plate_enter_next_events(fp);
}

/*
 * emit area in design wide comm_ file for task table jump
 * jmp to task name index array
 *
 * aslo emits the cvc mem use value for load lib design matches src check
 */
static void emit_comm_task_jmptable(FILE *fp) 
{
 int32 nti;
 char s1[RECLEN];

 /* AIV 01/05/06 - still produces code which causes linking errors */
 /* if a unreachable task calls a task it is not reachable but */
 /* code is produce  */
 /* if no tasks no jmp table to be made */
 /* if (__thdjmp_nxti == -1) return; */
 strcpy(s1, "__thdjmp_ret_addr_tab");
 emit_one_insn(fp, ".globl %s\n", s1);
 emit_one_insn(fp, "\t.align %d\n", WRDBYTES);
 emit_one_insn(fp, "%s:\n", s1);
 for (nti = 0; nti <= __thdjmp_nxti; nti++)
  {
   /* now add enter ndx as part of return thread name */ 
   emit_one_insn(fp, "\t.%s %s_%d\n", AW_STR, __thdjmp_ret_tab[nti], nti);
  }
}

/*
 * create the dummy end of net change list event 
 *
 * this struct nchglst_t is placed on the last event list
 *
 * only one per design and fixed boiler plate that could go in fixed .s file 
 * that is just linked in
 */
static void emit_last_nchglst_fence(FILE *fp)
{
 char s1[RECLEN];

 sprintf(s1, "NCHGDAT_LAST");
 /* AIV 08/05/09 - this should be .local */
 emit_one_insn(fp, ".local %s\n", s1);
 emit_one_insn(fp, "\t.align %d\n", WRDBYTES);
 emit_one_insn(fp, "%s:\n", s1);

 /* triggered = FALSE */
 emit_one_insn(fp, "\t.%s\t%d\n", AW_STR, FALSE);
 /* process_enterptr - this eq to end net change list handle */
 emit_one_insn(fp, "\t.%s\tLAST_NCHG_EV\n", AW_STR);
 /* delayed mipd FALSE */
 emit_one_insn(fp, "\t.%s\t%d\n", AW_STR, FALSE);
 /* bi1 and bi2 = -1 */
 emit_one_insn(fp, "\t.%s\t%d\n", AW_STR, -1);
 emit_one_insn(fp, "\t.%s\t%d\n", AW_STR, -1);
 /* chgnp set to NULL */
 emit_one_insn(fp, "\t.%s\t%d\n", AW_STR, 0);
 /* SJM 04/14/08 - this was left out previously */
 /* nchg_idp is NULL */
 emit_one_insn(fp, "\t.%s\t%d\n", AW_STR, 0);
 /* nchglnxt to NULL */
 emit_one_insn(fp, "\t.%s\t%d\n", AW_STR, 0);
}
 
/*
 * need boiler plate wrappers since routines can't use stack - current
 * solution is to generate the assembly into the .s file each time
 * compiler runs
 *
 * could use fixed .s file written once but problem is where to put it
 * 
 * AIV FIXME - these should be lowered
 */
static void emit_boiler_plate_enter_next_events(FILE *fp)
{
 struct tev_t *tevp;
 int32 offset;
 struct nchglst_t *nchgp;

 /* AIV 04/20/10 - if thread contains auto task need to call thrd wrapper */
 /* routine for extra handling for auto tasks/funcs */
 if (__design_has_auto_task)
  {
   emit_wrapper_routine(fp, "THRD_EV", "__process_compiled_thrd_ev_auto", TRUE,
    TRUE);
  }
 else
  {
   emit_wrapper_routine(fp, "THRD_EV", "__process_compiled_thrd_ev", TRUE, 
    TRUE);
  }
 /* AIV 08/05/09 - changed a bunch of these .glbl to .local */
 emit_wrapper_routine(fp, "NBPA_VARNDX_CONCAT_EV", 
  "__process_nbpa_varndx_concat_ev", FALSE, TRUE);
 emit_wrapper_routine(fp, "GATECHG_EV", "__cvc_change_gate_outwire", FALSE, 
   TRUE);
 /* wide gates use this wrapper gate process code */
 emit_wrapper_routine(fp, "GATECHG_WIDE_EV", "__process_gatechg_ev", FALSE,
  TRUE); 
 emit_wrapper_routine(fp, "WIRE_EV", "__process_wire_ev", FALSE, FALSE);
 emit_wrapper_routine(fp, "TRPTHDST_EV", "__process_compiled_trpthdst_ev", 
  FALSE, FALSE);
 /* AIV 01/09/07 - need a special delay callback for the pli */
 emit_wrapper_routine(fp, "DELAY_CB_EV", "__delay_callback", FALSE, FALSE);
 emit_wrapper_routine(fp, "PROCESS_PUTPDEL_EV", "__process_putpdel_ev", FALSE, 
  FALSE);
 emit_wrapper_routine(fp, "SETDEL_CALL_MISCTF_EV", "__setdel_call_misctf", 
  FALSE, FALSE);
 emit_wrapper_routine(fp, "SYNC_CALL_MISCTF_EV", "__sync_call_misctf", FALSE, 
  FALSE);
 emit_wrapper_routine(fp, "VPI_VARPUTV_EV", "__process_vpi_varputv_ev", FALSE,
  FALSE);
 emit_wrapper_routine(fp, "VPIDRV_EV", "__process_vpidrv_ev", FALSE, FALSE);
 /* AIV 01/09/08 - pli can still alloc/cancel events */
 emit_wrapper_routine(fp, "CANCEL_EV", NULL, FALSE, FALSE);

 //////////////////// FREE EVENT (LAST EVENT) ROUTINE ////////////////////

 /* process free event wrapper */
 emit_one_insn(fp, "\t.text\n");
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp, ".local %s\n", "FREE_EVENT_EV");
 emit_one_insn(fp, "%s:\n", "FREE_EVENT_EV");
 /* AIV 01/07/09 - no longer a need to set processing pnd0s */
 /* __processing_pnd0s = TRUE; */
 /* __cur_te_endp = NULL; */
 /* AIV 02/13/09 - removed the need to use/set __cur_te_hdrp */
 emit_one_insn(fp, "\t%s   $0, __cur_te_endp%s\n", MOVA_STR, GBL_OFS_STR);

 emit_process_next_event(fp, "free_ev", TRUE);

 //////////////////// FREE EVENT POUND 0 ROUTINE ////////////////
 /* process free event pnd0 wrapper */
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp, ".local %s\n", "FREE_EVENT_PND0_EV");
 emit_one_insn(fp, "%s:\n", "FREE_EVENT_PND0_EV");
 /* __p0_te_hdrp = __p0_te_endp = NULL; */
 emit_one_insn(fp, "\t%s   $0, __p0_te_hdrp%s\n", MOVA_STR, GBL_OFS_STR);
 emit_one_insn(fp, "\t%s   $0, __p0_te_endp%s\n", MOVA_STR, GBL_OFS_STR);

 emit_process_next_event(fp, "pnd0_ev", FALSE);

 /* last nchg event handler */
 //////////////////// LAST NET CHANGE DUMMY HANDLER ////////////////
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp, ".local %s\n", "LAST_NCHG_EV");
 emit_one_insn(fp, "%s:\n", "LAST_NCHG_EV");

 emit_process_next_event(fp, "last_nchg_ev", TRUE);

 //////////////////// ALLOCATE NET CHANGE WRAPPER ////////////////////
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp, ".local %s\n", "ALLOC_NCHG_EV");
 emit_one_insn(fp, "%s:\n", "ALLOC_NCHG_EV");

//save __nchg_futend->next in ebx - is currently known to be freed must save
 /* current net change is an %eax */
 /* __asl_process_alloc_nchg - currently frees the nchg so must save the */
 /* next net change event in callee save reg %ebx */
 /* AIV BEWARE __asl_process_alloced_nchg is expecting net change in %eax */
 nchgp = &__nchg_dummy_hd;
 emit_one_insn(fp, "\t%s   %s, __idp%s\n", MOVA_STR, __regs[IDP_REG], GBL_OFS_STR);
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_BX]);
 emit_one_insn(fp, "\tcall   %s\n", "__asl_process_alloced_nchg");
 emit_one_insn(fp, "\t%s   %s, %s\n", MOVA_STR, __regs[AR_BX], __regs[AR_AX]);
 offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_BX], 
  __regs[AR_BX]);
 emit_one_insn(fp, "\tjmp    *%s\n", __regs[AR_BX]);

 //////////////////// DO NEXT EVENT WRAPPER ////////////////////
 /* process free event wrapper */
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp, ".local %s\n", "NEXT_EV");
 emit_one_insn(fp, "%s:\n", "NEXT_EV");
 /* notice __cur_tevp is always known to be in %eax here */
 /* emit_one_insn(fp, "\tmovl   __cur_tevp, %%eax\n"); */
 emit_next_event(fp);
 
 emit_free_next_event(fp, FALSE); 
 emit_free_next_event(fp, TRUE); 
 
 //////////////////// ENTER THE FIRST EVENT ////////////////////
 /* process free event wrapper */
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp, ".local %s\n", "SIM_ENTER_EV");
 emit_one_insn(fp, "%s:\n", "SIM_ENTER_EV");
 /* notice __cur_tevp is always known to be in %eax here */
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->te_idp) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   __cur_tevp%s, %s\n", MOVA_STR, GBL_OFS_STR, __regs[AR_AX]);
 /* esi = __cur_tevp->te_idp; */
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
   __regs[IDP_REG]);
 /* execute the first event */
 offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_AX]);
 emit_one_insn(fp, "\tjmp    *%s\n", __regs[AR_AX]);

 /* AIV 12/08/10 - really this should just check for dumpvars from following */
 /* option */
 if (__toggle_coverage) __cvc_slotend_action |= SE_TOGGLE;
 if (__dmpvars_all || __has_dmpv_sys_calls) __cvc_slotend_action |= SE_DUMPVARS;
 /* AIV 04/22/11 - need to turn on dumpports slotend action */
 if (__has_dumpports_sys_calls) __cvc_slotend_action |= SE_DUMPPORTS;

 /* AIV 01/19/09 - if design doesn't contain any nb with delay */
 /* move time can produce better code */
 if (__design_has_nb_del_events) emit_move_time_routine(fp);
 else emit_move_time_routine_nonb(fp);

 /* AIV 07/09/09 - emit code to do the fix scalar-to-scalar NP_ICONN ops */
 emit_fixed_scalar_iconn(fp, FALSE, FALSE);
 emit_fixed_scalar_iconn(fp, TRUE, FALSE);
 emit_fixed_scalar_iconn(fp, FALSE, TRUE);
 emit_fixed_scalar_iconn(fp, TRUE, TRUE);

 emit_fixed_wrapper_ptrs(fp);
 
 //////////////////// non-blocking pound 0  event ////////////////////
 emit_static_tev_events(fp, "free_event_pnd0_tev", "FREE_EVENT_PND0_EV");
 /* AIV 12/18/08 - free event for alloc events should have a fixed */
 /* struct as well this allows for address use in move time code */
 /* instead of memory ref for __free_event_tevp */
 emit_static_tev_events(fp, "free_event_tev", "FREE_EVENT_EV");
}
 
/*
 * emit the routine to set the glbl pointer wrappers 
 */
static void emit_fixed_wrapper_ptrs(FILE *fp)
{
 emit_one_insn(fp, ".globl __init_glbs_wrps\n");
 emit_one_insn(fp, "__init_glbs_wrps:\n");

 ll_awr_set_glb_movl(fp, "__process_compiled_thrd_ev_enterp", "THRD_EV");
 ll_awr_set_glb_movl(fp, "__process_wire_ev_enterp", "WIRE_EV");
 ll_awr_set_glb_movl(fp, "__process_nbpa_varndx_ev_enterp",
  "NBPA_VARNDX_CONCAT_EV");
 ll_awr_set_glb_movl(fp, "__process_trpthdst_ev_enterp", "TRPTHDST_EV");
 ll_awr_set_glb_movl(fp, "__process_gatechg_ev_enterp", "GATECHG_WIDE_EV");

 /* SJM 09/04/08 - for now since assign struct fld can't assign at alnk time */

 ll_awr_set_glb_movl(fp, "__process_next_nchg_enterp", "ALLOC_NCHG_EV");
 ll_awr_set_glb_movl(fp, "__process_next_ev_enterp", "NEXT_EV");
 ll_awr_set_glb_movl(fp, "__process_next_event_free_enterp", "NEXT_FREE_EV");
 ll_awr_set_glb_movl(fp, "__process_free_ev_pnd0_enterp",
  "FREE_EVENT_PND0_EV");
 ll_awr_set_glb_movl(fp, "__free_event_pnd0_tevp", "free_event_pnd0_tev");
 ll_awr_set_glb_movl(fp, "__process_free_ev_enterp", "FREE_EVENT_EV");

 /* SJM 08/08/08 - forgot this dlsym link */
 /* SJM 08/24/08 - next nbmem free enterp now gone */ 
 ll_awr_set_glb_movl(fp, "__first_enterp", "SIM_ENTER_EV");
 ll_awr_set_glb_movl(fp, "__delay_callback_enterp", "DELAY_CB_EV");
 ll_awr_set_glb_movl(fp, "__process_putpdel_enterp", "PROCESS_PUTPDEL_EV");
 ll_awr_set_glb_movl(fp, "__process_putpdel_enterp", "PROCESS_PUTPDEL_EV");
 ll_awr_set_glb_movl(fp, "__setdel_call_misctf_enterp",
  "SETDEL_CALL_MISCTF_EV");
 ll_awr_set_glb_movl(fp, "__sync_call_misctf_enterp", "SYNC_CALL_MISCTF_EV");

 /* AIV 01/09/08 - pli can still alloc/cancel events */
 ll_awr_set_glb_movl(fp, "__process_cancel_ev_enterp", "CANCEL_EV");
 ll_awr_set_glb_movl(fp, "__process_vpi_varputv_enterp", "VPI_VARPUTV_EV");
 ll_awr_set_glb_movl(fp, "__process_vpidrv_enterp", "VPIDRV_EV");
 emit_one_insn(fp, "ret\n");
}

#ifdef __CVC32__
/*
 * do a fixed scalar to scalar operation 32-version
 * values of regs are the following
 * %ebx - scalar value1
 * %ecx - idp value
 * %edx - scalar value2 (maybe stored into)
 * %ecx - nchg value address
 *
 * if is_nchg_nxt - just jump to next nchg
 */
static void emit_fixed_scalar_iconn(FILE *fp, int32 is_nchg_nxt, int32 is_mipd)
{
 int32 offset;
 struct nchglst_t *nchgp;
 char s1[RECLEN], s2[RECLEN];

 if (is_nchg_nxt)
  {
   strcpy(s1, "ICONN_S_S_NCHG_NXT");
   strcpy(s2, "L_IC_RET");
  }
 else
  {
   strcpy(s1, "ICONN_S_S_NCHG");
   strcpy(s2, "L_IC_RET_N");
  }

 if (is_mipd)
  {
   strcat(s1, "_MIPD");
   strcat(s2, "_MIPD");
  }

 /* compare value if different store and record changes */
 emit_one_insn(fp, ".globl %s\n", s1);
 emit_one_insn(fp, "%s:\n", s1);
 emit_one_insn(fp, "\tcmpl	(%%ecx), %%ebx\n");
 emit_one_insn(fp, "\tje	%s\n", s2);
 emit_one_insn(fp, "\tmovl	%%ebx, (%%ecx)\n");
 emit_one_insn(fp, "\tmovl	(%%edx), %%ebx\n");
 emit_one_insn(fp, "\ttestl	%%ebx, %%ebx\n");
 emit_one_insn(fp, "\tjne	%s\n", s2);
 emit_one_insn(fp, "\tmovl	__nchg_futend, %%ebx\n");
 if (is_mipd)
  {
   offset = (byte *) &(nchgp->delayed_mipd) - (byte *) nchgp;
   emit_one_insn(fp, "\tmovl	$0, %d(%%edx)\n", offset);
  }
 emit_one_insn(fp, "\tmovl	%%ebx, (%%edx)\n");
 nchgp = &__nchg_dummy_hd;
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 emit_one_insn(fp, "\tmovl	%%edx, %d(%%ebx)\n", offset);
 emit_one_insn(fp, "\tmovl	%%edx, __nchg_futend\n");
 emit_one_insn(fp, "%s:\n", s2);
 /* if flagged last just jump to next nchg */
 if (is_nchg_nxt)
  {
   offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
   emit_one_insn(fp, "\tmovl\t%d(%%eax), %%ebx\n", offset);
   emit_one_insn(fp, "\tjmp\t*%%ebx\n");
  }
 else
  {
   emit_one_insn(fp, "\tret\n");
  }
}
#else
/*
 * refer to 32-bit version above - same just insns/regs changed to 64-bit
 */
static void emit_fixed_scalar_iconn(FILE *fp, int32 is_nchg_nxt, int32 is_mipd)
{
 int32 offset;
 struct nchglst_t *nchgp;
 char s1[RECLEN], s2[RECLEN];

 if (is_nchg_nxt)
  {
   strcpy(s1, "ICONN_S_S_NCHG_NXT");
   strcpy(s2, "L_IC_RET");
  }
 else
  {
   strcpy(s1, "ICONN_S_S_NCHG");
   strcpy(s2, "L_IC_RET_N");
  }

 if (is_mipd)
  {
   strcat(s1, "_MIPD");
   strcat(s2, "_MIPD");
  }

 nchgp = &__nchg_dummy_hd;
 emit_one_insn(fp, ".globl %s\n", s1);
 emit_one_insn(fp, "%s:\n", s1);
 emit_one_insn(fp, "\tcmpq	(%%rcx), %%rbx\n");
 emit_one_insn(fp, "\tje	%s\n", s2);
 emit_one_insn(fp, "\tmovq	%%rbx, (%%rcx)\n");
 emit_one_insn(fp, "\tmovq	(%%rdx), %%rbx\n");
 emit_one_insn(fp, "\ttestq	%%rbx, %%rbx\n");
 emit_one_insn(fp, "\tjne	%s\n", s2);

 emit_one_insn(fp, "\tmovq	__nchg_futend, %%rbx\n");
 if (is_mipd)
  {
   offset = (byte *) &(nchgp->delayed_mipd) - (byte *) nchgp;
   emit_one_insn(fp, "\tmovq	$0, %d(%%rdx)\n", offset);
  }
 emit_one_insn(fp, "\tmovq	%%rbx, (%%rdx)\n");
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 emit_one_insn(fp, "\tmovq	%%rdx, %d(%%rbx)\n", offset);
 emit_one_insn(fp, "\tmovq	%%rdx, __nchg_futend\n");
 emit_one_insn(fp, "%s:\n", s2);
 if (is_nchg_nxt)
  {
   offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
   emit_one_insn(fp, "\tmovq\t%d(%%rax), %%rbx\n", offset);
   emit_one_insn(fp, "\tjmp\t*%%rbx\n");
  }
 else
  {
   emit_one_insn(fp, "\tret\n");
  }
}
#endif

/*
 * emit one dummy event only need to fill event enter pointer to jump
 * to next event 
 * these are used for better code in lowered move_time so an address
 * instead of a mem ref is used
 */
static void emit_static_tev_events(FILE *fp, char *s1, char *s2)
{
 struct tev_t *tevp;
 int32 i, offset;
 
 emit_one_insn(fp, ".local %s\n", s1);
 emit_one_insn(fp, "\t.data\n");
 emit_one_insn(fp, "\t.align %d\n", WRDBYTES);

 emit_one_insn(fp, "%s:\n", s1);

 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
 /* DBG remove -- */
 if (offset != WRDBYTES*3) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 for (i = 0; i < sizeof(struct tev_t)/WRDBYTES; i++)
  {
   if (i == 3)
    {
     emit_one_insn(fp, "\t.%s %s\n", AW_STR, s2);
    }
   else emit_one_insn(fp, "\t.%s 0\n", AW_STR);
  }
}

/*
 * emit code to handle jumping to the next event for end of time handle
 */
#ifdef __CVC32__
/*
 * AIV 03/16/10 - rewrote 32-bit version to not do some of the moves
 * and used fixed memory offsets - 64-bit is still the same routine
 */
static void emit_process_next_event(FILE *fp, char *jmpto_blk, 
 int32 need_pnd0_check)
{
 struct tev_t *tevp;
 char lab1[RECLEN], lab2[RECLEN];
 int32 offset;
 struct nchglst_t *nchgp;

 /* AIV 01/19/09 - if contains no non-blocking no need to check here */
 if (__design_has_nb_events)
  {
   sprintf(lab1, "checknb_%s", jmpto_blk);
  }
 else sprintf(lab1, "move_time");

 /* AIV 02/12/09 - pnd0 was falling thru to next fg and just happened to */
 /* work if no nb can just jump to move time */
 if (!need_pnd0_check && !__design_has_nb_events) 
  {
   sprintf(lab2, "move_time");
  }
 else sprintf(lab2, "nonchg_%s", jmpto_blk);

 /* AIV 12/18/09 - code is a little faster if loading value into reg */
 /* do the compare and use offset from loaded register */
 emit_one_insn(fp, "\t%s   __nchg_futend, %s\n", MOVA_STR, __regs[AR_BX]);
 emit_one_insn(fp, "\t%s   $__nchg_dummy_hd, %s\n", CMPA_STR, __regs[AR_BX]);

 emit_one_insn(fp, "\tje     %s\n", lab2);
 nchgp = &__nchg_dummy_hd;
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 emit_one_insn(fp, "\t%s   __nchg_dummy_hd+%d, %s\n", MOVA_STR, 
   offset, __regs[AR_AX]);
 emit_one_insn(fp, "\t%s   $0, __cur_tevp\n", MOVA_STR);
 emit_one_insn(fp, "\t%s   $__nchg_dummy_hd, __nchg_futend\n", MOVA_STR); 

 emit_one_insn(fp, "\t%s   $NCHGDAT_LAST, %d(%s)\n", MOVA_STR, offset, __regs[AR_BX]);

 offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
   __regs[AR_BX]);
 emit_one_insn(fp, "\tjmp    *%s\n", __regs[AR_BX]);

 /* AIV 02/12/09 - pnd0 and no nb return return here */
 if (!need_pnd0_check && !__design_has_nb_events) return;

 emit_one_insn(fp, "%s:\n", lab2);

/*
 tevp = __p0_te_hdrp;
 if (tevp != NULL) 
  {
   __p0_te_endp->tenxtp = __free_event_pnd0_tevp;
   return(tevp);
  }
*/

 if (need_pnd0_check)
  {
   emit_one_insn(fp, "\t%s   __p0_te_hdrp, %s\n", MOVA_STR, __regs[AR_AX]);
   emit_one_insn(fp, "\t%s  %s, %s\n", TESTA_STR, __regs[AR_AX], __regs[AR_AX]);

   emit_one_insn(fp, "\tje     %s\n", lab1);
   tevp = __free_event_tevp;
   offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
  //AIV FIXME - make this local to the comm.s file to use address and 
  //save mem and move
   emit_one_insn(fp, "\t%s   __p0_te_endp, %s\n", MOVA_STR, __regs[AR_BX]);
   emit_one_insn(fp, "\t%s   $free_event_pnd0_tev, %d(%s)\n", MOVA_STR, offset, 
    __regs[AR_BX]);

   emit_jump_to_next_event(fp, AR_AX);

   if (!__design_has_nb_events) return;

   emit_one_insn(fp, "%s:\n", lab1);
  }
/*
 if (__nb_te_endp != &__nb_dummy_hd)
  {
   tevp = __p0_te_hdrp = __nb_dummy_hd.tenxtp; 
   __p0_te_endp = __nb_te_endp;
   __nb_te_endp = &__nb_dummy_hd;
   __p0_te_endp->tenxtp = __free_event_pnd0_tevp;
   return(tevp);
  }
*/
 /* AIV 01/19/09 - if design contains no non-blocking no need to check */
 /* this - design is known to not contain nb events */
 if (!__design_has_nb_events) return;

 /* if (__nb_te_endp != &__nb_dummy_hd) */
 emit_one_insn(fp, "\t%s   __nb_te_endp, %s\n", MOVA_STR, __regs[AR_BX]);
 emit_one_insn(fp, "\t%s   $__nb_dummy_hd, %s\n", CMPA_STR, __regs[AR_BX]);
  
 emit_one_insn(fp, "\tje     move_time\n");

 /* AIV 09/09/08 - tevp needs to be assigned dummy value */
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
 /* tevp = __p0_te_hdrp = __nb_dummy_hd.tenxtp;  */
 emit_one_insn(fp, "\t%s   __nb_dummy_hd+%d, %s\n", MOVA_STR, 
   offset, __regs[AR_AX]);
 /* __p0_te_endp = __nb_te_endp; */
 emit_one_insn(fp, "\t%s   %s, __p0_te_endp\n", MOVA_STR, __regs[AR_BX]);

 /* __p0_te_endp->tenxtp = __free_event_pnd0_tevp; */
 emit_one_insn(fp, "\t%s   $free_event_pnd0_tev, %d(%s)\n", MOVA_STR, offset, 
  __regs[AR_BX]);
  
 /* __nb_te_endp = &__nb_dummy_hd; */
 emit_one_insn(fp, "\t%s   $__nb_dummy_hd, __nb_te_endp\n", MOVA_STR);
  

 emit_one_insn(fp, "\t%s   %s, __p0_te_hdrp\n", MOVA_STR, __regs[AR_AX]);

 emit_jump_to_next_event(fp, AR_AX);
}
#else
/*
 * 64-bit version must use memory access via register offsets
 */
static void emit_process_next_event(FILE *fp, char *jmpto_blk, 
 int32 need_pnd0_check)
{
 struct tev_t *tevp;
 char lab1[RECLEN], lab2[RECLEN];
 int32 offset;
 struct nchglst_t *nchgp;

 /* AIV 01/19/09 - if contains no non-blocking no need to check here */
 if (__design_has_nb_events)
  {
   sprintf(lab1, "checknb_%s", jmpto_blk);
  }
 else sprintf(lab1, "move_time");

 /* AIV 02/12/09 - pnd0 was falling thru to next fg and just happened to */
 /* work if no nb can just jump to move time */
 if (!need_pnd0_check && !__design_has_nb_events) 
  {
   sprintf(lab2, "move_time");
  }
 else sprintf(lab2, "nonchg_%s", jmpto_blk);

 /* AIV 12/18/09 - code is a little faster if loading value into reg */
 /* do the compare and use offset from loaded register */
 emit_one_insn(fp, "\t%s   __nchg_futend%s, %s\n", MOVA_STR, GBL_OFS_STR, 
  __regs[AR_AX]);
 emit_one_insn(fp, "\t%s   $__nchg_dummy_hd, %s\n", MOVA_STR, __regs[AR_BX]);
 emit_one_insn(fp, "\t%s   %s, %s\n", CMPA_STR, __regs[AR_BX], __regs[AR_AX]);

 emit_one_insn(fp, "\tje     %s\n", lab2);
 emit_one_insn(fp, "\t%s   $0, __cur_tevp%s\n", MOVA_STR, GBL_OFS_STR);
 emit_one_insn(fp, "\t%s   %s, __nchg_futend%s\n", MOVA_STR, __regs[AR_BX],
   GBL_OFS_STR); 

 nchgp = &__nchg_dummy_hd;
 offset = (byte *) &(nchgp->nchglnxt) - (byte *) nchgp;
 emit_one_insn(fp, "\t%s   $NCHGDAT_LAST, %d(%s)\n", MOVA_STR, offset, __regs[AR_AX]);
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_BX],
  __regs[AR_AX]);

 offset = (byte *) &(nchgp->process_enterptr) - (byte *) nchgp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
   __regs[AR_BX]);
 emit_one_insn(fp, "\tjmp    *%s\n", __regs[AR_BX]);

 /* AIV 02/12/09 - pnd0 and no nb return return here */
 if (!need_pnd0_check && !__design_has_nb_events) return;

 emit_one_insn(fp, "%s:\n", lab2);

/*
 tevp = __p0_te_hdrp;
 if (tevp != NULL) 
  {
   __p0_te_endp->tenxtp = __free_event_pnd0_tevp;
   return(tevp);
  }
*/

 if (need_pnd0_check)
  {
   emit_one_insn(fp, "\t%s   __p0_te_hdrp%s, %s\n", MOVA_STR, GBL_OFS_STR,
    __regs[AR_AX]);
   emit_one_insn(fp, "\t%s  %s, %s\n", TESTA_STR, __regs[AR_AX], __regs[AR_AX]);

   emit_one_insn(fp, "\tje     %s\n", lab1);
   tevp = __free_event_tevp;
   offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
  //AIV FIXME - make this local to the comm.s file to use address and 
  //save mem and move
   emit_one_insn(fp, "\t%s   __p0_te_endp%s, %s\n", MOVA_STR, GBL_OFS_STR,
    __regs[AR_BX]);
   emit_one_insn(fp, "\t%s   $free_event_pnd0_tev, %d(%s)\n", MOVA_STR, offset, 
    __regs[AR_BX]);

   emit_jump_to_next_event(fp, AR_AX);

   if (!__design_has_nb_events) return;

   emit_one_insn(fp, "%s:\n", lab1);
  }
/*
 if (__nb_te_endp != &__nb_dummy_hd)
  {
   tevp = __p0_te_hdrp = __nb_dummy_hd.tenxtp; 
   __p0_te_endp = __nb_te_endp;
   __nb_te_endp = &__nb_dummy_hd;
   __p0_te_endp->tenxtp = __free_event_pnd0_tevp;
   return(tevp);
  }
*/
 /* AIV 01/19/09 - if design contains no non-blocking no need to check */
 /* this - design is known to not contain nb events */
 if (!__design_has_nb_events) return;

 /* if (__nb_te_endp != &__nb_dummy_hd) */
 emit_one_insn(fp, "\t%s   __nb_te_endp, %s\n", MOVA_STR, __regs[AR_AX]);
 emit_one_insn(fp, "\t%s   $__nb_dummy_hd, %s\n", MOVA_STR, __regs[AR_BX]);
 emit_one_insn(fp, "\t%s   %s, %s\n", CMPA_STR, __regs[AR_BX], __regs[AR_AX]);
  
 emit_one_insn(fp, "\tje     move_time\n");
 /* __p0_te_endp = __nb_te_endp; */
 emit_one_insn(fp, "\t%s   %s, __p0_te_endp%s\n", MOVA_STR, __regs[AR_AX], 
  GBL_OFS_STR);

 /* AIV 09/09/08 - tevp needs to be assigned dummy value */
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
 /* __p0_te_endp->tenxtp = __free_event_pnd0_tevp; */
 emit_one_insn(fp, "\t%s   $free_event_pnd0_tev, %d(%s)\n", MOVA_STR, offset, 
  __regs[AR_AX]);
  
 /* __nb_te_endp = &__nb_dummy_hd; */
 emit_one_insn(fp, "\t%s   %s, __nb_te_endp\n", MOVA_STR, __regs[AR_BX]);
  
 /* tevp = __p0_te_hdrp = __nb_dummy_hd.tenxtp;  */
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_BX],
  __regs[AR_AX]);

 emit_one_insn(fp, "\t%s   %s, __p0_te_hdrp%s\n", MOVA_STR, __regs[AR_AX], 
   GBL_OFS_STR);

 emit_jump_to_next_event(fp, AR_AX);
}
#endif

/*
 * jump the next event __cur_tevp->tenxt
 * set idp (%esi) and go to next event
 */
static void emit_jump_to_next_event(FILE *fp, int32 tevp_reg)
{
 int32 offset;
 struct tev_t *tevp;
 const char *cp;

 cp = __regs[tevp_reg];
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->te_idp) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   %s, __cur_tevp%s\n", MOVA_STR, cp, GBL_OFS_STR);
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, cp, __regs[IDP_REG]);
 offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, cp, __regs[AR_BX]);
 emit_one_insn(fp, "\tjmp    *%s\n", __regs[AR_BX]);
}

/*
 * AIV 07/24/08 - inlined the routine to move time
 *
 * just the code from gcc -02 from __asl_move_time with added 'M' to the front
 * of gcc labels
 *
 * minor changes to the gcc code 
 *  - know that no push/pops for callee regs are needed 
 *  - instead of return just jump to the next event or non-blocking event
 *  - can remove this line which just init min = -1 in asl_loc_heapify 
 *         movl    $-1, %%esi 
 *
 * AIV 01/21/10 - rewrote these routines for better code        
 * see v_aslib.c for new __asl_move_time base c code
 */
#ifdef __CVC32__
static void emit_move_time_routine(FILE *fp)
{
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp,"move_time:\n"); 

 if (__cvc_slotend_action != 0)
  {
   /* if has pli access all different end time move to check for end time */
   /* call backs */
   /* AIV 01/07/09 - no longer a need to set processing pnd0s */
   emit_one_insn(fp, "\t%s   $0, __slotend_action\n", CMPA_STR);

   emit_one_insn(fp, "\tje   noslotend\n");
   /* AIV 11/04/08 - inlined this was a problem for 64-bit calling/ret */
   /* since there was no stack */
   /* it is better to inline these anyway must pass down the blk name */
   emit_slotend_action(fp);
   emit_one_insn(fp, "noslotend:\n");
  }

 /* AIV 11/30/09 - if all nb have the same #delay set global to NULL */
 if (__all_nb_same_time == TRUE)
  {
   emit_one_insn(fp,"\tmovl	$0, __last_nb_hp\n");
  }

 /* AIV 01/21/10 - notice no more testl since subl will set condition code */
 emit_one_insn(fp,"\
        movl	__heap, %%edx\n \
	movl	__heap_size, %%eax\n \
	movl	4(%%edx), %%edi\n \
	subl	$1, %%eax\n \
	je	.MLdone_sim\n \
	movl	(%%edx,%%eax,4), %%esi\n \
	cmpl	$2, %%eax\n \
	movl	%%eax, (%%esp)\n \
	movl	4(%%edi), %%ecx\n \
	movl	8(%%edi), %%ebx\n \
	movl	%%eax, __heap_size\n \
	movl	%%esi, 4(%%edx)\n \
	movl	%%ecx, __simtime\n \
	movl	%%ebx, __simtime+4\n \
	jle	.ML586\n \
	movl	%%esi, (%%edx)\n \
	movl	$2, %%eax\n \
	.p2align 4,,7\n \
	.p2align 3\n \
.ML591:\n \
	movl	(%%edx,%%eax,4), %%ebx\n \
	leal	1(%%eax), %%ecx\n \
	movl	4(%%ebx), %%ebp\n \
	movl	8(%%ebx), %%ebx\n \
	cmpl	%%ebx, 8(%%esi)\n \
	ja	.ML587\n \
	jb	.ML595\n \
	cmpl	%%ebp, 4(%%esi)\n \
	jbe	.ML595\n \
	.p2align 4,,7\n \
	.p2align 3\n \
.ML587:\n \
	movl	(%%edx,%%ecx,4), %%esi\n \
	cmpl	%%ebx, 8(%%esi)\n \
	.p2align 4,,2\n \
	ja	.ML589\n \
	.p2align 4,,2\n \
	jb	.ML596\n \
	cmpl	%%ebp, 4(%%esi)\n \
	.p2align 4,,2\n \
	jb	.ML596\n \
	.p2align 4,,7\n \
	.p2align 3\n \
.ML589:\n \
	shrl	%%ecx\n \
	cmpl	%%ecx, %%eax\n \
	.p2align 4,,4\n \
	je	.ML586\n \
	leal	(%%edx,%%ecx,4), %%ebx\n \
	leal	(%%edx,%%eax,4), %%ecx\n \
	movl	(%%ebx), %%esi\n \
	addl	%%eax, %%eax\n \
	movl	(%%ecx), %%ebp\n \
	cmpl	%%eax, (%%esp)\n \
	movl	%%ebp, (%%ebx)\n \
	movl	%%esi, (%%ecx)\n \
	ja	.ML591\n \
.ML586:\n \
	movl	(%%edi), %%eax\n \
	movl	28(%%edi), %%edx\n \
	movl	%%edx, __time_hash(,%%eax,4)\n \
	movl	__free_heap_ndx, %%eax\n \
	movl	__free_heap, %%edx\n \
	movl	%%edi, (%%edx,%%eax,4)\n \
	addl	$1, %%eax\n \
	movl	$__nb_dummy_hd, %%esi\n \
	movl	%%eax, __free_heap_ndx\n \
	movl	24(%%edi), %%eax\n \
	testl	%%eax, %%eax\n \
	je	.ML676\n \
	movl	20(%%edi), %%ebx\n \
	movl	12(%%edi), %%ecx\n \
	movl	%%ebx, 44(%%esi)\n \
	movl	%%eax, %%esi\n \
	testl	%%ecx, %%ecx\n \
	je	.ML679\n"); 

 emit_one_insn(fp,".ML676:\n \
	movl	12(%%edi), %%eax\n \
	movl	16(%%edi), %%ebx\n \
	movl	%%esi, __nb_te_endp\n \
	movl	%%ebx, __cur_te_endp\n \
	movl	$free_event_tev, 44(%%ebx)\n"); 
 /* time slot has event just jump to the first event */
 /* if has pli access must check for change action */
 /* __cur_tevp is known to be in %eax */
 /* AIV 05/13/09 - access level is call back */
 if (__pli_access_level >= 2) 
  {
   /* call backs from vpi cb NextSimTime (after debugger entered) */
   /* if (__have_vpi_actions) __vpi_del_nxtsimtim_trycall(); */
   /* need to save eax in ebx prior to call */
   emit_one_insn(fp, "\tmovl  %%eax, %%ebx\n");
   emit_one_insn(fp, "\tcmpl  $0, __have_vpi_actions\n");
   emit_one_insn(fp, "\tje     pliaction\n");
   emit_one_insn(fp, "\tcall   %s\n", "__vpi_del_nxtsimtim_trycall");
   emit_one_insn(fp, "\tpliaction:\n");
   emit_jump_to_next_event(fp, AR_BX);
  }
 else emit_jump_to_next_event(fp, AR_AX);

 emit_one_insn(fp,"\
	.p2align 4,,7\n \
	.p2align 3\n \
.ML595:\n \
	shrl	%%eax\n \
	movl	(%%edx,%%eax,4), %%ebx\n \
	movl	4(%%ebx), %%ebp\n \
	movl	8(%%ebx), %%ebx\n \
	jmp	.ML587\n \
	.p2align 4,,7\n \
	.p2align 3\n \
.ML596:\n \
	movl	%%ecx, %%eax\n \
	jmp	.ML589\n");
 emit_one_insn(fp,"\n \
.ML679:\n \
	movl   %%eax, __p0_te_endp\n \
	movl   $__nb_dummy_hd, __nb_te_endp\n \
	movl   $free_event_pnd0_tev, 44(%%eax)\n \
	movl   %%ebx, %%eax\n \
	movl   %%ebx, __p0_te_hdrp\n \
	movl   %%ebx, __cur_tevp\n \
	movl   32(%%eax), %%esi\n \
	movl   12(%%eax), %%ebx\n \
	jmp    *%%ebx\n"); 
 emit_one_insn(fp,".MLdone_sim:\n \
	addl   $1, __simtime\n \
	adcl   $0, __simtime\n \
	call   __done_sim\n"); 
}

static void emit_move_time_routine_nonb(FILE *fp)
{
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp,"move_time:\n"); 

 if (__cvc_slotend_action != 0)
  {
   /* if has pli access all different end time move to check for end time */
   /* call backs */
   /* AIV 01/07/09 - no longer a need to set processing pnd0s */
   emit_one_insn(fp, "\t%s   $0, __slotend_action\n", CMPA_STR);

   emit_one_insn(fp, "\tje   noslotend\n");
   /* AIV 11/04/08 - inlined this was a problem for 64-bit calling/ret */
   /* since there was no stack */
   /* it is better to inline these anyway must pass down the blk name */
   emit_slotend_action(fp);
   emit_one_insn(fp, "noslotend:\n");
  }

 /* AIV 01/21/10 - notice no more testl since subl will set condition code */
 emit_one_insn(fp,"\
        movl	__heap, %%edx\n \
	movl	__heap_size, %%eax\n \
	movl	4(%%edx), %%edi\n \
	subl	$1, %%eax\n \
	je	.MLdone_sim\n \
	movl	(%%edx,%%eax,4), %%esi\n \
	cmpl	$2, %%eax\n \
	movl	%%eax, (%%esp)\n \
	movl	4(%%edi), %%ecx\n \
	movl	8(%%edi), %%ebx\n \
	movl	%%eax, __heap_size\n \
	movl	%%esi, 4(%%edx)\n \
	movl	%%ecx, __simtime\n \
	movl	%%ebx, __simtime+4\n \
	jle	.ML586\n \
	movl	%%esi, (%%edx)\n \
	movl	$2, %%eax\n \
	.p2align 4,,7\n \
	.p2align 3\n \
.ML591:\n \
	movl	(%%edx,%%eax,4), %%ebx\n \
	leal	1(%%eax), %%ecx\n \
	movl	4(%%ebx), %%ebp\n \
	movl	8(%%ebx), %%ebx\n \
	cmpl	%%ebx, 8(%%esi)\n \
	ja	.ML587\n \
	jb	.ML595\n \
	cmpl	%%ebp, 4(%%esi)\n \
	jbe	.ML595\n \
	.p2align 4,,7\n \
	.p2align 3\n \
.ML587:\n \
	movl	(%%edx,%%ecx,4), %%esi\n \
	cmpl	%%ebx, 8(%%esi)\n \
	.p2align 4,,2\n \
	ja	.ML589\n \
	.p2align 4,,2\n \
	jb	.ML596\n \
	cmpl	%%ebp, 4(%%esi)\n \
	.p2align 4,,2\n \
	jb	.ML596\n \
	.p2align 4,,7\n \
	.p2align 3\n \
.ML589:\n \
	shrl	%%ecx\n \
	cmpl	%%ecx, %%eax\n \
	.p2align 4,,4\n \
	je	.ML586\n \
	leal	(%%edx,%%ecx,4), %%ebx\n \
	leal	(%%edx,%%eax,4), %%ecx\n \
	movl	(%%ebx), %%esi\n \
	addl	%%eax, %%eax\n \
	movl	(%%ecx), %%ebp\n \
	cmpl	%%eax, (%%esp)\n \
	movl	%%ebp, (%%ebx)\n \
	movl	%%esi, (%%ecx)\n \
	ja	.ML591\n \
.ML586:\n \
	movl	(%%edi), %%eax\n \
	movl	28(%%edi), %%edx\n \
	movl	%%edx, __time_hash(,%%eax,4)\n \
	movl	__free_heap_ndx, %%eax\n \
	movl	__free_heap, %%edx\n \
	movl	%%edi, (%%edx,%%eax,4)\n \
	addl	$1, %%eax\n \
	movl	%%eax, __free_heap_ndx\n");

 emit_one_insn(fp,"\
	movl	12(%%edi), %%eax\n \
	movl	16(%%edi), %%ebx\n \
	movl	%%ebx, __cur_te_endp\n \
	movl	$free_event_tev, 44(%%ebx)\n"); 
 /* time slot has event just jump to the first event */
 /* if has pli access must check for change action */
 /* __cur_tevp is known to be in %eax */
 /* AIV 05/13/09 - access level is call back */
 if (__pli_access_level >= 2) 
  {
   /* call backs from vpi cb NextSimTime (after debugger entered) */
   /* if (__have_vpi_actions) __vpi_del_nxtsimtim_trycall(); */
   /* need to save eax in ebx prior to call */
   emit_one_insn(fp, "\tmovl  %%eax, %%ebx\n");
   emit_one_insn(fp, "\tcmpl  $0, __have_vpi_actions\n");
   emit_one_insn(fp, "\tje     pliaction\n");
   emit_one_insn(fp, "\tcall   %s\n", "__vpi_del_nxtsimtim_trycall");
   emit_one_insn(fp, "\tpliaction:\n");
   emit_jump_to_next_event(fp, AR_BX);
  }
 else emit_jump_to_next_event(fp, AR_AX);

 emit_one_insn(fp,"\
	.p2align 4,,7\n \
	.p2align 3\n \
.ML595:\n \
	shrl	%%eax\n \
	movl	(%%edx,%%eax,4), %%ebx\n \
	movl	4(%%ebx), %%ebp\n \
	movl	8(%%ebx), %%ebx\n \
	jmp	.ML587\n \
	.p2align 4,,7\n \
	.p2align 3\n \
.ML596:\n \
	movl	%%ecx, %%eax\n \
	jmp	.ML589\n");
 emit_one_insn(fp,".MLdone_sim:\n \
	addl   $1, __simtime\n \
	adcl   $0, __simtime\n \
	call   __done_sim\n"); 
}

#else
static void emit_move_time_routine(FILE *fp)
{
 struct tev_t *tevp;
 int32 offset, offset2;

 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp,"move_time:\n"); 
 emit_one_insn(fp,"\t.cfi_startproc\n"); 

 if (__cvc_slotend_action != 0)
  {
   /* if has pli access all different end time move to check for end time */
   /* call backs */
   /* AIV 01/07/09 - no longer a need to set processing pnd0s */
   /* __processing_pnd0s = FALSE; */

   emit_one_insn(fp, "\t%s   $0, __slotend_action\n", CMPA_STR);

   emit_one_insn(fp, "\tje   noslotend\n");
   /* AIV 11/04/08 - inlined this was a problem for 64-bit calling/ret */
   /* since there was no stack */
   /* it is better to inline these anyway must pass down the blk name */
   emit_slotend_action(fp);
   emit_one_insn(fp, "noslotend:\n");
  }

 /* AIV 11/30/09 - if all nb have the same #delay set global to NULL */
 if (__all_nb_same_time == TRUE)
  {
   emit_one_insn(fp,"\tmovq	$0, __last_nb_hp(%%rip)\n");
  }

 /* AIV 01/21/10 - notice no more testl since subl will set condition code */
 emit_one_insn(fp,"\
	movq	__heap(%%rip), %%rdx\n \
	movl	__heap_size(%%rip), %%r9d\n \
	movq	8(%%rdx), %%r8\n \
	subl	$1, %%r9d\n \
	je	.MLdone_sim\n \
	movl	%%r9d, __heap_size(%%rip)\n \
	cmpl	$2, %%r9d\n \
	movq	8(%%r8), %%rax\n \
	movq	%%rax, __simtime(%%rip)\n \
	movslq	%%r9d, %%rax\n \
	movq	(%%rdx,%%rax,8), %%rdi\n \
	movq	%%rdi, 8(%%rdx)\n \
	jle	.ML663\n \
	movq	%%rdi, (%%rdx)\n \
	movl	$2, %%eax\n \
	.p2align 4,,10\n \
	.p2align 3\n \
.ML582:\n \
	mov	%%eax, %%esi\n \
	leal	1(%%rax), %%ecx\n \
	movq	(%%rdx,%%rsi,8), %%rsi\n \
	movq	8(%%rsi), %%rsi\n \
	cmpq	%%rsi, 8(%%rdi)\n \
	ja	.ML580\n \
	shrl	%%eax\n \
	mov	%%eax, %%esi\n \
	movq	(%%rdx,%%rsi,8), %%rsi\n \
	movq	8(%%rsi), %%rsi\n \
.ML580:\n \
	mov	%%ecx, %%edi\n \
	movq	(%%rdx,%%rdi,8), %%rdi\n \
	cmpq	%%rsi, 8(%%rdi)\n \
	cmovb	%%ecx, %%eax\n \
	shrl	%%ecx\n \
	cmpl	%%ecx, %%eax\n \
	je	.ML663\n \
	mov	%%ecx, %%ecx\n \
	leaq	(%%rdx,%%rcx,8), %%rsi\n \
	mov	%%eax, %%ecx\n \
	addl	%%eax, %%eax\n \
	leaq	(%%rdx,%%rcx,8), %%rcx\n \
	cmpl	%%r9d, %%eax\n \
	movq	(%%rsi), %%rdi\n \
	movq	(%%rcx), %%r10\n \
	movq	%%r10, (%%rsi)\n \
	movq	%%rdi, (%%rcx)\n \
	jb	.ML582\n \
.ML663:\n \
	movslq	(%%r8),%%rdx\n \
	movq	48(%%r8), %%rax\n \
	movq	%%rax, __time_hash(,%%rdx,8)\n \
	movl	__free_heap_ndx(%%rip), %%eax\n \
	movq	__free_heap(%%rip), %%rdx\n \
	movslq	%%eax,%%rcx\n \
	addl	$1, %%eax\n \
	movq	%%r8, (%%rdx,%%rcx,8)\n \
	movq	40(%%r8), %%rdx\n \
	movl	%%eax, __free_heap_ndx(%%rip)\n \
	testq	%%rdx, %%rdx\n \
	je	.ML681\n \
	movq	32(%%r8), %%rax\n \
	movq	%%rdx, __nb_te_endp(%%rip)\n \
	movq	%%rax, __nb_dummy_hd+72(%%rip)\n \
	cmpq	$0, 16(%%r8)\n \
	je	.ML682\n \
.ML676:\n \
	movq	24(%%r8), %%rdx\n \
	movq	16(%%r8), %%rax\n \
	movq	$free_event_tev, 72(%%rdx)\n \
	movq	%%rdx, __cur_te_endp(%%rip)\n"); 
 /* AIV 02/13/09 - removed the need to use/set __cur_te_hdrp */
 /* time slot has event just jump to the first event */
 /* if has pli access must check for change action */
 /* __cur_tevp is known to be in %eax */
 /* AIV 05/13/09 - access level is call back */
 if (__pli_access_level >= 2) 
  {
   /* call backs from vpi cb NextSimTime (after debugger entered) */
   /* if (__have_vpi_actions) __vpi_del_nxtsimtim_trycall(); */
   /* need to save eax in ebx prior to call */
   emit_one_insn(fp, "\tmovq  %%rax, %%rbx\n");
   emit_one_insn(fp, "\tcmpl  $0, __have_vpi_actions\n");
   emit_one_insn(fp, "\tje     pliaction\n");
   emit_one_insn(fp, "\tcall   %s\n", "__vpi_del_nxtsimtim_trycall");
   emit_one_insn(fp, "\tpliaction:\n");
   emit_jump_to_next_event(fp, AR_BX);
  }
 else emit_jump_to_next_event(fp, AR_AX);

 emit_one_insn(fp,"\
.ML681:\n \
	movq	$__nb_dummy_hd, __nb_te_endp(%%rip)\n \
	jmp	.ML676\n \
.ML682:\n ");

 /* time event only contains non-blocking events just jump to first nb event */
 /* first event is known to be in %rdx */
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
 /* AIV 01/07/09 - no longer a need to set processing pnd0s */
 emit_one_insn(fp,"\
	movq   %%rdx, __p0_te_endp(%%rip)\n \
	movq   $__nb_dummy_hd, __nb_te_endp(%%rip)\n \
	movq   $free_event_pnd0_tev, %d(%%rdx)\n \
	movq   __nb_dummy_hd + %d, %%rax\n", offset, offset);

 offset = (byte *) &(tevp->te_idp) - (byte *) tevp;
 offset2 = (byte *) &(tevp->enterptr) - (byte *) tevp;
 emit_one_insn(fp,"\
	movq  %%rax, __p0_te_hdrp(%%rip)\n \
	movq  %%rax, __cur_tevp(%%rip)\n \
	movq  %d(%%rax), %s\n \
	movq  %d(%%rax), %%rbx\n \
	jmp   *%%rbx\n", offset, __regs[IDP_REG], offset2);
 emit_one_insn(fp,".MLdone_sim:\n \
        addq   $1, __simtime(%%rip)\n \
	call   __done_sim\n"); 
 emit_one_insn(fp,"\
       .cfi_endproc\n"); 
}

static void emit_move_time_routine_nonb(FILE *fp)
{

 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp,"move_time:\n"); 
 emit_one_insn(fp,"\t.cfi_startproc\n"); 

 if (__cvc_slotend_action != 0)
  {
   /* if has pli access all different end time move to check for end time */
   /* call backs */
   /* AIV 01/07/09 - no longer a need to set processing pnd0s */
   /* __processing_pnd0s = FALSE; */

   emit_one_insn(fp, "\t%s   $0, __slotend_action\n", CMPA_STR);

   emit_one_insn(fp, "\tje   noslotend\n");
   /* AIV 11/04/08 - inlined this was a problem for 64-bit calling/ret */
   /* since there was no stack */
   /* it is better to inline these anyway must pass down the blk name */
   emit_slotend_action(fp);
   emit_one_insn(fp, "noslotend:\n");
  }

 /* AIV 01/21/10 - notice no more testl since subl will set condition code */
 emit_one_insn(fp,"\
	movq	__heap(%%rip), %%rdx\n \
	movl	__heap_size(%%rip), %%r9d\n \
	movq	8(%%rdx), %%r8\n \
	subl	$1, %%r9d\n \
	je	.MLdone_sim\n \
	movl	%%r9d, __heap_size(%%rip)\n \
	cmpl	$2, %%r9d\n \
	movq	8(%%r8), %%rax\n \
	movq	%%rax, __simtime(%%rip)\n \
	movslq	%%r9d, %%rax\n \
	movq	(%%rdx,%%rax,8), %%rdi\n \
	movq	%%rdi, 8(%%rdx)\n \
	jle	.ML663\n \
	movq	%%rdi, (%%rdx)\n \
	movl	$2, %%eax\n \
	.p2align 4,,10\n \
	.p2align 3\n \
.ML582:\n \
	mov	%%eax, %%esi\n \
	leal	1(%%rax), %%ecx\n \
	movq	(%%rdx,%%rsi,8), %%rsi\n \
	movq	8(%%rsi), %%rsi\n \
	cmpq	%%rsi, 8(%%rdi)\n \
	ja	.ML580\n \
	shrl	%%eax\n \
	mov	%%eax, %%esi\n \
	movq	(%%rdx,%%rsi,8), %%rsi\n \
	movq	8(%%rsi), %%rsi\n \
.ML580:\n \
	mov	%%ecx, %%edi\n \
	movq	(%%rdx,%%rdi,8), %%rdi\n \
	cmpq	%%rsi, 8(%%rdi)\n \
	cmovb	%%ecx, %%eax\n \
	shrl	%%ecx\n \
	cmpl	%%ecx, %%eax\n \
	je	.ML663\n \
	mov	%%ecx, %%ecx\n \
	leaq	(%%rdx,%%rcx,8), %%rsi\n \
	mov	%%eax, %%ecx\n \
	addl	%%eax, %%eax\n \
	leaq	(%%rdx,%%rcx,8), %%rcx\n \
	cmpl	%%r9d, %%eax\n \
	movq	(%%rsi), %%rdi\n \
	movq	(%%rcx), %%r10\n \
	movq	%%r10, (%%rsi)\n \
	movq	%%rdi, (%%rcx)\n \
	jb	.ML582\n \
.ML663:\n \
	movslq	(%%r8),%%rdx\n \
	movq	48(%%r8), %%rax\n \
	movq	%%rax, __time_hash(,%%rdx,8)\n \
	movl	__free_heap_ndx(%%rip), %%eax\n \
	movq	__free_heap(%%rip), %%rdx\n \
	movslq	%%eax,%%rcx\n \
	addl	$1, %%eax\n \
	movq	%%r8, (%%rdx,%%rcx,8)\n \
	movl	%%eax, __free_heap_ndx(%%rip)\n \
	movq	24(%%r8), %%rdx\n \
	movq	16(%%r8), %%rax\n \
	movq	$free_event_tev, 72(%%rdx)\n \
	movq	%%rdx, __cur_te_endp(%%rip)\n"); 
 /* AIV 02/13/09 - removed the need to use/set __cur_te_hdrp */
 /* time slot has event just jump to the first event */
 /* if has pli access must check for change action */
 /* __cur_tevp is known to be in %eax */
 /* AIV 05/13/09 - access level is call back */
 if (__pli_access_level >= 2) 
  {
   /* call backs from vpi cb NextSimTime (after debugger entered) */
   /* if (__have_vpi_actions) __vpi_del_nxtsimtim_trycall(); */
   /* need to save eax in ebx prior to call */
   emit_one_insn(fp, "\tmovq  %%rax, %%rbx\n");
   emit_one_insn(fp, "\tcmpl  $0, __have_vpi_actions\n");
   emit_one_insn(fp, "\tje     pliaction\n");
   emit_one_insn(fp, "\tcall   %s\n", "__vpi_del_nxtsimtim_trycall");
   emit_one_insn(fp, "\tpliaction:\n");
   emit_jump_to_next_event(fp, AR_BX);
  }
 else emit_jump_to_next_event(fp, AR_AX);

 /* AIV 07/28/10 - removed unreachable code - should have been removed */
 /* for this nonb version */
 emit_one_insn(fp,".MLdone_sim:\n \
        addq   $1, __simtime(%%rip)\n \
	call   __done_sim\n"); 
 emit_one_insn(fp,"\
        .cfi_endproc\n"); 
        
}
#endif

 
/*
 * emit the assembly code to jump to the next event
 */
static void emit_next_event(FILE *fp)
{
 struct tev_t *tevp;
 int32 offset;

 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->tenxtp) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
   __regs[AR_AX]);

 offset = (byte *) &(tevp->te_idp) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   %s, __cur_tevp%s\n", MOVA_STR, __regs[AR_AX], GBL_OFS_STR);

 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
  __regs[IDP_REG]);

 offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_BX]);
 emit_one_insn(fp, "\tjmp    *%s\n", __regs[AR_BX]);
}

/*
 * emit the assembly code to handle the allocated tev_t
 * which may need to be generated a runtime if the static event is 
 * in use
 * - basically code comes from gcc -O2 - put this need to jump to next event
 * to avoid using the stack
 *
 * if is_nbmem free a non-blocking with malloced memory in tevp->tu.rhs_wp
 */
//AIV - this would be better code with using realloc instead of __my_realloc
//also don't jump back if realloc code fall thru after adding node
#ifdef __CVC32__
static void emit_free_next_event(FILE *fp, int32 is_nbmem)
{
 struct tev_t *tevp;
 char s1[RECLEN], lab1[10], lab2[10];
 int32 offset;

 if (is_nbmem) 
  {
   strcpy(s1, "NEXT_FREE_NBMEM_EV");
   strcpy(lab1, ".LNB1");
   strcpy(lab2, ".LNB2");
  }
 else 
  {
   strcpy(s1, "NEXT_FREE_EV");
   strcpy(lab1, ".LF1");
   strcpy(lab2, ".LF2");
  }

 emit_one_insn(fp, "\t.text\n");
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp, ".globl %s\n", s1);
 emit_one_insn(fp, "%s:\n", s1);

 /* notice __cur_tevp is always known to be in %eax here */
 /*  emit_one_insn(fp,"\tmovl	__cur_tevp, %%ecx\n");  */
 emit_one_insn(fp,"\tmovl	%%eax, %%ecx\n"); 

 emit_one_insn(fp,"\tmovl	__free_tev_ndx, %%edx\n");
 emit_one_insn(fp,"\tcmpl	__free_tev_size, %%edx\n");
 emit_one_insn(fp,"\tmovl	44(%%ecx), %%ebx\n");
 emit_one_insn(fp,"\tje	%s\n", lab2);
 emit_one_insn(fp,"%s:\n", lab1);
 emit_one_insn(fp,"\tmovl	__free_tevs, %%eax\n");
 emit_one_insn(fp,"\tmovl	%%ecx, (%%eax,%%edx,4)\n");
 emit_one_insn(fp,"\tleal	1(%%edx), %%eax\n");
 emit_one_insn(fp,"\tmovl	%%eax, __free_tev_ndx\n");
 emit_one_insn(fp,"\tmovl	32(%%ebx), %%esi\n");
 emit_one_insn(fp,"\tmovl	%%ebx, __cur_tevp\n");

 /* if nonblocking need to free the rhs memory for this alloc event */
 tevp = __free_event_tevp;
 if (is_nbmem) 
  {
   /* AIV 02/12/10 - removed pushl for passing args here */
   /* need to keep stack align for OSX */
   offset = (byte *) &(tevp->t2u.nb_rhs_size) - (byte *) tevp;
   emit_one_insn(fp,"\tmovl   %d(%%ecx), %%eax\n", offset);
   emit_one_insn(fp,"\tmovl   %%eax, 4(%%esp)\n");
   offset = (byte *) &(tevp->tu.rhs_wp) - (byte *) tevp;
   /* DBG remove -- */
   if (offset != WRDBYTES) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   emit_one_insn(fp, "\tmovl   %d(%%ecx), %%eax\n", offset);
   emit_one_insn(fp,"\tmovl     %%eax, (%%esp)\n");
   emit_one_insn(fp,"\tcall	__my_free\n");
  }
 offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
 emit_one_insn(fp,"\tmovl	%%ebx, %%eax\n");
 emit_one_insn(fp, "\tmovl   %d(%%ebx), %%ecx\n", offset);
 emit_one_insn(fp, "\tjmp    *%%ecx\n");

 /* AIV 02/12/10 - removed pushl for passing args here */
 /* need to keep stack align for OSX */
 emit_one_insn(fp,"%s:\n", lab2);
 emit_one_insn(fp,"\tmovl	%%edx, %%eax\n");
 emit_one_insn(fp,"\tshrl	$31, %%eax\n");
 emit_one_insn(fp,"\taddl	%%edx, %%eax\n");
 emit_one_insn(fp,"\tsarl	%%eax\n");
 emit_one_insn(fp,"\tleal	(%%edx,%%eax), %%eax\n");
 emit_one_insn(fp,"\tmovl	%%eax, __free_tev_size\n");
 emit_one_insn(fp,"\tsall	$2, %%eax\n");
 emit_one_insn(fp,"\tmovl       %%eax, 8(%%esp)\n");
 emit_one_insn(fp,"\tleal	0(,%%edx,4), %%eax\n");
 emit_one_insn(fp,"\tmovl       %%eax, 4(%%esp)\n");
 emit_one_insn(fp,"\tmovl	__free_tevs, %%eax\n");
 emit_one_insn(fp,"\tmovl       %%eax, (%%esp)\n");
 emit_one_insn(fp,"\tcall	__my_realloc\n");
 emit_one_insn(fp,"\taddl	$12, %%esp\n");
 emit_one_insn(fp,"\tmovl	__cur_tevp, %%ecx\n");
 emit_one_insn(fp,"\tmovl	__free_tev_ndx, %%edx\n");
 emit_one_insn(fp,"\tmovl	%%eax, __free_tevs\n");
 emit_one_insn(fp,"\tjmp	%s\n", lab1);
}
#else
static void emit_free_next_event(FILE *fp, int32 is_nbmem)
{
 struct tev_t *tevp;
 char s1[RECLEN], lab1[10], lab2[10];
 int32 offset;

 if (is_nbmem) 
  {
   strcpy(s1, "NEXT_FREE_NBMEM_EV");
   strcpy(lab1, ".LNB1");
   strcpy(lab2, ".LNB2");
  }
 else 
  {
   strcpy(s1, "NEXT_FREE_EV");
   strcpy(lab1, ".LF1");
   strcpy(lab2, ".LF2");
  }

 emit_one_insn(fp, "\t.text\n");
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 emit_one_insn(fp, ".globl %s\n", s1);
 emit_one_insn(fp, "%s:\n", s1);

 /* notice __cur_tevp is always known to be in %eax here */
 /*  emit_one_insn(fp,"\tmovl	__cur_tevp, %%ecx\n");  */
 emit_one_insn(fp,"\tmovq	%%rax, %%rsi\n"); 

 emit_one_insn(fp, "\tmovl	__free_tev_ndx(%%rip), %%ecx\n");
 emit_one_insn(fp, "\tcmpl	__free_tev_size(%%rip), %%ecx\n");
 emit_one_insn(fp, "\tmovq	72(%%rsi), %%rbx\n");
 emit_one_insn(fp, "\tje	%s\n", lab2);
 emit_one_insn(fp, "%s:\n", lab1);
 emit_one_insn(fp, "\tmovq	__free_tevs(%%rip), %%rax\n");
 emit_one_insn(fp, "\tmovslq	%%ecx,%%rdx\n");
 emit_one_insn(fp, "\tmovq	%%rsi, (%%rax,%%rdx,8)\n");
 emit_one_insn(fp, "\tleal	1(%%rcx), %%eax\n");
 emit_one_insn(fp, "\tmovq	%%rbx, __cur_tevp(%%rip)\n");
 emit_one_insn(fp, "\tmovl	%%eax, __free_tev_ndx(%%rip)\n");
 emit_one_insn(fp, "\tmovq	56(%%rbx), %%rax\n");
 /* AIV 11/06/08 - put idp into idp reg %r15 */
 emit_one_insn(fp, "\tmovq	%%rax, %s\n", __regs[IDP_REG]);

 /* if nonblocking need to free the rhs memory for this alloc event */
 tevp = __free_event_tevp;
 if (is_nbmem) 
  {
   offset = (byte *) &(tevp->tu.rhs_wp) - (byte *) tevp;
   emit_one_insn(fp, "\tmovq   %d(%%rsi), %%rdi\n", offset);
   offset = (byte *) &(tevp->t2u.nb_rhs_size) - (byte *) tevp;
   emit_one_insn(fp, "\tmovslq   %d(%%rsi), %%rsi\n", offset);
   emit_one_insn(fp,"\tcall	__my_free\n");
  }
 offset = (byte *) &(tevp->enterptr) - (byte *) tevp;
 emit_one_insn(fp, "\tmovq	%%rbx, %%rax\n");
 emit_one_insn(fp, "\tmovq   %d(%%rbx), %%rcx\n", offset);
 emit_one_insn(fp, "\tjmp    *%%rcx\n");


 emit_one_insn(fp, "%s:\n", lab2);
 emit_one_insn(fp, "\tmovl	%%ecx, %%edx\n");
 emit_one_insn(fp, "\tmovq	__free_tevs(%%rip), %%rdi\n");
 emit_one_insn(fp, "\tmovslq	%%ecx,%%rsi\n");
 emit_one_insn(fp, "\tshrl	$31, %%edx\n");
 emit_one_insn(fp, "\tsalq	$3, %%rsi\n");
 emit_one_insn(fp, "\taddl	%%ecx, %%edx\n");
 emit_one_insn(fp, "\tsarl	%%edx\n");
 emit_one_insn(fp, "\taddl	%%ecx, %%edx\n");
 emit_one_insn(fp, "\tmovl	%%edx, __free_tev_size(%%rip)\n");
 emit_one_insn(fp, "\tmovslq	%%edx,%%rdx\n");
 emit_one_insn(fp, "\tsalq	$3, %%rdx\n");
 emit_one_insn(fp, "\tcall	__my_realloc\n");
 emit_one_insn(fp, "\tmovq	__cur_tevp(%%rip), %%rsi\n");
 emit_one_insn(fp, "\tmovl	__free_tev_ndx(%%rip), %%ecx\n");
 emit_one_insn(fp, "\tmovq	%%rax, __free_tevs(%%rip)\n");
 emit_one_insn(fp, "\tjmp	%s\n", lab1);
}
#endif

/*
 * emit a wrapper call to the processing code
 * need a wrapper to jump to the next event without using the stack
 */
static void emit_wrapper_routine(FILE *fp, char *wrapper, char *call, 
 int32 reset_suspend, int32 is_global)
{
 int32 offset;
 struct tev_t *tevp;

 /* gate acc change wrapper */
 emit_one_insn(fp, "\t%s\n", ALIGN_FUNC_STR);
 /* AIV 08/05/09 - some of these are local */
 if (is_global)
  {
   emit_one_insn(fp, ".globl %s\n", wrapper);
  }
 else
  {
   emit_one_insn(fp, ".local %s\n", wrapper);
  }
 emit_one_insn(fp, "%s:\n", wrapper);
 /* AIV 01/5/08 - must set __idp here these wrappers may use */
 emit_one_insn(fp, "\t%s   %s, __idp%s\n", MOVA_STR, __regs[IDP_REG], GBL_OFS_STR);
 if (call != NULL)
  {
   emit_one_insn(fp, "\tcall   %s\n", call);
  }
 /* currently only __process_compiled_thrd_ev needs to reset stmt_suspend */
 /* AIV LOOKATME - think this is only needed for some debugging????? */
//SJM???????
 if (reset_suspend)
  {
   emit_one_insn(fp, "\t%s   $0, __stmt_suspend\n", MOVA_STR);
  }
 tevp = __free_event_tevp;
 offset = (byte *) &(tevp->trigger) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   __cur_tevp%s, %s\n", MOVA_STR, GBL_OFS_STR, __regs[AR_AX]);

 /* __cur_tevp->trigger = FALSE */
 emit_one_insn(fp, "\t%s   $0, %d(%s)\n", MOVA_STR, offset, __regs[AR_AX]);

 offset = (byte *) &(tevp->next_enterptr) - (byte *) tevp;
 emit_one_insn(fp, "\t%s   %d(%s), %s\n", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_BX]);
 emit_one_insn(fp, "\tjmp    *%s\n", __regs[AR_BX]);
}

/*
 * create the slot end action boiler plate from the design information
 * the design is known to have a certain slot end actions it can have
 * this handles all possible slotend action calls
 *
 * SJM 06-30-13 - notice slot end action used during compilation to
 * make sure right code gets emitted in binary - but it is a pun because
 * slot end action used for recording and changing state during simulation too
 */
static void emit_slotend_action(FILE *fp)
{
 int32 num_options, action, i, monit_action;
 int32 action_types[20];
 char do_other[RECLEN], skip_other[RECLEN];
 char *creg_cp;

 num_options = FALSE;

 /* there are no slotend actions in this design return */
 if (__cvc_slotend_action == 0) return;

 if (__show_asm)
  {
   __my_fprintf(fp, "#================================================\n");
   __my_fprintf(fp,
     "# MISC DESIGN SPECIFIC SLOT END MOSTLY FIXED BOILER PLATE\n");
   __my_fprintf(fp, "#================================================\n");
  }
 /* get all the possible actions */
 action = __cvc_slotend_action;
 if ((action & SE_TCHK_VIOLATION) != 0) 
  {
   action_types[num_options] = SE_TCHK_VIOLATION;
   num_options++;
  }
 if ((action & SE_DUMPVARS) != 0) 
  {
   action_types[num_options] = SE_DUMPVARS;
   num_options++;
  }
 if ((action & SE_DUMPPORTS) != 0) 
  {
   action_types[num_options] = SE_DUMPPORTS;
   num_options++;
  }
 if ((action & SE_MONIT_TRIGGER) != 0) 
  {
   action_types[num_options] = SE_MONIT_TRIGGER;
   num_options++;
  }
 if ((action & SE_MONIT_CHG) != 0) 
  {
   action_types[num_options] = SE_MONIT_CHG;
   num_options++;
  }
 if ((action & SE_FMONIT_TRIGGER) != 0) 
  {
   action_types[num_options] = SE_FMONIT_TRIGGER;
   num_options++;
  }
 if ((action & SE_STROBE) != 0) 
  {
   action_types[num_options] = SE_STROBE;
   num_options++;
  }
 if ((action & SE_TOGGLE) != 0) 
  {
   action_types[num_options] = SE_TOGGLE;
   num_options++;
  }

 /* AIV FIXME - this can be known for PLI access scheme */
 /* for now assume pli may add either of these actions */
 /* AIV 05/13/09 - access level > 2 for sync code */
 if (__pli_access_level >= 2)
  {
   //SE_TFROSYNC and SE_VPIROSYNC
   action_types[num_options] = SE_TFROSYNC;
   num_options++;
   action_types[num_options] = SE_VPIROSYNC;
   num_options++;
  }
 
 /* DBG remove -- */ 
 if (num_options == 0)  __misc_terr(__FILE__, __LINE__);
 /* ----- */ 


 /* monit is a special two possible action case */
 monit_action = (SE_MONIT_TRIGGER | SE_MONIT_CHG);
 /* only one action no need to check is the only possible action */
 if (num_options == 1)
  {
   action = action_types[0];
   emit_slotend_action_call(fp, action, TRUE, -1);
  }
 else if (num_options == 2)
  {
   /* if (action one) 
    *  { 
    *   do action one
    *   if (action two) do it
    *  }
    * else { do action two }
    */
   emit_one_insn(fp, "\t%s\t__slotend_action, %s\n", MOVA_STR, __regs[AR_AX]); 

   action = action_types[0];
   /* check for first action if not set must be doing second action */
   if ((action & monit_action) != 0)
    {
     emit_one_insn(fp, "\t%s\t$%d, %s\n", ANDA_STR, monit_action, __regs[AR_AX]); 
    }
   else emit_one_insn(fp, "\t%s\t$%d, %s\n", ANDA_STR, action, __regs[AR_AX]); 
   emit_one_insn(fp, "\t%s\t%s, %s\n", TESTA_STR, __regs[AR_AX], __regs[AR_AX]); 

   sprintf(do_other, "slotend_do_other");
   emit_one_insn(fp, "\tje\t%s\n", do_other);
   emit_slotend_action_call(fp, action, FALSE, -1);

   /* check the second slot option */
   action = action_types[1];
   emit_one_insn(fp, "\t%s\t__slotend_action, %s\n", MOVA_STR, __regs[AR_AX]); 

   if ((action & monit_action) != 0)
    {
     emit_one_insn(fp, "\t%s\t$%d, %s\n", ANDA_STR, monit_action, __regs[AR_AX]); 
    }
   else emit_one_insn(fp, "\t%s\t$%d, %s\n", ANDA_STR, action, __regs[AR_AX]); 

   emit_one_insn(fp, "\t%s\t%s, %s\n", TESTA_STR, __regs[AR_AX], __regs[AR_AX]); 
   sprintf(skip_other, "slotend_skip_other");
   emit_one_insn(fp, "\tje\t%s\n", skip_other);

   emit_one_insn(fp, "%s:\n", do_other);
   emit_slotend_action_call(fp, action, FALSE, -1);
   emit_one_insn(fp, "%s:\n", skip_other);
  }
 else 
  {
   /* AIV 03/31/09 - this needs to use %edi - %ebx - is used by monitor */
   /* code so was being overwritten - must loaded into %edi */
   /* AIV 03/31/09 - also no reason to push/pop %edi/ebx */
   /* greater than two options */
   /* load the slotend action into callee save reg %edi and do all the calls */
   /* AIV 04/02/09 - 64-bit cannot use edi - not callee saved reg */
#ifdef __CVC32__
  creg_cp = __regs[EDI];
#else
  creg_cp = __regs[R12];
#endif
   emit_one_insn(fp, "\t%s\t__slotend_action, %s\n", MOVA_STR, creg_cp); 
   for (i = 0; i < num_options; i++)
    {
     action = action_types[i];
     emit_one_insn(fp, "\t%s\t%s, %s\n", MOVA_STR, creg_cp, __regs[AR_AX]); 

     if ((action & monit_action) != 0)
      {
       emit_one_insn(fp, "\t%s\t$%d, %s\n", ANDA_STR, monit_action, __regs[AR_AX]); 
      }
     else emit_one_insn(fp, "\t%s\t$%d, %s\n", ANDA_STR, action, __regs[AR_AX]); 

     emit_one_insn(fp, "\t%s\t%s, %s\n", TESTA_STR, __regs[AR_AX], __regs[AR_AX]); 

     emit_one_insn(fp, "\tje\tslota_%d\n", i);
     /* last item needs an extra label if monitor */
     if ((i+1) == num_options)
      {
       emit_slotend_action_call(fp, action, FALSE, -1);
      }
     else emit_slotend_action_call(fp, action, FALSE, i);
     emit_one_insn(fp, "slota_%d:\n", i);
    }
  }
 /* AIV 01/26/11 - this should be movq for 64-bit since it is a word */
 /* this was ok otherwise since mask < 32 - but should zero word here */
#ifdef __CVC32__
 emit_one_insn(fp, "\tmovl   $0, __slotend_action\n"); 
#else
 emit_one_insn(fp, "\tmovq   $0, __slotend_action\n"); 
#endif
}

/*
 * created call for action type
 * monitor is handled as special case
 */
static void emit_slotend_action_call(FILE *fp, int32 type, int32 check_monit,
 int32 slot_ndx)
{
 switch (type) {
  case SE_TCHK_VIOLATION:
   emit_one_insn(fp, "\tcall\t__process_all_tchk_violations\n");
   break;
  case SE_DUMPVARS:
   emit_one_insn(fp, "\tcall\t__exec_slotend_dv\n"); 
   break;
  case SE_TOGGLE:
   emit_one_insn(fp, "\tcall\t__process_all_toggle_coverage\n"); 
   break;
  case SE_DUMPPORTS:
   emit_one_insn(fp, "\tcall\t__exec_slotend_dp\n"); 
   break;
  case SE_FMONIT_TRIGGER:
   emit_one_insn(fp, "\tcall\t__exec_fmonits\n"); 
   break;
  case SE_STROBE:
   emit_one_insn(fp, "\tcall\t__exec_strobes\n"); 
   break;
  case SE_MONIT_TRIGGER:
  case SE_MONIT_CHG:
   emit_slotend_monit_code(fp, check_monit, slot_ndx);
   break;
  case SE_TFROSYNC:
   emit_one_insn(fp, "\tcall\t__exec_rosync_misctf\n"); 
   break;
  case SE_VPIROSYNC:
   emit_one_insn(fp, "\tcall\t__vpi_del_rosync_call\n"); 
   break;
 }
}

/*
 * monitor is special case has to also check __monit_active flag 
 */
static void emit_slotend_monit_code(FILE *fp, int32 check_monit, int32 slot_ndx)
{
 char monit_skip[RECLEN];
#ifndef __CVC32__
 int32 reg;
#endif

 /* AIV 03/31/09 - if slota >= 3 slotend action jump to the next index */
 if (slot_ndx == -1)
  {
   sprintf(monit_skip, "slotend_monit_skip");
  }
 else
  {
   sprintf(monit_skip, "slota_%d", slot_ndx+1);
  }
 /* check __monit_active = TRUE */
 emit_one_insn(fp, "\tmovl\t__monit_active, %%ebx\n"); 
 emit_one_insn(fp, "\ttestl\t%%ebx, %%ebx\n");
 emit_one_insn(fp, "\tje\t%s\n", monit_skip);

#ifdef __CVC32__
 /* action & (SE_MONIT_TRIGGER | SE_MONIT_CHG) */
 emit_one_insn(fp, "\tmovl\t__slotend_action, %%eax\n"); 
 if (check_monit)
  {
   emit_one_insn(fp, "\tandl\t$%d, %%eax\n", (SE_MONIT_TRIGGER | SE_MONIT_CHG));
   emit_one_insn(fp, "\ttestl\t%%eax, %%eax\n");
   emit_one_insn(fp, "\tje\t%s\n", monit_skip);
  }

 /* shutoff the SE_MONIT_TRIGGER if on */
 emit_one_insn(fp, "\txorl\t$%d, %%eax\n", SE_MONIT_TRIGGER);

 /* AIV 02/14/10 - removed pushl for passing args here */
 /* need to keep stack align for OSX */
 emit_one_insn(fp, "\tmovl\t%%eax, 4(%%esp)\n"); 
 emit_one_insn(fp, "\tmovl\t__monit_dcehdr, %%ebx\n"); 
 emit_one_insn(fp, "\tmovl\t%%ebx, (%%esp)\n"); 
 emit_one_insn(fp, "\tcall\t__exec_monit\n"); 
#else
 

 /* AIV 01/26/11 - these should be used 64-bit instructions since slotend */
 /* is a word */
 /* action & (SE_MONIT_TRIGGER | SE_MONIT_CHG) */
 emit_one_insn(fp, "\tmovq\t__slotend_action, %%rax\n"); 
 if (check_monit)
  {
   emit_one_insn(fp, "\tandq\t$%d, %%rax\n", (SE_MONIT_TRIGGER | SE_MONIT_CHG));
   emit_one_insn(fp, "\ttestq\t%%rax, %%rax\n");
   emit_one_insn(fp, "\tje\t%s\n", monit_skip);
  }

 /* shutoff the SE_MONIT_TRIGGER if on */
 emit_one_insn(fp, "\txorq\t$%d, %%rax\n", SE_MONIT_TRIGGER);
 reg = __passed_regs_order[0];
 emit_one_insn(fp, "\tmovq\t__monit_dcehdr, %s\n", __regs[reg]); 
 reg = __passed_regs_order[1];
 emit_one_insn(fp, "\tmovq\t %%rax, %s\n", __regs[reg]); 
 emit_one_insn(fp, "\tcall\t__exec_monit\n"); 
#endif
 if (slot_ndx == -1)
  {
   emit_one_insn(fp, "%s:\n", monit_skip); 
  }
}

/*########################################################################*/ 

/*
 * ROUTINES TO WRITE AFTER LNK (ALNK) ASM ROUTINES TO CALL N. L. INIT WRAPPERS
 */

/*
 * write the design wide c source proc that calls the init proc for every mod
 *
 * since stack grows down args are pushed to %esp, %esp + 4 etc so order
 * is right to left following c convention
 */
static void ll_awr_allmods_init_func_def(FILE *fp)
{
 struct mod_t *mdp;
 char s1[RECLEN];
 
 emit_one_insn(fp, "\n# top level func to init all RT NL records\n");
 emit_one_insn(fp, ".globl __dsgn_init\n");
 emit_one_insn(fp, "__dsgn_init:\n");

 ll_awr_proc_enter_insns(fp);

 /* AIV 11/17/08 - set the running executable flag to TRUE */
 emit_one_insn(fp, "\tmovl	$1, __running_cvc_exe\n");

 /* AIV 12/30/10 - need to set the interp DPI wrapper func address */
 if (__dpi_interp_wrapper_fnam != NULL)
  {
#ifdef __CVC32__
   emit_one_insn(fp, "\tmovl	$__eval_dpi_wrapper, __dpi_imp_interp_routp\n");
#else
   emit_one_insn(fp, "\tmovq	$__eval_dpi_wrapper, __dpi_imp_interp_routp\n");
#endif
  }

 /* AIV 03/07/07 - now check memory usage if load so lib to make */
 /* sure source/options haven't changed - this links the lib symbol */
 /* SJM 09-07-08 - always set the ptr to the dsm in the alnk time code */ 
 /* does not hurt but will only be used if a save lib type option is used */
 ll_awr_set_glb_movl(fp, "__dsnmemp", "__dsnmem");

 emit_one_insn(fp, "\tcall\t__init_glbs_wrps\n");

 /* write code to set next ev in tmplate tev dat - always needed and the same */
 /* since tmplate copied onto each inst do not need to call set nxtev */
 strcpy(s1, "__tevdat_template");
 ll_awr_alnk_set_tev_nxtptr(fp, s1);

 /* SJM 08/28/08 - idp area contain itree info, must copy, free and relink */
 /* gen alnk time routines to copy and free every mod's idp area */
 emit_one_insn(fp, "\n# call wrappers to copy and free idp area for each mod\n");

 /* after all mod's mod idata area ptrs set to comm .s file, can fix */
 /* up all in one alnk time wrapper routine */
 ll_awr_fixup_allmods_comm_idp_areas(fp);

 emit_one_insn(fp, "\n# calls to alnk time init wrappers for each module\n");
 
 /* SJM 07/02/08 - since call side ebp/esp same for each call set once */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   emit_one_insn(fp, "\tcall\t__init_moddat_M%d\n", mdp->m_idnum); 
  } 

 /* emit ll awr calls to dsgn wide udp record adr init alnk wrappers */
 ll_awr_init_udptab_adrs(fp);

 if (__show_asm)
  {
   __my_fprintf(fp, "\n# MOVLS TO SET NET LIST RT USED IN C EXTERN PTRS\n"); 
  } 

 ll_awr_call_proc_leave_insns(fp);
}

/*
 * emit in comm .s file, one routine for all modules that fixes up
 * the newly copied into the comm .s file are idp areas
 *
 * SJM 08/28/08 - could actually build in comm .s file to simplify this
 */
static void ll_awr_fixup_allmods_comm_idp_areas(FILE *fp)
{
 char istr[RECLEN];

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_fixup_allmods_comm_idp_areas");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * emit call with args to the one routine to set next enter ptr in template
 * tev dat record
 *
 * just puts the for now fixed (name may change) NEXT_EV label in template tev
 *
 * top level asm routines allocated stack frame to fill for caller
 */
static void ll_awr_alnk_set_tev_nxtptr(FILE *fp, char *tmpl_tevdat_amstr)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
  tmpl_tevdat_amstr, 0);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_tev_nxtptr");
 emit_one_insn(fp, "%s\n", istr);
}


/*
 * write the c initialize wrapper proc define for one mod
 *
 * notice this routine runs as if it were a macro in the callers stack frame
 * ret (for asm) does not effect stack
 */
static void ll_awr_1mod_init_func_def(FILE *fp, struct mod_t *mdp)
{
 int32 has_trchans;

 emit_one_insn(fp, "\n# after link inits in for module %s\n", mdp->msym->synam);
 emit_one_insn(fp, ".globl __init_moddat_M%d\n", mdp->m_idnum);
 emit_one_insn(fp, "__init_moddat_M%d:\n", mdp->m_idnum);

 ll_awr_proc_enter_insns(fp);

 /* set the global __init_mdp */
 ll_init_glbl_mdp(fp, mdp->m_idnum);
 ll_awr_1mod_tevdat_init(fp, mdp);
 ll_awr_iaslt_enter_init(fp, mdp);
 ll_stmt_enter_init(fp, mdp);
 ll_dce_enter_init(fp, mdp);
 
//AIV LOOKATME AIV FIXME - all of these that work off of mnets could
//be combined so wouldn't have to make as many passes - doesn't 
//really take much time
 /* if not using static memory no need to link malloc structs */
 ll_stmt_addr_init(fp, mdp);
 ll_dcep_addr_init(fp, mdp);
 ll_grp_addr_init(fp, mdp);
 ll_gate_addr_init(fp, mdp);
 ll_conta_addr_init(fp, mdp);
 ll_net_addr_init(fp, mdp);
 ll_task_addr_init(fp, mdp);
 ll_all_npp_addr_init(fp, mdp);
 ll_xpr_addr_init(fp, mdp);

 /* AIV 08/04/09 - this should go outside of loop */

 has_trchans = ll_awr_1mod_nchg_init_and_npp_enter(fp, mdp);
 /* only need tran channel vtx to compile time know static not malloced */
 /* nchg in design wide comm .s file, if mod has tran channels */ 
 if (has_trchans)
  {
   ll_awr_alnk_set_trchan_vtx_nchgs(fp); 
  }
    

 ll_awr_init_tchk_tchg_adr(fp, mdp);
 ll_awr_init_pth_del_adr(fp, mdp);

 ll_awr_1mod_thrd_ret_stmts(fp, mdp);

 emit_one_insn(fp, "\t%s\t$0, __init_mdp\n", MOVA_STR);
 ll_awr_call_proc_leave_insns(fp);
}
 
/*
 * init the global __init_mdp pointer
 */
static void ll_init_glbl_mdp(FILE *fp, int32 mi)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, mi, NULL, 0);
  
 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_init_mdp");
 emit_one_insn(fp, "%s\n", istr);
}
 
/*
 * write one module's fixed (known) at compile tev_t records as asm 
 * wrapper calls
 *
 * now call wrapper routine that does something for every inst
 * key is that since everything asm, all globals automatically externs
 *
 * generated asm routines are called after static linking
 */
static void ll_awr_1mod_tevdat_init(FILE *fp, struct mod_t *mdp)
{
 struct ctev_t *ctevp;
 int32 gi, is_const;
 word64 gdel;
 char s1[RECLEN], s2[RECLEN], labnam[RECLEN];

 /* notice this loop is a gen iterator that inlines some code for each */
 /* tev in mod - for >1 insts fills one entry for each */
 for (ctevp = mdp->ctev_list_hd; ctevp != NULL; ctevp = ctevp->ctevnxt)
  {
   /* DBG remove -- */
   if (mdp != ctevp->mdp) __misc_terr(__FILE__, __LINE__);
   /* --- */
//SJM 05/04/08 FIXME - should include mod index?
   /* set the templates for every instance - most fields same */
   sprintf(s1, "__tevdat_%d", ctevp->ctev_ndx);
   if (__show_asm)
    {
     emit_one_insn(fp, "\n#ALNK initialize of compile time event %s\n", s1);
    }

   /* emit the enter ptr - same for every inst */
   /* set the idp cross links for all >1 - asl wrapper figures out 1 inst */
   /* case and does not set back link */
   /* AIV 03/12/12 - combined a bunch of routines to init tev_'s */
   /* this makes the code smaller and faster there is no reason to */
   /* have seperate routines - these are all perinst to so better to */
   /* to do just one pass */
   ct_get_tev_enterptr_labnam(labnam, ctevp);
   is_const = get_const_del(ctevp->du, ctevp->del_rep, &gdel, 0);
   ll_awr_init_tev_dat(fp, s1, mdp->flatinum, labnam, ctevp->ctev_idp_ofs,
    gdel, is_const);

   if (ctevp->ctev_gp != NULL)
    {
     /* same for every inst, but each tev dat different if needed */
     gi = ctevp->ctev_gp - mdp->mgates;
     ll_awr_alnk_set_tev_gp_u(fp, s1, gi, mdp->flatinum);
    }
   else gi = -1;


   /* SJM 08/25/08 - if non blocking, need th specific nb free enterptr */
   if (ctevp->nb_fg_num != -1)
    {
     sprintf(s2, "ST_ENT_NB_FREE_%d_%d", mdp->m_idnum, ctevp->nb_fg_num);
     ll_awr_set_tev_ent_nb_free(fp, s1, s2, mdp->flatinum); 
    }

   /* SJM 07/21/08 - may need to set the tev te_u field rhs non blk adr */
   if (ctevp->nb_rhs_byt_size != -1)
    {
     sprintf(s2, "__nb_rhs_area_%d", ctevp->ctev_ndx);
     ll_awr_alnk_tev_set_tu_nbrhs(fp, s1, s2, ctevp->nb_rhs_byt_size,
      mdp->flatinum, ctevp->srep);
    }

   /* 64 bit delay time - maybe per inst but 0th known at compile time */
   if (mdp->flatinum > 1 && is_const_is1v_delay(ctevp->del_rep))
    {
     sprintf(s2, "%s_1v_peri_tab", s1);
     if (ctevp->del_rep == DT_IS1V
      && is1v_nds_64bits(ctevp->du, mdp->flatinum))
      {
       ll_awr_alnk_cp_is1v_64b_tev_dels(fp, s1, s2, mdp->flatinum);
      }
     else
      {
       ll_awr_alnk_cp_is1v_32b_tev_dels(fp, s1, s2, mdp->flatinum);
      }
    }
  }
}

/*
 * link call to link in ialp->enterptr
 */
static void ll_awr_iaslt_enter_init(FILE *fp, struct mod_t *mdp)
{
 char istr[RECLEN], s1[RECLEN];

   
 /* contains no init/always blocks nothing to link */
 if (mdp->ialst == NULL) return;
 
 /* pass the array name */
 sprintf(s1, "ialst_%d", mdp->m_idnum);
 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

 /* pass the mod id */
 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, mdp->m_idnum, NULL, 1);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_ialst_enters");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * link stmt enter locations
 *  stp->enterptr = ST_ENT_
 */
static void ll_stmt_enter_init(FILE *fp, struct mod_t *mdp)
{
 int32 i;
 struct st_t *stp;
 char s1[RECLEN], istr[RECLEN];
 size_t offset, eoffset;

 /* AIV 03/13/12 - changed this to use inline - no reason to use */
 /* wrapper code - produces less code */
 sprintf(istr, "\t%s    __init_mdp, %s", MOVA_STR, __regs[AR_AX]);
 emit_one_insn(fp, "%s\n", istr);

 offset = (byte *) &(mdp->mstmts) - (byte *) mdp;
#ifdef __CVC32__
 sprintf(istr, "\t%s    %d(%s), %s", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_AX]);
#else
  sprintf(istr, "\t%s    %lu(%s), %s", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_AX]);
#endif
 emit_one_insn(fp, "%s\n", istr);

 for (i = 0; i < mdp->mstnum; i++) 
  {
   stp = mdp->mstmts[i];
   /* AIV 11/10/06 - if stmt is marked unreachable skip linking */
   if (stp->unreachable) continue;
 
   /* only link if enter label has been created */
   if (!stp->enter_created) continue;

   eoffset = (byte *) &(stp->enterptr) - (byte *) stp;
   sprintf(s1, "ST_ENT_%d_%d", mdp->m_idnum, i);
   offset = i*sizeof(struct st_t *);

#ifdef __CVC32__
   sprintf(istr, "\t%s    %d(%s), %s", MOVA_STR, offset, __regs[AR_AX],
      __regs[AR_BX]);
   emit_one_insn(fp, "%s\n", istr);
   sprintf(istr, "\t%s    $%s, %d(%s)", MOVA_STR, s1, eoffset,
     __regs[AR_BX]);
#else
   sprintf(istr, "\t%s    %lu(%s), %s", MOVA_STR, offset, __regs[AR_AX],
      __regs[AR_BX]);
   emit_one_insn(fp, "%s\n", istr);
   /* if uses +large model must use an extra move and movabsq */
   if (__cvc_use_large_model)
    {
     sprintf(istr, "\tmovabsq $%s, %%rcx", s1);
     emit_one_insn(fp, "%s\n", istr);
     sprintf(istr, "\tmovq    %%rcx, %lu(%s)", eoffset, __regs[AR_BX]);
    }
   else
    {
     sprintf(istr, "\tmovq    $%s, %lu(%s)", s1, eoffset, __regs[AR_BX]);
    }
#endif
   emit_one_insn(fp, "%s\n", istr);
  }
}

/*
 * AIV 07/25/09 - merged ll_awr_1mod_nchg_init and ll_npp_enter_init
 * because was producing too much assembly this reduce the init_mod code
 * size
 *
 * call to set up net to net loads address label 
 * and
 * emit all of mod's static (fixed) net changes into dsgn wide comm c file  
 * np->enter_npp = symadr;
 *
 * return T if mod has nets in a tran channel
 */
static int32 ll_awr_1mod_nchg_init_and_npp_enter(FILE *fp, struct mod_t *mdp)
{
 int32 ni, nd_set_nchg_entptr, first_np_npp, has_trchans;
 struct net_t *np;
 struct net_chg_t *ncp;
 char s1[RECLEN], istr[RECLEN], s2[RECLEN], s3[RECLEN];

 has_trchans = FALSE;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
  {
   /* has tran chans */
   if (np->ntraux != NULL) has_trchans = TRUE;

   /* if has net changes try to also set the npp->enter_npp */
   if (np->nchdp != NULL)
    {
     if (np->nlds != NULL) first_np_npp = TRUE;
     else first_np_npp = FALSE;

     for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
      {
       /* AIV 11/20/07 - may use the tran channels in wrapper code so lowered */
       /* flag may not be set */
       if (!ncp->is_lowered && !ncp->is_wire_ev && np->ntraux == NULL) continue;
       if (!__needs_netchg_record(np)) continue;
  
       nd_set_nchg_entptr = FALSE;     
       if (np->n_cause || np->n_mipd)
        {
         if (np->nlds != NULL || (np->ntyp < NONWIRE_ST && np->dcelst != NULL))
          { nd_set_nchg_entptr = TRUE; }
        }
       else nd_set_nchg_entptr = TRUE;
  
       sprintf(s1, "__nchgdat_%d", ncp->ndx);
       if (nd_set_nchg_entptr) 
        {
         sprintf(s2, "PROCESS_NCHG_%d", ncp->ndx);
         if (first_np_npp)
          {
           sprintf(s3, "NPP_%d_%d", mdp->m_idnum, ni);
           ll_awr_alnk_init_nchglst_el(fp, s1, s2, s3, ni, ncp);
          }
         else
          {
           ll_awr_alnk_init_nchglst_el(fp, s1, s2, NULL, ni, ncp);
          }
        }
       else
        {
         /* AIV FIXME - must never happen because "NULL" wouldn't compile */
         /* in the assembly passing string as "0" */
         //ll_awr_alnk_init_nchglst_el(fp, s1, "NULL", ni, ncp);
         if (first_np_npp)
          {
           sprintf(s3, "NPP_%d_%d", mdp->m_idnum, ni);
           ll_awr_alnk_init_nchglst_el(fp, s1, "0", s3, ni, ncp);
          }
         else
          {
           ll_awr_alnk_init_nchglst_el(fp, s1, "0", NULL, ni, ncp);
          }
         }
       first_np_npp = FALSE;
      }

    /* if still didn't load npp - must call regular npp lds */
    if (first_np_npp) goto lower_lds;
   }
  else
   {
    if (np->nlds == NULL) continue;

lower_lds:
    sprintf(s1, "NPP_%d_%d", mdp->m_idnum, ni);
    ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

    ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ni, NULL, 1);
   
    ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
     "__alnk_set_npp_entptr");
    emit_one_insn(fp, "%s\n", istr);
   }
  }
 return(has_trchans);
}
 
/*
 * np->enter_dce = symadr;
 */
static void ll_dce_enter_init(FILE *fp, struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 char s1[RECLEN], istr[RECLEN];
 size_t offset, eoffset;

 /* AIV 03/13/12 - changed this to use inline - no reason to use */
 /* wrapper code - produces less code */
 sprintf(istr, "\t%s    __init_mdp, %s", MOVA_STR, __regs[AR_AX]);
 emit_one_insn(fp, "%s\n", istr);

 offset = (byte *) &(mdp->mnets) - (byte *) mdp;
#ifdef __CVC32__
 sprintf(istr, "\t%s    %d(%s), %s", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_AX]);
#else
 sprintf(istr, "\t%s    %lu(%s), %s", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_AX]);
#endif
 emit_one_insn(fp, "%s\n", istr);

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
  {
   /* AIV LOOKATME AIV FIXME - make this a routine - got this from bbgen */
   /* dce datofs address code */
   if (!((np->nchg_nd_chgstore || np->nchg_has_dces || np->monit_in_src
      || np->dmpv_in_src || np->dmpp_in_src) && np->dcelst != NULL))
      continue;
   /* AIV 11/21/07 - need to link on var lhs nb as well to propgate chgs */
   if (!np->frc_assgn_allocated && !np->n_on_nblhs_varndx
        &&  !(np->ntyp < NONWIRE_ST || np->ntyp == N_EVENT)) 
    continue;

   sprintf(s1, "DCE_%d_%d", mdp->m_idnum, ni);
   eoffset = (byte *) &(np->enter_dce) - (byte *) np;
   offset = (ni*sizeof(struct net_t))+eoffset;

#ifdef __CVC32__
   sprintf(istr, "\t%s    $%s, %d(%s)", MOVA_STR, s1, offset,
     __regs[AR_AX]);
#else
   /* if uses +large model must use an extra move and movabsq */
   if (__cvc_use_large_model)
    {
     sprintf(istr, "\tmovabsq $%s, %%rcx", s1);
     emit_one_insn(fp, "%s\n", istr);
     sprintf(istr, "\tmovq    %%rcx, %lu(%s)", offset, __regs[AR_AX]);
    }
   else
    {
     sprintf(istr, "\tmovq    $%s, %lu(%s)", s1, offset, __regs[AR_AX]);
    }
#endif
   emit_one_insn(fp, "%s\n", istr);
  }
}
     
/*
 * set the value for ST_0_0 to the address of alloc stmt
 */
static void ll_stmt_addr_init(FILE *fp, struct mod_t *mdp)
{
 int32 sti;
 struct st_t *stp;
 char s1[RECLEN], istr[RECLEN];
 size_t offset;

 /* AIV 03/13/12 - changed this to use inline - no reason to use */
 /* wrapper code - produces less code */
 sprintf(istr, "\t%s    __init_mdp, %s", MOVA_STR, __regs[AR_AX]);
 emit_one_insn(fp, "%s\n", istr);

 offset = (byte *) &(mdp->mstmts) - (byte *) mdp;
#ifdef __CVC32__
 sprintf(istr, "\t%s    %d(%s), %s", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_AX]);
#else
 sprintf(istr, "\t%s    %lu(%s), %s", MOVA_STR, offset, __regs[AR_AX], 
  __regs[AR_AX]);
#endif
 emit_one_insn(fp, "%s\n", istr);

 for (sti = 0; sti < mdp->mstnum; sti++)
  {
   stp = mdp->mstmts[sti];
   if (!stp->is_loaded) continue;

   sprintf(s1, "ST_%d_%d", mdp->m_idnum, sti);
   offset = sti*sizeof(struct st_t *);

#ifdef __CVC32__
   sprintf(istr, "\t%s    %d(%s), %s", MOVA_STR, offset, __regs[AR_AX],
      __regs[AR_BX]);
   emit_one_insn(fp, "%s\n", istr);

   sprintf(istr, "\t%s    %s, %s", MOVA_STR, __regs[AR_BX], s1);
   emit_one_insn(fp, "%s\n", istr);
#else
   sprintf(istr, "\t%s    %lu(%s), %s", MOVA_STR, offset, __regs[AR_AX],
      __regs[AR_BX]);
   emit_one_insn(fp, "%s\n", istr);

   if (__cvc_use_large_model)
    {
     sprintf(istr, "\tmovabsq $%s, %s", s1, __regs[AR_CX]);
     emit_one_insn(fp, "%s\n", istr);

     sprintf(istr, "\tmovq    %s, (%s)", __regs[AR_BX], __regs[AR_CX]);
     emit_one_insn(fp, "%s\n", istr);
    }
   else
    {
     sprintf(istr, "\t%s    %s, %s", MOVA_STR, __regs[AR_BX], s1);
     emit_one_insn(fp, "%s\n", istr);
    }
#endif
  }
}
  
/*
 * set DCEA_modid_netndx_dcendx to point to a loaded dce 
 */
static void ll_dcep_addr_init(FILE *fp, struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct dcevnt_t *dcep;
 char s1[RECLEN], istr[RECLEN];

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
  {
   for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt) 
    {
     if (dcep->merged || !dcep->is_loaded) continue;
     sprintf(s1, "DCEA_%d_%d_%d", mdp->m_idnum, ni, dcep->dce_ndx);

     ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

     ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ni, NULL, 1);
  
     ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, dcep->dce_ndx, 
       NULL, 2);
   
     ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
      "__alnk_set_dcevnt");
     emit_one_insn(fp, "%s\n", istr);
    }
  }
}

/*
 * link GRP_modndx_grpndx to the malloc gref
 */
static void ll_grp_addr_init(FILE *fp, struct mod_t *mdp)
{
 int32 gi;
 struct gref_t *grp;
 char s1[RECLEN], istr[RECLEN];


 for (gi = 0, grp = &(mdp->mgrtab[0]); gi < mdp->mgrnum; gi++, grp++)
  {
   if (!grp->is_loaded) continue;

   sprintf(s1, "GRP_%d_%d", mdp->m_idnum, gi);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, gi, NULL, 1);
   
   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
    "__alnk_set_gref");
   emit_one_insn(fp, "%s\n", istr);
  }
}

/*
 * link G_modndx_gndx to the malloc gate addr
 */
static void ll_gate_addr_init(FILE *fp, struct mod_t *mdp)
{
 int32 gi;
 struct gate_t *gp;
 char s1[RECLEN], istr[RECLEN];

 for (gi = 0, gp = &(mdp->mgates[0]); gi < mdp->mgnum; gi++, gp++)
  {
   /* AIV 07/06/09 - removed gp->is_loaded to save space in gate_t */
   if (!is_gate_loaded(gp)) continue;

   sprintf(s1, "G_%d_%d", mdp->m_idnum, gi);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, gi, NULL, 1);
   
   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
    "__alnk_set_gate");
   emit_one_insn(fp, "%s\n", istr);
  }
}

/*
 * return TRUE if gate is loaded
 * only true for wide/tran/ or special +show_cancel options
 */
static int32 is_gate_loaded(struct gate_t *gp)
{
 word64 gdel;
 int32 nins, is_const;

 if (gp->g_class == GC_TRANIF) return(TRUE);

 nins = gp->gpnum - 1;
 if (nins > 15) return(TRUE);

 if (gp->g_delrep == DT_NONE) return(FALSE);

 is_const = __check_delay_constant(gp->g_du, gp->g_delrep, &(gdel));
 if (!is_const) return(TRUE);
 
 if (gp->g_hasst) return(TRUE);

 if ( __show_cancel_e || __warn_cancel_e) return(TRUE);


 if (gp->g_class == GC_LOGIC) return(FALSE);


 return(FALSE);
}
     
/*
 * link CA_modndx_cndx to the malloc conta addr
 */
static void ll_conta_addr_init(FILE *fp, struct mod_t *mdp)
{
 int32 ci;
 struct conta_t *cap;
 char s1[RECLEN], istr[RECLEN];

 for (ci = 0, cap = &(mdp->mcas[0]); ci < mdp->mcanum; ci++, cap++)
  {
   if (!cap->is_loaded) continue;

   sprintf(s1, "CA_%d_%d", mdp->m_idnum, ci);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ci, NULL, 1);
   
   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
    "__alnk_set_conta");
   emit_one_insn(fp, "%s\n", istr);
  }
}
     

/*
 * set _np_ to point to the malloc net address
 */
static void ll_net_addr_init(FILE *fp, struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 char s1[RECLEN], s2[RECLEN], istr[RECLEN];

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
  {
   if (!np->is_loaded) continue;

   __bldchk_var_comm_ref(s2, np, mdp, NULL);
   sprintf(s1, "%s_np_%d", s2, ni);
     
   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ni, NULL, 1);
   
   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
    "__alnk_set_net_addr");
   emit_one_insn(fp, "%s\n", istr);
  }
}

/*
 * set TSKP_modid_taskndx to point to the loaded task
 */
static void ll_task_addr_init(FILE *fp, struct mod_t *mdp)
{
 int32 ti;
 struct task_t *tskp;
 char s1[RECLEN], istr[RECLEN];


 for (ti = 0, tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt, ti++)
  {
   if (!tskp->is_loaded) continue;

   sprintf(s1, "TSKP_%d_%d", mdp->m_idnum, ti);
     
   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ti, NULL, 1);
   
   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
    "__alnk_set_task_addr");
   emit_one_insn(fp, "%s\n", istr);
  }
}
     
/*
 * set all the nets NPP_ to point to loaded npp
 */
static void ll_all_npp_addr_init(FILE *fp, struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct net_pin_t *npp;
 char s1[RECLEN];
 
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
     if (!npp->is_loaded) continue;
     sprintf(s1, "NPPA_%d_%d", mdp->m_idnum, npp->npp_idnum);
     ll_one_npp_addr_init(fp, s1, npp->npp_idnum);
    }
   for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
    {
     if (!npp->is_loaded) continue;
     sprintf(s1, "NPPA_%d_%d", mdp->m_idnum, npp->npp_idnum);
     ll_one_npp_addr_init(fp, s1, npp->npp_idnum);
    }
  }
}

/*
 * set one npp NPPA address to the malloc net_pin_t address
 */
static void ll_one_npp_addr_init(FILE *fp, char *nppa_str, int32 npp_idnum)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, nppa_str, 0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, npp_idnum, NULL, 
  1);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_npp_addr");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * set one expr XPR address to the malloc expr address
 */
static void ll_xpr_addr_init(FILE *fp, struct mod_t *mdp) 
{
 int32 xi;
 char s1[RECLEN], istr[RECLEN];
 struct expr_t *xp;
 struct expr_tab_t *etp;

 if ((etp = mdp->expr_tab) == NULL) return;

 for (xi = 0; xi < etp->num; xi++)
  {
   xp = etp->table[xi];
   if (!xp->is_loaded) continue;

   sprintf(s1, "XPR_%d_%d", mdp->m_idnum, xi);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 0);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, xi, NULL, 1);

   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
    "__alnk_set_xpr_addr");
   emit_one_insn(fp, "%s\n", istr);
  }
}

/*
 * return T if delay is 1v IS form
 *
 * SJM 04/10/08 - since need the RT edge table look up for 4v and 16v
 * only T for the 3 is 1v packing cases
 *
 * needed since ALNK tev init code needs to set only per inst delays
 */
static int32 is_const_is1v_delay(int32 dtyp)
{
 switch (dtyp) {
  case DT_IS1V: case DT_IS1V1: case DT_IS1V2:
   return(TRUE);
  case DT_NONE: case DT_1V: case DT_4V: case DT_16V:
  case DT_IS4V: case DT_IS4V1: case DT_IS4V2: case DT_IS16V:
  case DT_IS16V1: case DT_IS16V2:
  case DT_1X: case DT_4X:
  case DT_PTHDST: case DT_CMPLST:
   /* SJM 05/09/08 - these are just set to 0 so no need to chg */
   return(FALSE);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}

/*
 * routine to get label for processing routine
 *
 * AIV FIXME - path ndx is chosen over other wire events 
 * making too many not needed wire events????????
 *
 * SJM 04/18/08 - why is this routine so complicated
 */
static char *ct_get_tev_enterptr_labnam(char *labnam, struct ctev_t *ctevp)
{
 /* DBG remove --- 
 if (ctevp->path_ndx != -1 && ctevp->wev_ndx != -1)
  __misc_terr(__FILE__, __LINE__);
 ---- */
 if (ctevp->path_ndx != -1)
  {
   sprintf(labnam, "TRPTH_EV_%d_%d", ctevp->mdp->m_idnum, ctevp->path_ndx);
  }
 else if (ctevp->wev_ndx != -1)
  {
   sprintf(labnam, "WIRE_EV_%d", ctevp->wev_ndx);
  }
 else if (ctevp->ca_ndx != -1)
  {
   sprintf(labnam, "CAP_%d", ctevp->ca_ndx);
  }
 else if (ctevp->dctrl_ndx != -1)
  {
   sprintf(labnam, "MDC_ENT_%d_%d", ctevp->mdp->m_idnum, ctevp->dctrl_ndx);
  }
 else if (ctevp->ct_el_ndx == -1) 
  {
//AIV FIXME - this can be true because code is never produced for
//used task bodys - see t_used flag
//     if (ctevp->wrapper_type == WRAPPER_NONE)
//      __misc_terr(__FILE__, __LINE__);
   if (ctevp->wrapper_type == WRAPPER_NONE) strcpy(labnam, "0xffffffff");
   else 
    {
     if (ctevp->wrapper_type == WRAPPER_PROCESS_THRD_EV)
      {
       strcpy(labnam, "THRD_EV");
      }
     else if (ctevp->wrapper_type == WRAPPER_NPBA_VARNDX_CONCAT_EV)
      {
       strcpy(labnam, "NBPA_VARNDX_CONCAT_EV");
      }
     else __misc_terr(__FILE__, __LINE__);
    }
  }
 else
  {
   if (ctevp->ct_comlab_typ == COMLAB_PROC_ENTER)
    {
     sprintf(labnam, "ST_ENT_%d_%d", ctevp->mdp->m_idnum, ctevp->ct_el_ndx);
    }
   else if (ctevp->ct_comlab_typ == COMLAB_PROC_NB_ENTER)
    {
     sprintf(labnam, "ST_ENT_NB_%d_%d", ctevp->mdp->m_idnum,
      ctevp->ct_el_ndx);
    }
   else if (ctevp->ct_comlab_typ == COMLAB_GATE_ENTER) 
    {
     sprintf(labnam, "GATEDA_%d_%d", ctevp->mdp->m_idnum, ctevp->ct_el_ndx);
    }
   else if (ctevp->ct_comlab_typ == COMLAB_GATE_CHANGE_ENTER) 
    {
     strcpy(labnam, "GATECHG_EV");
    }
   else if (ctevp->ct_comlab_typ == COMLAB_PROCESS_WIRE_ENTER) 
    {
     sprintf(labnam, "WIRE_EV_%d", ctevp->ct_el_ndx);
    }
   else if (ctevp->ct_comlab_typ == COMLAB_MIPD_ENTER) 
    {
     sprintf(labnam, "MIPD_%d_%d", ctevp->mdp->m_idnum, ctevp->ct_el_ndx);
    }
   else __case_terr(__FILE__, __LINE__);
  }
 return(labnam);
}

/*
 * get a delay value for a known constant delay returning the 64 bit time
 * into two 32-bit times, returns TRUE if the delay is constant
 */
static int32 get_const_del(union del_u du, int32 drep,  word64 *gdel,
 int32 inum)
{
 int32 is_const;

 *gdel = 0xffffffffffffffffULL;
 if (drep == DT_NONE) return(FALSE);

 is_const = FALSE;
 switch ((byte) drep) {
  case DT_1V: 
   *gdel = du.d1v[0]; 
   is_const = TRUE;
   break;
  case DT_IS1V: 
   *gdel = du.dis1v[inum]; 
   is_const = TRUE;
   break;
  case DT_IS1V1:
   *gdel = (word64) du.dis1v1[inum];
   is_const = TRUE;
   break;
  case DT_IS1V2:
   *gdel = (word64) du.dis1v2[inum];
   is_const = TRUE;
   break;
  case DT_4V:
  case DT_IS4V:
  case DT_IS4V1:
  case DT_IS4V2:
  case DT_16V:
  case DT_IS16V:
  case DT_IS16V1:
  case DT_IS16V2:
  case DT_1X:
  case DT_4X:
  case DT_PTHDST:
  case DT_CMPLST:
   is_const = FALSE;
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(is_const);
}

/*
 * gen the dsgn wide comm .s asm calls to the alnk time udp adr init wrappers
 *
 * now only one routine that sets adr level (L_) and if has edges (E_) 
 * comm asm file labels
 *
 * SJM 07/30/08 - LOOKATME - eventually could move udp tables to comm .s file
 */
static void ll_awr_init_udptab_adrs(FILE *fp)
{
 struct udp_t *udpp;
 char s1[RECLEN], s2[RECLEN];
 
 for (udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
  {
   sprintf(s1, "__UDPL_%d", udpp->u_idnum);
   if (udpp->utyp == U_EDGE)
    {
     /* DBG remove -- */
     if (udpp->utab->eudptabs == NULL) __misc_terr(__FILE__, __LINE__); 
     /* --- */
     sprintf(s2, "__UDPE_%d", udpp->u_idnum);
    }
   else
    {
     /* DBG remove -- */
     if (udpp->utab->eudptabs != NULL) __misc_terr(__FILE__, __LINE__); 
     /* --- */
     strcpy(s2, "");
    }

   ll_awr_alnk_set_udptab_adr(fp, s1, s2, udpp->u_idnum);
  }
}

/*
 * emit ptr (addr) location that directly points to tchk tchg struct
 *
 * saves the complex indirection to get to the tchg_t record 
 */
static void ll_awr_init_tchk_tchg_adr(FILE *fp, struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct net_pin_t *npp;
 char s1[RECLEN];

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++)
  {
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
     if (npp->npntyp != NP_TCHG) continue;
     if (npp->chgsubtyp != NPCHG_TCCHK) continue;

     sprintf(s1, "__TCHK_TCHG_%d_%d", mdp->m_idnum, npp->npp_idnum);
     ll_awr_alnk_set_tchk_tchg_adr(fp, s1, npp->npp_idnum);
    }
  }
}

/*
 * emit ptr (addr) location that directly points to specify path del table
 *
 * saves the complex indirection to access the delay of a specify path
 * separates path selection in mod (complex wrapper) from delay access
 */
static void ll_awr_init_pth_del_adr(FILE *fp, struct mod_t *mdp)
{
 struct spcpth_t *pthp; 
 char s1[RECLEN];

 if (mdp->mspfy == NULL) return;

 for (pthp = mdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
  {
   /* DBG remove -- */
   if (pthp->spcpth_id == -1) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   sprintf(s1, "__PTHDEL_%d_%d", mdp->m_idnum, pthp->spcpth_id);

   ll_awr_alnk_set_pth_del_adr(fp, s1, pthp->spcpth_id);
  }
}

/*
 * ROUTINES TO EMIT ASSIGN NET LIST C EXTERN PTRS USING ASM LINKING OF MOVLS 
 */

/*
 * ll awr 1 mod stmts in thrd return tab that need to have stp enter ptrs set
 */
static void ll_awr_1mod_thrd_ret_stmts(FILE *fp, struct mod_t *mdp) 
{
 int32 i;
 struct st_t *stp;
 char s1[RECLEN];
 char *cp;

 for (i = 0; i < mdp->mstnum; i++) 
  {
   stp = mdp->mstmts[i];
   /* AIV 11/10/06 - if stmt is marked unreachable skip linking */
   if (stp->unreachable) continue;

   if (stp->enter_created) continue;

   /* AIV 02/03/06 - if stmt is a after a task call need to set enter loc */
   /* this is need because a disable in a task can return to scheduler */
   /* which needs to be able to enter back to task return location */
   if (stp->task_thrd_jmpndx == -1) continue;

   /* get the thrd jump back name and concat index */
   cp = __thdjmp_ret_tab[stp->task_thrd_jmpndx];
   /* DBG remove -- */
   if (cp == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   sprintf(s1, "%s_%d", cp, stp->task_thrd_jmpndx);
   ll_awr_set_stmt_entptr(fp, s1, i);
  }
}

/*
 * ROUTINES TO EMIT BOILER PLATE TYPE ASM INSNS - CALLER PASSES AMODE STRING 
 */

/*
 * emit memcpy wrapper that copies into every instance
 * 
 * AIV 07/25/09 - this is only used to init tev's - renamed no longer takes
 * src string
 */
static void ll_awr_init_tev_dat(FILE *fp, char *dst_amstr, int32 ninsts,
 char *entptr_amstr, size_t ctev_idp_ofs, word64 del, int32 set_delay)
{
 char istr[RECLEN];
 char s1[RECLEN];
#ifdef __CVC32__
 word32 ldel, hdel;
#endif
 
 /* SJM 07/22/08 - notice s1 used in whole routine, s2 is reused */
 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, dst_amstr,
  0);

 /* SJM 07/06/08 - was not pushing the number of insts */
 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ninsts, NULL, 1);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
  entptr_amstr, 2);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ctev_idp_ofs, 
   NULL, 3);

 /* if this tev has no delay just continue */
 if (!set_delay)
  {
   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
    "__alnk_init_tev_dat_nodelay");
   emit_one_insn(fp, "%s\n", istr);
   return;
  }

 /* if has delay pass the delay value to set */
#ifdef __CVC32__
 ldel = ((word32) del) & ALL1W;
 hdel = ((word32) (del >> 32)) & ALL1W;

 /* treat as label but really hex number - easier to read */
 sprintf(s1, "0x%lx", ldel);
 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 4);

 sprintf(s1, "0x%lx", hdel);
 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 5);
#else
 sprintf(s1, "0x%lx", del);
 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, s1, 4);
#endif

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_init_tev_dat");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * emit low level call to aslib set tev gate union routine
 */
static void ll_awr_alnk_set_tev_gp_u(FILE *fp, char *dst_amstr, int32 gi, 
 int32 ninsts)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, dst_amstr, 
  0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, gi, NULL, 1);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ninsts, NULL, 2);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_tev_gp_u");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * emit low level call to aslib to set the modules per non blocking assign
 * that needs memory's enter ptr for the right freeing flow graph 
 */
static void ll_awr_set_tev_ent_nb_free(FILE *fp, char *tevs_amstr,
 char *st_ent_nb_free_amstr, int32 ninsts)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, tevs_amstr, 0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
  st_ent_nb_free_amstr, 1);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ninsts, NULL, 2);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_tev_nb_free_nextevptr");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * emit the low level call to aslib set the nb rhs memory value area
 * for the first nb scheduled change (in fixed comm .s area near tevdat
 * to avoid the malloc in common only one pending nb event case)
 */
static void ll_awr_alnk_tev_set_tu_nbrhs(FILE *fp, char *tev_amstr,
 char *tev_nb_area_amstr, int32 nb_rhs_bytsiz, int32 ninsts, int32 srep)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, tev_amstr, 
  0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
  tev_nb_area_amstr, 1);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, nb_rhs_bytsiz, 
  NULL, 2);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ninsts, NULL, 3);

 /* need to handle 2-state in different wrapper */
 if (srep == SR_BIT2S)
  {
   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
     "__alnk_tev_set_tu_nbrhs_2s");
  }
 else
  {
   ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
     "__alnk_tev_set_tu_nbrhs_2s");
   }
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * emit call to asl alnk time wrapper to set packed into 32 bit per inst dels
 */
static void ll_awr_alnk_cp_is1v_32b_tev_dels(FILE *fp, char *tev_amstr,
 char *peri_tab_str, int32 ninsts)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, tev_amstr, 
   0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, peri_tab_str, 1);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ninsts, NULL, 2);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_cp_is1v_32b_tev_dels");
 emit_one_insn(fp, "%s\n", istr);
}


/*
 * emit call to asl alnk time wrapper to set packed into 64 bit per inst dels
 */
static void ll_awr_alnk_cp_is1v_64b_tev_dels(FILE *fp, char *tev_amstr,
 char *peri_tab_str, int32 ninsts)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, tev_amstr, 
  0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, peri_tab_str,
  1);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ninsts, NULL, 2);

#ifdef __CVC32__
 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_cp_is1v_64b_tev_dels");
#else
 /* AIV 11/13/08 - 64-bit version just needs to use regular 64-bit delay */
 /* index wrapper */
 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_cp_is1v_32b_tev_dels");
#endif
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * emit call with args to the routine to fill a nchglst element
 */
static void ll_awr_alnk_init_nchglst_el(FILE *fp, char *nchg_amstr,
 char *nchg_ent_amstr, char *npp_ent_amstr, int32 ni, struct net_chg_t *ncp)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, nchg_amstr, 
  0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, nchg_ent_amstr, 
  1);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ni, NULL, 2);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ncp->nchg_idp_ofs, 
  NULL, 3);

 /* AIV 07/22/09 - made this code smaller by making two cases one range */
 /* and one no range - produces less code */
 if (ncp->i1 != -1 || ncp->i2 != -1)
  {
   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ncp->i1, NULL,
    4);

   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, ncp->i2, NULL, 
    5);
  
   if (npp_ent_amstr != NULL)
    {
     ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
       npp_ent_amstr, 6);
     ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
      "__alnk_init_nchglst_el_rng_npp");
    }
   else 
    {
     ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
      "__alnk_init_nchglst_el_rng");
    }
  }
 else
  {
   if (npp_ent_amstr != NULL)
    {
     ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
       npp_ent_amstr, 4);
     ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
      "__alnk_init_nchglst_el_npp");
    }
   else
    {
     ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
      "__alnk_init_nchglst_el");
    }
  }

 emit_one_insn(fp, "%s\n", istr);
}

/*
 * gen asm code to call routine that traverses all net tran channels to
 * set vtx nchgps when needed
 */
static void ll_awr_alnk_set_trchan_vtx_nchgs(FILE *fp)
{
 char istr[RECLEN];

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_trchan_vtx_nchgs");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * gen asm code to call routine that sets the udp tab adr for one udp tab
 * needs to pass the label name since same for the one level and edge tabs
 */
static void ll_awr_alnk_set_udptab_adr(FILE *fp, char *udptab_l_amstr,
 char *udptab_e_amstr, int32 udp_idnum)
{
 char istr[RECLEN];

 /* store the argument 1st is (%esp) then upward by 4 */
 /* this is the label in the comm .s file for the either level or edge tab */
 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
  udptab_l_amstr, 0);

 if (strcmp(udptab_e_amstr, "") == 0)
  {
   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, 0, NULL, 1);
  }
 else
  {
   ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
    udptab_e_amstr, 1);
  }

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, udp_idnum, NULL,
   2);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_udptab_adrs");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * gen asm code to call routine that sets the tchk's tchk change subtype 
 * tchg record addr (ptr)
 */
static void ll_awr_alnk_set_tchk_tchg_adr(FILE *fp, char *tchk_tchg_amstr,
 int32 npp_id)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, 
  tchk_tchg_amstr, 0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, npp_id, NULL, 1);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_tchk_tchg_adr");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * gen asm code to call routine that sets the tchk's tchk change subtype 
 * tchg record addr (ptr)
 */
static void ll_awr_alnk_set_pth_del_adr(FILE *fp, char *pthdel_amstr,
 int32 pth_id)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, pthdel_amstr,
  0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, pth_id, NULL, 1);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_pth_del_adr");
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * emit set of stmt enter pointer given mod idnum, st idnum and label string
 */  
static void ll_awr_set_stmt_entptr(FILE *fp, char *dst_amstr, int32 sti)
{
 char istr[RECLEN];

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_LABEL, REG_NONE, -1, dst_amstr, 
  0);

 ll_pass_arg_insn_to_str(fp, istr, I_MOVA, AM_IMM, REG_NONE, sti, NULL, 1);

 ll_1op_insn_to_str(istr, I_CALL, AM_LABEL, REG_NONE, -1,
  "__alnk_set_stmt_entptr");
 emit_one_insn(fp, "%s\n", istr);
}


/*
 * LOWEST LEVEL EMIT LOW LEVEL ASM INSN ROUTINES
 */

/*
 * routine to gen 2 insns using $EAX to set a net list RT ptr to a asm
 * gened label
 *
 * this gens 2 boiler plate instructions using EAX in low level asm routine
 * where EAX always constantly globbered anyway
 */
static void ll_awr_set_glb_movl(FILE *fp, char *glb_rt_varnam,
 char *glb_asmlabnam) 
{
 if (__opt_debug_flg)
  {
   emit_one_insn(fp, "\n# c: %s = &(%s);\n", glb_rt_varnam, glb_asmlabnam);
  }
#ifdef __CVC32__
 /* AIV 01/25/11 - need to have a movq here for 64-bit */
 emit_one_insn(fp, "\tmovl\t$%s, %s\n", glb_asmlabnam, glb_rt_varnam); 
#else
 emit_one_insn(fp, "\tmovq\t$%s, %s\n", glb_asmlabnam, glb_rt_varnam); 
#endif
}

/*
 * emit insns to set up stack on asm routine entry
 *
 * assumes code and awr asm routines only use eax, ecx and edx
 *
 * assumes that all called asm routines are exactly one level down and
 * have no more than 16 (14) params - those routines can call c funcs
 * since the c func handles the callee saving and setup and restoring
 */
static void ll_awr_proc_enter_insns(FILE *fp)
{
 char istr[RECLEN];

 ll_1op_insn_to_str(istr, I_PUSHA, AM_REG, AR_BP, -1, NULL);
 emit_one_insn(fp, "%s\n", istr);
 ll_2op_insn_to_str(istr, I_MOVA, AM_REG, AR_SP, -1, NULL,
  AM_REG, AR_BP, -1);
 emit_one_insn(fp, "%s\n", istr);

 /* create a stack frame for use by called asm and if needed c procs */
//SJM 07/28/08 - BEWARE - assuming max 16 args to ll awr calls
 ll_2op_insn_to_str(istr, I_SUBA, AM_IMM, REG_NONE, 16*WRDBYTES, NULL,
   AM_REG, AR_SP, -1);
 emit_one_insn(fp, "%s\n", istr);
}

/*
 * routine to write call clean up (epilogue) insns
 *
 * -> leave same as: "mov %ebp, %esp; pop %ebp" 
 */
static void ll_awr_call_proc_leave_insns(FILE *fp)
{
 emit_one_insn(fp, "%s\n", "\tleave");
 emit_one_insn(fp, "%s\n", "\tret");
}

/*
 * bld an insn string from insn number and amodes - 2 operand version
 *
 * SJM 06/19/08 - new scheme that just maps insn name (for AMD 64 too)
 * and must be passed the amode string (also mapped but by here just passed str)
 */
static char *ll_2op_insn_to_str(char *s, int32 opcod, int32 amode, int32 mreg,
 int32 disp, char *lab, int32 amode2, int32 mreg2, int32 disp2)
{
 struct insn_info_t *iip;
 char s1[RECLEN], s2[RECLEN]; 

 ll_bld_amode_str(s1, amode, mreg, disp, lab);
 ll_bld_amode_str(s2, amode2, mreg2, disp2, NULL);
 iip = __to_iinfo_rec(opcod);
 sprintf(s, "\t%s\t%s, %s", iip->inam, s1, s2);
 return(s);
}

#ifdef __CVC32__
static void ll_pass_arg_insn_to_str(FILE *fp, char *s, int32 opcod, 
 int32 amode, int32 mreg, size_t disp, char *lab, int32 arg_no)
{
 struct insn_info_t *iip;
 char s1[RECLEN], s2[RECLEN]; 

 ll_bld_amode_str(s1, amode, mreg, disp, lab);
 if (arg_no == 0)
  {
   ll_bld_amode_str(s2, AM_NDXREG, ESP, -1, NULL);
  }
 else ll_bld_amode_str(s2, AM_NDXREG_DISP, ESP, arg_no*WRDBYTES, NULL);

 iip = __to_iinfo_rec(opcod);
 sprintf(s, "\t%s\t%s, %s", iip->inam, s1, s2);
 emit_one_insn(fp, "%s\n", s);
}
#else
static void ll_pass_arg_insn_to_str(FILE *fp, char *s, int32 opcod, 
 int32 amode, int32 mreg, size_t disp, char *lab, int32 arg_no)
{
 int32 pass_reg;
 struct insn_info_t *iip;
 char s1[RECLEN], s2[RECLEN]; 

 /* AIV 08/28/09 - if using large model may need to change move type */
 if (__cvc_use_large_model)
  {
   if (amode == AM_LABEL)
    {
     /* DBG remove -- */
     if (opcod != I_MOVQ && opcod != I_MOVABSQ) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     opcod = I_MOVABSQ;
    }
  }

  
 ll_bld_amode_str(s1, amode, mreg, disp, lab);
 /* DBG remove -- */
 if (arg_no >= 7) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 /* __alnk_init_nchglst_el - takes 7 arguments so last is on the stack */
 /* following 64-bit argument passing conventions */
 if (arg_no == 6) 
  {
   if (opcod == I_MOVABSQ)
    {
     /* mem to mem here need an extra move into %rax */
     sprintf(s, "\tmovabsq\t%s, %%rax", s1);
     emit_one_insn(fp, "%s\n", s);
     ll_bld_amode_str(s2, AM_NDXREG, AR_SP, -1, NULL);
     sprintf(s, "\tmovq\t%%rax, %s", s2);
     emit_one_insn(fp, "%s\n", s);
     return;
    }
   ll_bld_amode_str(s2, AM_NDXREG, AR_SP, -1, NULL);
  }
 else
  {
   pass_reg = __passed_regs_order[arg_no];
   ll_bld_amode_str(s2, AM_REG, pass_reg, -1, NULL);
  }

 iip = __to_iinfo_rec(opcod);
 sprintf(s, "\t%s\t%s, %s", iip->inam, s1, s2);
 emit_one_insn(fp, "%s\n", s);
}
#endif

/*
 * bld an insn string from insn number and amodes - 1 operand version
 */
static char *ll_1op_insn_to_str(char *s, int32 opcod, int32 amode,
 int32 mreg, int32 disp, char *labnam)
{
 struct insn_info_t *iip;
 char s1[RECLEN], s2[RECLEN]; 

 ll_bld_amode_str(s1, amode, mreg, disp, labnam);
 iip = __to_iinfo_rec(opcod);
 /* SJM 07/02/08 - ATT as syntax inconsistent in that $ prefix char */ 
 /* for call insns and jump insns are always treated as addresses */
 if (iip->inum == I_CALL) 
  {
   strcpy(s2, &(s1[1]));
   strcpy(s1, s2);
  }
 sprintf(s, "\t%s\t%s", iip->inam, s1);
 return(s);
}

/*
 * build a string from an amode triple
 *
 * SJM 07/01/08 - maybe should support label (equ? also .glob?) disps  
 * for ndx reg disp amodes
 */
static char *ll_bld_amode_str(char *s, int32 amode, int32 mreg,
 size_t disp, char *lab)
{
 switch (amode) {
  case AM_IMM:
#ifdef __CVC32__
   sprintf(s, "$%d", disp);
#else
   sprintf(s, "$%lu", disp);
#endif
   break;
  case AM_LABEL:
   sprintf(s, "$%s", lab);
   break;
  case AM_REG:
   sprintf(s, "%s", __regs[mreg]); 
   break;
  case AM_NDXREG:
   sprintf(s, "(%s)", __regs[mreg]); 
   break;
  case AM_NDXREG_DISP:
#ifdef __CVC32__
   sprintf(s, "%d(%s)", disp, __regs[mreg]); 
#else
   sprintf(s, "%lu(%s)", disp, __regs[mreg]); 
#endif
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * ROUTINE TO ASM AND LINK DESIGN MODEL (ALL .S FILES) INTO LIBRARY  
 */

/*
 * generate the one design wide .s file, assemble and then
 *
 * link all .s files into the library - finally use dlysm linking
 * to dynamically link the varous .s files and RT externs
 *
 * works by building and exec make file to assemble all .s files and link
 * the .so lib
 */
extern int32 __asm_and_link_dsgn_so_lib()
{
 time_t secs, msecs; 

 __my_ftime(&(secs), &(msecs));
 strcpy(__xs, ctime(&(secs)));
 //?? __my_fprintf(stdout, "*** before asm elapsed time %s\n", __xs);
     
 /* AIV 11/24/08 - need to unlink the previously built exe */
 unlink(__exe_name);

 /* gen design wide asm file (now all data storage excepts contab) */
 if (__show_asm) gen_mkfil_and_compile_solib();
 else pipe_cvcsim();

 __my_ftime(&(secs), &(msecs));
 strcpy(__xs, ctime(&(secs)));
 //?? __my_fprintf(stdout, "*** after asm elapsed time %s\n", __xs);
 return(TRUE);
}

/*
 * ROUTINES TO CREATE AND RUN MAKEFILE FOR SHOW ASM OR SET UP PIPE TO ASM
 */

/*
 * build and write make files and then run make to assemble and then
 * dynamically link generated .s files - +show_asm case where not piping
 * .s file output into assmbler
 */
static void gen_mkfil_and_compile_solib(void)
{
 int32 i, j;
 FILE *fp;
 struct mod_t *mdp;
 struct sv_lib_t *svlp;
 char *cp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], comm_fnam[RECLEN];
  
 /* create exe_main.o/cvclib.o into tmp */
 create_cvclib_files(FALSE);

 if ((fp = __my_fopen(RUNTIME_MAKEFILE, "w")) == NULL)
  {
   __pv_err(2904, "unable to open CVC output code make file %s",  
    RUNTIME_MAKEFILE);
   return;
  }

 fprintf(fp, "ARCHFLGS = \n");
/* SJM can't use omit frame ptr because prevents using gdb --
   -- also -fno-strength-reduce doesn't do anything - needed for old pentiums
 fprintf(fp, "OPTFLGS=-fno-strength-reduce -fomit-frame-pointer\n");
--- */
 fprintf(fp, "OPTFLGS =\n");
 fprintf(fp, "LFLAGS = \n");
 fprintf(fp, "CC = " ASM_CC "\n");
#ifdef __CVC32__
 fprintf(fp, "CFLAGS = -no-pie -g -m32\n");
#else
 fprintf(fp, "CFLAGS = -no-pie -g\n");
#endif

 /* reprise auto heartbeat needs threads */
 /* SJM 02-07-13 - this is show asm makefile modules mode so OS tmp ok */
 /* AIV 04/22/10 - FST needs to link in -lz lib */
 fprintf(fp, "LIBS = /tmp/exe_main.o /tmp/cvclib.o " ASM_LIBS "\n");

 fprintf(fp, "ASMFLAGS = --gstabs\n");
 fprintf(fp, "\nOBJS=");

 i = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt, i++)
  {
   if (i != 0 && i % 4 == 0) fprintf(fp, " \\\n");
   fprintf(fp, " %s.o", __bld_asm_fnam_stem(__xs, mdp));
   /* may have partitoned large assembly files into multiple files */
   if (mdp->asm_partition_cnt != -1)
    {
     for (j = 0; j <= mdp->asm_partition_cnt; j++)
      {
       fprintf(fp, " %s_%d.o", __xs, j);
      }
    }
   fprintf(fp, " comm_M%d_nt.o", mdp->m_idnum);
  }
 __bld_asm_comm_fnam_stem(s1);
 fprintf(fp, " %s.o\n", s1);

 fprintf(fp, ".PHONY: all\n");
 fprintf(fp, "all:\tclean %s\n\n", __exe_name);
 fprintf(fp, "%s:\t$(OBJS)\n", __exe_name);
 sprintf(s2, "$(CC) $(CFLAGS) $(LIBS) $(OBJS) ");
 /* if has DPI .so libs need to add them to the makefile */
 for (svlp = __sv_lib_hdrp; svlp != NULL; svlp = svlp->svnxt)
  {
   sprintf(s3, "%s ", svlp->path);
   strcat(s2, s3);
  }
 /* AIV 12/30/10 - if DPI interp wrapper need to link in wrapper lib */
 if (__dpi_interp_wrapper_fnam != NULL)
  {
   sprintf(s3, "%s.o ", __dpi_interp_wrapper_fnam); 
   strcat(s2, s3);
  }

 fprintf(fp, "\t%s -o %s\n", s2, __exe_name);
 fprintf(fp, "\t-rm -f $(OBJS)\n");

 /* file extension assembly or C */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   cp = __bld_asm_fnam_stem(__xs, mdp);
   fprintf(fp, "%s.o:\n\t$(CC) $(CFLAGS) -c %s.s\n", cp, cp);
   fprintf(fp, "#\t-rm -f %s.s\n\n", cp);
   /* may have partitoned large assembly files into multiple files */
   if (mdp->asm_partition_cnt != -1)
    {
     for (j = 0; j <= mdp->asm_partition_cnt; j++)
      {
       fprintf(fp, "%s_%d.o:\n\t$(CC) $(CFLAGS) -c %s_%d.s\n", cp, j, cp, j);
       fprintf(fp, "#\t-rm -f %s_%d.s\n\n", cp, j);
      }
    }
   fprintf(fp, "comm_M%d_nt.o:\n\t$(CC) $(CFLAGS) -c comm_M%d_nt.s\n", 
     mdp->m_idnum, mdp->m_idnum);
  }
 /* finally add the .bss net and constant storage file */
 /* use first module for comm fnam info */
 sprintf(comm_fnam, "%s", s1);
 fprintf(fp, "%s.o:\n\t$(CC) $(CFLAGS) -c %s.s\n", comm_fnam, comm_fnam);
 fprintf(fp, "#\t-rm -f %s.s\n\n", comm_fnam);

 /* SJM 07/20/05 - this make sure .so files removed */
 fprintf(fp, ".PHONY: clean\n");
 fprintf(fp, "clean:\n\t-rm -f %s\n", __exe_name);
 fprintf(fp, "\t-rm -f $(OBJS)\n");
 __my_fclose(fp);

 run_makefile();
}

/*
 * for normal compilation run ln (linker) command by piping all object
 * files into the linker input stream
 */
static void pipe_cvcsim(void)
{
 FILE *pp;
 struct mod_t *mdp;
 struct sv_lib_t *svlp;
 char s1[RECLEN], cmd[RECLEN], s2[RECLEN], fname[RECLEN], libs[RECLEN]; 
 char *objfiles, *cmd2, *dpi_objfiles;
 int32 size, slen, osize, allocsize, i, max_size, dpi_len;

 /* AIV FIXME - when making release do something about library naming */
 /* linker flags */
#ifdef __CVC32__
 /* reprise auto heartbeat needs threads */
 /* AIV 04/22/10 - FST needs to link in -lz lib */
 strcpy(libs, " -m32 " ASM_LIBS);
#else
 strcpy(libs, " " ASM_LIBS);
#endif

 /* AIV 03/24/09 - if has PLI need to compile with this flag for .so to */
 /* resolve symbols back into compiled binary */
 /* AIV 04/07/09 - if design has pli but no +pli access must also include */
 /* the flag - this way if design doesn't use cb may still link/work */
 if (__pli_access_level ||  __design_has_ld_pli_libs)
  {
   strcat(libs, " -export-dynamic");
  }

 /* create exe_main.o/cvclib.o into tmp */
 create_cvclib_files(TRUE);

 /* AIV 09/02/09 - use new temp area random generated file names */
 /* these are now generated in v_bbgen - need distinct names */
 /* for multicore to work correctly */
 /* AIV LOOKATME - don't think flags matter here already compiled with -02 */
 /* gcc just does the linking */
#ifdef __CVC_DEBUG__
 sprintf(cmd, ASM_CC " -no-pie -o %s %s %s ", __exe_name, __exe_file_name, 
   __cvclib_file_name);
#else
 sprintf(cmd, ASM_CC " -no-pie -O2 -o %s %s %s ", __exe_name, __exe_file_name,
  __cvclib_file_name);
#endif

 /* add comm_ storage file */ 
 /* the file object name string can be extra long so must malloc/realloc */
 allocsize = RECLEN;
 objfiles = __my_malloc(sizeof(char)*allocsize);
 sprintf(objfiles, "%s", __comm_file_name);
 size = strlen(objfiles);
 /* add all object files */ 
 /* AIV LOOKATME - concat all object files - for some unknown reason */
 /* fwrite was giving me a broken pipe - better to just write to pipe ??? */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   sprintf(s1, " %s", __bld_asm_fnam_stem(__xs, mdp));
   size += strlen(s1);
   /* if many object files in large design may have to realloc */
   if (size >= allocsize)
    {
     osize = allocsize;
     allocsize *= 2;
     allocsize += size;
     objfiles = __my_realloc(objfiles, osize, allocsize);
    }
   strcat(objfiles, s1);

   /* may have partitoned large assembly files into multiple files */
   if (mdp->asm_partition_cnt != -1)
    {
     for (i = 0; i <= mdp->asm_partition_cnt; i++)
      {
       sprintf(s1, " %s_%d.o", __xs, i);
       size += strlen(s1);
       /* if many object files in large design may have to realloc */
       if (size >= allocsize)
        {
         osize = allocsize;
         allocsize *= 2;
         allocsize += size;
         objfiles = __my_realloc(objfiles, osize, allocsize);
        }
       strcat(objfiles, s1);
      }
    }
  }

 /* AIV 08/05/09 - seperate init file placed on the end of list */
 /* AIV 03/02/12 - each module now has its own init file */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* if not using initialization file due to small partition continue */
   if (!mdp->m_using_init_file) continue;
   sprintf(s2, " %s ", __comm_nt_file_names[mdp->m_idnum]);

   size += strlen(s2);
   /* if many object files in large design may have to realloc */
   if (size >= allocsize)
    {
     osize = allocsize;
     allocsize *= 2;
     allocsize += size;
     objfiles = __my_realloc(objfiles, osize, allocsize);
    }
   strcat(objfiles, s2);
  }

 /* need to add some space for potential tmp make file */
 dpi_len = 0;
 if (__sv_lib_hdrp != NULL)
  {
   for (svlp = __sv_lib_hdrp; svlp != NULL; svlp = svlp->svnxt)
    {
     dpi_len += (strlen(svlp->path) + 2);
    }
   dpi_len++;
   /* AIV 12/30/10 - if DPI interp wrapper need to link in wrapper lib */
   /* AIV 12/31/10 - this has " " and ".so" added below add extra */
   /* AIV 01/05/10 - this can be NULL if never called */
   if (__dpi_interp_wrapper_fnam != NULL)
    {
     dpi_len += (strlen(__dpi_interp_wrapper_fnam)+20); 
    }
  }

 /* AIV 02/10/12 - moved -lz -ld, etc libs here apparently the order does */
 /* matter if -lz is placed on the end it is only searched if needed */
 /* also need to include the libs length here */
 slen = strlen(cmd) + size + 10 + dpi_len + strlen(libs) + 1;
 cmd2 = __my_malloc(sizeof(char)*slen);
 /* concat all object file list */ 
 strcpy(cmd2, cmd);
 strcat(cmd2, objfiles);
 /* if at the begging it must always be search and found */
 strcat(cmd2, libs);

 /* if has DPI .so libs need to link them in as well */
 if (__sv_lib_hdrp != NULL)
  {
   dpi_objfiles = (char *) __my_malloc(dpi_len);
   svlp = __sv_lib_hdrp;
   sprintf(s2, " %s ", svlp->path);
   strcpy(dpi_objfiles, s2);
   for (svlp = svlp->svnxt; svlp != NULL; svlp = svlp->svnxt)
    {
     sprintf(s2, " %s ", svlp->path);
     strcat(dpi_objfiles, s2);
    }
   /* AIV 12/30/10 - if DPI interp wrapper need to link in wrapper lib */
   if (__dpi_interp_wrapper_fnam != NULL)
    {
     sprintf(s2, " %s.o ", __dpi_interp_wrapper_fnam); 
     strcat(dpi_objfiles, s2);
    }
   strcat(cmd2, dpi_objfiles);
   __my_free(dpi_objfiles, dpi_len);
  }
 slen += dpi_len;


 /* AIV 11/13/09 - if large design cannot pipe > ARG_MAX */
 /* so new scheme is to print to file and exec file */
 /* just making this a large num for now */
 max_size = 10000;
 if (slen > max_size)
  {
   if (exec_command_file(cmd2, fname) == -1) return;
  }
 else
  {
   if ((pp = popen(cmd2, "w")) == NULL)
    {
     __pv_err(2904, "unable to open pipe %s", cmd2);  
     return;
    }
   pclose(pp);
  }


 /* remove the obj files in the obj directory */
 strcpy(cmd2, cmd);
 if (slen > max_size)
  {
   /* remove temp area execfile and obj files */
   sprintf(cmd2, "rm %s %s %s %s", objfiles, __exe_file_name, 
     __cvclib_file_name, fname);
   /* remove temp area rmexec file */
   if (exec_command_file(cmd2, fname) == -1) return;
   sprintf(cmd2, "rm %s", fname); 
   system(cmd2);
  }
 else
  {
   sprintf(cmd2, "rm %s %s %s", objfiles, __exe_file_name, __cvclib_file_name);
   if ((pp = popen(cmd2, "w")) == NULL)
    {
     __pv_err(2904, "unable to open pipe %s", cmd2);  
     return;
    }
   pclose(pp);
  }
 
 __my_free(cmd2, sizeof(char)*slen);
 __my_free(objfiles, sizeof(char)*allocsize);
}
   

/*
 * for large designs with a large number of files
 * gcc piping of large numbers ARG_MAX must be first written to a file
 * and then exec the file
 */
static int32 exec_command_file(char *cmd, char *fname)
{
 FILE *pp, *fp;


 /* get a tmp exec unique name */
 sprintf(fname, "%s/mk-XXXXXX", __objdir_path);
 if (__get_tmpfnam(fname) == -1)
  {
   __pv_err(2904, "unable to write open tmp exec file %s", fname);  
   return(-1);
  }
 /* open the file */
 if ((fp = __my_fopen(fname, "w")) == NULL)
  {
   __pv_err(2904, "unable to write pipe file %s", fname);  
   return(-1);
   }
 /* print the command to the file */
 fprintf(fp, "%s\n", cmd);
 fclose(fp);
 if (chmod(fname, S_IXUSR|S_IRUSR|S_IWUSR) == -1)
  {
   __pv_err(2904, "unable exec compile file %s", fname);  
   return(-1);
  }
 /* exec the command */
 if ((pp = popen(fname, "w")) == NULL)
  {
   __pv_err(2904, "unable to open pipe %s", cmd);  
   return(-1);
  }
 pclose(pp);
 return(0);
}
 
/*
 * write the binary files cvclib.o/exe_main.o into temp area which may be
 * objdir path specified by user
 */
static void create_cvclib_files(int32 is_pipe)
{
 /* AIV 09/02/09 - if piping use new temp area random file names */
 if (is_pipe)
  {
   /* DBG remove -- */
   if (__exe_file_name == NULL) __misc_terr(__FILE__, __LINE__);
   if (__cvclib_file_name == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */
   write_binary_file(__cvclib_file_name, (byte *) __cvclib_str, __cvclib_size);
   write_binary_file(__exe_file_name, (byte *) __exe_main_str, __exe_main_size);
  }
 else
  {
   /* SJM 02-07-13 - for non piping i.e. makefile modules must go in real tmp */
   write_binary_file("/tmp/cvclib.o", (byte *) __cvclib_str, __cvclib_size);
   write_binary_file("/tmp/exe_main.o", (byte *) __exe_main_str, 
    __exe_main_size);
  }
}


/*
 * dump in object file into temp area
 */
#define WBUFSIZ 0x4000   
static void write_binary_file(char *fname, byte *str, int32 size)
{
 int32 cursize;
 byte *cp;
 FILE *fp;

 if ((fp = __my_fopen(fname, "w")) == NULL)
  {
   __pv_err(2904, "unable to write cvc library file");
   return;
  } 

 //AIV LOOKATME - better I/O to copy to a local buf first?????????
 cp = str;
 for (cursize = size; cursize >= 0; )
  {
   fwrite(cp, 1, WBUFSIZ, fp);
   cp += WBUFSIZ;
   cursize -= WBUFSIZ;
   if (cursize <= WBUFSIZ)
    {
     fwrite(cp, 1, cursize, fp);
     break;
    }
  }
 fclose(fp);
}

/*
 * invoke system to run make file to assemble gen asm insns
 */
static void run_makefile(void)
{
 if (system("make -f makefile.modules >&/dev/null") < 0)
 {
  __pv_err(2903,
    "unable to assemble generated code, try manually running: 'make -f makefile.modules");
 }
}

/*
 * ROUTINES TO PRINT CVC STATS
 */

/*
 * print the bblk and insn numbers stats for one module
 */
extern void __prt_1fg_cvc_stats(struct flowg_t *fgp, struct mod_t *mdp)
{
 int32 nblks;
 struct bblk_t *bbp;

 __my_fprintf(stdout,
  "***STAT: printing stats for flow graph %p in module %s\n", fgp,
  mdp->msym->synam);
 nblks = cnt_bblk_num(fgp); 
 __my_fprintf(stdout, "*STAT: FG %p (%s) contains %d basic blocks\n",
  fgp, __to_flowgnam(__xs, fgp), nblks);

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt) 
  {
   prt_1bblk_cvc_stats(fgp, bbp);
  }
 __my_fprintf(stdout, "\n");
}

/*
 * count number of basic blocks in flowg
 */
static int32 cnt_bblk_num(struct flowg_t *fgp)
{
 int32 num_bblks;
 struct bblk_t *bbp;

 num_bblks = 0;
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt) num_bblks++;
 return(num_bblks);
}

/*
 * print cvc compiler stats for one basic block
 */
static void prt_1bblk_cvc_stats(struct flowg_t *fgp, struct bblk_t *bbp)
{
 int32 num_insns, num_predom_bblks; 
 struct insn_t *ip;
#ifdef __VALTRK__
 int32 rpo_num;
#endif

 num_insns = 0;
 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt) num_insns++;

 num_predom_bblks = 0; 
#ifdef __VALTRK__
 rpo_num = bbp->revpostordno;
 for (;;)
  {
   if (rpo_num == 0) break;
   rpo_num = fgp->predoms[rpo_num];
   num_predom_bblks++;
  }
#endif

 __my_fprintf(stdout,
  "*STAT: bblk %0d AFS=%0d nvi=%0d nmi=%0d, predom path to root len=%0d\n",
  bbp->bblk_seqno, bbp->after_suspend, num_insns, num_insns, num_predom_bblks);
}

/*
 * ROUTINES TO IMPLEMENT FASTER popen
 */

/*
 * wrapper to either to regular popen or new faster my_popen
 */
static FILE *do_popen(char *cmd, char *rw)
{
 if (__my_popen) return(my_popen());
 else return(popen(cmd, rw));
}

/*
 * wrapper to either to regular pclose or new faster my_pclose
 */
static void do_pclose(FILE *pp)
{
 if (__my_popen) my_pclose(pp);
 else pclose(pp);
}

#define POPEN_STACK_SIZE 64*1024
/*
 * do faster popen which uses lighter weight clone call
 * normal popen copies some memory so for large designs which use lots of
 * memory popens can run slow
 */
static FILE *my_popen(void) 
{
 pid_t pid;
 void *stack, *stack_aligned;
 FILE *fp;
#ifndef __CVC32__
 size_t tmp;
#endif

 /* 0 read 1 write  */
 if (pipe(__asm_pipefd) != 0) return(NULL);

 /* alloc stack to run thread */
 stack = __my_malloc(POPEN_STACK_SIZE);
 __asm_stack = stack;

 /* align stack on 16 bytes */
 stack_aligned = stack+POPEN_STACK_SIZE/sizeof(void **);

#ifndef __CVC32__
 /* DBG remove -- */
 tmp = (size_t) stack_aligned;
 if ((tmp % 16) != 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */
#endif

 /* DBG remove --
 __cv_msg("parent pid=%d\n", getpid());
 -- */
 pid = clone(popen_child_process_func, stack_aligned, 
        CLONE_VM|SIGCHLD|CLONE_VFORK, NULL);
 if (pid <= 0) return(NULL);

 /* DBG remove -- */
 //__cv_msg("pid=%d\n", pid);
 /* ---- */
 /* parent process */
 __asm_pid = pid;

 /* not reading */
 if (close(__asm_pipefd[0]) != 0) 
   return(NULL);

 /* write */
 fp = fdopen(__asm_pipefd[1], "w");

 if (fp == NULL) return(NULL); 

 return(fp);
}

/*
 * close unused pipes and call exec to assembler
 */
static int32 popen_child_process_func(void *empty) 
{
 char *args[5];

 /* it cannot close/dup emit error message */
 if (close(__asm_pipefd[1]) != 0) goto failed;

 if (close(STDIN_FILENO) != 0) goto failed;

 if (dup2(__asm_pipefd[0], STDIN_FILENO) == -1) goto failed;

 if (close(__asm_pipefd[0]) != 0) 
  {
failed:
   __pv_err(2905, "popen_child_process");
   __misc_terr(__FILE__, __LINE__);
  }

 /* call exec to assembler with assembly file name global */
#ifdef __CVC32__
 args[0] = "as"; 
 args[1] = "--32"; 
 args[2] = "-o"; 
 args[3] = __asm_file_name; 
 args[4] = (char *) 0; 
 execvp("as", args);
#else
 args[0] = "as"; 
 args[1] = "-o"; 
 args[2] = __asm_file_name; 
 args[3] = (char *) 0; 
 execvp("as", args);
#endif

 /* execvp will only return here on error */
 /* DBG remove -- */
 __misc_terr(__FILE__, __LINE__);
 /* ----- */
 return(0);
}

/*
 * wait for child process and close pipe
 */
static void my_pclose(FILE *fp) 
{
 int32 status;

 /* close write pipe */
 if (fclose(fp) != 0) __misc_terr(__FILE__, __LINE__);

 /* DBG remove -- 
 __cv_msg("in pid=%d waiting=%d\n", getpid(), __asm_pid);
 ------*/

 /* wait for clone child process to terminate */
 if (waitpid(__asm_pid, &status, 0) != __asm_pid) 
   __misc_terr(__FILE__, __LINE__);

 /* status better return fine */
 if (status != 0) __misc_terr(__FILE__, __LINE__);

 __my_free(__asm_stack, POPEN_STACK_SIZE);
 __asm_pid = 0;
}
