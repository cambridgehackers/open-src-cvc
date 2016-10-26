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
 * module that fixes and checks net list after all source read
 * all defparam and global processing in v_grf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/dir.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

/* local prototypes */
static void set_all_sym_to_gblk_ptrs(void);
static void set_1gitem_gblksy_elus(struct mod_t *,  struct genitem_t *);
static void set_1gblk_gblksy_elus(struct mod_t *, struct genblk_t *);
static void pre_fixup_dsgn_gens(void);
static void pre_fixup1_genitem(struct genitem_t *);
static void pre_fixup1_genblk(struct genblk_t *);
static void convert_connect1_gen_cell(struct genitem_t *);
static void sep_mdgates(void);
static int32 count_minum_and_mgnum(int32 *, struct mod_t *);
static void cellrep_to_gate(struct cell_t *, struct gate_t *);
static void add_mod_attrs_toinst(struct inst_t *);
static int32 pndparams_explicit(struct namparam_t *, int32 *);
static struct paramlst_t *bld_gate_paramlst(struct namparam_t *);
static void bld_gate_giap(struct mod_t *, struct gate_t *, struct cell_t *);
static void init_gia_aux_rec(struct gia_aux_t *);
static void bld_inst_giap(struct mod_t *, struct inst_t *, struct cell_t *);
static int32 cnt_gateprts(struct cell_t *);
static void cellrep_to_inst(struct cell_t *, struct inst_t *);
static struct expr_t **inst_nparms_to_xtab(struct namparam_t *,
 struct inst_t *);
static struct expr_t **match_namparam_exprtab(struct namparam_t *,
 struct inst_t *);
static int32 chk1_pndparam(char *, struct inst_t *, struct namparam_t *,
 int32, int32);
static int32 prmtab_cmp(const void *, const void *);
static struct expr_t **match_implprm_exprtab(struct namparam_t *,
 struct inst_t *);
static void fix_port_conns(void);
static void setchk_modports(void);
static int32 chk_prtref(struct expr_t *, struct mod_pin_t *, int32);
static int32 chk_prtntyp(struct mod_pin_t *, struct net_t *);
static void conn_mod_insts(void);
static struct srcloc_t *conn1_inst_in_mod(struct inst_t *);
static void conn_impl_mports(struct inst_t *, struct cell_pin_t *,
 struct mod_t *, struct expr_t **, struct srcloc_t *);
static void conn_expl_mports(struct inst_t *, struct cell_pin_t *,
 struct mod_t *, struct expr_t **, struct srcloc_t *);
static int32 chk_mdports_named(struct inst_t *, struct mod_t *, struct expr_t **);
static void bld_srted_mdpins(struct mod_t *);
static int32 smp_cmp(const void *, const void *);
static int32 bld_srted_ipins(struct inst_t *, struct cell_pin_t *, int32,
 struct cell_pin_t **);
static int32 cpn_cmp(const void *, const void *);
static void free_cpblks(void);
static void free_cppblks(void);
static void chg_params_to_tab(void);
static int32 cnt_prms(struct net_t *);
static void free_param_listform(struct net_t *);
static void copy_mod(struct mod_t *, char *);
static struct symtab_t *copy_mod_or_gen_symtabs(struct symtab_t *sytp);
static void copy_lowsymtab(struct symtab_t *, struct symtab_t *);
static struct symtab_t *copy_1symtab(struct symtab_t *);
static struct sy_t **copy_stsyms(struct sy_t **, word32);
static void copy_modports(void);
static void copy_wires(struct symtab_t *, struct symtab_t *);
static struct net_t *copy_1wire_guts(struct net_t *);
static struct mda_t *copy_mda(struct mda_t *);
static struct net_t *copy_params(struct net_t *, int32, int32);
static void copy_defparams(void);
static void copy_insts(void);
static struct attr_t *copy_attrs(struct attr_t *);
static struct varinitlst_t *copy_varinits(struct varinitlst_t *);
static void copy_1inst(struct inst_t *, struct inst_t *);
static void copy_iports(struct inst_t *, struct inst_t *);
static void copy_iploctab(void);
static void copy_gates(void);
static void copy_1gate(struct gate_t *, struct gate_t *);
static void copy_contas(void);
static void copy_mdtasks(void);
static struct task_t *copy1_task(struct task_t *);
static struct task_pin_t *copy_tskargs(struct task_t *);
static struct ialst_t *copy_ialst(struct ialst_t *);
static struct csitem_t *copy_csitemlst(struct csitem_t *);
static struct gref_t *match_in_new_gblk_ogref(struct gref_t *,
 struct genblk_t *);
static struct gref_t *match_in_new_mod_ogref(struct gref_t *, struct mod_t *);
static void turnon_all_net_dumpvars(struct mod_t *);
static void turnon_plitab_from_optcfgfile(void);

static struct exprlst_t *copy_xprlst(struct exprlst_t *);
static void copy_mgrefs(void);
static void copy_1xmr_gref_flds(struct gref_t *, struct gref_t *);
static void copy_1dfp_gref_flds(struct gref_t *, struct gref_t *);
static void copy_specify(void);
static void copy_spcpths(struct spfy_t *, struct spfy_t *);
static void copy_timchks(struct spfy_t *, struct spfy_t *);
static struct tchk_t *copy1_tchk(struct tchk_t *);

static struct genitem_t *copy_genitem_lst(struct genitem_t *,
 struct genblk_t *);
static struct genitem_t *copy1_genitem(struct genitem_t *, struct genitem_t *,
 struct genblk_t *);
static struct gen_for_t *copy1_genfor(struct genitem_t *, struct genblk_t *);
static struct gen_if_t *copy1_genif(struct genitem_t *, struct genblk_t *);
static struct gen_case_t *copy1_gencase(struct genitem_t *, struct genblk_t *);
static struct gen_csitem_t *copy1_csitem(struct gen_csitem_t *,
 struct genblk_t *);
static struct net_t *copy1_gen_vardecl(struct genitem_t *, struct genblk_t *);
static struct ialst_t *copy1_gen_initalw(struct genitem_t *);
static struct conta_t *copy1_gen_conta(struct genitem_t *);
static struct genblk_t *image_copy1_genblk(struct genblk_t *,
 struct genblk_t *);
static void copy_gblk_tasks(struct genblk_t *, struct genblk_t *);
static void copy_gblk_wires(struct genblk_t *, struct genblk_t *);
static void copy_gref_genitems(struct genblk_t *, struct genblk_t *);
static void copy_dfp_genitems(struct genblk_t *, struct genblk_t *);

/* gen local prototypes */
static void resolve_undef_mods(void);
static void process_lib(void);
static void resolve_from_ydir(struct vylib_t *);
static struct undef_t *add_undef_el(struct sy_t *, struct undef_t **,
 struct undef_t **);
static void bld_ylb_dirfiles(struct vylib_t *);
static int32 srch_yfiles(char *, struct mydir_t *, word32);
static int32 fn_cmp(const void *, const void *);
static int32 open_lbfil(int32, int32);
static void rd_vlibfil(struct undef_t *);
static void rescan_process_lib(void);
static void rescan_resolve_from_ydir(struct vylib_t *, struct undef_t *);
static void free_tnblks(void);
static int32 combine_split_mods(struct mod_t *);
static void rebld_splt_comb_nl(void);
static int32 cnt_split_mods(struct mod_t *);
static int32 has_non_combinable_param(struct mod_t *);
static int32 mprmval_cmp(struct mod_t *, struct mod_t *);
static void free_mods_split_list(void);

/* extern prototypes (maybe defined in this module) */
extern int32 __pre_fixup_nl(void);
extern void __fnd_chk_fixup_prep_confuncs(void); 
extern int32 __fixup2_nl(void);
extern void __resolve_xmrs_fr_xmrcmps(void);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern char *__pv_stralloc(char *);
extern struct ncomp_t *__alloc_arrncomp(void);
extern char *__prt_vtok(void);
extern int32 __isleaf(struct expr_t *);
extern struct expr_t *__alloc_newxnd(void);
extern struct exprlst_t *__alloc_xprlst(void);
extern char *__to_ptnam(char *, word32);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_sytyp(char *, word32);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern struct expr_t *__copy_expr(struct expr_t *);
extern struct expr_t *__sim_copy_expr(struct expr_t *);
extern struct genblk_t *__xpnd_copy1_genblk(struct genblk_t *, struct net_t *,
 int32);
extern struct genitem_t *__alloc_init_new_genitem(int32);
extern struct sy_t *__zget_sym(char *, struct sy_t **, word32);
extern struct sy_t *__add_modsym(char *);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct symtab_t *__alloc_symtab(int32);
extern struct paramlst_t *__alloc_pval(void);
extern struct delctrl_t *__alloc_dctrl(void);
extern struct csitem_t *__alloc_csitem(void);
extern struct paramlst_t *__copy_dellst(struct paramlst_t *);
extern char *__bld_lineloc(char *, word32, int32);
extern void __process_timescales(void);
extern void __chk_1mdecls(void);
extern int32 __chk_sv_dpi_lib(void);
extern void __mark_st_wires(void);
extern void __setchk_mpwidths(void);
extern void __chk_shorted_bids(void);
extern void __reconn_gia_pins(void);
extern void __reset_modport_strens(void);
extern int32 __get_optcfg_prop_typ(struct ocfg_stmt_t *);
extern void __prt_top_mods(void);
extern void __chk_mod(void);
extern void __free_icptab(void);
extern void __chkfix_spfy(void);
extern void __free_specify(struct mod_t *);
extern void __free_tchks(struct tchk_t *);
extern void __emit_param_informs(void);
extern void __grow_infils(int32);
extern void __my_free(void *, size_t);
extern void __get_vtok(void);
extern void __process_cdir(void);
extern int32 __vskipto_modend(int32);
extern int32 __vskipto2_modend(int32, int32);
extern int32 __rd_moddef(struct symtab_t *, int32);
extern int32 __rd_udpdef(struct symtab_t *);
extern void __my_rewind(FILE *);
extern void __my_fclose(FILE *);
extern FILE *__tilde_fopen(char *, char *);
extern void __free_xtree(struct expr_t *);
extern void __bld_unc_expr(void);
extern void __in_xpr_markparam(struct expr_t *);
extern int32 __chk_paramexpr(struct expr_t *, int32);
extern void __do_mdsplit(struct mod_t *);
extern struct task_t *__image_copy_confunc(struct task_t *);
extern void __chg_task_prms_to_tab(struct task_t *);
extern void __init_inst(struct inst_t *);
extern void __free_namedparams(struct namparam_t *);
extern int32 __get_arrwide(struct net_t *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern void __set_drvr_bits(void);
extern void __chk_chg_port_dir(int32);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern void __copy_wire_from_wire_array(struct net_t *, struct net_t *);
extern struct dfparam_t *__copy1_defparam(struct dfparam_t *p);
extern struct expr_t **__copy_pndxtab(struct inst_t *);
extern void __copy1_gate_gia_rec(struct gate_t *, struct gia_aux_t *);
extern void __copy1_inst_gia_rec(struct inst_t *, struct gia_aux_t *);
extern struct st_t *__copy_lstofsts(struct st_t *);
extern struct st_t *__copy_stmt(struct st_t *);
extern void __dmp_mod(FILE *, struct mod_t *, int32);
extern int32 __is_net_dumped(struct net_t *);

extern void __dbg_chk_modhdr_list_linking(struct mod_t *);
extern void __chk_dsgn_cpins(struct mod_t *);
extern void __chk_dsgn_ipins(struct mod_t *);
extern void __chk_1mod_cpins(struct mod_t *);
extern void __chk_copied_xpr(struct expr_t *, struct mod_t *);
extern void __free_flat_itree(void);
extern void __bld_flat_itree(void);
extern void __bld_moditps(void);
extern int32 __wide_vval_is0(word32 *, int32);
extern void __merge_same_pval_leaf_splitmods(void);

extern void __cv_msg(char *, ...);
extern void __crit_msg(char *, ...);
extern void __pv_ferr(int32, char *, ...);
extern void __pv_err(int32, char *, ...);
extern void __pv_warn(int32, char *,...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __pv_fwarn(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __finform(int32, char *, ...);
extern void __dbg_msg(char *, ...);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __misc_gfterr(char *, int32, word32, int32);
extern void __add_isnum_to_tree(void *, int32, int32);
extern void __chk_task_thread_needed(struct mod_t *);
static void copy_expr_table(void);
extern void __add_expr_totable(struct expr_t *);

/*
 * PASS 2 NET LIST FIXUP AND GEN ADD ELEMENTS LOOP ROUTINES
 */

/*
 * routine for operations that are not in gen add element loop
 * return F on errors but can return T if errors so caller chks err cnt
 *
 * mostly resolves mods by reading libs and converts some post src
 * read formats 
 *
 * SJM 02-28-09 - if split gen code into separate file, then should move
 * confunc processing code to here since done after all src for a mod done
 */
extern int32 __pre_fixup_nl(void)
{
 /* find and resolve unsatisfied module/udp refs - process lib. in here */
 /* reads more src so must complete before can fixup constant funcs */
 /* SJM 05/19/04 - following new P1364 LRM, config can't be in src */
 if (__map_files_hd == NULL && __undef_mods != 0)
  {
   resolve_undef_mods();
   if (__undef_mods != 0)
    {
     __crit_msg(
      "  %d modules or udps unresolved after library processing - cannot continue.\n",
      __undef_mods);
     return(FALSE);
    }
  }

 /* SJM 01-29-09 - new for all mods find/mark con funcs and eval */ 
 /* parameter ranges and rhs initial value expressions to numbers */
 /* SJM 02-28-09 - this does not emit errors - error chk in other routines */
 __fnd_chk_fixup_prep_confuncs(); 

 /* done with avl style mod sym tabs and know all param lists fixed */
 /* at this point all module and task symbol tables frozen so can free */
 /* the tree nodes (can be large) and change formats */
 free_tnblks();
 chg_params_to_tab();

 /* separate into gates and module instances */
 /* also converts cell term expr. list to array of exprs (never explicit) */
 /* fixup and gen from now on work with insts and gates not cells */

 /* SJM 03-01-09 - can't free cp blocks yet */
 /* SJM 04-21-10 - now also allocates and fill possible gia aux record but */
 /* does not expand yet */
 sep_mdgates();

 /* sep mod gates may find errors but need to run all so caller must */
 /* check for errors, i.e. can't return simple F here on errors */

 /* check module ports and connect inst ports (for iarrs conns unexpanded) */
 fix_port_conns();

 /* need to convert any generate cells here because they are also in */  
 /* cp blks freed after here */
 /* SJM 03-01-09 - new gen pre fixup step - need to convert gates and insts */
 pre_fixup_dsgn_gens();

 /* AIV 06/01/04 FIXME ### ??? bug if config used and free these blocks */
 /* now finished with cell pins and cells */
 if (__map_files_hd != NULL)
  {
   free_cpblks();
   /* this also frees cell pins (optional explicit port name) */
   free_cppblks();
  }

 return(TRUE);
}

/*
 * ROUTINES TO PRE FIXUP (PRE PROCESS GEN) ITEMS 
 */

/*
 * routine to do pre fixup operations on generates
 *
 * SJM 03-03-09 - notice when gen elaborate repeated, pre fixup not 
 * needed although mod hdr list is longer, copying will copy pre fixed nl
 */
static void pre_fixup_dsgn_gens(void)
{
 struct mod_t *mdp;
 struct genitem_t *gip;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* SJM 03-05-09 - must eliminate outside of push/pop of wrk itstk */
   if (mdp->mgenitems == NULL) continue;

   __push_wrkitstk(mdp, 0);

   for (gip = __inst_mod->mgenitems; gip != NULL; gip = gip->geninxt)
    {
     pre_fixup1_genitem(gip);
    }

   /* DBG remove -- */
   if (__debug_flg)
    {
     __dbg_msg(" >>>>> DUMPING MOD SRC WITH GENVARS FOR TYPE %s\n",
      __inst_mod->msym->synam);
      __dmp_mod(stdout, mdp, TRUE);
      __dbg_msg(" <<<<< END OF GEN SRC DMP\n");
    }
   /* --- */

   __pop_wrkitstk();
  }
}

/*
 * pre fixup gen items 
 *
 * for now only convert cells to gates/udps or instances and connects
 * insts to down ports for gen item cells converted to insts
 */ 
static void pre_fixup1_genitem(struct genitem_t *gip)
{
 struct gen_if_t *gifp;
 struct gen_case_t *gcasp;
 struct gen_csitem_t *gcsip;

 switch (gip->gityp) {
  case GI_GBLK:
   pre_fixup1_genblk(gip->giu.gi_gblkp);
   break;
  case GI_GFOR:
   pre_fixup1_genblk(gip->giu.gi_gforp->src_gforblkp);
   break;
  case GI_GIF:
   gifp = gip->giu.gi_gifp;
   pre_fixup1_genblk(gifp->src_then_gblkp);
   if (gifp->src_else_gblkp != NULL) pre_fixup1_genblk(gifp->src_else_gblkp);
   break;
  case GI_GCASE:
   gcasp = gip->giu.gi_gcasp;
   for (gcsip = gcasp->gcsitems; gcsip != NULL; gcsip = gcsip->gcsinxt)
    {
     pre_fixup1_genblk(gcsip->gen_csiblkp);
    }
   break;
  case GI_CELL:
   convert_connect1_gen_cell(gip);
   break;
  default: break;
 }
}

/*
 * pre fixup 1 gen blk's to convert cells to gates/udps or instances
 */
static void pre_fixup1_genblk(struct genblk_t *gblkp)
{
 struct genitem_t *gip;

 for (gip = gblkp->gitems; gip != NULL; gip = gip->geninxt)
  { 
   pre_fixup1_genitem(gip);
  } 
}

/*
 * convert 1 cell to a gate/udp or instance gen item
 * for insts also connects the inst pins to low conn imdp
 *
 * know cell's mod tye declared or will not get here even if eventually
 * cell never instanciated
 *
 * do not need to free the cells because when cpblks are freed the cells
 * will also be freed
 */
static void convert_connect1_gen_cell(struct genitem_t *gip)
{
 struct cell_t *gcp;
 struct gate_t *gp;
 struct inst_t *ip;
 struct srcloc_t *srclocp;

 gcp = gip->giu.gi_cp;
 /* SJM 03-11-11 - try to still expand to check gened cells - if prev */ 
 /* syntax errors may not be filled */
 if (gcp->cmsym == NULL || !gcp->cmsym->sydecl)
  {
   __sgferr(3621, 
    "generated module instance never constructed - probably earlier error");
   return;
  }

 /* SJM 04-21-10 - now gates/insts have ptr to arr aux rec - this just works */

 /* case 1: udp or gate */ 
 if (gcp->cmsym->sytyp == SYM_UDP || gcp->cmsym->sytyp == SYM_PRIM)
  {
   /* gate do not need to be named */
   gp = (struct gate_t *) __my_malloc(sizeof(struct gate_t));
   cellrep_to_gate(gcp, gp);
   if (gcp->cx1 != NULL) bld_gate_giap(__inst_mod, gp, gcp);
   gip->giu.gi_gp = gp;
   gip->gityp = GI_GATE; 
   return;
  }

 /* case 2 instance */
 if (!gcp->c_named)
  {
   __gferr(3607, gcp->csym->syfnam_ind, gcp->csym->sylin_cnt,
    "generated module instance required local name missing (type is %s)",
    gcp->cmsym->synam);
   return;
  }
 /* inst's do not have next field but know only one pointed by by gen item */
 ip = (struct inst_t *) __my_malloc(sizeof(struct inst_t)); 
 cellrep_to_inst(gcp, ip);
 /* SJM 05-03-10 - must also build inst array aux record for arrays in gblks */
 if (gcp->cx1 != NULL) bld_inst_giap(__inst_mod, ip, gcp);

 srclocp = conn1_inst_in_mod(ip);
 gip->giu.gi_igp = (struct inst_gen_t *)
  __my_malloc(sizeof(struct inst_gen_t));
 gip->gityp = GI_INST; 
 gip->giu.gi_igp->ip = ip;
 /* point to contained inst's per port hiconn src loc */ 
 gip->giu.gi_igp->srclocp = srclocp;

 /* SJM 03-11-11 this inst used in gen, might be generated later */
 /* could possibilty be top mod now, but will change later */
 /* expansion must converge so if top do these last */
 ip->imsym->el.emdp->m_maybe_gened = TRUE;
}

/*
 * 2nd part of fixup (pass 2 routines)
 *
 * called after gen finished and know all param vals and inst tree and
 * XMRs - does most of the run time element checking
 */
extern int32 __fixup2_nl(void)
{
 struct mod_t *mdp; 
 int32 tmp;
 struct task_t *tskp;
 int32 numtasks, i;

 /* AIV 02/03/12 - if compiled try to take leaf modules with matching */
 /* parameter values and combine - needs to go prior to xmr building */
 __merge_same_pval_leaf_splitmods();

 /* 03-27-11 - need genblk sym to gblk el_u ptrs to resolve XMRs (defps done) */
 set_all_sym_to_gblk_ptrs();

 /* SJM 03-16-10 - resolve xmrs by filling grefs from xmrcmp tables */
 __resolve_xmrs_fr_xmrcmps();
 
 /* SJM 04-09-11 - if errors resolving xmrs - must give up - will core dump */
 if (__pv_err_cnt != 0) return(TRUE);

 /* SJM 02-27-09 - only need timescale for chk of decls that chks delays */
 /* set timescale info before module checking that converts delays to ticks */
 __process_timescales();

 /* now all parameter values known */
 /* must check decl. and eval. wire params before setting port widths */
 /* must always have at least dummy itree context set for these */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
 
   /* LOOKATME maybe could change to scheme where one mod net table */
   /* contains all mod nets and regs decled in all tasks since one set */
   /* per task - SJM 02/29/00 - yes moved chk taskvars to chk 1 mdecls */
   __chk_1mdecls();
   
   __pop_wrkitstk();
  }

 /* SJM 01-30-13 - moved existence of dpi_ library back as far as possible */
 /* without the sv -lib option libraries for dpi imports think should */
 /* not check RTL - could move back more maybe? ext chk mod chks dpi args */
 if (__dpi_hdrp != NULL)
  {
   if (!__chk_sv_dpi_lib() || __pv_err_cnt != 0) return(TRUE); 
  }

 /* SJM 05/23/01 - can't guess port types until ranges known as exprs */
 /* set net per bit drvrs class (type) and change port dir if option on, */
 /* else warns */
 /* must do this after xmr's resolved and know ranges so can access xmr net */ 
 __set_drvr_bits();
 __chk_chg_port_dir(__chg_portdir);

 /* AIV 10/07/10 - need a routine to do the +dumpvars which turns on the */
 /* dmpv bits */
 if (__dmpvars_all)  
  {
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     turnon_all_net_dumpvars(mdp);
    }
  }
 /* at this point all wire widths known */

 /* if no arrays of gate or instances in design, can set strengths now */ 
 if (!__design_gi_arrays) __mark_st_wires();

 /* mod port widths set here, widths now known - inst. width set in chk mod */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   __setchk_mpwidths();
   __chk_shorted_bids();

   /* must make sure module level symbols are all marked as top level */
   mdp->msym->spltsy = NULL;

   __pop_wrkitstk();
  }

 if (__design_gi_arrays)
  {
   __reconn_gia_pins();
   /* mark wire that have strength storage format */
   __mark_st_wires();
   /* now set strength in port expr. bits if lhs with strength variable */
   /* only check exprs (because need size) at this point are ports */
   __reset_modport_strens();
  }

 /* if decl. errors cannot continue - do not know port widths */
 /* and probably have missing expr. node fields */
 if (__pv_err_cnt != 0) return(TRUE);

 if (!__quiet_msgs) __prt_top_mods();

 numtasks = 0;
 if (__compiled_sim)
  {
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
      {
       numtasks++;
      }
    }

   if (numtasks > 0)
    {
     for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
      {
       for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
        {
         tskp->called_tasks = (struct task_t **) 
          __my_malloc(numtasks*sizeof(struct task_t *));
         for (i = 0; i < numtasks; i++)
          {
           tskp->called_tasks[i] = NULL;
          }
        }
      }
    }
  }

 /* AIV 02/14/11 - this needs to go before chk_stmts since there are some */
 /* places which check for pli calls here and depend on __pli_access to */
 /* be set - this optconfig can also set this so it needs to be done by here */
 turnon_plitab_from_optcfgfile();

 /* check mainly element usage semantics */
 /* expression node widths and constant optimizations here */
 /* statement checking here */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   __chk_mod();
   __pop_wrkitstk();
  }

 tmp = __has_dmpv_sys_calls + __is_fst;

 /* user must use one or the other */
 if (tmp > 1)
  {
   __pv_ferr(1399,
    "Design contains a mix of $dumpvars/$fst calls - currenlty CVC only supports one dumping method at a time.\n");
  }
 else if (__is_fst)
  {
   if (__dv_fnam != NULL) __my_free(__dv_fnam, strlen(__dv_fnam));
   __dv_fnam = __pv_stralloc(DFLFSTFNAM);
  }

 if (__compiled_sim)
  {
   if (numtasks > 0)
    {
     for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
      {
       __chk_task_thread_needed(mdp);
      }
     for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
      {
       for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
        {
         __my_free(tskp->called_tasks, numtasks*sizeof(struct task_t *));
        }
      }
    }
  }

 /* free iploctab (line no. per contained mod port) shared among split */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   __free_icptab();
   __pop_wrkitstk();
  }

 /* -- specify fixup (pass 2) routines in v fx3 but also expr checking */

 /* check and fix up expressions from specify section */
 /* also emit all unused parameter (both types warnings */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   if (mdp->mspfy != NULL)
    {
     __chkfix_spfy();
     if (__no_specify)
      { __free_specify(mdp); mdp->mspfy = NULL; } 
     else if (mdp->mspfy->tchks != NULL && __no_tchks)
      {
       __free_tchks(mdp->mspfy->tchks);
       mdp->mspfy->tchks = NULL;
      }
    }
   __emit_param_informs();
   __pop_wrkitstk();
  }

 return(TRUE);
}

/*
 * first step after generate done, set mod's mgen_symtab gblk symbol
 * egblkp link to the genblk (sym tab has final gened symbols still)
 *
 * gblks and mgen symtab for final gens kept around still
 */
static void set_all_sym_to_gblk_ptrs(void)
{
 struct mod_t *mdp;
 struct genitem_t *gip;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mgenitems == NULL) continue;

   for (gip = mdp->mgenitems; gip != NULL; gip = gip->geninxt) 
    {
     set_1gitem_gblksy_elus(mdp, gip);
    }
  }
}

/*
 * set gblk name symbol e gblkp el_u ptr back to genblk 
 */ 
static void set_1gitem_gblksy_elus(struct mod_t *mdp,  struct genitem_t *gip)
{
 int32 gti;
 struct gen_for_t *gforp;
 struct gen_if_t *gifp;
 struct gen_case_t *gcasp;

 switch (gip->gityp) {
  case GI_GBLK:
   set_1gblk_gblksy_elus(mdp, gip->giu.gi_gblkp);
   break;
  case GI_GFOR:
   gforp = gip->giu.gi_gforp;
   for (gti = 0; gti < gforp->ngenblks; gti++)
    {
     /* SJM 03-04-09 - gen table may be sparse */ 
     if (gforp->gentab[gti] == NULL) continue;

     set_1gblk_gblksy_elus(mdp, gforp->gentab[gti]);
    }
   break;
  case GI_GIF:
   gifp = gip->giu.gi_gifp;
   /* SJM 03-07-09 - if empty gen if, i.e. nothing gened, nothing to do */
   if (gifp->ngenblks == -1) break;
   if (gifp->ngenblks != 1) __misc_terr(__FILE__, __LINE__); 
   set_1gblk_gblksy_elus(mdp, gifp->gentab[0]);
   break;
  case GI_GCASE:
   gcasp = gip->giu.gi_gcasp;
   /* SJM 03-07-09 - if empty gen case, i.e. nothing gened, nothing to do */
   if (gcasp->ngenblks == -1) break;

   /* DGB remove -- */
   if (gcasp->ngenblks != 1) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   set_1gblk_gblksy_elus(mdp, gcasp->gentab[0]);
   break;
  /* gened mod items ignored */
 }
}

/*
 * add gen items inside one genblk to gen item list
 *
 * also adds nets (in gen blk declared or implicitly declared from use)
 * nets to mod's mgen sytab
 */
static void set_1gblk_gblksy_elus(struct mod_t *mdp, struct genblk_t *gblkp)
{
 struct sy_t *syp;
 struct genitem_t *gip;

 if ((syp = __get_sym(gblkp->gblknam, mdp->mgen_symtab)) == NULL)
  __misc_terr(__FILE__, __LINE__);

 /* DBG remove -- */
 if (syp->sytyp != SYM_LGB) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* SJM 03-27-11 - set egblkp for everything gened before xmr resolving */
 syp->el.egblkp = gblkp;

 for (gip = gblkp->gitems; gip != NULL; gip = gip->geninxt)
  {
   set_1gitem_gblksy_elus(mdp, gip);
  }
}
     
/*
 * AIV 10/07/10 - need a routine to do the +dumpvars which turns on the
 * flag for all nets.  This used to be just set in v_src.c when a net
 * was alloc, but since new SV types (string)are not always dumped must do 
 * after net types are set 
 */
