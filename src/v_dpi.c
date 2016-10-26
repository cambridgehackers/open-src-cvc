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
 * module to implement all but code generation new DPI interface routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <dlfcn.h>

#include <unistd.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "igen.h"
#include "cvmacros.h"

#include "vpi_user.h"
#include "cv_vpi_user.h"
#include "svdpi.h"

/* local prototypes */
static int32 emsg_has_undef_sym_str(char *); 
static char *disp_itree_idp_path_dpi(t_midat *, struct task_t *);
static t_midat *cnvt_name_to_idp(const char *, struct symtab_t *, t_midat *);
static t_midat *bld_symidp(const char *, struct sy_t *, struct symtab_t *, 
 struct itree_t *);

static void set_dpi_arg_from_xpr(struct expr_t *, struct task_pin_t *,
 int32, struct dpiarg_t *, union adpi_u *);
static void set_dpi_arg_from_net(struct task_pin_t *, int32,
 struct dpiarg_t *, union adpi_u *);
static void set_dpi_arg_from_xstk(struct xstk_t *, struct task_pin_t *,
 int32, struct dpiarg_t *, union adpi_u *);
static void arr_set_dpi_arg(struct expr_t *, struct task_pin_t *,
 int32, struct dpiarg_t *, union adpi_u *);

#ifdef __CVC32__
static void map_to_cside_ab(unsigned int *, word32 *, int32);
static void map_to_verside_vec(word32 *, unsigned int *, int32);
#else
static void map_to_cside_ab(unsigned int *, word64 *, int32);
static void map_to_verside_vec(word64 *, unsigned int *, int32);
#endif
static struct xstk_t *get_dpi_arg(int32, struct dpiarg_t *, union adpi_u *,
 int32);
static void st_dpi_arg(struct expr_t *, int32, struct dpiarg_t *,
 union adpi_u *);
static struct xstk_t *push_dpi_c_side_arr_cell(int32, int32,
 struct dpiarg_t *, union adpi_u *, struct net_t *);

static void linkin_interp_dpi_dlsyms(void);
static void fill_all_dpi_recs(void);
static void alloc_init_dpi_arginfo(struct dpi_t *, int32);

static int32 dpi_cnt_tskpins(struct task_t *); 
static void fill_dpi_arginfo_tab(struct task_t *);
static void gen_dpi_wrapper_file(void);
static void gen_dpi_wrapper_pipe(void);
static void gen_write_dpi_wrapper_file(FILE *);
static void emit_dpi_cside_proto(FILE *, struct dpi_t *, int32);
static char *bld_dpi_proto_comment(char *, struct dpi_t *);
static void emit_dpi_arg_union_decl(FILE *);
static void emit_dpi_1tf_import_call_wrapper(FILE *, struct dpi_t *);
static void emit_dpi_1tf_export_def_wrapper(FILE *, struct dpi_t *);
static char *bld_adpi_u_arg_sel(char *, int32, struct dpiarg_t *);
static char *bld_adpi_u_sel_name(char *, struct dpiarg_t *);

static void gen_rt_dpi_interp_mkfil_and_compile(void);
static void gen_rt_dpi_interp_pipe_lib(void);
static void run_dpi_interp_mkfil(void);
static void wr_dpihdrs(void);

static void set_ver_side_srep(struct net_t *, struct dpiarg_t *);
static char *map_ver_svtyp_to_proto_typnam(char *, struct dpiarg_t *);
static char *map_ver_svtyp_to_ctypnam(char *, struct dpiarg_t *);
static int32 get_ver_side_svtyp(struct net_t *);

/* extern prototypes (maybe defined in this module) */
extern void __chk_1tsk_dpi(struct task_t *);
extern void __chk_funcdef_dpi(struct task_t *);

extern void __chk_fdef_args(struct task_t *);
extern void __chk_lstofsts(struct st_t *);
extern void __chk_nodel_lstofsts(struct st_t *);
extern int32 __get_netwide(struct net_t *);
extern int32 __is_cint_typ(int32);
extern char *__to_wtnam2(char *, word32);
extern void __lhspsel(word32 *, int32, word32 *, int32);
extern void __rhspsel(word32 *, word32 *, int32, int32);
extern struct task_t *__getcur_scope_tsk(void);
extern int32 __name_vpi_hasdot(const char *);
extern struct expr_t *__glbnam_to_expr(char *);
extern int32 __ip_indsrch(char *);
extern void __free_xtree(struct expr_t *);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct sy_t *__get_nongia_sym(char *, struct symtab_t *);
extern int32 __is_scope_sym(struct sy_t *);
extern char *__to_glbcmp_nam(struct expr_t *);
extern char *__to_tsktyp(char *, word32);

extern void __ld_arr_val(struct xstk_t *, struct expr_t *, struct net_t *,
 int32, struct gref_t *);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern void __ld_wire_val_wrds(word32 *, word32 *, struct net_t *);
extern void __exec2_proc_assign(struct expr_t *, word32 *, word32 *, int32);
extern void __eval_tskassign_rhsexpr(struct xstk_t *, int32,
 int32, int32, int32, int32, int32);
extern void __chg_st_arr_val(struct net_t *, struct expr_t *, int32, 
 word32 *, word32 *);
extern void __st_arr_val(struct net_t *, struct expr_t *, int32, word32 *, 
 word32 *, int32);
extern void __wakeup_delay_ctrls(struct net_t *, int32, int32);
extern void __add_select_nchglst_el(struct net_t *, int32, int32);
extern void __add_togglelst_el(struct net_t *);
extern void __add_dp_chglst_el(struct net_t *);
extern struct sy_t *__zget_sym(char *, struct sy_t **, word32);
extern void __st_val(struct net_t *, word32 *, word32 *, int32);
extern void __call_export_tf_wrapper(char *, union adpi_u *);
extern void __exec_dpi_exported_tf(struct task_t *);
extern char *__setstr_objdir_path(void);
extern struct thread_t *__alloc_thrd(void);
extern void __grow_fcstk(void);
extern void __exec_stmts(struct st_t *, int32 *, int32);
extern int32 __get_tmpfnam(char *);
extern char *__pv_stralloc(char *);
extern char *__alloc_vval_to_cstr(word32 *, int32, int32, int32);
extern struct xstk_t *__cstr_to_vval(char *);

extern void __cv_msg(char *, ...);
extern void __wrap_puts(char *, FILE *);
extern void __wrap_putc(int32, FILE *);
extern void __nl_wrap_puts(char *, FILE *);
extern char *__my_malloc(size_t);
extern void __my_free(void *, size_t);
extern FILE *__my_fopen(char *, char *);
extern void __my_fclose(FILE *);
extern void __my_exit(int32, int32);
extern void __pv_terr(int32, char *, ...);
extern void __pv_warn(int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __pv_err(int32, char *, ...);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);

extern const word32 __masktab[];

/* DPI specific globals */
/* SJM 11-07-10 - can't call the wrapper literal name from v_dpi since */
/* the linker will not find the symbol - need only this one dlsym */
void (*__dpi_imp_interp_routp)(int, union adpi_u *);

/*
 * FIXUP ELAB STAGE DPI CHECKING ROUTINES
 */

/*
 * just before chk mod that checks RTL statements need to make sure 
 * import dpi routines in lib
 */
extern int32 __chk_sv_dpi_lib(void)
{
 int32 num_imp_procs, fnd_cnt;
 struct sv_lib_t *svlp, *svlp2;
 struct dpi_t *dpip;
 void *fhandle;
 char *chp, impextypnam[RECLEN];

 /* if user does not pass -sv_lib - there is no way this can link properly */
 if (__sv_lib_hdrp == NULL)
  {
   __pv_err(4801,
    "DPI import or export used so a least one libary (.so file) -sv_lib option required on command line - but none present");
   return(FALSE);
  }
 for (num_imp_procs = 0, dpip= __dpi_hdrp; dpip != NULL; dpip = dpip->dpinxt)
  {
   if (dpip->dpi_type != DPI_IMPORT) continue;
   num_imp_procs++;
  }

 /* SJM 02-11-13 - need to mark and check import dpi routines because need */
 /* better dpi error checking */ 
 /* for each library mark all unmarked dlopenable syms */
 /* need to call to reset any pending dl errors */
 dlerror();
 for (fnd_cnt = 0, svlp = __sv_lib_hdrp; svlp != NULL; svlp = svlp->svnxt)
  {
   /* SJM 02-01-13 - see RHEL 6.x man page - say only dl err can find errors */
   /* but that is not what other man pages say - assuming dl open ret of nil */
   /* if can't open */
   if ((fhandle = dlopen(svlp->path, RTLD_LAZY | RTLD_GLOBAL)) == NULL)
    {
     /* case 1: can't open library - may be ok */
     /* warning if can't open a -sv_lib file - might be ok */
     __pv_warn(3137,
      "unable to open -sv_lib %s error: %s - if all dpi_ import routines found - simulation may still work",
     svlp->path, dlerror());
     /* SJM 02-12-13 - if get here, will not be open, so no need for dl close */
     continue;
    }
   /* need to keep looking */
   /* try to find all symbols in one library */
   for (dpip = __dpi_hdrp; dpip != NULL; dpip = dpip->dpinxt)
    {
     /* dpi import must be an sv lib or can't continue */ 
     if (dpip->dpi_type != DPI_IMPORT) continue;
     if (dpip->imp_fnd_in_lib) continue;

     if (dpip->cname == NULL) strcpy(impextypnam, dpip->dsym->synam);
     else strcpy(impextypnam, dpip->cname);
     dlerror();
     dlsym(fhandle, impextypnam);
     /* think not found is not an error */
     if ((chp = dlerror()) != NULL)
      {
       if (!emsg_has_undef_sym_str(chp))
        {
         __pv_warn(3142,
          "dpi_ import routine dlsym error searching for %s in library %s error - reason: %s",
          impextypnam, svlp->path, chp);
        }
      }
     else
      {
       if (__dpi_verbose)
        {
         __cv_msg("  DPI: found import routine %s in -sv_lib %s\n", 
          impextypnam, svlp->path);
        }
       dpip->imp_fnd_in_lib = TRUE;
       fnd_cnt++;
      }
    }
   /* SJM 02-12-13 - need the dl close - return 0 on success */
   if (dlclose(fhandle) != 0)
    {
     __pv_warn(3147, "dpi_ -sv_lib %s close failed - reason: %s",
      svlp->path, dlerror());
    } 
   if (fnd_cnt >= num_imp_procs)
    {
     /* SJM 02-11-13 - need warnings if all found before end of sv libs */
     for (svlp2 = svlp->svnxt; svlp2 != NULL; svlp2 = svlp2->svnxt) 
      {
       __pv_warn(3146,
        "-sv_lib %s not searched for dpi_ import routines - all import symbols already found",
        svlp2->path);
      }
     /* only if dpi_ verbose, need msg */
     __cv_msg("  DPI: all dpi_ import task/function routines found.\n");
     return(TRUE);
    }
  }
 /* DBG remove -- */
 if (fnd_cnt >= num_imp_procs) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* print out the missing ones */
 for (dpip = __dpi_hdrp; dpip != NULL; dpip = dpip->dpinxt)
  {
   if (dpip->dpi_type != DPI_IMPORT) continue;
   if (dpip->imp_fnd_in_lib) continue;

   if (dpip->cname == NULL) strcpy(impextypnam, dpip->dsym->synam);
   else strcpy(impextypnam, dpip->cname);

   __pv_err(4832,
    "DPI import routine %s not declared in any -sv_lib library", 
    impextypnam);
  }
 return(FALSE);
}

/*
 * return T if error string from dlerror after dlsym has "undefined symbol:"
 * in it
 *
 * SJM 06-25-13 - dlsym produces an error when a symbol is undefined in one
 * library but this is not an error or a problem providing that dlsym finds
 * symbol in later library - there will be an error if never found which is
 * right behavior 
 *
 * this is inefficient string matching algorithm
 */
static int32 emsg_has_undef_sym_str(char *emsg) 
{
 char *chp;

 for (chp = emsg; *chp != '\0'; chp++)
  {
   if (*chp != 'u') continue;
   if (strncmp(chp, "undefined symbol:", 17) == 0) return(TRUE);
  }
 return(FALSE);
}

/*
 * DPI task checking - almost same as regular task allowing passing of
 * entire arrays, no delay in exported tasks, etc
 */
extern void __chk_1tsk_dpi(struct task_t *tskp)
{
 int32 ai;
 struct task_pin_t *tpp;
 struct net_t *np;
 struct sy_t *syp;
 struct dpi_t *dpip;

 dpip = tskp->tf_dpip;
 __cur_tsk = tskp;
 /* variables checked, chk statements & look for non thread optimizations */
 for (ai = 1, tpp = tskp->tskpins; tpp != NULL; tpp = tpp->tpnxt, ai++)
  {
   np = tpp->tpsy->el.enp;
   /* now allowing passing entire array to DPI routine - only imports */
   if (np->n_isarr)
    {
     syp = tpp->tpsy;
     if (dpip->dpi_type == DPI_EXPORT)
      {
       __gferr(4817, syp->syfnam_ind, syp->sylin_cnt,
        "DPI exported %s %s definition entire array formal argument %s (pos. %d) illegal - must be simple variable",
        __to_tsktyp(__xs, tskp->tsktyp), tskp->tsksyp->synam, syp->synam, ai);
      }
     else if (np->mda != NULL)
      {
       __gferr(4818, syp->syfnam_ind, syp->sylin_cnt,
        "DPI %s %s definition argument %s (pos. %d) illegal - CVC DPI currently does not support multi-dimension arrays",
        __to_tsktyp(__xs, tskp->tsktyp), tskp->tsksyp->synam, syp->synam, ai);
      }
     continue;
    }

   /* notice task ports must be regs so no need to set 2nd on lhs */
   if (tpp->trtyp != IO_IN)
    {
     if (np->nrngrep == NX_CT)
      {
       if (tpp->trtyp == IO_BID) np->nu.ct->n_onlhs = TRUE;
       np->nu.ct->n_onrhs = TRUE;
      }
     tskp->thas_outs = TRUE;
    }
   else if (np->nrngrep == NX_CT) np->nu.ct->n_onlhs = TRUE;
  }
 __disp_uses_scope = FALSE;
 /* notice that task can take any legal variables no argument */
 /* requirements - this finds any named block no delay cases */
 __chk_lstofsts(tskp->tskst);

 /* finally do checking to determine if 0 delay or has task call */ 
 __task_has_delay = FALSE;
 __task_has_tskcall = FALSE;
 __task_has_xmrcall = FALSE;
 __nbsti = -1;
 __chk_nodel_lstofsts(tskp->tskst);
 /* AIV 05/28/07 - set task delay bit */
 tskp->no_delay = !__task_has_delay;
 /* AIV 04/12/10 - if task does not contain a delay there is no reason */
 /* for it to be automatic - turn off flag */
 /* AIV LOOKATME - pretty sure this is correct ???? */
 if (tskp->no_delay && !__task_has_tskcall) tskp->is_auto = FALSE;
 tskp->uses_scope = __disp_uses_scope;
 tskp->no_xmrcall = !__task_has_xmrcall;
 /* not allowing export tasks with delays for now */
 /* SJM 12-06-10 - because interp can just set the thread state - delays and */
 /* event controls work in exported ver tasks - not true of compiler */
 if (__execute_compiled)
  {
   if (__task_has_delay && dpip->dpi_type == DPI_EXPORT)
    {
     syp = tskp->tsksyp;
     __gferr(4821, syp->syfnam_ind, syp->sylin_cnt,
      "export task/function %s cannot have delay", tskp->tsksyp->synam);
    }
  } 
 __disp_uses_scope = FALSE;
 __cur_tsk = NULL;

 /* cannot have automatic DPI functions */
 if (tskp->is_auto)
  {
   __sgferr(4888, "DPI task %s cannot be declared automatic",
    tskp->tsksyp->synam);
  }
}

