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

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

/* local prototypes */
static void build_xmr_dependency(void);
static struct st_t *mark_1stmt_unreachable(struct mod_t *, struct st_t *);
static int32 is_reg_amode(int32);

static void free_tmp(struct tn_t *);
static void free_dup_trees(void);
static void formal_tmp_node_free(void *);
static void free_tn_avl_node(struct avlnode_t *, void (*)(void *));
static void dmp_formal_tmp_table(struct mod_t *);

#ifdef __CVC_DEBUG__
static void dmp_bblk_insns(struct bblk_t *, struct flowg_t *);
static char *iloc_tostr(char *, struct insn_t *, struct flowg_t *);
#endif

extern void __prep_design_for_compile(void);
extern char *__bldchk_var_comm_ref(char *, struct net_t *, struct mod_t *,
 struct task_t *);
extern void __push_cc_stmt(struct st_t *);
extern void __pop_cc_stmt(void);
extern struct st_t *__find_stlst_end(struct st_t *);
extern struct st_t *__find_after_tsk_nxtstmt(struct st_t *);
extern char *__to_sttyp(char *, word32);
extern void __bld_mod_flowg_ndx(struct mod_t *);
extern void __dmp_mod_insns(struct mod_t *);
extern void __dmp_flowg_insns(struct flowg_t *, struct mod_t *);
extern void __dmp_bblk_backelst(struct bblk_t *, struct flowg_t *,
 struct mod_t *);
extern void __chk_bblk_bedges(struct bblk_t *, struct flowg_t *,
 struct mod_t *); 
extern int32 __is_jmp_insn(int32);
extern void __linkout_insn(struct insn_t *, int32);
extern void __mark_stlst_unreachable(struct mod_t *, struct st_t *);
extern void __free_1insn(struct insn_t *);
#ifdef __VALTRK__
extern void __free_flowg_fuds(struct flowg_t *);
extern void __free_1insn_fud(struct insn_t *);
extern void __free_1bblk_predoms(struct bblk_t *);
#endif

extern void __dmp_1mod_tmp_table(struct mod_t *);
extern void __replace_insn(struct insn_t *, struct insn_t *);
extern struct insn_info_t *__to_iinfo_rec(int32);
extern char *__tn_type_tostr(char *, int32);
extern char *__to_flowgnam(char *, struct flowg_t *);
extern char *__to_iclassnam(char *, int32);
extern struct avlnode_t **__linearize_avl_tree(struct avlhd_t *, int32 *);
extern void __free_flowg_bblks(struct flowg_t *);
extern void __free_1bblk(struct bblk_t *, struct flowg_t *, int32);

extern void __free_tn_avltree(struct avlhd_t *, void (*)(void *));
extern void __free_flowg_insns(struct flowg_t *);
extern char *__asm_insn_tostr(char *, struct insn_t *, int32, struct flowg_t *);
extern char *__gen_comm_lab_amods(char *, struct tn_t *);
extern char *__tn_tostr(char *, struct tn_t *, int32);
extern char *__tn_to_assgnloc(char *, struct tn_t *);
extern char *__bld_lineloc(char *, word32, int32);
extern char *__bld_var_comm_ref(char *, struct net_t *);
extern char *__bld_var_comm_nam(char *, struct mod_t *, struct task_t *, 
 struct net_t *);
extern struct mod_t *__find_mod_task_of_var(struct net_t *, struct task_t **);
extern struct insn_t *__insert_insn(struct insn_t *, int32, int32, int32, ...);
extern struct insn_t *__alloc_insn(int32);
extern void __init_amode(struct amode_t *);
extern void __set_amode(struct amode_t *, va_list);
extern void __insert_after_insn(struct insn_t *, struct insn_t *);
extern void __insert_before_insn(struct insn_t *, struct insn_t *);
extern void __copy_amode(struct amode_t *, struct amode_t *);
extern int32 __is_constant(int32);
extern int32 __is_constant_with_zero_bpart(int32);
extern int32 __is_constant_zero(int32);
extern char *__bld_amods(char *, struct insn_t *, int32, struct amode_t *, 
 int32, struct flowg_t *);
extern int32 __get_tn_vec_size(struct tn_t *);
extern int32 __wide_vval_is0(word32 *, int32);
extern size_t __calc_ebp_spill_offset(int32, size_t);
extern int32 __get_con_adradd_xvi(int32);
extern word32 __get_wrd_con_val(int32);
extern word32 __get_wrd_amode_con_val(struct amode_t *);
extern word32 __get_con_wrd_aval_nd0bval(int32);
extern void __tn_dup_node_free(void *);
extern void __addr_add_dup_node_free(void *);
extern void __np_iconn_dup_node_free(void *);
extern void __gate_conta_dup_node_free(void *);
extern void __dcei_dup_node_free(void *);
extern int32 __get_asl_insn_retsiz(struct insn_t *, int32 *);
extern int32 __get_tnwid(int32);

extern char *__my_malloc(size_t);
extern void __my_free(void *, size_t);

extern void __my_fprintf(FILE *, char *, ...);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);

extern const char *__regs[];

/*
 * ROUTINES TO SET DESIGN WIDE FIELD IN PREPARATION FOR COMPILING 
 */

/*
 * prepare for cvc compile/load - not much here yet
 *
 * SJM 07/30/08 - now moved the n.l. object id num assign and ndx table
 * building to v_prp since need flexibility to change interpreter algorithms
 */
extern void __prep_netlists_for_cvc(void)
{
 /* mark all nets that are targets of XMRS - this mod's net accessed from */
 /* a different module */
 build_xmr_dependency();
}

/*
 * routine to build the cross module reference targets for entire design 
 */
//AIV? FIXME - need data struct so do per module compilation
static void build_xmr_dependency(void)
{
 struct mod_t *mdp;
 struct gref_t *grp;
 struct net_t *np;
 int32 i;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* mark all nets used in a xmr */
   for (i = 0; i < mdp->mgrnum; i++)
    {
     grp = &(mdp->mgrtab[i]); 
     /* AIV 0 8/24/06 - if not a net continue */
     if (grp->targsyp->sytyp != SYM_N) continue;
     np = grp->targsyp->el.enp;
     np->has_xmr = TRUE;
    }
  }
}

/*
 * mark at statement list unreable 
 * sets stp->unreable list
 */
extern void __mark_stlst_unreachable(struct mod_t *mdp, struct st_t *hdstp)
{
 struct st_t *stp;
 
 for (stp = hdstp; stp != NULL;)
  {
   stp = mark_1stmt_unreachable(mdp, stp);
  }
}
   
/*
 * mark at statement unreable 
 * sets stp->unreable list
 * same as set_1stmt_ent_bit - except sets bit
 */
static struct st_t *mark_1stmt_unreachable(struct mod_t *mdp, struct st_t *stp)
{
 int32 fji;
 struct st_t *astp, *fjstp, *cont_stp, *end_stp, *nxtstp;
 struct csitem_t *csip, *dflt_csip;
 struct delctrl_t *dctp;
 struct tskcall_t *tkcp;
 struct expr_t *tkxp;
 struct task_t *tskp;
 
 cont_stp = NULL;
 stp->unreachable = TRUE;
 switch ((byte) stp->stmttyp) {
  case S_RHSDEPROCA:
   stp->unreachable = TRUE;
   break;
  case S_NBPROCA:
   stp->unreachable = TRUE;
   break;
  case S_IF:
   __mark_stlst_unreachable(mdp, stp->st.sif.thenst);
   if (stp->st.sif.elsest != NULL)
    {
     __mark_stlst_unreachable(mdp, stp->st.sif.elsest);
    }
   break;
  case S_CASE:
   dflt_csip = stp->st.scs.csitems;
   for (csip = dflt_csip->csinxt; csip != NULL; csip = csip->csinxt)
    {
     __mark_stlst_unreachable(mdp, csip->csist);
    } 
   if (dflt_csip->csist != NULL && dflt_csip->csist->stmttyp != S_NULL)
    {
     __mark_stlst_unreachable(mdp,dflt_csip->csist);
    }
#ifdef __XPROP__
   /* AIV 08/02/11 - now might have xprop list to process as well */
   if (stp->st.scs.xprop_lstp != NULL)
    {
     __mark_stlst_unreachable(mdp, stp->st.scs.xprop_lstp);
    }
#endif
   break; 
  case S_FOREVER:
   __mark_stlst_unreachable(mdp, stp->st.swh.lpst);
   break;
  case S_REPEAT: 
   __mark_stlst_unreachable(mdp, stp->st.srpt.repst);
   break;
  case S_WHILE:
  case S_DO_WHILE:
   __mark_stlst_unreachable(mdp, stp->st.swh.lpst);
   break;
  case S_FOR:
   __mark_stlst_unreachable(mdp, stp->st.sfor->forbody);
   break;
  case S_WAIT:
   __mark_stlst_unreachable(mdp, stp->st.swh.lpst);
   break;
  case S_DELCTRL:
   dctp = stp->st.sdc;
   if (dctp->dctyp == DC_DELAY || dctp->dctyp == DC_EVENT)
    {
     astp = dctp->actionst;
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
       cont_stp = astp;
      }
     /* if non blocking no entry bit to set but must cont at right stmt */
     else if (astp->stmttyp == S_NBPROCA)
      {
       mark_1stmt_unreachable(mdp, astp);
       cont_stp = astp->stnxt;
      }
     else __case_terr(__FILE__, __LINE__);
    }
   return(cont_stp);
  case S_NAMBLK:
   /* named block takes over thread and can be disable - but never */
   /* entered from scheduler */
   tskp = stp->st.snbtsk;
   if (__processing_func || (!__gening_tsk && !tskp->can_be_disabled)) 
    {
     if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);
     __mark_stlst_unreachable(mdp, tskp->tskst);
     if (stp->stnxt != NULL) __pop_cc_stmt();
     break;
    }
   __mark_stlst_unreachable(mdp, tskp->tskst);
   break;
  case S_UNBLK:
   if (stp->stnxt != NULL) __push_cc_stmt(stp->stnxt);
   __mark_stlst_unreachable(mdp, stp->st.sbsts);
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
   for (fji = 0;; fji++)
    {
     /* first stmt of fork-join prong always entered from scheduler */
     if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;

     /* if this is named blocked adjust in next routine */
     if (fjstp->stmttyp == S_UNBLK)
      {
       __mark_stlst_unreachable(mdp, fjstp->st.sbsts);
      }
     else 
      {
       __mark_stlst_unreachable(mdp, fjstp);
      }
    }
   /* AIV LOOKATME - is this needed - double mark won't hurt ??? */
   if (stp->stnxt != NULL)
    {
     stp->stnxt->unreachable = TRUE;
    }
   break;
  case S_TSKCALL:
  case S_FUNCCALL:
   tkcp = &(stp->st.stkc);
   tkxp = tkcp->tsksyx;
   if (tkxp->lu.sy->sytyp == SYM_STSK) break;
   tskp = tkxp->lu.sy->el.etskp;
   nxtstp = __find_after_tsk_nxtstmt(stp);
   /* AIV 05/16/06 - the nxtstp could already be entered here */
   if ((__gening_tsk || tskp->can_be_disabled) && nxtstp != NULL)
    {
     if (!stp->is_enter) 
      {
       nxtstp->unreachable = TRUE;
      }
    }
   /* AIV 10/08/06 - was incorrectly returning nxtstp - causing incorrect */
   /* recursion for ifs/task just need next stmt */
   break;
  case S_GOTO: 
   if (stp->dctrl_goto) return(stp->st.sgoto);
   break;
  case S_REPDCSETUP:
   /* AIV 04/16/07 - need to check enter point for non-blocking rep dce */
   nxtstp = stp->stnxt;
   astp = nxtstp->st.sdc->actionst;
   if (astp->stmttyp == S_NBPROCA)
    {
     nxtstp->unreachable = TRUE;
    }
   break;
  default: break;
 }
 return(stp->stnxt);
}

/*
 * ROUTINES FOR BUILDING REFERENCE NAMES 
 */

/*
 * get a nets containing symbol table - either task it is in or module
 */ 
extern struct sy_t *__get_nets_containing_sy(struct net_t *np,
 struct mod_t **ret_mdp)
{
 struct mod_t *mdp;
 struct task_t *tskp;
 
 mdp = __find_mod_task_of_var(np, &(tskp));
 *ret_mdp = mdp;
 if (tskp != NULL) return(tskp->tsksyp);
 return(mdp->msym);
}

/*
 * build a net common name (label) - global but in .bss section
 *
 * used for references and declaration in .bss section of comm_ file
 * where know ref in cur mod
 */