static void turnon_all_net_dumpvars(struct mod_t *mdp)
{
 int32 ni;
 struct net_t *np;
 struct task_t *tskp;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   /* AIV 07/21/10 - this should have never turned these bits on for */
   /* arrays - now allowing dumping of arrays */
   if (np->n_isarr && !__dump_arrays) continue;
   if (__is_net_dumped(np)) 
    {
     np->dmpv_in_src = TRUE;
     np->nu.ct->dmpv_in_src = TRUE;
    }
  } 
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   if (tskp->trnum == 0) continue;
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {
     if (np->n_isarr && !__dump_arrays) continue;
     if (__is_net_dumped(np)) 
      {
       np->dmpv_in_src = TRUE;
       np->nu.ct->dmpv_in_src = TRUE;
      }
    }
  }
}

/*
 * turn on the pli access properties needed in design from optcfgfile
 *
 * SJM 03-24-13 - this must be done during early fixup2 nl (but after gen)
 * only sees which properties used and does not syntax checking of
 * optconfigfile statements so just works
 *
 * AIV 02/14/12 - if do_pli_only maybe turn on __pli_access and continue
 * SJM 10-30-12 - all first pass does is set pli access level glb 
 * SJM 03-22-13 - in fixup2 nl just after generate, this set some glbs 
 */
static void turnon_plitab_from_optcfgfile(void)
{
 struct ocfil_lst_t *ocfnp;
 struct ocfg_stmt_t *ocstmtp;

 /* indicating some pli is needed during fixup 2 */
 for (ocfnp = __optcfg_fils; ocfnp != NULL; ocfnp = ocfnp->oclnxt)
  {
   /* AIV 10/24/11 - this needs ptr to not copy */
   /* only turn on __pli_access if needed here */
   __cur_fnam = ocfnp->ocfnam;
   for (ocstmtp = ocfnp->oc_stmts; ocstmtp != NULL; ocstmtp = ocstmtp->ocsnxt) 
    {
     /* SJM 03-24-13 - other opt config file flags also maybe set but */ 
     /* think not needed and turned on later - leaving all for now */

     /* this does not use return masks */
     __get_optcfg_prop_typ(ocstmtp);
    }
  }
}

/*
 * routine to print top level modules - on one line
 * always printed unless -q on
 */
extern void __prt_top_mods(void)
{
 int32 tpii;
 struct inst_t *ip;

 __cv_msg("Highest level modules:\n");
 for (tpii = 0; tpii < __numtopm; tpii++)
  {
   ip = __top_itab[tpii];
   __cv_msg("%s\n", ip->imsym->synam);
  }
}

/*
 * MODULE DECLARATION CHECKING AND LIBRARY RESOLUTION ROUTINES
 */

/*
 * resolve all undefined modules and udps
 */
static void resolve_undef_mods(void)
{
 struct undef_t *undefp;
 struct sy_t *syp;

 /* try to satisfy unresolved modules/udps from -y, -v or - lib. */
 /* check for remaining unresolveds, cannot continue if any */
 if (__vyhdr != NULL)
  {
   if (__lib_rescan) rescan_process_lib();
   else process_lib();
  }
 if (__undef_mods > 0)
  {
   /* notice this must be printed no matter what */
   __crit_msg("Unresolved modules or udps:\n");
   for (undefp = __undefhd; undefp != NULL; undefp = undefp->undefnxt)
    {
     syp = undefp->msyp;
     if(syp->sydecl || !syp->syundefmod) __misc_terr(__FILE__, __LINE__);
     __crit_msg("  %s\n", syp->synam);
    }
   __crit_msg("\n");
  }
 /* if libverbose messages need to separate */
 else if (__lib_verbose) __cv_msg("\n");
}

/*
 * process library to attempt to resolve all unresolved libraries
 * only called if unresolved modules/udps remain
 */
static void process_lib(void)
{
 int32 num_passes, cur_ifi;
 struct undef_t *undefp;
 struct vylib_t *vyp;
 struct sy_t *syp;

 /* go thru libs in order */
 for (num_passes = 1;; num_passes++)
  {
   if (num_passes > 1) __rescanning_lib = TRUE;

   __cur_passres = 0;
   if (__lib_verbose)
    {
     /* notice only unresolved after 1st pass are interesting */
     if (num_passes > 1) 
      {
       __cv_msg("\n  Library scan pass %d with the following %d undefined:\n",
        num_passes, __undef_mods);
       for (undefp = __undefhd; undefp != NULL; undefp = undefp->undefnxt)
        {
         syp = undefp->msyp;
         __cv_msg("    %s (first reference %s)\n", syp->synam,
          __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt));
        }
      }
     else __cv_msg("\n  Begin library scan pass %d (%d undefined).\n",
      num_passes, __undef_mods);
    }

   for (vyp = __vyhdr; vyp != NULL; vyp = vyp->vynxt)
    {
     /* AIV 11/11/03 - if -y dir is empty changed to 'e' so do nothing */
     /* this handles multiple passes empty directories */
     if (vyp->vytyp == 'e') continue;

     if (vyp->vytyp == 'y')
      {
       if (vyp->yfiles == NULL) bld_ylb_dirfiles(vyp);

       /* AIV 11/11/03 - if -y dir is empty made 'e' and must do nothing */
       if (vyp->vytyp == 'e') continue;

       resolve_from_ydir(vyp);
       if (__undef_mods <= 0) return;
       continue;
      }

     /* add or reuse -v library file to in_fils */
     if (vyp->vyfnam_ind == 0)
      {
       /* this dies if >64k */
       if (++__last_lbf >= __siz_in_fils) __grow_infils(__last_lbf);
       vyp->vyfnam_ind = __last_lbf;
       __in_fils[__last_lbf] = __pv_stralloc(vyp->vyu.vyfnam);
      }

     cur_ifi = vyp->vyfnam_ind;
     /* AIV 05/23/12 - my fix for this was bad using SJM fix which just */
     /* passes the index - no longer a need to save/restore */
     /* know this will leave undef_mods with correct value */
     if (open_lbfil(cur_ifi, FALSE)) rd_vlibfil(NULL);
     if (__undef_mods <= 0) return;
    }
   if (__cur_passres == 0)
    {
     __pv_err(706,
      "%d modules or primitives unresolved after pass %d with no progress",
      __undef_mods, num_passes);
     return;
    }
  }
}

/*
 * resolve unresolved references from a library directory
 * tricky because resolve as go along effecting __undefhd list
 *
 * algorithm is:
 * 1) go through all unresolved and find all files that match any suffix
 *    and add to list
 * 2) then read and scan all files for any (not just names that produced
 *    file by adding +lbext+ suffix) unresolved - quits in case all resolved
 */
static void resolve_from_ydir(struct vylib_t *vyp)
{
 int32 lbxi, dfi, got_err, cur_ifi;
 struct undef_t *undefp;
 struct undef_t *tmphd, *tmptail, *tmpundefp, *undefp2;
 char fnam[IDLEN], stem[IDLEN];

 tmphd = tmptail = NULL;
 /* build stem that gives current path to directory */
 sprintf(stem, "%s/", vyp->vyu.vydirpth);
 /* case 1: no lbext - module name must exactly match file name */
 if (__last_lbx == -1)
  {
   for (undefp = __undefhd; undefp != NULL; undefp = undefp->undefnxt)
    {
     if ((dfi = srch_yfiles(undefp->msyp->synam, vyp->yfiles, vyp->vyfnam_ind))
      == -1 ) continue;
     /* add to tmp list since parsing changes __undefhd list */ 
     tmpundefp = add_undef_el(undefp->msyp, &tmphd, &tmptail); 
     tmpundefp->dfi = dfi;
     vyp->yfiles[dfi].ylbxi = 0;
    }
  }
 else
  {
   /* case 2: must add lbext to module name and see if matches */
   /* build temporary list of all */
   for (undefp = __undefhd; undefp != NULL; undefp = undefp->undefnxt)
    {
     for (lbxi = 0; lbxi <= __last_lbx; lbxi++)
      {
       sprintf(fnam, "%s%s", undefp->msyp->synam, __lbexts[lbxi]);
       if ((dfi = srch_yfiles(fnam, vyp->yfiles, vyp->vyfnam_ind)) == -1)
        continue;

       /* add to tmp list since parsing changes __undefhd list */ 
       tmpundefp = add_undef_el(undefp->msyp, &tmphd, &tmptail); 
       tmpundefp->dfi = dfi;
       vyp->yfiles[dfi].ylbxi = lbxi;
       /* when found, from precedence rules must stop looking */
       break;
      }
    }
  }
 /* go through temp list reading file */
 for (undefp = tmphd; undefp != NULL; undefp = undefp->undefnxt)
  {
   dfi = undefp->dfi;
   if (vyp->yfiles[dfi].ydirfnam_ind == 0)
    {
     /* this dies if >64k */
     if (++__last_lbf >= __siz_in_fils) __grow_infils(__last_lbf);
     vyp->yfiles[dfi].ydirfnam_ind = __last_lbf;
     if (__last_lbx == -1) sprintf(fnam, "%s%s", stem, undefp->msyp->synam);
     else
      {
       lbxi = vyp->yfiles[dfi].ylbxi;
       sprintf(fnam, "%s%s%s", stem, undefp->msyp->synam, __lbexts[lbxi]);
      }
     __in_fils[__last_lbf] = __pv_stralloc(fnam);
    }
   /* notice each lib. file increments this by 1 */
   cur_ifi = vyp->yfiles[dfi].ydirfnam_ind;
   got_err = FALSE;

   if (open_lbfil(cur_ifi, FALSE)) rd_vlibfil(NULL); else got_err = TRUE;
   if (got_err) continue;
   /* if scanned because of a module and still unresolved after scanning */
   /* need warning - i.e. it is legal to not resolve in name matching */
   /* module but unrecommended */
   if (!undefp->msyp->sydecl)
    {
     __pv_warn(510,
      "module %s still unresolved after processing library directory file %s",
      undefp->msyp->synam, __in_fils[vyp->yfiles[dfi].ydirfnam_ind]);
    }
   else break;
  }
 /* final step is to free temp undef list */
 for (undefp = tmphd; undefp != NULL;) 
  {
   undefp2 = undefp->undefnxt;
   __my_free(undefp, sizeof(struct undef_t)); 
   undefp = undefp2;
  }
}

/*
 * add to tail of undef list that is only singly linked
 */
static struct undef_t *add_undef_el(struct sy_t *syp,
 struct undef_t **hd, struct undef_t **tail)
{
 struct undef_t *undefp;

 undefp = (struct undef_t *) __my_malloc(sizeof(struct undef_t));
 undefp->msyp = syp;
 undefp->dfi = -1; 
 undefp->modnam = NULL; 
 undefp->undefprev = undefp->undefnxt = NULL;
 if (*tail == NULL) *hd = *tail = undefp;
 else { (*tail)->undefnxt = undefp; *tail = undefp; }
 return(undefp);
}

/*
 * preprocess 1 -y library directory - build entry for each file
 * this builds sorted yfiles array
 *
 * notice done only once and saved
 */
static void bld_ylb_dirfiles(struct vylib_t *vyp)
{
 int32 last_fi, numdfils, siz_mydir, bytlen, obytlen;
 DIR *dirp;
 /* all linux cases and special case interface for non unices */
 struct direct *dp;
 struct mydir_t *mdtab; 

 if ((dirp = opendir(vyp->vyu.vyfnam)) == NULL)
  {
   __pv_warn(511, "-y directory name %s not found - ignored",
    vyp->vyu.vydirpth);
   return;
  }
 siz_mydir = 256;
 bytlen = siz_mydir*sizeof(struct mydir_t);
 mdtab = (struct mydir_t *) __my_malloc(bytlen);
 for (last_fi = -1;;)
  {
   /* should check error number here for other than end of file */
   if ((dp = readdir(dirp)) == NULL) break;
   if (*dp->d_name == '.' && (strcmp(dp->d_name, ".") == 0
    || strcmp(dp->d_name, "..") == 0)) continue;

   if (++last_fi >= siz_mydir)
    {
     obytlen = bytlen;
     siz_mydir = 2*siz_mydir; 
     bytlen = siz_mydir*sizeof(struct mydir_t); 
     /* know initial section copied */
     mdtab = (struct mydir_t *) __my_realloc(mdtab, obytlen, bytlen); 
    }  
   mdtab[last_fi].ydirfnam_ind = 0;
   mdtab[last_fi].ylbxi = 0;
   mdtab[last_fi].dirfnam = __pv_stralloc(dp->d_name);
  }
 closedir(dirp);
 numdfils = last_fi + 1;

 /* AIV 11/11/03 could be an empty directory for -y, free, return */
 if (numdfils == 0)
  {
   __my_free(mdtab, bytlen);
   __pv_warn(3114, "-y directory %s empty - ignored", vyp->vyu.vydirpth);
   /* set vy type to 'e' to prevent any further attmpts to rebuild */
   vyp->vytyp = 'e';
   return;
  }

 /* final step, shrink my directory table back to exact size */
 if (numdfils != siz_mydir) 
  {
   obytlen = bytlen;
   bytlen = numdfils*sizeof(struct mydir_t); 
   mdtab = (struct mydir_t *) __my_realloc(mdtab, obytlen, bytlen); 
  } 
 qsort((char *) mdtab, (word32) numdfils, sizeof(struct mydir_t), fn_cmp); 
 vyp->vyfnam_ind = numdfils;
 vyp->yfiles = mdtab;
 __num_ys++;
}

/*
 * find index in sorted -y directory yfiles table
 */
static int32 srch_yfiles(char *nam, struct mydir_t *mdtab, 
 word32 numdfiles)
{
 int32 l, h, m, cv;

 if (numdfiles == 0) return(-1);
 l = 0; h = numdfiles - 1;
 for (;;)
  {
   m = (l + h)/2;
   if ((cv = strcmp(mdtab[m].dirfnam, nam)) == 0) return(m);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) break;
  }
 return(-1);
}

/*
 * module port name comparison routine
 */
static int32 fn_cmp(const void *dp1, const void *dp2)
{
 return(strcmp(((struct mydir_t *) dp1)->dirfnam,
  ((struct mydir_t *) dp2)->dirfnam));
}

/*
 * process a -v or in -y directory file - must try to resolve all modules
 * know file open and no token read and normal source input env. set
 * caller must open and close file
 *
 *
 * if lib rescan only resolve one passed undefp and stop when resolved
 *
 * LOOKATME _ better here to save byte location from ftell and seek to byte
 * for defined before used definitions but for now cannot do because do
 * not have mechanism for saving and restoring compiler directive state?
 */
static void rd_vlibfil(struct undef_t *res_undefp)
{
 int32 nd_repeat, len, rewind_pass;
 struct undef_t *hd, *tail, *undefp, *undefp2;
 struct sy_t *syp;
 char *chp, savtoken[IDLEN];

 rewind_pass = 0;
again:
 rewind_pass++;
 hd = tail = NULL; 
 __get_vtok();
 if (__toktyp == TEOF)
  { __pv_fwarn(609, "library file contains no tokens"); return; }

 for (;;)
  {
   /* may be a compiler directive */
   if (__toktyp >= CDIR_TOKEN_START && __toktyp <= CDIR_TOKEN_END)
    {
     __process_cdir();
     goto nxt_tok;
    }
   switch (__toktyp) {
    case MACROMODULE:
     __get_vtok();
     __finform(423,
      "macromodules in library not expanded - %s translated as module",
      __token);
     goto chk_name;
    case MODULE:
     __get_vtok();
chk_name:
     if (__toktyp != ID)
      {
       __pv_ferr(707, "in library file, module name expected - %s read",
        __prt_vtok());
       /* since error, just try to resynchronize */
       __vskipto_modend(ENDMODULE);
       goto nxt_tok;
      }

     /* if rescan specific one to resolve skip all but that one */
     if ((syp = __get_sym(__token, __modsyms)) == NULL || syp->sydecl
      || (res_undefp != NULL && syp != res_undefp->msyp))
      { 
       /* must save module name - skip overwrites */
       strcpy(savtoken, __token);
       if (!__vskipto_modend(ENDMODULE))
        { 
         __pv_ferr(767, 
         "syntax error in skipped (defined or not referenced) library module %s",
          __token);
         goto nxt_tok;
        }
try_add_unref:
       /* if symbol never referenced up to here may be define before use */
       /* so need to add to list in case reference nearer end */
       /* for rescan mode, this inhibits any rescanning */
       if (syp == NULL && !__lib_rescan)
        {
         undefp = add_undef_el((struct sy_t *) NULL, &hd, &tail); 
         chp = __pv_stralloc(savtoken);
         undefp->modnam = chp;
        }
       goto nxt_tok;
      }   

     /* notice name token read - also undef_mods not changed */
     if (__lib_verbose)
      __cv_msg("  Elaborating library module (%s).\n", __token);
     /* know error here will cause skipping to file level thing */
     if (!__rd_moddef(NULL, FALSE)) goto nxt_tok;
     /* when reading source this was set only if in cell define region */
     /* now turn on (maybe again) if all library modules are cells */
     /* dummy itstk empty here but if good module read mark as cell */
     if (__lib_are_cells && __last_libmdp != NULL)
      {
       __last_libmdp->m_iscell = TRUE;
       __design_has_cells = TRUE;
      }
     __last_libmdp = NULL;
     /* know to get here 1 more resolved */
     __cur_passres++;
     if (__undef_mods <= 0 || __lib_rescan) return;
     break;

    case PRIMITIVE:
     __get_vtok();
     if (__toktyp != ID)
      {
       __pv_ferr(708, "library file udp primitive name expected - %s read",
	__prt_vtok());
       /* since err, just try to skip to end primitive */
       __vskipto_modend(ENDPRIMITIVE);
       goto nxt_tok;
      }
     /* if rescan specific one to resolve skip all but that one */
     if ((syp = __get_sym(__token, __modsyms)) == NULL || syp->sydecl
      || (res_undefp != NULL && syp != res_undefp->msyp))
      { 
       /* must save module name - skip overwrites */
       strcpy(savtoken, __token);
       if (!__vskipto_modend(ENDPRIMITIVE))
        {
         __pv_ferr(702,
	  "syntax error in skipped (defined or not referenced) library primitive %s",
          __token);
         goto nxt_tok;
        }
       goto try_add_unref;
      }
     /* notice name token read */
     if (__lib_verbose)
      __cv_msg("  Elaborating library udp primitive (%s).\n", __token);
     if (!__rd_udpdef(NULL)) goto nxt_tok;
     /* if all modules resolved, nothing more to do */
     __cur_passres++;
     if (__undef_mods <= 0 || __lib_rescan) return;
     break;
    default:
     __pv_ferr(709,
     "library file module, primitive or directive expected - %s read",
      __prt_vtok());
     /* here just ignores extra semicolons */
     if (__toktyp != SEMI) __vskipto2_modend(ENDMODULE, ENDPRIMITIVE);
   }
nxt_tok:
   /* why checking this twice */
   if (__toktyp == TEOF)
    {
chk_ifdef:
     if (__in_ifdef_level != 0)
      {
       __pv_err(924, "last `ifdef unterminated in libary file %s",
        __cur_fnam);
      }
     break;
    }
   __get_vtok();
   if (__toktyp == TEOF) goto chk_ifdef;
 }
 /* need to determine if any of the skipped modules or udp's now undefined */
 nd_repeat = FALSE;
 for (undefp = hd; undefp != NULL; undefp = undefp->undefnxt) 
  {
   /* SJM 06/03/02 - change so undef list no longer shares undefprev */
   chp = (char *) undefp->modnam;
   /* DBG remove --- */
   if (chp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   
   if ((syp = __get_sym(chp, __modsyms)) != NULL && !syp->sydecl)
    {
     nd_repeat = TRUE; 
     if (!__lib_verbose) break;
     __cv_msg(
      "  Rereading %s library element %s defined before use (pass %d).\n",
      __cur_fnam, syp->synam, rewind_pass);
    }
  } 

 /* go through freeing list */
 for (undefp = hd; undefp != NULL;) 
  {
   undefp2 = undefp->undefnxt;
   /* LOOKATME - think will always be set here */ 
   if (undefp->modnam != NULL)
    {
     chp = undefp->modnam;
     len = strlen(chp);
     __my_free(chp, len + 1);
    }
   __my_free(undefp, sizeof(struct undef_t)); 
   undefp = undefp2;
  }
 if (nd_repeat)
  {
   __my_rewind(__in_s);
   /* in case hit eof with push back make sure reads 1st token */
   __lasttoktyp = UNDEF;
   __lin_cnt = 1;
   __file_just_op = TRUE;
   goto again;
  }
}

/*
 * try to open the next library file and repl. top of stack with its info
 * file must be openable and have contents
 * return F on no success
 * in fils of last lbf must be filled with file name
 * since know last_lbf > last_inf - on EOF get_vtok will resturn to caller
 */
static int32 open_lbfil(int32 ifi, int32 is_dir)
{
 /* if not first time, close previous file */
 if (__visp->vi_s != NULL) { __my_fclose(__visp->vi_s); __visp->vi_s = NULL; }
 /* know called with last_lbf index of file to process */
 __cur_fnam = __in_fils[ifi];
 if ((__in_s = __tilde_fopen(__cur_fnam, "r")) == NULL)
  {
   if (is_dir) strcpy(__xs, " directory"); else strcpy(__xs, "");
   __pv_err(710, "cannot open Verilog library%s file %s - skipped", __xs,
    __cur_fnam);
   return(FALSE);
  }
 if (feof(__in_s))
  {
   __pv_warn(512, "Verilog library file %s empty", __cur_fnam);
   return(FALSE);
  }
 /* whenever open new file must discard pushed back */
 __lasttoktyp = UNDEF;
 __visp->vi_s = __in_s;
 __visp->vifnam_ind = ifi;
 __cur_fnam_ind = ifi;
 __cur_fnam = __in_fils[__cur_fnam_ind];
 __lin_cnt = 1;
 __file_just_op = TRUE;
 if (__lib_verbose)
  {
   if (is_dir)
    __cv_msg("  Opening library directory file \"%s\".\n", __cur_fnam);
   else __cv_msg("  Scanning library file \"%s\".\n", __cur_fnam);
  }
 return(TRUE);
}

/*
 * RESCAN LIBRARY RESOLUTION ROUTINES 
 */
 
/*
 * process library to attempt to resolve all unresolved libraries
 * only called if unresolved modules/udps remain
 *
 * BEWARE - must not free memory of linked out resolved undefp for
 * 2 reasons: 1) need it for error msgs, 2) need next field to move in list
 */
static void rescan_process_lib(void)
{
 int32 passi, cur_ifi;
 struct undef_t *undefp, *sav_undefhd;
 struct vylib_t *vyp;
 struct sy_t *syp;

 if (__lib_verbose)
  {
   __cv_msg("\n  Begin rescan mode library resolution (%d undefined).\n",
    __undef_mods);
  }

 /* goto through unresolved resolving one per pass */
 /* resolution of one may add other to end, but next field will */
 /* be right for new */
 passi = 1; 
 for (undefp = __undefhd; undefp != NULL; passi++)
  {
   /* AIV 10/10/03 - undefhd may be removed and then new undefhd added as */
   /* unresolved so must save and replace if changed */
   sav_undefhd = __undefhd;

   if (passi > 1) __rescanning_lib = TRUE;

   if (__lib_verbose)
    {
     syp = undefp->msyp;
     __cv_msg("\n  Resolving %s (first reference %s)(pass %d)\n",
      syp->synam, __bld_lineloc(__xs, syp->syfnam_ind, syp->sylin_cnt), passi);
    }
   __cur_passres = 0;
   for (vyp = __vyhdr; vyp != NULL; vyp = vyp->vynxt)
    {
     /* AIV 11/11/03 - if -y dir is empty changed to 'e' so do nothing */
     /* this handles empty directories for rescanning */
     if (vyp->vytyp == 'e') continue;

     if (vyp->vytyp == 'y')
      {
       if (vyp->yfiles == NULL) bld_ylb_dirfiles(vyp);

       /* AIV 11/11/03 - if -y dir is empty made 'e' and must do nothing */
       if (vyp->vytyp == 'e') continue;

       rescan_resolve_from_ydir(vyp, undefp);
       if (__cur_passres == 0) continue;

       /* DBG remove -- */
       if (__cur_passres != 1) __misc_terr(__FILE__, __LINE__);
       /* --- */
       goto resolve_nxt;
      }

     /* add or reuse -v library file to in_fils */
     if (vyp->vyfnam_ind == 0)
      {
       /* this dies if >64k */
       if (++__last_lbf >= __siz_in_fils) __grow_infils(__last_lbf);
       vyp->vyfnam_ind = __last_lbf;
       __in_fils[__last_lbf] = __pv_stralloc(vyp->vyu.vyfnam);
      }

     cur_ifi = vyp->vyfnam_ind;
     /* know this will leave undef_mods with correct value */
     /* AIV 05/23/12 - my fix for this was bad using SJM fix which just */
     /* passes the index - no longer a need to save/restore */
     if (open_lbfil(cur_ifi, FALSE)) rd_vlibfil(undefp);
     if (__cur_passres == 0) continue;
     /* DBG remove -- */
     if (__cur_passres != 1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     goto resolve_nxt;
    }
   __pv_err(706,
    "lib rescan module %s unresolved after all libaries searched - skipping to next",
      undefp->msyp->synam);

resolve_nxt:;
   /* AIV 10/07/03 - if new head it is "next" else move one down list */ 
   if (sav_undefhd != __undefhd) undefp = __undefhd;
   else undefp = undefp->undefnxt;
  }
}

/*
 * rescan resolve one current unresolved references from a library dir
 * simpler than non rescan cases because at most one resolved 
 *
 * algorithm is:
 * 1) go through one current unresolved and find all files that match suffix
 *    and add to list
 * 2) then read and scan all files for the one unresolved now working on
 */
static void rescan_resolve_from_ydir(struct vylib_t *vyp,
 struct undef_t *undefp)
{
 int32 lbxi, dfi, got_err, cur_ifi;
 struct undef_t *tmpundefp, *undefp2, *tmphd, *tmptail;
 char fnam[IDLEN], stem[IDLEN];

 /* build stem that gives current path to directory */
 sprintf(stem, "%s/", vyp->vyu.vydirpth);
 /* case 1: no lbext - module name must exactly match file name */
 tmphd = tmptail = NULL;
 if (__last_lbx == -1)
  {
   if ((dfi = srch_yfiles(undefp->msyp->synam, vyp->yfiles, vyp->vyfnam_ind))
    != -1)
    {
     /* add to tmp list since parsing changes __undefhd list */ 
     tmpundefp = add_undef_el(undefp->msyp, &tmphd, &tmptail); 
     tmpundefp->dfi = dfi;
     vyp->yfiles[dfi].ylbxi = 0;
    }
  }
 else
  {
   /* case 2: must add lbext to module name and see if matches */
   /* build temporary list of all */
   for (lbxi = 0; lbxi <= __last_lbx; lbxi++)
    {
     sprintf(fnam, "%s%s", undefp->msyp->synam, __lbexts[lbxi]);
     if ((dfi = srch_yfiles(fnam, vyp->yfiles, vyp->vyfnam_ind)) == -1)
      continue;

     /* add to tmp list since parsing changes __undefhd list */ 
     tmpundefp = add_undef_el(undefp->msyp, &tmphd, &tmptail); 
     tmpundefp->dfi = dfi;
     vyp->yfiles[dfi].ylbxi = lbxi;
     /* when found, from precedence rules must stop looking */
     break;
    }
  }
 /* go through temp (will always be exactly one long) list reading file */
 /* DBG remove -- */
 if (tmphd != NULL && tmphd->undefnxt != NULL)
  __misc_terr(__FILE__, __LINE__);
 /* --- */
 for (undefp = tmphd; undefp != NULL; undefp = undefp->undefnxt)
  {
   dfi = undefp->dfi;
   if (vyp->yfiles[dfi].ydirfnam_ind == 0)
    {
     /* this dies if >64k */
     if (++__last_lbf >= __siz_in_fils) __grow_infils(__last_lbf);
     vyp->yfiles[dfi].ydirfnam_ind = __last_lbf;
     if (__last_lbx == -1) sprintf(fnam, "%s%s", stem, undefp->msyp->synam);
     else
      {
       lbxi = vyp->yfiles[dfi].ylbxi;
       sprintf(fnam, "%s%s%s", stem, undefp->msyp->synam, __lbexts[lbxi]);
      }
     __in_fils[__last_lbf] = __pv_stralloc(fnam);
    }
   /* notice each lib. file increments this by 1 */
   cur_ifi = vyp->yfiles[dfi].ydirfnam_ind;
   got_err = FALSE;

   if (open_lbfil(cur_ifi, FALSE)) rd_vlibfil(undefp); else got_err = TRUE;
   if (got_err) continue;
   /* if scanned because of a module and still unresolved after scanning */
   /* need warning - i.e. it is legal to not resolve in name matching */
   /* module but unrecommended */
   if (!undefp->msyp->sydecl)
    {
     __pv_warn(510,
      "module %s still unresolved after processing library directory file %s",
      undefp->msyp->synam, __in_fils[vyp->yfiles[dfi].ydirfnam_ind]);
    }
   else break;
  }
 /* final step is to free temp undef list */
 for (undefp = tmphd; undefp != NULL;) 
  {
   undefp2 = undefp->undefnxt;
   __my_free(undefp, sizeof(struct undef_t)); 
   undefp = undefp2;
  }
}

/*
 * PRELIMINARY FIXUP ROUTINES USUALLY FORMAT CHANGES 
 */

/*
 * routine to free all allocated tnode blks from unfrozen part of symtabs
 */
static void free_tnblks(void)
{
 struct tnblk_t *tnbp, *tnbp2;

 /* free all cell pin blks since ncomp form now gone */
 for (tnbp = __hdr_tnblks; tnbp != NULL;)
  {
   tnbp2 = tnbp->tnblknxt;
   __my_free(tnbp->tnblks, BIG_ALLOC_SIZE);
   __my_free(tnbp, sizeof(struct tnblk_t));
   tnbp = tnbp2;
  }
 __hdr_tnblks = NULL;
}

/*
 * change all module and task parameter lists to table from list
 *
 * also sets mprmnum and tprmnum so know size of tables
 * after completion, param nu2 field nnxt field no longed needed
 */
static void chg_params_to_tab(void)
{
 int32 pi, pnum;
 struct net_t *pnp, *pnp2;
 struct mod_t *mdp;
 struct net_t *nptab;
 struct task_t *tskp;
 struct spfy_t *spfyp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* first module params */
   pnum = cnt_prms(mdp->mprms);
   if (pnum != 0)
    {
     nptab = (struct net_t *) __my_malloc(pnum*sizeof(struct net_t));
     pi = 0;
     for (pnp = mdp->mprms; pnp != NULL; pnp = pnp->nu2.nnxt, pi++)
      {
       pnp2 = &(nptab[pi]);
       *pnp2 = *pnp;
       /* symbol points back to net - because copied to table change ptr */
       pnp2->nsym->el.enp = pnp2;
       /* ptr filds in pnp unique so will just get moved to new */
       /* except must nil out new table pnp2 nu2 because needed for saving */
       pnp2->nu2.wp = NULL;
      }
     mdp->mprmnum = pnum;
     free_param_listform(mdp->mprms);
     mdp->mprms = nptab;
    }

   /* first module LOCAL params */
   pnum = cnt_prms(mdp->mlocprms);
   if (pnum != 0)
    {
     nptab = (struct net_t *) __my_malloc(pnum*sizeof(struct net_t));
     pi = 0;
     for (pnp = mdp->mlocprms; pnp != NULL; pnp = pnp->nu2.nnxt, pi++)
      {
       pnp2 = &(nptab[pi]);
       *pnp2 = *pnp;
       pnp2->nsym->el.enp = pnp2;
       pnp2->nu2.wp = NULL;
      }
     mdp->mlocprmnum = pnum;
     free_param_listform(mdp->mlocprms);
     mdp->mlocprms = nptab;
    }

   /* next parameters in each task */
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     __chg_task_prms_to_tab(tskp);
    }
   /* finally specparams */
   if ((spfyp = mdp->mspfy) == NULL) goto nxt_mod;
   if ((pnum = cnt_prms(spfyp->msprms)) == 0) goto nxt_mod;

   nptab = (struct net_t *) __my_malloc(pnum*sizeof(struct net_t));
   pi = 0;
   for (pnp = spfyp->msprms; pnp != NULL; pnp = pnp->nu2.nnxt, pi++)
    {
     pnp2 = &(nptab[pi]);
     *pnp2 = *pnp;
     /* symbol points back to net - because copied to table change ptr */
     pnp2->nsym->el.enp = pnp2;
     /* ptr filds in pnp unique so will just get moved to new */
     /* except must nil out new table pnp2 nu2 because needed for saving */
     pnp2->nu2.wp = NULL;
    }
   spfyp->sprmnum = pnum;
   free_param_listform(spfyp->msprms);
   spfyp->msprms = nptab;
nxt_mod:
   __pop_wrkitstk();
  }
}

