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
 * module to implement pli tf_ routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>

#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "veriuser.h"
#include "cv_veriuser.h"
#include "acc_user.h"

/* local prototypes */
static void check_veriusertf_table(p_tfcell);
static void add_veriusertf_task(struct t_tfcell *);
static void add_veriusertf_func(struct t_tfcell *);
static int32 chk_idnam_veriusertf(char *);
static void pli_func_checktf(struct expr_t *);
static void pli_task_checktf(struct st_t *);
static void call_allinsts_misctfs(int32);
static void misc_call_misctf(struct tfrec_t *, int32);
static struct t_tfcell *get_tfcell(struct tfrec_t *);
static void allocset_vecval(struct t_tfnodeinfo *, struct xstk_t *, int32);
static int32 bad_nosimtf_err(char *);
static int32 bad_notfcontext_err(char *);
static int32 bad_rosync_err(char *);
static void init_nodeinfo(struct t_tfnodeinfo *);
static void init_exprinfo(struct t_tfexprinfo *);
static int32 get_xinfo_typ(struct expr_t *);
static struct xstk_t *tf_pushconvfromreal(double, int32);
static int32 delayed_str_putp(int32, int32, int32, char *, word64, int32);
static int32 chk_putdstr(char *, int32, int32 *);
static struct xstk_t *tftostrenval(char *, int32 *);
static int32 to_stval(char *);
static void cancel_dputp_toend(struct tfarg_t *, struct dltevlst_t *);
static int32 delayed_misctf_schd(word64);
static void bld_pvc_dces(struct expr_t *, int32);
static void linkon_pvc_dce(struct net_t *, int32, int32, struct gref_t *, int32);
static void rosync_call_misctf(struct tev_t *);
static void exec_tfarg_assign(struct tfarg_t *, struct expr_t *, word32 *,
 word32 *);
static void emit_tputd_trmsg(struct tedputp_t *, struct tfarg_t *);
static void reinit_1tfrec(struct tfrec_t *);
static void vprt_tferr_msg(char *, va_list, va_list);
static void vprt_tfwarn_msg(char *, va_list, va_list);

/* tf_ P1364 prototypes from veriuser.h file */
extern void io_mcdprintf(int32 mcd, char *format, ...);
extern void io_printf(char *format, ...);
extern char *mc_scan_plusargs(char *plusarg);
extern void tf_add_long(int32 *aof_lowtime1, int32 *aof_hightime1, int32 lowtime2,
 int32 hightime2);
extern int32 tf_asynchoff(void);
extern int32 tf_asynchon(void);
extern int32 tf_clearalldelays(void);
extern int tf_compare_long(unsigned int low1, unsigned int high1,
 unsigned int low2, unsigned int high2);
extern int32 tf_copypvc_flag(int32 nparam);
extern void tf_divide_long(int32 *aof_low1, int32 *aof_high1, int32 low2, int32 high2);
extern int32 tf_dofinish(void);
extern int32 tf_dostop(void);
extern int32 tf_error(char *fmt, ...);
extern int32 tf_evaluatep(int32 pnum);
extern p_tfexprinfo tf_exprinfo(int32 pnum, p_tfexprinfo pinfo);
extern char *tf_getcstringp(int32 nparam);
extern char *tf_getinstance(void);
extern int32 tf_getlongp(int32 *aof_highvalue, int32 pnum);
extern int32 tf_getlongsimtime(int32 *aof_hightime);
extern int32 tf_getlongtime(int32 *aof_hightime);
extern int32 tf_getnextlongtime(int32 *aof_lowtime, int32 *aof_hightime);
extern int32 tf_getp(int32 pnum);
extern int32 tf_getpchange(int32 nparam);
extern double tf_getrealp(int32 pnum);
extern double tf_getrealtime(void);
extern int32 tf_getsimtime(void);
extern int32 tf_gettime(void);
extern char *tf_getworkarea(void);
extern int32 tf_iasynchoff(char *inst);
extern int32 tf_iasynchon(char *inst);
extern int32 tf_iclearalldelays(char *inst);
extern int32 tf_icopypvc_flag(int32 nparam, char *inst);
extern int32 tf_ievaluatep(int32 pnum, char *inst);
extern p_tfexprinfo tf_iexprinfo(int32 pnum, p_tfexprinfo pinfo, char *inst);
extern char *tf_igetcstringp(int32 nparam, char *inst);
extern int32 tf_igetlongp(int32 *aof_highvalue, int32 pnum, char *inst);
extern int32 tf_igetlongsimtime(int32 *aof_hightime);
extern int32 tf_igetlongtime(int32 *aof_hightime, char *inst);
extern int32 tf_igetp(int32 pnum, char *inst);
extern int32 tf_igetpchange(int32 nparam, char *inst);
extern double tf_igetrealp(int32 pnum, char *inst);
extern double tf_igetrealtime(char *inst);
extern int32 tf_igettime(char *inst);
extern int32 tf_igettimeprecision(char *inst);
extern int32 tf_igettimeunit(char *inst);
extern char *tf_igetworkarea(char *inst);
extern char *tf_imipname(char *cell);
extern int32 tf_imovepvc_flag(int32 nparam, char *inst);
extern p_tfnodeinfo tf_inodeinfo(int32 pnum, p_tfnodeinfo pinfo, char *inst);
extern int32 tf_inump(char *inst);
extern int32 tf_ipropagatep(int32 pnum, char *inst);
extern int32 tf_iputlongp(int32 pnum, int32 lowvalue, int32 highvalue, char *inst);
extern int32 tf_iputp(int32 pnum, int32 value, char *inst);
extern int32 tf_iputrealp(int32 pnum, double value, char *inst);
extern int32 tf_irosynchronize(char *inst);
extern int32 tf_isetdelay(int32 delay, char *inst);
extern int32 tf_isetlongdelay(int32 lowdelay, int32 highdelay, char *inst);
extern int32 tf_isetrealdelay(double realdelay, char *inst);
extern int32 tf_isizep(int32 pnum, char *inst);
extern char *tf_ispname(char *cell);
extern int32 tf_istrdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, int32 delay, int32 delaytype, char *inst);
extern char *tf_istrgetp(int32 pnum, int32 format_char, char *inst);
extern int32 tf_istrlongdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, int32 lowdelay, int32 highdelay, int32 delaytype, char *inst);
extern int32 tf_istrrealdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, double realdelay, int32 delaytype, char *inst);
extern int32 tf_isynchronize(char *inst);
extern int32 tf_itestpvc_flag(int32 nparam, char *inst);
extern int32 tf_itypep(int32 pnum, char *inst);
extern void tf_long_to_real(int32 int_lo, int32 int_hi, double *aof_real);
extern char *tf_longtime_tostr(int32 lowtime, int32 hightime);
extern int32 tf_message(int32 level, char *facility, char *messno,
 char *message, ...);
extern char *tf_mipname(void);
extern int32 tf_movepvc_flag(int32 nparam);
extern void tf_multiply_long(int32 *aof_low1, int32 *aof_high1, int32 low2,
 int32 high2);
extern p_tfnodeinfo tf_nodeinfo(int32 pnum, p_tfnodeinfo pinfo);
extern int32 tf_nump(void);
extern int32 tf_propagatep(int32 pnum);
extern int32 tf_putlongp(int32 pnum, int32 lowvalue, int32 highvalue);
extern int32 tf_putp(int32 pnum, int32 value);
extern int32 tf_putrealp(int32 pnum, double value);
extern int32 tf_read_restart(char *blockptr, int32 blocklen);
extern void tf_real_to_long(double real, int32 *aof_int_lo, int32 *aof_int_hi);
extern int32 tf_rosynchronize(void);
extern void tf_scale_longdelay(char *cell, int32 delay_lo, int32 delay_hi,
 int32 *aof_delay_lo, int32 *aof_delay_hi);
extern void tf_scale_realdelay(char *cell, double realdelay,
 double *aof_realdelay);
extern int32 tf_setdelay(int32 delay);
extern int32 tf_setlongdelay(int32 lowdelay, int32 highdelay);
extern int32 tf_setrealdelay(double realdelay);
extern int32 tf_setworkarea(char *workarea);
extern int32 tf_sizep(int32 pnum);
extern char *tf_spname(void);
extern int32 tf_strdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, int32 delay, int32 delaytype);
extern char *tf_strgetp(int32 pnum, int32 format_char);
extern char *tf_strgettime(void);
extern int32 tf_strlongdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, int32 lowdelay, int32 highdelay, int32 delaytype);
extern int32 tf_strrealdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, double realdelay, int32 delaytype);
extern void tf_subtract_long(int32 *aof_lowtime1, int32 *aof_hightime1,
 int32 lowtime2, int32 hightime2);
extern int32 tf_synchronize(void);
extern int32 tf_testpvc_flag(int32 nparam);
extern int32 tf_text(char *fmt, ...);
extern int32 tf_typep(int32 pnum);
extern void tf_unscale_longdelay(char *cell, int32 delay_lo, int32 delay_hi,
 int32 *aof_delay_lo, int32 *aof_delay_hi);
extern void tf_unscale_realdelay(char *cell, double realdelay,
 double *aof_realdelay);
extern int32 tf_warning(char *fmt, ...);
extern int32 tf_write_save(char *blockptr, int32 blocklen);
extern void __dce_turn_chg_store_on(struct mod_t *, struct dcevnt_t *, int32);  
extern int32 __is_lnegative(word32 *, int32); 
extern void __ld_arr_val(struct xstk_t *, struct expr_t *, struct net_t *, 
 int32, struct gref_t *);

/* extern prototypes (maybe defined in this module) */
extern struct systsk_t *__alloc_systsk(void);
extern struct sysfunc_t *__alloc_sysfunc(void);
extern void __pli_func_sizetf(struct expr_t *);
extern void __call_all_checktfs(void);
extern void __call_misctfs_streset(void);
extern void __call_misctfs_endreset(void);
extern void __call_misctfs_simstart(void);
extern void __call_misctfs_iact(void);
extern void __call_misctfs_finish(void);
extern void __call_misctfs_scope(void);
extern char *__get_tfcellnam(struct tfrec_t *);
extern void __pli_func_calltf(struct expr_t *);
extern void __pli_task_calltf(struct st_t *);
extern char *__alloc_vval_to_cstr(word32 *, int32, int32, int32);
extern int32 __wide_vval_is0(word32 *, int32);
extern struct xstk_t *__putdstr_to_val(char *, int32, int32, int32);
extern struct dltevlst_t *__spliceout_last(struct dltevlst_t *);
extern struct dltevlst_t *__find_last_bdltevp(struct dltevlst_t *, word64);
extern void __pli_dofinish(int32, char *);
extern void __pvc_call_misctf(struct dcevnt_t *);
extern void __exec_rosync_misctf(void);
extern void __sync_call_misctf(void);
extern void __setdel_call_misctf(void);
extern void __process_putpdel_ev(void);
extern void __reinit_tfrecs(void);
extern char *__mytf_malloc(int32);

extern struct tnode_t *__vtfind(char *, struct symtab_t *);
extern void __add_sym(char *, struct tnode_t *);
extern void __grow_xstk(void);
extern void __grow_tevtab(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern int32 __get_arrwide(struct net_t *);
extern int32 __unnormalize_ndx(struct net_t *, int32);
extern void __xline_vval_to_cstr(word32 *, int32, int32, int32, int32);
extern int32 __v64_to_real(double *, word64 *);
extern void __cnv_stk_fromreg_toreal(struct xstk_t *, int32);
extern void __cnv_stk_fromreal_toreg32(struct xstk_t *);
extern void __sizchgxs(struct xstk_t *, int32);
extern char *__alloc_getasfmt(struct expr_t *, struct tfrec_t *, int32);
extern void __lmult(word32 *, word32 *, word32 *, int32);
extern void __insert_event(struct tev_t *);
extern void __strenwiden_sizchg(struct xstk_t *, int32);
extern int32 __to_base(int32);
extern void __to_dhboval(int32, int32);
extern int32 __is_vdigit(int32, int32);
extern void __my_free(void *, size_t);
extern char *__my_malloc(size_t);
extern int32 __real_to_v64tim(word64 *, double);
extern char *__st_regab_tostr(char *, byte *, int32);
extern char *__regab_tostr(char *, word32 *, word32 *, int32, int32, int32);
extern void __evtr_resume_msg(void);
extern char *__bld_lineloc(char *, word32, int32);
extern char *__msg2_cur_blditree(char *);
extern void __free_dceauxlst(struct dceauxlst_t *, int32);
extern void __cnv_ticks_tonum64(word64 *, word64, struct mod_t *);
extern char *__to_timstr(char *, word64 *);
extern void __disp_itree_idp_path(t_midat *, struct task_t *);
extern void __emit_stsk_endmsg(void);
extern void __vpi_endsim_trycall(void);
extern void __ldivmod2(word32 *, word32 *, word32 *, word32 *, int32);
extern void __my_vfprintf(FILE *, char *, va_list, va_list);
extern int32 __em_suppr(int32);
extern t_midat *__xmrget_refgrp_to_targ(struct gref_t *);
extern struct dcevnt_t *__alloc_dcevnt(struct net_t *);
extern void __alloc_plidce_prevval(struct dcevnt_t *);
extern void __init_plidce_prevval(struct dcevnt_t *);
extern void __exec2_proc_assign(struct expr_t *, word32 *, word32 *, int32);
extern void __st_perinst_val(union pck_u, int32, word32 *, word32 *);
extern void __mdr_assign_or_sched(struct expr_t *);
extern void __exec_conta_assign(struct expr_t *, word32 *, word32 *, int32);
extern void __init_tfdrv(struct tfarg_t *, struct expr_t *, struct mod_t *);
extern int32 __trim1_0val(word32 *, int32);
extern void __process_pli_dynamic_libs(struct loadpli_t *);
extern void __dcelst_off(struct dceauxlst_t *);
extern double __cnvt_signed64_to_real(word32 *, int32);
extern struct net_t *__get_indexed_psel_range(struct expr_t *, int32 *, 
 int32 *);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);

