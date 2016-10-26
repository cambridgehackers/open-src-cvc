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
 * file contains compiler miscellaneous routines for design wide compile
 * preparation, for build net list object comm area reference names 
 * and for dumping and freeing compiler data structures
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <dlfcn.h> 
#include <stdarg.h>
#include <unistd.h> 
#include <errno.h> 

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

int32 *__asl_info_map;    /* map of routine number to table index */
int32 __max_asl_rout_num; /* max asl routine number */
int32 __needs_thread_ctrl; /* T => block needs thread control */

int32 __avl_node_is_new; /* T avl tree find added the node */
struct avlnode_t **__avltab; /* array for linearized avl tree */
int32 __avltabsiz;     /* current malloced work tab size */ 
int32 __avl_lasti;     /* last allocated */
struct avlnode_t *__tmp_avl_hd;  /* tmp for balance avl tree */

/* internal run time work variables (regs) */
//AIV64 __nchged_i1 - int32/word32????????
#ifdef __CVC32__
int32 __nchged_i1;     /* RT - access to rng form nchg lp */
int32 __nchged_i2;     /* and low end of range */
#else
word32 __nchged_i1;     /* RT - access to rng form nchg lp */
word32 __nchged_i2;     /* and low end of range */
#endif
/* AIV 02/21/09 - this needs to be word32/ 64-bit */
word32 __nchged_delayed_mipd; /* and 2nd time thru mipd flag */
struct net_pin_t *__cur_npp; /* cur runtime net pin */
int32 __nchg_tevpi;
word64 __nb_const_last_time; /* last nb assign time */
int32  __all_nb_same_time;   /* nb assign const all same time */

word32 *__ebp;         /* dummy asm stack base for gdb debugging */

void *__process_nbpa_varndx_ev_enterp;
void *__process_next_event_free_enterp;

struct nchglst_t *__next_nchglp; /* next processing nchglp */
void *__process_next_nchg_enterp; /* process next nchg enter ptr */
void *__first_enterp; /* the first sim process entered */

struct heap_t *__last_nb_hp; /* last non-blocking heap inserted time */

struct nchglst_t __nchg_dummy_hd; /* dummy header for nchgs */
struct tev_t __pnd0_dummy_hd; /* dummy header for pnd0 events */
struct tev_t __nb_dummy_hd; /* dummy header for nb events */

struct task_t *__save_scope_tskp; /* save from $scope task if present */ 

int32 __gening_tsk;    /* T => generating insn inside task body */
struct mod_t *__init_mdp;  /* module glbl for init code */


static void set_stlst_ent_bits(struct mod_t *, struct st_t *);
static struct st_t *set_1stmt_ent_bit(struct mod_t *, struct st_t *);
static struct avlnode_t *obj_node_alloc(void *);
static cmpsword obj_node_cmp(const void *, const struct avlnode_t *);
static void addto_avltab(struct avlnode_t *);
static void avl_one_rot(struct avlnode_t *, struct avlnode_t *, 
 struct avlnode_t *);
static void avl_two_rot(struct avlnode_t *, struct avlnode_t *,
 struct avlnode_t *);
static void init_dummy_tevp(struct tev_t *);

extern void __set_mod_ent_bits(struct mod_t *);
extern void __free_mod_npp_dce_table(void);
extern void __free_sysfcall_expr(void);
extern struct avlhd_t *__allocinit_avlhd(void);
extern struct prep_obj_t *__find_add_obj(struct avlhd_t *, void *);
extern void __add_isnum_to_tree(void *, int32, int32);
extern struct avlnode_t **__linearize_avl_tree(struct avlhd_t *, int32 *);
extern void __grow_avltab(void);
extern struct net_chg_t *__find_nchg_range(struct net_t *, int32, int32);
extern void __push_cc_stmt(struct st_t *);
extern void __pop_cc_stmt(void);
extern struct avlnode_t *__avltfind(void *, struct avlhd_t *);
extern struct avlnode_t *__alloc_avlnode(void *);
extern struct st_t *__find_stlst_end(struct st_t *);
extern struct st_t *__find_after_tsk_nxtstmt(struct st_t *);
extern int32 __net_chg_nd_store(struct net_t *, int32, int32);
extern int32 __needs_netchg_record(struct net_t *);
extern void __setup_dummy_events(void);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern int32 __set_mark_mdprt_flags(struct net_pin_t *, int32 *, int32 *, 
 int32 *, int32 *, int32 *, int32 *, int32 *, int32 *, int32 *);
extern int32 __get_lhs_srep(struct expr_t *, int32 *);
extern int32 __get_array_srep_type(struct net_t *);
extern int32 __is_expr_2state(struct expr_t *);
extern int32 __get_tmpfnam(char *);


extern void __crit_msg(char *, ...);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
/*
 * ROUTINES TO SET BIT IN EVERY STMT ENTERABLE FROM SCHEDULER
 * CALLED BEFORE ANY CODE GEN
 */ 

/*
 * set enter from scheduler bit for all stmts that
 * start timing free (no suspend to scheduler) stmt blocks
 */
