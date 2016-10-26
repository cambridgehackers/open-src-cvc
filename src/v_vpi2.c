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
 * 2nd module to implement pli vpi_ routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

#include "vpi_user.h"
#include "cv_vpi_user.h"

/* local prototypes */
static void mk2_exprclass_handle(struct h_t *, struct expr_t *,
 t_midat *, struct task_t *);
static int32 iconnbit_lvalue(struct mod_pin_t *, struct net_pin_t *,
 struct itree_t *);
static vpiHandle bld_inmod_port_iter(struct h_t *);
static vpiHandle bld_fjlist_iter(struct st_t *, t_midat *, struct task_t *);
static vpiHandle bld_listofstmts_iter(struct st_t *, t_midat *, 
 struct task_t *);
static vpiHandle bld_listofexprs_iter(struct expr_t *, t_midat *, 
 struct task_t *);
static int32 termexpr_matches(struct expr_t *, struct net_t *, int32);
static int32 bld_net_tchkterms(struct net_t *, t_midat *, int32);
static int32 bld_net_pathterms(struct net_t *, t_midat *, int32);
static int32 bld_delay_iter(union del_u, word32, t_midat *, struct task_t *);
static vpiHandle bld_dig_attrlist_iter(struct h_t *, struct attr_t *);
static vpiHandle bld_netmdport_iter(struct h_t *);
static int32 bld_net_mdpins(struct net_t *, struct mod_t *, t_midat *);
static vpiHandle bld_netbitmdport_iter(struct h_t *);
static int32 cmp_drvld_bitndx(struct net_t **, struct h_t *, char *);
static int32 bld_netbit_mdpins(struct net_t *, int32, struct mod_t *, 
 t_midat *);
static vpiHandle bld_neticonnport_iter(struct h_t *);
static int32 bld_net_iconns(struct net_t *, t_midat *);
static int32 same_vpi_handle(struct h_t **, int32, int32, struct h_t *,
 struct hrec_t *);
static vpiHandle bld_netbiticonnport_iter(struct h_t *);
static int32 bld_netbit_iconns(struct net_t *, int32, t_midat *);
static vpiHandle net_lds_iter(struct h_t *);
static int32 bld_net_lds(struct net_t *, t_midat *);
static int32 fill_ld_handle(struct h_t *, struct hrec_t *, struct net_pin_t *);
static vpiHandle bit_lds_iter(struct h_t *);
static int32 bld_bit_lds(struct net_t *, int32, t_midat *, int32);
static int32 fill_bit_ld_handle(struct h_t *, struct hrec_t *, int32, int32, int32,
 struct net_pin_t *);
static vpiHandle bit_xl_ldsdrvs_iter(struct h_t *, int32);
static vpiHandle net_drvs_iter(struct h_t *);
static int32 bld_net_drvs(struct net_t *, t_midat *);
static int32 fill_drv_handle(struct h_t *, struct hrec_t *, struct net_pin_t *);
static vpiHandle bit_drvs_iter(struct h_t *hp);
static int32 bld_bit_drvs(struct net_t *, int32, t_midat *, int32);
static int32 fill_bit_drv_handle(struct h_t *, struct hrec_t *, int32, int32, int32,
 struct net_pin_t *);
static vpiHandle reg_drvs_iter(struct h_t *);
static vpiHandle cnvt_name_to_handle(char *, struct symtab_t *, t_midat *);
static vpiHandle bld_symhandle(char *, struct sy_t *, struct symtab_t *,
 struct itree_t *);
static int32 validate_property(char *, int32);
static int32 modprop_vpiget(struct h_t *, int32);
static void notpropof_err(word32, int32);
static word32 to_vpi_reghtyp(word32);
static int32 netprop_vpiget(struct h_t *, int32);
static int32 regprop_vpiget(struct h_t *, int32);
static int32 arrprop_vpiget(struct h_t *, int32);
static int32 arrwrdprop_vpiget(struct h_t *, int32);
static int32 paramprop_vpiget(struct h_t *, int32);
static int32 portprop_vpiget(struct h_t *, int32);
static int32 get_param_constyp(struct net_t *);
static int32 gateprop_vpiget(struct h_t *, int32);
static int32 tcallprop_vpiget(struct h_t *, int32);
static int32 funcdefprop_vpiget(struct h_t *, int32);
static int32 contaprop_vpiget(struct h_t *, int32);
static int32 fcallprop_vpiget(struct h_t *, int32);
static int32 tchkprop_vpiget(struct h_t *, int32);
static int32 to_vpi_tchktyp(word32);
static int32 tchktermprop_vpiget(struct h_t *, int32);
static int32 to_vpi_edgeval(word32);
static int32 pthprop_vpiget(struct h_t *, int32);
static int32 pthtermprop_vpiget(struct h_t *, int32);
static int32 exprclass_prop_vpiget(struct h_t *, int32);
static int32 get_vpi_const_typ(struct expr_t *);
static int32 iodecl_prop_vpiget(struct h_t *, int32);
static int32 udpiodecl_get(struct h_t *, int32);
static int32 udpdefnprop_vpiget(struct h_t *, int32);
static int32 udptabentryprop_vpiget(struct h_t *, int32);
static int32 dig_attrprop_vpiget(struct h_t *, int32);
static char *modstrprop_vpiget(struct h_t *, int32);
static char *netstrprop_vpiget(struct h_t *, int32);
static char *portstrprop_vpiget(struct h_t *, int32);
static char *gatestrprop_vpiget(struct h_t *, int32);
static char *tcallstrprop_vpiget(struct h_t *, int32);
static char *fcallstrprop_vpiget(struct h_t *, int32);
static char *taskstrprop_vpiget(struct h_t *, int32);
static char *iodeclstrprop_vpiget(struct h_t *, int32);
static char *dig_attrstrpop_vpiget(struct h_t *, int32);


/* extern prototypes (maybe defined in this module) */
extern vpiHandle vpi_handle_by_name(char *, vpiHandle);
extern vpiHandle vpi_handle_by_index(vpiHandle, PLI_INT32);
extern int32 vpi_get(PLI_INT32, vpiHandle);
extern word32 __ntyp_to_vpivarhtyp(struct net_t *);
extern word32 __to_vpinetbithtyp(word32);
extern word32 __from_vpi_vartyp(word32);
extern int32 __expr_optype_get(struct expr_t *);
extern char *vpi_get_str(int32, vpiHandle);
extern char *__to_vpionam(char *, word32);
extern char *__to_vpiopchar(char *, int32);
extern void __still_comp_err(char *);
extern int32 __validate_handle(char *, struct h_t *);
extern int32 __get_vpinet_index(struct net_t **, struct h_t *);

extern vpiHandle __bld_port_iterator(struct h_t *);
extern vpiHandle __bld_neticonn_iter(struct h_t *);
extern vpiHandle __bld_paramassign_stmt_iter(struct h_t *);
extern vpiHandle __bld_udpline_iter(struct h_t *);
extern vpiHandle __bld_primterm_iterator(struct h_t *);
extern vpiHandle __bld_loc_lds_iterator(struct h_t *, int32);
extern vpiHandle __bld_lds_iterator(struct h_t *, int32);
extern int32 __bld_xl_drvld_vtxtab(struct net_t *, int32, struct itree_t *,
 int32);
extern vpiHandle __bld_loc_drvs_iterator(struct h_t *, int32);
extern vpiHandle __bld_drvs_iterator(struct h_t *, int32);
extern vpiHandle __bld_arrwrd_iterator(struct h_t *);
extern vpiHandle __bld_bitof_iterator(struct h_t *);
extern vpiHandle __bld_systf_iterator(struct h_t *);
extern vpiHandle __bld_tfargexpr_iterator(struct h_t *);
extern vpiHandle __bld_pthterm_iterator(struct h_t *, word32);
extern vpiHandle __bld_stmt_iterator(struct h_t *);
extern vpiHandle __bld_netin_tchkterms(struct h_t *);
extern vpiHandle __bld_netin_pthterms(struct h_t *);
extern vpiHandle __bld_caseitems_iter(struct h_t *);
extern vpiHandle __bld_casi_exprs_iter(struct h_t *);
extern vpiHandle __bld_operands_iter(struct h_t *);
extern vpiHandle __bld_allcbs_iter(struct h_t *);
extern vpiHandle __bld_delay_expr_iter(struct h_t *);
extern vpiHandle __bld_iodecl_stmt_iter(struct h_t *);
extern struct task_t *__find_qualnam_task(char *, struct mod_t *,
 struct task_t *);
extern t_midat *__xmrget_refgrp_to_targ(struct gref_t *);
extern struct itree_t *__get_npprefloc(struct net_pin_t *);
extern void __get_bidnpp_sect(struct net_t *, struct net_pin_t *, int32 *,
 int32 *);