extern void __tr_msg(char *, ...);
extern void __crit_msg(char *, ...);
extern void __cv_msg(char *, ...);
extern void __my_fprintf(FILE *, char *, ...);
extern void __pv_err(int32, char *, ...);
extern void __pv_warn(int32, char *,...);
extern void __sgfwarn(int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __dbg_msg(char *, ...);
extern void __sgfinform(int32, char *, ...);
extern void __pv_terr(int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern void __my_exit(int32, int32);
extern void __inform(int32, char *, ...);

/* needed here since causes compiler error in veriuser.h */
#ifdef __STATIC_PLI__
extern struct t_tfcell veriusertfs[];
#endif

extern const double __dbl_toticks_tab[];
extern const word32 __masktab[];

/*
 * ROUTINES TO PROCESS VERIUSERTFS D.S. BEFORE PVER STARTS
 */ 

/*
 * setup both the static veriuser tfs and/or the +loadpli1 returned tables
 */
extern void __setup_veriusertf_systfs(void)
{
 int32 i, sav_last_veriusertf, num_pli1_systfs;
 struct dynboot_t *dnbp;
 struct loadpli_t *ldp;
 struct t_tfcell *veriusertf_ptr, *tfcp;

 sav_last_veriusertf = __last_veriusertf;

 /* SJM 07/08/02 - handle all +loadpli1 option dynamic lib loading first */
 /* this just load the dynamic libraries and finds boot strap routines */
 if (__pli1_dynlib_hd != NULL) __process_pli_dynamic_libs(__pli1_dynlib_hd);

 /* always add P1364 old built in table - empty unless old static cverobj.o */
#ifdef __STATIC_PLI__
 check_veriusertf_table(veriusertfs);
#else
 for (ldp = __pli1_dynlib_hd; ldp != NULL; ldp = ldp->load_plinxt)
  {
   for (dnbp = ldp->dynblst; dnbp != NULL; dnbp = dnbp->dynbootnxt)
    {
     /* bootstrap routine can be nil */
     if (dnbp->dynu.tf_rout == NULL) continue;

     /* vpi boostrap routines are assume to return void - if not ret ignored */
     /* notice user must insure if pli1 bootstrap routine returns val, that */
     /* it is pointer to p tfcell table */
     veriusertf_ptr = (struct t_tfcell *) (dnbp->dynu.tf_rout)();         
     dnbp->ret_veriusertf = veriusertf_ptr;
     if (dnbp->ret_veriusertf != NULL)
      {
       check_veriusertf_table(dnbp->ret_veriusertf);
      }
    } 
#endif
  }
 
 num_pli1_systfs = __last_veriusertf - sav_last_veriusertf;
 if (num_pli1_systfs != 0 && __verbose)
  {
   __cv_msg("  %d veriusertfs PLI 1.0 user tasks and functions defined.\n",
    num_pli1_systfs);
  }

 /* SJM 07/16/02 - need internal shadow veriuser tfs table that is copy */
 /* of legacy user filled veriuser tfs for old static cverobj.o pli1 scheme */ 
 /* and contains copy of all returned tables for new +load_pli1 mechanism */
 __shadow_veriusertfs = (struct t_tfcell *)
  __my_malloc((num_pli1_systfs + 1)*sizeof(struct t_tfcell));
#ifdef __STATIC_PLI__
 for (i = 0;; i++)
  {
   tfcp = &(veriusertfs[i]);
   __shadow_veriusertfs[i] = *tfcp;
   /* copy ending fence before break; */
   if (tfcp->type == 0) break;
  }
#else
 for (i = 0, ldp = __pli1_dynlib_hd; ldp != NULL; ldp = ldp->load_plinxt)
  {

   for (dnbp = ldp->dynblst; dnbp != NULL; dnbp = dnbp->dynbootnxt)
    {
     int32 j;

     /* bootstrap routine can be nil */
     if (dnbp->ret_veriusertf == NULL) continue;

     for (j = 0;; j++)
      {
       tfcp = &(dnbp->ret_veriusertf[j]);
       if (tfcp->type == 0) break;
       __shadow_veriusertfs[i++] = *tfcp;
      } 
    } 
  } 
 __shadow_veriusertfs[i].type = 0;
#endif
}

/*
 * during initialization routine to process and check tf_cell table entries
 *
 * put in normal system task or function table (possibly replacing built-in)
 * some execution mechanism same
 */
static void check_veriusertf_table(struct t_tfcell *boot_veriusertf)
{
 int32 i;
 struct t_tfcell *tfcp;

 /* notice, must be at least one entry or will crash */
 for (i = 0;; i++)
  {
   tfcp = &(boot_veriusertf[i]);
   switch (tfcp->type) {
    case 0: 
     /* need to start processing vpi systfs by move last systf one past end */
     /* each table ends by updating last */
     __last_systf = __last_veriusertf;
     return;
    case USERTASK: case USERFUNCTION: case USERREALFUNCTION:
     if (!chk_idnam_veriusertf(tfcp->tfname)) break;
     if (++__last_veriusertf - BASE_VERIUSERTFS >= MAXVERIUSERTFS)
      __pv_terr(320,
       "too many tasks and functions in veriusertfs (%d) and +loadpli1 bootstrap returned ptfcell tables",
       MAXVERIUSERTFS);
     if (tfcp->calltf == NULL)
      {
       __pv_warn(578,
        "PLI1 veriusertfs user function or task %s no Verilog execution routine",
        tfcp->tfname);
      }
     if (tfcp->type == USERTASK) add_veriusertf_task(tfcp);
     else add_veriusertf_func(tfcp);
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
  }
}

/*
 * add a veriuser table pli system task
 */
static void add_veriusertf_task(struct t_tfcell *tfcp)
{
 struct systsk_t *stbp;
 struct tnode_t *tnp;
 struct sy_t *syp;

 if (tfcp->sizetf != NULL)
  {
   __inform(425,
   "PLI1 veriusertfs task %s - sizetf function ignored but should not be in table",
    tfcp->tfname);
   tfcp->sizetf = NULL;
  }
 /* allocate a systsk_t entry - needed because splicing pli on and */
 /* need to be able to compile version without */
 stbp = __alloc_systsk();
 stbp->stsknam = tfcp->tfname;
 stbp->stsknum = __last_veriusertf;
 tnp = __vtfind(tfcp->tfname, __syssyms);
 if (!__sym_is_new)
  {
   syp = tnp->ndp;
   __inform(459,
    "PLI1 veriusertfs task %s replaces predefined system task or function with same name",
    syp->synam);
  }
 else
  {
   __add_sym(tfcp->tfname, tnp);
   (__syssyms->numsyms)++;
   syp = tnp->ndp;
  }
 syp->sytyp = SYM_STSK;
 syp->sydecl = TRUE;
 syp->el.esytbp = stbp;
}

/*
 * add a veriuser table pli system function (normal or real)
 */
static void add_veriusertf_func(struct t_tfcell *tfcp)
{
 struct tnode_t *tnp;
 struct sy_t *syp;
 struct sysfunc_t *sfbp;

 /* function tfcell must have sizetf or cannot execute */ 
 /* for real function know size */
 if (tfcp->type == USERFUNCTION && tfcp->sizetf == NULL)
  {
   __pv_warn(578,
    "PLI1 veriusertfs function %s sizetf function missing - assuming size 1",
    tfcp->tfname);
  }
 else if (tfcp->type == userrealfunction && tfcp->sizetf != NULL)
  {
   __inform(425,
   "PLI1 veriusertfs userrealfunction %s - sizetf function ignored but should not be in table",
    tfcp->tfname);
   tfcp->sizetf = NULL;
  }

 /* allocate a sysfunc_t entry - needed because splicing pli on and */
 /* need to be able to compile version without */
 sfbp = __alloc_sysfunc();
 sfbp->syfnum = __last_veriusertf;
 sfbp->tftyp = SYSF_TF;
 sfbp->syfnam = tfcp->tfname;
 tnp = __vtfind(tfcp->tfname, __syssyms);
 if (!__sym_is_new)
  {
   syp = tnp->ndp;
   __inform(459,
    "PLI1 veriusertfs function %s replaces predefined system task or function with same name",
    syp->synam);
  }
 else
  {
   __add_sym(tfcp->tfname, tnp);
   (__syssyms->numsyms)++;
   syp = tnp->ndp;
  }
 syp->sytyp = SYM_SF;
 syp->sydecl = TRUE;
 syp->el.esyftbp = sfbp;
}

/*
 * check for legal user tf task or function name
 */
static int32 chk_idnam_veriusertf(char *tfnam)
{
 int32 len;
 char *chp;

 chp = tfnam;
 if (*chp++ != '$') 
  {
   __pv_err(1302,
    "PLI1 - veriusertfs task or function %s must begin with '$'", tfnam); 
bad_end:   
   return(FALSE);
  }
 for (len = 1; *chp != '\0'; chp++)
  {
   /* notice no escaped names here */
   if (!isalnum(*chp) && *chp != '_' && *chp != '$')  
    {
     __pv_err(1303,
      "PLI1 veriusertfs task or function %s contains illegal char %c",
      tfnam, *chp);   
     goto bad_end;
    }
   if (++len >= IDLEN)   
    {
     /* notice cannot truncate since in user memory */
     __pv_err(1304,
      "PLI1 veriusertfs task or function %s name too long (%d)",
      tfnam, IDLEN); 
     goto bad_end;
    }
  }
 return(TRUE);
}

/*
 * allocate and initialize a system task struct for pli task
 * built-in system tasks are predefined in table
 */
extern struct systsk_t *__alloc_systsk(void)
{ 
 struct systsk_t *stbp;

 stbp = (struct systsk_t *) __my_malloc(sizeof(struct systsk_t));
 stbp->stsknam = NULL;
 stbp->stsknum = 0;
 return(stbp);
}

/*
 * allocate and initialize a system function struct for pli function
 * built-in system functions are predefined in table
 */
extern struct sysfunc_t *__alloc_sysfunc(void)
{ 
 struct sysfunc_t *sfbp;

 sfbp = (struct sysfunc_t *) __my_malloc(sizeof(struct sysfunc_t));
 sfbp->syfnam = NULL;
 /* these all all unused */ 
 sfbp->syfnum = 0;
 sfbp->retntyp = 0;
 sfbp->retsigned = FALSE;
 sfbp->retwid = 0;
 sfbp->tftyp = SYSF_UNKNOWN;
 return(sfbp);
}

/*
 * WRAPPERS THAT CALL THE USER'S TF FUNCTIONS FROM VERIUSERTFS TABLE
 */

/*
 * FUNCTION SIZETF ROUTINES CALL DURING FIXUP
 */

/*
 * call pli system function sizetf routine
 * for function sizetf must exist or will not get here
 * for userrealfunction just set to expected width (never seen by user)
 *
 * here if user calls routine that needs variable just crashes
 */
extern void __pli_func_sizetf(struct expr_t *fcallx)
{
 int32 siz, nbytes;
 word32 *wp;
 double d1;
 struct sysfunc_t *sfbp;
 struct t_tfcell *tfcp;
 struct tfinst_t tfiwrk;
 int32 (*sizetf_func)();

 sfbp = fcallx->lu.x->lu.sy->el.esyftbp;
 tfcp = &(__shadow_veriusertfs[sfbp->syfnum - BASE_VERIUSERTFS]); 
 __tfrec = fcallx->lu.x->szu.xfrec;

 /* for real function, set size and return no sizetf for real func. */
 if (tfcp->type == userrealfunction)
  {
   __tfrec->fretsiz = REALBITS;
   __tfrec->fretreal = TRUE;
   fcallx->is_real = TRUE;
   fcallx->has_sign = TRUE;
   /* since not checked need to set width for real */
   fcallx->szu.xclen = REALBITS;

   /* set the 0th expression for tf userrealfunction */
   /* points to value not expr. that is initialzed to 0.0 */
   nbytes = 2*wlen_(__tfrec->fretsiz)*WRDBYTES;
   wp = __tfrec->tfargs[0].arg.awp = (word32 *) __my_malloc(nbytes);
   /* initialize to 0.0 since no internals for pli func and double */
   d1 = 0.0;
   memcpy(wp, &d1, nbytes); 
   return;
  }
 sizetf_func = tfcp->sizetf; 

 if (sizetf_func == NULL)
  {
   siz = 1;
   goto have_size;
  }

 /* run in first inst. itree loc. - know moditps built by here */ 
 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = fcallx;
 __tfinst->tfstp = NULL;
 __tfinst->tfidp = NULL; 

 /* FIXME ??? - not 64 bit clean */
 siz = (*sizetf_func)((int32) tfcp->data, REASON_SIZETF);
 if (siz < 1 || siz > MAXNUMBITS)
  {
   __sgferr(1277,
    "tf_ function %s sizetf routine returned illegal size value %d",
    tfcp->tfname, siz);
   __tfinst = NULL;
   __tfrec = NULL;
   return;
  }

have_size:
 __tfrec->fretsiz = siz;
 /* SJM 04/07/03 - this is needed by compiler so much be also set */
 /* worked for vpi becausxe no tf rec alternative size location */
 sfbp->retwid = siz;

 /* set the 0th expression for tf function */
 /* points to value not expr. that is initialized to x */
 nbytes = 2*wlen_(__tfrec->fretsiz)*WRDBYTES;
 wp = __tfrec->tfargs[0].arg.awp = (word32 *) __my_malloc(nbytes);
 /* initialize to x since no internals for pli functions */
 one_allbits_(wp, 2*__tfrec->fretsiz); 
 fcallx->szu.xclen = __tfrec->fretsiz;
 __tfinst = NULL;
 __tfrec = NULL;
}

/*
 * CHECKTF ROUTINES CALLED NEAR END OF PREP
 */

/*
 * go through list of all task and function tf_ calls
 */
extern void __call_all_checktfs(void)
{
 struct tfrec_t *tfrp;

 for (tfrp = __tfrec_hdr; tfrp != NULL; tfrp = tfrp->tfrnxt)
  {
   if (tfrp->tf_func) pli_func_checktf(tfrp->tfu.callx);
   else pli_task_checktf(tfrp->tfu.tfstp);
  }
}

/*
 * call pli system function checktf
 *
 * must be called after call tf record built
 * this needs to be left in .a file since locates problem
 * LOOKATME if user tries to make sim tf_ calls will crash
 */
static void pli_func_checktf(struct expr_t *fcallx)
{
 struct t_tfcell *tfcp;
 struct sysfunc_t *sfbp;
 struct tfinst_t tfiwrk;
 int32 (*checktf_func)();
 decl_idp_locals_;

 sfbp = fcallx->lu.x->lu.sy->el.esyftbp;
 tfcp = &(__shadow_veriusertfs[sfbp->syfnum - BASE_VERIUSERTFS]); 

 checktf_func = tfcp->checktf; 
 if (checktf_func == NULL) return;

 __tfrec = fcallx->lu.x->szu.xfrec;
 /* run in first inst. itree loc. - know moditps built by here */
 /* if interactive just run in current itree loc. */
 /* DBG remove --- */
 if (__tfrec->tf_inmdp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---*/
 set_save_idp_(__tfrec->tf_inmdp->moditps[0]->it_idp);

 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = fcallx;
 __tfinst->tfstp = NULL;
 __tfinst->tfidp = __idp; 

 /* FIXME ??? - not 64 bit clean */
 (*checktf_func)((int32) tfcp->data, REASON_CHECKTF);

 __tfinst = NULL;
 __tfrec = NULL;
 restore_idp_();
}

/*
 * call checktf for task
 * runs in first instance tree location
 * this routine must stay in .a lib
 */ 
static void pli_task_checktf(struct st_t *stp) 
{
 int32 sav_fnam_ind, sav_slin_cnt;
 struct tskcall_t *tkcp;
 struct t_tfcell *tfcp;
 struct systsk_t *stbp;
 struct tfinst_t tfiwrk;
 int32 (*checktf_func)();
 decl_idp_locals_;

 /* statement is task call not task definition */
 tkcp = &(stp->st.stkc);
 stbp = tkcp->tsksyx->lu.sy->el.esytbp;
 tfcp = &(__shadow_veriusertfs[stbp->stsknum - BASE_VERIUSERTFS]); 

 checktf_func = tfcp->checktf; 
 if (checktf_func == NULL) return;

 __tfrec = tkcp->tkcaux.trec;
 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;
 __vpifnam_ind = __sfnam_ind; 
 __vpilin_cnt = __slin_cnt;

 /* if interactive just run in current itree loc. */
 /* DBG remove --- */
 if (__tfrec->tf_inmdp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---*/
 set_save_idp_(__tfrec->tf_inmdp->moditps[0]->it_idp);
 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = NULL;
 __tfinst->tfstp = stp;
 __tfinst->tfidp = __idp; 

 /* FIXME ??? - not 64 bit clean */
 (*checktf_func)((int32) tfcp->data, REASON_CHECKTF);

 restore_idp_();
 __tfrec = NULL;
 __tfinst = NULL;
 __sfnam_ind = sav_fnam_ind; __slin_cnt = sav_slin_cnt;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;
}

/*
 * ROUTINES FOR CALLING ALL MISCTF ROUTINES AT CHANGES
 */

/*
 * calling misctfs need to be here so can use REASON constants
 */
extern void __call_misctfs_streset(void)
{
 call_allinsts_misctfs(REASON_RESET);
}

extern void __call_misctfs_endreset(void)
{
 call_allinsts_misctfs(REASON_ENDOFRESET);
}

extern void __call_misctfs_simstart(void)
{
 call_allinsts_misctfs(REASON_ENDOFCOMPILE);
}

extern void __call_misctfs_iact(void)
{
 call_allinsts_misctfs(REASON_INTERACTIVE);
}

extern void __call_misctfs_finish(void)
{
 call_allinsts_misctfs(REASON_FINISH);
}

extern void __call_misctfs_scope(void)
{
 call_allinsts_misctfs(REASON_SCOPE);
}

/*
 * go through list of all task and function tf_ calls
 * and call misctf for every instance of every call
 */
static void call_allinsts_misctfs(int32 reason)
{
 struct tfrec_t *tfrp;

 for (tfrp = __tfrec_hdr; tfrp != NULL; tfrp = tfrp->tfrnxt)
  misc_call_misctf(tfrp, reason);
}

/*
 * call the misctf routine for misceallaneous reason
 */
static void misc_call_misctf(struct tfrec_t *tfrp, int32 reason)
{
 int32 ii, sav_fnam_ind, sav_slin_cnt;
 struct t_tfcell *tfcp;
 struct tfinst_t tfiwrk;
 struct mod_t *mdp;
 int32 (*misctf)(int32, int32, int32);
 decl_idp_locals_;

 __tfrec = tfrp;
 /* if no misc. tf routine just turn off, nothing to do */
 tfcp = get_tfcell(__tfrec);
 if ((misctf = tfcp->misctf) == NULL) return;

 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;
 __vpifnam_ind = __sfnam_ind; 
 __vpilin_cnt = __slin_cnt;

 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = NULL;
 __tfinst->tfstp = NULL;
 if (__tfrec->tf_func) __tfinst->callx = __tfrec->tfu.callx;
 else __tfinst->tfstp = __tfrec->tfu.tfstp;
 mdp = __tfrec->tf_inmdp;

 /* DBG remove --- */
 if (mdp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---*/
 save_idp_();
 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   set_idp_(mdp->moditps[ii]->it_idp); 
   __tfinst->tfidp = __idp; 

   /* SJM 06/13/1999 - misctf always requires 3rd argument although */
   /* ignored except for syncon callbacks ?? */
   /* FIXME ??? - not 64 bit clean */
   (*misctf)((int32) tfcp->data, reason, 0);
  }
 restore_idp_();
 __tfrec = NULL;
 __tfinst = NULL;
 __sfnam_ind = sav_fnam_ind; __slin_cnt = sav_slin_cnt;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;
}

/*
 * get a tfcell name
 */
extern char *__get_tfcellnam(struct tfrec_t *tfrp)
{
 struct t_tfcell *tfcp;

 tfcp = get_tfcell(tfrp);
 return(tfcp->tfname);
}

/*
 * get a tfcell record from a tfrec  
 */
static struct t_tfcell *get_tfcell(struct tfrec_t *tfrp)
{
 struct t_tfcell *tfcp;
 struct systsk_t *stbp;
 struct sysfunc_t *sfbp;

 if (tfrp->tf_func)
  {
   sfbp = tfrp->tfu.callx->lu.x->lu.sy->el.esyftbp;
   tfcp = &(__shadow_veriusertfs[sfbp->syfnum - BASE_VERIUSERTFS]); 
   return(tfcp);
  }
 stbp = tfrp->tfu.tfstp->st.stkc.tsksyx->lu.sy->el.esytbp;
 tfcp = &(__shadow_veriusertfs[stbp->stsknum - BASE_VERIUSERTFS]); 
 return(tfcp);
}

/*
 * WRAPPERS THAT CALL THE USER'S TF TASKS FROM VERIUSERTFS TABLE
 */

/*
 * execute the pli system function calltf routine
 * this pushes return value on top of expr. stack but does not return it
 * this uses the instance tree loc. called from
 */
extern void __pli_func_calltf(struct expr_t *fcallx)
{
 int32 nbytes, sav_fnam_ind, sav_slin_cnt;
 struct t_tfcell *tfcp;
 struct sysfunc_t *sfbp;
 struct xstk_t *xsp;
 struct tfinst_t tfiwrk;
 int32 (*calltf_func)();
      
 sfbp = fcallx->lu.x->lu.sy->el.esyftbp;
 tfcp = &(__shadow_veriusertfs[sfbp->syfnum - BASE_VERIUSERTFS]); 
 __tfrec = fcallx->lu.x->szu.xfrec;

 if ((calltf_func = tfcp->calltf) == NULL)
  {
   push_xstk_(xsp, __tfrec->fretsiz);
   one_allbits_(xsp->ap, xsp->xslen);
   one_allbits_(xsp->bp, xsp->xslen);
   __tfrec = NULL;
   return;
  }

 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;
 __vpifnam_ind = __sfnam_ind; 
 __vpilin_cnt = __slin_cnt;

 /* set up environment that is current implied tf instance */
 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = fcallx;
 __tfinst->tfstp = NULL;
 __tfinst->tfidp = __idp; 

 /* FIXME ??? - not 64 bit clean */
 (*calltf_func)((int32) tfcp->data, REASON_CALLTF);

 /* must store return value from caller's itree loc. */ 
 nbytes = 2*wlen_(__tfrec->fretsiz)*WRDBYTES;
 push_xstk_(xsp, __tfrec->fretsiz);
 /* this requires contiguous a and b stack values */
 memcpy(xsp->ap, __tfrec->tfargs[0].arg.awp, nbytes); 

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;
 __tfrec = NULL;
 __tfinst = NULL;
} 

/*
 * call the pli tf system task calltf routine
 */
extern void __pli_task_calltf(struct st_t *stp)
{
 int32 sav_fnam_ind, sav_slin_cnt;
 struct tskcall_t *tkcp;
 struct t_tfcell *tfcp;
 struct systsk_t *stbp;
 struct tfinst_t tfiwrk;
 int32 (*calltf_tsk)();
      
 tkcp = &(stp->st.stkc);
 stbp = tkcp->tsksyx->lu.sy->el.esytbp;
 tfcp = &(__shadow_veriusertfs[stbp->stsknum - BASE_VERIUSERTFS]); 

 if ((calltf_tsk = tfcp->calltf) == NULL) return;

 __tfrec = tkcp->tkcaux.trec;
 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;
 __vpifnam_ind = __sfnam_ind; 
 __vpilin_cnt = __slin_cnt;

 /* set up environment that is current implied tf instance */
 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = NULL;
 __tfinst->tfstp = stp;
 __tfinst->tfidp = __idp; 

 /* FIXME ??? - not 64 bit clean */
 (*calltf_tsk)((int32) tfcp->data, REASON_CALLTF);

 __tfrec = NULL;
 __tfinst = NULL;
 __sfnam_ind = sav_fnam_ind; __slin_cnt = sav_slin_cnt;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;
}

/*
 * USER CALLABLE TF_ ROUTINES GROUPED BY TYPE - UTILITY TOWARD BOTTOM
 */

/*
 * EXPRESSION AND VALUE INFORMATION ROUTINES
 */

/*
 * get number of parameters (user pli tasks are variable arg. no.) that
 * if checked done by user routine
 * LOOKATME - does this really need to be other inst?
 */
extern int32 tf_inump(char *inst)
{
 struct tfinst_t *tfip;
 struct tfrec_t *tfrp;
 
 tfip = (struct tfinst_t *) inst;
 if (tfip->callx != NULL) tfrp = tfip->callx->lu.x->szu.xfrec;
 else tfrp = tfip->tfstp->st.stkc.tkcaux.trec;
 return(tfrp->tfanump1 - 1);
}

/*
 * number of params from saved system task call
 */
extern int32 tf_nump(void)
{
 if (__tfrec == NULL) return(bad_notfcontext_err("tf_nump"));
 return(__tfrec->tfanump1 - 1);
}

/*
 * get parameter type 
 */
extern int32 tf_itypep(int32 pnum, char *inst)
{
 int32 rv;
 struct tfinst_t *tfip;
 struct tfrec_t *sav_tfrp;

 sav_tfrp = __tfrec; 
 tfip = (struct tfinst_t *) inst;
 if (tfip->callx != NULL) __tfrec = tfip->callx->lu.x->szu.xfrec;
 else __tfrec = tfip->tfstp->st.stkc.tkcaux.trec;

 rv = tf_typep(pnum);
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_typep(int32 pnum)
{
 struct expr_t *xp;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_typep"));
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return(TF_NULLPARAM);
 if (pnum == 0)
  {
   if (!__tfrec->tf_func) return(TF_NULLPARAM);
   if (__tfrec->fretreal) return(TF_READWRITEREAL);
   return(TF_READWRITE);
  }
 xp = __tfrec->tfargs[pnum].arg.axp;

 if (xp->tf_isrw)
  {
   if (xp->is_real) return(TF_READWRITEREAL);
   return(TF_READWRITE);
  }
 if (xp->optyp == NUMBER && xp->is_string) return(TF_STRING);
 if (xp->optyp == OPEMPTY) return(TF_NULLPARAM);
 if (xp->is_real) return(TF_READONLYREAL);
 return(TF_READONLY);
}

/*
 * return bit length of parameter
 * return size of parameter in bits - 0 for real
 */
extern int32 tf_isizep(int32 pnum, char *inst)
{
 int32 rv;
 struct tfinst_t *tfip;
 struct tfrec_t *sav_tfrp;

 sav_tfrp = __tfrec; 
 tfip = (struct tfinst_t *) inst;
 if (tfip->callx != NULL) __tfrec = tfip->callx->lu.x->szu.xfrec;
 else __tfrec = tfip->tfstp->st.stkc.tkcaux.trec;
 rv = tf_sizep(pnum);

 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_sizep(int32 pnum)
{
 struct expr_t *xp;
 
 if (__tfrec == NULL) return(bad_notfcontext_err("tf_sizep"));
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return(TF_NULLPARAM);
 if (pnum == 0)
  {
   if (__tfrec->fretreal) return(TF_NULLPARAM);
   return(__tfrec->fretsiz);
  }
 xp = __tfrec->tfargs[pnum].arg.axp;
 if (xp->is_real) return(TF_NULLPARAM);
 return(xp->szu.xclen);
}

/*
 * EXPRINFO AND NODINFO ROUTINES
 */

/* macro to saves and sets inst form environment */
/* need to be in normal code not part of block or if */
#define set_tfinst_(inst, stfip, stfrp) \
 stfip = __tfinst; \
 stfrp = __tfrec; \
 __tfinst = (struct tfinst_t *) inst; \
 if (__tfinst->callx != NULL) __tfrec = __tfinst->callx->lu.x->szu.xfrec; \
 else __tfrec = __tfinst->tfstp->st.stkc.tkcaux.trec;



/* 
 * return node info struct from nparam for read-write (lhs) expr. only  
 * node info if for underlying object in case select or index
 * cannot access pli func. return values here (no nodes)
 *
 * LOOKATME - need to find out 1 bit representation (always stren)
 * for now strength illegal since standard document method for storing
 * strength impossible (provided by 2.0 so leave)
 */
extern p_tfnodeinfo tf_inodeinfo(int32 pnum, p_tfnodeinfo pinfo, char *inst)
{
 struct t_tfnodeinfo *pinfo2;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 pinfo2 = tf_nodeinfo(pnum, pinfo);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(pinfo2);
}

extern p_tfnodeinfo tf_nodeinfo(int32 pnum, p_tfnodeinfo pinfo)
{
 int32 wlen, mwid, r1, r2, biti, bitj;
 int32 ai, ndx, undx, blen, nbytes, num_elements;
 struct xstk_t *xsp;
 struct net_t *np;
 char *chp;
 double d1;
 struct tfarg_t *tfap;
 struct expr_t *xp;
 struct gref_t *grp;
 t_midat *xmr_idp;
 decl_idp_locals_;

 if (__tfrec == NULL) { bad_notfcontext_err("tf_nodeinfo"); return(NULL); }
 if (pnum < 1 || pnum >= __tfrec->tfanump1) return(NULL);
 tfap = &(__tfrec->tfargs[pnum]);
 xp = tfap->arg.axp;
 init_nodeinfo(pinfo);
 /* if not rw (concat not rw), return null */
 if (!xp->tf_isrw) return(NULL);
 
 /* AIV 02/14/12 - if XMR need to set/restore the xmr idp area */
 save_idp = NULL;
 if (xp->optyp == GLBREF)
  {
   grp = xp->ru.grp;
   xmr_idp = __xmrget_refgrp_to_targ(grp);
   set_save_idp_(xmr_idp); 
  }

 /* cannot handle strength since as documented no way to store value */ 
 np = tfap->anp;
 if (np->n_stren)
  __sgfinform(489,
   "tf_nodeinfo of strength wire %s node_value set to value part only",
   np->nsym->synam);  

 /* SJM 10/30/99 - now using tf exprinfo for propagatep following new LRM */

 /* notice node_lhs_element and node_rhs_element unused */
 /* set the symbol name field */
 /* not my malloc can only call malloc (no other alloc scheme possible) */
 pinfo->node_symbol = __mytf_malloc(strlen(np->nsym->synam) + 1);
 strcpy(pinfo->node_symbol, np->nsym->synam);

 /* real is special case - no range */
 /* real array select work handled in xpr eval */
 if (np->ntyp == N_REAL)
  {
   xsp = __eval_xpr(xp); 
   pinfo->node_type = TF_REAL_NODE;
   /* eval of expr. always gets underlying value and handles xmr */
   /* notice for xmr, this will acess from right place - cannot push grp */
   memcpy(&d1, xsp->ap, sizeof(double));

   pinfo->node_value.real_val_p =
    (double *) __mytf_malloc(sizeof(double));
   *(pinfo->node_value.real_val_p) = d1;
   __pop_xstk();
   if (save_idp != NULL) { restore_idp_(); }
   return(pinfo);
  }

 /* set the vector size (component element for array) */
 pinfo->node_sign = np->n_signed;

 /* select of array (not entire) array special case */
 if (np->n_isarr)
  {
   pinfo->node_vec_size = np->nwid;
   pinfo->node_type = TF_MEMORY_NODE;
   mwid = __get_arrwide(np);
   pinfo->node_mem_size = mwid;
   /* DBG remove */
   if (np->nrngrep != NX_ARR) __misc_terr(__FILE__, __LINE__);
   /* --- */
   /* get range not size */
   pinfo->node_ms_index = np->nu.rngarr->ai1;
   pinfo->node_ls_index = np->nu.rngarr->ai2;
   /* each group is both 32 bits of a part and 32 bits of b */
   /* notice memory expression are always entire variable */

//AIV 01/24/12 - think this is how this is supposed to work - was never
//correct - must return entire array and a pointer in memoryval_p
//notice this must copy the entire array - so it is inefficient
//going to emit a message for now - stating to use VPI/DPI

   {
    struct t_tfcell *tfcp;

    tfcp = get_tfcell(__tfrec);
    __pv_warn(1404,
    "PLI1 - passing memory (array) - to tf_nodeinfo (via %s) is inefficient better to use VPI or DPI instead.", tfcp->tfname,
     np->nsym->synam); 
   }

   /* AIV 01/27/12 - now handling if array[10] - passed must start at */
   /* element 10 and fill the rest */
   if (xp->optyp == LSB)
    {
     biti = __comp_ndx(np, xp->ru.x);
     /* if passed out of range just return NULL */
     if (biti == -1)
      {
       if (save_idp != NULL) { restore_idp_(); }
       return(NULL);
      }
     biti = __unnormalize_ndx(np, biti);
    }
   else biti = 0;

   
   /* node_mem_size is the number of elements */
   num_elements = (mwid - biti);
   pinfo->node_mem_size = num_elements;
  
   blen = np->nwid;
   /* AIV 02/12/12 - this was wrong for < 8 bits was setting to 0 bytes */
   if (blen <= 8) nbytes = 1;
   else nbytes = blen/8;
   /* node_ngroups is the array size increment value (size) */
   pinfo->node_ngroups = nbytes;
   chp = __mytf_malloc(2*nbytes*num_elements);
   push_xstk_(xsp, blen);
   ndx = 0;
   /* now convert all CVC storage into standard pli a/b parts */
   for (ai = biti; ai < num_elements; ai++)
    {
     undx = __unnormalize_ndx(np, ai);
     __ld_arr_val(xsp, NULL, np, undx, NULL);
     memcpy(&(chp[ndx]), xsp->ap, nbytes);
     ndx += nbytes;
     memcpy(&(chp[ndx]), xsp->bp, nbytes);
     ndx += nbytes;
    }
   __pop_xstk();
   pinfo->node_value.memoryval_p = (char *) chp;
   if (save_idp != NULL) { restore_idp_(); }
   return(pinfo);
  }

 xsp = __eval_xpr(xp); 
 pinfo->node_vec_size = xp->szu.xclen;
 /* set the ranges of the node - always just var not mem decl. range */
 if (np->nrngrep == NX_WIR)
  { r1 = np->nu.rngwir->ni1; r2 = np->nu.rngwir->ni2; } 
 else if (np->nrngrep == NX_DWIR)
  { r1 = np->nu.rngdwir->ni1; r2 = np->nu.rngdwir->ni2; }
 else r1 = r2 = -1;

 /* assume entire range */
 pinfo->node_ms_index = r1;
 pinfo->node_ls_index = r2;
 /* for non scalar, non memory and non real, this is expression range */
 /* if non constant index (for reg) - use entire range */

 biti = -1;
 if (xp->optyp == LSB)
  {
   /* if anything but simple number, range is entire - per change op rules */
   if (xp->ru.x->optyp == NUMBER)  
    {
     biti = __contab[xp->ru.x->ru.xvi];
     pinfo->node_ms_index = pinfo->node_ls_index = __unnormalize_ndx(np, biti);
    }
  }  
 else if (xp->optyp == PARTSEL)
  {
   biti = __contab[xp->ru.x->lu.x->ru.xvi];
   bitj = __contab[xp->ru.x->ru.x->ru.xvi];
   pinfo->node_ms_index = __unnormalize_ndx(np, biti);
   pinfo->node_ls_index = __unnormalize_ndx(np, bitj);
  } 
 else if (xp->optyp == PARTSEL_NDX_PLUS || xp->optyp == PARTSEL_NDX_PLUS)
  {
   __get_indexed_psel_range(xp, &biti, &bitj);
   pinfo->node_ms_index = biti;
   pinfo->node_ls_index = bitj;
  }

 /* set node type field */
 if (!np->n_isavec) 
  {
   if (np->ntyp < NONWIRE_ST) pinfo->node_type = TF_NETSCALAR_NODE;
   else pinfo->node_type = TF_REG_NODE;
  } 
 else
  { 
   if (np->ntyp == N_REG || np->ntyp == N_LOGIC)
    {
     pinfo->node_type = TF_REG_NODE;
    }
   else if (np->ntyp == N_INT) pinfo->node_type = TF_INTEGER_NODE;
   else if (np->ntyp == N_TIME) pinfo->node_type = TF_TIME_NODE;
   else pinfo->node_type = TF_NETVECTOR_NODE;
  }
 /* correct for bit select from scalared wire to TF_NETSCALAR */
 /* must be constant bit select from scalared wire vector */
 if (pinfo->node_type == TF_NETVECTOR_NODE)
  {
   if (np->vec_scalared && biti != -1) pinfo->node_type = TF_NETSCALAR_NODE;
  }

 wlen = wlen_(xp->szu.xclen);
 pinfo->node_ngroups = wlen;
 /* know strength here impossible */
 allocset_vecval(pinfo, xsp, wlen);
 __pop_xstk();
 
 if (save_idp != NULL)
  {
   restore_idp_();
  }
 return(pinfo);
}

/*
 * allocate and set the vecval_p field
 */
static void allocset_vecval(struct t_tfnodeinfo *pinfo, struct xstk_t *xsp,
 int32 wlen)
{
 int32 wi;
 struct t_vecval *vecp;

 pinfo->node_value.vecval_p = (struct t_vecval *)
  __mytf_malloc(wlen*sizeof(struct t_vecval));
 vecp = pinfo->node_value.vecval_p;
 for (wi = 0; wi < wlen; wi++)
  {
   vecp[wi].avalbits = (int32) xsp->ap[wi]; 
   vecp[wi].bvalbits = (int32) xsp->bp[wi]; 
  }
}

/*
 * emit error for illegal routine called from checktf or sizetf
 * or before start of ims
 */
static int32 bad_nosimtf_err(char *rnam) 
{
 __sgferr(1289,
  "%s routine not callable before start of sim, during reset, or from checktf or sizetf because sets value or delay",
  rnam);
 return(TF_NULLPARAM);
}

/*
 * emit error for tf calls when there is no tf context
 */
static int32 bad_notfcontext_err(char *rnam)
{
 __sgferr(1289,
  "%s routine not callable because user code not invoked by PLI 1.0 - was systf registered using vpi_?",
  rnam);
 return(TF_NULLPARAM);
}

/*
 * emit error for illegal routine called from checktf or sizetf
 */
static int32 bad_rosync_err(char *rnam) 
{
 __sgferr(1299,
  "%s routine not callable during ro sync - it schedules or writes", rnam);
 return(TF_NULLPARAM);
}

/*
 * initialize an node info struct
 */
static void init_nodeinfo(struct t_tfnodeinfo *ninfop)
{
 ninfop->node_type = TF_NULL_NODE;
 ninfop->node_value.vecval_p = NULL;
 ninfop->node_symbol = NULL;
 ninfop->node_ngroups = 0;
 ninfop->node_vec_size = 0;
 ninfop->node_sign = FALSE;
 ninfop->node_ms_index = 0; 
 ninfop->node_ls_index = 0;
 ninfop->node_mem_size = 0;
 ninfop->node_lhs_element = 0;
 ninfop->node_rhs_element = 0;
 ninfop->node_handle = NULL;
}

/*
 * fill passed exprinfo struct from nparam
 */
extern p_tfexprinfo tf_iexprinfo(int32 pnum, p_tfexprinfo pinfo, char *inst)
{
 struct t_tfexprinfo *pinfo2;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 pinfo2 = tf_exprinfo(pnum, pinfo);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(pinfo2);
}

extern p_tfexprinfo tf_exprinfo(int32 pnum, p_tfexprinfo pinfo)
{
 int32 wi, wlen, slen, inum;
 word32 *wp;
 double d1;
 struct expr_t *xp;
 struct xstk_t *xsp;
 struct tfarg_t *tfap;
 struct net_t *np;
 char *chp;

 if (__tfrec == NULL)
  {
   bad_notfcontext_err("tf_exprinfo");
   return(NULL);
  }
 if (pnum < 1 || pnum >= __tfrec->tfanump1) return(NULL);
 tfap = &(__tfrec->tfargs[pnum]);
 xp = tfap->arg.axp;
 /* save for possible use by tf_evaluatep */
 /* SJM 11/29/99 - also following new LRM and XL used by tf_propagatep */
 inum = get_inum_();
 tfap->sav_xinfos[inum] = (char *) pinfo;

 init_exprinfo(pinfo);
 pinfo->expr_type = (short) get_xinfo_typ(xp); 
 if (xp->optyp == LSB || xp->optyp == PARTSEL || xp->optyp == PARTSEL_NDX_PLUS
  || xp->optyp == PARTSEL_NDX_MINUS)
  {
   if (xp->tf_isrw) pinfo->expr_lhs_select = 1;
   else pinfo->expr_rhs_select = 1;
  }
 if (xp->optyp == NUMBER && xp->is_string) 
  {
   wp = &(__contab[xp->ru.xvi]);
   chp = __alloc_vval_to_cstr(wp, xp->szu.xclen, FALSE, FALSE);
   pinfo->expr_string = chp;
   slen = strlen(chp);
   pinfo->expr_vec_size = 8*slen;
   return(pinfo);
  }
 /* here this always handles any gref itree pushing and popping */
 xsp = __eval_xpr(xp);
 if (xp->is_real)
  {
   memcpy(&d1, xsp->ap, sizeof(double));

   pinfo->real_value = d1;
   /* SJM 09/07/99 - previous problem with signedness of reals */ 
   /* reals always signed */
   pinfo->expr_sign = TRUE;
   goto done;
  }
 /* AIV 02/03/03 - if expr is ID, signed for systf arg comes from net */
 if(xp->optyp == ID || xp->optyp == GLBREF)
  { 
   np = xp->lu.sy->el.enp;
   if (np->n_signed) pinfo->expr_sign = TRUE;
//AIV 01/24/12 - was never handling memory here - thinks this needs to handle
//array as a special case
   if (np->n_isarr) __misc_terr(__FILE__, __LINE__);
  }   
 /* only other possibility is number or param where there is no ID */
 /* so has sign will be correctly set */
 else if (xp->has_sign) pinfo->expr_sign = TRUE;
  
 pinfo->expr_vec_size = (int32) xp->szu.xclen;
 wlen = wlen_(xp->szu.xclen);
 pinfo->expr_ngroups = (int32) wlen;
 pinfo->expr_value_p = (struct t_vecval *)
  __mytf_malloc(wlen*sizeof(struct t_vecval));
 for (wi = 0; wi < wlen; wi++)
  { 
   pinfo->expr_value_p[wi].avalbits = (int32) xsp->ap[wi];
   pinfo->expr_value_p[wi].bvalbits = (int32) xsp->bp[wi];
  } 

done:
 __pop_xstk();
 return(pinfo);
}

/*
 * convert a verilog value into a c string and return in malloced string  
 * notice no truncation here mostly for PLI
 * need to leave prefix of exprline since may be called from nested func.
 * or as display argument
 */
extern char *__alloc_vval_to_cstr(word32 *ap, int32 blen, int32 nd_quotes,
 int32 space_0)
{
 int32 sav_sofs, slen;
 char *chp;

 sav_sofs = __cur_sofs;
 /* always convert escaped special character such as new line to \\n */
 __xline_vval_to_cstr(ap, blen, nd_quotes, space_0, TRUE);
 slen = __cur_sofs - sav_sofs; 
 chp = __mytf_malloc(slen + 1);
 strcpy(chp, &(__exprline[sav_sofs]));
 /* restore exprline */ 
 __cur_sofs = sav_sofs;
 __exprline[sav_sofs] = '\0';
 return(chp);
}

/*
 * initialize an expr info struct 
 */
static void init_exprinfo(struct t_tfexprinfo *xinfop)
{
 xinfop->expr_type = TF_READONLY; 
 xinfop->expr_value_p = NULL;
 xinfop->expr_string = NULL;
 xinfop->expr_ngroups = 0;
 xinfop->expr_vec_size = 0;
 xinfop->expr_sign = FALSE;
 xinfop->expr_lhs_select = 0;
 xinfop->expr_rhs_select = 0;
}

/*
 * routine to get exprinfo type
 */
static int32 get_xinfo_typ(struct expr_t *xp)
{
 struct net_t *np;

 switch (xp->optyp) {
  case OPEMPTY: return(TF_NULLPARAM); 
  case NUMBER:
   if (xp->is_string) return(TF_STRING);
   return(TF_READONLY);
  case ISNUMBER:
   if (xp->is_string) __arg_terr(__FILE__, __LINE__);
   return(TF_READONLY);
  case REALNUM: case ISREALNUM: return(TF_READONLYREAL);
 }
 /* some kind of rhs expr. that cannot be assigned to */
 if (xp->tf_isrw)
 switch (xp->optyp) {
  case ID:
  case GLBREF:
   np = xp->lu.sy->el.enp;
   if (np->ntyp == N_REAL) return(TF_READWRITEREAL);
   /* know this is id than can be lhs */
   return(TF_READWRITE);
  case LSB:
   np = xp->lu.x->lu.sy->el.enp;
   if (np->n_isarr) return(TF_RWMEMSELECT);
   return(TF_RWBITSELECT);
  case PARTSEL: case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS:
   return(TF_RWPARTSELECT);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(TF_READONLY);
}

/*
 * PARAMETER ACCESS ROUTINES
 */

extern int32 tf_igetp(int32 pnum, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_getp(pnum);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * return value of parameter as int
 * values here are assumed to be signed 
 * LOOKATME - document that ingores b val 
 * according to LRM just return the low 32 bits without any checking
 */
extern int32 tf_getp(int32 pnum)
{
 int32 rv;
 word32 *wp;
 struct expr_t *xp;
 struct xstk_t *xsp;
 char *chp;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_getp"));
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return(TF_NULLPARAM);
 /* 0 ok here for possible func. return value */

 xsp = NULL;
 /* func. return value is special case */
 if (pnum == 0)
  {
   if (!__tfrec->tf_func) return(TF_NULLPARAM);

   push_xstk_(xsp, __tfrec->fretsiz);
   wp = __tfrec->tfargs[0].arg.awp;
   memcpy(xsp->ap, wp, 2*wlen_(__tfrec->fretsiz)*WRDBYTES);
   if (__tfrec->fretreal) goto do_real;

   /* SJM 08/31/00 - misread LRM for 2 value PLI 1.0 routines x/z is 0 */
   if (!vval_is0_(xsp->bp, xsp->xslen)) rv = 0; else rv = (int32) xsp->ap[0];
   goto done;  
  }

 xp = __tfrec->tfargs[pnum].arg.axp;
 if (xp->optyp == OPEMPTY) return(TF_NULLPARAM);

 xsp = __eval_xpr(xp);
 /* if real, must round */
 if (xp->is_real)
  {
do_real:
   /* this implements Verilog style rounding */
   __cnv_stk_fromreal_toreg32(xsp);
   rv = (int32) xsp->ap[0];
   goto done;
  }
 /* if any kind of literal string - cannot be expr - need c style */
 /* the return 32 bit int32 is pointer to string */
 if (xp->optyp == NUMBER && xp->is_string)
  {
   chp = __alloc_vval_to_cstr(xsp->ap, xsp->xslen, FALSE, FALSE);
   /* FIXME ??? - not 64 bit clean */
   rv = (int32) chp;
   goto done; 
  }

 /* finally just return bit pattern - caller must interpret sign */
 /* SJM 08/31/00 - misread LRM for 2 value PLI 1.0 routines x/z is 0 */
 if (!vval_is0_(xsp->bp, xsp->xslen)) rv = 0; else rv = (int32) xsp->ap[0];
done:
 __pop_xstk();
 return(rv);
}

extern int32 tf_igetlongp(int32 *aof_highvalue, int32 pnum, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_getlongp(aof_highvalue, pnum);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * get parameter into 2 32 bit ints (64 bits non x/z)
 * if string return ptr in low 32 bits
 * if paremeter real return error, must use getrealp
 */
extern int32 tf_getlongp(int32 *aof_highvalue, int32 pnum)
{
 int32 rv;
 word32 *wp;
 double d1;
 struct expr_t *xp;
 struct xstk_t *xsp;
 char *chp;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_getlongp"));
 *aof_highvalue = 0;
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return(TF_NULLPARAM);
 /* 0 ok here for possible func. return value */

 xsp = NULL;
 /* func. return value is special case */
 if (pnum == 0)
  {
   if (!__tfrec->tf_func) return(TF_NULLPARAM);

   push_xstk_(xsp, __tfrec->fretsiz);
   wp = __tfrec->tfargs[0].arg.awp;
   memcpy(xsp->ap, wp, 2*wlen_(__tfrec->fretsiz)*WRDBYTES);
   if (__tfrec->fretreal) goto do_real;

   /* SJM 08/31/00 - misread LRM for 2 value PLI 1.0 routines x/z is 0 */
   if (!vval_is0_(xsp->bp, xsp->xslen)) { *aof_highvalue = 0; rv = 0; }
   else
    {
     /* AIV 08/25/09 - this is only one word for 64-bit put still defined */
     /* as two ints just split the 64-bit address */
#ifdef __CVC32__
     if (__tfrec->fretsiz > 32) *aof_highvalue = (int32) xsp->ap[1];
     else *aof_highvalue = 0; 
     rv = (int32) xsp->ap[0];
#else
     *aof_highvalue = (int32) ((xsp->ap[0] << 32));
     rv = (int32) xsp->ap[0] & 0xffffffffUL;
#endif
    }
   goto done;  
  }

 xp = __tfrec->tfargs[pnum].arg.axp;
 if (xp->optyp == OPEMPTY) return(TF_NULLPARAM);

 xsp = __eval_xpr(xp);
 if (xp->is_real)
  {
do_real:
   memcpy(&d1, xsp->ap, sizeof(double));
   tf_real_to_long(d1, &rv, aof_highvalue);
   goto done;
  }
 /* if any kind of literal string - cannot be expr - need c style */
 /* the return 32 bit int32 is pointer to string */
 if (xp->optyp == NUMBER && xp->is_string)
  {
   chp = __alloc_vval_to_cstr(xsp->ap, xsp->xslen, FALSE, FALSE);

   /* FIXME ??? - not 64 bit clean */
   rv = (int32) chp;
   goto done; 
  }

 /* caller must interpret any sign */
 /* SJM 08/31/00 - misread LRM for 2 value PLI 1.0 routines x/z is 0 */
 if (!vval_is0_(xsp->bp, xsp->xslen)) { *aof_highvalue = 0; rv = 0; }
 else
  {
   /* AIV 08/25/09 - this is only one word for 64-bit put still defined */
   /* as two ints just split the 64-bit address */
#ifdef __CVC32__
   if (xsp->xslen > 32) *aof_highvalue = (int32) xsp->ap[1];
   else *aof_highvalue = 0; 
   rv = (int32) xsp->ap[0];
#else
   *aof_highvalue = (int32) ((xsp->ap[0] << 32));
   rv = (int32) xsp->ap[0] & 0xffffffffUL;
#endif
  }

done:
 __pop_xstk();
 return(rv);
}

/*
 * return double from passed routine    
 */
extern double tf_igetrealp(int32 pnum, char *inst)
{
 double d1;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 d1 = tf_getrealp(pnum);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(d1);
}

/*
 * get value of nparam (convert to real if needed) and return
 * here return 0 if literal string and use signedness of node for sign of r 
 */
extern double tf_getrealp(int32 pnum)
{
 int32 i1;
 word32 *wp;
 double d1;
 word64 t1;
 struct expr_t *xp;
 struct xstk_t *xsp;

 xp = NULL;
 if (__tfrec == NULL)
  {
   bad_notfcontext_err("tf_getrealp");
   return((double) TF_NULLPARAM);
  }
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return((double) TF_NULLPARAM);

 /* 0 ok here for possible func. return value */
 /* func. return value is special case */
 if (pnum == 0)
  {
   if (!__tfrec->tf_func) return(TF_NULLPARAM);
   push_xstk_(xsp, __tfrec->fretsiz);
   wp = __tfrec->tfargs[0].arg.awp;
   if (__tfrec->fretreal)
    { memcpy(&d1, wp, sizeof(double)); goto done; }
   memcpy(xsp->ap, wp, 2*wlen_(__tfrec->fretsiz)*WRDBYTES);
   goto do_non_real;
  }

 xp = __tfrec->tfargs[pnum].arg.axp;
 /* literal string is error */
 if (xp->optyp == OPEMPTY || (xp->optyp == NUMBER && xp->is_string))
  return((double) TF_NULLPARAM);

 xsp = __eval_xpr(xp);
 /* if real, must round */
 if (xp->is_real) { memcpy(&d1, xsp->ap, sizeof(double)); goto done; }
 /* only true if int32 and exactly 32 bits */
 if (xp->has_sign) { i1 = (int32) xsp->ap[0]; d1 = (double) i1; goto done; }   

do_non_real:
 /* SJM 05/10/04 - must handle conversion of signed 33-64 to signed double */
 if (xsp->xslen > WBITS)
  {
   if (xp->has_sign) d1 = __cnvt_signed64_to_real(xsp->ap, xsp->xslen);
   else
    {
     /* AIV 08/25/09 - if 64-bit only one word */
#ifdef __CVC32__
     t1 = ((word64) xsp->ap[0]) | (((word64) xsp->ap[1]) << 32); 
#else
     t1 = xsp->ap[0];
#endif
     if (!__v64_to_real(&d1, &t1)) d1 = 0.0;
    }
  }
 else d1 = (double) xsp->ap[0];

done:
 __pop_xstk();
 return(d1);
}

/*
 * convert signed 33 to 64 bit to real - tricky if narrow than 64
 */
extern double __cnvt_signed64_to_real(word32 *ap, int32 blen)
{
 word64 t1;
 sword64 st1;
 double d1;
 
 /* DBG remove -- */
 if (blen <= WBITS) __misc_terr(__FILE__, __LINE__);
 /* -- */

 /* t1 is just the word32 bit pattern */
 /* AIV 08/25/09 - if 64-bit only one word */
#ifdef __CVC32__
 t1 = ((word64) ap[0]) | (((word64) ap[1]) << 32); 
#else
 t1 = ap[0];
#endif
 if (__is_lnegative(ap, blen))
  {
   t1 &= (((word64) ~(__masktab[ubits_(blen)])) << 32);
   st1 = (sword64) t1;
   st1 = -st1;
   t1 = (word64) st1;
   if (!__v64_to_real(&d1, &t1)) d1 = 0.0;
   else d1 = -d1;
  }
 else
  {
   if (!__v64_to_real(&d1, &t1)) d1 = 0.0;
  }
 return(d1);
}

/*
 * TF_ PARAMETER STORE ROUTINES
 */

extern int32 tf_iputp(int32 pnum, int32 value, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_putp(pnum, value);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * assign int32 value to parameter nparm
 * return 0 on error else 1 and assign 
 */
extern int32 tf_putp(int32 pnum, int32 value)
{
 int32 rv;
 word32 *wp;
 struct tfarg_t *tfap;
 struct expr_t *xp;
 struct xstk_t *xsp;

 if (__run_state != SS_SIM)
  {
   rv = bad_nosimtf_err("tf_(i)putp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__rosync_slot)
  {
   rv = bad_rosync_err("tf_(i)putp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_putp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return(1);

 tfap = &(__tfrec->tfargs[pnum]);
 /* 0 ok here for possible func. return value */
 /* func. return value is special case - change return value, no assign */
 if (pnum == 0)
  {
   push_xstk_(xsp, WBITS);
   xsp->ap[0] = (word32) value;
   xsp->bp[0] = 0L;

   if (!__tfrec->tf_func) return(1);
   if (__tfrec->fretreal) __cnv_stk_fromreg_toreal(xsp, TRUE);
   /* contiguous bytes of stack have value after possible conversion */
   /* SJM 05/10/04 - deprecated PLI 1.0 can only return word32 regs */ 
   else if (xsp->xslen != __tfrec->fretsiz)
    {
     __sizchgxs(xsp, __tfrec->fretsiz);
    }
   wp = tfap->arg.awp;
   memcpy(wp, xsp->ap, 2*wlen_(__tfrec->fretsiz)*WRDBYTES);
   __pop_xstk();
   return(0);
  }

 xp = tfap->arg.axp;
 if (!xp->tf_isrw) return(1);
 push_xstk_(xsp, WBITS);
 xsp->ap[0] = (word32) value;
 xsp->bp[0] = 0L;

 /* assigned to param is real must convert before assign */ 
 if (xp->is_real) __cnv_stk_fromreg_toreal(xsp, TRUE);
 /* SJM 05/10/04 - deprecated PLI 1.0 can only return word32 regs */ 
 else if (xsp->xslen != xp->szu.xclen) __sizchgxs(xsp, xp->szu.xclen);
 /* ok to assign (by continuous) to wire */
 exec_tfarg_assign(tfap, xp, xsp->ap, xsp->bp);
 __pop_xstk();
 return(0);
}

extern int32 tf_iputlongp(int32 pnum, int32 lowvalue, int32 highvalue, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_putlongp(pnum, lowvalue, highvalue);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * input is 64 bit as 2 ints that is assigned to expr.
 * may need to convert stack to right lhs width and type
 * return 0 on error else 1 and assign
 */
extern int32 tf_putlongp(int32 pnum, int32 lowvalue, int32 highvalue)
{
 int32 rv;
 double d1;
 struct tfarg_t *tfap;
 struct expr_t *xp;
 struct xstk_t *xsp;

 if (__run_state != SS_SIM)
  {
   rv = bad_nosimtf_err("tf_(i)putlongp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__rosync_slot)
  {
   rv = bad_rosync_err("tf_(i)putlongp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_putlongp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return(1);

 tfap = &(__tfrec->tfargs[pnum]);
 /* 0 ok here for possible func. return value */
 /* func. return value is special case - change return value, no assign */
 if (pnum == 0)
  {
   if (!__tfrec->tf_func) return(1);

   /* if assigning to real convert - but rule is to ignore high 32 bits here */
   if (__tfrec->fretreal)
    {
     tf_long_to_real(lowvalue, highvalue, &d1);
     memcpy(tfap->arg.awp, &d1, sizeof(double));
     return(0);
    }   

   push_xstk_(xsp, 64);

   /* AIV 08/25/09 - if 64-bit only one word */
#ifdef __CVC32__
   xsp->ap[0] = (word32) lowvalue;
   xsp->ap[1] = (word32) highvalue; 
   xsp->bp[0] = xsp->bp[1] = 0L;
#else
   xsp->ap[0] = ((word64) lowvalue) | (((word64) highvalue) << 32); 
   xsp->bp[0] = 0L;
#endif
   /* contiguous bytes of stack have value after possible conversion */
   /* SJM 05/10/04 - deprecated PLI 1.0 can only return word32 regs */ 
   if (xsp->xslen != __tfrec->fretsiz) __sizchgxs(xsp, __tfrec->fretsiz);
   memcpy(tfap->arg.awp, xsp->ap, 2*wlen_(__tfrec->fretsiz)*WRDBYTES);
   __pop_xstk();
   return(0);
  }

 xp = tfap->arg.axp;
 if (!xp->tf_isrw) return(1);

 /* assigned to param is real must convert to double before assign */ 
 /* this must use time long form */
 if (xp->is_real)
  {
   tf_long_to_real(lowvalue, highvalue, &d1);
   push_xstk_(xsp, REALBITS);
   memcpy(xsp->ap, &d1, sizeof(double));
  } 
 else
  { 
   push_xstk_(xsp, 64);
   /* AIV 08/25/09 - if 64-bit only one word */
#ifdef __CVC32__
   xsp->ap[0] = (word32) lowvalue;
   xsp->ap[1] = (word32) highvalue; 
   xsp->bp[0] = xsp->bp[1] = 0L;
#else
   xsp->ap[0] = ((word64) lowvalue) | (((word64) highvalue) << 32); 
   xsp->bp[0] = 0L;
#endif
   /* SJM 05/10/04 - deprecated PLI 1.0 can only return word32 regs */ 
   if (xsp->xslen != xp->szu.xclen) __sizchgxs(xsp, xp->szu.xclen);
  }
 exec_tfarg_assign(tfap, xp, xsp->ap, xsp->bp);
 __pop_xstk();
 return(0);
}

extern int32 tf_iputrealp(int32 pnum, double value, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_putrealp(pnum, value);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * assign real value to paramter nparm
 */
extern int32 tf_putrealp(int32 pnum, double value)
{
 int32 rv;
 struct tfarg_t *tfap;
 struct expr_t *xp;
 struct xstk_t *xsp;

 if (__run_state != SS_SIM)
  {
   rv = bad_nosimtf_err("tf_(i)putrealp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__rosync_slot)
  {
   rv = bad_rosync_err("tf_(i)putrealp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_putrealp");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return(1);

 tfap = &(__tfrec->tfargs[pnum]);
 /* 0 ok here for possible func. return value */
 /* func. return value is special case - change return value, no assign */
 if (pnum == 0)
  {
   if (!__tfrec->tf_func) return(1);
   if (__tfrec->fretreal)
    {
     memcpy(tfap->arg.awp, &value, sizeof(double));
     return(0);
    }
   if ((xsp = tf_pushconvfromreal(value, __tfrec->fretsiz)) == NULL)
    return(1);
   memcpy(tfap->arg.awp, xsp->ap, 2*wlen_(__tfrec->fretsiz)*WRDBYTES);
   __pop_xstk();
   return(0);
  }

 xp = tfap->arg.axp;
 if (!xp->tf_isrw) return(1);

 if (xp->is_real)
  {
   push_xstk_(xsp, REALBITS);
   memcpy(xsp->ap, &value, sizeof(double));
  }
 else 
  { 
   if ((xsp = tf_pushconvfromreal(value, xp->szu.xclen)) == NULL)
    return(1);
  }
 exec_tfarg_assign(tfap, xp, xsp->ap, xsp->bp);
 __pop_xstk();
 return(0);
}

/*
 * routine to push and convert to real tf task/function parameter onto stack
 * know only called 
 * returns nil with nothing on stack on error 
 */
static struct xstk_t *tf_pushconvfromreal(double d1, int32 destsiz)
{
 int32 i, lo, hi;
 struct xstk_t *xsp;

 if (destsiz > WBITS)
  {
   tf_real_to_long(d1, &lo, &hi);
   push_xstk_(xsp, 64);
   /* AIV 08/25/09 - if 64-bit only one word */
#ifdef __CVC32__
   xsp->ap[0] = (word32) lo;
   xsp->ap[1] = (word32) hi;
   xsp->bp[0] = xsp->bp[1] = 0L;
#else
   xsp->ap[0] = ((word64) lo) | (((word64) hi) << 32); 
   xsp->bp[0] = 0L;
#endif
  }
 else
  {
   push_xstk_(xsp, WBITS);
   i = (int32) d1;
   xsp->ap[0] = (word32) i;
   xsp->bp[0] = 0L;
  } 
 /* SJM 05/10/04 - deprecated PLI 1.0 can only return word32 regs */ 
 if (xsp->xslen != destsiz) __sizchgxs(xsp, destsiz);
 return(xsp);
} 

/*
 * TF STRING FORM GET VALUE (FOR X/Z) ROUTINES
 */

/*
 * get a formatted c style string
 */
extern char *tf_istrgetp(int32 pnum, int32 format_char, char *inst)
{
 char *chp;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 chp = tf_strgetp(pnum, format_char);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(chp);
}

/*
 * get a parameter into c style string  
 */ 
extern char *tf_strgetp(int32 pnum, int32 format_char)
{
 struct expr_t *xp;

 if (__tfrec == NULL)
  {
   bad_notfcontext_err("tf_strgetp");
   return(NULL);
  }
 if (pnum < 0 || pnum >= __tfrec->tfanump1) return(NULL);
 /* 0 ok here for possible func. return value */
 if (pnum == 0)
  {
   if (!__tfrec->tf_func) return(NULL);
   return(__alloc_getasfmt((struct expr_t *) NULL, __tfrec, format_char));
  }
 xp = __tfrec->tfargs[pnum].arg.axp;
 if (xp->optyp == OPEMPTY) return(NULL);

 /* if returns 0, know expr line not changed */
 return(__alloc_getasfmt(xp, (struct tfrec_t *) NULL, format_char));
}

/*
 * convert parameter to c string
 * i.e. force intrepretation as string
 */
extern char *tf_igetcstringp(int32 nparam, char *inst)
{
 char *chp;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 chp = tf_getcstringp(nparam);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(chp);
}

/*
 * convert a value to a c string - evaluate expressions if needed
 * converts bit pattern to c string 
 */
extern char *tf_getcstringp(int32 nparam)
{
 int32 blen;
 word32 *wp;
 struct expr_t *xp;
 struct xstk_t *xsp;
 char *chp;

 if (__tfrec == NULL)
  {
   bad_notfcontext_err("tf_getcstringp");
   return(NULL);
  }
 if (nparam < 0 || nparam >= __tfrec->tfanump1) return(NULL);
 /* 0 ok here for possible func. return value */
 if (nparam == 0)
  {
   if (!__tfrec->tf_func) return(NULL);
   wp = __tfrec->tfargs[0].arg.awp;
   blen = __trim1_0val(wp, __tfrec->fretsiz);
   chp = __alloc_vval_to_cstr(wp, __tfrec->fretsiz, FALSE, FALSE);
   return(chp);
  }
 xp = __tfrec->tfargs[nparam].arg.axp;
 if (xp->optyp == OPEMPTY) return(NULL);

 /* real bit pattern can't be output as string */
 if (xp->is_real) return(NULL);

 /* even if literal string can still evaluate */
 /* this takes any bit pattern (i.e. real) and makes a string */
 /* and ignores and b value */
 xsp = __eval_xpr(xp);
 /* must remove high 0 bytes */
 blen = __trim1_0val(xsp->ap, xsp->xslen);
 chp = __alloc_vval_to_cstr(xsp->ap, blen, FALSE, FALSE);
 __pop_xstk();
 return(chp);
}

/* 
 * TF_ STRING FORM PARAMETER DELAYED STORE ROUTINES
 */

/*
 * set a delay from a string that is scanfed into a value that is set
 * for nparam of length bitlength use format_char to interpret value_p
 * where schedule is delayed delay (scaled) and if of type delaytype
 * and store value into parameter which will be lhs expr. at scheduled time
 *
 * return 0 on error 1 if ok, delaytype is 0 inertial, 1 transport, 2
 * pure transport
 * must be >= 0, 0 is #0 form
 */

/*
 * schedule set for other pli task
 */
extern int32 tf_istrdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, int32 delay, int32 delaytype, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_strdelputp(nparam, bitlength, format_char, value_p, delay,
  delaytype);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_strdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, int32 delay, int32 delaytype)
{
 int32 rv;
 word64 ticks, t1;
 struct mod_t *cur_mdp;

 /* scale from module delay to ticks */
 t1 = (word64) delay;
 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) cnv_num64to_ticks_(ticks, t1, cur_mdp);
 else ticks = t1;

 rv = delayed_str_putp(nparam, bitlength, format_char, value_p,
  ticks, delaytype);
 return(rv);
}

/*
 * routine that executes all delays since only difference is form
 * of delay - by here converted to internal ticks (scaling done)
 * dtyp is delay reschedule determining mode
 * possibilities:
 * 
 * inertial replaces pending sched ev with later and removes earlier 
 * 0: normal Verilog inertial (change so exactly one delay that is latest)
 * 1: transport - remove all delays later than scheduled
 * 2: pure transport - just add delay - never remove 
 */
static int32 delayed_str_putp(int32 nparam, int32 blen, int32 fmtch, char *value,
 word64 ticksdel, int32 dtyp)
{
 int32 nbytes, inum;
 struct tfarg_t *tfap;
 struct dltevlst_t *dlp, *dlp2, *ins_after_dlp;
 word64 schtim;
 struct tev_t *tevp;
 struct expr_t *xp;
 struct tedputp_t *tedp;
 struct xstk_t *xsp;

 if (__run_state != SS_SIM) return(bad_nosimtf_err("strdelputp type"));
 if (__rosync_slot) return(bad_rosync_err("strdelputp type"));
 if (__tfrec == NULL) return(bad_notfcontext_err("strdelputp type"));

 /* cannot used schedule delayed putp to assign to return value */
 if (nparam < 1 || nparam >= __tfrec->tfanump1) return(TF_NULLPARAM);
 tfap = &(__tfrec->tfargs[nparam]);
 xp = tfap->arg.axp;
 if (!xp->tf_isrw) return(TF_NULLPARAM);
 /* push value on to stack - width is lhs needed */
 xsp = __putdstr_to_val(value, blen, xp->szu.xclen, fmtch);
 if (xsp == NULL) return(TF_NULLPARAM);

 schtim = __simtime + ticksdel;
 ins_after_dlp = NULL;
 /* eliminate new and/or cancel any olds */
 inum = get_inum_();
 if ((dlp = tfap->dputp_tedlst[inum]) != NULL)
  {
   /* case 1: inertial - remove all but one latest - return if no effect */
   if (dtyp == 0)
    {
     /* start by removing all of list but last (if needed) - know >=2 */
     if (dlp->terp != NULL)
      {
       dlp2 = __spliceout_last(dlp);
       cancel_dputp_toend(tfap, dlp);
       dlp = dlp2;
       tfap->dputp_tedlst[inum] = dlp; 
       dlp->telp = NULL;
      }
     /* by here list has exactly one element (last) */
     /* if new one earlier - do not schedule, same time, use new */
     if (dlp->tevp->etime > schtim) { __pop_xstk(); return(1); }

     /* know new event time is later - cancel all of list (i.e. 1 in list) */
     cancel_dputp_toend(tfap, dlp);
     tfap->dputp_tedlst[inum] = NULL;
     ins_after_dlp = NULL;
     goto bld_tev;
    }
   /* case 2: modified transport - remove all delays > than new */
   /* notice if same time delays must leave and insert this after all */
   /* currently scheduled for this time */
   if (dtyp == 1)
    {
     /* SJM 09/05/99 - think elmination when scheduled wrong */
     /* nothing to remove, just put on end of active pnd0 queue */
     /* SJM - if (schtim == 0ULL) goto bld_tev; WRONG */

     /* know delay list in time order */
     /* dlp2 is one before first after (maybe last), nil is before all */ 
     if ((dlp2 = __find_last_bdltevp(dlp, schtim)) == NULL) 
      { 
       /* new delay is before all - must empty list */
       /* all delays at same time not removed */
       dlp2 = tfap->dputp_tedlst[inum];
       cancel_dputp_toend(tfap, dlp2);
       tfap->dputp_tedlst[inum] = NULL;
       ins_after_dlp = NULL;
       goto bld_tev; 
      } 
     /* new delay is after all - nothing to remove */
     if (dlp2->terp == NULL) { ins_after_dlp = dlp2; goto bld_tev; } 
     /* new delay is after some and before some */
     ins_after_dlp = dlp2;
     if (dlp2->terp != NULL)
      { cancel_dputp_toend(tfap, dlp2->terp); dlp2->terp = NULL; }
     goto bld_tev;
    }
   /* case 3: pure transport - insert in right place in list */
   if (dtyp != 2) return(TF_NULLPARAM); 
   /* new delay is before all - insert at front */
   if ((dlp2 = __find_last_bdltevp(dlp, schtim)) == NULL) 
    { ins_after_dlp = NULL; goto bld_tev; }
   /* if goes after list, end of list returned else place to ins after */
   ins_after_dlp = dlp2; 
  }   

bld_tev:
 /* always build and fill the tev */
 alloc_cur_tev_(tevp, __process_putpdel_enterp, schtim);
 if (__tedpfreelst != NULL)
  {
   tedp = __tedpfreelst;
   __tedpfreelst = (struct tedputp_t *)__tedpfreelst->tedtfrp;
  }
 else tedp = (struct tedputp_t *) __my_malloc(sizeof(struct tedputp_t));
 tedp->tedtfrp = __tfrec;
 tedp->tedpnum = nparam;
 tevp->tu.tedputp = tedp;
 
 nbytes = 2*WRDBYTES*wlen_(xsp->xslen);
 tedp->tedwp = (word32 *) __my_malloc(nbytes);
 memcpy(tedp->tedwp, xsp->ap, nbytes);  
 __pop_xstk();
 /* schedule event */
 /* case 1: schedule and add to list */
 /* SJM 09/05/99 - was only adding to pound 0 at time 0 - WRONG */
 if (ticksdel == 0ULL)
  {
   if (__p0_te_hdrp == NULL) __p0_te_hdrp = __p0_te_endp = tevp;
   else 
    { 
     __p0_te_endp->tenxtp = tevp; __p0_te_endp = tevp; 
     /* AIV 08/23/10 - if compiled need to set end of time event handler */
     if (__compiled_sim) tevp->tenxtp = __free_event_pnd0_tevp;
    }
  }
 else __insert_event(tevp);
 /* build the dl tev lst */
 if (__dltevfreelst != NULL)
  { dlp = __dltevfreelst; __dltevfreelst = __dltevfreelst->terp; }
 else dlp = (struct dltevlst_t *) __my_malloc(sizeof(struct dltevlst_t)); 
 dlp->tevp = tevp;

 /* insert at front of list */
 if (ins_after_dlp == NULL)  
  {
   dlp2 = tfap->dputp_tedlst[inum];
   dlp->terp = dlp2;
   if (dlp2 != NULL) dlp2->telp = dlp;
   dlp->telp = NULL;
   tfap->dputp_tedlst[inum] = dlp;
  }
 /* insert after */
 else
  {  
   dlp->terp = ins_after_dlp->terp; 
   if (dlp->terp != NULL) dlp->terp->telp = dlp;
   ins_after_dlp->terp = dlp;
   dlp->telp = ins_after_dlp;
  }
 return(1);
}

/*
 * convert putp tf_ routine string to value
 * returns nil if number bad
 * stacked return value always lhs expected len wide 
 *
 * convert to lhs length and strength if lhs expr stren
 * this is special type of scan with mechanism not needed by v_cnv
 *
 * blen is size for building number with x/z extension - lhslen is needed
 * to convert so event eval. assign has exactly rigth width - assign convert
 *
 * allowing 'v'/'V' extension
 */
extern struct xstk_t *__putdstr_to_val(char *s, int32 blen, int32 lhslen,
 int32 fmtch)
{
 int32 slen, stlen;
 struct xstk_t *xsp;

 /* value can be at most id len postions wide - used lhs part sel. for wider */
 if (fmtch == 'v' || fmtch == 'V')
  {
   if ((slen = strlen(s)) >= IDLEN) return(NULL);
   if ((xsp = tftostrenval(s, &stlen)) == NULL) return(NULL);
   /* adjusts xslen for narrow (xsawlen alloced size) else rebuilds */
   if (stlen != lhslen) __strenwiden_sizchg(xsp, lhslen);
   return(xsp);
  }
 /* check the number - must fit in id */
 __itokbase = __to_base(fmtch);
 /* this copies string without change to num token */
 if (!chk_putdstr(s, __itokbase, &slen)) return(NULL);
 if (slen >= IDLEN) return(NULL);

 /* numeric case caller's passed length is token length */
 __itoklen = blen; 
 /* this cannot fail but to get here know string good - value in ac/bc wr k*/ 
 __to_dhboval(__itokbase, TRUE);
 push_xstk_(xsp, __itoklen);
 cp_walign_(xsp->ap, __acwrk, __itoklen);
 cp_walign_(xsp->bp, __bcwrk, __itoklen);
 /* convert in preparation for storing in event for maybe later assign */
 /* SJM 05/10/04 - deprecated PLI 1.0 can only return word32 regs */ 
 /* SJM 05/10/04 FIXME ??? ### but here could use format to determine */ 
 if (xsp->xslen != lhslen) __sizchgxs(xsp, lhslen);
 return(xsp);
}

/*
 * check a number - also copies into token (only change is '_' removed)
 * returns F on error else T returned len only valid if T 
 */
static int32 chk_putdstr(char *s, int32 base, int32 *len)
{
 int32 slen;
 char *chp, *chp2;

 /* SJM - 03/20/00 - know num token wide eough */
 for (*len = 0, slen = 0, chp = s, chp2 = __numtoken; *chp != '\0';)
  {
   if (*chp == '_') { chp++; continue; }
   if (__is_vdigit((int32) *chp, base) < 0) return(FALSE);
   *chp2++ = *chp++;
   slen++;
  }
 *chp2 = '\0';
 *len = slen;
 return(TRUE);
}

/*
 * convert to strength value
 * returns nil on error and checks for good (vector space separated) 
 */
static struct xstk_t *tftostrenval(char *s, int32 *bitlen)
{
 int32 bi, blen, done, stval;
 byte *sbp;
 struct xstk_t *xsp;
 char *chp, *chp2, s1[4];

 /* strength value is 3 char value separated by white space */
 /* 1st count - then allocate and check and build */
 *bitlen = 0;
 for (blen = 0, chp = s;;)
  {
   while (isspace(*chp)) chp++;
   if (*chp == '\0') break;
   blen++;
   while (!isspace(*chp)) { if (*chp == '\0') goto strend; else chp++; } 
  }
strend:
 /* notice blen is computed from actual chars in string */
 if (blen == 0) return(NULL);
 push_xstk_(xsp, 4*blen);
 sbp = (byte *) xsp->ap;
 for (chp = s, done = FALSE, bi = blen - 1;;)
  {
   while (isspace(*chp)) chp++;
   if (*chp == '\0') break;
   chp2 = chp;
   while (!isspace(*chp))
    { if (*chp == '\0') { done = TRUE; break; } else chp++; }
   if (chp - chp2 != 3) return(NULL);
   strncpy(s1, chp2, 3);
   s1[3] = '\0';
   if ((stval = to_stval(s1)) == -1) {__pop_xstk(); return(NULL); } 
   sbp[bi--] = (byte) stval;
   if (done) break;
  }
 *bitlen = blen;
 return(xsp);
}  

/*
 * convert from 3 character strength to 1 byte strength value
 * return F on error
 */
static int32 to_stval(char *s)
{
 int32 st0, st1, stval;

 if (strlen(s) != 3) return(FALSE);
 if (strcmp(s, "HiZ") == 0) return(ST_HIZ);
 switch (s[2]) {
  case '0': stval = 0; break;
  case '1': stval = 1; break;
  /* notice z can only be HiZ */
  case 'x': case 'X': stval = 3; break;
  case 'H': stval = -2; break;
  case 'L': stval = -3; break;
  default: return(-1);
 }
 if (isdigit(s[0]))
  {
   if (!isdigit(s[1])) return(-1);
   st0 = s[0] - '0';
   st1 = s[1] - '1';
   /* cannot have 07<x,z,0,1> or any numeric 0 */ 
   if (st0 < 1 || st0 > 7 || st1 < 1 || st1 > 7) return(-1); 
   /* <0,0>=? is error hiZ required for <0,0>=z */
   if (st0 == 0 && st1 == 0) return(-1);
   /* L or H requires and value cannot be digit z */
   if (stval <= -2) return(-1);
   stval |= ((st0 << 5) | (st1 << 2));
   return(stval);
  }
 /* must match strength name including case */
 switch (s[0]) {
  case 'S':
   if (s[1] == 'u') st0 = st1 = 7;  
   else if (s[1] == 't') st0 = st1 = 6;
   else if (s[1] == 'm') st0 = st1 = 1;
   else return(-1);
   break;
  case 'P': if (s[1] != 'u') return(-1); st0 = st1 = 5; break;
  case 'L': if (s[1] != 'a') return(-1); st0 = st1 = 4; break;
  case 'W': if (s[1] != 'e') return(-1); st0 = st1 = 3; break;
  case 'M': if (s[1] != 'e') return(-1); st0 = st1 = 2; break;
  default: return(-1);
 }
 /* handle H */
 if (stval == -2)
  {
   /* 000sss02 */
   stval = (st1 << 2) | 2; 
   return(stval);
  }
 /* handle L */
 if (stval == -3)
  {
   /* sss00002 */
   stval = (st0 << 5) | 2; 
   return(stval);
  }
 /* handle normal value */
 stval |= ((st0 << 5) | (st1 << 2));
 return(stval);
}

/*
 * cancel all events starting at passed to end 
 *
 * for change to inertial - free all but last and return last (latest)
 * this list for the one given parameter must be ordered by time
 * caller must set previous next field to nil or nil out list
 */
static void cancel_dputp_toend(struct tfarg_t *tfap, struct dltevlst_t *frdlp)
{
 int32 lhslen;
 struct dltevlst_t *dlp;
 struct tev_t *tevp;
 byte *sbp;
 struct tedputp_t *tedp;
 struct expr_t *xp;
 struct dltevlst_t *last_dlp;

 for (last_dlp = NULL, dlp = frdlp; dlp != NULL; dlp = dlp->terp)  
  {
   tevp = dlp->tevp; 
   /* DBG remove -- */
   if (tevp->enterptr != __process_putpdel_ev) __misc_terr(__FILE__, __LINE__);
   /* --- */
   tedp = tevp->tu.tedputp;
   tevp->enterptr = __process_cancel_ev_enterp;
   xp = tfap->arg.axp;
   lhslen = xp->szu.xclen;
   /* free the value */
   if (xp->x_stren)
    { sbp = (byte *) tedp->tedwp; __my_free(sbp, lhslen); }
   else __my_free(tedp->tedwp, 2*wlen_(lhslen)*WRDBYTES);

   /* free tedputp by linking on free list */
   tedp->tedtfrp =  (struct tfrec_t *) __tedpfreelst;
   __tedpfreelst = tedp;
   last_dlp = dlp;
  }
 /* finally link all of tevlst onto free list */
 /* SJM 08/02/01 - add if to keep lint happy */
 if (last_dlp != NULL) last_dlp->terp = __dltevfreelst; 
 __dltevfreelst = frdlp;
}

/*
 * splice out and return last tev list element
 * only called if at least one two
 */
extern struct dltevlst_t *__spliceout_last(struct dltevlst_t *dlp)
{
 for (; dlp->terp != NULL; dlp = dlp->terp) ;
 /* know dlp has one before */ 
 dlp->telp->terp = NULL; 
 return(dlp);
}

/*
 * find last doubly linked te list element before new time
 *
 * know at least one scheduled or routine not called
 * if multiple as same time, return last of same time
 * if all at current time returns last of current time 
 * if ntim after all, returns last
 * if ntim before all, returns nil
 *
 * needed for modified transport where keep earlier (remove all after)
 * new event is after all same time
 *
 * notice modified transport keeps all of same time and put new on end
 */
extern struct dltevlst_t *__find_last_bdltevp(struct dltevlst_t *dlp,
 word64 ntim)
{
 struct dltevlst_t *last_dlp;

 for (last_dlp = NULL; dlp != NULL; dlp = dlp->terp)
  {
   if (ntim < dlp->tevp->etime) return(dlp->telp);
   last_dlp = dlp;
  }
 return(last_dlp);
}

/*
 * schedule set but use long time and other pli task
 */
extern int32 tf_istrlongdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, int32 lowdelay, int32 highdelay, int32 delaytype, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_strlongdelputp(nparam, bitlength, format_char, value_p, lowdelay,
  highdelay, delaytype);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * schedule set but use long time 
 */
extern int32 tf_strlongdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, int32 lowdelay, int32 highdelay, int32 delaytype)
{
 int32 rv;
 word64 t1, ticks;
 struct mod_t *cur_mdp;

 /* scale from module delay to ticks */
 /* SJM 02/03/00 - cast of negative (>2**31) sign extends need word32 1st */
 t1 = ((word64) ((word32) lowdelay)) | (((word64) ((word32) highdelay)) << 32);
 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) cnv_num64to_ticks_(ticks, t1, cur_mdp);
 else ticks = t1;

 rv = delayed_str_putp(nparam, bitlength, format_char, value_p,
  ticks, delaytype);
 return(rv);
}

/*
 * schedule set but use real time and other pli task
 */
extern int32 tf_istrrealdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, double realdelay, int32 delaytype, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_strrealdelputp(nparam, bitlength, format_char, value_p, realdelay,
  delaytype);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * schedule set but use real time 
 */
extern int32 tf_strrealdelputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, double realdelay, int32 delaytype)
{
 int32 rv;
 word64 t1, ticks;
 struct mod_t *cur_mdp;

 /* convert real to time */
 if (!__real_to_v64tim(&t1, realdelay)) return(TF_NULLPARAM); 

 /* then scale real from module time to ticks if needed */
 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) cnv_num64to_ticks_(ticks, t1, cur_mdp);
 else ticks = t1;

 /* here returns 1 for good and 0 if error */
 rv = delayed_str_putp(nparam, bitlength, format_char, value_p,
  ticks, delaytype);
 return(rv);
}

/*
 * added routine that uses real 0 delay (i.e. immediate store)
 * in delay forms delay 0 is #0
 * this does not use any delay and is independent of strdelputp
 * so if pending delay delays will happen as if only option is
 * pure transport that never cancels a delay
 */
extern int32 tf_istrputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_strputp(nparam, bitlength, format_char, value_p);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_strputp(int32 nparam, int32 bitlength, int32 format_char,
 char *value_p)
{
 struct tfarg_t *tfap;
 int32 lhslen;
 struct expr_t *lhsxp;
 struct xstk_t *xsp;

 if (__run_state != SS_SIM) return(bad_nosimtf_err("tf_strputp"));
 if (__rosync_slot) return(bad_rosync_err("tf_strputp"));
 if (__tfrec == NULL) return(bad_notfcontext_err("tf_strputp"));

 /* cannot used schedule delayed putp to assign to return value */
 if (nparam < 1 || nparam >= __tfrec->tfanump1) return(TF_NULLPARAM);
 tfap = &(__tfrec->tfargs[nparam]);
 lhsxp = tfap->arg.axp;
 if (!lhsxp->tf_isrw) return(TF_NULLPARAM);

 lhslen = lhsxp->szu.xclen;
 /* push value on to stack - width is lhs needed (maybe converted) */
 xsp = __putdstr_to_val(value_p, bitlength, lhslen, format_char);
 if (xsp == NULL) return(TF_NULLPARAM);

 if (__ev_tracing)
  {
   char s1[RECLEN], s2[RECLEN];

   if (tfap->anp->ntyp >= NONWIRE_ST) strcpy(s1, "procedural");
   else if (lhsxp->x_multfi) strcpy(s1, "continuous fi>1");
   else strcpy(s1, "continuous fi=1");
   if (lhsxp->x_stren)
    __st_regab_tostr(s2, (byte *) xsp->ap, lhsxp->szu.xclen);
   else __regab_tostr(s2, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE);
   __evtr_resume_msg();
   __tr_msg(
    "tf_ arg %d at %s in %s tf_strputp %s assign value %s\n",
    nparam, __bld_lineloc(__wrks1, __tfrec->tffnam_ind, __tfrec->tflin_cnt),
    __msg2_cur_blditree(__wrks2), s1, s2);
  }
 exec_tfarg_assign(tfap, lhsxp, xsp->ap, xsp->bp);
 __pop_xstk();
 return(1);
}

/*
 * SYNCHRONIZE (MISCTF) CONTROL AND DELAY (NOT VALUE) ROUTINES
 */

/*
 * schedule a delay at delay + __simtime
 * calls misctf with reason_reactivate when event happens
 * must be >= 0, 0 is #0 form
 * must scale for time scale
 * returns 0 on error else non 0
 */
extern int32 tf_isetdelay(int32 delay, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_setdelay(delay);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * set delay for other pli task
 * SJM 12/17/02 - notice this returns 0 on error unlike most others 
 */
extern int32 tf_setdelay(int32 delay)
{
 int32 rv;
 word64 ticks, t1;
 struct mod_t *cur_mdp;

 /* scale from module delay to ticks */
 /* SJM 02/03/00 - cast of negative (>2**31) sign extends need word32 1st */
 t1 = (word64) ((word32) delay);
 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) cnv_num64to_ticks_(ticks, t1, cur_mdp);
 else ticks = t1;

 rv = delayed_misctf_schd(ticks);
 return(rv);
}

/*
 * routine that schedules call to misctf routine 
 * by here delay converted to internal ticks (scaling done)
 *
 * SJM 12/17/02 - notice this returns 0 on error unlike most others 
 */
static int32 delayed_misctf_schd(word64 ticksdel)
{
 struct tev_t *tevp;
 struct tevlst_t *telp;
 word64 schtim;
 int32 inum;

 if (__run_state != SS_SIM) return(bad_nosimtf_err("setdelay type"));
 if (__rosync_slot) return(bad_rosync_err("setdelay type"));
 if (__tfrec == NULL) return(bad_notfcontext_err("setdelay type"));

 schtim = __simtime + ticksdel;
 alloc_cur_tev_(tevp, __setdel_call_misctf_enterp, schtim);
 tevp->tu.tetfrec = __tfrec;

 /* put event on front of tev pendng list for instance */
 if (__ltevfreelst != NULL)
  { telp = __ltevfreelst; __ltevfreelst = __ltevfreelst->telnxt; }
 else telp = (struct tevlst_t *) __my_malloc(sizeof(struct tevlst_t)); 
 inum = get_inum_();
 telp->telnxt = __tfrec->setd_telst[inum];
 __tfrec->setd_telst[inum] = telp;
 telp->tevp = tevp;
 
 /* add to event queue */
 if (ticksdel == 0ULL)
  {
   if (__p0_te_hdrp == NULL) __p0_te_hdrp = __p0_te_endp = tevp;
   else 
    { 
     __p0_te_endp->tenxtp = tevp; __p0_te_endp = tevp; 
     /* AIV 08/23/10 - if compiled need to set end of time event handler */
     if (__compiled_sim) tevp->tenxtp = __free_event_pnd0_tevp;
    }
  }
 else __insert_event(tevp);
 return(1);
}

/*
 * schedule long form (for now just ignore high long)
 * SJM 12/17/02 - notice this returns 0 on error unlike most others 
 */
extern int32 tf_isetlongdelay(int32 lowdelay, int32 highdelay, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_setlongdelay(lowdelay, highdelay);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * other pli task form of schedule long delay
 */
extern int32 tf_setlongdelay(int32 lowdelay, int32 highdelay)
{
 int32 rv;
 word64 t1, ticks;
 struct mod_t *cur_mdp;

 /* scale from module delay to ticks */
 /* SJM 02/03/00 - cast of negative (>2**31) sign extends need word32 1st */
 t1 = ((word64) ((word32) lowdelay))
  | (((word64) ((word32) highdelay)) << 32);
 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) cnv_num64to_ticks_(ticks, t1, cur_mdp);
 else ticks = t1;

 rv = delayed_misctf_schd(ticks);
 return(rv);
}

/*
 * set delay passed as real (double)
 */
extern int32 tf_isetrealdelay(double realdelay, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_setrealdelay(realdelay);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * set delay passed as real (double)
 * SJM 12/17/02 - notice this returns 0 on error unlike most others 
 */
extern int32 tf_setrealdelay(double realdelay)
{
 int32 rv;
 word64 t1, ticks;
 struct mod_t *cur_mdp;

 /* convert real to time */
 if (!__real_to_v64tim(&t1, realdelay)) return(TF_NULLPARAM); 

 /* then scale real from module time to ticks if needed */
 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) cnv_num64to_ticks_(ticks, t1, cur_mdp);
 else ticks = t1;
 rv = delayed_misctf_schd(ticks);
 return(rv);
}

/*
 * get next time at which a simulation event is scheduled 
 * can just scan through required list of scheduled events for this
 * task call and find first - assume slow
 *
 * this is slow if many scheduled events
 * set time and return 0 if ok, 1 no events, 2 not in ro synchronize mode
 * 
 * WRITEME
 */
extern int32 tf_getnextlongtime(int32 *aof_lowtime, int32 *aof_hightime)
{
 if (__run_state != SS_SIM) return(bad_nosimtf_err("tf_getnextlongtime"));
 /* MYABE WRITEME */
 __sgferr(1301,
  "tf_getnexlongtime not implemented - use PLI 2.0 cbNextSimTime callback");
 return(TF_NULLPARAM);
}

/*
 * clear (unschedule) delays
 * mark every event as cancelled and frees tev list
 * must cancel and free for all arguments
 */
extern int32 tf_iclearalldelays(char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_clearalldelays();
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_clearalldelays(void)
{
 struct tevlst_t *telp, *last_telp;
 int32 inum;

 if (__run_state != SS_SIM) return(bad_nosimtf_err("tf_(i)clearalldelays"));
 if (__rosync_slot) return(bad_rosync_err("tf_(i)clearalldelays"));
 if (__tfrec == NULL) return(bad_notfcontext_err("tf_clearalldelays"));

 inum = get_inum_();
 if ((telp = __tfrec->setd_telst[inum]) == NULL) return(1);
 /* notice these do not have any internal that needs to be freed */ 
 for (last_telp = NULL; telp != NULL; telp = telp->telnxt) 
  { 
   telp->tevp->enterptr = __process_cancel_ev_enterp;
   last_telp = telp; 
  }
 last_telp->telnxt = __ltevfreelst; 
 __ltevfreelst = __tfrec->setd_telst[inum];
 __tfrec->setd_telst[inum] = NULL;
 return(1);
}

/*
 * other pli form for synchronize call 
 */
extern int32 tf_isynchronize(char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_synchronize();
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * cause call of misctf user routine with reason_sync at end of called time
 * this schedules routine at end of pound0 list when called
 * set flag that causes calling of misctf at end of time slot (very end?)
 */
extern int32 tf_synchronize(void)
{
 struct tev_t *tevp;
 int32 inum;

 if (__run_state != SS_SIM)
  {
   return(bad_nosimtf_err("tf_synchronize"));
  }
 if (__rosync_slot)
  {
   return(bad_rosync_err("tf_sychronize"));
  }
 if (__tfrec == NULL)
  {
   return(bad_notfcontext_err("tf_synchronize"));
  }

 /* if already called nothing to do */
 inum = get_inum_();
 if (__tfrec->sync_tevp[inum] != NULL) return(1);

 alloc_cur_tev_(tevp, __sync_call_misctf_enterp, __simtime);
 tevp->tu.tetfrec = __tfrec;
 __tfrec->sync_tevp[inum] = tevp;
 /* schedule event at end of #0 queue - just need to lin on */
 if (__p0_te_hdrp == NULL) __p0_te_hdrp = __p0_te_endp = tevp;
 else 
  { 
   __p0_te_endp->tenxtp = tevp; __p0_te_endp = tevp; 
   /* AIV 08/23/10 - if compiled need to set end of time event handler */
   if (__compiled_sim) tevp->tenxtp = __free_event_pnd0_tevp;
  }
 return(1);
}

/*
 * cause call of misctf user routine with reason_sync at end of called time
 * misctf called with reason_rosync
 * this schedules routine as very last thing (before monitor/strobe)
 * user must not call any routine that schedules events (not checked)
 *
 * set flag that causes calling of misctf at end of time slot (very end?)
 */
extern int32 tf_irosynchronize(char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_rosynchronize();
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_rosynchronize(void)
{
 int32 rv, inum;
 struct tev_t *tevp;

 if (__run_state != SS_SIM)
  {
   rv = bad_nosimtf_err("tf_rosynchronize");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 /* can not call reason ro sync from within rosync routine */
 if (__rosync_slot)
  {
   rv = bad_rosync_err("tf_rosychronize");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err ("tf_rosynchronize");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }

 /* if already called nothing to do */
 inum = get_inum_();
 if (__tfrec->rosync_tevp[inum] != NULL) return(1);

 /* this is separate list that determines type, type never seen */
 alloc_cur_tev_(tevp, NULL, __simtime);
 tevp->tu.tetfrec = __tfrec;
 /* link on front of rosync list */
 if (__tehdr_rosyncp == NULL) __tehdr_rosyncp = __teend_rosyncp = tevp;
 else { __teend_rosyncp->tenxtp = tevp; __teend_rosyncp = tevp; }
 __tfrec->rosync_tevp[inum] = tevp;
 __slotend_action |= SE_TFROSYNC;
 return(0);
}

/*
 * turn off parameter change misctf calling
 */ 
extern int32 tf_iasynchoff(char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_asynchoff();
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_asynchoff(void)
{
 int32 rv, inum;

 if (__run_state != SS_SIM)
  {
   rv = bad_nosimtf_err("tf_(i)asynchoff");
   /* SJM 12/17/02 - error for asynch on/off is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_asynchoff");
   /* SJM 12/17/02 - error for asynch on/off is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }

 /* if already off nothing to do */
 /* SJM 12/17/02 LOOKATME ??? - assuming nothing to do is success */
 inum = get_inum_();
 if (__tfrec->asynchon[inum]) return(0);

 /* free dces and regen iops if needed for every param to turn off */
 /* may not be any dce's, but that still works */

 /* SJM 02/08/03 - can never free dces if -O used */
 /* for interpreter free dces, prev val num insts always 1, know peri */
 if (__compiled_sim) __dcelst_off(__tfrec->pvcdcep[inum]);
 else __free_dceauxlst(__tfrec->pvcdcep[inum], 1);

 __tfrec->pvcdcep[inum] = NULL;
 __tfrec->asynchon[inum] = 0;

 return(0);
}

/*
 * turn on calling of misctf routines on parameter change
 */ 
extern int32 tf_iasynchon(char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_asynchon();
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_asynchon(void)
{
 int32 i;
 int32 rv, inum;

 if (__run_state != SS_SIM)
  {
   rv = bad_nosimtf_err("tf_(i)asynchon");
   /* SJM 12/17/02 - error for asynch on/off is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_asynchon");
   /* SJM 12/17/02 - error for asynch on/off is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }

 /* if already on nothing to do */ 
 /* SJM 12/17/02 LOOKATME ??? - assuming nothing to do is success */
 inum = get_inum_();
 if (__tfrec->asynchon[inum]) return(0);
 /* build dces for every param and turn on */
 
 __pvc_dcehdr = NULL;
 for (i = 1; i < __tfrec->tfanump1; i++)
  bld_pvc_dces(__tfrec->tfargs[i].arg.axp, i);
 __tfrec->pvcdcep[inum] = __pvc_dcehdr; 
 __tfrec->asynchon[inum] = 1;

 return(0);
}

/*
 * PVC FLAG ROUTINES
 */

/*
 * move for different inst. and location pli task
 * move old pvc to saved flag and clears old flag and return moved
 * -1 is all and return ored change value 
 */
extern int32 tf_imovepvc_flag(int32 nparam, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_movepvc_flag(nparam);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_movepvc_flag(int32 nparam)
{
 int32 i, ii;
 byte oldpvc;
 int32 rv;
 struct tfarg_t *tfap;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_movepvc_flag"));
 ii = get_inum_();
 rv = 0;
 if (nparam == -1)
  {
   /* move old to saved pvc flags and reset old */
   for (i = 1; i < __tfrec->tfanump1; i++)
    {
     tfap = &(__tfrec->tfargs[i]);
     if ((oldpvc = tfap->old_pvc_flgs[ii]) != 0) rv = 1; 
     tfap->old_pvc_flgs[ii] = 0;
     tfap->sav_pvc_flgs[ii] = oldpvc;
    }
   return(rv);
  }
 tfap = &(__tfrec->tfargs[nparam]);
 if ((oldpvc = tfap->old_pvc_flgs[ii]) != 0) rv = 1; 
 tfap->old_pvc_flgs[ii] = 0;
 tfap->sav_pvc_flgs[ii] = oldpvc;
 return(rv);
}

/*
 * copy pvc flag to saved flag
 * returns flag that was copied
 * flags are internal to pli tasks per parameter
 * if nparams == -1 copy all and return logic or of all
 * notice copy does not result oldpvc that is set by verilog dctrls
 */
extern int32 tf_icopypvc_flag(int32 nparam, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_copypvc_flag(nparam);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_copypvc_flag(int32 nparam)
{
 int32 i, ii, rv;
 byte oldpvc;
 struct tfarg_t *tfap;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_copypvc_flag"));
 ii = get_inum_();
 rv = 0;
 if (nparam == -1)
  {
   /* move old to saved pvc flags and reset old */
   for (i = 1; i < __tfrec->tfanump1; i++)
    {
     tfap = &(__tfrec->tfargs[i]);
     if ((oldpvc = tfap->old_pvc_flgs[ii]) != 0) rv = 1; 
     tfap->sav_pvc_flgs[ii] = oldpvc;
    }
   return(rv);
  }
 tfap = &(__tfrec->tfargs[nparam]);
 if ((oldpvc = tfap->old_pvc_flgs[ii]) != 0) rv = 1; 
 tfap->sav_pvc_flgs[ii] = oldpvc;
 return(rv);
}

/*
 * returns saved flag, -1 means or of all 
 */
extern int32 tf_itestpvc_flag(int32 nparam, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_testpvc_flag(nparam);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_testpvc_flag(int32 nparam)
{
 int32 i, ii, rv;
 struct tfarg_t *tfap;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_testpvc_flag"));
 rv = 0;
 ii = get_inum_();
 if (nparam == -1)
  {
   /* move old to saved pvc flags and reset old */
   for (i = 1; i < __tfrec->tfanump1; i++)
    {
     tfap = &(__tfrec->tfargs[i]);
     if (tfap->old_pvc_flgs[ii] != 0) rv = 1; 
    }
   return(rv);
  }
 tfap = &(__tfrec->tfargs[nparam]);
 if (tfap->old_pvc_flgs[ii] != 0) rv = 1; 
 return(rv);
}

/*
 * get number of parameter that is > nparam
 * nparam must be 0 for 1st time called within a given user routine
 * invocation
 * returns 0 if no change > nparam or error
 * must execute tf_movepfv_flag before using routine
 * DOCUMENTME - for Cver does not need to be called with 0 first time
 */
extern int32 tf_igetpchange(int32 nparam, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_getpchange(nparam);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

extern int32 tf_getpchange(int32 nparam)
{
 int32 i, ii;
 struct tfarg_t *tfap;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_getpchange"));
 ii = get_inum_();
 if (nparam == 0) i = 1; else i = nparam + 1;
 for (; i < __tfrec->tfanump1; i++)
  {
   tfap = &(__tfrec->tfargs[i]);
   if (tfap->sav_pvc_flgs[ii] != 0) return(i);
  }
 return(TF_NULLPARAM);
}

/*
 * VERILOG SERVICES ROUTINES - MOSTLY TIME AND DELAY SCALING
 */

/*
 * get current sim time but scaled to timescale of inst.
 * scaled from 
 */
extern int32 tf_igettime(char *inst)
{
 word64 timval;
 struct tfinst_t *tfi;
 struct mod_t *mdp;

 tfi = (struct tfinst_t *) inst;
 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];
 if (!mdp->mno_unitcnv)
  {
   __cnv_ticks_tonum64(&timval, __simtime, mdp);
   return((int32) (timval & WORDMASK_ULL));
  }
 return((int32) (__simtime & WORDMASK_ULL));
}

/*
 * return current time as int32 (low 32 bits)  
 * user must cast to word32 or will lose high bit
 */
extern int32 tf_gettime(void)
{
 word64 timval;
 struct mod_t *cur_mdp;

 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) __cnv_ticks_tonum64(&timval, __simtime, cur_mdp);
 else timval = __simtime;
 return((int32) (timval & WORDMASK_ULL));
}

/*
 * return current time as int32 (low 32 bits) in ticks not scaled  
 * user must cast to word32 or will lose high bit
 */
extern int32 tf_getsimtime(void)
{
 return((int32) (__simtime & WORDMASK_ULL));
}

/* 
 * get a long time using other instance for from ticks scaling
 * caller must cast to word32 or will lose high bits
 */
extern int32 tf_igetlongtime(int32 *aof_hightime, char *inst)
{
 word64 timval;
 struct tfinst_t *tfi;
 struct mod_t *mdp;

 tfi = (struct tfinst_t *) inst;
 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];
 if (!mdp->mno_unitcnv)
  {
   __cnv_ticks_tonum64(&timval, __simtime, mdp);
   *aof_hightime = (int32) ((timval >> 32) & WORDMASK_ULL);
   return((int32) (timval & WORDMASK_ULL));
  }
 *aof_hightime = (int32) ((__simtime >> 32) & WORDMASK_ULL);
 return((int32) (__simtime & WORDMASK_ULL));
}

/* 
 * get a long time in ticks - lowest time precision in design
 * caller must cast to word32 or will lose high bit
 *
 * routine added because present in XL - no inst form 
 */
extern int32 tf_getlongsimtime(int32 *aof_hightime)
{
 *aof_hightime = (int32) ((__simtime >> 32) & WORDMASK_ULL);
 return((int32) (__simtime & WORDMASK_ULL));
}

/* 
 * get a long time using other instance for from ticks scaling
 * caller must cast to word32 or will lose high bit
 */
extern int32 tf_getlongtime(int32 *aof_hightime)
{
 word64 timval;
 struct mod_t *cur_mdp;

 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv)
  {
   __cnv_ticks_tonum64(&timval, __simtime, cur_mdp);
   *aof_hightime = (int32) ((timval >> 32) & WORDMASK_ULL);
   return((int32) (timval & WORDMASK_ULL));
  }
 *aof_hightime = (int32) ((__simtime >> 32) & WORDMASK_ULL);
 return((int32) (__simtime & WORDMASK_ULL));
}

/*
 * convert long time to string - does not scale caller must pass scaled
 * also no time unit suffix
 */
extern char *tf_longtime_tostr(int32 lowtime, int32 hightime)
{
 int32 save_nd_tsuf, slen;
 word64 t1;
 char *chp, s1[RECLEN];
 
 save_nd_tsuf = __nd_timstr_suf;
 __nd_timstr_suf = FALSE;
 
 t1 = ((word64) ((word32) lowtime)) | (((word64) ((word32) hightime)) << 32);
 __to_timstr(s1, &t1);
 __nd_timstr_suf = save_nd_tsuf;
 slen = strlen(s1);
 chp = __mytf_malloc(slen + 1);
 strcpy(chp, s1);
 return(chp);
}

/*
 * get scaled time as real 
 * i.e. get time then convert from ticks to real
 */
extern double tf_igetrealtime(char *inst)
{
 double d1;
 word64 timval;
 struct tfinst_t *tfi;
 struct mod_t *mdp;

 tfi = (struct tfinst_t *) inst;
 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];
 if (!mdp->mno_unitcnv) __cnv_ticks_tonum64(&timval, __simtime, mdp);
 else timval = __simtime;
 if (!__v64_to_real(&d1, &timval)) return((double) 0.0);
 return(d1); 
}

extern double tf_getrealtime(void)
{
 double d1;
 word64 timval;
 struct mod_t *cur_mdp;

 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) __cnv_ticks_tonum64(&timval, __simtime, cur_mdp);
 else timval = __simtime;
 if (!__v64_to_real(&d1, &timval)) return((double) 0.0);
 return(d1); 
}

/*
 * return pointer that is string of current time
 * LOOKATME - not listed as scaled in list but assuming it is for now
 */
extern char *tf_strgettime(void)
{
 int32 save_nd_tsuf, slen;
 word64 timval;
 char *chp, s1[RECLEN];
 struct mod_t *cur_mdp;

 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) __cnv_ticks_tonum64(&timval, __simtime, cur_mdp);
 else timval = __simtime;

 save_nd_tsuf = __nd_timstr_suf;
 __nd_timstr_suf = FALSE;
 __to_timstr(s1, &timval);
 __nd_timstr_suf = save_nd_tsuf;
 slen = strlen(s1);
 chp = __mytf_malloc(slen + 1);
 strcpy(chp, s1);
 return(chp);
}

/*
 * convert delay into internal simulation time units
 * use the inst to find module that has delay
 */
extern void tf_scale_longdelay(char *cell, int32 delay_lo, int32 delay_hi,
 int32 *aof_delay_lo, int32 *aof_delay_hi)
{
 word64 t1, t2;
 struct tfinst_t *tfi;
 struct mod_t *mdp;
 
 /* SJM 02/03/00 - cast of negative (>2**31) sign extends need word32 1st */
 t1 = ((word64) ((word32) delay_lo)) | (((word64) ((word32) delay_hi)) << 32);

 tfi = (struct tfinst_t *) cell;
 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];
 if (!mdp->mno_unitcnv) cnv_num64to_ticks_(t2, t1, mdp);
 else t2 = t1;
 *aof_delay_lo = (int32) (t2 & WORDMASK_ULL);
 *aof_delay_hi = (int32) ((t2 >> 32) & WORDMASK_ULL);
}

/*
 * convert delay as real into internal simulation time units
 *
 * passed delay which is in units of cell instance and convert to internal
 * ticks (i.e. lowest in design)
 * LOOKATME - for now rouding to ticks but maybe should use time format
 * values
 */
extern void tf_scale_realdelay(char *cell, double realdelay,
 double *aof_realdelay)
{
 int32 unit;
 struct tfinst_t *tfi;
 struct mod_t *mdp;

 tfi = (struct tfinst_t *) cell;
 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];
 if (!mdp->mno_unitcnv)
  {
   unit = __des_timeprec - mdp->mtime_units;
   *aof_realdelay = realdelay*__dbl_toticks_tab[unit];
  }
 /* just assign if no module time scale */
 else *aof_realdelay = realdelay;
}

/*
 * convert delay from internal simulation time units to delay of mod units
 * use the inst to find module that has delay
 */
extern void tf_unscale_longdelay(char *cell, int32 delay_lo, int32 delay_hi,
 int32 *aof_delay_lo, int32 *aof_delay_hi)
{
 word64 t1, t2;
 struct tfinst_t *tfi;
 struct mod_t *mdp;
 
 tfi = (struct tfinst_t *) cell;
 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];

 /* SJM 02/03/00 - cast of negative (>2**31) sign extends need word32 1st */
 t1 = ((word64) ((word32) delay_lo)) | (((word64) ((word32) delay_hi)) << 32);

 if (!mdp->mno_unitcnv) __cnv_ticks_tonum64(&t2, t1, mdp);
 else t2 = t1;
 *aof_delay_hi = (int32) ((t2 >> 32) & WORDMASK_ULL);
 *aof_delay_lo = (int32) (t2 & WORDMASK_ULL);
}

/*
 * convert delay from internal simulation time units to mod delay- real form
 */
extern void tf_unscale_realdelay(char *cell, double realdelay,
 double *aof_realdelay)
{
 int32 unit;
 struct tfinst_t *tfi;
 struct mod_t *mdp;
 
 tfi = (struct tfinst_t *) cell;
 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];
 if (!mdp->mno_unitcnv)
  {
   unit = __des_timeprec - mdp->mtime_units;
   *aof_realdelay = realdelay /__dbl_toticks_tab[unit];
  }
 else *aof_realdelay = realdelay;
}

/*
 * convert signed long to real
 * this is unusual in because converts 64 bit signed value
 * preserving sign to real
 * for most routines conversion is from int32 or word32 (32 bits) to real
 */
extern void tf_long_to_real(int32 int_lo, int32 int_hi, double *aof_real)
{
 long long iv1;

 /* SJM 11/29/99 - now know long long always supported so use it */
 /* also some problems with sign handling */
 iv1 = (((long long) int_hi) << 32) + ((long long) int_lo);
 *aof_real = (double) iv1;
}

/*
 * normal real to as much of 64bit as possible conversion
 */
extern void tf_real_to_long(double real, int32 *aof_int_lo, int32 *aof_int_hi)
{
 long long iv1;

 /* SJM 11/29/99 - must use long long arithmetic old routine wrong low 1 */
 /* in high word32 and 0 in low word32 (from double) */
 iv1 = (long long) real + 0.50000; 
 *aof_int_hi = (int32) (iv1 >> 32);  
 *aof_int_lo = (int32) (iv1 & 0xffffffff); 
}

/*
 * get time unit as scaled exponent 1 sec is 0 of time unit of cur module
 * get from other instance module
 * if null, return design wide time unit (smallest) 
 */
extern int32 tf_igettimeunit(char *inst)
{
 int32 i;
 struct tfinst_t *tfi;
 struct mod_t *mdp;
 
 tfi = (struct tfinst_t *) inst;
 /* special case return smallest time precision (not units) in design */
 if (tfi == NULL) { i = -((int32) __des_timeprec); return(i); } 

 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];
 /* this works because no unit conversion means design time prec (min. */
 /* but stored as positive inverse of neg. exponent) is same as unit */
 if (!mdp->mno_unitcnv) i = -((int32) mdp->mtime_units);
 else i = -((int32) __des_timeprec);
 return(i);
}

extern int32 tf_gettimeunit(void)
{
 int32 i;
 struct mod_t *cur_mdp;

 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv) 
   i = -((int32) (cur_mdp->mtime_units + cur_mdp->mtime_prec));
 /* if no time scale both precision and units the same */
 else i = -((int32) __des_timeprec);
 return(i);
}

/*
 * get the time precision for a module
 */
extern int32 tf_igettimeprecision(char *inst)
{
 int32 i;
 struct tfinst_t *tfi;
 struct mod_t *mdp;
 
 tfi = (struct tfinst_t *) inst;
 /* special case return design precison (sim. tick) value */
 /* design time units is minimum of all units in design */
 if (tfi == NULL) { i = -((int32) __des_timeprec); return(i); } 

 mdp = (struct mod_t *) tfi->tfidp[MD_MDP];
 if (!mdp->mno_unitcnv) i = -((int32) (mdp->mtime_units + mdp->mtime_prec));
 else i = -((int32) __des_timeprec);
 return(i);
}

/*
 * get the time precision for a module
 */
extern int32 tf_gettimeprecision(void)
{
 int32 i;
 struct mod_t *cur_mdp;
 
 cur_mdp = get_inst_mod_();
 if (!cur_mdp->mno_unitcnv)
  i = -((int32) (cur_mdp->mtime_units + cur_mdp->mtime_prec));
 else i = -((int32) __des_timeprec);
 return(i);
}

/*
 * return a string giving module name for task call from other inst/place
 */
extern char *tf_imipname(char *inst)
{
 char *chp;
 struct tfinst_t *sav_tfip;
 decl_idp_locals_;

 sav_tfip = __tfinst;
 __tfinst = (struct tfinst_t *) inst;
 set_save_idp_(__tfinst->tfidp);
 chp = tf_mipname(); 
 restore_idp_();
 __tfinst = sav_tfip;
 return(chp);
}

/*
 * return a string (. separated) that is the path to the call to a user
 * task or function
 *
 * just gets this out of cur_itp - when return if schedule has itp
 */
extern char *tf_mipname(void)
{
 char *chp;
 int32 slen;
 int32 sav_sofs = __cur_sofs;

 __disp_itree_idp_path(__idp, (struct task_t *) NULL);
 slen = __cur_sofs - sav_sofs;
 chp = __mytf_malloc(slen + 1);
 strcpy(chp, &(__exprline[sav_sofs]));
 __cur_sofs = sav_sofs;
 __exprline[__cur_sofs] = '\0'; 
 return(chp);
}

extern char *tf_ispname(char *cell)
{
 char *chp;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(cell, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 chp = tf_spname();
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(chp);
}

/*
 * return a string (. separated) that is the scope to the call to a user
 * task or function - will contain possible named block or task called from
 * plus module name prefix
 * for nested blocks can have multiple components
 */
extern char *tf_spname(void)
{
 int32 slen;
 int32 sav_sofs = __cur_sofs;
 char *chp;

 if (__tfrec == NULL)
  {
   bad_notfcontext_err("tf_spname");
   return(NULL);
  }
 __disp_itree_idp_path(__idp, __tfrec->tf_intskp);
 slen = __cur_sofs - sav_sofs;
 chp = __mytf_malloc(slen + 1);
 strcpy(chp, &(__exprline[sav_sofs]));
 __cur_sofs = sav_sofs;
 __exprline[__cur_sofs] = '\0'; 
 return(chp);
}

/*
 * cause $finish simulation termination (any clean up needed)
 *
 * normal convention to check verbose mode but no argument for messages
 */
extern int32 tf_dofinish(void)
{
 __pli_dofinish(0, "tf_dofinish");
 return(TF_NULLPARAM);
}

/*
 * PLI either tf_ or vpi_ routine to stop simulation ($finish)
 */
extern void __pli_dofinish(int32 diag_level, char *caller)
{
 int32 rv; 

 /* need to call PLI end of sim routines before finishing */
 if (__tfrec_hdr != NULL) __call_misctfs_finish();
 if (__have_vpi_actions) __vpi_endsim_trycall();

 /* if not simulating just exit */
 if (__run_state != SS_SIM)
  {
   __cv_msg(
    "Halted from call to PLI %s before simulation has begun.\n", caller);   
   goto endit;
  }

 if (__verbose)
  {
   __cv_msg(
    "Halted at location %s time %s from call to PLI %s.\n",   
    __bld_lineloc(__wrks2, (word32) __sfnam_ind, __slin_cnt),
    __to_timstr(__wrks1, &__simtime), caller);
   __emit_stsk_endmsg();
  }
 /* notice must always print error counts if any */
endit:
 if (__pv_err_cnt != 0 || __pv_warn_cnt != 0 || __inform_cnt != 0)
  __cv_msg("  There were %d error(s), %d warning(s), and %d inform(s).\n",
   __pv_err_cnt, __pv_warn_cnt, __inform_cnt);
 /* SJM 04/26/04 - needs to exit with non zero if any errors occurred */
 if (__pv_err_cnt != 0) rv = 1; else rv = 0;
 __my_exit(rv, TRUE);
}

/*
 * cause $stop return to interactive mode
 * this is tricky since must run interactive environment under here
 */
extern int32 tf_dostop(void)
{
 if (__run_state != SS_SIM) return(bad_nosimtf_err("tf_dostop"));
 if (__no_iact)
  {
   __sgfwarn(560,
    "Call to PLI tf_dostop no effect - interactive environment disabled");
   return(TF_NULLPARAM);
  }
 __pending_enter_iact = TRUE;
 __iact_reason = IAER_STOP;
 /* must leave signal on - if ^c hit before stop, same effect */
 /* but entry reason different and lost */
 return(TF_NULLPARAM);
}

/*
 * INSTANCE AND LOCATION USER STORAGE ROUTINES
 */

/*
 * convert current inst - arg list and itree place to alloced rec.
 * allocates record that user can free with tf_freeinst - added
 */
extern char *tf_getinstance(void)
{
 struct tfinst_t *tfip;

 /* LOOKATME - this storage is not freeable (inherent memory leak?) */
 tfip = (struct tfinst_t *) malloc(sizeof(struct tfinst_t));
 *tfip = *__tfinst;
 return((char *) tfip);
}

/* 
 * get associated work area
 * since can just use malloc this is pointless (was for IBM 360 mvs?)
 */
extern char *tf_igetworkarea(char *inst)
{
 char *chp;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 chp = tf_getworkarea();
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(chp);
}

/* 
 * get associated work area
 */
extern char *tf_getworkarea(void)
{
 int32 inum;

 if (__tfrec == NULL)
  {
   bad_notfcontext_err("tf_getworkarea");
   return(NULL);
  }
 inum = get_inum_();
 return(__tfrec->savwrkarea[inum]);
}

/*
 * store work area for other inst/loc pli task
 */
extern int32 tf_isetworkarea(char *workarea, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_setworkarea(workarea);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * store (associate) routine with pli task
 * just a pointer assignment
 */
extern int32 tf_setworkarea(char *workarea)
{
 int32 inum;

 if (__tfrec == NULL) return(bad_notfcontext_err("tf_setworkarea"));
 inum = get_inum_();
 __tfrec->savwrkarea[inum] = workarea;
 return(1);
}

/*
 * 64 BIT ARITHMETIC ROUTINES
 */

/*
 * add long's which even though passed as int32 are really unsigned
 * LOOKATME - is this supposed to be long but signed add
 * if really word32 should change veriuser.h template 
 */
extern void tf_add_long(int32 *aof_lowtime1, int32 *aof_hightime1, int32 lowtime2,
 int32 hightime2)
{
 int32 lowsum;

 lowsum = *aof_lowtime1 + lowtime2;
 *aof_hightime1 = *aof_hightime1 + hightime2
  + ((word32) lowsum < (word32) *aof_lowtime1);
 *aof_lowtime1 = lowsum;
}

/*
 * 2's complement signed long subtract
 * built in 32 bit size for int32 and any borrow is lost
 * fails on machine that does not use 2's complement for signed ints
 * also assumes conversion from word32 to int32 can make a negative int
 * per normal c conventions
 */
extern void tf_subtract_long(int32 *aof_lowtime1, int32 *aof_hightime1,
 int32 lowtime2, int32 hightime2)
{
 int32 lowdif;

 lowdif = *aof_lowtime1 - lowtime2;
 /* tmp greater than subtracted from means wrap around and need borrow */
 /* word32 borrow test since need to include high bit */
 *aof_hightime1 = *aof_hightime1 - hightime2
  - (int32) (((word32) lowdif > (word32) *aof_lowtime1));
 *aof_lowtime1 = lowdif;
}

/*
 * compare 2 long ints passed in 4 halves
 * return -1 <, 0 =, +1 >
 * requires 2 complement representation according to normal c convention
 */
extern int tf_compare_long(unsigned int low1, unsigned int high1,
 unsigned int low2, unsigned int high2)
{
 if (high1 == high2) 
  {
   if (low1 == low2) return(0); 
   if (low1 > low2) return(1); 
   return(-1);
  }
 if (high1 < high2) return(-1);
 return(1);
}

/*
 * 2's complement long multiply of 2 64 bit values
 * this is built in 64 bits because int32 must be 32 bits for portability
 * this removes and puts back sign
 */
extern void tf_multiply_long(int32 *aof_low1, int32 *aof_high1, int32 low2,
 int32 high2)
{
 word32 r[2], u[2], v[2];
 int32 ir0, ir1;
 int32 minus;

 if (*aof_high1 < 0)
  {
   minus = TRUE;
   u[0] = (word32) -(*aof_low1);
   u[1] = (word32) (-(*aof_high1) - (u[0] != 0)); 
  }
 else
  {
   minus = FALSE;
   u[0] = (word32) *aof_low1;
   u[1] = (word32) *aof_high1;
  }
 if (high2 < 0)
  {
   minus = !minus;
   v[0] = (word32) -low2;
   v[1] = (word32) (-high2 - (v[0] != 0));
  }
 else { v[0] = (word32) low2; v[1] = (word32) high2; }

 __lmult((word32 *) r, (word32 *) u, (word32 *) v,  64);
 if (minus)
  {
   ir0 = (int32) r[0];
   ir1 = (int32) r[1];
   *aof_low1 = -ir0;
   *aof_high1 = -ir1 - (*aof_low1 != 0);
  }
 else { *aof_low1 = (int32) r[0]; *aof_high1 = (int32) r[1]; }
}

/*
 * long divide of word32 times - assuming word32 div not mod
 * LOOKATME - treating as word32 why are arguments ints? and no way to
 * indicate divide by 0
 */
extern void tf_divide_long(int32 *aof_low1, int32 *aof_high1, int32 low2,
 int32 high2)
{
 int32 ir0, ir1;
 int32 minus;
 word32 res[02], u[2], v[2], dum[2];

 /* divide by 0 must be 0 since no error mechanism */
 if (low2 == 0L && high2 == 0L) { *aof_low1 = *aof_high1 = 0L; return; } 

 if (*aof_high1 < 0)
  {
   minus = TRUE;
   u[0] = (word32) -(*aof_low1);
   u[1] = (word32) (-(*aof_high1) - (u[0] != 0)); 
  }
 else
  {
   minus = FALSE;
   u[0] = (word32) *aof_low1;
   u[1] = (word32) *aof_high1;
  }
 if (high2 < 0)
  {
   minus = !minus;
   v[0] = (word32) -low2;
   v[1] = (word32) (-high2 - (v[0] != 0));
  }
 else { v[0] = (word32) low2; v[1] = (word32) high2; }
 __ldivmod2(res, dum, u, v, 64);
 if (minus)
  {
   ir0 = (int32) res[0];
   ir1 = (int32) res[1];
   *aof_low1 = -ir0;
   *aof_high1 = -ir1 - (*aof_low1 != 0);
  }
 else { *aof_low1 = (int32) res[0]; *aof_high1 = (int32) res[1]; }
}

/*
 * I/O ROUTINES
 */

/*
 * emit error using cver mechanism
 */
extern int32 tf_error(char *fmt, ...)
{
 va_list va, va2;

 va_start(va, fmt);
 va_start(va2, fmt);
 vprt_tferr_msg(fmt, va, va2);
 va_end(va);
 va_end(va2);
 return(1);
}

/*
 * actually print an error message tf form - also used by tf message
 */
static void vprt_tferr_msg(char *fmt, va_list va, va_list va2)
{
 char s1[RECLEN], s2[RECLEN];

 __pv_err_cnt++;
 if (!__no_errs)
  {
   if (__run_state == SS_SIM)
    sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
   else strcpy(s1, "");

   __my_fprintf(stdout, "**%s(%d) USER PLI ERROR**%s [1290] ",
    __in_fils[__sfnam_ind], __slin_cnt, s1);
   __my_vfprintf(stdout, fmt, va, va2);
   my_putc_('\n', stdout);
  }
 /* no maximum error count for these */
}

extern int32 tf_warning(char *fmt, ...)
{
 va_list va, va2;

 va_start(va, fmt);
 va_start(va2, fmt);
 vprt_tfwarn_msg(fmt, va, va2);
 va_end(va);
 va_end(va2);
 return(1);
}

/*
 * actually print a warning message tf form - also used by tf message
 */
static void vprt_tfwarn_msg(char *fmt, va_list va, va_list va2)
{
 char s1[RECLEN], s2[RECLEN];

 __pv_warn_cnt++;
 /* warning number 600 is for all pli tasks so all can be suppressed */
 if (__no_warns || __em_suppr(600)) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 __my_fprintf(stdout, "**%s(%d) PLI WARN**%s [600] ", __in_fils[__sfnam_ind],
  __slin_cnt, s1);
 __my_vfprintf(stdout, fmt, va, va2);
 my_putc_('\n', stdout);
}

/*
 * unimplemented sprintf like routine  
 */
extern int32 tf_text(char *fmt, ...)
{
 /* ---
 va_list va;

 va_start(va, fmt);
 va_end(va);
 --- */
 __sgferr(1287, "tf_text not implemented - use sprintf and tf_message");
 return(TF_NULLPARAM);
}

/*
 * print a message using Cver style error message format
 * facility and messno ignored
 */
extern int32 tf_message(int32 level, char *facility, char *messno,
 char *message, ...)
{
 va_list va, va2;
 char s1[RECLEN], s2[RECLEN];

 va_start(va, message);
 va_start(va2, message);

 switch (level) {
  case ERR_INTERNAL:
   if (__run_state == SS_SIM)
    sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
   else strcpy(s1, "");
   __my_fprintf(stdout, "**%s(%d) PLI INTERNAL FATAL**%s [300] ",
    __in_fils[__sfnam_ind], __slin_cnt, s1);
   __my_vfprintf(stdout, message, va, va2);
   my_putc_('\n', stdout);
   va_end(va);
   va_end(va2);
   __my_exit(2, TRUE);
   break;
  case ERR_ERROR: case ERR_SYSTEM:
   vprt_tferr_msg(message, va, va2);
   break;
  case ERR_MESSAGE:
   if (!__no_informs && !__em_suppr(400))
    { 
     __my_fprintf(stdout, "--%s(%d) PLI MESSAGE** [400] ",
      __in_fils[__sfnam_ind], __slin_cnt);
     __my_vfprintf(stdout, message, va, va2);
     my_putc_('\n', stdout);
    }
   break;
  case ERR_WARNING:
   vprt_tfwarn_msg(message, va, va2);
   break;
 }
 va_end(va);
 va_end(va2);
 return(1);
}

/*
 * printf to multi-channel descriptor
 */
extern void io_mcdprintf(int32 mcd, char *format, ...)
{
 int32 i;
 va_list va, va2;

 /* SJM 09/09/03 - fd case easy because only one stream to write to */
 if ((mcd & FIO_MSB) == FIO_MSB)
  {
   int32 fd;

   fd = (int32) (mcd & ~FIO_MSB);
   /* if fd does not correspond to open file, just set error indicator */
   if (__fio_fdtab[fd] == NULL)
    {
     __sgfwarn(651,
      "in tf_ pli file not open for descriptor number %d ", fd);
     errno = EBADF;
     return;
    }
   /* SJM 10/13/99 - ansii std says varargs not usable after vprintf */
   va_start(va, format);
   vfprintf(__fio_fdtab[fd]->fd_s, format, va);
   va_end(va);
   return;
  }

 /* SJM 03/26/00 - mcd 1 now both stdout and log if open */
 if ((mcd & 1) != 0)
  {
   va_start(va, format);
   va_start(va2, format);

   vprintf(format, va);
   if (__log_s != NULL) vfprintf(__log_s, format, va2);

   va_end(va);
   va_end(va2);
  }

 /* mcd's may require writing to lots of files */
 for (i = 1; i < 31; i++) 
  {
   if (((mcd >> i) & 1L) != 0L)
    { 
     if (__mulchan_tab[i].mc_s == NULL)
      {
       __sgfwarn(651,
        "in tf_ pli multi-channel descriptor bit %d on, but file not open",
        i);
      }
     else
      {
       /* SJM 10/13/99 - ansii std says varargs not usable after vprintf */
       va_start(va, format);
       vfprintf(__mulchan_tab[i].mc_s, format, va);
       va_end(va);
      }
    }
  }
 if (((mcd >> 31) & 1) != 0)
  {
   __sgfwarn(651,
    "in tf_ pli multi-channel descriptor bit 31 on but file not open - unusable because reserved for new Verilog 2001 file I/O");
  }
}

/*
 * formatted print to both standard output and log file (if open) 
 */
extern void io_printf(char *format, ...)
{
 va_list va, va2;

 va_start(va, format);
 va_start(va2, format);
 vprintf(format, va);
 if (__log_s != NULL) vfprintf(__log_s, format, va2);
 va_end(va);
 va_end(va2);
}

/*
 * scan plus args (for now scan args and if no + do not try to match)
 * plusarg does not have leading +
 * DOCUMENTME - returned string is read only
 */
extern char *mc_scan_plusargs(char *plusarg)
{
 int32 arglen, optlen;
 struct optlst_t *olp;
 char *chp;

 arglen = strlen(plusarg);
 /* all options expanded and saved so this is easy */
 for (olp = __opt_hdr; olp != NULL; olp = olp->optlnxt)
  {
   /* ignore markers added for building vpi argc/argv */
   if (olp->is_bmark || olp->is_emark) continue;

   chp = olp->opt;
   if (*chp != '+') continue;
   /* if plus arg longer than option cannot match */ 
   if ((optlen = strlen(&(chp[1]))) < arglen) continue; 
   /* match prefix */
   if (strncmp(&(chp[1]), plusarg, arglen) != 0) continue; 
   /* return pointer to 1st char after matched prefix */
   /* may be empty string */
   return(&(chp[arglen + 1]));
  }
 /* if no match return nil ptr not empty string */
 return(NULL);
}

/*
 * OLD ROUTINES NO LONGER IN STANDARD?
 */

/*
 * free instance - added routine if needed
 * rarely needed 
 */
/* ---
extern char tf_freeinstance(char *inst)
{
 free(inst);
}
--- */

/*
 * ROUTINES NOT INCLUDED IN PRELIMARY IEEE VERIUSER.H
 */

/*
 * think this is no longer needed since assigning causes propagate
 */
extern int32 tf_ievaluatep(int32 pnum, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_evaluatep(pnum);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * evaluate an expression for its value and set in tf_texprinfo node
 * notice this is for exprinfo not nodeinfo
 *
 * this uses a previously (last) set tf_texprinfo for this inst.
 * return 0 if no previous expr or error else 1
 * places new value into exprinfo structure
 *
 * for memories must be cell select since tf_ func/task argument must be
 * legal ver expr.
 * notice this is fast because only changes value exprinfo fields 
 */
extern int32 tf_evaluatep(int32 pnum)
{
 int32 wi, wlen, rv, inum;
 struct t_tfexprinfo *pinfo;
 struct xstk_t *xsp;
 double d1;
 struct tfarg_t *tfap;
 struct expr_t *xp;

 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_evaluatep");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 tfap = &(__tfrec->tfargs[pnum]);
 inum = get_inum_();
 pinfo = (struct t_tfexprinfo *) tfap->sav_xinfos[inum];
 if (pinfo == NULL) return(1);
 xp = tfap->arg.axp;

 /* here this always handles any gref itree pushing and popping */
 xsp = __eval_xpr(xp);
 if (xp->is_real)
  {
   memcpy(&d1, xsp->ap, sizeof(double));
   pinfo->real_value = d1;
  }
 else
  {
   wlen = wlen_(xp->szu.xclen);
   for (wi = 0; wi < wlen; wi++)
    { 
     pinfo->expr_value_p[wi].avalbits = (int32) xsp->ap[wi];
     pinfo->expr_value_p[wi].bvalbits = (int32) xsp->bp[wi];
    }  
  }
 __pop_xstk();
 return(0);
} 

/*
 * progogate a changed rhs value to all lhs?
 * what does this do and how is expr. stored ?
 */
extern int32 tf_ipropagatep(int32 pnum, char *inst)
{
 int32 rv;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;
 decl_idp_locals_;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 set_save_idp_(__tfinst->tfidp);
 rv = tf_propagatep(pnum);
 restore_idp_();
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(rv);
}

/*
 * propagate the value user placed in node info structure
 * previous call of tf nodeinfo set current node info struct 
 * 
 * this does not work for strengths because node info fails
 *
 * SJM 11/30/99 - changed to follow new LRM and use exprinfo for
 * save (from tf_exprinfo) instead of node info (from tf_nodeinfo)
 */
extern int32 tf_propagatep(int32 pnum)
{
 int32 wi, rv, inum;
 struct xstk_t *xsp;
 struct t_vecval *vecp; 
 struct t_tfexprinfo *xpinfo;
 double d1;
 struct tfarg_t *tfap;
 struct expr_t *lhsxp;

 if (__tfrec == NULL)
  {
   rv = bad_notfcontext_err("tf_propagatep");
   /* SJM 12/17/02 - error is 1 and success is 0 */
   if (rv == TF_NULLPARAM) return(1); else return(0);
  }
 tfap = &(__tfrec->tfargs[pnum]);
 if (pnum < 1 || pnum >= __tfrec->tfanump1) return(1);

 /* need previously stored from call to expr info */
 inum = get_inum_();
 xpinfo = (struct t_tfexprinfo *) tfap->sav_xinfos[inum];
 if (xpinfo == NULL) return(1);

 if (xpinfo->expr_type == TF_READONLY
  || xpinfo->expr_type == TF_READONLYREAL
  || xpinfo->expr_type == TF_STRING
  || xpinfo->expr_type == TF_NULLPARAM)  
  {  
   __sgferr(1280,
    "tf_propagatep saved expression illegal - expressions not writeable");
   return(1);
  }
 lhsxp = tfap->arg.axp;
 if (lhsxp->x_stren)
  {  
   __sgferr(1212,
    "tf_propagatep of strength expression illegal - tf_ does not store strength");
   return(1);
  }

 /* know user filled field of pinfo before calling this */
 /* copy value to internal a/b form for assignment */
 if (xpinfo->expr_type == TF_READWRITEREAL)
  {
   d1 = xpinfo->real_value;
   push_xstk_(xsp, REALBITS);
   memcpy(xsp->ap, &d1, sizeof(double));
  }
 else
  {
   /* here just convert from vecval p form to internal a/b form */
   /* SJM 02/16/07 - push xstk takes num bits not bytes - thanks SAS@Tharas */
   push_xstk_(xsp, xpinfo->expr_ngroups*WBITS);
   vecp = xpinfo->expr_value_p;
   for (wi = 0; wi < xpinfo->expr_ngroups; wi++)
    {
     xsp->ap[wi] = (word32) vecp[wi].avalbits;
     xsp->bp[wi] = (word32) vecp[wi].bvalbits;
    }
  } 
 exec_tfarg_assign(tfap, lhsxp, xsp->ap, xsp->bp);
 __pop_xstk();
 return(0);
}

/*
 * need $restart mechanism for this 
 */
extern int32 tf_read_restart(char *blockptr, int32 blocklen)
{
 /* UNIMPLMENTED */
 __sgferr(1287, 
  "tf_read_restart not implemented - $save/$restart not yet implemented"); 
 return(0);
}

extern int32 tf_write_save(char *blockptr, int32 blocklen)
{
 /* UNIMPLMENTED */
 __sgferr(1287, 
  "tf_write_save not implemented - $save/$restart not yet implemented"); 
 return(0);
}

/*
 * other pli function/task call version of sleep ? 
 */
/* ---
extern int32 tf_isleep(int32 delay, char *inst)
{
 int32 rv;
}
-- */

/*
 * scale to internal time unit and then block for that time
 * think this is like setdelay - or maybe has no argument and just 
 * terminates ? - why not just set delay and return?
 */
/* -- 
extern int32 tf_sleep(int32 delay)
{
 return(0);
}
-- */

/*
 * NEW ROUTINES ADDED FOR PVER
 */

/*
 * routine to determine source location of tf_ instance
 */
extern char *tf_igetsourceloc(int32 *lineno, char *inst)
{
 char *chp;
 struct tfinst_t *sav_tfip;
 struct tfrec_t *sav_tfrp;

 set_tfinst_(inst, sav_tfip, sav_tfrp);
 chp = tf_getsourceloc(lineno);
 __tfinst = sav_tfip;
 __tfrec = sav_tfrp;
 return(chp);
}


extern char *tf_getsourceloc(int32 *lineno)
{
 int32 slen;
 char *chp, *chp2;

 if (__tfrec == NULL)
  {
   bad_notfcontext_err("tf_getsourceloc");
   return(NULL);
  }
 chp2 = __in_fils[__tfrec->tffnam_ind];
 slen = strlen(chp2);
 chp = __my_malloc(slen + 1); 
 strcpy(chp, chp2);
 *lineno = __tfrec->tflin_cnt;
 return(chp);
}

/*
 * ROUTINES FOR MISCTF PARAMETER CHANGE PROCESSING
 */

/*
 * call the misctf routine after parameter changed
 *
 * know dce will not be linked on unless async is on for this inst/call 
 * know right itree location
 *
 * notice since this dce does not fit into normal scheme dce 1inst T if
 * func or F if task, dce2 union is ptr to task call statement or fcall expr
 * and unused dce_downitp is cast to int32 for pnum (set when built)
 */
extern void __pvc_call_misctf(struct dcevnt_t *dcep)
{
 int32 pnum, sav_fnam_ind, sav_slin_cnt, inum;
 struct st_t *stp;
 struct expr_t *fcallx; 
 struct t_tfcell *tfcp;
 struct tskcall_t *tkcp;
 struct systsk_t *stbp;
 struct sysfunc_t *sfbp;
 struct tfinst_t tfiwrk;
 int32 (*misctf)();

 stp = NULL;
 fcallx = NULL;
 /* T dce iscol for pvc means dce2 union is ptr to fcallx else to stp */
 if (dcep->dce_tfunc)
  {
   fcallx = dcep->dceu2.dce_pvc_fcallx; 
   sfbp = fcallx->lu.x->lu.sy->el.esyftbp;
   tfcp = &(__shadow_veriusertfs[sfbp->syfnum - BASE_VERIUSERTFS]); 
   __tfrec = fcallx->lu.x->szu.xfrec;
  }
 else
  {
   stp = dcep->dceu2.dce_pvc_stp;
   tkcp = &(stp->st.stkc);
   stbp = tkcp->tsksyx->lu.sy->el.esytbp;
   tfcp = &(__shadow_veriusertfs[stbp->stsknum - BASE_VERIUSERTFS]); 
   __tfrec = tkcp->tkcaux.trec;
  }

 pnum = dcep->dceu.pnum;
 /* step 1: update pvc change flags */  
 /* pvc code never turns change flags off user must call movepvc routine */
 inum = get_inum_();
 __tfrec->tfargs[pnum].old_pvc_flgs[inum] = 1;

 /* if no misc tf routine - done */
 /* SJM 06/13/1999 - misctf always requires 3rd argument although ignored */
 /* except for synchon callbacks ?? */
 if ((misctf = tfcp->misctf) == NULL) return;

 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;
 __vpifnam_ind = __sfnam_ind; 
 __vpilin_cnt = __slin_cnt;

 /* set up environment that is current implied tf instance */
 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = NULL;
 __tfinst->tfstp = NULL;
 __tfinst->tfidp = __idp; 
 if (dcep->dce_tfunc) __tfinst->callx = fcallx; else __tfinst->tfstp = stp;

 /* FIXME ??? - not 64 bit clean */
 (*misctf)((int32) tfcp->data, REASON_PARAMVC, pnum);
 __tfinst = NULL;
 __tfrec = NULL;
 __sfnam_ind = sav_fnam_ind; __slin_cnt = sav_slin_cnt;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;
}

/*
 * build and link on special pvc tf_ parameter change dce for one param
 * xp is param expr (can be rhs) - know __tfrec and instance loc. set
 */
static void bld_pvc_dces(struct expr_t *xp, int32 pnum)
{
 struct net_t *np;
 int32 biti, bitj, inum;
 word32 *wp;
 struct expr_t *idndp, *ndx;
 struct expr_t *fax;
 
 switch (xp->optyp) {
  case GLBREF:
   idndp = xp; 
   biti = bitj = -1;
glb_dce:
   np = idndp->lu.sy->el.enp;
   linkon_pvc_dce(np, biti, bitj, idndp->ru.grp, pnum);
   break;
  case ID:
   idndp = xp; 
   np = xp->lu.sy->el.enp;
   linkon_pvc_dce(np, -1, -1, (struct gref_t *) NULL, pnum);
   break;
  /* SJM 05/18/00 - must do nothing for reals */ 
  case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM: case OPEMPTY:
   return;
  case LSB:
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   ndx = xp->ru.x;
   /* for monits, any reg or non scalaraed wire must trigger on any chg */
   if (ndx->optyp == NUMBER)
    {
     wp = &(__contab[ndx->ru.xvi]);
     if (wp[1] != 0L) biti = -1; else biti = (int32) wp[0];
    }
   else if (ndx->optyp == ISNUMBER)
    {
     wp = &(__contab[ndx->ru.xvi]);
     inum = get_inum_();
     wp = &(wp[2*inum]);

     /* need length for IS number because can be wider - but get low */
     if (wp[1] != 0L) biti = -1; else biti = (int32) wp[0];
    }
   else
    {
     /* notice for monitor and dctrl event change, variable here is legal */
     /* and implies change for index and trigger on all bits of variable */
     bld_pvc_dces(ndx, pnum);
     biti = -1;
    }
   bitj = biti;
   if (biti != -1 && !np->vec_scalared) biti = bitj = -1;
   if (idndp->optyp == GLBREF) goto glb_dce;
   linkon_pvc_dce(np, biti, biti, (struct gref_t *) NULL, pnum);
   break;
  case PARTSEL:
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   ndx = xp->ru.x;
   /* know part select never IS */
   biti = (int32) __contab[ndx->lu.x->ru.xvi];
   bitj = (int32) __contab[ndx->ru.x->ru.xvi];
   if (!np->vec_scalared) biti = bitj = -1;
   if (idndp->optyp == GLBREF) goto glb_dce;
   linkon_pvc_dce(np, biti, bitj, (struct gref_t *) NULL, pnum);
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   idndp = xp->lu.x; 
   np = idndp->lu.sy->el.enp;
   ndx = xp->ru.x;
   /* these are always variable case */
   biti = bitj = -1;
   if (idndp->optyp == GLBREF) goto glb_dce;
   linkon_pvc_dce(np, biti, bitj, (struct gref_t *) NULL, pnum);
   break;
  case FCALL:
   /* if any arguments of system or user functions change, monitor triggers */
   /* notice $time function do not have arguments */
   for (fax = xp->ru.x; fax != NULL; fax = fax->ru.x)
    bld_pvc_dces(fax->lu.x, pnum);
   break;
  case LCB:
   for (fax = xp->ru.x; fax != NULL; fax = fax->ru.x)
    bld_pvc_dces(fax->lu.x, pnum);
   break;
  default:
   if (xp->lu.x != NULL) bld_pvc_dces(xp->lu.x, pnum);
   if (xp->ru.x != NULL) bld_pvc_dces(xp->ru.x, pnum);
   break;
 } 
}

/*
 * link on a special (one per inst) pvc dce
 *
 * know one of callx and stp set but not both
 * -2 IS form impossible since any one inst. IS form converted to constant
 * before here
 * need old value for ranges since need exact change processing
 * not sure if ref. itp needed here but stored
 */
static void linkon_pvc_dce(struct net_t *np, int32 biti, int32 bitj,
 struct gref_t *grp, int32 pnum)
{
 struct dcevnt_t *dcep;
 t_midat *xmr_idp, *ref_idp; 
 struct dceauxlst_t *dclp;
 struct mod_t *cur_mdp;
 decl_idp_locals_;

 ref_idp = __idp;
 save_idp = NULL;
 if (grp != NULL) 
  { 
   xmr_idp = __xmrget_refgrp_to_targ(grp); 
   set_save_idp_(xmr_idp); 
  }
 /* allocate, init, and fill the fields */
 dcep = __alloc_dcevnt(np);
   
 if (biti == -1) dcep->dce_typ = DCE_PVC;
 else
  {
   dcep->dce_typ = DCE_RNG_PVC;
   dcep->dci1 = biti;
   dcep->dci2.i = bitj;
  }
 /* link this on front */
 dcep->dcenxt = np->dcelst;

 /* AIV 09/25/06 - need to set has_dces bit to T - could be only one */
 /* has checking bit in record_nchg_ - and not executing list */
 np->nchg_has_dces = TRUE;

 np->dcelst = dcep;
 dcep->dce_1inst = TRUE;
 /* this is itree dcep put on */
 dcep->dce_matchu.idp = __idp;
 /* this is placed referenced, unless xmr same as match */
 dcep->dce_refu.idp = ref_idp;

 /* also set unused fmon field to pvc object and other pvc fields */
 if (__tfrec->tf_func)
  {
   dcep->dce_tfunc = TRUE;
   /* unused fmon field used for callx */
   dcep->dceu2.dce_pvc_fcallx = __tfrec->tfu.callx;
  }
 else
  {
   dcep->dce_tfunc = FALSE;  
   /* unused fmon field used for stp */
   dcep->dceu2.dce_pvc_stp = __tfrec->tfu.tfstp;
  } 
 /* unused down itp used for tf_ param number (tf_ func ret val not incl) */
 dcep->dceu.pnum = pnum;
 /* __inst_pr is right place */
 __alloc_plidce_prevval(dcep);
 __init_plidce_prevval(dcep);

 /* then link on undo/chg list */
 dclp = (struct dceauxlst_t *) __my_malloc(sizeof(struct dceauxlst_t));
 dclp->ldcep = dcep; 
 dclp->dclnxt = __pvc_dcehdr;
 __pvc_dcehdr = dclp;

 /* since no dce, no loads, and no dmpvars must always turn chg store on */
 if (!dcep->dce_np->nchg_nd_chgstore)
  {
   /* this also regen net's decl iops from dce if -O on */
   cur_mdp = get_inst_mod_();
   __dce_turn_chg_store_on(cur_mdp, dcep, TRUE);  
  }
 /* SJM 02/06/03 - may have npps but not dces so must turn this on */
 /* since nchg nd chgstore on, know nchg action right */
 if (np->ntyp >= NONWIRE_ST) np->nchg_has_dces = TRUE;

 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

/* 
 * ROUTINES FOR MISCTF ROSYNCHRONIZE PROCESSING
 */

/*
 * end of slot call misctf with reason ro sync
 */
extern void __exec_rosync_misctf(void)
{
 struct tev_t *tevp;

 __rosync_slot = TRUE; 
 for (tevp = __tehdr_rosyncp; tevp != NULL; tevp = tevp->tenxtp)
  rosync_call_misctf(tevp);
 /* slot end action turned off all at once later */
 /* add the list on to head of tev free list */ 
 __teend_rosyncp->tenxtp = __tefreelstp;
 __tefreelstp = __tehdr_rosyncp;
 __tehdr_rosyncp = __teend_rosyncp = NULL;
 __rosync_slot = FALSE; 
}

/*
 * call the misctf routine for reason ro synchronize
 */
static void rosync_call_misctf(struct tev_t *tevp)
{
 int32 sav_fnam_ind, sav_slin_cnt, itinum, inum;
 struct t_tfcell *tfcp;
 struct tfinst_t tfiwrk;
 int32 (*misctf)();
 decl_idp_locals_;

 __tfrec = tevp->tu.tetfrec;
 tfcp = get_tfcell(__tfrec);

 /* if no misc. tf routine just turn off, nothing to do */
 if ((misctf = tfcp->misctf) == NULL)
  {
   itinum = (int32) tevp->te_idp[MD_INUM];
   __tfrec->rosync_tevp[itinum] = NULL;
   return;
  }

 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;

 set_save_idp_(tevp->te_idp);
 /* set up environment that is current implied tf instance */
 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = NULL;
 __tfinst->tfstp = NULL;
 __tfinst->tfidp = __idp; 
 if (__tfrec->tf_func) __tfinst->callx = __tfrec->tfu.callx;
 else __tfinst->tfstp = __tfrec->tfu.tfstp;

 /* SJM 06/13/1999 - misctf always requires 3rd argument although ignored except for syncon callbacks ?? */
 /* FIXME ??? - not 64 bit clean */
 (*misctf)((int32) tfcp->data, REASON_ROSYNCH, 0);

 inum = get_inum_();
 __tfrec->rosync_tevp[inum] = NULL;
 restore_idp_();
 __tfrec = NULL;
 __tfinst = NULL;
 __sfnam_ind = sav_fnam_ind; __slin_cnt = sav_slin_cnt;
}

/*
 * call the misctf routine for reason synchronize
 *
 * this is called once to process every scheduled #0 sync event
 * there will be at most one event per call/inst but turned off
 * so can be called next cycle of #0 loop
 * no way these can be canceled except removed on reset
 */
extern void __sync_call_misctf(void)
{
 int32 sav_fnam_ind, sav_slin_cnt, itinum, inum;
 struct t_tfcell *tfcp;
 struct tfinst_t tfiwrk;
 struct tev_t *tevp;
 int32 (*misctf)();
 decl_idp_locals_;

 tevp = __cur_tevp;
 __tfrec = tevp->tu.tetfrec;
 tfcp = get_tfcell(__tfrec);
 /* if no misc. tf routine just turn off, nothing to do */
 if ((misctf = tfcp->misctf) == NULL)
  {
   itinum = (int32) tevp->te_idp[MD_INUM];
   __tfrec->sync_tevp[itinum] = NULL;
   return;
  }

 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;

 set_save_idp_(tevp->te_idp);
 /* set up environment that is current implied tf instance */
 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = NULL;
 __tfinst->tfstp = NULL;
 __tfinst->tfidp = __idp; 
 if (__tfrec->tf_func) __tfinst->callx = __tfrec->tfu.callx;
 else __tfinst->tfstp = __tfrec->tfu.tfstp;

 /* SJM 06/13/1999 - misctf always requires 3rd argument although ignored except for syncon callbacks ?? */
 /* FIXME ??? - not 64 bit clean */
 (*misctf)((int32) tfcp->data, REASON_SYNCH, 0);

 inum = get_inum_();
 __tfrec->sync_tevp[inum] = NULL;
 restore_idp_();
 __tfrec = NULL;
 __tfinst = NULL;
 __sfnam_ind = sav_fnam_ind; __slin_cnt = sav_slin_cnt;
}

/*
 * call the misctf routine for reason reactivate afer delay
 *
 * 0 is pound 0 
 */
extern void __setdel_call_misctf(void)
{
 int32 sav_fnam_ind, sav_slin_cnt, itinum;
 struct tevlst_t *telp, *last_telp;
 struct t_tfcell *tfcp;
 struct tfinst_t tfiwrk;
 struct tev_t *tevp;
 int32 (*misctf)();
 decl_idp_locals_;

 tevp = __cur_tevp;
 __tfrec = tevp->tu.tetfrec;
 tfcp = get_tfcell(__tfrec);

 /* if no misc. tf routine just turn off, nothing to do */
 if ((misctf = tfcp->misctf) == NULL) goto free_telst;

 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt; 
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;

 set_save_idp_(tevp->te_idp);
 /* set up environment that is current implied tf instance */
 /* notice assignment of addr. to static works since niled in this rout. */
 __tfinst = &tfiwrk;
 __tfinst->callx = NULL;
 __tfinst->tfstp = NULL;
 __tfinst->tfidp = __idp; 
 if (__tfrec->tf_func) __tfinst->callx = __tfrec->tfu.callx;
 else __tfinst->tfstp = __tfrec->tfu.tfstp;

 /* SJM 06/13/1999 - misctf always requires 3rd argument although ignored except for syncon callbacks ?? */
 /* FIXME ??? - not 64 bit clean */
 (*misctf)((int32) tfcp->data, REASON_REACTIVATE, 0);

 restore_idp_();
 __sfnam_ind = sav_fnam_ind; __slin_cnt = sav_slin_cnt;
 __tfinst = NULL;

free_telst:
 last_telp = NULL;
 itinum = (int32) tevp->te_idp[MD_INUM];
 telp = __tfrec->setd_telst[itinum];
 for (; telp != NULL; telp = telp->telnxt)
  {
   /* but tevp can not change */
   if (tevp == telp->tevp)
    {
     if (last_telp == NULL)
      __tfrec->setd_telst[itinum] = telp->telnxt;
     else last_telp->telnxt = telp->telnxt;
     /* link 1 freed on front */
     telp->telnxt = __ltevfreelst;
     __ltevfreelst = telp;
     __tfrec = NULL;
     return;
    }
   last_telp = telp;
  }
 __case_terr(__FILE__, __LINE__); 
}

/*
 * process a tf strdelputp store
 *
 * know parameter is read write
 * know value converted and available here 
 * know tf isrw never concat and may be either wire or reg 
 */
extern void __process_putpdel_ev(void)
{
 int32 wlen, inum;
 int32 lhslen;
 word32 *ap, *bp;
 byte *sbp;
 struct expr_t *lhsxp; 
 struct tfarg_t *tfap;
 struct tfrec_t *tfrp;
 struct tedputp_t *tedp; 
 struct dltevlst_t *dlp;

 tedp = __cur_tevp->tu.tedputp;
 __cur_tevp->tu.tedputp = NULL;

 tfrp = tedp->tedtfrp;
 tfap = &(tfrp->tfargs[tedp->tedpnum]);

 lhsxp = tfap->arg.axp;
 lhslen = lhsxp->szu.xclen;
 wlen = wlen_(lhslen);
 if (__ev_tracing) emit_tputd_trmsg(tedp, tfap);
 ap = tedp->tedwp;
 bp = &(ap[wlen]);
 exec_tfarg_assign(tfap, lhsxp, ap, bp);
 /* free the event tf delputp record stored rhs assign to value */
 if (lhsxp->x_stren)
  { sbp = (byte *) tedp->tedwp; __my_free(sbp, lhslen); }
 else __my_free(tedp->tedwp, 2*wlen_(lhslen)*WRDBYTES);

 tedp->tedtfrp =  (struct tfrec_t *) __tedpfreelst;
 __tedpfreelst = tedp;
 inum = get_inum_();
 dlp = tfap->dputp_tedlst[inum];
 /* also link out tevlst element - must be on front */
 /* DBGMAYBELEAVE */
 if (dlp == NULL || __cur_tevp != dlp->tevp) __misc_terr(__FILE__, __LINE__);
 /* --- */
 tfap->dputp_tedlst[inum] = dlp->terp;
 dlp->telp = NULL;
 /* put this telst elemnt on free list */
 dlp->terp = __dltevfreelst;
 __dltevfreelst = dlp;
}

/*
 * routine to assign tf arg 
 * input is a b pointer (b non used if stren) and lhs expr
 * __inst_pr set to right instance
 */
static void exec_tfarg_assign(struct tfarg_t *tfap, struct expr_t *lhsxp,
 word32 *ap, word32 *bp)
{
 int32 lhslen, schd_wire, inum;
 byte *sbp;

 /* case 1 procedural assign */ 
 lhslen = lhsxp->szu.xclen;
 if (tfap->anp->ntyp >= NONWIRE_ST)
  { __exec2_proc_assign(lhsxp, ap, bp, lhslen); return; }

 /* case 2: need continuous assign (concat impossible) */
 /* case 2a: fi>1 */
 if (lhsxp->x_multfi)
  {
   /* first update the driver then reeval all drivers */
   if (lhsxp->x_stren)
    {
     sbp = (byte *) ap;
     /* notice can just copy this is per inst table for driver */
     inum = get_inum_();
     memcpy(&(tfap->tfdrv_wp.bp[inum*lhslen]), sbp, lhslen);
    }
   else __st_perinst_val(tfap->tfdrv_wp, lhslen, ap, bp);
   __mdr_assign_or_sched(lhsxp);
   return;
  }

 /* case 2b: fi == 1 conta assign */ 
 if (lhsxp->lhsx_ndel && !__wire_init) schd_wire = TRUE;
 else schd_wire = FALSE;
 __exec_conta_assign(lhsxp, ap, bp, schd_wire);
}

/*
 * emit a strdelputp trace message if tracing on
 */
static void emit_tputd_trmsg(struct tedputp_t *tedp, struct tfarg_t *tfap)
{ 
 word32 *ap, *bp;
 struct tfrec_t *tfrp;
 struct expr_t *lhsxp;
 char s1[RECLEN], s2[IDLEN];

 lhsxp = tfap->arg.axp;
 if (tfap->anp->ntyp >= NONWIRE_ST) strcpy(s1, "procedural");
 else
  {
   if (lhsxp->x_multfi) strcpy(s1, "continuous fi>1");
   else strcpy(s1, "continuous fi=1");
  }
 tfrp = tedp->tedtfrp;
 if (lhsxp->x_stren)
  __st_regab_tostr(s2, (byte *) tedp->tedwp, lhsxp->szu.xclen);
 else
  { 
   ap = tedp->tedwp;
   bp = &(ap[wlen_(lhsxp->szu.xclen)]);
   __regab_tostr(s2, ap, bp, lhsxp->szu.xclen, BHEX, FALSE);
  }
 __evtr_resume_msg();
 __tr_msg("tf_ arg %d at %s in %s strdelputp %s assign value %s\n",
  tedp->tedpnum, __bld_lineloc(__wrks1, tfrp->tffnam_ind, tfrp->tflin_cnt),
  __msg2_cur_blditree(__wrks2), s1, s2);
} 

/*
 * ROUTINES TO REINITIALIZE PLI STUFF - TFRECS AND VPI ON RESET
 */

/*
 * during reset reinitialize tfrecs 
 */
extern void __reinit_tfrecs(void) 
{
 struct tfrec_t *tfrp;

 for (tfrp = __tfrec_hdr; tfrp != NULL; tfrp = tfrp->tfrnxt)
  reinit_1tfrec(tfrp);

 /* free all ro sync events */ 
 if (__tehdr_rosyncp != NULL)
  {
   /* add the list on to head of tev free list */ 
   __teend_rosyncp->tenxtp = __tefreelstp;
   __tefreelstp = __tehdr_rosyncp;
   __tehdr_rosyncp = __teend_rosyncp = NULL;
  }
}
 
/*
 * reinit 1 tfrec
 */
static void reinit_1tfrec(struct tfrec_t *tfrp)
{
 int32 i, pi;
 struct dltevlst_t *dlp;
 struct tevlst_t *tlp;
 struct dltevlst_t *last_dlp;
 struct tevlst_t *last_tlp;
 struct tfarg_t *tfap;
 struct expr_t *xp;
 struct mod_t *mdp;
 struct dceauxlst_t *dclp;

 /* DBG remove --- */
 if (tfrp->tf_inmdp == NULL) __misc_terr(__FILE__, __LINE__);
 /* ---*/

 mdp = tfrp->tf_inmdp;
 /* notice arguments start from 1 - 0 is place holder */
 /* arg 0 used for func. return value, but tfap[0] not used */
 for (pi = 1; pi < tfrp->tfanump1; pi++)
  {
   tfap = &(tfrp->tfargs[pi]);
   memset(tfap->old_pvc_flgs, 0, mdp->flatinum);
   memset(tfap->sav_pvc_flgs, 0, mdp->flatinum);
   xp = tfap->arg.axp;
   for (i = 0; i < mdp->flatinum; i++)
    {
     tfap->sav_xinfos[i] = NULL;
     if ((dlp = tfap->dputp_tedlst[i]) != NULL)
      {
       for (last_dlp = NULL; dlp != NULL; dlp = dlp->terp) last_dlp = dlp;
       last_dlp->terp = __dltevfreelst; 
       __dltevfreelst = tfap->dputp_tedlst[i];
       tfap->dputp_tedlst[i] = NULL;
      } 
    }
   if (tfap->tfdrv_wp.bp != NULL) __init_tfdrv(tfap, xp, mdp);
  }

 for (i = 0; i < mdp->flatinum; i++) 
  {
   if (tfrp->asynchon[i])
    {
     /* DBG remove ---*/
     if (tfrp->pvcdcep[i] == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* SJM 01/02/03 - new algorithm pvcs stay on across reset like vpi */
     for (dclp = tfrp->pvcdcep[i]; dclp != NULL; dclp = dclp->dclnxt)
      {
       /* SJM 05/08/03 - always one inst form */ 
       /* but need to re-initialize previous value */
       __init_plidce_prevval(dclp->ldcep);
      } 
    }
   /* still always remove any pending scheduled event */
   tfrp->rosync_tevp[i] = NULL;
   tfrp->sync_tevp[i] = NULL;
   /* notice any events for these freed elswhere */
   if ((tlp = tfrp->setd_telst[i]) != NULL)
    {
     for (last_tlp = NULL; tlp != NULL; tlp = tlp->telnxt) last_tlp = tlp;
     last_tlp->telnxt = __ltevfreelst; 
     __ltevfreelst = tfrp->setd_telst[i];
     tfrp->setd_telst[i] = NULL;
    }
  }
}

/*
 * MISCELLANEOUS ROUTINES
 */

/*
 * call to malloc that dies if no memory available
 * these are normal OS memory allocation with error terminaton
 */
extern char *__mytf_malloc(int32 size)
{
 char *cp;

 if ((cp = (char *) malloc((word32) size)) == NULL)
  {
   __crit_msg(
   "**FATAL[1]: No more memory from tf_ call at file %s line %d - %ld bytes memory used\n",
    __in_fils[__tfrec->tffnam_ind], __tfrec->tflin_cnt, __mem_use);
   __my_exit(4, TRUE);
  }
 /* DBG remove ---
 if (__debug_flg)
  __dbg_msg("tf_ allocated %d bytes\n", size);
 --- */
 return(cp);
}
