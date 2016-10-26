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
 * debugger - 2nd file most listing and break point routines 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifndef __NOSIGS__
#include <signal.h>
#endif

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

/* local prototypes */
static void get_middle_linrng(int32, int32 *, int32 *);
static struct incloc_t *find_incloc(int32);
static int32 change_srcfile(int32);
static int32 get_lastfillin(int32);
static int32 bld_filpostab(int32);
static void prt_brkpts(void);
static char *to_brkptnam(char *, word32);
static char *to_basename(char *, int32);
static void dbg_info_disp(void);
static int32 parse_scope_ref(t_midat **, struct task_t **, int32 *,
 int32 *, int32 *);
static int32 try_get_fillin_ref(char *, int32 *, int32 *, char **, char **);
static int32 local_scope_ref(char *, t_midat **, struct task_t **);
static int32 find_infil_ind(char *);
static int32 fil_lin_toscope(int32, int32, t_midat **, struct task_t **);
static int32 scope_lini_inrng(int32, int32, int32, int32, int32, int32);
static struct incloc_t *find2_incloc(int32);
static void set_scope_loc(t_midat *, struct task_t *, int32 *, int32 *);
static int32 get_ibrk_linref(t_midat *, struct task_t *, int32 *, int32 *);
static void init_brkpt(struct brkpt_t *);
static void insert_brkpt(struct brkpt_t *);
static struct st_t *conv_line_tostmt(struct mod_t *, struct task_t *, int32,
 int32);
static struct st_t *find_nxtstp(struct st_t *, int32, int32);
static struct st_t *find_lstofsts_stp(struct st_t *, int32, int32);
static struct incloc_t *find3_incloc(int32, int32);
static struct st_t *find_case_stp(struct st_t *, int32, int32);
static struct st_t *find_afterdflt(struct csitem_t *);
static void del_all_brkpts(void);
static void del_brkpt_num(int32);
static int32 cnt_same_brkpts(int32, int32, struct brkpt_t **);
static void del_all_disps(void);
static void del_disp_num(void);
static struct brkpt_t *rd_brkpt_num(char *, int32);
static struct brkpt_t *find_bpp(int32);
static int32 elim_brkpt_fromcond(struct brkpt_t *);
static void reinit_vars_and_state(void);
static void wr_1ev_trace(int32, struct tev_t *);
static void fill_near_evtab(int32, int32);
static int32 try_add_wrkevtab(struct tev_t *, int32, int32 *, int32);
static int32 get_var_scope(t_midat **, struct task_t **, int32 *);

/* extern prototypes (maybe defined in this module) */
extern void __do_scope_list(void);
extern void __do_dbg_list(void);
extern void __prt_src_lines(int32, int32, int32);
extern void __do_dbg_set(void);
extern int32 __get_dbg_val(void);
extern void __do_dbg_info(void);
extern void __do_dbg_scope(void);
extern void __set_dbentry_listline(void);
extern void __set_scopchg_listline(void);
extern void __do_dbg_history(void);
extern void __do_dbg_emptyhistory(void);
extern int32 __do_dbg_nextb(void);
extern void __do_dbg_brkpt(int32);
extern void __do_dbg_ibrkpt(int32);
extern void __do_dbg_delbrkdis(void);
extern void __dbg_undisplay(void);
extern void __do_dbg_dis_enable(int32);
extern void __dbg_brk_ignore(void);
extern void __dbg_brk_cond(void);
extern int32 __process_brkpt(struct st_t *);
extern void __reset_to_time0(void);
extern void __cleanup_dumpports(void); 
extern void __write_snapshot(int32);
extern void __prt_where_msg(struct thread_t *);
extern void __dmp_tskthrds(void);
extern void __dmp_tskthd(struct task_t *, struct mod_t *);
extern void __dmp_initalw_thrd_tree(void);
extern void __dmp_thrd_tree(struct thread_t *);
extern void __dmp_thrd_info(struct thread_t *);
extern void __dmp_all_thrds(void);