extern int32 __exprtype_get(struct expr_t *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern vpiHandle __nil_iter_err(word32);
extern void __notstrpropof_err(word32, int32);
extern struct pviter_t *__alloc_empty_iter(int32, vpiHandle *);
extern void __iter_fill_with_empty(struct pviter_t *);
extern void __init_hrec(struct hrec_t *);
extern void __grow_hptab(int32);
extern void __grow_hptab2(int32);
extern word32 __to_vpi_stmttyp(struct st_t **);
extern int32 __ip_indsrch(char *);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct sy_t *__get_nongia_sym(char *, struct symtab_t *);
extern vpiHandle __mk_handle(word32, void *, t_midat *, struct task_t *);
extern struct h_t *__get_new_hp_handle(void);
extern struct hrec_t *__get_hp_from_freelst(void);
extern struct hrec_t *__get_hrec_from_freelst(void);
extern int32 __is_scope_sym(struct sy_t *);
extern word32 __to_vpi_tasktyp(word32);
extern word32 __gate_to_vpiprimtyp(struct gate_t *);
extern int32 __to_vpi_primtyp(struct gate_t *);
extern int32 __primtermprop_vpiget(struct h_t *, int32);

extern void __getarr_range(struct net_t *, int32 *, int32 *, int32 *);
extern void __getwir_range(struct net_t *, int32 *, int32 *);
extern int32 __get_arrwide(struct net_t *);
extern int32 __wide_vval_is0(word32 *, int32);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern char *__msg2_idp_blditree(char *, t_midat *);
extern char *__msg_idp_blditree(char *, t_midat *, struct task_t *);
extern void __extract_delval(word64 *, int32 *, union del_u, word32);
extern void __cnv_ticks_tonum64(word64 *, word64, struct mod_t *);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern void __ld_arr_val(struct xstk_t *, struct expr_t *, struct net_t *, 
 int32, struct gref_t *);
extern struct expr_t *__bld_rng_numxpr(word32, word32, int32);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern char *__my_malloc(size_t);
extern int32 __unnormalize_ndx(struct net_t *, int32);
extern int32 __to_vpi_netproptyp(word32 ntyp);
extern struct expr_t *__glbnam_to_expr(char *);
extern char *__to_glbcmp_nam(struct expr_t *);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern struct expr_t *__sim_alloc_newxnd(void);
extern int32 __expr_is_vpiconst(struct expr_t *);
extern char *__to_vpipnam(char *, int32);
extern word32 __map_tovpi_stren(word32);
extern char *__strab2_tostr(char *, word32 *, int32, int32, int32);
extern int32 __name_vpi_hasdot(const char *);
extern void __free_iterator(vpiHandle);
extern void __free_xtree(struct expr_t *);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern struct attr_t *__find_attrspec(struct h_t *);
extern struct net_t *__get_indexed_psel_range(struct expr_t *, int32 *, 
 int32 *);

extern void __arg_terr(char *, int32);
extern void __vpi_terr(char *, int32);
extern void __vpi_err(int32, int32, char *, ...);

/* vpi only storage */
extern struct t_vpi_error_info *__last_eip;/* if err, ptr to wrk eifo or nil */

/*
 * ROUTINES TO BUILD ITERATORS (2nd GROUP)
 */

/*
 * build an expression from expr_t record
 *
 * this is shell that allocates empty handle and call v2 for filling it
 * needed because need to fill only for building iterators containing exprs
 *
 * if allocated, caller must see xp free bit
 */
extern vpiHandle __mk_exprclass_handle(struct expr_t *xp,
 t_midat *idp, struct task_t *xin_tskp)
{
 vpiHandle href;
 struct h_t *hp;

 /* here vpiNet is just place holder - fixed by caller */
 href = __mk_handle(vpiNet, NULL, idp, xin_tskp);
 hp = (struct h_t *) href;
 mk2_exprclass_handle(hp, xp, idp, xin_tskp);
 return(href);
}

/*
 * 
 * here handle content are expressions - bit handle from iterators
 * use different representation 
 *
 * select handles because they are not in handle index value
 * must be expr. itree loc - when converting to net in must handle xmr 
 * 
 * this is version that expects handle to be allocated and filled
 * (useful for filling iterator handles)
 */
static void mk2_exprclass_handle(struct h_t *hp,
 struct expr_t *xp, t_midat *idp, struct task_t *xin_tskp)
{
 int32 otyp, biti;
 struct hrec_t *hrp;
 t_midat *xidp;
 struct task_t *xtskp;
 struct net_t *np;
 struct expr_t *idndp;
 struct sy_t *syp;
 struct mod_t *imdp;

 hrp = hp->hrec;
 switch (xp->optyp) {
  case ID:   
   syp = xp->lu.sy;
   xidp = idp;
   if (xp->locqualnam)
    {
     imdp = (struct mod_t *) idp[MD_MDP];
     xtskp = __find_qualnam_task(xp->ru.qnchp, imdp, xin_tskp);
    }
   else xtskp = NULL;
   goto fill_id_handle;
  case GLBREF:
   xidp = __xmrget_refgrp_to_targ(xp->ru.grp);
   xtskp = xp->ru.grp->targtskp;

   /* xmr expressions can also be scopes objects (i.e. not net/reg or var) */
   syp = xp->lu.sy;
   switch (syp->sytyp) {
    case SYM_I: case SYM_M:
     /* DBG remove -- */
     if (xtskp != NULL) __vpi_terr(__FILE__, __LINE__);
     /* --- */
     hrp->htyp = vpiModule;
     imdp = (struct mod_t *) xidp[MD_MDP];
     hrp->hu.hmdp = imdp;
     hp->hin_idp = xidp;
     hrp->hin_tskp = NULL;
     return;
    /* notice function here must be function call */
    case SYM_TSK: case SYM_LB:
     { 
      struct task_t *tskp;
      struct symtab_t *sytp;

      tskp = syp->el.etskp;
      /* DBG remove --- */
      if (tskp != xtskp) __vpi_terr(__FILE__, __LINE__);
      /* --- */
      hrp->htyp = __to_vpi_tasktyp(tskp->tsktyp);
      hrp->hu.htskp = xtskp; 
      hp->hin_idp = xidp;
      sytp = xtskp->tsksymtab->sytpar;
      /* DBG remove */
      if (sytp == NULL) __vpi_terr(__FILE__, __LINE__); 
      /* --- */
      if (sytp->sypofsyt->sytyp != SYM_I)
       xin_tskp = sytp->sypofsyt->el.etskp;
      else xin_tskp = NULL;
      hrp->hin_tskp = xin_tskp;
     }
     return;
    default:
     break;
   }

fill_id_handle:
   /* this is both net/reg and variable (int32,real.time) but not bit select */
   np = xp->lu.sy->el.enp;
   otyp = __ntyp_to_vpivarhtyp(np);
   hrp->htyp = otyp;
   hrp->hu.hanyp = (void *) np;
   hp->hin_idp = xidp;
   hrp->hin_tskp = xtskp;
   break;
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM:
   hrp->htyp = vpiConstant;
   hrp->hu.hxp = xp;
   goto fill_itloc;
  case OPEMPTY:
   /* this is vpi Null Op operation */
   hrp->htyp = vpiOperation;
   hrp->hu.hxp = xp;
   goto fill_itloc;
  case LSB:
   idndp = xp->lu.x;
   /* SJM 08/23/00 - branches never XMRs */ 
   /* SJM 08/23/00 - if select from xmr, must change itree loc */
   if (idndp->optyp == GLBREF)
    {
     idp = __xmrget_refgrp_to_targ(idndp->ru.grp);
     xin_tskp = idndp->ru.grp->targtskp;
    }

   np = idndp->lu.sy->el.enp;
   if (np->n_isarr) hrp->htyp = vpiMemoryWord;
   else hrp->htyp = __to_vpinetbithtyp(np->ntyp);
   /* DBG remove -- */
   /* must never see parameter bit select or parameter array index */
   /* because must be converted to constant during translate/load */
   if (np->n_isaparam) __vpi_terr(__FILE__, __LINE__);
   /* --- */

   /* try to optimize to bith ndx form */
   if (!__expr_is_vpiconst(xp->ru.x))
    {
bld_expr_bsel:
     hrp->hu.hxp = xp;
     goto fill_itloc;
    }
   biti = __comp_ndx(np, xp->ru.x);
   if (biti == -1) goto bld_expr_bsel; 
   hrp->hu.hnp = np;
   hrp->hi = biti;
   hrp->bith_ndx = TRUE;
   goto fill_itloc;
  case PARTSEL:
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   hrp->htyp = vpiPartSelect;
   hrp->hu.hxp = xp;
   /* SJM 08/23/00 - if xmr part select, must change itree loc */
   if (xp->lu.x->optyp == GLBREF)
    {
     idndp = xp->lu.x;
     idp = __xmrget_refgrp_to_targ(idndp->ru.grp);
     xin_tskp = idndp->ru.grp->targtskp;
    }
   goto fill_itloc;
  case FCALL:
   if (xp->lu.x->lu.sy->sytyp == SYM_SF) hrp->htyp = vpiSysFuncCall;
   else
    {
     /* SJM 08/23/00 - if xmr user fcall, must change itree loc */
     if (xp->lu.x->optyp == GLBREF)
      {
       idndp = xp->lu.x;
       idp = __xmrget_refgrp_to_targ(idndp->ru.grp);
       xin_tskp = idndp->ru.grp->targtskp;
      }
     hrp->htyp = vpiFuncCall;
    }
   hrp->hu.hxp = xp;
   goto fill_itloc;
  default:
   hrp->htyp = vpiOperation;
   hrp->hu.hxp = xp;
fill_itloc:
   hp->hin_idp = idp;
   hrp->hin_tskp = xin_tskp;
  }
}

/*
 * build a parameter assign statement iterator
 *
 * this is internally same as parameter (gets valus from net)
 *
 * FIXME - not handle left hand side select parameter assigns in PLI
 */
extern vpiHandle __bld_paramassign_stmt_iter(struct h_t *hp)
{
 int32 pi, pi2, nparams; 
 struct h_t *hp2;
 struct hrec_t *hrp2, *hrp;
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct mod_t *mdp;
 struct task_t *tskp;

 if (hp == NULL)
  {
   return(__nil_iter_err(vpiParamAssign));
  }

 ihref = NULL;
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 hrp = hp->hrec;
 switch (hrp->htyp) {
  case vpiModule: 
   nparams = mdp->mprmnum + mdp->mlocprmnum;
   if (nparams <= 0) return(NULL);

   iterp = __alloc_empty_iter(nparams, &ihref);
   __iter_fill_with_empty(iterp);
   for (pi = 0, pi2 = 0; pi < mdp->mprmnum; pi++)
    {
     hp2 = iterp->scanhptab[pi2++];
     hrp2 = hp2->hrec;
     hrp2->htyp = vpiParamAssign;
     hrp2->hu.hnp = &(mdp->mprms[pi]);
     hp2->hin_idp = hp->hin_idp;
    }
   for (pi = 0; pi < mdp->mlocprmnum; pi++)
    {
     hp2 = iterp->scanhptab[pi2++];
     hrp2 = hp2->hrec;
     hrp2->htyp = vpiParamAssign;
     hrp2->hu.hnp = &(mdp->mlocprms[pi]);
     hp2->hin_idp = hp->hin_idp;
    }
   break;
  case vpiTask: case vpiFunction:
   tskp = hrp->hu.htskp;
bld_tskiter:
   nparams = tskp->tprmnum + tskp->tlocprmnum;
   if ((nparams = tskp->tprmnum) <= 0) return(NULL);
   iterp = __alloc_empty_iter(nparams, &ihref);
   __iter_fill_with_empty(iterp);

   for (pi = 0, pi2 = 0; pi < tskp->tprmnum; pi++)
    {
     hp2 = iterp->scanhptab[pi2++];
     hrp2 = hp2->hrec;
     hrp2->htyp = vpiParamAssign;
     hrp2->hu.hnp = &(tskp->tsk_prms[pi]);
     hp2->hin_idp = hp->hin_idp;
     hrp2->hin_tskp = tskp;
    }
   for (pi = 0; pi < tskp->tlocprmnum; pi++)
    {
     hp2 = iterp->scanhptab[pi2++];
     hrp2 = hp2->hrec;
     hrp2->htyp = vpiParamAssign;
     hrp2->hu.hnp = &(tskp->tsk_locprms[pi]);
     hp2->hin_idp = hp->hin_idp;
     hrp2->hin_tskp = tskp;
    }
   break;
  case vpiNamedBegin: case vpiNamedFork:
   tskp = hrp->hu.htskp;
   goto bld_tskiter;
  default:
   __vpi_err(1851, vpiError,
    "unable to construct vpiParamAssign iterator for %s object",
     __to_vpionam(__wrks2, hrp->htyp));
 }
 return(ihref);
}

/*
 * build a IO decl iterator
 *
 * this is internally same as parameter (property values from net_t)
 */
extern vpiHandle __bld_iodecl_stmt_iter(struct h_t *hp)
{
 int32 ni, nports; 
 struct h_t *hp2;
 struct net_t *np;
 struct hrec_t *hrp2; 
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct udp_t *udpp;
 struct mod_pin_t *mpp;

 if (hp == NULL) return(__nil_iter_err(vpiIODecl));
 ihref = NULL;
 switch (hp->hrec->htyp) {
  case vpiModule: 
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   /* module port is normal net form */
   np = &(mdp->mnets[0]);
   for (nports = 0; nports < mdp->mnnum; nports++, np++)
    { if (np->iotyp != NON_IO) nports++; }
   if (nports <= 0) return(NULL);

   iterp = __alloc_empty_iter(nports, &ihref);
   __iter_fill_with_empty(iterp);
   np = &(mdp->mnets[0]);
   for (nports = 0, ni = 0; nports < mdp->mnnum; nports++, np++)
    {
     if (np->iotyp != NON_IO) continue;

     hp2 = iterp->scanhptab[ni];
     hrp2 = hp2->hrec;
     hrp2->htyp = vpiIODecl;
     hrp2->hu.hnp = np;
     hp2->hin_idp = hp->hin_idp;
     ni++;
    }
   break;
  case vpiTask: case vpiFunction:
   /* normal io decl handle is net - alt form only for udp is mod_port */
   tskp = hp->hrec->hu.htskp;
bld_tsk_iodecls:
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   np = &(tskp->tsk_regs[0]);
   for (nports = 0, ni = 0; ni < tskp->trnum; nports++, np++)
    { if (np->iotyp != NON_IO) nports++; }
   if (nports <= 0) return(NULL);

   iterp = __alloc_empty_iter(nports, &ihref);
   __iter_fill_with_empty(iterp);
   np = &(tskp->tsk_regs[0]);
   for (nports = 0, ni = 0; nports < tskp->trnum; nports++, np++)
    {
     if (np->iotyp != NON_IO) continue;

     hp2 = iterp->scanhptab[ni];
     hrp2 = hp2->hrec;
     hrp2->htyp = vpiIODecl;
     hrp2->hu.hnp = np;
     hp2->hin_idp = hp->hin_idp;
     hrp2->hin_tskp = tskp;
     ni++;
    }
   break;
  case vpiNamedBegin: case vpiNamedFork:
   tskp = hp->hrec->hu.htskp;
   goto bld_tsk_iodecls;
  case vpiUdpDefn:
   /* here io decl port is alternative mod port form */ 
   /* LOOKATME - maybe should change Cver d.s. to store udp ports as nets */
   udpp = hp->hrec->hu.hudpp; 
   /* DBG remove --- */
   if (hp->hin_idp != NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   for (nports = 0, mpp = udpp->upins; mpp != NULL; mpp = mpp->mpnxt)
    {
     /* DBG remove --- */
     if (mpp->mptyp == IO_UNKN || mpp->mptyp == IO_BID)
      __vpi_terr(__FILE__, __LINE__);    
     /* --- */
     nports++;
    }
   /* DBG remove --- */
   if (nports <= 0) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   iterp = __alloc_empty_iter(nports, &ihref);
   __iter_fill_with_empty(iterp);
   for (nports = 0, mpp = udpp->upins; mpp != NULL; mpp = mpp->mpnxt,
    nports++)
    {
     hp2 = iterp->scanhptab[nports];
     hrp2 = hp2->hrec;
     hrp2->htyp = vpiIODecl;
     /* this must be actual udp port, not index since no table as with mod */
     hrp2->hu.hmpp = mpp;
     /* use unused itp field to point to containing */
//AIV IDP FIXME ???????
     hp2->hin_idp = (t_midat *) udpp;
     /* alt form for io decl indicates in udp */
     hrp2->htyp2 = vpiUdpDefn;
    }
   break;
  default:
   __vpi_err(1851, vpiError,
    "unable to construct vpiIODecl iterator for %s object",
    __to_vpionam(__wrks2, hp->hrec->htyp));
 }
 return(ihref);
}

/*
 * build a udp table line iterator
 *
 * note in Cver get value can only get string form - user must decompose
 */
extern vpiHandle __bld_udpline_iter(struct h_t *rhp)
{
 int32 uli, nulines;
 struct utline_t *utlp;
 struct hrec_t *hrp; 
 vpiHandle ihref;
 struct udp_t *udpp;
 struct h_t *hp; 
 struct pviter_t *iterp;

 if (rhp == NULL) return(__nil_iter_err(vpiTableEntry));
 if (rhp->hrec->htyp != vpiUdpDefn)
  {
   __vpi_err(1838, vpiError,
    "vpiTableEntry type 1-to-many iterator requires vpiUdpDefn object - %s illegal",
    __to_vpionam(__wrks1, rhp->hrec->htyp));
   return(NULL);
  }
 udpp = rhp->hrec->hu.hudpp;
 for (nulines = 0, utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt) 
  nulines++;
 /* this empty udp legal */
 if (nulines <= 0) return(NULL);

 /* build the design wide iterator of all udps */
 iterp = __alloc_empty_iter(nulines, &ihref);
 __iter_fill_with_empty(iterp);
 for (uli = 0, utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt, uli++) 
  {
   hp = iterp->scanhptab[uli];
   hrp = hp->hrec;
   hrp->htyp = vpiTableEntry;
   hrp->hu.hutlp = utlp;  
//AIV IDP FIXME ???????
   hp->hin_idp = (t_midat *) udpp;
   hrp->hi = uli;
  }
 return(ihref);
}

/*
 * build an iterator for every word32 in array
 *
 * notice this builds a handle for every word32 better for large
 * few bit (1) arrays to use vpi_handle_by_index
 *
 * in order to get parent of this handle, need to look at handle in 
 * iterator - only way to build arrword or vector bit handle
 */
extern vpiHandle __bld_arrwrd_iterator(struct h_t *hp)
{
 int32 ai, iti, awid;
 struct hrec_t *hrp2; 
 vpiHandle ihref;
 struct net_t *np;
 struct h_t *hp2;
 struct pviter_t *iterp;

 if (hp == NULL) return(__nil_iter_err(vpiMemoryWord));
 if (hp->hrec->htyp != vpiMemory) 
  {
   __vpi_err(1857, vpiError,
    "vpiMemoryWord 1-to-many iterator from object %s illegal - must be vpiMemory",
    __to_vpionam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 /* know hp is array (not array word32) handle */  
 np = hp->hrec->hu.hnp;
 awid = __get_arrwide(np);
 /* DBG remove --- */
 if (awid <= 0) __vpi_terr(__FILE__, __LINE__);
 /* --- */ 
 iterp = __alloc_empty_iter(awid, &ihref);
 __iter_fill_with_empty(iterp);
 for (iti = 0, ai = awid - 1; ai >= 0; ai--, iti++) 
  {
   hp2 = iterp->scanhptab[iti];
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiMemoryWord;
   hrp2->hu.hnp = np;
   hrp2->hi = ai;
   hrp2->bith_ndx = TRUE;
   hp2->hin_idp = hp->hin_idp;
   hrp2->hin_tskp = hp->hrec->hin_tskp;
  }
 return(ihref);
}

/*
 * build an iterator for every bit of a reg or net or associated object
 * 
 * also for ports, wire drivers for vectored nets, and scheduled wire driver
 * put value events
 *
 * notice there is no one-to-many connection for vpi_ driver to bit driver
 */
extern vpiHandle __bld_bitof_iterator(struct h_t *hp)
{
 int32 i, iti;
 struct hrec_t *hrp2; 
 vpiHandle ihref;
 struct net_t *np;
 struct h_t *hp2;
 struct mod_t *mdp;
 struct mod_pin_t *mpp; 
 struct pviter_t *iterp;

 if (hp == NULL) return(__nil_iter_err(vpiBit));
 switch (hp->hrec->htyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   np = hp->hrec->hu.hnp;
   if (!np->n_isavec) return(NULL);
   /* know nwid never 0 or will not get here */
   iterp = __alloc_empty_iter(np->nwid, &ihref);
   __iter_fill_with_empty(iterp);
   /* SJM - 06/14/99 - need 2 indices since bit of always [h:l] order */
   for (i = np->nwid - 1, iti = 0; i >= 0; i--, iti++) 
    {
     hp2 = iterp->scanhptab[iti];
     hrp2 = hp2->hrec;
     hrp2->htyp = __to_vpinetbithtyp(np->ntyp);
     hrp2->hu.hnp = np;
     hrp2->hi = i;
     hrp2->bith_ndx = TRUE;
     hp2->hin_idp = hp->hin_idp;
     hrp2->hin_tskp = hp->hrec->hin_tskp;
    }
   break;
  case vpiPort:  
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hp->hrec->hu.hpi]);
   /* returns nil for scalar port - no bits */
   if (mpp->mpwide == 1) return(NULL);
   iterp = __alloc_empty_iter(mpp->mpwide, &ihref);
   __iter_fill_with_empty(iterp);
   /* for port bit handles itp determines port list, hu.hpi port, and hi */
   /* must be h:0 to match bits of connected vector */
   /* SJM - 06/14/99 - need 2 indices since bit of always [h:l] order */
   for (i = mpp->mpwide - 1, iti = 0; i >= 0; i--, iti++)
    {
     hp2 = iterp->scanhptab[iti];
     hrp2 = hp2->hrec;
     hrp2->htyp = vpiPortBit;
     hrp2->hu.hpi = hp->hrec->hu.hpi;
     hrp2->hi = i;
     hp2->hin_idp = hp->hin_idp;
     hrp2->hin_tskp = hp->hrec->hin_tskp;
    }
   break;   
  default:
   __vpi_err(1859, vpiError,
    "vpiBit 1-to-many iterator from object %s illegal",
    __to_vpionam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 return(ihref);
}

/*
 * build iterator of primitive (gate) terminals
 *
 * notice needed so parent is primitive (gate) not scope
 */
extern vpiHandle __bld_primterm_iterator(struct h_t *hp)
{
 int32 pi;
 struct hrec_t *hrp2; 
 vpiHandle ihref;
 struct gate_t *gp;
 t_midat *idp; 
 struct h_t *hp2;
 struct hrec_t *hrp;
 struct pviter_t *iterp;

 if (hp == NULL) return(__nil_iter_err(vpiPrimTerm));
 hrp = hp->hrec;
 if (hrp->htyp != vpiGate && hrp->htyp != vpiUdp && hrp->htyp != vpiSwitch) 
  {
   __vpi_err(1855, vpiError,
    "vpiPrimTerm 1-to-many iterator from %s illegal - member of primitive class required",
    __to_vpionam(__wrks1, hrp->htyp));
   return(NULL);
  }
 gp = hrp->hu.hgp;
 idp = hp->hin_idp;
 /* DBG remove --- */
 if (gp->gpnum == 0) __vpi_terr(__FILE__, __LINE__);
 /* --- */
 iterp = __alloc_empty_iter((int32) gp->gpnum, &ihref);
  __iter_fill_with_empty(iterp);
 for (pi = 0; pi < (int32) gp->gpnum; pi++) 
  {
   hp2 = iterp->scanhptab[pi];
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiPrimTerm;
   hrp2->hi = pi;
   hrp2->hu.hgp = gp;
   hp2->hin_idp = idp;
  }
 return(ihref);
}


/*
 * build iterators for vpi Port selector
 *
 * iterator for reg/wire is all in module ports that the handle connects to
 */
extern vpiHandle __bld_port_iterator(struct h_t *hp)
{
 if (hp == NULL) return(__nil_iter_err(vpiPort));
 switch (hp->hrec->htyp) {
  case vpiModule: return(bld_inmod_port_iter(hp));
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   /* iterator is usually 1 port net connects to (only more if jumpered) */
   /* this returns port handles even if selects (i.e. any overlap) */
   return(bld_netmdport_iter(hp));
  case vpiNetBit: case vpiRegBit: case vpiVarSelect:
   /* iterator is usually the one port the bit connects to */
   /* this returns port bit handles for the one bit */
   return(bld_netbitmdport_iter(hp));
  default:
   __vpi_err(1861, vpiError,
    "vpiPort 1-to-many iterator from %s illegal - for in module or hiconn module ports",
    __to_vpionam(__wrks1, hp->hrec->htyp));
  }  
 return(NULL);
}

/*
 * build ports in module iterator (easiest)
 * since in module and have inst. do not need parent handle 
 */
static vpiHandle bld_inmod_port_iter(struct h_t *hp)
{
 int32 pi;
 struct h_t *hp2;
 struct hrec_t *hrp2; 
 struct mod_t *mdp;
 t_midat *idp; 
 struct pviter_t *iterp;
 vpiHandle ihref;

 idp = hp->hin_idp;
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 if (mdp->mpnum <= 0) return(NULL);
 iterp = __alloc_empty_iter(mdp->mpnum, &ihref);
 __iter_fill_with_empty(iterp);
 for (pi = 0; pi < mdp->mpnum; pi++)
  {
   hp2 = iterp->scanhptab[pi];
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiPort;
   /* using index so can get instance port index too */
   hrp2->hu.hpi = pi;
   hp2->hin_idp = idp;
  }
 return(ihref);
}

/*
 * build a statement iterator from a named or unnamed? block 
 * unnamed blocks usually marked with bit (but S_UNLBK in fork-join) 
 */
extern vpiHandle __bld_stmt_iterator(struct h_t *hp)
{
 struct hrec_t *hrp;
 struct st_t *stp;
 struct task_t *tskp;

 if (hp == NULL) return(__nil_iter_err(vpiStmt));
 hrp = hp->hrec;
 switch (hrp->htyp) {
  case vpiFork:
   return(bld_fjlist_iter(hrp->hu.hstp, hp->hin_idp, hrp->hin_tskp));

  case vpiBegin:
   stp = hrp->hu.hstp;
   /* this statement only for use in fork-join */
   if (stp->stmttyp == S_UNBLK)
    {
     /* pass first statement of block */
     stp = stp->st.sbsts;
     /* here iterator is in same scope as unnamed block */
     return(bld_listofstmts_iter(stp, hp->hin_idp, hrp->hin_tskp));
    }
   if (!stp->st_unbhead) __vpi_terr(__FILE__, __LINE__);
   /* normal un-named block just has bit set in first statement */
   return(bld_listofstmts_iter(stp, hp->hin_idp, hrp->hin_tskp));

  case vpiNamedFork:
   tskp = hrp->hu.htskp;
   return(bld_fjlist_iter(tskp->tskst, hp->hin_idp, tskp));
   
  case vpiNamedBegin:
   tskp = hrp->hu.htskp;
   /* here these are in the named block scope not the task stmt */
   /* notice hin taskp is name block task itself */
   return(bld_listofstmts_iter(tskp->tskst, hp->hin_idp, tskp));
  default:
   __vpi_err(1869, vpiError,
    "vpiStmt 1-to-many iterator from %s illegal - for blocks only",
   __to_vpionam(__wrks1, hrp->htyp));
 }  
 return(NULL);
}

/*
 * build a fork-join iterator - each statement from list
 */
static vpiHandle bld_fjlist_iter(struct st_t *stp, t_midat *idp,
 struct task_t *tskp)
{
 int32 si, fji, snum;
 struct st_t *fjstp;
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct h_t *hp;
 struct hrec_t *hrp; 
 struct st_t *stp3;

 /* these do not go into iterators */
 for (snum = fji = 0;; fji++)
  {
   if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;

   /* DBG remove -- */
   /* think can not have goto here */
   if (fjstp->rl_stmttyp == S_GOTO) __vpi_terr(__FILE__, __LINE__); 
   /* -- */
   /* SJM 09/24/01 - for these inserted stmts, add next to iterator */
   if (fjstp->rl_stmttyp == S_REPSETUP || fjstp->rl_stmttyp == S_FORASSGN
    || fjstp->rl_stmttyp == S_REPDCSETUP) fjstp = fjstp->stnxt;
   snum++;
  }

 /* LOOKATME - can this be none */
 if (snum <= 0) return(NULL);

 iterp = __alloc_empty_iter(snum, &ihref);
 __iter_fill_with_empty(iterp);
 for (fji = 0, si = 0;; fji++, si++)
  {
   if ((fjstp = stp->st.fj.fjstps[fji]) == NULL) break;

   /* these do not go into iterator */
   /* SJM 09/24/01 - for these inserted stmts, add next to iterator */
   if (fjstp->rl_stmttyp == S_REPSETUP || fjstp->rl_stmttyp == S_FORASSGN
    || fjstp->rl_stmttyp == S_REPDCSETUP) fjstp = fjstp->stnxt;

   hp = iterp->scanhptab[si];
   stp3 = fjstp;
   hrp = hp->hrec;
   hrp->htyp = __to_vpi_stmttyp(&stp3);

   /* skipping special setup stmts, no need to use next */
   if (hrp->htyp == vpiNamedBegin || hrp->htyp == vpiNamedFork)
    hrp->hu.htskp = fjstp->st.snbtsk;
   else hrp->hu.hstp = fjstp;

   hp->hin_idp = idp;
   hrp->hin_tskp = tskp;
  }
 return(ihref);
}

/*
 * build statement iterator from the first statement
 */
static vpiHandle bld_listofstmts_iter(struct st_t *stp, t_midat *idp,
 struct task_t *in_tskp)
{
 int32 si, snum;
 struct st_t *stp2;
 struct hrec_t *hrp; 
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct h_t *hp;
 struct st_t *stp3;

 for (snum = 0, stp2 = stp; stp2 != NULL; stp2 = stp2->stnxt)
  {
   if (stp2->rl_stmttyp == S_GOTO) break;
   if (stp2->rl_stmttyp == S_REPSETUP || stp2->rl_stmttyp == S_FORASSGN
    || stp2->rl_stmttyp == S_REPDCSETUP) continue;
   snum++;
  }
 /* LOOKATME - can this be none */
 if (snum <= 0) return(NULL);
 iterp = __alloc_empty_iter(snum, &ihref);
 __iter_fill_with_empty(iterp);
 for (stp2 = stp, si = 0; stp2 != NULL; stp2 = stp2->stnxt)  
  {
   if (stp2->rl_stmttyp == S_GOTO) break;
   /* these do not go into iterators */
   if (stp2->rl_stmttyp == S_REPSETUP || stp2->rl_stmttyp == S_FORASSGN
    || stp2->rl_stmttyp == S_REPDCSETUP)
    continue;

   /* his works for named begin and fj blocks because hu if statement */
   /* links in d.s. for going between 2 */
   hp = iterp->scanhptab[si++];
   hrp = hp->hrec;
   /* know will never be for assign or repeat where need to move to nxt */
   stp3 = stp2;
   hrp->htyp = __to_vpi_stmttyp(&stp3);

   /* skipping special setup stmts, no need to use next */
   if (hrp->htyp == vpiNamedBegin || hrp->htyp == vpiNamedFork)
    hrp->hu.htskp = stp2->st.snbtsk;
   else hrp->hu.hstp = stp2;

   hp->hin_idp = idp;
   hrp->hin_tskp = in_tskp;
  }
 return(ihref);
}

/*
 * convert from v.h stmt type to handle constant for stmt class
 *
 * tricky because for for assign and repeat setup added pseudo
 * statements must move to next and return type of next, i.e. the repeat
 * or for statement itself 
 *
 * here ignore unnamed block header since know only called for block contents
 */
extern word32 __to_vpi_stmttyp(struct st_t **stpp)
{
 struct task_t *tskp;
 struct st_t *stp;
 
 stp = *stpp;
 switch ((byte) stp->stmttyp) {
  /* blocks statements */
  case S_NAMBLK:
   /* use task type for statement type */
   tskp = stp->st.snbtsk;
   if (tskp->tsktyp == FORK) return(vpiNamedFork);
   if (tskp->tsktyp == Begin) return(vpiNamedBegin);
   __vpi_terr(__FILE__, __LINE__); 
   break;
  case S_UNBLK: return(vpiBegin);
  /* the statement is the header that points to the contents fj stlst */
  case S_UNFJ: return(vpiFork);

  /* atomic statements */
  case S_IF: 
   if (stp->st.sif.elsest == NULL) return(vpiIf);
   return(vpiIfElse);
//AIV FIXME AIV WHILE - vpiBreak/vpiContinue??
  case S_DO_WHILE: return(0);
  case S_WHILE: return(vpiWhile);
  case S_FOREVER: return(vpiForever);
  case S_REPEAT: return(vpiRepeat);
  case S_WAIT: return(vpiWait);
  case S_CASE: return(vpiCase);
  case S_FOR: return(vpiFor);
  case S_REPDCSETUP:
   *stpp = stp->stnxt;
   /* DBG remove --- */
   if (stp->stnxt == NULL) __vpi_terr(__FILE__, __LINE__);
   if (stp->stnxt->stmttyp == S_FORASSGN || stp->stnxt->stmttyp == S_REPSETUP
    || stp->stnxt->stmttyp == S_REPDCSETUP)
    __vpi_terr(__FILE__, __LINE__);
   /* --- */
   /* this is always assign mayhbe non blocking or rhs dctrl */
   return(vpiAssignment);
  case S_DELCTRL:
   if (stp->st.sdc->dctyp == DC_DELAY) return(vpiDelayControl);
   if (stp->st.sdc->dctyp == DC_EVENT) return(vpiEventControl);
   if (stp->st.sdc->dctyp == DC_RHSEVENT ||
    stp->st.sdc->dctyp == DC_RHSDELAY) return(vpiAssignment);
   __vpi_terr(__FILE__, __LINE__);
   break;
  case S_CAUSE: return(vpiEventStmt);
  /* properties in vpi_ distinguish */
//AIV FIXME - AIV INC - vpiInc???????
  case S_INC: case S_DEC:
  case S_PROCA: case S_NBPROCA: case S_RHSDEPROCA:
   return(vpiAssignment);
  case S_FORASSGN:
   /* need the following for - always followed by for */
   *stpp = stp->stnxt;
   /* DBG remove --- */
   if (stp->stnxt == NULL) __vpi_terr(__FILE__, __LINE__);
   if (stp->stnxt->stmttyp == S_FORASSGN || stp->stnxt->stmttyp == S_REPSETUP
    || stp->stnxt->stmttyp == S_REPDCSETUP)
    __vpi_terr(__FILE__, __LINE__);
   /* --- */
   return(vpiFor);
  case S_REPSETUP:
   *stpp = stp->stnxt;
   /* DBG remove --- */
   if (stp->stnxt == NULL) __vpi_terr(__FILE__, __LINE__);
   if (stp->stnxt->stmttyp == S_FORASSGN || stp->stnxt->stmttyp == S_REPSETUP
    || stp->stnxt->stmttyp == S_REPDCSETUP)
    __vpi_terr(__FILE__, __LINE__);
   /* --- */
   return(vpiRepeat);
  case S_QCONTA:
   if (stp->st.sqca->qcatyp == ASSIGN) return(vpiAssignStmt);
   if (stp->st.sqca->qcatyp == FORCE) return(vpiForce);
   __vpi_terr(__FILE__, __LINE__);
   break;
  case S_QCONTDEA:
   if (stp->st.sqcdea.qcdatyp == DEASSIGN) return(vpiRelease);
   if (stp->st.sqcdea.qcdatyp == RELEASE) return(vpiDeassign);
   __vpi_terr(__FILE__, __LINE__);
   break;
  case S_DSABLE: return(vpiDisable);
  case S_FUNCCALL: return(vpiFuncCall);
  case S_TSKCALL:
   if (stp->st.stkc.tsksyx->lu.sy->sytyp == SYM_STSK) return(vpiSysTaskCall);
   return(vpiTaskCall);
//AIV FIXME AIV LOOP - vpiBreak/vpiContinue??
  case S_CONTINUE: 
  case S_BREAK:
  case S_RETURN:
   return(0);

  case S_NULL: case S_STNONE: return(vpiNullStmt);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(0);
}

/*
 * build the top level all vpi_ systf iterator
 *
 * original handles build from systf register not freeable but this
 * iterator is
 * notice only thing can do with handles in itertor is get systf info
 */
extern vpiHandle __bld_systf_iterator(struct h_t *hp)
{
 int32 ti, num_vpi_systfs;
 struct hrec_t *hrp2; 
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct h_t *hp2;

 if (hp != NULL)
  {
   __vpi_err(1866, vpiError,
    "vpi_iterate for vpiUserSystf requires NULL handle - %s illegal",
    __to_vpionam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 num_vpi_systfs = __last_systf - __last_veriusertf;
 if (num_vpi_systfs <= 0) return(NULL);
 iterp = __alloc_empty_iter(num_vpi_systfs, &ihref);
 __iter_fill_with_empty(iterp);
 for (ti = 0; ti < num_vpi_systfs; ti++)
  {
   hp2 = iterp->scanhptab[ti];
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiUserSystf;
   /* handle must be number (i.e. 1000 + tf_ number + pos.) */ 
   hrp2->hi = __last_veriusertf + ti + 1; 
   /* this handle does not have itree loc. since not the call */
  }
 return(ihref);
}

/*
 * build task or function including system argument list iterator
 */
extern vpiHandle __bld_tfargexpr_iterator(struct h_t *hp)
{
 struct hrec_t *hrp;
 struct expr_t *argxp;
 struct tskcall_t *tkcp;

 if (hp == NULL) return(__nil_iter_err(vpiArgument));
 hrp = hp->hrec;
 switch (hrp->htyp) {
  /* for func def. first argment is return value but for call 1st is arg */
  case vpiFuncCall: case vpiSysFuncCall:
   argxp = hrp->hu.hxp->ru.x;
   if (argxp == NULL) return(NULL);
   return(bld_listofexprs_iter(argxp, hp->hin_idp, hrp->hin_tskp));
  case vpiTask: case vpiSysTaskCall:
   tkcp = &(hrp->hu.hstp->st.stkc);
   if (tkcp->targs == NULL) return(NULL);
   return(bld_listofexprs_iter(tkcp->targs, hp->hin_idp, hrp->hin_tskp));
  default:
   __vpi_err(1879, vpiError,
    "vpiArgument 1-to-many iterator from %s illegal - for tasks and functions",
   __to_vpionam(__wrks1, hrp->htyp));
 }
 return(NULL);
}

/*
 * build list of expressions iterator (know at least one or not called)
 * passed with first arg - can be nil for no arguments
 */
static vpiHandle bld_listofexprs_iter(struct expr_t *argx, t_midat *idp,
 struct task_t *tskp)
{
 int32 xi, numxps;
 struct expr_t *xp2;
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct h_t *hp;

 /* know there will always be 1 */
 for (numxps = 0, xp2 = argx; xp2 != NULL; xp2 = xp2->ru.x) numxps++;
 if (numxps <= 0) return(NULL);
 iterp = __alloc_empty_iter(numxps, &ihref);
 __iter_fill_with_empty(iterp);
 for (xp2 = argx, xi = 0; xp2 != NULL; xp2 = xp2->ru.x, xi++) 
  {
   hp = iterp->scanhptab[xi];
   /* expr. object can also be scopes if xmr object */
   mk2_exprclass_handle(hp, xp2->lu.x, idp, tskp);
  }
 return(ihref);
}

/*
 * ROUTINES TO BUILD TCHK AND PATH ITERATORS
 */

/*
 * build a module specify path iterator (indices and three types)
 */
extern vpiHandle __bld_pthterm_iterator(struct h_t *hp, word32 itype)
{
 int32 pi, numpes;
 struct hrec_t *hrp2; 
 struct spcpth_t *pthp;
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct h_t *hp2;
 struct hrec_t *hrp;
 struct expr_t *xp;

 hrp = hp->hrec;
 if (hrp->htyp != vpiModPath)
  {
   __vpi_err(1858, vpiError,
    "%s 1-to-many iterator requires vpiModPath reference handle - %s illegal",
    __to_vpionam(__wrks1, itype), __to_vpionam(__wrks2, hrp->htyp));
   return(NULL);
  }
 pthp = hrp->hu.hpthp;
 if (itype == vpiModPathIn || itype == vpiModPathOut)
  { 
   if (itype == vpiModPathIn) numpes = pthp->last_pein + 1;
   else numpes = pthp->last_peout + 1;
   goto bld_iter;
  }
 /* know itype already checked */ 
 /* DBG remove --- */ 
 if (itype != vpiModDataPathIn) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 
 if ((xp = pthp->datasrcx) == NULL) return(NULL);

 if (xp->optyp != FCCOM) numpes = 1;
 /* FCCOM list */
 else { for (numpes = 0; xp != NULL; xp = xp->ru.x) numpes++; }

bld_iter:
 if (numpes <= 0) return(NULL);
 iterp = __alloc_empty_iter(numpes, &ihref);
 __iter_fill_with_empty(iterp);
 for (pi = 0; pi < numpes; pi++)
  {
   hp2 = iterp->scanhptab[pi];
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiPathTerm;
   hrp2->htyp2 = itype;
   hrp2->hu.hpthp = pthp;
   /* this is index, path term type determines how accessed */
   hrp2->hi = pi;
   hp2->hin_idp = hp->hin_idp;
  }
 return(ihref);
}   

/*
 * routine to build iterator of vpi Tchk Terms that a net or bit is in
 *
 * notifier's not included since not really part of circuit (modeling addon)
 * and no a terminal
 * tchk terminals must be wires but not necessarily I/O ports
 */
extern vpiHandle __bld_netin_tchkterms(struct h_t *hp)
{
 int32 hi, ndx, nterms;
 struct hrec_t *hrp;
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 if (hp == NULL) return(__nil_iter_err(vpiTchkTerm));
 hrp = hp->hrec;
 if (hrp->htyp != vpiNet && hrp->htyp != vpiNetBit)
  {
bad_bit:
   __vpi_err(1872, vpiError,
    "vpiTchkTerm 1-to-many iterator from %s illegal - vpiNet or constant vpiNetBit only",
    __to_vpionam(__wrks1, hrp->htyp));
   return(NULL);
  }
 if (hrp->htyp == vpiNetBit)
  {
   if (!hrp->bith_ndx) goto bad_bit;
   ndx = hrp->hi;
  }
 else ndx = -1;
 np = hrp->hu.hnp;

 nterms = bld_net_tchkterms(np, hp->hin_idp, ndx);
 if (nterms <= 0) return(NULL);

 iterp = __alloc_empty_iter(nterms, &ihref);
 for (hi = 0; hi < nterms; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * build timing check terminals connected to net index ndx 
 *
 * -1 for all of wire
 */
static int32 bld_net_tchkterms(struct net_t *np, t_midat *idp, int32 ndx)
{
 int32 cnt;
 struct net_pin_t *npp; 
 struct h_t *hp2;
 struct hrec_t *hrp2; 
 struct tchk_t *tcp;
 struct tchg_t *tchgp;
 decl_idp_locals_;

 set_save_idp_(idp);
 /* for net bit, if any bit in range then entire terminal */
 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_TCHG) continue;

   /* will be one for each event, since just need tchk use only start ev */
   if (npp->chgsubtyp != NPCHG_TCSTART) continue;

   /* know tchk terminals are wires or selects (not globals) */
   tchgp = npp->elnpp.etchgp;
   tcp = tchgp->chgu.chgtcp;
   if (termexpr_matches(tcp->startxp, np, ndx))
    {
     /* SJM 06-22-10 - this force alloc if first time empty */
     if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);

     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hp2->hin_idp = idp;

     /* not using alloc iter so need to set in iter bit explicitly */
     hrp2 = hp2->hrec;
     hrp2->in_iter = TRUE;
     hrp2->htyp = vpiTchkTerm;
     hrp2->htyp2 = vpiTchkRefTerm;
     hrp2->hu.htcp = tcp; 
     /* only need to set cross link in newly added one */
     hp2->hrec = hrp2;
    }
   if (termexpr_matches(tcp->chkxp, np, ndx))
    {
     /* SJM 06-22-10 - this force alloc if first time empty */
     if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);

     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hp2->hin_idp = idp;

     hrp2 = hp2->hrec;
     hrp2->in_iter = TRUE;
     hrp2->htyp = vpiTchkTerm;
     hrp2->htyp2 = vpiTchkDataTerm;
     hrp2->hu.htcp = tcp; 
    }
  }
 restore_idp_();
 return(cnt);
}

/*
 * return T if term matches net and bit (ndx == -1 for all)
 *
 * this require itree context to be pushed onto itstk
 */
static int32 termexpr_matches(struct expr_t *xp, struct net_t *np, int32 ndx)
{
 int32 bi1, bi2;
 struct net_t *np2;

 if (xp == NULL) return(FALSE);
 if (xp->optyp == ID)
  {
   if (xp->lu.sy->el.enp == np) return(TRUE);
   return(FALSE);
  }
 if (xp->optyp == LSB)
  {
   np2 = xp->lu.x->lu.sy->el.enp;
   if (np != np2) return(FALSE);
   if (ndx == -1) return(TRUE);
   bi1 = __comp_ndx(np, xp->ru.x);
   if (bi1 == ndx) return(TRUE);
   return(FALSE);
  }
 else if (xp->optyp == PARTSEL)
  {
   np2 = xp->lu.x->lu.sy->el.enp;
   if (np != np2) return(FALSE);
   if (ndx == -1) return(TRUE);
   bi1 = (int32) __contab[xp->ru.x->lu.x->ru.xvi];
   bi2 = (int32) __contab[xp->ru.x->ru.x->ru.xvi];
   if (ndx > bi1 || ndx < bi2) return(FALSE);
   return(TRUE);
  }
 else if (xp->optyp == PARTSEL_NDX_PLUS || xp->optyp == PARTSEL_NDX_MINUS)
  {
   np2 = __get_indexed_psel_range(xp, &bi1, &bi2);
   if (np != np2) return(FALSE);
   if (ndx == -1) return(TRUE);
   if (ndx > bi1 || ndx < bi2) return(FALSE);
   return(TRUE);
  }
 else __vpi_terr(__FILE__, __LINE__);
 return(FALSE);
}

/*
 * grow global work handle table (must add at least addnum)
 */
extern void __grow_hptab(int32 addnum)
{
 int32 iti, nnum;
 size_t old_ithtsiz, osize, nsize;

 /* only allocate if accessing driver/load style handles at all */ 
 if (__ithtsiz == 0)
  {
   nnum = 1000 + addnum;
   __ithptab = (struct h_t **) __my_malloc(nnum*sizeof(struct h_t *));
   __ithtsiz = nnum; 
   /* set new elements to nil so will alloc the h_t rec */
   for (iti = 0; iti < __ithtsiz; iti++) __ithptab[iti] = NULL;
   return;
  }
 old_ithtsiz = __ithtsiz;
 osize = old_ithtsiz*sizeof(struct h_t *);
 __ithtsiz = addnum + (3*__ithtsiz)/2; 
 nsize = __ithtsiz*sizeof(struct h_t *);
 __ithptab = (struct h_t **) __my_realloc(__ithptab, osize, nsize);

 /* SJM 06-22-10 - the iterator tab is now just ptrs to h_t recs */
 /* set new ones to pt to nil */
 for (iti = old_ithtsiz; iti < __ithtsiz; iti++) __ithptab[iti] = NULL;
}

/*
 * grow 2nd for subtree processing  global work handle table
 */
extern void __grow_hptab2(int32 addnum)
{
 int32 iti;
 int32 nnum;
 size_t old_ithtsiz2, osize, nsize;

 /* only allocate if accessing driver/load style handles at all */ 
 if (__ithtsiz2 == 0)
  {
   nnum = 1000 + addnum;
   __ithptab2 = (struct h_t **) __my_malloc(nnum*sizeof(struct h_t *));
   __ithtsiz2 = nnum; 
   /* set new elements to nil so will alloc the h_t rec */
   for (iti = 0; iti < __ithtsiz2; iti++) __ithptab2[iti] = NULL;
   return;
  }
 old_ithtsiz2 = __ithtsiz2;
 osize = old_ithtsiz2*sizeof(struct h_t *);
 __ithtsiz2 = addnum + (3*__ithtsiz2)/2; 
 nsize = __ithtsiz2*sizeof(struct h_t *);
 __ithptab2 = (struct h_t **) __my_realloc(__ithptab2, osize, nsize);

 /* SJM 06-22-10 - the iterator tab is now just ptrs to h_t recs */
 /* set new ones to pt to nil */
 for (iti = old_ithtsiz2; iti < __ithtsiz2; iti++) __ithptab2[iti] = NULL;
}

/*
 * routine to build iterator of vpi path src and dst terms net is in
 * 
 * vpiModDataPathTerm not include since not path source or dest (cond.)
 * paths must be wires that are input/inout (source) and output/inout (dest)  
 *
 * path terms must be wires since input/inout are lvalues and path
 * destinations need delays so must be wire
 */
extern vpiHandle __bld_netin_pthterms(struct h_t *hp)
{
 int32 hi, ndx, nterms;
 struct hrec_t *hrp; 
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 if (hp == NULL) return(__nil_iter_err(vpiPathTerm));
 hrp = hp->hrec;
 if (hrp->htyp != vpiNet && hrp->htyp != vpiNetBit)
  {
bad_bit:
   __vpi_err(1873, vpiError,
    "vpiPathTerm 1-to-many iterator from %s illegal - vpiNet or vpiNetBit (constant) only",
    __to_vpionam(__wrks1, hrp->htyp));
   return(NULL);
  }
 np = hrp->hu.hnp;
 if (hrp->htyp == vpiNetBit)
  {
   /* know this is T unless variable select - only works for constants */
   if (!hrp->bith_ndx) goto bad_bit;  
   ndx = hrp->hi; 
  }
 else ndx = -1;

 nterms = bld_net_pathterms(np, hp->hin_idp, ndx);
 if (nterms <= 0) return(NULL);

 iterp = __alloc_empty_iter(nterms, &ihref);
 for (hi = 0; hi < nterms; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
} 

/*
 * build path terminals connected to net index ndx 
 *
 * ndx -1 for all of wire
 * on path sources and destinations here 
 */
static int32 bld_net_pathterms(struct net_t *np, t_midat *idp, int32 ndx)
{
 int32 bi, pei;
 int32 cnt, fr, to;
 struct net_pin_t *npp; 
 struct pthdst_t *pdp;
 struct hrec_t *hrp2; 
 struct h_t *hp2;
 struct h_t tmph;
 struct hrec_t tmphrec;
 struct tchg_t *tchgp;
 struct spcpth_t *pthp;
 struct pathel_t *pep;

 /* for net bit, if any bit in range then entire source terminal */
 /* first path sources - from path source load */
 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_TCHG) continue;
   /* will be one for each event, since just need tchk use only start ev */
   if (npp->chgsubtyp != NPCHG_PTHSRC) continue;

   /* know tchk terminals are wires or selects (not globals) */
   tchgp = npp->elnpp.etchgp;
   pthp = tchgp->chgu.chgpthp;
   for (pei = 0; pei <= pthp->last_pein; pei++)
    {
     pep = &(pthp->peins[pei]);
     if (np != pep->penp) continue;
     if (ndx != -1 && pep->pthi1 != -1 &&
      (ndx > pep->pthi1 || ndx < pep->pthi2)) continue;

     if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hp2->hin_idp = idp;

     hrp2 = hp2->hrec;
     hrp2->in_iter = TRUE;
     hrp2->htyp = vpiModPathIn;
     hrp2->hu.hpthp = pthp;
     hrp2->hi = pei;
     /* only need to set cross link in newly added one */
     hp2->hrec = hrp2;
    }
  }
 /* path destinations (if any) are linked on wire */
 if (np->n_isapthdst)
  {
   if (ndx == -1) { fr = 0; to = np->nwid - 1; } else fr = to = ndx;
   for (bi = fr; bi <= to; bi++) 
    {
     pdp = np->nu.rngdwir->n_du.pb_pthdst[bi];
     for (; pdp != NULL; pdp = pdp->pdnxt)
      {
       pthp = pdp->pstchgp->chgu.chgpthp;
       for (pei = 0; pei <= pthp->last_peout; pei++)
        {
         pep = &(pthp->peouts[pei]);
         if (ndx != -1 && pep->pthi1 != -1 &&
          (ndx > pep->pthi1 || ndx < pep->pthi2)) continue;

         /* SJM 06-22-10 - need a dummy h_t rec for handle compare */
         __init_hrec(&tmphrec);
         tmphrec.htyp = vpiModPathOut;
         tmphrec.hu.hpthp = pthp;
         tmphrec.hi = pei;
         tmph.hrec = &(tmphrec);
         tmph.hin_idp = idp;
         /* need to set in iter bit */
         tmphrec.in_iter = TRUE;

         /* if duplicated do not add */
         if (cnt != 0 && same_vpi_handle(__ithptab, 0, cnt, &tmph, &tmphrec))
          continue;

         if (cnt >= __ithtsiz) __grow_hptab(cnt - __ithtsiz + 1);
         hp2 = __get_new_hp_handle();
         __ithptab[cnt++] = hp2;
         hp2->hin_idp = tmph.hin_idp;
         memcpy(hp2->hrec, &(tmphrec), sizeof(struct hrec_t));
        }
      }
    }
  }
 return(cnt);
}

/*
 * build a delay expression iterator - this is value that appears in source
 *
 * except in cver returns expression of the latest back annotated value
 * not the original source
 *
 * FIXME - for vpiDelayControl should be one to one expr op. not iterator?
 */
extern vpiHandle __bld_delay_expr_iter(struct h_t *rhp)
{
 int32 hi;
 int32 ndels, ndels2;
 vpiHandle ihref;
 struct hrec_t *rhrp;
 struct h_t *tmphp;
 struct gate_t *gp;
 struct spcpth_t *pthp;
 struct tchk_t *tcp;
 struct delctrl_t *dctp;
 struct pviter_t *iterp;

 rhrp = rhp->hrec;
 switch (rhrp->htyp) {
  /* need the 3 cleass elements not the class name here */
  case vpiGate: case vpiUdp: case vpiSwitch:
   gp = rhrp->hu.hgp;     
   if (gp->g_delrep == DT_NONE) return(NULL);
   ndels = bld_delay_iter(gp->g_du, gp->g_delrep, rhp->hin_idp,
    rhrp->hin_tskp);
   break;
  case vpiModPath:
   pthp = rhrp->hu.hpthp;
   if (pthp->pth_delrep == DT_NONE) __vpi_terr(__FILE__, __LINE__);
   ndels = bld_delay_iter(pthp->pth_du, pthp->pth_delrep, rhp->hin_idp,
    rhrp->hin_tskp);
   break;
  case vpiTchk:
   tcp = rhrp->hu.htcp;
   if (tcp->tc_delrep == DT_NONE) __vpi_terr(__FILE__, __LINE__);
   ndels = bld_delay_iter(tcp->tclim_du, tcp->tc_delrep, rhp->hin_idp,
    rhrp->hin_tskp);
   if (ndels != 1) __vpi_terr(__FILE__, __LINE__);
   /* SJM 06-22-10 - now possible reversing is just changing ptrs */
   tmphp = __ithptab[0];
   if (tcp->tc_haslim2)
    {
     if (tcp->tc_delrep2 == DT_NONE) __vpi_terr(__FILE__, __LINE__);
     ndels2 = bld_delay_iter(tcp->tclim2_du, tcp->tc_delrep2, rhp->hin_idp,
      rhrp->hin_tskp);
     if (ndels2 != 1) __vpi_terr(__FILE__, __LINE__);

     /* SJM 06-22-10 - just reverse ptrs for new style order change */
     /* know already built and filled - just in wrong order */
     __ithptab[0] = __ithptab[1];
     __ithptab[1] = tmphp;
     ndels = 2;
    }
   break;
  case vpiDelayControl:
   dctp = rhrp->hu.hstp->st.sdc;
   if (dctp->dctyp != DC_DELAY && dctp->dctyp != DC_RHSDELAY) 
    __vpi_terr(__FILE__, __LINE__);
   if (dctp->dc_delrep == DT_NONE) __vpi_terr(__FILE__, __LINE__);
   ndels = bld_delay_iter(dctp->dc_du, dctp->dc_delrep, rhp->hin_idp,
    rhrp->hin_tskp);
   if (ndels != 1) __vpi_terr(__FILE__, __LINE__);
   break;
  default:
   __vpi_err(1838, vpiError,
    "vpiDelay 1-to-many (iterator) method illegal for %s object",
    __to_vpionam(__wrks1, rhp->hrec->htyp));
   return(NULL);
  }
 /* DBG remove --- */
 if (ndels <= 0) __vpi_terr(__FILE__, __LINE__);
 /* --- */

 iterp = __alloc_empty_iter(ndels, &ihref);
 for (hi = 0; hi < ndels; hi++)
   {
    iterp->scanhptab[hi] = __ithptab[hi];
    __ithptab[hi] = NULL;
   }
 return(ihref);
}

/*
 * fill it htab work iterator with delay expressions 
 *
 * not called for DT_NONE
 */
static int32 bld_delay_iter(union del_u du, word32 drep, t_midat *idp,
 struct task_t *tskp)
{
 int32 i;
 int32 ndels;
 word64 tim[12], timval;
 struct mod_t *mdp;
 struct h_t tmph;
 struct hrec_t tmphrec, *hrp2;
 struct h_t *hp2;
 struct expr_t *xp;
 struct xstk_t *xsp;
 decl_idp_locals_;

 /* for expressions, value is same as source (not ticks) */
 if (drep == DT_1X)
  {
   if (__ithtsiz <= 1) __grow_hptab(1); 

   tmph.hrec = &(tmphrec); 
   mk2_exprclass_handle(&tmph, du.d1x, idp, tskp);
   tmphrec.in_iter = TRUE; 

   hp2 = __get_new_hp_handle();
   __ithptab[0] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   memcpy(hp2->hrec, &(tmphrec), sizeof(struct hrec_t)); 
   return(1);
  }
 if (drep == DT_4X)
  {
   if (__ithtsiz <= 3) __grow_hptab(3);
   tmph.hrec = &(tmphrec); 
   mk2_exprclass_handle(&(tmph), du.d4x[0], idp, tskp);
   tmphrec.in_iter = TRUE; 

   hp2 = __get_new_hp_handle();
   __ithptab[0] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   memcpy(hp2->hrec, &(tmphrec), sizeof(struct hrec_t)); 

   tmph.hrec = &(tmphrec); 
   mk2_exprclass_handle(&tmph, du.d4x[1], idp, tskp);
   tmphrec.in_iter = TRUE; 

   hp2 = __get_new_hp_handle();
   __ithptab[1] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   memcpy(hp2->hrec, &(tmphrec), sizeof(struct hrec_t)); 

   tmph.hrec = &(tmphrec); 
   mk2_exprclass_handle(&tmph, du.d4x[2], idp, tskp);
   tmphrec.in_iter = TRUE; 

   hp2 = __get_new_hp_handle();
   __ithptab[2] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   memcpy(hp2->hrec, &(tmphrec), sizeof(struct hrec_t)); 

   /* 4x for in source expression has only 3 values (no to x) */
   return(3);
  }
 /* all other cases are constants - reconstruct source assuming no anotate */ 
 set_save_idp_(idp);
 mdp = (struct mod_t *) idp[MD_MDP];
 /* non expr. case, return as internal ticks constants */
 __extract_delval(tim, &ndels, du, drep);
 /* no t vpi time record here - always convert to number appearing in src */
 if (ndels > 0 && !mdp->mno_unitcnv)
  {
   for (i = 0; i < ndels; i++)
    {
     __cnv_ticks_tonum64(&timval, tim[i], mdp);
     tim[i] = timval;
    }
  }
 for (i = 0; i < ndels; i++)
  {
   if (i >= __ithtsiz) __grow_hptab(1);

   /* create expresion for each delay and store in constant table for */
   /* module type of instance */
   xp = __sim_alloc_newxnd();
   xp->szu.xclen = TIMEBITS;
   xp->optyp = NUMBER;

   /* AIV 08/25/09 - this needs to push bits - 64 not 2 */
   /* also needs to handle 64-bit case */
   push_xstk_(xsp, 64);
#ifdef __CVC32__
   xsp->ap[0] = (word32) (tim[i] & WORDMASK_ULL);
   xsp->ap[1] = (word32) ((tim[i] >> 32) & WORDMASK_ULL);
   xsp->bp[0] = 0L;
   xsp->bp[1] = 0L;
   xp->ru.xvi = __allocfill_cval_new(xsp->ap, xsp->bp, 2);
#else
   xsp->ap[0] = tim[i];
   xsp->bp[0] = 0L;
   xp->ru.xvi = __allocfill_cval_new(xsp->ap, xsp->bp, 1);
#endif
   __pop_xstk();

   hp2 = __get_new_hp_handle();
   __ithptab[i] = hp2;
   hp2->hin_idp = idp;

   /* fill the hrec */
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;
   hrp2->htyp = vpiConstant;
   hrp2->hu.hxp = xp;
   hrp2->hin_tskp = tskp;
   /* because in iter can not be freed but copied needs free xpr on */
   hrp2->free_xpr = TRUE;
  }
 restore_idp_();
 return(ndels);
}

/*
 * ROUTINES TO BUILD ATTRIBUTE ITERATOR
 */

/*
 * build the attr_spec iterators
 */
extern vpiHandle __bld_dig_attr_iter(struct h_t *hp)
{
 struct net_t *np;
 struct gate_t *gp;
 struct inst_t *ip;
 struct itree_t *itp;
 struct mod_t *mdp;
 struct hrec_t *hrp;

 if (hp == NULL) return(__nil_iter_err(vpiAttribute));

 hrp = hp->hrec;
 switch (hp->hrec->htyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
  case vpiNamedEvent: case vpiRealVar:
  /* LOOKATME - is this defined in LRM - think so */
  case vpiMemory:
   np = hrp->hu.hnp;
   if (np->nattrs == NULL) return(NULL);
   return(bld_dig_attrlist_iter(hp, np->nattrs));
  case vpiModule:
   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   ip = itp->itip;
   mdp = ip->imsym->el.emdp;

   /* if dig attr attached to inst use it */  
   if (ip->iattrs != NULL) return(bld_dig_attrlist_iter(hp, ip->iattrs));
   /* otherwise return mod attrs from mod */
   if (mdp->mattrs == NULL) return(NULL);
   return(bld_dig_attrlist_iter(hp, mdp->mattrs));
  case vpiGate: case vpiSwitch: case vpiUdp:
   gp = hrp->hu.hgp;
   if (gp->gattrs == NULL) return(NULL);
   return(bld_dig_attrlist_iter(hp, gp->gattrs));
  case vpiPort:
   __vpi_err(2113, vpiNotice,
    "vpiAttribute 1-to-many iterator for %s empty - attached to net",
    __to_vpionam(__wrks1, hp->hrec->htyp));
   return(NULL);
  default:
   __vpi_err(2032, vpiWarning,
    "vpiAttribute 1-to-many iterator for %s empty - attribute not yet stored",
    __to_vpionam(__wrks1, hp->hrec->htyp));
  }  
 return(NULL);
}

/*
 * get object that is parent of attribute 
 *
 * trick is storing digital attribute as object but offset count to
 * object's attribute record so using htyp2 as parent object htyp
 */
extern vpiHandle __get_digattr_parent(struct h_t *hp)
{
 struct h_t *hp2;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 hp2 = (struct h_t *) __mk_handle(hrp->htyp2, (void *) hrp->hu.hanyp,
  hp->hin_idp, hrp->hin_tskp);
 return((vpiHandle) hp2);
}

/*
 * build an attribute iterator of otyp objects from one attr table
 *
 * FIXME - should store as table so can access value using index not
 * list search 
 */
static vpiHandle bld_dig_attrlist_iter(struct h_t *hp, struct attr_t *attrp)
{
 int32 ai, atnum;
 struct attr_t *attrp2; 
 struct hrec_t *hrp, *hrp2;
 struct h_t *hp2;
 vpiHandle ihref;
 struct pviter_t *iterp;

 if (attrp == NULL) return(NULL);
 atnum = 0;
 for (attrp2 = attrp; attrp2 != NULL; attrp2 = attrp2->attrnxt) atnum++; 

 hrp = hp->hrec;
 iterp = __alloc_empty_iter(atnum, &ihref);
 __iter_fill_with_empty(iterp);
 for (ai = 0; ai < atnum; ai++)
  {
   hp2 = iterp->scanhptab[ai];
   hp2->hin_idp = hp->hin_idp;
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiAttribute;
   hrp2->htyp2 = hrp->htyp;
   hrp2->hi = ai;
   hrp2->hu.hanyp = hrp->hu.hanyp;
   hrp2->hin_tskp = hrp->hin_tskp;
  }  
 return(ihref);
}

/*
 * ROUTINES TO BUILD STATEMENT CONTENTS ITERATOR
 */

/*
 * build the case item iterator
 */
extern vpiHandle __bld_caseitems_iter(struct h_t *hp)
{
 int32 cii, numcis;
 struct csitem_t *csip2;
 struct hrec_t *hrp2;
 vpiHandle ihref;
 struct csitem_t *dfltcsip;
 struct h_t *hp2;
 struct pviter_t *iterp;
 struct st_t *stp;
 struct csitem_t *csips;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 if (hrp->htyp != vpiCase)
  {
   __vpi_err(1835, vpiError,
    "vpiCaseItem 1-to-many iterator requires vpiCase reference handle - %s illegal",
    __to_vpionam(__wrks1, hrp->htyp));
   return(NULL);
  }
 stp = hrp->hu.hstp;
 /* 08/27/99 - now case default always first on list - nil st if no dflt */
 dfltcsip = stp->st.scs.csitems;

 csips = dfltcsip->csinxt;
 for (numcis = 0, csip2 = csips; csip2 != NULL; csip2 = csip2->csinxt)
  numcis++;
 if (dfltcsip->csist != NULL) numcis++;
 if (numcis <= 0) return(NULL);

 iterp = __alloc_empty_iter(numcis, &ihref);
 __iter_fill_with_empty(iterp);
 for (csip2 = csips, cii = 0; csip2 != NULL; csip2 = csip2->csinxt, cii++) 
  {
   /* DBG remove --- */
   if (csip2->csist == NULL) __vpi_terr(__FILE__, __LINE__); 
   /* --- */

   hp2 = iterp->scanhptab[cii];
   hp2->hin_idp = hp->hin_idp;
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiCaseItem;
   hrp2->hu.hcsip = csip2;
   hrp2->hin_tskp = hrp->hin_tskp;
  }
 /* notice cii at loop exit is next past end */
 if (dfltcsip->csist != NULL)
  {
   hp2 = iterp->scanhptab[cii];
   hp2->hin_idp = hp->hin_idp;
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiCaseItem;
   hrp2->hu.hcsip = dfltcsip;
   hrp2->hin_tskp = hrp->hin_tskp;
  }
 return(ihref);
}

/*
 * build the case item expression iterator from case item (including default)
 */
extern vpiHandle __bld_casi_exprs_iter(struct h_t *hp)
{
 int32 xi;
 int32 numxps;
 vpiHandle ihref;
 struct exprlst_t *xplst;
 struct csitem_t *csip;
 struct h_t *hp2;
 struct pviter_t *iterp;
 struct hrec_t *hrp;
 
 hrp = hp->hrec;
 if (hrp->htyp != vpiCaseItem)
  {
   __vpi_err(1831, vpiError,
    "vpiExpr 1-to-many iterator only legal for vpiCaseItem - %s illegal",
    __to_vpionam(__wrks1, hrp->htyp));
   return(NULL);
  }
 csip = hrp->hu.hcsip;
 for (numxps = 0, xplst = csip->csixlst; xplst != NULL; xplst = xplst->xpnxt)
  numxps++;
 if (numxps <= 0) return(NULL);
 iterp = __alloc_empty_iter(numxps, &ihref);
 __iter_fill_with_empty(iterp);
 for (xi = 0, xplst = csip->csixlst; xplst != NULL; xplst = xplst->xpnxt, xi++)
  {
   hp2 = iterp->scanhptab[xi];
   /* SJM 06-22-10 - init needed here */
   mk2_exprclass_handle(hp2, xplst->xp, hp->hin_idp, hrp->hin_tskp);
  }
 return(ihref);
}

/*
 * build the iterator for operands of an operator
 * handle is an expression that must have operands
 *
 * for part select and bit (const or var) select vpiRange or vpiIndex
 * not vpiOperand iterator
 */
extern vpiHandle __bld_operands_iter(struct h_t *hp)
{
 int32 xi;
 int32 xtyp, otyp, numxps;
 struct expr_t *xp, *catxp;
 vpiHandle ihref;
 struct expr_t *xp2;
 struct h_t *hp2;
 struct pviter_t *iterp;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 if (hrp->htyp != vpiOperation)
  {
   strcpy(__wrks2, "*none*");
bad_handle:
   __vpi_err(1831, vpiError,
    "vpiOperand 1-to-many iterator requires vpiOperation handle - %s (type %s) illegal",
    __to_vpionam(__wrks1, hrp->htyp), __wrks2);
   return(NULL);
  }
 xp = hrp->hu.hxp;
 xtyp = __exprtype_get(xp);
 if (xtyp != vpiOperation)
  { __to_vpionam(__wrks2, (word32) xtyp); goto bad_handle; }

 otyp = __expr_optype_get(xp);

 /* null op has no operands */
 if (otyp == vpiNullOp)
  {
   return(NULL);
  }
 
 /* concatenate and ?: are special cases (3-ary and n-ary) */
 if (otyp == vpiConcatOp) 
  {
   for (numxps = 0, catxp = xp->ru.x; catxp != NULL; catxp = catxp->ru.x)
    numxps++;
   
   /* DBG remove --- */
   if (numxps <= 0) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   iterp = __alloc_empty_iter(numxps, &ihref);
   __iter_fill_with_empty(iterp);
   for (catxp = xp->ru.x, xi = 0; catxp != NULL; catxp = catxp->ru.x, xi++) 
    {
     /* works because alloc of iter make connect from hp to hrec */
     hp2 = iterp->scanhptab[xi];
     mk2_exprclass_handle(hp2, catxp->lu.x, hp->hin_idp, hrp->hin_tskp);
    }
   return(ihref);
  }
 if (otyp == vpiConditionOp)
  {
   iterp = __alloc_empty_iter(3, &ihref);
   __iter_fill_with_empty(iterp);
   for (xi = 0; xi < 3; xi++)
    {
     hp2 = iterp->scanhptab[xi];
     if (xi == 0) xp2 = xp->lu.x;
     else if (xi == 1) xp2 = xp->ru.x->lu.x;
     else xp2 = xp->ru.x->ru.x;
     mk2_exprclass_handle(hp2, xp2, hp->hin_idp, hrp->hin_tskp);
    }
   return(ihref);
  }
 /* notice ru operand nil implies unary */
 if (xp->ru.x == NULL)
  { 
   iterp = __alloc_empty_iter(1, &ihref);
   __iter_fill_with_empty(iterp);
   hp2 = iterp->scanhptab[0];
   mk2_exprclass_handle(hp2, xp->lu.x, hp->hin_idp, hrp->hin_tskp);
   return(ihref);
  }
 /* normal binary operator */
 iterp = __alloc_empty_iter(2, &ihref);
 __iter_fill_with_empty(iterp);
 for (xi = 0; xi < 2; xi++)
  {
   hp2 = iterp->scanhptab[xi];
   if (xi == 0) xp2 = xp->lu.x; else xp2 = xp->ru.x;
   mk2_exprclass_handle(hp2, xp2, hp->hin_idp, hrp->hin_tskp);
  }
 return(ihref);
}

/*
 * build all callbacks iterator
 * for now only legal is all, FIXME - should support from objects
 */
extern vpiHandle __bld_allcbs_iter(struct h_t *hp)
{
 int32 cbi, numcbs;
 struct cbrec_t *cbp;
 struct hrec_t *hrp2;
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct h_t *hp2;

 if (hp != NULL)
  {
   __vpi_err(1831, vpiError,
    "for now vpiCallback 1-to-many iterator requires NULL (all cbs) - %s illegal",
    __to_vpionam(__wrks1, hp->hrec->htyp));
    return(NULL);
  }
 if (__vpi_cbrec_hdr == NULL) return(NULL);
 for (numcbs = 0, cbp = __vpi_cbrec_hdr; cbp != NULL; cbp = cbp->cbnxt)
  numcbs++;
 if (numcbs <= 0) return(NULL);

 iterp = __alloc_empty_iter(numcbs, &ihref);
 __iter_fill_with_empty(iterp);
 /* since register list new added to front, build iterator back to front */ 
 cbp = __vpi_cbrec_hdr;
 /* SJM - 06/14/99 - since put latest on front build in reverse order */
 for (cbi = numcbs - 1; cbp != NULL; cbp = cbp->cbnxt, cbi--) 
  {
   hp2 = iterp->scanhptab[cbi];
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiCallback;
   hrp2->hu.hcbp = cbp;
   /* callback handles do not have itree loc (but obj might) */
  }
 return(ihref);
}

/*
 * ROUTINES TO BUILD PORT AND PORT BIT ITERATORS
 */

/*
 * build vpi Port module port iterator from a net (any type) handle
 *
 * given a net, find all ports that connect to the net (usually one)
 * but jumpered ports legal in Verilog
 * search through all of load, drivers, and inout vertex edges
 *
 * module port connections are never xmr since no xmr forms for port wire
 */
static vpiHandle bld_netmdport_iter(struct h_t *hp)
{
 int32 hi, numprts;
 vpiHandle ihref;
 struct net_t *np;
 struct mod_t *mdp;
 struct pviter_t *iterp;

 np = hp->hrec->hu.hnp;
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 if (mdp->mpnum == 0) return(NULL);
 numprts = bld_net_mdpins(np, mdp, hp->hin_idp);
 if (numprts <= 0) return(NULL);

 iterp = __alloc_empty_iter(numprts, &ihref);
 for (hi = 0; hi < numprts; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * build modport connecting iterators
 *
 * know all jumpered non tran channel ports will be marked if any are
 *
 * if multiple connections to same port do not include repeats
 * this does not run with anything on itstk instead uses itp
 *
 * here iterator is vpiPort so returns all port connections
 *
 * this is opposite of lowconn - from port connecting net up to port
 * here because not bit handle, return entire port
 *
 * to decompose and match expr. connections and ports, user must create
 * port iterator get highconn and lowconn connection and then write program
 * to match
 */
static int32 bld_net_mdpins(struct net_t *np, struct mod_t *mdp,
 t_midat *idp)
{
 int32 cnt;
 byte *prtconn;
 struct net_pin_t *npp;
 struct hrec_t *hrp2;
 struct h_t *hp2;
 struct mod_pin_t *mpp;
 
 prtconn = (byte *) __my_malloc(mdp->mpnum);
 memset(prtconn, 0, mdp->mpnum);
 /* mod port loads are output ports - can connect to regs too */
 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* PB mdports for drivers only */
   if (npp->npntyp == NP_PB_MDPRT)
    {
     /* SJM 09/20/02 - for per bit npp forms, ignore all but 1 npp */  
     /* there will be one npp per bit but only one iterator forllowing LRM */
     /* and by not doing 2nd per bit indexing, looks like vectored npp */
     if (npp->pbi != 0) continue;
    }
   else if (npp->npntyp != NP_MDPRT) continue;

   /* DBG remove --- */
   if (npp->elnpp.emdp != mdp) __vpi_terr(__FILE__, __LINE__);
   /* --- */  
   mpp = &(mdp->mpins[npp->obnum]);
   /* if no connection for this port include */
   if (prtconn[npp->obnum] == 0)
    {
     if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hp2->hin_idp = idp;
     hrp2 = hp2->hrec;
     hrp2->in_iter = TRUE;
     hrp2->htyp = vpiPort;
     hrp2->hu.hpi = npp->obnum;
     prtconn[npp->obnum] = 1;
    }
   if (!mpp->mp_jmpered) break;
  }
 /* if reg done */
 if (np->ntyp >= NONWIRE_ST) goto done;

 /* mod port drivers are input ports - must be wire */
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp == NP_PB_MDPRT)
    {
     /* SJM 09/20/02 - for per bit npp forms, ignore all but 1 npp */  
     /* there will be one npp per bit but only one iterator forllowing LRM */
     /* and by not doing 2nd per bit indexing, looks like vectored npp */
     if (npp->pbi != 0) continue;
    }
   else if (npp->npntyp != NP_MDPRT) continue;

   /* DBG remove --- */
   if (npp->elnpp.emdp != mdp) __vpi_terr(__FILE__, __LINE__);
   /* --- */  
   mpp = &(mdp->mpins[npp->obnum]);
   if (prtconn[npp->obnum] == 0)
    {
     if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hp2->hin_idp = idp;

     hrp2 = hp2->hrec;
     hrp2->in_iter = TRUE;
     hrp2->htyp = vpiPort;
     hrp2->hu.hpi = npp->obnum;
     prtconn[npp->obnum] = 1;
    }
   if (!mpp->mp_jmpered) break;
  }
 /* finally inout ports if they exist (always bit by bit) */
 if (np->ntraux == NULL) goto done;

 /* SJM - 05/15/99 - after tran channels built - leave npps connected */
 /* as part of ntraux - use for PLI not simulation */
 /* bid and tran (gate?) npps move to traux for PLI processing */
 for (npp = np->ntraux->tran_npps; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_BIDMDPRT) continue;

   mpp = &(mdp->mpins[npp->obnum]);
   /* DBG remove --- */
   if (npp->elnpp.emdp != mdp) __vpi_terr(__FILE__, __LINE__);
   /* --- */  
   mpp = &(mdp->mpins[npp->obnum]);
   if (prtconn[npp->obnum] == 0)
    {
     if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hp2->hin_idp = idp;
     hrp2 = hp2->hrec;
     hrp2->in_iter = TRUE;
     hrp2->htyp = vpiPort;
     hrp2->hu.hpi = npp->obnum;
     prtconn[npp->obnum] = 1;
    }
  }
done:
 __my_free(prtconn, mdp->mpnum);
 return(cnt);
}

/*
 * build the port bit iterator for all bits connecting to the one net bit
 *
 * for normal non scalar only connections this is needed to get per bit
 * connections since different bits will have different connectivity
 * never get here for scalar
 *
 * LOOKATME - netbit here must be constant only (i.e. no eval) 
 */
static vpiHandle bld_netbitmdport_iter(struct h_t *hp)
{
 int32 hi, bi, numprts;
 vpiHandle ihref;
 struct net_t *np;
 struct mod_t *mdp;
 struct pviter_t *iterp;

 if ((bi = cmp_drvld_bitndx(&np, hp, "vpiPort")) == -1) return(NULL);

 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 if (mdp->mpnum == 0) return(NULL);
 numprts = bld_netbit_mdpins(np, bi, mdp, hp->hin_idp);
 if (numprts <= 0) return(NULL);

 iterp = __alloc_empty_iter(numprts, &ihref);
 for (hi = 0; hi < numprts; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * compute index for bit object driver/load iterator
 *
 * ??? FIXME - think this is wrong needs to use current value 
 * but then can't call during vpiEndOfCompile?
 */
static int32 cmp_drvld_bitndx(struct net_t **nnp, struct h_t *hp, char *objnam)
{
 int32 bi;
 struct net_t *np;
 struct hrec_t *hrp;
 decl_idp_locals_;

 *nnp = NULL;
 hrp = hp->hrec;
 if (!hrp->bith_ndx && !__expr_is_vpiconst(hrp->hu.hxp))
  {
   __vpi_err(1880, vpiError,
    "%s 1-to-many iterator from %s illegal - vpiNetBit/vpiRegBit non constant",
    objnam, __to_vpionam(__wrks1, hrp->htyp));
   return(-1);
  }
 if (hrp->bith_ndx) { np = hrp->hu.hnp; bi = hrp->hi; }
 else
  {
   /* DBG remove --- */
   if (hrp->hu.hxp->optyp != LSB) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   /* know expr. is constant to get to here */ 
   np = hrp->hu.hxp->lu.sy->el.enp;
   set_save_idp_(hp->hin_idp);
   bi = __comp_ndx(np, hrp->hu.hxp->ru.x);
   restore_idp_();
   /* for x or out of range - iterator empty */
   if (bi == -1) return(-1);
  }
 *nnp = np;
 return(bi);
}

/*
 * build mod portbit connecting iterators
 * 
 * notice since net in module npp bits indices and bi will both be h:0 
 * here built iterator is vpiPortBit, i.e. bit matches
 *
 * this is opposite (iterator) of highconn
 *
 * here can not eliminate duplicates
 *
 * because this is bit, if port scalar returns vpiPort else vpiPortBit
 * if mod port is concat (rare) does not include and sets warning
 *
 * LOOKATME - all 3 cases have mostly same code - could make one func call
 */
static int32 bld_netbit_mdpins(struct net_t *np, int32 bi, struct mod_t *mdp,
 t_midat *idp)
{
 int32 ri1, ri2, cnt;
 struct net_pin_t *npp;
 struct hrec_t *hrp2;
 struct mod_pin_t *mpp;
 struct h_t *hp2;
 decl_idp_locals_;
 
 mpp = NULL;
 /* md prt loads are output ports */
 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* for per bit mod ports - match if this bit same as bi */
   if (npp->npntyp == NP_PB_MDPRT)
    {
     if (bi == npp->pbi)
      {
       ri1 = ri2 = bi;
       goto got_match;
      }
     /* SJM 05/20/07 - notice if do not set ri1/ri2, exit cont loop */
     else continue;
    }

   if (npp->npntyp != NP_MDPRT) continue;

   /* DBG remove --- */
   if (npp->elnpp.emdp != mdp) __vpi_terr(__FILE__, __LINE__);
   /* --- */  
   set_save_idp_(idp);
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   restore_idp_();
   if (ri1 == -1 || bi == -1) goto got_match;   
   if (bi > ri1 || bi < ri2) continue;

got_match:
   mpp = &(mdp->mpins[npp->obnum]);
   if (mpp->mpref->optyp == LCB)
    {
     char s1[RECLEN];

     sprintf(s1, "%s[%d]", np->nsym->synam, __unnormalize_ndx(np, bi));
     __vpi_err(2025, vpiWarning,
      "vpiPort iterator %s bit handle for concatenate port - unable to determine bit so vpiPort used",
       s1);
    }

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = idp;
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;

   if (mpp->mpwide == 1 || mpp->mpref->optyp == LCB) hrp2->htyp = vpiPort;
   else
    {
     hrp2->htyp = vpiPortBit;
     /* if simple wire (ri1 == -1) bits match one to one - else offset from */
     /* right edge */
     /* FIXME - what if range 0:h? */ 
     if (ri1 == -1) hrp2->hi = bi; else hrp2->hi = bi - ri2;
    }
   hrp2->hu.hpi = npp->obnum;
   /* LOOKATME - think some bit may be inout channel so need ports */
   if (!mpp->mp_jmpered) break;
  }
 /* will be no drivers and no tran channel for reg */
 if (np->ntyp >= NONWIRE_ST)
  {
   /* DBG remove --- */
   if (np->ndrvs != NULL || np->ntraux != NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   goto done;
  }

 /* md prt drivers are input ports */
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   /* SJM 09/20/02 - need to access per bit contained port for PB form */
   /* for per bit mod ports - match if this bit same as bi */
   if (npp->npntyp == NP_PB_MDPRT)
    {
     if (bi == npp->pbi) goto got_match2;
     else continue;
    }

   if (npp->npntyp != NP_MDPRT) continue;

   /* DBG remove --- */
   if (npp->elnpp.emdp != mdp) __vpi_terr(__FILE__, __LINE__);
   /* --- */  
   set_save_idp_(idp);
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   restore_idp_();
   if (ri1 == -1 || bi == -1) goto got_match2;   
   if (bi > ri1 || bi < ri2) continue;

got_match2:
   if (npp->npntyp == NP_MDPRT)
    {
     mpp = &(mdp->mpins[npp->obnum]);
     if (mpp->mpref->optyp == LCB)
      {
       char s1[RECLEN];

       sprintf(s1, "%s[%d]", np->nsym->synam, __unnormalize_ndx(np, bi));
       __vpi_err(2025, vpiWarning,
        "vpiPort iterator %s bit handle for concatenate port - unable to determine bit so vpiPort used",
         s1);
      }
    }
   else
    { 
//SJM 06-22-10 - LOOKATME - why repeated same?
//     mpp = &(mdp->mpins[npp->obnum]);
     mpp = &(mpp->pbmpps[npp->pbi]);
    }
   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = idp;
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;

   if (npp->npntyp == NP_MDPRT)
    {
     if (mpp->mpwide == 1 || mpp->mpref->optyp == LCB) hrp2->htyp = vpiPort;
     else
      {
       hrp2->htyp = vpiPortBit;
       /* notice these are internal h:0 - fixed when index accessed */
       /* correct for port bit from non concatenate net bit */ 
       if (ri1 == -1) hrp2->hi = bi; else hrp2->hi = bi - ri2;
      }
    } 
   else
    {
     /* SJM 09/20/02 - for PB input port MOD PORT, always scalared */
     hrp2->htyp = vpiPortBit;
     hrp2->hi = bi;
    }
   hrp2->hu.hpi = npp->obnum;
  }
done:
 return(cnt);
}

/*
 * ROUTINES BUILD PORT INSTANCE (ICONN) ITERATORS
 */

/*
 * build vpi port instance (iconn) iterators
 *
 * here will commonly have many iconns (ports of in module instances) 
 * for example if clock feeds lots of instances
 *
 * if net if any bits connect in iterator if bit only if right bit matches
 */
extern vpiHandle __bld_neticonn_iter(struct h_t *hp)
{
 if (hp == NULL) return(__nil_iter_err(vpiPortInst));
 switch (hp->hrec->htyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   /* iterator is usually 1 port net connects to (only more if jumpered) */
   /* this returns port handles even if selects */
   return(bld_neticonnport_iter(hp));
  case vpiNetBit: case vpiRegBit: case vpiVarSelect:
   /* iterator is usually 1 port bit bit connects to */
   /* this returns port bit handles for the one bit */
   return(bld_netbiticonnport_iter(hp));
  default:
   __vpi_err(1863, vpiError,
    "vpiPortInst 1-to-many iterator from %s illegal - for loconn instance ports",
    __to_vpionam(__wrks1, hp->hrec->htyp));
  }  
 return(NULL);
}

/*
 * build the iterator for all ports connecting to inside module instances
 *
 * each will have different hin_idp and expect many
 */
static vpiHandle bld_neticonnport_iter(struct h_t *hp)
{
 int32 hi, numprts;
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 np = hp->hrec->hu.hnp;
 numprts = bld_net_iconns(np, hp->hin_idp);
 if (numprts <= 0) return(NULL);

 iterp = __alloc_empty_iter(numprts, &ihref);
 for (hi = 0; hi < numprts; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * build down instance connecting iconns iterators
 *
 * here any common bits cause all of inst-port handle to be added to iter
 * never duplicates since will be different port (inst. term) or different
 * instance
 *
 * but since tran channel per bit, some connections will probably 
 * connect to same wire and port (i.e. needed to decompose part select or
 * wire to all the bits)
 *
 * algorithm is to count all so know will be at least big enough then
 * caller reallocates to shink when done
 *
 * notice nothing on itree stack here?
 * also no filtering of bit range and bit counts because return entire port
 *
 * SJM 09/20/02 - because this is vectored and only entire ports in   
 * iterator filter to only one of iconn high conn concat works
 */
static int32 bld_net_iconns(struct net_t *np, t_midat *idp)
{
 int32 cnt;
 struct net_pin_t *npp;
 struct hrec_t *hrp2;
 struct h_t *hp2;
 struct itree_t *itp2, *itp, *cur_itp;
 
 /* iconn loads are input ports */
 cur_itp = NULL;
 itp = (struct itree_t *) idp[MD_ITP];
 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* SJM 02/22/02 - works because rhs up expr not decomposed so all */ 
   /* loads are same - only difference is use part of port for action */
   if (npp->npntyp == NP_PB_ICONN)
    {
     /* SJM 09/20/02 - for per bit npp forms, ignore all but 1 npp */  
     /* there will be one npp per bit but only one iterator forllowing LRM */
     if (npp->pbi != 0) continue;
    }
   else if (npp->npntyp != NP_ICONN) continue;

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != idp)
     continue;

   if (npp->npproctyp == NP_PROC_INMOD) itp2 = &(itp->in_its[npp->elnpp.eii]);
   else
    {
     /* SJM 04/17/03 - LOOKATME - think inst conn. down into illegal */
     /* but leaving does not hurt */
     if ((cur_itp = __get_npprefloc(npp)) == NULL)
      {
       continue;
      }
     itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
    }

   if (cnt >= __ithtsiz) __grow_hptab(cnt+ 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = itp2->it_idp;
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;
   hrp2->htyp = vpiPort;
   hrp2->hu.hpi = npp->obnum;
  }
 /* will be no drivers and no tran channel for reg */
 if (np->ntyp >= NONWIRE_ST)
  {
   /* DBG remove --- */
   if (np->ndrvs != NULL || np->ntraux != NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   goto done;
  }

 /* iconn drivers are output ports and only exist for wires */
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   /* PB iconns only for loads */
   /* DBG remove -- */
   if (npp->npntyp == NP_PB_ICONN) __vpi_terr(__FILE__, __LINE__);
   /* -- */
   if (npp->npntyp != NP_ICONN) continue;

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != idp) 
      continue;

   if (npp->npproctyp == NP_PROC_INMOD) itp2 = &(itp->in_its[npp->elnpp.eii]);
   else
    {
     /* SJM 04/17/03 - LOOKATME - think inst conn. down into illegal */
     /* but leaving does not hurt */
     if ((cur_itp = __get_npprefloc(npp)) == NULL)
      {
       continue;
      }
     itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
    }

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   /* vpi handle parent will get module/instance port in */
   hp2->hin_idp = itp2->it_idp;
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;
   hrp2->htyp = vpiPort;
   hrp2->hu.hpi = npp->obnum;
  }

 /* finally inout if they exist */
 if (np->ntraux == NULL) goto done;

 /* iconns in tran channels are only bid iconns */
 for (npp = np->ntraux->tran_npps; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_BIDICONN) continue;

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != idp)
       continue;

   if (npp->npproctyp == NP_PROC_INMOD) itp2 = &(itp->in_its[npp->elnpp.eii]);
   else
    {
     /* can be iconn from other instance for xmr */
     /* SJM 04/17/03 - LOOKATME - think inst conn. down into illegal */
     /* but leaving does not hurt */
     if ((cur_itp = __get_npprefloc(npp)) == NULL)
      {
       continue;
      }
     itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
    }

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   /* vpi handle parent will get module/instance port in */
   hp2->hin_idp = itp2->it_idp;
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;
   hrp2->htyp = vpiPort;
   hrp2->hu.hpi = npp->obnum;
  }
done:
 return(cnt);
}

/*
 * return T if find tran channel inst-port that matches one already
 * in iterator
 */
static int32 same_vpi_handle(struct h_t **htab, int32 fr, int32 num,
 struct h_t *hp2, struct hrec_t *hrp2)
{
 int32 hi;
 struct h_t *hp;
 struct hrec_t *hrp;

 for (hi = fr; hi < num; hi++)
  {
   hp = htab[hi];
   hrp = hp->hrec; 

   switch (hrp->htyp) {
    case vpiPort:
     if (hrp2->htyp != vpiPort) break;
     if (hp2->hin_idp != hp->hin_idp) break;
     if (hrp2->hu.hpi != hrp->hu.hpi) break;
     return(TRUE);
    case vpiContAssign:
     if (hrp2->htyp != vpiContAssign) break;
     if (hp2->hin_idp != hp->hin_idp) break;
     if (hrp2->htyp2 == vpiGate || hrp->htyp2 == vpiGate)
      {
       if (hrp2->htyp2 != vpiGate || hrp->htyp2 != vpiGate) break; 
       if (hrp2->hu.hgp != hrp->hu.hgp) break;
      }
     else if (hrp2->hu.hcap != hrp->hu.hcap) break;
     return(TRUE);
    case vpiPrimTerm:
     /* terminal of gate */
     if (hrp2->htyp != vpiPrimTerm) break;
     if (hp2->hin_idp != hp->hin_idp) break;
     if (hrp2->hu.hgp != hrp->hu.hgp) break;
     if (hrp2->hi != hrp->hi) break;
     return(TRUE);
    case vpiModPathOut:
     if (hrp2->htyp != vpiModPathOut) break;
chk_modpath:
     if (hp2->hin_idp != hp->hin_idp) break;
     if (hrp2->hu.hpthp != hrp->hu.hpthp) break;
     if (hrp2->hi != hrp->hi) break;
     return(TRUE);
    case vpiModPathIn:
     if (hrp2->htyp != vpiModPathIn) break;
     goto chk_modpath;
    case vpiForce:
     if (hrp2->htyp != vpiForce) break;
     if (hp2->hin_idp != hp->hin_idp) break;
     if (hrp2->hu.hstp != hrp->hu.hstp) break;
     return(TRUE);
    default: __vpi_terr(__FILE__, __LINE__);
   }
 }
 return(FALSE);
}

/*
 * build the iterator for all port bits connecting to inside module instances
 * given a vpi net or reg bit handle, build iterator of port bit handles
 *
 * if iconn contenate or operator expression - returns entire handle
 */
static vpiHandle bld_netbiticonnport_iter(struct h_t *hp)
{
 int32 hi, bi, numprts;
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 if ((bi = cmp_drvld_bitndx(&np, hp, "vpiPortInst")) == -1) return(NULL);

 numprts = bld_netbit_iconns(np, bi, hp->hin_idp);
 if (numprts <= 0) return(NULL);

 iterp = __alloc_empty_iter(numprts, &ihref);
 for (hi = 0; hi < numprts; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * build down instance connecting iconns iterators
 *
 * here any common bits cause all of inst-port handle to be added to iter
 * never duplicates since will be different port (inst. term) or different
 * instance
 *
 * but since tran channel per bit, some connections will probably 
 * connect to same wire and port (i.e. needed to decompose part select or
 * wire to all the bits)
 *
 * algorithm is to count all so know will be at least big enough then
 * caller reallocates to shink when done
 *
 * notice nothing on itree stack here?
 */
static int32 bld_netbit_iconns(struct net_t *np, int32 bi, t_midat *idp)
{
 int32 ri1, ri2, cnt, not_lhs;
 struct net_pin_t *npp;
 struct hrec_t *hrp2;
 struct h_t *hp2;
 struct itree_t *itp2, *cur_itp, *itp;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 decl_idp_locals_;
 
 set_save_idp_(idp);
 /* iconn loads are input ports */
 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* SJM 02/22/02 - works because rhs up expr not decomposed so all */ 
   /* loads are same - only difference is use part of port for action */
   if (npp->npntyp != NP_ICONN && npp->npntyp != NP_PB_ICONN) continue;

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != idp)
      continue;

   /* can be iconn from other instance for xmr */
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - LOOKATME - think inst conn. down into illegal */
     /* but leaving does not hurt */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }

   /* this must run with right itree loc. */
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   if (ri1 == -1 || bi == -1) goto got_match;   
   if (bi > ri1 || bi < ri2) continue;

got_match:
   /* if iconn not lvalue (variable, bit or part select or mod pin concate */
   /* need warning and use entire vpiPort */
   cur_itp = get_itp_();
   itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
   downmdp = itp2->itip->imsym->el.emdp;
   if (npp->npntyp == NP_ICONN)
    {
     mpp = &(downmdp->mpins[npp->obnum]);
     if (!iconnbit_lvalue(mpp, npp, itp2)) not_lhs = TRUE; 
     else not_lhs = FALSE;

     if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hrp2 = hp2->hrec;
     hrp2->in_iter = TRUE;
     hrp2->hu.hpi = npp->obnum;

     if (mpp->mpwide == 1 || not_lhs) hrp2->htyp = vpiPort;
     else
      {
       hrp2->htyp = vpiPortBit;
       /* notice these are internal h:0 - fixed when index accessed */
       /* correct for port bit from non concatenate net bit */ 
       /* LOOKATME - is this right? */
       if (ri1 == -1) hrp2->hi = bi; else hrp2->hi = bi - ri2;
      }
    }
   else
    {
     /* SJM 09/20/02 - for per bit separated input iconn, need double ndxing */
     if (cnt >= __ithtsiz) __grow_hptab(cnt - __ithtsiz + 1);
     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hrp2 = hp2->hrec;
     hrp2->in_iter = TRUE;
     hrp2->hu.hpi = npp->obnum;
     hrp2->htyp = vpiPortBit;
     hrp2->hi = bi;   
    }
   /* SJM 06-22-10 - notice needed for all iter element blds */
   hp2->hin_idp = itp2->it_idp;
  }
 /* will be no drivers and no tran channel for reg */
 if (np->ntyp >= NONWIRE_ST)
  {
   /* DBG remove --- */
   if (np->ndrvs != NULL || np->ntraux != NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   goto done;
  }
 /* iconn drivers are output ports and only exist for wires */
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   /* SJM 09/20/02 - since this is output port iconn, never per bit */
   if (npp->npntyp != NP_ICONN) continue;

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != __idp)
    continue;

   /* can be iconn from other instance for xmr */
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - LOOKATME - think inst conn. down into illegal */
     /* but leaving does not hurt */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }

   /* this must run with right itree loc. */
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   if (ri1 == -1 || bi == -1) goto got_match2;   
   if (bi > ri1 || bi < ri2) continue;