/*
 * DPI function checking - almost same as regular task allowing passing of
 * entire arrays, no delay in exported tasks, can be void, etc
 */
extern void __chk_funcdef_dpi(struct task_t *tskp)
{
 int32 saverr_cnt, nwid;
 struct dpi_t *dpip;
 struct task_pin_t *tpp;
 struct net_t *np;
 char s1[RECLEN];
   
 __cur_tsk = tskp;

 saverr_cnt = __pv_err_cnt;
 /* check definition args */
 __chk_fdef_args(tskp);

 /* SJM 09/28/01 - see if func call other non sys func */
 __func_has_fcall = FALSE;

 /* first check all statements normally */ 
 __disp_uses_scope = FALSE;
 __chk_lstofsts(tskp->tskst);
 if (__func_has_fcall) tskp->fhas_fcall = TRUE;
 tskp->uses_scope = __disp_uses_scope;

 /* check all sub statements for illegal delay controls */
 /* also sets name_assigned_to if name somewhere on assign lhs */
 __task_has_delay = FALSE;
 __task_has_xmrcall = FALSE;
 __task_has_tskcall = FALSE;
 __name_assigned_to = FALSE;
 __locfnamsyp = tskp->tskpins->tpsy;
 __nbsti = -1;
 __checking_only = FALSE;
 __chk_nodel_lstofsts(tskp->tskst);
 __checking_only = TRUE;

 /* must leave name assigned to off, unless checking func. def body */
 __name_assigned_to = FALSE;
 if (__pv_err_cnt != saverr_cnt) tskp->tsksyp->sydecl = FALSE;
 __cur_tsk = NULL;
 __disp_uses_scope = FALSE;

 /* DPI function max return width is 64-bits */
 dpip = tskp->tf_dpip;
 if (dpip->has_ret)
  {
   tpp = tskp->tskpins;
   np = tpp->tpsy->el.enp;
   nwid = __get_netwide(np);
   /* DPI functions can only return C-style values */
   /* or scalar bit/logic */
   /* AIV 11/16/10 - can return string (char *) */
   if (!__is_cint_typ(np->ntyp) && !(nwid == 1 && np->ntyp == N_BIT) && 
       !(nwid == 1 && np->ntyp == N_LOGIC) && 
       (np->ntyp != N_STRING)) 
    {
     __to_wtnam2(s1, np->ntyp);
     __sgferr(4889,
      "DPI function %s return value must be a c style value or scalar not type - %s\n",
       np->nsym->synam, s1);
    }
   if (nwid > 64)
    {
     __sgferr(4890,
      "DPI maximum width return is 64-bits - function %s return width %d is too wide\n",
      np->nsym->synam, nwid);
    }
   }
 /* cannot have automatic DPI functions */
 if (tskp->is_auto)
  {
   __sgferr(4891, "DPI function %s cannot be declared automatic\n",
    tskp->tsksyp->synam);
  }
}

/*
 * DPI RUNTIME LRM DEFINED ROUTINES - defined in svdpi.h
 */

/*
 * Return implementation version information string ("P1800-2005" or "SV3.1a").
 */
extern const char* svDpiVersion(void)
{
 return("P1800-2005");
}

/* 
 * Bit select utility functions.
 *
 * Packed arrays are assumed to be indexed n-1:0,
 * where 0 is the index of least significant bit
 */

/* s=source, i=bit-index */
extern svBit svGetBitselBit(const svBitVecVal* s, int i)
{
 svBit sb;
 int32 wofs, bofs;
     
 /* notice - these are always 32-bit here - even for 64-bit */
 /* cannot use macros */
 wofs = i >> 5;  
 bofs = i & 0x1f;
 sb = (s[wofs] >> bofs) & 1L;
 return(sb);
}

extern svLogic svGetBitselLogic(const svLogicVecVal* s, int i)
{
 svLogic svl;
 uint32_t aval, bval;
 int32 wofs, bofs;
     
 /* notice - these are always 32-bit here - even for 64-bit */
 /* cannot use macros */
 wofs = i >> 5;  
 bofs = i & 0x1f;
 aval = s[wofs].aval;
 bval = s[wofs].bval;
 aval = (aval >> bofs) & 1L;
 bval = (bval >> bofs) & 1L;
 svl = (aval | (bval << 1));
 return(svl);
}

/* d=destination, i=bit-index, s=scalar */
extern void svPutBitselBit(svBitVecVal* d, int i, svBit s)
{
 int32 wofs, bofs;
     
 /* notice - these are always 32-bit here - even for 64-bit */
 /* cannot use macros */
 wofs = i >> 5;  
 bofs = i & 0x1f;
 d[wofs] &= ~(1L << bofs);
 d[wofs] |= ((s & 1L) << bofs);
}

extern void svPutBitselLogic(svLogicVecVal* d, int i, svLogic s)
{
 svLogic a, b;
 svLogicVecVal *sp;
 uint32_t aval, bval;
 int32 wofs, bofs;

 /* notice - these are always 32-bit here - even for 64-bit */
 /* cannot use macros */
 wofs = i >> 5;  
 bofs = i & 0x1f;
 sp = &(d[wofs]);

 /* do the a value */
 aval = sp->aval;
 aval &= ~(1L << bofs);
 a = s & 1;
 aval |= (a << bofs);
 sp->aval = aval;

 /* do the b value */
 bval = sp->bval;
 bval &= ~(1L << bofs);
 b = (s >> 1) & 1;
 bval |= (b << bofs);
 sp->bval = bval;
}

/*
 * Part select utility functions.
 *
 * A narrow (<=32 bits) part select is extracted from the
 * source representation and written into the destination word.
 *
 * Normalized ranges and indexing [n-1:0] are used for both arrays.
 *
 * s=source, d=destination, i=starting bit index, w=width
 * like for variable part selects; limitations: w <= 32
 */
extern void svGetPartselBit(svBitVecVal* d, const svBitVecVal* s, int i, int w)
{
 word32 *dp, *sp;

 if (w > 32) return;

 dp = (word32 *) d;
 sp = (word32 *) s;
 __rhspsel(dp, sp, i, w);
}

extern void svGetPartselLogic(svLogicVecVal* d, const svLogicVecVal* s, int i, 
 int w)
{
 int32 wofs;
 svLogicVecVal *dp;
 svLogicVecVal sval;
 word32 *dpp, *spp;

 if (w > 32) return;

 /* notice - these are always 32-bit here - even for 64-bit */
 /* cannot use macros */
 wofs = i >> 5;  
 sval = s[wofs];
 dp = &(d[wofs]);

 /* just cast the a/b pointer to word32 */
 dpp = (word32 *) &(dp->aval);
 spp = (word32 *) &(sval.aval);
 __rhspsel(dpp, spp, i, w);
 dpp = (word32 *) &(dp->bval);
 spp = (word32 *) &(sval.bval);
 __rhspsel(dpp, spp, i, w);
}

extern void svPutPartselBit(svBitVecVal* d, const svBitVecVal s, int i, int w)
{
 word32 *dp, *sp;

 if (w > 32) return;

 dp = (word32 *) d;
 sp = (word32 *) &s;
 __lhspsel(dp, i, sp, w);
}

extern void svPutPartselLogic(svLogicVecVal* d, const svLogicVecVal s, int i, 
 int w)
{
 int32 wofs;
 svLogicVecVal *dp;
 word32 *dpp, *spp;

 if (w > 32) return;

 /* notice - these are always 32-bit here - even for 64-bit */
 /* cannot use macros */
 wofs = i >> 5;  
 dp = &(d[wofs]);
 /* just cast the a/b pointer to word32 */
 dpp = (word32 *) &(dp->aval);
 spp = (word32 *) &(s.aval);
 __lhspsel(dpp, i, spp, w);
 dpp = (word32 *) &(dp->bval);
 spp = (word32 *) &(s.bval);
 __lhspsel(dpp, i, spp, w);
}


/*
 * Open array querying functions
 * These functions are modeled upon the SystemVerilog array
 * querying functions and use the same semantics.
 * 
 * If the dimension is 0, then the query refers to the
 * packed part of an array (which is one dimensional).
 * Dimensions > 0 refer to the unpacked part of an array.
 */
/* h= handle to open array, d=dimension */
extern int svLeft(const svOpenArrayHandle h, int d)
{
 return(-1);
}

extern int svRight(const svOpenArrayHandle h, int d)
{
 return(-1);
}

extern int svLow(const svOpenArrayHandle h, int d)
{
 return(-1);
}

extern int svHigh(const svOpenArrayHandle h, int d)
{
 return(-1);
}

extern int svIncrement(const svOpenArrayHandle h, int d)
{
 return(-1);
}

extern int svLength(const svOpenArrayHandle h, int d)
{
 return(-1);
}

extern int svDimensions(const svOpenArrayHandle h)
{
 return(-1);
}

/*
 * Pointer to the actual representation of the whole array of any type
 * NULL if not in C layout
 */
extern void *svGetArrayPtr(const svOpenArrayHandle h)
{
 return(NULL);
}

/* total size in bytes or 0 if not in C layout */
extern int svSizeOfArray(const svOpenArrayHandle h)
{
 return(-1);
}

/*
 * Return a pointer to an element of the array
 * or NULL if index outside the range or null pointer
 */
extern void *svGetArrElemPtr(const svOpenArrayHandle h, int indx1, ...)
{
 return(NULL);
}

/* specialized versions for 1-, 2- and 3-dimensional arrays: */
extern void *svGetArrElemPtr1(const svOpenArrayHandle h, int indx1)
{
 return(NULL);
}

extern void *svGetArrElemPtr2(const svOpenArrayHandle h, int indx1, int indx2)
{
 return(NULL);
}

extern void *svGetArrElemPtr3(const svOpenArrayHandle h, int indx1, int indx2,
        int indx3)
{
 return(NULL);
}

/*
 * Functions for copying between simulator storage and user space.
 * These functions copy the whole packed array in either direction.
 * The user is responsible for allocating an array to hold the 
 * canonical representation.
 */

/* s=source, d=destination */
/* From user space into simulator storage */
extern void svPutBitArrElemVecVal(const svOpenArrayHandle d, 
 const svBitVecVal* s, int indx1, ...)
{

}

extern void svPutBitArrElem1VecVal(const svOpenArrayHandle d, 
 const svBitVecVal* s, int indx1)
{

}

extern void svPutBitArrElem2VecVal(const svOpenArrayHandle d, 
 const svBitVecVal* s, int indx1, int indx2)
{

}

extern void svPutBitArrElem3VecVal(const svOpenArrayHandle d, 
 const svBitVecVal* s, int indx1, int indx2, int indx3)
{

}

extern void svPutLogicArrElemVecVal(const svOpenArrayHandle d, 
 const svLogicVecVal* s, int indx1, ...)
{

}

extern void svPutLogicArrElem1VecVal(const svOpenArrayHandle d, 
 const svLogicVecVal* s, int indx1)
{
}

extern void svPutLogicArrElem2VecVal(const svOpenArrayHandle d, 
 const svLogicVecVal* s, int indx1, int indx2)
{


}

extern void svPutLogicArrElem3VecVal(const svOpenArrayHandle d, 
 const svLogicVecVal* s, int indx1, int indx2, int indx3)
{


}



/* From simulator storage into user space */
extern void svGetBitArrElemVecVal(svBitVecVal* d, const svOpenArrayHandle s,
        int indx1, ...)
{

}

extern void svGetBitArrElem1VecVal(svBitVecVal* d, const svOpenArrayHandle s,
        int indx1)
{

}
extern void svGetBitArrElem2VecVal(svBitVecVal* d, const svOpenArrayHandle s,
        int indx1, int indx2)
{

}

extern void svGetBitArrElem3VecVal(svBitVecVal* d, const svOpenArrayHandle s,
        int indx1, int indx2, int indx3)
{

}

extern void svGetLogicArrElemVecVal(svLogicVecVal* d, const svOpenArrayHandle s,
        int indx1, ...)
{

}

extern void svGetLogicArrElem1VecVal(svLogicVecVal* d, 
             const svOpenArrayHandle s, int indx1)
{

}

extern void svGetLogicArrElem2VecVal(svLogicVecVal* d, 
  const svOpenArrayHandle s, int indx1, int indx2)
{

}

extern void svGetLogicArrElem3VecVal(svLogicVecVal* d, 
            const svOpenArrayHandle s, int indx1, int indx2, int indx3)
{

}

extern svBit svGetBitArrElem(const svOpenArrayHandle s, int indx1, ...)
{

 return(0);
}

extern svBit svGetBitArrElem1(const svOpenArrayHandle s, int indx1)
{

 return(0);
}

extern svBit svGetBitArrElem2(const svOpenArrayHandle s, int indx1, int indx2)
{

 return(0);
}

extern svBit svGetBitArrElem3(const svOpenArrayHandle s, int indx1, int indx2,
        int indx3)
{

 return(0);
}

extern svLogic svGetLogicArrElem(const svOpenArrayHandle s, int indx1, ...)
{

 return(0);
}

extern svLogic svGetLogicArrElem1(const svOpenArrayHandle s, int indx1)
{

 return(0);
}

extern svLogic svGetLogicArrElem2(const svOpenArrayHandle s, int indx1, 
  int indx2)
{

 return(0);
}

extern svLogic svGetLogicArrElem3(const svOpenArrayHandle s, int indx1, 
 int indx2, int indx3)
{

 return(0);
}

extern void svPutLogicArrElem(const svOpenArrayHandle d, svLogic value, 
 int indx1, ...)
{

}

extern void svPutLogicArrElem1(const svOpenArrayHandle d, svLogic value, 
  int indx1)
{

}


extern void svPutLogicArrElem2(const svOpenArrayHandle d, svLogic value, 
 int indx1, int indx2)
{

}

extern void svPutLogicArrElem3(const svOpenArrayHandle d, svLogic value, 
 int indx1, int indx2, int indx3)
{

}

extern void svPutBitArrElem(const svOpenArrayHandle d, svBit value, int indx1,   ...)
{

}

extern void svPutBitArrElem1(const svOpenArrayHandle d, svBit value, int indx1)
{
}

extern void svPutBitArrElem2(const svOpenArrayHandle d, svBit value, int indx1,
        int indx2)
{

}

extern void svPutBitArrElem3(const svOpenArrayHandle d, svBit value, int indx1,
        int indx2, int indx3)
{

}


/* Functions for working with DPI context */