extern void __set_mod_ent_bits(struct mod_t *mdp)
{
 struct ialst_t *ialp;
 struct task_t *tskp;
 struct st_t *stp;
 struct delctrl_t *dctp, *head_dctp;
 int32 iatyp;

 __needs_thread_ctrl = FALSE;
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)  
  {
   /* first stmt always entry point */
   stp = ialp->iastp;
   /* must add also set the for this module sequence number */
   /* DBG remove -- */
   if (stp->is_enter) __misc_terr(__FILE__, __LINE__);
   /* --- */
   stp->is_enter = TRUE;
   set_stlst_ent_bits(mdp, ialp->iastp);

   /* AIV 05/14/07 - must mark block that calls a function as using the */
   /* thread mechanism - because functions which use a name block */
   /* need to access __cur_thrd for return location */
   /* AIV FIXME - if known not to have named block wouldn't need */
   if (!ialp->needs_thread) 
    {
     ialp->needs_thread = __needs_thread_ctrl;
    }
   /* AIV 03/03/09 - for every always @ if needs thread control */
   /* cannot merge the blocks so need to mark dctp with need thread */
   /* to not merge into one fg later in gen code */
   iatyp = ialp->iatyp;
   /* AIV 07/12/12 - now supporting new SV always_* types */
   if ((iatyp == ALWAYS || iatyp == ALWAYS_COMB || iatyp == ALWAYS_FF || 
    iatyp == ALWAYS_LATCH) && ialp->needs_thread) 
    {
     if (ialp->iastp->stmttyp == S_DELCTRL)
      {
       dctp = ialp->iastp->st.sdc;
       /* mark each block which has been merged from the header */
       if (dctp != NULL && dctp->dctyp == DC_EVENT)
        {
         if (dctp->head_dctp != NULL) head_dctp = dctp->head_dctp;
         else head_dctp = dctp;

         head_dctp->needs_thread = TRUE;
         dctp = head_dctp->merged_dctp; 
         for (; dctp != NULL; dctp = dctp->merged_dctp)
          {
           dctp->needs_thread = TRUE;
          }
        }
      }
    }
   /* AIV 07/09/08 - need to reset needs thread ctrl to false - used for */
   /* for each init/always */
   __needs_thread_ctrl = FALSE;
  }
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   /* labeled blocks and forks are gened inline */
   if (tskp->tsktyp == Begin || tskp->tsktyp == FORK) continue;
   /* if task is never used continue since code is never lowered */
   if (!tskp->t_used) continue;

   /* func call and task enable suspend at end because takes over */
   /* thread after adjusting to continue just after task */
   /* SJM 03/30/04 - LOOKATME - func exec code slow because need to */
   /* step through it in interpreter - need to use cpu mechanism */
   if (tskp->tsktyp == FUNCTION)
    {
     /* SJM 03/30/04 - is this needed */
     __processing_func = TRUE;
     set_stlst_ent_bits(mdp, tskp->tskst);
     __processing_func = FALSE;
    }
   else
    {
     /* need to mark enter from scheduler only for non system tasks */
     __gening_tsk = TRUE;
     set_stlst_ent_bits(mdp, tskp->tskst);
     __gening_tsk = FALSE;
    }
  }
 /* AIV 08/30/08 - need to reset needs thread ctrl to false - used for */
 /* global flag during code generation as well */
 __needs_thread_ctrl = FALSE;
}

/*
 * set enter from scheduler bits for each stmt in list of stmts 
 */
static void set_stlst_ent_bits(struct mod_t *mdp, struct st_t *hdstp)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = set_1stmt_ent_bit(mdp, stp);
  }
}

/*
 * set the scheduler can enter at stmt bit for one stmt
 *
 * called only for stmts where bit not already set
 */
static struct st_t *set_1stmt_ent_bit(struct mod_t *mdp, struct st_t *stp)
{
 int32 fji;
 struct st_t *astp, *fjstp, *cont_stp, *end_stp, *nxtstp;
 struct csitem_t *csip, *dflt_csip;
 struct delctrl_t *dctp;
 struct tskcall_t *tkcp;
 struct expr_t *tkxp;
 struct task_t *tskp;
 struct systsk_t *stbp;
 struct sy_t *tsyp;
 
 cont_stp = NULL;
 switch ((byte) stp->stmttyp) {
  case S_RHSDEPROCA:
   /* DBG remove -- */
   if (!stp->is_enter) __misc_terr(__FILE__, __LINE__);
   /* --- */
   stp->is_enter = TRUE;
   break;
  case S_NBPROCA:
   /* check if already added - may already be added due to nb S_REPDCSETUP */
   stp->is_nb_enter = TRUE;
   break;
  case S_IF:
   set_stlst_ent_bits(mdp, stp->st.sif.thenst);
   if (stp->st.sif.elsest != NULL)
    {
     set_stlst_ent_bits(mdp, stp->st.sif.elsest);
    }
   break;
  case S_CASE:
   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
    {
     set_stlst_ent_bits(mdp, csip->csist);
    } 
   if (dflt_csip->csist != NULL && dflt_csip->csist->stmttyp != S_NULL)
    {
     set_stlst_ent_bits(mdp, dflt_csip->csist);
    }
#ifdef __XPROP__
   /* AIV 08/02/11 - now might have xprop list to process as well */
   if (stp->st.scs.xprop_lstp != NULL)
    {
     set_stlst_ent_bits(mdp, stp->st.scs.xprop_lstp);
    }
#endif
   break; 
  case S_FOREVER:
   set_stlst_ent_bits(mdp, stp->st.swh.lpst);
   break;
  case S_REPEAT: 
   set_stlst_ent_bits(mdp, stp->st.srpt.repst);
   break;
  case S_WHILE:
  case S_DO_WHILE:
   set_stlst_ent_bits(mdp, stp->st.swh.lpst);
   break;
  case S_FOR:
   set_stlst_ent_bits(mdp, stp->st.sfor->forbody);
   break;
  case S_WAIT:
   /* here end of wait loop suspends with entry again at first stmt of wait */
   /* AIV 05/16/06 - if stmt enter code is already set by wait is the first */
   /* stmt in an initial block don't reset */
   stp->is_enter = TRUE;
   set_stlst_ent_bits(mdp, stp->st.swh.lpst);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   if (dctp->dctyp == DC_DELAY || dctp->dctyp == DC_EVENT)
    {
     astp = dctp->actionst;
     if (astp == NULL) 
      {
       stp->stnxt->is_enter = TRUE; 
      }
     else 
      {
       astp->is_enter = TRUE; 
      }
#ifdef __XPROP__
   /* have new xprop edge handling fg enter */
   if (dctp->xprop_xedge_actionst)
    {
     /* DBG remove -- */
     if (dctp->dctyp != DC_EVENT) __misc_terr(__FILE__, __LINE__);
     /* --- */
     astp = dctp->xprop_xedge_actionst;
     if (astp == NULL) stp->stnxt->is_enter = TRUE; 
     else astp->is_enter = TRUE; 
    }
#endif
     cont_stp = astp;
    }
   else
    {
     /* handle rhs forms */
     astp = stp->st.sdc->actionst;
     /* DBG remove -- */
     if (astp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     if (astp->stmttyp == S_RHSDEPROCA)
      {
       astp->is_enter = TRUE; 
       cont_stp = astp;
      }
     /* if non blocking no entry bit to set but must cont at right stmt */
     else if (astp->stmttyp == S_NBPROCA)
      {
       set_1stmt_ent_bit(mdp, astp);
       cont_stp = astp->stnxt;
      }
     else __case_terr(__FILE__, __LINE__);
    }
   return(cont_stp);
  case S_NAMBLK:
   /* need thread info named blocks */
   /* AIV 08/08/09 - only need the thread control if disabled or has scope */
   /* was doing this for all named blocks */
   tskp = stp->st.snbtsk;
   /* AIV 03/10/09 - if named block doesn't have delay but uses scope */
   /* no longer need thread mechanism */
   /* AIV 04/13/10 - if automatic tasks need to be thread control */
   if ((tskp->uses_scope && !tskp->no_delay) || tskp->can_be_disabled 
        || tskp->is_auto) 
    {
     __needs_thread_ctrl = TRUE;
    }
   /* named block takes over thread and can be disable - but never */
   /* entered from scheduler */
   if (__processing_func || (!__gening_tsk && !tskp->can_be_disabled)) 
    {
     if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);
     set_stlst_ent_bits(mdp, tskp->tskst);
     if (stp->stnxt != NULL) __pop_cc_stmt();
     break;
    }
   if (stp->stnxt != NULL && tskp->can_be_disabled)
    {
     stp->stnxt->is_enter = TRUE; 
    }
   set_stlst_ent_bits(mdp, tskp->tskst);
   break;
  case S_UNBLK:
   if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);
   set_stlst_ent_bits(mdp, stp->st.sbsts);
   if (stp->stnxt != NULL) __pop_cc_stmt();