extern char *__bld_var_comm_ref(char *s, struct net_t *np)
{
 struct mod_t *mdp;
 struct task_t *tskp;

 mdp = __find_mod_task_of_var(np, &(tskp));
 /* DBG remove -- */
 if (mdp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 __bld_var_comm_nam(s, mdp, tskp, np);
 return(s);
}

/*
 * build a var comm .bss file reference name when know mod and net
 * 
 * versions for _comm file output
 */
extern char *__bldchk_var_comm_ref(char *s, struct net_t *np,
 struct mod_t *mdp, struct task_t *tskp)
{
 /* DBG remove --
 {
  struct mod_t *mdp2; 
  struct task_t *tskp2;

  mdp2 = __find_mod_task_of_var(np, &(tskp2));
  if (mdp2 == NULL) __misc_terr(__FILE__, __LINE__);
  if (mdp != mdp2) __misc_terr(__FILE__, __LINE__); 
  if (tskp != NULL)
   {
    if (tskp != tskp2) __misc_terr(__FILE__, __LINE__); 
   }
 --- */
 __bld_var_comm_nam(s, mdp, tskp, np);
 return(s);
}

/*
 * build the comm area unique net name
 */
extern char *__bld_var_comm_nam(char *s, struct mod_t *mdp,
 struct task_t *tskp, struct net_t *np)
{
 char s1[RECLEN];

 if (!__opt_emit_var_names)
  {
   /* AIV 01/15/07 - rare case parameter is lowered need to get index */
   /* from mprms - think this only happens for isparam bsels */
   if (np->n_isaparam)
    {
     sprintf(s, "PN_%d_%d", mdp->m_idnum, (int32) (np - mdp->mprms));
    }
   else if (tskp == NULL)
    {
     sprintf(s, "N_%d_%d", mdp->m_idnum, (int32) (np - mdp->mnets));
    }
   else
    {
     sprintf(s, "NT_%d_%d_%d", mdp->m_idnum, tskp->t_idnum,
      (int32) (np - mdp->mnets));
    }
   return(s);
  }

 /* case 2: for debugging try to omit the net name */
 if (np->nsym->synam[0] == '\\') sprintf(s1, "%d", (int32) (np - mdp->mnets));
 else strcpy(s1, np->nsym->synam);
 if (tskp == NULL) sprintf(s, "N_%d_%s", mdp->m_idnum, s1);
 else sprintf(s, "NT_%d_%d_%s", mdp->m_idnum, tskp->t_idnum, s1);
 return(s);
}

/*
 * find module and possible task that a variable is in
 *
 * if not in task will find in top level symbol table
 *
 * if in named block or task can be in current scope or above including
 * top level without any XMR prefix (only cross module refs are XMRs)
 */
extern struct mod_t *__find_mod_task_of_var(struct net_t *np,
 struct task_t **net_tskp)
{
 struct mod_t *mdp;
 struct symtab_t *sytp, *sytp2;

 sytp = np->syt_of_net; 

 /* SJM 05-11-10 - routines only for code gen, so should never see sym tabs */
 /* that correspond to gen blks - if gened, is moved to mod level */
 /* DBG REMOVE --- */ 
 if (sytp->sypofsyt == NULL || sytp->gblkofsyt != NULL)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (sytp->sypofsyt->sytyp == SYM_M)
  {
   *net_tskp = NULL; 
   mdp = sytp->sypofsyt->el.emdp; 
   return(mdp);
  }
 else
  {
   /* DBG remove -- */
   if (sytp->sypofsyt->sytyp != SYM_TSK && sytp->sypofsyt->sytyp != SYM_F
    && sytp->sypofsyt->sytyp != SYM_LB) __case_terr(__FILE__, __LINE__);
   /* --- */
   *net_tskp = sytp->sypofsyt->el.etskp; 
   for (sytp2 = sytp->sytpar; sytp2 != NULL; sytp2 = sytp2->sytpar)
    {
     /* DBG REMOVE --- */ 
     if (sytp2->sypofsyt == NULL || sytp2->gblkofsyt != NULL)
      __misc_terr(__FILE__, __LINE__);
     /* --- */
     if (sytp2->sypofsyt->sytyp == SYM_M)
      {
       mdp = sytp2->sypofsyt->el.emdp;
       return(mdp);
      }
    }
   __misc_terr(__FILE__, __LINE__);
  }
 return(NULL);
}

/*
 * ROUTINES TO ALLOC, FREE AND INSERT/REMOVE X86 INSNS
 */

/*
 * alloc a no opand and no result insn - caller must link in
 *
 * for now this is used for X86 insns sequences that replace v insns
 */
extern struct insn_t *__alloc_insn(int32 op)
{
 struct insn_t *ip;

 __num_asm_insn++;
 ip = (struct insn_t *) __my_malloc(sizeof(struct insn_t));
 ip->opcod = op;
 ip->is_store = FALSE;
 ip->jmptyp = CC_UNKN;
 ip->sgn_jmp = FALSE;
#ifdef __VALTRK__
 ip->trk_later_del = FALSE;
 ip->symb_res_val = TRK_UNKN;
#endif
 ip->is_coal_out = FALSE;
 ip->is_coal_out2 = FALSE;
 ip->is_dpi_enter = FALSE;
 ip->is_export_stack = FALSE;
#ifndef __CVC32__
 ip->is_large_ofs = FALSE;
#endif
 ip->callasl_argnum = 0;
 ip->extrau.ndxjp = NULL;
 ip->res_tni = -1;
 __init_amode(&(ip->isrc));
 __init_amode(&(ip->idst));

 /* SJM 02/20/07 - alloc/insert insns that preseved nums couldn't work */
 /* now use design wide numbering - for dbg can call oreder num routine */
 ip->ndx = ++__num_asm_insn;
 ip->inxt = NULL;
 ip->iprev = NULL;
#ifdef __CVC_DEBUG__
 ip->inmdp = __inst_mod;
 ip->ifru = __cur_ifrom_u; 
#endif

 ip->optu.fudp = NULL;
 return(ip);
}

/*
 * alloc and initialize a factored use-def insn def pointer record
 */
extern struct iusedef_t *__alloc_init_iusedef(void)
{
 struct iusedef_t *fudp;

 fudp = (struct iusedef_t *) __my_malloc(sizeof(struct iusedef_t));
 fudp->ip_trk_valp = NULL;
 fudp->trk_nbytes = -1;
 fudp->isrc_defip = NULL;
 fudp->idst_defip = NULL;
 fudp->savchain_ip = NULL;
 return(fudp);
}

/*
 * initialize an amode's variables 
 */
extern void __init_amode(struct amode_t *amp)
{
 amp->amode = AM_UNKN;
 amp->scale = 0; 
 amp->x86_regno = REG_NONE;
 amp->arr_base_nlo = NLO_NONE;
 amp->is_labnam = FALSE;
#ifndef __CVC32__
 /* large model only used for 64-bit */
 amp->is_large_label = FALSE;
#endif
 /* -1 allows detecting if not set */
 amp->am_tni = -1;
 amp->disp = 0;
 amp->apu.labnam = NULL;
}

/*
 * allocate a string for machine insn gen - separate for checking
 * SJM 06/25/05 - added for debugging 
 */
extern char *__xi_stralloc(char *s)
{
 int32 slen;
 char *cp;

 /* DBG remove -- */
 if (s == NULL || *s == '\0') __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 slen = strlen(s) + 1;
 cp = __my_malloc(slen);
 __memstr_use += slen;
 strcpy(cp, s);
 return(cp);
}

/*
 * gen an x86 machine insn for a flow graph and link minsn onto end of list
 *
 * SJM 10/28/06 - expected to be called after x86 reg assign because
 * sets amode x86 reg numbers for tn's less the high X86 reg number
 */
extern struct insn_t *__insert_insn(struct insn_t *oip, int32 after,
 int32 opcod, int32 src_amode, ...)
{
 int32 dst_amode;
 struct insn_t *ip;
 va_list va;

 /* DBG remove -- */
 if (__cur_bbp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* can allocate since internal error if call wrong */
 ip = __alloc_insn(opcod);  
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
   if (dst_amode == AM_NONE || dst_amode < 0) 
    {
     __misc_terr(__FILE__, __LINE__);
    }
   ip->idst.amode = dst_amode;
   if (dst_amode != AM_NONE) 
    {
     __set_amode(&(ip->idst), va);
#ifdef __CVC32__
     va = __advance_seta_va;
#endif
    }
  }
 if (is_reg_amode(ip->isrc.amode) && ip->isrc.am_tni < HIGH_MACH_REG)
  ip->isrc.x86_regno = ip->isrc.am_tni;
 if (is_reg_amode(ip->idst.amode) && ip->idst.am_tni < HIGH_MACH_REG)
  ip->idst.x86_regno = ip->idst.am_tni;

//SJM ==> insert while building flowg bblk optimization (elimination) proc 
 if (after) __insert_after_insn(ip, oip);
 else __insert_before_insn(ip, oip);
 va_end(va);
 return(ip);
}

/*
 * return T if amode is some reg type (not immediate or label type)
 */
static int32 is_reg_amode(int32 amod)
{
 if (amod == AM_REG || amod == AM_NDXREG || amod == AM_NDXREG_DISP)
  return(TRUE);
 return(FALSE);
}

/*
 * insert x86 vinsn before another x86 vinsn after linearized to one
 * list per flow graph X86 insn list built
 *
 * LOOKATME - think this can't change fg vi tail?
 */
extern void __insert_before_insn(struct insn_t *new_ip, struct insn_t *oip)
{
 /* DBG remove -- */
 if (__cur_bbp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* SJM 02/20/07 - just give insn number for debug - not ordered now */
 new_ip->ndx = ++__num_asm_insn;
#ifdef __CVC_DEBUG__
 new_ip->inmdp = oip->inmdp;
#endif

 if (oip == NULL && __cur_bbp->ihd == NULL)
  {
   /* block empty - add the one new insn */
   __cur_bbp->ihd = new_ip;
   new_ip->iprev = new_ip->inxt = NULL;
   return;
  }
 if (oip->iprev == NULL) 
  { 
   /* link in at front (but know not empty) */
   new_ip->inxt = __cur_bbp->ihd;
   new_ip->iprev = NULL; 
   __cur_bbp->ihd->iprev = new_ip;
   __cur_bbp->ihd = new_ip;
   return;
  }
 /* DBG remove -- */
 if (oip == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* insert inside */
 oip->iprev->inxt = new_ip; 
 new_ip->iprev = oip->iprev;
 new_ip->inxt = oip;
 oip->iprev = new_ip;
}

/*
 * insert instruction after another (nil for at front)
 */
/* SJM 08/21/06 - why is insert after insn called instead of insert insn? */
//SJM? - this should not be ext?
extern void __insert_after_insn(struct insn_t *new_ip, struct insn_t *oip)
{
 struct insn_t *tmp_ip;

 /* DBG remove -- */
 if (__cur_bbp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 tmp_ip = oip->inxt;
 oip->inxt = new_ip;
 new_ip->iprev = oip;
 new_ip->inxt = tmp_ip; 
 /* SJM 02/20/07 - just give insn number for debug - not ordered now */
 new_ip->ndx = ++__num_asm_insn;
#ifdef __CVC_DEBUG__
 new_ip->inmdp = oip->inmdp;
#endif

 /* if inside */
 if (tmp_ip != NULL) tmp_ip->iprev = new_ip;

 /* if old insn is the tail update __cur_bbp tail since the new is after */
 if (__cur_bbp->itail == oip) __cur_bbp->itail = new_ip;
}

/*
 * renumber all the insns in a flow graph 
 *
 * SJM 11/15/06 - expand copy can add up to 8 insns and 2 memref can add 4
 * more fixed increments narrow ranges too much because of the different
 * types of inserts
 */
extern void __renumber_fg_insns(struct flowg_t *fgp)
{
 int32 nxt_inum;
 struct bblk_t *bbp;
 struct insn_t *ip;

 nxt_inum = 100;
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     ip->ndx =  nxt_inum;
     nxt_inum += 100;
    }
  }
}

/*
 * insert a movl minsn from some amode (now the src) into a reg
 */
extern void __insert_srcdup_movl(struct insn_t *oip, int32 after,
 struct amode_t *srcp, int32 reg_ti)
{
 struct insn_t *ip;

 ip = __alloc_insn(I_MOVA);  
 __copy_amode(&(ip->isrc), srcp);
 ip->idst.amode = AM_REG;
 ip->idst.am_tni = reg_ti;
 if (after) __insert_after_insn(ip, oip);
 else __insert_before_insn(ip, oip);

}

/*
 * copy amode fields from one amode to another
 *
 * can copy body but must alloc new copy of label
 */
extern void __copy_amode(struct amode_t *dstp, struct amode_t *srcp)
{
//AIV LOOKATME - possible memory leak of srcp->labnam
//need to free here
 *dstp = *srcp;
 if (srcp->is_labnam) dstp->apu.labnam = __xi_stralloc(srcp->apu.labnam);
}

/*
 * ROUTINES TO DETERMINE IF TN IS SOME TYPE OF CONTAB OR CINT CONSTANT
 */

/*
 * return T if it is a constant
 *
 * 2 cases: cint not b part or a/b constant (even wide also true but non IS) 
 * SJM 09/23/06 - now separate routine for getting right type of value
 */
extern int32 __is_constant(int32 tni)
{
 struct tn_t *tnp;

 /* DBG remove -- */
 if (tni == -1 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tnp = &(__tntab[tni]);
 if (tnp->comlab_typ == COMLAB_CINT) return(TRUE);
 if (tnp->comlab_typ == COMLAB_CONADR)
  {
   if (tnp->conadr_is_is) return(FALSE);
   return(TRUE);
  }
 return(FALSE);
}

/*
 * return T if tn is a memory label
 *
 * SJM 08/24/06 - even for mem labels could still load into a reg
 */
extern int32 __is_mem_label(int32 tni)
{
 struct tn_t *tnp;

 /* DBG remove -- */
 if (tni == -1 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tnp = &(__tntab[tni]);
 if (tnp->comlab_typ != COMLAB_NONE) return(TRUE);
 return(FALSE);
}

/*
 * get a word con aval where require that bval is 0 (i.e. not x) 
 * for cases where adradd not used to decompose the conadr
 */
extern word32 __get_con_wrd_aval_nd0bval(int32 tni)
{
 struct tn_t *tnp;
 word32 aval;
 int32 xvi;

 /* DBG remove -- */
 if (tni == -1 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tnp = &(__tntab[tni]);
 /* DBG remove -- */
 if (tnp->tnwid > WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (tnp->comlab_typ == COMLAB_CINT)
  {
   aval = tnp->tncu.tn_cint; 
  }
 else if (tnp->comlab_typ == COMLAB_CONADR)
  {
   xvi = __get_con_adradd_xvi(tni);
   aval = __contab[xvi]; 
   if (__contab[xvi + 1] != 0) __misc_terr(__FILE__, __LINE__);
  }
 else { aval = -1; __case_terr(__FILE__, __LINE__); }
 return(aval);
}

/*
 * return TRUE if constant has 0 for bpart 
 */
extern int32 __is_constant_with_zero_bpart(int32 tni)
{
 word32 *wp;
 int32 xvi, wlen, i;
 struct tn_t *tnp;

 /* DBG remove -- */
 if (tni == -1 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* --- */

 tnp = &(__tntab[tni]);
 if (!__is_constant(tni)) return(FALSE);

 if (tnp->comlab_typ == COMLAB_CINT)
  {
   return(TRUE);
  }
 /* DBG remove -- */
 if (tnp->comlab_typ != COMLAB_CONADR) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 xvi = __get_con_adradd_xvi(tni);
 wlen = wlen_(tnp->tnwid);
 wp = &(__contab[xvi+wlen]); 
 for (i = 0; i < wlen; i++) 
  {
   if (wp[i] != 0) return(FALSE);
  }

 return(TRUE);
}

/*
 * return TRUE if constant is 0
 */
extern int32 __is_constant_zero(int32 tni)
{
 word32 *wp;
 int32 xvi, blen;
 struct tn_t *tnp;

 /* DBG remove -- */
 if (tni == -1 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* --- */

 tnp = &(__tntab[tni]);
 if (!__is_constant(tni)) return(FALSE);

 if (tnp->comlab_typ == COMLAB_CINT)
  {
   return(tnp->tncu.tn_cint == 0);
  }
 /* DBG remove -- */
 if (tnp->comlab_typ != COMLAB_CONADR) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 xvi = __get_con_adradd_xvi(tni);
 wp = &(__contab[xvi]); 
 blen = 2*tnp->tnwid;
 return(vval_is0_(wp, blen));
}

/*
 * get the a value from a word constant
 *
 * this may actually get a bval it just gets the one word - there may or
 * may not be a b value in contab higher since this can be the result
 * of an adr add
 */
extern word32 __get_wrd_con_val(int32 tni)
{
 struct tn_t *tnp;
 word32 cval;
 int32 xvi;

 /* DBG remove -- */
 if (tni == -1 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tnp = &(__tntab[tni]);
 /* DBG remove -- */
 /* AIV 07/03/07 - making this legal can get the low end of the wide value */
 /* shift part which is wide only needs the low word */
 /* if (tnp->tnwid > WBITS) __misc_terr(__FILE__, __LINE__); */
 /* --- */
 cval = 0;
 if (tnp->comlab_typ == COMLAB_CINT)
  {
   cval = tnp->tncu.tn_cint; 
  }
 else if (tnp->comlab_typ == COMLAB_CONADR)
  {
   xvi = __get_con_adradd_xvi(tni);
   cval = __contab[xvi]; 
  }
 else __case_terr(__FILE__, __LINE__);
 return(cval);
}

/*
 * get a value from a conadr constant at location offset disp in bytes
 */
extern word32 __get_wrd_amode_con_val(struct amode_t *amp)
{
 int32 tni, xvi;
 word32 cval;
 struct tn_t *tnp;

 cval = -1;
 tni = amp->am_tni;
 /* DBG remove -- */
 if (tni == -1 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tnp = &(__tntab[tni]);
 /* DBG remove -- */
//AIV64
 /* AIV 11/14/08 - making this legal can get the low end of the wide value */
 /* when loading cint into a registers for > 32 bit constants */
 //if (tnp->tnwid > WBITS) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (tnp->comlab_typ == COMLAB_CINT)
  {
   /* DBG remove -- */
   if (amp->disp > 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   cval = tnp->tncu.tn_cint; 
  }
 else if (tnp->comlab_typ == COMLAB_CONADR)
  {
   xvi = __get_con_adradd_xvi(tni);
   if (amp->disp <= 0) cval = __contab[xvi];
   else cval = __contab[xvi + amp->disp/WRDBYTES]; 
  }
 else __case_terr(__FILE__, __LINE__);
 return(cval);
}

/*
 * 
 * get the contab index for some conadr - get the right index for a child
 * of a used wide tn
 */
extern int32 __get_con_adradd_xvi(int32 tni)
{
 int32 ndx;
 struct tn_t *tnp;
 
 /* DBG remove -- */
 if (tni == -1 || tni > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tnp = &(__tntab[tni]);

 /* DBG remove -- */
 if (tnp->comlab_typ != COMLAB_CONADR) __misc_terr(__FILE__, __LINE__);
 if (tnp->conadr_is_is) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 if (tnp->child_tag_offset != 0)
  {
   /* SJM 10/11/06 - notice child tag offset is byte but word indexing here */
   /* DBG remove -- */
   if (tnp->tag_parent_tni == -1) __misc_terr(__FILE__, __LINE__);
   /* --- */
   ndx = tnp->tncu.el_ndx + tnp->child_tag_offset/WRDBYTES; 
  }
 else ndx = tnp->tncu.el_ndx;
 return(ndx);
}

/*
 * return number of words a vector (non a scalar if stren format) tmp uses
 * even for stren byte vectors must be at least word aligned
 */
extern int32 __get_tn_vec_size(struct tn_t *tnp)
{
 int32 wlen;

 if (tnp->srtyp == SR_SVEC)
  {
   if (tnp->tnwid <= WRDBYTES) wlen = 1;
   /* stren vector width rounded up to next word (4 byte?) boundary */ 
   else wlen = ((tnp->tnwid + WRDBYTES - 1)/WRDBYTES);
  }
 /* AIV 11/13/06 - sr_cint only needs one word */
 else if (tnp->srtyp == SR_CINT) 
  {
   wlen = 1;
  }
 else if (tnp->tnwid == 0)
  {
   /* SJM 12/12/06 - need to track nlo's - know always one bit */
   /* think no other comlab's possible here */
//AIV? - there is a minor bug - some of the asl routines change the NLO   
//       so either they must untrack or update tracked value?
   /* DBG remove -- */
//SJM??   if (tnp->comlab_typ != COMLAB_NLO) __misc_terr(__FILE__, __LINE__);
   /* --- */
   wlen = 1;
  }
 /* AIV 08/26/10 - 2-state does not need 2* */
 else if (tnp->srtyp == SR_BIT2S)
  {
   wlen = wlen_(tnp->tnwid);
  }
 else wlen = 2*wlen_(tnp->tnwid);
 return(wlen);
}

/*
 * return number of words a vector after tmps decomposed
 * TN_ADR - are always considered wlen = 1 here
 */
extern int32 __get_lowered_tmp_size(struct tn_t *tnp)
{
 int32 wlen;

 if (tnp->srtyp == SR_SVEC)
  {
   /* AIV 12/12/07 - was returning wrong width here for address */
   /* TN_ADR - always wlen 1 even if type is SR_SVEC */
   if (tnp->tn_typ == TN_ADR) return(1);
   else if (tnp->tnwid <= WRDBYTES) wlen = 1;
   else wlen = ((tnp->tnwid + WRDBYTES - 1)/WRDBYTES);
  }
 else if (!tnp->tn_used_wide) 
  {
   wlen = 1;
  }
 else wlen = 2*wlen_(tnp->tnwid);
 return(wlen);
}

/*
 * routine to get a parent tni - variant when byte offset not needed
 */
extern int32 __get2_par_tni(int32 tni)
{
 int32 par_tni;
 struct tn_t *tnp;

 /* DBG remove -- */
 if (tni == -1) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tnp = &(__tntab[tni]);
 if (tnp->tag_parent_tni != -1) par_tni = tnp->tag_parent_tni;
 else par_tni = tni;

 return(par_tni);
}

/*
 * FLOW GRAPH AND BBLK ALLOCATE ROUTINES
 */

/*
 * alloc and fill a basic block connecting edge
 */
extern struct bbedge_t *__alloc_bbedge(void)
{
 struct bbedge_t *bbep;

 bbep = (struct bbedge_t *) __my_malloc(sizeof(struct bbedge_t));
 bbep->eblkp = NULL;
 bbep->bbenxt = NULL;
 return(bbep);
}

/*
 * alloc and init a flow graph
 *
 * SJM 08/16/04 - the var tn index also stored in first flow graph of net
 */
extern struct flowg_t *__alloc_flowg(int32 ftyp)
{
 struct flowg_t *fgp;

 fgp = (struct flowg_t *) __my_malloc(sizeof(struct flowg_t));
 fgp->flowgtyp = ftyp;
 fgp->uses_idp = FALSE;
 fgp->do_not_load_idp = FALSE;
 fgp->has_overflow = FALSE;
 fgp->uses_ebx = FALSE;
 fgp->uses_ebp = FALSE;
#ifdef __CVC32__
 fgp->uses_edi = FALSE;
 fgp->uses_esi = FALSE;
#else
 fgp->uses_r12 = FALSE;
 fgp->uses_r13 = FALSE;
 fgp->uses_r14 = FALSE;
 fgp->uses_r15 = FALSE;
 fgp->has_real_ops = FALSE;
#endif
 fgp->has_nb_pnd0s = FALSE;
 fgp->is_nb = FALSE;
 fgp->is_nb_free = FALSE;
 fgp->is_nb_rhs_mem = FALSE;
 fgp->optim_scalar_port = FALSE;
 fgp->has_thread_ctrl = FALSE;
 fgp->fg_remove = FALSE;
 fgp->fg_seqno = ++__flowg_seq_no;
 fgp->max_call_args = 0;
 fgp->max_dpi_wrds = 0;
 fgp->fg_num_bblks = -1;
 fgp->ebp_wrd_area_siz = -1;
 fgp->flowgnxt = NULL;
 fgp->fg_bblks = NULL;
 fgp->fg_bblkend = NULL;
 fgp->enter_bblks = NULL; 
 fgp->fg_tn_ref_tree = NULL; 
 fgp->optim_port_np = NULL; 
#ifdef __VALTRK__
 fgp->predoms = NULL;
#endif
 fgp->fg_ihd = NULL;
 fgp->fg_itail = NULL;
 /* AIV 05/07/07 - need to check for flow graph overflow */
 /* DBG remove -- */
 if (fgp->fg_seqno == 0xffffffff) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 return(fgp);
}

/*
 * alloc and init a basic block
 */
extern struct bblk_t *__alloc_bblk(int32 is_xz)
{
 struct bblk_t *bbp;

 bbp = (struct bblk_t *) __my_malloc(sizeof(struct bblk_t));

 bbp->after_suspend = FALSE;
 bbp->afs_reachable = FALSE;
 bbp->mark_for_rm = FALSE;
 bbp->deflst_processed = FALSE;
 bbp->deflst_added = FALSE; 
 bbp->is_xz = is_xz;
 bbp->is_enter_loop = FALSE;
 bbp->in_list = FALSE;
 bbp->is_casejmp_item = FALSE;

 bbp->mark = -1;
 bbp->revpostordno = -1;
 bbp->bblk_seqno = ++__bblk_seq_no;
 bbp->ihd = bbp->itail = NULL;
 bbp->bbe_prev = NULL;
#ifdef __VALTRK__
 bbp->predom_frontiers = NULL;
 bbp->bblk_pdoms = NULL;
#endif

 bbp->ihd = NULL;
 bbp->itail = NULL;
 bbp->bbnxt = bbp->bbprev = NULL;

 /* link onto end of current flow graph bblk list */
 if (__cur_flowg->fg_bblks == NULL) __cur_flowg->fg_bblks = bbp;
 else
  {
   __cur_flowg->fg_bblkend->bbnxt = bbp;
   bbp->bbprev = __cur_flowg->fg_bblkend;
  }
 __cur_flowg->fg_bblkend = bbp;
 return(bbp);
}

/*
 * BALANCED AVL TREE ACCESS ROUTINES - ALMOST SAME AS SYMBOL TAB TREE CODE
 */

/*
 * search one avl tree (aka symbol tab or set ) and if found return ptr to node
 *
 * use avl_tfind routine if need to add if not found
 */
extern struct avlnode_t * __get_avlnode(void *valp, struct avlhd_t *tree_rec) 
{
 struct avlnode_t *cur;
 cmpsword cv;

 /* SJM 02/22/07 - if tn never referenced, tree will be nil not empty */
 if (tree_rec == NULL) return(NULL);
 if (tree_rec->avl_root == NULL) return(NULL);
 for (cur = tree_rec->avl_root;;)
  {
   if ((cv = tree_rec->avl_cmp(valp, cur)) == 0) return(cur);
   if ((cur = ((cv < 0) ? cur->lp : cur->rp)) == NULL) break;
  }
 return(NULL);
}

/*
 * version of get avlnode that dies with misc terr if not found
 */
extern struct avlnode_t * __get2_avlnode(void *valp, struct avlhd_t *tree_rec) 
{
 struct avlnode_t *cur;
 cmpsword cv;

 if (tree_rec->avl_root == NULL) return(NULL);
 for (cur = tree_rec->avl_root;;)
  {
   if ((cv = tree_rec->avl_cmp(valp, cur)) == 0) return(cur);
   if ((cur = ((cv < 0) ? cur->lp : cur->rp)) == NULL) break;
  }
 __misc_terr(__FILE__, __LINE__);
 return(NULL);
}

/*
 * MISC ROUTINES TO FREE CVC MEMORY
 */

/*
 * free all storage used during compile of current module 
 * free flow graphs, empty tmp name table, and free formal tmp table
 */
extern void __free_1mod_cvc_mem(struct mod_t *mdp)
{
 int32 fgi, i;
 struct flowg_t *fgp;
 struct nb_stmt_lst_t *nbalstp, *nbalstp2;
 struct bblklst_t *bblp, *bblp2;
 struct avlhd_t *tree_rec;
 struct gate_da_list_t *gdap, *gdap2;

 __bld_mod_flowg_ndx(mdp);
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   fgp = __flowgtab[fgi];

   /* free basic blocks in one flow graph - adds fg bblk list to free list */
   __free_flowg_bblks(fgp);

   /* since .s file generated, no longer needed */
   __free_flowg_insns(fgp);
 
   /* need to free flowg enter block list */
   for (bblp = fgp->enter_bblks; bblp != NULL; bblp = bblp2)
    {
     bblp2 = bblp->bl_nxt;
     __my_free(bblp, sizeof(struct bblklst_t));
    }

   /* AIV 06/16/09 - need to free this here - was leaking memory */
   __free_tn_avltree(fgp->fg_tn_ref_tree, __tn_dup_node_free);
   fgp->fg_tn_ref_tree = NULL;
  }
 /* free each flow graph record */
 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   fgp = __flowgtab[fgi];
   __my_free(fgp, sizeof(struct flowg_t));
  }
 
 /* mark work tab empty */
 __flowg_lasti = -1;
 __cur_flowg = NULL;

 for (i = 0; i < __tntab_nxti; i++)
  {
   free_tmp(&(__tntab[i]));
  }
 __tntab_nxti = 0; 
 __my_free(__tntab, __tntabsiz*sizeof(struct tn_t));
 __tntab = NULL;
 /* AIV 01/16/07 - free the non-blocking assign list */
 for (nbalstp = __nb_stmt_hd; nbalstp != NULL; nbalstp = nbalstp2)
  {
   nbalstp2 = nbalstp->stnxt;
   __my_free(nbalstp, sizeof(struct nb_stmt_lst_t));
  }
 __nb_stmt_hd = __nb_stmt_cur = NULL;
 
 /* free the duplicate comlab trees */
 free_dup_trees();
 /* free the formal tmp table trees */
 for (i = 0; i < LAST_INSN; i++)
  {
   if ((tree_rec = __formal_tmptab[i]) == NULL) continue;
   __free_tn_avltree(tree_rec, formal_tmp_node_free);
   __formal_tmptab[i] = NULL;
  }
 __my_free(__flowgtab, __flowgtabsiz*sizeof(struct flowg_t *));
 __my_free(__bblktab, __bblktabsiz*sizeof(struct bblk_t *));
 __my_free(__dum_fg_ent_bbp, sizeof(struct bblk_t));

 /* free back end gate assigns with delays structs */
 for (gdap = __hd_gdap; gdap != NULL; gdap = gdap2)
  {
   gdap2 = gdap->nxt;
   __my_free(gdap, sizeof(struct gate_da_list_t));
  }
 __hd_gdap = __tail_gdap =  NULL;

 /* AIV 06/16/09 - had memory leak here - this is malloc per mod */
 /* SJM 08-22-07 - can only free avltab used for linearizing any avl tree */
 /* after all solib linking finished */
 __my_free(__avltab, __avltabsiz*sizeof(struct avlnode_t *));

 __my_free(__ndxjmp_bbtab, __ndxjmp_bbtab_siz*sizeof(struct bblk_t *));
 __my_free(__jmpbase, __jmpbas_tabsiz*sizeof(int32));
}
 
/*
 * free a formal tmp table record
 */
static void formal_tmp_node_free(void *ftp)
{
 int32 slen;
 struct ftval_t *ftvp;

 ftvp = (struct ftval_t *) ftp;
 if (ftvp->am1.is_labnam)
  {
   slen = strlen(ftvp->am1.apu.labnam);
   __my_free(ftvp->am1.apu.labnam, slen + 1);
   ftvp->am1.apu.labnam = NULL;
  }
 if (ftvp->am2.is_labnam)
  {
   slen = strlen(ftvp->am2.apu.labnam);
   __my_free(ftvp->am2.apu.labnam, slen + 1);
   ftvp->am2.apu.labnam = NULL;
  }
 __my_free(ftvp, sizeof(struct ftval_t));
}

/*
 * free all duplicate tmp trees
 *
 */
static void free_dup_trees(void)
{
 /* AIV 01/22/07 - was never freeing dup trees */
 __free_tn_avltree(__cint_dup_tn_tree , __tn_dup_node_free);
 __cint_dup_tn_tree = NULL;
 __free_tn_avltree(__contab_dup_tn_tree, __tn_dup_node_free);
 __contab_dup_tn_tree = NULL;
 /* free adradd avl dup tree */
 __free_tn_avltree(__adradd_child_tree, __addr_add_dup_node_free);
 /* AIV 10/06/08 - if code is inlined don't need iconn fgs */
 if (!__inline_code)
  {
   __free_tn_avltree(__np_iconn_dup_tn_tree, __np_iconn_dup_node_free);
   __free_tn_avltree(__gate_conta_dup_tn_tree, __gate_conta_dup_node_free);
  }
}

/*
 * free a tmp 
 */
static void free_tmp(struct tn_t *tnp)
{
#ifdef __VALTRK__
 if (tnp->bb_def_tree != NULL)
  {
   __free_tn_avltree(tnp->bb_def_tree, NULL);
   tnp->bb_def_tree = NULL;
  }
#endif

 /* AIV 06/19/09 - this is now malloc to save space - must free here */
 if (tnp->tnsyrecp != NULL)
  {
   __my_free(tnp->tnsyrecp, sizeof(struct tn_syadr_t));
   tnp->tnsyrecp = NULL;
  }
}

/*
 * free all basic blocks in a flow graph
 * does not free insns since they are moved to flowg linear list
 */
extern void __free_flowg_bblks(struct flowg_t *fgp)
{
 struct bblk_t *rm_bbp, *rm_bbp2;   

 /* first free contents of every bblk in flow graph */
 for (rm_bbp = fgp->fg_bblks; rm_bbp != NULL;) 
  {
   rm_bbp2 = rm_bbp->bbnxt;
   /* free the bblk */
   __free_1bblk(rm_bbp, fgp, FALSE);
   rm_bbp = rm_bbp2;
  }
 fgp->fg_bblks = NULL;
}

/*
 * free one bblk 
 * 
 * 11/18/06 SJM - now can actually free the bblk after linking out of
 * the fg bblk list - but BEWARE - must rebuild the RPO numbers and index
 */
extern void __free_1bblk(struct bblk_t *rm_bbp, struct flowg_t *fgp, 
 int32 free_insns)
{
 struct bbedge_t *bbep, *bbep2;
 struct insn_t *ip, *ip2;

#ifdef __VALTRK__
 /* free the predominator and tn ref tracked in bblk data structures */ 
 __free_1bblk_predoms(rm_bbp);
#endif

 /* free back edge list if there is one */
 for (bbep = rm_bbp->bbe_prev; bbep != NULL;)
  {
   bbep2 = bbep->bbenxt;
   __my_free(bbep, sizeof(struct bbedge_t));
   bbep = bbep2;   
  }
 rm_bbp->bbe_prev = NULL;
 /* DBG remove -- */
 if (fgp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* link out of flowg bblk list */
//SJM? - problem - for now this won't after bpo numbering
 if (fgp->fg_bblks == rm_bbp)
  {
   fgp->fg_bblks = rm_bbp->bbnxt;
   if (fgp->fg_bblks != NULL) fgp->fg_bblks->bbprev = NULL;
  }
 /* AIV 12/08/06 - the last block of the flow graph */
 else if (fgp->fg_bblkend == rm_bbp)
  {
   /* DBG remove -- */
   if (rm_bbp->bbprev == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   fgp->fg_bblkend = rm_bbp->bbprev;
   rm_bbp->bbprev->bbnxt = NULL;
  }
 else
  {
   /* DBG remove -- */
   if (rm_bbp->bbprev == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   rm_bbp->bbprev->bbnxt = rm_bbp->bbnxt;
   if (rm_bbp->bbnxt != NULL) rm_bbp->bbnxt->bbprev = rm_bbp->bbprev;
  }
 /* cannot free for all blocks because nxt pointers are adjusted when */
 /* merging into one list for assembly generation */
 if (free_insns)
  {
   __cur_bbp = rm_bbp;
   for (ip = rm_bbp->ihd; ip != NULL;)
    { 
     ip2 = ip->inxt;
     __free_1insn(ip);
     ip = ip2;
    }
  }
 /* AIV 12/02/06 - was never actually freeing the block itself */
 __my_free(rm_bbp, sizeof(struct bblk_t));
}

/*
 * free a bblk avl tree - valp is ptr not record so easy
 */
extern void __free_bblk_avltree(struct avlhd_t *avlhdp)
{
 /* SJM 10/26/06 - for empty initial/always blocks no tn's to free */
 if (avlhdp == NULL) return;

 if (avlhdp->num_nodes > 0)
  {
   /* DBG remove -- */
   if (avlhdp->avl_root == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   free_tn_avl_node(avlhdp->avl_root, NULL);
  }
 __my_free(avlhdp, sizeof(struct avlhd_t));
}

/*
 * free a tni used in (read or set) tree for one xjmp master bblk 
 */
extern void __free_tn_avltree(struct avlhd_t *avlhdp, void (*avl_free)(void *))
{
 /* SJM 10/26/06 - for empty initial/always blocks no tn's to free */
 if (avlhdp == NULL) return;

 if (avlhdp->num_nodes > 0)
  {
   /* DBG remove -- */
   if (avlhdp->avl_root == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   free_tn_avl_node(avlhdp->avl_root, avl_free);
  }
 __my_free(avlhdp, sizeof(struct avlhd_t));
}

/*
 * free an avl tn usein tree
 */
static void free_tn_avl_node(struct avlnode_t *nodp, void (*avl_free)(void *))
{
 if (nodp->lp != NULL) free_tn_avl_node(nodp->lp, avl_free);
 if (nodp->rp != NULL) free_tn_avl_node(nodp->rp, avl_free);

 if (avl_free != NULL)
  {
   avl_free(nodp->valp);
  }
 __my_free(nodp, sizeof(struct avlnode_t));
}

/*
 * free list of machine insn in a flow graph
 *
 * notice could just link on insn free list if could reuse label malloc area
 *
 * notice usually insn moved from bblks to flow graph list but need
 * to free in both places
 */
extern void __free_flowg_insns(struct flowg_t *fgp)
{
 struct insn_t *ip, *ip2;

 /* for load modlib case, machine insn list will be empty */
 if (fgp->fg_ihd == NULL) return;
 for (ip = fgp->fg_ihd; ip != NULL;)
  { 
   ip2 = ip->inxt;
   __free_1insn(ip);
   ip = ip2;
  }
}

/*
 * free one insn - caller must link out if needed
 *
 * SJM 04/15/06 LOOKATME? - assuming only insn malloc storage for ndx jmps
 */
extern void __free_1insn(struct insn_t *ip)
{
 int32 tabsiz, slen;
 struct insn_info_t *iip;
 struct ndxjmp_t *ndxjp;
 struct defilst_t *dfilp, *dfilp2;

 iip = __to_iinfo_rec(ip->opcod);
 if (iip->iclass == ICLASS_NDXJMP)
  {
   ndxjp = ip->extrau.ndxjp;
   /* DBG remove -- */
   if (ndxjp == NULL) __misc_terr(__FILE__, __LINE__);
   /* AIV 01/24/07 - was freeing labnam which was always null */
   if (ip->idst.is_labnam) __misc_terr(__FILE__, __LINE__);
   /* --- */
   tabsiz = ndxjp->jtabstart + ndxjp->jtabsiz;
   /* AIV 08/29/06 - need to free ndx jump struct */
   __my_free(ndxjp->bbtab, tabsiz*sizeof(struct bblk_t *));
   __my_free(ndxjp, sizeof(struct ndxjmp_t));
   ip->extrau.ndxjp = NULL;
  }
 else if (iip->iclass == ICLASS_DEFLST)
  {
   /* SJM 01/01/07 - LOOKATME - think should be already freed by here */
   for (dfilp = ip->extrau.defilst; dfilp != NULL;)
    {
     dfilp2 = dfilp->defilstnxt;
     __my_free(dfilp, sizeof(struct defilst_t));
     dfilp = dfilp2;
    }
   ip->extrau.defilst = NULL;
  }
 else
  {
   if (ip->isrc.is_labnam)
    {
     slen = strlen(ip->isrc.apu.labnam);
     __my_free(ip->isrc.apu.labnam, slen + 1);
     ip->isrc.apu.labnam = NULL;
    }
   if (ip->idst.is_labnam)
    {
     slen = strlen(ip->idst.apu.labnam);
     __my_free(ip->idst.apu.labnam, slen + 1);
     ip->idst.apu.labnam = NULL;
    }
   /* SJM 10/16/06 - need to free the arg tn number array for medium calls */
   if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
    {
     __my_free(ip->extrau.asl_ausedefs,
      ip->callasl_argnum*sizeof(struct asl_def_t));
     ip->extrau.asl_ausedefs = NULL;
    }
  }
#ifdef __VALTRK__
 __free_1insn_fud(ip);
#endif

 __my_free(ip, sizeof(struct insn_t));
}

#ifdef __VALTRK__
/*
 * when done with optimization, free all the dominator, set and region
 * data structures for one flow graph
 *
 * since FUD insns ignored, normal bblk insn free will remove
 * user of any linearized avl tree array, must free it when done using it
 * 
 * SJM 01/01/07 - could remove the deflst (phi) insns here too?
 */
extern void __free_flowg_doms_and_sets(struct flowg_t *fgp)
{
 int32 avli, num_tnrefs;
 struct bblk_t *bbp;
 struct tn_dup_t *tndup;
 struct avlnode_t **tn_ref_avltab;

 /* free the predom tree (stored as array - child's index is parent */
 __my_free(fgp->predoms, fgp->fg_num_bblks*sizeof(int32));
 fgp->predoms = NULL;

 /* SJM 12/27/06 - LOOKATME - could link onto a free list and reuse */
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   /* free predom frontiers and inverted list of bblk bbp predominates */
   __free_1bblk_predoms(bbp);
  }

 /* free the tn def bblks */
 /* only need to free tn define tree of bblk for tn's used in flowg */ 
 tn_ref_avltab = __linearize_avl_tree(fgp->fg_tn_ref_tree, &(num_tnrefs));
 for (avli = 0; avli < num_tnrefs; avli++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[avli]->valp;

   __free_bblk_avltree(__tntab[tndup->tni].bb_def_tree);
   __tntab[tndup->tni].bb_def_tree = NULL;

   __free_bblk_avltree(__tntab[tndup->tni].bb_use_tree);
   __tntab[tndup->tni].bb_use_tree = NULL;
  }
 /* AIV 06/16/09 - LOOKATME - depending on when this is called */
 /* this may already be freed in __free_1mod - had memory leak */
 __my_free(tn_ref_avltab, num_tnrefs*sizeof(struct avlnode_t *)); 
 __free_tn_avltree(fgp->fg_tn_ref_tree, __tn_dup_node_free);
 fgp->fg_tn_ref_tree = NULL;

 __free_flowg_fuds(fgp);

 __cur_bbp = NULL;
}

/*
 * free the factored use-def records for every insn in a flow graph
 *
 * also free any remaining deflst insns since done with them
 */
extern void __free_flowg_fuds(struct flowg_t *fgp)
{
 struct bblk_t *bbp;
 struct insn_t *ip, *ip2;

 /* SJM 01/01/07 - LOOKATME - maybe should free this when free insn */
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   /* SJM 01/17/07 - need cur bbp to be set to call link out insn */
   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt; 
     __free_1insn_fud(ip);

     /* since flow graph structure changed, if need FUDs must rebuild */
     if (ip->opcod == I_DEFLST) __linkout_insn(ip, TRUE);
    }
  }
}

/*
 * free the factored def use chain in a insn if present
 */
extern void __free_1insn_fud(struct insn_t *ip)
{
 if (ip->optu.fudp == NULL) return; 

 if (ip->optu.fudp->ip_trk_valp != NULL) 
  { 
   __my_free(ip->optu.fudp->ip_trk_valp, ip->optu.fudp->trk_nbytes);
  }
 __my_free(ip->optu.fudp, sizeof(struct iusedef_t));
 ip->optu.fudp = NULL;
}

/*
 * free predom and value tracking data structures for one bblk
 */
extern void __free_1bblk_predoms(struct bblk_t *bbp)
{
 struct bblklst_t *bblp, *bblp2;

 for (bblp = bbp->predom_frontiers; bblp != NULL;)
  {
   bblp2 = bblp->bl_nxt;
   __my_free(bblp, sizeof(struct bblklst_t));
   bblp = bblp2;
  }
 bbp->predom_frontiers = NULL;
 /* free the list of bblk's this node predominates */ 
 for (bblp = bbp->bblk_pdoms; bblp != NULL;)
  {
   bblp2 = bblp->bl_nxt;
   __my_free(bblp, sizeof(struct bblklst_t));
   bblp = bblp2;
  } 
 bbp->bblk_pdoms = NULL;
}

#endif //__VALTRK__

/*
 * ROUTINES TO DUMP DESIGN WIDE TMP TABLE
 */

/*
 * dump tmp table (both tmp name and formal tmp table)
 */
extern void __dmp_mod_tmp_table(struct mod_t *mdp)
{
 int32 tni;
 struct tn_t *tnp;
 char s1[RECLEN];

 __my_fprintf(stdout, "PRTMP TABLE\n"); 
 for (tni = HIGH_X86_REG + 1; tni < __tntab_nxti; tni++)
  {
   tnp = &(__tntab[tni]);
   __tn_tostr(s1, tnp, FALSE);
   __my_fprintf(stdout, "r%0d    %s\n", tni, s1);
  }
 dmp_formal_tmp_table(mdp);
}

/*
 * ROUTINES TO DUMP FORMAL TMP TABLE
 */

/*
 * dump the formal tmp table to a file 
 */
static void dmp_formal_tmp_table(struct mod_t *mdp)
{
 int32 i, tni, avli, nxti, siz_avltab, *i_map; 
 struct avlnode_t *nodp, **ndx_avltab;
 struct ftval_t *ftvp;
 struct insn_info_t *iip;
 struct avlnode_t **formal_avltab;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN];

 if (__tntab_nxti == 0)
  {
   __my_fprintf(stdout, "\nFORMAL TMP TABLE - EMPTY\n"); 
   return;
  }

 __my_fprintf(stdout, "\nFORMAL TMP TABLE\n"); 
 nxti = __tntab_nxti;
 ndx_avltab = (struct avlnode_t **)
  __my_malloc(sizeof(struct avlnode_t *)*nxti);
 i_map = (int32 *) __my_malloc(sizeof(int32)*nxti);
 memset(ndx_avltab, 0, sizeof(struct avlnode_t *)*nxti);
 memset(i_map, 0, sizeof(int32)*nxti);

 for (i = 0; i < LAST_INSN; i++)
  {
   if (__formal_tmptab[i] == NULL) continue;
 
   /* SJM 12/26/06 - look at me - inefficient but only for dumping */
   formal_avltab = __linearize_avl_tree(__formal_tmptab[i], &(siz_avltab));
   for (avli = 0; avli < siz_avltab; avli++)
    {
     nodp = formal_avltab[avli];
     ftvp = (struct ftval_t *) nodp->valp;
     /* DBG remove -- */
     if (ftvp->res_tni == -1) __misc_terr(__FILE__, __LINE__);
     /* -- */
     ndx_avltab[ftvp->res_tni] = nodp;
     i_map[ftvp->res_tni] = i;
    }
   /* SJM 12/26/06 - caller must free avltab when done */
   __my_free(formal_avltab, siz_avltab*sizeof(struct avlnode_t *));
  }

 for (tni = 0; tni < __tntab_nxti; tni++)
  {
   if ((nodp = ndx_avltab[tni]) == NULL) continue;
   if (i_map[tni] == 0) continue;

   ftvp = (struct ftval_t *) nodp->valp;
   if (ftvp->res_tni != tni) __misc_terr(__FILE__, __LINE__);

   __tn_tostr(s1, &(__tntab[tni]), FALSE);
   iip = __to_iinfo_rec(i_map[tni]);
   if (iip == NULL) __misc_terr(__FILE__, __LINE__);
   strcpy(s2, iip->inam);
   if (ftvp->am1.amode == AM_NONE) strcpy(s3, "<none>");
   else __bld_amods(s3, NULL, i_map[tni], &(ftvp->am1), TRUE, NULL);
   if (ftvp->am2.amode == AM_NONE) strcpy(s4, "<none>");
   else __bld_amods(s4, NULL, i_map[tni], &(ftvp->am2), TRUE, NULL);
   __my_fprintf(stdout, "r%d %s: %s am1=%s am2=%s\n",
    tni, s1, s2, s3, s4);
  }
 __my_free(ndx_avltab, sizeof(struct avlnode_t *)*nxti);
 __my_free(i_map, sizeof(int32)*nxti);
 __my_fprintf(stdout, "\n");
}

/*
 * ROUTINES TO DUMP (PRINT) INSNS TO A FILE - NOT GAS FORMAT
 */

/*
 * dump flow graph insns for one mod to a file for debugging
 *
 * if res tni set uses 3 op format else x86 2 op format
 * if not already done, caller must call routine to build the mod's flowg ndx
 */
extern void __dmp_mod_insns(struct mod_t *mdp)
{
 int32 fgi;

 for (fgi = 0; fgi <= __flowg_lasti; fgi++)
  {
   __dmp_flowg_insns(__flowgtab[fgi], mdp);
  }
}

/*
 * print all insns for every basic block in one flow graph in x86 2 op form
 *
 * uses 3 operand format if res tni set else x86 2 operand format
 */
extern void __dmp_flowg_insns(struct flowg_t *fgp, struct mod_t *mdp)
{
 char s1[RECLEN];
#ifdef __CVC_DEBUG__
 struct bblk_t *bbp;
#endif

 if (fgp->fg_bblks == NULL)
  {
   __my_fprintf(stdout, "\n# EMPTY FLOWG (%s)\n", __to_flowgnam(s1, fgp)); 
   return;
  } 

 if (mdp != NULL) 
  {
   __my_fprintf(stdout, "\n# MODULE %s (%s)\n", mdp->msym->synam, 
    __in_fils[mdp->msym->syfnam_ind]); 
  }
 else if (__inst_mod != NULL)
  {
   __my_fprintf(stdout, "\n# MODULE %s (%s)\n", __inst_mod->msym->synam,
   __in_fils[__inst_mod->msym->syfnam_ind]); 
  }
 __my_fprintf(stdout, "# FLOWG (%s)\n", __to_flowgnam(s1, fgp)); 
 
#ifdef __CVC_DEBUG__
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   /* DBG remove --
   __dmp_bblk_backelst(bbp, fgp, mdp);
   -- */
   dmp_bblk_insns(bbp, fgp);
  }
#else
 /* AIV 06/17/09 - should never get here for non-debug version */
  __misc_terr(__FILE__, __LINE__);
#endif
 /* ??? TOO MANY BLANK LINES?  __my_fprintf(stdout, "\n\n"); */ 
}

#ifdef __CVC_DEBUG__
/*
 * dump one basic block's insns to file in human readable (not asm) form
 */
static void dmp_bblk_insns(struct bblk_t *bbp, struct flowg_t *fgp)
{
 struct insn_t *ip;
 char s1[RECLEN], sloc[RECLEN], last_sloc[RECLEN];
 
 /* don't print a \n for the first block */
 if (bbp->bblk_seqno > 1) __my_fprintf(stdout, "\n");

 strcpy(last_sloc, "");
 for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
  {
   if (__asm_emit_loc == 3) 
    {
     iloc_tostr(sloc, ip, fgp);
     if (strcmp(last_sloc, sloc) != 0)
      {
       __my_fprintf(stdout, "# %s\n", sloc);
       strcpy(last_sloc, sloc);
      }
    }
   __my_fprintf(stdout, "%d %s\n", ip->ndx, __asm_insn_tostr(s1, ip, TRUE, 
    fgp));
  }
}

/*
 * build the insns src (either stmt loc or net) in a string
 */
static char *iloc_tostr(char *s, struct insn_t *ip, struct flowg_t *fgp)
{
 struct st_t *stp;
 struct net_t *np;
 struct conta_t *cap;
 char s1[RECLEN];

 switch (fgp->flowgtyp) { 
  case FLOWG_PROC: case FLOWG_TASK: case FLOWG_FUNC:
   stp = ip->ifru.from_stp;
   if (fgp->flowgtyp == FLOWG_PROC) strcpy(s1, "STMT");
   else if (fgp->flowgtyp == FLOWG_TASK) strcpy(s1, "TASK");
   else if (fgp->flowgtyp == FLOWG_FUNC) strcpy(s1, "FUNC");
   else __case_terr(__FILE__, __LINE__);

   if (stp == NULL) strcpy(s, "STMT [NONE]:");
   else
    {
     sprintf(s, "%s at %s (%s):", s1, __bld_lineloc(__xs, stp->stfnam_ind,
      stp->stlin_cnt), __to_sttyp(__xs2, stp->stmttyp));
    }
   break;
  case FLOWG_DCE:
   np = ip->ifru.from_np;
   sprintf(s, "DCE %s at %s:", np->nsym->synam,
    __bld_lineloc(__xs, np->nsym->syfnam_ind, np->nsym->sylin_cnt));
   break;
  case FLOWG_NPP:
   np = ip->ifru.from_np;
   sprintf(s, "NPP %s at %s:", np->nsym->synam,
    __bld_lineloc(__xs, np->nsym->syfnam_ind, np->nsym->sylin_cnt));
   break;
  case FLOWG_MULTFI:
   np = ip->ifru.from_np;
   sprintf(s, "MULTFI %s at %s:", np->nsym->synam,
    __bld_lineloc(__xs, np->nsym->syfnam_ind, np->nsym->sylin_cnt));
   break;
  case FLOWG_CONTA:
   cap = ip->ifru.from_cap;
   sprintf(s, "CONTA: %d", cap->enter_cndx);
   break;
  case FLOWG_ICONN:
   //AIV LOOKATME - could build expr info here
   sprintf(s, "ICONN %d\n", ip->ifru.from_iconn);
   break;
  case FLOWG_GATEDA:
   sprintf(s, "GATEDA %d\n", ip->ifru.from_gateda);
   break;
  case FLOWG_GATECA:
   //AIV LOOKATME - could build expr info here
   sprintf(s, "GATECA %d\n", ip->ifru.from_gateca);
   break;
  case FLOWG_NCHG:
   sprintf(s, "NCHG %d\n", ip->ifru.from_gateca);
   break;
  case FLOWG_PROCESS_NCHG:
   sprintf(s, "PROCESS NCHG %d\n", ip->ifru.from_gateca);
   break;
  case FLOWG_MIPD:
   sprintf(s, "MIPD %s\n", ip->ifru.from_np->nsym->synam);
   break;
  case FLOWG_WIRE_EV:
   sprintf(s, "WIRE EV %s\n", ip->ifru.from_np->nsym->synam);
   break;
  case FLOWG_TRPTH:
   sprintf(s, "TRPTH %s\n", ip->ifru.from_np->nsym->synam);
   break;
  case FLOWG_MDC:
   //AIV LOOKATME - merged doesn't come from any one place
   stp = ip->ifru.from_stp;
   strcpy(s, "MDC\n");
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

#endif

/*
 * dump flow graph back edge list for a given basic block
 */
extern void __dmp_bblk_backelst(struct bblk_t *bbp, struct flowg_t *fgp,
 struct mod_t *mdp)
{
 int32 blki;
 struct bbedge_t *bbep;
 struct bblklst_t *bblp;

 __my_fprintf(stdout, "BBLK BACK EDGESps to (without back edges):\n");
 for (bblp = fgp->enter_bblks; bblp != NULL; bblp = bblp->bl_nxt)
  {
   __my_fprintf(stdout, "entry bblk B0%d (RPO order num %d)\n",
    bblp->bl_bbp->bblk_seqno, bblp->bl_bbp->revpostordno);
  }
 
 for (blki = 1; blki < fgp->fg_num_bblks; blki++)
  {
   bbp = __bblktab[blki];

   if (bbp->bbe_prev == NULL)
    {
     __my_fprintf(stdout, "block B0%d - back edge list EMPTY\n",
      bbp->bblk_seqno);
     return;
    }
   //SJM? - PUTMEBACK -  chk_bblk_bedges(bbp, fgp, mdp);
   for (bbep = bbp->bbe_prev; bbep != NULL; bbep = bbep->bbenxt) 
    {
//SJM? - why can back edges be duplicated? - should they only be added if new
     /* DBG remove -- */
     if (bbp->bblk_seqno == bbep->eblkp->bblk_seqno)
      __misc_terr(__FILE__, __LINE__);
     /* --- */
    __my_fprintf(stdout,
     "block B%0d (rpo=B%0d) - back edge from B%0d (rpo=B%0d)\n",
     bbp->bblk_seqno, bbp->revpostordno, bbep->eblkp->bblk_seqno,
     bbep->eblkp->revpostordno);
    }
  }
}

/*
 * check a basic block for duplicated back edges
 */
extern void __chk_bblk_bedges(struct bblk_t *bbp, struct flowg_t *fgp,
 struct mod_t *mdp) 
{
 struct bbedge_t *bbep, *bbep2;

 for (bbep = bbp->bbe_prev; bbep != NULL; bbep = bbep->bbenxt)
  {
   for (bbep2 = bbep->bbenxt; bbep2 != NULL; bbep2 = bbep2->bbenxt) 
    {
     if (bbep->eblkp == bbep2->eblkp)
      {
       __my_fprintf(stdout, "back edge list for bblk %d has duplicates:\n",
         bbp->bblk_seqno);
       __misc_terr(__FILE__, __LINE__);

//SJM? - what about duplicate back edges
//DUPLICATE BACK EDGES?    __dump_one_flowg_insns(fgp, mdp);
//DUPLICATE BACK EDGES??    __misc_terr(__FILE__, __LINE__);
      }
    }
  }
}

/*
 * build a string describing contents of a tn location for tmp tab dumping
 */ 
extern char *__tn_tostr(char *s, struct tn_t *tnp, int32 after_reg_alloc)
{
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN];

 if (tnp->child_tag_offset != 0)
  {
#ifdef __CVC32__
   sprintf(s3, " PAR=%d CHILD_OFS=%u", tnp->tag_parent_tni,
    tnp->child_tag_offset);
#else
   sprintf(s3, " PAR=%d CHILD_OFS=%lu", tnp->tag_parent_tni,
    tnp->child_tag_offset);
#endif
  }
 else strcpy(s3, "");

 __tn_type_tostr(s1, tnp->tn_typ);
 if (tnp->comlab_typ == COMLAB_NONE)
  {
   /* CASE 1: reg or ebp offset tmp on stack */
   if (after_reg_alloc) __tn_to_assgnloc(s2, tnp);
   else strcpy(s2, "");

   /* now s3 has the tag indentifying and offset info */   
   sprintf(s, "%s(%0d) %s%s", s1, tnp->tnwid, s2, s3);
   return(s);
  }

 /* CASE 2: a cint - not really a comm area label - labe is cint val */
 if (tnp->comlab_typ == COMLAB_CINT)
  {
   sprintf(s, "CINT=%lu", tnp->tncu.tn_cint); 
   return(s);
  }

 /* CASE 3: some kind of constant or label of com area variables */ 

 /* SJM 12/01/07 - nlo label are now amodes */
 sprintf(s2, "%s", __gen_comm_lab_amods(s4, tnp));

 /* now s2 has the tag indentifying and offset info */   
 sprintf(s, "%s(%0d) %s%s", s1, tnp->tnwid, s2, s3);
 return(s);
}

/*
 * print out the assign or spill location if it has been set
 */
extern char *__tn_to_assgnloc(char *s, struct tn_t *tnp)
{
 int32 tni; 
 size_t ebp_offset;

 tni = tnp - &(__tntab[0]);
 if (tnp->tn_used_wide)
  {
   /* DBG remove -- */
   if (tnp->tn_assigned) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* SJM 11/08/06 - assuming amode not ndxreg disp here so 0 amode disp */
   if (tnp->tn_spilled)
    {
     ebp_offset = __calc_ebp_spill_offset(tni, 0);
#ifdef __CVC32__
     sprintf(s, "= %d(%%ebp)", ebp_offset);
#else
     sprintf(s, "= %ld(%%ebp)", ebp_offset);
#endif
    }
   else strcpy(s, "NO EBP YET");
   return(s);
  }

 /* DBG remove -- */
 if (tnp->tn_spilled && tnp->spill_ebp_byt_ofs == -1)
  __misc_terr(__FILE__, __LINE__);
 if (tnp->tn_assigned && tnp->spill_ebp_byt_ofs != -1)
  __misc_terr(__FILE__, __LINE__);
 if (tnp->tn_assigned && tnp->tn_spilled) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (tnp->comlab_typ != COMLAB_NONE) { strcpy(s, ""); return(s); }
 else
  {
   if (tnp->tn_assigned)
    {
     /* DBG remove -- */
     if (tnp->tn_spilled) __misc_terr(__FILE__, __LINE__);
     /* --- */
     sprintf(s, "= %s", __regs[tnp->x86_regno]);
    }
   else if (tnp->tn_spilled)
    {
     /* DBG remove -- */
     if (tnp->tn_assigned) __misc_terr(__FILE__, __LINE__);
     /* --- */
     ebp_offset = __calc_ebp_spill_offset(tni, 0);
#ifdef __CVC32__
     sprintf(s, "= %d(%%ebp)", ebp_offset);
#else
     sprintf(s, "= %ld(%%ebp)", ebp_offset);
#endif
    }
   else strcpy(s, "NOT ASSGN");
  }
 return(s);
}

/*
 * map a tracking (constant propagation) state to a string
 */
extern char *__trk_state_tostr(char *s, int32 trk_state)
{
 switch (trk_state) {
  case TRK_TOP_UNDEF: strcpy(s, "TRK_TOP_UNDEF"); break;
  case TRK_CON: strcpy(s, "TRK_CON"); break;
  case TRK_BOT_VARYING: strcpy(s, "TRK_BOT_VARYING"); break;
  /* should never see uninialized here */
  default: strcpy(s, "?UNKN?"); __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/* 
 * return T for any jump/suspend type insn
 */
extern int32 __is_jmp_insn(int32 opcod)
{
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(opcod);
 if (iip->iclass == ICLASS_JMP || iip->iclass == ICLASS_NDXJMP) return(TRUE);
 return(FALSE);
}

/*
 * return T for any bblk that enters flow graph code from scheduler
 */
extern int32 __is_fg_enter_insn(int32 opcod) 
{
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(opcod);
 if (iip->iclass == ICLASS_ENTER) return(TRUE);
 return(FALSE);
}


/*
 * return T for any bblk that exits flow graph code into scheduler
 */
extern int32 __is_fg_exit_insn(int32 opcod) 
{
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(opcod);
 if (iip->iclass == ICLASS_SUSPEND || iip->iclass == ICLASS_TFJMP)
  return(TRUE);
 return(FALSE);
}

/*
 * LOW LEVEL ROUTINES TO REMOVE-INSERT INSNS IN BASIC BLOCKS
 */

/*
 * try to remove a jmp that is a fall through
 * if the tail is a plain jump and the next block number is the same as
 * the jump to remove the jump
 */
extern void __try_remove_jmp(struct bblk_t *bbp)
{
 struct amode_t *dstp;
 struct insn_t *ip;
 
 ip = bbp->itail;
 if (ip->opcod != I_JMP || bbp->bbnxt == NULL) 
  {
   return;
  }
 
 dstp = &(ip->idst);
 if (ip->jmptyp == CC_NONE && bbp->bbnxt->bblk_seqno == dstp->disp)
  {
   __linkout_insn(ip, TRUE);
  }
}

/*
 * link out one vm insn from a basic block
 */
extern void __linkout_insn(struct insn_t *ip, int32 free_it)
{
 /* DBG remove -- */
 if (__cur_bbp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 if (__cur_bbp->ihd == ip && __cur_bbp->itail == ip) 
  {
   /* emptying block */
   __cur_bbp->ihd = __cur_bbp->itail = NULL;
  }
 else if (ip->iprev == NULL) 
  { 
   /* link out at front */
   __cur_bbp->ihd = ip->inxt; 
   __cur_bbp->ihd->iprev = NULL;
  }
 else if (ip->inxt == NULL)
  {
   /* link out at end (but not emptying) */
   __cur_bbp->itail = ip->iprev;
   __cur_bbp->itail->inxt = NULL;
  }
 else
  {
   /* inside */
   ip->iprev->inxt = ip->inxt;
   ip->inxt->iprev = ip->iprev;
  } 
 /* finally put on free list since linked out */
 if (free_it)
  {
   __free_1insn(ip);
  }
}

/*
 * replace an insn
 *
 * this is first cut where insns just replaced
 */
extern void __replace_insn(struct insn_t *new_ip, struct insn_t *ip)
{
 __insert_before_insn(new_ip, ip);
 __linkout_insn(ip, FALSE);
}

/*
 * MISCELLANEOUS ROUTINES TO CONVERT DEFINE VALUES TO NAMES  
 */
/*
 * extract net-mod-task (if in task) given a scope symbol and mod net index  
 */
extern struct mod_t *__extract_mod_and_tsk(struct sy_t *tfm_syp,
 struct task_t **tskp)
{
 struct mod_t *mdp;
 struct symtab_t *sytp;

 *tskp = NULL;
 if (tfm_syp->sytyp == SYM_M) mdp = tfm_syp->el.emdp;
 else
  {
   *tskp = tfm_syp->el.etskp;
   for (sytp = (*tskp)->tsksymtab; sytp != NULL; sytp = sytp->sytpar) 
    {
     if (sytp->sypofsyt->sytyp == SYM_M) goto found_mod;
    }
   __case_terr(__FILE__, __LINE__);
found_mod:
   mdp = sytp->sypofsyt->el.emdp;
  }
 return(mdp);
}

/*
 * get an tn rtype string
 */
extern char *__tn_type_tostr(char *s1, int32 tntyp)
{
 switch (tntyp) {
  case TN_UNKN: strcpy(s1, "TN_UNKN"); break;
  case TN_VAL: strcpy(s1, "TN_VAL"); break;
  case TN_ADR: strcpy(s1, "TN_ADR"); break;
  default: __case_terr(__FILE__, __LINE__); break;
 }
 return(s1);
}

/*
 * return T if procedural flow graph
 */
extern int32 __is_proc_flowg(int32 fgtyp)
{
 switch (fgtyp) {
  case FLOWG_PROC: case FLOWG_TASK: case FLOWG_FUNC:
   return(TRUE);
  case FLOWG_DCE: case FLOWG_NPP: case FLOWG_MULTFI:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(FALSE);
}

/*
 * convert flow graph type to string name
 */
extern char *__to_flowgnam(char *s, struct flowg_t *fgp)
{
 char s1[RECLEN];

 switch (fgp->flowgtyp) {
  case FLOWG_UNKN: strcpy(s1, "**???**"); break;
  case FLOWG_PROC: strcpy(s1, "proc"); break;
  case FLOWG_TASK: strcpy(s1, "proc task"); break;
  case FLOWG_FUNC: strcpy(s1, "proc func"); break;
  case FLOWG_DCE: strcpy(s1, "dce nchg"); break;
  case FLOWG_NPP: strcpy(s1, "npp nchg"); break;
  case FLOWG_CONTA: strcpy(s1, "conta "); break;
  case FLOWG_ICONN: strcpy(s1, "iconn "); break;
  case FLOWG_GATEDA: strcpy(s1, "gate da "); break;
  case FLOWG_GATECA: strcpy(s1, "gate ca "); break;
  case FLOWG_MULTFI: strcpy(s1, "multfi nchg"); break;
  case FLOWG_NCHG: strcpy(s1, "nchg flowg"); break;
  case FLOWG_PROCESS_NCHG: strcpy(s1, "process nchg flowg"); break;
  case FLOWG_MIPD: strcpy(s1, "mipd"); break;
  case FLOWG_WIRE_EV: strcpy(s1, "wire"); break;
  case FLOWG_TRPTH: strcpy(s1, "trpth"); break;
  case FLOWG_MDC: strcpy(s1, "mdc"); break;
  default: strcpy(s1, "**illegal**"); __case_terr(__FILE__, __LINE__);
 }
 sprintf(s, "%s FG %lu", s1, fgp->fg_seqno); 
 return(s);
}

/*
 * convert insn class number to a string name 
 */
extern char *__to_iclassnam(char *s, int32 vi_class)
{
 switch (vi_class) {
  case ICLASS_UNKN: strcpy(s, "ICLASS_UNKN"); break;
  case ICLASS_MOV: strcpy(s, "ICLASS_MOV"); break;
  case ICLASS_STORE: strcpy(s, "ICLASS_STORE"); break;
  case ICLASS_BIN: strcpy(s, "ICLASS_BIN"); break;
  case ICLASS_UN: strcpy(s, "ICLASS_UN"); break;
  case ICLASS_SHFT: strcpy(s, "ICLASS_SHFT"); break;
  case ICLASS_CMP: strcpy(s, "ICLASS_CMP"); break;
  case ICLASS_JMP: strcpy(s, "ICLASS_JMP"); break;
  case ICLASS_NDXJMP: strcpy(s, "ICLASS_NDXJMP"); break;
  case ICLASS_TFJMP: strcpy(s, "ICLASS_TFJMP"); break;
  case ICLASS_CALL: strcpy(s, "ICLASS_CALL"); break;
  case ICLASS_SUSPEND: strcpy(s, "ICLASS_SUSPEND"); break;
  case ICLASS_PUSH: strcpy(s, "ICLASS_PUSH"); break;
  case ICLASS_POP: strcpy(s, "ICLASS_POP"); break;
  case ICLASS_REAL_1RD: strcpy (s, "ICLASS_REAL_1RD"); break;
  case ICLASS_REAL_NORD: strcpy(s, "ICLASS_REAL_NORD"); break;
  case ICLASS_REAL_WRAX: strcpy(s, "ICLASS_REAL_WRAX"); break;
  case ICLASS_ASL: strcpy(s, "ICLASS_ASL"); break;
  case ICLASS_WREDX: strcpy(s, "ICLASS_WREDX"); break;
  case ICLASS_SETE: strcpy(s, "ICLASS_SETE"); break;
  case ICLASS_LABEL: strcpy(s, "ICLASS_LABEL"); break;
  case ICLASS_DIR: strcpy(s, "ICLASS_DIR"); break;
  case ICLASS_DIV: strcpy(s, "ICLASS_DIV"); break;
  case ICLASS_FUNC_BRK: strcpy(s, "ICLASS_FUNC_BRK"); break;
  case ICLASS_DEFLST: strcpy(s, "ICALSS_DEFLST"); break; 
  default: strcpy(s, "**UNKN**"); __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * ROUTINES TO PROVIDE X86/ALPHA TYPE VIRTUAL MACHINE INSN PROPERTIES
 *
 * INSNS ARE FLOW GRAPH CODE GENERATION REPRESENTATION WITH BOTH MEDIUM
 * LEVEL AND LOW NEAR X86 MACHINE INSNS
 */

/* table of our close to x86 virtual machine insns */
/* AIV LOOKATME - maybe should get rid of some of these fields and expand */
/* the number of classes (could tell if insn takes byte rep from class, etc) */
#ifdef __CVC32__
static struct insn_info_t insn_info[] = {
 { I_UNKN, "UNKN", ICLASS_UNKN, SIZ_NONE },
 { I_BBLK_JMP, "I_BBLK_JMP", ICLASS_JMP, SIZ_NONE },
 { I_COND_JMP, "I_COND_JMP", ICLASS_JMP, SIZ_NONE },
 { I_REAL_COND_JMP, "I_REAL_COND_JMP", ICLASS_JMP, SIZ_NONE },
 /* SJM 07/17/06 - tsk jump needs to be suspend class */
 { I_TSKJMP, "jmp", ICLASS_SUSPEND, SIZ_NONE },
 { I_TSKRET_JMP, "jmp *", ICLASS_TFJMP, SIZ_L },
 { I_BBLK_LABEL, "I_BBLK_LABEL", ICLASS_LABEL, SIZ_NONE },
 { I_ENTER_PROC, "I_ENTER_PROC", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_MDC, "I_ENTER_MDC", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_NB_PROC, "I_ENTER_NB_PROC", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_NB_PROC_FREE, "I_ENTER_NB_PROC_FREE", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_THD_RET, "I_ENTER_THD_RET", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_DECL, "I_ENTER_DECL", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_NPP, "I_ENTER_NPP", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_CAP, "I_ENTER_CAP", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_ICONN, "I_ENTER_ICONN", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_PORT, "I_ENTER_PORT", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_GATECA, "I_ENTER_GATECA", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_GATEDA, "I_ENTER_GATEDA", ICLASS_ENTER, SIZ_NONE },
 { I_MULTFI_SUBR, "I_MULTFI_SUBR", ICLASS_ENTER, SIZ_NONE },
 { I_SUSPEND, "I_SUSPEND", ICLASS_SUSPEND, SIZ_NONE }, 
 { I_COMPLETE, "I_COMPLETE", ICLASS_SUSPEND, SIZ_NONE },

 { I_COPY, "I_COPY", ICLASS_STORE, SIZ_NONE },

 { I_CALL_ASLPROC, "I_CALL_ASLPROC", ICLASS_CALL, SIZ_NONE }, 
 { I_CALL_ASLFUNC, "I_CALL_ASLFUNC", ICLASS_CALL, SIZ_L }, 

 { I_PROLOGUE, "I_PROLOGUE", ICLASS_DIR, SIZ_NONE }, 
 { I_EPILOGUE, "I_EPILOGUE", ICLASS_DIR, SIZ_NONE }, 
 { I_DEFLST, "I_DEFLST", ICLASS_DEFLST, SIZ_NONE },

 { I_MOVL, "movl", ICLASS_MOV, SIZ_L },
 { I_MOVZBL, "movzbl", ICLASS_MOV, SIZ_BL },
 { I_MOVSBL, "movsbl", ICLASS_MOV, SIZ_BL },
 { I_MOVB, "movb", ICLASS_MOV, SIZ_B },
 { I_MOVW, "movw", ICLASS_MOV, SIZ_W },
 { I_MOVZWL, "movzwl", ICLASS_MOV, SIZ_WL },
 { I_LEAL, "leal", ICLASS_MOV, SIZ_L },

 { I_STOREL, "movl", ICLASS_STORE, SIZ_L },
 { I_STOREB, "movb", ICLASS_STORE, SIZ_B },
 { I_STOREW, "movw", ICLASS_STORE, SIZ_W },

 { I_ADDL, "addl", ICLASS_BIN, SIZ_L },
 { I_ADCL, "adcl", ICLASS_BIN, SIZ_L },
 { I_SUBL, "subl", ICLASS_BIN, SIZ_L },
 /* notice this is new x86 minsn that does not used fixed accum */
 { I_IMULL, "imull", ICLASS_BIN, SIZ_L },
 /* this divides src input (that is dest amode) into %eax/%edx pair */
 /* and puts remainder in %edx and dividend in %eax */
 /* need a seperate one for each because of special x86 insn handling */
 { I_DIVL, "divl", ICLASS_DIV, SIZ_L },
 { I_SGN_DIVL, "idivl", ICLASS_DIV, SIZ_L },
 { I_MODL, "divl", ICLASS_DIV, SIZ_L },
 { I_SGN_MODL, "idivl", ICLASS_DIV, SIZ_L },

 { I_ANDL, "andl", ICLASS_BIN, SIZ_L },
 { I_ORL, "orl", ICLASS_BIN, SIZ_L },
 { I_XORL, "xorl", ICLASS_BIN, SIZ_L },

 { I_NOTL, "notl", ICLASS_UN, SIZ_L },
 /* in place but same as write since can ignore read before write */
 { I_NEGL, "negl", ICLASS_UN, SIZ_L },

 /* shift may require dedicated regs but chg type is operator */
 { I_SHRU, "shrl", ICLASS_UN, SIZ_L },
 { I_SARU, "sarl", ICLASS_UN, SIZ_L },
 { I_SHLL, "shll", ICLASS_SHFT, SIZ_BL },
 { I_SHRL, "shrl", ICLASS_SHFT, SIZ_BL },
 { I_SALL, "sall", ICLASS_SHFT, SIZ_BL },
 { I_SARL, "sarl", ICLASS_SHFT, SIZ_BL },

 /* these set condition codes - BEWARE we do not track cc's */
 { I_CMPL, "cmpl", ICLASS_CMP, SIZ_L },
 { I_CMPB, "cmpb", ICLASS_CMP, SIZ_B },
 { I_CMPW, "cmpw", ICLASS_CMP, SIZ_W },
 { I_TESTB, "testb", ICLASS_CMP, SIZ_B },
 { I_TESTL, "testl", ICLASS_CMP, SIZ_L },

 { I_JMP, "jmp", ICLASS_JMP, SIZ_NONE }, 
 /* 08/04/06 - this is like copy - prelowered that is split into 2 x86 jmps */
 { I_COND_JMP, "I_COND_JMP", ICLASS_JMP, SIZ_NONE }, 
 { I_IND_JMP, "jmp *", ICLASS_NDXJMP, SIZ_L },
 { I_PORT_IND_JMP, "jmp *", ICLASS_NDXJMP, SIZ_L },
 //AIV LOOKATME - not so sure about this
 { I_FUNC_JMP, "jmp", ICLASS_FUNC_BRK, SIZ_L },

 { I_CALL, "call", ICLASS_CALL, SIZ_NONE },
 { I_FG_CALL, "call", ICLASS_CALL, SIZ_NONE },
 { I_RETURN, "ret", ICLASS_SUSPEND, SIZ_NONE },
 { I_LEAVE, "leave", ICLASS_SUSPEND, SIZ_NONE },
 { I_PUSHL, "pushl", ICLASS_PUSH, SIZ_L },
 { I_POPL, "popl", ICLASS_POP, SIZ_L },

 /* AIV LOOKATME - 03/08/06 - maybe these real ops should have another class */
 { I_FADD, "fadd", ICLASS_REAL_1RD, SIZ_D },
 { I_FLD, "fld", ICLASS_REAL_1RD, SIZ_D },
 { I_FSUB, "fsub", ICLASS_REAL_1RD, SIZ_D },
 { I_FMUL, "fmul", ICLASS_REAL_1RD, SIZ_D },
 { I_FDIV, "fdiv", ICLASS_REAL_1RD, SIZ_D },
 { I_FABS, "fabs", ICLASS_REAL_NORD, SIZ_NONE },
 { I_FLDL, "fldl", ICLASS_REAL_1RD, SIZ_D },
 { I_FSTPL, "fstpl", ICLASS_REAL_1RD, SIZ_D },
 { I_FADDL, "faddl", ICLASS_REAL_1RD, SIZ_D },
 { I_FSUBL, "fsubl", ICLASS_REAL_1RD, SIZ_D },
 { I_FMULL, "fmull", ICLASS_REAL_1RD, SIZ_D },
 { I_FDIVL, "fdivl", ICLASS_REAL_1RD, SIZ_D },
 { I_FUCOMPP, "fucompp", ICLASS_REAL_NORD, SIZ_NONE },
 { I_FNSTSW, "fnstsw", ICLASS_REAL_WRAX, SIZ_W },
 /* this writes st1 but fp regs invisible */
 { I_FXCH, "fxch", ICLASS_REAL_NORD, SIZ_NONE },
 { I_FCHS, "fchs", ICLASS_REAL_NORD, SIZ_NONE },
 /* actually just right bits 7-15 */
 { I_SAHF, "sahf", ICLASS_REAL_WRAX, SIZ_W },
 { I_FLDZ, "fldz", ICLASS_REAL_NORD, SIZ_NONE },

 { I_ASL_CALL, "call", ICLASS_ASL, SIZ_NONE },
 { I_ASL_REST_STK, "I_ASL_REST_STK", ICLASS_ASL, SIZ_NONE },

 { I_CLTD, "cltd", ICLASS_WREDX, SIZ_L },
 { I_SETE, "sete", ICLASS_SETE, SIZ_B },

 { I_DIRECTIVE, "DIRECTIVE", ICLASS_DIR, SIZ_NONE },
 { I_LABEL, "LABEL", ICLASS_LABEL, SIZ_NONE },
 { I_ENTER_LABEL, "ENTER_LABEL", ICLASS_LABEL, SIZ_NONE },
 { I_NEXT_EVENT, "I_NEXT_EVENT", ICLASS_LABEL, SIZ_NONE },
 { I_NEXT_NCHG_EVENT, "I_NEXT_NCHG_EVENT", ICLASS_LABEL, SIZ_NONE },
 { I_NEVENT_JMP, "jmp *", ICLASS_ASL, SIZ_L },
 { I_ENTER_NCHG, "I_ENTER_NCHG", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_PROCESS_NCHG, "I_ENTER_PROCESS_NCHG", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_MIPD, "I_ENTER_MIPD", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_TRPTH_EV, "I_ENTER_TRPTH_EV", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_WIRE_EV, "I_ENTER_WIRE_EV", ICLASS_ENTER, SIZ_NONE },
 { I_SETNE, "setne", ICLASS_SETE, SIZ_B },
 { I_SETGE, "setge", ICLASS_SETE, SIZ_B },
 { I_SETG, "setg", ICLASS_SETE, SIZ_B },
 { I_SETLE, "setle", ICLASS_SETE, SIZ_B },
 { I_SETL, "setl", ICLASS_SETE, SIZ_B },
 { I_SETA, "seta", ICLASS_SETE, SIZ_B },
 { I_SETAE, "setae", ICLASS_SETE, SIZ_B },
 { I_SETB, "setb", ICLASS_SETE, SIZ_B },
 { I_SETBE, "setbe", ICLASS_SETE, SIZ_B },
 /* AIV 07/23/08 - notice these must be jmp to avoid stack overflow */
 { I_CALL_FREE_NBMEM_EVENT, "jmp     NEXT_FREE_NBMEM_EV", ICLASS_CALL, 
   SIZ_NONE },
 { I_CALL_FREE_EVENT, "jmp     NEXT_FREE_EV", ICLASS_CALL, SIZ_NONE }
};
#else
/* 64 - bit insns */
static struct insn_info_t insn_info[] = {
 { I_UNKN, "UNKN", ICLASS_UNKN, SIZ_NONE },
 { I_BBLK_JMP, "I_BBLK_JMP", ICLASS_JMP, SIZ_NONE },
 { I_COND_JMP, "I_COND_JMP", ICLASS_JMP, SIZ_NONE },
 { I_REAL_COND_JMP, "I_REAL_COND_JMP", ICLASS_JMP, SIZ_NONE },
 /* SJM 07/17/06 - tsk jump needs to be suspend class */
 { I_TSKJMP, "jmp", ICLASS_SUSPEND, SIZ_NONE },
 { I_TSKRET_JMP, "jmp *", ICLASS_TFJMP, SIZ_L },
 { I_BBLK_LABEL, "I_BBLK_LABEL", ICLASS_LABEL, SIZ_NONE },
 { I_ENTER_PROC, "I_ENTER_PROC", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_MDC, "I_ENTER_MDC", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_NB_PROC, "I_ENTER_NB_PROC", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_NB_PROC_FREE, "I_ENTER_NB_PROC_FREE", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_THD_RET, "I_ENTER_THD_RET", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_DECL, "I_ENTER_DECL", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_NPP, "I_ENTER_NPP", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_CAP, "I_ENTER_CAP", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_ICONN, "I_ENTER_ICONN", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_PORT, "I_ENTER_PORT", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_GATECA, "I_ENTER_GATECA", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_GATEDA, "I_ENTER_GATEDA", ICLASS_ENTER, SIZ_NONE },
 { I_MULTFI_SUBR, "I_MULTFI_SUBR", ICLASS_ENTER, SIZ_NONE },
 { I_SUSPEND, "I_SUSPEND", ICLASS_SUSPEND, SIZ_NONE }, 
 { I_COMPLETE, "I_COMPLETE", ICLASS_SUSPEND, SIZ_NONE },

 { I_COPY, "I_COPY", ICLASS_STORE, SIZ_NONE },

 { I_CALL_ASLPROC, "I_CALL_ASLPROC", ICLASS_CALL, SIZ_NONE }, 
 { I_CALL_ASLFUNC, "I_CALL_ASLFUNC", ICLASS_CALL, SIZ_L }, 

 { I_PROLOGUE, "I_PROLOGUE", ICLASS_DIR, SIZ_NONE }, 
 { I_EPILOGUE, "I_EPILOGUE", ICLASS_DIR, SIZ_NONE }, 
 { I_DEFLST, "I_DEFLST", ICLASS_DEFLST, SIZ_NONE },

 { I_MOVL, "movq", ICLASS_MOV, SIZ_L },
 { I_MOVZBL, "movzbq", ICLASS_MOV, SIZ_BL },
 { I_MOVSBL, "movsbq", ICLASS_MOV, SIZ_BL },
 { I_MOVB, "movb", ICLASS_MOV, SIZ_B },
 { I_MOVW, "movw", ICLASS_MOV, SIZ_W },
 { I_MOVZWL, "movzwq", ICLASS_MOV, SIZ_WL },
 { I_LEAL, "leaq", ICLASS_MOV, SIZ_L },

 { I_STOREL, "movq", ICLASS_STORE, SIZ_L },
 { I_STOREB, "movb", ICLASS_STORE, SIZ_B },
 { I_STOREW, "movw", ICLASS_STORE, SIZ_W },

 { I_ADDL, "addq", ICLASS_BIN, SIZ_L },
 { I_ADCL, "adcq", ICLASS_BIN, SIZ_L },
 { I_SUBL, "subq", ICLASS_BIN, SIZ_L },
 /* notice this is new x86 minsn that does not used fixed accum */
 { I_IMULL, "imulq", ICLASS_BIN, SIZ_L },
 /* this divides src input (that is dest amode) into %eax/%edx pair */
 /* and puts remainder in %edx and dividend in %eax */
 /* need a seperate one for each because of special x86 insn handling */
 { I_DIVL, "divq", ICLASS_DIV, SIZ_L },
 { I_SGN_DIVL, "idivq", ICLASS_DIV, SIZ_L },
 { I_MODL, "divq", ICLASS_DIV, SIZ_L },
 { I_SGN_MODL, "idivq", ICLASS_DIV, SIZ_L },

 { I_ANDL, "andq", ICLASS_BIN, SIZ_L },
 { I_ORL, "orq", ICLASS_BIN, SIZ_L },
 { I_XORL, "xorq", ICLASS_BIN, SIZ_L },

 { I_NOTL, "notq", ICLASS_UN, SIZ_L },
 /* in place but same as write since can ignore read before write */
 { I_NEGL, "negq", ICLASS_UN, SIZ_L },

 /* shift may require dedicated regs but chg type is operator */
 { I_SHRU, "shrq", ICLASS_UN, SIZ_L },
 { I_SARU, "sarq", ICLASS_UN, SIZ_L },
 { I_SHLL, "shlq", ICLASS_SHFT, SIZ_BL },
 { I_SHRL, "shrq", ICLASS_SHFT, SIZ_BL },
 { I_SALL, "salq", ICLASS_SHFT, SIZ_BL },
 { I_SARL, "sarq", ICLASS_SHFT, SIZ_BL },

 /* these set condition codes - BEWARE we do not track cc's */
 { I_CMPL, "cmpq", ICLASS_CMP, SIZ_L },
 { I_CMPB, "cmpb", ICLASS_CMP, SIZ_B },
 { I_CMPW, "cmpw", ICLASS_CMP, SIZ_W },
 { I_TESTB, "testb", ICLASS_CMP, SIZ_B },
 { I_TESTL, "testq", ICLASS_CMP, SIZ_L },

 { I_JMP, "jmp", ICLASS_JMP, SIZ_NONE }, 
 /* 08/04/06 - this is like copy - prelowered that is split into 2 x86 jmps */
 { I_COND_JMP, "I_COND_JMP", ICLASS_JMP, SIZ_NONE }, 
 { I_IND_JMP, "jmp *", ICLASS_NDXJMP, SIZ_L },
 { I_PORT_IND_JMP, "jmp *", ICLASS_NDXJMP, SIZ_L },
 //AIV LOOKATME - not so sure about this
 { I_FUNC_JMP, "jmp", ICLASS_FUNC_BRK, SIZ_L },

 { I_CALL, "call", ICLASS_CALL, SIZ_NONE },
 { I_FG_CALL, "call", ICLASS_CALL, SIZ_NONE },
 { I_RETURN, "ret", ICLASS_SUSPEND, SIZ_NONE },
 { I_LEAVE, "leave", ICLASS_SUSPEND, SIZ_NONE },
 { I_PUSHL, "pushq", ICLASS_PUSH, SIZ_L },
 { I_POPL, "popq", ICLASS_POP, SIZ_L },

 /* AIV LOOKATME - 03/08/06 - maybe these real ops should have another class */
 { I_FADD, "addsd   %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_D },
 { I_FLD, "fld", ICLASS_REAL_NORD, SIZ_D },
 { I_FSUB, "subsd   %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_D },
 { I_FMUL, "fmuq", ICLASS_REAL_NORD, SIZ_D },
 { I_FDIV, "fdiv", ICLASS_REAL_NORD, SIZ_D },
 { I_FABS, "fabs", ICLASS_REAL_NORD, SIZ_NONE },
 { I_FLDL, "fldq", ICLASS_REAL_NORD, SIZ_D },
 { I_FSTPL, "fstpq", ICLASS_REAL_NORD, SIZ_D },
 { I_FADDL, "addsd   %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_D },
 { I_FSUBL, "subsd   %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_D },
 { I_FMULL, "mulsd   %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_D },
 { I_FDIVL, "divsd   %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_D },
 { I_FUCOMPP, "ucomisd %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_NONE },
 { I_XORSREAL, "xorpd   %xmm0, %xmm0", ICLASS_REAL_NORD, SIZ_NONE },
 { I_LDRNEG, "movsd   REALNEG(%rip), %xmm0", ICLASS_REAL_NORD, SIZ_NONE },
 { I_XORNREAL, "xorpd   %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_NONE },
 { I_ANDAREAL, "andpd   %xmm1, %xmm0", ICLASS_REAL_NORD, SIZ_NONE },
 { I_LDRABS, "movsd   REALABS(%rip), %xmm1", ICLASS_REAL_NORD, SIZ_NONE },
 { I_LDEPSILON, "movsd   EPSILON(%rip), %xmm0", ICLASS_REAL_NORD, SIZ_NONE },
 { I_FNSTSW, "fnstsw", ICLASS_REAL_WRAX, SIZ_W },
 /* this writes st1 but fp regs invisible */
 { I_FXCH, "fxch", ICLASS_REAL_NORD, SIZ_NONE },
 { I_FCHS, "fchs", ICLASS_REAL_NORD, SIZ_NONE },
 /* actually just right bits 7-15 */
 { I_SAHF, "sahf", ICLASS_REAL_WRAX, SIZ_W },
 { I_FLDZ, "fldz", ICLASS_REAL_NORD, SIZ_NONE },

 { I_ASL_CALL, "call", ICLASS_ASL, SIZ_NONE },
 { I_ASL_REST_STK, "I_ASL_REST_STK", ICLASS_ASL, SIZ_NONE },

 { I_CLTD, "cltq", ICLASS_WREDX, SIZ_L },
 { I_SETE, "sete", ICLASS_SETE, SIZ_B },

 { I_DIRECTIVE, "DIRECTIVE", ICLASS_DIR, SIZ_NONE },
 { I_LABEL, "LABEL", ICLASS_LABEL, SIZ_NONE },
 { I_ENTER_LABEL, "ENTER_LABEL", ICLASS_LABEL, SIZ_NONE },
 { I_NEXT_EVENT, "I_NEXT_EVENT", ICLASS_LABEL, SIZ_NONE },
 { I_NEXT_NCHG_EVENT, "I_NEXT_NCHG_EVENT", ICLASS_LABEL, SIZ_NONE },
 { I_NEVENT_JMP, "jmp *", ICLASS_ASL, SIZ_L },
 { I_ENTER_NCHG, "I_ENTER_NCHG", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_PROCESS_NCHG, "I_ENTER_PROCESS_NCHG", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_MIPD, "I_ENTER_MIPD", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_TRPTH_EV, "I_ENTER_TRPTH_EV", ICLASS_ENTER, SIZ_NONE },
 { I_ENTER_WIRE_EV, "I_ENTER_WIRE_EV", ICLASS_ENTER, SIZ_NONE },
 { I_MOVQ, "movq", ICLASS_MOV, SIZ_L },
 { I_MOVABSQ, "movabsq", ICLASS_MOV, SIZ_L },
 { I_STOREQ, "movq", ICLASS_STORE, SIZ_L },
 { I_SUBQ, "subq", ICLASS_STORE, SIZ_L },
 { I_ADDQ, "addq", ICLASS_STORE, SIZ_L },
 { I_PUSHQ, "pushq", ICLASS_STORE, SIZ_L },
 { I_POPQ, "popq", ICLASS_STORE, SIZ_L },
 { I_SETNE, "setne", ICLASS_SETE, SIZ_B },
 { I_SETGE, "setge", ICLASS_SETE, SIZ_B },
 { I_SETG, "setg", ICLASS_SETE, SIZ_B },
 { I_SETLE, "setle", ICLASS_SETE, SIZ_B },
 { I_SETL, "setl", ICLASS_SETE, SIZ_B },
 { I_SETA, "seta", ICLASS_SETE, SIZ_B },
 { I_SETAE, "setae", ICLASS_SETE, SIZ_B },
 { I_SETB, "setb", ICLASS_SETE, SIZ_B },
 { I_SETBE, "setbe", ICLASS_SETE, SIZ_B },
 { I_LDR1, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR2, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR3, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR4, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR5, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR6, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR7, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR8, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR9, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR10, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR11, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR12, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR13, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR14, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR15, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_LDR16, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_STREAL, "movsd", ICLASS_REAL_1RD, SIZ_D },
 { I_MOVSLQ, "movslq", ICLASS_MOV, SIZ_QL },
 { I_MOVQL, "movl", ICLASS_MOV, SIZ_LL },
 { I_STOREQL, "movl", ICLASS_STORE, SIZ_LL },
 /* AIV 07/23/08 - notice these must be jmp to avoid stack overflow */
 { I_CALL_FREE_NBMEM_EVENT, "jmp     NEXT_FREE_NBMEM_EV", ICLASS_CALL, 
   SIZ_NONE },
 { I_CALL_FREE_EVENT, "jmp     NEXT_FREE_EV", ICLASS_CALL, SIZ_NONE }
};
#endif

#define NUM_INSNS (sizeof(insn_info) / sizeof(struct insn_info_t))

/* indices only used here */
struct insn_info_t **insn_info_ndx;

extern void __bld_iinfo_tabs(void)
{
 int32 ii;

 insn_info_ndx = (struct insn_info_t **)
  __my_malloc((LAST_INSN + 1)*sizeof(struct insn_info_t *));
 for (ii = 0; ii < NUM_INSNS; ii++)
  {
   insn_info_ndx[insn_info[ii].inum] = &(insn_info[ii]);
  }
}

/*
 * get vm pre lowering insn record from number
 */
extern struct insn_info_t *__to_iinfo_rec(int32 opcod)
{
 return(insn_info_ndx[opcod]);
}

/*
 * TABLE AND ROUTINES TO PROVIDE ASM LIB (ASL_) ROUTINE PROPERTIES
 */
struct asl_info_t __aslinfo[] = {
//void *__asl_downrel_targ_to_ref(struct gref_t *)
 {ASL_DOWNREL_TARG_TO_REF, "__asl_downrel_targ_to_ref", TRUE, 
   RE_PTR, {A_RPTR} },
//void *__asl_uprel_targ_to_ref(struct gref_t *)
 {ASL_UPREL_TARG_TO_REF, "__asl_uprel_targ_to_ref", TRUE, RE_PTR, {A_RPTR} },
//  void *__asl_get_uprel_idp(struct gref_t *)
 {ASL_GET_UPREL_IDP, "__asl_get_uprel_idp", TRUE, RE_PTR, {A_RPTR} },
// int32 __asl_get_downrel_idp(struct gref_t *)
 {ASL_GET_DOWNREL_IDP, "__asl_get_downrel_idp", TRUE, RE_PTR, {A_RPTR} },
// void __asl_sched_proc_delay(struct st_t *, struct tev_t *)
 {ASL_SCHED_PROC_DELAY, "__asl_sched_proc_delay", TRUE, RE_VOID, 
   {A_RPTR, A_RPTR} },
// void __asl_arm_ectrl(struct tev_t *, int32)
 {ASL_ARM_ECTRL, "__asl_arm_ectrl", FALSE, RE_VOID, {A_RPTR, A_NUM} },
// void *__asl_setsav_assoc_tsk(struct st_t *)
 {ASL_SETSAV_ASSOC_TSK, "__asl_setsav_assoc_tsk", FALSE, RE_PTR, {A_RPTR} },
// word32 *__asl_arm_nb_ectrl(struct st_t *, void *, int32)
 {ASL_ARM_NB_ECTRL, "__asl_arm_nb_ectrl", TRUE, RE_PTR, 
   {A_RPTR, A_RPTR} },
// word32 *__asl_arm_nb_varndx_ectrl(struct st_t *, void *, int32, 
// struct tev_t *, int32)
 {ASL_ARM_NB_VARNDX_ECTRL, "__asl_arm_nb_varndx_ectrl", TRUE, RE_PTR, 
  {A_RPTR, A_RPTR, A_INT} },
// void __asl_sched_namblk_thd(struct st_t *)
 {ASL_SCHED_NAMBLK_THD, "__asl_sched_namblk_thd", TRUE, RE_VOID, {A_RPTR} },
// void __asl_sched_fork(struct st_t *, struct st_t *)
 {ASL_SCHED_FORK, "__asl_sched_fork", TRUE, RE_VOID, {A_RPTR, A_RPTR} },
// void__asl_exec_stsk(struct st_t *)
 {ASL_EXEC_STSK, "__asl_exec_stsk", TRUE, RE_VOID, {A_RPTR} },
// int32 __asl_reg_qcaf_inhibit(struct net_t *)
 {ASL_REG_QCAF_INHIBIT, "__asl_reg_qcaf_inhibit", TRUE, RE_INT, {A_RPTR} },
// int32 __asl_scalar_wire_inhibit(struct net_t *)
 {ASL_SCALAR_WIRE_INHIBIT, "__asl_scalar_wire_inhibit", TRUE, RE_INT, 
   {A_RPTR} },
// int32 __asl_bsel_wirfrc_inhibit(struct net_t *, int32)
 {ASL_BSEL_WIRFRC_INHIBIT, "__asl_bsel_wirfrc_inhibit", TRUE, RE_INT,
  {A_RPTR, A_INT} },
 /* SJM 06-16-07 - next 4 partially fixed so write ptr first arg */
 /* but still can't be tracked since also return int (can't return 2 vals) */
// int32 __asl_stren_correct_frc(byte *, struct net_t *)
 {ASL_STREN_CORRECT_FRC, "__asl_stren_correct_frc", TRUE, RE_INT, 
  {A_RWPTR, A_RPTR} },
// int32 __asl_correct_frc(word32 *, struct net_t *)
 {ASL_CORRECT_FRC, "__asl_correct_frc", TRUE, RE_INT, {A_RWPTR, A_RPTR} },
 /* AIV 02/02/12 - these psel force wrappers need to set idp */
// int32 __asl_psel_correct_frc(word32 *, struct net_t *, int32, int32)
 {ASL_PSEL_CORRECT_FRC, "__asl_psel_correct_frc", TRUE, RE_INT, 
   {A_RWPTR, A_RPTR, A_NUM, A_NUM} },
// int32 __asl_stren_psel_correct_frc(byte *, struct net_t *, int32, int32)
 {ASL_STREN_PSEL_CORRECT_FRC, "__asl_stren_psel_correct_frc", TRUE, RE_INT,
  {A_WPTR, A_RPTR, A_NUM, A_NUM} },
// int32 __asl_jmp_eq_stmask(word32 *, word32 *, int32)
 {ASL_JMP_EQ_STMASK, "__asl_jmp_eq_stmask", FALSE, RE_INT, 
   {A_RPTR, A_RPTR, A_NUM} },
// void __asl_trigger_ectrl(struct tev_t *)
 {ASL_TRIGGER_ECTRL, "__asl_trigger_ectrl", FALSE, RE_VOID, {A_INT} },
// void __asl_nb_trigger_ectrl(i_tev_ndx)
 {ASL_NB_TRIGGER_ECTRL, "__asl_nb_trigger_ectrl", FALSE, RE_VOID, {A_INT} },
// void __asl_fmonit_trigger(struct dcevnt_t *)
 {ASL_FMONIT_TRIGGER, "__asl_fmonit_trigger", FALSE, RE_VOID, {A_RPTR} },
 /* AIV 02/02/12 - these need to to set idp */
// void __asl_assign_qcaf(struct dcevnt_t *, struct nchglst_t *, int32)
 {ASL_ASSIGN_QCAF, "__asl_assign_qcaf", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR, A_NUM} },
// void __asl_movabw_fr_svec(word32 *, byte *, int32)
 {ASL_MOVABW_FR_SVEC, "__asl_movabw_fr_svec", FALSE, RE_VOID, {A_WPTR, A_RPTR,
   A_NUM} },
 {ASL_MOVABW_ONEW_FR_SVEC, "__asl_movabw_onew_fr_svec", FALSE, RE_INT, {A_RPTR,
   A_NUM} },
// void __asl_movsb_fr_wstad(byte *, word32 *, int32, word32) 
 {ASL_MOVSB_FR_WSTAD, "__asl_movsb_fr_wstad", FALSE, RE_VOID, {A_WPTR, A_RPTR,
  A_NUM, A_INT} },
// void __asl_movsb_fr_widestad(byte *, word32 *, int32, word32) 
 {ASL_MOVSB_FR_WIDESTAD, "__asl_movsb_fr_widestad", FALSE, RE_VOID, 
   {A_WPTR, A_RPTR, A_NUM, A_INT} },
// byte __asl_movsb_fr_scalstad(word32, word32) 
 {ASL_MOVSB_FR_SCALSTAD, "__asl_movsb_fr_scalstad", FALSE, RE_BYTE, 
   {A_INT, A_INT} },
// double __asl_movr_fr_w(word32 *, int32)
 {ASL_MOVR_FR_W, "__asl_movr_fr_w", FALSE, RE_DBLE, {A_RPTR, A_NUM} },
// double __asl_movr_fr_sgnw(word32 *, int32)
 {ASL_MOVR_FR_SGNW, "__asl_movr_fr_sgnw", FALSE, RE_DBLE, {A_RPTR, A_NUM} },
// void __asl_movw_fr_r(word32 *, double)
 {ASL_MOVW_FR_R, "__asl_movw_fr_r", FALSE, RE_VOID, {A_WPTR, A_DBLE} },
// word32 __asl_movw_fr_r_2state(double)
 {ASL_MOVW_FR_R_2STATE, "__asl_movw_fr_r_2state", FALSE, RE_INT, {A_DBLE} },
// void *__asl_exec_sysfunc(struct expr_t *)
 {ASL_EXEC_SYSFUNC, "__asl_exec_sysfunc", TRUE, RE_PTR, {A_RPTR} },
// int32 __asl_widcas_eval(word32 *, word32 *, int32)
 {ASL_WIDCAS_EVAL, "__asl_widcas_eval", FALSE, RE_INT, 
   {A_RPTR, A_RPTR, A_NUM} },
// int32 __asl_widcasx_eval(word32 *, word32 *, int32)
 {ASL_WIDCASX_EVAL, "__asl_widcasx_eval", FALSE, RE_INT, 
   {A_RPTR, A_RPTR, A_NUM} },
// int32 __asl_widcasz_eval(word32 *, word32 *, int32)
 {ASL_WIDCASZ_EVAL, "__asl_widcasz_eval", FALSE, RE_INT, 
   {A_RPTR, A_RPTR, A_NUM} },
// void __asl_wide_bitxor(word32 *, word32 *, word32 *, int32)
 {ASL_WIDE_BITXOR, "__asl_wide_bitxor", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// void __asl_wide_notl(word32 *, word32 *, int32)
 {ASL_WIDE_NOTL, "__asl_wide_notl", FALSE, RE_VOID, {A_WPTR, A_RPTR, A_NUM} },
// void __asl_wide_bitand(word32 *, word32 *, word32 *, int32)
 {ASL_WIDE_BITAND, "__asl_wide_bitand", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// word32 __asl_wide_redxor(word32 *, int32)
 {ASL_WIDE_REDXOR, "__asl_wide_redxor", FALSE, RE_INT, {A_RPTR, A_NUM} },
// void __asl_wid_bin_bitxnor(word32 *, word32 *, word32 *, int32)
 {ASL_WID_BIN_BITXNOR, "__asl_wid_bin_bitxnor", FALSE, RE_VOID, {A_WPTR, A_RPTR,
  A_RPTR, A_NUM} },
// void __asl_wid_bin_bitxnor_2state(word32 *, word32 *, word32 *, int32)
 {ASL_WID_BIN_BITXNOR_2STATE, "__asl_wid_bin_bitxnor_2state", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// void __asl_wid_bin_bitor(word32 *, word32 *, word32 *, int32)
 {ASL_WID_BIN_BITOR, "__asl_wid_bin_bitor", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// int32 __asl_wid_un_redor(word32 *, word32 *, int32)
 {ASL_WID_UN_REDOR, "__asl_wid_un_redor", FALSE, RE_INT, 
  {A_WPTR, A_RPTR, A_NUM} },
// void __asl_wid_unbitnot(word32 *, word32 *, int32)
 {ASL_WID_UNBITNOT, "__asl_wid_unbitnot", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_NUM} },
// void __asl_wid_unbitnot_2state(word32 *, word32 *, int32)
 {ASL_WID_UNBITNOT_2STATE, "__asl_wid_unbitnot_2state", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_NUM} },
// void __asl_wide_bitor(word32 *, word32 *, word32 *, int32)
 {ASL_WIDE_BITOR, "__asl_wide_bitor", FALSE, RE_VOID, {A_WPTR, A_RPTR, A_RPTR,
  A_NUM} },
// void __mwrshift(word32 *, word32, int32)
 {ASL_WIDE_RSHIFT, "__mwrshift", FALSE, RE_VOID, { A_WPTR, A_INT, A_NUM} },
// void __mwrshift(word32 *, word32, int32)
 {ASL_WIDE_LSHIFT, "__mwlshift", FALSE, RE_VOID, { A_WPTR, A_INT, A_NUM} },
// int32 __asl_widomitxz_ne(word32 *, word32 *, int32)
 {ASL_WIDOMITXZ_NE, "__asl_widomitxz_ne", FALSE, RE_INT, 
  { A_RPTR, A_RPTR, A_NUM} },
// void __asl_sgnmask(word32 *, word32, int32)
 {ASL_SGNMASK, "__asl_sgnmask", FALSE, RE_VOID, { A_RWPTR, A_INT, A_NUM} },
// void __asl_setup_task_thd(struct st_t *, struct st_t *)
 {ASL_SETUP_TASK_THD, "__asl_setup_task_thd", TRUE, RE_VOID, 
  { A_RPTR, A_RPTR} },
// void __asl_setup_task_thd_auto(struct st_t *, struct st_t *, t_midat *)
 {ASL_SETUP_TASK_THD_AUTO, "__asl_setup_task_thd_auto", TRUE, RE_VOID, 
  { A_RPTR, A_RPTR, A_RPTR} },
// int32 __asl_tskdone_cleanup_ret(void)
 {ASL_TSKDONE_CLEANUP_RET, "__asl_tskdone_cleanup_ret", FALSE, RE_INT },
// void __asl_tskdone_cleanup_ret_auto(void)
 {ASL_TSKDONE_CLEANUP_RET_AUTO, "__asl_tskdone_cleanup_ret_auto", FALSE, RE_VOID },
// t_midat __asl_thread_auto_cleanup(void)
 {ASL_THREAD_AUTO_CLEANUP, "__asl_thread_auto_cleanup", FALSE, RE_INT },
// int32 __asl_wide_cmp(word32 *, word32 *, int32, int32)
 {ASL_WIDE_CMP, "__asl_wide_cmp", FALSE, RE_INT, 
   { A_RPTR, A_RPTR, A_NUM, A_INT} },
// int32 __asl_sgn_wide_cmp(word32 *, word32 *, int32, int32)
 {ASL_SGN_WIDE_CMP, "__asl_sgn_wide_cmp", FALSE, RE_INT, {A_RPTR, A_RPTR, A_NUM,
  A_INT} },
// int32 __asl_wide_word_cmp(word32 *, word32, int32, int32)
 {ASL_WIDE_WORD_CMP, "__asl_wide_word_cmp", FALSE, RE_INT, 
  {A_RPTR, A_INT, A_NUM, A_INT} },
// int32 __asl_wide_sgnword_cmp(int32, word32 *, int32, int32)
 {ASL_WIDE_SGNWORD_CMP, "__asl_wide_sgnword_cmp", FALSE, RE_INT, 
  {A_INT, A_RPTR, A_NUM, A_INT} },
// int32 __asl_wide_jmpor_0(word32 *, word32 *, int32)
 {ASL_WIDE_JMPOR_0, "__asl_wide_jmpor_0", FALSE, RE_INT, 
  {A_RPTR, A_RPTR, A_NUM} },
// int32 __asl_wide_jmp_eq(word32 *, word32 *, int32 opwid)
 {ASL_WIDE_JMP_EQ, "__asl_wide_jmp_eq", FALSE, RE_INT, 
  {A_RPTR, A_RPTR, A_NUM} },
// void __asl_sgn_xtnd_widen(word32 *, word32 *, int32, int32)
 {ASL_SGN_XTND_WIDEN, "__asl_sgn_xtnd_widen", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_NUM, A_NUM} },
// void __asl_exec_cause(struct st_t *, struct nchglst_t *)
 {ASL_EXEC_CAUSE, "__asl_exec_cause", TRUE, RE_VOID, {A_RPTR, A_RPTR} },
// int32 __asl_repcnt_jmp(word32 *, int32)
 /* SJM 04/20/07 - the repcnt is updated in the RT NL, but is not a write ptr */
 {ASL_REPCNT_JMP, "__asl_repcnt_jmp", FALSE, RE_INT, {A_RPTR, A_NUM} },
// int32 __asl_wide_any1(word32 *, word32 *, int32)
 {ASL_WIDE_ANY1, "__asl_wide_any1", FALSE, RE_INT, {A_RPTR, A_RPTR, A_NUM} },
// void __asl_wide_qcol_comb_opands(word32 *, word32 *, word32 *, int32)
 {ASL_WIDE_QCOL_COMB_OPANDS, "__asl_wide_qcol_comb_opands", FALSE, RE_VOID,
  {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// int32 __asl_sgnbit_on(word32 *, int32)
 {ASL_SGNBIT_ON, "__asl_sgnbit_on", FALSE, RE_INT, {A_RPTR, A_NUM} },
// void __asl_set_byteval(byte *, byte, int32)
 {ASL_SET_BYTEVAL, "__asl_set_byteval", FALSE, RE_VOID, 
  {A_WPTR, A_INT, A_NUM} },
// word32 __asl_ld_logic_wide_driver(struct gate_t *, int32)
 {ASL_LD_LOGIC_WIDE_DRIVER, "__asl_ld_logic_wide_driver", TRUE, RE_INT, 
   {A_RPTR, A_NUM} },
// int32 __asl_exec_wide_logic_gate(struct gate_t *, int32)
 {ASL_EXEC_WIDE_LOGIC_GATE, "__asl_exec_wide_logic_gate", TRUE, RE_INT, 
   {A_RPTR, A_NUM} },
// void __asl_schd_caev(struct conta_t *)
 {ASL_SCHD_CAEV, "__asl_schd_caev", TRUE, RE_VOID, {A_RPTR, A_RPTR} },
// void __asl_cancel_ev(struct tev_t *) 
 {ASL_CANCEL_EV, "__asl_cancel_ev", FALSE, RE_VOID, {A_RPTR} },
// void __asl_calc_bufif_newstate(word32, int32, int32)
 {ASL_CALC_BUFIF_NEWSTATE, "__asl_calc_bufif_newstate", FALSE, RE_INT, 
  {A_INT, A_NUM, A_NUM} },
//void __asl_set_rhs_new_gateval(word32 *rhs_wp, int32 rhswid)
 {ASL_SET_RHS_NEW_GATEVAL, "__asl_set_rhs_new_gateval", FALSE, RE_VOID, 
  {A_RPTR, A_NUM} },
// int32 __asl_eval_cmos_gate(int32, int32, int32, int32)
 {ASL_EVAL_CMOS_GATE, "__asl_eval_cmos_gate", FALSE, RE_INT, 
  {A_INT, A_INT, A_INT, A_INT} },
// int32 __asl_eval_rcmos_gate(int32, int32, int32, int32)
 {ASL_EVAL_RCMOS_GATE, "__asl_eval_rcmos_gate", FALSE, RE_INT, 
  {A_INT, A_INT, A_INT, A_INT} },
// void __asl_stren_schd_1gev(struct gate_t *, void *)
 {ASL_STREN_SCHD_1GEV, "__asl_stren_schd_1gev", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR} },
// void __asl_schd_1gev(struct gate_t *, struct tev_t *)
 {ASL_SCHD_1GEV, "__asl_schd_1gev", TRUE, RE_VOID, {A_RPTR, A_RPTR} },
// void __asl_schd_1gev_const(struct tev_t *)
 {ASL_SCHD_1GEV_CONST, "__asl_schd_1gev_const", FALSE, RE_VOID, {A_RPTR} },
// void __asl_schd_1gev_pnd0(struct tev_t *)
 {ASL_SCHD_1GEV_PND0, "__asl_schd_1gev_pnd0", FALSE, RE_VOID, {A_RPTR} },
// int32 __asl_cancele_pend_nochg_1gev(struct gate_t *, int32)
 {ASL_CANCELE_PEND_NOCHG_1GEV, "__asl_cancele_pend_nochg_1gev", TRUE, RE_INT,
  {A_RPTR, A_RPTR} },
// void __asl_chg_gate_outwire(int32)
 {ASL_CHG_GATE_OUTWIRE, "__asl_chg_gate_outwire", FALSE, RE_VOID, {A_RPTR} },
// int32 __asl_cancele_pend_chg_1gev(struct gate_t *, struct tev_t *)
 {ASL_CANCELE_PEND_CHG_1GEV, "__asl_cancele_pend_chg_1gev", TRUE, RE_INT, 
  {A_RPTR, A_RPTR} },
// int32 __asl_pend_nochg_1gev(struct tev_t *)
 {ASL_PEND_NOCHG_1GEV, "__asl_pend_nochg_1gev", FALSE, RE_INT, {A_RPTR} },
// void __asl_stren_pend_chg_1gev(struct gate_t *, struct tev_t *)
 {ASL_STREN_PEND_CHG_1GEV, "__asl_stren_pend_chg_1gev", TRUE, RE_VOID, {A_RPTR,
  A_RPTR} },
// void __asl_pend_chg_1gev(struct gate_t *, struct tev_t *)
 {ASL_PEND_CHG_1GEV, "__asl_pend_chg_1gev", TRUE, RE_VOID, {A_RPTR, A_RPTR} },
// void __asl_pend_chg_1gev_const(struct tev_t *, int32)
 {ASL_PEND_CHG_1GEV_CONST, "__asl_pend_chg_1gev_const", FALSE, RE_VOID, 
  {A_RPTR} },
// void __asl_reschd_caev(struct conta_t *, struct tev_t *)
 /* AIV 08/28/09 - this was supposed to be A_RPTR - this must never be */
 /* reached AIV FIXME  - remove???? */
 {ASL_RESCHD_CAEV, "__asl_reschd_caev", TRUE, RE_VOID, {A_RPTR, A_RPTR} },
// void __asl_eval_tran_1bit(struct net_t *, int32)
 {ASL_EVAL_TRAN_DRVRS, "__asl_eval_tran_1bit", TRUE, RE_VOID, {A_RPTR, A_NUM} },
// void __asl_eval_tran_vector(struct net_t *)
 {ASL_EVAL_TRAN_DRVRS_VECTOR, "__asl_eval_tran_vector", TRUE, RE_VOID, 
  {A_RPTR} },
// void __asl_adjust_trireg(byte *, byte *, int32, word32)
 {ASL_ADJUST_TRIREG, "__asl_adjust_trireg", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_NUM, A_INT} },
// void *__asl_ld_tfrwarg_drvp(void)
//AIV? 04/20/07 ??? - LOOKATME - this should be RPTR - why write? */
 {ASL_LD_TFRWARG_DRVP, "__asl_ld_tfrwarg_drvp", FALSE, RE_PTR, {A_RPTR} },
// void __asl_get_perinst_val(word32 *, union pck_u, int32) 
 {ASL_GET_PERINST_VAL, "__asl_get_perinst_val", FALSE, RE_VOID, {A_WPTR, A_RPTR,
  A_NUM} },

 /* SJM 04/20/07 - removed asl sttfrwarg driver wrapper - never used */
// void __asl_stren_sched_unknown_bit(struct net_t *, word32, byte *, 
//struct nchtlst_t *, void *)
 {ASL_STREN_SCHED_UNKNOWN_BIT, "__asl_stren_sched_unknown_bit", FALSE, RE_VOID,
  {A_RPTR, A_INT, A_RPTR, A_INT, A_RPTR} },
// void __asl_sched_unknown_bit(struct net_t *, word32 *, void *)
 {ASL_SCHED_UNKNOWN_BIT, "__asl_sched_unknown_bit", FALSE, RE_VOID, 
  {A_RPTR, A_RPTR, A_RPTR, A_RPTR} },
// int32 __asl_bytecmp(byte *, byte *, int32) 
 {ASL_BYTECMP, "__asl_bytecmp", FALSE, RE_INT, {A_RPTR, A_RPTR, A_NUM} },
 /* SJM 04/20/07 - asl rhspsel removed since it is no longer used */

/* entries where run time routine called directly - no asl lib wrapper */
// void __eval_nmos_gate(word32)
 {ASL_EVAL_NMOS_GATE, "__eval_nmos_gate", FALSE, RE_VOID, {A_INT} },
// void __eval_rnmos_gate(word32)
 {ASL_EVAL_RNMOS_GATE, "__eval_rnmos_gate", FALSE, RE_VOID, {A_INT} },
// void __eval_pmos_gate(word32)
 {ASL_EVAL_PMOS_GATE, "__eval_pmos_gate", FALSE, RE_VOID, {A_INT} },
// void __eval_rpmos_gate(word32)
 {ASL_EVAL_RPMOS_GATE, "__eval_rpmos_gate", FALSE, RE_VOID, {A_INT} },
// void __cp_sofs_wval(word32 *, word32 *, int32, int32)
 {ASL_CP_SOFS_WVAL, "__cp_sofs_wval", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_INT, A_NUM} },
// void __lhspsel(word32 *, int32, word32 *, int32);
 {ASL_LHSPSEL, "__lhspsel", FALSE, RE_VOID, {A_RWPTR, A_INT, A_RPTR, A_INT} },
// word32 __lsub(word32 *, word32 *, word32 *, int32)
 {ASL_LSUB, "__lsub", FALSE, RE_VOID, {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// void __ladd(word32 *, word32 *, word32 *, int32)
 {ASL_LADD, "__ladd", FALSE, RE_VOID, {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// void __lmult(word32 *, word32 *, word32 *, int32);
 {ASL_LMULT, "__lmult", FALSE, RE_VOID, {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// void __sgn_lmult(word32 *, word32 *, word32 *, int32)
 {ASL_SGN_LMULT, "__sgn_lmult", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// void __sgn_ldivmod(word32 *, word32 *, word32 *, int32, int32);
 {ASL_SGN_LDIVMOD, "__sgn_ldivmod", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM, A_INT} },
// void __ldivmod(word32 *, word32 *, word32 *, int32, int32)
 {ASL_LDIVMOD, "__ldivmod", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM, A_INT} },
// word32 __wrd_redxor(word32)
 {ASL_WRD_REDXOR, "__wrd_redxor", FALSE, RE_INT, {A_INT} },
// int32 __wide_vval_is0(word32 *, int32)
 {ASL_WIDE_VVAL_IS0, "__wide_vval_is0", FALSE, RE_INT, {A_RPTR, A_NUM} },
// int32 __vval_is1(word32 *, int32)
 {ASL_VVAL_IS1, "__vval_is1", FALSE, RE_INT, {A_RPTR, A_NUM} },
// int32 __cvt_lngbool(word32 *, word32 *, int32)
 {ASL_CVT_LNGBOOL, "__cvt_lngbool", FALSE, RE_INT, {A_RPTR, A_RPTR, A_NUM} },
// void __asl_exec_qc_assign(struct st_t *, int32, struct nchglst_t *)
 {ASL_EXEC_QC_ASSIGN, "__asl_exec_qc_assign", TRUE, RE_VOID, 
   {A_RPTR, A_INT, A_RPTR, A_NUM} },
// void __asl_exec_qc_force(struct st_t *, int32, struct nchglst_t *)
 {ASL_EXEC_QC_FORCE, "__asl_exec_qc_force", TRUE, RE_VOID, 
   {A_RPTR, A_INT, A_RPTR, A_NUM} },
// void __asl_exec_qc_wireforce(struct st_t *, struct expr_t *,
// int32, struct nchglst_t *)
 {ASL_EXEC_QC_WIREFORCE, "__asl_exec_qc_wireforce", TRUE, RE_VOID, 
   {A_RPTR, A_NUM, A_RPTR, A_NUM} },
// void __asl_exec_qc_deassign(struct st_t *)
 {ASL_EXEC_QC_DEASSIGN, "__asl_exec_qc_deassign", TRUE, RE_VOID, {A_RPTR} },
// void __asl_exec_qc_wirerelease(struct st_t *, struct nchglst_t *)
 {ASL_EXEC_QC_WIRERELEASE, "__asl_exec_qc_wirerelease", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR, A_NUM} },
// int32 __asl_exec_disable(struct st_t *);
 {ASL_EXEC_DISABLE, "__asl_exec_disable", TRUE, RE_INT, {A_RPTR} },
// void __asl_eval_tranif_ld(struct gate_t *, int32)
 {ASL_EVAL_TRANIF_LD, "__asl_eval_tranif_ld", TRUE, RE_VOID, {A_RPTR, A_INT} },
// void __asl_schd_1pthwirebit(struct net_t *, int32, word32, word32, 
//struct nchglst_t *, void *enterp);
 {ASL_SCHD_1PTHWIREBIT, "__asl_schd_1pthwirebit", TRUE, RE_VOID, 
  {A_RPTR, A_INT, A_INT, A_INT, A_RPTR, A_RPTR} },
// void __asl_schd_1pthwirebit_nomsg(struct net_t *, int32, word32, word32, 
//struct nchglst_t *, void *enterp);
 {ASL_SCHD_1PTHWIREBIT_NOMSG, "__asl_schd_1pthwirebit_nomsg", TRUE, RE_VOID, 
  {A_RPTR, A_INT, A_INT, A_INT, A_RPTR, A_RPTR} },
// void __asl_schd_st_1pthwirebit(struct net_t *, int32, word32, word32,
//struct nchglst_t *, void *enterp)
 {ASL_SCHD_ST_1PTHWIREBIT, "__asl_schd_st_1pthwirebit", TRUE, RE_VOID, 
  {A_RPTR, A_INT, A_INT, A_INT, A_RPTR, A_RPTR} },
// void __asl_schd_scalar_1pthwirebit(struct net_t *, word32, word32, 
//struct nchglst_t, void *);
 {ASL_SCHD_SCALAR_1PTHWIREBIT, "__asl_schd_scalar_1pthwirebit", TRUE, RE_VOID, 
  {A_RPTR, A_INT, A_INT, A_RPTR, A_RPTR} },
// void __asl_schd_st_scalar_1pthwirebit(struct net_t *, word32, word32,
//struct nnchglst_t *, void *);
 {ASL_SCHD_ST_SCALAR_1PTHWIREBIT, "__asl_schd_st_scalar_1pthwirebit", TRUE,
  RE_VOID, {A_RPTR, A_INT, A_INT, A_RPTR, A_RPTR} },
// void __asl_wdel_schd_1wirebit(struct net_t *, int32, word32, word32, int32,
// struct nchglst_t *, void *)
 {ASL_WDEL_SCHD_1WIREBIT, "__asl_wdel_schd_1wirebit", TRUE, RE_VOID, 
  {A_RPTR, A_NUM, A_INT, A_INT, A_RPTR} },
//void __asl_schd_scalar_1wev(struct tev_t *)
 {ASL_SCHD_SCALAR_1WEV, "__asl_schd_scalar_1wev", FALSE, RE_VOID, 
  {A_RPTR}},
//void __asl_schd_1wev(struct tev_t *, word32, word64, int32)
 {ASL_SCHD_1WEV, "__asl_schd_1wev", FALSE, RE_VOID, 
  {A_RPTR, A_NUM}},
#ifdef __CVC32__
//void __asl_reschd_1wev(struct tev_t *, word32, word64)
 {ASL_RESCHD_1WEV, "__asl_reschd_1wev", FALSE, RE_VOID, 
  {A_RPTR, A_INT, A_INT}},
#else
//void __asl_reschd_1wev(struct tev_t *, word64)
 {ASL_RESCHD_1WEV, "__asl_reschd_1wev", FALSE, RE_VOID, 
  {A_RPTR, A_INT}},
#endif
// void __eval_stwire(byte *, word32, int32, int32, byte *)
 {ASL_EVAL_STWIRE, "__eval_stwire", FALSE, RE_VOID, 
  {A_WPTR, A_INT, A_INT, A_INT, A_RPTR} },
// void __asl_eval_wide_wire(word32 *, word32 *, word32 *, word32 *, int32)
 {ASL_EVAL_WIDE_WIRE, "__asl_eval_wide_wire", FALSE, RE_VOID, {A_RWPTR,
  A_RPTR, A_RPTR, A_NUM} },
// void __asl_add_dmpv_chglst_el(struct net_t *)
 {ASL_ADD_DMPV_CHGLST_EL, "__asl_add_dmpv_chglst_el", TRUE, RE_VOID, 
  {A_RPTR} },
// void __asl_add_dmpv_chglst_el_array(struct net_t *, int32)
 {ASL_ADD_DMPV_CHGLST_EL_ARRAY, "__asl_add_dmpv_chglst_el_array", TRUE, 
  RE_VOID, {A_RPTR, A_INT} },
// void __asl_add_dmpp_chglst_el(struct net_t *)
 {ASL_ADD_DMPP_CHGLST_EL, "__asl_add_dmpp_chglst_el", TRUE, RE_VOID, 
  {A_RPTR} },
 /* AIV 07/20/09 - special case duplicate same except no IDP - down port */
// void __asl_add_dmpv_chglst_el_mdprt(struct net_t *)
 {ASL_ADD_DMPV_CHGLST_EL_MDPRT, "__asl_add_dmpv_chglst_el_mdprt", FALSE, 
  RE_VOID, {A_RPTR} },
// void __asl_add_dmpp_chglst_el_mdprt(struct net_t *)
 {ASL_ADD_DMPP_CHGLST_EL_MDPRT, "__asl_add_dmpp_chglst_el_mdprt", FALSE, 
   RE_VOID, {A_RPTR} },
// void *memcpy(void *, const void *, int32)
 {ASL_MEMCPY, "memcpy", FALSE, RE_VOID, {A_WPTR, A_RPTR, A_NUM} },
// void *memset(void *, int32, int32)
 {ASL_MY_MEMSET, "memset", FALSE, RE_VOID, {A_WPTR, A_INT, A_NUM} },
//word32 __comb_1bitsts(word32 wtyp, word32 acc, word32 op)
 {ASL_COMB_1BITSTS, "__comb_1bitsts", FALSE, RE_INT, {A_INT, A_INT, A_INT} },
//void __asl_sched_proc_delay_const(struct_t tev_t *)
 {ASL_SCHED_PROC_DELAY_CONST, "__asl_sched_proc_delay_const", FALSE, RE_VOID, 
   {A_RPTR} },
//void __asl_sched_proc_delay_pnd0(struct tev_t *)
 {ASL_SCHED_PROC_DELAY_PND0, "__asl_sched_proc_delay_pnd0", FALSE, RE_VOID, 
   {A_RPTR} }, 
//void __asl_sched_proc_delay_task_const(struct_t tev_t *)
 {ASL_SCHED_PROC_DELAY_TASK_CONST, "__asl_sched_proc_delay_task_const", FALSE, 
   RE_VOID, {A_RPTR} },
//void __asl_sched_proc_delay_task_pnd0(struct tev_t *)
 {ASL_SCHED_PROC_DELAY_TASK_PND0, "__asl_sched_proc_delay_task_pnd0", FALSE,
   RE_VOID, {A_RPTR} }, 
//word32 *__asl_sched_nbrhs_dctrl(struct st_t *, void *, int32)
 {ASL_SCHED_NBRHS_DCTRL, "__asl_sched_nbrhs_dctrl", TRUE, RE_VOID, {A_RPTR,
  A_RPTR, A_INT} },
//word32 *__asl_sched_nbrhs_dctrl_const(struct tev_t *, int32)
 {ASL_SCHED_NBRHS_DCTRL_CONST, "__asl_sched_nbrhs_dctrl_const", FALSE, RE_PTR,
   {A_RPTR, A_INT} },
//int32 __asl_schd_caev_const(struct tev_t *)
 { ASL_SCHD_CAEV_CONST, "__asl_schd_caev_const", FALSE, RE_VOID, {A_RPTR} },
//int32 __asl_schd_caev_const0(sturct tev_t *)
 { ASL_SCHD_CAEV_CONST0, "__asl_schd_caev_const0", FALSE, RE_VOID, 
  {A_RPTR, A_RPTR} },
//int32 __asl_reschd_caev_const(struct tev_t *)
 { ASL_RESCHD_CAEV_CONST, "__asl_reschd_caev_const", FALSE, RE_VOID, {A_RPTR} },
//int32 __asl_wordcmp(word32 *w1, word32 *w2, int32 wlen) 
 { ASL_WORDCMP, "__asl_wordcmp", FALSE, RE_VOID, {A_RPTR, A_RPTR, A_NUM} },
// void __asl_chk_dce_cbvc(struct net_t *)
 {ASL_CHK_DCE_CBVC, "__asl_chk_dce_cbvc", TRUE, RE_VOID, {A_RPTR} },
//__asl_chk_ld_vpiputv_driver(struct net_t *, word32 *)
 {ASL_CHK_LD_VPIPUTV_DRIVER, "__asl_chk_ld_vpiputv_driver", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR } },  
//__asl_chk_gate_vpi_chg(struct gate_t *)
 {ASL_CHK_GATE_VPI_CHG, "__asl_chk_gate_vpi_chg", TRUE, RE_VOID, {A_RPTR} },
// void __asl_eval_1w_nonstren_wire(word32 *, word32 *, word32, word32)
 {ASL_EVAL_1W_NONSTREN_WIRE, "__asl_eval_1w_nonstren_wire", FALSE, RE_VOID, 
  { A_WPTR, A_INT, A_INT} },
// void __asl_eval_1w_nonstren_wire_and(word32 *, word32 *, word32, word32)
 {ASL_EVAL_1W_NONSTREN_WIRE_AND, "__asl_eval_1w_nonstren_wire_and", FALSE,
   RE_VOID, {A_WPTR, A_INT, A_INT} },
// void __asl_eval_1w_nonstren_wire_or(word32 *, word32 *, word32, word32)
 {ASL_EVAL_1W_NONSTREN_WIRE_OR, "__asl_eval_1w_nonstren_wire_or", FALSE,
   RE_VOID, {A_WPTR, A_INT, A_INT} },
// void __eval_wide_wire_and(word32 *, word32 *, word32 *, word32 *, int32)
 {ASL_EVAL_WIDE_WIRE_AND, "__asl_eval_wide_wire_and", FALSE, RE_VOID, {A_WPTR,
  A_RPTR, A_RPTR, A_NUM} },
// void __eval_wide_wire_or(word32 *, word32 *, word32 *, word32 *, int32)
 {ASL_EVAL_WIDE_WIRE_OR, "__asl_eval_wide_wire_or", FALSE, RE_VOID, {A_WPTR,
  A_RPTR, A_RPTR, A_NUM} },
//void __lpow(word32 *, word32 *, word32 *, int32);
 {ASL_WIDE_POWER, "__lpow", FALSE, RE_VOID, {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
//int32 __sgn_lpow(word32 *, word32 *, word32 *, int32);
 {ASL_WIDE_SGN_POWER, "__sgn_lpow", FALSE, RE_VOID, {A_WPTR, A_RPTR,
  A_RPTR, A_NUM} },
//int32 __asl_sgn_lpow_2state(word32 *, word32 *, word32 *, int32);
 {ASL_WIDE_SGN_POWER_2STATE, "__asl_sgn_lpow_2state", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
 {ASL_REAL_POW_FUNC, "pow", FALSE, RE_VOID, {A_DBLE, A_DBLE} },
//void __asl_bld_nb_nodelay_tev(struct tev_t *)
 {ASL_BLD_NB_NODELAY_TEV, "__asl_bld_nb_nodelay_tev", FALSE, RE_VOID, {A_RPTR}},
//__asl_schd_nb_vardel_rhsconst_dctrl(struct st_t *, void *)
 {ASL_SCHD_NB_VARDEL_RHSCONST_DCTRL, "__asl_schd_nb_vardel_rhsconst_dctrl",
   TRUE, RE_VOID, {A_RPTR, A_RPTR}},
//void __asl_sched_nbrhs_nomem_dctrl_const(struct tev_t *)
 {ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST, "__asl_sched_nbrhs_nomem_dctrl_const",
   FALSE, RE_VOID, {A_RPTR}},
//void __asl_sched_nbrhs_scalar_dctrl(struct st_t *, struct st_t *, word32)
 {ASL_SCHED_NBRHS_SCALAR_DCTRL, "__asl_sched_nbrhs_scalar_dctrl",
   TRUE, RE_VOID, {A_RPTR, A_RPTR, A_INT}},
//void __asl_sched_nbrhs_scalar_dctrl_const(struct tev_t *, word32)
 {ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST,"__asl_sched_nbrhs_scalar_dctrl_const",
   FALSE, RE_VOID, {A_RPTR, A_INT}},
//word32 *__asl_sched_nbrhs_varndx_dctl_const(int32, int32, struct tev_t *)
 {ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST,
   "__asl_sched_nbrhs_varndx_dctrl_const", FALSE, RE_PTR, 
    {A_INT, A_NUM, A_RPTR} },
//word32 *__asl_sched_nbrhs_varndx_dctrl(struct st_t *, int32,
//int32, struct tev_t *)
 {ASL_SCHED_NBRHS_VARNDX_DCTRL, "__asl_sched_nbrhs_varndx_dctrl", TRUE,  
  RE_VOID, {A_RPTR, A_INT, A_NUM, A_RPTR} },
// word32 *extern int32 __asl_sched_nb_pnd0_lhs_varndx(int32, 
//int32, struct tev_t *)
 {ASL_SCHED_NB_PND0_LHS_VARNDX, "__asl_sched_nb_pnd0_lhs_varndx", FALSE,
  RE_PTR, {A_INT, A_NUM, A_RPTR} },
//word32 *__asl_sched_nbrhs_varndx_dctl_const_concat(struct net_t *, int32, 
//int32, struct tev_t *, struct nchlst_t *)
 {ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_CONCAT,
   "__asl_sched_nbrhs_varndx_dctrl_const_concat", FALSE, RE_PTR, 
    {A_RPTR, A_INT, A_NUM, A_RPTR, A_RPTR} },
//word32 *__asl_sched_nbrhs_varndx_dctrl_concat(struct st_t *, struct net_t *,
//int32, int32, struct tev_t *, struct nchglst_t *)
 {ASL_SCHED_NBRHS_VARNDX_DCTRL_CONCAT, "__asl_sched_nbrhs_varndx_dctrl_concat",
   TRUE,  RE_VOID, {A_RPTR, A_RPTR, A_INT, A_NUM, A_RPTR, A_RPTR} },
// word32 *extern int32 __asl_sched_nb_pnd0_lhs_varndx_concat(struct net_t *, 
//int32, int32, struct tev_t *, struct nchglst_t *)
 {ASL_SCHED_NB_PND0_LHS_VARNDX_CONCAT, "__asl_sched_nb_pnd0_lhs_varndx_concat",
  FALSE, RE_PTR, {A_RPTR, A_INT, A_NUM, A_RPTR, A_RPTR} },
//void __asl_rhs_conta_stren(word32 *, int32, int32)
 {ASL_RHS_CONTA_STREN, "__asl_rhs_conta_stren", FALSE, RE_VOID, 
  {A_RPTR, A_NUM, A_NUM} },
// void __asl_sched_scalar_mipd_path(struct net_t *, void *)
 {ASL_SCHED_SCALAR_MIPD_PATH, "__asl_sched_scalar_mipd_path", TRUE, RE_VOID, 
   {A_RPTR, A_RPTR} },
// void __asl_sched_scalar_mipd_16v(struct net_t *, void *)
 {ASL_SCHED_SCALAR_MIPD_16V, "__asl_sched_scalar_mipd_16v", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR} },
// void __asl_sched_scalar_mipd_is16v(struct net_t *, void * 
 {ASL_SCHED_SCALAR_MIPD_IS16V, "__asl_sched_scalar_mipd_is16v", TRUE, RE_VOID,
  {A_RPTR, A_RPTR} },
// void __asl_sched_scalar_mipd_is16v1(struct net_t *, void *)
 {ASL_SCHED_SCALAR_MIPD_IS16V1, "__asl_sched_scalar_mipd_is16v1", TRUE, 
  RE_VOID, {A_RPTR, A_RPTR} },
// void __asl_sched_scalar_mipd_is16v2(struct net_t *, void *)
 {ASL_SCHED_SCALAR_MIPD_IS16V2, "__asl_sched_scalar_mipd_is16v2", TRUE,
  RE_VOID, {A_RPTR, A_RPTR} },
// void __asl_sched_scalar_mipd_is1v(struct tev_t *)
 {ASL_SCHED_SCALAR_MIPD_IS1V, "__asl_sched_scalar_mipd_is1v", TRUE, RE_VOID, 
  {A_RPTR} },
// void __asl_sched_scalar_mipd_pnd0(struct tev_t *)
 {ASL_SCHED_SCALAR_MIPD_PND0, "__asl_sched_scalar_mipd_pnd0", FALSE, RE_VOID, 
  {A_RPTR} },
 /* AIV 08/31/10 - these use __idp must set flag */
// void __asl_sched_vec_mipd_bit(struct net_t *, void *)
 {ASL_SCHED_VEC_MIPD_BIT, "__asl_sched_vec_mipd_bit", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR, A_NUM} },
// void __asl_sched_scalar_mipd_const(struct net_t *)
 {ASL_SCHED_SCALAR_MIPD_CONST, "__asl_sched_scalar_mipd_const", FALSE, RE_VOID, 
  {A_RPTR} },
// extern void __asl_timing_check_record(struct chktchg_t *chkchgp)
 {ASL_TIMING_CHECK_RECORD, "__asl_timing_check_record", TRUE, RE_VOID, 
  {A_RPTR} },
// void __asl_sched_proc_delay_nt(struct st_t *, void *, struct tev_t *)
 {ASL_SCHED_PROC_DELAY_NT, "__asl_sched_proc_delay_nt", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR} },
//void __asl_sched_proc_delay_const_nt(struct tev_t *)
 {ASL_SCHED_PROC_DELAY_CONST_NT, "__asl_sched_proc_delay_const_nt", FALSE,
   RE_VOID, {A_RPTR} },
//void __asl_sched_proc_delay_pnd0_nt(struct tev_t *)
 {ASL_SCHED_PROC_DELAY_PND0_NT, "__asl_sched_proc_delay_pnd0_nt", FALSE, 
  RE_VOID, {A_RPTR} }, 
// extern void __asl_add_static_nchglst_sel(struct nchglst_t *, int32, int32)
 {ASL_ADD_STATIC_NCHG_SEL, "__asl_add_static_nchglst_sel", TRUE, RE_VOID, 
  {A_RPTR, A_INT, A_INT}},
// extern void __asl_process_mipd_nchg_ev(struct net_t *)
 {ASL_PROCESS_MIPD_NCHG, "__asl_process_mipd_nchg_ev", TRUE, RE_VOID, 
  {A_RPTR}},
//extern void __asl_process_mipd_scalar_nchg_ev(struct nchglst_t *nchglp)
 {ASL_PROCESS_SCAL_MIPD_NCHG, "__asl_process_mipd_scalar_nchg_ev", FALSE,
  RE_VOID, {A_RPTR}},
//extern int32 __asl_update_tran_harddrvs(struct net_t *)
 {ASL_UPDATE_TRAN_HARDDRVS, "__asl_update_tran_harddrvs", TRUE,
   RE_INT, {A_RPTR}},
// void __asl_eval_htran_stwire_1bit(struct net_t *, int32 bi)
 {ASL_EVAL_HTRAN_STWIRE_1BIT, "__asl_eval_htran_stwire_1bit", TRUE, RE_VOID, 
   {A_RPTR, A_NUM} },
// void __asl_eval_htran_wire_1bit(struct net_t *, int32 bi)
 {ASL_EVAL_HTRAN_WIRE_1BIT, "__asl_eval_htran_wire_1bit", TRUE, RE_VOID, 
   {A_RPTR, A_NUM} },
// void __asl_eval_htran_stwire_1bit_nchg(struct net_t *, struct nchglst_t *, 
//int32 bi)
 {ASL_EVAL_HTRAN_STWIRE_1BIT_NCHG, "__asl_eval_htran_stwire_1bit_nchg", 
   TRUE, RE_VOID, {A_RPTR, A_RPTR, A_NUM} },
// void __asl_eval_htran_wire_1bit_nchg(struct net_t *, struct nchglst_t *, 
//int32 bi)
 {ASL_EVAL_HTRAN_WIRE_1BIT_NCHG, "__asl_eval_htran_wire_1bit_nchg", TRUE, 
  RE_VOID, {A_RPTR, A_RPTR, A_NUM} },

// int32 __asl_eval_tran_bidchan_1bit(int32)
 {ASL_EVAL_TRAN_BIDCHAN_1BIT , "__asl_eval_tran_bidchan_1bit", TRUE, RE_INT, 
   {A_NUM} },
// int32 __asl_eval_tran_scalar_bidchan_1bit(int32)
 {ASL_EVAL_TRAN_SCALAR_BIDCHAN_1BIT , "__asl_eval_tran_scalar_bidchan_1bit", 
   TRUE, RE_INT, {A_NUM} },
// int32 __asl_eval_tran_stbidchan_1bit(int32)
 {ASL_EVAL_TRAN_STBIDCHAN_1BIT , "__asl_eval_tran_stbidchan_1bit", TRUE,
   RE_INT, {A_NUM} },
// void __asl_eval_tran_bidchan_1bit_assign(int32)
 {ASL_EVAL_TRAN_BIDCHAN_1BIT_ASSIGN, "__asl_eval_tran_bidchan_1bit_assign", 
   TRUE, RE_INT, {A_NUM} },
// void __asl_eval_tran_stbidchan_1bit_scalar(int32)
 {ASL_EVAL_TRAN_STBIDCHAN_1BIT_ASSIGN , 
   "__asl_eval_tran_stbidchan_1bit_assign", TRUE, RE_INT, {A_NUM} },
// void __asl_eval_tran_bidchan_vectored(int32)
 {ASL_EVAL_TRAN_BIDCHAN_VECTORED_ASSIGN, 
   "__asl_eval_tran_bidchan_vectored_assign", TRUE, RE_INT, {A_RPTR} },
// void __asl_eval_tran_stbidchan_vectored(int32)
 {ASL_EVAL_TRAN_STBIDCHAN_VECTORED_ASSIGN, 
   "__asl_eval_tran_stbidchan_vectored_assign", TRUE, RE_INT, {A_RPTR} },
// void __asl_qc_active(struct net_t *, int32)
 {ASL_QC_ACTIVE , "__asl_qc_active", TRUE, RE_VOID, {A_RPTR, A_NUM} },
// void __asl_exec_qc_tran_wireforce(struct st_t *, struct expr_t *,
// int32, struct nchglst_t *)
 {ASL_EXEC_QC_TRAN_WIREFORCE, "__asl_exec_qc_tran_wireforce", TRUE, RE_VOID, 
   {A_RPTR, A_NUM, A_RPTR, A_NUM} },
// void __asl_exec_qc_tran_wirerelease(struct st_t *, struct nchglst_t *)
 {ASL_EXEC_QC_TRAN_WIRERELEASE, "__asl_exec_qc_tran_wirerelease", TRUE, 
   RE_VOID, {A_RPTR, A_RPTR, A_NUM} },
// void __asl_exec_qc_deassign_force(struct expr_t *)
 /* AIV 04/11/12 - this needs to set __idp for XMR cases */
 {ASL_EXEC_QC_DEASSIGN_FORCE, "__asl_exec_qc_deassign_force", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR, A_NUM} },
// void __asl_assign_qcaf_regform(struct dcevnt_t *, struct nchglst_t *,  int32)
 {ASL_ASSIGN_QCAF_REGFORM, "__asl_assign_qcaf_regform", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR, A_NUM} },
// void __asl_assign_scalar_qcaf_regform(struct dcevnt_t *, 
//struct nchglst_t *,  int32)
 {ASL_ASSIGN_SCALAR_QCAF, "__asl_assign_scalar_qcaf", TRUE, RE_VOID, 
  {A_RPTR, A_RPTR, A_NUM} },
//int32 *__asl_tran_addr(struct net_t *np)
 {ASL_TRAN_ADDR, "__asl_tran_addr", TRUE, RE_PTR, {A_RPTR} },
//int32 *__asl_stren_schd_bidpthddrvrs(struct net_t *np, byte *drv_sbp, 
//byte *trnva_sbp, int32, struct tev_t *)
 {ASL_STREN_SCHD_BIDPTHDRVRS, "__asl_stren_schd_bidpthdrvrs", TRUE, RE_INT, 
   {A_RPTR, A_RPTR, A_RPTR, A_NUM, A_RPTR} },
//int32 *__asl_schd_bidpthddrvrs(struct net_t *np, byte *drv_sbp, 
//byte *trnva_sbp, int32, struct tev_t *)
 {ASL_SCHD_BIDPTHDRVRS, "__asl_schd_bidpthdrvrs", TRUE, RE_INT, 
   {A_RPTR, A_RPTR, A_RPTR, A_NUM, A_RPTR} },
//int32 *__asl_schd_scalar_bidpthddrvrs(struct net_t *np, byte *drv_sbp, 
//byte *trnva_sbp, int32, struct tev_t *)
 {ASL_SCHD_SCALAR_BIDPTHDRVRS, "__asl_schd_scalar_bidpthdrvrs", TRUE,
  RE_INT, {A_RPTR, A_RPTR, A_RPTR, A_NUM, A_RPTR} },
//int32 *__asl_store_bidpthddrvrs(struct net_t *np, byte *, int32)
 {ASL_STORE_BIDPTHDRVRS, "__asl_store_bidpthdrvrs", TRUE, RE_INT, 
   {A_RPTR, A_RPTR, A_NUM} },
//int32 __asl_trpath_scalar_store(struct net_t *, word32)
 {ASL_TRPATH_SCALAR_STORE, "__asl_trpath_scalar_store", TRUE, RE_INT, 
   {A_RPTR, A_INT} },
//int32 __asl_trpath_store(struct net_t *, word32, int32)
 {ASL_TRPATH_STORE, "__asl_trpath_store", FALSE, RE_INT, 
  {A_RPTR, A_INT, A_NUM} },
//int32 __asl_immed_eval_trifchan(gate_t *)
 {ASL_IMMED_EVAL_TRIFCHAN, "__asl_immed_eval_trifchan", TRUE, RE_VOID, 
  {A_RPTR} },
// void __asl_wdel_trireg_sched_hiz(struct net_t *, byte *, word32, int32, 
//struct tev_t *)
 {ASL_WDEL_TRIREG_SCHED_HIZ, "__asl_wdel_trireg_sched_hiz", TRUE, RE_VOID, 
   {A_RPTR, A_WPTR, A_INT, A_NUM, A_RPTR} },
// word32 __asl_udp_wide_adjstate(word32 *, int32)
 {ASL_UDP_WIDE_ADJSTATE, "__asl_udp_wide_adjstate", FALSE, RE_INT, 
   {A_RPTR, A_INT} },
// int32 __asl_force_active(struct net_t *, int32)
 {ASL_FORCE_ACTIVE, "__asl_force_active", TRUE, RE_INT, {A_RPTR, A_INT} },
// word64 __asl_get_del_1x(union del_u)
 {ASL_GET_DEL_1X, "__asl_get_del_1x", TRUE, RE_DBLE, {A_RPTR}},
// word64 __asl_get_del_1x(union del_u)
 {ASL_GET_DEL_4X, "__asl_get_del_4x", TRUE, RE_DBLE, {A_RPTR}},
//sword32 __asl_random_with_seed(sword32 seed)
 {ASL_RANDOM_WITH_SEED, "__asl_random_with_seed", FALSE, RE_INT, {A_RPTR}},
//sword32 __asl_random(void)
 {ASL_RANDOM, "__asl_random", FALSE, RE_INT, },
// void __asl_rhs_psel_wide(word32 *, word32 *, int32, int32)
 {ASL_RHS_PSEL_WIDE, "__asl_rhs_psel_wide", FALSE, RE_VOID, 
   {A_WPTR, A_WPTR, A_RPTR, A_RPTR, A_INT, A_INT} },
// void __asl_rhs_psel_wide_2state(word32 *, word32 *, int32, int32)
 {ASL_RHS_PSEL_WIDE_2STATE, "__asl_rhs_psel_wide_2state", FALSE, RE_VOID, 
   {A_WPTR, A_RPTR, A_INT, A_INT} },
// word32 __asl_rhs_psel(word32 *, int32, int32)
 {ASL_RHS_PSEL, "__asl_rhs_psel", FALSE, RE_INT, 
  {A_RPTR, A_RPTR, A_INT, A_INT} },
// word32 __asl_rhs_psel_2state(word32 *, int32, int32)
 {ASL_RHS_PSEL_2STATE, "__asl_rhs_psel_2state", FALSE, RE_INT, 
  {A_RPTR, A_INT, A_INT} },
// word32 __asl_rhs_st_psel(word32 *, int32, int32)
 {ASL_RHS_ST_PSEL, "__asl_rhs_st_psel", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_INT} },
//int32 __asl_jmp_eq_wide_var(word32 *op1p, word32 *op2p, int32 nbits)
 {ASL_JMP_EQ_WIDE_VARMASK, "__asl_jmp_eq_wide_varmask", FALSE, RE_INT,
  {A_RPTR, A_RPTR, A_INT} },
// int32 __asl_wide_cmp_eq(word32 *, word32 *, int32 opwid)
 {ASL_WIDE_CMP_EQ, "__asl_wide_cmp_eq", FALSE, RE_INT, 
  {A_RPTR, A_RPTR, A_NUM} },
// int32 __asl_wide_cmp_neq(word32 *, word32 *, int32 opwid)
 {ASL_WIDE_CMP_NEQ, "__asl_wide_cmp_neq", FALSE, RE_INT, 
  {A_RPTR, A_RPTR, A_NUM} },
//void __asl_exec_display(struct st_t *)
 {ASL_EXEC_DISPLAY, "__asl_exec_display", TRUE, RE_VOID, {A_RPTR} },
//AIV FIXME - new port bsel types are wrong - may inline some of these
//extern void __asl_mdprt_bsel(struct expr_t *, word32 *, word32)
 {ASL_MDPRT_BSEL, "__asl_mdprt_bsel", FALSE, RE_VOID, {A_INT, A_INT, A_INT}},
//extern void __asl_mdprt_bsel_nchg(struct expr_t *, word32 *, word32, 
//struct nchglst_t *)
 {ASL_MDPRT_BSEL_NCHG, "__asl_mdprt_bsel_nchg", FALSE, RE_VOID, {A_INT, 
   A_INT, A_INT, A_RPTR}},
//extern void __asl_mdprt_bsel(struct expr_t *, word32 *, word32)
 {ASL_MDPRT_BSEL_1W, "__asl_mdprt_bsel_1w", FALSE, RE_VOID, 
  {A_INT, A_INT, A_INT}},
//extern void __asl_mdprt_bsel_nchg(struct expr_t *, word32 *, word32, 
//struct nchglst_t *)
 {ASL_MDPRT_BSEL_NCHG_1W, "__asl_mdprt_bsel_nchg_1w", FALSE, RE_VOID, 
   {A_INT, A_INT, A_INT, A_RPTR}},
//extern void __asl_mdprt_bsel_dmpv(struct expr_t *up_lhsx, word32 *lhs_ap,
// word32 new_val)
 {ASL_MDPRT_BSEL_DMPV, "__asl_mdprt_bsel_dmpv", FALSE, RE_VOID, 
   {A_INT, A_INT, A_INT}},
//extern void __asl_mdprt_bsel_nchg_dmpv(struct expr_t *up_lhsx, word32 *lhs_ap,
// word32 new_val, struct nchglst_t *nchglp)
 {ASL_MDPRT_BSEL_NCHG_DMPV, "__asl_mdprt_bsel_nchg_dmpv", FALSE, RE_VOID, 
   {A_INT, A_INT, A_INT, A_RPTR}},
//extern void __asl_mdprt_bsel_1w_dmpv(int32 bi, word32 *lhs_ap, word32 new_val,
// struct net_t *up_np)
 {ASL_MDPRT_BSEL_1W_DMPV, "__asl_mdprt_bsel_1w_dmpv", FALSE, RE_VOID, 
  {A_INT, A_INT, A_INT, A_RPTR}},
//extern void __asl_mdprt_bsel_nchg_1w_dmpv(int32 bi, word32 *lhs_ap, 
// word32 new_val, struct nchglst_t *nchglp, struct net_t *up_np)
 {ASL_MDPRT_BSEL_NCHG_1W_DMPV, "__asl_mdprt_bsel_nchg_1w_dmpv", FALSE, RE_VOID, 
   {A_INT, A_INT, A_INT, A_RPTR, A_RPTR}},
//extern void __asl_mdprt_bsel_dmpp(struct expr_t *up_lhsx, word32 *lhs_ap,
// word32 new_val)
 {ASL_MDPRT_BSEL_DMPP, "__asl_mdprt_bsel_dmpp", FALSE, RE_VOID, 
   {A_INT, A_INT, A_INT}},
//extern void __asl_mdprt_bsel_nchg_dmpp(struct expr_t *up_lhsx, word32 *lhs_ap,
// word32 new_val, struct nchglst_t *nchglp)
 {ASL_MDPRT_BSEL_NCHG_DMPP, "__asl_mdprt_bsel_nchg_dmpp", FALSE, RE_VOID, 
   {A_INT, A_INT, A_INT, A_RPTR}},
//extern void __asl_mdprt_bsel_1w_dmpp(int32 bi, word32 *lhs_ap, word32 new_val,
// struct net_t *up_np)
 {ASL_MDPRT_BSEL_1W_DMPP, "__asl_mdprt_bsel_1w_dmpp", FALSE, RE_VOID, 
  {A_INT, A_INT, A_INT, A_RPTR}},
//extern void __asl_mdprt_bsel_nchg_1w_dmpp(int32 bi, word32 *lhs_ap, 
// word32 new_val, struct nchglst_t *nchglp, struct net_t *up_np)
 {ASL_MDPRT_BSEL_NCHG_1W_DMPP, "__asl_mdprt_bsel_nchg_1w_dmpp", FALSE, RE_VOID, 
   {A_INT, A_INT, A_INT, A_RPTR, A_RPTR}},
//word32 *__asl_sched_nbrhs_dctrl_const_t(struct tev_t *, int32)
 {ASL_SCHED_NBRHS_DCTRL_CONST_T, "__asl_sched_nbrhs_dctrl_const_t", FALSE, 
   RE_PTR, {A_RPTR, A_INT} },
//void __asl_sched_nbrhs_nomem_dctrl_const_t(struct tev_t *)
 {ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST_T, "__asl_sched_nbrhs_nomem_dctrl_const_t",
   FALSE, RE_VOID, {A_RPTR}},
//void __asl_sched_nbrhs_scalar_dctrl_const_t(struct tev_t *, word32)
 {ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST_T,"__asl_sched_nbrhs_scalar_dctrl_const_t",
   FALSE, RE_VOID, {A_RPTR, A_INT}},
//word32 *__asl_sched_nbrhs_varndx_dctl_const_t(int32, int32, struct tev_t *)
 {ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_T,
   "__asl_sched_nbrhs_varndx_dctrl_const_t", FALSE, RE_PTR, 
    {A_INT, A_NUM, A_RPTR} },
//word32 *__asl_sched_nbrhs_varndx_dctl_const_concat_t(struct net_t *, int32, 
//int32, struct tev_t *, struct nchlst_t *)
 {ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_CONCAT_T,
   "__asl_sched_nbrhs_varndx_dctrl_const_concat_t", FALSE, RE_PTR, 
    {A_RPTR, A_INT, A_NUM, A_RPTR, A_RPTR} },
//void __asl_sched_nbrhs_scalar_dctrl_const_last(struct tev_t *, word32)
 {ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST_LAST,
   "__asl_sched_nbrhs_scalar_dctrl_const_last",
   FALSE, RE_VOID, {A_RPTR, A_INT}},
//word32 *__asl_sched_nbrhs_dctrl_const_last(struct tev_t *, int32)
 {ASL_SCHED_NBRHS_DCTRL_CONST_LAST, "__asl_sched_nbrhs_dctrl_const_last", 
   FALSE, RE_PTR, {A_RPTR, A_INT} },
//void __asl_sched_nbrhs_nomem_dctrl_const_last(struct tev_t *)
 {ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST_LAST, 
   "__asl_sched_nbrhs_nomem_dctrl_const_last", FALSE, RE_VOID, {A_RPTR}},
//t_midat __asl_new_auto_idp_area(t_midat *)
 {ASL_NEW_AUTO_IDP_AREA, "__asl_new_auto_idp_area", FALSE, RE_PTR, {A_RPTR}},
//void __asl_cp_auto_idp_area_func(t_midat *, t_midat *)
 {ASL_CP_AUTO_IDP_AREA_FUNC, "__asl_cp_auto_idp_area_func", FALSE, RE_VOID, 
  {A_RPTR, A_RPTR}},
//void __asl_4state_to_2state(t_midat *, t_midat *, int32)
 {ASL_4STATE_TO_2STATE_WIDE, "__asl_4state_to_2state_wide", FALSE, RE_VOID, 
  {A_RPTR, A_RPTR, A_NUM}},
// void __asl_sgn_xtnd_widen_2state(word32 *, word32 *, int32, int32)
 {ASL_SGN_XTND_WIDEN_2STATE, "__asl_sgn_xtnd_widen_2state", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_NUM, A_NUM} },
 /* AIV 09/13/10 - added builtin clib math routines */
 {ASL_COS, "cos", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_SIN, "sin", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_TAN, "tan", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_CEIL, "ceil", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_FLOOR, "floor", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_ACOS, "acos", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_ASIN, "asin", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_ATAN, "atan", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_COSH, "cosh", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_SINH, "sinh", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_TANH, "tanh", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_ACOSH, "acosh", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_ASINH, "asinh", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_ATANH, "atanh", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_LN, "log", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_LOG10, "log10", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_ABS, "fabs", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_SQRT, "sqrt", FALSE, RE_DBLE, {A_DBLE} },
 {ASL_EXP, "exp", FALSE, RE_DBLE, {A_DBLE} },
// void __add_togglelst_el(struct net_t *)
 {ASL_ADD_TOGGLELST_EL, "__add_togglelst_el", TRUE, 
   RE_VOID, {A_RPTR} },
// void __asl_add_togglelst_el_port(struct net_t *)
 {ASL_ADD_TOGGLELST_EL_PORT, "__asl_add_togglelst_el_port", TRUE, 
   RE_VOID, {A_RPTR} },
 {ASL_ST_STRING_CONST, "__asl_st_string_const", TRUE, RE_VOID, {A_RPTR, 
   A_RPTR, A_INT} },
 {ASL_ST_STRING_VAR, "__asl_st_string_var", TRUE, RE_VOID, {A_RPTR, 
   A_RPTR} },
 {ASL_ST_STRING_RHSX, "__asl_st_string_rhsx", TRUE, RE_VOID, {A_RPTR, 
   A_RPTR} },
 {ASL_STRING_BINOP, "__asl_string_binop", TRUE, RE_INT, {A_RPTR} },
 {ASL_ST_STRING_BYTE, "__asl_st_string_byte", TRUE, RE_VOID, 
   {A_RPTR, A_INT, A_RPTR} },
 {ASL_ST_STRING_ARRAY_CONST, "__asl_st_string_array_const", TRUE, RE_VOID, 
   {A_RPTR, A_INT, A_RPTR, A_INT} },
 {ASL_ST_STRING_ARRAY_VAR, "__asl_st_string_array_var", TRUE, RE_VOID, 
   {A_RPTR, A_RPTR, A_INT} },
 {ASL_ST_STRING_ARRAY_RHSX, "__asl_st_string_array_rhsx", TRUE, RE_VOID, 
   {A_RPTR, A_RPTR, A_INT} },
 {ASL_GET_STRING_BYTE, "__asl_get_string_byte", TRUE, RE_INT, 
   {A_RPTR, A_INT} },
 {ASL_SV_DPI_STRING, "__asl_sv_dpi_string", TRUE, RE_INT, {A_RPTR} },
 {ASL_SV_DPI_STRING_STORE, "__asl_sv_dpi_string_store", TRUE, RE_VOID, 
   {A_RPTR, A_RPTR} },
//word32 *__asl_sched_nbrhs_varndx_dctl_sel_const(int32, int32, struct tev_t *, int32)
 {ASL_SCHED_NBRHS_VARNDX_DCTRL_SEL_CONST,
   "__asl_sched_nbrhs_varndx_dctrl_sel_const", FALSE, RE_PTR, 
    {A_INT, A_NUM, A_RPTR, A_INT} },
//word32 *__asl_sched_nbrhs_varndx_sel_dctrl(struct st_t *, int32,
//int32, struct tev_t *, int32)
 {ASL_SCHED_NBRHS_VARNDX_SEL_DCTRL, "__asl_sched_nbrhs_varndx_sel_dctrl", TRUE,
   RE_VOID, {A_RPTR, A_INT, A_NUM, A_RPTR, A_INT} },
// word32 *extern int32 __asl_sched_nb_pnd0_lhs_varndx_sel(int32, 
//int32, struct tev_t *, int32)
 {ASL_SCHED_NB_PND0_LHS_VARNDX_SEL, "__asl_sched_nb_pnd0_lhs_varndx_sel", FALSE,
  RE_PTR, {A_INT, A_NUM, A_RPTR, A_INT} },
//word32 *__asl_sched_nbrhs_varndx_dctl_const_sel_t(int32, int32, 
// struct tev_t *, int32)
 {ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST_SEL_T,
   "__asl_sched_nbrhs_varndx_dctrl_const_sel_t", FALSE, RE_PTR, 
    {A_INT, A_NUM, A_RPTR, A_INT} },
// void __asl_misc_terr(void)
 {ASL_MISC_TERR, "__asl_misc_terr", FALSE, RE_VOID, },
 {ASL_ASSIGN_QCAF_REGFORM_CONCAT, 
   "__asl_assign_qcaf_regform_concat", TRUE, RE_VOID, {A_RPTR} },
 {ASL_ASSIGN_QCAF_CONCAT, 
   "__asl_assign_qcaf_concat", TRUE, RE_VOID, {A_RPTR} },
//extern void __asl_real_div0_warning(struct st_t *)
 {ASL_REAL_DIV0_WARNING, 
   "__asl_real_div0_warning", FALSE, RE_VOID, {A_RPTR} },
//extern void __asl_real_qcol_warning(struct st_t *)
 {ASL_REAL_QCOL_WARNING, 
   "__asl_real_qcol_warning", FALSE, RE_VOID, {A_RPTR} },
// void *__asl_exec_sysfunc(struct expr_t *, struct st_t *)
 {ASL_EXEC_SYSFUNC_STMTLOC, "__asl_exec_sysfunc_stmtloc", TRUE, RE_PTR, 
  {A_RPTR, A_RPTR} },
 /* AIV 03/02/12 - added concat versions to not load the expressions for */
 /* regular id forces */
// void __asl_exec_qc_tran_wireforce_concat(struct st_t *, struct expr_t *,
// int32, struct nchglst_t *)
 {ASL_EXEC_QC_TRAN_WIREFORCE_CONCAT, "__asl_exec_qc_tran_wireforce_concat", 
   TRUE, RE_VOID, {A_RPTR, A_RPTR, A_NUM, A_RPTR, A_NUM} },
// void __asl_exec_qc_tran_wirerelease_concat(struct st_t *, struct nchglst_t *)
 {ASL_EXEC_QC_TRAN_WIRERELEASE_CONCAT, "__asl_exec_qc_tran_wirerelease_concat",
   TRUE, RE_VOID, {A_RPTR, A_RPTR, A_NUM} },
// void __asl_exec_qc_wireforce_concat(struct st_t *, struct expr_t *,
// int32, struct nchglst_t *)
 {ASL_EXEC_QC_WIREFORCE_CONCAT, "__asl_exec_qc_wireforce_concat", TRUE, 
   RE_VOID, {A_RPTR, A_RPTR, A_NUM, A_RPTR, A_NUM} },
// void __asl_exec_qc_wirerelease_concat(struct st_t *, struct nchglst_t *)
 {ASL_EXEC_QC_WIRERELEASE_CONCAT, "__asl_exec_qc_wirerelease_concat", TRUE, 
   RE_VOID, {A_RPTR, A_RPTR, A_NUM} },
// void __asl_exec_qc_assign_concat(struct st_t *, int32, struct nchglst_t *)
 {ASL_EXEC_QC_ASSIGN_CONCAT, "__asl_exec_qc_assign_concat", TRUE, RE_VOID, 
   {A_RPTR, A_INT, A_RPTR, A_NUM, A_RPTR} },
// void __asl_exec_qc_force_concat(struct st_t *, int32, struct nchglst_t *)
 {ASL_EXEC_QC_FORCE_CONCAT, "__asl_exec_qc_force_concat", TRUE, RE_VOID, 
   {A_RPTR, A_INT, A_RPTR, A_NUM, A_RPTR} },
// void __asl_exec_qc_deassign_force(struct expr_t *)
 /* AIV 04/11/12 - this needs to set __idp for XMR cases */
 {ASL_EXEC_QC_DEASSIGN_FORCE_CONCAT, "__asl_exec_qc_deassign_force_concat", 
  TRUE, RE_VOID, {A_RPTR, A_RPTR, A_NUM} },
// void __asl_exec_qc_deassign_concat(struct expr_t *)
 {ASL_EXEC_QC_DEASSIGN_CONCAT, "__asl_exec_qc_deassign_concat", TRUE, RE_VOID, 
  {A_RPTR} },
#ifdef __XPROP__
// void __asl_wid_bin_bitor_x(word32 *, word32 *, word32 *, int32)
 {ASL_WID_BIN_BITOR_X, "__asl_wid_bin_bitor_x", FALSE, RE_VOID, 
  {A_WPTR, A_RPTR, A_RPTR, A_NUM} },
// int32 __asl_wid_un_redor_x(word32 *, word32 *, int32)
 {ASL_WID_UN_REDOR_X, "__asl_wid_un_redor_x", FALSE, RE_INT, 
  {A_WPTR, A_RPTR, A_NUM} },
 {ASL_GET_XPROP_ACCUM, 
   "__asl_get_xprop_accum", FALSE, RE_VOID, {A_RPTR} },
 {ASL_SET_XPROP_ACCUM_INIT, 
   "__asl_set_xprop_accum_init", FALSE, RE_VOID, {A_RPTR, A_INT, A_INT} },
 {ASL_SET_XPROP_ACCUM_INIT_WIDE, 
   "__asl_set_xprop_accum_init_wide", FALSE, RE_VOID, {A_RPTR, A_RPTR} },
 {ASL_PER_BIT_XPROP_ACCUM, 
   "__asl_per_bit_xprop_accum", TRUE, RE_INT, {A_RPTR, A_NUM, A_RPTR} },
 {ASL_STMT_ASSIGN_TO_ACCUM_WIDE, 
   "__asl_stmt_assign_to_accum_wide", TRUE, RE_VOID, 
    {A_RPTR, A_RPTR, A_RPTR, A_RPTR} },
 {ASL_STMT_ASSIGN_TO_ACCUM_1W, 
   "__asl_stmt_assign_to_accum_1w", TRUE, RE_VOID, 
   {A_RPTR, A_RPTR, A_INT, A_INT} },
 {ASL_SET_XPROP_ACCUM_BLOCK_CASE, 
   "__asl_set_xprop_accum_block_case", FALSE, RE_VOID, {A_RPTR} },
 {ASL_SET_RESTORE_XPROP_ACCUM_BLOCK, 
   "__asl_set_restore_xprop_accum_block", TRUE, RE_VOID, 
   {A_RPTR, A_INT} },
 {ASL_SET_RESTORE_XPROP_ACCUM_BLOCK_NODEFAULT, 
   "__asl_set_restore_xprop_accum_block_nodefault", TRUE, RE_VOID, 
   {A_RPTR, A_INT, A_INT} },
 /* AIV 03/22/12 - these need to set __idp for xedge net inum setting */
 {ASL_TRACE_XPROP_WRITE, 
   "__asl_trace_xprop_write", TRUE, RE_VOID, {A_RPTR, A_INT, A_INT, A_NUM} },
 {ASL_TRACE_XPROP_WRITE_WIDE, 
   "__asl_trace_xprop_write_wide", TRUE, RE_VOID, {A_RPTR, A_RPTR, A_RPTR, 
    A_NUM} },
 {ASL_POPCOUNT_1W, 
   "__popcountdi2", FALSE, RE_INT, {A_INT} },
 {ASL_POPCOUNT_WIDE, 
   "__asl_popcount_wide", FALSE, RE_INT, {A_RPTR, A_NUM} },
 {ASL_XPROP_CHECK_CASE_NET_SET,
   "__asl_xprop_check_case_net_set", FALSE, RE_VOID, {A_RPTR, A_INT} },
// void __asl_trigger_ectrl_xprop(struct tev_t *, void *)
 {ASL_TRIGGER_ECTRL_XPROP, "__asl_trigger_ectrl_xprop", FALSE, RE_VOID, 
   {A_INT, A_INT} },
// void __asl_has_xedge_wide(word32 *, word32 *, int)
 {ASL_HAS_XEDGE_WIDE, "__asl_has_xedge_wide", FALSE, RE_INT, 
   {A_RPTR, A_RPTR, A_NUM} },
// void __asl_has_xedge_wide_st(word32 *, word32 *, int)
 {ASL_HAS_XEDGE_WIDE_ST, "__asl_has_xedge_wide_st", FALSE, RE_INT, 
   {A_RPTR, A_RPTR, A_NUM} },
 {ASL_XPROP_ACCUM_TO_SELF,
   "__asl_xprop_accum_to_self", FALSE, RE_VOID, {A_RPTR, A_INT, A_INT} },
 {ASL_XPROP_ACCUM_TO_SELF_WIDE, 
   "__asl_xprop_accum_to_self_wide", FALSE, RE_VOID, {A_RPTR, A_RPTR} },
 {ASL_XPROP_XEDGE_NET, 
   "__asl_xprop_xedge_net", TRUE, RE_INT, {A_RPTR} },
 {ASL_XPROP_SET_XEDGE_NET, 
   "__asl_xprop_set_xedge_net", TRUE, RE_PTR, {A_RPTR, A_RPTR, A_INT} },
 {ASL_SET_RESTORE_XPROP_ACCUM_TOSELF, 
   "__asl_set_restore_xprop_accum_toself", TRUE, RE_VOID, {A_RPTR} },
 {ASL_SET_XPROP_ACCUM_BLOCK_IF, 
   "__asl_set_xprop_accum_block_if", FALSE, RE_VOID, {A_RPTR} },
 {ASL_STMT_ASSIGN_TO_ACCUM_1W_IF_ID, 
   "__asl_stmt_assign_to_accum_1w_if_id", FALSE, RE_VOID, 
    {A_RPTR, A_RPTR, A_INT, A_INT} },
 {ASL_STMT_ASSIGN_TO_ACCUM_1W_CASE_ID, 
   "__asl_stmt_assign_to_accum_1w_case_id", FALSE, RE_VOID, 
    {A_RPTR, A_RPTR, A_INT, A_INT} },
 {ASL_STMT_ASSIGN_TO_ACCUM_WIDE_IF_ID, 
   "__asl_stmt_assign_to_accum_wide_if_id", FALSE, RE_VOID, 
    {A_RPTR, A_RPTR, A_RPTR, A_RPTR} },
 {ASL_STMT_ASSIGN_TO_ACCUM_WIDE_CASE_ID, 
   "__asl_stmt_assign_to_accum_wide_case_id", FALSE, RE_VOID, 
    {A_RPTR, A_RPTR, A_RPTR, A_RPTR} },
#endif
 {ASL_POP_XSTK, "__asl_pop_xstk", FALSE, RE_VOID, {A_NUM}},
//printf - for debugging
 {ASL_BBLK_DBG_MSG, "printf", FALSE, RE_VOID, {A_RPTR, A_NUM} }
};

#define ASLNUM (sizeof(__aslinfo) / sizeof(struct asl_info_t))

/*
 * AIV 01/31/12 - setup asl routine map to index so __to_aslinfo_rec does
 * not have to do a linear search of the table every time it is called
 */
extern void __setup_aslinfo_map(void)
{
 int32 asli, rout_num;

 /* get the max value */
 __max_asl_rout_num = 0;
 for (asli = 0; asli < ASLNUM; asli++)
  {
   rout_num = __aslinfo[asli].asl_rout_num;
   if (rout_num > __max_asl_rout_num) 
    {
     __max_asl_rout_num = rout_num;
    }
  }
 /* alloc the map */
 __max_asl_rout_num++;
 __asl_info_map = (int32 *) __my_malloc(__max_asl_rout_num*sizeof(int32));

 /* init to zero */
 for (asli = 0; asli < __max_asl_rout_num; asli++)
  {
   __asl_info_map[asli] = -1;
  }

 /* set the mapped values */
 for (asli = 0; asli < ASLNUM; asli++)
  {
   rout_num = __aslinfo[asli].asl_rout_num;
   __asl_info_map[rout_num] = asli;
  }
}

/*
 * get vm pre lowering insn record from number
 */
extern struct asl_info_t *__to_aslinfo_rec(int32 asl_rout_num)
{
 int32 ndx;

 /* AIV 01/31/12 - changed this to just use an index map */
 /* DBG remove -- */
 ndx = __asl_info_map[asl_rout_num];
 if (ndx == -1 || ndx > __max_asl_rout_num) __misc_terr(__FILE__, __LINE__);
 /* --- */
 return(&(__aslinfo[ndx]));
}

/*
 * routine to get asl wrapper routine virtual insn return width in words
 *
 * every wide is passed the width for the particular insn as a cint or
 * width is fixed and known - part selects need ofset and size to get width
 */
extern int32 __get_asl_insn_retsiz(struct insn_t *ip, int32 *opand_bytsiz)
{
 int32 bitlen, wlen, bytlen, bi1, bi2;
 struct asl_def_t *aslap;
 struct asl_info_t *aslp; 

 /* DBG remove -- */
 if (ip->opcod != I_CALL_ASLPROC && ip->opcod != I_CALL_ASLFUNC)
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 aslp = __to_aslinfo_rec(ip->idst.disp);
 /* this is really the nbytes field when it is used */
 *opand_bytsiz = WRDBYTES; 
 switch (ip->idst.disp) {
  case ASL_GET_UPREL_IDP:
  case ASL_GET_DOWNREL_IDP: 
  case ASL_ARM_NB_ECTRL:
  case ASL_ARM_NB_VARNDX_ECTRL:
  case ASL_REG_QCAF_INHIBIT:
  case ASL_BSEL_WIRFRC_INHIBIT:
  case ASL_MOVSB_FR_SCALSTAD:
  case ASL_EXEC_SYSFUNC:
  case ASL_REPCNT_JMP:
  case ASL_SCHED_NB_PND0_LHS_VARNDX:
  case ASL_SCHED_NBRHS_VARNDX_DCTRL:
  case ASL_SCHED_NBRHS_VARNDX_DCTRL_CONST:
  case ASL_UPREL_TARG_TO_REF:
  case ASL_DOWNREL_TARG_TO_REF:
  case ASL_NB_TRIGGER_ECTRL:
  case ASL_SCHED_NBRHS_DCTRL_CONST:
  case ASL_COMB_1BITSTS:
  case ASL_EXEC_DISABLE:
  case ASL_WRD_REDXOR:
  case ASL_LD_TFRWARG_DRVP:
  case ASL_LD_LOGIC_WIDE_DRIVER:
  case ASL_CALC_BUFIF_NEWSTATE:
  case ASL_UDP_WIDE_ADJSTATE:
  case ASL_FORCE_ACTIVE:
  case ASL_EVAL_CMOS_GATE:
  case ASL_EVAL_RCMOS_GATE:
  case ASL_EXEC_STSK:
  case ASL_EXEC_DISPLAY:
  case ASL_SETSAV_ASSOC_TSK:
  case ASL_SCALAR_WIRE_INHIBIT:
  case ASL_CANCELE_PEND_CHG_1GEV:
  case ASL_CANCELE_PEND_NOCHG_1GEV: 
  case ASL_ARM_ECTRL:
  /* SJM 05-26-07 - FIXME - these has 2nd rw ptr and returns int - can't trk */
  case ASL_STREN_CORRECT_FRC:
  case ASL_CORRECT_FRC:
  case ASL_PSEL_CORRECT_FRC:
  case ASL_STREN_PSEL_CORRECT_FRC:
  case ASL_RESCHD_CAEV:
  case ASL_RESCHD_CAEV_CONST:
  case ASL_SCHD_CAEV_CONST: 
  case ASL_SCHD_CAEV_CONST0:
  case ASL_STREN_SCHD_1GEV: 
  case ASL_SCHD_1GEV:
  case ASL_PEND_CHG_1GEV:
  case ASL_PEND_CHG_1GEV_CONST:
  case ASL_PEND_NOCHG_1GEV:
  case ASL_STREN_PEND_CHG_1GEV:
  case ASL_EXEC_WIDE_LOGIC_GATE:
  case ASL_RANDOM_WITH_SEED:
  case ASL_RANDOM:
  case ASL_RHS_PSEL:
   return(1);
  case ASL_GET_DEL_1X:
  case ASL_GET_DEL_4X:
   return(2);
  case ASL_SCHED_PROC_DELAY:
  case ASL_SCHED_NBRHS_DCTRL:
  case ASL_SCHED_NAMBLK_THD:
  case ASL_SCHED_FORK:
  case ASL_TRIGGER_ECTRL:
  case ASL_FMONIT_TRIGGER:
  case ASL_ASSIGN_QCAF:
  case ASL_SETUP_TASK_THD:
  case ASL_EXEC_CAUSE:
  case ASL_SCHED_NBRHS_SCALAR_DCTRL:
  case ASL_SCHED_NBRHS_SCALAR_DCTRL_CONST:
  case ASL_SCHED_NBRHS_NOMEM_DCTRL_CONST:
  case ASL_SCHD_NB_VARDEL_RHSCONST_DCTRL:
  case ASL_BLD_NB_NODELAY_TEV:
  case ASL_BBLK_DBG_MSG:
  case ASL_CHK_GATE_VPI_CHG:
  case ASL_CHK_DCE_CBVC: 
  case ASL_SCHED_PROC_DELAY_CONST:
  case ASL_SCHED_PROC_DELAY_PND0:
  case ASL_ADD_DMPV_CHGLST_EL:
  case ASL_ADD_DMPV_CHGLST_EL_ARRAY:
  case ASL_ADD_DMPP_CHGLST_EL:
  case ASL_WDEL_SCHD_1WIREBIT:
  case ASL_SCHD_SCALAR_1WEV:
  case ASL_RESCHD_1WEV:
  case ASL_SCHD_1PTHWIREBIT:
  case ASL_SCHD_ST_1PTHWIREBIT:
  case ASL_SCHD_SCALAR_1PTHWIREBIT:
  case ASL_SCHD_1PTHWIREBIT_NOMSG:
  case ASL_TIMING_CHECK_RECORD:
  case ASL_EVAL_TRANIF_LD:
  case ASL_EXEC_QC_ASSIGN:
  case ASL_EXEC_QC_FORCE:
  case ASL_EXEC_QC_WIREFORCE:
  case ASL_EXEC_QC_DEASSIGN:
  case ASL_EXEC_QC_WIRERELEASE:
  case ASL_EVAL_NMOS_GATE:
  case ASL_EVAL_RNMOS_GATE:
  case ASL_EVAL_PMOS_GATE:
  case ASL_EVAL_RPMOS_GATE:
  case ASL_SCHED_UNKNOWN_BIT:
  case ASL_EVAL_TRAN_DRVRS:
  case ASL_EVAL_TRAN_DRVRS_VECTOR:
  case ASL_CHG_GATE_OUTWIRE: 
  case ASL_SCHED_VEC_MIPD_BIT:
  case ASL_SCHD_CAEV:
  case ASL_SCHED_SCALAR_MIPD_PATH:
  case ASL_SCHED_SCALAR_MIPD_16V:
  case ASL_SCHED_SCALAR_MIPD_IS16V:
  case ASL_SCHED_SCALAR_MIPD_IS16V1:
  case ASL_SCHED_SCALAR_MIPD_IS16V2:
  case ASL_SCHED_SCALAR_MIPD_IS1V:
  case ASL_SCHED_SCALAR_MIPD_PND0:
  case ASL_SCHED_SCALAR_MIPD_CONST:
  case ASL_SCHED_PROC_DELAY_NT:
  case ASL_SCHED_PROC_DELAY_CONST_NT:
  case ASL_SCHED_PROC_DELAY_PND0_NT:
  case ASL_ADD_STATIC_NCHG_SEL:
  case ASL_PROCESS_MIPD_NCHG:
  case ASL_PROCESS_SCAL_MIPD_NCHG:
   return(0);
  case ASL_REAL_POW_FUNC: 
   *opand_bytsiz = 2*WRDBYTES;
   return(0);
  case ASL_TSKDONE_CLEANUP_RET:
   *opand_bytsiz = -1; 
   return(1);
  case ASL_SGNBIT_ON:
   /* this returns value that is WPTR arg 0 */
   aslap = &(ip->extrau.asl_ausedefs[1]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = WRDBYTES*wlen;
   return(wlen);
  case ASL_CHK_LD_VPIPUTV_DRIVER:
   /* SJM 04/25/07 - could pass the the net's bit size instead */ 
   aslap = &(ip->extrau.asl_ausedefs[0]);
   bitlen = __get_tnwid(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = 2*WRDBYTES*wlen;
   return(2*WRDBYTES*wlen);
  case ASL_STREN_SCHED_UNKNOWN_BIT:
   /* SJM 04/26/07 - using tn width for width - width must be 2 */
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bytlen = __get_tnwid(aslap->am_arg.am_tni);
   *opand_bytsiz = bytlen;
   return(0);
  case ASL_JMP_EQ_STMASK:
  case ASL_BYTECMP:
  case ASL_WIDE_ANY1:
   /* width in bytes (or bits since stren) in arg 2 */
   aslap = &(ip->extrau.asl_ausedefs[2]);
   *opand_bytsiz = __get_wrd_con_val(aslap->am_arg.am_tni);
   return(1); 
  case ASL_MOVABW_FR_SVEC:
  case ASL_SET_BYTEVAL:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bytlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = bytlen;
   return(2*wlen_(bytlen));
  case ASL_MOVABW_ONEW_FR_SVEC:
   aslap = &(ip->extrau.asl_ausedefs[1]);
   bytlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = bytlen;
   return(1);
  case ASL_MOVSB_FR_WSTAD:
  case ASL_MOVSB_FR_WIDESTAD:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bytlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = 2*wlen_(bytlen)*WRDBYTES;
   return(wlen_(bytlen));
  case ASL_MOVR_FR_W:
  case ASL_MOVR_FR_SGNW:
   aslap = &(ip->extrau.asl_ausedefs[1]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = 2*wlen_(bitlen);
//SJM? THINKABOUTME - 05-24-2007 return 1 since no identity for 2nd wrd
   return(1);
  case ASL_MOVW_FR_R:
//AIV? fixme - this should not be a write ptr
   *opand_bytsiz = 2*WRDBYTES;
   return(2); 
  case ASL_EVAL_1W_NONSTREN_WIRE:
  case ASL_EVAL_1W_NONSTREN_WIRE_AND:
  case ASL_EVAL_1W_NONSTREN_WIRE_OR:
   *opand_bytsiz = WRDBYTES;
   return(2);
  case ASL_WIDCAS_EVAL:
  case ASL_WIDCASX_EVAL:
  case ASL_WIDCASZ_EVAL:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   wlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = 2*wlen*WRDBYTES;
   return(1);
  case ASL_WIDOMITXZ_NE:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = 2*wlen*WRDBYTES;
   return(1);
  case ASL_WIDE_CMP:
  case ASL_SGN_WIDE_CMP:
  case ASL_WIDE_WORD_CMP:
  case ASL_WIDE_SGNWORD_CMP:
  case ASL_WIDE_JMPOR_0:
  case ASL_WIDE_JMP_EQ:
  case ASL_WIDE_CMP_NEQ:
  case ASL_WIDE_CMP_EQ:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = wlen*WRDBYTES;
   return(1);
  case ASL_CVT_LNGBOOL:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   wlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = WRDBYTES*wlen;
   return(1);
  case ASL_WORDCMP:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   wlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = wlen*WRDBYTES;
   return(1);
  case ASL_VVAL_IS1:
  case ASL_WIDE_VVAL_IS0:
   aslap = &(ip->extrau.asl_ausedefs[1]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = wlen_(bitlen)*WRDBYTES;
   return(1);
  case ASL_MEMCPY:
  case ASL_ADJUST_TRIREG:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bytlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = bytlen;
   wlen = wlen_(bytlen*8);
   return(wlen);
  case ASL_MY_MEMSET:
   *opand_bytsiz = WRDBYTES;
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bytlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bytlen*8);
   return(wlen);
  case ASL_SGN_XTND_WIDEN: 
  case ASL_SGN_XTND_WIDEN_2STATE: 
  case ASL_GET_PERINST_VAL:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   *opand_bytsiz = 2*WRDBYTES*wlen_(bitlen);
   aslap = &(ip->extrau.asl_ausedefs[3]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   return(2*WRDBYTES*wlen_(bitlen));
  case ASL_WIDE_BITXOR:
  case ASL_WIDE_BITAND:
  case ASL_WIDE_BITOR:
  case ASL_WIDE_RSHIFT:
  case ASL_WIDE_LSHIFT:
  case ASL_WIDE_POWER:
  case ASL_LSUB:
  case ASL_LADD:
  case ASL_LMULT:
  case ASL_SGN_LMULT:
  case ASL_SGN_LDIVMOD:
  case ASL_LDIVMOD:
  case ASL_RHS_PSEL_WIDE:
   /* these only work on a or b not both ab part */
   aslap = &(ip->extrau.asl_ausedefs[3]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = WRDBYTES*wlen;
   return(wlen);
  case ASL_WIDE_SGN_POWER:
  case ASL_WIDE_SGN_POWER_2STATE:
//AIV? FIXME - can't return value for -1 case needs x 
   __misc_terr(__FILE__, __LINE__);
  case ASL_WID_BIN_BITOR:
  case ASL_WID_BIN_BITXNOR:
  case ASL_WID_BIN_BITXNOR_2STATE:
  case ASL_WIDE_QCOL_COMB_OPANDS:
   /* these work on both a and b parts */
   aslap = &(ip->extrau.asl_ausedefs[3]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = 2*WRDBYTES*wlen;
   return(2*wlen);
  case ASL_EVAL_WIDE_WIRE_AND:
  case ASL_EVAL_WIDE_WIRE_OR:
  case ASL_EVAL_WIDE_WIRE:
   /* SJM 04/26/07 - drive width may not be same as accum wptr width */
   /* SJM 06-16-07 - opand bytes is a part width, but returns a and b size */
   aslap = &(ip->extrau.asl_ausedefs[3]);
   bitlen = __get_tnwid(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen); 
   *opand_bytsiz = WRDBYTES*wlen;
   return(2*wlen);
  case ASL_WIDE_NOTL:
  case ASL_SGNMASK:
   /* SJM 04/26/07 - if value-result arg tracking in it will be tracked out */ 
   /* this is a or b part only */
   /* SJM 07-26-07 - these do not return a value */
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = WRDBYTES*wlen;
   return(wlen);
  case ASL_WIDE_REDXOR:
   /* SJM 07-26-07 - this returns only a part 1 bit as word val (reducing) */ 
   aslap = &(ip->extrau.asl_ausedefs[1]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = WRDBYTES*wlen;
   return(1);
  case ASL_WID_UN_REDOR:
   /* this is a and b parts */
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = 2*WRDBYTES*wlen;
   return(2*wlen);
  case ASL_WID_UNBITNOT:
   /* this is a and b parts for operand but only a part returned */
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = 2*WRDBYTES*wlen;
   return(wlen);
  case ASL_EVAL_STWIRE:
   aslap = &(ip->extrau.asl_ausedefs[2]);
   bi1 = __get_wrd_con_val(aslap->am_arg.am_tni);
   aslap = &(ip->extrau.asl_ausedefs[3]);
   bi2 = __get_wrd_con_val(aslap->am_arg.am_tni);
   bytlen = bi1 - bi2 + 1;
   *opand_bytsiz = bytlen;
   return(wlen_(bytlen));
  case ASL_LHSPSEL:
  case ASL_CP_SOFS_WVAL:
   /* SJM 04/26/07 - operand src size is rhs numbits byte for number of wrds */
   /* return size is entire lhs width although only some bits set */
   aslap = &(ip->extrau.asl_ausedefs[3]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = WRDBYTES*wlen;
   aslap = &(ip->extrau.asl_ausedefs[0]);
   bitlen = __get_tnwid(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   return(wlen);
  case ASL_SET_RHS_NEW_GATEVAL:
   aslap = &(ip->extrau.asl_ausedefs[1]);
   bitlen = __get_wrd_con_val(aslap->am_arg.am_tni);
   wlen = wlen_(bitlen);
   *opand_bytsiz = WRDBYTES*wlen;
   return(0);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(0);
}
