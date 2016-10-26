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
 * Verilog prep and interpreter sim exec routines for x propagation feature
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

#ifdef __XPROP__
static void prep_xprop_mark_lstofsts(struct st_t *, int32, int32 *);
static struct st_t *prep_xprop_mark_stmt(struct st_t *, int32, int32 *);
static struct st_t *make_dummy_dce_xedge_if_stmt(struct st_t *, int32);
static struct st_t *eligible_xprop_stmt(struct st_t *, int32 *);
static void prep_xprop_turnoff_lstofsts(struct st_t *);
static struct st_t *prep_xprop_turnoff_stmt(struct st_t *);
static void prep_xprop_lstofsts(struct st_t *, int32);
static struct st_t *prep_xprop_stmt(struct st_t *, int32);
static int32 is_stlst_lhs_assign(struct st_t *, int32 *, int32 *, 
 struct st_t *);
static int32 add_lhs_stmt(struct st_t *, struct st_t *, struct st_t *);
static int32 add_lhs_net(struct net_t *, struct st_t *, struct st_t *);
static int32 is_xprop_stmt_not_id(struct st_t *);
static int32 chk_lhs_assign_stmt(struct st_t *, struct st_t *, int32 *,
 struct st_t *);
static int32 if_stmt_lhs_assign(struct st_t *, int32, int32);
static int32 case_stmt_lhs_assign(struct st_t *, int32, int32);
static int32 check_case_items(struct st_t *);
static int32 xp_cmp(const void *, const void *);
static int32 compare_number(struct expr_t *, struct expr_t *);
static int32 find_case_item(struct expr_t *, struct expr_t **, int32);
static struct xprop_t *setup_xprop_lhs_nets(int32, int32, int32);
struct st_t *get_new_xprop_assign(struct st_t *, struct net_t *);
static void concat_stmtlst(struct st_t *, struct st_t *);
static void convert_x_assigns_stlst(struct st_t *);
static struct st_t *convert_x_assign_stmt(struct st_t *, struct st_t *, 
 int32 *);
static struct expr_t *make_x_expr(int32);
static int32 xprop_net_used_on_rhs(struct expr_t *, struct net_t *);
static int32 xprop_lhsexpr_var_ndx_uses_lhsnet(struct expr_t *, 
 struct net_t *);
static struct st_t *set_parent_xprop_stmt(struct st_t *, int32);
static void set_parent_xprop_lstofsts(struct st_t *, int32);
static void set_xprop_parent_lhs_ids_lstofsts(struct st_t *);
static struct st_t *set_xprop_parent_lhs_ids_stmt(struct st_t *);
static void set_xprop_ids_only_parent(struct xprop_t *);
static void add_xprop_stmt_to_list(struct st_t *);
static struct st_t *xprop_copy_stmt(struct st_t *);
static void add_new_xprop_stmts_to_mstmts(struct mod_t *);
static void set_xprop_accum_block(struct xprop_t *);
static void set_restore_xprop_accum_block(struct xprop_t *, int32, int32);


/* routines for interpeter execution */
static struct st_t *exec_xprop_stmts(struct st_t *, struct xprop_t *, int32);
static void assign_xprop_value(struct st_t *, struct xstk_t *);
static void assign_net_to_accum(struct expr_t *, word32 *, word32 *,
 struct xprop_t *);
static void set_xprop_accum_value(struct net_t *, int32, int32,
 word32 *, word32 *, struct xprop_t *, int32);
static void combine_xprop_accum(word32 *, word32 *, word32 *, int32);
static void xprop_tr_nbproc_assign(struct st_t *, struct xstk_t *);
static void xprop_tr_proc_assign(struct st_t *, struct xstk_t *);
static void emit_xprop_not_eligible(struct st_t *, struct st_t *, 
 struct st_t *, struct net_t *, int32);
static void xprop_check_case_net_assigned(struct xprop_t *);

extern void __prep_xprop_stmts(int32);
extern void __eligible_xprop_stofsts(struct st_t *, int32 *);
extern void __assign_lhsx_to_accum(struct expr_t *, word32 *, word32 *,
 struct xprop_t *);
extern struct st_t *__exec_xprop_if_stmt(struct st_t *, int32, struct xstk_t *);
extern void __exec_xprop_case(struct st_t *, int32, struct xstk_t *);
extern void __setup_xprop_trace_file(int32);
extern void __setup_xprop_not_eligible_file(struct optlst_t *);
extern void __free_xprop(struct xprop_t *);
extern struct expr_t *__get_lvalue_idndp(struct expr_t *);
extern void __trace_xprop_stmt_write(struct st_t *, word32 *, word32 *, int32);
extern void __assign_xprop_accum_values(struct xprop_t *);
extern struct st_t *__exec_xprop_dce(struct st_t *);
extern int32 __is_stlst_net_on_rhs_assign(struct st_t *, struct net_t *,
 struct st_t *); 

extern struct st_t *__copy_lstofsts(struct st_t *);
extern struct st_t *__copy_stmt(struct st_t *);
extern void __chk_lstofsts(struct st_t *);
extern struct expr_t *__alloc_newxnd(void);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern int32 __chk_rhsexpr(struct expr_t *, int32);
extern int32 __is_expr_2state(struct expr_t *);
extern int32 __cmp_xpr(struct expr_t *, struct expr_t *, int32 *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern int32 __wide_vval_is0(word32 *, int32);
extern void __sgn_xtnd_widen(struct xstk_t *, int32);
extern void __sizchg_widen(struct xstk_t *, int32);
extern void __narrow_sizchg(struct xstk_t *, int32);
extern FILE *__tilde_fopen(char *, char *);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern void __exec2_proc_assign(struct expr_t *, word32 *, word32 *);
extern void __cnv_stk_fromreal_toreg32(struct xstk_t *);
extern void __free_xtree(struct expr_t *);
extern void __sched_nbproc_delay(struct delctrl_t *, struct xstk_t *,
 struct st_t *);
extern struct xstk_t *__eval_assign_rhsexpr(struct expr_t *, struct expr_t *);
extern void __rhspsel(word32 *, word32 *, int32, int32);
extern void __lhspsel(word32 *, int32, word32 *, int32);
extern void __lhsbsel(word32 *, int32, word32);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern void __ld_wire_val_wrds(word32 *, word32 *,
 struct net_t *);
extern int32 __check_delay_constant(union del_u, int32, word64 *);
extern void __dmp_proc_assgn(FILE *, struct st_t *, struct delctrl_t *, int32);
extern void __trunc_exprline(int32, int32);
extern char *__xregab_tostr(char *, word32 *, word32 *, int32, struct expr_t *);
extern void __dmp_nbproc_assgn(FILE *, struct st_t *, struct delctrl_t *);
extern void __dmp_stmt(FILE *, struct st_t *, int32);
extern char *__to_sttyp(char *, word32);
extern char *__msgnumexpr_tostr(char *, struct expr_t *, int32);
extern struct st_t *__alloc_stmt(int32);
extern struct expr_t *__alloc_exprnd(void);
extern int32 __alloc_shareable_cval(word32, word32, int32);
extern int32 __is_const_expr(struct expr_t *);

extern void __tr_msg(char *, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_fclose(FILE *);
extern void __my_free(void *, size_t);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __pv_warn(int32, char *, ...);

extern const word32 __masktab[];

/* local global duplicate expr */
static struct expr_t *__dup_xp;
     
/* xprop not eligible reasons */
#define NOT_ELIGIBLE_ILLEGAL_STMT 0
#define NOT_ELIGIBLE_LHS_RHS_PROCA 1
#define NOT_ELIGIBLE_LHS_COND 2
#define NOT_ELIGIBLE_REAL 3
#define NOT_ELIGIBLE_NO_XZ_SELECT 4
#define NOT_ELIGIBLE_ASSIGNS_DONT_MATCH 5
#define NOT_ELIGIBLE_LHS_VARNDX 6
#define NOT_ELIGIBLE_LHS_XMR 7
#define NOT_ELIGIBLE_NB_NOT_CONST 8
#define NOT_ELIGIBLE_NB_NOT_SAME 9
#define NOT_ELIGIBLE_NET_FORCED 10
#define NOT_ELIGIBLE_LHS_ARRAY 11
#define NOT_ELIGIBLE_CASE_DUP 12    /* duplicate case items */
#define NOT_ELIGIBLE_CASE_EXPR 13   /* case item is expression (not const) */
#define NOT_ELIGIBLE_IF_EXPR 14     /* if cond constains !==/===/etc */

/* 
 * ROUTINES TO DO THE X-PROPAGATION PREP CODE - PRIOR TO SIMULATION
 */

/*
 * Prep possible xprop stmts marking eligible if/case stmts which can
 * be treated as xprop stmts.  Allocate xprop structs for each if/case
 * and set xprop stmt fields.
 */
extern void __prep_xprop_stmts(int32 is_xprop2)
{
 int32 max_net_count, wlen, not_eligible;
 struct task_t *tskp;
 struct mod_t *mdp;
 struct ialst_t *ialp; 

 /* AIV 03/22/12 - this needs to go after __xprop/__xprop2 set */
 if (__xprop_trace_on)
  {
   if (is_xprop2) __setup_xprop_trace_file(2);
   else __setup_xprop_trace_file(1);
  }


 /* AIV 10/27/11 - it +2state it makes no sense to use +xprop/+xprop2 */
 if (__opt_two_state)
  {
   __pv_warn(1013,
    "+xprop/+xprop2 along with +2state option should not be used no x/z parts");
   return;
  }

 /*  get the max number of nets for the entire design */
 max_net_count = 0;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum > max_net_count) max_net_count = mdp->mnnum;
  }

 /* allocate globals which store net values as we work down the stmt */
 /* list - these are for the local stmt xprop structs */
 __xprop_lhs_nets = (struct net_t **) 
    __my_malloc(max_net_count*sizeof(struct net_t *));
 __xprop_lhs_other_than_id = (int32 *) 
    __my_malloc(max_net_count*sizeof(int32));
 memset(__xprop_lhs_other_than_id, 0, max_net_count*sizeof(int32));
 __xprop_stmts = (struct st_t **)
    __my_malloc(max_net_count*sizeof(struct st_t *));
 __xprop_net_ndx = 0;

 /* same except contains the top level stmt xprop */
 __xprop_lhs_nets_top = (struct net_t **) 
    __my_malloc(max_net_count*sizeof(struct net_t *));
 __xprop_stmts_top = (struct st_t **)
    __my_malloc(max_net_count*sizeof(struct st_t *));
 __xprop_lhs_other_than_id_top = (int32 *) 
    __my_malloc(max_net_count*sizeof(int32));
 memset(__xprop_lhs_other_than_id_top, 0, max_net_count*sizeof(int32));
 __xprop_net_ndx_top = 0;

 /* traverse the initial/always stmts marking allocating stmts */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
    {
     /* xprop first marks then allocs */
     if (!is_xprop2)
      {
       /* if xprop not turned on for this module continue */
       if (!mdp->m_use_xprop) continue;
       /* first mark eligible stmts */
       prep_xprop_mark_lstofsts(ialp->iastp, 0, &not_eligible);
      }
     /* neither xprop for this module continue */
     if (!mdp->m_use_xprop2 && !mdp->m_use_xprop) continue;
     __xprop_net_ndx_top = 0;
     __xprop_net_ndx = 0;
     /* alloc xprop structs to do the actual xprop processing */
     prep_xprop_lstofsts(ialp->iastp, 0);
     if (!is_xprop2)
      {
       __current_xprop = NULL;
       set_parent_xprop_lstofsts(ialp->iastp, 0);
       /* if any parents have per bit need to use per bit code */
       set_xprop_parent_lhs_ids_lstofsts(ialp->iastp);
      }
    }
   /* only for xprop2 - convert tasks/functions - this is needed because */
   /* __xprop2 assumes entire design wide xprop setting */
   if (is_xprop2)
    {
     for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
      {
       prep_xprop_lstofsts(tskp->tskst, 0);
      }
     }
   /* --- DBG remove ---  */
   //__dmp_mod(stdout, mdp, FALSE);
   /* -----  */
  add_new_xprop_stmts_to_mstmts(mdp);
   __added_xprop_stlst_hdr = NULL;
   __added_xprop_stlst_tail = NULL; 
   __pop_wrkitstk();
  }

 /* create a max net wide vector of 1s - so don't have to push */
 /* the stack each time - never changes */
 wlen = wlen_(__xprop_max_net_width);
 __xprop_max_net_1_wp = (word32 *) __my_malloc(wlen*WRDBYTES);
 memset(__xprop_max_net_1_wp, 0xff, wlen*WRDBYTES);

 /* --- DBG remove ---  */
 if (__xprop_net_ndx_top != 0) __misc_terr(__FILE__, __LINE__);
 /* ------  */

 /* free global storage areas */
 __my_free(__xprop_lhs_nets, max_net_count*sizeof(struct net_t *));
 __my_free(__xprop_stmts, max_net_count*sizeof(struct st_t *));
 __my_free(__xprop_lhs_other_than_id, max_net_count*sizeof(int32));

 __my_free(__xprop_lhs_nets_top, max_net_count*sizeof(struct net_t *));
 __my_free(__xprop_stmts_top, max_net_count*sizeof(struct st_t *));
 __my_free(__xprop_lhs_other_than_id_top, max_net_count*sizeof(int32));
 
 /* need to close xprop not eligible stmt file */
 if (__xprop_not_eligible_fp != NULL) 
  {
   __my_fclose(__xprop_not_eligible_fp);
  }
}
 
/*
 *
 */
static void add_new_xprop_stmts_to_mstmts(struct mod_t *mdp)
{
 int32 added, i, onum;
 struct st_t *stp;
 size_t osize, nsize;
 struct st_list_t *stlstp, *stlstp2;
   
 if (__added_xprop_stlst_hdr == 0) return;

 added = 0;
 for (stlstp = __added_xprop_stlst_hdr; stlstp != NULL; stlstp = stlstp2)
  {
   added++;
   stlstp2 = stlstp->nxt_stp;
  }


 onum = mdp->mstnum - added;
 osize = onum*sizeof(struct st_t *);
 nsize = mdp->mstnum*sizeof(struct st_t *);

 /* --- DBG remove --- */
 if (osize == nsize) __misc_terr(__FILE__, __LINE__);
 /* ------ */
 
 /* realloc and grow the mstmts */
 mdp->mstmts = (struct st_t **) __my_realloc(mdp->mstmts, osize, nsize);

 /* fill in the new stmts on the end */
 i = onum;
 for (stlstp = __added_xprop_stlst_hdr; stlstp != NULL; stlstp = stlstp2, i++)
  {
   stlstp2 = stlstp->nxt_stp;

   stp = stlstp->stp;
   mdp->mstmts[i] = stp;
   stp->st_ndx = i;
   __my_free(stlstp, sizeof(struct st_list_t));
  }
}
     
/*
 * mark all if/case stmts ->xprop_eligible bits
 */
static void prep_xprop_mark_lstofsts(struct st_t *hdstp, int32 slevel,
 int32 *not_eligible)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = prep_xprop_mark_stmt(stp, slevel, not_eligible);
  }
}

/*
 * mark all if/case stmts ->xprop_eligible bits
 */