got_match2:
   /* if iconn not lvalue (variable, bit or part select or mod pin concate */
   /* need warning and use entire vpiPort */
   cur_itp = get_itp_();
   itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
   downmdp = itp2->itip->imsym->el.emdp;
   mpp = &(downmdp->mpins[npp->obnum]);
   if (!iconnbit_lvalue(mpp, npp, itp2)) not_lhs = TRUE; 
   else not_lhs = FALSE;

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = itp2->it_idp;
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;
   hrp2->htyp = vpiPort;
   hrp2->hu.hpi = npp->obnum;

   if (mpp->mpwide == 1 || not_lhs) hrp2->htyp = vpiPort;
   else
    {
     hrp2->htyp = vpiPortBit;
     /* notice these are internal h:0 - fixed when index accessed */
     /* correct for port bit from non concatenate net bit */ 
     if (ri1 == -1) hrp2->hi = bi; else hrp2->hi = bi - ri2;
    }
  }
 /* finally inout if they exist */
 if (np->ntraux == NULL) goto done;

 /* iconn drivers are output ports and only exist for wires */
 for (npp = np->ntraux->tran_npps; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_BIDICONN) continue;

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != __idp) 
    continue;

   /* can be iconn from other instance for xmr */
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - LOOKATME - think inst conn. down into illegal */
     /* but leaving does not hurt */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }

   /* this must run with right itree loc. */
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   if (ri1 == -1 || bi == -1) goto got_match3;   
   if (bi > ri1 || bi < ri2) continue;