   end_stp = __find_stlst_end(stp->st.sbsts);
   /* DBG remove -- */
   if (end_stp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (end_stp->stmttyp == S_GOTO)
    {
     if (end_stp->dctrl_goto) break;
    }
   break;
  case S_UNFJ:
   /* need thread info for fork/join */
   __needs_thread_ctrl = TRUE;
   for (fji = 0;; fji++)
    {
     /* first stmt of fork-join prong always entered from scheduler */
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;

     /* if this is named blocked adjust in next routine */
     if (fjstp->stmttyp == S_UNBLK)
      {
       fjstp->st.sbsts->is_enter = TRUE;
       set_stlst_ent_bits(mdp, fjstp->st.sbsts);
      }
     else 
      {
       fjstp->is_enter = TRUE;
       set_stlst_ent_bits(mdp, fjstp);
      }
    }
   /* AIV LOOKATME - is this needed - double mark won't hurt ??? */
   if (stp->stnxt != NULL)
    {
     stp->stnxt->is_enter = TRUE;
    }
   break;
  case S_TSKCALL:
  case S_FUNCCALL:
   tkcp = &(stp->st.stkc);
   tkxp = tkcp->tsksyx;
   tsyp = tkxp->lu.sy;
//AIV FIXME - showvars accesses __cur_thrd via task call wrapper
//AIV LOOKATME - more wrappers probably need as well????
   if (tsyp->sytyp == SYM_STSK)
    {
     stbp = tsyp->el.esytbp;
     /* AIV 08/21/07 - currently dumpvars wrapper call needs thread as well */
     //AIV LOOKATME - why is this the case???
     if (stbp->stsknum == STN_SHOWVARS || stbp->stsknum == STN_DUMPVARS
      || stbp->stsknum == STN_FST_DUMPVARS
      || stbp->stsknum == STN_DUMPPORTS)
      {
       __needs_thread_ctrl = TRUE;
      }
     /* AIV 05/17/07 - if PLI call don't know if needs thread so must leave */
     /* AIV LOOKATME - can check PLI code for access to thread????? */
     else if (!(stbp->stsknum < BASE_VERIUSERTFS 
       || (int32) stbp->stsknum > __last_systf))
      {
       __needs_thread_ctrl = TRUE;
      }
     break;
    }
   /* AIV 07/26/07 - currently if the block calls a xmr task must is */
   /* saving the return to area in __cur_thread */
   /* AIV FIXME - should just use one static address????? */
   else if (tkxp->optyp == GLBREF)
    {
     __needs_thread_ctrl = TRUE;
    }
   tskp = tkxp->lu.sy->el.etskp;
   /* AIV 05/29/07 - only if any of these flags does a task need thread */
   /* control mechanism */
   /* AIV 03/10/09 - if named block doesn't have delay but uses scope */
   /* no longer need thread mechanism */
   /* AIV 04/13/10 - if automatic tasks need to be thread control */
   if (!tskp->no_delay || tskp->can_be_disabled || !tskp->no_xmrcall || 
       tskp->is_auto)
    {
     __needs_thread_ctrl = TRUE;
     nxtstp = __find_after_tsk_nxtstmt(stp);
     /* AIV 05/16/06 - the nxtstp could already be entered here */
     if ((__gening_tsk || tskp->can_be_disabled) && nxtstp != NULL)
      {
       nxtstp->is_enter = TRUE;
      }
    }
   /* AIV 10/08/06 - was incorrectly returning nxtstp - causing incorrect */
   /* recursion for ifs/task just need next stmt */
   break;
  case S_GOTO: 
   if (stp->dctrl_goto) return(stp->st.sgoto);
   break;
  case S_REPDCSETUP:
   /* AIV 12/12/07 - need to set enter point for non-blocking rep dce */
   nxtstp = stp->stnxt;
   astp = nxtstp->st.sdc->actionst;
   if (astp->stmttyp == S_NBPROCA)
    {
     /* DBG remove -- */
     if (stp->is_nb_enter) __misc_terr(__FILE__, __LINE__);
     /* --- */
     stp->is_nb_enter = TRUE; 
    }
   break;
  default: break;
 }
 return(stp->stnxt);
}