/*
 * routine to change task prms to tab form
 *
 * SJM 02-02-09 - now need routine so can chg const func params to tab
 * during post src read elaboration - needed so rest of normal fix up and
 * prep routines can be called
 */
extern void __chg_task_prms_to_tab(struct task_t *tskp)
{
 int32 pnum, pi;
 struct net_t *nptab;
 struct net_t *pnp, *pnp2;

 if ((pnum = cnt_prms(tskp->tsk_prms)) != 0) 
  {
   nptab = (struct net_t *) __my_malloc(pnum*sizeof(struct net_t));
   pi = 0;
   for (pnp = tskp->tsk_prms; pnp != NULL; pnp = pnp->nu2.nnxt, pi++)
    {
     pnp2 = &(nptab[pi]);
     *pnp2 = *pnp;
     /* symbol points back to net - because copied to table change ptr */
     pnp2->nsym->el.enp = pnp2;
     /* ptr filds in pnp uniue so will just get moved to new */
     /* except must nil out new table pnp2 nu2 because needed for saving */
     pnp2->nu2.wp = NULL;
    }
   tskp->tprmnum = pnum;
   free_param_listform(tskp->tsk_prms);
   tskp->tsk_prms = nptab;
  }
 /* do the task LOCAL parameters as well */
 if ((pnum = cnt_prms(tskp->tsk_locprms)) != 0) 
  {
   nptab = (struct net_t *) __my_malloc(pnum*sizeof(struct net_t));
   pi = 0;
   for (pnp = tskp->tsk_locprms; pnp != NULL; pnp = pnp->nu2.nnxt, pi++)
    {
     pnp2 = &(nptab[pi]);
     *pnp2 = *pnp;
     /* symbol points back to net - because copied to table change ptr */
     pnp2->nsym->el.enp = pnp2;
     /* ptr filds in pnp uniue so will just get moved to new */
     /* except must nil out new table pnp2 nu2 because needed for saving */
     pnp2->nu2.wp = NULL;
    }
   tskp->tlocprmnum = pnum;
   free_param_listform(tskp->tsk_locprms);
   tskp->tsk_locprms = nptab;
  }
}

/*
 * count params in list form
 */
static int32 cnt_prms(struct net_t *np)
{
 int32 pnum;
 struct net_t *parm_np;

 for (pnum = 0, parm_np = np; parm_np != NULL; parm_np = parm_np->nu2.nnxt)
  { pnum++; }
 return(pnum);
}

/*
 * free parameter list form
 *
 * no freeing of ncomp or expressions pointed to from inside since moved
 * to table form element
 */
static void free_param_listform(struct net_t *parm_np)
{
 struct net_t *pnp, *pnp2;

 for (pnp = parm_np; pnp != NULL;)
  {
   pnp2 = pnp->nu2.nnxt;
   __my_free(pnp, sizeof(struct net_t)); 
   pnp = pnp2;
  }
}

/*
 * ROUTINES TO SEPARATE CELLS INTO GATES AND INSTANCES
 */

/*
 * separate module gate and insts into separate lists
 * contas already separated by here 
 * relocate, free cell_t, and build array form port lists
 *
 * also checks for unnamed module instances and number cells with type range
 * could save some space by make insts and gates array of thing rather
 * than array of ptrs to things
 */
static void sep_mdgates(void)
{
 int32 modinum, modgnum, ii, gi, nbytes;
 struct cell_t *cp;
 struct mod_t *mdp;
 struct inst_t *iptab;
 struct gate_t *gptab;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);

   /* first allocate array of pointers to instances */
   modinum = count_minum_and_mgnum(&modgnum, mdp);
   if (modinum != 0)
    {
     nbytes = modinum*sizeof(struct inst_t);
     iptab = (struct inst_t *) __my_malloc(nbytes);
    }
   else iptab = NULL;
   if (modgnum != 0)
    {
     nbytes = modgnum*sizeof(struct gate_t);
     gptab = (struct gate_t *) __my_malloc(nbytes);
    }
   else gptab = NULL;

   ii = gi = -1;
   for (cp = mdp->mcells; cp != NULL; cp = cp->cnxt)
    {
     /* if not declared error above can still get here */
     /* but undeclared udp symbol with always be actually undcl mod */
     /* case 1: udp */ 
     if (cp->cmsym->sytyp == SYM_UDP)
      {
       cellrep_to_gate(cp, &(gptab[++gi]));
       if (cp->cx1 != NULL) bld_gate_giap(mdp, &(gptab[gi]), cp);
       continue;
      }
     /* case 2: built in primitive */ 
     if (cp->cmsym->sytyp == SYM_PRIM)
      {
       /* notice pullup becomes gate but can have only 1 (or more) ports */
       cellrep_to_gate(cp, &(gptab[++gi]));
       if (cp->cx1 != NULL) bld_gate_giap(mdp, &(gptab[gi]), cp);
       continue;
      }
     /* case 3: instance */
     if (!cp->c_named)
      {
       __gferr(731, cp->csym->syfnam_ind, cp->csym->sylin_cnt,
        "required module instance name missing (type is %s)",
        cp->cmsym->synam);
       cp->c_named = FALSE;
      }
     if (cp->cmsym != NULL && cp->cmsym->sydecl)
      {
       cellrep_to_inst(cp, &(iptab[++ii]));
       /* need to build the giap also for arrays of insts in gen blks */
       if (cp->cx1 != NULL) bld_inst_giap(mdp, &(iptab[ii]), cp);
      }
    }
   mdp->minum = modinum; 
   mdp->minsts = iptab; 
   mdp->mgnum = modgnum;
   mdp->mgates = gptab; 
   mdp->mcells = NULL;

   __pop_wrkitstk();
  }
}

/*
 * count number of instances in module
 * need array that is parallel to itree array for instances so must
 * count in order to allocate before building array
 */
static int32 count_minum_and_mgnum(int32 *gnum, struct mod_t *mdp)
{
 int32 inum;
 struct cell_t *cp;
 struct sy_t *syp;

 for (inum = *gnum = 0, cp = mdp->mcells; cp != NULL; cp = cp->cnxt)
  {
   syp = cp->cmsym;
   if (syp == NULL || !syp->sydecl) continue;

   if (syp->sytyp == SYM_UDP || syp->sytyp == SYM_PRIM) (*gnum)++;
   else inum++;
  }
 return(inum);
}

/*
 * convert a syntax analysis format general cell struct to a sim gate struct
 * cell pin list changed to expression list later
 */
static void cellrep_to_gate(struct cell_t *cp, struct gate_t *gp)
{
 int32 pi, pnum, nbytes, all_named;
 struct cell_pin_t *cpp;
 char s1[RECLEN];

 /* how is a port connect lost */
 if ((pnum = cnt_gateprts(cp)) == 0L)
  {
   __gferr(732, cp->csym->syfnam_ind, cp->csym->sylin_cnt,
    "%s %s illegal - at least one gate required", __to_sytyp(__xs,
    cp->cmsym->sytyp), cp->cmsym->synam);
  }
 /* must fit in 16 bits */
 if (pnum >= 0x3fffL)
  {
   __gferr(732, cp->csym->syfnam_ind, cp->csym->sylin_cnt,
    "%s %s has too many terminals (%d)", __to_sytyp(__xs, cp->cmsym->sytyp),
    cp->cmsym->synam, 0x3fffL);
   pnum = 0x3fffL;
  }

 /* notice symbol type is still SYM_I here */
 gp->gsym = cp->csym;
 gp->gsym->el.egp = gp;
 gp->gmsym = cp->cmsym;
 gp->g_giap = NULL;
 gp->gpnum = pnum;
 gp->g_hasst = (cp->c_hasst) ? TRUE : FALSE;
 gp->g_stval = cp->c_stval;
 gp->g_delrep = DT_CMPLST;
 gp->g_gone = FALSE;
 gp->g_pdst = FALSE;
 gp->gate_out_ofs = 0;
 gp->ctevp = NULL;
 if (gp->gmsym->sytyp == SYM_UDP)
  { gp->g_class = GC_UDP; gp->gsym->sytyp = SYM_PRIM; }
 else
  {
   gp->g_class = gp->gmsym->el.eprimp->gclass;
   gp->gsym->sytyp = SYM_PRIM;
  }

 gp->schd_tevs_ofs = 0;
 /* since before cells numbered non zero means unnamed */
 if (!cp->c_named) gp->g_unam = TRUE; else gp->g_unam = FALSE;

 gp->g_du.pdels = NULL;
 if (cp->c_nparms != NULL)
  {
   /* explicit parameter name form illegal for udps or gates */
   /* T returned if some named */
   if (pndparams_explicit(cp->c_nparms, &all_named))
    {
     if (all_named) strcpy(s1, "all"); else strcpy(s1, "some");
     __gferr(809, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
      "%s explicit .[parameter name]([expr]) # delay forms illegal for %s %s",
      s1, __to_sytyp(__xs, gp->gmsym->sytyp), gp->gmsym->synam);
     __free_namedparams(cp->c_nparms);
     gp->g_du.pdels = NULL;
    }
   else
    {
     gp->g_du.pdels = bld_gate_paramlst(cp->c_nparms);
     __free_namedparams(cp->c_nparms);
     cp->c_nparms = NULL;
    }
  }
 gp->gstate_ofs = 0;

 /* just move ptr since not shared */
 gp->gattrs = cp->cattrs;

 nbytes = pnum*sizeof(struct expr_t *);
 /* SJM 05/05/03 - from previous syntax errors where can't recover */ 
 /* this may be nil, but since errors still works */
 if (pnum > 0) gp->gpins = (struct expr_t **) __my_malloc(nbytes);
 else gp->gpins = NULL;
 gp->gchg_func = NULL;
 for (cpp = cp->cpins, pi = 0; cpp != NULL; pi++, cpp = cpp->cpnxt)
  {
   /* this should always be at least 'bx by here */
   if (cpp->pnam != NULL)
    {
     __gferr(733, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt,
      "explicit port connection illegal for %s %s",
      __to_sytyp(__xs, gp->gmsym->sytyp), gp->gmsym->synam);
     /* all freeing later */
    }
   /* this copies expr. (not freed) from cpins so when entire */
   /* cpin blocks freed later, no interlinking */ 
   if (pi < pnum) gp->gpins[pi] = cpp->cpxnd;
  }
}

/*
 * return T if param name list has any explicit named forms
 * if returns T, also sets flag if all are explicit form
 */
static int32 pndparams_explicit(struct namparam_t *npmphdr, int32 *all_named)
{
 int32 has_named, all2_named;
 struct namparam_t *npmp;

 *all_named = FALSE;
 has_named = FALSE;
 all2_named = TRUE;
 for (npmp = npmphdr; npmp != NULL; npmp = npmp->nprmnxt)
  {
   if (npmp->pnam != NULL) has_named = TRUE;
   else all2_named = FALSE;
  }
 if (has_named) *all_named = all2_named; 
 return(has_named);
}

/*
 * build a delay parameter list from a named parameter list for gates
 *
 * know all unnamed comma separated form list or will not be called
 * also know delay list with at least one element present or not called
 */
static struct paramlst_t *bld_gate_paramlst(struct namparam_t *npmphdr)
{
 int32 pi;
 struct namparam_t *npmp;
 struct paramlst_t *nplphdr, *nplp, *last_nplp;

 nplphdr = last_nplp = NULL;
 for (pi = 0, npmp = npmphdr; npmp != NULL; npmp = npmp->nprmnxt, pi++)
  {
   if (npmp->pxndp->optyp == OPEMPTY)
    {
     __pv_ferr(1190,
      "empty ,, form primitive pound delay value illegal (pos. %d)", pi + 1);
     continue;
    }
//SJM 01-18-09 - what does this do?
   nplp = __alloc_pval();
//SJM? - this is moving not copying - why? */
   nplp->plxndp = npmp->pxndp; 
   npmp->pxndp = NULL;
   if (last_nplp == NULL) nplphdr = nplp; else last_nplp->pmlnxt = nplp;
   nplp->pmlnxt = NULL;
   last_nplp = nplp;
  }
 if (nplphdr == NULL)
  {
   __pv_ferr(1095, "empty primitive #() delay expression illegal");
  }
 return(nplphdr);
}

/*
 * build gate/inst aux record for this gate which is an array of gates
 * only called if array form has range expr
 */
static void bld_gate_giap(struct mod_t *mdp, struct gate_t *gp,
 struct cell_t *cp)
{
 struct gia_aux_t *giap;

 gp->g_giap = (struct gia_aux_t *) __my_malloc(sizeof(struct gia_aux_t)); 
 giap = gp->g_giap;
 init_gia_aux_rec(giap);

 /* since this one unexpanded now, it is always the firs tand base syp here */
 giap->gia_is_base_first = TRUE;
 giap->gia_base_syp = gp->gsym;

 giap->giax1 = cp->cx1;  
 giap->giax2 = cp->cx2;
 __design_gi_arrays = TRUE;
 mdp->m_has_garrs = TRUE;
}

/*
 * initialize a gia aux record (same for arrays of gates and arrays of insts)
 */
static void init_gia_aux_rec(struct gia_aux_t *giap)
{
 giap->gia_xpnd = FALSE;
 giap->gia_is_base_first = FALSE;
 giap->gia_rng_has_pnd = FALSE;
 giap->giax1 = giap->giax2 = NULL;
 giap->gia1 = giap->gia2 = -1; 
 giap->gia_bi = -1;
 giap->giapins_ptr = NULL;
 giap->gia_base_syp = NULL;
}

/*
 * build array of insts and gates (inst here) aux rec
 */
static void bld_inst_giap(struct mod_t *mdp, struct inst_t *ip, struct cell_t *cp)
{
 struct gia_aux_t *giap;

 ip->i_giap = (struct gia_aux_t *) __my_malloc(sizeof(struct gia_aux_t)); 
 giap = ip->i_giap;
 init_gia_aux_rec(giap);

 /* since this one unexpanded now, it is always the firs tand base syp here */
 giap->gia_is_base_first = TRUE;
 giap->gia_base_syp = ip->isym;

 giap->giax1 = cp->cx1;  
 giap->giax2 = cp->cx2;

 __design_gi_arrays = TRUE;
 mdp->m_has_iarrs = TRUE;
}

/*
 * count the number of ports a gate has
 */
static int32 cnt_gateprts(struct cell_t *cp)
{
 int32 pnum;
 struct cell_pin_t *cpp;

 for (pnum = 0, cpp = cp->cpins; cpp != NULL; cpp = cpp->cpnxt) pnum++;
 return(pnum);
}

/*
 * convert a syntax analysis format general cell struct to a sim gate struct
 *
 * by here know module declared params converted to table from list
 * this also checked passed instance # params constant expressions
 */
static void cellrep_to_inst(struct cell_t *cp, struct inst_t *ip)
{
 /* if module not defined, nothing to do */
 if (cp->c_hasst)
  {
   __gferr(734, cp->csym->syfnam_ind, cp->csym->sylin_cnt,
    "module instance %s type %s strength specification illegal",
    cp->csym->synam, cp->cmsym->synam);
  }

 __init_inst(ip);

 ip->isym = cp->csym;
 ip->isym->el.eip = ip;
 ip->imsym = cp->cmsym;
 ip->i_giap = NULL;
 ip->pprm_explicit = FALSE;
 /* instance numbers assigned later because splitting can change */
 /* convert named param list to parallel table of pound param exprs */

 /* must set instance type flags before processing pound params */
 ip->i_iscell = (cp->c_iscell) ? TRUE : FALSE;
 ip->i_pnddefsplit = FALSE;

 /* this also checks pound paremeter's since know each params loc. */
 if (cp->c_nparms == NULL) ip->ipxprtab = NULL;
 else ip->ipxprtab = inst_nparms_to_xtab(cp->c_nparms, ip);

 ip->ip_explicit = (cp->cp_explicit) ? TRUE : FALSE;

 /* indicate that instance has pound params (only 0 or 1 have meaning) */
 if (ip->ipxprtab != NULL) __num_inst_pndparams++;

 /* just move ptr since not shared */
 ip->iattrs = cp->cattrs;
 /* if has instance attributes combine mod attributes into inst attrs */
 if (ip->iattrs != NULL && ip->imsym->el.emdp->mattrs != NULL)
  add_mod_attrs_toinst(ip);

 /* for now must leave inst-pin list form - freed as part of all cppblks */
 ip->ipins = (struct expr_t **) cp->cpins;
}

/*
 * routine to initialize inst_t record
 *
 * SJM 10/16/00 - needed to avoid errors and for top_ip
 */
extern void __init_inst(struct inst_t *ip)
{
 ip->ip_explicit = FALSE;
 ip->pprm_explicit = FALSE;
 ip->i_iscell = FALSE;
 ip->i_pnddefsplit = FALSE;
 ip->isym = NULL;
 ip->imsym = NULL;
 ip->i_giap = NULL;
 ip->ipxprtab = NULL;
 ip->iattrs = NULL;
 ip->ipins = NULL;
 ip->pb_ipins_tab = NULL;
}

/*
 * merge attributes from mod into inst
 *
 * only called if both inst and mod have at least one attr
 * if same attr name in both use inst value
 * if name only in mod add to inst list so can use list to make iterator  
 */
static void add_mod_attrs_toinst(struct inst_t *ip)
{
 struct attr_t *iattrp, *mattrp, *iattr_end;
 struct attr_t *new_iattrp, *new_iattrhd, *new_iattrend;
 struct mod_t *mdp;

 new_iattrhd = new_iattrend = NULL;
 iattr_end = NULL;
 for (iattrp = ip->iattrs; iattrp != NULL; iattrp = iattrp->attrnxt) 
  { iattr_end = iattrp; }
 mdp = ip->imsym->el.emdp;

 for (mattrp = mdp->mattrs; mattrp != NULL; mattrp = mattrp->attrnxt) 
  {
   for (iattrp = ip->iattrs; iattrp != NULL; iattrp = iattrp->attrnxt)
    {
     /* attribute attached to both inst and mod - use inst value */
     if (strcmp(mattrp->attrnam, iattrp->attrnam) == 0) goto nxt_mod_attr;
    }
   /* attr attached to mod but not inst and inst has at least one attr */ 
   /* add mod attr to inst */
   new_iattrp = (struct attr_t *) __my_malloc(sizeof(struct attr_t));
   *new_iattrp = *mattrp;
   new_iattrp->attrnam = __pv_stralloc(mattrp->attrnam);
   new_iattrp->attr_xp = __copy_expr(mattrp->attr_xp);
   new_iattrp->attrnxt = NULL;
   if (new_iattrhd == NULL) new_iattrhd = new_iattrp;
   else new_iattrend->attrnxt = new_iattrp;
   new_iattrend = new_iattrp;
nxt_mod_attr:;
  }
 /* possible for all to be duplicated so none to add */
 if (iattr_end != NULL && new_iattrhd != NULL)
  iattr_end->attrnxt = new_iattrhd;
}

/*
 * build expr table from named param list
 *
 * know instance has pound param(s) or routine not called 
 * list needed because must be able to index pound parameters when building
 * arrays of instance 
 *
 * this assumes module pound params converted to table from list
 * happens just before cell rep to inst for each module
 *
 * when routine done no longer need nqc_u union (i.e. done with npi)
 */
static struct expr_t **inst_nparms_to_xtab(struct namparam_t *npmphdr,
 struct inst_t *ip)
{
 int32 all_named;
 struct expr_t **npxtab;

 /* new explicitly named form */
 if (pndparams_explicit(npmphdr, &all_named))
  {
   if (!all_named)
    {
     __gferr(829, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
      "mixed implicit and explicit # parameters illegal for instance %s",
      ip->isym->synam);
     __free_namedparams(npmphdr);
     return(NULL);
    }
   npxtab = match_namparam_exprtab(npmphdr, ip);
   if (npxtab != NULL) ip->pprm_explicit = TRUE;
  }
 else
  {
   /* old unnamed list - but ,, allowed and becomes nil (no param) */
   npxtab = match_implprm_exprtab(npmphdr, ip);
  }
 __free_namedparams(npmphdr);
 return(npxtab);
} 

/*
 * routine to build inst param expr table from named param list
 *
 * by here module definition pound parameters converted to table
 * param nu2 field union member npi used here as temp, can reuse after here 
 */
static struct expr_t **match_namparam_exprtab(struct namparam_t *npmphdr,
 struct inst_t *ip)
{
 int32 pi;
 struct namparam_t *npmp;
 struct mod_t *mdp;
 struct net_t *np, **prmtab;
 struct expr_t **npxtab;
 struct sy_t *syp;
 char s1[2*IDLEN];

 sprintf(s1, "instance %s", ip->isym->synam); 

 mdp = ip->imsym->el.emdp;
 if (mdp->mprmnum == 0)
  {
   __gferr(865, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
    "%s has explicit pound parameters but none declared in module %s",
    s1, mdp->msym->synam);
   return(NULL);
  }

 /* build sorted by name param declaration list */
 prmtab = (struct net_t **) __my_malloc(mdp->mprmnum*sizeof(struct net_t *));
 for (pi = 0; pi < mdp->mprmnum; pi++)
  {
   prmtab[pi] = &(mdp->mprms[pi]);
   /* need original ndx of param (net) in table so can set after sorting */
   prmtab[pi]->nu2.npi = pi;
  }
 qsort((char *) prmtab, (word32) mdp->mprmnum, sizeof(struct net_t *),
  prmtab_cmp); 
 /* allocate inst named param expr ptr table and set to unuused (ni) */
 npxtab = (struct expr_t **) __my_malloc(mdp->mprmnum*sizeof(struct expr_t *));
 for (pi = 0; pi < mdp->mprmnum; pi++) npxtab[pi] = NULL;

 for (npmp = npmphdr, pi = 0; npmp != NULL; npmp = npmp->nprmnxt, pi++)
  {
   /* DBG remove --- */
   if (npmp->pnam == NULL) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   
   syp = __zget_sym(npmp->pnam, mdp->msymtab->stsyms, mdp->msymtab->numsyms);
   if (syp == NULL || syp->sytyp != SYM_N)
    {
undcl_param:
     __gferr(865, npmp->prmfnam_ind, npmp->prmlin_cnt,
      "%s explicit pound parameter %s (pos. %d) not a declared parameter",
      s1, npmp->pnam, pi);
     /* if no declared parameters, always continue here */
     continue; 
    }
   np = syp->el.enp;
   if (!np->n_isaparam || np->nu.ct->p_specparam) goto undcl_param;

   /* AIV 09/27/06 - net cannot be a local param value cannot be overridden */
   if (np->nu.ct->p_locparam)
    {
     __gferr(3431, npmp->prmfnam_ind, npmp->prmlin_cnt,
      "%s explicit pound parameter %s (pos. %d) cannot be a localparam (declared pos. %d)",
      s1, npmp->pnam, pi, np->nu2.npi);
     continue;
    }

   if (npxtab[np->nu2.npi] != NULL)
    {
     __gferr(935, npmp->prmfnam_ind, npmp->prmlin_cnt,
      "%s explicit pound parameter %s (pos. %d) repeated (declared pos. %d)",
      s1, npmp->pnam, pi, np->nu2.npi);
     continue;
    }
   /* empty .[pnam]() form legal and becomes nil with warning */
   if (npmp->pxndp->optyp == OPEMPTY)
    {
#ifndef __CVC_RT__
     __gfwarn(545, npmp->prmfnam_ind, npmp->prmlin_cnt,
      "%s explicit pound parameter %s expression empty (pos. %d) - no pound override",
      s1, npmp->pnam, pi);
#endif
     continue;
    }
   /* on error (returns F), leave location in npx tab nil */
   if (chk1_pndparam(s1, ip, npmp, pi, np->nu2.npi))
    {
     npxtab[np->nu2.npi] = npmp->pxndp;
     /* this needed to prevent freeing when namparams freed */
     npmp->pxndp = NULL;
    }
  }
 /* if all are errors - i.e. table or none decled still empty return nil */
 for (pi = 0; pi < mdp->mprmnum; pi++)
  { if (npxtab[pi] != NULL) goto some_good; }
 return(NULL);

some_good:
 return(npxtab);
}

/*
 * compare for sort of table of ptrs order module parameter table
 */
static int32 prmtab_cmp(const void *np1, const void *np2)
{
 return(strcmp((*((struct net_t **) np1))->nsym->synam,
 ((*(struct net_t **) np2))->nsym->synam));
}

/*
 * check one pound param to make sure parameter constant expression
 *
 * if error, return -1 so caller does not add to ipx table
 * folding done later
 */
static int32 chk1_pndparam(char *s1, struct inst_t *ip, struct namparam_t *npmp,
 int32 pi, int32 npi)
{
 int32 rv, sav_sfnam_ind, sav_slin_cnt;
 struct mod_t *imdp;
 struct net_t *parm_np;

 /* SJM 10/01/99 - improve error location for param checking */
 /* chk param expr needs sim locations set - set temporary guess here */
 sav_sfnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt;
 __sfnam_ind = npmp->prmfnam_ind;
 __slin_cnt = npmp->prmlin_cnt;
 
 imdp = ip->imsym->el.emdp;
 parm_np = &(imdp->mprms[npi]);

 /* notice must check #(parms) rhs here since can be any parameter*/
 /* even one defined later in source according to LRM */
 if (!__chk_paramexpr(npmp->pxndp, 0))
  {
   __sgferr(753,
    "%s pound parameter %s (pos. %d) expression %s only parameters and constants - is parameter from other module?",
    s1, parm_np->nsym->synam, pi, __msgexpr_tostr(__xs, npmp->pxndp));
   rv = FALSE;
  }
 else rv = TRUE;

 __sfnam_ind = sav_sfnam_ind;
 __slin_cnt = sav_slin_cnt;
 return(rv);
}

/*
 * routine to build inst param expr table from implicit unnamed # param list
 *
 * no error possible here
 */