got_match3:
   /* if iconn not lvalue (variable, bit or part select or mod pin concate */
   /* need warning and use entire vpiPort */
   cur_itp = get_itp_();
   itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
   downmdp = itp2->itip->imsym->el.emdp;
   mpp = &(downmdp->mpins[npp->obnum]);
   if (!iconnbit_lvalue(mpp, npp, itp2)) not_lhs = TRUE; 
   else not_lhs = FALSE;

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = itp2->it_idp;
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;
   hrp2->htyp = vpiPort;
   hrp2->hu.hpi = npp->obnum;

   if (mpp->mpwide == 1 || not_lhs) hrp2->htyp = vpiPort;
   else
    {
     hrp2->htyp = vpiPortBit;
     /* notice these are internal h:0 - fixed when index accessed */
     /* correct for port bit from non concatenate net bit */ 
     if (ri1 == -1) hrp2->hi = bi; else hrp2->hi = bi - ri2;
    }
  }

done:
 restore_idp_();
 return(cnt);
}

/*
 * return T if good port and iconn simple (non concat) lvalue
 */
static int32 iconnbit_lvalue(struct mod_pin_t *mpp, struct net_pin_t *npp, 
 struct itree_t *itp2)
{
 struct expr_t *xp;

 if (mpp->mpref->optyp == LCB) return(FALSE);
 xp = itp2->itip->ipins[npp->obnum];
 if (xp->optyp == ID || xp->optyp == GLBREF || xp->optyp == LSB ||
  xp->optyp == PARTSEL || xp->optyp == PARTSEL_NDX_PLUS || 
  xp->optyp == PARTSEL_NDX_MINUS)
  {
   return(TRUE);
  }
 return(FALSE);
}

/*
 * ROUTINES TO BUILD LOCAL LOAD ITERATORS
 */

/*
 * build an iterator of wire or reg (or bit) local loads
 *
 * list differs but otherwise code is same 
 * inout ports and trans are both loads and drivers 
 *
 * this is local loads including ports and works for vectors
 * local loads give user exact control over connectivity tracing
 */
extern vpiHandle __bld_loc_lds_iterator(struct h_t *hp, int32 otype)
{
 if (hp == NULL) return(__nil_iter_err(otype));

 /* routine for each thing that load can be of */
 switch (hp->hrec->htyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   return(net_lds_iter(hp));
  case vpiNetBit: case vpiRegBit: case vpiVarSelect:
   return(bit_lds_iter(hp));
  default:
   __vpi_err(1874, vpiError,
    "vpiLocalLoad 1-to-many iterator from %s illegal - for net/reg/variable loads",
    __to_vpionam(__wrks1, hp->hrec->htyp));
  }  
 return(NULL);
}

/*
 * build entire wire net load iterator - in list if any bits
 *
 * caller must know type of iterator that is scanned since ld and driver
 * same except for list used
 */
static vpiHandle net_lds_iter(struct h_t *hp)
{
 int32 hi, num; 
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 np = hp->hrec->hu.hnp;
 if ((num = bld_net_lds(np, hp->hin_idp)) <= 0) return(NULL);

 iterp = __alloc_empty_iter(num, &ihref);
 for (hi = 0; hi < num; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * build loads on a net or reg (match on any common bits)
 *
 * but since tran channel per bit, some connections will probably 
 * connect to same wire and port (i.e. needed to decompose part select or
 * wire to all the bits)
 *
 * algorithm is to count all so know will be at least big enough then
 * caller reallocates to shink when done
 *
 * notice nothing on itree stack here?
 * also no need to filter bit range and bit counts
 */
static int32 bld_net_lds(struct net_t *np, t_midat *idp) 
{
 int32 cnt;
 struct net_pin_t *npp;
 struct hrec_t *hrp2;
 struct h_t tmph, *hp2;
 struct hrec_t tmphrec;
 struct itree_t *itp;
 decl_idp_locals_;
 
 set_save_idp_(idp);
 /* for hard inout/tran channel hard loads, found here */
 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* SJM 07/12/01 - until add v2k delay devices, omit mipd chg load */ 
   if (npp->npntyp == NP_MIPD_NCHG) continue;
   if (npp->npntyp == NP_PB_ICONN && npp->pbi != 0) continue;

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != idp) 
     continue;
   /* maybe move to right ref. itree loc. */ 
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - must match each inst in xmr path */
     /* but leaving does not hurt */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }
   __init_hrec(&tmphrec);
   tmphrec.in_iter = TRUE;
   tmph.hrec = &tmphrec;
   if (!fill_ld_handle(&(tmph), &(tmphrec), npp)) continue;

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   hrp2 = hp2->hrec;
   memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
  }
 /* will be no drivers and no tran channel for reg */
 if (np->ntyp >= NONWIRE_ST)
  {
   /* DBG remove --- */
   if (np->ndrvs != NULL || np->ntraux != NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   goto done;
  }
 /* tran channel npps - go in both ld and driver iterators */
 if (np->ntraux == NULL) goto done;

 /* SJM 05/15/99 - although not using npp's for inouts they are kept */
 /* around because they are needed for PLI load/driver iterators */
 for (npp = np->ntraux->tran_npps; npp != NULL; npp = npp->npnxt)
  {
   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != idp)
    continue;

   /* maybe move to right ref. itree loc. */ 
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - must match each inst in xmr path */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }
   __init_hrec(&tmphrec);
   tmphrec.in_iter = TRUE;
   if (!fill_ld_handle(&tmph, &tmphrec, npp)) continue;
   tmph.hrec = &tmphrec;

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   hrp2 = hp2->hrec;
   memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
  }
done:
 restore_idp_();
 return(cnt);
}

/*
 * fill a load handle - if non handle element, return nil
 *
 * caller must have initialized fields in handle
 * this must be called from ref. (stacked itree loc) for xmr 
 */
static int32 fill_ld_handle(struct h_t *hp, struct hrec_t *hrp,
 struct net_pin_t *npp)
{
 struct itree_t *itp2, *cur_itp;
 struct gate_t *gp;