static struct st_t *prep_xprop_mark_stmt(struct st_t *stp, int32 slevel,
 int32 *not_eligible)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;
 struct if_t *ifinfo;
 int32 fji, if_xprop, body_not_eligible, is_constn;
 struct st_t *fjstp;
 struct expr_t *condxp, *selxp;
 struct st_t *astp; 
 struct delctrl_t *dctp;
 word64 ndel;

 switch ((byte) stp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_FORASSGN:
  case S_REPSETUP: case S_REPDCSETUP: case S_TSKCALL:
  case S_QCONTA: case S_QCONTDEA: case S_CAUSE: case S_DSABLE:
   *not_eligible = TRUE; 
   break;
  case S_NULL: case S_STNONE: case S_GOTO:
  case S_PROCA: case S_RHSDEPROCA: case S_NBPROCA: 
   stp->xprop_eligible = TRUE;
   break;
  case S_IF:
   ifinfo = &(stp->st.sif);
   condxp = ifinfo->condx;
   /* if condition is real cannot have an x value leave as normal if */
   if_xprop = TRUE;
   if (condxp->is_real) 
    {
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_REAL);
     if_xprop = FALSE;
    }
   //LOOKATME - this marking might be iffy?????
   /* call set rhswidth which will set x_is2state bit - if known two state */
   /* if stmt no reason for the special x if stmt conversion */
   //if (condxp->x_is2state) break;
   __xprop_expr_has_cneq = FALSE; 
   __chk_rhsexpr(condxp, 0);
   if (__xprop_expr_has_cneq)
    { 
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_IF_EXPR);
     if_xprop = FALSE;
    }
   __xprop_expr_has_cneq = FALSE; 

   if (__is_expr_2state(condxp)) 
    {
     if_xprop = FALSE;
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_NO_XZ_SELECT);
    }


   if (!if_xprop)
    {
     prep_xprop_turnoff_lstofsts(stp->st.sif.thenst);
     if (stp->st.sif.elsest != NULL) 
       prep_xprop_turnoff_lstofsts(stp->st.sif.elsest);
     *not_eligible = TRUE; 
     break;
    }

   body_not_eligible = FALSE;
   prep_xprop_mark_lstofsts(stp->st.sif.thenst, slevel+1, &body_not_eligible);
   if (stp->st.sif.elsest != NULL) 
     prep_xprop_mark_lstofsts(stp->st.sif.elsest, slevel+1, &body_not_eligible);
   if (!body_not_eligible)
    {
     stp->xprop_eligible = if_stmt_lhs_assign(stp, 0, FALSE);
    }
   else *not_eligible = TRUE;
   __xprop_net_ndx = 0;

   if (!stp->xprop_eligible)
    {
     prep_xprop_turnoff_lstofsts(stp->st.sif.thenst);
     if (stp->st.sif.elsest != NULL) 
       prep_xprop_turnoff_lstofsts(stp->st.sif.elsest);
     *not_eligible = TRUE; 
    }
   /* AIV 02/16/12 - need to set xprop top index back to zero here */
   /* was not making xprop eligible top level blocks with different stmt */
   /* assign types */
   if (slevel == 0) __xprop_net_ndx_top = 0;
   break;
  case S_CASE:
   /* AIV 10/27/11 - need to check for 2state condition here as well */
   selxp = stp->st.scs.csx;
   /* if condition is real cannot have an x value leave as normal if */
   if (selxp->is_real) 
    {
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_REAL);
     *not_eligible = TRUE; 
     break;
    }
   /* if stmt no reason for the special x if stmt conversion */
   __chk_rhsexpr(selxp, 0);
   if (__is_expr_2state(selxp)) 
    {
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_NO_XZ_SELECT);
     *not_eligible = TRUE; 
     break;
    }

   /* AIV 01/31/12 - make sure no case items are duplicate and expressions */
   if (!check_case_items(stp)) 
    {
     *not_eligible = TRUE; 
     break;
    }

   body_not_eligible = FALSE;
   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
     prep_xprop_mark_lstofsts(csip->csist, slevel+1, &body_not_eligible);
   if (dflt_csip->csist != NULL)
     prep_xprop_mark_lstofsts(dflt_csip->csist, slevel+1, &body_not_eligible);
   if (!body_not_eligible)
    {
     stp->xprop_eligible = case_stmt_lhs_assign(stp, 0, FALSE);
    }
   else *not_eligible = TRUE;
   __xprop_net_ndx = 0;
   if (!stp->xprop_eligible)   
    {
     for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
      prep_xprop_turnoff_lstofsts(csip->csist);
     if (dflt_csip->csist != NULL)
      prep_xprop_turnoff_lstofsts(dflt_csip->csist);
    }
   /* AIV 02/16/12 - need to set xprop top index back to zero here */
   /* was not making xprop eligible top level blocks with different stmt */
   /* assign types */
   if (slevel == 0) __xprop_net_ndx_top = 0;
   break;
  case S_REPEAT:
   *not_eligible = TRUE; 
   prep_xprop_mark_lstofsts(stp->st.srpt.repst, slevel, not_eligible);
   break;
  case S_FOREVER: case S_WHILE:
   *not_eligible = TRUE; 
   prep_xprop_mark_lstofsts(stp->st.swh.lpst, slevel, not_eligible);
   break;
  case S_WAIT:
   *not_eligible = TRUE; 
   prep_xprop_mark_lstofsts(stp->st.swait.lpst, slevel, not_eligible);
   break;
  case S_FOR:
   *not_eligible = TRUE; 
   prep_xprop_mark_lstofsts(stp->st.sfor->forinc, slevel, not_eligible);
   prep_xprop_mark_lstofsts(stp->st.sfor->forbody, slevel, not_eligible);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;

   if (astp->stmttyp == S_NBPROCA) stp->xprop_eligible = TRUE;
   /* AIV 02/16/12 - now handling always @(Xedges) */
   //AIV LOOKATME - only including always @() for now */
   if (dctp->dctyp == DC_EVENT && dctp->is_always)
    {
//AIV EXPROP - report not eligible xmr
     if (dctp->d_has_xmr) 
      {
       if (astp != NULL) prep_xprop_mark_lstofsts(astp, slevel, not_eligible);
       break;
      }
     /* if first statement happens to be an if with no else */
     /* no reason to make a 'dummy' if place holder can just use the */
     /* actual if stmt */
     if (!__no_xprop_edges)
      {
       /* must call this to set the xprop_eligible bits */
       body_not_eligible = FALSE;
       prep_xprop_mark_lstofsts(astp, slevel, &body_not_eligible);
       /* AIV 02/25/12 - if has any not eligible stmts below this */
       /* cannot include this in X-dectection */
       if (!body_not_eligible) 
        {
         astp = make_dummy_dce_xedge_if_stmt(astp, slevel);
         dctp->xprop_xedge_actionst = astp;
         /* if always blocks merged this will be set but not if they are not */
         /* this needs to be set be the xprop xedge fgs need to be able */
         /* to get the fixed struct from dctp */
         if (__compiled_sim)
          {
           if (dctp->head_ctevp == NULL)
            {
             /*--- DBG remove ---  */
             if (stp->ctevp == NULL) __misc_terr(__FILE__, __LINE__);
             /*--------  */
             dctp->head_ctevp = stp->ctevp;
            }
          }
         prep_xprop_mark_lstofsts(astp, slevel, not_eligible);
        }
      }
     else prep_xprop_mark_lstofsts(astp, slevel, not_eligible);
     *not_eligible = FALSE; 
    }
   else 
    {
     if (astp != NULL) prep_xprop_mark_lstofsts(astp, slevel, not_eligible);
     /* AIV 02/25/12 - the <= #delay must be constant */
     if (astp->stmttyp == S_NBPROCA) 
      {
       is_constn = __check_delay_constant(dctp->dc_du, dctp->dc_delrep, 
          &(ndel));
       if (is_constn) stp->xprop_eligible = TRUE;
       else *not_eligible = TRUE; 
      }
     else *not_eligible = TRUE; 
    }
   break;
  case S_NAMBLK:
   *not_eligible = TRUE; 
   prep_xprop_mark_lstofsts(stp->st.snbtsk->tskst, slevel, not_eligible);
   break;
  case S_UNBLK:
   *not_eligible = TRUE; 
   prep_xprop_mark_lstofsts(stp->st.sbsts, slevel, not_eligible);
   break;
  case S_UNFJ:
   *not_eligible = TRUE; 
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     prep_xprop_mark_lstofsts(fjstp, slevel, not_eligible);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}

/*
 * nearly the same as above but just marks eligible or not stmts 
 * for setting up prevval_ofs at idp prep time
 */
extern void __eligible_xprop_stofsts(struct st_t *hdstp, int32 *not_eligible)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = eligible_xprop_stmt(stp, not_eligible);
  }
}

/*
 * set not_eligbile flag it stmts not eligible
 */
static struct st_t *eligible_xprop_stmt(struct st_t *stp, int32 *not_eligible)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;
 struct if_t *ifinfo;
 int32 fji, if_xprop, body_not_eligible, is_constn;
 struct st_t *fjstp;
 struct expr_t *condxp, *selxp;
 struct st_t *astp; 
 struct delctrl_t *dctp;
 word64 ndel;

 switch ((byte) stp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_FORASSGN:
  case S_REPSETUP: case S_REPDCSETUP: case S_TSKCALL:
  case S_QCONTA: case S_QCONTDEA: case S_CAUSE: case S_DSABLE:
   *not_eligible = TRUE; 
   break;
  case S_NULL: case S_STNONE: case S_GOTO:
  case S_PROCA: case S_RHSDEPROCA: case S_NBPROCA: 
   break;
  case S_IF:
   ifinfo = &(stp->st.sif);
   condxp = ifinfo->condx;
   if_xprop = TRUE;
   if (condxp->is_real) 
    {
     if_xprop = FALSE;
    }
   //LOOKATME - this marking might be iffy?????
   /* call set rhswidth which will set x_is2state bit - if known two state */
   /* if stmt no reason for the special x if stmt conversion */
   //if (condxp->x_is2state) break;
   __xprop_expr_has_cneq = FALSE; 
   __chk_rhsexpr(condxp, 0);
   if (__xprop_expr_has_cneq)
    { 
     if_xprop = FALSE;
    }
   __xprop_expr_has_cneq = FALSE; 

   if (__is_expr_2state(condxp)) 
    {
     if_xprop = FALSE;
    }


   if (!if_xprop)
    {
     prep_xprop_turnoff_lstofsts(stp->st.sif.thenst);
     if (stp->st.sif.elsest != NULL) 
       prep_xprop_turnoff_lstofsts(stp->st.sif.elsest);
     *not_eligible = TRUE; 
     break;
    }

   body_not_eligible = FALSE;
   __eligible_xprop_stofsts(stp->st.sif.thenst, &body_not_eligible);
   if (stp->st.sif.elsest != NULL) 
     __eligible_xprop_stofsts(stp->st.sif.elsest, &body_not_eligible);
   if (body_not_eligible)
    {
     *not_eligible = TRUE;
    }
   break;
  case S_CASE:
   /* AIV 10/27/11 - need to check for 2state condition here as well */
   selxp = stp->st.scs.csx;
   /* if condition is real cannot have an x value leave as normal if */
   if (selxp->is_real) 
    {
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_REAL);
     *not_eligible = TRUE; 
     break;
    }
   /* if stmt no reason for the special x if stmt conversion */
   __chk_rhsexpr(selxp, 0);
   if (__is_expr_2state(selxp)) 
    {
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_NO_XZ_SELECT);
     *not_eligible = TRUE; 
     break;
    }

   /* AIV 01/31/12 - make sure no case items are duplicate and expressions */
   if (!check_case_items(stp)) 
    {
     *not_eligible = TRUE; 
     break;
    }

   body_not_eligible = FALSE;
   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
     __eligible_xprop_stofsts(csip->csist, &body_not_eligible);
   if (dflt_csip->csist != NULL)
     __eligible_xprop_stofsts(dflt_csip->csist, &body_not_eligible);
   if (body_not_eligible)
    {
     *not_eligible = TRUE;
    }
   break;
  case S_REPEAT:
   *not_eligible = TRUE; 
   __eligible_xprop_stofsts(stp->st.srpt.repst, not_eligible);
   break;
  case S_FOREVER: case S_WHILE:
   *not_eligible = TRUE; 
   __eligible_xprop_stofsts(stp->st.swh.lpst, not_eligible);
   break;
  case S_WAIT:
   *not_eligible = TRUE; 
   __eligible_xprop_stofsts(stp->st.swait.lpst, not_eligible);
   break;
  case S_FOR:
   *not_eligible = TRUE; 
   __eligible_xprop_stofsts(stp->st.sfor->forinc, not_eligible);
   __eligible_xprop_stofsts(stp->st.sfor->forbody, not_eligible);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;

   if (astp != NULL) __eligible_xprop_stofsts(astp, not_eligible);
   /* AIV 02/25/12 - the <= #delay must be constant */
   if (astp->stmttyp == S_NBPROCA) 
    {
     is_constn = __check_delay_constant(dctp->dc_du, dctp->dc_delrep, 
        &(ndel));
     if (is_constn) stp->xprop_eligible = TRUE;
     else *not_eligible = TRUE; 
    }
   else *not_eligible = TRUE; 
   break;
  case S_NAMBLK:
   *not_eligible = TRUE; 
   __eligible_xprop_stofsts(stp->st.snbtsk->tskst, not_eligible);
   break;
  case S_UNBLK:
   *not_eligible = TRUE; 
   __eligible_xprop_stofsts(stp->st.sbsts, not_eligible);
   break;
  case S_UNFJ:
   *not_eligible = TRUE; 
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     __eligible_xprop_stofsts(fjstp, not_eligible);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}

/*
 * make a dummy 'if' statement which is really just the entry into
 * always @(if) which makes the xprop struct as normal
 */
static struct st_t *make_dummy_dce_xedge_if_stmt(struct st_t *stp, int32 slevel)
{
 struct expr_t *condxp;
 struct st_t *if_stp;

 __xprop_copying = TRUE; 
 if_stp = __alloc_stmt(S_IF);
 if_stp->stlin_cnt = stp->stlin_cnt;
 if_stp->stfnam_ind = stp->stfnam_ind;
 if_stp->st.sif.xedge_dce = TRUE;

 if_stp->st.sif.thenst = stp; 

 condxp = __alloc_exprnd();
 condxp->optyp = NUMBER;
 condxp->szu.xclen = 1;
 condxp->ru.xvi = __alloc_shareable_cval(1, 1, 1);
 if_stp->st.sif.condx = condxp;
 __xprop_copying = FALSE; 
 /* if not eligible remove the new statment and return NULL */
 if (!if_stmt_lhs_assign(if_stp, slevel, FALSE)) 
  {
   (__inst_mod->mstnum)--;
   __free_xtree(condxp);
   __my_free(if_stp, sizeof(struct st_t));
   return(NULL);
  }
 add_xprop_stmt_to_list(if_stp);
 return(if_stp);
}

/*
 *
 */
static struct st_t *xprop_copy_stmt(struct st_t *stp)
{
 struct st_t *new_stp;

 new_stp = __copy_stmt(stp);
 add_xprop_stmt_to_list(new_stp);
 return(new_stp);
}

/*
 *
 */
static void add_xprop_stmt_to_list(struct st_t *stp)
{
 struct st_list_t *stlstp;

 stlstp = (struct st_list_t *) __my_malloc(sizeof(struct st_list_t));
 stlstp->stp = stp;
 stlstp->nxt_stp = NULL;
 if (__added_xprop_stlst_hdr == NULL)
  {
   __added_xprop_stlst_hdr = stlstp; 
   __added_xprop_stlst_tail = stlstp; 
  }
 else
  {
   __added_xprop_stlst_tail->nxt_stp = stlstp; 
   __added_xprop_stlst_tail = stlstp; 
  }
}

/*
 * make sure a case statement can constant case items and the it does not
 * contain any duplicates - if either of these are true it returns FALSE
 */   
static int32 check_case_items(struct st_t *stp)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;
 int32 casi, xprnum, xpri, ndx;
 struct expr_t **icasxtab;
 struct expr_t *xp;
 struct exprlst_t *xplp;
 char s1[RECLEN];

 dflt_csip = stp->st.scs.csitems;
 csip = dflt_csip->csinxt;
 /* count the number of case items */
 for (xprnum = 0; csip != NULL; csip = csip->csinxt)
  {
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt) 
    {
     xprnum++;
     /* if case item is not constant - it is not eligible - cannot know value */
     //AIV LOOKATME - ISNUMBER?????
     if (xplp->xp->optyp != NUMBER)
      {
       emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_CASE_EXPR);
       return(FALSE);
      }
    }
  } 

 xprnum++;
 icasxtab = (struct expr_t **) __my_malloc(xprnum*sizeof(struct expr_t *));

 dflt_csip = stp->st.scs.csitems;
 csip = dflt_csip->csinxt;
 /* now check for duplicates */
 for (casi = 0, xpri = 0; csip != NULL; csip = csip->csinxt, casi++)
  {
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     xp = xplp->xp;
     icasxtab[casi] = xp;
     qsort((char *) icasxtab, (word32) casi, sizeof(struct expr_t *), xp_cmp); 
     ndx = find_case_item(xp, icasxtab, casi);
     if (ndx != -1)
      {
       __dup_xp = xp;
       __msgnumexpr_tostr(s1, xp, 0);
       __pv_warn(3014, "During X-propagation setup case statement at %s:%d has duplicate case items for value %s - this may be a bug in the RTL.", 
       __in_fils[stp->stfnam_ind], stp->stlin_cnt, s1);

       emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_CASE_DUP);

       __my_free(icasxtab, xprnum*sizeof(struct expr_t *));
       return(FALSE);
      }
    }
  } 
 __my_free(icasxtab, xprnum*sizeof(struct expr_t *));
 return(TRUE);
}

/*
 *
 */
static int32 xp_cmp(const void *x1, const void *x2)
{
 int32 is_eq;
 struct expr_t *xp1, *xp2;

 xp1 = (*((struct expr_t **) x1));
 xp2 = (*((struct expr_t **) x2));
 is_eq = compare_number(xp1, xp2);
 return(is_eq);
}

/*
 *
 */
static int32 compare_number(struct expr_t *xp1, struct expr_t *xp2)
{
 int32 wlen;
 word32 *wp1, *wp2;

 if (xp1->szu.xclen != xp2->szu.xclen) return(-1);

 wp1 = &(__contab[xp1->ru.xvi]);
 wp2 = &(__contab[xp2->ru.xvi]);
 wlen = wlen_(xp1->szu.xclen);
 return(memcmp(wp1, wp2, 2*wlen*WRDBYTES));

}

static int32 find_case_item(struct expr_t *xp, struct expr_t **xptab, int32 num)
{
 int32 l, h, m, cv;

 if (num == 0) return(-1);
 l = 0; h = num - 1;
 for (;;)
  {
   m = (l + h)/2;
   if ((cv = compare_number(xptab[m], xp)) == 0) return(m);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) break;
  }
 return(-1);
}

/*
 * if one level is not eligible turn off all bits below it
 */
static void prep_xprop_turnoff_lstofsts(struct st_t *hdstp)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = prep_xprop_turnoff_stmt(stp);
  }
}

/*
 * if one level is not eligible turn off all bits below it
 */