extern char *__msg_idp_blditree(char *, t_midat *, struct task_t *);
extern char *__msg_cur_blditree(char *, struct task_t *);
extern void __get_vtok(void);
extern char *__prt_vtok(void);
extern int32 __chk_extra_atend(int32);
extern int32 __tilde_open(char *, int32);
extern void __my_free(void *, size_t);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern int32 __get_dbcmdnum(char *, struct namlst_t *, int32);
extern char *__bld_ambiguous_list(char *, char *, struct namlst_t *, int32);
extern char *__schop(char *, char *);
extern char *__to_tsktyp(char *, word32);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern void __call_misctfs_scope(void);
extern void __vpi_iactscopechg_trycall(void);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern int32 __is_scope_sym(struct sy_t *);
extern t_midat *__xmrget_refgrp_to_targ(struct gref_t *);
extern void __exec_history_list(int32);
extern struct task_t *__find_thrdtsk(struct thread_t *);
extern char *__bld_lineloc(char *, word32, int32);
extern char *__msg2_blditree(char *, struct itree_t *);
extern char *__msg2_cur_blditree(char *);
extern struct expr_t *__rd_iact_expr(void);
extern int32 __colto_eol(void);
extern void __bld_xtree(int32);
extern void __free_xtree(struct expr_t *);
extern char *__to_timstr(char *, word64 *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern int32 __cvt_lngbool(word32 *, word32 *, int32); 
extern void __free_thd_list(struct thread_t *);
extern void __free_1thd(struct thread_t *);
extern void __do_iact_disable(struct hctrl_t *, int32);
extern void __free_telhdr_tevs(struct tev_t *);
extern void __free_1tev(struct tev_t *);
extern char *__pv_stralloc(char *);
extern void __my_fclose(FILE *);
extern void __my_close(int32);
extern void __reinit_tfrecs(void);
extern void __reinit_vpi(void);
extern void __reinit_sim(void);
extern void __reinitialize_vars(struct mod_t *);
extern void __initialize_dces(struct mod_t *);
extern void __init_all_inst_gate_state(struct gate_t *, struct mod_t *);
extern void __set_pre_idp_nchgaction_bits(void);
extern void __init_all_inst_udp_state(struct gate_t *, struct mod_t *);
extern void __allocinit_perival(union pck_u *, int32, int32, int32);
extern void __reinit_all_contas_in_mod(struct mod_t *);
extern void __reinit_mipd(struct mod_pin_t *, struct mod_t *);
extern char *__gstate_tostr(char *, struct gate_t *, int32);
extern char *__to_evtrcanam(char *, struct conta_t *, t_midat *);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern void __ld_val(word32 *, word32 *, word32 *, int32);
extern void __st_standval(byte *, struct xstk_t *, byte);
extern char *__st_regab_tostr(char *, byte *, int32);
extern char *__regab_tostr(char *, word32 *, word32 *, int32, int32, int32);
extern char *__bld_valofsched(char *, struct tev_t *);
extern char *__to_cur_evtrwnam(char *, struct net_t *, int32, int32);
extern char *__to_vvstnam(char *, word32);
extern void __ld_bit(word32 *, word32 *, struct net_t *, int32);
extern char *__to_vvnam(char *, word32);
extern char *__to_mpnam(char *, char *);
extern char *__xregab_tostr(char *, word32 *, word32 *, int32, struct expr_t *);
extern char *__get_tfcellnam(struct tfrec_t *);
extern char *__to_tetyp(char *, void *);
extern char *__to_dcenam(char *, word32);
extern char *__to_sytyp(char *, word32);
extern void __init_mod(struct mod_t *, struct sy_t *);
extern void __free_1glb_flds(struct gref_t *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern char *__to_ptnam(char *, word32);
extern char *__msg_blditree(char *, struct itree_t *, struct task_t *);

extern struct tev_t *__get_next_time_header(void);
#ifdef __STREE__
extern void __restore_min_time_nodes(int32); 
#else
extern void __restore_min_time_heap(int32); 
#endif

extern void __fst_close(void);

extern void __cv_msg(char *, ...);
extern void __cvsim_msg(char *, ...);
extern void __cvsim2_msg(char *, ...);
extern void __dbg_msg(char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __ia_err(int32 id_num, char *s, ...);

extern void __process_conta_ev(void);
extern void __process_wire_ev(void);
extern void __process_mipd_nchg_ev(void);
extern void __process_nbpa_ev(void);
extern void __process_gatechg_ev(void);
extern void __process_trpthdst_ev(void);
extern void __process_putpdel_ev(void);
extern void __process_vpidrv_ev(void);
extern void __process_thrd_ev(void);
extern void __sync_call_misctf(void);
extern void __setdel_call_misctf(void);

extern const char __pv_ctab[];

/*
 * ROUTINES TO IMPLEMENT SOURCE LISTING 
 */

/*
 * do the entire scope list for $list command
 * know current scope needs to be listed - caller set and restores 
 *
 * leave list line at end but if different scope form will be restored there 
 */
extern void __do_scope_list(void)
{
 int32 ifi, fr_ifi, to_ifi, fr_lini, to_lini, maxlini;
 struct mod_t *mdp;
 struct itree_t *itp;

 if (__scope_tskp != NULL)
  {
   fr_ifi = (int32) __scope_tskp->tsksyp->syfnam_ind;
   fr_lini = __scope_tskp->tsksyp->sylin_cnt;
   to_ifi = __scope_tskp->tsk_last_ifi;
   to_lini =  __scope_tskp->tsk_last_lini;
  }
 else
  {
   mdp = (struct mod_t *) __scope_idp[MD_MDP];
   fr_ifi = (int32) mdp->msym->syfnam_ind;
   fr_lini = mdp->msym->sylin_cnt;
   to_ifi = mdp->mod_last_ifi;
   to_lini = mdp->mod_last_lini;
  }
 /* normal case - all in one file - current file will include scope by here */
 
 if (fr_ifi == to_ifi)
  {
   itp = (struct itree_t *) __scope_idp[MD_ITP];
   __cvsim_msg("  Listing \"%s\" type %s file: %s\n",
    __msg_idp_blditree(__xs, __scope_idp, __scope_tskp),
    itp->itip->imsym->synam, __in_fils[fr_ifi]);  
   __prt_src_lines(fr_ifi, fr_lini, to_lini);
   return;
  }

 __cvsim_msg("  File: %s\n", __in_fils[fr_ifi]);  
 if ((maxlini = get_lastfillin(fr_ifi)) == -1) return; 
 __prt_src_lines(fr_ifi, fr_lini, maxlini);
 /* print intermediate files */
 for (ifi = fr_ifi + 1; ifi < to_ifi; ifi++) 
  {
   __cvsim_msg("  File: %s\n", __in_fils[ifi]);  
   if ((maxlini = get_lastfillin(ifi)) == -1) return; 
   __prt_src_lines(ifi, 1, maxlini);
  }
 __cvsim_msg("  File: %s\n", __in_fils[to_ifi]);  
 __prt_src_lines(to_ifi, 1, to_lini);
 /* this leave current list line after last listed */
}

/*
 * execute a list command
 * caller checks for any wrong extra characters at end
 *
 * current file is always file where header line of current scope is.
 * can give explist [file]:num list - which does not change current file
 * :l or ":l +" - list next ten lines (keep track of current list line)
 * :l- (list 10 lines to previous first
 * :l [+/-] number (list 10 lines with current in middle) 
 *   use :l +0 to list -5 to + 5 around current line 
 * :l [+/-][line1], [+/-][line2] or :l ,[+/-][line2] or :l [+/-][line1], 
 * :l ++/:l -- (move to next/prev. file) 
 * :l [file]:[line] (does not need to be in scope)
 * :l [scope] (first line of scope)
 *
 * this does not change scope
 */
extern void __do_dbg_list(void)
{
 int32 ltmp, lno1, lno2, rel_val, maxifi, maxlini, ifi, lini;
 struct task_t *tskp;
 t_midat *in_idp;
 struct itree_t *itp;
 struct sy_t *syp;
 struct incloc_t *ilp;
 char *savchp, *endchp;

 rel_val = ' ';
 /* here savchp is 1st char after leading white space - endchp first after */
 /* return F on error, if is [file]:[line] form ifi not -1 */
 if (!try_get_fillin_ref(__visp->vichp, &ifi, &lini, &savchp, &endchp))
  return;

 /* [file]:[line] is lines around loc. */
 if (ifi != -1)
  {
   if ((maxlini = get_lastfillin(ifi)) == -1) return; 
   if (lini > maxlini)
    {
     __ia_err(1469,
      "[file]:[line] reference line number %d too large - %s has %d lines",
      lini, __in_fils[ifi], maxlini);
     return;
    }
   __visp->vichp = endchp;
   __list_arg_lini = lini;
   get_middle_linrng(lini, &lno1, &lno2);
   __prt_src_lines(ifi, lno1, lno2);
   goto done;
  }

 /* parse from beginning of line */
 __visp->vichp = savchp;
 /* case 1: :l or ":l +" lists next 10 lines */
 __get_vtok();
 if (__toktyp == TEOF) 
  {
do_l:
   /* here for :br, line current before list */
   __list_arg_lini = __list_cur_lini;
   __prt_src_lines(__list_cur_ifi, __list_cur_lini, __list_cur_lini
    + __list_cur_listnum);
   return;
  }

 /* if starts with letter or _ or $ must be scope */
 /* this is not around since want to see scope */
 if (__toktyp == ID)
  {
   /* this reads xmr if needed */
   if (!get_var_scope(&in_idp, &tskp, &ltmp)) return;

   if (tskp != NULL) syp = tskp->tsksyp; 
   else 
    {
     itp = (struct itree_t *) in_idp[MD_ITP];
     syp = itp->itip->imsym;
    }
   ifi = (int32) syp->syfnam_ind;
   lno1 = syp->sylin_cnt; 
   __list_arg_lini = lno1;
   __prt_src_lines(ifi, lno1, lno1 + __list_cur_listnum + 1); 
   goto done;
  }

 if (__toktyp == PLUS)
  { 
   __get_vtok();

   /* :l ++ - move to next file if part of same scope - use task if set */
   /* notice always have dbg current file and line */
   if (__toktyp == PLUS)
    {
     /* if in include file exit to first included from place */
     if ((ilp = find_incloc(__list_cur_ifi)) != NULL)
      {
       __list_arg_lini = ilp->incfrom_lcnt;
       /* list from include line forward */
       __prt_src_lines(ilp->incfrom_fnind, __list_arg_lini,
        __list_arg_lini + __list_cur_listnum + 1);
       goto done;
      }

     maxifi = __last_srcf;
     if (__list_cur_ifi >= maxifi)
      {
       __ia_err(1461, "':list ++' failed - no next source input file");    
       return;
      }
     /* notice this changes __list_cur_ifi and list cur fd if succeeds */
     __list_arg_lini = 1;
     __prt_src_lines(__list_cur_ifi + 1, 1, __list_cur_listnum + 1);
     goto done;
    }
   if (__toktyp == TEOF) goto do_l;
   rel_val = '+';
  }
 /* case 1a: "l -" lists previous 10 before the ten just listed */
 else if (__toktyp == MINUS)
  {
   __get_vtok();
   /* :l ++ - move to next file if part of same scope - use task if set */
   /* notice always have dbg current file and line */
   if (__toktyp == MINUS)
    {
     /* if in include file list back from first included from place */
     if ((ilp = find_incloc(__list_cur_ifi)) != NULL)
      {
       __list_arg_lini = ilp->incfrom_lcnt - __list_cur_listnum;
       if (__list_arg_lini < 1) __list_arg_lini = 1;
       /* list from include line forward */
       __prt_src_lines(ilp->incfrom_fnind, __list_arg_lini,
        ilp->incfrom_lcnt);
       goto done;
      }

     /* first source file is 2 */
     if (__list_cur_ifi <= 2)
      {
       __ia_err(1462, "':list --' failed - no previous source input file");
       return;
      }
     maxlini = get_lastfillin(__list_cur_ifi - 1); 
     __list_arg_lini = maxlini - __list_cur_listnum;  
     if (__list_arg_lini < 1) __list_arg_lini = 1;
     __prt_src_lines(__list_cur_ifi - 1, __list_arg_lini, maxlini);
     goto done;
    }
   if (__toktyp == TEOF) 
    {
     /* here :br argument is one before current line - place list ends */ 
     ltmp = __list_cur_lini - 2*(__list_cur_listnum + 1);
     __list_arg_lini = ltmp + __list_cur_listnum + 1;
     if (__list_arg_lini < 1) __list_arg_lini = 1;
     __prt_src_lines(__list_cur_ifi, ltmp, ltmp + __list_cur_listnum);
     return;
    }
   rel_val = '-';
  }

 /* know in current file */
 maxlini = get_lastfillin(__list_cur_ifi); 
 if (__toktyp == COMMA)  
  {
   if (rel_val != ' ')
    {
     __ia_err(1444, ":list command %c,[number] form illegal", rel_val); 
     return;
    }
   lno1 = -2;
   goto get_2nd_rng;
  }
 /* get 1st range */
 if ((ltmp = __get_dbg_val()) == -1) 
  {
   __ia_err(1445, ":list command first range value %s illegal", __prt_vtok());  
   return;
  } 

 /* know dbg current line in range - silently fix relative lines */
 if (rel_val == '-') lno1 = __list_cur_lini - ltmp; 
 else if (rel_val == '+') lno1 = __list_cur_lini + ltmp;
 else
  {
   /* but fix line must be in range */
   if (ltmp < 1 || ltmp > maxlini) 
    {
bad_lin_loc:
     __ia_err(1463, ":list line %d impossible - %s has %d lines", ltmp,
      __in_fils[__list_cur_ifi], maxlini); 
     return;
    }
   lno1 = ltmp;
  }

 /* case 2: :l [+/-][number] form */
 __get_vtok();
 if (__toktyp == TEOF)
  {
   __list_arg_lini = lno1;
   get_middle_linrng(lno1, &lno1, &lno2);
   __prt_src_lines(__list_cur_ifi, lno1, lno2);
   return;
  }
 if (__toktyp != COMMA)
  {
   __ia_err(1446,
    ":list command line number range separator expected - %s read",
    __prt_vtok());
   return;
  }
 /* case 3: [num], form */
get_2nd_rng:
 __get_vtok();
 if (__toktyp == TEOF)
  {
   if (lno1 == -2)
    {
     __ia_err(1447,
      ":list command line number range comma by itself illegal");
     return;
    }
   lno2 = lno1 + __list_cur_listnum;
   __list_arg_lini = lno1;
   __prt_src_lines(__list_cur_ifi, lno1, lno2);
   return;
  }
 if (__toktyp == PLUS || __toktyp == MINUS)
  {
   if (__toktyp == PLUS) rel_val = '+'; else rel_val = '-';
   __get_vtok();
  }
 else rel_val = ' ';
 /* get 2nd range */
 if ((ltmp = __get_dbg_val()) == -1) 
  {
   __ia_err(1448, ":list command second range value %s illegal", __prt_vtok()); 
   return;
  } 
 if (rel_val == '-') lno2 = __list_cur_lini - ltmp;
 else if (rel_val == '+') lno2 = __list_cur_lini + ltmp - 1;
 else
  {
   /* but fix line must be in range */
   if (ltmp < 1 || ltmp > maxlini) goto bad_lin_loc;
   lno2 = ltmp; 
  }
 /* correct for ,[num] form */
 if (lno1 == -1) lno1 = lno2 - __list_cur_listnum;
 if (lno1 > lno2)
  {
   __ia_err(1464, ":list %d,%d - first range element larger than second",
    lno1, lno2);
   return;
  }
 __list_arg_lini = lno1;
 __prt_src_lines(__list_cur_ifi, lno1, lno2);

done:
 /* if did not read eof, need to check for nothing els on line */ 
 __chk_extra_atend(TRUE);
}

/*
 * compute range given line in middle and global number to list
 */
static void get_middle_linrng(int32 mid, int32 *rng1, int32 *rng2)
{
 int32 ltmp;

 if ((__list_cur_listnum % 2) == 0) ltmp = mid - __list_cur_listnum/2;
 else ltmp = mid - __list_cur_listnum/2 - 1;
 *rng1 = ltmp;
 *rng2 = ltmp + __list_cur_listnum;
}

/*
 * given an in_fils index that may be included find included loc record
 * returns nil if not included file
 */
static struct incloc_t *find_incloc(int32 ifi)
{
 struct incloc_t *ilp;

 for (ilp = __inclst_hdr; ilp != NULL; ilp = ilp->inclocnxt) 
  if (ilp->inc_fnind == ifi) return(ilp);
 return(NULL);
}

/*
 * print from frlini to stoplini in file fd (will open if needed) 
 * this uses same logic as gnu gdb list command
 *
 * frlini starts at 1 for first line
 * for listing of multiple files, caller must decompose 
 * FIXME - need to output OS returned message
 */
extern void __prt_src_lines(int32 ifi, int32 frlini, int32 stoplini)
{
 int32 c;
 int32 ctrlc_stop, nlines, cnt;
 char ctab[8];
 struct filpos_t *fposp;

 /* no source printing from interactive history event */ 
 /* DBG remove --- */
 if (ifi == 1) __arg_terr(__FILE__, __LINE__);
 /* --- */
 /* *** if (ifi == 1) return; */

 /* change source file if needed */
 if (__list_cur_ifi != ifi)
  {
   /* this emits error on file problem */
   if (!change_srcfile(ifi)) return;
  }
 if (stoplini - frlini > 20) ctrlc_stop = TRUE; else ctrlc_stop = FALSE;

 /* know file line start pos. cache built and current file open to get here */
 fposp = &(__filpostab[__list_cur_ifi]);

 /* adjust range, if absolute line list argument, must check above */
 if (frlini < 1) frlini = 1;
 if (stoplini < 1) stoplini = 1;
 if (stoplini > fposp->nlines) stoplini = fposp->nlines;
 if (frlini > fposp->nlines) frlini = fposp->nlines;
 __list_cur_lini = frlini;
 /* notice 0 means 1 line */
 nlines = stoplini - frlini;

 /* seek to line */
 if ((cnt = lseek(__list_cur_fd, (off_t) fposp->lpostab[__list_cur_lini - 1],
   0)) < 0)
  {
   __ia_err(1437, "unable to locate source line %d in %s",
     frlini, __in_fils[__list_cur_ifi]);
   return;
  }

 while (nlines-- >= 0)
  {
   if ((cnt = read(__list_cur_fd, ctab, 1)) != 1) break; 
   __cvsim_msg("%d\t", __list_cur_lini++);

   do {
    c = ctab[0];
    if (c < 040 && c != '\t' && c != '\n' && c != '\r')
     __cvsim_msg("^%c", c + 0100);
    else if (c == 0177) __cvsim_msg("^?");
    else __cvsim_msg("%c", c);
    /* notice this handles any system */
    /* under emx (dos vcpi and os2) sometimes will see return sometime not */
    /* return sometimes appears after using ^c a few times */ 
   } while (c != '\n' && (cnt = read(__list_cur_fd, ctab, 1)) == 1);
   /* for long lists, must allow ^c to stop */ 
   if (ctrlc_stop && __pending_enter_iact && __iact_reason == IAER_CTRLC)
    {
     __pending_enter_iact = FALSE;
     __iact_reason = IAER_UNKN;
     __cvsim_msg("Printing halted because interrupt (Ctrl-c) pressed.\n");
     break;
    }
  }
}

/*
 * chnage current source file - open new current and if needed build 
 * the line pos. tab for source
 * return F on error and do not change file
 *
 * only called if new_ifi different from current
 * know there will always be current source file in fils index
 */
static int32 change_srcfile(int32 new_ifi)
{
 int32 fd;
 struct filpos_t *fposp;
 struct stat st;

 /* if char pos of source lines table not built - build it and return */
 if (__filpostab == NULL) fposp = NULL;
 else fposp = &(__filpostab[new_ifi]); 
 /* build file line start char pos. table */ 
 if (fposp == NULL || fposp->lpostab == NULL)
  {
   /* if this fails, do not change current file */
   if ((fd = bld_filpostab(new_ifi)) == -1) return(FALSE); 
   goto good_end;
  }

 /* otherwise just open the file */
 if ((fd = __tilde_open(__in_fils[new_ifi], O_RDONLY)) < 0)
  {
op_err:
   __ia_err(1428,
    "unable to open or access new current debugger source file %s",
    __in_fils[new_ifi]);
   return(FALSE);
  }
 if (fstat(fd, &st) < 0) goto op_err;
 if (__start_time <= st.st_mtime)
  __ia_err(1429, "source file %s changed after simulation started",
   __in_fils[new_ifi]);
 
 /* know succeeded */
good_end:
 if (__list_cur_fd != -1)
  {
   /* LOOKATME - do not know name of source file here */
   /* still change even if cannot close */
   if (close(__list_cur_fd) != 0) 
    __ia_err(1451, "unable to close old current debugger source file");
  }
 __list_cur_ifi = new_ifi; 
 __list_cur_fd = fd;
 return(TRUE);
}

/*
 * get last line in file
 * this uses file position table - file can remain closed
 */
static int32 get_lastfillin(int32 ifi)
{
 struct filpos_t *fposp;

 /* if char pos of source lines table not built - build it and return */
 if (__filpostab == NULL) fposp = NULL;
 else fposp = &(__filpostab[ifi]); 
 /* build file line start char pos. table */ 
 if (fposp == NULL || fposp->lpostab == NULL)
  {
   /* if this fails, do not change current file */
   if (bld_filpostab(ifi) == -1) return(-1); 
  }
 return(fposp->nlines);
}

/*
 * build the line character position in file table for one file  
 * ifi is index of file in input file table
 * return file descriptor number on success or -1 on error
 * if success,  leaves file open
 *
 * know line char pos table not built and this adds to processed 
 * could free other linpostab when this built but now leaving all
 * know file not open
 */
static int32 bld_filpostab(int32 ifi)
{
 int32 i, buf_base, buf_size, fsize, nlines; 
 int32 fd, bytes, alloc_lines;
 size_t osize, nsize;
 int32 *linpostab;
 struct stat st;
 char buf[RDBUFSIZ];

 if ((fd = __tilde_open(__in_fils[ifi], O_RDONLY)) < 0)
  {
op_err:
   __ia_err(1428, "unable to open or access debugger current source file %s",
    __in_fils[ifi]);
   return(-1);
  }
 if (fstat(fd, &st) < 0) goto op_err;
 if (__start_time <= st.st_mtime)
  __ia_err(1429, "source file %s changed after simulation started", __in_fils[ifi]);
 fsize = (int32) st.st_size;
 linpostab = NULL;
 for (buf_base = 0, alloc_lines = 0, nlines = 0;;)
  {
   if (buf_base + RDBUFSIZ <= fsize) buf_size = RDBUFSIZ; 
   else buf_size = fsize - buf_base;

   if ((bytes = read(fd, buf, buf_size)) != buf_size)
    {
     __ia_err(1433,
      "error reading source file %s when building line position table",
      __in_fils[ifi]);
     if (alloc_lines != 0) __my_free(linpostab, sizeof(int32)*alloc_lines);
     if (close(fd) != 0) 
      __ia_err(1458, "unable to close source file %s after read error",
       __in_fils[ifi]);
     return(-1);
    }
   if (alloc_lines == 0)
    {
     alloc_lines = 1000;
     linpostab = (int32 *) __my_malloc(alloc_lines*sizeof(int32));
     linpostab[0] = 0;
     nlines = 1;
    }
   for (i = 0; i < buf_size;) 
    {
     /* a newline at the end of file does not start a new line */
     if (buf[i++] == '\n' && i < buf_size)
      {
       if (nlines == alloc_lines)
        {
         osize = (word32) alloc_lines*sizeof(int32);
         alloc_lines *= 2;
         linpostab = (int32 *) __my_realloc(linpostab, osize, 
          alloc_lines*sizeof(int32)); 
        } 
       linpostab[nlines++] = buf_base + i;
      }
    }
   if ((buf_base += buf_size) == fsize) break;
  } 
 
 /* final step is to allocate and fill parallel to __in_fils array of */
 /* file line info */ 
 if (__filpostab == NULL) 
  {
   __filpostab = (struct filpos_t *)
    __my_malloc((__last_srcf + 1)*sizeof(struct filpos_t));
   for (i = 0; i <= __last_srcf; i++)
    {
     __filpostab[i].nlines = 0;
     __filpostab[i].lpostab = NULL;
    }
  }
 /* know line table not built or will not be called */
 if (__filpostab[ifi].lpostab != NULL) __arg_terr(__FILE__, __LINE__);
 /* must adjust allocated line table down to right size if needed */
 if (nlines != alloc_lines)
  {
   osize = (word32) (alloc_lines*sizeof(int32));
   nsize = (word32) (nlines*sizeof(int32));
   linpostab = (int32 *) __my_realloc(linpostab, osize, nsize);
  }
 __filpostab[ifi].lpostab = linpostab; 
 __filpostab[ifi].nlines = nlines; 
 return(fd);
}

/*
 * ROUTINES TO IMPLEMENT COLON DEBUGGER SET COMMANDS
 */

#define SET_LSIZE 0
#define SET_HLSIZE 1
#define SET_SCHG 2
#define SET_NOSCHG 3
#define SET_PRTBASE 4 
#define SET_LOGECHO 5
#define SET_NOLOGECHO 6

/* set command options table */
static struct namlst_t setargs[] = {
 { SET_LSIZE, "listsize" }, 
 { SET_HLSIZE, "histlistsize" }, 
 { SET_SCHG, "scopechange" },
 { SET_NOSCHG, "noscopechange" },
 { SET_PRTBASE, "printbase" },
 { SET_LOGECHO, "logecho" },
 { SET_NOLOGECHO, "nologecho" }
};
#define NSETARGS (sizeof(setargs) / sizeof(struct namlst_t))

/*
 * execute debug set command - for now only :set listsize [number]
 */
extern void __do_dbg_set(void)
{
 char blet;
 int32 rv, lines;

 __get_vtok();
 if (__toktyp != ID)
  {
bad_setval:
   __ia_err(1441, ":set %s - debugger set parameter illegal or unknown",
    __prt_vtok());
   return;
  }
 rv = __get_dbcmdnum(__token, setargs, NSETARGS);
 switch (rv) {
  case -1: goto bad_setval;
  case -2:
   __ia_err(1422, "ambiguous :set %s parameter: %s", __token,
    __bld_ambiguous_list(__xs, __token, setargs, NSETARGS));
   return;
  case SET_LSIZE:
   __get_vtok();
   if ((lines = __get_dbg_val()) == -1) 
    { 
     __ia_err(1442,
      ":set listsize required number of lines value expected - %s read",
      __prt_vtok());
     return;
    }
   __list_cur_listnum = lines - 1;
   break;
  case SET_HLSIZE:
   __get_vtok();
   if ((lines = __get_dbg_val()) == -1) 
    { 
     __ia_err(1442,
      ":set histlistsize required command number value expected - %s read",
      __prt_vtok());
     return;
    }
   __hist_cur_listnum = lines;
   break;
  case SET_SCHG: __iact_scope_chg = TRUE; break;
  case SET_NOSCHG: __iact_scope_chg = FALSE; break;
  case SET_PRTBASE:
   __get_vtok();
   if (__toktyp != ID)
    { 
bad_base:
     __ia_err(1449,
      ":set printbase required default :print command base %s unrecognized",
      __prt_vtok());
     return;
    }
   blet = (isupper(__token[0])) ? tolower(__token[0]) : __token[0];
   if (blet == 'b') __dbg_dflt_base = BBIN; 
   else if (blet == 'o') __dbg_dflt_base = BOCT;
   else if (blet == 'h') __dbg_dflt_base = BHEX; 
   else if (blet == 'd') __dbg_dflt_base = BDEC;
   else goto bad_base;
   break;
  case SET_NOLOGECHO: __echo_iactcmds_tolog = FALSE; break;
  case SET_LOGECHO: __echo_iactcmds_tolog = TRUE; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 __chk_extra_atend(TRUE);
}

/*
 * get debugger value - return -1 on error - caller must emit message
 * this is only for positive values and expects token to have been read
 * this expects first token to have been read
 *
 * LOOKATME - notice slight memory link if error is string will not be freed
 */
extern int32 __get_dbg_val(void)
{
 int32 val;

 if (__toktyp != NUMBER || __itoklen > WBITS || __bcwrk[0] != 0L) return(-1);  
 val = (int32) __acwrk[0];
 if (val < -1) return(-1);  
 return(val);
}

/*
 * ROUTINES TO IMPLEMENT INFO COMMAND
 */
#define INFO_LSIZE 0
#define INFO_HLSIZE 1
#define INFO_SCHG 2
#define INFO_BRKPT 3
#define INFO_PRTBASE 4
#define INFO_LOGECHO 5
#define INFO_DISPLAY 6

/* info command options table */
static struct namlst_t infoargs[] = {
 { INFO_LSIZE, "listsize" }, 
 { INFO_HLSIZE, "histlistsize" }, 
 { INFO_SCHG, "scopechange" },
 { INFO_BRKPT, "breakpoints" },
 { INFO_PRTBASE, "printbase" },
 { INFO_LOGECHO, "logecho" },
 { INFO_DISPLAY, "displays" }
};
#define NINFOARGS (sizeof(infoargs) / sizeof(struct namlst_t))

/*
 * execute debug info command 
 */
extern void __do_dbg_info(void)
{
 int32 rv;
 char s1[RECLEN];
 
 __get_vtok();
 if (__toktyp != ID)
  {
bad_infoval:
   __ia_err(1443, ":info command parameter %s unknown", __prt_vtok());
   return;
  }

 rv = __get_dbcmdnum(__token, infoargs, NINFOARGS);
 switch (rv) {
  case -1: goto bad_infoval;
  case -2:
   __ia_err(1422, "ambiguous info %s command parameter: %s", __token,
    __bld_ambiguous_list(__xs, __token, infoargs, NINFOARGS));
   return;
  case INFO_LSIZE:
   __cvsim_msg("number of lines to list is %d\n", __list_cur_listnum + 1);
   break;
  case INFO_HLSIZE:
   __cvsim_msg("number of history commands to list is %d\n",
    __hist_cur_listnum);
   break;
  case INFO_SCHG:
   if (__iact_scope_chg)
    __cvsim_msg("interactive scope set on debugger entry\n");
   else __cvsim_msg("interactive scope only changed by $scope\n");
   break;
  case INFO_BRKPT:
   prt_brkpts();
   break;
  case INFO_PRTBASE:
   __cvsim_msg("default numeric base for :print command is %s\n",
    to_basename(s1, __dbg_dflt_base));
   break;
  case INFO_LOGECHO:
   if (__echo_iactcmds_tolog)
    __cvsim_msg("interactive input commands echoed to log file\n");
   else __cvsim_msg("interactive input command echo to log file off\n");
   break;
  case INFO_DISPLAY:
   dbg_info_disp();
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 __chk_extra_atend(TRUE);
}

/*
 * routine to print the current breakpoints
 */
static void prt_brkpts(void)
{
 struct brkpt_t *bpp;
 char s1[RECLEN], s2[RECLEN];
 struct itree_t *itp;

 if (__bphdr == NULL)
  {
   __cvsim_msg("No Breakpoints.\n");
   return;
  }

 __cvsim_msg("Breakpoints:\n");
 __cvsim_msg("Number  Disp Filter  Source-Instance Location\n");
 for (bpp = __bphdr; bpp != NULL; bpp = bpp->bpnxt) 
  {
   if (bpp->bp_enable)
    { if (bpp->bp_rm_when_hit) strcpy(s1, "del "); else strcpy(s1, "keep"); }
   else strcpy(s1, "dis ");
   __cvsim_msg("%-6d  %-4s  %-5s", bpp->bp_num, s1,
    to_brkptnam(s2, bpp->bp_type));
   __cvsim_msg("  %-s:%d", __schop(s1,
     __in_fils[bpp->bp_stp->stfnam_ind]), (int32) bpp->bp_stp->stlin_cnt);
   /* form is :[file]:[line]([inst or type]) */
   if (bpp->bp_idp == NULL) __arg_terr(__FILE__, __LINE__); 
   
   if (bpp->bp_type == BP_INST)
    __cvsim_msg("(%s)\n", __msg_idp_blditree(s1, bpp->bp_idp, bpp->bp_tskp));
   else
    {
     itp = (struct itree_t *) bpp->bp_idp[MD_ITP];
     if (bpp->bp_tskp == NULL)
      __cvsim_msg("(in %s)\n", itp->itip->imsym->synam);  
     else __cvsim_msg("(in %s %s: %s)\n",
      itp->itip->imsym->synam, __to_tsktyp(s1, bpp->bp_tskp->tsktyp),
      bpp->bp_tskp->tsksyp->synam);  
    }
   if (bpp->bp_condx != NULL) __cvsim_msg("        stop if: %s\n",
     __msgexpr_tostr(__xs, bpp->bp_condx));
  
   if (bpp->bp_hit_cnt > 0)
    __cvsim_msg("        breakpoint now hit %d times\n", bpp->bp_hit_cnt);
   if (bpp->bp_ignore_cnt - bpp->bp_hit_cnt > 0)
    __cvsim_msg("        ignore next %d hits\n",
     bpp->bp_ignore_cnt - bpp->bp_hit_cnt);
  }
}

/*
 * convert breakpoint type value to its name
 */
static char *to_brkptnam(char *s, word32 bptyp)
{
 switch ((byte) bptyp) {
  case BP_INST: strcpy(s, "Inst"); break; 
  case BP_TYPE: strcpy(s, "Type"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}
/*
 * convert base code to letter
 */
static char *to_basename(char *s, int32 base)
{
 switch ((byte) base) {
  case BBIN: strcpy(s, "binary"); break;
  case BHEX: strcpy(s, "hex"); break;
  case BOCT: strcpy(s, "octal"); break;
  case BDEC: strcpy(s, "decimal"); break;
  default: strcpy(s, "?"); __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * print info lines for all breakpoints 
 */
static void dbg_info_disp(void)
{
 struct dispx_t *dxp;
 char s1[RECLEN];

 if (__dispxhdr == NULL)
  {
   __cvsim_msg("No auto-display expressions.\n");
   return;
  }
 __cvsim_msg("Number  Enable Expression-(instance)\n");
 for (dxp = __dispxhdr; dxp != NULL; dxp = dxp->dsp_nxt) 
  {
   if (dxp->dsp_enable) strcpy(s1, "y"); else strcpy(s1, "n");
   __cvsim_msg("%-7d   %s     %s (%s)\n", dxp->dsp_num, s1,
    __msgexpr_tostr(__xs, dxp->dsp_xp), __msg_idp_blditree(__xs2, dxp->dsp_idp,
    dxp->dsp_tskp));
  }
}

/*
 * ROUTINES TO PARSE A SCOPE REFERNENCE
 */

/*
 * : debugger :scope command normal scope except allow [file]:[line] form
 * where first instance is implied - other wide argument is normal scope
 * :sc [file]:[line], .u (..) .d , normal xmr
 * returns T if parsed all of args even if error 
 *
 * notice scheme is to maybe use line to determine scope but then always
 * set at first line of scope not entered line?
 * ihea is that probably want to start by listing header and initial always
 * are ||
 */
extern void __do_dbg_scope(void)
{
 int32 ifi, lini, iref;
 t_midat *in_idp; 
 struct task_t *in_tskp;

 /* if cannot parse scope location, error emitted in routine */
 if (!parse_scope_ref(&in_idp, &in_tskp, &ifi, &lini, &iref)) return;
 /* do the scope change - implies current line change */
 /* notice even if ifi and line set, not used */
 __scope_idp = in_idp;
 __scope_tskp = in_tskp;
 /* replace top of inst. stack */
 set_idp_(__scope_idp);
 __set_scopchg_listline();

 if (__tfrec_hdr != NULL) __call_misctfs_scope();
 if (__have_vpi_actions) __vpi_iactscopechg_trycall();

 __chk_extra_atend(TRUE);
}

/*
 * routine to get scope line location for breakpoints and printing 
 * return F on error
 * this may set values but invalid unless returns T 
 * if T know all 5 return by ref. values set 
 * for breakpoints - determines if one instance ref only (iref T)
 * because of file form this does not use get_vtok but access vichp 
 * for scope but not line ref. sets ref_ifi and ref_lini to -1
 *
 * forms: .. .u .d scope change => scope,task,file,1st line
 *        [file]:[line] or [line] (current file) - scope,task,[file],[line] 
 *        [module name] => scope 1st inst,no task, file,first line 
 *        xmr => scope,task,file,1st line
 *
 * notice no spaces allowed in reference
 */
static int32 parse_scope_ref(t_midat **ref_idp, struct task_t **ref_tskp,
 int32 *ref_ifi, int32 *ref_lini, int32 *iref)
{
 int32 ifi, lini, maxlini;
 t_midat *in_idp;
 struct task_t *tskp;
 char *chp;
 char *savchp, *endchp, sref[RECLEN];

 /* assume instance ref. */
 *iref = TRUE;
 /* here savchp is 1st char of token - endchp first after */
 /* return F on error, if is not [file]:[line] ref - ifi is -1 */
 if (!try_get_fillin_ref(__visp->vichp, &ifi, &lini, &savchp, &endchp))
  return(FALSE);

 if (ifi != -1)
  {
set_line_scope:
   if ((maxlini = get_lastfillin(ifi)) == -1) return(FALSE); 
   if (lini > maxlini)
    {
     __ia_err(1469,
      "[file]:[line] reference line number %d too large - %s has %d lines",
      lini, __in_fils[ifi], maxlini);
     return(FALSE);
    }

   if (!fil_lin_toscope(ifi, lini, ref_idp, ref_tskp))
    {
     __ia_err(1454,
      "scope reference %s:%d illegal - line not inside any module",
      __in_fils[ifi], lini);
     return(FALSE);
    } 
   *ref_ifi = ifi;
   *ref_lini = lini;
   /* if has line number, not an instance ref. */ 
   *iref = FALSE;
   /* current get tok place is just after [file]:[line] ref. */
   __visp->vichp = endchp;
   return(TRUE);
  }

 /* know not [file]:[line] ref - try scope or special abbrev. */
 /* build the token */
 strncpy(sref, savchp, endchp - savchp); 
 sref[endchp - savchp] = '\0';  
 /* assume will match local scope ref. or [number] implied file form */
 __visp->vichp = endchp;
 /* maybe special local .. form */
 if (sref[0] == '.')
  {
   *ref_ifi = -1;
   *ref_lini = -1;
   return(local_scope_ref(sref, &in_idp, ref_tskp));
  }

 /* does not have : not [file]:[line] but maybe [line] */
 if (isdigit(sref[0]))
  {
   for (chp = sref; *chp != '\0'; chp++)
    {
     if (!isdigit(*chp))
      {
bad_lin:
       __ia_err(1452, "scope reference [line] form %s illegal format", sref);
       return(FALSE);
      }
    } 
   if (sscanf(sref, "%d", &lini) != 1) goto bad_lin; 
   ifi = __list_cur_ifi;
   goto set_line_scope;
  }

 /* must be identifier - need get vtok to check and parse GLBREF */
 /* put back and parse */
 __visp->vichp = savchp;
 
 /* know file form elminated before here */
 __get_vtok(); 
 if (__toktyp != ID)
  {
   __ia_err(1467, "scope reference %s illegal", __prt_vtok());
   return(FALSE);
  }
 if (!get_var_scope(&in_idp, &tskp, iref)) return(FALSE);
 *ref_idp = in_idp;  
 *ref_tskp = tskp;
 *ref_ifi = -1;
 *ref_lini = -1;
 return(TRUE);
}

/*
 * attempt to read a file and line reference form
 * return F on error
 * set ifi to -1 if turns out not to be [file]:[line] form
 * lini and endchp only good if ifi not -1
 */
static int32 try_get_fillin_ref(char *st_chp, int32 *ifi, int32 *lini,
 char **sav_chp, char **endchp)
{
 int32 rlen, arglen, rv;
 char *chp;
 char *chp1, *sref, *argref;
 char s1[RECLEN];

 /* skip any leading white space */
 argref = NULL;
 arglen = 0;
 rv = TRUE;
 *ifi = *lini = -1;
 for (chp = st_chp;; chp++) { if (!vis_white_(*chp)) break; }
 *sav_chp = chp;

 /* separate scope reference into separate string in case file:line form */
 /* tricky because anything except \0 can go in file name */
 chp1 = chp;
 for (;; chp++)
  {
   /* any escaped cannot end */
   if (*chp == '\\') { chp++; continue; }
   if (vis_white_(*chp) || *chp == '\0') break; 
  }
 rlen = chp - chp1;
 sref = __my_malloc(rlen + 1);
 strncpy(sref, chp1, rlen);
 sref[rlen] = '\0'; 

 /* set vichp to continuation place in case more arguments */
 *endchp = chp;
 /* have scope ref. in sref - rule if has unescaped : line, else scope */ 
 /* escaped ID always scope ref */
 if (sref[0] == '\\') goto done;
 /* if no : cannot be [file]:[line] form - [line] form handled elsewhere */
 if ((chp = strrchr(sref, ':')) == NULL) goto done;
 chp--;
 /* if last : escaped no possible number following */
 if (*chp == '\\')  goto done;
 chp++;
 arglen = chp - sref + 1;
 argref = __my_malloc(arglen);
 strncpy(argref, sref, chp - sref);
 argref[chp - sref] = '\0';
 /* must be all digits after : */
 chp++;
 for (chp1 = chp; *chp1 != '\0'; chp1++)
  {
   if (!isdigit(*chp1))
    {
bad_fil_lin:
     __ia_err(1468, "[file]:[line] form %s illegal format", sref);
     rv = FALSE;
     goto done;
    }
  }
 strcpy(s1, chp);
 if (sscanf(s1, "%d", lini) != 1 || *lini < 1) goto bad_fil_lin; 
 if ((*ifi = find_infil_ind(argref)) == -1)
  {
   __ia_err(1453,
    "scope reference file, path or path tail \"%s\" unrecognized", argref);
   rv = FALSE;
  }
done:
 __my_free(sref, rlen + 1);
 if (argref != NULL) __my_free(argref, arglen);
 return(rv);
}

/*
 * get a ID or GLBREF expr. (know read token ID) scope location
 * 
 * this reads to EOL - no other way to know end because of inst. array sel.
 *
 *
 * need to run with current module for counting any allocated globals
 * may alloc some globals in grwrk tab - need to free fields and empty tab
 */
static int32 get_var_scope(t_midat **in_idp, struct task_t **tskpp,
 int32 *iref)
{
 int32 gri, rv, sav_ecnt;
 struct sy_t *syp;
 struct gref_t *grp;
 struct expr_t *glbndp;
 struct expridtab_t *xidp;
 struct mod_t wrkmod;
 struct sy_t wrksym;
 char s1[RECLEN];
 struct mod_t *mdp;
 t_midat *xmr_idp;

 rv = TRUE;
 syp = NULL;
 /* collect to end of line (TEOF) */
 if (!__colto_eol())
  {
   __ia_err(1434, "scope reference bad format - extra tokens at end(?)");
   return(FALSE); 
  }

 /* allow [module name] form if not instance name - not legal source xmr */
 /* must handle this before parsing since it is an error */
 if (__last_xtk == 0 && __exprtab[0]->optyp == ID)
  {
   xidp = __expr_idtab[0];

   /* know this has one component */
   /* case 1: not defined in cur. module or not scope in cur. mod */
   mdp = (struct mod_t *) __scope_idp[MD_MDP];
   if ((syp = __get_sym(xidp->idnam, mdp->msymtab)) == NULL
    || !__is_scope_sym(syp))
    {
     /* can scope to any module (implied first instance) */
     /* udp's are in mod syms */
     if ((syp = __get_sym(xidp->idnam, __modsyms)) != NULL
      && syp->sytyp == SYM_M)
      {
       *tskpp = NULL;  
       *in_idp = syp->el.emdp->moditps[0]->it_idp;
       /* if top then this is iref need for ibreak where required */
       if (syp->el.emdp->minstnum == 0) *iref = TRUE; else *iref = FALSE;
       return(TRUE);
      }
     /* must be some kind of one component global or maybe error */
    }
  }

 wrksym.synam = s1;
 wrksym.sydecl = TRUE;
 strcpy(wrksym.synam, "** DBG SCOPE WRK**"); 
 __init_mod(&wrkmod, &wrksym);
 wrkmod.flatinum = 1;
 wrksym.el.emdp = &wrkmod;
 __push_wrkitstk(&wrkmod, 0);

 /* try global - can be one component downward relative xmr */
 /* if fails will be set to x number */
 sav_ecnt = __pv_err_cnt;
 __allow_scope_var = TRUE;
 __bld_xtree(0);
 __allow_scope_var = FALSE;
 glbndp = __root_ndp;
 if (__pv_err_cnt > sav_ecnt) { rv = FALSE; goto done; }

 /* if local task/func/named block reference - just change task */
 /* if local reference may have been converted back to ID */
 if (glbndp->optyp == ID)
  {
   if (!__is_scope_sym(glbndp->lu.sy))
    {
     __ia_err(1440, "scope reference to non scope symbol %s type %s",
      glbndp->lu.sy->synam,  __to_sytyp(__xs, glbndp->lu.sy->sytyp));
     rv = FALSE;
     goto done;
    }

   /* know scope ptr always on top of inst. stack here */
   *in_idp = __scope_idp; 
   *tskpp = glbndp->lu.sy->el.etskp;
   rv = TRUE;
   goto done;
  }

 if (glbndp->optyp != GLBREF) 
  {
   __ia_err(1411, "scope reference illegal hierarchical reference");
   return(FALSE);
  }
 grp = glbndp->ru.grp;
 if (grp->gr_err) { rv = FALSE; goto done; }

 /* convert from gref reference to itree target location */
 xmr_idp = __xmrget_refgrp_to_targ(grp);
 *in_idp = xmr_idp;

 if (glbndp->lu.sy->sytyp != SYM_I && glbndp->lu.sy->sytyp != SYM_M)
  *tskpp = glbndp->lu.sy->el.etskp;
 else *tskpp = NULL;

done:
 if (__grwrknum > 0)
  {
   grp = &(__grwrktab[0]);
   for (gri = 0; gri < __grwrknum; grp++, gri++) __free_1glb_flds(grp);
   __grwrknum = 0;
  }
 __free_xtree(glbndp);
 __pop_wrkitstk();
 return(rv);
}

/*
 * get a local form scope reference
 * know 1st token read
 */
static int32 local_scope_ref(char *refnam, t_midat **ref_idp,
 struct task_t **ref_tskp)
{
 struct itree_t *itp;
 struct task_t *tskp;
 struct symtab_t *sytp;
 struct itree_t *scope_itp;

 scope_itp = (struct itree_t *) __scope_idp[MD_ITP];
 if (refnam[1] == '.')
  {
   if (refnam[2] != '\0') goto bad_locchg;

do_up:
   /* if in task, up is to next task up or enclosing named block */
   tskp = __scope_tskp;
   itp = scope_itp;
   if ((tskp = __scope_tskp) != NULL)
    {
     /* see what parent symbol table symbol of is */
     sytp = tskp->tsksymtab->sytpar;
     if (sytp == NULL) __misc_terr(__FILE__, __LINE__);
     /* if task top in module up is module scope */
     if (sytp->sypofsyt->sytyp == SYM_M) tskp = NULL;
     else tskp = sytp->sypofsyt->el.etskp;
    } 
   else
    {
     if (scope_itp->up_it == NULL)
      {
       __ia_err(1455,
        "scope reference .. (up) change impossible - already at top level");
       return(FALSE);
      }
     itp = scope_itp->up_it;
     tskp = NULL;
    }
   goto do_change;
  }
 /* :scope .[dir. letter] */
 if ((refnam[1] != 'u' && refnam[1] != 'd') || refnam[2] != '\0')
  {
bad_locchg:
   __ia_err(1459,
    "illegal scope reference local change argument %s", refnam);
   return(FALSE);
  }
 if (refnam[1] == 'u') goto do_up; 
 /* down case - even if current task scope ignore */
 if (scope_itp->in_its == NULL)
  {
   __ia_err(1456,
    "scope reference local .d move down impossible - scope has no instances");
    return(FALSE);
  }
 itp = &(scope_itp->in_its[0]);
 tskp = NULL;

do_change:
 *ref_idp = itp->it_idp;
 *ref_tskp = tskp;
 return(TRUE);
}

/*
 * given a file name or path, convert to in_fils index number
 * return -1 if no match
 */
static int32 find_infil_ind(char *nam)
{
 int32 i;
 char *chp;
 
 /* file spec. if path - must match path exactly */
 if ((chp = strrchr(nam, '/')) != NULL)
  {
   /* 0 and 1 used for place holders */
   for (i = 2; i <= __last_srcf; i++) 
    { if (strcmp(nam, __in_fils[i]) == 0) return(i); }
   return(-1);
  }
 /* simple file, first try to match exactly */
 for (i = 2; i <= __last_srcf; i++)
  { if (strcmp(nam, __in_fils[i]) == 0) return(i); }
 /* then try tails of paths */
 for (i = 2; i <= __last_srcf; i++)
  {
   if ((chp = strrchr(__in_fils[i], '/')) == NULL) continue;
   if (strcmp(++chp, __in_fils[i]) == 0) return(i);
  }
 return(-1);
}

/*
 * find scope from line number
 * do not need file pos. table for this
 */
static int32 fil_lin_toscope(int32 ifi, int32 lini, t_midat **in_idp,
 struct task_t **in_tskp)
{
 struct mod_t *mdp; 
 struct task_t *tskp;
 struct mod_t *in_mdp;

 /* module in means from first to last */
 for (in_mdp = NULL, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (scope_lini_inrng(lini, ifi, mdp->msym->sylin_cnt,
    (int32) mdp->msym->syfnam_ind, mdp->mod_last_lini, mdp->mod_last_ifi))
    {
     in_mdp = mdp;
     break;
    }
  }
 if (in_mdp == NULL) return(FALSE);
 *in_idp = in_mdp->moditps[0]->it_idp;
 /* next see if within task or function but not named block */
 /* since named blocks nests must handle as normal statements */  
 *in_tskp = NULL;
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   /* notice must include named blocks as well as task/funcs in scope */
   if (scope_lini_inrng(lini, ifi, tskp->tsksyp->sylin_cnt,
    (int32) tskp->tsksyp->syfnam_ind, tskp->tsk_last_lini, tskp->tsk_last_ifi))
    { *in_tskp = tskp; break; }
  } 
 return(TRUE);
}

/*
 * determine if line inside module scope - scope can span multiple files 
 *
 * here line can be anywhere in module scope providing followed by procedural
 * statement
 */
static int32 scope_lini_inrng(int32 lini, int32 ifi, int32 st_lini, int32 st_ifi,
 int32 last_lini, int32 last_ifi)
{
 struct incloc_t *ilp;

 /* if ifi included (first) file ilp is non included location */
 /* that is right location for which to do in range check */
 if ((ilp = find2_incloc(ifi)) != NULL) 
  { ifi = ilp->incfrom_fnind; lini = ilp->incfrom_lcnt; }

 /* debugger current location in file outside scope files */
 if (ifi < st_ifi || ifi > last_ifi) return(FALSE);

 /* in first (usually only) file of scope */
 if (ifi == st_ifi)
  {
   if (lini < st_lini) return(FALSE);
   if (last_ifi > ifi) return(TRUE);
   return(lini <= last_lini);
  }
 /* in last file of scope where scope spans files */
 if (ifi == last_ifi) return(lini <= last_lini);
 /* if in not first or last spanned file, then know in range */
 return(TRUE);
}

/*
 * find incloc that is non included file
 * for multiply included this returns location of outermost
 */
static struct incloc_t *find2_incloc(int32 ifi)
{
 struct incloc_t *ilp, *ilp2; 

 if ((ilp2 = find_incloc(ifi)) == NULL) return(NULL);
 /* know included trace outward until finding one not included and */
 /* return that ilp */
 for (;;)
  {
   ifi = ilp2->incfrom_fnind;
   ilp = ilp2;
   if ((ilp2 = find_incloc(ifi)) == NULL) break;
  }
 return(ilp);
}

/*
 * set list line to suspended thread next statement first line if possible
 * else to first line of scope
 */
extern void __set_dbentry_listline(void)
{
 int32 lini, ifi;
 struct st_t *stp;

 if (__suspended_thd == NULL || __suspended_thd->thnxtstp == NULL)
  {
   __set_scopchg_listline();
   goto done;
  }

 stp = __suspended_thd->thnxtstp;
 ifi = (int32) stp->stfnam_ind;
 /* never change dbg list line to interactive history */
 if (ifi == __cmd_ifi) goto done;
 lini = stp->stlin_cnt;
 __list_arg_lini = __list_cur_lini = lini;
 if (__list_cur_ifi != ifi)
  {
   /* this emits error on file problem */
   if (!change_srcfile(ifi)) return;
  }
 done:;
  /* DBG REMOVED ---
  if (__debug_flg)
   {
   __dbg_msg("=== IACT entry at %s scope %s\n",
    __bld_lineloc(__xs, (word32) __list_cur_ifi, __list_cur_lini), 
    __msg_idp_blditree(__xs2, __scope_idp, __scope_tskp));
   }
 --- */
}

/*
 * set a scope change list line - for interactive only
 */
extern void __set_scopchg_listline(void)
{
 int32 lini, ifi;
 struct sy_t *syp;
 struct itree_t *itp;

 /* no suspended thread use first line of scope */
 if (__scope_tskp != NULL) syp = __scope_tskp->tsksyp;
 else 
  {
   itp = (struct itree_t *) __scope_idp[MD_ITP];
   syp = itp->itip->imsym;
  }
 ifi = (int32) syp->syfnam_ind;
 /* start with list arg same as scope */
 lini = syp->sylin_cnt;
 __list_arg_lini = __list_cur_lini = lini;
 /* this emits error on file problem */
 if (__list_cur_ifi != ifi) change_srcfile(ifi);
}

/*
 * print history list - :history [number] command
 */
extern void __do_dbg_history(void)
{
 int32 hnum;

 __get_vtok(); 
 if (__toktyp == TEOF) { __exec_history_list(__hist_cur_listnum); return; }
 /* notice since history starts at 1, last is same as size */
 if ((hnum = __get_dbg_val()) == -1 || hnum < 0)
  { __ia_err(1477, ":history %s argument illegal", __prt_vtok()); return; } 
 __exec_history_list(hnum);
 __chk_extra_atend(TRUE);
}

/*
 * empty the history list if possible
 */
extern void __do_dbg_emptyhistory(void)
{
 int32 iahi;
 struct iahist_t *iahp;
 int32 llen;

 /* first check to make sure nothing pending */ 
 for (iahi = 1; iahi <= __iah_lasti; iahi++) 
  {
   iahp = &(__iahtab[iahi]);
   /* notice when non immediate statement finishes, disable turned on */ 
   if (iahp->iah_hcp != NULL)
    {
     __ia_err(1483,
      ":emptyhistory impossible because command %d not completed or disabled",
      iahi); 
     return;
    }
  }
 for (iahi = 1; iahi <= __iah_lasti; iahi++) 
  {
   iahp = &(__iahtab[iahi]);
   if (iahp->iah_hcp != NULL || iahp->iah_lp == NULL)
    __misc_terr(__FILE__, __LINE__);
   llen = strlen(iahp->iah_lp);
   __my_free(iahp->iah_lp, llen + 1);
   __iahtab[iahi].iah_hcp = NULL;
   __iahtab[iahi].iah_lp = NULL;
  } 
 __iah_lasti = 0;
 __chk_extra_atend(TRUE);
}

/*
 * ROUTINES TO IMPLEMENT BREAK POINTS
 */

/*
 * : debugger command to stop over current statement
 * abbreviation for :tibreak [next line] if exists, '.'
 */
extern int32 __do_dbg_nextb(void)
{
 struct thread_t *thp;
 struct st_t *stp;
 struct brkpt_t *bpp;
 struct task_t *tskp;

 /* need to have started execution to use :nextb */
 if ((thp = __suspended_thd) == NULL)
  {  
   __ia_err(1494,
    ":nextb impossible exection not started - start with ',' or :step");
   return(TRUE);
  }  
 if ((stp = thp->thnxtstp) == NULL || stp->stnxt == NULL)
  {
   __ia_err(1494,
    ":nextb impossible no next statement - set manual :tbreak");
   return(TRUE);
  }
 if (stp->stnxt->rl_stmttyp == S_REPEAT) stp = stp->stnxt;
 /* DBG remove --- */
 if (stp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */  

 bpp = (struct brkpt_t *) __my_malloc(sizeof(struct brkpt_t));
 init_brkpt(bpp);
 bpp->bp_type = BP_INST;
 bpp->bp_num = __nxt_bpnum++;
 bpp->bp_stp = stp->stnxt;
 bpp->bp_idp = thp->th_idp;

 if (__fcspi >= 0) tskp = __fcstk[__fcspi];
 else if (thp->th_fj) tskp = __find_thrdtsk(thp);
 else tskp = thp->assoc_tsk;
 bpp->bp_tskp = tskp;
 bpp->bp_rm_when_hit = TRUE;
 insert_brkpt(bpp);
 return(FALSE);
}

/*
 * : debugger command to set a breakpoint that applies to all insts of type
 */
extern void __do_dbg_brkpt(int32 is_tmp)
{
 int32 ifi, lini, iref;
 struct brkpt_t *bpp;
 t_midat *in_idp; 
 struct task_t *in_tskp;
 struct mod_t *mdp;
 struct st_t *stp, *stp2;
 char *sav_chp;
 char s1[RECLEN], s2[RECLEN];
 struct itree_t *itp;
 
 if (is_tmp) strcpy(s1, ":tbreakpoint"); else strcpy(s1, ":breakpoint");
 sav_chp = __visp->vichp;
 __get_vtok(); 
 if (__toktyp == TEOF)
  {
   /* here always use last printed file line type location - know exists */
   ifi = __list_cur_ifi;
   if (__list_arg_lini < 1)
    {
     __ia_err(1485, "%s no argument form failed - no last list line", s1);
     return;
    }
   lini = __list_arg_lini;
   if (!fil_lin_toscope(ifi, lini, &in_idp, &in_tskp))
    {
     __ia_err(1472,
      "%s not set at list location %s:%d - outside procedural region of scope",
      s1, __in_fils[ifi], lini);
     return;
    } 
   iref = FALSE;
   __visp->vichp = sav_chp; 
  }
 else 
  {
   __visp->vichp = sav_chp; 
   if (!parse_scope_ref(&in_idp, &in_tskp, &ifi, &lini, &iref)) return;

   /* must have line number which is first procedural statement of scope */
   if (ifi == -1) set_scope_loc(in_idp, in_tskp, &ifi, &lini);
  }

 /* convert to statement, if scope form, line and file will be set to 1st */
 /* first build the new breakpoint */
 mdp = (struct mod_t *) in_idp[MD_MDP];
 if ((stp = conv_line_tostmt(mdp, in_tskp, ifi, lini)) == NULL)
  {
   __ia_err(1473, 
    "%s reference location %s:%d outside task or initial/always block", s1,
    __in_fils[ifi], lini); 
   return;
  }

 /* can't set stmt breakpoint on delay control must go on action stmt */
 if (stp->stmttyp == S_DELCTRL) 
  {
   stp2 = stp->st.sdc->actionst;
   if (stp2 == NULL) 
    {
     __ia_err(1488,
      "statement %s only on delay control with action statement", s1);
     return;
    }
   stp = stp2;
  }

 bpp = (struct brkpt_t *) __my_malloc(sizeof(struct brkpt_t));
 init_brkpt(bpp);
 bpp->bp_type = BP_TYPE;
 bpp->bp_num = __nxt_bpnum++;
 bpp->bp_stp = stp;
 bpp->bp_idp = in_idp;
 bpp->bp_tskp = in_tskp;
 if (is_tmp) bpp->bp_rm_when_hit = TRUE;
 insert_brkpt(bpp);
 
 if (bpp->bp_tskp == NULL) strcpy(s1, "");
 else sprintf(s1, " %s: %s", __to_tsktyp(__xs, bpp->bp_tskp->tsktyp),
  bpp->bp_tskp->tsksyp->synam); 
 if (is_tmp) strcpy(s2, " (temp)"); else strcpy(s2, "");

 itp = (struct itree_t *) bpp->bp_idp[MD_ITP];
 __cvsim_msg("Breakpoint%s %d set at %s in %s%s\n", s2,
  bpp->bp_num, __bld_lineloc(__xs, bpp->bp_stp->stfnam_ind,
  bpp->bp_stp->stlin_cnt), itp->itip->imsym->synam, s1);
 __chk_extra_atend(TRUE);
}

/*
 * set a scope starting line number - for non line number forms
 * takes itp and tskp inputs, and sets addrs ref_ifi and ref_lini
 */
static void set_scope_loc(t_midat *in_idp, struct task_t *tskp, 
 int32 *ref_ifi, int32 *ref_lini)
{
 struct mod_t *mdp;
 struct itree_t *itp;

 if (tskp != NULL)
  {
   *ref_ifi = (int32) tskp->tskst->stfnam_ind;
   *ref_lini = tskp->tskst->stlin_cnt;
   return;
  }
 itp = (struct itree_t *) in_idp[MD_ITP];
 mdp = itp->itip->imsym->el.emdp; 
 if (mdp->ialst == NULL)
  {
   __ia_err(1484,
    "scope %s module %s no initial always blocks - no procedural location",
    __msg2_blditree(__xs, itp), mdp->msym->synam);
   /* must use first line of scope - probably later another error */
   *ref_ifi = (int32) itp->itip->imsym->syfnam_ind; 
   *ref_lini = itp->itip->imsym->sylin_cnt; 
   return;
  }
 *ref_lini = mdp->ialst->ia_first_lini;
 *ref_ifi = mdp->ialst->ia_first_ifi;
}

/*
 * : debugger command to set a breakpoint that applies to all insts of type
 */
extern void __do_dbg_ibrkpt(int32 is_tmp)
{
 int32 ifi, lini, iref;
 struct brkpt_t *bpp;
 struct itree_t *itp; 
 t_midat *in_idp;
 struct task_t *in_tskp;
 struct mod_t *mdp, *in_mdp;
 struct st_t *stp, *stp2;
 struct sy_t *syp;
 char *savchp;
 char s1[RECLEN];

 if (is_tmp) strcpy(s1, ":tibreakpoint"); else strcpy(s1, ":ibreakpoint");
 savchp = __visp->vichp;
 __get_vtok(); 
 /* case 1: no argument use current list and scope locations */
 if (__toktyp == TEOF)
  {
   /* here if not in scope instance use first instance of scope */
   ifi = __list_cur_ifi;
   if (__list_arg_lini < 1)
    {
     __ia_err(1485,
      "%s no argument form failed - no last list line", s1);
     return;
    }
   lini = __list_arg_lini;
   if (!fil_lin_toscope(ifi, lini, &in_idp, &in_tskp))
    {
     __ia_err(1474,
      "%s set at scope first line - list location %s:%d not in scope", s1,
      __in_fils[ifi], lini);
     in_idp = NULL;
    } 
   if (in_idp != NULL)
    {
     mdp = (struct mod_t *) __scope_idp[MD_MDP];
     in_mdp = (struct mod_t *) in_idp[MD_MDP];
     if (in_mdp != mdp) 
      {
       __ia_err(1476,
        "%s set at scope first line - list location %s:%d outside current scope",
         s1, __in_fils[ifi], lini);
       in_idp = NULL;
      }
    }
   __visp->vichp = savchp; 
   /* problem with line - use first line of scope */
   if (in_idp == NULL)
    {
     itp = (struct itree_t *) __scope_idp[MD_ITP];
     if (__scope_tskp != NULL) syp = __scope_tskp->tsksyp;
     else 
      {
       syp = itp->itip->imsym;
      }
     ifi = (int32) syp->syfnam_ind;
     lini = syp->sylin_cnt; 
     in_idp = __scope_idp;
     in_tskp = __scope_tskp;
    }
   __visp->vichp = savchp; 
  }
 else
  {
   /* case 3: scope ref, maybe ,[line ref.] */
   __visp->vichp = savchp; 
   __get_vtok();
   /* :ib ,[line ref] form legal */
   if (__toktyp == COMMA)
    {
     /* notice either need to use scope ptr here or scope from inst */
     in_idp = __scope_idp; 
     in_tskp = __scope_tskp;
     goto got_comma;  
    }

   __visp->vichp = savchp;
   if (!parse_scope_ref(&in_idp, &in_tskp, &ifi, &lini, &iref)) return;
   if (!iref)
    {
     __ia_err(1478,
      "%s cannot be set - instance reference required", s1);
     return;
    }
   __get_vtok(); 
got_comma:
   /* see if optional ,[file]:[line] form present - use for line */ 
   if (__toktyp == COMMA)
    { if (!get_ibrk_linref(in_idp, in_tskp, &ifi, &lini)) return; }
   /* else use first procedural statement line of scope not arg lini */
   else set_scope_loc(in_idp, in_tskp, &ifi, &lini);
  }
 /* convert to statement, if scope form, line and file will be set to 1st */
 /* first build the new breakpoint */
 mdp = (struct mod_t *) in_idp[MD_MDP];
 if ((stp = conv_line_tostmt(mdp, in_tskp, ifi, lini)) == NULL)
  {
   __ia_err(1475, 
    "%s reference location %s:%d outside task or initial/always block", s1,
    __in_fils[ifi], lini); 
   return;
  }
 /* can't set stmt breakpoint on delay control must go on action stmt */
 if (stp->stmttyp == S_DELCTRL) 
  {
   stp2 = stp->st.sdc->actionst;
   if (stp2 == NULL) 
    {
     __ia_err(1488,
      "statement %s only on delay control with action statement", s1);
     return;
    }
   stp = stp2;
  }
 
 bpp = (struct brkpt_t *) __my_malloc(sizeof(struct brkpt_t));
 init_brkpt(bpp);
 bpp->bp_type = BP_INST;
 bpp->bp_num = __nxt_bpnum++;
 bpp->bp_stp = stp;
 bpp->bp_idp = in_idp;
 bpp->bp_tskp = in_tskp;
 if (is_tmp) bpp->bp_rm_when_hit = TRUE;
 insert_brkpt(bpp);

 if (is_tmp) strcpy(s1, " (temp)"); else strcpy(s1, "");
 __cvsim_msg("Breakpoint%s (inst) %d set at %s in %s\n", s1,
  bpp->bp_num, __bld_lineloc(__xs, bpp->bp_stp->stfnam_ind,
  bpp->bp_stp->stlin_cnt), __msg_idp_blditree(__xs, bpp->bp_idp, bpp->bp_tskp));
 __chk_extra_atend(TRUE);
}

/*
 * get the [line ref. after , in ibreakpoint
 * know , read and reads end of [line] or [file]:[line] reference
 * return F on error
 */
static int32 get_ibrk_linref(t_midat *in_idp, struct task_t *tskp,
 int32 *ifi, int32 *lini) 
{
 char *chp;
 struct sy_t *syp;
 struct mod_t *mdp;
 char *savchp, *endchp;
 char sref[RECLEN];
 struct itree_t *itp;

 /* return F on error, if not [file]:[line], ifi set to -1 */
 if (!try_get_fillin_ref(__visp->vichp, ifi, lini, &savchp, &endchp))
  return(FALSE);

 if (*ifi != -1) __visp->vichp = endchp;
 else
  { 
   /* know not [file]:[line] ref - must be line by itself */
   strncpy(sref, savchp, endchp - savchp); 
   sref[endchp - savchp] = '\0';  
   __visp->vichp = endchp;
   /* does not have : not [file]:[line] but maybe [line] */
   if (!isdigit(sref[0]))
    {
bad_lin_num:
     __ia_err(1481, ":ibreakpoint ,[number] expected - %s read", sref);
     return(FALSE);
    }
   for (chp = sref; *chp != '\0'; chp++)
    { if (!isdigit(*chp)) goto bad_lin_num; } 
   if (sscanf(sref, "%d", lini) != 1) goto bad_lin_num; 
   if (tskp != NULL) syp = tskp->tsksyp; 
   else 
    {
     itp = (struct itree_t *) in_idp[MD_ITP];
     syp = itp->itip->imsym;
    }
    /* have [line] form - file is first in scope */
   *ifi = (int32) syp->syfnam_ind;
  }
 /* make sure in range */
 if (tskp != NULL)
  {
   if (!scope_lini_inrng(*lini, *ifi, tskp->tsksyp->sylin_cnt,
    (int32) tskp->tsksyp->syfnam_ind, tskp->tsk_last_lini, tskp->tsk_last_ifi))
    {
out_of_rng:
     __ia_err(1482, ":ibreakpoint %s:%d not before statement in scope %s",
      __in_fils[*ifi], *lini, __msg_idp_blditree(__xs, in_idp, tskp));
     return(FALSE);
    }
   return(TRUE);
  }
 /* must be in scope with initial/always and before last */
 mdp = (struct mod_t *) in_idp[MD_MDP];
 if (!scope_lini_inrng(*lini, *ifi, mdp->msym->sylin_cnt,
  (int32) mdp->msym->syfnam_ind, mdp->mod_last_lini, mdp->mod_last_ifi))
  goto out_of_rng;
 if (mdp->ialst == NULL) goto out_of_rng;
 /* if after last - error later */
 return(TRUE);   
}

/*
 * initialize a breakpoint 
 */
static void init_brkpt(struct brkpt_t *bpp)
{
 bpp->bp_type = BP_UNKN;
 bpp->bp_can_halt = TRUE;
 bpp->bp_enable = TRUE;
 /* unused for now */
 bpp->bp_prttyp = 0;
 bpp->bp_dup = FALSE;
 bpp->bp_rm_when_hit = FALSE;
 bpp->bp_num = -1;
 bpp->bp_ignore_cnt = 0;
 bpp->bp_hit_cnt = 0;
 bpp->bp_stp = NULL;
 bpp->bp_idp = NULL;
 bpp->bp_tskp = NULL;
 bpp->bp_condx = NULL;
 bpp->bpnxt = NULL;
} 

/*
 * insert the breakpoint with duplicate same loc. flag setting 
 * this traverses to end of list - know new number is one higher than last
 */
static void insert_brkpt(struct brkpt_t *bpp)
{
 struct brkpt_t *bpp2;
 struct brkpt_t *bpp_last;
 int32 seen_same_line;

 seen_same_line = FALSE;
 for (bpp_last = NULL, bpp2 = __bphdr; bpp2 != NULL; bpp2 = bpp2->bpnxt) 
  {
   /* set dup if same line number seen */
   if (bpp->bp_stp->stfnam_ind == bpp2->bp_stp->stfnam_ind
    && bpp->bp_stp->stlin_cnt == bpp2->bp_stp->stlin_cnt)
    {
     if (!seen_same_line)
      {
       __cvsim_msg("Note: other statement breakpoint(s) set at %s\n",
        __bld_lineloc(__xs, bpp->bp_stp->stfnam_ind, bpp->bp_stp->stlin_cnt));
       seen_same_line = TRUE;
      }
     bpp2->bp_dup = bpp->bp_dup = TRUE;
    }
   bpp_last = bpp2;
  }
 /* insert on end - bpp last is recomputed tmp */ 
 if (__bphdr == NULL) __bphdr = bpp;
 else
  {
   /* SJM 08/02/01 - add if to keep lint happy */
   if (bpp_last != NULL) bpp_last->bpnxt = bpp;
  }
 /* finally arm breakpoint */
 if (!bpp->bp_dup) 
  {
   /* DBG - remove */
   if (bpp->bp_stp->stmttyp == S_BRKPT) __misc_terr(__FILE__, __LINE__);
   bpp->bp_stp->stmttyp = S_BRKPT;
  }
}

/*
 * routine to find statement given ifi and lini 
 * returns NULL on error
 * if not [file]:[line] - know will match first line if any exists
 * finds first statement after line - error if not found in scope
 * tricky because scope can extend across multiple files
 */
static struct st_t *conv_line_tostmt(struct mod_t *in_mdp,
 struct task_t *in_tskp, int32 ifi, int32 lini)
{
 struct ialst_t *ialp; 
 struct st_t *stp, *stp2;
 struct incloc_t *ilp;
 int32 st_ifi, st_lini, ifi2, lini2;

 /* if in included file, must use line included form in range tests */ 
 if ((ilp = find2_incloc(ifi)) != NULL) 
  { ifi2 = ilp->incfrom_fnind; lini2 = ilp->incfrom_lcnt; }
 else { ifi2 = ifi; lini2 = lini; } 

 /* if task, know will have statements and use last if after */
 if (in_tskp != NULL)
  {
   stp = in_tskp->tskst; 
   /* know will always be at least an NONE - ; by itself */
   if (stp == NULL) __misc_terr(__FILE__, __LINE__);
   st_ifi = (int32) stp->stfnam_ind;
   st_lini = stp->stlin_cnt;
   /* if location in task and before first statement - use first statement */
   if (ifi2 <= st_ifi && lini2 <= st_lini) return(stp);

   /* here must use included file/line */
   if ((stp2 = find_lstofsts_stp(stp, ifi, lini)) != NULL) return(stp2);
   /* since know in task and not before any statement - must be after last */
   /* change to last */
   /* if after last - not found since know in scope becomes last */
   return(__blklast_stp);
  }
 /* in module, look through ia blocks - must be from 1st to last statement */ 
 /* after 1st part of last statement to end will be error not last stmt */
 for (ialp = in_mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   stp = ialp->iastp;
   /* if location before, begin of initial/always skip */
   if (ifi2 < ialp->ia_first_ifi || (ifi2 == ialp->ia_first_ifi
    && lini2 < ialp->ia_first_lini)) continue;
   /* if location after, end of initial/always skip */
   if (ifi2 > (int32) ialp->ia_last_ifi || (ifi2 == ialp->ia_last_ifi
    && lini2 > ialp->ia_last_lini)) continue;

   /* here must match include line */
   if ((stp2 = find_lstofsts_stp(stp, ifi, lini)) != NULL) return(stp2);
   /* if after last in init/always, just use last - know muat be there */
   return(__blklast_stp);
  }
 return(NULL);
}

/*
 * for searching source file, find next statement
 * passed last statement which know line number after (also file)
 * and before or equal to next statement (stnxt) if there is one 
 *
 * return match or NULL if at last
 * know line after last_stp and before next statement
 * look inside statement if possible
 */
static struct st_t *find_nxtstp(struct st_t *last_stp, int32 ifi, int32 lini)
{
 int32 fji;
 byte styp; 
 int32 st_ifi, st_lini, has_else;
 struct st_t *tmpstp, *stp2, *fjstp;
 struct task_t *tskp;
 
again:
 styp = (byte) last_stp->stmttyp;
brk_again:
 switch (styp) {
  case S_IF:
   /* know after if ( ) and before next stmtm */
   /* if no else, only look in if */
   if (last_stp->st.sif.elsest == NULL)
    {
     has_else = FALSE;
try_then:
     if ((tmpstp = find_lstofsts_stp(last_stp->st.sif.thenst, ifi, lini))
      != NULL) return(tmpstp);
     if (has_else) return(last_stp->st.sif.elsest);
     break;
    }
   /* has else */
   tmpstp = last_stp->st.sif.elsest;
   st_ifi = (int32) tmpstp->stfnam_ind;
   st_lini = (int32) tmpstp->stlin_cnt;
   /* if match else statement, return it */
   if (ifi == st_ifi && lini == st_lini) return(tmpstp);
   if (ifi < st_ifi || (ifi == st_ifi && lini < st_lini))
    { has_else = TRUE; goto try_then; }
   /* can only in else or next statement */
   return(find_lstofsts_stp(last_stp->st.sif.elsest, ifi, lini));
  case S_FOR:
   return(find_lstofsts_stp(last_stp->st.sfor->forbody, ifi, lini));
  case S_FOREVER: case S_WHILE: case S_DO_WHILE:
   return(find_lstofsts_stp(last_stp->st.swh.lpst, ifi, lini));
  case S_REPEAT:
   return(find_lstofsts_stp(last_stp->st.srpt.repst, ifi, lini));
  case S_WAIT:
   return(find_lstofsts_stp(last_stp->st.swait.lpst, ifi, lini));

  /* lists that need to be searched */
  case S_CASE:
   /* tricky since default can be anywhere - must find defl. insert loc */ 
   return(find_case_stp(last_stp, ifi, lini));
  case S_DELCTRL:
   /* know does not match location of # or @ <something> */
   /* if no action statement, done */
   if ((tmpstp = last_stp->st.sdc->actionst) == NULL) break;
   return(find_lstofsts_stp(tmpstp, ifi, lini));
  case S_NAMBLK:
   /* see if in name block, handles any where between begin and end */ 
   /* if inside name block must succeed */
   tskp = last_stp->st.snbtsk;
   if (scope_lini_inrng(lini, ifi, tskp->tsksyp->sylin_cnt,
    (int32) tskp->tsksyp->syfnam_ind, tskp->tsk_last_lini, tskp->tsk_last_ifi))
    {
     tmpstp = tskp->tskst; 
     /* if location in task and before first sttt - use first statement */
     if (ifi <= (int32) tmpstp->stfnam_ind && lini <= tmpstp->stlin_cnt)
      return(tmpstp);

     /* this will set last if past last in block statement */
     if ((stp2 = find_lstofsts_stp(tmpstp, ifi, lini)) != NULL) return(stp2);
     return(__blklast_stp);
    }
   break;
  case S_UNBLK:
   /* know after begin */
   return(find_lstofsts_stp(last_stp->st.sbsts, ifi, lini));
  case S_UNFJ:
   /* know after fork */
   for (fji = 0;; fji++)
    {
     if ((fjstp = last_stp->st.fj.fjstps[fji]) == NULL) break;

     /* if find, done */
     if ((tmpstp = find_lstofsts_stp(fjstp, ifi, lini)) != NULL)
      return(tmpstp);
    }
   /* know after last - matches next one up */
   break;
  /* special simulation control statements */
  case S_REPSETUP:
   /* this must be invisible - has same line as next stmt */
   last_stp = last_stp->stnxt;
   goto again;
  case S_REPDCSETUP:
   /* this must be invisible - has same line as next stmt */
   last_stp = last_stp->stnxt;
   goto again;
  case S_GOTO:
   /* here there will never be a next */
   if (last_stp->stnxt != NULL) __misc_terr(__FILE__, __LINE__);
   break; 
  case S_BRKPT:
   styp = (byte) last_stp->rl_stmttyp;
   goto brk_again;
  default: break;
 }
 return(NULL);
}

/*
 * find next statement in list 
 * can be before first in which case return first, if after last, return nil
 */
static struct st_t *find_lstofsts_stp(struct st_t *hdrstp, int32 ifi, int32 lini)
{
 struct st_t *stp; 
 int32 st_ifi, st_lini, ifi2, lini2; 
 struct st_t *stp2;
 struct incloc_t *ilp;

 for (__blklast_stp = NULL, stp = hdrstp; stp != NULL; stp = stp->stnxt)
  {
   /* know does not match header */
   st_ifi = (int32) stp->stfnam_ind;
   st_lini = (int32) stp->stlin_cnt;
   /* if line and statement in same file use if before or at */ 
   if (ifi == st_ifi && lini <= st_lini) return(stp);

   /* if next statement is inside include use it if before include point */
   /* notice if includes nested must find include line in current file */
   /* which may be included itself */
   if ((ilp = find3_incloc(st_ifi, ifi)) != NULL) 
    { 
     ifi2 = ilp->incfrom_fnind;
     lini2 = ilp->incfrom_lcnt;
     /* if before or at include use first statement of include */
     if (ifi < ifi2 || (ifi == ifi2 && lini <= lini2)) return(stp);
    }
   else 
    {
     /* normal rule: if before or at next loop statement return it */
     if (ifi < st_ifi || (ifi == st_ifi && lini <= st_lini)) return(stp);
    }
   /* this statement may be block or other complicated */
   if ((stp2 = find_nxtstp(stp, ifi, lini)) != NULL) return(stp2);
   /* after current and any substatement structure */
   __blklast_stp = stp;
  }
 /* after block - will probably be at next statement */ 
 return(NULL);
}

/*
 * find incloc that is non included file
 * for multiply included this returns location of outermost or caller if
 * caller is itself an included file 
 */
static struct incloc_t *find3_incloc(int32 ifi, int32 call_ifi)
{
 struct incloc_t *ilp, *ilp2; 

 if ((ilp2 = find_incloc(ifi)) == NULL) return(NULL);
 /* know included trace outward until finding one not included and */
 /* return that ilp */
 for (;;)
  {
   ifi = ilp2->incfrom_fnind;
   if (ifi == call_ifi) return(ilp2);
   ilp = ilp2;
   if ((ilp2 = find_incloc(ifi)) == NULL) break;
  }
 return(ilp);
}

/*
 * find statement inside (or after case)
 * know after case header and can have default case somwwhere
 * each case statement or default can be list (begin elided)
 */
static struct st_t *find_case_stp(struct st_t *last_stp, int32 ifi, int32 lini)
{
 struct csitem_t *csip;
 struct st_t *stp, *tmpstp, *stp_after_dflt;
 struct csitem_t *dflt_csip; 

 dflt_csip = last_stp->st.scs.csitems;
 if (dflt_csip->csist != NULL) stp_after_dflt = find_afterdflt(dflt_csip);
 else stp_after_dflt = NULL;
 for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
  {
   stp = csip->csist;
   
   /* if this case statement list after default, see if in default range */
   /* only T if has default, i.e. no stp non nil so will never match */
   if (stp_after_dflt == stp)
    {
     if ((tmpstp = find_lstofsts_stp(dflt_csip->csist, ifi, lini)) != NULL)
      return(tmpstp);
     /* if after default end, look at next case */
    }
   /* see if in this case range */
   if ((tmpstp = find_lstofsts_stp(stp, ifi, lini)) != NULL) return(tmpstp);
  }
 /* this will move up stack to connect ending stnxt to next exec. place */
 if (dflt_csip->csist != NULL && stp_after_dflt == NULL)
  return(find_lstofsts_stp(dflt_csip->csist, ifi, lini));
 return(NULL);
}

/*
 * find case statement immediately after default 
 * only called if has default
 * returns nil on common default at end case
 */
static struct st_t *find_afterdflt(struct csitem_t *dflt_csip)
{
 struct csitem_t *csip;
 int32 st_ifi, st_lini, dflt_ifi, dflt_lini;
 struct st_t *dfltstp, *stp;

 dfltstp = dflt_csip->csist;
 dflt_ifi = (int32) dfltstp->stfnam_ind;
 dflt_lini = dfltstp->stlin_cnt;
 
 /* key is that know all case items except default in source order */
 /* also one after default is always first in source order */
 for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
  {
   stp = csip->csist;
   st_ifi = (int32) stp->stfnam_ind;
   st_lini = stp->stlin_cnt;
   if (st_ifi > dflt_ifi || (st_ifi == dflt_ifi && st_lini >= dflt_lini))
    return(stp);
  }
 return(NULL);
}

#define TYP_BRKPTS 0
#define TYP_DISP 1

/* info command options table */
static struct namlst_t dtyparg[] = {
 { TYP_BRKPTS, "breakpoints" },
 { TYP_DISP, "displays" } 
};
#define NTYPARGS (sizeof(dtyparg) / sizeof(struct namlst_t))

/*
 * : debugger breakpint32 delete command
 */
extern void __do_dbg_delbrkdis(void)
{
 int32 bpnum, deltyp;

 __get_vtok();
 if (__toktyp == ID)
  { deltyp = __get_dbcmdnum(__token, dtyparg, NTYPARGS); __get_vtok(); }
 else deltyp = TYP_BRKPTS;

 if (deltyp == TYP_BRKPTS)
  {
   if (__toktyp == TEOF) del_all_brkpts();
   else
    {
     if ((bpnum = __get_dbg_val()) == -1 || bpnum < 1)
      {
       __ia_err(1471, "breakpoint number %s illegal - can not delete",
        __prt_vtok());
       return;
      } 
     del_brkpt_num(bpnum);
     __chk_extra_atend(TRUE);
    }
  }
 else
  {
   if (__toktyp == TEOF) del_all_disps();
   else { del_disp_num(); __chk_extra_atend(TRUE); }
  }
}

/*
 * delete all breakpoints 
 */
static void del_all_brkpts(void)
{
 struct brkpt_t *bpp, *bpp2;
 char s1[RECLEN];

 if (__bphdr == NULL)
  { __ia_err(1466, "no breakpoints to delete"); return; }
 __cvsim2_msg("Delete all breakpoints? (y/n) ");
 /* FIXME - how read input from vendor 1 side */
 if (fgets(s1, RECLEN, stdin) == NULL || (s1[0] != 'y' && s1[0] != 'Y'))
  return;
 for (bpp = __bphdr; bpp != NULL;)
  {
   bpp2 = bpp->bpnxt;
   /* if triggered, untrigger */
   if (bpp->bp_stp->stmttyp == S_BRKPT)
    bpp->bp_stp->stmttyp = bpp->bp_stp->rl_stmttyp; 
   __my_free(bpp, sizeof(struct brkpt_t));  
   bpp = bpp2;
  }
 __bphdr = NULL;
}

/*
 * delete break in globals tok typ and token
 */
static void del_brkpt_num(int32 bpnum)
{
 struct brkpt_t *bpp;
 struct brkpt_t *last_bpp, *bpp2;
 int32 bpcnt;

 /* delete break numbered bpnum */
 for (last_bpp = NULL, bpp = __bphdr; bpp != NULL; bpp = bpp->bpnxt)
  {
   if (bpp->bp_num == bpnum)
    {
     if (last_bpp == NULL) __bphdr = bpp->bpnxt; 
     else last_bpp->bpnxt = bpp->bpnxt;

     /* for temporary break points reuse number if last */
     if (bpp->bp_rm_when_hit)
      { if (bpp->bp_num == __nxt_bpnum - 1) __nxt_bpnum--; } 

     /* notice by here one to delete removed from list */
     bpcnt = cnt_same_brkpts((int32) bpp->bp_stp->stfnam_ind,
      bpp->bp_stp->stlin_cnt, &bpp2);
     /* if no more at this location and triggered, untrigger */
     if (bpcnt == 0 && bpp->bp_stp->stmttyp == S_BRKPT)
      bpp->bp_stp->stmttyp = bpp->bp_stp->rl_stmttyp; 
     /* if only one left at location unset the dup flag */ 
     if (bpcnt == 1) bpp2->bp_dup = FALSE;
     /* final step is to free the bp */
     __my_free(bpp, sizeof(struct brkpt_t)); 
     return;
    }
   last_bpp = bpp;
  }
 __ia_err(1471, "no breakpoint number %d", bpnum);
}

/*
 * count number of breakpoints at same location
 */
static int32 cnt_same_brkpts(int32 ifi, int32 lini, struct brkpt_t **last_bpp)
{
 int32 cnt;
 struct brkpt_t *bpp;
 
 cnt = 0;
 *last_bpp = NULL;
 for (bpp = __bphdr; bpp != NULL; bpp = bpp->bpnxt) 
  {
   if (ifi == (int32) bpp->bp_stp->stfnam_ind && lini == bpp->bp_stp->stlin_cnt)
    {
     cnt++;
     *last_bpp = bpp;
    }
  }
 return(cnt);
}

/*
 * undisplay breakpoints - same as delete display [optional number]  
 */
extern void __dbg_undisplay(void)
{
 __get_vtok();
 if (__toktyp == TEOF) del_all_disps();
 else { del_disp_num(); __chk_extra_atend(TRUE); }
}

/*
 * delete all auto-display points 
 */
static void del_all_disps(void)
{
 struct dispx_t *dxp, *dxp2;
 char s1[RECLEN];

 if (__dispxhdr == NULL)
  { __ia_err(1466, "no displays to delete"); return; }
 __cvsim2_msg("Delete all displays? (y/n) ");
 if (fgets(s1, RECLEN, stdin) == NULL || (s1[0] != 'y' && s1[0] != 'Y'))
  return;
 for (dxp = __dispxhdr; dxp != NULL;)
  {
   dxp2 = dxp->dsp_nxt;
   __my_free(dxp, sizeof(struct dispx_t));  
   dxp = dxp2;
  }
 __dispxhdr = NULL;
}

/*
 * delelete a display by number from tok typ and token 
 * know token read before calling this
 */
static void del_disp_num(void)
{
 struct dispx_t *dxp;
 struct dispx_t *last_dxp;
 int32 disnum;

 if ((disnum = __get_dbg_val()) == -1 || disnum < 1)
  {
   __ia_err(1471, "auto-display number %s illegal - can not delete",
    __prt_vtok());
   return;
  } 
 /* delete auto-display numbered disnum */
 for (last_dxp = NULL, dxp = __dispxhdr; dxp != NULL; dxp = dxp->dsp_nxt)
  {
   if (dxp->dsp_num == disnum)
    {
     if (last_dxp == NULL) __dispxhdr = dxp->dsp_nxt; 
     else last_dxp->dsp_nxt = dxp->dsp_nxt;

     /* final step is to free the bp */
     __my_free(dxp, sizeof(struct dispx_t)); 
     return;
    }
   last_dxp = dxp;
  }
 __ia_err(1471, "no auto-display number %d", disnum);
}

/*
 * disable or enable a breakpoint or display
 */
extern void __do_dbg_dis_enable(int32 do_enable)
{
 struct brkpt_t *bpp;
 struct dispx_t *dxp;
 int32 denum, disentyp;
 char s1[RECLEN];

 if (do_enable) strcpy(s1, "enable"); else strcpy(s1, "disable");
 __get_vtok();
 if (__toktyp == ID)
  {
   disentyp = __get_dbcmdnum(__token, dtyparg, NTYPARGS);
   __get_vtok();
  }
 else disentyp = TYP_BRKPTS;

 if (disentyp == TYP_BRKPTS)
  {
   if (__toktyp == TEOF) denum = -2; 
   else
    {
     if ((denum = __get_dbg_val()) == -1 || denum < 1)
      {
       __ia_err(1477, ":%s expected breakpoint number %s illegal", s1,
        __prt_vtok());
       return;
      }
    }
   /* delete break numbered bpnum */
   for (bpp = __bphdr; bpp != NULL; bpp = bpp->bpnxt)
    {
     if (denum == -2 || bpp->bp_num == denum)
      {
       bpp->bp_enable = (do_enable) ? TRUE : FALSE;
       if (denum != -2) goto done;
      }
    }
   if (denum == -2) goto done; 
   __ia_err(1479, ":%s breakpoint failed - no breakpoint number %d",
     s1, denum); 
   return;
  }
 /* display case */
 if (__toktyp == TEOF) denum = -2; 
 else
  {
   if ((denum = __get_dbg_val()) == -1 || denum < 1)
    {
     __ia_err(1477, ":%s expected auto-display number %s illegal", s1,
      __prt_vtok());
     return;
    }
  }
 /* delete break numbered bpnum */
 for (dxp = __dispxhdr; dxp != NULL; dxp = dxp->dsp_nxt)
  {
   if (denum == -2 || dxp->dsp_num == denum)
    {
     dxp->dsp_enable = (do_enable) ? TRUE : FALSE;
     if (denum != -2) goto done;
    }
  }
 if (denum == -2) goto done;
 __ia_err(1479, ":%s displays failed - no auto-display number %d",
  s1, denum); 
 return;

done:
 __chk_extra_atend(TRUE);
}

/*
 * set ignore count for a break point (add to current hit count)
 *
 * :cond [bp num] [ingore count]
 * ignore next count breakpoints before breaking
 */
extern void __dbg_brk_ignore(void)
{
 int32 icnt;
 struct brkpt_t *bpp;

 __get_vtok();
 if ((bpp = rd_brkpt_num(":ignore", 1)) == NULL) return; 
 __get_vtok();
 if (__toktyp == TEOF)
  {
   __ia_err(1491,
    ":ignore second argument (number of hits to ignore) missing");
   return;
  }
 if ((icnt = __get_dbg_val()) == -1 || icnt < 0)
  { 
   __ia_err(1492,
    ":ignore second argument (number of hits to ignore) illegal - %s read",
    __prt_vtok());
   return;
  }

 /* ignore count value in brk pt record is number from current hit number */  
 /* count is number to ignore so 0 is next, 1 is skip 1, and stop on next */ 
 /* and so on */
 bpp->bp_ignore_cnt = bpp->bp_hit_cnt + icnt;  
 if (icnt == 0)
  __cvsim_msg("Stopping next time breakpoint %d is reached.\n", bpp->bp_num);
 else __cvsim_msg("Ignoring next %d crossings of breakpoint %d.\n", icnt,
  bpp->bp_num);
}

/*
 * read a break point number argument and return break point record
 * returns nil on error
 * expects number token to have been read and reads no more
 */
static struct brkpt_t *rd_brkpt_num(char *cmdnam, int32 argnum)
{
 int32 bpnum;
 struct brkpt_t *bpp;

 if (__toktyp == TEOF)
  {
   __ia_err(1491,
    "%s argument number %d (break point number) missing", cmdnam, argnum);
   return(NULL);
  }
 if ((bpnum = __get_dbg_val()) == -1)
  { 
   __ia_err(1492, "%s argument number %d break point number %s illegal",
    cmdnam, argnum, __prt_vtok());
   return(NULL);
  }
 if ((bpp = find_bpp(bpnum)) == NULL) 
  {
   __ia_err(1493,
    "there is no break point number %d (argument %d)", bpnum, argnum);
   return(NULL);
  }
 return(bpp);
}

/*
 * set up condition filter expresson for break point
 : :cond [bp num] [cond expr]
 */
extern void __dbg_brk_cond(void)
{
 t_midat *sav_scope_idp;
 struct task_t *sav_scope_tskp;
 struct expr_t *xp;
 struct brkpt_t *bpp;
 decl_idp_locals_;

 __get_vtok();
 if ((bpp = rd_brkpt_num(":cond", 1)) == NULL) return;

 /* if collect returns nil, know error emitted in routine */
 __get_vtok();
 /* ":cond [number]" turns off condition */
 if (__toktyp == TEOF)
  {
   __cvsim_msg("Breakpoint %d now unconditional.\n", bpp->bp_num);
   xp = NULL;
  }
 else
  {
   sav_scope_idp = __scope_idp;
   sav_scope_tskp = __scope_tskp;
   __scope_idp = bpp->bp_idp;
   __scope_tskp = bpp->bp_tskp; 
   set_save_idp_(__scope_idp);
   xp = __rd_iact_expr();
   restore_idp_();
   __scope_idp = sav_scope_idp;
   __scope_tskp = sav_scope_tskp; 
   if (xp == NULL) return;
  }
 bpp->bp_condx = xp;
 __chk_extra_atend(TRUE);
}

/*
 * find a break point given its number 
 */
static struct brkpt_t *find_bpp(int32 bpnum)
{
 struct brkpt_t *bpp;

 for (bpp = __bphdr; bpp != NULL; bpp = bpp->bpnxt)
  { if (bpp->bp_num == bpnum) return(bpp); }
 return(NULL);
}

/*
 * process a breakpoint
 *
 * called from v_ex using exec itree loc.
 * tricky because possibly multiple breaks at one statement
 * if returns FALSE, does not enter iact and execs and reenables stmt brk
 * whenever statement with break execed, rearms but setting type to S BRK 
 *
 * complicated breakpoint logic - every hit stmt breakpoint must change to
 * can not halt so will be execed 
 */
extern int32 __process_brkpt(struct st_t *stp)
{
 struct brkpt_t *bpp;
 int32 stop_from_dup;
 struct brkpt_t *brk_bpp, *bpp2, *first_hitbpp;

 /* always find first in list */
 brk_bpp = NULL;
 first_hitbpp = NULL;
 for (bpp = __bphdr; bpp != NULL; bpp = bpp->bpnxt)
  { if (bpp->bp_stp == stp) goto found_stmt_match; }
 /* if have statement with type breakpoint must be in table */ 
 __arg_terr(__FILE__, __LINE__);

found_stmt_match:
 brk_bpp = bpp;
 /* if any on same line in not can halt state all are, cont from break, */
 /* scheme is once exec of SBRK stmt, turn off can halt so next time */
 /* stmt execed not S BRK */
 if (!brk_bpp->bp_can_halt)
  {
   /* rearm (all on line if needed) and return F - will exec stmt. */
   /* notice brk_bpp is first on stmt */
   if (brk_bpp->bp_dup)
    {
     for (bpp = brk_bpp; bpp != NULL; bpp = bpp->bpnxt)
      { if (bpp->bp_stp == stp) bpp->bp_can_halt = TRUE; }
    }
   else brk_bpp->bp_can_halt = TRUE;
   /* now all breakpoints at statement armed and will exec statement */
   return(FALSE);
  } 

 /* found breakpoints on line - see if filters eliminate stop */
 if (!brk_bpp->bp_dup)
  {
   if (elim_brkpt_fromcond(brk_bpp))
    {
     /* make sure stmt gets execed next time it is execed */
     /* when hit stmt does not get advanced, go thru here first */
     brk_bpp->bp_can_halt = TRUE;
     return(FALSE);
    }
   first_hitbpp = brk_bpp;
  }  
 else
  {
   stop_from_dup = FALSE;
   for (bpp = brk_bpp; bpp != NULL; bpp = bpp->bpnxt)
    {
     if (bpp->bp_stp != stp) continue;
     /* if find any that stop, must stop */ 
     if (!elim_brkpt_fromcond(bpp))
      {
       stop_from_dup = TRUE;
       if (first_hitbpp == NULL) first_hitbpp = bpp;
      }
    }
   if (!stop_from_dup)
    {
     /* all are filtered out, no stop */
     for (bpp = brk_bpp; bpp != NULL; bpp = bpp->bpnxt)
      { if (bpp->bp_stp == stp) bpp->bp_can_halt = TRUE; }
     return(FALSE);
    }
  }

 /* mark all as cannot stop for next exec and inc count on all */
 if (!brk_bpp->bp_dup) brk_bpp->bp_can_halt = FALSE;
 else
  {
   for (bpp = brk_bpp; bpp != NULL; bpp = bpp->bpnxt)
    { if (bpp->bp_stp != stp) continue; bpp->bp_can_halt = FALSE; }
  }
 /* need to indicate at this line in case step since have hit this line */
 __step_lini = stp->stlin_cnt;
 __step_ifi = (int32) stp->stfnam_ind;

 /* hit breakpoint - write message and setup suspend into interactive dbger */
 __cvsim_msg("\nBreakpoint %d scope %s", first_hitbpp->bp_num,
  __msg_cur_blditree(__xs, first_hitbpp->bp_tskp)); 
 __cvsim_msg(" (%s line %d)", __in_fils[stp->stfnam_ind], stp->stlin_cnt);
 if (__last_brktime != __simtime)
  {
   __cvsim_msg(" time %s\n", __to_timstr(__xs, &__simtime));
   __last_brktime = __simtime;
  }
 else __cvsim_msg("\n");
 __prt_src_lines((int32) stp->stfnam_ind, stp->stlin_cnt, stp->stlin_cnt);

 /* remove all temp (t) breaks at this statement */
 /* know break always put on first statement of line */
 if (brk_bpp->bp_dup)
  {
   for (bpp = brk_bpp; bpp != NULL;)
    {
     bpp2 = bpp->bpnxt;
     if (bpp->bp_stp == stp)
      { if (bpp->bp_rm_when_hit) del_brkpt_num(bpp->bp_num); }
     bpp = bpp2;
    }
  }
 else { if (brk_bpp->bp_rm_when_hit) del_brkpt_num(brk_bpp->bp_num); }

 /* must not suspend thread here since when hit enter iact test will */
 /* supsend, suspend on entry needed in case ^c entry to interact */
 /* even if interrupt (^c) received, doing again does not hurt */
#ifndef __NOSIGS__
 signal(SIGINT, SIG_IGN);
#endif

 __pending_enter_iact = TRUE;
 __iact_reason = IAER_BRKPT;  
 return(TRUE);
}

/*
 * process all conditions that disable stopping from a break point
 * returns T if break point eliminated (i.e. not stopped at)
 * F => break hit need to enter iact mode
 */
static int32 elim_brkpt_fromcond(struct brkpt_t *bpp)
{
 struct xstk_t *xsp;
 word32 tmp;
 decl_idp_locals_;

 /* handle all not dup cases */
 if (!bpp->bp_enable || (bpp->bp_type == BP_INST
   && bpp->bp_idp != __idp)) return(TRUE);

 /* evaluate conditional expression if present */
 if (bpp->bp_condx != NULL)
  {
   set_save_idp_(bpp->bp_idp);
   xsp = __eval_xpr(bpp->bp_condx);
   /* normal loop T condition, if any bit 1, then T (non zero) */
   if (xsp->xslen <= WBITS)
    {
     /* SJM 07/20/00 - must convert to real if real */
     if (bpp->bp_condx->is_real)
      {
       double d1;

       memcpy(&d1, xsp->ap, sizeof(double));
       tmp = (d1 != 0.0);
      }
     else tmp = ((xsp->ap[0] & ~xsp->bp[0]) != 0L);
    } 
   else tmp = (__cvt_lngbool(xsp->ap, xsp->bp, wlen_(xsp->xslen)) == 1);
   __pop_xstk();
   restore_idp_();
   /* non 1 (F) so routine returns T to cancel */
   if (!tmp) return(TRUE);
  }
 /* must always increment hit count before checking ignore count */
 /* otherwide will never advance to ignore count */
 (bpp->bp_hit_cnt)++;
  
 /* being ignored because not yet hit enough times */
 /* if hit is 0, and ignore is 1, 1st time here will both be 1 */
 /* so not hit, 2nd time hit will be 2, so hit */ 
 /* DBG remove ---
 __dbg_msg("=== hit count for break %d is %d and ignore count is %d ===\n",
  bpp->bp_num, bpp->bp_hit_cnt, bpp->bp_ignore_cnt);
 --- */

 if (bpp->bp_hit_cnt <= bpp->bp_ignore_cnt) return(TRUE);
 return(FALSE);
}

/*
 * ROUTINES TO RESET STATE TO START OF SIM 
 */

/*
 * reset simulation back to time 0
 * LOOKATME - could just save after initializing values then just reload
 */
extern void __reset_to_time0(void)
{
 int32 i;
 struct thread_t *thp;
 char *chp;
 struct tev_t *tevp;
 struct thread_t *thp2;
 struct fmonlst_t *fmonp, *fmonp2;
 struct dceauxlst_t *dclp;
 struct mdvmast_t *mdvp, *mdvp2;
 struct hctrl_t *hcp, *hcp2;
 struct strblst_t *strbp;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct brkpt_t *bpp;

 /* --- debug remove --
 -* if (__debug_flg) __dmp_tskthrds(); *-
 if (__debug_flg) __dmp_all_thrds();
 --- */

 /* free the procedural threads and subthreads */
 /* this mark events so must be done first */
 /* know here thread always top level */
 for (thp = __initalw_thrd_hdr; thp != NULL;)
  { 
   thp2 = thp->thright;
   /* free thp and all underneath */ 
   if (thp->thofs != NULL) __free_thd_list(thp->thofs);
   thp->th_ialw = FALSE;
   __free_1thd(thp);
   thp = thp2;
  }
 __initalw_thrd_hdr = NULL;
 /* disable all active interactive statements */
 for (hcp = __hctrl_hd; hcp != NULL;)
  {
   hcp2 = hcp->hc_nxt;
   /* unlink interactive leaving hcp since can just free element without */
   /* unlinking */
   __do_iact_disable(hcp, TRUE);
   __my_free(hcp, sizeof(struct hctrl_t));
   hcp = hcp2;
  }
 /* DBG remove - check to make sure all tasks freed */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->tsktyp == FUNCTION) 
      {
       if (tskp->tthrds != NULL) __misc_terr(__FILE__, __LINE__);
       continue;
      }
     for (i = 0; i < mdp->flatinum; i++) 
      { if (tskp->tthrds[i] != NULL) __misc_terr(__FILE__, __LINE__); }
    }
  }
 /* --- */

 __hctrl_hd = __hctrl_end = NULL;
 /* any breakpoints halted but not yet continued from reset, reenable */
 /* when breakpoint counts added, will reset here */
 for (bpp = __bphdr; bpp != NULL; bpp = bpp->bpnxt) 
  {
   bpp->bp_can_halt = TRUE;
   bpp->bp_ignore_cnt = 0; 
  }

 /* free all timing tree events */
 /* this is needed because need to free guts of events and need to leave */
 /* tevtab action cb elements */ 
 for (; ; )
  {
   tevp = __get_next_time_header();
   if (tevp == NULL) break;
   __free_telhdr_tevs(tevp); 
  }

 /* cur te hdr/end is same as one of twheel lists if hdr non nil */ 
 __cur_te_hdrp = __cur_te_endp = NULL;  

 /* but no timing wheel te hdr corresponds to #0s */ 
 if (__p0_te_hdrp != NULL)
  {
   struct tev_t *tevp2;

   for (tevp = __p0_te_hdrp; tevp != NULL;)
    {
     tevp2 = tevp->tenxtp;
     __free_1tev(tevp);
     tevp = tevp2; 
    }
   __p0_te_hdrp = __p0_te_endp = NULL;  

   for (tevp = __nb_te_hdrp; tevp != NULL;)
    {
     tevp2 = tevp->tenxtp;
     __free_1tev(tevp);
     tevp = tevp2; 
    }
   __nb_te_hdrp = __nb_te_endp = NULL;
  }

 /* free pending strobes for this time slot - if none added does nothing */
 if (__strobe_hdr != NULL)
  {
   /* must mark any seen but not output strobe as not seen */
   for (strbp = __strobe_hdr; strbp != NULL; strbp = strbp->strbnxt) 
    strbp->strbstp->strb_seen_now = FALSE;

   __strobe_end->strbnxt = __strb_freelst;
   __strb_freelst = __strobe_hdr;
  } 
 __strobe_hdr = __strobe_end = NULL;

 /* free pending dce list  */
 /* notice here dcevnts turned off when needed net dcelst's turned off */
 for (fmonp = __fmon_hdr; fmonp != NULL;) 
  {
   fmonp2 = fmonp->fmonnxt;
   /* free all fmon aux list since only on if re-added after reset */
   for (dclp = fmonp->fmon_dcehdr; dclp != NULL; dclp = dclp->dclnxt)
    {
     /* AIV 11/26/02 dc events now built during elaboration and not freed */
     dclp->ldcep->dce_off = TRUE;
    }
   __my_free(fmonp, sizeof(struct fmonlst_t));
   fmonp = fmonp2;
  }
 __fmon_hdr = __fmon_end = NULL; 

 /* free any activated but not yet executed slot end fmonitors */
 if (__fmonse_hdr != NULL)
  {
   __fmonse_end->fmsenxt = __fmse_freelst;
   __fmse_freelst = __fmonse_hdr;
  } 

 /* free monitor - same as call to $monitor with no arguments */
 /* know only 1 inst. */
 /* indcate no pending monitor */
 /* SJM 06/21/02 - never free monit dces - just turn off - but free list */
 for (dclp = __monit_dcehdr; dclp != NULL; dclp = dclp->dclnxt)
  {
   /* turn off the dce but do not free */
   /* AIV 11/26/02 dc events now built during elaboration and not freed */
   dclp->ldcep->dce_off = TRUE;
  }
 if (__monit_dcehdr != NULL) __monit_dcehdr = NULL;
 __monit_stp = NULL;
 __monit_idp = NULL;

 /* re-initialize vars and state and the dce list for each wire */
 /* dce list both scheduled events tables reset and triggered dmpv bits */
 reinit_vars_and_state();
 /* DBG remove ---
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   __dmpmod_nplst(mdp, TRUE);
   __pop_wrkitstk();
  }
 --- */

 /* free dumpvars setup master records - will be setup again */ 
 for (mdvp = __dv_hdr; mdvp != NULL;)
  {
   mdvp2 = mdvp->mdvnxt;
   __my_free(mdvp, sizeof(struct mdvmast_t));
   mdvp = mdvp2;
  }
 __dv_hdr = __dv_end = NULL;
 /* close any open dumpvars file */ 
 if (strcmp(__dv_fnam, DFLTDVFNAM) != 0)
  {
   __my_free(__dv_fnam, strlen(__dv_fnam) + 1);
   __dv_fnam = __pv_stralloc(DFLTDVFNAM);
  }
 /* close any dv file, if running gets to dv will then overwrite */
 if (__dv_fd != -1) { __my_close(__dv_fd); __dv_fd = -1; }

 if (__has_dumpports_sys_calls)
  {
   __cleanup_dumpports(); 
  }

 /* close fst file */
 if (__fst_ctx != NULL) __fst_close();

 /* add any pending until slot end tim chk changes to free list */
 if (__tcpendlst_end != NULL)
  {
   __tcpendlst_end->tc_plnxt = __tcpendfreelst; 
   __tcpendfreelst = __tcpendlst_hdr;
   __tcpendlst_hdr = __tcpendlst_end = NULL; 
  }

 /* free any pending but unprocessed net change records */ 
 if (__nchg_futend != NULL)
  {
   __nchg_futend->nchglnxt = __nchgfreelst;
   __nchgfreelst = __nchg_futhdr;
  }

 /* add any pending dumpvars changes to end of free list for next time */
 if (__dv_chgnethdr != NULL)
  {
   __dv_chgnethdr = NULL;
  }
 /* must close any open multi-channel descriptors and turn bit off */
 /* initialize the multichannel descriptor table */
 /* SJM 03/26/00 - bit 3 (value 4) no longer log file - lumped with stdout */ 
 /* leave stdout (1) and stderr (2) */
 for (i = 2; i < 31; i++)
  {
   if (__mulchan_tab[i].mc_s == NULL) continue;
    
   __my_fclose(__mulchan_tab[i].mc_s);
   chp = __mulchan_tab[i].mc_fnam;
   __my_free(chp, strlen(chp) + 1);
   __mulchan_tab[i].mc_s = NULL;
   __mulchan_tab[i].mc_fnam = NULL;
  }
 /* free all tfrec for tf_ tasks and functions to initial state */
 __reinit_tfrecs();
 /* putv records reinitialized during wire reset */
 __reinit_vpi(); 

 /* can leave any pending repeat counts since will be reset when entered */
 /* rerun initialize to propagate all initial events */
 __reinit_sim();
 /* must leave any breakpoints and debugger states */
 /* will start up as previous so if -s set, will again enter interactive */
}

/*
 * re-initialize variables and state information 
 * traverse static circuit freeing all values and pending scheduled values
 */
static void reinit_vars_and_state(void)
{
 int32 gi, i;
 struct mod_pin_t *mpp;
 struct mod_t *mdp;
 struct gate_t *gp;
 int32 insts;
 t_midat *idp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   /* turn off dumpvars in mod here and in caller */
   mdp->mod_hasdvars = FALSE;
   __reinitialize_vars(mdp);
   __pop_wrkitstk();
  }
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* turn off dumpvars in mod here and in caller */
   mdp->mod_hasdvars = FALSE;

   insts = mdp->flatinum;
   /* since can't init dces until cgen .bss .so linking done - same as init */
   __initialize_dces(mdp);
   for (gi = 0; gi < mdp->mgnum; gi++)
    {
     gp = &(mdp->mgates[gi]);
     /* no scheduled event table if no delay */ 
     if (gp->schd_tevs_ofs != (t_midat) NULL)
      { 
       for (i = 0; i < insts; i++) 
        {
         idp = mdp->moditps[i]->it_idp;
         idp[gp->schd_tevs_ofs] = (t_midat) NULL; 
        }
      }

     if (gp->g_class == GC_UDP) __init_all_inst_udp_state(gp, mdp);
     else
      {
       if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN) goto nxt_mod;
       /* if output unc. (OPEMPTY), changes are not seen (do not propagate) */
       if (gp->g_class != GC_TRANIF && gp->gpins[0]->optyp == OPEMPTY)
        goto nxt_mod;

       __init_all_inst_gate_state(gp, mdp);
      }
    }
   /* AIV 08/13/07 - this is now a routine to init idp area */
   __reinit_all_contas_in_mod(mdp);

   if (mdp->mod_has_mipds)
    {
     for (i = 0; i < mdp->mpnum; i++)
      {
       mpp = &(mdp->mpins[i]);
       if (!mpp->has_mipd) continue;

       __reinit_mipd(mpp, mdp);
      }
    }
nxt_mod:
   __pop_wrkitstk();
  }
 __set_pre_idp_nchgaction_bits();
}

/*
 * NON DEBUGGER ONLY ROUTINES
 */

/*
 * ROUTINES TO IMPLEMENT PENDING EVENT TRACE  
 */

/*
 * write event location trace - assume basic event message already printed
 * for active thread could actually give trace back of enables
 * may be no scope here
 */
extern void __write_snapshot(int32 pend_num)
{
 int32 i;
 struct tev_t *tevp;
 struct thread_t *thp;

 __cvsim_msg("*** Activity snapshot at %s ***\n", __to_timstr(__xs,
  &__simtime));
 if (__cur_tevp == NULL)
  {
   if (__idp == NULL) strcpy(__xs, "<none>");
   else __msg2_cur_blditree(__xs);

   if (__sfnam_ind <= 0)
    __cvsim_msg("Current event: <none> last scope %s - no last statement\n",
      __xs);
   else __cvsim_msg(
    "Current event: <none> last scope %s - last statement %s\n", __xs,
    __bld_lineloc(__xs2, (word32) __sfnam_ind, __slin_cnt));
   if (__suspended_thd != NULL)
    {
     __cvsim_msg("Trace back of just suspended statements:\n");  
     __prt_where_msg(__suspended_thd);
    }
  }
 else
  {
   /* current event is one being processed now */
   if (__cur_tevp->enterptr == __process_thrd_ev)
    {
     thp = __cur_tevp->tu.tethrd;
     __cvsim_msg("Trace back of enabled statements:\n");  
     __prt_where_msg(thp);
    }
   else
    {
     /* this write the end new line */
     wr_1ev_trace(-1, __cur_tevp);
    }
  }
 /* FIXME - think this is wrong for CG thrd but rarely used feature */
 fill_near_evtab(pend_num, TE_THRD);
 if (__last_wevti >= 0)
  __cvsim_msg("\nNext %d pending procedural events:\n", __last_wevti + 1); 

 for (i = 0; i <= __last_wevti; i++)  
  {
   tevp = __wrkevtab[i];
   wr_1ev_trace(i, tevp);
  }
 fill_near_evtab(pend_num, TE_G);
 if (__last_wevti >= 0)
  __cvsim_msg("\nNext %d pending declarative events:\n", __last_wevti + 1); 
 for (i = 0; i <= __last_wevti; i++)  
  {
   tevp = __wrkevtab[i];
   wr_1ev_trace(i, tevp);
  }
 __dmp_all_thrds();
 __cvsim_msg("*** End of snapshot ***\n");
}

/*
 * print where message
 * LOOKATME - maybe this should not use global __fcspi
 */
extern void __prt_where_msg(struct thread_t *thp)
{
 int32 i;
 struct st_t *stp;
 struct task_t *tskp;
 struct thread_t *down_thp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 if (__fcspi >= 0) tskp = __fcstk[__fcspi];
 else if (thp->th_fj) tskp = __find_thrdtsk(thp);
 else tskp = thp->assoc_tsk;

 if ((stp = thp->thnxtstp) == NULL) strcpy(s1, "**END**"); 
 else __bld_lineloc(s1, (word32) stp->stfnam_ind, stp->stlin_cnt);
 __cvsim_msg("In scope %s next statement at %s\n",
  __msg_idp_blditree(s2, thp->th_idp, tskp), s1);

 if (__fcspi >= 0)
  {
   for (i = __fcspi - 1; i >= 0; i--)
    {
     tskp = __fcstk[i];
     __cvsim_msg(" -- function %s\n",
       __msg_idp_blditree(s1, thp->th_idp, tskp));
    }
   i = 0; 
  }
 else i = 1;
 down_thp = thp;
 for (thp = down_thp->thpar; thp != NULL; thp = thp->thpar, i++) 
  {
   if (down_thp->th_fj) tskp = __find_thrdtsk(down_thp);
   else tskp = down_thp->assoc_tsk;
   if (tskp == NULL) strcpy(s1, "");
   else sprintf(s1, " %s", __to_tsktyp(s2, tskp->tsktyp));
   if (down_thp->th_idp == NULL) __misc_terr(__FILE__, __LINE__);
   __msg_idp_blditree(s3, down_thp->th_idp, tskp);

   __cvsim_msg("%2d)%s enabled from %s in %s\n", i, s1,
    __bld_lineloc(s2, down_thp->thenbl_sfnam_ind, down_thp->thenbl_slin_cnt),
    s3);
   down_thp = thp;
  }
 __cvsim_msg("%2d) started from initial/always at %s in %s\n", i,
  __bld_lineloc(s1, down_thp->thenbl_sfnam_ind, down_thp->thenbl_slin_cnt),
  __msg_idp_blditree(s2, down_thp->th_idp, (struct task_t *) NULL));
}

/*
 * ROUTINES TO WRITE THREAD TRACE BACK
 */

/*
 * write trace of 1 thread event
 * for procedural scheduled but not active
 */
static void wr_1ev_trace(int32 i, struct tev_t *tevp)
{
 int32 lhslen, bi, wlen;
 byte *sbp;
 word32 *wp, av, bv;
 struct conta_t *cap;
 struct gate_t *gp;
 struct net_t *np;
 struct thread_t *thp;
 struct tfrec_t *tfrp;
 struct st_t *stp;
 t_midat *sav_tridp;
 struct xstk_t *xsp, *xsp2;
 struct task_t *tskp;
 struct tedputp_t *tedp;
 struct expr_t *xp;
 struct tfarg_t *tfap;
 char s1[RECLEN], s2[RECLEN];
 decl_idp_locals_;

 sav_tridp = __last_tridp;
 __last_tridp = NULL;
 if (i == -1) __cvsim_msg("Current event: ");
 else __cvsim_msg("  %2d) time %s ", i + 1, __to_timstr(__xs, &(tevp->etime)));
 if (tevp->enterptr == __process_cancel_ev_enterp) __cvsim_msg("[canceled] ");
 set_save_idp_(tevp->te_idp);
 if (tevp->enterptr == __process_thrd_ev)
  {
   /* SJM 03/15/01 - now using normal stmt thread mechanism */ 
   /* ithrd interpreter use stmt ithrd cod ptr */
   thp = tevp->tu.tethrd;  
   stp = thp->thnxtstp;
   /* here may have hit breakpoint in func. so ok */ 
   if (thp->th_fj) tskp = __find_thrdtsk(thp); else tskp = thp->assoc_tsk;
   __cvsim_msg("procedural event in %s resume", __msg_cur_blditree(__xs, tskp));
   if (stp == NULL) __cvsim_msg(" **at end**\n");
   else __cvsim_msg(" %s\n", __bld_lineloc(__xs, stp->stfnam_ind,
    stp->stlin_cnt)); 
   __cvsim_msg("      enabled from %s\n", __bld_lineloc(__xs,
    thp->thenbl_sfnam_ind, thp->thenbl_slin_cnt));
   }
 else if (tevp->enterptr == __process_gatechg_ev)
  {
   gp = tevp->tu.tegp;
   __cvsim_msg("gate line %s:\n", __bld_lineloc(__xs,
    gp->gsym->syfnam_ind, gp->gsym->sylin_cnt));
   __cvsim_msg("        %s\n", __gstate_tostr(__xs2, gp, TRUE));   
  }
 else if (tevp->enterptr == __process_conta_ev)
  {
   /* SJM 09/28/02 - notice for decomposed into per bit, this is PB el */
   cap = tevp->tu.tecap;
   __cvsim_msg("%s:\n", __to_evtrcanam(__xs, cap, tevp->te_idp));
   lhslen = cap->lhsx->szu.xclen;
   push_xstk_(xsp, lhslen);
   /* notice will never be called unless drv_wp exists - else no event */
   __ld_val(xsp->ap, xsp->bp, &(__idp[cap->ca_drv_ofs]), lhslen);
   /* build a conta driving string - may need to add strength */ 
   if (cap->ca_hasst)
    {
     push_xstk_(xsp2, 4*lhslen);
     sbp = (byte *) xsp2->ap;
     __st_standval(sbp, xsp, cap->ca_stval);
     __st_regab_tostr(s1, sbp, lhslen);
     __pop_xstk();
    }
   else __regab_tostr(s1, xsp->ap, xsp->bp, lhslen, BBIN, FALSE);
   __pop_xstk();
   xsp = __eval_xpr(cap->rhsx);
   /* notice for conta if 0 delay fi==1, never get here */
   __cvsim_msg("      %s = %s %s\n", s1, 
    __regab_tostr(__xs, xsp->ap, xsp->bp, cap->rhsx->szu.xclen, BBIN,
     FALSE), __bld_valofsched(__xs2, tevp));
   __pop_xstk();
  }
 else if (tevp->enterptr == __process_wire_ev 
   || tevp->enterptr == __process_trpthdst_ev)
  {
   np = tevp->tu.tenp->tenu.np;
   bi = tevp->tu.tenp->nbi;
   if (tevp->enterptr == __process_wire_ev) strcpy(s2, "wire event");
   else strcpy(s2, "inout path dest. event");
   __cvsim_msg("%s %s declared line %s\n",
    __to_cur_evtrwnam(__xs, np, bi, bi), s2,
    __bld_lineloc(__xs2, np->nsym->syfnam_ind, np->nsym->sylin_cnt));
   if (np->n_stren)
    {
     sbp = (byte *) &(__idp[np->nva_ofs]);
     __to_vvstnam(s1, (word32) sbp[bi]);
    }
   else
    { __ld_bit(&av, &bv, np, bi); __to_vvnam(s1, (word32) (av | (bv << 1))); }
   __cvsim_msg("       value %s %s\n", s1, __bld_valofsched(__xs2, tevp));
  }
 else if (tevp->enterptr == __process_mipd_nchg_ev)
  {
   /* FIXME - maybe add info so can print port bit too */
   np = tevp->tu.tenp->tenu.np;
   bi = tevp->tu.tenp->nbi;
   __cvsim_msg("MIPD on %s net %s\n", __to_ptnam(__xs2, np->iotyp),
    __to_cur_evtrwnam(__xs, np, bi, bi));
  }
 else if (tevp->enterptr == __process_nbpa_ev)
  {
   stp = tevp->tu.tenbpa->nbastp;
   __cvsim_msg("non blocking assign event in %s line %s",
    __msg2_cur_blditree(__xs), __bld_lineloc(__xs2, stp->stfnam_ind,
    stp->stlin_cnt));
   if (stp->st.sdc->repcntx != NULL)
    {
     sprintf(__xs, "waiting for repeat count events (now %s)\n",
      __to_timstr(__xs2, &(tevp->etime)));
    }
   else sprintf(__xs, "assign at %s\n", __to_timstr(__xs2, &(tevp->etime)));
   wp = tevp->tu.tenbpa->nbawp;
   /* SJM 08/08/99 - use copied lhs expr. with ndxes converted to con if set */
   if ((xp = tevp->tu.tenbpa->nblhsu.nblhsxp) == NULL) xp = stp->st.spra.lhsx;

   lhslen = xp->szu.xclen;
   wlen = wlen_(lhslen);
   __cvsim_msg("       new value %s %s\n",
    __xregab_tostr(s1, wp, &(wp[wlen]), lhslen, xp), __xs);
  }
 else if (tevp->enterptr == __setdel_call_misctf)
  {
   tfrp = tevp->tu.tetfrec;
   __cvsim_msg("tf_ set delay misctf call of %s in %s at %s\n",
    __get_tfcellnam(tfrp), __msg_cur_blditree(__xs, tfrp->tf_intskp),
    __bld_lineloc(__xs2, tfrp->tffnam_ind, tfrp->tflin_cnt));
  }
 else if (tevp->enterptr == __sync_call_misctf)
  {
   tfrp = tevp->tu.tetfrec;
   __cvsim_msg("tf_ #0 synchronize misctf call of %s in %s at %s\n",
    __get_tfcellnam(tfrp), __msg_cur_blditree(__xs, tfrp->tf_intskp),
    __bld_lineloc(__xs2, tfrp->tffnam_ind, tfrp->tflin_cnt));
  }
 else if (tevp->enterptr == __process_putpdel_ev)
  {
  tedp = tevp->tu.tedputp;
  tfrp = tedp->tedtfrp;
  __cvsim_msg("tf_ strdel putp assign to arg %d of %s in %s at %s\n",
   tedp->tedpnum, __get_tfcellnam(tfrp), __msg_cur_blditree(__xs,
   tfrp->tf_intskp), __bld_lineloc(__xs2, tfrp->tffnam_ind, tfrp->tflin_cnt));

  tfap = &(tfrp->tfargs[tedp->tedpnum]);
  if (tfap->anp->ntyp >= NONWIRE_ST) strcpy(__xs, "procedural assign of"); 
  else strcpy(__xs, "tf_ driver is"); 
  xp = tfap->arg.axp;
  wp = tedp->tedwp;
  lhslen = xp->szu.xclen;
  wlen = wlen_(lhslen);
  __cvsim_msg("       %s %s\n", __xs, __xregab_tostr(s1, wp,
   &(wp[wlen]), lhslen, xp));
  }
 else __case_terr(__FILE__, __LINE__);
 __last_tridp = sav_tridp; 
 restore_idp_();
}

/*
 * routine to fill table (known big enough) with future events
 * starts with next event must match event type to passed number
 *
 * puts in global table __wrkevtab index __last_wevti size __size_wrkevtab
 * this must skip current event
 */
static void fill_near_evtab(int32 ntevs, int32 tefilt)
{
 int32 evnum, twi, added_pnd0s;
 size_t osize;
 struct tev_t *tevp;
#ifdef __STREE__
 struct tqnode_t *sav_root_nodep;
 int32 save_free_node_ndx;
#else
 int32 save_free_heap_ndx;
#endif

 /* make sure work event table allocated and large enough */
 if (__wrkevtab == NULL)
  {
   __wrkevtab = (struct tev_t **) __my_malloc(ntevs*sizeof(struct tev_t *)); 
   __size_wrkevtab = ntevs;
  }
 else
  {
   if (ntevs > __size_wrkevtab)
    {
     osize = __size_wrkevtab*sizeof(struct tev_t *);
     __wrkevtab = (struct tev_t **) __my_realloc(__wrkevtab, osize,
      ntevs*sizeof(struct tev_t *)); 
     __size_wrkevtab = ntevs; 
    }
  }
 __last_wevti = -1;
 evnum = 0;

 /* first rest of current list */
 /* if not in pound 0's, first rest of current slot list */ 
 added_pnd0s = FALSE;
 if (!__processing_pnd0s)
  {
   /* if cur tevp index set, 1st pending event must be next */
   if (__cur_tevp != NULL) tevp = __cur_tevp->tenxtp;
   else tevp = __cur_te_hdrp;
   for (; tevp != NULL; tevp = tevp->tenxtp)
    {
     if (!try_add_wrkevtab(tevp, ntevs, &evnum, tefilt)) return;
    }
   /* add pnd0's or nb pnd0's if no pnd0s */
   if (__p0_te_hdrp != NULL) { tevp = __p0_te_hdrp; added_pnd0s = TRUE; }
   else tevp = __nb_te_hdrp;
  }
 else
  {
   /* SJM - also add nb's if no pound 0's */
   if (__cur_tevp != NULL) tevp = __cur_tevp->tenxtp;
   else if (__p0_te_hdrp != NULL) { added_pnd0s = TRUE; tevp = __p0_te_hdrp; }
   else tevp = __nb_te_hdrp;
  }
 /* next try pound 0's */
 for (; tevp != NULL; tevp = tevp->tenxtp)
  {
   if (!try_add_wrkevtab(tevp, ntevs, &evnum, tefilt)) return;

   /* if processing pnd0s and added pnd0's, must also add any nb pnd0s */
   /* before moving forward in time */
   if (tevp == NULL && added_pnd0s)
    {
     added_pnd0s = FALSE;
     tevp = __nb_te_hdrp;
    }
  }

#ifdef __STREE__
 if (__tree_root != SENTINEL)
  {
   /* need to save the root and the number of freed timing nodes */
   save_free_node_ndx = __free_node_ndx;
   sav_root_nodep = __tree_root;
   for (twi = 0; twi < ntevs; twi++)
    {
     /* get (pop) the next min time from the tree */
     tevp = __get_next_time_header();
     /* no more events break */
     if (tevp == NULL) break;
     for (; tevp != NULL; tevp = tevp->tenxtp)
      { if (!try_add_wrkevtab(tevp, ntevs, &evnum, tefilt)) return; }
    }
   /* restore the minimum events by placing them back into the tree */
   __restore_min_time_nodes(save_free_node_ndx); 
   /* set the root back to its original root */
   __tree_root = sav_root_nodep;
  }
#else
 /* go through timing heap to get up to ntev pending events */ 
 if (__heap_size > 1)
  {
   /* need to save the root and the number of freed timing nodes */
   save_free_heap_ndx = __free_heap_ndx;
   for (twi = 0; twi < ntevs; twi++)
    {
     /* get (pop) the next min time from the heap */
     tevp = __get_next_time_header();
     /* no more events break */
     if (tevp == NULL) break;
     for (; tevp != NULL; tevp = tevp->tenxtp)
      { if (!try_add_wrkevtab(tevp, ntevs, &evnum, tefilt)) return; }
    }
   /* restore the minimum events by placing them back into the heap */
   __restore_min_time_heap(save_free_heap_ndx); 
  }
#endif
}

/*
 * add to work ev tab if not elminated by filter
 * filter is threads only or all but thread
 * this return FALSE when table full
 */
static int32 try_add_wrkevtab(struct tev_t *tevp, int32 ntevs, int32 *evnum,
 int32 tefilt)
{
 if (tefilt != -1)
  {
   /* FIXME for new cg threads this looks wrong but maybe return T right */
   if (tefilt == TE_THRD)
    { if (tevp->enterptr != __process_thrd_ev) return(TRUE); }
   else if (tevp->enterptr == __process_thrd_ev) return(TRUE);
  }
 if (++(*evnum) > ntevs) return(FALSE);
 __wrkevtab[++__last_wevti] = tevp;
 return(TRUE);
}

/*
 * TASK THREAD DUMP ROUTINES
 */

extern void __dmp_all_thrds()
{
 __dmp_initalw_thrd_tree();
 __dmp_tskthrds();
}

extern void __dmp_tskthrds(void)
{
 int32 first_time = TRUE;
 struct mod_t *mdp;
 struct task_t *tskp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mtasks == NULL) continue;
   if (first_time) { __cv_msg("\n"); first_time = FALSE; }

   __cvsim_msg("Task threads in module %s:\n", mdp->msym->synam);
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {

     __dmp_tskthd(tskp, mdp);
    } 
  }
}

/*
 * dump 1 task thread
 */
extern void __dmp_tskthd(struct task_t *tskp, struct mod_t *mdp)
{
 int32 i;
 struct tskthrd_t *ttp;

 if (tskp->tsktyp == FUNCTION) 
  {
   if (tskp->tthrds != NULL) __misc_terr(__FILE__, __LINE__);
   return;
  }
 for (i = 0; i < mdp->flatinum; i++) 
  {
   if ((ttp = tskp->tthrds[i]) == NULL)
    {
     if (__debug_flg)
      __dbg_msg("*** task %s instance %d has no task threads\n", 
       tskp->tsksyp->synam, i);
     continue;
    }
   __cvsim_msg("*** dumping threads for task %s (%s)\n",
    tskp->tsksyp->synam, __msg_blditree(__xs, mdp->moditps[i],
    (struct task_t *) NULL));
   for (; ttp != NULL; ttp = ttp->tthd_r) __dmp_thrd_info(ttp->tthrd);
  }
}

/*
 * dump top level init/always thread tree
 */
extern void __dmp_initalw_thrd_tree(void)
{
 struct thread_t *thp;

 __cvsim_msg("Initial/always threads:\n");
 for (thp = __initalw_thrd_hdr; thp != NULL; thp = thp->thright)
  {
   if (thp->thdtevp == NULL && thp->th_dctp_tev_ofs == 0 && thp->thofscnt == 0)
    {
     __cvsim_msg("   initial/always thread enabled at %s completed\n",
      __bld_lineloc(__xs, thp->thenbl_sfnam_ind, thp->thenbl_slin_cnt));
     continue;
    }
   __dmp_thrd_info(thp);
   if (thp->thofs != NULL) __dmp_thrd_tree(thp->thofs); 
  }
 __cvsim_msg("  *** end of initial/always threads ***\n");
}

extern void __dmp_thrd_tree(struct thread_t *thp)
{
 for (; thp != NULL; thp = thp->thright)
  {
   __dmp_thrd_info(thp);
   if (thp->thofs != NULL) __dmp_thrd_tree(thp->thofs); 
  } 
}

extern void __dmp_thrd_info(struct thread_t *thp)
{
 struct tev_t *tevp;
 int32 dctp_tev_ndx;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 if (thp->thnxtstp == NULL) strcpy(s2, "**at end");
 else __bld_lineloc(s2, thp->thnxtstp->stfnam_ind, thp->thnxtstp->stlin_cnt);

 __cvsim_msg("   enabled %s statement %s in %s\n",
  __bld_lineloc(s1, thp->thenbl_sfnam_ind, thp->thenbl_slin_cnt), s2,
  __msg_idp_blditree(s3, thp->th_idp, thp->assoc_tsk));

 if ((tevp = thp->thdtevp) != NULL)
  {
   __cvsim_msg("   [%s event for time %s cancel=%d]\n",
    __to_tetyp(s1, tevp->enterptr), __to_timstr(s2, &(tevp->etime)),
     (tevp->enterptr == __process_cancel_ev_enterp));
  }
 /* AIV 10/19/07 - changed to int only needed for dctp_tev_ofs - no need */
 /* to save the dctp in the code with new idp scheme */
 if ((dctp_tev_ndx = thp->th_dctp_tev_ofs) != 0)
  {
   sprintf(s1, "dce with tev index %d", dctp_tev_ndx);
  } 
 else strcpy(s1, "not waiting for event ctrl");
 __cvsim_msg("   [has task outs=%d, disable=%d, fork=%d, %s]\n",
   thp->tsk_stouts, thp->th_dsable, thp->th_fj, s1);
}