 hp->hin_idp = __idp;
 switch ((byte) npp->npntyp) {
  case NP_ICONN: case NP_BIDICONN: case NP_PB_ICONN:
   /* load iconn is input port */
   hrp->htyp = vpiPort;
   hrp->hu.hpi = npp->obnum;
   cur_itp = get_itp_();
   itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
   hp->hin_idp = itp2->it_idp;
   break;
  case NP_MDPRT: case NP_BIDMDPRT: case NP_PB_MDPRT:
   /* load mdprt is output port */
   hrp->htyp = vpiPort;
   hrp->hu.hpi = npp->obnum;
   break;
  case NP_CONTA:
   hrp->htyp = vpiContAssign;
   hrp->hu.hcap = npp->elnpp.ecap;
   break;
  case NP_GATE: case NP_TRANIF: case NP_TRAN:
   gp = npp->elnpp.egp;
   if (gp->gmsym->el.eprimp->gateid == G_ASSIGN)
    {
     hrp->htyp = vpiContAssign;
     hrp->htyp2 = vpiGate;
     hrp->hu.hgp = gp;
    }
   else
    {
     gp = npp->elnpp.egp; 
     hrp->htyp = vpiPrimTerm;
     hrp->hu.hgp = gp;
     hrp->hi = npp->obnum;
    }
   break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * build the iterator for all port bits connecting to inside module instances
 * given a vpi net or reg bit handle, build iterator of port bit handles
 *
 * builds in it htab and then allocates iterator and copies into it
 */
static vpiHandle bit_lds_iter(struct h_t *hp)
{
 int32 hi, bi, num;
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 if ((bi = cmp_drvld_bitndx(&np, hp, "vpiLoad/vpiLocalLoad")) == -1)
  return(NULL);

 num = bld_bit_lds(np, bi, hp->hin_idp, FALSE);
 if (num <= 0) return(NULL);

 iterp = __alloc_empty_iter(num, &ihref);
 for (hi = 0; hi < num; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * build net bit loads or drivers iterator
 * 
 * fills it htab that then gets copied from later 
 *
 * since per bit never a need to remove duplicates
 * passed itp is instance of load npp
 * notice this works for scalar where bi must be -1
 */
static int32 bld_bit_lds(struct net_t *np, int32 bi, t_midat *idp,
 int32 no_ports)
{
 int32 ri1, ri2, cnt;
 struct net_pin_t *npp;
 struct hrec_t *hrp2;
 struct h_t tmph, *hp2;
 struct hrec_t tmphrec;
 struct itree_t *itp;
 decl_idp_locals_;
 
 set_save_idp_(idp);
 /* iconn loads are input ports */
 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   /* SJM 07/12/01 - until add v2k delay devices, omit mipd chg load */ 
   if (npp->npntyp == NP_MIPD_NCHG) continue;

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != __idp) 
     continue;

   /* can be iconn from other instance for xmr */
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - must match each inst in xmr path */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }

   /* this must run with right itree loc. */
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   if (ri1 == -1 || bi == -1) goto got_match;   
   if (bi > ri1 || bi < ri2) continue;

got_match:
   if (no_ports)
    {
     /* remove port npp's */
     switch ((byte) npp->npntyp) {
      case NP_ICONN: case NP_BIDICONN: case NP_MDPRT: case NP_BIDMDPRT:
      case NP_PB_ICONN: case NP_PB_MDPRT:
       continue;
      default: break;
     }
    }

   __init_hrec(&tmphrec);
   tmphrec.in_iter = TRUE;
   tmph.hrec = &tmphrec;

   if (!fill_bit_ld_handle(&tmph, &tmphrec, bi, ri1, ri2, npp)) continue; 

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   hrp2 = hp2->hrec;
   memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
  }
 /* will be no drivers and no tran channel for reg */
 if (np->ntyp >= NONWIRE_ST)
  {
   /* DBG remove --- */
   if (np->ndrvs != NULL || np->ntraux != NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   goto done;
  }
 /* tran channel connections if they exist */
 if (np->ntraux == NULL) goto done;

 /* iconn tran channel connections are all loads */
 for (npp = np->ntraux->tran_npps; npp != NULL; npp = npp->npnxt)
  {
   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != __idp) 
    continue;

   /* can be iconn from other instance for xmr */
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - must match each inst in xmr path */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }

   /* this must run with right itree loc. */
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   if (ri1 == -1 || bi == -1) goto got2_match;   
   if (bi > ri1 || bi < ri2) continue;

got2_match:
   if (no_ports)
    {
     /* remove port npp's */
     switch ((byte) npp->npntyp) {
      case NP_ICONN: case NP_BIDICONN: case NP_MDPRT: case NP_BIDMDPRT:
      case NP_PB_ICONN: case NP_PB_MDPRT:
       continue;
      default: break;
     }
    }
   __init_hrec(&tmphrec);
   tmphrec.in_iter = TRUE;
   tmph.hrec = &(tmphrec);

   if (!fill_bit_ld_handle(&(tmph), &(tmphrec), bi, ri1, ri2, npp)) continue; 

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   hrp2 = hp2->hrec;
   memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
  }
done:
 restore_idp_();
 return(cnt);
}

/*
 * fill a load handle - if non handle element, return nil
 *
 * caller must have initialized fields in handle
 * this must be called from ref. (stacked itree loc) for xmr 
 *
 * looking for load of net np bit bi (if scalar not called) 
 */