static struct st_t *prep_xprop_turnoff_stmt(struct st_t *stp)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;
 int32 fji;
 struct st_t *fjstp;
 struct st_t *astp;
 struct delctrl_t *dctp;

 stp->xprop_eligible = FALSE;
 switch ((byte) stp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_NULL: case S_STNONE:
  case S_PROCA: case S_RHSDEPROCA: case S_NBPROCA: case S_FORASSGN:
  case S_REPSETUP: case S_REPDCSETUP: case S_TSKCALL:
  case S_QCONTA: case S_QCONTDEA: case S_CAUSE: case S_DSABLE:
   break;
  case S_IF:
   prep_xprop_turnoff_lstofsts(stp->st.sif.thenst);
   if (stp->st.sif.elsest != NULL) 
     prep_xprop_turnoff_lstofsts(stp->st.sif.elsest);
   break;
  case S_CASE:
   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
     prep_xprop_turnoff_lstofsts(csip->csist);
   if (dflt_csip->csist != NULL)
     prep_xprop_turnoff_lstofsts(dflt_csip->csist);
   break;
  case S_REPEAT:
   prep_xprop_turnoff_lstofsts(stp->st.srpt.repst);
   break;
  case S_FOREVER: case S_WHILE:
   prep_xprop_turnoff_lstofsts(stp->st.swh.lpst);
   break;
  case S_WAIT:
   prep_xprop_turnoff_lstofsts(stp->st.swait.lpst);
   break;
  case S_FOR:
   prep_xprop_turnoff_lstofsts(stp->st.sfor->forinc);
   prep_xprop_turnoff_lstofsts(stp->st.sfor->forbody);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;
   if (astp != NULL) prep_xprop_turnoff_lstofsts(astp);
   if (dctp->xprop_xedge_actionst != NULL) 
     prep_xprop_turnoff_lstofsts(dctp->xprop_xedge_actionst);
   break;
   break;
  case S_NAMBLK:
   prep_xprop_turnoff_lstofsts(stp->st.snbtsk->tskst);
   break;
  case S_UNBLK:
   prep_xprop_turnoff_lstofsts(stp->st.sbsts);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     prep_xprop_turnoff_lstofsts(fjstp);
    }
   break;
  case S_GOTO:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}


/*
 * process stmts list allocating xprop structs
 */
static void prep_xprop_lstofsts(struct st_t *hdstp, int32 slevel)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = prep_xprop_stmt(stp, slevel);
  }
}

/*
 * process a stmt allocating xprop structs
 */
static struct st_t *prep_xprop_stmt(struct st_t *stp, int32 slevel)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;
 struct if_t *ifinfo;
 struct exprlst_t *xplp;
 int32 fji, isx, num_items, xcount, wlen, i;
 struct st_t *fjstp, *orig_thenstp, *orig_elsestp, *new_stp, *xp_list, *xp_hdr;
 struct st_t *astp;
 struct delctrl_t *dctp;
 struct expr_t *condxp, *selxp;
 struct xstk_t *xsp;

 /* record the if/case level - need these to know when to return */
 stp->xprop_level = slevel;
 switch ((byte) stp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_NULL: case S_STNONE:
  case S_PROCA: case S_RHSDEPROCA: case S_NBPROCA: case S_FORASSGN:
  case S_REPSETUP: case S_REPDCSETUP: case S_TSKCALL:
  case S_QCONTA: case S_QCONTDEA: case S_CAUSE: case S_DSABLE:
   break;
  case S_IF:
   ifinfo = &(stp->st.sif);
   condxp = ifinfo->condx;
   orig_thenstp = stp->st.sif.thenst;
   orig_elsestp = stp->st.sif.elsest;
   /* if not converting to ifx cannot increment the slevel */
   //AIV LOOKATME - think remove this isx at least for if????
   isx = stp->xprop_eligible;
   if (__xprop2)
    {
     prep_xprop_lstofsts(orig_thenstp, slevel+isx);

     /* if condition is real cannot have an x value leave as normal if */
     if (condxp->is_real) 
      {
       prep_xprop_lstofsts(orig_elsestp, slevel+isx);
       break;
      }
     __chk_rhsexpr(condxp, 0);
     if (__is_expr_2state(condxp))
      {
       prep_xprop_lstofsts(orig_elsestp, slevel+isx);
       break;
      }
  
     __xprop_copying = TRUE; 
     new_stp = xprop_copy_stmt(stp);
     __xprop_copying = FALSE; 
     concat_stmtlst(orig_thenstp, orig_elsestp);
     convert_x_assigns_stlst(orig_thenstp);

     /* AIV 10/26/11 - only do else after concat - otherwise has memory */
     /* issue for large concats */
     prep_xprop_lstofsts(orig_elsestp, slevel+isx);
     stp->st.sif.elsest = new_stp;
     /* may need to do some fixup code in new stmt list */
     __chk_lstofsts(new_stp);
     stp->xprop_eligible = TRUE;
    }
   else
    {
     prep_xprop_lstofsts(orig_thenstp, slevel+isx);
     prep_xprop_lstofsts(orig_elsestp, slevel+isx);
     /* copy in the original else stmt block */
     if (isx)
      {
       if (!if_stmt_lhs_assign(stp, slevel, TRUE)) 
         __misc_terr(__FILE__, __LINE__);
      }

     if (slevel == 0) __xprop_net_ndx_top = 0;
    }
   break;
  case S_CASE:
   /* if not converting to xcase cannot increment the slevel */
   isx = stp->xprop_eligible;
   dflt_csip = stp->st.scs.csitems;
   num_items = 0;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
    {
     prep_xprop_lstofsts(csip->csist, slevel+isx);

     /* AIV 02/19/12 - need to get the X/Z count for case matching */
     if (isx)
      {
       for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
        {
         if (__is_const_expr(xplp->xp))
          {
           xsp = __eval_xpr(xplp->xp);
           xcount = 0;
           wlen = wlen_(xsp->xslen);
           for (i = 0; i < wlen; i++)
            {
             xcount += __builtin_popcountl(xsp->bp[i]);
            }
           __pop_xstk();
          }
         else __misc_terr(__FILE__, __LINE__);
         if (xcount == 0) xplp->num_xmatch = 1;
         else xplp->num_xmatch = 2*xcount;
         num_items++;
        }
      }
    }
   if (dflt_csip->csist != NULL)
     prep_xprop_lstofsts(dflt_csip->csist, slevel+isx);
   selxp = stp->st.scs.csx;
   /* if condition is real cannot have an x value leave as normal if */
   if (selxp->is_real) 
    {
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_REAL);
     break;
    }
   /* if stmt no reason for the special x if stmt conversion */
   __chk_rhsexpr(selxp, 0);
   if (__is_expr_2state(selxp)) 
    {
     emit_xprop_not_eligible(stp, NULL, NULL, NULL, NOT_ELIGIBLE_NO_XZ_SELECT);
     break;
    }
        

   if (__xprop2)
    {
     __xprop_copying = TRUE; 
     xp_hdr = NULL;
     xp_list = NULL;
     if (dflt_csip->csist != NULL)
      {
       xp_hdr = __copy_lstofsts(dflt_csip->csist);
       xp_list = xp_hdr;
      }

     for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
      {
       new_stp = __copy_lstofsts(csip->csist);
       if (xp_hdr == NULL) xp_hdr = new_stp;
       else concat_stmtlst(xp_list, new_stp);
       xp_list = new_stp;
      }
     __xprop_copying = FALSE; 
     convert_x_assigns_stlst(xp_hdr);
     stp->st.scs.xprop_lstp = xp_hdr;
     /* may need to do some fixup code in new stmt list */
     __chk_lstofsts(xp_hdr);

     stp->xprop_eligible = TRUE;
     /* --- DBG remove --- 
     __my_fprintf(stdout, "New case xlist:\n");
     for (new_stp = xp_hdr; new_stp != NULL; new_stp = new_stp->stnxt)
      {
       __dmp_stmt(stdout, new_stp, NL);
      }
      __my_fprintf(stdout, "\n\n");
      ------ */
    }
   else 
    {
     if (isx)
      {
       if (!case_stmt_lhs_assign(stp, slevel, TRUE)) 
        __misc_terr(__FILE__, __LINE__);
      }
     /* zero out - only used for debug */
     else if (slevel == 0) __xprop_net_ndx_top = 0;
    }

   break;
  case S_REPEAT:
   prep_xprop_lstofsts(stp->st.srpt.repst, slevel);
   break;
  case S_FOREVER: case S_WHILE:
   prep_xprop_lstofsts(stp->st.swh.lpst, slevel);
   break;
  case S_WAIT:
   prep_xprop_lstofsts(stp->st.swait.lpst, slevel);
   break;
  case S_FOR:
   prep_xprop_lstofsts(stp->st.sfor->forinc, slevel);
   prep_xprop_lstofsts(stp->st.sfor->forbody, slevel);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;
   if (astp != NULL) 
    {
     /* AIV 02/16/12 - now including always (x) detection */
     if (dctp->xprop_xedge_actionst != NULL) 
        prep_xprop_lstofsts(dctp->xprop_xedge_actionst, slevel);
     else prep_xprop_lstofsts(astp, slevel);
    }
   break;
  case S_NAMBLK:
   prep_xprop_lstofsts(stp->st.snbtsk->tskst, slevel);
   break;
  case S_UNBLK:
   prep_xprop_lstofsts(stp->st.sbsts, slevel);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     prep_xprop_lstofsts(fjstp, slevel);
    }
   break;
  case S_GOTO:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}

/*
 * Check a case stmt to see if it is eligible to be an xprop stmt.  Returns
 * FALSE if cannot be an xprop stmt.  
 */
static int32 case_stmt_lhs_assign(struct st_t *stp, int32 slevel, 
 int32 do_alloc)
{
 int32 i, save_ndx, has_nested, has_one_id;
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;
 struct xprop_t *xprop;
 struct net_t *np;

 /* AIV 02/09/12 - just turning these off for now */
 //if (stp->st.scs.castyp == CASEX) return(FALSE);
 /* AIV FIXME - need special handling for CASEZ */
 /* if (stp->st.scs.castyp == CASEZ) return(FALSE); */

 dflt_csip = stp->st.scs.csitems;
 save_ndx = __xprop_net_ndx;
 /* each stmt in the case must be eligible */
 has_nested = FALSE;
 has_one_id = TRUE;
 for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
  {
   if (!is_stlst_lhs_assign(csip->csist, &has_nested, &has_one_id, stp))
    {
     return(FALSE);
    }
  }

 if (dflt_csip->csist != NULL)
  {
   if (!is_stlst_lhs_assign(dflt_csip->csist, &has_nested, &has_one_id, stp))
    {
     return(FALSE);
    }
  }


 /* now must make sure all lhs nets never appear on the rhs */
 /* if any net is the lhs is on the rhs cannot handle as xprop */
 for (i = 0; i < __xprop_net_ndx; i++)
  {
   np = __xprop_lhs_nets[i];
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
    {
     /* only if stmt assign is a proc assign is this true */
     if (__xprop_stmts[i]->stmttyp != S_PROCA) continue;

     if (__is_stlst_net_on_rhs_assign(csip->csist, np, stp))
      {
       return(FALSE);
      }

     if (dflt_csip->csist != NULL)
      {
       if (__is_stlst_net_on_rhs_assign(dflt_csip->csist, np, stp))
        {
         return(FALSE);
        }
      }
    }
  }


 /* first pass do not allocate xprop struct */
 if (!do_alloc)
  {
   /* even if no nets still need to treat need to alloc xprop */
   return(TRUE);
  }

 /* --- DBG remove --- */
 if (stp->st.scs.xprop != NULL) __misc_terr(__FILE__, __LINE__);
 if (!stp->xprop_eligible) __misc_terr(__FILE__, __LINE__); 
 /* ---- */

 /* slevel is the top level xprop (entery point) */
 if (slevel == 0)
  {
   xprop =  setup_xprop_lhs_nets(-1, has_nested, has_one_id);
   stp->st.scs.xprop = xprop;
   __xprop_net_ndx = 0;
   if (xprop == NULL) return(FALSE);
   return(TRUE);
  }

 /* a sub level - that is not a top level entry point */
 xprop =  setup_xprop_lhs_nets(save_ndx, has_nested, has_one_id);
 stp->st.scs.xprop = xprop;
 __xprop_net_ndx = 0;
 return(TRUE);
}

//AIV EXPROP
extern struct st_t *__exec_xprop_dce(struct st_t *stp)
{
 struct st_t *nxtstp;
 struct xprop_t *xprop;
 word32 sval, setval;
 word32 *net_wp;
 int32 inum;
 struct net_t *np;

 xprop = stp->st.sif.xprop;
 /* DBG remove --- */
 if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
 if (stp->stmttyp != S_IF) __misc_terr(__FILE__, __LINE__);
 if (__no_xprop_edges) __misc_terr(__FILE__, __LINE__); 
 /* --- */

 /* now if has a posedge/negedge scalar it is known to take the value */
 /* of the edge direction - 0 or 1 - otherwise there would be no edge */
 inum = get_inum_();
 np = xprop->xedge_nets[inum];
 sval = 0;
 net_wp = NULL;
 if (np != NULL)
  {
   setval = xprop->xedge_to_vals[inum];
   /* DBG remove --- */
   if (np->srep != SR_SCAL && np->srep != SR_SSCAL) 
      __misc_terr(__FILE__, __LINE__);
   if (setval == XPROP_XEDGE_NOT_SET) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   net_wp = &(__idp[np->nva_ofs]);
   sval = *net_wp; 
   *net_wp = setval;
   xprop->xedge_nets[inum] = NULL;
   xprop->xedge_to_vals[inum] = XPROP_XEDGE_NOT_SET;
  }

//AIV EXPROP WRITEME - need more detail for this
 if (__xprop_trace_on) 
  {
   __trace_xprop_stmt_write(stp, NULL, NULL, -1);
  }

 set_xprop_accum_block(xprop);
 xprop->xblock = 0;
 nxtstp = exec_xprop_stmts(stp->st.sif.thenst, xprop, 1);
 set_restore_xprop_accum_block(xprop, FALSE, TRUE);
 /* restore the scalar edge value to to original value here */
 if (net_wp != NULL) 
  {
   *net_wp = sval;
  }
 __assign_xprop_accum_values(xprop);
 return(nxtstp);
}

/*
 * Allocate the xprop struct for if/case stmt.  If save_ndx is -1 it is the
 * top level if/case xprop entry point thus contains all nets if 
 * if/case/assigns below it.  Otherwise it is local to if/case stmt.
 * Assigns all the xprop lhs nets and allocates xprop fiels need at simulation
 * time for xprop handling.
 */
