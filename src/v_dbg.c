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
 * debugger - interactive environment
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dlfcn.h> 
#include <stdarg.h>

#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h>
#endif

#ifndef __NOSIGS__
#include <signal.h>
#endif

#include <unistd.h>
#include <setjmp.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

#include "igen.h"

/* local prototypes */
static void rem_escape_newlines(char *);
static void snap_finish(void);
static void setup_interactive(void);
static void add_iahist(void);
static int32 get_iahcmdnum(void);
static void grow_iahtab(void);
static void rd_exec_iact_stmt(int32);
static void chk_iact_grefs(int32);
static void init_iahctrl(struct hctrl_t *);
static void init_sched_iathd(struct hctrl_t *);
static struct thread_t *bld_immed_iathrd(struct st_t *);
static void free_iact_glbs(struct gref_t *, int32);
static void renumber_1stmt(struct st_t *, int32, int32);
static void renumber_csitemlst(struct csitem_t *, int32, int32);
static void renumber_stlst(struct st_t *, int32, int32);
static int32 prt1_iahist_cmd(int32);
static void free_done_iact_control(struct hctrl_t *, int32);
static int32 do_dbg_cmd(void);
static int32 dbcmd_prefix_rep(int32, char *, int32, struct namlst_t *, int32);
static void do_dbg_help(void);
static void wr_dbg_hlpmsg(char **);
static void wr_dbg_lstofcmds(struct namlst_t *, int32);
static void dbg_print(void);
static char *dbg_bld_expr_val(char *, struct expr_t *, int32, int32, int32);
static void dbg_display(void);
static void prt_all_disp_exprs(void);
static char *bld_prtbasecode(char *, int32, int32, int32);
static void do_dbg_expris(void);
static char *bld_expr_telltale(char *, struct expr_t *);
static void do_dbg_varis(void);
static void print_iddecl_ref(struct sy_t *, struct sy_t *);
static void do_dbg_whatis(void);