/*
 * Retrieve the active instance scope currently associated with the executing
 * imported function.  Unless a prior call to svSetScope has occurred, this
 * is the scope of the function's declaration site, not call site.
 * Returns NULL if called from C code that is *not* an imported function.
 */
extern svScope svGetScope()
{
 /* just need to return the idp address */
 return(__idp);
}

/*
 * Set context for subsequent export function execution.
 * This function must be called before calling an export function, unless
 * the export function is called while executing an extern function. In that
 * case the export function shall inherit the scope of the surrounding extern
 * function. This is known as the "default scope".
 * The return is the previous active scope (as per svGetScope)
 */
extern svScope svSetScope(const svScope scope)
{
 /* just need to set the idp address */
 __idp = (t_midat *) scope;
 return(scope);
}

/* Gets the fully qualified name of a scope handle */
extern const char* svGetNameFromScope(const svScope scope)
{
 struct task_t *tskp;
 svScope s;

 /* assume if passed NULL - is the current scope */
 if (scope == NULL) s = __idp;
 else s = scope;

 if (__cur_thd == NULL || __scope_tskp != NULL) tskp = __scope_tskp; 
 /* %m defined as "scope" which may be task/func/block/inst */
 else tskp = __getcur_scope_tsk();
 /* notice this leaks memory here - put nothing can really do about it */
 return(disp_itree_idp_path_dpi(s, tskp));
}

/*
 * Retrieve svScope to instance scope of an arbitrary function declaration.
 * (can be either module, program, interface, or generate scope)
 * The return value shall be NULL for unrecognized scope names.
 */
extern svScope svGetScopeFromName(const char* scopeName)
{
 t_midat *idp;

 idp = cnvt_name_to_idp(scopeName, NULL, __idp);
 return((svScope) idp);
}

/*
 * Store an arbitrary user data pointer for later retrieval by svGetUserData()
 * The userKey is generated by the user. It must be guaranteed by the user to
 * be unique from all other userKey's for all unique data storage requirements
 * It is recommended that the address of static functions or variables in the
 * user's C code be used as the userKey.
 * It is illegal to pass in NULL values for either the scope or userData
 * arguments. It is also an error to call svPutUserData() with an invalid
 * svScope. This function returns -1 for all error cases, 0 upon success. It is
 * suggested that userData values of 0 (NULL) not be used as otherwise it can
 * be impossible to discern error status returns when calling svGetUserData()
 */
extern int svPutUserData(const svScope scope, void *userKey, void* userData)
{
 return(-1);
}

/*
 * Retrieve an arbitrary user data pointer that was previously
 * stored by a call to svPutUserData(). See the comment above
 * svPutUserData() for an explanation of userKey, as well as
 * restrictions on NULL and illegal svScope and userKey values.
 * This function returns NULL for all error cases, 0 upon success.
 * This function also returns NULL in the event that a prior call
 * to svPutUserData() was never made.
 */
extern void* svGetUserData(const svScope scope, void* userKey)
{
 return(NULL);
}

/*
 * Returns the file and line number in the SV code from which the extern call
 * was made. If this information available, returns TRUE and updates fileName
 * and lineNumber to the appropriate values. Behavior is unpredictable if
 * fileName or lineNumber are not appropriate pointers. If this information is
 * not available return FALSE and contents of fileName and lineNumber not
 * modified. Whether this information is available or not is implementation
 * specific. Note that the string provided (if any) is owned by the SV
 * implementation and is valid only until the next call to any SV function.
 * Applications must not modify this string or free it
 */
extern int svGetCallerInfo(const char** fileName, int *lineNumber)
{
 //AIV LOOKATME - could support this - put would have to set for every call
 //to a dpi routine - skipping for performance
 return(FALSE);
}

/*
 * Returns 1 if the current execution thread is in the disabled state.
 * Disable protocol must be adhered to if in the disabled state.
 */
extern int svIsDisabledState()
{
 return(-1);
}

/*
 * Imported functions call this API function during disable processing to
 * acknowledge that they are correctly participating in the DPI disable protocol.
 * This function must be called before returning from an imported function that is
 * in the disabled state.
 */
extern void svAckDisabledState()
{
}

/*
 *  END OF SVDPI.h FILE HERE
 */


/*
 * HELPER ROUTINES FOR BUILT IN SV* CALLS
 */

/*
 * return a scope name - similar to disp_itree_idp_path in v_cnv.c -
 * expect it returns a string - not place it in __exprline
 */
static char *disp_itree_idp_path_dpi(t_midat *idp, struct task_t *tskp)
{
 int32 gi, save_gi;
 struct symtab_t *sytp;
 struct itree_t *itp;
 int32 slen;
 char *namep;

 /* if in task (probably nested block), build from bottom */
 if (tskp != NULL)
  {
   for (sytp = tskp->tsksymtab, gi = 0;;)
    {
     /* notice do not need glb x cmps here since symbol is right inst */
     __glbsycmps[gi] = sytp->sypofsyt;
     sytp = sytp->sytpar;
     /* SJM 05-02-10 - now parent of task can be gen blk when disping */
     if (sytp == NULL || sytp->sypofsyt == NULL
      || sytp->sypofsyt->sytyp == SYM_M) break;
//SJM 05-02-10 - FIXME - ???? wrong since omitting gen blk name that is not
// really a symbol - better to read gen blks into mod_t records
     if (++gi >= MAXGLBCOMPS)
      __pv_terr(310,
       "cannot print instance path name with too many components (%d)",
       MAXGLBCOMPS);
    }
   gi++;
  }
 else gi = 0;

 /* fill from front to end - know at least one component */
 itp = (struct itree_t *) idp[MD_ITP];
 for (;;)
  {
   __glbsycmps[gi] = itp->itip->isym;
   /* virtual tops modules have no up entry */
   itp = itp->up_it;
   if (itp == NULL) break;
   if (++gi >= MAXGLBCOMPS)
    __pv_terr(310,
     "cannot print instance path name with too many components (%d)",
     MAXGLBCOMPS);
  }
 /* then fill top end to front - know string nil terminated by last __adds */
 slen = 0;
 save_gi = gi;
 for (; gi >= 0; gi--)
  { 
   slen += strlen(__glbsycmps[gi]->synam); 
   if (gi > 0) slen++;
  }
 slen++;
 namep = (char *) __my_malloc(slen);

 gi = save_gi;
 strcpy(namep, __glbsycmps[gi]->synam); 
 gi--;
 for (; gi >= 0; gi--)
  { 
   strcat(namep, "."); 
   strcat(namep, __glbsycmps[gi]->synam); 
  }
 return(namep);
}

/*
 * AIV 09/15/10 - basically the same as cnvt_name_to_handle in v_vpi2.c
 * except it doesn't create handle it just returns the idp area pointer
 */
static t_midat *cnvt_name_to_idp(const char *nam, struct symtab_t *sytp,
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
           return(bld_symidp(nam, syp, sytp, itp));
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
       return(bld_symidp(nam, syp, sytp, itp));
      }
     /* if last symbol, build the scope handle - this is inst. type ref */
     if (gcmp_ndp->ru.x == NULL)
      { 
       if (glbndp != NULL) __free_xtree(glbndp);
       return(bld_symidp(nam, syp, sytp, itp));
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
   __misc_terr(__FILE__, __LINE__);
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
   return(itp->it_idp);
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
      return(bld_symidp(nam, syp, sytp, itp));
    }
   return(NULL);
  }
 /* simple name found in scope */
 return(bld_symidp(nam, syp, sytp, itp));
}

/*
 * just the same as bld_symhandle in v_vpi2.c - but this is known to take
 * a module and return the idp address, if not a module return NULL
 */
static t_midat *bld_symidp(const char *nam, struct sy_t *syp,
 struct symtab_t *sytp, struct itree_t *itp)
{
 int32 ii;
 byte *bp1, *bp2;
 struct inst_t *ip;
 struct itree_t *down_itp;
 struct mod_t *mdp;

 if (syp->sytyp != SYM_I) return(NULL);

 mdp = itp->itip->imsym->el.emdp;  
 ip = syp->el.eip;
 bp1 = (byte *) ip;
 bp2 = (byte *) mdp->minsts;
 ii = (bp1 - bp2)/sizeof(struct inst_t);
 down_itp = &(itp->in_its[ii]);
 return(down_itp->it_idp);
}

/* ===
#######################################################################
#######################################################################
#######################################################################
#######################################################################
#######################################################################
==== */

/*
 * ROUTINES TO CALL EVAL ARGS AND CALL DPI GENED C WRAPPER ROUTINE
 */

#define RT_DPI_INTERP_MKFIL "makefile.interp.wrap.dpi"
#define DPI_IMP_INTERP_ROUT "__eval_dpi_wrapper"
#define DPI_EXP_INTERP_WRAP_ROUT "__call_export_tf_wrapper"
#define DPI_HDR_FIL "dpi_hdrs.h"
/* just create some dummy space for SV Strings 2048 ??? */
#define DPI_DFLT_STRING_BYTES 2048/8
extern void __eval_dpi_wrapper(int, union adpi_u *);

/*
 * routine to exec a dpi function and task
 *
 * for functions first tpp is ret value and leaves ret on stack, for tasks
 * first tpp and first dpi ainfo is real first arg
 */
extern void __exec_dpi_imported_tf(struct task_t *tskp,
 struct expr_t *arghd_xp)
{
 int32 argi, argwid;
 struct dpi_t *dpip;
 struct task_pin_t *tpp;
 t_midat *cur_save_idp;
 struct expr_t *argxp, *lhsxp;
 struct xstk_t *xsp;
 struct net_t *c_np;
 struct dpiarg_t *dap;

 dpip = tskp->tf_dpip;
 cur_save_idp = __idp;
 /* for func, first arg is return value */
 if (tskp->tsktyp == FUNCTION) { tpp = tskp->tskpins->tpnxt; argi = 1; }
 else { tpp = tskp->tskpins; argi = 0; }
  
 /* SJM 11-05-10 - for func, first tskpin is variable that is name of func */
 /* that is return val of expr on xstk for interpreter */
 /* for task first is just first arg */
 for (argxp = arghd_xp; argxp != NULL; argxp = argxp->ru.x, tpp = tpp->tpnxt,
  argi++)
  {
   c_np = tpp->tpsy->el.enp;
   dap = &(dpip->dpi_ainfo[argi]);
   if (!c_np->n_isarr)
    {
     set_dpi_arg_from_xpr(argxp, tpp, argi, dap, dpip->arg_u_tab);
    }
   else arr_set_dpi_arg(argxp, tpp, argi, dap, dpip->arg_u_tab);
  }

 /* call the generated wrapper in the generated wrapper .so lib */ 
 /* call generate wrapper - this is the one dlsym since v dpi is linked */
 /* before the libraries are dlopened */
 __dpi_imp_interp_routp(dpip->dpi_proc_ndx, dpip->arg_u_tab);

 /* assign to output and inout args, normal chg store rules */
 if (tskp->tsktyp == FUNCTION) { tpp = tskp->tskpins->tpnxt; argi = 1; }
 else { tpp = tskp->tskpins; argi = 0; }
 for (argxp = arghd_xp; argxp != NULL; argxp = argxp->ru.x, tpp = tpp->tpnxt,
  argi++)
  {
   if (tpp->trtyp == IO_IN) continue;

   lhsxp = argxp->lu.x;
   /* assign task local param var. value to lhs call argument */
   /* xp->lu.x is rhs src., np is lhs dest. var. */
   c_np = tpp->tpsy->el.enp;
   dap = &(dpip->dpi_ainfo[argi]);
   if (!c_np->n_isarr)
    {
     /* SJM 03-03-13 - fixed was not using tpp which differs for func or task */
     argwid = tpp->tpsy->el.enp->nwid;
     xsp = get_dpi_arg(argi, dap, dpip->arg_u_tab, argwid);
     __exec2_proc_assign(lhsxp, xsp->ap, xsp->bp, xsp->xslen);
     __pop_xstk();
    }
   else
    {
     /* SJM 11-19-10 - array case store - handles it own popping */
     st_dpi_arg(argxp, argi, dap, dpip->arg_u_tab);
    } 
  }
 /* SJM 11-07-10 - for func, leaves return val on xstk for tck call */
 /* just returns */ 
 if (tskp->tsktyp == FUNCTION)
  {
   /* DBG remove -- */
   if (dpip->dpi_ainfo[0].ver_side_svtyp == VOID)
    __misc_terr(__FILE__, __LINE__);
   /* --- */

   /* SJM 11-07-10 - for function, return value is first tpp pin */
   dap = &(dpip->dpi_ainfo[0]);
   argwid = tskp->tskpins->tpsy->el.enp->nwid;
   /* the xsp is ignored in this proc, caller get ret val off top of xstk */
   xsp = get_dpi_arg(0, dap, dpip->arg_u_tab, argwid);
  }
}

//SJM 11-03-10 - put me back for wrapper .c file gen
/* ===
extern void __eval_dpi_wrapper(int dpi_ndx, union adpi_u *a_u_tab)
{
}
==== */

/*
 * ROUTINES TO GET VER SIDE VAL AND STORE INTO C SIDE WRAPPER UNION FOR IN/INOUT
 */

/*
 * routine to set argi position value into dpi arg union field (may malloc)
 * for non array both 32 and 64 bits cases
 *
 * for setting arg union before calling c function for DPI import t/f
 *
 * semantics is pass by value/result not pass by reference
 * but value/result for wider and x/z things alloc and fill ptr in arg union
 *
 * must match all the complexities of Verilog t/f arg eval
 * passing arg value union array as separate arg since need to pass that way
 * to wrapper
 */
static void set_dpi_arg_from_xpr(struct expr_t *argxp, struct task_pin_t *tpp,
 int32 argi, struct dpiarg_t *dap, union adpi_u *a_u_tab)
{
 struct expr_t *xp;
 struct net_t *c_np;
 struct xstk_t *xsp;

 /* this is the c side dpi import net */
 c_np = tpp->tpsy->el.enp;

 xp = argxp->lu.x;
 /* for non output, eval arg onto top of xstk */
 /* output easy - either do nothing or malloc if need ptr */
 /* get value of non outputs - need size conversion */
 xsp = NULL;
 if (tpp->trtyp != IO_OUT) 
  {
   /* wrong width (net type) IDs, this will do the size conversion */
   xsp = __eval_xpr(xp);
   __eval_tskassign_rhsexpr(xsp, (c_np->ntyp == N_REAL), c_np->nwid,
    (xp->is_real == 1), (xp->has_sign == 1), c_np->n_2state, 
    (c_np->ntyp == N_STRING));
  }
 set_dpi_arg_from_xstk(xsp, tpp, argi, dap, a_u_tab);
 
 /* SJM 11-17-10 - only eval actual arg, for input or inout args */
 if (tpp->trtyp != IO_OUT) __pop_xstk();
}


/*
 * routine to set argi position value into dpi arg union field (may malloc)
 * for DPI export after verilog t/f has run from the stored verilog t/f
 * variable (name of function for function return val)
 *
 * no size conversion needed here
 */
static void set_dpi_arg_from_net(struct task_pin_t *tpp, int32 argi,
 struct dpiarg_t *dap, union adpi_u *a_u_tab)
{
 struct net_t *c_np;
 struct xstk_t *xsp;