static struct xprop_t *setup_xprop_lhs_nets(int32 save_ndx, int32 has_nested,
 int32 has_one_id)
{
 struct xprop_t *xprop;
 struct net_t *np;
 struct st_t *xprop_stp, *astp;
 int32 *other_than_lhs_ids;
 struct delctrl_t *dctp;
 struct net_t **xprop_lhs_nets;
 struct st_t **xprop_stmts;
 word32 *wp;
 int32 i, ndx, num_nets, start, end, wlen;

 
 /* if -1 known to be the top level include all the nets which are assigned */
 /* to below this stmt */
 if (save_ndx == -1)
  {
   /* top-level version */
   num_nets = __xprop_net_ndx_top;
   xprop_lhs_nets = __xprop_lhs_nets_top;
   xprop_stmts = __xprop_stmts_top;
   other_than_lhs_ids = __xprop_lhs_other_than_id_top;
   start = 0;
   end = num_nets;
   /* put the top ndx back to 0 */
   __xprop_net_ndx_top = 0;
  }
 else 
  {
   /* local version */
   num_nets = __xprop_net_ndx - save_ndx;
   xprop_lhs_nets = __xprop_lhs_nets;
   xprop_stmts = __xprop_stmts;
   other_than_lhs_ids = __xprop_lhs_other_than_id;
   start = save_ndx;
   end = __xprop_net_ndx;
  }
 /* if num nets zero - probably just empty block or nested case/if */
 /* nothing to do no need to make an X condition block */
 // if (num_nets == 0) return(NULL);
 xprop = (struct xprop_t *) __my_malloc(sizeof(struct xprop_t));
 xprop->is_top_level = (save_ndx == -1);
 /* need to mark has nested if/case - can produce better code if known */
 /* to not be nested - one if/case stmt */
 xprop->nested_if_case = has_nested;
 xprop->top_single_item = !has_nested;
 xprop->has_ids_only = TRUE;
 xprop->x_entered = FALSE;

 xprop->xedge_to_vals = (byte *) __my_malloc(__inst_mod->flatinum);
 xprop->xedge_nets = (struct net_t **) 
   __my_malloc(sizeof(struct net_t *) * __inst_mod->flatinum);
 xprop->xevents = NULL;
 for (i = 0; i < __inst_mod->flatinum; i++)
  {
   xprop->xedge_to_vals[i] = XPROP_XEDGE_NOT_SET;
   xprop->xedge_nets[i] = NULL;
  }


 /* if has_one_id - is set - no empty blocks known to be set */
 if (has_one_id)
  {
   xprop->has_one_id_only = (num_nets == 1);
  }
 else xprop->has_one_id_only = FALSE;
 xprop->ncount = num_nets; 
 xprop->parent_xprop = NULL;
 xprop->xblock = 0;

 /* if num nets zero - probably just empty block or nested case/if */
 if (num_nets == 0) 
  {
   xprop->lhsnets = NULL;
   xprop->astmts = NULL;
   xprop->lhs_id_only = NULL;
   xprop->bits_set = NULL;
   xprop->accum_block1 = NULL;
   xprop->accum_block2 = NULL;
   xprop->xbitmask_block1_set = NULL;
   xprop->xbitmask_block2_set = NULL;
   xprop->net_block1_set = NULL;
   xprop->net_block2_set = NULL;
   xprop->parent_net_indices = NULL;
   return(xprop);
  }

 /* bits to check if each lhs net is assigned to in each block */
 xprop->net_block1_set = (int32 *) __my_malloc(sizeof(int32)*num_nets); 
 memset(xprop->net_block1_set, 0xff, sizeof(int32)*num_nets); 
 xprop->net_block2_set = (int32 *) __my_malloc(sizeof(int32)*num_nets); 
 memset(xprop->net_block2_set, 0xff, sizeof(int32)*num_nets); 

 /* bits to check if each lhs net is assigned to in each block - per bit */
 xprop->xbitmask_block1_set = (word32 **) 
         __my_malloc(sizeof(word32 *)*num_nets); 
 xprop->xbitmask_block2_set = (word32 **) 
        __my_malloc(sizeof(word32 *)*num_nets); 
 xprop->bits_set = (word32 **)
        __my_malloc(sizeof(word32 *)*num_nets); 
 xprop->accum_block1 = (word32 **)
        __my_malloc(sizeof(word32 *)*num_nets); 
 xprop->accum_block2 = (word32 **)
        __my_malloc(sizeof(word32 *)*num_nets); 

 /* parent net indices to preserve nested block1/2 setting */
 xprop->parent_net_indices = (int32 *) __my_malloc(sizeof(int32)*num_nets); 
 memset(xprop->parent_net_indices, 0xff, sizeof(int32)*num_nets); 
 /* lhs id only marks lhs nets which are only ID not selects */
 xprop->lhs_id_only = (int32 *) __my_malloc(sizeof(int32)*num_nets); 
 memset(xprop->lhs_id_only, 0, sizeof(int32)*num_nets); 


 /* lhsnets array of lhs nets */
 xprop->lhsnets = (struct net_t **) 
  __my_malloc(sizeof(struct net_t *)*num_nets); 
 /* assign style stmts to do the actual combined assign */
 xprop->astmts = (struct st_t **) 
  __my_malloc(sizeof(struct st_t *)*num_nets); 

 /* process the list of lhs nets for this xprop */
 for (i = start; i < end; i++)
  {
   np = xprop_lhs_nets[i];
   ndx = i-start;
   xprop->lhsnets[ndx] = np;
   np->n_xprop_ndx = ndx;

   /* need to save module wide max net width */
   if (np->nwid > __xprop_max_net_width) __xprop_max_net_width = np->nwid;         
   /* the per bit masks - if on lhs ids not needed */
   wlen = wlen_(np->nwid);
   if (other_than_lhs_ids[i])
    {
     xprop->has_ids_only = FALSE;
     xprop->has_one_id_only = FALSE;
     xprop->lhs_id_only[ndx] = FALSE;
    }
   else
    {
     xprop->lhs_id_only[ndx] = TRUE;
    }

   wp = (word32 *) __my_malloc(wlen*WRDBYTES);
   memset(wp, 0, wlen*WRDBYTES);
   xprop->xbitmask_block1_set[ndx] = wp;
  
   wp = (word32 *) __my_malloc(wlen*WRDBYTES);
   memset(wp, 0, wlen*WRDBYTES);
   xprop->xbitmask_block2_set[ndx] = wp;

   wp = (word32 *) __my_malloc(wlen*WRDBYTES);
   memset(wp, 0, wlen*WRDBYTES);
   xprop->bits_set[ndx] = wp;
     
   wp = (word32 *) __my_malloc(2*wlen*WRDBYTES);
   memset(wp, 0, 2*wlen*WRDBYTES);
   xprop->accum_block1[i] = wp;

   wp = (word32 *) __my_malloc(2*wlen*WRDBYTES);
   memset(wp, 0, 2*wlen*WRDBYTES);
   xprop->accum_block2[i] = wp;

   xprop_stp = xprop_stmts[i];
   astp = NULL;
   switch (xprop_stp->stmttyp) {
    case S_PROCA: break;
    case S_NBPROCA: 
     astp = xprop_stp;
     break;
    case S_DELCTRL:
     dctp = xprop_stp->st.sdc;
     astp = dctp->actionst;

     /* DBG remove --- */
     if (astp->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);
     /* ------ */
     break;
    default: __case_terr(__FILE__, __LINE__); break;
   }

   /* order doesn't matter just put it on front of the list */
   /* this assign needs to be the entire ID since it must assign all */
   /* rhs accum bits */
   xprop->astmts[ndx] = get_new_xprop_assign(xprop_stp, np);

   /* alloc accum for the net and init all bits */
   if (np->xprop_accum == NULL)
    {
     wlen = wlen_(np->nwid);
     np->xprop_accum = (word32 *) __my_malloc(2*wlen*WRDBYTES);
     memset(np->xprop_accum, 0xff, 2*wlen*WRDBYTES);
    }
  }
 return(xprop);
}
   
/*
 * Get a new lhs assign statement.  For the compiler these may need to
 * get a pre added non-blocking assign since nb have fixed structs which
 * are needed at prep time.  For interpreter just alloc a new stmt.
 */
struct st_t *get_new_xprop_assign(struct st_t *stp, struct net_t *np)
{
 struct st_t *new_stp, *astp;
 struct expr_t *lhsx;
 struct delctrl_t *dctp;

 __xprop_copying = TRUE; 
 /* if compiler may have to get the new stmt otherwise alloc a new one */
 if (__compiled_sim)
  {
   if (stp->xprop_nbu.xprop_astp != NULL) 
    {
     new_stp = stp->xprop_nbu.xprop_astp;
    }
   else new_stp = xprop_copy_stmt(stp);
  }
 else new_stp = xprop_copy_stmt(stp);
 __xprop_copying = FALSE; 

 astp = NULL;
 switch (new_stp->stmttyp) {
  case S_PROCA: 
  case S_NBPROCA: 
   astp = new_stp;
   break;
  case S_DELCTRL:
   dctp = new_stp->st.sdc;
   if (__compiled_sim)
    {
     /* DBG remove --- */
     astp = dctp->xprop_nb_actionst;
     if (astp == NULL) __misc_terr(__FILE__, __LINE__);
     if (astp->xprop_nbu.xprop_astp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ----- */
    }
   else astp = dctp->actionst;

   /* DBG remove --- */
   if (astp->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);
   /* ------ */
   break;
  default: __case_terr(__FILE__, __LINE__); break;
 }

 /* if lhs is not an ID must convert to ID */
 lhsx = astp->st.spra.lhsx;
 if (lhsx->optyp != ID)
  {
   lhsx->optyp = ID;
   lhsx->lu.sy = np->nsym;
   lhsx->szu.xclen = np->nwid;
  }
 return(new_stp);
}

/*
 *  Check if stmt is eligible for xprop, if not return false.
 */
static int32 if_stmt_lhs_assign(struct st_t *stp, int32 slevel, int32 do_alloc)
{
 struct xprop_t *xprop;
 struct net_t *np;
 int32 i, save_ndx, has_nested, has_one_id;

 /* all stmt types better be of the correct type */
 save_ndx = __xprop_net_ndx;
 has_nested = FALSE;
 has_one_id = TRUE;
 if (!is_stlst_lhs_assign(stp->st.sif.thenst, &has_nested, &has_one_id, stp))
  {
   return(FALSE);
  }
 /* if it is a dummy xprop created else no need to check */
 if (stp->st.sif.elsest != NULL)
  {
   if (!is_stlst_lhs_assign(stp->st.sif.elsest, &has_nested, &has_one_id, stp))
    {
     return(FALSE);
    }
  }

 /* now must make sure all lhs nets never appear on the rhs */
 for (i = 0; i < __xprop_net_ndx; i++)
  {
   np = __xprop_lhs_nets[i];
   /* only if stmt assign is a proc assign is this true */
   if (__xprop_stmts[i]->stmttyp != S_PROCA) continue;
   if (__is_stlst_net_on_rhs_assign(stp->st.sif.thenst, np, stp))
    {
     return(FALSE);
    }
   /* if it is a dummy xprop created else no need to check */
   if (stp->st.sif.elsest != NULL)
    {
     if (__is_stlst_net_on_rhs_assign(stp->st.sif.elsest, np, stp))
      {
       return(FALSE);
      }
    }
  }

 /* first pass just marks does not allocate */
 if (!do_alloc)
  {
   /* even if no nets still need to treat need to alloc xprop */
   return(TRUE);
  }
   
 /* --- DBG remove --- */
 if (!stp->xprop_eligible) __misc_terr(__FILE__, __LINE__); 
 if (stp->st.sif.xprop != NULL) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* if top level entry if stmt use top level */
 if (slevel == 0)
  {
   xprop = setup_xprop_lhs_nets(-1, has_nested, has_one_id);
   if (stp->st.sif.xedge_dce)
    {
     xprop->xevents = (struct tev_t **) 
     __my_malloc(sizeof(struct tev_t *)*__inst_mod->flatinum);
     memset(xprop->xevents, 0, sizeof(struct tev_t *)*__inst_mod->flatinum);
    }
   stp->st.sif.xprop = xprop;
   __xprop_net_ndx = 0;
   if (xprop == NULL) return(FALSE);
   return(TRUE);
  }
 /* local if stmt xprop */
 xprop = setup_xprop_lhs_nets(save_ndx, has_nested, has_one_id);
 if (stp->st.sif.xedge_dce)
  {
   xprop->xevents = (struct tev_t **) 
   __my_malloc(sizeof(struct tev_t *)*__inst_mod->flatinum);
   memset(xprop->xevents, 0, sizeof(struct tev_t *)*__inst_mod->flatinum);
  }
 stp->st.sif.xprop = xprop;
 __xprop_net_ndx = 0;
 return(TRUE);
}

/*
 * Check stmt list to make sure it is eligible.  Currently only allowing
 * the following:
 *
 *  if/case with assigns (=, <=, <= #delay)
 *  
 *  All other stmts will just treat the if/case stmt as normal
 */
static int32 is_stlst_lhs_assign(struct st_t *hd_stp, int32 *has_nested,
 int32 *has_one_id, struct st_t *top_stp) 
{
 struct csitem_t *csip, *dflt_csip;
 struct st_t *stp, *astp;
 struct delctrl_t *dctp;


 for (stp = hd_stp; stp != NULL; stp = stp->stnxt)
  {
   switch (stp->stmttyp) {
    case S_IF:
     *has_nested = TRUE;
     if (!is_stlst_lhs_assign(stp->st.sif.thenst, has_nested, has_one_id, 
           top_stp)) 
      {
        return(FALSE);
      }
     /* if xprop created else clause this is known to be good */
     if (stp->st.sif.elsest != NULL)
      {
       if (!is_stlst_lhs_assign(stp->st.sif.elsest, has_nested, has_one_id, 
            top_stp)) 
        {
         return(FALSE);
        }
      }
     break;
    case S_CASE:
     *has_nested = TRUE;
     dflt_csip = stp->st.scs.csitems;
     for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
      {
       if (!is_stlst_lhs_assign(csip->csist, has_nested, has_one_id, top_stp)) 
        return(FALSE);
      }
     if (dflt_csip->csist != NULL)
      {
       if (!is_stlst_lhs_assign(dflt_csip->csist, has_nested, has_one_id,
             top_stp)) 
        {
         return(FALSE);
        }
      }
     break;
    case S_PROCA: 
    case S_NBPROCA: 
     if (!add_lhs_stmt(stp, stp, top_stp)) return(FALSE);
     break;
    case S_DELCTRL:
     /* non-blocking with delay are legal */
     dctp = stp->st.sdc;
     astp = dctp->actionst;
     if (astp->stmttyp != S_NBPROCA) 
      {
       /* may need to record the stmt which is not supported */
       emit_xprop_not_eligible(top_stp, stp, NULL, NULL, 
         NOT_ELIGIBLE_ILLEGAL_STMT);
       return(FALSE);
      }
     if (!add_lhs_stmt(stp, astp, top_stp)) return(FALSE);
     break;
    case S_STNONE:
     /* if empty block cannot always assume id is set */
     *has_one_id = FALSE;
     break;
    case S_GOTO:
    case S_NULL:
     break;
    default: 
     /* may need to record the stmt which is not supported */
     emit_xprop_not_eligible(top_stp, stp, NULL, NULL, 
       NOT_ELIGIBLE_ILLEGAL_STMT);
     return(FALSE);
   }
  }
 return(TRUE);
}


/*
 * check if net is used on the rhs of a stmt list - if not may have to
 * record the reason why
 */
extern int32 __is_stlst_net_on_rhs_assign(struct st_t *hd_stp, 
 struct net_t *lhsnp, struct st_t *top_stp) 
{
 struct expr_t *rhsx, *lhsx;
 struct st_t *stp, *astp;
 struct delctrl_t *dctp;
 struct csitem_t *csip, *dflt_csip;


 for (stp = hd_stp; stp != NULL; stp = stp->stnxt)
  {
   switch (stp->stmttyp) {
    case S_IF:
     /* if lhs net is a proc assign and used in block as condition - cannot */
     /* include the stmt */
     if (xprop_net_used_on_rhs(stp->st.sif.condx, lhsnp))
      {
       emit_xprop_not_eligible(top_stp, NULL, NULL, lhsnp, 
         NOT_ELIGIBLE_LHS_COND);
       return(TRUE);
      }
     if (__is_stlst_net_on_rhs_assign(stp->st.sif.thenst, lhsnp, top_stp))
      {
       emit_xprop_not_eligible(top_stp, NULL, NULL, lhsnp, 
         NOT_ELIGIBLE_LHS_RHS_PROCA);
       return(TRUE);
      }
     /* AIV XIF */
     /* if xprop else had no else this is dummy assign to self else block */
     if (stp->st.sif.elsest != NULL)
      {
       if (__is_stlst_net_on_rhs_assign(stp->st.sif.elsest, lhsnp, top_stp))
        {
         emit_xprop_not_eligible(top_stp, NULL, NULL, lhsnp, 
           NOT_ELIGIBLE_LHS_RHS_PROCA);
         return(TRUE);
        }
      }
     break;
    case S_CASE:
     dflt_csip = stp->st.scs.csitems;
     /* if lhs net is a proc assign and used in block as condition - cannot */
     /* include the stmt */
     if (xprop_net_used_on_rhs(stp->st.scs.csx, lhsnp))
      {
       emit_xprop_not_eligible(top_stp, NULL, NULL, lhsnp, 
         NOT_ELIGIBLE_LHS_COND);
       return(TRUE);
      }
     for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
      {
       if (__is_stlst_net_on_rhs_assign(csip->csist, lhsnp, top_stp)) 
        {
         emit_xprop_not_eligible(top_stp, NULL, NULL, lhsnp, 
           NOT_ELIGIBLE_LHS_RHS_PROCA);
         return(TRUE);
        }
      }
     if (dflt_csip->csist != NULL)
      {
       if (__is_stlst_net_on_rhs_assign(dflt_csip->csist, lhsnp, top_stp)) 
        {
         emit_xprop_not_eligible(top_stp, NULL, NULL, lhsnp, 
           NOT_ELIGIBLE_LHS_RHS_PROCA);
         return(TRUE);
        }
      }
     break;
    case S_PROCA: 
    case S_NBPROCA: 
     rhsx = stp->st.spra.rhsx;
     lhsx = stp->st.spra.lhsx;
     if (xprop_lhsexpr_var_ndx_uses_lhsnet(lhsx, lhsnp)) 
      {
       emit_xprop_not_eligible(top_stp, stp, NULL, lhsnp, 
         NOT_ELIGIBLE_LHS_VARNDX);
       return(TRUE);
      }
     if (xprop_net_used_on_rhs(rhsx, lhsnp)) 
      {
       emit_xprop_not_eligible(top_stp, NULL, NULL, lhsnp, 
         NOT_ELIGIBLE_LHS_RHS_PROCA);
       return(TRUE);
      }
     break;
    case S_DELCTRL:
     /* non-blocking with delay are legal */
     dctp = stp->st.sdc;
     astp = dctp->actionst;
     if (astp->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);

     rhsx = astp->st.spra.rhsx;
     lhsx = astp->st.spra.lhsx;
     if (xprop_lhsexpr_var_ndx_uses_lhsnet(lhsx, lhsnp)) 
      {
       emit_xprop_not_eligible(top_stp, stp, NULL, lhsnp, 
         NOT_ELIGIBLE_LHS_VARNDX);
       return(TRUE);
      }
     if (xprop_net_used_on_rhs(rhsx, lhsnp)) 
      {
       emit_xprop_not_eligible(top_stp, NULL, NULL, lhsnp, 
         NOT_ELIGIBLE_LHS_RHS_PROCA);
       return(TRUE);
      }
     break;
    case S_STNONE:
    case S_GOTO:
    case S_NULL:
     break;
    default: return(FALSE);
   }
  }
 return(FALSE);
}

/*
 * return TRUE if lhsnp is used as variable inndx into lhs expr
 * similar to __lhsexpr_var_ndx - but must compare index values
 */
static int32 xprop_lhsexpr_var_ndx_uses_lhsnet(struct expr_t *xp, 
 struct net_t *lhsnp)
{
 struct expr_t *sel_ndx, *ndx;
 struct net_t *np;