static int32 fill_bit_ld_handle(struct h_t *hp, struct hrec_t *hrp, int32 bi,
 int32 ri1, int32 ri2, struct net_pin_t *npp)
{
 int32 not_lhs;
 struct itree_t *itp2, *cur_itp;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 struct gate_t *gp;
 struct mod_t *cur_mdp;

 hp->hin_idp = __idp;
 switch ((byte) npp->npntyp) {
  case NP_ICONN: case NP_BIDICONN:
   /* load iconn is input port */
   cur_itp = get_itp_();
   itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
   downmdp = itp2->itip->imsym->el.emdp;
   mpp = &(downmdp->mpins[npp->obnum]);
   if (!iconnbit_lvalue(mpp, npp, itp2)) not_lhs = TRUE; 
   else not_lhs = FALSE;
   if (mpp->mpwide == 1 || not_lhs) hrp->htyp = vpiPort;
   else
    {
     hrp->htyp = vpiPortBit;
     /* notice these are internal h:0 - fixed when index accessed */
     if (ri1 == -1) hrp->hi = bi; else hrp->hi = bi - ri2;
    }
   hrp->hu.hpi = npp->obnum;
   hp->hin_idp = itp2->it_idp;
   break;
  case NP_PB_ICONN: 
   /* load iconn is concat high conn one bit of PB separated input port */
   cur_itp = get_itp_();
   itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
   downmdp = itp2->itip->imsym->el.emdp;
   mpp = &(downmdp->mpins[npp->obnum]);
   mpp = &(mpp->pbmpps[npp->pbi]);
   hrp->htyp = vpiPortBit;
   hrp->hi = bi;
   hrp->hu.hpi = npp->obnum;
   hp->hin_idp = itp2->it_idp;
   break;
  case NP_MDPRT: case NP_BIDMDPRT:
   /* load mod port is output port */
   cur_mdp = get_inst_mod_();
   mpp = &(cur_mdp->mpins[npp->obnum]);
   if (mpp->mpref->optyp == LCB || mpp->mpwide == 1) hrp->htyp = vpiPort;
   else
    {
     hrp->htyp = vpiPortBit;
     /* notice these are internal h:0 - fixed when index accessed */
     /* correct for port bit from non concatenate net bit */ 
     if (ri1 == -1) hrp->hi = bi; else hrp->hi = bi - ri2;
    }
   hrp->hu.hpi = npp->obnum;
   break;
  case NP_PB_MDPRT:
   /* load mod port is output port - this is one bit from PB decompose */
   /* but still for vpi_ do not use decomposed mpp */
   cur_mdp = get_inst_mod_();
   mpp = &(cur_mdp->mpins[npp->obnum]);
   /* SJM 11/15/02 - LOOKATME ??? - why is this filter needed */
   if (npp->npntyp == NP_PB_MDPRT && npp->pbi != 0) return(FALSE);
   hrp->htyp = vpiPortBit;
   /* notice these are internal h:0 - fixed when index accessed */
   /* correct for port bit from non concatenate net bit */ 
   if (ri1 == -1) hrp->hi = bi; else hrp->hi = bi - ri2;
   hrp->hu.hpi = npp->obnum;
   break;
  case NP_CONTA:
   hrp->htyp = vpiContAssign;
   hrp->hu.hcap = npp->elnpp.ecap;
   break;
  case NP_GATE: case NP_TRANIF: case NP_TRAN:
   gp = npp->elnpp.egp; 
   /* must correct for 1 bit conta */
   if (gp->gmsym->el.eprimp->gateid == G_ASSIGN)
    {
     hrp->htyp = vpiContAssign;
     hrp->htyp2 = vpiGate;
     hrp->hu.hgp = npp->elnpp.egp;
     break;
    }
   hrp->htyp = vpiPrimTerm;
   hrp->hu.hgp = gp;
   hrp->hi = npp->obnum;
   break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * ROUTINES TO BUILD XL STYLE LOAD ITERATORS (SCALAR OR BIT ONLY)
 */

/*
 * build an iterator of wire or reg bit XL style collapsed loads
 *
 * inout ports and trans are both loads and drivers 
 *
 * no ports here - cross and include actual loads from other side
 * algorithm sort of (mostly?) duplicates XL collapsing
 * only makes sense for 1 bit objects
 *
 * uese local loads but cross ports 
 */
extern vpiHandle __bld_lds_iterator(struct h_t *hp, int32 otype)
{
 struct hrec_t *hrp;

 if (hp == NULL) return(__nil_iter_err(otype));

 hrp = hp->hrec;
 /* routine for each thing that load can be of */
 switch (hrp->htyp) {
  case vpiNet: case vpiReg: 
   if (hrp->hu.hnp->nwid != 1) goto bad_obj;
   return(bit_xl_ldsdrvs_iter(hp, TRUE));
  case vpiNetBit: case vpiRegBit: case vpiVarSelect:
   return(bit_xl_ldsdrvs_iter(hp, TRUE));
  default:
bad_obj:
   __vpi_err(1874, vpiError,
    "vpiLoad 1-to-many iterator from %s illegal - for one bit net or reg loads only",
    __to_vpionam(__wrks1, hrp->htyp));
  }  
 return(NULL);
}

/*
 * build bit XL collapsed style net loads iterator
 *
 * caller must know type of iterator that is scanned since ld and driver
 * same except for list used
 *
 * differs from acc next load "iterators" because returns contas and
 * does not distinguish cells 
 */
static vpiHandle bit_xl_ldsdrvs_iter(struct h_t *hp, int32 do_loads)
{
 int32 vti, hi, hi2, bi, vtxnum, num, xlnum, new2siz;
 vpiHandle ihref;
 struct hrec_t *hrp;
 struct itree_t *itp;
 struct net_t *np;
 struct xldlvtx_t *xldlvp;
 struct pviter_t *iterp;

 itp = (struct itree_t *) hp->hin_idp[MD_ITP];
 hrp = hp->hrec;
 /* know if not bit object, then scalar net or reg */
 if (hrp->htyp == vpiReg || hrp->htyp == vpiNet)
  {
   np = hrp->hu.hnp;
   bi = -1;
  }
 else
  {
   if ((bi = cmp_drvld_bitndx(&np, hp, "vpiLoad")) == -1) return(NULL);
  }
 /* know there will always be one */
 /* 4th arg. T means loads */
 vtxnum = __bld_xl_drvld_vtxtab(np, bi, itp, do_loads);

 for (vti = 0, xlnum = 0; vti < vtxnum; vti++)
  {
   xldlvp = __xldlvtxind[vti];
   /* DBG remove -- */
   if (xldlvp == NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */

   /* fill ith tab with only non port loads or drivers */ 
//AIV INUM FIXME - why are these the exact same???????????????
   if (do_loads)
    {
     num = bld_bit_lds(xldlvp->dlnp, xldlvp->dlbi, xldlvp->dlitp->it_idp,
        TRUE);
    }
   else
    {
     num = bld_bit_drvs(xldlvp->dlnp, xldlvp->dlbi, xldlvp->dlitp->it_idp, 
        TRUE);
    }

   /* copy onto end of 2nd ith tab */
   if (num > 0)
    {
     new2siz = xlnum + num;
     if (new2siz >= __ithtsiz2) __grow_hptab2(num);

     for (hi = xlnum, hi2 = 0; hi < num + xlnum; hi++, hi2++)
      {
       __ithptab2[hi] = __ithptab[hi2];
       __ithptab[hi2] = NULL;
      }
     xlnum += num;
    }
   __my_free(xldlvp, sizeof(struct xldlvtx_t));
   __xldlvtxind[vti] = NULL;
  }
 __num_xldlvtxs = 0;

 /* iterator may be empty */
 if(xlnum <= 0) return(NULL);

 /* final step copy from 2nd ith tab into iterator */
 iterp = __alloc_empty_iter(xlnum, &ihref);
 for (hi = 0; hi < xlnum; hi++)
  {
   iterp->scanhptab[hi] = __ithptab2[hi];
   __ithptab2[hi] = NULL;
  }
 /* xl style ld/drvr vertex table to empty */
 return(ihref);
}

/*
 * ROUTINES TO BUILD LOCAL DRIVER ITERATOR 
 */

/*
 * build an iterator of local wire drivers
 *
 * regs have only qausi-continuous vpiForce and vpiRelease drivers
 *
 * includes user added vpi drivers
 *
 * inout ports and trans are both loads and drivers 
 * user must traverse all of channel to get hard drivers of inout
 */
extern vpiHandle __bld_loc_drvs_iterator(struct h_t *hp, int32 otype)
{
 if (hp == NULL) return(__nil_iter_err(otype));

 switch (hp->hrec->htyp) {
  case vpiNet:
   return(net_drvs_iter(hp));
  case vpiNetBit:
   return(bit_drvs_iter(hp));

  case vpiReg: case vpiIntegerVar: case vpiTimeVar:
  case vpiRegBit: case vpiVarSelect:
   /* quasi-procedural force and assign are only drivers of regs */
   /* also never per bit */
   return(reg_drvs_iter(hp));
  default:
   __vpi_err(1877, vpiError,
    "vpiDriver 1-to-many iterator from %s illegal - only variables have drivers",
    __to_vpionam(__wrks1, hp->hrec->htyp));
  }  
 return(NULL);
}

/*
 * build entire wire net drivers iterator - in list if any bits
 *
 * normal drivers plus pull and per bit force
 */
static vpiHandle net_drvs_iter(struct h_t *hp)
{
 int32 hi, num;
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 np = hp->hrec->hu.hnp;
 num = bld_net_drvs(np, hp->hin_idp);
 if (num <= 0) return(NULL);

 iterp = __alloc_empty_iter(num, &ihref);
 for (hi = 0; hi < num; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * build drivers on a net
 *
 * entire net drivers are not net bit
 * nothing on itree stack here
 */
static int32 bld_net_drvs(struct net_t *np, t_midat *idp)
{
 int32 bi;
 int32 cnt, cnt2, inum;
 struct net_pin_t *npp;
 struct h_t tmph, *hp2;
 struct hrec_t tmphrec, *hrp2;
 struct qcval_t *frc_qcp; 
 struct itree_t *itp;
 decl_idp_locals_;
 
 set_save_idp_(idp);
 for (cnt = 0, npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   /* SJM 09/20/02 - for per bit input port drivers only use first */
   if (npp->npntyp == NP_PB_MDPRT && npp->pbi != 0) continue; 

   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != idp) 
    continue;
   /* maybe move to right ref. itree loc. */ 
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - must match each inst in xmr path */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }
   __init_hrec(&tmphrec);
   tmphrec.in_iter = TRUE;
   tmph.hrec = &(tmphrec);

   if (!fill_drv_handle(&(tmph), &(tmphrec), npp)) continue;

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   hrp2 = hp2->hrec;
   memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
  }
 cnt2 = cnt;
 /* will be no drivers and no tran channel for reg */
 if (np->ntyp >= NONWIRE_ST)
  {
   /* DBG remove --- */
   if (np->ndrvs != NULL || np->ntraux != NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   goto do_force;
  } 
 /* tran channel npps - go in both ld and driver iterators */
 if (np->ntraux == NULL) goto do_force;

 /* notice any tran channel tran/inout port is driver and load */
 for (npp = np->ntraux->tran_npps; npp != NULL; npp = npp->npnxt)
  {
   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != idp)
     continue;
   /* maybe move to right ref. itree loc. */ 
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - must match each inst in xmr path */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }

   __init_hrec(&tmphrec);
   tmphrec.in_iter = TRUE;
   tmph.hrec = &tmphrec;

   if (!fill_drv_handle(&tmph, &tmphrec, npp)) continue;

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   hrp2 = hp2->hrec;
   memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
  }
 cnt2 = cnt;

do_force:
 /* if not in src or added by PLI, can't be active */  
 if (!np->frc_assgn_allocated) goto done;

 /* for scalar bit 0 right */
 /* ?? LOOKATME - this was low to high */
 inum = get_inum_();
 frc_qcp = &(np->nu2.qcval[inum*np->nwid + np->nwid - 1]);
 /* 11/22/02 AIV removed equal in for break bi >= */
 for (bi = np->nwid - 1; bi > 0; bi--, frc_qcp--)
  {
   /* 11/22/02 AIV must check for null case */
   if(frc_qcp == NULL) break;
   if (frc_qcp->qc_active)
    {
     /* FIXME - vpi_ driver not found as driver - vpi_ must keep track */ 
     /* if vpi_ force, do not return as driver */
     if (frc_qcp->qcstp == NULL) continue;

     __init_hrec(&tmphrec);
     tmphrec.in_iter = TRUE;
     tmph.hrec = &tmphrec;

     tmphrec.htyp = vpiForce;
     tmphrec.hu.hstp = frc_qcp->qcstp;
     tmph.hin_idp = __idp;

     if (cnt != 0 && same_vpi_handle(__ithptab, cnt2, cnt, &tmph, &tmphrec))
      continue;

     if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
     hp2 = __get_new_hp_handle();
     __ithptab[cnt++] = hp2;
     hp2->hin_idp = tmph.hin_idp;
     hrp2 = hp2->hrec;
     memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
    }
  }

done:
 restore_idp_();
 return(cnt);
}

/*
 * fill a driver handle (hp) - if non handle element, return nil
 * notice same rules for loads and drivers (iterator type determines)
 *
 * caller must have initialized fields (for iterator type) 
 * this must be called from ref. (stacked itree loc) for xmr 
 */
static int32 fill_drv_handle(struct h_t *hp, struct hrec_t *hrp,
 struct net_pin_t *npp)
{
 struct itree_t *itp2, *cur_itp;
 struct gate_t *gp;

 hp->hin_idp = __idp;
 switch ((byte) npp->npntyp) {
  case NP_ICONN: case NP_BIDICONN:
   /* SJM 09/20/02 - PB ICONN form only possible for loads */
   /* iconn driver is output port */
   hrp->htyp = vpiPort;
   hrp->hu.hpi = npp->obnum;
   cur_itp = get_itp_();
   itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
   hp->hin_idp = itp2->it_idp;
   break;
  case NP_MDPRT: case NP_BIDMDPRT: case NP_PB_MDPRT:
   /* iconn driver is input port */
   hrp->htyp = vpiPort;
   hrp->hu.hpi = npp->obnum;
   break;
  case NP_CONTA:
   hrp->htyp = vpiContAssign;
   hrp->hu.hcap = npp->elnpp.ecap;
   break;
  case NP_GATE: case NP_TRANIF: case NP_TRAN:
   gp = npp->elnpp.egp; 
   if (gp->gmsym->el.eprimp->gateid == G_ASSIGN)
    {
     hrp->htyp = vpiContAssign;
     hrp->htyp2 = vpiGate;
     hrp->hu.hgp = gp;
    }
   else
    {
     hrp->htyp = vpiPrimTerm;
     hrp->hu.hgp = gp;
     hrp->hi = npp->obnum;
    }
   break;
  case NP_VPIPUTV:
   /* include entire wire or any bit's driver here */
   if (npp->npaux != NULL && npp->npaux->nbi1 != -1)
    {
     hrp->htyp = vpiNetBitDriver;  
     hrp->hi = npp->npaux->nbi1;
    }
   else hrp->htyp = vpiNetDriver;
   hrp->hu.hnpp = npp;
   break;
  case NP_PULL:
   gp = npp->elnpp.egp; 
   hrp->htyp = vpiPrimTerm;
   hrp->hu.hgp = gp;
   hrp->hi = npp->obnum;
   break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * build the iterator for all port bits connecting to inside module instances
 * given a vpi net or reg bit handle, build iterator of port bit handles
 */
static vpiHandle bit_drvs_iter(struct h_t *hp)
{
 int32 hi, bi, num;
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;

 if ((bi = cmp_drvld_bitndx(&np, hp, "vpiDriver/vpiLocalDriver")) == -1)
  return(NULL);

 num = bld_bit_drvs(np, bi, hp->hin_idp, FALSE);
 if (num <= 0) return(NULL);

 iterp = __alloc_empty_iter(num, &ihref);
 for (hi = 0; hi < num; hi++)
  {
   iterp->scanhptab[hi] = __ithptab[hi];
   __ithptab[hi] = NULL;
  }
 return(ihref);
}

/*
 * build net bit drivers iterator
 *
 * nothing on itree stack here?
 * since per bit never a need to remove duplicates
 */
static int32 bld_bit_drvs(struct net_t *np, int32 bi, t_midat *idp,
 int32 no_ports)
{
 int32 ri1, ri2, cnt, inum;
 struct net_pin_t *npp;
 struct h_t tmph, *hp2;
 struct hrec_t tmphrec, *hrp2;
 struct qcval_t *frc_qcp;
 struct itree_t *itp;
 decl_idp_locals_;
 
 set_save_idp_(idp);
 /* iconn drivers are output ports */
 for (cnt = 0, npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != __idp) 
    continue;

   /* can be iconn from other instance for xmr */
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - must match each inst in xmr path */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }

   /* this must run with right itree loc. */
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   /* for scalar bi will be -1 here */  
   if (ri1 == -1 || bi == -1) goto got_match;   
   if (bi > ri1 || bi < ri2) continue;

got_match:
   if (no_ports)
    {
     /* remove port npp's */
     switch ((byte) npp->npntyp) {
      case NP_ICONN: case NP_BIDICONN: case NP_MDPRT: case NP_BIDMDPRT:
      case NP_PB_MDPRT: case NP_PB_ICONN:
       continue;
      default: break;
     }
    }
   __init_hrec(&tmphrec);
   tmphrec.in_iter = TRUE;
   tmph.hrec = &tmphrec;

   if (!fill_bit_drv_handle(&tmph, &tmphrec, bi, ri1, ri2, npp)) continue; 

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   hrp2 = hp2->hrec;
   memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
  }
 /* will be no drivers and no tran channel for reg */
 if (np->ntyp >= NONWIRE_ST)
  {
   /* DBG remove --- */
   if (np->ndrvs != NULL || np->ntraux != NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   goto do_force;
  }
 /* tran channel connections if they exist */
 if (np->ntraux == NULL) goto do_force;

 /* iconn drivers are output ports */
 for (npp = np->ntraux->tran_npps; npp != NULL; npp = npp->npnxt)
  {
   /* filter out per inst. that is not this instance */
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != __idp) 
    continue;

   /* can be iconn from other instance for xmr */
   if (npp->npproctyp != NP_PROC_INMOD)
    {
     /* SJM 04/17/03 - must match each inst in xmr path */
     if ((itp = __get_npprefloc(npp)) == NULL) continue;
     set_idp_(itp->it_idp); 
    }

   /* this must run with right itree loc. */
   __get_bidnpp_sect(np, npp, &ri1, &ri2);
   /* for scalar bi will be -1 here */  
   if (ri1 == -1 || bi == -1) goto got2_match;   
   if (bi > ri1 || bi < ri2) continue;

got2_match:
   if (no_ports)
    {
     /* remove port npp's */
     switch ((byte) npp->npntyp) {
      case NP_ICONN: case NP_BIDICONN: case NP_MDPRT: case NP_BIDMDPRT:
      case NP_PB_ICONN: case NP_PB_MDPRT:
       continue;
      default: break;
     }
    }

   __init_hrec(&tmphrec);
   tmphrec.in_iter = TRUE;
   tmph.hrec = &tmphrec;

   if (!fill_bit_drv_handle(&(tmph), &(tmphrec), bi, ri1, ri2, npp)) continue; 

   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = tmph.hin_idp;
   hrp2 = hp2->hrec;
   memcpy(hrp2, &(tmphrec), sizeof(struct hrec_t));
  }

do_force:
 if (!np->frc_assgn_allocated) goto done;
 /* this is 1 bit form */
 inum = get_inum_();
 frc_qcp = &(np->nu2.qcval[inum*np->nwid + ((bi == -1) ? 0 : bi)]);
 if (frc_qcp->qc_active)
  {
   /* FIXME - vpi_ driver not found as driver - vpi_ must keep track */ 
   /* if vpi_ force, do not return as driver */
   if (frc_qcp->qcstp == NULL) goto done;

   /* there is an active force - maybe just constant */
   if (cnt >= __ithtsiz) __grow_hptab(cnt + 1);
   hp2 = __get_new_hp_handle();
   __ithptab[cnt++] = hp2;
   hp2->hin_idp = __idp;
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;
   hrp2->htyp = vpiForce;
   hrp2->hu.hstp = frc_qcp->qcstp;
  }
done:
 restore_idp_();
 return(cnt);
}

/*
 * fill a bit driver handle - if non handle element, return nil
 *
 * caller must have initialized fields in handle
 * this must be called from ref. (stacked itree loc) for xmr 
 *
 * looking for driver of net np bit bi (if scalar not called) 
 *
 * LOOKATME - except for pull, same as fill bit ld handle - right?
 */
static int32 fill_bit_drv_handle(struct h_t *hp, struct hrec_t *hrp, int32 bi,
 int32 ri1, int32 ri2, struct net_pin_t *npp)
{
 int32 not_lhs;
 struct itree_t *itp2, *cur_itp;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 struct gate_t *gp;
 struct mod_t *cur_mdp;

 hp->hin_idp = __idp;
 switch ((byte) npp->npntyp) {
  case NP_ICONN: case NP_BIDICONN:
   /* driver iconn is output port */
   cur_itp = get_itp_();
   itp2 = &(cur_itp->in_its[npp->elnpp.eii]);
   downmdp = itp2->itip->imsym->el.emdp;
   mpp = &(downmdp->mpins[npp->obnum]);
   if (!iconnbit_lvalue(mpp, npp, itp2)) not_lhs = TRUE; 
   else not_lhs = FALSE;
   if (mpp->mpwide == 1 || not_lhs) hrp->htyp = vpiPort;
   else
    {
     hrp->htyp = vpiPortBit;
     /* notice these are internal h:0 - fixed when index accessed */
     /* correct for port bit from non concatenate net bit */ 
     if (ri1 == -1) hrp->hi = bi; else hrp->hi = bi - ri2;
    }
   hrp->hu.hpi = npp->obnum;
   hp->hin_idp = itp2->it_idp;
   break;
  case NP_MDPRT: case NP_BIDMDPRT:
   /* driver mod port is input port */
   cur_mdp = get_inst_mod_();
   mpp = &(cur_mdp->mpins[npp->obnum]);
   if (mpp->mpref->optyp == LCB || mpp->mpwide == 1) hrp->htyp = vpiPort;
   else
    {
     hrp->htyp = vpiPortBit;
     /* notice these are internal h:0 - fixed when index accessed */
     /* correct for port bit from non concatenate net bit */ 
     if (ri1 == -1) hrp->hi = bi; else hrp->hi = bi - ri2;
    }
   hrp->hu.hpi = npp->obnum;
   break;
  case NP_PB_MDPRT:
   /* driver is bit of separated into per bits mod input port */
   hrp->htyp = vpiPortBit;
   hrp->hu.hpi = npp->obnum;
   if (ri1 == -1) hrp->hi = bi; else hrp->hi = bi - ri2;
   break;
  case NP_CONTA:
   hrp->htyp = vpiContAssign;
   hrp->hu.hcap = npp->elnpp.ecap;
   break;
  case NP_GATE: case NP_TRANIF: case NP_TRAN:
   gp = npp->elnpp.egp; 
   /* must correct for 1 bit conta */
   if (gp->gmsym->el.eprimp->gateid == G_ASSIGN)
    {
     hrp->htyp = vpiContAssign;
     hrp->htyp2 = vpiGate;
     hrp->hu.hgp = npp->elnpp.egp;
     break;
    }
   hrp->htyp = vpiPrimTerm;
   hrp->hu.hgp = gp;
   hrp->hi = npp->obnum;
   break;
  case NP_VPIPUTV:
   /* include entire wire (know overlaps) or matching bit's driver here */
   if (npp->npaux != NULL && npp->npaux->nbi1 != -1)
    {
     if (npp->npaux->nbi1 != bi) break; 
     hrp->htyp = vpiNetBitDriver;  
     hrp->hi = npp->npaux->nbi1;
    }
   else hrp->htyp = vpiNetDriver;
   hrp->hu.hnpp = npp;
   break;
  case NP_PULL: 
   gp = npp->elnpp.egp; 
   hrp->htyp = vpiPrimTerm;
   hrp->hu.hgp = gp;
   hrp->hi = npp->obnum;
   break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * build iterator for drivers of a reg (or variable)
 *
 * only possible drivers are quasi continuous force or assign 
 * notice only one can be active (i.e. either no iter or size 1)
 *
 * d.s for reg qcval is 2 qcval's per inst. - one for entire reg force and
 * one for qc assign 
 */
static vpiHandle reg_drvs_iter(struct h_t *hp)
{
 int32 itinum; 
 struct hrec_t *hrp2;
 vpiHandle ihref;
 struct net_t *np;
 struct pviter_t *iterp;
 struct h_t *hp2;
 struct qcval_t *assgn_qcp, *frc_qcp;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 np = hrp->hu.hnp;
 itinum = (int32) hp->hin_idp[MD_INUM];
 /* not in src or added by PLI, can't be active */
 if (!np->frc_assgn_allocated) return(NULL);

 frc_qcp = &(np->nu2.qcval[2*itinum]);
 if (frc_qcp->qc_active)
  {
   /* FIXME - vpi_ driver not found as driver - vpi_ must keep track */ 
   /* if vpi_ force know will not be reg qc assign */
   if (frc_qcp->qcstp == NULL) return(NULL);

   /* there is an active force - maybe just constant */
   iterp = __alloc_empty_iter(1, &ihref);
   __iter_fill_with_empty(iterp);
   hp2 = iterp->scanhptab[0];
   hp2->hin_idp = hp->hin_idp;
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiForce;
   hrp2->hu.hstp = frc_qcp->qcstp;
   return(ihref);
  }

 assgn_qcp = &(np->nu2.qcval[2*itinum + 1]);
 if (!assgn_qcp->qc_active) return(NULL);
 iterp = __alloc_empty_iter(1, &ihref);
 __iter_fill_with_empty(iterp);
 hp2 = iterp->scanhptab[0];
 hp2->hin_idp = hp->hin_idp;
 hrp2 = hp2->hrec;
 hrp2->htyp = vpiAssignStmt;
 hrp2->hu.hstp = assgn_qcp->qcstp;
 return(ihref);
}

/* 
 * ROUTINES TO BUILD XL STYLE DRIVER ITERATOR (SCALAR OR BIT ONLY)
 */

/*
 * build an iterator of wire or reg bit XL style collapsed drivers
 *
 * inout ports and trans are both loads and drivers 
 *
 * no ports here - cross and include actual loads from other side
 * algorithm sort of (mostly?) duplicates XL collapsing
 * only makes sense for 1 bit objects
 */
extern vpiHandle __bld_drvs_iterator(struct h_t *hp, int32 otype)
{
 if (hp == NULL) return(__nil_iter_err(otype));

 /* routine for each thing that load can be of */
 switch (hp->hrec->htyp) {
  case vpiNet: case vpiReg: 
   if (hp->hrec->hu.hnp->nwid != 1) goto bad_obj;
   return(bit_xl_ldsdrvs_iter(hp, FALSE));
  case vpiNetBit:
   return(bit_xl_ldsdrvs_iter(hp, FALSE));

  /* quasi-procedural force and assign are only drivers of regs */
  /* also really never per bit and no cross module iconn/port */
  case vpiRegBit: case vpiVarSelect:
   return(reg_drvs_iter(hp));

  default:
bad_obj:
   __vpi_err(1874, vpiError,
    "vpiLoad 1-to-many iterator from %s illegal - for one bit net or reg loads only",
    __to_vpionam(__wrks1, hp->hrec->htyp));
  }  
 return(NULL);
}

/*
 * ITERATOR SCAN ROUTINES
 */

/*
 * given a handle returned by vpi iterator, get next object
 * and move to one past
 *
 * easy since table of right object type handles already built
 * LOOKATME - for empty iterator is this supposed to return nil (think yes)
 */
extern vpiHandle vpi_scan(vpiHandle iterator)
{
 struct pviter_t *iterp;
 struct h_t *ihp, *hp;
 
 /* assume no error */
 __last_eip = NULL;
 if (__run_state == SS_COMP) { __still_comp_err("vpi_scan"); return(NULL); } 
 ihp = (struct h_t *) iterator;
 if (ihp == NULL) return(NULL);
 if (!__validate_handle("vpi_scan (iterator)", ihp)) return(NULL);
 if (ihp->hrec->htyp != vpiIterator) 
  {
   __vpi_err(1864, vpiError,
    "vpi_scan passed handle of type %s - must be vpiIterator",
    __to_vpionam(__wrks1, ihp->hrec->htyp));
   return(NULL);
  }
 /* for last, return and move past end - then next call return nil and free */
 iterp = ihp->hrec->hu.hiterp;
 if (iterp->nxthi == -1) 
  {
   __vpi_err(1862, vpiError,
    "vpi_scan iterator handle invalid because scan already finished or error");
   return(NULL);
  }
 if (iterp->nxthi >= iterp->numhs)
  {
   iterp->nxthi = -1;
   __free_iterator(iterator);
   return(NULL);
  }
 hp = iterp->scanhptab[iterp->nxthi];
 /* here can not free since corrupt handle */
 if (!__validate_handle("vpi_scan (component)", hp))
  {
   iterp->nxthi = -1;
   return(NULL);
  } 
 (iterp->nxthi)++;
 return((vpiHandle) hp);
}

/*
 * ROUTINES FOR OBTAINING HANDLES
 */
 
/*
 * get handle by name - use symbol table of scope (task or itree loc) 
 *
 * LRM does not allow vpiFullName for ports
 */
extern vpiHandle vpi_handle_by_name(char *name, vpiHandle scope)
{
 int32 sav_ecnt;
 vpiHandle href; 
 struct h_t *hp;
 struct symtab_t *sytp;
 struct hrec_t *hrp;
 struct mod_t *mdp;

 sav_ecnt = __pv_err_cnt;
 __last_eip = NULL;
 if (__run_state == SS_COMP)
  { __still_comp_err("vpi_handle_by_name"); return(NULL); } 
 if (scope == NULL)
  {
   /* AIV 09/15/10 - this needs to pass NULL here */
   /* this must have been wrong since when we converted to idp */
   href = cnvt_name_to_handle(name, NULL, __idp);
   goto done;
  }

 hp = (struct h_t *) scope;
 if (!__validate_handle("vpi_handle_by_name", hp)) return(NULL);
 hrp = hp->hrec;
 switch (hrp->htyp) {
  case vpiModule:
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   sytp = mdp->msymtab;
   break;
  case vpiTask: case vpiFunction:
   sytp = hrp->hu.htskp->tsksymtab;
   break;
  case vpiNamedBegin: case vpiNamedFork:
   sytp = hrp->hu.htskp->tsksymtab;
   break; 
  default:
   __vpi_err(1868, vpiError,
    "vpi_handle_by_name scope object must be scope handle - %s illegal",
   __to_vpionam(__wrks1, hrp->htyp));
  return(NULL);
 }
 href = cnvt_name_to_handle(name, sytp, hp->hin_idp);

done:
 if (sav_ecnt < __pv_err_cnt)
  {
   __vpi_err(1878, vpiError,
    "vpi_handle_by_name failed - name %s illegal", name);
  }
 return(href);
}

/*
 * convert a name to a handle 
 *
 * sytp is scope to start in - if nil, then reference is rooted 
 * if sytp nil so must be scopitp
 *
 * on error, this returns nil
 * FIXME - figure out whether last gnc was set to last or to last non net
 *         if so this routine is wrong because it uses last
 * LOOKATME - this routine fails on arr of insts (comp. with numeric ind)
 *            but so far that is correct unless LRM changes - if g/i array 
 *            passed, not seen here
 */
static vpiHandle cnvt_name_to_handle(char *nam, struct symtab_t *sytp,
 t_midat *idp)
{
 int32 ii, has_dot;
 struct itree_t *itp;
 struct expr_t *glbndp, *gcmp_ndp;
 struct sy_t *syp, *hsyp;
 struct mod_t *mdp;
 struct inst_t *ip;
 char *chp;
 byte *bp1, *bp2;

 /* case 1 - xmr name */
 has_dot = __name_vpi_hasdot(nam);
 if (has_dot)
  {
   itp = NULL;
   if ((glbndp = __glbnam_to_expr(nam)) == NULL) return(NULL);
   gcmp_ndp = glbndp->ru.x;
   if (sytp == NULL)
    {
     chp = __to_glbcmp_nam(gcmp_ndp);
     if ((ii = __ip_indsrch(chp)) == -1)
      {
ret_nil:
       if (glbndp != NULL) __free_xtree(glbndp);
       return(NULL);
      }
     itp = __it_roots[ii];
     sytp = itp->itip->imsym->el.emdp->msymtab;
     gcmp_ndp = gcmp_ndp->ru.x;
    }
   else itp = (struct itree_t *) idp[MD_ITP];

   for (; gcmp_ndp != NULL;)
    {
     chp = __to_glbcmp_nam(gcmp_ndp);
     /* look up first in context then in specify section */
     if ((syp = __get_nongia_sym(chp, sytp)) == NULL)
      {
       if (gcmp_ndp->ru.x != NULL) goto ret_nil;
       /* this is last component */
       hsyp = sytp->sypofsyt; 
       if (hsyp->sytyp != SYM_M) goto ret_nil;
 
       mdp = itp->itip->imsym->el.emdp;
       /* first try specify section if it exists */ 
       if (mdp->mspfy != NULL)
        {
         if ((syp = __get_sym(chp, mdp->mspfy->spfsyms)) != NULL)
          {
           if (glbndp != NULL) __free_xtree(glbndp);
           return(bld_symhandle(nam, syp, sytp, itp));
          }
        }
       goto ret_nil;
      }
     /* non scope symbol found in scope */
     if (!__is_scope_sym(syp))
      { 
       /* if non scope symbol but not end of path - mismatch */
       if (gcmp_ndp->ru.x != NULL) goto ret_nil;
       if (glbndp != NULL) __free_xtree(glbndp);
       /* end of path build whatever it is */
       return(bld_symhandle(nam, syp, sytp, itp));
      }
     /* if last symbol, build the scope handle - this is inst. type ref */
     if (gcmp_ndp->ru.x == NULL)
      { 
       if (glbndp != NULL) __free_xtree(glbndp);
       return(bld_symhandle(nam, syp, sytp, itp));
      }
     /* scope symbol - maybe descend */
     if (syp->sytyp == SYM_I)
      {
       /* syp in itp */
       ip = syp->el.eip;
       mdp = itp->itip->imsym->el.emdp;
       bp1 = (byte *) ip;
       bp2 = (byte *) mdp->minsts;
       ii = (bp1 - bp2)/sizeof(struct inst_t);
       itp = &(itp->in_its[ii]);
       sytp = itp->itip->imsym->el.emdp->msymtab;
      }
     else sytp = syp->el.etskp->tsksymtab;
     if ((gcmp_ndp = gcmp_ndp->ru.x) == NULL) break;
    }
   __vpi_terr(__FILE__, __LINE__);
   if (glbndp != NULL) __free_xtree(glbndp);
   return(NULL);
  }

 /* case 2: simple name */
 itp = (struct itree_t *) idp[MD_ITP];
 /* top level module name */ 
 if (sytp == NULL)
  {
   /* LOOKATME - could add getting user defined systf here by name */
   /* but LRM says only things with vpiFullName properties can be accessed */
   if ((ii = __ip_indsrch(nam)) == -1)
    {
     return(NULL);
    }
   itp = __it_roots[ii];
   return(__mk_handle(vpiModule, (void *) itp->itip->imsym->el.emdp, 
     itp->it_idp, (struct task_t *) NULL));
  }
 hsyp = sytp->sypofsyt; 
 /* case 1b simple name in some scope */
 if ((syp = __get_nongia_sym(nam, sytp)) == NULL)
  {
   if (hsyp->sytyp != SYM_M) return(NULL);

   mdp = hsyp->el.emdp;
   /* try specify section if it exists */ 
   if (mdp->mspfy != NULL)
    {
     if ((syp = __get_sym(nam, mdp->mspfy->spfsyms)) != NULL)
      return(bld_symhandle(nam, syp, sytp, itp));
    }
   return(NULL);
  }
 /* simple name found in scope */
 return(bld_symhandle(nam, syp, sytp, itp));
}

/*
 * build a handle from a symbol
 *
 * nam here just for error messages
 */
static vpiHandle bld_symhandle(char *nam, struct sy_t *syp,
 struct symtab_t *sytp, struct itree_t *itp)
{
 int32 ii, ttyp;
 word32 otyp;
 vpiHandle href;
 struct sy_t *in_tsyp;
 struct task_t *intskp, *tskp;
 struct mod_t *mdp;
 struct inst_t *ip;
 struct itree_t *down_itp;
 struct gate_t *gp;
 struct net_t *np;
 struct h_t *hp;
 byte *bp1, *bp2;

 in_tsyp = sytp->sypofsyt;
 if (in_tsyp->sytyp == SYM_M) intskp = NULL; else intskp = in_tsyp->el.etskp;

 switch ((byte) syp->sytyp) {
   case SYM_I:
    if (intskp != NULL) __vpi_terr(__FILE__, __LINE__);
    mdp = itp->itip->imsym->el.emdp;  
    ip = syp->el.eip;
    bp1 = (byte *) ip;
    bp2 = (byte *) mdp->minsts;
    ii = (bp1 - bp2)/sizeof(struct inst_t);
    down_itp = &(itp->in_its[ii]);
    href = __mk_handle(vpiModule, (void *) down_itp->itip->imsym->el.emdp,
     down_itp->it_idp, (struct task_t *) NULL);
    break;
   case SYM_TSK: case SYM_F: case SYM_LB: 
    tskp = syp->el.etskp;
    ttyp = __to_vpi_tasktyp(tskp->tsktyp);
    href = __mk_handle(ttyp, (void *) tskp, itp->it_idp, intskp);
    break;
   case SYM_PRIM:
    if (intskp != NULL) __vpi_terr(__FILE__, __LINE__);
    gp = syp->el.egp;
    if (gp->gmsym->el.eprimp->gateid == G_ASSIGN)
     {
      href = __mk_handle(vpiContAssign, (void *) gp, itp->it_idp, NULL);
      hp = (struct h_t *) href;
      hp->hrec->htyp2 = vpiGate;
      break;
     }
    href = __mk_handle(__gate_to_vpiprimtyp(gp), (void *) gp, itp->it_idp,
       NULL);
    break;
   case SYM_N:
    np = syp->el.enp;
    if (np->n_isaparam)
     {
      /* case 1: specparam */
      if (np->nu.ct->p_specparam)
       {
        href = __mk_handle(vpiSpecParam, (void *) np, itp->it_idp, NULL);
       }
      else
       {
        /* case 2: parameter */ 
        /* if local imported param - always returns global "real" copy */
        /* now just fall thru to make param handle */
        href = __mk_handle(vpiParameter, (void *) np, itp->it_idp, NULL);
       }
      break;  
     }
    /* case 3: variable (wire/net) and never select */
    /* 01/25/00 SJM - for imported global net this is just normal net */
    otyp = __ntyp_to_vpivarhtyp(np);
    href = __mk_handle(otyp, (void *) np, itp->it_idp, intskp); 
    break;
   /* these are Cver extensions for added delay setting system tasks */
   case SYM_CA:
    href = __mk_handle(vpiContAssign, (void *) syp->el.ecap, itp->it_idp, 
      NULL);
    break;
   case SYM_TCHK:
    href = __mk_handle(vpiTchk, (void *) syp->el.etcp, itp->it_idp, NULL);
    break;
   case SYM_PTH:
    href = __mk_handle(vpiTchk, (void *) syp->el.epthp, itp->it_idp, NULL);
    break;
   case SYM_UDP:
    __vpi_err(1856, vpiError,
     "vpi_handle_by_name of udp definition %s object not supported",
     nam);
    return(NULL);
   /* never should see SYM_M - if top level this not called */
   /* preprocess (SYM_DEF) and system task (SYM_SF) never seen here */
   default: __vpi_terr(__FILE__, __LINE__); return(NULL);
  }
 return(href);
}

/*
 * return T if has dot (xmr type path)
 *
 * tricky because name in xmr paths can be escaped
 */
extern int32 __name_vpi_hasdot(const char *nam)
{
 char *chp;

 for (chp = nam; *chp != '\0'; chp++)
  {
   if (*chp == '.') return(TRUE);
   if (*chp == '\\')
    {
     for (chp++;; chp++)
      {
       if (*chp == ' ') goto nxt_comp; 
       if (*chp == '\0') break;
      }
     return(FALSE);
    }
nxt_comp:;
  }
 return(FALSE);
}

/*
 * get a bit handle from its index
 *
 * error and return NULL for non indexable handle
 * this is passed user [i1:i2] range index instead of normalized internal
 */
extern vpiHandle vpi_handle_by_index(vpiHandle object, int32 indx)
{  
 int32 biti, ri1, ri2, wid;
 word32 ityp;
 word32 av, bv;
 vpiHandle href;
 struct h_t *hp, *hp2;
 struct net_t *np;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 struct xstk_t *xsp;
 struct hrec_t *hrp, *hrp2;

 __last_eip = NULL;
 if (__run_state == SS_COMP)
  { __still_comp_err("vpi_handle_by_index"); return(NULL); } 
 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_handle_by_index", hp)) return(NULL);
 hrp = hp->hrec;

 ri1 = ri2 = 0;
 switch (hrp->htyp) {
  case vpiMemory:
   /* convert index to internal range */
   np = hrp->hu.hnp;
   if (!np->n_isarr) __vpi_terr(__FILE__, __LINE__);
   __getarr_range(np, &ri1, &ri2, &wid);
   biti = normalize_ndx_(indx, ri1, ri2);
   if (biti < 0 || biti >= wid)
    {
bad_ndx:
     __vpi_err(1828, vpiError,
      "vpi_handle_by_index index %d of %s out of range [%d:%d]", indx,
      __to_vpionam(__wrks1, hrp->htyp), ri1, ri2);
     return(NULL);
    }
   ityp = vpiMemoryWord;
   href = __mk_handle(ityp, (void *) np, hp->hin_idp, NULL);
   hp2 = (struct h_t *) href;
   hrp2 = hp2->hrec;
   hrp2->hi = biti;
   hrp2->bith_ndx = TRUE;
   break;
  case vpiMemoryWord:
   /* LOOKATME - should this be vpiRegBit object? */
   /* this evaluates expr. to array and bit or for bith form just get ndx */
   biti = __get_vpinet_index(&np, hp);

   /* DBG remove --- */
   if (!np->n_isarr) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   if (!np->n_isavec) goto no_ndx;
   /* load the array */
   push_xstk_(xsp, np->nwid); 
   __ld_arr_val(xsp, NULL, np, biti, NULL);
   /* determine (normalize) bit */
   __getwir_range(np, &ri1, &ri2);
   biti = normalize_ndx_(indx, ri1, ri2);
   if (biti < 0 || biti >= np->nwid) { __pop_xstk(); goto bad_ndx; }
   av = rhsbsel_(xsp->ap, biti);
   bv = rhsbsel_(xsp->bp, biti);
   __pop_xstk();
   href = __mk_handle(vpiConstant, (void *) NULL, hp->hin_idp,
    hp->hrec->hin_tskp);
   hp2 = (struct h_t *) href;
   hrp2 = hp2->hrec;
   hrp2->hu.hxp = __bld_rng_numxpr(av, bv, 1);
   hrp2->free_xpr = TRUE;
   break;
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   np = hrp->hu.hnp;
   if (!np->n_isavec)
    {
no_ndx:
     __vpi_err(2027, vpiWarning,
      "vpi_handle_by_index of non indexable object %s - index of scalar illegal",  
      __to_vpionam(__wrks1, hrp->htyp));
     return(NULL);
    }
   __getwir_range(np, &ri1, &ri2);
   biti = normalize_ndx_(indx, ri1, ri2);
   if (biti < 0 || biti >= np->nwid) goto bad_ndx;
   ityp = __to_vpinetbithtyp(np->ntyp);
   href = __mk_handle(ityp, (void *) np, hp->hin_idp, NULL);
   hp2 = (struct h_t *) href;
   hrp2 = hp2->hrec; 
   hrp2->hi = biti;
   hrp2->bith_ndx = TRUE;
   break;
  case vpiPort: 
   /* port ranges always wid-1:0 since not declared (can be 0) */
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   if (mpp->mpwide == 1) goto no_ndx;
   ri1 = mpp->mpwide - 1;
   ri2 = 0;
   if (indx < 0 || indx > ri1) goto bad_ndx;
   href = __mk_handle(vpiPortBit, (void *) hrp->hu.hpi, hp->hin_idp, NULL);
   hp2 = (struct h_t *) href;
   hrp2 = hp2->hrec;
   hrp2->hi = indx;
   break;
  default:
   __vpi_err(1846, vpiError,
    "vpi_handle_index failed because %s has no contained indexable object", 
    __to_vpionam(__wrks1, hrp->htyp));
   return(NULL);  
 }  
 return(href);
}

/*
 * new handle by index that requires new 2001 multi-dimensional vectors
 * and is only way to access them by indexing
 *
 * WRITME - add multi-dimensional vector support
 */
extern vpiHandle vpi_handle_by_multi_index(vpiHandle obj, PLI_INT32 num_index,
 PLI_INT32 *index_array)
{
 __vpi_err(1801, vpiError,
  "new P1364 2001 vpi_handle_by_multi_index unsupported because multi-dimensional arrays not supported");
 return(NULL);
}

/*
 * ROUTINES TO GET PROPERTIES
 */

/* 
 * get property type property for object object if it exists
 */
extern int32 vpi_get(PLI_INT32 property, vpiHandle object)
{
 PLI_INT32 pval;
 int32 casetyp;
 struct h_t *hp;
 struct hrec_t *hrp;

 __last_eip = NULL;
 if (__run_state == SS_COMP)
  {
   __still_comp_err("vpi_get");
   return(vpiUndefined);
  } 
 if (!validate_property("vpi_get", property)) return(0);
 /* special case return smallest time precision (not units) in design */
 if (object == NULL)
  {
   /* design wide these are same - could be timeformat unit */
   /* LOOKATME - acc_ equivalent returns timeformat precision here */ 
   if (property == vpiTimePrecision)
    { pval = -((int32) __des_timeprec); return(pval); } 
   else if (property == vpiTimeUnit)
    { pval = -((int32) __des_timeprec); return(pval); } 
   __vpi_err(1865, vpiError,  
    "property %s illegal for vpi_get with NULL object - only for timescale",
    __to_vpipnam(__wrks1, property));
   return(vpiUndefined);
  }
 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_get", hp)) return(vpiUndefined);
 hrp = hp->hrec;

 /* vpiType special meta property for handle object */
 if (property == vpiType) return(hrp->htyp);

 switch (hrp->htyp) {
  /* notice - not in LRM but iterators have size property */
  case vpiIterator:
   if (property != vpiSize)
    { notpropof_err(hrp->htyp, property); return(vpiUndefined); }
   return(hrp->hu.hiterp->numhs);
  case vpiModule:   
   pval = modprop_vpiget(hp, property);
   break;
  case vpiNet: case vpiNetBit:
   pval = netprop_vpiget(hp, property);
   break;
  case vpiReg: case vpiRegBit: case vpiIntegerVar: case vpiTimeVar:
  case vpiRealVar: case vpiVarSelect: case vpiNamedEvent:
   pval = regprop_vpiget(hp, property);
   break;
  case vpiMemory:
   pval = arrprop_vpiget(hp, property);
   break;
  case vpiMemoryWord:
   pval = arrwrdprop_vpiget(hp, property);
   break;
  case vpiParameter: case vpiSpecParam:
   pval = paramprop_vpiget(hp, property);
   break;
  case vpiPort: case vpiPortBit:
   pval = portprop_vpiget(hp, property);
   break;
  case vpiGate: case vpiUdp: case vpiSwitch:
   pval = gateprop_vpiget(hp, property);
   break;
  case vpiPrimTerm:
   pval = __primtermprop_vpiget(hp, property);
   break;
  case vpiContAssign:
   pval = contaprop_vpiget(hp, property);
   break;
  case vpiFuncCall: case vpiSysFuncCall:
   pval = fcallprop_vpiget(hp, property);
   break;
  case vpiTaskCall: case vpiSysTaskCall:
   pval = tcallprop_vpiget(hp, property);
   break;
  /* this is function definition not call */
  case vpiFunction:
   pval = funcdefprop_vpiget(hp, property);
   break;
  case vpiTchk:
   pval = tchkprop_vpiget(hp, property);
   break;
  case vpiTchkTerm:
   pval = tchktermprop_vpiget(hp, property);
   break;
  case vpiModPath:
   pval = pthprop_vpiget(hp, property);
   break;
  case vpiPathTerm:
   pval = pthtermprop_vpiget(hp, property);
   break;
  case vpiSchedBitEvent: 
   if (property != vpiScheduled)
    { notpropof_err(hrp->htyp, property); return(vpiUndefined); }
   /* for vector wire driver form only T if all bits done */
   if (hrp->evnt_done) return(FALSE);
   return(TRUE);
  case vpiSchedEvent:
   if (property != vpiScheduled)
    { notpropof_err(hrp->htyp, property); return(vpiUndefined); }
   /* for non table form bit determines if done or canceled */
   if (hrp->evnt_done) return(FALSE);
   /* table vectored driver form - must re-check for */
   if (hrp->bith_ndx)
    {
     int32 bi;
     struct net_t *np;
     struct tev_t **evtab, *tevp;

     np = hrp->hu.hevrec->evnp;
     evtab = hrp->hu.hevrec->evndxtab;
     /* ?? LOOKATME - this was low to high */
     for (bi = np->nwid - 1; bi >= 0; bi--)
      {
       tevp = evtab[bi];
       if (tevp != NULL && 
          (tevp->enterptr != __process_cancel_ev_enterp))
           {
             return(FALSE);
           }
      }
    }
   return(TRUE);

  /* all statements and processes - not processes (init/always) */
  case vpiAssignStmt: case vpiBegin: case vpiDeassign:
  case vpiDelayControl: case vpiEventControl: case vpiDisable:
  case vpiEventStmt: case vpiFor: case vpiForce: case vpiForever:
  case vpiFork: case vpiIf: case vpiIfElse: case vpiNullStmt:
  case vpiRelease: case vpiRepeat: case vpiWait: case vpiWhile:
try_line_prop:
   if (property != vpiLineNo)
    { notpropof_err(hrp->htyp, property); return(vpiUndefined); }
   pval = hrp->hu.hstp->stlin_cnt;
   break;
  /* named blocks are tasks although "in line" */ 
  case vpiNamedBegin: case vpiNamedFork:
   if (property != vpiLineNo)
    { notpropof_err(hrp->htyp, property); return(vpiUndefined); }
   pval = hrp->hu.htskp->tsksyp->sylin_cnt;
   break;
  case vpiDefParam:
   if (property != vpiLineNo)
    { notpropof_err(vpiDefParam, property); return(vpiUndefined); }
   pval = (int32) hrp->hu.hdfp->dfplin_cnt;
   break;
  case vpiParamAssign:
   if (property != vpiLineNo)
    { notpropof_err(vpiParamAssign, property); return(vpiUndefined); }
   pval = (int32) hrp->hu.hnp->nsym->sylin_cnt;
   break;
  case vpiAssignment:
   if (property == vpiBlocking)
    {
     if (hrp->hu.hstp->rl_stmttyp == S_NBPROCA) pval = TRUE;
     else pval = FALSE;
     break;
    }
   goto try_line_prop;
  case vpiCase:
   if (property == vpiCaseType)
    {
     casetyp = hrp->hu.hstp->st.scs.castyp;
     if (casetyp == CASEZ) pval = vpiCaseZ;
     else if (casetyp == CASEX) pval = vpiCaseX;
     else pval = vpiCaseExact;
     break;
    }
   goto try_line_prop;
  /* all elements of expr. class that are not variables or selects of vars */
  case vpiConstant: case vpiPartSelect: case vpiOperation:
   pval = exprclass_prop_vpiget(hp, property);
   break;
  case vpiIODecl:
   pval = iodecl_prop_vpiget(hp, property);
   break;
  case vpiUdpDefn:
   pval = udpdefnprop_vpiget(hp, property);
   break;
  case vpiTableEntry:
   pval = udptabentryprop_vpiget(hp, property);
   break;
  case vpiAttribute:
   pval = dig_attrprop_vpiget(hp, property);
   break;
  case vpiCallback:
   /* property for enable (active or on) call back is vpiActive, i.e. on */
   if (property != vpiActive)
    { notpropof_err(hrp->htyp, property); return(vpiUndefined); }
   if (hrp->hu.hcbp->cb_user_off) return(FALSE);
   return(TRUE); 
   
  default:
   notpropof_err(hrp->htyp, property);
   return(vpiUndefined);
  }
 return(pval);
} 

/*
 * validate property
 * returns F on error
 */
static int32 validate_property(char *rnam, int32 proptyp)
{
 if (__to_vpipnam(__wrks1, proptyp) == NULL || proptyp == vpiUndefined)
  {
   __vpi_err(1819, vpiError,
    "%s: property %d illegal or out of range", rnam, proptyp);
   return(FALSE);
  }
 return(TRUE);
}

/*
 * get int32 property values for module (inst. itree loc.)
 */
static int32 modprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct mod_t *mdp;
 struct itree_t *itp;
  
 mdp = hp->hrec->hu.hmdp;
 switch (prop) {
  case vpiCellInstance:
   if (mdp->m_iscell) return(TRUE);
   return(FALSE);
  /* delay modes not supported by Cver */
  case vpiDefDelayMode: return(vpiDelayModeNone);
  case vpiLineNo: 
     itp = (struct itree_t *) hp->hin_idp[MD_ITP];
     return(itp->itip->isym->sylin_cnt);
   break;
  case vpiDefLineNo: return(mdp->msym->sylin_cnt);
  case vpiProtected: return(FALSE);
  case vpiTimeUnit:
   if (!mdp->mno_unitcnv) pval = -((int32) mdp->mtime_units);
   /* if no time scale both precision and units the same */
   else pval = -((int32) __des_timeprec);
   return(pval);
  case vpiTimePrecision:
   if (!mdp->mno_unitcnv)
    pval = -((int32) (mdp->mtime_units + mdp->mtime_prec));
   else pval = -((int32) __des_timeprec);
   return(pval);
  case vpiDefNetType: return(__to_vpi_netproptyp(mdp->mod_dfltntyp));
  case vpiUnconnDrive:
   if (mdp->mod_uncdrv == TOK_NONE) return(vpiHighZ); 
   if (mdp->mod_uncdrv == PULL0) return(vpiPull0);
   if (mdp->mod_uncdrv == PULL1) return(vpiPull1);
   __vpi_terr(__FILE__, __LINE__);
   return(0);
  case vpiTopModule: 
   if (mdp->minstnum == 0) return(TRUE);
   return(FALSE);
  /* LOOKATME - what should this be? */
  case vpiDefDecayTime: return(0);
  default: notpropof_err(hp->hrec->htyp, prop); break;
 }
 return(vpiUndefined);
}

/*
 * emit not property of handle err
 *
 * know hp non nil or will not get here
 */
static void notpropof_err(word32 typh, int32 prop)
{
 __vpi_err(1867, vpiError,  
  "property %s not defined for vpi_get of %s",
  __to_vpipnam(__wrks1, prop), __to_vpionam(__wrks2, typh));
}

/*
 * get the vpi handle object type for a variable (net_t)
 */
extern word32 __ntyp_to_vpivarhtyp(struct net_t *np)
{
 word32 otyp;

 if (np->n_isaparam) otyp = vpiParameter;
 else if (np->ntyp < NONWIRE_ST) otyp = vpiNet;
 else if (np->n_isarr) otyp = vpiMemory;
 else otyp = to_vpi_reghtyp(np->ntyp);
 return(otyp);
}

/*
 * routine to convert from internal Cver net (but known to be reg)
 * type to vpi_ var object type
 *
 * SJM 08/11/97 - separated so old one type mapping from ntyp routine
 *                now 3 depending on vpi_ output needed
 */
static word32 to_vpi_reghtyp(word32 ntyp)
{
 switch (ntyp) {
  case N_BIT: return(vpiReg);
  case N_CINT: return(vpiIntegerVar);
  case N_REG: case N_LOGIC: return(vpiReg);
  case N_INT: return(vpiIntegerVar);
  case N_TIME: return(vpiTimeVar);
  case N_REAL: return(vpiRealVar);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(0);
}

/*
 * convert a Cver side net type to vpi_ var bit select type
 */
extern word32 __to_vpinetbithtyp(word32 ntyp)
{
 if (ntyp < NONWIRE_ST) return(vpiNetBit);
 switch (ntyp) {
  case N_REG: return(vpiRegBit);
  case N_INT: case N_TIME: case N_REAL: return(vpiVarSelect);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(0);
}

/*
 * routine to convert from internal Cver wire type to vpi property value
 * also converts internal net types to variable (reg,int32, ...) object types 
 */
extern int32 __to_vpi_netproptyp(word32 ntyp)
{
 switch (ntyp) {
  case N_WIRE: return(vpiWire);
  case N_WA: return(vpiWand);
  case N_WO: return(vpiWor);
  case N_TRI: return(vpiTri);
  case N_TRI0: return(vpiTri0);
  case N_TRI1: return(vpiTri1);
  case N_TRIREG: return(vpiTriReg);
  case N_TRIAND: return(vpiTriAnd);
  case N_TRIOR: return(vpiTriOr); 
  case N_SUPPLY0: return(vpiSupply0); 
  case N_SUPPLY1: return(vpiSupply1);
  case N_BIT: return(vpiReg);
  case N_CINT: return(vpiIntegerVar);
  case N_LOGIC: return(vpiReg);
  case N_REG: return(vpiReg);
  case N_INT: return(vpiIntegerVar);
  case N_TIME: return(vpiTimeVar);
  case N_REAL: return(vpiRealVar);
  case N_EVENT: return(vpiNamedEvent);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(vpiUndefined);
}

/*
 * routine to convert from vpi handle type known to be variable to
 * to internal ntyp
 * 
 * never called with bit of (vpiNetBit or vpiRegBit) 
 */
extern word32 __from_vpi_vartyp(word32 pval)
{
 switch ((byte) pval) {
  case vpiWire: return(N_WIRE);
  case vpiWand: return(N_WA);
  case vpiWor: return(N_WO);
  case vpiTri: return(N_TRI);
  case vpiTri0: return(N_TRI0);
  case vpiTri1: return(N_TRI1);
  case vpiTriReg: return(N_TRIREG);
  case vpiTriAnd: return(N_TRIAND);
  case vpiTriOr: return(N_TRIOR);
  case vpiSupply0: return(N_SUPPLY0);
  case vpiSupply1: return(N_SUPPLY1);
  case vpiReg: return(N_REG);
  case vpiIntegerVar: return(N_INT);
  case vpiTimeVar: return(N_TIME);
  case vpiRealVar: return(N_REAL);
  case vpiNamedEvent: return(N_EVENT);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(0);
}

/*
 * get int32 property values of net for net or net bit (ignore bit)
 */
static int32 netprop_vpiget(struct h_t *hp, int32 prop) 
{
 int32 biti;
 struct net_t *np;
 struct hrec_t *hrp;
 decl_idp_locals_;

 hrp = hp->hrec;
 if (hrp->htyp == vpiNetBit)
  {
   if (hrp->bith_ndx) np = hrp->hu.hnp;
   else np = hrp->hu.hxp->lu.x->lu.sy->el.enp;
  }
 else np = hrp->hu.hnp;

 switch (prop) {
  case vpiExpanded: return(TRUE);
  case vpiImplicitDecl:
   if (np->nsym->sy_impldecl) return(TRUE); 
   return(FALSE);
  case vpiLineNo: return(np->nsym->sylin_cnt);
  /* vpiNetDeclAssign undeclared in Cver */

  /* get net type property (i.e vpiWand) not net expr. part obj htyp */
  /* know net or net bit or will not get here */
  case vpiNetType: return(__to_vpi_netproptyp(np->ntyp));
  case vpiScalar:  
   if (np->n_isavec) return(FALSE);
   return(TRUE);
  /* always false in Cver since the default */ 
  case vpiExplicitScalared: return(FALSE);
  case vpiSigned:
   /* SJM 09/28/06 - for 2001/5 net type objects have signed prop */ 
   if (np->n_signed) return(TRUE);
   return(FALSE);
   break; 
  case vpiSize:
   if (hrp->htyp == vpiNetBit) return(1);
   return(np->nwid);
  /* no net strengths in Cver (or Verilog?) just charge */
  /* if no charge strength returns 0 */
  case vpiChargeStrength:
   if (np->n_capsiz == CAP_NONE) return(0);
   if (np->n_capsiz == CAP_SMALL) return(vpiSmallCharge);
   if (np->n_capsiz == CAP_MED) return(vpiMediumCharge);
   if (np->n_capsiz == CAP_LARGE) return(vpiLargeCharge);
   __vpi_terr(__FILE__, __LINE__);
   break;
  case vpiVector:
   if (np->n_isavec) return(TRUE);
   return(FALSE);
  case vpiConstantSelect:
   if (hrp->htyp != vpiNetBit) goto bad_prop;
   if (hrp->bith_ndx) return(TRUE);
   if (__expr_is_vpiconst(hrp->hu.hxp->ru.x)) 
    {
     set_save_idp_(hp->hin_idp);
     /* if constant already normalized to h:0, else this will normalize */
     /* variable index */
     biti = __comp_ndx(np, hrp->hu.hxp->ru.x);
     restore_idp_();
     if (biti == -1) return(FALSE);
     return(TRUE);
    }
   return(FALSE);

  default:
bad_prop:
    notpropof_err(hrp->htyp, prop); break;
 }
 return(vpiUndefined);
}


/*
 * get int32 property values for reg or reg bit (includes int32 and time)
 * all properties same
 */
static int32 regprop_vpiget(struct h_t *hp, int32 prop) 
{
 int32 biti, is_bit;
 struct net_t *np;
 struct hrec_t *hrp;
 decl_idp_locals_;
 
 hrp = hp->hrec; 
 is_bit = FALSE;
 if (hrp->htyp == vpiRegBit || hrp->htyp == vpiVarSelect)
  {
   if (hrp->bith_ndx) np = hrp->hu.hnp;
   else np = hrp->hu.hxp->lu.x->lu.sy->el.enp;
   is_bit = TRUE;
  }
 else np = hrp->hu.hnp;

 switch (prop) {
  case vpiLineNo: return(np->nsym->sylin_cnt);
  case vpiScalar:  
   if (np->n_isavec) return(FALSE);
   return(TRUE);
  case vpiSigned:
   /* SJM 09/28/06 - for 2001/5 net type objects have signed prop */ 
   if (np->n_signed) return(TRUE);
   return(FALSE);
  case vpiSize:
   if (is_bit) return(1);
   return(np->nwid);
  case vpiVector:
   if (np->n_isavec && !is_bit) return(TRUE);
   return(FALSE);
  case vpiConstantSelect:
   if (hrp->htyp != vpiRegBit && hrp->htyp != vpiVarSelect) goto bad_prop;
   if (hrp->bith_ndx) return(TRUE);
   if (__expr_is_vpiconst(hrp->hu.hxp->ru.x)) 
    {
     set_save_idp_(hp->hin_idp);
     /* if constant already normalized to h:0, else this will normalize */
     /* variable index */
     biti = __comp_ndx(np, hrp->hu.hxp->ru.x);
     restore_idp_();
     if (biti == -1) return(FALSE);
     return(TRUE);
    }
   return(FALSE);
  default:
bad_prop:
   notpropof_err(hrp->htyp, prop); break;
 }
 return(vpiUndefined);
}


/*
 * get int32 property values for array (know hp is array handle)
 */
static int32 arrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct net_t *np;

 np = hp->hrec->hu.hnp;
 switch (prop) {
  case vpiLineNo: return(np->nsym->sylin_cnt);
  case vpiSize: return(__get_arrwide(np));
  default: notpropof_err(hp->hrec->htyp, prop); break;
 }
 return(vpiUndefined);
}
/*
 * get int32 property values for word32 of array
 */
static int32 arrwrdprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 biti;
 struct net_t *np;
 struct hrec_t *hrp;
 decl_idp_locals_;

 hrp = hp->hrec;
 if (hrp->bith_ndx) np = hrp->hu.hnp;
 else np = hrp->hu.hxp->lu.x->lu.sy->el.enp;

 switch (prop) {
  case vpiLineNo: return(np->nsym->sylin_cnt);
  case vpiSize: return(np->nwid);
  case vpiConstantSelect:
   if (hrp->bith_ndx) return(TRUE);
   if (__expr_is_vpiconst(hrp->hu.hxp->ru.x)) 
    {
     set_save_idp_(hp->hin_idp);
     /* if constant already normalized to h:0, else this will normalize */
     /* variable index */
     biti = __comp_ndx(np, hrp->hu.hxp->ru.x);
     restore_idp_();
     if (biti == -1) return(FALSE);
     return(TRUE);
    }
   return(FALSE);

  default: notpropof_err(hrp->htyp, prop); break;
 }
 return(vpiUndefined);
}

/*
 * get int32 property values for param
 */
static int32 paramprop_vpiget(struct h_t *hp, int32 prop)
{
 struct net_t *np;

 np = hp->hrec->hu.hnp;
 switch (prop) {
  /* this will always be constant because evaluated to constant */
  /* may have been expr in source but by here always a number */
  case vpiConstType: return(get_param_constyp(np));
  case vpiLineNo: return(np->nsym->sylin_cnt);
  case vpiSize: return(np->nwid);
  case vpiLocalParam:
   if (np->nu.ct->p_locparam) return(TRUE);
   return(FALSE);
  case vpiSigned:
   /* SJM 09/28/06 - for 2001/5 net type objects have signed prop */ 
   if (hp->hrec->htyp == vpiParameter)
    {
     if (np->n_signed) return(TRUE);
     return(FALSE);
    }
  /* SJM 09/28/06 - fall thru if specparam since no has sign property */
  default:
   notpropof_err(hp->hrec->htyp, prop); break;
 }
 return(vpiUndefined);
}

/*
 * get param constant type property
 */
static int32 get_param_constyp(struct net_t *np)
{
 int32 ctyp;

 ctyp = 0;
 if (np->ntyp == N_REAL) return(vpiRealConst);
 if (np->nu.ct->pstring) return(vpiStringConst);

 switch (np->nu.ct->pbase) {
  case BBIN: ctyp = vpiBinaryConst; break;
  case BOCT: ctyp = vpiOctConst; break;
  case BDEC: ctyp = vpiDecConst; break;
  case BHEX: ctyp = vpiHexConst; break;
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(ctyp);
}

/*
 * get int32 property values for port and port bit
 */
static int32 portprop_vpiget(struct h_t *hp, int32 prop)
{
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 mpp = &(mdp->mpins[hrp->hu.hpi]);
 switch (prop) {
  case vpiConnByName: 
   if (mpp->mp_explicit) return(TRUE);
   return(FALSE);
  case vpiDirection:  
   if (mpp->mptyp == IO_IN) return(vpiInput);
   if (mpp->mptyp == IO_OUT) return(vpiOutput);
   if (mpp->mptyp == IO_BID) return(vpiInout);
   __vpi_terr(__FILE__, __LINE__);
   break;
  case vpiExplicitName:
   if (mpp->mpsnam == NULL) return(FALSE);
   return(TRUE);  
  case vpiPortIndex: return(hrp->hu.hpi);
  case vpiLineNo: return(mpp->mplin_cnt);
  case vpiScalar: return(mpp->mpwide == 1);
  case vpiSize:
   if (hrp->htyp == vpiPortBit) return(1);
   return(mpp->mpwide);
  case vpiVector:
   if (hrp->htyp == vpiPortBit) return(FALSE);
   return(mpp->mpwide != 1);
  default: notpropof_err(hrp->htyp, prop); break;
 }
 return(vpiUndefined);
}

/*
 * get int32 property values for primitives
 */
static int32 gateprop_vpiget(struct h_t *hp, int32 prop)
{
 word32 sval;
 struct gate_t *gp;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 gp = hrp->hu.hgp;
 switch (prop) {
  case vpiLineNo: return(gp->gsym->sylin_cnt);
  case vpiPrimType: return(__to_vpi_primtyp(gp));
  /* LRM defines this as number of inputs */
  case vpiSize:
   /* switch all terminasl are inputs (counting inouts) */
   if (hrp->htyp == vpiSwitch) return(gp->gpnum);
   /* for udp get from udp definition */
   if (hrp->htyp == vpiUdp) return(gp->gmsym->el.eudpp->numins);
   /* all other have one output (cmos is 3 inputs and one output */
   /* pullup/pulldown not seen here */
   return(gp->gpnum - 1);
  /* LOOKATME - what if no gate strength - no way to detect */
  case vpiStrength0:
   /* 0 is high 3 bits */
   sval = (gp->g_stval >> 3) & 0x7;
   return((int32) __map_tovpi_stren(sval));
  case vpiStrength1:
   /* 1 is low 3 bits */
   sval = gp->g_stval & 0x7;
   return((int32) __map_tovpi_stren(sval));
  default: notpropof_err(hrp->htyp, prop); break;
 }
 return(vpiUndefined);
}

/*
 * routine to convert from internal Cver gate type to vpi primitive class
 *
 * i.e. type of udp or particular type of gate (not vpi gate rather vpi Buf)
 */
extern int32 __to_vpi_primtyp(struct gate_t *gp)
{
 struct primtab_t *ptp;
 struct udp_t *udpp;

 if (gp->g_class == GC_UDP)
  {
   udpp = gp->gmsym->el.eudpp;
   if (udpp->utyp == U_COMB) return(vpiCombPrim);
   return(vpiSeqPrim);
  }
 ptp = gp->gmsym->el.eprimp; 
 switch ((byte) ptp->gateid) {
  case G_BITREDAND: return(vpiAndPrim);
  case G_NAND: return(vpiNandPrim);
  case G_NOR: return(vpiNorPrim);
  case G_BITREDOR: return(vpiOrPrim);
  case G_BITREDXOR: return(vpiXorPrim);
  case G_REDXNOR: return(vpiXnorPrim);
  case G_BUF: return(vpiBufPrim);
  case G_NOT: return(vpiNotPrim);
  case G_BUFIF0: return(vpiBufif0Prim);
  case G_BUFIF1: return(vpiBufif1Prim);
  case G_NOTIF0: return(vpiNotif0Prim);
  case G_NOTIF1: return(vpiNotif1Prim);
  case G_NMOS: return(vpiNmosPrim);
  case G_RNMOS: return(vpiRnmosPrim);
  case G_PMOS: return(vpiPmosPrim);
  case G_RPMOS: return(vpiRpmosPrim);
  case G_CMOS: return(vpiCmosPrim);
  case G_RCMOS: return(vpiRcmosPrim);
  case G_TRAN: return(vpiTranPrim);
  case G_RTRAN: return(vpiRtranPrim);
  case G_TRANIF0: return(vpiTranif0Prim);
  case G_RTRANIF0: return(vpiRtranif0Prim);
  case G_TRANIF1: return(vpiTranif1Prim);
  case G_RTRANIF1: return(vpiRtranif1Prim);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(vpiUndefined);
}

/*
 * get int32 property values for primitive (gate) terminals
 */
extern int32 __primtermprop_vpiget(struct h_t *hp, int32 prop)
{
 struct gate_t *gp;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 gp = hrp->hu.hgp;
 switch (prop) {
  case vpiDirection:
   /* tran switch first 2 terminals always bid - third for tranif input */
   if (gp->g_class == GC_TRAN || gp->g_class == GC_TRANIF)
    {
     if (hrp->hi == 2) return(vpiInput);
     return(vpiInout);
    }
   /* first (0th) terminal always output */
   if (hrp->hi == 0) return(vpiOutput);
   /* rest always input - not supporting >1 outpu buf/not gates */
   return(vpiInput);

  case vpiTermIndex: return(hrp->hi);
  case vpiLineNo: return(gp->gsym->sylin_cnt);
  default: notpropof_err(hrp->htyp, prop); break;
 }
 return(vpiUndefined);
}

/*
 * get property values for task call
 *
 * LOOKAT - interpreted LRM to allow vpUserDefn for user system tasks
 * <not clear from even new Verilog 98 LRM page>
 */
static int32 tcallprop_vpiget(struct h_t *hp, int32 prop)
{
 struct tskcall_t *tkcp;
 struct systsk_t *stbp;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 switch (prop) {
  case vpiLineNo: return(hrp->hu.hstp->stlin_cnt);
  case vpiUserDefn:
   /* non system task is always user defined */
   if (hrp->htyp == vpiTaskCall) return(TRUE);
   tkcp = &(hrp->hu.hstp->st.stkc);
   stbp = tkcp->tsksyx->lu.sy->el.esytbp;
   if (stbp->stsknum > BASE_VERIUSERTFS) return(TRUE); 
   return(FALSE);
  default: notpropof_err(hrp->htyp, prop);
 }
 return(vpiUndefined);
}

/*
 * get property values of function definition (task def. has only str props)
 *
 * this is only for user function definitions (vpiFunction) - use
 * vpi get systtf_info for system functions
 */
static int32 funcdefprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct net_t *np;
 struct task_t *tskp;

 tskp = hp->hrec->hu.htskp;
 pval = 0;
 switch (prop) { 
  case vpiLineNo:
   pval = tskp->tsksyp->sylin_cnt;
   break;
  case vpiFuncType: 
   /* first pin for func. is the return value */
   np = tskp->tskpins->tpsy->el.enp;
   if (np->ntyp == N_INT) { pval = vpiIntFunc; break; }
   if (np->ntyp == N_REAL) { pval = vpiRealFunc; break; }
   if (np->ntyp == N_TIME) { pval = vpiTimeFunc; break; }
   pval = vpiSizedFunc;
   break;
  case vpiSize:
   /* first pin for func. is the return value */
   np = tskp->tskpins->tpsy->el.enp;
   pval = np->nwid;
   break;
  case vpiSigned:
   /* SJM 09/28/06 - for 2001/5 net type objects have signed prop */ 
   np = tskp->tskpins->tpsy->el.enp;
   if (np->n_signed) pval = TRUE; else pval = FALSE;
   break;
  default: 
   notpropof_err(hp->hrec->htyp, prop);
   return(vpiUndefined);
 }
 return(pval);
}

/*
 * get property values (int32) for cont assign
 */
static int32 contaprop_vpiget(struct h_t *hp, int32 prop)
{
 word32 sval;
 struct conta_t *cap;
 struct gate_t *gp;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 if (hrp->htyp2 == vpiGate)
  {
   gp = hrp->hu.hgp;
   switch (prop) {
    case vpiLineNo: return(gp->gsym->sylin_cnt);
    case vpiNetDeclAssign:
     /* in Cver always assuming not part of net since not preserved */
     /* FIXME - should record */
     return(FALSE);
    case vpiStrength0:
     /* 0 is high 3 bits */
     sval = (gp->g_stval >> 3) & 0x7;
     return((int32) __map_tovpi_stren(sval));
    case vpiStrength1:
     /* 1 is low 3 bits */
     sval = gp->g_stval & 0x7;
     return((int32) __map_tovpi_stren(sval));
    default: notpropof_err(hrp->htyp, prop); break;
   }
   return(vpiUndefined);
  } 
 cap = hrp->hu.hcap;
 switch (prop) {
  case vpiLineNo: return(cap->casym->sylin_cnt);
  /* vpiNetDeclAssign undeclared in Cver */
  case vpiStrength0:
   /* 0 is high 3 bits */
   sval = (cap->ca_stval >> 3) & 0x7;
   return((int32) __map_tovpi_stren(sval));
  case vpiStrength1:
   /* 1 is low 3 bits */
   sval = cap->ca_stval & 0x7;
   return((int32) __map_tovpi_stren(sval));
  default: notpropof_err(hrp->htyp, prop); break;
 }
 return(vpiUndefined);
}

/*
 * get property values for function call (user or system)
 *
 * name for vpiSysFunc and vpiFunc subtype property changed to vpiFuncType and
 * now applies to both user and system functions: values now are
 * vpiIntFunc, vpiRealFunc, vpiTimeFunc, vpiSizedFunc
 *
 * contrary to new Veirlog 98 LRM system func calls do not have line location
 * so emitting warning and return 0
 */
static int32 fcallprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct sy_t *fsyp;
 struct sysfunc_t *sfbp;
 struct task_t *tskp;
 struct net_t *np;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 pval = 0;
 /* case 1: user function call */
 if (hrp->htyp == vpiFuncCall)
  {
   fsyp = hrp->hu.hxp->lu.x->lu.sy;
   switch (prop) {
    case vpiSize:
     /* FIXME - what should size of real be - for now making it 0 */
     if (hrp->hu.hxp->is_real) { pval = 0; break; }
     pval = hrp->hu.hxp->szu.xclen;
     break;
    case vpiLineNo:
     /* for compatibility making location 0 with inform */
     __vpi_err(2112, vpiNotice,
      "vpiLineNo property not saved for vpiFuncCall object - 0 returned");
     pval = 0;
     break; 
    case vpiFuncType:
     tskp = fsyp->el.etskp;
     /* DBG remove --- */
     if (tskp->tskpins == NULL || tskp->tskpins->tpsy == NULL)
      __vpi_terr(__FILE__, __LINE__);
     /* --- */
     np = tskp->tskpins->tpsy->el.enp;
     if (np->ntyp == N_INT) { pval = vpiIntFunc; break; }
     if (np->ntyp == N_REAL) { pval = vpiRealFunc; break; }
     if (np->ntyp == N_TIME) { pval = vpiTimeFunc; break; }
     pval = vpiSizedFunc;
     break;
    default:
no_prop:
     notpropof_err(hrp->htyp, prop);
     return(vpiUndefined);
   }
   return(pval);
  }
 /* DBG remove --- */
 if (hrp->htyp != vpiSysFuncCall) __vpi_terr(__FILE__, __LINE__);
 /* --- */ 

 /* case 2: sysfunc of some type call */
 fsyp = hrp->hu.hxp->lu.x->lu.sy;
 sfbp = fsyp->el.esyftbp;
 switch (prop) { 
  case vpiUserDefn:
   if (sfbp->syfnum > BASE_VERIUSERTFS) pval = TRUE;
   else pval = FALSE;
   break;
  case vpiSize:
   /* FIXME - what should size of real be - for now making it 0 */
   if (sfbp->retntyp == N_REAL) { pval = 0; break; }
   pval = hrp->hu.hxp->szu.xclen;
   break;

  /* as of Verilog 98, both normal and system functions have ret. type */
  case vpiFuncType: 
   if (sfbp->retntyp == N_INT) { pval = vpiIntFunc; break; }
   if (sfbp->retntyp == N_REAL) { pval = vpiRealFunc; break; }
   if (sfbp->retntyp == N_TIME) { pval = vpiTimeFunc; break; }
   pval = vpiSizedFunc;
   break;
  case vpiLineNo: 
   __vpi_err(2112, vpiNotice,
    "vpiLineNo property not saved for vpiSysFuncCall object - 0 returned");
   return(0);
  default: goto no_prop;
 }
 return(pval);
}

/*
 * get property values for tchk
 */
static int32 tchkprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct tchk_t *tcp;

 tcp = hp->hrec->hu.htcp; 
 switch (prop) {
  case vpiLineNo: pval = tcp->tcsym->sylin_cnt; break;
  case vpiTchkType:
   pval = to_vpi_tchktyp(tcp->tchktyp);
   break;
  default: notpropof_err(hp->hrec->htyp, prop); pval = vpiUndefined; 
 }
 return(pval);
}

/*
 * routine to convert from internal Cver tchk type to vpi_ constant
 *
 * notice hold of setup hold separate tchk but will never see
 */
static int32 to_vpi_tchktyp(word32 tctyp)
{
 switch ((byte) tctyp) {
  case TCHK_SETUP: return(vpiSetup);
  case TCHK_HOLD: return(vpiHold);  
  case TCHK_WIDTH: return(vpiWidth);
  case TCHK_PERIOD: return(vpiPeriod);
  case TCHK_SKEW: return(vpiSkew);
  case TCHK_RECOVERY: return(vpiRecovery);
  case TCHK_NOCHANGE: return(vpiNoChange);
  case TCHK_SETUPHOLD: return(vpiSetupHold);
  /* SJM 12/15/03 - new 2001 timing checks - recognized but not supported */
  case TCHK_FULLSKEW: return(vpiFullskew);
  case TCHK_RECREM: return(vpiRecrem);
  case TCHK_REMOVAL: return(vpiRemoval);
  case TCHK_TIMESKEW: return(vpiTimeskew);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(vpiUndefined);
}

/*
 * get property values for function call
 * LOOKATME - think reversed 1st and 2nd term for setup already moved?
 */
static int32 tchktermprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct tchk_t *tcp;

 tcp = hp->hrec->hu.htcp;
 switch (prop) {
  case vpiLineNo: pval = tcp->tcsym->sylin_cnt; break;
  case vpiEdge:
   if (hp->hrec->htyp2 == vpiTchkRefTerm)
    pval = to_vpi_edgeval(tcp->startedge);
   else if (hp->hrec->htyp2 == vpiTchkDataTerm)
    pval = to_vpi_edgeval(tcp->chkedge);
   else { __vpi_terr(__FILE__, __LINE__); return(vpiUndefined); }
   break;
  default: notpropof_err(hp->hrec->htyp, prop); pval = vpiUndefined;
 }
 return(pval);
}

/*
 * routine to convert from internal Cver edge to Vpi edge
 * they are identical execept no any edge in Cver (same filtering algorithm)
 * 
 * LOOKATME: could just remove this identity mapping since same
 */
static int32 to_vpi_edgeval(word32 edg)
{
 switch ((byte) edg) {
  case NOEDGE: return(vpiNoEdge);
  case EDGE01: return(vpiEdge01);
  case EDGE10: return(vpiEdge10);
  case EDGE0X: return(vpiEdge0x);
  case EDGEX1: return(vpiEdgex1);
  case EDGE1X: return(vpiEdge1x);
  case EDGEX0: return(vpiEdgex0);
  case E_POSEDGE: return(vpiPosedge);
  case E_NEGEDGE: return(vpiNegedge);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(vpiUndefined);
}

/*
 * get property values for function call
 */
static int32 pthprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct spcpth_t *pthp;

 pthp = hp->hrec->hu.hpthp;
 switch (prop) {
  case vpiLineNo: pval = pthp->pthsym->sylin_cnt; break;
  case vpiPathType:
   if (pthp->pthtyp == PTH_PAR) pval = vpiPathParallel;
   else if (pthp->pthtyp == PTH_FULL) pval = vpiPathFull;
   else { __vpi_terr(__FILE__, __LINE__); pval = vpiUndefined; }
   break;
  case vpiPolarity:
   if (pthp->pthpolar == POLAR_PLUS) pval = vpiPositive;
   else if (pthp->pthpolar == POLAR_MINUS) pval = vpiNegative;
   else if (pthp->pthpolar == POLAR_NONE) pval = vpiUnknown;
   else { __vpi_terr(__FILE__, __LINE__); pval = vpiUndefined; }
   break;
  case vpiDataPolarity:
   if (pthp->dsrc_polar == POLAR_PLUS) pval = vpiPositive;
   else if (pthp->dsrc_polar == POLAR_MINUS) pval = vpiNegative;
   else if (pthp->dsrc_polar == POLAR_NONE) pval = vpiUnknown;
   else { __vpi_terr(__FILE__, __LINE__); pval = vpiUndefined; }
   break;
  case vpiModPathHasIfNone: 
   if (pthp->pth_ifnone) pval = TRUE; else pval = FALSE;
   break; 
  default: notpropof_err(hp->hrec->htyp, prop); pval = vpiUndefined;
 }
 return(pval);
}

/*
 * get property values for function call
 * handle is hu pthp, hi - index, htyp2 is list from 
 */
static int32 pthtermprop_vpiget(struct h_t *hp, int32 prop)
{
 struct spcpth_t *pthp; 
 int32 pval;

 pthp = hp->hrec->hu.hpthp;
 switch (prop) {
  case vpiLineNo: pval = pthp->pthsym->sylin_cnt; break;
  case vpiDirection: pval = (int32) hp->hrec->htyp2; break;
  case vpiEdge:
   /* only path in has edge */
   if (hp->hrec->htyp2 != vpiModPathIn) goto no_prop;
   pval = to_vpi_edgeval(pthp->pthedge);
   break;
  default:
no_prop:
   notpropof_err(hp->hrec->htyp, prop);
   pval = vpiUndefined;
 }
 return(pval);
}

/*
 * get an expr property (know hp is vpiExpr to get here)
 *
 * uses changed semantics because of added vpiExpr object
 */
static int32 exprclass_prop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct expr_t *xp;

 xp = hp->hrec->hu.hxp;
 pval = vpiUndefined;
 switch (hp->hrec->htyp) {
  case vpiOperation:
   if (prop == vpiOpType) pval = __expr_optype_get(xp);
   else if (prop == vpiSize) pval = xp->szu.xclen;
   else goto not_prop;
   break;
  case vpiConstant:
   if (prop == vpiConstType)
    {
     return(get_vpi_const_typ(xp));
    }
   else if (prop == vpiSize) pval = xp->szu.xclen;
   else goto not_prop;
   break;  
  /* misc. with no special properties */
  case vpiFuncCall: case vpiSysFuncCall:
   if (prop == vpiSize) pval = xp->szu.xclen;
   else goto not_prop;
   break;
  case vpiPartSelect:
   if (prop == vpiSize) pval = xp->szu.xclen;
   else if (prop == vpiConstantSelect) pval = TRUE;
   else goto not_prop;
   break;
  default: goto not_prop;
 }
 return(pval);

not_prop:
 notpropof_err(hp->hrec->htyp, prop);
 return(vpiUndefined);
}

/*
 * get constant type property from expression
 */
static int32 get_vpi_const_typ(struct expr_t *xp)
{
 if (xp->is_real) return(vpiRealConst); 
 if (xp->is_string) return(vpiStringConst);
 if (xp->ibase == BBIN) return(vpiBinaryConst);  
 if (xp->ibase == BOCT) return(vpiOctConst);  
 if (xp->ibase == BDEC) return(vpiDecConst);  
 if (xp->ibase == BHEX) return(vpiHexConst);  
 __vpi_terr(__FILE__, __LINE__);
 return(vpiUndefined);
}

/*
 * given an internal (ndp) expr node, return vpi_ expression htyp
 *
 * this gets type, no itree information needed
 */
extern int32 __exprtype_get(struct expr_t *ndp)
{
 struct net_t *np;
 struct sy_t *syp;

 /* in this case, must put value on tos */
 switch (ndp->optyp) {
  case NUMBER: case REALNUM: case ISNUMBER: case ISREALNUM:
   return(vpiConstant);
  case GLBREF: case ID:
   np = ndp->lu.sy->el.enp; 
   return(__ntyp_to_vpivarhtyp(np));
  case LSB:
   /* this must just return select from a variable (net/reg/var) */
   return(vpiVarSelect);
  case PARTSEL_NDX_PLUS: 
   return(vpiPosIndexed);
  case PARTSEL_NDX_MINUS:
   return(vpiNegIndexed);
  case PARTSEL: 
   return(vpiPartSelect);
  case FCALL:
   syp = ndp->lu.x->lu.sy;
   if (syp->sytyp == SYM_SF) return(vpiSysFuncCall);
   return(vpiFuncCall);
 }
 /* LOOKATME - currently no way to check - only other possibility is op */
 return(vpiOperation);
}

/*
 * for a binary or unary or ?: expression return the top node operator type
 */
extern int32 __expr_optype_get(struct expr_t *xp)
{
 switch (xp->optyp) { 
  /* unary ops */
  case BITNOT: return(vpiBitNegOp);
  case REALNOT: case NOT: return(vpiNotOp);
  /* both binary and unary in Cver */
  case REALMINUS: case MINUS:
   if (xp->ru.x == NULL) return(vpiMinusOp); 
   return(vpiSubOp);
  case PLUS: case REALPLUS:
   if (xp->ru.x == NULL) return(vpiPlusOp);
   return(vpiAddOp);
  /* LOOKATME - vpiUnaryNorOp does not exist in Cver - decomposed */
  case BITREDOR:
   if (xp->ru.x == NULL) return(vpiUnaryOrOp);
   return(vpiBitOrOp);
  case BITREDXOR:
   if (xp->ru.x == NULL) return(vpiUnaryXorOp);
   return(vpiBitXorOp);
  case REDXNOR:
   if (xp->ru.x == NULL) return(vpiUnaryXNorOp);
   return(vpiBitXNorOp);
  /* vpiUnaryNandOp does not exist in Cver - decomposed */
  case BITREDAND:
   if (xp->ru.x == NULL) return(vpiUnaryAndOp);
   return(vpiBitAndOp);

  /* binary only ops */
  case TIMES: case REALTIMES: return(vpiMultOp);
  case DIV: case REALDIV: return(vpiDivOp);
  case MOD: return(vpiModOp);
  case REALRELGT: case RELGT: case STRRELGT: return(vpiGtOp);
  case RELGE: case REALRELGE: case STRRELGE: return(vpiGeOp);
  case RELLT: case REALRELLT: case STRRELLT: return(vpiLtOp);
  case RELLE: case REALRELLE: case STRRELLE: return(vpiLeOp);
  case RELCEQ: return(vpiCaseEqOp);
  case RELCNEQ: return(vpiCaseNeqOp);
  case RELEQ: case REALRELEQ: case STRRELEQ: return(vpiEqOp);
  case RELNEQ: case REALRELNEQ: case STRRELNEQ: return(vpiNeqOp);
  case BOOLAND: case REALBOOLAND: return(vpiLogAndOp);
  case BOOLOR: case REALBOOLOR: return(vpiLogOrOp);
  case SHIFTL: return(vpiLShiftOp);
  case ASHIFTL: return(vpiArithLShiftOp);
  case SHIFTR: return(vpiRShiftOp);
  case ASHIFTR: return(vpiArithRShiftOp);
  case QUEST: case REALREALQUEST: case REALREGQUEST: case REGREALQUEST:
    return(vpiConditionOp);
  /* SJM 06/01/04 - ### ??? LOOKATME - vpi_ can't distinguish 2 ev or types */
  case OPEVOR: case OPEVCOMMAOR: return(vpiEventOrOp);
  case OPPOSEDGE: return(vpiPosedgeOp);
  case OPNEGEDGE: return(vpiNegedgeOp);
  case LCB: return(vpiConcatOp);
  case CATREP: return(vpiMultiConcatOp);
  case OPEMPTY: return(vpiNullOp);
  default: __vpi_terr(__FILE__, __LINE__);
 }  
 return(vpiUndefined);
}

/*
 * get properties of an iodecl object
 *
 * udp io decl indicated by htyp2 type of vpiUdpDefn
 * if any bits of net are in port, entire net is a port (hu hnp field set)
 */
static int32 iodecl_prop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct net_t *np;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 if (hrp->htyp2 == vpiUdpDefn) return(udpiodecl_get(hp, prop));
 pval = vpiUndefined;
 np = hrp->hu.hnp;
 switch (prop) {
  case vpiDirection:
   if (np->ntyp == IO_IN) pval = vpiInput;
   else if (np->ntyp == IO_OUT) pval = vpiOutput;
   else if (np->ntyp == IO_BID) pval = vpiInout;
   else __vpi_terr(__FILE__, __LINE__);
   break;
  case vpiLineNo:
   pval = np->nsym->sylin_cnt;
   break;
  case vpiSize:
   pval = np->nwid;
   break;
  case vpiScalar:
   if (!np->n_isavec) pval = TRUE; else pval = FALSE;
   break;
  case vpiSigned:
   /* SJM 09/28/06 - for 2001/5 net type objects have signed prop */ 
   if (np->n_signed) pval = TRUE; else pval = FALSE;
   break;
  case vpiVector:
   if (np->n_isavec) pval = TRUE; else pval = FALSE;
   break;
  default: notpropof_err(hrp->htyp, prop);
 }
 return(pval);
}

/*
 * get properties for a udp io decl object (mod pin - not nets)
 */
static int32 udpiodecl_get(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;

 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 mpp = &(mdp->mpins[hp->hrec->hu.hpi]);
 pval = vpiUndefined;
 switch (prop) {
  case vpiDirection:
   if (mpp->mptyp == IO_IN) pval = vpiInput;
   else if (mpp->mptyp == IO_OUT) pval = vpiOutput;
   else __vpi_terr(__FILE__, __LINE__);
   break;
  case vpiLineNo:
   pval = mpp->mplin_cnt;
   break;
  case vpiSize:
   pval = 1;
   break;
  case vpiScalar:
   pval = TRUE;
   break;
  case vpiVector:
   pval = FALSE;
   break;
  default: notpropof_err(hp->hrec->htyp, prop);
 }
 return(pval);
}

/*
 * get a upd definition property
 */
static int32 udpdefnprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct udp_t *udpp;

 pval = vpiUndefined;
 udpp = hp->hrec->hu.hudpp;
 switch (prop) {
  case vpiLineNo:
   pval = udpp->usym->sylin_cnt;
   break;
  case vpiSize:
   /* LOOKATME - for now using number of inputs not states */
   pval = udpp->numins;
   break;
  case vpiProtected:
   /* no protection in Cver */
   pval = FALSE;
   break;
  case vpiPrimType:
   /* SJM 03/01/04 - properties were reversed here */
   if (udpp->utyp == U_COMB) pval = vpiCombPrim;
   else if (udpp->utyp == U_LEVEL || udpp->utyp == U_EDGE)
    pval = vpiSeqPrim;
   else __vpi_terr(__FILE__, __LINE__);
   break;
  default: notpropof_err(hp->hrec->htyp, prop);
 }
 return(pval);
}

/*
 * get a upd definition property
 */
static int32 udptabentryprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct udp_t *udpp;
 struct utline_t *utlp;

 pval = vpiUndefined;
 udpp = (struct udp_t *) hp->hin_idp;
 utlp = hp->hrec->hu.hutlp;

 switch (prop) {
  case vpiLineNo:
   pval = (int32) utlp->utlin_cnt;
   break;
  case vpiSize:
   /* value is number of states plus one for out */
   pval = udpp->numstates + 1;
   break;
  default: notpropof_err(hp->hrec->htyp, prop);
 }
 return(pval);
}

