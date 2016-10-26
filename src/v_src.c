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
 * source reading of module items except for specify and udps
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

/* local prototypes */
static void decl_undecl_cell_and_conta_conns(struct mod_t *);
static void dcl_1undecl_wires(struct sy_t *, struct expr_t *);
static void travfreeze_lowsymtab(struct symtab_t *);
static void bld_mdpin_table(struct mod_t *);
static int32 rd_modhdr(struct mod_t *);
static int32 rd_hdrpnd_parmdecls(void);
static int32 rd_portref(void);
static void set_ioprtnets(struct expr_t *);
static int32 rd_list_of_ports_decl(struct mod_t *);
static int32 rd_modbody(void);
static int32 rd_init_always(int32);
static int32 rd_sv_always(int32);
static int32 rd_contassign(void);
static int32 rd_genvar_decl(void);
static int32 rd_gen_region_mod_items(void); 
static struct genblk_t *rd1_gen_block(void);
static int32 rd1_gen_mod_item(struct genblk_t *);
static int32 rd_gen_for(struct genblk_t *);
static int32 rd_gen_foreach(struct genblk_t *);
static struct genblk_t *rd1_nd_blk_gen_body(void);
static int32 rd_gen_case(struct genblk_t *);
static int32 rd_gen_if(struct genblk_t *);
static int32 rd_gen_begin(struct genblk_t *);
static int32 rd_dpi_declaration(void);
static struct dpi_t *alloc_init_dpi_rec(void);
static int32 rd_iodecl(word32);
static void add_net_attr(struct net_t *, int32);
static int32 rd_vardecl(word32);
static void init_ncomp(struct ncomp_t *);
static void chk_capwdecl_strens(word32);
static void chk_drvstren(word32);
static int32 rd_oparamdels(struct paramlst_t **);
static int32 do_wdecl_assgn(struct sy_t *, struct paramlst_t *, int32);
static struct net_t *decl_wirereg(word32, struct expr_t *, struct expr_t *,
 struct sy_t *);
static int32 rdbld_mod_varinitlst(struct sy_t *, int32);
static int32 is_decl_err(struct sy_t *, word32, word32);
static int32 chkset_wdrng(struct net_t *, struct expr_t *, struct expr_t *);
static int32 cmp_rng(struct expr_t *, struct expr_t *, struct expr_t *,
 struct expr_t *);
static int32 rd_verstrens(void);
static int32 rd_1verstren(int32 *);
static int32 is_tokstren(int32);
static struct conta_t *add_conta(struct expr_t *, struct expr_t *, int32,
 int32, struct genblk_t *);
static int32 rd_eventdecl(int32);
static int32 rd_paramdecl(int32, int32);
static int32 rd_dfparam_stmt(void);
static struct dfparam_t *alloc_dfpval(void);
static int32 rd_task(void);
static int32 rd_taskvardecl(int32, int32, char *);
static struct net_t *decl_taskvar(word32, struct expr_t *, struct expr_t *);
static struct task_pin_t *alloc_tskpin(void);
static int32 rd_func(void);
static void add_funcretdecl(char *, word32, struct expr_t *, struct expr_t *,
 int32);

static int32 rd_inst(char *);
static void add_cell_attr(struct cell_t *);
static int32 rd_pull_stren(char *, int32 *);
static struct namparam_t *rd_npndparams(void);
static struct namparam_t *rd1_namedparam(void);
static struct namparam_t *copy_namparamlst(struct namparam_t *);  
static int32 rd_iports(char *);
static int32 rd_cpin_conn(void);
static char *alloc_cpnam(char *);
static struct cell_pin_t *alloc_memcpins(void);
static struct cell_t *add_cell(char *);
static struct cell_t *alloc_memcell(void);
static void init_task(struct task_t *);
static int32 rd_tf_list_of_ports_decl(struct task_t *, char *, int32);
static int32 rd_decl_rng(struct expr_t **, struct expr_t **, int32);

static void mark_all_mod_confuncs(void);
static int32 func_canbe_const(struct task_t *);
static int32 expr_canbe_in_con_func(struct task_t *, struct expr_t *, int32);
static struct sy_t *confunc_get_sym(char *, struct symtab_t *,
 struct symtab_t *);
static int32 sysf_confunc_legal(int32);
static int32 stmt_can_be_con_func(struct task_t *, struct st_t *); 
static int32 stlst_can_be_con_func(struct task_t *, struct st_t *); 
static int32 csitem_canbe_in_con_func(struct task_t *, struct csitem_t *);
static int32 exprlst_canbe_in_con_func(struct task_t *, struct exprlst_t *);
static int32 dsable_xpr_canbe_in_con_func(struct task_t *,
 struct expr_t *);

static void eval_all_param_expr_to_nums(void);
static void param_rng_chk_cnvt_to_num(struct net_t *, char *);
static void chk_eval_param_rhs(struct net_t *, char *);
static void chk_assign_val_specparam(struct net_t *);
static void chk_dfparam_rhs_expr(struct dfparam_t *);
static struct task_t *alloc_task(struct sy_t *);

/* extern prototypes (maybe defined in this module) */
extern char *__pv_stralloc(char *);
extern char *__my_malloc(size_t);
extern struct mod_t *__alloc_mod(struct sy_t *);
extern void __init_mod(struct mod_t *, struct sy_t *);
extern void __freeze_mod_syms(struct symtab_t *, struct symtab_t *);
extern int32 __xpr_has_param(struct expr_t *);
extern struct ncomp_t *__alloc_arrncomp(void);
extern char *__prt_kywrd_vtok(void);
extern char *__prt_vtok(void);
extern void __freeze_1symtab(struct symtab_t *);
extern void __travfreeze_syms(struct tnode_t *);
extern void __travfreeze_genitem_sytabs(struct genitem_t *);
extern struct sy_t *__get_sym_env(char *);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct sy_t *__decl_sym(char *, struct symtab_t *);
extern struct sy_t *__bld_loc_symbol(int32, struct symtab_t *, char *,
 char *);
extern struct sy_t *__find_sym(char *);
extern struct net_t *__add_net(struct sy_t *, struct symtab_t *);
extern struct sy_t *__add_modsym(char *);
extern char *__to_ptnam(char *, word32);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_wtnam2(char *, word32);
extern char *__to_wrange(char *, struct net_t *);
extern char *__get_vkeynam(char *, int32);
extern char *__to_sytyp(char *, word32);
extern char *__msgtox_wrange(char *, struct expr_t *, struct expr_t *);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern char *__pregab_tostr(char *, word32 *, word32 *, struct net_t *);
extern char *__to_stren_nam(char *, int32, int32);
extern word32 __fr_stren_nam(int32);
extern struct symtab_t *__alloc_symtab(int32);
extern struct mod_pin_t *__alloc_modpin(void);
extern int32 __is_int_atom_typ(int32);
extern int32 __is_cint_typ(int32);
extern int32 __is_int_vec_typ(int32);
extern int32 __is_non_int_typ(int32);
extern int32 __is_2state_typ(int32);
extern struct genblk_t *__alloc_init_new_genblk(char *);
extern struct genitem_t *__alloc_init_new_genitem(int32);
extern struct tnode_t *__vtfind(char *, struct symtab_t *);
extern struct namparam_t *__alloc_namparam(void);
extern struct paramlst_t *__copy_dellst(struct paramlst_t *);
extern struct expr_t *__bld_rng_numxpr(word32, word32, int32);
extern struct st_t *__alloc_stmt(int32);
extern struct st_t *__alloc2_stmt(int32, int32, int32);
extern struct delctrl_t *__alloc_dctrl(void);
extern char *__to_splt_nam(char *, int32);
extern struct st_t *__rd_stmt(void);
extern int32 __rd_lstofsts(int32, struct st_t **, int32, int32);
extern struct paramlst_t *__alloc_pval(void);
extern struct expr_t *__gen_wireid_expr(struct sy_t *);
extern char *__bld_lineloc(char *, word32, int32);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern word32 __to_cap_size(int32);
extern void __init_xnd(struct expr_t *);
extern struct expr_t *__copy_expr(struct expr_t *);
extern struct expr_t *__alloc_newxnd(void);
extern void __get_vtok(void);
extern int32 __rd_moddef(struct symtab_t *, int32);
extern struct gref_t *__alloc_grtab(struct gref_t *, int32);
extern int32 __rd_udpdef(struct symtab_t *);
extern int32 __vskipto_modend(int32);
extern int32 __vskipto_lofp_end(void);
extern int32 __vskipto2_lofp_end(void);
extern void __add_sym(char *, struct tnode_t *);
extern int32 __chk_redef_err(char *, struct sy_t *, char *, word32);
extern void __remove_undef_mod(struct sy_t *);
extern void __my_free(void *, size_t);
extern int32 __vskipto2_any(int32, int32);
extern int32 __vskipto3_any(int32, int32, int32);
extern int32 __vskipto4_any(int32, int32, int32, int32);
extern void __unget_vtok(void);
extern int32 __col_parenexpr(int32, int32, int32);
extern int32 __col_connexpr(int32);
extern int32 __col_caseexpr(void);
extern struct exprlst_t *__alloc_xprlst(void);
extern void __bld_xtree(int32);
extern int32 __rd_spfy(struct mod_t *);
extern int32 __fr_wtnam(int32);
extern int32 __vskipto_any(int32);
extern int32 __col_rangeexpr(void);
extern int32 __is_capstren(int32);
extern int32 __col_comsemi(int32);
extern void __set_numval(struct expr_t *, word32, word32, int32);
extern int32 __col_lval(void);
extern int32 __col_newparamrhsexpr(void);
extern int32 __col_lofp_paramrhsexpr(void);
extern int32 __bld_tsk(char *, int32, int32, int32);
extern word32 __to_tasksytyp(int32);
extern char *__bld_gen_labnam(char *, char *, struct genblk_t *);
extern int32 __rd_tfdecls(char *);
extern int32 __bld_expnode(void);
extern void __set_xtab_errval(void);
extern int32 __col_delexpr(int32);
extern int32 __vskipto3_modend(int32, int32, int32);
extern void __set_opempty(int32);
extern void __free_xtree(struct expr_t *);
extern void __free2_xtree(struct expr_t *);
extern int32 __rd_opt_param_vec_rng(struct expr_t **, struct expr_t **,
 int32);
extern int32 __chk_paramexpr(struct expr_t *, int32);
extern struct net_t *__add_param(char *, struct expr_t *, struct expr_t *, 
 int32, int32);
extern void __init_stmt(struct st_t *, int32);
extern void __push_nbstk(struct st_t *);
extern void __pop_nbstk(void);
extern int32 __set_reg_widths(word32, struct expr_t **, struct expr_t **);

extern int32 __isleaf(struct expr_t *);
extern void __free_namedparams(struct namparam_t *);
extern struct cell_t *__alloc_cell(struct sy_t *);
extern struct cell_pin_t *__alloc_cpin(int32);
extern void __add_syp_to_undefs(struct sy_t *);
extern void __narrow_sizchg(struct xstk_t *, int32);
extern void __sizchg_widen(struct xstk_t *, int32);
extern void __sgn_xtnd_widen(struct xstk_t *, int32);
extern int32 __allocfill_cval_new(word32 *, word32 *, int32);
extern int32 __alloc_shareable_cval(word32, word32, int32);
extern int32 __alloc_shareable_rlcval(double);
extern char *__to1_stren_nam(char *, int32, int32);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern int32 __cmp_xpr(struct expr_t *, struct expr_t *, int32 *);
extern struct attr_t *__rd_parse_attribute(struct attr_t *);
extern void __cnv_stk_fromreg_toreal(struct xstk_t *, int32);
extern void __fnd_chk_fixup_prep_confuncs(void); 
extern void __eval_param_rhs_tonum(struct expr_t *, int32, int32);
extern void __assign_1specparam(struct net_t *);
extern int32 __nd_ndxnum(struct expr_t *, char *, int32);
extern struct sy_t *__get_forw_funcdef_sy(struct expr_t *, int32);
extern char *__bld_gen_scope_nam(char *, struct genblk_t *);
extern void __set_1net_srep(struct net_t *);
extern struct st_t *__rd_dctrl_st_always_comb_latch(void);

extern void __pv_ferr(int32, char *, ...);
extern void __pv_terr(int32, char *, ...);
extern void __sgferr(int32 id_num, char *s, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __pv_fwarn(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern void __finform(int32, char *, ...);
extern void __dbg_msg(char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __misc_fterr(char *, int32);

/*
 * read one top level module or udp definition
 * expects a keyword to have been read and reads end of module
 *
 * upon return current token must be endmodule/primitive or eof or
 * one before module/primitive
 */
extern void __rd_ver_mod(void)
{
 switch (__toktyp) {
  case TEOF: return;
  case MACROMODULE:
   __get_vtok();
   __finform(423, "macromodules not expanded - %s translated as module",
    __token);
   goto rd_def;
  case MODULE:
   /* know these will either die with eof or have read end mod/prim */
   /* or have skipped on error so next token read is mod/prim */
   __get_vtok();
rd_def:
   __rd_moddef(NULL, FALSE);
   break;
  case PRIMITIVE:
   /* because library must check for unresolved, get name before call */
   __get_vtok();
   __rd_udpdef(NULL);
   break;
  case GENERATE:
   __pv_ferr(3549,
    "P1364-2005 generate only allowed inside module definitions");
   __vskipto_modend(ENDGENERATE); 
   break;
  case ENDGENERATE:
   __pv_ferr(3549,
    "P1364-2005 endgenerate only allowed inside module definitions");
   __get_vtok();
   break;
  case GENVAR:
   __pv_ferr(3549,
    "P1364-2005 genvar declaration only allowed inside module definitions");
   __vskipto_any(SEMI);
   if (__toktyp == SEMI) __get_vtok();
   break;
  default:
   __pv_ferr(975, "module or primitive keyword expected - %s read",
    __prt_vtok());
   /* for common extra ;, will move to module and back up 1 */
   /* otherwise will skip to eof */  
   __vskipto_modend(ENDMODULE);
 }
}

/*
 * cfg form of read ver mod 
 *
 * SJM FIXME ??? - why is this different version needed 
 */
extern void __rd_cfg_ver_mod(void)
{
 switch (__toktyp) {
  case TEOF: return;
  case MACROMODULE:
   __get_vtok();
   __finform(423, "macromodules not expanded - %s translated as module",
    __token);
   __get_vtok();
   break;
  case MODULE:
   /* know these will either die with eof or have read end mod/prim */
   /* or have skipped on error so next token read is mod/prim */
   __get_vtok();
   break;
  case PRIMITIVE:
   /* because library must check for unresolved, get name before call */
   __get_vtok();
   break;
  default:
   __pv_ferr(975, "module or primitive keyword expected - %s read",
    __prt_vtok());
   /* for common extra ;, will move to module and back up 1 */
   /* otherwise will skip to eof */  
 }
}

/*
 * MODULE DEFINITION ROUTINES
 */

/*
 * read a module definition
 * 
 * if reading config, put module name in passed config lib el sym table 
 * upon return current token must be synced to file level token
 * return F if parse errors, T even if other errors
 */
extern int32 __rd_moddef(struct symtab_t *cfg_sytab, int32 isconfig)
{
 struct sy_t *syp;
 struct symtab_t *sp_sytp;
 struct mod_t *mdp;
 struct tnode_t *tnp;
 int32 save_lin_cnt;

 save_lin_cnt = __lin_cnt;
 __lofp_port_decls = FALSE;
 /* DBG remove --- */
 if (__top_sti != 0) __misc_terr(__FILE__, __LINE__);
 if (__inst_mod != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* these are couner for use in building object names */
 __cp_num = __conta_num = 1;

 /* notice that Verilog keywords are reserved words */
 if (__toktyp != ID)
  {
no_read:
   __pv_ferr(976, "module name expected - %s read", __prt_kywrd_vtok());
   __vskipto_modend(ENDMODULE);
   return(FALSE);
  }
 
 /* SJM 01/07/04 - if module in config library file, put into its mod sy tab */
 if (cfg_sytab != NULL) 
  {
   tnp = __vtfind(__token, cfg_sytab);
   /* dups already checked for */
   /* DBG remove -- */
   if (!__sym_is_new) __misc_terr(__FILE__, __LINE__);
   /* --- */
   __add_sym(__token, tnp);
   (cfg_sytab->numsyms)++;
   syp = tnp->ndp;
  }
 else syp = __add_modsym(__token);

 if (syp == NULL) goto no_read;
 syp->cfg_needed = FALSE;
 syp->sytyp = SYM_M;

 mdp = __alloc_mod(syp);
 syp->el.emdp = mdp;
 /* AIV 05/24/04 - need to set flag to get rid of highest level mods */
 /* that are scanned but never used in configs */
 mdp->m_inconfig = isconfig;
 /* this is where module definition actually resolved */
 syp->sydecl = TRUE;
 /* need place where udp declared */
 syp->syfnam_ind = __cur_fnam_ind;
 syp->sylin_cnt = __lin_cnt;

 /* if saw attribute before reading latest module keyword save */
 /* as string - evaled during pass 2 fixup */ 
 if (__wrk_attr.attr_seen)
  {
   /* here only one string possible - on serious error returns nil */
   /* if returns non nil, at least some attr_specs good */
   mdp->mattrs = __rd_parse_attribute(&__wrk_attr);
   /* SJM 07/30/01 - this is work read value, but now done with it */
   __my_free(__wrk_attr.attrnam, __attr_line_len + 1);
   __wrk_attr.attr_seen = FALSE;
  } 
 __push_wrkitstk(mdp, 0);

 /* must also allocate the new symbol table */
 __inst_mod->msymtab = __alloc_symtab(TRUE);
 /* module symbol table always outermost */
 __inst_mod->msymtab->sytpar = NULL;
 /* link symbol table back to module symbol */
 __inst_mod->msymtab->sypofsyt = syp;

 /* set list ends for elements that must be kept in order */
 __end_cp = NULL; __end_tbp = NULL; 
 __end_paramnp = __end_loc_paramnp = NULL;
 __end_ca = NULL; __end_ialst = NULL; __end_dfp = NULL;
 __end_impparamnp = NULL;
 __end_mod_varinitlst = NULL; 
 __cur_declobj = MODULE;
 __mod_specparams = 0;
 /* initialize symbol table stack so module on bottom */
 /* replaces previous module symbol table so no need to pop here */
 /* system names now in separate symbol table and separated by $ prefix */
 __top_sti = 0;
 __venviron[0] = __inst_mod->msymtab;

 /* do not need to build type until entire module read */
 /* if these return F, know needed to skip to file level mod/prim */
 if (!rd_modhdr(__inst_mod)) goto bad_end;
 if (!rd_modbody()) goto bad_end;
 /* AIV 11/03/10 - if SV can now have endmodule:name - mod name must match : */
 if (__sv_parse)
  {
   __get_vtok();
   if (__toktyp == COLON)
    {
     __get_vtok();
     /* must be a an ID */
     if (__toktyp != ID)
      {
       __pv_ferr(4868, "endmodule : [name] - missing module identifier - %s read", 
         __prt_vtok());
       goto bad_end;
      }
     else if (strcmp(mdp->msym->synam,  __token) != 0)
      {
       /* names must match */
       __pv_ferr(4869, "module name %s on line %d does not match endmodule : %s - names must be the same", mdp->msym->synam, save_lin_cnt, __token);
       goto bad_end;
      }
    }
   else __unget_vtok();
  }

 /* if error will not get linked in - this quarentees source order */
 if (__end_mdp == NULL) __modhdr = __inst_mod;
 else __end_mdp->mnxt = __inst_mod;
 __end_mdp = __inst_mod;

 /* current module now always one root of symbol table tree */
 /* declare wire names used in inst. conns. as 1 bit wires */
 /* SJM 01-25-12 - was not declaring undeclared wires used on the LHS of */
 /* undeclared continuous assignments - implicit name always scalar */
 decl_undecl_cell_and_conta_conns(__inst_mod);

 /* here may have no specparams but symbol because of syntax error */
 /* in common attempt to use defparams as specparams error */
 if (__inst_mod->mspfy != NULL && __inst_mod->mspfy->spfsyms != NULL)
  sp_sytp = __inst_mod->mspfy->spfsyms;
 else sp_sytp = NULL;

 __freeze_mod_syms(__inst_mod->msymtab, sp_sytp);

 /* SJM 01-15-08 - also need to freeze gen item symbol tables */
 /* nothing more added so can freeze - during expand new syms added */
 /* to the one gen item symbol table at mod level */
 if (__inst_mod->mgenitems != NULL)
  {
   __travfreeze_genitem_sytabs(__inst_mod->mgenitems);
  }

 bld_mdpin_table(__inst_mod);

 /* copy wrk gr table to module's gr table */ 
 if (__grwrknum > 0)
  {
   __inst_mod->mgrtab = __alloc_grtab(__grwrktab, __grwrknum);
   __inst_mod->mgrnum = __grwrknum;
   __grwrknum = 0; 
  }

 __last_libmdp = __inst_mod;
 __pop_wrkitstk();
 return(TRUE);

bad_end:
 /* need to free storage so no inst. will find this type */
 /* assuming could not stay synced while reading */
 if (__mod_specparams > 0) sp_sytp = __inst_mod->mspfy->spfsyms;
 else sp_sytp = NULL;
 __freeze_mod_syms(__inst_mod->msymtab, sp_sytp);
 /* make undeclared */
 syp->sydecl = FALSE;

 /* if error, do not need to freeze the genitem sy tabs - will never need */

 __pop_wrkitstk();
 return(TRUE);
}

/*
 * add the module name symbol to symbol table
 */
extern struct sy_t *__add_modsym(char *nam)
{
 struct tnode_t *tnp;
 struct sy_t *syp;

 tnp = __vtfind(nam, __modsyms);
 /* this is define before use in source file case */
 if (__sym_is_new)
  {
   __add_sym(nam, tnp);
   (__modsyms->numsyms)++;
   syp = tnp->ndp;
  }
 else
  {
   /* path impossible for copy mod splitting */
   syp = tnp->ndp;
   if (!__chk_redef_err(nam, syp, "module", SYM_M)) return(NULL);
   /* chk fail means never in module undef list */
   __remove_undef_mod(syp);
  }
 syp->sytyp = SYM_M;
 return(syp);
}

/*
 * remove a module from the undef list and count
 * module now resolved
 */
extern void __remove_undef_mod(struct sy_t *syp)
{
 struct undef_t *undefp;

 /* repeated use of "module [name]" with no definition will cause */
 /* lots of syntax error but also will have no module to remove */
 if (!syp->syundefmod) return;

 /* DBG remove -- */
 if (syp->sydecl) __misc_terr(__FILE__, __LINE__);
 /* --- */
 undefp = syp->el.eundefp;
 __undef_mods--; 
 /* case 1, removing head */ 
 if (undefp == __undefhd)
  {
   if (undefp == __undeftail)
    { 
     __undefhd = __undeftail = NULL;
     if (__undef_mods != 0) __misc_terr(__FILE__, __LINE__);
    }
   else { __undefhd = undefp->undefnxt; __undefhd->undefprev = NULL; }
  }
 /* case 2, removing tail - know at least 2 elements */
 else if (undefp == __undeftail)
  {
   /* SJM 06/03/2002 - added extra fields for 64 bit clean - no sharing */
   __undeftail = undefp->undefprev;
   __undeftail->undefnxt = NULL;
  }
 /* case 3, removing internal */
 else
  {
   undefp->undefprev->undefnxt = undefp->undefnxt;
   undefp->undefnxt->undefprev = undefp->undefprev;
  }
 syp->syundefmod = FALSE;
 syp->el.eundefp = NULL;
}

/*
 * allocate a new module
 */
extern struct mod_t *__alloc_mod(struct sy_t *syp)
{
 struct mod_t *mdp;

 mdp = (struct mod_t *) __my_malloc(sizeof(struct mod_t));
 __init_mod(mdp, syp);
 return(mdp);
}

/*
 * allocate a new module
 */
extern void __init_mod(struct mod_t *mdp, struct sy_t *syp)
{
 mdp->msym = syp;
 mdp->mod_last_lini = -1;
 mdp->mod_last_ifi = -1;
 mdp->msymtab = NULL;
 mdp->mod_cfglbp = NULL; 
 mdp->minstnum = 0;
 mdp->mhassts = FALSE;
 mdp->msplit = FALSE;
 mdp->mpndsplit = FALSE;
 mdp->mhassplit = FALSE;
 mdp->mgone = FALSE;
 mdp->msplitpth = FALSE;
 mdp->mwiddetdone = FALSE;
 mdp->dfp_allmodinsts_split = FALSE;
 mdp->mhas_widthdet = FALSE;
 mdp->mhas_indir_widdet = FALSE;
 mdp->mgia_rngdone = FALSE;
 mdp->m_has_garrs = FALSE;
 mdp->m_has_iarrs = FALSE;
 mdp->mpndprm_ingirng = FALSE;
 mdp->mhasisform = FALSE;
 /* default is 1 ns.(time unit) with 0 digits percision */
 mdp->mtime_units = __cur_units;
 /* normally just round (0 frac. digits of precision) */
 /* module precision is mtime units plus mtime units */
 mdp->mtime_prec = __cur_prec;
 mdp->mno_unitcnv = FALSE;
 if (__in_cell_region) { mdp->m_iscell = TRUE; __design_has_cells = TRUE; }
 else mdp->m_iscell = FALSE;
 mdp->m_hascells = FALSE;
 mdp->mod_hasdvars = FALSE;
 mdp->mod_dvars_in_src = FALSE;
 mdp->mod_dumpports_in_src = FALSE;
 mdp->mod_dumiact = FALSE;
 mdp->mod_rhs_param = FALSE;
 mdp->mod_hasbidtran = FALSE;
 mdp->mod_hastran = FALSE;
 mdp->mod_gatetran = FALSE;
 mdp->mod_1bcas = FALSE;
 mdp->mod_has_mipds = FALSE;
 mdp->mod_parms_gd = FALSE;
 mdp->mod_lofp_decl = FALSE;
 /* values not used by cver but set so vpi_ routines can return */
 mdp->mod_dfltntyp = (word32) __dflt_ntyp;
 mdp->mod_uncdrv =  (word32) __unconn_drive;
 /* SJM 05-01-10 - these need to be initialized here - were not */
 mdp->m_inconfig = FALSE;
 mdp->cfg_scanned = FALSE;

 mdp->m_idnum = -1;
 mdp->mod_flowg = NULL;
 mdp->ctev_list_hd = NULL;
#ifdef __XPROP__
 mdp->xprop_nb_taskp = NULL;
#endif
 mdp->mhas_frcassgn = FALSE;
 mdp->m_gia_in_gblks = FALSE;
 mdp->m_tfs_in_gblks = FALSE;
 mdp->m_xmrs_in_gblks = FALSE;
 mdp->m_dfps_in_gblks = FALSE;
 mdp->m_gen_xpnded = FALSE;
 mdp->m_maybe_gened = FALSE; 
 mdp->m_gened_remove = FALSE;
 mdp->m_no_param_match = FALSE;
 /* SJM 04-26-13 - not known if mod has tgl coverage until after optcfgfile */
 /* read - need to set lots of bits for simple -toggle so set there too */
 mdp->m_has_toggle_cover = FALSE;
 mdp->m_has_stmt_cover = __stmt_coverage;
 mdp->m_has_event_cover = __event_coverage;
 mdp->m_combined_into = FALSE;
 mdp->m_using_init_file = FALSE;
 mdp->m_opt_pli_bits_set = FALSE;

#ifdef __XPROP__
 mdp->m_use_xprop = __xprop;
 mdp->m_use_xprop2 = __xprop2;
 mdp->m_use_xprop_and_or_x  = __xprop_and_or_xs;
#endif
 mdp->m_gened_fstvars = FALSE;

 mdp->flatinum = 0;
 mdp->mpnum = 0;
 mdp->mpins = NULL;
 mdp->mgates = NULL;
 mdp->minum = 0;
 mdp->mgnum = 0;
 mdp->mcas = NULL;
 mdp->mcanum = 0;
 mdp->minsts = NULL;
 mdp->mnets = NULL;
 mdp->mnnum = 0;
 mdp->mtotvarnum = 0;
 mdp->mprms = NULL;
 mdp->mlocprms = NULL;
 mdp->mprmnum = 0;
 mdp->mlocprmnum = 0;
 mdp->moditps = NULL;
 mdp->m_itps_tgl_cover = NULL;
 mdp->mnxt = NULL;

 mdp->mattrs = NULL;
 mdp->mvarinits = NULL;
 mdp->mgateout_cbs = NULL;
 mdp->mgenitems = NULL;
 mdp->mgen_symtab = NULL;

 mdp->ialst = NULL;
 mdp->mtasks = NULL;

 /* SJM 07/30/08 - notice this is for com lab stupid dat ofs - not a mod ndx */ 
 mdp->mod_ndx_seq_no = 0;
 mdp->asm_partition_cnt = -1;  
 mdp->mod_idp_map = NULL;
 mdp->expr_tab = NULL;
 mdp->isnum_tree = NULL;
 mdp->dctrl_array = NULL;
 mdp->dctrl_size = -1;

 mdp->mstmts = NULL;
 mdp->mstnum = 0;
 mdp->mstnum_no_task = 0;

 mdp->prov_mstndx = NULL;
 mdp->prov_mstnum = 0;

 mdp->mgrtab = NULL;
 mdp->mgrnum = 0;

 mdp->m_pth_ndx = NULL;
 mdp->mpthnum = 0;

 mdp->m_npp_ndx = NULL;
 mdp->mnppnum = 0;

 mdp->mspfy = NULL;

 /* SJM 06-18-07 - now storing vars all in same mod together with */ 
 /* region repeated for every instance so can use idp base ptr addressing */
 mdp->mod_idata = NULL;
 mdp->mod_idata_siz = 0;
 mdp->mod_idata_siz_presim = 0;
 mdp->task_start_ofs = 0;

 /* LOOKATME - could convert to compile time only struct */
 mdp->mversno = 0;
 mdp->lastinum = 0;
 mdp->mlpcnt = -1;
 mdp->m_idnum = -1;
 mdp->mlevnxt = NULL;
 mdp->mspltmst = NULL;
 mdp->mpndspltmst = NULL;
 mdp->split_hd = NULL;
 mdp->split_tail = NULL;
 mdp->split_nxt = NULL;
 mdp->inst_split = NULL;
 mdp->recomb_to_mdp = NULL;
 mdp->mlevel = -1;
 mdp->mcells = NULL;
 mdp->smpins = NULL;
 mdp->iploctab = NULL;
 mdp->mdfps = NULL;
 mdp->sav_mdfps = NULL;
 mdp->dcep_lst_xmrp = NULL;
}

/*
 * NET LIST FIX UP ROUTINES CALLED DURING INPUT PROCESSING
 */

/*
 * declare all undeclared wires connected to module insts and gates
 *
 * SJM 01-25-12 - also need to declare undecl nets used on lhs of contas
 * implicitly
 */
static void decl_undecl_cell_and_conta_conns(struct mod_t *mdp)
{
 struct cell_t *cp;
 struct cell_pin_t *cpp;
 struct conta_t *cap;

 /* at this point all mod. insts., and gates on cell list */
 /* SJM 03/25/99 - all gate ports including control must be declared imp. */ 
 for (cp = mdp->mcells; cp != NULL; cp = cp->cnxt)
  {
   if (cp->cmsym == NULL) continue;
   
   for (cpp = cp->cpins; cpp != NULL; cpp = cpp->cpnxt)
    {
     /* this should always be at least 'bx by here */
     /* change to special unc. indicator and check/fix here */
     /* cell port connections lost */
     if (cpp->cpxnd == NULL) __misc_terr(__FILE__, __LINE__);
    
     dcl_1undecl_wires(cp->csym, cpp->cpxnd);
    }
  }
 /* also decl vars (IDs) used on lhs of contas as wire of implicit wire type */
 /* SJM 01-25-12 - implicit lhs decls idea is that undeclared are intended */
 /* to be 1 bit CAs that become buf gates */
 for (cap = mdp->mcas; cap != NULL; cap = cap->pbcau.canxt)
  {
   dcl_1undecl_wires(cap->casym, cap->lhsx);
  }
}

/*
 * declare all undeclared wires mentioned in inst. conns implicitly
 * anything in inst. port expr. implictly declared if not declared
 * even index of bit select and everything in concatenate
 *
 * SJM 05-25-12 - now also for conta lhs must decl as 1 bit default wire 
 * so passing the symbol since there is no cell here for contas
 */
static void dcl_1undecl_wires(struct sy_t *gate_syp, struct expr_t *ndp)
{
 struct net_t *np;
 struct sy_t *syp;
 struct expr_t *ndp2;

 switch ((byte) ndp->optyp) {
  case NUMBER: case REALNUM: case OPEMPTY: break;
  /* global are not declared in this module */
  case GLBREF: break;
  case ID:
   syp = ndp->lu.sy;
   if (syp->sydecl || syp->sytyp != SYM_N) break;

   np = syp->el.enp;
   /* must not implicitly declare I/O port */
   if (np->iotyp != NON_IO) break;
   syp->sydecl = TRUE;
   syp->sy_impldecl = TRUE;
   syp->syfnam_ind = gate_syp->syfnam_ind;
   syp->sylin_cnt = gate_syp->sylin_cnt;
   np->iotyp = NON_IO;
   /* type for undeclared is default net types */
   np->ntyp = __dflt_ntyp;
   np->nu.ct->n_iotypknown = TRUE;
   np->nu.ct->n_rngknown = FALSE;
   np->nu.ct->n_impldecl = TRUE;
   np->nu.ct->n_wirtypknown = TRUE;

   /* AIV 05/17/11 - LRM states that `default_nettype none */
   /* means that all wires must be defined no implicit */
   if (__dflt_ntyp_is_none)
    {
     __pv_ferr(3006, "wire '%s' %s cannot be implicitly defined with use of '`default_nettype none' - must explicity define wire",
     syp->synam, __bld_lineloc(__xs2, syp->syfnam_ind, syp->sylin_cnt));
    }

   __gfinform(419, syp->syfnam_ind, syp->sylin_cnt,
    "%s %s implicitly declared here from use in instance or gate connection",
     __to_wtnam(__xs, np), np->nsym->synam);
   break;
  default:
    /* SJM 07-21-09 - was not decl implict undecl wire in multi-dim sels */
   for (ndp2 = ndp->next_ndx; ndp2 != NULL; ndp2 = ndp2->next_ndx) 
    {
     dcl_1undecl_wires(gate_syp, ndp2);
    }
   /* know will not get here unless operator */
   if (ndp->lu.x != NULL) dcl_1undecl_wires(gate_syp, ndp->lu.x);
   if (ndp->ru.x != NULL) dcl_1undecl_wires(gate_syp, ndp->ru.x);
   break;
 }
}

/*
 * freeze module symbols and all enclosed symbol tables
 * treee form of tables free during fixup by freeing the tn blocks
 * notice sp_sytp can be nil but not sytp
 *
 * SJM 05-04-10 - now in chg to gen blks as pseudo mods - called to freeze
 * gen blk symtabs too  
 */
extern void __freeze_mod_syms(struct symtab_t *sytp,
 struct symtab_t *sp_sytp)
{
 /* since only system tasks and interpretive level symbols in level 0 */
 /* do not look for global there */
 sytp->sytpar = NULL;

 if (sytp->numsyms == 0) sytp->stsyms = NULL;
 else __freeze_1symtab(sytp);

 /* if needed also freeze specify specparam symbol table */
 if (sp_sytp != NULL)
  {
   /* symbol table empty if spec params all numbers - works since */
   /* back annotation is to slot not spec param */
   if (sp_sytp->numsyms == 0) sp_sytp->stsyms = NULL;
   else __freeze_1symtab(sp_sytp);
  }
 /* notice no top level symbol but contained symbols possible */
 if (sytp->sytofs != NULL) travfreeze_lowsymtab(sytp->sytofs);
}

/*
 * freeze one non empty symbol table
 */
extern void __freeze_1symtab(struct symtab_t *sytp)
{
 int32 bytes;

 /* SJM 12-23-08 - this just copies from avl symbol tab form to wrkstab */
 /* can now use on any symbol table */
 bytes = sytp->numsyms*sizeof(struct sy_t *);
 __wrkstab = (struct sy_t **) __my_malloc(bytes);
 __last_sy = -1;
 __travfreeze_syms(sytp->n_head);
 sytp->stsyms = __wrkstab;
 sytp->n_head = NULL;
 sytp->linkto_cp_osytp = NULL;
 /* non mod symbol table size wrong */
 if (__last_sy + 1 != sytp->numsyms) __misc_terr(__FILE__, __LINE__);
}

/*
 * traversal in sorted preorder
 */
extern void __travfreeze_syms(struct tnode_t *tnp)
{
 if (tnp->lp != NULL) __travfreeze_syms(tnp->lp);
 __wrkstab[++__last_sy] = tnp->ndp;
 if (tnp->rp != NULL) __travfreeze_syms(tnp->rp);
}

/*
 * depth first symbol table tree traversal across offspring
 */
static void travfreeze_lowsymtab(struct symtab_t *sytp)
{
 for (; sytp != NULL; sytp = sytp->sytsib)
  {
   if (sytp->numsyms == 0) sytp->stsyms = NULL;
   else __freeze_1symtab(sytp);
   if (sytp->sytofs != NULL) travfreeze_lowsymtab(sytp->sytofs);
  }
}

/*
 * convert list of module ports to array of ptrs to module ports
 * need so port can be accessed from its index
 * port order is list order that came from header list of ports
 */
static void bld_mdpin_table(struct mod_t *mdp)
{
 int32 pi, pnum;
 struct mod_pin_t *mpp;
 struct mod_pin_t *mphdr, *mpp2;

 if ((pnum = mdp->mpnum) == 0) return;
 mphdr = (struct mod_pin_t *) __my_malloc(pnum*sizeof(struct mod_pin_t));
 for (pi = 0, mpp = mdp->mpins; mpp != NULL; mpp = mpp->mpnxt, pi++)
  {
   mphdr[pi] = *mpp;
   mphdr[pi].mpnxt = NULL;
  }
 /* now free all old ports - contents copied - and need to keep expr */
 for (mpp = mdp->mpins; mpp != NULL;) 
  {
   mpp2 = mpp->mpnxt;
   __my_free(mpp, sizeof(struct mod_pin_t));
   mpp = mpp2;
  }
 mdp->mpins = mphdr;
}

/*
 * check for and emit a redefinition error
 */
extern int32 __chk_redef_err(char *nam, struct sy_t *syp,
 char *newtnam, word32 styp)
{
 if (!syp->sydecl)
  {
   /* when see mod or udp, assume mod - may turn out to be udp and no err */
   if (syp->sytyp == SYM_M && styp == SYM_UDP) return(TRUE);
  }

 if (syp->sytyp != styp)
  {
   __pv_ferr(977, "cannot redefine %s as a %s - previous type was %s at %s",
    nam, newtnam, __to_sytyp(__xs, syp->sytyp), __bld_lineloc(__xs2,
    syp->syfnam_ind, syp->sylin_cnt));
   return(FALSE);
  }
 if (syp->sydecl)
  {
   __pv_ferr(978, "cannot redefine %s %s - previous definition %s",
    newtnam, nam, __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
   return(FALSE);
  }
 return(TRUE);
}

/*
 * process an the module header iolist
 * must read leading ( or (empty ;) and reads trailing ;
 *
 * if return T, even if error parsing can continue in module
 * sometimes guesses that continuing ok, error caught by next routine
 */
static int32 rd_modhdr(struct mod_t *mp)
{
 struct mod_pin_t *mpp, *last_mpp;

 /* empty I/O list legal */
 __get_vtok();

 /* P1364 2001 allows #(list of normal parameter decls) here that allows */
 /* param decls in addition to body param decls */
 if (__toktyp == SHARP)
  {
   /* if error and sync failed, know synced to module level item */
   if (!rd_hdrpnd_parmdecls()) goto ret_end;
  }
 
 if (__toktyp == SEMI) return(TRUE);
 /* norma end reads ending rpar but on error mayhave synced to lpar */
 if (__toktyp != LPAR) __get_vtok();

 if (__toktyp != LPAR)
  {
   __pv_ferr(979, 
    "module header list of ports initial left parenthesis expected - %s read",
    __prt_vtok());
   if (__vskipto2_any(RPAR, SEMI)) 
    {
     if (__toktyp == RPAR) __get_vtok();
     /* if not semi, assume semi left out - if bad, next rout. will catch */
     if (__toktyp != SEMI) __unget_vtok();
     return(TRUE);
    }
ret_end:
   switch ((byte) __syncto_class) {
    case SYNC_FLEVEL: return(FALSE);
    case SYNC_MODLEVEL: return(TRUE);
    /* should never sync to statement up here */
    case SYNC_STMT:
     __vskipto_modend(ENDMODULE);
     return(FALSE);
    default: __case_terr(__FILE__, __LINE__);
   }
  }
 __get_vtok();
 if (__toktyp == RPAR)
  {
do_end:
   __get_vtok();
do_end2:
   if (__toktyp == SEMI) return(TRUE);

   __pv_ferr(980,
    "module header list of ports end semicolon expected - %s read",
    __prt_vtok());
   __unget_vtok();
   return(TRUE);
  }

 /* SJM 05/23/04 - branch point for separate list of port decl header form */
 if (__toktyp == INPUT || __toktyp == OUTPUT || __toktyp == INOUT)
  {
   /* reads ending ; after ) - also sets flags that prevents further */
   /* port decls that would be legal for port name (explicit too) forms */
   if (!rd_list_of_ports_decl(mp)) goto ret_end;
   if (__toktyp == RPAR) __get_vtok();
   goto do_end2;
  }

 for (last_mpp = NULL;;)
  {
   /* this declares the symbols in the header */

   /* SJM 08/30/00 - need to ignore ,, and not count as a port in hdr def. */
   if (__toktyp == COMMA)
    {
     __pv_fwarn(3103,
      "empty ,, in module header port definition list ignored - not used in ordered instance connection list"); 
     goto nxt_port;
    }
   if (__toktyp == RPAR)
    {
     __pv_fwarn(3103,
      "empty ,) in module header port definition list ignored"); 
     goto do_end;
    } 

   if (!rd_portref())
    {
     /* on error ignore this port and move on to next */
do_resync:
     if (__vskipto3_any(COMMA, SEMI, RPAR)) 
      {
       /* port effectively not seen - error emitted already */
       if (__toktyp == COMMA) goto nxt_port;
       if (__toktyp == RPAR) goto do_end;
       break;
      }
     goto ret_end;
    }

   /* assume unvectored 1 bit port */
   mpp = __alloc_modpin();
   /* think possiblity unnamed ports can appear here */
   if (strcmp(__portnam, "") == 0) mpp->mpsnam = NULL;
   else mpp->mpsnam = __pv_stralloc(__portnam);
   mpp->mp_explicit = (__mpref_explicit) ? TRUE : FALSE;

   if (last_mpp == NULL) mp->mpins = mpp; else last_mpp->mpnxt = mpp;
   last_mpp = mpp;
   mpp->mpref = __root_ndp;
   /* count number of ports */
   (mp->mpnum)++;
   if (mp->mpnum >= MAXNUMPORTS)
    {
     __pv_ferr(314, "INTERNAL FATAL - module has more than %d ports - contact Tachyon DA",
      MAXNUMPORTS);
     (mp->mpnum)--; 
    }

   if (__toktyp == RPAR) goto do_end;
   if (__toktyp != COMMA)
    {
     __pv_ferr(984,
      "module header comma expected - %s read", __prt_vtok());
     goto do_resync;
    }
nxt_port:
   __get_vtok();
  }
 return(TRUE);
}

/*
 * read the module define #(param decl list) parameter delcarations
 * know the leading # read and reads one past ending ')' (probably '(')
 *
 * format is: module xx #([parameter decl list], ...) (port list) ...
 * notice that only legal for module definitions
 */
static int32 rd_hdrpnd_parmdecls(void)
{
 __get_vtok();
 if (__toktyp != LPAR)
  {
   __pv_ferr(984,
    "module header #([parameter decl], ..) form starting left paren expected - %s read",
    __prt_vtok());
   if (!__vskipto3_any(RPAR, LPAR, SEMI)) return(FALSE);
   return(TRUE);
  }
 __get_vtok();
 for (;;)
  {
   if (__toktyp == RPAR) return(TRUE);
   if (__toktyp != PARAMETER)
    {
     if (!__vskipto4_any(PARAMETER, COMMA, RPAR, SEMI)) return(FALSE);
     if (__toktyp == PARAMETER) continue;
     if (__toktyp == COMMA) { __get_vtok(); continue; }
     if (__toktyp == RPAR || __toktyp == SEMI) return(TRUE);
    }

   /* AIV 09/27/06 - can never be a local param here */
   if (!rd_paramdecl(TRUE, FALSE)) return(FALSE);
  }
}

/*
 * read module header port .[port name]([port expr.]) or [port expr.] form
 * know 1st token name read and reads one past end , or ) if no error
 * if no error, expression in root_ndp
 *
 * medium level - caller syncs if returns error F
 */
static int32 rd_portref(void)
{
 int32 nd_rpar;

 if (__toktyp == DOT)
  {
   __mpref_explicit = TRUE;
   __get_vtok();
   if (__toktyp != ID)
    {
     __pv_ferr(985, "module definition header name of port expected - %s read",
      __prt_kywrd_vtok());
     return(FALSE);
    }
   strcpy(__portnam, __token);
   __get_vtok();
   if (__toktyp != LPAR)
    {
     __pv_ferr(986,
     "module definition header .[port]([port expr.]) form left parenthesis expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   nd_rpar = TRUE;
   /* read collect the expression that must end with ) only */
   __get_vtok();
   /* this cannot be empty */
   if (__toktyp == RPAR)
    { 
     __finform(3004,
      "empty module definition header explicit form () port expression no effect");
     __last_xtk = 0;
     __set_opempty(0);
    }
   else 
    {
     if (!__col_parenexpr(-1, FALSE, FALSE)) return(FALSE);
    }
  }
 else
  {
   __mpref_explicit = FALSE;
   nd_rpar = FALSE;
   strcpy(__portnam, "");
   /* read/collect expression that must end with ) or , */
   /* know 1st token of expression read */
   if (!__col_connexpr(-1)) return(FALSE);
  }
 /* build the tree, copy/allocate nodes, sets root_ndp to its root */
 __bld_xtree(0);
 /* must set all net like things as IO ports */
 set_ioprtnets(__root_ndp);

 if (!nd_rpar)
  {
   struct expr_t *idx;

   /* for unnamed port is simple id, that is port name */
   if (__root_ndp->optyp == ID) idx = __root_ndp;
   else if (__root_ndp->optyp == LSB || __root_ndp->optyp == PARTSEL || 
    __root_ndp->optyp == PARTSEL_NDX_PLUS ||
    __root_ndp->optyp == PARTSEL_NDX_MINUS)
    {
     idx = __root_ndp->lu.x;
    }
   else idx = NULL;
   if (idx != NULL) strcpy(__portnam, idx->lu.sy->synam);
  }
 else 
  {
   if (__toktyp != RPAR)
    {
     __pv_ferr(988,
     "module definition header named port form right parenthesis expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   __get_vtok();
  }
 return(TRUE);
}

/*
 * mark all nets in I/O port expression as I/O of unknown direction
 * can be arbitrary expressions here because not yet checked 
 */
static void set_ioprtnets(struct expr_t *ndp)
{
 struct sy_t *syp;

 if (__isleaf(ndp))
  {
   if (ndp->optyp == ID)
    {
     syp = ndp->lu.sy;
     /* module header wire %s declaration inconsistent */
     /* DBG remove -- */
     if (syp->sytyp != SYM_N)
      {
       __pv_ferr(684,
        "I/O port definition %s name %s type %s illegal - must be a net",
        __msgexpr_tostr(__xs, ndp), syp->synam, __to_sytyp(__xs2, syp->sytyp));
       syp->sytyp = SYM_N;
      }
     /* --- */
     syp->el.enp->iotyp = IO_UNKN;
    }
   return;
  }
 if (ndp->lu.x != NULL) set_ioprtnets(ndp->lu.x);
 if (ndp->ru.x != NULL) set_ioprtnets(ndp->ru.x);
}

/*
 * allocate a module pin (port) element
 */
extern struct mod_pin_t *__alloc_modpin(void)
{
 struct mod_pin_t *mpp;

 mpp = (struct mod_pin_t *) __my_malloc(sizeof(struct mod_pin_t));
 mpp->mpsnam = NULL;
 mpp->mptyp = IO_UNKN;
 /* gets set and used only for bidirects */ 
 mpp->mp_explicit = FALSE;
 mpp->mp_jmpered = FALSE;
 mpp->inout_unc = FALSE;
 mpp->assgnfunc_set = FALSE;
 mpp->has_mipd = FALSE;
 mpp->has_scalar_mpps = FALSE;

 /* assume 1 for prim */
 mpp->mpwide = 1;
 /* expression for .[name]({...}) form but usually same internal net */
 mpp->mpref = NULL;
 mpp->mpattrs = NULL;
 mpp->mpfnam_ind = __cur_fnam_ind;
 mpp->mplin_cnt = __lin_cnt;
 mpp->mpaf.mpp_upassgnfunc = NULL;
 mpp->pbmpps = NULL;
 mpp->mpnxt = NULL;
 return(mpp);
}

/*
 * ROUTINES TO READ AND ADD LIST OF PORTS STYLE HEADER PORT DECLATIONS 
 */

/*
 * read list of header port declarations
 * new alternative ANSII style port header decl form added to 2001 LRM
 *
 * first port type keyword read and reads ending );
 *
 * if return T, even if error parsing can continue in module
 * on error must sync to semi and back up one - mod item which just returns
 */
static int32 rd_list_of_ports_decl(struct mod_t *mp)
{
 int32 first_time, wtyp, ptyp, attr_ttyp, has_attr, is_signed;
 struct sy_t *syp;
 struct net_t *np;
 struct expr_t *x1, *x2, *ox1, *ox2;
 struct mod_pin_t *mpp, *last_mpp;
 char s1[RECLEN];

 /* DBG remove -- */
 if (__cur_cntxt_gblk != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 syp = NULL;
 np = NULL;
 ptyp = -1;
 /* even if syntax error, T once a port type keyword appears in hdr */
 mp->mod_lofp_decl = TRUE;
 __lofp_port_decls = TRUE;

 last_mpp = NULL;
 for (;;)
  {
   /* attribute collected by scanner - but need to save so associates with */
   /* right port */
   if (__attr_prefix)
    {
     __wrk_attr.attr_tok = __toktyp;
     __wrk_attr.attr_seen = TRUE;
     /* for now this is unparsed entire attr. string */
     __wrk_attr.attrnam = __pv_stralloc(__attrwrkstr);
     __wrk_attr.attr_fnind = __attr_fnam_ind;
     __wrk_attr.attrlin_cnt = __attr_lin_cnt;
    }
   else __wrk_attr.attr_seen = FALSE;

   attr_ttyp = __toktyp;
   if (__toktyp == INPUT) ptyp = IO_IN;
   else if (__toktyp == OUTPUT) ptyp = IO_OUT;
   else if (__toktyp == INOUT) ptyp = IO_BID;
   else __case_terr(__FILE__, __LINE__); 

   __get_vtok();

   /* defaults to wire if net type omitted - can be var/reg type */
   if ((wtyp = __fr_wtnam(__toktyp)) != -1) __get_vtok();
   else wtyp = N_WIRE;

   /* SJM 07-30-10 - with new SV semantics ints default to signed but can */
   /* be changed by unsigned keyword */
   if (__is_int_atom_typ(wtyp) || __is_non_int_typ(wtyp)) is_signed = TRUE;
   else is_signed = FALSE;

   /* vectored or scalared keywords never appear in port decls */
   if (__toktyp == SIGNED)
    {
     is_signed = TRUE;
     if (wtyp == N_EVENT || __is_non_int_typ(wtyp)) 
      {
       __pv_ferr(3423,
        "signed keyword illegal for variable type %s in ansi style port header declarations",
        __to_wtnam2(s1, wtyp));
      }
     __get_vtok();
    }
   else if (__toktyp == UNSIGNED)
    {
     is_signed = FALSE;
     if (wtyp == N_EVENT || __is_non_int_typ(wtyp)) 
      {
       __pv_ferr(3423,
        "unsigned keyword illegal for variable type %s in ansi style port header declarations",
        __to_wtnam2(s1, wtyp));
      }
    }

   /* even if error if 1 past ending ] continue */
   if (!rd_decl_rng(&ox1, &ox2, FALSE))
    {
     /* bad decl - but if sync to new I/O port direction, caller will cont */
     if (!__vskipto_lofp_end()) return(FALSE); 
     if (__toktyp == RPAR) { __get_vtok(); return(TRUE); } 
     /* semi read */
     return(TRUE);
    }
   if (ox1 != NULL)
    {
     if (!__is_int_vec_typ(wtyp) && wtyp >= NONWIRE_ST)
      {
       __pv_ferr(1002,
        "ansi style port header declaration vector range illegal for type %s",
        __to_wtnam2(s1, wtyp));
       ox1 = ox2 = NULL;
      }
    }

   /* use local has attr flag so can turn glb seen off before return */
   if (__wrk_attr.attr_seen)
    { has_attr = TRUE; __wrk_attr.attr_seen = FALSE; }
   else has_attr = FALSE;

   x1 = x2 = NULL;
   for (first_time = TRUE;;)
    {
     if (__toktyp != ID)
      {
       __pv_ferr(992, "list of port form %s port name expected - %s read",
        __to_ptnam(s1, ptyp), __prt_kywrd_vtok());

       if (__vskipto2_lofp_end())
        {
         if (__toktyp == SEMI) return(TRUE);
         if (__toktyp == RPAR) { __get_vtok(); return(TRUE); }
         /* only other possibility is the port name separating comma */
         continue;
        }
       /* can't recover (resync) from error - synced to module item */
       return(FALSE);
      }

     if ((syp = __get_sym_env(__token)) != NULL)
      {
       __pv_ferr(3418, "list of port form %s port name %s redeclared", 
        __to_ptnam(s1, ptyp), __token);
       goto nxt_port;
      }

     if (first_time) { x1 = ox1; x2 = ox2; first_time = FALSE; } 
     else
      {
       if (x1 == NULL) x1 = x2 = NULL;
       else { x1 = __copy_expr(ox1); x2 = __copy_expr(ox2); }
      }

     /* first declare the port's wire/reg */
     if ((np = decl_wirereg(wtyp, x1, x2, NULL)) == NULL) goto nxt_port;

     /* if previously used will be treated as reg - must set to compatible */
     /* wire type if declared as time or int32 */
     np->ntyp = wtyp;
     syp = np->nsym;

     /* SJM 08-04-10 - new 2 state var */
     if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;

     /* if saw an (* *) attribute for module item token, seen on */
     if (has_attr)
      {
       /* this add to net's attr list on end if also net decl first */
       add_net_attr(np, attr_ttyp);
      }

     /* SJM 10/02/03 - signed can be turned on either in port or wire decl */ 
     np->n_signed = is_signed;

     np->iotyp = ptyp;
     /* for list of ports mod header decl form, all info in hdr decl */ 
     np->nu.ct->n_iotypknown = TRUE;

     syp->sydecl = TRUE;
     /* need I/O decl. place not header or wire decl. */
     syp->syfnam_ind = __cur_fnam_ind;
     syp->sylin_cnt = __lin_cnt;

     /* then add the port to the port list - know port and net name same */
     mpp = __alloc_modpin();
     mpp->mpsnam = __pv_stralloc(np->nsym->synam);
     mpp->mp_explicit = FALSE;

     if (last_mpp == NULL) mp->mpins = mpp; else last_mpp->mpnxt = mpp;
     last_mpp = mpp;

     /* name of port still in token - expr here always ID */
     __last_xtk = -1;
     if (!__bld_expnode()) __set_xtab_errval();
     __bld_xtree(0);
     mpp->mpref = __root_ndp;

     /* count number of ports */
     (mp->mpnum)++;
     if (mp->mpnum >= MAXNUMPORTS)
      {
       __pv_ferr(314,
        "INTERNAL FATAL - module has more than %d ports - contact Tachyon DA",
        MAXNUMPORTS);
       (mp->mpnum)--; 
      }

nxt_port:
     __get_vtok();
     if (__toktyp == RPAR) return(TRUE);

     /* AIV 08/17/11 - now if there is an = if not a wire can init value */
     /* could be a variable initialization i.e. integer i = 12; */
     if (__toktyp == EQ && np != NULL)
      {
       if (np->ntyp >= NONWIRE_ST)
        {
         /* cannot init an array - illegal syntax */
         if (np->n_isarr)  
          {
            __pv_ferr(3429,
          "variable assign initialize form illegal for %s - arrays cannot be initialized",
           syp->synam); 
           goto try_resync;
          }
         if (!rdbld_mod_varinitlst(syp, TRUE)) goto try_resync;

         if (__toktyp == RPAR) return(TRUE);
        }
       else
        {
         /* must be of non-wire type to initialize */
         __pv_ferr(3437, 
           "variable assign initialize form illegal for %s - cannot initialize type %s", 
          syp->synam, __to_wtnam2(__xs, np->ntyp));
        }
      }

try_resync:

     if (__toktyp != COMMA)
      {
       __pv_ferr(995,
        "list of ports form declaration list comma or right paren expected - %s read",
        __prt_vtok());
       /* try to resync */
       if (!__vskipto_lofp_end()) return(FALSE); 
       if (__toktyp == COMMA) goto nxt_net;
       /* misplaced semi or sync to rpar */
       return(TRUE);
      }
nxt_net:
     __get_vtok();
     if (__toktyp == INPUT || __toktyp == OUTPUT || __toktyp == INOUT)  
      break;
    }
  }
 __misc_terr(__FILE__, __LINE__);
 return(TRUE);
}

/*
 * NEW SV TYPE GROUPING ROUTINES
 */

/*
 * return T if integer atomic type (only old integer and time 4 state)
 */
extern int32 __is_int_atom_typ(int32 wtyp)
{
 switch (wtyp) {
  case N_INT:
  case N_CINT:
  case N_TIME:
  case N_BYTE:
  case N_SHORTCINT:
  case N_LONGCINT:
  case N_CHANDLE:
   return(TRUE);
  default: break;
 }
 return(FALSE);
}

/*
 * return T if C style 2-state type 
 */
extern int32 __is_cint_typ(int32 wtyp)
{
 switch (wtyp) {
  case N_CINT:
  case N_BYTE:
  case N_SHORTCINT:
  case N_LONGCINT:
  case N_CHANDLE:
  case N_REAL:
   return(TRUE);
  default: break;
 }
 return(FALSE);
}

/*
 * routine for var types that are stored as 2 state in idp area
 * can be eval as 2 state and if not T, assigns to state must conver x/z to 0
 *
 * SJM 08-04-10 - currently interpreter expr eval always pushes as a/b
 */
extern int32 __is_2state_typ(int32 wtyp)
{
 switch (wtyp) {
  /* notice N_INT and N_TIME are 4 state */
  case N_BIT: case N_BYTE: case N_CINT: case N_SHORTCINT: case N_LONGCINT:
  case N_CHANDLE:
   return(TRUE);
  case N_REG:
  case N_INT:
  case N_LOGIC:
   if (__opt_two_state) return(TRUE);
   else return(FALSE);
   break;
  case N_WIRE: case N_TRI: case N_TRIAND: case N_WA: case N_TRIOR: case N_WO:
   /* AIV 08/25/10 - if running with +2state and including wires are 2-state */
   if (__opt_two_state && !__opt_two_state_no_wires) return(TRUE);
   else return(FALSE);
  default: break;
 }
 return(FALSE);
}

/*
 * return T if vector type (can take 'packed' range before ID)
 *
 * SJM - 08-04-10 SV - for debugging make reg, logic and bit same need ifs
 */
extern int32 __is_int_vec_typ(int32 wtyp)
{
 switch (wtyp) {
  case N_REG: case N_LOGIC: case N_BIT:
   return(TRUE);
  }
 return(FALSE);
}

/*
 * return T if non integer (basically real)
 *
 * SJM 08-02-10 - realtime is just converted to real currently (fix?)
 */
extern int32 __is_non_int_typ(int32 wtyp)
{
 switch (wtyp) {
//SJM 08-02-10 - WRITME SV add N_SHORTREAL
  case N_REAL: return(TRUE);
  default: break;
 }
 return(FALSE);
}

/*
 * MODULE ITEM ROUTINES
 */

/*
 * read module body and process the various module items
 * know __inst_mod points to current module structure
 * know module port list end ; read
 *
 * if returns T must be synced on end mod 
 *
 * SJM 11-07-08 - 5 new module body items added for generate
 */
static int32 rd_modbody(void)
{
 int32 rv, wtyp;
 char typnam[IDLEN];

 __in_gen_region = FALSE;
 __last_gip = NULL;
 __mod_gen_id = -1;

#ifdef __XPROP__
 /* this is the dummy place holder for non-blocking assigns when the compiler */
 /* is used with xprop, the task is need to alloc nb stmts to be used at */
 /* prep time for assign xprop accumed values */
 /* if optconfig can now turn on xprop */
 if ((__xprop || __optcfg_fils != NULL) && __compiled_sim)
  {
   int32 save_top_sti;
 
   save_top_sti = __top_sti;
   rv = __bld_tsk("nb$xproptask", TASK, FALSE, FALSE);
   if (rv == 0) __misc_terr(__FILE__, __LINE__);
   __inst_mod->xprop_nb_taskp = __cur_tsk;
   __end_tbp = __cur_tsk;
   __inst_mod->mtasks = __cur_tsk;
   __cur_tsk->t_used = TRUE;
   __top_sti = save_top_sti;
  }
#endif

 for (;;)
  {
   /* routines called in switch expected to read ending ; or token */
   __get_vtok();
   /* SJM 03/20/00 - save attribute info for mod items */
   if (__attr_prefix)
    {
     __wrk_attr.attr_tok = __toktyp;
     __wrk_attr.attr_seen = TRUE;
     /* for now this is unparsed entire attr. string */
     __wrk_attr.attrnam = __pv_stralloc(__attrwrkstr);
     __wrk_attr.attr_fnind = __attr_fnam_ind;
     __wrk_attr.attrlin_cnt = __attr_lin_cnt;
    }
   else __wrk_attr.attr_seen = FALSE;

   switch(__toktyp) {
    case TEOF:
     __pv_ferr(989, "endmodule missing");
     return(FALSE);
    case INPUT:
     if (!rd_iodecl(IO_IN))
      {
moditem_resync:
       /* on error - reset attribute prefix state */
       __wrk_attr.attr_seen = FALSE;
       switch ((byte) __syncto_class) {
        case SYNC_FLEVEL: return(FALSE);
        case SYNC_MODLEVEL: break;
	/* if sync. to statement assume initial left out */
        case SYNC_STMT:
         /* here must clear any pushed back */
         if (__lasttoktyp != UNDEF) __get_vtok(); 
	 /*FALLTHRU */
        case SYNC_TARG:
         /* SJM 11-08-08 - separated reading of init/always into proc */
         if (rd_init_always(INITial)) continue;
         goto moditem_resync;
        default: __case_terr(__FILE__, __LINE__);
       }
      }
     continue;
    case OUTPUT:
     if (!rd_iodecl(IO_OUT)) goto moditem_resync;
     continue;
    case INOUT:
     if (!rd_iodecl(IO_BID)) goto moditem_resync;
     continue;
    case EVENT:
     if (!rd_eventdecl(FALSE)) goto moditem_resync;
     continue;
    case INITial: case ALWAYS:
    /* AIV 07/12/12 - now supporting new SV always_* types */
    case ALWAYS_COMB: case ALWAYS_FF: case ALWAYS_LATCH:
     if (rd_init_always(__toktyp)) continue;
     goto moditem_resync;
    case ASSIGN:
     if (!rd_contassign()) goto moditem_resync;
     continue;
    case PARAMETER:
     if (!rd_paramdecl(FALSE, FALSE)) goto moditem_resync;
     continue;
    case LOCALPARAM:
     if (!rd_paramdecl(FALSE, TRUE)) goto moditem_resync;
     continue;
    case DEFPARAM:
     __rding_defparam = TRUE;
     rv = rd_dfparam_stmt();
     __rding_defparam = FALSE;
     if (!rv) goto moditem_resync;
     continue;
    case SPECIFY:
     if (!__rd_spfy(__inst_mod)) goto moditem_resync;
     continue;
    case TASK:
     __cur_declobj = TASK;
     rv = rd_task();
     __cur_declobj = MODULE;
     if (!rv)
      { 
       /* if have something on task var sym tab stack - must mark it gone */
       /* SJM 04-12-14 - FIXED BUG - minor misc terr on totally bad ver src */
       if (__top_sti > 0) __top_sti = 0;
       goto moditem_resync;
      }
     continue;
    case FUNCTION:
     __cur_declobj = TASK;
     rv = rd_func();
     __cur_declobj = MODULE;
     if (!rv) goto moditem_resync;
     continue;
    case ENDMODULE:
     /* save end so can put in module's end souce range fields */
     __inst_mod->mod_last_lini = __lin_cnt;
     __inst_mod->mod_last_ifi = __cur_fnam_ind;

     /* catch common extra ; error here */
     __get_vtok();
     if (__toktyp == SEMI)
      __pv_ferr(999, "semicolon following endmodule illegal"); 
     else __unget_vtok();
     break;
    case ENDPRIMITIVE:
     /* but assume still in sync */
     __pv_ferr(990, "module definition can not end with endprimitive");
     break;
    case GENVAR:
     /* genvar form is stylized "genvar <comma list of variables>;" */
     /* SJM 11-08-08 - genvar can appear inside generate or as mod item */
     if (!rd_genvar_decl()) return(FALSE);
     continue;
    case GENERATE:
     if (!rd_gen_region_mod_items()) goto moditem_resync;
     /* SJM 04-11-10 - mashed gen blks still can return T here */
     if (__pv_err_cnt > 0) goto moditem_resync;
     continue;
    case ENDGENERATE:
     /* SJM 11-08-08 - generate-endgenerate now input in separate proc */
     __pv_ferr(3585, "endgenerate read - but no previous matching generate");
      continue;
    case FOR:
     /* SJM 11-08-08 - gen for/case/if can be outside generate region */
     if (!rd_gen_for(NULL)) goto moditem_resync;
     continue;
    case FOREACH:
     if (!rd_gen_foreach(NULL)) goto moditem_resync;
     continue;
    case CASE:
     if (!rd_gen_case(NULL)) goto moditem_resync;
     continue;
    case IF:
     if (!rd_gen_if(NULL)) goto moditem_resync;
     break;
    case Begin:
     /* SJM 05-17-11 - need to allow begin-end gen items - treat as T if */
     if (!rd_gen_begin(NULL)) goto moditem_resync;
     break;
    case IMPORT:
    case EXPORT:
     if (!rd_dpi_declaration()) goto moditem_resync;
     continue;
    default:
     if ((wtyp = __fr_wtnam(__toktyp)) != -1)
      {
       /* false here means out of sync - must skip rest of module */
       /* if T will have skipped to semi */
       if (!rd_vardecl((word32) wtyp)) goto moditem_resync;
       /* needed to add attribute to every net in list - can now reset */
       __wrk_attr.attr_seen = FALSE;
       continue;
      }
     /* must be instance (udp, gate, module instantiation) */
     if (__toktyp != ID)
      {
       __pv_ferr(991, "module type, gate or udp name expected - %s read",
        __prt_kywrd_vtok());
       /* can only sync to ; here - else need names to decl. */
       if (!__vskipto_any(SEMI)) goto moditem_resync;
       /* SJM 04-27-10 - SJM - need to change sync for new stuff in gen */
       /* syntax erros differ such as spcsyn2.v in tstshs7 */
       return(FALSE);
      }
     strcpy(typnam, __token);
     if (!rd_inst(typnam)) goto moditem_resync;
     /* needed to add attr to every instance, now can reset attr seen */ 
     __wrk_attr.attr_seen = FALSE;
     continue;
   }
   break;
  }
 return(TRUE);
}

/*
 * read a mod item init/always block
 */  
static int32 rd_init_always(int32 iattyp)
{
 int32 iafnind, ialcnt;
 struct st_t *stp;
 struct ialst_t *ialp;

 /* AIV 07/12/12 - now supporting new SV always_* types */
 if (iattyp == ALWAYS_COMB ||  iattyp == ALWAYS_FF ||
     iattyp == ALWAYS_LATCH)
  {
   return(rd_sv_always(__toktyp));
  }

 iafnind = __cur_fnam_ind;
 ialcnt = __lin_cnt;
 iattyp = iattyp;
 __get_vtok();
 /* read statement return value determines re-synchronize */
 if ((stp = __rd_stmt()) != NULL)
  {
   ialp = (struct ialst_t *) __my_malloc(sizeof(struct ialst_t));
   ialp->iatyp = iattyp;
   /* AIV 02/19/09 - this longer needs to set __needs_thread_ctrl here */
   /* only needed for functions with %m which are now set later */
   ialp->needs_thread = FALSE;
   ialp->enterptr = NULL;
   ialp->iastp = stp;
   ialp->ia_first_ifi = iafnind;
   ialp->ia_first_lini = ialcnt;
   ialp->ia_last_ifi = __cur_fnam_ind;
   ialp->ia_last_lini = __lin_cnt;
   ialp->ialnxt = NULL;

   __save_last_mitem = (void *) __end_ialst;
   if (__end_ialst == NULL) __inst_mod->ialst = ialp;
   else __end_ialst->ialnxt = ialp;
   __end_ialst = ialp;
   return(TRUE);
  }
 /* SJM 11-08-08 - this will force a jump to resync code */
 return(FALSE);
}

/*
 * AIV 07/12/12 - read SV always_comb/always_ff/always_latch
 */  
static int32 rd_sv_always(int32 iattyp)
{
 int32 iafnind, ialcnt;
 struct st_t *stp;
 struct ialst_t *ialp;
 char s1[RECLEN];

 iafnind = __cur_fnam_ind;
 ialcnt = __lin_cnt;
 iattyp = iattyp;
 __get_vtok();

 /* only always_ff has/must have @(posedge/negedge) */
 if (iattyp == ALWAYS_FF)
  {
   __rd_always_ff = TRUE;
   if (__toktyp != AT)
    {
     __pv_ferr(3441, "always_ff must include @() sensitivity list - %s read", 
       __prt_kywrd_vtok());
     return(FALSE);
    }
   stp = __rd_stmt();
   __rd_always_ff = FALSE;
  }
 else 
  {
   /* AIV 07/16/12 - always_comb/always_latch cannot contain @ */
   if (iattyp == ALWAYS_COMB) strcpy(s1, "always_comb");
   else strcpy(s1, "always_latch");

   if (__toktyp == AT)
    {
     __pv_ferr(3442, "%s must not include @() sensitivity list - %s read", 
       __prt_kywrd_vtok(), s1);
     return(FALSE);
    }
   stp = __rd_dctrl_st_always_comb_latch();
  }

 if (stp != NULL)
  {
   ialp = (struct ialst_t *) __my_malloc(sizeof(struct ialst_t));
   ialp->iatyp = iattyp;
   /* AIV 02/19/09 - this longer needs to set __needs_thread_ctrl here */
   /* only needed for functions with %m which are now set later */
   ialp->needs_thread = FALSE;
   ialp->enterptr = NULL;
   ialp->iastp = stp;
   ialp->ia_first_ifi = iafnind;
   ialp->ia_first_lini = ialcnt;
   ialp->ia_last_ifi = __cur_fnam_ind;
   ialp->ia_last_lini = __lin_cnt;
   ialp->ialnxt = NULL;

   __save_last_mitem = (void *) __end_ialst;
   if (__end_ialst == NULL) __inst_mod->ialst = ialp;
   else __end_ialst->ialnxt = ialp;
   __end_ialst = ialp;
   return(TRUE);
  }
 return(FALSE);
}

/*
 * read a continuous assign module item
 * assign statement read and reads ending ;
 * return F if cannot sync to ending ;, if F will be sync to next mod/prim
 * list of assignments allowed here
 */
static int32 rd_contassign(void)
{
 struct expr_t *lhsndp, *rhsndp;
 struct paramlst_t *pmphdr;
 struct conta_t *cap;
 int32 first_time, sfnind, slcnt;

 /* must read drive strength and delay */
 pmphdr = NULL;
 __v0stren = __v1stren = NO_STREN;

 __get_vtok();
 if (__toktyp == LPAR)
  {
   __get_vtok();
   if (!rd_verstrens())
    {
     if (!__vskipto2_any(RPAR, SEMI)) return(FALSE);
     if (__toktyp == RPAR) { __get_vtok(); goto rd_parms; }
     return(TRUE);
    }
  }

rd_parms:
 if (__toktyp == SHARP)
  {
   if (!rd_oparamdels(&pmphdr))
    {
bad_end:
     return(__vskipto_any(SEMI));
    }
  }
 for (first_time = TRUE;;)
  {
   sfnind = __cur_fnam_ind;
   slcnt = __lin_cnt;
   /* collect lhs */
   if (!__col_lval()) goto bad_end;
   __bld_xtree(0);

   lhsndp = __root_ndp;
   __get_vtok();
   if (!__col_comsemi(-1)) goto bad_end;
   __bld_xtree(0);
   rhsndp = __root_ndp;
   /* SJM 04-11-10 - for contas in gen blks, need to move list - wire assign */
   if (first_time) __save_last_mitem = (void *) __end_ca;

   cap = add_conta(lhsndp, rhsndp, sfnind, slcnt, __cur_cntxt_gblk);
   if (first_time) cap->ca_du.pdels = pmphdr;
   else cap->ca_du.pdels = __copy_dellst(pmphdr);

   if (__v0stren != NO_STREN)
    {
     cap->ca_hasst = TRUE;
     cap->ca_stval = ((__v0stren << 3) | __v1stren) & 0x3f;
    }
   if (__toktyp == SEMI) break;
   if (__toktyp != COMMA) 
    {
     /* try to sync to next list el. if present */
     if (!__vskipto2_any(COMMA, SEMI)) return(FALSE);
     if (__toktyp == SEMI) break;
    }
   first_time = FALSE;
   __get_vtok();
  }
 return(TRUE);
}

/*
 * ROUTINES TO READ GENVAR DECLARATIONS AND GENERATE MODULE ITEMS
 */

/*
 * read simple list of genvars declarations
 *
 * know genvar keyword read - reads simple list of variables up to semi
 * at least one genvar name required 
 */
static int32 rd_genvar_decl(void)
{
 int32 save_top_sti;
 struct net_t *genvar_np, *np;
 struct expr_t *x1, *x2;
 struct sy_t *syp;
 word32 *wp;

 /* SJM 11-09-08 genvar are declared as a type of local param always */
 /* only in module top level symbol table even if declared in a gen blk */
 save_top_sti = __top_sti;
 __top_sti = 0;
 
 __get_vtok();
 for (;;)
  {
   if (__toktyp != ID)
    {
     __pv_ferr(3589, "genvar name expected - %s read", __prt_kywrd_vtok());
     /* part of delay expression may have been built */
     if (!__vskipto2_any(COMMA, SEMI))
      { __top_sti = save_top_sti; return(FALSE); } 
     if (__toktyp == COMMA) { __get_vtok(); continue; }
     break;
    }

   /* must emit warning if genvar already declared */ 
   /* SJM 11-11-08 - algorithm is to put genvars in module's symbol table */ 
   if ((syp = __get_sym(__token, __venviron[0])) != NULL) 
    {
     if (syp->sytyp != SYM_N)
      {
       __pv_ferr(3595,
        "cannot declare %s as a genvar - declared with symbol type %s at %s",
        syp->synam, __to_sytyp(__xs, syp->sytyp),
        __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
       goto nxt_genvar; 
      }
     np = syp->el.enp;
     if (np->n_isaparam)
      {
       if (np->nu.ct->p_genvar)
        {
         __finform(3151,
          "genvar %s declaration repeated (previous at %s) - ok since all genvars in module scope",
         np->nsym->synam, __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
        }
       else
        {
         __pv_ferr(3596,
          "cannot declare %s as a genvar - already declared as %s parameter at %s",
          syp->synam, __to_wtnam2(__xs, np->ntyp),
        __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
        }
      }
     else
      {
       __pv_ferr(3597,
        "cannot declare %s as a genvar - already declared as %s at %s",
        syp->synam, __to_wtnam2(__xs, np->ntyp),
        __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
      }
     goto nxt_genvar;
    }

//AIV64 11-11-08 - FIXME FOR 64 bit
   /* SJM 11-11-08 - must fill as a integer local param here */
   x1 = __bld_rng_numxpr(INTBITS - 1, 0L, WBITS);
   x2 = __bld_rng_numxpr(0L, 0L, WBITS);
   genvar_np = __add_param(__token, x1, x2, FALSE, TRUE);
   genvar_np->ntyp = N_INT;
   genvar_np->nwid = INTBITS;

   /* SJM 11-27-09 - genvar pseudo params are always rng and type declared */
   genvar_np->nu.ct->prngdecl = TRUE;
   genvar_np->nu.ct->ptypdecl = TRUE;

   genvar_np->n_signed = TRUE;
   genvar_np->nu.ct->pbase = BDEC;
   genvar_np->n_isavec = TRUE;
   genvar_np->vec_scalared = TRUE;
   __root_ndp = __alloc_newxnd();
   __set_numval(__root_ndp, 0L, 0L, 1);
   genvar_np->nu.ct->n_dels_u.d1x = __root_ndp;
   genvar_np->nu.ct->parm_srep = SR_PXPR;
   wp = (word32 *) __my_malloc(2*WRDBYTES);
   wp[0] = 0;
   wp[1] = 0;
   genvar_np->prm_nva.wp = wp;
   genvar_np->srep = SR_PNUM;

nxt_genvar:
   __get_vtok();
   if (__toktyp == SEMI) break;
   if (__toktyp != COMMA)
    {
     __pv_ferr(3590,
      "genvar declaration list ; or , separator expected - %s read",
      __prt_vtok());

     if (!__vskipto2_any(COMMA, SEMI))
      { __top_sti = save_top_sti; return(FALSE); } 
     if (__toktyp == SEMI) break;
    }
   __get_vtok();
  }
 __top_sti = save_top_sti;
 return(TRUE);
}

/*
 * read the generate mod items (within generate-endgenerate region)
 *
 * know generate token read - reads to endgenerate (or endmodule if error)
 *
 * there is no implied gen block context (sy tab)here - just rd and put on list
 *
 * implied generate block started here so any wire decls for now go into 
 * the generate implied generate form block
 *
 * SJM 11-09-08 - need to add code to handle unnamed bblk unique name build
 */
static int32 rd_gen_region_mod_items()   
{
 __in_gen_region = TRUE;
 __cur_cntxt_gblk = NULL;

 for (;;)
  {
   __get_vtok();
   if (__toktyp == ENDGENERATE) break;

   /* notice will never see wire decl as generate here - pseudo blk for top */
   if (!rd1_gen_mod_item(NULL))
    {
     if (__vskipto_modend(ENDGENERATE)) return(TRUE);
     return(FALSE);
    }
  }
 __in_gen_region = FALSE;
 return(TRUE);
}

/*
 * allocate and initialize a new gen block
 */
extern struct genblk_t *__alloc_init_new_genblk(char *blknam)
{
 struct genblk_t *gblkp;
 char s1[RECLEN];

 gblkp = (struct genblk_t *) __my_malloc(sizeof(struct genblk_t));
 gblkp->genblk_fnam_ind = __cur_fnam_ind;
 gblkp->genblk_lin_cnt = __lin_cnt;
 gblkp->gen_id = ++__mod_gen_id;
 gblkp->genv_ndx = -1;
 if (strcmp(blknam, "") == 0)
  {
   sprintf(s1, "genblk%d", gblkp->gen_id);
   gblkp->gblknam = __pv_stralloc(s1);
   gblkp->unnamed_gblk = TRUE;
  }
 else
  {
   gblkp->gblknam = __pv_stralloc(blknam);
   gblkp->unnamed_gblk = FALSE;
  }  
 gblkp->gblk_has_grefs = FALSE;
 gblkp->gblk_in_gfor = FALSE;

 /* 03-18-09 - new algorithm freezes gen blk's sym tab - expand into one */
 /* mod sym tab */
 gblkp->gblk_sytab = __alloc_symtab(TRUE);

 /* SJM 03-29-11 - also need to set new mod, genblk in */
 /* needed because top level mod gen blks need sytab par field nil */ 
 gblkp->gblk_mod_in = __inst_mod;

 /* SJM 02-16-10 - needed to add explicit gen blk ptr in symtab's */
 /* non nil used to see if sytab inside gen blk */
 gblkp->gblk_sytab->gblkofsyt = gblkp;

 gblkp->gvnp = NULL;

 /* SJM 02-16-10 - remove gblk par field - must make appear like task and */
 /* trace upward through the gblk's sym tab parent */

 gblkp->gitems = NULL;
 gblkp->last_gitem = NULL;

 gblkp->gblk_tsks = NULL;
 gblkp->end_gblk_tsk = NULL;

 gblkp->gref_gitems = NULL;
 gblkp->last_gref_gitem = NULL;

 gblkp->dfp_gitems = NULL;
 gblkp->last_dfp_gitem = NULL;
 
 return(gblkp);
}

/*
 7* alloc and initalize a generate item (no symbol table)
 */
extern struct genitem_t *__alloc_init_new_genitem(int32 typ)
{
 struct genitem_t *gip;

 /* SJM 04-04-10 - if get here, know design uses generates */
 __dsgn_uses_generate = TRUE;

 gip = (struct genitem_t *) __my_malloc(sizeof(struct genitem_t));
 gip->gityp = typ;
 gip->gi_fnam_ind = 0;
 gip->gilin_cnt = -1;
 gip->giu.gi_gforp = NULL;
 gip->gi_nam = NULL;
 gip->gened_nxt = NULL;
 gip->geninxt = NULL;
 return(gip);
}

/*
 * read gen a gen block - not a one element (no begin-end) mod item
 *
 * know begin read - reads and builds internal d.s through ending end
 * always labeled but label name optional (if not present must be generated) 
 */  
static struct genblk_t *rd1_gen_block(void)
{
 struct genblk_t *gblkp, *ret_gblkp;
 char blknam[RECLEN];

 gblkp = NULL;
 strcpy(blknam, "");
 __get_vtok();
 if (__toktyp == COLON)
  {
   __get_vtok();
   if (__toktyp != ID)
    {
     __pv_ferr(3591, "generate form labeled block name expected - %s read",
      __prt_vtok());
     if (__vskipto2_any(END, SEMI))
      {
       if (__toktyp == END) return(NULL);
       if (__toktyp == Begin) goto rd_items;
      }
     return(NULL);
    }
   strcpy(blknam, __token);
   __get_vtok();
  }
 
rd_items:
 if (strcmp(blknam, "") == 0) sprintf(blknam, "genblk%d", __mod_gen_id + 1); 
 gblkp = __alloc_init_new_genblk(blknam);
 ret_gblkp = gblkp;
 __top_sti++;
 __venviron[__top_sti] = gblkp->gblk_sytab;
 for (;;)
  {
   if (__toktyp == END) break;

   /* this allocates each gen item and links it into passed gen blk */
   if (!rd1_gen_mod_item(gblkp))
    { 
     ret_gblkp = NULL;
     if (!__vskipto_modend(END)) goto done;
     goto done;
    }
   __get_vtok();
  }
done:
 __top_sti--;
 return(ret_gblkp);
}

/*
 * read one generate module item (items only allowed in generate contexts)
 *
 * needed because generate items outside generate-endgenerate regions only
 * allow one generate item (i.e. next module item not treated (checked)
 * as generate
 *
 * SJM 11-08-08 - assuming illegal to generate multiple func or task
 * declarations - if legal, not obvious how body gen works
 *
 * SJM 05-21-09 - for item in generate region but not gen item passed nil
 */
static int32 rd1_gen_mod_item(struct genblk_t *cgblkp)
{
 int32 rv, wtyp, sav_conta_num;
 struct genitem_t *gip;
 struct dfparam_t *dfpp, *dfpp2; 
 struct conta_t *cap, *cap2;
 char typnam[IDLEN];

 /* SJM 03/20/00 - save attribute info for mod items */
 if (__attr_prefix)
  {
   __wrk_attr.attr_tok = __toktyp;
   __wrk_attr.attr_seen = TRUE;
   /* for now this is unparsed entire attr. string */
   __wrk_attr.attrnam = __pv_stralloc(__attrwrkstr);
   __wrk_attr.attr_fnind = __attr_fnam_ind;
   __wrk_attr.attrlin_cnt = __attr_lin_cnt;
  }
 else __wrk_attr.attr_seen = FALSE;

 switch(__toktyp) {
  case TEOF:
   __pv_ferr(989, "endgenerate and endmodule missing within generate region");
   return(FALSE);
  case INPUT:
  case OUTPUT:
  case INOUT:
   __pv_ferr(3583, "%s port declaration illegal in generate region\n",
    __prt_vtok());
   /* skip to ; - know if T, then the semicolon read */
   if (!__vskipto_any(SEMI)) return(FALSE);
   break;
  case EVENT:
   /* SJM 12-09-08 new algorithm - need to set global gblk before element */ 
   /* adds and expression parsing */ 
   __cur_cntxt_gblk = cgblkp;
   /* SJM 12-13-08 - this may declare var in inner gen blk scope */
   if (!rd_eventdecl(FALSE)) rv = FALSE; else rv = TRUE;
   __cur_cntxt_gblk = NULL;
   return(rv);
  case INITial:
  case ALWAYS:
   /* if inside gen blk, need to set global context for expr parsing */
   __cur_cntxt_gblk = cgblkp;
   /* SJM 12-13-08 - uses new lookup algorithm - first local scopes (maybe */
   /* from labeled block) then gen blk scopes then mod level symbol table */
   rv = rd_init_always(__toktyp);
   __cur_cntxt_gblk = NULL;
   if (!rv) return(FALSE);

   /* SJM 05-21-09 - non generate init/always can be between in generate */
   /* keyword region, but it is not gen item so just return - works because */
   /* will be correctly on end of inst mod's ialst */
   /* SJM 05-21-09 - can just forget about save last mitem because will be */
   /* set next time gen item (or non gen item) read */
   if (cgblkp == NULL) break;

   /* SJM 11-09-08 - if glb generate cntxt (symbol tab) move to gen item lst */ 
   /* if no context, then ignore as gen and treat as normal */
   gip = __alloc_init_new_genitem(GI_INITALW);
   /* DBG remove -- */
   if (__end_ialst == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   gip->giu.gi_ialp = __end_ialst;

   gip->gi_fnam_ind = gip->giu.gi_ialp->ia_first_ifi;
   gip->gilin_cnt = gip->giu.gi_ialp->ia_first_lini;

   if (cgblkp->last_gitem == NULL) cgblkp->gitems = gip;
   else cgblkp->last_gitem->geninxt = gip;
   cgblkp->last_gitem = gip;

   /* must remove from end of ialst too */
   __end_ialst = (struct ialst_t *) __save_last_mitem;  
   /* SJM 11-10-08 - if first one taken off, end of mod's list nil */
   /* SJM 11-11-08 if this was first one added - must fix mod's ptr */
   if (__end_ialst == NULL) __inst_mod->ialst = NULL;
   else __end_ialst->ialnxt = NULL;
   break;
  case ASSIGN:
   /* if inside gen blk, need to set global context to add to sym tab */
   __cur_cntxt_gblk = cgblkp;
   /* SJM 12-13-08 - if gen blk context, adds virtual conta symbol to */
   /* current enclosing gen blk scope so if not chosen to add to src */
   /* will just not exist - for exprs looks in enclosing gen blk scopes */
   /* then module symbol table - in gen blks no forward decls */
   /* 01-20-09 - can be good sync but other syntax error */
   sav_conta_num = __conta_num;
   rv = rd_contassign();
   __cur_cntxt_gblk = NULL;
   if (!rv) return(FALSE);
   /* SJM 01-20-09 if can sync but other error no conta added */
   if (sav_conta_num == __conta_num) return(FALSE);

   /* SJM 05-21-09 - if only in generate region do not alloc gen item */ 
   if (cgblkp == NULL) break;

   /* SJM 11-09-08 - if glb generate cntxt (symbol tab) move to gen item lst */
   /* if no context, then ignore as gen and treat as normal */

   /* SJM 05-13-10 contas can be comma separated list save mitem points */
   /* to one before start of list (or one before the one) */
   cap = (struct conta_t *) (struct conta_t *) __save_last_mitem;
   if (cap == NULL) cap = __inst_mod->mcas;
   else cap = cap->pbcau.canxt;
   for (; cap != NULL; cap = cap2)
    {
     cap2 = cap->pbcau.canxt;

     gip = __alloc_init_new_genitem(GI_CONTA);
     gip->giu.gi_cap = cap;
     
     /* have a dummy local constructed sym for ca so just use loc */
     gip->gi_fnam_ind = cap->casym->syfnam_ind;
     gip->gilin_cnt = cap->casym->sylin_cnt;

     gip->giu.gi_cap->pbcau.canxt = NULL;
     if (cgblkp->last_gitem == NULL) cgblkp->gitems = gip;
     else cgblkp->last_gitem->geninxt = gip;
     cgblkp->last_gitem = gip;
    }

   /* SJM 04-11-10 - this now sets end to start of possible conta list */
   /* must remove from end of ca lst too */
   __end_ca = (struct conta_t *) __save_last_mitem;  

   /* SJM 11-11-08 if this was first one added - must fix mod's ptr */
   if (__end_ca == NULL) __inst_mod->mcas = NULL;
   else __end_ca->pbcau.canxt = NULL;
  
   break;
  case PARAMETER: case LOCALPARAM:
   __pv_ferr(3584, "%s declaration illegal in generate region\n",
    __prt_vtok());
   /* skip to ; */
   if (!__vskipto_any(SEMI)) return(FALSE);
   break;
  case DEFPARAM:
   /* SJM 04-07-10 - back to putting defparams in the gen blk */
   /* new code moves gen blks with fixed up names in exprs into mod after */
   /* a pass of v fx (i.e. before 2*/ 

   /* if inside gen blk, need to set global context to add to sym tab */
   __cur_cntxt_gblk = cgblkp;
   __rding_defparam = TRUE;
   rv = rd_dfparam_stmt();
   __rding_defparam = FALSE;
   __cur_cntxt_gblk = NULL;
   if (!rv) return(FALSE);

   /* SJM 05-21-09 - if only in generate region do not alloc gen item */ 
   if (cgblkp == NULL)
    { 
     /* SJM 05-21-09 - if only in generate region do not alloc gen item */ 
     if (__pv_err_cnt == 0) break;

     /* even if in gen block gen item, may get here on sync problem */
     __pv_ferr(3588, "while reading gen defparam - end sync failure"); 
     return(FALSE);
    }

   /* SJM 11-09-08 - if glb generate cntxt (symbol tab) move to gen item lst */ 
   /* if no context, then was ignore as gen and treated as normal above */
   /* SJM 04-07-10 - know at least one dfp form ready - possibly list */

   /* SJM 05-13-10 defps can be comma separated list, save mitem points */
   /* to one before start of list (or one before the one) */
   dfpp = (struct dfparam_t *) __save_last_mitem;
   if (dfpp == NULL) dfpp = __inst_mod->mdfps;
   else dfpp = dfpp->dfpnxt;
   for (; dfpp != NULL; dfpp = dfpp2)
    {
     dfpp2 = dfpp->dfpnxt;

     gip = __alloc_init_new_genitem(GI_DFPARM);
     gip->giu.gi_dfp = dfpp;
     gip->giu.gi_dfp->dfpnxt = NULL;

     /* SJM 04-07-10 - putting back defparams in gen blks as gen items */
     gip->giu.gi_dfp->dfp_in_gen = TRUE;
     gip->giu.gi_dfp->dfp_gblk_in = cgblkp; 
     if (dfpp->dfpxlhs->optyp == GLBREF)
      {
       gip->giu.gi_dfp->dfpxlhs->ru.grp->gr_defparam = TRUE;
      }
     gip->gi_fnam_ind = dfpp->dfpfnam_ind;
     gip->gilin_cnt = dfpp->dfplin_cnt;

     if (cgblkp->last_dfp_gitem == NULL) cgblkp->dfp_gitems = gip;
     else cgblkp->last_dfp_gitem->geninxt = gip;
     cgblkp->last_dfp_gitem = gip;
    }

   /* must remove from end of expected in mod dfps*/
   __end_dfp = (struct dfparam_t *) __save_last_mitem;  
   /* SJM 04-07-10 if this was first one added - must fix mod's ptr */
   if (__end_dfp == NULL) __inst_mod->mdfps = NULL;
   else __end_dfp->dfpnxt = NULL;

   break;
  case SPECIFY:
   __pv_ferr(3587, "specify block illegal in generate region");
   /* skip to ; */
   /* SJM 11-08-08 - think need better specify section re-syncing */
   if (!__vskipto_any(ENDSPECIFY)) return(FALSE);
   break;
  case TASK:
   /* SJM 11-08-08 - task declarations can only appear outside gen for */
   /* blocks, therefore no different than normal task/func decl - no genvar */
   /* local params - must catch here */

   /* if inside gen blk, need to set global context to add to sym tab */
   __cur_cntxt_gblk = cgblkp;
   __cur_declobj = TASK;

   /* SJM 12-13-08 - task/funcs can be declared in non for loop generate */
   /* contexts - normal decl except in body stmt can find vars after local */
   /* scopes in possibly nested gen blk scopes then mod level sym table */
   rv = rd_task();
   __cur_declobj = MODULE;
   __cur_cntxt_gblk = NULL;
   if (!rv) return(FALSE);
   break;
  case FUNCTION:
   /* if inside gen blk, need to set global context to add to sym tab */
   __cur_cntxt_gblk = cgblkp;
   __cur_declobj = TASK;

   rv = rd_func();
   __cur_declobj = MODULE;
   __cur_cntxt_gblk = NULL;
   if (!rv) return(FALSE);
   break;
  case ENDMODULE:
   /* save end so can put in module's end source range fields */
   __inst_mod->mod_last_lini = __lin_cnt;
   __inst_mod->mod_last_ifi = __cur_fnam_ind;
   /* SJM 11-08-08 - think extra check for wrong ;, can't be used here */
   /* SJM 05-09-09 - can get here on sequencing problem even if no generate */
   if (__gen_fnam_ind != -1)   
    {
     __pv_ferr(3587,
      "endmodule token read before endgenerate - generate at %s",
      __bld_lineloc(__xs, __cur_fnam_ind, __lin_cnt));
    }
   else
    {
     __pv_ferr(3587, "endmodule token read before endgenerate - gen block never ended?");
    }
   return(FALSE);
  case ENDPRIMITIVE:
   /* but assume still in sync */
   __pv_ferr(990, "generate region can not end with endprimitive");
   return(FALSE);
  case GENVAR:
   if (!rd_genvar_decl()) return(FALSE);
   break;
  case FOR:
   /* SJM 11-08-08 - gen for/case/if can be outside generate region */
   if (!rd_gen_for(cgblkp)) return(FALSE);
   break;
  case FOREACH:
   if (!rd_gen_foreach(cgblkp)) return(FALSE);
   break;
  case CASE:
   if (!rd_gen_case(cgblkp)) return(FALSE);
   break;
  case IF:
   if (!rd_gen_if(cgblkp)) return(FALSE);
   break;
  case Begin:
   /* SJM 05-17-11 - need to allow begin-end gen items - treat as T if */
   if (!rd_gen_begin(cgblkp)) return(FALSE);
   break;
  case IMPORT:
  case EXPORT:
   if (!rd_dpi_declaration()) return(FALSE);
   break;
  case GENERATE:
   __pv_ferr(3581,
    "generate module item can not be nested - previous at %s - ignored",
    __bld_lineloc(__xs, __gen_fnam_ind, __gen_lin_cnt));
   __gen_fnam_ind = __cur_fnam_ind;
   __gen_lin_cnt = __lin_cnt;
   break;
  case ENDGENERATE:
   return(TRUE);
  default:
   /* SJM 05-21-09 - here if gblkp nil (just in generate area) decled in */
   /* right symbol table */
   if ((wtyp = __fr_wtnam(__toktyp)) != -1)
    {
     /* if inside gen blk, need to set global context to add to sym tab */
     __cur_cntxt_gblk = cgblkp;

     /* false here means out of sync - must skip rest of module */
     /* if T will have skipped to semi */
     /* SJM 12-13-08 - this may declare var in inner gen blk scope */
     rv = rd_vardecl((word32) wtyp);
     /* AIV 05/08/09 - moved the code to add nets declared generate blocks  */
     /* it is now in rd_vardecl to handle the 'reg var1, var2;' case */
     __cur_cntxt_gblk = NULL;
     if (!rv) return(FALSE);

     /* needed to add attribute to every net in list - can now reset */
     __wrk_attr.attr_seen = FALSE;

     /* SJM 11-10-08 - declaring wire as usual but add ing to gen item list */
     return(rv);
    }
   /* must be instance (udp, gate, module instantiation) */
   if (__toktyp != ID)
    {
     __pv_ferr(991, "module type, gate or udp name expected - %s read",
      __prt_kywrd_vtok());
     /* can only sync to ; here - else need names to decl. */
     if (!__vskipto_any(SEMI)) return(FALSE);
     return(FALSE);
    }
   strcpy(typnam, __token);

   /* if inside gen blk, need to set global context to add to sym tab */
   /* SJM 12-13-08 put inst name in current gen blk scope, only check */
   /* there and then add to smallest containing gen blk symbol table */
   __cur_cntxt_gblk = cgblkp;
   /* read inst (cell - can be either inst or gate) needs symbol tab cntxt */
   rv = rd_inst(typnam);
   __cur_cntxt_gblk = NULL;
   if (!rv) return(FALSE);
  
   /* needed to add attr to every instance, now can reset attr seen */ 
   __wrk_attr.attr_seen = FALSE;
  }
 return(TRUE);
}

/*
 * read gen for loop construct
 *
 * for read and read either the one module item or multiple items within
 * labeled begin-end (if no label, implied label needed) 
//SJM 12-13-08 FIXME?? - order of setting of gen for vars wrong - can be unset
 */
static int32 rd_gen_for(struct genblk_t *cgblkp)
{
 int32 slcnt, sfnind, sav_in_gen_region, styp;
 struct gen_for_t *genforp;
 struct st_t *inita, *inca;
 struct expr_t *lhsndp, *rhsndp, *stopndp;
 struct genitem_t *gip;
 struct genblk_t *gblkp;

 sav_in_gen_region = __in_gen_region;
 __in_gen_region = TRUE;
 /* if have context - add to that symbol table */
// SJM 11-09-08 WRONG!!! - think symbol tables wrong - how fix?
// need to declare for used but not declared in context symbol table - how?

 /* SJM 02-09-09 - on error inita and inca probably nil - problem is that */
 /* if can resync from error try to read as much as possible */
 inita = NULL;
 inca = NULL;
 stopndp = NULL;

 /* SJM 11-08-08 the for (...) is normal for statement code */
 /* must read expressions separately for assigns */
 /* first build initialization assign */
 slcnt = __lin_cnt;
 sfnind = __cur_fnam_ind;
 __get_vtok();
 if (__toktyp != LPAR)
  {
   __pv_ferr(3592, "for statement left parenthesis expected - %s read",
    __prt_vtok());
bad_gen_for:
   if (__vskipto2_any(RPAR, SEMI))
    {
     if (__toktyp == SEMI) { inita = __alloc_stmt(S_NULL); goto bldtrmx; }
    }
//SJM 11-08-08 - why does stmt for try to read a statement here?
   __in_gen_region = sav_in_gen_region;
   
   return(FALSE);
  }
 __get_vtok();
 /* collect lhs to = */
 if (!__col_lval()) goto bad_gen_for;
 __bld_xtree(0);
 lhsndp = __root_ndp;
 __get_vtok();
 if (!__col_comsemi(-1)) goto bad_gen_for; 
 if (__toktyp != SEMI)
  {
   __pv_ferr(3593,
    "generate for form initial assignment ending semicolon expected - %s read",
    __prt_vtok());
   __vskipto_any(RPAR);
   goto rd_gen_for_item;
  }

 __bld_xtree(0);
 rhsndp = __root_ndp;
 /* build proc assign */
 inita = __alloc_stmt(S_FORASSGN);
 inita->st.spra.lhsx = lhsndp;
 inita->st.spra.rhsx = rhsndp;

 /* build termination expression */
bldtrmx:
 __get_vtok();
 if (!__col_comsemi(-1))
  {
   if (__vskipto2_any(RPAR, SEMI))
    {
     if (__toktyp == SEMI) { __set_xtab_errval(); goto bldcondx; } 
    }
   goto rd_gen_for_item;
  }
 if (__toktyp != SEMI)
  {
   __pv_ferr(3594,
    "generate for form termination expression ending semicolon expected - %s read",
    __prt_vtok());
   __vskipto_any(RPAR);
   goto rd_gen_for_item;
  }

bldcondx:
 __bld_xtree(0);
 stopndp = __root_ndp;

 /* collect assignment ending in ) */
 __get_vtok();
 /* collect lhs to = - this can only end with = */
 if (!__col_lval())
  {
bad2_for:
   if (__vskipto_any(RPAR))
    { 
     inca = __alloc_stmt(S_NULL);
     goto rd_gen_for_item;
    }
   goto rd_gen_for_item;
  }
   
 __bld_xtree(0);
 lhsndp = __root_ndp;
 /* AIV 09/24/10 - can now have ++/-- */
 if (lhsndp->optyp == INC || lhsndp->optyp == DEC)
  {
   if (!__col_parenexpr(-1, FALSE, FALSE)) goto bad2_for;
   if (lhsndp->optyp == INC) styp = S_INC;
   else styp = S_DEC;
   inca = __alloc_stmt(styp);
   inca->st.spra.lhsx = lhsndp;
   inca->st.spra.rhsx = NULL;
  }
 else
  {
   __get_vtok();
   if (!__col_parenexpr(-1, FALSE, FALSE)) goto bad2_for;
   __bld_xtree(0);
   rhsndp = __root_ndp;

   /* build proc assign */
   inca = __alloc_stmt(S_PROCA);
   inca->st.spra.lhsx = lhsndp;
   inca->st.spra.rhsx = rhsndp;
  }

rd_gen_for_item:

 /* alloc the gen for d.s. */
 genforp = (struct gen_for_t *) __my_malloc(sizeof(struct gen_for_t));
 genforp->ngenblks = -1;

 genforp->gforassgn = inita;
 genforp->gfortermx = stopndp;
 genforp->gforinc = inca;
 genforp->gentab = NULL;

 gip = __alloc_init_new_genitem(GI_GFOR);
 gip->giu.gi_gforp = genforp;
 gip->gilin_cnt = slcnt;
 gip->gi_fnam_ind = sfnind;

 /* if gen blk context, add to that list else to mod's gen item list */
 if (cgblkp != NULL)
  {
   if (cgblkp->last_gitem == NULL) cgblkp->gitems = gip;
   else cgblkp->last_gitem->geninxt = gip;
   cgblkp->last_gitem = gip;
  } 
 else
  {
   if (__last_gip == NULL) __inst_mod->mgenitems = gip;
   else __last_gip->geninxt = gip;
   __last_gip = gip;
  }

 __get_vtok(); 

 if ((gblkp = rd1_nd_blk_gen_body()) == NULL) return(FALSE);
 genforp->src_gforblkp = gblkp;
 gblkp->gblk_in_gfor = TRUE;

 /* SJM 02-16-10 must link in gen blk sym tab parent symtab */
 /* if this gen blk is not nested inside another gen blk, parent is mod sytab */
 /* gblkp is the gen blk current reading in */
 /* DBG remove -- */
 if (gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (cgblkp == NULL) gblkp->gblk_sytab->sytpar = __inst_mod->msymtab;
 else gblkp->gblk_sytab->sytpar = cgblkp->gblk_sytab;

 __in_gen_region = sav_in_gen_region;
 return(TRUE);
}

/*
 * AIV SV
 */
static int32 rd_gen_foreach(struct genblk_t *cgblkp)
{
 //AIV WRITEME probably not true
 __pv_ferr(4849,
    "generate foreach statement not yet supported in generate blocks");
 return(FALSE);
}

/*
 * read a gen statement where know needs its own symbol table (genblk)
 * even if only one statement (no labeled or unlabled block)
 */ 
static struct genblk_t *rd1_nd_blk_gen_body(void)
{
 int32 blkno;
 struct genblk_t *gblkp;
 char blknam[RECLEN];

 /* SJM 04-09-11 - gen body can also be empty semi - see LRM */
 if (__toktyp == SEMI)
  {
   blkno = __mod_gen_id + 1;
   sprintf(blknam, "genblk%d", blkno);
   gblkp = __alloc_init_new_genblk(blknam);
   return(gblkp);
  }

 if (__toktyp == Begin) 
  {
   if ((gblkp = rd1_gen_block()) == NULL) return(NULL);
  }
 else
  {
   blkno = __mod_gen_id + 1;
   sprintf(blknam, "genblk%d", blkno);
   gblkp = __alloc_init_new_genblk(blknam);
   if (!rd1_gen_mod_item(gblkp)) return(NULL);
  }
 return(gblkp);
}

/*
 * read the gen if conditional construct
 *
 * if read - read either one module item or list if begin-end (always labeled)
 * then optional else that may also have labeled begin-end
 *
 * SJM 11-08-08 for chained if-then-elses - the 2nd if inside the else clause
 */
static int32 rd_gen_if(struct genblk_t *cgblkp)
{
 int32 sav_in_gen_region;
 struct expr_t *condx;
 struct genblk_t *gblkp;
 struct genitem_t *gip;
 struct gen_if_t *genif;

 sav_in_gen_region = __in_gen_region;
 __in_gen_region = TRUE;
 gip = __alloc_init_new_genitem(GI_GIF);
 
 /* if gen blk context, add to that list else to mod's gen item list */
 if (cgblkp != NULL)
  {
   if (cgblkp->last_gitem == NULL) cgblkp->gitems = gip;
   else cgblkp->last_gitem->geninxt = gip;
   cgblkp->last_gitem = gip;
  } 
 else
  {
   if (__last_gip == NULL) __inst_mod->mgenitems = gip;
   else __last_gip->geninxt = gip;
   __last_gip = gip;
  }
 genif = (struct gen_if_t *) __my_malloc(sizeof(struct gen_if_t));
 genif->no_if_beg = FALSE;
 genif->ngenblks = -1;
 genif->condx = NULL;
 genif->src_then_gblkp = NULL;
 genif->src_else_gblkp = NULL;
 genif->gentab = NULL;

 gip->giu.gi_gifp = genif;
 gip->gi_fnam_ind = __cur_fnam_ind;
 gip->gilin_cnt = __lin_cnt;

 condx = NULL;
 __get_vtok();
 if (__toktyp != LPAR)
  {
bad_ifx:
   if (__vskipto2_any(RPAR, ELSE))
    {
     if (__toktyp == RPAR) goto rd_if;
     if (__toktyp == ELSE) goto rd_else;
    }
   __in_gen_region = sav_in_gen_region;
   return(FALSE);
  }
 __get_vtok();
 if (!__col_parenexpr(-1, FALSE, FALSE)) goto bad_ifx;
 /* SJM 12-09-08 since const expr and no param defines in gen blks, */
 /* do not need to access possible gblk's symbol table */
 __bld_xtree(0);
 condx = __root_ndp;
 genif->condx = condx;
rd_if:
 __get_vtok(); 
 if ((gblkp = rd1_nd_blk_gen_body()) == NULL)
  {
   __in_gen_region = sav_in_gen_region;
   return(FALSE);
  }
 genif->src_then_gblkp = gblkp;

 /* SJM 02-16-10 must link in gen blk sym tab parent symtab */
 /* if this gen blk is not nested inside another gen blk, parent is mod sytab */
 /* gblkp is the gen blk current reading in */
 /* DBG remove -- */
 if (gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (cgblkp == NULL) gblkp->gblk_sytab->sytpar = __inst_mod->msymtab;
 else gblkp->gblk_sytab->sytpar = cgblkp->gblk_sytab;

 __get_vtok();
 if (__toktyp != ELSE)
  {
   __unget_vtok();
   __in_gen_region = sav_in_gen_region;
   return(TRUE);
  }

rd_else:
 __get_vtok();
 if ((gblkp = rd1_nd_blk_gen_body()) == NULL)
  {
   __in_gen_region = sav_in_gen_region;
   return(FALSE);
  }
 genif->src_else_gblkp = gblkp;

 /* SJM 02-16-10 must link in gen blk sym tab parent symtab */
 /* if this gen blk is not nested inside another gen blk, parent is mod sytab */
 /* gblkp is the gen blk current reading in */
 /* DBG remove -- */
 if (gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (cgblkp == NULL) gblkp->gblk_sytab->sytpar = __inst_mod->msymtab;
 else gblkp->gblk_sytab->sytpar = cgblkp->gblk_sytab;

 __in_gen_region = sav_in_gen_region;
 return(TRUE);
}

/*
 * read the gen begin end (no if - but faked as gen if with if (1) implied
 *
 * begin read 
 * SJM 05-18-11 - must support begin-end genblks without if, not in LRM but
 * was so other simulators allow
 */
static int32 rd_gen_begin(struct genblk_t *cgblkp)
{
 int32 sav_in_gen_region;
 struct expr_t *condx;
 struct genblk_t *gblkp;
 struct genitem_t *gip;
 struct gen_if_t *genif;

 sav_in_gen_region = __in_gen_region;
 __in_gen_region = TRUE;
 gip = __alloc_init_new_genitem(GI_GIF);
 
 /* if gen blk context, add to that list else to mod's gen item list */
 if (cgblkp != NULL)
  {
   if (cgblkp->last_gitem == NULL) cgblkp->gitems = gip;
   else cgblkp->last_gitem->geninxt = gip;
   cgblkp->last_gitem = gip;
  } 
 else
  {
   if (__last_gip == NULL) __inst_mod->mgenitems = gip;
   else __last_gip->geninxt = gip;
   __last_gip = gip;
  }
 genif = (struct gen_if_t *) __my_malloc(sizeof(struct gen_if_t));
 genif->no_if_beg = TRUE;
 genif->ngenblks = -1;
 genif->condx = NULL;
 genif->src_then_gblkp = NULL;
 genif->src_else_gblkp = NULL;
 genif->gentab = NULL;

 gip->giu.gi_gifp = genif;
 gip->gi_fnam_ind = __cur_fnam_ind;
 gip->gilin_cnt = __lin_cnt;

 /* need 32 bit 1 (T) */ 
 __last_xtk = 0;
 __init_xnd(__exprtab[0]);
 __set_numval(__exprtab[0], 1L, 0L, WBITS);
 __bld_xtree(0);
 condx = __root_ndp;
 genif->condx = condx;

 /* SJM 05-19-11 - rd a gen body assumes current token is the begin */ 
 if ((gblkp = rd1_nd_blk_gen_body()) == NULL)
  {
   __in_gen_region = sav_in_gen_region;
   return(FALSE);
  }
 genif->src_then_gblkp = gblkp;

 /* SJM 02-16-10 must link in gen blk sym tab parent symtab */
 /* if this gen blk is not nested inside another gen blk, parent is mod sytab */
 /* gblkp is the gen blk current reading in */
 /* DBG remove -- */
 if (gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (cgblkp == NULL) gblkp->gblk_sytab->sytpar = __inst_mod->msymtab;
 else gblkp->gblk_sytab->sytpar = cgblkp->gblk_sytab;

 __in_gen_region = sav_in_gen_region;
 return(TRUE);
}

/*
 * read the gen case conditional construct
 *  
 * case keyword read and reads endcase
 */
static int32 rd_gen_case(struct genblk_t *cgblkp)
{
 int32 seen_dflt, sav_in_gen_region, rv;
 struct expr_t *condx;
 struct exprlst_t *csixhdr, *xplp, *last_xplp;
 struct genitem_t *gip;
 struct gen_csitem_t *gencsitem, *last_gcsip;
 struct gen_case_t *gencase;
 struct genblk_t *gblkp;

 sav_in_gen_region = __in_gen_region;
 __in_gen_region = TRUE;
 gip = __alloc_init_new_genitem(GI_GCASE);
 /* if gen blk context, add to that list else to mod's gen item list */
 if (cgblkp != NULL)
  {
   if (cgblkp->last_gitem == NULL) cgblkp->gitems = gip;
   else cgblkp->last_gitem->geninxt = gip;
   cgblkp->last_gitem = gip;
  } 
 else
  {
   if (__last_gip == NULL) __inst_mod->mgenitems = gip;
   else __last_gip->geninxt = gip;
   __last_gip = gip;
  }
 gencase = (struct gen_case_t *) __my_malloc(sizeof(struct gen_case_t));
 gencase->ngenblks = -1;

 gencase->csx = NULL;
 gencase->gcsitems = NULL;
 gencase->gentab = NULL;
 gip->giu.gi_gcasp = gencase;
 gip->gi_fnam_ind = __cur_fnam_ind;
 gip->gilin_cnt = __lin_cnt;

 last_gcsip = NULL;
 condx = NULL;
 __get_vtok();
 if (__toktyp != LPAR)
  {
   __pv_ferr(3592,
    "generate case form selection expression left parenthesis expected - %s read",
    __prt_vtok());
bad_csx:
   if (__vskipto2_any(RPAR, ENDCASE))
    {
     if (__toktyp == ENDCASE) return(TRUE);
     __set_xtab_errval();
     goto bld_csx;
    }
   __in_gen_region = sav_in_gen_region;
   return(FALSE);
  }

 __get_vtok();
 /* this reads the ending ) */
 if (!__col_parenexpr(-1, FALSE, FALSE)) goto bad_csx;
bld_csx:
 __bld_xtree(0);
 condx = __root_ndp;
 gencase->csx = condx;
 seen_dflt = FALSE;
 for (;;)
  {
   __get_vtok();
   switch (__toktyp) {
    case ENDCASE: return(TRUE);
    case DEFAULT:
     /* SJM 11-08-08 - default clause need not be last */
     __get_vtok();
     if (__toktyp == COLON) __get_vtok();
     if (seen_dflt)
      __pv_ferr(3593,
       "more than one generate case form default item not permitted");
     if ((gblkp = rd1_nd_blk_gen_body()) == NULL)
      {
       /* return T/F here is info for error recovery */
       if (!__vskipto_any(ENDCASE)) rv = FALSE;
       else rv = TRUE;
       goto done;
      }
     gencsitem = (struct gen_csitem_t *)
      __my_malloc(sizeof(struct gen_csitem_t));
     gencsitem->gdflt_i = TRUE;
     gencsitem->csixlst = NULL;
     gencsitem->gen_csiblkp = gblkp;
     gencsitem->gcsinxt = NULL; 

     /* SJM 02-16-10 must link in gen blk sym tab parent symtab */
     /* if this gen blk not nested inside another gen blk, par is mod sytab */
     /* gblkp is the gen blk current reading in */
     /* DBG remove -- */
     if (gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     if (cgblkp == NULL) gblkp->gblk_sytab->sytpar = __inst_mod->msymtab;
     else gblkp->gblk_sytab->sytpar = cgblkp->gblk_sytab;

     /* know default goes on front */
     gencsitem->gcsinxt = gencase->gcsitems;
     gencase->gcsitems = gencsitem;
     seen_dflt = TRUE;
     continue;
    default:
     /* expr. collection will fail if not required at least one expr. */
     for (last_xplp = NULL, csixhdr = NULL;;)
      {
more_xprs:
       if (!__col_caseexpr())
        {
         if (__vskipto3_any(COLON, SEMI, COMMA))
          {
           if (__toktyp == SEMI) goto nxt_case;
           __set_xtab_errval();
          }
         else return(FALSE);
        }
       __bld_xtree(0);
       /* allocate and link in the expression list item */
       xplp = __alloc_xprlst();
       xplp->xp = __root_ndp;
       if (last_xplp == NULL) csixhdr = xplp; else last_xplp->xpnxt = xplp;
       last_xplp = xplp;

       if (__toktyp != COMMA) break;
       __get_vtok();
      }
     if (__toktyp != COLON)
      {
       __pv_ferr(3594,
        "generate case form expression list colon expected - %s read",
        __prt_vtok());
       if (__vskipto3_any(COLON, SEMI, COMMA))
        {
         if (__toktyp == SEMI) continue;
         if (__toktyp == COLON) goto do_cstmt;
         goto more_xprs;
        }
       else { rv = FALSE; goto done; }
      }
do_cstmt:
     __get_vtok();
     /* ; null module body item ok here */
//SJM? 11-09-08 - is it true for gen cases? 
     if (__toktyp == CASE) continue; 

     if ((gblkp = rd1_nd_blk_gen_body()) == NULL)
      { rv = FALSE; goto done; } 

     gencsitem = (struct gen_csitem_t *)
      __my_malloc(sizeof(struct gen_csitem_t));
     gencsitem->gdflt_i = FALSE;
     gencsitem->csixlst = csixhdr;
     gencsitem->gen_csiblkp = gblkp;
     /* SJM 03-07-09 - was not setting nxt field to nil */
     gencsitem->gcsinxt = NULL;

     /* SJM 02-16-10 must link in gen blk sym tab parent symtab */
     /* if this gen blk not nested inside another gen blk, par is mod sytab */
     /* gblkp is the gen blk current reading in */
     /* DBG remove -- */
     if (gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     if (cgblkp == NULL) gblkp->gblk_sytab->sytpar = __inst_mod->msymtab;
     else gblkp->gblk_sytab->sytpar = cgblkp->gblk_sytab;

     /* 11-11-08 - was not handling last gcsip nil right */
     if (last_gcsip == NULL) gencase->gcsitems = gencsitem;
     else last_gcsip->gcsinxt = gencsitem;
     last_gcsip = gencsitem;
    }
nxt_case:;
  }
done:
 __in_gen_region = sav_in_gen_region;
 return(rv);
}

/*
 * MODULE DECLARATION ROUTINES
 */

/*
 * process an I/O or wire declaration
 * mostly sets the iotyp field
 * I/O decl. does not declare symbol even though wire decl. not required
 */
static int32 rd_iodecl(word32 typ)
{
 int32 first_time, ttyp, has_attr, is_signed, num_signeds, is_complete, wtyp;
 struct sy_t *syp;
 struct net_t *np;
 struct expr_t *x1, *x2, *ox1, *ox2;
 char s1[RECLEN];

 syp = NULL;
 np = NULL;
 wtyp = -1;
 is_complete = FALSE;
 /* vectored or scalared keywords only appear on wire decls */
 __get_vtok();
 num_signeds = 0;
 is_signed = FALSE;
 if (__toktyp == SIGNED)
  {
   num_signeds++;
   is_signed = TRUE;
   __get_vtok();
  }
 /* SJM 07-30-10 - new SV semantics allows unsigned keyword on integer too */
 else if (__toktyp == UNSIGNED)
  {
   num_signeds++;
   is_signed = FALSE;
   __get_vtok();
  }

 /* AIV 07/20/04 port decl can now contain net type making it complete  */
 if ((wtyp = __fr_wtnam(__toktyp)) != -1)
  {
    /* if complete set the flag set the type */
    is_complete = TRUE;
    __get_vtok();
    /* must check for sign again */
    if (__toktyp == SIGNED)
     {
      is_signed = TRUE;
      num_signeds++;
      __get_vtok();
     }
    if (__toktyp == UNSIGNED)
     {
      is_signed = FALSE;
      num_signeds++;
      __get_vtok();
     }
   }
  /* type defaults to reg if undefined */
  else wtyp = N_REG;

  if (num_signeds > 0)
   {
    if (wtyp == N_EVENT || __is_non_int_typ(wtyp))
     {
      /* types for which signed keyword illegal always signed */
      is_signed = TRUE;
      __pv_ferr(3423,
       "%s port declaration signed keyword illegal for type %s",
       __to_ptnam(__xs, typ), __to_wtnam2(s1, wtyp));
     }
   }
  if (num_signeds > 1)
   {
    __pv_ferr(3425,
     "%s port declaration illegal - only one signed/unsigned allowed",
     __to_ptnam(s1, typ));
   }

 /* even if error if 1 past ending ] continue */
 if (!rd_decl_rng(&ox1, &ox2, FALSE))
  {
   /* ignore decl but continue with mod. item */
   if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
   if (__toktyp == SEMI) return(TRUE);
   __get_vtok();
  }
 if (ox1 != NULL)
  {
   if (!__is_int_vec_typ(wtyp) && wtyp >= NONWIRE_ST)
    {
     /* AIV 08/17/11 - this was missing the second format %s */
     __pv_ferr(1002,
      "%s port declaration illegal - vector range illegal for type %s",
      __to_ptnam(__xs, typ), __to_wtnam2(s1, wtyp));
     ox1 = ox2 = NULL;
    }
  } 

 /* use local has attr flag so can turn glb seen of before return */
 if (__wrk_attr.attr_seen) { has_attr = TRUE; __wrk_attr.attr_seen = FALSE; }
 else has_attr = FALSE;
 x1 = x2 = NULL;
 for (first_time = TRUE;;)
  {
   if (__toktyp != ID)
    {
     __pv_ferr(992, "%s port name expected - %s read", __to_ptnam(s1, typ),
      __prt_kywrd_vtok());
     /* need token and symbol and cannot parse */
     return(__vskipto_any(SEMI));
    }

   /* any port decl illegal if hdr list of port form used */
   if (__lofp_port_decls)
    {
     __pv_ferr(3421,
      "%s declaration of \"%s\" illegal - module uses list of ports declaration form",
     __to_ptnam(s1, typ), __prt_kywrd_vtok());
     goto nxt_port; 
    }

   /* 3 ways to not be in I/O port header list */
   /* know only one symbol level here */
   /* also know must be defined since added when header read */
   if ((syp = __get_sym_env(__token)) == NULL)
    {
not_a_port:
     __pv_ferr(993,
     "%s declaration of \"%s\" illegal - not in module header list of ports",
      __to_ptnam(s1, typ), __token);
     goto nxt_port;
    }
   if (syp->sytyp != SYM_N) goto not_a_port;
   np = syp->el.enp;

   /* SJM 10/02/03 - signed can be turned on either in port or wire decl */ 
   if (is_signed) np->n_signed = TRUE;

   /* when module header list of ports read, port set to IO_UNKN */
   if (np->iotyp == NON_IO) goto not_a_port;

   /* header port changed when I/O port decl. seen */
   if (np->nu.ct->n_iotypknown)
    {
     __pv_ferr(994, "I/O port %s previously declared as %s", __token,
      __to_ptnam(s1, np->iotyp));
    }
   else
    {
     np->iotyp = typ;
     np->nu.ct->n_iotypknown = TRUE;
    }

   /* if saw an (* *) attribute for module item token, seen on */
   if (has_attr)
    {
     if (typ == IO_IN) ttyp = INPUT; else if (typ == IO_OUT) ttyp = OUTPUT;
     else ttyp = INOUT;

     /* this add to net's attr list on end if also net decl first */
     add_net_attr(np, ttyp);
    }

   if (first_time) { x1 = ox1; x2 = ox2; first_time = FALSE; } 
   else
    {
     if (x1 == NULL) x1 = x2 = NULL;
     else { x1 = __copy_expr(ox1); x2 = __copy_expr(ox2); }
    }
   if (!chkset_wdrng(np, x1, x2)) goto nxt_port;

   /* 2 cases, if so far only appeared in port header wirtypknown F */
   /* and need to set as wire not reg (default for ports), else already set */
   /* but notice if set, type still not known just implicitly wire */
   if (is_complete)
    {
     np->ntyp = wtyp;


     /* must make as  */
     np->nu.ct->n_iscompleted = TRUE;
    }
   else if (!np->nu.ct->n_wirtypknown) np->ntyp = N_WIRE;

   /* AIV 08/16/10 - wire type which isn't defined is first declared a reg */
   /* need to shut off the 2state bit */
   /* SJM 08-04-10 - new 2 state var */
   if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;
   else np->n_2state = FALSE;

   syp->sydecl = TRUE;
   /* need I/O decl. place not header or wire decl. */
   syp->syfnam_ind = __cur_fnam_ind;
   syp->sylin_cnt = __lin_cnt;

nxt_port:
   __get_vtok();
   if (__toktyp == SEMI) break;

   /* AIV 08/17/11 - now if there is an = if not a wire can init value */
   /* could be a variable initialization i.e. integer i = 12; */
   if (__toktyp == EQ && np != NULL)
    {
     if (np->ntyp >= NONWIRE_ST)
      {
       /* cannot init an array - illegal syntax */
       if (np->n_isarr)  
        {
         __pv_ferr(3429,
          "variable assign initialize form illegal for %s - arrays cannot be initialized",
          syp->synam); 
         goto try_resync;
        }
       if (!rdbld_mod_varinitlst(syp, FALSE)) goto try_resync;

       if (__toktyp == SEMI) break;
      }
     else
      {
       /* must be of non-wire type to initialize */
       __pv_ferr(3437, 
         "variable assign initialize form illegal for %s - cannot initialize type %s", 
          syp->synam, __to_wtnam2(__xs, np->ntyp));
      }
    }

try_resync:

   if (__toktyp != COMMA)
    {
     __pv_ferr(995,
      "I/O port declaration list comma or semicolon expected - %s read",
      __prt_vtok());
     /* try to resync */
     if (!__vskipto2_any(COMMA, SEMI)) return(FALSE); 
     if (__toktyp == COMMA) goto nxt_var;
     break;
    }
nxt_var:
   __get_vtok();
  }
 return(TRUE);
}

/*
 * read a decl range (either reg, wire, array, or gate/inst)
 * know possible for range present [ read and reads one past end ]
 * this fills exprs that are evaluated later
 *
 * on error caller handles skipping
 * x1 and x2 only point to non nil if succeeds
 *
 * AIV 10/04/10 - made static and added new SV code to fixup new array
 * size code without a partsel array[5] => array[4:0]
 */
static int32 rd_decl_rng(struct expr_t **x1, struct expr_t **x2, 
  int32 canbe_lsb_style)
{
 struct expr_t *sel_ndp, *minus_ndp;

 *x1 = *x2 = NULL;
 if (__toktyp == LSB) 
  {
   if (!__col_rangeexpr())
    {
     /* error, but structure right */
     if (__toktyp == RSB) { __get_vtok(); return(TRUE); }
     return(FALSE);
    }
   __bld_xtree(0);
   __get_vtok();
   /* if SV parse and can be declared as [5] instead of [4:0] - convert */
   /* the LSB of [5] to a PARTSEL of [4:0] */
   if (__sv_parse && canbe_lsb_style)
    {
     /* must be a lsb - else will get error below */
     if (__root_ndp->optyp == LSB)
      {
       __root_ndp->optyp = PARTSEL; 
       sel_ndp = __root_ndp->ru.x;
       /* alloc a -1 expr of the lsb expression */
       minus_ndp = __alloc_newxnd();
       minus_ndp->optyp = MINUS;
       minus_ndp->lu.x = __copy_expr(sel_ndp); 
       /* get a one */
       minus_ndp->ru.x = __bld_rng_numxpr(1L, 0L, WBITS);
       sel_ndp->ru.x = minus_ndp;
       /* the rhs is an implied 0 */
       sel_ndp->lu.x = __bld_rng_numxpr(0L, 0L, WBITS);
       sel_ndp->optyp = COLON; 
      }
    }
   /* this really is number range */
   if (__root_ndp->optyp != PARTSEL && __root_ndp->optyp != PARTSEL_NDX_PLUS 
      && __root_ndp->optyp != PARTSEL_NDX_MINUS)
    {
     __pv_ferr(998, "illegal declaration range expression");
    }
   else { *x1 = __root_ndp->ru.x->lu.x; *x2 = __root_ndp->ru.x->ru.x; }
  }
 return(TRUE);
}

/*
 * add a net attribute 
 * SJM - 03/20/00 - if I/O decl attrs really net attrs for port net
 */
static void add_net_attr(struct net_t *np, int32 ttyp)
{
 struct attr_t *attrp, *new_attrp, *last_attrp;

 /* need to set token type so each parsed attr_spec has right tok type */
 __wrk_attr.attr_tok = ttyp;
 
 /* return nil on error */
 if ((new_attrp = __rd_parse_attribute(&__wrk_attr)) != NULL)
  { 
   if (np->nattrs == NULL) np->nattrs = new_attrp;
   else
    {
     /* linear search not problem because only 2 decls possible */
     last_attrp = NULL;
     /* move to tail of list */
     for (attrp = np->nattrs; attrp != NULL; attrp = attrp->attrnxt) 
      { last_attrp = attrp; }
     /* SJM 08/02/01 - add if to keep lint happy */
     if (last_attrp != NULL) last_attrp->attrnxt = new_attrp;
    }
  }
 __my_free(__wrk_attr.attrnam, __attr_line_len + 1);
 __wrk_attr.attr_seen = FALSE;
}

/*
 * [wire type] [charge or drive stren] [range] [delay] [list of variables]
 * [charge strength] is ([cap. size])
 */

/*
 * read and process a wire/reg/time/int/real variable declaration
 * know wire type read and reads final semi
 * semantic routines detect errors later
 * tricky because wires can also be continuous assignments
 * capacitor strength indicated by v_stren1 = NO_STREN
 *
 * if returns F synced to next module, else synced to SEMI
 * SJM 12-13-08 - this can be called from gen blk where declares in gblk
 * local scope
 */
static int32 rd_vardecl(word32 wtyp)
{
 int32 first_time, split_state, is_signed, has_attr, dim, i;
 int32 has_wdecl;
 struct expr_t *x1, *x2, *ox1, *ox2, *xm1, *xm2;
 struct sy_t *syp;
 struct net_t *np;
 struct expr_t *tab_of_ax1[MAX_ARRAY_DIM];
 struct expr_t *tab_of_ax2[MAX_ARRAY_DIM];
 struct mda_t *mdap;
 struct paramlst_t *pmphdr;
 struct genitem_t *gip;
 struct genblk_t *cgblkp;
 struct conta_t *cap;
 char s1[RECLEN];

 np = NULL;
 pmphdr = NULL;
 __v0stren = __v1stren = NO_STREN;
 /* SJM 07-31-10 - notice in SV, byte is c signed char */  
 /* this is just default assumption, signed/unsigned keyword can change */
 if (__is_int_atom_typ(wtyp) || __is_non_int_typ(wtyp)) is_signed = TRUE;
 else is_signed = FALSE;
 
 __get_vtok();
 if (__toktyp == LPAR)
  {
   __get_vtok();
   /* normal use of strengths if for wire assign net decl form */
   if (!rd_verstrens())
    {
     if (!__vskipto2_any(RPAR, SEMI)) return(FALSE);
     if (__toktyp == RPAR) { __get_vtok(); goto rd_rng; }
     return(TRUE);
    }
   /* if error strength turned off */
   chk_capwdecl_strens(wtyp);
  }

rd_rng:
 split_state = SPLT_DFLT;
 if (__toktyp == VECTORED) { __get_vtok(); split_state = SPLT_VECT; }
 else if (__toktyp == SCALARED) { split_state = SPLT_SCAL; __get_vtok(); }

 if (__toktyp == SIGNED)
  {
   if (wtyp == N_EVENT || __is_non_int_typ(wtyp))
    {
     __pv_ferr(3423, "signed keyword illegal for variable declaration type %s",
      __to_wtnam2(s1, wtyp));
    }
   else is_signed = TRUE;
   __get_vtok();
  }
 else if (__toktyp == UNSIGNED)
  { 
   if (wtyp == N_EVENT || __is_non_int_typ(wtyp))
    {
     __pv_ferr(3423,
      "unsigned keyword illegal for variable declaration type %s",
      __to_wtnam2(s1, wtyp));
    }
   else is_signed = FALSE;
   __get_vtok();
  }
 if (!rd_decl_rng(&ox1, &ox2, FALSE))
  {
   if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
   if (__toktyp == SEMI) return(TRUE);
   /* on success this reads one past ] */
   __get_vtok();
  } 
 if (split_state != SPLT_DFLT)
  {
   char s2[RECLEN];

   /* SJM 07/19/02 - notice only one of these errors can be emitted */
   if (wtyp >= NONWIRE_ST)
    {
     __pv_ferr(997,
      "%s keyword illegal for type \"%s\"", __to_splt_nam(s1, split_state),
      __to_wtnam2(s2, wtyp));
     split_state = SPLT_DFLT; 
     ox1 = ox2 = NULL;
    }
   else if (ox1 == NULL)
    {
     __pv_ferr(996, "%s keyword required following range missing",
      __to_splt_nam(s1, split_state));
     split_state = SPLT_DFLT; 
    }
  }
 if (ox1 != NULL)
  {
   if (!__is_int_vec_typ(wtyp) && wtyp >= NONWIRE_ST)
    {
     __pv_ferr(1002, "vector range illegal for type %s",
       __to_wtnam2(s1, wtyp));
     ox1 = ox2 = NULL;
    }
  }
 /* leave scalar with SPLT_DFLT state */
 /* returning F means must try to skip to semi */ 
 if (__toktyp == SHARP)
  {
   if (!rd_oparamdels(&pmphdr))
    {
bad_end:
     return(__vskipto_any(SEMI));
    } 
  }

 /* use local has attr flag so can turn glb seen of before return */
 if (__wrk_attr.attr_seen) { has_attr = TRUE; __wrk_attr.attr_seen = FALSE; }
 else has_attr = FALSE;
 /* know ox1 and ox2 contain statement decl range */ 
 for (first_time = TRUE, has_wdecl = FALSE;;)
  {
   /* save line count since for conta form need lhs var location */
   if (__toktyp != ID)
    {
     __pv_ferr(1001, "wire or reg declaration wire name expected - %s read",
      __prt_kywrd_vtok());
     /* must move over this token in case it is vendor 1 keyword */
     __get_vtok();
     goto bad_end;
    }
  
   /* if hdr list of port form used, decls giving additional info illegal */
   if ((syp = __get_sym_env(__token)) != NULL && syp->sytyp == SYM_N
    && syp->el.enp->iotyp != NON_IO)
    {
     if (__lofp_port_decls || syp->el.enp->nu.ct->n_iscompleted)
      {
       if (__lofp_port_decls)
        {
         __pv_ferr(3421,
          "%s declaration of port \"%s\" illegal - module uses list of ports declarations form",
          __to_wtnam2(s1, wtyp), __prt_kywrd_vtok());
        }
       else
        {
         __pv_ferr(3424,
          "%s declaration of port \"%s\" illegal - net type is previously defined",
          __to_wtnam2(s1, wtyp), __prt_kywrd_vtok()); 
        }
 
       /* ignore rest of declaration - should resync if no syntax error */
       if (!__vskipto2_any(COMMA, SEMI)) return(FALSE); 
       if (__toktyp == SEMI) return(TRUE);
       goto nxt_wire;
      }
    }

   /* set implied range for time and integer */
   /* each time through need to call this to make copy */
   if (ox1 == NULL) __set_reg_widths(wtyp, &x1, &x2);
   else if (first_time) { x1 = ox1; x2 = ox2; }
   else { x1 = __copy_expr(ox1); x2 = __copy_expr(ox2); }

   /* must skip to ending ; here since cannot decl. any of list */
   /* and lack information to read rest of this decl. */ 
   if ((np = decl_wirereg(wtyp, x1, x2, NULL)) == NULL)
    {
     /* resync at , or ; - should succeed */
try_resync:
     if (!__vskipto2_any(COMMA, SEMI)) return(FALSE); 
     if (__toktyp == SEMI) return(TRUE);
     goto nxt_wire;
    }
   /* if previously used will be treated as reg - must set to compatible */
   /* wire type if declared as time or int32 */
   np->ntyp = wtyp;

   /* SJM 08-04-10 - new 2 state var */
   if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;

   syp = np->nsym;

   /* SJM - 03/20/00 - save wire decl attrs */
   /* if saw an (* *) attribute for module item token, seen on */
   if (has_attr)
    {
     /* add to end if I/O decl seen first for ports - still on net not port */
     add_net_attr(np, WIRE);
    }

   /* different array range expr. for every array */
   __get_vtok();
   if (!rd_decl_rng(&xm1, &xm2, TRUE))
    {
     if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
     if (__toktyp == SEMI) return(TRUE);
     __get_vtok();
    }
   /* AIV 02/23/09 - wire arrays are now allowed */
   /*
   if (xm1 != NULL && (wtyp < NONWIRE_ST || wtyp == N_EVENT))
    {
     __pv_ferr(1003, "%s %s cannot be an array", __to_wtnam2(s1, wtyp),
      syp->synam);
     xm1 = xm2 = NULL;
    }
   */
   if (pmphdr != NULL && wtyp >= NONWIRE_ST)
    {
     __pv_ferr(1004,
      "%s %s not a wire - cannot have delay(s)", __to_wtnam2(s1, wtyp),
      syp->synam);
     pmphdr = NULL;
    }
   if (xm1 != NULL)
    { 
     np->n_isarr = TRUE; 
     /* AIV 07/21/10 - this should have never turned these bits on for */
     /* arrays - now allowing dumping of arrays */
     if (__dmpvars_all && !__dump_arrays && !(np->ntyp < NONWIRE_ST))
      {
       np->dmpv_in_src = FALSE;
       np->nu.ct->dmpv_in_src = FALSE;
      }
     dim = 1;
     if (__toktyp != LSB)
      { 
       np->nu.ct->ax1 = xm1; 
       np->nu.ct->ax2 = xm2; 
      }
     else
      {
       tab_of_ax1[0] = xm1;
       tab_of_ax2[0] = xm2;

       /* get a mult-dimensional array decl */
       while (__toktyp == LSB)
        {
         /* check for max dimesions */
         if (dim == MAX_ARRAY_DIM)
          {
           __pv_ferr(3436,
            "array %s - cannot have more than %d dimensions", syp->synam, 
            MAX_ARRAY_DIM); 
           /* SJM 02-09-09 - must return and try to resync here */
           if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
           if (__toktyp == SEMI) return(TRUE);
           return(FALSE);
          }
         if (!rd_decl_rng(&xm1, &xm2, TRUE))
          {
           if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
           if (__toktyp == SEMI) return(TRUE);
           __get_vtok();
         }
         tab_of_ax1[dim] = xm1;
         tab_of_ax2[dim] = xm2;
         dim++;
        }
       /* alloc a multi-dim array info struct */
       mdap = (struct mda_t *) __my_malloc(sizeof(struct mda_t));
       /* SJM 01-17-08 alloc the two dim size array range expr ptr tabs */ 
       mdap->tab_ax1 = (struct expr_t **)
        __my_malloc(dim*sizeof(struct expr_t *));
       mdap->tab_ax2 = (struct expr_t **)
        __my_malloc(dim*sizeof(struct expr_t *));

       mdap->dimension = dim;
       mdap->rng1 = mdap->rng2 = NULL;
       mdap->ni1 = mdap->ni2 = -1;
       mdap->dim_mult = NULL;
       /* set the ranges for each dim */
       for (i = 0; i < dim; i++)
        {
         mdap->tab_ax1[i] = tab_of_ax1[i]; 
         mdap->tab_ax2[i] = tab_of_ax2[i]; 
        }
       np->mda = mdap;
      }
     }
   np->nu.ct->n_spltstate = split_state;

   /* SJM 10/02/03 - now signed keyword or int real implies signed */
   /* must not turn off since if port and turned on there, stays on */
   if (is_signed) np->n_signed = TRUE;

   /* AIV 09/29/04 - now if there is an = not necessarily a cont assgn */
   /* could be a variable initialization i.e. integer i = 12; */
   if (__toktyp == EQ)
    {
     if (np->ntyp >= NONWIRE_ST)
      {
       /* cannot init an array - illegal syntax */
       if (np->n_isarr)  
        {
         __pv_ferr(3429,
          "variable assign initialize form illegal for %s - arrays cannot be initialized",
          syp->synam); 
         goto try_resync;
        }
       if (!rdbld_mod_varinitlst(syp, FALSE)) goto try_resync;
      }
     else
      {
       /* SJM 05-13-10 - need separate wdecl 1st time for saving end ca */
       /* can have wire decl list form where first does not have a wdecl */
       /* assign */
       if (!do_wdecl_assgn(syp, pmphdr, first_time)) goto try_resync;
       has_wdecl = TRUE;
      }
    }
   else
    {
     /* copying delay list here since gets freed and converted later */
     if (first_time) np->nu.ct->n_dels_u.pdels = pmphdr;
     else np->nu.ct->n_dels_u.pdels = __copy_dellst(pmphdr);
     /* know strength good or will be turned off by here */
     if (__v0stren != NO_STREN)
      {
       if (wtyp == N_TRIREG)
        {
         /* know capacitor strength already checked */
         np->n_capsiz = __to_cap_size(__v0stren);
        } 
       else chk_drvstren(wtyp);
      }
     /* set trireg default to medium (always needed) */
     else if (wtyp == N_TRIREG) np->n_capsiz = CAP_MED;  
    }

nxt_wire:
   if (first_time) first_time = FALSE;
   /* AIV 05/08/09 - this needs to go here to handle var declarations in */
   /* gen blocks to handle the 'reg var1, var2;' in loop - was only */
   /* adding the last variable */
   if (__cur_cntxt_gblk != NULL)
    {
     cgblkp = __cur_cntxt_gblk;

     gip = __alloc_init_new_genitem(GI_VARDECL);
     gip->giu.gi_np = np;

     if (cgblkp->last_gitem == NULL) cgblkp->gitems = gip;
     else cgblkp->last_gitem->geninxt = gip;
     cgblkp->last_gitem = gip;

     /* SJM 05-13-10 - may also need to bld a gen item for wire decl ca */
     if (has_wdecl)
      {
       cap = (struct conta_t *) __end_ca;
       if (cap == NULL) cap = __inst_mod->mcas;

       gip = __alloc_init_new_genitem(GI_CONTA);
       gip->giu.gi_cap = cap;
       gip->giu.gi_cap->pbcau.canxt = NULL;

       if (cgblkp->last_gitem == NULL) cgblkp->gitems = gip;
       else cgblkp->last_gitem->geninxt = gip;
       cgblkp->last_gitem = gip;

       /* SJM 05-13-10 - this now sets end to start of possible conta list */
       /* must remove from end of ca lst too */
       __end_ca = (struct conta_t *) __save_last_mitem;  

       /* SJM 11-11-08 if this was first one added - must fix mod's ptr */
       if (__end_ca == NULL) __inst_mod->mcas = NULL;
       else __end_ca->pbcau.canxt = NULL;
      }
    }
   has_wdecl = FALSE;

   if (__toktyp == SEMI) break;
   if (__toktyp != COMMA)
    {
     __pv_ferr(1005,
      "wire declaration comma separator or semicolon expected - %s read",
      __prt_vtok());
     /* try to resync */
     if (!__vskipto2_any(COMMA, SEMI)) return(FALSE); 
     if (__toktyp == SEMI) break;
    }
   __get_vtok();
   first_time = FALSE;
  }
 return(TRUE);
}

/*
 * need ncomp records also now for calculating dimensions
 */
static void init_ncomp(struct ncomp_t *ncmp)
{
 ncmp->nx1 = ncmp->nx2 = NULL;
 ncmp->ax1 = ncmp->ax2 = NULL;
 ncmp->n_pb_drvtyp = NULL;
 ncmp->n_drvtyp = DRVR_NONE;
 ncmp->n_dels_u.pdels = NULL;
 ncmp->n_iotypknown = FALSE;
 ncmp->n_wirtypknown = FALSE;
 ncmp->n_rngknown = FALSE;
 ncmp->n_impldecl = FALSE;
 ncmp->n_in_gia_rng = FALSE;
 ncmp->n_onrhs = FALSE;
 ncmp->n_onlhs = FALSE;
 ncmp->n_2ndonlhs = FALSE;
 ncmp->num_prtconns = 0;
}

/*
 * check cap. wire declaration strength - no strength appeared
 */
static void chk_capwdecl_strens(word32 wtyp)
{
 char s1[RECLEN], s2[RECLEN];

 if (!__is_capstren(__v0stren))
  {
   if (wtyp == N_TRIREG)
    {
     __pv_ferr(1006,
      "trireg wire declaration non capacitor size strength %s illegal",
      __to_stren_nam(s1, __v0stren, __v1stren));
     __v0stren = __v1stren = NO_STREN;
    }
   return;
  }
 /* know this is cap. strenght */
 if (wtyp != N_TRIREG)
  {
   __pv_ferr(1007,
   "non trireg wire type %s declaration has illegal capacitor size strength \"%s\"",
    __to_wtnam2(s1, wtyp), __to_stren_nam(s2, __v0stren, __v1stren));
   __v0stren = __v1stren = NO_STREN;
  }
}

/*
 * know non assign wire decl. has strength - emit error
 */
static void chk_drvstren(word32 wtyp)
{
 char s1[RECLEN], s2[RECLEN];

 /* SJM 04/17/03 - must not use stren to string routine if not set in src */
 if (__v0stren == 0 || __v1stren == 0)
  {
   __pv_ferr(1008,
    "%s declaration required tow driving strengths not present in non wire assign form",
    __to_wtnam2(s1, wtyp));
  }
 else
  {
   __pv_ferr(1008,
    "%s declaration driving strength \"%s\" illegal in non wire assign form",
     __to_wtnam2(s1, wtyp), __to_stren_nam(s2, __v0stren, __v1stren));
  }
 __v0stren = __v1stren = NO_STREN;
}


/*
 * get old style only implicit # type parameters i.e. delay expr. list
 *
 * know # read (if needs to be present) and reads one past end
 * builds a parameter/delay list and returns pointer to header
 * this routine for # form and path delay () list (no #) only
 * specparam and deparam rhs no # or ( ok
 * error if #() 
 *
 * this routine returns F on sync error - caller must resync
 * but in places with known delimiter attempt to resync to delim 
 */
static int32 rd_oparamdels(struct paramlst_t **pmphdr)
{
 struct paramlst_t *pmp, *last_pmp;

 *pmphdr = NULL;
 /* this is #[number] or #id - not (..) form - min:typ:max requires () */
 /* for path delay will never see this form */
 __get_vtok();
 if (__toktyp != LPAR)
  {
   /* notice must surround m:t:m with () */
   if (__toktyp != ID && __toktyp != NUMBER && __toktyp != REALNUM)
    {
     __pv_ferr(1049,
     "non parenthesized delay parameter name or number expected - %s read",
      __prt_kywrd_vtok());
     return(FALSE);
    }
   __last_xtk = -1;
   /* on error, set as error expr. - maybe since param should be 0 */
   if (!__bld_expnode()) __set_xtab_errval();
   /* here does the allocating */
   __bld_xtree(0);
   pmp = __alloc_pval();
   pmp->plxndp = __root_ndp;
   pmp->pmlnxt = NULL;
   *pmphdr = pmp;
  }
 else
  {
   /* #(...) form */
   for (last_pmp = NULL;;)
    {
     __get_vtok();
     if (!__col_delexpr(TRUE))
      {
       if (!__vskipto3_modend(COMMA, RPAR, SEMI)) return(FALSE);
       if (__toktyp == SEMI) return(FALSE);
      }       
     __bld_xtree(0);
     pmp = __alloc_pval();
     pmp->plxndp = __root_ndp;

     /* link on front */
     if (last_pmp == NULL) *pmphdr = pmp; else last_pmp->pmlnxt = pmp;
     last_pmp = pmp;

     if (__toktyp == COMMA) continue;
     if (__toktyp == RPAR) break;
     /* should never happen - sync on err above, if does give up */
     __pv_ferr(1050,
      "delay parameter list comma or right parenthesis expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
  }
 __get_vtok();
 return(TRUE);
}

/*
 * allocate a # style parameter value (also for specify delays)
 */
extern struct paramlst_t *__alloc_pval(void)
{
 struct paramlst_t *pmp;

 pmp = (struct paramlst_t *) __my_malloc(sizeof(struct paramlst_t));
 pmp->plxndp = NULL;
 pmp->pmlnxt = NULL;
 return(pmp);
}

/*
 * process a wire decl. assign
 * notice # delays and strengths are put into globals
 * also notice wire values in this case moved here no wire delay
 *
 * SJM 05-13-10 - need separate wdecl 1st time for saving last so can
 * move to gen items if in gen blk, normal wire decl 1st time still needed
 * for copying delay list
 */
static int32 do_wdecl_assgn(struct sy_t *syp, struct paramlst_t *pmphdr,
 int32 first_time)
{
 struct conta_t *cap;
 struct expr_t *lhs_ndp;
 int32 sfnind, slcnt;

 /* need lhs wire as location of conta */
 sfnind = syp->syfnam_ind;
 slcnt = __lin_cnt;
 /* wire decl. form continuous assignment */
 /* generate expression from node that is simply wire name */
 lhs_ndp = __gen_wireid_expr(syp);
 /* collect rhs and build expression tree */
 __get_vtok();
 if (!__col_comsemi(-1)) return(FALSE);
 __bld_xtree(0);
 /* SJM 05-13-10 - for conta's declared in wire decls, each one handled */ 
 /* in wdecl list so only one may need to be as a gen item */
 __save_last_mitem = (void *) __end_ca;
 /* SJM 04-13-10 - now may need to add and build gblk item for wdecl assign */
 cap = add_conta(lhs_ndp, __root_ndp, sfnind, slcnt, __cur_cntxt_gblk);

 /* uses wire decl delay and strength */
 if (first_time) cap->ca_du.pdels = pmphdr;
 else cap->ca_du.pdels = __copy_dellst(pmphdr);
 if (__v0stren != NO_STREN) 
  {
   cap->ca_hasst = TRUE;
   cap->ca_stval = ((__v0stren << 3) | __v1stren) & 0x3f;
  }
 return(TRUE);
}

/*
 * read the initialize to expr and add to mod's var init list 
 * format example: reg r = 12;
 *
 * build the net and expr pair lists here - check to make sure constant
 * expr during fixup and initialize as first sim step in pv_sim
 *
 * notice can't check the constant expr here since parameter decl may 
 * follow in source order
 */
static int32 rdbld_mod_varinitlst(struct sy_t *syp, int32 is_hdr_format)
{
 struct varinitlst_t *initp;

 /* collect rhs and build expression tree */
 __get_vtok();
 /* AIV 08/17/11 - if hdr format can have ) paren return value here */
 if (is_hdr_format)
  {
   if (!__col_lofp_paramrhsexpr()) return(FALSE);
  }
 else if (!__col_comsemi(-1)) return(FALSE);
 __bld_xtree(0);

 initp = (struct varinitlst_t *) __my_malloc(sizeof(struct varinitlst_t));
 initp->init_syp = syp;
 initp->init_xp = __root_ndp;
 initp->varinitnxt = NULL;

 if (__end_mod_varinitlst == NULL) __inst_mod->mvarinits = initp;
 else __end_mod_varinitlst->varinitnxt = initp;
 __end_mod_varinitlst = initp;

 return(TRUE);
}

/*
 * add the wire type decl. symbol and associated wire/reg
 *
 * because nets are a tab (array) only put in sym tab here - nets
 * are later collected from the symbol tables
 *
 * caller must set wire type after checking for duplicates
 * for declares only at top level
 * need null ranges for real, width set later or special case
 * returns null on error
 * x1 and x2 passed must be copies for multiple decls in one stmt case 
 *
 * SJM 12-11-08 - algorithm for generate wire declarations,  if no generate
 * block in mod items, then wire is really declared and goes in current symbol
 * table, if global cur cntxt gblk, all declares must decl the wire/reg in
 * the cur gen block, but must also look upward first 
 */
static struct net_t *decl_wirereg(word32 wtyp, struct expr_t *x1,
 struct expr_t *x2, struct sy_t *dsyp)
{
 struct net_t *np;
 struct sy_t *syp;
 struct symtab_t *sytp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];
 
 /* SJM 12-12-08 - if generate wire declare - is declared as local to */
 /* smallest generate block only */
 if (__cur_cntxt_gblk != NULL)
  {
   /* there are no forward declaration of generate declared nets */
   sytp = __cur_cntxt_gblk->gblk_sytab; 
   if ((syp = __get_sym(__token, sytp)) != NULL)
    {
     __pv_ferr(3601,
      "cannot declare %s as %s in generate scope - previously declared as %s at %s",
      syp->synam, __to_wtnam2(s2, wtyp), __to_wtnam2(s1, syp->sytyp),
      __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
    }
   /* need special purpose declare code for vars in generate blocks */
   syp = __decl_sym(__token, sytp);
   np = __add_net(syp, sytp);
   np->iotyp = NON_IO;
   np->ntyp = wtyp;

   /* SJM 08-04-10 - new 2 state var */
   if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;

   if (x1 != NULL)
    { np->n_isavec = TRUE; np->nu.ct->nx1 = x1; np->nu.ct->nx2 = x2; }
   if (is_decl_err(syp, SYM_N, wtyp)) return(NULL);
   if (!chkset_wdrng(np, x1, x2)) return(NULL);
   np->nu.ct->n_wirtypknown = TRUE;
   return(np);
  }

 /* this find and sets type for already read and processed I/O port decl. */
 syp = __decl_sym(__token, __venviron[0]);
 if (__sym_is_new)
  {
   np = __add_net(syp, __venviron[0]);
   np->iotyp = NON_IO;
   np->ntyp = wtyp;

   /* SJM 08-04-10 - new 2 state var */
   if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;

   if (x1 != NULL)
    { np->n_isavec = TRUE; np->nu.ct->nx1 = x1; np->nu.ct->nx2 = x2; }
  }
 else
  {
   if (syp->sytyp != SYM_N)
    {
     __pv_ferr(1028,
      "cannot declare %s as %s - previously declared as %s at %s",
      syp->synam, __to_wtnam2(s2, wtyp), __to_wtnam2(s1, syp->sytyp),
      __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
     return(NULL);
    }

   /* wire/reg decl. after I/O decl. may set range */
   np = syp->el.enp;
   /* need special handling for module I/O ports - declared in header, */
   /* I/O direction and maybe wire */
   if (np->iotyp != NON_IO)
    {
     /* if wire decl. for I/O port use it */
     /* any wire type, reg, int32, and time ok here, but not real or event */
     if (wtyp == N_REAL || wtyp == N_EVENT)
      {
       __pv_ferr(1009,
        "%s port %s %s illegal", __to_ptnam(s1, np->iotyp), syp->synam,
        __to_wtnam2(s2, wtyp));
       return(NULL);
      }
     /* this only has meaning for I/O port redecls */
     if (np->nu.ct->n_wirtypknown)
      {
       if (dsyp == NULL)
        {
         __pv_ferr(1010,
          "%s port %s previously declared as %s cannot be %s",
	  __to_ptnam(s1, np->iotyp), syp->synam, __to_wtnam(s2, np),
	  __to_wtnam2(s3, wtyp));
        }
       else
        {
         __pv_ferr(1010,
          "%s port %s previously declared as %s - unknown: %s",
	  __to_ptnam(s1, np->iotyp), syp->synam, __to_wtnam(s2, np),
          dsyp->synam);
        }
       return(NULL);
      }
     np->ntyp = wtyp;
     /* SJM 08-04-10 - new 2 state var */
     if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;
    }
   else
    {
     if (is_decl_err(syp, SYM_N, wtyp)) return(NULL);
     /* must set wire type - may override guessed wire type from use */  
     np->ntyp = wtyp;
     /* SJM 08-04-10 - new 2 state var */
     if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;
    }
   if (!chkset_wdrng(np, x1, x2)) return(NULL);
   np->nu.ct->n_wirtypknown = TRUE;
  }
 /* port header wire, require I/O port dir. decl., else this is decl. */
 if (np->iotyp == NON_IO)
  {
   syp->sydecl = TRUE;
   /* even if used before, must set to declaration place */
   syp->syfnam_ind = __cur_fnam_ind;
   syp->sylin_cnt = __lin_cnt;
  }
 return(np);
}

/*
 * allocate a new net for a symbol that is just seen for first time
 */
extern struct net_t *__add_net(struct sy_t *syp, struct symtab_t *net_sytp)
{
 struct net_t *np;

 np = (struct net_t *) __my_malloc(sizeof(struct net_t));
 np->nsym = syp;
 /* allocate during compilation part - free and change to storage later */
 np->nrngrep = NX_CT;
 np->nu.ct = (struct ncomp_t *) __alloc_arrncomp();
 /* also initialize */
 /* SJM 08/25/08 - ncomp malloc additional area needed to calc multi-dims */
 /* ncomp here converted to interp/cvc form before sim starts */
 init_ncomp(np->nu.ct);

 np->nu.ct->nx1 = np->nu.ct->nx2 = NULL;
 np->nu.ct->ax1 = np->nu.ct->ax2 = NULL;
 np->nu.ct->n_pb_drvtyp = NULL;
 np->nu.ct->n_drvtyp = DRVR_NONE;
 np->nu.ct->n_dels_u.pdels = NULL;
 np->nu.ct->n_iotypknown = FALSE;
 np->nu.ct->n_wirtypknown = FALSE;
 np->nu.ct->n_rngknown = FALSE;
 np->nu.ct->n_impldecl = FALSE;
 np->nu.ct->n_in_gia_rng = FALSE;
 np->nu.ct->n_onrhs = FALSE;
 np->nu.ct->n_onlhs = FALSE;
 np->nu.ct->n_2ndonlhs = FALSE;
 np->nu.ct->num_prtconns = 0;

 /* this is default implies word32 a/b type also for reals */
 np->srep = SR_VEC;

 /* fields for parameters only */
 np->nu.ct->n_widthdet = FALSE;
 np->nu.ct->n_indir_widthdet = FALSE;
 np->nu.ct->p_specparam = FALSE;
 np->nu.ct->p_rhs_has_param = FALSE;
 np->nu.ct->p_locparam = FALSE;
 np->nu.ct->p_genvar = FALSE;
 np->nu.ct->p_setby_defprm = FALSE;
 np->nu.ct->p_canbe_setby_pndprm = FALSE;
 np->nu.ct->prngdecl = FALSE;
 np->nu.ct->ptypdecl = FALSE;
 np->nu.ct->psigndecl = FALSE;
 np->nu.ct->parm_srep = SR_VEC;
 np->nu.ct->pbase = BNONE;
 np->nu.ct->pstring = FALSE;
 /* AIV 12/22/11 - added field as a work around for generate parameter issue */
 //AIV LOOKATME - this can be removed
 np->nu.ct->isparam_ninsts = -1;

 /* init fields for comiled sim */
 np->nu.ct->frc_assgn_in_src = FALSE;
 np->nu.ct->monit_in_src = FALSE;
 /* AIV 01/26/11 - if autotask cannot dump its value */
 if (__rd_auto_task)
  {
   np->nu.ct->dmpv_in_src = FALSE;
  }
 else
  {
   if (__dmpvars_all) np->nu.ct->dmpv_in_src = TRUE;
   else np->nu.ct->dmpv_in_src = FALSE;
  }

 np->dmpp_in_src = FALSE;
 /* assumes normal wire e when in header these will be changed */
 np->iotyp = NON_IO;
 np->n_isaparam = FALSE;
 np->n_isavec = FALSE;
 np->nwid = 0;
 np->n_isarr = FALSE;
 np->n_isarr_vector = FALSE;
 np->mda = NULL;
 /* cap. strength of non cap. strength strong is no cap. strength */
 np->n_capsiz = CAP_NONE;
 np->n_signed = FALSE;
 np->nu.ct->n_iscompleted = FALSE;
 np->nu.ct->n_spltstate = SPLT_DFLT;
 /* this gets sets in v_prep if vector - vectored is scalared */
 np->vec_scalared = TRUE;
 np->n_stren = FALSE;
 np->n_2state = FALSE;
 np->n_mark = FALSE;
 np->n_multfi = FALSE;
 np->n_isapthsrc = FALSE;
 np->n_isapthdst = FALSE;
 np->n_hasdvars = FALSE;
 np->n_onprocrhs = FALSE;
 np->n_gone = FALSE;
 /* AIV 09/14/06 - set pli is on must compile all net changes */
 /* AIV 05/13/09 - access level > 1 for change record */
 if (__pli_access_level >= 1)
  {
   np->nchg_nd_chgstore = TRUE;
  }
 else np->nchg_nd_chgstore = FALSE;
 np->nchg_has_dces = FALSE;
 np->nchg_has_lds = FALSE;
 /* 03/21/01 - these are fields from removed separate optim table */ 
 np->frc_assgn_allocated = FALSE;
 /* AIV 01/26/11 - if autotask cannot dump its value */
 if (__rd_auto_task)
  {
   np->dmpv_in_src = FALSE;
  }
 else
  {
   if (__dmpvars_all) np->dmpv_in_src = TRUE;
   else np->dmpv_in_src = FALSE;
  }
 np->monit_in_src = FALSE;
 np->n_onrhs = FALSE;
 np->n_onlhs = FALSE;
 np->n_drvtyp = DRVR_NONE;
 np->n_is_auto_var = __rd_auto_task; 
 np->n_is_auto = FALSE;
 np->n_has_toggle = FALSE;
 np->n_has_tglbits_excl = FALSE;
 np->dcelst = NULL;
 np->ndrvs = NULL;
 np->nlds = NULL;
 np->ntraux = NULL;
 np->nchgaction_ofs = 0;
 np->vpi_ndrvs = NULL;
 np->regwir_putv_tedlst = NULL;
 np->nva_ofs = 0;
 np->prm_nva.bp = NULL;
 np->nu2.nnxt = NULL;
 np->nattrs = NULL;
 np->n_cause = FALSE;
 np->n_mipd = FALSE;
 np->n_on_nblhs_varndx = FALSE;
 np->cc_need_multfi = FALSE;
 np->has_xmr = FALSE;
 np->is_loaded = FALSE;
 np->is_printed = FALSE;
 np->is_iconn_port_scalar_opt = FALSE; 
 np->fold_for_inc = FALSE;
 /* AIV 09/14/06 - set pli access either all nets on/off for now */
 np->pli_access = __pli_access_level;
 np->mfi_id = -1;
 np->nchdp = NULL;
 np->nflowg = NULL;
 np->enter_dce = NULL;
 np->enter_npp = NULL;
 np->ndel_ctevtab = NULL;
 np->syt_of_net = net_sytp;
 np->dcetable = NULL;
 syp->sytyp = SYM_N;
 syp->el.enp = np;
 /* assume reg */
 np->ntyp = N_REG;

 /* SJM 08-04-10 - since for debugging using making N_REG really N_BIT need */
 /* SJM 08-04-10 - new 2 state var */
//  if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;

 np->dmpv_funcu.single = NULL;
 np->dvns = NULL;
 np->n_arr_hasdvars = NULL;
 np->arr_num_els = -1;
 np->ntgp = NULL;
#ifdef __XPROP__
 np->xprop_accum = NULL;
 np->n_xprop_accum_set = FALSE;
 np->n_xprop_accum_set_block1 = FALSE;
 np->n_xprop_accum_set_block2 = FALSE;
 np->n_xprop_ndx = -1;
#endif
 return(np);
}

/*
 * allocate a ncomp element from a preallocated block for fast freeing
 */
extern struct ncomp_t *__alloc_arrncomp(void)
{
 struct ncablk_t *ncabp;
 struct ncomp_t *ncmp;

 if (__ncablk_nxti == -1)
  {
   ncabp = (struct ncablk_t *) __my_malloc(sizeof(struct ncablk_t));
   ncabp->ancmps = (struct ncomp_t *) __my_malloc(BIG_ALLOC_SIZE);
   ncabp->ncablknxt = __hdr_ncablks;
   __hdr_ncablks = ncabp;
   __ncablk_nxti = 0;
  }
 ncmp = (struct ncomp_t *) &(__hdr_ncablks->ancmps[__ncablk_nxti]);
 if (++__ncablk_nxti > ((BIG_ALLOC_SIZE/sizeof(struct ncomp_t)) - 1))
  __ncablk_nxti = -1;
 return(ncmp);
}

/*
 * print message and return true if declaration error
 * called for declaration when symbol is not new
 * for symbols that are like variables
 */
static int32 is_decl_err(struct sy_t *syp, word32 dclsytyp,
 word32 dclwtyp)
{
 struct net_t *np;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 if (syp->sytyp == SYM_N) np = syp->el.enp; else np = NULL;
 /* symbol already declared */
 /* see if declaration repeated */
 if (syp->sydecl || syp->sytyp != dclsytyp)
  {
   /* current symbol */
   if (np != NULL) __to_wtnam(s1, np); else __to_sytyp(s1, syp->sytyp);
   /* declared type */
   if (dclsytyp == SYM_N) __to_wtnam2(s2, dclwtyp);
   else __to_sytyp(s2, dclsytyp);

   if (syp->sydecl) strcpy(s3, "declared"); else strcpy(s3, "used");
   __pv_ferr(1014, "%s %s previously %s as %s at %s", s2, syp->synam,
    s3, s1, __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
   return(TRUE);
  }
 return(FALSE);
}

/*
 * set a register width
 */
extern int32 __set_reg_widths(word32 wtyp, struct expr_t **x1,
 struct expr_t **x2)
{
 word32 rhigh;

 /* AIV 03/12/08 - integer for 64-bit machine still 32-bits */
 switch (wtyp) {
  case N_INT: rhigh = INTBITS; break;
  case N_CINT: rhigh = CINTBITS; break;
  case N_TIME: rhigh = TIMEBITS; break;
  case N_REAL: rhigh = REALBITS;  break;
//SJM 08-02-10 WRITEME - add SV support for shortreal
//  case N_SHORTREAL: rhigh = SHORTREALBITS - 1; break;
  case N_BYTE: rhigh = BYTEBITS; break;
  case N_SHORTCINT: rhigh = SHORTCINTBITS; break;
  case N_LONGCINT: rhigh = LONGCINTBITS; break;
  case N_CHANDLE: rhigh = WBITS; break;
  default: *x1 = NULL; *x2 = NULL; return(0);
 }
 *x1 = __bld_rng_numxpr(rhigh-1, 0L, WBITS);
 *x2 = __bld_rng_numxpr(0L, 0L, WBITS);
 return(rhigh);
}

/*
 * for constant predefined ranges need to build a number expr. 
 * so param substitution and folding will work but do nothing
 *
 * LOOKATME - siz must be <= WBITS so why pass it 
 */
extern struct expr_t *__bld_rng_numxpr(word32 av, word32 bv, int32 siz)
{
 struct expr_t *ndp;

 /* this also initializes node */
 ndp = __alloc_newxnd();
 __set_numval(ndp, av, bv, siz);
 return(ndp);
}

/*
 * check and possibly set wire range
 */
static int32 chkset_wdrng(struct net_t *np, struct expr_t *x1,
 struct expr_t *x2)
{
 int32 cval;
#ifndef __CVC_RT__
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];
#endif

 /* know range - either previous I/O or wire decl. with range */
 if (np->nu.ct->n_rngknown)
  {
   if (x1 == NULL) return(TRUE);
   if (np->nu.ct->nx1 != NULL)
    cval = cmp_rng(x1, x2, np->nu.ct->nx1, np->nu.ct->nx2);
   else cval = 1;
#ifndef __CVC_RT__
   if (cval != 0)
    {
     __to_wrange(s2, np);
     __pv_fwarn(568,
     "%s port %s declaration range %s mismatch with port range %s",
      __to_wtnam(s1, np), np->nsym->synam,
      __msgtox_wrange(s3, x1, x2), s2);
    }
#endif
   return(TRUE);
  }
 if (x1 != NULL)
  {
   np->nu.ct->n_rngknown = TRUE;
   np->n_isavec = TRUE;
   np->nu.ct->nx1 = x1;
   np->nu.ct->nx2 = x2;
  }
 return(TRUE);
}

/*
 * compare 2 range exprs during compilation - before params known
 * equal if same known numbers (or numeric expr.) or if exprs the same
 */
static int32 cmp_rng(struct expr_t *x1, struct expr_t *x2,
 struct expr_t *nx1, struct expr_t *nx2)
{
 int32 has_xmr;
 if (!__cmp_xpr(x1, nx1, &has_xmr)) return(1);
 if (!__cmp_xpr(x2, nx2, &has_xmr)) return(1);
 return(0);
}

/*
 * compare 2 expressions for identicalness
 * if incorrect real, same and error caught later
 */
extern int32 __cmp_xpr(struct expr_t *nx, struct expr_t *ox, int32 *has_xmr)
{
 int32 retval, owlen, nwlen;
 word32 *owp, *nwp;

 switch ((byte) nx->optyp) { 
  /* AIV 07/11/11 - if converted to an IS param just return false */
  /* this was causing a core dump then trying to merge always@ this routine */
  /* just used for optimizing so just skip the IS number case */ 
  case ISNUMBER: return(FALSE);
  case NUMBER:
   if (ox->optyp != NUMBER) return(FALSE);
#ifdef __XPROP__
  /* AIV 09/24/11 - xprop can now compare realnums during prep code */
  case REALNUM:
#endif
   owlen = wlen_(ox->szu.xclen); 
   nwlen = wlen_(nx->szu.xclen); 
   /* since implied assignment to 32 bit value - just use low words */
   owp = &(__contab[ox->ru.xvi]); 
   nwp = &(__contab[nx->ru.xvi]); 
   if (owp[0] != nwp[0]) return(FALSE); 
   if (owp[owlen] != nwp[nwlen]) return(FALSE);
   break;
  case GLBREF:
   /* AIV 11/16/10 - now marking passed flag for XMR exprs */
   *has_xmr = TRUE;
   /*FALLTHRU */
  case ID:
   if (ox->lu.sy != nx->lu.sy) return(FALSE);
   break;
  default:
   if (ox->optyp != nx->optyp) return(FALSE);
   retval = TRUE;
   if (ox->lu.x != NULL) retval = __cmp_xpr(nx->lu.x, ox->lu.x, has_xmr); 
   if (!retval) return(FALSE);
   if (ox->ru.x != NULL) retval = __cmp_xpr(nx->ru.x, ox->ru.x, has_xmr); 
   return(retval);
 }
 return(TRUE);
}

/*
 * get optional strengths
 * know first strength read and reads one past ending )
 * can be cap size or strength pair - because of cont. assignments gets
 * checked later
 * set globals __v0stren and __v1stren
 */
static int32 rd_verstrens(void)
{
 int32 strentyp;

 __v0stren = __v1stren = NO_STREN;
 /* this sets __v0stren and __v1stren F means structural problem */
 if (!rd_1verstren(&strentyp)) return(FALSE);
 /* returned T and 2nd strength null means cap. size */
 if (strentyp == CAP_STREN) { __get_vtok(); return(TRUE); }
 if (__toktyp == RPAR)
  {
   __pv_ferr(1015,
    "required 2nd drive strength missing - %s read", __prt_vtok());
   return(FALSE);
  }

 /* know comma read to get here */
 __get_vtok();
 if (!rd_1verstren(&strentyp)) return(FALSE);
 if (__toktyp == COMMA)
  {
   __pv_ferr(1016, "strength list has more than 2 strengths");
   return(FALSE);
  }
 __get_vtok();
 if (__v0stren == NO_STREN || __v1stren == NO_STREN)
  {
   __pv_ferr(1017, "0 or 1 transition strength repeated (other missing)");
   if (__v0stren == NO_STREN) __v0stren = __v1stren;
   else __v1stren = __v0stren;
  }
 if (__v0stren == ST_HIGHZ && __v1stren == ST_HIGHZ)
  {
   __pv_ferr(1018, "(highz0, highz1) strength illegal");
   __v0stren = __v1stren = NO_STREN;
  }
 else if (__v0stren == ST_STRONG && __v1stren == ST_STRONG)
  {
   __finform(424,
    "explicit (strong0, strong1) removed to speed up simulation"); 
   __v0stren = __v1stren = NO_STREN;
  }
 return(TRUE);
}


/*
 * get 1 strength - know leading '(' and strength read
 * reads ending ')' or ',', sets __v1stren and __v0stren
 *
 * notice this returns symbolic constant that is strength type set either
 * __v0stren or __v1stren depending on token type
 * returns F on token error else F, if bad sets to none
 */
static int32 rd_1verstren(int32 *strentyp)
{
 int32 strenval;

 *strentyp = NO_STREN;
 if ((*strentyp = is_tokstren(__toktyp)) == CAP_STREN)
  {
   strenval = __fr_stren_nam(__toktyp);
   __get_vtok();
   if (__toktyp != RPAR)
    {
     __pv_ferr(1019, "trireg charge strength ending ')' expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   __v0stren = strenval;
   return(TRUE);
  }
 if (*strentyp == LOW_STREN)
  {
   if (__v0stren != NO_STREN)
    __pv_fwarn(569, "both strengths are 0 transition - 2nd changed");
   __v0stren = __fr_stren_nam(__toktyp);
  }
 else if (*strentyp == HIGH_STREN)
  {
   if (__v1stren != NO_STREN)
    __pv_fwarn(569, "both strengths are 1 transition - 2nd changed");
   __v1stren = __fr_stren_nam(__toktyp);
  }
 else
  {
   __pv_ferr(1020, "expected strength missing - %s read", __prt_vtok());
   return(FALSE);
  }
 __get_vtok();
 if (__toktyp != COMMA && __toktyp != RPAR)
  {
   __pv_ferr(1021,
    "strength not followed by comma or right parenthesis - %s read",
    __prt_vtok());
   return(FALSE);
  }
 return(TRUE);
}

/*
 * determine if token type strength and whether 0 or 1 group
 */
static int32 is_tokstren(int32 ttyp)
{
 switch (ttyp) {
  case SUPPLY0: case STRONG0: case PULL0: case WEAK0: case HIGHZ0:
   return(LOW_STREN);
  case SUPPLY1: case STRONG1: case PULL1: case WEAK1: case HIGHZ1:
   return(HIGH_STREN);
  case SMALL: case MEDIUM: case LARGE:
   return(CAP_STREN);
 }
 return(NO_STREN);
}

/*
 * read the parameter statement (declares the parameter)
 * form: parameter [name] = [value], [name] = [value], ...;
 * where name is a simple id and [value] is a constant expr.
 *
 * no # or () around delay in parameter decl. but min:typ:max form
 * needs () since rhs is constant expr. in grammar not mintypmax expr.
 *
 * if returns F synced to next module, else synced to SEMI
 *
 * also reads vendor1 specific param types
 *
 * SJM 10/07/03 - add optional signed declaration - following normal
 * rule for parameter typing, if signed not present determined from rhs
 *
 * SJM 05/25/04 - added new P1364 module #(<param decl>, ...) form but only 
 * for modules parameter declarations and unlike header list of ports both
 * types can be combined 
 *
 * SJM 08-02-10 - changed to SV syntax possibilities are:
 * [signed/unsigned] [range] or [net type name] [signed/unsigned] [range]
 */
static int32 rd_paramdecl(int32 is_hdr_form, int32 is_local_param)
{
 int32 ptyp_decl, prng_decl, psign_decl, pwtyp, pwid, is_signed, r1, r2;
 struct expr_t *x1, *x2;
 struct net_t *np;
 char paramnam[IDLEN], ptnam[RECLEN];

 if (is_local_param) strcpy(ptnam, "localparam");
 else strcpy(ptnam, "parameter");

 x1 = x2 = NULL;
 pwid = -1;
 ptyp_decl = FALSE; 
 prng_decl = FALSE;
 pwtyp = -1;
 is_signed = FALSE;
 psign_decl = FALSE; 
 __get_vtok();
 
 pwid = WBITS;
 /* key for SV is that if [type] given, must be first */
 if ((pwtyp = __fr_wtnam(__toktyp)) != -1)
  {
   ptyp_decl = TRUE;
   __get_vtok();
  }
 else pwtyp = N_REG;

 if (__toktyp == SIGNED)
  {
   psign_decl = TRUE;
   is_signed = TRUE;
   __get_vtok();
  }
 else if (__toktyp == UNSIGNED)
  {
   psign_decl = TRUE;
   is_signed = TRUE;
   __get_vtok();
  }

 /* read the range */
 if (__toktyp == LSB)
  {
   /* SJM 01-29-09 - for explicit range must leave pwid -1 here */
   /* also check to make sure ranges are non x/z 32 bit values */
   if (!__rd_opt_param_vec_rng(&x1, &x2, is_hdr_form)) return(FALSE);

   /* if T, this is error condition */
   if (x1 == NULL || x2 == NULL) goto chk_typ;

   if (!__is_int_vec_typ(pwtyp) && pwtyp >= NONWIRE_ST)
    {
     __pv_ferr(686, "%s declaration range illegal for declared type %s",
      ptnam, __to_wtnam2(__xs, (word32) pwtyp));
     goto chk_typ;
    }
   prng_decl = TRUE;
   /* AIV 08/26/10 - this was actually wrong in older versions as well */
   /* may declare a wide reg here */
   /* if more complicated expr - must resize param later */
   if (x1->optyp == NUMBER && x2->optyp == NUMBER)
    {
     r1 = (int32) __contab[x1->ru.xvi];
     r2 = (int32) __contab[x2->ru.xvi];
     pwid = (r1 >= r2) ? r1 - r2 + 1 : r2 - r1 + 1; 
    }
  }
 else 
  {
   /* only vec types can be scalars with no internal range */
   if (!__is_int_vec_typ(pwtyp))
    {
     /* this build the range h:l (low is 0) exprs */
     /* AIV 08/26/10 - need to set pwid here */
     pwid = __set_reg_widths(pwtyp, &(x1), &(x2));
    }
  }
 /* know parameter name read */

 /* SJM 08-02-10 - new systematic param decl syntax for SV - if net type */
 /* not given, signed and ranges will be ok here */
chk_typ:
 if (ptyp_decl)
  {
   if (pwtyp == N_EVENT || pwtyp < NONWIRE_ST)
    {
     __pv_ferr(685, "%s declaration illegal type %s", ptnam, __prt_vtok());
     x1 = x2 = NULL;
     pwtyp = N_REG;
    }
  }
 /* SJM 08/02/10 - new SV algorithm - separate checking */
 if (psign_decl)
  {
   if (pwtyp == N_TIME || __is_int_atom_typ(pwtyp))
    {
     /* AIV 08/17/11 - mas not passing var name for first %s */
     __pv_ferr(3423,
      "%s signed or unsigned keyword illegal when declared parameter type %s",
      ptnam, __to_wtnam2(__xs, pwtyp));
     psign_decl = FALSE;
    }
  }

 /* if ptyp decl F, then must attempt to determine param type from rhs */ 
 for (;;)
  {
   if (__toktyp != ID)
    {
     __pv_ferr(1023,
      "%s declaration parameter name expected - %s read", ptnam,
      __prt_kywrd_vtok());
bad_end:
     /* part of delay expression may have been built */
     if (!is_hdr_form)
      {
       if (!__vskipto2_any(COMMA, SEMI)) return(FALSE);
       if (__toktyp == COMMA) { __get_vtok(); continue; }
      }
     else
      {
       if (!__vskipto2_any(COMMA, RPAR)) return(FALSE); 
       if (__toktyp == COMMA) { __get_vtok(); continue; }
      }
     return(TRUE);
    }
   strcpy(paramnam, __token);

   /* initial value always required */
   __get_vtok();

   /* SJM 01-25-09 - needed to remove the old AMS parameter arrays because */
   /* conflict with constant functions since parameter arrays outside of */
   /* digital Verilog/World */

   if (__toktyp != EQ)
    {
     __pv_ferr(1024,
      "%s declaration equal expected - %s read", ptnam, __prt_vtok());
     goto bad_end;
    }

   /* notice initial value required */
   __get_vtok();
   /* this can collect array construct that will look like concat */
   if (is_hdr_form)
    {
     /* SJM 05/26/04 - new module decl #(list of param decls) form needs */
     /* different collect routine because semi illegal */
     if (!__col_lofp_paramrhsexpr()) goto bad_end;
    }
   else
    {
     if (!__col_newparamrhsexpr()) goto bad_end;
    }
   __bld_xtree(0);

   if (__has_top_mtm)
    {
     __pv_fwarn(652,
      "%s %s declaration min:typ:max expression needs parentheses under 1364 - unportable",
      ptnam, paramnam);
    }

   /* SJM 01-29-09 - now only can alloc param net and set fields that */
   /* correspond to passed nu.ct fields that are set */

   /* check and links on modules parameter list */
   /* when rhs expr. evaluated, if real will change */
   /* LOOKATME - problem with all params in list sharing range xprs? */ 
   if ((np = __add_param(paramnam, x1, x2, is_local_param, FALSE)) == NULL) 
    {
     return(FALSE);
    }
   /* for explicit param vector type, this sets actual width else -1 */
   /* this is current best guess at net type - when eval rhs will fix */
   np->nu.ct->n_dels_u.d1x = __root_ndp;
   np->nu.ct->parm_srep = SR_PXPR;
   np->nu.ct->prngdecl = prng_decl;
   np->nu.ct->ptypdecl = ptyp_decl;
   np->nu.ct->psigndecl = psign_decl;

   /* SJM 02-01-09 - some param decl fields set in parm net record */ 
   /* not touched until range set where maybe update - then maybe */
   /* updated again if no wire type and no range where set from rhs */ 
   /* SJM 02-12-09 - this was wrong - need the const func if stmts */
   if (ptyp_decl || prng_decl)
    {
     if (pwtyp == N_REAL)
      {
       np->ntyp = N_REAL; 
       np->n_signed = TRUE;
       np->nwid = REALBITS;
       np->nu.ct->pbase = BDBLE;
      }
     else
      {
       np->ntyp = pwtyp;
       /* SJM 02-12-09 - here always have a correct declared width */
       np->nwid = pwid;
       np->n_signed = is_signed;

       /* SJM 08-04-10 - new 2 state var */
       if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;
      }
    }
   else
    {
     /* only possibilities are reg or real - assign spec param will set */
     /* to real from expr type - no type decl possible for specparams */
     np->ntyp = N_REG;

     /* SJM 08-04-10 - new 2 state var */
     if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;

     /* SJM 02-12-09 - but may still have signed decl */
     np->n_signed = is_signed;
    }
   /* SJM 08-03-10 - because of the new 2 state and cint's as possible */ 
   /* param types, need to set the srep here */
   __set_1net_srep(np);

   if (is_hdr_form)
    {
     if (__toktyp == RPAR) break;
     if (__toktyp != COMMA)
      {
       __pv_ferr(1026,
        "%s module header form declaration right paren or comma expected - %s read",
        ptnam, __prt_vtok());
       if (!__vskipto2_any(COMMA, RPAR)) return(FALSE); 
       if (__toktyp == RPAR) break;
      }
    }
   else
    {
     if (__toktyp == SEMI) break;
     if (__toktyp != COMMA)
      {
       __pv_ferr(1026,
        "%s declaration semicolon or comma separator expected - %s read",
        ptnam, __prt_vtok());
       if (!__vskipto2_any(COMMA, SEMI)) return(FALSE); 
       if (__toktyp == SEMI) break;
      }
    }
   __get_vtok();
   if (is_hdr_form)
    {
     /* if , followed by ID, part of list else new parameter decl */
     if (__toktyp == PARAMETER) break;
    }
  }
 return(TRUE);
}

/*
 * return T if parameter define rhs expr contains any param
 *
 * set ncomp rhs has param bit causes re-eval of param value 
 * to use new pound and defparam values if changed
 */
extern int32 __xpr_has_param(struct expr_t *ndp)
{
 struct sy_t *syp;
 struct net_t *np;
 struct expr_t *fandp;

 switch (ndp->optyp) { 
  case NUMBER: case REALNUM: case ISNUMBER: case ISREALNUM: return(FALSE);
  case ID:
   syp = ndp->lu.sy;
   if (!syp->sydecl || syp->sytyp != SYM_N) return(FALSE);
   np = syp->el.enp; 
   if (np->n_isaparam) return(TRUE);
   return(FALSE);
  case GLBREF: return(FALSE);
  case FCALL:
   for (fandp = ndp->ru.x; fandp != NULL; fandp = fandp->ru.x)
    {
     /* LOOKATME - even if real param not allowed arg to const systf */
     /* can be real */
     if (__xpr_has_param(fandp->lu.x)) return(TRUE);
    }
   return(FALSE);
 } 
 if (ndp->lu.x != NULL) if (__xpr_has_param(ndp->lu.x)) return(TRUE);
 if (ndp->ru.x != NULL) if (__xpr_has_param(ndp->ru.x)) return(TRUE);
 return(FALSE);
}

/*
 * read a parameter vector declaration range 
 *
 * know [ read and reads one past ]
 */
extern int32 __rd_opt_param_vec_rng(struct expr_t **rx1, struct expr_t **rx2,
 int32 is_hdr_form)
{
 struct expr_t *x1, *x2;
 char ptnam[RECLEN];

 if (__cur_declobj == SPECIFY) strcpy(ptnam, "specparam");
 strcpy(ptnam, "parameter");

 *rx1 = *rx2 = NULL;
 if (!rd_decl_rng(&x1, &x2, FALSE))
  {
   if (!is_hdr_form)
    {
     if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
     if (__toktyp == SEMI) return(TRUE);
    }
   else
    {
     if (!__vskipto3_any(COMMA, RPAR, RSB)) return(FALSE); 
     if (__toktyp != RSB) return(TRUE);
    }
   __get_vtok();
   if (x1 != NULL) __free_xtree(x1);
   if (x2 != NULL) __free_xtree(x2);
   *rx1 = *rx2 = NULL;
  }
 else { *rx1 = x1; *rx2 = x2; }

 /* SJM 01-28-09 - can't eval and convert to numbers until const funcs */
 /* identified, checked and prepared so can exec */
 return(TRUE);
}


/*
 * add newly declared parameter - better not be already defined
 * called from parameter declaration item only
 * range must be passed because of parameter "v[h:l] =" form (not yet in) 
 *
 * uses initial expressions to set wire type - defparam can change
 * but one type for all instance
 *
 * this is for both parameters and specparams indicated by current decl obj
 * for specparam top of scope symbol table stack is special symbol table
 * just for specparams - no other symbols legal
 *
 * code that reads parameter arrays calls this then sets fields it
 *
 * SJM 08-04-10 - for params 2 state bits set later - type may come from eval
 */
extern struct net_t *__add_param(char *nam, struct expr_t *x1,
 struct expr_t *x2, int32 is_local_param, int32 is_genvar)
{
 int32 is_spec;
 struct tnode_t *tnp;
 struct sy_t *syp;
 struct net_t *np;
 char s1[RECLEN], ptypnam[RECLEN]; 

 if (__cur_declobj == SPECIFY)
  { is_spec = TRUE; strcpy(ptypnam, "specparam"); } 
 else
  {
   is_spec = FALSE;
   if (is_local_param) strcpy(ptypnam, "localparam");
   else if (is_genvar) strcpy(ptypnam, "genvar");
   else strcpy(ptypnam, "parameter");
  }
 /* just look in local scope here since parameter decl. must be local */
 tnp = __vtfind(nam, __venviron[__top_sti]);
 if (__sym_is_new)
  {
   __add_sym(nam, tnp);
   /* notice still need to update total symbol count */
   (__venviron[__top_sti]->numsyms)++;
   syp = tnp->ndp;
   /* this initializes ncomp for all net forms including params */
   np = __add_net(syp, __venviron[__top_sti]);
  }
 else
  {
   syp = tnp->ndp;
   if (syp->sytyp == SYM_N) np = syp->el.enp; else np = NULL;
   if (!syp->sydecl)
    {
     /* is previously used as net, then ok */
     if (syp->sytyp != SYM_N)
      {
       __pv_ferr(1027,
        "cannot declare %s %s - previously used as %s at %s", 
        nam, ptypnam, __to_sytyp(s1, syp->sytyp), __bld_lineloc(__xs,
        syp->syfnam_ind, syp->sylin_cnt));
       return(NULL);
      }
    }
   else
    {
     /* this needs to be explicit to include param wire types */
     if (np != NULL) __to_wtnam2(s1, np->ntyp);
     else __to_sytyp(s1, syp->sytyp);
     __pv_ferr(1028, "cannot declare %s %s - previously declared as %s at %s",
      nam, ptypnam, s1, __bld_lineloc(__xs, syp->syfnam_ind,
      syp->sylin_cnt));
     return(NULL);
    }
   /* know will be wire to get to be declared here */
   syp->syfnam_ind = __cur_fnam_ind;
   syp->sylin_cnt = __lin_cnt;
  }
 syp->sydecl = TRUE;

 /* change to proper type of wire even if already used */
 /* io type for parameter unused instead used for wire type */
 np->iotyp = NON_IO;
 np->n_isaparam = TRUE;
 np->nu.ct->p_locparam = is_local_param;
 np->nu.ct->p_genvar = is_genvar;
 if (is_spec) np->nu.ct->p_specparam = TRUE;
 
 /* if has range know is vector */ 
 if (x1 != NULL) { np->n_isavec = TRUE; np->vec_scalared = TRUE; }
 np->nu.ct->nx1 = x1;
 np->nu.ct->nx2 = x2;

 /* notice already linked into wire list - must also link into param list */
 /* link on end to preserve order */
 /* link the LOCAL parameters on a seperate list than the regular params */
 if (is_local_param || is_genvar)
  {
   if (__cur_declobj == MODULE)
    {
     if (__end_loc_paramnp == NULL) __inst_mod->mlocprms = np;
     else __end_loc_paramnp->nu2.nnxt = np;
     __end_loc_paramnp = np;
    }
   else if (__cur_declobj == TASK)
    {
     /* DBG remove -- */
     if (is_genvar) __misc_terr(__FILE__, __LINE__);
     /* --- */

     if (__end_tsk_loc_paramnp == NULL) __cur_tsk->tsk_locprms = np;
     else __end_tsk_loc_paramnp->nu2.nnxt = np;
     __end_tsk_loc_paramnp = np;
    }
   else __case_terr(__FILE__, __LINE__); 
  }
 else
  {
   /* regular parameter list */
   if (__cur_declobj == MODULE)
    {
     /* module parameter declaration */
     if (__end_paramnp == NULL) __inst_mod->mprms = np;
     else __end_paramnp->nu2.nnxt = np;
     __end_paramnp = np;
    }
   else if (__cur_declobj == SPECIFY)
    {
     if (__end_msprms == NULL) __cur_spfy->msprms = np;
     else __end_msprms->nu2.nnxt = np;
     __end_msprms = np;
    }
   else if (__cur_declobj == TASK)
    {
     if (__end_tskparamnp == NULL) __cur_tsk->tsk_prms = np;
     else __end_tskparamnp->nu2.nnxt = np;
     __end_tskparamnp = np;
    }
   else __case_terr(__FILE__, __LINE__); 
  }
 return(np);
}

/*
 * add a continuous assignment form cell
 * even if lhs 1 bit stored in non gate form here
 */
static struct conta_t *add_conta(struct expr_t *lhsndp, struct expr_t *rhsndp,
 int32 sfnind, int32 slcnt, struct genblk_t *cgblkp)
{
 struct conta_t *cap;
 struct symtab_t *sytp;
 struct sy_t *syp;

 /* SJM 12-13-08 - if have gblk context build the local symbol in enclosing */
 /* smallest gen blk scope, else in mod item symbol table */
 if (cgblkp == NULL) sytp = __venviron[0];
 else sytp = cgblkp->gblk_sytab;
  
 /* SJM 04-15-10 - notice conta num just a counter - can bld a sym here */
 /* it will never be used but does not hurt */
 syp = __bld_loc_symbol(__conta_num, sytp, "assgn", "continuous assign");
 syp->sytyp = SYM_CA;
 /* this is place of declaration */
 syp->syfnam_ind = sfnind;
 syp->sylin_cnt = slcnt;
 syp->sydecl = TRUE;

 cap = (struct conta_t *) __my_malloc(sizeof(struct conta_t));
 cap->casym = syp;
 syp->el.ecap = cap;
 cap->ca_hasst = FALSE;
 cap->ca_stval = ST_STRVAL;
 cap->ca_delrep = DT_CMPLST;
 cap->is_loaded = FALSE;
 cap->is_printed = FALSE;
 if (__compiled_sim) cap->enter_cndx = ++__cap_seq_no;
 else cap->enter_cndx = -1;
 cap->flowg = NULL;
 cap->ctevp = NULL;
 cap->ca_du.pdels = NULL; 
 cap->ca_4vdel = FALSE;
 cap->ca_gone = FALSE;
 cap->ca_pb_sim = FALSE;
 cap->ca_pb_el = FALSE;
 cap->lhsx = lhsndp;
 cap->rhsx = rhsndp;
 cap->caschd_tevs_ofs = 0; 
 cap->ca_drv_ofs = 0;
 cap->schd_drv_ofs = 0;
 /* SJM 12/19/04 - when chk contas done - contas now tab of size m ca num */
 /* removed nxt field from conta type - can be in pbca's built in prp pass */
 cap->pbcau.canxt = NULL;

 /* SJM 04-11-10 - must set marker in conta rd caller because can be list */
 /* link on to list */
 if (__end_ca == NULL) __inst_mod->mcas = cap;
 else __end_ca->pbcau.canxt = cap;
 __end_ca = cap;
 __conta_num++;
 return(cap);
}

/*
 * read an event declaration
 *
 * parsing routine to read and declare an event decl (can't be array/vec)
 * need to declare as task var if reading task/func/named block
 *
 * SJM 12-13-08 - this can be called from gen blk where declares in gblk
 * local scope - but also works for tasks/func decl where calls decl
 * task var decl so variable goes correctly into task symbol table
 */
static int32 rd_eventdecl(int32 reading_tsk)
{
 int32 first_time, has_attr;
 struct net_t *np;

 /* use local has attr flag so can turn glb seen of before return */
 if (__wrk_attr.attr_seen) { has_attr = TRUE; __wrk_attr.attr_seen = FALSE; }
 else has_attr = FALSE;
 for (first_time = TRUE;;)
  {
   __get_vtok();
   if (__toktyp != ID)
    {
     __pv_ferr(1029,
      "event declaration event name expected - %s read", __prt_kywrd_vtok());
     goto try_resync;
    }
   /* since no range, if fails just try next one*/
   if (reading_tsk) np = decl_taskvar(N_EVENT, NULL, NULL);
   else np = decl_wirereg(N_EVENT, NULL, NULL, NULL);

   /* SJM - 03/20/00 - save wire decl attrs */
   if (has_attr)
    {
     /* until Verilog 2000 will not see also event port attrs */
     if (np != NULL) add_net_attr(np, EVENT);
    }

   if (first_time) first_time = FALSE;

   __get_vtok();
   if (__toktyp == SEMI) break;
   if (__toktyp != COMMA)
    {
     __pv_ferr(1033,
      "event declaration comma or semicolon separator expected - %s read",
      __prt_vtok());
     /* try to resync */
try_resync:
     if (!__vskipto2_any(COMMA, SEMI)) return(FALSE); 
     if (__toktyp == SEMI) break;
    }
  }
 return(TRUE);
}

/*
 * allocate a statement entry
 * for empty statement (;) never get here
 */
extern struct st_t *__alloc_stmt(int32 styp)
{
 struct st_t *stp;
 struct for_t *frp;
 struct qconta_t *qcafs;
 struct mod_t *mdp;

 stp = (struct st_t *) __my_malloc(sizeof(struct st_t));
 __init_stmt(stp, styp);
//AIV IDP FIXME - used for both interactive and elaboration
//__indp not available during elaboration - not really consistent
 if (__idp == NULL)
  {
   mdp = __inst_mod;
  }
 else
  {
   mdp = get_inst_mod_();
  }
 (mdp->mstnum)++; 

 /* DBG remove --
 if (__debug_flg)
  {
    extern char *__to_sttyp(char *, word32);

    __dbg_msg("AT %s %s - STMT ALLOC (%s)\n",
     __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt),
     __inst_mod->msym->synam, __to_sttyp(__xs2, styp));
  }
 --- */
 /* DBG remove --
 if (__debug_flg)
  {
   extern char *__to_sttyp(char *, unsigned);

   __dbg_msg("%04d: AT %s %s - STMT ALLOC (%s)\n",
    __inst_mod->mstnum - 1, __bld_lineloc(__xs, stp->stfnam_ind,
    stp->stlin_cnt), __inst_mod->msym->synam, __to_sttyp(__xs2, styp));
  }
 --- */
 /* ALTERNATE DBG remove --
 if (__debug_flg)
  {
   extern char *__to_sttyp(char *, unsigned);

   __dbg_msg("AT %s %s - STMT ALLOC %04d (%s)\n",
    __bld_lineloc(__xs, stp->stfnam_ind, stp->stlin_cnt),
    __inst_mod->msym->synam, __inst_mod->mstnum - 1, __to_sttyp(__xs2, styp));
  }
 --- */

 switch ((byte) styp) {
  /* null just has type value and NULL pointer */
  case S_NULL: case S_STNONE: break;
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA:
  case S_INC: case S_DEC:
   stp->st.spra.lhsx = NULL;
   stp->st.spra.rhsx = NULL;
   break;
  case S_IF:
   stp->st.sif.condx = NULL;
   stp->st.sif.thenst = NULL;
   stp->st.sif.elsest = NULL;
#ifdef __XPROP__
   stp->st.sif.xprop = NULL;
   stp->st.sif.xedge_dce = FALSE;
#endif
   break;
  case S_CASE:
   stp->st.scs.castyp = UNDEF;
   stp->st.scs.maxselwid = 0;
   stp->st.scs.csx = NULL;
   stp->st.scs.csitems = NULL;
#ifdef __XPROP__
   stp->st.scs.xprop_lstp = NULL;
   stp->st.scs.xprop = NULL;
#endif
   break;
  case S_REPEAT:
   stp->st.srpt.repx = NULL;
   stp->st.srpt.reptmp_ofs = 0;
   stp->st.srpt.repst = NULL;
   break;
  case S_FOREVER:
  case S_WHILE:
  case S_DO_WHILE:
   stp->st.swh.lpx = NULL;
   stp->st.swh.lpst = NULL;
   break;
  case S_WAIT:
   stp->st.swait.lpx = NULL;
   stp->st.swait.lpst = NULL;
   stp->st.swait.wait_dctp = __alloc_dctrl();
   break;
  case S_FOR:
   frp = (struct for_t *) __my_malloc(sizeof(struct for_t));
   stp->st.sfor = frp;
   frp->has_continue = FALSE;
   frp->has_break = FALSE;
   frp->is_expanded_foreach = FALSE;
   frp->foreach_syp = NULL;
   frp->dim = -1;
   frp->forassgn = NULL;
   frp->fortermx = NULL;
   frp->forinc = NULL;
   frp->forinc_tail = NULL;
   frp->forbody = NULL;
   break;
  case S_DELCTRL:
   stp->st.sdc = __alloc_dctrl();
   break;
  case S_NAMBLK:
   stp->st.snbtsk = NULL;
   break;
  case S_UNBLK:
   stp->st.sbsts = NULL;
   break;
  case S_UNFJ:
   stp->st.fj.fjstps = NULL;
   stp->st.fj.fjlabs = NULL;
   break;
  case S_FUNCCALL:
  case S_TSKCALL:
   stp->st.stkc.targs = NULL;
   stp->st.stkc.tsksyx = NULL;
   stp->st.stkc.tkcaux.trec = NULL;
   break;
  case S_QCONTA:
   /* SJM 06/23/02 - since pre-building dce for qcaf need more fields */
   qcafs = (struct qconta_t *) __my_malloc(sizeof(struct qconta_t));
   stp->st.sqca = qcafs;
   qcafs->qcatyp = UNDEF;
   qcafs->regform = FALSE;
   qcafs->qclhsx = NULL;
   qcafs->qcrhsx = NULL;
   qcafs->rhs_qcdlstlst = NULL;
   break;
  case S_QCONTDEA:
   stp->st.sqcdea.qcdatyp = UNDEF;
   stp->st.sqcdea.qcdalhs = NULL;
   break;
  case S_CAUSE:
   stp->st.scausx = NULL;
   break;
  case S_DSABLE:
   stp->st.sdsable.dsablx = NULL;
   stp->st.sdsable.func_nxtstp = NULL;
   break;
  /* statement added for execution */
  case S_REPSETUP:
   /* union field unused */
   stp->st.scausx = NULL;
   break;
  case S_REPDCSETUP:
   /* union field unused */
   stp->st.scausx = NULL;
   break;
  case S_GOTO:
   stp->st.sgoto = NULL;
   break;
  case S_CONTINUE: case S_BREAK: case S_RETURN:
   stp->st.sgoto = NULL;
   break;
  default: __case_terr(__FILE__, __LINE__);
  }
 return(stp);
}

/*
 * initialize stmt
 */
extern void __init_stmt(struct st_t *stp, int32 styp)
{
 stp->stlin_cnt = __lin_cnt;
 stp->stfnam_ind = __cur_fnam_ind;
 stp->stmttyp = styp;
 stp->st_unbhead = FALSE;
 /* notice this always has the statement type even if break point not set */
 stp->rl_stmttyp = styp;
 stp->strb_seen_now = FALSE;
 stp->lpend_goto = FALSE;
 stp->dctrl_goto = FALSE;
 stp->lpend_goto_dest = FALSE;
 stp->dmp_stmt = FALSE;
 stp->enter_created = FALSE;
 stp->is_loaded = FALSE;
 stp->is_printed = FALSE;
 stp->unreachable = FALSE;
 stp->enterptr = NULL;
 stp->is_nb_enter = FALSE;
 stp->is_enter = FALSE;
 stp->task_thrd_jmpndx = -1;
 stp->stmt_id_ndx = __stmt_id_ndx++;
 stp->st_ndx = -1;
 stp->rhs_idp_ofs = 0;
 stp->ctevp = NULL;
#ifdef __XPROP__
 stp->nb_xprop_in_list = FALSE;
 stp->xprop_eligible = FALSE;
 stp->xprop_level = -1; 
 stp->xprop_nbu.xprop_astp = NULL;
#endif
 /* assume if non blocking need the sched tev table */
 stp->stnxt = NULL;
}

/*
 * allocate and initialize a delay control record
 */
extern struct delctrl_t *__alloc_dctrl(void)
{
 struct delctrl_t *dctp;

 dctp = (struct delctrl_t *) __my_malloc(sizeof(struct delctrl_t));
 dctp->dctyp = DC_NONE;
 dctp->dc_iact = FALSE;
 dctp->dc_delrep = DT_CMPLST;
 dctp->dc_nblking = FALSE;
 dctp->dc_is_always_comb_latch = FALSE;
 dctp->dc_is_always_ff = FALSE;
 dctp->implicit_evxlst = FALSE;
 dctp->dc_du.pdels = NULL;
 dctp->repcntx = NULL;
 dctp->dceschd_tev_ofs = 0;
 dctp->actionst = NULL;
#ifdef __XPROP__
 dctp->xprop_xedge_actionst = NULL;  
 dctp->xprop_nb_actionst = NULL;  
 dctp->d_has_xmr = FALSE;
 dctp->d_only_scalars = TRUE;
 dctp->d_only_vectors = TRUE;
 dctp->d_has_edge = FALSE;
 dctp->d_only_edges = TRUE;
 dctp->d_edgval = NOEDGE;
 dctp->d_same_edge = TRUE;
 dctp->d_uses_nets_on_rhs = FALSE;
 dctp->d_gt_one = 0;
#endif
 /* this is allocated during prep - nil for now */
 dctp->dce_repcnt_ofs = 0;
 dctp->is_merged = FALSE;
 dctp->is_always = FALSE;
 dctp->needs_thread = FALSE;
 dctp->nested_dctrl = FALSE;
 dctp->head_dctp = NULL;
 dctp->head_ctevp = NULL;
 dctp->merged_dctp = NULL;
 dctp->dc_id_ndx = __dc_id_ndx++;
 return(dctp);
}

/*
 * variant of alloc stmt that takes "real" location as args
 */
extern struct st_t *__alloc2_stmt(int32 styp, int32 fnind, int32 lcnt)
{
 int32 sav_fnami, sav_flini;
 struct st_t *stp;

 sav_fnami = __cur_fnam_ind;
 sav_flini = __lin_cnt;
 __cur_fnam_ind = fnind;
 __lin_cnt = lcnt;

 stp = __alloc_stmt(styp);

 __cur_fnam_ind = sav_fnami;
 __lin_cnt = sav_flini;
 return(stp);
}

/*
 * DEFPARAM READING ROUTINES
 */

/*
 * read the parameter defparam statement
 * assigns values to this or other params
 * form: defparam [hieriarch path or id] = [param. value expr.], ... ;
 *
 * if returns F synced to next mod/prim else synced to ;
 * list of assignments allowed here
 */
static int32 rd_dfparam_stmt(void)
{
 int32 first_time;
 struct dfparam_t *dfpp;
 struct expr_t *lhsndp;
 
 for (first_time = TRUE;;)	
  {
   __get_vtok();
   /* notice only for lhs not right */
   if (!__col_lval())
    {
     /* part of lhs may have been built */
     if (!__vskipto3_any(EQ, COMMA, SEMI)) return(FALSE);
     if (__toktyp == EQ) goto do_rhs; 
     if (__toktyp == COMMA) continue;
     return(TRUE);
    }
do_rhs:
   __bld_xtree(0);
   lhsndp = __root_ndp;
   if (lhsndp->optyp != ID && lhsndp->optyp != GLBREF)
    {
     __pv_ferr(1034, "defparam lvalue %s not identifier or hierarchical path",
      __msgexpr_tostr(__xs, lhsndp));
    }

   /* know = read */
   __get_vtok();
   if (!__col_comsemi(-1))
    {
err_cont:
     if (!__vskipto2_any(COMMA, SEMI)) return(FALSE);
     if (__toktyp == COMMA) continue;
     return(TRUE);
    }
   __bld_xtree(0);

   /* SJM 01/27/04 - must leave as rhs expr since just gets evaled */
   /* bug if convert when downward propagation of defparams used on rhs */
   /* of other defparams used */

   /* notice cannot check rhs here since defparam statement rhs can be */
   /* any local parameter(possibly defined later in source) from LRM */ 
   dfpp = alloc_dfpval();
   dfpp->dfpxlhs = lhsndp;
   dfpp->dfpxrhs = __root_ndp;
   dfpp->dfp_in_mdp = __inst_mod;
   /* SJM 09-06-11 - notice local defparams are legal - get converted */
   /* with no defparam processing needed */
   if (dfpp->dfpxlhs->optyp == GLBREF) dfpp->dfp_grp = dfpp->dfpxlhs->ru.grp;
   else dfpp->dfp_grp = NULL;

   /* must always put on end of list - order important */
   /* since reading in source order list stays in source order */
   /* within each module */
   if (first_time)
    {
     /* SJM 04-11-10 - need to move entire list from end if inside */
     /* gen blk becuase defparam <list of dfp assigns> legal */ 
     __save_last_mitem = (void *) __end_dfp; 
     first_time = FALSE;
    }
   /* SJM 04-07-10 - for defparams in gens, puts on here gen rd removes */
   if (__end_dfp == NULL) __inst_mod->mdfps = dfpp;
   else __end_dfp->dfpnxt = dfpp;
   __end_dfp = dfpp;

   /* can be comma separated assignment list */
   if (__toktyp == SEMI) break;
   if (__toktyp != COMMA)
    {
     __pv_ferr(1039,
      "defparam semicolon or comma separator expected - %s read",
      __prt_vtok());
     goto err_cont;
    }
  }
 return(TRUE);
}

/*
 * allocate a module defparam structure for later processing
 */
static struct dfparam_t *alloc_dfpval(void)
{
 struct dfparam_t *dfpp;

 dfpp = (struct dfparam_t *) __my_malloc(sizeof(struct dfparam_t));
 dfpp->dfpxlhs = NULL;
 dfpp->dfpxrhs = NULL;
 dfpp->dfp_grp = NULL;
 dfpp->dfp_in_mdp = NULL;
 dfpp->dfpfnam_ind = __cur_fnam_ind;
 dfpp->dfplin_cnt = __lin_cnt;
 dfpp->dfp_local = FALSE;
 dfpp->dfp_rooted = FALSE;
 dfpp->dfp_done = FALSE;
 dfpp->dfp_mustsplit = FALSE;
 dfpp->dfp_has_idents = FALSE;
 dfpp->dfp_in_gen = FALSE;
 dfpp->dfp_was_in_gen = FALSE;
 dfpp->dfp_gblk_in_pth = FALSE;
 dfpp->dfpnxt = NULL;

 dfpp->dfpiis = NULL;
 dfpp->last_dfpi = -1;
 dfpp->gdfpnam = NULL;
 dfpp->targsyp = NULL;
 dfpp->idntmastdfp = NULL;
 dfpp->idntnxt = NULL;
 dfpp->rooted_dfps = NULL;
 dfpp->dfptskp = NULL;
 return(dfpp);
}

/*
 * TASK DEFINITION ROUTINES
 * here because uses common declaration code
 */

/*
 * process a task definition
 * know task or function keyword read, reads the endtask
 * no F return on error, since either build d.s. or not
 */
static int32 rd_task(void)
{
 int32 is_auto, rv, save_lin_cnt, save_port_decls;
 struct st_t *stp;

 /* AIV 05/17/11 - need to save/restore port type local to this routine */
 /* failed if had function within list of port/decls  */
 save_port_decls = __lofp_port_decls;
 __lofp_port_decls = FALSE;
 save_lin_cnt = __lin_cnt;
 __get_vtok();
 /* AIV 04/06/10 - check if it is an automatic task */
 is_auto = FALSE;
 if (__toktyp == AUTOMATIC)
  {
   __design_has_auto_task = TRUE; 
   __rd_auto_task = TRUE;
   is_auto = TRUE;
   __get_vtok();
  }

 if (__toktyp != ID)
  {
   __pv_ferr(1130, "task name expected - %s read", __prt_kywrd_vtok());
sync_to_endtask:
   /* could change to dummy tsk name and continue here */
   /* but for now must find ENDTASK or skip to module level item */
   if (__vskipto_modend(ENDTASK)) 
    {
     __rd_auto_task = FALSE;
     __lofp_port_decls = save_port_decls;
     return(TRUE);
    }
   __syncto_class = SYNC_FLEVEL;
   __lofp_port_decls = save_port_decls;
   return(FALSE);
  }
 /* FALSE means previously defined - must not read */
 rv = __bld_tsk(__token, TASK, FALSE, FALSE);
 if (rv == 0) goto sync_to_endtask;

 __get_vtok();
 if (__toktyp == LPAR)
  {
   /* DPI export function can only declare name */
   if (__cur_dpip != NULL && __cur_dpip->dpi_type == DPI_EXPORT) 
    {
     __lofp_port_decls = save_port_decls;
     return(FALSE);
    }
   /* if couldn't sync to end of list of tf decls list ); */
   if (!rd_tf_list_of_ports_decl(__cur_tsk, "task", (rv == -1)))
    {
     switch ((byte) __syncto_class) {
      case SYNC_FLEVEL: case SYNC_MODLEVEL: 
       __rd_auto_task = FALSE;
       __lofp_port_decls = save_port_decls;
       return(FALSE);
      case SYNC_STMT: __get_vtok(); goto more_stmts;
      default: __case_terr(__FILE__, __LINE__);
     }
    }
   if (__toktyp == RPAR) __get_vtok();
  }
 
 /* AIV 01/26/11 - now emit warn for usage of automatic tasks - since */
 /* these can slow performance */
 if (is_auto)
  {
   __pv_fwarn(3156, "Task (%s) declared 'automatic' will slow simulation, do not use 'automatic' unless necessary.", __cur_tsk->tsksyp->synam);
  }

 /* AIV 04/06/10 - mark automatic task flag */
 __cur_tsk->is_auto = is_auto;
 /* first decl. type token read */
 /* if reading a DPI import/export task just read the header information */
 if (__cur_dpip != NULL) 
  {
   __cur_tsk->t_used = TRUE;
   __cur_tsk->tf_dpip = __cur_dpip;
   /* SJM 09-11-10 - must cross link dpi records and tasks */
   /* only used when the interpreter is run */
   __cur_dpip->dpi_tskp = __cur_tsk;

   __cur_dpip->dsym = __cur_tsk->tsksyp;
   __cur_tsk->tskst = NULL;
   __cur_tsk->tsk_last_lini = __lin_cnt;
   __cur_tsk->tsk_last_ifi = __cur_fnam_ind;
  }
 else
  {
   if (__toktyp != SEMI)
    {
     __pv_ferr(1131,
      "task declaration name not followed by semicolon - %s read",
      __prt_vtok());
    }
   else __get_vtok();
   if (!__rd_tfdecls("task")) 
    {
     __rd_auto_task = FALSE;
     __lofp_port_decls = save_port_decls;
     return(FALSE);
    }
more_stmts:
   /* AIV 11/01/10 - SV tasks no longer need to have begin/end for */
   /* stmts can just be a list of stmts */
   if (__sv_parse)
    {
     if (!__rd_lstofsts(ENDTASK, &stp, __lin_cnt, __cur_fnam_ind)) 
      {
       __lofp_port_decls = save_port_decls;
       return(FALSE);
      }
     __cur_tsk->tskst = stp;
    }
   else
    {
     if ((stp = __rd_stmt()) == NULL)
      {
       switch ((byte) __syncto_class) {
        case SYNC_FLEVEL: case SYNC_MODLEVEL: 
         __rd_auto_task = FALSE;
         __lofp_port_decls = save_port_decls;
         return(FALSE);
        case SYNC_STMT: __get_vtok(); goto more_stmts;
        case SYNC_TARG: break;
        default: __case_terr(__FILE__, __LINE__);
       }
      }
     /* only one task statement */
     __cur_tsk->tskst = stp;
     __get_vtok();
     if (__toktyp != ENDTASK)
      {
       __pv_ferr(1132, "endtask expected - %s read", __prt_vtok());
       /* must free task symbol table on error */
       if (__top_sti > 0) __top_sti = 0;
       /* this will sync to next module item if possible */
       __rd_auto_task = FALSE;
       __lofp_port_decls = save_port_decls;
       return(__vskipto_any(ENDTASK));
      }
    }
   __cur_tsk->tsk_last_lini = __lin_cnt;
   __cur_tsk->tsk_last_ifi = __cur_fnam_ind;

   __get_vtok();
   if (__toktyp == SEMI)
    __pv_ferr(999, "semicolon following endtask illegal"); 
   else __unget_vtok();
 }

 /* SJM 05-04-10 - now all tasks on gen blks tsk list - moving to */
 /* gen blocks as pseudo mod algorithm */
 if (__cur_cntxt_gblk != NULL)
  {
   if (__cur_cntxt_gblk->end_gblk_tsk == NULL)
    {
     __cur_cntxt_gblk->gblk_tsks = __cur_tsk;
    }
   else __cur_cntxt_gblk->end_gblk_tsk->tsknxt =  __cur_tsk;
   __cur_cntxt_gblk->end_gblk_tsk = __cur_tsk;
  }
 else
  {
   /* if error will not get linked in to module's task list */
   /* if rv is -1 then this is a export DPI task - which is already added */
   if (rv != -1)
    {
     if (__end_tbp == NULL) __inst_mod->mtasks = __cur_tsk;
     else __end_tbp->tsknxt = __cur_tsk;
     __end_tbp = __cur_tsk;
    }
  }

 /* symbols no longer accessible */
 __top_sti--;
 __rd_auto_task = FALSE;
 /* AIV 11/01/10 - if SV can now have endtask:name - task name must match : */
 if (__sv_parse && __cur_dpip == NULL)
  {
   __get_vtok();
   if (__toktyp == COLON)
    {
     __get_vtok();
     /* must be a block ID */
     if (__toktyp != ID)
      {
       __pv_ferr(4864, "endtask : [name] - missing task identifier - %s read", 
         __prt_vtok());
       __lofp_port_decls = save_port_decls;
       return(FALSE);
      }
     else if (strcmp(__cur_tsk->tsksyp->synam,  __token) != 0)
      {
       /* names must match */
       __pv_ferr(4865, "task name %s on line %d does not match endtask : %s - names must be the same", __cur_tsk->tsksyp->synam, save_lin_cnt, __token);
       __lofp_port_decls = save_port_decls;
       return(FALSE);
      }
    }
   else __unget_vtok();
  }
 __lofp_port_decls = save_port_decls;
 return(TRUE);
}

/*
 * build a task structure from declaration (label block/task/function)
 * expects task name and return task symbol - __cur_tsk set to inited task
 * notice that this does not link task into task chain
 *
 * SJM 04-13-10 - new algorithm for tasks/func/lbs in gen blocks - lbs
 * treated as normal since can never appear at top level of gen, not really
 * gened but task/funcs are - here just add to list build context later
 * when moved into mod
 */
extern int32 __bld_tsk(char *tnam, int32 tsktok, int32 auto_generated,
 int32 is_void_func)
{
 int32 tstyp;
 struct symtab_t *upsyt;
 struct sy_t *syp;
 struct dpi_t *dpip;
 struct task_t *tskp;
 char s1[RECLEN], s2[RECLEN], tnam2[RECLEN];

 /* AIV 10/13/10 - auto_generated block names start with $$ */
 if (*tnam == '$' && !auto_generated)
  {
   __pv_ferr(1133, "system function or task %s cannot be redefined", tnam);
   return(FALSE);
  }
 tstyp = __to_tasksytyp(tsktok);

 /* SJM 04-29-10 - tasks in gen blks need to use scope name */
 /* checking for name conflicts later */
 strcpy(tnam2, tnam);

 /* SJM 04-14-09 - for labeled block, may be declared in containing lb */
 /* sym tab */ 
 syp = __find_sym(tnam2);
 if (!__sym_is_new)
  {
   /* could be a define export stmt - this needs to read the body stmts */
   if (syp->sytyp == SYM_TSK)
    {
     tskp = syp->el.etskp;
     dpip = tskp->tf_dpip;
     if (dpip != NULL)
      {
       __cur_tsk = tskp;
       __venviron[++__top_sti] = __cur_tsk->tsksymtab;
       return(-1);
      }
    }
   /* if disable caused decl. as task, change to named block */
   if (syp->sytyp == SYM_TSK && tstyp == SYM_LB) syp->sytyp = SYM_LB;
   if (syp->sydecl || syp->sytyp != tstyp)
    {
     if (__cur_cntxt_gblk != NULL)
      {
       __pv_ferr(1134,
        "%s definition of \"%s\" in generate block %s illegal - previously defined as %s at %s",
        __get_vkeynam(s1, tsktok), __token, __cur_cntxt_gblk->gblknam,
        __to_sytyp(s2, syp->sytyp), __bld_lineloc(__xs, syp->syfnam_ind,
        syp->sylin_cnt));
      }
     else
      {
       __pv_ferr(1134,
        "%s definition of \"%s\" illegal - previously defined as %s at %s",
        __get_vkeynam(s1, tsktok), __token, __to_sytyp(s2, syp->sytyp),
        __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
      }
     return(FALSE);
    }
  }

 /* possibilities include named block fork and join */
 syp->sytyp = tstyp;
 __cur_tsk = alloc_task(syp);
 __cur_tsk->is_inter_blk = auto_generated;
 /* set flag for 'void function' */
 __cur_tsk->is_void_func = is_void_func;

 /* all different task types still point to etskp element */
 syp->el.etskp = __cur_tsk;
 syp->sydecl = TRUE;
 syp->syfnam_ind = __cur_fnam_ind;
 syp->sylin_cnt = __lin_cnt;

 /* SJM 01-26-09 - only const func info during src rd is def in gen bit */ 
 if (__cur_cntxt_gblk != NULL)
  {
   __cur_tsk->tsk_ingen = TRUE;
   __inst_mod->m_tfs_in_gblks = TRUE;
  }

 /* allocate the new symbol table */
 __cur_tsk->tsksymtab = __alloc_symtab(TRUE);
 __cur_tsk->tsktyp = tsktok;
 /* link symbol table to object it is symbol of */
 __cur_tsk->tsksymtab->sypofsyt = syp;
 /* set list ends for elements that must be kept in order */
 __end_tpp = NULL;
 __end_tskparamnp = NULL;
 __end_tsk_loc_paramnp = NULL;

 __venviron[++__top_sti] = __cur_tsk->tsksymtab;

 /* for not in gen blk, link in symbol table structure to mod's sym tab */
 /* for gen blk, link into containing */
 upsyt = __venviron[__top_sti - 1];
 __cur_tsk->tsksymtab->sytpar = upsyt;
 if (upsyt->sytofs == NULL) upsyt->sytofs = __cur_tsk->tsksymtab;
 /* link on front */
 else
  {
   __cur_tsk->tsksymtab->sytsib = upsyt->sytofs;
   upsyt->sytofs = __cur_tsk->tsksymtab;
  }

 return(TRUE);
}

/*
 * routine to bld the name of a labeled block in a gen init/always
 * for gen loop fixup still need all labeled blocks at top level at least
 * because of possible disables - use <gen blk scope>.<lab name>$<gblk index>
 */
extern char *__bld_gen_labnam(char *s, char *lbnam, struct genblk_t *gblkp)
{
 char s1[RECLEN];

 __bld_gen_scope_nam(s1, __cur_cntxt_gblk);
 /* 04-12-09 - need to make name unique in case multiple conditional gen */
 /* blks with same name - each gen blk has unique mod wide id> */ 
 sprintf(s, "%s.%s$%d", s1, lbnam, gblkp->gen_id); 
 return(s);
}

/*
 * convert one of the task token types to corresponding symbol type
 */
extern word32 __to_tasksytyp(int32 ttyp)
{
 int32 styp;

 styp = SYM_UNKN;
 switch (ttyp) {
  case TASK: styp = SYM_TSK; break;
  case FUNCTION: styp = SYM_F; break;
  case FORK: case Begin: styp = SYM_LB; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(styp);
}

/*
 * allocate a new task
 */
static struct task_t *alloc_task(struct sy_t *syp)
{
 struct task_t *tskp;

 tskp = (struct task_t *) __my_malloc(sizeof(struct task_t));
 init_task(tskp);
 tskp->tsksyp = syp;
 return(tskp);
}

/*
 * initialize a task 
 */
static void init_task(struct task_t *tskp)
{
 tskp->tsksyp = NULL;
 tskp->tsk_last_lini = -1;
 tskp->tsk_last_ifi = -1;
 tskp->tsktyp = UNDEF;
 tskp->t_used = FALSE;
 tskp->thas_outs = FALSE;
 tskp->thas_tskcall = FALSE;
 tskp->fhas_fcall = FALSE;
 tskp->can_be_disabled = FALSE;
 tskp->tf_lofp_decl = FALSE;
 tskp->tsk_ingen = FALSE;
 /* SJM 01-26-09 - new con func bits set by after all src read elab code */
 /* SJM 01-27-09 - assume know whether or not const func, unless explicityly */
 /* mark as unkn */
 tskp->unkn_if_con_func = FALSE;
 tskp->is_con_func = FALSE;
 tskp->is_cp_conf_image = FALSE;
 tskp->is_inter_blk = FALSE;
 tskp->is_void_func = FALSE;
 tskp->has_return = FALSE;
 tskp->is_auto = FALSE;
 tskp->tf_dpip = NULL;
 tskp->no_delay = TRUE;
 tskp->is_loaded = FALSE;
 tskp->is_printed = FALSE;
 tskp->uses_scope = FALSE;
 tskp->no_xmrcall = FALSE;
 tskp->tsksymtab = NULL;
 tskp->st_namblkin = NULL;
 tskp->tskpins = NULL;
 tskp->tsk_prms = NULL;
 tskp->tsk_locprms = NULL;
 tskp->tprmnum = 0;
 tskp->tlocprmnum = 0;
 tskp->tsk_regs = NULL;
 tskp->trnum = 0;
 tskp->cfu.to_exec_confunc = NULL;
 tskp->tskst = NULL;
 tskp->tsknxt = NULL;
 tskp->tthrds = NULL;
 tskp->t_idnum = -1;
 tskp->dsa_brk_ndx = -1;
 tskp->called_tasks = NULL;
}

/*
 * ROUTINES TO READ AND ADD LIST OF PORTS STYLE TASK/FUNC HEADER PORT DECLS 
 */

/*
 * read list of task/func header port declarations
 * new alternative ANSII style port header decl form added to 2001 LRM
 *
 * initial ( read and reads ending );
 * think now () form legal
 *
 * if return T, even if error parsing can continue in module
 * on error must sync to end of tf list of decls ')' - if not returns F
 * and sets sync class to right place to continue in t/f
 * may also sync to ; on error with T return
 */
static int32 rd_tf_list_of_ports_decl(struct task_t *tskp, char *tftypnam,
 int32 already_decl)
{
 int32 first_time, wtyp, ptyp, attr_ttyp, has_attr, is_signed;
 int32 i, dim;
 struct mda_t *mdap;
 struct sy_t *syp;
 struct net_t *np;
 struct expr_t *x1, *x2, *ox1, *ox2;
 struct expr_t *tab_of_ax1[MAX_ARRAY_DIM];
 struct expr_t *tab_of_ax2[MAX_ARRAY_DIM];
 struct expr_t *xm1, *xm2;
 struct task_pin_t *tpp;
 char s1[RECLEN];

 syp = NULL;
 is_signed = FALSE;
 ptyp = -1;
 /* even if syntax error, T once a port type keyword appears in hdr */
 tskp->tf_lofp_decl = TRUE;
 __lofp_port_decls = TRUE;

 __get_vtok();
 np = NULL;
 for (;;)
  {
   if (__toktyp == RPAR)
    {
     __pv_fwarn(3136,
      "%s %s header list of ports decl form - but list of ports empty",
      tftypnam, tskp->tsksyp->synam);
     /* assuming this forces list of ports header form */ 
     return(TRUE);
    }

   if (__toktyp != INPUT && __toktyp != OUTPUT && __toktyp != INOUT)
    {
     __pv_ferr(3422, "%s list of ports form port direction expected - %s read",
      tftypnam, __prt_kywrd_vtok());
     if (!__vskipto_lofp_end()) return(FALSE); 
     return(TRUE);
    }

   /* attribute collected by scanner - but need to save so associates with */
   /* right port */
   if (__attr_prefix)
    {
     __wrk_attr.attr_tok = __toktyp;
     __wrk_attr.attr_seen = TRUE;
     /* for now this is unparsed entire attr. string */
     __wrk_attr.attrnam = __pv_stralloc(__attrwrkstr);
     __wrk_attr.attr_fnind = __attr_fnam_ind;
     __wrk_attr.attrlin_cnt = __attr_lin_cnt;
    }
   else __wrk_attr.attr_seen = FALSE;

   attr_ttyp = __toktyp; 
   if (__toktyp == INPUT) ptyp = IO_IN;
   else if (__toktyp == OUTPUT) ptyp = IO_OUT;
   else if (__toktyp == INOUT) ptyp = IO_BID;
   else __case_terr(__FILE__, __LINE__); 

   __get_vtok();

   /* defaults to reg if net type omitted - can be var/reg type */
   if ((wtyp = __fr_wtnam(__toktyp)) != -1) __get_vtok();
   else wtyp = N_REG;

   /* SJM 07-30-10 - this is the default signedness */
   if (__is_int_atom_typ(wtyp) || __is_non_int_typ(wtyp)) is_signed = TRUE;
   else is_signed = FALSE;
   /* vectored or scalared keywords never appear in port decls */

   if (__toktyp == SIGNED)
    {
     if (wtyp == N_EVENT || __is_non_int_typ(wtyp))
      {
       __pv_ferr(3423,
        "signed keyword illegal in task/function list of ports declaration for type %s",
        __to_wtnam2(s1, wtyp));
      }
     else is_signed = TRUE;
     __get_vtok();
    }
   else if (__toktyp == UNSIGNED)
    {
     if (wtyp == N_EVENT || __is_non_int_typ(wtyp))
      {
       __pv_ferr(3423,
        "unsigned keyword illegal in task/function list of ports declaration for type %s",
        __to_wtnam2(s1, wtyp));
      }
     else is_signed = FALSE;
     __get_vtok();
    }

   /* even if error if 1 past ending ] continue */
   if (!rd_decl_rng(&ox1, &ox2, FALSE))
    {
     /* bad decl - but if sync to new I/O port direction, caller will cont */
     if (!__vskipto_lofp_end()) return(FALSE); 
     if (__toktyp == RPAR) return(TRUE); 
     /* semi read */
     return(TRUE);
    }

   /* use local has attr flag so can turn glb seen off before return */
   if (__wrk_attr.attr_seen)
    { has_attr = TRUE; __wrk_attr.attr_seen = FALSE; }
   else has_attr = FALSE;

   x1 = x2 = NULL;
   for (first_time = TRUE;;)
    {
     if (__toktyp != ID)
      {
       __pv_ferr(992,
        "%s header list of port form %s port name expected - %s read",
        tftypnam, __to_ptnam(s1, ptyp), __prt_kywrd_vtok());

       if (__vskipto2_lofp_end())
        {
         if (__toktyp == SEMI) return(TRUE);
         if (__toktyp == RPAR) { __get_vtok(); return(TRUE); }
         /* only other possibility is the port name separating comma */
         continue;
        }
       /* can't recover (resync) from error - synced to module item */
       return(FALSE);
      }

     /* if DPI of type export only task name has been declared */
     if (tskp->tf_dpip != NULL)
      {
       if (tskp->tf_dpip->dpi_type != DPI_EXPORT && already_decl) goto nxt_port;
      }

     /* SJM 05/25/04 - must just search for redeclare in tf sym tab */
     if ((syp = __get_sym(__token, __venviron[__top_sti])) != NULL)
      {
       __pv_ferr(3418,
        "%s header list of ports form %s port name %s redeclared", 
        tftypnam, __to_ptnam(s1, ptyp), __token);
       goto nxt_port;
      }

     if (first_time) { x1 = ox1; x2 = ox2; first_time = FALSE; } 
     else
      {
       if (x1 == NULL) x1 = x2 = NULL;
       else { x1 = __copy_expr(ox1); x2 = __copy_expr(ox2); }
      }

     /* first declare the port's wire/reg */
     /* if DPI export is already added just skip to next */
     if ((np = decl_taskvar(wtyp, x1, x2)) == NULL) goto nxt_port;

     /* if previously used will be treated as reg - must set to compatible */
     /* wire type if declared as time or int32 */
     syp = np->nsym;

     /* if saw an (* *) attribute for module item token, seen on */
     if (has_attr)
      {
       /* this add to net's attr list on end if also net decl first */
       add_net_attr(np, attr_ttyp);
      }

     /* SJM 10/02/03 - signed can be turned on either in port or wire decl */ 
     np->n_signed = is_signed;
     np->iotyp = ptyp;

     /* alloc port and add to end of list - order here crucial */
     tpp = alloc_tskpin();
     tpp->tpsy = syp;
     tpp->trtyp = ptyp;

     /* although with hdr list of ports form list known, for other form */
     /* don't know task/func ports until end of task/func */ 
     if (__end_tpp == NULL) __cur_tsk->tskpins = tpp;
     else __end_tpp->tpnxt = tpp;
     __end_tpp = tpp;

nxt_port:
     __get_vtok();
     if (__toktyp == RPAR) return(TRUE);

     /* allowing to pass entire array to DPI function */
     /* reading a DPI header if __cur_dpip not NULL */
     //AIV LOOKATME - this is same code as rd_vardecl - make this routine
     if (__cur_dpip != NULL)
      {
       xm1 = xm2 = NULL;
       if (!rd_decl_rng(&xm1, &xm2, TRUE))
        {
         if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
         if (__toktyp == SEMI) return(TRUE);
         __get_vtok();
        }
       if (xm1 != NULL)
        { 
         np->n_isarr = TRUE; 
         /* AIV 07/21/10 - this should have never turned these bits on for */
         /* arrays - now allowing dumping of arrays */
         /* AIV 01/23/11 - if is a wire array still dump since these are */
         /* turned into vectors later */
         if (__dmpvars_all && !__dump_arrays && !(np->ntyp < NONWIRE_ST))
          {
           np->dmpv_in_src = FALSE;
           np->nu.ct->dmpv_in_src = FALSE;
          }
         dim = 1;
         if (__toktyp != LSB)
          { 
           np->nu.ct->ax1 = xm1; 
           np->nu.ct->ax2 = xm2; 
          }
         else
          {
           tab_of_ax1[0] = xm1;
           tab_of_ax2[0] = xm2;
   
           /* get a mult-dimensional array decl */
           while (__toktyp == LSB)
            {
             /* check for max dimesions */
             if (dim == MAX_ARRAY_DIM)
              {
               __pv_ferr(3436,
                "array %s - cannot have more than %d dimensions", syp->synam, 
                MAX_ARRAY_DIM); 
               /* SJM 02-09-09 - must return and try to resync here */
               if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
               if (__toktyp == SEMI) return(TRUE);
               return(FALSE);
              }
             if (!rd_decl_rng(&xm1, &xm2, TRUE))
              {
               if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
               if (__toktyp == SEMI) return(TRUE);
               __get_vtok();
              }
             tab_of_ax1[dim] = xm1;
             tab_of_ax2[dim] = xm2;
             dim++;
            }
           /* alloc a multi-dim array info struct */
           mdap = (struct mda_t *) __my_malloc(sizeof(struct mda_t));
           /* SJM 01-17-08 alloc the two dim size array range expr ptr tabs */ 
           mdap->tab_ax1 = (struct expr_t **)
            __my_malloc(dim*sizeof(struct expr_t *));
           mdap->tab_ax2 = (struct expr_t **)
            __my_malloc(dim*sizeof(struct expr_t *));
   
           mdap->dimension = dim;
           mdap->rng1 = mdap->rng2 = NULL;
           mdap->ni1 = mdap->ni2 = -1;
           mdap->dim_mult = NULL;
           /* set the ranges for each dim */
           for (i = 0; i < dim; i++)
            {
             mdap->tab_ax1[i] = tab_of_ax1[i]; 
             mdap->tab_ax2[i] = tab_of_ax2[i]; 
            }
           np->mda = mdap;
          }
        }
       if (__toktyp == RPAR) return(TRUE);
      }

     if (__toktyp != COMMA)
      {
       __pv_ferr(995,
        "%s list of ports form declaration list comma or right paren expected - %s read",
        tftypnam, __prt_vtok());
       /* try to resync */
       if (!__vskipto_lofp_end()) return(FALSE); 
       if (__toktyp == COMMA) goto nxt_var;
       /* misplaced semi or sync to rpar */
       return(TRUE);
      }
nxt_var:
     __get_vtok();
     if (__toktyp == INPUT || __toktyp == OUTPUT || __toktyp == INOUT)  
      break;
    }
  }
 __misc_terr(__FILE__, __LINE__);
 return(TRUE);
}

/*
 * read task declarations
 * notice in any kind of task, function, or named block, decls come first
 * with one statement at end
 * expects first token to have been read and reads start of 1st statement
 */
extern int32 __rd_tfdecls(char *tftypnam)
{
 word32 wtyp, pntyp;

 for (;;)
  {
   /* routines called in switch expected to read ending ; or token */
   switch(__toktyp) {
    case TEOF:
     __pv_ferr(1135, "%s unexpected EOF", tftypnam);
     return(FALSE);
    case PARAMETER:
    case LOCALPARAM:
     /* this add to symbol table and list */
     /* notice for these, if error but synced to ;, still returns T */
     if (!rd_paramdecl(FALSE, (__toktyp == LOCALPARAM))) 
      {
tfdecl_sync:
       switch ((byte) __syncto_class) {
        case SYNC_FLEVEL: return(FALSE);
        case SYNC_MODLEVEL: break;
        /* statement follows task decls */
        case SYNC_STMT: return(TRUE);
        case SYNC_TARG: break;
        default: __case_terr(__FILE__, __LINE__);
       }
      }
     break;
    case INOUT:
     pntyp = IO_BID;
     goto decl_port;
    case OUTPUT:
     pntyp = IO_OUT;
     goto decl_port;
    case INPUT: 
     pntyp = IO_IN;
decl_port:
     if (!rd_taskvardecl(pntyp, TRUE, tftypnam)) goto tfdecl_sync;
     break;
    case REG:
     wtyp = N_REG;
do_tfwdecl:
     if (!rd_taskvardecl(wtyp, FALSE, tftypnam)) goto tfdecl_sync;
     break;
    case TIME: wtyp = N_TIME; goto do_tfwdecl;
    case INTEGER: wtyp = N_INT; goto do_tfwdecl;
    case REAL: case REALTIME: wtyp = N_REAL; goto do_tfwdecl;
    case BIT: wtyp = N_BIT; goto do_tfwdecl; 
    case BYTE: wtyp = N_BYTE; goto do_tfwdecl; 
    case INT: wtyp = N_CINT; goto do_tfwdecl; 
    case SHORTINT: wtyp = N_SHORTCINT; goto do_tfwdecl; 
    case LONGINT: wtyp = N_LONGCINT; goto do_tfwdecl; 
    case CHANDLE: wtyp = N_CHANDLE; goto do_tfwdecl; 
    case STRING: wtyp = N_STRING; goto do_tfwdecl; 
    case EVENT:
     if (!rd_eventdecl(TRUE)) goto tfdecl_sync;
     break;
    default:
     /* assume start of statement */
     goto decl_end;
   }
   __get_vtok();
  }
decl_end:
 return(TRUE);
}

/*
 * read and process a task reg/time/int/real declaration
 * know reg type read and reads final semi
 * for non new ascii declaration in header forms
 *
 * SJM 07-30-10 - new allow signed/unsigned code for SV
 */
static int32 rd_taskvardecl(int32 wtyp, int32 is_io, char *tftypnam)
{
 int32 decl_signed, is_signed, first_time, ttyp, has_attr, pntyp;
 struct sy_t *syp;
 struct net_t *np;
 struct task_pin_t *tpp;
 struct expr_t *x1, *x2, *ox1, *ox2, *xa1, *xa2;
 char s1[RECLEN], s2[RECLEN];

 ttyp = __toktyp;
 if (is_io)
  {
   pntyp = wtyp;
   __get_vtok();
   /* this emit error msg and returns -1 if error */
   if ((wtyp = __fr_wtnam(__toktyp)) != -1) __get_vtok();
   else wtyp = N_REG;
  }
 else
  {
   /* SJM 07-31-10 - keyword is wire type, code expects to read next */
   pntyp = NON_IO;
   __get_vtok();
  }
 /* wire types illegal in task var decl */
 if (wtyp == N_EVENT || wtyp < NONWIRE_ST)
  {
   __pv_ferr(1141,
    "task or function I/O port or variable declaration type %s illegal",
    __to_wtnam2(s1, wtyp));
   wtyp = N_REG;
  }

 /* set default signedness */ 
 if (__is_int_atom_typ(wtyp) || __is_non_int_typ(wtyp)) is_signed = TRUE;
 else is_signed = FALSE;

 decl_signed = FALSE; 
 if (__toktyp == SIGNED)
  {
   decl_signed = TRUE;
   is_signed = TRUE;
   __get_vtok();
  }
 else if (__toktyp == UNSIGNED)
  {
   decl_signed = TRUE;
   is_signed = FALSE;
   __get_vtok();
  }
   
 if (decl_signed && (__is_non_int_typ(wtyp) || wtyp == N_EVENT))
  {
   /* always will be signed - usually real for this */
   __pv_ferr(3423,
    "signed/unsigned keyword illegal for task or function declaration type %s",
    __to_wtnam2(s1, wtyp));
  }

 if (!rd_decl_rng(&ox1, &ox2, FALSE))
  {
   if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
   if (__toktyp == SEMI) return(TRUE);
   __get_vtok();
  }
 if (ox1 != NULL)
  {
   if (!__is_int_vec_typ(wtyp) && wtyp >= NONWIRE_ST)
    {
     __pv_ferr(1142, "%s %s %s vector range illegal", tftypnam,
      __to_wtnam2(s1, wtyp), __token);
     x1 = x2 = NULL;
    }
  }
 /* use local has attr flag so can turn glb seen of before return */
 if (__wrk_attr.attr_seen) { has_attr = TRUE; __wrk_attr.attr_seen = FALSE; }
 else has_attr = FALSE;
 for (first_time = TRUE;;)
  {
   if (__toktyp != ID)
    {
     __pv_ferr(1140, "%s declaration name of reg expected - %s read",
      tftypnam, __prt_kywrd_vtok());
bad_end:
     return(__vskipto_any(SEMI));
    }

   /* any port decl illegal - new ones or re-decls */
   if (__lofp_port_decls)
    {
     if (is_io)
      {
       __pv_ferr(3421,
       "port declaration of \"%s\" illegal - list of ports declaration form used",
       __prt_kywrd_vtok());
       /* if I/O decl, know read entire decl, i.e. can't be array */
       goto nxt_var; 
      }
     else
      {
       if (((syp = __get_sym_env(__token)) != NULL) && syp->sytyp == SYM_N
        && syp->el.enp->iotyp != NON_IO)
        {
         __pv_ferr(3421,
          "%s declaration of port \"%s\" illegal - %s uses list of ports declarations form",
          __to_wtnam2(s1, wtyp), __prt_kywrd_vtok(), tftypnam);

         /* here may need to skip the possible array decl */
         if (!__vskipto2_any(COMMA, SEMI)) return(FALSE); 
         if (__toktyp == SEMI) return(TRUE);
         goto nxt_var;
        }
      }
    }

   /* each time through need to call this to make copy */
   if (ox1 == NULL) __set_reg_widths(wtyp, &x1, &x2);
   else if (first_time) { x1 = ox1; x2 = ox2; first_time = FALSE; }
   else { x1 = __copy_expr(ox1); x2 = __copy_expr(ox2); }

   /* this handles all normal wire setting and checking */
   if ((np = decl_taskvar(wtyp, x1, x2)) == NULL)
    {     
     /* if no np, cannot read possible declaration - must skip over it */
     if (__toktyp == LSB)
      {
       if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
       if (__toktyp == SEMI) return(TRUE);
       __get_vtok();
      } 
     goto nxt_var;
    }
   syp = np->nsym;

   /* SJM - 03/20/00 - save reg decl attrs */
   /* if saw an (* *) attribute for module item token, seen on */
   if (has_attr) add_net_attr(np, ttyp);

   __get_vtok();
   /* notice task/function ports do not allow array syntax */
   /* also notice no strength or wire delay syntax */
   if (is_io) xa1 = xa2 = NULL;
   else
    {
     if (!rd_decl_rng(&xa1, &xa2, TRUE))
      {
       if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
       if (__toktyp == SEMI) return(TRUE);
       __get_vtok();
      }
     if (xa1 != NULL && wtyp == N_EVENT)
      {
       __pv_ferr(1143, "%s %s %s cannot be a array", tftypnam,
        __to_wtnam2(s1, wtyp), syp->synam);
       xa1 = xa2 = NULL;
      }
    }
   if (xa1 != NULL)
    { 
     np->n_isarr = TRUE; 
     /* AIV 03/09/11 - forgot to merge this from 4.xx */
     /* AIV 07/21/10 - this should have never turned these bits on for */
     /* arrays - now allowing dumping of arrays */
     /* AIV 01/23/11 - if is a wire array still dump since these are */
     /* turned into vectors later */
     if (__dmpvars_all && !__dump_arrays)  
      {
       np->dmpv_in_src = FALSE;
       np->nu.ct->dmpv_in_src = FALSE;
      }
     np->nu.ct->ax1 = xa1; 
     np->nu.ct->ax2 = xa2; 
    }
   np->n_signed = is_signed;

   if (is_io)
    {
     /* check for repeated I/O decls - wrong */
     if (np->iotyp != NON_IO)
      {
       if (np->iotyp == pntyp)
        {
         __pv_fwarn(574, "%s %s port declaration of \"%s\" repeated",
	  tftypnam, __to_ptnam(s1, pntyp), syp->synam);
	}
       else
        {
         __pv_ferr(1144, "%s %s port %s previously declared as %s port",
          tftypnam, __to_ptnam(s1, wtyp), syp->synam,
          __to_ptnam(s2, np->iotyp));
	 goto nxt_var;
        }
      }
     np->iotyp = pntyp;
     /* alloc port and add to end of list - order here crucial */
     tpp = alloc_tskpin();
     tpp->tpsy = syp;
     tpp->trtyp = pntyp;
     if (__end_tpp == NULL) __cur_tsk->tskpins = tpp;
     else __end_tpp->tpnxt = tpp;
     __end_tpp = tpp;
    }

nxt_var:
   if (__toktyp == SEMI) break;
   if (__toktyp != COMMA)
    {
     __pv_ferr(1145,
      "%s reg declaration list comma or semicolon expected - %s read",
      tftypnam, __prt_vtok());
     goto bad_end;
    }
   __get_vtok();
  }
 return(TRUE);
}

/*
 * add the task variable type decl. symbol and associated reg
 * caller must set reg type after checking for duplicates
 * returns null on error
 *
 * SJM 12-13-08 - task/func variable declarations always come before body
 * so this just works - declare in task scope - when reading t/f body
 * statement - will look first inside task scope variables and then
 * containing gen blk scopes and then module top level item symbol table
 *
 * SJM 08-01-10 - caller set signedness still
 */
static struct net_t *decl_taskvar(word32 wtyp, struct expr_t *x1,
 struct expr_t *x2)
{
 struct net_t *np;
 struct sy_t *syp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 syp = __decl_sym(__token, __venviron[__top_sti]);
 if (__sym_is_new)
  {
   np = __add_net(syp, __venviron[__top_sti]);
   np->iotyp = NON_IO;
   /* AIV 09/04/08 - wasn't setting the widths for inputs passed with type */
   /* function integer f(input integer number) */
   /* was setting wrong width/type for interger - was treating as scalar */
   /* if not vector this routine will leave x1 & x2 - NULL */
   if (x1 == NULL) 
    {
     __set_reg_widths(wtyp, &x1, &x2);
    }
   if (x1 != NULL)
    {
     np->nu.ct->n_rngknown = TRUE;
     np->n_isavec = TRUE;
     np->nu.ct->nx1 = x1;
     np->nu.ct->nx2 = x2;
    }
   np->ntyp = wtyp;

   /* SJM 08-04-10 - new 2 state var */
   if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;

   syp->sydecl = TRUE;
   /* even if used before, must set to declaration place */
   syp->syfnam_ind = __cur_fnam_ind;
   syp->sylin_cnt = __lin_cnt;
  }
 else
  {
   if (syp->sytyp != SYM_N)
    {
     __pv_ferr(1028,
      "cannot declare %s as %s - previously declared as %s at %s",
      syp->synam, __to_wtnam2(s2, wtyp), __to_wtnam2(s1, syp->sytyp),
      __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
     return(NULL);
    }
   /* wire/reg decl. after I/O decl. may set range */
   np = syp->el.enp;
   /* need special handling for I/O ports - declared in header, */
   /* I/O direction and maybe wire */
   if (np->iotyp != NON_IO)
    {
     /* task vars can be anthing providing output is lhs */
     /* this only has meaning for I/O port redecls */
     if (np->nu.ct->n_wirtypknown)
      {
       __pv_ferr(1146, "%s port %s previously declared as %s cannot be %s",
	__to_ptnam(s1, np->iotyp), syp->synam, __to_wtnam(s2, np),
	__to_wtnam2(s3, wtyp));
       /* must cause skipping because no np */
       return(NULL);
      }
    }
   else { if (is_decl_err(syp, SYM_N, wtyp)) return(NULL); }
   np->ntyp = wtyp;

   /* SJM 08-04-10 - new 2 state var */
   /* AIV 08/24/10 - wire type which isn't defined is first declared a reg */
   /* need to shut off the 2state bit */
   if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;
   else np->n_2state = FALSE;

   if (!chkset_wdrng(np, x1, x2)) return(NULL);
   np->nu.ct->n_wirtypknown = TRUE;

   /* if I/O decl follows reg decl, symbol uses I/O decl. place */
   if (np->iotyp != NON_IO)
    {
     syp->sydecl = TRUE;
     /* even if used before, must set to declaration place */
     syp->syfnam_ind = __cur_fnam_ind;
     syp->sylin_cnt = __lin_cnt;
    }
  }
 return(np);
}

/*
 * allocate a task pin (port) list element
 */
static struct task_pin_t *alloc_tskpin(void)
{
 struct task_pin_t *tpp;

 tpp = (struct task_pin_t *) __my_malloc(sizeof(struct task_pin_t));
 tpp->tpsy = NULL;
 tpp->trtyp = NON_IO;
 tpp->tpnxt = NULL;
 return(tpp);
}

/*
 * process a function definition
 * keyword function reads and reads decl. and final endfunction
 * no F return on error since either build d.s. or not
 *
 * SJM 08-01-10 - new 2 state net types added version - also changed 
 * so signed/unsigned(new) after automatic following LRM
 *
 * SV uses new 4 slot decl for function name (return) decl:
 * [optional auto/static][optional var type][optional sign/unsign][optional rng]
 * 5 P1364 LRM cases contained in these
 */
static int32 rd_func(void)
{
 int32 frwtyp, is_signed, is_auto, rv, save_lin_cnt, is_void, save_port_decls;
 struct st_t *stp;
 struct expr_t *x1, *x2;
 char s1[RECLEN];

 /* AIV 05/17/11 - need to save/restore port type local to this routine */
 /* failed if had function within list of port/decls  */
 save_port_decls = __lofp_port_decls;
 save_lin_cnt = __lin_cnt;
 __lofp_port_decls = FALSE;
 x1 = x2 = NULL;
 __get_vtok();

 /* SJM 08-01-10 - automatic keyword before type, signedness, rng etc. decls */
 /* AIV 04/06/10 - check if it is an automatic task */
 is_auto = FALSE;
 is_signed = FALSE;
 if (__toktyp == AUTOMATIC)
  {
   __design_has_auto_task = TRUE; 
   is_auto = TRUE;
   __get_vtok();
  }

 /* AIV 11/08/10 - 'void functions' no legal for SV - just skip return type */
 frwtyp = N_REG;
 if (__toktyp == VOID && __sv_parse) 
  {
   is_void = TRUE;
   __get_vtok();
  }
 else
  {
   is_void = FALSE;
   /* SJM 08-02-10 - variable type if present must come before signed */
   if ((frwtyp = __fr_wtnam(__toktyp)) == -1) frwtyp = N_REG;
   else
    {
     if (frwtyp == N_EVENT || frwtyp < NONWIRE_ST)
      {
       __pv_ferr(1141, "function cannot return type %s", __prt_vtok());
       frwtyp = N_REG;
      }
     __get_vtok();
    }

   /* set default signedness */ 
   if (__is_int_atom_typ(frwtyp) || __is_non_int_typ(frwtyp)) is_signed = TRUE;
   else is_signed = FALSE;
  
   if (__toktyp == SIGNED)
    {
     if (__is_non_int_typ(frwtyp))
      {
       __pv_ferr(3423,
        "signed keyword illegal when function declaration return type %s",
        __to_wtnam2(__xs, frwtyp));
      }
     else is_signed = TRUE;
     __get_vtok();
    }
   else if (__toktyp == UNSIGNED)
    {
     if (__is_non_int_typ(frwtyp))
      {
       __pv_ferr(3423,
        "unsigned keyword illegal when function declaration return type %s",
        __to_wtnam2(__xs, frwtyp));
      }
     else is_signed = FALSE;
     __get_vtok();
    }
  
   if (__toktyp == LSB)
    {
     if (!rd_decl_rng(&x1, &x2, FALSE))
      {
       if (!__vskipto2_any(SEMI, RSB)) 
        {
         __lofp_port_decls = save_port_decls;
         return(FALSE); 
        }
       if (__toktyp == SEMI) 
        {
         __lofp_port_decls = save_port_decls;
         return(TRUE);
        }
       __get_vtok();
      }
     if (!__is_int_vec_typ(frwtyp) && frwtyp >= NONWIRE_ST)
      {
       __pv_ferr(1142, "for function return type %s vector range illegal", 
        __to_wtnam2(s1, frwtyp));
       x1 = x2 = NULL;
      }
    } 
   else 
    {
     /* only vec types can be scalars with no internal range */
     if (!__is_int_vec_typ(frwtyp))
      {
       /* this build the range h:l (low is 0) exprs */
       __set_reg_widths(frwtyp, &(x1), &(x2));
      }
    }
  }

 if (__toktyp != ID)
  {
   __pv_ferr(1148, "function name expected - %s read", __prt_kywrd_vtok());
no_sym:
   if (__vskipto_modend(ENDFUNCTION)) 
    {
     __lofp_port_decls = save_port_decls;
     return(TRUE);
    }
   __syncto_class = SYNC_FLEVEL;
   __lofp_port_decls = save_port_decls;
   return(FALSE);
  }
 rv = __bld_tsk(__token, FUNCTION, FALSE, is_void);
 if (rv == 0) goto no_sym;
 
 /* AIV 04/06/10 - mark automatic task flag */
 /* AIV 01/26/11 - now emit warn for usage of automatic tasks - since */
 /* these can slow performance */
 if (is_auto)
  {
   __pv_fwarn(3157, "Function (%s) declared 'automatic' will slow simulation, do not use 'automatic' unless necessary.", __cur_tsk->tsksyp->synam);
  }
 __cur_tsk->is_auto = is_auto;

 add_funcretdecl(__token, (word32) frwtyp, x1, x2, is_signed);

 __get_vtok();
 if (__toktyp == LPAR)
  {
   /* DPI export function can only declare name */
   if (__cur_dpip != NULL && __cur_dpip->dpi_type == DPI_EXPORT) 
    {
     __lofp_port_decls = save_port_decls;
     return(FALSE);
    }
   /* if couldn't sync to end of list of tf decls list ); */
   if (!rd_tf_list_of_ports_decl(__cur_tsk, "function", (rv == -1)))
    {
     switch ((byte) __syncto_class) {
      case SYNC_FLEVEL: case SYNC_MODLEVEL: 
       __lofp_port_decls = save_port_decls;
       return(FALSE);
       break;
      case SYNC_STMT: __get_vtok(); goto more_stmts;
      default: __case_terr(__FILE__, __LINE__);
     }
    }
   if (__toktyp == RPAR) __get_vtok();
  }

 if (__cur_dpip != NULL) 
  {
   __cur_tsk->t_used = TRUE;
   __cur_tsk->tf_dpip = __cur_dpip;
   __cur_dpip->dsym = __cur_tsk->tsksyp;
   /* SJM 09-16-10 - was not setting dpi task back link for functions */
   __cur_dpip->dpi_tskp = __cur_tsk; 
   __cur_tsk->tskst = NULL;
  }
 else
  {
   if (__toktyp != SEMI)
    {
     __pv_ferr(1153,
      "function declaration name not followed by semicolon - %s read",
      __prt_vtok());
    }
   else __get_vtok();

   if (!__rd_tfdecls("function")) 
    {
     __lofp_port_decls = save_port_decls;
     return(FALSE); 
    }
more_stmts:
   /* AIV 11/01/10 - SV functions no longer need to have begin/end for */
   /* stmts can just be a list of stmts */
   if (__sv_parse)
    {
     if (!__rd_lstofsts(ENDFUNCTION, &stp, __lin_cnt, __cur_fnam_ind)) 
      {
       __lofp_port_decls = save_port_decls;
       return(FALSE);
      }
     __cur_tsk->tskst = stp;
    }
   else 
    {
     if ((stp = __rd_stmt()) == NULL)
      { 
       /* only get here on error */
       if (__toktyp == ENDFUNCTION)
        {
         __get_vtok();
         if (__toktyp == SEMI)
          __pv_ferr(999, "semicolon following endfunction illegal"); 
         else __unget_vtok();
         __lofp_port_decls = save_port_decls;
         return(TRUE);
        }
       switch ((byte) __syncto_class) {
        case SYNC_FLEVEL: case SYNC_MODLEVEL: 
         __lofp_port_decls = save_port_decls;
         return(FALSE);
         break;
        /* legally only 1 stmt - but try to parse all */
        case SYNC_STMT:
         __get_vtok();
         goto more_stmts;
        case SYNC_TARG: break;
        default: __case_terr(__FILE__, __LINE__);
       }
      }
     __cur_tsk->tskst = stp;
     __get_vtok();
     if (__toktyp != ENDFUNCTION)
      {
       __pv_ferr(1154, "endfunction expected - %s read", __prt_vtok());
       /* if missing endfunction, need to deallocate symbol table */
       if (__top_sti > 0) __top_sti = 0;
       __lofp_port_decls = save_port_decls;
       return(__vskipto_any(ENDFUNCTION));
      }
    }
  }
 /* set line of end */
 __cur_tsk->tsk_last_lini = __lin_cnt;
 __cur_tsk->tsk_last_ifi = __cur_fnam_ind;

 /* SJM 05-04-10 - now all tasks on gen blks tsk list - moving to */
 /* gen blocks as pseudo mod algorithm */
 if (__cur_cntxt_gblk != NULL)
  {
   if (__cur_cntxt_gblk->end_gblk_tsk == NULL)
    {
     __cur_cntxt_gblk->gblk_tsks = __cur_tsk;
    }
   else __cur_cntxt_gblk->end_gblk_tsk->tsknxt =  __cur_tsk;
   __cur_cntxt_gblk->end_gblk_tsk = __cur_tsk;
  }
 else
  {
   /* if error will not get linked in to module's task list */
   /* notice functions get linked in task order on module task list */
   /* if rv is -1 then this is a export DPI task - which is already added */
   if (rv != -1)
    {
     if (__end_tbp == NULL) __inst_mod->mtasks = __cur_tsk;
     else __end_tbp->tsknxt = __cur_tsk;
     __end_tbp = __cur_tsk;
    }
  }
  
 /* symbols no longer accessible */
 __top_sti--;
 /* AIV 11/01/10 - if SV can now have endfunction:name - name must match : */
 if (__sv_parse && __cur_dpip == NULL)
  {
   __get_vtok();
   if (__toktyp == COLON)
    {
     __get_vtok();
     /* must be a block ID */
     if (__toktyp != ID)
      {
       __pv_ferr(4866, "endfunction : [name] - missing task identifier - %s read", 
         __prt_vtok());
       __lofp_port_decls = save_port_decls;
       return(FALSE);
      }
     else if (strcmp(__cur_tsk->tsksyp->synam,  __token) != 0)
      {
       /* names must match */
       __pv_ferr(4867, "function name %s on line %d does not match endfunction : %s - names must be the same", __cur_tsk->tsksyp->synam, save_lin_cnt, __token);
       __lofp_port_decls = save_port_decls;
       return(FALSE);
      }
    }
   else __unget_vtok();
  }
 __lofp_port_decls = save_port_decls;
 return(TRUE);
}

/*
 * add implicit first output port return value decl. to task d.s.
 */
static void add_funcretdecl(char *rvnam, word32 frwtyp, struct expr_t *x1,
 struct expr_t *x2, int32 is_signed)
{
 struct sy_t *syp;
 struct net_t *np;
 struct task_pin_t *tpp;

 /* notice symbol already in one up task decl. also name of port */
 syp = __decl_sym(rvnam, __venviron[__top_sti]);
 /* function declaration symbol table inconsisent */
 if (!__sym_is_new) __misc_fterr(__FILE__, __LINE__);

 np = __add_net(syp, __venviron[__top_sti]);
 if (x1 != NULL)
  {
   np->nu.ct->n_rngknown = TRUE;
   np->n_isavec = TRUE;
   np->nu.ct->nx1 = x1;
   np->nu.ct->nx2 = x2;
  }
 np->iotyp = IO_OUT;
 np->ntyp = frwtyp;

 /* SJM 08-04-10 - new 2 state var */
 if (__is_2state_typ(np->ntyp)) np->n_2state = TRUE;

 np->nu.ct->n_rngknown = TRUE;
 np->nu.ct->n_iotypknown = TRUE;
 np->nu.ct->n_wirtypknown = TRUE;
 np->n_signed = is_signed;

 syp->sydecl = TRUE;
 syp->syfnam_ind = __cur_fnam_ind;
 syp->sylin_cnt = __lin_cnt;

 /* alloc port and add to end of list - order here crucial */
 tpp = alloc_tskpin();
 tpp->tpsy = syp;
 tpp->trtyp = IO_OUT;
 if (__end_tpp == NULL) __cur_tsk->tskpins = tpp;
 else __end_tpp->tpnxt = tpp;
 __end_tpp = tpp;
}

/*
 * INSTANCE READING ROUTINES
 */

/*
 * [module type] [# param list] [inst] ([mod connections]) ;
 * [udp/prim type] [strength] [#param list] [inst] ([prim. conn.]);
 */

/*
 * read an instance - treat as if not yet defined or resolved
 * module type name read, reads final ;
 * at this point do not know if instance, gate or udp
 * return F if synced to next mod/prim else T if synced to ; even if err
 */
static int32 rd_inst(char *typnam)
{
 int32 first_time, has_iname, strenval, has_attr;
 struct cell_t *cp;
 struct sy_t *syp;
 struct tnode_t *tnp;
 struct namparam_t *nprmhdr; 
 struct expr_t *x1, *x2;
 char s1[IDLEN];

 nprmhdr = NULL;
 first_time = TRUE;
 __v0stren = __v1stren = NO_STREN;
 has_iname = TRUE;
 x1 = x2 = NULL;

 /* must go here because for gate maybe no inam */
 /* use local has attr flag so can turn glb seen of before return */
 if (__wrk_attr.attr_seen) { has_attr = TRUE; __wrk_attr.attr_seen = FALSE; }
 else has_attr = FALSE;

 if (*typnam == '$')
  {
   __pv_ferr(1042,
   "instance/gate type \"%s\" cannot begin with $ - reserved for system tasks",
    typnam);
bad_end:
   return(__vskipto_any(SEMI));
  }
 __get_vtok();
 if (__toktyp == LPAR)
  {
   __get_vtok();
   if (is_tokstren(__toktyp) == NO_STREN)
    {
     sprintf(s1, "__gate$$%d", __cp_num);
     has_iname = FALSE;
     goto no_inam;
    }
   /* need special strength read routine for pull */
   if (strcmp(typnam, "pullup") == 0 || strcmp(typnam, "pulldown") == 0)
    {
     if (!rd_pull_stren(typnam, &strenval)) goto bad_stren;

     /* here syntax good but strength values illegal - assume strong */
     /* error already emitted */
     if (strenval == NO_STREN)
      {
       if (strcmp(typnam, "pullup") == 0) strenval = STRONG1;
       else strenval = STRONG0;
      }
     /* LOOKATME - both strength must be same and right selected one */
     /* since simualtion uses low 3 bits of strength value */ 
     __v0stren = __v1stren = strenval;  
     __get_vtok();
     goto rd_parms;
    }

   if (!rd_verstrens())
    {
bad_stren:
     if (!__vskipto2_any(RPAR, SEMI)) return(FALSE);
     if (__toktyp == RPAR) { __get_vtok(); goto rd_parms; }
     /* bad strengths do not provide any punctuation to sync to */
     return(TRUE);
    }
  }

rd_parms:
 if (__toktyp == SHARP)
  {
   if ((nprmhdr = rd_npndparams()) == NULL) goto bad_end;
  }
 else nprmhdr = NULL;

 for (;;)
  {
   if (__toktyp == LPAR)
    {
     /* name is [module name]$[unique number] */
     sprintf(s1, "__gate$$%d", __cp_num);
     has_iname = FALSE;
    }
   else
    {
     if (__toktyp != ID)
      {
       __pv_ferr(1043, "instance/gate name for type \"%s\" expected - %s read",
        typnam, __prt_kywrd_vtok());
       /* resyncing of comma list of same type insts not port lists */ 
       if (!__vskipto2_any(COMMA, SEMI)) return(FALSE); 
       if (__toktyp == SEMI) return(TRUE);
       __get_vtok();
       continue;
      }
     strcpy(s1, __token);
     __get_vtok();
     /* new arrays of gates/instances [h:l] becomes "_"[number] suffix later */
     /* if no range, this just returns T and sets x1 and x2 to nil */
     /* if range, sets x1, x2 and reads one past ] */
     if (!rd_decl_rng(&x1, &x2, FALSE))
      {
       if (!__vskipto2_any(SEMI, RSB)) return(FALSE); 
       if (__toktyp == SEMI) return(TRUE);
       __get_vtok();
      }
     if (__toktyp != LPAR)
      {
       __pv_ferr(1044,
        "instance/gate \"%s\" type \"%s\" connection list expected - %s read",
  	s1, typnam, __prt_vtok());
        goto bad_end;     
      }
    }
   __get_vtok();
no_inam:
   /* if port errors just inst. with no ports */
   if ((cp = add_cell(s1)) != NULL)
    {
     /* no checking for type sep. name space - if never decled err later */
     tnp = __vtfind(typnam, __modsyms);
     if (__sym_is_new)
      {
       __add_sym(typnam, tnp);
       (__modsyms->numsyms)++;
       syp = tnp->ndp;
       syp->sytyp = SYM_M;
       /* getting here means module/udp referenced before defined */
       /* and only place mod/udp can be seen */
       __add_syp_to_undefs(syp);
      }
     else syp = tnp->ndp;
     /* AIV 06/01/04 - mark all as not in config - config processing */ 
     /* will mark as true later */ 
     syp->cfg_needed = FALSE;
     /* instance must be named, error caught only after lib. processed */
     /* using inst. num that is unused until design wide checking */
     if (has_iname) cp->c_named = TRUE;
     if (x1 != NULL) { cp->cx1 = x1; cp->cx2 = x2; } 

     cp->cmsym = syp;
     if (first_time) cp->c_nparms = nprmhdr;
     else cp->c_nparms = copy_namparamlst(nprmhdr);
     if (__v0stren != NO_STREN) 
      {
       cp->c_hasst = TRUE;
       cp->c_stval = ((__v0stren << 3) | __v1stren) & 0x3f;
      }
    }
   /* if synced to ;, T even if errors */ 
   if (!rd_iports(s1)) return(TRUE);
   if (cp != NULL) cp->cpins = __cphdr;

   /* if saw an (* *) attribute for module item token, seen on */
   if (has_attr)
    {
     if (cp != NULL) add_cell_attr(cp);
    }

   __get_vtok();
   if (__toktyp == SEMI) break;
   first_time = FALSE;
   if (__toktyp == COMMA) { __get_vtok(); continue; }

   __pv_ferr(1048,
   "instance or gate terminal list ending semicolon or comma missing - %s read",
    __prt_vtok());
   /* must find a semi to continue */
   goto bad_end;
  }
 return(TRUE);
}

/*
 * add an inst attribute 
 */
static void add_cell_attr(struct cell_t *cp)
{
 /* DBG remove -- */
 if (cp->cattrs != NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* need to set token type so each parsed attr_spec has right tok type */
 __wrk_attr.attr_tok = MODULE;

 /* return nil on error */
 cp->cattrs = __rd_parse_attribute(&__wrk_attr);
 /* SJM 07/30/01 - this is work read value, but now done with it */
 __my_free(__wrk_attr.attrnam, __attr_line_len + 1);
 __wrk_attr.attr_seen = FALSE;
}

/*
 * read the pull strength
 * know leading '(' and strength read, reads optional second , stren and
 * then ending ')' or just ending ')'
 * on F return trys to sync to ending ')' or ';'
 *
 * SJM 10/01/99 - allow both 0 and 1 strength where unused one dropped 
 * required by 1999 LRM
 *
 * where two strengths given, drops unused one here
 * know ehen called first token is some kind of strength
 */
static int32 rd_pull_stren(char *pullnam, int32 *strenval)
{
 int32 st1typ, st1val, st2val, st2typ, err_seen; 
 int32 strentyp, strenval1, strenval2;

 err_seen = FALSE;
 st1typ = st2typ = strentyp = NO_STREN;
 st1val = st2val = TOK_NONE;
 *strenval = NO_STREN;
 /* know 1st required */
 st1val = __toktyp;
 if ((st1typ = is_tokstren(__toktyp)) == CAP_STREN || st1typ == NO_STREN)
  {
   __pv_ferr(1032, "%s strength %s non driving or illegal", pullnam,
    __prt_vtok());  
   st1typ = NO_STREN;
   err_seen = TRUE;
  }

 __get_vtok();
 if (__toktyp == COMMA)
  {
   /* second strength present */
   __get_vtok();
   st2val = __toktyp;
   if ((st2typ = is_tokstren(__toktyp)) == CAP_STREN || st2typ == NO_STREN)
    {
     __pv_ferr(1032, "%s second strength %s non driving or illegal", pullnam,
      __prt_vtok());  
     st2typ = NO_STREN;
     err_seen = TRUE;
    }
   __get_vtok();
  }
 if (__toktyp != RPAR)
  {
   __pv_ferr(1031, "%s strength ending ')' expected - %s read", pullnam,
    __prt_vtok());
   return(FALSE);
  }
 if (err_seen) return(TRUE);

 /* know one or two strengths read and legal */
 /* case 1: old only one strength form - check to make sure right type */
 if (st2typ == NO_STREN)
  {
   strentyp = st1typ; 
   /* map from strength token to strength constant value */
   *strenval = __fr_stren_nam(st1val);
   if (strcmp(pullnam, "pullup") == 0)
    {
     if (strentyp == LOW_STREN) 
      {
       __pv_fwarn(608,
        "%s single strength form low (0) strength %s should be high (1) - changed", 
        pullnam, __to1_stren_nam(__xs, *strenval, st1typ));
      }
    } 
   else
    {
     if (strentyp == HIGH_STREN) 
      {
       __pv_fwarn(608,
        "%s single strength form high (1) strength %s should be low (0) - changed", 
        pullnam, __to1_stren_nam(__xs, *strenval, st1typ));
      }
    }
   if (*strenval == ST_HIGHZ)
    {
     __pv_ferr(1018,
      "highz strength illegal for single strength form %s gate",
      pullnam);
     strentyp = NO_STREN;
     *strenval = NO_STREN;
    }
   return(TRUE);
  }
 /* case 2 */
 /* make sure not both 0 strens and not both 1 strens */
 if (st1typ == LOW_STREN && st2typ == LOW_STREN)
  {
   __pv_ferr(1032, "%s two strength form both strengths low (0)", pullnam);
   return(TRUE);
  }
 if (st1typ == LOW_STREN && st2typ == LOW_STREN)
  {
   __pv_ferr(1032, "%s two strength form both strengths high (1)", pullnam);
   return(TRUE);
  }
 /* map from strength token to strength constant value for both */
 strenval1 = __fr_stren_nam(st1val);
 strenval2 = __fr_stren_nam(st2val);
 if (strenval1 == ST_HIGHZ || strenval2 == ST_HIGHZ)
  {
   __pv_ferr(1018, "highz strength illegal as either strength for %s gate",
    pullnam);
   strentyp = NO_STREN;
   *strenval = NO_STREN;
   return(TRUE);
  }
 /* select right strength from two */
 if (strcmp(pullnam, "pullup") == 0)
  {
   if (st1typ == LOW_STREN) *strenval = strenval2; else *strenval = strenval1;
  }
 else
  {
   if (st1typ == HIGH_STREN) *strenval = strenval2; else *strenval = strenval1;
  }
 return(TRUE);
}

/*
 * read a new style instance only old implicit or new explicit param form
 *
 * know # read and reads one past list ending ) - maybe only one and no ()
 * must also read new style for gates since until types resolved do not
 * know if gate or instance - error during fixup in new style for gate/udp
 */
static struct namparam_t *rd_npndparams(void)
{
 int32 prm_err;
 struct namparam_t *npmphdr, *npmp, *last_npmp;

 __get_vtok();
 /* case 1: old #[one token] case */
 if (__toktyp != LPAR)
  {
   /* notice must surround m:t:m with () */
   if (__toktyp != ID && __toktyp != NUMBER && __toktyp != REALNUM)
    {
     __pv_ferr(1049,
     "non parenthesized pound parameter one element identifier or number expected - %s read",
      __prt_kywrd_vtok());
     return(NULL);
    }
   __last_xtk = -1;
   /* on error, set as error expr. - maybe since param should be 0 */
   if (!__bld_expnode()) __set_xtab_errval();
   /* here does the allocating */
   __bld_xtree(0);
   npmphdr = __alloc_namparam();
   npmphdr->pxndp = __root_ndp;
   npmphdr->prmfnam_ind = __cur_fnam_ind;
   npmphdr->prmlin_cnt = __lin_cnt;
   __get_vtok();
   return(npmphdr);
  }
 
 /* case 2: #(...) - either , list (no empties) or explicit form */
 for (npmphdr = NULL, last_npmp = NULL, prm_err = FALSE;;)
  {
   __get_vtok();

   /* read the pound parameter (maybe new explicit form) and one token past */
   /* illegal forms caught during fix up */
   if ((npmp = rd1_namedparam()) == NULL) goto bad_skipend;
   if (npmphdr == NULL) npmphdr = npmp; else last_npmp->nprmnxt = npmp;
   last_npmp = npmp;

   if (__toktyp == RPAR) break;
   if (__toktyp == COMMA) continue;

   __pv_ferr(1051, "pound parameter list comma or ) expected - %s read ",
    __prt_vtok());

bad_skipend:
   prm_err = TRUE;
   if (!__vskipto3_any(RPAR, COMMA, SEMI)) return(FALSE); 
   if (__toktyp == COMMA) { __get_vtok(); continue; }
   /* if ) or ; done and synced to right place */
   if (__toktyp == SEMI) __unget_vtok();
   break;
  }
 __get_vtok();

 if (prm_err)
  {
   if (npmphdr != NULL) __free_namedparams(npmphdr);
   return(NULL);
  }
 return(npmphdr);
}

/*
 * read one instance (cell) or gate param (may have new named form)
 *
 * know 1st token read and reads punctuation after , or )
 * returns built named param record 
 *
 * on error returns nil, caller (not in this routine) tries to resync
 * on , and read next param * but on .[id](<some error> ..., this trys
 * to resync to list ending ) 
 *
 * LOOKATME - allowing ,, form
 */
static struct namparam_t *rd1_namedparam(void)
{
 int32 namedparam_form, slcnt, sfnind;
 struct namparam_t *npmp;
 char nam[IDLEN];

 slcnt = __lin_cnt;
 sfnind = __cur_fnam_ind;
 if (__toktyp == DOT)
  {
   __get_vtok();
   if (__toktyp != ID)
    {
     __pv_ferr(1052, "name of pound param expected - %s read",
      __prt_kywrd_vtok());
     return(NULL);
    }
   strcpy(nam, __token);
   __get_vtok();
   if (__toktyp != LPAR)
    {
     __pv_ferr(1053,
      "pound param explicitly named form left parenthesis expected - %s read",
      __prt_vtok());
     return(NULL);
    }
   /* 1st token in expr. must be read */
   __get_vtok();
   /* explicit param name .[param]() for unc. is legal */
   if (__toktyp == RPAR)
    {
     __last_xtk = 0;
     __set_opempty(0);
    }
   else
    {
     /* need to collect delay expr. because min-typ-max without () ok */
     if (!__col_delexpr(TRUE)) return(NULL);
    }
   namedparam_form = TRUE;
  }
 else
  {
   namedparam_form = FALSE;
   /* (, - ,, and ,) all legal */
   if (__toktyp == COMMA || __toktyp == RPAR)
    {  __last_xtk = 0; __set_opempty(0); }
   else
    {
     /* need to collect delay expr. because min-typ-max without () ok */
     if (!__col_delexpr(TRUE)) return(NULL);
    }
  }
 /* build the tree, copy/allocate nodes, sets __root_ndp to its root */
 /* this must be a constant expr but checked later - this will decl */
 __bld_xtree(0);

 if (namedparam_form)
  {
   if (__toktyp != RPAR)
    {
     __pv_ferr(1055,
      "explicitly named pound param form right parenthesis expected - %s read",
      __prt_vtok());
     return(NULL);
    }
   __get_vtok();
   /* LOOKATME - why is this check here - think no longer needed */
   /* but catching user or PLI sys function here does not hurt */
   if (__root_ndp->optyp == FCALL )
    {
     struct sy_t *syp; 

     /* only built in sysfuncs allowed - const args checked later */
     syp = __root_ndp->lu.x->lu.sy;
     if (syp->sytyp == SYM_SF && syp->el.esyftbp->tftyp == SYSF_BUILTIN)
      goto named_ok;

     __pv_ferr(1055,
      "explicitly named pound param %s illegal -  not required .[name]([value])",
      __msgexpr_tostr(__xs, __root_ndp));
     return(NULL);
    }
  }
named_ok:
 npmp = __alloc_namparam();
 npmp->pxndp = __root_ndp;
 if (namedparam_form) npmp->pnam = __pv_stralloc(nam);
 else npmp->pnam = NULL;
 npmp->prmfnam_ind = sfnind;
 npmp->prmlin_cnt = slcnt;
 return(npmp);
}

/*
 * free list of named param records
 */
extern void __free_namedparams(struct namparam_t *npmphdr)
{
 int32 slen;
 struct namparam_t *npmp, *npmp2;

 for (npmp = npmphdr; npmp != NULL;)
  {
   npmp2 = npmp->nprmnxt;
   
   /* expr. may be nil, when freeing after expr. copied */
   if (npmp->pxndp != NULL) __free_xtree(npmp->pxndp);
   if (npmp->pnam != NULL)
    {
     slen = strlen(npmp->pnam);
     __my_free(npmp->pnam, slen + 1); 
    }
   __my_free(npmp, sizeof(struct namparam_t));

   npmp = npmp2;
  }
}

/*
 * add module symbol (possibly later changed to udp) to undef list
 */
extern void __add_syp_to_undefs(struct sy_t *syp)
{
 struct undef_t *undefp;

 undefp = (struct undef_t *) __my_malloc(sizeof(struct undef_t));
 undefp->msyp = syp;
 undefp->undefnxt = NULL;
 undefp->dfi = -1;
 undefp->modnam = NULL; 
 syp->syundefmod = TRUE;
 syp->el.eundefp = undefp;
 
 if (__undeftail == NULL)
  {
   __undeftail = __undefhd = undefp;
   undefp->undefprev = NULL;
  }
 else 
  {
   undefp->undefprev = __undeftail;
   __undeftail->undefnxt = undefp;
   __undeftail = undefp;
  } 
 __undef_mods++;
}

/*
 * copy possibly named param list 
 *
 * only needed during instance reading because converted to dellst form
 * when module copying needed
 */
static struct namparam_t *copy_namparamlst(struct namparam_t *old_npmp)  
{
 struct namparam_t *npmphdr, *npmp, *onpmp, *last_npmp;
 
 if (old_npmp == NULL) return(NULL);

 npmphdr = NULL;
 last_npmp = NULL;
 for (onpmp = old_npmp; onpmp != NULL; onpmp = onpmp->nprmnxt)
  {
   npmp = (struct namparam_t *) __my_malloc(sizeof(struct namparam_t));
   /* since mallocing, need to fill all fields */
   npmp->prmfnam_ind = onpmp->prmfnam_ind;
   npmp->prmlin_cnt = onpmp->prmlin_cnt;
   npmp->pxndp = __copy_expr(onpmp->pxndp);
   if (onpmp->pnam != NULL) npmp->pnam = __pv_stralloc(onpmp->pnam);
   else npmp->pnam = NULL;
   npmp->nprmnxt = NULL;

   if (last_npmp == NULL) npmphdr = npmp; else last_npmp->nprmnxt = npmp;
   last_npmp = npmp;
  }
 return(npmphdr);
}

/*
 * allocate and initialize a inst/gate pound param record
 */
extern struct namparam_t *__alloc_namparam(void)
{
 struct namparam_t *npmp;

 npmp = (struct namparam_t *) __my_malloc(sizeof(struct namparam_t));
 npmp->pxndp = NULL;
 npmp->prmfnam_ind = 0;
 npmp->prmlin_cnt = -1;
 npmp->pnam = NULL;
 npmp->nprmnxt = NULL;
 return(npmp);
}

/*
 * make a copy of a param list
 * know at copy point delay is DT_CMPLST list
 */
extern struct paramlst_t *__copy_dellst(struct paramlst_t *oplp)
{
 struct paramlst_t *plp, *nplphdr, *nplp, *last_nplp;

 if (oplp == NULL) return(NULL);

 nplphdr = NULL;
 for (last_nplp = NULL, plp = oplp; plp != NULL; plp = plp->pmlnxt)
  {
   nplp = __alloc_pval();
   nplp->plxndp = __copy_expr(plp->plxndp);
   if (last_nplp == NULL) nplphdr = nplp; else last_nplp->pmlnxt = nplp;
   nplp->pmlnxt = NULL;
   last_nplp = nplp;
  }
 return(nplphdr);
}

/*
 * read instance ports - probably no module def. at this point
 * know 1st token of port expr. read and reads final )
 */
static int32 rd_iports(char *inam)
{
 for (__cphdr = NULL;;)
  {
   /* read the cell-pin reference and one token past */
   /* illegal forms caught during fix up */
   if (!rd_cpin_conn()) goto bad_trynxt;

   if (__toktyp == RPAR) break;
   if (__toktyp == COMMA) { __get_vtok(); continue; }
   __pv_ferr(1051,
    "instance/gate %s port connection list comma or ) expected - %s read ",
    inam, __prt_vtok());

bad_trynxt:
   if (!__vskipto3_any(RPAR, COMMA, SEMI)) return(FALSE); 
   if (__toktyp == COMMA) { __get_vtok(); continue; }
   /* if ) or ; done and synced to right place */
   if (__toktyp == SEMI) __unget_vtok();
   break;
  }
 return(TRUE);
}

/*
 * read an instance port connection
 * know 1st token read and reads punctuation after , or )
 * then adds to end of global cell pin list header __cphdr
 *
 * on error returns F, caller tries to resync on , and read next port
 * but on .[id](<some error> ..., this trys to resync to port ending ) 
 */
static int32 rd_cpin_conn(void)
{
 int32 namedport_form;
 struct cell_pin_t *cpp;

 if (__toktyp == DOT)
  {
   __get_vtok();
   if (__toktyp != ID)
    {
     __pv_ferr(1052,
      "instance/gate connection name of port expected - %s read",
      __prt_kywrd_vtok());
     return(FALSE);
    }
   strcpy(__portnam, __token);
   __get_vtok();
   if (__toktyp != LPAR)
    {
     __pv_ferr(1053,
      "explicit port name form left parenthesis expected - %s read",
      __prt_vtok());
     return(FALSE);
    }
   /* 1st token in expr. must be read */
   __get_vtok();
   /* instance connection .[port]() for unc. is legal */
   if (__toktyp == RPAR)
    {
     __last_xtk = 0;
     __set_opempty(0);
     /* need to leave right paren in token since checked for later */
    }
   else
    {
     if (!__col_parenexpr(-1, FALSE, FALSE)) 
      {
       /* if can resync to ) move to next tok - then caller resyncs again */
       if (__vskipto_modend(RPAR)) __get_vtok();
       return(FALSE);
      }
    }
   namedport_form = TRUE;
  }
 else
  {
   namedport_form = FALSE;
   /* (, - ,, and ,) all legal */
   if (__toktyp == COMMA || __toktyp == RPAR)
    {  __last_xtk = 0; __set_opempty(0); }
   else { if (!__col_connexpr(-1)) return(FALSE); }
  }
 /* this declares undeclared wire */
 /* build the tree, copy/allocate nodes, sets __root_ndp to its root */
 __bld_xtree(0);

 if (namedport_form)
  {
   if (__toktyp != RPAR)
    {
     __pv_ferr(1055,
      "instance explicit named port form right parenthesis expected - %s read",
      __prt_vtok());
     if (__vskipto_modend(RPAR)) { __get_vtok(); return(TRUE); } 
     return(FALSE);
    }
   __get_vtok();
  }
 /* this save the global portnam as a string if present */
 cpp = __alloc_cpin(namedport_form);
 cpp->cpxnd = __root_ndp;
 if (__cphdr == NULL) __cphdr = cpp; else __cpp_last->cpnxt = cpp;
 __cpp_last = cpp;

 return(TRUE);
}

/*
 * allocate a cell pin - fill mostly from global data
 */
extern struct cell_pin_t *__alloc_cpin(int32 has_name)
{
 struct cell_pin_t *cpp;

 cpp = alloc_memcpins();
 if (has_name) cpp->pnam = alloc_cpnam(__portnam);
 else cpp->pnam = NULL;
 cpp->cplin_cnt = __lin_cnt;
 cpp->cpfnam_ind = __cur_fnam_ind;
 cpp->cpxnd = NULL;
 cpp->cpnxt = NULL;

 return(cpp);
}

/*
 * allocate a string element a preallocated block for fast freeing
 * used only for cell pin names
 */
static char *alloc_cpnam(char *s)
{
 char *cp;
 int32 slen, rem, real_size;
 struct cpnblk_t *cpnbp;

 slen = strlen(s) + 1;
 if ((rem = slen % 4) != 0) real_size = slen + 4 - rem;
 else real_size = slen;

 if ((__hdr_cpnblks->cpn_start_sp + real_size + 4) >= 
  __hdr_cpnblks->cpn_end_sp)
  {
   cpnbp = (struct cpnblk_t *) __my_malloc(sizeof(struct cpnblk_t));
   cpnbp->cpnblknxt = __hdr_cpnblks;
   __hdr_cpnblks = cpnbp;
   cpnbp->cpnblks = cpnbp->cpn_start_sp = __my_malloc(BIG_ALLOC_SIZE);
   cpnbp->cpn_end_sp = cpnbp->cpn_start_sp + BIG_ALLOC_SIZE - 16;
  }
 cp = __hdr_cpnblks->cpn_start_sp;
 __hdr_cpnblks->cpn_start_sp += real_size;
 strcpy(cp, s);
 return(cp);
}

/*
 * allocate a cell pin element from a preallocated block for fast freeing
 */
static struct cell_pin_t *alloc_memcpins(void)
{
 struct cppblk_t *cppbp;
 struct cell_pin_t *cpp;

 if (__cppblk_nxti == -1)
  {
   cppbp = (struct cppblk_t *) __my_malloc(sizeof(struct cppblk_t));
   cppbp->cppblks = (struct cell_pin_t *) __my_malloc(BIG_ALLOC_SIZE);
   cppbp->cppblknxt = __hdr_cppblks;
   __hdr_cppblks = cppbp;
   __cppblk_nxti = 0;
  }
 cpp = (struct cell_pin_t *) &(__hdr_cppblks->cppblks[__cppblk_nxti]);
 if (++__cppblk_nxti > ((BIG_ALLOC_SIZE/sizeof(struct cell_pin_t)) - 1))
  __cppblk_nxti = -1;
 return(cpp);
}

/*
 * add cell - better not be already defined at module top level
 * at this point both gates and module instances cells
 * cells always declared at top level
 */
static struct cell_t *add_cell(char *inam)
{
 struct cell_t *cp;
 struct sy_t *syp;
 struct genitem_t *gip;
 char s1[RECLEN];

 __cp_num++;
 if (__cur_cntxt_gblk == NULL) syp = __decl_sym(inam, __venviron[0]);
 else syp = __decl_sym(inam, __cur_cntxt_gblk->gblk_sytab);
 if (__sym_is_new)
  {
treat_as_new:
   syp->sytyp = SYM_I;
   cp = __alloc_cell(syp);
   syp->el.ecp = cp;

   syp->sydecl = TRUE;
    /* this is place of declaration */
   syp->syfnam_ind = __cur_fnam_ind;
   syp->sylin_cnt = __lin_cnt;

   if (__cur_cntxt_gblk == NULL)
    {
     /* must link on end to preserve inst. order */
     if (__end_cp == NULL) __inst_mod->mcells = cp;
     else __end_cp->cnxt = cp;
     __end_cp = cp;
    }
   else
    {
     /* if have generate blk context - must add to end gen item list */
     gip = __alloc_init_new_genitem(GI_CELL);
     gip->giu.gi_cp = cp;
     if (__cur_cntxt_gblk->last_gitem == NULL) __cur_cntxt_gblk->gitems = gip;
     else __cur_cntxt_gblk->last_gitem->geninxt = gip;
     __cur_cntxt_gblk->last_gitem = gip;
    }
   return(cp);
  }
 /* since symbol may be used as down 1 xmr in some system tasks */
 /* if not declared just assume is instance - checked later */
 if (syp->sytyp != SYM_I) 
  {
   if (syp->sydecl) 
    {
     __pv_ferr(1056, "instance/gate name %s previously declared as %s at %s",
      syp->synam, __to_sytyp(s1, syp->sytyp),
      __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
    }
   else goto treat_as_new;
  }
 else __pv_ferr(1057, "instance/gate name %s repeated - previous %s",
  syp->synam, __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
 return(NULL);
}

/*
 * allocate the cell - at this point can be gate, udp or inst.
 */
extern struct cell_t *__alloc_cell(struct sy_t *syp)
{
 struct cell_t *cp;

 /* alloc the element */
 cp = alloc_memcell();
 /* initialize contents union by zeroing all bytes of entire cell */
 cp->csym = syp;
 /* need to fill module type later */
 cp->cmsym = NULL;
 cp->cnxt = NULL;
 cp->c_hasst = FALSE;
 cp->c_stval = ST_STRVAL; 
 cp->cp_explicit = FALSE;
 cp->c_named = FALSE;
 cp->c_iscell = FALSE;
 cp->cx1 = cp->cx2 = NULL;
 cp->c_nparms = NULL;
 cp->cattrs = NULL;
 cp->cpins = NULL;
 return(cp);
}

/*
 * allocate a ncomp element from a preallocated block for fast freeing
 */
static struct cell_t *alloc_memcell(void)
{
 struct cpblk_t *cpbp;
 struct cell_t *cp;

 if (__cpblk_nxti == -1)
  {
   cpbp = (struct cpblk_t *) __my_malloc(sizeof(struct cpblk_t));
   cpbp->cpblks = (struct cell_t *) __my_malloc(BIG_ALLOC_SIZE);
   cpbp->cpblknxt = __hdr_cpblks;
   __hdr_cpblks = cpbp;
   __cpblk_nxti = 0;
  }
 cp = (struct cell_t *) &(__hdr_cpblks->cpblks[__cpblk_nxti]);
 if (++__cpblk_nxti > ((BIG_ALLOC_SIZE/sizeof(struct cell_t)) - 1))
  __cpblk_nxti = -1;
 return(cp);
}

/*
 * ROUTINES TO FIND, CHECK AND PREPARE CONSTANT FUNCTIONS FOR EXECUTION
 */

/*
 * routine to find check fixup and prep constant functions
 * 
 * new algorithm treats all functions even those marked as constant during
 * run time as normal run time functions - during elaboration where
 * constant contexts must be evaluated - when func is called it is
 * on demand copied, fixed up and preped then executed
 *
 * at end of param expr eval (only constant contexts - the preped con
 * func copies are freed
 */
extern void __fnd_chk_fixup_prep_confuncs(void) 
{
 /* SJM 02-02-09 - if any syntax errors do not mark any funcs as const */
 /* this will allow more checking since any con func use will not be */
 /* seen as con func */
 if (__pv_err_cnt == 0)
  {
   mark_all_mod_confuncs();
  }
 /* this may elab and eval const funcs - mark insures only elaborated once */
 eval_all_param_expr_to_nums();
}

/*
 * routine to find and mark all con functions - if called in non constant
 * context with non constant args then treated as normal function
 */
static void mark_all_mod_confuncs(void)
{
 int32 nd_2nd_pass;
 struct mod_t *mdp;
 struct task_t *ftskp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   nd_2nd_pass = FALSE;
   for (ftskp = mdp->mtasks; ftskp != NULL; ftskp = ftskp->tsknxt)
    {
     /* ignore DPI functions here cannot be constant functions */
     if (ftskp->tf_dpip) continue;
     if (ftskp->tsktyp != FUNCTION) continue;  

     /* if returns F, this sets con func type, if returns T, callee sets bits */
     if (!func_canbe_const(ftskp))
      {
       /* eliminated therefore now unknown is F and is con func is F */
       /* this is bottom of lattice so can't change */
       ftskp->unkn_if_con_func = FALSE;
       ftskp->is_con_func = FALSE;
       continue;
      }
     /* ftskp can be con func so set - but callee sets unknown/known */
     ftskp->is_con_func = TRUE;

     /* SJM 01-27-09 - mark this func as probably con func, but need */
     /* pass because at this point unknown if called func all are con funcs */
     if (ftskp->unkn_if_con_func) nd_2nd_pass = TRUE; 
     /* DBG remove -- */
     else if (__debug_flg) 
      {
       __dbg_msg(" ++ module %s function %s is a constant function\n",
        mdp->msym->synam, ftskp->tsksyp->synam);
      }
     /* --- */
    }
   if (!nd_2nd_pass)
    {
     __pop_wrkitstk();
     continue;
    }

   for (ftskp = mdp->mtasks; ftskp != NULL; ftskp = ftskp->tsknxt)
    {
     if (ftskp->tsktyp != FUNCTION) continue;  
     /* if know whether or not const func, nothing more to do */
     if (!ftskp->unkn_if_con_func) continue;

     /* if unkn only can happen if is con func T, i.e. passed all other tests */
     /* DBG remove -- */
     if (!ftskp->is_con_func) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* if returns F, this sets con func type, if returns T, callee sets bits */
     if (!func_canbe_const(ftskp))
      {
       /* eliminated therefore now unknown is F and is con func is F */
       /* this is bottom of lattice so can't change */
       ftskp->unkn_if_con_func = FALSE;
       ftskp->is_con_func = FALSE;
       continue;
      }
     /* ftskp can be con func - known bit must be set - this set is con func */
     /* DBG remove -- */
     if (ftskp->unkn_if_con_func) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* SJM 01-27-09 - mark this func as probably con func, but need */
     /* pass because at this point unknown if called func all are con funcs */
     /* DBG remove -- */
     else if (__debug_flg) 
      {
       __dbg_msg(
        " ++ 2ND PASS module %s function %s is a constant function\n",
        mdp->msym->synam, ftskp->tsksyp->synam);
      }
     /* --- */
    }
   __pop_wrkitstk();
  }
}

/*
 * return T if function can possibly be constant  
 *
 * do not know if actually a constant func until later because may call
 * function that may turn out to be non constant
 *
 * SJM 12-01-08 new 2005 feature allowing constant functions to be used
 * to elaborate (determine inst tree) so must be identified and market
 * before gen work space copy and net list fixup
 */
static int32 func_canbe_const(struct task_t *ftskp)
{
 int32 dim, rv;
 struct net_t *np;
 struct mda_t *mdap;

 if (ftskp->tsk_ingen) return(FALSE);

 /* variables or param ranges can't use global parm or call const func */
 for (np = ftskp->tsk_prms; np != NULL; np = np->nu2.nnxt)
  {
   if (np->nu.ct->nx1 != NULL)
    {
     if (!expr_canbe_in_con_func(ftskp, np->nu.ct->nx1, TRUE)) return(FALSE);
    }  
   if (np->nu.ct->nx2)
    {
     if (!expr_canbe_in_con_func(ftskp, np->nu.ct->nx2, TRUE)) return(FALSE);
    }
   /* SJM 01-27-09 - rhs of any param decl in const func can not call any */ 
   /* const function - required by LRM and insures known elab sizes */
   /* DBG remove --- */
   if (np->nu.ct->parm_srep != SR_PXPR) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   if (!expr_canbe_in_con_func(ftskp, np->nu.ct->n_dels_u.d1x, TRUE))
    return(FALSE);
  }
 for (np = ftskp->tsk_locprms; np != NULL; np = np->nu2.nnxt)
  {
   if (np->nu.ct->nx1 != NULL)
    {
     if (!expr_canbe_in_con_func(ftskp, np->nu.ct->nx1, TRUE)) return(FALSE);
    }
   if (np->nu.ct->nx2 != NULL)
    {
     if (!expr_canbe_in_con_func(ftskp, np->nu.ct->nx2, TRUE)) return(FALSE);
    }
  }
 for (np = ftskp->tsk_regs; np != NULL; np = np->nu2.nnxt)
  {
   /* range of local const func variables can not call const funcs */
   if (np->nu.ct->nx1 != NULL)
    {
     if (!expr_canbe_in_con_func(ftskp, np->nu.ct->nx1, TRUE)) return(FALSE);
    }
   if (np->nu.ct->nx2 != NULL)
    {
     if (!expr_canbe_in_con_func(ftskp, np->nu.ct->nx2, TRUE)) return(FALSE);
    }
   /* arrays including multi-dimensional possible too */
   if (np->mda != NULL) 
    {
     mdap = np->mda;
     for (dim = 0; dim < mdap->dimension; dim++)
      {
       if (!expr_canbe_in_con_func(ftskp, mdap->tab_ax1[dim], TRUE))
        return(FALSE);
       if (!expr_canbe_in_con_func(ftskp, mdap->tab_ax2[dim], TRUE))
        return(FALSE);
      }
    }
   if (np->nu.ct->ax1 != NULL)
    {
     if (!expr_canbe_in_con_func(ftskp, np->nu.ct->ax1, TRUE)) return(FALSE);
    }
   if (np->nu.ct->ax2 != NULL)
    {
     if (!expr_canbe_in_con_func(ftskp, np->nu.ct->ax2, TRUE)) return(FALSE);
    }
  }
 __nbsti = -1;
 rv = stmt_can_be_con_func(ftskp, ftskp->tskst);
 /* SJM 02-15-09 - as soon as eliminated returns F must clear nb stk here */
 __nbsti = -1;
 return(rv);
}

/*
 * return T if expr is something that does not prevent a function from
 * being constant
 *
 * SJM 01-27-09 - key is that if returns F to eliminate possibility of
 * being a constant func, caller sets unknown to F, but if fcall only
 * reason can't set as con func, this callee sets unkn
 *
 * algorithm works by assuming function can be a constant function used in
 * constant contexts and eliminate if can't be used
 *
 */
static int32 expr_canbe_in_con_func(struct task_t *ftskp, struct expr_t *xp,
 int32 is_con_cntxt)
{
 struct net_t *np;
 struct expr_t *xp2;
 struct sy_t *syp, *fcall_syp;

 if (__isleaf(xp))
  {
   /* const funcs can't have globals */
   if (xp->optyp == GLBREF) return(FALSE);
   if (xp->optyp == ID)
    {
     /* SJM 12-01-08 - since uncheck src, if not net - elim - error later */
     if (xp->lu.sy->sytyp != SYM_N) return(FALSE);

     np = xp->lu.sy->el.enp;
     if (np->n_isaparam)
      {
       /* DBG remove -- */
       if (np->nrngrep != NX_CT) __misc_terr(__FILE__, __LINE__);
       /* --- */
       /* case 1: it is a param declared previously in this mod's src */
       /* gen vars can't be used in constant functions */
       /* SJM 01-26-09 - param value used is current value when called */
       if (np->nu.ct->p_genvar) return(FALSE);

       /* if know it is a non xmr param ref, always can be in const func */
      }
     else
      {
       /* case 2: some var (net) */
       /* if a constant context, this is syntax error - eliminate */
       if (is_con_cntxt) return(FALSE);

       /* if syntax error, can get here on not declared var, just eliminate */
       if (!np->nsym->sydecl) return(TRUE);

       /* finally must be declared in function symbol table only */
//SJM 12-01-08 - LOOKATME??  for named blocks with local var decls 
       if ((syp = confunc_get_sym(np->nsym->synam, ftskp->tsksymtab,
        ftskp->tsksymtab)) == NULL) return(FALSE);
       /* declared in func so good */
      }
     return(TRUE);
    }
   /* DBG remove -- */
   if (xp->optyp == ISNUMBER || xp->optyp == ISREALNUM)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* all other leaf exprs then not eliminated - can be */
   return(TRUE);
  }
 if (xp->optyp == FCALL)
  {
   /* SJM - 02-15-09 - if forward decl of called func, can't tell here */
   /* if xmr or not so will still be gref - fixed up later */
   if (xp->lu.x->optyp == GLBREF)
    {
     /* syp is symbol of called func - this runs after all src read so */
     /* even if forward but not real XMR, will be found */
     /* SJM 02-19-09 - now using proc to access forward func symbols */
     if ((syp = __get_forw_funcdef_sy(xp->lu.x, TRUE)) == NULL) return(FALSE);
    }
   else syp = xp->lu.x->lu.sy;

   if (syp->sytyp == SYM_SF && syp->el.esyftbp->tftyp == SYSF_BUILTIN)
    {
     /* can also always call one of the legal sys funcs in const func */
     if (!sysf_confunc_legal(syp->el.esyftbp->syfnum)) return(FALSE);
    }
   else
    {
     /* no user func even constant in constant contexts - i.e. decl ranges */
     if (is_con_cntxt) return(FALSE);

     /* all func read, but may not have set can be con func bits yet */
     fcall_syp = __get_sym(syp->synam, __inst_mod->msymtab);
     /* AIV 04/07/09 - had fcall_syp == NULL __misc_terr here */
     /* needs to return NULL for undefined PLI calls for later undef error */
     if (fcall_syp == NULL) return(FALSE);

     /* DBG remove -- */
     if (fcall_syp->sytyp != SYM_F) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* know for sure that this function is either a con func or not */
     if (!fcall_syp->el.etskp->unkn_if_con_func)
      {
       /* if return F, caller will set correctn unkn/known state */
       if (!fcall_syp->el.etskp->is_con_func) return(FALSE);
      }
     else
      {
       /* can possibly be con func but won't know for sure until determine */
       /* that called function is a legal con func */
       /* returns T so is con func set but - unkn bit will cause more chks */
       /* if args eliminate will return F so caller will turn off unkn state */
       ftskp->unkn_if_con_func = TRUE;
      }
    }

   /* SJM 01-27-09 con func calls or local con func variables allowed here */
   for (xp2 = xp->ru.x; xp2 != NULL; xp2 = xp2->ru.x)
    { 
     if (!expr_canbe_in_con_func(ftskp, xp2->lu.x, FALSE))
      return(FALSE);
    }
   return(TRUE);
  }

 /* finally check sub expressions */
 if (xp->lu.x != NULL)
  {
   if (!expr_canbe_in_con_func(ftskp, xp->lu.x, is_con_cntxt))
    return(FALSE);
  }  
 if (xp->ru.x != NULL)
  {
   if (!expr_canbe_in_con_func(ftskp, xp->ru.x, is_con_cntxt))
    return(FALSE);
  }
 return(TRUE);
}

/*
 * need special symbol table search routine that uses current labeled blk
 * symbol table and works up but only to func def symbol table
 *
 * SJM 12-01-08 FIXME for not allowing decls in const func labeled blocks
 * SJM 12-01-08 think same search routine can be used for automatic func/tasks
 */
static struct sy_t *confunc_get_sym(char *snam, struct symtab_t *cur_sytab,
 struct symtab_t *ftsk_sytab)
{
 struct symtab_t *sytp;
 struct sy_t *syp;

 /* first see if declared in func declaration top level symbol table */ 
 if ((syp = __get_sym(snam, ftsk_sytab)) != NULL) return(syp);
 
 /* see if inside labeled block - usually won't search here */
 for (sytp = cur_sytab; sytp != ftsk_sytab; sytp = sytp->sytpar)
  {
   if ((syp = __get_sym(snam, sytp)) != NULL) return(syp);
  }
 return(NULL);
}

/*
 * return forward fcall module sym tab symbol (can get tskp from it)
 */
extern struct sy_t *__get_forw_funcdef_sy(struct expr_t *xp, int32 conf_only)
{
 struct sy_t *syp;

 /* DBG remove -- */
 if (xp->optyp != GLBREF) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (!conf_only)
  {
   if (xp->lu.sy != NULL) return(xp->lu.sy);
   if (xp->ru.grp != NULL && xp->ru.grp->targsyp != NULL)
    return(xp->ru.grp->targsyp);
  }

 syp = __get_sym(xp->ru.grp->gnam, __inst_mod->msymtab);
 if (syp == NULL || syp->sytyp != SYM_F) return(NULL);
 return(syp);
}

/*
 * return T if a system function can be legally used in constant function
 */
static int32 sysf_confunc_legal(int32 sysfunc_no)
{
 switch (sysfunc_no) {
  case STN_CLOG2:
  case STN_CEIL:
  case STN_FLOOR:
  case STN_RTOI:
  case STN_ITOR:
  case STN_REALTOBITS:
  case STN_BITSTOREAL:
  case STN_SIGNED:
  case STN_UNSIGNED:
  case STN_LN:
  case STN_LOG10:
  case STN_EXP:
  case STN_SQRT:
  case STN_POW:
  case STN_SIN:
  case STN_COS:
  case STN_TAN:
  case STN_ASIN:
  case STN_ACOS:
  case STN_ATAN:
  case STN_HYPOT:
  case STN_SINH:
  case STN_COSH:
  case STN_TANH:
  case STN_ASINH:
  case STN_ACOSH:
  case STN_ATANH:
   break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * routine to check function body statement (usally block) to eliminate
 * functions that can't possibly be const (works by setting bits)
 */
static int32 stmt_can_be_con_func(struct task_t *ftskp, struct st_t *stp) 
{
 struct for_t *frp;

 switch ((byte) stp->stmttyp) {
  case S_NULL: case S_STNONE:
   break;
  case S_PROCA: case S_FORASSGN:
   if (!expr_canbe_in_con_func(ftskp, stp->st.spra.rhsx, FALSE))
    return(FALSE);
   if (!expr_canbe_in_con_func(ftskp, stp->st.spra.lhsx, FALSE))
    return(FALSE);
   break;
  case S_QCONTA: case S_QCONTDEA: case S_RHSDEPROCA:
  case S_TSKCALL: case S_DELCTRL: case S_WAIT: case S_UNFJ: case S_FUNCCALL:
  case S_NBPROCA: case S_CAUSE:
   /* stmts that eliminate const func - maybe illegal - if so error later */
   return(FALSE);
   break;
  case S_IF:
   if (!expr_canbe_in_con_func(ftskp, stp->st.sif.condx, FALSE)) return(FALSE);
   if (!stlst_can_be_con_func(ftskp, stp->st.sif.thenst)) return(FALSE);
   if (stp->st.sif.elsest != NULL) 
    {
     if (!stlst_can_be_con_func(ftskp, stp->st.sif.elsest)) return(FALSE);
    }
   break;
  case S_CASE:
   if (!expr_canbe_in_con_func(ftskp, stp->st.scs.csx, FALSE)) return(FALSE);
   if (csitem_canbe_in_con_func(ftskp, stp->st.scs.csitems)) return(FALSE);
   break;
  case S_FOREVER:
   if (!stlst_can_be_con_func(ftskp, stp->st.swh.lpst)) return(FALSE);
   break;
  case S_WHILE:
  case S_DO_WHILE:
   if (!expr_canbe_in_con_func(ftskp, stp->st.swh.lpx, FALSE)) return(FALSE);
   if (!stlst_can_be_con_func(ftskp, stp->st.swh.lpst)) return(FALSE);
   break;
  case S_REPEAT:
   if (!expr_canbe_in_con_func(ftskp, stp->st.srpt.repx, FALSE)) return(FALSE);
   if (!stlst_can_be_con_func(ftskp, stp->st.srpt.repst)) return(FALSE);
   break;
  case S_FOR:
   frp = stp->st.sfor;
   if (!expr_canbe_in_con_func(ftskp, frp->fortermx, FALSE)) return(FALSE);
   if (stlst_can_be_con_func(ftskp, frp->forinc)) return(FALSE);
   if (!stlst_can_be_con_func(ftskp, frp->forbody)) return(FALSE);
   break;
  case S_NAMBLK:
   __push_nbstk(stp); 
   if (!stmt_can_be_con_func(ftskp, stp->st.snbtsk->tskst)) return(FALSE);
   __pop_nbstk();

   /* SJM 02-05-09 - making labeled blocks with var declarations non const */
   /* LRM is not specific - but very difficult to build idp area */
   if (stp->st.snbtsk->tsksymtab != NULL
    && stp->st.snbtsk->tsksymtab->numsyms > 0)
    {
#ifndef __CVC_RT__
     __gfwarn(3144, stp->stfnam_ind, stp->stlin_cnt,
      "labeled blocks with variable declarations not allowed in constant functions");
#endif
     return(FALSE);
    } 
   break;
  case S_UNBLK:
   if (!stlst_can_be_con_func(ftskp, stp->st.sbsts)) return(FALSE);
   break;
  case S_DSABLE:
   /* SJM 02-09-09 - think disable - even of func name is just break/ret */
   if (!dsable_xpr_canbe_in_con_func(ftskp, stp->st.sdsable.dsablx))
    return(FALSE);
   /* SJM 03-07-09 - fixed but was not return T if ok */
   break;
  case S_INC: case S_DEC:
  case S_CONTINUE: case S_BREAK: case S_RETURN:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(TRUE);
}

/*
 * check list of stmts to eliminate functions that can't possibly
 * be in const functions
 */
static int32 stlst_can_be_con_func(struct task_t *ftskp, struct st_t *stp) 
{
 for (; stp != NULL; stp = stp->stnxt)
  {
   if (!stmt_can_be_con_func(ftskp, stp)) return(FALSE);
  }
 return(TRUE);
}

/*
 * check case stmt to elminate functions that can't possilby const func
 */  
static int32 csitem_canbe_in_con_func(struct task_t *ftskp,
 struct csitem_t *csip)
{
 if (csip->csixlst != NULL)
  {
   if (!exprlst_canbe_in_con_func(ftskp, csip->csixlst)) return(FALSE);
  }
 if (csip->csist != NULL)
  {
   /* AIV 07/15/09 - this needs the ! here - was reversed */
   return(!stlst_can_be_con_func(ftskp, csip->csist));
  }
 return(TRUE);
}

/*
 * check expr list to eliminate functions that can't possibly be const func 
 */
static int32 exprlst_canbe_in_con_func(struct task_t *ftskp,
 struct exprlst_t *xplp)
{
 for (; xplp != NULL; xplp = xplp->xpnxt)
  {
   if (!expr_canbe_in_con_func(ftskp, xplp->xp, FALSE)) return(FALSE);
  }
 return(TRUE);
}

/*
 * return T if function disable (know it is no delay) can be in const
 * function - must be labeled block in current function
 *
 * SJM 02-09-09 - FIXME - maybe should allow disable to be used as return
 */
static int32 dsable_xpr_canbe_in_con_func(struct task_t *ftskp,
 struct expr_t *dsxp)
{
 int32 i;
 struct sy_t *syp;

 if (dsxp->optyp == GLBREF) return(FALSE); 
 /* this syntax error will be caught later */
 if (dsxp->optyp != ID) return(FALSE);  
 syp = dsxp->lu.sy;
 if (syp->sytyp != SYM_LB)
  {
   /* SJM 02-15-09 - at this point disable of name of func looks like disabl */
   /* of net - it is now ok on const func and will be fixed up later */
   if (syp->sytyp == SYM_N) 
    {
     if (strcmp(syp->synam, ftskp->tsksyp->synam) == 0) return(TRUE);
    }
   return(FALSE);
  }

 for (i = __nbsti; i >= 0; i--)
  {
   if (__nbstk[i]->st.snbtsk->tsksyp == syp) return(TRUE);
  }
 return(FALSE);
}

/*
 * routine to eval all ranges to numbers in every module
 *
 * SJM 01-27-09 - this is new algorithm that must wait until all const
 * funcs are marked (identified) and prepper so exec con func routine can be
 * called 
 */
static void eval_all_param_expr_to_nums(void)
{
 int32 sav_decl_obj;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct net_t *parm_np;
 struct spfy_t *spcp;
 struct dfparam_t *dfpp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* all task and function params */
   /* SJM 02-02-09 - know that for usuable as elab time const funcs */
   /* will never call funcs in parameter (const) contexts */
   
   /* params */
   for (parm_np = mdp->mprms; parm_np != NULL; parm_np = parm_np->nu2.nnxt)
    {
     param_rng_chk_cnvt_to_num(parm_np, "parameter");
     chk_eval_param_rhs(parm_np, "parameter");
    }
   /* local params */
   for (parm_np = mdp->mlocprms; parm_np != NULL; parm_np = parm_np->nu2.nnxt)
    {
     /* SJM 02-20-09 - no ranges or rhs changes need for mod level genvars */
     if (parm_np->nu.ct->p_genvar) continue;
      
     param_rng_chk_cnvt_to_num(parm_np, "localparam");
     chk_eval_param_rhs(parm_np, "localparam");
    }

   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     parm_np = tskp->tsk_prms;
     for (; parm_np != NULL; parm_np = parm_np->nu2.nnxt)
      {
       param_rng_chk_cnvt_to_num(parm_np, "parameter");
       chk_eval_param_rhs(parm_np, "parameter");
      }
     parm_np = tskp->tsk_locprms;
     for (; parm_np != NULL; parm_np = parm_np->nu2.nnxt)
      {
       param_rng_chk_cnvt_to_num(parm_np, "parameter");
       chk_eval_param_rhs(parm_np, "parameter");
      }
    }

   /* all spec params */
   spcp = mdp->mspfy;
   if (spcp != NULL)
    {
     /* SJM 02-19-09 - need to set object to specify to find use of params */
     /* errors - only specparams allowed in specify section */
     sav_decl_obj = __cur_declobj;
     __cur_declobj = SPECIFY;
     for (parm_np = spcp->msprms; parm_np != NULL; parm_np = parm_np->nu2.nnxt)
      {
       param_rng_chk_cnvt_to_num(parm_np, "specparam");
       chk_assign_val_specparam(parm_np);
      }
     __cur_declobj = sav_decl_obj;
    }
   /* finally, all defparam stmt rhs exprs */
   for (dfpp = mdp->mdfps; dfpp != NULL; dfpp = dfpp->dfpnxt) 
    {
     chk_dfparam_rhs_expr(dfpp);
    }

   __pop_wrkitstk();
  }
}

/*
 * routine to check optional param vector rng and convert to numbers 
 *
 * SJM 01-29-09 - now need to chk and eval separately after const funcs
 * found and prepared
 */
static void param_rng_chk_cnvt_to_num(struct net_t *parm_np, char *ptnam)
{
 int32 rngerr, sav_slin_cnt, sav_sfnam_ind;
 struct expr_t *x1, *x2;

 rngerr = FALSE;
 x1 = parm_np->nu.ct->nx1;
 x2 = parm_np->nu.ct->nx2;
 /* if rng not set (decl from rhs), nothing to do */
 if (x1 == NULL)
  {
   /* DBG remove -- */
   if (x2 != NULL) __misc_terr(__FILE__, __LINE__);
   if (parm_np->nu.ct->prngdecl) __misc_terr(__FILE__, __LINE__);
   if (parm_np->nu.ct->ptypdecl) __misc_terr(__FILE__, __LINE__);
   /* --- */
   return;
  }

 sav_sfnam_ind = __slin_cnt;
 sav_slin_cnt = __sfnam_ind;
 __sfnam_ind = parm_np->nsym->syfnam_ind;
 __slin_cnt = parm_np->nsym->sylin_cnt;

 /* SJM 02-19-09 - param expr must not handle xmr fcalls from forward func */ 
 /* decls as special case */
 if (!__chk_paramexpr(x1, 0))
  {
   __sgferr(1025,
    "%s declaration first range \"%s\" illegal - defined %ss, constants and constant functions only",
    ptnam, __msgexpr_tostr(__xs, x1), ptnam);
   rngerr = TRUE;
  }
 else
  {
   /* because of previous check, this can not fail */
   __eval_param_rhs_tonum(x1, __sfnam_ind, __slin_cnt);
   if (!__nd_ndxnum(x1, "parameter array declaration first range", TRUE))
     rngerr = TRUE;
  }

 /* SJM 02-19-09 - param expr must not handle xmr fcalls from forward func */ 
 /* decls as special case */
 /* still need checking - this allows functions - if non const caught later */
 if (!__chk_paramexpr(x2, 0))
  {
   __sgferr(1025,
    "%s declaration second range \"%s\" illegal - defined %ss, constants and constant functions only",
    ptnam, __msgexpr_tostr(__xs, x2), ptnam);
   rngerr = TRUE;
  }
 else
  {
   /* because of previous check, this can not fail */
   __eval_param_rhs_tonum(x2, __sfnam_ind, __slin_cnt);
   if (!__nd_ndxnum(x2, "parameter array declaration second range", TRUE))
    rngerr = TRUE;
  }

 if (rngerr)
  { 
   /* SJM 02-01-09 - if err, make 32 bit reg */
   x1 = __bld_rng_numxpr(WBITS - 1, 0L, WBITS);
   x2 = __bld_rng_numxpr(0L, 0L, WBITS);
   parm_np->nwid = WBITS;
  }

 parm_np->nu.ct->nx1 = x1;
 parm_np->nu.ct->nx2 = x2;

 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * routine to evaluate parameters or defparam rhs and produce constant
 *
 * this expects itree location to be set but no IS forms allowed by here
 * know rhs legal (only params and constants and const functions)
 *
 * SJM 01-28-09 - this freezes by converting to a num any param rhs val or
 * range including spec params - original expr saved in nu.ct n_dels_u d1x
 * since now called after src read just before work space gen copya and
 * fix up caller must pass location (also used without any const funcs from
 * attribute read code in v src3)
 */
extern void __eval_param_rhs_tonum(struct expr_t *ndp, int32 sfnind,
 int32 slcnt)
{ 
 int32 wlen, is_str, xbase, sav_slin_cnt, sav_sfnam_ind;
 double d1;
 struct xstk_t *xsp;

 sav_slin_cnt = __slin_cnt;
 sav_sfnam_ind = __sfnam_ind;
 __sfnam_ind = sfnind;
 __slin_cnt = slcnt;

 if (ndp->is_string) is_str = TRUE; else is_str = FALSE;
 xbase = ndp->ibase;
 
 /* possibly different expr. */
 switch (ndp->optyp) {  
  case NUMBER: case REALNUM: break;
  /* IS forms can only be created by # or defparam assignments later */
  /* can never be in source */ 
  case ISNUMBER: case ISREALNUM: __arg_terr(__FILE__, __LINE__); break;
 default:
  if (ndp->optyp == ID && ndp->lu.sy->el.enp->n_isaparam)
   {
    is_str = ndp->lu.sy->el.enp->nu.ct->pstring;
    xbase = ndp->lu.sy->el.enp->nu.ct->pbase;
   }
  else if (ndp->optyp == LCB) is_str = TRUE;

  /* SJM 01-28-09 - eval before running fixup works because only params, */
  /* numbers and const functions that have been preped to exec */
  xsp = __eval_xpr(ndp);

  __free2_xtree(ndp);
  wlen = wlen_(xsp->xslen);
  if (xsp->xslen <= WBITS)
   {
    if (ndp->is_real)
     {
      memcpy(&d1, xsp->ap, sizeof(double)); 
      ndp->ru.xvi = __alloc_shareable_rlcval(d1);
     }
    else
     {
      ndp->ru.xvi = __alloc_shareable_cval(xsp->ap[0], xsp->bp[0], xsp->xslen);
     }
   }
  else
   {
    ndp->ru.xvi = __allocfill_cval_new(xsp->ap, xsp->bp, wlen);
   }
  __pop_xstk();
  /* notice string from rhs param expr. impossible */
  if (ndp->is_real) ndp->optyp = REALNUM;
  else
   {
    ndp->optyp = NUMBER;
    /* notice leave rest of ndp fields the same */
    ndp->is_string = is_str;
   }
  ndp->ibase = xbase;
 } 

 /* put back in src loc */
 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * routine to chk and eval param rhs expr and set param nu.ct fields
 * must be called after param ranges converted to numbers
 *
 * SJM 01-29-09 this routine now does all the work the old src chk rd
 * param did during src reading - must do all this after con funcs found
 *
 * SJM 01-29-09 - Verilog param ranges must be set to numbers during
 * src read phase but now because of con functions, done in separate pass
 * before work space copy for gen and nl fixup - nl fixup sees exactly same
 * d.s. as before
 */
static void chk_eval_param_rhs(struct net_t *parm_np, char *ptnam)
{
 int32 pwid, pwtyp, r1, r2, wlen, sav_slin_cnt, sav_sfnam_ind;
 int32 cntxt_wid;
 word32 *wp;
 struct expr_t *x1, *x2, *ndp;
 struct xstk_t *xsp;
 
 sav_sfnam_ind = __slin_cnt;
 sav_slin_cnt = __sfnam_ind;
 __sfnam_ind = parm_np->nsym->syfnam_ind;
 __slin_cnt = parm_np->nsym->sylin_cnt;

 x1 = x2 = NULL;
 pwid = parm_np->nwid;
 
 /* pw typ is just provisional guess at param's wire type */
 pwtyp = parm_np->ntyp;
 /* SJM 02-02-09 - if range declared may need to adjust range to h:0 */
 /* case is prng decl on but p typ decl off */
 if (parm_np->nu.ct->prngdecl && !parm_np->nu.ct->ptypdecl)
  {
   /* by here know that for any vector parm, range set as number exprs */
   x1 = parm_np->nu.ct->nx1;
   x2 = parm_np->nu.ct->nx2;
   /* DBG remove -- */
   if (x1 == NULL || x2 == NULL) __misc_terr(__FILE__, __LINE__);
   if (x1->optyp != NUMBER || x2->optyp != NUMBER)
     __misc_terr(__FILE__, __LINE__);
   /* --- */

   r1 = (int32) __contab[x1->ru.xvi];
   r2 = (int32) __contab[x2->ru.xvi];
   pwid = (r1 >= r2) ? r1 - r2 + 1 : r2 - r1 + 1; 
   parm_np->nwid = pwid;

   /* SJM 02-19-09 - can't normalize to h:0 here - must be done later */
   /* because in v fx3 part selects from parameter codes needs in src rnges */
  }

 /* now check rhs - if wire range/type not declared will use to set parm */
 /* var properties such as its range (size) and var type */

 ndp = parm_np->nu.ct->n_dels_u.d1x;
 /* SJM 10/06/03 - chk paramexpr routine sets expr signed bit */

 /* expr width context 0 if param decl from rhs expr type */
 if (parm_np->nu.ct->prngdecl || parm_np->nu.ct->ptypdecl)
  {
   cntxt_wid = parm_np->nwid;
  }
 else cntxt_wid = 0;
 /* SJM 02-19-09 - param expr must not handle xmr fcalls from forward func */ 
 /* decls as special case */
 if (!__chk_paramexpr(ndp, cntxt_wid))
  {
   __sgferr(1025,
    "%s %s declaration right hand side \"%s\" error - defined %ss, constants and constant functions only",
    __to_wtnam2(__xs, pwtyp), parm_np->nsym->synam, __msgexpr_tostr(__xs, ndp),
    ptnam);
   /* need to still add value of x to prevent further errors */
   __free2_xtree(ndp);
   ndp->szu.xclen = WBITS;
   __set_numval(ndp, ALL1W, ALL1W, WBITS);  
   parm_np->nu.ct->n_dels_u.d1x = ndp; 
   /* SJM 03/15/00 - on err if decl as real - must convert to non real */
   if (pwtyp == N_REAL) pwtyp = N_REG;
  }

 /* now eval param */
 xsp = __eval_xpr(ndp); 

 /* case parameter type declared - maybe convert - must eval before here */
 /* if range, implied pwtyp set to reg type */
 if (parm_np->nu.ct->ptypdecl || parm_np->nu.ct->prngdecl)
  {
   if (pwtyp == N_REAL)
    {
     parm_np->ntyp = N_REAL; 
     parm_np->n_signed = TRUE;
     parm_np->nwid = REALBITS;
     parm_np->nu.ct->pbase = BDBLE;

     if (!ndp->is_real)
      __cnv_stk_fromreg_toreal(xsp, (__root_ndp->has_sign == 1));
    }
   else
    {
     parm_np->ntyp = pwtyp;

     /* SJM 08-04-10 - new 2 state var */
     if (__is_2state_typ(parm_np->ntyp)) parm_np->n_2state = TRUE;

     parm_np->n_signed = FALSE;
     /* SJM 02-02-09 - param width set before here if declared */
     /* SJM 08-02-10 - for SV rhs decl still works but 2001 form */
     if (parm_np->nu.ct->psigndecl) parm_np->n_signed = TRUE;
     else
      {
       if (__is_int_atom_typ(parm_np->ntyp)) parm_np->n_signed = TRUE;
      }

     /* even if declared use rhs expr. for param ncomp expr formats */
     if (ndp->is_string) parm_np->nu.ct->pstring = TRUE;
     parm_np->nu.ct->pbase = ndp->ibase;

     /* convert declared param type real rhs to int/reg */
     if (ndp->is_real) parm_np->nu.ct->pbase = BDEC;

     /* SJM 02-02-09 - there was a call to siz chg xs routine here that */
     /* seemingly had no effect because of next if - if problem put back */

     /* SJM 09/29/03 - change to handle sign extension and separate types */
     /* SJM 02/19/09 - only narrow if too wide was wrong equal */
     if (xsp->xslen > ndp->szu.xclen) __narrow_sizchg(xsp, pwid);
     else if (xsp->xslen < parm_np->nwid)
      {
       if (ndp->has_sign) __sgn_xtnd_widen(xsp, parm_np->nwid);
       else __sizchg_widen(xsp, parm_np->nwid);
      }
    }
  }
 else
  {
   /* no parameter range given or will not get here */ 
   /* SJM 02-02-09 - this is case where rhs expr determeind param var decl */
   if (ndp->is_real)
    {
     parm_np->ntyp = N_REAL;
     parm_np->n_signed = TRUE;
     parm_np->nwid = REALBITS;
    }
   else
    {
//SJM 08-03-10 FIXME ??? - should add the dbg use bit here too
     parm_np->ntyp = N_REG;
     /* SJM 10/06/03 - no range or var type but signed may be present */
     if (parm_np->nu.ct->psigndecl) parm_np->n_signed = TRUE;
     /* AIV 05/06/09 - this is no longer true parameter must be signed */
     /* not the expression it is assigned to - need to use "singed" */
     /* AIV 12/06/11 - this is actually correct and the comment above is */
     /* wrong - this was compensating for a bug which needs to turn off */
     /* the parameter signed bit */
     else if (ndp->has_sign) parm_np->n_signed = TRUE;
     parm_np->nwid = ndp->szu.xclen;
    }
   /* SJM 02-02-09 - if scalar rhs - no vec range */
   if (parm_np->nwid > 1)
    {
     /* this is any vector including real or time */
     parm_np->n_isavec = TRUE;
     parm_np->vec_scalared = TRUE;

     /* since no decls - decl determined from rhs - better not be rnges */
     /* DBG remove -- */
     if (parm_np->nu.ct->nx1 != NULL || parm_np->nu.ct->nx2 != NULL)
      __misc_terr(__FILE__, __LINE__);
     /* --- */
     parm_np->nu.ct->nx1 = __bld_rng_numxpr(parm_np->nwid - 1, 0L, WBITS);
     parm_np->nu.ct->nx2 = __bld_rng_numxpr(0L, 0L, WBITS);
    }
   /* always true for real and int32 - maybe true from others */
   if (ndp->is_string) parm_np->nu.ct->pstring = TRUE;
   /* this works because param expr checking always sets ibase */ 
   parm_np->nu.ct->pbase = ndp->ibase;
  }
 /* must leave n_dels d1x field since it is original expr */
 if (__xpr_has_param(ndp)) 
  {
   parm_np->nu.ct->p_rhs_has_param = TRUE;
   __inst_mod->mod_rhs_param = TRUE;
  }

 /* value must be evaluated to constant expr - since may need to */
 /* change to IS form */
 /* assign the value as SR PNUM form because now always "declared" - has */
 /* kown type so can store as net value */
 wlen = wlen_(xsp->xslen);
 wp = (word32 *) __my_malloc(2*WRDBYTES*wlen);
 memcpy(wp, xsp->ap, 2*wlen*WRDBYTES);
 parm_np->prm_nva.wp = wp;
 parm_np->srep = SR_PNUM;
 __pop_xstk();

 if (__debug_flg)
  {
   char s1[RECLEN], s2[RECLEN], s3[RECLEN], *chp;
     
   strcpy(s1, "");
   strcpy(s2, "");
   if (ndp->is_real) strcpy(s1, "real ");
   else 
    {
     sprintf(s2, " width %d", ndp->szu.xclen);
     if (ndp->is_string) strcpy(s1, "string ");
     else if (ndp->has_sign) strcpy(s1, "signed ");
    }
   /* SJM 04/20/00 - changed so uses param type for printing */
   /* SJM 05/24/00 - trim leading spaces */
   __pregab_tostr(__xs, wp, &(wp[wlen]), parm_np);
   for (chp = __xs;; chp++) { if (*chp != ' ') break; }
   __dbg_msg("%s%s %s defined at %s has initial value %s%s\n", s1,
    ptnam, parm_np->nsym->synam, __bld_lineloc(s3, __sfnam_ind, __slin_cnt),
     chp, s2);
  }

 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * routine to check and assign a value to a spec param rhs expr 
 */
static void chk_assign_val_specparam(struct net_t *parm_np)
{
 int32 sav_slin_cnt, sav_sfnam_ind;
 struct expr_t *ndp;

 sav_sfnam_ind = __slin_cnt;
 sav_slin_cnt = __sfnam_ind;
 __sfnam_ind = parm_np->nsym->syfnam_ind;
 __slin_cnt = parm_np->nsym->sylin_cnt;

 ndp = parm_np->nu.ct->n_dels_u.d1x;

 /* SJM 02-19-09 - param expr must not handle xmr fcalls from forward func */ 
 /* decls as special case */

 /* checking rhs does no evaluation (not known yet) but set sizes */
 /* and makes sure contains only num and previously defined specparams */
 if (!__chk_paramexpr(ndp, WBITS))
  {
   __sgferr(1233,
    "specparam %s right hand side %s illegal - defined specparams, constants and constant functions only",
    parm_np->nsym->synam, __msgexpr_tostr(__xs, ndp));
   __free2_xtree(ndp);
   ndp->szu.xclen = WBITS;
// SJM 01-29-09 - LOOKATME - making this 0 - what should it be
   __set_numval(ndp, 0, 0, WBITS);  
   return;
  }
 __assign_1specparam(parm_np);

 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * routine to check defparam stmt rhs expr
 *
 * SJM 01-29-09 - separate routine because must do in separate mini-pass
 * before gen workspace copy and nl fixup - just checks because eval
 * needs to follow complex rules
 */
static void chk_dfparam_rhs_expr(struct dfparam_t *dfpp)
{
 int32 sav_slin_cnt, sav_sfnam_ind;
 struct expr_t *ndp;

 sav_sfnam_ind = __slin_cnt;
 sav_slin_cnt = __sfnam_ind;
 __sfnam_ind = dfpp->dfpfnam_ind;
 __slin_cnt = dfpp->dfplin_cnt;

 /* checking rhs does no evaluation but set sizes and checks for only */
 /* numbers and previously defined in source order parameters */
 /* defparam rhs params must be defined previously in module */
 /* notice must be converted to number immediately else can have */
 /* circular dependency */
 /* LRM requires source order definition before use */
 /* SJM 08/07/96 */

 ndp = dfpp->dfpxrhs;
 /* SJM 02-19-09 - param expr must not handle xmr fcalls from forward func */ 
 /* decls as special case */
 if (!__chk_paramexpr(ndp, 0))
  {
   __sgferr(1025,
    "defparam right hand side \"%s\" illegal - parameters, constants and constant functions only",
    __msgexpr_tostr(__xs, ndp));
   /* need to still add value of x to prevent further errors */
   /* notice this change expr in place */
   __free2_xtree(ndp);
   ndp->szu.xclen = WBITS;
   __set_numval(ndp, ALL1W, ALL1W, WBITS);  
  }

 /* SJM 01/27/04 - must leave as rhs expr since just gets evaled */
 /* bug if convert when downward propagation of defparams used on rhs */
 /* of other defparams used */

 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
}

/*
 * ROUTINES TO READ DPI SRC CONSTRUCTS
 */

/*
 * parse a DPI import/export declaration and add to global dpi list
 */
static int32 rd_dpi_declaration(void)
{
 struct dpi_t *dpip;
 char impextypnam[RECLEN];

 dpip = alloc_init_dpi_rec();
 __cur_dpip = dpip;
 dpip->has_ret = FALSE;
 strcpy(impextypnam, "");
 if (__toktyp == IMPORT)
  {
   dpip->dpi_type = DPI_IMPORT;
   /* SJM 02-11-13 - need work strings - think can not use ptrs because */
   /* of passing down and storing - know tok typ has right val */
   strcpy(impextypnam, __prt_vtok());
  }
 else if (__toktyp == EXPORT)
  {
   dpip->dpi_type = DPI_EXPORT;
   strcpy(impextypnam, __prt_vtok());
  }
 else __misc_terr(__FILE__, __LINE__);

 __get_vtok();
 if (__toktyp != LITSTR)
  {
   __pv_ferr(4802, "DPI %s expecting \"DPI\" string", impextypnam);
dpi_error:
   __my_free(dpip, sizeof(struct dpi_t));
   __vskipto_any(SEMI);
   __cur_dpip = NULL;
   return(FALSE);
  }
 /* AIV 09/16/10 - need to use strncmp - here since __strtoken may not */
 /* contain \0 - if previous stroken > DPI */
 if ((strncmp(__strtoken, "DPI", 3) != 0)
  && (strncmp(__strtoken, "DPI-C", 5) != 0)) 
  {
   __pv_ferr(4803, "DPI %s type string (%s) not supported", impextypnam,
    __strtoken);
   goto dpi_error;
  }
 /* SJM 02-11-13 - for current dpi_ only language possible */
 dpip->dpi_language = DPI_LANG_C;

 __get_vtok();
 if (__toktyp == CONTEXT)
  {
   dpip->import_property = DPI_IMPRT_CONTEXT;
   __get_vtok();
  }
 else if (__toktyp == PURE)
  {
   dpip->import_property = DPI_IMPRT_PURE;
   __get_vtok();
  }
 else if (__toktyp == ID)
  {
   /* AIV 08/02/10 - trying special type to pass CVC style arguments */
   if (strcmp(__token, "cvc") == 0)
    {
     dpip->import_property = DPI_CVC_PTRS;
     __get_vtok();
    }
  }

 /* import "DPI-C" cname = function void vname(); */
 /* SJM 01-31-13 - will only have c name if explicitly included in src */
 /* normally will be same as c side task/func name */
 if (__toktyp == ID)
  {
   dpip->cname = __pv_stralloc(__token);
   __get_vtok();
   if (__toktyp != EQ)
    {
     __pv_ferr(4809, "DPI %s rename expecting '=' not (%s)", impextypnam,
      __prt_vtok());
     goto dpi_error;
    }
   __get_vtok();
  }
 else dpip->cname = NULL;

 /* import "DPI-C" function void f1(); */
 if (__toktyp == FUNCTION)
  {
   dpip->dpi_call_type = DPI_TF_FUNC;
   if (!rd_func()) 
    {
     /* DPI export function can only declare name */
     if (__cur_dpip->dpi_type == DPI_EXPORT) 
      {
       __pv_ferr(4812,
        "DPI export must only define function/task name - no input/output header definitions\n");
      }
     goto dpi_error;
    }
   /* can now be void C-style function */
   if (!__cur_tsk->is_void_func) dpip->has_ret = TRUE;
  }
 else if (__toktyp == TASK)
  {
   dpip->dpi_call_type = DPI_TF_TASK;
   if (!rd_task()) 
    {
     if (__cur_dpip->dpi_type == DPI_EXPORT) 
      {
       __pv_ferr(4814,
        "DPI export must only define function/task name - no input/output header definitions\n");
      }
     goto dpi_error;
    }
  }
 else
  {
   __pv_ferr(4815, "DPI %s expecting task/function declaraion not - %s",
    __token, impextypnam);
   goto dpi_error;
  }

 dpip->dpinxt = NULL;
 __vskipto_any(SEMI);

 dpip->dpinxt = NULL;
 if (__dpi_hdrp == NULL) __dpi_hdrp = __dpi_endp = dpip;
 else
  {
   __dpi_endp->dpinxt = dpip;
   __dpi_endp = dpip;
  }

 __cur_dpip = NULL;
 return(TRUE);
}

/*
 * alloc and init dpi record
 */
static struct dpi_t *alloc_init_dpi_rec(void)
{
 struct dpi_t *dpip;

 dpip = (struct dpi_t *) __my_malloc(sizeof(struct dpi_t));
 dpip->dpi_type = DPI_UNKN; 
 dpip->dpi_call_type = DPI_TF_UNKN;
 dpip->dpi_language = DPI_LANG_C;
 dpip->import_property = DPI_IMPRT_UNKN;
 dpip->has_ret = FALSE;
 dpip->imp_fnd_in_lib = FALSE;
 dpip->dsym = NULL;
 dpip->cname = NULL;
 dpip->dpi_tskp = NULL;
 /* only used by interpreter's to generate c */
 dpip->dpi_proc_ndx = -1;
 dpip->dpi_ainfo = NULL;
 dpip->dpinxt = NULL;
 return(dpip);
}