 switch (xp->optyp) {
  case GLBREF: case ID:
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   /* if index psel know first variable is not constant */
   return(TRUE);
  case PARTSEL:
   /* part select always constant */
   break;
  case LSB:
   np = xp->lu.x->lu.sy->el.enp;
   if (np->mda == NULL)
    {
     ndx = xp->ru.x;
     if (ndx->arr_select)
      {
       sel_ndx = ndx->next_ndx;
       if (sel_ndx->optyp == NUMBER || sel_ndx->optyp == ISNUMBER)
        {
         break;
        }
       if (xprop_net_used_on_rhs(sel_ndx, lhsnp))
        {
         return(TRUE);
        }
      }
     if (ndx->optyp == NUMBER || ndx->optyp == ISNUMBER) break;

     /* if net used as lhs index must return true */
     if (xprop_net_used_on_rhs(ndx, lhsnp))
      {
       return(TRUE);
      }
    }
   else
    {
     /* AIV 02/07/11 - if array select with variable need to save the index */
     ndx = xp->ru.x;
     if (ndx->arr_select)
      {
       sel_ndx = ndx->ru.x->next_ndx;
       if (sel_ndx->optyp == NUMBER || sel_ndx->optyp == ISNUMBER)
        {
         break;
        }
       if (xprop_net_used_on_rhs(sel_ndx, lhsnp))
        {
         return(TRUE);
        }
      }
     /* if any of the mda indices are variable return TRUE */
     if (ndx->folded_ndx) return(FALSE);
     /* if net used as lhs index must return true */
     if (xprop_net_used_on_rhs(ndx, lhsnp))
      {
       return(TRUE);
      }
     return(TRUE);
    }
   break; 
  case LCB:
   {
    struct expr_t *catxp;

    for (catxp = xp->ru.x; catxp != NULL; catxp = catxp->ru.x)
     {
      /* if var index must copy entire expr. */
      if (xprop_lhsexpr_var_ndx_uses_lhsnet(catxp->lu.x, lhsnp)) return(TRUE);
     }
   } 
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}
  
/*
 * return true if net is used on rhs of the expression 
 */
static int32 xprop_net_used_on_rhs(struct expr_t *rhsx, struct net_t *np)
{
 int32 save_on_rhs, on_rhs;

 save_on_rhs = np->n_onprocrhs;
 np->n_onprocrhs = FALSE;
 __chk_rhsexpr(rhsx, 0);
 on_rhs = np->n_onprocrhs;
 np->n_onprocrhs = save_on_rhs;
 return(on_rhs);
}


/*
 * add a lhs stmt (net) to the globals which are used to build the 
 * xprop structs - this handles concats as well
 */
static int32 add_lhs_stmt(struct st_t *nstp, struct st_t *lhs_stp,
 struct st_t *top_stp)
{
 struct expr_t *lhsx, *idndp, *fax;
 struct net_t *np;


 lhsx = lhs_stp->st.spra.lhsx;
 /* lhs cannot be XMR */
 if (lhsx->optyp == GLBREF) 
  {
   emit_xprop_not_eligible(top_stp, NULL, NULL, NULL, NOT_ELIGIBLE_LHS_XMR);
  }
 if (lhsx->optyp != LCB)
  {
   idndp = __get_lvalue_idndp(lhsx);
   np = idndp->lu.sy->el.enp;
   if (!add_lhs_net(np, nstp, top_stp)) 
     return(FALSE);
  }
 else
  {
   /* concat case */
   for (fax = lhsx->ru.x; fax != NULL; fax = fax->ru.x)
    {
     idndp = __get_lvalue_idndp(fax->lu.x);
     np = idndp->lu.sy->el.enp;
     if (!add_lhs_net(np, nstp, top_stp)) 
       return(FALSE);
    }
  }
 return(TRUE);
}

/*
 * add a lhs stmt (net) to the globals which are used to build the 
 * xprop structs 
 */
static int32 add_lhs_net(struct net_t *np, struct st_t *nstp,
 struct st_t *top_stp)
{
 struct st_t *ostp;
 int32 i, add_net_top, other_than_id;

 /* not handling arrays for now - ever? */
 if (np->n_isarr) 
  {
   emit_xprop_not_eligible(top_stp, NULL, NULL, np, NOT_ELIGIBLE_LHS_ARRAY);
   return(FALSE);
  }

 /* if net is ever forced cannot use xprop */
 if (np->frc_assgn_allocated)
  {
   emit_xprop_not_eligible(top_stp, NULL, NULL, np, NOT_ELIGIBLE_NET_FORCED);
   return(FALSE);
  }

 //be done twice
 /* check the top level stmt list first */
 add_net_top = TRUE;
 other_than_id = FALSE;
 for (i = 0; i < __xprop_net_ndx_top; i++)
  {
   if (np == __xprop_lhs_nets_top[i]) 
    {
     ostp = __xprop_stmts_top[i]; 
     if (!chk_lhs_assign_stmt(nstp, ostp, &other_than_id, top_stp)) 
      {
       return(FALSE);
      }
     /* if anything on lhs other than id need to mark it */
     if (other_than_id) 
      {
       __xprop_lhs_other_than_id_top[i] = TRUE;
      }
     add_net_top = FALSE;
    }
  }

 /* if net has not been added to top level do so */
 if (add_net_top)
  {
   __xprop_lhs_nets_top[__xprop_net_ndx_top] = np;
   __xprop_stmts_top[__xprop_net_ndx_top] = nstp;
   __xprop_lhs_other_than_id_top[__xprop_net_ndx_top] = 
    is_xprop_stmt_not_id(nstp);
   __xprop_net_ndx_top++;
  }

 /* same exact code with local level stmt list */
 other_than_id = FALSE;
 for (i = 0; i < __xprop_net_ndx; i++)
  {
   if (np == __xprop_lhs_nets[i]) 
    {
     ostp = __xprop_stmts[i]; 
     if (!chk_lhs_assign_stmt(nstp, ostp, &other_than_id, top_stp)) 
       return(FALSE);

     if (other_than_id) 
      {
       __xprop_lhs_other_than_id[i] = TRUE;
      }
     return(TRUE);
    }
  }

 /* add the net to the local xprop building lists */
 __xprop_lhs_nets[__xprop_net_ndx] = np;
 __xprop_stmts[__xprop_net_ndx] = nstp;
 __xprop_lhs_other_than_id[__xprop_net_ndx] = is_xprop_stmt_not_id(nstp);
 __xprop_net_ndx++;
 return(TRUE);
}
 
/*
 * return TRUE of lhs xprop stmt not an ID
 */
static int32 is_xprop_stmt_not_id(struct st_t *stp)
{
 struct st_t *astp;
 struct expr_t *lhsx;
 struct delctrl_t *dctp;

 astp = NULL;
 switch (stp->stmttyp) {
  case S_PROCA: 
  case S_NBPROCA: 
   astp = stp;
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;

   /* DBG remove --- */
   if (astp->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);
   /* ------ */
   break;
  default: __case_terr(__FILE__, __LINE__); break;
 }

 /* if lhsx is not an id return false */
 lhsx = astp->st.spra.lhsx;
 if  (lhsx->optyp != ID) return(TRUE);

 return(FALSE);
}


/*
 * return TRUE if lhs statement is correct type
 * stmts for each net must all be same style (=, <=, <= #delay).
 */
static int32 chk_lhs_assign_stmt(struct st_t *nstp, struct st_t *ostp,
 int32 *other_than_id, struct st_t *top_stp)
{
 struct st_t *astp;
 struct expr_t *lhsx;
 struct delctrl_t *dctp, *odctp;
 int32 is_consto, is_constn;
 word64 odel, ndel;

 *other_than_id = FALSE;
 /* stmt types must match */
 if (ostp->stmttyp != nstp->stmttyp) 
  {
   emit_xprop_not_eligible(top_stp, nstp, ostp, NULL, 
     NOT_ELIGIBLE_ASSIGNS_DONT_MATCH);
   return(FALSE);
  }

 if (nstp->stmttyp == S_DELCTRL)
  {
   dctp = nstp->st.sdc;
   astp = dctp->actionst;
   /* must be <= # style */
   if (astp->stmttyp != S_NBPROCA)
    return(FALSE);

   /* delays must be constant and match */
   odctp = ostp->st.sdc;
   is_constn = __check_delay_constant(dctp->dc_du, dctp->dc_delrep, &(ndel));
   if (!is_constn) 
    {
     emit_xprop_not_eligible(top_stp, nstp, NULL, NULL, 
        NOT_ELIGIBLE_NB_NOT_CONST);
     return(FALSE);
    }

   is_consto = __check_delay_constant(odctp->dc_du, odctp->dc_delrep, &(odel));
   if (!is_consto) return(FALSE);

   /* delay values must be the same */  
   if (ndel != odel) 
    {
     emit_xprop_not_eligible(top_stp, nstp, ostp, NULL, 
        NOT_ELIGIBLE_NB_NOT_SAME);
     return(FALSE);
    }


   lhsx = astp->st.spra.lhsx;
  }
 else 
  {
   lhsx = nstp->st.spra.lhsx;
  }

 /* if not ID set to TRUE for the bit mask */
 if (lhsx->optyp != ID) 
  {
   *other_than_id = TRUE;
  }

 return(TRUE);
}
     
/*
 * set xprop stmt parents xprop values
 */
static void set_parent_xprop_lstofsts(struct st_t *hdstp, int32 slevel)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = set_parent_xprop_stmt(stp, slevel);
  }
}

/*
 * set xprop stmt parents xprop values
 */
static struct st_t *set_parent_xprop_stmt(struct st_t *stp, int32 slevel)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;
 int32 fji, isx;
 struct st_t *fjstp, *orig_thenstp, *orig_elsestp;
 struct st_t *astp;
 struct delctrl_t *dctp;
 struct xprop_t *xprop, *save_last_xprop;

 save_last_xprop = NULL;
 switch ((byte) stp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_NULL: case S_STNONE:
  case S_PROCA: case S_RHSDEPROCA: case S_NBPROCA: case S_FORASSGN:
  case S_REPSETUP: case S_REPDCSETUP: case S_TSKCALL:
  case S_QCONTA: case S_QCONTDEA: case S_CAUSE: case S_DSABLE:
   break;
  case S_IF:
   orig_thenstp = stp->st.sif.thenst;
   orig_elsestp = stp->st.sif.elsest;
   isx = stp->xprop_eligible;
   if (isx)
    {
     xprop = stp->st.sif.xprop;
     save_last_xprop = __current_xprop;
     xprop->parent_xprop = __current_xprop;
     /* cannot handle this as lone if */
     if (__current_xprop != NULL)
      {
       xprop->top_single_item = FALSE;
      }
     __current_xprop = xprop;   
    }
   set_parent_xprop_lstofsts(orig_thenstp, slevel+isx);
   set_parent_xprop_lstofsts(orig_elsestp, slevel+isx);
   if (isx) __current_xprop = save_last_xprop;
   break;
  case S_CASE:
   /* if not converting to xcase cannot increment the slevel */
   isx = stp->xprop_eligible;
   if (isx)
    {
     xprop = stp->st.scs.xprop;
     save_last_xprop = __current_xprop;
     xprop->parent_xprop = __current_xprop;
     /* cannot handle this as lone case */
     if (__current_xprop != NULL)
      {
       xprop->top_single_item = FALSE;
      }
     __current_xprop = xprop;   
    }

   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
     set_parent_xprop_lstofsts(csip->csist, slevel+isx);
   if (dflt_csip->csist != NULL)
     set_parent_xprop_lstofsts(dflt_csip->csist, slevel+isx);
   if (isx) __current_xprop = save_last_xprop;
   break;
  case S_REPEAT:
   set_parent_xprop_lstofsts(stp->st.srpt.repst, slevel);
   break;
  case S_FOREVER: case S_WHILE:
   set_parent_xprop_lstofsts(stp->st.swh.lpst, slevel);
   break;
  case S_WAIT:
   set_parent_xprop_lstofsts(stp->st.swait.lpst, slevel);
   break;
  case S_FOR:
   set_parent_xprop_lstofsts(stp->st.sfor->forinc, slevel);
   set_parent_xprop_lstofsts(stp->st.sfor->forbody, slevel);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;
   /* AIV 02/16/12 - now including always (x) detection */
   /* only set one because xprop actionst list will have extra if parent */
   if (dctp->xprop_xedge_actionst != NULL)
     set_parent_xprop_lstofsts(dctp->xprop_xedge_actionst, slevel);
   else if (astp != NULL) set_parent_xprop_lstofsts(astp, slevel);
   break;
  case S_NAMBLK:
   set_parent_xprop_lstofsts(stp->st.snbtsk->tskst, slevel);
   break;
  case S_UNBLK:
   set_parent_xprop_lstofsts(stp->st.sbsts, slevel);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     set_parent_xprop_lstofsts(fjstp, slevel);
    }
   break;
  case S_GOTO:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}
  
/*
 * if any parents have per bit need to use per bit code - mark are
 * having per-bit for each parent xprop
 */
static void set_xprop_parent_lhs_ids_lstofsts(struct st_t *hdstp)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = set_xprop_parent_lhs_ids_stmt(stp);
  }
}

/*
 * if any parents have per bit need to use per bit code - mark are
 * having per-bit for each parent xprop
 */
static struct st_t *set_xprop_parent_lhs_ids_stmt(struct st_t *stp)
{
 struct csitem_t *csip, *dflt_csip;
 struct st_t *fjstp;
 struct st_t *astp;
 struct delctrl_t *dctp;
 struct xprop_t *xprop, *parent_xprop;
 int32 fji;

 switch ((byte) stp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_NULL: case S_STNONE:
  case S_PROCA: case S_RHSDEPROCA: case S_NBPROCA: case S_FORASSGN:
  case S_REPSETUP: case S_REPDCSETUP: case S_TSKCALL:
  case S_QCONTA: case S_QCONTDEA: case S_CAUSE: case S_DSABLE:
   break;
  case S_IF:
   if (stp->xprop_eligible)
    {
     xprop = stp->st.sif.xprop; 
     /* --- DBG remove --- */
     if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     parent_xprop = xprop->parent_xprop;
     if (parent_xprop != NULL) 
       set_xprop_ids_only_parent(xprop);
    }
   set_xprop_parent_lhs_ids_lstofsts(stp->st.sif.thenst);
   set_xprop_parent_lhs_ids_lstofsts(stp->st.sif.elsest);
   break;
  case S_CASE:
   if (stp->xprop_eligible)
    {
     xprop = stp->st.scs.xprop; 
     /* --- DBG remove --- */
     if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     parent_xprop = xprop->parent_xprop;
     if (parent_xprop != NULL) 
       set_xprop_ids_only_parent(xprop);
    }
   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
     set_xprop_parent_lhs_ids_lstofsts(csip->csist);
   if (dflt_csip->csist != NULL)
     set_xprop_parent_lhs_ids_lstofsts(dflt_csip->csist);
   break;
  case S_REPEAT:
   set_xprop_parent_lhs_ids_lstofsts(stp->st.srpt.repst);
   break;
  case S_FOREVER: case S_WHILE:
   set_xprop_parent_lhs_ids_lstofsts(stp->st.swh.lpst);
   break;
  case S_WAIT:
   set_xprop_parent_lhs_ids_lstofsts(stp->st.swait.lpst);
   break;
  case S_FOR:
   set_xprop_parent_lhs_ids_lstofsts(stp->st.sfor->forinc);
   set_xprop_parent_lhs_ids_lstofsts(stp->st.sfor->forbody);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;
   /* AIV 02/16/12 - now including always (x) detection */
   if (dctp->xprop_xedge_actionst != NULL)
     set_xprop_parent_lhs_ids_lstofsts(dctp->xprop_xedge_actionst);
   if (astp != NULL) set_xprop_parent_lhs_ids_lstofsts(astp);
   break;
  case S_NAMBLK:
   set_xprop_parent_lhs_ids_lstofsts(stp->st.snbtsk->tskst);
   break;
  case S_UNBLK:
   set_xprop_parent_lhs_ids_lstofsts(stp->st.sbsts);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     set_xprop_parent_lhs_ids_lstofsts(fjstp);
    }
   break;
  case S_GOTO:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}


/*
 * if parent xprop has per bit code all children must as well
 */
static void set_xprop_ids_only_parent(struct xprop_t *xprop)
{
 int32 i, j;
 struct xprop_t *parent_xprop;
 struct net_t *np, *np2, *pnp;

 parent_xprop = xprop->parent_xprop;
 /* must do all the parents first */
 if (parent_xprop->parent_xprop != NULL)
  {
   set_xprop_ids_only_parent(parent_xprop);
  }
 /* n^2 but these are normally small */
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];
   pnp = NULL;
   for (j = 0; j < parent_xprop->ncount; j++)
    {
     np2 = parent_xprop->lhsnets[j];
     if (np == np2)
      {
       pnp = np2;
       break;
      }
    }
   /* --- DBG remove --- */
   if (pnp == NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */

   /* if not id must mark as false */
   if (!parent_xprop->lhs_id_only[j])
     xprop->lhs_id_only[i] = FALSE;
  }
}

/*
 * used for xprop2 - concat a list of stmt lists
 */
static void concat_stmtlst(struct st_t *into_stp, struct st_t *next_stp)
{
 struct st_t *stp, *last_stp;
 
 last_stp = NULL;
 for (stp = into_stp; stp != NULL; stp = stp->stnxt)
  {
   last_stp = stp;
  }
 if (last_stp != NULL)
  {
   last_stp->stnxt = next_stp;
  }
}
   
/*
 * used for xprop2 make a stmt list rhs values all x
 */
static void convert_x_assigns_stlst(struct st_t *hd_stp)
{
 struct st_t *stp, *prev_stp, *save_stp;
 int32 update_last;
 
 prev_stp = NULL;
 for (stp = hd_stp; stp != NULL; )
  {
   save_stp = stp;
   update_last = TRUE;
   stp = convert_x_assign_stmt(stp, prev_stp, &update_last);
   /* if found duplicate in a row do not update the last list */
   if (update_last)
    {
     prev_stp = save_stp;
    }
  }
}

/*
 * used for xprop2
 * convert a stmt list of assigns rhs to all Xs to build the x if/case 
 * list setting
 */