/*
 * free all the modules npp and dce load storage struct
 */
extern void __free_mod_npp_dce_table(void)
{
 struct dce_info_t *dceip;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct net_t *np;
 int32 ni;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
    {
     dceip = np->dcetable;
     if (dceip != NULL)
      {
       __my_free(dceip->dtable, dceip->size*sizeof(struct dcevnt_t *));
       __my_free(dceip, sizeof(struct dcevnt_t *));
       np->dcetable = NULL;
      }
     }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       dceip = np->dcetable;
       if (dceip != NULL)
        {
         __my_free(dceip->dtable, dceip->size*sizeof(struct dcevnt_t *));
         __my_free(dceip, sizeof(struct dcevnt_t *));
         np->dcetable = NULL;
        }
      }
    }
  }
}

/*
 * free the sys function call expression table
 * AIV LOOKATME - this can go when sys calls are lowered
 */
extern void __free_sysfcall_expr(void)
{
 struct mod_t *mdp;
 struct expr_tab_t *etp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if ((etp = mdp->expr_tab) == NULL) continue;
   __my_free(etp->table, etp->size*sizeof(struct expr_t *));
   __my_free(etp, sizeof(struct expr_tab_t));
   mdp->expr_tab = NULL;
  }
}

/*
 * initialize a tn dup avl tree header
 */
extern struct avlhd_t *__allocinit_avlhd(void)
{
 struct avlhd_t *avlhdp;

 avlhdp = (struct avlhd_t *) __my_malloc(sizeof(struct avlhd_t));
 avlhdp->num_nodes = 0;
 avlhdp->avl_cmp = NULL;
 avlhdp->avl_alloc = NULL;
 avlhdp->avl_root = NULL;
 return(avlhdp);
}

/*
 * add an object (pointer) struct to the tree
 */
extern struct prep_obj_t *__find_add_obj(struct avlhd_t *avlhp, void *obj)
{
 struct prep_obj_t *pop, tmp_obj;
 struct avlnode_t *avlp;

 tmp_obj.obj = obj;
 if (avlhp->num_nodes == 0)
  {
   /* case 1: tree is empty */
   avlhp->num_nodes = 1;
   avlhp->avl_cmp = obj_node_cmp;
   avlhp->avl_alloc = obj_node_alloc;
   avlhp->avl_root = obj_node_alloc(&(tmp_obj));
   pop = (struct prep_obj_t *) avlhp->avl_root->valp;
   __avl_node_is_new = TRUE;
   return(pop);
  }

 __avl_node_is_new = FALSE;
 /* if can't find, inserts new node in avl tree, fills and sets node is new */
 avlp = __avltfind(((void *) &(tmp_obj)), avlhp);
 pop = (struct prep_obj_t *) avlp->valp;
 return(pop);
}

/*
 * compare an object node
 */
static cmpsword obj_node_cmp(const void *valp, const struct avlnode_t *nodp)
{
 cmpsword cv;
 struct prep_obj_t *p1, *p2;

 p1 = (struct prep_obj_t *) valp;
 p2 = (struct prep_obj_t *) nodp->valp;
 /* AIV 11/10/08 - need to cast the expr_ to word * to do the compare */
 cv = ((cmpsword *) p1->obj - (cmpsword *) p2->obj);
 return(cv);
}

/*
 * alloc an object node
 */
static struct avlnode_t *obj_node_alloc(void *tnsydup)
{
 struct prep_obj_t *newp, *oldp;
 struct avlnode_t *nodp;

 oldp = (struct prep_obj_t *) tnsydup;
 newp = (struct prep_obj_t *) __my_malloc(sizeof(struct prep_obj_t));
 *newp = *oldp;
 nodp = __alloc_avlnode((void *) newp);
 return(nodp);
}

/*
 * add an IS number to the tree
 * passed an obj (npp, dce, expr) and the constant index and its size
 * each module has its own inum tree to later be placed into idp area
 *
 */
extern void __add_isnum_to_tree(void *obj, int32 xvi, int32 size)
{
 struct prep_obj_t *pop;

 /* mod doesn't yet have a tree allocated */
 if (__inst_mod->isnum_tree == NULL)
  {
   __inst_mod->isnum_tree = __allocinit_avlhd();
  }
 /* add the IS number object saving size and index into __contab */
 pop = __find_add_obj(__inst_mod->isnum_tree, obj);
 pop->blen = size;
 pop->xvi = xvi;
 /* AIV 12/01/09 - need to record order added by num nodes */
 /* need to sort with these so then executable runs idp ofs are the same */
 pop->id = __inst_mod->isnum_tree->num_nodes;
 __inst_mod->isnum_tree->num_nodes++;
}

/*
 * no longer have igen aux for nets to store need of chg store
 * routine needs to be called instead if needed
 */
extern int32 __net_chg_nd_store(struct net_t *np, int32 i1, int32 i2)
{
 struct net_chg_t *ncp;
 int32 ni1, ni2;

 /* AIV 01/26/12 - access level >= 1 for change record */
 if (np->pli_access >= 1) return(TRUE);

 /* AIV 12/20/07 - if dumpvars in source always need the record */
 /* AIV 10/15/08 - must check for dumpports in source as well */
 if (np->dmpv_in_src || np->dmpp_in_src) return(TRUE);
 /* AIV 12/06/10 - if has toggle coverage need to check for changes */ 
 if (np->n_has_toggle) return(TRUE);

 if (np->nchg_nd_chgstore || np->nchg_has_dces || np->monit_in_src) 
  {
   if (i1 == -1 || i2 == -1) return(TRUE);
   for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
    {
     ni1 = ncp->i1;
     ni2 = ncp->i2;
     /* if recorded change is a variable and passed constant don't need rec */
     if (ncp->is_const) 
      {
       if (ni1 == -1 || ni2 == -1) return(TRUE);
      }
     if (i1 < ni2 || i2 > ni1) continue;
     return(TRUE);
    }
   //if (np->nchdp != NULL) __misc_terr(__FILE__, __LINE__);
   return(FALSE);
  }
 return(FALSE);
}