/* extern prototypes (maybe defined in this module) */
extern void __write_not_triggered_events(void);
extern void __write_uncovered_stmts(void);
extern void __process_exit_tgl_output(void);
extern char *__my_malloc(size_t);
extern FILE *__tilde_fopen(char *, char *);
extern char *__pv_stralloc(char *);
extern struct task_t *__find_thrdtsk(struct thread_t *);
extern void __set_dbentry_listline(void);
extern void __call_misctfs_iact(void);
extern void __vpi_enteriact_trycall(void);
extern void __call_misctfs_scope(void);
extern void __vpi_iactscopechg_trycall(void);
extern int32 __rd_ialine(void);
extern void __my_fclose(FILE *);
extern void __call_misctfs_finish(void);
extern void __vpi_endsim_trycall(void);
extern void __get_vtok(void);
extern char *__msg_blditree(char *, struct itree_t *, struct task_t *);
extern char *__msg_idp_blditree(char *, t_midat *, struct task_t *);
extern char *__bld_lineloc(char *, word32, int32);
extern void __vpi_exitiact_trycall(void);
extern int32 __chk_extra_atend(int32);
extern char *__prt_vtok(void);
extern void __do_iact_disable(struct hctrl_t *, int32);
extern char *__to_timstr(char *, word64 *);
extern void __write_snapshot(int32);
extern void __my_ftime(time_t *, time_t *);
extern void __prt_end_msg(void);
extern void __add_infil(char *);
extern int32 __wide_vval_is0(word32 *, int32);
extern char *__regab_tostr(char *, word32 *, word32 *, int32, int32, int32);
extern char *__my_realloc(void *, size_t, size_t);
extern struct st_t *__rd_stmt(void);
extern void __chk_lstofsts(struct st_t *);
extern void __chk_nodel_lstofsts(struct st_t *);
extern struct st_t *__prep_lstofsts(struct st_t *, int32, int32);
extern void __free_1stmt(struct st_t *);
extern void __free_dceauxlst(struct dceauxlst_t *, int32);
extern void __free_dceauxs_only(struct dceauxlst_t *);
extern struct st_t *__brktr_exec_1stmt(struct st_t *, int32 *, int32);
extern void __my_free(void *, size_t);
extern void __ia_warn(int32, char *, ...);
extern char *__msg2_cur_blditree(char *);
extern struct thread_t *__alloc_thrd(void);
extern void __add_ev_to_front(struct tev_t *);
extern void __free_1glb_flds(struct gref_t *);
extern char *__get_eval_cstr(struct expr_t *, int32 *);
extern void __free_thd_list(struct thread_t *);
extern void __free_1thd(struct thread_t *);
extern int32 __get_dbcmdnum(char *, struct namlst_t *, int32);
extern char *__bld_ambiguous_list(char *, char *, struct namlst_t *, int32);
extern void __prt_where_msg(struct thread_t *);
extern void __do_dbg_list(void);
extern void __do_dbg_set(void);
extern void __do_dbg_info(void);
extern void __do_dbg_dis_enable(int32);
extern void __dbg_undisplay(void);
extern int32 __get_dbg_val(void);
extern void __do_dbg_history(void);
extern void __do_dbg_emptyhistory(void);
extern void __do_dbg_brkpt(int32);
extern void __do_dbg_ibrkpt(int32);
extern int32 __do_dbg_nextb(void);
extern void __do_dbg_delbrkdis(void);
extern void __do_dbg_scope(void);
extern void __dbg_brk_ignore(void);
extern void __dbg_brk_cond(void);
extern void __wrap_puts(char *, FILE *);
extern void __wrap_putc(int32, FILE *);
extern struct expr_t *__rd_iact_expr(void);
extern int32 __colto_eol(void);
extern void __free_xtree(struct expr_t *);
extern char *__strenexpr_tostr(char *, struct expr_t *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern int32 __trim1_0val(word32 *, int32);
extern char *__strab_tostr(char *, word32 *, int32, int32, int32);
extern char *__regab2_tostr(char *, word32 *, word32 *, int32, int32, int32, int32);
extern void __bld_xtree(int32);
extern int32 __chk_rhsexpr(struct expr_t *, int32);
extern int32 __bld_expnode(void);
extern void __set_xtab_errval(void);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern char *__to_opname(word32);
extern char *__to_sytyp(char *, word32);
extern char *__bld_showvars_prefix(char *, struct net_t *,
 struct gref_t *grp);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern int32 __do_vpi_stop(int32);
extern void __do_vpi_reset(int32, int32, int32);
extern void __emit_vpi_noiact_warn(void);
extern void __emit_vpi_iniact_warn(void);
extern void __emit_stsk_endmsg(void);
extern struct gref_t *__alloc_grtab(struct gref_t *, int32);
extern void __init_mod(struct mod_t *, struct sy_t *);
extern void __my_dv_flush(void);
extern void __wr_dvtimstr(void);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern void __free_dce_prevval(struct dcevnt_t *, int32, int32);
extern int32 __get_dcewid(struct dcevnt_t *, struct net_t *);
extern int32 __get_pcku_chars(int32, int32);
extern void __cleanup_dumpports(void); 
extern void __cleanup_dpi_interp_wrap_lib(void);

extern void __fst_close(void);

#ifdef __PROFILE__
extern void __dmp_iop_hist(void);
#endif

extern void __my_fprintf(FILE *, char *, ...);
extern void __cv_msg(char *, ...);
extern void __cvsim_msg(char *, ...);
extern void __cvsim2_msg(char *, ...);
extern void __cvsim3_msg(char *, ...);
extern void __pv_warn(int32, char *,...);
extern void __sgfwarn(int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __pv_terr(int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __my_exit(int32, int32);
extern void __ia_err(int32 id_num, char *s, ...);

extern void __process_thrd_ev(void);

extern const char __pv_ctab[];

/*
 * STARTUP SIGNAL INITIALIZATION ROUTINES
 */

/*
 * signal handler during compilation
 * should put in alarm here
 */
#ifndef __NOSIGS__
extern void __comp_sigint_handler(void)
{
 char s1[RECLEN];

 /* ignore ^c signal in here */ 
 signal(SIGINT, SIG_IGN);
 __cvsim2_msg(
  "\nInterrupt (^C) occurred during translate/load, really quit? (y/n) ");
 if (fgets(s1, RECLEN, stdin) == NULL) goto done;

 if (s1[0] == 'y' || s1[0] == 'Y')
  {
   /* put back called signal */
#if defined(INTSIGS)
   signal(SIGINT, __old_int_sig);
#else
   signal(SIGINT, (void (*)()) __old_int_sig);
#endif
   __pv_terr(311, "translate/load terminated by interrupt (^C) signal");
  }
done:
 /* why need to reset signal handler */
#if defined(INTSIGS)
 signal(SIGINT, __comp_sigint_handler);
#else
 signal(SIGINT, (void (*)()) __comp_sigint_handler);
#endif
     
 /* AIV 04/22/10 - if FST file open flush here */
 if (__fst_ctx != NULL) fstWriterFlushContext(__fst_ctx);
}
#endif

/*
 * signal during execution 
 * just set flag here - must be run to top level before catching
 *
 * all this does is set switch - caller must reset internal switch 
 * when processed or ignored
 */
#ifndef __NOSIGS__
extern void __sim_sigint_handler(void)
{
 char s1[RECLEN];

 /* SJM 07/31/01 - think need message to indicate interrupt */
 /* DBG remove -- */
 if (!__compiled_sim)
  __cvsim2_msg( "<INTERRUPT>\n");
 /* --- */
 __pending_enter_iact = TRUE;
 __iact_reason = IAER_CTRLC;
 /* if stepping, disable as if step completed */
 __single_step = FALSE; 
 __step_rep_cnt = 0;
 __step_lini = -1;
 __step_ifi = -1;

 /* AIV 08/11/09 - if using the compiler - just finish */
 if (__compiled_sim)
  {
   /* AIV 04/03/12 - added simulation time to print statement */
   __to_timstr(s1, &__simtime);
   __cvsim2_msg( "INTERRUPT - exiting compiled simulation at time %s.\n", s1);
   __my_exit(6, TRUE);
  }
}
#endif

/*
 * interface to (only way program quits) to reset callers signal handler
 *
 * normally do_exit true but to return to caller called with do exit F 
 */
extern void __my_exit(int32 rc, int32 do_exit)
{
 int32 i;

#ifndef __NOSIGS__
 /* put back entry signal */
#ifdef INTSIGS
   signal(SIGINT, __old_int_sig);
#else
   signal(SIGINT, (void (*)()) __old_int_sig);
#endif
#endif

 /* for antrim flush buffers */
 /* always flush here in case of $finish */
 if (__dv_fd != -1)
  {
   /* SJM 10/08/99 - need to write time at end for some wave form viewers */ 
   __wr_dvtimstr();
   __my_dv_flush();
  }
 __cleanup_dumpports();
 /* close fst file */
 if (__fst_ctx != NULL) __fst_close();

 /* dump coverage data */
 if (__run_state == SS_SIM)
  {
   /* event @ coverage */
   if (__event_coverage) __write_not_triggered_events();
   /* all statement coverage */
   if (__stmt_coverage) __write_uncovered_stmts();

   if (__toggle_coverage) __process_exit_tgl_output();
  }
 /* AIV 12/30/10 - if DPI interp wrapper - remove tmp files */
 if (__dpi_interp_wrapper_fnam != NULL)
  {
   __cleanup_dpi_interp_wrap_lib();
  }

#ifdef __XPROP__
 /* need to flush and close xprop trace file */
 if (__xprop_trace_fp != NULL) 
  {
   fflush(__xprop_trace_fp);
   __my_fclose(__xprop_trace_fp);
  }
#endif

 if (__log_s != NULL) fflush(__log_s);
 if (__tr_s != NULL) fflush(__tr_s);
 for (i = 0; i < 31; i++) 
  {
   if (__mulchan_tab[i].mc_s != NULL) fflush(__mulchan_tab[i].mc_s);
  }
#ifdef  __CVC_DEBUG__
 #ifndef __STREE__
 if (__verbose)
  {
   __my_fprintf(stdout, "Scheduled time hash collision count %d\n",
     __collision_count);
  }
 #endif
#endif
 if (do_exit) exit(rc);
 return;
}

/*
 * INTERACTIVE SETUP ROUTINES
 */

/*
 * initialize interactive environment just before simulation begins
 * but after all initialization wire evaluation finished
 *
 * since various interactive system tasks can appear in normal source
 * this initializes those things - when interactive called real init done
 * notice this is run with __iact_state off
 */
extern void __init_interactive(void)
{ 
 int32 i;
 struct sy_t *syp;

 /* set up listing file - nothing open and no line pos. file cached */
 __filpostab = NULL;
 __list_cur_fd = -1;
 /* use can change this with :set - number is one less than no. to list */
 /* since prt src lines is from - to */ 
 __list_cur_listnum = 9;
 /* start at 1st top level */
 /* force setting on first :l command */
 __list_cur_ifi = -1;
 __nxt_bpnum = 1; 
 __bphdr = NULL;
 __dispxhdr = NULL;
 __nxt_dispxnum = 1;
 __single_step = FALSE;
 __step_rep_cnt = 0;
 __step_from_thread = FALSE;
 __step_match_idp = NULL;
 __step_lini = -1;
 __step_ifi = -1;
 __verbose_step = FALSE;
 __last_iasytp = NULL;

 __last_stepidp = NULL;
 __last_steptskp = NULL;
 __last_stepifi = -1;
 __last_brktime = 0xffffffffffffffffULL;

 /* $scope start at first top level module - no old scope to push */
 __scope_idp = __it_roots[0]->it_idp;
 __scope_tskp = NULL;

 /* allocate interactive module - re-initialized each time iact entered */
 /* 08/18/99 - for now only expr tab and glb tab fields used */
 __iact_mdp = (struct mod_t *) __my_malloc(sizeof(struct mod_t)); 

 syp = (struct sy_t *) __my_malloc(sizeof(struct sy_t));
 syp->synam = __pv_stralloc("**IACT WORK**");
 syp->sydecl = TRUE;

 __init_mod(__iact_mdp, syp);
 __iact_mdp->flatinum = 1;
 syp->el.emdp = __iact_mdp;

 /* default is now, use scope of entry in interactive, :set to use old */ 
 __iact_scope_chg = TRUE; 
 __dbg_dflt_base = BHEX;

 /* notice line count and :list command line are unrelated - line count is */
 /* source line number or command history number */
 __lin_cnt = 1;
 /* this forces getc to read from read interactive line */
 __in_s = NULL;
 __file_just_op = FALSE;
 __first_linetok = FALSE; 
 __cmd_fnam = NULL;
 __cmd_s = NULL;

 /* special code in get_env_sym so no environment here */
 __venviron[0] = NULL;
 
 /* LOOKATME - should read .[cverdbinit?] with history off */
 __iahwrklen = 2*IDLEN + 8;
 __iahwrkline = __my_malloc(__iahwrklen);
 __hist_cur_listnum = 20;
 __echo_iactcmds_tolog = TRUE;

 /* setup history */
 /* FIXME - need to wrap table not continue growing without limit */
 __iahsiz = IAHISTSIZ;
 __iahtab = (struct iahist_t *) __my_malloc(__iahsiz*sizeof(struct iahist_t));
 /* must start with 0 since first add moves to real 1 start */
 __iah_lasti = 0;
 /* indexed from 1 but initialize from 0 */
 for (i = 0; i < __iahsiz; i++)
  { __iahtab[i].iah_lp = NULL; __iahtab[i].iah_hcp = NULL; }
 __hctrl_hd =__hctrl_end = NULL;
}

/*
 * INTERACTIVE DEBUGGER ROUTINES
 */

/*
 * execute the interactive control loop
 *
 * unless -<num> or <num> form or not history on put into history list
 * only break (ctrl-c), $stop, or -s command option tranfer control to here
 * continue (.) does not return here unless ctrl-c or $stop() execed
 * when events exhausted looks like $finish hit
 * commands executed from here return to here
 *
 * debugger commands are not added to the history list 
 * this runs with ctrl-c (int32) disabled
 * upon entry, interrupt signal is SIGIGN
 * also no current thread - run between processed events
 * if entry from interactive non immediate $stop, no scope or file change
 */
extern void __do_interactive_loop(void)
{
 int32 histcmd_num, hist_rexec, rv, sav_lin_cnt, sav_cur_fnam_ind;
 int32 chg_scope, still_stepping;
 FILE *sav_cmd_s, *f;
 char *sav_cmd_fnam;
 struct iahist_t *iahp;
 struct task_t *tskp;
 struct sy_t *syp;
 char s1[RECLEN], s2[RECLEN];
 struct itree_t *itp;
 decl_idp_locals_;

 /* where call finish callbacks and exit when interactive turned off */
#ifndef __NOSIGS__
 signal(SIGINT, SIG_IGN);
#else
 /* algorithm for Antrim signal removal is enter intractive loop */
 /* handler returns with longjmp before exit */
 __call_misctfs_finish();
 if (__have_vpi_actions) __vpi_endsim_trycall();
 __my_exit(0, TRUE);
#endif

 /* things needed on any entry to interactive */
 /* if interactive mode off, just finish */
 __iact_state = TRUE;
 __pending_enter_iact = FALSE;
 if (__no_iact) snap_finish();
 /* if first time do some setup - not done after :reset or $reset */ 
 if (!__iasetup)
  {
   setup_interactive(); 
   __iasetup = TRUE;
   __cvsim2_msg("Type :help for help\n");
  }
 if (!__ia_entered)
  {
   if (__cmd_start_fnam != NULL)
    {
     /* this was opened once to check but may be problem since then */
     if ((f = __tilde_fopen(__cmd_start_fnam, "r")) == NULL)
      {
       __pv_warn(505, 
        "now cannot open -i startup interactive input file %s - using stdin",
        __cmd_start_fnam);
      }
     else
      {
       __cmd_s = f;
       __cmd_fnam = __pv_stralloc(__cmd_start_fnam);
      }  
    }
   __ia_entered = TRUE;
  }
 hist_rexec = FALSE;
 sav_cmd_s = NULL;
 sav_cmd_fnam = NULL; 
 sav_cur_fnam_ind = -1;
 sav_lin_cnt = -1;

 /* for entry from iact ($stop?), use original scope of interactive */
 /* unless turned off or sim not started, use entry proc. scope as scope */
 if (__iact_scope_chg && __suspended_thd != NULL)
  {
   /* scheme if that is last thread (pending) was in task move to task */
   /* if enterered from ^c but evaling event, may want scope change */
   if (__fcspi >= 0) tskp = __fcstk[__fcspi];
   else if (__suspended_thd->th_fj) tskp = __find_thrdtsk(__suspended_thd);
   else tskp = __suspended_thd->assoc_tsk;
   /* this pushes scope since iact flag on */
   __scope_idp = __suspended_idp;
   __scope_tskp = tskp;
   chg_scope = TRUE;
  }
 else chg_scope = FALSE;
 /* whenever enter iact, must push scope (needs to be in inst. ptr) */ 
 set_save_idp_(__scope_idp);

 /* notice list line and scope now unrelated - but always can set from */
 /* suspended thread next statement */
 __set_dbentry_listline();

 /* if stepping repeat count, decrement and continue execing */ 
 still_stepping = FALSE;
 if (__iact_reason == IAER_STEP && --__step_rep_cnt > 0)
  {
   /* save moved to line but continue stepping */
   __single_step = TRUE;
   __verbose_step = TRUE;
   if (__suspended_thd == NULL || __suspended_thd->thnxtstp == NULL)
    __step_from_thread = FALSE;
   still_stepping = TRUE;
   goto do_ret;
  }
 if (__tfrec_hdr != NULL) __call_misctfs_iact();
 if (__have_vpi_actions) __vpi_enteriact_trycall();

 if (chg_scope)
  {
   if (__tfrec_hdr != NULL) __call_misctfs_scope();
   if (__have_vpi_actions) __vpi_iactscopechg_trycall();
  }
 /* process and pending display commands */
 if (__dispxhdr != NULL) prt_all_disp_exprs();

again:
 /* hist rexec requires command and line no. from history - put back here */ 
 /* re-execed history and now re-entering debugger so must change */
 /* to input line world */
 if (hist_rexec)
  {
   __cmd_s = sav_cmd_s;
   __cmd_fnam = sav_cmd_fnam; 
   __cur_fnam_ind  = sav_cur_fnam_ind;
   __cur_fnam = __in_fils[__cur_fnam_ind];
   __lin_cnt = sav_lin_cnt;
   hist_rexec = FALSE;
  }

 /* write prompt if to screen if needed and/or to log file if exists */ 
 /* here need to use next history location even though net yet filled */
 if (__cmd_s == NULL && isatty(fileno(stdin)))
  __cvsim2_msg("C%d > ", __iah_lasti + 1); 
 /* LOOKATME - log file output only because typed in from terminal */
 if (__echo_iactcmds_tolog && __log_s != NULL) 
  __cvsim3_msg("C%d > ", __iah_lasti + 1); 

 /* first read the entire command (possible multiple \[new line] lines */
 /* notice only $finish gets out of this loop */
 if (__vin_top > 0) __misc_terr(__FILE__, __LINE__);
 rv =__rd_ialine();
 if (rv == TEOF)
  {
   if (__cmd_s != NULL)
    {
     /* LOOKATME - think this is unneeded */
     clearerr(__cmd_s);
     __my_fclose(__cmd_s);
     __cmd_s = NULL;
     __cmd_fnam = NULL;
     __cur_fnam = __in_fils[1];
     __cur_fnam_ind = __cmd_ifi;
     /* after close file must emit prompt */
    }
   else
    {
     if (isatty(fileno(stdin))) 
      {
       __ia_err(1403,
        "EOF (^D or ^C) read from tty stdin - use :q or $finish; to exit program");
       clearerr(stdin); 
       goto again;
      }
     /* cver run from batch file - on eof of stdin execute $finish */
     __ia_err(1406,
      "EOF on non tty stdin (simulation run from script) - $finish executed");
     if (__tfrec_hdr != NULL) __call_misctfs_finish();
     if (__have_vpi_actions) __vpi_endsim_trycall();
     __my_exit(2, TRUE);
    }
  }
 /* if no $input (or -i) file, line is command number */
 if (__cmd_s == NULL) __lin_cnt = __iah_lasti;
num_reenable:
 __visp->vichp = __iahwrkline;
 /* since keywords ok in interactive, set beginning of line */
 __first_num_eol = TRUE;

 /* this is command parsing that requires tokenization */
 __get_vtok(); 
 if (__toktyp == TEOF) goto again;

 switch (__toktyp) {
  case TEOF: __case_terr(__FILE__, __LINE__); break; 
  case COLON:
   __get_vtok();
   if (__toktyp == TEOF) 
    {
     if (__scope_tskp != NULL) syp = __scope_tskp->tsksyp; 
     else 
      {
       itp = (struct itree_t *) __scope_idp[MD_ITP];
       syp = itp->itip->imsym;
      }
     __cvsim_msg("scope: %s (at %s and :list at %s)\n",
      __msg_idp_blditree(__xs, __scope_idp, __scope_tskp),
      __bld_lineloc(s1, syp->syfnam_ind, syp->sylin_cnt),
      __bld_lineloc(s2, (word32) __list_cur_ifi, __list_arg_lini));
     goto again;
    }
   /* : debugger commands always go on history list unless hist re-exec */
   if (__history_on && !hist_rexec) add_iahist();
   /* implement : [debugger command] - handles errors */
   if (!do_dbg_cmd())
    {
     /* if debug command some kind of step, if rexeced restore iact loc. */
     if (hist_rexec)
      {
       __cmd_s = sav_cmd_s;
       __cmd_fnam = sav_cmd_fnam; 
       __cur_fnam_ind  = sav_cur_fnam_ind;
       __cur_fnam = __in_fils[__cur_fnam_ind];
       __lin_cnt = sav_lin_cnt;
       hist_rexec = FALSE;
      }
     /* here even if re-exec dot, still treat as new step */ 
     __step_lini = -1;
     __step_ifi = -1;
     goto do_ret;
    }
   else goto again;
  case DOT:
   __step_lini = -1;
   __step_ifi = -1;
do_ret:
   if (!still_stepping && __have_vpi_actions) __vpi_exitiact_trycall();

   __iact_state = FALSE;
   /* if ^c hit in interactive debugger, unless command handles just ignore */ 
   /* this is needed to stop, from immediate statement dbg enter */
   /* on entry always push a scope, but must pop away before running again */
   restore_idp_();
  /* need to enable sim sigint32 handler since turned off in iact loop */
#ifndef __NOSIGS__
#if defined(INTSIGS)
   signal(SIGINT, __sim_sigint_handler);
#else
   signal(SIGINT, (void (*)()) __sim_sigint_handler);
#endif
#endif
   __pending_enter_iact = FALSE;
   __iact_reason = IAER_UNKN;
   return;
  case SEMI:
   /* ; statement step with no trace */  
step_setup:
   __single_step = TRUE;
   __step_rep_cnt = 1;
   if (__iact_reason == IAER_CTRLC || __suspended_thd == NULL
    || __suspended_thd->thnxtstp == NULL) __step_from_thread = FALSE;
   __chk_extra_atend(TRUE);
   goto do_ret;
  case COMMA:
   /* , statement step with debugger trace */
   /* notice -t tracing additional and independent */
   __verbose_step = TRUE;
   goto step_setup;
  case MINUS:
   __get_vtok();
   if (__toktyp != NUMBER)
    {
     __ia_err(1410, "minus disable command number expected: %s read",
      __prt_vtok());
     goto again;
    }
   /* this emits own error */
   if ((histcmd_num = get_iahcmdnum()) == -1) goto again;

   iahp = &(__iahtab[histcmd_num]);
   if (iahp->iah_hcp == NULL)
    {
     __ia_err(1412, "-%d disable failed: command already completed",
      histcmd_num);
     goto again;
    }
   /* disable the command and free control record */
   __do_iact_disable(iahp->iah_hcp, FALSE);
   goto again;
  case NUMBER:
   /* this emits own error */
   if ((histcmd_num = get_iahcmdnum()) == -1) goto again;
   /* since need eventual history support, free if needed and reparse */
   if (__iahtab[histcmd_num].iah_hcp != NULL)
    {
     __ia_err(1416, "attempt to re-execute C%d failed: command not completed",
      histcmd_num);
     goto again;
    }
   /* must copy since can edit new and new probably goes in history */
   strcpy(__iahwrkline, __iahtab[histcmd_num].iah_lp);
   rem_escape_newlines(__iahwrkline);
   /* save all line loc. state and set to history command no. */
   sav_cmd_s = __cmd_s;
   __cmd_s = NULL;
   sav_cmd_fnam = __cmd_fnam;
   __cmd_fnam = NULL;
   sav_cur_fnam_ind = __cur_fnam_ind;
   __cur_fnam_ind = __cmd_ifi;
   __cur_fnam = __in_fils[1];
   sav_lin_cnt = __lin_cnt; 
   __lin_cnt = histcmd_num;
   hist_rexec = TRUE;
   goto num_reenable;
  default:
   /* schedule non immediate but never leave debugger from Verilog cmd */
   rd_exec_iact_stmt(hist_rexec);
   goto again;
 }
}

/*
 * when reparsing from history list must remove all escaped new lines
 * since need to emit error message with only loc. history
 */
static void rem_escape_newlines(char *lp)
{
 for (; *lp != '\0'; lp++)
  {
   if (*lp == '\\') { if (lp[1] == '\n') { *lp = ' '; lp[1] = ' '; lp++; } }
  }
}

/*
 * emit error if extra characters at end of line
 * return F if more on line
 */
extern int32 __chk_extra_atend(int32 emit_err)
{
 char *chp; 

 chp = __visp->vichp;
 while (vis_white_(*chp)) chp++;
 if (*chp != '\0')
  {
   if (emit_err)
    {
     __ia_err(1413,
      "interactive command extra characters [%s] at end discarded", chp);
    }
   return(FALSE);
  }
 return(TRUE);
} 

/*
 * routine to write snapshot and quit on interrupt for debugging
 * notice may not be scope when this called
 */
static void snap_finish(void)
{
 char s1[RECLEN];

 __call_misctfs_finish();
 if (__have_vpi_actions) __vpi_endsim_trycall();

 /* return from interrupt signal handler */
 __cvsim_msg(
  "\nSimulation terminated by interrupt (^C) now %s (interactive debugger disabled)\n",
  __to_timstr(s1, &__simtime));
 if (__intsig_prt_snapshot)
  {
   /* DBG FIXME - for now just using large number */
   if (__debug_flg) __write_snapshot(1000);
   else __write_snapshot(DFLT_SNAP_EVS);
  }

 if (__verbose)
  {
   __my_ftime(&__end_time, &__end_mstime);
   __prt_end_msg();
  } 
 __my_exit(0, TRUE);
}

/*
 * setup the interactive loop - called first time interactive started only
 * once setup just leave special interactive file on visp stack
 */
static void setup_interactive(void)
{
 /* input looks like reading from macro that is read ia line */
 /* this justs stays present during simulation */
 __visp = __vinstk[__vin_top];
 __visp->vilin_cnt = 0;
 __visp->vifnam_ind = __cmd_ifi;
 __visp->vi_s = NULL;
 /* this is set after each line is read */
 __visp->vichp = NULL;

 if (__cmd_s == NULL)
  {
   /* file is stdin */
   __cur_fnam = __in_fils[1];
   __cur_fnam_ind = __cmd_ifi;
   /* line count will be set to command no. each time */
   __lin_cnt = 0;
  }
 else
  { 
   /* start reading from -i interactive file */
   __add_infil(__cmd_fnam);
   __cur_fnam_ind = __last_inf;
   __cmd_fnam = __in_fils[__cur_fnam_ind];
   __lin_cnt = 0;
  }
 __lasttoktyp = UNDEF;
 return;

 /* -- FIXME - ADD KEY (for now no key file)
 -* first entry to interactive - open key file if possible *-
 if (__key_fnam != NULL)
  {
   if ((__key_s = __tilde_fopen(__key_fnam, "w")) == NULL)
    {
     __ia_err(1414,
      "cannot open -k interactive input key file %s - trying default",
      __key_fnam);
     __my_free(__key_fnam, strlen(__key_fnam) + 1);
     __key_fnam = NULL;
     goto no_explicit;
    }
   return;
  }

no_explicit:
 if ((__key_s = __tilde_fopen(DFLTKEYFNAM, "w")) == NULL)
  {
   __ia_err(1415, "cannot open default key file %s - no key file",
    DFLTKEYFNAM);
   return;
  }
 __key_fnam = __my_malloc(strlen(DFLTKEYFNAM) + 1);
 strcpy(__key_fnam, DFLTKEYFNAM);
 --- */
}

/*
 * add a new entry to history queue - even if error entry must
 * go in queue so can be edited
 * this must be called after command read
 *
 * FIXME - ksh style editing not yet implemented
 */
static void add_iahist(void)
{
 struct iahist_t *iahp;

 if (++__iah_lasti >= __iahsiz) grow_iahtab();
 iahp = &(__iahtab[__iah_lasti]);
 iahp->iah_lp = __pv_stralloc(__iahwrkline);
 iahp->iah_hcp = NULL;
 iahp->iah_iti = NULL;
}

/*
 * check command number - message and F returned on error
 * cannot use nd_ndxnum because no IS forms here and just need value
 * notice both iahtab and command number start at 1 (0 unused)
 */
static int32 get_iahcmdnum(void)
{
 int32 base, cno;

 if (__itoklen > WBITS)
  {
   if (!vval_is0_(&(__acwrk[1]), __itoklen - WBITS)
    || !vval_is0_(__bcwrk, __itoklen))
    {
     base = BHEX;
prt_err:
     __ia_err(1418, "command history number %s invalid or out of range",
      __regab_tostr(__xs, __acwrk, __bcwrk, __itoklen, base, FALSE)); 
     return(-1);
    }
  }
 else
  {
    if (!vval_is0_(__bcwrk, __itoklen)) { base = BHEX; goto prt_err; } 
  }
 cno = (int32) __acwrk[0];
 if (cno < 1 || cno - 1 > __iah_lasti) { base = BDEC; goto prt_err; }
 return(cno);
}

/*
 * grow the interactive history table - no freeing and wrap for now
 */
static void grow_iahtab(void)
{
 int32 i;
 size_t old_iahsiz, osize, nsize;

 old_iahsiz = __iahsiz;
 osize = old_iahsiz*sizeof(struct iahist_t);
 __iahsiz = (3*__iahsiz)/2; 
 nsize = __iahsiz*sizeof(struct iahist_t);
 __iahtab = (struct iahist_t *) __my_realloc(__iahtab, osize, nsize);
 for (i = old_iahsiz; i < __iahsiz; i++)
  { __iahtab[i].iah_lp = NULL; __iahtab[i].iah_hcp = NULL; }
}
/*
 * ROUTINES TO IMPLMENT VERILOG STATEMENT EXECUTION DEBUGGER
 */

/* special external for setjmp environment - only used in v_ms.c */
jmp_buf __iact_jmpbuf;
jmp_buf __reset_jmpbuf;

/*
 * read and execute a Verilog interactive statement
 * errors here go into total but maybe should not
 *
 * must execute statement with delay as named block with no vars
 */
static void rd_exec_iact_stmt(int32 hist_rexec)
{
 int32 sav_err_cnt, sav_sfnam_ind, sav_slin_cnt, immed_exec;
 int32 sav_itspi, sav_st_trace, sfnind, slcnt, first_stmt, dowhile;
 struct st_t *stp, *stp2, *stp3;
 struct iahist_t *iahp;
 struct hctrl_t *hcp;
 struct mod_t *cur_mdp;

 /* free any globals from immediate exec unless monitor/strobe sys task */
 __iact_can_free = TRUE;
 cur_mdp = get_inst_mod_();

 /* DBG remove -- */
 if (__iact_dcehdr != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 sav_sfnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt;
 __sfnam_ind = __cur_fnam_ind;
 __slin_cnt = __lin_cnt;
 sav_err_cnt = __pv_err_cnt;

 /* on setup returns 0, if get here from call to long jump, all done */
 if (setjmp(__iact_jmpbuf) != 0)
  {
   /* get here only on error - must skip and read token or macro vinstk */
   /* will not be popped back to 0 */
   for (;;) { if (__toktyp == TEOF) break; __get_vtok(); }
   /* possible that parse error occured with something pushed back */
   __lasttoktyp = UNDEF;
   /* LOOKATME - may be minor memory leak for compound stmt with errors */
   goto free_ds;
  }
 __iact_stmt_err = FALSE;
 first_stmt = TRUE;
more_stmts:
 /* if error almost certainly with go to setdump code */
 /* unless undeclared problem */
 if ((stp = __rd_stmt()) == NULL) { __iact_stmt_err = TRUE; goto free_ds; }
 
 if (__pv_err_cnt != sav_err_cnt)
  { __iact_stmt_err = TRUE; goto free_stmts_done; }

 /* since know syntax good errors here, do not return */
 __cur_tsk = NULL;
 __iact_must_sched = FALSE;
 __chk_lstofsts(stp);
 if (__pv_err_cnt != sav_err_cnt)
  { __iact_stmt_err = TRUE; goto free_stmts_done; }
 __nbsti = -1;
 __task_has_delay = FALSE;
 __task_has_tskcall = FALSE;
 /* $stop or any loop in interactive requires scheduling */
 __chk_nodel_lstofsts(stp);
 if (__pv_err_cnt != sav_err_cnt)
  { __iact_stmt_err = TRUE; goto free_stmts_done; }
 if (__task_has_delay || __task_has_tskcall || __iact_must_sched)
  immed_exec = FALSE;
 else immed_exec = TRUE;

 /* notice always re-execing from history in current scope */
 /* so to reenable an edge or change breakpoint user must insure either */
 /* uses rooted names or scope is set to right place */  
 /* check and emit warning for non rooted interactive globals if from */
 /* history re-exec since no way to tell if from same itree loc. */
 chk_iact_grefs(hist_rexec);

 /* delay times are tfmt time units not time unit from current scope */
 __sav_mtime_units = cur_mdp->mtime_units;
 cur_mdp->mtime_units = __tfmt_units;
 /* rest of fields used from curr scope itree location */ 
 __prpsti = 0;
 __nbsti = -1;
 __prpstk[0] = NULL;
 __iact_dcehdr = NULL;
 /* AIV 03/05/09 - need to push mod here for __inst_mod may need to be set */
 __push_wrkitstk(cur_mdp, 0);
 stp = __prep_lstofsts(stp, FALSE, FALSE);
 __pop_wrkitstk();
 
 if (__pv_err_cnt != sav_err_cnt)
  {
   __iact_stmt_err = TRUE;
free_stmts_done:
   /* interactive always exactly 1 inst. */
   if (__iact_can_free)
    {
     for (stp2 = stp; stp2 != NULL;)
      { stp3 = stp2->stnxt; __free_1stmt(stp2); stp2 = stp3; }
    }
free_ds:
   /* SJM 01/02/03 - since never gening iops for interactive - ok because */
   /* only get here on error */
   if (__iact_can_free && __iact_dcehdr != NULL)
    {
     __free_dceauxlst(__iact_dcehdr, 1);
     __iact_dcehdr = NULL;
    }

   if (__grwrknum > 0)
    {
     int32 gri;
     size_t osize, nsize;
     struct gref_t *grp; 

     /* for monitor/strobe must add globals to iact mod table */
     if (__iact_can_free)
      {
       grp = &(__grwrktab[0]); 
       for (gri = 0; gri < __grwrknum; gri++, grp++) __free_1glb_flds(grp); 
      }
     else
      {
       /* need to copy grefs to iact module gr table so when interactive */
       /* scheduled statement executes can access grefs */
       if (__iact_mdp->mgrnum == 0)  
        {
         __iact_mdp->mgrtab = (struct gref_t *)
           __my_malloc(__grwrknum*sizeof(struct gref_t));
         memcpy(__iact_mdp->mgrtab, __grwrktab,
          __grwrknum*sizeof(struct gref_t));
        }
       else
        {
         osize = __iact_mdp->mgrnum*sizeof(struct gref_t);
         nsize = (__iact_mdp->mgrnum + __grwrknum)*sizeof(struct gref_t);
         __iact_mdp->mgrtab = (struct gref_t *)
          __my_realloc(cur_mdp->mgrtab, osize, nsize);

         memcpy(&(__iact_mdp->mgrtab[__iact_mdp->mgrnum]), __grwrktab,
          __grwrknum*sizeof(struct gref_t));
        } 
       __iact_mdp->mgrnum += __grwrknum;
       /* then fix up expr ptrs for all */
       grp = &(__iact_mdp->mgrtab[0]);
       for (gri = 0; gri < __iact_mdp->mgrnum; gri++, grp++)
        { grp->gxndp->ru.grp = grp; }
      }
     __grwrknum = 0;
    }
   goto done;
  }

 if (immed_exec)
  {
   /* DBG remove -- */
   if (__iact_dcehdr != NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */

   if (__history_on && !hist_rexec && first_stmt) add_iahist();
   /* in case exit with ^c (infinite loop?) restore entry itree loc. */
   sav_itspi = __itspi;
   /* must never trace immediate debugger commands */
   sav_st_trace = __st_tracing; 
   __st_tracing = FALSE;
   /* notice normally no thread while in interactive mode */
   __cur_thd = bld_immed_iathrd(stp);
   __cur_thd->th_idp = __scope_idp;
   __idp = __scope_idp;
   for (;;)
    {
     dowhile = -1;
     stp = __brktr_exec_1stmt(stp, &dowhile, FALSE);
     if (stp == NULL) break;
     if (__pending_enter_iact)  
      {
       __cvsim2_msg(
        "\nInterrupt (^C) during immediate interactive execution, reenter debugger? (y/n) ");
       if (fgets(__xs, RECLEN, stdin) != NULL
        && (__xs[0] == 'y' || __xs[0] == 'Y'))
        {
         __pending_enter_iact = FALSE;
         /* may be executing xmr func. when ^c hit */
         __itspi = sav_itspi;
         break; 
        }
      }
    }
   __st_tracing = sav_st_trace; 
   /* DBG remove --- */
   if (__cur_thd == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---*/
   /* notice thread just used as dummy place holder so nothing used */
   __my_free(__cur_thd, sizeof(struct thread_t)); 
   __cur_thd = NULL;
   goto free_stmts_done;
  }

 /* build and link on to history list the ia statement */
 hcp = (struct hctrl_t *) __my_malloc(sizeof(struct hctrl_t));
 init_iahctrl(hcp);

 sfnind = __cmd_ifi;
 if (hist_rexec)
  {
   iahp = &(__iahtab[__lin_cnt]);
   hcp->hc_lini = __lin_cnt;
   iahp->iah_hcp = hcp;
   hcp->hc_ifi = __cmd_ifi;
   hcp->hc_iahp = iahp;
   slcnt = __lin_cnt;
  } 
 else if (__history_on)
  {
   add_iahist();
   iahp = &(__iahtab[__iah_lasti]);
   hcp->hc_lini = __iah_lasti;
   iahp->iah_hcp = hcp;
   hcp->hc_ifi = __cmd_ifi;
   hcp->hc_iahp = iahp;
   slcnt = __iah_lasti;
  }
 else slcnt = 1; 

 /* always put on end of doubly linked list */
 renumber_1stmt(stp, sfnind, slcnt);

 hcp->hc_stp = stp;
 hcp->hc_idp = __scope_idp;
 if (__hctrl_hd == NULL) __hctrl_hd = __hctrl_end = hcp;
 else
  { 
   __hctrl_end->hc_nxt = hcp;
   hcp->hc_prev = __hctrl_end;
   __hctrl_end = hcp;
  }
 hcp->hc_dcelst = __iact_dcehdr;   
 __iact_dcehdr = NULL;

 /* allocate new gref table for later use if command in history list execed */ 
 /* only freed if statement removed from history list */
 if (__grwrknum > 0)
  {
   hcp->hc_grtab = __alloc_grtab(__grwrktab, __grwrknum);
   hcp->hc_numglbs = __grwrknum;
   __grwrknum = 0;
  }

 init_sched_iathd(hcp);

done:;
 if (!__iact_stmt_err && !__chk_extra_atend(FALSE))
  {
   first_stmt = FALSE;
   __get_vtok(); 
   /* DBG remove --- */
   if (__toktyp == TEOF) __misc_terr(__FILE__, __LINE__);
   /* --- */
   goto more_stmts;
  }
 /* only way to exit exec iact stmt routine */
 cur_mdp->mtime_units = __sav_mtime_units;
 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * check all xmr's from this statement
 */
static void chk_iact_grefs(int32 hist_rexec)
{
 int32 gri;
 struct gref_t *grp;

 grp = &(__grwrktab[0]);
 for (gri = 0; gri < __grwrknum; gri++, grp++)
  {
   if (grp->gr_gone || grp->gr_err) continue;
   if (hist_rexec)
    {
     if (!grp->is_rooted)
      {
       __ia_warn(1601,
        "statement has non rooted global %s - scope instance %s may differ from original",
        grp->gnam, __msg2_cur_blditree(__xs));
      }
    }
  }
}

/*
 * initialize an history suspended statement record 
 */
static void init_iahctrl(struct hctrl_t *hcp)
{
 hcp->hc_stp = NULL;
 hcp->hc_thp = NULL;
 hcp->hc_idp = NULL;
 hcp->hc_lini = 0;
 hcp->hc_ifi = 0;
 hcp->hc_nxt = hcp->hc_prev = NULL;
 hcp->hc_iahp = NULL;
 hcp->hc_dcelst = NULL;
 hcp->hc_grtab = NULL;
 hcp->hc_numglbs = 0;
}

/*
 * build the interactive statement thread and schedule event
 * this runs in current interactive scope itp
 * when finishes just terminates like any other thread - maybe in 0 time
 */
static void init_sched_iathd(struct hctrl_t *hcp)
{
 struct thread_t *thp;
 struct tev_t *tevp;
 
 /* allocate thread and event and fill links */
 alloc_tev_(tevp, __process_thrd_ev, hcp->hc_idp, __simtime);
 thp = __alloc_thrd();
 thp->th_hctrl = hcp;
 thp->thdtevp = tevp;
 thp->thenbl_sfnam_ind = __cmd_ifi;
 thp->thenbl_slin_cnt = __iah_lasti;
 thp->th_idp = hcp->hc_idp;
 tevp->tu.tethrd = thp;
 thp->thnxtstp = hcp->hc_stp;
 thp->thpar = NULL;
 hcp->hc_thp = thp; 

 /* here can just add to front of event list - best to get started */ 
 /* LOOKATME - notice no longer need to add to front - just more coherent */
 __add_ev_to_front(tevp);
}

/*
 * for immediate exec, allocate and set dummy current thread
 */
static struct thread_t *bld_immed_iathrd(struct st_t *stp)
{
 struct thread_t *thp;

 thp = __alloc_thrd();
 thp->thenbl_sfnam_ind = __cmd_ifi;
 thp->thenbl_slin_cnt = __iah_lasti;
 thp->thnxtstp = stp; 
 thp->thpar = NULL;
 return(thp);
}

/*
 * free iact globals
 * notice caller sets iact gref table to empty
 */
static void free_iact_glbs(struct gref_t *grtab, int32 grnum)
{
 int32 gri;
 struct gref_t *grp; 
 
 for (gri = 0, grp = &(grtab[0]); gri < grnum; gri++, grp++)
  { __free_1glb_flds(grp); }
 __my_free(grtab, grnum*sizeof(struct gref_t));
}

/*
 * free a list dce's (for monit/fmonit, qcaf and tf_ parameter change)
 * if compiled sim on and no syntax error, nd regen T else F
 * only called when free interactive dce list vpi_ call back lists
 *
 * caller may need to set header to nil
 * this works (does nothing) if called with nil dcehdr 
 * LOOKATME - if doubly linked would be faster
 *
 * SJM 06/21/02 - now only PLI and reset call this to remove from dce list
 * LOOKATME - think assuming trigger set to regen iops called
 *
 * SJM 12/30/02 - must not call this routine except on interactive debugger
 * syntax error if -O on
 *
 * LOOKATME - here removing monit dce's because only freed if added
 * from interactive mode
 */
extern void __free_dceauxlst(struct dceauxlst_t *dcehdr, int32 numinsts)
{
 struct dceauxlst_t *dclp;
 struct dcevnt_t *dcep2;
 struct dcevnt_t *dcep, *last_dcep;
 struct net_t *np;

  /* DBG remove -- must not call if CVC */
  /* AIV 03/19/07 - can remove call back in CVC now since wrapper and all */
  /* access modes are turned on */
  //if (__compiled_sim) __misc_terr(__FILE__, __LINE__);
  /* -- */

 /* remove all dc events that were added for this delay control event */
 for (dclp = dcehdr; dclp != NULL; dclp = dclp->dclnxt)
  {
   /* get the dce to free */
   dcep = dclp->ldcep; 

   /* since list not doubly linked must search thru list saving last */
   /* BEWARE - except for dmpv on front removable dces can be put anywhere */
   /*          on list so can not optimize this */
   np = dcep->dce_np;

   last_dcep = NULL;
   for (dcep2 = np->dcelst; dcep2 != NULL; dcep2 = dcep2->dcenxt)
    {
     if (dcep == dcep2)
      {
       if (last_dcep == NULL)
        {
         np->dcelst = dcep->dcenxt;
         /* SJM - 06/30/00 - dce list now empty - deactivate ev ctrl wakeups */
         /* LOOKATME - can this really ever happen */
         if (np->dcelst == NULL)
          {
           /* SJM 07/24/00 - may be off if reg - turning off again ok */
           np->nchg_has_dces = FALSE;
           if (np->nlds == NULL && !np->n_hasdvars)
            np->nchg_nd_chgstore = FALSE;
           /* notice do not use all changed always on optimization here */
          }
        }
       else last_dcep->dcenxt = dcep->dcenxt;

       /* now that linked out, can regen net's list */
       /* for XMR, may need to move to different mod */
       /* if remove last, still regen to free and does not stop recording */

       /* if no dce value, does nothing */
       __free_dce_prevval(dcep, numinsts, __get_dcewid(dcep, np));

       /* SJM 10/06/06 - if free dce aux list, called from a vpi cb value */
       /* change and the a freed dce is the same as the one that caused the */
       /* value chg user c routine to run, must indicate the one dce */
       /* that caused the cbvc callback to be called has been freed */
       if (dcep == __cbvc_causing_dcep) __cbvc_causing_dcep = NULL;

       __my_free(dcep, sizeof(struct dcevnt_t));
       dcep = NULL;
       goto nxt_dce;
      }
     last_dcep = dcep2;
    }
   __misc_terr(__FILE__, __LINE__);
nxt_dce:;
  }
 /* finally free the dce list - know dce of element already freed */ 
 __free_dceauxs_only(dcehdr);
}

/*
 * free a dce list - know dce of each element already freed
 */
extern void __free_dceauxs_only(struct dceauxlst_t *dcehdr)
{
 struct dceauxlst_t *dclp, *dclp2;

 for (dclp = dcehdr; dclp != NULL;)
  {
   dclp2 = dclp->dclnxt;
   __my_free(dclp, sizeof(struct dceauxlst_t));  
   dclp = dclp2;
  }
}

/*
 * free a dce previous value field 
 * if none, does nothing
 */
extern void __free_dce_prevval(struct dcevnt_t * dcep, int32 insts, int32 dcewid)
{
 /* SJM 05/05/03 - for rooted XMR dce - only 1 inst allocated */
 if (dcep->dce_expr != NULL && dcep->dce_expr->mast_dcep == dcep) 
  {
   dcep->dce_expr->expr_ofs = 0;
  }
 dcep->prevval_ofs = 0;
}

/*
 * ROUTINES TO RENUMBER STATEMENTS
 */

/*
 * renumber a statement - for use when adding to commnd history
 * statement can be head of compound
 */
static void renumber_1stmt(struct st_t *stp, int32 sfnind, int32 slcnt)
{
 int32 fji;
 struct for_t *frp;
 struct st_t *fjstp;

 if (stp == NULL) return;

 /* always set statement body line */
 stp->stfnam_ind = (word32) sfnind;
 stp->stlin_cnt = slcnt;

 switch (stp->stmttyp) {
  /* simple statement just set number */
  case S_NULL: case S_STNONE:
  case S_INC: case S_DEC:
  case S_BREAK: case S_CONTINUE: case S_RETURN:
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA:
  case S_TSKCALL: case S_QCONTA: case S_QCONTDEA: case S_CAUSE:
  case S_DSABLE: case S_REPSETUP: case S_REPDCSETUP: case S_GOTO:
  case S_FUNCCALL:
   break;
  case S_IF:
   renumber_stlst(stp->st.sif.thenst, sfnind, slcnt);
   renumber_stlst(stp->st.sif.elsest, sfnind, slcnt);
   break;
  case S_CASE:
   /* first always default or place holder for missing default */
   renumber_csitemlst(stp->st.scs.csitems->csinxt, sfnind, slcnt);
   /* if has default, know has default statement */
   if (stp->st.scs.csitems->csist != NULL)
    renumber_stlst(stp->st.scs.csitems->csist, sfnind, slcnt);
   break;
  case S_REPEAT:
   renumber_stlst(stp->st.srpt.repst, sfnind, slcnt);
   break;
  case S_FOREVER:
  case S_WHILE:
  case S_DO_WHILE:
   renumber_stlst(stp->st.swh.lpst, sfnind, slcnt);
   break;
  case S_WAIT:
   /* LOOKATME - is there a action statement that needs to be renumbered */
   renumber_stlst(stp->st.swait.lpst, sfnind, slcnt);
   break;
  case S_FOR:
   frp = stp->st.sfor;
   /* notice for assign already freed */
   renumber_stlst(frp->forinc, sfnind, slcnt);
   renumber_stlst(frp->forbody, sfnind, slcnt);
   break;
  case S_DELCTRL:
   if (stp->st.sdc->actionst != NULL)
    renumber_stlst(stp->st.sdc->actionst, sfnind, slcnt);
   break;
  case S_UNBLK:
   renumber_stlst(stp->st.sbsts, sfnind, slcnt);
   break;
  case S_UNFJ:
   /* renumber statement ptr table each of which may be st list */
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     renumber_stlst(fjstp, sfnind, slcnt);
    }
   break;
  /* notice named block non freeable (at least for now) */
  default: __case_terr(__FILE__, __LINE__);
  }
}

/*
 * renumber case item list statements
 */
static void renumber_csitemlst(struct csitem_t *csip, int32 sfnind,
 int32 slcnt)
{
 for (;csip != NULL; csip = csip->csinxt)
  { renumber_stlst(csip->csist, sfnind, slcnt); }
}

/*
 * renumber each statement of a list to same history statement list number
 */
static void renumber_stlst(struct st_t *stp, int32 sfnind, int32 slcnt)
{
 for (; stp != NULL; stp = stp->stnxt) renumber_1stmt(stp, sfnind, slcnt);
}

/*
 * INTERACTIVE COMMAND EXECUTION ROUTINES
 */

/*
 * escape from debugging environment to unix shell
 * for now no system task - can use $input
 *
 * know interactive environment always run with SIG_IGN but shell needs
 * default so ^c get out of shell
 */
extern void __escape_to_shell(char *argchp)
{
 int32 rc, status, pid;
 char *chp, *usersh;

 /* signal(SIGINT, SIG_DFL); */ 

 if ((usersh = (char *) getenv ("SHELL")) == NULL) usersh = "/bin/sh";
 if ((chp = strrchr(usersh, '/')) == NULL) chp = usersh; else chp++;
 if ((pid = fork()) == 0)
  {
   if (*argchp == '\0') execl(usersh, chp, (char *) 0);
   else execl(usersh, chp, "-c", argchp, (char *) 0);
   if (__iact_state)
    __ia_err(983, "OS Failure - user shell escape execl system call failed");
   else __sgferr(983,
    "OS Failure - user shell escape execl system call failed");
   return;
  }
 if (pid != -1) { while ((rc = wait(&status)) != pid && rc != -1) ; }
 else
  {
   if (__iact_state)
    __ia_err(983, "OS Failure - user shell escape fork system call failed");
   else __sgferr(983,
    "OS Failure - user shell escape fork system call failed");
  }
/* need to enable sim sigint32 handler even if called from :shell */  
/* ---
#if defined(INTSIGS)
 signal(SIGINT, __sim_sigint_handler);
#else
 signal(SIGINT, (void (*)()) __sim_sigint_handler);
#endif
--- */
}

/*
 * exec the $input for interactive command input source system task
 * here open cmd file and closes previous - new file is chained not nested
 * if this appears in source, just change for next time enter interactive
 */
extern void __exec_input_fnamchg(struct expr_t *axp)
{
 int32 slen;
 FILE *tmp_s;
 char *chp;

 /* msgexpr uses __exprline but if error not filled anyway */
 chp = __get_eval_cstr(axp->lu.x, &slen);
 if ((tmp_s = __tilde_fopen(chp, "r")) == NULL)
  {
   __sgferr(1241, "cannot open $input interactive command file %s", chp);
   goto done;  
  }
 if (__cmd_s != NULL) __my_fclose(__cmd_s);
 __cmd_s = tmp_s;
 if (feof(__cmd_s))
  {
   __sgfwarn(610, "$input interactive command file %s empty", chp);
   /* here just go back to stdin */
   __cmd_s = NULL;
   __cmd_fnam = NULL;
   __cur_fnam = __in_fils[1];
   __cur_fnam_ind = __cmd_ifi;
   __lin_cnt = __iah_lasti;
   goto done;
  }
 __add_infil(chp);
 __cur_fnam_ind = __last_inf;
 __cmd_fnam = __in_fils[__cur_fnam_ind];
 __lin_cnt = 0;
 if (__verbose)
  __cv_msg("  Reading interactive commands from file \"%s\".\n", __cur_fnam);

done:
 __my_free(chp, slen + 1);
} 

/*
 * execute the $history list system task
 * extension allows optional number (how many to list) arg
 * prompt after 20 lines (including embedded new lines) except finish 
 */
extern void __exec_history_list(int32 num)
{
 int32 i, h_start, nlines;
 char s1[RECLEN];

 if (num == 0) h_start = 1;
 else { if ((h_start = __iah_lasti - num + 1) <= 1) h_start = 1; }
 for (nlines = 0, i = h_start; i <= __iah_lasti; i++)
  {
   nlines += prt1_iahist_cmd(i);
   if (nlines > __hist_cur_listnum)
    {
     nlines = 0;
     __cvsim2_msg("Press return to continue:");
     fgets(s1, RECLEN, stdin);
    }
  }
}

/*
 * print one history entry - may be muliple line (with embedded new lines)  
 * returns number of lines listed (for mulitple line)
 */
static int32 prt1_iahist_cmd(int32 iahi)
{
 int32 first_time, prmplen, numlines;
 struct iahist_t *iahp;
 char c, save_ch, *chp, *chp2, s1[RECLEN];

 numlines = 1;
 iahp = &(__iahtab[iahi]);
 /* notice when non immediate statement finishes, disable turned on */ 
 if (iahp->iah_hcp != NULL) c = '*'; else c = ' ';
 sprintf(s1, "C%d%c ", iahi, c);
 __cvsim_msg(s1);

 prmplen = strlen(s1);
 __blnkline[prmplen] = '\0';
 for (chp = iahp->iah_lp, first_time = TRUE;;) 
  {
   if ((chp2 = strchr(chp, '\\')) != NULL)
    {
     chp2++;
     if (*chp2 == '\n')
      {
       chp2++;
       save_ch = *chp2;
       *chp2 = '\0';
       /* notice this has the \\\n */
       if (first_time) { __cvsim_msg("%s", chp); first_time = FALSE; }
       else __cvsim_msg("%s%s", __blnkline, chp);
       *chp2 = save_ch;
       chp = chp2;
       numlines++;
       continue;
      }
    }
   /* notice no ending \n */
   if (first_time) __cvsim_msg("%s\n", chp);
   else __cvsim_msg("%s%s\n", __blnkline, chp);
   break;
  }
 __blnkline[prmplen] = ' ';
 return(numlines);
}

/* 
 * ROUTINES FOR INTERACTIVE DISABLE AND THREAD FREEING
 */

/*
 * exec disable of interactive thread
 * this disables and free entire statement 
 */
extern void __do_iact_disable(struct hctrl_t *hcp, int32 lv_ctrl)
{
 struct thread_t *thp;

 thp = hcp->hc_thp;
 /* if any active down threads, task enables or fjs - free/disable all */
 if (thp->thofs != NULL) __free_thd_list(thp->thofs);
 free_done_iact_control(hcp, lv_ctrl);
 thp->th_dctp_tev_ofs = 0;
 /* thread frees cancel any pending events - no parent */
 __free_1thd(thp);
}

/*
 * remove interactive thread and statement list
 *
 * also removes any globals associated with statement
 */
static void free_done_iact_control(struct hctrl_t *hcp, int32 lv_ctrl)
{
 struct st_t *stp;
 struct st_t *stp2;

 /* free statements, if reenbled must parse again */
 __push_wrkitstk(__iact_mdp, 0);
 for (stp = hcp->hc_stp; stp != NULL;)
  { stp2 = stp->stnxt; __free_1stmt(stp); stp = stp2; }
 /* free any dces - know only 1 iact inst. */
 if (hcp->hc_dcelst != NULL)
  {
   /* know can only be called once sim started SIM STATE */
   __free_dceauxlst(hcp->hc_dcelst, 1);
   /* but always remove from list */ 
   hcp->hc_dcelst = NULL;
  }
 if (hcp->hc_numglbs > 0)
  { 
   free_iact_glbs(hcp->hc_grtab, hcp->hc_numglbs);
   hcp->hc_grtab = NULL;
   hcp->hc_numglbs = 0;
  }
 __pop_wrkitstk();

 /* thread freed by caller, lv ctrl when all freed at once above */ 
 if (!lv_ctrl)
  {
   if (hcp->hc_nxt != NULL) hcp->hc_nxt->hc_prev = hcp->hc_prev;
   else
    {
     __hctrl_end = hcp->hc_prev;
     if (__hctrl_end != NULL) __hctrl_end->hc_nxt = NULL;
    }
   if (hcp->hc_prev != NULL) hcp->hc_prev->hc_nxt = hcp->hc_nxt;
   else
    {
     __hctrl_hd = hcp->hc_nxt;
     if (__hctrl_hd != NULL) __hctrl_hd->hc_prev = NULL;
    }  
  }

 /* if on history, free and mark inactive */
 if (hcp->hc_iahp != NULL) hcp->hc_iahp->iah_hcp = NULL;
 if (!lv_ctrl) __my_free(hcp, sizeof(struct hctrl_t)); 
}

/*
 * ROUTINES TO IMPLEMENTED EXTENDED : DEBUGGER COMMANDS
 */

/* table of debugger commands values */
#define DB_HELP 0
#define DB_SH 1
#define DB_QUIT 2
#define DB_WHERE 3
#define DB_PRINT 4 
#define DB_RESET 5
#define DB_EXPRIS 6
#define DB_VARIS 7
#define DB_WHATIS 8
#define DB_LIST 9
#define DB_SET 10
#define DB_INFO 11
#define DB_SCOPE 12
#define DB_BRKPT 13
#define DB_IBRKPT 14
#define DB_DELBRKDIS 15
#define DB_BPDIS_ENABLE 16
#define DB_BPDIS_DISABLE 17
#define DB_STEP 18
#define DB_ISTEP 19
#define DB_HIST 20
#define DB_EMPTHIST 21
#define DB_DISPLAY 22
#define DB_UNDISPLAY 23
#define DB_TBRKPT 24
#define DB_TIBRKPT 25
#define DB_IGNORE 26
#define DB_COND 27
#define DB_SNAPSHOT 28
#define DB_NEXTB 29

/* debugger command name table (unordered) */
static struct namlst_t dbcmds[] = {
 { DB_HELP, ":help" }, 
 { DB_SH, ":shell" },
 { DB_QUIT, ":quit" },
 { DB_WHERE, ":where" },
 { DB_PRINT, ":print" },
 { DB_RESET, ":reset" },
 { DB_EXPRIS, ":expris" },
 { DB_VARIS, ":varis" },
 { DB_WHATIS, ":whatis" },
 { DB_LIST, ":list" }, 
 { DB_SET, ":set" }, 
 { DB_INFO, ":info" }, 
 { DB_SCOPE, ":scope" },
 { DB_BRKPT, ":breakpoint" },
 { DB_IBRKPT, ":ibreakpoint" },
 { DB_DELBRKDIS, ":delete" },
 { DB_BPDIS_ENABLE, ":enable" }, 
 { DB_BPDIS_DISABLE, ":disabl" }, 
 { DB_STEP, ":step" },
 { DB_ISTEP, ":istep" },
 { DB_HIST, ":history" },
 { DB_EMPTHIST, ":emptyhistory" },
 { DB_DISPLAY, ":display" },
 { DB_UNDISPLAY, ":undisplay" },
 { DB_TBRKPT, ":tbreakpoint" },
 { DB_TIBRKPT, ":tibreakpoint" },
 { DB_IGNORE, ":ignore" },
 { DB_COND, ":cond" },
 { DB_SNAPSHOT, ":snapshot" },
 { DB_NEXTB, ":nextb" }
};
#define NDBCMDS (sizeof(dbcmds) / sizeof(struct namlst_t))

/*
 * process a colon command
 *
 * this must handle history updating - returns F on exit interactive 
 * know : followed by non white space to get here and command token read 
 */
static int32 do_dbg_cmd(void)
{
 int32 rv, tmp;
 char s1[IDLEN];

 if (__toktyp != ID)
  { 
   sprintf(s1, ":%s", __prt_vtok());
bad_colon_cmd:
   __ia_err(1421, "undefined extended :[command] debugger command %s", s1); 
   return(TRUE);   
  }

 strcpy(s1, ":");
 strcat(s1, __token);

 rv = __get_dbcmdnum(s1, dbcmds, NDBCMDS);
 switch (rv) {
  case -1: goto bad_colon_cmd;
  case -2:
   __ia_err(1422, "%s ambiguous debugger command: %s", s1,
    __bld_ambiguous_list(__xs, s1, dbcmds, NDBCMDS));
   break;
  case DB_HELP:
   do_dbg_help();
chk_end:
   __chk_extra_atend(TRUE);
   break;
  case DB_SH: 
   if (__cmd_s != NULL) 
    { 
     __ia_err(1424,
      "debugger shell escape cannot be invoked from $input file");
     break;
    }
   /* must pass rest of line */
   __escape_to_shell(__visp->vichp);
   break;
  case DB_QUIT:
   __chk_extra_atend(TRUE);

   if (__tfrec_hdr != NULL) __call_misctfs_finish();
   if (__have_vpi_actions) __vpi_endsim_trycall();
   __my_exit(0, TRUE);
  case DB_WHERE:
   /* write the trace back using suspended thread */
   if (__suspended_thd == NULL)
    __ia_err(1496,
     ":where failed - no procedural context, single step and try again");
   else
    {
     __cvsim_msg("Procedural thread trace back:\n");
     __prt_where_msg(__suspended_thd);
    }
   goto chk_end; 
  case DB_SNAPSHOT:
   __write_snapshot(5);
   goto chk_end;
  case DB_PRINT:
   dbg_print();
   break;
  case DB_RESET:
   /* here do not change reset count or value and only enter interactive */
   __get_vtok(); 
   __dbg_stop_before = 100; 
   if (__toktyp != TEOF)
    {
     if (__toktyp == ID && (strcmp(__token, "s") == 0
      || strcmp(__token, "st") == 0 || strcmp(__token, "sto") == 0
      || strcmp(__token, "stop") == 0)) __dbg_stop_before = 101;
     else
      {
       __ia_err(1486, ":reset command argument %s not expected s or stop",
        __prt_vtok());
      } 
    }
   __cvsim2_msg("Simulation begun, really reset to start over? (y/n) ");
   if (fgets(s1, RECLEN, stdin) == NULL || (s1[0] != 'y' && s1[0] != 'Y'))
    break;
   /* leaving interactive - and go back to compile ^c handler */
   __iact_state = FALSE;
   /* reenable the normal ^c signal handler */
#ifndef __NOSIGS__
#if defined(INTSIGS)
   signal(SIGINT, __comp_sigint_handler);
#else
   signal(SIGINT, (void (*)()) __comp_sigint_handler);
#endif
#endif
   __reset_count--;
   longjmp(__reset_jmpbuf, 1);
   break;
  case DB_EXPRIS:
   do_dbg_expris();
   break;
  case DB_VARIS:
   do_dbg_varis();
   break;
  case DB_WHATIS:
   do_dbg_whatis();
   break;
  case DB_LIST:
   __do_dbg_list();
   break;
  case DB_SET:
   __do_dbg_set();
   break;
  case DB_INFO:
   __do_dbg_info();
   break;
  case DB_SCOPE:
   __do_dbg_scope();
   break;
  case DB_BRKPT:
   __do_dbg_brkpt(FALSE);
   break;
  case DB_TBRKPT:
   __do_dbg_brkpt(TRUE);
   break;
  case DB_IBRKPT:
   __do_dbg_ibrkpt(FALSE);
   break;
  case DB_TIBRKPT:
   __do_dbg_ibrkpt(TRUE);
   break;
  case DB_NEXTB:
   if (!__do_dbg_nextb()) return(FALSE);
   break;
  case DB_DELBRKDIS:
   __do_dbg_delbrkdis();
   break;
  case DB_BPDIS_DISABLE:
   __do_dbg_dis_enable(FALSE);
   break;
  case DB_BPDIS_ENABLE:
   __do_dbg_dis_enable(TRUE);
   break;
  case DB_DISPLAY:
   dbg_display();
   break;
  case DB_UNDISPLAY: 
   __dbg_undisplay();
   break;
  case DB_STEP:
   __get_vtok(); 
   if (__toktyp == TEOF) __step_rep_cnt = 1;
   else
    {
     if ((tmp = __get_dbg_val()) == -1 || tmp < 1)
      {
       __ia_err(1470, ":istep command repeat count %s illegal", __prt_vtok());
       break;
      } 
     __step_rep_cnt = tmp;
    }
   __single_step = TRUE;
   __verbose_step = TRUE;
   if (__iact_reason == IAER_CTRLC || __suspended_thd == NULL
    || __suspended_thd->thnxtstp == NULL) __step_from_thread = FALSE;
   __chk_extra_atend(TRUE);
   return(FALSE); 
  case DB_ISTEP:
   __get_vtok(); 
   if (__toktyp == TEOF) __step_rep_cnt = 1;
   else
    {
     if ((tmp = __get_dbg_val()) == -1 || tmp < 1)
      {
       __ia_err(1470, ":step command repeat count %s illegal", __prt_vtok());
       break;
      } 
     __step_rep_cnt = tmp;
    }
   __single_step = TRUE;
   __verbose_step = TRUE;
   if (__iact_reason == IAER_CTRLC || __suspended_thd == NULL
    || __suspended_thd->thnxtstp == NULL) __step_from_thread = FALSE;
   __step_match_idp = __scope_idp;
   __chk_extra_atend(TRUE);
   return(FALSE); 
  case DB_HIST: 
   __do_dbg_history();
   break;
  case DB_EMPTHIST:
   __do_dbg_emptyhistory();
   break;
  case DB_IGNORE:
   __dbg_brk_ignore();
   break;
  case DB_COND:
   __dbg_brk_cond();
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(TRUE); 
}

/*
 * find a db style command
 * algorithm is that any unique prefix is sufficient
 * also need algorithm that does not require full table search each time
 *
 * this needs alias mechanism ala gdb
 */
extern int32 __get_dbcmdnum(char *aval, struct namlst_t *cmdtab, int32 cmdnum)
{
 int32 i, alen, alen2;

 /* first search for normal option (if arg white space separated) */ 
 alen = strlen(aval); 
 for (i = 0; i < cmdnum; i++)
  {
   alen2 = strlen(cmdtab[i].lnam);
   if (alen2 > alen) alen2 = alen;
   if (strncmp(aval, cmdtab[i].lnam, alen2) == 0)
    { 
     if (dbcmd_prefix_rep(i + 1, aval, alen2, cmdtab, cmdnum)) return(-2);
     return(cmdtab[i].namid);
    }
  }
 return(-1);
}

/*
 * return T if find match in remaining part of db command table
 */
static int32 dbcmd_prefix_rep(int32 i, char *aval, int32 alen,
 struct namlst_t *cmdtab, int32 cmdnum)
{
 for (; i < cmdnum; i++)
  { if (strncmp(aval, cmdtab[i].lnam, alen) == 0) return(TRUE); }
 return(FALSE);
}

/*
 * given a comman prefix where know ambiguous, built table of all possibilities
 */
extern char *__bld_ambiguous_list(char *s, char *aval, struct namlst_t *cmdtab,
 int32 cmdnum)
{
 int32 i; 
 int32 first_time, alen;

 alen = strlen(aval);
 for (first_time = TRUE, i = 0; i < cmdnum; i++)
  {
   if (strncmp(aval, cmdtab[i].lnam, alen) == 0)
    {
     if (first_time) { strcpy(s, cmdtab[i].lnam); first_time = FALSE; }
     else { strcat(s, ", "); strcat(s, cmdtab[i].lnam); }
    }
  }
 return(s);
}

/*
 * DEBUGGER HELP SCREEN LINE TABLES
 */

/*
 * define debugger general topic help screen
 */ 
static char *dbg_topic_hlp[] = {
 "Type ':help [topic]' or ':help :[debugger command]' to print specific help",
 "message.  Any name can be abbreviated by a unique prefix within : debugger.",
 "Colon is required for command name help but not allowed for help topics.",
 " ",
 "Help topics:",
 "  debugging:  Entering and supplying input for +interp interactive debugging.",
 "  compiling: No interactive debugger when compiling - alternatives.", 
 "  tracing:  Separate batch tracing system for debugging.",
 "  differences:  Interactive debugger differences from XL behavior.",
 "  statements:  Using traditional interactive Verilog statement debugger.",
 "  data:  Examining variables and expressions.",
 "  source:  Listing source and navigating between files.",
 "  scope:  Setting and navigating between instance and task scopes.",
 "  break points:  Behavioral statement breakpoints and single stepping.",
 "  changes breaking:  Breaking on net changes and edges.",
 "  history:  Command history and history number command enable/disable.",
 "  info:  Determining and setting debugger status and settings.",
 "  tasks:  System task and functions useful for interactive debugging.",
 "  commands:  A list of :[command] debugger commands.", 
 "" 
};

static char *dbg_dbg_hlp[] = { 
 "Debugging:",  
 "  Both the standard Verilog XL (TM Cadence Design Systems) statement",
 "  debugger and a command based GDB style debugger are supported.  The",
 "  interactive debugger is not available when compiled simulation is used.",
 " ",
 "  Input is typed from the terminal or read from a file.",
 "  Input is terminated with a new line.  For multi-line commands, all",
 "  but the last line ends with a back slash escaped new line.  The new",
 "  command debugger commands begin with a colon as part of the name and",
 "  cannot be executed from Verilog source.  All interactive commands are",
 "  echoed to the log file unless ':set noecholog' is used to to suppress log",
 "  file command echoing (':set echolog' re-enables).",
 " ",
 "  The debugger is entered by pressing the interrupt key (^c), by calling",
 "  the $stop system task, by the -s command line option, by completing a",
 "  step command, or by hitting a breakpoint.", 
 " ",
 "  The $input(\"[file]\") system task causes debugger commands to be read",
 "  from [file] the first time interactive mode is entered (by -s?).  $input",
 "  files do not nest, instead $input in a file causes $input to chain to the",
 "  new file.  Output is written to the screen and the log file.  stderr is",
 "  not used.  All typed user input including command prompts and $input",
 "  commands is written to the log file.  $nolog and $log plus",
 "  $nokeepcommands and $keepcommands can minimize $input script output.",
 "  +nokeepcommands option disables history saving.  It is useful if",
 "  simulation is run from a shell script.",
 ""
}; 

static char *dbg_compiling_hlp[] = { 
 "Compiling no interactive debugger:",
 "  When CVC is used to compile designs to machine code, the interactive",
 "  debugger is disabled.  Use the +interp option to select slower",
 "  interpreted simulation and to enable the XL style interactive debugger.",
 "  Use a a wave form based debugger when debugging compiled designs.  CVC",
 "  supports both VCD and GTKWave FST value change dump formats.",
 " ",
 "  CVC ignores the $stop system task when simulating a compiled design.",
 "  When $stop is executed supressable warning 560 is emitted.  Pressing the",
 "  interrupt key (usually ctrl-c) kills your simulation the sent quit signal",
 "  is passed to your shell.",
 ""
}; 

static char *dbg_trc_hlp[] = { 
 "Debugging using the tracing mechanism:", 
 "  An alternative non interactive tracing mechanism is supported.",
 "  Behavioral statement tracing is started with the -t option or $settrace",
 "  system task and stopped by calling $cleartrace.  Event tracing is started", 
 "  with the -et option or $setevtrace system task and stopped by calling",
 "  $clearevtrace.  The -et option allows pre time 0 initialization events",
 "  to be traced.  Trace output is written to stdout and the log file unless",
 "  the +tracefile [file name] option or $settracefile([string]) system task",
 "  are used to direct trace output to a separate file.  The trace mechanism",
 "  is intended to allow debugging of parallel activity by searching trace",
 "  output with a debugger.",
 " ",
 "  Trace statements and gates are reconstructed source with parameters",
 "  replaced by numeric values.  Interactive debugger breakpoint and step",
 "  tracing also emit source lines.  To avoid duplicate output if tracing",
 "  and the interactive debugger are used, redirect trace output.",
 " ",
 "  The tracing options works with compiled simulation except only a small",
 "  subset of tracing messages are printed.",
 ""
}; 

static char *dbg_dif_hlp[] =  { 
 "Debugger differences from older P1364 LRMs:",
 "  1) Multiple line interactive debugger commands must end with escaped new",
 "  lines.  Verilog statements still require the ending semicolon.",
 "  2) The $settrace system task (also -t) are divided into the two tracing",
 "  classes: $settrace and $setevtrace (-t and -et).",
 "  3) By default when interactive mode is entered the $scope interactive",
 "  scope is set to the current scope.  This allows examination of local",
 "  variables on step or break but may require entering $scope command on",
 "  every interactive entry to run some legacy scripts.  In functions, named",
 "  blocks do not have scope so function scope remains.  Interactivbe variable",
 "  access in function named block must use qualified reference from function",
 "  scope.  To duplicate XL behavior in which interactive scope can only",
 "  be changed by $scope system task, type: ':set noscopechange' inside the",
 "  interactive debugger.  When re-enabling commands from the history list,",
 "  either the command must use rooted names or the scope must be the same",
 "  as the scope when the command was originally entered.",
 "  4) Delay back annotation by specparam assignments not supported, and",
 "  $updatetiming, but similar standard SDF (LABEL form and PLI 2.0 assignment",
 "  to defparams and specparam before delay elaboration supported.",
 ""
}; 

static char *dbg_stmt_hlp[] =  { 
 "Interactive Verilog statement execution:",
 "  Any Verilog statement can be entered at the interactive mode prompt (or",
 "  in an $input file) except named blocks and initial or always statements.",
 "  No new variables can be declared and all identifiers are accessed using",
 "  the current scope (entry scope or change $scope location).  Compound",
 "  statements and statements with delay or event controls are legal.",
 "  Commands are:",
 " ",
 "   '.'   Exit the debugger and continue execution (event processing).",
 "   ':'   Print the current instance and possibly task scope plus location",
 "         of scope and current :list current location.  Prints scope and",
 "         listing location, use :where for procedural execution location.", 
 "   ';'   Silently step through next procedural statement and process all",
 "         events and time movement up to the next procedural statement. The",
 "         current location for the :list command is not changed.  Tasks and",
 "         functions are stepped into.",
 "   ','   Step through next statement and print next source statement.  Same",
 "         as ';' except the next source line to execute is printed.",
 "   -[number]  Disable history command [number] if it has not yet completed.",
 "         The $history task indicates commands that are active with a '*'",
 "   [number]  Re-execute command [number] from the history list only if the",
 "         command has finished (no '*' mark when printed with $history).",
 "         Commands are re-executed in the current scope so if a command sets",
 "         a change or edge breakpoint, it must contain rooted names or be",
 "         executed from the same scope as it's original entry.", 
 ""
}; 

static char *dbg_data_hlp[] =  { 
 "Displaying internal circuit values:",
 "  In addition to the normal $display (or $write) system tasks to display",
 "  values use :print to override declared expression base or width (type",
 "  ':help :print' for legal values). Use :display to define expressions that",
 "  are printed whenever interactive mode is entered.  :display and :print",
 "  take same format and width modifiers.  :expris [expr] to determine the",
 "  width and type of an expression.  Use :varis [var.] to determine type,",
 "  width and declaration keywords of a variable.  Use :whatis [name] to",
 "  determine all uses of an identifier name.  Entire qualified path from",
 "  function scope required for accessing variables in named blocks in", 
 "  functions.",
 ""
}; 

static char *dbg_src_hlp[] =  { 
 "Listing source statements:", 
 "  The normal $list([scope]) system task can list all of any task or module.",
 "  The :list command lists 10 lines from a selected location that can be",
 "  a scope or a [file:][line] reference or argument relative to last listed",
 "  line.  Type ':set listsize [number]' to change the number of lines listed.",
 "  The current listing location is independent of current scope except when",
 "  :scope or $scope is executed, the current list line is set to the first",
 "  line of the scope.  Also since ',' and :[i]step and hitting a breakpoint",
 "  print a source line, those commands change the current list line.", 
 "  The explicit [file:][line] list command lists in a new file and :list ++",
 "  lists the beginning of the next source file (:list -- the previous end).",
 "  Only these three commands can change listing file.  Type ':help :list'",
 "  for the format of the various :list command options.", 
 ""
}; 

static char *dbg_scope_hlp[] =  { 
 "Setting interactive scope:",
 "  The $scope([scope xmr]) system task changes interactive scope.  The :scope",
 "  command also changes scope but allows a more general reference.  The",
 "  :breakpoint command takes a scope reference argument.  Format is:",
 " ",
 "  [file:][line] - first instance of scope determined by [file:][line].",
 "       [file] can be source file, -y or -v path or any path tail if it is",
 "       unique.  [line] must be between module - endmodule.  Any ':' in",
 "       [file] name must be escaped with a back slash.  Scope set to type or",
 "       first instance but other command argument may select instance for",
 "       :breakpoint.  Scope list line set to first line of scope not [line].", 
 "       [line] is same as [file:][line] where [file] is current file.",
 " .. or .u - upward scope first line - if scope in task - one up task or",
 "       instance containing task (not up instance).",
 " .d - first line of scope of first contained instance (not contained task).",
 " [module name]  - first instance of module unless name declared as instance",
 "       in current scope, then normal downward hierarchical reference.",
 " [hierarchical ref.] - first line of instance - same as $scope argument.",
 "" 
}; 

static char *dbg_brkpt_hlp[] = { 
 "Behavioral statement breakpoints:",
 "  Use the :breakpoint or :ibreakpoint commands to set a breakpoint at a",
 "  specific source statement.  The break occurs before statement execution.",
 "  :breakpoint breaks in all instances and :ibreakpoint breaks only in the",
 "  specified instance.  The :breakpoint argument can be any scope or line",
 "  reference.  If no line reference is given the break is at the first",
 "  initial, always or task statement of the scope.  For :ibreakpoint the",
 "  argument must be an instance reference that may optionally be followed by",
 "  a ',' and a line reference.  For a line reference, the breakpoint is set",
 "  at the first procedural statement at or following the line in the scope.", 
 " ",
 "  Type ':help :breakpoint' or ':help :ibreakpoint' for other options and",
 "  argument format.  Use ':info breakpoints' to print a list of breakpoints",
 "  ':delete [number]' to delete breakpoint [number] (no argument deletes all),",
 "  ':disabl [number]' to temporarily disable breakpoint and ':enable [number]'",
 "  to re-enable.  :tbreakpoint and :tibreakpoint are identical to :ibreak",
 "  and :break except breakpoint removed when hit.  :cond adds expression to",
 "  breakpoint that must be true to cause stop. :ignore adds count of how many",
 "  hits to ignore before halting.",
 ""
}; 

static char *dbg_chgbrk_hlp[] = {
 "Breaking on net changes:",
 "  Enter a delay or event control followed by the $stop system task to",
 "  enter interactive mode on value change.  Normally the event control",
 "  statement will be in a loop (probably a forever) because otherwise the",
 "  break is disabled after each trigger.  Also when interactive mode is",
 "  entered from an interactive $stop, a step (',', ':', :step, or :istep)",
 "  command must be entered before using [number] to re-enable a history",
 "  statement.  For example: 'forever @(posedge clock) $stop;' is usually",
 "  better than '@(posedge clock) $stop;'",
 ""
};

static char *dbg_hist_hlp[] = { 
 "History mechanism:",
 "  A command is re-executed by entering its history number.  A uncompleted",
 "  command (such as a Verilog wait or delay control) is disabled by entering",
 "  -[number] where [number] is command's assigned number in history list.",
 " ",
 "  The $history system task prints the most recent 20 (or histlistsize if",
 "  different) history entries.  The debugger :history [optional number]",
 "  command is more flexible because if an optional number argument appears,",
 "  that many elements are printed (0 for all).  The interactive command",
 "  prompt is 'C[number] >' where [number] is a command's history number.",
 "  The one character, [number] to execute, [-][number] to disable and",
 "  incorrect (such as mistyped Verilog statement entered interactively)",
 "  commands are not added to the history list.",
 " ",
 "  All commands input during a run are retained.  Use $nokeepcommands to",
 "  suppress history accumulation and $keepcommands to re-enable in $input",
 "  scripts.  +nokeepcomands command line option disables history saving for",
 "  programs that run a simulation by supplying command input through a pipe.",
 "  :emptyhistory command discards all retained history commands and resets",
 "  command number to one.  If any history commands are enabled (have not yet", 
 "  completed or been disabled), :emptyhistory will fail.  When an interactive",
 "  Verilog statement is executed, if it can be executed immediately (no", 
 "  delays, events or tasks enables), it is executed from inside debugger and",
 "  control remains in interactive mode.  Non immediate statements are",
 "  scheduled after already scheduled events and resumes.  $stop or the", 
 "  interrupt signal (^c) must then be used to reenter interactive mode.  Use",
 "  ':set histlistsize' to set default number of history commands to list and",
 " ':info histlistsize' to see current number.", 
 ""
}; 

static char *dbg_info_hlp[] = { 
 "Determining and setting internal debugger state values:",
 "  The ':info [debugger value name]' command prints the current value of",
 "  a debugger value.  The ':set [debugger value name] [value]' command",
 "  changes a debugger value.  Type ':help :info' or ':help :set' for the list",
 "  of debugger info value names.",
 ""
}; 

static char *dbg_stsks_hlp[] = { 
 "The following system tasks may be useful during interactive debugging:",
 "   $finish;  Terminate simulation.",
 "   $list([scope reference]);  list source lines of scope (:list is",
 "      alternative).  $list does not print variables values, use $showvars",
 "      or :print <expr> for that.  Also $list does not mark source lines",
 "      with pending events.",
 "   $system(\"[OS command string]\");  Escape to a sub shell and execute the",
 "      command string (alternative is :shell [command string]).  Use empty",
 "      string (\"\") to invoke an interactive sub-shell.",
 "   $flushlog;  Call OS flush of buffers for log file and trace file.  Can",
 "      then use :shell to invoke your editor to inspect output.",
 "   $history;  Print history list to stdout and log file.  Contrary to XL,",
 "      '$history;' prints last 20 (or histlistsize) commands.  Use",
 "      ':history <num>' to print <num> commands.  <num> 0 prints all. :set",
 "      sets and :info prints debugger histlistsize parameter that determines",
 "      number of commands to list.",
 " $keepcommands;, $nokeepcommands;  Enable (or disable) saving of commands",
 "      entered interactively to history list.  Default is $keepcommands.",
 "      Use the +nokeepcommands command line option to disable saving of",
 "      commands to the history list unless '$keepcommands;' is executed.",
 "   $input([string]);  Process interactive commands from [string] file.",
 "   $nolog;, $log;  All commands in $input scripts will be copied to the",
 "      log file unless $nolog is used.  To re-enable log file output, use",
 "      $log; with no argument.  To change log file use $log([string]).",
 "   $reset;, $reset_count;, $reset_value;  During debugging reset to start",
 "      of simulation.  :reset command is better during debugging since it",
 "      returns to time 0 leaving the reset count unaffected and allows stop.",
 "   $scope;  Change interactive environment scope to avoid a need to type",
 "      full paths for variable names.  :scope and automatic scope tracking",
 "      are intended to lessen need to set explicit interactive scopes.",
 "      $scope can set scope to function named block but next ineractive entry",
 "      (from step?) will change scope to function body scope.",
 "   $showallinstances;  Print all instances in design with source file and",
 "      line location.  Useful to find module whose name is forgotten.",
 "      +printstats and +printallstats give more detailed information.", 
 "      If no other window is available, use $flushlog; and :shell to view.",
 "   $showscopes;  Used to show scopes in current interactive scope.  Can be",
 "      called with non zero argument to list entire design scope map.", 
 "   $showvariables;, $showvars  Print all variables in current scope. :print",
 "      is more terse but $showvars prints more for multiple fan-in wires.",
 "   $shapshot; print up to 5 pending procedural and 5 pending declarative",
 "      events and status of every interactive thread.  Same as :snapshot.",
 "   $display, $write  Write values.  Alternative :print is more flexible but",
 "      these tasks allow formatted output.",
 "" 
}; 

/* table of debugger help topic values */
#define HLP_DBG 0
#define HLP_COMP 1
#define HLP_TRC 2
#define HLP_DIF 3
#define HLP_STMT 4
#define HLP_DAT 5
#define HLP_SRC 6
#define HLP_SCP 7
#define HLP_BP 8
#define HLP_CHGBP 9
#define HLP_HIST 10
#define HLP_INF 11
#define HLP_TSK 12
#define HLP_CMD 13

/* debugger help topic name table */
/* index and pos. in this table must be identical */
static struct namlst_t hlptoptab[] = {
 { HLP_DBG, "debugging" },
 { HLP_COMP, "compiling" },
 { HLP_TRC, "tracing" },
 { HLP_DIF, "differences" },
 { HLP_STMT, "statements" },
 { HLP_DAT, "data" },
 { HLP_SRC, "source" },
 { HLP_SCP, "scope" },
 { HLP_BP, "breakpoints" },
 { HLP_CHGBP, "changes" }, 
 { HLP_HIST, "history" },
 { HLP_INF, "info" },
 { HLP_TSK, "tasks" },
 { HLP_CMD, "commands" }
};
#define NHLPTOPS (sizeof(hlptoptab) / sizeof(struct namlst_t))

/* per help topic line tables - size is same help topices */
/* index and pos. in this table must be identical */
static struct hlplst_t hlp_topics[] = { 
 { HLP_DBG, dbg_dbg_hlp },
 { HLP_COMP, dbg_compiling_hlp },
 { HLP_TRC, dbg_trc_hlp },
 { HLP_DIF, dbg_dif_hlp },
 { HLP_STMT, dbg_stmt_hlp },
 { HLP_DAT, dbg_data_hlp },
 { HLP_SRC, dbg_src_hlp },
 { HLP_SCP, dbg_scope_hlp },
 { HLP_BP, dbg_brkpt_hlp },
 { HLP_CHGBP, dbg_chgbrk_hlp },
 { HLP_HIST, dbg_hist_hlp },
 { HLP_INF, dbg_info_hlp },
 { HLP_TSK, dbg_stsks_hlp },
 /* here must call special command list routine */ 
 { HLP_CMD, NULL, }
};

/* 
 * DEBUGGER INDIVIDUAL COMMAND HELP SCREEN LINE TABLES
 */

static char *help_msg[] = { 
 ":help [optional topic or :[command] name prefix]", 
 "   Print help message.",
 ""
}; 

static char *shell_msg[] = { 
 ":shell [rest of line is OS command]",
 "   Execute rest of line as OS command in sub-shell.  Notice no quotes needed.",
 "   Empty rest of line to spawn interactive shell.  Equivalent to",
 "   '$system([quotes OS command string]);' system task.",
 ""
}; 

static char *snapshot_msg[] = { 
 ":snapshot",
 "   Print snapshot of current procedural location and list of statement at",
 "   which each procedural (per instance) thread suspended at.  Also lists",
 "   pending events on head of event list.  May be long so one way to view it",
 "   is to type: $flushlog; then ':sh [evoke editor on verilog.log file]'.",
 ""
}; 

static char *where_msg[] = { 
 ":where",
 "   Print back trace of most recently suspended control thread including all",
 "   upward thread enables with source and scope locations.  To see a listing",
 "   of all pending scheduled event activity and thread states use $snapshot;",
 "   or :snapshot.  :where corresponds as closely as possible to normal",
 "   call stack trace back.  ':' prints instance scope and last source",
 "   listing location.  If :where fails, suspension was from declarative code.",
 "   Try single step and entering :where again.",
 ""
}; 

static char *quit_msg[] = { 
 ":quit",
 "   Exit.  Equivalent to $finish;", 
 ""
};

static char *print_msg[] = { 
 ":print [/format][#width] [expression]",
 "   Evaluate and print expression.  If [/format] is present, interpret the",
 "   value according to format.  Formats are:  'd' (decimal), 'u' (unsigned),",
 "   'b' (binary), 'h' or 'x' (hex), 's' (string), or 'c' (1 character).  If",
 "   the [/format] is omitted, use current default unless the expression is a",
 "   string or real.  Starting default base is hex, but use ':set printbase'",
 "   to set different default base.  /u format prints bit pattern as unsigned.",
 "   If [#width] value is present, interpret as [width] wide, instead of width",
 "   computed from operator width rules.  Any format or width are ignored for",
 "   reals, use $realtobits to view bit pattern.",
 ""
};

static char *reset_msg[] = { 
 ":reset [stop]",
 "   Reset simulation back to time 0 and restart simulation.  Interactive mode",
 "   must be explicitly entered by interrupt (^c), calling $stop or [stop]",
 "   option.  If a -i startup file was given it is executed on interactive",
 "   entry.  $reset_count and $reset_value are not changed.  If optional",
 "   :reset stop argument is present, stop just before simulation, else rerun",
 "   without stopping even if -s option was given on command line.  Equivalent",
 "   to $reset system task but can be used to restart for debugging models",
 "   that use the $reset system task.  The $reset system task uses the -s",
 "   option unless the first argument is non zero and stops before simulation.",
 "   All uncompleted interactive statements are disabled by either :reset",
 "   or $reset.  They are re-enabled by typing history command number or",
 "   running -i start up interactive file.  Debugger state : breakpoints",
 "   (left enabled) and history are preserved.",
 ""
};

static char *expris_msg[] = { 
 ":expris [expression]",
 "   Print type and width of expression.  Use to determine Verilog width and",
 "   property rules for complex expressions.",
 ""
};

static char *varis_msg[] = { 
 ":varis [variable]",
 "   Print type and width and declaration keywords of variable.",
 ""
};

static char *whatis_msg[] = { 
 ":whatis [identifier]",
 "   Print symbol information for every use of identifier.  Also, emits one",
 "   instance reference for each use, so a breakpoint can be set.",
 ""
};

static char *list_msg[] = { 
 ":list [range]",
 "   List source within [range] lines.  Some [range]s are relative to last",
 "   printed line.  Any scope change or $list or previous :list command",
 "   changes the last printed line.  Legal [range]s are:",
 " ",
 "     + or [empty]             10 lines starting with last printed.",
 "     +0                       10 lines around current line.",
 "     -                        10 lines ending 1 before previous first line.",
 "     ++                       First 10 lines of next file.",
 "     --                       Last 10 lines of previous file.",
 "     [file]:[number]          10 lines around [number] in file [file].",
 "     [number]                 10 lines around [number] in current file.",
 "     [+/-][offset]            10 lines starting [offset] from current.",
 "     [+/-][num1],[+/-][num2]  Range, if [+/-] offset from current line.",
 "     [scope reference]        First 10 lines starting at [scope].",
 " ", 
 "   By default 10 lines are list, use ':set listsize [number]' to change",
 "   number of printed lines to [number].  Notice stepping with ';' does not",
 "   change last printed line.  Use [file]:[number] to list inside `include",
 "   files.  ++ and -- exit to file and line of first inclusion of file.",
 "   Read library files are same as source files.",
 ""
};

static char *set_msg[] = { 
 ":set [debugger parameter] [value]",
 "   Set debugger internal parameter to [value].  Legal set parameters are:",
 " ",     
 "   :set listsize [number]     Default is 10 lines to list.",
 "   :set histlistsize [number] Default is 20 history commands to list.",
 "   :set noscopechange         Disable automatic scope setting on entry to",
 "                              interactive mode.",
 "   :set scopechange           Re-enable automatic scope setting on.  Scope",
 "                              not set to named blocks in functions.",
 "   :set printbase [base]      Set default :print command base, values: hex",
 "                              (default), decimal, octal binary.",
 "   :set nologecho             Turn off writing of input interactive commands",
 "                              the log file (default).",
 "   :set logecho               Turn on writing of input commands.",
 ""
};

static char *info_msg[] = { 
 ":info [debugger parameter]",
 "   Show value of debugger state or parameter setting.  Legal info parameters",
 "   are: listsize, histlistsize, scopechange, breakpoints, displays,",
 "   printbase and logecho.  For breakpoints and auto-display expressions",
 "   prints status information for each.",
 ""
};

static char *scope_msg[] = { 
 ":scope [scope reference]",
 "   Change interactive scope to [scope reference] location.  Type",
 "   ':help scope' for list of legal scope selection forms.  Any [line] is",
 "   used only to determine surrounding scope.  Scope only applies to",
 "   interactive mode and system tasks that explicitly are defined to use the",
 "   interactive scope.   Extended version of $scope system task.  If scope",
 "   set to function named block scope, next interactive entry will change", 
 "   scope to function body scope (assuming scopechange mode active).", 
 ""
};

static char *breakpoint_msg[] = { 
 ":breakpoint [scope reference] or none",
 "   Set statement breakpoint at all instances of [scope reference].  Type", 
 "   ':help scope' for a list of legal [scope reference] forms.  If the",
 "   reference selects an instance, only the type of the instance is used.",
 "   If the [scope reference] is not a [file:][line] reference, use first",
 "   initial, always or task statement of scope.  If no argument, set at",
 "   last :list argument (first if range, closest if backward) that must be",
 "   within task, function or initial or always block.  Setting a breakpoint",
 "   at a line means the first procedural statement at or after the line (but",
 "   must be within scope).  Type ':help breakpoints' for discussion of other",
 "   breakpoint commands.",
 "", 
}; 

static char *ibreakpoint_msg[] = { 
 ":ibreakpoint [scope reference][,[file:][line]] or none",
 "   Set statement breakpoint at instances of [scope reference] file [file]",
 "   and [line] line.  Type ':help scope' for a list of legal [scope ref.]s,",
 "   but here only explicit instance scope references are legal.  If the",
 "   ',[file:][line]' argument is omitted, use first statement of first",
 "   initial, always, or task (for task scope).  If ',[line]' but no [file]",
 "   is given, use first or only file of scope.  If no scope reference and",
 "   only ',[file:][line]' is given, use current scope.  No argument means",
 "   set at last :list argument (first if range, closest if backward)",
 "   that must be within task, function, or initial or always block.",
 "   Type ':help breakpoints' for discussion of other breakpoint commands.",
 "", 
}; 

static char *delete_msg[] = { 
 ":delete [optional type] [number]",
 "   Delete breakpoint or display expression with number [number] or all if",
 "   number is omitted.  [optional type] is breakpoints or displays (default",
 "   if omitted is breakpoints).  Type 'info breakpoints' or 'info displays'",
 "   to determine breakpoint or auto-display number.  If [number] is omitted,",
 "   delete all breakpoints or auto-display expressions.", 
 ""
};

static char *disable_msg[] = { 
 ":disabl [optional type] [number]",
 "   Temporarily disable breakpoint or display with number [number].",
 "   [optional type] is breakpoints or displays (breakpoints is default if",
 "   omitted) and can be abbreviated to first letter. Type 'info breakpoints'",
 "   or 'info displays' to determine breakpoint or auto-display number and",
 "   enable state.  Notice final e must not appear to avoid conflict with",
 "   Verilog disable keyword (any unique prefix such as 'disa' works).  Also",
 "   notice that :disabl disables an added : debugger breakpoint, but disable",
 "   statement or -[number] disables simulation of a Verilog statement.",
 ""
};

static char *enable_msg[] = { 
 ":enable [optional type] [number]",
 "   Enable breakpoint or display with number [number].  [optional type]",
 "   is either breakpoints or displays (breakpoints is default if omitted) and",
 "   can be abbreviated to first letter.  Type 'info breakpoints' or",
 "   'info displays' to determine breakpoint or auto-display expression",
 "   number and enable state.",
 ""
};

static char *step_msg[] = { 
 ":step [optional repeat count]",
 "   Step to next procedural line.  Execute one statement or statements on",
 "   current line, stop before first statement of next line.  May process",
 "   pending declarative events before stepping.  Execution steps into any",
 "   task or function.  Equivalent to ',' interactive Verilog command.",
 "   Always prints location after stopping.  if optional repeat count, step",
 "   that many times before stopping and printing message.  If interrupt (^c)", 
 "   or breakpoint hit during stepping, stop stepping and enter interactive",
 "   mode.",
 ""
};

static char *istep_msg[] = { 
 ":istep [optional repeat count]",
 "   Step to next procedural statement that is in same instance tree location.",
 "   Otherwise identical to :step.  If debugger entered by interrupt, use one",
 "   :step before :istep since scope may have been in module without any", 
 "   procedural statements.  :istep uses currently executing instance not",
 "   interactive scope set by $scope.",
 ""
};

static char *hist_msg[] = { 
 ":history [optional number]",
 "   Print 20 (or value of histlistsize info debugger parameter) commands.",
 "   If [number] appears, print [number] (0 means all) history commands.",
 "   Pauses and prompts for CR every histlistsize lines.",
 "" 
};

static char *empthist_msg[] = { 
 ":emptyhistory",
 "   If all history commands have completed or are disabled with (-[number]",
 "   command), discard retained history and set next history command to 1.",
 "" 
};

static char *disp_msg[] = { 
 ":display [/format][#width] [expression]",
 "   Set up [expression] in display table so that it is displayed on every",
 "   entry to interactive mode.  Arguments are identical to :print command.",  
 "   Use ':delete display' or ':undisplay' to delete all auto-display",
 "   expressions.  If either is followed by a number, delete that numbered",
 "   display only.  Use ':info display' to list current displays.  ':display'",
 "   with no arguments displays all current auto-display expressions.",
 "   Use 'enable display' and 'disabl display' to temporarily turn off or on",
 "   an auto-display expression.",  
 ""
};

static char *undisp_msg[] = { 
 ":undisplay [optional number]",
 "   Delete [number] auto-display expression or all current if [number] is",
 "   not present.  Same as ':delete display' command.",
 ""
};

static char *tbreakpoint_msg[] = { 
 ":tbreakpoint [scope reference] or none",
 "   Command identical to :breakpoint except breakpoint is temporary and",
 "   removed after it is hit the first time.  To avoid tracing in task or", 
 "   function (approximate DBX/GDB next command), use the :nextb command.",
 "   It sets a :tibreak at the next line and executes a '.' command.  Because",
 "   of delay and event controls, other threads may be executed before break",
 "   is hit.  The :ignore command can be used with :tbreakpoint.  After",
 "   ignore count hits, the break point is taken and then removed.",
 ""
};

static char *tibreakpoint_msg[] = { 
 ":tibreakpoint [scope reference][,[file:][line]] or none",
 "   Command identical to :ibreakpoint except breakpoint is temporary and",
 "   removed after it his the first time (see :tbreakpoint help).  Only", 
 "   stops in instance that is same as scope reference instance.", 
 ""
};

static char *nextb_msg[] = { 
 ":nextb",
 "   Abbreviation for :tibreak [line number of next thread statement]",
 "   followed by '.'.  Analog of DBX/GDB next command steps over current",
 "   statement.  Break point is visible and can be removed before it is hit.",
 "   If no next statement in thread, temporary break point not set and error",
 "   message emitted.  :nextb over task enable may execute other threads",
 "   before stopping if the task contains event or delay controls.  :nextb",
 "   and for that matter any temporary break point do not use up a break",
 "   point number unless a new break point is set before temporary break",
 "   point is hit.  See ':help :tbreakpoint' and ':help statements' for",
 "   more information.", 
 ""
};

static char *ignorebrk_msg[] = { 
 ":ignore [breakpoint number] [ignore count]",
 "   Do not stop at break point [number] until [ignore count] hits of the",
 "   break point have occurred.  Ignore count assumes last hit was 0th.",
 "   To remove an :ignore count, use 'ignore [break number] 0'.  Use", 
 "   ':info breakpoints' to determine number of hits and any pending ignore",
 "   count.",
 ""
};

static char *condbrk_msg[] = { 
 ":cond [breakpoint number] [optional condition expression]",
 "   Do not stop at break point [number] unless [expression] evaluates to",
 "   a positive non x/z value (i.e. true).  Expression will be checked and",
 "   evaluated in instance and task/function or named block scope of break",
 "   point.  Since Verilog variables persist, :cond expression variable always",
 "   have values.  Conditions are evaluated before ignore counts so if",
 "   condition is false hit count does not rise.  Use ':cond [break number]'",
 "   to remove condition.",
 ""
};

/* per command help line tables - size is same as dbcmds */
/* this table must have value and index same (same order as constants) */
static struct hlplst_t hlpcmds[] = { 
 { DB_HELP, help_msg }, 
 { DB_SH, shell_msg },
 { DB_QUIT, quit_msg },
 { DB_WHERE, where_msg },
 { DB_PRINT, print_msg },
 { DB_RESET, reset_msg },
 { DB_EXPRIS, expris_msg },
 { DB_VARIS, varis_msg },
 { DB_WHATIS, whatis_msg },
 { DB_LIST, list_msg }, 
 { DB_SET, set_msg }, 
 { DB_INFO, info_msg }, 
 { DB_SCOPE, scope_msg },
 { DB_BRKPT, breakpoint_msg },
 { DB_IBRKPT, ibreakpoint_msg },
 { DB_DELBRKDIS, delete_msg },
 { DB_BPDIS_ENABLE, enable_msg },
 { DB_BPDIS_DISABLE, disable_msg },
 { DB_STEP, step_msg },
 { DB_ISTEP, istep_msg },
 { DB_HIST, hist_msg },
 { DB_EMPTHIST, empthist_msg },
 { DB_DISPLAY, disp_msg },
 { DB_UNDISPLAY, undisp_msg },
 { DB_TBRKPT, tbreakpoint_msg },
 { DB_TIBRKPT, tibreakpoint_msg },
 { DB_IGNORE, ignorebrk_msg },
 { DB_COND, condbrk_msg },
 { DB_SNAPSHOT, snapshot_msg },
 { DB_NEXTB, nextb_msg }
};

/*
 * ROUTINES TO IMPLEMENT DEBUGGER HELP SYSTEM
 */

/*
 * write the debugger help screens
 * format is :help or :help [topic] where [topic] is special topic or
 * :[command]
 */
static void do_dbg_help(void)
{
 int32 rv;
 char s1[RECLEN];

 /* number error here, but make sure not allocated */
 __get_vtok();
 /* case 1: no argument, emit topic list */ 
 if (__toktyp == TEOF) { wr_dbg_hlpmsg(dbg_topic_hlp); return; }
 /* case 2: argument is : debugger command */
 if (__toktyp == COLON)
  {
   __get_vtok();
   if (__toktyp != ID || strlen(__token) > 40)
    {
bad_cmd:
     __ia_err(1438,
      ":help argument :%s illegal - not a : debugger command", __prt_vtok()); 
     return;
    }
   strcpy(s1, ":");
   strcat(s1, __token);
   rv = __get_dbcmdnum(s1, dbcmds, NDBCMDS);
   if (rv == -1) goto bad_cmd; 
   if (rv == -2)
    {
     __ia_err(1422, ":help %s - ambiguous : debugger command: %s", s1,
      __bld_ambiguous_list(__xs, s1, dbcmds, NDBCMDS));
     return;
    }
   /* notice rv is found in command table but indexes hlpcmds table */
   /* therefore the 2 tables must be kept in indentical order */
   wr_dbg_hlpmsg(hlpcmds[rv].hmsgtab);
   goto done;
  }
 /* case 3: argument is help topic */
 if (__toktyp != ID)
  {
bad_topic:
   __ia_err(1439, ":help topic %s unrecognized", __prt_vtok()); 
   goto done;
  }
 rv = __get_dbcmdnum(__token, hlptoptab, NHLPTOPS);
 if (rv == -1) goto bad_topic; 
 if (rv == -2)
  {
   __ia_err(1422, ":help %s - ambiguous topic: %s", s1,
    __bld_ambiguous_list(__xs, s1, hlptoptab, NHLPTOPS));
   goto done;
  }
 /* for help command topic, routine to list all commands */
 /* hlptoptab and hlp_topics tables must be kept in identical order */
 if (rv == HLP_CMD) wr_dbg_lstofcmds(dbcmds, NDBCMDS);
 else wr_dbg_hlpmsg(hlp_topics[rv].hmsgtab);

done:
 __chk_extra_atend(TRUE);
}

/*
 * write a debugger help message to standard output and log file
 */
static void wr_dbg_hlpmsg(char **dbgmsg)
{
 int32 i; 

 for (i = 0; *dbgmsg[i] != '\0'; i++) __cvsim_msg("%s\n", dbgmsg[i]); 
}

/*
 * write the list of debugger commands
 */
static void wr_dbg_lstofcmds(struct namlst_t *cmdtab, int32 cmdnum)
{
 int32 i;

 if (__outlinpos != 0) __misc_terr(__FILE__, __LINE__);
 __pv_stlevel = 0;
 __wrap_puts(":[command] debugger commands:  ", stdout); 
 for (i = 0; i < cmdnum; i++)
  {
   __wrap_puts(cmdtab[i].lnam, stdout);
   if (i != cmdnum - 1) __wrap_puts(", ", stdout);
  }
 if (__outlinpos != 0) __wrap_putc('\n', stdout);
 __outlinpos = 0;
}

/*
 * ROUTINES TO IMPLEMENT DEBUGGER EXPRESSION EVALUATION
 */

/*
 * print an expression value - know :print read 
 *
 * format - :print/[d,u,b,h(x),s,c]#[bits] <expr> - default h and expr width
 * p#42 - p/d#52
 * notice no f - since will always print real as real
 */
static void dbg_print(void)
{
 int32 prtfmt, prtwidth, force_unsign;
 struct expr_t *prtx;

 prtfmt = BNONE;
 prtwidth = -1;
 force_unsign = FALSE;
 /* handle optional /[format letter] */
 __get_vtok();
 if (__toktyp == DIV)
  {
   __get_vtok();
   if (__toktyp == ID)
    {
     if (strlen(__token) > 1)
      {
bad_prt_typ:
       __ia_err(1425, ":print type selector /%s illegal", __token); 
       return;
      }
     switch (__token[0]) {
      case 'd': prtfmt = BDEC; break; 
      case 'u': prtfmt = BDEC; force_unsign = TRUE; break; 
      case 'o': prtfmt = BOCT; break;
      case 'b': prtfmt = BBIN; break; 
      case 'h': case 'x': prtfmt = BHEX; break;
      case 's': prtfmt = BSTR; break; 
      case 'c': prtfmt = BCHAR; break;
      default: goto bad_prt_typ;
     }
    }
   else
    {
     __ia_err(1426,
      ":print type selector / not followed by format letter - %s read",
      __prt_vtok());
     return;
    }
   __get_vtok();
  }
 /* handle optional #<width> */ 
 if (__toktyp == SHARP)
  {
   __get_vtok();
   if (__toktyp != NUMBER || __itoklen > WBITS || __bcwrk[0] != 0L)  
    { 
     __ia_err(1427, ":print width override # not followed by legal number");
     return;
    }
   prtwidth = (int32) __acwrk[0];
   __get_vtok();
  }
 /* if collect returns F, if NULL, know error emitted in routine */
 /* notice here if value, cannot free - need the iatok ptr allocated value */
 if ((prtx = __rd_iact_expr()) == NULL) return;
 /* know this will fit in RECLEN and truncates for readabililty for */
 /* very wide values */
 dbg_bld_expr_val(__xs, prtx, prtfmt, prtwidth, force_unsign);
 __cvsim_msg("%s\n", __xs);

 /* can free expr. */
 __free_xtree(prtx);
 __chk_extra_atend(TRUE);
}

/*
 * print an expression value for :print or :display commands
 */
static char *dbg_bld_expr_val(char *s, struct expr_t *prtx, int32 prtfmt,
 int32 prtwidth, int32 force_unsign)
{
 int32 blen;
 word32 av, bv;
 double d1;
 struct xstk_t *xsp;
 char s1[IDLEN];

 /* strength only emitted if no strength override */
 if (prtx->x_stren && prtfmt == BNONE && prtwidth == -1)
  { __strenexpr_tostr(s, prtx); return(s); }

 xsp = __eval_xpr(prtx);
 /* always print real as double - can use system task to get bit pattern */ 
 if (prtx->is_real)
  {
   memmove(&d1, xsp->ap, sizeof(double));
   sprintf(s, "%g", d1);
   goto do_prt;
  }
 
 /* print as character ignore any print width */ 
 if (prtfmt == BCHAR)
  {
   /* if has x/z, print as 8 bit binary x/z value */
   av = xsp->ap[0] & 0xff;
   bv = xsp->bp[0] & 0xff;
   if (bv != 0)
    {
     __regab_tostr(s1, &av, &bv, 8, BBIN, FALSE);
     sprintf(s, "char: [%s]", s1);
    }
   /* if non printable, print as escaped */
   /* SJM 09/19/03 - must also print new line and tab - isprint does */
   /* not include new line and tab etc. */
   else if (isprint(av) || av == '\n' || av == '\r' || av == '\t')
    sprintf(s, "\\%x", (int32) av);
   else sprintf(s, "%c", (char) av);
   goto do_prt;
  }
 /* force print as string */
 if (prtfmt == BSTR)
  {
   /* if explicit width use it and do not trim, else trim leading 0's */
   if (prtwidth == -1) blen = __trim1_0val(xsp->ap, xsp->xslen);
   else blen = prtwidth; 
   /* convert to string with escape octal for non printable */
   __strab_tostr(s, xsp->ap, blen, FALSE, FALSE);
   goto do_prt;
  }
 /* finally print according to values */
 if (prtwidth == -1) blen = xsp->xslen; else blen = prtwidth;
 if (prtfmt == BNONE) prtfmt = __dbg_dflt_base;
 __regab2_tostr(s, xsp->ap, xsp->bp, blen, prtfmt,
  (!force_unsign) ? TRUE : FALSE, (prtwidth == -1) ? 0 : -1);

do_prt:
 __pop_xstk();
 return(s);
}

/*
 * read and parse an interactive debugger expression
 * expects first token to have been read
 * this must be run in right scope
 */
extern struct expr_t *__rd_iact_expr(void)
{
 int32 sav_err_cnt;
 struct expr_t *xp;

 if (!__colto_eol()) return(NULL); 
 /* LOOKATME - needed because iact errors counted - maybe should not */ 
 sav_err_cnt = __pv_err_cnt;
 __bld_xtree(0);
 xp = __root_ndp;
 /* if already error, do not check expr. */ 
 if (__pv_err_cnt == sav_err_cnt) __chk_rhsexpr(xp, 0);
 if (__pv_err_cnt != sav_err_cnt)
  {
   __ia_err(1423, "invalid syntax in debugger expression");
   return(NULL);
  }
 return(xp);
}

/*
 * for debugger collect expression to end of line
 * expects 1st token to have been read
 * if in file or interactive tty, same eof on end of line
 */
extern int32 __colto_eol(void)
{
 for (__last_xtk = -1;;)
  {
   if (__toktyp == TEOF) return(TRUE);
   if (__toktyp == SEMI)
    {
     __ia_err(1487, "semicolon illegal end of interactive expression");
     goto bad_end;  
    }
   if (!__bld_expnode()) goto bad_end;
   __get_vtok();
  }

bad_end:
 __set_xtab_errval();
 return(FALSE);
}

/*
 * ROUTINES TO IMPLEMENT DISPLAY COMMANDS
 */

/*
 * set up display of expr on any interactive entry - know :display read 
 *
 * always print on start
 * format - :display/[d,u,b,h(x),s,c]#[bits] <expr> 
 */
static void dbg_display(void)
{
 int32 prtfmt, prtwidth, force_unsign;
 struct expr_t *prtx;
 struct dispx_t *dxp;

 __get_vtok();
 if (__toktyp == TEOF)
  {
   /* display all current non disable display expressions */
   prt_all_disp_exprs();
   return;
  }

 prtfmt = BNONE;
 prtwidth = -1;
 force_unsign = FALSE;
 if (__toktyp == DIV)
  {
   __get_vtok();
   if (__toktyp == ID)
    {
     if (strlen(__token) > 1)
      {
bad_prt_typ:
       __ia_err(1425, ":display type selector /%s illegal", __token); 
       return;
      }
     switch (__token[0]) {
      case 'd': prtfmt = BDEC; break; 
      case 'u': prtfmt = BDEC; force_unsign = TRUE; break; 
      case 'o': prtfmt = BOCT; break;
      case 'b': prtfmt = BBIN; break; 
      case 'h': case 'x': prtfmt = BHEX; break;
      case 's': prtfmt = BSTR; break; 
      case 'c': prtfmt = BCHAR; break;
      default: goto bad_prt_typ;
     }
    }
   else
    {
     __ia_err(1426,
      ":display type selector / not followed by format letter - %s read",
      __prt_vtok());
     return;
    }
   __get_vtok();
  }
 /* handle optional #<width> */ 
 if (__toktyp == SHARP)
  {
   __get_vtok();
   if (__toktyp != NUMBER || __itoklen > WBITS || __bcwrk[0] != 0L)  
    { 
     __ia_err(1427, ":display width override # not followed by legal number");
     return;
    }
   prtwidth = (int32) __acwrk[0];
   __get_vtok();
  }
 /* if collect returns F, if NULL, know error emitted in routine */
 /* notice here if value, cannot free - need the iatok ptr allocated value */
 if ((prtx = __rd_iact_expr()) == NULL) return;

 /* add to display list but do not print anything */
 dxp = (struct dispx_t *) __my_malloc(sizeof(struct dispx_t));
 dxp->dsp_enable = TRUE;
 dxp->dsp_frc_unsign = force_unsign;
 dxp->dsp_num = __nxt_dispxnum++;
 dxp->dsp_prtfmt = prtfmt; 
 dxp->dsp_prtwidth = prtwidth; 
 dxp->dsp_xp = prtx;
 /* need to eval. in this instance (or use as start pt. for xmr) */
 dxp->dsp_idp = __idp;
 dxp->dsp_tskp = __scope_tskp;
 /* behavior is to print last first so need to put on front */
 dxp->dsp_nxt = __dispxhdr;
 __dispxhdr = dxp;
 __chk_extra_atend(TRUE);
}

/*
 * print all expressions for display - prints nothing if none
 */
static void prt_all_disp_exprs(void)
{
 struct dispx_t *dxp;
 char s1[RECLEN];
 decl_idp_locals_;

 save_idp_();
 for (dxp = __dispxhdr; dxp != NULL; dxp = dxp->dsp_nxt) 
  {
   /* if disabled, do not print anything */
   if (!dxp->dsp_enable) continue;

   set_idp_(dxp->dsp_idp);
   dbg_bld_expr_val(__xs, dxp->dsp_xp, dxp->dsp_prtfmt,
    dxp->dsp_prtwidth, (dxp->dsp_frc_unsign) ? TRUE : FALSE);
   __cvsim_msg("%d:%s %s = %s\n", dxp->dsp_num, 
    bld_prtbasecode(s1, dxp->dsp_prtfmt, (dxp->dsp_frc_unsign) ? TRUE : FALSE,
    dxp->dsp_prtwidth), __msgexpr_tostr(__xs2, dxp->dsp_xp), __xs);
  }
 restore_idp_();
}

/*
 * convert debug base code and width to string or empty string if none
 */
static char *bld_prtbasecode(char *s, int32 bcod, int32 force_unsign, int32 prtwidth)
{
 char s1[RECLEN];

 switch ((byte) bcod) {
  case BBIN: strcpy(s, " /b"); break;
  case BHEX: strcpy(s, " /x"); break;
  case BDEC: 
   if (force_unsign) strcpy(s, " /u");
   else strcpy(s, " /d"); break;
  case BOCT: strcpy(s, " /o"); break;
  case BSTR: strcpy(s, " /s"); break;
  case BCHAR: strcpy(s, " /c"); break;
  case BNONE: strcpy(s, ""); break;
  default: strcpy(s, "?"); __case_terr(__FILE__, __LINE__); 
 }
 if (prtwidth == -1) return(s);
 strcpy(s1, s);
 sprintf(s, "%s #%d", s1, prtwidth);
 return(s);
}

/*
 * MISCELLANEOUS DEBUGGER EXPRESSION ROUTINES
 */

/*
 * emit description of expression information
 * notice expression must be variable not scope - no way to parse and
 * distinguish case where numeric expr. or scope can be mixed in Verilog
 */
static void do_dbg_expris(void)
{
 struct expr_t *prtx;
 char s1[RECLEN];

 __get_vtok();
 if ((prtx = __rd_iact_expr()) == NULL) return;
 __cvsim_msg("%s\n", bld_expr_telltale(s1, prtx));
 __chk_extra_atend(TRUE);
}

/*
 * build an expression tell tale
 */
static char *bld_expr_telltale(char *s, struct expr_t *xp)
{
 sprintf(s, "<top operator %s width %d", __to_opname(xp->optyp),
  xp->szu.xclen);
 if (xp->has_sign) strcat(s, " signed");
 if (xp->optyp == NUMBER || xp->optyp == ISNUMBER)
  {
   if (xp->is_string) strcat(s, " string");
   if (!xp->unsiznum) strcat(s, " explicit width");
   if (xp->sizdflt) strcat(s, " default width");
  } 
 if (xp->is_real) strcat(s, " real"); 
 if (xp->x_multfi) strcat(s, " fi>1 or tran wire");
 if (xp->x_stren) strcat(s, " has strength wire");
 if (xp->tf_isrw) strcat(s, " tf_ argument lvalue");
 if (xp->locqualnam) strcat(s, " local qualified name");
 if (xp->x_is2state) strcat(s, " expr 2state");
 strcat(s, ">");
 return(s);
}

/*
 * emit description of variable information
 */
static void do_dbg_varis(void)
{ 
 struct net_t *np;
 struct expr_t *prtx;
 struct sy_t *scope_syp;

 __get_vtok();
 if ((prtx = __rd_iact_expr()) == NULL) return;
 if (prtx->optyp != ID)
  {
   __ia_err(1465, ":varis argument %s illegal - must be variable name",
    __msgexpr_tostr(__xs, prtx));
   return;
  }
 np = prtx->lu.sy->el.enp;
 if (__last_iasytp == NULL) __misc_terr(__FILE__, __LINE__);
 scope_syp = __last_iasytp->sypofsyt;
 print_iddecl_ref(np->nsym, scope_syp);
 __chk_extra_atend(TRUE);
}

/*
 * print out a variable information line
 *
 * for module or system tf, scope is nil 
 * for variable, scope is declaration symbol table (mod or task)
 * for user task/funct, scope is containing module (or task/func/named block) 
 * for symbol declared in named block
 */
static void print_iddecl_ref(struct sy_t *syp, struct sy_t *scope_syp)
{
 int32 nd_inst;
 struct net_t *np;
 struct mod_t *mdp;
 struct symtab_t *sytp;
 struct task_t *tskp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 mdp = NULL;
 np = NULL;
 tskp = NULL;
 nd_inst = TRUE;
 switch ((byte) syp->sytyp) {
  case SYM_M: case SYM_PRIM: case SYM_UDP: case SYM_STSK: case SYM_SF:
   /* DBG remove --- */
   if (scope_syp != NULL) __arg_terr(__FILE__, __LINE__);
   /* --- */
   nd_inst = FALSE;
   sprintf(s1, "%s %s", __to_sytyp(s2, syp->sytyp), syp->synam);
   if (syp->sy_giabase) strcat(s1, " (array of primitives base)");
   break;
  case SYM_I: case SYM_TSK: case SYM_F:
   /* DBG remove --- */
   if (scope_syp == NULL) __arg_terr(__FILE__, __LINE__);
   /* --- */
   sprintf(s1, "%s %s", __to_sytyp(s2, syp->sytyp), syp->synam);
   if (syp->sy_giabase) strcat(s1, " (instance array base)");
   if (scope_syp->sytyp == SYM_M) mdp = scope_syp->el.emdp;
   else mdp = scope_syp->el.eip->imsym->el.emdp;
   break;
  case SYM_LB:
   /* DBG remove --- */
   if (scope_syp == NULL) __arg_terr(__FILE__, __LINE__);
   /* --- */
   sprintf(s1, "%s %s", __to_sytyp(s2, syp->sytyp), syp->synam);
   /* for named block, can be inside task or other named block */
   if (scope_syp->sytyp == SYM_M) mdp = scope_syp->el.emdp; 
   else
    {
     tskp = scope_syp->el.etskp;
     for (sytp = tskp->tsksymtab;; sytp = sytp->sytpar)
      {
       /* DBG remove --- */
       if (sytp == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       if (sytp->sypofsyt->sytyp == SYM_M) break;
      }
     mdp = sytp->sypofsyt->el.emdp;
    }
   break; 
  case SYM_N:
   /* DBG remove --- */
   if (scope_syp == NULL) __arg_terr(__FILE__, __LINE__);
   /* --- */
   np = syp->el.enp;
   __bld_showvars_prefix(s1, np, NULL);
   if (scope_syp->sytyp == SYM_M) mdp = scope_syp->el.emdp;
   else
    {
     tskp = scope_syp->el.etskp;
     for (sytp = tskp->tsksymtab;; sytp = sytp->sytpar)
      {
       /* DBG remove --- */
       if (sytp == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       if (sytp->sypofsyt->sytyp == SYM_M) break;
      }
     mdp = sytp->sypofsyt->el.emdp;
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (scope_syp == NULL) { __cvsim_msg(" %s (top level object)\n", s1); }
 else
  {
   __cvsim_msg("%s in %s %s %s\n", s1,
    __to_sytyp(s2, scope_syp->sytyp), scope_syp->synam,
    __bld_lineloc(s3, syp->syfnam_ind, syp->sylin_cnt));
   if (nd_inst)
    {
     __cvsim_msg("  [one instance: %s.%s]\n", 
      __msg_blditree(s2, mdp->moditps[0], tskp), syp->synam);
    }
  }
}

/*
 * emit information on every declaration of variable 
 */
static void do_dbg_whatis(void)
{ 
 int32 not_defed;
 struct mod_t *mdp;  
 struct task_t *tskp;
 struct sy_t *syp;

 not_defed = TRUE;
 __get_vtok();
 if (__toktyp != ID)
  {
   __ia_err(1465, ":whatis argument %s illegal - must be legal identifier",
    __prt_vtok());
   return;
  }
 /* first look in top level symbol tables (top level object) */
 if ((syp = __get_sym(__token, __modsyms)) != NULL)
  { print_iddecl_ref(syp, (struct sy_t *) NULL); not_defed = FALSE; }

 /* look in system functions and tasks */
 if ((syp = __get_sym(__token, __syssyms)) != NULL)
  { print_iddecl_ref(syp, (struct sy_t *) NULL); not_defed = FALSE; }

 /* next look in each module's symbol table */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if ((syp = __get_sym(__token, mdp->msymtab)) != NULL)
    {
     print_iddecl_ref(syp, mdp->msym);
     not_defed = FALSE;
    }
  }
 /* finally look at tasks and functions in every module */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if ((syp = __get_sym(__token, tskp->tsksymtab)) != NULL)
      {
       print_iddecl_ref(syp, tskp->tsksyp);
       not_defed = FALSE;
      }
    }
  }
 if (not_defed) __cvsim_msg("%s undefined\n", __token);
 __chk_extra_atend(TRUE);
}

/*
 * ROUTINES TO IMPLEMENT VPI_ SIM CONTROL INTERACTIVE ROUTINES  
 */

/*
 * execute $stop (schedule it) from user vpi_ code 
 */
extern int32 __do_vpi_stop(int32 diag_level)
{
 if (__no_iact)
  {
   __emit_vpi_noiact_warn();
   return(TRUE);
  }
 if (__iact_state)
  {
   __emit_vpi_iniact_warn();
   return(FALSE);
  }
 if (diag_level >= 1)
  {
   if (!__quiet_msgs) __cv_msg("\n");
   __cv_msg("vpi_control vpiStop executed at time %s.\n",
    __to_timstr(__xs, &__simtime));
  }
 if (diag_level >= 2) __emit_stsk_endmsg();

 /* must leave signal on - if ^c hit before stop, same effect */
 /* but entry reason different and lost */
 __pending_enter_iact = TRUE;
 __iact_reason = IAER_STOP;
 return(TRUE);
}

/*
 * do a reset from user vpi_ code (it's immediate)
 */
extern void __do_vpi_reset(int32 stop_val, int32 reset_val, int32 diag_level)
{
 int32 enter_iact;

 if (diag_level >= 1)
  {
   if (!__quiet_msgs) __cv_msg("\n");
   __cv_msg("vpi_control vpiReset executed at time %s.\n",
    __to_timstr(__xs, &__simtime));
  }
 if (diag_level >= 2) __emit_stsk_endmsg();

 /* enter interactive unless reset value non zero */
 if (stop_val != 0) enter_iact = FALSE; else enter_iact = TRUE;
 if (enter_iact) __stop_before_sim = TRUE; else __stop_before_sim = FALSE;

 /* record state changes caused by arguments */
 __reset_value = reset_val;

 /* reenable the normal ^c signal handler - when variables reset */
 /* sim will replace with sim handler for entering interactive */
#ifndef __NOSIGS__
#if defined(INTSIGS)
 signal(SIGINT, __comp_sigint_handler);
#else
 signal(SIGINT, (void (*)()) __comp_sigint_handler);
#endif
#endif

 /* this does not return - uses lng jmp */
 longjmp(__reset_jmpbuf, 1);
}