static struct st_t *convert_x_assign_stmt(struct st_t *stp, 
 struct st_t *prev_stp, int32 *update_last)
{
 struct csitem_t *csip;
 struct csitem_t *dflt_csip;
 int32 fji, has_xmr, is_eq;
 struct st_t *fjstp;
 struct st_t *astp;
 struct expr_t *lhsx, *new_rhsx, *olhsx;
 struct delctrl_t *dctp;

 switch ((byte) stp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_STNONE: case S_NULL: break;
  case S_PROCA: 
  case S_NBPROCA: 
  case S_RHSDEPROCA:
   lhsx = stp->st.spra.lhsx;
   new_rhsx = make_x_expr(lhsx->szu.xclen);
   __free_xtree(stp->st.spra.rhsx);
   stp->st.spra.rhsx = new_rhsx;
   /* this gets the common case which has multiple */
   /* case stmts */
   /* 1: b = 1; */
   /* 2: b = 2; */
   if (prev_stp != NULL && prev_stp->stnxt == stp) 
    {
     /* if stmt types are the same and lhsx are the same can just link out */
     /* since know to be 'x */
     if (prev_stp->stmttyp == stp->stmttyp)
      {
       olhsx = prev_stp->st.spra.lhsx;
       is_eq = __cmp_xpr(lhsx, olhsx, &has_xmr);
       if (is_eq)
        {
         prev_stp->stnxt = stp->stnxt;
         *update_last = FALSE;
         break;
        }
      }
    }
   break;
  case S_QCONTA: 
   lhsx = stp->st.sqca->qclhsx;
   new_rhsx = make_x_expr(lhsx->szu.xclen);
   __free_xtree(stp->st.sqca->qcrhsx);
   stp->st.sqca->qcrhsx = new_rhsx;
   break;
  case S_FORASSGN:
  case S_REPSETUP: 
  case S_REPDCSETUP:
  case S_TSKCALL:
  case S_CAUSE: case S_DSABLE: case S_QCONTDEA: 
   break;
  case S_IF:
   convert_x_assigns_stlst(stp->st.sif.thenst);
   convert_x_assigns_stlst(stp->st.sif.elsest);
   break;
  case S_CASE:
   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
     convert_x_assigns_stlst(csip->csist);
   if (dflt_csip->csist != NULL)
     convert_x_assigns_stlst(dflt_csip->csist);
   if (stp->st.scs.xprop_lstp != NULL)
     convert_x_assigns_stlst(stp->st.scs.xprop_lstp);
   break;
  case S_REPEAT:
   convert_x_assigns_stlst(stp->st.srpt.repst);
   break;
  case S_FOREVER: case S_WHILE:
   convert_x_assigns_stlst(stp->st.swh.lpst);
   break;
  case S_WAIT:
   convert_x_assigns_stlst(stp->st.swait.lpst);
   break;
  case S_FOR:
   convert_x_assigns_stlst(stp->st.sfor->forinc);
   convert_x_assigns_stlst(stp->st.sfor->forbody);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;
   /* AIV 02/16/12 - now including always (x) detection */
   if (dctp->xprop_xedge_actionst != NULL)
     set_xprop_parent_lhs_ids_lstofsts(dctp->xprop_xedge_actionst);
   if (astp != NULL) convert_x_assigns_stlst(astp);
   break;
  case S_NAMBLK:
   convert_x_assigns_stlst(stp->st.snbtsk->tskst);
   break;
  case S_UNBLK:
   convert_x_assigns_stlst(stp->st.sbsts);
   break;
  case S_UNFJ:
   for (fji = 0;; fji++)
    {
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;
     convert_x_assigns_stlst(fjstp);
    }
   break;
  case S_GOTO:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(stp->stnxt);
}
   
/*
 * used for xprop2
 * create a lhswidth'bx expression
 */
static struct expr_t *make_x_expr(int32 blen)
{
 int32 wlen, xvi;
 struct expr_t *xp;
 word32 *wp;

 /* --- DBG remove --- */
 if (blen <= 0) __misc_terr(__FILE__, __LINE__);
 /* ---- */
 wlen = wlen_(blen);
 wp = (word32 *) __my_malloc(wlen*WRDBYTES);
 memset(wp, 0xff, wlen*WRDBYTES);
 /* need to mask off the high bits */
 wp[wlen - 1] &= __masktab[ubits_(blen)];
 xp = __alloc_newxnd();
 xp->optyp = NUMBER;
 xvi = __allocfill_cval_new(wp, wp, wlen);
 xp->ru.xvi = xvi;
 xp->ibase = BHEX;
 xp->szu.xclen = blen;
 return(xp);
}

/*
 * free an xprop struct 
 */
extern void __free_xprop(struct xprop_t *xprop)
{
 int32 ncount, i, wlen;
 struct net_t *np;
 word32 *wp;

 ncount = xprop->ncount;
 /* free all the bit masks */
 for (i = 0; i < ncount; i++)
  {
   np = xprop->lhsnets[i];
   wlen = wlen_(np->nwid);

   wp = xprop->xbitmask_block1_set[i];
   __my_free(wp, wlen*WRDBYTES);
  
   wp = xprop->xbitmask_block2_set[i];
   __my_free(wp, wlen*WRDBYTES);
     
   wp = xprop->bits_set[i];
   __my_free(wp, wlen*WRDBYTES);

   wp = xprop->accum_block1[i];
   __my_free(wp, wlen*WRDBYTES);

   wp = xprop->accum_block2[i];
   __my_free(wp, wlen*WRDBYTES);
  }
 __my_free(xprop->xbitmask_block1_set, sizeof(word32 *)*ncount); 
 __my_free(xprop->xbitmask_block2_set, sizeof(word32 *)*ncount); 
 __my_free(xprop->bits_set, sizeof(word32 *)*ncount); 
 __my_free(xprop->accum_block1, sizeof(word32 *)*ncount); 
 __my_free(xprop->accum_block2, sizeof(word32 *)*ncount); 
 __my_free(xprop->lhs_id_only, sizeof(int32)*ncount); 
 __my_free(xprop->net_block1_set, sizeof(int32)*ncount); 
 __my_free(xprop->net_block2_set, sizeof(int32)*ncount); 
 __my_free(xprop->lhsnets, sizeof(struct net_t *)*ncount); 
 __my_free(xprop->astmts, sizeof(struct st_t *)*ncount); 
 __my_free(xprop, sizeof(struct xprop_t)); 
}

/* 
 * ROUTINES TO DO THE X-PROPAGATION EXECUTION CODE FOR INTERPRETER
 */

/*
 * New xprop if stmt handling.  The if stmt xprop code combines the if/else 
 * sections 'combining' rhs value much like ?: if the condition conatins an X.
 * 
 * If evaled_xsp is passed it is known to be the top-level xprop entry point
 * and contain an X, if no evaled_xsp it is a nested if inside another
 * if/case stmt.
 *
 * If stmts which contain no else and the condition contains an X are simply
 * skipped.
 */
extern struct st_t *__exec_xprop_if_stmt(struct st_t *stp, int32 slevel,
 struct xstk_t *evaled_xsp)
{
 int32 has_abit, has_bbit;
 struct st_t *nxtstp;
 struct xprop_t *xprop;
 struct xstk_t *xsp;

 xprop = stp->st.sif.xprop;
 /* DBG remove --- */
 if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* if entry this will be passed in as xsp */
 if (evaled_xsp == NULL)
  {
   xsp = __eval_xpr(stp->st.sif.condx);
  }
 else xsp = evaled_xsp;

 /* condition T (non zero) only if at least 1, 1 */
 if (xsp->xslen <= WBITS)
  {
   has_abit = (xsp->ap[0] != 0L);
   has_bbit = (xsp->bp[0] != 0L);
  }
 else 
  {
   has_abit = !(vval_is0_(xsp->ap, xsp->xslen));
   has_bbit = !(vval_is0_(xsp->bp, xsp->xslen));
  }

 /* if it contains an x/z need to combine values */
 if (has_bbit)
  {
   if (__xprop_trace_on) 
    {
     __trace_xprop_stmt_write(stp, xsp->ap, xsp->bp, xsp->xslen);
    }
   /* must combine both blocks */
   xprop->xblock = 0;
   set_xprop_accum_block(xprop);
   nxtstp = exec_xprop_stmts(stp->st.sif.thenst, xprop, slevel+1);
   /* if the else is created and uses per bit need to copy the first */
   /* blocks bitmask back */
   if (stp->st.sif.elsest != NULL) 
    {
     xprop->xblock = 1;
     exec_xprop_stmts(stp->st.sif.elsest, xprop, slevel+1);
     set_restore_xprop_accum_block(xprop, TRUE, FALSE);
    }
   else set_restore_xprop_accum_block(xprop, FALSE, TRUE);
  }
 else
  {
   /* does not contain an x bit but still needs to combine values */
   if (has_abit) 
    {
     set_xprop_accum_block(xprop);
     exec_xprop_stmts(stp->st.sif.thenst, xprop, slevel+1);
     set_restore_xprop_accum_block(xprop, FALSE, FALSE);
    }
   else if (stp->st.sif.elsest != NULL) 
    {
     set_xprop_accum_block(xprop);
     exec_xprop_stmts(stp->st.sif.elsest, xprop, slevel+1);
     set_restore_xprop_accum_block(xprop, FALSE, FALSE);
    }
   nxtstp = stp->stnxt;
  }
 if (evaled_xsp == NULL) __pop_xstk();
 return(nxtstp);
}
       
/*
 * New xprop caset stm handling.  The case stmt xprop combines each
 * element 'combining' rhs value much like ?: if the condition conatins an X.
 * 
 * If evaled_xsp is passed it is known to be the top-level xprop entry point
 * and contain an X, if no evaled_xsp it is a nested if inside another
 * if/case stmt.
 *
 * AIV 01/20/12 - changed how cases with default/without are combined/X
 * Need to count the number of x/zs and count the number of possbile item
 * matches
 *  if (has default)
 *    if (number_matched != (1 << num_xs)) combine default
 *  else (number_matched != (1 << num_xs)) all Xs since intentions not known 
 */
extern void __exec_xprop_case(struct st_t *stp, int32 slevel, 
 struct xstk_t *evaled_xsp)
{
 word32 aw, bw; 
 struct xstk_t *itemxsp, *selxsp;
 struct csitem_t *csip;
 struct exprlst_t *xplp;
 int32 selxlen, xslen, selwlen, i;
 int32 xcount, wlen, num_matched, combine_to_self;
 word32 *wp;
 struct csitem_t *dflt_csip;
 struct xprop_t *xprop;

 xprop = stp->st.scs.xprop;
 /* DBG remove --- */
 if (xprop == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 xprop->xblock = 0;
 selxlen = stp->st.scs.maxselwid;
 if (evaled_xsp == NULL)
  {
   selxsp = __eval_xpr(stp->st.scs.csx);
  }
 else selxsp = evaled_xsp;

 
 set_xprop_accum_block(xprop);
 /* if bpart is zero just handle as a regular case stmt */
 /* if nested still need to do the combining values - only can do this */
 /* if it is a top level case stmt */
 wp = selxsp->bp;
 xslen = selxsp->xslen;
 /* AIV 01/20/12 - this has to count the x/z bits for later checking */
 /* if all cases were accounted for and combining in the default */
 if (xslen <= WBITS)
  {
   xcount = __builtin_popcountl(wp[0]);
  }
 else
  {
   xcount = 0;
   wlen = wlen_(xslen);
   for (i = 0; i < wlen; i++)
    {
     xcount += __builtin_popcountl(wp[i]);
    }
  }


 /* record the x/z case if tracing on */
 if (__xprop_trace_on && xcount)
  {
   __trace_xprop_stmt_write(stp, selxsp->ap, selxsp->bp, xslen);
  }

 dflt_csip = stp->st.scs.csitems;

 /* if result of selector is not as wide as needed widen */
 /* case needs w bits width but selector is wire < w */
 /* DBG remove -- */
 /* AIV 01/20/12 - reals are not included as xprop case stmts */
 /* if expression real, convert to 32 bit reg */
 if (stp->st.scs.csx->is_real) __misc_terr(__FILE__, __LINE__);
 if (xslen > selxlen) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 if (xslen < selxlen)
  {
   if (stp->st.scs.csx->has_sign && !stp->st.scs.csx->unsgn_widen)
    __sgn_xtnd_widen(selxsp, selxlen);
   else __sizchg_widen(selxsp, selxlen);
  }

 csip = dflt_csip->csinxt;

 /* case case 1: fits in one word32 */
 num_matched = 0;
 if (selxlen <= WBITS)
  {
   aw = selxsp->ap[0];
   bw = selxsp->bp[0];
   for (; csip != NULL; csip = csip->csinxt)
    {
     for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
      {
       itemxsp = __eval2_xpr(xplp->xp);
     
       if (itemxsp->xslen > selxlen) __narrow_sizchg(itemxsp, selxlen);
       else if (itemxsp->xslen < selxlen)
        {
         if (xplp->xp->has_sign && !xplp->xp->unsgn_widen)
          __sgn_xtnd_widen(itemxsp, selxlen);
         else __sizchg_widen(itemxsp, selxlen);
        }

       /* no conversion needed becaause know item may be too narrow only */
       /* must 0 any don't care bits with either x/z bit 0 mask */
       if ((((aw ^ itemxsp->ap[0]) | (bw ^ itemxsp->bp[0]))
        & ~(bw | itemxsp->bp[0])) == 0)
        { 
         xprop->xblock = num_matched;
         exec_xprop_stmts(csip->csist, xprop, slevel+1);
         num_matched += xplp->num_xmatch;
         /* AIV 02/08/12 - for the second and greater case items must make */
         /* sure that all variables that were written to in the first */
         /* match are also written to in the second */
         /* if only one id do not need to do this */
         if (num_matched > 1 && !xprop->has_one_id_only)
          {
           xprop_check_case_net_assigned(xprop);
          }
        }
       __pop_xstk();
      }
    }

   if (evaled_xsp == NULL) __pop_xstk();

   if (dflt_csip->csist != NULL) 
    {
     if (xcount)
      {
       /* if all possible Xs are not included must combine the default */
       if (num_matched < (1 << xcount)) 
        {
         xprop->xblock = num_matched;
         exec_xprop_stmts(dflt_csip->csist, xprop, slevel+1);
        }
       set_restore_xprop_accum_block(xprop, num_matched, FALSE);
      }
     else set_restore_xprop_accum_block(xprop, FALSE, FALSE);
    }
   else 
    {
     xprop->xblock = (num_matched > 1);
     /* if no default and all the possible Xs are not matched just X out */
     combine_to_self = (num_matched < (1 << xcount));
     set_restore_xprop_accum_block(xprop, (num_matched > 1), combine_to_self);
    }
   return;
  }

 /* nearly identical for the wide case */
 /* case case 2: wider than 1 word32 */
 selwlen = wlen_(selxlen);
 for (; csip != NULL; csip = csip->csinxt)
  {
   for (xplp = csip->csixlst; xplp != NULL; xplp = xplp->xpnxt)
    {
     itemxsp = __eval2_xpr(xplp->xp);

     if (itemxsp->xslen > selxlen) __narrow_sizchg(itemxsp, selxlen);
     else if (itemxsp->xslen < selxlen)
      {
       if (xplp->xp->has_sign && !xplp->xp->unsgn_widen)
        __sgn_xtnd_widen(itemxsp, selxlen);
       else __sizchg_widen(itemxsp, selxlen);
      }

     for (i = 0; i < selwlen; i++)
      {
       if ((((selxsp->ap[i] ^ itemxsp->ap[i])
        | (selxsp->bp[i] ^ itemxsp->bp[i]))
        & ~(selxsp->bp[i] | itemxsp->bp[i])) != 0) goto nxt_x;
      }
   xprop->xblock = num_matched;
   exec_xprop_stmts(csip->csist, xprop, slevel+1);
   num_matched++;
   if (num_matched > 1)
    {
      xprop_check_case_net_assigned(xprop);
    }
nxt_x:
     __pop_xstk();
    }
  }
 /* none match do the default - if no default it is x */
 if (evaled_xsp == NULL) __pop_xstk();

 if (dflt_csip->csist != NULL) 
  {
   /* if xcount must include default */
   if (xcount)
    {
     if (num_matched != (1 << xcount)) 
      {
       xprop->xblock = num_matched;
       exec_xprop_stmts(dflt_csip->csist, xprop, slevel+1);
      }
     set_restore_xprop_accum_block(xprop, num_matched, FALSE);
    }
   else set_restore_xprop_accum_block(xprop, FALSE, FALSE);
  }
 else 
  {
   xprop->xblock = (num_matched > 1);
   combine_to_self = (num_matched < (1 << xcount));
   set_restore_xprop_accum_block(xprop, (num_matched > 1), combine_to_self);
  }
}
            
/* 
 * AIV 02/08/12 - for the second and greater case items must make 
 * sure that all variables that were written to in the first 
 * match are also written to in the second, othwerwise must make X
 */
static void xprop_check_case_net_assigned(struct xprop_t *xprop)
{
 int32 i, wlen;
 struct net_t *np;
 word32 *setbits_wp, *accum_wp;

 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];
   /* if set in the first block and not the second - set accumulator to X */ 
   /* and set */
   // AIV LOOKATME - could just optimize this as for now on known to be X
   // with a known_x - this way does no more combining
   // AIV LOOKATME - not doing per bit saving here - intentions unknown so
   // setting values to X
   if (xprop->net_block1_set[i] && !xprop->net_block2_set[i]) 
    {
     xprop->net_block2_set[i] = TRUE;
     
     wlen = wlen_(np->nwid);
     /* all bits set marking */
     setbits_wp = xprop->bits_set[i];
     memset(setbits_wp, 0xff, wlen*WRDBYTES);

     /* set to x */
     accum_wp = xprop->accum_block2[i];
     set_regtox_(accum_wp, &(accum_wp[wlen]), np->nwid);
    }
  }
}