/*
 * return TRUE if net needs to record a change
 */
extern int32 __needs_netchg_record(struct net_t *np)
{
 int32 has_record;

 has_record = FALSE;

 /* pli access must always record change */
 /* AIV 05/13/09 - access level >= 1 for change record */
 if (np->pli_access >= 1) return(TRUE);

 if (!np->n_cause && !np->n_mipd)
  {
   /* check if net has an nchg action */
   if (np->nlds == NULL) 
    {
     if (np->dcelst == NULL)
      {
       has_record = FALSE;
      }
     else if (np->ntyp >= NONWIRE_ST) 
      {
       has_record = FALSE;
      }
     else has_record = TRUE;
     /* AIV 11/14/07 - if has force may need to propgate changes for dces */
     /* this was a problem for the new force with pass nchg code */
     /* AIV 11/21/07 - if index with var on lhs nb need need to link dces */
     if (np->frc_assgn_allocated || np->n_on_nblhs_varndx) 
      {
       has_record = TRUE;
      }
    }
   else has_record = TRUE;
  }
 else has_record = TRUE;

 return(has_record);
}

 
/*
 * return TRUE if gate stores its output value in the idp (not packed)
 */
extern int32 __gate_needs_output_word(int32 g_class)
{
 switch (g_class) {
  case GC_LOGIC:
  case GC_BUFIF:
  case GC_CMOS:
  case GC_MOS:
  case GC_UDP:
   return(TRUE);
  case GC_TRAN:
  case GC_TRANIF:
  case GC_PULL:
   return(FALSE);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}

/*
 * linearize any avl tree (really just a set) in preorder
 *
 * SJM 12/26/06 - new algorithm this fills an malloced table that is
 * returned - caller must free the returned malloced avl tab when done
 *
 * fixes problem with trying to reuse one global avl tab
 * since linearizing avl tree's rare, fills the global tab and then
 * malloc correct size table and copies into it
 */
extern struct avlnode_t **__linearize_avl_tree(struct avlhd_t *avhdp,
 int32 *siz_avltab)
{
 int32 nbytes;
 struct avlnode_t **new_avltab;

 /* tree can be alloc and empty */
 if (avhdp == NULL || avhdp->avl_root == NULL)
  {
   *siz_avltab = 0;
   return(NULL);
  }

 __avl_lasti = -1;
 addto_avltab(avhdp->avl_root);
 nbytes = (__avl_lasti + 1)*sizeof(struct avlnode_t *);
 new_avltab = (struct avlnode_t **) __my_malloc(nbytes);
 memcpy(new_avltab, __avltab, nbytes);
 *siz_avltab = __avl_lasti + 1;
 __avl_lasti = -1;

 return(new_avltab);
}

/*
 * addto defuse bblk avl tree table
 */
static void addto_avltab(struct avlnode_t *nodp)
{
 if (nodp == NULL) return;

 addto_avltab(nodp->lp); 

 /* must mark while building so lower cycles are cut */
 if (++__avl_lasti >= __avltabsiz) __grow_avltab();
 __avltab[__avl_lasti] = nodp;

 addto_avltab(nodp->rp); 
}

/*
 * grow avl tree node table for linearizing
 */
extern void __grow_avltab(void)
{
 size_t osize, nsize;

 osize = __avltabsiz*sizeof(struct avlnode_t *);
 /* flow graphs are small so grow slowly */
 __avltabsiz = (3*__avltabsiz)/2; 
 nsize = __avltabsiz*sizeof(struct avlnode_t *);
 __avltab = (struct avlnode_t **) __my_realloc(__avltab, osize, nsize);
}

/*
 * find a static net change for the passed range
 * passed -1, -1 to indicate the entire net
 * the net_chg_t are built at prep time and better exist for passed values
 *
 * AIV LOOKATME - linear search could result in performance issues
 */
extern struct net_chg_t *__find_nchg_range(struct net_t *np, int32 i1, int32 i2)
{
 struct net_chg_t *ncp;
 struct net_chg_t *entire_net_ncp;
 int32 ni1, ni2, numbits;

 /* entire_net_ncp is the entire net change */
 entire_net_ncp = NULL;
 /* first pass find exact match */
 for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
  {
   ni1 = ncp->i1;
   ni2 = ncp->i2;
   /* save the entire net change if there is one */
   if (ni1 == -1 && ni2 == -1) entire_net_ncp = ncp;
   /* AIV 09/13/10 - psel of entire net are now optimize to chg st of */
   /* the entire net */
   else 
    {
     if (ni1 > ni2) numbits = ni1 - ni2 + 1;
     else numbits = ni2 - ni1 + 1;
     if (np->nwid == numbits) entire_net_ncp = ncp;
    }
   /* found exact match return */
   if (ni1 == i1 && ni2 == i2)
    {
     ncp->is_lowered = TRUE;
     return(ncp);
    }
  }
 /* find value in given range if exact match not found */
 for (ncp = np->nchdp; ncp != NULL; ncp = ncp->nxt)
  {
   ni1 = ncp->i1;
   ni2 = ncp->i2;
   if (i1 < ni2 || i2 > ni1) continue;
   /* range found */
   ncp->is_lowered = TRUE;
   return(ncp);
  }
 /* if exact match and range not found better have an entire net change */
 /* DBG remove -- */
 if (i1 != -1 || i2 != -1) __misc_terr(__FILE__, __LINE__);
 if (entire_net_ncp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 entire_net_ncp->is_lowered = TRUE;
 return(entire_net_ncp);
}

/*
 * push a nested preparation statement
 * this is for control flow so many not pushed
 */
extern void __push_cc_stmt(struct st_t *stp)
{
 if (++__prpsti >= MAXPRPSTNEST) __misc_terr(__FILE__, __LINE__);
 __prpstk[__prpsti] = stp;
 /* DBG remove --
 if (__opt_debug_flg)
  {
   if (stp != NULL)
    {
     __my_fprintf(stdout, ".. push nested stmt stack to %d at %s\n",
      __prpsti, __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt));
    }
   else
    {  
     __my_fprintf(stdout, ".. push NULL nested stmt stack to %d\n",
      __prpsti);
    }
  }
 --- */
}

/*
 * pop a nested preparation statement
 */
extern void __pop_cc_stmt(void)
{ 
 /* should never undeflow */
 if (__prpsti < 0) __misc_terr(__FILE__, __LINE__);
 __prpsti--;
 /* DBG remove --
 if (__opt_debug_flg)
  {
   struct st_t *stp;

    stp = __prpstk[__prpsti];
    if (stp != NULL)
     {
      __my_fprintf(stdout, ".. pop nested stmt stack to %d at %s\n",
       __prpsti, __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt));
     }
    else
     {  
      __my_fprintf(stdout, ".. pop NULL nested stmt stack to %d\n",
       __prpsti);
     }
  }
 --- */
}

/*
 * find an entry in an avl node tree and add if needed
 *
 * routine same as symbol table avl tree code except values are void *
 * instead of symbol table mechanism
 *
 * if caller wants to know if node was inserted it must turn off
 * __avl_node_is_new flag before call
 *
 * the value field is set with valp but caller must fill any contents
 * of the valp field if it is a record
 */
extern struct avlnode_t *__avltfind(void *valp, struct avlhd_t *tree_rec)
{
 struct avlnode_t *cur, *down;
 struct avlnode_t *balpt_par, *bal_pt, *vtnew, *bal_down;
 cmpsword cv;

 vtnew = NULL;
 if (tree_rec->avl_root == NULL)
  {
   __avl_node_is_new = TRUE;
   tree_rec->avl_root = tree_rec->avl_alloc(valp);
   return(tree_rec->avl_root);
  }

 for (balpt_par = NULL, bal_pt = cur = tree_rec->avl_root;;)
  {
   if ((cv = tree_rec->avl_cmp(valp, cur)) == 0)
    {
     return(cur);
    }

   if (cv < 0) { cur->via_dir = BLEFT; down = cur->lp; }
   else { cur->via_dir = BRIGHT; down = cur->rp; }
   if (down == NULL)
    {
     __avl_node_is_new = TRUE;
     down = tree_rec->avl_alloc(valp);
     if (cur->via_dir == BLEFT) cur->lp = down; else cur->rp = down;
     vtnew = down;
     break;
    }
   if (down->bal != BEVEN) { balpt_par = cur; bal_pt = down; }
   cur = down;
  }

 /* bal down is one below balance point */
 if (bal_pt->via_dir == BLEFT) bal_down = bal_pt->lp;
 else bal_down = bal_pt->rp;
 /* know all nodes from bal_pt down to but not including new had balance 0 */
 /* adjust up to but not including balance of new */
 for (cur = bal_down; cur != vtnew;)
  {
   cur->bal = cur->via_dir;
   if (cur->via_dir == BLEFT) cur = cur->lp; else cur = cur->rp;
  }
 /* since only unbalanced by 1 put off doing anything */
 if (bal_pt->bal == BEVEN) { bal_pt->bal = bal_pt->via_dir; return(vtnew); }

 /* tree got more balanced */
 /* check for bal and even dir opposite or both even */
 if ((bal_pt->bal == BEVEN && bal_pt->via_dir == BEVEN)
  || (bal_pt->bal == BLEFT && bal_pt->via_dir == BRIGHT)
  || (bal_pt->bal == BRIGHT && bal_pt->via_dir == BLEFT))
  {
   bal_pt->bal = BEVEN;
   return(vtnew);
  }

 /* tree more out of balance - needs rebalancing */
 __tmp_avl_hd = tree_rec->avl_root;

 /* may rotate new node into root loc, but not passign tree rec */
 if (bal_down->bal == bal_pt->via_dir)
  avl_one_rot(bal_pt, bal_down, balpt_par);
 else avl_two_rot(bal_pt, bal_down, balpt_par);

 tree_rec->avl_root = __tmp_avl_hd;
 return(vtnew);
}

/*
 * single rotation
 * may rotate to change root node
 */
static void avl_one_rot(struct avlnode_t *bal_pt, struct avlnode_t *bal_down, 
 struct avlnode_t *balpt_par)
{
 if (bal_pt->via_dir == BLEFT)
  {
   bal_pt->lp = bal_down->rp;
   bal_down->rp = bal_pt;
  }
 else
  {
   bal_pt->rp = bal_down->lp;
   bal_down->lp = bal_pt;
  }
 bal_pt->bal = bal_down->bal = BEVEN;

 if (balpt_par == NULL) __tmp_avl_hd = bal_down;
 else if (balpt_par->via_dir == BLEFT) balpt_par->lp = bal_down;
 else balpt_par->rp = bal_down;
}

/*
 * double rotation
 * may rotate to change root node
 */
static void avl_two_rot(struct avlnode_t *bal_pt, struct avlnode_t *bal_down,
 struct avlnode_t *balpt_par)
{
 struct avlnode_t *tmp;

 if (bal_pt->via_dir == BLEFT)
  {
   tmp = bal_down->rp;
   bal_down->rp = tmp->lp;
   tmp->lp = bal_down;
   bal_pt->lp = tmp->rp;
   tmp->rp = bal_pt;
  }
 else
  {
   tmp = bal_down->lp;
   bal_down->lp = tmp->rp;
   tmp->rp = bal_down;
   bal_pt->rp = tmp->lp;
   tmp->lp = bal_pt;
  }

 /* update the balances */
 if (tmp->bal == BEVEN) bal_pt->bal = bal_down->bal = BEVEN;
 else if (tmp->bal == bal_pt->via_dir)
  {
   if (bal_pt->via_dir == BRIGHT) bal_pt->bal = BLEFT;
   else if (bal_pt->via_dir == BLEFT) bal_pt->bal = BRIGHT;
   else bal_pt->bal = BEVEN;
   bal_down->bal = BEVEN;
  }
 else { bal_pt->bal = BEVEN; bal_down->bal = bal_pt->via_dir; }
 tmp->bal = BEVEN;

 /* point node above balance point to new high node */
 if (balpt_par == NULL) __tmp_avl_hd = tmp;
 else if (balpt_par->via_dir == BLEFT) balpt_par->lp = tmp;
 else balpt_par->rp = tmp;
}

/*
 * allocate an avl tree node
 */
extern struct avlnode_t *__alloc_avlnode(void *valp)
{
 struct avlnode_t *tnp;

 tnp = (struct avlnode_t *) __my_malloc(sizeof(struct avlnode_t));
 tnp->valp = valp;
 tnp->lp = tnp->rp = NULL;
 tnp->bal = BEVEN;
 tnp->via_dir = BEVEN;
 return(tnp);
}

/*
 * routine for find the ending goto of a list of statements
 * must exist
 */
extern struct st_t *__find_stlst_end(struct st_t *hdstp)
{ 
 struct st_t *stp, *endlst_stp;

 endlst_stp = NULL;
 for (stp = hdstp; stp != NULL; stp = stp->stnxt)
  {
   endlst_stp = stp;
  }
 /* DBG remove -- */
 if (endlst_stp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 return(endlst_stp);
}

/*
 * find continuation stmt (known at compile time) for task enable 
 * for task with no outputs
 *
 * these if stmts complex and stupid but just following v ex code
 */
extern struct st_t *__find_after_tsk_nxtstmt(struct st_t *stp)
{
 struct st_t *stp2; 
 
 stp2 = stp->stnxt;
 if (stp2 == NULL) return(NULL);
 if (stp2->stmttyp != S_GOTO) return(stp2);
 if (stp2->lpend_goto) return(stp2);

 for (;;)
  {
   /* know on entry stp2 goto */
   stp2 = stp2->st.sgoto;
   if (stp2 == NULL || stp2->stmttyp != S_GOTO) break;
   if (stp2->lpend_goto) break;
  }
 return(stp2);
}

/*
 * setup the compiler runtime fixed events
 * make the headers for the list to avoid checking for null to place on head
 * of list
 */
extern void __setup_dummy_events(void)
{
 if (__all_nb_same_time == TRUE)
  {
   __last_nb_hp = NULL;
  }
 else
  {
   /* AIV 02/13/09 - need to init the last nb delay to max time */
   __last_nb_hp = (struct heap_t *) __my_malloc(sizeof(struct heap_t));
   __last_nb_hp->hash = -1;
   __last_nb_hp->time = 0xffffffffffffffffULL;
   __last_nb_hp->te_hdrp = NULL; 
   __last_nb_hp->te_endp = NULL;
   __last_nb_hp->nb_hdrp = NULL; 
   __last_nb_hp->nb_endp = NULL;
   __last_nb_hp->next = NULL;
  }

 __nchg_dummy_hd.triggered = FALSE;
 __nchg_dummy_hd.process_enterptr = NULL;
 __nchg_dummy_hd.delayed_mipd = FALSE;
 __nchg_dummy_hd.bi1 = -1;
 __nchg_dummy_hd.bi2 = -1;
 __nchg_dummy_hd.nchg_idp = NULL;
 __nchg_dummy_hd.nchglnxt = NULL;
 __nchg_futhdr = __nchg_futend = &__nchg_dummy_hd;
 

 init_dummy_tevp(&__pnd0_dummy_hd);
 init_dummy_tevp(&__nb_dummy_hd);
 __nchg_futhdr = __nchg_futend = &__nchg_dummy_hd;
 __nb_te_hdrp = __nb_te_endp = &__nb_dummy_hd;
 __save_scope_tskp = NULL;
}

/*
 * initialize a dummy event 
 * these are used to avoid checking for NULL making lists
 */
static void init_dummy_tevp(struct tev_t *tevp)
{
 tevp->free_it = FALSE;
 tevp->nb_evctrl = FALSE;
 tevp->te_trdecay = FALSE;
 tevp->gev_acc = FALSE;
 tevp->vpi_reschd = FALSE;
 tevp->vpi_regwir_putv = FALSE;
 tevp->align_filler = FALSE;
 tevp->outv = 0;
 tevp->scalar_nb_val = 0;
 tevp->tu.stp = NULL;
 tevp->trigger = FALSE;
 tevp->enterptr = NULL;
 tevp->next_enterptr = NULL;
#ifdef __STREE__
 tevp->nodep = NULL;
#else
 tevp->time_hp = NULL;
#endif
 tevp->etime = 0;
 tevp->te_idp = NULL;
 tevp->delay = 0;
 tevp->tenxtp = NULL;
 tevp->teprevp = NULL;
}

/*
 * scan a list up lhsx for the known NP_MDPRT and set flags whether or
 * not each net has a net change, any net change or dump vars 
 *
 * has_all_nchg = TRUE - all nets contain a net change
 * has_some_nchg = TRUE - only some nets contain a net change
 * has_dmpv = TRUE - some nets contain dump vars
 * had_dmpp - has dump ports
 * all_empty - all the connections are empty expressions
 * has_all_bsel - all expressions are bit selects
 * all_bsel_1w - all bit selects are < 1 word
 * has_toggle - at least net has toggle coverage
 */
extern int32 __set_mark_mdprt_flags(struct net_pin_t *npp, int32 *has_all_nchg, 
 int32 *has_some_nchg, int32 *has_dmpv, int32 *has_dmpp, int32 *has_empty,
 int32 *has_all_bsel, int32 *all_bsel_1w, int32 *all_empty, int32 *has_toggle)
{
 struct expr_t *up_lhsx;
 struct itree_t *itp;
 struct inst_t *ip;
 struct mod_t *downmdp;
 struct net_t *up_np;
 int32 ii, biti, has_mixed_expr;
     
 /* assuming this is a known optimizable npp - this better be set */
 /* DBG remove -- */
 if (npp->scalar_mdprt_ofs == 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 *has_all_nchg = TRUE;
 *all_bsel_1w = TRUE;
 *all_empty = TRUE;

 *has_some_nchg = FALSE;
 *has_dmpv = FALSE;
 *has_empty = FALSE;
 *has_dmpp = FALSE;
 *has_toggle = FALSE;
 *has_all_bsel = TRUE;

 has_mixed_expr = FALSE;

 downmdp = npp->elnpp.emdp;
 for (ii = 0; ii < downmdp->flatinum; ii++) 
  {
   itp = downmdp->moditps[ii];
   /* this is an instance of mod containing rhs output port load */
   ip = itp->itip;
   if (npp->npntyp == NP_PB_MDPRT)
    { up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi]; }
    else up_lhsx = ip->ipins[npp->obnum];

    if (up_lhsx->optyp == OPEMPTY) 
     {
      *has_empty = TRUE;
      *has_all_bsel = FALSE;
      has_mixed_expr = TRUE;
      continue;
     }

    *all_empty = FALSE;
    /* down better be simple scalar ID */
    if (up_lhsx->optyp == LSB)
     {
      up_np = up_lhsx->lu.x->lu.sy->el.enp;
      biti = __comp_ndx(up_np, up_lhsx->ru.x);
      /* AIV 08/20/09 - this needs to be the net width for the b part */
      /* not the index */
      if (up_np->nwid > WBITS) *all_bsel_1w = FALSE;
      has_mixed_expr = TRUE;
     }
    else
     {
      up_np = up_lhsx->lu.sy->el.enp;
      biti = -1;
      *has_all_bsel = FALSE;
     }

    /* set the flags */
   if (__needs_netchg_record(up_np) && __net_chg_nd_store(up_np, biti, biti)) 
    {
     *has_some_nchg = TRUE;
    }
   else *has_all_nchg = FALSE;
 
   if (up_np->dmpv_in_src) *has_dmpv = TRUE;
   if (up_np->dmpp_in_src) *has_dmpp = TRUE;
   /* AIV 12/06/10 - if has toggle coverage need to check for changes */ 
   if (up_np->n_has_toggle) *has_toggle = TRUE;
  }
 return(has_mixed_expr);
}

/*
 * check for constant delay - if constant return TRUE
 * divide the time into high/low word
 */
extern int32 __check_delay_constant(union del_u dc_du, int32 dc_delrep, 
 word64 *del)
{

 *del = -1;
 if (dc_delrep !=  DT_1V) return(FALSE);

 *del = dc_du.d1v[0]; 
 return(TRUE);
}

/*
 * return a non-blocking lhs srep type
 */
extern int32 __get_lhs_srep(struct expr_t *lhsx, int32 *bsize)
{
 int32 lhs_srep, nbytes;
 struct expr_t *idndp;
 struct net_t *np;

 //AIV FIXME - what about array SR_ARRAY as well????
 if (lhsx->optyp == GLBREF || lhsx->optyp == ID) idndp = lhsx;
 else if (lhsx->optyp == LSB || lhsx->optyp == PARTSEL 
  || lhsx->optyp == PARTSEL_NDX_PLUS || lhsx->optyp == PARTSEL_NDX_MINUS) 
  {
   idndp = lhsx->lu.x;
  }
 else idndp = NULL;

 /* if lhs concat must check the mark expression bit */
 if (idndp == NULL) 
  {
   if (__is_expr_2state(lhsx)) lhs_srep = SR_BIT2S;
   else lhs_srep = SR_VEC;
  }
 else
  {
   np = idndp->lu.sy->el.enp;
   if (np->srep == SR_ARRAY)
    {
     lhs_srep = __get_array_srep_type(np); 
    }
   else if (np->srep == SR_SCAL) lhs_srep = SR_SCAL;
   else if (np->srep == SR_SCAL2S) lhs_srep = SR_SCAL2S;
   else if (np->srep == SR_BIT2S) lhs_srep = SR_BIT2S;
   else lhs_srep = SR_VEC;
  }
   
 /* know vector or scalar so copy the correct size */
 if (lhs_srep == SR_VEC)
  {
   nbytes = 2*wlen_(lhsx->szu.xclen)*WRDBYTES;
  }
 else if (lhs_srep == SR_BIT2S)
  {
   nbytes = wlen_(lhsx->szu.xclen)*WRDBYTES;
  }
 else nbytes = WRDBYTES;

 *bsize = nbytes;
 return(lhs_srep);
}

/*
 * return TRUE if expression can be handled as 2-state
 */
extern int32 __is_expr_2state(struct expr_t *ndp)
{
 /* if expr has strength return false */
 if (ndp->x_stren) return(FALSE);

 if (ndp->x_is2state)
  {
   /* can only compile 2-state with new SV keyworks or +2state option */
   if (__opt_two_state || __sv_parse)
    {
     return(TRUE);
    }
  }
 return(FALSE);
}

/*
 * generate a distinct file name - with call to mkstemp 
 */
extern int32 __get_tmpfnam(char *fname)
{
 int32 fd;

 /* get the file name and just close file for now */
 if ((fd = mkstemp(fname)) < 0) 
  {
   __crit_msg("**fatal err[1]: OS open tmp file %s failed: %s\n", 
    fname, strerror(errno));
   return(-1);
  } 
 else
  {
   if (close(fd) < 0)
    {
     __crit_msg("**fatal err[1]: OS close tmp file %s failed: %s\n", 
      fname, strerror(errno));
     return(-1);
    }
  }
 return(0);
}