static struct expr_t **match_implprm_exprtab(struct namparam_t *npmphdr,
 struct inst_t *ip)
{
 int32 pi;
 struct namparam_t *npmp;
 struct mod_t *mdp;
 struct expr_t **npxtab;
 char s1[2*IDLEN];

 /* can never see connector parameters here */
 sprintf(s1, "instance %s", ip->isym->synam); 

 mdp = ip->imsym->el.emdp;
 /* FIXME - SJM 06/01/99 - if syntax error and no mod params */
 /* was wrongly allocating 0 size array here */
 /* notice 1 bit enough since once malloced exits pound param loop */
 if (mdp->mprmnum == 0)
  {
   npxtab = (struct expr_t **) __my_malloc(1*sizeof(struct expr_t *));
   npxtab[0] = NULL;
  }
 else
  {
   /* allocate inst named param expr ptr table and set to unuused (ni) */
   npxtab = (struct expr_t **)
    __my_malloc(mdp->mprmnum*sizeof(struct expr_t *));
  }
 for (pi = 0; pi < mdp->mprmnum; pi++) npxtab[pi] = NULL;

 /* unnamed so must match by position */
 for (npmp = npmphdr, pi = 0; npmp != NULL; npmp = npmp->nprmnxt, pi++)
  {
   /* too few ok, but too many is error */
   if (pi >= mdp->mprmnum) 
    {
     /* need to count all in list */
     for (; npmp != NULL; npmp = npmp->nprmnxt) pi++;

     __gferr(752, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
      "%s # parameter list too long (%d) - only %d parameters declared",
      s1, pi, mdp->mprmnum); 
     break;
    }
   /* because now translating like ports allowing ,, that become nil */
   if (npmp->pxndp->optyp == OPEMPTY) continue;
   if (chk1_pndparam(s1, ip, npmp, pi, pi))
    {
     npxtab[pi] = npmp->pxndp;
     npmp->pxndp = NULL;
    }
  }
 /* if list short, tail will be correctly nil but need inform */
 if (pi < mdp->mprmnum)
  {
   __gfinform(408, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
    "%s only first %d of %d pound parameters set", s1, pi + 1, mdp->mprmnum);
  }
 return(npxtab); 
}

/*
 * ROUTINES TO CONNECT PORTS
 */

/*
 * check module ports and make instance connections
 * handles implicit and explicit form port matching
 */
static void fix_port_conns(void)
{
 struct mod_t *mdp;

 /* set implicit module port form names and I/O directions */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   setchk_modports();
   __pop_wrkitstk();
  }

 /* connect module ports and change to instance port expr. list */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   __push_wrkitstk(mdp, 0);
   conn_mod_insts();
   __pop_wrkitstk();
  }

 /* finally can free any sorted work mod port pointer arrays */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->smpins == NULL) continue;
   __my_free(mdp->smpins, mdp->mpnum*sizeof(struct srtmp_t));
   mdp->smpins = NULL;
  }
}

/*
 * set and check module header port connections
 * needed because .[port]([expr]), legal, unnamed ports legal, and
 * repeated nets legal
 *
 * since wire width not known yet, structural checking here only, widths
 * set and checked later
 *
 * SJM 03-02-09 - routine deals with mods does not effect gen instance
 * connections
 */
static void setchk_modports(void)
{
 int32 pi, pnum, port_gd;
 struct mod_pin_t *mpp;

 if ((pnum = __inst_mod->mpnum) == 0) return;
 for (pi = 0; pi < pnum; pi++)
  {
   mpp = &(__inst_mod->mpins[pi]);
   __pr_iodir = IO_UNKN;
   port_gd = chk_prtref(mpp->mpref, mpp, TRUE);
   mpp->mptyp = __pr_iodir;

   /* notice empty and concatenate port lists remain unnamed */
   if (port_gd)
    {
     /* SJM 08/23/00 - now OPEMPTY ports also legal and unnamed */
     if (mpp->mpsnam == NULL && mpp->mpref->optyp != LCB
      && mpp->mpref->optyp != OPEMPTY)
      {
       if (mpp->mpref->optyp == ID) mpp->mpsnam = mpp->mpref->lu.sy->synam;
       else mpp->mpsnam = mpp->mpref->lu.x->lu.sy->synam;
      }
    }
   else
    {
     __free_xtree(mpp->mpref);
     __bld_unc_expr();
     mpp->mpref = __root_ndp;
    }
  }
}

/*
 * check a module port def. expression to make sure it is a prtref
 * return F on error else T
 * prtref is lhs value or concatenate (including nested) of port refs.
 * also checks and sets I/O direction
 * this is called before wire and port ranges known
 */