/*
 * init the xprop lhs net values upon entry into if/case stmt
 */
//AIV XPROP - this can be static when compiler works
static void set_xprop_accum_block(struct xprop_t *xprop)
{
 int32 i, wlen;
 struct net_t *np;

 /* go through each on net on the lhs init flags */ 
 xprop->x_entered = TRUE;
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];
   /* save the parent xprop net index */
   xprop->parent_net_indices[i] = np->n_xprop_ndx;
   np->n_xprop_ndx = i;
   /* init the across block setting flags */
   xprop->net_block1_set[i] = 0;
   xprop->net_block2_set[i] = 0;
   /* init the across block setting flags - per bit */
   if (!xprop->lhs_id_only[i])
    {
     wlen = wlen_(np->nwid);
     memset(xprop->bits_set[i], 0, wlen*WRDBYTES);
     memset(xprop->xbitmask_block1_set[i], 0, wlen*WRDBYTES);
     memset(xprop->xbitmask_block2_set[i], 0, wlen*WRDBYTES);
    }
  }
}

/*
 * on exit to xprop stmt restore flags and combine parent xprop block
 * setting if there is one.  If force_x is on must force value to x.
 */
static void set_restore_xprop_accum_block(struct xprop_t *xprop, 
 int32 combine_blocks, int32 combine_to_self)
{
 int32 i, wlen, last_ndx, bi, block1_set, block2_set, wi, set_block;
 struct xprop_t *parent_xprop;
 word32 *b1wp, *b2wp, *parent_wp, *combine_wp;
 word32 *net_accum_wp, *parent_accum1_wp, *parent_accum2_wp, *accum_wp;
 word32 *setbits_wp, *parent_setbits_wp, *other_wp, *net_wp;
 word32 aval, bval, sval;
 struct net_t *np;
 struct xstk_t *xsp;

 xprop->x_entered = FALSE;
 /* if X out no need to combine blocks */
 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];

   wlen = wlen_(np->nwid);
   net_accum_wp = np->xprop_accum;
   /* case 1: lhs known to be ID set entire net */
 
   if (xprop->xblock == 0)
    {
     accum_wp = xprop->accum_block1[i];
     other_wp = xprop->accum_block2[i];
    }
   else 
    {
     accum_wp = xprop->accum_block2[i];
     other_wp = xprop->accum_block1[i];
    }

   /* AIV 02/23/12 - this must combine to its current value not set to X */
   if (combine_to_self)
    {
     /* need to mark accum flag set so this will later X out */
     //AIV LOOKATME - not sure about this but if case doesn't match set to X
     /* could 'X' out all values just not setting for now */
     /*
     if (!np->n_xprop_accum_set)
      {
       np->n_xprop_accum_set = TRUE;
       xprop->net_block1_set[i] = TRUE;
       set_regtox_(accum_wp, &(accum_wp[wlen]), np->nwid); 
       goto combine;
      }
      */
     if (!np->n_xprop_accum_set) goto combine;

     np->n_xprop_accum_set = TRUE;
     xprop->net_block1_set[i] = TRUE;
     net_wp = &(__idp[np->nva_ofs]);
     /* if vector just combine into its current value */
     if (np->srep == SR_VEC)
      {
       combine_xprop_accum(accum_wp, net_wp, &(net_wp[wlen]), np->nwid);
      }
     /* if scalar just create word and combine */
     else if (np->srep == SR_SCAL || np->srep == SR_SSCAL)
      {
       sval = *net_wp; 
       aval = sval & 1;
       bval = (sval >> 1) & 1;
       combine_xprop_accum(accum_wp, &aval, &bval, 1);
      }
     else 
      {
       /* all others create a/b parts */
       push_xstk_(xsp, np->nwid);
       __ld_wire_val_wrds(xsp->ap, xsp->bp, np);
       combine_xprop_accum(accum_wp, xsp->ap, xsp->bp, 1);
       __pop_xstk();
      }
    }
combine:

   if (combine_blocks)
    {
     combine_xprop_accum(accum_wp, other_wp, &(other_wp[wlen]), np->nwid);
    }
   memcpy(net_accum_wp, accum_wp, 2*wlen*WRDBYTES);

   if (xprop->lhs_id_only[i])
    {
     block1_set = xprop->net_block1_set[i];
     block2_set = xprop->net_block2_set[i];

     /* DBG remove -- */
     if (block1_set == -1) __misc_terr(__FILE__, __LINE__);
     if (block2_set == -1) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     if (combine_blocks) 
      {
       if (block1_set != block2_set)
        {
         set_regtox_(net_accum_wp, &(net_accum_wp[wlen]), np->nwid);
        }
      }


     parent_xprop = xprop->parent_xprop;
     /* can have empty if block with no nets nothing to combine */
     /* if parent has not been entered there is no reason to combine it */
     if (parent_xprop != NULL && parent_xprop->x_entered)
      {
       last_ndx = xprop->parent_net_indices[i];
       /* DBG remove -- */
       if (last_ndx > parent_xprop->ncount) __misc_terr(__FILE__, __LINE__);
       /* ---- */
       if (xprop->xblock == 0) set_block = block1_set;
       else set_block = block2_set;

       /* if never set do not set accum values */
       if (set_block)
        {
         if (parent_xprop->xblock == 0)
          {
           parent_xprop->net_block1_set[last_ndx] |= set_block;
           parent_accum1_wp = parent_xprop->accum_block1[last_ndx]; 
           memcpy(parent_accum1_wp, accum_wp, 2*wlen*WRDBYTES);
          }
         else
          {
           parent_xprop->net_block2_set[last_ndx] |= set_block;
           parent_accum2_wp = parent_xprop->accum_block2[last_ndx]; 
           memcpy(parent_accum2_wp, accum_wp, 2*wlen*WRDBYTES);
          }
        }
      }
     xprop->net_block1_set[i] = -1;
     xprop->net_block2_set[i] = -1;
    }
   /* case 2: lhs contains some selects part/bsel - need to handle per bit */
   else
    {
     b1wp = xprop->xbitmask_block1_set[i];
     b2wp = xprop->xbitmask_block2_set[i];
     /* DBG remove -- */
     if (b1wp == NULL) __misc_terr(__FILE__, __LINE__);
     if (b2wp == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     if (combine_blocks)
      {
       /* need to set per bit values */
       for (bi = 0; bi < np->nwid; bi++)
        {
         block1_set = rhsbsel_(b1wp, bi);
         block2_set = rhsbsel_(b2wp, bi);

         if (block1_set != block2_set)
          {
           /* set just this one bit to x */
           __lhsbsel(net_accum_wp, bi, 1);
           __lhsbsel(&(net_accum_wp[wlen]), bi, 1);
          }
        }
      }

     parent_xprop = xprop->parent_xprop;
     /* can have empty if block with no nets nothing to combine */
     /* AIV 10/25/11 - this should only enter if x_entered bit set */
     if (parent_xprop != NULL && parent_xprop->x_entered)
      {
       last_ndx = xprop->parent_net_indices[i];
       /* DBG remove -- */
       if (last_ndx > parent_xprop->ncount) __misc_terr(__FILE__, __LINE__);
       /* ---- */
  
       if (xprop->xblock == 0) combine_wp = b1wp;
       else combine_wp = b2wp;

       setbits_wp = xprop->bits_set[i];
       parent_setbits_wp = parent_xprop->bits_set[last_ndx];
       if (parent_xprop->xblock == 0)
        {
         parent_wp = parent_xprop->xbitmask_block1_set[last_ndx];
         parent_accum1_wp = parent_xprop->accum_block1[last_ndx]; 
         /* need to set per bit values */
         for (bi = 0; bi < np->nwid; bi++)
          {
           block1_set = rhsbsel_(setbits_wp, bi);
           if (block1_set)
            {
             aval = rhsbsel_(accum_wp, bi);
             bval = rhsbsel_(&(accum_wp[wlen]), bi);
             __lhsbsel(parent_accum1_wp, bi, aval);
             __lhsbsel(&(parent_accum1_wp[wlen]), bi, bval);
            }
          }
        }
       else
        {
         parent_wp = parent_xprop->xbitmask_block2_set[last_ndx];
         parent_accum2_wp = parent_xprop->accum_block2[last_ndx]; 
         for (bi = 0; bi < np->nwid; bi++)
          {
           block2_set = rhsbsel_(setbits_wp, bi);
           if (block2_set)
            {
             aval = rhsbsel_(accum_wp, bi);
             bval = rhsbsel_(&(accum_wp[wlen]), bi);
             __lhsbsel(parent_accum2_wp, bi, aval);
             __lhsbsel(&(parent_accum2_wp[wlen]), bi, bval);
            }
          }
        }
       /* combine the accumulator and the set bits */
       for (wi = 0; wi < wlen; wi++)
        {
         parent_wp[wi] |= combine_wp[wi];
         parent_setbits_wp[wi] |= setbits_wp[wi];
        }
      }
    }
   /* restore the parent net xprop index */
   np->n_xprop_ndx = xprop->parent_net_indices[i];
  }
}

/*
 * upon exit of the xprop code assign all lhs net values their accumulated
 * rhs value
 */
extern void __assign_xprop_accum_values(struct xprop_t *xprop)
{
 int32 i, wlen, bi, accum_aval, accum_bval;
 word32 *accum_wp, *setbits_wp, *accum_bwp;
 struct net_t *np;
 struct xstk_t *xsp;

 for (i = 0; i < xprop->ncount; i++)
  {
   np = xprop->lhsnets[i];
   if (np->n_xprop_accum_set == 0) continue;

#ifdef __CVC_DEBUG__
   /* DBG remove -- */
   if (np->srep != SR_VEC && np->srep != SR_SCAL && np->srep != SR_ARRAY)
    __misc_terr(__FILE__, __LINE__);
   /* ---- */
#endif
   
   np->n_xprop_accum_set = FALSE;
   push_xstk_(xsp, np->nwid);
   wlen = wlen_(np->nwid);
   /* if ID assign the entire width */
   if (xprop->lhs_id_only[i])
    {
     memcpy(xsp->ap, np->xprop_accum, 2*wlen*WRDBYTES);
     assign_xprop_value(xprop->astmts[i], xsp);
    }
   else
    {
     /* per bit needs to check if each bit is set */
     accum_wp = np->xprop_accum;
     /* copy in current net value */
     __ld_wire_val_wrds(xsp->ap, xsp->bp, np);

     accum_bwp = &(accum_wp[wlen]);
     setbits_wp = xprop->bits_set[i];

     /* for each bit set place into xsp value */
     for (bi = 0; bi < np->nwid; bi++)
      {
       if (rhsbsel_(setbits_wp, bi))
        {
         accum_aval = rhsbsel_(accum_wp, bi);
         __lhsbsel(xsp->ap, bi, accum_aval);
         accum_bval = rhsbsel_(accum_bwp, bi);
         __lhsbsel(xsp->bp, bi, accum_bval);
        }
      }

     /* convert the lhsx to a regular ID if anything but ID */
     assign_xprop_value(xprop->astmts[i], xsp);
    }

   __pop_xstk();
  }
}
     
/*
 * execute a list of xprop stmts accumulating rhs values as stmts are
 * executed.
 */
static struct st_t *exec_xprop_stmts(struct st_t *hd_stp, 
 struct xprop_t *xprop, int32 slevel)
{
 int32 level;
 struct xstk_t *xsp;
 struct expr_t *lhsx;
 struct delctrl_t *dctp;
 struct st_t *stp, *astp, *stp2;

 stp = hd_stp;
 for (;;)
  {
   /* notice one pass through loop executes exactly 1 statement */
   if (__stmt_covered != NULL) 
    {  
     __stmt_covered[stp->stmt_id_ndx] = TRUE;
    }
   __slin_cnt = stp->stlin_cnt;
   __sfnam_ind = stp->stfnam_ind;
   __num_execstmts++;
   /* DBG remove --
   if (__cur_thd == NULL || __cur_thd->th_idp != __idp)
    __misc_terr(__FILE__, __LINE__);
   --- */

   switch ((byte) stp->stmttyp) {
    /* SJM - 02/08/02 - should not count empties as exec stmts */
    case S_NULL: case S_STNONE: __num_execstmts--; break;
     /* FALLTHRU */
    case S_PROCA:
    case S_NBPROCA:
     lhsx = stp->st.spra.lhsx;
     xsp = __eval_assign_rhsexpr(stp->st.spra.rhsx, stp->st.spra.lhsx);
     __assign_lhsx_to_accum(lhsx, xsp->ap, xsp->bp, xprop);
     __pop_xstk();
     break;
    case S_DELCTRL:
     dctp = stp->st.sdc;
     astp = dctp->actionst;
     /* DBG remove --- */
     if (astp->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);
     /* ----- */
     lhsx = astp->st.spra.lhsx;
     xsp = __eval_assign_rhsexpr(astp->st.spra.rhsx, astp->st.spra.lhsx);
     __assign_lhsx_to_accum(lhsx, xsp->ap, xsp->bp, xprop);
     __pop_xstk();
     break;
    case S_IF:
     /* DBG remove --- */
     if (!stp->xprop_eligible) __misc_terr(__FILE__, __LINE__);
     /* ----- */
     stp = __exec_xprop_if_stmt(stp, slevel, NULL);
     goto nxt_stmt;
    case S_CASE:
     /* DBG remove --- */
     if (!stp->xprop_eligible) __misc_terr(__FILE__, __LINE__);
     /* ----- */
     __exec_xprop_case(stp, slevel, NULL);
     stp = stp->stnxt;
     goto nxt_stmt;
    case S_GOTO:
     /* now if not xprop stmt return */
     stp2 = stp->st.sgoto;
//AIV EXPROP - always @(c) d <= #1 e;  appears to have a empty goto
//AIV LOOKATME - is this right?????
     if (stp2 == NULL) return(NULL);
     level = stp2->xprop_level;
     if (level != -1 && level < slevel) return(stp2);
     stp = stp2;
     goto nxt_stmt;
    default: __case_terr(__FILE__, __LINE__);
   }
   stp = stp->stnxt;
nxt_stmt:
   if (stp == NULL) break;
  // if (stp->stmttyp != S_GOTO && !stp->xprop_mark) return(stp);

   level = stp->xprop_level;
   if (level != -1 && level > slevel) return(stp);
  }
 __stmt_suspend = FALSE;
 __cur_thd->thnxtstp = NULL;
 return(NULL);
}
     
/*
 * accumulate lhs expression values
 */
//AIV XPROP - can make this static when compiler is working
extern void __assign_lhsx_to_accum(struct expr_t *lhsx, word32 *ap, word32 *bp,
 struct xprop_t *xprop)
{
 struct expr_t *catndp, *catlhsx;
 int32 catxlen, bi1;
 struct xstk_t *catxsp;

 if (lhsx->optyp != LCB)
  {
   assign_net_to_accum(lhsx, ap, bp, xprop); 
  }
 else
  {
   /* do lhs concatenate assigns from left to right */
   /* just like __exec2_proc_concat_assign */
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    {
     catlhsx = catndp->lu.x;
     catxlen = catlhsx->szu.xclen;
     /* bi1 is low bit of rhs part select */
     /* length for catndp is distance from high bit of section to right end */ 
     bi1 = catndp->szu.xclen - catxlen;
  
     /* notice assignment always same width */
     push_xstk_(catxsp, catxlen);
     if (catxlen == 1)
      { catxsp->ap[0] = rhsbsel_(ap, bi1); catxsp->bp[0] = rhsbsel_(bp, bi1); }
     else
      {
       __rhspsel(catxsp->ap, ap, bi1, catxlen);
       __rhspsel(catxsp->bp, bp, bi1, catxlen);
      }

     assign_net_to_accum(catlhsx, catxsp->ap, catxsp->bp, xprop);
     __pop_xstk();
    }
  }
}

/*
 * accumulate rhs expression values for each lhs net
 */
static void assign_net_to_accum(struct expr_t *lhsx, word32 *ap, word32 *bp,
 struct xprop_t *xprop)
{
 struct net_t *np;
 int32 ri1, ri2, biti;
 struct expr_t *idndp, *ndx1;