 /* this is the Verilog side dpi import/export c side net */
 c_np = tpp->tpsy->el.enp;

 /* for non output, eval arg onto top of xstk */
 /* output easy - either do nothing or malloc if need ptr */
 /* get value of non outputs - need size conversion */
 xsp = NULL;
 if (tpp->trtyp != IO_OUT) 
  {
   push_xstk_(xsp, c_np->nwid);
   __ld_wire_val_wrds(xsp->ap, xsp->bp, c_np);
  }
 /* even for outputs, need to call in case need to malloc arg union tab */
 set_dpi_arg_from_xstk(xsp, tpp, argi, dap, a_u_tab);
 
 /* SJM 11-17-10 - only eval actual arg, for input or inout args */
 if (tpp->trtyp != IO_OUT) __pop_xstk();
}

/*
 * routine to set the dpi arg union val for argi from pushed xstk value
 * that is know to be right width
 */
static void set_dpi_arg_from_xstk(struct xstk_t *xsp, struct task_pin_t *tpp,
 int32 argi, struct dpiarg_t *dap, union adpi_u *a_u_tab)
{
 int32 nbytes;
 double d1;
 struct net_t *c_np;
 char *cp;

 c_np = tpp->tpsy->el.enp;
 switch (dap->arg_srep) {
  case SR_SCAL:
   if (tpp->trtyp != IO_OUT)
    {
     /* SJM 10-24-10 - for narrow do not need to malloc */
     /* SJM 11-14-10 - shift of b part was right - should be left */
     a_u_tab[argi].sv_ch = (unsigned char)
      (xsp->ap[0] & 1) | ((xsp->bp[0] & 1) << 1);
    }
   break;
  case SR_SCAL2S:
   if (tpp->trtyp != IO_OUT)
    {
     a_u_tab[argi].sv_ch = (unsigned char) (xsp->ap[0] & 1);
    }
   break;
  case SR_DPI_BYTE:
   if (tpp->trtyp != IO_OUT)
    {
     a_u_tab[argi].sv_ch = (unsigned char) (xsp->ap[0] & 0xff);
    }
   break;
  case SR_DPI_CINT:
   if (tpp->trtyp != IO_OUT)
    {
//SJM 10-24-10 - LOOKATME? - think don't need the mask
     a_u_tab[argi].sv_i = (int) xsp->ap[0];
    }
   break;
  case SR_DPI_SHORTCINT:
   if (tpp->trtyp != IO_OUT)
    {
//SJM 10-24-10 - LOOKATME? - think don't need the mask
     a_u_tab[argi].sv_shrti = (short int) xsp->ap[0];
    }
   break;
  case SR_DPI_LONGCINT:
   if (tpp->trtyp != IO_OUT)
    {
#ifdef __CVC32__ 
     a_u_tab[argi].sv_lngi = ((long long int) xsp->ap[0])
      | (((long long int) xsp->ap[1]) << WBITS);
#else
     a_u_tab[argi].sv_lngi = (long long int) xsp->ap[0];
#endif
    }
   break;
  case SR_DPI_REAL:
   if (tpp->trtyp != IO_OUT)
    {
     memcpy(&(d1), xsp->ap, sizeof(double));
     a_u_tab[argi].sv_d = d1;
    }
   break;
  case SR_DPI_CHANDLE:
   /* no size here - so no malloc */
   /* SJM 10-24-10 - ap is ptr size so adjusts for 64 bit cvc */
   a_u_tab[argi].sv_ptr = (void *) xsp->ap[0];
   break;
  case SR_BIT2S:
   /* SJM 10-24-10 - now always alloc */  
   /* wrd bytes and w len macro adjust for 64 bit cvc */
   nbytes = WRDBYTES*wlen_(c_np->nwid);
   dap->arg_nbytes = nbytes;
   a_u_tab[argi].sv_ptr = (void *) __my_malloc(nbytes);
//SJM 10-24-10 - LOOKATME? - think for 2 state, do not reorder
   if (tpp->trtyp != IO_OUT)
    {
     memcpy(a_u_tab[argi].sv_ptr, xsp->ap, nbytes);
    }   
   break;
  case SR_VEC:
   /* SJM 04-24-10 - now always mallocing */
   nbytes = 2*WRDBYTES*wlen_(c_np->nwid);
   a_u_tab[argi].sv_ptr = (void *) __my_malloc(nbytes);
   dap->arg_nbytes = nbytes;
   /* SJM 11-11-10 - need 32 bit chunck wlen not actual wide here */ 
   map_to_cside_ab((unsigned int *) a_u_tab[argi].sv_ptr, xsp->ap, 
    wlen32_(c_np->nwid));
   break;
  case SR_STRING:
   /* AIV 01/04/10 - need to handle SV strings */
   if (tpp->trtyp != IO_OUT)
    {
     nbytes = (xsp->xslen/8)+1;
     dap->arg_nbytes = nbytes;
     /* create c-style string to pass in */
     cp = __alloc_vval_to_cstr(xsp->ap, xsp->xslen, FALSE, FALSE);
     a_u_tab[argi].sv_ptr = (void *) __my_malloc(nbytes);
     strcpy(a_u_tab[argi].sv_ptr, cp);
     __my_free(cp, nbytes);
    }
   else
    {
     nbytes = DPI_DFLT_STRING_BYTES;
     dap->arg_nbytes = nbytes;
     a_u_tab[argi].sv_ptr = (void *) __my_malloc(nbytes);
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * routine to set argi position value into dpi arg union field (may malloc)
 * array both 32 and 64 bits cases
 *
 * array must be simpl net name
 */
static void arr_set_dpi_arg(struct expr_t *argxp, struct task_pin_t *tpp,
 int32 argi, struct dpiarg_t *dap, union adpi_u *a_u_tab)
{
 int32 ai, wlen, wlen32, ptab_bytes, dat_bytes, wi;
 unsigned char *chp;
 int *intp;
 unsigned int *uip, *uip2;
 unsigned int **uipp;
 short int *hip;
 long long int *lip;
 double *dip;
 word32 *wp, *wp2;
 word32 **wpp;
 struct net_t *c_np, *ver_np;
 struct xstk_t *xsp;

 /* DBG remove -- */
 if (argxp->lu.x->optyp != ID) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 ver_np = argxp->lu.x->lu.sy->el.enp;

 /* this is the c side dpi import/export c side net */
 c_np = tpp->tpsy->el.enp;
 /* DBG remove -- */
 if (!c_np->n_isarr || !ver_np->n_isarr) __misc_terr(__FILE__, __LINE__);
 if (c_np->ntyp != ver_np->ntyp) __misc_terr(__FILE__, __LINE__);
 if (c_np->nwid != ver_np->nwid) __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 switch (dap->arg_srep) {
  case SR_SCAL: case SR_SCAL2S:
   /* SJM 11-19-10 - scalar arrays are unpacked for c side into words */
   /* maybe wrong should be array of svScalar */
   chp = (unsigned char *) __my_malloc(c_np->arr_num_els);
   dap->arg_nbytes = c_np->arr_num_els;
   a_u_tab[argi].sv_ptr = (void *) chp;
   
   if (tpp->trtyp != IO_OUT)
    {
     push_xstk_(xsp, 1);
     for (ai = 0; ai < ver_np->arr_num_els; ai++)
      {
       /* for both 2 state and 4 state, scalar arrays stored as 2 bits */ 
       /* with the b bit always 0 for 2 state */
       __ld_arr_val(xsp, NULL, ver_np, ai, NULL);
       if (dap->arg_srep == SR_SCAL)
        {
         chp[ai] = (unsigned char) ((xsp->ap[0] & 1) | (xsp->bp[0] & 1) << 1);
        } 
       else chp[ai] = (unsigned char) (xsp->ap[0] & 1);
      }
     __pop_xstk();
    } 
   break;
  case SR_DPI_BYTE:
   chp = (unsigned char *) __my_malloc(ver_np->arr_num_els);
   dap->arg_nbytes = ver_np->arr_num_els;
   a_u_tab[argi].sv_ptr = (void *) chp;
   if (tpp->trtyp != IO_OUT)
    {
     push_xstk_(xsp, BYTEBITS);
     for (ai = 0; ai < ver_np->arr_num_els; ai++)
      {
       __ld_arr_val(xsp, NULL, ver_np, ai, NULL);
       chp[ai] = (unsigned char) (xsp->ap[0] & 0xff);
      }
     __pop_xstk();
    }
   break;
  case SR_DPI_CINT:
   dap->arg_nbytes = ver_np->arr_num_els*sizeof(int);
   intp = (int *) __my_malloc(dap->arg_nbytes);
   a_u_tab[argi].sv_ptr = (void *) intp;
   if (tpp->trtyp != IO_OUT)
    {
     push_xstk_(xsp, CINTBITS);
     for (ai = 0; ai < ver_np->arr_num_els; ai++)
      {
       __ld_arr_val(xsp, NULL, ver_np, ai, NULL);
#ifdef __CVC32__
       intp[ai] = (int) xsp->ap[0];
#else
       intp[ai] = (int) (xsp->ap[0] & ALL1HW);
#endif
      }
     __pop_xstk();
    }
   break;
  case SR_DPI_SHORTCINT:
   dap->arg_nbytes = ver_np->arr_num_els*sizeof(short int);
   hip = (short int *) __my_malloc(ver_np->arr_num_els*sizeof(short int));
   a_u_tab[argi].sv_ptr = (void *) hip;
   if (tpp->trtyp != IO_OUT)
    {
     push_xstk_(xsp, SHORTCINTBITS);
     for (ai = 0; ai < ver_np->arr_num_els; ai++)
      {
       __ld_arr_val(xsp, NULL, ver_np, ai, NULL);
       hip[ai] = (short int) xsp->ap[0] & 0xffff;
      }
     __pop_xstk();
    }
   break;
  case SR_DPI_LONGCINT:
   dap->arg_nbytes = ver_np->arr_num_els*sizeof(long long int);
   lip = (long long int *)
    __my_malloc(ver_np->arr_num_els*sizeof(long long int));
   a_u_tab[argi].sv_ptr = (void *) lip;
   if (tpp->trtyp != IO_OUT)
    {
     push_xstk_(xsp, LONGCINTBITS);
     for (ai = 0; ai < ver_np->arr_num_els; ai++)
      {
       __ld_arr_val(xsp, NULL, ver_np, ai, NULL);
#ifdef __CVC32__
       lip[ai] = ((long long int) xsp->ap[0])
        | (((long long int) xsp->ap[1]) << WBITS);
#else
       lip[ai] = (long long int) xsp->ap[0];
#endif
      }
     __pop_xstk();
    }
   break;
  case SR_DPI_REAL:
   dap->arg_nbytes = ver_np->arr_num_els*sizeof(double);
   dip = (double *) __my_malloc(ver_np->arr_num_els*sizeof(double));
   a_u_tab[argi].sv_ptr = (void *) dip;
   if (tpp->trtyp != IO_OUT)
    {
     push_xstk_(xsp, REALBITS);
     for (ai = 0; ai < ver_np->arr_num_els; ai++)
      {
       __ld_arr_val(xsp, NULL, ver_np, ai, NULL);
       memcpy(&(dip[ai]), xsp->ap, sizeof(double));
      }
     __pop_xstk();
    }
   break;
  case SR_BIT2S:
   wlen = wlen_(ver_np->nwid);
   wpp = NULL;
   wp = NULL;
   if (wlen32_(ver_np->nwid) == 1)
    {
     dap->arg_nbytes = ver_np->arr_num_els*wlen*WRDBYTES;
     wp = (word32 *) __my_malloc(dap->arg_nbytes); 
     a_u_tab[argi].sv_ptr = (void *) wp;
    }
   else
    {
     /* SJM 11-19-10 - following AIV's algorithm, for wider than WBITS */
     /* array, will pass a tab of ptrs to array element size a parts */
     /* the values are in the pointed to a parts */
     ptab_bytes = ver_np->arr_num_els*sizeof(unsigned int *);
     dat_bytes = wlen*WRDBYTES;
     dap->arg_nbytes = ptab_bytes + ver_np->arr_num_els*dat_bytes;
     wpp = (word32 **) __my_malloc(dap->arg_nbytes);
     a_u_tab[argi].sv_ptr = (void *) wpp;
     /* SJM 11-20-10 - only a part stored here - if more than 32 bits */ 
     /* even if cvc64 need the ptrs - but area still 64 bits chunks then */
     wi = ver_np->arr_num_els;
     for (ai = 0; ai < ver_np->arr_num_els; ai++, wi += wlen)
      {
       wpp[ai] = (word32 *) &(wpp[wi]);
      }
    }
   if (tpp->trtyp != IO_OUT)
    {
     push_xstk_(xsp, ver_np->nwid);
     for (ai = 0; ai < ver_np->arr_num_els; ai++)
      {
       __ld_arr_val(xsp, NULL, ver_np, ai, NULL);
       /* SJM 11-19-20 - for narrower than WBITS (64 for cvc64), there is */
       /* no tab of ptrs to the arr el values, but for wider need ptab */
       if (wlen32_(ver_np->nwid) == 1) wp2 = &(wp[ai*wlen]);
       else wp2 = wpp[ai];
       memcpy(wp2, xsp->ap, wlen*WRDBYTES);
       wi = ver_np->arr_num_els;
      }
     __pop_xstk();
    }
   break;
  case SR_VEC:
   wlen32 = wlen32_(ver_np->nwid);
   uip = NULL;
   uipp = NULL;
   if (wlen32 == 1)
    {
     dap->arg_nbytes = ver_np->arr_num_els*2*wlen32*WRDBYTES;
     uip = (unsigned int *) __my_malloc(dap->arg_nbytes); 
     a_u_tab[argi].sv_ptr = (void *) uip;
    }
   else
    {
     /* SJM 11-19-10 - following AIV's algorithm, for wider than WBITS */
     /* array, will pass a tab of ptrs to array element size a/b parts */
     /* whose values are the 32 bit <a,b><a,b> jumbled chunks */
     ptab_bytes = ver_np->arr_num_els*sizeof(unsigned int *);
     dat_bytes = 2*wlen32*WRDBYTES;
     dap->arg_nbytes = ptab_bytes + ver_np->arr_num_els*dat_bytes;
     uipp = (unsigned int **) __my_malloc(dap->arg_nbytes);
     a_u_tab[argi].sv_ptr = (void *) uipp;
     wi = ver_np->arr_num_els;
     for (ai = 0; ai < ver_np->arr_num_els; ai++, wi += 2*wlen32)
      {
       uipp[ai] = (unsigned int *) &(uipp[wi]);
      }
    }
   if (tpp->trtyp != IO_OUT)
    {
     push_xstk_(xsp, ver_np->nwid);
     for (ai = 0; ai < ver_np->arr_num_els; ai++)
      {
       __ld_arr_val(xsp, NULL, ver_np, ai, NULL);
       if (wlen32 == 1) uip2 = &(uip[2*ai*wlen32]); else uip2 = uipp[ai];
       /* SJM 11-19-10 - needs to jumble to 32 bit chunk <a,b><a,b> */ 
       map_to_cside_ab(uip2, xsp->ap, wlen32_(c_np->nwid));
      } 
     __pop_xstk();
    }
   break;
//SJM 09-28-10 - notice arrays of SR_DPI CHANDLE illegal 
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * routine to get non array inout and output values into xstk
 * caller will use proc assign to handle the chg store if needed
 *
 * only called if output or inout
 * SJM 11-14-10 - for inout args, value for non sv_ptr still in the
 * union fixed value - wrapper passes the addr to c side
 */
static struct xstk_t *get_dpi_arg(int32 argi, struct dpiarg_t *dap,
 union adpi_u *a_u_tab, int32 argwid)
{
 int32 wlen, ubits;
 char *cp;
 /* notice word32 is actually word64 for 64 bit versions of CVC */
 struct xstk_t *xsp;

 xsp = NULL;
 switch (dap->arg_srep) {
  case SR_SCAL:
   /* know not ptr - push the byte onto stack and convert to a/b */
   push_xstk_(xsp, 1);
   xsp->ap[0] = (word32) (a_u_tab[argi].sv_ch & 1); 
   /* SJM 11-14-10 - was shift left instead of right */
   xsp->bp[0] = (word32) ((a_u_tab[argi].sv_ch >> 1) & 1);
   break;
  case SR_SCAL2S:
   push_xstk_(xsp, 1);
   xsp->ap[0] = (word32) (a_u_tab[argi].sv_ch & 1); 
   xsp->bp[0] = 0;
   break;
  case SR_DPI_BYTE:
   push_xstk_(xsp, BYTEBITS);
   /* on the Verilog side, byte looks like 8 bit 2 state */ 
   xsp->ap[0] = (word32) (a_u_tab[argi].sv_ch & 0xff);
   xsp->bp[0] = 0;
   break;
  case SR_DPI_SHORTCINT:
   push_xstk_(xsp, SHORTCINTBITS);
   xsp->ap[0] = (word32) a_u_tab[argi].sv_shrti;
   xsp->bp[0] = 0;
   break;
  case SR_DPI_CINT:
   push_xstk_(xsp, CINTBITS);
   xsp->ap[0] = (word32) a_u_tab[argi].sv_i;
   xsp->bp[0] = 0;
   break;
  case SR_DPI_LONGCINT:
   push_xstk_(xsp, LONGCINTBITS);
#ifdef __CVC32__
   xsp->ap[0] = (word32) ((a_u_tab[argi].sv_lngi) & ALL1W);
   xsp->ap[1] = (word32) ((a_u_tab[argi].sv_lngi >> WBITS) & ALL1W);
   xsp->bp[0] = 0;
   xsp->bp[1] = 0;
#else
   xsp->ap[0] = (word64) a_u_tab[argi].sv_lngi;
   xsp->bp[0] = 0;
#endif
   break;
  case SR_DPI_REAL:
   push_xstk_(xsp, REALBITS);
   memcpy(xsp->ap, &(a_u_tab[argi].sv_d), sizeof(double));
#ifndef __CVC32__
   xsp->bp[0] = 0;
#endif
   break;
  case SR_DPI_CHANDLE:
   /* SJM 10-24-10 - wbits is ptr size */
   push_xstk_(xsp, WBITS);
   /* -- */
   xsp->ap[0] = (word32) a_u_tab[argi].sv_ptr;  
   xsp->bp[0] = 0;
   a_u_tab[argi].sv_ptr = NULL;
   break;
  case SR_BIT2S:
   /* DBG remove -- */
   if (dap->arg_nbytes == 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   push_xstk_(xsp, argwid);
   memcpy(xsp->ap, a_u_tab[argi].sv_ptr, dap->arg_nbytes);
   wlen = wlen_(argwid);
   ubits = ubits_(argwid);
   /* AIV 12/27/10 - need to mask high bits - from copy */
   xsp->ap[wlen - 1] &= __masktab[ubits];
   memset(xsp->bp, 0, dap->arg_nbytes);
   __my_free(a_u_tab[argi].sv_ptr, dap->arg_nbytes);
   a_u_tab[argi].sv_ptr = NULL;
   dap->arg_nbytes = 0;   
   break;
  case SR_VEC:
   /* SJM 10-24-10 - works because size is 2 times wlen for a and b parts */
   /* DBG remove -- */
   if (dap->arg_nbytes == 0) __misc_terr(__FILE__, __LINE__);
   /* --- */
   push_xstk_(xsp, argwid);
   /* SJM 11-11-10 - need map from <a,b><a,b>... back to our a/b */
   map_to_verside_vec(xsp->ap, a_u_tab[argi].sv_ptr, wlen_(argwid));
   __my_free(a_u_tab[argi].sv_ptr, dap->arg_nbytes);
   wlen = wlen_(argwid);
   ubits = ubits_(argwid);
   /* AIV 12/27/10 - need to mask high bits - from copy */
   xsp->ap[wlen -1] &= __masktab[ubits];
   xsp->bp[wlen -1] &= __masktab[ubits];

   a_u_tab[argi].sv_ptr = NULL;
   dap->arg_nbytes = 0;   
   break;
  case SR_STRING:
   cp = a_u_tab[argi].sv_ptr;
   /* convert to c string to vval */
   xsp = __cstr_to_vval(cp);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(xsp);
}

/*
 * ROUTINES FOR VER SIDE STORE OF IMPORT C ROUTINE OUTS AND INOUTS
 */

/*
 * routine to chg (if needed) store every returned cell from arr arg
 * caller will use proc assign for every cell to handle the chg store if needed
 */
static void st_dpi_arg(struct expr_t *argxp, int32 argi, struct dpiarg_t *dap,
 union adpi_u *a_u_tab)
{
 int32 ai;
 struct net_t *ver_np;
 struct xstk_t *xsp;

 /* DBG remove -- */
 if (argxp->lu.x->optyp != ID) __misc_terr(__FILE__, __LINE__); 
 /* --- */
 ver_np = argxp->lu.x->lu.sy->el.enp;
 /* this is the c side dpi import/export c side net */
 for (ai = 0; ai < ver_np->arr_num_els; ai++)
  {
   if (dap->arg_iotyp == IO_IN)
    {
     /* DBG ---
     if (dap->arg_nbytes == 0) __misc_terr(__FILE__, __LINE__); 
     --- */  
    }

   xsp = push_dpi_c_side_arr_cell(argi, ai, dap, a_u_tab, ver_np);
   if (ver_np->nchg_nd_chgstore)
    {
     __chg_st_arr_val(ver_np, NULL, ai, xsp->ap, xsp->bp);
     if (__lhs_changed) record_sel_nchg_(ver_np, ai, ai);
    }
   else
    {
     __st_arr_val(ver_np, NULL, ai, xsp->ap, xsp->bp, xsp->xslen);
    }
   __pop_xstk();
  }
 /* DBG remove --- 
 if (dap->arg_nbytes == 0) __misc_terr(__FILE__, __LINE__);
 --- */  
 __my_free(a_u_tab[argi].sv_ptr, dap->arg_nbytes);
 dap->arg_nbytes = 0;
}

/*
 * routine to copy one array cell returned (out/inout) value to xstk
 */
static struct xstk_t *push_dpi_c_side_arr_cell(int32 argi, int32 arri,
 struct dpiarg_t *dap, union adpi_u *a_u_tab, struct net_t *ver_np)
{
 struct xstk_t *xsp;
 int32 wlen32;
 unsigned char *chp;
 short int *hip;
 int *cip;
 unsigned int *uip, *uip2;
 unsigned int **uipp;
 long long int *lip;
 word32 *wp, *wp2;
 word32 **wpp;
 double *dp;

 switch (dap->arg_srep) {
  case SR_SCAL:
   push_xstk_(xsp, 1);
   chp = (unsigned char *) a_u_tab[argi].sv_ptr;
   xsp->ap[0] = chp[arri] & 1;
   xsp->bp[0] = (chp[arri] >> 1) & 1;
   break;
  case SR_SCAL2S:
   push_xstk_(xsp, 1);
   chp = (unsigned char *) a_u_tab[argi].sv_ptr;
   xsp->ap[0] = chp[arri] & 1;
   xsp->bp[0] = 0;
   break;
  case SR_DPI_BYTE:
   push_xstk_(xsp, BYTEBITS);
   chp = (unsigned char *) a_u_tab[argi].sv_ptr;
   xsp->ap[0] = chp[arri];
   xsp->bp[0] = 0;
   break;
  case SR_DPI_SHORTCINT:
   push_xstk_(xsp, SHORTCINTBITS);
   hip = (short int *) a_u_tab[argi].sv_ptr;
   xsp->ap[0] = hip[arri];
   xsp->bp[0] = 0;
   break;
  case SR_DPI_CINT:
   push_xstk_(xsp, CINTBITS);
   cip = (int *) a_u_tab[argi].sv_ptr;
   xsp->ap[0] = cip[arri];
   xsp->bp[0] = 0;
   break;
  case SR_DPI_LONGCINT:
   push_xstk_(xsp, LONGCINTBITS);
   lip = (long long int *) a_u_tab[argi].sv_ptr;
#ifdef __CVC32__
   xsp->ap[0] = ((word32) lip[arri]);
   xsp->ap[1] = ((word32) (lip[arri] >> WBITS));
   xsp->bp[0] = 0;
   xsp->bp[1] = 0;
#else
   xsp->ap[0] = (word64) lip[arri];
   xsp->bp[0] = 0;
#endif
   break;
  case SR_DPI_REAL:
   push_xstk_(xsp, REALBITS);
   dp = (double *) a_u_tab[argi].sv_ptr;
   memcpy(xsp->ap, &(dp[arri]), sizeof(double));
#ifndef __CVC32__
   xsp->bp[0] = 0;
#endif
   break;
  case SR_BIT2S:
   wlen32 = wlen32_(ver_np->nwid);
   push_xstk_(xsp, ver_np->nwid);

   /* for wider than WBITS (64 for cvc64), alloc tab of ptrs to the */
   /* a part multi-word vals */
   if (wlen32 == 1)
    {
     wp = (word32 *) a_u_tab[argi].sv_ptr;
     wp2 = &(wp[wlen32*arri]);
    } 
   else
    {
     wpp = (word32 **) a_u_tab[argi].sv_ptr;
     /* SJM 11-20-10 - this was wrong, needs to be arri */
     wp2 = wpp[arri];
    }
   memcpy(xsp->ap, wp2, wlen32*WRDBYTES);
   break;
  case SR_VEC:
   wlen32 = wlen32_(ver_np->nwid);
   push_xstk_(xsp, ver_np->nwid);
   /* SJM 11-19-10 - for wider than 32 bits arr els, alloc tab of ptrs */
   /* with each ptr pointing to that elements <a,b><a,b> ... area */
   if (wlen32 == 1)
    {
     uip = (unsigned int *) a_u_tab[argi].sv_ptr;
     uip2 = &(uip[2*wlen32*arri]);
    } 
   else
    {
     uipp = (unsigned int **) a_u_tab[argi].sv_ptr;
     uip2 = uipp[arri];
    }
   map_to_verside_vec(xsp->ap, uip2, wlen_(ver_np->nwid));
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(xsp);
}

/*
 * ROUTINES TO ASSIGN C SIDE UNION IN/INOUTS TO VER SIDE VALS AND INVOKE T/F
 */

/*
 * proc called by C wrapper routine for export Verilog T/Fs to store Verilog
 * T/F values from C union and invoke ver task or call ver func
 */
extern void __call_export_tf_wrapper(char *export_tf_nam,
 union adpi_u *cside_a_u_tab)
{
 int32 ai, argwid, numargs;
 struct sy_t *tsksyp;
 struct task_t *tskp;
 struct task_pin_t *tpp;
 struct net_t *arg_np;
 struct xstk_t *xsp;
 struct dpi_t *dpip;
 struct dpiarg_t *dap;
 struct mod_t *mdp;

 mdp = get_inst_mod_();
 if ((tsksyp = __zget_sym(export_tf_nam, mdp->msymtab->stsyms,
  mdp->msymtab->numsyms)) == NULL)
  {
   __sgferr(4892, "export DPI task/function %s undefined on Verilog side in module %s",
    export_tf_nam, mdp->msym->synam);
   return;
  }
 tskp = tsksyp->el.etskp;
 dpip = tskp->tf_dpip;
 numargs = dpi_cnt_tskpins(tskp);
 /* SJM 11-29-10 - function starts at 1, task 0 - it was backwards */
 if (tskp->tsktyp == FUNCTION) { ai = 1; tpp = tskp->tskpins->tpnxt; }
 else { ai = 0; tpp = tskp->tskpins; }
 for (; ai < numargs; ai++, tpp = tpp->tpnxt)
  {
   /* for output ports nothing to do */
   if (tpp->trtyp == IO_OUT) continue;

   dap = &(dpip->dpi_ainfo[ai]); 
   /* know will not see arg net array here - checked earlier */
   /* DBG remove -- */
   if (dap->arg_arr) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* SJM 11-29-10 - this was always wrongly getting 2nd arg */
   arg_np = tpp->tpsy->el.enp;
   argwid = arg_np->nwid;
   xsp = get_dpi_arg(ai, dap, cside_a_u_tab, argwid);
   __st_val(arg_np, xsp->ap, xsp->bp, xsp->xslen);
   __pop_xstk();
  }
 __exec_dpi_exported_tf(tskp);

 /* dpi exported verilog tf exec with results in task pin args */
 /* if func 0th arg has return value */
 if (tskp->tsktyp == FUNCTION) { ai = 0; tpp = tskp->tskpins->tpnxt; }
 else { ai = 1; tpp = tskp->tskpins; }
 for (; ai < numargs; ai++, tpp = tpp->tpnxt)
  {
   /* SJM 11-22-10 - for input args do not move result of ver t/f exec back */
   /* into union so c routine will see args - since in, nothing passed up */
   if (tpp->trtyp == IO_IN) continue;

   dap = &(dpip->dpi_ainfo[ai]); 
   /* DBG remove -- */
   if (dap->arg_arr) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* SJM 11-29-10 - this was always wrongly getting 2nd arg */
   arg_np = tpp->tpsy->el.enp;
   argwid = arg_np->nwid;
   set_dpi_arg_from_net(tpp, ai, dap, cside_a_u_tab);
  }
}

/*
 * routine to exec a dpi function
 */
extern void __exec_dpi_exported_tf(struct task_t *tskp) 
{
 int32 savslin_cnt, savsfnam_ind, nd_thdfree, dowhile;
 struct st_t *stp;

 /* SJM 02-18-09 - this must run with __idp set */
 /* DBG remove -- */
 if (__idp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */
 
 /* for decl. rhs, maybe no thrd - bld for 1st call else take over cur. */ 
 nd_thdfree = FALSE;
 if (__cur_thd == NULL)
  {
   __cur_thd = __alloc_thrd();
   __cur_thd->th_idp = __idp;
   nd_thdfree = TRUE;
  }

 /* this is dynamic call list */
 if (++__fcspi >= __maxfcnest) __grow_fcstk();
 __fcstk[__fcspi] = tskp;
 savslin_cnt = __slin_cnt;
 savsfnam_ind = __sfnam_ind;

 /* cannot schedule and resume inside func. so suspend and schedule */
 /* then unsuspend and cancel event */
 stp = tskp->tskst;
 __cur_thd->thnxtstp = stp;

 __stmt_suspend = FALSE;
 __exec_stmts(stp, &dowhile, FALSE);
 
 __slin_cnt = savslin_cnt;
 __sfnam_ind = savsfnam_ind;
 __fcspi--;

 if (nd_thdfree)
  {
   __my_free(__cur_thd, sizeof(struct thread_t));
   __cur_thd = NULL;
  } 
}

/*
 * ROUTINES FOR CONVERTING BETWEEN DPI VER SIDE AND C SIDE VALUES 
 */

// ===========================================================
/*
 * src read coding:
 *
 * 1. all non scalar 2 and 4 state values stored as vector h:0
 * 2. net n_2state used to indicate no b part
 * 3. scalar will have n_isavec on but stored as WBITS
 *    either 2 words if not 2 state or 1 word if 2 state
 *
 * coding of dpi c side non array values: 
 *
 * scalars - byte
 * cint - 32 bit int
 * long cint - 64 bit int
 * short cint - 16 bit int
 * real - double
 * bit - 2state - packed as 32 bit words even for cvc64 
 * vec - 4state - packed as <a,b><a,b> 32 bit chunks even for cvc64
 * chandle - ptr (either 32 bit or 64 bit if 64 bit)
 *
 * coding of dpi array values: 
 * - same as non arrays except
 * 1) scalars always packed into 2 bit vectors (32 or 64 bit WBITS chunks) 
 *    -- for 2 state 2nd always 0
 * 2) 2 state > 1 bit width always coded in WBITS chunks even <WBITS/2
 * 3) 4 state code in byte, then hword, then word (WBITS for both so wider
 *    for cvc64)
 * 4) wider than WBITS/2 each is WBITS (not 32 for cvc64) chunks
 *    -- need <a,b><a,b> conversions and  64 bit chunks
 *
 * c side coded as arrays of cint chunks concenated side by side
 * using non array c side storage
 *
 * scalars/byte is char array, but bit [7:0] is 32 bit chunks for 2 state
 * 4 state is same 32 bit chunks one after the other but 
 */
// ===========================================================

#ifdef __CVC32__
/*
 * map 4 state 32 bit cvc a/b value to c side 32 bit chunk <a><b><a><b> ...
 *
 * notice int32 always int that is also 32 bits for 64 abi
 * nip size must be same as owp which is 2*wlen32
 */
static void map_to_cside_ab(unsigned int *nup, word32 *owp, int32 wlen32)
{
 int32 wi, si;
 word32 *wpb;

 wpb = &(owp[wlen32]);
 for (wi = 0, si = 0; wi < wlen32; si += 2, wi++)
  {
   nup[si] = (unsigned int) owp[wi];
   nup[si + 1] = (unsigned int) wpb[wi];
  }
}

/*
 * map 4 state <a><b><a><b>... to cvc verilog side separate a/b vecs
 * 32 bit version
 */
static void map_to_verside_vec(word32 *nwp, unsigned int *nup, int32 wlen32)
{
 int32 wi, si;
 word32 *nwpb;

 nwpb = &(nwp[wlen32]);
 for (wi = 0, si = 0; si < wlen32; si++, wi += 2)
  {
   nwp[si] = (word32) nup[wi]; 
   nwpb[si] = (word32) nup[wi + 1]; 
  }
}
#else
/*
 * map 4 state 64 bit cvc a/b value to c side 32 bit chunk <a><b><a><b> ...
 *
 * here WBITS is 64 and both word32 and word64 are really 64 bits 
 */
static void map_to_cside_ab(unsigned int *nup, word64 *owp, int32 wlen32)
{
 int32 wi, si;
 unsigned int *wb32p, *ow32p;

 /* AIV 12/20/10 - just need to cast these to int 32 and do normal 32-bit */
 /* version */
 if (wlen32 == 1) wb32p = (unsigned int *) &(owp[1]);
 else wb32p = (unsigned int *) &(owp[wlen32/2]);

 ow32p = (unsigned int *) owp;
 for (wi = 0, si = 0; wi < wlen32; si += 2, wi++)
  {
   nup[si] = (unsigned int) ow32p[wi];
   nup[si + 1] = (unsigned int) wb32p[wi];
  }
}

/*
 * map 4 state <a><b><a><b>... to cvc verilog side separate a/b vecs
 * 64 bit version
 */
static void map_to_verside_vec(word64 *nwp, unsigned int *nup, int32 wlen64)
{
 int32 wi, si;
 word64 *nwpb;

 nwpb = &(nwp[wlen64]);
 for (wi = 0, si = 0; si < wlen64; si++, wi += 4)
  {
   nwp[si] = ((word64) nup[wi]) | (((word64) nup[wi + 2]) << CINTBITS);
   nwpb[si] = ((word64) nup[wi + 1]) | (((word64) nup[wi + 3]) << CINTBITS);
  }
}
#endif

/*
 * ROUTINES TO FILL THE DPI RECORD AND ALLOC/FILL ARG INFO TAB
 */

/*
 * routine to prepare dpi - 1st step in load phase only if there are
 * dpi import/export routines and only if interp option on
 *
 * SJM 10-07-10 - now only called if at least one dpi t/f
 * SJM 11-28-10 - now only called if dpi used
 */
extern void __prep_dpi(void)
{
 char tmpname[RECLEN], cmd[RECLEN];

 fill_all_dpi_recs();

 /* if compiled this is compiled in - just return */
 if (__compiled_sim && __running_cvc_exe) return;

 /* SJM 02-07-13 - now one place to set prefix used instead of OS tmp */
 __setstr_objdir_path();

 sprintf(tmpname, "%s/__dpi-XXXXXX", __objdir_path);
 if (__get_tmpfnam(tmpname) == -1)
  {
   __pv_err(4877, "unable to write open tmp DPI interp wrapper file %s", 
    tmpname);  
   return;
  }
 /* AIV 12/30/10 - empty file opened to make sure can write - must be */
 /* removed as well */
 sprintf(cmd, "rm %s", tmpname);
 system(cmd);

 __dpi_interp_wrapper_fnam = __pv_stralloc(tmpname);


//SJM 12-28-10 - FIXME?? - should not use fixed name for pipe file
 /* SJM 12-28-10 - normal mode is to use pipe to make the wrapper .so lib */
 if (!__use_interp_dpi_mk) 
  {
   /* AIV 12/30/10 - no need to make the .c file if piping */
   gen_dpi_wrapper_pipe();
   /* only need .so for +interp */
   if (!__compiled_sim) gen_rt_dpi_interp_pipe_lib();
  }
 else 
  {
   gen_dpi_wrapper_file();
   gen_rt_dpi_interp_mkfil_and_compile();
  }

 if (__pv_err_cnt != 0) return; 
 if (!__compiled_sim)
  {
   linkin_interp_dpi_dlsyms();
  }

 /* if user selected +write_dpi_hdrs option, write dpi c hdrs to a file */
 if (__wr_dpi_c_hdrs) wr_dpihdrs();
}

/*
 * proc to set obj dir path - needs to be set in early dpi prep even if
 * not compiled sim 
 *
 * SJM 02-07-13 - now have one routine to do the setting easier to debug
 * also less problem with dpi_ mem alloc problems since copied into pre alloc wide
 *
 * this always sets - if set for dpi - will set str again right to same
 */
extern char *__setstr_objdir_path(void)
{
 /* SJM 02-07-13 - now making these large pre-alloced strings because if */
 /* problem with dpi mem alloc, now will not be over-written */

 /* SJM 02-07-13 - +work over-rides - is that right */
 if (__use_pwd_as_tmp) strcpy(__objdir_path, "./");
 /* AIV 07/16/12 - now allowing +usedir= to setting working directory */
 /* to use instead of OS tmp for temp work area */
 else if (strcmp(__usedir_cp, "") != 0) strcpy(__objdir_path, __usedir_cp);
 else  strcpy(__objdir_path, DEF_OBJ_DIR);

 return(__objdir_path);
}

/*
 * routine to handle dpi linking in with dlopen of the SV dpi libraries
 *
 * SJM 11-07-10 - nothing else needed the dlopen of every library means
 * when the c side routine is called, the dynamic linker will find the
 * symbol and link it in the first time
 */ 
static void linkin_interp_dpi_dlsyms(void)
{
 struct sv_lib_t *svlp;
 void *f_handle;
 char s1[RECLEN];

 /* first open the library from the generated c wrapper */
 /* SJM 12-29-10 - notice must not dlclose the interp dpi wrap lib */
 sprintf(s1, "%s.so", __dpi_interp_wrapper_fnam); 
 if ((f_handle = dlopen(s1, RTLD_LAZY | RTLD_GLOBAL)) == NULL)
  {
   __pv_err(4878,
    "unable to load +interp mode generated wrapper library %s: %s",
    s1, dlerror());
   return;
  }
 if ((__dpi_imp_interp_routp = dlsym(f_handle, DPI_IMP_INTERP_ROUT)) == NULL)
  {
   __pv_err(4879,
    "unable to find dpi +interp fixed c side import wrapper calls symbol %s: %s",
    DPI_IMP_INTERP_ROUT, dlerror());
   return;
  } 

 /* if has DPI .so libs need to dl open each so dlsym will work */
 /* SJM 11-07-10 - new algorithm just open all the sv libs and leave open */
 if (__sv_lib_hdrp != NULL)
  {
   for (svlp = __sv_lib_hdrp; svlp != NULL; svlp = svlp->svnxt)
    {
     if ((f_handle = dlopen(svlp->path, RTLD_LAZY | RTLD_GLOBAL)) == NULL)
      {
       __pv_err(4880,
        "unable to load SV dpi (in +interp mode) %s dynamic library: %s",
         svlp->path, dlerror());
       continue;
      }
    }
  }
}

/*
 * ROUTINES TO FILL DPI INTERP FIELDS
 */

/*
 * fill all dpi records and build the unerlying c stdlib arg types
 */
static void fill_all_dpi_recs(void)
{
 int32 dpi_ndx, ndpi_args;
 struct dpi_t *dpip;
 struct task_t *tskp;

 dpi_ndx = 1;
 for (dpip = __dpi_hdrp; dpip != NULL; dpip = dpip->dpinxt)
  {
   tskp = dpip->dpi_tskp;
   ndpi_args = dpi_cnt_tskpins(tskp);
   dpip->dpi_nargs = ndpi_args;

   alloc_init_dpi_arginfo(dpip, ndpi_args);
   fill_dpi_arginfo_tab(tskp);

   /* also set the index for the gen c file */
   dpip->dpi_proc_ndx = dpi_ndx++;  
  }
}

/*
 * allocate and initialize the dpi import/export descrpition record per
 * arg info struct
 */ 
static void alloc_init_dpi_arginfo(struct dpi_t *dpip, int32 nargs)
{
 int32 argi;
 struct dpiarg_t *dap;

 dpip->dpi_ainfo = (struct dpiarg_t *)
  __my_malloc(nargs*sizeof(struct dpiarg_t));
 for (argi = 0; argi < nargs; argi++)
  {
   dap = &(dpip->dpi_ainfo[argi]); 
   dap->ver_side_svtyp = SV_UNKN;
   dap->arg_srep = SR_DPI_UNKN;
   dap->arg_iotyp = IO_UNKN;
   dap->arg_arr = FALSE;
   /* SJM 11-17-10 - combined various need ptr wrapper args to nd lval */
   dap->nd_lval_ptr = FALSE;
   dap->arg_nbytes = 0;
  }
 /* SJM 11-03-10 - also alloc and init the arg value union table */
 dpip->arg_u_tab = (union adpi_u *) __my_malloc(nargs*sizeof(union adpi_u));
 for (argi = 0; argi < nargs; argi++)
  {
   dpip->arg_u_tab[argi].sv_ptr = NULL; 
  }
}
   
/*
 * proc to count number of declared Verilog task/function args
 *
 * notice a task with no args will still have 1 dpi ctyp tab arg
 */
static int32 dpi_cnt_tskpins(struct task_t *tskp) 
{
 int32 anum;
 struct task_pin_t *tpp;

 /* SJM 11-11-10 - number of args is really size of arg info tab */
 for (anum = 0, tpp = tskp->tskpins; tpp != NULL; tpp = tpp->tpnxt) anum++; 
 return(anum);
}

/*
 * fill dpi arg info array 
 *
 * atyp array has the underlying ctyp type for each DPI C func/task 
 * pos. 0 is func return val and unused for tasks
 *
 * can't fill the nd ptr fields yet because need to know storage representation
 */
static void fill_dpi_arginfo_tab(struct task_t *tskp)
{
 int32 ai, svtyp;
 struct dpi_t *dpip;
 struct task_pin_t *tpp;
 struct net_t *np;
 struct dpiarg_t *dap;
 
 dpip = tskp->tf_dpip;
 /* 0th arg for functions is return value, unused void for tasks */
 dap = &(dpip->dpi_ainfo[0]);
 /* SJM 11-17-10 - return value can't be lval unless actual sv ptr */
 dap->nd_lval_ptr = FALSE;
 if (tskp->tsktyp == FUNCTION)
  {
   /* SJM 11-11-10 - for func - must set arginfo here */ 
   /* arg 0 is always an output if it is a function */
   dap->arg_iotyp = IO_OUT;
   /* first arg is the return type for functions*/ 
   tpp = tskp->tskpins;
   np = tpp->tpsy->el.enp;
   /* DBG remove -- */
   if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
   /* -- */
   svtyp = get_ver_side_svtyp(np);
   dap->ver_side_svtyp = svtyp;
   /* fill the dpi srep field and set the nd*/
   set_ver_side_srep(np, dap);
   tpp = tpp->tpnxt;
   ai = 1;
  }
 else
  {
   /* task 1st arg is real first arg - not return value */
   /* no return arginfo */
   ai = 0;
   tpp = tskp->tskpins;
  }

 for (;tpp != NULL; tpp = tpp->tpnxt, ai++)
  {
   dap = &(dpip->dpi_ainfo[ai]);
   np = tpp->tpsy->el.enp;
   svtyp = get_ver_side_svtyp(np);
   dap->ver_side_svtyp = svtyp;
   dap->arg_iotyp = np->iotyp;
   /* SJM 11-19-10 - lval ptr needed also for arrays, array wrapper differs */
   if (tpp->trtyp != IO_IN || np->n_isarr) dap->nd_lval_ptr = TRUE; 
   if (np->n_isarr) dap->arg_arr = TRUE;

   /* set the dpi srep field (needed because no srep for arrays) and set */
   /* dpi nd ptr field for cases where both in and out nd to be passed ptr */ 
   set_ver_side_srep(np, dap);
  }
 if (ai != tskp->tf_dpip->dpi_nargs) __misc_terr(__FILE__, __LINE__);
}

/*
 * ROUTINES TO WRITE DPI C WRAPPER C CODE FILE AND MAKE/PIPE SYSTEM CODE
 */

/*
 * open a file to write the DPI wrapper
 */
static void gen_dpi_wrapper_file(void)
{
 FILE *fp;
 char s1[RECLEN];
 
 sprintf(s1, "%s.c", __dpi_interp_wrapper_fnam);
 if ((fp = __my_fopen(s1, "w")) == NULL)
  {
   __pv_err(4881,
    "unable to open DPI cvc +interp c wrapper file %s.c for writing",  
     __dpi_interp_wrapper_fnam);
   return;
  }


 gen_write_dpi_wrapper_file(fp);
 /* all written - now close - causes flush */
 __my_fclose(fp);
}


/*
 * open a pipe to write the DPI wrapper 
 */
static void gen_dpi_wrapper_pipe(void)
{
 FILE *pp;
 char cc_cmd[RECLEN];
 
 /* AIV 12/30/10 - '-x C' states inputing C, - reads from stdin */
#ifdef __CVC32__
 sprintf(cc_cmd, "gcc -x c -m32 -fPIC -c -O2 -o %s.o -",
  __dpi_interp_wrapper_fnam);
#else
 sprintf(cc_cmd, "gcc -x c -fPIC -O2 -c -o %s.o -", __dpi_interp_wrapper_fnam);
#endif

 if ((pp = popen(cc_cmd, "w")) == NULL)
  {
   __pv_err(4882,
    "unable to pipe DPI cvc +interp c wrapper file %s.c for writing",  
     __dpi_interp_wrapper_fnam);
   return;
  }
 gen_write_dpi_wrapper_file(pp);

 /* all written - now close - causes flush */
 pclose(pp);
}

/*
 * routine to gen the c wrapper file for all dpi import/export functions
 * and tasks in one design
 *
 * SJM 11-07-10 - dlsym stuff was wrong - do not need to use dlsym - dlopen
 * handles the dynamic linking - finds when called first time - dlsym is
 * for finding symbols when name is not known until call time
 */
static void gen_write_dpi_wrapper_file(FILE *fp)
{
 struct dpi_t *dpip;
 FILE *sav_log_s;
 char s1[RECLEN];


 /* SJM 11-30-10 - convert cvcsim write from err msg writing to c src */
 /* to file writing - must be pick back at end of here */
 __dpi_file_writing = TRUE;
 sav_log_s = __log_s;
 __log_s = fp;

 fprintf(fp, "/* Copyright (c) 2014 Tachyon Design Automation */\n");
 fprintf(fp, "\n");
 fprintf(fp, "/* === INSERT LICENSE === */\n");
 fprintf(fp, "\n");
 fprintf(fp, "#include <stdint.h>\n");
 fprintf(fp, "#include <stdlib.h>\n");
#ifdef __DBMALLOC__
 fprintf(fp, "#include <stdio.h>\n");
 fprintf(fp, "#include <stdlib.h>\n");
 fprintf(fp, "#include <string.h>\n");
 fprintf(fp, "#include <ctype.h>\n");
 fprintf(fp, "#include <stdarg.h>\n");
 fprintf(fp, "#include <dlfcn.h>\n");
 fprintf(fp, "#include \"../malloc.h\"\n");
#endif

 /* need liteal svecval */
 fprintf(fp, "\n");
 fprintf(fp, "struct dpi_vecval_t {\n");
 fprintf(fp, " unsigned int aval;\n");
 fprintf(fp, " unsigned int bval;\n");
 fprintf(fp, "};\n");

 fprintf(fp, "\n");
 emit_dpi_arg_union_decl(fp);
 fprintf(fp, "\n");

 fprintf(fp, "extern void %s(char *, union adpi_u *);\n",
  DPI_EXP_INTERP_WRAP_ROUT);

 __pv_stlevel = 0;
 __outlinpos = 0;
 __cur_sofs = 0;
 __nl_wrap_puts("", fp);
 for (dpip = __dpi_hdrp; dpip != NULL; dpip = dpip->dpinxt)
  {
   /* SJM 10-25-10 - do not really need the user c code proto here */
   /* does not hurt */
   emit_dpi_cside_proto(fp, dpip, FALSE);
  }
 __nl_wrap_puts("", fp);

 __wrap_puts("extern void __eval_dpi_wrapper(int dpi_ndx,", fp);
 __pv_stlevel++; 
 __nl_wrap_puts("union adpi_u *a_u_tab)", fp);
 __pv_stlevel--;
 __nl_wrap_puts("{", fp);

 __pv_stlevel++;
 __nl_wrap_puts("switch (dpi_ndx) {", fp);
 __pv_stlevel++;
 for (dpip = __dpi_hdrp; dpip != NULL; dpip = dpip->dpinxt)
  {
   /* SJM 11-23-10 - for export, need a separate wrapper c proc for each */ 
   if (dpip->dpi_type == DPI_EXPORT) continue;

   sprintf(s1, "case %0d:", dpip->dpi_proc_ndx);  
   __nl_wrap_puts(s1, fp);
   __pv_stlevel++;
   emit_dpi_1tf_import_call_wrapper(fp, dpip);
   __nl_wrap_puts("break;", fp);
   __pv_stlevel--;
  }
 __nl_wrap_puts("default:", fp);
 __pv_stlevel++;
 __nl_wrap_puts("exit(100);", fp);
 __pv_stlevel -= 2;
 __nl_wrap_puts("}", fp);
 __pv_stlevel--;
 __nl_wrap_puts("}", fp);
 __nl_wrap_puts("", fp);

 /* need to generate one wrapper with the name of the exported Verilog */
 /* t/f for each dpi export verioog task/func */
 for (dpip = __dpi_hdrp; dpip != NULL; dpip = dpip->dpinxt)
  {
   /* SJM 11-23-10 - import call in wrapper already written */ 
   if (dpip->dpi_type == DPI_IMPORT) continue;

   /* AIV 12/30/10 - if compiled sim - no wrapper for interpreter */
   /* AIV LOOKATME - this could handle all exports????? */
   if (__compiled_sim) continue;
   emit_dpi_1tf_export_def_wrapper(fp, dpip);
  }
 __pv_stlevel = 0;
 __outlinpos = 0;
 __cur_sofs = 0;

 __dpi_file_writing = FALSE;
 __log_s = sav_log_s;
}

/*
 * routine to emit wrapper dpi function for one dpi import header decl 
 */
static void emit_dpi_cside_proto(FILE *fp, struct dpi_t *dpip,
 int32 assume_svdpi)
{
 int32 ai, first_time;
 struct task_t *tskp;
 char *chp, s1[RECLEN], ctypnam[RECLEN];

 if (dpip->cname == NULL) chp = dpip->dsym->synam;
 else chp = dpip->cname;
 bld_dpi_proto_comment(s1, dpip);

 tskp = dpip->dpi_tskp;
 if (tskp->tsktyp != FUNCTION)
  {
   __wrap_puts("extern void", fp);
   __wrap_putc(' ', fp);
   __wrap_puts(chp, fp);
   __wrap_putc('(', fp);
   ai = 0;
  }
 else
  {
   /* for wr hdr proto need to svdpi types (assume use will include) */
   if (assume_svdpi)
    {
     map_ver_svtyp_to_proto_typnam(ctypnam, &(dpip->dpi_ainfo[0]));
    }
   else map_ver_svtyp_to_ctypnam(ctypnam, &(dpip->dpi_ainfo[0]));

   __wrap_puts("extern", fp);
   __wrap_putc(' ', fp);
   __wrap_puts(ctypnam, fp);
   __wrap_putc(' ', fp);
   __wrap_puts(chp, fp);
   __wrap_putc('(', fp);
   /* SJM 11-11-10 - for tasks first (0th) arg info table is first arg */
   ai = 1;
  }

 if (dpip->dpi_nargs == 0)
  {
   /* SJM - 12-01-10 - empty prototype needs a void */ 
   __nl_wrap_puts("void);", fp);
  }
 else
  {
   for (first_time = TRUE; ai < dpip->dpi_nargs; ai++)
    {
     if (!first_time) { __wrap_putc(',', fp); __wrap_putc(' ', fp); }
     else first_time = FALSE;

     if (assume_svdpi)
      {
       map_ver_svtyp_to_proto_typnam(ctypnam, &(dpip->dpi_ainfo[ai]));
      }
     else map_ver_svtyp_to_ctypnam(ctypnam, &(dpip->dpi_ainfo[ai]));
     __wrap_puts(ctypnam, fp);

//     __wrap_putc(' ', fp);
//SJM 12-01-10 NO VAR NAME IN PROTO - REMOVE -  sprintf(s2, "arg%d", ai);
//     __wrap_puts(s2, fp);
    }
   __nl_wrap_puts(");", fp);
  }
}

/*
 * emit the dlsym rout ptr call assign - passes the union values
 */
static void emit_dpi_1tf_import_call_wrapper(FILE *fp, struct dpi_t *dpip)
{
 int32 ai, first_time;
 struct task_t *tskp;
 struct dpiarg_t *dap;
 char *chp, s1[RECLEN], s2[RECLEN];

 if (dpip->cname == NULL) chp = dpip->dsym->synam;
 else chp = dpip->cname;

 tskp = dpip->dpi_tskp;
 if (tskp->tsktyp != FUNCTION)
  {
   __wrap_puts(chp, fp);
   __wrap_putc('(', fp);
   ai = 0;
  }
 else
  {
   dap = &(dpip->dpi_ainfo[0]);
   bld_adpi_u_arg_sel(s1, 0, dap);
   __wrap_puts(s1, fp);
   __wrap_puts(" = ", fp);
   __wrap_puts(chp, fp);
   __wrap_putc('(', fp);
   ai = 1;
  }

 for (first_time = TRUE; ai < dpip->dpi_nargs; ai++)
  {
   if (!first_time) __wrap_puts(", ", fp); else first_time = FALSE;

   dap = &(dpip->dpi_ainfo[ai]);
   bld_adpi_u_arg_sel(s1, ai, dap);
   /* if sv_ptr do not pass addr */
   if (dap->arg_arr
    || dap->ver_side_svtyp == SV_BITVECVAL
    || dap->ver_side_svtyp == SV_CHANDLE
    || dap->ver_side_svtyp == SV_LOGICVECVAL) __wrap_puts(s1, fp);
   else if (dap->nd_lval_ptr)
    {
     /* SJM 11-14-10 - for inout args, pass the addr of the sv union */
     sprintf(s2, "&(%s)", s1);
     __wrap_puts(s2, fp);
    }
   else __wrap_puts(s1, fp);
  }
 __nl_wrap_puts(");", fp);
}

/*
 * emit the routine that c side code calls to invoke the verilog t/f
 *
 * for ver functions that return a val, proto and define need the ret decl
 */
static void emit_dpi_1tf_export_def_wrapper(FILE *fp, struct dpi_t *dpip)
{
 int32 ai, first_time;
 struct task_t *tskp;
 struct dpiarg_t *dap;
 char *chp, *chp2, s1[RECLEN], s2[RECLEN], ctypnam[RECLEN];

 if (dpip->cname == NULL) chp2 = chp = dpip->dsym->synam;
 else { chp = dpip->cname; chp2 = dpip->dsym->synam; } 

 tskp = dpip->dpi_tskp;
 if (tskp->tsktyp != FUNCTION)
  {
   __wrap_puts("extern void", fp);
   __wrap_putc(' ', fp);
   __wrap_puts(chp, fp);
   __wrap_putc('(', fp);
   ai = 0;
  }
 else
  {
   dap = &(dpip->dpi_ainfo[0]);
   map_ver_svtyp_to_ctypnam(ctypnam, dap);
   __wrap_puts("extern", fp);
   __wrap_putc(' ', fp);
   __wrap_puts(ctypnam, fp);
   __wrap_putc(' ', fp);
   __wrap_puts(chp, fp);
   __wrap_putc('(', fp);
   ai = 1;
  }

 for (first_time = TRUE; ai < dpip->dpi_nargs; ai++)
  {
   if (!first_time) { __wrap_putc(',', fp); __wrap_putc(' ', fp); }
   else first_time = FALSE;

   dap = &(dpip->dpi_ainfo[ai]);
   map_ver_svtyp_to_ctypnam(ctypnam, dap);
   __wrap_puts(ctypnam, fp);
   __wrap_putc(' ', fp);
   sprintf(s2, "arg%0d", ai);
   __wrap_puts(s2, fp);
  }
 __nl_wrap_puts(")", fp);
 __nl_wrap_puts("{", fp);
 __pv_stlevel++;
 __wrap_puts("union adpi_u a_u_tab", fp);
 sprintf(s2, "[%0d]", dpip->dpi_nargs);
 __wrap_puts(s2, fp);
 __nl_wrap_puts(";", fp);
 __nl_wrap_puts("", fp);

 if (tskp->tsktyp != FUNCTION) ai = 0; else ai = 1;
 for (; ai < dpip->dpi_nargs; ai++)
  {
   dap = &(dpip->dpi_ainfo[ai]);
   bld_adpi_u_arg_sel(s1, ai, dap);
   map_ver_svtyp_to_ctypnam(ctypnam, dap);
   __wrap_puts(s1, fp);
   __wrap_puts(" = (", fp);
   __wrap_puts(ctypnam, fp);
   __wrap_puts(") ", fp);
   sprintf(s2, "arg%0d", ai);
   __wrap_puts(s2, fp);
   __nl_wrap_puts(";", fp);
  }
 __wrap_puts(DPI_EXP_INTERP_WRAP_ROUT, fp);
 __wrap_putc('(', fp);
 __wrap_putc('"', fp);
 __wrap_puts(chp2, fp);
 __wrap_putc('"', fp);
 __wrap_puts(", ", fp);
 __nl_wrap_puts("a_u_tab);", fp);

 /* if c function, return arg 0 (in Verilog name of func assoc. var) */ 
 if (tskp->tsktyp == FUNCTION)
  {
   dap = &(dpip->dpi_ainfo[0]);
   map_ver_svtyp_to_ctypnam(ctypnam, dap);
   bld_adpi_u_arg_sel(s1, 0, dap);
   /* notice always need to case the return val for export funcs */
   __wrap_puts("return(", fp);
   __wrap_puts(ctypnam, fp);
   __wrap_puts(") ", fp);
   __wrap_puts(s1, fp);
   __nl_wrap_puts(";", fp);
  }
 __pv_stlevel--;
 __nl_wrap_puts("}", fp); 
}

/*
 * bld a string of one adpi_u a_u_tab union value selector
 */
static char *bld_adpi_u_arg_sel(char *s, int32 argi, struct dpiarg_t *dap)
{
 char s1[RECLEN];

 bld_adpi_u_sel_name(s1, dap);
 sprintf(s, "a_u_tab[%d].%s", argi, s1);
 return(s);
}

/*
 * convert a sv type field to the name of a union selector 
 */
static char *bld_adpi_u_sel_name(char *s, struct dpiarg_t *dap)
{
 /* SJM - 11-19-10 - for arrays, need to pass the sv ptr not sv ch addr */
 if (dap->arg_arr)
  {
   strcpy(s, "sv_ptr");
   return(s);
  }

 switch (dap->ver_side_svtyp) {
  case SV_BIT: case SV_BYTE: case SV_LOGIC:
   strcpy(s, "sv_ch");
   break;
  case SV_SHORTCINT:
   strcpy(s, "sv_shrti");
   break;
  case SV_CINT:
   strcpy(s, "sv_i");
   break;
  case SV_LONGCINT:
   strcpy(s, "sv_lngi");
   break;
  case SV_REAL:
   strcpy(s, "sv_d");
   break;
  case SV_BITVECVAL: case SV_CHANDLE: case SV_LOGICVECVAL:
  case SV_CHAR_PTR:
   strcpy(s, "sv_ptr");
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * routine to bld comment describing the dpi import/export 
 */
static char *bld_dpi_proto_comment(char *s, struct dpi_t *dpip)
{
 struct task_t *tskp;
 char dpitypnam[RECLEN], csidnam[RECLEN];

 if (dpip->cname == NULL) strcpy(csidnam, "");
 else sprintf(csidnam, "(cname=%s)", dpip->cname);
 tskp = dpip->dpi_tskp;
 /* emit user world (not wrapper world) c side prototype */ 
 if (dpip->dpi_type == DPI_EXPORT) strcpy(dpitypnam, "export");
 else strcpy(dpitypnam, "import");
 sprintf(s, "/* proto verilog %s %s named %s%s */", dpitypnam,
  __to_tsktyp(__xs, tskp->tsktyp), dpip->dsym->synam, csidnam);
 return(s);
}

/*
 * routine to write the dpi arg union declaration
 *
 * SJM 10-25-10 - BEWARE - must exactly match struct in v.h
 * SJM 11-14-10 - sv_ch must be unsigned char - to match svBit, svLogic
 */
static void emit_dpi_arg_union_decl(FILE *fp)
{
 fprintf(fp, "union adpi_u {\n");
 fprintf(fp, " unsigned char sv_ch;\n");
 fprintf(fp, " int sv_i;\n");
 fprintf(fp, " short int sv_shrti;\n");
 fprintf(fp, " long long int sv_lngi;\n");
 fprintf(fp, " double sv_d;\n");
 fprintf(fp, " void *sv_ptr;\n");
 fprintf(fp, "};\n");
}

/*
 * ROUTINES TO CREATE AND RUN DPI MAKEFILE FOR SHOW ASM OR SET UP PIPE 
 */

/*
 * build and write make files and then run make to assemble and then
 * dynamically link generated .s files - +show_asm case where not piping
 * .s file output into assmbler
 */
static void gen_rt_dpi_interp_mkfil_and_compile(void)
{
 FILE *fp;

 if ((fp = __my_fopen(RT_DPI_INTERP_MKFIL, "w")) == NULL)
  {
   __pv_err(4883,
    "unable to open DPI c function and task make file %s for writing",  
    RT_DPI_INTERP_MKFIL);
   return;
  }

 // SJM 10-29-10 - PUTMEBACK - fprintf(fp, "WARNS=-Wall\n");
 fprintf(fp, "CC=gcc\n");
#ifdef __CVC32__
 fprintf(fp, "LFLAGS= -G -shared -export-dynamic -melf_i386\n");
 fprintf(fp, "CFLAGS= -fPIC -Wall -g -m32\n");
#else
 fprintf(fp, "LFLAGS= -G -shared -export-dynamic\n");
 fprintf(fp, "CFLAGS= -fPIC -Wall -g\n");
#endif
 fprintf(fp, "\n");
 fprintf(fp, "%s.so:\t%s.o\n", __dpi_interp_wrapper_fnam,
    __dpi_interp_wrapper_fnam);
 fprintf(fp,
  "\t$(LD) $(LFLAGS) %s.o -o %s.so\n", __dpi_interp_wrapper_fnam,
    __dpi_interp_wrapper_fnam);
 fprintf(fp, "%s.o:\t%s.c\n", __dpi_interp_wrapper_fnam, 
   __dpi_interp_wrapper_fnam);
 fprintf(fp, "\t$(CC) $(CFLAGS) -c %s.c -o %s.o\n",
   __dpi_interp_wrapper_fnam, __dpi_interp_wrapper_fnam);
 fprintf(fp, "\n");
 __my_fclose(fp);

 run_dpi_interp_mkfil();
}

/*
 * invoke system to run make file to run gcc to compile dpi task/func wrapper
 * c code
 */
static void run_dpi_interp_mkfil(void)
{
 char s1[RECLEN];

 //SJM 10-29-10 PUTMEBACK - sprintf(s1, "make -f %s >&/dev/null", RT_DPI_INTERP_MKFIL);
 sprintf(s1, "make -f %s", RT_DPI_INTERP_MKFIL);
 if (system(s1) < 0)
 {
  __pv_err(4884,
  "unable to compile %s.c, try manually running: 'make -f %s",
  __dpi_interp_wrapper_fnam, RT_DPI_INTERP_MKFIL); 
 }
}

/*
 * routine to use shell pipe open to run gcc and ld on wrapper file to
 * make fixed tmp .so wrapper file in temp area
 */
static void gen_rt_dpi_interp_pipe_lib()
{
 FILE *pp;
 char ld_cmd[RECLEN], cmd2[RECLEN];

 /* AIV 01/05/10 - need different flags for Mac */
#ifdef __CVC32__
 sprintf(ld_cmd, "gcc -m32 -shared -export-dynamic %s.o -o %s.so",
  __dpi_interp_wrapper_fnam, __dpi_interp_wrapper_fnam);
#else
 sprintf(ld_cmd, "gcc -shared -export-dynamic %s.o -o %s.so",
  __dpi_interp_wrapper_fnam, __dpi_interp_wrapper_fnam);
#endif
 if ((pp = popen(ld_cmd, "w")) == NULL)
  {
   __pv_err(4885, "unable to locate system linker ld");
   return;
  } 
 pclose(pp);

 /* SJM 12-29-10 - now finished with .o wrapper file */
 sprintf(cmd2, "rm %s.o", __dpi_interp_wrapper_fnam);
 system(cmd2);
 /* must leave the library - remove on exit */
}

/*
 * routine to cleanup dpi interp library - only if make file not used
 * only called if know interp with dpi routines and no make file
 */
extern void __cleanup_dpi_interp_wrap_lib(void)
{
 char s1[RECLEN], s2[RECLEN];

 /* if show asm must leave the wrapper around */
 if (__show_asm) return;
 /* compiler uses the .o not dynamic lib .so */
 if (__compiled_sim)
  {
   sprintf(s1, "%s.o", __dpi_interp_wrapper_fnam);
  }
 else sprintf(s1, "%s.so", __dpi_interp_wrapper_fnam);

 if (access(s1, F_OK) == -1)
  {
   __pv_err(4886, "problem cleaning up interp dpi");
  }
 sprintf(s2, "rm %s", s1);
 system(s2);
}

/*
 * ROUTINES TO WRITE DPI HDRS FILE TO HELP USER DEBUG 
 */

/*
 * write an ascii file of dpi c header prototypes
 */
static void wr_dpihdrs(void)
{
 struct dpi_t *dpip;
 FILE *fp, *sav_log_s;
 char s1[RECLEN];

 if ((fp = __my_fopen(DPI_HDR_FIL, "w")) == NULL)
  {
   __pv_err(4887,
    "unable to open +write_dpi_hdrs option c prototype headers file %s",
    DPI_HDR_FIL);
   return;
  }

 /* SJM 11-30-10 - convert cvcsim write from err msg writing to c src */
 /* to file writing - must be pick back at end of here */
 __dpi_file_writing = TRUE;
 sav_log_s = __log_s;
 __log_s = fp;
 __pv_stlevel = 0;
 __outlinpos = 0;
 __cur_sofs = 0;
 __nl_wrap_puts("/*", fp);
 sprintf(s1, " * Example header prototypes for run of %s", __pv_timestamp);
 __nl_wrap_puts(s1, fp);
 __nl_wrap_puts(" */", fp);
 __nl_wrap_puts("", fp);

 strcpy(s1, "#include \"svdpi.h\"");
 __nl_wrap_puts(s1, fp);
 __nl_wrap_puts("", fp);

//SJM 11-30-10 - WRITEME NEED SOME KIND OF TIME STAMP AT TOP
 for (dpip = __dpi_hdrp; dpip != NULL; dpip = dpip->dpinxt)
  {
   emit_dpi_cside_proto(fp, dpip, TRUE);
  }
 __dpi_file_writing = FALSE;
 __log_s = sav_log_s;
}

/*
 * ROUTINES FOR MAPPING SV TYPES NUMS, CTYPES NUMS AND NAME STRING 
 */

/*
 * build the underlying verilog side new SV type define num
 *
 * SJM 09-19-10 - new algorithm following page 384 of SV Veriification
 * book - mapping is sometimes to normal C types and sometimes to one
 * of the 3 sv types defined in svdpi.h
 *
 * SJM 10-25-10 - what about voids - for now not using
 */
static int32 get_ver_side_svtyp(struct net_t *np)
{
 int32 svtyp;

 svtyp = -1;
 switch (np->ntyp) {
  /* 2 state */
  case N_BIT:
   if (!np->n_isavec) svtyp = SV_BIT; else svtyp = SV_BITVECVAL; 
   break;
  case N_BYTE:
   svtyp = SV_BYTE;
   break;
  case N_SHORTCINT:
   svtyp = SV_SHORTCINT;
   break;
  case N_CINT:
   svtyp = SV_CINT;
   break;
  case N_LONGCINT:
   svtyp = SV_LONGCINT;
   break;
  case N_REAL:
   svtyp = SV_REAL;
   break;
  case N_CHANDLE:
   svtyp = SV_CHANDLE;
   break;
  /* 4 state */
  case N_REG: case N_LOGIC:
   if (np->nwid == 1) svtyp = SV_LOGIC; else svtyp = SV_LOGICVECVAL; 
   break;
  case N_INT: case N_TIME:
   svtyp = SV_LOGICVECVAL; 
   break;
  case N_STRING:
   svtyp = SV_CHAR_PTR; 
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(svtyp);
}

/*
 * build the underlying verilog side dpi srep (mostly needed for arrays)
 * this needs to use net types in case array
 *
 * AIV 09-27-10 - FIXME - we should get rid of the SR_ARRAY since then
 * can't store the net's srep
 */
static void set_ver_side_srep(struct net_t *np, struct dpiarg_t *dap)
{
 switch (np->ntyp) {
  /* 2 state */
  case N_BYTE:
   dap->arg_srep = SR_DPI_BYTE;
   break;
  case N_BIT:
   if (np->nwid == 1) dap->arg_srep = SR_SCAL2S;
   else dap->arg_srep = SR_BIT2S;
   break;
  case N_SHORTCINT:
   dap->arg_srep = SR_DPI_SHORTCINT;
   break;
  case N_CINT:
   dap->arg_srep = SR_DPI_CINT;
   break;
  case N_LONGCINT:
   dap->arg_srep = SR_DPI_LONGCINT;
   break;
  case N_REAL:
   dap->arg_srep = SR_DPI_REAL;
   break;
  /* 4 state */
  case N_REG: case N_LOGIC:
   if (np->nwid == 1) dap->arg_srep = SR_SCAL; else dap->arg_srep = SR_VEC;
   break;
  case N_INT: case N_TIME:
   dap->arg_srep = SR_VEC;
   break;
  case N_CHANDLE:
   dap->arg_srep = SR_DPI_CHANDLE;
   break;
  case N_STRING:
   dap->arg_srep = SR_STRING;
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * routine to map ver side sv type to c type for prototypes
 *
 * variant of routine that uses types in svdpi.h - for the wr proto option
 */
static char *map_ver_svtyp_to_proto_typnam(char *s, struct dpiarg_t *dap)
{
 char s1[RECLEN];

 strcpy(s1, "");
 strcpy(s, "??PROTO-ERROR??");
 switch (dap->ver_side_svtyp) {
  case SV_BIT:
//SJM 10-25-10 - LOOKATME? - should this be unsigned char instead?
   if (dap->nd_lval_ptr) strcpy(s1, "svBit *"); else strcpy(s1, "svBit");
   break;
  case SV_BYTE:
   if (dap->nd_lval_ptr) strcpy(s1, "unsigned char *");
   else strcpy(s1, "unsigned char");
   break;
  case SV_SHORTCINT:
   if (dap->nd_lval_ptr) strcpy(s1, "short int *");
   else strcpy(s1, "short int");
   break;
  case SV_CINT:
   if (dap->nd_lval_ptr) strcpy(s1, "int *"); else strcpy(s1, "int");
   break;
  case SV_LONGCINT:
   if (dap->nd_lval_ptr) strcpy(s1, "long long int *");
   else strcpy(s1, "long long int");
   break;
  case SV_REAL:
   if (dap->nd_lval_ptr) strcpy(s1, "double *");
   else strcpy(s1, "double");
   break;
  case SV_LOGIC:
   if (dap->nd_lval_ptr) strcpy(s1, "svLogic *"); else strcpy(s1, "svLogic");
   break;
  case SV_BITVECVAL:
   strcpy(s1, "svBitVecVal *"); 
   break;
  case SV_LOGICVECVAL:
   strcpy(s1, "svLogicVecVal *");
   break;
  case SV_CHAR_PTR:
   strcpy(s1, "void *");
   break;
  case SV_CHANDLE:
   strcpy(s, "void *");
   return(s);
  case SV_VOID:
   strcpy(s, "void");
   return(s);
  case SV_VOID_PTR:
   strcpy(s, "void *");
   return(s);
  default: __case_terr(__FILE__, __LINE__);
 }
 if (dap->arg_iotyp == IO_IN) sprintf(s, "%s", s1);
 else strcpy(s, s1);
 return(s);
}


/*
 * routine to map ver side sv type to c type for prototypes
 *
 * variant of version for wrapper .c file that does not need svdpi.h
 */
static char *map_ver_svtyp_to_ctypnam(char *s, struct dpiarg_t *dap)
{
 char s1[RECLEN];

 strcpy(s1, "");
 strcpy(s, "??PROTO-ERROR??");
 switch (dap->ver_side_svtyp) {
  case SV_BIT: case SV_BYTE: case SV_LOGIC:
   if (dap->nd_lval_ptr) strcpy(s1, "unsigned char *");
   else strcpy(s1, "unsigned char");
   break;
  case SV_SHORTCINT:
   if (dap->nd_lval_ptr) strcpy(s1, "short int *");
   else strcpy(s1, "short int");
   break;
  case SV_CINT:
   if (dap->nd_lval_ptr) strcpy(s1, "int *"); else strcpy(s1, "int");
   break;
  case SV_LONGCINT:
   if (dap->nd_lval_ptr) strcpy(s1, "long long int *");
   else strcpy(s1, "long long int");
   break;
  case SV_REAL:
   if (dap->nd_lval_ptr) strcpy(s1, "double *");
   else strcpy(s1, "double");
   break;
   break;
  case SV_BITVECVAL:
//SJM 12-29-10 - LOOKATME - think even for 64 bits int is 32 bits
   strcpy(s1, "unsigned int *"); 
   break;
  case SV_LOGICVECVAL:
   strcpy(s1, "struct dpi_vecval_t *");
   break;
  case SV_CHAR_PTR:
   strcpy(s1, "void *");
   break;
  case SV_CHANDLE:
   strcpy(s, "void *");
   return(s);
  case SV_VOID:
   strcpy(s, "void");
   return(s);
  case SV_VOID_PTR:
   strcpy(s, "void *");
   return(s);
  default: __case_terr(__FILE__, __LINE__);
 }
 if (dap->arg_iotyp == IO_IN) sprintf(s, "%s", s1);
 else strcpy(s, s1);
 return(s);
}