/*
 * get property of attribute
 */
static int32 dig_attrprop_vpiget(struct h_t *hp, int32 prop)
{
 int32 pval;
 double d1;
 struct attr_t *attrp;
 struct xstk_t *xsp;

 pval = vpiUndefined;
 switch (prop) {
  case vpiDefAttribute:
   /* T if no value or non zero value */
   attrp = __find_attrspec(hp);
   if (attrp->attr_xp == NULL) { pval = 1; break; }
   /* LOOKATME - since know number could access as constant */
   xsp = __eval_xpr(attrp->attr_xp);
   if (attrp->attr_xp->is_real)
    {
     memcpy(&d1, xsp->ap, sizeof(double));
     if (d1 != 0.0) pval = 1; else pval = 0;
     __pop_xstk();
     break;
    }
   if (vval_is0_(xsp->ap, xsp->xslen) && vval_is0_(xsp->bp, xsp->xslen))
    pval = 0; 
   else pval = 1;
   __pop_xstk();
   break;
  case vpiConstType:
   attrp = __find_attrspec(hp);
   if (attrp->attr_xp == NULL) { pval = vpiUndefined; break; }
   pval = get_vpi_const_typ(attrp->attr_xp);
   break;
  default: notpropof_err(hp->hrec->htyp, prop);
 }
 return(pval);
}