 np = NULL;
 switch (lhsx->optyp) {
  case ID:
   np = lhsx->lu.sy->el.enp;
   set_xprop_accum_value(np, -1, -1, ap, bp, xprop, FALSE);
   break;
  case LSB:
   /* for now first determine if array index */
   idndp = lhsx->lu.x;
   ndx1 = lhsx->ru.x;
   np = idndp->lu.sy->el.enp;
   /* notice can never assign or force arrays */
   if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
   biti = __comp_ndx(np, ndx1);
   if (biti == -1)
    {
     set_xprop_accum_value(np, biti, biti, ap, bp, xprop, TRUE);
    }
   else set_xprop_accum_value(np, biti, biti, ap, bp, xprop, FALSE);

   break;
  case PARTSEL:
   idndp = lhsx->lu.x;
   np = idndp->lu.sy->el.enp;
   ri1 = (int32) __contab[lhsx->ru.x->lu.x->ru.xvi];
   ri2 = (int32) __contab[lhsx->ru.x->ru.x->ru.xvi];
   set_xprop_accum_value(np, ri1, ri2, ap, bp, xprop, FALSE);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}


/*
 * set the net rhs accumulation value
 */
static void set_xprop_accum_value(struct net_t *np, int32 bi1, int32 bi2,
 word32 *ap, word32 *bp, struct xprop_t *xprop, int32 force_x)
{
 word32 *accum_wp, *accum_bwp, *setbits_wp, *setblock_mask_wp;
 word32 bsela, bselb;
 int32 wlen, xblock, numbits, xprop_ndx; 
 int32 *accum_set_ip;
 struct xstk_t *xsp;


 xprop_ndx = np->n_xprop_ndx;
 /* DBG remove --- */
 if (xprop_ndx < 0) __misc_terr(__FILE__, __LINE__);
 if (xprop_ndx >= xprop->ncount) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 xblock = xprop->xblock;
 if (xblock == 0)
  {
   accum_wp = xprop->accum_block1[xprop_ndx];
   accum_set_ip = &(xprop->net_block1_set[xprop_ndx]);
  }
 else 
  {
   accum_wp = xprop->accum_block2[xprop_ndx];
   accum_set_ip = &(xprop->net_block2_set[xprop_ndx]);
  }
 
 /* DBG remove --- */
 if (accum_wp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ----- */


 wlen = wlen_(np->nwid);
 switch ((byte) np->srep) {
  case SR_ARRAY:
  case SR_VEC:
  case SR_SCAL:
   /* out of range for 'x */
   setbits_wp = xprop->bits_set[xprop_ndx];
   if (force_x)
    {
     /* all bits set marking */
     memset(setbits_wp, 0xff, wlen*WRDBYTES);

     /* set to x */
     set_regtox_(accum_wp, &(accum_wp[wlen]), np->nwid);
     break;
    }

   /* DBG remove --- */
   if (xprop->net_block1_set == NULL) __misc_terr(__FILE__, __LINE__);
   /* ----- */
   
   if (xblock == 0)
    {
     setblock_mask_wp = xprop->xbitmask_block1_set[xprop_ndx];
    }
   else setblock_mask_wp = xprop->xbitmask_block2_set[xprop_ndx];

   /* entire net */
   if (bi1 == -1)
    {
     /* all bits set marking */
     if (!xprop->lhs_id_only[xprop_ndx])
      {
       memset(setbits_wp, 0xff, wlen*WRDBYTES);
       memset(setblock_mask_wp, 0xff, wlen*WRDBYTES);
      }

     /* if xblock is zero - nothing yet to combine */
     if (!(*accum_set_ip))
      {
       memcpy(accum_wp, ap, wlen*WRDBYTES);
       memcpy(&(accum_wp[wlen]), bp, wlen*WRDBYTES);
      }
     else
      {
       combine_xprop_accum(accum_wp, ap, bp, np->nwid);
      }
    }
   else if (bi1 == bi2)
    {
     /* bit select */
     accum_bwp = &(accum_wp[wlen]);

     /* have to mark this bit as set */
     __lhsbsel(setbits_wp, bi1, 1);
     /* set bit for block */
     __lhsbsel(setblock_mask_wp, bi1, 1);

     /* if xblock is zero - nothing yet to combine */
     if (!(*accum_set_ip))
      {
       /* init to x's so just add the bit */
       //AIV not sure about this making zero - should preserve value???
       memset(accum_wp, 0, 2*wlen*WRDBYTES);
       __lhsbsel(accum_wp, bi1, ap[0]);
       __lhsbsel(accum_bwp, bi1, bp[0]);
      }
     else
      {
       /* is 0-0 = 0, 1-1 = 1, else x */
       bsela = rhsbsel_(accum_wp, bi1);
       bselb = rhsbsel_(accum_bwp, bi1);
       if (bsela != ap[0] || bselb != bp[0])
        {
         bsela = 1;
         bselb = 1;
        }
       __lhsbsel(accum_wp, bi1, bsela);
       __lhsbsel(accum_bwp, bi1, bselb);
      }
    }
   else
    {
     /* part select */
     numbits = bi1 - bi2 + 1;
     accum_bwp = &(accum_wp[wlen]);
     /* set per block mask */
     __lhspsel(setblock_mask_wp, bi2, __xprop_max_net_1_wp, numbits);

     /* set the bits as set */
     __lhspsel(setbits_wp, bi2, __xprop_max_net_1_wp, numbits); 

     /* if xblock is zero - nothing yet to combine */
     if (!(*accum_set_ip))
      {
       /* init to x's so just add the bit */
       //AIV not sure about this making zero - should preserve value???
       memset(accum_wp, 0, 2*wlen*WRDBYTES);
       __lhspsel(accum_wp, bi2, ap, numbits); 
       __lhspsel(accum_bwp, bi2, bp, numbits); 
      }
     else
      {
       /* just make a copy and combine the entire value */
       push_xstk_(xsp, np->nwid);
       memcpy(xsp->ap, accum_wp, 2*wlen*WRDBYTES);
       __lhspsel(xsp->ap, bi2, ap, numbits);
       __lhspsel(xsp->bp, bi2, bp, numbits);
       combine_xprop_accum(accum_wp, xsp->ap, xsp->bp, np->nwid);
       __pop_xstk();
      }
    }
    

   /* set accum init flags */
   np->n_xprop_accum_set = TRUE;
   *accum_set_ip = TRUE;
   return;
  default: __case_terr(__FILE__, __LINE__);
 }
}
     
/*
 * combine the xprop accumulation value using the ?:
 * truth table is 0-0 = 0, 1-1 = 1, else x 
 */
static void combine_xprop_accum(word32 *accum_wp, word32 *ap, word32 *bp, 
 int32 nwid)
{
 int32 wi, wlen, ubits;
 word32 *accum_bwp;

 wlen = wlen_(nwid);
 accum_bwp = &(accum_wp[wlen]);

 for (wi = 0; wi < wlen; wi++)
  {
   /* truth table is 0-0 = 0, 1-1 = 1, else x */
   accum_bwp[wi] = accum_bwp[wi] | bp[wi] | (accum_wp[wi] ^ ap[wi]);
   accum_wp[wi] = accum_bwp[wi] | ap[wi];
  }
 ubits = ubits_(nwid);
 accum_wp[wlen - 1] &= __masktab[ubits];
 accum_bwp[wlen - 1] &= __masktab[ubits];
}


/*
 * assign the lhs net is rhs accumulated value
 */
static void assign_xprop_value(struct st_t *stp, struct xstk_t *xsp)
{
 struct expr_t *lhsx;
 struct st_t *astp;
 struct delctrl_t *dctp;

 /* now assign lhs expression */
 switch (stp->stmttyp) {
  case S_PROCA: 
   if (__st_tracing)
    {
     xprop_tr_proc_assign(stp, xsp);
    }
   lhsx = stp->st.spra.lhsx;
    __exec2_proc_assign(lhsx, xsp->ap, xsp->bp);
   break;
  case S_NBPROCA: 
   if (__st_tracing)
    {
     xprop_tr_nbproc_assign(stp, xsp);
    }
   __sched_nbproc_delay((struct delctrl_t *) NULL, xsp, stp);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   astp = dctp->actionst;

   /* DBG remove --- */
   if (astp->stmttyp != S_NBPROCA) __misc_terr(__FILE__, __LINE__);
   if (dctp->dctyp != DC_RHSDELAY) __misc_terr(__FILE__, __LINE__);
   /* ------ */
   /* for non blocking assign - must not exec assign - event processing */
   /* routine does that, must continue after actionst if can else nxt */
   if (dctp->actionst != NULL && dctp->actionst->stnxt != NULL)
     __cur_thd->thnxtstp = dctp->actionst->stnxt;
   else __cur_thd->thnxtstp = stp->stnxt;
    
   if (__st_tracing)
    {
     xprop_tr_nbproc_assign(astp, xsp);
    }
   __sched_nbproc_delay(dctp, xsp, astp);
   break;
  default: __case_terr(__FILE__, __LINE__); break;
 }
}

/*
 * XPROP FINAL COMBINED VALUE ASSIGN TRACING ROUTINES
 */
    
/*
 * xprop final combined assign trace assignment
 * notice this expects rhs value to be on top of stack (caller pops)
 *
 * ok to use rgab_tostr here since know __exprline can not be in use before
 * statement execution begins
 */
static void xprop_tr_proc_assign(struct st_t *stp, struct xstk_t *xsp)
{
 __cur_sofs = 0;
 __dmp_proc_assgn((FILE *) NULL, stp, (struct delctrl_t *) NULL, FALSE);
 __exprline[__cur_sofs] = 0; 
 __trunc_exprline(TRTRUNCLEN, FALSE);
 __tr_msg("XPROP comb trace: %-7d %s", __slin_cnt, __exprline);
 __tr_msg(" [%s]\n", __xregab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen,
  stp->st.spra.lhsx));
 __cur_sofs = 0;
}

/*
 * trace an non blocking assignment statement
 * notice this expects rhs value to be on top of stack (caller pops)
 *
 * ok to use rgab_tostr here since know __exprline can not be in use before
 * statement execution begins
 */
static void xprop_tr_nbproc_assign(struct st_t *stp, struct xstk_t *xsp)
{
 struct expr_t *xrhs;

 __cur_sofs = 0;
 __dmp_nbproc_assgn((FILE *) NULL, stp, (struct delctrl_t *) NULL);
 __exprline[__cur_sofs] = 0; 
 __trunc_exprline(TRTRUNCLEN, FALSE);
 xrhs = stp->st.spra.rhsx;
 __tr_msg("XPROP nba comb trace: %-7d %s", __slin_cnt, __exprline);
 __tr_msg(" [%s]\n", __xregab_tostr(__xs, xsp->ap, xsp->bp,
  xsp->xslen, xrhs));
 __cur_sofs = 0;
}

/*
 * setup the xprop tracing file header info for tracing xprop entry with
 * +xtace option
 */
extern void __setup_xprop_trace_file(int32 xprop_type)
{
 FILE *fp;
 char c;

 /* get the xprop type 1 or 2 */
 c = ' ';
 if (xprop_type == 1) c = ' ';
 else if (xprop_type == 2) c = '2';


 fp = __xprop_trace_fp;
 /* --- DBG remove ---  */
 if (fp == NULL) __misc_terr(__FILE__, __LINE__);
 /* -----  */
 
 fprintf(fp, "\n \
                     ************************************************\n \
                     **                                            **\n \
                     **  CVC - Verilog X-propagation %c Report      **\n \
                     **                                            **\n \
                     **  Generated :  %s     **\n \
                     ************************************************", 
    c, __pvdate);

 fprintf(fp, "\n\n\n");
}


/*
 * setup xprop not eligible stmt file info
 */
extern void __setup_xprop_not_eligible_file(struct optlst_t *olp)
{
 FILE *fp;


//AIV XPROP - also need option to pass xprop file name - using default
 if ((fp = __tilde_fopen(DFLT_NOT_ELIGIBLE_XPROPFNAM, "w")) == NULL)
  {
   __gfwarn(641, olp->optfnam_ind, olp->optlin_cnt,
    "cannot open xprop trace file %s", DFLT_NOT_ELIGIBLE_XPROPFNAM);
   return;
  }
 fprintf(fp, "\n \
                     ************************************************\n \
                     **                                            **\n \
                     **  X-propagation Not Eligible Statements     **\n \
                     **                                            **\n \
                     **  Generated :  %s     **\n \
                     ************************************************", 
    __pvdate);

 fprintf(fp, "\n\n\n");
 __xprop_not_eligible_fp = fp;
}
     
/*
 * emit a reason why a stmt is cannot be included in xprop
 */
static void emit_xprop_not_eligible(struct st_t *stp, struct st_t *ne_stp, 
 struct st_t *ostp, struct net_t *np, int32 reason)
{
 char s1[RECLEN], s2[RECLEN];
 FILE *fp;
     

 /* if not on just return */
 if (!__xprop_not_eligible) return;

 /* can only be an if/case */
 fp = __xprop_not_eligible_fp;
 if (stp->stmttyp == S_IF) strcpy(s1, "if");
 else if (stp->stmttyp == S_CASE) strcpy(s1, "case");
 else __misc_terr(__FILE__, __LINE__);

 __cur_sofs = 0; 
 __pv_stlevel = 2;
 __force_dmp_fp = fp;
 fprintf(fp, "  ########## %s at [%s:%d] not included ############\n\n", s1,
     __in_fils[stp->stfnam_ind], stp->stlin_cnt);
 switch (reason) {
  /* illegal stmt */
  case NOT_ELIGIBLE_ILLEGAL_STMT:
   fprintf(fp, "  Illegal statement type (only if/case/assign allowed):\n\n");
   __to_sttyp(s2, ne_stp->stmttyp);
   fprintf(fp, "  Statement type : %s at [%s:%d]\n", s2, 
     __in_fils[ne_stp->stfnam_ind], ne_stp->stlin_cnt);
   __dmp_stmt(fp, ne_stp, NL);
   break;
  /* illegal net used on lhs and rhs */
  case NOT_ELIGIBLE_LHS_RHS_PROCA:
   /* --- DBG remove ---  */
   if (np == NULL) __misc_terr(__FILE__, __LINE__);
   /* -----  */
   fprintf(fp, "  Net (%s) is used on both lhs/rhs with a procedural assign:\n\n", 
     np->nsym->synam);
   __dmp_stmt(fp, stp, NL);
   break;
  /* select is a real */
  case NOT_ELIGIBLE_REAL:
   fprintf(fp, "  Select expression is a real value :\n\n");
   __dmp_stmt(fp, stp, NL);
   break;
  /* select is a 2-state */
  case NOT_ELIGIBLE_NO_XZ_SELECT:
   fprintf(fp, "  Select expression is a 2-state value (no x/z):\n\n");
   __dmp_stmt(fp, stp, NL);
   break;
  /* lhs is an array */
  case NOT_ELIGIBLE_LHS_ARRAY:
   fprintf(fp, "  Arrays (%s) are not yet supported for X-prop:\n\n", 
     np->nsym->synam);
   __dmp_stmt(fp, stp, NL);
   break;
  /* lhs for each net assigns don't match <=/= */
  case NOT_ELIGIBLE_ASSIGNS_DONT_MATCH:
   fprintf(fp, "  Assignment types are not the same - this is probably a bug in the RTL:\n\n"); 
   fprintf(fp, "  ** First statment assign type :\n"); 
   __dmp_stmt(fp, ostp, NL);
   fprintf(fp, "\n  ** Does not macth second statment assign type :"); 
   __dmp_stmt(fp, ne_stp, NL);
   break;
  /* lhs is XMR */
  case NOT_ELIGIBLE_LHS_XMR:
   fprintf(fp, "  Hierarchical references are not allowed on the left-hand-side:\n\n"); 
   __dmp_stmt(fp, stp, NL);
   break;
  /* nb delay is not constant */
  case NOT_ELIGIBLE_NB_NOT_CONST:
   fprintf(fp, "  Non-blocking assign contains a non-constant delay:\n\n"); 
   __dmp_stmt(fp, ne_stp, NL);
   break;
  /* nb delay is not the same delay value */
  case NOT_ELIGIBLE_NB_NOT_SAME:
   fprintf(fp, "  Non-blocking delay values are different - this is probably a bug in the RTL:\n\n"); 
   fprintf(fp, "  ** First statment <= assign :\n"); 
   __dmp_stmt(fp, ostp, NL);
   fprintf(fp, "\n  ** Does not macth second delay value :"); 
   __dmp_stmt(fp, ne_stp, NL);
   break;
  /* lhs is variable index [+:] */
  case NOT_ELIGIBLE_LHS_VARNDX:
   fprintf(fp, "  Statement uses lhs variable index:\n\n"); 
   __dmp_stmt(fp, ne_stp, NL);
   break;
  case NOT_ELIGIBLE_NET_FORCED:
   fprintf(fp, "  Net (%s) is forced in design - cannot use xprop:",
      np->nsym->synam); 
   break;
  case NOT_ELIGIBLE_LHS_COND:
   /* --- DBG remove ---  */
   if (np == NULL) __misc_terr(__FILE__, __LINE__);
   /* -----  */
   fprintf(fp, "  Net (%s) is used on both rhs and in conditional with a procedural assign:\n\n", 
     np->nsym->synam);
   __dmp_stmt(fp, stp, NL);
   break;
  case NOT_ELIGIBLE_CASE_EXPR:
   fprintf(fp, "  Case statement has illegal non-contant expression in case item list (only constants allowed for X-propagation):\n\n");
   __to_sttyp(s2, stp->stmttyp);
   fprintf(fp, "  Statement type : %s at [%s:%d]\n", s2, 
     __in_fils[stp->stfnam_ind], stp->stlin_cnt);
   __dmp_stmt(fp, stp, NL);
   break;
  case NOT_ELIGIBLE_CASE_DUP:
   __msgnumexpr_tostr(s1, __dup_xp, 0);
   fprintf(fp, "  Case statement has duplicate case items (value %s) - this is probably a bug\n\n", s1);
   __to_sttyp(s2, stp->stmttyp);
   fprintf(fp, "  Statement type : %s at [%s:%d]\n", s2, 
     __in_fils[stp->stfnam_ind], stp->stlin_cnt);
   __dmp_stmt(fp, stp, NL);
   break;
  case NOT_ELIGIBLE_IF_EXPR:
   fprintf(fp, "  If statement conditional contains ===/!== :\n\n");
   __to_sttyp(s2, stp->stmttyp);
   fprintf(fp, "  Statement type : %s at [%s:%d]\n", s2, 
     __in_fils[stp->stfnam_ind], stp->stlin_cnt);
   __dmp_stmt(fp, stp, NL);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 __force_dmp_fp = NULL;
 fprintf(fp, "\n\n  ###########################################################\n\n");
}
#endif