static int32 chk_prtref(struct expr_t *ndp, struct mod_pin_t *mpp,
 int32 is_top)
{
 struct net_t *np;
 struct expr_t *idndp;
 char s1[RECLEN], s2[RECLEN];

 switch (ndp->optyp) {
  case GLBREF:
bad_prtglb:
   __gferr(736, mpp->mpfnam_ind, mpp->mplin_cnt,
    "module header list of ports hierarchical path reference %s illegal",
     ndp->ru.grp->gnam);
   return(FALSE);
  case ID:
   /* when ID appears in mod. def. port header, converted to undecl net */ 
   np = ndp->lu.sy->el.enp;
   idndp = ndp;
chk_dir:
   if (!idndp->lu.sy->sydecl)
    {
     __gferr(737, mpp->mpfnam_ind, mpp->mplin_cnt,
      "I/O port %s required direction declaration missing", np->nsym->synam);
     return(FALSE);
    }
   if (np->iotyp == NON_IO)
    {
     __gferr(738, mpp->mpfnam_ind, mpp->mplin_cnt,
      "module header list of ports %s %s must be I/O port",
       __to_wtnam(s1, np), np->nsym->synam);
     return(FALSE);
    }
   if (__pr_iodir == IO_UNKN) __pr_iodir = np->iotyp;
   else if (__pr_iodir != np->iotyp)
    {
     __gferr(739, mpp->mpfnam_ind, mpp->mplin_cnt,
     "module header list of ports %s wire %s has conflicting %s port type",
      __to_ptnam(s1, np->iotyp), np->nsym->synam, __to_ptnam(s2, __pr_iodir));
     return(FALSE);
    }
   /* count times wire repeated in port list */
   if (np->nu.ct->num_prtconns != 2 && is_top) np->nu.ct->num_prtconns += 1;

   /* notice in and inout ports must be wires but out can be reg */
   if (!chk_prtntyp(mpp, np)) return(FALSE);
   break;
  case PARTSEL:
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   /* since check module port syntax before splitting, mark params that */
   /* can effect expr. width here to later possibly cause split not IS form */
   __in_xpr_markparam(ndp->ru.x->lu.x);
   __in_xpr_markparam(ndp->ru.x->ru.x);
   /* FALLTHRU */
  case LSB:
   if (ndp->lu.x->optyp == GLBREF) goto bad_prtglb;
   idndp = ndp->lu.x;
   np = idndp->lu.sy->el.enp;
   /* inout port expr. may need to go in tran channel so can't be IS form */
   if (np->iotyp == IO_BID) __in_xpr_markparam(ndp->ru.x);
   goto chk_dir;
  case LCB:
   if (!is_top)
    {
     __gferr(740, mpp->mpfnam_ind, mpp->mplin_cnt,
      "module header list of ports nested concatenate illegal");
     return(FALSE);
    }
   {
    struct expr_t *ndp2;

    /* ndp2 left can still be nested concatenate by here */
    /* but can find rep. number */
    for (ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
     {
      /* check I/O direction from subcomponents one down */
      /* also check for incorrect reg one down */
      if (!chk_prtref(ndp2->lu.x, mpp, FALSE)) return(FALSE);
     }
   }
   break;
  case CATREP:
   __gferr(741, mpp->mpfnam_ind, mpp->mplin_cnt,
    "module header list of ports port ref. concatenate repeat form illegal");
   return(FALSE);
  case OPEMPTY:
   break;
  default:
   __gferr(742, mpp->mpfnam_ind, mpp->mplin_cnt,
    "%s illegal module header list of ports port reference",
    __msgexpr_tostr(__xs, ndp));
   return(FALSE);
 }
 return(TRUE);
}

/*
 * check a port wire to make sure net type legal
 */
static int32 chk_prtntyp(struct mod_pin_t *mpp, struct net_t *np)
{
 char s1[RECLEN], s2[RECLEN];

 if (np->iotyp == IO_OUT)
  {
   if (np->ntyp == N_REAL)
    {
     __gferr(743, mpp->mpfnam_ind, mpp->mplin_cnt,
      "%s port %s type real illegal", __to_ptnam(__xs, np->iotyp),
      np->nsym->synam);
     return(FALSE);
    }
  }
 else
  {
   if (np->ntyp >= NONWIRE_ST)
    {
     __gferr(744, mpp->mpfnam_ind, mpp->mplin_cnt,
      "%s port %s of net type %s illegal - must be a wire",
       __to_ptnam(s1, np->iotyp), np->nsym->synam, __to_wtnam(s2, np));
     return(FALSE);
    }
  }
 return(TRUE);
}

/*
 * check/connect cell pins to defined down one module
 * no processing of gates here
 */
static void conn_mod_insts(void)
{
 int32 ii;
 int32 nbytes;
 struct inst_t *ip;
 struct srcloc_t *srcloc;

 if (__inst_mod->minum == 0) return;
 
 /* allocate the || to minsts per contained inst pin src loc table */  
 nbytes = __inst_mod->minum*sizeof(struct srcloc_t *);
 __inst_mod->iploctab = (struct srcloc_t **) __my_malloc(nbytes);

 for (ii = 0; ii < __inst_mod->minum; ii++)
  {
   ip = &(__inst_mod->minsts[ii]);
   srcloc = conn1_inst_in_mod(ip);

   /* must connect to current mod since need port locs for expr check */
   /* since parallel to insts, for insts. with no cell pin list will be nil */ 
   __inst_mod->iploctab[ii] = srcloc;
  }
}

/*
 * routine to copy one instance in a module
 *
 * SJM 02-03-09 - new routine so can connect pins for gens too
 */  
static struct srcloc_t *conn1_inst_in_mod(struct inst_t *ip)
{
 int32 nbytes;
 struct cell_pin_t *cpp;
 struct sy_t *syp;
 struct mod_t *imdp;
 struct expr_t **xphdr;
 struct srcloc_t *srcloc;

 srcloc = NULL;
 syp = ip->imsym;
 /* module instance declaration info lost */
 if (!syp->sydecl)
  __misc_gfterr(__FILE__, __LINE__, ip->isym->syfnam_ind,
   ip->isym->sylin_cnt);
 imdp = ip->imsym->el.emdp;

 /* instance must contain at least () which will cause 1 unc. pin */
 cpp = (struct cell_pin_t *) ip->ipins;
 /* DBG remove --- */
 /* know there will be at least one pin if no error */
 if (cpp == NULL && imdp->mpnum != 0)
  {
   if (__pv_err_cnt == 0) __misc_terr(__FILE__, __LINE__);
  }
 /* --- */

 /* allocate new expression table */
 /* special case of module with no ports instantiated as () */
 /* it will have one unc. port - legal for 1 port case */
 /* but since no module ports this special port must be thrown away */
 if (imdp->mpnum == 0)
  {
   ip->ipins = NULL;
   srcloc = NULL;
   /* only set to NULL if has 1 unc. port - else will be null */
   /* LOOKATME - not freeing case of one unc. port */  
   if (cpp == NULL || (cpp->cpnxt == NULL && cpp->cpxnd->optyp == OPEMPTY))
    {
     return(srcloc);
    }

   __gferr(746, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
    "instance %s module type %s has ports but module does not",
     ip->isym->synam, imdp->msym->synam);
   return(srcloc);
  }
 nbytes = imdp->mpnum*sizeof(struct expr_t *);
 xphdr = (struct expr_t **) __my_malloc(nbytes);
 nbytes = imdp->mpnum*sizeof(struct srcloc_t);
 srcloc = (struct srcloc_t *) __my_malloc(nbytes);

 /* allocate cell-pin expression table */
 /* all implicit connection case else all explicit connection case */
 if (cpp->pnam == NULL) conn_impl_mports(ip, cpp, imdp, xphdr, srcloc);
 else conn_expl_mports(ip, cpp, imdp, xphdr, srcloc);
 ip->ipins = xphdr;
 return(srcloc);
}

/*
 * connect implicit instance ports
 * mdp is instance module type
 * various checking goes here
 * ,, form here already made appropriate unc. 
 * 
 * know module port num at least one or not called 
 */
static void conn_impl_mports(struct inst_t *ip, struct cell_pin_t *cpp,
 struct mod_t *mdp, struct expr_t **xphdr, struct srcloc_t *srclocp)
{
 int32 pi, pnum, num_unc_ports;
 struct cell_pin_t *last_cpp;

 ip->ip_explicit = FALSE;
 pnum = mdp->mpnum;
 num_unc_ports = 0;
 for (pi = 0; pi < pnum;)
  {
   if (cpp->pnam != NULL)
    {
     __gferr(747, cpp->cpfnam_ind, cpp->cplin_cnt,
     "%s(%s) explicit port %s (pos. %d) mixed in implicit connection list",
      ip->isym->synam, ip->imsym->synam, cpp->pnam, pi + 1);
    }
   /* SJM 11/13/00 - now also emit warning if ,, unc. form in implicit list */
   if (cpp->cpxnd->optyp == OPEMPTY) num_unc_ports++;
   xphdr[pi] = cpp->cpxnd;
   /* here implicit means port in order def. i and inst i same */ 
   srclocp[pi].sl_fnam_ind = cpp->cpfnam_ind;
   srclocp[pi].sl_lin_cnt = cpp->cplin_cnt;
   last_cpp = cpp;
   if ((cpp = cpp->cpnxt) == NULL && pi < pnum - 1) goto too_few;
   pi++;
  }
 if (cpp != NULL)
  {
   __gferr(748, cpp->cpfnam_ind, cpp->cplin_cnt,
    "%s(%s) implicit connection list more ports than type with %d",
    ip->isym->synam, ip->imsym->synam, pnum);
  }
#ifndef __CVC_RT__
 if (num_unc_ports > 0)
  {
   __gfwarn(531, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
    "%s(%s) implicit connection list fewer ports %d connected than type's %d",
    ip->isym->synam, ip->imsym->synam, pnum - num_unc_ports, pnum);
  }
#endif
 return;

too_few:
 pi++;
 /* warn because ,,s should be included */
#ifndef __CVC_RT__
  {
   __gfwarn(531, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
    "%s(%s) implicit connection list fewer ports %d in list than type's %d",
    ip->isym->synam, ip->imsym->synam, pi, pnum);
  }
#endif
 for (; pi < pnum; pi++)
  {
   __bld_unc_expr(); 
   xphdr[pi] = __root_ndp;
   /* for missing use last or if no conn use isym loc. */
   if (last_cpp == NULL)
    {
     srclocp[pi].sl_fnam_ind = ip->isym->syfnam_ind;
     srclocp[pi].sl_lin_cnt = ip->isym->sylin_cnt;
    }
   else
    {
     srclocp[pi].sl_fnam_ind = last_cpp->cpfnam_ind;
     srclocp[pi].sl_lin_cnt = last_cpp->cplin_cnt;
    }
  }
}

/*
 * connect explicit instance connection form ports
 *
 * builds ipins table (of prts to exprs) size is always num mod ports
 * even if some unconnected (will be unc. expr)
 *
 * know module port num at least one or not called 
 */
static void conn_expl_mports(struct inst_t *ip, struct cell_pin_t *cpp,
 struct mod_t *imdp, struct expr_t **xphdr, struct srcloc_t *srclocp)
{
 int32 pi, mpi, cpnum, pnum, cv, num_unc_ports;
 struct cell_pin_t **srtcptab;
 struct srtmp_t *srtmptab;
 struct cell_pin_t *scpp;
 struct srtmp_t *smpp;

 ip->ip_explicit = TRUE;
 /* if module has unnamed ports, cannot continue */
 if (!chk_mdports_named(ip, imdp, xphdr)) return;

 /* if no sorted port list for this module type, build one */
 if (imdp->smpins == NULL) bld_srted_mdpins(imdp);
 srtmptab = imdp->smpins;

 /* build the sorted cell pin table for instance */
 pnum = imdp->mpnum; 
 for (scpp = cpp, cpnum = 0; scpp != NULL; scpp = scpp->cpnxt) cpnum++;
 srtcptab = (struct cell_pin_t **)
  __my_malloc(cpnum*sizeof(struct cell_pin_t *));
 if (!bld_srted_ipins(ip, cpp, cpnum, srtcptab)) goto free_pin_tab;

 pi = 0; scpp = srtcptab[0];
 mpi = 0; smpp = &(srtmptab[0]);
 /* know both lists sorted so move through */
 /* if past end of either done - if no match, left as nil, made unc. */ 
 for (; pi < cpnum && mpi < pnum;)
  {
   /* scpp is cell (inst.) port and smpp is module port */
   if ((cv = strcmp(scpp->pnam, smpp->smp->mpsnam)) == 0)
    {
     xphdr[smpp->mppos] = scpp->cpxnd;
     /* index here is type def. order, def. i line no. if for i conn. */ 
     srclocp[smpp->mppos].sl_fnam_ind = scpp->cpfnam_ind; 
     srclocp[smpp->mppos].sl_lin_cnt = scpp->cplin_cnt;
     /* if at end of instance ports, done */
     pi++; if (pi < cpnum) scpp = srtcptab[pi];
     mpi++; if (mpi < pnum) smpp = &(srtmptab[mpi]);
     continue;
    }
   /* module instance port extra or repeated - fits between type ports */
   /* cell port alphabetically less than module port - is non mod port */
   /* becasue both sorted - if repeated, moved to next mod port so same */
   /* cell port now less than */
   if (cv < 0)
    {
     if (pi > 0 && strcmp(srtcptab[pi - 1]->pnam, scpp->pnam) == 0) 
      {
       __gferr(745, scpp->cpfnam_ind, scpp->cplin_cnt,
        "%s(%s) explicit connection port %s repeated",
        ip->isym->synam, imdp->msym->synam, scpp->pnam);
      } 
     else __gferr(749, scpp->cpfnam_ind, scpp->cplin_cnt,
      "%s(%s) explicit connection port %s is not a module port",
      ip->isym->synam, imdp->msym->synam, scpp->pnam);
     pi++;
     if (pi < cpnum) scpp = srtcptab[pi];
     continue;
    }
   /* cell port alphabetically greater than module port */
   /* module type port is extra (unc.) - fits between module inst ports */
   mpi++; if (mpi < pnum) smpp = &(srtmptab[mpi]);
  }
 /* if more cell ports, know are non port - emit error */
 for (; pi < cpnum; pi++)
  {
   scpp = srtcptab[pi];
   __gferr(749, scpp->cpfnam_ind, scpp->cplin_cnt,
    "%s(%s) explicit connection port %s is not a module port",
    ip->isym->synam, imdp->msym->synam, scpp->pnam);
  }  
free_pin_tab:
 __my_free(srtcptab, cpnum*sizeof(struct cell_pin_t *));
 srtcptab = NULL;

 /* for all unc. (NULL) expressions convert to real unconnected */
 num_unc_ports = 0;
 for (pi = 0; pi < pnum; pi++)
  {
   if (xphdr[pi] == NULL)
    {
     __bld_unc_expr();
     xphdr[pi] = __root_ndp;
     /* use instance location for these */
     srclocp[pi].sl_fnam_ind = ip->isym->syfnam_ind; 
     srclocp[pi].sl_lin_cnt = ip->isym->sylin_cnt;
     num_unc_ports++;
    }
  }
#ifndef __CVC_RT__
 if (num_unc_ports > 0)
  {
   __gfwarn(531, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
    "%s(%s) explicit connection list fewer ports %d connected than type's %d",
    ip->isym->synam, ip->imsym->synam, pnum - num_unc_ports, pnum);
  }
#endif
}

/*
 * check to make sure for explicit instance form all module ports named 
 * also initialized instance port expression table to NULL
 * only called for explicit conn. instances
 */
static int32 chk_mdports_named(struct inst_t *ip,
 struct mod_t *mdp, struct expr_t **xphdr)
{
 int32 pi, pnum, __err_seen;
 struct mod_pin_t *mpp;

 if ((pnum = mdp->mpnum) == 0) return(FALSE);

 __err_seen = FALSE;
 for (pi = 0; pi < pnum; pi++)
  {
   mpp = &(mdp->mpins[pi]);
   if (mpp->mpsnam == NULL)
    {
     __gferr(750, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
      "%s(%s) explicit connection form illegal - port %d unnamed",
     ip->isym->synam, mdp->msym->synam, pi + 1);
     __err_seen = TRUE;
    }
   xphdr[pi] = NULL;
  }
 return(!__err_seen);
}

/*
 * build sorted table of module ports - once built saved so not rebuilt
 * each time - freed when port connection phase completed
 * only called when know all module ports named and at least 1 port
 */
static void bld_srted_mdpins(struct mod_t *mdp)
{
 int32 pi, pnum;
 struct srtmp_t *smpp;
 struct mod_pin_t *mpp;
 struct srtmp_t *smptab;  

 pnum = mdp->mpnum;
 smptab = (struct srtmp_t *) __my_malloc(pnum*sizeof(struct srtmp_t)); 
 mdp->smpins = smptab;
 mpp = &(mdp->mpins[0]);
 for (pi = 0, smpp = &(smptab[0]); pi < pnum; pi++, smpp++, mpp++)
  {
   smpp->smp = mpp;
   smpp->mppos = pi;
  }
 qsort((char *) smptab, (word32) pnum, sizeof(struct srtmp_t), smp_cmp); 
}

/*
 * module port name comparison routine
 */
static int32 smp_cmp(const void *srp1, const void *srp2)
{
 return(strcmp(((struct srtmp_t *) srp1)->smp->mpsnam,
 ((struct srtmp_t *) srp2)->smp->mpsnam));
}

/*
 * build sorted table of instance ports
 * built for each explicitly connected instance
 * free when instance connections made
 */
static int32 bld_srted_ipins(struct inst_t *ip, struct cell_pin_t *cpp,
 int32 pnum, struct cell_pin_t **scptab)
{
 int32 pi; 
 struct cell_pin_t *cpp2;
 char *chp;

 for (pi = 0; pi < pnum; pi++, cpp = cpp->cpnxt)
  {
   if (cpp->pnam == NULL)
    {
     __gferr(751, ip->isym->syfnam_ind, ip->isym->sylin_cnt,
      "%s(%s) explicit connection list but port connection %d is implicit",
      ip->isym->synam, ip->imsym->synam, pi + 1);
     return(FALSE);
    }
   scptab[pi] = cpp;
  }
 qsort((char *) scptab, (word32) pnum, sizeof(struct cell_pin_t *), cpn_cmp); 

 /* must check for duplicate of same name since illegal */
 /* LOOKATME - think none impossible but doing nothing is right if happens */ 
 if (pnum <= 0) return(TRUE);

 chp = scptab[0]->pnam; 
 for (pi = 1; pi < pnum; pi++)
  {
   cpp2 = scptab[pi];
   if (strcmp(chp, cpp2->pnam) == 0)
    {
     __gferr(1038, cpp2->cpfnam_ind, cpp2->cplin_cnt,
      "%s(%s) explicit connection list named port %s repeated",
      ip->isym->synam, ip->imsym->synam, chp);
    }
   else chp = scptab[pi]->pnam;
  }
 return(TRUE);
}

/*
 * module port name comparison routine
 */
static int32 cpn_cmp(const void *cpp1, const void *cpp2)
{
 return(strcmp((*((struct cell_pin_t **) cpp1))->pnam,
  (*(struct cell_pin_t **) cpp2)->pnam));
}

/*
 * routine to free all allocated ncmp blks when no longed used at all
 */
static void free_cpblks(void)
{
 struct cpblk_t *cpbp, *cpbp2;

 /* free all cell pin blks since ncomp form now gone */
 for (cpbp = __hdr_cpblks; cpbp != NULL;)
  {
   cpbp2 = cpbp->cpblknxt;
   __my_free(cpbp->cpblks, BIG_ALLOC_SIZE);
   __my_free(cpbp, sizeof(struct cpblk_t));
   cpbp = cpbp2;
  }
}

/*
 * routine to free all allocated cell pin and cell pin name blks when
 * no longed used at all
 *
 * SJM 03-01-09 done will
 */
static void free_cppblks(void)
{
 struct cppblk_t *cppbp, *cppbp2;
 struct cpnblk_t *cpnbp, *cpnbp2;

 /* free all cell pin blks since ncomp form now gone */
 for (cppbp = __hdr_cppblks; cppbp != NULL;)
  {
   cppbp2 = cppbp->cppblknxt;
   __my_free(cppbp->cppblks, BIG_ALLOC_SIZE);
   __my_free(cppbp, sizeof(struct cppblk_t));
   cppbp = cppbp2;
  }
 for (cpnbp = __hdr_cpnblks; cpnbp != NULL;)
  {
   cpnbp2 = cpnbp->cpnblknxt;
   __my_free(cpnbp->cpnblks, BIG_ALLOC_SIZE);
   __my_free(cpnbp, sizeof(struct cpnblk_t));
   cpnbp = cpnbp2;
  }
}

/*
 * ROUTINES TO SPLIT (COPY) MODULES
 */

/*
 * copy the module and link in to list module list unless only 1 inst.
 * __modsyms updated when this is done so split module insts. can be split
 *
 * if from pound param splitting must also copy non rooted defparams
 * split off module, splitting sets __inst_mod to point to it
 * so caller must save and restore __inst_mod
 */
extern void __do_mdsplit(struct mod_t *smdp)
{
 char s1[IDLEN];
 struct sy_t *syp;

 /* for master, version no. is highest of split off, else actual no. */
 if (!smdp->msplit)
  {
   /* __splitting a module effects exactly one flattened inst. too */
   /* flat inst counts and version numbers only kept in original master */
   (smdp->mversno)++;
   sprintf(s1, "%s$$%d", smdp->msym->synam, smdp->mversno);
  }
 else
  {
   /* for module, should never split from already split */
   __misc_terr(__FILE__, __LINE__);
  }
 __splitting = TRUE;
 copy_mod(smdp, s1);
 /* new split off module now pointed to by __inst_mod */
 __splitting = FALSE;

 /* must link on end so gets processed later */
 if (__end_mdp == NULL) __modhdr = __inst_mod;
 else __end_mdp->mnxt = __inst_mod;
 __end_mdp = __inst_mod;

 syp = smdp->msym;
 __gfinform(409, syp->syfnam_ind, syp->sylin_cnt,
  "module %s converted to new type - defparam or # parameter changes width",
  syp->synam); 
}

/*
 * copy a module - point __inst_mod to newly created module
 *
 * this is passed the master to copy out of
 * expects splitting to be true and adjust old module counts
 * new module does not have any defparams since info from master's
 * if from pound must copy non rooted defparams also
 *
 * this copies internal module components but does not insert new module
 * type in itree or up module's inst_t list
 *
 * BEWARE - non standard use of inst mod required here no itstk value
 */
static void copy_mod(struct mod_t *omdp, char *newnam)
{
 struct sy_t *syp;

 __oinst_mod = omdp;
 __inst_mod = (struct mod_t *) __my_malloc(sizeof(struct mod_t));

 /* notice this copies the flags which always stay the same */
 *__inst_mod = *omdp;

 __inst_mod->msplit = TRUE;
 __oinst_mod->mhassplit = TRUE;
 /* must add new name to modsyms - copy here can not effect undef mods */
 /* because all references resolved or will not get here */
 if ((syp = __add_modsym(newnam)) == NULL)
  {
   /* unable to split module to version and name */
   __misc_gfterr(__FILE__, __LINE__, omdp->msym->syfnam_ind,
    omdp->msym->sylin_cnt);
  }

 /* must set new sym and new version */
 syp->sydecl = TRUE;
 syp->el.emdp = __inst_mod;
 syp->syfnam_ind = __oinst_mod->msym->syfnam_ind;
 syp->sylin_cnt = __oinst_mod->msym->sylin_cnt;
 /* never need to connect through old splt sym here */
 __inst_mod->msym = syp;

 /* __splitting off from already split impossible */
 if (__oinst_mod->mspltmst != NULL) __misc_terr(__FILE__, __LINE__);

 /* not decing non flattented module insts. = only used to determine tops */
 (__oinst_mod->flatinum)--;
 /* can never be 0 instances of old copied from */
 if (__oinst_mod->flatinum == 1) __oinst_mod->minstnum = 1;
 __inst_mod->minstnum = 1;
 __inst_mod->flatinum = 1;

 /* connect current module to module type that was its source */
 /* if split off already split, link to real master */
 /* once split off no way to resplit since params frozen at split point */
 if (__oinst_mod->mspltmst != NULL)
  __inst_mod->mspltmst = __oinst_mod->mspltmst;
 else __inst_mod->mspltmst = __oinst_mod;

 /* caller responsible for linking into list */
 __inst_mod->mnxt = NULL;

 /* copy symbol table including all lower such as tasks and named blocks */
 /* SJM 01-06-09 key is that the n head field links from old to new symbol */
 /* SJM 05-02-10 - also need to copy gen blk sym tab tree so routine chged */
 __inst_mod->msymtab = copy_mod_or_gen_symtabs(__oinst_mod->msymtab);
 __inst_mod->msymtab->sypofsyt = __inst_mod->msym;

 /* must copy global references before copy any expressions */
 /* SJM 09-05-11 - notice now defparam grefs malloced and linked to dfp */
 copy_mgrefs();

 /* notice since params and ports really wires, must copy nets first */
 /* but after symbol table copied */
 copy_wires(__oinst_mod->msymtab, __inst_mod->msymtab);
 copy_modports();
 __inst_mod->mprms = copy_params(__oinst_mod->mprms, __oinst_mod->mprmnum,
  MODULE);
 /* AIV 09/27/06 - need to copy the local params as well */
 __inst_mod->mlocprms = copy_params(__oinst_mod->mlocprms, 
  __oinst_mod->mlocprmnum, MODULE);

 if (__oinst_mod->mdfps != NULL)
  {
   copy_defparams();
   /* SJM 09-08-11 - in copied to, must turn off saving so next time */
   /* through will move from this mod's copied to defparams to sav */
   /* for future passes */
   __inst_mod->sav_mdfps = NULL;
  }

 if (__oinst_mod->mattrs != NULL)
  __inst_mod->mattrs = copy_attrs(__oinst_mod->mattrs);
 if (__oinst_mod->mvarinits != NULL)
  __inst_mod->mvarinits = copy_varinits(__oinst_mod->mvarinits);

 copy_insts();

 copy_iploctab();
 
 copy_gates();
 
 copy_contas();
 copy_mdtasks();

 __inst_mod->ialst = copy_ialst(__oinst_mod->ialst);
 if (__oinst_mod->mspfy != NULL) copy_specify();

 /* AIV 03/26/07 - copy the system function call table */
 /* AIV LOOKATME - this can go when sys calls are lowered */
 if (__oinst_mod->expr_tab != NULL) copy_expr_table();

 /* SJM 03-03-09 - now need to copy gen items too if used in mod */
 if (__oinst_mod->mgenitems != NULL)
  {
   __inst_mod->mgenitems = copy_genitem_lst(__oinst_mod->mgenitems, NULL);
   /* SJM 03-30-10 - no need to fixup gref in gblk ptrs - just set for dbg */ 
  }
}

/*
 * AIV 03/26/07 - copy the system function call table 
 * AIV LOOKATME - this can go when sys calls are lowered
 */
static void copy_expr_table(void)
{
 size_t size;
 struct expr_tab_t *oetp, *netp;

 oetp =  __oinst_mod->expr_tab;
 netp = (struct expr_tab_t *) __my_malloc(sizeof(struct expr_tab_t));
 netp->num = oetp->num;
 netp->size = oetp->size;
 size = netp->size*sizeof(struct expr_t *);
 netp->table = (struct expr_t **) __my_malloc(size);
 size = oetp->num*sizeof(struct expr_t *);
 memcpy(netp->table, oetp->table, size);
 __inst_mod->expr_tab = netp;
}

/*
 * copy module symbol table structure
 * expects __oinst_mod to be set to old inst mod, __inst_mod to newly alloced
 * still must set all symbol el. union values
 * this does not copy specify symbol table for specparams
 */
static struct symtab_t *copy_mod_or_gen_symtabs(struct symtab_t *osytp)
{
 struct symtab_t *nsytp;

 nsytp = copy_1symtab(osytp);
 nsytp->sytpar = NULL;
 nsytp->sytsib = NULL;
 nsytp->sytofs = NULL;
 nsytp->linkto_cp_osytp = NULL;
 /* this copy is and connects by linking in pointers */
 if (osytp->sytofs != NULL) copy_lowsymtab(osytp->sytofs, nsytp);
 return(nsytp);
}

/*
 * depth first symbol table tree traversal across offspring
 */
static void copy_lowsymtab(struct symtab_t *osytp, struct symtab_t *nupsytp)
{
 struct symtab_t *nsytp, *last_nsytp;

 for (last_nsytp = NULL; osytp != NULL; osytp = osytp->sytsib)
  {
   nsytp = copy_1symtab(osytp);
   if (last_nsytp == NULL) nupsytp->sytofs = nsytp;
   else last_nsytp->sytsib = nsytp;

   /* link up */
   nsytp->sytpar = nupsytp;
   /* copy underneath level (know only frozen tables copied) */
   if (osytp->sytofs != NULL) copy_lowsymtab(osytp->sytofs, nsytp);
   nsytp->sytsib = NULL;
   last_nsytp = nsytp;
  }
}

/*
 * copy one symbol table
 * caller fills in up and down links
 */
static struct symtab_t *copy_1symtab(struct symtab_t *osytp)
{
 int32 ofreezes;
 struct symtab_t *nsytp;

 /* DBG remove -- */
 if (osytp->numsyms != 0 && osytp->n_head != NULL)
  __misc_terr(__FILE__, __LINE__);
 /* ---*/

 ofreezes = osytp->freezes;
 nsytp = __alloc_symtab(ofreezes);
 *nsytp = *osytp;
 /* SJM 02-06-11 - need to nil fields that need to be set - sometimes in */
 /* caller */
 nsytp->linkto_cp_osytp = NULL;  
 nsytp->sypofsyt = NULL;
 nsytp->gblkofsyt = NULL;
 /* must leave as NULL if empty table */
 if (osytp->numsyms == 0) nsytp->stsyms = NULL;
 else nsytp->stsyms = copy_stsyms(osytp->stsyms, osytp->numsyms);

 /* when above symbol table was copied, old symbol links to new */
 /* SJM 12/26/03 - specify symbol table has no associated symbol */
 if (osytp->sypofsyt != NULL) nsytp->sypofsyt = osytp->sypofsyt->spltsy;
 else nsytp->sypofsyt = NULL;

 /* SJM 03-18-09 - notice gblk of sytab not copied, caller must set if need */

 /* must link old to point to new */
 /* SJM 01-18-09 now separate field from old to new while copying sym tabs */
 osytp->linkto_cp_osytp = nsytp;
 return(nsytp);
}

/*
 * copy stsyms - know at least one symbol in table
 */
static struct sy_t **copy_stsyms(struct sy_t **osytab,
 word32 nsyms)
{
 int32 i, bytes;
 struct sy_t **sytbp;
 struct sy_t *nsyp;

 bytes = nsyms*sizeof(struct sy_t *);
 __wrkstab = (struct sy_t **) __my_malloc(bytes);
 for (i = 0; i < (int32) nsyms; i++)
  {
   /* allocate the new symbol */
   nsyp = (struct sy_t *) __my_malloc(sizeof(struct sy_t));
   *nsyp = *(osytab[i]);
   /* SJM 04-18-10 - for special case task in gen sy tab copying, leave net */
   /* nets are in task and get copied later - cross linking right */
   if (!__gentsk_copying)  
    {
     /* set union to NULL, any member will do */
     nsyp->el.ecp = NULL;
    }
   __wrkstab[i] = nsyp;
   /* tmp link from old to new */
   osytab[i]->spltsy = nsyp;

   /* DBG remove */ 
   if (__debug_flg)
    {
     __dbg_msg("copy of sym %s type %s (split %s)\n", nsyp->synam,
      __to_sytyp(__xs, nsyp->sytyp), osytab[i]->spltsy->synam);
    }
   /* --- */

   /* SJM 03-20-09 - mark copied from sym as in gen blk - when copy expr */
   /* and see sym declared in gen blk (usually local net) need splt sy set */
   if (__genblk_copying) osytab[i]->sy_in_genblk = TRUE;

  }
 sytbp = __wrkstab;
 return(sytbp);
}

/*
 * copy module ports
 */
static void copy_modports(void)
{
 int32 pi, pnum;
 struct mod_pin_t *ompp, *nmpp;

 if ((pnum = __oinst_mod->mpnum) == 0) return;

 __inst_mod->mpins = (struct mod_pin_t *)
  __my_malloc(pnum*sizeof(struct mod_pin_t)); 

 nmpp = &(__inst_mod->mpins[0]);  
 for (pi = 0, ompp = &(__oinst_mod->mpins[0]); pi < pnum; pi++, ompp++, nmpp++)
  {
   *nmpp = *ompp;
   nmpp->mpref = __copy_expr(ompp->mpref);
  }
}

/*
 * copy wires from __oinst_mod to __inst_mod
 * also link in nsym and symbol table el.enp
 * know decl. symbol tables for these
 *
 * at this point do not know if wire correct - must copy from symbol table
 */
static void copy_wires(struct symtab_t *sytp, struct symtab_t *new_sytp)
{
 int32 syi;
 struct sy_t **syms;
 struct sy_t *syp;
 struct net_t *onp, *nnp;

 for (syms = sytp->stsyms, syi = 0; syi < (int32) sytp->numsyms; syi++)
  {
   syp = syms[syi];
   if (syp->sytyp != SYM_N) continue;
   onp = syp->el.enp;
   /* do not copy parameters or specparams here */
   if (onp->n_isaparam) continue;
   
   nnp = copy_1wire_guts(onp);

   /* when symbol table copied old spltsy field pointed to new */
   /* copying symbol table copies symbols */
   syp = onp->nsym->spltsy;
   nnp->nsym = syp;
   syp->el.enp = nnp;
   /* SJM 05/07/06 - must also set net's containing symtab to new */
   /* SJM 03-03-09 - because of gen now always copy syt of net */
   nnp->syt_of_net = new_sytp;

   /* mutual links now separated */
   /* must not change splt sym since still needed by param type regs */
  }
}

/*
 * routine to copy the guts of one net (wire or reg)
 *
 * SJM 03-02-09 caller handles linking through symbol table
 * or link to gen item for generate and set name during gen expand
 */
static struct net_t *copy_1wire_guts(struct net_t *onp)
{
 struct net_t *nnp;

 /* must copy depending or original storage method */
 nnp = (struct net_t *) __my_malloc(sizeof(struct net_t));
 /* copy body */
 *nnp = *onp;
 /* allocate extra storage area */
 nnp->nu.ct = __alloc_arrncomp(); 
 /* copy ncomp body */
 *(nnp->nu.ct) = *(onp->nu.ct); 
 /* DBG remove --- */
 if (nnp->nrngrep != NX_CT) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (nnp->n_isavec)
  {
   nnp->nu.ct->nx1 = __copy_expr(onp->nu.ct->nx1);
   nnp->nu.ct->nx2 = __copy_expr(onp->nu.ct->nx2);
  }
 else nnp->nu.ct->nx1 = nnp->nu.ct->nx2 = NULL;

 if (nnp->n_isarr)
  {
   nnp->nu.ct->ax1 = __copy_expr(onp->nu.ct->ax1);
   /* notice this copies initial value expr. for params */
   nnp->nu.ct->ax2 = __copy_expr(onp->nu.ct->ax2);
  }
 else nnp->nu.ct->ax1 = nnp->nu.ct->ax2 = NULL;

 if (onp->nattrs != NULL) nnp->nattrs = copy_attrs(onp->nattrs);
 else nnp->nattrs = NULL;

 nnp->nu.ct->n_dels_u.pdels = __copy_dellst(onp->nu.ct->n_dels_u.pdels);

 /* SJM 01-18-09 - must also now copy mda record for mult-dim arrays */
 if (onp->mda != NULL) nnp->mda = copy_mda(onp->mda);
 return(nnp);
}

/*
 * routine to copy mda record for multi-dim arrays
 */
static struct mda_t *copy_mda(struct mda_t *omdap)
{
 int32 i, num_dims;
 struct mda_t *nmdap;

 nmdap = (struct mda_t *) __my_malloc(sizeof(struct mda_t));
 *nmdap = *omdap;
 
 num_dims = omdap->dimension;
 nmdap->tab_ax1 = (struct expr_t **)
  __my_malloc(num_dims*sizeof(struct expr_t *));
 nmdap->tab_ax2 = (struct expr_t **)
  __my_malloc(num_dims*sizeof(struct expr_t *));
 if (omdap->rng1 != NULL)
  {
   nmdap->rng1 = (int32 *) __my_malloc(num_dims*sizeof(int32));
   nmdap->rng2 = (int32 *) __my_malloc(num_dims*sizeof(int32));
  }
 /* DBG remove -- */
 else { if (omdap->rng2 != NULL) __misc_terr(__FILE__, __LINE__); }
 /* --- */
 if (omdap->dim_mult != NULL)
  {
   nmdap->dim_mult = (int32 *) __my_malloc(num_dims*sizeof(int32));
  }

 for (i = 0; i < num_dims; i++)
  {
   nmdap->tab_ax1[i] = __copy_expr(omdap->tab_ax1[i]);
   nmdap->tab_ax2[i] = __copy_expr(omdap->tab_ax2[i]);
   
   if (omdap->rng1 != NULL)
    {
     nmdap->rng1[i] = omdap->rng1[i];
     nmdap->rng2[i] = omdap->rng2[i];
    }
   if (omdap->dim_mult != NULL)
    {
     nmdap->dim_mult[i] = omdap->dim_mult[i];
    }
  }
 return(nmdap);
}

/*
 * copy wire from wire array template
 */
extern void __copy_wire_from_wire_array(struct net_t *nnp, struct net_t *onp)
{
 /* copy body */
 *nnp = *onp;
 /* allocate extra storage area */
 nnp->nu.ct = __alloc_arrncomp(); 
 /* copy ncomp body */
 *(nnp->nu.ct) = *(onp->nu.ct); 
 /* DBG remove --- */
 if (nnp->nrngrep != NX_CT) __misc_terr(__FILE__, __LINE__);
 /* --- */
 if (nnp->n_isavec)
  {
   nnp->nu.ct->nx1 = __copy_expr(onp->nu.ct->nx1);
   nnp->nu.ct->nx2 = __copy_expr(onp->nu.ct->nx2);
  }
 else nnp->nu.ct->nx1 = nnp->nu.ct->nx2 = NULL;
 /* new net never array */
 nnp->nu.ct->ax1 = nnp->nu.ct->ax2 = NULL;
 nnp->mda = NULL;
 nnp->n_isarr = FALSE;
 
 if (onp->nattrs != NULL) nnp->nattrs = copy_attrs(onp->nattrs);
 else nnp->nattrs = NULL;
 nnp->nu.ct->n_dels_u.pdels = __copy_dellst(onp->nu.ct->n_dels_u.pdels);

 /* do not have the new symbol yet */
 /* SJM 05/07/06 - must also set net's containing symtab to new */
 nnp->syt_of_net = __inst_mod->msymtab;
}

/*
 * copy params (storage same as nets and also by here will be in tab form)
 * for both module and task/func params 
 *
 * also links in nsym and symbol table el.enp
 * know decl. symbol tables for these
 *
 * value of param as parm_var net is assumed to be in pxp format
 * and expr. copied.
 */
static struct net_t *copy_params(struct net_t *onptab, int32 oprmnum,
 int32 pclass)
{
 int32 ni, nbytes, awid;
 struct sy_t *syp;
 struct net_t *nnp, *onp, *nnptab;

 if (oprmnum == 0) return(NULL);
 nbytes = oprmnum*sizeof(struct net_t);
 /* allocate and copy new parameter (really nets) as a block */ 
 nnptab = (struct net_t *) __my_malloc(nbytes);
 memcpy(nnptab, onptab, nbytes);
 
 /* need to also allocate and copy ncomp union field for each */
 for (ni = 0; ni < oprmnum; ni++)
  {
   nnp = &(nnptab[ni]);
   onp = &(onptab[ni]);
   /* DBG remove --- */
   if (pclass == MODULE)
    { if (!onp->n_isaparam) __misc_terr(__FILE__, __LINE__); }
   else if (pclass == SPECIFY)
    { if (!onp->n_isaparam) __misc_terr(__FILE__, __LINE__); }
   else __case_terr(__FILE__, __LINE__);
   /* --- */

   /* get area from special block */
   nnp->nu.ct = __alloc_arrncomp(); 

   *(nnp->nu.ct) = *(onp->nu.ct); 
   if (nnp->n_isavec)
    {
     nnp->nu.ct->nx1 = __copy_expr(onp->nu.ct->nx1);
     nnp->nu.ct->nx2 = __copy_expr(onp->nu.ct->nx2);
    }
   else nnp->nu.ct->nx1 = nnp->nu.ct->nx2 = NULL;

   /* know rhs will still be one expr. (SR_PNUM) here pointed to by nva */
   /* SJM 02-19-09 - need to allow this - only happens after syntax error */
   /* for error recovery */
   
   /* must also handle parameter arrays */
   if (onp->n_isarr)
    {
     nnp->nu.ct->ax1 = __copy_expr(onp->nu.ct->ax1);
     nnp->nu.ct->ax2 = __copy_expr(onp->nu.ct->ax2);
     awid = __get_arrwide(onp); 
     /* arrays of parameters never packed always take at least 8 bytes */
     nbytes = 2*WRDBYTES*awid*wlen_(onp->nwid);
    }
   else
    {
     nnp->nu.ct->ax1 = nnp->nu.ct->ax2 = NULL;
     nbytes = 2*WRDBYTES*wlen_(onp->nwid); 
    }
   /* alloc and copy value */
   nnp->prm_nva.wp = (word32 *) __my_malloc(nbytes);
   memcpy(nnp->prm_nva.wp, onp->prm_nva.wp, nbytes);
   /* AIV 03/15/11 - need to mark this as a regular parameter */
   /* this can now make multiple passes through fixup for generate and */
   /* the next time around this may have to convert back to IS again */
   /* thus the malloc here might be too small because it is */
   nnp->srep = SR_PNUM;

   /* and copy source expr for params kept in n_dels_u field */
   /* DBG remove --- */
   if (onp->nu.ct->parm_srep != SR_PXPR) __misc_terr(__FILE__, __LINE__);
   /* --- */
   nnp->nu.ct->n_dels_u.d1x = __copy_expr(onp->nu.ct->n_dels_u.d1x);

   /* when symbol table copied old splt sym field pointed to new */
   /* copying symbol table copies symbols */
   syp = onp->nsym->spltsy;
   nnp->nsym = syp;
   syp->el.enp = nnp;
   /* mutual links now separated */
   /* must not change splt sym since still needed by param type regs */

   /* SJM 08-31-11 - because of checking later, also need to set the */
   /* syt of net from old param */
   /* DBG remove -- */
   if (onp->syt_of_net == NULL) __misc_terr(__FILE__, __LINE__);
   if (onp->syt_of_net->linkto_cp_osytp == NULL)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   nnp->syt_of_net = onp->syt_of_net->linkto_cp_osytp;
  }
 return(nnptab);
}

/*
 * copy downward relative only defparams - know checking completed
 *
 * SJM 04-04-10 - now need to copy defparams in gblks or with gblk in path
 * separately
 */
static void copy_defparams(void)
{
 struct dfparam_t *odfpp, *ndfpp;
 struct dfparam_t *ndfphdr, *ndfpend;

 ndfphdr = ndfpend = NULL;
 for (odfpp = __oinst_mod->mdfps; odfpp != NULL; odfpp = odfpp->dfpnxt) 
  {
   /* for rooted defparam in copied has no effect */
   /* if copying during splitting from defparams, down relative gone */ 

   /* SJM from 03-02-09 now 04-04-10 - before any copying defparams not */
   /* in gen blks moved to design wide rooted list */ 
   if (odfpp->dfp_rooted) continue; 

   ndfpp = __copy1_defparam(odfpp);
  
   if (ndfphdr == NULL) ndfphdr = ndfpp; else ndfpend->dfpnxt = ndfpp;  
   ndfpend = ndfpp;
  }
 __inst_mod->mdfps = ndfphdr;
}

/*
 * routine to copy 1 def param
 * notice proc used both by gen xpnd copy and mod split copy 
 *
 * SJM 03-03-09 - now separate proc since also used by expand gen defparam
 * SJM 09-06-11 - notice for xmr's copy expr uses ngrp to old fld - for
 * defps must cross link here
 *
 * SJM 09-07-11 - now using for making rooted defparams so must allow
 * copy local (lhs is not XMR)
 */
extern struct dfparam_t *__copy1_defparam(struct dfparam_t *odfpp)
{
 int32 dfi;
 struct dfparam_t *ndfpp;

 /* always copy local defparams */
 ndfpp = (struct dfparam_t *) __my_malloc(sizeof(struct dfparam_t));
 *ndfpp = *odfpp;
 ndfpp->dfpxlhs = __copy_expr(odfpp->dfpxlhs);
 ndfpp->dfpxrhs = __copy_expr(odfpp->dfpxrhs);
 /* SJM 09-07-11 - two cases if called from splitting mod copy, inst mod */
 /* is really the new mod which is right since copying to, for defparam */
 /* gen first step of move to source copying, inst mod current mod */
 ndfpp->dfp_in_mdp = __inst_mod;

 /* SJM 01-19-08 - also used in pre nl fixup copy where gdfpnam not */
 /* yet set because during fix up gets the gref name */
 if (ndfpp->gdfpnam != NULL)
  {
   ndfpp->gdfpnam = __pv_stralloc(odfpp->gdfpnam);
  }

 if (odfpp->dfpxlhs->optyp == GLBREF) 
  {
   /* DBG remove -- */
   if (odfpp->dfp_grp == NULL) __misc_terr(__FILE__, __LINE__);
   /* -- */
   /* SJM 09-03-11 - for dfps - must copy the assoc. gref - no dfp grtab */
   ndfpp->dfp_grp = (struct gref_t *) __my_malloc(sizeof(struct gref_t));

   copy_1dfp_gref_flds(ndfpp->dfp_grp, odfpp->dfp_grp);
   /* SJM 09-06-11 - cross link defp's copied to gref and lhs glb ref xpr */
   ndfpp->dfp_grp->gxndp = ndfpp->dfpxlhs;
   ndfpp->dfpxlhs->ru.grp = ndfpp->dfp_grp;
  } 

 /* since resetting do not need this code --
 if (odfpp->dfptskp != NULL)
  ndfpp->dfptskp = odfpp->dfptskp->tsksyp->spltsy->el.etskp;
 --- */
 ndfpp->dfpnxt = NULL;
 ndfpp->rooted_dfps = NULL;

 /* dfp path not yet set - must not copy */
 /* must look up target symbols for defparam at end, no copy here */ 
 if (odfpp->dfpiis != NULL)
  {
   ndfpp->dfpiis = (int32 *) __my_malloc((ndfpp->last_dfpi + 1)*sizeof(int32));
   /* SJM 06/03/05 - index was wrongly not starting at 0 */
   for (dfi = 0; dfi < ndfpp->last_dfpi + 1; dfi++)
    ndfpp->dfpiis[dfi] = odfpp->dfpiis[dfi];
  }

 /* SJM 03-15-10 - for dfps in gblks, just copies wrong ptr, fixed up later */
 return(ndfpp);
}

/*
 * copy Verilog 2000 attributes
 */
static struct attr_t *copy_attrs(struct attr_t *oattrp)
{
 struct attr_t *nattrp, *nattr_hd, *last_nattrp; 

 last_nattrp = NULL;
 nattr_hd = NULL;
 for (; oattrp != NULL; oattrp = oattrp->attrnxt)
  {
   nattrp = (struct attr_t *) __my_malloc(sizeof(struct attr_t));
   *nattrp = *oattrp;
   nattrp->attrnam = __pv_stralloc(oattrp->attrnam);
   if (oattrp->attr_xp != NULL)
    nattrp->attr_xp = __copy_expr(oattrp->attr_xp);
   nattrp->attrnxt = NULL;
   if (last_nattrp == NULL) nattr_hd = nattrp;
   else last_nattrp->attrnxt = nattrp;  
   last_nattrp = nattrp;
  }
 return(nattr_hd);
}

/*
 * routine for copy module variable initialize assign var init records
 *
 * notice this must be copied after copying wires and parameters 
 */
static struct varinitlst_t *copy_varinits(struct varinitlst_t *oinitp)
{
 struct varinitlst_t *ninitp, *nvarinit_hd, *last_initp; 

 last_initp = NULL;
 nvarinit_hd = NULL;
 ninitp = NULL;
 for (; oinitp != NULL; oinitp = oinitp->varinitnxt)
  {
   ninitp = (struct varinitlst_t *) __my_malloc(sizeof(struct varinitlst_t));
   *ninitp = *oinitp;
   ninitp->init_syp = oinitp->init_syp->spltsy;
   ninitp->init_xp = __copy_expr(oinitp->init_xp); 
   ninitp->varinitnxt = NULL;
   if (last_initp == NULL) nvarinit_hd = ninitp;
   else last_initp->varinitnxt = ninitp;
   last_initp = ninitp;
  }
 return(nvarinit_hd);
}

/*
 * ROUTINES TO COPY INSTS FOR SPLITTING COPY
 */

/*
 * routine for copying module instances
 */
static void copy_insts(void)
{
 int32 ii;
 struct inst_t *oip, *nip, *first_oip, *first_nip;

 /* if no instances - original copy set fields to nil and 0 */
 if (__oinst_mod->minum == 0)
  {
   __inst_mod->minsts = NULL;
   return;
  }

 /* DBG remove -- */
 if (!__splitting) __misc_terr(__FILE__, __LINE__);
 /* -- */

 __inst_mod->minsts = (struct inst_t *)
  __my_malloc(__oinst_mod->minum*sizeof(struct inst_t));

 first_nip = first_oip = NULL;
 for (ii = 0; ii < __oinst_mod->minum; ii++)
  {
   oip = &(__oinst_mod->minsts[ii]);
   nip = &(__inst_mod->minsts[ii]);
   copy_1inst(nip, oip);

   /* copy inst's giap record if present - tricky because all copied non */
   /* first (base) must point to the same gia base sym */
   if (oip->i_giap != NULL)
    {
     /* always copy gia aux rec */
     __copy1_inst_gia_rec(nip, oip->i_giap);
     if (oip->i_giap->gia_is_base_first) 
      {
       /* case 1: a base first - gia base sym for all must pt to this one */
       nip->i_giap->gia_base_syp = oip->i_giap->gia_base_syp->spltsy;
       first_oip = oip;
       first_nip = nip;
      }
     else
      {
       /* DBG remove -- */
       if (first_nip == NULL) __misc_terr(__FILE__, __LINE__);
       if (oip->i_giap->gia_base_syp != first_oip->i_giap->gia_base_syp) 
        __misc_terr(__FILE__, __LINE__);
       /* --- */
       /* case 2: non first - base syp must point to base syp from 1st */
       nip->i_giap->gia_base_syp = first_nip->i_giap->gia_base_syp;
      } 
    }
   else first_oip = first_nip = NULL;
  }
 /* SJM 09-08-11 - notice mod's num of insts same in copied to so body */
 /* copy sets */
}

/*
 * copy 1 instance
 */
static void copy_1inst(struct inst_t *nip, struct inst_t *oip)
{
 struct sy_t *syp;

 /* this copies instance must split for later if needed (>1 unsplit) */
 *nip = *oip;

 /* SJM 04-29-10 - cell names (insts) always put in gen blk symtab so splt sy */
 /* will be set when gen blk containing inst copied (since inst in some gen */
 /* blk always will be set to point to new sym tab's sym */
 /* also always set for normal mod copy */
 /* DBG remove -- */
 if (oip->isym == NULL || oip->isym->spltsy == NULL) 
  __misc_terr(__FILE__, __LINE__);
 /* --- */  
 syp = oip->isym->spltsy;
 nip->isym = syp;
 syp->el.eip = nip;

 /* mutual links now separated */
 /* notice module symbol (in modsyms) the same until splitting completed */
 nip->ipxprtab = __copy_pndxtab(oip);

 if (oip->iattrs != NULL) nip->iattrs = copy_attrs(oip->iattrs);
 else nip->iattrs = NULL;

 copy_iports(nip, oip);
 if (oip->i_giap != NULL) __copy1_inst_gia_rec(nip, oip->i_giap);
}

/*
 * routine to copy one array of insts gia aux record
 *
 * only called if old inst was an array of insts form (or split part of one)
 */
extern void __copy1_inst_gia_rec(struct inst_t *nip, struct gia_aux_t *ogiap)
{
 struct gia_aux_t *ngiap;

 ngiap = (struct gia_aux_t *) __my_malloc(sizeof(struct gia_aux_t));
 nip->i_giap = ngiap;
 *ngiap = *ogiap;

 /* new needs to point to right (its newly copied) module's ipins list */
 ngiap->giapins_ptr = nip->ipins;

 /* only other fields that need copying is expression */
 ngiap->giax1 = __copy_expr(ogiap->giax1);
 ngiap->giax2 = __copy_expr(ogiap->giax2);
}

/*
 * copy pound param expression table
 *
 * if pound param expr. table exists it has loc (maybe nil) for every mod param
 */
extern struct expr_t **__copy_pndxtab(struct inst_t *oip)
{
 int32 pi;
 struct expr_t **nnpxtab, **onpxtab;
 struct mod_t *imdp;

 if ((onpxtab = oip->ipxprtab) == NULL) return(NULL);

 imdp = oip->imsym->el.emdp;
 nnpxtab = (struct expr_t **)
  __my_malloc(imdp->mprmnum*sizeof(struct expr_t *));
 for (pi = 0; pi < imdp->mprmnum; pi++)
  {
   if (onpxtab[pi] == NULL) nnpxtab[pi] = NULL;
   else nnpxtab[pi] = __copy_expr(onpxtab[pi]);
  }
 return(nnpxtab);
}

/*
 * copy module instance ports
 */
static void copy_iports(struct inst_t *nip, struct inst_t *oip)
{
 int32 pi, pnum;

 if ((pnum = oip->imsym->el.emdp->mpnum) != 0)
  {
   nip->ipins = (struct expr_t **) __my_malloc(pnum*sizeof(struct expr_t *));
   for (pi = 0; pi < pnum; pi++) nip->ipins[pi] = __copy_expr(oip->ipins[pi]);
  }
 else nip->ipins = NULL;
}

/*
 * copy the ip loc table array
 *
 * SJM 07-14-07 - because of new mod inst array, need to copy the iploc
 * table since copied module may have a different number of instances
 *  during relaxation after unbld and rebld
 */
static void copy_iploctab(void)
{
 int32 ii, pi, nbytes;
 struct mod_t *oimdp;
 struct inst_t *oip;

 /* SJM 07-14-07 - if no instances - nothing to copy */
 if (__oinst_mod->minum == 0) 
  {
   __inst_mod->iploctab = NULL;
  return;
  }

 nbytes = __oinst_mod->minum*sizeof(struct srcloc_t *);
 __inst_mod->iploctab = (struct srcloc_t **) __my_malloc(nbytes);
 for (ii = 0; ii < __oinst_mod->minum; ii++)
  {
   oip = &(__oinst_mod->minsts[ii]);
   oimdp = oip->imsym->el.emdp;
   if (oimdp->mpnum == 0)
    {
     __inst_mod->iploctab[ii] = NULL;
     continue;
    }

   nbytes = oimdp->mpnum*sizeof(struct srcloc_t);
   __inst_mod->iploctab[ii] = (struct srcloc_t *) __my_malloc(nbytes);
   for (pi = 0; pi < oimdp->mpnum; pi++)
    {
     __inst_mod->iploctab[ii][pi] = __oinst_mod->iploctab[ii][pi];
    }
  }
}

/*
 * routine for copying module gates
 */
static void copy_gates(void)
{
 int32 gi;
 struct gate_t *ogp, *ngp, *first_ogp, *first_ngp;

 /* inst mod is new */
 if (__oinst_mod->mgnum == 0)
  {
   __inst_mod->mgates = NULL;
   return;
  }

 __inst_mod->mgates = (struct gate_t *)
  __my_malloc(__oinst_mod->mgnum*sizeof(struct gate_t));

 /* DBG remove -- */
 if (!__splitting) __misc_terr(__FILE__, __LINE__);
 /* -- */

 first_ngp = first_ogp = NULL;
 for (gi = 0; gi < __oinst_mod->mgnum; gi++)
  {
   ogp = &(__oinst_mod->mgates[gi]);
   ngp = &(__inst_mod->mgates[gi]);

   /* SJM 04-25-10 - now this does not copy the gia record for array of gates */ 
   copy_1gate(ngp, ogp);

   /* copy gate's giap record if present - tricky because all copied non */
   /* first (base) must point to the same gia base sym */
   if (ogp->g_giap != NULL)
    {
     /* always copy gia aux rec */
     __copy1_gate_gia_rec(ngp, ogp->g_giap);
     if (ogp->g_giap->gia_is_base_first) 
      {
       /* case 1: a base first - gia base sym for all must pt to this one */
       ngp->g_giap->gia_base_syp = ogp->g_giap->gia_base_syp->spltsy;
       first_ogp = ogp;
       first_ngp = ngp;
      }
     else
      {
       /* DBG remove -- */
       if (first_ngp == NULL) __misc_terr(__FILE__, __LINE__);
       if (ogp->g_giap->gia_base_syp != first_ogp->g_giap->gia_base_syp) 
        __misc_terr(__FILE__, __LINE__);
       /* --- */
       /* case 2: non first - base syp must point to base syp from 1st */
       ngp->g_giap->gia_base_syp = first_ngp->g_giap->gia_base_syp;
      } 
    }
   else first_ogp = first_ngp = NULL;
  }
}

/*
 * copy 1 gate (passes already allocated address in gate tables)
 */
static void copy_1gate(struct gate_t *ngp, struct gate_t *ogp)
{
 int32 pnum, pi;
 struct sy_t *syp;

 pnum = ogp->gpnum;
 /* copy everything but port connection expressions */
 *ngp = *ogp;
 if (ogp->gsym->spltsy == NULL)
  {
   ngp->gsym = NULL;
  }
 else
  {
   /* if gate unamed will still have gate<dol><dol> form name */
   syp = ogp->gsym->spltsy;
   /* DBG remove -- */  
   if (syp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* when symbol copied old splt sym field pointed to new */
   ngp->gsym = syp;
   syp->el.egp = ngp;
  }

 /* mutual links now separated */
 /* notice module symbol (in modsyms) the same until splitting completed */

 /* copy output that is still expr.  - gets changed to wire later */
 ngp->g_du.pdels = __copy_dellst(ogp->g_du.pdels);

 if (ogp->gattrs != NULL) ngp->gattrs = copy_attrs(ogp->gattrs);
 else ngp->gattrs = NULL;
 
 /* DBG remove -- */ 
 if (pnum <= 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 ngp->gpins = (struct expr_t **) __my_malloc(pnum*sizeof(struct expr_t *));
 /* copy the input port expressions */
 for (pi = 0; pi < pnum; pi++)
  {
   ngp->gpins[pi] = __copy_expr(ogp->gpins[pi]);
  }
}

/*

 * routine to copy one array of gates gia aux record
 * SJM 04-25-10 - now caller must set the base union sym/base giap
 *
 * only called if old inst was an array of insts form (or split part of one)
 */
extern void __copy1_gate_gia_rec(struct gate_t *ngp, struct gia_aux_t *ogiap)
{
 struct gia_aux_t *ngiap;

 ngiap = (struct gia_aux_t *) __my_malloc(sizeof(struct gia_aux_t));
 ngp->g_giap = ngiap;
 *ngiap = *ogiap;

 /* now needs to point to right (its newly copied) module's ipins list */
 /* SJM 04-21-10 gate pins already and always copied - gia aux needs to point */
 /* to gate's pins list which will be either original unexpanded array of */
 /* gates pins or for split copying, the copied version */
 ngiap->giapins_ptr = ngp->gpins;

 /* only other fields that need copying is expression */
 ngiap->giax1 = __copy_expr(ogiap->giax1);
 ngiap->giax2 = __copy_expr(ogiap->giax2);
}

/*
 * copy continuous assigns 
 */
static void copy_contas(void)
{
 struct conta_t *ocap, *ncap, *last_ncap;
 struct sy_t *syp;

 __inst_mod->mcas = NULL; 
 last_ncap = NULL;
 for (ocap = __oinst_mod->mcas; ocap != NULL; ocap = ocap->pbcau.canxt)
  {
   ncap = (struct conta_t *) __my_malloc(sizeof(struct conta_t));

   /* when symbol copied old splt sym field pointed to new */
   *ncap = *ocap;
   syp = ocap->casym->spltsy;
   ncap->casym = syp;
   syp->el.ecap = ncap;

   ncap->ca_du.pdels = __copy_dellst(ocap->ca_du.pdels);
   ncap->lhsx = __copy_expr(ocap->lhsx);
   ncap->rhsx = __copy_expr(ocap->rhsx);
   /* AIV 01/15/07 - if adding new conta need to make new enter index */
   if (__compiled_sim) ncap->enter_cndx = ++__cap_seq_no;
   if (last_ncap == NULL) __inst_mod->mcas = ncap;
   else last_ncap->pbcau.canxt = ncap;
   last_ncap = ncap;  
  }
 if (last_ncap != NULL) last_ncap->pbcau.canxt = NULL;
}

/*
 * copy all mod tasks
 */
static void copy_mdtasks(void)
{
 struct task_t *otskp, *ntskp, *last_ntskp;

 last_ntskp = NULL;
 __inst_mod->mtasks = NULL;
 for (otskp = __oinst_mod->mtasks; otskp != NULL; otskp = otskp->tsknxt)
  {
   ntskp = copy1_task(otskp);

   if (last_ntskp == NULL) 
    {
     __inst_mod->mtasks = ntskp;
#ifdef __XPROP__
    /* dummy non-blocking compiler task holder must be preserved */
    if (__inst_mod->xprop_nb_taskp == otskp)
      __inst_mod->xprop_nb_taskp = ntskp;
#endif
    }
   else last_ntskp->tsknxt = ntskp;
   last_ntskp = ntskp;
  }
}

/*
 * routine to copy 1 task 
 *
 * SJM 04-13-10 - needed for copying gen item tasks as separate routine
 * without the linking
 */
static struct task_t *copy1_task(struct task_t *otskp)
{
 struct task_t *ntskp;

 ntskp = (struct task_t *) __my_malloc(sizeof(struct task_t));
 *ntskp = *otskp;
 /* fill link from task to symbol table and symbol */
 /* SJM 01-18-09 now separate field from old to new while copying sym tabs */

 /* SYM 04-18-10 - for new special case copy of task in gen blk */
 /* (not in mod's items and sym tab tree), if no link, can just use the */
 /* already copied sym tab, for normal tasks, sym tab gets copied in */ 
 /* mod sym tab tree copy - expand needs speical case copy with no lnk */
 if (otskp->tsksymtab->linkto_cp_osytp != NULL)
  {
   ntskp->tsksymtab = otskp->tsksymtab->linkto_cp_osytp;
  }

 if (otskp->tsksyp != NULL)
  {
   /* notice must link both directions */
   ntskp->tsksyp = otskp->tsksyp->spltsy;
   ntskp->tsksyp->el.etskp = ntskp;
  }
 else ntskp->tsksyp = NULL;

 /* for tasks everything is a reg so must copy first */
 copy_wires(otskp->tsksymtab, ntskp->tsksymtab);

 /* for named blocks, connect from task to named block filled when named */
 /* block statement filled (st_namblkin field) */

 /* copy task pins */
 ntskp->tskpins = copy_tskargs(otskp);

 /* copy task params */
 ntskp->tsk_prms = copy_params(otskp->tsk_prms, otskp->tprmnum, MODULE);

 /* AIV 09/27/06 - need to copy the local params as well */
 ntskp->tsk_locprms = copy_params(otskp->tsk_locprms, otskp->tlocprmnum,
  MODULE); 

 /* copy the 1 statement */
 ntskp->tskst = __copy_lstofsts(otskp->tskst);

 /* SJM 02-08-09 - notice mod's elaborated con func never copied */
 ntskp->cfu.to_exec_confunc = NULL;

 return(ntskp);
}

/*
 * routine to copy a constant function image during elaborate time
 */
extern struct task_t *__image_copy_confunc(struct task_t *otskp)
{
 struct task_t *ntskp;

 ntskp = (struct task_t *) __my_malloc(sizeof(struct task_t));
 *ntskp = *otskp;
 if (otskp->tsksymtab != NULL)
  {
   ntskp->tsksymtab = copy_1symtab(otskp->tsksymtab);
  }
 /* SJM - 02-18-09 - both symbol tables have same name - can't add */
 /* here since mod symtabs are frozen */
 /* notice both the normal function for run time eval (maybe) and the */
 /* con function have same name - causes no problem */

 /* for tasks everything is a reg so must copy first */
 copy_wires(otskp->tsksymtab, ntskp->tsksymtab);

 /* for named blocks, connect from task to named block filled when named */
 /* block statement filled (st_namblkin field) */

 /* copy task pins */
 ntskp->tskpins = copy_tskargs(otskp);

 /* copy task params */
 ntskp->tsk_prms = copy_params(otskp->tsk_prms, otskp->tprmnum, MODULE);

 /* AIV 09/27/06 - need to copy the local params as well */
 ntskp->tsk_locprms = copy_params(otskp->tsk_locprms, otskp->tlocprmnum,
  MODULE); 

 /* copy the 1 statement */
 ntskp->tskst = __copy_lstofsts(otskp->tskst);
 return(ntskp);
}


/*
 * copy task ports - only regs can be ports
 */
static struct task_pin_t *copy_tskargs(struct task_t *otskp)
{
 struct task_pin_t *otpp, *last_ntpp, *ntpp, *ntpp_hdr;

 last_ntpp = NULL;
 ntpp_hdr = NULL;
 for (otpp = otskp->tskpins; otpp != NULL; otpp = otpp->tpnxt)
  {
   ntpp = (struct task_pin_t *) __my_malloc(sizeof(struct task_pin_t));
   /* this copies trtyp field */
   *ntpp = *otpp;
   ntpp->tpsy = otpp->tpsy->spltsy;
   ntpp->tpnxt = NULL;
   if (last_ntpp == NULL) ntpp_hdr = ntpp; else last_ntpp->tpnxt = ntpp;
   last_ntpp = ntpp;
  }
 return(ntpp_hdr);
}

/*
 * copy a statement entry
 */
extern struct st_t *__copy_stmt(struct st_t *ostp)
{
 struct st_t *nstp;
 struct sy_t *nsyp;

 if (ostp == NULL) return(NULL);

 /* AIV 07/13/09 - this needs to alloc enough for the generated items */
 /* in a generate region - alloc_stmt incs this so need to do this here */
 (__inst_mod->mstnum)++; 

 nstp = (struct st_t *) __my_malloc(sizeof(struct st_t));

 *nstp = *ostp;
 nstp->stnxt = NULL;

 switch ((byte) ostp->stmttyp) {
  /* null just has type value and NULL pointer (i.e. ; by itself) */
  case S_NULL: case S_STNONE: break;
  case S_PROCA: case S_FORASSGN: case S_RHSDEPROCA: case S_NBPROCA:
   nstp->st.spra.lhsx = __copy_expr(ostp->st.spra.lhsx);
   nstp->st.spra.rhsx = __copy_expr(ostp->st.spra.rhsx);
   break;
  case S_IF:
   nstp->st.sif.condx = __copy_expr(ostp->st.sif.condx);
   nstp->st.sif.thenst = __copy_lstofsts(ostp->st.sif.thenst);
   nstp->st.sif.elsest = __copy_lstofsts(ostp->st.sif.elsest);
#ifdef __XPROP__
   nstp->st.sif.xprop = ostp->st.sif.xprop;
   nstp->st.sif.xedge_dce = ostp->st.sif.xedge_dce;
#endif
   break;
  case S_CASE:
   nstp->st.scs.castyp = ostp->st.scs.castyp;
   nstp->st.scs.maxselwid = ostp->st.scs.maxselwid;
   nstp->st.scs.csx = __copy_expr(ostp->st.scs.csx);

   /* this also copies default which is first (always present) */
   /* if case has no default, st field nil */ 
   nstp->st.scs.csitems = copy_csitemlst(ostp->st.scs.csitems);
#ifdef __XPROP__
   /* now need to copy xprop stmt list if there is one */
   nstp->st.scs.xprop = ostp->st.scs.xprop;
   nstp->st.scs.xprop_lstp = __copy_lstofsts(ostp->st.scs.xprop_lstp);
#endif
   break;
  case S_REPEAT:
   nstp->st.srpt.repx = __copy_expr(ostp->st.srpt.repx);
   /* SJM 08-06-07 - tmp repeat cnt now in idp area for interp and cvc */
   nstp->st.srpt.reptmp_ofs = 0;
   nstp->st.srpt.repst = __copy_lstofsts(ostp->st.srpt.repst);
   break;
  case S_FOREVER:
  case S_WHILE:
  case S_DO_WHILE:
   nstp->st.swh.lpx = __copy_expr(ostp->st.swh.lpx);
   nstp->st.swh.lpst = __copy_lstofsts(ostp->st.swh.lpst);
   break;
  case S_WAIT:
   nstp->st.swait.lpx = __copy_expr(ostp->st.swait.lpx);
   nstp->st.swait.lpst = __copy_lstofsts(ostp->st.swait.lpst);
   /* until prep, this dctp is just allocated unfilled version */
   nstp->st.swait.wait_dctp = __alloc_dctrl();
   *(nstp->st.swait.wait_dctp) = *(ostp->st.swait.wait_dctp);
   break;
  case S_FOR:
   {
    struct for_t *nfrp, *ofrp;
    struct st_t *head_stp, *tail_stp, *stp2, *stp3;

    nfrp = (struct for_t *) __my_malloc(sizeof(struct for_t));
    nstp->st.sfor = nfrp;
    ofrp = ostp->st.sfor;
    nfrp->has_continue = ofrp->has_continue;
    nfrp->has_break = ofrp->has_break;
    /* AIV 04/08/11 - need to copy these fielse as well */
    nfrp->foreach_syp = ofrp->foreach_syp;
    nfrp->dim = ofrp->dim;
    nfrp->is_expanded_foreach = ofrp->is_expanded_foreach;
    /* AIV 10/01/10 - for assign can now have multiple - cannot use */
    /* list because is linked onto forbody */
    head_stp = NULL;
    /* just make a new list */
    stp3 = NULL;
    for (stp2 = ofrp->forassgn; stp2 != NULL; stp2 = stp2->stnxt)
     {
      if (stp2->stmttyp != S_FORASSGN) break;
      stp3 = __copy_stmt(stp2);
      if (head_stp == NULL) head_stp = tail_stp = stp3;
      else
       {
        tail_stp->stnxt = stp3;
        tail_stp = stp3;
       }
     }
    nfrp->forassgn = head_stp;

    nfrp->fortermx = __copy_expr(ofrp->fortermx);
    nfrp->forinc = __copy_lstofsts(ofrp->forinc);
    /* must get the new address of the last tail item */
    for (stp2 = nfrp->forinc; stp2 != NULL; stp2 = stp2->stnxt) 
     stp3 = stp2;

    nfrp->forinc_tail = stp3; 
    nfrp->forbody = __copy_lstofsts(ofrp->forbody);
   }
   break;
  case S_DELCTRL:
   {
    struct delctrl_t *ndcp, *odcp;

    ndcp = (struct delctrl_t *) __my_malloc(sizeof(struct delctrl_t));
    nstp->st.sdc = ndcp;
    odcp = ostp->st.sdc;
#ifdef __XPROP__
    /* if xprop copying these are already converted */
    /* xprop2 - is done pre-prep time so need the entire copy */
    if (__xprop_copying && !__xprop2)
     {
      *ndcp = *odcp;
      ndcp->actionst = __copy_stmt(odcp->actionst);
      ndcp->xprop_xedge_actionst = __copy_lstofsts(odcp->xprop_xedge_actionst);
      ndcp->xprop_nb_actionst = __copy_lstofsts(odcp->xprop_nb_actionst);
      break;
     }
#endif
    ndcp->dctyp = odcp->dctyp;
    ndcp->dc_iact = odcp->dc_iact; 
    /* SJM 08/02/02 - need to also explicitly copy new non blking flag */ 
    ndcp->dc_nblking = odcp->dc_nblking;
    /* SJM 08/17/04 - f2016 was failing because this was not set */
    ndcp->implicit_evxlst = odcp->implicit_evxlst;
    ndcp->dc_delrep = odcp->dc_delrep;
    ndcp->dc_is_always_comb_latch = odcp->dc_is_always_comb_latch;
    ndcp->dc_is_always_ff = odcp->dc_is_always_ff;
    ndcp->dc_du.pdels = __copy_dellst(odcp->dc_du.pdels);
    ndcp->repcntx = __copy_expr(odcp->repcntx);
    /* AIV 03/03/09 - need to copy new merged always block fields */
    /* AIV LOOKATME - maybe should just copy using * above ?????? */
    ndcp->is_merged = odcp->is_merged; 
    ndcp->is_always = odcp->is_always; 
    ndcp->needs_thread = odcp->needs_thread;
    ndcp->nested_dctrl = odcp->nested_dctrl; 
    ndcp->merged_dctp = odcp->merged_dctp; 
    ndcp->head_dctp = odcp->head_dctp; 
    ndcp->head_ctevp = odcp->head_ctevp; 
    ndcp->dc_id_ndx = odcp->dc_id_ndx;

    /* SJM 10/07/06 - repcnts not yet set - set in v prp2 */
    /* DBG remove --- */
    if (odcp->dce_repcnt_ofs != 0) __misc_terr(__FILE__, __LINE__);
    /* --- */

    ndcp->dce_repcnt_ofs = 0;
    ndcp->dceschd_tev_ofs = 0;
    /* can be list because of #10 begin ... end */
    ndcp->actionst = __copy_lstofsts(odcp->actionst);
#ifdef __XPROP__
    ndcp->xprop_xedge_actionst = __copy_lstofsts(odcp->xprop_xedge_actionst);
    ndcp->xprop_nb_actionst = __copy_lstofsts(odcp->xprop_nb_actionst);
    ndcp->d_has_xmr = odcp->d_has_xmr;
#endif
   }
   break;
  case S_NAMBLK:
   {
#ifdef __XPROP__
    /* this can only happen for __xprop2 - so notice disable etc will not */
    /* work correctly just leaving for now */
    if (__xprop_copying) 
     {
      nstp->stmttyp = S_UNBLK;
      nstp->st.sbsts = __copy_lstofsts(ostp->st.snbtsk->tskst);
      break;
     }
#endif
    /* SJM 05-02-10 - since copied either mod splt sym tab or gblk local */
    /* sym tab, know splt sy always set */
    /* DBG remove -- */
    if (ostp->st.snbtsk->tsksyp->spltsy == NULL)
     __misc_terr(__FILE__, __LINE__);
    /* -- */
    /* know task copied and old sy points to new - new el is new task */
    nsyp = ostp->st.snbtsk->tsksyp->spltsy;

    nstp->st.snbtsk = nsyp->el.etskp;
    nsyp->el.etskp->st_namblkin = nstp;
   }
   break;
  case S_UNBLK:
   nstp->st.sbsts = __copy_lstofsts(ostp->st.sbsts);
   break;
  case S_UNFJ:
   { 
    int32 fji, num_fji;
    struct st_t *ofjstp;

    /* first count number of statements in fj */
    for (num_fji = 0;; num_fji++)
     { if (ostp->st.fj.fjstps[num_fji] == NULL) break; }

    nstp->st.fj.fjstps = (struct st_t **)
     __my_malloc((num_fji + 1)*sizeof(struct st_t *));
    nstp->st.fj.fjlabs = (int32 *) __my_malloc((num_fji + 1)*sizeof(int32));

    /* know fork-join will always have at least 1 statement (maybe null) */
    /* also if labeled it will be surrounded by named block */
    for (fji = 0;; fji++)
     {
      if ((ofjstp = ostp->st.fj.fjstps[fji]) == NULL) break;
      nstp->st.fj.fjstps[fji] = __copy_lstofsts(ofjstp);

      /* code gen label unused here but still copy */
      nstp->st.fj.fjlabs[fji] = ostp->st.fj.fjlabs[fji];
     }
    nstp->st.fj.fjstps[num_fji] = NULL;
    nstp->st.fj.fjlabs[num_fji] = -1;
   }
   break;
  case S_FUNCCALL:
  case S_TSKCALL:
   /* find new task through old to new symbol */
   /* for system tasks since points to itself gets same (right) sym */
   nstp->st.stkc.tsksyx = __copy_expr(ostp->st.stkc.tsksyx);
   nstp->st.stkc.targs = __copy_expr(ostp->st.stkc.targs);

   /* field for pli tasks filled during prep */
   nstp->st.stkc.tkcaux.trec = NULL;
   break;
  case S_QCONTA:
   {
    /* SJM 06/23/02 - now aneed more room in qcont stmt specific area */
    struct qconta_t *nqcafs;

    nqcafs = (struct qconta_t *) __my_malloc(sizeof(struct qconta_t));

    nstp->st.sqca = nqcafs;
    nstp->st.sqca->qcatyp = ostp->st.sqca->qcatyp;
    nstp->st.sqca->regform = ostp->st.sqca->regform;
    nstp->st.sqca->qclhsx = __copy_expr(ostp->st.sqca->qclhsx);
    nstp->st.sqca->qcrhsx = __copy_expr(ostp->st.sqca->qcrhsx);
    /* lst of dce lists field nil until near end of prep */
    nstp->st.sqca->rhs_qcdlstlst = NULL;
   }
   break;
  case S_QCONTDEA:
   nstp->st.sqcdea.qcdatyp = ostp->st.sqcdea.qcdatyp;
   nstp->st.sqcdea.regform = ostp->st.sqcdea.regform;
   nstp->st.sqcdea.qcdalhs = __copy_expr(ostp->st.sqcdea.qcdalhs);
   break;
  case S_CAUSE:
   /* must copy expr. even though know just event name */
   nstp->st.scausx = __copy_expr(ostp->st.scausx);
   break;
  case S_DSABLE:
   nstp->st.sdsable.dsablx = __copy_expr(ostp->st.sdsable.dsablx);
   nstp->st.sdsable.func_nxtstp = NULL;
   break;
  case S_INC: case S_DEC: 
   nstp->st.spra.lhsx = __copy_expr(ostp->st.spra.lhsx);
   break;
  case S_BREAK: case S_CONTINUE: case S_RETURN: break;
  /* name resolving statement type no. */
  default: __case_terr(__FILE__, __LINE__);
 }
 return(nstp);
}

/*
 * copy a statement list (linked list of statements)
 */
extern struct st_t *__copy_lstofsts(struct st_t *ostp)
{
 struct st_t *nstp_hdr, *nstp, *last_nstp;

 nstp_hdr = NULL;
 for (last_nstp = NULL; ostp != NULL; ostp = ostp->stnxt)
  {
   nstp = __copy_stmt(ostp);
   if (last_nstp == NULL) nstp_hdr = nstp; else last_nstp->stnxt = nstp;
   nstp->stnxt = NULL;
   last_nstp = nstp;
  }
 return(nstp_hdr);
}

/*
 * copy a list of ialst blocks
 */
static struct ialst_t *copy_ialst(struct ialst_t *oialp)
{
 struct ialst_t *nialp, *last_nialp, *nialst_hdr;
 
 nialst_hdr = NULL;
 for (last_nialp = NULL; oialp != NULL; oialp = oialp->ialnxt)
  {
   nialp = (struct ialst_t *) __my_malloc(sizeof(struct ialst_t));
   *nialp = *oialp; 
   /* notice here initial/always exactly 1 statement, for always 2nd loop */
   /* back added during prep. */
   nialp->iastp = __copy_lstofsts(oialp->iastp);
   nialp->ialnxt = NULL;

   if (last_nialp == NULL) nialst_hdr = nialp;
   else last_nialp->ialnxt = nialp;
   last_nialp = nialp;
  }
 return(nialst_hdr);
}

/*
 * copy the case item list
 * notice in common case of no default, pass nil - returns nil
 *
 * this copies default which is first too
 */
static struct csitem_t *copy_csitemlst(struct csitem_t *ocsip)
{
 struct csitem_t *ncsip, *ncsip_hdr, *last_ncsip;

 ncsip_hdr = NULL;
 for (last_ncsip = NULL; ocsip != NULL; ocsip = ocsip->csinxt)
  {
   ncsip = __alloc_csitem();
   if (last_ncsip == NULL) ncsip_hdr = ncsip; else last_ncsip->csinxt = ncsip;
   ncsip->csixlst = copy_xprlst(ocsip->csixlst);
   if (ocsip->csist == NULL) ncsip->csist = NULL; 
   else ncsip->csist = __copy_lstofsts(ocsip->csist);
   ncsip->csinxt = NULL;
   last_ncsip = ncsip;
  }
 return(ncsip_hdr);
}

/*
 * copy an expression list
 */
static struct exprlst_t *copy_xprlst(struct exprlst_t *oxplp)
{
 struct exprlst_t *xplp;
 struct exprlst_t *nxplp_hdr, *nxplp, *last_nxplp;

 nxplp_hdr = NULL;
 for (last_nxplp = NULL, xplp = oxplp; xplp != NULL; xplp = xplp->xpnxt)
  {
   nxplp = __alloc_xprlst();
   if (last_nxplp == NULL) nxplp_hdr = nxplp; else last_nxplp->xpnxt = nxplp;
   nxplp->xp = __copy_expr(xplp->xp);
   last_nxplp = nxplp;
#ifdef __XPROP__ 
   nxplp->num_xmatch = xplp->num_xmatch;
#endif
  }
 return(nxplp_hdr);
}

/*
 * copy an expression
 * this must deal with ID and symbol and globals (or need 2nd vers.)
 * update expression nodes to point to new modules symbols not old
 * if needed, caller must free src
 *
 */
extern struct expr_t *__copy_expr(struct expr_t *src)
{
 struct expr_t *dst, *xp2, *xp3, *last_next_ndx, *next_ndx_hd; 
 struct sy_t *syp;
 struct gref_t *dgrp, *sgrp;

 /* loops can have null expr. slots */
 if (src == NULL) return(NULL);

 /* SJM 01-19-09 - next ndx on bsel ru.x so must copy and pt with hdr */
 /* and then put back at end since all of dst node over-written in copy */
 next_ndx_hd = NULL;
 if (src->next_ndx != NULL) 
  {
   last_next_ndx = NULL;
   for (xp2 = src->next_ndx; xp2 != NULL; xp2 = xp2->next_ndx)
    {
     xp3 = __copy_expr(xp2);
     if (last_next_ndx == NULL) next_ndx_hd = xp3;
     else last_next_ndx->next_ndx = xp3;
     last_next_ndx = xp3;

     xp3->next_ndx = NULL;
    }
  }

 dst = __alloc_newxnd();
 /* think long constant values can be shared but for now copying */
 /* copy of number node does node body including type copy */
 switch (src->optyp) {
  case NUMBER: case REALNUM:
   /* for non IS form constants can share (use same pointer) */
   *dst = *src;
   break;
  case ISNUMBER: case ISREALNUM:
   *dst = *src;
#ifdef __XPROP__
   /* AIV 07/30/11 - if compiled sim may need to copy in ISNUM expression */
   /* this was a problem for x-prop stmt/expr code copy new expr not */
   /* AIV 10/25/11 - this only true for xprop2 - xprop no longer needed */
   if (__compiled_sim && __xprop2)
    {
     __add_isnum_to_tree((void *) dst, src->ru.xvi, src->szu.xclen);
    }
#endif
   /* 2 cases - if splitting - IS forms impossible else can't share con tab */
//SJM? 01-08-09 - CHECKME??? - during image copy, can IS forms occur
   if (__splitting || __confunc_copying || __genblk_copying)
    {
     __misc_terr(__FILE__, __LINE__);
    }
   break;
  case ID:
   /* must point new modules symbol - nothing points back */
   *dst = *src;
   /* if not splitting a module, copy has same symbol */
   /* SJM 02-18-09 - for confunc image copy, need image copying flag on */
   if (__splitting || __confunc_copying)
    {
     syp = src->lu.sy;
     /* for system tasks/functions copied symbol is same as original */
     if (syp->sytyp != SYM_STSK && syp->sytyp != SYM_SF
      && syp->synam[0] != '$')
      {
       /* AIV 05/25/11 - if this is a parameter from outside constant func */
       /* this will not and shouldn't be set just use module level param */
       /* symbol */
       if (syp->spltsy != NULL) 
        {
         dst->lu.sy = syp->spltsy;
        }
      }
    }
   /* SJM 03-20-09 - for gen (blk) copying - only use split sym for */
   /* gen blk sym tab */
   else if (__genblk_copying)
    {
     syp = src->lu.sy;
     if (syp->sy_in_genblk) 
      {
       /* DBG remove -- */
       if (syp->spltsy == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       dst->lu.sy = syp->spltsy;
      }
//SJM? 03-20-09 - LOOKATME - if previous mod splitting spltsy not reset????
//SJM? 03-20-09 - only change symbol for gen blk var decls - in genblk sytab */
    }
   break;
  case XMRID:
   /* LOOKATME - copying pointers to make sure no shared storage */
   /* but since both read only maybe do not need to */
   *dst = *src;
   /* DBG remove ---*/
   if (src->ru.qnchp == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   dst->ru.qnchp = __pv_stralloc(src->ru.qnchp);
   break;
  case GLBREF:
   /* need to copy only top level expr because global already copied */
   /* LOOKATME - if not splitting gref point to original not copied gxndp */
   /* since not really copying gref think this must work - i.e. not using */
   *dst = *src;
   /* know symbol points to old gref entry - this sets new copied gref */
   /* and expr. cross linking */
   /* DBG remove -- */
   /* --- */
   if (__splitting || __confunc_copying || __genblk_copying)
    {
     sgrp = src->ru.grp;

     /* SJM 09-03-11 - now for defparams do not need to set dest grp */
     /* defparam copy caller sets */
     if (sgrp != NULL && sgrp->gr_defparam) 
      {
       dst->ru.grp = NULL;  
       break;
      }

     if (sgrp == NULL) dst->ru.grp = NULL; 
     else
      {
       /* SJM 03-22-11 - splitting gened insts, down split type may not */
       /* have xmr in gen blk - if not normal xmr copyng case */
       /* notice that there may both be xmrs in gen blocks and not so */
       /* must check the actual XMR */
//SJM 03-22-11 - LOOKATME - ok rooted xmr for gened module - wrong other places
       if (__cur_cntxt_gblk != NULL && __cur_cntxt_gblk->gblk_has_grefs
        && sgrp->gr_gblk_in != NULL)
        {
         /* this is new (dst) gen blk expr copying in  - src grp is old */
         /* dst grp is new */  
         /* this dies if can't find */
         dgrp = match_in_new_gblk_ogref(sgrp, __cur_cntxt_gblk);
        }
       else
        {
         /* DBG remove -- */
         if (__genblk_copying) __misc_terr(__FILE__, __LINE__);
         /* --- */
         dgrp = match_in_new_mod_ogref(sgrp, __inst_mod);    
        }
//SJM 03-30-10 - think?? cases where the gref does not exist - die for now */
       dst->ru.grp = dgrp;
       /* also link dest. group entry expr. ID node ptr to new node */
       dgrp->gxndp = dst;

       /* do not need to set lu.sy since later global name resolution sets */
       /* to target in some other part of design */
      }
    }
   break;
  case FCALL:
   *dst = *src;
   if (src->lu.x != NULL) dst->lu.x = __copy_expr(src->lu.x);
   if (src->ru.x != NULL) dst->ru.x = __copy_expr(src->ru.x);
   /* AIV 03/28/07 - when copying expr need to copy expression to the */
   /* syscall expression tree */
   /* AIV FIXME - should be building tree at prep time ????? */
   if (__compiled_sim) 
    {
     syp = dst->lu.x->lu.sy;
     /* symbol can be NULL here if it is a fcall look above under ID */
     if (syp == NULL) __add_expr_totable(dst);
     else if (syp->sytyp == SYM_SF) __add_expr_totable(dst);
    }
   break;
  default:
   /* know this is a operator node */
   /* must copy all contents - need optyp, rest mostly recomputed */
   *dst = *src;

   if (src->lu.x != NULL) dst->lu.x = __copy_expr(src->lu.x);
   if (src->ru.x != NULL) dst->ru.x = __copy_expr(src->ru.x);
 }
 dst->next_ndx = next_ndx_hd;
 return(dst);
}
 
/*
 * copy an expressions - special version for xform and vpi 
 * that does not count in size of expr table
 */
extern struct expr_t *__sim_copy_expr(struct expr_t *src)
{
 int32 sav_stnum, sav_exprnum;
 struct expr_t *dst;

 sav_stnum = 0;
 sav_exprnum = 0;
 /* AIV 03/26/07 - removed mexpr table from xform - now only time it is */
 /* loaded is for system functions */
 if (__inst_mod != NULL)
  {
   sav_stnum = __inst_mod->mstnum;
  }
   
 dst = __copy_expr(src);

 if (__inst_mod != NULL)
  {
   __inst_mod->mstnum = sav_stnum;
  }
 return(dst);
}

/*
 * find a new gref given an old gref and the new containing gen blk it 
 * was used in
 *
 * sjm 03-30-10 - can't use old to new pointers that are over written for
 * each copy for gen blks because copying done during expand with a gen
 * for capable of being copied to many gen blk (from gen for say)
 * using the same algorithm for mod copies (see next routine)
 */  
static struct gref_t *match_in_new_gblk_ogref(struct gref_t *ogrp,
 struct genblk_t *ngblkp)
{
 struct genitem_t *gip;
 struct gref_t *ngrp;

 /* SJM 08-31-11 - with new separate defparam grefs area - now need to */
 /* search in different tab for defparams */
 /* DBG remove -- */
 if (ogrp->gr_defparam) __misc_terr(__FILE__, __LINE__);
 /* -- */

 for (gip = ngblkp->gref_gitems; gip != NULL; gip = gip->geninxt)
  {
   ngrp = gip->giu.gi_grp; 
   if (ngrp->new_to_old_grp == ogrp) return(ngrp);
  }
 /* must always find */
 __misc_terr(__FILE__, __LINE__);
 return(NULL);
}

/*
 * find a new gref given an old gref and the containing new mod it was
 * in the mod's gref tab for
 *
 * sjm 03-30-10 - can't use old to new pointers that are over written for
 * each copy for gen blks because copying done during expand with a gen
 * for capable of being copied to many gen blk (from gen for say)
 * using the same algorithm for mod copies (see next routine)
 */  
static struct gref_t *match_in_new_mod_ogref(struct gref_t *ogrp,
 struct mod_t *nmdp)
{
 int32 gri;
 struct gref_t *ngrp;

 ngrp = &(nmdp->mgrtab[0]);
 for (gri = 0; gri < nmdp->mgrnum; gri++, ngrp++)
  {
   if (ngrp->new_to_old_grp == ogrp) return(ngrp);
  }
 /* must always find */
 __misc_terr(__FILE__, __LINE__);
 return(NULL);
}

/*
 * ROUTINES TO COPY GREFS
 */

/*
 * routine to go through an old (src) gen blk gref list and find the
 * gen blk that corresponds
 */

/*
 * copy module's global list (now only has XMR grefs not defparam)
 *
 * must copy grefs before copying any expression so can link new expr
 * to new global
 */
static void copy_mgrefs(void)
{
 int32 gri, num_grefs;
 struct gref_t *ogrp, *ngrp;

 if (__oinst_mod->mgrnum != 0)
  { 
   num_grefs = __oinst_mod->mgrnum;
   __inst_mod->mgrtab = (struct gref_t *)
    __my_malloc(num_grefs*sizeof(struct gref_t));

   ogrp = &(__oinst_mod->mgrtab[0]);
   ngrp = &(__inst_mod->mgrtab[0]);
   for (gri = 0; gri < __oinst_mod->mgrnum; gri++, ogrp++, ngrp++)
    {
     copy_1xmr_gref_flds(ngrp, ogrp);
    }
  }  
 /* SJM 09-03-11 - no more gref tab for defps, just alloc - dfp pts to */
}

/*
 * copy 1 gref guts - operation depends on type (processing state) of gref
 * copies from 2nd ogrp to new ngrp 
 *
 * notice copying done before xmr resolution - so only need to copy
 * things that determine where appears 
 *
 * SJM 04-01-10 - this does not need __cur cntxt gblk set
 */
static void copy_1xmr_gref_flds(struct gref_t *ngrp, struct gref_t *ogrp)
{ 
 /* DBG remove -- */
 if (ogrp->targmdp != NULL) __misc_terr(__FILE__, __LINE__);
 if (ogrp->targtskp != NULL) __misc_terr(__FILE__, __LINE__);
 /* ---*/ 

 *ngrp = *ogrp; 
 ngrp->gnam = __pv_stralloc(ogrp->gnam);

 /* SJM 01-13-09 this was bug when tried to copy - this is the back ptr to */
 /* the expr. that is cross linked (to and back) with this gref */
 /* here leave uncopied - when the new mod (dest) gxndp copied, will be set */
 ngrp->gxndp = NULL;

 /* need to copy global path because later folding inst/gate array selects */
 ngrp->glbref = __copy_expr(ogrp->glbref);

 /* SJM 01-18-09 now separate field from old to new while copying sym tabs */
 /* link new sy tab to correspond old mod sym tab - stored in n head for now */
 /* SJM 04-11-10 for copying grefs in gen blks new (cur cntxt) gblk */
 /* is the sym tab needs to start from (the one it is in) */
 if (__cur_cntxt_gblk != NULL)
  {
   ngrp->grsytp = __cur_cntxt_gblk->gblk_sytab;
  }
 else ngrp->grsytp = ogrp->grsytp->linkto_cp_osytp;

 /* targ module and task set during XMR resolution */ 
 ngrp->gin_mdp = __inst_mod; 

 /* targu and targ symbol set way after copy (both types) */
 /* grcmps always nil during copy since copy finished before resolution */
 /* DBG remove --- */
 if (ogrp->targu.targitp != NULL) __misc_terr(__FILE__, __LINE__);
 if (ogrp->grcmps != NULL) __misc_terr(__FILE__, __LINE__);
 if (ogrp->grxcmps != NULL) __misc_terr(__FILE__, __LINE__);
 if (ogrp->last_gri != -1) __misc_terr(__FILE__, __LINE__);
 /* ---*/

 /* SJM 03-13-10 - must not copy xmr cmp fields since must be rebuild (for */
 /* gen loop) or build after all copying fixed - can't copy because need */
 /* all the cross hierarchy gref info first */
 /* DBG remove --- */
 if (ogrp->gr_xmptab != NULL || ogrp->gr_num_xmps != 0) 
  __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* when copying a gen blk there will be cur gen blk cntxt, use it */
 ngrp->gr_gblk_in = __cur_cntxt_gblk;

 /* this is needed so when expr. copied will point to gref in copied mod */
 /* except not needed for image copying */

 /* SJM 03-30-10 - must always point new to old because one can be copied */
 /* to many for gen for loops say (plus undoing if we add) */
//SJM 03-15-10 - LOOKATME? - shouldn't the ptr be needed for xpnd copy too?
 ngrp->new_to_old_grp = ogrp;
}

/*
 * copy 1 defapram gref guts - copies from 2nd ogrp to new ngrp 
 *  
 * used for both copy dfp gref from gen item and for post resolved grefs
 * malloc and pointed to by defparams during mod copy
 *
 * SJM 09-06-11 - ogrp pointed to (malloced) from defparam after defparam
 * resolution to copied to new split off mod so fields set, except copying
 * to new gref that will be elaborated on next fixup round
 *
 * SJM 09-06-11 - notice during defparam processing ngrp gxndp and defparam
 * lhs expr cross links set
 */
static void copy_1dfp_gref_flds(struct gref_t *ngrp, struct gref_t *ogrp)
{ 
 *ngrp = *ogrp; 
 ngrp->gnam = __pv_stralloc(ogrp->gnam);

 /* need to copy global path because later folding inst/gate array selects */
 ngrp->glbref = __copy_expr(ogrp->glbref);
 /* SJM 09-06-11 - at this point, glbref ru dot grp field set to nil */
 ngrp->gxndp = NULL;

 /* SJM 01-18-09 now separate field from old to new while copying sym tabs */
 /* link new sy tab to correspond old mod sym tab - stored in n head for now */
 /* SJM 04-11-10 for copying grefs in gen blks new (cur cntxt) gblk */
 /* is the sym tab needs to start from (the one it is in) */
 if (__cur_cntxt_gblk != NULL)
  {
   ngrp->grsytp = __cur_cntxt_gblk->gblk_sytab;
  }
 else ngrp->grsytp = ogrp->grsytp->linkto_cp_osytp;

 /* targ module and task set during XMR resolution */ 
 /* SJM 09-06-11 - new inst mod set for both gen item xpnd and mod split copy*/ 
 ngrp->gin_mdp = __inst_mod; 

 ogrp->targu.targitp = NULL;
 ogrp->grcmps = NULL;
 ogrp->grxcmps = NULL;
 ogrp->last_gri = -1;
 ogrp->gr_xmptab = NULL;
 ogrp->gr_num_xmps = 0;

 /* when copying a gen blk there will be cur gen blk cntxt, use it */
 ngrp->gr_gblk_in = __cur_cntxt_gblk;
}

/*
 * copy specify section if old has specify
 */
static void copy_specify(void)
{
 struct spfy_t *ospfyp, *nspfyp;

 /* first allocate new module's specify section */
 ospfyp = __oinst_mod->mspfy;
 nspfyp = (struct spfy_t *) __my_malloc(sizeof(struct spfy_t));
 /* AIV 06/08/06 - need to do copy of old to new */
 *nspfyp = *ospfyp;
 __inst_mod->mspfy = nspfyp;
 /* if has symbol table for specparams copy */
 /* this will link old specparams to new */ 
 if (ospfyp->spfsyms != NULL) nspfyp->spfsyms = copy_1symtab(ospfyp->spfsyms);
 /* copy parameters */
 nspfyp->msprms = copy_params(ospfyp->msprms, ospfyp->sprmnum, SPECIFY);
 copy_spcpths(ospfyp, nspfyp);
 copy_timchks(ospfyp, nspfyp);
}

/*
 * copy list of specify paths (port to port delay paths)
 */
static void copy_spcpths(struct spfy_t *ospfyp, struct spfy_t *nspfyp)
{
 struct spcpth_t *npthp, *opthp, *last_npthp, *npthp_hdr;
 struct sy_t *syp;

 last_npthp = NULL;
 npthp_hdr = NULL;
 for (opthp = ospfyp->spcpths; opthp != NULL; opthp = opthp->spcpthnxt)
  {
   npthp = (struct spcpth_t *) __my_malloc(sizeof(struct spcpth_t));
   /* for path this copies most of fields (part of packed constants) */
   *npthp = *opthp;
   /* must link copied symbol */
   syp = opthp->pthsym->spltsy;
   npthp->pthsym = syp;
   syp->el.epthp = npthp;

   /* copy the path input and and path output that is here a cast expr list */
   npthp->peins = (struct pathel_t *)
    copy_xprlst((struct exprlst_t *) opthp->peins);
   npthp->peouts = (struct pathel_t *)
    copy_xprlst((struct exprlst_t *) opthp->peouts);

   /* copy the optional conditional path fields */
   npthp->datasrcx = __copy_expr(opthp->datasrcx);
   npthp->pthcondx = __copy_expr(opthp->pthcondx);

   /* copy the delay list - always CMPLST and can be long (up to 12?) */
   npthp->pth_du.pdels = __copy_dellst(opthp->pth_du.pdels);

   /* finally, link on end */ 
   npthp->spcpthnxt = NULL;
   if (last_npthp == NULL) npthp_hdr = npthp;
   else last_npthp->spcpthnxt = npthp;

   npthp->spcpth_id = -1;

   last_npthp = npthp;
  }
 nspfyp->spcpths = npthp_hdr;
}

/*
 * copy timing checks 
 */
static void copy_timchks(struct spfy_t *ospfyp, struct spfy_t *nspfyp)
{
 struct tchk_t *ntcp, *otcp, *last_ntcp, *ntcp_hdr;

 last_ntcp = NULL;
 ntcp_hdr = NULL;
 for (otcp = ospfyp->tchks; otcp != NULL; otcp = otcp->tchknxt)
  {
   ntcp = copy1_tchk(otcp);
   /* finally, link on end */ 
   ntcp->tchknxt = NULL;
   if (last_ntcp == NULL) ntcp_hdr = ntcp; else last_ntcp->tchknxt = ntcp;
   last_ntcp = ntcp;
  }
 nspfyp->tchks = ntcp_hdr;
}

/*
 * copy 1 timing check 
 * notice here hold half of setuphold not yet copied
 */
static struct tchk_t *copy1_tchk(struct tchk_t *otcp)
{
 struct tchk_t *ntcp;
 struct sy_t *syp;

 ntcp = (struct tchk_t *) __my_malloc(sizeof(struct tchk_t));
 /* this copies flags */
 *ntcp = *otcp;
 syp = otcp->tcsym->spltsy;
 ntcp->tcsym = syp;
 syp->el.etcp = ntcp;

 if (otcp->startxp != NULL) ntcp->startxp = __copy_expr(otcp->startxp);
 if (otcp->startcondx != NULL)
  ntcp->startcondx = __copy_expr(otcp->startcondx);
 if (otcp->chkxp != NULL) ntcp->chkxp = __copy_expr(otcp->chkxp);
 if (otcp->chkcondx != NULL) ntcp->chkcondx = __copy_expr(otcp->chkcondx);

 /* know 1st delay limit always required - always CMPLST here */
 ntcp->tclim_du.pdels = __copy_dellst(otcp->tclim_du.pdels);
 if (otcp->tc_haslim2) 
  ntcp->tclim2_du.pdels = __copy_dellst(otcp->tclim2_du.pdels);
 else ntcp->tclim2_du.pdels = NULL;

 /* at this point, if present, ntfy_np is a sy_t */ 
 if (otcp->ntfy_np == NULL) ntcp->ntfy_np = NULL;
 else
  {
   syp = (struct sy_t *) otcp->ntfy_np;
   /* old symbols always have splt sym link to new */
   syp = syp->spltsy;
   ntcp->ntfy_np = (struct net_t *) syp;  
  }
 return(ntcp);
}

/*
 * ROUTINES TO COPY GENERATE CONSTRUCTS
 */

/*
 * copy a list of gen items
 *
 * uses normal copy pattern of expecting old module in __oinst_mod
 * and copying into __inst_mod (caller must have set these)
 * 
 * SJM 03-20-09 - this can be called from mod split copy (__splitting on)
 * or from gen item expand copy
 */  
static struct genitem_t *copy_genitem_lst(struct genitem_t *ogip_hd,
 struct genblk_t *par_gblkp)
{
 struct genitem_t *ogip, *ngip, *last_ngip, *ngip_hd;

 ngip_hd = NULL;
 last_ngip = NULL;
 for (ogip = ogip_hd; ogip != NULL; ogip = ogip->geninxt)
  {
   ngip = __alloc_init_new_genitem(ogip->gityp);
   copy1_genitem(ngip, ogip, par_gblkp);

   if (last_ngip == NULL) ngip_hd = ngip;
   else last_ngip->geninxt = ngip;
   last_ngip = ngip;
  }
 return(ngip_hd);
}

/*
 * routine to copy one generate item
 *
 * SJM 03-20-09 - this can be called from mod split copy (__splitting on)
 * or from gen item expand copy
 */  
static struct genitem_t *copy1_genitem(struct genitem_t *ngip,
 struct genitem_t *ogip, struct genblk_t *par_gblkp)
{
 struct inst_t *nip, *oip;
 struct gate_t *ngp, *ogp;
 struct gref_t *ngrp, *ogrp;
 struct mod_t *imdp;

 ngip->gityp = ogip->gityp;
 switch (ogip->gityp) {
  case GI_GFOR:
   ngip->giu.gi_gforp = copy1_genfor(ogip, par_gblkp);
   break;
  case GI_GIF:
   ngip->giu.gi_gifp = copy1_genif(ogip, par_gblkp);
   break;
  case GI_GCASE:
   ngip->giu.gi_gcasp = copy1_gencase(ogip, par_gblkp);
   break;
  case GI_VARDECL:
   ngip->giu.gi_np = copy1_gen_vardecl(ogip, par_gblkp);
   break;
  case GI_INITALW:
   ngip->giu.gi_ialp = copy1_gen_initalw(ogip);
   break;
  case GI_CONTA:
   ngip->giu.gi_cap = copy1_gen_conta(ogip);
   break;
  case GI_INST:
   /* SJM 03-03-09 - now when copy only see gen item as inst or prim not cell */
   nip = (struct inst_t *) __my_malloc(sizeof(struct inst_t));
   oip = ogip->giu.gi_igp->ip;
   /* use split sy here - does not copy src per inst hiconn src locs */
   copy_1inst(nip, oip);
   /* need to copy the giap record - know just one not expanded */
   if (oip->i_giap != NULL)
    {
     /* DBG remove --- */
     if (oip->i_giap->gia_xpnd) __misc_terr(__FILE__, __LINE__);
     /* -- */
     __copy1_inst_gia_rec(nip, oip->i_giap);
     nip->i_giap->gia_base_syp = oip->i_giap->gia_base_syp;
    }

   /* SJM 03-06-09 - need 2 fields for gen inst items - so must alloc */
   ngip->giu.gi_igp = (struct inst_gen_t *)
    __my_malloc(sizeof(struct inst_gen_t));
   ngip->giu.gi_igp->ip = nip;
   if (ogip->giu.gi_igp->srclocp == NULL) ngip->giu.gi_igp->srclocp = NULL;
   else
    {
     imdp = nip->imsym->el.emdp;
     /* SJM 03-12-09 - wrong - need to copy inst's mod's num pins src locs */
     /* since may be copies gen item into new mod, must alloc src loc */
     ngip->giu.gi_igp->srclocp = (struct srcloc_t *)
      __my_malloc(imdp->mpnum*sizeof(struct srcloc_t));
     memcpy(ngip->giu.gi_igp->srclocp, ogip->giu.gi_igp->srclocp,
      imdp->mpnum*sizeof(struct srcloc_t));
    }
   break;
  case GI_GATE:
   ngp = (struct gate_t *) __my_malloc(sizeof(struct gate_t));
   ogp = ogip->giu.gi_gp;
   copy_1gate(ngp, ogp);

   /* need to copy the giap record - know just one not expanded */
   if (ogp->g_giap != NULL)
    {
     /* DBG remove --- */
     if (ogp->g_giap->gia_xpnd) __misc_terr(__FILE__, __LINE__);
     /* -- */
     __copy1_gate_gia_rec(ngp, ogp->g_giap);
     ngp->g_giap->gia_base_syp = ogp->g_giap->gia_base_syp;
    }

   ngip->giu.gi_gp = ngp;
   break;
  case GI_GREF:
   ngrp = (struct gref_t *) __my_malloc(sizeof(struct gref_t));
   ogrp = ogip->giu.gi_grp;

   /* no need to init, this sets all fields */
   /* SJM 03-30-10 - know this copy always sets the nxt ptr in new to nil */
   copy_1xmr_gref_flds(ngrp, ogrp);

   /* SJM 04-06-10 - new to old copied in copy 1 gref fields now */
   /* SJM 04-11-10 - all the gref fields even for in gen blks copied */
   /* when fields copied now */

   /* SJM 04-01-10 - need to set the gen item gref after copying guts */
// dfp lhs expr not expanded (copied) into gen ptr so can use new in old
// ==> copy 10 grefs because for has 10 blocks, there needs to be, 10 defparms 
// -- each gen for block needs its own downward relative defparam - how get
//    so many
   /* SJM 09-06-11 - new gref has all info but possible to late mv many */
   /* grefs from gen blk into different instantiated gen blocks (say gen for) */
   /* know only down into gen blks allowed (can't ref into non gened code - */
   /* obviously because grefs and glb ref exprs need to be 1-to-1 */
   ngip->giu.gi_grp = ngrp;
   break;
  case GI_DFPARM:
   ngip->giu.gi_dfp = __copy1_defparam(ogip->giu.gi_dfp);
   break;
  case GI_GBLK:
   /* if mod copy splitting need image copy else gen blk xpnd copy */
   if (__splitting)
    {
     ngip->giu.gi_gblkp = image_copy1_genblk(ogip->giu.gi_gblkp, par_gblkp);
    } 
   else
    {
     ngip->giu.gi_gblkp = __xpnd_copy1_genblk(ogip->giu.gi_gblkp, NULL, -1);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 /* expanded gen item field must be nil - used by gen xpnd - freed by gather */
 return(ngip);
}

/*
 * copy 1 generate for
 *
 * SJM 03-20-09 - this can be called from mod split copy (__splitting on)
 * or from gen item expand copy
 *
 * SJM 03-20-09 - notice do not need gen for index here since not gentab
 */
static struct gen_for_t *copy1_genfor(struct genitem_t *ogip,
 struct genblk_t *par_gblkp)
{
 struct gen_for_t *ogforp, *ngforp;

 ogforp = ogip->giu.gi_gforp;
 ngforp = (struct gen_for_t *) __my_malloc(sizeof(struct gen_for_t));
 *ngforp = *ogforp;
 ngforp->gforassgn = __copy_stmt(ogforp->gforassgn);
 ngforp->gfortermx = __copy_expr(ogforp->gfortermx);
 ngforp->gforinc = __copy_stmt(ogforp->gforinc);

 /* if mod copy splitting need image copy else gen blk xpnd copy */
 if (__splitting)
  { 
   ngforp->src_gforblkp = image_copy1_genblk(ogforp->src_gforblkp, par_gblkp);
  }
 else
  { 
   ngforp->src_gforblkp = __xpnd_copy1_genblk(ogforp->src_gforblkp, NULL, -1);
  }
 /* SJM 04-05-11 - now keeping gentab around so old one will exist */
 /* works since just leaks memory and gets over written */
 return(ngforp);
}

/*
 * copy 1 generate if
 *
 * SJM 03-20-09 - this can be called from mod split copy (__splitting on)
 * or from gen item expand copy
 */
static struct gen_if_t *copy1_genif(struct genitem_t *ogip,
 struct genblk_t *par_gblkp)
{
 struct gen_if_t *ogifp, *ngifp;

 ogifp = ogip->giu.gi_gifp;
 ngifp = (struct gen_if_t *) __my_malloc(sizeof(struct gen_if_t));
 *ngifp = *ogifp;

 ngifp->condx = __copy_expr(ogifp->condx);

 /* if mod copy splitting need image copy else gen blk xpnd copy */
 if (__splitting)
  {
   ngifp->src_then_gblkp = image_copy1_genblk(ogifp->src_then_gblkp,
    par_gblkp);
  }
 else
  {
   ngifp->src_then_gblkp = __xpnd_copy1_genblk(ogifp->src_then_gblkp, NULL, -1);
  }

 if (ogifp->src_else_gblkp == NULL) ngifp->src_else_gblkp = NULL;
 else
  {
   /* if mod copy splitting need image copy else gen blk xpnd copy */
   if (__splitting)
    {
     ngifp->src_else_gblkp = image_copy1_genblk(ogifp->src_else_gblkp,
      par_gblkp);
    }
   else
    {
     ngifp->src_else_gblkp = __xpnd_copy1_genblk(ogifp->src_else_gblkp,
      NULL, -1);
    }
  }
 return(ngifp);
}

/*
 * copy 1 generate case
 */
static struct gen_case_t *copy1_gencase(struct genitem_t *ogip,
 struct genblk_t *par_gblkp)
{
 struct gen_case_t *ogcasp, *ngcasp;
 struct gen_csitem_t *last_gcsip, *ngcsip, *ogcsip; 

 ogcasp = ogip->giu.gi_gcasp;
 ngcasp = (struct gen_case_t *) __my_malloc(sizeof(struct gen_case_t));
 *ngcasp = *ogcasp;
 ngcasp->csx = __copy_expr(ogcasp->csx);

 last_gcsip = NULL;
 for (ogcsip = ogcasp->gcsitems; ogcsip != NULL; ogcsip = ogcsip->gcsinxt)
  {
   ngcsip = copy1_csitem(ogcsip, par_gblkp);

   if (last_gcsip == NULL) ngcasp->gcsitems = ngcsip;
   else last_gcsip->gcsinxt = ngcsip;
   last_gcsip = ngcsip;
  }
 return(ngcasp);
}

/*
 * routine to copy 1 case item
 *
 * SJM 03-20-09 - this can be called from mod split copy (__splitting on)
 * or from gen item expand copy
 */
static struct gen_csitem_t *copy1_csitem(struct gen_csitem_t *ogcsip,
 struct genblk_t *par_gblkp)
{
 struct gen_csitem_t *ngcsip;

 ngcsip = (struct gen_csitem_t *) __my_malloc(sizeof(struct gen_csitem_t)); 
 *ngcsip = *ogcsip;
 ngcsip->csixlst = copy_xprlst(ogcsip->csixlst);

 /* if mod copy splitting need image copy else gen blk xpnd copy */
 if (__splitting)
  {
   ngcsip->gen_csiblkp = image_copy1_genblk(ogcsip->gen_csiblkp, par_gblkp);
  }
 else
  {
   ngcsip->gen_csiblkp = __xpnd_copy1_genblk(ogcsip->gen_csiblkp, NULL, -1);
  }

 ngcsip->gcsinxt = NULL;

 return(ngcsip);
}

/*
 * copy 1 generate var decl
 *
 * SJM 03-20-09 - all this does now is some checking and return new net
 */
static struct net_t *copy1_gen_vardecl(struct genitem_t *ogip,
 struct genblk_t *par_gblkp)
{
 struct net_t *nnp;
 struct sy_t *osyp, *nsyp;

 /* SJM 03-20-09 - module gen items can't be genvar */
 if (par_gblkp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* need copy of net in case gening many net decls from gen for */
 /* SJM 03-12-09 - this is just gen expanding copy - still pts to same */
 /* mod and same gen blk local symbol for now */
 osyp = ogip->giu.gi_np->nsym;
 nsyp = osyp->spltsy;
 nnp = nsyp->el.enp;

 /* DBG remove */ 
 if (nnp->nsym != nsyp) __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 /* SJM 03-16-09 - not setting syt of net's for copied gen blk sy tabs */ 
 return(nnp);
}

/*
 * copy 1 generate init/always block
 */
//SJM 12-06-08 - can this just do the copy?
static struct ialst_t *copy1_gen_initalw(struct genitem_t *ogip)
{
 struct ialst_t *oialp, *nialp;
 
 oialp = ogip->giu.gi_ialp;
 nialp = copy_ialst(oialp);
 return(nialp);
}

/*
 * copy 1 generate conta
 * simple so just inline copy - do not need separate routine
 */
static struct conta_t *copy1_gen_conta(struct genitem_t *ogip)
{
 struct conta_t *ocap, *ncap;
 struct sy_t *syp;
 
 ocap = ogip->giu.gi_cap;
 ncap = (struct conta_t *) __my_malloc(sizeof(struct conta_t));

 /* when symbol copied old splt sym field pointed to new */
 *ncap = *ocap;
 /* AIV 03/25/09 - compilers need each ca to have unique indentifier */
 if (__compiled_sim) ncap->enter_cndx = ++__cap_seq_no;
 else ncap->enter_cndx = -1;
 syp = ocap->casym->spltsy;
 ncap->casym = syp;
 syp->el.ecap = ncap;

 ncap->ca_du.pdels = __copy_dellst(ocap->ca_du.pdels);
 ncap->lhsx = __copy_expr(ocap->lhsx);
 ncap->rhsx = __copy_expr(ocap->rhsx);

 /* do not need to link on end, since caller links on end of gen item list */

 return(ncap);
}

/*
 * image copy a generate blk
 *
 * for mod split copying, copies and preserves genvar ndx and genv np ptr
 * this pre gen src read form copy
 *
 * ALGORITHM: SJM 03-22-09 - image copy for splitting same as expand copying
 * except image copy parent must be passed from new inst mod instead of
 * being same in expand copy and no tracking of possible gen var values for
 * gen for  
 *
 * CRUCIAL TRICK: copying even for expand always copies all case items and
 * both if branches - so can use same copy for both except for gen blk copy
 *
 * SJM 04-01-10 - this just copies the gen blk bodies (1 for genfor) but
 * all for gen case and gen if, but because gref's now in gen blks need the
 * old (src) gen blk as cur glb gen blk context here to and must save/restore  
 *
 * notice only gen items in gen blks need to have special gen blk/gen item
 * copying
 */
static struct genblk_t *image_copy1_genblk(struct genblk_t *ogblkp,
 struct genblk_t *par_gblkp)
{
 struct genblk_t *ngblkp, *sav_glb_cntxt_gblk;

 /* SJM 03-05-09 - gen blk ndx and gen var must not be set here */
 /* DBG remove -- */
 if (ogblkp->genv_ndx != -1) __misc_terr(__FILE__, __LINE__);
 /* --- */  

 /* SJM 02-02-11 - copying genfor in mod's that need to split are legal */
 /* and gvnp will be set - ignored here - will be fixed later */
 /* REMOVED - if (ogblkp->gvnp != NULL) __misc_terr(__FILE__, __LINE__); */

 /* SJM 04-01-10 - gen blk copying flag must be off here */

 ngblkp = (struct genblk_t *) __my_malloc(sizeof(struct genblk_t));
 *ngblkp = *ogblkp;

 ngblkp->gblknam = __pv_stralloc(ogblkp->gblknam);

 /* when copying gen blk - now copy possible task blk tree of sy tabs */
 ngblkp->gblk_sytab = copy_mod_or_gen_symtabs(ogblkp->gblk_sytab);
 ngblkp->gblk_sytab->sypofsyt = NULL;
 /* SJM 03-18-09 - must explicitly set gblk of gblk's sytab */
 ngblkp->gblk_sytab->gblkofsyt = ngblkp;

 /* SJM 03-29-11 - also need to set new mod, genblk in */
 /* needed because top level mod gen blks need sytab par field nil */ 
 ngblkp->gblk_mod_in = __inst_mod;

 /* SJM 02-16-10 - now upward link to par gblk through gblk's sym tab */
 /* SJM 02-16-10 - but now parents linked through a genblk's sym tab par */
 /* if no context, parent symtab is mod's */
 /* AIV 03-14-10 - only set gblk sytab if par gblkp not nil */
 if (par_gblkp != NULL)
  {
   /* DBG remove -- */
   if (par_gblkp->gblk_sytab == NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   ngblkp->gblk_sytab->sytpar = par_gblkp->gblk_sytab;
  }

 /* SJM 03-22-09 - still need to copy gen blk wires even for image copy */
 /* syms in gen blk sym tab or will miss the implicitly declared nets */
 /* copy wires after gen blk symtab copied */
 copy_gblk_wires(ngblkp, ogblkp);

//SJM 03-30-10 - LOOKATME? does it matter if wires copied first?
/* SJM 03-03-09 - here genv index needs to be -1, only used in gen expand */

 /* SJM 04-11-10 - also need new gen blk context when copying a mod */
 /* so gen blk in and sym tab fields right */
 
 /* SJM 04-10-10 - because of new old to new gref ptrs, must copy gref */
 /* gen items first */
 sav_glb_cntxt_gblk = __cur_cntxt_gblk;
 /* SJM 05-06-10 - this needs to be new gblk copying into */ 
 __cur_cntxt_gblk = ngblkp;

 /* must copy all gblk gref items first - does not need cur cntxt gblk */
 copy_gref_genitems(ogblkp, ngblkp);

 copy_dfp_genitems(ogblkp, ngblkp);

 /* SJM 05-06-10 - when splitting also need to copy all grefs in gen blks */
 /* SJM 05-06-10 - must copy tasks after grefs copied because task calls */
 /* of local tasks in gen blks, will appear as XMRs */
 copy_gblk_tasks(ngblkp, ogblkp);

 ngblkp->gitems = copy_genitem_lst(ogblkp->gitems, ngblkp);

 /* SJM 04-01-01 - restore because need to handle nested gen blks here too */
 __cur_cntxt_gblk = sav_glb_cntxt_gblk;

 return(ngblkp);
}

/*
 * expand copy a generate blk
 *
 * special code for for so that gen var is part of new genblk name
 * and par is same parent as copied from
 *
 * SJM 04-01-10 - expr copying now need old (src) gen blk - since called from
 * here need to set and save the global cur gblk cntxt
 */
extern struct genblk_t *__xpnd_copy1_genblk(struct genblk_t *ogblkp,
 struct net_t *genv_np, int32 ndx)
{
 int32 sav_genblk_copying;
 struct genblk_t *ngblkp, *sav_glb_cntxt_gblk;
 char s1[RECLEN];

 sav_genblk_copying = __genblk_copying;
 __genblk_copying = TRUE;

 ngblkp = (struct genblk_t *) __my_malloc(sizeof(struct genblk_t));
 *ngblkp = *ogblkp;

 if (ndx == -1) strcpy(s1, ogblkp->gblknam);
 else sprintf(s1, "%s[%d]", ogblkp->gblknam, ndx);
 ngblkp->gblknam = __pv_stralloc(s1);

 /* DBG remove -- */
 if (!ogblkp->gblk_sytab->freezes) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* SJM 03-17-09 - this only sets link from old to new symtab */
 /* SJM 05-02-10 - copy task tree of gen blk sy tabs */
 ngblkp->gblk_sytab = copy_mod_or_gen_symtabs(ogblkp->gblk_sytab);
 ngblkp->gblk_sytab->sypofsyt = NULL;
 /* SJM 03-18-09 - must explicitly set gblk of gblk's sytab */
 ngblkp->gblk_sytab->gblkofsyt = ngblkp;

 /* SJM 03-29-11 - also need to set new mod, genblk in */
 /* needed because top level mod gen blks need sytab par field nil */ 
 ngblkp->gblk_mod_in = __inst_mod;

 /* parent symtab is same as in src blk copied from for gen for */
 /* SJM - 10-02-09 - this is guess that parent same as copied from - if not */
 /* caller will fix */
 /* SJM 02-16-10 now linking parents through the gblk's sym tab */
 ngblkp->gblk_sytab->sytpar = ogblkp->gblk_sytab->sytpar;

 /* SJM 03-03-09 - here genv index will to be -1, only used in gen expand */
 /* for gen for only, need the gen for's gen blk's one required genvar */
 /* SJM 03-20-09 - this copy works beause genvars are in mod item sym tab */ 
 ngblkp->gvnp = genv_np;
 ngblkp->genv_ndx = ndx;

//SJM 03-30-10 - LOOKATME? does it matter if wires copied first?

 /* SJM 03-20-09 - var decl and implicit wires must be copied using all */
 /* syms in gen blk sym tab or will miss the implicitly declared nets */
 /* copy wires after gen blk symtab copied */
 copy_gblk_wires(ngblkp, ogblkp);

 /* SJM 04-11-10 - copy dfp genitems copies exprs, so now need gblk cntxt */
 /* copy gen item list needs to run with the newly created (dst) gen blk */
 /* as the context gen blk */
 /* SJM 04-02-11 - this was wrong - need to save the current cntxt */
 /* was wrongly changing ton gblkp */
 sav_glb_cntxt_gblk = __cur_cntxt_gblk;
 /* SJM 05-06-10 - notice this needs to be new copied into context gblk */ 
 __cur_cntxt_gblk = ngblkp;


 /* must copy all gblk gref items before dfps - does not need cur cntxt gblk */

 /* SJM 04-06-10 - by copying grefs in gen blocks first, when the exprs */ 
 /* in normal gen items (init/always say) are copied the gref and the */
 /* expr 1-to-1 cross links are set up right */
 copy_gref_genitems(ogblkp, ngblkp);

 /* SJM 04-11-10 - must also copy the post expand (especiall gen fors) dfps */
 copy_dfp_genitems(ogblkp, ngblkp);

 /* SJM 05-06-10 - must copy tasks after grefs copied because task calls */
 /* of local tasks in gen blks, will appear as XMRs */
 copy_gblk_tasks(ngblkp, ogblkp);

 /* SJM 04-01-10 must copy gen items image copying on and save and restore */
 ngblkp->gitems = copy_genitem_lst(ogblkp->gitems, ngblkp);

 __genblk_copying = sav_genblk_copying;
 __cur_cntxt_gblk = sav_glb_cntxt_gblk;

 return(ngblkp);
}

/*
 * copy genblk's tasks (now all t/f/lb)
 */
static void copy_gblk_tasks(struct genblk_t *ngblkp,
 struct genblk_t *ogblkp)
{
 struct task_t *otskp, *ntskp;
 struct task_t *last_ntskp;

 last_ntskp = NULL;
 
 ngblkp->gblk_tsks = NULL;
 for (otskp = ogblkp->gblk_tsks; otskp != NULL; otskp = otskp->tsknxt)
  {
   ntskp = copy1_task(otskp);

   if (last_ntskp == NULL) ngblkp->gblk_tsks = ntskp;
   else last_ntskp->tsknxt = ntskp;
   last_ntskp = ntskp;
  }
 ngblkp->end_gblk_tsk = last_ntskp;
}

/*
 * copy all nets in a gen blk
 *
 * SJM 03-20-09 - need to copy using same algorithm as mod split copying 
 * - namely, need to go through gen blks sym table and copy all nets
 * needed because no gen vardecl for implicit nets - implicit nets are
 *
 * local to their gen blk as if there were a var (net) decl in the gen blk
 * this does not do changing of sym or net decl bits
 */
static void copy_gblk_wires(struct genblk_t *ngblkp, struct genblk_t *ogblkp)
{
 int32 syi;
 struct symtab_t *nsytp, *osytp;
 struct sy_t **syms, *syp;
 struct net_t *onp, *nnp;

 nsytp = ngblkp->gblk_sytab;
 osytp = ogblkp->gblk_sytab;
 for (syms = osytp->stsyms, syi = 0; syi < (int32) osytp->numsyms; syi++)
  {
   syp = syms[syi];
   if (syp->sytyp != SYM_N) continue;

   onp = syp->el.enp;
   /* param declarations illegal in gen blks */
   /* DBG remove -- */
   if (onp->n_isaparam) __misc_terr(__FILE__, __LINE__);
   /* --- */
   
   nnp = copy_1wire_guts(onp);

   /* when symbol table copied old spltsy field pointed to new */
   /* copying symbol table copies symbols */
   syp = onp->nsym->spltsy;
   nnp->nsym = syp;
   syp->el.enp = nnp;
   /* SJM 05/07/06 - must also set net's containing symtab to new */
   /* SJM 03-03-09 - because of gen now always copy syt of net */
   nnp->syt_of_net = nsytp;

   /* mutual links now separated */
   /* must not change splt sym since still needed by param type regs */
  }
}

/*
 * routine to copy only the gref gen items first since when other gen items
 * copied (or expanded) must have the gref new to old ptrs set
 *
 * copy direct is first arg old to 2nd arg new gblk
 *
 * SJM 04-01-01 - key here is that know gref in gen blks are 1 to 1 with
 * exprs in the same gen blk, i.e. can't be in included gen blk
 */
static void copy_gref_genitems(struct genblk_t *ogblkp,
 struct genblk_t *ngblkp)
{
 struct genitem_t *ogip, *ngip, *last_ngip;

 last_ngip = NULL;
 for (ogip = ogblkp->gref_gitems; ogip != NULL; ogip = ogip->geninxt)
  {
   /* DBG remove -- */
   if (ogip->gityp != GI_GREF) __misc_terr(__FILE__, __LINE__);
   /* -- */
  
   /* copy for gref gitem (actually all) handles the alloc and init */
   ngip = __alloc_init_new_genitem(GI_GREF);
   /* when know gen item is a gref gen item, never need a parent gblk */
   copy1_genitem(ngip, ogip, NULL);

   if (last_ngip == NULL) ngblkp->gref_gitems = ngip;
   else last_ngip->geninxt = ngip;
   last_ngip = ngip;
  }
 /* SJM 04-03-10 - also nee to set the last pointer to new */
 ngblkp->last_gref_gitem = last_ngip;
}

/*
 * routine to copy def paramg gen items 
 * defparams in gen blks have their fields filled later when moved into mod
 *
 * copy direct is first arg old to 2nd arg new gblk
 */
static void copy_dfp_genitems(struct genblk_t *ogblkp, struct genblk_t *ngblkp)
{
 struct genitem_t *ogip, *ngip, *last_ngip;

 last_ngip = NULL;
 for (ogip = ogblkp->dfp_gitems; ogip != NULL; ogip = ogip->geninxt)
  {
   /* DBG remove -- */
   if (ogip->gityp != GI_DFPARM) __misc_terr(__FILE__, __LINE__);
   /* -- */
  
   /* copy for gref gitem (actually all) handles the alloc and init */
   ngip = __alloc_init_new_genitem(GI_DFPARM);
   /* when know gen item is a gref gen item, never need a parent gblk */
   copy1_genitem(ngip, ogip, NULL);

   if (last_ngip == NULL) ngblkp->dfp_gitems = ngip;
   else last_ngip->geninxt = ngip;
   last_ngip = ngip;
  }
 /* SJM 04-11-10 - also nee to set the last pointer to new */
 ngblkp->last_dfp_gitem = last_ngip;
}

//AIV 03-23-10 - LOOKATME
/*
 * ROUTINES TO FREE GENERATE ITEMS 
 */

// ++> free init/always
// ++> free inst
// ++> free gate
// ++> free defparam

// ++> free task/func (when supported) 

// ++> free var decl (maybe leave?)

// ++> when done need to rebuild mod's sym tab - can remove gened ndecl here?

/*
 * routine to free an init always - needed before re-gen fixup nl
 *
 * passed last in list (nil if head) and ptr to one to remove 
 * linked list form so easy except for labeled blocks 
 *
 * SJM 03-23-10 - new algorithm - when have defparams/splitting(?)/pound
 * params in gens, need at leat one more fixup pass, possible that different
 * param values will be set requiring removing gen constructs moved to mod
 * top level
 */
extern void __free1_initalw(struct ialst_t *ialp, struct ialst_t *last_ialp)
{
 // -- st list
 // -- other
 // -- labeled blocks
}

/*
 * free one conta (linked list so easy) - needed by param chg gen repeate undo
 *
 * last cap nil if head of mods list
 */
extern void __free_1conta(struct conta_t *cap, struct conta_t *last_cap)
{
 // what about constructed symbol moved to mod's top level sym tab
}

/*
 * free one gate (this is a tab after cell separate)
 *
 * needed by param chg gen repeate undo
 */
extern void __free_1gate(int32 gi)
{
 // what about constructed symbol moved to mod's top level sym tab
 // what have with gates that instantiate UDPS? - also sym tab problem
}

// __free_1dfparam written and in genfx.c (SJM handles - need to change)

/*
 * GENERATE RELATED DESIGN CHECKING DEBUG ROUTINES
 */

//SJM? 03-01-09 - with new algorithm think can get rid of these

/*
 * routine to check mod sym linking
 */
extern void __dbg_chk_modhdr_list_linking(struct mod_t *mhdrp)
{
 struct mod_t *mdp;

 for (mdp = mhdrp; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->msym->el.emdp != mdp) __misc_terr(__FILE__, __LINE__);
  }
}

/*
 * debug routine to check for correct copying of mod cell pins
 */
extern void __chk_dsgn_cpins(struct mod_t *mhdrp)
{
 struct mod_t *mdp;
 struct cell_t *cp;
 struct cell_pin_t *cpp;

 for (mdp = mhdrp; mdp != NULL; mdp = mdp->mnxt)
  {
   for (cp = mdp->mcells; cp != NULL; cp = cp->cnxt)
    {
     for (cpp = cp->cpins; cpp != NULL; cpp = cpp->cpnxt)
      {
       __chk_copied_xpr(cpp->cpxnd, mdp);
      }
    }
  }
}

/*
 * debug routine to check for correct elaborated ipins
 */
extern void __chk_dsgn_ipins(struct mod_t *mhdrp)
{
 int32 ii, pi, pnum;
 struct mod_t *mdp;
 struct inst_t *ip;
 struct expr_t *xp;

 for (mdp = mhdrp; mdp != NULL; mdp = mdp->mnxt)
  {
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     pnum = ip->imsym->el.emdp->mpnum;
     for (pi = 0; pi < pnum; pi++)
      {
       xp = ip->ipins[pi];
       __chk_copied_xpr(xp, mdp);
      }
    }
  }
}

/*
 * debug routine to check for correct copying of mod cell pins
 */
extern void __chk_1mod_cpins(struct mod_t *mdp)
{
 struct cell_t *cp;
 struct cell_pin_t *cpp;

 for (cp = mdp->mcells; cp != NULL; cp = cp->cnxt)
  {
   for (cpp = cp->cpins; cpp != NULL; cpp = cpp->cpnxt)
    {
     __chk_copied_xpr(cpp->cpxnd, mdp);
    }
  }
}

/*
 * check an expr to make sure all nets and params are in right mod
 */
extern void __chk_copied_xpr(struct expr_t *xp, struct mod_t *mdp)
{
 struct net_t *np;

 if (__isleaf(xp))
  {
   if (xp->optyp == ID && xp->lu.sy->sytyp == SYM_N)
    {
     np = xp->lu.sy->el.enp;
     /* SJM 03-07-09 - it is possible for gen var to be undeclared */
     if (np->nsym->sydecl)
      {
       if (np->syt_of_net->sypofsyt != NULL
        && np->syt_of_net->sypofsyt != mdp->msym)
        __misc_terr(__FILE__, __LINE__);
      }
    }
   return;
  }
 if (xp->lu.x != NULL) __chk_copied_xpr(xp->lu.x, mdp);
 if (xp->ru.x != NULL) __chk_copied_xpr(xp->ru.x, mdp);
}

/*
 * ROUTINES TO MERGE SPLIT LEAF MODULES JUST BEFORE DESIGN CHECKING
 */

/*
 * re-merge split leaf modules with exactly same parameter values after
 * splitting
 *
 * splitting needed since had width determing but if all params same,
 * can combine back
 */
extern void __merge_same_pval_leaf_splitmods(void)
{
 int32 spltnum, num_merged, total;
 struct mod_t *hd_mdp;

 /* if no params are split return */
 if (!__pndparam_splits && !__defparam_splits) return;

 /* only do this for comiled sim */
 if (!__compiled_sim) return;

 /* do not do this if splitting turned off */
 if (__same_param_must_split) return;

 /* AIV 02/06/12 - these may already be merged because of generate */
 if (__leaf_modules_already_merged) return;
 __leaf_modules_already_merged = TRUE;

 total = 0;
 for (hd_mdp = __modhdr; hd_mdp != NULL; hd_mdp = hd_mdp->mnxt)
  {
   if (hd_mdp->minum != 0) continue;
   if (hd_mdp->split_hd == NULL) continue;  
   if (hd_mdp->m_combined_into) continue;
   if (hd_mdp->recomb_to_mdp != NULL) continue;

   /* if split via defparam cannot recombine */
   if (hd_mdp->dfp_allmodinsts_split) continue;

   /* for every split leaf module group head - try to find equiv classes */
   spltnum = cnt_split_mods(hd_mdp);
   /* DBG remove -- */
   if (spltnum <= 0) __misc_terr(__FILE__, __LINE__);
   /* -- */
//SJM 01-27-12 - FIXME - should be some small number (20) - for testing always
   if (spltnum < 0) continue;

/* DEBUG
   __cv_msg("+=+= module %s has %d possibly combinable leaf modules +=+=\n",
    hd_mdp->msym->synam, spltnum);  
*/

   if (has_non_combinable_param(hd_mdp)) continue;

   num_merged = combine_split_mods(hd_mdp);
/* DEBUG
   __cv_msg("+=+= module %s has %d merged back +=+=\n",
    hd_mdp->msym->synam, num_merged);  
*/
   total += num_merged;
 }
 if (total) rebld_splt_comb_nl();
}

/*
 * count number of modules split list 
 */
static int32 cnt_split_mods(struct mod_t *hd_mdp)
{
 int32 snum;
 struct mod_t *mdp;
  
 snum = 0;
 for (mdp = hd_mdp->split_hd; mdp != NULL; mdp = mdp->split_nxt) 
  {
//AIV LOOKATME - split list copied to itself?????
   if (mdp == hd_mdp) continue;
   snum++;
  }
 return(snum);
}

   
/*
 * combine all leaf modules with the same parameter values back into
 * one module
 */
static int32 combine_split_mods(struct mod_t *hd_mdp)
{
 int32 total, count;
 struct mod_t *mdp;
 struct mod_t *split_from_mdp;

 
 total = 0;
 count = hd_mdp->flatinum;
 split_from_mdp = hd_mdp;
 for (mdp = hd_mdp->split_hd; mdp != NULL; mdp = mdp->split_nxt) 
  {
//AIV LOOKATME - split list copied to itself?????
   if (mdp == split_from_mdp) continue;
   if (!mprmval_cmp(split_from_mdp, mdp))
    {
     if (has_non_combinable_param(mdp)) continue;

     split_from_mdp->m_combined_into = TRUE;
/* DEBUG
     __cv_msg("+=+= combined module %s to %s\n", mdp->msym->synam, 
        split_from_mdp->msym->synam);  
*/
     mdp->recomb_to_mdp = split_from_mdp;
     total++;
     /* if number of instances is already large just leave split */
     /* this can actually increase compile time by taking longer */
     /* for large jump tables */
     if (count > NO_SPLIT_INST_MAX) 
      {
       split_from_mdp = mdp;
       count = split_from_mdp->flatinum;
       continue;
      }
     count += mdp->flatinum;
    }
  }
 return(total);
}

/*
 * after determining combinable rebuild the various net list data structs
 */
static void rebld_splt_comb_nl(void)
{
 int32 ii;
 struct mod_t *mdp, *to_mdp, *last_mdp;
 struct inst_t *ip;
 struct itree_t *itp;

 /* first change inst mod sym for every mod - since remcomb leaf won't chg */ 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   to_mdp = mdp->recomb_to_mdp;
   /* AIV 02/27/12 - if combined into do not process here */
   if (mdp->m_combined_into) continue;

   if (to_mdp != NULL)
    {
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       itp = mdp->moditps[ii];
       /* DBG remove -- */
       if (itp == NULL) __misc_terr(__FILE__, __LINE__);
       /* -- */

       ip = itp->itip;
       ip->imsym = to_mdp->msym;
       to_mdp->flatinum++;
      }
     mdp->flatinum = 0;
    }
  } 

 /* next update mod hdr list by removing leaf mod's that have been recombed */
 last_mdp = NULL;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* can only link out if have no more instance */
   if (mdp->recomb_to_mdp != NULL && mdp->flatinum == 0) 
    {
     if (last_mdp == NULL) __modhdr = mdp;
     else last_mdp->mnxt = mdp->mnxt; 
    }
   else last_mdp = mdp; 
  }
 /* now that modhdr mods removed the split lists are wrong - nil ptrs */
 free_mods_split_list();
 
 /* final step is freeing and rebuilding instance tree */
 __free_flat_itree();
 __bld_flat_itree();
 __bld_moditps();

//SJM - should probably free the removed split back mods here
//AIV LOOKATME - 01-27-12 - can we just call __free_1mod_cvc_mem here?
}

/*
 * count number of width determining params
 */
static int32 has_non_combinable_param(struct mod_t *mdp)
{
 int32 ni, wlen;
 struct net_t *prmp;
 word32 *wp;
 
 for (ni = 0, prmp = &(mdp->mprms[0]); ni < mdp->mprmnum; ni++, prmp++)
  {
   /* AIV 02/05/12 - SR_PISNUM do not work - LOOKATME - think they should?? */
   if (prmp->srep != SR_PNUM) return(TRUE);

   wlen = wlen_(prmp->nwid);
   /* only include those with zero bpart */
   wp = &(prmp->prm_nva.wp[wlen]);
   if (!vval_is0_(wp, prmp->nwid)) return(TRUE);
  }
 return(FALSE);
}


/*
 * compare 2 modules list of width det params
 */
static int32 mprmval_cmp(struct mod_t *mdp1, struct mod_t *mdp2)
{
 int32 ni, pval1, pval2, wlen, rv;
 struct net_t *prmp1, *prmp2;

 /* DBG remove -- */
 if (mdp1->mprmnum != mdp2->mprmnum) __misc_terr(__FILE__, __LINE__);
 /* -- */ 
 
 for (ni = 0, prmp1 = &(mdp1->mprms[0]), prmp2 = &(mdp2->mprms[0]);
   ni < mdp1->mprmnum; ni++, prmp1++, prmp2++)
  {
   /* skip the IS ones since combining will work - just different IS num */
   if (prmp1->srep != prmp2->srep) continue;

   /* widths better be the same */
   if (prmp1->nwid != prmp2->nwid) return(TRUE);

   if (prmp1->nwid <= WBITS)
    {
     pval1 = prmp1->prm_nva.wp[0];
     pval2 = prmp2->prm_nva.wp[0];
     if (pval1 != pval2) return(pval1 - pval2);
    }
   wlen = wlen_(prmp1->nwid);
   rv = memcmp(prmp1->prm_nva.wp, prmp2->prm_nva.wp, wlen*WRDBYTES);
   if (rv != 0) return(rv);
  }
 return(0);
}

/*
 * routine to nil out the split intertwined through mods lists used for
 * recombining during fixup because now invalid
 */
static void free_mods_split_list(void)
{ 
 struct mod_t *mdp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   mdp->split_hd = NULL;
   mdp->split_tail = NULL;
   mdp->split_nxt = NULL;
  }
}