/*
 * find attribute by getting parent object then moving through list
 * passed attribute object returns matching attribute struct
 *
 * BEWARE - this must be inverse of iterator since goes form iterator
 * element to parent
 */
extern struct attr_t *__find_attrspec(struct h_t *hp)
{
 int32 ai;
 struct attr_t *attrp;
 struct inst_t *ip;
 struct mod_t *mdp;
 struct gate_t *gp;
 struct hrec_t *hrp;
 struct itree_t *itp;

 attrp = NULL;
 hrp = hp->hrec;
 switch (hrp->htyp2) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
  case vpiNamedEvent: case vpiRealVar:
  /* LOOKATME - is this defined in LRM - think so */
  case vpiMemory:
   attrp = hrp->hu.hnp->nattrs;
   break;
  case vpiModule:
   /* FIXME - need to add and access bit determing where attr is ??? */
   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   ip = itp->itip; 
   /* if dig attr attached to inst use it */  
   if (ip->iattrs != NULL) { attrp = ip->iattrs; break; }
   /* else use any attached to module */
   mdp = ip->imsym->el.emdp;
   attrp = mdp->mattrs;
   break;
  case vpiGate: case vpiSwitch: case vpiUdp:
   gp = hrp->hu.hgp;
   attrp = gp->gattrs;
   break;
  default: __vpi_terr(__FILE__, __LINE__);
 }
 ai = hrp->hi;
 for (ai = 0; ai < hrp->hi; ai++)
  {
   if (attrp == NULL) __vpi_terr(__FILE__, __LINE__);
   attrp = attrp->attrnxt;
  }
 if (attrp == NULL) __vpi_terr(__FILE__, __LINE__);
 return(attrp);
}


/*
 * ROUTINES TO GET STRING PROPERTIES
 */

/*
 * get a string property
 */
extern char *vpi_get_str(PLI_INT32 property, vpiHandle object)
{
 PLI_INT32 pval;
 struct h_t *hp;
 struct gate_t *gp;
 struct sy_t *syp;
 struct st_t *stp;
 struct hrec_t *hrp;

 __last_eip = NULL;
 if (__run_state == SS_COMP)
  { __still_comp_err("vpi_get_str"); return(NULL); } 
 if (!validate_property("vpi_get_str", property)) return(NULL);

 if (object == NULL)
  {
   __vpi_err(1865, vpiError,  
    "property %s illegal for vpi_get_str with NULL object",
    __to_vpipnam(__wrks1, property));
   return(NULL);
  }

 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_get_str", hp)) return(NULL);
 hrp = hp->hrec;

 /* LOOKATME - special meta string property - standard needs meta name */
 if (property == vpiType) 
  {  
   /* every handle has a type */
   __to_vpionam(__wrk_vpiget_str, hrp->htyp);
   return(__wrk_vpiget_str);
  }

 switch (hrp->htyp) {
  case vpiModule:   
   return(modstrprop_vpiget(hp, property));
  /* all net string properties the same */
  case vpiNet: case vpiNetBit: case vpiReg: case vpiRegBit: case vpiVarSelect:
  case vpiIntegerVar: case vpiTimeVar: case vpiNamedEvent:
  case vpiRealVar: case vpiParameter: case vpiSpecParam:
  case vpiMemory: case vpiMemoryWord:
   return(netstrprop_vpiget(hp, property));
  case vpiPort: case vpiPortBit:
   return(portstrprop_vpiget(hp, property));
  case vpiGate: case vpiUdp: case vpiSwitch:
   return(gatestrprop_vpiget(hp, property));
  case vpiPrimTerm:  
   if (property != vpiFile)
    { __notstrpropof_err(hrp->htyp, property); return(NULL); }
   gp = hrp->hu.hgp;
   strcpy(__wrk_vpiget_str, __in_fils[gp->gsym->syfnam_ind]);
   return(__wrk_vpiget_str);
  case vpiFuncCall: case vpiSysFuncCall:
   return(fcallstrprop_vpiget(hp, property));
  case vpiTaskCall: case vpiSysTaskCall:
   return(tcallstrprop_vpiget(hp, property));
  /* handles whose only str property is file location */ 
  case vpiTchk: case vpiTchkTerm:
   syp = hrp->hu.htcp->tcsym;
ret_fnam:
   if (property != vpiFile)
    { __notstrpropof_err(hrp->htyp, property); return(NULL); }
   strcpy(__wrk_vpiget_str, __in_fils[syp->syfnam_ind]);
   return(__wrk_vpiget_str);
  case vpiModPath: case vpiPathTerm:
   syp = hrp->hu.hpthp->pthsym;
   goto ret_fnam;
  /* scope def. handles */
  case vpiContAssign:
   if (hrp->htyp2 == vpiGate) syp = hrp->hu.hgp->gsym;
   else syp = hrp->hu.hcap->casym;
   goto ret_fnam;
  case vpiNamedBegin: case vpiNamedFork: case vpiTask: case vpiFunction:
   return(taskstrprop_vpiget(hp, property));
  case vpiAssignStmt: case vpiAssignment: case vpiBegin:
  case vpiCase: case vpiDeassign: case vpiDelayControl: case vpiEventControl:
  case vpiDisable: case vpiEventStmt: case vpiFor: case vpiForce:
  case vpiForever: case vpiFork: case vpiIf: case vpiIfElse: case vpiNullStmt:
  case vpiRelease: case vpiRepeat: case vpiWait: case vpiWhile:
   if (property != vpiFile)
    { __notstrpropof_err(hrp->htyp, property); return(NULL); }
   stp = hrp->hu.hstp;
   strcpy(__wrk_vpiget_str, __in_fils[stp->stfnam_ind]);
   return(__wrk_vpiget_str);
  case vpiOperation:
   /* Cver extension can get the name of operator (i.e. its symbol) */
   if (property != vpiName)
    { __notstrpropof_err(hrp->htyp, property); return(NULL); }
   pval = __expr_optype_get(hrp->hu.hxp);
   __to_vpiopchar(__wrk_vpiget_str, pval);
   return(__wrk_vpiget_str);
  case vpiDefParam:
   if (property != vpiFile)
    { __notstrpropof_err(hrp->htyp, property); return(NULL); }
   strcpy(__wrk_vpiget_str, __in_fils[hrp->hu.hdfp->dfpfnam_ind]);
   return(__wrk_vpiget_str);
  case vpiParamAssign:
   if (property != vpiFile)
    { __notstrpropof_err(hrp->htyp, property); return(NULL); }

   strcpy(__wrk_vpiget_str, __in_fils[hrp->hu.hnp->nsym->syfnam_ind]);
   return(__wrk_vpiget_str);
  case vpiAttribute:
   return(dig_attrstrpop_vpiget(hp, property));

  case vpiIODecl: return(iodeclstrprop_vpiget(hp, property));
  case vpiUdpDefn:
   if (property == vpiFile) 
    {
     strcpy(__wrk_vpiget_str, __in_fils[hrp->hu.hudpp->usym->syfnam_ind]);
    }
   else if (property == vpiDefName) 
    {
     strcpy(__wrk_vpiget_str, hrp->hu.hudpp->usym->synam);
    }
   else { __notstrpropof_err(hrp->htyp, property); return(NULL); }
   return(__wrk_vpiget_str);
  case vpiTableEntry:
   if (property != vpiFile)
    { __notstrpropof_err(hrp->htyp, property); return(NULL); }
   strcpy(__wrk_vpiget_str, __in_fils[hrp->hu.hutlp->utlfnam_ind]);
   return(__wrk_vpiget_str);
  default: __notstrpropof_err(hrp->htyp, property);
 }
 return(NULL);
}

/*
 * get string property values for module (inst. itree loc.)
 * copy to the one work string for these
 */
static char *modstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct mod_t *mdp;
 struct inst_t *ip;
 struct itree_t *itp;
  
 mdp = hp->hrec->hu.hmdp;
 switch (prop) {
  case vpiName: 
    itp = (struct itree_t *) hp->hin_idp[MD_ITP];
    ip = itp->itip;
    strcpy(__wrk_vpiget_str, ip->isym->synam); 
   break;
  case vpiFullName:
   strcpy(__wrk_vpiget_str, __msg2_idp_blditree(__wrks1, hp->hin_idp));
   break;
  case vpiFile:
   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   ip = itp->itip;
   strcpy(__wrk_vpiget_str, __in_fils[ip->isym->syfnam_ind]);
   break;
  case vpiDefName:
   strcpy(__wrk_vpiget_str, mdp->msym->synam);
   break;
  case vpiDefFile:
   strcpy(__wrk_vpiget_str, __in_fils[mdp->msym->syfnam_ind]);
   break;
  default: __notstrpropof_err(hp->hrec->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}

/*
 * emit not property of handle err
 *
 * know hp non nil or will not get here
 */
extern void __notstrpropof_err(word32 typh, int32 prop)
{
 __vpi_err(1875, vpiError, 
  "string property %s not defined for vpi_get_str of %s",
  __to_vpipnam(__wrks1, prop), __to_vpionam(__wrks2, typh));
 strcpy(__wrk_vpiget_str, "");  
}

/*
 * get string property values for net or array (and bits of)
 * copy to the one overwritten work string 
 *
 * notice although strictly speaking a array is not a net str props the same
 */
static char *netstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct net_t *np;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 if (hrp->htyp == vpiNetBit || hrp->htyp == vpiRegBit
  || hrp->htyp == vpiVarSelect || hrp->htyp == vpiMemoryWord
 )
  {
   if (hrp->bith_ndx) np = hrp->hu.hnp;
   else np = hrp->hu.hxp->lu.x->lu.sy->el.enp;
  }
 else np = hrp->hu.hnp;

 switch (prop) {
  case vpiFile:
   strcpy(__wrk_vpiget_str, __in_fils[np->nsym->syfnam_ind]);
   break;
  case vpiName: strcpy(__wrk_vpiget_str, np->nsym->synam); break;
  case vpiFullName:  
   if (hrp->hin_tskp == NULL)
    {
     sprintf(__wrk_vpiget_str, "%s.%s", 
      __msg2_idp_blditree(__wrks1, hp->hin_idp), np->nsym->synam);
    }
   else sprintf(__wrk_vpiget_str, "%s.%s",
    __msg_idp_blditree(__wrks1, hp->hin_idp, hrp->hin_tskp), np->nsym->synam);
   break;
  default: __notstrpropof_err(hrp->htyp, prop); return(NULL);
 } 
 return(__wrk_vpiget_str);
}

/*
 * get string property values for gates
 * copy to the one overwritten work string 
 *
 * LRM 98 removes vpiFullName property for ports
 */
static char *portstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct mod_t *mdp;
 struct mod_pin_t *mpp;

 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 mpp = &(mdp->mpins[hp->hrec->hu.hpi]);
 switch (prop) {
  case vpiFile:
   strcpy(__wrk_vpiget_str, __in_fils[mpp->mpfnam_ind]);
   break;
  case vpiName:
   if (mpp->mpsnam == NULL) return(NULL);
   return(mpp->mpsnam);
  default: __notstrpropof_err(hp->hrec->htyp, prop); return(NULL);
 } 
 return(__wrk_vpiget_str);
}

/*
 * get string property values for gates
 * copy to the one overwritten work string 
 */
static char *gatestrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct gate_t *gp;

 gp = hp->hrec->hu.hgp;
 switch (prop) {
  case vpiDefName:
   strcpy(__wrk_vpiget_str, gp->gmsym->synam);
   break;
  case vpiFile:
   strcpy(__wrk_vpiget_str, __in_fils[gp->gsym->syfnam_ind]);
   break;
  case vpiName: strcpy(__wrk_vpiget_str, gp->gsym->synam); break;
  case vpiFullName:  
    sprintf(__wrk_vpiget_str, "%s.%s", __msg2_idp_blditree(__wrks1,
     hp->hin_idp), gp->gsym->synam);
   break;
  default: __notstrpropof_err(hp->hrec->htyp, prop); return(NULL);
 } 
 return(__wrk_vpiget_str);
}

/*
 * get string property values for task call
 * copy to the one overwritten work string 
 */
static char *tcallstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct st_t *stp;

 stp = hp->hrec->hu.hstp;
 switch (prop) { 
  case vpiFile:
   strcpy(__wrk_vpiget_str, __in_fils[stp->stfnam_ind]);
   break;  
  case vpiName: 
   strcpy(__wrk_vpiget_str, stp->st.stkc.tsksyx->lu.sy->synam); 
   break;  
  default: __notstrpropof_err(hp->hrec->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}

/*
 * get string property values for function call
 * copy to the one overwritten work string 
 *
 * LOOKATME - for compatibility making location: unkown 0?
 */
static char *fcallstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct hrec_t *hrp;

 hrp = hp->hrec;
 switch (prop) { 
  case vpiFile:
   __vpi_err(2112, vpiNotice,
    "vpiFile call location property not saved for vpiFuncCall or vpiSysFuncCall - [unknown] returned");
   strcpy(__wrk_vpiget_str, "[Unknown]");
   break;
  case vpiName: 
   strcpy(__wrk_vpiget_str, hrp->hu.hxp->lu.x->lu.sy->synam); 
   break;
  default: __notstrpropof_err(hrp->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}

/*
 * get string property values for func/task declaration (scope not call)
 *
 * copy to the one overwritten work string 
 * also named begin or fork
 */
static char *taskstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct task_t *tskp;

 tskp = hp->hrec->hu.htskp;
 switch (prop) { 
  case vpiName: 
   strcpy(__wrk_vpiget_str, tskp->tsksyp->synam); 
   break;  
  case vpiFullName:  
   sprintf(__wrk_vpiget_str, "%s.%s", 
    __msg2_idp_blditree(__wrks1, hp->hin_idp), tskp->tsksyp->synam); 
   break;  
  case vpiFile:
   strcpy(__wrk_vpiget_str, __in_fils[tskp->tsksyp->syfnam_ind]);
   break;
  default: __notstrpropof_err(hp->hrec->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}

/*
 * get string property values for io decl
 * copy to the one overwritten work string 
 */
static char *iodeclstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct hrec_t *hrp;

 hrp = hp->hrec;
 switch (prop) { 
  case vpiName: 
   if (hrp->htyp2 == vpiUdpDefn)
    {
     /* DBG remove -- */
     if (hrp->hu.hmpp->mpsnam == NULL) __arg_terr(__FILE__, __LINE__);
     /* --- */
     strcpy(__wrk_vpiget_str, hrp->hu.hmpp->mpsnam); 
    }
   else strcpy(__wrk_vpiget_str, hrp->hu.hnp->nsym->synam);
   break;
  case vpiFile:
   if (hrp->htyp2 == vpiUdpDefn)
    strcpy(__wrk_vpiget_str, __in_fils[hrp->hu.hmpp->mpfnam_ind]);
   else strcpy(__wrk_vpiget_str, __in_fils[hrp->hu.hnp->nsym->syfnam_ind]);
   break;
  default: __notstrpropof_err(hrp->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}

/*
 * get string property values for digital attribute
 * copy to the one overwritten work string 
 */
static char *dig_attrstrpop_vpiget(struct h_t *hp, int32 prop)
{
 struct attr_t *attrp;

 switch (prop) {
  case vpiName:
   /* this can't fail */
   attrp = __find_attrspec(hp);
   strcpy(__wrk_vpiget_str, attrp->attrnam);
   break;
  default: __notstrpropof_err(hp->hrec->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}
